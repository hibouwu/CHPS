# 1. 数据、任务与学习函数

[本课目录](../01_intro_zh.md) · [下一篇：算法家族、正则化与处理流程](02_algorithms_and_pipeline.md)

M2 CHPS

[Data & Apprentissage] Introduction à la science des données et à l’apprentissage

**数据科学与机器学习导论**

Nicolas Vayatis

<a id="section-01"></a>

## Introduction du cours

**课程导论**

<a id="classroom-reading"></a>

**What you should be able to explain in this course**

**这门课要求你会解释什么**

Understanding a method means being able to explain its task, inputs and outputs, underlying principle, assumptions, and the situations in which its results should not be trusted. Running a program or obtaining a number is not enough to judge whether the method is appropriate. Formal notation makes these questions precise; experiments turn abstract rules into observable results.

理解一种方法，需要说清楚：它解决什么任务、输入和输出是什么、核心原理是什么、依赖哪些条件，以及什么时候不能信任结果。只会运行程序或得到一个数值，还不足以判断方法是否适用。形式化记号用于把这些问题说准确，实验则用于把抽象规则变成可观察的结果。

When reading, first use a concrete problem to identify the objects, then return to the notation. For example, establish what maps an image to a pedestrian/no-pedestrian label before reading about a function from an input space to a label space. You need not master every proof when first encountering a formula, but you should know what its objects and conditions mean.

阅读下面的内容时，可以先用一个具体问题理解对象，再回来看符号。例如，先把“图像 → 是否有行人”对应清楚，再读“从输入空间到标签空间的函数”。不必在第一次遇到公式时就掌握全部证明，但要知道公式中的对象和条件分别是什么。

<a id="data-context"></a>

<a id="section-02"></a>

## Data science : information, pipelines, decisions

**数据科学：信息、处理流程与决策**


- Why ? Information –> Data –> Predictions, decisions, knowledge...

  为什么？信息 → 数据 → 预测、决策、知识……

- How ? Building pipelines from sensors to decisions

  怎样做？构建从传感器到决策的处理流程。

- For whom ? For humans ! with Humans in the loop (or not...)

  为谁服务？为人服务！人可以参与流程，也可以不参与……

<a id="classroom-data-decisions"></a>

**From sensor readings to useful decisions**

**从传感器读数到真正有用的决策**

**Information, data, and decisions are three distinct stages.** Real-world phenomena are measured to produce data that can be stored and processed; algorithms use those data to make predictions, which support actions or the accumulation of knowledge. Measurements may be noisy, sampling may miss changes between observations, and records may lack the timing or context needed to interpret a signal. Having a large amount of data therefore does not necessarily mean having the information needed to solve a problem.

**信息、数据和决策是三个不同环节。** 现实中发生的现象先经过测量，成为可保存和计算的数据；算法从这些数据中作出预测，预测再服务于行动或知识积累。测量可能有噪声，采样可能漏掉两次观测之间的变化，记录中也可能缺少理解信号所需的时间或背景信息。因此，“已有很多数据”并不等于“已有解决问题所需的信息”。

Consider fall detection in a nursing home: floor pressure sensors produce signals, a microcontroller processes them, a model decides whether a fall has occurred, and care staff receive an alert and decide whether to check on the resident. Electronics engineers, algorithm developers, facility staff, and sales staff face different constraints. Without communication between these stages, strong performance at an individual stage may still fail to produce a useful system.

以养老院的跌倒检测为例：地板中的压力传感器产生信号，微控制器处理信号，模型判断是否跌倒，护理人员接收警报并决定是否前去查看。电子工程师、算法开发者、机构工作人员和销售人员关注的约束不同；若各环节没有沟通，局部技术指标再好，也可能得不到有用的系统。

| System decision and reality<br>系统的判断与现实 | Immediate consequence<br>直接后果 | Why include it in the objective?<br>为什么也要计入目标 |
|---|---|---|
| A fall occurs; no alarm<br>实际跌倒，系统没有报警 | Delayed assistance may cause further injury<br>援助延迟，可能造成进一步伤害 | Missed detections have a high cost<br>漏检的代价很高 |
| No fall occurs; an alarm is raised<br>没有跌倒，系统却报警 | Repeated unnecessary staff responses<br>护理人员反复无效出动 | Persistent false alarms erode trust and can cause real alarms to be ignored<br>持续误报会削弱信任，使后续真实警报被忽视 |

Imagine a system producing 50 false alarms per hour. Even if the 51st alarm corresponds to a real fall, it may be ignored because of the preceding false alarms. This is alarm fatigue. The two kinds of error have different costs, but neither should be treated as entirely harmless. Later, [loss functions](06_empirical_and_true_risk.md#classroom-loss-cost) will express which errors matter more within a mathematical objective.

设想一个系统每小时误报 50 次：即使第 51 次警报对应真实跌倒，也可能因先前的反复误报而被忽视。这就是警报疲劳。两种错误的代价不同，但不能把其中一种当作完全无害。后面学习[损失函数](06_empirical_and_true_risk.md#classroom-loss-cost)时，就是把“什么错误更值得避免”写进数学目标。

The objective also determines the timescale. Fall detection supports immediate action, whereas a longitudinal study may seek to accumulate knowledge about a population over ten or twenty years. An algorithm may output a detection, a prediction, or a clue for further investigation, while a person may still make the final decision.

目标还决定时间尺度：跌倒检测服务于即时行动；长期随访研究可能希望在十年、二十年后积累对某类人群的知识。算法输出可以是检测、预测或知识线索，最终行动也可能由人来决定。

<details>
<summary>案例：数据湖、医院排班与“有数据却用不上”</summary>

转录记录的数据湖案例有一个共同问题：项目投入了存储、索引、数据库和访问架构，却在集中收集数据之后才考虑用途。具体困难包括：缺少目标需要的字段；数据虽在库中，却难以提取；或者大量数据没有明确的使用目标。

在转录所述的疫情期间案例中，有医院需要判断次日护理或影像服务能否运行，员工请假等信息虽然存在于信息系统中，却不能及时以合适格式汇总，因而无法支持眼前的预测与安排。这个例子说明，数据是否可用取决于具体问题、时间要求和访问流程，而不仅是存储容量。

另一个例子是监护设备：屏幕能显示读数，不代表医院保存了原始信号。厂商可能保有较细的数据，却缺乏病人在院期间和出院后的情境；医护人员了解事件和病程，却未必掌握相应的细粒度记录。信息分散在不同主体手里，会妨碍事件对齐和后续学习。这些案例反映了数据衔接的问题，不能推广成所有设备或医院的共同现状。

“要测量什么”和“要获得什么知识”可以不同：视频中的变化可以作为提取生理信号的线索，长期人群观察则可能用于研究治疗效果或药物的不同用途。原转录提到的药物名称 Ozempic、Viagra 及具体用途属于口头旁例，本讲不据此给出药理、适应证或因果结论。

</details>

<details>
<summary>讨论：数据访问、人是否参与、谁对结果负责</summary>

数据来源可以是互联网，也可以是连接计算机的物理传感器。公开可见、技术上可取得和有权使用是不同问题；还需要考虑个人数据、访问权限和数据盗取，不能把“能下载”视作充分条件。

人是否必须参与决策，可以通过一个思维实验来讨论：你是否愿意登上一架没有飞行员的飞机？判断涉及信任、事故风险、模拟器评价、硬件与软件可靠性、攻击和未预见情境，也涉及另一层代价：不采用可能改善结果的技术会怎样？这些是课堂思辨问题；转录中关于无人驾驶更安全、某次机场事故和医疗决策法律要求的说法没有在本讲核实，不能作为安全统计或现行法律结论。关键问题是：评价对象是什么，依据是什么，出现问题时有哪些相关方。

转录还出现“90% 的人口”等随口数字，不作为技术前提。此处保留讨论问题与原文入口，避免将含混的数字或地域性口头判断写成普遍规则。

</details>

*来源：[转录 1](../01_part1.md) 第 35–262 行。*

<a id="section-03"></a>

## The three pillars of data science

**数据科学的三个支柱**


1. Hardware : sensors, computing power, telecommunications, interfaces

   硬件：传感器、计算能力、通信、接口。

2. Software environments : for design, testing and operations

   软件环境：用于设计、测试和运行。

3. Mathematical modeling and algorithms : high dimensional statistics, dimension reduction, machine learning, network science, time series, etc.

   数学建模与算法：高维统计、降维、机器学习、网络科学、时间序列等。

<a id="classroom-representation"></a>

**Why a data row is a point, and why coordinates cannot be shuffled arbitrarily**

**一行数据为什么是一个点，坐标为什么不能随意混排**

Measuring 50 variables for each of 20 people produces a table with **20 rows and 50 columns**. Each row represents a person and each column an attribute, so there are 20 samples, each lying in a 50-dimensional feature space. Here, dimension means the number of values used to describe one sample, not the number of people in the class or the number of directions in physical space.

对 20 个人各测量 50 个变量，得到一个 **20 行、50 列** 的表。每行代表一个人，每列代表一种属性；于是共有 20 个样本，每个样本位于 50 维特征空间中。这里的“维度”是描述一个样本需要多少个数，不是班级有多少人，也不是物理空间有多少个方向。

We cannot directly draw this 50-dimensional point cloud, but we can still calculate distances, make predictions, or reduce its dimension. Replacing a 50-dimensional representation with five dimensions uses fewer variables to preserve selected aspects of its structure; the task and method determine what to preserve. Compressing several measurements into one score, from average grades to recruitment assessments, always involves choices of weights and objectives. Grades, knowledge, and collaboration need not have the same importance in every task.

我们无法直接画出这个 50 维点云，但仍能计算距离、做预测或降维。把 50 维表示变成 5 维表示，是用较少变量保留某些所关心的结构；保留什么必须由任务和方法决定。从平均成绩到招聘评价，把多项信息压成一个分数，都包含权重和目标选择；考试成绩、知识、协作等维度不一定在不同任务中同样重要。

It is also necessary to distinguish the existence of variables from the structure connecting them.

还要区分“变量存在”与“变量之间的结构”。

| Data<br>数据 | Example<br>例子 | Structure to preserve<br>应保留的结构 |
|---|---|---|
| Attribute table<br>属性表 | Income, overdrafts, and other credit-application attributes<br>信贷申请中的收入、透支情况等 | Each column's meaning and units; update interpretation and model inputs when column order changes<br>每列的语义和单位；列顺序变更时要同步修改解释与模型输入 |
| Time series<br>时间序列 | An account balance alternating between positive and negative each month<br>账户余额逐月正负交替 | Time order; moving positives before negatives turns regular cash flows into an apparent recent run of overdrafts<br>时间顺序；把正数全放前面、负数全放后面，会把规律性收支变成“最近连续透支” |
| Image<br>图像 | Pixel grid and RGB channels<br>像素网格及 RGB 通道 | Pixel positions, spatial adjacency, and channel relationships<br>像素位置、空间邻接和通道关系 |
| Relational data<br>关系数据 | Objects and their connections in a network<br>网络中的对象及其连接 | Which objects are connected, and what each connection means<br>哪些对象相连，以及连接的含义 |

Flattening an image into a vector in a fixed, reversible order does not itself lose pixel information: the image can be reconstructed if its dimensions and ordering are known. Problems arise when the positional mapping is lost or the algorithm fails to use spatial adjacency. This is the sense in which shuffling coordinates can destroy an image's structure. Likewise, columns in an ordinary attribute table cannot be arbitrarily exchanged at prediction time without updating the model's interpretation.

图像按固定、可逆的顺序展平为向量，本身不会丢失像素信息；已知宽高和排列规则就能还原。问题在于丢失位置映射，或使用的算法没有利用空间邻接结构。“打乱坐标会破坏图像”应在这个意义上理解。同样，普通属性表也不能在预测时随意交换列而不通知模型。

<details>
<summary>Further detail: how the three pillars interact, and why computation alone is insufficient<br>延伸：三个支柱怎样分工，为什么“能算出来”还不够</summary>

Hardware includes sensors, communications, and human interfaces as well as computers. Software environments support design, calibration, testing, and deployment, with dedicated tools such as MLOps for production and scaling. Algorithms can first be expressed in pseudocode, then implemented in a programming language and deployed. Writing a prediction program and establishing its reliability under stated conditions are different tasks.

硬件不仅是计算机，还包括传感器、通信和人机接口；软件环境分别支持设计、校准、测试和部署，生产运行与规模化又有专门工具，例如 MLOps 工具。算法则可以先用伪代码表达，再用编程语言实现并部署。写出一个预测程序与证明它在某些条件下可靠，是两项不同的工作。

Gaussian models illustrate the role of assumptions. Bell-shaped distributions simplify derivation and calculation, but heavier tails or mixtures of populations require reexamining interpretations and guarantees that depend on the distributional assumptions. This does not mean that every departure from Gaussianity makes all methods fail completely. Distinguish whether an algorithm remains computable, which conclusions require Gaussianity, and how performance changes when assumptions fail.

高斯模型可以说明假设的作用：钟形分布便于推导和计算，但数据若有更重的尾部或由多个不同群体混合而成，原先依赖分布假设的解释和保证就需要重查。这不表示任何偏离高斯的数据都会让所有方法完全失效；应区分算法能否计算、哪些结论依赖高斯性，以及偏离假设后的实际表现。

Exam grades provide an intuitive bell-shaped example, but bounded grades cannot strictly follow an unbounded Gaussian distribution. Transcript figures such as the brain handling 16 variables or five or six variables are oral illustrations of the difficulty of high-dimensional visualization, not quantitative conclusions about cognitive capacity.

考试成绩被用作钟形分布的直觉例子，但有界成绩不严格服从取值无界的高斯分布。转录中关于人脑可处理“16 个变量”或“5、6 个变量”的数字，也只是帮助说明高维可视化困难的口头表述，不作为认知能力的定量结论。

</details>

*来源：[转录 1](../01_part1.md) 第 269–491 行。*

<a id="problem-types"></a>

<a id="section-04"></a>

## Types of Machine Learning problems

**机器学习问题的类型**

![image](<../Images/01_intro/image_001.jpg>)

<a id="classroom-task-types"></a>

**Identify the problem type from the output and available labels**

**先看输出和已有标签，再确定问题类型**

In the banking example, a customer's information is the input, and the historical outcome of whether they repaid as agreed is the label. Supervised learning uses these input–label pairs to learn how to predict outcomes for new customers. A label is not automatically part of the input: it must be defined, obtained, and checked for consistency with the task.

在银行例子里，一个客户的资料是输入，历史上“是否按约还款”是标签。监督学习使用这样的输入—标签对，学习预测新客户的结果。标签不是自动包含在输入里的：必须定义它、获取它，并确认它与要解决的任务一致。

Without such labels, one can still study customer similarity, groups, or low-dimensional representations. However, an unsupervised group cannot immediately be interpreted as good or bad customers, nor can the same repayment predictor be assumed to be calibrated without outcome labels. The end of the first transcript discusses rules, experience, and prior judgments and begins a Capital One example. The passage then stops; the available files do not provide its continuation, so its conclusion cannot be reconstructed.

没有这类标签时，仍可研究客户的相似性、分组或低维表示，但不能直接把一个无监督分组解释为“好客户／坏客户”，也不能假定没有结果标签就能校准同样的还款预测。第一份转录结尾涉及规则、经验和先入判断，并开始举 Capital One 的例子；该片段随后中断，现有文件没有提供完整后续，不能补写其结论。

Classification outputs categories, regression outputs continuous values, and scoring outputs values used to rank or select items. Their primary distinction lies in the task, not in whether they use the same data file. The later [credit-ranking example](02_algorithms_and_pipeline.md#classroom-pipeline) shows how identical labels can still lead to different optimization objectives.

分类输出类别，回归输出连续数值，评分输出用于排列或筛选的分数。它们的差别首先在于任务，不在于是否使用同一个数据文件。后面的[信贷排序例子](02_algorithms_and_pipeline.md#classroom-pipeline)会说明：标签相同，实际要优化的目标仍可能不同。

*来源：[转录 1](../01_part1.md) 第 492–521 行；[转录 3](../01_part3.md) 第 143–173 行；[转录 3](../01_part3.md) 第 197–200 行。*

<a id="reading-figure-terms"></a>

**Reading the diagram: semi-supervised learning and association analysis**

**读图：半监督学习与关联分析**

**Semi-supervised learning** in the diagram uses a small amount of labeled data together with more unlabeled data. For example, only some images may carry pedestrian/no-pedestrian labels; the remaining images can still reveal the input distribution and similarity structure, helping to construct a classifier. Labeled samples connect that structure to the target classes. Whether unlabeled data help depends on whether the structure is relevant to the classification task.

图中的 **Semi-supervised Learning（半监督学习）** 使用少量带标签数据和较多未标注数据。例如，只有一部分图像已经标明“有行人／无行人”，其余图像仍可提供输入分布和相似结构的信息，帮助构造分类器。带标签样本把这种结构与目标类别联系起来；能否从未标注数据中获益，取决于这些结构是否与分类任务相关。

**Association analysis** looks for items or events that frequently occur together. Market basket analysis in the diagram treats a purchase as a set of products and studies which products are often bought together. Buying bread and milk together, for example, can suggest a candidate association rule, whose relevance is then assessed using purchase frequencies. Association concerns co-occurrence between items, whereas clustering groups similar samples. Both can study data structure without a prespecified target label.

**Association（关联分析）** 寻找经常共同出现的项目或事件。图中的 Market Basket Analysis 就是购物篮分析：把一次购买看作一组商品，研究哪些商品经常同时出现。例如，面包和牛奶的共同购买可以形成一条候选关联规则，再用购买频率判断这条规则是否值得关注。这里关注的是项目之间的共现关系；聚类则把相似的样本分成组。两者都能在没有预先指定目标标签的情况下研究数据结构。

<a id="symbolic-ai"></a>

<a id="section-05"></a>

## Symbolic AI vs. Machine Learning

**符号人工智能与机器学习**

The Traditional Programming Paradigm

传统编程范式

![image](<../Images/01_intro/image_002.jpg>)

Machine Learning

机器学习

![image](<../Images/01_intro/image_003.jpg>)

<a id="classroom-rules"></a>

**From human-written rules to rules estimated from data**

**从“人写规则”到“用数据估计规则”**

In symbolic methods, people explicitly specify processing rules and then supply new inputs to the program. Online-shopping fraud rules, for example, might check whether the transaction location, amount, and previous transactions on the same card match a predefined suspicious pattern. This illustrates the mechanism of a rule-based system; it does not establish the current architecture of any particular payment platform.

符号式方法由人显式规定处理规则，再把新输入交给程序；例如，网购反欺诈规则可以检查交易地点、金额及同一张卡前几笔操作是否符合预设的异常模式。这里用的是规则系统这一机制，不据此判断某家支付平台当前使用什么架构。

In learning-based methods, historical inputs and labels are supplied first, training produces a prediction rule, and that rule is then applied to new customers or images. Saying that the computer wrote the program here means that data produced a decision function; it need not mean that new source code was generated. People still choose the task, available inputs, candidate function types, and evaluation criteria.

学习式方法则先提供历史输入和标签，通过训练得到预测规则，再对新客户或新图像使用这个规则。这里所谓“电脑写出了程序”，指的是数据驱动地产生决策函数，不一定指生成一份新的源代码。人仍然决定任务、可用输入、候选函数类型和评价标准。

The two approaches can coexist in one system. Learned rules can sometimes be difficult to interpret and may make unreliable predictions far from the training data. Learning a pattern does not establish knowledge that is correct in every new situation. Interpretability depends on the particular model; learning methods should not all be regarded as uninterpretable.

两类方式可以在一个系统中结合。机器学习规则有时难以解释，并且在远离训练数据的输入上可能给出不可靠预测；学习到了规律，不等于获得了对所有新情境都正确的知识。可解释程度取决于具体模型，不能把所有学习方法都一概视为无法解释。

<details>
<summary>旁例：对话系统、黑箱与责任</summary>

固定应答、分支和模板也能制造“正在对话”的感觉，早期模拟心理咨询的规则式程序就是转录中的一个例子；客服、Siri 也出现在相关问答中。转录在 1964、1966 年间口头游移，还把早期程序称作“大型语言模型”；这里保留其历史类比，但早期规则式对话程序不能直接等同于现代 LLM。

转录中关于复杂产品包含符号规则层的猜测，以及对黑箱解释能力的判断，都不能替代具体产品的证据。这里未据此断言某个闭源产品的内部构造，更不能由“产品细节不公开”推出“机器学习的运作原理完全不可知”。

以汽车进入社会空间为类比：使用者、部署者、制造者等都可能涉及故障和责任问题，规则需要处理这些关系。录课时关于各地立法进展的评论保留在原转录中，不作为现行法规说明。外推风险、解释困难和责任分配是三个相关但不同的问题。

</details>

*来源：[转录 2](../01_part2.md) 第 1–67 行。*

<a id="learning-task"></a>

<a id="section-06"></a>

## The goal of machine learning

**机器学习的目标**

### Finding a function

**寻找一个函数**


- Example : Pedestrian detection from video cameras

  例子：通过摄像机视频检测行人。

![image](<../Images/01_intro/image_004.jpg>)


- What is the search space for such a function ?

  这样的函数应当在哪个空间中搜索？

<a id="classroom-function"></a>

**One image, one label, and one decision function**

**一张图像、一个标签与一个决策函数**

Video consists of successive images. Start by reducing autonomous driving to one subtask: take an image and output pedestrian present or absent. Traffic lights, other vehicles, and bicycles are additional targets that a more complete system must handle. Solving this binary classification subtask does not amount to solving autonomous driving.

视频由连续图像组成。先把自动驾驶场景缩小为一个子任务：输入一张图像，输出“有行人／无行人”。交通灯、其他车辆、自行车等是更完整系统需要处理的其他目标，不能因为解决了这个二分类子任务，就认为已经解决自动驾驶。

An RGB image contains many color values. For example, an image with only $2\times2$ pixels and three channels per pixel can be represented as $x\in\mathbb R^{12}$. A whole image is one point in feature space, and its label $y\in\{0,1\}$ assigns a class to that point. Red and black points in the diagram indicate sample labels, not pixel colors in the original photograph; the two coordinate axes in the schematic do not represent the photograph's width and height either.

一张 RGB 图像含有许多个颜色数值。例如，若图像只有 $2\times2$ 个像素、每个像素 3 个通道，那么它可以表示为 $x\in\mathbb R^{12}$。一整张图像是特征空间中的一个点；标签 $y\in\{0,1\}$ 为这个点指定类别。图中的“红点／黑点”表示样本标签，不是原照片里像素的颜色；示意图上的两条坐标轴也不等于照片的宽和高。

Learning aims to obtain a function $h$ that takes a new $x$ and returns the prediction $h(x)$. In a geometric view of binary classification, this divides the input space into two decision regions, separated by a line, a curve, or a higher-dimensional surface. The search space $\mathcal H$ specifies which functions are permitted as answers.

学习要得到函数 $h$：给定新的 $x$，返回预测 $h(x)$。在二分类的几何图像里，这相当于把输入空间分成两个判定区域，边界可能是直线、曲线或更高维的曲面。搜索空间 $\mathcal H$ 则规定允许哪些函数成为答案。

Ask two questions in order: **Which class of functions may we search? How do we compare candidates within that class?** Linear models, neural networks, and random forests provide different representations. Although linear models are restrictive, they make general principles easier to see. A network's architecture also restricts its candidate functions; it cannot simply represent anything whatsoever. A language model's stepwise text generation can also be understood through learned functions, but its output space differs from this binary example.

所以应依次问：**允许找哪一类函数？在这一类里，怎样比较两个候选函数？** 线性模型、神经网络、随机森林等提供不同的表示方式；线性模型虽有限制，却便于看清通用原理。网络也由所选架构限定候选函数，并非“想表达什么都可以”。语言模型逐步生成文本也可用学习函数的形式理解，但它的输出空间与这里的二分类不同。

*来源：[转录 2](../01_part2.md) 第 68–121 行。*

<a id="two-errors"></a>

<a id="section-07"></a>

## The art of machine learning

**机器学习的技巧**

### Solving the "bias-variance" trade-off

**解决“偏差—方差”权衡**


- Distance between solution provided by a learning method and the optimal solution (function) : sum of Approximation error and Estimation error

  学习方法给出的解与最优解（函数）之间的距离：近似误差与估计误差之和。

Hypothesis class H

假设类 H

![image](<../Images/01_intro/image_005.jpg>)


- Learning a function amounts to :

  学习一个函数相当于：

(a) choosing a search space (design process),

(a) 选择一个搜索空间（设计过程）；

(b) estimating the best function in this space (training process).

(b) 估计这个空间中的最佳函数（训练过程）。

<a id="classroom-three-functions"></a>

**Distinguish the three functions before interpreting the two errors**

**先分清三个函数，再读两种误差**

Following the three objects in the diagram is clearer than immediately memorizing the phrase bias–variance.

沿着图中的三个对象读，会比直接记“偏差—方差”更清楚。

| Object<br>对象 | Question answered<br>它回答什么问题 | Dependence on training data<br>对训练数据的依赖 |
|---|---|---|
| $h^*$ | If the true data mechanism were known, what would be best among all allowed decisions?<br>如果知道真实数据规律，在所有允许决策中什么最好？ | A theoretical reference, usually unknown<br>是理论参照，通常未知 |
| $\bar h$ | Within the current class $\mathcal H$, which function has the best true performance?<br>限定在当前函数类 $\mathcal H$ 中，真实表现最好的是什么？ | A theoretical reference when distribution and class are fixed<br>在分布和函数类固定时是理论参照 |
| $\widehat h$ | What was actually learned from this finite training set?<br>这一次用有限训练集实际学到了什么？ | Usually changes with a different training dataset<br>换一批训练数据，通常会改变 |

If only straight lines are allowed but the ideal boundary is curved, even the best line may remain limited with abundant data: this is **approximation error**. Even when that best line is fixed, a finite sample may lead us to choose a different line: this is **estimation error**.

如果只允许直线，而理想边界是弯曲的，那么即使数据很多，最好的直线也可能有局限，这对应**近似误差**。即使最好的直线已经确定，有限样本还可能让我们选到另一条直线，这对应**估计误差**。

More data mainly help distinguish better and worse functions within a given class; enlarging the class provides richer candidate answers. The latter may reduce approximation error while also giving a finite sample more opportunities to favor a function that happens to fit that particular dataset. The design stage chooses representations and constraints, while training estimates parameters from data; these are distinct steps.

增加数据主要帮助我们在给定函数类中辨别好坏；扩大函数类则提供更丰富的候选答案。后者可能降低近似误差，却也给有限样本带来更多选择机会，容易选中“碰巧适合这一批数据”的函数。设计阶段选择表示方式与约束，训练阶段依据数据估计参数；两者不能混成一个步骤。

The diagram compares random estimation error to variance, but it is not literally a computed variance. The exact bias–variance identity appears later in the squared-error setting of [parameter estimation](04_hypotheses_and_bias_variance.md#parametric-estimation). Estimation error is also not the computation time required to search more candidates: it is statistical error due to a finite sample. More data from the same distribution tend to help under suitable conditions, but error need not decrease monotonically each time a sample is added. Nor does enlarging the function class necessarily increase every algorithm's estimation error.

图中把随机的估计误差类比为“方差”，但它不是直接算出的方差，严格的偏差—方差恒等式要到后面[参数估计](04_hypotheses_and_bias_variance.md#parametric-estimation)的平方误差设定中才出现；它也不是“候选多所以搜索更久”的计算耗时，而是有限样本带来的统计误差。更多同分布数据有助于学习，是在适当条件下的趋势，不保证每次加一个样本误差都单调下降；扩大函数类也不保证任一算法的估计误差必然增大。

**Example: interpret the two gaps using three risk values**

**例子：用三个风险数值读懂图中的两段距离**

Suppose that under the same loss, $L(h^*)=0.08$, $L(\bar h)=0.12$, and $L(\widehat h)=0.17$. The excess risk relative to the ideal optimal rule is then $0.17-0.08=0.09$: $0.17-0.12=0.05$ is the estimation gap within the class, and $0.12-0.08=0.04$ is the approximation gap of the current class. These are differences between risk values, not Euclidean distances between three points in the picture.

假设同一损失下，$L(h^*)=0.08$、$L(\bar h)=0.12$、$L(\widehat h)=0.17$。那么相对理想最优规则的额外风险为 $0.17-0.08=0.09$，其中 $0.17-0.12=0.05$ 是类内估计差距，$0.12-0.08=0.04$ 是当前函数类的近似差距。这里比较的是风险数值，不是画面上三点之间的欧氏距离。

It is also possible for $h^*$ to belong to $\mathcal H$, in which case approximation error can be zero. With noise, however, even using $h^*$ need not give zero absolute risk.

$h^*$ 也可能属于 $\mathcal H$，此时近似误差可以为零；有噪声时，即使使用 $h^*$，绝对风险也未必为零。

*来源：[转录 2](../01_part2.md) 第 122–178 行。*

---

[本课目录](../01_intro_zh.md) · [下一篇：算法家族、正则化与处理流程](02_algorithms_and_pipeline.md)
