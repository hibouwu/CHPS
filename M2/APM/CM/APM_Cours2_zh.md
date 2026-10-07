# 硬件加速器体系结构与编程

*第 2 讲：进阶 CUDA*

> 译文说明：本文件翻译原课件的英文、法文正文，并按阅读需要合并重复展示。已去除页角装饰图、无信息的裁切碎片，以及被完整图覆盖的中间帧；保留必要的架构图、对照图和关键步骤。原始 PDF、原文提取稿与图片文件均保留，可用于逐页对照。未整理的代码片段仍可能含提取错误，不能视为已验证的可运行程序。

> 原提取稿说明：原文由教师 PDF 自动提取，已整理本地图片并校正部分明确的识别错误。幻灯片的逐步展示会造成内容重复；代码和公式请以同名 PDF 为准。

**教师：** Adrien Roussel · adrien.roussel@cea.fr

**原始 PDF：** [APM_Cours2.pdf](APM_Cours2.pdf) · **原文 Markdown：** [APM_Cours2.md](APM_Cours2.md)

> 版本同步：已对照 2026 年 9 月 29 日导出的 98 页 PDF，补入第 8、53 页的新增内容及第 95 页完整显示的计时函数签名。保留已有课堂补充；以下课件页码均指新版 PDF。

<!-- classroom:provenance -->
**课堂补充说明**

已将第二讲转录中有助于理解和实践的解释补入对应位置。现有转录从函数属性讨论的中途开始；“课堂讲解”是内容归纳，“补充说明”是为澄清术语、前提或口述简化所加的解释。来源行号指归档转录；自动转录中的 CUDA 名称和中文译词有误，阅读时以本讲义中的技术标识符为准。
<!-- /classroom:provenance -->

## 概览

### 编程语言

- 关键字
- 可用函数
- 示例
- 内核优化
- 多 GPU
- CUDA 编程

### 计算内核

- 以 C99 标准为基础
- 存在一些限制
- 增加了一些扩展

### 扩展

- 关键字
- 预定义变量
- 函数

### 参阅《CUDA C Programming Guide》附录 B

### 基本内核

### 内核的基本语法

- 不返回值的函数，返回类型为 `void`
- 使用函数属性，声明该函数在设备上执行
  - `__global__`
- 输入参数

### 示例

```cpp
__global__ void vecAddKernel( double *a,
    double *b, double *c, int N ) {
    int i ;
    i = blockIdx.x * blockDim.x + threadIdx.x ;
    if (i<N) {
    c[i] = a[i]+b[i];
    }
}
```

### 扩展：关键字

- 定义了新的关键字
- 分类
- 函数属性
- 变量属性
- 类型
- 一组预定义变量
- 使用新的数据类型

### 函数属性

- 在函数声明和定义中添加关键字
- 添加在返回类型与函数名之间
- 在设备上执行、可以从主机调用的函数
  - `__global__`
- 专门用于主机或设备的函数属性，可以组合使用
  - `__host__`
  - `__device__`
- 默认等同于 `__host__`

<!-- classroom:qualifiers -->
**课堂讲解：同一个辅助函数怎样在两端复用**

老师用 `min` 举例：如果 CPU 与 GPU 都需要同一段计算逻辑，可以使用 `__host__ __device__`，避免维护两份函数体。编译器分别为两端生成适用的版本，函数体也必须满足相应端的限制。

**补充说明：** `__device__` 辅助函数由设备代码普通调用，不会因此启动一个新内核；本课从主机发起的内核调用使用 `__global__` 和 `<<<...>>>`。内核返回类型为 `void`，计算结果通常写到传入指针所指向的内存中，再由主机在完成同步后读取。双重属性也不意味着一次调用会同时在 CPU 和 GPU 执行。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 1–23 行。*
<!-- /classroom:qualifiers -->

### 函数限制

### 声明为 `__global__` 的函数

- 返回类型为 `void`
- 调用时需要指定执行配置，如线程块数、每块线程数等
- 异步调用
- 课件称无法获取其函数指针
- 在设备上执行的函数
- 不允许静态变量
- 不允许可变数量的参数
- 递归受限，仅适用于声明为 device 的函数〔原文此处括号未闭合〕

### 数据类型

### 新增类型

- 向量
- 多维整数
- 向量类型
- 基本类型加元素数量
- 例如：`int2`、`float4`
- 需要遵守对齐规则
- 提供相应的构造函数
- 例如：int2 make_int2(int $\textrm { x } ,$ int y);

**新版课件参考示例（第 8 页）：** [CUDA Pro Tip: Increase Performance with Vectorized Memory Access（通过向量化访存提高性能）](https://developer.nvidia.com/blog/cuda-pro-tip-increase-performance-with-vectorized-memory-access/)。

<!-- classroom:vectors -->
**课堂讲解：向量类型会改变每个线程处理的数据量**

`float4` 把四个 `float` 分量放在一个对象中。若原来每线程处理一个元素，改为每线程处理四个元素，就要同步调整索引、工作量和末尾不足四个元素的处理；仅修改类型名称并不够。

**补充说明：** 这种类型有助于表达成组访存，但不保证所有计算都会变成一条向量指令。是否生成合适的加载／存储，还取决于地址对齐、实际使用的分量以及编译结果。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 25–56 行。*
<!-- /classroom:vectors -->

### 数据类型（续）

### 三维整数类型

- dim3
- 等价于向量类型 `uint3`
- 通过字段 `x`、`y` 和 `z` 访问各分量
- 默认初始化为 1
- 用于表示 CUDA 网格、线程块和线程的坐标与维度。

### 示例

```text
dim3 a ;
```

```text
a.x = 4 ;
```

## 内存管理

### GPU 的存储层次

GPU 包含多种存储资源，其访问机制、作用范围和管理方式不同。原课件逐步叠加全局内存、常量内存、共享内存、纹理、只读数据和寄存器；这里保留完整图。

![GPU 存储层次与全局内存分配、传输](Images/cours2_img_024.jpg)

*图：GPU 存储层次与全局内存分配、传输。*

从计算实体的角度看：

| 计算实体 | 对应的存储资源 |
|---|---|
| 线程 | 私有寄存器与局部内存 |
| 线程块 | 块内线程共享的共享内存 |
| 网格中的线程 | 可访问设备全局内存 |

![单个线程与局部内存](Images/cours2_img_016.jpg)

*图：单个线程与局部内存。*

![线程块与共享内存](Images/cours2_img_017.jpg)

*图：线程块与共享内存。*

全局内存的分配与主机／设备传输分别通过 `cudaMalloc`、`cudaMemcpy` 等接口完成。

<!-- classroom:scope -->
**课堂讲解：从“谁能访问”理解存储层次**

寄存器保存单个线程的私有状态；普通 `__shared__` 数组由一个线程块内的线程共同使用；全局内存用来保存跨块使用的数据和内核输出。要把共享内存中的结果交回主机，通常先由线程写到全局内存，再进行设备到主机复制。

**补充说明：** 同一 SM 可以同时驻留多个线程块，只要资源允许；各块仍各有一份共享内存，不能因为落在同一 SM 就直接访问另一块的普通共享数组。网格与线程块是程序的逻辑组织，SM 是执行它们的硬件资源，二者并非一一对应。这里按课件的普通线程块模型讨论。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 64–140 行。*
<!-- /classroom:scope -->

### GPU 上的基本内存分配

- host device__ cudaError_t cudaMalloc (void ** ptr, size_t size)
- 在设备上分配内存
- 在设备全局内存中分配 `size` 字节
- 传入用于接收地址的指针 `ptr`
- CUDA 运行时负责分配内存并获取该内存区域的地址
- 将分配得到的地址返回并存入 `ptr` 指向的位置
- 这个地址不能直接在主机端解引用！

### GPU 上的高级内存分配

- host__ cudaError_t cudaMallocPitch (void ** ptr, size_t * pitch, size_t width, size_t height)
- 在设备上分配二维内存
- 至少分配 `width × height` 字节
- 内存分配需要满足对齐约束
- 这可能影响二维和三维内存分配
- 每一行都必须正确对齐
- 可能需要在行末添加填充
- 一行实际占用的字节数，即宽度加填充，通过变量 `pitch` 返回

<!-- classroom:pitch -->
**课堂讲解：pitch 是一整行的跨度**

二维数组的有效行宽与相邻两行起始地址的距离可能不同。`cudaMallocPitch` 的 `width` 用字节表示，`height` 用行数表示；返回的 `pitch` 包含有效数据和行末填充。

**补充说明（算例）：** 假设每行 100 个 `float`，有效行宽是 400 字节；若返回 `pitch = 512`，第二行从基址后 512 字节开始，不能按 400 字节寻址。第 `r` 行先用字节指针加上 `r * pitch`，再转换为元素指针。二维复制时，源、目标各自使用自己的 pitch，而复制宽度仍是有效的 400 字节。512 只是示例，不能假定所有分配都返回这个值，也不能把 pitch 当作填充量本身。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 139–172 行。*
<!-- /classroom:pitch -->

### GPU 上的高级内存分配

### host cudaError_t cudaMalloc3D ( struct cudaPitchPtr * pitchedDevPtr,

### Struct cudaExtent extent)

- 指定至少需要分配的字节数
- 结构体 `cudaExtent` 包含三个字段
- size_t depth
- size_t height
- size_t width
- 至少分配 `depth × height × width` 字节

### GPU 上的高级内存分配

- host cudaError_t cudaMalloc3D ( struct cudaPitchPtr * pitchedDevPtr,
- 获取设备上已分配内存的地址
- 结构体中还保存一些与对齐约束有关的信息
- `size_t size` 和 `size_t ysize`：课件称其对应分配时传入的 `extent` 结构体中的 `width` 和 `height` 字段〔字段名按原文保留〕
- `size_t pitch`：课件用来描述包含必要填充后的实际分配跨度〔使用时需核对 API 中 pitch 的具体含义〕
- struct cudaExtent extent)

### GPU 上的基本内存复制

- _host__ cudaError_t cudaMemcpy
- (void * dst, const void * src,
- size_t count, enum cudaMemcpyKind kind)
- 从 `src` 指向的内存向 `dst` 指向的内存复制 `count` 字节

### GPU 上的基本内存复制

- host__ cudaError_t cudaMemcpy
- (void * dst, const void * src,
- size_t count, enum cudaMemcpyKind kind)
- 从 `src` 指向的内存向 `dst` 指向的内存复制 `count` 字节
- `kind` 指定复制方向
- cudaMemcpyHostToDevice
- cudaMemcpyDeviceToHost
- cudaMemcpyHostToHost
- cudaMemcpyDeviceToDevice
- cudaMemcpy(d_a, h_a, ( sizeof(int) * 1024), cudaMemcpyHostToDevice);

```text
Copie avancée sur le GPU
__host__ cudaError_t cudaMemcpy2D
(void * dst, size_t dpitch,
const void * src, size_t spitch,
size_t width, size_t height,
enum cudaMemcpyKind kind)
• Copie width x height octets de la mémoire pointée par src vers la mémoire pointée par dst
```

### GPU 上的高级内存复制

```c
__host__ cudaError_t cudaMemcpy2D (void * dst, size_t dpitch, const void * src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind)
```

- 从 `src` 指向的内存向 `dst` 指向的内存复制 `width × height` 字节
- 可以分别指定源内存区域与目标内存区域的行跨度，以处理填充
- 与 `cudaMallocPitch` 分配的内存区域兼容
- cudaMemcpy2D(d_a, pitch, h_a, ( sizeof(int) * 64), ( sizeof(int) * 64), 16, cudaMemcpyostToDevice);

$$
\begin{array}{c} \text {Copie avancée sur le GPU} \\ \hline \text {GPU} \\ \hline \text {\_host\_cudaError\_t cudaMemcpy3D (const struct} \\ \text {\_cudaMemcpy3DParms * p)} \end{array}
$$

### GPU 上的高级内存复制

- host__ cudaError_t cudaMemcpy3D (const struct cudaMemcpy3DParms * p)
- struct cudaArray *srcArray;
- struct cudaPos srcPos
- (size_t x, size_t y, size_t z)
- struct cudaPitchedPtr srcPtr;
- struct cudaArray *dstArray;
- X struct cudaPos dstPos;
- struct cudaPitchedPtr dstPtr;
- struct cudaExtent extent;
- enum cudaMemcpyKind kind;

### 二维代码示例

```c
__global__ void plus_one(int * a, int size, size_t pitch)
{
    int y = blockIdx.x;
    int x = threadIdx.x;
    int rp = (int)(pitch / sizeof(int));

    int test = blockIdx.x * blockDim.x + threadIdx.x;

    if (test < size)
    {
    a[y * rp + x] += 1;
    }
}

int main (int argc, char * argv[])
{
    int * h_a = NULL;
    h_a = (Int *)malloc(sizeof(int) * 1024);

    int i;
    for (i = 0; i < 1024; i++)
    {
    h_a[i] = 10;
    }

    int * d_a = NULL;
    size_t pitch;
    cudaMallocPitch(&d_a, &pitch, (sizeof(int) * 64), 16);

    cudaMemcpy2D(d_a, pitch, h_a, (sizeof(int) * 64), (sizeof(int) * 64), 16, cudaMemcpyHostToDevice);

    plus_one<<<16, 64>>>(d_a, 1024, pitch);

    cudaMemcpy2D(h_a, (sizeof(int) * 64), d_a, pitch, (sizeof(int) * 64), 16, cudaMemcpyDeviceToHost);

    for (i = 0; i < 1024; i++)
    {
    printf("%d]", h_a[i]);
    }
    printf("\n");

    return 0;
```

### 其他高级函数

### 分配

- cudaMallocArray
- cudaMalloc3DArray

### 复制

- cudaMemcpyToArray
- cudaMemcpy2DToArray
- cudaMemcpyFromArray
- cudaMemcpy2DFromArray
- cudaMemcpyArrayToArray
- cudaMemcpy2DArrayToArray

### 自动内存管理（统一内存）

### CUDA 6.0 引入

- 在主机与设备之间提供统一的内存视图
- 主机与一个或多个 GPU 使用同一个指针
- 根据主机或设备对数据的使用情况自动进行传输

### 自动内存管理（统一内存）

### 申请自动管理内存的两种方式

- host__ cudaMallocManaged( void** devPtr, size_t size, unsigned int flags)
- cudaMemAttachGlobal
- 任意设备均可访问这块内存
- cudaMemAttachHost
- 课件描述为设备均不能访问〔这里说明的是该标志对应的初始关联状态〕
- 在变量声明中使用 `managed` 属性〔原文省略了下划线〕

<!-- classroom:managed -->
**课堂讲解：统一指针省去显式搬运，仍需管理依赖**

老师强调统一内存让程序更容易表达，但数据在哪里、何时被访问，仍然影响性能。使用 `cudaMallocManaged` 后，同一指针可以供主机和设备使用；CPU 要读取内核刚写出的结果，仍需先确认内核完成。

**补充说明：** `cudaMemAttachGlobal` 与 `cudaMemAttachHost` 描述关联／访问规则，不宜理解为“指定最初物理分配到 GPU 或 CPU”。底层迁移与访问机制依赖平台。统一内存不自动消除 CPU 与 GPU 对同一数据的竞争，也不保证每次访问都没有传输开销。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 187–208 行。*
<!-- /classroom:managed -->

### 统一内存：示例

- cudaMallocManaged
- 默认标志：`cudaMemAttachGlobal`

```c
__global__ void AplusB(int *ret, int a, int b) {
    ret[threadIdx.x] = a + b + threadIdx.x;
}

int main() {
    int *ret;
    cudaMallocManaged(&ret, 1000 * sizeof(int));
    AplusB<< 1, 1000 >>>(ret, 10, 100);
}
```

- `managed` 属性
- device managed int ret[1000]; global void AplusB(int a, int b){ ret[threadIdx.x] = a + b + threadIdx.x;
- int main() { ÀplùsB<<< 1, 1000 >>>(10, 100); cudaDeviceSynchronize() ;

### 自动内存管理（统一内存）

- CUDA 6.0 引入
- 在主机与设备之间提供统一的内存视图
- 主机与一个或多个 GPU 使用同一个指针
- 根据主机或设备对数据的使用情况自动进行传输

### 自动内存管理（统一内存，续）

- CUDA 6.0 引入
- 在主机与设备之间提供统一的内存视图
- 主机与一个或多个 GPU 使用同一个指针
- 根据主机或设备对数据的使用情况自动进行传输
- 注意 CPU 与 GPU 之间反复迁移数据造成的性能问题！

```c
cudaMallocManaged(&a, 100000*sizeof(int));
for(i=0; i<100000; i++) a[i] = i;
gettimeofday(&start1, NULL);
for(j=0; j<2000; j++)
{
    kernel<<<100,1000>>>(a);
    cudaDeviceSynchronize();
    function(a);
}
gettimeofday(&stop1, NULL);

gettimeofday(&start2, NULL);
for(j=0; j<2000; j++)
{
    kernel<<<100,1000>>(a);
    cudaDeviceSynchronize();
}
for(j=0; j<2000; j++)
{
    function(a);
}
gettimeofday(&stop2, NULL);
```

- 统一内存性能问题示例

### 示例

- 重复调用 `kernel` 和 `function` 2000 次，更新同一个数组：`_host__ void function(int * a)`
- int i; for(i=0; i< 100000; i++)
- 统一内存性能问题示例

**示例：**

- 重复调用 `kernel` 和 `function` 2000 次，更新同一个数组
- 交替执行：重复 2000 次“kernel + function”
- _host__ void function(int * a)

```text
int i;
for(i=0; i< 100000; i++)
```

```c
cudaMallocManaged(&a, 100000*sizeof(int));
for(i=0; i<100000; i++) a[i] = i;

gettimeofday(&start1, NULL);
for(j=0; j<2000; j++)
{
    kernel<<<100,1000>>>(a);
    cudaDeviceSynchronize();
    function(a);
}
gettimeofday(&stop1, NULL);

gettimeofday(&start2, NULL);
for(j=0; j<2000; j++)
{
    kernel<<<100,1000>>(a);
    cudaDeviceSynchronize();
}
for(j=0; j<2000; j++)
{
    function(a);
}
gettimeofday(&stop2, NULL);
```

### 统一内存性能问题示例

### 示例

- 重复调用 `kernel` 和 `function` 2000 次，更新同一个数组
- 交替执行：重复 2000 次“kernel + function”
- 分组执行：先执行 2000 次 `kernel`，再执行 2000 次 `function`
- 测得的时间：
- _host__ void function(int * a)
- int i; for(i=0; i< 100000; i++)

```c
cudaMallocManaged(&a, 100000*sizeof(int));
for(i=0; i<100000; i++) a[i] = i;

gettimeofday(&start1, NULL);
for(j=0; j<2000; j++)
{
    kernel<<<100,1000>>>(a);
    cudaDeviceSynchronize();
    function(a);
}
gettimeofday(&stop1, NULL);

gettimeofday(&start2, NULL);
for(j=0; j<2000; j++)
{
    kernel<<<100,1000>>(a);
    cudaDeviceSynchronize();
}
for(j=0; j<2000; j++)
{
    function(a);
}
gettimeofday(&stop2, NULL);
```

```c
cudaMallocManaged(&a, 100000*sizeof(int));
for(i=0; i<100000; i++) a[i] = i;
gettimeofday(&start1, NULL);
for(j=0; j<2000; j++)
{
    kernel<<<100,1000>>>(a);
    cudaDeviceSynchronize();
    function(a);
}
gettimeofday(&stop1, NULL);

gettimeofday(&start2, NULL);
for(j=0; j<2000; j++)
{
    kernel<<<100,1000>>(a);
    cudaDeviceSynchronize();
}
for(j=0; j<2000; j++)
{
    function(a);
}
```

### 统一内存性能问题示例

### 示例

- 重复调用 `kernel` 和 `function` 2000 次，更新同一个数组
- 交替执行：重复 2000 次“kernel + function”
- 分组执行：先执行 2000 次 `kernel`，再执行 2000 次 `function`
- 测得的时间：
- _global__ void kernel(int * a)
- _host__ void function(int * a)
- int i; for(i=0; i< 100000; i++)
- a[i]++;

<!-- classroom:migration -->
**课堂讲解：为什么 CPU、GPU 交替访问可能很慢**

课件比较两种顺序：重复“GPU 更新 → CPU 更新”，以及先集中执行 GPU 更新，再集中执行 CPU 更新。前一种顺序可能让同一批数据反复迁移；后一种让数据在同一端被连续复用，更容易摊薄搬运成本。

**补充说明：** 这个比较揭示的是访问顺序的影响，不能把任意程序都重排成后一种。如果 CPU 每轮产生的数据正是下一轮 GPU 的输入，就必须保留依赖。课件中的耗时属于该实验，不代表统一内存固定慢多少倍；`cudaDeviceSynchronize()` 的作用是等待完成，也不能简单等同于“执行一次数据复制”。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 196–208 行。*
<!-- /classroom:migration -->

### 内存访问

- 一个 warp 内同步执行
- 某个线程执行内存加载时，其他线程也可能受到拖累
- 多个同时发出的内存访问可能被串行处理
- 访问延迟越长，就需要越多线程来隐藏延迟
- 可采用的优化
- 合并访存（load coalescing）
- 避免存储体冲突（bank conflict）

### 合并访存

- 访问全局内存
- 同一 warp 内的线程并发发出访问请求
- 同一 warp 内的所有线程在同一时刻执行同一条指令
- 课件按每组 128 字节，即缓存行大小，描述请求的串行处理
- 访问地址连续时可以得到优化！

### 合并访存：warp 内的线程编号

*新版课件新增内容，第 53 页。*

![4 × 4 × 2 线程块中的线程编号](Images/cours2_2026_warp_thread_numbering.png)

- 一个 warp 包含 32 个线程。
- 一个 SM 中有多个 warp scheduler。
  - 课件称一个 warp scheduler 最多可同时执行两条指令。
- 课件用一次事务最多加载 128 字节来解释访存合并。
  - 同一 warp 的线程访问连续数据时，访存请求可以合并，从而减少内存加载事务。
  - 对分散访问，课件按所需的 32 字节数据块解释额外的加载。

**读图说明：** 图中 `blockDim = (4, 4, 2)`，共有 32 个线程。块内线性编号为 `threadIdx.x + 4 * threadIdx.y + 16 * threadIdx.z`，因此 x 先变化，再是 y、z。例如 `(3, 1, 0)` 对应编号 7，`(0, 0, 1)` 对应编号 16。图中的 `tid (global)` 标签实际展示了这个块内的线性编号，没有包含 `blockIdx` 项。

**适用范围：** 上述“两条指令”“128 字节”“32 字节”保留课件的描述；调度器发射能力及访存事务粒度需要结合具体架构与访问类型理解，不能一概当成所有 GPU 的固定规则。下面的课堂解释进一步说明线程编号与访问地址的关系。

<!-- classroom:coalescing -->
**课堂讲解：线程编号为什么会影响访存效率**

老师把合并访存与第一讲的编号规则联系起来：块内线程按 x 最快变化的顺序线性化，相邻的线性编号组成 warp。因此，设计二维数组访问时，要观察同一 warp 在同一条访存指令中访问的地址。

**补充说明（对照）：** 对行主序矩阵，令相邻线程读取同一行的相邻列，地址通常更紧凑；若相邻线程跨行读取同一列，地址间隔会变成一整行。后者可能需要更多内存事务。课件的“128 字节”是解释用的粒度，实际事务取决于架构、访问宽度与对齐，不能据此断言一个 warp 的加载永远只产生一笔事务。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 211–223 行。*
<!-- /classroom:coalescing -->

### 合并访存与共享内存

- 使用共享内存

- 需要声明驻留在共享内存中的缓冲区
- 在内核开始时传入数据
- 在内核结束时更新全局内存
- 优化：利用最初从全局内存到共享内存的传输，实现连续地址访问
- 即使并非所有数据都需要用到，也可以考虑这样做！
- 注意存储体冲突

<!-- classroom:tiling -->
**课堂讲解：先协作搬入，再重复使用**

共享内存的收益来自块内协作：线程先以合适的全局访问模式装入一块数据，再反复使用，减少重复访问全局内存。只把数据搬入共享内存却不复用，可能增加搬运和同步成本。

**补充说明：** 全局内存的合并访存与共享内存的 bank conflict 是两个问题。共享内存冲突要看同一次访问中各线程的地址如何映射到 bank；不能只靠“地址对齐”判断是否有冲突。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 226–235 行。*
<!-- /classroom:tiling -->

### 变量属性（1）

### 驻留在设备上的变量

- `device`〔原文省略下划线〕
- 默认位于全局内存中，所有线程均可访问，生命周期覆盖整个应用
- 驻留在常量内存中的变量
- `constant`〔原文省略下划线〕
- 生命周期覆盖整个应用
- 不能在设备端定义〔按课件原文表述〕

<!-- classroom:constant -->
**补充说明：常量内存与纹理访问需要区分**

转录把纹理与常量内存混在一起解释。`__constant__` 声明与 `cudaMemcpyToSymbol` 更新对应的是常量符号；纹理访问使用自己的资源绑定和读取接口。它们可能都涉及只读访问和缓存，但不能把两者当作同一机制，也不能把 SM 内的缓存等同于全部数据的物理存储位置。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 253–265 行。*
<!-- /classroom:constant -->

### 变量属性（2）

### 共享内存中的变量

- `shared`〔原文省略下划线〕
- 同一线程块内的所有线程共享
- 每个线程块有一份副本
- 生命周期与线程块一致

### 默认情况下，设备函数中声明的变量存储在寄存器中

### volatile 变量

- 对并发访问的公共数据进行同步
- 并发访问示例

```cpp
// myArray is an array of non-zero integers
// located in global or shared memory
__global__ void MyKernel(int* result) {
    int tid = threadIdx.x;
    int ref1 = myArray[tid] * 1;
    myArray[tid + 1] = 2;
    int ref2 = myArray[tid] * 1;
    result[tid] = ref1 * ref2;
}
```

- `result[tid]` 的值是多少？

```text
✿ myArray[tid] est dans un registre, donc ref1==ref2
```

- 课件称声明为 `volatile` 后即可，或加入内存栅栏（memory fence）〔译注：此处保留课件说法，不能据此把 volatile 当成完整的线程同步机制〕
- 但这并不能保证执行顺序

<!-- classroom:volatile -->
**补充说明：volatile 不能修复这里的数据竞争**

课堂用相邻线程读写数组来解释可见性，但“加上 `volatile` 就能得到正确值”不能作为编程规则。上例中，一个线程读 `myArray[tid]`，另一个线程可能正写这个位置，缺少执行顺序约束，因而不能给出一个可靠的固定结果。

`volatile` 不提供线程间同步或原子性，内存栅栏本身也不会让其他线程等待。如果算法要求所有线程先读取旧值、然后更新、最后读取新值，应明确划分阶段，并在适当作用域内同步；跨块时还需另外设计协调方式。不能用打印结果恰好正确来证明它没有竞争。

核对依据：[CUDA 对 volatile 的限制](https://docs.nvidia.com/cuda/archive/13.0.0/cuda-c-programming-guide/index.html#volatile-qualifier)。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 238–244 行。*
<!-- /classroom:volatile -->

### 变量限制

- 动态管理共享内存变量

```c
extern __shared__ char array[];
__device__ void func() {
    short* array0 = (short*)array;
    float* array1 = (float*)&array[128];
    int* array2 = (int*)&array[64];
}
```

- 如果动态使用共享内存，需要手动管理其中的数据布局，并遵守对齐规则

### 寄存器分配

- 每个计算内核都需要使用多个寄存器
- 使用量取决于内核中的指令，以及编译器进行的变换和优化
- 寄存器分配
- 但需要注意
- 寄存器数量有限
- 同一流式多处理器上执行的线程共享寄存器资源
- 这与线程数有什么关系？

### 寄存器分配

- 可以通过选项向编译器指定寄存器数量上限
- maxrregcount=N
- 通过属性向编译器提供最大线程数和线程块数量的提示

```c
__global__ void
    _launch bounds (maxThreadsPerBlock,
    _minBlocksPerMultiprocessor)
MyKernel(...)
{
    ...
}
```

<!-- classroom:registers -->
**课堂讲解：寄存器用量与驻留线程数之间的取舍**

SM 的寄存器总量有限。每个线程占用更多寄存器时，同一 SM 可能容纳更少的线程或线程块，隐藏延迟的能力也可能受到影响。因此，老师把寄存器用量与并行度一起讨论。

**补充说明：** `__launch_bounds__(maxThreadsPerBlock, minBlocksPerMultiprocessor)` 给出最大块大小及期望的最少驻留块数，编译器据此调整寄存器使用；参数不是寄存器数量。直接限制寄存器可用 `--maxrregcount=N`，但压得过低可能导致溢出到局部内存，或增加指令数。驻留率高也不保证运行更快，应结合资源用量与实测时间判断。

核对依据：[CUDA Launch Bounds](https://docs.nvidia.com/cuda/archive/13.0.0/cuda-c-programming-guide/index.html#launch-bounds)。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 247–268 行。*
<!-- /classroom:registers -->

## 异步执行

### CUDA 中的异步执行

### CUDA 内核是异步的

- 内核调用返回时，内核不一定已经执行完毕
- 调用内核时，它不一定立即开始执行
- 可以理解为向 GPU 发出了执行内核的命令
- 内核可能稍后才执行
- 要确认内核已经执行完毕，需要进行设备同步

<!-- classroom:async -->
**课堂讲解：提交完成、执行完成与并发是三件事**

启动内核后，主机通常可以继续做其他工作，这只说明提交对主机是异步的。同一流中的任务仍按顺序执行：例如“复制输入 → 内核 A → 内核 B → 复制输出”，可以连续提交，不必在每两步之间让 CPU 等待。

**补充说明：** 顺序来自流的语义，不是运行时自动分析指针并推断数据依赖。跨流的先写后读需要显式建立依赖。主机侧 `cudaDeviceSynchronize()` 等待当前设备此前提交的工作完成，不是插入内核内部的全网格线程屏障；只关心一条流或一个阶段时，可以等待对应的流或事件。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 280–337 行。*
<!-- /classroom:async -->

### 全局同步

- host device cudaDeviceSynchronize();
- 等待设备上的操作完成
- 从主机调用时，使主机与设备同步
- 具体行为与该设备设置的同步标志有关

### 异步复制

- 可以执行异步复制
- Y host cudaMemcpyAsync
- host cudaMemcpyPitchAsync
- host cudaMemcpy3DAsync
- 避免数据复制时立即进行主机与设备同步

### 异步复制

- 可以执行异步复制
- host cudaMemcpyAsync
- host cudaMemcpyPitchAsync
- host cudaMemcpy3DAsync
- 避免数据复制时立即进行主机与设备同步
- 在显示或使用主机缓冲区之前，必须确认设备到主机的复制已经完成！
- cudaMemcpyAsync(h_a, d_a, ( sizeof(int) * 1024), cudaMemcpyDeviceToHost);cudaDeviceSynchronize(日
- for(i=0; i<1024; i++)
- printf("[%d]", h_a[i]);

### 异步执行

- 默认情况下，某些函数会先将控制权交还主机程序
- 内核执行
- 设备到设备的复制
- 内存初始化
- 可以在需要时调用 `cudaDeviceSynchronize();` 等待执行完成
- 连续调用向量加法内核 `vecAdd`
- 如果各次调用操作的是不同向量呢？
- 如果计算中存在先写后读（RAW）依赖呢？

### 异步执行

- 连续调用的内核之间存在依赖时，不一定需要全局同步〔本段按同一流内顺序执行的情境理解〕
- 即使控制权已交还主机，执行语义仍然保持顺序
- 计算内核按顺序执行
- 依赖关系得到隐式处理

### 异步提交与同步等待：一个完整过程

课件将同一个例子拆成多页动画。下面合并重复的调用序列，保留“等待完成”和“继续提交”两张关键时间线。

1. 主机提交 H→D 数据复制。
2. 在同一流中依次提交 `kernel1`、`kernel2`、`kernel3`。
3. 提交 D→H 数据复制。
4. 调用 `cudaDeviceSynchronize()`，主机等待前面的设备工作完成。
5. 同步返回后，再提交 `kernel4`。

> 这是原示例的调用顺序摘要，不是可直接运行的完整程序；原始调用片段见[原文提取稿](APM_Cours2.md)。

![CPU 等待 GPU 完成：绿色区域表示同步等待](Images/cours2_img_059.jpg)

*图：CPU 等待 GPU 完成：绿色区域表示同步等待。*

![同步完成后，CPU 继续提交 kernel4](Images/cours2_img_060.jpg)

*图：同步完成后，CPU 继续提交 kernel4。*

<!-- classroom:pinned-intro -->
**课堂讲解：异步复制期间，缓冲区仍在被使用**

老师强调用 `cudaMallocHost` 分配页锁定主机内存，以支持高效的主机／设备异步传输。`Async` 后缀本身不保证一次调用一定立即返回，也不保证复制必然与计算重叠；使用可分页内存时，运行时可能需要中转或同步。

**补充说明：** H→D 复制完成前不要修改或释放源主机缓冲区；D→H 复制完成前不要读取或复用目标缓冲区。可在复制后记录事件，并等待事件完成后再使用该缓冲区。页锁定解决内存传输条件，等待完成解决缓冲区的使用时机。

核对依据：[CUDA API 同步行为](https://docs.nvidia.com/cuda/cuda-runtime-api/api-sync-behavior.html)。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 340–355 行。*
<!-- /classroom:pinned-intro -->

### 异步执行与主机内存

- 问题：从调用 `cudaMemcpyAsync` 到实际复制之间，主机内存对应的物理地址可能变化
- 这是因为虚拟地址空间与物理地址空间分离
- 异步复制需要通过相应函数固定主机内存的物理页
- cudaMallocHost

### 异步执行

- 连续调用的内核之间存在依赖时，不一定需要全局同步〔本段按同一流内顺序执行的情境理解〕
- 即使控制权已交还主机，执行语义仍然保持顺序
- 计算内核按顺序执行
- 依赖关系得到隐式处理
- 如何实现真正的异步执行？

### 高级异步执行

- 目的：
- 在内核执行期间传输数据
- 同时执行多个计算内核
- 前提是显卡支持，例如 Fermi
- 并且内核之间没有依赖

### 解决办法：使用流（stream）

### 高级异步执行

- 声明一个或多个流
- 每次与设备的交互都提交到某个特定流中
- 驱动据此判断哪些工作可以并行执行

```cpp
cudaMemCpy(d_c, c, N*sizeof(double), cudaMemcpyHostToDevice, stream[0]);
my_kernel<<<Dg, Db, 0, stream[0]>>> (arg1, arg2, arg3);
```

### 高级异步执行

- 声明一个或多个流
- 每次与设备的交互都提交到某个特定流中
- 驱动据此判断哪些工作可以并行执行

```cpp
cudaMemCpy(d_c, c, N*sizeof(double), cudaMemcpyHostToDevice, stream[0]);
my_kernel<<<Dg, Db, 0, stream[1]>>> (arg1, arg2, arg3);
```

### 高级异步执行

### 流的数据类型

- cudaStream_t

### 创建流

- cudaStream_t stream;
- cudaStreamCreate(&stream);

### 销毁流

- cudaStreamDestroy(stream);

### 同步流

- cudaStreamSynchronize(stream);
- cudaStreamWaitEvent(stream, event, flag)

<!-- classroom:streams -->
**课堂讲解：流是一条任务队列，不绑定某一个 SM**

一条流中的内核可以使用多个 SM。多条流表达可以独立推进的工作，但是否实际重叠还取决于资源余量、复制引擎、硬件能力和依赖关系。老师用“各占一半资源”帮助理解，并不能直接拿监控工具里的两个利用率百分比相加，判断能否并发。

**补充说明：** 上面的跨流示意中，如果内核使用刚复制的 `d_c`，就必须建立复制完成到内核启动的依赖，例如在复制流中记录事件，再让计算流调用 `cudaStreamWaitEvent`。原片段里的 `cudaMemCpy(..., stream)` 也不是正确的运行时 API 拼写；指定流的异步复制应使用 `cudaMemcpyAsync(..., stream)`。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 358–379 行。*
<!-- /classroom:streams -->

### 线程块内同步

### void syncthreads();〔原文省略下划线〕

- 同一线程块内的所有线程同步
- 同时实现相关内存访问的同步
- 注意控制流！

<!-- classroom:barrier -->
**课堂讲解：共享内存装入后为什么需要屏障**

让每个线程装入一部分共享数组后，某线程可能已经装完，而邻居还未写入。若马上读取邻居负责的数据，就可能使用未准备好的值。典型步骤是“协作装入 → `__syncthreads()` → 共同计算”；若还要覆盖同一缓冲区，也需确认其他线程已读完旧数据。

**补充说明：** 这个屏障的作用域是线程块。不要把它放进仅部分线程会进入的分支；边界线程可以跳过越界的加载或计算，但仍应按一致的控制流程参与块内屏障。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 382–388 行。*
<!-- /classroom:barrier -->

### 对于支持计算能力 2.0 的显卡

- int syncthreads_count(int predicate);
- int syncthreads_and(int predicate);
- int syncthreads_or(int predicate);

## 其他功能

### 数学运算

- 提供一组针对 GPU 优化的数学函数
- 例如：`sin(float)`、`cos(double)` 等
- 可通过编译选项启用快速数学函数
- -use_fast_math
- 仅用于单精度计算

### 原子操作

### 保证原子性的指令

- 例如：`int atomicAdd(int* address, int val);`

### 可用函数

- 算术操作：`atomicAdd`、`atomicSub`
- 交换：`atomicExch`
- 最小值／最大值：课件列出 `atomicMin`
- 自增／自减：课件列出 `atomicInc`
- 比较并交换（CAS）等

### 限制

**适用类型：**

- 整数、浮点数
- 16 位、32 位、64 位
- 具体支持情况取决于计算能力（compute capability）

<!-- classroom:atomic -->
**课堂讲解：原子操作的瓶颈来自争用**

若大量线程都对同一个地址执行 `atomicAdd`，这个热点会限制吞吐量。可考虑先在块内汇总，再由少量线程更新全局结果，以减少争用。

**补充说明：** 这是算法上的优化方向，不是说一个原子操作会把整个 GPU 串行化。分组求和改变浮点加法顺序时，也可能改变舍入结果；是否允许这种差异，要看计算要求。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 397–409 行。*
<!-- /classroom:atomic -->

### 打印

### 格式化输出

- int printf(const char *format[, arg, ...]);
- 支持计算能力 2.0 的显卡
- 每个线程分别调用
- 最终格式化在主机端完成

### 计时与程序跟踪

- 测量时间，进行性能分析
- 使用 CUDA 定义的事件
- 主要类型：`cudaEvent_t`

### 创建

- cudaEventCreate(cudaEvent_t * e)
- 记录事件
- cudaEventRecord(cudaEvent_t e, cudaStream_t s)
- 等待事件完成
- cudaEventSynchronize(cudaEvent_t e);

### 计算经过的时间

- `cudaEventElapsedTime(float *ms, cudaEvent_t start, cudaEvent_t stop);`
- 计算开始事件与结束事件之间的时间，结果通过 `ms` 返回，单位为毫秒。新版第 95 页已完整显示此签名。

<!-- classroom:timing -->
**课堂讲解：测到的究竟是提交时间还是执行时间**

CPU 在内核启动语句前后立即读时钟，通常只量到了提交相关开销。老师建议把开始、结束事件记录到执行目标工作的流中，等待结束事件完成，再调用 `cudaEventElapsedTime(&ms, start, stop)`，返回值单位是毫秒。

**补充说明：** 事件之间放了哪些操作，就测量那一段流上的时间间隔；若想测整个应用的耗时，可用 CPU 时钟，但结束读数之前要等待所测工作完成。计时前还应明确是否包含数据传输、首次初始化和预热，避免把不同测量范围混在一起。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 421–439 行。*
<!-- /classroom:timing -->

### 错误处理

- CUDA 中几乎所有函数都会返回错误码
- 返回类型为 `cudaError_t`
- 执行成功时返回 `cudaSuccess`
- 否则可以获取错误描述
- const char * cudaGetErrorString (cudaError_t error);
- 对于不返回此类信息的操作，例如内核调用
- 调用 `cudaGetLastError()`
- 其返回类型为 `cudaError_t`

### 调试

### 如何调试代码？

- 可以直接使用 `printf`，但它并非万无一失
- 加入同步操作
- 检查每个 CUDA 函数的返回值
- 对内核也要获取 CUDA 错误信息

<!-- classroom:errors -->
**课堂讲解：启动失败与运行途中出错要分别检查**

CUDA API 的错误码如果被忽略，程序可能继续运行，却没有产生预期结果。老师用块大小超限举例：配置不合法时，内核可能根本没有启动。

**补充说明：** 普通 API 调用检查其 `cudaError_t` 返回值；`<<<...>>>` 启动后检查 `cudaGetLastError()`，并检查后续同步调用的返回值以捕获异步执行错误。前一项成功不能证明内核已经正确执行完。调试时可在可疑内核后增加同步帮助定位，但正式计时应重新确认这些等待是否属于原本流程。

`printf` 也会改变执行时序并增加开销，适合有限地观察数据，不能充当同步机制或作为性能测量的基础。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 442–466 行。*
<!-- /classroom:errors -->

### 优化

### 高优先级

- 从并行角度思考
- 尽量减少主机与设备之间的数据传输
- 线程块数量至少达到 SM 数量
- 线程数量至少达到计算核心数量
- 对全局内存使用合并访存
- 使用共享内存
- 避免代码出现过多不同的执行路径

<!-- classroom:optimization -->
**课堂讲解：先让工作和数据组织适合 GPU**

老师的优先顺序是：提供足够的并行工作，减少主机／设备来回搬运，再整理同一 warp 的访问模式。块数太少会让部分 SM 无事可做；有足够任务时，更多块可为调度提供余量。

**补充说明：** “块数至少等于 SM 数”是利用整卡的起点，不是最佳配置公式。每块线程数取 32 的倍数通常是合理起点，但并非所有内核的正确性要求；块也不是越小越好，还要考虑寄存器、共享内存、驻留块上限与任务规模。保留必要的边界判断，重点检查同一 warp 是否频繁走不同分支，而不是机械删除所有 `if`。

*课堂来源：[第 2 讲转录](Archive/APM_cours2_transcript.md)，第 469–493 行。*
<!-- /classroom:optimization -->

### 中低优先级

- 避免共享内存的存储体冲突
- 每个线程块使用较多线程，数量取 32 的倍数
- 使用经过优化的数学函数
