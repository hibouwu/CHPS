# 2. 算法家族、正则化与处理流程

[本课目录](../01_intro_zh.md) · [上一篇：数据、任务与学习函数](01_data_and_learning.md) · [下一篇：信息量、样本与 PAC 学习](03_information_and_pac.md)

<a id="regularization"></a>

<a id="algorithm-families"></a>

<a id="section-08"></a>

## The three families of ML algorithms

**机器学习算法的三个家族**

### 1 Local methods : based on grouping and local voting (or averaging)

**1. 局部方法：基于分组和局部投票（或平均）**


- k-Nearest-Neighbors

  k 近邻。

- Kernel rules

  核规则。

- Decision trees

  决策树。

<a id="classroom-local"></a>

**Local methods first define which observations are close**

**局部方法先决定“谁和谁接近”**

Local methods first identify samples near the point to be predicted, or assign the input to a local region, and then vote using labels or average numerical values within that region. For example, if four of the five nearest labeled samples belong to class 1, a majority vote predicts class 1.

局部方法先找到待预测点附近的样本，或把输入落到某个局部区域，再用区域内的标签投票、用数值平均。例如，若最近的 5 个已标注样本中有 4 个属于类别 1，多数投票就给出类别 1。

The key is not only the vote, but also the definition of closeness. Feature units, scales, distances, and partitions all change the neighbors. Decision trees construct regions through successive splits and can also serve as building blocks for ensembles. Describing a method as outdated in a transcript is an oral judgment, not evidence that local methods are generally ineffective; the usefulness of trees and their combinations remains task-dependent.

关键不只在投票，还在“近”如何定义。特征单位、尺度、距离及划分方式都会改变邻居。决策树通过逐步划分形成区域，也可作为集成方法的基础。转录中“过时”的说法属于口头评价，不能据此判定局部方法普遍无效；树方法及其组合的价值仍取决于具体任务。

*来源：[转录 3](../01_part3.md) 第 17–25 行。*

### 2 Global methods : based on functional optimization

**2. 全局方法：基于函数优化**


- Regularized regression (Ridge, LASSO...)

  正则化回归（Ridge、LASSO 等）。

- Support Vector Machines

  支持向量机。

- Boosting

  Boosting。

- Feedforward neural networks

  前馈神经网络。

<a id="classroom-global"></a>

**Optimizing a function usually means optimizing its parameters**

**在函数上优化，实际通常是在参数上优化**

If a candidate function is written as $h_\theta$, each parameter choice determines one candidate rule. Training combines performance on all training samples into an objective and adjusts $\theta$. Linear models adjust coefficients and feedforward networks adjust weights, for example. This turns abstract function selection into an implementable numerical calculation.

若候选函数写成 $h_\theta$，一次参数选择就确定一个候选规则。训练把所有训练样本上的表现汇总为目标，再调整 $\theta$。例如线性模型调整系数，前馈网络调整权重；这种写法把抽象的函数选择变成可实现的数值计算。

Global here means evaluating candidates through an overall objective. It does not guarantee that a numerical algorithm finds a global optimum, nor does it imply that every learning method has only finitely many parameters. The parameter dimension may be very large, but optimization remains an implementation step; it cannot replace choosing a function class and objective.

这里的“全局”描述用一个整体目标评价候选函数，不保证数值算法能找到全局最优解，也不表示所有学习方法都只有有限维参数。参数维数可以很大，但优化始终是方法的实现环节，不能替代函数类和目标的选择。

*来源：[转录 3](../01_part3.md) 第 26–31 行。*

### 3 Ensemble methods : based on resampling and aggregation

**3. 集成方法：基于重采样与聚合**


- Bagging

  Bagging。

- Boosting

  Boosting。

- Random forests

  随机森林。

<a id="classroom-ensemble"></a>

**An ensemble organizes multiple runs of a learning method**

**集成是在学习算法之上再加一层组织**

Ensemble methods run a base learning procedure repeatedly to produce several predictors, then vote or average their outputs. Varying the training data, learning several rules, and combining their votes adds a layer of organization above the base procedure. An ensemble can therefore be viewed as a meta-method: its inputs include both data and an available learning algorithm.

集成方法把一个基础学习过程多次运行，产生多个预测器，再对它们的输出进行投票或平均。改变训练数据、训练多条规则再让它们投票，相当于在基础学习过程上增加一层组织，因此它可以看作元方法：输入不仅是数据，还包含一个已经可用的学习算法。

Trees are frequently used as base models. On some smaller-scale data problems, combining them may be more appropriate and easier to implement than a complex network. This choice must be tested on concrete data; it is not a universal performance ranking. Listing boosting under both global and ensemble methods is consistent: an algorithm can combine models while also corresponding to an overall optimization objective. The three families are not mutually exclusive.

树经常作为基础模型。在某些规模较小的数据任务上，这种组合可能比复杂网络更合适，而且实施较简单；这是一种需要用具体数据验证的选择，不是所有任务上的性能排序。课件把 Boosting 同时列在全局与集成方法中，并不矛盾：一种算法可以既组合多个模型，又对应某个整体优化目标；三个家族不是严格互斥分类。

*来源：[转录 3](../01_part3.md) 第 32–43 行。*

<a id="shallow-deep"></a>


- Shallow learning : often relates to Tikhonov’s regularization

  浅层学习：通常与 Tikhonov 正则化有关。

$$
\min _ {h \in \mathcal {H}} \left(\frac {1}{n} \sum_ {i = 1} ^ {n} \ell (h (X _ {i}), Y _ {i}) + \lambda_ {n} \cdot \mathrm{pen} (h, n)\right)
$$


- The penalty controls the variance term (Occam’s razor)

  惩罚项控制方差项（奥卡姆剃刀原则）。

- It may also induce a desired structure of the function (e.g. sparsity).

  它也可以使函数具有所希望的结构，例如稀疏性。

- Deep Learning :

  深度学习：

- Universal approximators (zero bias)

  通用逼近器（零偏差）。

- No penalty term in the optimization but lots of tricks in the implementation which amount to implicit regularization

  优化中没有惩罚项，但实现中有许多技巧，它们起到隐式正则化的作用。

> **Note:** Zero bias idealizes approximation capacity. Universal approximation theorems have conditions on function classes, domains, activations, and network capacity; they do not say that any fixed network already has zero bias or that training a finite network on finite data achieves zero error. The statement that optimization has no penalty term is likewise a teaching contrast with shallow learning. Deep learning can also use explicit penalties, such as weight decay.

> **译注：** “零偏差”是对逼近能力的理想化表述：通用逼近定理有函数类、定义域、激活函数与网络容量等前提，不表示任意固定网络已经零偏差，也不保证有限网络、有限样本训练能达到零误差。“优化中没有惩罚项”也只是与浅层学习的教学对比，深度学习同样可以显式使用惩罚项（如权重衰减）。

<a id="classroom-regularization"></a>

**Why a penalty changes the function we select**

**惩罚项为什么会改变我们选中的函数**

The objective above has two parts: the first rewards fitting the training data, while the second raises the cost of certain complex functions or functions lacking a desired structure. The parameter $\lambda_n$ controls that cost's weight. Regularization thus changes the choice made during training; it is not merely a comment after training that a model is too complex.

上面的目标由两部分组成：第一项要求预测贴合训练数据，第二项提高某些复杂或不符合结构要求的函数的代价。参数 $\lambda_n$ 调节这种代价的权重。因此，正则化并不是训练结束后评价一句“模型太复杂”，而是会改变训练时的选择。

Consider polynomial degree. A constant function has little flexibility and a low complexity cost. A quadratic can bend and fit more variation. A high-degree polynomial can even pass through all training points, but that does not guarantee reliable predictions at new locations. Penalizing degree means weighing the reduction in training error against the increase in complexity cost.

以多项式次数为例：常数函数灵活性低，复杂度代价小；二次多项式能弯曲，可能贴合更多变化；高次多项式甚至能穿过所有训练点，但这并不保证新位置上的预测可靠。如果把次数作为惩罚，就要同时衡量训练误差减少多少、复杂度代价增加多少。

Penalties can also favor structures such as sparse coefficients or functions compatible with the problem's constraints. Occam's razor expresses a modeling preference for simpler explanations when fits are comparable; it does not guarantee that simpler models are always correct. Under some statistical settings and consistency conditions, regularization can gradually weaken as data increase. This does not require every problem's penalty to automatically vanish with sample size.

惩罚还可以偏好某种结构，例如稀疏系数或与问题约束相容的函数。奥卡姆剃刀在这里表达“拟合相当时偏好简单解释”的建模取向，并不保证简单模型永远正确。在某些统计设定与一致性条件下，数据增多后可以逐渐减弱正则化；这并不要求所有问题的惩罚项都随样本增加而自动趋零。

**Example: why a model with lower training error may still be rejected**

**例子：训练误差更低，为什么仍可能不被选中**

To illustrate the objective comparison, suppose a constant model has empirical loss 0.40 and degree 0, while a quadratic has empirical loss 0.10 and degree 2. With $\lambda=0.2$ and degree as the penalty, their objective values are $0.40+0.2\times0=0.40$ and $0.10+0.2\times2=0.50$, so the constant is preferred. With $\lambda=0.05$, the quadratic's objective becomes 0.20 and it is preferred instead.

只为展示目标如何比较，设某个常数模型的经验损失为 0.40、次数为 0；某个二次模型的经验损失为 0.10、次数为 2。取 $\lambda=0.2$ 且用次数作惩罚，则目标分别为 $0.40+0.2\times0=0.40$ 与 $0.10+0.2\times2=0.50$，常数模型被偏好；若改成 $\lambda=0.05$，二次模型的目标为 0.20，它就更有利。

The claim that a degree-50 polynomial passes through 50 points needs additional conditions. Precisely, for 50 distinct input coordinates, an interpolating polynomial of degree at most 49 always exists; higher degrees can also interpolate. If the same input coordinate has different labels, a single-valued function cannot pass through both exactly. Interpolation capacity, generalization, and the suitability of degree as a penalty are three different questions.

“50 个点用 50 次多项式通过所有点”还需要补足条件。精确地说，对于 50 个互异的横坐标，总存在次数至多为 49 的插值多项式；允许更高次数也可插值。若同一个横坐标出现不同标签，则不能用单值函数同时精确通过。插值能力、泛化能力和是否适合用次数惩罚，是三个不同的问题。

<details>
<summary>Further detail: why deep learning cannot be understood simply as having no penalty<br>延伸：深度学习为什么不能仅靠“没有惩罚项”来理解</summary>

A gap remains between universal approximation and good generalization: why do highly expressive networks not always behave as badly as simple intuition might suggest? Training procedures and design choices also regularize. Effects not written explicitly as objective penalties are commonly called implicit regularization. Parameter selection, experimentation, and tuning require practical experience; explaining a mechanism theoretically does not supply settings that work for every problem.

通用逼近能力与良好泛化之间仍有需要解释的距离：表示能力很强的网络为什么没有总是如简单直觉预想的那样失控？具体实现中的训练方式和设计选择也会起到正则化作用，其中未显式写成目标惩罚项的作用通常称为隐式正则化。选择参数、做实验和调节方案需要实践经验，理论解释机制不等于提供了对每个问题都有效的参数配方。

A neural network's loss depends on the task and is not always least squares. With squared error, the comparison is between prediction $h(x_i)$ and label $y_i$, not between input $x_i$ and label.

神经网络的损失由任务决定，并不总是最小二乘；使用平方误差时，比较的是预测 $h(x_i)$ 与标签 $y_i$，而不是输入 $x_i$ 与标签。

</details>

*来源：[转录 3](../01_part3.md) 第 44–122 行。*

<a id="frameworks"></a>

<a id="section-09"></a>

## The various frameworks of Machine Learning

**机器学习的不同框架**

![image](<../Images/01_intro/image_006.jpg>)

<a id="classroom-frameworks"></a>

**The learning framework depends on the feedback available**

**学习框架取决于可获得的反馈**

Supervised learning uses labels related to the target; unsupervised learning mainly discovers structure without target labels. Reinforcement learning involves actions and feedback from their consequences, so it cannot simply be treated as classification without labels. Transfer learning asks whether what was acquired in one task or data environment can help another task.

监督学习有与目标有关的标签；无监督学习主要从没有目标标签的数据中发现结构。强化学习涉及行动及其后果所提供的反馈，不能简单当成“没有标签的分类”。迁移学习则问：在一个任务或数据环境中获得的东西，能否帮助另一个任务。

The historical diagram above presents a view of the development of supervised, reinforcement, and transfer learning. Robots, vehicles, and dialogue systems may combine several approaches. The diagram reflects an outlook at a particular time; it cannot establish today's rate of progress or show that the frameworks are mutually exclusive. The course now focuses mainly on supervised learning, with some unsupervised methods.

上面的历史图展示了监督学习、强化学习与迁移学习的发展展望。机器人、车辆和对话系统可能组合多种技术。该图表达的是特定时期的展望，不能用来推算当前进展速度或认定几种框架互斥。课程接下来主要聚焦监督学习，并涉及部分无监督方法。

*来源：[转录 1](../01_part1.md) 第 492–518 行；[转录 3](../01_part3.md) 第 125–134 行；[转录 3](../01_part3.md) 第 197–200 行。*

<a id="pipeline"></a>

<a id="section-10"></a>

## Machine Learning in the real world A full pipeline for data processing

**现实中的机器学习：完整的数据处理流程**


- data collection and indexing

  数据收集与索引。

- modeling,

  建模。

- preprocessing (data quality, filtering and information compression)

  预处理（数据质量、过滤和信息压缩）。

- training,

  训练。

- evaluation,

  评价。

- monitoring,

  监控。

- capitalization

  成果与知识积累。

- learning-to-learn

  学习如何学习。

<a id="classroom-pipeline"></a>

**What labels, tasks, evaluation, and changes after deployment each address**

**标签、任务、评估和上线后的变化，分别解决什么问题**

**Collection and annotation determine whether training information is trustworthy.** Ordinary images and images requiring specialist knowledge impose different annotator requirements, costs, and time demands. Under a fixed budget, having more people each label one image versus having several people check the same image is a design tradeoff between coverage and label reliability. More labels are not automatically better.

**收集和标注决定训练所用信息是否可信。** 普通图像与需要专业知识的图像，标注者的要求、时间和成本不同。固定预算下，让更多人各标一张，还是让多人复核同一张，是覆盖范围与标注可靠性之间的设计问题；不是标注数量越大就自动越好。

**Modeling should start from the actual decision.** Suppose 100 people apply for loans and a classifier identifies 80 as good repayers. If the bank has only 10 euros and each applicant needs one euro, it can select at most ten. A good/bad output does not rank those 80 people. Scores or rankings are needed, followed by selection under the resource constraint.

**建模要从实际决策出发。** 假设有 100 名贷款申请人，分类器把 80 人判为好还款人；但银行只有 10 欧元，每人需要 1 欧元，因此最多只能选 10 人。一个“好／坏”输出无法区分这 80 人的先后，需要评分或排序，再结合资源限制选择对象。

The same applies to search engines: finding pages containing query terms does not place the most useful results first. When searching for a football match, recent results and old broadcast information may contain the same words but differ in value. The data and binary relevance labels can be identical while classification, ranking, and business decisions have different evaluation objectives. The score direction must be specified: does a higher score mean greater relevance, or is lower risk preferable? Real credit decisions also involve amounts, returns, and constraints; this example only illustrates why ranking is needed.

搜索引擎也是同样的道理：找到包含查询词的页面，不等于把最有用的结果排在前面。例如，搜索一场足球比赛时，近期赛况与很久以前的转播信息即使含有相同词语，其价值也不同。数据和二元相关性标签可以相同，分类、排序及业务决策的评价目标却可能不同。评分的方向应预先说清，是分数越高越相关，还是风险越低越优；真实信贷还涉及金额、收益和约束，此处的例子只说明排序的必要性。

**Evaluation asks whether a result still works on data not used to select it.** Training deliberately reduces training error, so using that same error as evidence of generalization is optimistic. A client might retain an independent dataset for a blind test. A validation set repeatedly used for tuning has a different role from a final test set. Repeatedly selecting models from test results also contaminates the final evaluation.

**评价要回答“对未参与选择的数据是否仍然有效”。** 训练本来就尽力降低训练误差，再拿同一误差当作泛化能力的证据，会产生乐观判断。例如，客户可以保留一份未参与训练的数据做盲测。用于反复调参的验证集与最终测试集职责不同；反复依据测试结果选择模型，也会污染最后的评价。

**Monitoring remains necessary after deployment.** Customer populations, preferences, products, and seasons can change, making tomorrow's data different from yesterday's. Changing preferences and products motivate updates in advertising recommendations; model versions, accumulated experience, and learning to learn likewise concern continued adaptation. These are motivations, not claims that every system must retrain daily or that every model update merely adds new data.

**上线以后仍需监控。** 客户群体、偏好、产品和季节都可能改变，使明天的数据不再与昨天相同。广告推荐中的偏好和产品变化，会推动规则更新；模型版本更新、经验积累和“学习如何学习”也都与持续适应有关。这些是动机，不意味着所有系统必须每天重训，也不意味着每次模型更新都只是在添加新数据。

<details>
<summary>旁例：人工标注和 Mechanical Turk</summary>

第三份转录开头把一个亚马逊人工任务平台反复识别成“机械键盘／机械按键”。结合发布任务、付费标注以及“机器里其实有人”的故事，上下文应指 Mechanical Turk，而不是键盘。这个故事提示：看似自动的 AI 系统背后可能有大量人的劳动；专业图像还需要专业判断，因此大规模高质量标注受预算和人员供给制约。

转录还包含“即将永久关闭”“九月底前可以发任务”及劳动者地区的泛化评论。这里将其保留为录课时的口头说法，不作为平台现状、使用期限或劳动力统计。原段的历史年代和棋类名称也未确定，不补造细节。

</details>

*来源：[转录 3](../01_part3.md) 第 1–16 行；[转录 3](../01_part3.md) 第 137–197 行。*

<a id="course-scope"></a>


- Data points are vectors in $\mathbb { R } ^ { d }$

  数据点是 $\mathbb { R } ^ { d }$ 中的向量。

- Setup : supervised, some unsupervised

  学习设定：监督学习，也涉及一些无监督学习。

- Problems : classification, (scoring), regression, dimension reduction, clustering

  问题：分类、（评分）、回归、降维、聚类。

Focus on : a) problem setup, b) performance assessment, c) algorithms, d) principles and best-practice

重点：a) 问题设定；b) 性能评价；c) 算法；d) 原则与最佳实践。

<a id="classroom-scope"></a>

**Using this lecture to select and evaluate tools**

**怎样把本讲方法用于选择和评价工具**

Selecting and evaluating tools can proceed through four questions: turn the business goal into a clear task; choose a performance criterion consistent with that goal; explain how the candidate algorithm produces a predictor from data; and decide when its results are trustworthy or need reevaluation. This applies both to developing models yourself and to using or purchasing models from others.

选择和评价工具，可以依次处理四个问题：把业务目的写成一个明确任务；选定与目标一致的性能标准；说明候选算法怎样从数据得到预测器；判断何时可信、何时需要重新评价。这既适用于自己开发，也适用于使用或采购他人的模型。

Abstracting data as vectors later does not eliminate collection, structure, annotation, or human involvement. It temporarily fixes these conditions to focus on how learning from data works. Statements about concentrating on global methods or not covering every proof describe teaching priorities; they do not replace the assumptions of individual theorems.

后面把数据抽象为向量，并不表示采集、结构、标注和人的环节消失了，只是暂时固定这些条件，集中研究从数据学习的机制。课中“主要讲全局方法”“不深入全部证明”等比例或侧重点是教学安排，不能代替每个定理的适用条件。

*来源：[转录 1](../01_part1.md) 第 359–425 行；[转录 3](../01_part3.md) 第 38–43 行；[转录 3](../01_part3.md) 第 197–202 行。*

<a id="section-11"></a>

## Supervised Machine Learning

**监督机器学习**


- Learning and information

  学习与信息。

- The bias-variance trade-off

  偏差—方差权衡。

- Empirical Risk Minimization

  经验风险最小化。

---

[本课目录](../01_intro_zh.md) · [上一篇：数据、任务与学习函数](01_data_and_learning.md) · [下一篇：信息量、样本与 PAC 学习](03_information_and_pac.md)
