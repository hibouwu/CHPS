## 2. CUDA 进阶：内存、执行与同步

主要来源：[CM2，98 页 PDF](../CM/APM_Cours2.pdf)，2026 年 9 月 29 日版本。已纳入第 8、53 页新增内容及第 95 页完整签名。本章合并逐步展示的重复幻灯；重新整理的代码用于理解，没有在本次整理中执行。

### 2.1 函数属性与内核结构

来源：CM2，第 3-7 页。

| 声明 | 执行位置 | 本课中的用法 |
|---|---|---|
| `__host__` 或无属性 | CPU | 由主机程序调用的函数 |
| `__device__` | GPU | 由 GPU 代码调用的辅助函数 |
| `__global__` | GPU | 从主机通过 `<<<...>>>` 启动的内核 |
| `__host__ __device__` | CPU 或 GPU | 根据调用位置编译出两个版本 |

普通调用 `__device__` 函数不会启动新网格。`__global__` 内核返回 `void`，通常通过写入传入的缓冲区产生结果。内核启动相对于 CPU 是异步的。第 7 页的历史限制应放在课程使用的编程模型中理解，不应当成适用于所有 CUDA 版本的绝对清单。

```cpp
__global__ void vecAdd(const double *a, const double *b,
                       double *c, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        c[i] = a[i] + b[i];
    }
}
```

当问题规模不是线程块大小的整数倍时，`i < n` 保护最后一个块的边界。不能仅仅为了消除分支就删掉它。

### 2.2 索引、向量类型与 warp 编号

来源：CM2，第 8-9 页，以及 2026 年新增的第 53 页。

| 对象 | 含义 |
|---|---|
| `threadIdx.x/y/z` | 线程在线程块内的坐标 |
| `blockIdx.x/y/z` | 线程块在网格中的坐标 |
| `blockDim.x/y/z` | 一个线程块的尺寸 |
| `gridDim.x/y/z` | 网格的尺寸 |
| `dim3` | 维度类型，省略的分量默认为 1 |
| `int2`、`float4`、`make_int2(x, y)` | 向量类型及构造函数 |

块内线程的线性编号先改变 `x`，再改变 `y`，最后改变 `z`。一个 warp 包含 32 个连续的块内线性编号。

$$
t=x+D_x(y+D_y z),\qquad w=\lfloor t/32\rfloor,\qquad \ell=t\bmod32.
$$

当 `blockDim = (4, 4, 2)` 时，`t = x + 4y + 16z`：`(3,1,0)` 对应 7，`(0,0,1)` 对应 16。整个块有 32 个线程，即一个 warp。第 53 页图中标作“tid (global)”的实际上是块内编号，不包含 `blockIdx`；应以公式消除图上部分坐标绘制的歧义。

向量类型有对齐要求。写成 `float4` 不保证生成一条向量算术指令，也不保证更快；还要看访问方式、地址对齐和最终生成代码。第 8 页新增的是向量化访存示例。

### 2.3 内存层次：可见范围与生命周期

来源：CM2，第 11-19、55-58 页。

| 空间 | 谁能访问 | 需要掌握的生命周期或用途 |
|---|---|---|
| 寄存器 | 一个线程 | 线程私有变量；SM 上的有限资源 |
| 局部内存 | 一个线程 | 私有数组或寄存器溢出；“局部”不等于快速的片上内存 |
| 共享内存 `__shared__` | 同一线程块中的线程 | 每块一份，在线程块结束时失效 |
| 全局内存 | 能访问该分配的线程 | 存放较大数组；通常显式分配和释放 |
| 常量内存 `__constant__` | GPU 读取 | 由主机更新；线程读取共同地址时有利 |
| 纹理／只读缓存 | 依所用机制执行读取 | 特定读取路径及规则；不能代替同步 |

两个线程块即使驻留在同一 SM，也不会自动共享各自的 `__shared__` 数组。网格和线程块是软件组织，SM 是硬件执行资源。简单的局部变量可能放入寄存器，但不能保证所有局部变量都在寄存器中。

同一 warp 读取同一个常量地址时，常量内存比较有利；读取不同地址可能削弱这种优势。缓存容量及缓存与共享内存的物理关系依赖具体架构。

### 2.4 分配与复制：字节数和指针归属

来源：CM2，第 20-24、30-33 页。

```cpp
double *d_a = nullptr;
size_t bytes = n * sizeof(double);
cudaMalloc((void **)&d_a, bytes);
cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice);
cudaMemcpy(h_a, d_a, bytes, cudaMemcpyDeviceToHost);
cudaFree(d_a);
```

`cudaMalloc` 接收指针变量的地址，用来写回分配结果。`cudaMemcpy` 接收数据地址，应传 `d_a`，而不是 `&d_a`。`count` 表示字节数。课件列出的四个方向为 `cudaMemcpyHostToDevice`、`cudaMemcpyDeviceToHost`、`cudaMemcpyHostToHost` 和 `cudaMemcpyDeviceToDevice`。

在课程的独立显存模型中，普通 CPU 循环不能直接解引用 `cudaMalloc` 得到的设备指针。多个计算之间保留 GPU 上的数据，可以减少不必要的传输。

### 2.5 二维、三维分配与 pitch

来源：CM2，第 25-40 页。

`cudaMallocPitch(&ptr, &pitch, width, height)` 分配按要求对齐的各行。`width` 是有效行宽，单位为字节；`pitch` 是相邻两行起点的实际字节距离，包括行末填充；`height` 是行数。pitch 既不是元素个数，也不是单独的填充量。

```cpp
float *d_a = nullptr;
size_t pitch = 0;
size_t widthBytes = width * sizeof(float);
cudaMallocPitch((void **)&d_a, &pitch, widthBytes, height);
cudaMemcpy2D(d_a, pitch, h_a, widthBytes,
             widthBytes, height, cudaMemcpyHostToDevice);
```

在内核中，第 `row` 行的地址应先按字节偏移计算：

```cpp
float *line = (float *)((char *)d_a + row * pitch);
float value = line[col];
```

例如，每行 100 个 `float` 的有效宽度为 400 字节。假设返回的 pitch 为 512 字节，下一行起点就是 `base + 512`，不能写成 `base + 400`。512 只是算例，不是硬件固定规则。

`cudaMemcpy2D` 的源和目标可以有不同 pitch，它只复制每行的有效宽度和指定行数。复制回紧凑主机数组时，本例主机端自己的 pitch 仍然是 400 字节。

三维分配 `cudaMalloc3D` 使用 `cudaExtent`，返回 `cudaPitchedPtr`；在线性分配情形中，宽度以字节为单位。层间距离由行 pitch 和保存的高度推得。`cudaMemcpy3D` 把位置、指针或 CUDA 数组、范围及复制方向封装进 `cudaMemcpy3DParms`。`cudaArray` 是专门的对象，不能当作普通 C 数组指针使用。

### 2.6 统一内存与迁移开销

来源：CM2，第 41-50 页。

课件介绍的统一内存从 CUDA 6.0 引入，可通过 `cudaMallocManaged` 或 `__managed__` 变量让主机与 GPU 使用同一个指针。系统负责管理访问，并根据平台决定如何移动数据。这减少了手动管理，但不保证消除传输开销。

```cpp
int *a = nullptr;
cudaMallocManaged((void **)&a, n * sizeof(int));
kernel<<<grid, block>>>(a);
cudaDeviceSynchronize();
consume_on_cpu(a);
cudaFree(a);
```

`cudaMemAttachGlobal` 与 `cudaMemAttachHost` 表示关联和访问规则，不应简单理解为“物理分配在 GPU”或“物理分配在 CPU”。CPU 读取计算结果前仍要等待 GPU 完成。

第 46-50 页比较了在同一数组上反复交替 GPU → CPU，与把访问分成较大阶段的方式。来回访问可能产生反复迁移。只有程序依赖允许改变顺序时，才可以集中执行：如果每一轮 CPU 都为下一轮 GPU 产生输入，就不能把所有 CPU 操作挪到最后。

### 2.7 全局内存的合并访存

来源：CM2，第 51-54 页；第 53 页新增线程编号说明。

分析一次加载时，应写出同一 warp 各线程执行同一条访存指令时访问的地址。地址紧凑且对齐合适，通常比地址分散需要更少事务。只有单个线程前后两次访问连续，还不足以判断合并访存。

对于按行存储的矩阵：

$$
\operatorname{addr}(r,c)=\operatorname{base}+(rN+c)\,s.
$$

`N` 是列数，`s` 是元素字节数。相邻线程改变 `c`，地址相差 `s`；相邻线程改变 `r`，地址相差 `Ns`。前者通常利于合并，后者可能让事务分散。

第 52-53 页提到 128 字节、32 字节分组，以及每个调度器最多同时执行两条指令。这些是该幻灯的表述，不能当成所有 GPU 的通用常数。精确事务数还依赖架构、访问宽度及地址对齐。

可以先通过合并的全局访存把数据块加载到共享内存，再在线程块中复用或重新排列。适当多加载一些元素有时有利，但要由总成本的降低来证明其合理性。

### 2.8 共享内存与存储体冲突

来源：CM2，第 54-58、98 页。下面的 bank 模型是复习解释，不是课程中的新增测量结果。

当同一次操作中多个不同地址落在同一个 bank，服务可能被串行化，形成存储体冲突。它与全局内存的合并访存是两个不同问题。

在“32 个 bank、每个字为 4 字节”的简化假设下：

$$
\operatorname{bank}(a)=\left\lfloor a/4\right\rfloor\bmod32.
$$

对于 `float tile[32][32]`，用 `tile[threadIdx.x][col]` 读一列，地址间隔为 32 个字，在这个模型中全部映射到同一个 bank。改成带填充的 `float tile[32][33]` 会改变步长并分散这些访问。多个线程读同一个字可能使用广播，不能与“同一 bank 中不同字”的冲突混为一谈。

动态共享内存通过 `extern __shared__` 声明，大小在启动参数的第三项指定。如果多个数组共用一块区域，必须手动保证偏移不重叠，并满足各类型的对齐要求。

### 2.9 寄存器、驻留率与分支分歧

来源：CM2，第 59-60、98 页。下列公式用于解释课件中的资源限制。

SM 的寄存器由其驻留线程使用。每线程寄存器越多，能够同时驻留的块可能越少。每块共享内存、线程数，以及硬件允许的块数和 warp 数也都可能成为限制。

$$
\mathrm{occupancy}=W_{\mathrm{resident}}/W_{\max}.
$$

`W_resident` 表示驻留 warp 数，`W_max` 表示该 SM 允许的最大驻留 warp 数。忽略分配粒度时，可以用以下简化模型给出上界：

$$
B_{\mathrm{resident}}\leq\min\left(B_{\max},\left\lfloor T_{\max}/T_b\right\rfloor,\left\lfloor R_{\mathrm{SM}}/(rT_b)\right\rfloor,\left\lfloor S_{\mathrm{SM}}/S_b\right\rfloor\right).
$$

`T_b` 是每块线程数，`r` 是每线程寄存器数，`S_b` 是每块共享内存；当 `S_b = 0` 时省略共享内存这一项。这个上界并不是完整的运行时间预测器。

`--maxrregcount=N` 限制寄存器数量；`__launch_bounds__(maxThreadsPerBlock, minBlocksPerMultiprocessor)` 告知编译器目标启动配置。把寄存器压得太低，可能溢出到局部内存。更高驻留率不保证内核更快。

分支分歧关注同一 warp 内线程的执行路径。线程走不同路径时，可能降低计算单元利用率。不同 warp 分别走不同分支，并不是同一种分歧。目标是减少代价较高的分歧，而非禁止所有 `if`。

### 2.10 屏障、可见性、`volatile` 与原子操作

来源：CM2，第 57、90、93 页。

| 工具 | 保证或用途 | 不能替代什么 |
|---|---|---|
| `__syncthreads()` | 块内线程会合，并保证相关先前全局／共享内存写入的可见性 | 全网格屏障 |
| `__syncthreads_count/and/or` | 屏障加上对谓词的集体结果 | 块间同步 |
| `atomicAdd`、`atomicExch`、`atomicCAS` 等 | 在支持的类型和作用域内，原子更新目标 | 所有内存操作的一般顺序保证 |
| `volatile` | 对编译器访存处理的约束 | 原子性、线程会合或同步协议 |

同一块的线程需要按一致的控制流程到达屏障。处理数据块时，越界线程可以加载零，再与其他线程一起参与屏障。若块内各线程对边界判断的结果不同，把屏障只放进 `if (i < n)` 就会出问题。

**第 57 页的澄清：** 给数组加 `volatile` 不能修复没有同步的并发读写。fence 可以约束一定范围内的访存顺序，但本身不等待所有线程到齐。这一区别也见 [NVIDIA 的 `volatile` 文档](https://docs.nvidia.com/cuda/cuda-programming-guide/05-appendices/cpp-language-support.html)。

`a[i]++` 包含读、加、写三步，多线程并发时可能丢失更新。`atomicAdd(&a[i], 1)` 保护这次更新，但大量线程争用同一地址可能代价较高。先局部归约再减少原子操作次数是一个方向，浮点计算还要考虑改变加法次序后的舍入差异。支持的类型和位宽依赖 compute capability。

### 2.11 异步执行、stream 与页锁定主机内存

来源：CM2，第 62-89 页。第 68-83 页是在逐步展示同一条时间线。

异步启动意味着 GPU 尚未完成工作时，CPU 已经可以继续。相同 stream 内仍保持操作顺序：输入复制 → 内核 A → 内核 B → 输出复制。顺序来自 stream 语义，CUDA 不会分析指针并自动发现任意跨流数据依赖。

| API | 用途 |
|---|---|
| `cudaStreamCreate/Destroy` | 创建和释放 stream |
| `cudaMemcpyAsync(..., stream)` | 向指定 stream 提交复制 |
| `kernel<<<grid, block, sharedBytes, stream>>>(...)` | 向指定 stream 提交内核 |
| `cudaStreamSynchronize(stream)` | CPU 等待该 stream |
| `cudaDeviceSynchronize()` | 等待当前 GPU 上当前上下文中此前提交的工作 |
| `cudaStreamWaitEvent(stream, event, 0)` | 在 stream 中建立依赖，不要求 CPU 主动等待 |

不同 stream 允许在硬件和资源支持时重叠独立工作。两个 stream 不保证两个内核一定同时运行。默认 stream 可能因具体模式引入额外依赖；清楚推理时应使用显式 stream，并写明依赖关系。

```cpp
cudaMemcpyAsync(d_a, h_a, bytes, cudaMemcpyHostToDevice, copyStream);
cudaEventRecord(ready, copyStream);
cudaStreamWaitEvent(computeStream, ready, 0);
kernel<<<grid, block, 0, computeStream>>>(d_a);
```

这段代码假设 stream、事件与缓冲区已经创建。如果内核使用刚复制的数据，它补足了第 87-88 页跨流示意缺少的依赖。正确 API 名为 `cudaMemcpyAsync`，对应的二维形式是 `cudaMemcpy2DAsync`；不能照抄 `cudaMemCpy` 或 `cudaMemcpyPitchAsync`。

要实现真正的主机-GPU 异步传输及重叠，应使用页锁定主机内存，例如通过 `cudaMallocHost` 分配、`cudaFreeHost` 释放。普通可分页内存可能引入中间拷贝或阻塞。H→D 完成前不能修改或释放源缓冲区；D→H 完成前不能读取或复用目标缓冲区。锁定内存页和等待操作完成，解决的是不同问题。

### 2.12 事件与计时

来源：CM2，第 95 页；2026 年 PDF 中可看到完整函数签名。

```cpp
cudaEvent_t start, stop;
cudaEventCreate(&start);
cudaEventCreate(&stop);
cudaEventRecord(start, stream);
kernel<<<grid, block, 0, stream>>>(d_a);
cudaEventRecord(stop, stream);
cudaEventSynchronize(stop);
float milliseconds = 0.0f;
cudaEventElapsedTime(&milliseconds, start, stop);
cudaEventDestroy(start);
cudaEventDestroy(stop);
```

两个事件圈定 stream 上的一段时间，`cudaEventElapsedTime` 写回毫秒数。等待 `stop` 保证读取时间前这段工作已经完成。以上只是教学示意，为便于阅读省略了错误检查。

CPU 计时器如果只包围 `<<<...>>>`，主要测到的是提交时间。若要从 CPU 测量完整计算，结束读数前必须等待计算完成。始终写清测量范围：内核还是整个程序、是否包含传输、是否包含首次初始化和预热。本资料没有生成任何性能测量结果。

### 2.13 错误检查、数学函数与调试

来源：CM2，第 92-97 页。

检查 CUDA 函数返回的 `cudaError_t`，通过 `cudaGetErrorString` 获取错误描述。内核启动后用 `cudaGetLastError()` 检查启动错误，还要检查后续同步调用，以发现异步执行错误。成功提交不代表没有越界，也不代表数值结果正确。

GPU 上的 `printf` 由到达该语句的各线程执行，可能产生大量输出并扰动计时。为了定位错误加入的同步，需要在最终测量前重新判断是否属于实际流程。

优化数学函数及 `--use_fast_math` 可以加速部分单精度运算，但会改变数值行为。它并不表示“所有双精度操作都能在结果不变的情况下变快”。

### 2.14 答题方法与优化顺序

来源：CM2，第 98 页；练习应用见第 4 节。

1. 明确一个线程负责什么，检查索引边界。
2. 减少 CPU-GPU 传输，把后续仍需使用的数据保留在 GPU。
3. 提供足够线程块来使用各个 SM，但不要把“每个 SM 至少一个块”当成最优配置公式。
4. 写出一个 warp 的访问地址，先看全局合并访存，再看共享内存的 bank conflict。
5. 在能减少总成本的情况下通过共享内存复用数据，并放置必要屏障。
6. 检查寄存器、共享内存、驻留率和分支，然后比较相同范围的执行时间。

每块线程数取 32 的倍数通常是合理起点，但不能只根据核心数决定块大小。DGEMM 的详细优化、循环展开和 tiling 留在对应练习部分；它们在课程日历中的位置见第 4 节。

解释加速时，要把具体修改连到原因：传输字节更少、内存事务更少、复用更多，或重叠更充分。不能仅凭使用了 `__shared__`、增加了 stream，或提高了驻留率，就宣称获得了实测加速。
