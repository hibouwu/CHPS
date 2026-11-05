#!/usr/bin/env bash
# Execute only within a fresh, single-GPU Slurm allocation.
set -eo pipefail
: "${SLURM_JOB_ID:?Submit this script with sbatch on ROMEO}"
# Slurm executes a spooled copy of this file; $0 is not the source location.
cd "${SLURM_SUBMIT_DIR}/TP3/SOLUTION"
source /apps/2025/manual_install/spack-armgpu-1.0.x/share/spack/setup-env.sh
spack load cuda@12.9.0
set -u
export OMP_NUM_THREADS=1
export TMPDIR="${SLURM_SUBMIT_DIR}/tmp-${SLURM_JOB_ID}"
export TMP="$TMPDIR" TEMP="$TMPDIR"
mkdir -p "$TMPDIR"
out="$(realpath ..)/RESULTS/romeo-${SLURM_JOB_ID}"
mkdir -p "$(dirname "$out")"
date --iso-8601=seconds
hostname
uname -m
df -h "$TMPDIR"
df -i "$TMPDIR"
scontrol show job "$SLURM_JOB_ID"
python3 validate.py --compiler nvcc --arch sm_90 --output "$out"
# Larger matrices make the block tiling comparison more useful on a GH200.
for batch in 1 2 3; do
    for n in 2048 4096; do
        "$out/dgemm_tp3.exe" "$n" "$n" "$n" 7 > "$out/large_batch${batch}_${n}.log"
    done
done
cuobjdump --dump-resource-usage "$out/dgemm_tp3.exe" > "$out/resource_usage.txt"
sha256sum "$out/dgemm_tp3.exe"
printf 'ALL_CHECKS_PASSED\n'
