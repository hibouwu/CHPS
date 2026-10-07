# 分类问题与参数方法：原课件忠实译本

> 正文按原课件顺序逐段翻译，不作摘要式压缩；例子、练习、重复正文、公式、图表及文献均保留。图中文字保留原图语言。原课件错误与必要辨析以独立“译注”标明。

[原 PDF](03_LMC.pdf) · [原文转换稿](03_LMC.md) · [逐块对应清单](Translation-audit/2026-09-28-coverage.json) · [课程目录](../README.md)

<details>
<summary>本讲目录（点击展开）</summary>

- [分类问题与参数方法](#section-01)
- [分类数据：例子](#section-02)
- [这些数据可以支持哪些决策？](#section-03)
- [分类数据的概率模型](#section-04)
- [分类问题的理论框架](#section-05)
- [评价准则：分类器的误差](#section-06)
- [分类中的过拟合（续）](#section-07)
- [复杂度调整](#section-08)
- [实践中的留出法](#section-09)
- [方法 1：线性判别分析（LDA）与二次判别分析（QDA）](#section-10)
- [线性判别分析（LDA）](#section-11)
- [线性判别分析（续）](#section-12)
- [二次判别分析（QDA）](#section-13)
- [方法 2：Fisher 判别分析（FDA）](#section-14)
- [方法 3：线性逻辑回归](#section-15)
- [生成式方法的局限](#section-16)
- [从分类到评分：ROC 曲线与 AUC](#section-17)
- [Neyman–Pearson 分类器](#section-18)
- [评分的最优解](#section-19)
- [实用准则：ROC 曲线下面积（AUC）](#section-20)
- [评分的性能度量](#section-21)
- [评分的性能度量](#section-22)
- [评分的性能度量](#section-23)
- [非参数线性判别算法](#section-24)
- [感知机算法（Rosenblatt，1958）](#section-25)
- [一般感知机算法](#section-26)
- [Novikoff 定理](#section-27)
- [场景 1：具有良好泛化能力的超平面](#section-28)
- [Karush–Kuhn–Tucker 条件](#section-29)
- [规范最优超平面](#section-30)

</details>

M2 CHPS

**数据科学与机器学习导论**

Nicolas Vayatis

<a id="section-01"></a>

## 分类问题与参数方法

<a id="section-02"></a>

## 分类数据：例子

### 医学诊断

- X：医学检查结果。
- $Y$：诊断。
- 如果患者健康，则 $Y = +1$；否则 $Y = -1$。

### 信用风险

- X：个人的社会经济数据。
- $Y$：违约指标。
- 如果借款人可靠，则 $Y = +1$；否则 $Y = -1$。

### 垃圾邮件识别

- X：邮件的描述特征。
- $Y$：邮件的状态。
- 如果邮件是垃圾邮件，则 $Y = +1$；否则 $Y = -1$。

<a id="section-03"></a>

## 这些数据可以支持哪些决策？

### 1. 分类

目标：预测新的标签 Y。

如果分类错误率低，就认为结果令人满意。

### 2. 评分

目标：将 X 排列成一个列表。

如果列表前端有许多 Y = +1 的对象，就认为结果令人满意。

1. 分类数据的概率模型。
2. 分类问题的理论框架。
3. 经典的参数化（线性）分类方法。
1. 判别分析（LDA/QDA）。
2. Fisher 判别分析（FDA）。
3. 线性逻辑回归。

### 4. 从分类到评分（定向筛选）：ROC 曲线与 AUC 面积

5. 感知机算法：线性且非参数！

<a id="classification-model"></a>

<a id="section-04"></a>

## 分类数据的概率模型

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

<a id="section-05"></a>

## 分类问题的理论框架

### 二分类问题

- 可用数据：$(x_1, y_1), \ldots, (x_n, y_n)$，$x_i \in \mathbb{R}^d$，$y_i \in \{-1, +1\}$。
- 问题：已知 x，预测标签 y。
- 要寻找：一个分类器 $g$：$\mathbb{R}^d \to \{-1, +1\}$。
- 问题：找到一个能够良好“泛化”的分类器 $g$。
- 思路：选择一个能够很好地“解释”数据、但又不过度解释的 $g$！
- 具体而言：通常先寻找决策函数 $f: \mathbb{R}^{d} \to \mathbb{R}$，再将其与分类器 $g = \text{sgn}(f)$ 对应。

<a id="section-06"></a>

## 评价准则：分类器的误差

- 给定一个观测 $x$，分类器 $g$ 作出预测 $g(x)$，将其与类别 $y$ 比较。

分类器的误差 = 被错误分类的观测所占比例。

$$
\hat {L} _ {n} (g) = \frac {1}{n} \sum_ {i = 1} ^ {n} \mathbb {I} _ {[ g (x _ {i}) \neq y _ {i} ]} = \frac {\# \{i : g (x _ {i}) \neq y _ {i} \}}{n}
$$

这个误差也称为训练误差。

- 如果分类器 $g$ 的训练误差低，就说它能够恰当地“解释”数据。
- 注意！如果只关注这类误差，就可能出现问题……

![image](<Images/03_LMC/image_001.jpg>)

![image](<Images/03_LMC/image_002.jpg>)

<a id="section-07"></a>

## 分类中的过拟合（续）

欠拟合与过拟合

负例；正例；新患者。

<a id="section-08"></a>

## 复杂度调整

![image](<Images/03_LMC/image_003.jpg>)

<a id="section-09"></a>

## 实践中的留出法

- 将可用数据分为两个子集：
- 训练集：$(X_1, Y_1), \ldots, (X_n, Y_n)$。
- 测试集：$(X_{n+1}, Y_{n+1}), \ldots, (X_{n+m}, Y_{n+m})$。
- 对任意分类器 $g$，测试误差 $\hat{L}_{m}^{\prime}(g) = \frac{1}{m}\sum_{j=1}^{m}\mathbb{I}_{[g(X_{n+j})\neq Y_{n+j}]}$ 是 $L(g)$ 的估计量（如果 $g$ 是学习得到的，可以对训练集取条件）。
- 更好的实践：使用交叉验证，使 $L(g)$ 的估计更稳健。

<a id="section-10"></a>

## 方法 1：线性判别分析（LDA）与二次判别分析（QDA）

### 回顾：多元高斯分布

### 多元高斯模型

- 与一元情形类似。

$$
\mathcal {N} (\underline {{{{x}}}}; \underline {{{{\mu}}}}, \Sigma) = \frac {1}{(2 \pi) ^ {d / 2}} | \Sigma | ^ {- 1 / 2} \exp \left\{- \frac {1}{2} (\underline {{{{x}}}} - \underline {{{{\mu}}}}) \Sigma^ {- 1} (\underline {{{{x}}}} - \underline {{{{\mu}}}}) ^ {T} \right\}
$$

![image](<Images/03_LMC/image_004.jpg>)

$$
\begin{array}{l} \mu = \text{长度为 d 的行向量} \\ \Sigma = \text{d×d 矩阵} \end{array}
$$

$|\Sigma| = \text{矩阵行列式}$

最大似然估计：

$$
\bar {\mu} = \frac {1}{m} \sum_ {j} x ^ {(j)}
$$

$$
\bar {\Sigma} = \frac {1}{m} \sum_ {j} (\underline {{x}} ^ {(j)} - \underline {{\mu}}) ^ {T} (\underline {{x}} ^ {(j)} - \underline {{\mu}})
$$

（对 d×d 矩阵取平均。）

> **译注：** 这里给出的是高斯均值与协方差的形式解。均值未知、协方差要求正定的非退化模型，需要中心化样本协方差正定才存在对应的最大似然解；样本不足或落在低维仿射子空间中时不能直接求逆。QDA 要逐类检查，LDA 检查合并类内散布矩阵。

### 回顾：二维高斯混合

![image](<Images/03_LMC/image_005.jpg>)

b

![image](<Images/03_LMC/image_006.jpg>)

### 假设：参数化高斯混合模型

- $X \in \mathbb{R}^d$，且 $Y \in \{1, \ldots, K\}$。
- 后验分布采用高斯参数形式。

$$
\mathbb {P} (X \mid Y = k) \sim \mathcal {N} (m _ {k}, \Sigma_ {k}), \quad \text{密度} f _ {k}
$$

> **译注：** 原页写“后验分布”，但式中是给定类别后的输入分布，即类条件分布；类别后验是下一式中的 $\eta_k(x)$。

- 第 $Y = k$ 类的混合参数为 $\pi_{k}$。
- 于是可以写出：

$$
\eta_ {k} (x) = \mathbb {P} (Y = k \mid X = x) = \frac {\pi_ {k} f _ {k} (x)}{\sum_ {j = 1} ^ {K} \pi_ {j} f _ {j} (x)}
$$

<a id="discriminant-analysis"></a>

<a id="section-11"></a>

## 线性判别分析（LDA）

- 假设 $\Sigma_{k} = \Sigma, \forall k$。
- 于是可以写出：

$$
\begin{array}{r l} \log \left(\frac {\eta_ {k} (x)}{\eta_ {j} (x)}\right) & = \frac {\pi_ {k} f _ {k} (x)}{\pi_ {j} f _ {j} (x)} \\ & = \log \left(\frac {f _ {k} (x)}{f _ {j} (x)}\right) + \log \left(\frac {\pi_ {k}}{\pi_ {j}}\right) \\ & = - \frac {1}{2} (m _ {k} + m _ {j}) ^ {T} \Sigma^ {- 1} (m _ {k} + m _ {j}) \\ & \quad + \log \left(\frac {\pi_ {k}}{\pi_ {j}}\right) + x ^ {T} \Sigma^ {- 1} (m _ {k} - m _ {j}) \end{array}
$$

> **译注：** 原页第一行右边漏了 log，第三行的均值二次项也有笔误。正确展开为 $\log\frac{\eta_k(x)}{\eta_j(x)}=x^T\Sigma^{-1}(m_k-m_j)-\tfrac12(m_k^T\Sigma^{-1}m_k-m_j^T\Sigma^{-1}m_j)+\log\frac{\pi_k}{\pi_j}$。原式保留于上方。

- 关于 x 的线性方程！

<a id="section-12"></a>

## 线性判别分析（续）

![image](<Images/03_LMC/image_007.jpg>)

<a id="section-13"></a>

## 二次判别分析（QDA）

- 矩阵 $\Sigma_{k}$、$\forall k$ 不同的情形。
- 此时得到如下判别函数：

$$
\delta_ {k} (x) = - \frac {1}{2} (x - m _ {k}) ^ {T} \Sigma_ {k} ^ {- 1} (x - m _ {k})
$$

$$
+ \log (\pi_ {k}) - \frac {1}{2} \log d e t (\Sigma_ {k})
$$

- 关于 $x!$ 的二次分界面。
- 在高维情况下，估计矩阵 $\Sigma_{k}$ 的代价很高。
- 那么，是带耦合项的 LDA，还是 QDA？
- 思路：通过插值对矩阵作正则化。

$$
\hat {\Sigma} _ {k} (\lambda) = \lambda \hat {\Sigma} _ {k} (\lambda) + (1 - \lambda) \hat {\Sigma}
$$

参见 Friedman（1989）。

- 围绕正则化与稀疏性的变体。

<a id="section-14"></a>

## 方法 2：Fisher 判别分析（FDA）

### Fisher 判别分析的原理

- 假设：对 $\mathcal{L}(X \mid Y)$ 考虑两个高斯分布。
- 启发式思路：考虑一个线性分隔面，使两个分布投影后的中心距离相对于投影总方差最大；投影方向取分隔面的法向量。

![image](<Images/03_LMC/image_008.jpg>)

![image](<Images/03_LMC/image_009.jpg>)

更形式化地说：对 i = 1,2 使用以下记号。

- 从高斯分布 $\mathcal{N}(\mu_i, \Sigma_i)$ 中采样得到二分类数据。
- 参数的经验估计量 $\hat{\mu}_{i}$、$\hat{\Sigma}_{i}$。
- 投影到向量 $u \in \mathbb{R}^d: m_i(u) = u^T \hat{\mu}_i$ 上的中心。
- 投影后观测的离散程度：

$$
\hat {S} _ {i} ^ {2} (u) = \sum_ {j: Y _ {j} = i} \left(u ^ {T} X _ {j} - m _ {i} (u)\right) ^ {2}
$$

- 对 $u \in \mathbb{R}^d$ 要最大化的准则：

$$
J (u) = \frac {(m _ {1} (u) - m _ {2} (u)) ^ {2}}{\hat {S} _ {1} ^ {2} (u) + \hat {S} _ {2} ^ {2} (u)} = \frac {u ^ {T} S _ {B} u}{u ^ {T} S _ {W} u}
$$

其中 $S_{B}$ 和 $S_{W}$ 分别可解释为类间散布矩阵与类内散布矩阵。

- 使用拉格朗日方法，通过求解以下特征值问题得到解：

$$
S _ {B} u = \lambda S _ {W} u
$$

如果 $S_{W}$ 满秩，则解有显式表达：

$$
u = S _ {W} ^ {- 1} \big (\hat {\mu} _ {1} - \hat {\mu} _ {2} \big)
$$

- 注意，方向 $u$ 与 PCA 得到的方向无关。

<a id="logistic-model"></a>

<a id="section-15"></a>

## 方法 3：线性逻辑回归

- 设 $Y\in\{1,\ldots,K\}$，$X\in\mathbb R^d$。
- 对 $k \in \{1, \ldots, K\}$，记 $\eta_k(x) = \mathbb{P}\{Y = k \mid X = x\}$。
- 假设 $\forall k$，存在 $\theta_k \in \mathbb{R}^d$，使得

$$
\log \left(\frac {\eta_ {k} (x)}{\eta_ {K} (x)}\right) = \theta_ {k} ^ {T} x
$$

- 或者写成：

$$
\eta_ {k} (x) = \frac {\exp (\theta_ {k} ^ {T} x)}{1 + \sum_ {j = 1} ^ {K - 1} \exp (\theta_ {j} ^ {T} x)}
$$

并且 $\theta_{K}=1$。

### 拟合逻辑回归模型

- 记 $\theta = (\theta_1, \ldots, \theta_{K-1})$ 和 $\eta_k(x) = p_k(x, \theta)$。
- 对数似然：

$$
\ell (\theta) = \sum_ {i = 1} ^ {n} \log p _ {k} (X _ {i}, \theta)
$$

- $K = 2$、$\theta \in \mathbb{R}^d$、$p(x, \theta) = p_1(x, \theta)$ 的情形。

$$
\begin{array}{l} \ell (\theta) = \sum_ {i = 1} ^ {n} \big (Y _ {i} \log p (X _ {i}, \theta) + (1 - Y _ {i}) \log (1 - p (X _ {i}, \theta)) \big) \\ = \sum_ {i = 1} ^ {n} \big (Y _ {i} \theta^ {T} X _ {i} - \log (1 + \exp (\theta^ {T} X _ {i})) \big) \end{array}
$$

- 得分方程：

$$
\frac {\partial \ell}{\partial \theta} (\theta) = \sum_ {i = 1} ^ {n} X _ {i} \big (Y _ {i} - p (X _ {i}, \theta) \big) = 0
$$

- Hessian 矩阵：

$$
H _ {\ell} (\theta) = - \sum_ {i = 1} ^ {n} X _ {i} X _ {i} ^ {T} p (X _ {i}, \theta) \big (1 - p (X _ {i}, \theta) \big)
$$

- Newton–Raphson 迭代格式：

$$
\theta_ {t + 1} = \theta_ {t} - (H _ {\ell} (\theta_ {t})) ^ {- 1} \frac {\partial \ell}{\partial \theta} (\theta_ {t})
$$

- 归结为加权最小二乘估计……

<a id="section-16"></a>

## 生成式方法的局限

> **译注：** 原课件使用这个标题，但前面介绍的逻辑回归属于判别式方法，不属于生成式方法。

- 参数统计模型：“所有模型都是错的”……
- 很强的建模先验：“……但有些模型是有用的”。
- 高斯框架。
- 线性模型。
- 维数灾难（参见 Bellman）。

<a id="scoring"></a>

<a id="section-17"></a>

## 从分类到评分：ROC 曲线与 AUC

- 分类误差的分解：

$$
L (g) = \mathbb {P} \left\{g (X) = + 1, Y = - 1 \right\} + \mathbb {P} \left\{g (X) = - 1, Y = + 1 \right\}
$$

- 假阳性率。

$$
\alpha (g) = \mathbb {P} \left\{g (X) = + 1 \mid Y = - 1 \right\}
$$

- 真阳性率。

$$
\beta (g) = \mathbb {P} \left\{g (X) = + 1 \mid Y = + 1 \right\}
$$

- 注意到：

$$
L (g) = \mathbb {P} \{Y \neq g (X) \} = (1 - p) \alpha (g) + p (1 - \beta (g))
$$

### α–β 图

- 对固定比例 $p$ 和固定分类误差 $L(g) = L$，有：

$$
\beta = \left(\frac {1 - p}{p}\right) \alpha + 1 - \frac {L}{p}
$$

![image](<Images/03_LMC/image_010.jpg>)

- 给定观测 $X$，检验

$$
H _ {0}: Y = - 1 \quad \text{对立假设} \quad H _ {1}: Y = + 1
$$

- 最优检验统计量（Neyman–Pearson）：

$$
T ^ {*} (X) = \frac {1 - p}{p} \cdot \frac {\eta (X)}{1 - \eta (X)}
$$

• $\alpha = \text{第一类错误率}$

- $\beta =$：检验功效。

<a id="section-18"></a>

## Neyman–Pearson 分类器

- 对固定的 $\alpha$，拒绝域为：

$$
R _ {\alpha} ^ {*} = \left\{x: \eta (x) > Q ^ {-} (\eta , \alpha) \right\}
$$

$$
Q^-(\eta,\alpha)=\mathcal L(\eta(X)\mid Y=-1)\text{ 的 }(1-\alpha)\text{ 分位数}.
$$

- 定义分类器：

$$
g _ {\alpha} ^ {*} (x) = 2 \mathbb {I} \left\{x \in R _ {\alpha} ^ {*} \right\} - 1
$$

- 一般有 $L(g_{\alpha}^{*}) > L^{*}$，除非 $Q^{-}(\eta, \alpha) = 1/2$。

> **译注：** 原句的“除非”过强：不同阈值若在有概率质量的区域产生相同决策，也可能达到相同的 Bayes 风险；离散评分的精确误报水平还可能需要阈值处随机化。

- 令 $\beta^{*}(\alpha) = \beta(g_{\alpha}^{*})$。

![image](<Images/03_LMC/image_011.jpg>)

### 记号：评分规则的性能

- 考虑一个检测器的响应 $s: \mathbb{R}^d \to \mathbb{R}$，即评分规则。
- 命中对应 $Y = +1$，报警对应 $\{s(X) \geq t\}$。
- 真阳性率与假阳性率：

$$
\begin{array}{l l} \beta (s, t) = & \mathbb {P} \left\{s (X) \geq t \mid Y = + 1 \right\} \quad (\text {TPR}) \to \max \\ \alpha (s, t) = & \mathbb {P} \left\{s (X) \geq t \mid Y = - 1 \right\} \quad (\text {FPR}) \to \min \end{array}
$$

- 关键点：需要权衡，因为

$$
\begin{array}{l l l l} \beta (s, t) \to 1 & \text{但} & \alpha (s, t) \to 1 & \text{当} t \to - \infty \\ \alpha (s, t) \to 0 & \text{但} & \beta (s, t) \to 0 & \text{当} t \to + \infty \end{array}
$$

### 理想 ROC 曲线

![image](<Images/03_LMC/image_012.jpg>)

![image](<Images/03_LMC/image_013.jpg>)

- 对固定的规则 $s: \mathbb{R}^d \to \mathbb{R}$。
- 评分规则 s 的 ROC 曲线：

$$
t \in \mathbb {R} \mapsto (\alpha_ {s} (t), \beta_ {s} (t))
$$

<a id="section-19"></a>

## 评分的最优解

- $X \in \mathbb{R}^d$：高维空间中的观测向量。
- $Y \in \{-1, +1\}$：二元诊断，即分类数据。
- 关键理论量（后验概率）：

$$
\eta (x) = \mathbb {P} \{Y = 1 \mid X = x \}, \quad \forall x \in \mathbb {R} ^ {d}
$$

- 最优评分规则：

$\Rightarrow$ $\eta$ 的递增变换。

<a id="section-20"></a>

## 实用准则：ROC 曲线下面积（AUC）

- 对任意评分规则 $s$，令：

$$
\begin{array}{l l} \text {AUC} (s) & = \int_ {0} ^ {1} \text {ROC} (s, \alpha) d \alpha \\ & = \mathbb {P} \{s (X) > s (X ^ {\prime}) | Y > Y ^ {\prime} \} \\ & \qquad + \frac {1}{2} \mathbb {P} \{s (X) = s (X ^ {\prime}) | Y > Y ^ {\prime} \} \end{array}
$$

其中 $(X, Y)$、$(X', Y')$ 独立同分布。

- 最大 AUC：

$$
\mathrm{AUC} ^ {*} = \mathrm{AUC} (\eta) = \frac {1}{2} + \frac {\mathbb {E} (| \eta (X) - \eta (X ^ {\prime}) |)}{4 p (1 - p)},
$$

- AUC 意义下的收敛对应于 ROC 曲线的 $L_{1}$ 收敛。

> **译注：** 这里应结合最优 ROC 包络理解面积差与 $L_1$ 差距。任意两条相交 ROC 曲线的 AUC 接近，不保证两条曲线接近。

### 曲线

- ROC 曲线。
- （精确率—召回率曲线。）
- （提升曲线。）

### 汇总指标

- AUC（全局度量）。
- 部分 AUC。

（Dodd 与 Pepe，2003。）

### 局部 AUC

（Clémençon 与 Vayatis，2007。）

![image](<Images/03_LMC/image_014.jpg>)

ROC 曲线。

### 曲线

- ROC 曲线。
- （精确率—召回率曲线。）
- （提升曲线。）

### 汇总指标

- AUC（全局度量）。
- 部分 AUC（Dodd 与 Pepe，2003）。

### 局部 AUC

（Clémençon 与 Vayatis，2007。）

![image](<Images/03_LMC/image_015.jpg>)

ROC 曲线。

<a id="section-21"></a>

## 评分的性能度量

### 曲线

- ROC 曲线。
- （精确率—召回率曲线。）
- （提升曲线。）

### 汇总指标

- AUC（全局度量）。
- 部分 AUC（Dodd 与 Pepe，2003）。
- 局部 AUC（Clémençon 与 Vayatis，2007）。

![image](<Images/03_LMC/image_016.jpg>)

部分 AUC。

<a id="section-22"></a>

## 评分的性能度量

### 曲线

- ROC 曲线。
- （精确率—召回率曲线。）
- （提升曲线。）

### 汇总指标

- AUC（全局度量）。
- 部分 AUC（Dodd 与 Pepe，2003）。
- 局部 AUC（Clémençon 与 Vayatis，2007）。

![image](<Images/03_LMC/image_017.jpg>)

部分 AUC 的不一致性。

<a id="section-23"></a>

## 评分的性能度量

### 曲线

- ROC 曲线。
- （精确率—召回率曲线。）
- （提升曲线。）

### 汇总指标

- AUC（全局度量）。
- 部分 AUC（Dodd 与 Pepe，2003）。
- 局部 AUC（Clémençon 与 Vayatis，2007）。

![image](<Images/03_LMC/image_018.jpg>)

局部 AUC。

<a id="section-24"></a>

## 非参数线性判别算法

1. 两个群体线性可分。
2. 两个群体近似线性可分。
3. 两个群体不能线性分离。

### 线性可分性

![image](<Images/03_LMC/image_019.jpg>)

场景 1

![image](<Images/03_LMC/image_020.jpg>)

场景 2

- 决策函数的形式：

$$
f (x) = b + <   \beta , x >
$$

其中 $b\in \mathbb{R},\beta \in \mathbb{R}^d$。

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

其中 $x_{0} \in H$。

![image](<Images/03_LMC/image_021.jpg>)

二维训练集的分隔超平面 $(\boldsymbol{w}, b) \in \mathbb{R}^{n} \times \mathbb{R}$。

注意！这里 $w = \beta$……

<a id="section-25"></a>

## 感知机算法（Rosenblatt，1958）

### 简化版本：b = 0

生成参数 $\beta$ 的取值序列 $\beta_{0},\ldots,\beta_{n}$。

1. 初始化：$\beta_{0} = 0$。
2. 第 i 步：考虑数据对 $(x_{i}, y_{i})$，检查它是否被正确分类。

$$
\beta_ {i} = \left\{ \begin{array}{l l} \beta_ {i - 1} & \text{若} y _ {i} \cdot <   \beta_ {i - 1}, x _ {i} > > 0 \\ \beta_ {i - 1} + y _ {i} x _ {i} & \text{若} y _ {i} \cdot <   \beta_ {i - 1}, x _ {i} > \leq 0 \end{array} \right.
$$

<a id="section-26"></a>

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

<a id="section-27"></a>

## Novikoff 定理

如果两个群体线性可分，则感知机算法在有限的 $T \leq n$ 步内收敛，其中：

$$
T \leq \frac {2 R ^ {2}}{M ^ {2}}
$$

这里，对某个分隔面 $H^*$，有 $M = \min_{1 \leq i \leq n} \{y_i d(x_i, H^*)\}$。

> **译注：** 原课件写出的 $T\le n$ 不普遍成立。标准感知机界按错误更新次数计数，使用同一增广空间中的样本半径和分隔间隔；不能直接把原空间的几何距离与增广间隔混用。

- 感知机的缺点：泛化能力差。
- 感知机的优点：序贯（在线）算法。

<a id="maximum-margin"></a>

<a id="section-28"></a>

## 场景 1：具有良好泛化能力的超平面

问题：是否存在与每个群体的距离都尽可能大的超平面？

![image](<Images/03_LMC/image_022.jpg>)

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

![image](<Images/03_LMC/image_023.jpg>)

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

<a id="section-29"></a>

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

> **译注：** 由等式确定截距时应选取满足 $0<\widehat\alpha_j<C$ 的自由支持向量；任取非零系数的支持向量不一定满足边界等式。

<a id="section-30"></a>

## 规范最优超平面

![image](<Images/03_LMC/image_024.jpg>)

⇒ SVM 的稀疏表示。

- 无监督分类（没有标签）。
- 其他分类算法：非参数、非线性。
- 复杂度调整与优化问题的正则化。
