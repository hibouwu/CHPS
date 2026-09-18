# Blocked-series GEMM 参数筛选脚本

本目录实现了 `Turning_omp_BlockSize_Packsize.md` 中定义的 planned protocol。

## 目录结构

```
scripts/ExperienceGEMM/Blocked/
  common.sh                          # 公共 helper（env 设置、build、_run_bench_core）
  summarize.py                       # 聚合 results.csv → summary CSV + rank
  omp_blocked/
    screening_small.sh               # 第一轮筛选（矩阵 64–512）
    rescreen_large.sh                # 第二轮复测（矩阵 1024–2048），读候选列表
  omp_blocked_packb/
    screening_small.sh
    rescreen_large.sh
  omp_blocked_packab/
    gen_feasible_candidates.py       # 生成满足 L1 footprint 约束的 (Mc,Nc,Kc) 组合
    screening_small.sh
    rescreen_large.sh

output/ExperienceGEMM/Blocked/
  omp_blocked/{screening_small,rescreen_large,summary}/
  omp_blocked_packb/{screening_small,rescreen_large,summary}/
  omp_blocked_packab/{screening_small,rescreen_large,summary}/
```

## 脚本说明

| 脚本 | 作用 |
|---|---|
| `common.sh` | `setup_env` / `restore_env` / `build_bench` / `_run_bench_core` |
| `omp_blocked/screening_small.sh` | BlockSize ∈ {16,32,48,64,128,256} × sizes × threads |
| `omp_blocked/rescreen_large.sh` | 读 candidates CSV → 大矩阵复测 |
| `omp_blocked_packb/screening_small.sh` | BlockSize ∈ {16,32,48} × sizes × threads |
| `omp_blocked_packb/rescreen_large.sh` | 读 candidates CSV → 大矩阵复测 |
| `omp_blocked_packab/gen_feasible_candidates.py` | 生成 38 个可行 (Mc,Nc,Kc) 组合 |
| `omp_blocked_packab/screening_small.sh` | 38 组合 × sizes × threads |
| `omp_blocked_packab/rescreen_large.sh` | 读 candidates CSV（pack_m,pack_n,pack_k 列）→ 大矩阵复测 |
| `summarize.py` | 读 results.csv，按 (size,threads) 排名，输出 summary CSV |
| `select_candidates.py` | 从 screening_small summary 自动选出 top-N 候选，写入 rescreen_large/candidates.csv |

## 完整两轮流程（全自动）

> 所有命令从仓库根目录运行，需要 `sudo` 用于 `cpupower` 锁频。

### 第一步：第一轮筛选

```bash
# 锁频、绑核 0-7 已由脚本内部处理（cpupower + taskset）
bash scripts/ExperienceGEMM/Blocked/omp_blocked/screening_small.sh
bash scripts/ExperienceGEMM/Blocked/omp_blocked_packb/screening_small.sh
bash scripts/ExperienceGEMM/Blocked/omp_blocked_packab/screening_small.sh
```

覆盖默认参数：

```bash
REPS=1000 CORE_RANGE=0-7 FREQ_TARGET=4000MHz \
  bash scripts/ExperienceGEMM/Blocked/omp_blocked/screening_small.sh
```

### 第二步：生成第一轮聚合摘要

```bash
python3 scripts/ExperienceGEMM/Blocked/summarize.py all --phase screening_small
```

输出到 `output/ExperienceGEMM/Blocked/<impl>/summary/screening_small_summary.csv`。

### 第三步：自动选出第二轮候选

```bash
# 默认 top-3，以 size=512（最大筛选规模）各线程数的平均时间排名
python3 scripts/ExperienceGEMM/Blocked/select_candidates.py all

# 调整候选数（packab 参数空间更大，可适当多取）
python3 scripts/ExperienceGEMM/Blocked/select_candidates.py omp_blocked_packab --top-n 5

# 指定参考规模（默认为数据中最大的 size）
python3 scripts/ExperienceGEMM/Blocked/select_candidates.py omp_blocked --top-n 3 --ref-size 512
```

选出的候选自动写入：

- `output/ExperienceGEMM/Blocked/omp_blocked/rescreen_large/candidates.csv`
- `output/ExperienceGEMM/Blocked/omp_blocked_packb/rescreen_large/candidates.csv`
- `output/ExperienceGEMM/Blocked/omp_blocked_packab/rescreen_large/candidates.csv`

### 第四步：第二轮复测

```bash
# 无参数时自动读取上一步生成的 candidates.csv
bash scripts/ExperienceGEMM/Blocked/omp_blocked/rescreen_large.sh
bash scripts/ExperienceGEMM/Blocked/omp_blocked_packb/rescreen_large.sh
bash scripts/ExperienceGEMM/Blocked/omp_blocked_packab/rescreen_large.sh
```

也可手动指定候选文件：

```bash
bash scripts/ExperienceGEMM/Blocked/omp_blocked/rescreen_large.sh /path/to/my_candidates.csv
```

### 第五步：生成复测摘要

```bash
python3 scripts/ExperienceGEMM/Blocked/summarize.py all --phase rescreen_large
```

## 环境变量

| 变量 | 默认值 | 说明 |
|---|---|---|
| `REPS` | 1000 | benchmark 重复次数 |
| `FREQ_TARGET` | `4000MHz` | cpupower 锁频目标 |
| `CORE_RANGE` | `0-7` | taskset 绑核范围 |
| `ENABLE_PERF` | `false` | 是否采集 perf 计数器 |
| `WARMUP_RUNS` | 0 | 每个测点正式测量前的预热次数；预热结果不写入 CSV |
| `EMIT_EFFECTIVE_CONFIG` | `false` | 设为 `true` 时在每次 benchmark 前设置 `MATMUL_EMIT_EFFECTIVE_CONFIG=1`，让 binary 打印实际生效的 impl 名和参数（用于 sanity check） |

OMP/BLAS 环境由脚本统一设置，不需要手动指定：
- `OMP_DYNAMIC=false`
- `OMP_PROC_BIND=true`
- `OMP_PLACES=cores`
- `OPENBLAS_NUM_THREADS=1`
- `MKL_NUM_THREADS=1`

## 冲突说明

- 旧脚本 `benchmark_omp_blocked_packed_block_sizes.sh` 使用了错误的实现名
  `omp_blocked_packed`，本协议不使用该名字，统一用 `omp_blocked_packb`。
- 旧脚本的矩阵规模（包含 1536）和线程数（包含 16）与 protocol 不同，
  本脚本严格按 protocol 执行，不继承旧脚本的设置。

## 候选选取标准说明

`select_candidates.py` 的选取依据是 `screening_small_aggregates.csv` 中
`mean_time_us_across_threads` 列，即在参考规模（默认最大 size，通常为 512）下，
对每个 param_tuple 跨所有线程数的 `time_us` 取均值，再按该均值升序选 top-N。

这一标准假设各线程数的性能具有同等重要性。如果后续报告更关注固定线程数
（例如仅关注 threads=8 时的延迟），需要直接查阅 `screening_small_summary.csv`
并按 `(size=512, threads=8)` 分组过滤，不要直接依赖当前的 aggregates 结果。

## 尚未实现的部分

- **可视化脚本**：summary CSV 写出后的 heatmap / bar chart 绘图脚本
  （protocol 文档中提到 `heatmap_packk_32.png` 等，但未在本 planned protocol 中定义具体规格）。
