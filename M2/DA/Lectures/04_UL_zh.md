# 无监督学习与降维：原课件忠实译本

> 正文按原课件顺序逐段翻译，不作摘要式压缩；例子、练习、重复正文、公式、图表及文献均保留。图中文字保留原图语言。原课件错误与必要辨析以独立“译注”标明。

[原 PDF](04_UL.pdf) · [原文转换稿](04_UL.md) · [逐块对应清单](Translation-audit/2026-09-28-coverage.json) · [课程目录](../README.md)

<details>
<summary>本讲目录（点击展开）</summary>

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

</details>

**数据科学与机器学习导论**

Nicolas Vayatis

<a id="section-01"></a>

## 无监督学习与降维

- 机器学习就是从数据中学习（即选择、估计）一个函数。
- 关键概念是寻找解时所在函数空间（“假设空间”）的复杂度，即“从多少个函数中作选择”。
- 学习的技巧在于利用数据调整假设空间的复杂度，同时隐含地考虑近似误差。
- 对最小二乘线性回归这一特殊情形，也可以通过仅选择并使用一小部分变量来调整复杂度，这就是变量选择问题。

<a id="section-02"></a>

## 学习的另一幅“全景图”

![image](<Images/04_UL/image_001.jpg>)

<a id="section-03"></a>

## 本讲目标

- 重点是特征选择与特征学习：学习（“寻找”或“选择”）数据的一种表示。此前的理论重点是：对给定的特征集合（“表示”），学习用于预测的函数，并对其泛化／预测误差给出界。

今天：针对其他应用提出新的正则化／机器学习表述，例如学习矩阵，即估计矩阵中缺失的元素；推荐系统就是一个应用例子。

- 此外：学习一些求解机器学习问题表述／方法的优化途径，这些问题可能是非凸的。优化是机器学习的核心。

<a id="section-04"></a>

## 稀疏性入门

- 诱导稀疏性的回归方法：LASSO。
- 在线性预测模型中的动机：松弛对所用自变量个数的 $\ell _ { 0 }$ 约束，即从最小化

$$
\| \mathbf {Y} - \mathbf {X} \boldsymbol {\beta} \| ^ {2} + \lambda \| \boldsymbol {\beta} \| _ {0}
$$

变为最小化

$$
\| \mathbf {Y} - \mathbf {X} \boldsymbol {\beta} \| ^ {2} + \lambda \| \boldsymbol {\beta} \| _ {1}
$$

- 优点：计算可处理，模型可解释。
- 附带结果：稀疏选择一致性，即使用多少个变量、使用哪些变量。

<a id="section-05"></a>

## 今天的应用：具有（秩）稀疏性的矩阵补全——Netflix 推荐竞赛

![image](<Images/04_UL/image_002.jpg>)

评分矩阵

<a id="section-06"></a>

## 今天的应用：具有（秩）稀疏性的矩阵补全——Netflix 推荐竞赛

- 给定含有缺失值的矩阵 M，寻找与 M 的已知元素一致且秩最小的矩阵 X（为什么要秩最小？本讲稍后说明）：

$$
\min _ {X} \{\operatorname{rank} (X) \} \text{满足} X _ {i j} = M _ {i j}    , \forall (i, j) \in \Omega
$$

其中 $\Omega=\{(i,j):M_{ij}\text{ 未缺失}\}$。

- 怎样求解这个困难的优化问题？它为什么困难？

<a id="section-07"></a>

## 稀疏特征选择与学习

A. 特征选择：LASSO 及其优化方法。

B. 特征学习：PCA 及其变体。

C. 应用：矩阵补全、稀疏编码、压缩感知。

<a id="section-08"></a>

## A. 特征选择：LASSO 及其优化方法

### 线性模型的 LASSO：从 $\ell _ { 0 }$ 到 $\ell _ { 1 }$

- 考虑 LASSO 估计（学习）方法：对任意 $\lambda > 0$，

$$
\widehat {\beta} _ {\lambda} \in \underset {\beta \in \mathbb {R} ^ {d}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| ^ {2} + \lambda \| \beta \| _ {1} \right\}
$$

其中 $\ell _ { 1 } { \mathrm { - } } \mathsf { n o r m }$ 为：

$$
\| \beta \| _ {1} = \sum_ {j = 1} ^ {d} | \beta_ {j} |
$$

<a id="section-09"></a>

## LASSO 的优点

- 通过构建所谓正则化路径的高效算法求近似解：对 λ 的所有取值，找到相应的 ${ \widehat { \beta } } ( \lambda ) )$。

![image](<Images/04_UL/image_003.jpg>)

- 理论依据：可以证明（如果真实模型是线性的），当 $n , d \to \infty$ 时，

$$
\frac {1}{n} \mathbb {E} \big (\| \mathbf {X} \beta^ {*} - \mathbf {X} \widehat {\beta} \| ^ {2} \big) \leq C \| \beta^ {*} \| _ {1} \sqrt {\frac {\log d}{n}}
$$

<a id="sparse-optimization"></a>

<a id="section-10"></a>

## LASSO 估计的优化方法

［主要提供不同方法及文献的线索。］

- 最小角回归。
- 坐标下降。
- 近端方法。

<a id="section-11"></a>

## 第一种算法：最小角回归（LARS）

- LARS 是向线性模型中逐步增加变量的增量过程的一种变体。
- Efron、Hastie、Johnstone、Tibshirani 的论文 Least Angle Regression（最小角回归），发表于 Annals of Statistics，2004 年。
- 更早的工作包括 Osborne 等（2000）提出的所谓同伦方法。
- 也与正交匹配追踪等贪心方法有关（Mallat、Zhang，1993；Mallat、Davis、Zhang，1994）。
- 恢复 LASSO 的完整正则化路径 $\lambda \to { \hat { \beta } } ( \lambda )$。
- 该过程之所以成功，基于 LASSO 路径分段线性这一事实。
- 计算效率：每一步进行一次普通最小二乘计算。

<a id="section-12"></a>

## 最小角回归：伪代码

1. 从所有系数 $\beta$ 均为零开始。
2. 找出与 y 相关性最高的预测变量 $x _ { j }$。
3. 沿着与 y 的相关系数符号所指的方向增加系数 $\beta _ { j }$，直到另一个预测变量 $x _ { k }$ 与 $\boldsymbol { r } = \boldsymbol { y } - \boldsymbol { \hat { y } }$ 的相关程度达到 $x _ { j }$ 的水平。
4. 沿联合最小二乘方向增加 $( \beta _ { j } , \beta _ { k } )$，直到另一个预测变量 $x _ { m }$ 与残差 r 的相关程度也达到相同水平。
5. 继续，直到所有预测变量都进入模型，这对应于 λ 很小时的解。

> **译注：** 原页是最小角回归的概略伪代码。构造完整 LASSO 路径时还需处理活跃系数降到零、从活跃集中移除等步骤。

<a id="section-13"></a>

## 第二种算法：坐标下降

- 简单思路：循环遍历所有变量，每次进行一维优化，直到收敛。
- 每一步的优化相当于一个一维 LASSO 问题。
- 解由一维普通最小二乘估计经过软阈值处理得到。

![image](<Images/04_UL/image_004.jpg>)

<a id="section-14"></a>

## 第三种算法：近端方法

Parikh 与 Boyd 的教程论文（2013）：“正如 Newton 方法是求解中等规模无约束光滑优化问题的标准工具，近端算法可以看作处理这些问题的非光滑、带约束、大规模或分布式版本的类似工具。”

- 早期工作可追溯至 Moreau（20 世纪 60 年代），以及后来的 Nemirovski、Yudin（1983）。
- 大约在 2005 年因信号处理应用及某些优化问题的求解而重新受到重视。
- 适用于如下形式的问题：

$$
\min _ {\beta} \left\{L (\beta) + \psi (\beta) \right\}
$$

其中 L 光滑、凸、梯度“有界”，而 $\psi$ 连续、凸，但不光滑。

- 近端算法是一种下降算法，按如下方式产生序列 $\beta _ { t }$：在每一步 t，

$$
\beta_ {t} = \operatorname{prox} \left(\psi , \beta_ {t - 1} - \nabla L \left(\beta_ {t - 1}\right)\right)
$$

> **译注：** 原页省略了步长，且“梯度有界”不是通常所用的光滑性条件。若 $\nabla L$ 为 $L_g$-Lipschitz，标准近端梯度步写作 $\beta_t=\operatorname{prox}_{\eta\psi}(\beta_{t-1}-\eta\nabla L(\beta_{t-1}))$，例如取 $0<\eta\le1/L_g$；近端项通常要求适当、下半连续且凸。

其中 prox 是所谓的近端算子，它推广了正交投影的概念。

<a id="section-15"></a>

## 近端方法 $( 2 / 4 )$：近端算子的定义

- 对目标函数 $L + \psi$ 中的非光滑项 $\psi$，近端算子定义为：

$$
\operatorname{prox} \bigl (\psi , z \bigr) = \arg \min _ {\beta} \left\{\frac {1}{2} \| \beta - z \| _ {2} ^ {2} + \psi (\beta) \right\}
$$

- 解释：近端算子寻找一个点，在减小 $\psi$ 与靠近点 z 之间取得权衡。

<a id="section-16"></a>

## 近端方法（3/4）：应用于 LASSO

- 这里 $\begin{array} { r } { L ( \beta ) = \frac { 1 } { 2 } \| X \beta - y \| _ { 2 } ^ { 2 } } \end{array}$，且 $\psi ( { \boldsymbol { \beta } } ) = \lambda \| { \boldsymbol { \beta } } \| _ { 1 }$。
- 梯度步使用光滑项 L 的梯度：

$$
\nabla L (\beta) = X ^ {T} (X \beta - y)
$$

- $\ell _ { 1 }$ 范数的近端算子为：

$$
\operatorname{prox} (\lambda \| \cdot \| _ {1}, z) = (z - \lambda) _ {+} - (- z - \lambda) _ {+}
$$

（对 $z )$ 的每个分量施加软阈值算子。）

- 也称 ISTA，即 Iterative Shrinkage Thresholding Algorithm（迭代收缩阈值算法）。
- 特殊情形：梯度下降、投影梯度。
- 加速版本：FISTA，即 Fast Iterative Shrinkage Thresholding Algorithm（快速迭代收缩阈值算法）。
- 数值收敛速度：从 $O ( 1 / t )$ 改进到 $O ( 1 / t ^ { 2 } )$。

<a id="pca"></a>

<a id="section-17"></a>

## B. 特征学习：PCA 及其变体

### 所有学生都应该知道的内容：PCA

- 动机：降维。
- 原理：寻找一组正交基来表示数据、将数据投影到其上，使其捕获数据离散程度（方差）最大的方向。
- 隐含假设：高斯且高度相关的数据。

> **译注：** 高斯性不是计算 PCA 的必要条件；PCA 的线性代数构造适用于一般具有有限二阶矩的数据。这里保留原课件的建模动机。

![image](<Images/04_UL/image_005.jpg>)

<a id="section-18"></a>

## PCA 的经典构造

- 计算数据的协方差矩阵或相关矩阵。
- 求出该矩阵的特征值和特征向量；特征向量彼此正交。
- 主成分按特征值从大到小排列。
- 将原始数据点投影到前 r 个主要特征向量上，将维度从 d 降到较小的 r。

<a id="section-19"></a>

## PCA 应用于音乐推荐

LastFM 数据集。

![image](<Images/04_UL/image_006.jpg>)

![image](<Images/04_UL/image_007.jpg>)

<a id="section-20"></a>

## PCA 应用于时间序列：职位招聘数据

JOLTS 数据集可从 https://www.bls.gov/jlt/ 获取。

![image](<Images/04_UL/image_008.jpg>)

![image](<Images/04_UL/image_009.jpg>)

<a id="section-21"></a>

## PCA 应用于时间序列：职位招聘数据

### 成分解释

![image](<Images/04_UL/image_010.jpg>)

![image](<Images/04_UL/image_011.jpg>)

![image](<Images/04_UL/image_012.jpg>)

![image](<Images/04_UL/image_013.jpg>)

<a id="section-22"></a>

## PCA 应用于时间序列：职位招聘数据

### 投影到主成分

![image](<Images/04_UL/image_014.jpg>)

![image](<Images/04_UL/image_015.jpg>)

![image](<Images/04_UL/image_016.jpg>)

![image](<Images/04_UL/image_017.jpg>)

<a id="section-23"></a>

## PCA 应用于时间序列：金融数据（1/2）

Avellaneda 与 Lee（2008）的论文。

![image](<Images/04_UL/image_018.jpg>)

图 1：使用一年窗口估计、于 2007 年 5 月 1 日计算的市场收益率相关矩阵的特征值，以解释方差百分比表示。

Avellaneda 与 Lee（2008）的论文。

![image](<Images/04_UL/image_019.jpg>)

图 4：按系数大小排序的第一特征向量。横轴给出与各股票所属行业对应的 ETF。

<a id="low-rank"></a>

<a id="section-24"></a>

## 从另一角度看 PCA

- 用 $X$ 表示大小为 $d \times n$ 的数据矩阵（假设数据点已经中心化），用 $\begin{array} { r } { \| M \| _ { F } ^ { 2 } = \sum _ { i , j } M _ { i j } ^ { 2 } } \end{array}$ 表示矩阵 $M = ( \bar { M } _ { i j } ) _ { i j }$ 的 Frobenius 范数的平方。
- 求解最小化问题：

$$
\min _ {P, Z} \| X - P Z \| _ {F} ^ {2} \text{满足} P ^ {T} P = I _ {r}
$$

其中 $P$ 是大小为 $d \times r$ 的投影矩阵，其列为前 r 个特征向量；$Z$ 是大小为 $r \times n$ 的矩阵，记录投影到 r 维子空间后的数据点。同时有正交约束 $P ^ { T } P = I _ { r }$，因为特征向量彼此正交。

<a id="section-25"></a>

## PCA 的低秩表述

- 令 $A = P Z$，前述优化问题可改写为：

$$
\min _ {A} \| X - A \| _ {F} ^ {2} \text{满足} \operatorname{rank} (A) = r
$$

- 理论结果（Vidal、Ma、Sastry，2016）：该问题的一个最优解为：

$$
A = U _ {r} \Sigma_ {r} V _ {r}
$$

> **译注：** 按下文的矩阵维度，原式漏了转置，应为 $A=U_r\Sigma_rV_r^T$。最佳低秩逼近通常写成 $\operatorname{rank}(A)\le r$；若要求严格等于 r，还需注意原矩阵秩不足 r 的情况。

其中 $U _ { r }$ 和 $V _ { r }$ 的列正交，大小分别为 $d \times r$ 和 $n \times r$；$\textstyle \sum _ { r }$ 是大小为 $r \times r$ 的对角方阵。矩阵 $U _ { r } , \ \Sigma _ { r } , \ V _ { r }$ 对应矩阵 X 的约化奇异值分解（SVD）。

<a id="section-26"></a>

## 线性代数背景：奇异值分解

特征值与特征向量的推广。

- 定义：如果存在两个单位向量 $u \in \mathbb { R } ^ { d }$ 和 $v \in \mathbb { R } ^ { n }$，使得下式成立，则 σ 是大小为 $d \times n$ 的矩形矩阵 X 的一个奇异值：

$$
X ^ {T} u = \sigma v \text{且} X v = \sigma u
$$

向量 u 和 v 称为奇异向量。

- 定理：对任意矩形矩阵，存在大小分别为 $d \times d$ 和 $n \times n$ 的正交矩阵 U、V，以及大小为 $d \times n$ 的对角矩阵 $\boldsymbol { \Sigma }$，使得：

$$
X = U \Sigma V ^ {T}
$$

- PCA 对异常值敏感；经验协方差矩阵随样本量增加而向真实协方差矩阵收敛的速度较慢……
- 如果自然成分不是高斯的，会怎样？如果它们并非正交，而是独立的呢（不仅检查相关性）？……
- 可解释性呢？也许需要矩阵 Z（新的数据表示）非负 → 非负矩阵分解。

<a id="section-27"></a>

## 非负矩阵分解

![image](<Images/04_UL/image_020.jpg>)

D. D. Lee 与 H. S. Seung，Learning the parts of objects by non-negative matrix factorization（通过非负矩阵分解学习对象的组成部分），Nature 401 (6755)，第 788–791 页，1999。

<a id="section-28"></a>

## PCA 的推广：机器学习问题表述示例

- 例子：Candès、Li、Ma、Wright（2011）的稳健 PCA。
- 动机：假设数据矩阵可以分解为 X = L + S，其中 L 为低秩矩阵，S 为稀疏矩阵。

主成分追踪：核范数（也称迹范数）$\| \cdot \| _ { * }$ 定义为奇异值之和；用 $\| \cdot \| _ { 1 }$ 表示矩阵的 $\ell _ { 1 }$ 范数，即所有元素绝对值之和。寻找矩阵 L 和 S：

$$
\min _ {L, S} \| L \| _ {*} + \lambda \| S \| _ {1} \text{满足} L + S = X
$$

- 主要理论结果：在某些假设下，这个过程可以恢复精确解。
- 稀疏 PCA。
- 非线性 PCA、核 PCA。

参考书：Vidal、Ma、Sastry，Generalized Principal Component Analysis（广义主成分分析），Springer，2016。

<a id="completion"></a>

<a id="section-29"></a>

## C. 应用：矩阵补全与压缩感知

### 矩阵补全：推荐系统应用

![image](<Images/04_UL/image_021.jpg>)

- 原始优化表述：一种“Ivanov 正则化”，要求在可用的矩阵元素（即数据）上没有误差。

$$
\min _ {X} \{\operatorname{rank} (X) \} \text{满足} X _ {i j} = M _ {i j}    , \forall (i, j) \in \Omega
$$

其中 $\Omega=\{(i,j):M_{ij}\text{ 为可用数据}\}$。

- 关键挑战：非凸问题，难以求解。

### 凸松弛

- 回顾：X 的核范数为 $\| X \| _ { * } = \sum _ { i = 1 } \sigma _ { i }$，其中 $\sigma _ { i }$ 是 X 的奇异值；回顾 X 的奇异值分解为 $X = U \Sigma V ^ { T } )$。
- 矩阵补全问题的凸表述：

$$
\min _ {X} \| X \| _ {*} \text{满足} X _ {i j} = M _ {i j}, \forall (i, j) \in \Omega
$$

其中 $\Omega=\{(i,j):M_{ij}\text{ 为可用数据}\}$。

- 正则化表述：核范数惩罚。

$$
\min _ {X} \left\{\frac {1}{2} \sum_ {i j \in \Omega} (X _ {i j} - M _ {i j}) ^ {2} + \lambda \| X \| _ {*} \right\}
$$

- 简化问题（没有掩码 Ω）：

$$
\min _ {X} \left\{\frac {1}{2} \| X - M \| ^ {2} + \lambda \| X \| _ {*} \right\}
$$

- 解有闭式表达，给出如下：

$$
\operatorname{shrink} (X, \lambda) = U \Sigma (\lambda) V ^ {T}
$$

其中 $\Sigma ( \lambda ) = \mathrm { d i a g } ( ( \sigma _ { i } - \lambda ) _ { + } )$。

- 注意：该解只使用大于 λ 的奇异值……
- 需要一种技巧来处理 $\Omega$。
- 使用一个完整的辅助矩阵 Y。
- 定义矩阵 $\Pi _ { \Omega } ( X )$：当 $( i , j ) \in \Omega$ 时，其元素为 $X _ { i j }$；当 $( i , j ) \notin \Omega$ 时，其元素为零。
- 迭代算法 $\left( \mathsf { c a l l e d } ^ { \prime \prime } \mathsf { S V T } ^ { \prime \prime } \right)$。
1. 设定 $\lambda > 0$ 和步长序列 $( \delta _ { k } ) _ { k \geq 1 }$。
2. 从大小为 $n \times m$ 的矩阵 $Y _ { 0 } = 0$ 开始。
3. 在每一步 $k ,$，计算：

$$
\left\{ \begin{array}{l l} X _ {k} & = \text { shrink } (Y _ {k - 1}, \lambda) \\ Y _ {k} & = Y _ {k - 1} + \delta_ {k} \Pi_ {\Omega} (M - X _ {k}) \end{array} \right.
$$

<a id="dictionary"></a>

<a id="section-30"></a>

## C.2. 字典学习

### 动机与参考资料

- 某些用于表示数据的特征可能有利于压缩，但不利于解释，反之亦然；它们也可能根本无法产生稀疏表示，例如无法学到只使用少量特征的函数。
- 能否学习一种数据特征（表示），使得在这种表示“空间”中学习或估计的函数也是稀疏的？
- 思路：利用数据中相似模式可能重复出现这一事实，即使这些模式不光滑。
- （也可用于处理某些非平稳情形。）

参考文献：Olshausen 与 Field（1997）；Kreutz-Delgado 等（2003）；Mairal、Elad、Sapiro（2008）；Gribonval 等（2015）。

<a id="section-31"></a>

## 稀疏编码：问题表述

- 目标：同时寻找 A（“特征”）和 Y，使其在允许误差 ε 的范围内给出数据 X 的稀疏表示。
- 表述：

$$
\min _ {A, Y} \left\{\sum_ {i = 1} ^ {n} \| Y _ {i} \| _ {0} \right\} \text{满足} \| X - A Y \| _ {2} \leq \varepsilon
$$

<a id="section-32"></a>

## 稀疏编码：走向非凸优化

- 与 $\ell _ { 0 }$ 范数最小化问题具有相同的复杂度。实践中使用 $\ell _ { 1 } { \mathsf { - t y p e } }$ 松弛求解。
- 但是：固定 $A ,$ 时，关于 Y 的最小化是凸的；同时关于 A 和 Y 的联合优化却不是凸的。
- 非凸矩阵分解问题的主要策略：交替最小化（Douglas–Rachford），或分块坐标下降。

> **译注：** 交替最小化、分块坐标下降与 Douglas–Rachford 分裂有不同的算法定义，不能直接视为同一算法。原课件括号中的归类保留，但应作此区分。

- 图像（文本？多媒体？等等）。

![image](<Images/04_UL/image_022.jpg>)

- 消费品的表示（“元属性”）与效用函数；另见第 13–14 次课中的联合分析和多任务学习。

稀疏性

<a id="section-33"></a>

## C.3. 压缩感知

### 信号处理中的一场革命

- 经典信号表示先测量、后压缩信息或数据，从而“找到规则／规律”。
- 要点：稀疏性与正则化是实现极高压缩率的关键。
- 成像技术中已经出现突破，例如“单像素相机”。
- 开创性工作：Candès、Romberg、Tao（2006）和 Donoho（2006）。
- 希望基于少量测量 $x _ { i } = z _ { i } ^ { T } y$ 恢复信号 $\boldsymbol { y } \in \mathbb { R } ^ { d }$，其中 $i = 1 , \ldots , n$，满足 $\boldsymbol { n } \ll d$，$z _ { i }$ 是随机“方向”。
- 假设：信号 y 具有稀疏线性表示，即存在稀疏向量 $\beta$，使 $y = \Psi \beta$，其中 Ψ 是由基向量组成的矩阵。
- 于是，压缩感知可以写成关于 $\beta \mathbf { : }$ 的线性规划：

$$
\min _ {\beta \in \mathbb {R} ^ {d}} \| \beta \| _ {1} \text{满足} X = Z \Psi \beta
$$

其中向量 $X \in \mathbb { R } ^ { n }$ 包含观测；矩阵 $Z$（大小为 $n \times d )$ 的设计矩阵）与 $\boldsymbol { \Psi }$（大小为 $d \times d$、构成 $\mathbb { R } ^ { d } )$ 的一组基的方阵）都固定且已知。

- 最后，利用关系 $y = \Psi \beta$ 恢复信号，即解压缩。

**备注：** 根据设计矩阵的选择，可以得到一族不同的过程；通常使用元素服从高斯分布或 Rademacher 分布的随机矩阵。

<a id="section-34"></a>

## 小结与其他主题

- 表示学习旨在从复杂的低层数据中提取结构。
- 实用方法依赖高维统计建模、线性代数，以及受机器学习技术启发的优化表述。
- 字典学习是无监督学习任务的一个例子。
- 其他无监督学习问题包括：
- 聚类（也称分割或无监督分类）。
- 异常检测。
- 新颖性检测。
