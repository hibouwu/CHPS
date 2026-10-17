# 4. 学习对象与偏差—方差分解

[本课目录](../01_intro_zh.md) · [上一篇：信息量、样本与 PAC 学习](03_information_and_pac.md) · [下一篇：线性模型：从拟合到预测误差](05_linear_models.md)

<a id="section-16"></a>

## Supervised Machine Learning The bias-variance decomposition in Machine Learning

**监督机器学习：机器学习中的偏差—方差分解**

<a id="hypothesis-space"></a>

### General setup Notations

**一般设定与记号**


- Goal of learning : an optimal decision function $h ^ { * } : \mathcal { X } \to \mathcal { Y }$ $\mathcal { X }$ : domain set, Y : label set

  学习目标：最优决策函数 $h ^ { * } : \mathcal { X } \to \mathcal { Y }$。$\mathcal { X }$ 是定义域集合，Y 是标签集合。

- Input of learning :

  学习的输入：

- Training data : a set of labeled data

  训练数据：一组带标签的数据

$$
D _ {n} = \{(X _ {1}, Y _ {1}), \dots , (X _ {n}, Y _ {n}) \}
$$

of size n, where the $( X , Y ) ^ { \prime }$ s are in $\mathcal { X } \times \mathcal { V }$

其大小为 n，其中各 $( X , Y ) ^ { \prime }$ 属于 $\mathcal { X } \times \mathcal { V }$。


- Hypothesis space : a collection $\mathcal { H }$ of candidate decision functions $h : \mathcal { X }  \mathcal { Y }$

  假设空间：候选决策函数 $h : \mathcal { X }  \mathcal { Y }$ 的集合 $\mathcal { H }$。

- Output of learning : an empirical decision function $\widehat { h }$ in the hypothesis space $\mathcal { H }$ estimated from training data $D _ { n }$

  学习的输出：利用训练数据 $D _ { n }$ 估计得到、位于假设空间 $\mathcal { H }$ 中的经验决策函数 $\widehat { h }$。

- Reference in $\mathcal { H }$ : the best decision function $\bar { h }$ in the class (the more data, the closer $\widehat { h }$ to $\hat { h } )$

  $\mathcal { H }$ 中的参照：该类中的最佳决策函数 $\bar { h }$（数据越多，$\widehat { h }$ 越接近 $\hat { h } )$）。

> **Note:** The original phrase says $\widehat h$ approaches $\hat h$, naming the same object twice. In context it should say approaches $\bar h$. This is also idealized: whether the algorithm's output approaches $\bar h$ as n grows depends on consistency conditions and whether optimization actually reaches the empirical-risk minimum.

> **译注：** 原句“$\widehat h$ 越接近 $\hat h$”把同一对象写了两次，按上下文应为“越接近 $\bar h$”。这也是理想化说法：学习算法的输出是否随 n 增大趋近 $\bar h$，还取决于一致性条件和优化是否真正达到经验风险最小。

<a id="classroom-notation"></a>

**What the hat, bar, and star each signify**

**符号中的“帽子”“横线”和“星号”各自提醒什么**

$D_n$ is the sample set used in this training run; $\mathcal H$ is the set of candidate functions; and $h$ is one candidate. The same kind of object can also be denoted f; changing the letter does not change the problem. Classification labels may be 0 or 1 and regression labels real-valued, while the input $x_i$ can still be a high-dimensional vector.

$D_n$ 是这次用于训练的样本集合；$\mathcal H$ 是候选函数的集合；$h$ 是集合中的一个候选。也可以用 f 表示同类对象，字母变化不代表问题变了。分类标签可以是 0／1，回归标签可以是实数，而输入 $x_i$ 仍可以是高维向量。

The meanings of $h^*$, $\bar h$, and $\widehat h$ are given in the earlier [comparison table](01_data_and_learning.md#classroom-three-functions). In this notation, the bar in $\bar h$ identifies the true-risk optimum within the class; it does **not** mean averaging $\widehat h$.

$h^*$、$\bar h$、$\widehat h$ 的含义见前面的[对照表](01_data_and_learning.md#classroom-three-functions)。记号上要注意：$\bar h$ 的横线在这里表示类内真实风险最优，**不是**对 $\widehat h$ 取平均。

*来源：[转录 3](../01_part3.md) 第 392–407 行。*

<a id="risk-decomposition"></a>

### The key trade-off in Machine Learning

**机器学习中的关键权衡**


- Denote by $L ( h )$ the error measure for any decision function h

  对任意决策函数 h，用 $L ( h )$ 表示其误差度量。

- We have : $L ( \bar { h } ) = \operatorname* { i n f } _ { \mathcal { H } } L$ , and $L ( h ^ { * } ) = \mathsf { i n f } L$

  有 $L ( \bar { h } ) = \operatorname* { i n f } _ { \mathcal { H } } L$，以及 $L ( h ^ { * } ) = \mathsf { i n f } L$。

- Bias-Variance type decomposition of error for any output $\widehat { h }$ :

  对任意输出 $\widehat { h }$，误差具有如下偏差—方差类型的分解：

$$
L (\widehat {h}) - L (h ^ {*}) = \underbrace {L (\widehat {h}) - L (\bar {h})} _ {\text{估计误差（随机）}} + \underbrace {L (\bar {h}) - L (h ^ {*})} _ {\text{近似误差（确定性）}}
$$

Hypothesis class H

假设类 H

![image](<../Images/01_intro/image_008.jpg>)

<a id="classroom-risk-split"></a>

**Risk decomposition inserts the same intermediate reference twice**

**风险分解只是插入同一个中间参照**

$L(h)$ assigns an entire rule a long-run average-loss score; smaller is better. The diagram compares performance under the same true distribution and loss, not similarity of function shapes. Adding and subtracting $L(\bar h)$ splits the gap from the learned rule to the ideal optimum into a gap to the within-class optimum and a gap from that optimum to the ideal one.

$L(h)$ 是给整个规则打的“长期平均损失分数”，越小越好。图中比较的不是函数长得像不像，而是它们在同一真实分布、同一损失下的表现。把 $L(\bar h)$ 加一次再减一次，就把“实际规则到理想最优”的差拆成“实际规则到类内最优”和“类内最优到理想最优”两段。

With the distribution and candidate class fixed, the approximation term is fixed, while the estimation term varies with training data. In the earlier [three-function example](01_data_and_learning.md#classroom-three-functions), these two gaps were 0.05 and 0.04 respectively for estimation and approximation.

在分布和候选类固定时，近似项是固定的；估计项随训练数据变化。回想前面的[三个函数示例](01_data_and_learning.md#classroom-three-functions)，这两段就是 0.05 与 0.04。

*来源：[转录 3](../01_part3.md) 第 395–409 行。*

<a id="approximation-theory"></a>

### About approximation error

**关于近似误差**


- Cybenko (1989) - Denseness result in the spirit of Stone-Weierstrass showing that any linear combination of compositions of sigmoid with linear functions is dense wrt the supremum norm in the space of continuous functions over the d-dimensional unit cube.

  Cybenko（1989）：一个具有 Stone–Weierstrass 风格的稠密性结果，表明 sigmoid 与线性函数复合后所得函数的线性组合，在 d 维单位立方体上的连续函数空间中，关于上确界范数稠密。

- Barron (1994) - Approximation error bound involves a parameter quantifying the smoothness of the target function.

  Barron（1994）：近似误差界包含一个刻画目标函数光滑程度的参数。

- Status of this question in the regression setup :

  回归设定下这一问题的研究状况：

  - For kernel machines : a full theory is available thanks to Smale (2003), Steinwart (2008).

    对核方法：Smale（2003）、Steinwart（2008）的工作提供了完整理论。

  - For deep learning : recent work by Grohs, Perekrestenko, Elbrächter, and Bölcskei (2019) .

    对深度学习：Grohs、Perekrestenko、Elbrächter 和 Bölcskei（2019）的近期工作。

- In the classification setup, tough problem, still open issue...

  在分类设定下，这是一个困难的问题，仍有待解决……

<a id="classroom-approximation"></a>

**Being representable and being learnable from finite data are different questions**

**表达得出来，与用有限数据学得到，是两回事**

The approximation results listed here ask how closely a target can be approximated for a given function family and target regularity. They do not directly determine whether a finite training sample is sufficient, whether optimization succeeds, or how the resulting network performs on new samples.

这里列出的近似理论结果讨论：允许什么函数族、目标具有怎样的正则性时，能够逼近到什么程度。它们并不直接回答：有限训练样本够不够、优化是否成功、得到的网络在新样本上表现怎样。

This slide lists only a few representative works and does not establish the size of the whole literature. A comment that research on the two errors is uneven should not be turned into a claim that approximation theory contains only three or four papers. The useful distinction is: **representation capacity describes what could be achieved; statistical learning must explain how data can bring us close to it.**

这一页只选列了少量代表工作，不能据此判断整个领域的文献规模。转录中“两类误差的理论研究并不对称”的评论不宜进一步读成“近似理论只有三四篇论文”。学习时保留这条界线即可：**表示能力是可能达到的上限，统计学习还要解释怎样凭数据接近它。**

*来源：[转录 3](../01_part3.md) 第 104–122 行；[转录 3](../01_part3.md) 第 410–415 行。*

<a id="bias-variance"></a>

<a id="section-17"></a>

## What all students (should) know The bias-variance trade-off in statistical inference

**所有学生都（应该）知道的内容：统计推断中的偏差—方差权衡**

<a id="parametric-estimation"></a>

### The case of parametric estimation

**参数估计的情形**

$\Theta$ is a parameter set, subset of $\mathbb { R } ^ { p }$

$\Theta$ 是参数集合，是 $\mathbb { R } ^ { p }$ 的子集。

$P _ { \theta }$ with $\theta \in \Theta$ is a parametric class of distributions

$P _ { \theta }$（其中 $\theta \in \Theta$）构成一个参数化分布族。

$P _ { \theta ^ { * } }$ is the true distribution of the data for some $\theta ^ { \ast } \in \Theta$ (assumption)

对某个 $\theta ^ { \ast } \in \Theta$，$P _ { \theta ^ { * } }$ 是数据的真实分布（假设）。

$\widehat { \theta } _ { n }$ is an estimator of $\theta ^ { * }$ based on a sample of size n

$\widehat { \theta } _ { n }$ 是基于大小为 n 的样本对 $\theta ^ { * }$ 作出的估计量。


- Mean-squared error decomposition :

  均方误差分解：

$$
\begin{array}{r l} & {\mathbb {E} \left(\| \widehat {\theta} _ {n} - \theta^ {*} \| ^ {2}\right) =} \\ & {\qquad \mathbb {E} \left(\left((\widehat {\theta} _ {n} - \mathbb {E} (\widehat {\theta} _ {n})) (\widehat {\theta} _ {n} - \mathbb {E} (\widehat {\theta} _ {n})) ^ {T}\right)\right) + \| \mathbb {E} (\widehat {\theta} _ {n}) - \theta^ {*} \| ^ {2}} \end{array}
$$

**Exercise: compute the mean squared error (MSE) of OLS and Ridge regression.**

**练习：计算回归中 OLS 与 Ridge 回归的均方误差（MSE）。**

> **Note:** The first term on the original right-hand side is a covariance matrix, while the left-hand side is a scalar, so they cannot be equal. With squared Euclidean norm for a vector, every coordinate has a variance-plus-squared-bias decomposition. Summing coordinates makes the variance contribution the trace of the covariance matrix. The correct identity is $\mathbb E\|\widehat\theta_n-\theta^*\|^2=\operatorname{tr}\operatorname{Cov}(\widehat\theta_n)+\|\mathbb E\widehat\theta_n-\theta^*\|^2$.

> **译注：** 原式右侧第一项是协方差矩阵，左侧是标量，两边不能相等。对向量使用平方欧氏范数时，每个坐标各有一个“方差 + 平方偏差”分解，相加后方差部分就是协方差矩阵的迹，正确恒等式为 $\mathbb E\|\widehat\theta_n-\theta^*\|^2=\operatorname{tr}\operatorname{Cov}(\widehat\theta_n)+\|\mathbb E\widehat\theta_n-\theta^*\|^2$。

<a id="classroom-parameter-mse"></a>

**Why average over estimates obtained from fresh samples?**

**为什么要对“重新抽样得到的估计量”取平均**

When a Gaussian family models observations, its mean and variance determine the particular distribution. The true parameter $\theta^*$ is unknown, and $\widehat\theta_n$, computed from n samples, estimates it. The expectation here is not another average over one fixed data table. Imagine repeatedly drawing datasets of size n, recomputing the estimator each time, and examining the average behavior of those estimates.

若用一个高斯分布族描述观测，均值和方差决定族中具体是哪一个分布。真实参数 $\theta^*$ 未知，从 n 个样本算出的 $\widehat\theta_n$ 是它的估计。这里的期望不是“对一张已经固定的数据表再平均一次”，而是想象反复抽取大小为 n 的数据集，每次都重新计算估计量，再观察这些估计结果的平均表现。

Bias compares the mean of these estimates with the true parameter; variance describes their fluctuations around that mean. A method centered accurately but fluctuating substantially can still have large MSE. Another method with a small systematic offset but greater stability can have lower MSE. This explains why regularization that permits moderate bias can be useful.

偏差比较“这些估计的平均值”和真实参数；方差描述各次估计围绕其平均值的波动。某个方法平均位置很准，却每次都大幅波动，仍可能有较大均方误差；另一个方法略有系统偏移，却更稳定，均方误差反而可能更小。这也解释了为什么允许适度偏差的正则化值得考虑。

<details>
<summary>Derivation: why the cross term is zero<br>推导：交叉项为什么为零</summary>

First consider a scalar parameter and write $\mu=\mathbb E[\widehat\theta_n]$. Add and subtract the same value $\mu$:

先考虑标量参数，记 $\mu=\mathbb E[\widehat\theta_n]$。加上再减去同一个数 $\mu$：

$$
\widehat\theta_n-\theta^*=(\widehat\theta_n-\mu)+(\mu-\theta^*).
$$

Square and take expectations, using $(a+b)^2=a^2+b^2+2ab$, to obtain

平方后取期望，用 $(a+b)^2=a^2+b^2+2ab$，得到

$$
\mathbb E[(\widehat\theta_n-\theta^*)^2]
=\mathbb E[(\widehat\theta_n-\mu)^2]
+(\mu-\theta^*)^2
+2(\mu-\theta^*)\mathbb E[\widehat\theta_n-\mu].
$$

The last term is zero because $\mu-\theta^*$ is fixed and $\mathbb E[\widehat\theta_n-\mu]=0$. What remains is variance plus squared bias. The relevant second moments must exist.

最后一项等于零，因为 $\mu-\theta^*$ 是固定数，而 $\mathbb E[\widehat\theta_n-\mu]=0$。剩下的就是方差加平方偏差。这里要求相关二阶矩存在。

</details>

*来源：[转录 3](../01_part3.md) 第 416–449 行。*

<a id="prediction-error"></a>

### The case of prediction error in ML

**机器学习中预测误差的情形**


- Observations : scalar Y, d-dimensional covariate vectors X

  观测：标量 Y，以及 d 维协变量向量 X。

- Regression model : $Y = h ^ { \ast } ( X ) + \varepsilon$

  回归模型：$Y = h ^ { \ast } ( X ) + \varepsilon$。

- Random noise : ε independent of X

  随机噪声：ε 与 X 独立。

- Sample-based predictor $\widehat { h } _ { n }$

  基于样本的预测器 $\widehat { h } _ { n }$。

- Mean-squared error at a fixed point $\left( x , y \right)$

  在固定点 $\left( x , y \right)$ 处的均方误差：

$$
\mathbb {E} _ {n} \left((y - \widehat {h} _ {n} (x)) ^ {2}\right) = \left(\mathbb {E} _ {n} (\widehat {h} _ {n} (x)) - h ^ {*} (x)\right) ^ {2} + \mathbb {V} _ {n} \left(\widehat {h} _ {n} (x)\right) + \varepsilon^ {2}
$$

> **Note:** With $y$ fixed, the displayed equation generally fails, and $\varepsilon^2$ should be a noise variance. The correct object is an independent new observation $Y=h^*(x)+\varepsilon$ at x. If the noise has conditional mean zero and conditional variance $\sigma^2$, and the new noise is independent of the training sample, averaging over both gives $\mathbb E[(Y-\widehat h_n(x))^2\mid X=x]=(\mathbb E_n\widehat h_n(x)-h^*(x))^2+\operatorname{Var}_n(\widehat h_n(x))+\sigma^2$.

> **译注：** 固定 $y$ 时，上式通常不成立，原式中的 $\varepsilon^2$ 应为噪声方差。正确的对象是 x 处的一个独立新观测 $Y=h^*(x)+\varepsilon$：若噪声条件均值为零、条件方差为 $\sigma^2$，且新噪声与训练样本独立，对二者取期望得到 $\mathbb E[(Y-\widehat h_n(x))^2\mid X=x]=(\mathbb E_n\widehat h_n(x)-h^*(x))^2+\operatorname{Var}_n(\widehat h_n(x))+\sigma^2$。

$( \mathbb { E } _ { n } , \mathbb { V } _ { n }$ : expectation and variance wrt training sample)

（$( \mathbb { E } _ { n } , \mathbb { V } _ { n }$：相对于训练样本计算的期望和方差。）

MSE = Squared-bias term + Variance of predictions + Bayes error

均方误差 = 平方偏差项 + 预测值的方差 + Bayes 误差。

<a id="classroom-prediction-noise"></a>

**Why prediction error contains an extra noise term**

**预测误差为什么比参数误差多一项噪声**

Parameter estimation compares an estimate with a fixed true parameter. Predicting a new observation is different: even if the ideal regression function were known, the observation could still fluctuate. In the model $Y=h^*(X)+\varepsilon$, $h^*(X)$ is the part explained by the current input, while $\varepsilon$ represents the remaining random variation.

估计参数时，我们比较估计值与固定的真实参数；预测新观测时，即使已知理想回归函数，新观测本身仍可能波动。模型 $Y=h^*(X)+\varepsilon$ 中，$h^*(X)$ 描述可由当前输入解释的部分，$\varepsilon$ 表示模型中剩余的随机变化。

This noise term does not disappear simply by estimating parameters more accurately. Irreducible is relative to the current input information and modeling assumptions; it does not mean that additional informative observations can never help.

这个噪声项不会仅靠把参数估计得更精确就消失。“不可约”是相对于当前输入信息和建模设定而言，不意味着增加有效观测信息也永远无用。

*来源：[转录 3](../01_part3.md) 第 449–458 行。*

---

[本课目录](../01_intro_zh.md) · [上一篇：信息量、样本与 PAC 学习](03_information_and_pac.md) · [下一篇：线性模型：从拟合到预测误差](05_linear_models.md)
