# TP3 — ROMEO GH200 实测记录

2026-11-05 · [ROMEO 逐题解答](../../SUJET/tp3_romeo.md) · [详细原理与本机对照](../../SUJET/tp3.md) · [TP3 入口](../../../README.md)

**Slurm 作业 817906 已完成：`COMPLETED / 0:0`，节点 `romeo-a052`，用时 28 秒。** 使用一块 GH200、2 CPU、4 GiB 内存，账户 `r260073`，分区 `instant`，约束 `armgpu`。任务结束后 GPU 分配已释放。

证据：[Slurm accounting](slurm-accounting.txt)、[完整作业日志](slurm.log)、[提交参数](submission.json)、[回传与哈希核对记录](retrieval.json)。前两次仅在脚本定位目录时失败，记录见文末；未将失败作业计作成功验证。

## 环境与原始文件

| 项目 | 本次运行 |
|---|---|
| GPU | NVIDIA GH200 120GB，计算能力 9.0，132 SM |
| CPU 架构 | aarch64 |
| 驱动 | 590.48.01 |
| Toolkit / nvcc | CUDA 12.9 / V12.9.41 |
| 宿主编译器 | GCC 11.5.0 |
| 编译选项 | `-O3 -std=c++17 -lineinfo -Xptxas=-v -arch=sm_90` |
| 存储 | 独立的 `/scratch_p/hibouwu/coursework/apm-tp3-20261105T100627Z` |
| 临时文件 | 该任务目录下 `tmp-817906`，通过 TMPDIR/TMP/TEMP 配置 |

日志：[GPU](environment.log)、[nvcc](nvcc_version.log)、[GCC](host_compiler_version.log)、[编译及 ptxas 资源](build.log)。完整源文件快照在 [source/](source/)，教师源与解答 kernel 均留有哈希。解答 kernel 与本机运行的源代码相同；两次编译的编译器、架构和硬件不同，不能据此单独归因某一项的作用。

验证程序为 [dgemm_tp3.cu](../../SOLUTION/dgemm_tp3.cu)，集群启动脚本为 [run_romeo.sh](../../SOLUTION/run_romeo.sh)。原始 kernel 函数体通过 include 保留，教师 `main` 被重命名且未调用。

## Q1–Q13：资源与理论 occupancy

| 设备属性 | 实测值 |
|---|---:|
| 共享内存/SM | 233472 B = 228 KiB |
| 单 block 默认共享内存上限 | 49152 B = 48 KiB |
| 单 block opt-in 共享内存上限 | 232448 B = 227 KiB |
| 系统保留共享内存/block | 1024 B |
| 最大线程/SM | 2048 |
| 最大线程/block | 1024 |
| 寄存器/SM | 65536 个 32-bit 寄存器 |
| 最大 block/SM | 32 |
| warp 大小 | 32 |
| 最大 warp/SM | 64 |

来自 [资源查询日志](case_256_256_256.log)。下表的手算使用原题的 256 寄存器/warp 分配单位，并加入硬件 block、warp 和单 block 上限；共享内存容量比值为只计用户申请的课堂模型，最终用 API 核对。

| kernel 与启动 | 线程/block | 寄存器/thread | 静态/动态共享内存 | 手算 blocks/SM | API blocks/SM | API warps/SM | 理论 occupancy |
|---|---:|---:|---|---:|---:|---:|---:|
| 教师原始启动 `original_extra_smem` | 1024 | 32 | 16 / 16 KiB | 2 | 2 | 64 | 100% |
| 教师去掉额外申请 `original_no_extra_smem` | 1024 | 32 | 16 / 0 KiB | 2 | 2 | 64 | 100% |
| 安全基线 `shared_safe` | 1024 | 40 | 16 / 0 KiB | 1 | 1 | 32 | 50% |
| 每线程 4 个输出 `tiled_tm4` | 256 | 42 | 16 / 0 KiB | 5 | 5 | 40 | 62.5% |

教师原始启动的课堂上限为 $B_S=7$、$B_T=2$、$B_R=2$，最终 2 块、64 warp，occupancy 为 100%。安全基线的寄存器数升到 40/thread，每块 40960 个，只允许 1 块。优化版每 warp 按 256 向上取整为 1536 个寄存器，每块 12288 个，允许 5 块，共 40 warp。

因此，**相对安全基线，优化版的理论 occupancy 从 50% 提高到 62.5%；相对教师 kernel，则从 100% 降到 62.5%**。同时优化版在大矩阵上更快，说明最高 occupancy 不等于最低运行时间。

ptxas 报告三个 kernel 均为 0 stack、0 spill stores、0 spill loads；运行时 `localSizeBytes=0`。反汇编工具的 [resource usage](resource_usage.txt) 报告 `SHARED:17408`，而运行时的用户静态共享内存为 16384 B，两者相差本机 1024 B/block 保留量；不要把工具的不同口径混作用户静态数组大小。

以上均为理论驻留容量，不是用性能分析器测得的实际平均 occupancy。本次未使用 NCU，也未改动集群频率或驱动配置。

追加的 [作业 818095](../romeo-818095/README.md) 验证了另一种编译配置：同一优化源码增加 `--maxrregcount=40` 后，实际使用 40 寄存器/thread，API 返回 6 blocks/SM、75%。本页保留原始默认配置数据，不将两次作业混为同一二进制。

## 正确性与 sanitizer

计算 `C = 1.25*A*B - 0.5*C_initial`，输入含正负数和非零 C。CPU 参考用 `long double` 累加，误差要求为 `abs_error <= 1e-10*(1+abs(reference))`。

| M × N × K | CPU 对照 | 两个安全 GPU 版本的对照 | 日志 |
|---|---|---|---|
| 1 × 1 × 1 | 全量 | 全量 | [PASS](case_1_1_1.log) |
| 31 × 31 × 31 | 全量 | 全量 | [PASS](case_31_31_31.log) |
| 32 × 32 × 32 | 全量 | 全量 | [PASS](case_32_32_32.log) |
| 33 × 33 × 33 | 全量 | 全量 | [PASS](case_33_33_33.log) |
| 63 × 65 × 37 | 全量 | 全量 | [PASS](case_63_65_37.log) |
| 128 × 96 × 160 | 全量 | 全量 | [PASS](case_128_96_160.log) |
| 256 × 256 × 256 | 全量 | 全量 | [PASS](case_256_256_256.log) |
| 1000 × 1000 × 1000 | 128 个确定性位置，含首尾 | 全量 1000000 个元素 | [PASS](case_1000_1000_1000.log) |
| 1024 × 1024 × 1024 | 128 个确定性位置，含首尾 | 全量 1048576 个元素 | [PASS](case_1024_1024_1024.log) |
| 2048 × 2048 × 2048 | 每批 128 个位置 | 每批全量 4194304 个元素 | [PASS](large_batch1_2048.log) |
| 4096 × 4096 × 4096 | 每批 128 个位置 | 每批全量 16777216 个元素 | [PASS](large_batch1_4096.log) |

全部尺寸对照通过；在以上 CPU 检查点中最大绝对误差为 **2.57571742e-14**，最大缩放误差为 **1.54141741e-14**。两个安全 GPU 版本全量比较的最大差值均为 0。大矩阵 CPU 为抽样检查，不是全量 CPU 证明；GPU 版本彼此一致也不能代替独立参考。

原始 kernel 仅在 M/N/K 全部为 32 的倍数时执行，非对齐尺寸明确跳过。

| 检查 | 尺寸 | 结果 |
|---|---|---|
| [memcheck](memcheck_32.log) | 32，含教师原始两种启动与两个安全版本 | 0 errors |
| [memcheck](memcheck_33.log) | 33，两个安全版本 | 0 errors |
| [racecheck](racecheck_33.log) | 33，两个安全版本 | 0 hazards，0 errors，0 warnings |
| [synccheck](synccheck_33.log) | 33，两个安全版本 | 0 errors |
| [initcheck](initcheck_33.log) | 33，两个安全版本 | 0 errors |

sanitizer 使用 `--error-exitcode 99`，上述检查均退出 0。没有在所有大尺寸上重复 sanitizer。

## Q14–Q16：SASS

| kernel | 静态总条数 | 最多的指令 | LDS | DFMA | 原始文件 |
|---|---:|---|---:|---:|---|
| 教师原始 kernel | 160 | LDS：48，30.00% | 48 | 33 | [SASS](original.sass) · [统计](original_counts.md) |
| 安全基线 | 472 | IMAD：76，16.10% | 48 | 33 | [SASS](shared_safe.sass) · [统计](shared_safe_counts.md) |
| 每线程 4 个输出 | 656 | DFMA：132，20.12% | 96 | 132 | [SASS](tiled_tm4.sass) · [统计](tiled_tm4_counts.md) |

使用教师 `parse_sass.sh`，每份文件仅含一个 `sm_90` kernel。当前 GH200 构建中教师 kernel 的 LDS 静态数量最多，与题目预期方向一致；本机 Clang/SM120 构建中静态数量最多的则是 NOP。这反映了编译结果差异。

仍须区分静态次数与动态执行次数。优化版算 4 倍输出，DFMA 数约 4 倍，LDS 静态次数却只约 2 倍；这个静态结果与复用方向一致，但循环、向量读取宽度、谓词和调度都会影响实际流量，不能用静态次数直接计算时间。Q16 的 20–40/4–8 cycles 为题设假设，本次未实测这些延迟。

## Q17：三批计时

每次 kernel 前从设备备份恢复同一份 C；正确性执行后预热 2 次，再计时 7 次。下表取各批 7 次的中位数，CUDA event 只覆盖 kernel，排除分配、C 重置、主机与设备传输及 CPU 参考。每个样本保存在日志的 `SAMPLES_MS` 行。

| 阶数 | 批次 | 安全基线/ms | 优化版/ms | 基线/优化加速比 | 日志 |
|---|---:|---:|---:|---:|---|
| 256 | 1 | 0.020864 | 0.020288 | 1.028× | [batch 1](case_256_256_256.log) |
| 256 | 2 | 0.021248 | 0.020672 | 1.028× | [batch 2](batch2_256.log) |
| 256 | 3 | 0.021184 | 0.020640 | 1.026× | [batch 3](batch3_256.log) |
| 1000 | 1 | 0.558560 | 0.274336 | 2.036× | [batch 1](case_1000_1000_1000.log) |
| 1000 | 2 | 0.566432 | 0.291552 | 1.943× | [batch 2](batch2_1000.log) |
| 1000 | 3 | 0.566208 | 0.289984 | 1.953× | [batch 3](batch3_1000.log) |
| 1024 | 1 | 0.565152 | 0.289536 | 1.952× | [batch 1](case_1024_1024_1024.log) |
| 1024 | 2 | 0.561088 | 0.273280 | 2.053× | [batch 2](batch2_1024.log) |
| 1024 | 3 | 0.561632 | 0.288608 | 1.946× | [batch 3](batch3_1024.log) |
| 2048 | 1 | 4.587424 | 2.235136 | 2.052× | [batch 1](large_batch1_2048.log) |
| 2048 | 2 | 4.596960 | 2.248160 | 2.045× | [batch 2](large_batch2_2048.log) |
| 2048 | 3 | 4.587296 | 2.261632 | 2.028× | [batch 3](large_batch3_2048.log) |
| 4096 | 1 | 38.878239 | 16.529312 | 2.352× | [batch 1](large_batch1_4096.log) |
| 4096 | 2 | 38.895489 | 16.642719 | 2.337× | [batch 2](large_batch2_4096.log) |
| 4096 | 3 | 38.888287 | 16.604639 | 2.342× | [batch 3](large_batch3_4096.log) |

对齐尺寸还能直接与教师 kernel 比较。下表的教师版本已经去掉多余动态共享内存，函数体保持不变：

| 阶数 | 教师 kernel 中位数/ms，三批 | 优化版相对教师 kernel 加速比，三批 |
|---|---|---|
| 256 | 0.018816 / 0.019200 / 0.019232 | 0.927× / 0.929× / 0.932× |
| 1024 | 0.458272 / 0.457536 / 0.457280 | 1.583× / 1.674× / 1.584× |
| 2048 | 3.618304 / 3.622912 / 3.625632 | 1.619× / 1.612× / 1.603× |
| 4096 | 28.442656 / 28.382879 / 28.401344 | 1.721× / 1.705× / 1.710× |

优化版对大矩阵有改善，对 256 阶相对教师 kernel 反而稍慢，不能声称所有尺寸都更快。1000 阶不能与不处理边界的教师 kernel 做正确的直接性能对照。

该作业申请单块 GPU，启动时设备上没有其他运行进程，但没有锁频或独占整节点；版本执行顺序固定，未随机交错，也未报告统计置信区间。这些是本次短作业的结果，不是跨节点、跨时段或跨平台的性能保证。occupancy、复用与编译结果一起变化，不能仅凭计时将加速全部归因于某个单独机制。

## 复现

在 ROMEO 上传 `TP3/CODE`、`TP3/SOLUTION`、`TP3/SUJET/tp3.pdf` 到一个新的 scratch 任务目录后，执行如下形式的提交命令。`APM_TP3_STAGE` 必须指向含 `TP3/` 的父目录；Slurm 的 `$0` 指向 spool 副本，`SLURM_SUBMIT_DIR` 也不随 `--chdir` 改变。

```bash
stage=/scratch_p/hibouwu/coursework/apm-tp3-new-run
sbatch --account=r260073 --partition=instant --constraint=armgpu \
  --nodes=1 --ntasks=1 --cpus-per-task=2 --mem=4G \
  --gpus-per-node=1 --time=00:15:00 --job-name=apm-tp3 \
  --chdir="$stage" --export="ALL,APM_TP3_STAGE=$stage" \
  --output="$stage/slurm-%j.out" "$stage/TP3/SOLUTION/run_romeo.sh"
```

任务内加载 CUDA 12.9.0，使用 `validate.py --compiler nvcc --arch sm_90` 完成基本检查，再执行 2048、4096 阶三批对照。`validate.py` 现在还会保留二进制和源文件快照；本机旧运行的原始源快照也已补存，原始清单和数值未改。

本次回传的 **48 个远端文件**已按 [remote.sha256](remote.sha256) 全部核对。二进制 SHA-256 为：

```text
bf38f2e06f2b33b16fa45a9c93bde1efabe1ad8b94a01c8b8e786bd472ed2647
```

该清单描述回传当时的远端文件；本页、Slurm accounting 与回传收据属于随后补充的本地说明，未冒充原始运行产物。远端小型任务目录保留，没有清理其他项目文件。

## 保留的失败尝试

| 作业 | 状态 | 原因 | 保留材料 |
|---|---|---|---|
| 817900 | FAILED / 1:0，1 秒 | 按 `$0` 定位源码，实际落到 `/var/spool/slurmd` | [日志](../romeo-817900/slurm.log) · [accounting](../romeo-817900/slurm-accounting.txt) · [源快照](../romeo-817900/source/SOLUTION/run_romeo.sh) |
| 817904 | FAILED / 1:0，0 秒 | 将 `SLURM_SUBMIT_DIR` 误作 `--chdir` 路径，实际仍是 home | [日志](../romeo-817904/slurm.log) · [accounting](../romeo-817904/slurm-accounting.txt) · [源快照](../romeo-817904/source/SOLUTION/run_romeo.sh) |
| 817906 | COMPLETED / 0:0，28 秒 | 用显式环境变量绑定上传目录，全部检查通过 | [完整日志](slurm.log) |

前两次均在编译与计算前退出，最终成功结果全部来自 817906。
