# 4 矩阵分解

> 来源：[英文稿](<04_Matrix Decompositions.md>) · [本章 PDF](<../PDF/04_Matrix Decompositions.pdf>)。本译稿尚未完成，当前覆盖引言及完整的 4.1、4.2 节；下一节为 4.3 Cholesky 分解。

![第 4 章标志图](<Images/04_Matrix_Decompositions_image_001.jpg>)

第 2 章和第 3 章讨论了向量的操作与度量、向量投影和线性映射。向量的映射与变换可以方便地用矩阵运算描述。此外，数据也常以矩阵形式表示，例如用矩阵的行表示不同的人，列表示体重、身高、社会经济地位等不同特征。本章从三个方面介绍矩阵：如何概括矩阵的性质、如何分解矩阵，以及如何利用这些分解进行矩阵近似。

首先，讨论如何用少数几个数描述矩阵的整体性质。对于方阵这一重要的特殊情形，4.1 节将介绍行列式（determinant），4.2 节将介绍特征值（eigenvalue）。这些特征数具有重要的数学意义，使我们能够快速掌握矩阵有哪些有用性质。随后介绍矩阵分解方法。矩阵分解可以类比为数的因数分解，例如将 21 分解成素数的乘积 $7\cdot3$。因此，矩阵分解也常称为矩阵因子分解（matrix factorization）。它通过具有可解释意义的矩阵因子，给出原矩阵的另一种表示。

先介绍对称正定矩阵上的一种类似开平方的运算，即 Cholesky 分解（4.3 节）。接着介绍两种相关的矩阵分解方法，将矩阵化为典范形式。第一种是矩阵对角化（matrix diagonalization，4.4 节）：选择合适的基后，可以用对角变换矩阵表示线性映射。第二种是奇异值分解（singular value decomposition，4.5 节），将这种分解推广到非方阵，是线性代数的基本概念之一。这些分解很有用，因为表示数值数据的矩阵往往规模很大，难以分析。最后，4.7 节以矩阵分类体系的形式，系统概括不同矩阵类型及区分它们的特征性质。

本章的方法将在后续数学章节，例如第 6 章，以及应用章节，例如第 10 章的降维和第 11 章的密度估计中发挥重要作用。图 4.1 展示了本章的总体结构。

![图 4.1：矩阵分解概念关系](<Images/04_Matrix_Decompositions_Figure_4_1.png>)

图 4.1 本章概念及其在全书其他部分中的应用关系图。

图内标签对照：Determinant——行列式；Invertibility——可逆性；Cholesky——Cholesky 分解；Eigenvalues——特征值；Eigenvectors——特征向量；Orthogonal matrix——正交矩阵；Diagonalization——对角化；SVD——奇异值分解；Probability & distributions——概率与分布；Dimensionality reduction——降维。tests 表示检验，determines 表示确定，constructs 表示构造，used in 表示用于，Chapter 表示章。

本材料由剑桥大学出版社以《Mathematics for Machine Learning》出版，作者为 Marc Peter Deisenroth、A. Aldo Faisal 和 Cheng Soon Ong（2020）。本版本仅供个人免费查看和下载，不得再分发、转售或用于衍生作品。© M. P. Deisenroth、A. A. Faisal 和 C. S. Ong，2024。[原书网站](https://mml-book.com)。

## 4.1 行列式与迹

> 行列式记号 $|A|$ 不要与绝对值混淆。

行列式是线性代数中的重要概念，是分析和求解线性方程组时使用的数学对象。行列式只对方阵 $A \in \mathbb { R } ^ { n \times n }$ 定义，也就是行数与列数相同的矩阵。本书将行列式记作 det(A)，有时也写作 $| A |$，即

$$
\det (\boldsymbol {A}) = \left| \begin{array}{c c c c} a _ {1 1} & a _ {1 2} & \ldots & a _ {1 n} \\ a _ {2 1} & a _ {2 2} & \ldots & a _ {2 n} \\ \vdots & & \ddots & \vdots \\ a _ {n 1} & a _ {n 2} & \ldots & a _ {n n} \end{array} \right|.\tag{4.1}
$$

方阵 $A \in \mathbb { R } ^ { n \times n }$ 的行列式是一个将 A 映射为实数的函数。在给出一般 $n \times n$ 矩阵的行列式定义之前，先看一些引导性的例子，并定义特殊矩阵的行列式。

**例 4.1（检验矩阵是否可逆）**

先考察方阵 A 是否可逆，见 2.2.2 节。对于最小的几种情形，已经知道矩阵何时可逆。如果 A 是 $1 \times 1$ 矩阵，即一个标量，那么 $\begin{array} { r } { \pmb { A } = \pmb { a } \implies \pmb { A } ^ { - 1 } = \frac { 1 } { a } } \end{array}$。因此，$\begin{array} { r } { a \ \frac { 1 } { a } = 1 } \end{array}$ 成立，当且仅当 $a \neq 0$。

对于 $2 \times 2$ 矩阵，根据逆的定义（定义 2.3），有 $\pmb { A } \pmb { A } ^ { - 1 } = \pmb { I }$。由式 (2.24)，A 的逆为

$$
\pmb {A} ^ {- 1} = \frac {1}{a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1}} \left[ \begin{array}{c c} a _ {2 2} & - a _ {1 2} \\ - a _ {2 1} & a _ {1 1} \end{array} \right].\tag{4.2}
$$

因此，A 可逆，当且仅当

$$
a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1} \neq 0.\tag{4.3}
$$

这个量就是 $A \in \mathbb { R } ^ { 2 \times 2 }$ 的行列式，即

$$
\det (\boldsymbol {A}) = \left| \begin{array}{c c} a _ {1 1} & a _ {1 2} \\ a _ {2 1} & a _ {2 2} \end{array} \right| = a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1}.\tag{4.4}
$$

例 4.1 已经指出行列式与逆矩阵存在性之间的关系。下一条定理将同一结论推广到 $n \times n$ 矩阵。

**定理 4.1。** 对任意方阵 $A \in \mathbb { R } ^ { n \times n }$，A 可逆，当且仅当 $\det(A)\neq0$。

对于小矩阵，行列式可以用矩阵元素写成显式的闭式表达式。当 $n = 1$ 时，

$$
\det (\boldsymbol {A}) = \det (a _ {1 1}) = a _ {1 1}.\tag{4.5}
$$

当 $n=2$ 时，

$$
\det (\boldsymbol {A}) = \left| \begin{array}{c c} a _ {1 1} & a _ {1 2} \\ a _ {2 1} & a _ {2 2} \end{array} \right| = a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1},\tag{4.6}
$$

前面的例子已经给出了这一结果。

当 $n = 3$ 时，使用 Sarrus 法则（Sarrus’ rule）：

$$
\begin{array}{r l} & {\left| \begin{array}{l l l} a _ {1 1} & a _ {1 2} & a _ {1 3} \\ a _ {2 1} & a _ {2 2} & a _ {2 3} \\ a _ {3 1} & a _ {3 2} & a _ {3 3} \end{array} \right| = a _ {1 1} a _ {2 2} a _ {3 3} + a _ {2 1} a _ {3 2} a _ {1 3} + a _ {3 1} a _ {1 2} a _ {2 3}} \\ & {- a _ {3 1} a _ {2 2} a _ {1 3} - a _ {1 1} a _ {3 2} a _ {2 3} - a _ {2 1} a _ {1 2} a _ {3 3}.} \end{array}\tag{4.7}
$$

为了记住 Sarrus 法则中的乘积项，可以在矩阵中依次描出各个三重乘积所取元素的位置。

若方阵 $\boldsymbol T$ 在 $i>j$ 时满足 $T_{ij}=0$，即主对角线下方的元素均为零，就称其为上三角矩阵（upper-triangular matrix）。类似地，主对角线上方元素均为零的矩阵称为下三角矩阵（lower-triangular matrix）。对于三角矩阵 $\boldsymbol T\in\mathbb R^{n\times n}$，行列式等于主对角线元素的乘积，即

$$
\det (\boldsymbol {T}) = \prod_ {i = 1} ^ {n} T _ {i i}.\tag{4.8}
$$

**例 4.2（用行列式度量体积）**

将行列式看作一个以 $n$ 个向量组成的集合为输入的映射，就很自然了：这些向量在 $\mathbb R^n$ 中张成一个几何对象。事实上，行列式 $\det(\boldsymbol A)$ 就是矩阵 $\boldsymbol A$ 的列向量所构成的 $n$ 维平行多面体（parallelepiped）的有向体积（signed volume）。

> 行列式是矩阵列向量所构成的平行多面体的有向体积。

当 $n=2$ 时，矩阵的列向量构成一个平行四边形，见图 4.2。向量之间的夹角变小时，平行四边形的面积也随之减小。考虑构成矩阵 $\boldsymbol A=[\boldsymbol b,\boldsymbol g]$ 的两列的向量 $\boldsymbol b,\boldsymbol g$。矩阵 $\boldsymbol A$ 的行列式的绝对值，就是以 $\boldsymbol 0,\boldsymbol b,\boldsymbol g,\boldsymbol b+\boldsymbol g$ 为顶点的平行四边形的面积。特别地，如果 $\boldsymbol b,\boldsymbol g$ 线性相关，即存在 $\lambda\in\mathbb R$ 使得 $\boldsymbol b=\lambda\boldsymbol g$，它们就不再构成二维的平行四边形，因此相应的面积为 0。反过来，如果 $\boldsymbol b,\boldsymbol g$ 线性无关，且分别为标准基向量 $\boldsymbol e_1,\boldsymbol e_2$ 的倍数，那么可写成 $\boldsymbol b=\begin{bmatrix}b\\0\end{bmatrix}$ 和 $\boldsymbol g=\begin{bmatrix}0\\g\end{bmatrix}$，行列式为 $\begin{vmatrix}b&0\\0&g\end{vmatrix}=bg-0=bg$。

> 译注：原文关于夹角与面积的表述省略了条件。对于长度固定的两个向量，面积随夹角减小而减小的结论适用于夹角在 $0$ 到 $\pi/2$ 之间的情形；不能推广到整个 $0$ 到 $\pi$ 区间。

图 4.2 向量 $\boldsymbol b$ 和 $\boldsymbol g$ 张成的平行四边形（阴影区域）的面积为 $|\det([\boldsymbol b,\boldsymbol g])|$。

![图 4.2](<Images/04_Matrix_Decompositions_image_003.jpg>)

行列式的符号表示张成该图形的向量 $\boldsymbol b,\boldsymbol g$ 相对于标准基 $(\boldsymbol e_1,\boldsymbol e_2)$ 的定向（orientation）。在图中，将顺序改为 $\boldsymbol g,\boldsymbol b$，就会交换 $\boldsymbol A$ 的两列，并反转阴影区域的定向。这就得到熟悉的公式：面积 = 高 $\times$ 长。这一直观认识可以推广到更高维。在 $\mathbb R^3$ 中，考虑三个向量 $\boldsymbol r,\boldsymbol b,\boldsymbol g\in\mathbb R^3$，它们张成一个平行六面体的各条棱；这种立体的各个面都是平行四边形，且相对的面互相平行（见图 4.3）。$3\times3$ 矩阵 $[\boldsymbol r,\boldsymbol b,\boldsymbol g]$ 的行列式的绝对值就是该立体的体积。因此，行列式作为一个函数，度量了矩阵中各列向量构成的有向体积。

图 4.3 向量 $\boldsymbol r,\boldsymbol b,\boldsymbol g$ 张成的平行六面体（阴影体积）的体积为 $|\det([\boldsymbol r,\boldsymbol b,\boldsymbol g])|$。

![图 4.3](<Images/04_Matrix_Decompositions_Figure_4_3.png>)

> 行列式的符号表示张成该图形的向量的定向。

考虑以下三个线性无关的向量 $\boldsymbol r,\boldsymbol g,\boldsymbol b\in\mathbb R^3$：

$$
\boldsymbol {r} = \left[ \begin{array}{c} 2 \\ 0 \\ - 8 \end{array} \right], \quad \boldsymbol {g} = \left[ \begin{array}{c} 6 \\ 1 \\ 0 \end{array} \right], \quad \boldsymbol {b} = \left[ \begin{array}{c} 1 \\ 4 \\ - 1 \end{array} \right].\tag{4.9}
$$

将这些向量写成矩阵的列，得到

$$
\boldsymbol {A} = [ \boldsymbol {r}, \boldsymbol {g}, \boldsymbol {b} ] = \left[ \begin{array}{c c c} 2 & 6 & 1 \\ 0 & 1 & 4 \\ - 8 & 0 & - 1 \end{array} \right]\tag{4.10}
$$

于是可计算所求体积为

$$
V = | \det (\boldsymbol {A}) | = 186.\tag{4.11}
$$

当 $n>3$ 时，计算 $n\times n$ 矩阵的行列式需要一种通用算法，下面将对此展开讨论。定理 4.2 将计算 $n\times n$ 矩阵行列式的问题，归结为计算 $(n-1)\times(n-1)$ 矩阵的行列式。因此，递归使用拉普拉斯展开（Laplace expansion，定理 4.2），最终只需计算 $2\times2$ 矩阵的行列式，就能求出 $n\times n$ 矩阵的行列式。

**定理 4.2（拉普拉斯展开）。** 考虑矩阵 $\boldsymbol A\in\mathbb R^{n\times n}$。对于所有 $j=1,\dots,n$，都有：

1. 沿第 $j$ 列展开

$$
\det (\boldsymbol {A}) = \sum_ {k = 1} ^ {n} (- 1) ^ {k + j} a _ {k j} \det (\boldsymbol {A} _ {k, j}).\tag{4.12}
$$

2. 沿第 $j$ 行展开

$$
\det (\boldsymbol {A}) = \sum_ {k = 1} ^ {n} (- 1) ^ {k + j} a _ {j k} \det (\boldsymbol {A} _ {j, k}).\tag{4.13}
$$

这里，$\boldsymbol A_{k,j}\in\mathbb R^{(n-1)\times(n-1)}$ 是从 $\boldsymbol A$ 中删去第 $k$ 行和第 $j$ 列后得到的子矩阵。

> $\det(\boldsymbol A_{k,j})$ 称为余子式（minor），$(-1)^{k+j}\det(\boldsymbol A_{k,j})$ 称为代数余子式（cofactor）。

**例 4.3（拉普拉斯展开）**

下面沿第一行进行拉普拉斯展开，计算矩阵

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 1 & 2 & 3 \\ 3 & 1 & 2 \\ 0 & 0 & 1 \end{array} \right]\tag{4.14}
$$

的行列式。应用 (4.13)，得到

$$
\begin{array}{c} \left| \begin{array}{c c c} 1 & 2 & 3 \\ 3 & 1 & 2 \\ 0 & 0 & 1 \end{array} \right| = (- 1) ^ {1 + 1} \cdot 1 \left| \begin{array}{c c} 1 & 2 \\ 0 & 1 \end{array} \right| \\ + (- 1) ^ {1 + 2} \cdot 2 \left| \begin{array}{c c} 3 & 2 \\ 0 & 1 \end{array} \right| + (- 1) ^ {1 + 3} \cdot 3 \left| \begin{array}{c c} 3 & 1 \\ 0 & 0 \end{array} \right|. \end{array}\tag{4.15}
$$

利用 (4.6) 计算所有 $2\times2$ 矩阵的行列式，得到

$$
\det (\boldsymbol {A}) = 1 (1 - 0) - 2 (3 - 0) + 3 (0 - 0) = - 5.\tag{4.16}
$$

为使讨论完整，也可以用 Sarrus 法则 (4.7) 计算行列式，并与上述结果比较：

$$
\det (\boldsymbol {A}) = 1 \cdot 1 \cdot 1 + 3 \cdot 0 \cdot 3 + 0 \cdot 2 \cdot 2 - 0 \cdot 1 \cdot 3 - 1 \cdot 0 \cdot 2 - 3 \cdot 2 \cdot 1 = 1 - 6 = - 5.\tag{4.17}
$$

对于 $\boldsymbol A\in\mathbb R^{n\times n}$，行列式具有以下性质：

- 矩阵乘积的行列式等于相应行列式的乘积，即 $\det(\boldsymbol A\boldsymbol B)=\det(\boldsymbol A)\det(\boldsymbol B)$。
- 转置不改变行列式，即 $\det(\boldsymbol A)=\det(\boldsymbol A^\top)$。
- 若 $\boldsymbol A$ 是正则的（regular，即可逆的），则 $\det(\boldsymbol A^{-1})=\frac{1}{\det(\boldsymbol A)}$。
- 相似矩阵（similar matrices，定义 2.22）具有相同的行列式。因此，对于线性映射 $\Phi:V\to V$，其所有变换矩阵 $\boldsymbol A_\Phi$ 的行列式都相同。也就是说，线性映射的行列式不随基的选择而改变。
- 将某一列或某一行的倍数加到另一列或另一行上，不改变 $\det(\boldsymbol A)$。
- 将某一列或某一行乘以 $\lambda\in\mathbb R$，会使 $\det(\boldsymbol A)$ 也乘以 $\lambda$。特别地，$\det(\lambda\boldsymbol A)=\lambda^n\det(\boldsymbol A)$。
- 交换两行或两列会改变 $\det(\boldsymbol A)$ 的符号。

利用最后三条性质，可以通过高斯消元法（Gaussian elimination，见 2.1 节）将 $\boldsymbol A$ 化为行阶梯形（row-echelon form），从而计算 $\det(\boldsymbol A)$。当 $\boldsymbol A$ 已经成为主对角线下方元素全为 0 的三角形式时，就可以停止高斯消元。回顾 (4.8)，三角矩阵的行列式等于主对角线元素的乘积。

**定理 4.3。** 方阵 $\boldsymbol A\in\mathbb R^{n\times n}$ 满足 $\det(\boldsymbol A)\neq0$，当且仅当 $\operatorname{rk}(\boldsymbol A)=n$。换言之，$\boldsymbol A$ 可逆，当且仅当它满秩（full rank）。

在数学计算主要依靠手工进行的年代，计算行列式被视为分析矩阵可逆性的重要方法。然而，现代机器学习采用直接的数值方法，取代了显式计算行列式的做法。例如，在第 2 章中，我们已经学习了用高斯消元法计算逆矩阵。因此，高斯消元法也可以用于计算矩阵的行列式。

行列式将在后续各节发挥重要的理论作用，特别是在通过特征多项式（characteristic polynomial）学习特征值（eigenvalue）和特征向量（eigenvector）时（4.2 节）。

**定义 4.4。** 方阵 $\boldsymbol A\in\mathbb R^{n\times n}$ 的迹（trace）定义为

$$
\operatorname{tr} (\boldsymbol {A}) := \sum_ {i = 1} ^ {n} a _ {i i},\tag{4.18}
$$

即 $\boldsymbol A$ 的主对角线元素之和。

迹具有以下性质：

- 对于 $\boldsymbol A,\boldsymbol B\in\mathbb R^{n\times n}$，$\operatorname{tr}(\boldsymbol A+\boldsymbol B)=\operatorname{tr}(\boldsymbol A)+\operatorname{tr}(\boldsymbol B)$。
- 对于 $\boldsymbol A\in\mathbb R^{n\times n}$ 和 $\alpha\in\mathbb R$，$\operatorname{tr}(\alpha\boldsymbol A)=\alpha\operatorname{tr}(\boldsymbol A)$。
- $\operatorname{tr}(\boldsymbol I_n)=n$。
- 对于 $\boldsymbol A\in\mathbb R^{n\times k}$、$\boldsymbol B\in\mathbb R^{k\times n}$，$\operatorname{tr}(\boldsymbol A\boldsymbol B)=\operatorname{tr}(\boldsymbol B\boldsymbol A)$。

可以证明，同时满足这四条性质的函数只有一个，就是迹（Gohberg 等，2012）。

矩阵乘积的迹还具有更一般的性质。具体而言，迹在循环置换（cyclic permutation）下保持不变，即

$$
\operatorname{tr} (\boldsymbol {A K L}) = \operatorname{tr} (\boldsymbol {K L A})\tag{4.19}
$$

其中矩阵 $\boldsymbol A\in\mathbb R^{a\times k}$、$\boldsymbol K\in\mathbb R^{k\times l}$、$\boldsymbol L\in\mathbb R^{l\times a}$。这一性质可以推广到任意多个矩阵的乘积。作为 (4.19) 的一个特例，对于两个向量 $\boldsymbol x,\boldsymbol y\in\mathbb R^n$，有

$$
\operatorname{tr} \left(\boldsymbol {x} \boldsymbol {y} ^ {\top}\right) = \operatorname{tr} \left(\boldsymbol {y} ^ {\top} \boldsymbol {x}\right) = \boldsymbol {y} ^ {\top} \boldsymbol {x} \in \mathbb {R}.\tag{4.20}
$$

> 循环置换不改变迹。

给定线性映射 $\Phi:V\to V$，其中 $V$ 是向量空间，我们用 $\Phi$ 的矩阵表示的迹来定义该映射的迹。对于 $V$ 的一个给定基，可以用变换矩阵 $\boldsymbol A$ 描述 $\Phi$，此时 $\Phi$ 的迹就是 $\boldsymbol A$ 的迹。对于 $V$ 的另一个基，相应的变换矩阵 $\boldsymbol B$ 可以通过形如 $\boldsymbol S^{-1}\boldsymbol A\boldsymbol S$ 的基变换得到，其中 $\boldsymbol S$ 是适当的矩阵（见 2.7.2 节）。对于 $\Phi$ 的迹，这意味着

$$
\operatorname{tr} (\boldsymbol {B}) = \operatorname{tr} \left(\boldsymbol {S} ^ {- 1} \boldsymbol {A} \boldsymbol {S}\right) \stackrel {(4.19)} {=} \operatorname{tr} \left(\boldsymbol {A} \boldsymbol {S} \boldsymbol {S} ^ {- 1}\right) = \operatorname{tr} (\boldsymbol {A}).\tag{4.21}
$$

因此，线性映射的矩阵表示虽然依赖于基，但线性映射 $\Phi$ 的迹与基无关。

本节介绍了行列式和迹这两个刻画方阵的函数。结合对两者的理解，现在可以定义一个用多项式描述矩阵 $\boldsymbol A$ 的重要等式，后续各节将广泛使用它。

**定义 4.5（特征多项式）。** 对于 $\lambda\in\mathbb R$ 和方阵 $\boldsymbol A\in\mathbb R^{n\times n}$，

$$
\displaystyle p_{\boldsymbol A}(\lambda):=\det(\boldsymbol A-\lambda\boldsymbol I)\tag{4.22a}
$$

$$
\displaystyle \phantom{p_{\boldsymbol A}(\lambda)}=c_0+c_1\lambda+c_2\lambda^2+\dots+c_{n-1}\lambda^{n-1}+(-1)^n\lambda^n,\tag{4.22b}
$$

称为 $\boldsymbol A$ 的特征多项式，其中 $c_0,\dots,c_{n-1}\in\mathbb R$。特别地，

$$
c _ {0} = \det (\boldsymbol {A}),\tag{4.23}
$$

$$
c _ {n - 1} = (- 1) ^ {n - 1} \operatorname{tr} (\boldsymbol {A}).\tag{4.24}
$$

特征多项式 (4.22a) 将使我们能够计算特征值和特征向量，下一节将对此展开讨论。

## 4.2 特征值与特征向量

下面介绍一种刻画矩阵及其对应线性映射的新方法。回顾 2.7.1 节，给定一个有序基后，每个线性映射都有唯一的变换矩阵。通过“特征”分析，可以理解线性映射及其对应的变换矩阵。我们将看到，线性映射的特征值会告诉我们一组特殊向量——特征向量——在该映射下如何变化。

> Eigen 是德语词，意为“特征的”“自身的”或“自己的”。

**定义 4.6。** 设 $\boldsymbol A\in\mathbb R^{n\times n}$ 为方阵。若

$$
\boldsymbol {A} \boldsymbol {x} = \lambda \boldsymbol {x}.\tag{4.25}
$$

则称 $\lambda\in\mathbb R$ 为 $\boldsymbol A$ 的特征值，$\boldsymbol x\in\mathbb R^n\backslash\{\boldsymbol0\}$ 为 $\boldsymbol A$ 对应的特征向量。

我们将 (4.25) 称为特征值方程（eigenvalue equation）。

**说明。** 在线性代数文献和软件中，常常约定将特征值按降序排列：最大的特征值及其对应特征向量称为第一特征值及其对应特征向量，第二大的称为第二特征值及其对应特征向量，依此类推。不过，不同教材和出版物可能采用不同的排序，也可能不规定顺序。本书除非明确说明，否则不预设任何排序。

以下表述等价：

- $\lambda$ 是 $\boldsymbol A\in\mathbb R^{n\times n}$ 的特征值。
- 存在 $\boldsymbol x\in\mathbb R^n\backslash\{\boldsymbol0\}$，使得 $\boldsymbol A\boldsymbol x=\lambda\boldsymbol x$；等价地，$(\boldsymbol A-\lambda\boldsymbol I_n)\boldsymbol x=\boldsymbol0$ 有非平凡解，即 $\boldsymbol x\neq\boldsymbol0$。
- $\operatorname{rk}(\boldsymbol A-\lambda\boldsymbol I_n)<n$。
- $\det(\boldsymbol A-\lambda\boldsymbol I_n)=0$。

**定义 4.7（共线与同向）。** 指向同一方向的两个向量称为同向（codirected）。如果两个向量指向相同或相反的方向，则称它们共线（collinear）。

**说明（特征向量的不唯一性）。** 若 $\boldsymbol x$ 是 $\boldsymbol A$ 对应于特征值 $\lambda$ 的特征向量，那么对于任意 $c\in\mathbb R\backslash\{0\}$，$c\boldsymbol x$ 也是 $\boldsymbol A$ 对应于同一特征值的特征向量，因为

$$
\boldsymbol {A} (c \boldsymbol {x}) = c \boldsymbol {A} \boldsymbol {x} = c \lambda \boldsymbol {x} = \lambda (c \boldsymbol {x}).\tag{4.26}
$$

因此，所有与 $\boldsymbol x$ 共线的向量也都是 $\boldsymbol A$ 的特征向量。

**定理 4.8。** $\lambda\in\mathbb R$ 是 $\boldsymbol A\in\mathbb R^{n\times n}$ 的特征值，当且仅当 $\lambda$ 是 $\boldsymbol A$ 的特征多项式 $p_{\boldsymbol A}(\lambda)$ 的根。

**定义 4.9。** 设方阵 $\boldsymbol A$ 有特征值 $\lambda_i$。$\lambda_i$ 的代数重数（algebraic multiplicity）是该根在特征多项式中出现的次数。

**定义 4.10（特征空间与特征谱）。** 对于 $\boldsymbol A\in\mathbb R^{n\times n}$，与特征值 $\lambda$ 对应的所有特征向量组成的集合张成 $\mathbb R^n$ 的一个子空间，称为 $\boldsymbol A$ 关于 $\lambda$ 的特征空间（eigenspace），记为 $E_\lambda$。$\boldsymbol A$ 的全部特征值组成的集合称为 $\boldsymbol A$ 的特征谱（eigenspectrum），或简称为谱（spectrum）。

若 $\lambda$ 是 $\boldsymbol A\in\mathbb R^{n\times n}$ 的特征值，则对应的特征空间 $E_\lambda$ 是齐次线性方程组 $(\boldsymbol A-\lambda\boldsymbol I)\boldsymbol x=\boldsymbol0$ 的解空间。从几何上看，非零特征值对应的特征向量指向一个被线性映射伸缩的方向，特征值就是伸缩的倍数。如果特征值为负，伸缩的方向还会反转。

**例 4.4（单位矩阵的情形）**

单位矩阵 $\boldsymbol I\in\mathbb R^{n\times n}$ 的特征多项式为 $p_{\boldsymbol I}(\lambda)=\det(\boldsymbol I-\lambda\boldsymbol I)=(1-\lambda)^n=0$，它只有一个特征值 $\lambda=1$，出现 $n$ 次。此外，对于所有向量 $\boldsymbol x\in\mathbb R^n\backslash\{\boldsymbol0\}$，都有 $\boldsymbol I\boldsymbol x=\lambda\boldsymbol x=1\boldsymbol x$。因此，单位矩阵唯一的特征空间 $E_1$ 为 $n$ 维，$\mathbb R^n$ 的全部 $n$ 个标准基向量都是 $\boldsymbol I$ 的特征向量。

> 译注：原文在特征多项式表达式后直接写了“$=0$”，这里表示为求特征值而令多项式等于零，并非说该多项式恒为零。

特征值和特征向量具有以下有用的性质：

- 矩阵 $\boldsymbol A$ 及其转置 $\boldsymbol A^\top$ 具有相同的特征值，但不一定具有相同的特征向量。
- 特征空间 $E_\lambda$ 是 $\boldsymbol A-\lambda\boldsymbol I$ 的零空间（null space），因为

$$
\boldsymbol {A} \boldsymbol {x} = \lambda \boldsymbol {x} \iff \boldsymbol {A} \boldsymbol {x} - \lambda \boldsymbol {x} = \mathbf {0}\tag{4.27a}
$$

$$
\Longleftrightarrow (\boldsymbol {A} - \lambda \boldsymbol {I}) \boldsymbol {x} = \boldsymbol {0} \Longleftrightarrow \boldsymbol {x} \in \ker (\boldsymbol {A} - \lambda \boldsymbol {I}).\tag{4.27b}
$$

- 相似矩阵（见定义 2.22）具有相同的特征值。因此，线性映射 $\Phi$ 的特征值与其变换矩阵所用基的选择无关。这使得特征值与行列式、迹一起，成为刻画线性映射的关键参数，因为它们都在基变换下保持不变。
- 对称正定矩阵的特征值总是正实数。

**例 4.5（计算特征值、特征向量与特征空间）**

下面求 $2\times2$ 矩阵

$$
\boldsymbol {A} = \left[ \begin{array}{c c} 4 & 2 \\ 1 & 3 \end{array} \right].\tag{4.28}
$$

的特征值和特征向量。

**第 1 步：特征多项式。** 根据 $\boldsymbol A$ 的特征向量 $\boldsymbol x\neq\boldsymbol0$ 和特征值 $\lambda$ 的定义，存在向量满足 $\boldsymbol A\boldsymbol x=\lambda\boldsymbol x$，即 $(\boldsymbol A-\lambda\boldsymbol I)\boldsymbol x=\boldsymbol0$。由于 $\boldsymbol x\neq\boldsymbol0$，$\boldsymbol A-\lambda\boldsymbol I$ 的核（kernel，也称零空间）中必须含有零向量以外的元素。这意味着 $\boldsymbol A-\lambda\boldsymbol I$ 不可逆，因此 $\det(\boldsymbol A-\lambda\boldsymbol I)=0$。所以，要找到特征值，需要计算特征多项式 (4.22a) 的根。

**第 2 步：特征值。** 特征多项式为

$$
p _ {\boldsymbol {A}} (\lambda) = \det (\boldsymbol {A} - \lambda \boldsymbol {I})\tag{4.29a}
$$

$$
= \det \left(\left[ \begin{array}{c c} 4 & 2 \\ 1 & 3 \end{array} \right] - \left[ \begin{array}{c c} \lambda & 0 \\ 0 & \lambda \end{array} \right]\right) = \left| \begin{array}{c c} 4 - \lambda & 2 \\ 1 & 3 - \lambda \end{array} \right|\tag{4.29b}
$$

$$
= (4 - \lambda) (3 - \lambda) - 2 \cdot 1.\tag{4.29c}
$$

对特征多项式作因式分解，得到

$$
p (\lambda) = (4 - \lambda) (3 - \lambda) - 2 \cdot 1 = 10 - 7 \lambda + \lambda^ {2} = (2 - \lambda) (5 - \lambda)\tag{4.30}
$$

因此，两根为 $\lambda_1=2$ 和 $\lambda_2=5$。

**第 3 步：特征向量与特征空间。** 为求出这些特征值对应的特征向量，我们寻找满足下式的向量 $\boldsymbol x$：

$$
\left[ \begin{array}{c c} 4 - \lambda & 2 \\ 1 & 3 - \lambda \end{array} \right] \boldsymbol {x} = \boldsymbol {0}.\tag{4.31}
$$

对于 $\lambda=5$，得到

$$
\left[ \begin{array}{c c} 4 - 5 & 2 \\ 1 & 3 - 5 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \end{array} \right] = \left[ \begin{array}{c c} - 1 & 2 \\ 1 & - 2 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \end{array} \right] = \mathbf {0}.\tag{4.32}
$$

求解这个齐次方程组，得到解空间

$$
E _ {5} = \operatorname{span} [ \left[ \begin{array}{c} 2 \\ 1 \end{array} \right] ].\tag{4.33}
$$

这个特征空间是一维的，因为它只有一个基向量。

类似地，求解下面的齐次方程组，可以找到 $\lambda=2$ 对应的特征向量：

$$
\left[ \begin{array}{c c} 4 - 2 & 2 \\ 1 & 3 - 2 \end{array} \right] \boldsymbol {x} = \left[ \begin{array}{c c} 2 & 2 \\ 1 & 1 \end{array} \right] \boldsymbol {x} = \boldsymbol {0}.\tag{4.34}
$$

这意味着，任何满足 $x_2=-x_1$ 的向量 $\boldsymbol x=\begin{bmatrix}x_1\\x_2\end{bmatrix}$，例如 $\begin{bmatrix}1\\-1\end{bmatrix}$，都是特征值 2 对应的特征向量。相应的特征空间为

$$
E _ {2} = \operatorname{span} [ \left[ \begin{array}{c} 1 \\ - 1 \end{array} \right] ].\tag{4.35}
$$

> 译注：这里的“任何向量”仍须满足特征向量非零的定义条件；零向量属于特征空间，但不是特征向量。

例 4.5 中的两个特征空间 $E_5$ 和 $E_2$ 都是一维的，因为它们各自由一个向量张成。不过，在其他情况下，可能存在多个相同的特征值（见定义 4.9），特征空间的维数也可能大于一。

**定义 4.11。** 设 $\lambda_i$ 是方阵 $\boldsymbol A$ 的一个特征值。$\lambda_i$ 的几何重数（geometric multiplicity）是与 $\lambda_i$ 对应的线性无关特征向量的个数。换言之，它是与 $\lambda_i$ 对应的特征向量所张成的特征空间的维数。

**说明。** 一个特征值的几何重数至少为一，因为每个特征值都至少有一个对应的特征向量。几何重数不能超过代数重数，但可以小于代数重数。

**例 4.6**

矩阵 $\boldsymbol A=\begin{bmatrix}2&1\\0&2\end{bmatrix}$ 有两个重复的特征值 $\lambda_1=\lambda_2=2$，其代数重数为 2。然而，这个特征值只有一个不同的单位特征向量 $\boldsymbol x_1=\begin{bmatrix}1\\0\end{bmatrix}$，因此几何重数为 1。

> 译注：原文“只有一个不同的单位特征向量”表述不严谨，因为 $-\boldsymbol x_1$ 也是单位特征向量。这里应理解为只有一个线性无关的特征向量方向；特征空间为一维，几何重数为 1 的结论不受影响。

### 二维图形直观解释

下面借助不同的线性映射，建立对行列式、特征向量和特征值的直观认识。图 4.4 展示了五个变换矩阵 $\boldsymbol A_1,\dots,\boldsymbol A_5$ 及其对以原点为中心的正方形点阵的影响：

- $\boldsymbol A_1=\begin{bmatrix}\frac12&0\\0&2\end{bmatrix}$。两个特征向量的方向对应于 $\mathbb R^2$ 中的标准基向量，也就是两条坐标轴。竖直方向被拉伸为原来的 2 倍（特征值 $\lambda_1=2$），水平方向被压缩为原来的 $\frac12$（特征值 $\lambda_2=\frac12$）。该映射保持面积不变，因为 $\det(\boldsymbol A_1)=1=2\cdot\frac12$。
- $\boldsymbol A_2=\begin{bmatrix}1&\frac12\\0&1\end{bmatrix}$ 对应一个剪切映射（shearing mapping）：位于竖直坐标为正的半平面内的点沿水平方向向右移动，反之则向左移动。该映射保持面积不变，因为 $\det(\boldsymbol A_2)=1$。特征值 $\lambda_1=1=\lambda_2$ 重复出现，特征向量共线（图中特意沿相反的两个方向绘出）。这表明映射只沿一个方向，即水平方向，产生作用。
- $\boldsymbol A_3=\begin{bmatrix}\cos(\frac\pi6)&-\sin(\frac\pi6)\\\sin(\frac\pi6)&\cos(\frac\pi6)\end{bmatrix}=\frac12\begin{bmatrix}\sqrt3&-1\\1&\sqrt3\end{bmatrix}$。矩阵 $\boldsymbol A_3$ 将点逆时针旋转 $\frac\pi6\,\mathrm{rad}=30^\circ$，且只有复特征值，体现了该映射的旋转性质（因此图中没有绘出特征向量）。旋转必须保持体积，所以行列式为 1。关于旋转的更多内容，见 3.9 节。
- $\boldsymbol A_4=\begin{bmatrix}1&-1\\-1&1\end{bmatrix}$ 表示标准基下的一个映射，将二维定义域压缩到一维。由于一个特征值为 0，空间沿对应于 $\lambda_1=0$ 的蓝色特征向量方向被压缩至零；而与之正交的红色特征向量方向上的空间则被拉伸为原来的 $\lambda_2=2$ 倍。因此，像的面积为 0。
- $\boldsymbol A_5=\begin{bmatrix}1&\frac12\\\frac12&1\end{bmatrix}$ 是兼有剪切和伸缩作用的映射，将面积缩放为原来的 75%，因为 $|\det(\boldsymbol A_5)|=\frac34$。它沿对应于 $\lambda_2$ 的红色特征向量方向将空间拉伸为原来的 1.5 倍，并沿与之正交的蓝色特征向量方向将空间压缩为原来的 0.5 倍。

> 在几何学中，这种平行于某一坐标轴的剪切保持面积不变的性质，也称为平行四边形等面积的卡瓦列里原理（Cavalieri’s principle；Katz，2004）。

图 4.4 行列式与特征空间。图中概览了五种线性映射及其对应的变换矩阵 $\boldsymbol A_i\in\mathbb R^{2\times2}$：将 400 个以颜色区分的点 $\boldsymbol x\in\mathbb R^2$（左列）映射到目标点 $\boldsymbol A_i\boldsymbol x$（右列）。中间一列绘出了按对应特征值 $\lambda_1$ 缩放的第一特征向量，以及按特征值 $\lambda_2$ 缩放的第二特征向量。每一行展示一个变换矩阵 $\boldsymbol A_i$ 在标准基下的作用。图中蓝色对应第一特征向量，红色对应第二特征向量；$\det(A)$ 表示行列式，第三行数值中的 $j$ 表示虚数单位。

![图 4.4](<Images/04_Matrix_Decompositions_Figure_4_4.png>)

**例 4.7（生物神经网络的特征谱）**

图 4.5 秀丽隐杆线虫（Caenorhabditis elegans）的神经网络（Kaiser 和 Hilgetag，2006）。（a）对称化后的连接矩阵；（b）特征谱。

![图 4.5(a)](<Images/04_Matrix_Decompositions_image_018.jpg>)

（a）连接矩阵。横轴和纵轴的 neuron index 均表示神经元编号。

![图 4.5(b)](<Images/04_Matrix_Decompositions_image_019.jpg>)

（b）特征谱。横轴 index of sorted eigenvalue 表示按降序排列后的特征值序号；纵轴 eigenvalue 表示特征值。

分析网络数据并从中学习的方法，是机器学习方法的重要组成部分。理解网络的关键在于网络节点之间的连接关系，尤其是两个节点是否相互连接。在数据科学应用中，研究记录这些连接数据的矩阵往往很有用。

我们为秀丽隐杆线虫的完整神经网络构建一个连接矩阵（connectivity matrix），也称邻接矩阵（adjacency matrix），$\boldsymbol A\in\mathbb R^{277\times277}$。每一行或每一列代表这种线虫脑中的 277 个神经元之一。如果神经元 $i$ 通过突触向神经元 $j$ 传递信息，连接矩阵 $\boldsymbol A$ 的元素取 $a_{ij}=1$；否则取 $a_{ij}=0$。连接矩阵不是对称的，这意味着特征值可能不是实数。因此，我们计算连接矩阵的一个对称化版本：$\boldsymbol A_{sym}:=\boldsymbol A+\boldsymbol A^\top$。这个新矩阵 $\boldsymbol A_{sym}$ 如图 4.5(a) 所示；当且仅当两个神经元之间有连接时，相应元素 $a_{ij}$ 非零（白色像素），而不区分连接的方向。图 4.5(b) 展示了 $\boldsymbol A_{sym}$ 的特征谱。横轴表示按降序排列后的特征值序号，纵轴表示对应的特征值。许多生物神经网络的特征谱都具有这种典型的 S 形。产生这一形状的内在机制，是神经科学中一个活跃的研究领域。

**定理 4.12。** 若矩阵 $\boldsymbol A\in\mathbb R^{n\times n}$ 有 $n$ 个互不相同的特征值 $\lambda_1,\dots,\lambda_n$，则对应的特征向量 $\boldsymbol x_1,\dots,\boldsymbol x_n$ 线性无关。

该定理说明，具有 $n$ 个互不相同特征值的矩阵，其特征向量构成 $\mathbb R^n$ 的一个基。

**定义 4.13。** 若方阵 $\boldsymbol A\in\mathbb R^{n\times n}$ 的线性无关特征向量少于 $n$ 个，则称它为亏损矩阵（defective matrix）。

非亏损矩阵 $\boldsymbol A\in\mathbb R^{n\times n}$ 不一定需要有 $n$ 个互不相同的特征值，但其特征向量必须能够构成 $\mathbb R^n$ 的一个基。考察亏损矩阵的特征空间，可以得到各特征空间的维数之和小于 $n$。具体而言，亏损矩阵至少有一个特征值 $\lambda_i$，其代数重数 $m>1$，而几何重数小于 $m$。

**说明。** 亏损矩阵不可能有 $n$ 个互不相同的特征值，因为不同特征值对应的特征向量线性无关（定理 4.12）。

**定理 4.14。** 给定矩阵 $\boldsymbol A\in\mathbb R^{m\times n}$，通过定义

$$
\boldsymbol {S} := \boldsymbol {A} ^ {\top} \boldsymbol {A}.\tag{4.36}
$$

总能得到一个对称半正定矩阵 $\boldsymbol S\in\mathbb R^{n\times n}$。

**说明。** 若 $\operatorname{rk}(\boldsymbol A)=n$，则 $\boldsymbol S:=\boldsymbol A^\top\boldsymbol A$ 是对称正定矩阵。

理解定理 4.14 为何成立，有助于理解如何使用对称化的矩阵。对称性要求 $\boldsymbol S=\boldsymbol S^\top$；代入 (4.36)，得到 $\boldsymbol S=\boldsymbol A^\top\boldsymbol A=\boldsymbol A^\top(\boldsymbol A^\top)^\top=(\boldsymbol A^\top\boldsymbol A)^\top=\boldsymbol S^\top$。此外，半正定性（3.2.3 节）要求 $\boldsymbol x^\top\boldsymbol S\boldsymbol x\geq0$；代入 (4.36)，得到 $\boldsymbol x^\top\boldsymbol S\boldsymbol x=\boldsymbol x^\top\boldsymbol A^\top\boldsymbol A\boldsymbol x=(\boldsymbol x^\top\boldsymbol A^\top)(\boldsymbol A\boldsymbol x)=(\boldsymbol A\boldsymbol x)^\top(\boldsymbol A\boldsymbol x)\geq0$，因为点积计算的是各分量的平方和，而每个平方都非负。

**定理 4.15（谱定理，spectral theorem）。** 若 $\boldsymbol A\in\mathbb R^{n\times n}$ 对称，则相应的向量空间 $V$ 存在一个由 $\boldsymbol A$ 的特征向量构成的标准正交基（orthonormal basis），且每个特征值都是实数。

谱定理直接意味着，对称矩阵 $\boldsymbol A$ 的特征分解（eigendecomposition）存在，且特征值为实数。我们可以找到由特征向量构成的标准正交基，使得 $\boldsymbol A=\boldsymbol P\boldsymbol D\boldsymbol P^\top$，其中 $\boldsymbol D$ 为对角矩阵，$\boldsymbol P$ 的各列为这些特征向量。

**例 4.8**

考虑矩阵

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 3 & 2 & 2 \\ 2 & 3 & 2 \\ 2 & 2 & 3 \end{array} \right].\tag{4.37}
$$

$\boldsymbol A$ 的特征多项式为

$$
p _ {\boldsymbol {A}} (\lambda) = - (\lambda - 1) ^ {2} (\lambda - 7),\tag{4.38}
$$

因此得到特征值 $\lambda_1=1$ 和 $\lambda_2=7$，其中 $\lambda_1$ 是重特征值。按照计算特征向量的通常步骤，得到特征空间

$$
E _ {1} = \operatorname{span} [ \underbrace {\left[ \begin{array}{c} - 1 \\ 1 \\ 0 \end{array} \right]} _ {=: \boldsymbol {x} _ {1}}, \underbrace {\left[ \begin{array}{c} - 1 \\ 0 \\ 1 \end{array} \right]} _ {=: \boldsymbol {x} _ {2}} ], \quad E _ {7} = \operatorname{span} [ \underbrace {\left[ \begin{array}{c} 1 \\ 1 \\ 1 \end{array} \right]} _ {=: \boldsymbol {x} _ {3}} ].\tag{4.39}
$$

可以看到，$\boldsymbol x_3$ 与 $\boldsymbol x_1$、$\boldsymbol x_2$ 都正交。不过，由于 $\boldsymbol x_1^\top\boldsymbol x_2=1\neq0$，后两个向量不正交。谱定理（定理 4.15）保证存在正交基，但目前得到的基不是正交的。不过，我们可以构造一个正交基。

构造时可以利用这样一个事实：$\boldsymbol x_1$ 和 $\boldsymbol x_2$ 是同一特征值 $\lambda$ 对应的特征向量。因此，对于任意 $\alpha,\beta\in\mathbb R$，都有

$$
\boldsymbol {A} \left(\alpha \boldsymbol {x} _ {1} + \beta \boldsymbol {x} _ {2}\right) = \boldsymbol {A} \boldsymbol {x} _ {1} \alpha + \boldsymbol {A} \boldsymbol {x} _ {2} \beta = \lambda \left(\alpha \boldsymbol {x} _ {1} + \beta \boldsymbol {x} _ {2}\right),\tag{4.40}
$$

也就是说，$\boldsymbol x_1$ 和 $\boldsymbol x_2$ 的任意线性组合也是 $\boldsymbol A$ 对应于 $\lambda$ 的特征向量。格拉姆–施密特算法（Gram–Schmidt algorithm，3.8.3 节）利用这样的线性组合，从一组基向量出发，迭代构造正交基或标准正交基。因此，即使 $\boldsymbol x_1$ 和 $\boldsymbol x_2$ 不正交，也可以应用该算法，找到对应于 $\lambda_1=1$、彼此正交且都与 $\boldsymbol x_3$ 正交的特征向量。在本例中，得到

$$
\boldsymbol {x} _ {1} ^ {\prime} = \left[ \begin{array}{c} - 1 \\ 1 \\ 0 \end{array} \right], \quad \boldsymbol {x} _ {2} ^ {\prime} = \frac {1}{2} \left[ \begin{array}{c} - 1 \\ - 1 \\ 2 \end{array} \right],\tag{4.41}
$$

它们彼此正交，也都与 $\boldsymbol x_3$ 正交，并且都是 $\boldsymbol A$ 对应于 $\lambda_1=1$ 的特征向量。

> 译注：原文“任意线性组合也是特征向量”须排除线性组合等于零的情形；公式 (4.40) 对零组合仍成立，但零向量不是特征向量。

在结束对特征值和特征向量的讨论之前，将这些矩阵特征与行列式、迹联系起来很有帮助。

**定理 4.16。** 矩阵 $\boldsymbol A\in\mathbb R^{n\times n}$ 的行列式等于其特征值的乘积，即

$$
\det (\boldsymbol {A}) = \prod_ {i = 1} ^ {n} \lambda_ {i},\tag{4.42}
$$

其中 $\lambda_i\in\mathbb C$ 是 $\boldsymbol A$ 的特征值，可以重复出现。

**定理 4.17。** 矩阵 $\boldsymbol A\in\mathbb R^{n\times n}$ 的迹等于其特征值之和，即

$$
\operatorname{tr} (\boldsymbol {A}) = \sum_ {i = 1} ^ {n} \lambda_ {i},\tag{4.43}
$$

其中 $\lambda_i\in\mathbb C$ 是 $\boldsymbol A$ 的特征值，可以重复出现。

图 4.6 特征值的几何解释。$\boldsymbol A$ 的特征向量按照对应的特征值伸缩。单位正方形的面积变为原来的 $|\lambda_1\lambda_2|$ 倍，周长变为原来的 $\frac12(|\lambda_1|+|\lambda_2|)$ 倍。

![图 4.6](<Images/04_Matrix_Decompositions_image_020.jpg>)

下面给出这两个定理的几何直观解释。考虑具有两个线性无关特征向量 $\boldsymbol x_1,\boldsymbol x_2$ 的矩阵 $\boldsymbol A\in\mathbb R^{2\times2}$。在这个例子中，假设 $(\boldsymbol x_1,\boldsymbol x_2)$ 是 $\mathbb R^2$ 的标准正交基，因此两向量正交，所张成的正方形面积为 1，见图 4.6。由 4.1 节可知，行列式计算了单位正方形在变换 $\boldsymbol A$ 下的面积变化。本例中可以显式计算这种变化：用 $\boldsymbol A$ 映射两个特征向量，得到 $\boldsymbol v_1=\boldsymbol A\boldsymbol x_1=\lambda_1\boldsymbol x_1$ 和 $\boldsymbol v_2=\boldsymbol A\boldsymbol x_2=\lambda_2\boldsymbol x_2$。也就是说，新向量 $\boldsymbol v_i$ 是特征向量 $\boldsymbol x_i$ 的缩放结果，缩放因子为对应的特征值 $\lambda_i$。$\boldsymbol v_1,\boldsymbol v_2$ 仍然正交，所张成的矩形面积为 $|\lambda_1\lambda_2|$。

由于本例中的 $\boldsymbol x_1,\boldsymbol x_2$ 标准正交，单位正方形的周长可直接算得为 $2(1+1)$。用 $\boldsymbol A$ 映射这两个特征向量后，得到的矩形周长为 $2(|\lambda_1|+|\lambda_2|)$。因此，特征值的绝对值之和告诉我们，单位正方形的周长在变换矩阵 $\boldsymbol A$ 的作用下如何变化。

**例 4.9（Google 的 PageRank：作为特征向量的网页）**

Google 使用矩阵 $\boldsymbol A$ 的最大特征值所对应的特征向量，确定网页在搜索中的排名。Larry Page 和 Sergey Brin 于 1996 年在斯坦福大学提出 PageRank 算法，其思路是：一个网页的重要性，可以通过链接到它的那些网页的重要性来近似衡量。为此，他们将所有网站表示为一个巨大的有向图，记录哪些页面链接到哪些页面。PageRank 通过统计指向网站 $a_i$ 的页面数量，计算其权重（重要性）$x_i\geq0$，同时也考虑链接到 $a_i$ 的网站的重要性。随后，用该图的转移矩阵（transition matrix）$\boldsymbol A$ 对用户的浏览行为建模，矩阵描述了用户以多大的点击概率到达另一个网站。

矩阵 $\boldsymbol A$ 具有这样的性质：对于任意初始排名或重要性向量 $\boldsymbol x$，序列 $\boldsymbol x,\boldsymbol A\boldsymbol x,\boldsymbol A^2\boldsymbol x,\dots$ 收敛到向量 $\boldsymbol x^*$。该向量称为 PageRank，并满足 $\boldsymbol A\boldsymbol x^*=\boldsymbol x^*$，即它是 $\boldsymbol A$ 对应于特征值 1 的特征向量。将 $\boldsymbol x^*$ 归一化，使得 $\|\boldsymbol x^*\|=1$ 后，可以将各分量解释为概率。关于 PageRank 的更多细节和不同视角，可参阅原始技术报告（Page 等，1999）。

> 译注：这里概述的是具有相应收敛性质的 PageRank 转移矩阵；任意转移矩阵并不都保证上述迭代收敛。原文未注明归一化使用的范数；要将非负分量解释为概率，应使分量之和为 1，即采用 $\ell_1$ 归一化。

