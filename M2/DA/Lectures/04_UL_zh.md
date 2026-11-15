# 无监督学习与降维：原文与中文逐段对照

> 正文按原课件顺序排列，英文或法语原文后紧跟中文；例子、练习、重复正文、公式、图表及文献均保留。图中文字保留原图语言。原课件错误与必要辨析以独立“译注”标明。

[原 PDF](04_UL.pdf) · [原文转换稿](04_UL.md) · [逐块对应清单](Translation-audit/2026-09-28-coverage.json) · [课程目录](../README.md)

**本讲目录**

- [无监督学习与降维](#section-01)
- [学习的另一幅“全景图”](#section-02)
- [本讲目标](#section-03)
- [稀疏性入门](#section-04)
- [今天的应用：具有（秩）稀疏性的矩阵补全——Netflix 推荐竞赛](#section-05)
- [今天的应用：具有（秩）稀疏性的矩阵补全——Netflix 推荐竞赛](#section-06)
- [稀疏特征选择与学习](#section-07)
- [A. 特征选择：LASSO 及其优化方法](#section-08)
- [LASSO 的优点](#section-09)
- [LASSO 估计的优化方法](#section-10)
- [第一种算法：最小角回归（LARS）](#section-11)
- [最小角回归：伪代码](#section-12)
- [第二种算法：坐标下降](#section-13)
- [第三种算法：近端方法](#section-14)
- [近端方法 $( 2 / 4 )$：近端算子的定义](#section-15)
- [近端方法（3/4）：应用于 LASSO](#section-16)
- [B. 特征学习：PCA 及其变体](#section-17)
- [PCA 的经典构造](#section-18)
- [PCA 应用于音乐推荐](#section-19)
- [PCA 应用于时间序列：职位招聘数据](#section-20)
- [PCA 应用于时间序列：职位招聘数据](#section-21)
- [PCA 应用于时间序列：职位招聘数据](#section-22)
- [PCA 应用于时间序列：金融数据（1/2）](#section-23)
- [从另一角度看 PCA](#section-24)
- [PCA 的低秩表述](#section-25)
- [线性代数背景：奇异值分解](#section-26)
- [非负矩阵分解](#section-27)
- [PCA 的推广：机器学习问题表述示例](#section-28)
- [C. 应用：矩阵补全与压缩感知](#section-29)
- [C.2. 字典学习](#section-30)
- [稀疏编码：问题表述](#section-31)
- [稀疏编码：走向非凸优化](#section-32)
- [C.3. 压缩感知](#section-33)
- [小结与其他主题](#section-34)

**重点定理与概念解释速查：**

- [从向量稀疏（$\ell_0 \to \ell_1$）到矩阵秩稀疏（$\operatorname{rank} \to \|\cdot\|_*$）及 LASSO 高维泛化界](#reading-lasso-oracle-and-sparsity)
- [LASSO 的三类优化算法：LARS、坐标下降与近端梯度（ISTA / FISTA）及软阈值推导](#reading-lasso-optimization-ista)
- [PCA 的两种等价视角、奇异值分解（SVD）与 Eckart–Young–Mirsky 低秩逼近定理证明](#reading-pca-svd-eckart-young)
- [PCA 的变体与推广：非负矩阵分解（NMF）与稳健主成分分析（Robust PCA）](#reading-nmf-and-robust-pca)
- [矩阵补全、核范数凸松弛与奇异值阈值算法（SVT）推导](#reading-matrix-completion-svt)
- [字典学习／稀疏编码的双凸交替优化与压缩感知（RIP 及精确恢复原理）](#reading-dictionary-learning-compressed-sensing)

**Data & Apprentissage Introduction `a la science des donn´ees et `a l’apprentissage**

**数据科学与机器学习导论**

Nicolas Vayatis

<a id="section-01"></a>

Apprentissage non supervise´ - R´eduction de dimension

## 无监督学习与降维

- Machine Learning is about learning (= choosing = estimating) a function from data

  机器学习就是从数据中学习（即选择、估计）一个函数。
- The key concept is the complexity of the function space (”hypothesis space”) where we look for our solution (”how many functions we select from”)

  关键概念是寻找解时所在函数空间（“假设空间”）的复杂度，即“从多少个函数中作选择”。
- The art of learning is to use the data to adjust the complexity of the hypothesis space - while implicitly considering the approximation error.

  学习的技巧在于利用数据调整假设空间的复杂度，同时隐含地考虑近似误差。
- In the particular case of least square linear regression, complexity calibration can (also) be achieved by only selecting and using a small subset of the variables (the problem of variable selection).

  对最小二乘线性回归这一特殊情形，也可以通过仅选择并使用一小部分变量来调整复杂度，这就是变量选择问题。

<a id="section-02"></a>

**Another ”Big picture” of Learning**

## 学习的另一幅“全景图”

![image](<Images/04_UL/image_001.jpg>)

<a id="section-03"></a>

**Objectives for this class**

## 本讲目标

- Focus on feature selection and feature learning: learning (”finding” or ”choosing”) a representation of the data (Theory so far: focused on learning functions for prediction and on bounding their generalization/prediction error for a given set of features (”representation”))

  重点是特征选择与特征学习：学习（“寻找”或“选择”）数据的一种表示。此前的理论重点是：对给定的特征集合（“表示”），学习用于预测的函数，并对其泛化／预测误差给出界。

Today: Develop new regularisation/machine learning formulations for other applications such as learning (= estimating the missing entries of) matrices - for example used in recommender systems

今天：针对其他应用提出新的正则化／机器学习表述，例如学习矩阵，即估计矩阵中缺失的元素；推荐系统就是一个应用例子。

- Also: We will learn about some optimization approaches to solve machine learning formulations/methods (possibly nonconvex optimization problems): Optimization is central for machine learning

  此外：学习一些求解机器学习问题表述／方法的优化途径，这些问题可能是非凸的。优化是机器学习的核心。

<a id="section-04"></a>

**A primer on parsity**

## 稀疏性入门

- Sparsity-inducing regression methods: LASSO

  诱导稀疏性的回归方法：LASSO。
- Motivation in linear predictive models: relaxation of $\ell _ { 0 }$ constraint on number of independent variables used, namely from minimizing

  在线性预测模型中的动机：松弛对所用自变量个数的 $\ell _ { 0 }$ 约束，即从最小化

$$
\| \mathbf {Y} - \mathbf {X} \boldsymbol {\beta} \| ^ {2} + \lambda \| \boldsymbol {\beta} \| _ {0}
$$

to minimizing

变为最小化

$$
\| \mathbf {Y} - \mathbf {X} \boldsymbol {\beta} \| ^ {2} + \lambda \| \boldsymbol {\beta} \| _ {1}
$$

- Advantages: tractable computations, interpretable models

  优点：计算可处理，模型可解释。
- Byproduct: sparsistency (i.e. how many, and which variables to use)

  附带结果：稀疏选择一致性，即使用多少个变量、使用哪些变量。

<a id="section-05"></a>

Application (today): Matrix completion with (rank) Sparsity (”Netflix Recommendation Competition”)

## 今天的应用：具有（秩）稀疏性的矩阵补全——Netflix 推荐竞赛

![image](<Images/04_UL/image_002.jpg>)

Rating Matrix

评分矩阵

<a id="section-06"></a>

Application (today): Matrix completion with (rank) Sparsity (”Netflix Recommendation Competition”)

## 今天的应用：具有（秩）稀疏性的矩阵补全——Netflix 推荐竞赛

- Given a matrix M with missing values, find the matrix X with minimal rank (why? - see later today) which coincides with the available coeficients of M:

  给定含有缺失值的矩阵 M，寻找与 M 的已知元素一致且秩最小的矩阵 X（为什么要秩最小？本讲稍后说明）：

$$
\min _ {X} \{\operatorname{rank} (X) \} \text{满足} X _ {i j} = M _ {i j}    , \forall (i, j) \in \Omega
$$

where $\Omega = \{ ( i , j ) : M _ { i j }$ not missing}.

其中 $\Omega=\{(i,j):M_{ij}\text{ 未缺失}\}$。

- How to solve this dificult optimization problem? Why is it dificult?

  怎样求解这个困难的优化问题？它为什么困难？

<a id="section-07"></a>

**Sparse Feature Selection and Learning**

## 稀疏特征选择与学习

A. Feature Selection: LASSO with optimization methods

A. 特征选择：LASSO 及其优化方法。

B. Feature Learning: PCA and variants

B. 特征学习：PCA 及其变体。

C. Applications: matrix completion, sparse coding, compressed sensing

C. 应用：矩阵补全、稀疏编码、压缩感知。

<a id="section-08"></a>

A. Feature selection: LASSO with optimization methods

## A. 特征选择：LASSO 及其优化方法

The LASSO for linear models From $\ell _ { 0 }$ to $\ell _ { 1 }$

### 线性模型的 LASSO：从 $\ell _ { 0 }$ 到 $\ell _ { 1 }$

- Consider the LASSO estimation (learning) method: for any $\lambda > 0$

  考虑 LASSO 估计（学习）方法：对任意 $\lambda > 0$，

$$
\widehat {\beta} _ {\lambda} \in \underset {\beta \in \mathbb {R} ^ {d}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| ^ {2} + \lambda \| \beta \| _ {1} \right\}
$$

where the $\ell _ { 1 } { \mathrm { - } } \mathsf { n o r m }$ is:

其中 $\ell _ { 1 } { \mathrm { - } } \mathsf { n o r m }$ 为：

$$
\| \beta \| _ {1} = \sum_ {j = 1} ^ {d} | \beta_ {j} |
$$

<a id="section-09"></a>

**Blessings of the LASSO**

## LASSO 的优点

- Approximate solutions via eficient algorithms building the so-called regularization path (find for all values of λ the ${ \widehat { \beta } } ( \lambda ) )$

  通过构建所谓正则化路径的高效算法求近似解：对 λ 的所有取值，找到相应的 ${ \widehat { \beta } } ( \lambda ) )$。

![image](<Images/04_UL/image_003.jpg>)

- Theoretical soundness: it can be shown that (if the real model is linear): as $n , d \to \infty$

  理论依据：可以证明（如果真实模型是线性的），当 $n , d \to \infty$ 时，

$$
\frac {1}{n} \mathbb {E} \big (\| \mathbf {X} \beta^ {*} - \mathbf {X} \widehat {\beta} \| ^ {2} \big) \leq C \| \beta^ {*} \| _ {1} \sqrt {\frac {\log d}{n}}
$$

<a id="reading-lasso-oracle-and-sparsity"></a>

**Complément — from vector sparsity to rank sparsity, and why the $\sqrt{(\log d)/n}$ LASSO bound matters**

**补充——从向量稀疏到矩阵秩稀疏，以及如何读懂 LASSO 的 $\sqrt{(\log d)/n}$ 高维预测界**

Sections 4 to 9 connect two forms of sparsity through the same convex-relaxation principle:

第 4 至 9 节通过同一个“凸松弛（convex relaxation）”思想，把向量特征选择与矩阵低秩恢复联系了起来：

| Problem setting / 问题设定 | Nonconvex cardinality measure / 非凸计数度量（NP-hard） | Tightest convex relaxation / 最紧凸松弛（可高效求解） | Meaning of sparsity / 稀疏性的具体含义 |
|---|---|---|---|
| **Linear regression** ($\beta \in \mathbb{R}^d$) / **线性回归**（参数向量 $\beta \in \mathbb{R}^d$） | $\ell_0$ pseudo-norm: $\|\beta\|_0 = \#\{j : \beta_j \neq 0\}$ / $\ell_0$ 伪范数：非零系数个数 $\|\beta\|_0$ | $\ell_1$ norm: $\|\beta\|_1 = \sum_{j=1}^d |\beta_j|$ / $\ell_1$ 范数：系数绝对值之和 $\|\beta\|_1$ | Only a few features $X^{(j)}$ affect the response $Y$ / 只有少数输入特征 $X^{(j)}$ 对预测响应 $Y$ 有贡献 |
| **Matrix completion / PCA** ($X \in \mathbb{R}^{n_1\times n_2}$) / **矩阵补全／低秩建模**（矩阵 $X \in \mathbb{R}^{n_1\times n_2}$） | Matrix rank: $\operatorname{rank}(X) = \|\sigma(X)\|_0$ / 矩阵的秩：非零奇异值个数 $\operatorname{rank}(X) = \|\sigma(X)\|_0$ | Nuclear norm: $\|X\|_* = \sum_i \sigma_i(X) = \|\sigma(X)\|_1$ / 核范数（迹范数）：奇异值之和 $\|X\|_* = \sum_i \sigma_i(X)$ | Ratings are explained by a few latent factors ($r \ll \min(n_1,n_2)$) / 整张评分矩阵由少数潜在因子（如 $r$ 个兴趣维度）线性生成 |

**Why the LASSO prediction bound in Section 9 is a high-dimensional breakthrough:**
In fixed-design linear regression $Y = \mathbf{X}\beta^* + \varepsilon$ with $\mathbb{E}[\varepsilon]=0$ and $\operatorname{Cov}(\varepsilon)=\sigma^2 I_n$, any ordinary least squares (OLS) fit projects $Y$ orthogonally onto the column space $\operatorname{Im}(\mathbf{X})$, so its in-sample prediction error is $\frac{1}{n}\mathbb{E}\|\mathbf{X}\widehat{\beta}_{\text{OLS}} - \mathbf{X}\beta^*\|_2^2 = \sigma^2 \frac{\operatorname{rank}(\mathbf{X})}{n} \le \sigma^2$. In the classical low-dimensional full-column-rank regime ($d \le n$ and $\operatorname{rank}(\mathbf{X}) = d$), this equals $\sigma^2 \frac{d}{n}$, which grows linearly with $d$. Once $d \ge n$ (with $\operatorname{rank}(\mathbf{X}) = n$), OLS simply interpolates the noisy observations ($\mathbf{X}\widehat{\beta}_{\text{OLS}} = Y$), so the in-sample error stays stuck at $\sigma^2 \not\to 0$ (no denoising), while $\mathbf{X}^T\mathbf{X}$ becomes singular—making $\widehat{\beta}_{\text{OLS}}$ non-unique and out-of-sample prediction unstable without regularization. By contrast, the LASSO bound in Section 9 (known as the **slow rate** or **basic inequality bound** under column-normalized design and sub-Gaussian noise):

**为什么第 9 节的 LASSO 预测误差界是高维统计的核心突破：**
在固定设计线性模型 $Y = \mathbf{X}\beta^* + \varepsilon$（$\mathbb{E}[\varepsilon]=0, \operatorname{Cov}(\varepsilon)=\sigma^2 I_n$）下，普通最小二乘（OLS）拟合值 $\mathbf{X}\widehat{\beta}_{\text{OLS}}$ 是 $Y$ 向列空间 $\operatorname{Im}(\mathbf{X})$ 的正交投影，因此其样本内预测误差精确等于 $\frac{1}{n}\mathbb{E}\|\mathbf{X}\widehat{\beta}_{\text{OLS}} - \mathbf{X}\beta^*\|_2^2 = \sigma^2 \frac{\operatorname{rank}(\mathbf{X})}{n} \le \sigma^2$。只有当设计矩阵满列秩（$d \le n$ 且 $\operatorname{rank}(\mathbf{X}) = d$）时，该式才写成第二课中的 $\sigma^2 \frac{d}{n}$ 并随维度 $d$ 线性增长；而当进入高维情形 $d \ge n$（通常 $\operatorname{rank}(\mathbf{X}) = n$）时，OLS 直接插值含噪观测（$\mathbf{X}\widehat{\beta}_{\text{OLS}} = Y$），样本内误差停留在常数 $\sigma^2 \not\to 0$（失去降噪能力），同时 $\mathbf{X}^T\mathbf{X}$ 奇异不可逆，导致参数解 $\widehat{\beta}_{\text{OLS}}$ 不唯一、样本外预测缺乏稳定性。相比之下，第 9 节给出的 LASSO 预测界（在列归一化与高斯噪声下称为 **LASSO 慢速界 / slow rate**）：

$$
\frac{1}{n}\mathbb{E}\big(\|\mathbf{X}\beta^* - \mathbf{X}\widehat{\beta}_\lambda\|^2\big) \le C \|\beta^*\|_1 \sqrt{\frac{\log d}{n}}
$$

replaces the linear dimension factor $d/n$ with $\sqrt{(\log d)/n}$! Even if $d = 10^6$ features and $n = 1000$ samples, we have $\sqrt{(\log d)/n} \approx \sqrt{13.8/1000} \approx 0.118$. As long as the true parameter vector $\beta^*$ has a bounded $\ell_1$ norm $\|\beta^*\|_1$, LASSO achieves consistent in-sample denoising even in ultra-high dimensions ($\log d \ll n$). Furthermore, if the design matrix $\mathbf{X}$ satisfies a *Restricted Eigenvalue* or *Compatibility* condition (controlling collinearity on sparse subsets of columns) and $\beta^*$ has $s = \|\beta^*\|_0$ nonzero entries, LASSO achieves an even sharper **fast oracle rate** of order $O\!\left(\sigma^2 \frac{s \log d}{n}\right)$, matching up to the $\log d$ variable-selection factor the error $O(\sigma^2 s/n)$ one would get if the $s$ relevant variables were known in advance!

将维度依赖从满秩时的 $d/n$ 降到了对数平方根 $\sqrt{(\log d)/n}$！例如当 $d = 10^6$ 个特征而样本只有 $n = 1000$ 时，$\sqrt{(\log d)/n} \approx \sqrt{13.8/1000} \approx 0.118$ 依然很小。只要真实参数 $\beta^*$ 的 $\ell_1$ 范数 $\|\beta^*\|_1$ 有界，即使维度 $d$ 远大于 $n$（只要 $\log d \ll n$），LASSO 的样本内预测误差仍随 $n\to\infty$ 趋于零。不仅如此，若设计矩阵 $\mathbf{X}$ 满足**限制特征值条件（Restricted Eigenvalue condition，即稀疏列子集上无强共线性）**且真实非零个数为 $s = \|\beta^*\|_0$，LASSO 还能达到更快的 **快速度（fast oracle rate）** $O\!\left(\sigma^2 \frac{s \log d}{n}\right)$——相比事先知道哪 $s$ 个变量有用时的理想最小二乘误差 $O(\sigma^2 s/n)$，仅多付出了一个在 $d$ 个候选变量中搜索支撑集的对数因子 $\log d$！

<a id="sparse-optimization"></a>

<a id="section-10"></a>

**Optimization methods for LASSO estimation**

## LASSO 估计的优化方法

[mainly pointers to diferent approaches and literatures]

［主要提供不同方法及文献的线索。］

- Least Angle Regression

  最小角回归。
- Coordinate Descent

  坐标下降。
- Proximal methods

  近端方法。

<a id="section-11"></a>

**First algorithm: Least Angle Regression (LARS)**

## 第一种算法：最小角回归（LARS）

- LARS = variant of the incremental stagewise procedure for adding variables in a linear model

  LARS 是向线性模型中逐步增加变量的增量过程的一种变体。
- Least Angle Regression paper by Efron-Hastie-Johnstone-Tibshirani (AoS, 2004)

  Efron、Hastie、Johnstone、Tibshirani 的论文 Least Angle Regression（最小角回归），发表于 Annals of Statistics，2004 年。
- Previous work by Osborne et al. (2000) on the so-called homotopy method

  更早的工作包括 Osborne 等（2000）提出的所谓同伦方法。
- Also related to greedy approaches such as Orthogona Matching Pursuit (by Mallat, Zhang (1993), Mallat, Davis, Zhang (1994))

  也与正交匹配追踪等贪心方法有关（Mallat、Zhang，1993；Mallat、Davis、Zhang，1994）。
- Recovers the full regularization path $\lambda \to { \hat { \beta } } ( \lambda )$ of the LASSO

  恢复 LASSO 的完整正则化路径 $\lambda \to { \hat { \beta } } ( \lambda )$。
- Success of the procedure based on the fact that LASSO path is piecewise linear.

  该过程之所以成功，基于 LASSO 路径分段线性这一事实。
- Computational eficiency: one ordinary least square computation at each step

  计算效率：每一步进行一次普通最小二乘计算。

<a id="section-12"></a>

**Least Angle Regression: Pseudocode**

## 最小角回归：伪代码

1. 1 Start with all coeficients $\beta$ equal to zero.

   从所有系数 $\beta$ 均为零开始。
2. 2 Find the predictor $x _ { j }$ most correlated with y

   找出与 y 相关性最高的预测变量 $x _ { j }$。
3. 3 Increase the coeficient $\beta _ { j }$ in the direction of the sign of its correlation with y until some other predictor $x _ { k }$ has as much correlation with $\boldsymbol { r } = \boldsymbol { y } - \boldsymbol { \hat { y } }$ as $x _ { j }$ has.

   沿着与 y 的相关系数符号所指的方向增加系数 $\beta _ { j }$，直到另一个预测变量 $x _ { k }$ 与 $\boldsymbol { r } = \boldsymbol { y } - \boldsymbol { \hat { y } }$ 的相关程度达到 $x _ { j }$ 的水平。
4. 4 Increase $( \beta _ { j } , \beta _ { k } )$ in their joint least squares direction, until some other predictor $x _ { m }$ has as much correlation with the residual r.

   沿联合最小二乘方向增加 $( \beta _ { j } , \beta _ { k } )$，直到另一个预测变量 $x _ { m }$ 与残差 r 的相关程度也达到相同水平。
5. 5 Continue until: all predictors are in the model (corresponding to the solution when λ is small)

   继续，直到所有预测变量都进入模型，这对应于 λ 很小时的解。

> **译注：** 原页是最小角回归的概略伪代码。构造完整 LASSO 路径时还需处理活跃系数降到零、从活跃集中移除等步骤。

<a id="section-13"></a>

**Second algorithm: Coordinate Descent**

## 第二种算法：坐标下降

- Simple idea of one dimensional optimization with cyclic iteration over all variables, until convergence

  简单思路：循环遍历所有变量，每次进行一维优化，直到收敛。
- Optimization at each step amounts to a one-dimensional LASSO problem

  每一步的优化相当于一个一维 LASSO 问题。
- Solution obtained as a soft thresholding of the one-dimensional ordinary least square estimate.

  解由一维普通最小二乘估计经过软阈值处理得到。

![image](<Images/04_UL/image_004.jpg>)

<a id="section-14"></a>

**Third algorithm: Proximal methods**

## 第三种算法：近端方法

Parikh-Boyd tutorial paper (2013): ”Much like Newton’s method is a standard tool for solving unconstrained smooth optimization problems of modest size, proximal algorithms can be viewed as an analogous tool for nonsmooth, constrained, large-scale, or distributed versions of these problems.”

Parikh 与 Boyd 的教程论文（2013）：“正如 Newton 方法是求解中等规模无约束光滑优化问题的标准工具，近端算法可以看作处理这些问题的非光滑、带约束、大规模或分布式版本的类似工具。”

- Early work goes back to Moreau (1960s) then Nemirovski, Yudin (1983)

  早期工作可追溯至 Moreau（20 世纪 60 年代），以及后来的 Nemirovski、Yudin（1983）。
- Rediscovered around 2005 with applications to signal processing and solving certain optimization problems • Applies to a problem of the form:

  大约在 2005 年因信号处理应用及某些优化问题的求解而重新受到重视。
- 适用于如下形式的问题：

$$
\min _ {\beta} \left\{L (\beta) + \psi (\beta) \right\}
$$

when: L is smooth, convex, with ”bounded” gradient, and $\psi$ is continuous, convex, but non-smooth

其中 L 光滑、凸、梯度“有界”，而 $\psi$ 连续、凸，但不光滑。

- The proximal algorithm is a descent algorithm which provides a sequence $\beta _ { t }$ obtained as follows: at each step t,

  近端算法是一种下降算法，按如下方式产生序列 $\beta _ { t }$：在每一步 t，

$$
\beta_ {t} = \operatorname{prox} \left(\psi , \beta_ {t - 1} - \nabla L \left(\beta_ {t - 1}\right)\right)
$$

> **译注：** 原页省略了步长，且“梯度有界”不是通常所用的光滑性条件。若 $\nabla L$ 为 $L_g$-Lipschitz，标准近端梯度步写作 $\beta_t=\operatorname{prox}_{\eta\psi}(\beta_{t-1}-\eta\nabla L(\beta_{t-1}))$，例如取 $0<\eta\le1/L_g$；近端项通常要求适当、下半连续且凸。

where prox is the so-called proximal operator (generalizes the concept of orthogonal projection)

其中 prox 是所谓的近端算子，它推广了正交投影的概念。

<a id="section-15"></a>

**Proximal method $( 2 / 4 )$ Definition of proximal operator**

## 近端方法 $( 2 / 4 )$：近端算子的定义

- Definition of the proximal operator for the nonsmooth term $\psi$ of the objective $L + \psi$

  对目标函数 $L + \psi$ 中的非光滑项 $\psi$，近端算子定义为：

$$
\operatorname{prox} \bigl (\psi , z \bigr) = \arg \min _ {\beta} \left\{\frac {1}{2} \| \beta - z \| _ {2} ^ {2} + \psi (\beta) \right\}
$$

- Interpretation: The proximal operator finds a point that corresponds to a trade-of between minimizing $\psi$ and being near to the point z.

  解释：近端算子寻找一个点，在减小 $\psi$ 与靠近点 z 之间取得权衡。

<a id="section-16"></a>

**Proximal method (3/4) Application to LASSO**

## 近端方法（3/4）：应用于 LASSO

- Here: $\begin{array} { r } { L ( \beta ) = \frac { 1 } { 2 } \| X \beta - y \| _ { 2 } ^ { 2 } } \end{array}$ and $\psi ( { \boldsymbol { \beta } } ) = \lambda \| { \boldsymbol { \beta } } \| _ { 1 }$

  这里 $\begin{array} { r } { L ( \beta ) = \frac { 1 } { 2 } \| X \beta - y \| _ { 2 } ^ { 2 } } \end{array}$，且 $\psi ( { \boldsymbol { \beta } } ) = \lambda \| { \boldsymbol { \beta } } \| _ { 1 }$。
- Gradient step relies on the gradient of the smooth term L:

  梯度步使用光滑项 L 的梯度：

$$
\nabla L (\beta) = X ^ {T} (X \beta - y)
$$

- Proximal operator for the $\ell _ { 1 }$ norm is given by:

  $\ell _ { 1 }$ 范数的近端算子为：

$$
\operatorname{prox} (\lambda \| \cdot \| _ {1}, z) = (z - \lambda) _ {+} - (- z - \lambda) _ {+}
$$

(soft thresholding operator on each component of $z )$

（对 $z )$ 的每个分量施加软阈值算子。）

- Also called ISTA (for Iterative Shrinkage Thresholding Algorithm)

  也称 ISTA，即 Iterative Shrinkage Thresholding Algorithm（迭代收缩阈值算法）。
- Special cases: gradient descent, projected gradient

  特殊情形：梯度下降、投影梯度。
- Accelerated version: FISTA for Fast Iterative Shrinkage Thresholding Algorithm

  加速版本：FISTA，即 Fast Iterative Shrinkage Thresholding Algorithm（快速迭代收缩阈值算法）。
- Numerical convergence: from $O ( 1 / t )$ to $O ( 1 / t ^ { 2 } )$

  数值收敛速度：从 $O ( 1 / t )$ 改进到 $O ( 1 / t ^ { 2 } )$。

<a id="reading-lasso-optimization-ista"></a>

**Complément — why LASSO requires iterative algorithms, derivation of the soft-thresholding proximal operator, and comparison of LARS, Coordinate Descent, and ISTA/FISTA**

**补充——为什么 LASSO 需要专门的优化算法、软阈值近端算子的完整推导，以及三种算法的对比**

Unlike Ridge regression, where the smooth penalty $\lambda\|\beta\|_2^2$ has gradient $2\lambda\beta$ and yields the linear system $(X^T X + \lambda I_d)\hat{\beta} = X^T y$, the $\ell_1$ norm $\|\beta\|_1 = \sum_{j=1}^d |\beta_j|$ is **not differentiable whenever any coordinate $\beta_j = 0$**. When columns of $X$ are not orthogonal, the signs of the active coordinates interact, so no general closed-form matrix formula exists. However, the objective is still **convex** and decomposes into a smooth quadratic part $L(\beta) = \frac{1}{2}\|X\beta - y\|_2^2$ plus a separable nonsmooth part $\psi(\beta) = \lambda\|\beta\|_1$. Both Coordinate Descent (§13) and Proximal Gradient / ISTA (§14–16) rely on the exact closed-form solution of the **1D $\ell_1$ proximal problem**!

与岭回归（光滑惩罚 $\lambda\|\beta\|_2^2$ 的梯度为 $2\lambda\beta$，可直接解线性方程组 $(X^T X + \lambda I_d)\hat{\beta} = X^T y$）不同，LASSO 的 $\ell_1$ 范数 $\|\beta\|_1 = \sum_{j=1}^d |\beta_j|$ **在任意坐标 $\beta_j = 0$ 处均不可微**。当设计矩阵 $X$ 的各列不正交时，哪些系数非零及其正负号相互耦合，因此一般没有显式矩阵求逆公式。但 LASSO 目标函数依然是**凸函数**，且具有“光滑二次损失 $L(\beta) = \frac{1}{2}\|X\beta - y\|_2^2$ + 可分离非光滑惩罚 $\psi(\beta) = \lambda\|\beta\|_1$”的复合结构。无论是坐标下降（§13）还是近端梯度算法 ISTA（§14–16），它们最核心的计算积木都是**一维 $\ell_1$ 近端算子（软阈值算子）的闭式解**！

**Derivation: why the proximal operator of $\lambda\|\cdot\|_1$ is the soft-thresholding operator $S_\lambda(z)$, and how $\operatorname{prox}_\psi$ generalizes orthogonal projection**

**推导：为什么 $\lambda\|\cdot\|_1$ 的近端算子恰好是软阈值算子 $S_\lambda(z)$，以及近端算子如何推广正交投影**

1. **Derivation of 1D soft-thresholding (§15–16) 一维软阈值算子的严格推导 :**
   Because $\|\beta - z\|_2^2 = \sum_{j=1}^d (\beta_j - z_j)^2$ and $\|\beta\|_1 = \sum_{j=1}^d |\beta_j|$ both sum over coordinates $j=1,\dots,d$ independently, the $d$-dimensional proximal minimization in Section 15 decouples into $d$ independent scalar problems:

   由于欧氏距离平方 $\|\beta - z\|_2^2 = \sum_{j=1}^d (\beta_j - z_j)^2$ 与 $\ell_1$ 范数 $\|\beta\|_1 = \sum_{j=1}^d |\beta_j|$ 均按坐标可分离，第 15 节的 $d$ 维近端最小化完全拆解为 $d$ 个独立的一维标量问题：

$$
\big[\operatorname{prox}_{\lambda\|\cdot\|_1}(z)\big]_j = \underset{b \in \mathbb{R}}{\arg\min} \left\{ \frac{1}{2}(b - z_j)^2 + \lambda |b| \right\}, \qquad \lambda > 0.
$$

   The subdifferential of $|b|$ is $\partial |b| = \{+1\}$ if $b > 0$, $\{-1\}$ if $b < 0$, and the interval $[-1, +1]$ if $b = 0$. By Fermat's rule for convex functions, $b^*$ minimizes the objective if and only if $0 \in (b^* - z_j) + \lambda \partial |b^*|$:
   - **Case 1 ($b^* > 0$):** $(b^* - z_j) + \lambda(1) = 0 \implies b^* = z_j - \lambda$. This is valid if and only if $z_j - \lambda > 0 \iff z_j > \lambda$.
   - **Case 2 ($b^* < 0$):** $(b^* - z_j) + \lambda(-1) = 0 \implies b^* = z_j + \lambda$. This is valid if and only if $z_j + \lambda < 0 \iff z_j < -\lambda$.
   - **Case 3 ($b^* = 0$):** $0 \in -z_j + \lambda[-1, 1] \iff z_j \in [-\lambda, \lambda] \iff |z_j| \le \lambda$.

   绝对值函数 $|b|$ 的次微分（subdifferential）为：当 $b > 0$ 时 $\partial |b| = \{+1\}$；当 $b < 0$ 时 $\partial |b| = \{-1\}$；当 $b = 0$ 时为闭区间 $\partial |b| = [-1, +1]$。由凸优化的 Fermat 最优性条件，$b^*$ 为全局极小点的充要条件是 $0 \in (b^* - z_j) + \lambda \partial |b^*|$：
   - **情形 1（$b^* > 0$）：** $(b^* - z_j) + \lambda = 0 \implies b^* = z_j - \lambda$，该解成立当且仅当 $z_j > \lambda$；
   - **情形 2（$b^* < 0$）：** $(b^* - z_j) - \lambda = 0 \implies b^* = z_j + \lambda$，该解成立当且仅当 $z_j < -\lambda$；
   - **情形 3（$b^* = 0$）：** $0 \in -z_j + \lambda[-1, 1] \iff z_j \in [-\lambda, \lambda] \iff |z_j| \le \lambda$。

   Combining the three cases yields the **soft-thresholding operator** $S_\lambda(z_j)$:

   合并三种情形，即得第 16 节给出的**软阈值算子（soft-thresholding operator）** $S_\lambda(z_j)$：

$$
S_\lambda(z_j)
= \begin{cases}
z_j - \lambda, & \text{if / 若 } z_j > \lambda, \\
0, & \text{if / 若 } |z_j| \le \lambda, \\
z_j + \lambda, & \text{if / 若 } z_j < -\lambda,
\end{cases}
\;= \operatorname{sgn}(z_j)\big(|z_j| - \lambda\big)_+
= (z_j - \lambda)_+ - (-z_j - \lambda)_+.
$$

   Every coordinate inside the dead-zone $[-\lambda, \lambda]$ is set **exactly to zero** (producing sparsity!), while coordinates outside $[-\lambda, \lambda]$ are shrunk toward zero by $\lambda$.
   **Numerical example:** For $z = (2.5, -0.4, -1.8)^T$ and $\lambda = 1.0$, soft-thresholding immediately gives $S_{1.0}(z) = (1.5, 0, -0.8)^T$.

   可以看到：凡是落入死区 $[-\lambda, \lambda]$ 内的坐标都会被**精确置零**（从而产生稀疏解！），而超出阈值的坐标则向零收缩 $\lambda$。
   **数值例子：** 若梯度步之后的向量为 $z = (2.5, -0.4, -1.8)^T$，阈值取 $\lambda = 1.0$，则逐分量软阈值立刻给出 $S_{1.0}(z) = (1.5, 0, -0.8)^T$。

2. **Why does the proximal operator generalize orthogonal projection (§14 & §16)? 为什么近端算子是正交投影的推广（§14、§16）？**
   Let $C \subset \mathbb{R}^d$ be a nonempty closed convex set, and let $\psi(\beta) = \iota_C(\beta)$ be its convex indicator function ($\iota_C(\beta) = 0$ if $\beta \in C$, and $+\infty$ if $\beta \notin C$). Substituting $\psi = \iota_C$ into the definition of $\operatorname{prox}_\psi(z)$ (§15):

   设 $C \subset \mathbb{R}^d$ 为非空闭凸集，令 $\psi(\beta) = \iota_C(\beta)$ 为 $C$ 的凸示性函数（当 $\beta \in C$ 时取 $0$，当 $\beta \notin C$ 时取 $+\infty$）。将 $\psi = \iota_C$ 代入第 15 节近端算子的定义：

$$
\operatorname{prox}_{\iota_C}(z)
= \underset{\beta \in \mathbb{R}^d}{\arg\min} \left\{ \frac{1}{2}\|\beta - z\|_2^2 + \iota_C(\beta) \right\}
= \underset{\beta \in C}{\arg\min} \; \frac{1}{2}\|\beta - z\|_2^2
= \Pi_C(z),
$$

   which is the Euclidean **orthogonal projection** of $z$ onto $C$! Consequently:
   - When $\psi(\beta) \equiv 0$, $\operatorname{prox}_0(z) = z$, and the proximal gradient step reduces to standard **gradient descent** $\beta_t = \beta_{t-1} - \eta\nabla L(\beta_{t-1})$.
   - When $\psi(\beta) = \iota_C(\beta)$, it reduces to **projected gradient descent** $\beta_t = \Pi_C\big(\beta_{t-1} - \eta\nabla L(\beta_{t-1})\big)$.
   - When $\psi(\beta) = \lambda\|\beta\|_1$, it yields **ISTA** $\beta_t = S_{\eta\lambda}\big(\beta_{t-1} - \eta X^T(X\beta_{t-1}-y)\big)$!

   这正是点 $z$ 到闭凸集 $C$ 上的欧氏**正交投影算子** $\Pi_C(z)$！因此，第 16 节所说的特殊情形一目了然：
   - 当 $\psi(\beta) \equiv 0$ 时，$\operatorname{prox}_0(z) = z$，近端梯度法退化为普通**梯度下降** $\beta_t = \beta_{t-1} - \eta\nabla L(\beta_{t-1})$；
   - 当 $\psi(\beta) = \iota_C(\beta)$ 时，$\operatorname{prox}_{\iota_C} = \Pi_C$，近端梯度法退化为**投影梯度下降** $\beta_t = \Pi_C\big(\beta_{t-1} - \eta\nabla L(\beta_{t-1})\big)$；
   - 当 $\psi(\beta) = \lambda\|\beta\|_1$ 时，$\operatorname{prox}_{\eta\lambda\|\cdot\|_1} = S_{\eta\lambda}$，近端梯度法即为 **ISTA（迭代收缩阈值算法）** $\beta_t = S_{\eta\lambda}\big(\beta_{t-1} - \eta X^T(X\beta_{t-1}-y)\big)$！

**Comparison of the three LASSO optimization methods (§11–16)**

**三种 LASSO 优化算法的对比与适用场景（§11–16）**

| Algorithm / 算法 | Core mechanism at each step / 每一步的核心计算机制 | Output & convergence behavior / 输出特性与收敛速度 | When to prefer it / 适用场景 |
|---|---|---|---|
| **LARS / Homotopy (§11–12)** / 最小角回归／同伦法 | Exploits the fact that $\hat{\beta}(\lambda)$ is **piecewise linear** in $\lambda$; moves along equiangular least-squares directions among active variables until a new variable enters (or an active variable hits $0$). / 利用正则化路径 $\hat{\beta}(\lambda)$ 的**分段线性性质**，沿当前活跃集与残差等夹角的最小二乘方向推进，直至新变量进入或旧变量归零。 | Computes the **entire exact regularization path** $\{\hat{\beta}(\lambda) : \lambda > 0\}$ in a finite number of steps (each requiring an OLS solve on the active set). / 有限步内精确算出**整条正则化路径** $\{\hat{\beta}(\lambda) : \lambda > 0\}$，每步需要对当前活跃集求一次最小二乘。 | Moderate dimension $d$ when the full path $\lambda \mapsto \hat{\beta}(\lambda)$ is desired. / 中等维度 $d$、需要完整观察整条系数路径 $\lambda \mapsto \hat{\beta}(\lambda)$ 时。 |
| **Coordinate Descent (§13)** / 坐标下降法 | Fixes all coordinates except $\beta_j$, computes the partial residual $r^{(-j)} = y - \sum_{k\neq j} X_{\cdot,k}\beta_k$, and applies 1D soft-thresholding $\beta_j \leftarrow \frac{1}{\|X_{\cdot,j}\|_2^2} S_\lambda(X_{\cdot,j}^T r^{(-j)})$. / 固定其余 $d-1$ 个坐标，计算偏残差 $r^{(-j)} = y - \sum_{k\neq j} X_{\cdot,k}\beta_k$，对单变量做一维软阈值更新。 | Each coordinate update costs $O(n)$ with warm-starts and active-set screening; very fast for sparse solutions (used in `glmnet` and `scikit-learn`). / 单坐标更新仅需 $O(n)$，配合热启动（warm start）与活跃集筛选极快（`glmnet` 与 `scikit-learn` 默认采用）。 | Standard tabular LASSO / Elastic Net, even for large $n$ and $d$. / 标准表格数据的 LASSO 与 Elastic Net 首选求解器。 |
| **Proximal Gradient: ISTA / FISTA (§14–16)** / 近端梯度法（ISTA / FISTA） | Full gradient step $z_t = \beta_{t-1} - \eta X^T(X\beta_{t-1}-y)$ (with $0 < \eta \le 1/\|X^T X\|_{\text{op}}$) followed by componentwise soft-thresholding $S_{\eta\lambda}(z_t)$. FISTA applies Nesterov momentum extrapolation before the gradient step. / 先沿光滑项负梯度走一步 $z_t = \beta_{t-1} - \eta X^T(X\beta_{t-1}-y)$（步长 $0 < \eta \le 1/\|X^T X\|_{\text{op}}$），再做软阈值 $S_{\eta\lambda}(z_t)$；FISTA 在梯度步前加入 Nesterov 动量外推。 | Sublinear objective error $F(\beta_t) - F^* = O(1/t)$ for ISTA, accelerated to optimal first-order rate $O(1/t^2)$ for **FISTA** (Beck & Teboulle, 2009) at virtually the same per-iteration cost. / 目标值误差从 ISTA 的 $O(1/t)$ 加速至 **FISTA**（Beck & Teboulle, 2009）的一阶最优速率 $O(1/t^2)$，且每步计算量几乎不变。 | Large-scale problems where $X$ is a fast linear operator (e.g., FFT / wavelet / convolution in signal processing) or for non-separable penalties like Group LASSO / nuclear norm (SVT, §29). / 大规模算子型问题（如傅里叶／小波变换）或不可按坐标分离的惩罚（如 Group LASSO、§29 核范数 SVT）。 |

<a id="pca"></a>

<a id="section-17"></a>

B. Feature Learning: PCA and variants

## B. 特征学习：PCA 及其变体

**What all students should know PCA**

### 所有学生都应该知道的内容：PCA

- Motivation: Dimensionality reduction

  动机：降维。
- Principle: Find an orthogonal basis to represent (project on) the data, which captures the directions of highest dispersion (variance) of the data

  原理：寻找一组正交基来表示数据、将数据投影到其上，使其捕获数据离散程度（方差）最大的方向。
- Underlying assumption: Gaussian, highly correlated data

  隐含假设：高斯且高度相关的数据。

> **译注：** 高斯性不是计算 PCA 的必要条件；PCA 的线性代数构造适用于一般具有有限二阶矩的数据。这里保留原课件的建模动机。

![image](<Images/04_UL/image_005.jpg>)

<a id="section-18"></a>

**PCA Classical construction**

## PCA 的经典构造

- Compute the covariance (or correlation) matrix of the data

  计算数据的协方差矩阵或相关矩阵。
- Find the eigen-elements (values/vectors) - eigenvectors being orthogonal - of this matrix

  求出该矩阵的特征值和特征向量；特征向量彼此正交。
- Principal components are ordered from the larger eigenvalue to the smallest

  主成分按特征值从大到小排列。
- Dimensionality reduction from d to (small) r is performed by projecting the initial data points on the first (principal) r eigenvectors

  将原始数据点投影到前 r 个主要特征向量上，将维度从 d 降到较小的 r。

<a id="section-19"></a>

**PCA applied to music recommendation**

## PCA 应用于音乐推荐

LastFM data set

LastFM 数据集。

![image](<Images/04_UL/image_006.jpg>)

![image](<Images/04_UL/image_007.jpg>)

<a id="section-20"></a>

**PCA applied to time series Job hiring data**

## PCA 应用于时间序列：职位招聘数据

JOLTS data set available at https://www.bls.gov/jlt/>

JOLTS 数据集可从 https://www.bls.gov/jlt/ 获取。

![image](<Images/04_UL/image_008.jpg>)

![image](<Images/04_UL/image_009.jpg>)

<a id="section-21"></a>

**PCA applied to time series Job hiring data**

## PCA 应用于时间序列：职位招聘数据

**Components interpretation**

### 成分解释

![image](<Images/04_UL/image_010.jpg>)

![image](<Images/04_UL/image_011.jpg>)

![image](<Images/04_UL/image_012.jpg>)

![image](<Images/04_UL/image_013.jpg>)

<a id="section-22"></a>

**PCA applied to time series Job hiring data**

## PCA 应用于时间序列：职位招聘数据

**Projection on principal components**

### 投影到主成分

![image](<Images/04_UL/image_014.jpg>)

![image](<Images/04_UL/image_015.jpg>)

![image](<Images/04_UL/image_016.jpg>)

![image](<Images/04_UL/image_017.jpg>)

<a id="section-23"></a>

**PCA applied to time series Financial data (1/2)**

## PCA 应用于时间序列：金融数据（1/2）

Paper by Avellenada and Lee (2008)

Avellaneda 与 Lee（2008）的论文。

![image](<Images/04_UL/image_018.jpg>)

Figure 1: Eigenvalues of the correlation matrix of market returns computed on May 1 2007 estimated using a 1-year window (measured as percentage of explained variance)

图 1：使用一年窗口估计、于 2007 年 5 月 1 日计算的市场收益率相关矩阵的特征值，以解释方差百分比表示。

Paper by Avellenada and Lee (2008)

Avellaneda 与 Lee（2008）的论文。

![image](<Images/04_UL/image_019.jpg>)

Figure 4: First eigenvector sorted by coefficient size. The x-axis shows the ETF corresponding to the industry sector of each stock

图 4：按系数大小排序的第一特征向量。横轴给出与各股票所属行业对应的 ETF。

<a id="low-rank"></a>

<a id="section-24"></a>

**A diferent view on PCA**

## 从另一角度看 PCA

- Denote by $X$ the data matrix of size $d \times n$ (assume that the points are centered) and by $\begin{array} { r } { \| M \| _ { F } ^ { 2 } = \sum _ { i , j } M _ { i j } ^ { 2 } } \end{array}$ the square of the Frobenius norm of the matrix $M = ( \bar { M } _ { i j } ) _ { i j }$

  用 $X$ 表示大小为 $d \times n$ 的数据矩阵（假设数据点已经中心化），用 $\begin{array} { r } { \| M \| _ { F } ^ { 2 } = \sum _ { i , j } M _ { i j } ^ { 2 } } \end{array}$ 表示矩阵 $M = ( \bar { M } _ { i j } ) _ { i j }$ 的 Frobenius 范数的平方。
- Solve the minimization problem:

  求解最小化问题：

$$
\min _ {P, Z} \| X - P Z \| _ {F} ^ {2} \text{满足} P ^ {T} P = I _ {r}
$$

where $P$ is the projection matrix of size $d \times r$ (the matrix whose columns are the first r eigenvectors), and $Z$ is $r \times n$ matrix of the projected points in the r-dimensional subspace. We also have the orthogonality constraint $P ^ { T } P = I _ { r }$ (eigenvectors are orthogonal)

其中 $P$ 是大小为 $d \times r$ 的投影矩阵，其列为前 r 个特征向量；$Z$ 是大小为 $r \times n$ 的矩阵，记录投影到 r 维子空间后的数据点。同时有正交约束 $P ^ { T } P = I _ { r }$，因为特征向量彼此正交。

<a id="section-25"></a>

**A low-rank formulation of PCA**

## PCA 的低秩表述

- An alternative formulation to the previous optimization problem, by setting: $A = P Z$ , is:

  令 $A = P Z$，前述优化问题可改写为：

$$
\min _ {A} \| X - A \| _ {F} ^ {2} \text{满足} \operatorname{rank} (A) = r
$$

- Theoretical result (Vidal, Ma, Sastry (2016)): an optima solution to this problem is given by:

  理论结果（Vidal、Ma、Sastry，2016）：该问题的一个最优解为：

$$
A = U _ {r} \Sigma_ {r} V _ {r}
$$

> **译注：** 按下文的矩阵维度，原式漏了转置，应为 $A=U_r\Sigma_rV_r^T$。最佳低秩逼近通常写成 $\operatorname{rank}(A)\le r$；若要求严格等于 r，还需注意原矩阵秩不足 r 的情况。

where $U _ { r }$ and $V _ { r }$ have orthogonal columns of size $d \times r$ and $n \times r$ respectively, $\textstyle \sum _ { r }$ diagonal square matrix of size $r \times r$ The matrices $U _ { r } , \ \Sigma _ { r } , \ V _ { r }$ correspond to the reduced singular value decomposition (SVD) of matrix X.

其中 $U _ { r }$ 和 $V _ { r }$ 的列正交，大小分别为 $d \times r$ 和 $n \times r$；$\textstyle \sum _ { r }$ 是大小为 $r \times r$ 的对角方阵。矩阵 $U _ { r } , \ \Sigma _ { r } , \ V _ { r }$ 对应矩阵 X 的约化奇异值分解（SVD）。

<a id="section-26"></a>

**Some linear algebra background: SVD decomposition**

## 线性代数背景：奇异值分解

A generalization of eigenvalues and eigenvectors.

特征值与特征向量的推广。

- Definition: σ is a singular value of a rectangular $d \times n$ matrix X if there exist unit two vectors $u \in \mathbb { R } ^ { d }$ and $v \in \mathbb { R } ^ { n }$ such that

  定义：如果存在两个单位向量 $u \in \mathbb { R } ^ { d }$ 和 $v \in \mathbb { R } ^ { n }$，使得下式成立，则 σ 是大小为 $d \times n$ 的矩形矩阵 X 的一个奇异值：

$$
X ^ {T} u = \sigma v \text{且} X v = \sigma u
$$

The vectors u and v are called singular vectors.

向量 u 和 v 称为奇异向量。

- Theorem: For any rectangular matrix, there exist U and V orthogonal matrices of size $d \times d$ and $n \times n$ respectively and a diagonal matrix $\boldsymbol { \Sigma }$ of size $d \times n$ such that:

  定理：对任意矩形矩阵，存在大小分别为 $d \times d$ 和 $n \times n$ 的正交矩阵 U、V，以及大小为 $d \times n$ 的对角矩阵 $\boldsymbol { \Sigma }$，使得：

$$
X = U \Sigma V ^ {T}
$$

- PCA is sensitive to outliers; empirical covariance matrix converges to real covariance slowly wrt sample size...

  PCA 对异常值敏感；经验协方差矩阵随样本量增加而向真实协方差矩阵收敛的速度较慢……
- What if natural components are not Gaussian? what if they are not orthogonal but independent (check more than just their correlation)? ...

  如果自然成分不是高斯的，会怎样？如果它们并非正交，而是独立的呢（不仅检查相关性）？……
- What about interpretation? Maybe we need nonnegativity of matrix Z (the new data representation) → Nonnegative Matrix Factorization

  可解释性呢？也许需要矩阵 Z（新的数据表示）非负 → 非负矩阵分解。

<a id="reading-pca-svd-eckart-young"></a>

**Complément — why maximizing projected variance equals minimizing reconstruction error, SVD, and the Eckart–Young–Mirsky theorem**

**补充——为什么“最大化投影方差”等价于“最小化重构误差”、SVD 与 Eckart–Young–Mirsky 定理**

Sections 17–18 and Sections 24–26 present three seemingly different formulations of Principal Component Analysis (PCA) for a centered data matrix $X = [x_1, \dots, x_n] \in \mathbb{R}^{d\times n}$ (where each column $x_i \in \mathbb{R}^d$ is a centered observation, $\frac{1}{n}\sum_{i=1}^n x_i = 0$, and the empirical covariance matrix is $\hat{\Sigma} = \frac{1}{n} X X^T \in \mathbb{R}^{d\times d}$):

第 17–18 节与第 24–26 节针对中心化后的数据矩阵 $X = [x_1, \dots, x_n] \in \mathbb{R}^{d\times n}$（每列 $x_i \in \mathbb{R}^d$ 为一个中心化样本，满足 $\frac{1}{n}\sum_{i=1}^n x_i = 0$，样本协方差矩阵为 $\hat{\Sigma} = \frac{1}{n} X X^T \in \mathbb{R}^{d\times d}$），给出了主成分分析（PCA）的三种表述：

1. **Maximum variance view (§17–18) 最大投影方差视角 :** Find $r$ orthonormal directions $P = [u_1, \dots, u_r] \in \mathbb{R}^{d\times r}$ ($P^T P = I_r$) that maximize the total variance of the projected points $z_i = P^T x_i$:
   寻找 $r$ 个标准正交方向 $P = [u_1, \dots, u_r] \in \mathbb{R}^{d\times r}$（满足 $P^T P = I_r$），使投影坐标 $z_i = P^T x_i$ 的总方差最大：

$$
\max_{P^T P = I_r} \frac{1}{n}\sum_{i=1}^n \|P^T x_i\|_2^2 = \max_{P^T P = I_r} \operatorname{Tr}\big(P^T \hat{\Sigma} P\big).
$$

2. **Minimum subspace reconstruction error view (§24) 最小子空间重构误差视角 :** Find an orthonormal basis $P \in \mathbb{R}^{d\times r}$ ($P^T P = I_r$) and low-dimensional coordinates $Z = [z_1, \dots, z_n] \in \mathbb{R}^{r\times n}$ that minimize the squared Frobenius reconstruction error $\|X - P Z\|_F^2 = \sum_{i=1}^n \|x_i - P z_i\|_2^2$.
   寻找标准正交基 $P \in \mathbb{R}^{d\times r}$（$P^T P = I_r$）及降维坐标矩阵 $Z = [z_1, \dots, z_n] \in \mathbb{R}^{r\times n}$，使重构误差平方和 $\|X - P Z\|_F^2 = \sum_{i=1}^n \|x_i - P z_i\|_2^2$ 最小。

3. **Low-rank matrix approximation view (§25–26) 最佳低秩矩阵逼近视角 :** Find a matrix $A \in \mathbb{R}^{d\times n}$ of rank at most $r$ that minimizes $\|X - A\|_F^2$.
   在所有秩不超过 $r$ 的矩阵 $A \in \mathbb{R}^{d\times n}$ 中，寻找使 $\|X - A\|_F^2$ 最小的矩阵。

**Derivation: proof of the equivalence of the three views and the Eckart–Young–Mirsky theorem via SVD**

**推导：三种视角等价性的勾股定理证明，以及基于 SVD 的 Eckart–Young–Mirsky 定理**

1. **Equivalence of Views 1 and 2 via the Pythagorean theorem 由勾股定理证明视角 1 与视角 2 等价 :**
   Fix any matrix $P \in \mathbb{R}^{d\times r}$ with orthonormal columns ($P^T P = I_r$). For each sample $x_i$, the vector $P z_i$ lies in the $r$-dimensional subspace $\operatorname{Span}(P)$, and the closest point to $x_i$ in that subspace is its orthogonal projection $P(P^T x_i)$, meaning the optimal coordinate vector is $z_i^* = P^T x_i$ (or in matrix form, $Z^* = P^T X$).
   Since the orthogonal projection $P P^T x_i$ and the residual $(I_d - P P^T)x_i$ are orthogonal, the Pythagorean theorem gives:

   固定任意列标准正交矩阵 $P \in \mathbb{R}^{d\times r}$（$P^T P = I_r$）。对每个样本 $x_i$，重构向量 $P z_i$ 位于 $P$ 张成的 $r$ 维子空间中；由正交投影性质，子空间中离 $x_i$ 最近的点必为 $P(P^T x_i)$，即最优低维坐标为 $z_i^* = P^T x_i$（矩阵形式 $Z^* = P^T X$）。
   由于投影分量 $P P^T x_i$ 与残差分量 $(I_d - P P^T)x_i$ 正交，且 $\|P P^T x_i\|_2^2 = x_i^T P(P^T P)P^T x_i = \|P^T x_i\|_2^2$，对所有样本应用勾股定理可得：

$$
\underbrace{\|X - P P^T X\|_F^2}_{\text{Reconstruction error / 重构误差平方和}}
= \sum_{i=1}^n \|x_i - P P^T x_i\|_2^2
= \underbrace{\sum_{i=1}^n \|x_i\|_2^2}_{\|X\|_F^2 \text{ (constant / 常数)}} - \underbrace{\sum_{i=1}^n \|P^T x_i\|_2^2}_{n \operatorname{Tr}(P^T \hat{\Sigma} P) \text{ (projected variance / 投影方差)}}.
$$

   Because total data energy $\|X\|_F^2$ does not depend on $P$, **minimizing reconstruction error $\|X - P P^T X\|_F^2$ is identical to maximizing projected variance $\operatorname{Tr}(P^T \hat{\Sigma} P)$**!

   因为原始数据的总能量 $\|X\|_F^2$ 与 $P$ 无关，**最小化重构误差 $\|X - P P^T X\|_F^2$ 在数学上恒等于最大化投影方差 $\operatorname{Tr}(P^T \hat{\Sigma} P)$**！

2. **Connection between Eigen-decomposition of $\hat{\Sigma}$ and SVD of $X$ (§18 & §26) 协方差特征分解与数据矩阵 SVD 的联系 :**
   Let $X = U \Sigma V^T = \sum_{k=1}^{\min(d,n)} \sigma_k u_k v_k^T$ be the Singular Value Decomposition of $X$ (§26), where $U = [u_1,\dots,u_d] \in \mathbb{R}^{d\times d}$ and $V = [v_1,\dots,v_n] \in \mathbb{R}^{n\times n}$ are orthogonal matrices and $\sigma_1 \ge \sigma_2 \ge \dots \ge 0$ are the singular values. Then:

   设 $X = U \Sigma V^T = \sum_{k=1}^{\min(d,n)} \sigma_k u_k v_k^T$ 为数据矩阵 $X$ 的奇异值分解（§26），其中 $U = [u_1,\dots,u_d] \in \mathbb{R}^{d\times d}$ 与 $V = [v_1,\dots,v_n] \in \mathbb{R}^{n\times n}$ 为正交矩阵，$\sigma_1 \ge \sigma_2 \ge \dots \ge 0$ 为奇异值。于是样本协方差矩阵可写为：

$$
\hat{\Sigma} = \frac{1}{n} X X^T = \frac{1}{n} U \Sigma V^T V \Sigma^T U^T = U \operatorname{diag}\!\left(\frac{\sigma_1^2}{n}, \dots, \frac{\sigma_d^2}{n}\right) U^T.
$$

   Thus, the **left singular vectors $u_k$ of $X$ are the eigenvectors (principal axes) of $\hat{\Sigma}$**, and the **eigenvalues of $\hat{\Sigma}$ are $\lambda_k = \sigma_k^2 / n$**!

   由此可见：**$X$ 的左奇异向量 $u_k$ 就是样本协方差矩阵 $\hat{\Sigma}$ 的特征向量（主成分方向）**，而 **$\hat{\Sigma}$ 的特征值恰好是 $\lambda_k = \sigma_k^2 / n$**！

3. **Eckart–Young–Mirsky Theorem (§25) Eckart–Young–Mirsky 低秩逼近定理 :**
   Any matrix $A \in \mathbb{R}^{d\times n}$ with $\operatorname{rank}(A) \le r$ has column space contained in some $r$-dimensional subspace, so it can be written as $A = P Z$ with $P^T P = I_r$. By Ky Fan's trace inequality, $\operatorname{Tr}(P^T X X^T P) \le \sum_{k=1}^r \sigma_k^2$. Equality is attained whenever the columns of $P$ span a principal subspace associated with the $r$ largest singular values—for example, $P = U_r Q$ for any orthogonal matrix $Q \in O(r)$, where $U_r = [u_1, \dots, u_r]$ and $Z^* = P^T X = Q^T \Sigma_r V_r^T$ (which leaves the projection $P P^T = U_r U_r^T$ invariant; this optimal $r$-dimensional subspace and the resulting rank-$r$ approximation $A_r$ are **unique if and only if $\sigma_r > \sigma_{r+1}$**). Therefore, the truncated SVD

   任意满足 $\operatorname{rank}(A) \le r$ 的矩阵 $A \in \mathbb{R}^{d\times n}$ 都可分解为 $A = P Z$（其中 $P \in \mathbb{R}^{d\times r}$ 列标准正交）。由 Ky Fan 迹不等式，投影能量满足 $\operatorname{Tr}(P^T X X^T P) \le \sum_{k=1}^r \sigma_k^2$。当 $P$ 的各列张成前 $r$ 个最大奇异值对应的主子空间——即取 $P = U_r Q$（其中 $U_r = [u_1, \dots, u_r]$，$Q \in O(r)$ 为任意 $r\times r$ 正交矩阵，相应坐标为 $Z^* = P^T X = Q^T \Sigma_r V_r^T$，正交投影阵 $P P^T = U_r U_r^T$ 保持不变）时取等号；此外，该最优 $r$ 维子空间及最佳秩 $r$ 逼近矩阵 $A_r$ **唯一当且仅当存在严格谱隙 $\sigma_r > \sigma_{r+1}$**（若 $\sigma_r = \sigma_{r+1}$，则与 $\sigma_r$ 关联的特征子空间内可作不同选择）。因此，截断 SVD（即前 $r$ 个秩 1 矩阵之和）

$$
A_r = U_r \Sigma_r V_r^T = \sum_{k=1}^r \sigma_k u_k v_k^T
$$

   is a global minimizer of $\|X - A\|_F^2$ over $\{\operatorname{rank}(A) \le r\}$, and the minimum reconstruction error is the sum of the discarded squared singular values:

   是低秩逼近问题 $\min_{\operatorname{rank}(A)\le r}\|X - A\|_F^2$ 的全局最优解，且最小重构误差平方和恰好等于被舍弃的后 $\min(d,n)-r$ 个奇异值平方和：

$$
\min_{\operatorname{rank}(A) \le r} \|X - A\|_F^2 = \|X - A_r\|_F^2 = \sum_{k=r+1}^{\min(d,n)} \sigma_k^2.
$$

   Consequently, the **proportion of variance explained** by the first $r$ principal components (plotted in the financial return spectrum of Section 23) is simply:

   相应地，前 $r$ 个主成分的**累计解释方差比例（proportion of explained variance，即第 23 节金融收益率特征值谱图的纵轴）**为：

$$
\text{Explained Variance Ratio}(r) = \frac{\sum_{k=1}^r \lambda_k}{\sum_{k=1}^d \lambda_k} = \frac{\sum_{k=1}^r \sigma_k^2}{\sum_{k=1}^{\min(d,n)} \sigma_k^2} = 1 - \frac{\|X - A_r\|_F^2}{\|X\|_F^2}.
$$

**Practical precautions when using PCA (§18–26)**

**应用 PCA 时的三个关键注意事项（§18–26）**

- **Centering is essential 必须先中心化数据 :** If the columns of $X$ are not centered ($\bar{x} \neq 0$), the first singular vector of $X$ mainly points toward the mean vector $\bar{x}$ rather than the direction of highest variance around the mean.
- **必须先中心化：** 若未减去样本均值（$\bar{x} \neq 0$），直接对原始矩阵做 SVD 时第一奇异向量往往指向均值向量 $\bar{x}$ 的方向，而不是围绕均值的最大波动方向。
- **Covariance PCA vs. Correlation PCA (units and scaling) 协方差矩阵 PCA 与相关矩阵 PCA（量纲敏感性） :** PCA is not scale-invariant! If one variable is measured in millimeters (variance $10^6$) and another in meters (variance $1$), covariance PCA will almost entirely align with the first variable. Standardizing each feature to unit variance before PCA is equivalent to computing the eigenvectors of the **correlation matrix** (as done for the stock return correlations in Section 23).
- **协方差 PCA 与相关矩阵 PCA（对单位缩放敏感）：** PCA 对特征的量纲缩放不具有不变性！如果一个变量以毫米为单位（方差 $10^6$），另一个以米为单位（方差 $1$），协方差矩阵的第一主成分几乎会被第一个变量垄断。在量纲不同或波动幅度差异极大的场景下，先将每个变量标准化为单位方差再做 PCA，等价于对**相关系数矩阵（correlation matrix）**做特征分解（如第 23 节股票收益率分析）。
- **Sensitivity to outliers 对异常值敏感 :** Because PCA minimizes *squared* residuals $\|X - A\|_F^2$, a single corrupted entry or extreme outlier can dramatically tilt the principal subspace—motivating Robust PCA in Section 28.
- **对异常值高度敏感：** 由于 PCA 最小化的是**平方**重构误差 $\|X - A\|_F^2$，少量极端异常值或损坏像素就会剧烈拉偏主子空间——这正是第 28 节引入稳健 PCA（Robust PCA）的直接原因。

<a id="section-27"></a>

**Nonnegative Matrix Factorization**

## 非负矩阵分解

![image](<Images/04_UL/image_020.jpg>)

D.D. Lee and H. S.Seung, ”Learning the parts of objects by non-negative matrix factorization”, Nature 401 (6755), pp. 788–791, 1999

D. D. Lee 与 H. S. Seung，Learning the parts of objects by non-negative matrix factorization（通过非负矩阵分解学习对象的组成部分），Nature 401 (6755)，第 788–791 页，1999。

<a id="section-28"></a>

**PCA Generalisations: Example Machine Learning Formulation**

## PCA 的推广：机器学习问题表述示例

- Example: Robust PCA by Cand`es, Li, Ma, Wright (2011)

  例子：Candès、Li、Ma、Wright（2011）的稳健 PCA。
- Motivation: assume a decomposition of the data matrix X = L + S where L is low rank and S is sparse.

  动机：假设数据矩阵可以分解为 X = L + S，其中 L 为低秩矩阵，S 为稀疏矩阵。

Principal Component Pursuit: the nuclear norm (also called Trace norm) $\| \cdot \| _ { * }$ defined as the sum of singular values; note with $\| \cdot \| _ { 1 }$ the $\ell _ { 1 }$ matrix norm (sum of the absolute values of all the entries of the matrix). We search for matrices L and S:

主成分追踪：核范数（也称迹范数）$\| \cdot \| _ { * }$ 定义为奇异值之和；用 $\| \cdot \| _ { 1 }$ 表示矩阵的 $\ell _ { 1 }$ 范数，即所有元素绝对值之和。寻找矩阵 L 和 S：

$$
\min _ {L, S} \| L \| _ {*} + \lambda \| S \| _ {1} \text{满足} L + S = X
$$

- Main theoretical result: under some assumptions the exact solution may be recovered by this procedure

  主要理论结果：在某些假设下，这个过程可以恢复精确解。
- Sparse PCA

  稀疏 PCA。
- Nonlinear PCA, Kernel PCA

  非线性 PCA、核 PCA。

Reference: book by Vidal, Ma, Sastry. Generalized Principal Component Analysis. Springer (2016)

参考书：Vidal、Ma、Sastry，Generalized Principal Component Analysis（广义主成分分析），Springer，2016。

<a id="reading-nmf-and-robust-pca"></a>

**Complément — Nonnegative Matrix Factorization (NMF) vs. PCA, and Robust PCA (Principal Component Pursuit)**

**补充——非负矩阵分解（NMF）的局部可加性，以及稳健主成分分析（Robust PCA）的低秩—稀疏分离条件**

1. **Why Nonnegative Matrix Factorization (NMF, §27) encourages additive representations 为什么非负矩阵分解（NMF，§27）产生纯可加表示**
   In standard PCA ($X \approx P Z$), both the basis vectors $P$ and the coordinates $Z$ contain positive and negative numbers. A face image in PCA is reconstructed by adding and subtracting holistic "eigenfaces" that cancel each other out across pixels. By contrast, when the data matrix $X \in \mathbb{R}_+^{d\times n}$ is naturally nonnegative (pixel intensities, word counts, audio spectrograms, user listening counts), **NMF** (Lee & Seung, 1999) seeks two nonnegative matrices $W \in \mathbb{R}_+^{d\times r}$ and $H \in \mathbb{R}_+^{r\times n}$ such that $X \approx W H$. Because negative cancellations are forbidden ($W_{ik} \ge 0, H_{kj} \ge 0$), each column of $X$ must be built by **purely additive combinations** of the columns of $W$. In the facial image experiment of Section 27, Lee & Seung (1999) observed that the columns of $W$ resemble localized facial parts (eyes, noses, mouths, eyebrows). Note, however, that **nonnegativity alone only guarantees additivity, not sparsity or spatial localization**: dense nonnegative factors can also achieve minimal reconstruction error (and NMF is generally non-unique), so when guaranteed sparse or localized factors are needed, explicit sparsity constraints (such as $\ell_1$ penalties or Hoyer's 2004 sparse NMF) must be added.

   在标准 PCA（$X \approx P Z$）中，基矩阵 $P$ 和编码矩阵 $Z$ 的元素均可正可负：重构一张人脸图像时，PCA 通过全局“特征脸（eigenfaces）”之间的正负加减相互抵消来拟合像素值，单个主成分在空间上遍布整张脸。相反，当数据矩阵 $X \in \mathbb{R}_+^{d\times n}$ 天然非负（如图像像素灰度、文本词频、音频频谱或用户播放次数）时，**非负矩阵分解（NMF，Lee & Seung, 1999）**要求基矩阵与系数矩阵同时满足逐元素非负：$X \approx W H$（$W \in \mathbb{R}_+^{d\times r}, H \in \mathbb{R}_+^{r\times n}$）。由于**不允许正负抵消**，每个样本列只能由基向量的**纯加法叠加**生成；在第 27 节的人脸图像实验中，Lee 与 Seung（1999）观察到 $W$ 的各列呈现出类似局部器官（眼睛、鼻子、嘴唇与眉毛）的形态。但需注意：**非负约束本身只保证“纯可加性”，并不自动保证稀疏性或空间局部性**——稠密的非负因子同样可能达到最优重构误差（且标准 NMF 解通常不唯一）；若需严格保证或控制因子的稀疏与局部化程度，还需额外施加显式稀疏约束（如 $\ell_1$ 惩罚或 Hoyer, 2004 的稀疏约束 NMF）。

2. **Robust PCA (`X = L + S`, §28): separating a low-rank background from sparse outliers 稳健 PCA（`X = L + S`，§28）：分离低秩背景与稀疏大幅异常值**
   Classical PCA fails when even a few entries of $X$ are grossly corrupted, because squared Frobenius loss $\|X - L\|_F^2$ assumes small Gaussian noise on all entries. **Robust PCA** models $X = L_0 + S_0$, where $L_0$ has low rank (not small entries!) and $S_0$ is sparse (most entries are zero, but nonzero entries can be arbitrarily large!). For example, in a surveillance video where each column of $X$ is a flattened video frame, the static background changes very little across frames (**low-rank matrix $L_0$**), while moving pedestrians or cars occupy only a small fraction of pixels in each frame (**sparse matrix $S_0$**).

   当数据矩阵 $X$ 中混入少量幅度极大的损坏点（outliers）时，经典 PCA 的平方损失 $\|X - L\|_F^2$ 会为了迁就这几个极大残差而使整个低秩子空间严重偏离。**稳健 PCA（Robust PCA，Candès, Li, Ma, Wright, 2011）**将数据建模为 $X = L_0 + S_0$，其中 $L_0$ 是**低秩矩阵**，$S_0$ 是**稀疏矩阵**（大部分元素严格为 $0$，但非零元素可以任意大！）。典型应用是监控视频前景—背景分离：将每一帧图像展平为 $X$ 的一列，则几乎不变的背景构成高度相关的**低秩矩阵 $L_0$**，而画面中走动的行人或车辆只占少数像素，构成**稀疏矩阵 $S_0$**。

   Replacing $\operatorname{rank}(L)$ by the nuclear norm $\|L\|_*$ and $\|S\|_0$ by the entrywise $\ell_1$ norm $\|S\|_1 = \sum_{i,j}|S_{ij}|$ yields the convex **Principal Component Pursuit (PCP)** program of Section 28. Intuitively, exact separation is impossible if $L_0$ is also sparse (e.g., a matrix with a single nonzero entry is both rank-1 and 1-sparse) or if $S_0$ is also low-rank (e.g., an entire corrupted column). Formally, **Candès, Li, Ma & Wright (2011, Theorem 1.1)** proved that PCP with universal parameter $\lambda = 1/\sqrt{\max(d,n)}$ recovers **both $L_0$ and $S_0$ exactly** with high probability under three quantitative assumptions:
   1. **Incoherence of $L_0$:** the singular vectors of $L_0 = U\Sigma V^T$ are delocalized ($\max_i \|U^T e_i\|_2^2 \le \frac{\mu r}{d}$, $\max_j \|V^T e_j\|_2^2 \le \frac{\mu r}{n}$, and $\|U V^T\|_\infty \le \frac{\sqrt{\mu r}}{\sqrt{dn}}$ for an incoherence parameter $\mu \ge 1$);
   2. **Uniform random support of $S_0$:** the support set of $S_0$ of cardinality $m = \|S_0\|_0$ is distributed uniformly at random among all subsets of size $m$ (whereas magnitudes and signs of nonzero entries of $S_0$ can be arbitrary);
   3. **Quantitative rank and sparsity bounds:** both the rank $r = \operatorname{rank}(L_0)$ and the number of corrupted entries $m = \|S_0\|_0$ are sufficiently small, namely $r \le \rho_r \frac{\min(d,n)}{\mu (\log\max(d,n))^2}$ and $m \le \rho_s d n$ for positive numerical constants $\rho_r, \rho_s$.

   将非凸的 $\operatorname{rank}(L)$ 松弛为核范数 $\|L\|_*$，将非零元素计数 $\|S\|_0$ 松弛为逐元素绝对值之和 $\|S\|_1 = \sum_{i,j}|S_{ij}|$，就得到第 28 节的凸优化问题**主成分追踪（Principal Component Pursuit, PCP）**。从直觉上看，若 $L_0$ 同时也很稀疏（如仅含单个非零元的矩阵既是秩 1 又是 1-稀疏），或 $S_0$ 同时也是低秩的（如整行、整列被污染），则两者在代数上无法唯一区分。严格而言，**Candès、Li、Ma 与 Wright（2011，定理 1.1）**证明了当满足以下三条定量假设时，取通用参数 $\lambda = 1/\sqrt{\max(d,n)}$ 的 PCP 凸规划能够以高概率**精确恢复出真实的 $L_0$ 和 $S_0$**：
   1. **$L_0$ 的非相干性（Incoherence）：** $L_0 = U\Sigma V^T$ 的左右奇异向量不集中在少数坐标上，满足定量界 $\max_i \|U^T e_i\|_2^2 \le \frac{\mu r}{d}$、$\max_j \|V^T e_j\|_2^2 \le \frac{\mu r}{n}$ 及联合界 $\|U V^T\|_\infty \le \frac{\sqrt{\mu r}}{\sqrt{dn}}$；
   2. **$S_0$ 支撑集的均匀随机分布：** 稀疏矩阵 $S_0$ 的非零位置集合（基数为 $m = \|S_0\|_0$）在所有大小为 $m$ 的位置子集中均匀随机选取（而非零元素的幅值与正负号可任意大）；
   3. **秩与污染比例的定量上界：** $L_0$ 的秩与 $S_0$ 的非零个数同时受定量上界约束：$r \le \rho_r \frac{\min(d,n)}{\mu (\log\max(d,n))^2}$ 且 $m \le \rho_s d n$（其中 $\rho_r, \rho_s > 0$ 为绝对常数）。

<a id="completion"></a>

<a id="section-29"></a>

C. Applications: matrix completion, compressed sensing

## C. 应用：矩阵补全与压缩感知

Matrix completion: Recommender Systems Application

### 矩阵补全：推荐系统应用

![image](<Images/04_UL/image_021.jpg>)

- Original optimization formulation (kind of ”Ivanov Regularization” with no error on the available matrix entries - our data)

  原始优化表述：一种“Ivanov 正则化”，要求在可用的矩阵元素（即数据）上没有误差。

$$
\min _ {X} \{\operatorname{rank} (X) \} \text{满足} X _ {i j} = M _ {i j}    , \forall (i, j) \in \Omega
$$

where $\Omega = \{ ( i , j ) : M _ { i j }$ the available data}.

其中 $\Omega=\{(i,j):M_{ij}\text{ 为可用数据}\}$。

- Key Challenge: Non-convex problem, hard to solve

  关键挑战：非凸问题，难以求解。

Convex Relaxation

### 凸松弛

- Recall the nuclear norm of X is $\| X \| _ { * } = \sum _ { i = 1 } \sigma _ { i }$ , where $\sigma _ { i }$ are the singular values of X (recall the SVD of X is $X = U \Sigma V ^ { T } )$

  回顾：X 的核范数为 $\| X \| _ { * } = \sum _ { i = 1 } \sigma _ { i }$，其中 $\sigma _ { i }$ 是 X 的奇异值；回顾 X 的奇异值分解为 $X = U \Sigma V ^ { T } )$。
- Convex formulation of the matrix completion problem:

  矩阵补全问题的凸表述：

$$
\min _ {X} \| X \| _ {*} \text{满足} X _ {i j} = M _ {i j}, \forall (i, j) \in \Omega
$$

where $\Omega = \{ ( i , j ) : M _ { i j }$ the available data}.

其中 $\Omega=\{(i,j):M_{ij}\text{ 为可用数据}\}$。

- Regularization formulation: Nuclear norm penalty

  正则化表述：核范数惩罚。

$$
\min _ {X} \left\{\frac {1}{2} \sum_ {i j \in \Omega} (X _ {i j} - M _ {i j}) ^ {2} + \lambda \| X \| _ {*} \right\}
$$

- Simplified problem (no mask Ω):

  简化问题（没有掩码 Ω）：

$$
\min _ {X} \left\{\frac {1}{2} \| X - M \| ^ {2} + \lambda \| X \| _ {*} \right\}
$$

- The solution is closed form and given by:

  解有闭式表达，给出如下：

$$
\operatorname{shrink} (X, \lambda) = U \Sigma (\lambda) V ^ {T}
$$

where $\Sigma ( \lambda ) = \mathrm { d i a g } ( ( \sigma _ { i } - \lambda ) _ { + } )$

其中 $\Sigma ( \lambda ) = \mathrm { d i a g } ( ( \sigma _ { i } - \lambda ) _ { + } )$。

- Note: the solution uses only the singular values that are larger than λ...

  注意：该解只使用大于 λ 的奇异值……
- Need a trick to deal with the $\Omega$

  需要一种技巧来处理 $\Omega$。
- Use an auxiliary matrix Y which is complete

  使用一个完整的辅助矩阵 Y。
- Define $\Pi _ { \Omega } ( X )$ the matrix with coeficients $X _ { i j }$ if $( i , j ) \in \Omega$ and zero if $( i , j ) \notin \Omega$

  定义矩阵 $\Pi _ { \Omega } ( X )$：当 $( i , j ) \in \Omega$ 时，其元素为 $X _ { i j }$；当 $( i , j ) \notin \Omega$ 时，其元素为零。
- Iterative algorithm $\left( \mathsf { c a l l e d } ^ { \prime \prime } \mathsf { S V T } ^ { \prime \prime } \right)$

  迭代算法 $\left( \mathsf { c a l l e d } ^ { \prime \prime } \mathsf { S V T } ^ { \prime \prime } \right)$。
1. 1 Set $\lambda > 0$ and sequence of step sizes $( \delta _ { k } ) _ { k \geq 1 }$

   设定 $\lambda > 0$ 和步长序列 $( \delta _ { k } ) _ { k \geq 1 }$。
2. 2 Start with $Y _ { 0 } = 0$ matrix of size $n \times m$

   从大小为 $n \times m$ 的矩阵 $Y _ { 0 } = 0$ 开始。
3. 3 At each step $k ,$ compute:

   在每一步 $k ,$，计算：

$$
\left\{ \begin{array}{l l} X _ {k} & = \text { shrink } (Y _ {k - 1}, \lambda) \\ Y _ {k} & = Y _ {k - 1} + \delta_ {k} \Pi_ {\Omega} (M - X _ {k}) \end{array} \right.
$$

<a id="reading-matrix-completion-svt"></a>

**Complément — why low-rank matrix completion works, nuclear-norm proximal operator, and Singular Value Thresholding (SVT)**

**补充——低秩矩阵补全的可恢复原理、核范数近端算子与奇异值阈值算法（SVT）推导**

In the Netflix problem (§5–6 & §29), only a tiny fraction of entries $(i,j) \in \Omega$ of the user–movie rating matrix $M \in \mathbb{R}^{n_1\times n_2}$ is observed. Without structural assumptions, the missing entries $(i,j) \notin \Omega$ could take any values whatsoever. Assuming $\operatorname{rank}(X) = r \ll \min(n_1, n_2)$ means that each user $i$ is described by $r$ preference factors $u_i \in \mathbb{R}^r$ and each movie $j$ by $r$ attribute factors $v_j \in \mathbb{R}^r$ such that $X_{ij} = u_i^T v_j$: instead of $n_1 n_2$ independent degrees of freedom, the matrix has only $r(n_1 + n_2 - r)$ degrees of freedom!

在 Netflix 推荐问题（§5–6、§29）中，用户—电影评分矩阵 $M \in \mathbb{R}^{n_1\times n_2}$ 只有极少数位置 $(i,j) \in \Omega$ 有观测值。若不对矩阵结构作假设，未观测位置 $(i,j) \notin \Omega$ 可以填任意数值。假设目标矩阵满足**低秩结构** $\operatorname{rank}(X) = r \ll \min(n_1, n_2)$，意味着每个用户 $i$ 由 $r$ 个潜在偏好因子 $u_i \in \mathbb{R}^r$ 描述、每部电影 $j$ 由 $r$ 个属性因子 $v_j \in \mathbb{R}^r$ 描述，使得评分 $X_{ij} = u_i^T v_j$：整张矩阵的自由度从 $n_1 n_2$ 骤降至 $r(n_1 + n_2 - r)$，从而使利用少量观测恢复整张矩阵成为可能！

**Derivation: why singular value soft-thresholding $\operatorname{shrink}(Y,\lambda)$ solves the nuclear-norm proximal problem (§29)**

**推导：为什么奇异值软阈值算子 $\operatorname{shrink}(Y,\lambda)$ 是核范数近端问题的闭式解（§29）**

Consider the simplified full-matrix denoising problem in Section 29 (which is the **proximal operator of the nuclear norm** $\lambda\|\cdot\|_*$ evaluated at a matrix $M$ with SVD $M = U \Sigma V^T$, where $\Sigma = \operatorname{diag}(\sigma_1, \dots, \sigma_r)$):

考察第 29 节的简化无掩码问题（这正是**核范数 $\lambda\|\cdot\|_*$ 在矩阵 $M$ 处的近端算子 $\operatorname{prox}_{\lambda\|\cdot\|_*}(M)$**；注意原页第 763 行把自变量写成了 $X$，实际是对给定矩阵 $M = U \Sigma V^T$ 的奇异值做收缩）：

$$
\widehat{X} = \underset{X}{\arg\min} \left\{ \frac{1}{2}\|X - M\|_F^2 + \lambda \|X\|_* \right\}.
$$

By von Neumann's trace inequality, for any two matrices $X$ and $M$ with singular values $\sigma_1(X) \ge \sigma_2(X) \ge \dots \ge 0$ and $\sigma_1(M) \ge \sigma_2(M) \ge \dots \ge 0$, we have $\langle X, M\rangle_F = \operatorname{Tr}(X^T M) \le \sum_i \sigma_i(X)\sigma_i(M)$, with equality when $X$ and $M$ admit a simultaneous singular value decomposition $M = U \Sigma V^T$ and $X = U \operatorname{diag}(s_1, \dots, s_r) V^T$ with $s_1 \ge \dots \ge s_r \ge 0$. Consequently:

由 von Neumann 迹不等式，对任意矩阵 $X$ 和 $M$（奇异值按降序排列分别为 $\sigma_1(X) \ge \dots \ge 0$ 和 $\sigma_1(M) \ge \dots \ge 0$），有内积上界 $\langle X, M\rangle_F = \operatorname{Tr}(X^T M) \le \sum_i \sigma_i(X)\sigma_i(M)$，因此

$$
\|X - M\|_F^2 = \|X\|_F^2 - 2\langle X, M\rangle_F + \|M\|_F^2 \ge \sum_i \big(\sigma_i(X) - \sigma_i(M)\big)^2,
$$

with equality attained when $X$ takes the form $X = U \operatorname{diag}(s_1, \dots, s_r) V^T$ ($s_i \ge 0$) for the SVD $M = U \Sigma V^T$. Because the objective $\frac{1}{2}\|X - M\|_F^2 + \lambda\|X\|_*$ is **strictly convex** in $X$, its global minimizer $\widehat{X}$ is unique and is found by minimizing over the singular values $s_i \ge 0$:

当对 $M = U \Sigma V^T$ 取 $X = U \operatorname{diag}(s_1, \dots, s_r) V^T$（$s_i \ge 0$）时达到下界。由于目标函数 $\frac{1}{2}\|X - M\|_F^2 + \lambda\|X\|_*$ 关于矩阵 $X$ **严格凸**，其全局极小点 $\widehat{X}$ 必然唯一，且直接由关于各奇异值 $s_i \ge 0$ 的独立标量优化给出：

$$
\min_{s_i \ge 0} \sum_{i} \left\{ \frac{1}{2}(s_i - \sigma_i)^2 + \lambda s_i \right\}
\implies s_i^* = (\sigma_i - \lambda)_+ = \max(0, \sigma_i - \lambda).
$$

Hence the exact closed-form solution is the **Singular Value Thresholding (SVT) operator** (Cai, Candès, & Shen, 2010):

由此直接得到第 29 节的**奇异值软阈值算子（Singular Value Thresholding, SVT，Cai, Candès & Shen, 2010）**闭式解：

$$
\operatorname{shrink}(M, \lambda) = U \operatorname{diag}\big((\sigma_1 - \lambda)_+, \dots, (\sigma_r - \lambda)_+\big) V^T.
$$

Just as 1D soft-thresholding $S_\lambda(z)$ sets small coordinates to zero and shrinks large coordinates by $\lambda$, $\operatorname{shrink}(M,\lambda)$ **sets all singular values $\sigma_i \le \lambda$ to zero**—directly reducing the rank of $X_k$! In the masked SVT algorithm at the bottom of Section 29, $X_k = \operatorname{shrink}(Y_{k-1}, \lambda)$ produces a low-rank candidate, and $Y_k = Y_{k-1} + \delta_k \Pi_\Omega(M - X_k)$ accumulates the prediction residuals on the observed entries $\Omega$ (which is dual gradient ascent / Uzawa's method on $\min_X \frac{1}{2}\|X\|_F^2 + \lambda\|X\|_*$ subject to $\Pi_\Omega(X) = \Pi_\Omega(M)$).

正如一维软阈值算子 $S_\lambda(z)$ 将绝对值小于 $\lambda$ 的坐标置零一样，矩阵奇异值软阈值算子 $\operatorname{shrink}(M,\lambda)$ **将所有小于等于 $\lambda$ 的奇异值直接截断为零**，从而自动降低矩阵 $X_k$ 的秩！在第 29 节末的 SVT 迭代算法中，第一步 $X_k = \operatorname{shrink}(Y_{k-1}, \lambda)$ 通过奇异值软阈值生成低秩矩阵，第二步 $Y_k = Y_{k-1} + \delta_k \Pi_\Omega(M - X_k)$ 则仅在已观测位置 $\Omega$ 上累加残差（本质上是求解 $\min_{\Pi_\Omega(X)=\Pi_\Omega(M)} \frac{1}{2}\|X\|_F^2 + \lambda\|X\|_*$ 的拉格朗日对偶梯度上升／Uzawa 算法）。

<a id="dictionary"></a>

<a id="section-30"></a>

C2. Dictionary learning

## C.2. 字典学习

**Motivations and references**

### 动机与参考资料

- Some features (to represent the data) may be good for compression but not for interpretation (and vice versa); they may also simply fail to ”lead to” sparse representations (e.g., learn functions that use only a few of the features)

  某些用于表示数据的特征可能有利于压缩，但不利于解释，反之亦然；它们也可能根本无法产生稀疏表示，例如无法学到只使用少量特征的函数。
- Can we learn data features (representation) so that the functions we learn (estimate) in that representation (”space”) are also sparse?

  能否学习一种数据特征（表示），使得在这种表示“空间”中学习或估计的函数也是稀疏的？
- Idea is to exploit the fact that similar patterns may be repeated in the data (even if they are not smooth)

  思路：利用数据中相似模式可能重复出现这一事实，即使这些模式不光滑。
- (Can also be used to handle some cases of non-stationarity)

  （也可用于处理某些非平稳情形。）

参考文献：Olshausen 与 Field（1997）；Kreutz-Delgado 等（2003）；Mairal、Elad、Sapiro（2008）；Gribonval 等（2015）。

<a id="section-31"></a>

**Sparse coding Formulation**

## 稀疏编码：问题表述

- Objective: find both A (the ”features”) and Y that yield to the sparse representation of the data X up to some error ε

  目标：同时寻找 A（“特征”）和 Y，使其在允许误差 ε 的范围内给出数据 X 的稀疏表示。
- Formulation:

  表述：

$$
\min _ {A, Y} \left\{\sum_ {i = 1} ^ {n} \| Y _ {i} \| _ {0} \right\} \text{满足} \| X - A Y \| _ {2} \leq \varepsilon
$$

<a id="section-32"></a>

**Sparse coding Towards nonconvex optimization**

## 稀疏编码：走向非凸优化

- Same complexity as $\ell _ { 0 }$ norm minimization problem. In practice, it is solved with an $\ell _ { 1 } { \mathsf { - t y p e } }$ relaxation

  与 $\ell _ { 0 }$ 范数最小化问题具有相同的复杂度。实践中使用 $\ell _ { 1 } { \mathsf { - t y p e } }$ 松弛求解。
- But: for fixed $A ,$ , minimization over Y is convex but the joint optimization wrt both A and Y is not convex

  但是：固定 $A ,$ 时，关于 Y 的最小化是凸的；同时关于 A 和 Y 的联合优化却不是凸的。
- Main strategy for non convex matrix factorization problems: alternating minimization (Douglas-Rachford) or Block coordinate descent

  非凸矩阵分解问题的主要策略：交替最小化（Douglas–Rachford），或分块坐标下降。

> **译注：** 交替最小化、分块坐标下降与 Douglas–Rachford 分裂有不同的算法定义，不能直接视为同一算法。原课件括号中的归类保留，但应作此区分。

- Images (text? multimedia?, etc)

  图像（文本？多媒体？等等）。

![image](<Images/04_UL/image_022.jpg>)

- Representation of consumer products (”meta-attributes”) and utility functions (see also conjoint analysis and Multi-task Learning in Sessions 13-14).

  消费品的表示（“元属性”）与效用函数；另见第 13–14 次课中的联合分析和多任务学习。

Sparsity

稀疏性

<a id="section-33"></a>

C.3. Compressed sensing

## C.3. 压缩感知

**A revolution in signal processing**

### 信号处理中的一场革命

- Classical signal representation relies on first measuring then compressing (the information/data - hence ”finding the rules/laws”)

  经典信号表示先测量、后压缩信息或数据，从而“找到规则／规律”。
- Take-home message: Sparsity and regularization are the keys for extreme compression

  要点：稀疏性与正则化是实现极高压缩率的关键。
- Technological breakthroughs have been achieved in imaging such as the ”one-pixel camera”

  成像技术中已经出现突破，例如“单像素相机”。
- Pioneering work by Cand`es-Romberg-Tao (2006) and Donoho (2006)

  开创性工作：Candès、Romberg、Tao（2006）和 Donoho（2006）。
- Want to recover the signal $\boldsymbol { y } \in \mathbb { R } ^ { d }$ based on few measurements $x _ { i } = z _ { i } ^ { T } y$ for $i = 1 , \ldots , n$ with $\boldsymbol { n } \ll d$ where $z _ { i }$ are random ”directions”.

  希望基于少量测量 $x _ { i } = z _ { i } ^ { T } y$ 恢复信号 $\boldsymbol { y } \in \mathbb { R } ^ { d }$，其中 $i = 1 , \ldots , n$，满足 $\boldsymbol { n } \ll d$，$z _ { i }$ 是随机“方向”。
- Assumption: the signal y has a sparse linear representation, meaning that there exists a sparse vector $\beta$ such that $y = \Psi \beta$ where Ψ is the matrix of basis vectors.

  假设：信号 y 具有稀疏线性表示，即存在稀疏向量 $\beta$，使 $y = \Psi \beta$，其中 Ψ 是由基向量组成的矩阵。
- Compressed sensing can then be formulated as a linear program wrt $\beta \mathbf { : }$ :

  于是，压缩感知可以写成关于 $\beta \mathbf { : }$ 的线性规划：

$$
\min _ {\beta \in \mathbb {R} ^ {d}} \| \beta \| _ {1} \text{满足} X = Z \Psi \beta
$$

where the vector $X \in \mathbb { R } ^ { n }$ contains the observations, and the two matrices $Z$ (design matrix of size $n \times d )$ and $\boldsymbol { \Psi }$ (square matrix $d \times d$ , basis of $\mathbb { R } ^ { d } )$ are fixed and known.

其中向量 $X \in \mathbb { R } ^ { n }$ 包含观测；矩阵 $Z$（大小为 $n \times d )$ 的设计矩阵）与 $\boldsymbol { \Psi }$（大小为 $d \times d$、构成 $\mathbb { R } ^ { d } )$ 的一组基的方阵）都固定且已知。

- Eventually, the signal is recovered (de-compressed) thanks to the relation $y = \Psi \beta$

  最后，利用关系 $y = \Psi \beta$ 恢复信号，即解压缩。

**备注：** 根据设计矩阵的选择，可以得到一族不同的过程；通常使用元素服从高斯分布或 Rademacher 分布的随机矩阵。

<a id="reading-dictionary-learning-compressed-sensing"></a>

**Complément — Dictionary Learning vs. PCA, biconvex alternating minimization, and the mathematics of Compressed Sensing**

**补充——字典学习与 PCA 的对比、双凸交替最小化，以及压缩感知的数学原理**

1. **Dictionary Learning / Sparse Coding (§30–32) vs. PCA 字典学习／稀疏编码与 PCA 的本质区别**
   Both PCA ($X \approx P Z$) and Dictionary Learning ($X \approx A Y$) factorize the data matrix $X \in \mathbb{R}^{d\times n}$ into a dictionary/basis matrix times a representation matrix, but with opposite structural priors:
   - **PCA (§24):** requires $P \in \mathbb{R}^{d\times r}$ to have **orthogonal columns** ($r \le d$), while the code matrix $Z \in \mathbb{R}^{r\times n}$ is dense (every sample uses all $r$ principal components).
   - **Dictionary Learning (§30–32):** allows the dictionary $A = [a_1, \dots, a_K] \in \mathbb{R}^{d\times K}$ to be **overcomplete** ($K > d$, non-orthogonal "atoms"), while requiring each column $Y_i \in \mathbb{R}^K$ of the code matrix $Y$ to be **sparse** ($\|Y_i\|_0 \le s \ll d$). That is, all samples share a rich vocabulary of $K$ atoms, but each individual patch $X_i$ is reconstructed using only a few atoms tailored to it!
   - **Why is joint optimization nonconvex, and how is it solved (§32)?** Because of the product $A Y$, the objective $\frac{1}{2}\|X - A Y\|_F^2 + \lambda\sum_{i=1}^n \|Y_i\|_1$ is not jointly convex in $(A, Y)$ (for instance, permuting the columns of $A$ and rows of $Y$ gives multiple isolated minima, and scaling $A \mapsto \alpha A, Y \mapsto \alpha^{-1}Y$ shrinks $\|Y\|_1$ unless the columns of $A$ are constrained by $\|a_k\|_2 \le 1$). However, it is **biconvex**:
     1. **Sparse coding step ($A$ fixed, optimize $Y$):** decouples into $n$ independent LASSO problems $\min_{Y_i} \frac{1}{2}\|X_i - A Y_i\|_2^2 + \lambda\|Y_i\|_1$.
     2. **Dictionary update step ($Y$ fixed, optimize $A$):** a smooth convex constrained least-squares problem $\min_{\|a_k\|_2 \le 1} \frac{1}{2}\|X - A Y\|_F^2$, solved efficiently by block coordinate descent over the columns $a_k$.

   PCA（$X \approx P Z$）与字典学习（$X \approx A Y$）都将样本矩阵 $X \in \mathbb{R}^{d\times n}$ 分解为“基／字典矩阵 $\times$ 表示矩阵”，但施加了截然不同的结构先验：
   - **PCA（§24）：** 要求基矩阵 $P \in \mathbb{R}^{d\times r}$ 的列**正交**且维数受限（$r \le d$），而表示矩阵 $Z \in \mathbb{R}^{r\times n}$ 是稠密的（每个样本都同时使用全部 $r$ 个主成分）。
   - **字典学习（§30–32）：** 允许字典矩阵 $A = [a_1, \dots, a_K] \in \mathbb{R}^{d\times K}$ 是**过完备的（overcomplete，$K > d$，各列称为原子 atom，不必正交）**，但要求编码矩阵 $Y$ 的每一列 $Y_i \in \mathbb{R}^K$ **高度稀疏**（$\|Y_i\|_0 \le s \ll d$）。换言之，所有样本共享一个容量丰富的字典 $A$，但每个具体图像块 $X_i$ 只挑选其中极少数几个原子进行组合！
   - **为什么联合优化非凸，以及如何通过交替最小化求解（§32）：** 由于乘积项 $A Y$ 中两个未知矩阵相乘，目标函数 $\frac{1}{2}\|X - A Y\|_F^2 + \lambda\sum_{i=1}^n \|Y_i\|_1$ 关于 $(A, Y)$ 联合非凸（例如同时置换 $A$ 的列与 $Y$ 的行会产生对称等价极小点；且必须约束字典列范数 $\|a_k\|_2 \le 1$，否则令 $A \mapsto \alpha A, Y \mapsto \alpha^{-1}Y$ 并让 $\alpha\to\infty$ 会使惩罚项 $\lambda\|Y\|_1 \to 0$）。但该问题具有优美的**双凸性（biconvexity）**，因此实践中采用交替最小化：
     1. **稀疏编码步（固定字典 $A$，更新编码 $Y$）：** 完全解耦为 $n$ 个独立的 LASSO 问题 $\min_{Y_i} \frac{1}{2}\|X_i - A Y_i\|_2^2 + \lambda\|Y_i\|_1$；
     2. **字典更新步（固定编码 $Y$，更新字典 $A$）：** 转化为凸的球约束最小二乘问题 $\min_{\|a_k\|_2 \le 1} \frac{1}{2}\|X - A Y\|_F^2$，可对字典各列 $a_k$ 用分块坐标下降高效更新。

2. **Compressed Sensing (§33): how can $n \ll d$ measurements recover a $d$-dimensional signal exactly? 压缩感知（§33）：为什么远少于维度的测量（$n \ll d$）能精确恢复高维信号？**
   In classical linear algebra, an underdetermined system $X = \Phi\beta$ (where $\Phi = Z\Psi \in \mathbb{R}^{n\times d}$ has $n \ll d$ rows) has an infinite $(d-n)$-dimensional affine subspace of solutions $\beta$. How can the Basis Pursuit linear program $\min_\beta \|\beta\|_1$ subject to $\Phi\beta = X$ recover the *exact* true vector $\beta^*$?
   - **Sparsity prior:** Although the signal lives in $\mathbb{R}^d$, its coefficient vector $\beta^* \in \mathbb{R}^d$ in a known orthonormal basis $\Psi \in \mathbb{R}^{d\times d}$ (such as wavelets or Fourier) is **$k$-sparse** ($\|\beta^*\|_0 \le k \ll n \ll d$).
   - **Sufficient recovery conditions (Restricted Isometry Property / RIP & Null-Space Property):** If we measured only the first $n$ coordinates of $\beta^*$, any nonzero component in coordinates $n+1,\dots,d$ would be lost. Instead, let the measurement matrix $Z \in \mathbb{R}^{n\times d}$ have i.i.d. entries normalized to variance $1/n$ (e.g., $Z_{ij} \sim \mathcal{N}(0, 1/n)$ or $\pm 1/\sqrt{n}$ Rademacher variables, so that each column has expected unit $\ell_2$ norm). Because $\Psi$ is orthonormal, $\Phi = Z\Psi$ has the same sub-Gaussian distribution. Candès, Romberg, & Tao (2006) and Donoho (2006) proved that when $n \ge C_\delta k \log(d/k)$, $\Phi$ satisfies the **Restricted Isometry Property (RIP)** of order $2k$ with high probability: for every $2k$-sparse vector $v$,
     $$(1 - \delta_{2k})\|v\|_2^2 \le \|\Phi v\|_2^2 \le (1 + \delta_{2k})\|v\|_2^2.$$
     When the RIP constant $\delta_{2k}$ is **sufficiently small**—for instance, under the classic sufficient condition **$\delta_{2k} < \sqrt{2} - 1 \approx 0.414$** (Candès, 2008)—$\Phi$ satisfies the **Null Space Property (NSP)** of order $k$ ($\|h_S\|_1 < \|h_{S^c}\|_1$ for all $h \in \ker(\Phi)\setminus\{0\}$ and $|S|\le k$). Geometrically, this prevents the $(d-n)$-dimensional null space $\ker(\Phi)$ from entering the $\ell_1$ cross-polytope from $\beta^*$, ensuring that the affine solution space $\{\beta : \Phi\beta = X\}$ intersects the $\ell_1$ ball of radius $\|\beta^*\|_1$ **uniquely at the low-dimensional ($(k-1)$-dimensional) boundary face (or vertex when $k=1$) containing the sparse ground truth $\beta^*$**!

   在线性代数中，当观测数远小于未知数个数（$n \ll d$）时，欠定线性方程组 $X = \Phi\beta$（其中传感矩阵 $\Phi = Z\Psi \in \mathbb{R}^{n\times d}$）的解集是一个 $(d-n)$ 维仿射子空间，有无穷多解。为什么第 33 节的基追踪（Basis Pursuit）问题 $\min_\beta \|\beta\|_1 \text{ s.t. } \Phi\beta = X$ 能够从中**唯一精确恢复**真实信号 $\beta^*$？
   - **稀疏先验：** 尽管信号在原空间是 $d$ 维的，但它在已知标准正交基 $\Psi \in \mathbb{R}^{d\times d}$（如小波基）下的系数向量 $\beta^*$ 是 **$k$-稀疏的**（$\|\beta^*\|_0 \le k \ll n \ll d$）。
   - **精确恢复的充分条件（限制等距性质 RIP 与零空间性质 NSP）：** 如果直接采样前 $n$ 个坐标，其余 $d-n$ 个坐标的信息会完全丢失；而若令随机测量矩阵 $Z \in \mathbb{R}^{n\times d}$ 的元素独立同分布且**方差归一化为 $1/n$**（例如 $Z_{ij} \sim \mathcal{N}(0, 1/n)$ 或取 $\pm 1/\sqrt{n}$ 的 Rademacher 变量，使每列期望欧氏范数为 $1$），则由 $\Psi$ 的正交不变性，$\Phi = Z\Psi$ 同样是列归一化的次高斯随机矩阵。Candès、Romberg、Tao（2006）与 Donoho（2006）证明：当观测数满足
     $$n \ge C_\delta \, k \log(d/k)$$
     时，矩阵 $\Phi = Z\Psi$ 以高概率满足 $2k$ 阶**限制等距性质（Restricted Isometry Property, RIP）**——即对任意 $2k$-稀疏向量 $v$，有
     $$(1 - \delta_{2k})\|v\|_2^2 \le \|\Phi v\|_2^2 \le (1 + \delta_{2k})\|v\|_2^2.$$
     当等距常数 $\delta_{2k}$ **足够小**——例如满足经典充分条件 **$\delta_{2k} < \sqrt{2} - 1 \approx 0.414$**（Candès, 2008）时，矩阵 $\Phi$ 满足 $k$ 阶**零空间性质（Null Space Property, NSP）**（即对任意非零零空间向量 $h \in \ker(\Phi)\setminus\{0\}$ 及 $|S|\le k$，均有 $\|h_S\|_1 < \|h_{S^c}\|_1$）。从几何上看，这保证了仿射解空间 $\{\beta : \Phi\beta = X\}$ 不会刺入半径为 $\|\beta^*\|_1$ 的 $\ell_1$ 正轴体（cross-polytope）内部，而是与该 $\ell_1$ 球面在 $\beta^*$ 所在的**低维（$k-1$ 维）边界面（当 $k=1$ 时为顶点）处唯一相交于真实稀疏解 $\beta^*$**！此外，通过令 $\beta = \beta^+ - \beta^-$（$\beta^+, \beta^- \ge 0$），该问题可直接化为标准**线性规划（Linear Program）**求解。

<a id="section-34"></a>

**Wrap-up and other topics**

## 小结与其他主题

- Representation learning aims at extracting structure from complex low-level data

  表示学习旨在从复杂的低层数据中提取结构。
- Practical methods rely on high dimensional statistical modeling, linear algebra and optimization formulations inspired from machine learning techniques

  实用方法依赖高维统计建模、线性代数，以及受机器学习技术启发的优化表述。
- Dictionary learning is an example of unsupervised learning task

  字典学习是无监督学习任务的一个例子。
- Other unsupervised learning problems are:

  其他无监督学习问题包括：
- Clustering (or segmentation or unsupervised classification)

  聚类（也称分割或无监督分类）。
- Anomaly detection

  异常检测。
- Novelty detection

  新颖性检测。
