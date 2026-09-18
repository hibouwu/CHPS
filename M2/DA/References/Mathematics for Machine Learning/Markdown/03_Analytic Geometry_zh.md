# 3 解析几何

> 来源：[英文稿](<03_Analytic Geometry.md>) · [本章 PDF](<../PDF/03_Analytic Geometry.pdf>)。本译稿尚未完成，本章全部正文及习题 3.1—3.10 已完成翻译与复核；英文稿已完成全部 28 页 PDF 对照校对。原书疑点另见章节验收记录。

![第 3 章标志图](<Images/03_Analytic_Geometry_image_001.jpg>)

第 2 章从一般而抽象的层面研究了向量、向量空间和线性映射。本章将为这些概念补充几何解释和直觉。具体来说，我们将考察几何向量，计算向量的长度，以及两个向量之间的距离和夹角。为此，给向量空间赋予一个内积（inner product），由它诱导出该空间的几何结构。内积及其对应的范数（norm）和度量（metric），刻画了相似性与距离的直观概念；第 12 章将利用这些概念介绍支持向量机（support vector machine）。随后，我们利用向量长度和夹角讨论正交投影（orthogonal projection）。在第 10 章的主成分分析（principal component analysis），以及第 9 章通过最大似然估计（maximum likelihood estimation）进行回归时，正交投影都将起核心作用。图 3.1 概括了本章各概念之间的关系，以及它们与其他章节的联系。

图 3.1 本章介绍的概念及其在全书其他部分中的应用关系图。

![图 3.1：解析几何概念关系](<Images/03_Analytic_Geometry_image_002.jpg>)

图内标签对照：Inner product——内积；Norm——范数；Lengths——长度；Angles——夹角；Rotations——旋转；Orthogonal projection——正交投影；Classification——分类；Regression——回归；Matrix decomposition——矩阵分解；Dimensionality reduction——降维。induces 表示“诱导”，Chapter 表示“章”。

本材料由剑桥大学出版社以《Mathematics for Machine Learning》出版，作者为 Marc Peter Deisenroth、A. Aldo Faisal 和 Cheng Soon Ong（2020）。本版本仅供个人免费查看和下载，不得再分发、转售或用于衍生作品。© M. P. Deisenroth、A. A. Faisal 和 C. S. Ong，2024。[原书网站](https://mml-book.com)。

## 3.1 范数

将几何向量看作从原点出发的有向线段时，直观上，向量长度就是该有向线段的终点到原点的距离。下面利用范数的概念讨论向量长度。

**定义 3.1（范数）。** 向量空间 V 上的范数是一个函数

$$
\| \cdot \|: V \to \mathbb {R},\tag{3.1}
$$

$$
\boldsymbol {x} \mapsto \| \boldsymbol {x} \|,\tag{3.2}
$$

它为每个向量 x 指定长度 $\| \pmb { x } \| \in \mathbb { R }$，并且对所有 $\lambda \in \mathbb { R }$ 和 $\boldsymbol{x},\boldsymbol{y}\in V$，满足以下条件：

- **绝对齐次性（absolute homogeneity）：** $\| \lambda \pmb { x } \| = | \lambda | \| \pmb { x } \|$。

- **三角不等式（triangle inequality）：** $\| { \pmb x } + { \pmb y } \| \leqslant \| { \pmb x } \| + \| { \pmb y } \|$。

- **正定性（positive definiteness）：** $\| \pmb { x } \| \geqslant 0$，且 $\| { \pmb x } \| = 0 \iff { \pmb x } = \mathbf { 0 }$。

从几何上说，三角不等式表示：任意三角形的任意两边长度之和，都大于或等于第三边长度，见图 3.2。定义 3.1 针对一般向量空间 V，见 2.4 节，但本书只考虑有限维向量空间 $\mathbb { R } ^ { n }$。回顾一下，对向量 $\pmb { x } \in \mathbb { R } ^ { n }$，用下标表示其元素，即 $x _ { i }$ 是向量 x 的第 $i$ 个元素。

![图 3.2：三角不等式](<Images/03_Analytic_Geometry_image_004.jpg>)

图 3.2 三角不等式。

**例 3.1（曼哈顿范数）**

对 $\pmb { x } \in \mathbb { R } ^ { n }$，$\mathbb { R } ^ { n }$ 上的曼哈顿范数（Manhattan norm）定义为

$$
\left\| \boldsymbol {x} \right\| _ {1} := \sum_ {i = 1} ^ {n} \left| x _ {i} \right|,\tag{3.3}
$$

其中 $| \cdot |$ 表示绝对值。图 3.3 左图展示了满足 $\| \pmb { x } \| _ { 1 } = 1$ 的所有向量 $\boldsymbol{x}\in\mathbb{R}^{2}$。曼哈顿范数也称 $\ell_1$ 范数。

**例 3.2（欧几里得范数）**

向量 $\pmb { x } \in \mathbb { R } ^ { n }$ 的欧几里得范数（Euclidean norm）定义为

$$
\| \boldsymbol {x} \| _ {2} := \sqrt {\sum_ {i = 1} ^ {n} x _ {i} ^ {2}} = \sqrt {\boldsymbol {x} ^ {\top} \boldsymbol {x}}\tag{3.4}
$$

它计算 x 到原点的欧几里得距离（Euclidean distance）。图 3.3 右图展示了满足 $\| \pmb { x } \| _ { 2 } = 1$ 的所有向量 $\boldsymbol{x}\in\mathbb{R}^{2}$。欧几里得范数也称 $\ell _ { 2 }$ 范数。

![图 3.3：两种范数的单位向量集合](<Images/03_Analytic_Geometry_image_003.jpg>)

图 3.3 对不同范数，红线表示范数为 1 的向量所组成的集合。左图：曼哈顿范数；右图：欧几里得距离。

**注。** 全书如无特别说明，默认使用式 (3.4) 中的欧几里得范数。◇

## 3.2 内积

内积使我们能够引入直观的几何概念，例如向量长度，以及两个向量之间的夹角或距离。内积的一个主要用途是判断向量是否相互正交（orthogonal）。

### 3.2.1 点积

我们可能已经熟悉一种特殊的内积，即 $\mathbb{R}^{n}$ 中的标量积／点积（scalar product / dot product）：

$$
\boldsymbol {x} ^ {\top} \boldsymbol {y} = \sum_ {i = 1} ^ {n} x _ {i} y _ {i}.\tag{3.5}
$$

本书将这种特殊的内积称为点积。不过，内积是具有特定性质的更一般的概念，下面将介绍这些性质。

### 3.2.2 一般内积

回顾 2.7 节的线性映射：它与加法和标量乘法相容，可以把这些运算移到映射之外。双线性映射（bilinear mapping）Ω 有两个自变量，并且对每个自变量分别线性。也就是说，在向量空间 V 中，对所有 $\boldsymbol{x},\boldsymbol{y},\boldsymbol{z}\in V$、$\lambda,\psi\in\mathbb{R}$，有

$$
\Omega (\lambda \boldsymbol {x} + \psi \boldsymbol {y}, \boldsymbol {z}) = \lambda \Omega (\boldsymbol {x}, \boldsymbol {z}) + \psi \Omega (\boldsymbol {y}, \boldsymbol {z})\tag{3.6}
$$

$$
\Omega (\boldsymbol {x}, \lambda \boldsymbol {y} + \psi \boldsymbol {z}) = \lambda \Omega (\boldsymbol {x}, \boldsymbol {y}) + \psi \Omega (\boldsymbol {x}, \boldsymbol {z}).\tag{3.7}
$$

式 (3.6) 表明 Ω 对第一个自变量线性，式 (3.7) 表明它对第二个自变量线性，另见式 (2.87)。

**定义 3.2。** 设 V 是向量空间，$\Omega:V\times V\to\mathbb{R}$ 是将两个向量映射为一个实数的双线性映射。那么，

- 如果对所有 $x,y\in V$ 都有 $\Omega ( x , y ) = \Omega ( y , x )$，就称 Ω 对称（symmetric），也就是说，自变量的顺序不影响结果。

- 如果满足

$$
\forall \boldsymbol {x} \in V \backslash \{\boldsymbol {0} \}: \Omega (\boldsymbol {x}, \boldsymbol {x}) > 0, \quad \Omega (\boldsymbol {0}, \boldsymbol {0}) = 0.\tag{3.8}
$$

就称 Ω 正定（positive definite）。

**定义 3.3。** 设 $V$ 是向量空间，$\Omega:V\times V\to\mathbb{R}$ 是将两个向量映射为一个实数的双线性映射。那么，

- 正定、对称的双线性映射 $\Omega:V\times V\to\mathbb{R}$ 称为 V 上的内积。通常写作 $\langle { \pmb x } , { \pmb y } \rangle$，而不是 $\Omega ( { \pmb x } , { \pmb y } )$。

- 二元组 $\left( V , \langle \cdot , \cdot \rangle \right)$ 称为内积空间（inner product space），或带内积的实向量空间。如果采用式 (3.5) 定义的点积，则称 $\left( V , \langle \cdot , \cdot \rangle \right)$ 为欧几里得向量空间（Euclidean vector space）。

本书统一把这些空间称为内积空间。

**例 3.3（不同于点积的内积）**

考虑 $V = \mathbb { R } ^ { 2 }$。如果定义

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle := x _ {1} y _ {1} - (x _ {1} y _ {2} + x _ {2} y _ {1}) + 2 x _ {2} y _ {2}\tag{3.9}
$$

那么 $\langle \cdot , \cdot \rangle$ 是内积，但不同于点积。证明留作练习。

### 3.2.3 对称正定矩阵

对称正定矩阵（symmetric positive definite matrix）在机器学习中起重要作用，可以通过内积来定义。4.3 节将在矩阵分解的背景下再次讨论对称正定矩阵。对称半正定矩阵（symmetric positive semidefinite matrix）的概念，则是定义核函数（kernel，12.4 节）的关键。

考虑 n 维向量空间 V，赋予内积 $\langle\cdot,\cdot\rangle:V\times V\to\mathbb{R}$，见定义 3.3，并选择 $V$ 的有序基 $B = ( b _ { 1 } , \ldots , b _ { n } )$。回顾 2.6.1 节，任意向量 $\boldsymbol{x},\boldsymbol{y}\in V$ 都能写成基向量的线性组合：对于合适的 $\psi _ { i } , \lambda _ { j } \in \mathbb { R }$，有 $\begin{array} { r } { \pmb { x } = \sum _ { i = 1 } ^ { n } { \psi _ { i } \pmb { b } _ { i } } \in V } \end{array}$ 和 $\begin{array} { r } { \pmb { y } = \sum _ { j = 1 } ^ { n } \lambda _ { j } \pmb { b } _ { j } \in V } \end{array}$。由内积的双线性性，对所有 $\mathbf { { \pmb { x } } } , \mathbf { { \pmb { y } } } \in V$，有

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle = \left\langle \sum_ {i = 1} ^ {n} \psi_ {i} \boldsymbol {b} _ {i}, \sum_ {j = 1} ^ {n} \lambda_ {j} \boldsymbol {b} _ {j} \right\rangle = \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \psi_ {i} \left\langle \boldsymbol {b} _ {i}, \boldsymbol {b} _ {j} \right\rangle \lambda_ {j} = \hat {\boldsymbol {x}} ^ {\top} \boldsymbol {A} \hat {\boldsymbol {y}},\tag{3.10}
$$

其中 $A _ { i j } : = \langle b _ { i } , b _ { j } \rangle$，而 $\hat { \pmb x } , \hat { \pmb y }$ 分别是 x 和 y 关于基 B 的坐标。这意味着，内积 $\langle \cdot , \cdot \rangle$ 由 A 唯一确定。内积的对称性也意味着 A 对称。此外，内积的正定性意味着

$$
\forall \boldsymbol {x} \in V \backslash \{\mathbf {0} \}: \boldsymbol {x} ^ {\top} \boldsymbol {A} \boldsymbol {x} > 0.\tag{3.11}
$$

**定义 3.4（对称正定矩阵）。** 满足式 (3.11) 的对称矩阵 $\pmb { A } \in \mathbb { R } ^ { n \times n }$ 称为对称正定矩阵，或简称正定矩阵。如果式 (3.11) 只要求大于等于 0，就称 A 为对称半正定矩阵。

**例 3.4（对称正定矩阵）**

考虑矩阵

$$
\boldsymbol {A} _ {1} = \left[ \begin{array}{c c} 9 & 6 \\ 6 & 5 \end{array} \right], \quad \boldsymbol {A} _ {2} = \left[ \begin{array}{c c} 9 & 6 \\ 6 & 3 \end{array} \right].\tag{3.12}
$$

$\pmb { A } _ { 1 }$ 正定，因为它对称，并且

$$
\pmb {x} ^ {\top} \pmb {A} _ {1} \pmb {x} = \left[ \begin{array}{c c} x _ {1} & x _ {2} \end{array} \right] \left[ \begin{array}{c c} 9 & 6 \\ 6 & 5 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \end{array} \right]\tag{3.13a}
$$

$$
= 9 x _ {1} ^ {2} + 12 x _ {1} x _ {2} + 5 x _ {2} ^ {2} = (3 x _ {1} + 2 x _ {2}) ^ {2} + x _ {2} ^ {2} > 0\tag{3.13b}
$$

对所有 ${ \pmb x } \in V \backslash \{ { \bf 0 } \}$ 成立。相比之下，$A _ { 2 }$ 虽然对称，却不正定，因为 $x ^ { \top } A _ { 2 } x = 9 x _ { 1 } ^ { 2 } + 12 x _ { 1 } x _ { 2 } + 3 x _ { 2 } ^ { 2 } = ( 3 x _ { 1 } + 2 x _ { 2 } ) ^ { 2 } - x _ { 2 } ^ { 2 }$ 可以小于 0，例如取 $\pmb { x } = [ 2 , - 3 ] ^ { \top }$。

如果 $A \in \mathbb { R } ^ { n \times n }$ 对称正定，那么

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle = \hat {\boldsymbol {x}} ^ {\top} \boldsymbol {A} \hat {\boldsymbol {y}}\tag{3.14}
$$

定义了关于有序基 $B$ 的一个内积，其中 $\hat{\boldsymbol{x}}$ 和 $\hat{\boldsymbol{y}}$ 是 $\boldsymbol{x},\boldsymbol{y}\in V$ 关于 B 的坐标表示。

**定理 3.5。** 对实有限维向量空间 $V$ 及其有序基 B，$\langle\cdot,\cdot\rangle:V\times V\to\mathbb{R}$ 是内积，当且仅当存在对称正定矩阵 $A \in \mathbb { R } ^ { n \times n }$，使

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle = \hat {\boldsymbol {x}} ^ {\top} \boldsymbol {A} \hat {\boldsymbol {y}}.\tag{3.15}
$$

如果 $\pmb { A } \in \mathbb { R } ^ { n \times n }$ 对称正定，则有以下性质：

- A 的零空间（核）只包含 0，因为对所有 $\mathbf { \boldsymbol { x } } \neq \mathbf { \boldsymbol { 0 } }$ 都有 ${ \pmb x } ^ { \top } { \pmb A } { \pmb x } > 0$。这意味着，如果 $\mathbf { \boldsymbol { x } } \neq \mathbf { 0 }$，就有 $A\boldsymbol{x}\neq\boldsymbol{0}$。

- A 的对角元素 $a _ { i i }$ 为正，因为 $a _ { i i } = e _ { i } ^ { \top } A e _ { i } > 0$，其中 $e _ { i }$ 是 $\mathbb { R } ^ { n }$ 标准基中的第 i 个向量。

## 3.3 长度与距离

3.1 节已经介绍了可用于计算向量长度的范数。内积与范数关系密切：任何内积都能自然地诱导出一个范数

$$
\| \boldsymbol {x} \| := \sqrt {\langle \boldsymbol {x} , \boldsymbol {x} \rangle}\tag{3.16}
$$

这样就可以利用内积计算向量长度。不过，并非每个范数都由内积诱导。曼哈顿范数 (3.3) 就是没有对应内积的一个例子。下面重点讨论由内积诱导的范数，并介绍长度、距离和夹角等几何概念。

**注（柯西–施瓦茨不等式）。** 对内积向量空间 $\left( V , \langle \cdot , \cdot \rangle \right)$，其诱导范数 $\| \cdot \|$ 满足柯西–施瓦茨不等式（Cauchy–Schwarz inequality）：

$$
| \langle \boldsymbol {x}, \boldsymbol {y} \rangle | \leqslant \| \boldsymbol {x} \| \| \boldsymbol {y} \|.\tag{3.17}
$$

**例 3.5（利用内积计算向量长度）**

几何中经常需要计算向量长度。现在可以通过式 (3.16) 用内积计算。取 $\pmb { x } = [ 1 , 1 ] ^ { \top } \in$ $\mathbb { R } ^ { 2 }$，如果使用点积作为内积，由式 (3.16) 得到

$$
\| \boldsymbol {x} \| = \sqrt {\boldsymbol {x} ^ {\top} \boldsymbol {x}} = \sqrt {1 ^ {2} + 1 ^ {2}} = \sqrt {2}\tag{3.18}
$$

这就是 x 的长度。现在选择另一种内积：

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle := \boldsymbol {x} ^ {\top} \left[ \begin{array}{c c} 1 & - \frac {1}{2} \\ - \frac {1}{2} & 1 \end{array} \right] \boldsymbol {y} = x _ {1} y _ {1} - \frac {1}{2} (x _ {1} y _ {2} + x _ {2} y _ {1}) + x _ {2} y _ {2}  .\tag{3.19}
$$

计算向量范数时，如果 $x _ { 1 }$ 与 $x _ { 2 }$ 同号，并且 $x_1x_2>0$，该内积得到的值比点积小；否则，得到的值比点积大。使用该内积，有

$$
\langle \boldsymbol {x}, \boldsymbol {x} \rangle = x _ {1} ^ {2} - x _ {1} x _ {2} + x _ {2} ^ {2} = 1 - 1 + 1 = 1 \implies \| \boldsymbol {x} \| = \sqrt {1} = 1,\tag{3.20}
$$

因此，相比使用点积，x 在这个内积下变得“更短”。

> 译注：上段的“否则更大”沿用原文。由式 (3.19) 可知，若两个分量的乘积为零，两种计算结果相等；乘积为负时，前者才更大。

**定义 3.6（距离与度量）。** 考虑内积空间 $\left( V , \langle \cdot , \cdot \rangle \right)$。那么，

$$
d (\boldsymbol {x}, \boldsymbol {y}) := \| \boldsymbol {x} - \boldsymbol {y} \| = \sqrt {\langle \boldsymbol {x} - \boldsymbol {y} , \boldsymbol {x} - \boldsymbol {y} \rangle}\tag{3.21}
$$

对 $\boldsymbol{x},\boldsymbol{y}\in V$，上式称为 $\boldsymbol{x}$ 与 $\boldsymbol{y}$ 之间的距离。如果内积采用点积，就称为欧几里得距离。

映射

$$
d: V \times V \to \mathbb {R}\tag{3.22}
$$

$$
(\boldsymbol {x}, \boldsymbol {y}) \mapsto d (\boldsymbol {x}, \boldsymbol {y})\tag{3.23}
$$

称为度量。

**注。** 与向量长度类似，定义向量之间的距离并不要求内积，只需范数即可。如果所用范数由内积诱导，那么选择不同内积，距离也可能不同。◇

度量 d 满足以下性质：

1. d 正定，即对所有 $\boldsymbol{x},\boldsymbol{y}\in V$，都有 $d ( { \pmb x } , { \pmb y } ) \geqslant 0$，且 $d(\boldsymbol{x},\boldsymbol{y})=0\iff\boldsymbol{x}=\boldsymbol{y}$。

2. d 对称，即对所有 $\boldsymbol{x},\boldsymbol{y}\in V$，都有 $d ( \pmb { x } , \pmb { y } ) = d ( \pmb { y } , \pmb { x } )$。

3. 三角不等式：对所有 $\pmb { x } , \pmb { y } , \pmb { z } \in V$，都有 $d ( \pmb { x } , z ) \leqslant d ( \pmb { x } , \pmb { y } ) + d ( \pmb { y } , z )$。

**注。** 乍看之下，内积与度量的性质列表十分相似。但比较定义 3.3 和定义 3.6，可以发现 $\langle { \pmb x } , { \pmb y } \rangle$ 与 $d ( { \pmb x } , { \pmb y } )$ 的变化方向相反：非常相似的 $\boldsymbol{x}$ 和 $\boldsymbol{y}$ 会对应较大的内积值和较小的度量值。◇

> 译注：这里是原文对相似性的直观说明；内积的大小还受向量长度影响，不能在长度任意变化时仅凭内积值比较相似程度。

## 3.4 夹角与正交性

内积除了能定义向量长度和两个向量之间的距离，还能通过定义夹角 $\omega$ 来刻画向量空间的几何。利用柯西–施瓦茨不等式 (3.17)，可以在内积空间中定义两个向量 x、y 的夹角 $\omega$，这一概念与我们在 $\mathbb { R } ^ { 2 }$ 和 $\mathbb { R } ^ { 3 }$ 中的直觉一致。假设 $\pmb { x } \neq \mathbf { 0 } , \pmb { y } \neq \mathbf { 0 }$，则有

$$
- 1 \leqslant \frac {\langle \boldsymbol {x} , \boldsymbol {y} \rangle}{\| \boldsymbol {x} \| \| \boldsymbol {y} \|} \leqslant 1.\tag{3.24}
$$

因此，存在唯一的 $\omega \in [ 0 , \pi ]$，使得

$$
\cos \omega = \frac {\langle \boldsymbol {x} , \boldsymbol {y} \rangle}{\| \boldsymbol {x} \| \| \boldsymbol {y} \|}.\tag{3.25}
$$

图 3.4 将自变量限制在 $[ 0 , \pi ]$ 上时，$f ( \omega ) = \cos ( \omega )$ 在区间 [−1, 1] 中返回唯一的数值。

![图 3.4：余弦函数](<Images/03_Analytic_Geometry_image_005.jpg>)

数值 $\omega$ 就是向量 $\boldsymbol{x}$ 与 $\boldsymbol{y}$ 之间的夹角（angle）。直观地说，夹角反映了两个向量方向的相似程度。例如，采用点积时，x 与 $\begin{array} { r } { \pmb { y } = 4 \pmb { x } } \end{array}$ 之间的夹角为 0；这里 y 是 $x$ 缩放后的向量，两者方向相同。

**例 3.6（向量之间的夹角）**

计算 $\pmb { x } = [ 1 , 1 ] ^ { \top } \in \mathbb { R } ^ { 2 }$ 与 $\pmb { y } = [ 1 , 2 ] ^ { \top } \in \mathbb { R } ^ { 2 }$ 之间的夹角，见图 3.5。这里采用点积作为内积，得到

$$
\cos \omega = \frac {\langle \boldsymbol {x} , \boldsymbol {y} \rangle}{\sqrt {\langle \boldsymbol {x} , \boldsymbol {x} \rangle \langle \boldsymbol {y} , \boldsymbol {y} \rangle}} = \frac {\boldsymbol {x} ^ {\top} \boldsymbol {y}}{\sqrt {\boldsymbol {x} ^ {\top} \boldsymbol {x y} ^ {\top} \boldsymbol {y}}} = \frac {3}{\sqrt {10}},\tag{3.26}
$$

两个向量之间的夹角为 arccos $\left( { \frac { 3 } { \sqrt { 10 } } } \right) \approx 0.32 { \mathrm { r a d } }$，约对应 $18^{\circ}$。

![图 3.5：两向量夹角](<Images/03_Analytic_Geometry_image_006.jpg>)

图 3.5 两个向量 x、y 的夹角 ω 通过内积计算。

内积的一个关键特点，是还可以用它刻画正交的向量。

**定义 3.7（正交性）。** 两个向量 x、y 正交，当且仅当 $\langle { \pmb x } , { \pmb y } \rangle = 0$，记作 $\mathbf {  { x } } \perp \mathbf {  { y } }$。如果还满足 $\| { \pmb x } \| = 1 = \| { \pmb y } \|$，即两个向量都是单位向量，就称它们标准正交（orthonormal）。

该定义意味着，零向量与向量空间中的每个向量都正交。

**注。** 正交性是将垂直概念推广到双线性形式后的结果，这种双线性形式不必是点积。在这里，从几何上可以把正交向量理解为：相对于特定内积，它们的夹角是直角。

**例 3.7（正交向量）**

![图 3.6：夹角随内积而变](<Images/03_Analytic_Geometry_image_007.jpg>)

图 3.6 两个向量 x、y 的夹角 ω 可能随所选内积而改变。

考虑两个向量 $\pmb { x } = [ 1 , 1 ] ^ { \top } , \pmb { y } = [ - 1 , 1 ] ^ { \top } \in \mathbb { R } ^ { 2 }$，见图 3.6。用两种不同内积求它们之间的夹角 ω。采用点积作为内积时，x 与 $\boldsymbol{y}$ 之间的夹角 $\omega$ 为 $90^{\circ}$，因此 $\boldsymbol{x}\perp\boldsymbol{y}$。不过，如果选择内积

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle = \boldsymbol {x} ^ {\top} \left[ \begin{array}{c c} 2 & 0 \\ 0 & 1 \end{array} \right] \boldsymbol {y},\tag{3.27}
$$

则 x 与 $\boldsymbol{y}$ 之间的夹角 ω 满足

$$
\cos \omega = \frac {\langle \boldsymbol {x} , \boldsymbol {y} \rangle}{\| \boldsymbol {x} \| \| \boldsymbol {y} \|} = - \frac {1}{3} \implies \omega \approx 1.91 \mathrm{rad} \approx 109.5 ^ {\circ},\tag{3.28}
$$

此时 x、y 不正交。因此，关于某个内积正交的向量，关于另一个内积未必正交。

**定义 3.8（正交矩阵）。** 方阵 $\pmb { A } \in \mathbb { R } ^ { n \times n }$ 为正交矩阵（orthogonal matrix），当且仅当它的各列标准正交，从而

$$
\boldsymbol {A} \boldsymbol {A} ^ {\top} = \boldsymbol {I} = \boldsymbol {A} ^ {\top} \boldsymbol {A},\tag{3.29}
$$

这意味着

$$
\boldsymbol {A} ^ {- 1} = \boldsymbol {A} ^ {\top},\tag{3.30}
$$

即只需转置矩阵，就能得到它的逆。

> 惯例把这些矩阵称为“正交”矩阵，但更准确的描述应是“标准正交”。正交矩阵所表示的变换保持距离和夹角。

正交矩阵表示的变换具有特殊性质：用正交矩阵 A 变换向量 x，不会改变向量的长度。采用点积时，有

$$
\left\| \boldsymbol {A} \boldsymbol {x} \right\| ^ {2} = (\boldsymbol {A} \boldsymbol {x}) ^ {\top} (\boldsymbol {A} \boldsymbol {x}) = \boldsymbol {x} ^ {\top} \boldsymbol {A} ^ {\top} \boldsymbol {A} \boldsymbol {x} = \boldsymbol {x} ^ {\top} \boldsymbol {I} \boldsymbol {x} = \boldsymbol {x} ^ {\top} \boldsymbol {x} = \| \boldsymbol {x} \| ^ {2}.\tag{3.31}
$$

此外，将任意两个向量 x、y 同时用正交矩阵 A 变换，由内积度量的夹角也保持不变。假设内积采用点积，像 Ax 与 $\pmb { A } \pmb { y }$ 的夹角满足

$$
\cos \omega = \frac {(\boldsymbol {A} \boldsymbol {x}) ^ {\top} (\boldsymbol {A} \boldsymbol {y})}{\| \boldsymbol {A} \boldsymbol {x} \| \| \boldsymbol {A} \boldsymbol {y} \|} = \frac {\boldsymbol {x} ^ {\top} \boldsymbol {A} ^ {\top} \boldsymbol {A} \boldsymbol {y}}{\sqrt {\boldsymbol {x} ^ {\top} \boldsymbol {A} ^ {\top} \boldsymbol {A} \boldsymbol {x} \boldsymbol {y} ^ {\top} \boldsymbol {A} ^ {\top} \boldsymbol {A} \boldsymbol {y}}} = \frac {\boldsymbol {x} ^ {\top} \boldsymbol {y}}{\| \boldsymbol {x} \| \| \boldsymbol {y} \|},\tag{3.32}
$$

这恰好给出 x 与 $\boldsymbol{y}$ 之间的夹角。因此，满足 $\pmb { A } ^ { \top } = \pmb { A } ^ { - 1 }$ 的正交矩阵 A 同时保持夹角和距离。正交矩阵所定义的变换是旋转，也可能伴随翻转。3.9 节将更详细地讨论旋转。

## 3.5 标准正交基

2.6.1 节刻画了基向量的性质：在 n 维向量空间中，需要 n 个基向量，也就是 n 个线性无关的向量。3.3 节和 3.4 节利用内积计算了向量长度和夹角。下面讨论一种特殊情形：各基向量相互正交，且长度均为 1。这样的基称为标准正交基（orthonormal basis）。

下面给出更正式的定义。

**定义 3.9（标准正交基）。** 考虑 n 维向量空间 $V$，以及 $V$ 的一组基 $\{ b _ { 1 } , \ldots , b _ { n } \}$。如果

$$
\langle \boldsymbol {b} _ {i}, \boldsymbol {b} _ {j} \rangle = 0 \quad (i\neq j)\tag{3.33}
$$

$$
\langle \pmb {b} _ {i}, \pmb {b} _ {i} \rangle = 1\tag{3.34}
$$

对所有 $i , j = 1 , \ldots , n$ 成立，就称该基为标准正交基（ONB）。如果只满足式 (3.33)，就称为正交基（orthogonal basis）。注意，式 (3.34) 意味着每个基向量的长度或范数均为 1。

回顾 2.6.1 节，可以用高斯消元为一组向量张成的向量空间求一组基。假设给定一组尚未正交化、也未归一化的基向量 $\{ \tilde { b } _ { 1 } , \dots , \tilde { b } _ { n } \}$。将它们拼成矩阵 $\tilde { \pmb { B } } = [ \tilde { \pmb { b } } _ { 1 } , \dots , \tilde { \pmb { b } } _ { n } ]$，对增广矩阵 $[\tilde{\boldsymbol{B}}\tilde{\boldsymbol{B}}^{\top}\mid\tilde{\boldsymbol{B}}]$（见 2.3.2 节）进行高斯消元，以得到标准正交基。这种逐步构造标准正交基 $\{ b _ { 1 } , \ldots , b _ { n } \}$ 的方法称为 Gram–Schmidt 过程（Gram–Schmidt process；Strang，2003）。

> 译注：上段保留了原书表述。一般的高斯消元并不能保证所得向量正交且长度为 1；Gram–Schmidt 过程需要逐次减去沿已有正交方向的投影，再进行归一化。这里不能把两种过程直接等同。

**例 3.8（标准正交基）**

欧几里得向量空间 $\mathbb { R } ^ { n }$ 的典范基／标准基是一组标准正交基，这里内积采用向量的点积。

在 $\mathbb { R } ^ { 2 }$ 中，向量

$$
\boldsymbol {b} _ {1} = \frac {1}{\sqrt {2}} \left[ \begin{array}{c} 1 \\ 1 \end{array} \right], \quad \boldsymbol {b} _ {2} = \frac {1}{\sqrt {2}} \left[ \begin{array}{c} 1 \\ - 1 \end{array} \right]\tag{3.35}
$$

构成一组标准正交基，因为 $\pmb { b } _ { 1 } ^ { \top } \pmb { b } _ { 2 } = 0$，且 $\| \pmb { b } _ { 1 } \| = 1 = \| \pmb { b } _ { 2 } \|$。

第 12 章讨论支持向量机和第 10 章讨论主成分分析时，都将用到标准正交基的概念。

## 3.6 正交补

定义了正交性之后，下面考察彼此正交的向量空间。这将在第 10 章从几何角度讨论线性降维时发挥重要作用。

考虑 D 维向量空间 V 及其 M 维子空间 $U \subseteq V$。它的正交补（orthogonal complement）$U ^ { \perp }$ 是 $V$ 的 $( D - M )$ 维子空间，包含 $V$ 中与 U 的每个向量都正交的所有向量。此外，$U \cap U ^ { \bot } = \{ { \bf 0 } \}$，因此任意向量 $\pmb { x } \in V$ 都可以唯一分解为

$$
\boldsymbol {x} = \sum_ {m = 1} ^ {M} \lambda_ {m} \boldsymbol {b} _ {m} + \sum_ {j = 1} ^ {D - M} \psi_ {j} \boldsymbol {b} _ {j} ^ {\perp}, \quad \lambda_ {m}, \psi_ {j} \in \mathbb {R},\tag{3.36}
$$

其中，$\left( \pmb { b } _ { 1 } , \dots , \pmb { b } _ { M } \right)$ 是 $U$ 的一组基，$( \pmb { b } _ { 1 } ^ { \perp } , \ldots , \pmb { b } _ { D - M } ^ { \perp } )$ 是 $U ^ { \perp }$ 的一组基。

因此，也可以用正交补描述三维向量空间中的平面 $U$，即二维子空间。具体而言，与平面 $U$ 正交且满足 $\| \pmb { w } \| = 1$ 的向量 w，是 $U ^ { \perp }$ 的一个基向量。图 3.7 展示了这一情形。按构造，所有与 w 正交的向量都必须位于平面 $U$ 中。向量 w 称为 $U$ 的法向量（normal vector）。

图 3.7 三维向量空间中的平面 U 可以由其法向量描述，法向量张成它的正交补 $U ^ { \perp }$。

![图 3.7：平面与法向量](<Images/03_Analytic_Geometry_image_008.jpg>)

更一般地，正交补可以用来描述 n 维向量空间和仿射空间中的超平面。

## 3.7 函数的内积

前面利用内积的性质计算了长度、夹角和距离，重点是有限维向量的内积。下面介绍另一类向量的内积：函数的内积。

此前讨论的内积定义在分量个数有限的向量上。可以把向量 $\pmb { x } \in \mathbb { R } ^ { n }$ 看作具有 n 个函数值的函数。内积概念可以推广到具有无穷多个分量的向量，即可数无穷的情形，也可以推广到连续取值函数，即不可数无穷的情形。此时，对向量各分量求和，例如式 (3.5)，就变成了积分。

两个函数 $u:\mathbb{R}\to\mathbb{R}$ 和 $v:\mathbb{R}\to\mathbb{R}$ 的内积可以定义为定积分

$$
\langle u, v \rangle := \int_ {a} ^ {b} u (x) v (x) d x\tag{3.37}
$$

其中 $a , b < \infty$ 分别为积分下限和上限。与通常的内积一样，可以通过内积定义范数和正交性。如果式 (3.37) 的值为 0，函数 u、v 就正交。为了在数学上严格定义这一内积，需要处理测度与积分的定义，从而引出希尔伯特空间（Hilbert space）。此外，与有限维向量的内积不同，函数内积可能发散，即取无穷值。这涉及实分析和泛函分析中更深入的细节，本书不作讨论。

**例 3.9（函数的内积）**

取 $u = \sin ( x )$ 和 $v = \cos ( x )$，式 (3.37) 的被积函数 $f ( x ) = u ( x ) v ( x )$ 如图 3.8 所示。该函数是奇函数，即 $f ( - x ) = - f ( x )$，因此，在 $a = - \pi , b = \pi$ 为积分上下限时，这一乘积的积分为 0。所以，sin 与 cos 是正交函数。

![图 3.8：正弦与余弦的乘积](<Images/03_Analytic_Geometry_image_009.jpg>)

图 3.8 $f(x)=\sin(x)\cos(x)$。

**注。** 函数族

$$
\{1, \cos (x), \cos (2 x), \cos (3 x), \dots \}\tag{3.38}
$$

在从 $-\pi$ 到 $\pi$ 的积分下也正交，即任意两个不同的函数彼此正交。式 (3.38) 中的函数族张成了 $[ - \pi , \pi )$ 上偶周期函数的一个很大的子空间。将函数投影到该子空间，是傅里叶级数（Fourier series）的基本思想。

6.4.6 节将介绍另一种非常规内积：随机变量的内积。

## 3.8 正交投影

投影（projection）是除旋转和反射之外的一类重要线性变换，在图形学、编码理论、统计学和机器学习中都起重要作用。机器学习经常处理高维数据，而高维数据往往难以分析或可视化。不过，高维数据常常只有少数维度包含大部分信息，其余大多数维度并非描述数据关键性质所必需。压缩或可视化高维数据时会丢失信息。为了尽量减小压缩损失，理想情况下应找出数据中信息最丰富的维度。第 1 章讨论过，数据可以表示为向量，本章将介绍一些数据压缩的基本工具。具体来说，可以将原始高维数据投影到低维特征空间（feature space），并在低维空间中进一步了解数据集、提取相关模式。例如，Pearson（1901）和 Hotelling（1933）的主成分分析，以及深度神经网络（如深度自编码器，Deng et al.，2010），都大量利用了降维思想。下面重点讨论正交投影，第 10 章将用它进行线性降维，第 12 章将用它进行分类。第 9 章讨论的线性回归也可以用正交投影解释。对给定的低维子空间，高维数据的正交投影尽可能保留信息，并使原始数据与对应投影之间的差异或误差最小。图 3.9 展示了这种正交投影。在详细推导如何求投影之前，先定义什么是投影。

> “特征”（feature）是数据表示中的常用术语。

![图 3.9：数据集的正交投影](<Images/03_Analytic_Geometry_image_010.jpg>)

图 3.9 将二维数据集（蓝点）正交投影到一维子空间（直线），所得投影为橙点。

**定义 3.10（投影）。** 设 V 是向量空间，$U \subseteq V$ 是 V 的子空间。如果线性映射 $\pi:V\to U$ 满足 $\pi ^ { 2 } = \pi \circ \pi = \pi$，就称其为投影。

线性映射可以用变换矩阵表示，见 2.7 节，因此上述定义同样适用于一类特殊的变换矩阵，即投影矩阵（projection matrix）$P _ { \pi }$，它满足 $P _ { \pi } ^ { 2 } = P _ { \pi }$。

下面推导内积空间 $\left( \mathbb { R } ^ { n } , \langle \cdot , \cdot \rangle \right)$ 中向量到子空间的正交投影。先从一维子空间开始，这种子空间也称直线。如无特别说明，默认以点积 $\langle \pmb { x } , \pmb { y } \rangle = \pmb { x } ^ { \top } \pmb { y }$ 作为内积。

### 3.8.1 投影到一维子空间（直线）

假设给定一条经过原点的直线，即一维子空间，其基向量为 $b ~ \in ~ \mathbb { R } ^ { n }$。该直线是由 b 张成的一维子空间 $U \subseteq \mathbb { R } ^ { n }$。将 $\pmb { x } \in \mathbb { R } ^ { n }$ 投影到 $U$ 上时，寻找的是最接近 x 的向量 $\pi _ { U } ( { \pmb x } ) \in U$。下面用几何论证刻画投影 $\pi _ { U } ( { \pmb x } )$ 的一些性质，见图 3.10(a)：

- 投影 $\pi _ { U } ( { \pmb x } )$ 最接近 $\boldsymbol{x}$，其中“最接近”意味着距离 $\| { \pmb x } - \pi _ { U } ( { \pmb x } ) \|$ 最小。因此，连接 $\pi _ { U } ( { \pmb x } )$ 与 x 的线段 $\pi _ { U } ( { \pmb x } ) - { \pmb x }$ 与 $U$ 正交，也就与 $U$ 的基向量 b 正交。因为夹角通过内积定义，正交条件给出 $\langle \pi _ { U } ( { \pmb x } ) - { \pmb x } , { \pmb b } \rangle = 0$。

- x 到 $U$ 上的投影 $\pi _ { U } ( { \pmb x } )$ 必须属于 U，因此必为张成 U 的基向量 b 的倍数，即 $\pi _ { U } ( { \pmb x } ) = \lambda { \pmb b }$，其中 $\lambda \in \mathbb { R }$。

![图 3.10(a)：向直线投影](<Images/03_Analytic_Geometry_image_011.jpg>)

(a) 将 $\boldsymbol{x}\in\mathbb{R}^{2}$ 投影到以 b 为基向量的子空间 U。

![图 3.10(b)：单位向量的投影](<Images/03_Analytic_Geometry_image_012.jpg>)

图 3.10 投影到一维子空间的例子。

(b) 将满足 $\| \pmb { x } \| = 1$ 的二维向量 x 投影到由 b 张成的一维子空间。

> $\lambda$ 是 $\pi_U(\boldsymbol{x})$ 关于 $\boldsymbol{b}$ 的坐标。

下面分三步求出坐标 $\lambda$、投影 $\pi _ { U } ( { \pmb x } ) \in U$，以及将任意 $\mathbf { x } \in \mathbb { R } ^ { n }$ 映射到 $U$ 的投影矩阵 ${ \pmb P } _ { \pi }$：

**1.** 求坐标 $\lambda$。正交条件给出

$$
\langle \boldsymbol {x} - \pi_ {U} (\boldsymbol {x}), \boldsymbol {b} \rangle = 0 \stackrel {{\pi_ {U} (\boldsymbol {x}) = \lambda \boldsymbol {b}}} {{\Longleftrightarrow}} \langle \boldsymbol {x} - \lambda \boldsymbol {b}, \boldsymbol {b} \rangle = 0.\tag{3.39}
$$

利用内积的双线性性，得到

$$
\langle \boldsymbol {x}, \boldsymbol {b} \rangle - \lambda \langle \boldsymbol {b}, \boldsymbol {b} \rangle = 0 \iff \lambda = \frac {\langle \boldsymbol {x} , \boldsymbol {b} \rangle}{\langle \boldsymbol {b} , \boldsymbol {b} \rangle} = \frac {\langle \boldsymbol {b} , \boldsymbol {x} \rangle}{\| \boldsymbol {b} \| ^ {2}}.\tag{3.40}
$$

> 对一般内积，如果 $\|\boldsymbol{b}\|=1$，则有 $\lambda=\langle\boldsymbol{x},\boldsymbol{b}\rangle$。

最后一步利用了内积的对称性。如果选择 $\langle \cdot , \cdot \rangle$ 为点积，则得到

$$
\lambda = \frac {\boldsymbol {b} ^ {\top} \boldsymbol {x}}{\boldsymbol {b} ^ {\top} \boldsymbol {b}} = \frac {\boldsymbol {b} ^ {\top} \boldsymbol {x}}{\| \boldsymbol {b} \| ^ {2}}.\tag{3.41}
$$

如果 $\|\boldsymbol{b}\|=1$，投影的坐标 λ 就是 ${ \pmb b } ^ { \top } { \pmb x }$。

**2.** 求投影点 $\pi _ { U } ( { \pmb x } ) \in U$。由于 $\pi _ { U } ( { \pmb x } ) = \lambda { \pmb b }$，由式 (3.40) 立即得到

$$
\pi_ {U} (\boldsymbol {x}) = \lambda \boldsymbol {b} = \frac {\langle \boldsymbol {x} , \boldsymbol {b} \rangle}{\| \boldsymbol {b} \| ^ {2}} \boldsymbol {b} = \frac {\boldsymbol {b} ^ {\top} \boldsymbol {x}}{\| \boldsymbol {b} \| ^ {2}} \boldsymbol {b},\tag{3.42}
$$

最后一个等号仅对点积成立。还可以根据定义 3.1 计算 $\pi _ { U } ( { \pmb x } )$ 的长度：

$$
\left\| \pi_ {U} (\boldsymbol {x}) \right\| = \left\| \lambda \boldsymbol {b} \right\| = | \lambda | \| \boldsymbol {b} \|.\tag{3.43}
$$

因此，投影的长度为 b 长度的 $| \lambda |$ 倍。这也解释了为什么 λ 是 $\pi _ { U } ( { \pmb x } )$ 关于基向量 b 的坐标，b 张成了一维子空间 $U$。

如果采用点积作为内积，有

$$
\left\| \pi_ {U} (\boldsymbol {x}) \right\| \stackrel {(3.42)} {=} \frac {\left| \boldsymbol {b} ^ {\top} \boldsymbol {x} \right|}{\left\| \boldsymbol {b} \right\| ^ {2}} \left\| \boldsymbol {b} \right\| \stackrel {(3.25)} {=} | \cos \omega | \| \boldsymbol {x} \| \| \boldsymbol {b} \| \frac {\left\| \boldsymbol {b} \right\|}{\left\| \boldsymbol {b} \right\| ^ {2}} = | \cos \omega | \| \boldsymbol {x} \|.\tag{3.44}
$$

> 水平轴是一维子空间。

这里 ω 是 x 与 b 之间的夹角。这一公式与三角学中的结论一致：如果 $\|\boldsymbol{x}\|=1$，则 x 位于单位圆上。因此，在由 b 张成的水平轴上的投影坐标恰好为 cos ω，而对应向量的长度为 $\pi _ { U } ( { \pmb x } ) = | \cos { \omega } |$，见图 3.10(b)。

> 译注：原文在此处描述投影的长度，但公式左侧省略了范数符号；应区分投影向量、它的坐标与它的长度。

**3.** 求投影矩阵 ${ \pmb P } _ { \pi }$。投影是线性映射，见定义 3.10，因此存在矩阵 $P _ { \pi }$，使 $\pi _ { U } ( { \pmb x } ) = P _ { \pi } { \pmb x }$。采用点积作为内积，由

$$
\pi_ {U} (\boldsymbol {x}) = \lambda \boldsymbol {b} = \boldsymbol {b} \lambda = \boldsymbol {b} \frac {\boldsymbol {b} ^ {\top} \boldsymbol {x}}{\| \boldsymbol {b} \| ^ {2}} = \frac {\boldsymbol {b b} ^ {\top}}{\| \boldsymbol {b} \| ^ {2}} \boldsymbol {x},\tag{3.45}
$$

立即可得

$$
\boldsymbol {P} _ {\pi} = \frac {\boldsymbol {b b} ^ {\top}}{\| \boldsymbol {b} \| ^ {2}}.\tag{3.46}
$$

> 投影矩阵总是对称的。
>
> 译注：此句沿用原书边注，适用于本节标准点积下的正交投影矩阵；任意满足幂等性的投影矩阵不一定对称。

注意，$b b ^ { \top }$ 及相应的 $P_{\pi}$ 都是秩为 1 的对称矩阵，而 $\| \pmb { b } \| ^ { 2 } = \langle \pmb { b } , \pmb { b } \rangle$ 是标量。

投影矩阵 $P _ { \pi }$ 将任意向量 $\pmb { x } \in \mathbb { R } ^ { n }$ 投影到经过原点、以 b 为方向的直线上，等价地，就是投影到 b 张成的子空间 $U$ 上。

**注。** 投影 $\pi _ { U } ( \pmb { x } ) \in \mathbb { R } ^ { n }$ 仍是 n 维向量，而不是标量。不过，要表示这一投影不再需要 n 个坐标：如果采用张成子空间 $U$ 的基向量 b，只需一个坐标 $\lambda$。◇

![图 3.11：投影到二维子空间](<Images/03_Analytic_Geometry_image_013.jpg>)

图 3.11 投影到以 $b _ { 1 } , b _ { 2 }$ 为基的二维子空间 U。向量 x $\in \mathbb { R } ^ { 3 }$ 到 U 的投影 π_U(x) 可以表示为 $b _ { 1 } , b _ { 2 }$ 的线性组合，位移向量 ${ \pmb x } - \pi _ { U } ( { \pmb x } )$ 同时与 $\pmb { b } _ { 1 }$ 和 $b _ { 2 }$ 正交。

**例 3.10（投影到直线）**

求投影矩阵 ${ \pmb P } _ { \pi }$，将向量投影到经过原点、由 $\pmb { b } = \left[ 1 \quad 2 \quad 2 \right] ^ { \top }$ 张成的直线上。b 是该一维子空间的方向，也是一组基。

由式 (3.46)，得到

$$
\boldsymbol {P} _ {\pi} = \frac {\boldsymbol {b b} ^ {\top}}{\boldsymbol {b} ^ {\top} \boldsymbol {b}} = \frac {1}{9} \left[ \begin{array}{l} 1 \\ 2 \\ 2 \end{array} \right] \left[ \begin{array}{l l l} 1 & 2 & 2 \end{array} \right] = \frac {1}{9} \left[ \begin{array}{l l l} 1 & 2 & 2 \\ 2 & 4 & 4 \\ 2 & 4 & 4 \end{array} \right].\tag{3.47}
$$

现在选择具体的 x，考察它是否位于 b 张成的子空间中。对于 $\boldsymbol{x}=[1,1,1]^{\top}$，其投影为

$$
\pi_ {U} (\boldsymbol {x}) = \boldsymbol {P} _ {\pi} \boldsymbol {x} = \frac {1}{9} \left[ \begin{array}{c c c} 1 & 2 & 2 \\ 2 & 4 & 4 \\ 2 & 4 & 4 \end{array} \right] \left[ \begin{array}{c} 1 \\ 1 \\ 1 \end{array} \right] = \frac {1}{9} \left[ \begin{array}{c} 5 \\ 10 \\ 10 \end{array} \right] \in \operatorname{span} [ \left[ \begin{array}{c} 1 \\ 2 \\ 2 \end{array} \right] ].\tag{3.48}
$$

注意，对 $\pi _ { U } ( { \pmb x } )$ 再施加 $P _ { \pi }$ 不会改变结果，即 $\pmb { P } _ { \pi } \pi _ { U } ( \pmb { x } ) = \pi _ { U } ( \pmb { x } )$。这符合预期，因为根据定义 3.10，投影矩阵 ${ \pmb P } _ { \pi }$ 对所有 x 都满足 $\boldsymbol { P } _ { \pi } ^ { 2 } \boldsymbol { x } = \boldsymbol { P } _ { \pi } \boldsymbol { x }$。

**注。** 利用第 4 章的结果，可以证明 $\pi _ { U } ( { \pmb x } )$ 是 $P_{\pi}$ 的特征向量（eigenvector），对应特征值（eigenvalue）为 1。

### 3.8.2 投影到一般子空间

下面讨论将向量 $\pmb { x } \in \mathbb { R } ^ { n }$ 正交投影到低维子空间 $U \subseteq \mathbb { R } ^ { n }$ 上，其中 $\dim ( U ) = m \geqslant 1$。图 3.11 给出了示意。

设 $\left( b _ { 1 } , \ldots , b _ { m } \right)$ 是 U 的有序基。到 U 上的任意投影 $\pi _ { U } ( { \pmb x } )$ 必然属于 U，因此可表示为 $U$ 的基向量 $b _ { 1 } , \ldots , b _ { m }$ 的线性组合，即 $\begin{array} { r } { \pi _ { U } ( { \pmb x } ) = \sum _ { i = 1 } ^ { m } \lambda _ { i } \pmb { b } _ { i } } \end{array}$。

> 如果给出的只是 U 的一组张成向量，而不是基，应先确定一组基 $\pmb { b } _ { 1 } , \dots , \pmb { b } _ { m }$，再继续。

> 基向量构成矩阵 $B\in\mathbb{R}^{n\times m}$ 的各列，其中 $B=[\boldsymbol{b}_1,\ldots,\boldsymbol{b}_m]$。

与一维情形一样，分三步求投影 $\pi _ { U } ( { \pmb x } )$ 和投影矩阵 $P _ { \pi }$：

**1.** 求投影关于 U 的基的坐标 $\lambda _ { 1 } , \ldots , \lambda _ { m }$，使线性组合

$$
\pi_ {U} (\boldsymbol {x}) = \sum_ {i = 1} ^ {m} \lambda_ {i} \boldsymbol {b} _ {i} = B \boldsymbol {\lambda},\tag{3.49}
$$

$$
\boldsymbol {B} = \left[ \boldsymbol {b} _ {1}, \dots , \boldsymbol {b} _ {m} \right] \in \mathbb {R} ^ {n \times m}, \quad \boldsymbol {\lambda} = \left[ \lambda_ {1}, \dots , \lambda_ {m} \right] ^ {\top} \in \mathbb {R} ^ {m},\tag{3.50}
$$

最接近 $\pmb { x } \in \mathbb { R } ^ { n }$。与一维情形相同，“最接近”指距离最小，因此连接 $\pi _ { U } ( \pmb { x } ) \in U$ 与 $\pmb { x } \in \mathbb { R } ^ { n }$ 的向量必须与 $U$ 的所有基向量正交。采用点积作为内积，得到 m 个同时成立的条件：

$$
\langle \pmb {b} _ {1}, \pmb {x} - \pi_ {U} (\pmb {x}) \rangle = \pmb {b} _ {1} ^ {\top} (\pmb {x} - \pi_ {U} (\pmb {x})) = 0\tag{3.51}
$$

$$
\vdots
$$

$$
\langle \pmb {b} _ {m}, \pmb {x} - \pi_ {U} (\pmb {x}) \rangle = \pmb {b} _ {m} ^ {\top} (\pmb {x} - \pi_ {U} (\pmb {x})) = 0\tag{3.52}
$$

结合 $\pi _ { U } ( { \pmb x } ) = B \lambda$，可写成

$$
\boldsymbol {b} _ {1} ^ {\top} (\boldsymbol {x} - \boldsymbol {B} \boldsymbol {\lambda}) = 0\tag{3.53}
$$

$$
\begin{array}{c} \vdots \\ \boldsymbol {b} _ {m} ^ {\top} (\boldsymbol {x} - \boldsymbol {B} \boldsymbol {\lambda}) = 0 \end{array}\tag{3.54}
$$

由此得到齐次线性方程组

$$
\left[ \begin{array}{c} \boldsymbol {b} _ {1} ^ {\top} \\ \vdots \\ \boldsymbol {b} _ {m} ^ {\top} \end{array} \right] \left[ \begin{array}{c} \boldsymbol {x} - \boldsymbol {B} \boldsymbol {\lambda} \end{array} \right] = \mathbf {0} \iff \boldsymbol {B} ^ {\top} (\boldsymbol {x} - \boldsymbol {B} \boldsymbol {\lambda}) = \mathbf {0}\tag{3.55}
$$

$$
\Longleftrightarrow \boldsymbol {B} ^ {\top} \boldsymbol {B} \lambda = \boldsymbol {B} ^ {\top} \boldsymbol {x}.\tag{3.56}
$$

最后一个表达式称为正规方程（normal equation）。由于 $\pmb { b } _ { 1 } , \dots , \pmb { b } _ { m }$ 是 $U$ 的基，所以它们线性无关，$\boldsymbol { B } ^ { \intercal } \boldsymbol { B } \in \mathbb { R } ^ { m \times m }$ 正则且可逆。因此可以求得系数或坐标

$$
\boldsymbol {\lambda} = \left(\boldsymbol {B} ^ {\top} \boldsymbol {B}\right) ^ {- 1} \boldsymbol {B} ^ {\top} \boldsymbol {x}.\tag{3.57}
$$

矩阵 $( B ^ { \top } B ) ^ { - 1 } B ^ { \top }$ 也称为 $B$ 的伪逆（pseudo-inverse），非方阵 B 也可以计算这种伪逆。它只要求 $B ^ { \top } B$ 正定，在这里 B 满秩即可满足这一条件。实际应用中，例如线性回归，常向 $B ^ { \top } B$ 加入微小扰动项 ϵI，以提高数值稳定性并保证正定性。这种“岭”（ridge）可以通过贝叶斯推断严格推导，详见第 9 章。

> 译注：加入正则项会改变解，一般不再得到严格的正交投影；原文此处转而说明实际计算中的正则化做法。

**2.** 求投影 $\pi _ { U } ( { \pmb x } ) \in U$。前面已知 $\pi_U(\boldsymbol{x})=B\boldsymbol{\lambda}$，因此由式 (3.57) 得到

$$
\pi_ {U} (\boldsymbol {x}) = \boldsymbol {B} (\boldsymbol {B} ^ {\top} \boldsymbol {B}) ^ {- 1} \boldsymbol {B} ^ {\top} \boldsymbol {x}.\tag{3.58}
$$

**3.** 求投影矩阵 ${ \pmb P } _ { \pi }$。由式 (3.58) 立即可见，满足 $\pmb { P } _ { \pi } \pmb { x } = \pi _ { U } ( \pmb { x } )$ 的投影矩阵必为

$$
\boldsymbol {P} _ {\pi} = \boldsymbol {B} (\boldsymbol {B} ^ {\top} \boldsymbol {B}) ^ {- 1} \boldsymbol {B} ^ {\top}.\tag{3.59}
$$

**注。** 一般子空间投影的解包含一维情形：如果 $\dim(U)=1$，那么 $B ^ { \top } B \in \mathbb { R }$ 是标量，式 (3.59) 的投影矩阵 $\begin{array} { r } { \pmb { P } _ { \pi } = \pmb { B } ( \pmb { B } ^ { \top } \pmb { B } ) ^ { - 1 } \pmb { B } ^ { \top } } \end{array}$ 可以改写为 $\begin{array} { r } { { P } _ { \pi } = \frac { B B ^ { \top } } { B ^ { \top } B } } \end{array}$，恰好就是式 (3.46)。◇

**例 3.11（投影到二维子空间）**

给定子空间 $U=\operatorname{span}\left[\begin{bmatrix}1\\1\\1\end{bmatrix},\begin{bmatrix}0\\1\\2\end{bmatrix}\right]\subseteq\mathbb{R}^{3}$ 及 $\boldsymbol{x}=\begin{bmatrix}6\\0\\0\end{bmatrix}\in\mathbb{R}^{3}$，求 x 在子空间 $U$ 中对应的坐标 $\boldsymbol{\lambda}$、投影点 $\pi_U(\boldsymbol{x})$ 和投影矩阵 $P_{\pi}$。

> 译注：这里的坐标指投影点关于所给子空间基的坐标，原向量 x 本身不一定属于该子空间。

第一步，确认 $U$ 的生成集是一组基，因为这些向量线性无关；将 U 的基向量写成矩阵 $\boldsymbol{B} = \left[ \begin{array} { l l } { 1 } & { 0 } \\ { 1 } & { 1 } \\ { 1 } & { 2 } \end{array} \right]$。

第二步，计算矩阵 $B ^ { \top } B$ 和向量 $B^{\top}\boldsymbol{x}$：

$$
\boldsymbol {B} ^ {\top} \boldsymbol {B} = \left[ \begin{array}{c c c} 1 & 1 & 1 \\ 0 & 1 & 2 \end{array} \right] \left[ \begin{array}{c c} 1 & 0 \\ 1 & 1 \\ 1 & 2 \end{array} \right] = \left[ \begin{array}{c c} 3 & 3 \\ 3 & 5 \end{array} \right], \quad \boldsymbol {B} ^ {\top} \boldsymbol {x} = \left[ \begin{array}{c c c} 1 & 1 & 1 \\ 0 & 1 & 2 \end{array} \right] \left[ \begin{array}{c} 6 \\ 0 \\ 0 \end{array} \right] = \left[ \begin{array}{c} 6 \\ 0 \end{array} \right].\tag{3.60}
$$

第三步，求解正规方程 $B^{\top}B\boldsymbol{\lambda}=B^{\top}\boldsymbol{x}$，得到 λ：

$$
\left[ \begin{array}{c c} 3 & 3 \\ 3 & 5 \end{array} \right] \left[ \begin{array}{c} \lambda_ {1} \\ \lambda_ {2} \end{array} \right] = \left[ \begin{array}{c} 6 \\ 0 \end{array} \right] \iff \boldsymbol {\lambda} = \left[ \begin{array}{c} 5 \\ - 3 \end{array} \right].\tag{3.61}
$$

第四步，x 到 $U$ 上的投影 $\pi _ { U } ( { \pmb x } )$，也就是到 $B$ 列空间上的投影，可直接计算为

$$
\pi_ {U} (\boldsymbol {x}) = \boldsymbol {B} \boldsymbol {\lambda} = \left[ \begin{array}{c} 5 \\ 2 \\ - 1 \end{array} \right].\tag{3.62}
$$

> 投影误差也称重构误差（reconstruction error）。

相应的投影误差是原向量与其在 U 上投影的差向量的范数，即

$$
\left\| \boldsymbol {x} - \pi_ {U} (\boldsymbol {x}) \right\| = \left\| \left[ \begin{array}{c c c} 1 & - 2 & 1 \end{array} \right] ^ {\top} \right\| = \sqrt {6}.\tag{3.63}
$$

第五步，对任意 $\pmb { x } \in \mathbb { R } ^ { 3 }$，投影矩阵为

$$
\boldsymbol {P} _ {\pi} = \boldsymbol {B} (\boldsymbol {B} ^ {\top} \boldsymbol {B}) ^ {- 1} \boldsymbol {B} ^ {\top} = \frac {1}{6} \left[ \begin{array}{c c c} 5 & 2 & - 1 \\ 2 & 2 & 2 \\ - 1 & 2 & 5 \end{array} \right].\tag{3.64}
$$

可以用两种方式验证结果：(a) 检查位移向量 $\pi _ { U } ( { \pmb x } ) - { \pmb x }$ 是否与 U 的所有基向量正交；(b) 验证 $P _ { \pi } = P _ { \pi } ^ { 2 }$，见定义 3.10。

**注。** 投影 $\pi _ { U } ( { \pmb x } )$ 虽然位于 m 维子空间 $U \subseteq \mathbb { R } ^ { n }$ 中，但仍是 $\mathbb{R}^{n}$ 中的向量。不过，表示投影向量只需它关于 $U$ 的基向量 $\pmb { b } _ { 1 } , \dots , \pmb { b } _ { m }$ 的 m 个坐标 $\lambda _ { 1 } , \ldots , \lambda _ { m }$。◇

**注。** 在具有一般内积的向量空间中，计算夹角和距离时应注意，它们都是通过所选内积定义的。

> 利用投影，可以为无解的线性方程组寻找近似解。

投影还可以处理线性方程组 Ax＝b 无解的情形。回顾一下，无解意味着 b 不在 A 的张成空间中，也就是不属于 A 的各列所张成的子空间。无法精确求解时，可以寻找近似解：在 A 的列空间中找到最接近 b 的向量，即将 b 正交投影到该子空间。这个问题在实际中经常出现，所得解称为超定方程组的最小二乘解（least-squares solution），这里假设采用点积作为内积。9.4 节将进一步讨论。利用重构误差 (3.63)，也是推导主成分分析的一种途径，见 10.3 节。

**注。** 前面讨论了将向量 x 投影到以 $\{ b _ { 1 } , \ldots , b _ { k } \}$ 为基的子空间 U。如果该基是标准正交基，即满足式 (3.33) 和式 (3.34)，投影公式 (3.58) 将大幅简化为

$$
\pi_ {U} (\pmb {x}) = \pmb {B B} ^ {\top} \pmb {x}\tag{3.65}
$$

因为 $B ^ { \top } B = I$，其坐标为

$$
\boldsymbol {\lambda} = \boldsymbol {B} ^ {\top} \boldsymbol {x}.\tag{3.66}
$$

这意味着不再需要计算式 (3.58) 中的逆矩阵，从而节省计算时间。◇

### 3.8.3 Gram–Schmidt 正交化

投影是 Gram–Schmidt 方法的核心。该方法可以构造性地将 n 维向量空间 $V$ 的任意一组基 $\left( b _ { 1 } , \ldots , b _ { n } \right)$ 转换为 $V$ 的正交基或标准正交基 $( \pmb { u } _ { 1 } , \dots , \pmb { u } _ { n } )$。这样的基总是存在（Liesen and Mehrmann，2015），而且 $\operatorname{span}[\boldsymbol{b}_1,\ldots,\boldsymbol{b}_n]=\operatorname{span}[\boldsymbol{u}_1,\ldots,\boldsymbol{u}_n]$。Gram–Schmidt 正交化从 V 的任意基 $\left( b _ { 1 } , \ldots , b _ { n } \right)$ 出发，按如下方式迭代构造正交基 $\left( \pmb { u } _ { 1 } , \dots , \pmb { u } _ { n } \right)$：

$$
\boldsymbol {u} _ {1} := \boldsymbol {b} _ {1}\tag{3.67}
$$

$$
\boldsymbol {u} _ {k} := \boldsymbol {b} _ {k} - \pi_ {\text { span } [ \boldsymbol {u} _ {1}, \dots , \boldsymbol {u} _ {k - 1} ]} (\boldsymbol {b} _ {k}), \quad k = 2, \dots , n.\tag{3.68}
$$

在式 (3.68) 中，将第 k 个基向量 $\boldsymbol{b}_k$ 投影到已经构造出的前 $k - 1$ 个正交向量 $u _ { 1 } , \ldots , u _ { k - 1 }$ 所张成的子空间，见 3.8.2 节。再从 $b _ { k }$ 中减去这一投影，得到向量 $\boldsymbol{u}_k$，它与 $\pmb { u } _ { 1 } , \ldots , \pmb { u } _ { k - 1 }$ 张成的 $( k - 1 )$ 维子空间正交。对全部 n 个基向量 $b _ { 1 } , \ldots , b _ { n }$ 重复此过程，就得到 $V$ 的正交基 $\left( \pmb { u } _ { 1 } , \dots , \pmb { u } _ { n } \right)$。将 $\boldsymbol{u}_k$ 归一化，则得到标准正交基，满足对 $k = 1 , \dots , n$ 均有 $\| \boldsymbol { u } _ { k } \| = 1$。

**例 3.12（Gram–Schmidt 正交化）**

![图 3.12(a)：原始基](<Images/03_Analytic_Geometry_image_014.jpg>)

(a) 原始的非正交基向量 $\boldsymbol{b}_1,\boldsymbol{b}_2$。

![图 3.12(b)：第一个新基向量](<Images/03_Analytic_Geometry_image_015.jpg>)

(b) 第一个新基向量 $\boldsymbol{u}_1=\boldsymbol{b}_1$，以及 $\boldsymbol{b}_2$ 到 $\boldsymbol{u}_1$ 张成子空间上的投影。

![图 3.12(c)：正交基](<Images/03_Analytic_Geometry_image_016.jpg>)

(c) 正交基向量 $\boldsymbol{u}_1$ 和 $\boldsymbol{u}_2=\boldsymbol{b}_2-\pi_{\operatorname{span}[\boldsymbol{u}_1]}(\boldsymbol{b}_2)$。

图 3.12 Gram–Schmidt 正交化。(a) $\mathbb { R } ^ { 2 }$ 中的非正交基 $( b _ { 1 } , b _ { 2 } )$；(b) 首先构造的基向量 ${ \pmb u } _ { 1 }$，以及 $\pmb { b } _ { 2 }$ 到 span $[ { \pmb u } _ { 1 } ]$ 上的正交投影；(c) $\mathbb { R } ^ { 2 }$ 的正交基 $( \mathbf { \boldsymbol { u } } _ { 1 } , \mathbf { \boldsymbol { u } } _ { 2 } )$。

考虑 $\mathbb { R } ^ { 2 }$ 的一组基 $( b _ { 1 } , b _ { 2 } )$，其中

$$
\boldsymbol {b} _ {1} = \left[ \begin{array}{c} 2 \\ 0 \end{array} \right], \quad \boldsymbol {b} _ {2} = \left[ \begin{array}{c} 1 \\ 1 \end{array} \right];\tag{3.69}
$$

另见图 3.12(a)。采用点积作为内积，使用 Gram–Schmidt 方法按如下步骤构造 $\mathbb { R } ^ { 2 }$ 的正交基 $( \pmb { u } _ { 1 } , \pmb { u } _ { 2 } )$：

$$
\boldsymbol {u} _ {1} := \boldsymbol {b} _ {1} = \left[ \begin{array}{c} 2 \\ 0 \end{array} \right],\tag{3.70}
$$

$$
\boldsymbol {u} _ {2} := \boldsymbol {b} _ {2} - \pi_ {\text {span} [ \boldsymbol {u} _ {1} ]} (\boldsymbol {b} _ {2}) \stackrel {(3.45)} {=} \boldsymbol {b} _ {2} - \frac {\boldsymbol {u} _ {1} \boldsymbol {u} _ {1} ^ {\top}}{\| \boldsymbol {u} _ {1} \| ^ {2}} \boldsymbol {b} _ {2} = \left[ \begin{array}{c} 1 \\ 1 \end{array} \right] - \left[ \begin{array}{c c} 1 & 0 \\ 0 & 0 \end{array} \right] \left[ \begin{array}{c} 1 \\ 1 \end{array} \right] = \left[ \begin{array}{c} 0 \\ 1 \end{array} \right].\tag{3.71}
$$

图 3.12(b)、(c) 展示了这些步骤。可以直接看到，$\boldsymbol{u}_1$ 与 ${ \bf { u } } _ { 2 }$ 正交，即 $\pmb { u } _ { 1 } ^ { \top } \pmb { u } _ { 2 } = 0$。

### 3.8.4 投影到仿射子空间

图 3.13 投影到仿射空间。(a) 原始情形；(b) 将整个问题平移 −x₀，使 x−x₀ 能投影到方向空间 U；(c) 将投影平移回 x₀＋π_U(x−x₀)，得到最终的正交投影 $\pi _ { L } ( { \pmb x } )$。

![图 3.13：平移、投影与平移回原空间](<Images/03_Analytic_Geometry_Figure_3_13.png>)

(a) 原始情形。

(b) 将问题转化为向量子空间上的投影 π_U。

(c) 加回支撑点，得到仿射投影 $\pi _ { L }$。

前面讨论了如何将向量投影到低维子空间 U。下面给出将向量投影到仿射子空间的方法。

考虑图 3.13(a) 的情形。给定仿射空间 $L =$ $x _ { 0 } + U$，其中 $b _ { 1 } , b _ { 2 }$ 是 $U$ 的基向量。为求 x 到 $L$ 上的正交投影 $\pi _ { L } ( \pmb { x } )$，先将问题转换为已知的向量子空间投影问题。具体做法是从 x 和 $L$ 中减去支撑点 $\boldsymbol{x}_0$，使 $L - x _ { 0 } = U$ 恰为向量子空间 $U$。现在可以使用 3.8.2 节的方法，得到投影 $\pi _ { U } ( \pmb { x } - \pmb { x } _ { 0 } )$，见图 3.13(b)。再加回 $\boldsymbol{x}_0$，将这一投影平移回 L，便得到仿射空间 $L$ 上的正交投影：

$$
\pi_ {L} (\boldsymbol {x}) = \boldsymbol {x} _ {0} + \pi_ {U} (\boldsymbol {x} - \boldsymbol {x} _ {0}),\tag{3.72}
$$

其中 $\pi _ { U } ( \cdot )$ 表示到子空间 $U$，即 $L$ 的方向空间上的正交投影，见图 3.13(c)。

由图 3.13 也可以看出，x 到仿射空间 $L$ 的距离，与 $\boldsymbol{x}-\boldsymbol{x}_0$ 到 U 的距离相同，即

$$
d (\boldsymbol {x}, L) = \left\| \boldsymbol {x} - \pi_ {L} (\boldsymbol {x}) \right\| = \left\| \boldsymbol {x} - \left(\boldsymbol {x} _ {0} + \pi_ {U} (\boldsymbol {x} - \boldsymbol {x} _ {0})\right) \right\|\tag{3.73a}
$$

$$
= d (\boldsymbol {x} - \boldsymbol {x} _ {0}, \pi_ {U} (\boldsymbol {x} - \boldsymbol {x} _ {0})) = d (\boldsymbol {x} - \boldsymbol {x} _ {0}, U).\tag{3.73b}
$$

12.1 节将利用仿射子空间上的投影推导分离超平面（separating hyperplane）的概念。

## 3.9 旋转

![图 3.14：平面旋转](<Images/03_Analytic_Geometry_image_018.jpg>)

图 3.14 旋转使平面中的对象绕原点转动。旋转角为正时，沿逆时针方向旋转。图内 Original 表示原始状态，Rotated by 112.5° 表示旋转 112.5° 后的状态。

![图 3.15：机械臂](<Images/03_Analytic_Geometry_image_019.jpg>)

图 3.15 机械臂需要转动关节，才能抓取物体或把物体正确放置。图片取自 Deisenroth et al.（2015）。

3.4 节讨论过，保持长度和夹角，是具有正交变换矩阵的线性映射的两项特征。下面进一步考察描述旋转的特定正交变换矩阵。

旋转（rotation）是一种线性映射，更具体地说，是欧几里得向量空间的自同构，它使平面绕原点转过角度 θ，因此原点保持不动。按通常约定，正角 $\theta>0$ 对应逆时针旋转。图 3.14 给出一个例子，其变换矩阵为

$$
\boldsymbol {R} = \left[ \begin{array}{c c} - 0.38 & - 0.92 \\ 0.92 & - 0.38 \end{array} \right].\tag{3.74}
$$

旋转的重要应用包括计算机图形学和机器人学。例如，机器人学中经常需要确定机械臂关节应如何转动，以抓取或放置物体，见图 3.15。

图 3.16 将 $\mathbb { R } ^ { 2 }$ 中的标准基旋转角度 θ。

![图 3.16：标准基的旋转](<Images/03_Analytic_Geometry_image_020.jpg>)

### 3.9.1 二维空间中的旋转

考虑 $\mathbb { R } ^ { 2 }$ 的标准基 $\{\boldsymbol{e}_1=[1,0]^{\top},\boldsymbol{e}_2=[0,1]^{\top}\}$，它定义了 $\mathbb { R } ^ { 2 }$ 中的标准坐标系。目标是将该坐标系旋转角度 θ，见图 3.16。旋转后的向量仍然线性无关，因此仍是 $\mathbb { R } ^ { 2 }$ 的一组基。这意味着旋转执行了一次基变换。

旋转 Φ 是线性映射，因此可用旋转矩阵（rotation matrix）$R ( \theta )$ 表示。利用三角学，见图 3.16，可以求出旋转后坐标轴，也就是 Φ 的像，关于 $\mathbb { R } ^ { 2 }$ 标准基的坐标。得到

$$
\Phi (\boldsymbol {e} _ {1}) = \left[ \begin{array}{c} \cos \theta \\ \sin \theta \end{array} \right], \quad \Phi (\boldsymbol {e} _ {2}) = \left[ \begin{array}{c} - \sin \theta \\ \cos \theta \end{array} \right].\tag{3.75}
$$

因此，执行这一旋转基变换的矩阵 $R ( \theta )$ 为

$$
\boldsymbol {R} (\theta) = \left[ \begin{array}{c c} \Phi (\boldsymbol {e} _ {1}) & \Phi (\boldsymbol {e} _ {2}) \end{array} \right] = \left[ \begin{array}{c c} \cos \theta & - \sin \theta \\ \sin \theta & \cos \theta \end{array} \right].\tag{3.76}
$$

### 3.9.2 三维空间中的旋转

与 $\mathbb { R } ^ { 2 }$ 的情形不同，在 $\mathbb { R } ^ { 3 }$ 中可以让任意二维平面绕一维轴旋转。指定一般旋转矩阵的最直接方式，是指定标准基 $e _ { 1 } , e _ { 2 } , e _ { 3 }$ 的像应如何旋转，并确保这些像 $R e _ { 1 } , R e _ { 2 } , R e _ { 3 }$ 彼此标准正交。再将标准基的像组合起来，就得到旋转矩阵 R。

要使旋转角有明确意义，必须定义高于二维时“逆时针”的含义。这里约定，绕某轴的“逆时针”平面旋转，是从该轴末端朝原点迎面观察时所见的旋转方向。在 $\mathbb { R } ^ { 3 }$ 中，分别绕三个标准基向量所在轴的平面旋转如下，见图 3.17：

![图 3.17：三维旋转](<Images/03_Analytic_Geometry_image_021.jpg>)

图 3.17 将三维空间中的向量（灰色）绕 e₃ 轴旋转角度 θ，旋转后的向量以蓝色表示。

- 绕 $e _ { 1 }$ 轴旋转：

$$
\boldsymbol {R} _ {1} (\theta) = \left[ \begin{array}{c c c} \Phi (\boldsymbol {e} _ {1}) & \Phi (\boldsymbol {e} _ {2}) & \Phi (\boldsymbol {e} _ {3}) \end{array} \right] = \left[ \begin{array}{c c c} 1 & 0 & 0 \\ 0 & \cos \theta & - \sin \theta \\ 0 & \sin \theta & \cos \theta \end{array} \right].\tag{3.77}
$$

此时 $e _ { 1 }$ 坐标固定，在 $e _ { 2 } e _ { 3 }$ 平面内作逆时针旋转。

- 绕 $e_2$ 轴旋转：

$$
\boldsymbol {R} _ {2} (\theta) = \left[ \begin{array}{c c c} \cos \theta & 0 & \sin \theta \\ 0 & 1 & 0 \\ - \sin \theta & 0 & \cos \theta \end{array} \right].\tag{3.78}
$$

将 $e _ { 1 } e _ { 3 }$ 平面绕 $e _ { 2 }$ 轴旋转时，需要从 $e _ { 2 }$ 轴的端点朝原点观察。

- 绕 $e _ { 3 }$ 轴旋转：

$$
\boldsymbol {R} _ {3} (\theta) = \left[ \begin{array}{c c c} \cos \theta & - \sin \theta & 0 \\ \sin \theta & \cos \theta & 0 \\ 0 & 0 & 1 \end{array} \right].\tag{3.79}
$$

图 3.17 展示了这一情形。

### 3.9.3 n 维空间中的旋转

将二维、三维旋转推广到 n 维欧几里得向量空间，可以直观地理解为：固定 $n - 2$ 个维度，将旋转限制在 n 维空间的一个二维平面内。与三维情形一样，可以旋转任意平面，即 $\mathbb{R}^{n}$ 的二维子空间。

**定义 3.11（Givens 旋转）。** 设 V 是 n 维欧几里得向量空间，$\Phi:V\to V$ 是自同构，其变换矩阵为

$$
\boldsymbol {R} _ {i j} (\theta) := \left[ \begin{array}{c c c c c} \boldsymbol {I} _ {i - 1} & \boldsymbol {0} & \dots & \dots & \boldsymbol {0} \\ \boldsymbol {0} & \cos \theta & \boldsymbol {0} & - \sin \theta & \boldsymbol {0} \\ \boldsymbol {0} & \boldsymbol {0} & \boldsymbol {I} _ {j - i - 1} & \boldsymbol {0} & \boldsymbol {0} \\ \boldsymbol {0} & \sin \theta & \boldsymbol {0} & \cos \theta & \boldsymbol {0} \\ \boldsymbol {0} & \dots & \dots & \boldsymbol {0} & \boldsymbol {I} _ {n - j} \end{array} \right] \in \mathbb {R} ^ {n \times n},\tag{3.80}
$$

其中 $1\leqslant i<j\leqslant n$，$\theta\in\mathbb{R}$。称 $R _ { i j } ( \theta )$ 为 Givens 旋转（Givens rotation）。本质上，$R _ { i j } ( \theta )$ 就是将单位矩阵 $\scriptstyle { { \cal { I } } _ { n } }$ 中的以下元素替换后得到的矩阵：

$$
r _ {i i} = \cos \theta , r _ {i j} = - \sin \theta , r _ {j i} = \sin \theta , r _ {j j} = \cos \theta .\tag{3.81}
$$

在二维情形，即 $n=2$ 时，式 (3.76) 是其特例。

### 3.9.4 旋转的性质

将旋转视为正交矩阵，见定义 3.8，可以推导出以下有用性质：

- 旋转保持距离，即 $\| x - y \| = \| R _ { \theta } ( { \pmb x } ) - { \pmb R } _ { \theta } ( \pmb y ) \|$。换言之，旋转变换不改变任意两点之间的距离。

- 旋转保持夹角，即 $\scriptstyle { R _ { \theta } } x$ 与 $\scriptstyle R _ { \theta } { \boldsymbol { y } }$ 之间的夹角，等于 x 与 $\boldsymbol{y}$ 之间的夹角。

- 三维或更高维空间中的旋转一般不满足交换律。因此，即使绕同一点旋转，施加旋转的顺序也很重要。二维向量旋转满足交换律，即对所有 $\phi , \theta \in [ 0 , 2 \pi )$，都有 $R ( \phi ) R ( \theta ) = R ( \theta ) R ( \phi )$。只有当它们绕同一点旋转，例如原点时，才在乘法下构成阿贝尔群。

## 3.10 延伸阅读

本章简要介绍了解析几何中的一些重要概念，后续章节将用到它们。若希望更全面、深入地了解这些概念，可参阅 Axler（2015）和 Boyd and Vandenberghe（2018）的优秀著作。

利用内积和 Gram–Schmidt 方法，可以为向量空间或子空间确定特定的基，使每个向量都与其余向量正交，即正交基。这类基在优化和线性方程组的数值求解算法中非常重要。例如，Krylov 子空间方法，包括共轭梯度法和广义极小残量法（GMRES），会最小化相互正交的残差误差（Stoer and Burlirsch，2002）。

在机器学习中，内积对核方法（kernel methods）十分重要（Schölkopf and Smola，2002）。核方法利用了这样一个事实：许多线性算法可以完全用内积计算表示。借助“核技巧”（kernel trick），可以在可能为无限维的特征空间中隐式计算这些内积，甚至不需要显式知道这个特征空间。这使许多机器学习算法得以“非线性化”，例如用于降维的核主成分分析（kernel-PCA；Schölkopf et al.，1997）。高斯过程（Gaussian processes；Rasmussen and Williams，2006）也属于核方法，原书将其描述为当时概率回归，即对数据点拟合曲线的前沿方法。第 12 章将进一步讨论核的思想。

投影常用于计算机图形学，例如生成阴影。在优化中，正交投影常用于迭代地最小化残差误差。这也应用于机器学习，例如在线性回归中寻找使残差误差最小的线性函数；原文将此描述为数据到线性函数上的正交投影的长度（Bishop，2006）。第 9 章将进一步讨论。PCA（Pearson，1901；Hotelling，1933）也利用投影降低高维数据的维数，第 10 章将详细介绍。

> 译注：最后一段对残差长度的表述沿用原文。应区分投影向量的长度与原向量减去投影后所得残差的长度；最小二乘最小化的是后者。

## 习题

**3.1.** 对所有 $\pmb { x } = [ x _ { 1 } , x _ { 2 } ] ^ { \top } \in \mathbb { R } ^ { 2 }$ 和 $\pmb { y } = [ y _ { 1 } , y _ { 2 } ] ^ { \top } \in \mathbb { R } ^ { 2 }$，通过下式定义 $\langle \cdot , \cdot \rangle$：

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle := x _ {1} y _ {1} - (x _ {1} y _ {2} + x _ {2} y _ {1}) + 2 (x _ {2} y _ {2})
$$

证明它是一个内积。

**3.2.** 考虑 $\mathbb { R } ^ { 2 }$，对 $\mathbb { R } ^ { 2 }$ 中所有 x 和 $\pmb { y }$，定义 $\langle \cdot , \cdot \rangle$ 为

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle := \boldsymbol {x} ^ {\top} \underbrace {\left[ \begin{array}{c c} 2 & 0 \\ 1 & 2 \end{array} \right]} _ {=: \boldsymbol {A}} \boldsymbol {y}.
$$

$\langle \cdot , \cdot \rangle$ 是否为内积？

**3.3.** 计算下列两向量之间的距离：

$$
\boldsymbol {x} = \left[ \begin{array}{c} 1 \\ 2 \\ 3 \end{array} \right], \quad \boldsymbol {y} = \left[ \begin{array}{c} - 1 \\ - 1 \\ 0 \end{array} \right]
$$

分别使用

**(a)** $\langle \pmb { x } , \pmb { y } \rangle : = \pmb { x } ^ { \top } \pmb { y }$。

**(b)** $\langle\boldsymbol{x},\boldsymbol{y}\rangle:=\boldsymbol{x}^{\top}\boldsymbol{A}\boldsymbol{y}$，$\boldsymbol{A}:=\begin{bmatrix}2&1&0\\1&3&-1\\0&-1&2\end{bmatrix}$。

**3.4.** 计算下列两向量之间的夹角：

$$
\boldsymbol {x} = \left[ \begin{array}{c} 1 \\ 2 \end{array} \right], \quad \boldsymbol {y} = \left[ \begin{array}{c} - 1 \\ - 1 \end{array} \right]
$$

分别使用

**(a)** $\langle \pmb { x } , \pmb { y } \rangle : = \pmb { x } ^ { \top } \pmb { y }$。

**(b)**

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle := \boldsymbol {x} ^ {\top} \boldsymbol {B} \boldsymbol {y}, \quad \boldsymbol {B} := \left[ \begin{array}{c c} 2 & 1 \\ 1 & 3 \end{array} \right]
$$

**3.5.** 考虑采用点积的欧几里得向量空间 $\mathbb { R } ^ { 5 }$。子空间 $U \subseteq \mathbb { R } ^ { 5 }$ 及向量 $\pmb { x } \in \mathbb { R } ^ { 5 }$ 如下：

$$
U = \operatorname{span} [ \left[ \begin{array}{c} 0 \\ - 1 \\ 2 \\ 0 \\ 2 \end{array} \right], \left[ \begin{array}{c} 1 \\ - 3 \\ 1 \\ - 1 \\ 2 \end{array} \right], \left[ \begin{array}{c} - 3 \\ 4 \\ 1 \\ 2 \\ 1 \end{array} \right], \left[ \begin{array}{c} - 1 \\ - 3 \\ 5 \\ 0 \\ 7 \end{array} \right] ], \quad \boldsymbol {x} = \left[ \begin{array}{c} - 1 \\ - 9 \\ - 1 \\ 4 \\ 1 \end{array} \right].
$$

**(a)** 求 x 到 $U$ 上的正交投影 $\pi _ { U } ( { \pmb x } )$。

**(b)** 求距离 $d ( { \pmb x } , U )$。

**3.6.** 考虑 $\mathbb { R } ^ { 3 }$ 及其内积

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle := \boldsymbol {x} ^ {\top} \left[ \begin{array}{c c c} 2 & 1 & 0 \\ 1 & 2 & - 1 \\ 0 & - 1 & 2 \end{array} \right] \boldsymbol {y}.
$$

此外，记 $e_1,e_2,e_3$ 为 $\mathbb { R } ^ { 3 }$ 的标准基／典范基。

**(a)** 求 $e _ { 2 }$ 到下列子空间上的正交投影 $\pi _ { U } ( e _ { 2 } )$：

$$
U = \operatorname{span} [ \boldsymbol {e} _ {1}, \boldsymbol {e} _ {3} ].
$$

提示：正交性通过内积定义。

**(b)** 计算距离 $d ( e _ { 2 } , U )$。

**(c)** 画出这一情形中的标准基向量和 $\pi _ { U } ( e _ { 2 } )$。

**3.7.** 设 V 为向量空间，π 为 V 上的自同态。

**(a)** 证明 π 是投影，当且仅当 $\operatorname { i d } _ { V } - \pi$ 是投影，其中 $\operatorname { i d } _ { V }$ 是 $V$ 上的恒等自同态。

**(b)** 现假设 π 是投影。用 Im(π) 和 ker(π) 表示 Im $( \operatorname { i d } _ { V } - \pi )$ 和 $\ker ( \mathrm { i d } _ { V } - \pi )$。

**3.8.** 用 Gram–Schmidt 方法，将二维子空间 $U \subseteq \mathbb { R } ^ { 3 }$ 的基 $B ~ = ~ ( b _ { 1 } , b _ { 2 } )$ 转换为 U 的标准正交基 $C = ( c _ { 1 } , c _ { 2 } )$，其中

$$
\boldsymbol {b} _ {1} := \left[ \begin{array}{c} 1 \\ 1 \\ 1 \end{array} \right], \quad \boldsymbol {b} _ {2} := \left[ \begin{array}{c} - 1 \\ 2 \\ 0 \end{array} \right].
$$

**3.9.** 设 $n \in \mathbb { N }$，$x _ { 1 } , \ldots , x _ { n } > 0$ 是 n 个正实数，且 $x _ { 1 } +$ $\ldots + x _ { n } = 1$。利用柯西–施瓦茨不等式证明

**(a)** $\sum_{i=1}^{n}x_i^2\geqslant\frac1n$。

**(b)** $\sum_{i=1}^{n}\frac{1}{x_i}\geqslant n^2$。

提示：考虑 $\mathbb { R } ^ { n }$ 中的点积。选择特定向量 $\boldsymbol{x},\boldsymbol{y}\in\mathbb{R}^{n}$，再应用柯西–施瓦茨不等式。

**3.10.** 将向量

$$
\pmb {x} _ {1} := \left[ \begin{array}{c} 2 \\ 3 \end{array} \right], \quad \pmb {x} _ {2} := \left[ \begin{array}{c} 0 \\ - 1 \end{array} \right]
$$

旋转 $30^{\circ}$。
