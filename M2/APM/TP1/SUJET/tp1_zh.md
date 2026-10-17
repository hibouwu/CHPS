# APM — TP1：内存访问优化

**M2 — 硬件加速器体系结构与编程，2026–2027 学年**  
凡尔赛圣康坦昂伊夫林大学 — 巴黎萨克雷大学  
**教师：** adrien.roussel@cea.fr  
**原题副标题：** 共享内存的使用

[Version française](tp1.md) · [原始题目（PDF）](tp1.pdf)

## 实验目标与说明

本实验通过线性代数中的典型计算——矩阵乘法，理解 GPU 上不同类型的内存及其使用方式。题目介绍中提到了全局内存、共享内存、常量内存和统一内存。

实验目标如下：

- 掌握 CUDA 编译流程；
- 理解 GPU 上的内存访问；
- 利用共享内存优化性能。

主要代码延续上一次实验的实现。本文件中的 Q.1～Q.12 涉及编译流程和使用全局内存的第一版矩阵乘法，尚未要求实现共享内存 kernel。

> **排版与一致性修正：** 原题混用了 `TMP` 和 `CUDAIMG`，这里统一为 `CUDAIMG`，并修正了命令选项中的横线。示例中的累加变量由 `float` 改为 `double`，与矩阵类型及 `dgemm.c` 保持一致。
>
> 以下参考答案已结合 **2026 年 10 月 9 日 ROMEO 实测**补全，作业号为 `738578`。题目原有的 Ruche 环境说明保留；本次运行使用 ROMEO GH200，复现命令见文末。

## I. 编译流程

在 Ruche 上先用 `module spider cuda` 查询可用的 CUDA 模块，再加载对应模块。如果存在名为 `cuda` 的模块，可以执行 `module load cuda`；否则使用查询到的带版本模块名。在 [tp1_check.cu](../CODE/Partie1/tp1_check.cu) 所在目录执行：

```bash
mkdir -p CUDAIMG
nvcc --keep --keep-dir CUDAIMG -c tp1_check.cu
ls CUDAIMG
```

中间文件保存在 `CUDAIMG` 中。`-c` 表示生成目标文件，不继续链接为可执行程序。

### Q.1 — 识别编译产物

**题目：** 哪个文件是 PTX？哪个文件是 CUDA 二进制文件？

**参考答案：** `.ptx` 文件包含面向 GPU 的文本形式中间代码。`.cubin` 文件包含针对某一 GPU 架构生成的机器代码。`.fatbin` 可以打包一个或多个目标架构的 PTX 和／或 cubin。`.o` 是主机侧目标文件，其中包含主机代码及嵌入的 GPU 代码等内容，它本身不是 cubin。具体文件名取决于 `nvcc` 版本和编译选项。参见 [NVIDIA nvcc 文档](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html)。

**ROMEO 实测：** 本次明确使用 `nvcc -O3 -arch=sm_90 --keep --keep-dir CUDAIMG -c tp1_check.cu`，生成的 PTX 为 [tp1_check.ptx](../RESULTS/romeo-738578/CUDAIMG/tp1_check.ptx)，GPU 机器代码为 [tp1_check.sm_90.cubin](../RESULTS/romeo-738578/CUDAIMG/tp1_check.sm_90.cubin)，打包文件为 [tp1_check.fatbin](../RESULTS/romeo-738578/CUDAIMG/tp1_check.fatbin)。原始程序执行输出 `TEST PASSED !`。

### Q.2 — 识别编译为 PTX 的代码

**题目：** `tp1_check.cu` 中哪些部分被保留下来，编译为 PTX？

**参考答案：** 所给文件中，在 GPU 上执行的计算代码是：

```cpp
__global__ void kernel(int *v) {
    *v = 1;
}
```

该 kernel 会生成 PTX 入口及必要的声明。`main`、输出语句、GPU 信息查询、`malloc`、`cudaMalloc`／`cudaMemcpy`／`cudaFree` 调用和最终结果检查都留在主机侧。`kernel<<<...>>>` 启动表达式被转换为触发 kernel 的主机代码；kernel 函数体在 GPU 上运行。

**实际 PTX 证据：** 入口为 `.visible .entry _Z6kernelPi`，关键指令为 `mov.u32 %r1, 1` 和 `st.global.u32 [%rd2], %r1`，对应向参数指向的全局内存写入整数 1。

### Q.3 — 理解 `_30` 后缀

**题目：** 生成文件名称中的 `_30` 后缀表示什么？

**参考答案：** 旧版文件名中的 `compute_30` 或 `sm_30` 对应 **3.0 计算能力**，属于 Kepler 架构。`compute_30` 表示虚拟架构目标，`sm_30` 表示机器代码目标。它不表示 CUDA 版本，也不表示线程数。这个后缀来自旧实验环境，当前编译命令不一定产生它。应查看实际生成的文件以及 PTX 的 `.target` 声明。参见 [历史版本 nvcc 文档](https://docs.nvidia.com/cuda/archive/8.0/cuda-compiler-driver-nvcc/index.html)。

**本次环境：** GH200 的计算能力为 9.0。生成文件使用 `.sm_90.cubin` 后缀，PTX 声明为 `.version 8.8`、`.target sm_90`；本次没有生成 `_30` 目标。

## II. 矩阵乘法

全局内存可由网格中的线程访问。本实验用 `cudaMalloc` 和 `cudaFree` 分配、释放 GPU 数组。

提供的串行程序 [dgemm.c](../CODE/Partie2/dgemm.c) 计算：

$$
C \leftarrow \alpha AB + \beta C.
$$

从这里开始，补全该程序，将计算移到 GPU，并把源文件扩展名改为 `.cu`。这里的三个矩阵均为 $N \times N$ 方阵，按行存储在包含 $N^2$ 个 `double` 元素的连续数组中。第 $(i,j)$ 个元素对应下标 `i * N + j`。

矩阵和标量完成初始化后，串行计算过程如下：

```cpp
for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
        double sum = 0.0;
        for (int k = 0; k < N; k++) {
            sum += A[i * N + k] * B[k * N + j];
        }
        C[i * N + j] = alpha * sum + beta * C[i * N + j];
    }
}
```

各题代码片段用于逐步补全程序，不能不加调整地直接全部拼接。以下假设 `N > 0`、主机内存分配成功，已包含 `<cuda_runtime.h>`，并复用 `tp1_check.cu` 中的 `CUDA_CHECK` 宏。保留 `dgemm.c` 中的 `init`、`dgemm` 和 `get_elapsedtime` 函数。Q.11 还需要 `<vector>` 和 `<cmath>`。kernel 定义放在 `main` 外，内存分配、复制和启动代码放在 `main` 内。

### 1. 内存分配与数据传输

### Q.4 — 在 GPU 上分配矩阵

**题目：** 用 `cudaMalloc` 在 GPU 上分配三个各含 $N^2$ 个元素的数组，分别保存两个输入矩阵和结果矩阵。使用连续存储，并在程序结束时用 `cudaFree` 释放。

**参考答案：** 每个矩阵需要 $N^2 \times \mathrm{sizeof(double)}$ 字节。CUDA 中 `double` 占 8 字节，因此每个矩阵为 $8N^2$ 字节。

```cpp
size_t bytes = (size_t)N * N * sizeof(double);
double *d_A = nullptr, *d_B = nullptr, *d_C = nullptr;
CUDA_CHECK(cudaMalloc((void **)&d_A, bytes));
CUDA_CHECK(cudaMalloc((void **)&d_B, bytes));
CUDA_CHECK(cudaMalloc((void **)&d_C, bytes));
```

结果回传并检查完毕后释放：

```cpp
CUDA_CHECK(cudaFree(d_A));
CUDA_CHECK(cudaFree(d_B));
CUDA_CHECK(cudaFree(d_C));
```

主机上的 `A`、`B`、`C` 若由 `malloc` 分配，仍需分别调用 `free` 释放。

### Q.5 — 将数据复制到 GPU

**题目：** 使用 `cudaMemcpy`，把主机端已初始化的数据传输到 GPU。

**参考答案：** 执行 `init(A, B, C, N)` 后，复制三个矩阵：

```cpp
CUDA_CHECK(cudaMemcpy(d_A, A, bytes, cudaMemcpyHostToDevice));
CUDA_CHECK(cudaMemcpy(d_B, B, bytes, cudaMemcpyHostToDevice));
CUDA_CHECK(cudaMemcpy(d_C, C, bytes, cudaMemcpyHostToDevice));
```

`d_C` 也必须初始化，因为计算中的 $\beta C$ 会读取原来的 $C$。所给程序中 `beta = 1`，$C$ 初始为零；`cudaMalloc` 不会自动把分配的内存清零。

### 2. kernel 配置

### Q.6 — 设置线程块和网格

**题目：** 使用 `dim3` 创建二维线程块，每块 $32 \times 32$，共 1 024 个线程。网格需要有足够的线程，使每个线程负责结果矩阵的一个元素。为简化处理，令 $N$ 为 32 的倍数。

**参考答案：** 用 `x` 方向对应列，`y` 方向对应行。

```cpp
dim3 block(32, 32);
dim3 grid((N + block.x - 1) / block.x,
          (N + block.y - 1) / block.y);
```

当 $N$ 为 32 的倍数时，网格包含 $(N/32) \times (N/32)$ 个线程块，总计恰好 $N^2$ 个线程。例如，$N=1024$ 时网格为 $32 \times 32$ 个线程块。上述向上取整写法也能覆盖其他大小，但需要配合 Q.10 的边界检查。应确认 GPU 支持每块 1 024 个线程及所要求的各维大小；题目指定的配置不一定是性能最好的配置。

### Q.7 — 启动空 kernel

**题目：** 编写一个暂时不执行计算的空 kernel，并在前面配置的网格上启动它。

**参考答案：** `__global__` 声明一个由主机调用、在 GPU 上执行的函数。

```cpp
__global__ void empty_kernel() {
}

// In main():
empty_kernel<<<grid, block>>>();
CUDA_CHECK(cudaGetLastError());
```

kernel 启动对主机是异步的。`cudaGetLastError` 检查启动错误；执行期间的错误还需要在同步或后续复制时检查。

### Q.8 — 回传结果

**题目：** kernel 执行后，将矩阵乘法结果传回主机。

**参考答案：** 将 `d_C` 复制到主机数组 `C`：

```cpp
CUDA_CHECK(cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost));
```

这里的 kernel 和复制操作使用同一个默认流。GPU 到 CPU 的复制会等待该流中的前序操作，且返回时结果已可供主机使用。在 Q.7 的空 kernel 阶段，矩阵还没有参与计算，复制回来的只是初始值。

### 3. 编写 kernel

### Q.9 — 计算行列下标

**题目：** 根据网格的维度和线程索引，计算该线程负责的 $C$ 元素的行号与列号。

**参考答案：**

```cpp
int row = blockIdx.y * blockDim.y + threadIdx.y;
int col = blockIdx.x * blockDim.x + threadIdx.x;
```

该线程负责 `C[row * N + col]`。不同的有效线程对应不同的矩阵元素。

### Q.10 — 计算 C 的一个元素

**题目：** 每个线程在 GPU kernel 中完成对应的 $C$ 元素计算。

**参考答案：** 线程遍历 $A$ 的第 `row` 行和 $B$ 的第 `col` 列，计算点积，再应用 $\alpha$ 和 $\beta$。

```cpp
__global__ void dgemm_kernel(int N, double alpha,
                             const double *A, const double *B,
                             double beta, double *C) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row >= N || col >= N) return;

    double sum = 0.0;
    for (int k = 0; k < N; k++) {
        sum += A[row * N + k] * B[k * N + col];
    }
    C[row * N + col] = alpha * sum + beta * C[row * N + col];
}
```

使用原程序中的系数，将空 kernel 启动和 Q.8 的回传代码替换为：

```cpp
double alpha = 1.0, beta = 1.0;
dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost));
```

这里不需要 `__syncthreads()`：每个线程使用自己的局部累加变量，并写入不同的元素。这一版矩阵乘法通过全局内存访问矩阵。

### 4. 性能分析

### Q.11 — 测量并比较运行时间

**题目：** 使用 `cudaEventElapsedTime` 测量 GPU 时间，考察矩阵乘法及结果回传到主机的耗时，并与 CPU 串行版本比较。

**参考答案：** 用两个 CUDA event 测量 kernel 时间，同时用主机计时函数 `get_elapsedtime` 测量“启动、计算、回传 $C$”这一过程。后者包含启动和计时开销，但不包括内存分配及最初的 CPU 到 GPU 复制。如果要统计整个应用的完整耗时，还应把这些步骤纳入范围。`cudaEventElapsedTime` 返回毫秒，读取前需要确保事件已经完成。参见 [NVIDIA CUDA event 文档](https://docs.nvidia.com/cuda/cuda-runtime-api/cuda_runtime_api/group__CUDART__EVENT.html)。

以下代码**替换** Q.10 的启动和回传部分。放在 Q.5 数据复制、Q.6 网格配置之后，并且放在任何会修改 `C` 的计算之前；预先定义 `alpha = 1.0`、`beta = 1.0`。代码保留初始 $C$，让 CPU 和 GPU 计算相同的表达式。

```cpp
// Keep the same initial C for the CPU, warm-up and measured GPU run.
std::vector<double> C_initial(C, C + (size_t)N * N);
std::vector<double> C_cpu = C_initial;

double cpu_start = get_elapsedtime();
dgemm(N, N, N, alpha, A, B, beta, C_cpu.data());
double cpu_ms = (get_elapsedtime() - cpu_start) * 1e3;

// Warm-up (excluded from timing).
dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaDeviceSynchronize());
CUDA_CHECK(cudaMemcpy(d_C, C_initial.data(), bytes,
                      cudaMemcpyHostToDevice));
CUDA_CHECK(cudaDeviceSynchronize());

cudaEvent_t start, stop;
CUDA_CHECK(cudaEventCreate(&start));
CUDA_CHECK(cudaEventCreate(&stop));

double gpu_start = get_elapsedtime();
CUDA_CHECK(cudaEventRecord(start));
dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaEventRecord(stop));
CUDA_CHECK(cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost));
double gpu_with_copy_ms = (get_elapsedtime() - gpu_start) * 1e3;

CUDA_CHECK(cudaEventSynchronize(stop));
float kernel_ms = 0.0f;
CUDA_CHECK(cudaEventElapsedTime(&kernel_ms, start, stop));
CUDA_CHECK(cudaEventDestroy(start));
CUDA_CHECK(cudaEventDestroy(stop));

printf("CPU: %.3f ms\n", cpu_ms);
printf("GPU kernel: %.3f ms\n", kernel_ms);
printf("GPU kernel + D2H (host): %.3f ms\n", gpu_with_copy_ms);
printf("Speedup (kernel): %.3f\n", cpu_ms / kernel_ms);
printf("Speedup (kernel + D2H): %.3f\n", cpu_ms / gpu_with_copy_ms);

bool correct = true;
for (size_t i = 0; i < C_initial.size(); i++) {
    double tolerance = 1e-10 + 1e-10 * std::abs(C_cpu[i]);
    if (!std::isfinite(C[i]) || !std::isfinite(C_cpu[i]) ||
        std::abs(C[i] - C_cpu[i]) > tolerance) {
        correct = false;
        break;
    }
}
printf("Validation: %s\n", correct ? "PASSED" : "FAILED");
```

示例误差容限用于本实验的基本检查，应根据数据尺度和 $N$ 调整。如果检查失败，应先排查结果，再比较性能。按照 `init` 的初始化，$A_{ik}=i$、$B_{kj}=k$、$C^{(0)}=0$；当 $\alpha=\beta=1$ 时，还可以用 $C_{ij}=iN(N-1)/2$ 验证结果。

预热后重复测量，并在每次测量之前将 `C_initial` 重新复制到 `d_C`，这次恢复不计入时间，最后报告中位数。否则在 $\beta=1$ 时，重复启动会不断累加结果。记录 CPU、GPU、CUDA 版本、$N$ 和编译选项。本次实测结果如下。

**ROMEO 实测条件：** 2026 年 10 月 9 日 14:27（巴黎时间），节点 `romeo-a057`，Slurm 作业 `738578`。GPU 为 NVIDIA GH200 120GB，CPU 为 Grace 的 ARM Neoverse-V2 单核（绑定 CPU 280）；CUDA 12.9.41、GCC 11.5.0、驱动 590.48.01。使用 `-O3 -arch=sm_90` 编译。矩阵为 `double`，线程块为 `32×32`，采用原始 `init` 数据及 `alpha = beta = 1`。

CPU 与 GPU 各预热一次，随后分别测量 5 次，表中每一列耗时均取各自中位数。CPU 保留题目中的 `i → j → k` 串行循环，未使用 BLAS 或多线程。主机数组使用普通可分页内存。事件测量只包围 kernel；“含回传”列使用主机时钟，包含启动、事件记录、计算及 GPU→CPU 复制，不包含分配、初始化和最初的 CPU→GPU 复制。校验、预热和每次恢复初始 C 均在计时区间之外。

| N | CPU 串行 / ms | GPU kernel / ms | GPU 含回传 / ms | kernel 加速比 | 含回传加速比 |
|---:|---:|---:|---:|---:|---:|
| 256 | 11.966112 | 0.036736 | 0.055616 | 325.73× | 215.16× |
| 512 | 205.259776 | 0.093152 | 0.121568 | 2203.49× | 1688.44× |
| 1024 | 1846.268896 | 0.577568 | 0.644448 | 3196.63× | 2864.89× |

这说明，对本实验的三种规模，GPU 版本在包含结果回传后仍快于所给的 CPU 串行实现。较大的加速比以朴素三重循环为基线，不能推广为相对于优化 BLAS 或多核 CPU 的加速比。这里也没有测量共享内存优化的收益。

**正确性：** 三种性能测试的 CPU、GPU 结果均与解析式 $C_{ij}=iN(N-1)/2$ 完全一致，最大绝对误差为 0。另对 `N = 1, 31, 32, 33, 65` 使用正负小数、非零初始 C、`alpha = 0.75` 和 `beta = -0.5`，与 `long double` 累加参考比较，全部通过，最大绝对误差约为 $2.164\times10^{-15}$。`N=33` 的 Compute Sanitizer `memcheck` 报告 **0 errors**；其插桩运行时间不进入性能表。

[完整日志](../RESULTS/romeo-738578/run.log) · [原始测量及中位数](../RESULTS/romeo-738578/measurements.json) · [Slurm 完成记录](../RESULTS/romeo-738578/slurm-accounting.txt)

### Q.12 — 复杂度和 FLOP/s

**题目：** 算法的算术复杂度是多少？计算实现的每秒浮点运算次数。

**参考答案：** 一共需要计算 $N^2$ 个元素，每个元素的点积循环执行 $N$ 次，因此总算术工作量为 $\Theta(N^3)$。每个线程完成 $\Theta(N)$ 的工作；并行执行不会改变总算术工作量。

每轮点积执行一次乘法和一次加法，通常采用以下运算量约定：

$$
F \simeq 2N^3.
$$

如果按照源代码逐项计数，$\alpha\,\mathrm{sum}+\beta C$ 还为每个元素增加两次乘法和一次加法，因此在编译器简化之前为 $2N^3+3N^2$ 次浮点运算。即使乘加融合为一条 FMA 指令，仍按两个 FLOP 计数。

若时间 $t_s$ 的单位是秒，或 $t_{ms}$ 的单位是毫秒，则：

$$
P_{\mathrm{FLOP/s}} = \frac{2N^3}{t_s},
\qquad
P_{\mathrm{GFLOP/s}} = \frac{2N^3}{t_{ms}\,10^6}.
$$

```cpp
double operations = 2.0 * N * N * N;
double kernel_gflops = operations / (kernel_ms * 1e6);
printf("GPU kernel: %.3f GFLOP/s\n", kernel_gflops);
```

当 $N=1024$ 时，$2N^3=2\,147\,483\,648$ FLOP。代入实际测得的时间，才能得到吞吐率。使用 `kernel_ms` 得到 kernel 吞吐率；使用 `gpu_with_copy_ms` 得到包含结果回传的有效吞吐率，需要明确标注。内存复制不计为 FLOP。本次 ROMEO 实测吞吐率如下。

| N | CPU / GFLOP/s | GPU kernel / GFLOP/s | GPU 含回传 / GFLOP/s |
|---:|---:|---:|---:|
| 256 | 2.804 | 913.394 | 603.326 |
| 512 | 1.308 | 2881.693 | 2208.112 |
| 1024 | 1.163 | 3718.149 | 3332.285 |

以 $N=1024$ 为例：

$$
P_{\mathrm{kernel}}=\frac{2\times1024^3}{0.577567995\times10^6}
\simeq 3718.149\ \mathrm{GFLOP/s}.
$$

这是该全局内存版本在本次配置下的实测吞吐率。

## III. 完整程序与 ROMEO 复现

完整实现见 [dgemm.cu](../CODE/Partie2/dgemm.cu)，自动编译、校验和测量脚本见 [run_romeo.sh](../CODE/run_romeo.sh)。原始 `dgemm.c` 与 `tp1_check.cu` 均保留。

远程目录为 `/gpfs/projet/r260073/hibouwu/coursework/apm-tp1-20261009`。本次发现 home 和 scratch 配额已满，因此使用该项目下的个人目录，没有删除已有研究文件。远程与本地源码哈希已核对，实测源码快照保存在 [source](../RESULTS/romeo-738578/source/)，校验清单见 [source.sha256](../RESULTS/romeo-738578/source.sha256)。

从本地终端连接，再通过 Slurm 执行：

```bash
ssh romeo
cd /gpfs/projet/r260073/hibouwu/coursework/apm-tp1-20261009/CODE
srun --account=r260073 --partition=instant --constraint=armgpu \
    --nodes=1 --ntasks=1 --cpus-per-task=1 --mem=4G \
    --gpus-per-node=1 --time=00:15:00 --job-name=apm-tp1 \
    --cpu-bind=cores bash ./run_romeo.sh
```

脚本会在计算节点加载 CUDA 12.9，将日志和中间文件保存到 `RESULTS/romeo-作业号/`。不要在登录节点直接执行 GPU 程序。上述命令会新申请作业；本次 `738578` 已正常结束，状态为 `COMPLETED`，退出码 `0:0`，分配时长 22 秒，资源已释放。如果其他研究任务也在申请 GH200，应沿用本地公共 GPU 锁串行安排。

若已经进入自己的 GPU 分配，并加载了 CUDA，也可以在 `CODE` 目录手动编译运行：

```bash
nvcc -std=c++17 -O3 -arch=sm_90 -Xcompiler=-Wall,-Wextra \
    Partie2/dgemm.cu -o dgemm
./dgemm 1024 5
./dgemm 33 2 general
```

参数依次是矩阵大小、测量次数以及可选的 `general` 校验输入。省略参数时使用 `N=1024`、5 次测量和原题输入。本地取回的可执行文件为 aarch64 架构，应在 ROMEO 对应计算节点运行。
