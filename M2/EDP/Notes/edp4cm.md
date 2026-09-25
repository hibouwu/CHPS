# 性能评估：仿真与测量

[课程入口](../README.md) · [中文笔记 PDF](edp4cm.pdf)

按原笔记顺序整理，保留法文术语；已修复的内容问题在相应小节标为“校注”。教师课件与核对依据见[审校说明](../审校说明.md)。

## 1 概论 (Généralités)

### 1.1 仿真 (Simulation)

#### 1.1.1 目的 (But)

能够在任何条件 (配置) 下观察任何系统的行为, 即使该系统在评估时尚不存在, 代表各种应用背景。

#### 1.1.2 优势 (Intérêts)
- 无需构建真实系统
- 可以进行可控且可重复的测试
- 测试场景无限制
- 其他用户可以重现结果

#### 1.1.3 应用示例 (Exemples d’utilisation)

仿真可以回答如下问题:
- 在给定架构上, 哪种放置算法 (algorithme de placement) 对某个应用更好?
- 哪种缓存策略 (stratégie de cache) 对某个应用更好?
- 与某些共享资源管理策略相关的公平性 (équité) 和吞吐量 (débit) 特性是什么?

#### 1.1.4 仿真与测量对比 (Simulation Vs. Mesure)

测量 (mesure).... 在精确性和真实系统代表性方面很好, 但是....
- 结果中真实的系统故障/过载 (dysfonctionnements/surcharge) 占多大比例?
- 实验及其结果仅限于所分析的平台
- 外推是可能的, 但很难令人信服
- 其他用户很难重现结果

### 1.2 仿真: 定义与分类 (Définition et classification)

#### 1.2.1 定义 (Définition)

通过创建模仿来尝试预测任何系统行为的不同方面。

#### 1.2.2 分类 (Classification)

存在不同类型的仿真:
- 仿真 (Emulation)
- 静态仿真 (Simulation statique)
- 离散事件仿真 (Simulation à événements discrets)

### 1.3 仿真和静态仿真 (Emulation et simulation statique)

#### 1.3.1 仿真 (Emulation)

通过在另一个系统上运行的软件来模仿系统的物理行为, 使其表现得像被模仿的系统。

注意: 仿真产生相当精确的结果, 但作为代价会产生很大的开销 (overhead)。

#### 1.3.2 静态仿真 (Simulation statique)

本课以蒙特卡洛方法为例，讨论不显式描述系统随时间演化的静态仿真。可以按计算预算或估计精度停止；不要求达到动态系统的平衡状态。

## 2 离散事件仿真 (Simulation à événements discrets)

### 2.1 离散事件仿真的定义

通过事件 (événements)、与之相关的转换 (transitions) 以及每当这些事件发生并执行相关转换时要执行的特定函数来表示系统。因此, 这是对功能模式的模仿, 根据时间和外部事件或仿真生成的事件进行状态改变。

### 2.2 分布式仿真 (Simulation distribuée)

主要与仿真执行的方式有关: 分布式的, 利用不同站点的资源, 协作和通信, 同时遵守已建立的工作流模式 (schéma Workflow) 和因果关系原则 (principes de causalité)。

### 2.3 仿真示例:CPU 仿真

三种可能的仿真, 抽象级别递减:
- 数学仿真 (Simulation mathématique): 任务和组件 (管道)(pipe) 的宏观流动, 采用粗粒度数学仿真
- 离散事件仿真 (Simulation à événements discrets): 周期级仿真 (微观级别), 以提高精度
- 仿真 (Emulation): 通过另一个 CPU 进行虚拟化, 即构建虚拟机

### 2.4 仿真示例: 通信网络仿真

三种可能的仿真, 抽象级别递减:
- 数学仿真: 网络任务和组件 (管道) 的宏观流动, 采用粗粒度数学仿真
- 离散事件仿真: 数据包级别的仿真, 通过网络不同组件进行微观跟踪
- 仿真: 实际流量通过网络的仿真

### 2.5 术语 (Terminologie)

#### 2.5.1 基本术语
- 状态变量 (Variables d’état): 定义系统状态的变量, 保存的值允许停止的仿真稍后重新启动 (队列大小、任务消耗进度等)
- 事件 (Événement): 系统状态的改变 (作业到达或完成、组件故障等)
- 连续时间 (Temps continu) 与离散时间 (temps discret): 指示系统状态是否始终定义
- 连续状态 (État continu) 与离散状态 (état discret): 指示系统变量是连续的 (时间) 还是离散的(出现次数、大小)

### 2.6 离散事件仿真器的结构 (Structure)

离散事件仿真器必须包含以下模块:

1. 事件调度器 (ordonnanceur d’événements)

2. 全局时钟和时间更新方法 (horloge globale et méthode pour la mise à jour du temps)

3. 事件处理过程 (procédures de traitement des événements)

4. 事件生成机制 (mécanismes de génération d’événements)

5. 数据记录/过滤过程 (procédures d’enregistrement/filtrage des données)

#### 2.6.1 事件调度器 (L’ordonnanceur des événements)

调度器构成离散事件仿真器的核心, 其功能是:
- 按全局时间顺序维护事件列表 (未处理的)
- 通过从列表中删除适当的事件并将其传送到与之关联的处理过程来处理该事件
- 在尊重列表时间顺序的前提下插入新事件, 并确保调度或删除事件的其他任务
- 确保与全局时钟的协调

#### 2.6.2 全局时钟 (L’horloge globale)

仿真的时间参考, 由调度器根据两种方法更新:

##### 1. 固定步长递增 (Incrémentation par pas fixe)

调度器以固定步长进行递增, 然后检查列表中的事件并启动就绪的事件。执行结束后, 调度器重新递增时钟。

##### 2. 事件驱动递增 (Incrémentation événementielle)

时钟以非均匀方式变化, 并取列表头部事件的日期值。这是最常用的方法。

#### 2.6.3 事件处理 (Traitement des événements)
- 每种类型的事件都与一个处理过程相关联, 该过程模拟当该事件发生时系统的行为
- 每个处理过程可以改变系统状态并生成其他事件, 这些事件将添加到调度器维护的列表中
- 实现的处理取决于被仿真系统的性质

#### 2.6.4 事件生成 (Génération des événements)

事件生成器根据所使用的生成技术进行分类。两个主要类别:

1. 面向轨迹的类 (Classe orientée trace): 在真实系统上观察到的事件序列。具有代表性但体积非常大, 单一验证点, 收集引入偏差

2. 面向概率分布的类 (Classe orientée loi de probabilité): 形式相似但由仿真器根据概率分布生成 (在开始时或伴随仿真过程)

#### 2.6.5 数据记录 (Enregistrement des données)

维护状态变量, 即事件计数器和时间测量变量, 以进行统计并总结结果。

结构 (Structures):
- 有序列表或双向链表 (Listes ordonnées ou doublement chaînées)
- 树 (Arbres)

这些是最常用的结构, 用于加速操作 (插入、查询、修改), 即使内存访问不均匀。

#### 2.6.6 验证 (Validation)

验证确定功能模型的精度水平, 回答以下问题:
- 模型是否捕获了系统的基本功能?
- 假设是否合理?
- 输入数据是否代表真实情况?
- 获得的结果是否合理?
- 这些结果是否可以解释?

#### 2.6.7 关于仿真器构建的注意事项 (Remarques)

关于仿真器的构建:
- 遵循良好实践: 结构化编程、模块化设计、文档、错误检查等
- 逐步执行以验证通过被仿真系统的所有状态
- 验证仿真器的一致性和稳定性
- 强调特殊情况 (边界条件)(corner conditions) 的验证

### 2.7 流行的仿真器 (Simulateurs populaires)

#### 2.7.1 微处理器仿真器 (Simulateur de Microprocesseur)

众多周期级标准仿真器:

http://pages.cs.wisc.edu/~arch/www/tools.html

#### 2.7.2 SimGrid

用于分布式和异构环境 (从工作站网络到计算网格) 的工具, 由 INRIA 开发:http://simgrid.gforge.inria.fr/

#### 2.7.3 存储系统仿真器 (Simulateur de système de stockage)

先驱, 由并行数据实验室 (CMU) 开发/维护:

http://www.pdl.cmu.edu/DiskSim/

我们的:OGSSim. Li-PaRAD,UVSQ / CEA-DAM

## 3 蒙特卡洛仿真 (Simulation par Monte Carlo)

### 3.1 历史 (Historique)

N. Metropolis 和 S. Ulam [1947-1949], 使用随机过程来计算数值。因此暗指在蒙特卡洛 (Monte Carlo)进行的机会游戏。

### 3.2 定义 (Définition)

使用随机变量集作为输入, 迭代评估确定性模型的方法。

确定性模型 (modèle déterministe) 在相同条件下、使用相同输入重新计算多次时, 会给出相同的结果。

### 3.3 应用 (Applications)

蒙特卡洛方法的应用领域包括: 多维积分计算 (表面、体积)、金融风险评估、银行和保险部门的盈利能力或偿付能力、分子动力学或人口运动研究等。

注意 (Remarque): 蒙特卡洛方法需要非常大量的评估, 并行计算促进了这项任务。

### 3.4 蒙特卡洛的步骤

执行蒙特卡洛仿真遵循的不同步骤:

1. 为参数 $( X _{1} , X _{2} , . . . , X _{k} )$ 创建模型

2. 生成一组随机值 $( X _{i 1} , X _{i 2} , . . . , X _{i k} )$

3. 评估模型并将结果存储在 $Y_i$ 中

4. 对 i = 1..n(n 非常大, 以使用大数定律) 重复步骤 2 和 3

5. 使用直方图、平均值和方差、置信区间等分析结果

### 3.5 蒙特卡洛示例：计算 $\pi$

在单位正方形 $[0,1]^2$ 中独立均匀抽取点，统计落在单位圆第一象限四分之一圆内的比例：

1. 单位圆总面积为 $\pi$，正方形内的四分之一圆面积为 $\pi/4$。
2. 对每次抽样，独立生成 $x_{i1},x_{i2}\sim U(0,1)$。
3. 若 $x_{i1}^2+x_{i2}^2<1$，将圆内点数 $N_B$ 加 1；无论是否命中，总抽样数都加 1。
4. 抽样 $N$ 次后，使用：

$$
\frac{\pi}{4}\approx\frac{N_B}{N},\qquad \widehat\pi=4\frac{N_B}{N}.
$$

> 校注：提取稿丢失了两处 $\pi/4$ 的分母，并将“圆”识别成数学符号；原中文 PDF 第 5 页能核对分母。这里也明确了 $N_B$ 是命中四分之一圆的点数。

## 4 测量 (Mesure)

### 4.1 测量: 引言 (Introduction)

#### 4.1.1 测量什么?(Quoi mesurer?)

事件出现次数、两个事件之间的持续时间、包含信息的大小等。

#### 4.1.2 定义 (Définition)

测量用于通过以下方式跟踪系统的运行:

1. 观察和收集 (L’observation et la collecte): 进行测量并收集由此产生的信息

2. 分析 (L’analyse): 使用统计技术处理收集的数据

3. 呈现 (La présentation): 以各种适当的形式显示结果

### 4.2 测量: 术语 (Terminologie)

#### 4.2.1 常用术语
- 事件 (Événement): 系统状态的任何改变 (例如请求/数据包到达、内存访问等)
- 轨迹 (Trace): 事件的列表或日志
- 开销 (Surcharge, overhead): 指示系统额外消耗的测量
- 分辨率 (Résolution): 观察的详细程度
- 输入大小 (Taille en entrée): 编码事件的位数
- 可移植性 (Portabilité): 为实现测量工具需要进行的修改量

### 4.3 观察/收集阶段 (Phase d’observation/collecte)

#### 4.3.1 观察机制 (Mécanismes d’observation)

1. 隐式监视 (“Espionnage implicite”, Implicit spying):

在不干扰系统运行的情况下观察系统。对性能没有影响, 但使用过滤器保留有用信息。

2. 显式插桩 (Instrumentation explicite):

使用硬件计数器等合并跟踪器、探针。

#### 4.3.2 观察/收集类别
- 在线 (On-line): 在监控期间分析结果
- 批处理 (batch): 收集数据但分析推迟

#### 4.3.3 收集策略 (Stratégies de collecte)
- 事件驱动 (Event-driven): 每次事件出现时记录信息
- 轨迹 (Trace): 还记录系统状态。因此在时间和空间上产生开销
- 采样 (Échantillonnage): 定期记录信息, 因此重新调整开销
- 间接测量 (Mesure indirecte): 当要测量的度量不能直接测量时使用。确定另一个可测量的度量并推导/导出感兴趣的度量

### 4.4 简单的收集工具 (Outils simples de collecte)

示例:

除了测量硬件和专用软件外, 还有一些简单但有效的工具, 经常用于测量。

我们列举:

`time`、`gettimeofday`（以微秒表示时间）、`top`、`gprof` 等；表示单位不等于实际时钟分辨率。

### 4.5 分析阶段 (Phase d’analyse)

任何评估的目的, 取决于上下文和度量。对于测量来说更重要, 因为收集的数据量大、细节丰富且有噪声。

#### 4.5.1 方差分析 (ANalysis Of VAriance, ANOVA)

在系统上进行测量时, 收集的数据呈现出可能很大的偏差, 这些偏差可能仅与测量的重复有关, 或者表示真实的测量误差。

ANOVA 将总变异分解为方案间效应和组内残差；残差可能包含未解释的随机波动，不应全归因于测量仪器出错。

#### 4.5.2 ANOVA - 计算 (Calcul)

考虑为 k 次执行 (备选方案)(alternatives) 中的每一次收集的 n 个测量样本, 集合组成第 j 次执行的第 i 次测量的 $y _{i j}$

计算平均值:

按方案计算与总体计算的均值分别为：

$$
\bar y_j=\frac1n\sum_{i=1}^n y_{ij},\qquad
\bar y=\frac1{kn}\sum_{j=1}^k\sum_{i=1}^n y_{ij}.
$$

测量可以重写为 $y _{i j} = \bar{y} _{j} + e _{i j}$ , 其中 $e _{i j}$ 是测量误差。

按备选方案的测量平均值可以重写为:

$$
\bar{y} _{j} = \bar{y} + \alpha_{j}
$$

其中 $\alpha_{j}$ 是执行效应 (effet d’execution), 且 $\textstyle \sum_{j = 1} ^{k} \alpha_{j} = 0$

#### 4.5.3 ANOVA - 应用 (Application)

与执行相关的变化由备选方案平方和 (Sum of the Squares of Alternatives, SSA) 表示:

$$
\mathrm{SSA} = n \sum_{j = 1} ^{k} (\bar{y} _{j} - \bar{y}) ^{2}
$$

与测量误差相关的变化由误差平方和 (Sum of Squares of Errors, SSE) 表示:

$$
\mathrm{SSE} = \sum_{j = 1} ^{k} \sum_{i = 1} ^{n} (y _{i j} - \bar{y} _{j}) ^{2}
$$

#### 4.5.4 ANOVA 和 F 检验 (F-test)

单因素 ANOVA 检验 $k$ 个备选方案的总体均值是否相同。经典模型假设误差独立、近似正态且各组具有相同方差。

$$
S_a^2=\frac{\mathrm{SSA}}{k-1},\qquad
S_c^2=\frac{\mathrm{SSE}}{k(n-1)},\qquad
F_{\mathrm{计算}}=\frac{S_a^2}{S_c^2}.
$$

当

$$
F_{\mathrm{计算}}>F_{1-\alpha;\,k-1,\,k(n-1)}
$$

时，在显著性水平 $\alpha$ 下拒绝“各组均值相同”的原假设。

> 校注：原中文 PDF 第 8 页与教师 PDF 第 34 页均将不等号方向写反；Markdown 还把“计算”识别成了乱码。此处同时修正。未拒绝原假设不等于证明各组均值相同。

### 4.6 呈现阶段 (Phase de présentation)

#### 4.6.1 呈现选择的参数

与系统相关的选择, 但要考虑三个参数:

1. 呈现频率 (在线)

2. 层次化表示 (résentation hiérarchique)

3. 重要点: 阈值、异常事件等

#### 4.6.2 简单、流行和有代表性的工具

一组简单的统计技术: 平均值、方差和标准差、分位数等 (参见工作负载课程), 以及置信区间。

## 5 测量质量 (Qualité de mesure)

### 5.1 定义 (Définition)

测量中的误差或噪声必须量化, 以通过以下方式确定这些测量的质量:

1. 准确性 (Justesse, Accuracy): 指示测量值与标准值的接近程度

2. 精密度 (Précision)：重复测量之间的一致程度；此处“逆”指相反概念，不是直接取数学倒数

3. 分辨率 (Résolution): 是可检测和” 可显示” 的最小变化

### 5.2 误差来源 (Sources d’erreurs)

测量仪器、用户之间的时间共享、实时事件 (例如网络接口中断)、时钟同步、不确定性事件 (缓存未命中、系统异常、页面错误等)

### 5.3 量化 (Quantification)

1. 准确性: 难以量化

2. 精密度可通过重复测量的离散程度评估，均值估计的不确定性可用置信区间描述。
3. 分辨率是仪器可辨识的最小变化，不能直接用均值置信区间替代。

### 5.4 平均值的置信区间：大样本近似

当样本独立、方差有限且样本均值的正态近似合理时：

$$
\begin{aligned}
c_1&=\bar X-z_{1-\alpha/2}\frac{s}{\sqrt n},\\
c_2&=\bar X+z_{1-\alpha/2}\frac{s}{\sqrt n}.
\end{aligned}
$$

$\alpha$ 是显著性水平，$1-\alpha$ 是置信水平。例如 95% 置信水平对应 $\alpha=0.05$。

> 校注：原 PDF 将 $\alpha$ 写为 0.9 或 0.95，混淆了两个概念；$n\ge30$ 只是经验提示，并不能保证任意数据都满足正态近似。

### 5.5 平均值的置信区间：Student 区间

对于来自正态总体的独立样本，当总体方差未知时：

$$
\begin{aligned}
c_1&=\bar X-t_{1-\alpha/2;n-1}\frac{s}{\sqrt n},\\
c_2&=\bar X+t_{1-\alpha/2;n-1}\frac{s}{\sqrt n}.
\end{aligned}
$$

自由度为 $n-1$。该式不局限于 $n<30$；样本变大时，Student 临界值接近标准正态临界值。

### 5.6 误差量化示例 (Exemple)

文件写入时间的 8 次观测为：

| 测量编号 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 写入时间 $X_i$（s） | 8.0 | 7.0 | 5.0 | 9.0 | 9.5 | 11.3 | 5.2 | 8.5 |

$$
\bar X=7.9375\ \mathrm{s},\qquad
s=\sqrt{\frac{\sum_{i=1}^{8}(X_i-\bar X)^2}{7}}\approx2.14472\ \mathrm{s}.
$$

对 90% 置信水平，$\alpha=0.1$、$t_{0.95;7}\approx1.89458$，得到：

$$
[c_1,c_2]\approx[6.50089,\ 9.37411]\ \mathrm{s}.
$$

> 校注：原稿在代入过程中将均值从 7.94 写为 7.95，现按原始数据重算。90% 指反复使用该区间构造方法的长期覆盖率，不是固定总体均值落入已算区间的概率。

### 5.7 所需测量次数（原题：Nombre d’alternatives）

若目标是均值置信区间的绝对半宽不超过 $\delta$，可用先导样本标准差 $s_0$ 进行正态近似规划：

$$
n\ge\left(\frac{z_{1-\alpha/2}s_0}{\delta}\right)^2.
$$

若采用相对半宽 $e_{\mathrm{rel}}$，令 $\delta=e_{\mathrm{rel}}|\bar X_0|$，于是：

$$
n\ge\left(\frac{z_{1-\alpha/2}s_0}{e_{\mathrm{rel}}|\bar X_0|}\right)^2.
$$

使用上例的课件舍入值 $s_0=2.14$、$\bar X_0=7.94$，以 90% 置信水平和相对半宽 3.5% 为目标：

$$
n\ge\left(\frac{1.64485\times2.14}{0.035\times7.94}\right)^2
\approx160.44.
$$

向上取整得到初步规划值 **161 次**。

> 校注：原稿写出的 $(2.14\times1.895/(0.07\times7.94))^2$ 约等于 53.24，不能得到 212.95。将分母中的全宽 0.07 改为半宽 0.035，并固定使用先导样本的 $t_{0.95;7}\approx1.895$，才得到约 212.95，即 **213 次**。这与采用正态临界值所得的 161 次是不同的规划方法。先导样本只有 8 次，标准差仍有估计误差，可迭代采用新自由度的 Student 临界值；不能把规划值当作精度保证。

## 6 测量场景的设计 (Conception d’un scénario de mesure)

### 6.1 目的 (But)
- 在最大化收集信息的同时最小化实验数量
- 隔离每个输入因子 (facteur) 的影响
- 确定因子之间相互作用的影响
- 量化结果中的误差部分

### 6.2 实验设计: 定义 (Plan d’expérience : définition)

实验之间因子数量和因子水平数量 (可能值)(niveaux, valeurs possibles) 的分布。

### 6.3 实验设计: 分类 (Plan d’expérience : classification)

1. 简单设计 (Plan simple): 从初始配置出发, 改变一个因子 (局部优化)。不分析交互作用。

2. 完全因子设计 (Plan factoriel complet): 考虑所有配置 (组合)。不可行, 因为数量非常大。

3. 部分因子设计 (Plan fractionnaire): 组合的子集。可行, 但如何选择组合?

### 6.4 实验设计: 示例 (Plan d’expérience : Exemple)

4. 个因子 {A, B, C, D}, 每个因子 3 个水平

完全因子设计给出 81 种组合。

下表是 4 因子、每因子 3 水平的 $L_9(3^4)$ 正交表。

> 校注：原稿称其为“星形设计”，与表格结构不符。每两列的 9 种水平组合各出现一次；9 次试验不能独立估计所有交互作用。

| 实验 (Expérience) | 因子 1(Fact1) | 因子 2(Fact2) | 因子 3(Fact3) | 因子 4(Fact4) |
| --- | --- | --- | --- | --- |
| 1 | A1 | B1 | C1 | D1 |
| 2 | A1 | B2 | C2 | D2 |
| 3 | A1 | B3 | C3 | D3 |
| 4 | A2 | B1 | C2 | D3 |
| 5 | A2 | B2 | C3 | D1 |
| 6 | A2 | B3 | C1 | D2 |
| 7 | A3 | B1 | C3 | D2 |
| 8 | A3 | B2 | C1 | D3 |
| 9 | A3 | B3 | C2 | D1 |

## 7 总结

本课程涵盖了性能评估中的仿真和测量两个重要方法:

### 7.1 仿真的关键要点
- 仿真允许在不需要真实系统的情况下评估系统性能
- 离散事件仿真 (Simulation à événements discrets) 是最常用的方法, 通过事件、状态和转换来模拟系统行为
- 蒙特卡洛方法 (Méthode Monte Carlo) 用于使用随机变量迭代评估确定性模型
- 仿真器必须包含: 事件调度器、全局时钟、事件处理过程、事件生成机制和数据记录机制

### 7.2 测量的关键要点
- 测量涉及观察/收集、分析和呈现三个阶段
- 测量质量通过准确性 (Justesse)、精度 (Précision) 和分辨率 (Résolution) 来评估
- 统计方法如 ANOVA 和置信区间用于量化测量中的误差
- 实验设计 (Plan d’expérience) 帮助最小化实验数量同时最大化收集的信息

### 7.3 重要工具和资源
- 微处理器仿真器: http://pages.cs.wisc.edu/~arch/www/tools.html
- SimGrid: http://simgrid.gforge.inria.fr/
- DiskSim: http://www.pdl.cmu.edu/DiskSim/
- OGSSim: https://github.com/liparad-storage/ogssim
- 简单测量工具: time, gettimeofday, top, gprof 等

## 附录：重要公式汇总

### 置信区间

在正文说明的假设下，均值区间为：

$$
\bar X\pm z_{1-\alpha/2}\frac{s}{\sqrt n}
\quad\text{（大样本正态近似）},
$$

$$
\bar X\pm t_{1-\alpha/2;n-1}\frac{s}{\sqrt n}
\quad\text{（正态总体、方差未知）}.
$$

### ANOVA

$$
\bar y_j=\frac1n\sum_{i=1}^n y_{ij},\qquad
\bar y=\frac1{kn}\sum_{j=1}^k\sum_{i=1}^n y_{ij}.
$$

$$
\mathrm{SSA}=n\sum_{j=1}^k(\bar y_j-\bar y)^2,\qquad
\mathrm{SSE}=\sum_{j=1}^k\sum_{i=1}^n(y_{ij}-\bar y_j)^2.
$$

$$
F=\frac{\mathrm{SSA}/(k-1)}{\mathrm{SSE}/[k(n-1)]}.
$$

当 $F>F_{1-\alpha;k-1,k(n-1)}$ 时拒绝各组均值相等的原假设。

### 所需测量次数

$$
n\ge\left(\frac{z_{1-\alpha/2}s_0}{e_{\mathrm{rel}}|\bar X_0|}\right)^2.
$$

$e_{\mathrm{rel}}$ 为相对半宽；计算结果向上取整，且依赖先导样本和统计模型的适用性。
