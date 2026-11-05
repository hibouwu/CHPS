# TP3 本机验证记录 — 2026-11-05

[TP3 入口](../../../README.md) · [逐题解答](../../SUJET/tp3.md) · [程序](../../SOLUTION/dgemm_tp3.cu) · [复现脚本](../../SOLUTION/validate.py) · [命令、退出码与 SHA-256 清单](run1/manifest.json)

这次运行完成了 Q1–Q17 所需的资源查询、理论 occupancy 核对、SASS 分析以及一个每线程计算 4 个结果的版本。所有记录来自本机 RTX 5070 Laptop GPU，没有在 ROMEO 或 Ruche 运行。

随后另有 [ROMEO GH200 作业 817906](../romeo-817906/README.md) 完成；它与本页属于不同运行。本页原始数值与清单保持不变。旧版验证脚本及其对应源文件已补存到 [source/](run1/source/)，新版脚本增加了集群环境兼容及二进制保留。

## 环境与编译

| 项目 | 实测值 |
|---|---|
| 设备 | NVIDIA GeForce RTX 5070 Laptop GPU |
| 计算能力 / SM 数 | 12.0 / 36 |
| 驱动 / CUDA Runtime | 615.78.08 / 13.0 |
| 设备报告的 driver API 版本 | 13.4 |
| CUDA Toolkit | 13.0 |
| 编译器 / 目标 | Clang 22.1.8 / `sm_120` |
| 宿主默认 GCC | 16，超出本机 CUDA 13.0 的 nvcc 支持范围 |

证据：[设备状态](run1/environment.log)、[CUDA 版本](run1/nvcc_version.log)、[Clang 版本](run1/clang_version.log)、[运行时资源查询](run1/case_256_256_256.log)。`nvidia-smi` 显示的 CUDA 兼容版本与安装的 Toolkit 版本不同。

普通 `nvcc` 编译确实失败，[失败日志](run1/nvcc_probe.log)已保留。没有使用 `-allow-unsupported-compiler` 绕过检查。Clang 编译成功，同时发出“CUDA 版本高于其最新部分支持版本 12.9”的警告，见[编译日志](run1/build.log)。编译成功、实际 kernel 执行、正确性与 sanitizer 通过分别有独立记录。

本次使用的实际编译命令等价于：

```bash
clang++ -O3 -std=c++17 -gline-tables-only \
  --no-offload-new-driver --cuda-path=/usr/local/cuda-13.0 \
  --cuda-gpu-arch=sm_120 \
  -L/usr/local/cuda-13.0/lib64 -Wl,-rpath,/usr/local/cuda-13.0/lib64 \
  dgemm_tp3.cu -lcudart -o /tmp/dgemm_tp3.exe
```

实际临时目录名及命令参数以 `manifest.json` 为准。临时二进制在验证后自动删除，清单保留其 SHA-256；可以通过脚本重新构建，原始 SASS 与全部运行日志已留在仓库材料中。

## 资源与 occupancy

设备查询值：100 KiB 共享内存/SM，1536 threads/SM，65536 个 32-bit 寄存器/SM，24 blocks/SM，32 threads/warp。因此上限为 **48 warps/SM**。

| 版本 | 线程/block | warp/block | 寄存器/thread | 静态/动态共享内存 | 手算 blocks/SM | API blocks/SM | 理论 occupancy |
|---|---:|---:|---:|---|---:|---:|---:|
| `original_extra_smem` | 1024 | 32 | 28 | 16 / 16 KiB | 1 | 1 | 66.67% |
| `original_no_extra_smem` | 1024 | 32 | 28 | 16 / 0 KiB | 1 | 1 | 66.67% |
| `shared_safe` | 1024 | 32 | 32 | 16 / 0 KiB | 1 | 1 | 66.67% |
| `tiled_tm4` | 256 | 8 | 64 | 16 / 0 KiB | 4 | 4 | 66.67% |

课堂手算以每 warp 256 个寄存器为分配单位，并加入硬件 blocks/SM 上限与 warp 容量检查。共享内存容量比值只计用户申请，系统保留与实际分配由 API 核对；本次手算的最终驻留结果与 API 一致。所有 kernel 的 `localSizeBytes` 均为 0。这些结果属于本次编译版本，不是 GPU 上所有 kernel 的固定属性。

原始启动受线程块过大限制。优化版允许 4 块驻留，但每块只有 8 个 warp，且寄存器需求将块数限制为 4，最终 warp 数仍是 32。这里没有测量实际平均 occupancy 或发射效率。

## 正确性

所有运行均使用随位置变化、含正负数的 A/B，以及非零初始 C；`alpha=1.25`、`beta=-0.5`。CPU 参考用 `long double` 累加，比较标准为：

$$
|C_{GPU}-C_{ref}|\le10^{-10}(1+|C_{ref}|).
$$

| M × N × K | CPU 检查范围（每个执行版本） | GPU 安全基线与优化版比较 | 结果与日志 |
|---|---|---|---|
| 1 × 1 × 1 | 全量 1 个输出 | 全量 1 个 | [PASS](run1/case_1_1_1.log) |
| 31 × 31 × 31 | 全量 961 个输出 | 全量 961 个 | [PASS](run1/case_31_31_31.log) |
| 32 × 32 × 32 | 全量 1024 个输出 | 全量 1024 个 | [PASS](run1/case_32_32_32.log) |
| 33 × 33 × 33 | 全量 1089 个输出 | 全量 1089 个 | [PASS](run1/case_33_33_33.log) |
| 63 × 65 × 37 | 全量 4095 个输出 | 全量 4095 个 | [PASS](run1/case_63_65_37.log) |
| 128 × 96 × 160 | 全量 12288 个输出 | 全量 12288 个 | [PASS](run1/case_128_96_160.log) |
| 256 × 256 × 256 | 全量 65536 个输出 | 全量 65536 个 | [PASS](run1/case_256_256_256.log) |
| 1000 × 1000 × 1000 | 128 个确定性位置，包含首尾 | 全量 1000000 个 | [PASS](run1/case_1000_1000_1000.log) |
| 1024 × 1024 × 1024 | 128 个确定性位置，包含首尾 | 全量 1048576 个 | [PASS](run1/case_1024_1024_1024.log) |

CPU 检查中观察到的最大绝对误差为 **2.1649349e-14**，最大缩放误差 `abs_error/(1+abs(reference))` 为 **1.54141741e-14**。两个安全 GPU 版本在全部检查输出上最大差值为 **0**。

原始两个启动版本只在 M/N/K 均为 32 的倍数时执行；其他情况明确输出 `SKIP`。没有为“复现越界”而在原始 kernel 上运行非对齐尺寸。1000/1024 阶的 CPU 检查属于抽样，不能描述成大矩阵全量 CPU 验证；两个 GPU 版本彼此全量一致也不能替代独立 CPU 参考。

## Compute Sanitizer

使用 `--error-exitcode 99`，以下命令均退出 0。sanitizer 下的运行时间不作为性能证据。

| 检查 | 方阵尺寸 | 执行范围 | 实测摘要 |
|---|---:|---|---|
| [memcheck](run1/memcheck_32.log) | 32 | 原始两种启动、安全基线、优化版 | 0 errors |
| [memcheck](run1/memcheck_33.log) | 33 | 安全基线、优化版 | 0 errors |
| [racecheck](run1/racecheck_33.log) | 33 | 安全基线、优化版 | 0 hazards，0 errors，0 warnings |
| [synccheck](run1/synccheck_33.log) | 33 | 安全基线、优化版 | 0 errors |
| [initcheck](run1/initcheck_33.log) | 33 | 安全基线、优化版 | 0 errors |

这是代表尺寸的检查结果，没有对所有大矩阵尺寸运行 sanitizer。

## 性能

每个版本先单独执行一次供正确性检查，再进行 2 次预热、7 次采样。每次 kernel 前都把同一份初始 C 从设备副本还原，避免 `beta != 0` 时重复运行改变输入。CUDA event 仅围住一次 kernel，排除 C 重置、分配、CPU 验证以及主机与设备传输。GFLOP/s 使用主项 $2MNK$ 计算，未计 epilogue。

对 256、1000、1024 阶分别保留了 3 批数据。表中都是该批 7 次的中位数，所有原始单次样本保存在相应日志的 `SAMPLES_MS` 行。

| 阶数 | 批次 | 安全基线中位数/ms | 优化版中位数/ms | 加速比：基线/优化 | 日志 |
|---|---:|---:|---:|---:|---|
| 256 | 1 | 0.104448 | 0.100352 | 1.041× | [batch 1](run1/case_256_256_256.log) |
| 256 | 2 | 0.104448 | 0.100352 | 1.041× | [batch 2](run1/batch2_256.log) |
| 256 | 3 | 0.104480 | 0.100352 | 1.041× | [batch 3](run1/batch3_256.log) |
| 1000 | 1 | 6.337824 | 5.768192 | 1.099× | [batch 1](run1/case_1000_1000_1000.log) |
| 1000 | 2 | 6.121472 | 6.160480 | 0.994× | [batch 2](run1/batch2_1000.log) |
| 1000 | 3 | 6.181888 | 6.099936 | 1.013× | [batch 3](run1/batch3_1000.log) |
| 1024 | 1 | 6.216704 | 6.081152 | 1.022× | [batch 1](run1/case_1024_1024_1024.log) |
| 1024 | 2 | 6.609920 | 6.269856 | 1.054× | [batch 2](run1/batch2_1024.log) |
| 1024 | 3 | 6.553920 | 6.281024 | 1.043× | [batch 3](run1/batch3_1024.log) |

在本次数据中，256 阶约有 4.1% 的吞吐改善，1024 阶各批中位数改善 2.2%–5.4%；1000 阶在第 2 批略慢，不能认定稳定加速。教师原始两种启动的结果也保存在对齐尺寸日志中，不与有边界判断的安全基线混为同一个实现。

该 GPU 同时承担桌面显示任务，未锁频，版本执行顺序固定，没有随机交错或置信区间；大尺寸单次样本的变化明显。以上数据用于完成本次实验的实测比较，不作为通用性能结论，也不证明 LDS 延迟是主导瓶颈。

## SASS 静态分析

| kernel | 教师脚本计数总条数 | 数量最多 | LDS | DFMA | 报告 |
|---|---:|---|---:|---:|---|
| 教师原始 kernel | 112 | NOP：25 | 6 | 5 | [SASS](run1/original.sass) · [统计](run1/original_counts.md) |
| 安全基线 | 296 | NOP：123 | 49 | 33 | [SASS](run1/shared_safe.sass) · [统计](run1/shared_safe_counts.md) |
| 优化版 | 1192 | NOP：521 | 112 | 132 | [SASS](run1/tiled_tm4.sass) · [统计](run1/tiled_tm4_counts.md) |

每份文件只对应一个 kernel、一个 `sm_120` 目标。教师脚本原样使用，统计的是静态出现次数，会去掉指令宽度等后缀。不同循环展开程度使不同 kernel 的原始条数不能直接比较为“总工作量”；NOP 可能包含填充，静态数量第一也不表示运行时执行最多或最耗时。要回答动态执行频率，需要额外的动态测量，本次未进行。

## 复现与原始文件完整性

在 `TP3/SOLUTION/` 中运行：

```bash
python3 validate.py --compiler clang --arch sm_120 --output ../RESULTS/new-local-run
```

脚本要求输出目录不存在，完整运行后生成环境、命令、日志、SASS 和清单。其它机器可选择 `--compiler nvcc`，并用设备对应的 `--arch`；默认 `sm_120` 只适用于相应目标设备。

原始文件在整理前后的 SHA-256 相同：

```text
fa2c759d5e81ad83d75c4657da683124095a63b768f705f80c4c94121237746e  SUJET/tp3.pdf
0415d9c3a47a797a08dfb39349f9a459b929a69e5bb8abf8b5f99bfe7bfd0c26  CODE/dgemm-shared.cu
49dc6af9d825a6ab96d8f189fa5df3feac639563ca41e861d21ce46d298d585d  CODE/Makefile
a7429c1efc414be6b99f0b17403192749115e74e6fe2b3c5327e6f39a2c52b9c  CODE/parse_sass.sh
```

清单还保留了解答代码、验证脚本和临时二进制的哈希。原题和教师材料没有被覆盖。
