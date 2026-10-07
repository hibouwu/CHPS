# 深度学习：原课件忠实译本

> 正文按原课件顺序逐段翻译，不作摘要式压缩；例子、练习、重复正文、公式、图表及文献均保留。图中文字保留原图语言。原课件错误与必要辨析以独立“译注”标明。

[原 PDF](06_DL.pdf) · [原文转换稿](06_DL.md) · [逐块对应清单](Translation-audit/2026-09-28-coverage.json) · [课程目录](../README.md)

<details>
<summary>本讲目录（点击展开）</summary>

- [深度学习](#section-01)
- [学习的“全景图”](#section-02)
- [此前学过的内容](#section-03)
- [机器学习方法：此前学过的例子](#section-04)
- [深度学习：主要概念介绍](#section-05)
- [深度学习](#section-06)
- [深度学习的成功（1/3）：计算机视觉](#section-07)
- [深度学习的成功（2/3）：语音识别](#section-08)
- [深度学习的成功（3/3）：自然语言处理](#section-09)
- [浅层与深度学习：Vapnik 与 LeCun](#section-10)
- [本讲目标](#section-11)
- [神经网络的历史视角](#section-12)
- [第一波：20 世纪 60 年代](#section-13)
- [第二波：20 世纪 80 年代](#section-14)
- [第二波：20 世纪 80 年代](#section-15)
- [单层神经网络的定义](#section-16)
- [单层神经网络是通用逼近器](#section-17)
- [选读材料：通过反向传播计算梯度](#section-18)
- [反向传播：讨论](#section-19)
- [机器学习中的新权衡：三个项](#section-20)
- [第三波：2010 年代](#section-21)
- [深度学习工程](#section-22)
- [深度学习中的正则化，以及深度学习理论为何困难](#section-23)
- [深度学习实现：GitHub 示例](#section-24)
- [设计问题（1/2）：设定](#section-25)
- [设计问题（2/2）：选择结构](#section-26)
- [其他常见深度学习架构](#section-27)
- [其他架构：卷积神经网络](#section-28)
- [其他架构：自编码器](#section-29)
- [从浅层到深层网络](#section-30)
- [近似理论中的结果](#section-31)
- [深度学习优化中的结果](#section-32)
- [Vapnik 理论应用于深度学习：排列的复杂度](#section-33)

</details>

M2 CHPS

**数据科学与机器学习导论**

Nicolas Vayatis

<a id="section-01"></a>

## 深度学习

<a id="section-02"></a>

## 学习的“全景图”

![image](<Images/06_DL/image_001.jpg>)

机器学习

<a id="section-03"></a>

## 此前学过的内容

### 监督机器学习：设定

- 数据：$( X _ { 1 } , Y _ { 1 } ) , \dots , ( X _ { 1 } , Y _ { 1 } )$，其中 $X _ { j }$ 是第 i 个观测的变量（因素）向量，$Y _ { i }$ 是 $X _ { j }$ 的标签。

> **译注：** 原页数据序列的末项重复写成第一项；按上下文应为第 n 个样本，原记号保留以便核对。

- 假设类：函数集合 $h \in \mathcal H$。
- 函数 h 在数据点 $( X , Y )$ 上的损失。

$$
\ell (h (X), Y) \geq 0
$$

- 函数 h 在数据上的经验风险：

$$
\widehat {L} _ {n} (h) = \frac {1}{n} \sum_ {i = 1} ^ {n} \ell (h (X _ {i}), Y _ {i})
$$

### 什么是机器学习方法？

- 问题由三个要素刻画：
  - 损失。
  - 假设空间。
  - 正则化。
- 机器学习算法由一种优化策略刻画，该策略在假设空间上最小化正则化损失。

<a id="section-04"></a>

## 机器学习方法：此前学过的例子

- 一般假设空间，通过经验风险最小化（ERM）选择函数，可以是浅层或深层方法。
- （稀疏）线性模型，通过（惩罚）最小二乘最小化估计参数。
- 核岭回归。练习：这种情况下的假设空间、损失、正则化和优化方法分别是什么？

最后一种是流行且高效的浅层学习方法的例子。

<a id="section-05"></a>

## 深度学习：主要概念介绍

<a id="network-function"></a>

### 深度前馈网络

![image](<Images/06_DL/image_002.jpg>)

- 假设空间：如下形式的函数。

$$
h (x, \theta) = \sigma_ {m} \circ A _ {m} \circ \sigma_ {m - 1} \circ \dots \circ A _ {2} \circ \sigma_ {1} \circ A _ {1} x
$$

其中 $\theta = \left( A _ { 1 } , \ldots , A _ { m } \right)$ 是需要通过学习估计的参数序列。

- 用 $\sigma = \left( \sigma _ { 1 } , \ldots , \sigma _ { m } \right)$ 表示所谓激活函数；它们是与网络架构选择有关的超参数，架构选择包括层数及各层大小，见下文。

<a id="training-objective"></a>

### 深度前馈网络

![image](<Images/06_DL/image_003.jpg>)

- 优化目标（远非凸的！正则化项在哪里？）：

$$
\min _ {\theta} \frac {1}{n} \sum_ {i = 1} ^ {n} \ell (h (X _ {i}, \theta), Y _ {i})
$$

- 基于随机梯度下降的优化方法：在数据点上迭代。

$$
\theta_ {i + 1} = \theta_ {i} - \eta \frac {\partial \ell (h (X _ {i} , \theta) , Y _ {i})}{\partial \theta} (\theta_ {i})
$$

<a id="section-06"></a>

## 深度学习

### 为什么流行？

### “深”意味着输入与输出之间有“许多层”（复合）……

深度神经网络

![image](<Images/06_DL/image_004.jpg>)

隐藏层 1；隐藏层 2；隐藏层 3。

![image](<Images/06_DL/image_005.jpg>)

![image](<Images/06_DL/image_006.jpg>)

边缘

![image](<Images/06_DL/image_007.jpg>)

边缘的组合

![image](<Images/06_DL/image_008.jpg>)

对象模型

<a id="section-07"></a>

## 深度学习的成功（1/3）：计算机视觉

![image](<Images/06_DL/image_009.jpg>)

<a id="section-08"></a>

## 深度学习的成功（2/3）：语音识别

![image](<Images/06_DL/image_010.jpg>)

| 系统 | 清晰语音（94） | 含噪语音（82） | 合并（176） |
| --- | --- | --- | --- |
| Apple Dictation | 14.24 | 43.76 | 26.73 |
| Bing Speech | 11.73 | 36.12 | 22.05 |
| Google API | 6.64 | 30.47 | 16.72 |
| wit.ai | 7.94 | 35.06 | 19.41 |
| Deep Speech | 6.56 | 19.06 | 11.85 |

<a id="section-09"></a>

## 深度学习的成功（3/3）：自然语言处理

![image](<Images/06_DL/image_011.jpg>)

<a id="section-10"></a>

## 浅层与深度学习：Vapnik 与 LeCun

首批在视觉任务上达到人类表现的算法。

LeCun、Boser 等（1989）. Backpropagation Applied to Handwritten Zip Code Recognition（将反向传播应用于手写邮政编码识别），发表于 Neural Computation。

架构：1000 个单元，70,000 条连接。

- C. Cortes 与 V. Vapnik（1995）. Support-Vector Networks（支持向量网络），发表于 Machine Learning。

架构：1 个核，2 个参数。

![USPS 手写邮政编码样本，来自原 PDF 第 15 页](<Images/06_DL/pdf_p15_usps.jpg>)

USPS 邮政编码数据库。

> **译注：** “达到人类表现”和“2 个参数”均为原页历史性概括，不能据此认为训练后的 SVM 只有两个系数。

<a id="section-11"></a>

## 本讲目标

- 加深对深度学习与神经网络的理解：什么时候有效，什么时候无效，以及“有效”意味着什么（开放讨论）。
- 深度学习优化与工程的实践指南。
- 了解深度学习的三个谜题，并将其与此前学过的机器学习概念联系起来，例如近似误差、复杂度与正则化。

<a id="section-12"></a>

## 神经网络的历史视角

### 控制论（20 世纪 40—60 年代）

- 成就：对单个神经元建模并训练。
- 关键算法：感知机。
- 论文：Rosenblatt（1958）。

### 联结主义（20 世纪 80 年代）

- 成就：训练一层或两层隐藏层。
- 关键算法：反向传播。
- 论文：Rumelhart、Hinton、Williams（1986）。

### 深度学习（2007 年起）

- 成就：训练多层表示。
- 关键算法：随机梯度。
- 论文：Hinton（2006）、Bengio–LeCun（2007）。

<a id="section-13"></a>

## 第一波：20 世纪 60 年代

感知机

### 原始神经网络：单神经元感知机

![image](<Images/06_DL/image_012.jpg>)

<a id="section-14"></a>

## 第二波：20 世纪 80 年代

多层感知机

1. 理论：通用逼近器。
2. 算法：反向传播算法。

<a id="section-15"></a>

## 第二波：20 世纪 80 年代

多层感知机

### 1. 通用逼近器的存在性定理

### Stone–Weierstrass 定理

- 考虑任意连续函数 $f ~ : ~ [ a , b ] \to \mathbb { R }$，则对任意 $\varepsilon > 0$，存在多项式 $P$，使得：

$$
\sup _ {x \in [ a, b ]} | f (x) - P (x) | <   \varepsilon .
$$

<a id="section-16"></a>

## 单层神经网络的定义

单层神经网络：设 σ 是一个“光滑”激活函数。具有 N 个单元、激活函数为 σ 的单层神经网络，是如下形式的函数：

$$
h (x) = \sum_ {k = 1} ^ {N} \sigma \left(a _ {k} ^ {T} x + b\right), \forall x \in \mathbb {R} ^ {d}
$$

其中 $a \in \mathbb { R } ^ { d } , \ b \in \mathbb { R }$，N 为整数。数目 N 对应网络隐藏层中的单元数。

> **译注：** 原页公式省略了输出权重，且偏置统一写成 b；通用逼近中常用的形式为 $h(x)=c_0+\sum_{k=1}^N c_k\sigma(a_k^Tx+b_k)$。此外，图示 ReLU 在零点并不光滑。

![image](<Images/06_DL/image_013.jpg>)

![image](<Images/06_DL/image_014.jpg>)

<a id="section-17"></a>

## 单层神经网络是通用逼近器

- Cybenko 定理：考虑任意连续函数 $f : [ 0 , 1 ] ^ { d } \to \mathbb { R }$，则对任意 $\varepsilon > 0$，存在单层神经网络 $\begin{array} { r } { \boldsymbol { h } ( \boldsymbol { x } ) = \sum _ { k = 1 } ^ { N } \overset { \cdot } { \boldsymbol { \sigma } } ( \boldsymbol { a } _ { k } ^ { T } \boldsymbol { x } + \boldsymbol { b } ) } \end{array}$，也就是存在某些 N、a、b，使得：

$$
\sup _ {x \in [ a, b ]} | f (x) - h (x) | <   \varepsilon .
$$

> **译注：** 原页上确界区域写成了一维 $[a,b]$，应与前面的输入域 $[0,1]^d$ 对应；通用逼近还需对激活函数施加相应条件。

- 后续工作：Hornik、Stinchcombe、White（1989），Barron（1993）。

<a id="backpropagation"></a>

### 2. 反向传播算法

多层感知机参数校准的关键。假设空间：如下形式的函数。

$$
h (x, \theta) = \sigma \circ A _ {m} \circ \sigma \circ \dots \circ A _ {2} \circ \sigma \circ A _ {1} x
$$

其中 $\theta = \left( A _ { 1 } , \ldots , A _ { m } \right)$ 是需要通过学习估计的参数序列，$\sigma$ 是逐分量施加的激活函数。

![image](<Images/06_DL/image_015.jpg>)

- 考虑平方损失。给定权重向量 $\theta _ { 1 }$，可以将误差计算为：

$$
\mathcal {L} \left(\theta_ {1}\right) = \frac {1}{n} \sum_ {i = 1} ^ {n} \left(h \left(X _ {i}, \theta_ {1}\right) - Y _ {i}\right) ^ {2}
$$

- 思路是在网络中将误差反向传播，按下式更新 $\theta _ { 1 }$：

$$
\theta_ {2} = \theta_ {1} - \eta \nabla_ {\theta} \mathcal {L} (\theta_ {1})
$$

其中 $\eta$ 是所谓学习率。

<a id="section-18"></a>

## 选读材料：通过反向传播计算梯度

### 反向传播背景：链式法则

- 考虑三个函数的复合：

$$
f (u) = \ell \circ \sigma \circ g (x)
$$

> **译注：** 原式混用 u 与 x；链式求导时应统一自变量。

其中 $t = \sigma \circ g ( u )$，$z = g ( u )$，这里所有量都在 $\mathbb { R }$ 中。

- 链式法则给出 $f \colon$ 的导数表达式：

$$
\frac {d f}{d u} (u) = \frac {d \ell}{d t} (t) \frac {d \sigma}{d z} (z) \frac {d g}{d u} (u) = \ell^ {\prime} (\sigma \circ g (u)) \sigma^ {\prime} (g (u)) g ^ {\prime} (u)
$$

### 反向传播背景：激活函数

#### 典型例子

![image](<Images/06_DL/image_016.jpg>)

- 对逻辑激活函数 $\sigma ( z ) = \frac { 1 } { 1 + e ^ { - z } }$，通过基本代数运算得到：

$$
\sigma^ {\prime} (z) = \frac {d \sigma}{d z} (z) = \sigma (z) (1 - \sigma (z))
$$

- 考虑连接到网络输出 Y 的单个单元（神经元）$h ( x , a ) = \sigma ( a ^ { T } x )$。
- 这个神经元在训练数据上的预测误差为：

$$
\mathcal {L} (a) = \frac {1}{n} \sum_ {i = 1} ^ {n} \ell (\sigma (a ^ {T} X _ {i}), Y _ {i})
$$

其中 $\ell ( t , y ) = ( t - y ) ^ { 2 }$，这里考虑平方损失。

- 对三个函数复合、其中最后一个函数为线性的情形，应用链式法则。
- $\mathcal { L }$ 关于 a 的梯度为：

$$
\frac {\partial \mathcal {L}}{\partial a _ {j}} (a) = \frac {1}{n} \sum_ {i = 1} ^ {n} \frac {\partial \ell}{\partial t} (\sigma (a ^ {T} X _ {i}), Y _ {i}) \sigma^ {\prime} (a ^ {T} X _ {i}) X _ {i j}
$$

- 这里的特殊情形：平方损失、逻辑激活函数。

$$
\frac {\partial \ell}{\partial t} (t, Y _ {i}) = 2 (t - Y _ {i}) \text{且} \sigma^ {\prime} (z) = \sigma (z) (1 - \sigma (z))
$$

- 对输入“神经元”施加的梯度更新如下。

$$
\frac {\partial \mathcal {L}}{\partial a _ {j}} (a) = \frac {2}{n} \sum_ {i = 1} ^ {n} (z _ {i} - Y _ {i}) z _ {i} (1 - z _ {i}) X _ {i j}
$$

> **译注：** 上式是梯度的计算式，尚不是参数更新式；更新还需乘学习率并从当前权重中减去。

其中 $z _ { i } = \sigma \big ( \boldsymbol { a } ^ { T } X _ { i } \big )$。

选读材料结束。

选读材料结束。

<a id="section-19"></a>

## 反向传播：讨论

- 在多层情形下，只需向前面的层继续应用链式法则。更多细节参见 Jake Abernethy 的讲义。

[Jake Abernethy 讲义目录](https://nbviewer.jupyter.org/format/slides/github/thejakeyboy/umich-eecs545-lectures/)

<!-- 原转换稿此处的 URL 片段已完整拼接于上方链接。 -->

![image](<Images/06_DL/image_017.jpg>)

前向

![image](<Images/06_DL/image_018.jpg>)

反向

<!-- 原转换稿此处的 URL 片段已完整拼接于上方链接。 -->

<!-- 原转换稿此处的 URL 片段已完整拼接于上方链接。 -->

### 但是，梯度下降会收敛到最优解吗？

<a id="learning-errors"></a>

<a id="section-20"></a>

## 机器学习中的新权衡：三个项

$$
\begin{array}{r c l} \mathcal {E} & = & \mathbb {E} \left[ E (f _ {\mathcal {T}} ^ {*}) - E (f ^ {*}) \right] + \mathbb {E} \left[ E (f _ {n}) - E (f _ {\mathcal {T}} ^ {*}) \right] + \mathbb {E} \big [ E (\tilde {f} _ {n}) - E (f _ {n}) \big ] \\ & = & \mathcal {E} _ {\mathrm{app}} + \mathcal {E} _ {\mathrm{est}} + \mathcal {E} _ {\mathrm{opt}}. \end{array}
$$

![image](<Images/06_DL/image_019.jpg>)

| 量 | 含义 | $\mathcal F$ | $n$ | $\rho$ |
|---|---|---|---|---|
| $\mathcal E_{\mathrm{app}}$ | 近似误差 | ↘ | | |
| $\mathcal E_{\mathrm{est}}$ | 估计误差 | ↗ | ↘ | |
| $\mathcal E_{\mathrm{opt}}$ | 优化误差 | … | … | ↗ |
| $T$ | 计算时间 | ↗ | ↗ | ↘ |

$f_{\mathcal D}^*$：真实参照，$\arg\min_{f\in\mathcal Y^{\mathcal X}}L_{\mathcal D}(f)$。

$h _ { \mathcal { D } } ^ { \ast }$：最优假设 $\mathsf { ( a r g m i n } _ { h \in \mathcal { H } } L _ { \mathcal { D } } ( h ) )$。

$h _ { S } ^ { * }$：经验最优假设 $\mathsf { \Gamma } ( \mathsf { a r g m i n } _ { h \in \mathcal { H } } L _ { S } ( h ) )$。

$\bar { h }$：算法返回的假设。

这里 n 为样本量，$\rho$ 为优化中的数值容差。

> **译注：** 原页用真实风险差定义最后一项时，该项不必非负，例如提前停止可能改善泛化。表中箭头是趋势示意，不能当作对所有模型、数据与算法成立的单调性定理。

<a id="section-21"></a>

## 第三波：2010 年代

### 从浅层到深层网络

1. 怎样构建深层网络。
2. 深度学习的谜题。

### 从浅层到深层网络

1. 怎样构建深层网络。

<a id="section-22"></a>

## 深度学习工程

- 深度学习软件环境以计算图组织，例如 Theano、Keras、TensorFlow。

![image](<Images/06_DL/image_020.jpg>)

- 计算图是用图论语言表示数学函数的一种方式。
- 在计算图中，节点要么是输入值，要么是用于组合数值的函数。

数据流经计算图时，边获得相应的权值。输入节点的出边以该输入值为权值；函数节点的输出按指定函数组合入边的权值，从而得到权值。

> **译注：** 这里边的“权值”指流经边的计算结果，并不意味着每条数据依赖边都有独立可训练参数。

<a id="regularization"></a>

<a id="section-23"></a>

## 深度学习中的正则化，以及深度学习理论为何困难

正则化隐含在目标之中，但计算图中存在许多工程技巧：

- 权重衰减。
- 权重共享。
- 提前停止。
- 模型平均。
- Dropout。
- 数据增强。
- 对抗训练。

> **译注：** 原页将这些方法概括为工程中的隐含正则化；它们包含目标函数、结构、数据和优化过程等不同层面的约束，不都属于严格意义上的隐式正则化。

<a id="section-24"></a>

## 深度学习实现：GitHub 示例

- https://github.com/enggen/Deep-Learning-Coursera/
- https://github.com/aymericdamien/TensorFlow-Examples/

<!-- 原转换稿此处的 URL 片段已完整拼接于上方链接。 -->

<a id="section-25"></a>

## 设计问题（1/2）：设定

- 用 T 表示深层网络的结构参数，包括架构、激活函数、正则化方式等；用 $\dot { \hat { f } } _ { T }$ 表示给定 T 后深度学习产生的函数。
- 假设能够获得该函数预测误差的某个估计 $\hat { L } ( \hat { f } _ { T } )$，可通过留出法、交叉验证等估计。
- 寻找 T 是解决估计—近似权衡的关键。

<a id="section-26"></a>

## 设计问题（2/2）：选择结构

- 选择深层网络的结构是一个元学习问题。
- 如果能够求解以下优化问题，就可以得到最优架构：

$$
\min _ {T} \hat {L} (\hat {f} _ {T})
$$

这个问题通常非凸且非光滑。

- 寻找 T 的主要途径：经验、启发式、离散优化、实验设计？

<a id="section-27"></a>

## 其他常见深度学习架构

- 卷积神经网络。
- 循环神经网络。
- 长短期记忆网络。
- 自编码器。
- Boltzmann 机、信念网络。
- 生成对抗网络。

<a id="section-28"></a>

## 其他架构：卷积神经网络

![image](<Images/06_DL/image_021.jpg>)

<a id="section-29"></a>

## 其他架构：自编码器

![image](<Images/06_DL/image_022.jpg>)

<a id="section-30"></a>

## 从浅层到深层网络

### 2. 深度学习的谜题

### 深度学习的谜题

- 近似：深层优于浅层吗？
- 优化：上百万维的非凸问题！
- 过拟合：巨大的复杂度。

<a id="section-31"></a>

## 近似理论中的结果

### 浅层与深层网络的比较

- Poggio 与 Liao（2018）：复合函数的逼近。
- Liang 与 Srikant（2017）：多项式函数的逼近。
- 相似的发现：

“对于给定的函数逼近精度，浅层网络逼近一个函数所需的神经元数，比相应深层网络所需的神经元数呈指数级增长。”

> **译注：** 此处的深度优势依赖目标函数类、激活函数、网络结构和误差定义，不能推广为所有深网络对所有函数都指数级优于浅层网络。

<a id="section-32"></a>

## 深度学习优化中的结果

- 在某些条件下，不存在坏的局部极小值。

![image](<Images/06_DL/image_023.jpg>)

图 1：非凸函数的临界点示例，以红色标出。(a,c) 平坦区域；(b,d) 全局极小值；(c,g) 局部极大值；(f,h) 局部极小值。

> **译注：** 原图的局部极大值编号应为 (e,g)；原图注把 e 写成了 c。

### SGD 避开不良临界点

- 更大的网络具有更好的性质，局部极小值都是全局极小值。

> **译注：** 这些优化结论分别有各自的网络、损失、数据与算法条件，不能合并为任意深度网络的无条件保证。

### 参考文献

Soudry 与 Carmon（2016），No bad local minima: Data independent training error guarantees for multilayer neural networks（无坏的局部极小值：多层神经网络中与数据无关的训练误差保证）。

Kawaguchi（2016），Deep learning without poor local minima（没有坏的局部极小值的深度学习）。

Haeffele 与 Vidal（2017），Global optimality in neural network training（神经网络训练中的全局最优性）。

Janzamin、Sedghi 与 Anandkumar（2015），Beating the perils of non-convexity: Guaranteed training of neural networks using tensor methods（克服非凸性的困难：使用张量方法实现有保证的神经网络训练）。

Panageas 与 Piliouras（2016），Gradient descent only converges to minimizers: Non-isolated critical points and invariant regions（梯度下降只收敛到极小点：非孤立临界点与不变区域）。

Brutzkus、Alon 等（2017），SGD Learns Over-parameterized Networks that Provably Generalize on Linearly Separable Data（SGD 学习在理论上能对线性可分数据泛化的过参数化网络）。

<!-- 原转换稿中的论文标题换行已完整拼接于上一段。 -->

<a id="section-33"></a>

## Vapnik 理论应用于深度学习：排列的复杂度

![image](<Images/06_DL/image_024.jpg>)

- 使用阶跃函数作为激活函数、具有 $\omega$ 个参数的多层前馈神经网络的 VC 维：

$V\le2\omega\log_2(e\omega)$，可能非常大……

> **译注：** 该数值界照原页保留；原页未完整交代网络结构假设，不应直接用于任意 ReLU 或 sigmoid 网络。
