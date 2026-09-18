[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/bViEsdsg)

# Lab6 - AI Project (1) SGEMM Kernel Optimization

This repository documents the SGEMM optimization lab: from baseline implementation through multiple optimizations, testing, and analysis. Follow the steps below for day-to-day usage.

---

## 1. Environment & Build
- Initial configuration:
  ```bash
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
  ```
- To disable OpenMP support, add `-DENABLE_OPENMP=OFF` during configuration.
- Build targets:
  ```bash
  cmake --build build          # 默认 Release/Debug 由首次配置决定
  cmake --build build --target test_runner
  ```
- If OpenBLAS is not installed, set `-DENABLE_OPENBLAS=OFF`; otherwise specify `-DOpenBLAS_DIR=<path>`.
- To get O3 / vectorization reports:
  ```bash
  cmake -S . -B build-o3 -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_C_FLAGS="-O3 -march=native -fopt-info-vec-optimized"
  cmake --build build-o3 --clean-first
  ```

---

## 2. Running SGEMM
- Executable: `./build/sgemm <version> <M> <N> <K>`
- Supported versions:
  - `naive`: triple loop (i, j, k)
  - `ikj`: loop reordering to improve cache locality
  - `blocked`: tiled kernel (default tile 128×128)
  - `omp`: OpenMP parallel version (`_OPENMP` must be enabled)
  - `blas`: OpenBLAS `cblas_sgemm` wrapper (falls back to naive if BLAS missing)
- Examples:
  ```bash
  ./build/sgemm naive 256 256 256
  ./build/sgemm ikj   1024 512 512
  ./build/sgemm blocked  768 512 512
  ./build/sgemm omp      2048 512 512
  ./build/sgemm blas 256 256 256
  ```

---

## 3. Unit Tests
- Build:
  ```bash
  cmake --build build --target test_runner
  ```
- Run:
  ```bash
  ./build/test_runner
  ```
- Coverage:
  - Baseline SGEMM correctness on multiple sizes
  - Random matrix reproducibility
  - `sgemm_ikj`, `sgemm_blocked`, `sgemm_omp` vs baseline
  - `sgemm_blas` vs baseline (skipped if OpenBLAS unavailable)

---

## 4. Performance Workflow
1. **Size sweep**  
   ```bash
   cd performance
   ./compare-sizes.sh
   python3 plot-sizes.py sgemm_sizes_comparison.csv performance_naive.png
   ```
   Default run benchmarks the `naive` kernel and records time/energy.

2. **Variant comparison**  
   ```bash
   cd performance

   OUTPUT_CSV=sgemm_perf_default.csv OMP_THREADS_OVERRIDE="1 2 4 8 16" CPU_SET=0-7 ./compare-optimizations.sh

   GEMM_EXEC=../build-o3/sgemm OUTPUT_CSV=sgemm_perf_vectorized.csv OMP_THREADS_OVERRIDE="1 2 4 8 16" CPU_SET=0-7 ./compare-optimizations.sh
   python3 plot-optimizations.py --csv sgemm_optimizations_comparison.csv --out-dir . --prefix performance_optimizations
   ```
   - `plot-optimizations.py` generates dual-axis plots with inset zoom (`performance/performance_optimizations_dual_small.png` / `_dual_large.png`).

3. **Vectorization / energy checks**  
   - Use `perf stat` for `duration_time` and `power/energy-pkg/`:
     ```bash
     perf stat -r 3 -a -e duration_time,power/energy-pkg/ \
         ./build/sgemm naive 512 512 512
     ```
   - If RAPL is available, direct MSR reads can be used (see legacy examples).

4. **Cache behaviour analysis**
   - For AMD L3 PMU (requires sudo):
     ```bash
     sudo perf stat -a -e amd_l3/l3_lookup_state.all_coherent_accesses_to_l3/,amd_l3/l3_lookup_state.l3_hit/,amd_l3/l3_lookup_state.l3_miss/,L1-dcache-load-misses ./build/sgemm ikj 1280 512 512
     ```
     If running inside `performance/`, use `../build/sgemm ...`.
     ```bash
     # Pin SGEMM to a core set (e.g. 0–7) while collecting only that subset.
     sudo taskset -c 0-7 perf stat -a -C 0-7 \
     -e amd_l3/l3_lookup_state.all_coherent_accesses_to_l3/,\
     amd_l3/l3_lookup_state.l3_hit/,\
     amd_l3/l3_lookup_state.l3_miss/,\
     L1-dcache-load-misses \
     ./build/sgemm ikj 1280 512 512
     ```
   
---

## 5. Optimization roadmap
1. Baseline (`sgemm`) – completed.
2. Loop reorder (`sgemm_ikj`) – improves cache use.
3. Blocked kernel (`sgemm_blocked`) – default tile 128.
4. OpenMP (`sgemm_omp`) – ensure compilation with `-fopenmp`.
5. OpenBLAS (`sgemm_blas`) – optional external backend.
6. Further ideas: SIMD intrinsics, multi-level tiling, alternative BLAS baselines, etc.

---

## 6. TODO tracking
- `Afaire.md` keeps the live checklist. Mark items as you finish optimizing scripts, removing sudo dependencies, etc.

---

## 7. Command cheat sheet
| Scenario              | Command |
|----------------------|---------|
| Debug build          | `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug` |
| Release build        | `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release` |
| Build tests          | `cmake --build build --target test_runner` |
| Run unit tests       | `./build/test_runner` |
| Run specific kernel  | `./build/sgemm <version> M N K` |
| Batch performance    | `(cd performance && ./compare-sizes.sh)` |
| Plot results         | `(cd performance && python3 plot-sizes.py sgemm_sizes_comparison.csv output.png)` |

Add new commands or scripts to the sections above so the README stays in sync with the project state.***
