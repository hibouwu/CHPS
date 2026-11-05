# 按课堂讲解复测：2 blocks/SM 与 100% occupancy

2026-11-05 · [TP3 入口](../../../README.md) · [ROMEO 逐题解答](../../SUJET/tp3_romeo.md)

**老师 70:06–74:58 这段讲解的计算已在 ROMEO 复现：每块 1024 线程、每块 32 warp、每个 SM 驻留 2 块，共 64 warp，理论 occupancy 为 100%。** 一维 `1024×1×1` 与正确改写索引后的二维 `32×32×1` 都得到这个结果。

## 作业与环境

Slurm 作业 **818143**，节点 `romeo-a046`，状态 **COMPLETED / 0:0**，用时 **13 秒**。分配 1 块 GPU、2 CPU、4 GiB 内存，账户 `r260073`、分区 `instant`、约束 `armgpu`。作业已结束，GPU 分配已释放。

设备为 GH200 120GB、132 SM、计算能力 9.0。nvcc 12.9.41，GCC 11.5.0，编译选项为 `-O3 -std=c++17 -lineinfo -Xptxas=-v -arch=sm_90`，**没有使用 `--maxrregcount`**。

证据：[accounting](slurm-accounting.txt)、[作业日志](slurm.log)、[提交参数](submission.json)、[环境](environment.log)、[nvcc](nvcc_version.log)、[GCC](host_compiler_version.log)。

## 比较的两个布局

一维对照直接编译现有 [dgemm_tp3.cu](../../SOLUTION/dgemm_tp3.cu)，教师 kernel 不改：

```cpp
dim3 block(1024, 1, 1);
// Inside the teacher kernel:
const uint threadRow = threadIdx.x / BLOCKSIZE;
const uint threadCol = threadIdx.x % BLOCKSIZE;
```

二维版生成独立的代码副本，将教师 kernel 的索引改为：

```cpp
dim3 block(32, 32, 1);
// Inside the adapted teacher kernel:
const uint threadRow = threadIdx.y;
const uint threadCol = threadIdx.x;
```

可检查 [二维 kernel 源码](variant_2d/teacher_2d.cu) 和 [二维版完整驱动](variant_2d/dgemm_tp3_2d.cu)。驱动仅对教师 `dgemm_shared` 使用二维启动，其他两个安全 kernel 保持一维布局。额外的主机打印会输出 `TEACHER_LAYOUT x=32 y=32 z=1 total_threads=1024`，用于绑定运行日志与布局。

不能只改启动形状而保留原有 `/32`、`%32` 索引，否则二维块中的 x 仅为 0–31，会导致多组线程错误地读写同一行。原教师文件和现有默认解答源没有被覆盖；生成与验证脚本为 [compare_teacher_layouts.py](../../SOLUTION/compare_teacher_layouts.py)，Slurm wrapper 为 [run_teacher_romeo.sh](../../SOLUTION/run_teacher_romeo.sh)。

## 资源与 API 实测

| 指标 | 一维 1024×1×1 | 二维 32×32×1 |
|---|---:|---:|
| threads/block，三维尺寸乘积 | 1024 | 1024 |
| warp/block | 32 | 32 |
| 实际寄存器/thread | 32 | 32 |
| 寄存器/block，课堂模型 | 32768 | 32768 |
| SM 最大线程数 | 2048 | 2048 |
| SM 最大 warp 数 | 64 | 64 |
| CUDA API blocks/SM | **2** | **2** |
| CUDA API warps/SM | **64** | **64** |
| 理论 occupancy | **100%** | **100%** |

日志：[一维查询](check_1d_32.log)、[二维查询](check_2d_32.log)。两版均分别检查教师原始的额外 16 KiB 动态申请，以及去掉此申请的启动，最终 API 结果都是 2 块、100%。ptxas 也报告两版教师 kernel 都使用 32 个寄存器/thread，无 spill、无 stack，见 [一维编译](build_1d.log)、[二维编译](build_2d.log)。

按老师讲解计算：

$$T_b=32\times32\times1=1024,\qquad W_b=1024/32=32,$$

$$B_T=\lfloor2048/1024\rfloor=2,\qquad
B_R=\lfloor65536/(32\times1024)\rfloor=2.$$

原始启动的用户共享内存为 32 KiB，课堂容量比值为 $\lfloor233472/32768\rfloor=7$；去掉多余动态申请后为 $\lfloor233472/16384\rfloor=14$。这些上限均高于线程、寄存器允许的 2 块，最终 API 也确认 2 块：

$$W_{active}=2\times32=64\ \mathrm{warps/SM},\qquad
\mathrm{Occupancy}=64/64=100\%.$$

64 是**每个 SM** 的 warp 数，不是整块 GPU 的 warp 总数。API 给出资源允许的理论驻留容量，未测实际平均 occupancy；小网格仍可能无法填满整块 GPU。本次只有每个尺寸 1 次计时采样，用于运行验证，不据此比较两种布局的性能。

## 与此前“5 或 6 块”的关系

| 比较对象 | 线程/block | 寄存器/thread | API blocks/SM | 理论 occupancy |
|---|---:|---:|---:|---:|
| 本次教师原始 kernel，两种布局 | 1024 | 32 | 2 | 100% |
| 每线程 4 个输出，默认编译 | 256 | 42 | 5 | 62.5% |
| 每线程 4 个输出，限制为最多 40 寄存器 | 256 | 40 | 6 | 75% |

后两行对应[作业 818095](../romeo-818095/README.md) 的不同编译配置，不能拿来代替老师对原始 kernel 的计算。“block 更多”也不能脱离每块 warp 数来比较 occupancy。

因此，按这段课堂内容填写原始 kernel 的 Q9–Q12，应使用 **64 最大 warp/SM、2 blocks/SM、64 活跃 warp/SM、100% 理论 occupancy**。Q17 再单独讨论改变每线程工作量后的优化版。

## 转录中需要区分的内容

- 70:06 的“2 blocs、64 warp、100%”与本次实测一致。
- 71:00 的法文识别结果“32 par 32, c’est pas 1024”前后矛盾。没有音频，无法断定原话；计算上 32×32 确实等于 1024，中文应保持这个事实。
- 71:56 的 2048 是 ROMEO GH200 的 `maxThreadsPerMultiProcessor`。72:49 提到其他 GPU 的 1536 也合理；先前本机 RTX 5070 Laptop GPU 的查询值正是 1536。
- 72:17 出现的“1736”在这份材料中只能作为待核对的转录内容，不能当作本次设备属性。
- 若 74:14 指的是改变 `-arch=sm_XX`，它不会将同一块 GH200 查询出的硬件线程容量从 2048 变成 1536；但编译目标和编译结果可以影响寄存器需求，从而影响某个 kernel 的 occupancy。该片段的具体词语仍存在识别歧义。

## 正确性与回传

两版均在 N=32、64、1024 运行通过。N=32、64 对 CPU 做全量对照；N=1024 对 CPU 检查 128 个确定性位置。教师原始两个启动和两个安全 kernel 都通过各自的 CPU 检查；日志中的 `GPU_COMPARE` 只比较该二进制内的两个安全 kernel，没有将其冒充两种教师布局间的全量比较。

| 检查 | 一维版 | 二维版 |
|---|---|---|
| N=32，全量 CPU | [PASS](check_1d_32.log) | [PASS](check_2d_32.log) |
| N=64，全量 CPU | [PASS](check_1d_64.log) | [PASS](check_2d_64.log) |
| N=1024，CPU 抽样 | [PASS](check_1d_1024.log) | [PASS](check_2d_1024.log) |
| memcheck，N=32 | [0 errors](memcheck_1d.log) | [0 errors](memcheck_2d.log) |
| racecheck，N=32 | [0 hazards/errors/warnings](racecheck_1d.log) | [0 hazards/errors/warnings](racecheck_2d.log) |

原始源文件、二维生成副本、两个二进制与命令均保留；**32 个远端文件**按 [remote.sha256](remote.sha256) 核对通过，另有 [manifest](manifest.json) 和 [回传记录](retrieval.json)。原始解答源的 SHA-256 仍为 `0cef892c05f1079dbfb240a00162e1afafc692bf69f04dabc7ba54207be1bbed`。

已取得 ROMEO GPU allocation 并加载 CUDA 12.9.0 后，于 `SOLUTION/` 执行：

```bash
python3 compare_teacher_layouts.py --output ../RESULTS/new-teacher-layout-check
```
