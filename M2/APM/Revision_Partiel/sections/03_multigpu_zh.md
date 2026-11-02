## 3. CUDA API、上下文与多 GPU 编程

本章对应 [CM3](../CM/APM_Cours3.pdf)。课件最后一页讲的是 NCCL 2.19.3，不是后续所有版本的完整功能表。

### 3.1 Runtime API 与 Driver API（CM3 第 4-10 页）

| 比较项 | Runtime API | Driver API |
|---|---|---|
| 抽象层次 | 较高层，前面的课程示例主要使用它 | 控制更显式，可用于某些库开发 |
| 前缀 | `cuda` | `cu` |
| 分配 | `cudaMalloc` | `cuMemAlloc` |
| 复制 | `cudaMemcpy` 加复制方向 | 如 `cuMemcpyHtoD`、`cuMemcpyDtoH` |
| 上下文 | 通常由 runtime 管理 | 可以显式管理 |
| 返回类型 | `cudaError_t` | `CUresult` |

两套 API 都访问同一个 GPU。Driver API 不保证更快，它的价值是更明确地控制资源和上下文。混合使用时，需要检查当前上下文，以及所用对象属于哪个上下文。

### 3.2 上下文代表什么（CM3 第 13-25 页）

上下文组织某个 GPU 的 CUDA 状态，包括常见的内存分配、地址空间、stream、事件等资源。分析一个指针时，要知道其分配归属和访问权限，不能只看 GPU 编号。

| 情形 | 在课程模型中应掌握的共享关系 |
|---|---|
| 同一进程的多个 CPU 线程使用同一主上下文 | 这些线程可以共享该上下文中的分配 |
| 一个进程使用多个 GPU | 每个使用的 GPU 有对应主上下文 |
| 多个 MPI 进程使用同一 GPU | 不会自动获得同一个地址空间 |
| 同一 GPU 上有两个显式上下文 | GPU 物理上相同，不代表其中分配可以自动互换使用 |

课程把主上下文介绍为 CUDA 4.0 开始提供：同一进程中面向同一个 GPU 的线程共享它。当前上下文则与主机线程有关，两个线程可以各自使用不同的当前 GPU。

**第 22 页的澄清：** 不应把“较新版本只剩主上下文”记成现行规则。Driver API 仍然提供 `cuCtxCreate`。显式上下文也并非天然“永远只属于一个线程”，其线程关联可以操作。参见 [NVIDIA 上下文管理文档](https://docs.nvidia.com/cuda/cuda-driver-api/group__CUDA__CTX.html)。

### 3.3 选择 GPU 并检查错误（CM3 第 28-38 页）

`cudaGetDeviceCount(&count)` 返回当前进程可见的 GPU 数量。`cudaSetDevice(device)` 为调用它的主机线程选择 GPU，后续分配、stream、事件和内核启动都应关联到预期 GPU。

```cpp
int count = 0;
cudaError_t status = cudaGetDeviceCount(&count);
if (status != cudaSuccess || count == 0) {
    return 1;
}
int device = local_rank % count;
status = cudaSetDevice(device);
if (status != cudaSuccess) {
    return 1;
}
```

该片段假设已经定义 `local_rank`。只有 `count > 0` 时取模才有效。映射必须依据实际分配且对进程可见的 GPU，不能假定看得到所有物理设备编号。

**第 36 页的纠正：** 非法编号可能返回 `cudaErrorInvalidDevice`，不能期待系统默默改用 GPU 0。第 31-35 页还描述了历史上下文栈搜索，这不能作为通用契约：官方文档把 `cudaSetDevice` 描述为给当前调用线程绑定选定 GPU 的主上下文。参见 [NVIDIA 设备管理文档](https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__DEVICE.html)。

切换当前 GPU 不会迁移已经分配的数据，也不会自动等待另一个 GPU 上先前提交的工作完成。

### 3.4 使用 Driver API 操作上下文（CM3 第 39-49 页）

| 函数 | 需要理解的效果 |
|---|---|
| `cuCtxCreate` | 创建新上下文并使其成为当前上下文；不会查找并复用已有分配 |
| `cuCtxGetCurrent` | 查询当前上下文，不将其移除 |
| `cuCtxGetDevice` | 查询当前上下文对应的 GPU |
| `cuCtxPushCurrent` | 将上下文压入调用线程的栈，使其成为当前上下文 |
| `cuCtxPopCurrent` | 移除当前上下文，并返回被移除的上下文 |
| `cuCtxSetCurrent` | 为调用线程显式关联上下文 |
| `cuCtxDestroy` | 不再使用相关资源后，销毁显式创建的上下文 |

推理示例：线程起初使用 A，压入 B 后，依赖当前上下文的操作就使用 B；弹出 B 后恢复 A。`cuCtxPopCurrent` 写回的是 B 的句柄，不是 A。即使指定相同 GPU，两次创建也可能得到两个不同上下文。

幻灯中三个参数的创建函数签名有版本适用范围，编译时应以所用 toolkit 的签名为准。考试更应掌握操作效果和资源归属，而非复制不完整片段。本段和表格的澄清与 [Driver API 官方文档](https://docs.nvidia.com/cuda/cuda-driver-api/group__CUDA__CTX.html)一致。

### 3.5 UVA 与统一内存是两个概念（CM3 第 51-62 页）

统一内存见 CM2 第 41-50 页。

课程把 UVA 的引入时间列为 CUDA 4.0。在支持的平台上，它把主机和各 GPU 的地址放入统一虚拟地址布局。因此，即使当前 GPU 改变，也可以根据地址识别其对应分配和位置。

| 概念 | 提供什么 | 不意味着什么 |
|---|---|---|
| UVA | 统一识别地址 | 所有物理内存合并为一块 |
| `cudaMemcpyDefault` | 在 UVA 环境中根据指针推断复制方向 | 复制本身被消除 |
| 统一内存 `cudaMallocManaged` | 管理 CPU/GPU 共享分配的访问和数据移动 | 没有迁移、没有竞争或无需同步 |
| 点对点访问 | 支持且已授权时访问另一个 GPU 的内存 | 只要有 UVA 就一定能访问 |

地址能被识别，不代表任意处理器都能直接解引用。应分别回答：“分配在哪里？”“谁能访问？”“数据何时准备好？”

第 51-59 页的 `cudaMemcpy` 采用简写。真实调用应传数据指针 `d_a`，而不是指针变量本身的地址 `&d_a`。

### 3.6 P2P 访问与 GPU 间传输

这是与 UVA 相关的补充澄清，CM3 没有按以下流程详细展开。它用于区分地址识别与访问授权。

```cpp
int canAccess = 0;
cudaDeviceCanAccessPeer(&canAccess, 0, 1);
if (canAccess) {
    cudaSetDevice(0);
    cudaDeviceEnablePeerAccess(1, 0);
}
```

此片段先查询 GPU 0 是否能访问 GPU 1，然后从 GPU 0 激活这个方向；它不会自动激活反方向。片段假设设备编号有效，并为展示机制省略错误检查。

`cudaMemcpyPeer` 或 `cudaMemcpyPeerAsync` 表达两个 GPU 分配之间的数据复制，有效路径取决于拓扑和可用能力。P2P 不表示“数据已经到达”，也不保证远端访问与本地访问同样便宜。生产数据、复制数据和消费数据之间仍需建立顺序。参见 [NVIDIA 对等设备内存访问文档](https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__PEER.html)。

### 3.7 MPI 与 GPU 分配（CM3 第 64-69 页）

如果所有进程都使用默认 GPU，它们可能全部挤到 GPU 0。让所有进程执行同一个 `cudaSetDevice(1)`，也不会分散工作。课程提出轮转分配：

$$
\operatorname{device}(r)=r\bmod N_{\mathrm{GPU}}.
$$

在单节点上，它把各 rank 分配到可见 GPU。在多节点上，应结合节点内 local rank 和实际分配 GPU 的可见性推理；全局 MPI rank 本身不能完整说明节点内映射。如果每个进程只看得到分配给自己的一个 GPU，那么各进程中的设备本地编号都可能是 0。

轮转不保证负载均衡，因为不同 rank 的计算量可能不同。它也不保证 CPU、主机内存、GPU 和网络接口之间具有最佳 NUMA 位置关系。

MPI 进程具有独立地址空间。只发送一个指针数值或上下文句柄，不能共享实际分配。交换数据需要专门机制，例如通信、适配实现对 GPU buffer 的支持，或显式进程间共享机制。这不意味着任意 MPI 都能直接接收 GPU 指针。

### 3.8 主机端 OpenMP 与主上下文共享（CM3 第 71-75 页）

这里是 OpenMP 创建 CPU 线程，再调用 CUDA；OpenMP `target` 卸载是另一种机制。

```cpp
#pragma omp parallel
{
    int tid = omp_get_thread_num();
    int device = tid % gpuCount;
    cudaSetDevice(device);
    cudaStream_t stream;
    cudaStreamCreate(&stream);
    kernel<<<grid, block, 0, stream>>>(buffers[device]);
    cudaStreamSynchronize(stream);
    cudaStreamDestroy(stream);
}
```

这一示意假设 `gpuCount > 0`、每个 GPU 都有正确的 buffer，且各线程工作相互兼容。如果多个线程写同一个 buffer，需要划分区域或增加同步；共享上下文本身不能使并发写入正确。

每个主机线程应在发起 CUDA 操作前选择自己的 GPU。同一进程中使用同一个主上下文的线程，可以操作同一组分配。反之，如果每次都重新创建独立显式上下文，之前的指针可能无法在新的当前上下文中使用。

stream 组织 GPU 上的工作顺序，OpenMP 同步还负责 CPU 侧的交换和访问顺序。两个层次的同步不能互相替代。

### 3.9 MPI + OpenMP + CUDA：组织方式与拓扑（CM3 第 76-82 页）

课程给出“每个 GPU 一个 MPI 进程，进程中多个主机线程配合 stream”的组织方式，便于共享分配和重叠工作。它是一个起点，不是所有程序达到最高性能的证明。

第 78-80 页需要谨慎理解：16 或 128 不是所有 GPU 可创建 stream 数量的通用上限，`cudaMalloc(..., stream)` 也不是 `cudaMalloc` 的函数签名。在已讨论的示例中，stream 传给内核启动或 `cudaMemcpyAsync`。

分析映射时应沿着数据路径看：CPU 核 → NUMA 内存 → GPU → 其他 GPU 或网络。一个 GPU 对某些核心近，对另一些核心远；最适合 GPU 的位置可能与 CPU 的最佳位置冲突。外部库也可能修改当前 device 或上下文，不能假定调用任何库以后这些状态都保持不变。

### 3.10 NCCL：通信域、rank 与初始化（CM3 第 84-92 页）

NCCL 提供 GPU 间通信。这里的“clique”指参与一个通信域的 GPU 集合，可以只包含部分 GPU。必须区分三个编号：MPI rank、CUDA 设备本地编号，以及 NCCL 通信域内 rank。

| 函数 | 组织方式 |
|---|---|
| `ncclGetUniqueId` | 生成并分发给参与者的共同标识 |
| `ncclCommInitRank` | 每个参与者先选 GPU，再初始化自己的 rank |
| `ncclCommInitAll` | 单个进程按 `devList` 初始化一组本地 GPU |

若 `devList = {0, 3, 1, 5}`，NCCL rank 0、1、2、3 分别对应本地 GPU 0、3、1、5。`ncclCommInitRank` 的最后一个参数是在 `0..nranks-1` 内唯一的 NCCL rank，不一定是 GPU 编号；这澄清了第 90 页的歧义。

参与者使用相同标识。在 MPI 中，可以由一个进程创建，再通过 `MPI_Bcast` 等方式广播。初始化可能等待其他参与者，因此调用需要协调：由多个线程或进程参与；如果一个线程管理多个 GPU，则使用成组调用。

在本课使用的模型中，同一个 GPU 不应对应同一通信域中的多个 rank。因此，多个线程使用同一 GPU 时，应指定实际进行初始化的参与者，这也对应第 90 页的提醒。参见 [NCCL 通信域创建文档](https://docs.nvidia.com/deeplearning/nccl/user-guide/docs/usage/communicators.html)。

这些区别，特别是 `ncclCommInitAll` 的单进程适用范围，已与 [NCCL 通信域官方文档](https://docs.nvidia.com/deeplearning/nccl/user-guide/docs/api/comms.html)核对。在一个进程中创建的句柄，不会因为广播了它的数值就能在其他进程中使用。

### 3.11 集体通信、AllReduce 与异步执行（CM3 第 93-100 页）

| 操作 | 结果 |
|---|---|
| Broadcast | 根 rank 的数据发送给所有参与者 |
| Reduce | 合并各参与者的贡献，结果保存在根 rank |
| AllReduce | 合并各参与者的贡献，每个参与者都得到结果 |
| AllGather | 每个参与者都收集所有参与者的贡献 |
| ReduceScatter | 先合并，再把结果按块分配给参与者 |

对 `P` 个参与者做求和，每个参与者得到：

$$
y_j=\sum_{r=0}^{P-1}x_{r,j}.
$$

`ncclAllReduce(sendbuff, recvbuff, count, datatype, op, comm, stream)` 使用 GPU buffer，`count` 是元素数，不是字节数。参与者必须以一致的集体调用顺序，执行参数相容的操作。各自本地指针可以不同；“相同参数”不表示所有进程中的指针数值必须相同。

操作被提交到 stream。主机函数返回，并不代表 CPU 已经能立刻读取结果。应通过 stream 依赖或适当等待，保护后续消费者。

当单线程管理多个 GPU 时，幻灯中的普通 `for` 循环需要补上成组调用语义：

```cpp
ncclGroupStart();
for (int i = 0; i < nLocalGPUs; ++i) {
    ncclAllReduce(send[i], recv[i], count, ncclFloat,
                  ncclSum, comms[i], streams[i]);
}
ncclGroupEnd();
```

这里假设通信域、buffer 和 stream 都已初始化。应在 `ncclGroupEnd` 之后等待各 stream，不能在组中途等待。这样可避免第一项调用等待尚未提交的其他参与者。参见 [NCCL 成组调用文档](https://docs.nvidia.com/deeplearning/nccl/user-guide/docs/usage/groups.html)。

### 3.12 期中复习易错点（CM3 第 22、36、78-80、84、90、101 页）

1. **同一 GPU 不代表同一上下文。** 要检查进程、当前上下文和分配归属。
2. **UVA 不等于统一内存。** 地址识别、访问授权和数据移动要分别分析。
3. **同一上下文不代表没有竞争。** 读写仍需要正确顺序。
4. **切换 device 不会移动数据。** 必须保留 buffer、stream 和事件的归属信息。
5. **NCCL rank、MPI rank 和 CUDA device 可以不同。** 改错前先画出明确映射表。
6. **异步不代表完成。** 用 stream、事件和等待连接生产、通信与消费。

第 84 页用 InfiniBand 介绍多节点，而第 101 页明确列的是 NCCL 2.19.3，还提到了 RoCE 和 IP sockets。因此不能记成“NCCL 多节点必须使用 InfiniBand”。末页把集体通信、点对点交换及可由点对点构造的通信模式一起列出，不意味着每种模式都有一个独立的集体通信 API。

本章代码是推理材料，不是已执行程序，也不是扩展性测量结果。回答性能问题时，还要检查数据量、通信频率、计算不均衡及机器拓扑。
