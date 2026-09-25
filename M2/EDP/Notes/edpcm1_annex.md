# 第一课 Annex：HPC 扩展与后续课程预习

[第一课中文正文](edpcm1.md) · [课程目录](../README.md) · [今年教师课件](../CM/1_edpCpl.pdf) · [原中文笔记 PDF](edpcm1.pdf)

本文件承接原中文笔记第 19–35 节，使用 A1–A17 编号，保留其中的背景、模型、工具与后续课程预习内容。部分基础概念与新版正文重合，可作复习；Roofline、LogP、BSP 等扩展没有在当前 CM1 的对应正文页展开，不作为教师已授内容的证明。

跟课时先读 [正文第 19–26 节](edpcm1.md)，本附录按需要查阅。这里保留的工具名称用于了解用途，具体安装与运行方式应另查当前文档。

## 阅读导航

| 需要补充的内容 | 本附录位置 | 原笔记位置 |
|---|---|---|
| HPC 背景、Amdahl 假设、峰值性能 | A1–A3 | 第 19–21 节 |
| Roofline、其他模型、通信与同步 | A4–A5 | 第 22–23 节 |
| 评估层次、工具与 HPC 扩展小结 | A6–A7 | 第 24–25 节 |
| 工作负载、建模、仿真和测量预习 | A8–A12 | 第 26–30 节 |
| 模型局限、方法、常见陷阱与结果展示 | A13–A17 | 第 31–35 节 |

后续课程的对应入口：[工作负载](edpcm2.md)、[数学建模与排队模型](ed充满.md)、[仿真与测量](edp4cm.md)。

## A1 高性能计算（HPC）中的性能评估（Évaluation des performances pour le HPC）

### A1.1 动机与问题（Motivation et problématique —HPC）

在高性能计算（HPC, High Performance Computing / Calcul Haute Performance）中，性能评估对于以下方面至关重要：

- 理解程序在并行执行中的行为；
- 定位性能瓶颈（goulots d’étranglement）；
- 指导调优（optimisation）与扩展；
- 选择合理的硬件架构（architectures）；
- 设计高效并行算法；
- 比较不同实现、不同平台的性能差异。

HPC 系统的复杂性来自多层次架构：

- 多核处理器（multi‐core CPUs）
- 异构加速器（GPU / accelerators）
- 多节点互连网络（réseau d’interconnexion）
- 分布式存储系统

因此，HPC 性能评估不仅需要基本指标，还必须考虑架构特性与并行模型。

## A2 并行性与性能（Parallélisme et performance）

在 HPC 中，性能依赖于并行度（parallélisme）和资源利用效率（efficacité d’utilisation des ressources）。

### A2.1 并行加速比：回顾（Speedup）

加速比：

$$
\mathrm{Acc} = \frac{T_{\mathrm{séquentiel}}}{T_{\mathrm{parallèle}}}
$$

理想情况下：

$$
\mathrm{Acc} (P) = P
$$

但在实际 HPC 中，由于通信（communication）、同步（synchronisation）、缓存一致性等开销，加速比会偏离线性。

### A2.2 Amdahl 定律的限制（Limites de la loi d’Amdahl）

Amdahl 定律考虑固定问题规模（strong scaling）。其局限在于：

- 假设并行部分比例固定；
- 假设并行部分可理想均分，忽略额外通信、同步等开销；
- 大规模系统中的额外开销和问题规模变化需要另行建模；核心数量本身不会让 Amdahl 的固定规模关系失效；

固定规模分析可使用 Amdahl 模型；扩大规模的分析可使用 Gustafson-Barsis 模型，并明确两者的时间基准。

> 校注：原笔记“核心数很大时 Amdahl 不再适用”的说法过强，已按模型假设修正。

## A3 HPC 中的经典性能指标（Métriques classiques dans le HPC）

HPC 领域中的指标包括：

- 加速比（speedup）
- 并行效率（efficacité parallèle）
- 浮点性能（FLOPS）
- 使用率（utilisation）
- 通信开销（coût de communication）
- 负载均衡（load balancing）

### A3.1 浮点性能（FLOPS）

FLOPS（Floating Point Operations Per Second）：衡量每秒可执行浮点运算数量。理论峰值性能（peak performance）：

$$
P_{\mathrm{peak}} = N_{\mathrm{cœurs}}\times f\times N_{\mathrm{FLOP/cycle/cœur}}
$$

实际性能通常远低于理论值，受制于：

- 内存带宽（memory bandwidth）
- 吞吐瓶颈（bottlenecks）
- 指令混合（instruction mix）
- 缓存行为（cache locality）
- 通信、同步开销

<a id="annex-roofline"></a>

## A4 性能模型与局限（Modèles et lacunes）

HPC 常用的性能模型包括：

- Roofline 模型（roofline model）
- LogP 模型
- Bulk Synchronous Parallel (BSP) 模型
- Amdahl / Gustafson 模型

这些模型用于：

- 估计算法性能；
- 分析是否受算力限制（compute‐bound）；
- 分析是否受内存带宽限制（memory‐bound）；
- 量化通信成本。

### A4.1 Roofline 性能模型

Roofline 模型给出性能上限：

$$
\mathrm{Performance} \leq \min(P_{\mathrm{peak}}, I \times \mathrm{BW})
$$

其中：

- I = 算术强度（intensité arithmétique = FLOP/byte）
- BW = 内存带宽（bandwidth）

它区分两类程序：

- 内存带宽受限（memory‐bound）
- 计算性能受限（compute‐bound）

该模型帮助比较算力上限与带宽上限。算术强度的字节数和带宽必须针对同一存储层级；上限也不等于实际可达到的性能。模型说明见 [Berkeley Lab 的 Roofline 介绍](https://amcr.lbl.gov/departments/computer-science-department/ppan/roofline-performance-model/)。

## A5 通信与同步开销（Communications et synchronisation）

在并行程序中必须考虑：

- 点对点通信（point‐to‐point）
- 集体通信（collectives）
- 同步屏障（barrières）
- 缓存一致性协议
- NUMA 访问成本

通信成本取决于消息大小、互连延迟、带宽和可重叠的计算量；比较时应明确通信操作与计算操作的单位和规模。

## A6 HPC 中的性能评估方法（Évaluation dans le HPC）

HPC 性能评估通常包括：

- 微基准测试（microbenchmarks）
- 内核（kernel）测试
- 真实应用测试（applications réelles）
- 仿真（simulation HPC）
- 跟踪（tracing）分析

工具示例：

- MPI 测试套件：IMB、OSU Benchmarks
- 性能分析工具：perf、VTune、TAU、HPCToolkit
- 跟踪系统：Paraver、Score-P

## A7 HPC 扩展内容小结（Résumé HPC）

本附录前半部分讨论：

- HPC 性能的重要性；
- 并行加速模型及其局限；
- FLOPS 与实际性能差距；
- Roofline 等性能模型；
- 通信与同步的影响；
- HPC 中的评估方法与工具。

## A8 工作负载（Workloads）

在性能评估中，工作负载（workload）用于代表系统在真实使用中将面对的任务类型。

选择或构造工作负载时，通常希望它能够：

- 准确反映真实场景；
- 能在不同系统间复现；
- 能用于比较不同配置；
- 能引出性能瓶颈；
- 对评估方式（建模、仿真、测量）保持一致性。

### A8.1 工作负载的分类

工作负载通常分为两类：

#### 1. 合成工作负载（synthetic workload）

- 由人工构造；
- 可控、可重复；
- 通常用于微基准测试（microbenchmarks）；
- 特点：简单、可调整、易于分析；
- 示例：固定大小的矩阵乘法、循环访问模式测试等。

#### 2. 真实工作负载（workload réel）

- 来自实际应用；
- 代表实际系统的行为；
- 能揭示复杂交互；
- 但可能不可控、难以重现；
- 示例：真实 HPC 应用，如 CFD、分子动力学、天气模拟等。

### A8.2 工作负载特性（Caractéristiques des workloads）

根据系统类型选择需要描述的特征；并非每个实验都同时需要下列所有特征：

- 到达率（taux d’arrivée）
- 服务时间（temps de service）
- 并行度模式（modèle de parallélisme）
- 数据访问模式（localité, patterns mémoire）
- 通信模式（communication patterns）
- I/O 行为
- 资源消耗特征（CPU, mémoire, réseau）

### A8.3 工作负载类型示例

批处理型（batch workloads）

- 长时间运行的任务；
- 数据密集或计算密集；
- HPC 中非常常见。

交互式（interactive workloads）

- 需要快速响应；
- 典型指标为响应时间（temps de réponse）；

事务型（transactionnel）

- 常见于数据库；
- 指标包括 TPS（transactions per second）。

## A9 数学建模（Modélisation mathématique）

数学建模用数学方法近似描述系统行为，也常用于系统尚不存在或无法直接测量的情形。主要优势：

- 评估速度快；
- 不需要真实系统；
- 可预测未来场景；
- 可在模型假设允许的范围内比较大量输入与配置。

缺点：

- 需要大量假设；
- 可能与现实偏离；
- 细节通常被抽象化；

### A9.1 数学建模的步骤

1. 定义要分析的系统；

2. 确定系统的主要组成部分；

3. 定义参数和变量；

4. 写出描述系统的数学方程；

5. 求解这些方程或模拟其运行；

6. 分析结果；

7. 验证模型与真实数据是否一致。

### A9.2 队列模型（Modèles de files d’attente）

队列模型用于描述：

- 请求的到来；
- 等待；
- 服务（service）；
- 离开。

常见模型：

- M/M/1
- M/M/k
- M/G/1
- G/G/1

它们用于预测：

- 平均等待时间（temps d’attente）
- 平均响应时间（temps de réponse）
- 利用率（utilisation）
- 队列长度（longueur de file）

## A10 仿真（Simulation）

仿真是在无法直接测量真实系统、或数学建模不够精确时使用的一种方法。

类型包括：

- 离散事件仿真（simulation à événements discrets）
- 连续仿真（simulation continue）
- 模拟 ‐ 仿真混合模型（modèles hybrides）

优势：

- 能纳入较细的系统行为；准确性取决于模型及输入是否可信；
- 可处理复杂系统；
- 不需要真实硬件；

缺点：

- 非常耗时（时间成本高）；
- 模型复杂；
- 需要大量计算资源；

### A10.1 离散事件仿真的典型步骤

1. 定义系统实体（entités）；

2. 定义事件（événements）；

3. 定义系统状态（états du système）；

4. 构建事件调度器（ordonnanceur d’événements）；

5. 定义统计收集方式；

6. 运行仿真，收集数据；

7. 分析、验证仿真结果；

## A11 测量（Mesure）

当系统存在且可访问时，测量能提供实际运行证据。结果仍受工作负载代表性、测量工具开销和环境噪声影响，需检验可重复性。

主要挑战：

- 系统必须可用；
- 测试可能干扰真实用户；
- 某些参数不可控；
- 测量结果可能受噪音影响；

### A11.1 测量的组成要素

- 测量工具（outils de mesure）；
- 性能计数器（compteurs de performance）；
- 事件跟踪（tracing）；
- 日志（logs）；
- 时间戳（timestamps）；

### A11.2 测量的关键要求

- 可重复性（répétabilité）
- 正确性（exactitude）
- 最小侵入（faible perturbation）
- 高精度（précision）
- 多样化数据（variété des données collectées）

### A11.3 测量方法示例

#### 1. Profiling（性能剖析）

- 统计函数执行次数；
- 栈调用关系；
- CPU 时间占比；

#### 2. Tracing（事件跟踪）

- 跟踪事件时间线；
- 在所记录事件和时间精度的范围内展示程序行为；

#### 3. 基准测试（benchmarking）

- 使用固定任务测试性能；
- 可用于不同系统之间比较；

### A11.4 测量工具示例

- perf
- PAPI（Performance API）
- gprof
- valgrind
- HPCToolkit
- Intel VTune
- Score-P / Paraver

## A12 综合对比：建模 vs 仿真 vs 测量

- 数学建模（modélisation）：快速，但抽象。
- 仿真（simulation）：可表达更多细节，但有模型误差和计算成本。
- 测量（mesure）：真实但需要系统存在。

在专业性能评估中：

通常结合两种或三种方法，检查结论是否相互支持；多种方法一致也不能代替对共同假设的检查。

## A13 模型的局限（Lacunes des modèles）

模型通过简化假设减少求解难度，因此必须检查假设是否适合当前问题：

- 常见简化包括任务独立、通信开销线性增长、负载均匀分布。
- 根据抽象层次，模型可能省略 NUMA、多级缓存、网络拓扑、不规则通信与操作系统噪声。
- 极端情况与输入变化可能超出模型经过验证的范围。
- 不同模型关注不同方面。例如基本 Roofline 连接算术强度、带宽和算力上限，无法独自解释所有延迟与同步问题。

模型适合提出预测和指导分析；还应结合实测或仿真检查其适用性。

## A14 HPC 性能评估的综合方法论（Méthodologie d’évaluation pour le HPC）

1. **定义目标。** 寻找瓶颈、比较算法、优化程序、选择硬件，或评估扩展能力。
2. **选择指标。** 根据目标选择加速比、效率、利用率、FLOP/s、I/O 吞吐量或通信开销，并定义单位与测量范围。
3. **选择工作负载。** 让任务、规模与访问行为能代表要研究的场景。
4. **选择方法。** 使用数学建模、仿真、实测中的一项或多项。
5. **设计实验。** 明确变化参数和控制变量，重复运行，必要时随机化运行次序。
6. **收集与分析。** 检查均值、方差、置信区间和异常值；说明异常值处理理由。
7. **解释与呈现。** 用图表、模型对比和扩展性分析说明结果，记录假设及限制。

## A15 性能评估中的常见陷阱（Erreurs fréquentes）

性能评估中常见错误包括：

- 不恰当的性能指标；
- 工具本身干扰程序性能；
- 忽略现实系统中的随机性；
- 工作负载不匹配；
- 使用单一数据点得出错误结论；
- 错误解释基准测试结果；
- 未考虑内存层次结构的影响；
- 忽略通信与同步成本；
- 过度依赖 MIPS 或 FLOPS；
- 案例设计不完整；

Raj Jain 的 checklist 可用于避免这些陷阱。

## A16 性能结果展示方法（Présentation des résultats）

- 根据问题选择折线图、柱状图或加速比/效率曲线。
- 标清单位、比较基准、误差条的含义与重复次数。
- 使用对数刻度时说明原因，避免读者误判变化幅度。
- 解释趋势及可能原因，并区分观测事实和推测。
- 写明模型假设、局限、测试平台、编译选项与优化配置。

图表应让读者知道比较对象、测量条件及结论适用范围。

## A17 原笔记扩展主题回顾

原笔记及本附录涉及的主题如下；其中部分对应课程主线，部分属于扩展，不能据此推断今年的授课或考试范围：

- 性能评估的基本概念（concepts de base）
- 工作负载特性（workloads）
- 性能指标（temps de réponse, débit, speedup, efficacité, fiabilité, disponibilité）
- 避免错误的 checklist（Raj Jain）
- 性能评估方法（modélisation, simulation, mesure）
- 并行性能分析（HPC）
- 加速比模型（Amdahl, Gustafson-Barsis）
- 通信、同步与并行开销
- Roofline 模型
- HPC 性能工具

这些材料可以用于练习：

1. 正确评估一个系统的性能；

2. 选择合适的性能指标；

3. 使用多种方法进行分析；

4. 在 HPC 环境中识别瓶颈与优化方向；

5. 清晰展示性能结果；

进一步学习时，应把这些主题对应回具体问题和实验，而不只记忆模型与工具名称。
