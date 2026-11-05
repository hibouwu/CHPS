#!/usr/bin/env bash
set -euo pipefail
probe_directory="$(cd "$(dirname "$0")" && pwd)"
export CODERUJB_JOB_TMP
CODERUJB_JOB_TMP="$(mktemp -d "/dev/shm/coderujb-${SLURM_JOB_ID}-XXXXXX")"
cleanup() {
    rm -rf -- "$CODERUJB_JOB_TMP"
}
trap cleanup EXIT
export TMPDIR="$CODERUJB_JOB_TMP"
export TMP="$TMPDIR"
export TEMP="$TMPDIR"
export HF_HOME="$TMPDIR/hf-cache"
export PYTHONDONTWRITEBYTECODE=1
export TOKENIZERS_PARALLELISM=false
export OMP_NUM_THREADS=8
hostname
printenv SLURM_JOB_ID SLURM_JOB_NODELIST SLURM_MEM_PER_NODE
df -h "$TMPDIR"
/home/hibouwu/gpuresearch/vpsr-gpu/.venv/bin/python -u "$probe_directory/probe.py" "$probe_directory"
