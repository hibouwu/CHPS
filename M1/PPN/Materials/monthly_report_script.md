# 本月工作汇报讲稿

## 1. 开场版本

老师好，我这个月的工作主要集中在三个方面。

第一，是把分布式训练里的梯度同步路径做了系统化整理和比较，重点比较了 `per_param`、`bucketed` 和 `overlap_bucketed` 三种模式，并把当前真正可靠的 correctness baseline 收口到了 `bucketed`。

第二，是对自动求导 backward 做了一次结构性重构。我把原来比较分散、偏原型式的 backward 执行方式，收敛成了显式的 `GradFn + BackwardContext + AutogradEngine` 模型，让系统第一次真正具备了 `final-ready` 和 `parameter-ready` 这种运行时语义。

第三，是继续压缩 autograd hot path 的框架开销。优化之后，profile 里很多原来属于 runtime 本身的开销已经明显下降，系统的主要瓶颈重新暴露到了卷积相关算子本身。

如果一句话概括，这个月我做的事情不是单纯“再堆一个优化点”，而是把训练系统往“结构更清晰、correctness 边界更明确、后续优化更可验证”的方向推进了一步。

---

## 2. 第一部分：分布式梯度同步这块我做了什么

这一部分我主要想讲清楚一件事：我不是简单在 MPI 上加了一层通信，而是把几种同步模式的语义边界理顺了。

最基础的模式是 `per_param`。它的逻辑比较直接，就是每个 rank 本地算完梯度之后，对每个参数分别做一次 `MPI_Allreduce`，最后用全局平均梯度更新参数。这个模式在数学上最容易理解，correctness 也最直观，但通信粒度太碎，小规模 collective 太多，开销比较大。

在这个基础上，我做的第一层优化是 `bucketed`。核心思想是把多个参数梯度先打包成连续 buffer，再按 bucket 发起 `Allreduce`。这个优化不改变数学语义，优化规则完全不变，改变的只是通信前梯度的组织方式。它的意义是两点：

第一，减少 `MPI_Allreduce` 次数，摊薄小消息带来的额外成本。

第二，为后续 overlap 路径提供一个稳定的静态 bucket layout，也就是参数顺序、bucket 切分、offset 和 pack/unpack 语义都先固定下来。

这一步目前已经作为分布式 correctness baseline 收口了。也就是说，现在如果我要回答“多 rank 下哪条路径是当前最可靠的 correctness 基线”，答案是 `bucketed`，而不是 `overlap_bucketed`。

然后在 `bucketed` 之上，我继续推进了 `overlap_bucketed`。但这里我这月最重要的收获其实不是“让它看起来更快”，而是把它的语义重新看清楚了：

真正难的不是“能不能早一点把通信发出去”，而是“多 rank 下所有进程是不是仍然按同一个 collective 序列前进”。

因为只要 collective 序列不一致，即使每个 rank 本地都觉得自己做得合理，最终也会出现 collective mismatch、hang，或者更隐蔽的 nondeterministic 错误。

所以我这段时间其实一直在围绕这个问题收紧边界。当前我采用的核心思路是：

- bucket index 作为全局唯一 collective 序号
- 所有 rank 都必须按这个固定前缀顺序推进
- overlap 路径不能靠“本地哪个 bucket 先 ready 就先发哪个”这种局部事实来驱动
- `onBackwardComplete()` 的职责只是补尾部，而不是重新决定通信顺序

这里我要特别说明一点：当前仓库里的 `overlap_bucketed` 还不能直接被当成“已经拿到 benchmark 资格的真实 overlap 结果”。现在更准确的说法是，它仍然是 correctness-only 路径。也就是说，它具备了进一步实现和验证真实 overlap 的工程基础，但还没有完成完整的 qualification。

所以如果老师问我，“你这个月是不是已经证明 overlap 确实带来稳定收益了”，我更严谨的回答会是：

还不能这么说。现阶段我能负责任地说的是，系统已经把 correctness foundation 和 overlap 试验路径明确分开了，并且 overlap 相关的 contract、trace 和测试证据链都比以前扎实得多，但 benchmark 资格这件事还需要后续继续验证。

---

## 3. 第二部分：为什么要重构 backward

这一部分是这个月最核心的系统性工作。

原来的自动求导实现是典型的原型式设计。每个节点在 forward 时绑定一个 `backwardFn` lambda，训练时做一次 reverse-topo 执行。这种方式在项目早期很好用，因为简单、快，能把 MLP、loss、激活函数、CNN 都先跑起来。

但它的问题是：它虽然能算对梯度，却不能显式表达 backward 的执行状态。

更具体地说，在旧设计里，一个节点往父节点 grad buffer 里写了一次梯度，系统只能看到“写了”，但不知道：

- 这是中间 contribution 还是最后一个 contribution
- 这个节点的输出梯度是否已经 `final-ready`
- 某个参数梯度是不是已经到了可以安全触发通信的时刻

这件事在单机同步训练里问题不大，因为反正所有同步都等 backward 全部结束之后再做。但一旦我要做按参数 ready 触发的 overlap、做更细粒度 profile，或者未来要对接更复杂的执行策略，这种“算对了但说不清执行进度”的设计就成了结构性限制。

所以这次重构的目标并不是改梯度公式，而是把 backward 变成一个显式、可调度、可观察的执行过程。

现在的结构是：

- `Node` 只保留必要的 autograd 元数据和输入依赖
- backward 规则被拆到显式的 `GradFn`
- backward 过程中需要的缓存放进 `BackwardContext`
- 真正的执行推进、贡献汇合和 ready 判定统一由 `AutogradEngine` 管理

这样做之后，系统第一次拥有了很关键的一层语义：一个节点什么时候才算真正 `final-ready`。

这件事对分布式训练特别重要，因为 overlap runtime 正是建立在这个语义之上的。只有当 engine 能可靠地告诉 runtime “这个参数梯度现在已经是本地最终可用状态”，runtime 才有资格去判断一个 bucket 是否可以安全 pack、是否可以尝试发起通信。

所以 backward 重构的价值不只是“代码更漂亮”，而是它把训练系统从“能工作”推进到了“运行时语义足够明确，能支撑更复杂的调度与验证”。

---

## 4. 第三部分：hot path 优化的结果怎么理解

在 backward 结构收敛之后，我继续做了一轮 hot path 优化。这里我关注的问题是：不是梯度算得对不对，而是这个 autograd engine 自己是不是太贵。

我这轮主要做了几件事：

- backward 执行状态改成按每次 backward 建立本地 dense index，减少基于指针和 `shared_ptr` 的状态查找
- `GradientContribution` 不再携带重对象，而是尽量用更轻的索引形式传递目标
- 小规模 contribution 列表改成 inline 容器，减少小对象堆分配
- grad merge 路径继续收紧，让第一次 materialize 和后续 accumulate 的成本被分开观测

这些优化之后，profile 给我的信号是比较明确的：

一方面，原来属于 autograd runtime 本身的一部分框架开销已经被明显压下去了。

另一方面，系统最主要的热点重新暴露在卷积相关路径上，比如 `im2col/col2im`、卷积前向 GEMM、卷积反向的 dX 和 dW 计算。

这其实是一个好现象。因为它说明我现在看到的瓶颈更接近真实算子本身，而不是被 framework overhead 遮住。

如果用一句更工程化的话来说，就是：

这个月我做的工作，把瓶颈从“系统框架层的执行开销”往“真正的数值计算内核”那边推了过去。

这意味着下一阶段如果还想继续明显缩短 epoch 时间，重点就不应该只放在 distributed runtime 上，而应该更多看卷积 CPU kernel、内存重排路径，以及训练配置本身。

---

## 5. 结果该怎么汇报，哪些话现在还不能说

这一段我建议汇报时单独强调，因为它能体现你对 correctness 和实验边界是清楚的。

我建议可以这样说：

“这个月我保留了 Tiny-ImageNet 上一些历史 profile 数据，它们说明通信占比可能已经下降，autograd hot path 的一部分成本也确实被压下去了。但是我没有把这些历史数字直接包装成已经通过重新认证的 overlap benchmark 结论。当前更稳妥的判断是：`bucketed` 已经作为 distributed correctness baseline 稳定下来，而 `overlap_bucketed` 仍然是 correctness-only 路径。也就是说，系统已经具备进一步实现和验证真实 overlap 的工程基础，但 benchmark qualification 这件事还没有在这个月内宣称完成。” 

这段话的好处是两点：

- 它不会过度承诺
- 它能体现你不是只在追求“看起来更快”，而是在先把 correctness foundation 打牢

---

## 6. 下个月准备怎么做

这里我建议讲得具体一点，分成三条。

第一条，是继续把 overlap qualification 做完整。

也就是围绕多 rank 下一致 collective 序、trace 证据链、以及真实 early launch 与最终数值结果的一致性，继续把测试和验证做扎实。目标不是“让它看起来有 overlap”，而是证明它在多 rank 下既正确又真的发生了可解释的 overlap。

第二条，是继续推进卷积相关热点的优化。

因为从目前 profile 看，主要瓶颈已经更集中地落在卷积前向、卷积反向和相关的内存重排上。所以下一步如果希望 epoch 时间继续下降，优化重点应该是 `im2col/col2im`、卷积 backward，以及相关 GEMM 路径。

第三条，是继续调整训练配置和模型本身。

因为现在 Tiny-ImageNet 上不仅有系统性能问题，也还有模型精度和训练效率之间的平衡问题。所以接下来还需要一起看学习率、batch size、模型结构和同步模式组合，找到更合理的实验配置。

---

## 7. 一个 3 到 5 分钟的精简口头版本

老师好，我这个月的工作主要分成三部分。

第一部分是分布式训练。我系统比较了三种梯度同步模式：逐参数同步、按 bucket 同步，以及 bucketed overlap。现在 `bucketed` 已经作为当前多 rank correctness baseline 稳定下来；而 `overlap_bucketed` 这条路径，我这月重点不是把它包装成性能结果，而是把它的语义边界和 correctness 基础理顺。目前更准确的说法是，它还是 correctness-only，还需要继续做 qualification，不能直接把历史测量当成已经确认的 overlap benchmark。

第二部分是 backward 重构。原来的 autograd 能算对梯度，但不能显式表达 backward 的执行状态，所以不适合支撑按参数 ready 触发的通信。这个月我把 backward 统一收敛成 `GradFn + BackwardContext + AutogradEngine` 的显式执行模型，让系统真正具备了 `final-ready` 和 `parameter-ready` 语义。这为后续 overlap 和更细粒度 profiling 提供了结构基础。

第三部分是 hot path 优化。我继续压缩了 autograd runtime 的框架开销。优化之后，profile 显示一部分 engine 自身开销已经下来了，系统的主要热点重新暴露在卷积相关算子上。这个结果说明，下一步如果还想继续明显提速，重点应该更多放在卷积 CPU kernel 和训练配置上，而不只是继续围绕通信 runtime 做文章。

如果总结一下，这个月我做的不是单点优化，而是把训练系统朝着“correctness 边界更明确、执行语义更清晰、后续优化更容易验证”的方向推进了一步。

---

## 8. 老师可能会问的问题与回答

### 问题 1：你现在的 overlap 到底算不算已经做出来了？

可以回答：

“如果从工程结构上说，支撑 overlap 的 runtime、hook 和 trace 基础已经比较完整了；但如果从 benchmark qualification 的标准说，还不能直接宣称已经完成。当前更稳妥的说法是，`overlap_bucketed` 仍然是 correctness-only，下一步还需要继续做多 rank 下一致性和真实 overlap 证据链的验证。”

### 问题 2：为什么要花这么大力气改 autograd，而不是直接优化通信？

可以回答：

“因为旧的 autograd 虽然能算对梯度，但它不表达执行状态。没有 `final-ready` / `parameter-ready` 这种语义，runtime 就不知道参数梯度什么时候真的可用，也就没法安全地做更细粒度通信调度。所以 backward 重构其实是在补 overlap 和 profiling 所依赖的基础设施。”

### 问题 3：你觉得现在最大的瓶颈在哪里？

可以回答：

“从目前 profile 来看，主要瓶颈已经更多回到卷积相关算子和内存重排路径，而不是纯粹的同步框架逻辑。这说明之前对 autograd runtime 的压缩是有效的，也说明下一步提速重点应该逐步转向卷积 kernel 和训练配置。”

### 问题 4：这个月最实质性的产出是什么？

可以回答：

“我觉得最实质性的产出有两个。一个是 backward 从原型式执行模型转成了显式 engine 模型，系统第一次有了清晰的 ready 语义。另一个是 distributed 这边的 correctness baseline 和 overlap 试验路径被明确区分开了，后续继续做 overlap 时，不会再把 baseline 和实验路径混在一起。”

