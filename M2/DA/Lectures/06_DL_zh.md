# 深度学习：原文与中文逐段对照

> 正文按原课件顺序排列，英文或法语原文后紧跟中文；例子、练习、重复正文、公式、图表及文献均保留。图中文字保留原图语言。原课件错误与必要辨析以独立“译注”标明。

[原 PDF](06_DL.pdf) · [原文转换稿](06_DL.md) · [逐块对应清单](Translation-audit/2026-09-28-coverage.json) · [课程目录](../README.md)

**本讲目录**

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

**重点定理与概念解释速查：**

- [核岭回归四要素练习解答与深度前馈网络复合表示](#reading-compositional-representation)
- [通用逼近定理（Stone–Weierstrass、Cybenko、Barron）：存在性与维数代价](#reading-universal-approximation-cybenko-barron)
- [反向传播（Backpropagation）链式法则矩阵推导与梯度消失机制](#reading-backpropagation-chain-rule)
- [Bottou–Bousquet 三项误差分解（近似、估计与优化误差）及计算预算权衡](#reading-bottou-bousquet-three-errors)
- [深度学习中的显式／隐式正则化与典型架构（CNN 卷积权重共享、自编码器与 PCA 的关系）](#reading-dl-regularization-and-architectures)
- [深度学习三大谜题解析：深度指数优势、非凸鞍点逃逸与过参数化泛化](#reading-three-mysteries-of-dl)

M2 CHPS

**[Data & Apprentissage] Introduction `a la science des donn´ees et `a l’apprentissage**

**数据科学与机器学习导论**

Nicolas Vayatis

<a id="section-01"></a>

Deep learning

## 深度学习

<a id="section-02"></a>

**”Big picture” of Learning**

## 学习的“全景图”

![image](<Images/06_DL/image_001.jpg>)

Machine Learning

机器学习

<a id="section-03"></a>

What we have seen so far

## 此前学过的内容

**Supervised machine learning Setup**

### 监督机器学习：设定

- Data: $( X _ { 1 } , Y _ { 1 } ) , \dots , ( X _ { 1 } , Y _ { 1 } )$ with $X _ { j }$ being a vector of variables (factors) for observation i, and $Y _ { i }$ being the label of $X _ { j }$

  数据：$( X _ { 1 } , Y _ { 1 } ) , \dots , ( X _ { 1 } , Y _ { 1 } )$，其中 $X _ { j }$ 是第 i 个观测的变量（因素）向量，$Y _ { i }$ 是 $X _ { j }$ 的标签。

> **译注：** 原页数据序列的末项重复写成第一项；按上下文应为第 n 个样本，原记号保留以便核对。

- Hypothesis class: set of functions $h \in \mathcal H$

  假设类：函数集合 $h \in \mathcal H$。
- Loss of a function h at a data point $( X , Y )$

  函数 h 在数据点 $( X , Y )$ 上的损失。

$$
\ell (h (X), Y) \geq 0
$$

- Empirical risk of a function h over the data:

  函数 h 在数据上的经验风险：

$$
\widehat {L} _ {n} (h) = \frac {1}{n} \sum_ {i = 1} ^ {n} \ell (h (X _ {i}), Y _ {i})
$$

What is a Machine Learning Method:

### 什么是机器学习方法？

- Problem characterized by three ingredients:

  问题由三个要素刻画：
  - Loss

    损失。
  - Hypothesis space

    假设空间。
  - Regularization

    正则化。
- ML algorithm characterized by an optimization strategy to solve the minimization of regularized loss over the hypothesis space

  机器学习算法由一种优化策略刻画，该策略在假设空间上最小化正则化损失。

<a id="section-04"></a>

**Machine Learning Methods Examples seen so far**

## 机器学习方法：此前学过的例子

- General hypothesis space with function selected through Empirical Risk Minimization (ERM) (could be shallow or deep)

  一般假设空间，通过经验风险最小化（ERM）选择函数，可以是浅层或深层方法。
- (Sparse) Linear models with parameters estimated through (penalized) least square minimization

  （稀疏）线性模型，通过（惩罚）最小二乘最小化估计参数。
- Kernel ridge regression - Exercise: What are the hypothesis space, the loss, the regularization, and the optimization method in that case?

  核岭回归。练习：这种情况下的假设空间、损失、正则化和优化方法分别是什么？

The latter is an example of popular and eficient shallow learning method.

最后一种是流行且高效的浅层学习方法的例子。

<a id="section-05"></a>

Deep Learning: Introducing the main concepts

## 深度学习：主要概念介绍

<a id="network-function"></a>

**Deep Feedforward Network**

### 深度前馈网络

![image](<Images/06_DL/image_002.jpg>)

- Hypothesis space: functions of the form

  假设空间：如下形式的函数。

$$
h (x, \theta) = \sigma_ {m} \circ A _ {m} \circ \sigma_ {m - 1} \circ \dots \circ A _ {2} \circ \sigma_ {1} \circ A _ {1} x
$$

where $\theta = \left( A _ { 1 } , \ldots , A _ { m } \right)$ sequence of parameters to be estimated through learning

其中 $\theta = \left( A _ { 1 } , \ldots , A _ { m } \right)$ 是需要通过学习估计的参数序列。

- We denote by $\sigma = \left( \sigma _ { 1 } , \ldots , \sigma _ { m } \right)$ the so-called activation functions which are hyperparameters related to the choice of a network architecture (which includes the number and size of the layers - see below).

  用 $\sigma = \left( \sigma _ { 1 } , \ldots , \sigma _ { m } \right)$ 表示所谓激活函数；它们是与网络架构选择有关的超参数，架构选择包括层数及各层大小，见下文。

<a id="training-objective"></a>

**Deep Feedforward Network**

### 深度前馈网络

![image](<Images/06_DL/image_003.jpg>)

- Optimization objective (far from convex! where is the regularizer?):

  优化目标（远非凸的！正则化项在哪里？）：

$$
\min _ {\theta} \frac {1}{n} \sum_ {i = 1} ^ {n} \ell (h (X _ {i}, \theta), Y _ {i})
$$

- Optimization method based on stochastic gradient descent (iterates over data points)

  基于随机梯度下降的优化方法：在数据点上迭代。

$$
\theta_ {i + 1} = \theta_ {i} - \eta \frac {\partial \ell (h (X _ {i} , \theta) , Y _ {i})}{\partial \theta} (\theta_ {i})
$$

<a id="section-06"></a>

Deep Learning:

## 深度学习

Why is it popular?

### 为什么流行？

**Deep means ’many layers’ (compositions) between input and output...**

### “深”意味着输入与输出之间有“许多层”（复合）……

Deep Neural Network

深度神经网络

![image](<Images/06_DL/image_004.jpg>)

Hidden Layer 1 Hidden Layer 2 Hidden Layer 3

隐藏层 1；隐藏层 2；隐藏层 3。

![image](<Images/06_DL/image_005.jpg>)

![image](<Images/06_DL/image_006.jpg>)

edges

边缘

![image](<Images/06_DL/image_007.jpg>)

combinations of edges

边缘的组合

![image](<Images/06_DL/image_008.jpg>)

object models

对象模型

<a id="reading-compositional-representation"></a>

**Supplement — Solution to the Kernel Ridge Regression Exercise (Four ML Ingredients) and Compositional Feature Learning in Deep Feedforward Networks.**

**补充——核岭回归四要素练习解答与深度前馈网络中的复合特征表示学习。**

Sections 3–6 contrast classical **shallow learning** (where a linear predictor acts on a fixed, pre-specified feature map $\Phi(x)$) with **deep learning** (where the feature representation itself is learned end-to-end as a composition of parameterized nonlinear layers). First, let us answer the **Exercise in Section 4** by comparing **Kernel Ridge Regression (KRR)** and **Deep Feedforward Networks (DNN)** across the four fundamental ingredients of any machine learning method:

第 3 至第 6 节将经典**浅层学习**（在预先固定的特征映射 $\Phi(x)$ 上拟合线性预测器）与**深度学习**（将特征表示本身建模为多层带参非线性变换的复合，并端到端联合学习）进行了对比。首先，我们通过对比**核岭回归（KRR）**与**深度前馈网络（DNN）**在机器学习四要素上的差异，完整解答**第 4 节的课堂练习**：

| ML Ingredient / 机器学习四要素 | Kernel Ridge Regression (Section 4 Exercise Answer) / 核岭回归（第 4 节练习解答） | Deep Feedforward Network (Sections 5–6) / 深度前馈神经网络（第 5–6 节） |
| --- | --- | --- |
| **1. Hypothesis Space $\mathcal{H}$** / **1. 假设空间 $\mathcal{H}$** | Reproducing Kernel Hilbert Space (RKHS) $\mathcal{H}_K$ associated with a fixed positive definite kernel $K$; by the Representer Theorem, $f(x) = \sum_{i=1}^n \alpha_i K(x_i, x)$ (**linear** in parameters $\alpha$). / 与固定正定核 $K$ 关联的再生核 Hilbert 空间 $\mathcal{H}_K$；由表示定理可写为 $f(x) = \sum_{i=1}^n \alpha_i K(x_i, x)$（关于参数 $\alpha$ **线性**）。 | Compositional functions $h(x, \theta) = (\sigma_m\circ A_m\circ\dots\circ\sigma_1\circ A_1)(x)$ where $A_l(z) = W^{(l)}z + b^{(l)}$ are affine maps and $\sigma_l$ are element-wise nonlinear activations (**highly nonlinear** in $\theta$). / 复合函数族 $h(x, \theta) = (\sigma_m\circ A_m\circ\dots\circ\sigma_1\circ A_1)(x)$，其中 $A_l(z) = W^{(l)}z + b^{(l)}$ 为仿射变换，$\sigma_l$ 为逐元素非线性激活函数（关于参数 $\theta$ **高度非线性**）。 |
| **2. Loss Function $\ell$** / **2. 损失函数 $\ell$** | Squared loss $\ell(f(x), y) = (y - f(x))^2$. / 平方损失 $\ell(f(x), y) = (y - f(x))^2$。 | Task-dependent differentiable loss: squared loss $(y - h(x,\theta))^2$ for regression, cross-entropy $-\sum_c y_c\log \hat{p}_c(x,\theta)$ for classification. / 取决于任务的可微损失：回归用平方损失，分类用交叉熵损失。 |
| **3. Regularization** / **3. 正则化** | Explicit squared RKHS norm penalty $\lambda \|f\|_{\mathcal{H}_K}^2 = \lambda \alpha^T K_n \alpha$ ($\lambda > 0$). / 显式 RKHS 范数平方惩罚 $\lambda \|f\|_{\mathcal{H}_K}^2 = \lambda \alpha^T K_n \alpha$（$\lambda > 0$）。 | Combination of explicit penalties (weight decay $\lambda\|\theta\|_2^2$) and architectural/algorithmic regularization (weight sharing, dropout, early stopping, SGD implicit bias). / 显式惩罚（权重衰减 $\lambda\|\theta\|_2^2$）与架构／算法隐式正则化（权重共享、Dropout、早停、SGD 隐式偏置）的结合。 |
| **4. Optimization Strategy** / **4. 优化策略** | **Strictly convex quadratic** problem with exact closed-form linear system solution $\hat{\alpha} = (K_n + n\lambda I_n)^{-1}Y$ ($O(n^3)$ time). / **严格凸二次优化**，具有精确闭式解 $\hat{\alpha} = (K_n + n\lambda I_n)^{-1}Y$（计算复杂度 $O(n^3)$）。 | **Nonconvex** optimization in $\theta \in \mathbb{R}^\omega$ solved iteratively via **Stochastic Gradient Descent (SGD)** and **Backpropagation** ($O(n\omega)$ per epoch). / 关于 $\theta \in \mathbb{R}^\omega$ 的**非凸优化**，通过**随机梯度下降（SGD）**配合**反向传播**迭代求解（每轮复杂度 $O(n\omega)$）。 |

**Why Nonlinear Activations $\sigma_l$ and Compositional Depth Matter**:
- **Without nonlinear activations, depth collapses**: If every activation $\sigma_l$ were the identity (or a linear map), then a $m$-layer network $A_m \circ A_{m-1} \circ \dots \circ A_1(x)$ with $A_l(z) = W^{(l)}z + b^{(l)}$ would simply collapse into a **single affine transformation** $W_{\mathrm{eff}} x + b_{\mathrm{eff}}$ where $W_{\mathrm{eff}} = W^{(m)}W^{(m-1)}\cdots W^{(1)}$. Thus, element-wise nonlinearities $\sigma_l$ (such as ReLU $\max(0, z)$ or sigmoid) are essential to expand the expressive power beyond linear models.
- **Hierarchical Representation Learning**: Rather than hand-crafting features or choosing a fixed kernel $K(x, x')$, an $m$-layer network learns a sequence of progressively more invariant and abstract representations $h^{(1)}(x) = \sigma_1(A_1 x) \mapsto h^{(2)}(x) = \sigma_2(A_2 h^{(1)}(x)) \mapsto \dots \mapsto h^{(m-1)}(x)$. As illustrated on the visual cortex / CNN example in Section 6, Layer 1 learns localized **oriented edges** (Gabor-like filters), Layer 2 composes edges into **corners, contours, and textures**, Layer 3 assembles them into **object parts** (eyes, wheels, noses), and the final layer performs linear classification on top of these disentangled high-level features.

**为什么非线性激活函数 $\sigma_l$ 与复合深度至关重要**：
- **若无非线性激活，多层网络会坍缩为单层线性模型**：如果每一层的激活函数 $\sigma_l$ 都是恒等映射（或线性映射），那么 $m$ 层复合 $A_m \circ A_{m-1} \circ \dots \circ A_1(x)$（其中 $A_l(z) = W^{(l)}z + b^{(l)}$）在代数上会直接坍缩为**单一仿射变换** $W_{\mathrm{eff}} x + b_{\mathrm{eff}}$（其中 $W_{\mathrm{eff}} = W^{(m)}W^{(m-1)}\cdots W^{(1)}$）。因此，逐分量非线性激活函数 $\sigma_l$（如 ReLU $\max(0,z)$ 或 Sigmoid）是突破线性模型表达瓶颈的必要条件。
- **层次化特征表示学习**：深度网络不再依赖人工设计特征或固定核函数 $K(x, x')$，而是逐层学习由低级到高级、不变性逐渐增强的中间表示 $h^{(1)}(x) = \sigma_1(A_1 x) \mapsto h^{(2)}(x) = \sigma_2(A_2 h^{(1)}(x)) \mapsto \dots \mapsto h^{(m-1)}(x)$。正如第 6 节视觉示例中所示：第 1 隐藏层自发学到局部**朝向边缘**（类似 Gabor 滤波器），第 2 隐藏层将边缘复合成**角点、轮廓与纹理**，第 3 隐藏层进一步组合成**物体局部部件**（如眼睛、车轮），最后一层只需在这些高度解耦的高层语义特征上做线性分类。

<a id="section-07"></a>

**Success of deep learning (1/3) Computer Vision**

## 深度学习的成功（1/3）：计算机视觉

![image](<Images/06_DL/image_009.jpg>)

<a id="section-08"></a>

**Success of deep learning (2/3) Speech recognition**

## 深度学习的成功（2/3）：语音识别

![image](<Images/06_DL/image_010.jpg>)

| System | Clean (94) | Noisy (82) | Combined (176) |
| --- | --- | --- | --- |
| Apple Dictation | 14.24 | 43.76 | 26.73 |
| Bing Speech | 11.73 | 36.12 | 22.05 |
| Google API | 6.64 | 30.47 | 16.72 |
| wit.ai | 7.94 | 35.06 | 19.41 |
| Deep Speech | 6.56 | 19.06 | 11.85 |

| 系统 | 清晰语音（94） | 含噪语音（82） | 合并（176） |
| --- | --- | --- | --- |
| Apple Dictation | 14.24 | 43.76 | 26.73 |
| Bing Speech | 11.73 | 36.12 | 22.05 |
| Google API | 6.64 | 30.47 | 16.72 |
| wit.ai | 7.94 | 35.06 | 19.41 |
| Deep Speech | 6.56 | 19.06 | 11.85 |

<a id="section-09"></a>

**Success of deep learning (3/3) Natural Language processing**

## 深度学习的成功（3/3）：自然语言处理

![image](<Images/06_DL/image_011.jpg>)

<a id="section-10"></a>

**Shallow vs. Deep Learning Vapnik vs. LeCun**

## 浅层与深度学习：Vapnik 与 LeCun

The first algorithms to reach human performance on a visual task

首批在视觉任务上达到人类表现的算法。

LeCun, Boser, et al. (1989). Backpropagation Applied to Handwritten Zip Code Recognition, in Neural Computation.

LeCun、Boser 等（1989）. Backpropagation Applied to Handwritten Zip Code Recognition（将反向传播应用于手写邮政编码识别），发表于 Neural Computation。

Architecture: 1000 units - 70,000 connections

架构：1000 个单元，70,000 条连接。

- C. Cortes and V. Vapnik (1995). Support-Vector Networks, in Machine Learning Journal.

  C. Cortes 与 V. Vapnik（1995）. Support-Vector Networks（支持向量网络），发表于 Machine Learning。

架构：1 个核，2 个参数。

![USPS 手写邮政编码样本，来自原 PDF 第 15 页](<Images/06_DL/pdf_p15_usps.jpg>)

USPS ZIP code database

USPS 邮政编码数据库。

> **译注：** “达到人类表现”和“2 个参数”均为原页历史性概括，不能据此认为训练后的 SVM 只有两个系数。

<a id="section-11"></a>

**Goal for the class today**

## 本讲目标

- Develop insights about deep learning and neural networks: when it works and when it does not work, and what it means to ”work” (open discussion)

  加深对深度学习与神经网络的理解：什么时候有效，什么时候无效，以及“有效”意味着什么（开放讨论）。
- Practical guide to deep learning optimization and engineering

  深度学习优化与工程的实践指南。
- Learn about the three mysteries of deep learning... and connect to the machine learning concepts seen so far (such as approximation error, complexity, and regularization)

  了解深度学习的三个谜题，并将其与此前学过的机器学习概念联系起来，例如近似误差、复杂度与正则化。

<a id="section-12"></a>

**Historical perspective on neural networks**

## 神经网络的历史视角

**• Cybernetics (1940s-1960s)**

### 控制论（20 世纪 40—60 年代）

- Achievement: modeling and training one neuron

  成就：对单个神经元建模并训练。
- Key algorithm: Perceptron

  关键算法：感知机。
- Paper: Rosenblatt (1958)

  论文：Rosenblatt（1958）。

**• Connectionism (1980s)**

### 联结主义（20 世纪 80 年代）

- Achievement: training one or two hidden layers

  成就：训练一层或两层隐藏层。
- Key algorithm: Backpropagation

  关键算法：反向传播。
- Paper: Rumelhart-Hinton-Williams (1986)

  论文：Rumelhart、Hinton、Williams（1986）。

**• Deep Learning (2007-....)**

### 深度学习（2007 年起）

- Achievement: training multiple layers of representation

  成就：训练多层表示。
- Key algorithm: Stochastic gradient

  关键算法：随机梯度。
- Papers: Hinton (2006), Bengio-LeCun (2007)

  论文：Hinton（2006）、Bengio–LeCun（2007）。

<a id="section-13"></a>

First wave: 1960s

## 第一波：20 世纪 60 年代

The Perceptron

感知机

**Primitive neural network Single neuron Perceptron**

### 原始神经网络：单神经元感知机

![image](<Images/06_DL/image_012.jpg>)

<a id="section-14"></a>

Second wave: 1980’s

## 第二波：20 世纪 80 年代

Multilayer perceptrons

多层感知机

1. Theory: Universal approximators

   理论：通用逼近器。
2. Algorithm: Backpropagation algorithm

   算法：反向传播算法。

<a id="section-15"></a>

Second wave: 1980’s

## 第二波：20 世纪 80 年代

Multilayer perceptrons

多层感知机

1. Existence theorems of universal approximators

### 1. 通用逼近器的存在性定理

**Stone-Weierstrass theorem**

### Stone–Weierstrass 定理

- Consider any continuous function $f ~ : ~ [ a , b ]  \mathbb { R }$ , then for any $\varepsilon > 0$ , there exists a polynomial $P$ such that:

  考虑任意连续函数 $f ~ : ~ [ a , b ] \to \mathbb { R }$，则对任意 $\varepsilon > 0$，存在多项式 $P$，使得：

$$
\sup _ {x \in [ a, b ]} | f (x) - P (x) | <   \varepsilon .
$$

<a id="section-16"></a>

**Single-Layer Neural Network Definition**

## 单层神经网络的定义

Single-layer neural network: Let σ a ’smooth’ activation function. A single-layer neural network with N units and an activation function σ, is a function of this form:

单层神经网络：设 σ 是一个“光滑”激活函数。具有 N 个单元、激活函数为 σ 的单层神经网络，是如下形式的函数：

$$
h (x) = \sum_ {k = 1} ^ {N} \sigma \left(a _ {k} ^ {T} x + b\right), \forall x \in \mathbb {R} ^ {d}
$$

where $a \in \mathbb { R } ^ { d } , \ b \in \mathbb { R }$ , N integer. The number N corresponds to the number of units in the hidden layer of the network.

其中 $a \in \mathbb { R } ^ { d } , \ b \in \mathbb { R }$，N 为整数。数目 N 对应网络隐藏层中的单元数。

> **译注：** 原页公式省略了输出权重，且偏置统一写成 b；通用逼近中常用的形式为 $h(x)=c_0+\sum_{k=1}^N c_k\sigma(a_k^Tx+b_k)$。此外，图示 ReLU 在零点并不光滑。

![image](<Images/06_DL/image_013.jpg>)

![image](<Images/06_DL/image_014.jpg>)

<a id="section-17"></a>

**Single-Layer Neural Network are universal approximators**

## 单层神经网络是通用逼近器

- Cybenko’s theorem: consider any continuous function $f : [ 0 , 1 ] ^ { d } \to \mathbb { R }$ , then for any $\varepsilon > 0$ , there exists a single-layer neural network $\begin{array} { r } { \boldsymbol { h } ( \boldsymbol { x } ) = \sum _ { k = 1 } ^ { N } \overset { \cdot } { \boldsymbol { \sigma } } ( \boldsymbol { a } _ { k } ^ { T } \boldsymbol { x } + \boldsymbol { b } ) } \end{array}$ (i.e. some N, a, b) such that:

  Cybenko 定理：考虑任意连续函数 $f : [ 0 , 1 ] ^ { d } \to \mathbb { R }$，则对任意 $\varepsilon > 0$，存在单层神经网络 $\begin{array} { r } { \boldsymbol { h } ( \boldsymbol { x } ) = \sum _ { k = 1 } ^ { N } \overset { \cdot } { \boldsymbol { \sigma } } ( \boldsymbol { a } _ { k } ^ { T } \boldsymbol { x } + \boldsymbol { b } ) } \end{array}$，也就是存在某些 N、a、b，使得：

$$
\sup _ {x \in [ a, b ]} | f (x) - h (x) | <   \varepsilon .
$$

> **译注：** 原页上确界区域写成了一维 $[a,b]$，应与前面的输入域 $[0,1]^d$ 对应；通用逼近还需对激活函数施加相应条件。

- Further work by Hornik-Stinchcombe-White (1989), Barron (1993).

  后续工作：Hornik、Stinchcombe、White（1989），Barron（1993）。

<a id="reading-universal-approximation-cybenko-barron"></a>

**Supplement — Universal Approximation Theorems (Stone–Weierstrass, Cybenko, Leshno–Lin–Pinkus–Schocken, Barron): What They Guarantee and What They Do Not.**

**补充——通用逼近定理（Stone–Weierstrass、Cybenko、Leshno 等、Barron）：它们保证了什么，又没有保证什么？**

Write a general single-hidden-layer neural network with $N$ hidden units (neurons) as:

将具有 $N$ 个隐藏单元（神经元）的一般单隐藏层神经网络完整写为：

$$
h_N(x) = \sum_{k=1}^N c_k\,\sigma\!\left(a_k^T x + b_k\right) + c_0, \qquad a_k \in \mathbb{R}^d,\; b_k, c_k \in \mathbb{R}.
$$

How do classical approximation results justify this architecture?

经典逼近理论是如何支撑这一架构的？

1. **From Stone–Weierstrass (1885/1937) to Cybenko (1989) & Hornik et al. (1989)**:
   - **Stone–Weierstrass** states that any subalgebra of $C(K)$ (continuous functions on a compact set $K\subset\mathbb{R}^d$) that separates points and contains a non-zero constant is dense in $C(K)$ under the supremum norm $\|f - P\|_\infty = \sup_{x\in K}|f(x) - P(x)|$ (e.g., polynomials).
   - **Cybenko (1989)** proved that if $\sigma : \mathbb{R}\to\mathbb{R}$ is any continuous **sigmoidal** function ($\lim_{z\to-\infty}\sigma(z)=0$ and $\lim_{z\to+\infty}\sigma(z)=1$), the linear span of ridge functions $\{\sigma(a^T x + b)\}$ is dense in $C([0,1]^d)$: for every $f\in C([0,1]^d)$ and $\varepsilon > 0$, there exists $N\in\mathbb{N}$ and parameters $(a_k, b_k, c_k)$ such that $\sup_{x\in[0,1]^d}|f(x) - h_N(x)| < \varepsilon$. (Cybenko's proof uses the Hahn–Banach and Riesz Representation Theorems: if the closure of the span were not all of $C([0,1]^d)$, there would exist a non-zero signed Radon measure $\mu$ on $[0,1]^d$ orthogonal to $\sigma(a^T x + b)$ for all $a,b$, which forces the Fourier transform of $\mu$ to vanish everywhere, hence $\mu \equiv 0$.)
   - **Leshno, Lin, Pinkus & Schocken (1993)** gave the definitive characterization: a continuous activation $\sigma$ provides universal approximation for single-hidden-layer networks if and only if **$\sigma$ is not a polynomial**! (If $\sigma$ were a polynomial of degree $p$, then $\sum_{k=1}^N c_k\sigma(a_k^T x + b_k)$ would always be a polynomial of degree at most $p$, no matter how large $N$ is, so it could never approximate functions outside $\mathbb{P}_p$; this also explains why **ReLU** $\sigma(z)=\max(0,z)$ is a universal approximator.)

   **从 Stone–Weierstrass（1885/1937）到 Cybenko（1989）与 Leshno 等（1993）**：
   - **Stone–Weierstrass 定理**指出，紧集 $K\subset\mathbb{R}^d$ 上连续函数空间 $C(K)$ 的任意子代数，只要能分离点且包含非零常数（如多项式族），就在一致范数 $\|f - P\|_\infty = \sup_{x\in K}|f(x) - P(x)|$ 下在 $C(K)$ 中稠密。
   - **Cybenko 定理（1989）**证明：只要 $\sigma : \mathbb{R}\to\mathbb{R}$ 是任意连续的 **S 型（sigmoidal）函数**（满足 $\lim_{z\to-\infty}\sigma(z)=0$ 且 $\lim_{z\to+\infty}\sigma(z)=1$），由岭函数 $\{\sigma(a^T x + b)\}$ 张成的线性子空间就在 $C([0,1]^d)$ 中稠密——即对任意 $f\in C([0,1]^d)$ 与 $\varepsilon > 0$，总存在有限宽度 $N$ 使 $\sup_{x\in[0,1]^d}|f(x) - h_N(x)| < \varepsilon$。（Cybenko 的证明利用了 Hahn–Banach 定理与 Riesz 表示定理：若张成空间的闭包不等于整个 $C([0,1]^d)$，则必存在非零符号 Radon 测度 $\mu$ 对所有 $a,b$ 满足 $\int \sigma(a^T x + b)\,d\mu(x) = 0$，进而推出 $\mu$ 的傅里叶变换处处为零，与 $\mu\neq 0$ 矛盾。）
   - **Leshno, Lin, Pinkus & Schocken（1993）**给出了充要条件：连续激活函数 $\sigma$ 能使单隐藏层网络成为通用逼近器，当且仅当 **$\sigma$ 不是多项式函数**！（若 $\sigma$ 是 $p$ 次多项式，无论隐藏单元数 $N$ 多大，线性组合 $\sum_{k=1}^N c_k\sigma(a_k^T x + b_k)$ 永远只能是次数不超过 $p$ 的多项式；这也直接解释了为什么分段线性的 **ReLU** $\sigma(z)=\max(0,z)$ 同样是通用逼近器。）

**Constructive 1D Intuition: How Shifted Sigmoids or ReLUs Build Localized Bump / Piecewise Linear Approximations（一维构造性直觉——平移 Sigmoid 或 ReLU 如何拼出局部阶梯／分段线性逼近）**

Why can a sum of global sigmoids or ReLUs approximate any local shape on $[0, 1]$?

为什么全局延伸的 Sigmoid 或 ReLU 的线性组合能够逼近 $[0,1]$ 上的任意局部函数？

1. **With Sigmoid $\sigma(z) = (1+e^{-z})^{-1}$**: By choosing a large slope $a \gg 1$ and shifting the bias to $-a \tau_k$, the function $\sigma(a(x - \tau_k))$ acts as a smooth **step function** transitioning from $0$ to $1$ around $x = \tau_k$ (with $\sigma(0) = 1/2$ right at the jump point $x = \tau_k$, and exponentially decaying tails outside). Taking the difference of two shifted sigmoids at $\tau_k < \tau_{k+1}$ creates an **approximately localized window (bump) function** on $(\tau_k, \tau_{k+1})$:

   **使用 Sigmoid $\sigma(z) = (1+e^{-z})^{-1}$**：取很大的斜率 $a \gg 1$ 并将偏置设为 $-a \tau_k$，$\sigma(a(x - \tau_k))$ 就逼近在 $x = \tau_k$ 附近从 $0$ 跳变到 $1$ 的**光滑阶跃函数**（在跳变中心点 $x = \tau_k$ 处取值为 $\sigma(0) = 1/2$，在区间外具有指数衰减尾，并非严格紧支撑）。将两个相邻位置 $\tau_k < \tau_{k+1}$ 的 Sigmoid 函数相减，即可构造出集中在 $(\tau_k, \tau_{k+1})$ 上的**近似局部矩形窗函数（bump function）**：

   $$
   B_k(x) := \sigma\!\big(a(x - \tau_k)\big) - \sigma\!\big(a(x - \tau_{k+1})\big).
   $$

   *Endpoint & Jump Caveat for Uniform Approximation on $[0, 1]$*: If one naively sets the outer grid endpoints directly to $\tau_0 = 0$ and $\tau_N = 1$, then even for the constant function $f(x)\equiv 1$, the telescoping sum $\sum_{k=0}^{N-1} B_k(x) = \sigma(ax) - \sigma(a(x-1))$ evaluates to $\sigma(0) - \sigma(-a) \to 1/2 \neq 1$ at $x=0$ (and similarly $1/2$ at $x=1$) as $a\to\infty$! To achieve **uniform approximation on the entire closed interval $[0, 1]$**, we extend the outer boundary points slightly outside $[0, 1]$: choose $\delta > 0$ (e.g., $\delta = 1/N$) and set $\tau_0 = -\delta < 0 < \tau_1 < \dots < \tau_{N-1} < 1 < \tau_N = 1+\delta$ with sample points $t_k \in [\tau_k, \tau_{k+1}]\cap[0,1]$. Then on $[0, 1]$:
   - The partition of unity satisfies $\sum_{k=0}^{N-1} B_k(x) = \sigma(a(x+\delta)) - \sigma(a(x-1-\delta)) \to 1$ **uniformly for all $x\in[0,1]$** as $a\to\infty$;
   - At any interior jump point $x = \tau_k$ ($1 \le k \le N-1$), $B_{k-1}(\tau_k) \to 1/2$ and $B_k(\tau_k) \to 1/2$, so $\sum_{j=0}^{N-1} f(t_j) B_j(\tau_k) \to \frac{1}{2}\big(f(t_{k-1}) + f(t_k)\big)$, which differs from $f(\tau_k)$ by at most $\frac{1}{2}\omega_f(\max_j(\tau_{j+1}-\tau_j)) \to 0$ by the uniform continuity of $f$ on $[0,1]$. Thus, first choosing the grid fine enough ($N$ large) and then choosing the slope $a$ large enough guarantees $\sup_{x\in[0,1]} \big|f(x) - \sum_{k=0}^{N-1} f(t_k) B_k(x)\big| < \varepsilon$ using $2N$ hidden units (or $N+1$ units if adjacent $\sigma(a(x-\tau_k))$ terms are merged into the telescoping step sum $f(t_0)\sigma(a(x+\delta)) + \sum_{k=1}^{N-1}(f(t_k)-f(t_{k-1}))\sigma(a(x-\tau_k)) - f(t_{N-1})\sigma(a(x-1-\delta))$).

   **闭区间 $[0, 1]$ 上一致逼近的端点延拓与跳变点处理**：需要注意，如果直接把网格外端点取在 $\tau_0 = 0$ 与 $\tau_N = 1$，那么哪怕对常值函数 $f(x)\equiv 1$，裂项求和 $\sum_{k=0}^{N-1} B_k(x) = \sigma(ax) - \sigma(a(x-1))$ 在端点 $x=0$ 处当 $a\to\infty$ 时也只会趋于 $\sigma(0) = 1/2 \neq 1$（在 $x=1$ 处同理趋于 $1/2$），无法在整个闭区间 $[0,1]$ 上一致逼近！为了在**整个闭区间 $[0,1]$ 上实现一致逼近**，只需将左右外边界向 $[0,1]$ 外侧略微延拓 $\delta > 0$（如取 $\delta = 1/N$）：设 $\tau_0 = -\delta < 0 < \tau_1 < \dots < \tau_{N-1} < 1 < \tau_N = 1+\delta$，并在每段上取采样点 $t_k \in [\tau_k, \tau_{k+1}]\cap[0,1]$。此时对所有 $x\in[0,1]$：
   - 单位分解和 $\sum_{k=0}^{N-1} B_k(x) = \sigma(a(x+\delta)) - \sigma(a(x-1-\delta))$ 当 $a\to\infty$ 时**在 $[0,1]$ 上一致收敛到 $1$**；
   - 即便在内部分界点 $x = \tau_k$（$1\le k\le N-1$）处，由于 $B_{k-1}(\tau_k)\to 1/2$ 且 $B_k(\tau_k)\to 1/2$，加权和趋于左右相邻段函数值的平均 $\frac{1}{2}\big(f(t_{k-1}) + f(t_k)\big)$；由连续函数 $f$ 在紧集 $[0,1]$ 上的一致连续性，当网格加密时该平均值与 $f(\tau_k)$ 的偏差一致趋于 $0$。因此，先取足够密的网格 $N$ 再取足够大的斜率 $a$，即可保证 $\sup_{x\in[0,1]}\big|f(x) - \sum_{k=0}^{N-1} f(t_k)B_k(x)\big| < \varepsilon$。
2. **With ReLU $\sigma(z) = (z)_+ = \max(0, z)$**: Any continuous piecewise-linear function on $0 = t_0 < t_1 < \dots < t_N = 1$ with slopes $s_k = \frac{f(t_{k+1}) - f(t_k)}{t_{k+1} - t_k}$ can be written **exactly** as a 1-hidden-layer ReLU network:

   **使用 ReLU $\sigma(z) = (z)_+ = \max(0, z)$**：网格 $0 = t_0 < t_1 < \dots < t_N = 1$ 上的任意连续分段线性插值函数（各段斜率为 $s_k = \frac{f(t_{k+1}) - f(t_k)}{t_{k+1} - t_k}$）都可以**精确**写成如下单隐藏层 ReLU 网络：

   $$
   h_N(x) = f(t_0) + s_0(x - t_0)_+ + \sum_{k=1}^{N-1} (s_k - s_{k-1})(x - t_k)_+.
   $$

2. **What Universal Approximation Does NOT Guarantee (and Barron's Theorem, 1993)**:
   - **Curse of Dimensionality in Width $N$**: For a general $1$-Lipschitz function on $[0,1]^d$, achieving uniform error $\varepsilon$ with a 1-hidden-layer network requires $N = \Omega(\varepsilon^{-d})$ hidden units—exponential in the input dimension $d$!
   - **Barron's Theorem (1993)** showed that if $f$ belongs to the **Barron space** (functions whose Fourier transform $\tilde{f}(\omega)$ has finite first absolute moment $C_f = \int_{\mathbb{R}^d} \|\omega\|_2 |\tilde{f}(\omega)|\,d\omega < \infty$), then there exists a 1-hidden-layer network of width $N$ achieving integrated squared error $\|f - h_N\|_{L^2(\mu)}^2 \le \frac{(2C_f)^2}{N}$, an approximation rate $O(1/N)$ whose exponent is **independent of dimension $d$**!
   - **Existence $\neq$ Learnability**: Universal approximation is purely an **existence theorem** in approximation theory ($\mathcal{E}_{\mathrm{app}} \to 0$ as $N\to\infty$). It says nothing about whether gradient descent on a finite sample $D_n$ can find those weights ($\mathcal{E}_{\mathrm{opt}}$) or whether such a massive shallow network will generalize ($\mathcal{E}_{\mathrm{est}}$).

   **通用逼近定理没有保证什么（以及 Barron 定理，1993）**：
   - **宽度 $N$ 的维数灾难**：对 $[0,1]^d$ 上的一般 $1$-Lipschitz 连续函数，单隐藏层网络要达到一致逼近精度 $\varepsilon$，在最坏情况下所需的神经元数高达 $N = \Omega(\varepsilon^{-d})$——随输入维数 $d$ 呈指数爆炸！
   - **Barron 定理（1993）**指出：若目标函数 $f$ 的傅里叶变换 $\tilde{f}(\omega)$ 满足一阶绝对矩有限 $C_f = \int_{\mathbb{R}^d} \|\omega\|_2 |\tilde{f}(\omega)|\,d\omega < \infty$（即属于 **Barron 空间**），则存在宽度为 $N$ 的单隐藏层网络使其 $L^2$ 逼近误差满足 $\|f - h_N\|_{L^2(\mu)}^2 \le \frac{(2C_f)^2}{N}$——逼近速率 $O(1/N)$ 的阶数**与维数 $d$ 无关**！
   - **存在性 $\neq$ 可学习性**：通用逼近定理只是逼近论中的**存在性定理**（仅说明当 $N\to\infty$ 时近似误差 $\mathcal{E}_{\mathrm{app}} \to 0$）。它既不保证梯度下降能从有限样本中找到这组权重（优化误差 $\mathcal{E}_{\mathrm{opt}}$），也不保证如此宽的浅层网络在有限样本下不会严重过拟合（估计误差 $\mathcal{E}_{\mathrm{est}}$）。

<a id="backpropagation"></a>

2. Backpropagation algorithm:

### 2. 反向传播算法

The key to multilayer perceptron calibration • Hypothesis space: functions of the form

多层感知机参数校准的关键。假设空间：如下形式的函数。

$$
h (x, \theta) = \sigma \circ A _ {m} \circ \sigma \circ \dots \circ A _ {2} \circ \sigma \circ A _ {1} x
$$

where $\theta = \left( A _ { 1 } , \ldots , A _ { m } \right)$ sequence of parameters to be estimated through learning and $\sigma$ activation function applied componentwise

其中 $\theta = \left( A _ { 1 } , \ldots , A _ { m } \right)$ 是需要通过学习估计的参数序列，$\sigma$ 是逐分量施加的激活函数。

![image](<Images/06_DL/image_015.jpg>)

- Consider the square loss, then given a weight vector $\theta _ { 1 }$ , we can evaluate the error as:

  考虑平方损失。给定权重向量 $\theta _ { 1 }$，可以将误差计算为：

$$
\mathcal {L} \left(\theta_ {1}\right) = \frac {1}{n} \sum_ {i = 1} ^ {n} \left(h \left(X _ {i}, \theta_ {1}\right) - Y _ {i}\right) ^ {2}
$$

- The idea is to propagate the error backwards in the network to update $\theta _ { 1 }$ by the following rule:

  思路是在网络中将误差反向传播，按下式更新 $\theta _ { 1 }$：

$$
\theta_ {2} = \theta_ {1} - \eta \nabla_ {\theta} \mathcal {L} (\theta_ {1})
$$

where $\eta$ is the so-called learning rate.

其中 $\eta$ 是所谓学习率。

<a id="section-18"></a>

Optional material Computing the gradient with Backpropagation

## 选读材料：通过反向传播计算梯度

**Backpropagation Background: Chain rule**

### 反向传播背景：链式法则

- Consider the composition of three functions:

  考虑三个函数的复合：

$$
f (u) = \ell \circ \sigma \circ g (x)
$$

> **译注：** 原式混用 u 与 x；链式求导时应统一自变量。

with $t = \sigma \circ g ( u )$ and $z = g ( u )$ (everything in $\mathbb { R }$ here)

其中 $t = \sigma \circ g ( u )$，$z = g ( u )$，这里所有量都在 $\mathbb { R }$ 中。

- The chain rule provides the expression for the derivative of $f \colon$

  链式法则给出 $f \colon$ 的导数表达式：

$$
\frac {d f}{d u} (u) = \frac {d \ell}{d t} (t) \frac {d \sigma}{d z} (z) \frac {d g}{d u} (u) = \ell^ {\prime} (\sigma \circ g (u)) \sigma^ {\prime} (g (u)) g ^ {\prime} (u)
$$

**Backpropagation Background: Activation function**

### 反向传播背景：激活函数

**• Typical examples:**

#### 典型例子

![image](<Images/06_DL/image_016.jpg>)

- For the logistic activation function: $\sigma ( z ) = \frac { 1 } { 1 + e ^ { - z } }$ , we have by standard algebra:

  对逻辑激活函数 $\sigma ( z ) = \frac { 1 } { 1 + e ^ { - z } }$，通过基本代数运算得到：

$$
\sigma^ {\prime} (z) = \frac {d \sigma}{d z} (z) = \sigma (z) (1 - \sigma (z))
$$

- Consider a single unit (neuron): $h ( x , a ) = \sigma ( a ^ { T } x )$ which is connected to the output Y of the network

  考虑连接到网络输出 Y 的单个单元（神经元）$h ( x , a ) = \sigma ( a ^ { T } x )$。
- The error of the predictions produced by this neuron on the training data is the following:

  这个神经元在训练数据上的预测误差为：

$$
\mathcal {L} (a) = \frac {1}{n} \sum_ {i = 1} ^ {n} \ell (\sigma (a ^ {T} X _ {i}), Y _ {i})
$$

where $\ell ( t , y ) = ( t - y ) ^ { 2 }$ considering the square loss here.

其中 $\ell ( t , y ) = ( t - y ) ^ { 2 }$，这里考虑平方损失。

- Apply the chain rule with three compositions in the case where the last function is linear

  对三个函数复合、其中最后一个函数为线性的情形，应用链式法则。
- The gradient of $\mathcal { L }$ wrt a is given by:

  $\mathcal { L }$ 关于 a 的梯度为：

$$
\frac {\partial \mathcal {L}}{\partial a _ {j}} (a) = \frac {1}{n} \sum_ {i = 1} ^ {n} \frac {\partial \ell}{\partial t} (\sigma (a ^ {T} X _ {i}), Y _ {i}) \sigma^ {\prime} (a ^ {T} X _ {i}) X _ {i j}
$$

- Special case here: square loss, logistic activation function

  这里的特殊情形：平方损失、逻辑激活函数。

$$
\frac {\partial \ell}{\partial t} (t, Y _ {i}) = 2 (t - Y _ {i}) \text{且} \sigma^ {\prime} (z) = \sigma (z) (1 - \sigma (z))
$$

- The gradient update applied at input ’neurons’ is the following

  对输入“神经元”施加的梯度更新如下。

$$
\frac {\partial \mathcal {L}}{\partial a _ {j}} (a) = \frac {2}{n} \sum_ {i = 1} ^ {n} (z _ {i} - Y _ {i}) z _ {i} (1 - z _ {i}) X _ {i j}
$$

> **译注：** 上式是梯度的计算式，尚不是参数更新式；更新还需乘学习率并从当前权重中减去。

where $z _ { i } = \sigma \big ( \boldsymbol { a } ^ { T } X _ { i } \big )$

其中 $z _ { i } = \sigma \big ( \boldsymbol { a } ^ { T } X _ { i } \big )$。

选读材料结束。

End of optional material

选读材料结束。

<a id="section-19"></a>

**Backpropagation Discussion**

## 反向传播：讨论

- In case of multiple layers, it sufices to apply the chain rule upstream For more details: check Lecture notes by Jake Abernethy

  在多层情形下，只需向前面的层继续应用链式法则。更多细节参见 Jake Abernethy 的讲义。

https:

[Jake Abernethy 讲义目录](https://nbviewer.jupyter.org/format/slides/github/thejakeyboy/umich-eecs545-lectures/)

//nbviewer.jupyter.org/format/

<!-- 原转换稿此处的 URL 片段已完整拼接于上方链接。 -->

![image](<Images/06_DL/image_017.jpg>)

Forward

前向

![image](<Images/06_DL/image_018.jpg>)

Backward

反向

slides/github/thejakeyboy/

<!-- 原转换稿此处的 URL 片段已完整拼接于上方链接。 -->

umich-eecs545-lectures/

<!-- 原转换稿此处的 URL 片段已完整拼接于上方链接。 -->

**• But does the gradient descent converge to the optimal solution?**

### 但是，梯度下降会收敛到最优解吗？

<a id="reading-backpropagation-chain-rule"></a>

**Supplement — Matrix-Vector Backpropagation Recurrence, Computational Complexity ($O(\omega)$ vs. $O(\omega^2)$), and the Vanishing Gradient Phenomenon.**

**补充——多层反向传播的矩阵–向量递推公式、计算复杂度（$O(\omega)$ 对比 $O(\omega^2)$）与梯度消失机制。**

Section 18 derived the gradient for a single neuron; how does **Backpropagation (reverse-mode automatic differentiation)** scale to an $m$-layer network with $\omega$ total parameters?

第 18 节推导了单个神经元的梯度；当网络扩展到含 $m$ 层、共 $\omega$ 个参数的深层网络时，**反向传播（反向模式自动微分）**是如何高效运作的？

**Derivation: The Four Fundamental Equations of Multilayer Backpropagation（多层神经网络反向传播的四个基本递推方程推导）**

Let layer $l \in \{1, \dots, m\}$ take post-activation vector $a^{(l-1)}$ from layer $l-1$ (with $a^{(0)} = x$), compute pre-activation vector $z^{(l)} = W^{(l)} a^{(l-1)} + b^{(l)}$, and apply element-wise activation $a^{(l)} = \sigma(z^{(l)})$. For a single sample loss $\ell(a^{(m)}, y)$, define the **backpropagated error sensitivity vector** at layer $l$ as $\delta^{(l)} := \nabla_{z^{(l)}} \ell$:

设第 $l \in \{1, \dots, m\}$ 层接收第 $l-1$ 层的激活输出向量 $a^{(l-1)}$（其中输入层 $a^{(0)} = x$），计算线性预激活向量 $z^{(l)} = W^{(l)} a^{(l-1)} + b^{(l)}$，再经逐分量激活得到 $a^{(l)} = \sigma(z^{(l)})$。对单样本损失 $\ell(a^{(m)}, y)$，定义第 $l$ 层的**反向误差敏感度向量**为 $\delta^{(l)} := \nabla_{z^{(l)}} \ell$：

1. **Forward Pass ($l = 1 \to m$)**: Store intermediate pre-activations $z^{(l)}$ and activations $a^{(l)}$.

   **前向传播（$l = 1 \to m$）**：逐层计算并缓存中间预激活值 $z^{(l)}$ 与激活值 $a^{(l)}$。
2. **Output Layer Error ($l = m$)**: By the chain rule on $a^{(m)} = \sigma(z^{(m)})$ ($\odot$ denotes element-wise Hadamard product):

   **输出层误差（$l = m$）**：由 $a^{(m)} = \sigma(z^{(m)})$ 的链式法则（$\odot$ 表示逐元素 Hadamard 积）：

   $$
   \delta^{(m)} = \nabla_{a^{(m)}} \ell \odot \sigma'\!\big(z^{(m)}\big).
   $$
3. **Backward Error Propagation ($l = m-1 \to 1$)**: Since $z^{(l+1)} = W^{(l+1)} \sigma(z^{(l)}) + b^{(l+1)}$, the Jacobian $\frac{\partial z^{(l+1)}}{\partial z^{(l)}}$ is $W^{(l+1)} \operatorname{diag}(\sigma'(z^{(l)}))$. Multiplying its transpose by $\delta^{(l+1)}$ gives the backward recurrence:

   **误差反向递推（$l = m-1 \to 1$）**：由 $z^{(l+1)} = W^{(l+1)} \sigma(z^{(l)}) + b^{(l+1)}$，雅可比矩阵 $\frac{\partial z^{(l+1)}}{\partial z^{(l)}}$ 为 $W^{(l+1)} \operatorname{diag}(\sigma'(z^{(l)}))$。将其转置作用于 $\delta^{(l+1)}$ 即得反向递推式：

   $$
   \delta^{(l)} = \Big(\big(W^{(l+1)}\big)^T \delta^{(l+1)}\Big) \odot \sigma'\!\big(z^{(l)}\big).
   $$
4. **Parameter Gradients at Layer $l$**: Since $z_j^{(l)} = \sum_k W_{jk}^{(l)} a_k^{(l-1)} + b_j^{(l)}$, differentiating with respect to $W_{jk}^{(l)}$ and $b_j^{(l)}$ yields an outer product:

   **第 $l$ 层参数梯度**：由 $z_j^{(l)} = \sum_k W_{jk}^{(l)} a_k^{(l-1)} + b_j^{(l)}$，对 $W_{jk}^{(l)}$ 与 $b_j^{(l)}$ 求偏导即得外积形式：

   $$
   \nabla_{W^{(l)}} \ell = \delta^{(l)} \big(a^{(l-1)}\big)^T, \qquad \nabla_{b^{(l)}} \ell = \delta^{(l)}.
   $$

- **Why Backpropagation Is Crucial for Efficiency ($O(\omega)$ vs. $O(\omega^2)$)**:
  Computing $\nabla_\theta \ell$ by numerical finite differences $\frac{\ell(\theta + \epsilon e_p) - \ell(\theta)}{\epsilon}$ requires a separate $O(\omega)$ forward pass for each of the $\omega$ parameters, costing **$O(\omega^2)$ operations per sample** (for $\omega = 10^7$, $\omega^2 = 10^{14}$ operations per sample!). By reusing the cached activations $a^{(l-1)}$ from the forward pass and propagating $\delta^{(l)}$ backward in a single sweep, Backpropagation computes all $\omega$ partial derivatives in **$O(\omega)$ time**—only about $2\times$ to $3\times$ the cost of a single forward pass!
- **Why Deep Sigmoid Networks Suffer from Vanishing/Exploding Gradients (and How ReLU & Residual Connections Mitigate It)**:
  Writing $D_l := \operatorname{diag}\big(\sigma'(z^{(l)})\big) \in \mathbb{R}^{d_l \times d_l}$, the single-layer backward recurrence is $\delta^{(l)} = D_l \big(W^{(l+1)}\big)^T \delta^{(l+1)}$ (where $W^{(l+1)} \in \mathbb{R}^{d_{l+1}\times d_l}$, so $(W^{(l+1)})^T \in \mathbb{R}^{d_l \times d_{l+1}}$ matches $D_l$). Unrolling this recurrence from layer $m$ down to layer $1$ yields the ordered matrix product:
  $$
  \delta^{(1)} = D_1 \big(W^{(2)}\big)^T D_2 \big(W^{(3)}\big)^T \cdots D_{m-1} \big(W^{(m)}\big)^T \delta^{(m)} = \left(\prod_{l=1}^{m-1} D_l \big(W^{(l+1)}\big)^T\right) \delta^{(m)}.
  $$
  By submultiplicativity of the operator (spectral) norm, the sensitivity at layer $1$ is bounded by both the activation derivatives and the weight spectral norms:
  $$
  \big\|\delta^{(1)}\big\|_2 \le \left(\prod_{l=1}^{m-1} \|D_l\|_{\mathrm{op}}\right) \left(\prod_{l=2}^{m} \big\|W^{(l)}\big\|_{\mathrm{op}}\right) \big\|\delta^{(m)}\big\|_2.
  $$
  For the logistic sigmoid $\sigma(z) = (1+e^{-z})^{-1}$, the derivative $\sigma'(z) = \sigma(z)(1-\sigma(z))$ attains its global maximum of **$1/4 = 0.25$** at $z=0$ ($\|D_l\|_{\mathrm{op}} \le 1/4$), and decays exponentially to $0$ when $|z|$ is large (saturation). Consequently, under standard small or unit-scale initializations where $\|W^{(l)}\|_{\mathrm{op}} \lesssim 1$, the factor $\prod_{l=1}^{m-1}\|D_l\|_{\mathrm{op}} \le (1/4)^{m-1}$ shrinks the gradient bound exponentially with depth $m$ (**vanishing gradient**); conversely, attempting to compensate by initializing $\|W^{(l)}\|_{\mathrm{op}} \ge 4$ pushes the pre-activations $z^{(l)} = W^{(l)} a^{(l-1)} + b^{(l)}$ into the saturated tails ($|z^{(l)}| \gg 1$, making $\|D_l\|_{\mathrm{op}} \ll 1/4$) or triggers **exploding gradients** when $\prod_l \|D_l (W^{(l+1)})^T\|_{\mathrm{op}} > 1$. Replacing sigmoid with **ReLU** $\sigma(z) = \max(0, z)$ (whose derivative is $\sigma'(z) = 1$ on the active half-line $z > 0$), combined with variance-preserving initialization (He/Xavier), normalization layers, and **residual skip connections** ($z^{(l+1)} = z^{(l)} + \mathcal{F}(z^{(l)})$), substantially mitigates gradient vanishing and enabled the training of very deep networks (though care is still required to avoid "dying ReLU" units where $z \le 0$ persistently or exploding/vanishing products across badly scaled weight matrices).

- **为什么反向传播在计算上至关重要（$O(\omega)$ 对比 $O(\omega^2)$）**：
  若用数值有限差分 $\frac{\ell(\theta + \epsilon e_p) - \ell(\theta)}{\epsilon}$ 计算梯度 $\nabla_\theta \ell$，需要对 $\omega$ 个参数分别执行一次 $O(\omega)$ 的前向传播，单样本计算量高达 **$O(\omega^2)$**（当 $\omega = 10^7$ 时单样本需 $10^{14}$ 次运算！）。而反向传播通过复用前向缓存的 $a^{(l-1)}$ 并单趟反向传递 $\delta^{(l)}$，仅需 **$O(\omega)$ 时间**（约为单次前向传播的 $2$ 至 $3$ 倍）即可同时算出全部 $\omega$ 个偏导数！
- **为什么 Sigmoid 深层网络容易出现“梯度消失／爆炸”（以及 ReLU 与残差连接如何缓解它）**：
  记对角导数矩阵 $D_l := \operatorname{diag}\big(\sigma'(z^{(l)})\big) \in \mathbb{R}^{d_l \times d_l}$，单层反向递推式为 $\delta^{(l)} = D_l \big(W^{(l+1)}\big)^T \delta^{(l+1)}$（其中 $W^{(l+1)} \in \mathbb{R}^{d_{l+1}\times d_l}$，故转置 $(W^{(l+1)})^T \in \mathbb{R}^{d_l \times d_{l+1}}$ 与 $D_l$ 的维度精确匹配）。将该递推从第 $m$ 层逐层展开到第 $1$ 层，得到矩阵连乘：
  $$
  \delta^{(1)} = D_1 \big(W^{(2)}\big)^T D_2 \big(W^{(3)}\big)^T \cdots D_{m-1} \big(W^{(m)}\big)^T \delta^{(m)} = \left(\prod_{l=1}^{m-1} D_l \big(W^{(l+1)}\big)^T\right) \delta^{(m)}.
  $$
  由算子范数（谱范数）的次乘性，第 $1$ 层误差敏感度的范数上界同时取决于激活导数与权重矩阵的谱范数：
  $$
  \big\|\delta^{(1)}\big\|_2 \le \left(\prod_{l=1}^{m-1} \|D_l\|_{\mathrm{op}}\right) \left(\prod_{l=2}^{m} \big\|W^{(l)}\big\|_{\mathrm{op}}\right) \big\|\delta^{(m)}\big\|_2.
  $$
  对于逻辑 Sigmoid 函数 $\sigma(z) = (1+e^{-z})^{-1}$，其导数 $\sigma'(z) = \sigma(z)(1-\sigma(z))$ 在 $z=0$ 处才取到**全局最大值 $1/4 = 0.25$**（即 $\|D_l\|_{\mathrm{op}} \le 1/4$），而在 $|z|$ 较大（神经元饱和）时指数级趋于 $0$。因此，在常见的单位尺度或小权重初始化（$\|W^{(l)}\|_{\mathrm{op}} \lesssim 1$）下，激活导数连乘因子 $\prod_{l=1}^{m-1}\|D_l\|_{\mathrm{op}} \le (1/4)^{m-1}$ 会使上界随深度 $m$ 呈指数衰减，导致底层权重（$W^{(1)}, W^{(2)}$）梯度趋近于零（**梯度消失**）；反之，若试图将权重放大到 $\|W^{(l)}\|_{\mathrm{op}} \ge 4$ 来抵消 $1/4$，又会导致前向预激活值 $|z^{(l)}|$ 迅速增大而落入饱和区（使 $\|D_l\|_{\mathrm{op}} \ll 1/4$），或者在连乘谱范数大于 $1$ 时引发**梯度爆炸（exploding gradients）**。2010 年代通过将激活函数替换为正半轴导数恒为 $1$ 的 **ReLU** $\sigma(z) = \max(0, z)$，并配合保持方差的权重初始化（Xavier/He 初始化）、归一化层（BatchNorm/LayerNorm）以及**残差连接（ResNet）**，有效缓解了深层网络的梯度消失难题（但仍需合理设置初始化与步长，以避免神经元恒处于 $z\le 0$ 的“ReLU 死亡”或权重连乘导致的梯度失稳）。

<a id="learning-errors"></a>

<a id="section-20"></a>

**A new trade-of in Machine Learning The three terms**

## 机器学习中的新权衡：三个项

$$
\begin{array}{r c l} \mathcal {E} & = & \mathbb {E} \left[ E (f _ {\mathcal {T}} ^ {*}) - E (f ^ {*}) \right] + \mathbb {E} \left[ E (f _ {n}) - E (f _ {\mathcal {T}} ^ {*}) \right] + \mathbb {E} \big [ E (\tilde {f} _ {n}) - E (f _ {n}) \big ] \\ & = & \mathcal {E} _ {\mathrm{app}} + \mathcal {E} _ {\mathrm{est}} + \mathcal {E} _ {\mathrm{opt}}. \end{array}
$$

![image](<Images/06_DL/image_019.jpg>)

|  |  | $\mathcal{F}$ | $n$ | $\rho$ |
| --- | --- | --- | --- | --- |
| $\mathcal{E}_{\text{app}}$ | (approximation error) | ↘ |  |  |
| $\mathcal{E}_{\text{est}}$ | (estimation error) | ↗ | ↘ |  |
| $\mathcal{E}_{\text{opt}}$ | (optimization error) | ... | ... | ↗ |
| $T$ | (computation time) | ↗ | ↗ | ↘ |

| 量 | 含义 | $\mathcal F$ | $n$ | $\rho$ |
|---|---|---|---|---|
| $\mathcal E_{\mathrm{app}}$ | 近似误差 | ↘ | | |
| $\mathcal E_{\mathrm{est}}$ | 估计误差 | ↗ | ↘ | |
| $\mathcal E_{\mathrm{opt}}$ | 优化误差 | … | … | ↗ |
| $T$ | 计算时间 | ↗ | ↗ | ↘ |

$f _ { \mathcal { D } } ^ { * }$ - ground truth (argminf∈yx LD(f))

$f_{\mathcal D}^*$：真实参照，$\arg\min_{f\in\mathcal Y^{\mathcal X}}L_{\mathcal D}(f)$。

$h _ { \mathcal { D } } ^ { \ast }$ - optimal hypothesis $\mathsf { ( a r g m i n } _ { h \in \mathcal { H } } L _ { \mathcal { D } } ( h ) )$

$h _ { \mathcal { D } } ^ { \ast }$：最优假设 $\mathsf { ( a r g m i n } _ { h \in \mathcal { H } } L _ { \mathcal { D } } ( h ) )$。

$h _ { S } ^ { * }$ - empirically optimal hypothesis $\mathsf { \Gamma } ( \mathsf { a r g m i n } _ { h \in \mathcal { H } } L _ { S } ( h ) )$

$h _ { S } ^ { * }$：经验最优假设 $\mathsf { \Gamma } ( \mathsf { a r g m i n } _ { h \in \mathcal { H } } L _ { S } ( h ) )$。

$\bar { h }$ - returned hypothesis

$\bar { h }$：算法返回的假设。

Here: n sample size, $\rho$ numerical tolerance in the optimization

这里 n 为样本量，$\rho$ 为优化中的数值容差。

> **译注：** 原页用真实风险差定义最后一项时，该项不必非负，例如提前停止可能改善泛化。表中箭头是趋势示意，不能当作对所有模型、数据与算法成立的单调性定理。

<a id="reading-bottou-bousquet-three-errors"></a>

**Supplement — The Bottou–Bousquet (2008) Three-Term Error Decomposition ($\mathcal{E}_{\mathrm{app}} + \mathcal{E}_{\mathrm{est}} + \mathcal{E}_{\mathrm{opt}}$) and the Large-Scale SGD Advantage.**

**补充——Bottou–Bousquet（2008）三项误差分解（$\mathcal{E}_{\mathrm{app}} + \mathcal{E}_{\mathrm{est}} + \mathcal{E}_{\mathrm{opt}}$）与大规模随机梯度下降（SGD）的计算权衡优势。**

In classical statistical learning (Lecture 1), we assumed that the Empirical Risk Minimizer $f_n = \arg\min_{f\in\mathcal{F}} \hat{L}_n(f)$ could be computed **exactly**, yielding the two-term decomposition $\mathcal{E}_{\mathrm{app}} + \mathcal{E}_{\mathrm{est}}$. In deep learning and large-scale learning, however, optimization is nonconvex and stopped at a numerical tolerance $\rho > 0$ under a finite computational budget $T_{\max}$, producing an **approximate solution** $\tilde{f}_n \in \mathcal{F}$. **Bottou & Bousquet (2008, *The Tradeoffs of Large Scale Learning*)** introduced a fourth reference function and the telescoping three-term decomposition of excess risk $E(f) = L(f)$:

在经典统计学习理论（第 1 讲）中，我们默认经验风险极小点 $f_n = \arg\min_{f\in\mathcal{F}} \hat{L}_n(f)$ 可以被**精确求出**，从而只有近似误差与估计误差两项分解 $\mathcal{E}_{\mathrm{app}} + \mathcal{E}_{\mathrm{est}}$。然而在深度学习与大规模机器学习中，优化问题高度非凸，且受限于计算时间预算 $T_{\max}$ 与数值优化容差 $\rho > 0$，算法实际返回的只是一个**近似解** $\tilde{f}_n \in \mathcal{F}$。**Bottou 与 Bousquet（2008，*The Tradeoffs of Large Scale Learning*）**引入了四个基准函数，将总超额风险作如下三项裂项分解：

| Reference Function (Slide vs. Diagram Notation) / 基准函数（正文公式与插图记号对照） | Mathematical Definition / 数学定义 | Role in the Decomposition / 在误差分解中的定位 |
| --- | --- | --- |
| $f^*$ (or $f_{\mathcal{D}}^*$) | $\arg\min_{f\in\mathcal{Y}^{\mathcal{X}}} E(f)$ | **Bayes optimal rule**: best measurable function over all possible functions. / **Bayes 最优规则**：在所有可测函数空间中达到最小真实风险 $E(f^*)$ 的理想函数。 |
| $f_{\mathcal{F}}^*$ (or $h_{\mathcal{D}}^*$) | $\arg\min_{f\in\mathcal{F}} E(f)$ | **Best in-class hypothesis**: best function within the chosen network architecture $\mathcal{F}$. / **类内最优假设**：在选定的网络架构类 $\mathcal{F}$ 中达到最小真实风险的函数。 |
| $f_n$ (or $h_S^*$) | $\arg\min_{f\in\mathcal{F}} \hat{E}_n(f)$ | **Exact ERM hypothesis**: exact minimizer of the empirical risk on sample $S$ of size $n$. / **精确经验最优假设**：在容量为 $n$ 的训练集 $S$ 上精确最小化经验风险 $\hat{E}_n(f)$ 的函数。 |
| $\tilde{f}_n$ (or $\bar{h}$) | Output of algorithm ($\hat{E}_n(\tilde{f}_n) \le \hat{E}_n(f_n) + \rho$) | **Returned hypothesis**: approximate solution returned by SGD after finite time $T$ (tolerance $\rho$). / **算法实际返回的假设**：优化算法在有限时间 $T$（数值容差 $\rho$）下实际输出的近似解。 |

Adding and subtracting $E(f_{\mathcal{F}}^*)$ and $E(f_n)$ gives the exact identity:

通过加减中间项 $E(f_{\mathcal{F}}^*)$ 与 $E(f_n)$，得到恒等分解：

$$
\mathcal{E} = \mathbb{E}\big[E(\tilde{f}_n) - E(f^*)\big] = \underbrace{\mathbb{E}\big[E(f_{\mathcal{F}}^*) - E(f^*)\big]}_{\mathcal{E}_{\mathrm{app}}\text{ (Approximation Error)}} + \underbrace{\mathbb{E}\big[E(f_n) - E(f_{\mathcal{F}}^*)\big]}_{\mathcal{E}_{\mathrm{est}}\text{ (Estimation Error)}} + \underbrace{\mathbb{E}\big[E(\tilde{f}_n) - E(f_n)\big]}_{\mathcal{E}_{\mathrm{opt}}\text{ (Optimization Error)}}.
$$

**Why "Inexact" SGD Often Outperforms "Exact" Batch Optimization in the Big-Data Regime (Fixed Compute Budget $T \le T_{\max}$)**:
- Notice how the three control knobs—hypothesis space size $|\mathcal{F}|$, sample size $n$, and optimization tolerance $\rho$—show qualitative trends with the compute time $T$ in the table above:
  - Enlarging the network $|\mathcal{F}| \uparrow$ decreases $\mathcal{E}_{\mathrm{app}} \downarrow$, and typically increases the worst-case capacity bound on $\mathcal{E}_{\mathrm{est}} \uparrow$ and compute time $T \uparrow$;
  - Increasing sample size $n \uparrow$ typically decreases $\mathcal{E}_{\mathrm{est}} \downarrow$ (at rate $O(1/\sqrt{n})$ or $O(1/n)$), while increasing compute time $T \uparrow$ for full-batch methods;
  - Loosening numerical tolerance $\rho \uparrow$ (stopping earlier or using noisy stochastic gradients) increases the **empirical** optimization suboptimality $\hat{E}_n(\tilde{f}_n) - \hat{E}_n(f_n) \le \rho$, while **slashing compute time $T \downarrow$**! *(Subtlety on $\mathcal{E}_{\mathrm{opt}}$: because the slide defines $\mathcal{E}_{\mathrm{opt}} = \mathbb{E}[E(\tilde{f}_n) - E(f_n)]$ using the **true risk $E$** rather than the empirical risk $\hat{E}_n$, $\mathcal{E}_{\mathrm{opt}}$ is not even guaranteed to be non-negative or monotonically increasing in $\rho$—for instance, when early stopping acts as a regularizer against an overfit ERM $f_n$, one can actually have $E(\tilde{f}_n) < E(f_n)$, i.e., $\mathcal{E}_{\mathrm{opt}} < 0$! In theoretical upper bounds, one bounds $E(\tilde{f}_n) - E(f_{\mathcal{F}}^*) \le 2\sup_{f\in\mathcal{F}}|E(f) - \hat{E}_n(f)| + \rho$, where $\rho$ is the empirical optimization tolerance.)*
- **Key Asymptotic Insight of Bottou & Bousquet (2008)**: Since the empirical risk $\hat{E}_n(f_n)$ is already a noisy approximation of the true risk $E(f_{\mathcal{F}}^*)$ with statistical estimation error $\mathcal{E}_{\mathrm{est}} \asymp O(n^{-1/2})$ (or $O(n^{-1})$), optimizing $\hat{E}_n(f)$ down to machine precision ($\rho = 10^{-12}$) spends massive computation far below the statistical noise floor. In the **time-budgeted large-data regime** ($n$ very large, compute time constrained by $T \le T_{\max}$), **Stochastic Gradient Descent (SGD)**—which costs $O(1)$ per step independent of $n$—accepts a moderate empirical optimization tolerance $\rho \asymp \mathcal{E}_{\mathrm{est}}$ and uses the saved compute budget $T_{\max}$ to process **far more samples $n$**, achieving a better asymptotic total excess risk bound $\mathcal{E}$ than full-batch gradient methods under the same time budget $T_{\max}$.

**为什么在大数据与固定算力预算（$T \le T_{\max}$）下，“近似求解”的 SGD 往往优于“精确求解”的全批量优化**：
- 观察上方表格中三个调节旋钮——函数类规模 $|\mathcal{F}|$、样本量 $n$ 与优化容差 $\rho$——与计算时间 $T$ 的典型定性趋势：
  - 扩大网络规模 $|\mathcal{F}| \uparrow$ 会降低近似误差 $\mathcal{E}_{\mathrm{app}} \downarrow$，通常也会增大估计误差的容量上界 $\mathcal{E}_{\mathrm{est}} \uparrow$ 及计算耗时 $T \uparrow$；
  - 增大样本量 $n \uparrow$ 通常会降低估计误差 $\mathcal{E}_{\mathrm{est}} \downarrow$（速率约为 $O(n^{-1/2})$ 或 $O(n^{-1})$），同时使全批量算法的计算耗时 $T \uparrow$；
  - 放宽数值优化容差 $\rho \uparrow$（提前停止或使用带噪声的随机梯度）虽然会放宽**经验风险**上的优化次优度 $\hat{E}_n(\tilde{f}_n) - \hat{E}_n(f_n) \le \rho$，却能**大幅节省计算时间 $T \downarrow$**！*（关于 $\mathcal{E}_{\mathrm{opt}}$ 符号与单调性的注记：由于课件正文用**真实风险 $E$** 定义 $\mathcal{E}_{\mathrm{opt}} = \mathbb{E}[E(\tilde{f}_n) - E(f_n)]$，这一项在数学上甚至不必非负，也不必随 $\rho$ 严格单调递增——例如当精确经验风险极小点 $f_n$ 发生过拟合而提前停止点 $\tilde{f}_n$ 起到隐式正则化作用时，反而可能出现 $E(\tilde{f}_n) < E(f_n)$ 即 $\mathcal{E}_{\mathrm{opt}} < 0$！在严格的一致收敛上界推导中，通常将 $E(\tilde{f}_n) - E(f_{\mathcal{F}}^*)$ 放缩为 $2\sup_{f\in\mathcal{F}}|E(f) - \hat{E}_n(f)| + \rho$，此时经验优化容差 $\rho$ 作为加性上界项出现。）*
- **Bottou & Bousquet（2008）的渐近核心洞见**：由于经验风险 $\hat{E}_n(f_n)$ 相对于真实风险 $E(f_{\mathcal{F}}^*)$ 本身就带有量级为 $\mathcal{E}_{\mathrm{est}} \asymp O(n^{-1/2})$（或 $O(n^{-1})$）的统计抽样误差，把 $\hat{E}_n(f)$ 优化到双精度机器误差（如 $\rho = 10^{-12}$）是在统计噪声水平之下消耗算力。在**样本充裕但计算时间受限（$T \le T_{\max}$）的大数据渐近机制**下，每步计算复杂度为 $O(1)$（与样本量 $n$ 无关）的**随机梯度下降（SGD）**通过容忍与统计误差同量级的经验优化容差 $\rho \asymp \mathcal{E}_{\mathrm{est}}$，把有限算力预算 $T_{\max}$ 用于处理**更多的数据样本 $n$**，从而在相同时间预算 $T_{\max}$ 下取得比全批量优化算法更优的渐近总超额风险上界。

<a id="section-21"></a>

Third wave: 2010s

## 第三波：2010 年代

From shallow to deep networks

### 从浅层到深层网络

1. How to build deep networks

   怎样构建深层网络。
2. The mysteries of deep learning

   深度学习的谜题。

From shallow to deep networks

### 从浅层到深层网络

1. How to build deep networks

   怎样构建深层网络。

<a id="section-22"></a>

**Engineering of deep learning**

## 深度学习工程

- Software environments for deep learning designed as computational graphs (Theano, Keras, TensorFlow...)

  深度学习软件环境以计算图组织，例如 Theano、Keras、TensorFlow。

![image](<Images/06_DL/image_020.jpg>)

- A computational graph is a way to represent a math function in the language of graph theory.

  计算图是用图论语言表示数学函数的一种方式。
- In a computational graph nodes are either input values or functions for combining values.

  在计算图中，节点要么是输入值，要么是用于组合数值的函数。

Edges receive their weights as the data flows through the graph. Outbound edges from an input node ar wei hted with that input value; outbound nodes from a function node are wei hted by combinin the weights of the inbound edges using the specified function.

数据流经计算图时，边获得相应的权值。输入节点的出边以该输入值为权值；函数节点的输出按指定函数组合入边的权值，从而得到权值。

> **译注：** 这里边的“权值”指流经边的计算结果，并不意味着每条数据依赖边都有独立可训练参数。

<a id="regularization"></a>

<a id="section-23"></a>

**Regularization in deep learning and why DL theory is dificult**

## 深度学习中的正则化，以及深度学习理论为何困难

Implicit in the objective, but lots of engineering tricks in the computational graph:

正则化隐含在目标之中，但计算图中存在许多工程技巧：

- Weight decay

  权重衰减。
- Weight sharing

  权重共享。
- Early stopping

  提前停止。
- Model averaging

  模型平均。
- Dropout

  Dropout。
- Data augmentation

  数据增强。
- Adversarial training

  对抗训练。

> **译注：** 原页将这些方法概括为工程中的隐含正则化；它们包含目标函数、结构、数据和优化过程等不同层面的约束，不都属于严格意义上的隐式正则化。

<a id="section-24"></a>

**Implementation of Deep Learning Examples on github**

## 深度学习实现：GitHub 示例

- https://github.com/enggen/Deep-Learning-Coursera/

  https://github.com/enggen/Deep-Learning-Coursera/
- https:

  https://github.com/aymericdamien/TensorFlow-Examples/

//github.com/aymericdamien/TensorFlow-Examples/

<!-- 原转换稿此处的 URL 片段已完整拼接于上方链接。 -->

<a id="section-25"></a>

**The design problem (1/2) Setup**

## 设计问题（1/2）：设定

- Denote by T the structural parameters of the deep network (architecture, activity functions, regularization modes...) and $\dot { \hat { f } } _ { T }$ the function produced by deep learning given T

  用 T 表示深层网络的结构参数，包括架构、激活函数、正则化方式等；用 $\dot { \hat { f } } _ { T }$ 表示给定 T 后深度学习产生的函数。
- Some estimate of the predictive error $\hat { L } ( \hat { f } _ { T } )$ of the function supposed to be available (can be estimated by hold out, cross validation...).

  假设能够获得该函数预测误差的某个估计 $\hat { L } ( \hat { f } _ { T } )$，可通过留出法、交叉验证等估计。
- Finding T is key to address the estimation-approximation tradeof

  寻找 T 是解决估计—近似权衡的关键。

<a id="section-26"></a>

**The design problem (2/2) Selecting the structure**

## 设计问题（2/2）：选择结构

- Selecting the structure of a deep network is a meta-learning problem

  选择深层网络的结构是一个元学习问题。
- The optimal architecture can be obtained if it is possible to solve the following optimization problem:

  如果能够求解以下优化问题，就可以得到最优架构：

$$
\min _ {T} \hat {L} (\hat {f} _ {T})
$$

which is generally nonconvex, nonsmooth

这个问题通常非凸且非光滑。

- Main approaches to find T: experience, heuristics, discrete optimization, experimental design?

  寻找 T 的主要途径：经验、启发式、离散优化、实验设计？

<a id="section-27"></a>

**Other popular deep learning architectures**

## 其他常见深度学习架构

- Convolutional Neural Networks

  卷积神经网络。
- Recurrent Neural Networks

  循环神经网络。
- Long Short Term Memory

  长短期记忆网络。
- Auto-Encoders

  自编码器。
- Boltzmann Machines, Belief Networks

  Boltzmann 机、信念网络。
- Generative Adversarial Networks

  生成对抗网络。

<a id="section-28"></a>

**Other popular deep learning architectures Convolutional Neural Networks**

## 其他架构：卷积神经网络

![image](<Images/06_DL/image_021.jpg>)

<a id="section-29"></a>

**Other popular deep learning architectures Auto-Encoders**

## 其他架构：自编码器

![image](<Images/06_DL/image_022.jpg>)

<a id="reading-dl-regularization-and-architectures"></a>

**Supplement — Regularization Mechanisms in Deep Learning, Convolutional Weight Sharing (CNNs), and Autoencoders vs. PCA.**

**补充——深度学习中的正则化机制、卷积神经网络（CNN）的局部连接与权重共享，以及自编码器与 PCA 的关系。**

Section 5 asked: *"Where is the regularizer in $\min_\theta \frac{1}{n}\sum_{i=1}^n \ell(h(X_i,\theta), Y_i)$?"* Sections 23–29 reveal that regularization in deep learning is distributed across **four distinct levels**: the loss objective, the optimization trajectory, the data distribution, and the network architecture itself.

第 5 节曾提出问题：*“在经验风险最小化目标 $\min_\theta \frac{1}{n}\sum_{i=1}^n \ell(h(X_i,\theta), Y_i)$ 中，正则化项在哪里？”* 第 23 至 29 节揭示了深度学习的正则化实际上分布在**四个不同层面**：目标函数、优化轨迹、数据分布以及网络架构本身。

| Regularization Technique (Section 23) / 正则化技术（第 23 节） | Mathematical Formulation / Operational Rule / 数学形式／操作机制 | Statistical & Geometric Effect / 统计与几何作用 |
| --- | --- | --- |
| **Weight Decay ($\ell_2$ penalty)** / **权重衰减** | Add $\frac{\lambda}{2}\|\theta\|_2^2$ to objective $\iff$ update $\theta_{t+1} = (1 - \eta\lambda)\theta_t - \eta\nabla_\theta\hat{L}_n(\theta_t)$ | Shrinks weights toward $0$; bounds the Lipschitz constant $\prod_{l=1}^m \|W^{(l)}\|_{\mathrm{op}}$ of the network. / 将权重向 $0$ 收缩；限制网络的 Lipschitz 常数 $\prod_{l=1}^m \|W^{(l)}\|_{\mathrm{op}}$，防止决策边界剧烈振荡。 |
| **Early Stopping** / **提前停止（早停法）** | Stop GD/SGD at step $t^*$ (e.g., when validation error begins to rise) | Restricts $\theta_t$ near initialization $\theta_0$; for quadratic loss $\frac{1}{2n}\|Y-X\theta\|_2^2$ initialized at $\theta_0 = 0$ (with step size $\eta < 2/\lambda_{\max}(\frac{1}{n}X^T X)$), $t$ steps of GD apply the spectral filter $1 - (1 - \eta s)^t$ to eigenvalue $s$ of $\frac{1}{n}X^T X$, whereas Ridge regression ($\min_\theta \frac{1}{2n}\|Y-X\theta\|_2^2 + \frac{\lambda}{2}\|\theta\|_2^2$) applies $\frac{s}{s+\lambda}$. Under the scale correspondence $\lambda \asymp \frac{1}{\eta t^*}$, early stopping exerts a **similar** spectral regularization effect (Ali, Kolter & Tibshirani, 2019), though the two estimators are generally not identical. / 将参数限制在初始点 $\theta_0$ 附近；对从 $\theta_0 = 0$ 出发的平方损失 $\frac{1}{2n}\|Y-X\theta\|_2^2$（步长 $\eta < 2/\lambda_{\max}(\frac{1}{n}X^T X)$），梯度下降迭代 $t$ 步对 $\frac{1}{n}X^T X$ 的特征值 $s$ 施加谱滤波因子 $1 - (1 - \eta s)^t$，而岭回归 $\min_\theta \frac{1}{2n}\|Y-X\theta\|_2^2 + \frac{\lambda}{2}\|\theta\|_2^2$ 施加的谱滤波因子为 $\frac{s}{s+\lambda}$。在尺度对应 $\lambda \asymp \frac{1}{\eta t^*}$ 下，早停具有与岭回归**相似**的谱正则化作用（Ali, Kolter & Tibshirani, 2019），但二者通常不是严格相等的估计量。 |
| **Dropout (Srivastava et al., 2014)** / **Dropout 随机失活** | Multiply each hidden unit $a_j^{(l)}$ by $B_j \sim \operatorname{Bernoulli}(p)$ during training; scale by $p$ at test time | Prevents co-adaptation of neurons; acts as an approximate geometric ensemble average over $2^H$ thinned subnetworks sharing weights (and induces an adaptive $\ell_2$-like penalty). / 防止神经元共适应；近似等价于对共享权重的 $2^H$ 个稀疏子网络做几何模型平均（并在二阶近似下诱导自适应 $\ell_2$ 正则化）。 |
| **Data Augmentation** / **数据增强** | Apply label-preserving transformations $g\in\mathcal{G}$ (crops, translations, flips, noise) to $X_i$ | Replaces empirical distribution $\hat{P}_n$ by the orbit-smoothed distribution; enforces invariance $h(g(x),\theta)\approx h(x,\theta)$ and reduces estimation variance. / 用变换群轨道平滑经验分布 $\hat{P}_n$；显式注入对称不变性 $h(g(x),\theta)\approx h(x,\theta)$ 并降低方差。 |
| **Adversarial Training (Goodfellow et al., 2015)** / **对抗训练** | Robust min-max objective: $\min_\theta \frac{1}{n}\sum_{i=1}^n \max_{\|\delta\|\le\epsilon} \ell(h(X_i+\delta, \theta), Y_i)$ | Penalizes directional sensitivity $\|\nabla_x \ell(h(x,\theta),y)\|_{*}$ around data points; enforces local Lipschitz smoothness in input space. / 惩罚数据点附近的输入梯度敏感度 $\|\nabla_x \ell(h(x,\theta),y)\|_{*}$，强制网络在输入空间具有局部光滑性。 |

**Architectural Regularization — Convolutional Neural Networks (CNNs) and Autoencoders**:
1. **Convolutional Neural Networks (Section 28: Local Receptive Fields + Weight Sharing + Pooling)**:
   For an image $X \in \mathbb{R}^{H\times W\times C}$, a standard fully connected layer mapping $1000\times 1000\times 3 = 3\times 10^6$ inputs to $10^6$ hidden units would require $3\times 10^{12}$ parameters—both computationally impossible and guaranteed to overfit. A **convolutional layer** regularizes the linear map $A_l$ via two structural constraints:
   - **Locality (Sparse Connectivity)**: Each hidden unit only connects to a small spatial patch of size $k\times k$ (e.g., $3\times 3$ or $5\times 5$).
   - **Weight Sharing (Translation Equivariance)**: The exact same filter kernel $K \in \mathbb{R}^{k\times k\times C}$ is slid across all spatial positions $(u,v)$ via discrete convolution $(K * X)_{u,v} = \sum_{p,q,c} K_{p,q,c}\,X_{u+p, v+q, c}$. This reduces the parameter count per feature map from $3\times 10^{12}$ down to just $k^2 C$ (e.g., $5\times 5\times 3 = 75$ parameters!) and guarantees **translation equivariance** (if an object shifts in the image, its feature activation shifts by the exact same amount). Subsequent **pooling/subsampling** layers aggregate local neighborhoods to build **translation invariance**.

   **卷积神经网络（第 28 节：局部感受野 + 权重共享 + 池化）**：
   对分辨率为 $1000\times 1000\times 3 = 3\times 10^6$ 的图像，若使用全连接层映射到 $10^6$ 个隐藏单元，单层就需要 $3\times 10^{12}$ 个参数，计算上不可行且必然严重过拟合。**卷积层**通过两条结构性先验对线性映射 $A_l$ 施加极强的架构正则化：
   - **局部连接（稀疏性）**：每个神经元仅连接输入图像中 $k\times k$（如 $3\times 3$ 或 $5\times 5$）的局部感受野；
   - **权重共享（平移等变性）**：同一个卷积核滤波器 $K \in \mathbb{R}^{k\times k\times C}$ 在所有空间位置 $(u,v)$ 上共享参数并滑动做离散卷积 $(K * X)_{u,v} = \sum_{p,q,c} K_{p,q,c}\,X_{u+p, v+q, c}$。这使每个特征图的参数量从 $3\times 10^{12}$ 骤降至仅 $k^2 C$ 个（例如 $5\times 5\times 3 = 75$ 个参数！），并天然保证**平移等变性**（图像中的目标平移时，特征图响应随之同步平移）；随后的**池化／下采样（Subsampling）层**通过对局部邻域聚合进一步赋予网络**平移不变性**。
2. **Autoencoders vs. PCA (Section 29: Unsupervised Nonlinear Manifold Learning)**:
   An **Autoencoder** is an unsupervised neural network consisting of an **Encoder** $z = f_{\mathrm{enc}}(x) \in \mathbb{R}^r$ that compresses input $x \in \mathbb{R}^d$ into a low-dimensional **bottleneck code** ($r \ll d$, as shown by the 3-node central layer in Section 29's diagram) and a **Decoder** $\hat{x} = g_{\mathrm{dec}}(z) \in \mathbb{R}^d$ trained to reconstruct $x$ by minimizing the reconstruction error $\frac{1}{n}\sum_{i=1}^n \|X_i - g_{\mathrm{dec}}(f_{\mathrm{enc}}(X_i))\|_2^2$:
   - **Theorem (Bourlard & Kamp, 1988; Baldi & Hornik, 1989 — Connection to Lecture 4 PCA)**: Suppose the data are centered ($\frac{1}{n}\sum_{i=1}^n X_i = 0$, or an explicit intercept vector is included) with data matrix $X = [X_1, \dots, X_n] \in \mathbb{R}^{d\times n}$, empirical covariance $\hat{\Sigma} = \frac{1}{n}X X^T$, and $\operatorname{rank}(X) \ge r$. If the encoder $f_{\mathrm{enc}}(x) = W_1 x$ and decoder $g_{\mathrm{dec}}(z) = W_2 z$ are **linear** ($W_1\in\mathbb{R}^{r\times d}, W_2\in\mathbb{R}^{d\times r}$) and the $r$-th eigenvalue of $\hat{\Sigma}$ satisfies a strict spectral gap $\lambda_r > \lambda_{r+1}$, then by the Eckart–Young theorem (Lecture 4), any global minimizer $(\widehat{W}_1, \widehat{W}_2)$ of $\sum_{i=1}^n \|X_i - W_2 W_1 X_i\|_2^2 = \|X - W_2 W_1 X\|_F^2$ reconstructs the exact rank-$r$ PCA projection on the data: $\widehat{W}_2 \widehat{W}_1 X = U_r U_r^T X$, where $U_r \in \mathbb{R}^{d\times r}$ contains the top $r$ orthonormal eigenvectors of $\hat{\Sigma}$ as columns. When $\hat{\Sigma}$ is full-rank ($\operatorname{rank}(X) = d$), this forces $\widehat{W}_2 \widehat{W}_1 = U_r U_r^T$ everywhere on $\mathbb{R}^d$ (whereas if $\operatorname{rank}(X) < d$, the empirical objective only constrains $\widehat{W}_2\widehat{W}_1$ on the data subspace $\operatorname{Im}(X)$ unless minimal-norm regularization is added); furthermore, the individual factors $(\widehat{W}_1, \widehat{W}_2) = (R^{-1} U_r^T, U_r R)$ are determined only up to an invertible change-of-basis matrix $R \in \operatorname{GL}_r(\mathbb{R})$.
   - When $f_{\mathrm{enc}}$ and $g_{\mathrm{dec}}$ are **deep nonlinear networks**, the autoencoder generalizes linear PCA to **nonlinear dimensionality reduction**, learning curved low-dimensional manifolds in $\mathbb{R}^d$.

   **自编码器与 PCA 的关系（第 29 节：无监督非线性流形学习）**：
   **自编码器（Autoencoder）**是一种无监督神经网络，由将高维输入 $x \in \mathbb{R}^d$ 压缩为低维**瓶颈编码（bottleneck code）** $z = f_{\mathrm{enc}}(x) \in \mathbb{R}^r$（$r \ll d$，对应第 29 节图中仅含 3 个神经元的最窄中间层）的**编码器（Encoder）**，与将 $z$ 重建回 $\hat{x} = g_{\mathrm{dec}}(z) \in \mathbb{R}^d$ 的**解码器（Decoder）**组成，通过最小化重构误差 $\frac{1}{n}\sum_{i=1}^n \|X_i - g_{\mathrm{dec}}(f_{\mathrm{enc}}(X_i))\|_2^2$ 进行训练：
   - **线性自编码器与 PCA 的定理（Bourlard & Kamp, 1988；Baldi & Hornik, 1989）**：设样本已中心化（$\frac{1}{n}\sum_{i=1}^n X_i = 0$，或包含显式截距项），记数据矩阵 $X = [X_1, \dots, X_n] \in \mathbb{R}^{d\times n}$，样本协方差矩阵 $\hat{\Sigma} = \frac{1}{n}X X^T$，且 $\operatorname{rank}(X) \ge r$。若编码器 $f_{\mathrm{enc}}(x) = W_1 x$ 与解码器 $g_{\mathrm{dec}}(z) = W_2 z$ 均为**线性映射**（$W_1\in\mathbb{R}^{r\times d}, W_2\in\mathbb{R}^{d\times r}$），且 $\hat{\Sigma}$ 的第 $r$ 个特征值满足严格谱间隙 $\lambda_r > \lambda_{r+1}$，则由第 4 讲的 Eckart–Young 定理，$\sum_{i=1}^n \|X_i - W_2 W_1 X_i\|_2^2 = \|X - W_2 W_1 X\|_F^2$ 的任意全局极小点 $(\widehat{W}_1, \widehat{W}_2)$ 在数据矩阵上的重构都与前 $r$ 个主成分（PCA 特征向量矩阵 $U_r \in \mathbb{R}^{d\times r}$）的正交投影一致：$\widehat{W}_2 \widehat{W}_1 X = U_r U_r^T X$。特别地，当样本协方差矩阵满秩（$\operatorname{rank}(X) = d$）时，这在整个 $\mathbb{R}^d$ 上唯一确定了乘积算子 $\widehat{W}_2 \widehat{W}_1 = U_r U_r^T$（若 $\operatorname{rank}(X) < d$，经验损失仅约束 $\widehat{W}_2\widehat{W}_1$ 在数据子空间 $\operatorname{Im}(X)$ 上与 $U_r U_r^T$ 一致，在正交补 $\operatorname{Im}(X)^\perp$ 上需附加最小范数正则化才能唯一确定）；此外，单个因子矩阵 $(\widehat{W}_1, \widehat{W}_2) = (R^{-1} U_r^T, U_r R)$ 在相差任意可逆矩阵 $R \in \operatorname{GL}_r(\mathbb{R})$ 的基底变换下等价。
   - 当 $f_{\mathrm{enc}}$ 与 $g_{\mathrm{dec}}$ 为**多层非线性网络**时，自编码器将线性 PCA 推广为**非线性降维**，能够捕获高维空间中的弯曲低维流形。

<a id="section-30"></a>

From shallow to deep networks

## 从浅层到深层网络

2. The mysteries of Deep Learning

### 2. 深度学习的谜题

**Mysteries about deep learning**

### 深度学习的谜题

- Approximation: deep better than shallow?

  近似：深层优于浅层吗？
- Optimization: nonconvex with millions of dimensions (!)

  优化：上百万维的非凸问题！
- Overfitting: huge complexity

  过拟合：巨大的复杂度。

<a id="section-31"></a>

**Facts about approximation theory**

## 近似理论中的结果

Comparison of Shallow vs. Deep Networks

### 浅层与深层网络的比较

- Poggio and Liao (2018): approximation of compositional functions

  Poggio 与 Liao（2018）：复合函数的逼近。
- Liang and Srikant (2017): approximation of polynomial functions

  Liang 与 Srikant（2017）：多项式函数的逼近。
- Similar findings:

  相似的发现：

” the number of neurons needed by a shallow network to approximate a function is exponentially larger than the corresponding number of neurons needed by a deep network for a given degree of function approximation.

“对于给定的函数逼近精度，浅层网络逼近一个函数所需的神经元数，比相应深层网络所需的神经元数呈指数级增长。”

> **译注：** 此处的深度优势依赖目标函数类、激活函数、网络结构和误差定义，不能推广为所有深网络对所有函数都指数级优于浅层网络。

<a id="section-32"></a>

**Facts about optimization in Deep Learning**

## 深度学习优化中的结果

- Under certain conditions, no poor local minima

  在某些条件下，不存在坏的局部极小值。

![image](<Images/06_DL/image_023.jpg>)

Figure 1. Example critical points of a non-convex function (showr in red). (a,c) Plateaus. (b,d) Global minima. (c,g) Local maxima (f,h) Local minima

图 1：非凸函数的临界点示例，以红色标出。(a,c) 平坦区域；(b,d) 全局极小值；(c,g) 局部极大值；(f,h) 局部极小值。

> **译注：** 原图的局部极大值编号应为 (e,g)；原图注把 e 写成了 c。

**• SGD avoids bad critical points**

### SGD 避开不良临界点

- Larger networks are better behaved (local minima are global)

  更大的网络具有更好的性质，局部极小值都是全局极小值。

> **译注：** 这些优化结论分别有各自的网络、损失、数据与算法条件，不能合并为任意深度网络的无条件保证。

**References:**

### 参考文献

Soudry and Carmon (2016), “No bad local minima: Data independent trainin error uarantees for multilaye neural networks”.

Soudry 与 Carmon（2016），No bad local minima: Data independent training error guarantees for multilayer neural networks（无坏的局部极小值：多层神经网络中与数据无关的训练误差保证）。

Kawaguchi (2016), “Deep learning without poor local minima”.

Kawaguchi（2016），Deep learning without poor local minima（没有坏的局部极小值的深度学习）。

Haefele and Vidal (2017), “Global optimality in neural network training”.

Haeffele 与 Vidal（2017），Global optimality in neural network training（神经网络训练中的全局最优性）。

Janzamin, Sedghi, and Anandkumar (2015), “Beating the perils of non-convexity: Guaranteed training of neural networks using tensor methods".

Janzamin、Sedghi 与 Anandkumar（2015），Beating the perils of non-convexity: Guaranteed training of neural networks using tensor methods（克服非凸性的困难：使用张量方法实现有保证的神经网络训练）。

Panageas and Piliouras (2016), “Gradient descent only converges to minimizers: Non-isolated critical points an invariant regions".

Panageas 与 Piliouras（2016），Gradient descent only converges to minimizers: Non-isolated critical points and invariant regions（梯度下降只收敛到极小点：非孤立临界点与不变区域）。

Brutzkus, Alon et al. (2017), “SGD Learns Over-parameterized Networks that Provably Generalize on Linearly

Brutzkus、Alon 等（2017），SGD Learns Over-parameterized Networks that Provably Generalize on Linearly Separable Data（SGD 学习在理论上能对线性可分数据泛化的过参数化网络）。

Separable Data”.

<!-- 原转换稿中的论文标题换行已完整拼接于上一段。 -->

<a id="section-33"></a>

**Vapnik’s theory applied to Deep Learning Complexity of arrangements**

## Vapnik 理论应用于深度学习：排列的复杂度

![image](<Images/06_DL/image_024.jpg>)

- VC dimension of multilayer feedforward neural network with $\omega$ parameters using step function for activation:

  使用阶跃函数作为激活函数、具有 $\omega$ 个参数的多层前馈神经网络的 VC 维：

V ≤ 2ω log (eω) can be quite huge...

$V\le2\omega\log_2(e\omega)$，可能非常大……

> **译注：** 该数值界照原页保留；原页未完整交代网络结构假设，不应直接用于任意 ReLU 或 sigmoid 网络。

<a id="reading-three-mysteries-of-dl"></a>

**Supplement — Unpacking the Three Mysteries of Deep Learning: Exponential Depth Separation, Saddle-Point Escape in Nonconvex Optimization, and Generalization Beyond VC Dimension.**

**补充——深入解析深度学习三大谜题：深度的指数逼近优势、非凸优化中的鞍点逃逸，以及超越 VC 维的过参数化泛化。**

Sections 30–33 highlight three apparent paradoxes ("mysteries") when classical statistical learning theory is applied to modern deep networks. Each corresponds to one of the three terms in the Bottou–Bousquet decomposition $\mathcal{E} = \mathcal{E}_{\mathrm{app}} + \mathcal{E}_{\mathrm{opt}} + \mathcal{E}_{\mathrm{est}}$:

第 30 至 33 节指出了将经典统计学习理论应用于现代深度网络时出现的三个表面悖论（“三大谜题”），它们恰好分别对应 Bottou–Bousquet 误差分解 $\mathcal{E} = \mathcal{E}_{\mathrm{app}} + \mathcal{E}_{\mathrm{opt}} + \mathcal{E}_{\mathrm{est}}$ 中的三项：

#### 1. Mystery 1 (Approximation $\mathcal{E}_{\mathrm{app}}$): Why Is Deep Exponentially More Efficient Than Shallow?
#### 1. 谜题一（近似误差 $\mathcal{E}_{\mathrm{app}}$）：为什么深层网络比浅层网络具有指数级的参数效率优势？

Although Cybenko's theorem says a 1-hidden-layer network *can* approximate any continuous function, **depth separation theorems** (Telgarsky, 2016; Liang & Srikant, 2017; Poggio & Liao, 2018) prove that for compositional and oscillatory functions, a shallow network requires **exponentially more neurons** than a deep network:

尽管 Cybenko 定理表明单隐藏层网络在理论上*能够*逼近任意连续函数，但**深度分离定理**（Telgarsky, 2016；Liang & Srikant, 2017；Poggio & Liao, 2018）严格证明：对于具有层次复合结构或高频振荡的函数，浅层网络所需的神经元数量比深层网络呈**指数级膨胀**：

**Constructive Proof Example: Telgarsky's Sawtooth / Triangle Wave Composition ($2^L$ Linear Pieces with $O(L)$ Neurons)（Telgarsky 锯齿波／三角波复合的构造性证明——$O(L)$ 个神经元生成 $2^L$ 段线性振荡）**

Consider the 1D symmetric tent (triangle) map $T : [0, 1] \to [0, 1]$ defined by $T(x) = 2x$ on $[0, 1/2]$ and $T(x) = 2(1-x)$ on $(1/2, 1]$. Using the ReLU activation $\sigma(z) = (z)_+ = \max(0, z)$, $T(x)$ can be written **exactly** on $[0, 1]$ (and extended by $0$ outside $[0, 1]$) with just **3 ReLU neurons**:

考虑区间 $[0, 1] \to [0, 1]$ 上的一维对称帐篷映射（三角波函数）：当 $x\in[0,1/2]$ 时 $T(x) = 2x$，当 $x\in(1/2,1]$ 时 $T(x) = 2(1-x)$。使用 ReLU 激活函数 $\sigma(z) = (z)_+ = \max(0, z)$，$T(x)$ 仅需 **3 个 ReLU 神经元**即可**精确表示**：

$$
T(x) = 2(x)_+ - 4\left(x - \frac{1}{2}\right)_+ + 2(x - 1)_+.
$$

- **Deep Network ($L$ layers)**: Composing $T$ with itself $L$ times—$f_L(x) = (\underbrace{T \circ T \circ \dots \circ T}_{L\text{ times}})(x)$—requires a deep ReLU network of depth $L$ and width $3$, containing only **$3L$ total neurons** ($O(L)$ parameters). Yet each composition doubles the number of oscillations: $f_L(x)$ is a sawtooth wave oscillating between $0$ and $1$ with **$2^{L-1}$ peaks and $2^L$ affine segments** on $[0, 1]$!
- **Shallow Network (1 hidden layer)**: Any 1-hidden-layer ReLU network $h_N(x) = \sum_{k=1}^N c_k(a_k x + b_k)_+ + c_0$ has at most $N$ breakpoints, so it is piecewise linear with at most $N + 1$ affine segments. To approximate $f_L(x)$ within $L^1$ error $\varepsilon < 1/8$, a 1-hidden-layer ReLU network must have at least **$N = \Omega(2^L)$ neurons**! For $L = 30$, the deep network uses $3\times 30 = 90$ neurons, whereas the shallow network requires $\sim 10^9$ neurons!
- **Poggio & Liao (2018) on Compositional Functions**: More generally, if a $d$-dimensional target function has a hierarchical binary tree structure $f(x_1,\dots,x_8) = h_3\big(h_{21}(h_{11}(x_1,x_2), h_{12}(x_3,x_4)),\, h_{22}(h_{13}(x_5,x_6), h_{14}(x_7,x_8))\big)$ where each local function is $m$-smooth on $\mathbb{R}^2$, a shallow network suffers the full $d$-dimensional curse of dimensionality $N_{\mathrm{shallow}} = O(\varepsilon^{-d/m})$, whereas a deep network matching the compositional graph only needs $N_{\mathrm{deep}} = O((d-1)\varepsilon^{-2/m})$—replacing the exponent $d$ by the local fan-in $2$!

- **深层网络（$L$ 层）**：将帐篷映射 $T$ 自复合 $L$ 次——即 $f_L(x) = (T \circ T \circ \dots \circ T)(x)$——只需一个深度为 $L$、每层宽度为 $3$ 的深层 ReLU 网络，总共仅含 **$3L$ 个神经元**（$O(L)$ 个参数）。然而每复合一次，振荡频率就翻倍：$f_L(x)$ 在 $[0,1]$ 上是具有 **$2^{L-1}$ 个波峰、$2^L$ 个线性分段**的高频锯齿波！
- **浅层网络（单隐藏层）**：任意含 $N$ 个神经元的单隐藏层 ReLU 网络 $h_N(x) = \sum_{k=1}^N c_k(a_k x + b_k)_+ + c_0$ 至多只有 $N$ 个折点，因此至多只能形成 $N+1$ 个线性分段。要以优于 $\varepsilon < 1/8$ 的误差逼近 $f_L(x)$，单隐藏层网络至少需要 **$N = \Omega(2^L)$ 个神经元**！当层数 $L=30$ 时，深层网络仅需 $90$ 个神经元，而浅层网络需要约 $10^9$（十亿）个神经元！
- **Poggio & Liao（2018）复合函数逼近定理**：更一般地，若 $d$ 维目标函数具有二叉树式的层次局部复合结构（每个局部节点仅依赖 $2$ 个输入且具 $m$ 阶光滑性），浅层网络会遭受完整的维数灾难 $N_{\mathrm{shallow}} = O(\varepsilon^{-d/m})$，而匹配该层次结构的深层网络仅需 $N_{\mathrm{deep}} = O((d-1)\varepsilon^{-2/m})$——将指数上的全局维数 $d$ 降为了局部扇入维数 $2$！

#### 2. Mystery 2 (Optimization $\mathcal{E}_{\mathrm{opt}}$): Why Does SGD Succeed on Million-Dimensional Nonconvex Landscapes?
#### 2. 谜题二（优化误差 $\mathcal{E}_{\mathrm{opt}}$）：为什么 SGD 能在上百万维的非凸损失曲面上成功寻优？

In 1D or 2D intuition (like Figure 1 in Section 32), nonconvex functions trap gradient descent in poor local minima. Why doesn't this cripple deep learning in $\mathbb{R}^\omega$ ($\omega \gg 10^6$)?

在一维或二维直觉中（如第 32 节图 1），非凸函数极易使梯度下降陷入局部极小值。为什么在 $\mathbb{R}^\omega$（$\omega \gg 10^6$）的高维空间中，这并没有阻碍深度学习？

- **Critical Points in High Dimensions and Random-Landscape Intuition**:
  At any critical point $\theta^*$ ($\nabla_\theta \mathcal{L}(\theta^*) = 0$) of a smooth loss, local curvature is governed by the $\omega\times\omega$ Hessian matrix $\nabla_\theta^2 \mathcal{L}(\theta^*)$: a **local minimum** requires all eigenvalues $\lambda_1, \dots, \lambda_\omega \ge 0$, whereas any $\lambda_j < 0$ provides a negative-curvature descent direction (**strict saddle point**). In statistical-physics and random-landscape models (such as high-dimensional Gaussian random fields and spin-glass Hamiltonians analyzed in Bray & Dean, 2007; Auffinger, Ben Arous & Černý, 2013, and used as a heuristic motivation for neural networks in Dauphin et al., 2014), critical points at high loss levels typically possess indefinite Hessians with negative eigenvalues, while true local minima tend to concentrate at low loss levels. *(Caveat: real neural network Hessians are structured, data-dependent, and often degenerate, so random-matrix results such as Wigner's semicircle law do not directly prove unconditional saddle-point probabilities for arbitrary neural networks.)*
- **Escaping Strict Saddle Points and Conditional "No Bad Local Minima" Results**:
  Under smoothness ($\beta$-Lipschitz gradient) and suitable step-size conditions, the stable manifold theorem guarantees that gradient descent from random initialization almost surely avoids **strict saddle points** ($\lambda_{\min}(\nabla_\theta^2 \mathcal{L}) < 0$; Lee et al., 2016; Panageas & Piliouras, 2016), though unperturbed GD can still linger exponentially long near saddle points in worst-case landscapes. Adding explicit perturbations or satisfying suitable stochastic-noise, Hessian-Lipschitz, and step-size assumptions allows perturbed gradient descent / SGD to escape $\gamma$-strict saddle points ($\lambda_{\min}(\nabla_\theta^2 \mathcal{L}) \le -\gamma < 0$) in time polynomial in smoothness, $1/\gamma$, and $1/\epsilon$, and at most polylogarithmic in dimension $\omega$ (Jin et al., 2017; building on noisy SGD escape analyses such as Ge et al., 2015—noting that real mini-batch SGD noise is state-dependent and anisotropic rather than purely isotropic). Furthermore, theorems proving **"no bad local minima"** hold only under specific structural assumptions—for example, deep **linear** networks under full-rank data/width conditions (Kawaguchi, 2016), or particular overparameterized / homogeneous architectures and losses (Soudry & Carmon, 2016; Haeffele & Vidal, 2017)—rather than unconditionally for arbitrary deep nonlinear networks.

- **高维临界点的几何特征与随机景观启发**：
  在光滑损失函数的任意临界点 $\theta^*$（$\nabla_\theta \mathcal{L}(\theta^*) = 0$）处，局部曲率由 $\omega\times\omega$ 维海森矩阵 $\nabla_\theta^2 \mathcal{L}(\theta^*)$ 的特征值决定：**局部极小点**要求全部特征值 $\lambda_1, \dots, \lambda_\omega \ge 0$，而只要存在 $\lambda_j < 0$ 就对应着负曲率下降方向（**严格鞍点**）。在统计物理与随机景观模型（如高维高斯随机场／自旋玻璃模型：Bray & Dean, 2007；Auffinger, Ben Arous & Černý, 2013，以及 Dauphin 等，2014 对神经网络鞍点的启发式分析）中，高损失能级处的临界点往往呈现特征值正负混合的不定海森矩阵，而真正的局部极小值多集中在低损失区域。*（注记：真实神经网络的海森矩阵高度依赖数据与架构且常呈退化特征，因此 Wigner 半圆律或高斯随机场结论只提供几何直觉，不能直接给出适用于任意网络的无条件概率公式。）*
- **严格鞍点的逃逸条件与“无坏局部极小值”的适用范围**：
  在梯度 Lipschitz 光滑性与合适步长条件下，稳定流形定理说明从随机初始化出发的梯度下降几乎必然不收敛到**严格鞍点**（$\lambda_{\min}(\nabla_\theta^2 \mathcal{L}) < 0$；Lee 等，2016；Panageas & Piliouras, 2016），但无扰动梯度下降在最坏情形下仍可能在鞍点附近停留指数长时间。若加入显式扰动或满足适当的光滑性、海森 Lipschitz 性、步长以及噪声激发条件，扰动梯度下降／随机梯度方法可在关于光滑常数、$1/\gamma$、$1/\epsilon$ 为多项式级、且关于维数 $\omega$ 至多为多对数级 $\operatorname{polylog}(\omega)$（Jin 等，2017；发展自 Ge 等，2015 对带噪声 SGD 逃逸鞍点的分析）的步数内逃离 $\gamma$-严格鞍点（$\lambda_{\min}(\nabla_\theta^2 \mathcal{L}) \le -\gamma < 0$）（同时需注意，真实小批量 SGD 噪声依赖于当前状态且各向异性，并非理想各向同性噪声）。此外，**“不存在坏局部极小值”**的理论结论同样依赖各自特定的结构假设——例如满足满秩数据与层宽条件的深层**线性**网络（Kawaguchi, 2016），或特定过参数化／齐次架构与损失（Soudry & Carmon, 2016；Haeffele & Vidal, 2017）——而不能无条件推广至所有深度非线性网络。

#### 3. Mystery 3 (Generalization $\mathcal{E}_{\mathrm{est}}$): Why Don't Networks with $\omega \gg n$ Overfit Catastrophically?
#### 3. 谜题三（估计／泛化误差 $\mathcal{E}_{\mathrm{est}}$）：为什么参数量远大于样本量（$\omega \gg n$）的网络没有灾难性过拟合？

- **Why Classical VC Dimension Fails to Explain Deep Learning**:
  Section 33 shows that a threshold/step network with $\omega$ weights has VC dimension $V = O(\omega\log\omega)$ (and a deep ReLU network of depth $L$ has $V = O(\omega L\log\omega)$, Bartlett et al., 2019). Plugging $V \ge \omega \gg n$ into the classical VC generalization bound $\sqrt{V/n}$ yields a bound $> 1$, which is **vacuous** (and indeed, Zhang et al., 2017 showed that deep networks have enough capacity to fit random noise labels on benchmarks such as CIFAR-10 and ImageNet).
- **Norm-Based Capacity Control & Implicit Bias of GD/SGD**:
  Why, then, can deep networks generalize well on real data? Because VC dimension measures the worst-case capacity over **all possible weights $\theta \in \mathbb{R}^\omega$**, whereas gradient methods starting from small initialization only explore structured, norm-constrained regions of parameter space. Two complementary lines of theory investigate this phenomenon (while remaining active research areas rather than a complete explanation of all modern deep nets):
  1. **Norm-Based Rademacher Margin Bounds**: Analogous to SVM margin bounds depending on $\|w\|_2 / M$ rather than ambient dimension, Bartlett, Foster & Telgarsky (2017) bounded the margin-normalized Rademacher complexity of an $m$-layer network (with $1$-Lipschitz activations such as ReLU and reference matrices $M^{(l)}$, e.g., $M^{(l)}=0$ or initialization) by the product of **spectral norms** multiplied by a **layerwise $\ell_{2,1}$ norm factor**:
     $$
     \frac{\sqrt{\frac{1}{n}\sum_{i=1}^n \|X_i\|_2^2}}{\gamma\sqrt{n}} \left(\prod_{l=1}^{m} \|W^{(l)}\|_{\mathrm{op}}\right) \left(\sum_{l=1}^{m} \frac{\big\|(W^{(l)})^T - (M^{(l)})^T\big\|_{2,1}^{2/3}}{\|W^{(l)}\|_{\mathrm{op}}^{2/3}}\right)^{3/2},
     $$
     where $\gamma > 0$ is the classification margin and $\|\cdot\|_{2,1}$ denotes the sum of column $\ell_2$ norms (distinguishing this spectrally normalized $\ell_{2,1}$ bound from **path-norm** bounds such as Neyshabur, Tomioka & Srebro, 2015). Both depend on weight norms rather than raw parameter count $\omega$, though numerically evaluating them on large practical networks can still be loose.
  2. **Implicit Bias of Gradient Methods (Under Specific Model & Loss Assumptions)**: Among infinitely many zero-training-error solutions, gradient descent and SGD often favor low-complexity interpolators without explicit penalties, depending on architecture, loss, and initialization:
     - On **linearly separable classification data** with exponential-tailed losses (e.g., logistic or exponential loss), gradient descent on **homogeneous linear predictors** ($f(x;\theta) = \theta^T x$; Soudry et al., 2018) drives the parameter norm to infinity ($\|\theta_t\|_2 \to \infty$) while the **normalized direction** $\theta_t / \|\theta_t\|_2$ converges to the hard-margin SVM maximum-$\ell_2$-margin direction; related directional margin-maximization / KKT results extend to certain **positively homogeneous deep networks** (Lyu & Li, 2020), while SGD on 2-layer overparameterized leaky-ReLU networks on linearly separable data admits provable generalization guarantees (Brutzkus et al., 2017).
     - On **underdetermined linear least squares** ($d > n$) initialized at $\theta_0 = 0$, gradient descent converges to the **minimum-$\ell_2$-norm interpolating solution** $\hat{\theta}_{\min} = X^+ Y$.
     *(Caveat: these implicit-regularization mechanisms motivate analyses of the modern **double descent** phenomenon—where test error can decrease again beyond the interpolation threshold in stylized linear, random-feature, or kernel regimes, e.g., Belkin et al., 2019—but they do not constitute a general proof that test error always decreases monotonically in the overparameterized regime for arbitrary deep networks.)*

- **为什么经典 VC 维界无法解释深度学习的泛化**：
  第 33 节指出，含 $\omega$ 个权重的阶跃激活网络其 VC 维高达 $V = O(\omega\log\omega)$（深度为 $L$ 的 ReLU 网络其 VC 维为 $V = O(\omega L\log\omega)$，Bartlett 等，2019）。在现代过参数化网络中 $\omega \gg n$，将 $V > n$ 代入经典 VC 泛化界 $\sqrt{V/n}$ 会得到大于 $1$ 的**平凡空界（vacuous bound）**（事实上，Zhang 等，2017 在 CIFAR-10 与 ImageNet 等基准上展示了深度网络甚至足以记住完全随机的噪声标签）。
- **基于范数的容量控制与 GD／SGD 的隐式偏置**：
  既然函数类总容量如此巨大，为什么深度网络在真实数据上仍能良好泛化？因为 VC 维衡量的是**整个无约束参数空间 $\theta \in \mathbb{R}^\omega$** 的最坏复杂度，而从零附近小初始化出发的梯度算法通常只访问参数空间中受范数与结构约束的特定区域。理论界主要从以下两个互补方向研究这一现象（二者仍属持续研究前沿，并非对所有现代深度网络的完备解释）：
  1. **基于范数的 Rademacher 间隔泛化界**：与核 SVM 的泛化界由 $\|w\|_2 / M$ 而非空间维数控制相类比，Bartlett, Foster & Telgarsky（2017）证明，对于采用 ReLU 等 $1$-Lipschitz 激活函数的 $m$ 层网络（相对于参考矩阵 $M^{(l)}$，如 $0$ 或初始化矩阵），其分类间隔 $\gamma > 0$ 对应的归一化 Rademacher 复杂度主要由**各层权重谱范数乘积**与**逐层 $\ell_{2,1}$ 范数因子**共同控制：
     $$
     \frac{\sqrt{\frac{1}{n}\sum_{i=1}^n \|X_i\|_2^2}}{\gamma\sqrt{n}} \left(\prod_{l=1}^{m} \|W^{(l)}\|_{\mathrm{op}}\right) \left(\sum_{l=1}^{m} \frac{\big\|(W^{(l)})^T - (M^{(l)})^T\big\|_{2,1}^{2/3}}{\|W^{(l)}\|_{\mathrm{op}}^{2/3}}\right)^{3/2},
     $$
     其中 $\|\cdot\|_{2,1}$ 表示矩阵各列 $\ell_2$ 范数之和（该谱范数–$\ell_{2,1}$ 联合界不同于 Neyshabur, Tomioka & Srebro, 2015 的**路径范数 path-norm** 界）。这些界不直接受原始参数总数 $\omega$ 惩罚，但在大型实际网络上直接代值估计时仍可能偏宽松。
  2. **梯度优化算法的隐式偏置（依赖具体模型、损失与数据条件）**：在过参数化模型无穷多个零训练误差插值解中，GD／SGD 在无显式惩罚项时仍会偏向特定低复杂度解，具体结论高度依赖设定：
     - **线性可分数据 + 指数尾损失（如逻辑损失／指数损失）**：对**齐次线性分类器** $f(x;\theta)=\theta^T x$（Soudry 等，2018），梯度下降中参数范数本身发散（$\|\theta_t\|_2 \to \infty$），但其**归一化方向** $\theta_t / \|\theta_t\|_2$ 收敛到硬间隔 SVM 的最大 $\ell_2$ 间隔方向；对于特定**正齐次深层网络**，归一化方向的极限点收敛到最小范数间隔问题的 KKT 驻点（Lyu & Li, 2020），而两层过参数化 leaky-ReLU 网络上 SGD 对线性可分数据的收敛与泛化亦有专门理论证明（Brutzkus 等，2017）。
     - **欠定线性最小二乘（$d > n$）**：从 $\theta_0 = 0$ 出发的梯度下降始终保持在行空间中，从而精确收敛到**最小 $\ell_2$ 范数插值解** $\hat{\theta}_{\min} = X^+ Y$。
     *（注记：这些隐式正则化机制为线性、随机特征或核模型等典型设定中的**双下降曲线（Double Descent）**现象（Belkin 等，2019）提供了重要理论解释，但这些结果各有限定假设，不能概括为“一般过参数化深度网络的测试误差在过参数化区必然再次单调下降”。）*
