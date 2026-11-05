"""Bounded CodeLlama-13B load/generation probe; no benchmark-score claim."""
import concurrent.futures
import hashlib
import json
import os
from pathlib import Path
import shutil
import socket
import subprocess
import sys
import time
import urllib.request


def log(event, **fields):
    print(json.dumps({"event": event, **fields}), flush=True)


def main():
    persistent = Path(sys.argv[1]).resolve()
    temporary = Path(os.environ["CODERUJB_JOB_TMP"]).resolve()
    model_dir = temporary / "model"
    model_dir.mkdir()
    manifest = json.loads((persistent / "download-manifest.json").read_text())
    result = {
        "status": "started",
        "job_id": os.environ["SLURM_JOB_ID"],
        "node": socket.gethostname(),
        "repository": manifest["repo"],
        "revision": manifest["revision"],
        "temporary_model_directory": str(model_dir),
        "job_memory_mib": os.environ.get("SLURM_MEM_PER_NODE"),
        "benchmark_evaluated": False,
    }
    result_file = persistent / "result.json"
    result_file.write_text(json.dumps(result, indent=2) + "\n")
    started = time.monotonic()
    try:
        import torch
        import transformers
        from transformers import AutoModelForCausalLM, AutoTokenizer

        result.update(torch=torch.__version__, transformers=transformers.__version__,
                      cuda=torch.version.cuda, gpu=torch.cuda.get_device_name(0))
        log("runtime_ready", **result)
        expected_bytes = sum(f["size"] for f in manifest["files"])
        assert shutil.disk_usage(temporary).free > expected_bytes + 5_000_000_000
        deadline = time.monotonic() + 600

        def download(item):
            name = item["rfilename"]
            url = (f'https://huggingface.co/{manifest["repo"]}/resolve/'
                   f'{manifest["revision"]}/{name}?download=true')
            output = model_dir / name
            digest = hashlib.sha256()
            size = 0
            last_log = time.monotonic()
            attempts = 0
            while size < item["size"]:
                attempts += 1
                headers = {"Accept-Encoding": "identity"}
                if size:
                    headers["Range"] = f"bytes={size}-"
                request = urllib.request.Request(url, headers=headers)
                try:
                    with urllib.request.urlopen(request, timeout=40) as response:
                        if size and (response.status != 206 or not response.headers.get(
                                "Content-Range", "").startswith(f"bytes {size}-")):
                            raise RuntimeError(f"Server did not honor the resume offset for {name}")
                        with output.open("ab" if size else "wb") as stream:
                            while True:
                                if time.monotonic() > deadline:
                                    raise TimeoutError("Download exceeded the ten-minute probe budget")
                                chunk = response.read(4 * 1024 * 1024)
                                if not chunk:
                                    break
                                stream.write(chunk)
                                digest.update(chunk)
                                size += len(chunk)
                                if time.monotonic() - last_log > 15:
                                    log("download_progress", file=name, bytes=size, expected=item["size"])
                                    last_log = time.monotonic()
                except OSError as error:
                    if attempts >= 4 or time.monotonic() > deadline:
                        raise
                    log("download_retry", file=name, offset=size, attempt=attempts, error=repr(error))
                    time.sleep(1)
                if attempts >= 4 and size < item["size"]:
                    raise RuntimeError(f"Incomplete download after four attempts: {name}")
            assert size == item["size"], (name, size, item["size"])
            expected_hash = item.get("lfs", {}).get("sha256")
            if expected_hash:
                assert digest.hexdigest() == expected_hash, name
            receipt = {"file": name, "bytes": size, "sha256": digest.hexdigest(),
                       "lfs_sha256_verified": bool(expected_hash)}
            log("download_verified", **receipt)
            return receipt

        with concurrent.futures.ThreadPoolExecutor(max_workers=3) as pool:
            receipts = list(pool.map(download, manifest["files"]))
        result["download_receipts"] = receipts
        result["download_seconds"] = time.monotonic() - started
        log("download_complete", bytes=expected_bytes, seconds=result["download_seconds"])
        tokenizer = AutoTokenizer.from_pretrained(model_dir, local_files_only=True)
        torch.cuda.reset_peak_memory_stats()
        load_started = time.monotonic()
        model = AutoModelForCausalLM.from_pretrained(
            model_dir, torch_dtype=torch.bfloat16, local_files_only=True,
            low_cpu_mem_usage=False, attn_implementation="eager",
        ).to("cuda").eval()
        torch.cuda.synchronize()
        result["load_seconds"] = time.monotonic() - load_started
        result["dtype"] = str(next(model.parameters()).dtype)
        result["parameters"] = sum(p.numel() for p in model.parameters())
        log("model_loaded", parameters=result["parameters"], dtype=result["dtype"],
            seconds=result["load_seconds"], allocated_bytes=torch.cuda.memory_allocated())
        prompt = (persistent / "prompt.txt").read_text().strip()
        encoded = tokenizer(prompt, return_tensors="pt")
        result["prompt_tokens_full"] = int(encoded["input_ids"].shape[-1])
        encoded = {k: v[:, -4096:].to("cuda") for k, v in encoded.items()}
        torch.manual_seed(4)
        generation_started = time.monotonic()
        with torch.inference_mode():
            outputs = model.generate(**encoded, max_new_tokens=256, do_sample=True,
                                     temperature=0.2, pad_token_id=tokenizer.eos_token_id)
        torch.cuda.synchronize()
        generated = tokenizer.decode(outputs[0, encoded["input_ids"].shape[-1]:],
                                     skip_special_tokens=True)
        (persistent / "generation.txt").write_text(generated)
        result.update(
            status="load_and_generation_passed",
            task_idx=4, generation_mode="complete", temperature=0.2, seed=4,
            max_input_tokens=4096, max_new_tokens=256,
            generated_tokens=int(outputs.shape[-1] - encoded["input_ids"].shape[-1]),
            generation_seconds=time.monotonic() - generation_started,
            peak_cuda_allocated_bytes=torch.cuda.max_memory_allocated(),
            peak_cuda_reserved_bytes=torch.cuda.max_memory_reserved(),
        )
        log("generation_complete", **result)
    except Exception as error:
        result.update(status="probe_failed", error=repr(error))
        log("probe_failed", error=repr(error))
        raise
    finally:
        result["elapsed_seconds"] = time.monotonic() - started
        result_file.write_text(json.dumps(result, indent=2) + "\n")
        subprocess.run(["nvidia-smi", "--query-gpu=name,memory.total,memory.used,memory.free",
                        "--format=csv,noheader"], check=False)


if __name__ == "__main__":
    main()
