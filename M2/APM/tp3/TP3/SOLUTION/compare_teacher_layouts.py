#!/usr/bin/env python3
"""Check the teacher's 1024-thread occupancy with matching 1D and 2D indexing."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parent.parent
    out = args.output.resolve()
    out.mkdir(parents=True, exist_ok=False)
    nvcc = Path(shutil.which("nvcc")).resolve()
    manifest = {"job_id": os.environ.get("SLURM_JOB_ID"), "node": os.uname().nodename,
                "started_utc": datetime.now(timezone.utc).isoformat(),
                "commands": [], "sha256": {},
                "layouts": {"1d": [1024, 1, 1], "2d": [32, 32, 1]}}
    for directory in ("CODE", "SOLUTION"):
        for p in sorted((root / directory).rglob("*")):
            if p.is_file() and p.suffix not in (".exe", ".sass", ".pyc"):
                target = out / "source" / p.relative_to(root)
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(p, target)

    def command(label, argv):
        proc = subprocess.run([str(x) for x in argv], cwd=root / "SOLUTION", text=True,
                              stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        (out / f"{label}.log").write_text(proc.stdout)
        manifest["commands"].append({"label": label, "argv": [str(x) for x in argv],
                                     "exit_code": proc.returncode})
        (out / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
        print(f"{label}: exit={proc.returncode}", flush=True)
        if proc.returncode:
            raise RuntimeError(f"{label} failed")
        return proc.stdout

    source = (root / "SOLUTION/dgemm_tp3.cu").read_text()
    teacher = (root / "CODE/dgemm-shared.cu").read_text()
    variant = out / "variant_2d"
    variant.mkdir()
    old_index = "const uint threadRow = threadIdx.x / BLOCKSIZE;\n  const uint threadCol = threadIdx.x % BLOCKSIZE;"
    new_index = "const uint threadRow = threadIdx.y;\n  const uint threadCol = threadIdx.x;"
    assert teacher.count(old_index) == 1
    (variant / "teacher_2d.cu").write_text(teacher.replace(old_index, new_index))
    old_launch = "dim3(threads), args, dynamic, nullptr)"
    new_launch = "(kernel == (const void*)dgemm_shared ? dim3(32, 32) : dim3(threads)), args, dynamic, nullptr)"
    assert source.count(old_launch) == 1
    source = source.replace('#include "../CODE/dgemm-shared.cu"', '#include "teacher_2d.cu"')
    source = source.replace(old_launch, new_launch)
    main_decl = "int main(int argc, char** argv) {"
    assert source.count(main_decl) == 1
    source = source.replace(main_decl, main_decl + '\n    printf("TEACHER_LAYOUT x=32 y=32 z=1 total_threads=1024\\n");')
    (variant / "dgemm_tp3_2d.cu").write_text(source)
    command("environment", ["nvidia-smi"])
    command("nvcc_version", [nvcc, "--version"])
    command("host_compiler_version", ["g++", "--version"])
    for layout, input_file in (("1d", root / "SOLUTION/dgemm_tp3.cu"),
                                ("2d", variant / "dgemm_tp3_2d.cu")):
        binary = out / f"teacher_{layout}.exe"
        command(f"build_{layout}", [nvcc, "-O3", "-std=c++17", "-lineinfo", "-Xptxas=-v",
                                   "-arch=sm_90", input_file, "-o", binary])
        for n in (32, 64, 1024):
            command(f"check_{layout}_{n}", [binary, n, n, n, 1])
        for tool in ("memcheck", "racecheck"):
            command(f"{tool}_{layout}", [nvcc.parent / "compute-sanitizer", "--tool", tool,
                                         "--error-exitcode", "99", binary, 32, 32, 32, 1])
    for path in sorted(out.rglob("*")):
        if path.is_file() and ("source" in path.relative_to(out).parts or
                               "variant_2d" in path.relative_to(out).parts or path.suffix == ".exe"):
            manifest["sha256"][str(path.relative_to(out))] = hashlib.sha256(path.read_bytes()).hexdigest()
    manifest["finished_utc"] = datetime.now(timezone.utc).isoformat()
    (out / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print("TEACHER_LAYOUT_COMPARISON_PASSED", flush=True)


if __name__ == "__main__":
    main()
