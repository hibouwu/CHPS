## 4. 习题解答与代码阅读

### 4.1. 复习顺序与原文对应

提供的课表把 DST 安排在 **10 月 22 日上午**，此前已安排 CM1-CM3、TD1、TD2 和 TP1。因此，4.2-4.8 是本章的主要复习内容。4.9-4.14 是有参考价值的往年题，作为拓展练习。GEMM 优化的 TP2 安排在考试后的 10 月 22 日下午。

| 文档 | 原文件标注的学年 | 本章覆盖内容 |
|---|---|---|
| [TD1 及已有解答](../TD1%20%20APM/td1.md) | 2026-2027 | Q.1-Q.9：索引、AXPY、CPU 模拟 |
| [TD2 Monte Carlo](../TD2/TD2/SUJET/td2.pdf) | 2026-2027 | Q.1-Q.6：C、OpenMP、CUDA、cuRAND |
| [TP1 中文版](../TP1/SUJET/tp1_zh.md) | 2026-2027 | Q.1-Q.12：编译、GEMM、校验、计时 |
| [往年 TP1 解答](../TDTP2025/TP/tp1_correction.pdf) | **2024-2025** | 补充 Q.13-Q.21：访存模型、合并访问、分块 |
| [往年 SDF 计分 TD](../TDTP2025/TD/td2.pdf) | 2025-2026 | Q.1-Q.7：三维数组、采样、投影 |
| [TP2 streams 题目](../TDTP2025/TP/tp2_sujet_2025-2026.pdf) / [解答](../TDTP2025/TP/tp2_correction.pdf) | 题目 2025-2026，解答 **2024-2025** | Q.1-Q.15：传输、依赖、计时 |

CUDA 片段默认具备相应头文件及错误检查；`CUDA_CHECK` 可采用 TP1 代码中的定义。

### 4.2. TD1 Q.1-Q.5：展平多维索引

**题意：** 为二维、三维网格中的块编号，计算三维块的线程数，再得到线程的唯一编号。

**解答：** 明确采用 **x 维最快、y 次之、z 最慢** 的顺序。每增加一个维度，就计入此前完整行或完整平面中的元素数。

```cpp
// Q.1: block in a 2D grid
unsigned int block2 = blockIdx.y * gridDim.x + blockIdx.x;
// Q.2: block in a 3D grid
unsigned int block3 = (blockIdx.z * gridDim.y + blockIdx.y)
                    * gridDim.x + blockIdx.x;
// Q.3: number of threads in a 3D block
unsigned int block_size = blockDim.x * blockDim.y * blockDim.z;
// Q.4: thread index within one block
unsigned int local = (threadIdx.z * blockDim.y + threadIdx.y)
                   * blockDim.x + threadIdx.x;
// Q.5: unique thread index, blocks stored consecutively
unsigned int global = block3 * block_size + local;
```

取 `gridDim=(2,2,2)`、`blockDim=(4,2,2)`、`blockIdx=(1,0,1)`、`threadIdx=(2,1,0)`，得到 `block3=5`、`block_size=16`、`local=6`，因此 **`global=86`**。

虽然 Q.4 原文使用了“全局索引”，这里实际求的是**块内**线程编号。Q.5 的编号也不一定等于三维空间数组的地址。访问空间数组时，应先求 `gx=blockIdx.x*blockDim.x+threadIdx.x`，同理求 `gy,gz`，再使用 `gx + Nx*(gy + Ny*gz)`。两种排列方式不能混用。

**纸上检查方法：** 第一个编号应为 0，最后一个应为“总数 − 1”；不同坐标不能映射到同一编号。处理特别大的数组时，乘法之前应先转换为 `size_t`。

### 4.3. TD1 Q.6-Q.9：阅读 AXPY 程序

实际源码为 [tp1.cu](../TD1%20%20APM/tp1.cu)。题目提到的 `td2.cu` 不在目录中，以下按实际提供的代码作答。

**Q.6--各部分在哪里执行？** `main`、分配、初始化、复制和 kernel 启动语句由 CPU 执行。声明为 `__global__ kernel` 的函数体在 GPU 上执行。`cudaMalloc` 是主机侧调用，分配的是设备内存。

**Q.7--程序计算什么？** 程序执行 AXPY：

$$
y_i\leftarrow 3.14x_i+y_i,
\qquad x_i=\frac1{i+1},\quad y_i^{(0)}=\frac{i-1}{i+1},
\qquad y_i=\frac{i+2.14}{i+1}.
$$

因此 `y[0]=2.14`。程序把结果复制回来后释放数组，并没有打印结果。

**Q.8--块数和线程数是多少？** `N=1000`，每块 64 个线程，需要 `ceil(1000/64)=16` 个块。**启动 1024 个线程**，其中 **1000 个线程有效**，另外 **24 个线程越界**，由 `if (i < N)` 排除。

**Q.9--不用 CUDA 进行模拟。** 保留两组数组、数据复制、kernel 函数，以及块和线程的两层循环。下面是核心实现；目录中已有[完整 CPU 程序](../TD1%20%20APM/tp1_cpu.cpp)。

```cpp
void kernel_cpu(const double *x, double *y, double alpha,
                int N, int block, int thread, int block_size) {
    int i = block * block_size + thread;
    if (i < N) y[i] = alpha * x[i] + y[i];
}
// d_x and d_y are separate CPU arrays; copy inputs into them first.
for (int block = 0; block < 16; ++block)
    for (int thread = 0; thread < 64; ++thread)
        kernel_cpu(d_x, d_y, 3.14, 1000, block, thread, 64);
// Copy d_y back into h_y, then release all four arrays.
```

这是对索引和数据流的**串行语义模拟**，不模拟 warp 或 GPU 的实际调度行为。

### 4.4. TD2 Q.1-Q.2：CPU 上的 Monte Carlo

**修正后的原理：** 在 `[0,1] × [0,1]` 中均匀取点，统计满足 `x*x+y*y<=1` 的点。四分之一圆面积为 `π/4`，正方形面积为 1。题目开头“边长为 1 的正方形与同心、半径为 1 的圆”的表述存在几何歧义；算法实际使用这里的单位正方形和四分之一单位圆。

$$
\widehat\pi=4\frac{H}{T},\qquad
\operatorname{SE}(\widehat\pi)=4\sqrt{\frac{p(1-p)}T},\quad p=\frac\pi4.
$$

在独立采样假设下，典型统计误差按 `1/sqrt(T)` 缩小。采样数增加 100 倍，误差尺度约缩小 10 倍，而不是 100 倍。

**Q.1--串行 C 版本。** [pi.c](../TD2/TD2/CODE/pi.c) 已有这一循环。注意 `10E7` 表示 **100 000 000** 次采样，不是一千万次。

```c
uint64_t hits = 0;
srand(2026);
for (uint64_t trial = 0; trial < trials; ++trial) {
    double x = rand() / (double)RAND_MAX;
    double y = rand() / (double)RAND_MAX;
    if (x * x + y * y <= 1.0) ++hits;
}
double pi = 4.0 * (double)hits / (double)trials;
```

**Q.2--题目要求的 OpenMP 版本。** 每个线程进行 `trials_per_thread` 次采样，把估计值写入自己的数组元素，再由主线程求平均。随机数生成器的状态必须是**线程私有**的，不能让线程竞争同一个全局状态。下面给出适用于 Linux 的 C/POSIX 教学片段，需要 `stdlib.h`、`stdint.h`、`omp.h`：

```c
int capacity = omp_get_max_threads(), used = 0;
double *partial = malloc((size_t)capacity * sizeof(*partial));
#pragma omp parallel shared(partial, used)
{
    int tid = omp_get_thread_num();
    unsigned int state = 2026u + 104729u * (unsigned int)tid;
    uint64_t hits = 0;
    #pragma omp single
    used = omp_get_num_threads();
    for (uint64_t trial = 0; trial < trials_per_thread; ++trial) {
        double x = rand_r(&state) / (double)RAND_MAX;
        double y = rand_r(&state) / (double)RAND_MAX;
        if (x*x + y*y <= 1.0) ++hits;
    }
    partial[tid] = 4.0 * hits / trials_per_thread;
}
double pi = 0.0;
for (int tid = 0; tid < used; ++tid) pi += partial[tid];
pi /= used;
free(partial);
```

`rand_r` 是 POSIX 教学用法，不能据此证明随机序列的质量或统计独立性。并行区域结束时，所有线程已经完成写入。各线程采样数相同，所以可以直接平均；若采样数不同，应汇总命中数和总采样数，再计算 `4*sum(hits)/sum(trials)`。

### 4.5. TD2 Q.3-Q.6：GPU 上的 Monte Carlo

**Q.3--执行配置。** `512` 个块，每块 `256` 个线程，共 **131 072 个线程**。若 `R=TRIALS_PER_THREAD`，总采样数为 `131072*R`。

**Q.4--分配。** 每线程存一个 `double`，共 `131072*8=1048576` 字节，即 **1 MiB**。**Q.5--取回结果。** 在 kernel 启动后安排 D2H 复制；同一 stream 中的先后顺序保证随后可以在 CPU 求平均。

```cpp
const int blocks = 512, threads = 256;
const int count = blocks * threads;
size_t bytes = (size_t)count * sizeof(double);
double *d_partial;
double *h_partial = (double *)malloc(bytes);
CUDA_CHECK(cudaMalloc((void **)&d_partial, bytes));
monte_carlo<<<blocks, threads>>>(d_partial, trials_per_thread, 2026ULL);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaMemcpy(h_partial, d_partial, bytes, cudaMemcpyDeviceToHost));
double pi = 0.0;
for (int i = 0; i < count; ++i) pi += h_partial[i];
pi /= count;
CUDA_CHECK(cudaFree(d_partial));
free(h_partial);
```

**Q.6--kernel。** 每个线程使用局部 cuRAND 状态，以 `tid` 区分序列，避免所有线程生成完全相同的采样。下面的 kernel 应定义在启动代码之前：

```cpp
#include <curand_kernel.h>
__global__ void monte_carlo(double *partial, unsigned long long trials,
                            unsigned long long seed) {
    unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;
    curandStatePhilox4_32_10_t state;
    curand_init(seed, (unsigned long long)tid, 0ULL, &state);
    unsigned long long hits = 0;
    for (unsigned long long trial = 0; trial < trials; ++trial) {
        double x = curand_uniform_double(&state);
        double y = curand_uniform_double(&state);
        if (x*x + y*y <= 1.0) ++hits;
    }
    partial[tid] = 4.0 * (double)hits / (double)trials;
}
```

要求 `trials>0`。API 接收的是**状态指针**；原题给出的函数原型不完整。`curand_init` 的返回类型是 `void`，cuRAND 的均匀随机函数取值范围是 `(0,1]`。这种离散端点约定不改变四分之一圆的建模方法。CPU 和 GPU 若使用不同随机数生成器，不要求 π 估计值逐位相等；应检查采样总数、结果是否位于 `[0,4]`、固定配置下能否复现，以及统计误差的变化。

### 4.6. TP1 Q.1-Q.3：编译链

**Q.1--分别是什么文件？** `.ptx` 是 GPU 代码的文本中间表示；`.cubin` 是特定 GPU 目标的机器码；`.fatbin` 可以包含 PTX 和／或 cubin；`.o` 是主机侧目标文件，其中可嵌入 GPU 代码。`-c` 表示编译到目标文件，不完成可执行文件的链接。

```bash
mkdir -p CUDAIMG
nvcc --keep --keep-dir CUDAIMG -c tp1_check.cu
```

**Q.2--哪部分生成 PTX？** 在 [tp1_check.cu](../TP1/CODE/Partie1/tp1_check.cu) 中，`__global__ void kernel(int *v) { *v=1; }` 成为 GPU 入口。`main`、`printf`、分配、复制和校验留在主机端。启动语句被转换为请求执行 kernel 的主机代码。

**Q.3--`_30` 表示什么？** `sm_30` 或 `compute_30` 表示计算能力 **3.0**，不是 CUDA 3.0，也不是 30 个线程。`compute_*` 是虚拟目标，`sm_*` 是机器目标。实际文件名取决于编译器和选项。已有 GH200 实验生成的是 `sm_90`，即计算能力 9.0，不能把历史题目中的 `_30` 套在该实验上。

### 4.7. TP1 Q.4-Q.10：建立正确的 GEMM

[串行源码](../TP1/CODE/Partie2/dgemm.c) 计算 `C ← αAB + βC`，矩阵元素为 `double`，按行连续存储：`(row,col)` 对应 `row*N+col`。

**Q.4-Q.5--分配和复制。** 分配三个包含 `N*N` 个元素的连续数组。还要复制 **C 的初值**，因为公式会读取 `βC`；`cudaMalloc` 不负责初始化内容。

```cpp
size_t bytes = (size_t)N * N * sizeof(double);
double *d_A, *d_B, *d_C;
CUDA_CHECK(cudaMalloc((void **)&d_A, bytes));
CUDA_CHECK(cudaMalloc((void **)&d_B, bytes));
CUDA_CHECK(cudaMalloc((void **)&d_C, bytes));
CUDA_CHECK(cudaMemcpy(d_A, A, bytes, cudaMemcpyHostToDevice));
CUDA_CHECK(cudaMemcpy(d_B, B, bytes, cudaMemcpyHostToDevice));
CUDA_CHECK(cudaMemcpy(d_C, C, bytes, cudaMemcpyHostToDevice));
```

**Q.6--执行配置。** 题目指定 `block(32,32)`，每块 1024 个线程，即 32 个 warp。网格向上取整也能覆盖不是 32 倍数的尺寸；应检查设备限制并保留越界判断。

```cpp
dim3 block(32, 32);
dim3 grid((N + 31) / 32, (N + 31) / 32);
```

**Q.7：空 kernel。** 定义一个不修改矩阵的函数，再从 `main` 发起调用：

```cpp
__global__ void empty_kernel() {}
// In main(), after grid and block have been defined:
empty_kernel<<<grid, block>>>();
```

**Q.8：取回结果。** 在 kernel 后执行下面的复制。该 stream 内的复制会等待前面的计算。

```cpp
CUDA_CHECK(cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost));
```

**Q.9-Q.10--索引与计算。** `x` 遍历列，`y` 遍历行。每个线程只计算一个输出元素；累加器是线程局部变量，类型采用 `double`。

```cpp
__global__ void dgemm_kernel(int N, double alpha, const double *A,
                             const double *B, double beta, double *C) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row >= N || col >= N) return;
    double sum = 0.0;
    for (int k = 0; k < N; ++k)
        sum += A[row*N+k] * B[k*N+col];
    C[row*N+col] = alpha * sum + beta * C[row*N+col];
}
// In main(), after allocations and copies:
dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost));
CUDA_CHECK(cudaFree(d_A));
CUDA_CHECK(cudaFree(d_B));
CUDA_CHECK(cudaFree(d_C));
```

这里不需要 `__syncthreads()`，因为线程间不共享中间计算结果。原程序初始化为 `A[i,k]=i`、`B[k,j]=k`、`C=0`、`α=β=1`，因此预期结果为 `C[i,j]=i*N*(N-1)/2`。这条解析式可用于独立于 CPU 循环的校验。

### 4.8. TP1 Q.11-Q.12：正确性与性能

**Q.11--测量什么？** 区分 kernel 时间、kernel 加 D2H 回传时间，以及包含分配和 H2D 的完整时间。只测量 kernel 启动调用，不能得到异步计算的执行时间。测量 kernel 时，在它所在的 stream 中插入两个事件：

```cpp
cudaEvent_t start, stop;
CUDA_CHECK(cudaEventCreate(&start));
CUDA_CHECK(cudaEventCreate(&stop));
CUDA_CHECK(cudaEventRecord(start));
dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaEventRecord(stop));
CUDA_CHECK(cudaEventSynchronize(stop));
float kernel_ms;
CUDA_CHECK(cudaEventElapsedTime(&kernel_ms, start, stop));
CUDA_CHECK(cudaEventDestroy(start));
CUDA_CHECK(cudaEventDestroy(stop));
```

测量 kernel 加 D2H 时，用主机时钟从启动前测到阻塞复制完成后。应预热、重复测量、说明采用的统计量，并在每轮前恢复 C：`β=1` 时直接重复启动会不断累加结果。先检查正确性，再解释时间。

**Q.12--复杂度和吞吐率。** `N²` 个输出，每个输出执行 `N` 轮，所以总工作量为 `Θ(N³)`，每线程工作量为 `Θ(N)`。一条 FMA 按两个 FLOP 计数。常用主项计数为：

$$
F\simeq2N^3,\qquad P_{\mathrm{GFLOP/s}}=\frac{2N^3}{t_{\mathrm{ms}}10^6},
\qquad S=\frac{t_{\mathrm{CPU}}}{t_{\mathrm{GPU}}}.
$$

如果逐项计算源码中的 `αsum+βC`，编译器化简之前还应增加 `3N²` 次运算。内存复制不计为 FLOP。

**实测例子：** TP1 在 ROMEO 上的[日志](../TP1/RESULTS/romeo-738578/run.log)与[测量 JSON](../TP1/RESULTS/romeo-738578/measurements.json)记录：GH200、CUDA 12.9、FP64、`32×32` 线程块，预热一次后测量五次。CPU 基线是 Grace 单核上的朴素循环。表中为五次测量的中位数；kernel + D2H 列不含分配、初始化和最初的 H2D。恢复 C 初值、预热与校验均在计时区间之外。

| N | CPU / ms | Kernel / ms | Kernel + D2H / ms | Kernel / GFLOP/s |
|---:|---:|---:|---:|---:|
| 256 | 11.966112 | 0.036736 | 0.055616 | 913.394 |
| 512 | 205.259776 | 0.093152 | 0.121568 | 2881.693 |
| 1024 | 1846.268896 | 0.577568 | 0.644448 | 3718.149 |

这些数字没有测量优化 BLAS 的 CPU 性能，也没有测量共享内存优化收益。`N=1024` 时，相对该 CPU 循环的 kernel 加速比约为 `3196.63`，含 D2H 的加速比约为 `2864.89`。数据中另有 `N=1,31,32,33,65`、非零初始 C 的一般输入校验，可补充原题高度规则的初始化。实现见[完整程序](../TP1/CODE/Partie2/dgemm.cu)。

### 4.9. 拓展--往年 TP1 Q.13-Q.16：流量与合并访问

这些题来自 **2024-2025** 解答。题号不同于本年 TP1：往年 Q.12 是计时，Q.13 开始分析性能模型。往年 Q.1-Q.12 的基本步骤已经在 4.6-4.8 讲解，题号相同不代表问题相同。

**Q.13--`C=AB`、FP32、N=4096 的理想下界。** 假设 A、B 每个元素只读一次，C 每个元素只写一次。这个问题版本不读取 C 初值。

$$
F=2N^3=137.438953472\times10^9\ \mathrm{FLOP},\qquad
V_r=8N^2=128\ \mathrm{MiB},\quad V_w=4N^2=64\ \mathrm{MiB}.
$$

$$
\begin{aligned}
V&=12N^2=192\ \mathrm{MiB}=201.326592\ \mathrm{MB},\\
t_{\mathrm{data}}&=V/BW,\qquad t_{\mathrm{compute}}=F/P_{\mathrm{peak}},\\
t&\ge\max(t_{\mathrm{data}},t_{\mathrm{compute}}).
\end{aligned}
$$

工作量单位是 FLOP，不是 FLOP/s。$1\,\mathrm{MiB}=2^{20}$ 字节，$1\,\mathrm{MB}=10^6$ 字节。`ρ=t_compute/t_data` 比较两个下界：`ρ>1` 表示**在这个理想模型中**计算下界更大，不证明实际的朴素 kernel 一定受计算限制。若 `β≠0`，最小流量还要加入 C 初值的读取。

**Q.14--与峰值比较。** 先算 `P_实测=F/t`，再算 `P_实测/P_峰值`。精度和指令必须匹配：FP64 标量 kernel 不能直接与 FP32 或 Tensor Core 峰值比较。FP64/FP32 的比例依赖 GPU，不固定为 1/2。本章没有新增吞吐率测量。

**Q.15--128 B 缓存行模型。** 这里假设 `C=AB`，不读取 C 初值：一个线程读 A 的 N 个元素、B 的 N 个元素，再写一个 C。FP64 每线程逻辑数据量为 `8(2N+1)` 字节，N=4096 时是 **65544 字节**。为明确假设，忽略线程间缓存行共享，把一次写入算作一次缓存行传输，不额外计算写分配流量。

$$
V_{\mathrm{tout\ manque}}=N^2(2N+1)128\ \mathrm{B},\qquad
V_{\mathrm{localite\ ligne}}=N^2\left(\left\lceil\frac{N}{16}\right\rceil+N+1\right)128\ \mathrm{B}.
$$

第二个模型利用 A 的一条缓存行容纳 16 个 `double`，但假设 B 的一列每读取一个元素就缺失一次。N=4096 时，两种模型分别约为 **16.002 TiB**、**8.502 TiB**；单个矩阵只有 **128 MiB**。这些是教学模型下的计数，**不是观测到的 DRAM 流量**；合并访问、缓存和线程间复用会改变真实流量。旧解答的流量数字与其计数过程不一致，因此这里重新推算。

**Q.16--合并访问的映射。** 若 warp 内 `row` 相同、`col` 连续，固定 k 时线程读取同一个 A、连续的 B，再写连续的 C。采用 `col=blockIdx.x*T+threadIdx.x`、`row=blockIdx.y*T+threadIdx.y`。本年 TP1 已采用这个选择。若用含 `T*T` 个线程的一维块：

```cpp
int row = blockIdx.y * T + threadIdx.x / T;
int col = blockIdx.x * T + threadIdx.x % T;
```

`% T` 必须作用于 `threadIdx.x`。旧解答的 `threadIdx.y % T` 不适用于一维块，因为其中 `threadIdx.y` 恒为 0。

### 4.10. 拓展--往年 TP1 Q.17-Q.21：共享内存分块

**Q.17-Q.19--声明、加载、计算。** 两块 `T×T` 的 `double` tile 占用 `2*T*T*8` 字节共享内存，**T=32 时为 16 KiB**。一个块计算 C 的一个 tile。沿 K 维推进时，每个线程各加载一个 A、B 元素，再复用其他线程加载的数据。

为正确完成 Q.17-Q.19 的实现，需要两次屏障：第一次保证全部加载完成后再读取共享数据；第二次保证所有线程读完后，下一块数据才覆盖当前 tile。下面还处理 N 不是 T 倍数的情况：

```cpp
template<int T>
__global__ void tiled_gemm(int N, const double *A, const double *B,
                            double *C, double alpha, double beta) {
    __shared__ double tile_A[T][T], tile_B[T][T];
    int tx = threadIdx.x, ty = threadIdx.y;
    int row = blockIdx.y * T + ty, col = blockIdx.x * T + tx;
    double sum = 0.0;
    for (int base = 0; base < N; base += T) {
        tile_A[ty][tx] = (row < N && base+tx < N)
                       ? A[row*N+base+tx] : 0.0;
        tile_B[ty][tx] = (base+ty < N && col < N)
                       ? B[(base+ty)*N+col] : 0.0;
        __syncthreads();
        for (int k = 0; k < T; ++k)
            sum += tile_A[ty][k] * tile_B[k][tx];
        __syncthreads();
    }
    if (row < N && col < N)
        C[row*N+col] = alpha * sum + beta * C[row*N+col];
}
```

以 `block(T,T)` 启动。所有线程都参与两次屏障，输出越界的线程加载零，最后不写 C。不要把屏障放进按线程分歧的 `if (row<N && col<N)`。对 `C=AB` 可取 `alpha=1,beta=0`，但这段代码仍显式读取 `beta*C`，所以也应提供初始化后的 C。

**Q.20--运行并核对结果。** 使用相同输入及相同 C 初值，将分块版本与前一版本和 CPU 参考结果比较。既测 T 的倍数，也测边界尺寸，例如 `N=1,T-1,T,T+1,2*T+1`，并使用正负数和非零 C。检查结果是否有限，再验证 `abs(gpu-ref) <= atol + rtol*abs(ref)`；容限应根据精度、N 和数据尺度选择。如果不同运行的错误不稳定，可能是缺少屏障；同时排查索引、边界补零和 C 初值恢复。

**Q.21--FP32/FP64 的收益。** 在相同大小、类型、系数和计时范围下测量各版本，再计算 `t_朴素/t_分块`。收益取决于缓存、算术吞吐率、屏障和每块资源占用。旧解答的数字来自其他 GPU。

### 4.11. 拓展--SDF Q.1-Q.5：采样三维体积

**2025-2026** 计分 TD 使用符号距离：物体内部为负，外部为正。先为每个三维点生成颜色，再投影为二维图像。PDF 引用的 `Color`、`GetColor`、`PPMSave` 模板不在目录中，因此以下接口需按实际模板适配，不是直接可编译的完整程序。

**Q.1--连续数组。** 题图为 x 最快、y 次之、z 最慢。边长 N 的立方数组索引为：

```cpp
__host__ __device__ size_t index3(int x, int y, int z, int N) {
    return (size_t)x + (size_t)N * ((size_t)y + (size_t)N * z);
}
// PPMSave: color[index3(x, slice, z, N)]
```

**Q.2--分配。** `count=(size_t)N*N*N`，`bytes=count*sizeof(Color)`；主机用 `malloc(bytes)`，设备用 `cudaMalloc(...,bytes)`。N=1000 时有**十亿个颜色元素**：若 `sizeof(Color)==3`，占 3 GB；若为 4，占 4 GB。核实结构体大小、分配结果和可用内存。

**Q.3--网格。** 可以用 `block(8,8,8)`，每块 512 个线程，N=1000 时配 `grid(125,125,125)`。每线程负责一个体素；保留 `x<N && y<N && z<N` 以适应其他大小。这个配置便于坐标映射，不意味着性能最优。

**Q.4--Y=0 切片。** 明确采用 `position(i)=-1+2*i/N`，区间为 `[-1,1[`，则 **slice=N/2=500**。如果用 `-1+2*i/(N-1)` 包含两端点，1000 个点中没有精确的零，499、500 位于 Y=0 两侧。先说明采样约定，再选择切片。

采样后把设备体积复制回主机，让 `PPMSave` 读取 `(x,500,z)`。设备数据保留用于投影。只复制切片能减少传输量，但不是完成本题的必要条件。

**Q.5--颜色。** 按 Q.4 的约定实现如下逻辑：

```text
x = blockIdx.x * blockDim.x + threadIdx.x
y = blockIdx.y * blockDim.y + threadIdx.y
z = blockIdx.z * blockDim.z + threadIdx.z
if x < N and y < N and z < N:
    px = -1.0 + 2.0*x/N
    py = -1.0 + 2.0*y/N
    pz = -1.0 + 2.0*z/N
    color[index3(x,y,z,N)] = GetColor(px,py,pz)
```

### 4.12. 拓展--SDF Q.6-Q.7：无竞争的投影

**Q.6--网格。** 一个线程负责完整的一列 `(x,z)`。例如二维块 `block(32,8)`，网格 `((N+31)/32,(N+7)/8)`。CUDA x 轴映射空间 x，CUDA y 轴映射空间 **z**。线程数约为 N²，不是 N³。

**Q.7--投影。** 观察者在 `(0,+∞,0)`。按 y 递增遍历，每遇到非黑色就更新当前颜色，最终保留最大 y 处的可见颜色。循环边界为 **y<N**，不能写 `y<=1000`。

```text
x = blockIdx.x * blockDim.x + threadIdx.x
z = blockIdx.y * blockDim.y + threadIdx.y
if x < N and z < N:
    last = Color(0,0,0)
    for y = 0, ..., N-1:
        current = color[index3(x,y,z,N)]
        if current.r != 0 or current.g != 0 or current.b != 0:
            last = current
    color[index3(x,0,z,N)] = last
```

每线程读完后只写**自己那列**的底部，无需原子操作或线程间屏障。采样和投影应在同一 stream 依次执行，或用事件建立依赖。随后复制结果，以 `slice=0` 保存。让每体素一个线程并同时写 `(x,0,z)` 会造成竞争。

### 4.13. 拓展--streams Q.1-Q.9：切分数据并安排顺序

题目为 **2025-2026**，解答为 **2024-2025**。引用的程序及 `graph.pdf` 不在目录中。可以重建原理，但缺少 `func` 源码，不能假造其中指数函数的具体表达式。

**Q.1--移植。** 计算 `i=blockIdx.x*blockDim.x+threadIdx.x`，判断 `i<N`，然后对第 i 个元素执行 `func`。kernel 为 `__global__`，网格块数为 `(N+threads-1)/threads`。

**Q.2-Q.4--stream。** 创建 NSTREAMS 个 stream，各处理互不相交的一段数据。省略启动语句第四个参数时使用默认 stream。legacy 模式与阻塞 stream 建立隐式依赖，per-thread 模式规则不同。kernel 启动不会因此变成对 CPU 的阻塞调用：GPU 操作顺序和主机调用返回是两个不同问题。

```cpp
cudaStream_t streams[NSTREAMS];
for (int s = 0; s < NSTREAMS; ++s)
    CUDA_CHECK(cudaStreamCreate(&streams[s]));
for (int s = 0; s < NSTREAMS; ++s) {
    size_t begin = (size_t)s * total / NSTREAMS;
    size_t end = (size_t)(s+1) * total / NSTREAMS;
    size_t count = end - begin;
    if (count == 0) continue;
    size_t bytes = count * sizeof(double);
    CUDA_CHECK(cudaMemcpyAsync(d_in+begin, h_in+begin, bytes,
                               cudaMemcpyHostToDevice, streams[s]));
    func_kernel<<<(count+255)/256, 256, 0, streams[s]>>>(
        d_in+begin, d_out+begin, count);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaMemcpyAsync(h_out+begin, d_out+begin, bytes,
                               cudaMemcpyDeviceToHost, streams[s]));
}
for (int s = 0; s < NSTREAMS; ++s)
    CUDA_CHECK(cudaStreamSynchronize(streams[s]));
// Check results, then release buffers after all their users have finished.
for (int s = 0; s < NSTREAMS; ++s)
    CUDA_CHECK(cudaStreamDestroy(streams[s]));
```

片段之前应完成缓冲区分配；`func_kernel` 按缺失的原程序定义。用商计算分段起止位置，也能处理 `total` 不能被 NSTREAMS 整除的余数。

**Q.5--为什么收益可能很小？** 多个 kernel 不保证重叠：阻塞复制、可分页内存、GPU 饱和、分段过小或启动开销，都可能限制收益。不能让 NSTREAMS 个 kernel 各处理整个向量，否则会增加工作量，还可能造成竞争。

**Q.6-Q.7--异步复制与 pinned。** `cudaMemcpyAsync` 将复制排入 stream。为支持通常的 H2D/D2H 重叠，主机缓冲区用 `cudaMallocHost` 分配，以 `cudaFreeHost` 释放。传输结束前不能读取结果或改动源数据。实际重叠还受硬件和可用资源约束。

**Q.8--同步与异步。** kernel、`cudaMemcpyAsync`、`cudaEventRecord` 通常是相对 CPU 的异步提交。`cudaDeviceSynchronize`、`cudaStreamSynchronize`、`cudaEventSynchronize` 分别等待对应范围。D2H 的 `cudaMemcpy` 返回前会使主机数据可用。传统分配／释放可能引入同步，应放到流水循环之外。`cudaStreamDestroy` 可以在任务未完成时返回，不能当作等待结束。旧解答的二分类表并非完整 API 保证。

**Q.9--两个 stream 的依赖图。** 箭头是执行约束，不是测量时间：

```text
S0 : H2D [0,N[  --> K0 [0,N[  --> D2H [0,N[  ----+
                                                 +--> wait --> CPU check
S1 : H2D [N,2N[ --> K1 [N,2N[ --> D2H [N,2N[ ----+
```

创建和分配先于提交，CPU 请求先于对应 GPU 操作。按题目记号，D2H $\Rightarrow$ 同步结束。互不相交的分段没有跨行数据依赖，但硬件仍可能将操作串行执行。

### 4.14. 拓展--streams Q.10-Q.15：测量并发

**Q.10--程序时间。** 被测操作前调用 `gettimeofday`，提交后等待所有任务，再取结束时间。不等待只能测到提交。换算 `Δt=(sec_fin-sec_debut)+1e-6*(usec_fin-usec_debut)`，并说明是否含分配和传输。不受题目限定时，单调时钟可避免系统时间调整的影响。

**Q.11--所有 kernel 的总时间。** 先 H2D，调用 `cudaDeviceSynchronize`，记 t0，提交所有 kernel，调用 `cudaDeviceSynchronize`，记 t1，最后 D2H。`t1-t0` 是计算阶段的整体时长，不是各 kernel 时间之和。

**Q.12--代价。** 这种计时把传输和计算分为独立阶段，破坏两者的重叠。如果在第二次屏障前提交全部 kernel，它们仍可能相互重叠，因此不能说所有并发都必然消失。

**Q.13--主机时钟测单个 kernel。** 如果只有 `gettimeofday` 和 `cudaDeviceSynchronize`，需要用同步把每个 kernel 单独隔开。kernel 被依次执行，计时因此改变了程序的并发行为。

**Q.14--事件。** 每个 stream s 内用 `start[s]`、`stop[s]` 包围 kernel，等待结束事件后算各自时间。存在重叠时，不能把这些时间相加作为总时间。可用协调 stream，从共同起点测量所有 kernel 的整体范围：

```text
Complete H2D before this kernel-only experiment.
Record global_start in coordination stream.
For every stream s:
    wait(global_start) in s
    record start[s] in s
    launch kernel[s] in s
    record stop[s] in s
For every stream s:
    wait(stop[s]) in coordination stream
Record global_stop in coordination stream.
Wait on global_stop at the host.
Elapsed(global_start,global_stop) = total kernel-phase duration.
Elapsed(start[s],stop[s]) = duration observed for kernel s.
```

stream 间等待使用 `cudaStreamWaitEvent`，时长计算使用 `cudaEventElapsedTime`。共同起点增加了依赖约束，应明确这是“只测 kernel”的阶段。测真实流水线时保留原顺序，另测完整时间。并发时一个 kernel 也可能比单独运行时更慢。

**Q.15--多 stream GEMM。** 把 A、C 按行分包。每个 stream 传输自己的 A；`β≠0` 时也传输 C 初值；计算这些行，再回传 C。所有分包都需要**完整的 B**，因此在流水线前传一次 B，并保证所有 stream 等到它就绪。可使用全局行偏移，或传入偏移指针和局部行数；分块 kernel 仍要处理边界。若直接使用 4.10 的 kernel，`beta=0` 时也须初始化 C，或者把最终写入改成 `beta==0` 分支直接写 `alpha*sum`、不读取 C；没有这一修改就省略 C 的复制，会读取未初始化数据。

用相同输入和计时范围比较合并访问与分块版本。GPU 已饱和时，改善传输不保证加速。旧解答的 P5000 数字不能预测 GH200 的结果。

**应能纸上独立完成：** 主线包括索引、线程数、主机／设备代码分工、带边界判断的 kernel、C 初值、π 的面积比例、真正等待计算完成的计时，以及 ms/GFLOP/s 换算。拓展包括两次屏障、stream 依赖和 SDF 投影方向。
