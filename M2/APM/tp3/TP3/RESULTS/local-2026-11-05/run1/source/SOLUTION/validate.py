#!/usr/bin/env python3
"""Build, validate, and retain TP3 evidence. No remote GPU or scheduler is used."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
from datetime import datetime, timezone


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler", choices=("nvcc", "clang"), default="nvcc")
    parser.add_argument("--arch", default="sm_120")
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parent.parent
    out = args.output.resolve()
    out.mkdir(parents=True, exist_ok=False)  # do not overwrite a previous run
    cuda = Path(shutil.which("nvcc")).resolve().parent.parent
    manifest = {"started_utc": datetime.now(timezone.utc).isoformat(),
                "compiler": args.compiler, "arch": args.arch, "commands": [], "sha256": {}}

    def command(label, argv, required=True):
        proc = subprocess.run([str(a) for a in argv], cwd=root / "SOLUTION",
                              text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        (out / f"{label}.log").write_text(proc.stdout)
        manifest["commands"].append({"label": label, "argv": [str(a) for a in argv],
                                     "cwd": str(root / "SOLUTION"), "exit_code": proc.returncode})
        print(f"{label}: exit={proc.returncode}", flush=True)
        if required and proc.returncode:
            (out / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
            raise RuntimeError(f"{label} failed; inspect {out / (label + '.log')}")
        return proc.stdout

    command("environment", ["nvidia-smi"])
    command("nvcc_version", [cuda / "bin/nvcc", "--version"])
    command("clang_version", ["clang++", "--version"])
    with tempfile.TemporaryDirectory(prefix="apm-tp3-") as tmp:
        exe = Path(tmp) / "dgemm_tp3.exe"
        source = root / "SOLUTION/dgemm_tp3.cu"
        nvcc_cmd = [cuda / "bin/nvcc", "-O3", "-std=c++17", "-lineinfo", "-Xptxas=-v",
                    f"-arch={args.arch}", source, "-o", exe]
        if args.compiler == "clang":
            # Preserve the ordinary nvcc failure too; do not bypass its compiler guard.
            command("nvcc_probe", nvcc_cmd, required=False)
            command("build", ["clang++", "-O3", "-std=c++17", "-gline-tables-only",
                               "--no-offload-new-driver", f"--cuda-path={cuda}",
                               f"--cuda-gpu-arch={args.arch}", f"-L{cuda / 'lib64'}",
                               f"-Wl,-rpath,{cuda / 'lib64'}", source, "-lcudart", "-o", exe])
        else:
            command("build", nvcc_cmd)
        manifest["binary_sha256"] = hashlib.sha256(exe.read_bytes()).hexdigest()
        cases = [(1, 1, 1), (31, 31, 31), (32, 32, 32), (33, 33, 33),
                 (63, 65, 37), (128, 96, 160), (256, 256, 256),
                 (1000, 1000, 1000), (1024, 1024, 1024)]
        for m, n, k in cases:
            command(f"case_{m}_{n}_{k}", [exe, m, n, k, 7])
        # Repeat only the performance cases, to expose variation between batches.
        for batch in (2, 3):
            for size in (256, 1000, 1024):
                command(f"batch{batch}_{size}", [exe, size, size, size, 7])
        for tool, case in [("memcheck", 32), ("memcheck", 33), ("racecheck", 33),
                           ("synccheck", 33), ("initcheck", 33)]:
            command(f"{tool}_{case}", [cuda / "bin/compute-sanitizer", "--tool", tool,
                                       "--error-exitcode", "99", exe, case, case, case, 1])
        for label, symbol in {
            "original": "_Z12dgemm_sharediiidPKdS0_dPd",
            "shared_safe": "_Z10dgemm_safeILi1EEviiidPKdS1_dPd",
            "tiled_tm4": "_Z10dgemm_safeILi4EEviiidPKdS1_dPd",
        }.items():
            sass = command(f"{label}_sass", [cuda / "bin/cuobjdump", "--dump-sass",
                                             "--function", symbol, exe])
            sass_path = out / f"{label}.sass"
            sass_path.write_text(sass)
            (out / f"{label}_sass.log").unlink()  # identical copy, retain the .sass
            report = command(f"{label}_counts", ["bash", root / "CODE/parse_sass.sh", sass_path])
            (out / f"{label}_counts.md").write_text(report)
            (out / f"{label}_counts.log").unlink()
            if not re.search(r"\| 1 \|", report):
                raise RuntimeError(f"No instructions parsed for {label}")
    for path in sorted(root.rglob("*")):
        if path.is_file() and "RESULTS" not in path.parts and path.suffix != ".exe":
            manifest["sha256"][str(path.relative_to(root))] = hashlib.sha256(path.read_bytes()).hexdigest()
    manifest["finished_utc"] = datetime.now(timezone.utc).isoformat()
    (out / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"Evidence retained in {out}")


if __name__ == "__main__":
    main()
