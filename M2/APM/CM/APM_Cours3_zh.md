# 硬件加速器体系结构与编程

*第 3 讲：CUDA API 与多 GPU 编程*

> 译文说明：本文件翻译原课件的英文、法文正文，并按阅读需要合并重复展示。已去除页角装饰图、无信息的裁切碎片，以及被完整图覆盖的中间帧；保留必要的架构图、对照图和关键步骤。原始 PDF、原文提取稿与图片文件均保留，可用于逐页对照。未整理的代码片段仍可能含提取错误，不能视为已验证的可运行程序。

> 原提取稿说明：原文由教师 PDF 自动提取，已整理本地图片并校正部分明确的识别错误。幻灯片的逐步展示会造成内容重复；代码和公式请以同名 PDF 为准。

**教师：** Julien Jaeger · julien.jaeger@cea.fr

**原始 PDF：** [APM_Cours3.pdf](APM_Cours3.pdf) · **原文 Markdown：** [APM_Cours3.md](APM_Cours3.md)

## 第 3 讲提纲

- CUDA 的不同 API
- 什么是 CUDA 上下文？
- 多 GPU 编程

## CUDA 的不同 API

![应用、CUDA 库、运行时与驱动的调用层次](Images/cours3_img_001.jpg)

*图：应用、CUDA 库、运行时与驱动的调用层次。*

- CUDA 的不同 API
- 运行时 API（Runtime API）
- 驱动 API（Driver API）
- 什么是 CUDA 上下文？
- 多 GPU 编程

### 运行时 API（1）

- 面向最终用户的 API
- 到目前为止，课件和上机实验中的所有示例都使用运行时 API
- 函数名使用 `cuda` 前缀
- 提供 CUDA 编程的基本函数
- cudaMalloc, cudaFree, cudaMemcpy, …

### 运行时 API（2）

- 高层 API
- 抽象层次较高
- 大多数 CUDA 内部细节对最终用户隐藏，无法直接干预

### 驱动 API（1）

- 底层 API
- 面向专家和库开发者
- 使用时需要更深入的专业知识
- 可以将库内部的 CUDA 开发与程序其他部分的 CUDA 开发隔离
- 尤其是与最终用户编写的代码隔离

### 驱动 API（2）

- 函数名使用 `cu` 前缀
- 提供与运行时 API 类似的功能
- 但需要处理更多细节
- `cudaMalloc` → `cuMemAlloc`
- `cudaMemcpy` → `cuMemcpyDtoH`、`cuMemcpyHtoD`、`cuMemcpyHtoH`、`cuMemcpyDtoD`〔名称按课件保留〕

## CUDA 上下文

### 上下文（1）

- 与某个 GPU 关联的 CUDA 内部结构
- 每次执行需要 GPU 的操作时，CUDA 运行时都会查阅该结构，确定操作涉及哪个 GPU
- 当用户请求关联某个 GPU 时创建
- 前提是对应上下文尚不存在

### 上下文（2）

- 封装 CUDA 程序运行所需的相关对象，例如：
- 独立地址空间中的所有内存分配
- 因此，只有共享同一上下文的计算实体，例如线程，才能共享同一 GPU 地址空间
- CUDA 流
- CUDA 事件

### 上下文（3）

- 两类上下文
- 主上下文与传统上下文
- 与使用的 API 层次有关
- 主上下文：运行时 API 默认使用
- 传统上下文：历史上最早的形式，通过驱动 API 管理

### 主上下文（1）

- CUDA 历史上较晚引入的上下文类型
- 从 CUDA 4.0 开始提供
- 面向同一 GPU 的线程共享该上下文〔本段语境为同一进程内〕
- 某个线程写入 GPU 全局内存的数据，可以被关联到同一 GPU、共享该上下文的其他线程读取
- 当线程首次关联到一个此前尚未使用的 GPU 时，创建新的主上下文
- 原文随后提到：已创建上下文的“栈”中是否已有与该 GPU 关联的上下文〔该句与前句衔接不清，保留其检查意图〕

> 同一进程中，每个 GPU 对应一个主上下文；面向该 GPU 的线程可以共享它。

![一个进程中的线程使用同一 GPU 主上下文](Images/cours3_img_006.jpg)

*图：一个进程中的线程使用同一 GPU 主上下文。*

### 主上下文（3）

- 同一操作系统进程中的多个线程，可以通过不同主上下文关联到不同 GPU

### 主上下文（4）

- 共享同一主上下文的线程，也共享 GPU 上的同一地址空间
- 某个线程分配的缓冲区，可以被使用同一主上下文的其他线程使用。图示：多线程进程
- 主上下文集合

![同一进程使用两个 GPU 的主上下文](Images/cours3_img_010.jpg)

*图：同一进程使用两个 GPU 的主上下文。*

### 传统上下文（1）

- CUDA API 历史上最早的上下文
- CUDA 4.0 之前的默认上下文
- 每个线程私有的上下文〔按课件表述〕
- 调用 `cuCtxCreate(…)` 时创建新上下文
- 不论传统上下文栈或主上下文集合中已经有哪些内容
- 课件称较新 CUDA 版本只提供主上下文。〔译注：这与本讲随后介绍的驱动 API 上下文创建存在冲突；此处保留原文观点，不把它视为已核实的版本结论。〕

### 传统上下文（2）

- 每个线程有一个传统上下文栈
- 保存在 TLS（线程局部存储）中
- 传统上下文栈

![线程局部存储中的传统上下文栈](Images/cours3_img_011.jpg)

*图：线程局部存储中的传统上下文栈。*

- 系统调度器
- GPGPU 0
- GPGPU 1
- NUMA 1

### 传统上下文（3）

- 用户级线程带来的问题：需要手动管理上下文栈
- 多线程进程
- 传统上下文栈

![用户级线程与上下文栈的管理](Images/cours3_img_013.jpg)

*图：用户级线程与上下文栈的管理。*

- 系统调度器
- 操作系统
- GPGPU 0
- GPGPU 1
- NUMA 0
- NUMA 1

### 传统上下文（4）

- 优先于主上下文
- 先检查传统上下文，再检查主上下文〔本段沿用课件模型〕
- 传统上下文栈

![主上下文与传统上下文栈并存](Images/cours3_img_014.jpg)

*图：主上下文与传统上下文栈并存。*

## 多 GPU 编程

- 第 3 讲提纲

### 在 CUDA 中选择 GPU

- 可以通过两种方式选择后续函数使用哪个 GPU：
- 运行时 API：`cudaSetDevice(…)`
- 驱动 API：`cuCreateCtx(…)`〔原文如此；后文使用 `cuCtxCreate`〕

### 运行时 API：cudaSetDevice

- host__cudaError_t cudaSetDevice (int device)
- 设置后续 GPU 执行所使用的设备。

### 参数

- device
- 当前主机线程应在哪个设备上执行设备代码。

```text
Utilisation de cudaSetDevice
Int main()
{
...
    cudaMalloc(&d_a, ...) // malloc on the default device (device 0)
    cudaSetDevice(1); // Select device 1 for the following CUDA functions
    cudaMalloc(&d_b, ...) // malloc on device 1
...
```

### cudaSetDevice：细节（1）

- `cudaSetDevice` 检查是否已有上下文与目标 GPU 关联〔以下是课件给出的流程描述〕
- 如果存在传统上下文栈
- 则检查其中是否有与目标 GPU 关联的上下文
- 如果有，将其放到栈顶并选中它
- 如果没有，创建与目标设备关联的新传统上下文
- 如果不存在传统上下文栈，则检查是否已有与目标 GPU 关联的主上下文
- 如果有，选择该上下文
- 如果没有，创建相应的主上下文

### cudaSetDevice：细节（2）

- 传统上下文优先于主上下文
- 先检查并选择传统上下文，再考虑主上下文

### cudaSetDevice：细节（3）

- 如果请求的设备不存在，会怎样？
- 例如，节点只有两个设备，却向 `cudaSetDevice` 传入 3？
- 课件称不会报错，也不会发生段错误
- 课件称后续 CUDA 函数会在默认设备，即设备 0 上执行。〔译注：这两条是课件原有说法，不能作为程序错误处理的依据；应检查 API 返回值。〕

### 运行时 API：cudaGetDeviceCount

- host device__cudaError_t cudaGetDeviceCount (int *count)

- 返回支持计算的设备数量。

### 参数

- `count`
- 课件描述为返回计算能力大于或等于 2.0 的设备数量〔此版本条件按原文保留〕

```text
cudaSetDevice usage
int main()
{
...
    cudaMalloc(&d_a, ...);
    cudaGetDeviceCount(&nbGPUs); // Get the number of available devices
    cudaSetDevice(1%nbGPUs); // A mod on the number of GPUs allows always choosing n existing GPU
    cudaMalloc(&d_b, ...); //
...
}
```

### 驱动 API：cuCtxCreate

### CUresult cuCtxCreate (CUcontext *pctx, unsigned int flags, CUdevice dev)

- 创建 CUDA 上下文。
- 新上下文被压入调用线程的上下文栈栈顶

### 参数

- `pctx`：返回新上下文的句柄
- `flags`：上下文创建标志
- `dev`：要为哪个设备创建上下文

### 驱动 API：cuCtxPopCurrent

- CUresult cuCtxPopCurrent (CUcontext *pctx)
- 从当前 CPU 线程的上下文栈中弹出当前 CUDA 上下文。

### 参数

- `pctx`
- 返回上下文句柄〔原文称“新的上下文句柄”；具体指代需按 API 定义核对〕

### 驱动 API：cuCtxPushCurrent

- CUresult cuCtxPushCurrent (CUcontext ctx)
- 将一个上下文压入当前 CPU 线程的上下文栈。
- 参数
- `ctx`
- 要压栈的上下文

```text
Utilisation de cuCtxCreate
Int main()
{
...
cudaMalloc(&d_a, ...) // malloc on the default device (device 0)
cuCtxCreate(&myctx, flags, 1); // Select device 1 for the following CUDA operations
cudaMalloc(&d_b, size) // malloc on device 1
cuMemAlloc(&d_c, size) // malloc on device 1
...
```

### 使用 cuCtxPopCurrent 和 cuCtxPushCurrent

```text
Int main()
{
    cuCtxCreate(&myctx, flags, 1);
    cudaMalloc(&d_a, ...); // malloc on device 1
    cuCtxPopCurrent(&tmpctx); // « pop » myctx from the top of the stack
    cudaMalloc(&d_b, ...); // malloc on the previous device
    cuCtxPushCurrent(tmpctx); // put back the device 1 context a the top of the context stack
    cudaMalloc(&d_c, ...); // malloc on device 1
}
```

### cuCtxCreate：细节

- `cuCtxCreate` 为目标 GPU 创建一个新上下文
- 不考虑当前上下文栈中已有的内容
- 因此，栈中可能有多个与同一 GPU 关联的传统上下文
- 课件称调用 `cudaSetDevice` 会选择首先遇到的、与目标 GPU 关联的上下文

### 驱动 API：其他函数

- CUresult cuCtxGetCurrent (CUcontext *pctx)
- 返回绑定到调用 CPU 线程的 CUDA 上下文。
- 不会弹出该上下文；它仍位于栈顶

### 驱动 API：其他函数

- CUresult cuCtxGetCurrent (CUcontext *pctx)
- 返回绑定到调用 CPU 线程的 CUDA 上下文。
- CUresult cuCtxGetDevice (CUdevice *device)
- 返回当前上下文对应的设备 ID。
- CUresult cuCtxSetCurrent (CUcontext ctx)
- 将指定 CUDA 上下文绑定到调用 CPU 线程。
- 可以理解为一种上下文替换：弹出栈顶，再将 `ctx` 放到栈顶〔课件中的类比〕

- 传统上下文的细粒度管理（1）

- 如何避免为同一 GPU 创建多个传统上下文：
- 手动检查传统上下文栈
- 创建新上下文前，依次弹出栈内上下文进行检查
- 每一步调用 `cuCtxGetDevice()`，获取当前栈顶上下文对应的设备 ID

### 传统上下文的细粒度管理（2）

- 如果找到目标 GPU 对应的上下文，先将其弹出，再依次压回其他已弹出的上下文，最后把目标上下文放到栈顶〔原文最后一步写作 pop，按此段操作意图译为放回栈顶〕
- 如果没有找到目标 GPU，则调用 `cuCtxCreate`
- 也可以通过 `cudaSetDevice` 交给运行时 API 处理〔沿用课件说法〕
- 先为线程创建一个传统上下文
- 课件称此后每次调用 `cudaSetDevice`，都会在传统上下文栈中查找匹配项，或者创建符合要求的新传统上下文
- 第 3 讲提纲
- 什么是 CUDA 上下文？
- 多 GPU 编程
- 在 CUDA 中选择要使用的 GPU
- UVA
- MPI+CUDA
- OpenMP + CUDA
- NCCL

```text
Using same address on different address space
Int main()
{ ...
    cudaMalloc(&d_a, ...) //
    cudaSetDevice(1); //
    cudaMemcpy(&d_a, ...) //
...
}
```

### 在不同地址空间中使用同一地址值

```text
Int main()
{ ...
    cudaMalloc(&d_a, ...) //
    cudaSetDevice(1); //
    cudaMemcpy(&d_a, ...) //
...
}
```

- 这种情况下会发生什么？

```text
Using same address on different address space
Int main()
{ ...
    cudaMalloc(&d_a, ...) // malloc on the default device (device 0)
    cudaSetDevice(1); // Select device 1 for the next CUDA calls
    cudaMemcpy(&d_a, ...) // Error! d_a is allocated on device 0, and doesn't have meaning for device 1
...
```

### 这种情况下会发生什么？

```text
Using same address on different address space
int main()
{ ...
    cudaMalloc(&d_a, ...) // malloc on the default device (device 0)
    cudaSetDevice(1); // Select device 1 for the next CUDA calls
    cudaMemcpy(&d_a, ...) // Error! d_a is allocated on device 0, and doesn't have meaning for device 1
...
```

- 这是引入 UVA 之前的情况

### UVA：统一虚拟寻址

- UVA 随 CUDA 4.0 引入
- UVA 即统一虚拟寻址
- 主机与不同 GPU 的内存彼此独立，原本具有不同地址空间
- UVA 将这些内存呈现在同一个虚拟地址空间中
- 每一部分占据各自的地址范围
- 因此，主机或设备能够正确识别来自其他设备的内存地址
- 可以判断某个地址属于哪个设备

![UVA 示例：切换设备后仍使用原设备地址](Images/cours3_img_036.jpg)

*图：UVA 示例：切换设备后仍使用原设备地址。*

- 这是引入 UVA 之前的情况

```text
What happens with UVA
int main()
{ ...
    cudaMalloc(&d_a, ...) // malloc on the default device (device 0)
    cudaSetDevice(1); //
    cudaMemcpy(&d_a, ...) //
...
}
```

### 引入 UVA 之前的情况

```text
What happens with UVA
int main()
{ ...
    cudaMalloc(&d_a, ...) // malloc on the default device (device 0)
    cudaSetDevice(1); // Select device 1 for the next CUDA calls
    cudaMemcpy(&d_a, ...) //
...
}
```

- 这是引入 UVA 之前的情况

```text
What happens with UVA
int main()
{ ...
    cudaMalloc(&d_a, ...) // malloc on the default device (device 0)
    cudaSetDevice(1); // Select device 1 for the next CUDA calls
    cudaMemcpy(&d_a, ...) // Le runtime reconnaît que d_a est une adresse sur le GPU 0, et va donc copier les données sur ce GPU
...
```

### 引入 UVA 之前的情况

### UVA：统一虚拟寻址

- 可以向当前未关联的 GPU 复制数据，或从该 GPU 复制数据
- CUDA 运行时能够识别地址对应的位置
- 不再需要显式指定复制方向
- CudaMemcpyHostToDevice
- CudaMemcpyDeviceToHost…

### cudaMemcpyDefault

- 运行时自行确定复制方向
- 什么是 CUDA 上下文？
- 多 GPU 编程
- 在 CUDA 中选择要使用的 GPU
- UVA
- MPI+CUDA
- OpenMP + CUDA
- NCCL

```text
MPI+CUDA (1)
GPU
Int main()
{
    MPI_Init(...)//
...
    cudaMalloc(...); // All the MPI processes will target the same
GPU
...
    MPI_Finalize(...)
}
```

```text
MPI+CUDA (2)
GPU
Int main()
{
    MPI_Init(...)//
...
    cudaSetDevice (1); // Assign GPU 1
    cudaMalloc(...); // All MPI processes did the same assignment, so all MPI processes will target the same GPU 1
...
    MPI_Finalize(...)
}
```

```cpp
MPI+CUDA (3)
GPU
Int main()
{
    MPI_Init(...)//
    MPI_Comm_rank(MCW, &rank);
    cudaSetDevice(rank); // Assign a unique GPU to each MPI processus, as long as rank<nb GPU.
    cudaMalloc(...); //
...
    MPI_Finalize(...)
}
```

```text
MPI+CUDA (4)
Int main()
{
    MPI_Init(...)//
    MPI_Comm_rank(MCW, &rank);
    cudaGetDeviceCount(&nbGPU);
    cudaSetDevice(rank % nbGPU); // Assign a GPU to each MPI process following a Round-Robin distribution.
    cudaMalloc(...);
...
    MPI_Finalize(...)
}
```

### 轮转分配 GPU（1）

- 尽可能将 MPI 进程分散到所有可用 GPU 上
- 不一定能优化 GPU 利用率
- 每个 MPI 进程交给 GPU 的计算负载可能不同
- MPI 进程不一定关联到离自己最近的 GPU
- NUMA 效应可能产生影响

### 轮转分配 GPU（2）

- 关联到同一 GPU 的不同 MPI 进程，并不共享同一地址空间
- 例如，一个 MPI 进程写入 GPU 内存的数据，另一个 MPI 进程可能无法直接读取
- 课件将共享地址空间的条件表述为：多个 MPI 进程共享同一上下文
- 基于进程的 MPI：不能直接做到；无法把 GPU 上下文广播给其他 MPI 进程，因为 CUDA 上下文是不透明对象
- 用户无法获取其内部大小和内容
- 基于线程的 MPI：使用主上下文即可〔按本讲同一进程的语境理解〕
- 什么是 CUDA 上下文？
- 多 GPU 编程
- 在 CUDA 中选择要使用的 GPU
- UVA
- MPI+CUDA
- OpenMP + CUDA
- NCCL

```text
OpenMP+CUDA (1)
Int main()
{
    #pragma omp parallel
    {
    rank = omp_get_thread_num();
    cudaGetDeviceCount(&nbGPU);
    cudaSetDevice(rank % nbGPU); // Each thread chooses its GPU. The GPU current context is only modified for the current thread. Shared memory and address space for the threads attached to the same GPU (thanks to primary context).
    cudaMalloc(...);
    }
}
```

```text
OpenMP+CUDA (2)
Int main()
{
    #pragma omp parallel
    {
    rank = omp_get_thread_num();
    cudaGetDeviceCount(&nbGPU);
    cuCtxCreate(rank % nbGPU); // Create and assign a new context independent for each thread. Available GPUs are associated in Round-Robin fashion. GPU memory is not shared between threads.
    cudaMalloc(...);
    }
}
```

```text
OpenMP+CUDA (2)
GPU
Int main()
{
    #pragma omp parallel
    {
    rank = omp_get_thread_num();
    cudaGetDeviceCount(&nbGPU);
    cuCtxCreate (rank % nbGPU);
    cudaMalloc(&d_a,...);

    cudaGetDeviceCount(&nbGPU);
    cuCtxCreate (rank % nbGPU);
    cudaMemcpy(&d_a,...); // Error! Even if it is the same GPU, context are different with means memory address spaces are different.
    }
}
```

### 轮转分配 GPU（3）

- 线程与 CUDA 的组合，也会遇到与 MPI + CUDA 类似的问题
- 无法保证充分利用 GPU
- 分配给线程的 GPU 不一定是最近的 GPU
- 关联到同一 GPU 的线程也不一定共享地址空间
- 这取决于使用的上下文

### 轮转分配 GPU（4）

- 主上下文集合
- 多线程进程
- 主上下文 0
- GPGPU 0
- 主上下文 1
- GPGPU 1

![多个线程与 GPU 主上下文的对应关系](Images/cours3_img_046.jpg)

*图：多个线程与 GPU 主上下文的对应关系。*

- 系统调度器
- 操作系统
- GPGPU 0
- GPGPU1
- NUMA 1

### MPI + OpenMP + CUDA（1）

- 对 GPU 而言，接近最佳的情况……
- 每个可用 GPU 对应一个 MPI 进程

![每个 GPU 对应一个 MPI 进程](Images/cours3_img_047.jpg)

*图：每个 GPU 对应一个 MPI 进程。*

### MPI + OpenMP + CUDA（2）

### 使用所有可用 GPU

- 同一 MPI 进程中的所有线程，可以共享 GPU 上的同一地址空间
- 可以在 OpenMP 并行区域之前完成内存分配与复制，再由各线程启动内核处理数据
- 使用运行时 API 即可实现
- 不必使用驱动 API 中的复杂功能
- 也适用于用户级线程

### MPI + OpenMP + CUDA（3）

- 注意：课件称同一 MPI 进程内的 CUDA 调用会串行化〔应结合下文默认流的使用情境理解〕
- 需要用流来避免这种依赖：为每个线程关联一个流
- 独立流之间不必串行，因此两个各只占用一部分 GPU 资源的线程所提交的工作可能并发执行
- 注意：课件将 GPU 可用流数量写为 16 或 128，取决于 GPU。〔译注：这里应进一步区分软件流数量与硬件并发执行上限，原文未作区分。〕

### MPI + OpenMP + CUDA（4）

### 对 GPU 而言的最佳情况

- 每个可用 GPU 对应一个 MPI 进程，并配合使用流

![每个 GPU 对应一个 MPI 进程，并为线程分配流](Images/cours3_img_048.jpg)

*图：每个 GPU 对应一个 MPI 进程，并为线程分配流。*

```text
MPI+OpenMP+CUDA (5)
GPU
Int main()
{
    MPI_Init(...)//
    MPI_Comm_rank(MCW, &mpirank);
    cudaGetDeviceCount(&nbGPU);
    cudaSetDevice(mpirank % nbGPU); // modulo nécessaire pour associer chaque rang au bon GPU en multi-noeud
    #pragma omp parallel
    {
    omprank = omp_get_thread_num();
    cudaMalloc(..., omprank % 16); // appel à cudaMalloc sur le stream n° (omprank %16).
    }
    MPI_Finalize(...)
}
```

### MPI + OpenMP + CUDA（6）

- 为获得较好性能，应考虑 GPU 的位置，将 MPI 进程绑定到靠近对应 GPU 的 CPU，以减少 NUMA 效应
- 可能无法完全避免 NUMA 效应
- 例如：两个 CPU 插槽，但两块 GPU 都连接到同一个插槽

### MPI + OpenMP + CUDA（7）

- 注意：最利于 GPU 使用的 MPI 进程／线程布局，不一定能获得最佳 CPU 性能。
- 注意：外部库可能操作 GPU 或 CUDA 上下文，从而破坏原先优化好的绑定关系。
- CUDA 的不同 API
- 什么是 CUDA 上下文？
- 多 GPU 编程
- 在 CUDA 中选择要使用的 GPU
- UVA
- MPI+CUDA
- OpenMP + CUDA
- NCCL

### NCCL（1）

- NCCL，读作“Nickel”：NVIDIA 集合通信库
- 目的：支持同一节点内多个 GPU 之间的点对点通信和集合通信
- 课件还描述了通过 NVIDIA Mellanox InfiniBand 网络互连的跨节点 GPU 通信〔此处不表示只支持该网络；本讲结尾列出了其他通信方式〕

### NCCL（2）

### 与 MPI 很相似

- 一个通信组（课件称 clique）包含参与某次集合通信的 GPU，不一定包含全部 GPU
- 为通信组中的每个 GPU 初始化一个通信器
- 可以为每个 GPU 分别调用初始化函数
- 这种初始化包含同步等待，因此需要并行进行
- 可由不同 MPI 进程或不同线程执行
- 也可以通过一次整体调用完成

### 初始化函数

- ncclResult_t ncclCommInitRank (ncclComm_t* comm, int nGPUs, ncclUniqueId cliqueId, int rank);
- 初始化对应的 rank
- 参数
- `comm`：通信器
- `nGPUs`：通信组中的 GPU 数量
- `cliqueId`：通信组的唯一标识
- 一个 rank 调用 `ncclGetUniqueId()`，然后将其广播，例如使用 `MPI_Bcast`
- `rank`：当前 GPU 在通信组中的唯一编号

### 初始化函数

- ncclResult_t ncclCommInitAll (ncclComm_t* comms, int nGPUs, int* devList);
- 一次初始化 `nGPUs` 个 GPU 对应的通信器
- 参数
- `comms`：通信器数组，每个 GPU 对应一个
- `nGPUs`：通信组中的 GPU 数量
- `devList`：指定各 rank 对应的 CUDA 设备

```text
ncclCommInitRank (MPI)
GPU
Int main()
{
...
MPI_Init();
MPI_Comm_rank(MCW, &rank);
ncclCommInitRank(&gpucomm, nGPUs, cUID, getGPU(rank)); // Seuls les rangs choisis initialisent leur communicateur GPU.
MPI_Finalize();
...
}
```

```text
ncclCommInitRank (OpenMP)
Int main()
{
...
    #pragma omp parallel
    {
    rank = omp_get_thread_num();
    ncclCommInitRank(&gpucomm, nGPUs, cUID, getGPU(rank)); //Only the chosen ranks must initialize their GPU communicator
    }
...
}
```

### ncclCommInitRank

- 注意：如果多个 MPI 进程或线程关联到同一个 GPU，用户必须保证此处每个 GPU 只执行一次 `ncclCommInitRank` 调用〔限定于课件讨论的通信组初始化〕。
- 课件强调编号应对应参与通信的 GPU，而不是直接采用 MPI 进程／线程编号。〔译注：不要据此混淆 CUDA 设备 ID 与通信器 rank；应结合前面的参数说明。〕

```text
ncclCommInitAll (MPI)
int clique = {0,3,1,5}
Int main()
{
    ncclComm_t gpucomm [4]; // Need as many nccl communicators than GPUs in the clique
    MPI_Init();
    MPI_Comm_rank(MCW, &rank);
    if(rank == constante)
    ncclCommInitAll(&gpucomm, nGPUs, clique); // Only call this collective initialization one time
    MPI_Finalize();
}
```

```text
ncclCommInitAll (OpenMP)
int clique = {0,3,1,5}
Int main()
{
    ncclComm_t gpucomm [4]; // Need as many nccl communicators than GPUs in the clique
    ncclCommInitAll(&gpucomm, nGPUs, clique); // Only call this collective initialization one time
    #pragma omp parallel
    {
    ...
    }
}
```

### NCCL（3）

- 集合通信函数的原型与 MPI 集合通信很相似
- 每个 GPU 都必须调用相同的函数，并使用相互匹配的参数〔原文写作相同参数〕
- NCCL 集合通信操作采用异步执行方式
- 各次调用可以由同一个 MPI 进程或线程发出〔具体调用组织方式参照原示例〕
- 选择 GPU，然后调用函数

### 集合通信函数：all-reduce

- 原 PDF 第 95 页并列比较 NCCL 与 MPI 的 all-reduce 函数签名。下列文字按幻灯片转录；其中 NCCL 参数名 `sendoff` 为原页所写。
- **NCCL**

```text
ncclResult_t ncclAllReduce(
    void* sendoff,
    void* recvbuff,
    int count,
    ncclDataType_t type,
    ncclRedOp_t op,
    ncclComm_t comm,
    cudaStream_t stream);
```

- **MPI**

```text
int MPI_Allreduce(
    void* sendbuf,
    void* recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm);
```

```text
Collective communications (MPI 1)
int clique = {0,3,1,5}
Int main()
{
    MPI_Init();
    MPI_Comm_rank(MCW, &rank);
    ... // Initialization of nccl comms
    if(inClique(getGPU(rank)) // Either the chosen ranks realize the calls
    {
    ncclAllReduce(&sendbuf, &recvbuf, count, type, op, gpucomm[getGPU(rank)]);
    }
    MPI_Finalize();
}
```

### 集合通信（MPI 2）

```text
int clique = {0,3,1,5}
Int main()
{
    MPI_Init();
    MPI_Comm_rank(MCW, &rank);
    ... // Initialization of nccl comms
    if(rank==0) // Or only one rank realizes all the GPU calls
    for(i=0; i<nbGPUs; i++)
    {
    if(inClique (i))
    {
    ncclAllReduce(&sendbuf, &recvbuf, count, type, op, gpucomm);
    }
    }
    MPI_Finalize();
}
```

### 集合通信（MPI 3）

```text
// If all GPUs are concerned, no need for selection/check: simpler code
Int main()
{
    MPI_Init();
    MPI_Comm_rank(MCW, &rank);
    ... // Initialization of nccl comms

    if(rank==0)
    {
    for(i=0; i<nbGPUs; i++)
    {
    ncclAllReduce(&sendbuf, &recvbuf, count, type, op, gpucomm);
    }
    }
    MPI_Finalize();
}
```

```text
Utilisation de ncclCommInitAll (OpenMP 1)
int clique = {0,3,1,5}
Int main()
{
    ... // Initialization of nccl comms
    #pragma omp parallel
    {
    rank = omp_get_thread_num();
    if (inClique (getGPU(rank)) // Either the chosen ranks realize the calls
    {
    ncclAllReduce(&sendbuf, &recvbuf, count, type, op, gpucomm);
    }
    }
}
```

### 使用 ncclCommInitAll（OpenMP 2）

```text
int clique = {0,3,1,5}
Int main()
{
    ... // Initialization of nccl comms
    for(i=0; i<nGPUs, i++)
    {
    if(inClique (i) // Or only one thread realizes all the GPU calls, inside ou outside of the OpenMP parallel region
    {
    ncclAllReduce(&sendbuf, &recvbuf, count, type, op, gpucomm);
    }
    }
    #pragma omp parallel
    {
    }
}
```

### NCCL 2.19.3 的功能情况

### 集合通信

- 广播（Broadcast）
- 全收集（All-Gather）
- 归约（Reduce）
- 全归约（All-Reduce）
- 归约后分发（Reduce-Scatter）

### 点对点通信

- 发送／接收（Send / recv）
- 一对多分发（Scatter）
- 多对一收集（Gather）
- 全交换（All-to-all）
- 邻居交换（Neighbor exchange）

### 主要特性

- 支持单节点与多节点
- 主机端 API
- 异步、非阻塞接口
- 支持多线程和多进程
- 支持原地操作与非原地操作
- 自动检测拓扑
- 支持 NVLink 与 PCIe/QPI*
- 支持 InfiniBand verbs、libfabric、RoCE 和 IP Socket 等节点间通信方式
