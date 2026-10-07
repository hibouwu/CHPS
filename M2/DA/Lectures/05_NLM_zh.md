# 非线性方法：SVM、局部方法与集成：原课件忠实译本

> 正文按原课件顺序逐段翻译，不作摘要式压缩；例子、练习、重复正文、公式、图表及文献均保留。图中文字保留原图语言。原课件错误与必要辨析以独立“译注”标明。

[原 PDF](05_NLM.pdf) · [原文转换稿](05_NLM.md) · [逐块对应清单](Translation-audit/2026-09-28-coverage.json) · [课程目录](../README.md)

<details>
<summary>本讲目录（点击展开）</summary>

- [非线性方法：SVM、局部方法与集成](#section-01)
- [回顾：分类数据的概率模型](#section-02)
- [分类问题的形式化](#section-03)
- [评价准则：分类器的误差](#section-04)
- [实践中的留出法](#section-05)
- [生成式方法的局限](#section-06)
- [非参数线性判别算法](#section-07)
- [感知机算法（Rosenblatt，1958）](#section-08)
- [一般感知机算法](#section-09)
- [Novikoff 定理](#section-10)
- [场景 1：具有良好泛化能力的超平面](#section-11)
- [Karush–Kuhn–Tucker 条件](#section-12)
- [规范最优超平面](#section-13)
- [基于局部性的非线性模型](#section-14)
- [无需优化的正则化：直方图](#section-15)
- [这类正则化的组成要素](#section-16)
- [从直方图到机器学习](#section-17)
- [两类常见的局部方法](#section-18)
- [局部方法 1：k 近邻（k-NN）](#section-19)
- [局部方法 2：基于划分的方法（决策树）](#section-20)
- [关于局部方法的要点](#section-21)
- [浅层且高效的机器学习算法：集成方法](#section-22)
- [集成方法：出发点](#section-23)
- [决策树集成：一般原理](#section-24)
- [决策树集成：得到的分类器](#section-25)
- [决策树集成：三种常见方法](#section-26)
- [集成方法 1：Bagging 与随机森林](#section-27)
- [一般而言，bootstrap 是什么？](#section-28)
- [集成方法 2：Boosting](#section-29)
- [推断原则](#section-30)
- [经验风险最小化（ERM）](#section-31)
- [高效算法](#section-32)

</details>

**数据科学与机器学习导论**

Nicolas Vayatis

<a id="section-01"></a>

## 非线性方法：SVM、局部方法与集成

<a id="section-02"></a>

## 回顾：分类数据的概率模型

### 监督分类的概率模型

- $(X, Y)$：一对概率分布 $P$ 未知的随机变量。
- $X \in \mathcal{X}$：可测空间上的观测，例如 $\mathbb{R}^d$。
- $Y \in \{-1, +1\}$：二元标签／类别（为简单起见）。

→ 如何从条件分布描述随机变量对 $(X, Y)$ 的联合分布 $P = \mathcal{L}(X, Y)$？

### 联合分布的描述

1. 生成式方法：$\mathcal{L}(X, Y) = \mathcal{L}(Y) \otimes \mathcal{L}(X \mid Y)$。
- 混合模型，其参数为：

$$
p = \mathbb {P} \{Y = + 1 \} \in [ 0, 1 ]
$$

- $\mathbb{R}^d$ 上的条件分布：

$$
P _ {+} = \mathcal {L} (X \mid Y = + 1) \quad \text{且} \quad P _ {-} = \mathcal {L} (X \mid Y = - 1)
$$

2. 判别式方法：$\mathcal{L}(X,Y)=\mathcal{L}(X)\otimes\mathcal{L}(Y\mid X)$。
- $\mathbb{R}^{d}: P_{X} = \mathcal{L}(X)$ 上的边际分布。
- 最佳预测：

$$
\eta (x) = \mathbb {P} \{Y = + 1 \mid X = x \}, \quad \forall x \in \mathbb {R} ^ {d}
$$

- 边际分布（“dP”表示分布的密度）：

$$
d P _ {X} = p d P _ {+} + (1 - p) d P _ {-}
$$

- 后验概率（回归函数）：

$$
\forall x \in \mathcal {X}, \qquad \eta (x) = \frac {p d P _ {+}}{p d P _ {+} + (1 - p) d P _ {-}} (x)
$$

- 一个备注：

$$
\eta (x) > \frac {1}{2} \quad \Leftrightarrow \quad p d P _ {+} (x) > (1 - p) d P _ {-} (x)
$$

<a id="section-03"></a>

## 分类问题的形式化

### 二分类问题

- 可用数据：$(x_1, y_1), \ldots, (x_n, y_n)$，$x_i \in \mathbb{R}^d$，$y_i \in \{-1, +1\}$。
- 问题：已知 x，预测标签 y。
- 要寻找：一个分类器 $g$：$\mathbb{R}^d \to \{-1, +1\}$。
- 问题：找到一个能够良好“泛化”的分类器 $g$。
- 思路：选择一个能够很好地“解释”数据、但又不过度解释的 $g$！
- 具体而言：通常先寻找决策函数 $f: \mathbb{R}^{d} \to \mathbb{R}$，再将其与分类器 $g = \text{sgn}(f)$ 对应。

<a id="section-04"></a>

## 评价准则：分类器的误差

- 给定一个观测 $x$，分类器 $g$ 作出预测 $g(x)$，将其与类别 $y$ 比较。

分类器的误差 = 被错误分类的观测所占比例。

$$
\hat {L} _ {n} (g) = \frac {1}{n} \sum_ {i = 1} ^ {n} \mathbb {I} _ {[ g (x _ {i}) \neq y _ {i} ]} = \frac {\# \{i : g (x _ {i}) \neq y _ {i} \}}{n}
$$

这个误差也称为训练误差。

- 如果分类器 $g$ 的训练误差低，就说它能够恰当地“解释”数据。

<a id="section-05"></a>

## 实践中的留出法

- 将可用数据分为两个子集：
- 训练集：$(X_1, Y_1), \ldots, (X_n, Y_n)$。
- 测试集：$(X_{n+1}, Y_{n+1}), \ldots, (X_{n+m}, Y_{n+m})$。
- 对任意分类器 $g$，测试误差 $\hat{L}_{m}^{\prime}(g) = \frac{1}{m}\sum_{j=1}^{m}\mathbb{I}_{[g(X_{n+j})\neq Y_{n+j}]}$ 是 $L(g)$ 的估计量（如果 $g$ 是学习得到的，可以对训练集取条件）。
- 更好的实践：使用交叉验证，使 $L(g)$ 的估计更稳健。

<a id="section-06"></a>

## 生成式方法的局限

- 上一讲提到的方法：判别分析、逻辑回归。
- 参数统计模型：“所有模型都是错的”……
- 很强的建模先验：“……但有些模型是有用的”。
- 高斯框架。
- 线性模型。
- 维数灾难（参见 Bellman）。

<a id="section-07"></a>

## 非参数线性判别算法

1. 两个群体线性可分。
2. 两个群体近似线性可分。
3. 两个群体不能线性分离。

### 线性可分性

![image](<Images/05_NLM/image_001.jpg>)

场景 1

![image](<Images/05_NLM/image_002.jpg>)

场景 2

- 决策函数的形式：

$$
f (x) = b + <   \beta , x >
$$

其中 $b \in \mathbb{R}$，$\beta \in \mathbb{R}^d$。

- 方程 $f(x) = 0$ 在 $\mathbb{R}^d$ 中定义一个分隔超平面 $H$。
- 对应的分类器：

$$
\forall x \in \mathbb {R} ^ {d} \quad g _ {f} (x) = \left\{ \begin{array}{l l} + 1 & \text{若} f (x) > 0 \\ - 1 & \text{若} f (x) \leq 0 \end{array} \right.
$$

1. $\beta^{*}=\frac{\beta}{\|\beta\|}$ 是 H 的法向量。

② $\forall x_{0} \in H, <\beta, x_{0} > = -b$

3. 点 $x \in R^{d}$ 到 H 的有符号距离（可以为负！）为

$$
d (x, H) = <   \beta^ {*}, x - x _ {0} > = \frac {1}{\| \beta \|} (b + <   \beta , x >)
$$

其中 $x_0 \in H$。

![image](<Images/05_NLM/image_003.jpg>)

二维训练集的分隔超平面 $(\boldsymbol{w}, b) \in \mathbb{R}^{n} \times \mathbb{R}$。

注意！这里 $w = \beta$……

<a id="section-08"></a>

## 感知机算法（Rosenblatt，1958）

### 简化版本：b = 0

生成参数 $\beta$ 的取值序列 $\beta_{0},\ldots,\beta_{n}$。

1. 初始化：$\beta_{0} = 0$。
2. 第 i 步：考虑数据对 $(x_{i}, y_{i})$，检查它是否被正确分类。

$$
\beta_ {i} = \left\{ \begin{array}{l l} \beta_ {i - 1} & \text{若} y _ {i} \cdot <   \beta_ {i - 1}, x _ {i} > > 0 \\ \beta_ {i - 1} + y _ {i} x _ {i} & \text{若} y _ {i} \cdot <   \beta_ {i - 1}, x _ {i} > \leq 0 \end{array} \right.
$$

<a id="section-09"></a>

## 一般感知机算法

### 感知机：一般版本

- 参数：
- 学习率 η。
- 观测的半径 $R = \max_{1 \leq i \leq n} \|x_i\|$。

### 算法

1. 初始化：$\beta_{0}=0$，$b_{0}=0$。
2. 第 i 步：如果 $(x_{i}, y_{i})$ 被超平面 $(b_{i-1}, \beta_{i-1})$ 错误分类，则：

$$
{\beta_ {i}} {= \beta_ {i - 1} + \eta y _ {i} x _ {i}}
$$

$$
{b _ {i}} {= b _ {i - 1} + \eta y _ {i} ^ {2} R ^ {2}}
$$

> **译注：** 原课件截距更新含 $y_i^2$，在标签为 $\pm1$ 时会丢失符号；按增广向量 $(x_i,R)$ 的约定，应为 $b_i=b_{i-1}+\eta y_iR^2$。

否则 $\beta_{i}=\beta_{i-1},\ b_{i}=b_{i-1}$。

<a id="section-10"></a>

## Novikoff 定理

如果两个群体线性可分，则感知机算法在有限的 $T \leq n$ 步内收敛，其中：

$$
T \leq \frac {2 R ^ {2}}{M ^ {2}}
$$

这里，对某个分隔面 $H^*$，有 $M = \min_{1 \leq i \leq n} \{ y_i d(x_i, H^*) \}$。

> **译注：** 原课件写出的 $T\le n$ 不普遍成立。标准感知机界按错误更新次数计数，使用同一增广空间中的样本半径和分隔间隔；不能直接把原空间的几何距离与增广间隔混用。

- 感知机的缺点：泛化能力差。
- 感知机的优点：序贯（在线）算法。

<a id="section-11"></a>

## 场景 1：具有良好泛化能力的超平面

问题：是否存在与每个群体的距离都尽可能大的超平面？

![image](<Images/05_NLM/image_004.jpg>)

### 优化问题

$$
\max _ {\beta \in \mathbb {R} ^ {d}, b \in \mathbb {R}} M
$$

约束条件：

$$
\forall i = 1, \dots , n, \quad y _ {i} \cdot d (x _ {i}, H) \geq M
$$

回顾：

$$
d (x _ {i}, H) = \frac {1}{\| \beta \|} (b + <   \beta , x _ {i} >)
$$

约束：

$$
\forall i = 1, \dots , n, \quad y _ {i} \cdot \frac {1}{\| \beta \|} (b + <   \beta , x _ {i} >) \geq M
$$

完全可以设定：$M = 1 / \|\beta\|$。

### 等价表述

$$
\min _ {\beta , b} \frac {1}{2} \| \beta \| ^ {2}
$$

约束条件：

$$
\forall i = 1, \dots , n, \quad y _ {i} \cdot (b + <   \beta , x _ {i} >) \geq 1
$$

![image](<Images/05_NLM/image_005.jpg>)

$$
\text{场景 2：松弛变量（续）}
$$

引入 $n$ 个附加变量（“松弛变量”或“弹簧”）：$\xi = (\xi_1, \ldots, \xi_n)$，满足 $\xi_i \geq 0, \forall i$。

### 新的优化问题

$$
\min _ {\beta , b, \xi} \frac {1}{2} \| \beta \| ^ {2}
$$

约束条件：

$$
\forall i = 1, \dots , n, y _ {i} \cdot (b + <   \beta , x _ {i} >) \geq 1 - \xi_ {i}
$$

$$
\xi_ {i} \geq 0
$$

$$
\sum_ {i = 1} ^ {n} \xi_ {i} \leq \Xi
$$

### 拉格朗日表述 I

$$
\min _ {\beta , b, \xi} \frac {1}{2} \| \beta \| ^ {2} + C \sum_ {i = 1} ^ {n} \xi_ {i}
$$

约束条件：

$$
\begin{array}{r l} \forall i = 1, \ldots , n, & \xi_ {i} \geq 0 \\ & \xi_ {i} \geq 1 - [ y _ {i} \cdot (b + <   \beta , x _ {i} >) ] \end{array}
$$

### 拉格朗日表述 II：拉格朗日乘子 $\alpha = (\alpha_{1}, \ldots, \alpha_{n})$、$\mu = (\mu_{1}, \ldots, \mu_{n})$

$$
\min _ {\beta , b, \xi} \frac {1}{2} \| \beta \| ^ {2} + C \sum_ {i = 1} ^ {n} \xi_ {i} - \sum_ {i = 1} ^ {n} \alpha_ {i} \left(y _ {i} \cdot (b + <   \beta , x _ {i} >) - (1 - \xi_ {i})\right) + \sum_ {i = 1} ^ {n} \mu_ {i} \xi_ {i}
$$

一阶条件（梯度为零）：

$$
\beta = \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} x _ {i}
$$

$$
\sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} = 0
$$

$$
\forall i = 1, \ldots , n, \alpha_ {i} = C + \mu_ {i}
$$

### 对偶表述

$$
\max _ {\alpha} \sum_ {i = 1} ^ {n} \alpha_ {i} - \frac {1}{2} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \alpha_ {i} \alpha_ {j} y _ {i} y _ {j} <   x _ {i}, x _ {j} >
$$

约束条件：

$$
\begin{array}{r l} \forall i = 1, \ldots , n, & 0 \leq \alpha_ {i} \leq C \\ \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} & = 0 \end{array}
$$

用 $\hat{\alpha} = (\hat{\alpha}_1, \ldots, \hat{\alpha}_n)$ 表示该问题的解。

<a id="section-12"></a>

## Karush–Kuhn–Tucker 条件

Karush–Kuhn–Tucker 条件：

$$
\begin{array}{r l} \forall i = 1, \ldots , n, & \alpha_ {i} (y _ {i} \cdot f (x _ {i}) - (1 - \xi_ {i})) = 0 \\ & y _ {i} \cdot f (x _ {i}) - (1 - \xi_ {i}) \geq 0 \\ & \alpha_ {i} + \mu_ {i} = C \\ & \mu_ {i} \xi_ {i} = 0 \\ & \beta = \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} x _ {i} \\ & \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} = 0 \end{array}
$$

系数与观测位置的联系：

- 如果 $\hat{\alpha}_i = 0$，则 $y_i \cdot f(x_i) \geq 1 \Rightarrow$，点 $x_i$ 被正确分类，因为 $\mu_i = C > 0$，并且有 $\xi_i = 0$。
- 如果 $0 < \hat{\alpha}_i < C$，则 $y_i \cdot f(x_i) = 1 \Rightarrow$，点 $x_i$ 位于间隔边界上，因为 $\mu_i > 0$ 且 $\xi_i = 0$。
- 如果 $\hat{\alpha}_i = C$，则 $y_i \cdot f(x_i) \leq 1 \Rightarrow$，点 $x_i$ 越过间隔边界，因为 $\mu_i = 0$，所以 $\xi_i \geq 0$。

> **译注：** $\widehat\alpha_i=C$ 时只能推出 $y_if(x_i)\le1$，包括等号；不能断言该点严格越过间隔边界或一定误分类。

一个值得注意的现象！

实际中，许多 $\hat{\alpha}_i$ 为零！

### 定义

$\hat{\alpha}_i \neq 0$ 对应支持向量。用 $I$ 表示 $\{1, \ldots, n\}$ 中相应索引构成的集合。

### 解的表示

决策函数：

$$
\hat {f} (x) = \hat {b} + \sum_ {i \in I} \hat {\alpha} _ {i} y _ {i} <   x _ {i}, x >
$$

其中：

$$
\hat {\beta} = \sum_ {i \in I} \hat {\alpha} _ {i} y _ {i} x _ {i}, I = \{i: \hat {\alpha} _ {i} \neq 0 \}
$$

$$
\hat {b} = y _ {j} - \sum_ {i \in I} \hat {\alpha} _ {i} y _ {i} <   x _ {i}, x _ {j} >, \quad \text{对某个} j \in I
$$

<a id="section-13"></a>

## 规范最优超平面

![image](<Images/05_NLM/image_006.jpg>)

⇒ SVM 的稀疏表示。

<a id="kernel-svm"></a>

- 大多数分类问题需要非线性分隔。
- 构造最优间隔超平面的算法只通过内积 $< x_i, x_j >$ 使用观测，其中 $i, j$。
- 决策函数依赖新点 $x$ 与支持向量 $x_i$ 之间的内积。
- 核技巧：构造最优间隔超平面的算法只通过 Gram 矩阵的元素依赖于观测。

$$
K = \big (<   x _ {i}, x _ {j} > \big) _ {1 \leq i, j \leq n}
$$

- 核方法：用一个正定核替换标准内积。

$$
k: \mathcal {X} \times \mathcal {X} \to \mathbb {R}
$$

于是 $K$ 变为以 $k(x_{i},x_{j})$ 为元素的矩阵。

### 对偶表述

$$
\max _ {\alpha} \sum_ {i = 1} ^ {n} \alpha_ {i} - \frac {1}{2} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \alpha_ {i} \alpha_ {j} y _ {i} y _ {j} k (x _ {i}, x _ {j})
$$

约束条件：

$$
\begin{array}{r l} \forall i = 1, \ldots , n, & 0 \leq \alpha_ {i} \leq C \\ \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} & = 0 \end{array}
$$

决策函数：

$$
\hat {f} (x) = \hat {b} + \sum_ {i \in I} \hat {\alpha} _ {i} k (x _ {i}, x)
$$

> **译注：** 原课件的核 SVM 决策函数漏了标签因子。若沿用上方对偶变量定义，应为 $\widehat f(x)=\widehat b+\sum_{i\in I}\widehat\alpha_i y_i k(x_i,x)$；只有把标签吸收到另一定义的系数中时才能省略它。

其中 I 为支持向量的索引集合。

- 多项式核。

$$
\begin{array}{r l} {k _ {r} (x, x ^ {\prime})} & {= (<   x, x ^ {\prime} >) ^ {r}} \\ {k _ {r, c} (x, x ^ {\prime})} & {= (<   x, x ^ {\prime} > + c) ^ {r}} \end{array}
$$

- 高斯径向基函数核（RBF）。

$$
k _ {\sigma} (x, x ^ {\prime}) = \exp \left(- \frac {\| x - x ^ {\prime} \| ^ {2}}{2 \sigma^ {2}}\right)
$$

- sigmoid 核（神经网络）。

$$
k _ {\kappa , \theta} (x, x ^ {\prime}) = \tanh (\kappa <   x, x ^ {\prime} > + \theta)
$$

> **译注：** sigmoid 形式并非对任意参数、任意输入集合都构成正定核；使用核 SVM 时还需检查其适用条件。

- 选择核。
- 参数调整：使用验证集。
- 性能度量：测试集上的误差。
- 与其他方法比较。
- 扩展：
- 超过两个类别的分类问题。
- 各群体比例极不均衡的情形。

<a id="local-methods"></a>

<a id="section-14"></a>

## 基于局部性的非线性模型

### 其他形式的正则化

- 总体思路：不进行全局优化的正则化函数估计。
- 两个方向：
- 局部方法：最近邻与决策树。
- 集成方法：Bagging、Boosting、随机森林。

<a id="section-15"></a>

## 无需优化的正则化：直方图

![image](<Images/05_NLM/image_007.jpg>)

![image](<Images/05_NLM/image_008.jpg>)

![image](<Images/05_NLM/image_009.jpg>)

![image](<Images/05_NLM/image_010.jpg>)

Titanic 乘客的年龄分布，分箱宽度从 1 年变化到 15 年。

<a id="section-16"></a>

## 这类正则化的组成要素

- 直方图使用两个一般思想：局部性（分箱）与平均（分段常数函数）。
- 定义局部：哪些训练数据可以认为接近待预测的点？
- 平均（若结果离散则为投票）：对每个分箱内的值取平均。
- 通过超参数选择进行正则化：寻找最优分箱大小，相当于寻找恰当的假设类。

<a id="section-17"></a>

## 从直方图到机器学习

- 在前面的例子中，目标是根据从某个分布中抽取的样本估计该分布的密度函数；文献中将这一问题称为非参数密度估计或核密度估计。

> **译注：** 直方图属于非参数密度估计；它与通常通过平滑核函数构造的核密度估计不应简单视为同义方法。

- 密度估计可视为无监督学习问题。
- 在监督学习设定下，通过平均（回归情形）或投票（分类情形）确定每个分箱上的函数值。平均／投票的通用名称是聚合／组合。

<a id="section-18"></a>

## 两类常见的局部方法

- 最近邻：局部点是距离最近的点。
- 基于划分的规则，也称决策树：局部点仅指输入空间某个划分单元内的点。

这些方法适用于分类、回归及其他问题……但这里重点讨论分类。

- 已知：
- 考虑一个分类数据样本

$$
(X _ {1}, Y _ {1}) \dots (X _ {n}, Y _ {n})
$$

其中 $X_{i} \in R^{d}$ 是自变量向量，

$Y_{i}\in \{1,\dots ,C\}$ 是标签。

- 希望：
- 在任意位置 x 预测标签 y。

<a id="section-19"></a>

## 局部方法 1：k 近邻（k-NN）

### k 近邻（1/4）：算法原理

#### 1. 计算距离

- 对所有 $i = 1, \ldots, n$，计算两两距离 $d(x, X_{i})$。

#### 2. 对训练数据排序

- 将数据点从最近的 $X_{(1)}$ 排到最远的 $X_{(n)}$，即 $d(x, X_{(1)}) \leq \ldots \leq d(x, X_{(n)})$。

#### 3. 预测 $\hat{h}(x,k)=$：k 个最近邻的多数投票

- 考虑距离 $x$ 最近的 $k$ 个点的标签 $Y_{(1)}, \ldots, Y_{(k)}$，进行多数投票。

$$
\hat {h} (x, k) = \arg \max _ {c} \{\sum_ {l = 1} ^ {k} \mathbb {I} \{Y _ {(l)} = c \} \}
$$

### k 近邻（2/4）：算法原理

#### kNN 算法

0. 观察数据。

![image](<Images/05_NLM/image_011.jpg>)

假设要将灰色点分到某个类别。这里有三个可能的类别：黄绿色、绿色和橙色。

1. 计算距离。

![image](<Images/05_NLM/image_012.jpg>)

首先计算灰色点与其他所有点之间的距离。

#### 2. 找到邻居

![image](<Images/05_NLM/image_013.jpg>)

接下来按距离递增排列各点，找出最近邻。灰色点的最近邻就是数据空间中距离它最近的点。

#### 3. 对标签投票

![image](<Images/05_NLM/image_014.jpg>)

该类别赢得投票！

归入该类别。

根据 k 个最近邻的类别，对预测类别标签进行投票。这里基于 k = 3 个最近邻预测标签。

> **译注：** 原页图中文字写 k=3，但投票表中的计数为 2、1、1，共 4 票；此处按原文保留，并指出图文不一致。

### 超参数

- 选择 $\mathbb{R}^d$ 中点之间的距离 $d$。
- 最近邻个数 k，通过交叉验证估计：

![image](<Images/05_NLM/image_015.jpg>)

![image](<Images/05_NLM/image_016.jpg>)

![image](<Images/05_NLM/image_017.jpg>)

- 回顾：分类误差 $L(h) = \mathbb{P}(Y \neq h(X))$，以及 $L^* = \inf L$。
- 一致性结果：

$$
\mathbb {E} L \big (\hat {h} (\cdot , k _ {n}) \big) \to L ^ {*}
$$

条件为：当 $n \rightarrow \infty$ 时，$k_{n} \rightarrow \infty$ 且 $k_{n}/n \rightarrow 0$。

- 最优 $k_{n}$ 没有闭式解；实践中使用交叉验证。
- 距离的选择没有理论线索，它与数据表示及问题的物理性质有关。

> **译注：** 原文的说法较强；这些一致性条件本身不能给出适合任意任务的最佳距离，但并不意味着距离选择完全没有理论研究。

<a id="decision-trees"></a>

<a id="section-20"></a>

## 局部方法 2：基于划分的方法（决策树）

### 基于划分的分类器（1/4）

对固定划分计算预测。用 $c = \bigcup_{j} \gamma_{j}$ 表示划分，其单元为 $\gamma_{j}$。

1. 找出 x 所在的单元 $\gamma(x)$。
2. 考虑单元 $\gamma(x)$ 中的训练数据。
3. 预测 $\hat{h}(x,c)=$：对单元 $\gamma(x)$ 中的训练数据进行多数投票。

![image](<Images/05_NLM/image_018.jpg>)

![image](<Images/05_NLM/image_019.jpg>)

### 基于划分的分类器（2/4）：构建数据驱动的划分

- 从所有训练数据开始，寻找一个使某个代价函数最小的简单分类器。
- 对该分类器边界两侧的训练数据子集重复这一过程，$\longrightarrow$ 这称为递归划分。

![image](<Images/05_NLM/image_020.jpg>)

树表示

X 定义域的递归划分

### 基于划分的分类器（3/4）：超参数

- 局部优化的代价函数：在单元层面，针对单元内的数据优化。
- 每个单元中的最少点数。
- 树的最大深度或单元总数，通过剪枝估计。剪枝相当于探索所有子划分（子树）构成的类，并优化如下惩罚准则：

$$
\arg \min _ {c} \hat {L} _ {n} (h _ {c}) + \lambda | c |
$$

其中 $c \subset \hat{c}$ 是从已学得的划分出发、自下而上剪枝得到的子划分集合。

![image](<Images/05_NLM/image_021.jpg>)

- 规则划分情形：单元是 $\mathbb{R}^d$ 中边长为 $\delta_n$ 的超立方体。

$$
\mathbb {E} L (\hat {h} (\cdot , \delta_ {n})) \to L ^ {*}
$$

条件为：当 $n \rightarrow \infty$ 时，$n\delta_{n}^{d} \rightarrow \infty$ 且 $\delta_{n} \rightarrow 0$；需要每个单元中有足够多的数据点，并且单元直径随样本量增加而趋于零。

- 数据驱动的划分：VC 理论和 Rademacher 理论适用。

<a id="section-21"></a>

## 关于局部方法的要点

### 主要局限

- $k$ 近邻方法需要存储全部训练数据，才能预测新输入的标签。
- 决策树极不稳定。
- 两者的预测性能都低于当时最先进的方法。

### 决策树的优点

- 可以处理缺失数据、类别数据和尺度变化。
- 可以表述为逻辑规则，$\longrightarrow$ 可解释机器学习。

决策树中有哪些东西值得保留？

<a id="section-22"></a>

## 浅层且高效的机器学习算法：集成方法

1. Bagging 与随机森林。
2. Boosting。

### 集成的动机：其他领域的线索

- 技术：数据科学竞赛冠军将多种方法组合起来提高性能，例如 Netflix 挑战赛获胜者 BelKor 团队。
- 决策理论：社会选择理论。
- 概率论：遍历定理。
- 非参数统计：聚合估计量。

<a id="section-23"></a>

## 集成方法：出发点

- 假设已有一个性能尚可、希望进一步改进的机器学习算法，例如决策树、k-NN、SVM 等。
- 集成的思想是：从相同训练数据与相同假设空间产生不同的函数。
- 在接下来的示例及大部分讨论中，基础假设空间由通过正交切分得到的决策树构成；这样的切分称为决策树桩。

<a id="section-24"></a>

## 决策树集成：一般原理

- 使用基础机器学习算法，例如决策树，生成一组弱预测器，即集成。
- 对每个点 $x$，计算各预测器的预测。
- 对各预测取平均或多数投票，得到集成的预测。

![image](<Images/05_NLM/image_022.jpg>)

<a id="section-25"></a>

## 决策树集成：得到的分类器

![image](<Images/05_NLM/image_023.jpg>)

<a id="section-26"></a>

## 决策树集成：三种常见方法

- Bagging（Breiman，1996）。
- 随机森林（Amit–Geman，1997；Breiman，2000）。
- Boosting（Freund–Schapire，1996）。

<a id="bagging"></a>

<a id="section-27"></a>

## 集成方法 1：Bagging 与随机森林

### Bagging 与随机森林的假设空间是什么？

- 用 $\mathcal{H}$ 表示基础假设空间，对应已有的那个表现不算出色的算法，例如决策树。
- 用 $D_{n}$ 表示训练数据，并假设在给定 $D_{n}$ 的条件下，能够从 $\mathcal{H}$ 中抽样得到函数 $\hat{h}_1, \ldots, \hat{h}_t$，即集成。
- 对由 $T$ 个函数组成的集成，Bagging／随机森林的输出是这些基于数据生成的“随机”函数的平均：

$$
\hat {f} _ {T} = \frac {1}{T} \sum_ {t = 1} ^ {T} \hat {h} _ {t}
$$

- 这些方法的假设空间是基础假设空间 $\mathcal{H}$ 的线性张成空间。这个空间可能非常大！

> **译注：** 上式实值平均函数属于基础函数类的凸包，因而属于线性张成空间；若随后取符号或最大概率类别，最终离散分类器不必属于这个空间。

- Bagging 与随机森林都依赖对训练数据进行 bootstrap 抽样。
- 两者的区别在于构建每棵树时，对递归划分过程作了不同的规定；其中不进行剪枝。

<a id="section-28"></a>

## 一般而言，bootstrap 是什么？

| 观测编号 | X | Y |
| --- | --- | --- |
| 3 | 5.3 | 2.8 |
| 1 | 4.3 | 2.4 |
| 3 | 5.3 | 2.8 |

![image](<Images/05_NLM/image_024.jpg>)

| 观测编号 | X | Y |
| --- | --- | --- |
| 1 | 4.3 | 2.4 |
| 2 | 2.1 | 1.1 |
| 3 | 5.3 | 2.8 |

原始数据（Z）

| 观测编号 | X | Y |
| --- | --- | --- |
| 2 | 2.1 | 1.1 |
| 3 | 5.3 | 2.8 |
| 1 | 4.3 | 2.4 |

| 观测编号 | X | Y |
| --- | --- | --- |
| 2 | 2.1 | 1.1 |
| 2 | 2.1 | 1.1 |
| 1 | 4.3 | 2.4 |

- 某个理想化 Bagging 版本的一致性结果。
- 最重要的一点：Bagging 可以把不一致的规则变成一致规则！
- Biau、Devroye 和 Lugosi（2008）研究了将 Bagging 应用于 1-NN。一般分类情形下，1-NN 不一致，零噪声或纯随机标签的情形除外。
- 在对采样过程施加某些合理条件后，对 1-NN 分类器进行 Bagging 可以得到一致性。

> **译注：** 上述结论依赖采样条件。“纯随机标签”的例外不能理解为任意与输入独立的标签分布：正负均衡是一个典型例外，类别比例不均衡时 1-NN 不会因此自动达到 Bayes 风险。

<a id="boosting"></a>

<a id="section-29"></a>

## 集成方法 2：Boosting

### Boosting 的历史视角

- 原始论文：Freund, Y. 与 Schapire, R. E.（ICML，1996）。
- 将所求解的优化问题解释为随机梯度下降：Friedman, J. H.（CSDA，2002）。
- Wald 纪念讲座（IMS，2000）：Leo Breiman 宣称，“理解 Boosting 是机器学习中最重要的问题”。
- Boosting 一致性的证明：Lugosi, G. 与 Vayatis, N.（Annals of Statistics 含讨论的专刊，2004）。
- 可扩展的实现 XGBoost：Chen, T. 与 Guestrin, C.（ACM SIGKDD，2016）。
- 输入：
- 数据样本 $D_{n} = \{(X_{i}, Y_{i}) : i = 1, \dots, n\}$，其中分类数据满足 $\{-1, +1\}$。
- 弱分类器的基础假设类 $\mathcal{H}$，例如决策树；假设该类对称，即 $h \in \mathcal{H}$ 当且仅当 $-h \in \mathcal{H}$。
- 迭代 $t = 1, \ldots, T$。
- 计算权重 $w_{t} > 0$ 与弱分类器 $\widehat{h}_{t} \in H$。
- 输出：
- Boosting 分类器对如下弱分类器线性组合取符号：$\widehat{f}_n(x) = \sum_{t=1}^{T} w_t \widehat{h}_t(x)$。
- 数据上的 Boosting 分布：定义在 $\{1, \ldots, n\}$ 上的一列离散概率分布，记为 $\Pi_t$，$t \geq 1$。
- 加权训练误差：对任意弱分类器 $h \in \mathcal{H}$，以及 $t \geq 1$，

$$
\widehat {\varepsilon} _ {t} (h) = \sum_ {i = 1} ^ {n} \Pi_ {t} (i) \mathbb {I} \{h (X _ {i}) \neq Y _ {i} \}
$$

### Boosting（3/7）

原始算法：AdaBoost。

1. 初始化：$\Pi_{1}$ 是 $\{1,\ldots,n\}$ 上的均匀分布。
2. Boosting 迭代：对 $t = 1, \ldots, T$，寻找满足下式的弱分类器：

$$
\widehat {h} _ {t} = \underset {h \in \mathcal {H}} {\arg \min} \widehat {\varepsilon} _ {t} (h)
$$

然后令 $e_{t}=\widehat{\varepsilon}_{t}(\widehat{h}_{t})$，并取权重为

$$
w _ {t} = \frac {1}{2} \log \left(\frac {1 - e _ {t}}{e _ {t}}\right)
$$

3. 更新 Boosting 分布：对任意 $i = 1, \ldots, n$，

$$
\Pi_ {t + 1} (i) \propto \Pi_ {t} (i) \exp \left(- w _ {t} Y _ {i} \cdot \widehat {h} _ {t} (X _ {i})\right)
$$

![image](<Images/05_NLM/image_025.jpg>)

![image](<Images/05_NLM/image_026.jpg>)

![image](<Images/05_NLM/image_027.jpg>)

![image](<Images/05_NLM/image_028.jpg>)

![image](<Images/05_NLM/image_029.jpg>)

- Boosting 可以解释为针对如下泛函进行的函数空间梯度下降：

$$
\hat {A} _ {n} (f) = \frac {1}{n} \sum_ {i = 1} ^ {n} \exp \left(- Y _ {i} f (X _ {i})\right)
$$

其中 f 所在的假设空间，是“简单”分类器集合 H 的线性张成空间。

- 练习：为什么？

参见：J. Friedman，Greedy Function Approximation: A Gradient Boosting Machine（贪心函数逼近：梯度提升机），The Annals of Statistics，第 29 卷第 5 期，2001。

### Boosting（6/7）

#### 梯度提升的超参数

- 迭代次数 $T$：越大，过拟合的可能性越高。
- 步长 $\eta$ 固定：降低学习率往往可以改善泛化性能。

![image](<Images/05_NLM/image_030.jpg>)

### Boosting（7/7）：尚未完全解释的谜题

尽管训练误差已经为零，测试误差仍随迭代继续下降。$\longrightarrow$ 是平均带来的正则化效应吗？？

![image](<Images/05_NLM/image_031.jpg>)

- Python：scikit-learn。
- R：
- rpart：递归划分。
- caret：分类与回归训练（SVM、随机森林等）。
- xgboost：极端梯度提升。

<a id="surrogate-loss"></a>

<a id="section-30"></a>

## 推断原则

- 一种误差度量：

$$
L (g) = \mathbb {P} \left\{Y \cdot g (X) <   0 \right\} = \mathbb {E} \left(\mathbb {I} _ {[ Y \cdot g (X) <   0 ]}\right)
$$

- Bayes 分类器与 Bayes 误差：

$$
\begin{array}{r l} {g ^ {*}} & {= \underset {g} {\arg \min} L (g) = \operatorname{sgn} \left(\eta - \frac {1}{2}\right)} \\ {L ^ {*}} & {= L (g ^ {*})} \end{array}
$$

- 经验准则：

$$
\hat {L} _ {n} (g) = \frac {1}{n} \sum_ {i = 1} ^ {n} \mathbb {I} _ {[ Y _ {i} \cdot g (X _ {i}) <   0 ]}
$$

<a id="section-31"></a>

## 经验风险最小化（ERM）

Vapnik 的理论（1995 年起）使人们能够发展针对高维数据分类的一致策略。

### ERM 的缺点

- 算法方面：NP-hard 问题。
- 复杂度控制：需要 Glivenko–Cantelli 性质以避免过拟合。

### 但是

高效方法在非常庞大的函数类中构建估计量！

<a id="section-32"></a>

## 高效算法

### 1. 支持向量机：Vapnik（1995）

- 核技巧：将数据映射到一个 Hilbert 空间，使数据在其中近似线性可分。
- 最大间隔超平面：带二次约束的凸优化。

> **译注：** 按前文标准软间隔 SVM 的表述，目标是凸二次函数，约束为线性不等式；原文此处“二次约束”的说法不准确。

### 2. Boosting：Freund（1990）；Freund、Schapire（1996）

- 从简单分类器的类 H 开始。
- 然后迭代构造简单分类器的线性组合，使经验误差下降。

“Boosting 是世界上最好的开箱即用分类器。”——Breiman，1996。

### 共同特征

如果暂不考虑：

1. 几何直觉；
2. 各算法特有的动态过程，那么：

Boosting 与 SVM 都可以看作：

### 在庞大的函数空间中最小化带惩罚的凸风险的过程。

它们的区别在于：

- 估计量所属的类不同。
- 风险不同。
- 惩罚项不同。
- 支持向量机：设 k 为正定核。

$$
\mathcal {F} = \left\{f = \sum_ {i = 1} ^ {+ \infty} \alpha_ {i} k (x _ {i}, \cdot): \alpha_ {i} \in \mathbb {R}, x _ {i} \in \mathcal {X} \right\}
$$

- Boosting：设 $\mathcal{G}$ 是 VC 维 $V$ 有限的简单分类器族。

$$
\mathcal {F} = \left\{f = \sum_ {i = 1} ^ {+ \infty} w _ {i} g _ {i}: w _ {i} \in \mathbb {R}, g _ {i} \in \mathcal {G} \right\}
$$

两种算法都构造函数的线性组合。

> **译注：** 若使用无限和定义函数类，需要另行规定收敛条件；这里只是原课件对函数空间的简写。

### SVM 的情形：回到拉格朗日表述 I

设

$$
f (x) = \sum_ {i = 1} ^ {n} \alpha_ {i} k (x _ {i}, x)
$$

$$
\| f \| _ {\mathcal {F}} = \sqrt {\sum_ {i , j} \alpha_ {i} \alpha_ {j} k (x _ {i} , x _ {j})}
$$

### 拉格朗日表述 I

$$
\min _ {f \in \mathcal {F}} \frac {1}{2} \| f \| _ {\mathcal {F}} ^ {2} + C \sum_ {i = 1} ^ {n} \xi_ {i}
$$

约束条件：

$$
\forall i = 1, \dots , n, \quad \xi_ {i} \geq \left(1 - y _ {i} \cdot f (x _ {i})\right) _ {+}
$$

设 $\varphi(x)=(1+x)_{+}$，称为 hinge loss（合页损失）。

### 惩罚风险的最小化

$$
\min _ {f \in \mathcal {F}} \frac {1}{2} \| f \| _ {\mathcal {F}} ^ {2} + C \sum_ {i = 1} ^ {n} \varphi (- y _ {i} f (x _ {i}))
$$

### 说明

- 这一表述对统计理论很重要。
- 对优化而言，它不如对偶表述方便。
- $\|f\|_{\mathcal{F}}$ 提供了对 $f$ 正则性的度量。
- 决策函数：

$$
f: \mathcal {X} \to \mathbb {R}
$$

- 分类器：

$$
g (x) = g _ {f} (x) = \operatorname{sgn} (f (x)) \in \{- 1, + 1 \}
$$

- 自然的准则：

$$
L (f) = \mathbb {P} \left\{Y \cdot f (X) <   0 \right\} = \mathbb {E} \left\{\mathbb {I} _ {[ Y \cdot f (X) <   0 ]} \right\}
$$

- 损失函数：$\varphi$ 凸、非负，并且满足 $\varphi(x) \geq \mathbb{I}_{\mathbb{R}_+}(x)$。
- 实用准则（$\varphi$ 风险）：

$$
\begin{array}{r l} A (f) & = \mathbb {E} \varphi (- Y f (X)) \\ & = \mathbb {E} \left[ \eta (X) \varphi (- f (X)) + (1 - \eta (X)) \varphi (f (X)) \right] \end{array}
$$

其中 $\eta(X)=\mathbb P\{Y=1\mid X=x\}$。

> **译注：** 原页等号左侧写 $\eta(X)$，右侧使用固定输入 x；定义应统一写成 $\eta(x)=\mathbb P(Y=1\mid X=x)$。

问题：最小化 A 是否等价于最小化 L？

仅有如下关系：$L(f) \leq A(f)...$。

![image](<Images/05_NLM/image_032.jpg>)

### 目标函数

- 泛函 $A$ 的极小点记为 $f^{*}$。
- 最小 $\varphi$ 风险：$A^{*} = \min_{f} A(f) = A(f^{*})$。
- 可以证明，$\operatorname{sgn}(f^{*}) = g^{*}$ 是最优分类器。
- 还可以证明，分类误差的超额风险 $L(f) - L^*$ 由 $A(f) - A^*$ 控制。

> **译注：** 分类校准结论需要对替代损失施加额外条件，不能仅由凸、非负、上界 0/1 损失推出。以下指数损失和 hinge 损失是具体例子；边界概率和并列最优情形还需单独处理。

- 例子：
- 指数损失（Boosting）。

$$
f ^ {*} (x) = \frac {1}{2} \log \left(\frac {\eta (x)}{1 - \eta (x)}\right)
$$

- 合页损失（SVM）。

$$
f ^ {*} (x) = \operatorname{sgn} (\eta (x) - 1 / 2) = g ^ {*} (x)
$$

- 可解释性。
- 强化学习。
- 将这些概念应用到其他问题：
- 从目标角度：例如偏好学习、评分、排序、异常检测、新颖性检测等。
- 从学习设定角度：在线学习、无监督学习、迁移学习、多任务学习、预算受限学习、主动学习等。
