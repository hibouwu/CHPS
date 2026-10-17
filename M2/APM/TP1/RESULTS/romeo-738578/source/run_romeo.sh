#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
: "${SLURM_JOB_ID:?Run this script inside a Slurm GPU allocation}"
source /apps/2025/manual_install/spack-armgpu-1.0.x/share/spack/setup-env.sh
spack load cuda@12.9.0
run_dir="../RESULTS/romeo-${SLURM_JOB_ID}"
mkdir -p "$run_dir/CUDAIMG" "$run_dir/bin"
run_dir=$(realpath "$run_dir")
exec > >(tee "$run_dir/run.log") 2>&1
export OMP_NUM_THREADS=1
date --iso-8601=seconds
hostname
uname -m
printf 'SLURM_JOB_ID=%s\n' "$SLURM_JOB_ID"
printf 'CPU affinity: '
taskset -pc $$
lscpu
nvidia-smi
nvidia-smi --query-gpu=name,uuid,driver_version --format=csv
nvcc --version
g++ --version
sha256sum Partie1/tp1_check.cu Partie2/dgemm.c Partie2/dgemm.cu run_romeo.sh > "$run_dir/source.sha256"

set -x
# Save both PTX and cubin from the actual GH200 compilation.
nvcc -O3 -arch=sm_90 --keep --keep-dir "$run_dir/CUDAIMG" \
    -c Partie1/tp1_check.cu -o "$run_dir/bin/tp1_check.o"
nvcc "$run_dir/bin/tp1_check.o" -o "$run_dir/bin/tp1_check"
"$run_dir/bin/tp1_check"
ls -l "$run_dir/CUDAIMG"
cat "$run_dir/CUDAIMG/tp1_check.ptx"
nvcc -std=c++17 -O3 -arch=sm_90 -Xcompiler=-Wall,-Wextra \
    Partie2/dgemm.cu -o "$run_dir/bin/dgemm"
cuobjdump --dump-resource-usage "$run_dir/bin/dgemm"
for n in 1 31 32 33 65; do
    "$run_dir/bin/dgemm" "$n" 2 general
done
compute-sanitizer --tool memcheck --error-exitcode 99 "$run_dir/bin/dgemm" 33 1 general
for n in 256 512 1024; do
    "$run_dir/bin/dgemm" "$n" 5
done
set +x
printf 'ALL_CHECKS_PASSED\n'
