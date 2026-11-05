#!/bin/bash
set -eo pipefail
cd "/scratch_p/hibouwu/coursework/apm-fw-q5-20261105T144005Z"
mkdir -p tmp
export TMPDIR="$PWD/tmp" TMP="$PWD/tmp" TEMP="$PWD/tmp"
source /apps/2025/manual_install/spack-armgpu-1.0.x/share/spack/setup-env.sh
spack load cuda@12.9.0
hostname
nvidia-smi --query-gpu=name,driver_version --format=csv
nvcc --version
nvcc -O3 -std=c++17 -arch=sm_90 -lineinfo fw_gpu.cu -o fw_gpu 2>&1 | tee build.log
./fw_gpu 2>&1 | tee example.log
for n in 8 64 512 1024 2048 33; do
 ./fw_gpu -n "$n" 2>&1 | tee "n${n}.log"
done
compute-sanitizer --tool memcheck --error-exitcode 99 ./fw_gpu -n 33 2>&1 | tee memcheck.log
sha256sum fw_gpu.cu fw.c fw_utils.h cuda_utils.h fw_gpu *.log > SHA256SUMS
