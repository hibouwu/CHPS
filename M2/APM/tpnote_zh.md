# GPU 编程 — 计分实验：GPU 上的 Floyd–Warshall 算法

**APM 2026–2027 学年 · 时长：3 小时**

凡尔赛圣康坦昂伊夫林大学 · 巴黎萨克雷大学  
教师：adrien.roussel@cea.fr

[原题 PDF](tpnote.pdf) · [法语整理版](tpnote.md) · [原始答题文件](../CODE/REPONSES.md) · [返回 APM](../../README.md)

> **译文说明：** 本文按照原题 PDF 六页可见正文的顺序翻译，整理了排版与命令中的空格，并增加小标题以便查找。PDF 文本层中页面不可见的附注未混入题目正文。本文为题目翻译，不含解答。

<!-- 原文第 1 页 -->

## 实验目标

本实验的目标是：

- 编写并启动第一个 CUDA kernel，完成设备内存管理的整个流程。
- 分析内存访问的性质，重点关注合并访存，并测量数据吞吐率。
- 在附加部分中使用共享内存，实现分块 Floyd–Warshall。

## 提交要求

在本次课结束时，从 `CODE` 目录中执行以下命令，将工作目录中的提交文件打包成 `NOM.PRENOM.tar.gz`：

```bash
bash rendu.sh
```

脚本会询问你的姓和名，创建 `NOM.PRENOM` 目录，并将需要提交的文件收集到其中：你在第 I 节开始时创建的 `fw_gpu.cu`、填写完成的 `REPONSES.md`、C/C++/CUDA 源文件及 `Makefile`。

脚本不会复制任何可执行文件；它会检查压缩包并列出其中的内容。发送前，请核对这份文件列表。将压缩包作为邮件附件发送至 **adrien.roussel@cea.fr**。

提供的文件 **`fw.c`、`fw_utils.h`、`cuda_utils.h`、`Makefile` 不得修改**。

编程题 **Q.2–Q.5、Q.7、Q.10** 根据 `fw_gpu.cu` 中的内容评分；其余题目根据 `REPONSES.md` 中的内容评分。

## 实验规则

**不允许使用 AI 助手；提交的作业会接受分析检查。**

如果一道题让你卡住超过 15 分钟，请先做下一题：第 I、II 节的优先级高于附加部分。

| 部分 | 题号 | 分值 | 建议用时 |
|---|---|---:|---:|
| I. 第一个 CUDA kernel | Q.1–Q.5 | 10 | 70 分钟 |
| II. 合并访存 | Q.6–Q.8 | 6 | 40 分钟 |
| III. 附加部分：共享内存 | Q.9、Q.10 | 4 | 50 分钟 |

## Floyd–Warshall 要解决的问题及算法

### 问题描述

有一个包含 $n$ 个顶点、边权为正的有向图，用邻接矩阵表示：`d[i][j]` 是边 $i\to j$ 的权重；当 $i=j$ 时为 0；`INF` 表示不存在这条边，输出时用一个点表示。

本实验解决的是**所有顶点对之间的最短路径问题**：对每一对顶点 $(i,j)$，计算从 $i$ 到 $j$ 的最短路径长度；如果不存在路径，则为 `INF`。

<!-- 原文第 2 页 -->

### 算法

Floyd–Warshall 通过连续 $n$ 轮处理解决这个问题，矩阵在原位置更新。在第 $k$ 轮，每个元素按以下公式更新：

$$
d_{ij}\leftarrow\min(d_{ij},\ d_{ik}+d_{kj}).
$$

也就是说：经过中间顶点 $k$，是否能缩短从 $i$ 到 $j$ 的路径？

完成 $n$ 轮后，`d[i][j]` 就是从 $i$ 到 $j$ 的最短路径长度。总共需要约 $n^3$ 次更新；本实验的目的就是把这些更新交给 GPU 完成。

### 题目中的示例

下面是一个固定的 4 顶点图，由 `fw.c` 中的 `graph_example()` 创建，并作为整个实验的参考。左侧是初始图，右侧是运行 Floyd–Warshall 后的预期结果：

$$
\begin{pmatrix}
0&3&10&\cdot\\
\cdot&0&4&8\\
\cdot&\cdot&0&1\\
\cdot&\cdot&\cdot&0
\end{pmatrix}
\qquad
\begin{pmatrix}
0&3&7&8\\
\cdot&0&4&5\\
\cdot&\cdot&0&1\\
\cdot&\cdot&\cdot&0
\end{pmatrix}.
$$

不带参数运行 `./fw` 时，程序会计算并显示这两个矩阵。你的 GPU 版本必须准确复现右侧的矩阵。

## 基础代码与运行环境

### 提供的代码

`CODE` 目录包含 CPU 参考程序 `fw.c`、两个头文件和提交脚本：

- **[fw.c](../CODE/fw.c)**：CPU 版 Floyd–Warshall。它仅包含 `floyd_warshall`——在原矩阵上更新的算法实现——和 `main`。使用 `make` 编译。**不得修改这个文件**，它是你的参考实现。
- **[fw_utils.h](../CODE/fw_utils.h)**：包含工具函数 `graph_example()`——创建上面的固定示例——、`graph_random(n, seed)`——创建可复现的随机图——、`print_graph(d, n)`——打印图，不存在的边用点表示——以及 `now_ms()`——以毫秒为单位的时钟。
- **[rendu.sh](../CODE/rendu.sh)**：生成提交压缩包的脚本，使用方法见前面的“提交要求”。
- **[cuda_utils.h](../CODE/cuda_utils.h)**：供 GPU 版本使用的辅助功能。`fw.c` 和 `Makefile` 都没有使用这个头文件；你可以在 `fw_gpu.cu` 中包含它。它只提供错误检查和计时功能，**不提供内存分配、复制或 kernel 启动**；这些操作仍需由你编写，并且必须出现在提交的代码中：

```cpp
CUDA_CHECK(cudaMalloc(&d, octets));    /* arrete en cas d'erreur */

gpu_timer_t t;
gpu_timer_start(&t);
/* ... vos lancements et copies ... */
float ms = gpu_timer_stop(&t);        /* duree en millisecondes */
```

<!-- 原文第 3 页 -->

### 运行环境

集群的登录节点 `romeo1.univ-reims.fr` 使用 x86 架构，计算节点使用 ARM 架构。因此，应先预留集群计算节点，在该节点上执行 `module load cuda`，再进行编译和运行。

基本命令如下：

```bash
srun --account r260073 --time 00:30:00 --mem 20G \
     --constraint armgpu -c72 -n1 --gpus-per-node 1 --pty /bin/bash
cp fw.c fw_gpu.cu                         # votre fichier de travail
nvcc -O3 -arch=sm_90 -o fw_gpu fw_gpu.cu
./fw                                     # reference CPU (exemple du sujet)
./fw -n 512                              # reference CPU, graphe aleatoire
./fw_gpu ...                             # votre version GPU
```

第一条命令会预留 GPU 计算节点，并在该节点上打开一个交互式 shell。如果不使用 `--pty /bin/bash`，`srun` 会直接执行通过参数传入的命令。

课堂使用的 GPU 是 GH200，对应架构为 `sm_90`。

## I. 第一个 CUDA kernel：每个线程负责一个矩阵元素

`fw.c` 中的 `floyd_warshall` 函数实现了前面介绍的算法。对于固定的 $k$，第 $k$ 轮的 $n^2$ 次更新彼此独立，正适合交给一个 kernel 处理，每个线程负责一个矩阵元素。

本节先构建这个初始版本，后续章节再对它进行分析和改进。

### 第 0 步 — 在 Q.1 之前完成，不计分

将 `fw.c` 复制为 `fw_gpu.cu`，使用上面的 nvcc 命令编译并运行。它目前还是 C 代码，行为应当与 `./fw` 完全一致。这样你就编译出了第一个 CUDA 程序。

### Q.1 — k 循环与同步

不能将 $k$ 循环直接原样移入 kernel。

1. **(a)** 第 $k+1$ 轮会读取哪些由第 $k$ 轮刚刚生成的数据？
2. **(b)** `__syncthreads()` 能在什么范围内同步线程？在标准 CUDA 中，要同步整个网格，还缺少什么？
3. **(c)** 据此得出结论：$k$ 循环应保留在哪里？在你的程序中，什么机制起到相邻两轮之间的同步屏障作用？

**1 分，填写在 `REPONSES.md` 中。**

### Q.2 — 主机函数 fw_gpu

仍然在 `fw_gpu.cu` 中，编写主机函数 `fw_gpu(int *d, int n)`，在 `main` 中调用它来代替 `floyd_warshall`。同时，在文件中保留 `floyd_warshall`，因为第 4 题需要使用它。

在这一步，`fw_gpu` 先准备 kernel 周围的工作：内存分配、数据传输以及网格尺寸设置。

验证标准：函数返回时，`d` 与输入时完全一致。通过程序的打印结果即可检查这一点。

**2 分。**

### Q.3 — kernel fw_step

在 `fw_gpu.cu` 中编写 kernel `fw_step(int *d, int n, int k)`，完成算法的第 $k$ 轮更新。然后补全 `fw_gpu`，使它像 `floyd_warshall` 一样在原位置完成计算：函数返回时，`d` 中保存计算结果。

**3 分。**

### Q.4 — CPU / GPU 正确性验证

验证你的实现：无论是题目给出的示例，还是不同规模的随机图，GPU 版本都必须得到与 CPU 参考程序完全一致的结果。至少测试 $n=8,64,512$。

程序必须明确输出验证结论。

**2 分。**

<!-- 原文第 4 页 -->

### Q.5 — CPU / GPU 计时

对两个版本进行计时，GPU 版本的时间必须包含数据传输。将 $n=512,1024,2048$ 时的运行时间填写到 `REPONSES.md`，并用一句话描述你的观察结果。

**2 分。**

## II. 合并访存

本节分析第 I 节 kernel 的内存访问，并测量这些访问方式对性能的影响。

### Q.6 — 内存访问的类型

针对你编写的 `fw_step`，将每一类内存访问划分为：**合并访问、广播访问或跨步访问（strided）**。

- **广播访问**：整个 warp 访问同一个地址。
- **跨步访问**：相邻线程访问的地址之间具有固定步长。

答案取决于你如何把 $i$ 和 $j$ 分配给线程坐标，因此需要明确说明这种映射。

**2 分，填写在 `REPONSES.md` 中。**

### Q.7 — 比较两种映射

如果第 I 节的版本没有实现合并访存，请进行修正。

无论初始版本如何，都要再实现采用另一种映射的版本，并在 $n=4096$ 时测量两者：将运行时间及其差距填写到 `REPONSES.md`。

**2 分。**

### Q.8 — 朴素 kernel 的内存流量模型

1. **(a)** 在最好的情况下，每次更新需要传输多少字节？
2. **(b)** 每次更新需要多少次算术运算？由此推导 kernel 的算术强度：它受计算能力限制，还是受内存限制？请使用你的 GPU 的计算与带宽比进行论证，即峰值计算吞吐率与峰值内存带宽之比，单位为 flop/字节。
3. **(c)** 你的合并访存版本最高能够达到多少数据吞吐率，单位为 GB/s？在 $n=4096$ 时，你实际达到了 GPU 峰值内存带宽的百分之多少？

**2 分，填写在 `REPONSES.md` 中。**

## III. 附加部分：使用共享内存的分块 Floyd–Warshall

### 基本原理

朴素 kernel 在每次更新时都重新读取 $d_{ik}$ 和 $d_{kj}$，因此总内存流量约为 $16n^3$ 字节。

分块版本可以减少这些流量：将矩阵划分为 `TILE × TILE` 的小块，在 `fw_gpu.cu` 中设置 `#define TILE 32`。

每个方向上共有 $nb$ 个 tile，最后一个 tile 可能不完整。tile $(I,J)$ 覆盖第 $32I$ 至 $32I+31$ 行，以及第 $32J$ 至 $32J+31$ 列。

对于同一个分块步内的 32 轮更新，每个需要用到的 tile 只加载到共享内存一次。这个复用倍数不取决于 $n$；$n$ 只决定 tile 的数量与分块步数。

### 分块步

$k$ 循环仍保留在主机端，参见 Q.1，但改为每次处理一组 32 轮。第 $K$ 个分块步中，$K=0,1,\ldots,nb-1$，包含 $k$ 从 $32K$ 到 $32K+31$ 的 32 轮更新。

在一个分块步内，每个矩阵元素 $(i,j)$ 都要对这些 $k$ 值逐一执行第 $k$ 轮的更新：

$$
d_{ij}\leftarrow\min(d_{ij},\ d_{ik}+d_{kj}).
$$

<!-- 原文第 5 页 -->

### 操作数位于哪些 tile？

对于 tile $(I,J)$ 内的一个矩阵元素，公式中的三个值分别位于以下 tile：

- 累加更新值 $d_{ij}$ 位于 tile $(I,J)$ 自身。
- 操作数 $d_{ik}$ 位于 tile $(I,K)$，即同一 tile 行、分块索引为 $K$ 的列。
- 操作数 $d_{kj}$ 位于 tile $(K,J)$，即分块索引为 $K$ 的行、同一 tile 列。

因此，只有当 tile $(I,K)$ 和 $(K,J)$ 完成第 $K$ 个分块步的全部 32 轮更新后，才能处理 tile $(I,J)$。如果提前处理，就会得到错误结果。

### 按什么顺序处理 tile？

在一个分块步中，需要区分三种情况。原题示意图中的数字表示处理阶段：

$$
\begin{matrix}
3&3&2&3\\
3&3&2&3\\
2&2&1&2\\
3&3&2&3
\end{matrix}
$$

- **阶段 1**：枢轴 tile $(K,K)$ 位于第 $K$ 行和第 $K$ 列的交点，只读取自身。这是一次独立的 $32\times32$ Floyd–Warshall；本分块步中的中间顶点 $k$，正是枢轴 tile 对应的顶点。
- **阶段 2**：第 $K$ 行和第 $K$ 列上的 tile，除了读取自身，还读取枢轴 tile，由它提供所需的另一个操作数。
- **阶段 3**：其余所有 tile，除了读取自身，还读取所在 tile 行的 $(I,K)$ 以及所在 tile 列的 $(K,J)$。

因此，阶段编号恰好对应需要读取的不同 tile 的数量：依次是 1 个、2 个、3 个。

### 算法流程

对于每一个分块步 $K$：

1. 阶段 1 仅对枢轴 tile $(K,K)$ 执行该分块步的 32 轮更新。
2. 阶段 2 对第 $K$ 行和第 $K$ 列的 tile 执行这 32 轮更新。
3. 阶段 3 对其余所有 tile 执行这 32 轮更新。

在这 32 轮更新中，每个 tile 都会反复读取自身。阶段 3 结束时，矩阵应与朴素版本完成第 $32K+31$ 轮后的矩阵完全一致。

### 实现方式

一个线程块负责一个 tile：将这个 tile 及所需的相邻 tile 加载到共享内存中，在共享内存中完成该分块步的 32 轮更新，再将结果 tile 写回全局内存。

每个阶段分别启动一次 kernel。下一题要求说明这样做的原因。

### Q.9 — 每个分块步启动三次 kernel

为什么每个分块步 $K$ 恰好要启动三次 kernel，而不是一次启动就完成所有工作？将多个阶段合并到一次 kernel 启动中，会有什么具体风险？

**1 分，填写在 `REPONSES.md` 中。**

### Q.10 — 实现分块版本

实现分块版本：按照你的 `fw_gpu` 的组织方式，编写三个 kernel：`fw_phase1_kernel`、`fw_phase2_kernel`、`fw_phase3_kernel`，它们的参数签名均为 `(int *d, int n, int K)`；并编写负责组织这些调用的函数 `fw_blocked(int *d, int n)`。

CPU / GPU 正确性验证必须继续通过，包括矩阵大小不是 32 倍数的情况，例如 $n=33$。

然后测量该版本相对于朴素合并访存版本的加速比，将结果填写到 `REPONSES.md`。

**3 分。**

<!-- 原文第 6 页 -->

## 附录：提示

- **计时**：GPU 使用 `cuda_utils.h` 中的 `gpu_timer_start`、`gpu_timer_stop`；CPU 使用 `fw_utils.h` 中的 `now_ms()`。时间单位均为毫秒。
- 可以在 kernel 中使用 `min(a, b)`。
- 使用 `cuda_utils.h` 中的 `CUDA_CHECK` 检查每次调用。
- 向集群复制文件：`scp fichier romeo1.univ-reims.fr:`；从集群取回文件：`scp romeo1.univ-reims.fr:fichier .`；必要时使用 `login@romeo1.univ-reims.fr` 指定登录名。
