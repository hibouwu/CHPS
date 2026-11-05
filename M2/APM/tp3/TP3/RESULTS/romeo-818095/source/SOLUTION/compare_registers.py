#!/usr/bin/env python3
"""Compare the unchanged TP3 source with default registers and --maxrregcount=40."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parent.parent
    out = args.output.resolve()
    out.mkdir(parents=True, exist_ok=False)
    nvcc = shutil.which("nvcc")
    cuda_bin = Path(nvcc).resolve().parent
    manifest = {"started_utc": datetime.now(timezone.utc).isoformat(),
                "job_id": os.environ.get("SLURM_JOB_ID"), "node": os.uname().nodename,
                "commands": [], "source_sha256": {}, "binary_sha256": {}}
    for directory in ("CODE", "SOLUTION"):
        for source in sorted((root / directory).rglob("*")):
            if source.is_file() and source.suffix not in (".exe", ".pyc", ".sass"):
                relative = source.relative_to(root)
                snapshot = out / "source" / relative
                snapshot.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(source, snapshot)
                manifest["source_sha256"][str(relative)] = hashlib.sha256(source.read_bytes()).hexdigest()

    def command(label, argv):
        proc = subprocess.run([str(x) for x in argv], cwd=root / "SOLUTION", text=True,
                              stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        (out / f"{label}.log").write_text(proc.stdout)
        manifest["commands"].append({"label": label, "argv": [str(x) for x in argv],
                                     "exit_code": proc.returncode})
        (out / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
        print(f"{label}: exit={proc.returncode}", flush=True)
        if proc.returncode:
            raise RuntimeError(f"{label} failed; inspect its retained log")
        return proc.stdout

    command("environment", ["nvidia-smi"])
    command("nvcc_version", [nvcc, "--version"])
    command("host_compiler_version", ["g++", "--version"])
    variants = {"default": [], "maxreg40": ["--maxrregcount=40"]}
    for name, flags in variants.items():
        binary = out / f"dgemm_{name}.exe"
        command(f"build_{name}", [nvcc, "-O3", "-std=c++17", "-lineinfo", "-Xptxas=-v",
                                  "-arch=sm_90", *flags, root / "SOLUTION/dgemm_tp3.cu", "-o", binary])
        manifest["binary_sha256"][binary.name] = hashlib.sha256(binary.read_bytes()).hexdigest()
        command(f"resource_{name}", [cuda_bin / "cuobjdump", "--dump-resource-usage", binary])
        command(f"sass_{name}", [cuda_bin / "cuobjdump", "--dump-sass", "--function",
                                 "_Z10dgemm_safeILi4EEviiidPKdS1_dPd", binary])
        for m, n, k in [(1, 1, 1), (31, 31, 31), (32, 32, 32), (33, 33, 33),
                         (63, 65, 37), (128, 96, 160), (256, 256, 256)]:
            command(f"check_{name}_{m}_{n}_{k}", [binary, m, n, k, 1])
        for tool, n in [("memcheck", 32), ("memcheck", 33), ("racecheck", 33),
                        ("synccheck", 33), ("initcheck", 33)]:
            command(f"{tool}_{name}_{n}", [cuda_bin / "compute-sanitizer", "--tool", tool,
                                           "--error-exitcode", "99", binary, n, n, n, 1])

    # Alternate executable order across batches; every sample starts with the same C.
    timing = []
    for batch in (1, 2, 3):
        order = ("default", "maxreg40") if batch % 2 else ("maxreg40", "default")
        for n in (1000, 1024, 2048, 4096):
            for name in order:
                log = command(f"batch{batch}_{name}_{n}", [out / f"dgemm_{name}.exe", n, n, n, 7])
                row = re.search(r"TIMING tiled_tm4 repeats=7 median_ms=([\d.e+-]+).*?gemm_gflops=([\d.e+-]+)", log)
                if row is None:
                    raise RuntimeError("Missing timing result")
                timing.append({"batch": batch, "variant": name, "N": n,
                               "median_ms": float(row[1]), "gflops": float(row[2])})
    (out / "timings.json").write_text(json.dumps(timing, indent=2) + "\n")
    manifest["finished_utc"] = datetime.now(timezone.utc).isoformat()
    (out / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print("REGISTER_COMPARISON_PASSED", flush=True)


if __name__ == "__main__":
    main()
