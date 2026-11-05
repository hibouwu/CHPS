#!/usr/bin/env bash
set -eo pipefail
: "${SLURM_JOB_ID:?Run inside a Slurm GPU allocation}"
: "${APM_TP3_STAGE:?Export the uploaded TP3 parent directory}"
cd "${APM_TP3_STAGE}/TP3/SOLUTION"
source /apps/2025/manual_install/spack-armgpu-1.0.x/share/spack/setup-env.sh
spack load cuda@12.9.0
set -u
export OMP_NUM_THREADS=1
export TMPDIR="${APM_TP3_STAGE}/tmp-${SLURM_JOB_ID}"
export TMP="$TMPDIR" TEMP="$TMPDIR"
mkdir -p "$TMPDIR"
date --iso-8601=seconds
hostname
uname -m
df -h "$TMPDIR"
df -i "$TMPDIR"
scontrol show job "$SLURM_JOB_ID"
python3 compare_teacher_layouts.py --output "$(realpath ..)/RESULTS/romeo-${SLURM_JOB_ID}"
printf 'ALL_CHECKS_PASSED\n'
