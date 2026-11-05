#!/usr/bin/env bash
set -euo pipefail
cd "$SLURM_SUBMIT_DIR"
export CODERUJB_JOB_TMP
CODERUJB_JOB_TMP=$(mktemp -d /dev/shm/coderujb-cl13-XXXXXX)
trap 'rm -rf -- "$CODERUJB_JOB_TMP"' EXIT
export HF_HOME="$CODERUJB_JOB_TMP/hf"
export TMPDIR="$CODERUJB_JOB_TMP"
export PYTHONDONTWRITEBYTECODE=1 TOKENIZERS_PARALLELISM=false OMP_NUM_THREADS=8
hostname
nvidia-smi --query-gpu=name,uuid,memory.total,memory.free --format=csv
/home/hibouwu/gpuresearch/vpsr-gpu/.venv/bin/python -u generate.py
