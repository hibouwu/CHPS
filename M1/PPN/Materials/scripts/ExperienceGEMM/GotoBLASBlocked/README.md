# GotoBLASBlocked Single-Thread Screening

This directory contains the minimal executable toolchain for the single-thread blocked-size screening described in `Docs/report/BlockedSizeCherche.md` section `5.4`.

## Files

- `config/single_thread_blocked_candidates.json`: workload set, `(m_r,n_r,k_c)` rows, per-row `(m_c,n_c)` candidates, and execution protocol.
- `config/single_thread_blocked_candidates_round2_refinement.json`: second-round refinement config that keeps the same workload set and single-thread protocol, but restricts the search to the five retained `KernelShape/Kc` rows and denser local `Mc/Nc` grids.
- `run_single_thread_blocked_candidates.py`: runs the custom `omp_gotoblas_avx2` path with `1000` timing samples and `5` `perf stat` samples per candidate.
- `run_single_thread_blocked_candidates_round2_refinement.py`: thin wrapper around the round-1 custom runner with round2 defaults for config and output paths.
- `run_single_thread_openblas_baseline.py`: runs the single-thread OpenBLAS baseline with `1000` timing samples on the same workload set.
- `run_single_thread_openblas_baseline_round2_refinement.py`: thin wrapper around the round-1 OpenBLAS baseline runner with round2 defaults for config and output paths.
- `summarize_single_thread_blocked_results.py`: produces aggregate candidate tables, row winners, cross-row comparison, and a markdown summary.
- `summarize_single_thread_blocked_results_round2_refinement.py`: thin wrapper around the round-1 summarizer with round2 raw/summary directories and a round2 summary title.
- `plot_single_thread_blocked_heatmaps.py`: renders the kernel-shape selection heatmap from the summary CSV files under `output/ExperienceGEMM/GotoBLASBlocked/summary/`.
- `plot_single_thread_blocked_heatmaps_round2_refinement.py`: thin wrapper around the round-1 plotting script with round2 summary/plot directories and a round2-specific title and filename.

## Build

Compile the benchmark binary first:

```bash
cmake --build build --target test_benchmark_large -j
```

## Run The Custom Candidate Sweep

```bash
python3 scripts/ExperienceGEMM/GotoBLASBlocked/run_single_thread_blocked_candidates.py
```

The runner enforces:

- `OMP_NUM_THREADS=1`
- `OPENBLAS_NUM_THREADS=1`
- `GOTO_NUM_THREADS=1`
- `BLIS_NUM_THREADS=1`
- `MKL_NUM_THREADS=1`
- single-core pinning through `taskset` when available
- frequency policy control through the configured governor policy; the default configuration attempts to switch the pinned core to `performance` before the run and restores the original governor afterwards

Timing and `perf stat` are executed separately. Failures do not abort the batch; they are written to the raw CSV with `Status=failed` or `Status=unsupported_kernel_shape`. By default the raw CSV is overwritten at the start of the run; pass `--append` only when you intentionally want to accumulate additional samples into an existing raw file.

For the custom `omp_gotoblas_avx2` runs, the benchmark binary also emits the effective runtime configuration. The raw CSV therefore keeps both the requested values (`RequestedKernelShape`, `RequestedMc`, `RequestedNc`, `RequestedKc`) and the values actually consumed by the GotoBLAS path (`KernelShape`, `Mc`, `Nc`, `Kc`). Aggregate tables and heatmaps are grouped by the effective values.

## Run The OpenBLAS Baseline

```bash
python3 scripts/ExperienceGEMM/GotoBLASBlocked/run_single_thread_openblas_baseline.py
```

The baseline uses the same workload set, the same single-thread pinning policy, the same governor policy, and the same raw CSV schema. It participates only in cross-row comparison. Its raw CSV is also overwritten by default; use `--append` only for an intentional continuation run.

## Summarize Results

```bash
python3 scripts/ExperienceGEMM/GotoBLASBlocked/summarize_single_thread_blocked_results.py
```

## Plot Heatmaps

```bash
python3 scripts/ExperienceGEMM/GotoBLASBlocked/plot_single_thread_blocked_heatmaps.py
```

By default the script writes:

- `output/ExperienceGEMM/GotoBLASBlocked/summary/plots/relative_to_best_custom_heatmap.png`

Outputs are written under:

- `output/ExperienceGEMM/GotoBLASBlocked/raw/`
- `output/ExperienceGEMM/GotoBLASBlocked/summary/`

The summarizer emits:

- `candidate_aggregates.csv`
- `row_winners.csv`
- `cross_row_summary.csv`
- `summary.md`

## Important Current Limitation

The configuration preserves the full candidate rows from the document, including kernel shapes that are not yet wired into the current binary. The runtime path now exposes `MATMUL_GOTO_KERNEL` together with `MATMUL_MC/NC/KC`, but only a subset of the documented AVX2 shapes are implemented today. Consequently:

- `KernelShape=8x8`, `12x8`, `13x8`, `4x16`, `5x16`, and `6x16` rows are executable today.

This keeps the candidate manifest aligned with the document while avoiding false execution claims.

## Round 2 Refinement

The second-round experiment is a **single-thread local refinement**, not a fresh global search. It keeps the same representative workload set, the same single-thread pinning/governor/timing/perf protocol, and the same requested/effective CSV schema as round 1. Its purpose is narrower: it only fills in intermediate `Mc/Nc` points around the first-round winning regions.

Round 2 retains only five `KernelShape/Kc` rows:

- `8x8`, `Kc=288`
- `8x8`, `Kc=384`
- `4x16`, `Kc=192`
- `4x16`, `Kc=256`
- `4x16`, `Kc=320`

The round2 config expands these five rows into a total of `75` `(KernelShape, Kc, Mc, Nc)` combinations by taking Cartesian products of the row-local `Mc` and `Nc` candidate lists. It does **not** reopen the dropped round-1 shapes, and it does **not** change the workload set or thread protocol.

Round 2 custom sweep:

```bash
python3 scripts/ExperienceGEMM/GotoBLASBlocked/run_single_thread_blocked_candidates_round2_refinement.py
```

Round 2 OpenBLAS baseline:

```bash
python3 scripts/ExperienceGEMM/GotoBLASBlocked/run_single_thread_openblas_baseline_round2_refinement.py
```

Round 2 summarization:

```bash
python3 scripts/ExperienceGEMM/GotoBLASBlocked/summarize_single_thread_blocked_results_round2_refinement.py
```

Round 2 plotting:

```bash
python3 scripts/ExperienceGEMM/GotoBLASBlocked/plot_single_thread_blocked_heatmaps_round2_refinement.py
```

The round2 heatmap is intentionally restricted to the two retained round2 shapes, `8x8` and `4x16`, rather than the full first-round shape set.

Round 2 outputs are kept separate from round 1:

- raw: `output/ExperienceGEMM/GotoBLASBlocked/round2_refinement/raw/`
- summary: `output/ExperienceGEMM/GotoBLASBlocked/round2_refinement/summary/`

After summarization, the main round2 files to inspect are:

- `candidate_aggregates.csv`
- `row_winners.csv`
- `cross_row_summary.csv`
- `summary.md`
- `plots/round2_refinement_relative_to_best_custom_heatmap.png`

Round 2 grouping and comparison still operate on the runtime-effective `KernelShape/Mc/Nc/Kc` fields, not on nominal request labels. Its conclusions only strengthen the evidence for **single-thread blocked-size selection** under the current `omp_gotoblas_avx2` path; they do not by themselves establish a multi-thread final blocked-size conclusion.
