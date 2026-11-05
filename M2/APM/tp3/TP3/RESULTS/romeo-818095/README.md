# ROMEO：5 与 6 blocks/SM 的对照实测

2026-11-05 · [TP3 入口](../../../README.md) · [ROMEO 逐题解答](../../SUJET/tp3_romeo.md) · [初次完整验证](../romeo-817906/README.md)

**实测可以达到 6 blocks/SM、75% 理论 occupancy。** 当前 `dgemm_safe<4>` 默认编译使用 42 个寄存器/thread，API 返回 5；同一源码增加 `--maxrregcount=40` 后，编译器实际使用 40 个寄存器/thread，API 返回 6。两版均通过正确性和 sanitizer 检查，但 4096 阶的 6-block 版本稍慢，因此未修改原有默认编译选项。

## 作业与比较范围

Slurm 作业 **818095**，节点 `romeo-a043`，**COMPLETED / 0:0**，用时 **41 秒**。分配 1 GPU、2 CPU、4 GiB 内存，账户 `r260073`、分区 `instant`、约束 `armgpu`。作业已退出，GPU 分配已释放。

证据：[accounting](slurm-accounting.txt)、[完整日志](slurm.log)、[提交命令](submission.json)、[回传收据](retrieval.json)。环境为 GH200 120GB、132 SM、计算能力 9.0、nvcc 12.9.41、GCC 11.5.0，编译目标 `sm_90`。日志：[GPU](environment.log)、[nvcc](nvcc_version.log)、[GCC](host_compiler_version.log)。

两版使用同一份 [dgemm_tp3.cu](../../SOLUTION/dgemm_tp3.cu)，源文件 SHA-256 为：

```text
0cef892c05f1079dbfb240a00162e1afafc692bf69f04dabc7ba54207be1bbed
```

共同编译选项为 `-O3 -std=c++17 -lineinfo -Xptxas=-v -arch=sm_90`，唯一增加的选项为 `--maxrregcount=40`。本页只比较两个二进制中 `tiled_tm4` 的结果。该编译选项作用于整个源文件，也会改变其他 kernel 的编译结果；例如教师 kernel 在默认版使用 32 个寄存器，在限制版使用 40 个，不能把其余 kernel 与旧二进制视为相同机器代码。

## API 与寄存器分配

| `tiled_tm4` 指标 | 默认编译 | `--maxrregcount=40` |
|---|---:|---:|
| 线程/block | 256 | 256 |
| warp/block | 8 | 8 |
| 实际寄存器/thread | 42 | 40 |
| 取整后寄存器/warp，课堂模型 | 1536 | 1280 |
| 寄存器/block，课堂模型 | 12288 | 10240 |
| 静态/动态用户共享内存 | 16384 / 0 B | 16384 / 0 B |
| 手算 blocks/SM | 5 | 6 |
| CUDA API blocks/SM | **5** | **6** |
| CUDA API warps/SM | 40 | 48 |
| 理论 occupancy | **62.5%** | **75%** |
| ptxas spill stores / loads | 0 / 0 B | 0 / 0 B |
| ptxas stack / runtime local memory | 0 / 0 B | 0 / 0 B |

查询：[默认版](check_default_32_32_32.log)、[40 寄存器版](check_maxreg40_32_32_32.log)。编译资源：[默认 ptxas](build_default.log)、[40 寄存器 ptxas](build_maxreg40.log)；另有 [resource_default](resource_default.log)、[resource_maxreg40](resource_maxreg40.log)、[默认 SASS](sass_default.log)、[限制版 SASS](sass_maxreg40.log)。

默认版按原题每 warp 256 寄存器的分配单位计算：

$$R_w=256\left\lceil\frac{42\times32}{256}\right\rceil=1536,$$

$$R_b=1536\times8=12288,\qquad B_R=\lfloor65536/12288\rfloor=5.$$

40 寄存器版：

$$R_w=40\times32=1280,\quad R_b=1280\times8=10240,$$

$$B_R=\lfloor65536/10240\rfloor=6,\qquad \mathrm{Occupancy}=\frac{6\times8}{64}=75\%.$$

若对默认 42 寄存器版忽略取整，直接用 `65536/(42*256)`，也会算出 6，但与该默认二进制的 API 返回值不符。这里通过改变编译配置得到了 API 确认的 6；不能据此确定同学的源码、编译选项或算法。

这些是理论驻留容量。本次未运行 NCU 测量实际平均 occupancy，也未测量各 SM 随时间实际驻留的 block 数。

## 正确性与 sanitizer

每个二进制都检查了 1、31、32、33、256 阶，以及 63×65×37、128×96×160 的非方阵输入，均做全量 CPU 对照。1000、1024、2048、4096 阶每批计时前做 128 个确定性位置的 CPU 对照，包含首尾。所有尺寸还在各自二进制内对安全基线和优化版做全量 GPU 结果比较。

两版全部通过。CPU 对照最大绝对误差均为 **2.57571742e-14**，最大缩放误差均为 **1.54141741e-14**；同一二进制内安全基线与优化版全量比较的最大差值均为 0。大矩阵 CPU 对照是抽样，没有额外导出两份二进制的大矩阵进行跨二进制全量比较。

| 检查 | 默认版 | 40 寄存器版 |
|---|---|---|
| memcheck，N=32 | [0 errors](memcheck_default_32.log) | [0 errors](memcheck_maxreg40_32.log) |
| memcheck，N=33 | [0 errors](memcheck_default_33.log) | [0 errors](memcheck_maxreg40_33.log) |
| racecheck，N=33 | [0 hazards/errors/warnings](racecheck_default_33.log) | [0 hazards/errors/warnings](racecheck_maxreg40_33.log) |
| synccheck，N=33 | [0 errors](synccheck_default_33.log) | [0 errors](synccheck_maxreg40_33.log) |
| initcheck，N=33 | [0 errors](initcheck_default_33.log) | [0 errors](initcheck_maxreg40_33.log) |

## 三批性能对照

两版在同一作业、同一块 GPU 上运行。每批每版预热 2 次、采样 7 次，下表为各批中位数。第 1、3 批先跑默认版，第 2 批先跑 40 寄存器版。每次恢复相同初始 C，CUDA event 只覆盖一次 kernel，不含重置与传输。各日志保留 `SAMPLES_MS` 原始样本，汇总为 [timings.json](timings.json)。

| 阶数 | 批次 | 默认 5 blocks/SM，ms | 限制为 6 blocks/SM，ms | 默认时间/限制版时间 | 日志 |
|---|---:|---:|---:|---:|---|
| 1000 | 1 | 0.283840 | 0.262944 | 1.079× | [默认](batch1_default_1000.log) · [限制](batch1_maxreg40_1000.log) |
| 1000 | 2 | 0.289280 | 0.268064 | 1.079× | [默认](batch2_default_1000.log) · [限制](batch2_maxreg40_1000.log) |
| 1000 | 3 | 0.272544 | 0.265504 | 1.027× | [默认](batch3_default_1000.log) · [限制](batch3_maxreg40_1000.log) |
| 1024 | 1 | 0.287328 | 0.261088 | 1.101× | [默认](batch1_default_1024.log) · [限制](batch1_maxreg40_1024.log) |
| 1024 | 2 | 0.288928 | 0.264608 | 1.092× | [默认](batch2_default_1024.log) · [限制](batch2_maxreg40_1024.log) |
| 1024 | 3 | 0.269728 | 0.264800 | 1.019× | [默认](batch3_default_1024.log) · [限制](batch3_maxreg40_1024.log) |
| 2048 | 1 | 2.218880 | 1.991552 | 1.114× | [默认](batch1_default_2048.log) · [限制](batch1_maxreg40_2048.log) |
| 2048 | 2 | 2.254560 | 1.997600 | 1.129× | [默认](batch2_default_2048.log) · [限制](batch2_maxreg40_2048.log) |
| 2048 | 3 | 2.221120 | 1.996448 | 1.113× | [默认](batch3_default_2048.log) · [限制](batch3_maxreg40_2048.log) |
| 4096 | 1 | 16.484863 | 17.197887 | 0.959× | [默认](batch1_default_4096.log) · [限制](batch1_maxreg40_4096.log) |
| 4096 | 2 | 16.431423 | 17.082975 | 0.962× | [默认](batch2_default_4096.log) · [限制](batch2_maxreg40_4096.log) |
| 4096 | 3 | 16.432768 | 17.152479 | 0.958× | [默认](batch3_default_4096.log) · [限制](batch3_maxreg40_4096.log) |

比值大于 1 表示 40 寄存器版更快。本次 1000、1024、2048 阶均有改善，2048 阶约为 **1.113–1.129 倍**；4096 阶则约慢 **4.0%–4.4%**。因此不能因 occupancy 从 62.5% 增至 75% 就认定整体性能更好，原有默认选项保持不变。

未锁频，没有跨时段或跨节点重复，也没有统计置信区间。指令组织会随寄存器限制而变化，不能将全部时间差归因为 occupancy 本身。

## 复现与文件核对

两份二进制、源快照、编译日志和 SASS 均已保留。**71 个远端文件**按 [remote.sha256](remote.sha256) 全部核对，二进制哈希和命令见 [manifest.json](manifest.json)。本页、Slurm accounting 与回传收据是后续补充材料。

在已取得的 ROMEO GPU allocation 内加载 CUDA 12.9.0，于 `SOLUTION/` 执行：

```bash
python3 compare_registers.py --output ../RESULTS/new-register-comparison
```

对应 Slurm wrapper 为 [run_registers_romeo.sh](../../SOLUTION/run_registers_romeo.sh)，上传目录与 `APM_TP3_STAGE` 的绑定方式和[原有提交流程](../romeo-817906/README.md)一致。

只复现 40 寄存器编译与查询：

```bash
nvcc -O3 -std=c++17 -lineinfo -Xptxas=-v -arch=sm_90 \
  --maxrregcount=40 dgemm_tp3.cu -o dgemm_tp3_reg40.exe
./dgemm_tp3_reg40.exe 256
```

`--maxrregcount=40` 是上限请求；最终寄存器数与 spilling 仍应检查 ptxas 输出。本次实际为 40 个，且无 spill。
