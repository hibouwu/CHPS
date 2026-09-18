# GotoBLASBlockedAVX512

Scripts for AVX-512 GotoBLAS correctness checks and staged tuning.

The tuning flow is intentionally two-stage:

1. Stage 1: fixed conservative `Kc/Mc/Nc`, compare primary kernel shapes only.
2. Stage 2: after choosing a kernel shape, sweep that shape's `Kc/Mc/Nc` candidates.

`avx512_4x32` is included only as a stress / fallback candidate. It is implementation-feasible but strict-L1-set-model-infeasible, so it should not be used for primary ranking.

## Scripts

- `run_avx512_correctness_matrix.py`
  Runs the AVX-512 driver correctness tests.

- `run_single_thread_avx512_stage1_kernel_screening.py`
  Runs stage-1 primary kernel-shape screening using `config/avx512_stage1_kernel_screening.json`.

- `run_single_thread_avx512_stage2_blocked_candidates.py`
  Runs stage-2 blocked-size candidates using `config/avx512_stage2_blocked_candidates.json`.

- `summarize_avx512_candidates.py`
  Summarizes stage-1 or stage-2 raw CSV files.

- `plot_avx512_heatmaps.py`
  Plots primary-shape heatmaps from the summary CSV files.

- `run_avx2_vs_avx512_comparison.py`
  Emits or runs a fixed AVX2-vs-AVX512 comparison protocol. Use this only after candidate selection, not during tuning.

- `run_avx512_thread_aware_mcnc_tuning.py`
  Runs the AVX-512 `avx512_8x32` fixed-`Kc=160` thread-aware `Mc/Nc` sweep.

- `summarize_avx512_thread_aware_mcnc_tuning.py`
  Aggregates the thread-aware `Mc/Nc` sweep into workload, family, overall, strict-winner, and conservative recommendation outputs.

- `plot_avx512_thread_aware_mcnc_heatmaps.py`
  Plots per-family and overall `Mc/Nc` heatmaps from the thread-aware summary files.

- `run_fixed_strong_scaling_comparison.py`
  Runs a fixed-config strong-scaling comparison across AVX2 GotoBLAS, AVX-512 GotoBLAS, and OpenBLAS.

- `summarize_fixed_strong_scaling_comparison.py`
  Aggregates fixed-config strong-scaling raw results into speedup, efficiency, relative-ratio, and winner tables.

- `plot_fixed_strong_scaling_comparison.py`
  Plots fixed-config strong-scaling summary charts.

## Typical Commands

```bash
python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_avx512_correctness_matrix.py

python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_single_thread_avx512_stage1_kernel_screening.py --skip-perf
python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/summarize_avx512_candidates.py --stage stage1
python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/plot_avx512_heatmaps.py --stage stage1

python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_single_thread_avx512_stage2_blocked_candidates.py --skip-perf
python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/summarize_avx512_candidates.py --stage stage2
python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/plot_avx512_heatmaps.py --stage stage2
```

AVX-512 thread-aware `Mc/Nc` tuning for the current default path:

```bash
cmake --build build --target test_benchmark_large -j2

python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_avx512_thread_aware_mcnc_tuning.py --quick

python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/summarize_avx512_thread_aware_mcnc_tuning.py

python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/plot_avx512_thread_aware_mcnc_heatmaps.py

python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_avx512_thread_aware_mcnc_tuning.py --full
```

The full thread-aware sweep fixes `MATMUL_IMPL=omp_gotoblas_avx512`, `MATMUL_GOTO_KERNEL=avx512_8x32`, and `MATMUL_KC=160`, then scans only `Mc/Nc` across thread counts. It does not include AVX2 comparison, does not include `avx512_16x16`, and does not reopen kernel-shape search. The current conservative multi-thread fixed scaling candidate selected from this sweep is `avx512_8x32, Kc=160, Mc=8, Nc=448`.

The runner uses longer inner repetitions by default than the first smoke version: quick mode uses `--reps 50`, and full mode uses `--reps 100`. Override this explicitly when needed, for example `--reps 200`.

Next steps after the thread-aware sweep:

```bash
# final fixed-config validation for the selected AVX-512 multi-thread candidate
MATMUL_IMPL=omp_gotoblas_avx512 \
MATMUL_GOTO_KERNEL=avx512_8x32 \
MATMUL_KC=160 \
MATMUL_MC=8 \
MATMUL_NC=448 \
./build/test_benchmark_large <M> <K> <N> <reps>

# only after AVX-512 fixed-config validation
python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_avx2_vs_avx512_comparison.py
```

Fixed-config strong-scaling comparison:

AVX2 and AVX-512 are fixed-config custom GotoBLAS paths using `MATMUL_IMPL=omp_gotoblas_avx2/avx512` and explicit `MATMUL_GOTO_KERNEL`/`MATMUL_KC`/`MATMUL_MC`/`MATMUL_NC`. OpenBLAS uses `MATMUL_IMPL=blas` and `OPENBLAS_NUM_THREADS`; GotoBLAS blocking variables are not set for the OpenBLAS case. Interpret results by workload family; do not use this experiment to claim universal superiority of any implementation.

`--quick` is a smoke check only (2 threads, 2 workloads, 50 reps). It verifies the pipeline but is not an experimental conclusion. Use `--full` for any formal comparison.

Three workload sets are available:
- `minimal` — 5 synthetic workloads covering the main GEMM families (default)
- `full` — 10 workloads with larger shapes and square references
- `training-trace` — 7 workloads derived from actual MATMUL_TRACE_SHAPES=1 runs on CNN+MLP training; see `Docs/report/ActualTrainingGemmFamilies.md`

**Note on transposed shapes in training-trace:** the custom AVX2/AVX-512 implementations only handle non-transposed GEMMs. Transposed training calls (Conv dW, FC dW) fall back to the scalar loop in production; the benchmark measures non-transposed throughput for the same M/K/N dimensions. Do not interpret training-trace benchmark results as representative of the complete training FLOP budget.

```bash
# 0. build
cmake --build build --target test_benchmark_large -j2

# 1. quick smoke (pipeline verification only — not a conclusion)
python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_fixed_strong_scaling_comparison.py --quick --workload-set minimal

python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/summarize_fixed_strong_scaling_comparison.py

python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/plot_fixed_strong_scaling_comparison.py

# 2. full minimal (4 workloads, 4 thread counts, 3 samples)
python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_fixed_strong_scaling_comparison.py --full --workload-set minimal

# 3. full extended workload set
python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_fixed_strong_scaling_comparison.py --full --workload-set full

# 4. training-trace workload set (real shapes from CNN+MLP training)
python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_fixed_strong_scaling_comparison.py --full --workload-set training-trace
```

To collect a fresh shape trace before running the training-trace set:
```bash
cmake --build build --target ppn_train -j2

MATMUL_TRACE_SHAPES=1 \
MATMUL_TRACE_SHAPES_FILE=output/ExperienceGEMM/GotoBLASBlockedAVX512/training_shape_trace/cnn_shapes.csv \
MATMUL_IMPL=blas \
./build/ppn_train cnn mnist/ 32 1

python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/summarize_training_gemm_shapes.py \
  --input output/ExperienceGEMM/GotoBLASBlockedAVX512/training_shape_trace/cnn_shapes.csv \
  --output-dir output/ExperienceGEMM/GotoBLASBlockedAVX512/training_shape_trace/summary/cnn
```

For smoke checks without running benchmarks:

```bash
python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_single_thread_avx512_stage1_kernel_screening.py --dry-run --limit-candidates 2 --limit-workloads 1
python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_single_thread_avx512_stage2_blocked_candidates.py --dry-run --limit-candidates 2 --limit-workloads 1
python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_avx2_vs_avx512_comparison.py --dry-run

# 0. build
cmake --build build --target test_gemm_gotoblas_driver test_benchmark_large -j2

# 1. lock frequency policy on cores 0-7 if permitted
for c in 0 1 2 3 4 5 6 7; do
  if [ -w /sys/devices/system/cpu/cpu${c}/cpufreq/scaling_governor ]; then
    echo performance | sudo tee /sys/devices/system/cpu/cpu${c}/cpufreq/scaling_governor >/dev/null
  fi
done

# 2. common thread / affinity env
export OMP_NUM_THREADS=1
export OPENBLAS_NUM_THREADS=1
export GOTO_NUM_THREADS=1
export BLIS_NUM_THREADS=1
export MKL_NUM_THREADS=1
export OMP_PROC_BIND=true
export OMP_PLACES=cores

# 3. correctness
sudo taskset -c 0 python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_avx512_correctness_matrix.py

# 4. stage 1: kernel-shape screening
sudo taskset -c 0 python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_single_thread_avx512_stage1_kernel_screening.py

python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/summarize_avx512_candidates.py --stage stage1

python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/plot_avx512_heatmaps.py --stage stage1

# 5. stage 2: blocked-size candidates
sudo taskset -c 0 python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/run_single_thread_avx512_stage2_blocked_candidates.py

python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/summarize_avx512_candidates.py --stage stage2

python3 scripts/ExperienceGEMM/GotoBLASBlockedAVX512/plot_avx512_heatmaps.py --stage stage2

```
