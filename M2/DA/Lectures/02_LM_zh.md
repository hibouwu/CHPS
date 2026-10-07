# 线性模型与稀疏性：原课件忠实译本

> 正文按原课件顺序逐段翻译，不作摘要式压缩；例子、练习、重复正文、公式、图表及文献均保留。图中文字保留原图语言。原课件错误与必要辨析以独立“译注”标明。

[原 PDF](02_LM.pdf) · [原文转换稿](02_LM.md) · [逐块对应清单](Translation-audit/2026-09-28-coverage.json) · [课程目录](../README.md)

<details>
<summary>本讲目录（点击展开）</summary>

- [线性模型与稀疏性](#section-01)
- [监督机器学习：机器学习中的偏差—方差分解](#section-02)
- [统计学线性模型回顾：回归情形](#section-03)
- [线性回归中的最小二乘估计](#section-04)
- [线性模型中最小二乘计算的证明](#section-05)
- [基于链式法则的另一种证明](#section-06)
- [所有学生都（应该）知道的内容：回归中的偏差—方差权衡](#section-07)
- [机器学习如何接续线性回归](#section-08)
- [从经典统计到机器学习](#section-09)
- [高维插曲：一个令人意外的事实](#section-10)
- [从经典统计到机器学习：处理高维问题](#section-11)
- [对线性回归而言，“高维”意味着什么](#section-12)
- [A. 稀疏性与线性模型：调整模型维度](#section-13)
- [稀疏线性回归模型](#section-14)
- [两种表述：约束优化与惩罚优化](#section-15)
- [稀疏性与线性模型：模型选择](#section-16)
- [线性模型中的模型选择](#section-17)
- [线性模型中的模型选择](#section-18)
- [选读材料：赤池信息准则的推导](#section-19)
- [高维情况下的 AIC](#section-20)
- [A. 稀疏性与线性模型：从数理统计到优化](#section-21)
- [线性模型的 LASSO：从 $\ell _ { 0 }$ 到 $\ell _ { 1 }$](#section-22)
- [机器学习算法之“母”：惩罚优化](#section-23)
- [A. 稀疏性与线性模型：结构化稀疏性](#section-24)
- [A. 稀疏性与线性模型：岭回归](#section-25)
- [统计中的不适定问题：高维最小二乘回归](#section-26)
- [统计中最早的正则化方法：岭回归](#section-27)
- [岭回归估计量的推导](#section-28)
- [对偶优化问题：表述与 KKT 条件](#section-29)
- [对偶优化问题：求解](#section-30)
- [对偶优化问题：结果的解释](#section-31)
- [Elastic Net：兼得 LASSO 与 Ridge 的优点？](#section-32)
- [LASSO 与 Elastic Net：正则化路径比较](#section-33)
- [超参数调整：交叉验证](#section-34)
- [练习：比较三种惩罚](#section-35)
- [B. 估计非线性函数](#section-36)
- [核的魔力：核岭回归](#section-37)
- [基本核的例子](#section-38)
- [核机器学习估计：可行吗？](#section-39)
- [C. 推广：应用于其他估计问题](#section-40)

</details>

**数据科学与机器学习导论**

Nicolas Vayatis

<a id="section-01"></a>

## 线性模型与稀疏性

<a id="section-02"></a>

## 监督机器学习：机器学习中的偏差—方差分解

### 一般设定与记号

- 学习目标：最优决策函数 $h ^ { \ast } : \mathcal { X }  \mathcal { V }$。$\mathcal { X } \mathrm { : }$ 是定义域集合，Y 是标签集合。
- 学习的输入：
- 训练数据：一组带标签的数据

$$
D _ {n} = \{(X _ {1}, Y _ {1}), \dots , (X _ {n}, Y _ {n}) \}
$$

其大小为 n，其中各 $( X , Y ) ^ { \prime } s$ 属于 $\mathcal { X } \times \mathcal { V }$。

- 假设空间：候选决策函数 $h : \mathcal { X }  \mathcal { Y }$ 的集合 $\mathcal { H }$。
- 学习的输出：利用训练数据 $D _ { n }$ 估计得到、位于假设空间 $\mathcal { H }$ 中的经验决策函数 $\widehat { h }$。
- $\mathcal { H } \mathrm { : }$ 中的参照：该类中的最佳决策函数 $\bar { h }$（数据越多，$\widehat { h }$ 越接近 $\bar { h } )$）。

### 机器学习中的关键权衡

- 对任意决策函数 h，用 $L ( h )$ 表示其误差度量。
- 有 $L ( \bar { h } ) = \operatorname* { i n f } _ { \mathcal { H } } L$，以及 $L ( h ^ { * } ) = \mathsf { i n f } L$。
- 对任意输出 $\widehat { h }$，误差具有如下偏差—方差类型的分解：

$$
L (\widehat {h}) - L (h ^ {*}) = \underbrace {L (\widehat {h}) - L (\bar {h})} _ {\text{估计误差（随机）}} + \underbrace {L (\bar {h}) - L (h ^ {*})} _ {\text{近似误差（确定性）}}
$$

假设类 H

![image](<Images/02_LM/image_001.jpg>)

### 关于近似误差

Cybenko（1989）：一个具有 Stone–Weierstrass 风格的稠密性结果，表明 sigmoid 与线性函数复合后所得函数的线性组合，在 d 维单位立方体上的连续函数空间中，关于上确界范数稠密。

- Barron（1994）：近似误差界包含一个刻画目标函数光滑程度的参数。
- 回归设定下这一问题的研究状况：
  - 对核方法：Smale（2003）、Steinwart（2008）的工作提供了完整理论。
  - 对深度学习：Grohs、Perekrestenko、Elbrächter 和 Bölcskei（2019）的近期工作。
- 在分类设定下，这是一个困难的问题，仍有待解决……

<a id="section-03"></a>

## 统计学线性模型回顾：回归情形

- 学习目标：$h ^ { * } : \mathbb { R } ^ { d }  \mathbb { R }$。
- 观测：独立同分布的随机变量对 $( X _ { i } , Y _ { i } ) \in \mathbb { R } ^ { d } \times \mathbb { R }$。

$$
Y _ {i} = h ^ {*} (X _ {i}) + \varepsilon_ {i}, \quad i = 1, \dots , n
$$

其中 $\varepsilon _ { i }$ 是与 $X$ 独立的随机噪声变量。

- 下面使用如下向量记法：

$$
\mathbf {Y} = \mathbf {h} ^ {*} + \varepsilon
$$

其中三项都属于 $\mathbb { R } ^ { n }$。

- $\mathbb { R } ^ { n }$ 中的元素：

$$
\mathbf {Y} = \left(Y _ {1}, \dots , Y _ {n}\right) ^ {T},
$$

$$
\varepsilon = \left(\varepsilon_ {1}, \dots , \varepsilon_ {n}\right) ^ {T}
$$

- 像向量：对任意 $h \in \mathcal H$，用粗体表示

$$
\mathbf {h} = \left(h (X _ {1}), \dots , h (X _ {n})\right) ^ {T}
$$

- 数据点经 $\mathcal { H }$ 中的函数映射后得到的像集合为

$$
\mathcal {H} (X) = \left\{\mathbf {h} = \left(h \left(X _ {1}\right), \dots , h \left(X _ {n}\right)\right) ^ {T},: h \in \mathcal {H} \right\}
$$

- $\mathbb { R } ^ { n }$ 中的范数：

$$
\forall u = \left(u _ {1}, \ldots , u _ {n}\right) ^ {T} \in \mathbb {R} ^ {n}, \| u \| ^ {2} = \sum_ {i = 1} ^ {n} u _ {i} ^ {2}
$$

- 最小二乘估计（LSE）的定义：

$$
\widehat {\mathbf {h}} _ {\mathbf {n}} = \underset {\mathbf {h} \in \mathcal {H} (X)} {\arg \min} \frac {1}{n} \| \mathbf {Y} - \mathbf {h} \| ^ {2}
$$

其中 ${ \mathcal { H } } ( X ) = \{ \boldsymbol { \mathsf { h } } = ( h ( X _ { 1 } ) , \ldots , h ( X _ { n } ) ) ^ { T } , : h \in { \mathcal { H } } \}$。

- 假设线性模型为高斯模型，即噪声变量独立同分布、服从均值为零且方差固定并已知的高斯分布，则最小二乘估计也对应最大似然估计。
- 假设空间 $\mathcal { H }$ 是秩为 $d$ 的线性函数类。
- 噪声向量 $\boldsymbol { \varepsilon } = ( \varepsilon _ { 1 } , \ldots , \varepsilon _ { n } ) ^ { T }$ 是 $\mathbb { R } ^ { n }$ 中服从分布 ${ \mathcal { N } } _ { n } ( 0 , \sigma ^ { 2 } I _ { n } )$ 的高斯随机向量。

记号：$\boldsymbol { x } = ( \boldsymbol { x } ^ { ( 1 ) } , \ldots , \boldsymbol { x } ^ { ( d ) } ) ^ { T } \in \mathbb { R } ^ { d }$。

- 线性回归：$\begin{array} { r } { h ( x ) = \sum _ { k = 1 } ^ { d } \beta _ { k } x ^ { ( k ) } } \end{array}$。
- 基／框架展开（Fourier、样条、小波等）。
- 加性模型：$h ( x ) = \sum _ { k = 1 } ^ { d } f _ { k } ( x ^ { ( k ) } )$。
- 分段常数回归（考虑分段点）。

<a id="least-squares"></a>

<a id="section-04"></a>

## 线性回归中的最小二乘估计

- 用 $\pmb { \mathsf { X } } \in \mathbb { R } ^ { n \times d }$ 表示数据矩阵，$\boldsymbol { \beta } \in \mathbb { R } ^ { d }$ 表示待估计参数。
- 假设：X 满秩，其秩等于 d，并假设 $d \leq n$。
- 最小二乘估计的定义：$\begin{array} { r } { \widehat { \beta } _ { \mathfrak { n } } = \arg \min _ { \beta \in \mathbb { R } ^ { d } } \frac { 1 } { n } \| \pmb { \mathsf { Y } } - \pmb { \mathsf { X } } \beta \| ^ { 2 } } \end{array}$。
- 最小二乘估计：$\widehat { \mathbf { h } } _ { \mathbf { n } } = \mathbf { X } \widehat { \beta } _ { \mathbf { n } } = \mathbf { X } ( \mathbf { X } ^ { T } \mathbf { X } ) ^ { - 1 } \mathbf { X } ^ { T } \mathbf { Y } = \widehat { \Pi } \mathbf { Y }$。

![image](<Images/02_LM/image_002.jpg>)

<a id="section-05"></a>

## 线性模型中最小二乘计算的证明

$$
\widehat {\beta} _ {\mathbf {n}} = \underset {\beta \in \mathbb {R} ^ {d}} {\arg \min} R (\beta) \text{其中} R (\beta) = \frac {1}{n} \| \mathbf {Y} - \mathbf {X} \beta \| ^ {2}
$$

- 计算梯度：

$$
\frac {d}{d \beta} \left((\mathbf {Y} - \mathbf {X} \beta) ^ {T} (\mathbf {Y} - \mathbf {X} \beta)\right) = - 2 \mathbf {Y} ^ {T} \mathbf {X} + 2 \beta^ {T} \mathbf {X} ^ {T} \mathbf {X} \in \mathbb {R} ^ {1 \times d}
$$

- 凸函数极小点的一阶条件：

$$
\mathbf {Y} ^ {T} + \beta^ {T} \mathbf {X} ^ {T} \mathbf {X} = 0
$$

> **译注：** 原课件该行漏了 $\mathbf Y^T$ 后的 $\mathbf X$。一阶条件应为 $-\mathbf Y^T\mathbf X+\beta^T\mathbf X^T\mathbf X=0$。

- 最终结果：$\widehat { \beta } _ { \mathfrak { n } } = ( \mathsf { X } ^ { T } \mathsf { X } ) ^ { - 1 } \mathsf { X } ^ { T } \mathsf { Y }$。

<a id="section-06"></a>

## 基于链式法则的另一种证明

- 设 $R ( \beta ) = \ell ( e ( \beta ) )$，其中 $\ell ( e ) = \| e \| ^ { 2 }$，且 $\boldsymbol { e } ( \beta ) = \boldsymbol { \mathsf { Y } } - \boldsymbol { \mathsf { X } } \beta$。
- 链式法则：$\frac { d R } { d \beta } = \frac { \partial \ell } { \partial e } \frac { \partial e } { \partial \beta }$，其中第 $j \mathrm { - t h }$ 个元素为：

$$
\frac {d R}{d \beta} [ j ] = \sum_ {k = 1} ^ {n} \frac {\partial \ell}{\partial e} [ k ] \frac {\partial e}{\partial \beta} [ k, j ]
$$

- 注意：$\frac { \partial \ell } { \partial e } = 2 e ^ { T } \in \mathbb { R } ^ { 1 \times n }$，且 $\frac { \partial e } { \partial \beta } = - { \pmb X } \in \mathbb { R } ^ { n \times d }$。
- 最后得到：$\frac{dR}{d\beta}=-2e^T\mathbf X=-2(\mathbf Y-\mathbf X\beta)^T\mathbf X$。

<a id="regression-risk"></a>

<a id="section-07"></a>

## 所有学生都（应该）知道的内容：回归中的偏差—方差权衡

- 模型：$\pmb { \mathsf { Y } } = \pmb { \mathsf { h } } ^ { * } + \varepsilon \in \mathbb { R } ^ { n }$。
- 最小二乘估计的计算：$\widehat { \mathbf { h } } _ { \mathbf { n } } = \widehat { \Pi } \mathbf { Y }$，其中 $\widehat { \Pi } = \pmb { \mathsf { X } } ( \pmb { \mathsf { X } } ^ { T } \pmb { \mathsf { X } } ) ^ { - 1 } \pmb { \mathsf { X } } ^ { T }$。
- 一种风险的定义：

$$
L (\widehat {\mathbf {h}} _ {\mathbf {n}}) = \frac {1}{n} \mathbb {E} \big (\| \mathbf {h} ^ {*} - \widehat {\mathbf {h}} _ {\mathbf {n}} \| ^ {2} \big)
$$

### 偏差—方差分解（1/2）：推导

- 首先注意到 $\widehat { \mathbf { h } } _ { \mathbf { n } } = \widehat { \Pi } \mathbf { Y } = \widehat { \Pi } ( \mathbf { h } ^ { * } + \varepsilon )$，于是

$$
\mathbf {h} ^ {*} - \widehat {\mathbf {h}} _ {\mathfrak {n}} = (I _ {n} - \widehat {\Pi}) \mathbf {h} ^ {*} - \widehat {\Pi} \varepsilon
$$

- 注意，$\widehat { \Pi } : \mathbb { R } ^ { n } \to \mathbb { R } ^ { n }$ 是到 $\mathcal { H } ( X )$ 上的正交投影。

$$
\widehat {\Pi} \circ \widehat {\Pi} = \widehat {\Pi}
$$

- 由于 $I _ { n } - { \widehat { \Pi } }$ 和 $\widehat { \Pi } .$ 的像空间正交：

$$
\begin{array}{r} L (\widehat {h} _ {n}) = \frac {1}{n} \mathbb {E} \big (\| \mathbf {h} ^ {*} - \widehat {\mathbf {h}} _ {\mathbf {n}} \| ^ {2} \big) \\ = \frac {1}{n} \mathbb {E} \big (\| (I _ {n} - \widehat {\Pi}) \mathbf {h} ^ {*} \| ^ {2} + \| \widehat {\Pi} \varepsilon \| ^ {2} \big) \end{array}
$$

### 偏差—方差分解（2/2）：结果

- 利用一个额外的技术结果（见下一页）：

$$
\begin{array}{r l} & L (\widehat {h} _ {n}) = \frac {1}{n} \mathbb {E} \big (\| \mathbf {h} ^ {*} - \widehat {\mathbf {h}} _ {\mathbf {n}} \| ^ {2} \big) \\ & \quad = \frac {1}{n} \mathbb {E} \big (\| (I _ {n} - \widehat {\Pi}) \mathbf {h} ^ {*} \| ^ {2} + \| \widehat {\Pi} \varepsilon \| ^ {2} \big) \\ & \quad = \underbrace {\frac {1}{n} \mathbb {E} \big (\| (I _ {n} - \widehat {\Pi}) \mathbf {h} ^ {*} \| ^ {2} \big)} _ {\text{偏差}} + \underbrace {\sigma^ {2} \frac {d}{n}} _ {\text{方差}} \end{array}
$$

- 用于模型选择，例如 AIC，即 Akaike Information Criterion（赤池信息准则）。

### d/n 项的解释

高斯随机向量投影的范数性质：

- 假设 $\mathbf { Z }$ 是 $\mathbb { R } ^ { n }$ 中服从 $ { \mathcal { N } _ { n } } ( 0 ,  { I _ { n } } )$ 的高斯随机向量，H 是 $\mathbb { R } ^ { n }$ 的线性子空间，$\Pi : \mathbb { R } ^ { n }  \mathbb { R } ^ { n }$ 是到 $\mathcal { H }$ 的线性投影。
- 则随机向量 $\Pi _ { \mathcal { H } } \mathbf { Z }$ 在 $\mathbb { R } ^ { n }$ 上服从高斯分布 $\mathcal { N } _ { n } ( 0 , \Pi )$（高斯随机向量的线性变换仍为高斯随机向量）。
- 此外，$\|\Pi Z\|^2$ 服从卡方分布，并且

$$
\mathbb {E} (\| \Pi \mathbf {Z} \| ^ {2}) = \dim (\mathcal {H})
$$

> **译注：** 上述性质要求正交投影。若投影子空间维度为 r，则平方范数服从自由度为 r 的卡方分布。

<a id="section-08"></a>

## 机器学习如何接续线性回归

1. 如果噪声不是加性的，会怎样？回归以外的任务呢？
2. 从线性模型到非线性模型。
3. 在非线性模型中，什么量替代维度 d 来衡量复杂度？
4. d/n 的速率对更大的假设类是否也具有代表性？如果 d 大于 n 呢？

<a id="section-09"></a>

## 从经典统计到机器学习

- 处理高维模型：

$$
d \gg 1, d \gg n
$$

- 重新审视维度：

参数个数与函数集合复杂度的比较。

<a id="section-10"></a>

## 高维插曲：一个令人意外的事实

![image](<Images/02_LM/image_003.jpg>)

99%

- 外壳与总体积之比：

$$
\frac {v o l (B _ {d} (0 , 1) - B _ {d} (0 , 1 - \varepsilon))}{v o l (B _ {d} (0 , 1))} = 1 - (1 - \varepsilon) ^ {d} \rightarrow 1 \text{当} d \rightarrow \infty
$$

### 综述性观点文章

D. Donoho（2000），High Dimensional Data Analysis: The Curses and Blessings of Dimensionality（高维数据分析：维度的诅咒与馈赠）。

### 数学著作

Roman Vershynin（2018），High-Dimensional Probability（高维概率）。

<a id="section-11"></a>

## 从经典统计到机器学习：处理高维问题

A. 稀疏性与线性模型。

B. 估计非线性函数。

C. 推广。

<a id="section-12"></a>

## 对线性回归而言，“高维”意味着什么

- 到目前为止，假设 $n \geq d$ 且 $( \pmb { \mathsf { X } } ) = d$。
- 当 d 增大时，可能或将会出现两种情况：
- 计算逆矩阵 $( { \pmb X } ^ { T } { \pmb X } ) ^ { - 1 }$ 时不稳定。
- 数据矩阵 X 秩亏。
- 秩亏情形（但仍有 $n \geq d )$）：
- 最小二乘问题存在多个解……
- 在投影矩阵中使用 Moore–Penrose 伪逆来代替 $( { \pmb X } ^ { T } { \pmb X } ) ^ { - 1 }$，可得到一个最小二乘估计。
- 这个最小二乘估计是使 $\ell _ { 2 } { \mathrm { - } } \mathsf { n o r m }$ 最小的解。
- 对不稳定性的补救：使用（岭）正则化……

<a id="section-13"></a>

## A. 稀疏性与线性模型：调整模型维度

- 向量记号：

响应向量 $\mathbf { Y } \in \mathbb { R } ^ { n }$，输入数据矩阵 $\textsf { X } ( { \mathsf { s i z e } } \ n \times d )$。

- 以向量形式表示的线性模型：

$$
\mathbf {Y} = \mathbf {X} \boldsymbol {\beta} ^ {*} + \varepsilon
$$

其中 ε 是均值为零、与 X 独立的随机噪声向量。

<a id="section-14"></a>

## 稀疏线性回归模型

- 直觉：如果模型中的某些变量不提供信息，但我们不知道具体是哪些变量，会怎样？
- 稀疏性假设：设真实参数 $\beta ^ { * }$ 仅涉及一部分变量，这个变量子集称为支撑集。

$$
m ^ {*} = \{j: \beta_ {j} ^ {*} \neq 0 \} \subset \{1, \dots , d \}
$$

任意 β 的 $\ell _ { 0 }$“范数”：$\| \beta \| _ { 0 } = \sum _ { j = 1 } ^ { d } \mathbb { I } \{ \beta _ { i } \neq 0 \}$。

<a id="section-15"></a>

## 两种表述：约束优化与惩罚优化

1. Ivanov 表述：在 $0$ 与 min $\{ n , d \}$ 之间选取 k。

$$
\min _ {\beta \in \mathbb {R} ^ {d}} \| \mathbf {Y} - \mathbf {X} \beta \| _ {2} ^ {2} \quad \text{满足} \| \beta \| _ {0} \leq k
$$

2. Tikhonov 表述：取 $\lambda > 0$。

$$
\min _ {\beta \in \mathbb {R} ^ {d}} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| _ {2} ^ {2} + \lambda \| \beta \| _ {0} \right\}
$$

- Tikhonov 表述看起来是 Ivanov 表述的拉格朗日形式。
- 但由于 $\ell _ { 0 }$ 范数缺乏光滑性，这里的两种表述并不等价。

> **译注：** 原文将不等价归因于“不光滑”，这个归因不充分。这里的关键是非凸性及离散的支撑选择；非光滑的凸问题在适当条件下仍可以建立约束形式与惩罚形式的对应。

- 带 $\ell _ { 0 }$ 约束的 Ivanov 表述称为最佳子集选择问题。已有基于启发式的算法，例如前向逐步回归，在 $k \simeq 3 5$ 以内效果尚可。近期进展：参见 Bertsimas 等（2016）的混合整数优化（MIO）表述。
- 从现在起重点讨论 Tikhonov 正则化。

<a id="section-16"></a>

## 稀疏性与线性模型：模型选择

### 建立联系：Tikhonov 惩罚与方差

回顾：

- 带 $\ell _ { 0 }$ 惩罚的 Tikhonov 表述：取 $\lambda > 0$。

$$
\min _ {\beta \in \mathbb {R} ^ {d}} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| _ {2} ^ {2} + \lambda \| \beta \| _ {0} \right\}\tag{1}
$$

- 最小二乘估计 ${ \widehat { \beta } } \mathbf { : }$ 的误差偏差—方差分解：

$$
\frac {1}{n} \mathbb {E} \big (\| \mathbf {X} \beta^ {*} - \mathbf {X} \widehat {\beta_ {\mathbf {n}}} \| ^ {2} \big) \simeq \text{偏差} + \sigma^ {2} \frac {d}{n}\tag{2}
$$

其中 d 是数据维度，$\sigma ^ { 2 }$ 是高斯噪声的方差。

现在的问题：偏差—方差分解（2）能否解释（1）？这个惩罚项是否正确？

<a id="section-17"></a>

## 线性模型中的模型选择

- 模型：$\pmb { \gamma } = \pmb { \mu } _ { \ b { \mu } } + \varepsilon$。
- 考虑 $\beta ^ { * }$ 的一个模型：它由 $\{ 1 , \ldots , d \}$ 的索引子集 m 给出。
- 例子：在维度 $d = 3$ 下，有：
- 1 个大小为 $| m | = 0 ;$ 的模型：常数模型。
- 3 个大小为 $| m | = 1 ; \{ 1 \} , \{ 2 \} , \{ 3 \}$ 的模型。
- 3 个大小为 $| m | = 2 \colon \{ 1 , 2 \} , \{ 2 , 3 \} , \{ 1 , 3 \}$ 的模型。
- 1 个大小为 $| m | = 3 \colon \{ 1 , 2 , 3 \}$ 的模型。

可能有 8 个版本的最小二乘估计，称为约束最小二乘估计（$| m | = 3$ 的情形除外，它没有约束）。

<a id="section-18"></a>

## 线性模型中的模型选择

- 考虑索引 $\{ 1 , \ldots , d \}$ 中变量子集 m 的集合 $\mathcal { M }$，这样的集合 m 共有 $2 ^ { d }$ 个。
- 对每个 $m \in { \mathcal { M } }$，有一个维度为 $| m |$ 的标准线性回归模型。换言之，对那些 $j \notin m _ { \cdot }$，有 $\theta _ { j } ^ { * } = 0$。
- 用 $\mathsf { X } _ { m }$ 表示 X 的一个大小为 $n \times | m |$ 的子矩阵，它只包含索引属于 m 的列。
- 对每个模型 $m \in { \mathcal { M } }$，计算约束最小二乘估计 $\widehat { \theta } _ { n } ^ { ( m ) } = ( \mathsf { X } _ { m } ^ { T } \mathsf { X } _ { m } ) ^ { - 1 } \mathsf { X } _ { m } ^ { T } \mathsf { Y } \in \mathbb { R } ^ { | m | }$。
- 最终估计量是在所有 $m \in { \mathcal { M } }$ 上的 ${ \widehat { \theta } } _ { n } ^ { ( m ) }$ 中选出的“最佳”估计量。
- 用 $\mathsf { X } _ { m }$ 表示大小为 $n \times | m |$ 的数据矩阵。
- 预测器的风险：$r _ { m } = \frac { 1 } { n } \mathbb { E } \big ( \| \mathbf { X } \theta ^ { * } - \mathbf { X } _ { m } \widehat { \theta } _ { n } ^ { ( m ) } \| ^ { 2 } \big )$。
- 理论上的最佳估计量（称为预言机）：

$$
\widehat {\theta} _ {n} ^ {(\overline {{m}})} \quad \text{其中} \quad \overline {{m}} = \underset {m \in \mathcal {M}} {\arg \min} r _ {m}
$$

- 使用赤池信息准则（AIC）的惩罚最小二乘：

$$
\widehat {m} = \underset {m \in \mathcal {M}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} \| ^ {2} + 2 | m | \sigma^ {2} \right\}
$$

（假设 $\sigma ^ { 2 }$ 已知，则可由数据计算。）

<a id="section-19"></a>

## 选读材料：赤池信息准则的推导

### 线性回归中的最小二乘估计

- 用 $\mathsf { X } _ { m }$ 表示数据矩阵 $( n \times | m | )$，用 ${ \widehat { \theta } } _ { n } ^ { ( m ) }$ 表示最小二乘估计。
- 预测向量：$\mathsf { X } _ { m } \widehat { \theta } _ { n } ^ { ( m ) } = \mathsf { X } _ { m } ( \mathsf { X } _ { m } ^ { T } \mathsf { X } _ { m } ) ^ { - 1 } \mathsf { X } _ { m } ^ { T } \mathsf { Y } = \widehat { \Pi } _ { m } \mathsf { Y }$。

![image](<Images/02_LM/image_004.jpg>)

### 偏差—方差分解（1/2）：推导

- 注意，$\widehat { \Pi } _ { m } : \mathbb { R } ^ { n }  \mathbb { R } ^ { n }$ 是到 m 中各方向所张成空间的正交投影：

$$
\widehat {\Pi} _ {m} \circ \widehat {\Pi} _ {m} = \widehat {\Pi} _ {m}
$$

- 有 $\begin{array} { r } { \pmb { \chi } _ { m } \widehat { \theta } _ { n } ^ { ( m ) } = \widehat { \Pi } _ { m } \pmb { \Upsilon } = \widehat { \Pi } _ { m } ( \pmb { \Upsilon } \theta ^ { \ast } + \pmb { \varepsilon } ) } \end{array}$，于是

$$
\mathbf {X} \theta^ {*} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} = (I _ {n} - \widehat {\Pi} _ {m}) \mathbf {X} \theta^ {*} - \widehat {\Pi} _ {m} \varepsilon
$$

- 投影算子的性质：$I _ { n } - \widehat { \Pi }$ 和 $\widehat { \Pi }$ 的像空间正交。
- 因此：

$$
\begin{array}{r l} {r _ {m}} & {= \frac {1}{n} \mathbb {E} \left(\| (I _ {n} - \widehat {\Pi} _ {m}) \mathbf {X} \theta^ {*} \| ^ {2} + \| \widehat {\Pi} _ {m} \varepsilon \| ^ {2}\right)} \\ & {= \frac {1}{n} \mathbb {E} \left(\| (I _ {n} - \widehat {\Pi} _ {m}) \mathbf {X} \theta^ {*} \| ^ {2}\right) + \sigma^ {2} \frac {| m |}{n}} \end{array}
$$

因为 $\| \widehat { \Pi } _ { m } \varepsilon \| ^ { 2 }$ 服从自由度为 $| m |$ 的卡方分布（多元高斯向量投影的性质）。

### 赤池信息准则（1/2）：推导

- 类似地，可以推导出：

$$
\frac {1}{n} \mathbb {E} \big (\| \mathbf {Y} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} \| ^ {2} \big) = \frac {1}{n} \mathbb {E} \big (\| (I _ {n} - \widehat {\Pi} _ {m}) \mathbf {X} \theta^ {*} \| ^ {2} \big) + \sigma^ {2} \frac {(n - | m |)}{n}
$$

事实上，$\begin{array} { r } { \mathsf { \pmb { Y } } - \mathsf { \pmb { X } } _ { m } \widehat { \theta } _ { n } ^ { ( m ) } = \big ( I _ { n } - \widehat { \Pi } _ { m } \big ) ( \mathsf { \pmb { X } } \theta ^ { * } + \varepsilon ) } \end{array}$，且 $\| I _ { n } - \widehat { \Pi } _ { m } \varepsilon \| ^ { 2 }$ 服从自由度为 $n - | m |$ 的卡方分布。

- 联合这两个恒等式，可将预测误差与风险联系起来：

$$
\frac {1}{n} \mathbb {E} \big (\| \mathbf {Y} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} \| ^ {2} \big) = r _ {m} + \sigma^ {2} \frac {(n - 2 | m |)}{n}
$$

### 赤池信息准则（2/2）：误差的经验估计量

- 已经得到：

$$
r _ {m} = \frac {1}{n} \mathbb {E} \big (\| \mathbf {Y} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} \| ^ {2} \big) + \sigma^ {2} \frac {(2 | m | - n)}{n}
$$

- 误差的无偏估计量（假设方差已知）：

$$
\widehat {r} _ {m} = \frac {1}{n} \| \mathbf {Y} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} \| ^ {2} + \sigma^ {2} \frac {(2 | m | - n)}{n}
$$

- 赤池信息准则：

$$
\widehat {m} = \underset {m \in \mathcal {M}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} \| ^ {2} + 2 | m | \sigma^ {2} \right\}
$$

选读材料结束。

<a id="section-20"></a>

## 高维情况下的 AIC

- 当 d 很大时，这样做是否实用？
- 最坏情况下，需要遍历大约 $e ^ { d / 2 }$ 个模型，其中 $| m | \simeq d / 2 .$。

<a id="section-21"></a>

## A. 稀疏性与线性模型：从数理统计到优化

### 解决计算负担：凸性的力量

实用的模型选择方法主要是贪心启发式方法，每次增加和／或移除一个变量，以探索整个模型空间的一部分；整个模型空间的规模随维度呈指数增长。例子包括前向逐步回归、前向—后向算法等。

- 问题：是否能够同时针对未知参数 $\beta$ 及其支撑索引子集进行优化？
- 答案是肯定的，代价是进行所谓的松弛：把带 $\ell _ { 0 }$ 惩罚的非凸表述替换为带 $\ell _ { 1 }$ 惩罚的凸化问题。

<a id="lasso"></a>

<a id="section-22"></a>

## 线性模型的 LASSO：从 $\ell _ { 0 }$ 到 $\ell _ { 1 }$

- 考虑对前述问题作松弛，用 $\ell _ { 1 } { \mathrm { - } } \mathsf { n o r m }$ 替代 $\ell _ { 0 } - \mathsf { n o r m }$。

$$
\| \beta \| _ {1} = \sum_ {j = 1} ^ {d} | \beta_ {j} |
$$

- 新估计量称为 ${ \mathsf { L } } { \mathsf { A } } { \mathsf { S } } { \mathsf { S } } { \mathsf { O } }$：对任意 $\lambda > 0$，

$$
\widehat {\beta} _ {\lambda} \in \underset {\beta \in \mathbb {R} ^ {d}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| ^ {2} + \lambda \| \beta \| _ {1} \right\}
$$

- 通过构建所谓正则化路径 $\lambda  \widehat { \beta } _ { \lambda }$ 的高效算法求近似解。

![image](<Images/02_LM/image_005.jpg>)

- 理论依据：可以证明，当 $n , d \to \infty$ 时，

$$
\frac {1}{n} \mathbb {E} \big (\| \mathbf {X} \beta^ {*} - \mathbf {X} \widehat {\beta} \| ^ {2} \big) \leq C \| \beta^ {*} \| _ {1} \sqrt {\frac {\log d}{n}}
$$

<a id="section-23"></a>

## 机器学习算法之“母”：惩罚优化

- 将学习过程写成对依赖于数据的准则的优化：

准则(h) = 训练误差(h) + λ 惩罚(h)。

- 训练误差：与损失函数相关的数据拟合项。
- 惩罚项：决策函数的复杂度。
- 常数 λ：通过交叉验证过程调整的平滑参数。

<a id="section-24"></a>

## A. 稀疏性与线性模型：结构化稀疏性

### 将人的先验放进惩罚项：稀疏模式

![image](<Images/02_LM/image_006.jpg>)

### 最简单的结构化惩罚：Group LASSO

- 参数 $\beta ^ { * }$ 的分组结构：设 G 是 $\{ 1 , \ldots , d \}$ 中索引子集的分组数。对 $g = 1 , \ldots , G$，用 $\mathbf { \boldsymbol { x } } ( \bar { g } )$ 表示 X 中由第 $\boldsymbol { g }$ 组变量组成的子矩阵，用 $\beta ^ { ( g ) }$ 表示施加于第 $\boldsymbol { g }$ 组变量的系数向量；$d _ { g }$ 是第 g 组的大小。
- Group LASSO 表述：

$$
\widehat {\beta} _ {\lambda} \in \underset {\beta \in \mathbb {R} ^ {d}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| ^ {2} + \lambda \sum_ {g = 1} ^ {G} \sqrt {d _ {g}} \| \beta^ {(g)} \| \right\}
$$

![image](<Images/02_LM/image_007.jpg>)

- 强制时间上的一致性，会引入如下惩罚项：

$$
\widehat {\beta} _ {\lambda} \in \underset {\beta \in \mathbb {R} ^ {d}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| ^ {2} + \lambda \| \beta \| _ {1} + \mu \sum_ {j = 2} ^ {d} | \beta_ {j} - \beta_ {j - 1} | \right\}
$$

<a id="ridge"></a>

<a id="section-25"></a>

## A. 稀疏性与线性模型：岭回归

### 惩罚优化：其他惩罚项？

- 到目前为止：由线性函数 $h \in \mathcal H$ 构成的假设类，以及诱导稀疏性的各种惩罚项。

$$
\text{准则} (h) = \text{训练误差} (h) + \lambda \text{惩罚项} (h)
$$

- 这个思想可追溯到 20 世纪 60 年代（Ivanov、John、Lavrent’ev、Tikhonov），当时惩罚项被用作不适定问题解的正则化器。

<a id="section-26"></a>

## 统计中的不适定问题：高维最小二乘回归

- 假设 d 大于 n。
- 求解最小二乘优化问题时，可以看到方程数少于变量数：这就是欠定线性系统的情形。
- 另一种说法是，$\mathbf { x } ^ { \tau } \mathbf { x }$ 不满秩，因而不可逆，并且有无穷多个解。

<a id="section-27"></a>

## 统计中最早的正则化方法：岭回归

- Ridge 估计量是下列惩罚优化问题的解：对任意 $\lambda > 0$，

$$
\widehat {\beta} _ {\lambda} \in \underset {\beta \in \mathbb {R} ^ {d}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| ^ {2} + \lambda \| \beta \| _ {2} ^ {2} \right\}
$$

<a id="section-28"></a>

## 岭回归估计量的推导

- 记目标函数为：

$$
F (\beta) = \left(\mathbf {Y} - \mathbf {X} \beta\right) ^ {T} \left(\mathbf {Y} - \mathbf {X} \beta\right) + \lambda \beta^ {T} \beta
$$

- 利用 F 的凸性和可微性，通过求解下式得到解：

$$
\nabla F (\beta) = 2 \mathbf {X} ^ {T} (\mathbf {X} \beta - \mathbf {Y}) + 2 \lambda \beta = 0
$$

- 解为：

$$
\widehat {\beta} _ {\lambda} = \left(\mathbf {X} ^ {T} \mathbf {X} + \lambda I _ {d}\right) ^ {- 1} \mathbf {X} ^ {T} \mathbf {Y}
$$

因为 ${ \pmb { \times } } ^ { T } { \pmb { \times } } + \lambda I _ { d }$ 总是可逆的。

- 当 d 很大时，计算仍然困难……

<a id="section-29"></a>

## 对偶优化问题：表述与 KKT 条件

- 岭回归优化的等价表述：

$$
\min _ {\beta \in \mathbb {R} ^ {d}, r \in \mathbb {R} ^ {n}} \left\{\frac {1}{2} \| r \| ^ {2} + \frac {\lambda}{2} \| \beta \| ^ {2} \right\} \quad \text{满足} r = \mathbf {X} \beta - \mathbf {Y}
$$

- 乘子向量为 $\alpha$ 的拉格朗日表述：

$$
\mathcal {L} (\beta , r, \alpha) = \frac {1}{2} \| r \| ^ {2} + \frac {\lambda}{2} \| \beta \| ^ {2} + \alpha^ {T} (r - \mathbf {X} \beta + \mathbf {Y})
$$

- Karush–Kuhn–Tucker 条件：令关于原变量 $\beta , r ,$ 的梯度为零，得到：

$$
\beta (\alpha) = \frac {1}{\lambda} \mathbf {X} ^ {T} \alpha \quad \text{且} \quad r (\alpha) = - \alpha
$$

<a id="section-30"></a>

## 对偶优化问题：求解

- 于是，岭回归优化的一种等价表述为：

$$
\mathcal {L} (\beta (\alpha), r (\alpha), \alpha) = \frac {1}{2} \| \alpha \| ^ {2} + \frac {1}{2 \lambda} \| \mathbf {X} ^ {T} \alpha \| + \alpha^ {T} \left(- \alpha - \frac {1}{\lambda} \mathbf {X X} ^ {T} \alpha + \mathbf {Y}\right)
$$

> **译注：** 原课件的 $\|\mathbf X^T\alpha\|$ 漏了平方。补上平方后，代回并整理得到对偶函数 $g(\alpha)=\alpha^T\mathbf Y-\tfrac12\|\alpha\|^2-\tfrac1{2\lambda}\|\mathbf X^T\alpha\|^2$，对偶问题是最大化该函数。原文的代入中间式完整保留在上方。

- 解为：

$$
\widehat {\alpha} = \lambda \left(\mathbf {X X} ^ {T} + \lambda I _ {n}\right) ^ {- 1} \mathbf {Y} \quad \text{且} \quad \widehat {\beta} = \frac {1}{\lambda} \mathbf {X} ^ {T} \widehat {\alpha}
$$

<a id="section-31"></a>

## 对偶优化问题：结果的解释

- 对 $x \in \mathbb { R } ^ { d }$ 的预测可用 α 表示。

$$
x ^ {T} \widehat {\beta} = \frac {1}{\lambda} x ^ {T} \mathbf {X} ^ {T} \widehat {\alpha} = \frac {1}{\lambda} \sum_ {i = 1} ^ {n} \widehat {\alpha} _ {i} x ^ {T} X _ {i}
$$

- 可以利用恒等式：

$\pmb { \mathsf { X } } ^ { T } \left( \pmb { \mathsf { X } } \pmb { \mathsf { X } } ^ { T } + \lambda \pmb { I } _ { n } \right) ^ { - 1 } = \left( \pmb { \mathsf { X } } ^ { T } \pmb { \mathsf { X } } + \lambda \pmb { I } _ { d } \right) ^ { - 1 } \pmb { \mathsf { X } } ^ { T }$ 来验证两个解相同。

- 重要观察：优化与函数求值只需要 $x ^ { \prime } s$ 与数据点 $X _ { i } ^ { \prime } s$ 之间的两两内积。

<a id="section-32"></a>

## Elastic Net：兼得 LASSO 与 Ridge 的优点？

- 动机（引自 Zou 与 Hastie，2005）：

(a) 在 $p > n { \mathrm { ~ c a s e } }$ 的情形下，由于凸优化问题自身的性质，LASSO 在达到饱和之前最多选择 n 个变量。对于变量选择方法，这似乎是一项限制。此外，除非系数的 $L _ { \mathrm { l } } \mathrm { - n o r m }$ 上界小于某个值，否则 LASSO 不是良好定义的。

(b) 如果一组变量之间的两两相关性非常高，LASSO 倾向于只从中选择一个变量，而不在意具体选中哪个。参见第 2.3 节。

(c) 对通常的 $n > p$ 情形，如果预测变量之间高度相关，经验上观察到 LASSO 的预测性能不如岭回归（Tibshirani，1996）。

> **译注：** 以上是原课件引用 Zou 与 Hastie（2005）的论述，不能脱离该文的条件把它解释为所有 LASSO 问题都不存在解或都不唯一。

- 组合 $\ell _ { 1 }$ 与 $\ell _ { 2 }$ 惩罚。

$$
\widehat {\beta} _ {\lambda} \in \underset {\beta \in \mathbb {R} ^ {d}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| ^ {2} + \lambda \| \beta \| _ {1} + \mu \| \beta \| _ {2} ^ {2} \right\}
$$

<a id="section-33"></a>

## LASSO 与 Elastic Net：正则化路径比较

![image](<Images/02_LM/image_008.jpg>)

![image](<Images/02_LM/image_009.jpg>)

<a id="section-34"></a>

## 超参数调整：交叉验证

- 如何选择参数 λ 和 $\mu ?$？它们称为超参数、平滑参数或正则化参数。
- 这是控制机器学习方法过拟合效应时普遍遇到的问题。
- 交叉验证过程将在后续课程中展开。

<a id="section-35"></a>

## 练习：比较三种惩罚

- 考虑如下玩具问题：$Y \sim { \mathcal { N } } _ { 1 } ( \beta ^ { * } , 1 )$，其中 $\beta$ 是实值参数，$( d = 1 )$。
- 分别最小化下面三个函数，求出相应的三个估计量：

$$
(\mathrm{i}) \frac {1}{2} (Y - \beta) ^ {2} + \lambda , (\mathrm{ii}) \frac {1}{2} (Y - \beta) ^ {2} + \lambda | \beta |, (\mathrm{iii}) \frac {1}{2} (Y - \beta) ^ {2} + \lambda \beta^ {2}
$$

- 以无约束最小二乘估计为自变量，画出这些估计量的函数图像，并解释惩罚估计过程中使用的术语：硬阈值、软阈值、收缩。

<a id="kernels"></a>

<a id="section-36"></a>

## B. 估计非线性函数

### 从非线性到线性：多项式回归例子

- 考虑维度为 $d = 2$ 的多项式回归：它对应一个维度为 $d ^ { \prime } = 7$ 的线性模型，特征向量为：

$$
\Phi (x _ {1}, x _ {2}) = \left(1, \sqrt {2} x _ {1}, \sqrt {2} x _ {2}, \sqrt {2} x _ {1} x _ {2}, x _ {1} ^ {2}, x _ {2} ^ {2}\right) ^ {T}
$$

> **译注：** 原页写作 7 维，但所列特征向量只有 6 个分量；与该向量一致的维度应为 6。

- 注意：

$$
\Phi (x) ^ {T} \Phi (x ^ {\prime}) = (x ^ {T} x ^ {\prime} + 1) ^ {2}
$$

- 称 $K ( x , x ^ { \prime } ) = ( x ^ { T } x ^ { \prime } + 1 ) ^ { 2 }$ 为多项式核。核具有这样一个性质：可以表示为高维特征空间中的内积。特征空间是原始 d 维输入空间经 Φ 映射得到的像空间，其维度可能非常大。

<a id="section-37"></a>

## 核的魔力：核岭回归

- 在线性岭回归中已经看到，无论问题表述还是预测求值，真正用到的依赖数据的量，只有 $X _ { i } ^ { T } X _ { j }$ 与 $x ^ { T } X _ { i }$ 的两两内积。
- 基本上，可以将任意一个内积替换为相应点对的核函数值，而完全不改变求解的算法复杂度。于是能够估计下列非线性函数中的参数 $\alpha _ { i }$：

> **译注：** 这里保留原文的算法复杂度说法。替换内积不改变基于 Gram 矩阵求解的框架，但具体核函数的求值代价与存储成本仍需另外考虑。

$$
f (x) = \sum_ {i = 1} ^ {n} \alpha_ {i} K (x, X _ {i})
$$

<a id="section-38"></a>

## 基本核的例子

- 线性核：$\operatorname { K } ( \mathbf { x } , \mathbf { z } ) = \mathbf { x } \cdot z$。
- 多项式核：$\operatorname { K } ( \mathbf { x } , z ) = ( \mathbf { x } \cdot z ) ^ { \mathrm { d } } \circ r \operatorname { K } ( \mathbf { x } , z ) = ( 1 + \mathbf { x } \cdot z ) ^ { \mathrm { d } }$。
- 高斯核：$\begin{array} { r } { \mathrm { K } ( \mathrm { x } , z ) = \exp \left[ - \frac { \left| \left| x - z \right| \right| ^ { 2 } } { 2 \sigma ^ { 2 } } \right] } \end{array}$。
- Laplace 核：$\begin{array} { r } { \mathrm { K } ( \mathrm { x } , z ) = \exp \left[ - \frac { | | x - z | | } { 2 \sigma ^ { 2 } } \right] } \end{array}$。

![image](<Images/02_LM/image_010.jpg>)

$$
\begin{array}{l} d _ {K} \left(\mathbf {x} _ {1}, \mathbf {x} _ {2}\right) ^ {2} = \| \Phi \left(\mathbf {x} _ {1}\right) - \Phi \left(\mathbf {x} _ {2}\right) \| _ {\mathcal {H}} ^ {2} \\ \qquad = \langle \Phi \left(\mathbf {x} _ {1}\right) - \Phi \left(\mathbf {x} _ {2}\right), \Phi \left(\mathbf {x} _ {1}\right) - \Phi \left(\mathbf {x} _ {2}\right) \rangle_ {\mathcal {H}} \\ \qquad = \langle \Phi \left(\mathbf {x} _ {1}\right), \Phi \left(\mathbf {x} _ {1}\right) \rangle_ {\mathcal {H}} + \langle \Phi \left(\mathbf {x} _ {2}\right), \Phi \left(\mathbf {x} _ {2}\right) \rangle_ {\mathcal {H}} - 2 \langle \Phi \left(\mathbf {x} _ {1}\right), \Phi \left(\mathbf {x} _ {2}\right) \rangle_ {\mathcal {H}} \\ d _ {K} (\mathbf {x} _ {1}, \mathbf {x} _ {2}) ^ {2} = K (\mathbf {x} _ {1}, \mathbf {x} _ {1}) + K (\mathbf {x} _ {2}, \mathbf {x} _ {2}) - 2 K (\mathbf {x} _ {1}, \mathbf {x} _ {2}) \end{array}
$$

- 为处理字符串（文本、DNA 序列等）这样的结构化数据，人们设计了专门的核。
- 用于 DNA 序列的谱核示例：

核的定义

- $\mathbf{x} = \text{CGGSLIAMMWFGV}$ 的 3-spectrum（长度为 3 的子串谱）是：(CGG, GGS, GSL, SLI, LIA, IAM, AMM, MMW, MWF, WFG, FGV)。
- 令 $\Phi_u(\mathbf{x})$ 表示 $u$ 在 $\mathbf{x}$ 中的出现次数。$k$-spectrum 核定义为 $K(\mathbf{x}, \mathbf{x}') := \sum_{u \in A^k} \Phi_u(\mathbf{x}) \Phi_u(\mathbf{x}')$。

> **译注：** 原页称这是 DNA 序列示例，但字符串含有 DNA 四种碱基字母以外的字符；这里保留原例，不改变核的计数定义。

<a id="section-39"></a>

## 核机器学习估计：可行吗？

- 核函数具有良好的建模性质。
- 问题是：最小二乘意义下的惩罚优化是否可行？

<a id="section-40"></a>

## C. 推广：应用于其他估计问题

### 惩罚优化：还有哪些变体？

- 到目前为止：由线性函数 $h \in \mathcal H$ 构成的假设类，以及不同的惩罚项。

$$
\text{准则} (h) = \text{训练误差} (h) + \lambda \text{惩罚项} (h)
$$

- 从现在起：使用其他损失函数来改变训练误差。

$$
\text{准则} (h) = \text{训练误差} (h) + \lambda \text{惩罚项} (h)
$$

几个例子：

岭回归：

线性 SVM：

$$
\min _ {\boldsymbol {\beta} \in \mathbb {R} ^ {p}} \frac {1}{n} \sum_ {i = 1} ^ {n} \frac {1}{2} (y _ {i} - \boldsymbol {\beta} ^ {\top} \mathbf {x} _ {i}) ^ {2} + \lambda \| \boldsymbol {\beta} \| _ {2} ^ {2}.
$$

$$
\min _ {\boldsymbol {\beta} \in \mathbb {R} ^ {p}} \frac {1}{n} \sum_ {i = 1} ^ {n} \max (0, 1 - y _ {i} \boldsymbol {\beta} ^ {\top} \mathbf {x} _ {i}) + \lambda \| \boldsymbol {\beta} \| _ {2} ^ {2}.
$$

逻辑回归：$\underset { \beta \in \mathbb { R } ^ { p } } { \min } \frac { 1 } { n } \sum _ { i = 1 } ^ { n } \vert \boldsymbol { \mathrm { o g } } \left( 1 + e ^ { - y _ { i } \beta ^ { \top } \boldsymbol { \mathbf { x } } _ { i } } \right) + \lambda \vert \vert \beta \vert \vert _ { 2 } ^ { 2 } .$。

![image](<Images/02_LM/image_011.jpg>)

- 其他任务：用于分类的线性模型。
- 表示问题：特征工程、变量选择、表示学习。
- 从线性模型到非线性模型：哪些部分可以保留？
