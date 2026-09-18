# 并行手段

这份路线图只讨论和当前项目真实约束匹配的方向，不做脱离现状的“百科式并行大全”。

## 当前项目硬约束

1. 主平台仍然是 `CPU`，主线训练性能主要来自 `OpenMP / BLAS / MPI`。
2. 当前分布式方案仍是 `MPI + 同步数据并行`。
3. 当前已经同时具备三种 grad-sync 形态：`per_param`、`bucketed baseline` 和 `overlap_bucketed correctness-only`；其中后两者共享分桶基础设施，但 `overlap_bucketed` 仍应被视为 correctness-only，而不是已经完成性能资格认证的真实 overlap 方案。
4. 当前已经有两套数据集入口：`MNIST` 与 `Tiny-ImageNet`；系统级 profile、artifact 和 Stage C 资格验证已经明显转向 `Tiny-ImageNet + CNN`，`MNIST + MLP` 更适合作为轻量 correctness / smoke baseline。
5. 卷积算子现在已经不只是一条 CPU reference 路径：主线可选 `reference / oneDNN` 两种 backend，另有独立的 `cuDNN` experimental probe 与测试目标；但这些 GPU 代码还不是完整训练主线。
6. `GPU / AMP / TF32 / Tensor Cores` 不再是“完全空白”，但目前仍不是正式主线交付物，不能把 isolated probe 当成完整异构训练系统。

## 当前正式状态

1. `MNIST`：Stage C 已完成最小资格验证，当前正式结论是 `Partial-NoStableBenefit`；这表示 correctness、合法 real early launch 证据和 rank-order 一致性已经成立，但还没有观察到稳定、可重复的性能收益。
2. `Tiny-ImageNet`：Stage C 仍处于 `Qualification In Progress / Not Yet Complete`；当前主要瓶颈是完整预注册 run 集合的运行成本较高，而不是 correctness gate 未通过。
3. `oneDNN Conv backend`：已经进入“可选 correctness-first backend”状态，具备 forward/backward parity、optimizer parity 和 benchmark/probe 支撑，但还不能当成 fully tuned 的最终性能后端。
4. `cuDNN experimental conv path`：已经有独立 probe、smoke test 和 experimental forward/backward 测试，但仍属于 isolated / experimental 路径，不等同于正式 GPU 训练主线。
5. 在 `Tiny-ImageNet` 的 Stage C 完成之前，`overlap_bucketed` 的对外语义保持 `correctness-only`；不能宣称“真实 overlap 已完成”，也不能把历史 profile 或局部 timing 写成已获资格认证的 benchmark 结论。

## 1. 已完成 / 已在项目中

| 优先级 | 类别 | 技术/做法 | 当前状态 | 适用（CNN/MLP） | 并行类型 | 核心思路（在干什么） | 典型收益 | 代价/坑点 | 实战备注 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 已完成 | 分布式训练 | 数据并行 DP（MPI AllReduce 梯度） | 已实现 | 两者 | 跨进程 | 每个 rank 一份完整模型，不同 mini-batch，本地反传后同步梯度 | 最直接提升吞吐；是后续所有分布式实验的基线 | 需要持续区分 `per_param`、`bucketed baseline` 与 `overlap correctness-only` 的语义边界 | 这是你现在 `distributed` 的真实语义 |
| 已完成 | 通信优化 | 梯度 bucketing（full-bucket baseline） | 已实现 | 两者 | 跨进程 | 将多个参数梯度打包到 bucket buffer 中，减少 collective 次数 | 在 Tiny-ImageNet 路径上已经形成稳定基线，并能导出更细的 sync artifact | 当前实现仍是保守 baseline：固定 full-bucket launch order、zero-fill pack、full-registry unpack | 已经不是路线图候选项，而是现有基线的一部分 |
| 已完成（correctness-only） | 通信优化 | bucketed overlap runtime | 已实现但仅 correctness-only | 两者 | 跨进程 | 借助 parameter-ready 事件和 `MPI_Iallreduce` 做 bucket 级异步通信装配 | 已具备 runtime 结构、事件接口、多 rank contract test 和 qualification artifact | 不能把当前 profile 当成“已经证明有真实 overlap 收益”的结论 | 当前更像后续性能证明的结构准备，而不是最终版 overlap |
| 已完成 | 算子实现 | MLP 的 GEMM 优化（blocking / OpenMP / BLAS） | 已实现 | MLP 为主 | 单机多线程 | 优化矩阵乘，减少 cache miss，提高线程利用率 | 端到端训练提速最明显 | 小矩阵不一定吃到多线程收益；线程绑核和库配置影响很大 | 这是你当前 HPC 实验的重要基础 |
| 已完成 | 算子工程化 | GEMM 后端运行时切换 + epoch 级 matmul profiling | 已实现 | MLP 为主 | 单机算子级 | 通过 `MATMUL_IMPL` 在 `blas/ijk/ikj/blocked/omp` 间切换，并在 `PROFILE_MATMUL` 下汇总 epoch 级调用次数与总耗时 | 方便做可控对照实验，快速定位 matmul 是否仍是热点 | 目前只有 epoch 聚合，没有细到 shape/per-call/report 文件 | 已经具备“同一训练入口下切换算子基线”的实验条件 |
| 已完成 | 算子实现 | CNN 卷积：reference configurable CNN + LeNet 风格主线 | 已实现 | CNN | 单机算子级 | 当前 CNN 网络已支持多 stage conv/pool + FC 配置，不再只是固定死的单一结构 | 让 `Tiny-ImageNet + CNN` 成为可运行主线 | 仍缺 BatchNorm、residual block、ResNet 级组件化 | 现在的 CNN 主线已足够承担 profiling 与分布式实验 |
| 已完成（correctness-first） | 算子实现 | oneDNN Conv backend | 已实现但以 correctness-first 为主 | CNN | 单机算子级 | 在保持外部 `Matrix<double>` 接口不变的前提下，为 Conv2D 增加可选 oneDNN 后端 | 已具备 forward/backward parity、optimizer parity、benchmark/probe 与 fail-fast 选择逻辑 | 还没有 primitive cache、weight reorder cache、跨层 layout 传播等性能型工程化 | 这是“可选后端”，不是默认主线性能结论 |
| 已完成（experimental） | GPU/算子验证 | cuDNN conv forward/backward probe 与实验测试 | 已有 isolated probe / smoke / experimental test | CNN | 单机异构 | 用独立测试目标验证 cuDNN forward/backward 的 shape、parity 与失败回退 contract | 证明 GPU 卷积探索已开始，不再是纯概念路线 | 仍未形成设备抽象、训练主循环迁移、端到端 GPU 训练入口 | 只能写成 experimental path，不能写成“GPU 训练已实现” |
| 已完成 | 训练机制 | Mini-batch 训练 | 已实现 | 两者 | 样本维度 | 每步处理一个 batch，而不是全量样本 | 更稳定、可扩展到数据并行 | batch 太小时吞吐差，太大时精度可能降 | 它是训练机制，不是独立分布式范式 |
| 已完成 | 工程能力 | epoch 级训练打点 + `metrics.csv` / profile artifacts / sync trace 输出 | 已实现 | 两者 | — | 记录 `epoch/data/fwd_bwd/sync_total/sync_wait/sync_pack/sync_launch/sync_unpack/samples_per_s` 等指标，并写出 metrics / profile / qualification CSV | 已经能对比单机/MPI 训练开销拆分，也能保留 grad-sync mode 元数据与 trace | 仍缺更完整的自动汇总、plot/report 生成，以及更系统的 scaling efficiency 统计 | 现在已经不只是控制台日志，而是可分析 artifact |
| 已完成 | 工程能力 | Stage C qualification 脚本与 manifest 约束 | 已实现 | 两者 | — | 对预注册 run 集、commit hash、trace 路径、snapshot 一致性做自动检查，并生成资格结论摘要 | 大幅提升 overlap 相关论证的可信度 | 运行成本高，Tiny-ImageNet 全量资格仍比较重 | 这是当前仓库比普通课程项目更“工程化”的一块 |
| 已完成 | 输入管线 | DataLoader 按 batch 取数 + 复用 batch buffer | 已实现 | 两者 | CPU 侧流水 | 训练循环复用 `batch_x/batch_y`，避免每步重建主 batch 缓冲区 | 比“每步新建 batch 矩阵”更稳，也更利于后续继续优化 | 仍会构造 `batch_indices`，MNIST 路径仍是物理拷贝 | 已经迈出减分配的第一步 |
| 已完成 | 输入管线 | Tiny-ImageNet `BatchSource` 流式 JPEG 解码 | 已实现 | CNN 为主 | CPU/IO | 以 `BatchSource` 抽象按索引加载样本，训练时按 batch 解码 JPEG，而不是整套数据一次性常驻内存 | 让更真实图像数据集可以在当前框架下跑通 | 还没有 prefetch / decode overlap / 缓存 / resize-crop augment | 这是数据管线从“纯内存 MNIST”向真实图像任务的关键升级 |
| 已完成（基础版） | 工程能力 | checkpoint / resume | 已实现并接入训练 CLI | 两者 | — | 支持保存并恢复模型参数、优化器状态、epoch 以及主要训练配置，训练入口已具备 `--save_checkpoint`、`--resume` 与 `--save_every` | 长实验中断后可继续训练，也让正式实验更接近真实训练系统 | 当前还缺系统化的恢复连续性验证、统一实验纳入与更完整的恢复元数据 | 代码层已经落地，不应再写成“未实现” |
| 已完成（部分） | 工程能力 | HPO / 实验脚本与 `run_meta.json` | 部分实现 | 两者 | — | Optuna/HPO 路径已经能导出 `run_meta.json`、`trials.csv`、`best.txt` 与复现实验命令 | 比“手工试参数 + 截图”更可复现 | 这套元数据目前集中在 HPO/qualification 路径，不是所有训练 run 默认都有完整环境记录 | 作品集展示价值已经有，但还没完全统一到全局 schema |

## 2. 升级前适合做的主线任务（当前主线，按优先级）

这一段只放“立刻能做、立刻能产出结果、而且最能提升项目可信度”的主线任务。

| 优先级 | 类别 | 技术/做法 | 当前状态 | 适用（CNN/MLP） | 并行类型 | 核心思路（在干什么） | 典型收益 | 代价/坑点 | 实战备注 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| P1 | 工程能力 | 指标打点（artifact 自动汇总与固定 schema 报表） | 部分实现（epoch 级 artifact 已有，自动汇总仍缺） | 两者 | — | 当前已输出 metrics / profile / trace CSV，并带有 grad-sync mode metadata | 已经能支撑通信与 backward 的第一轮定量分析 | 仍缺 `scaling_efficiency`、固定 plotting/report、per-step 汇总视图，以及统一报表入口 | 现在更合理的下一步是“补齐自动汇总与 scaling 口径”，而不是从零开始打点 |
| P2 | 混合并行 | MPI + OpenMP/BLAS 参数化 + 绑核策略固化 | 部分实现（线程数与脚本已有，绑核未固化） | 两者 | 混合并行 | 现有脚本已可通过 `OMP_NUM_THREADS`、`NPROC`、`GLOBAL_BATCH` 驱动 MPI 对比实验 | 已经能初步避免“配置全写死”，也方便做 scaling 实验 | 尚未固化 rank pinning / affinity / `OPENBLAS_NUM_THREADS` / `OMP_PROC_BIND` 等关键设置，也没有过订阅检查 | 这块现在属于“能跑实验，但系统性还不够” |
| P3 | 工程能力 | 可复现记录与实验追踪统一化 | 部分实现 | 两者 | — | 当前 qualification/HPO 路径已记录 `commit hash`、run id、部分配置与复现命令 | 已经比“只看终端输出”强很多 | 仍未统一覆盖普通训练 run 的机器信息、线程/绑核配置、完整命令行与 git 状态 | 下一步应该是把这层 metadata 下沉到所有正式实验 |
| P4 | 通信优化 | bucketed baseline / overlap qualification 的自动化收口 | 部分完成（功能已落地，验证体系未完全收口） | 两者 | 跨进程 | 不再是“先把 bucketing 做出来”，而是补齐固定实验口径、artifact schema 和 baseline 验证闭环 | 能把当前分布式基线从“能跑”提升到“可稳定比较、可复现汇报” | 容易被误做成继续堆 runtime 小改动，而忽略实验口径与报表自动化 | 现在最值钱的是把已有 baseline 变成铁打对照组 |
| P5 | 工程能力 | checkpoint / resume 的恢复连续性验证与实验纳入 | 已实现（基础版），验证仍未系统化 | 两者 | — | 当前代码已支持保存/恢复模型参数、优化器状态、epoch 和主要训练配置；下一步重点是把恢复后的 loss/acc 连续性、实验纳入方式与元数据记录固化 | 能把“有 checkpoint 功能”提升为“可被正式实验依赖的 checkpoint 能力” | 如果缺少恢复一致性验证，容易出现“功能存在但不敢作为正式实验依赖”的尴尬状态 | 现在的重点已经不是“从零实现”，而是把它收进正式实验闭环 |
| P6 | 输入管线 | DataLoader 减拷贝 / prefetch / decode overlap | 部分实现 | 两者 | CPU/内存流水 | 现已具备 batch buffer 复用、`BatchSource` 抽象，以及 Tiny-ImageNet 的按需流式加载 | 已经减少了一部分重复分配，并为后续 view/prefetch 留出了接口位置 | 仍没有异步 prefetch、连续区间快路径、MNIST 零拷贝 view，batch 索引也还是每步新建 | 下一步最值钱的是“去掉 batch_indices 分配 + 引入预取” |
| P7 | 算子实现 | oneDNN Conv backend 的性能工程化 | 部分实现（correctness-first 已完成） | CNN | 单机算子级 | 基于现有 optional backend 补 primitive cache、reorder cache、layout 传播与更稳的 benchmark 口径 | 有机会把 CNN 主线 CPU backend 再往前推一步 | 很容易从“有价值的工程化”滑向“过早微优化” | 前提是先把 benchmark 与 artifact 口径固定 |

### 当前阶段最低交付物

1. 单进程与 MPI 基线：`epoch time`、`samples/s`、`avg_step_time_ms`、`sync_wait ratio`。
2. 多进程扩展：`np=1/2/4` 的 `speedup`、`scaling efficiency`、`allreduce/sync ratio`。
3. 吞吐 vs 收敛：固定几组 `global batch / local batch / world size`，同时记录 `samples/s` 和最终精度或 loss 曲线。
4. 稳定性：同配置至少重复 `3-5` 次，输出均值和方差。
5. 可复现性：任意一次正式实验都能定位到配置、环境和提交版本。
6. 工程能力：支持中断后从 checkpoint 恢复继续训练。
7. 指标口径约束：以上指标的计算方式必须在 P1 阶段固定，避免后续阶段对比口径漂移。

## 3. 适合做的研究分支（主线完成后再开）

这些方向可以做，但不应该抢在主线前面。否则很容易变成“名词很多，基线不牢”。

| 优先级 | 类别 | 技术/做法 | 当前状态 | 适用（CNN/MLP） | 并行类型 | 核心思路（在干什么） | 典型收益 | 代价/坑点 | 实战备注 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| R1 | 分布式训练 | Local SGD / Periodic Averaging | 未实现 | 两者 | 跨进程 | 不是每步同步，而是本地更新若干步后再平均参数/梯度 | 降低通信频率，扩展性更好 | 收敛可能变差，超参更敏感 | 前置依赖是 P1（可比指标）+ 已有同步 DP baseline；必须和同步 DP 做清晰对照：`K=2/4/8...` |
| R2 | 论文相关 | IST（Independent Subnet Training） | 未实现 | 两者 | 跨进程 + 训练策略 | 每步只训练/同步部分子网，减少通信和激活开销 | 如果通信真是瓶颈，可能比全量同步更划算 | 实现和验证复杂，当前视觉任务上收益未必显著 | 需要明确论文来源、最小复现实验和对照设计 |
| R3 | 通信优化 | overlap backward and reduce 的性能证明与真正 overlap 化 | 部分实现（runtime 与 hook 已有，但仍 correctness-only） | 两者 | 跨进程 | 当前已经具备 `parameter-ready` hook、`BucketedOverlapRuntime` 和 `MPI_Iallreduce` 装配；下一步不是“从零实现”，而是证明并收紧真实 overlap 语义 | 如果能证明真实 overlap，可能进一步降低 `sync_wait` 暴露时间 | 当前最大的风险不是代码缺失，而是误把 correctness-only 路径当成性能结论 | 这应作为独立里程碑：先证明，再决定是否继续深推 runtime 复杂度 |
| R4 | 通信优化 | 梯度压缩 / 低比特通信 | 未实现 | 两者 | 跨进程 | 只传 top-k、量化梯度或更低精度梯度 | 通信量下降 | 可能影响收敛，调参麻烦 | 更适合作为后期研究分支，而不是当前主线 |
| R5 | 算子研究 | CNN backend 选择策略（reference / oneDNN / experimental GPU） | 部分实现 | CNN | 单机算子级 / 异构 | 在统一 workload 下比较不同卷积后端的正确性、热点拆分和吞吐 | 让“为什么要保留多个 backend”更有数据支撑 | 需要谨慎区分 correctness-first 与 performance-ready 语义 | 更适合写成技术附录或作品集 bonus 分支 |

## 4. 作品集升级方向：从课程项目到更真实的视觉训练系统

这一段不是“再加一个数据集”这么简单，而是把项目从课程实验升级成更接近工业训练系统的作品集项目。

### 升级的目标

1. 让数据规模和任务复杂度不再停留在 `MNIST`。
2. 让训练系统具备吞吐、profiling、可复现、断点续训、分布式这些工程能力。
3. 让项目叙事从“我手写了一个分类器”升级到“我做了一个可分析、可扩展、可复现的训练管线”。

### 建议迁移路径

1. 不要直接上完整 `ImageNet-1k`。
2. 当前其实已经走到 `Tiny-ImageNet`；因此更合理的下一步不是“退回 CIFAR-10”，而是把 `Tiny-ImageNet + CNN` 这条线先做扎实。
3. 然后再做 `ImageNet-100` 或自定义 `ImageNet` 子集。
4. 只有在管线、指标和资源都稳定后，才考虑完整 `ImageNet-1k`。

### 为什么不建议一直停留在 MNIST

1. `MNIST` 模型太小，很多带宽型优化不敏感，结果容易被启动开销和调度噪声影响。
2. 但减少 AllReduce 次数、固定 affinity、控制过订阅这类 latency / 系统型优化，仍然可能有可见收益。
3. 如果一直停留在 `MNIST`，复杂分布式优化的收益可能不够显著，也不够有说服力。
4. 迁移到更真实的数据规模后，吞吐、通信、输入管线瓶颈才更接近工业场景。

## 5. 升级后适合做的主线任务（更真实视觉任务阶段，按优先级）

这里放的是更适合在数据规模升级之后做的内容。它们很多在 `MNIST` 上也能做，但收益和说服力会在更真实的数据规模下明显提高。

| 优先级 | 类别 | 技术/做法 | 当前状态 | 适用（CNN/MLP） | 并行类型 | 核心思路（在干什么） | 典型收益 | 代价/坑点 | 实战备注 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| P8 | 数据集与输入管线 | ImageFolder 风格数据集 + normalize/shuffle + 更完整 augment/prefetch | 部分实现（Tiny-ImageNet 已有 ImageFolder-like + normalize/shuffle；augment/prefetch 仍缺） | CNN 为主 | CPU/IO 并行 | 在现有 Tiny-ImageNet streaming 基础上补齐更真实的图像输入管线 | 更接近工业训练流程 | 数据读取、增强、缓存都会变复杂 | 当前最稳的做法是先把 Tiny-ImageNet 这条线补完整 |
| P9 | Data I/O 工程化 | 缓存 / 打包格式 / 端到端吞吐优化 | 未实现 | 两者 | CPU/IO 并行 | 评估目录读图、缓存、打包格式（如 tar/record/LMDB 类思路）对训练吞吐的影响 | 让训练不再只看模型计算，而是看端到端吞吐 | 会引入数据格式管理和预处理成本 | 这是训练系统岗位很常问的一块 |
| P10 | 模型升级 | ResNet-18（优先）/ 精简版 ResNet | 未实现 | CNN | 单机 / 分布式 | 用比当前 configurable CNN 更现代的网络作为工业基线 | 更像真实视觉训练项目 | 当前 CNN 组件层还没有 `BatchNorm + residual block`；底层 `add` 原语已有，但模块级封装仍要补 | 对作品集说服力提升非常大 |
| P11 | 指标体系 | scaling efficiency / speedup / data loading ratio / end-to-end throughput | 未完善 | 两者 | — | 除了精度，还系统记录扩展性和系统瓶颈指标 | 结果更工程化，也更适合汇报 | 需要统一实验格式和统计口径 | 在更真实数据规模下更有说服力 |
| P12 | 训练效率 | 吞吐 vs 收敛权衡 | 未系统化 | 两者 | — | 比较不同 `global batch`、同步频率、数据管线设置下的速度与收敛表现 | 避免“只追吞吐不看收敛”的伪优化 | 需要更长训练和更稳定对照实验 | 这是训练系统岗位常考的判断题 |
| P13 | profiling 输出 | 固定生成 step breakdown / MPI breakdown / hotspot 报告 | 部分实现 | 两者 | — | 把已有 metrics/profile/trace 输出进一步固化成标准报告 | 让性能分析从“看日志”变成“看报表” | 需要规范输出 schema | 这是工业训练管线的重要观感来源 |
| P14 | 工程化输出 | 自动汇总报告（csv -> plot -> markdown/report） | 未实现 | 两者 | — | 把训练结果自动汇总成图表和报告 | 很适合作品集展示和复盘 | 需要固定实验 schema | 展示价值非常高 |
| P15 | 训练稳定性 | OOM / activation checkpoint / 大 batch 内存管理 | 未实现 | 两者 | 内存优化 | 面对更大模型和 batch 时，处理内存上限与激活保存成本 | 能把更大模型或 batch 跑起来，也更像真实训练系统 | 实现依赖底层内存管理和图执行方式 | 在 CPU 阶段可先建立概念，GPU 阶段会更关键 |
| P16 | 分布式训练 | SyncBN / GroupNorm / LayerNorm 替代 | 未实现 | CNN 为主 | 跨进程 / 算子 | 小 batch 或 DP 下改善归一化稳定性 | 训练更稳，可能提升精度 | SyncBN 有额外通信成本 | 当 batch 受限或 rank 增多时更重要 |
| P17 | 算子实现 | 卷积算法选择（reference / oneDNN 深化 / 更系统 benchmark） | 部分实现 | CNN | 单机算子级 | 在现有 backend 体系上形成更清晰的算法/后端选择依据 | 比“一刀切只有一种卷积实现”更真实 | 需要严谨的 workload 与 profile 设计 | 这比直接再堆一个新 backend 更有价值 |
| P18 | 分布式训练 | ZeRO / FSDP / Sharded | 未实现 | 两者 | 跨进程 | 把参数、梯度、优化器状态按 rank 分片，降低单进程内存占用 | 节省内存，占用比纯 DP 更优 | 通信和实现复杂度都显著上升 | 这是面试中常被追问的分片训练思路 |
| P19 | 通信优化 | ReduceScatter / AllGather / 拓扑与分组 | 未实现 | 两者 | 跨进程 | 在分片训练或层次化通信里，用不同 collective 和分组策略优化通信路径 | 比单纯 AllReduce 更接近工业实现 | 需要理解网络拓扑、node 内外分层、group 切分 | 适合放在 ZeRO/FSDP 之后理解和实现 |

### 升级后最低交付物

1. 一个更真实的数据集训练入口，例如当前 `Tiny-ImageNet` 的稳定主线，或进一步扩展到 `ImageNet-100`。
2. 一个更现代的模型基线，例如 `ResNet-18`。
3. 固定输出训练曲线、吞吐、扩展性、profiling 和端到端 I/O 指标图表。
4. 至少一组“吞吐 vs 收敛”对照实验，而不是只报最快配置。
5. 能展示一次完整的“从配置到结果到报告”的实验闭环。

## 6. 平台升级方向：GPU 异构加速（第二主线）

这一条应该放在 `CPU baseline`、`Tiny-ImageNet` 管线和 artifact 体系稳定之后。原因很直接：如果 CPU 版训练系统、指标体系和分布式基线还没有扎实，过早切到 GPU，后面很难分清瓶颈到底来自算法、通信、数据管线，还是来自设备迁移和 CUDA 工程本身。

这里说的“GPU 异构加速”不是简单地“换个设备跑”，而是把项目升级为一个真正的 `CPU + GPU` 异构训练系统：

1. `CPU` 负责数据加载、预处理、调度、日志、checkpoint、实验管理。
2. `GPU` 负责主要算子计算，例如 `GEMM / Conv / Activation / Backward`。
3. 需要显式处理 `host-device` 数据传输、设备内存管理、同步与异步执行。

| 优先级 | 类别 | 技术/做法 | 当前状态 | 适用（CNN/MLP） | 并行类型 | 核心思路（在干什么） | 典型收益 | 代价/坑点 | 实战备注 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| G1 | 平台升级 | GPU 算子卸载（Conv 优先） | 部分实现（已有 cuDNN probe 与 experimental conv path） | CNN 为主 | CPU-GPU 异构 | 先把最重的卷积算子迁到 GPU，其他控制逻辑仍留在 CPU | 吞吐提升潜力最大，也最容易讲清楚收益来源 | 当前还没有正式训练入口、设备张量抽象与端到端数据流 | 现阶段的正确表述是“算子级探索已开始” |
| G2 | 平台升级 | 设备抽象（Tensor / Device / Stream） | 未实现 | 两者 | CPU-GPU 异构 | 给张量和算子引入 CPU/GPU 设备语义，避免代码里散落大量特殊分支 | 后续扩展 GPU 路线更干净 | 需要重构底层张量和算子接口 | 这是长期可维护性的关键，但不应该一上来重构半个框架 |
| G3 | 输入管线 | CPU 预处理 + GPU 训练流水 | 未实现 | CNN 为主 | CPU-GPU 异构 | 让数据加载和 GPU 计算重叠，减少 GPU 等数据 | 提升设备利用率，体现异构系统设计能力 | 需要 pinned memory、prefetch、拷贝与计算重叠 | 这类内容很适合作品集展示 |
| G4 | 数值与吞吐 | GPU 混合精度（FP16 / BF16） | 未实现 | 两者 | GPU 数值路径 | 在 GPU 路线上再引入低精度，进一步提高吞吐和降低显存占用 | 现代 GPU 上收益通常明显 | 需要 loss scaling、数值稳定性和算子支持 | 这项应该放在 GPU 主线能稳定训练之后 |
| G5 | 分布式训练 | 多 GPU 数据并行（单机多卡或多机） | 未实现 | 两者 | GPU + 跨设备 | 在 GPU 版训练管线上继续做同步 DP、bucketing、overlap | 更接近工业训练系统 | 复杂度显著上升，需要重新审视通信和显存瓶颈 | 应该建立在单 GPU 训练稳定之后 |

### GPU 异构加速最低交付物

1. 至少一个关键算子成功迁移到 GPU，例如 `conv`。
2. 能跑通一个完整训练任务，而不是只做 isolated probe。
3. 输出 `CPU vs GPU` 的吞吐、step time、热点对比。
4. 说明清楚数据传输、设备内存、数值精度、OOM 风险和 profiling 结果。

## 7. 当前低优先级 / 暂不建议先做

这些方向不是没价值，而是和你当前项目阶段不匹配，或者会把主线稀释掉。

| 优先级 | 类别 | 技术/做法 | 当前状态 | 适用（CNN/MLP） | 并行类型 | 核心思路（在干什么） | 典型收益 | 代价/坑点 | 实战备注 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| L1 | 分布式训练 | 张量并行 TP（Linear/GEMM 切分） | 未实现 | MLP 更典型 | 跨进程 | 把单层大矩阵分给不同设备算 | 大层能放下，单层吞吐可提升 | 通信频繁，实现复杂 | 你现在的模型和阶段都不需要先做 |
| L2 | 分布式训练 | 流水线并行 PP（按层切 stage） | 未实现 | 深网络 | 跨进程 | 按层切 stage，用 micro-batch 流水推进 | 单设备不必放全模型 | bubble、调度、激活管理复杂 | 等模型深度和资源规模再说 |
| L3 | 分布式训练 | 空间并行（Spatial Parallel for Conv） | 未实现 | CNN | 跨进程 | 按 feature map 空间维切卷积计算 | 超大图像 / 3D 卷积时有效 | halo exchange 很麻烦 | 对当前视觉任务优先级很低 |
| L4 | 分布式训练 | 专家并行（MoE） | 未实现 | MLP / Transformer 为主 | 跨进程 | 不同专家放不同设备，样本动态路由 | 参数规模可大幅提升 | 路由、负载均衡、all-to-all 都复杂 | 与当前 CNN/图像分类主线不匹配 |
| L5 | 数值与吞吐 | 混合精度（FP16/BF16）CPU 主线 | 未实现 | 两者 | 数值路径 | 用低精度换吞吐和显存 | 在 GPU 或新硬件上常有明显收益 | 当前 CPU 主线收益不稳定，数值风险也更高 | 更适合作为未来 GPU 路线 |
| L6 | 数值与吞吐 | TF32 / Tensor Cores 路径 | 未实现 | 两者 | 硬件专用 | 利用 GPU 张量核提速 GEMM/Conv | GPU 上提升明显 | 完全依赖 NVIDIA GPU | 当前项目不适用 |
| L7 | 推理与部署 | 量化（INT8/FP8）、剪枝、蒸馏 | 未实现 | 两者 | 推理优化 | 压缩模型、降低推理成本 | 推理速度和部署体积更好 | 与当前训练系统主线关系不大 | 可以以后作为部署方向单独做 |

## 8. 建议的实际路线

1. 先把当前 `Tiny-ImageNet + CNN + MPI artifact` 这条主线做扎实，而不是把系统验证退回到纯 `MNIST`。
2. `P1-P4` 先收口：固定 metrics/report schema、补齐 scaling 口径、把 `bucketed baseline` 与 `overlap correctness-only` 的资格验证流程自动化。
3. **Gate A（P1-P4 后）**：提供 `np=1/2/4` 的 `speedup / scaling efficiency / sync_wait_ratio`，至少 `3` 次重复的均值/方差，并能明确区分 `bucketed baseline` 与 `overlap correctness-only` 的对外语义。
4. `P5-P7` 再推进：固化 checkpoint/resume 的恢复连续性验证、继续做 DataLoader 去拷贝与 prefetch、把 oneDNN backend 从 correctness-first 往更稳定的 benchmark-ready 状态推进。
5. **Gate B（P5-P7 后）**：checkpoint 恢复后 loss/acc 曲线连续且可复现；输入管线优化前后吞吐差异可复现；oneDNN/reference 至少在固定 workload 下有清晰 benchmark 结论。
6. 主线稳定后，再决定是否开 `Local SGD`、`IST`、真正的 overlap 性能证明这些研究分支。
7. 如果后面有稳定 GPU 资源，再开 `GPU 异构加速` 第二主线；当前仓库里的 `cuDNN` probe 只作为准备工作与技术储备，不应抢主线优先级。
8. 最后再考虑 `ResNet-18`、`BatchNorm + residual block`、`ZeRO`、更复杂通信优化、或多 GPU / 多机训练。
