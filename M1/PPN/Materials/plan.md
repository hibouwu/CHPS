# 8 周执行计划（MVP 冲刺版）

## 目标与范围

在 8 周内完成以下主线：

1. 彻底吃透现有项目（能独立讲清理论 + 代码实现）。
2. MNIST 主线任务完成 `P1-P6`（其中 `P6` 做基础可用版）。
3. 跑通 `Tiny-ImageNet + ResNet-18` 并输出可复现实验报告闭环。

> 计划起始日期：`2026-03-09`  
> 计划结束日期：`2026-05-03`

---

## 执行原则

1. 每个任务节点都必须有“可验证交付物”，禁止只学习不落盘。
2. 优先主线，不在冲刺期并行开启 `R1-R4` 研究分支。
3. AI 仅用于提速，不替代理解：核心逻辑自己讲清、自己复盘。
4. 排序规则固定：按**进度阶段** -> **任务顺序 ID** -> **任务类型**执行。

---

## 任务总览（按进度 -> 顺序 -> 类型）

| 进度阶段 | 顺序 ID | 类型 | 时间窗 | 任务 | 核心交付 |
| --- | --- | --- | --- | --- | --- |
| P1 训练主链掌握 | T01-T07 | 验证/读码/推导/复述 | 03/09-03/15 | 单机链路完整掌握 | `output/week1/*.md` |
| P2 CNN+MPI 深挖 | T08-T14 | 读码/测试映射/推导/复述 | 03/16-03/22 | CNN 与 MPI 路径掌握 | `output/week2/*.md` |
| P3 指标体系（P1） | T15-T17 | 工程实现 | 03/23-03/29 | 打点与 CSV 口径 | `metrics.csv` + 字段口径文档 |
| P4 混合并行 + 复现（P2/P3） | T18-T20 | 脚本/实验管理 | 03/30-04/05 | 绑核固化 + 元信息记录 | Gate A 报告 |
| P5 通信优化（P4） | T21-T23 | 通信实现/实验 | 04/06-04/12 | 梯度 bucketing | 数值一致 + 性能对比 |
| P6 工程可靠性（P5） | T24-T26 | 存档恢复/数据管线 | 04/13-04/19 | checkpoint/resume + DataLoader 基础优化 | Gate B 报告 |
| P7 任务升级 | T27-T29 | 数据集/模型实现 | 04/20-04/26 | Tiny-ImageNet + ResNet-18 跑通 | 基础收敛曲线 |
| P8 结果闭环 | T30-T32 | 实验编排/报告自动化 | 04/27-05/03 | 配置到报告全链路 | 最终结果包 |

---

## 阶段 P1（03/09-03/15）：训练主链掌握

### 任务 T01（03/09，类型：验证）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 确认仓库处于可构建、可测试、可运行的基线状态 |
| 前置输入 | 当前分支代码，`build` 可重建 |
| 执行步骤 | 1) 记录系统信息（CPU/编译器/CMake）<br>2) `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release`<br>3) `cmake --build build -j$(nproc)`<br>4) `ctest --test-dir build -N`<br>5) 跑核心测试：`Matrix/MLP/Autodiff/Optimizer`<br>6) 跑一次最小训练命令并保存日志 |
| 交付文件 | `output/week1/day1_baseline.md` |
| 验收标准 | 文档包含命令、测试通过/失败、失败原因（如有）、训练日志路径 |
| 回退策略 | 若构建失败，仅定位首个错误并记录，不进入功能改造 |

### 任务 T02（03/10，类型：读码）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 吃透 `main` 入口：参数解析、模型构建、训练装配 |
| 前置输入 | T01 基线验证结果 |
| 执行步骤 | 1) 阅读 `src/main.cpp` 参数分支<br>2) 阅读 MLP/CNN 构建分支<br>3) 阅读数据加载与 Trainer 初始化路径<br>4) 画对象装配图（Model/Loss/Optimizer/DataLoader/Trainer）<br>5) 写 10 行以内入口总结 |
| 交付文件 | `output/week1/day2_entry_flow.md` |
| 验收标准 | 能口述“CLI -> 第一轮训练循环开始”的路径 |
| 回退策略 | 若流程图不清晰，用函数调用顺序表替代 |

### 任务 T03（03/11，类型：读码）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 吃透单个 epoch 的 batch 生命周期 |
| 前置输入 | T02 入口流程图 |
| 执行步骤 | 1) 阅读 `src/trainer.cpp`<br>2) 阅读 `src/dataloader.cpp`<br>3) 梳理 shape：`inputs -> preds -> loss`<br>4) 列 `train/evaluate` 分支差异<br>5) 写 `step` 组成清单（data/fwd+bwd/sync/opt 概念位置） |
| 交付文件 | `output/week1/day3_train_loop.md` |
| 验收标准 | 不看代码可讲清一个 batch 内发生了什么 |
| 回退策略 | 若细节过多，先锁最短路径再补异常分支 |

### 任务 T04（03/12，类型：推导）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 吃透 autodiff 核心机制 |
| 前置输入 | T03 的 step 流程 |
| 执行步骤 | 1) 阅读 `src/node.cpp` 的 `topoSort/backward`<br>2) 阅读 `src/maths_ops.cpp` 的 `add/matmul/relu`<br>3) 手推 `matmul` 梯度<br>4) 手推 `relu` 梯度<br>5) 建立“公式 -> 代码行”映射 |
| 交付文件 | `output/week1/day4_autodiff.md` |
| 验收标准 | 能解释“拓扑序 + 反向遍历 + 梯度累加” |
| 回退策略 | 若推导卡住，先用 1x1/1x2 小矩阵示例验证 |

### 任务 T05（03/13，类型：推导+验证）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 吃透损失定义与参数更新规则 |
| 前置输入 | T04 梯度理解 |
| 执行步骤 | 1) 阅读 `src/loss.cpp`（CE/MSE）<br>2) 阅读 `src/optimizer.cpp`（SGD/Momentum/AdamW）<br>3) 写 `loss_sum -> avg_loss` 关系<br>4) 写 `gradScale` 在 `step` 中的作用<br>5) 跑 `OptimizerTest/GradientCheckTest` 复核 |
| 交付文件 | `output/week1/day5_loss_opt.md` |
| 验收标准 | 能解释“为什么按 global batch 缩放梯度” |
| 回退策略 | 若 AdamW 不扎实，先讲透 SGD/Momentum，AdamW 次节点补 |

### 任务 T06（03/14，类型：复述）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 闭卷复述并发现盲点 |
| 前置输入 | T01-T05 所有文档 |
| 执行步骤 | 1) 不看代码做 10-15 分钟讲解稿<br>2) 回答 5 个固定问题（DataLoader/loss/backward/gradScale/MPI 分叉）<br>3) 标记不会答的问题<br>4) 回源码补齐<br>5) 再复述一次（5 分钟） |
| 交付文件 | `output/week1/day6_closed_book.md` |
| 验收标准 | 第二次复述明显更顺，关键链路无中断 |
| 回退策略 | 若卡顿，拆成“入口/循环/反传/更新”四段单练 |

### 任务 T07（03/15，类型：收口）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 收口阶段 P1 并准备进入 P2 |
| 前置输入 | P1 全部交付文档 |
| 执行步骤 | 1) 汇总 P1 交付清单<br>2) 提炼至少 3 个优化候选（附文件位置）<br>3) 写 P2 输入（CNN/MPI/数学推导准备）<br>4) 补齐缺失项 |
| 交付文件 | `output/week1/week1_summary.md` |
| 验收标准 | P1 产物完整且可复述 train step |
| 回退策略 | 缺项过多时优先补“可复述链路”相关文档 |

---

## 阶段 P2（03/16-03/22）：CNN + MPI + 数学细节

### 任务 T08（03/16，类型：读码）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 吃透 CNN 配置系统（默认、扩展、校验） |
| 前置输入 | P1 主链理解 |
| 执行步骤 | 1) 阅读 CNN 配置结构与默认扩展逻辑<br>2) 列字段依赖（channels/kernels/strides/paddings/pool）<br>3) 列合法与非法配置样例<br>4) 对齐 CLI 参数映射 |
| 交付文件 | `output/week2/day1_cnn_config.md` |
| 验收标准 | 能给出合法最小配置并解释原因 |
| 回退策略 | 字段太多时先锁 LeNet 默认路径 |

### 任务 T09（03/17，类型：读码）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 吃透 CNN forward shape 流 |
| 前置输入 | T08 配置理解 |
| 执行步骤 | 1) 阅读 `CNNNetwork::forward` 主干<br>2) 阅读 `Conv2DLayer` 与 `MaxPool2DLayer`<br>3) 写 `(N,C,H,W)` 逐层变化表<br>4) 写 flatten 与 FC 输入维度来源 |
| 交付文件 | `output/week2/day2_cnn_forward.md` |
| 验收标准 | 任意给配置可手算关键层 shape |
| 回退策略 | 推导出错时先验证一层 conv + 一层 pool 的最小路径 |

### 任务 T10（03/18，类型：测试映射）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 建立“测试 -> 实现”映射关系 |
| 前置输入 | T09 shape 表 |
| 执行步骤 | 1) 阅读 `tests/test_cnn_configurable.cpp` 全部 case<br>2) 建“case -> 模块 -> 防回归点”表<br>3) 标注覆盖空白<br>4) 执行测试并记录 |
| 交付文件 | `output/week2/day3_cnn_tests.md` |
| 验收标准 | 能解释每个 case 的存在意义 |
| 回退策略 | 优先覆盖 default/single/multi/backward 核心 case |

### 任务 T11（03/19，类型：读码+手算）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 吃透 MPI runtime 与数据切分策略 |
| 前置输入 | P1 的 main/trainer 理解 |
| 执行步骤 | 1) 阅读 `src/distributed/distributed.cpp`<br>2) 阅读 `main` 中 shard 逻辑<br>3) 手算 `np=1/2/4` 样本分配<br>4) 对比 train/test 切分差异 |
| 交付文件 | `output/week2/day4_mpi_shard.md` |
| 验收标准 | 能讲清 padded 与普通 round-robin 区别 |
| 回退策略 | 示例过复杂时固定总样本 10 条演算 |

### 任务 T12（03/20，类型：时序分析）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 吃透梯度同步与指标聚合路径 |
| 前置输入 | T11 MPI 基础 |
| 执行步骤 | 1) 梳理 `GradSyncFn` 调用位置<br>2) 画 `local backward -> allreduce -> optimizer step` 时序图<br>3) 梳理 `reduceMetrics` 聚合路径<br>4) 写通信瓶颈假设（逐参数 allreduce） |
| 交付文件 | `output/week2/day5_mpi_sync.md` |
| 验收标准 | 能准确指出通信发生在 train step 哪个阶段 |
| 回退策略 | 时序图不清时改为文本事件时间线 |

### 任务 T13（03/21，类型：推导）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 手推三类关键梯度并与实现对齐 |
| 前置输入 | T04 autodiff + T12 sync 路径 |
| 执行步骤 | 1) 手推 `matmul` 梯度<br>2) 手推 `CrossEntropy(softmax)` 梯度<br>3) 手推 `ReLU/GELU` 梯度<br>4) 建“公式 -> 实现位置”映射<br>5) 用测试结论核对 |
| 交付文件 | `output/week2/day6_grad_math.md` |
| 验收标准 | 三类梯度都能脱稿讲清核心推导 |
| 回退策略 | GELU 过慢时先固化 ReLU/CE，GELU 用近似导数补充 |

### 任务 T14（03/22，类型：收口）

| 项 | 细化内容 |
| --- | --- |
| 目标 | 收口阶段 P2 并准备进入 P3 |
| 前置输入 | P2 全部交付文档 |
| 执行步骤 | 1) 完成 15 分钟闭卷讲解稿（CNN+MPI+梯度）<br>2) 列盲点并补齐文档<br>3) 产出 P3（打点）准备清单 |
| 交付文件 | `output/week2/week2_summary.md` |
| 验收标准 | 能独立讲清 CNN 路径 + MPI 同步 + 关键梯度 |
| 回退策略 | 有盲点时将下个任务前 30 分钟用于补盲 |

### P1-P2 验证场景

1. 构建验证：`build` 可完成配置与编译。
2. 测试验证：`AutodiffTest`, `GradientCheckTest`, `OptimizerTest`, `CNNConfigurableTest` 可执行并记录。
3. 训练烟雾验证：至少一次最小训练命令成功并有日志。
4. 理解验证：P1/P2 各完成一次闭卷讲解与问答。

### P1-P2 默认假设

1. 先执行 P1-P2，不并行推进 P3 编码任务。
2. 该阶段以学习和验证为主，不引入大规模功能改动。
3. 交付文件当天落盘，不允许后补堆积。

---

## 阶段 P3-P8（03/23-05/03）：实现与扩展任务

| 进度阶段 | 顺序 ID | 类型 | 任务说明 | 交付 | 验收 |
| --- | --- | --- | --- | --- | --- |
| P3 | T15 | 工程实现 | 固定指标口径：`step=data+fwd_bwd+sync+opt` | 口径文档 | 公式与实现一致 |
| P3 | T16 | 工程实现 | 增加计时打点：`step/epoch/data/fwd_bwd/sync/opt` | `metrics.csv` | 字段完整且稳定输出 |
| P3 | T17 | 结果规范 | 固定 CSV schema（自动报告输入） | schema 说明 | 后续脚本可直接消费 |
| P4 | T18 | 系统脚本 | 固化线程与 affinity 启动脚本 | 启动脚本 + 日志项 | 参数可复现 |
| P4 | T19 | 实验追踪 | 记录 seed/命令/MPI world size/commit/机器信息 | 元信息文件 | 任意实验可回放 |
| P4 | T20 | 扩展实验 | 跑 `np=1/2/4` + 3-5 次重复统计 | Gate A 报告 | speedup/efficiency/allreduce_ratio |
| P5 | T21 | 通信实现 | 设计 bucket 与 offset 管理 | 设计文档 | 覆盖全部可训练参数 |
| P5 | T22 | 通信实现 | 实现 bucket allreduce（可切换路径） | 代码 + 开关 | per-param/bucketed 可切换 |
| P5 | T23 | 实验验证 | 数值一致 + 性能对比 | 对比图表 | 与基线一致且有收益 |
| P6 | T24 | 工程可靠性 | checkpoint：参数/优化器/epoch/step/随机状态 | 存档文件规范 | 可恢复训练 |
| P6 | T25 | 工程可靠性 | resume：中断恢复继续训练 | 恢复脚本/入口 | 曲线连续 |
| P6 | T26 | 数据管线 | DataLoader 基础减拷贝优化 | 对比实验 | 吞吐可见提升或更稳定 |
| P7 | T27 | 数据集升级 | Tiny-ImageNet 数据入口 | 数据加载模块 | 可跑训练 |
| P7 | T28 | 模型升级 | `BatchNorm + residual block + ResNet-18` | 模型实现 | 单机可收敛 |
| P7 | T29 | 稳定性验证 | 训练稳定性与基础曲线 | 曲线图 | loss/acc 合理 |
| P8 | T30 | 实验编排 | 固定实验矩阵（配置集合/重复次数） | 实验清单 | 可一键重跑 |
| P8 | T31 | 报告自动化 | `csv -> 统计 -> 绘图 -> markdown` | 自动化脚本 | 报告自动生成 |
| P8 | T32 | 最终收口 | 复现检查 + 结果打包 | 最终结果包 | 配置到报告全链路闭环 |

---

## 执行节奏建议（单任务循环）

1. 读码/设计：明确目标、风险、验收口径。
2. 实施/验证：完成任务并跑最小验证。
3. 交付/复盘：当天写交付文档，更新下一任务输入。

---

## 风险与回退策略

1. P5（bucketing）延误超过 2 天：先交付“可切换 + 数值一致”，性能优化后移。
2. P7（ResNet-18）训练不稳定：先锁定最小可跑配置，再补 BN 与超参。
3. 总进度落后超过 1 阶段：优先保证 `P1-P6 + Tiny 入口 + ResNet-18 单机跑通`。

---

## 完成定义（Definition of Done）

1. 能独立讲清训练与反向传播实现，不依赖 AI 解释。
2. MNIST `P1-P6` 均有代码、实验结果和可复现记录。
3. Tiny-ImageNet + ResNet-18 可训练并有报告闭环输出。
