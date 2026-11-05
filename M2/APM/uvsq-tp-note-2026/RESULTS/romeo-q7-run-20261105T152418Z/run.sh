#!/bin/bash
set -eo pipefail
cd "/scratch_p/hibouwu/coursework/apm-fw-q7-run-20261105T152418Z"
mkdir -p tmp
export TMPDIR="$PWD/tmp" TMP="$PWD/tmp" TEMP="$PWD/tmp"
source /apps/2025/manual_install/spack-armgpu-1.0.x/share/spack/setup-env.sh
spack load cuda@12.9.0
hostname
nvidia-smi --query-gpu=name,driver_version --format=csv
nvcc --version
nvcc -O3 -std=c++17 -arch=sm_90 -lineinfo fw_gpu.cu -o fw_coalesced 2>&1 | tee build_coalesced.log
nvcc -O3 -std=c++17 -arch=sm_90 -lineinfo -DSTRIDED fw_gpu.cu -o fw_strided 2>&1 | tee build_strided.log
for variant in coalesced strided; do
 for n in 33 512 4096; do
  ./fw_$variant -n "$n" 2>&1 | tee "${variant}_n${n}.log"
 done
 compute-sanitizer --tool memcheck --error-exitcode 99 ./fw_$variant -n 33 2>&1 | tee "${variant}_memcheck.log"
done
sha256sum fw_gpu.cu fw.c fw_utils.h cuda_utils.h fw_coalesced fw_strided build*.log coalesced*.log strided*.log > SHA256SUMS
