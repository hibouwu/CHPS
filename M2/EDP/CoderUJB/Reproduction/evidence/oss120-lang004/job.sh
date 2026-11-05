#!/bin/bash
set -euo pipefail
cd "$SLURM_SUBMIT_DIR"
module load cuda/12.6
t=$(mktemp -d /dev/shm/oss120-XXXXXX)
export WEIGHTS="$t/model.gguf"
cleanup() {
 if [[ -n "${server_pid:-}" ]]; then kill "$server_pid" 2>/dev/null || true; fi
 rm -rf -- "$t"
}
trap cleanup EXIT
hostname
nvidia-smi --query-gpu=name,memory.total,memory.free --format=csv
python3 stage.py > stage.log 2>&1 &
stage_pid=$!
rev=$(python3 -c "import json;print(json.load(open('manifest.json'))['llama_cpp_commit'])")
mkdir -p src
curl -fsSL --retry 3 "https://codeload.github.com/ggml-org/llama.cpp/tar.gz/$rev" | tar -xz --strip-components=1 -C src
cmake -S src -B build -DGGML_CUDA=ON -DCMAKE_CUDA_ARCHITECTURES=90 -DGGML_NATIVE=OFF -DLLAMA_CURL=OFF -DLLAMA_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release > configure.log 2>&1
cmake --build build -j "$SLURM_CPUS_PER_TASK" --target llama-server > build.log 2>&1
wait "$stage_pid"
port=$((20000 + SLURM_JOB_ID % 30000))
export PORT=$port
build/bin/llama-server -m "$WEIGHTS" -ngl 99 -c 8192 -np 1 --jinja --host 127.0.0.1 --port "$port" >server.log 2>&1 &
server_pid=$!
python3 infer.py "$server_pid"
