# C++ Neural Network Training Systems

## 1. One-line Positioning
适合投递训练系统 / AI Infrastructure / HPC 性能优化 / C++ 系统开发方向，重点是从零实现 C++ autodiff/MLP/CNN 训练系统，并扩展 GEMM、MPI 同步和 Tiny-ImageNet 实验路径。

## 2. Recruiter Summary
该项目从 C++ 实现 MNIST MLP 和自动微分引擎起步，逐步扩展到 CNN、Tiny-ImageNet、GEMM 内核优化、OpenMP/BLAS/AVX2/AVX-512 对比、MPI 同步数据并行、梯度 bucketing、通信重叠和 IST 风格周期同步。报告和 git 历史共同确认 Jianye 在设计、集成、MNIST 数据接入、optimizer、profiling、HPO、GEMM、Tiny-ImageNet dataset、Conv2D、MPI baseline/runtime 等模块中有实质贡献；IST runtime 和部分 gradient compression 提交主要来自 Xiang，需要避免写成个人完成。

## 3. My Work

- 项目整体内容：C++ neural network runtime，包含 Tensor/Matrix、dynamic DAG autodiff、MLP/CNN/ResNet 路径、MNIST/Tiny-ImageNet 数据加载、优化器、GEMM 后端、MPI 梯度同步、IST 风格同步实验和实验脚本。
- 时间范围：git 可确认整体项目时间为 2025-10-23 至 2026-05-05；Jianye 个人提交覆盖同一范围。第一阶段 MLP/autodiff/MNIST 主要集中在 2025-10 至 2026-01；第二阶段 CNN/Tiny-ImageNet/MPI/GEMM/IST 扩展主要集中在 2026-02 至 2026-05。
- 我实际完成或主要参与的内容：第一阶段报告明确写到 Jianye 发起设计文档和 UML、集成组件、更新 UML、参与 optimizer、接入 MNIST 并验证 pipeline、进行 profiling 和超参实验。git 进一步显示 Jianye 是仓库主要提交者之一（`shortlog` 中 91 个提交），并且当前 `src/gemm/GEMMGotoBLAS.cpp`、`src/gemm/matmul_dispatch.cpp`、`src/autograd/engine.cpp`、`src/tiny_imagenet_dataset.cpp` 基本/全部由 Jianye 贡献；`src/conv2d_layer.cpp`、`src/distributed/gradient_sync_runtime.cpp`、`src/distributed/distributed.cpp` 也以 Jianye 行数为主。
- 需要人工确认的个人贡献：`src/trainer.cpp` 当前 blame 中 Xiang/xiang024 行数多于 Jianye，不能把 Trainer 全部写成个人完成；IST runtime 相关提交明确有 Xiang 的 `Add IST runtime sources...`；gradient compression 路径也有 Xiang 和 Hao 的提交，不能写成个人独立完成。

## 4. Technical Stack
- 语言：C++，部分 C/Python/Shell 脚本
- 核心模块：autodiff DAG, `Tensor/Matrix`, `Node`, `MathOps`, `Trainer`, `Optimizer`, `LossFunction`
- 模型：MLP, CNN, ResNet
- 数据集：MNIST, Tiny-ImageNet
- 并行与性能：OpenMP, OpenBLAS/BLAS, AVX2, AVX-512, GotoBLAS-style blocking/packing/micro-kernel, `std::chrono`, `gprof`, `perf`/affinity 脚本
- 分布式：MPI, synchronous data parallel, gradient bucketing, overlap bucketed sync, fp16/i8 compression framework, IST-inspired periodic sync
- 关键路径：`include/autograd/*`, `src/autograd/engine.cpp`, `include/distributed/*`, `src/distributed/*`, `src/gemm/*`, `include/ist/ist_runtime.hpp`, `src/ist/ist_runtime.cpp`, `scripts/ExperienceGEMM/*`, `scripts/Performance/*`, `scripts/ExperienceIST/*`

## 5. Work Path / 工作路径
- baseline 是什么：第一阶段 baseline 是 C++ from-scratch MLP + dynamic DAG autodiff，在 MNIST 上完成 forward/loss/backward/SGD 训练。
- 遇到的主要问题是什么：矩阵乘法占 naive 训练时间 96.4%；BLAS 后瓶颈转移到数据加载和内存分配；第二阶段进一步暴露 CNN/GEMM、Tiny-ImageNet 输入管线和 MPI 同步开销。
- 如何定位问题：使用 `gprof`、micro-benchmark、线程扩展实验、CPU affinity、GEMM workload family、MPI profile 的 `fwd_bwd/sync_total/sync_wait` 拆分。
- 做了哪些实现、重构或优化：第一阶段实现 autodiff/MLP/trainer/optimizer/data pipeline；第二阶段扩展 GEMM blocked/packing/GotoBLAS AVX2/AVX-512、CNN/Tiny-ImageNet、MPI bucketing/overlap、压缩框架、IST 风格周期同步。
- 如何验证：MNIST 训练曲线、超参网格实验、gprof 表、GEMM GFLOPS 图、MPI scaling 表、Tiny-ImageNet 训练曲线、IST 消融图。
- 结果如何：MNIST MLP 可达约 `98.2%` validation accuracy；naive 到 BLAS 的 1 epoch 端到端从 `13.27s` 到 `1.74s`，speedup `7.6x`；MNIST CNN MPI `np=1->4` 1 epoch 从 `31.66s` 到 `11.98s`，speedup `2.64x`；Tiny-ImageNet 当前过拟合，40 epoch train acc `47%`、test acc `7.24%`。
- 还有什么局限：第二阶段多项性能结论是阶段性/工程验证；Tiny-ImageNet 精度低；IST 只有小规模实验；真实 payload 压缩收益未验证；Trainer、IST、gradient compression 等多人模块需要按 git 归属谨慎表述。

## 6. Evidence Map

| Claim | Evidence | File / Path | Confidence | Interview Risk |
|---|---|---|---|---|
| 第一阶段实现 from-scratch MLP 和 autodiff 用于 MNIST | 报告 Introduction/Implémentation 描述完整 pipeline | `ppn-mnist-neural-network/ProjetRapportlatex/rapport.tex` | High | 需要能解释 DAG、topological backward 和 gradient accumulation |
| Matrix 是核心计算模块，matmul 有 naive/OpenMP/BLAS 多实现 | 报告 Matrix 章节和 `src/gemm/*` | `ppn-mnist-neural-network/ProjetRapportlatex/rapport.tex`; `ppn-mnist-neural-network/src/gemm/` | High | 具体 dispatch 逻辑可能被追问 |
| Jianye 负责设计发起、集成、MNIST 接入、pipeline 验证、profiling 和超参实验 | Déroulé du Projet 明确分工 | `ppn-mnist-neural-network/ProjetRapportlatex/rapport.tex` | High | 仅覆盖第一阶段，不自动覆盖第二阶段 |
| naive 训练中 `Matrix::matmul` 占 96.4% | gprof 表格 | `ppn-mnist-neural-network/ProjetRapportlatex/rapport.tex`; `ProjetRapportlatex/Images/gprof_analyse_naive.png` | High | gprof 采样精度和配置会被问 |
| BLAS 后端到端 1 epoch 从 `13.27s` 到 `1.74s`，speedup `7.6x` | Amdahl 分析段和 e2e 图 | `ppn-mnist-neural-network/ProjetRapportlatex/rapport.tex`; `ProjetRapportlatex/Images/e2e_benchmark_plot.png` | High | 微基准“数百倍”不能等同端到端 |
| MNIST MLP 最优配置约 `98.2%` validation accuracy | Synthèse 和 HPO 图表 | `ppn-mnist-neural-network/ProjetRapportlatex/rapport.tex`; `ProjetRapportlatex/Images/combined_*_results.png` | High | 数据集和验证集划分需说明 |
| 第二阶段加入 CNN、Tiny-ImageNet、MPI 同步和 GEMM 优化 | 中文报告引言和各章节 | `ppn-mnist-neural-network/ProjetRapportlatex/rapportS2_cn.tex`; `include/cnn_network.hpp`; `include/tiny_imagenet_dataset.hpp`; `include/distributed/` | High | 需区分 Jianye 主导文件和多人模块 |
| Jianye 对 GEMM 后端有强 git 证据 | 当前 `GEMMGotoBLAS.cpp` blame 1502 行均为 Jianye，`matmul_dispatch.cpp` 374 行均为 Jianye；相关提交包括 `optimise GEMM par le pattern GotoBLAS`、`MicroKernel and MacroKernel`、AVX2/AVX512 实验 | `ppn-mnist-neural-network/src/gemm/GEMMGotoBLAS.cpp`; `src/gemm/matmul_dispatch.cpp`; `scripts/ExperienceGEMM/` | High | 仍需避免声称自研 GEMM 全面超过 OpenBLAS |
| Jianye 对 Tiny-ImageNet dataset、Conv2D、MPI runtime 有实质 git 贡献 | blame 显示 `tiny_imagenet_dataset.cpp` 366/368 行为 Jianye，`conv2d_layer.cpp` 1322/1346 行为 Jianye，`gradient_sync_runtime.cpp` 452/580 行为 Jianye | `src/tiny_imagenet_dataset.cpp`; `src/conv2d_layer.cpp`; `src/distributed/gradient_sync_runtime.cpp` | High | gradient sync runtime 仍有 Xiang 贡献，不能写“独立完成” |
| IST runtime 不应写成 Jianye 独立完成 | git log 有 Xiang BIAN 提交 `Add IST runtime sources, tests, and build wiring` 和 epoch resample 支持 | `ppn-mnist-neural-network/.git`; `src/ist/ist_runtime.cpp`; `include/ist/ist_runtime.hpp` | High | 可写项目包含/团队实现，不能写个人实现 |
| GEMM 比较包含 OpenBLAS、OpenMP blocked/packing、GotoBLAS AVX2/AVX-512 | 中文报告 GEMM 章节和脚本目录 | `ppn-mnist-neural-network/ProjetRapportlatex/rapportS2_cn.tex`; `scripts/ExperienceGEMM/` | High | 自研内核多数情况下仍落后 OpenBLAS，不能夸大 |
| GotoBLAS AVX2/AVX512 8 线程 speedup 约 `3.23x`，OpenBLAS 约 `2.72x` | strong scaling 章节摘要 | `ppn-mnist-neural-network/ProjetRapportlatex/rapportS2_cn.tex` | Medium | 几何平均跨 9 workload；绝对性能 OpenBLAS 仍领先 |
| MNIST CNN MPI 从 1 到 4 进程 speedup `2.64x` | MPI scaling 表 | `ppn-mnist-neural-network/ProjetRapportlatex/rapportS2_cn.tex`; `ProjetRapportlatex/Images/mpi_scaling_fixed_local_batch.png` | High | global batch 变化影响准确率和步数，不能说纯 strong scaling |
| Tiny-ImageNet 路径可训练但过拟合严重 | Tiny-ImageNet 章节写 40 epoch train/test acc | `ppn-mnist-neural-network/ProjetRapportlatex/rapportS2_cn.tex` | High | 不应写成成功训练高精度模型 |
| IST 风格同步是工程可行性验证，`K=4` 约为 dense 耗时 98.9% | IST 消融章节 | `ppn-mnist-neural-network/ProjetRapportlatex/rapportS2_cn.tex`; `scripts/ExperienceIST/` | High | 只有小规模、多 seed 2 epoch，不是强性能结论 |
| 项目整体开发时间为 2025-10-23 至 2026-05-05 | git 首尾提交日期；Jianye 个人提交覆盖同一范围 | `ppn-mnist-neural-network/.git` | High | 这是仓库活动范围；不同阶段需分开表述 |

## 7. Detailed Project Experience / 详细项目经历母版
项目整体目标分两阶段。第一阶段是从零实现一个可训练的 C++ MLP/autodiff 系统，用 MNIST 验证深度学习训练的基本机制；第二阶段把它扩展为训练系统实验平台，用于比较 GEMM 内核、CNN/Tiny-ImageNet 负载、MPI 同步策略和周期同步近似方法。

第一阶段中，报告明确记录 Jianye 发起设计文档和 UML，集成各组件，更新 UML，参与 optimizer/loss 阶段中的 optimizer，实现或集成 MNIST 数据路径并验证完整 pipeline，还做了 profiling 和超参实验。这些内容适合作为个人贡献写入简历。第二阶段虽然报告缺少逐人分工，但 git 可以降低一部分不确定性：GEMM GotoBLAS/dispatch、Tiny-ImageNet dataset、Conv2D backend、autograd engine 和部分 distributed runtime 有明确 Jianye blame/commit 证据；Trainer、IST runtime、gradient compression 等模块应写成团队或多人协作。

技术实现上，autodiff 使用 dynamic DAG：每个 `Node` 保存 value、gradient 和依赖关系，backward 通过 topological traversal 传播梯度。训练框架由 `Trainer` 组织 `forward -> loss -> backward -> optimizer.step()`。`CrossEntropyLoss` 内部做稳定 softmax，logits 梯度为 `p-y`。矩阵计算后端支持 naive/OpenMP/BLAS，并在第二阶段进一步引入 blocked、packing、GotoBLAS-style micro-kernel、AVX2/AVX-512。

关键代码路径包括 `include/node.hpp`、`src/autograd/engine.cpp`、`src/maths_ops.cpp`、`include/trainer.hpp`、`src/trainer.cpp`、`include/optimizer.hpp`、`src/optimizer.cpp`、`src/gemm/`、`include/distributed/gradient_sync_runtime.hpp`、`src/distributed/gradient_sync_runtime.cpp`、`include/ist/ist_runtime.hpp`、`src/ist/ist_runtime.cpp`。

实验验证分三层。模型正确性层面，MNIST MLP 训练曲线和 HPO 结果显示约 `98.2%` validation accuracy。性能层面，gprof 显示 naive matmul 占 96.4%，换 BLAS 后端到端 1 epoch 从 `13.27s` 降到 `1.74s`。系统层面，第二阶段报告给出 GEMM strong scaling、MPI CNN scaling、Tiny-ImageNet 训练曲线和 IST 消融实验。

可量化结果必须谨慎裁剪：可以写 MNIST MLP `~98.2%`、BLAS 端到端 `7.6x`、MPI CNN `2.64x`，但需标注实验条件；不应把 Tiny-ImageNet 写成高精度成果，也不应把 IST 写成已证明有效的训练算法。

适合写进简历的是第一阶段个人贡献、autodiff engine、profiling/Amdahl、GEMM 后端、Tiny-ImageNet dataset/Conv2D、MPI baseline/runtime 中有 git 支撑的部分。只适合面试展开的是 Trainer 多人协作边界、IST 理论近似、梯度压缩 payload 尚未真实压缩的限制。

## 8. Resume Bullet Candidates / 简历要点候选

### 训练系统 / AI Infrastructure 方向
- 从零实现 C++ MLP/autodiff 训练 pipeline，组织 `forward -> loss -> backward -> optimizer.step()`，并在 MNIST 上验证约 `98.2%` validation accuracy。
- 集成 MNIST 数据加载、mini-batch DataLoader 和 optimizer 路径，完成可复现实验流程（第一阶段个人贡献有报告依据；`trainer.cpp` 为多人文件，表述时避免独占 Trainer）。
- 扩展同步数据并行路径，引入 gradient bucketing 和 overlap bucketed profile，用 `fwd_bwd/sync_total/sync_wait` 拆分通信等待。
- 实现/接入通信边界 compression 框架 `compress -> AllReduce -> decompress -> step`；当前 payload 仍为 float，真实通信收益需补充验证。
- 设计 IST-inspired periodic sync 路径，以 ownership mask 和 `K` step 窗口降低同步频率；目前为工程可行性验证，不作强性能 claim。

### HPC / 性能优化方向
- 用 gprof 定位 naive 训练中 `Matrix::matmul` 占 96.4%，切换 BLAS 后 1 epoch 从 `13.27s` 到 `1.74s`，端到端 speedup `7.6x`。
- 对 GEMM 后端进行 OpenMP、blocked、packing、GotoBLAS AVX2/AVX-512 对比，使用 workload family 和 affinity 控制评估线程扩展。
- 通过 CPU affinity 实验识别 16 线程 SMT 调度开销，context switch 从 2013 降至 14 的诊断结果用于确定线程预算。
- 在项目 workload 上比较 OpenBLAS 与自研 GotoBLAS-style 内核；8 线程几何平均 speedup 约 `3.23x`，但 OpenBLAS 多数绝对性能仍领先。
- 使用 `std::chrono`、warm-up、trimmed mean、gprof 和脚本化 plotting 形成可复现实验链路。

### C++ 后端 / 系统开发方向
- 用 C++ 组织 `Node/MathOps/Trainer/Optimizer/LossFunction` 模块，基于 `shared_ptr` 管理 dynamic DAG 生命周期。
- 将 matmul 后端做成运行时可选择实现，支持 naive/OpenMP/BLAS 和后续 GotoBLAS-style 内核实验。
- 设计 CNN、ResNet、MNIST/Tiny-ImageNet dataset、checkpoint 和 run artifact writer 等模块化接口。
- 编写 GoogleTest/benchmark 测试覆盖 autodiff、gradient check、GEMM microkernel、distributed sync、Tiny-ImageNet dataset 等路径。
- 用 MPI runtime 模块封装参数注册、bucket layout、gradient sync 和 sync profile，降低训练循环与通信实现耦合。

### 数值计算 / 科研计算方向
- 实现矩阵乘法、softmax cross entropy、SGD/Momentum/AdamW 等训练数值核心，并用固定 seed 控制实验可复现。
- 对 activation、batch size、hidden size、learning rate 做多 seed HPO 分析，确认 MNIST MLP 稳定配置 `LR=0.01, B=64, H=128, ReLU`。
- 用 Tiny-ImageNet 暴露输入管线、CNN 计算和 MPI 同步在更高负载下的瓶颈；当前 40 epoch test acc 仅 `7.24%`，不作为精度成果。
- 分析 GEMM micro-kernel 的 cache blocking、packing、TLB/page footprint 和 SIMD lane 组织，为科研计算内核优化提供证据。

## 9. Interview Pitch
- 30 秒讲法：这个项目是一个 C++ 训练系统实验平台。第一阶段我参与并有报告分工依据的是 MLP/autodiff、MNIST pipeline、optimizer、profiling 和 HPO；第二阶段项目扩展到 CNN、Tiny-ImageNet、GEMM AVX2/AVX-512、MPI bucketing/overlap 和 IST 风格同步。最硬的结果是 naive matmul 占 96.4%，BLAS 后 1 epoch 从 13.27 秒降到 1.74 秒，MNIST MLP 达到约 98.2%。
- 2 分钟讲法：我会把它分成模型正确性、单机性能和分布式系统三层讲。第一层是 C++ dynamic DAG autodiff：`Node` 保存 value/grad/dependency，训练循环执行 forward、loss、backward 和 optimizer step，MNIST MLP 用 CrossEntropyLoss 和 SGD 验证收敛。第二层是性能：gprof 显示 naive matmul 占 96.4%，切换 BLAS 后端端到端 speedup 7.6x，但瓶颈转移到数据加载和 Matrix allocation，这是 Amdahl 的典型例子。第三层是系统扩展：我可以重点讲 git 支撑较强的 GEMM blocking/packing/GotoBLAS AVX2/AVX-512、Tiny-ImageNet dataset、Conv2D 和部分 MPI runtime；IST 和 compression 我会明确说是团队模块，不写成个人独立成果。

可能被追问的 8 个问题：
1. Autodiff backward 怎么实现？回答要点：dynamic DAG、topological order、每个 op 用 lambda/grad_fn 回传局部梯度。
2. CrossEntropyLoss 为什么用 logits？回答要点：稳定 softmax，梯度 `p-y`，避免显式 softmax 后再求导的数值问题。
3. BLAS 为什么只带来 7.6x 而不是数百倍？回答要点：matmul 优化后瓶颈转到 dataset load 和 allocation，Amdahl 限制。
4. MNIST `98.2%` 条件是什么？回答要点：MLP, `LR=0.01`, batch 64, hidden 128, ReLU，报告 HPO 图和 3 seeds。
5. 自研 GotoBLAS 内核是否超过 OpenBLAS？回答要点：多数绝对性能仍 OpenBLAS 领先，自研路径用于理解 blocking/packing/SIMD 和 workload-specific tuning。
6. MPI `2.64x` 是否是严格 strong scaling？回答要点：不是，固定 local batch，global batch 变大，准确率和步数也受影响。
7. Tiny-ImageNet 为什么精度低？回答要点：当前 LeNet 风格 CNN、无数据增强、输入管线和 conv backward/im2col 成本仍需检查。
8. IST 路径能否作为算法成果？回答要点：不能过度声称；当前是 periodic sync 工程验证，dense delta 仍 AllReduce，只有小规模实验。

## 10. What Not To Overclaim
- 不要把第二阶段所有模块写成个人完成；git 支撑 GEMM/Tiny-ImageNet/Conv2D/部分 MPI runtime 的 Jianye 贡献，但 Trainer、IST、compression 是多人模块。
- 不要说自研 GEMM 全面超过 OpenBLAS；报告明确多数 workload OpenBLAS 仍领先。
- 不要把 Tiny-ImageNet 写成成功高精度训练；报告显示严重过拟合。
- 不要把 MPI scaling 写成纯 strong scaling；global batch 随进程数变化。
- 不要把 gradient compression 写成真实降低通信 payload；报告说明 payload 仍使用 float 缓冲区。
- 不要把 IST 写成等价同步 SGD 或成熟算法；报告明确是近似策略和工程验证。

## 11. Keywords for Internship Search
训练系统, AI Infrastructure（人工智能基础设施）, C++ 深度学习框架, 自动微分, 反向传播, MNIST, Tiny-ImageNet, MLP, CNN, ResNet, GEMM, OpenMP, OpenBLAS, AVX2, AVX-512, GotoBLAS, MPI, 分布式训练, Gradient Bucketing, Communication Overlap, Gradient Compression, Data Parallel Training, Autodiff, Training Runtime, HPC, Performance Profiling
