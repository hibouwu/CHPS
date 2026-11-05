#!/bin/bash
set -euo pipefail
cd "$SLURM_SUBMIT_DIR"
module load cuda/12.6
t=$(mktemp -d /dev/shm/oss120-pilot-XXXXXX)
export WEIGHTS="$t/model.gguf"
cleanup() {
    if [[ -n "${server_pid:-}" ]]; then kill "$server_pid" 2>/dev/null || true; fi
    rm -rf -- "$t"
}
trap cleanup EXIT
hostname
nvidia-smi --query-gpu=name,uuid,memory.total,memory.free --format=csv
bin=/scratch_p/hibouwu/coderujb/oss120-20261105-v1/build/bin/llama-server
echo "7d26b05d045cd70e65489c70daee3fe8c1ff02ae8ee7f8b95d3ca33c20241bc1  $bin" | sha256sum -c -
python3 stage.py > stage.log 2>&1
export PORT=$((20000 + SLURM_JOB_ID % 30000))
"$bin" -m "$WEIGHTS" -ngl 99 -c 16384 -np 1 --jinja --host 127.0.0.1 --port "$PORT" >server.log 2>&1 &
server_pid=$!
python3 -u infer.py "$server_pid"
