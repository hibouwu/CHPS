# 2 线性代数

> 来源：[英文稿](<02_Linear Algebra.md>) · [本章 PDF](<../PDF/02_Linear Algebra.pdf>)。本章正文及习题 2.1—2.20 已完成翻译与复核；英文稿已完成全部 53 页 PDF 对照校对。原书疑点另见章节验收记录。

![第 2 章标志图](<Images/02_Linear_Algebra_image_001.jpg>)

将直观概念形式化时，一种常见方法是构造一组对象（符号），以及一组操作这些对象的规则。这就称为一个代数（algebra）。线性代数（linear algebra）研究向量及操作向量的某些规则。我们许多人在学校里接触过的向量称为“几何向量”（geometric vector），通常在字母上方加一个小箭头表示，例如 $\vec{x}$ 和 $\vec{y}$。本书讨论更一般的向量概念，并用粗体字母表示向量，例如 $\boldsymbol{x}$ 和 $\boldsymbol{y}$。

一般来说，向量是一类特殊对象：它们可以相加，也可以与标量（scalar）相乘，结果仍是同一类对象。从抽象的数学视角看，满足这两种性质的任何对象都可以视为向量。下面给出这类向量对象的一些例子：

1. **几何向量。** 在高中数学和物理中，你可能已经熟悉了这种向量。几何向量是有向线段，见图 2.1(a)，可以画出来，至少在二维情况下如此。两个几何向量 $\vec { x }$、$\vec { y }$ 可以相加，得到另一个几何向量 $\vec{x}+\vec{y}=\vec{z}$。此外，与标量相乘得到的 $\lambda { \vec { x } }$（$\lambda \in \mathbb { R }$） 也是几何向量。实际上，它就是将原向量按 $\lambda$ 缩放后的结果。因此，几何向量是前述向量概念的实例。将向量理解为几何向量，能让我们利用关于方向和大小的直觉来推理数学运算。

2. **多项式也是向量**，见图 2.1(b)。两个多项式相加，结果仍是多项式；多项式与标量 $\lambda\in\mathbb{R}$ 相乘，结果也仍是多项式。因此，多项式也是向量的实例，只是这种实例比较不寻常。请注意，多项式与几何向量非常不同：几何向量是具体的“图形”，多项式则是抽象概念。不过，从前述意义上看，两者都是向量。

3. **音频信号是向量。** 音频信号表示为一系列数值。我们可以将音频信号相加，其和是一个新的音频信号；对音频信号进行缩放，得到的也仍是音频信号。因此，音频信号也是一种向量。

4. **$\mathbb { R } ^ { n }$ 中的元素**（由 $n$ 个实数组成的元组）**是向量。** $\mathbb { R } ^ { n }$ 比多项式更加抽象，也是本书重点讨论的概念。例如，

$$
\boldsymbol {a} = \left[ \begin{array}{c} 1 \\ 2 \\ 3 \end{array} \right] \in \mathbb {R} ^ {3}\tag{2.1}
$$

就是一个由三个数组成的三元组。将两个向量 $\boldsymbol{a}, \boldsymbol{b} \in \mathbb{R}^{n}$ 按对应分量相加，会得到另一个向量：$\pmb { a } + \pmb { b } = \pmb { c } \in \mathbb { R } ^ { n }$。此外，将 $\pmb { a } \in \mathbb { R } ^ { n }$ 与 $\lambda \in \mathbb { R }$ 相乘，得到缩放后的向量 $\lambda\boldsymbol{a}\in\mathbb{R}^{n}$。将向量看作 $\mathbb { R } ^ { n }$ 中的元素还有一个好处：它大致对应于计算机中的实数数组。[^array-vector-operations] 许多编程语言支持数组运算，便于实现涉及向量运算的算法。

![几何向量相加](<Images/02_Linear_Algebra_image_002.jpg>)

(a) 几何向量。

![多项式曲线](<Images/02_Linear_Algebra_image_003.jpg>)

(b) 多项式。

图 2.1 不同类型的向量。向量可以是一些出人意料的对象，包括 (a) 几何向量和 (b) 多项式。

线性代数关注这些向量概念的共同之处：它们可以相加，也可以与标量相乘。我们主要关注 $\mathbb { R } ^ { n }$ 中的向量，因为线性代数的大多数算法都在 $\mathbb { R } ^ { n }$ 中表述。第 8 章将说明，我们经常把数据表示为 $\mathbb { R } ^ { n }$ 中的向量。本书重点讨论有限维向量空间（finite-dimensional vector space）；在这种情况下，任何一种向量都与 $\mathbb { R } ^ { n }$ 中的元素存在一一对应关系。方便时，我们会借助几何向量的直觉，并考虑基于数组的算法。

数学中的一个重要思想是“闭包”（closure）。它所提出的问题是：通过我所规定的运算，能够得到的全部对象构成什么集合？对于向量，问题就是：从一小组向量出发，将它们彼此相加并进行缩放，能够得到的向量构成什么集合？由此得到向量空间（vector space，见 2.4 节）。向量空间的概念及其性质是机器学习许多内容的基础。图 2.2 概括了本章介绍的概念。

本章主要依据 Drumm and Weil（2001）、Strang（2003）、Hogben（2013）、Liesen and Mehrmann（2015）的讲义与著作，以及 [Pavel Grinfeld 的线性代数系列课程](http://tinyurl.com/nahclwm)。其他优秀资源包括 [Gilbert Strang 在 MIT 开设的线性代数课程](http://tinyurl.com/bdfbu8s5)和 [3Blue1Brown 的线性代数系列](https://tinyurl.com/h5g4kps)。

![本章概念关系图](<Images/02_Linear_Algebra_image_004.jpg>)

图 2.2 本章所介绍概念的思维导图，以及这些概念在本书其他部分中的应用位置。

图内标签对照：Vector——向量；Matrix——矩阵；Vector space——向量空间；Group——群；Linear independence——线性无关；Basis——基；System of linear equations——线性方程组；Gaussian elimination——高斯消元；Matrix inverse——矩阵的逆；Linear/affine mapping——线性／仿射映射；Vector calculus——向量微积分；Analytic geometry——解析几何；Classification——分类；Dimensionality reduction——降维。关系标签：composes——组成；closure——闭包；property of——……的性质；represents——表示；solved by——由……求解；solves——求解；Abelian with +——在加法运算下为阿贝尔群；maximal set——极大集合。Chapter 表示章。

线性代数在机器学习和一般数学中都发挥着重要作用。第 3 章将进一步扩展本章介绍的概念，引入几何思想。第 5 章将讨论向量微积分（vector calculus），其中必须系统地掌握矩阵运算。第 10 章将利用投影（projection，将在 3.8 节介绍），通过主成分分析（principal component analysis，PCA）进行降维（dimensionality reduction）。第 9 章将讨论线性回归（linear regression），其中线性代数在求解最小二乘问题（least-squares problem）时起核心作用。

## 2.1 线性方程组

线性方程组（system of linear equations）在线性代数中占据核心地位。许多问题都可以表述为线性方程组，而线性代数为求解它们提供了工具。

**例 2.1**

某公司生产产品 $N _ { 1 } , \ldots , N _ { n }$，需要使用资源 $R _ { 1 } , \ldots , R _ { m }$。每生产一单位产品 $N_j$，就需要 $a_{ij}$ 单位的资源 $R _ { i }$，其中 $i = 1 , \ldots , m$，$j = 1 , \dots , n$。

目标是找到一个最优生产计划：当资源 $R _ { i }$ 的可用总量为 $b _ { i }$ 单位，并且理想情况下所有资源都没有剩余时，确定每种产品 $N _ { j }$ 应当生产的数量 $x _ { j }$。

如果相应产品的产量分别为 $x _ { 1 } , \ldots , x _ { n }$ 单位，那么所需资源总量为

$$
a _ {i 1} x _ {1} + \dots + a _ {i n} x _ {n}\tag{2.2}
$$

单位的资源 $R _ { i }$。因此，一个最优生产计划 $( x _ { 1 } , \ldots , x _ { n } ) \in \mathbb { R } ^ { n }$ 必须满足以下方程组：

$$
\begin{array}{c} a _ {1 1} x _ {1} + \dots + a _ {1 n} x _ {n} = b _ {1} \\ \vdots \\ a _ {m 1} x _ {1} + \dots + a _ {m n} x _ {n} = b _ {m} \end{array} ,\tag{2.3}
$$

其中 $a _ { i j } \in \mathbb { R }$，$b _ { i } \in \mathbb { R }$。

式 (2.3) 是线性方程组的一般形式，$x _ { 1 } , \ldots , x _ { n }$ 是该方程组的未知数。每个满足式 (2.3) 的 $n$ 元组 $( x _ { 1 } , \ldots , x _ { n } ) \in$ $\mathbb { R } ^ { n }$ 都是该线性方程组的一个解。

**例 2.2**

线性方程组

$$
\begin{array}{rcrcrcl}
x_1 & + & x_2 & + & x_3 & = & 3 \quad (1) \\
x_1 & - & x_2 & + & 2x_3 & = & 2 \quad (2) \\
2x_1 & & & + & 3x_3 & = & 1 \quad (3)
\end{array}
\tag{2.4}
$$ 

无解：将前两个方程相加，得到 $2 x _ { 1 } + 3 x _ { 3 } = 5$，这与第三个方程 (3) 矛盾。

再来看下面的线性方程组：

$$
\begin{array}{rcrcrcll} x _ {1} & + & x _ {2} & + & x _ {3} & = & 3 & (1) \\ x _ {1} & - & x _ {2} & + & 2 x _ {3} & = & 2 & (2) \\ & & x _ {2} & + & x _ {3} & = & 2 & (3) \end{array} .\tag{2.5}
$$

由第一个和第三个方程可得 $x _ { 1 } = 1$。由 $( 1 ) + ( 2 )$ 得到 $2x_1+3x_3=5$，即 $x_3=1$。再由 (3) 得到 $x_2=1$。因此，(1, 1, 1) 是唯一可能的解，也是这个方程组的唯一解（将 (1, 1, 1) 代入，验证它确实是解）。

第三个例子考虑方程组

$$
\begin{array}{c c c c c c c c} x _ {1} & + & x _ {2} & + & x _ {3} & = & 3 & (1) \\ x _ {1} & - & x _ {2} & + & 2 x _ {3} & = & 2 & (2) \\ 2 x _ {1} & & & + & 3 x _ {3} & = & 5 & (3) \end{array}\tag{2.6}
$$

由于 $( 1 ) + ( 2 ) = ( 3 )$，可以省略第三个方程，因为它是冗余的。由 (1) 和 (2) 得到 $2 x _ { 1 } = 5 { - } 3 x _ { 3 }$ 和 $2 x _ { 2 } = 1 + x _ { 3 }$。令 $x_3=a\in\mathbb{R}$ 为自由变量（free variable），则任意三元组

$$
\left(\frac {5}{2} - \frac {3}{2} a, \frac {1}{2} + \frac {1}{2} a, a\right), \quad a \in \mathbb {R}\tag{2.7}
$$

都是这个线性方程组的解，也就是说，我们得到的解集包含无穷多个解。

一般来说，实数域上的线性方程组有三种可能：无解、恰有一个解，或者有无穷多个解。当线性方程组无法求解时，线性回归（第 9 章）处理的是例 2.1 的一种变体。

**注（线性方程组的几何解释）。** 对于含两个变量 $x _ { 1 } , x _ { 2 }$ 的线性方程组，每个线性方程都在 $x_1x_2$ 平面上定义一条直线。由于方程组的解必须同时满足所有方程，其解集就是这些直线的交集。交集可以是一条直线（各方程描述同一条直线时）、一个点，也可以是空集（直线平行时）。图 2.3 展示了以下方程组的情形：

$$
\begin{array}{l} {4 x _ {1} + 4 x _ {2} = 5} \\ {2 x _ {1} - 4 x _ {2} = 1} \end{array}\tag{2.8}
$$

其中，解空间是点 $( x _ { 1 } , x _ { 2 } ) = ( 1 , { \textstyle \frac { 1 } { 4 } } )$。类似地，对于三个变量，每个线性方程都确定三维空间中的一个平面。当我们求这些平面的交集，即同时满足所有线性方程时，得到的解集可以是一个平面、一条直线、一个点，也可以是空集（这些平面没有公共交集时）。

![图 2.3：两条直线的交点](<Images/02_Linear_Algebra_image_005.jpg>)

图 2.3 含两个变量的两个线性方程所组成方程组的解空间，可以在几何上解释为两条直线的交集。每个线性方程表示一条直线。

为了系统地求解线性方程组，我们引入一种实用而紧凑的记法：将系数 $a _ { i j }$ 组织成向量，再将这些向量组织成矩阵（matrix）。换言之，将式 (2.3) 的方程组写成以下形式：

$$
\left[ \begin{array}{c} a _ {1 1} \\ \vdots \\ a _ {m 1} \end{array} \right] x _ {1} + \left[ \begin{array}{c} a _ {1 2} \\ \vdots \\ a _ {m 2} \end{array} \right] x _ {2} + \dots + \left[ \begin{array}{c} a _ {1 n} \\ \vdots \\ a _ {m n} \end{array} \right] x _ {n} = \left[ \begin{array}{c} b _ {1} \\ \vdots \\ b _ {m} \end{array} \right]\tag{2.9}
$$

$$
\Longleftrightarrow \left[ \begin{array}{c c c} a _ {1 1} & \dots & a _ {1 n} \\ \vdots & & \vdots \\ a _ {m 1} & \dots & a _ {m n} \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ \vdots \\ x _ {n} \end{array} \right] = \left[ \begin{array}{c} b _ {1} \\ \vdots \\ b _ {m} \end{array} \right].\tag{2.10}
$$

下面将仔细研究这些矩阵，并定义其运算规则。2.3 节将回到线性方程的求解问题。

## 2.2 矩阵

矩阵在线性代数中起核心作用。矩阵既可以紧凑地表示线性方程组，也可以表示线性函数（线性映射，linear mapping），后一种用途将在 2.7 节介绍。在讨论这些有趣的主题之前，我们先定义矩阵是什么，以及可以对矩阵进行哪些运算。第 4 章将介绍矩阵的更多性质。

**定义 2.1（矩阵）。** 设 $m,n\in\mathbb{N}$。实数值的 $(m,n)$ 矩阵 $\boldsymbol{A}$ 是由 $m\cdot n$ 个元素 $a_{ij}$ 构成的元组，其中 $i=1,\ldots,m$、$j=1,\ldots,n$。这些元素按照具有 $m$ 行、$n$ 列的矩形形式排列：

$$
\boldsymbol{A}=\begin{bmatrix}
a_{11}&a_{12}&\cdots&a_{1n}\\
a_{21}&a_{22}&\cdots&a_{2n}\\
\vdots&\vdots&&\vdots\\
a_{m1}&a_{m2}&\cdots&a_{mn}
\end{bmatrix},\quad a_{ij}\in\mathbb{R}.
\tag{2.11}
$$

按照惯例，$(1,n)$ 矩阵称为行，$(m,1)$ 矩阵称为列。这两种特殊矩阵也称为行向量（row vector）和列向量（column vector）。

$\mathbb{R}^{m\times n}$ 是所有实数值 $(m,n)$ 矩阵组成的集合。将矩阵的全部 $n$ 列依次堆叠成一个长向量，就可以把 $\boldsymbol{A}\in\mathbb{R}^{m\times n}$ 等价地表示为 $\boldsymbol{a}\in\mathbb{R}^{mn}$，见图 2.4。

![图 2.4：堆叠矩阵的各列](<Images/02_Linear_Algebra_image_006.jpg>)

图 2.4 将各列依次堆叠，可以把矩阵 $\boldsymbol{A}$ 表示为一个长向量 $\boldsymbol{a}$。图内 re-shape 表示重塑形状。

### 2.2.1 矩阵加法与乘法

两个矩阵 $\boldsymbol{A}\in\mathbb{R}^{m\times n}$、$\boldsymbol{B}\in\mathbb{R}^{m\times n}$ 的和定义为对应元素之和，即

$$
\boldsymbol{A}+\boldsymbol{B}:=\begin{bmatrix}
a_{11}+b_{11}&\cdots&a_{1n}+b_{1n}\\
\vdots&&\vdots\\
a_{m1}+b_{m1}&\cdots&a_{mn}+b_{mn}
\end{bmatrix}\in\mathbb{R}^{m\times n}.
\tag{2.12}
$$

对于矩阵 $\boldsymbol{A}\in\mathbb{R}^{m\times n}$、$\boldsymbol{B}\in\mathbb{R}^{n\times k}$，其乘积 $\boldsymbol{C}=\boldsymbol{A}\boldsymbol{B}\in\mathbb{R}^{m\times k}$ 的元素 $c_{ij}$ 按以下方式计算：

$$
c_{ij}=\sum_{l=1}^{n}a_{il}b_{lj},\quad i=1,\ldots,m,\quad j=1,\ldots,k.
\tag{2.13}
$$

> 注意矩阵的尺寸。

```python
C = np.einsum('il,lj', A, B)
```

这意味着，计算元素 $c _ { i j }$ 时，将 A 的第 i 行与 B 的第 j 列中的对应元素相乘，再把结果相加。在 3.2 节中，我们将把这种运算称为对应行与列的点积（dot product）。当需要明确说明所做的是乘法时，我们用记号 $\pmb { A } \cdot \pmb { B }$ 表示乘法，也就是显式写出“$\cdot$”。

> $\boldsymbol{A}$ 有 $n$ 列，$\boldsymbol{B}$ 有 $n$ 行，因此对于 $l=1,\ldots,n$，都可以计算 $a_{il}b_{lj}$。
>
> 通常，两个向量 $\boldsymbol{a},\boldsymbol{b}$ 的点积记为 $\boldsymbol{a}^{\top}\boldsymbol{b}$ 或 $\langle\boldsymbol{a},\boldsymbol{b}\rangle$。

**注。** 只有当两个矩阵“相邻”的维度匹配时，才能相乘。例如，一个 $n\times k$ 矩阵 $\boldsymbol{A}$ 可以与一个 $k\times m$ 矩阵 $\boldsymbol{B}$ 相乘，但前者只能放在后者左边：

$$
\underbrace {A} _ {n \times k} \underbrace {B} _ {k \times m} = \underbrace {C} _ {n \times m}\tag{2.14}
$$

如果 $m\neq n$，乘积 $\boldsymbol{B}\boldsymbol{A}$ 就没有定义，因为相邻维度不匹配。

**注。** 矩阵乘法并不是对矩阵元素逐个相乘，即 $c_{ij}\neq a_{ij}b_{ij}$，即使 $A , B$ 的尺寸选择得合适，也仍然如此。编程语言中对多维数组进行相乘时，经常会出现这种逐元素乘法，它称为 Hadamard 积（Hadamard product）。

**例 2.3**

对于

$$
\boldsymbol {A} = \left[ \begin{array}{l l l} 1 & 2 & 3 \\ 3 & 2 & 1 \end{array} \right] \in \mathbb {R} ^ {2 \times 3},   \boldsymbol {B} = \left[ \begin{array}{l l} 0 & 2 \\ 1 & - 1 \\ 0 & 1 \end{array} \right] \in \mathbb {R} ^ {3 \times 2}
$$

可得

$$
\boldsymbol {A} \boldsymbol {B} = \left[ \begin{array}{c c c} 1 & 2 & 3 \\ 3 & 2 & 1 \end{array} \right] \left[ \begin{array}{c c} 0 & 2 \\ 1 & - 1 \\ 0 & 1 \end{array} \right] = \left[ \begin{array}{c c} 2 & 3 \\ 2 & 5 \end{array} \right] \in \mathbb {R} ^ {2 \times 2},\tag{2.15}
$$

$$
\boldsymbol {B} \boldsymbol {A} = \left[ \begin{array}{c c} 0 & 2 \\ 1 & - 1 \\ 0 & 1 \end{array} \right] \left[ \begin{array}{c c c} 1 & 2 & 3 \\ 3 & 2 & 1 \end{array} \right] = \left[ \begin{array}{c c c} 6 & 4 & 2 \\ - 2 & 0 & 2 \\ 3 & 2 & 1 \end{array} \right] \in \mathbb {R} ^ {3 \times 3}.\tag{2.16}
$$

从这个例子已经可以看出，矩阵乘法不满足交换律，即 $\boldsymbol{A}\boldsymbol{B}\neq\boldsymbol{B}\boldsymbol{A}$。图 2.5 也对此作了说明。

![图 2.5：AB 与 BA 的形状](<Images/02_Linear_Algebra_image_007.jpg>)

图 2.5 即使矩阵乘法 $AB$ 和 $BA$ 都有定义，结果的维度也可能不同。

**定义 2.2（单位矩阵）。** 在 $\mathbb { R } ^ { n \times n }$ 中，定义单位矩阵（identity matrix）

$$
\boldsymbol {I} _ {n} := \left[ \begin{array}{c c c c c c} 1 & 0 & \dots & 0 & \dots & 0 \\ 0 & 1 & \dots & 0 & \dots & 0 \\ \vdots & \vdots & \ddots & \vdots & \ddots & \vdots \\ 0 & 0 & \dots & 1 & \dots & 0 \\ \vdots & \vdots & \ddots & \vdots & \ddots & \vdots \\ 0 & 0 & \dots & 0 & \dots & 1 \end{array} \right] \in \mathbb {R} ^ {n \times n}\tag{2.17}
$$

为主对角线上元素均为 1、其余元素均为 0 的 $n\times n$ 矩阵。

定义了矩阵乘法、矩阵加法和单位矩阵之后，下面来看矩阵的一些性质：

- **结合律（associativity）：**

$$
\forall \boldsymbol {A} \in \mathbb {R} ^ {m \times n}, \boldsymbol {B} \in \mathbb {R} ^ {n \times p}, \boldsymbol {C} \in \mathbb {R} ^ {p \times q}: (\boldsymbol {A B}) \boldsymbol {C} = \boldsymbol {A} (\boldsymbol {B C})\tag{2.18}
$$

- **分配律（distributivity）：**

$$
\forall \boldsymbol {A}, \boldsymbol {B} \in \mathbb {R} ^ {m \times n}, \boldsymbol {C}, \boldsymbol {D} \in \mathbb {R} ^ {n \times p}: (\boldsymbol {A} + \boldsymbol {B}) \boldsymbol {C} = \boldsymbol {A C} + \boldsymbol {B C}\tag{2.19a}
$$

$$
\boldsymbol {A} (\boldsymbol {C} + \boldsymbol {D}) = \boldsymbol {A C} + \boldsymbol {A D}\tag{2.19b}
$$

- **与单位矩阵相乘：**

$$
\forall \boldsymbol {A} \in \mathbb {R} ^ {m \times n}: \boldsymbol {I} _ {m} \boldsymbol {A} = \boldsymbol {A} \boldsymbol {I} _ {n} = \boldsymbol {A}\tag{2.20}
$$

注意，当 $m\neq n$ 时，${ \pmb { I } } _ { m } \neq { \pmb { I } } _ { n }$。

### 2.2.2 逆与转置

**定义 2.3（逆）。** 考虑方阵（square matrix）$A \in \mathbb { R } ^ { n \times n }$。设矩阵 $B \in \mathbb { R } ^ { n \times n }$ 满足 $A B = I _ { n } = B A$，则称 B 为 A 的逆（inverse），记为 $A^{-1}$。

> 方阵的行数与列数相同。

遗憾的是，并非每个矩阵 A 都有逆 $A ^ { - 1 }$。如果逆存在，就称 A 为正则矩阵／可逆矩阵／非奇异矩阵（regular/invertible/nonsingular）；否则称为奇异矩阵／不可逆矩阵（singular/noninvertible）。矩阵的逆如果存在，就一定唯一。2.3 节将讨论一种通过求解线性方程组计算矩阵逆的一般方法。

**注（$2\times2$ 矩阵的逆何时存在）。** 考虑矩阵

$$
\boldsymbol {A} := \left[ \begin{array}{c c} a _ {1 1} & a _ {1 2} \\ a _ {2 1} & a _ {2 2} \end{array} \right] \in \mathbb {R} ^ {2 \times 2}.\tag{2.21}
$$

将 A 与下面的矩阵相乘：

$$
\boldsymbol {A} ^ {\prime} := \left[ \begin{array}{c c} a _ {2 2} & - a _ {1 2} \\ - a _ {2 1} & a _ {1 1} \end{array} \right]\tag{2.22}
$$

得到

$$
\boldsymbol {A} \boldsymbol {A} ^ {\prime} = \left[ \begin{array}{c c} a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1} & 0 \\ 0 & a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1} \end{array} \right] = (a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1}) \boldsymbol {I}.\tag{2.23}
$$

因此，

$$
\pmb {A} ^ {- 1} = \frac {1}{a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1}} \left[ \begin{array}{c c} a _ {2 2} & - a _ {1 2} \\ - a _ {2 1} & a _ {1 1} \end{array} \right]\tag{2.24}
$$

当且仅当 $a _ { 1 1 } a _ { 2 2 } - a _ { 1 2 } a _ { 2 1 } \neq 0$。4.1 节将介绍，$a_{11}a_{22}-a_{12}a_{21}$ 是 $2\times2$ 矩阵的行列式（determinant）。更一般地，也可以通过行列式判断矩阵是否可逆。

**例 2.4（逆矩阵）**

矩阵

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 1 & 2 & 1 \\ 4 & 4 & 5 \\ 6 & 7 & 7 \end{array} \right], \quad \boldsymbol {B} = \left[ \begin{array}{c c c} - 7 & - 7 & 6 \\ 2 & 1 & - 1 \\ 4 & 5 & - 4 \end{array} \right]\tag{2.25}
$$

互为逆矩阵，因为 $AB=I=BA$。

**定义 2.4（转置）。** 对于 $\pmb { A } \in \mathbb { R } ^ { m \times n }$，满足 $b _ { i j } = a _ { j i }$ 的矩阵 $B \in \mathbb { R } ^ { n \times m }$ 称为 A 的转置（transpose），记为 $\boldsymbol{B}=\boldsymbol{A}^{\top}$。

一般来说，将 A 的各列写成 $A ^ { \top }$ 的各行，即可得到 $A ^ { \top }$。下面列出逆和转置的重要性质：

> 矩阵 $\boldsymbol{A}$ 的主对角线（main diagonal，也称 principal diagonal、primary diagonal、leading diagonal 或 major diagonal）是满足 $i=j$ 的元素 $A_{ij}$ 的集合。

$$
\boldsymbol{A}\boldsymbol{A}^{-1}=\boldsymbol{I}=\boldsymbol{A}^{-1}\boldsymbol{A}
\tag{2.26}
$$

$$
(\boldsymbol{A}\boldsymbol{B})^{-1}=\boldsymbol{B}^{-1}\boldsymbol{A}^{-1}
\tag{2.27}
$$

$$
(\boldsymbol{A}+\boldsymbol{B})^{-1}\neq\boldsymbol{A}^{-1}+\boldsymbol{B}^{-1}
\tag{2.28}
$$

> 式 (2.28) 在标量情况下的例子是 $\frac{1}{2+4}=\frac{1}{6}\neq\frac{1}{2}+\frac{1}{4}$。

$$
(\boldsymbol{A}^{\top})^{\top}=\boldsymbol{A}
\tag{2.29}
$$

$$
(\boldsymbol{A}\boldsymbol{B})^{\top}=\boldsymbol{B}^{\top}\boldsymbol{A}^{\top}
\tag{2.30}
$$

$$
(\boldsymbol{A}+\boldsymbol{B})^{\top}=\boldsymbol{A}^{\top}+\boldsymbol{B}^{\top}
\tag{2.31}
$$

**定义 2.5（对称矩阵）。** 如果矩阵 $A \in \mathbb { R } ^ { n \times n }$ 满足 $\boldsymbol{A}=\boldsymbol{A}^{\top}$，就称它为对称矩阵（symmetric matrix）。

注意，只有 $( n , n )$ 矩阵才可能对称。通常也把 $( n , n )$ 矩阵称为方阵，因为其行数与列数相同。此外，如果 A 可逆，那么 $A ^ { \top }$ 也可逆，并且 $( A ^ { - 1 } ) ^ { \top } = ( A ^ { \top } ) ^ { - 1 } = : A ^ { - \top }$。

**注（对称矩阵的和与积）。** 对称矩阵 $\pmb { A } , \pmb { B } \in \mathbb { R } ^ { n \times n }$ 的和总是对称矩阵。不过，虽然它们的乘积总有定义，却一般不是对称矩阵：

$$
\left[ \begin{array}{c c} 1 & 0 \\ 0 & 0 \end{array} \right] \left[ \begin{array}{c c} 1 & 1 \\ 1 & 1 \end{array} \right] = \left[ \begin{array}{c c} 1 & 1 \\ 0 & 0 \end{array} \right].\tag{2.32}
$$

### 2.2.3 与标量相乘

下面考察矩阵与标量 $\lambda \in \mathbb { R }$ 相乘时会发生什么。设 $\pmb { A } \in \mathbb { R } ^ { m \times n }$，$\lambda \in \mathbb { R }$，则 $\lambda A=K$，$K_{ij}=\lambda a_{ij}$。实际上，λ 对 A 的每一个元素进行缩放。对于 $\lambda , \psi \in \mathbb { R }$，以下性质成立：

- **结合律：**

$$
(\lambda \psi) \boldsymbol {C} = \lambda (\psi \boldsymbol {C}), \quad \boldsymbol {C} \in \mathbb {R} ^ {m \times n}
$$

- $\lambda ( B C ) = ( \lambda B ) C = B ( \lambda C ) = ( B C ) \lambda , \quad B \in \mathbb { R } ^ { m \times n } , C \in \mathbb { R } ^ { n \times k } .$

注意，这使我们可以移动标量因子的位置。

- $( \lambda C ) ^ { \top } = C ^ { \top } \lambda ^ { \top } = C ^ { \top } \lambda = \lambda C ^ { \top }$，因为对所有 $\lambda\in\mathbb{R}$ 都有 $\lambda = \lambda ^ { \top }$。

- **分配律：**

$$
(\lambda + \psi) \boldsymbol {C} = \lambda \boldsymbol {C} + \psi \boldsymbol {C}, \quad \boldsymbol {C} \in \mathbb {R} ^ {m \times n}
$$

$$
\lambda (\boldsymbol {B} + \boldsymbol {C}) = \lambda \boldsymbol {B} + \lambda \boldsymbol {C}, \quad \boldsymbol {B}, \boldsymbol {C} \in \mathbb {R} ^ {m \times n}
$$

**例 2.5（分配律）**

如果定义

$$
\boldsymbol {C} := \left[ \begin{array}{c c} 1 & 2 \\ 3 & 4 \end{array} \right],\tag{2.33}
$$

那么，对任意 $\lambda , \psi \in \mathbb { R }$，都有

$$
(\lambda+\psi)\boldsymbol{C}
=\begin{bmatrix}(\lambda+\psi)1&(\lambda+\psi)2\\(\lambda+\psi)3&(\lambda+\psi)4\end{bmatrix}
=\begin{bmatrix}\lambda+\psi&2\lambda+2\psi\\3\lambda+3\psi&4\lambda+4\psi\end{bmatrix}
\tag{2.34a}
$$

$$
=\begin{bmatrix}\lambda&2\lambda\\3\lambda&4\lambda\end{bmatrix}
+\begin{bmatrix}\psi&2\psi\\3\psi&4\psi\end{bmatrix}
=\lambda\boldsymbol{C}+\psi\boldsymbol{C}.
\tag{2.34b}
$$

### 2.2.4 线性方程组的紧凑表示

考虑线性方程组

$$
\begin{array}{l} 2 x _ {1} + 3 x _ {2} + 5 x _ {3} = 1 \\ 4 x _ {1} - 2 x _ {2} - 7 x _ {3} = 8 \\ 9 x _ {1} + 5 x _ {2} - 3 x _ {3} = 2 \end{array}\tag{2.35}
$$

利用矩阵乘法规则，可以将该方程组更紧凑地写成

$$
\left[ \begin{array}{c c c} 2 & 3 & 5 \\ 4 & - 2 & - 7 \\ 9 & 5 & - 3 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \\ x _ {3} \end{array} \right] = \left[ \begin{array}{c} 1 \\ 8 \\ 2 \end{array} \right].\tag{2.36}
$$

注意，$x _ { 1 }$ 缩放第一列，$x _ { 2 }$ 缩放第二列，$x _ { 3 }$ 缩放第三列。

一般来说，线性方程组可以紧凑地表示为矩阵形式 $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{b}$，见式 (2.3)。乘积 $\boldsymbol{A}\boldsymbol{x}$ 是 $\pmb { A }$ 各列的一个（线性）组合。2.5 节将更详细地讨论线性组合（linear combination）。

## 2.3 求解线性方程组

式 (2.3) 给出了方程组的一般形式，即

$$
\begin{array}{c} a _ {1 1} x _ {1} + \dots + a _ {1 n} x _ {n} = b _ {1} \\ \vdots \\ a _ {m 1} x _ {1} + \dots + a _ {m n} x _ {n} = b _ {m}, \end{array}\tag{2.37}
$$

其中，$a _ { i j } \in \mathbb { R }$ 和 $b _ { i } \in \mathbb { R }$ 是已知常数，$x _ { j }$ 是未知数，$i = 1 , \ldots , m , j = 1 , \ldots , n$。前面已经看到，矩阵可以紧凑地表述线性方程组，因此可以写成 $\mathbf { { A } } \mathbf { { x } } = \mathbf { { b } }$，见式 (2.10)。此外，我们还定义了矩阵加法、乘法等基本运算。下面将重点讨论线性方程组的求解，并给出一种求矩阵逆的算法。

### 2.3.1 特解与通解

在讨论线性方程组的一般求解方法之前，先来看一个例子。考虑方程组

$$
\left[ \begin{array}{c c c c} 1 & 0 & 8 & - 4 \\ 0 & 1 & 2 & 12 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \\ x _ {3} \\ x _ {4} \end{array} \right] = \left[ \begin{array}{c} 42 \\ 8 \end{array} \right].\tag{2.38}
$$

该方程组含两个方程和四个未知数，因此通常预期它有无穷多个解。这个方程组的形式特别简单：前两列都由一个 1 和一个 0 构成。请记住，我们希望找到标量 $x _ { 1 } , \ldots , x _ { 4 }$，使 $\textstyle \sum _ { i = 1 } ^ { 4 } x _ { i } c _ { i } = b$，其中 $c _ { i }$ 表示矩阵的第 i 列，b 表示式 (2.38) 的右端。取第一列的 42 倍和第二列的 8 倍，就能立即找到式 (2.38) 的一个解，因为

$$
\boldsymbol {b} = \left[ \begin{array}{c} 42 \\ 8 \end{array} \right] = 42 \left[ \begin{array}{c} 1 \\ 0 \end{array} \right] + 8 \left[ \begin{array}{c} 0 \\ 1 \end{array} \right].\tag{2.39}
$$

因此，一个解为 $[ 42 , 8 , 0 , 0 ] ^ { \top }$。这样的解称为特解（particular solution 或 special solution）。不过，这不是该线性方程组的唯一解。为了找到其余所有解，我们需要巧妙地利用矩阵的各列，以非平凡的方式产生 0：给特解加上 0，不会改变这个特解。为此，利用形式非常简单的前两列表示第三列：

$$
\left[ \begin{array}{c} 8 \\ 2 \end{array} \right] = 8 \left[ \begin{array}{c} 1 \\ 0 \end{array} \right] + 2 \left[ \begin{array}{c} 0 \\ 1 \end{array} \right]\tag{2.40}
$$

这样就有 ${ \mathbf{0} } = 8 { { c } _ { 1 } } + 2 { { c } _ { 2 } } - 1 { { c } _ { 3 } } + 0 { { c } _ { 4 } }$，相应地，$( x _ { 1 } , x _ { 2 } , x _ { 3 } , x _ { 4 } ) = ( 8 , 2 , - 1 , 0 )$。实际上，用任意 $\lambda _ { 1 } \in \mathbb { R }$ 对这一解进行缩放，仍然产生零向量，即

$$
\left[ \begin{array}{c c c c} 1 & 0 & 8 & - 4 \\ 0 & 1 & 2 & 12 \end{array} \right] \left(\lambda_ {1} \left[ \begin{array}{c} 8 \\ 2 \\ - 1 \\ 0 \end{array} \right]\right) = \lambda_ {1} (8 \boldsymbol {c} _ {1} + 2 \boldsymbol {c} _ {2} - \boldsymbol {c} _ {3}) = \boldsymbol {0}.\tag{2.41}
$$

沿着同样的思路，利用前两列表示式 (2.38) 中矩阵的第四列，得到另一组以非平凡方式产生 0 的表达式：

$$
\left[ \begin{array}{c c c c} 1 & 0 & 8 & - 4 \\ 0 & 1 & 2 & 12 \end{array} \right] \left(\lambda_ {2} \left[ \begin{array}{c} - 4 \\ 12 \\ 0 \\ - 1 \end{array} \right]\right) = \lambda_ {2} (- 4 \boldsymbol {c} _ {1} + 12 \boldsymbol {c} _ {2} - \boldsymbol {c} _ {4}) = \mathbf {0}\tag{2.42}
$$

其中 $\lambda _ { 2 } \in \mathbb { R }$ 可以任意取值。综合上述结果，就得到式 (2.38) 方程组的全部解，称为通解（general solution），其集合形式为

$$
\left\{\boldsymbol {x} \in \mathbb {R} ^ {4}: \boldsymbol {x} = \left[ \begin{array}{c} 42 \\ 8 \\ 0 \\ 0 \end{array} \right] + \lambda_ {1} \left[ \begin{array}{c} 8 \\ 2 \\ - 1 \\ 0 \end{array} \right] + \lambda_ {2} \left[ \begin{array}{c} - 4 \\ 12 \\ 0 \\ - 1 \end{array} \right], \lambda_ {1}, \lambda_ {2} \in \mathbb {R} \right\}.\tag{2.43}
$$

**注。** 上述一般方法包含以下三个步骤：

1. 找到 $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{b}$ 的一个特解。

2. 找到 $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{0}$ 的全部解。

3. 将步骤 1 和步骤 2 的解合并，得到通解。

通解和特解都不是唯一的。

> 译注：此句按原文保留。就这里的构造而言，可以选择不同特解以及不同的参数化方式来表示同一个解集；固定方程组的全部解所组成的集合本身是确定的。

前面的线性方程组之所以容易求解，是因为式 (2.38) 中的矩阵具有特别方便的形式，观察即可找到特解和通解。然而，一般的方程组并没有这样简单的形式。幸好，有一种构造性的算法可以将任意线性方程组变换为这种特别简单的形式，这就是高斯消元（Gaussian elimination）。高斯消元的关键是对线性方程组进行初等变换（elementary transformation），把它化为简单形式。然后，就可以对这一简单形式应用前面围绕式 (2.38) 的例子所讨论的三个步骤。

### 2.3.2 初等变换

求解线性方程组的关键，是通过初等变换保持解集不变，同时将方程组化为更简单的形式：

- 交换两个方程，即交换表示该方程组的矩阵中的两行。

- 将一个方程（一行）乘以常数 $\lambda \in \mathbb { R } \backslash \{ 0 \}$。

- 将两个方程（两行）相加。

**例 2.6**

对于 $a\in\mathbb{R}$，求以下方程组的全部解：

$$
\begin{array}{rcrcrcrcrcl}- 2 x _ {1} & + & 4 x _ {2} & - & 2 x _ {3} & - & x _ {4} & + & 4 x _ {5} & = & - 3 \\ 4 x _ {1} & - & 8 x _ {2} & + & 3 x _ {3} & - & 3 x _ {4} & + & x _ {5} & = & 2 \\ x _ {1} & - & 2 x _ {2} & + & x _ {3} & - & x _ {4} & + & x _ {5} & = & 0 \\ x _ {1} & - & 2 x _ {2} & & & - & 3 x _ {4} & + & 4 x _ {5} & = & a \\ \end{array} .\tag{2.44}
$$

首先，将方程组转换成紧凑的矩阵记法 $A x = b$。不再显式写出变量 x，而是构造增广矩阵（augmented matrix），其形式为 $[\boldsymbol{A}\mid\boldsymbol{b}]$：

$$
\left[\begin{array}{rrrrr|r}
-2&4&-2&-1&4&-3\\
4&-8&3&-3&1&2\\
1&-2&1&-1&1&0\\
1&-2&0&-3&4&a
\end{array}\right]
\qquad R_1\leftrightarrow R_3
$$

其中，竖线将式 (2.44) 的左端与右端分开。用 $\rightsquigarrow$ 表示对增广矩阵施加初等变换。

> 增广矩阵 $[\boldsymbol{A}\mid\boldsymbol{b}]$ 紧凑地表示了线性方程组 $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{b}$。

交换第 1 行和第 3 行，得到

$$
\left[\begin{array}{rrrrr|r}
1&-2&1&-1&1&0\\
4&-8&3&-3&1&2\\
-2&4&-2&-1&4&-3\\
1&-2&0&-3&4&a
\end{array}\right]
\qquad
\begin{array}{l}
R_2\leftarrow R_2-4R_1\\
R_3\leftarrow R_3+2R_1\\
R_4\leftarrow R_4-R_1
\end{array}
$$

现在进行所标出的变换，例如从第 2 行减去第 1 行的 4 倍，得到

$$
\left[\begin{array}{rrrrr|r}
1&-2&1&-1&1&0\\
0&0&-1&1&-3&2\\
0&0&0&-3&6&-3\\
0&0&-1&-2&3&a
\end{array}\right]
\qquad R_4\leftarrow R_4-R_2-R_3
$$

$$
\rightsquigarrow
\left[\begin{array}{rrrrr|r}
1&-2&1&-1&1&0\\
0&0&-1&1&-3&2\\
0&0&0&-3&6&-3\\
0&0&0&0&0&a+1
\end{array}\right]
\qquad
\begin{array}{l}
R_2\leftarrow -R_2\\
R_3\leftarrow -\frac13R_3
\end{array}
$$

$$
\rightsquigarrow
\left[\begin{array}{rrrrr|r}
1&-2&1&-1&1&0\\
0&0&1&-1&3&-2\\
0&0&0&1&-2&1\\
0&0&0&0&0&a+1
\end{array}\right]
$$

这个增广矩阵具有一种便于处理的形式，称为行阶梯形（row-echelon form，REF）。将紧凑记法还原为包含待求变量的显式记法，得到

$$
\begin{array}{rcrcrcrcrcl} x _ {1} & - & 2 x _ {2} & + & x _ {3} & - & x _ {4} & + & x _ {5} & = & 0 \\ & & & & x _ {3} & - & x _ {4} & + & 3 x _ {5} & = & - 2 \\ & & & & & & x _ {4} & - & 2 x _ {5} & = & 1 \\ & & & & & & & & 0 & = & a + 1 \end{array}\tag{2.45}
$$

仅当 $a = - 1$ 时，该方程组才有解。一个特解为

$$
{\left[ \begin{array}{l} x _ {1} \\ x _ {2} \\ x _ {3} \\ x _ {4} \\ x _ {5} \end{array} \right]} = {\left[ \begin{array}{l} 2 \\ 0 \\ - 1 \\ 1 \\ 0 \end{array} \right]}\tag{2.46}
$$

包含全部可能解的通解为

$$
\left\{\boldsymbol {x} \in \mathbb {R} ^ {5}: \boldsymbol {x} = \left[ \begin{array}{c} 2 \\ 0 \\ - 1 \\ 1 \\ 0 \end{array} \right] + \lambda_ {1} \left[ \begin{array}{c} 2 \\ 1 \\ 0 \\ 0 \\ 0 \end{array} \right] + \lambda_ {2} \left[ \begin{array}{c} 2 \\ 0 \\ - 1 \\ 2 \\ 1 \end{array} \right], \quad \lambda_ {1}, \lambda_ {2} \in \mathbb {R} \right\}.\tag{2.47}
$$

下面将详细介绍一种构造方法，用来求出线性方程组的特解和通解。

**注（主元与阶梯结构）。** 一行的首项系数，即从左往右第一个非零数，称为主元（pivot）。在行阶梯形中，它总是严格位于上一行主元的右侧。因此，行阶梯形的方程组总是具有“阶梯”结构。

**定义 2.6（行阶梯形）。** 如果一个矩阵满足以下条件，就称其为行阶梯形：

- 所有只含零的行都在矩阵底部；相应地，所有至少包含一个非零元素的行，都位于这些全零行上方。

- 只考虑非零行时，每行从左往右第一个非零数，也称主元或首项系数，总是严格位于上一行主元的右侧。

> 某些其他教材还要求主元为 1。

**注（基本变量与自由变量）。** 行阶梯形中与主元对应的变量称为基本变量（basic variable），其余变量称为自由变量。例如，在式 (2.45) 中，$x _ { 1 } , x _ { 3 } , x _ { 4 }$ 是基本变量，$x _ { 2 } , x _ { 5 }$ 是自由变量。◇

**注（求特解）。** 行阶梯形使求特解变得更容易。具体做法是用主元列表示方程组的右端，使 $\boldsymbol{b}=\sum_{i=1}^{P}\lambda_i\boldsymbol{p}_i$，其中 $p _ { i } , i = 1 , \ldots , P$ 是主元列。确定 $\lambda _ { i }$ 最容易的方式，是从最右边的主元列开始，逐步向左处理。

在前面的例子中，我们要寻找 $\lambda _ { 1 } , \lambda _ { 2 } , \lambda _ { 3 }$，使

$$
\lambda_ {1} \left[ \begin{array}{c} 1 \\ 0 \\ 0 \\ 0 \end{array} \right] + \lambda_ {2} \left[ \begin{array}{c} 1 \\ 1 \\ 0 \\ 0 \end{array} \right] + \lambda_ {3} \left[ \begin{array}{c} - 1 \\ - 1 \\ 1 \\ 0 \end{array} \right] = \left[ \begin{array}{c} 0 \\ - 2 \\ 1 \\ 0 \end{array} \right].\tag{2.48}
$$

由此可以较为直接地得到 $\lambda _ { 3 } = 1 , \lambda _ { 2 } = - 1 , \lambda _ { 1 } = 2$。综合结果时，不要忘记非主元列：我们实际上已将它们的系数设为 0。因此，得到特解 $\boldsymbol{x}=[2,0,-1,1,0]^{\top}$。

**注（简化行阶梯形）。** 如果一个方程组满足以下条件，就称其为简化行阶梯形（reduced row-echelon form，也称 row-reduced echelon form 或 row canonical form）：

- 它是行阶梯形。

- 每个主元都是 1。

- 主元是其所在列中唯一的非零元素。

简化行阶梯形在后面的 2.3.3 节中将起重要作用，因为它使我们能够直接确定线性方程组的通解。

**注（高斯消元）。** 高斯消元是一种通过初等变换，将线性方程组化为简化行阶梯形的算法。

**例 2.7（简化行阶梯形）**

验证下面的矩阵是简化行阶梯形，主元用粗体标出：

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c c} \mathbf {1} & 3 & 0 & 0 & 3 \\ 0 & 0 & \mathbf {1} & 0 & 9 \\ 0 & 0 & 0 & \mathbf {1} & - 4 \end{array} \right].\tag{2.49}
$$

求 $\pmb { A } \pmb { x } = \pmb { 0 }$ 的解，关键在于考察非主元列，并将其表示为主元列的线性组合。简化行阶梯形使这件事比较直接：用非主元列左侧主元列的倍数与和表示它。第二列是第一列的 3 倍，第二列右侧的主元列可以忽略。因此，为了得到 0，需要从第一列的 3 倍中减去第二列。再看第五列，这是第二个非主元列。它可以表示为第一个主元列的 3 倍、第二个主元列的 9 倍和第三个主元列的 $-4$ 倍之和。我们需要留意主元列在原矩阵中的下标：这里对应第一列的 3 倍、第二列的 0 倍（第二列是非主元列）、第三列的 9 倍（第三列是第二个主元列），以及第四列的 $-4$ 倍（第四列是第三个主元列）。然后减去第五列，即可得到 0。归根结底，我们求解的仍是一个齐次方程组（homogeneous system）。

综上，$\pmb { A } \pmb { x } = \mathbf { 0 } , \pmb { x } \in \mathbb { R } ^ { 5 }$ 的全部解为

$$
\left\{\boldsymbol {x} \in \mathbb {R} ^ {5}: \boldsymbol {x} = \lambda_ {1} \left[ \begin{array}{c} 3 \\ - 1 \\ 0 \\ 0 \\ 0 \end{array} \right] + \lambda_ {2} \left[ \begin{array}{c} 3 \\ 0 \\ 9 \\ - 4 \\ - 1 \end{array} \right], \quad \lambda_ {1}, \lambda_ {2} \in \mathbb {R} \right\}.\tag{2.50}
$$

### 2.3.3 减一技巧

下面介绍一种实用技巧，用于直接读出齐次线性方程组 $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{0}$ 的解 $\boldsymbol{x}$，其中 $\boldsymbol{A}\in\mathbb{R}^{k\times n}$，$\boldsymbol{x}\in\mathbb{R}^{n}$。

首先，假设 A 已经是简化行阶梯形，且不包含全零行，即

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c c c c c c c c c c c c} 0 & \dots & 0 & \mathbf {1} & * & \dots & * & 0 & * & \dots & * & 0 & * & \dots & * \\ \vdots & & \vdots & 0 & 0 & \dots & 0 & \mathbf {1} & * & \dots & * & \vdots & \vdots & & \vdots \\ \vdots & & \vdots & \vdots & \vdots & & \vdots & 0 & \vdots & & \vdots & \vdots & \vdots & & \vdots \\ \vdots & & \vdots & \vdots & \vdots & & \vdots & \vdots & \vdots & & \vdots & 0 & \vdots & & \vdots \\ 0 & \dots & 0 & 0 & 0 & \dots & 0 & 0 & 0 & \dots & 0 & \mathbf {1} & * & \dots & * \end{array} \right],\tag{2.51}
$$

其中，$*$ 可以是任意实数，但须满足：每行的第一个非零元素为 1，且它所在列的其他元素都为 0。包含主元（以粗体标出）的列 $j _ { 1 } , \dots , j _ { k }$ 是标准单位向量（standard unit vector）$e _ { 1 } , \ldots , e _ { k } \in \mathbb { R } ^ { k }$。通过添加 $n - k$ 行如下形式的行向量，将该矩阵扩展为 $n \times n$ 矩阵 $\tilde{\boldsymbol{A}}$：

$$
\left[ \begin{array}{c c c c c c c} 0 & \dots & 0 & - 1 & 0 & \dots & 0 \end{array} \right]\tag{2.52}
$$

使扩展后的矩阵 $\tilde { \boldsymbol { A } }$ 的对角线上只含 $1$ 或 $-1$。于是，$\tilde{\boldsymbol{A}}$ 中以 $-1$ 为主元的那些列，就是齐次方程组 $\mathbf { { \boldsymbol { A } } } \mathbf { { \boldsymbol { x } } } = \mathbf { { \boldsymbol { 0 } } }$ 的解。更准确地说，这些列构成了 $\mathbf { { \boldsymbol { A } } } \mathbf { { \boldsymbol { x } } } = \mathbf { { \boldsymbol { 0 } } }$ 的解空间的一组基（basis，见 2.6.1 节）。后面将把这个解空间称为核或零空间（kernel 或 null space，见 2.7.3 节）。

**例 2.8（减一技巧）**

重新考察式 (2.49) 中已经处于简化行阶梯形的矩阵：

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c c} 1 & 3 & 0 & 0 & 3 \\ 0 & 0 & 1 & 0 & 9 \\ 0 & 0 & 0 & 1 & - 4 \end{array} \right].\tag{2.53}
$$

现在，在对角线上缺少主元的位置插入式 (2.52) 形式的行，将它扩展为 $5 \times 5$ 矩阵，得到

$$
\tilde {\boldsymbol {A}} = \left[ \begin{array}{c c c c c} 1 & 3 & 0 & 0 & 3 \\ 0 & - \mathbf {1} & 0 & 0 & 0 \\ 0 & 0 & 1 & 0 & 9 \\ 0 & 0 & 0 & 1 & - 4 \\ 0 & 0 & 0 & 0 & - \mathbf {1} \end{array} \right].\tag{2.54}
$$

从这个形式可以立即读出 $\mathbf { A } \mathbf { { x } } = \mathbf { 0 }$ 的解：取 $\tilde{\boldsymbol{A}}$ 中对角元素为 $-1$ 的列即可，得到

$$
\left\{\boldsymbol {x} \in \mathbb {R} ^ {5}: \boldsymbol {x} = \lambda_ {1} \left[ \begin{array}{c} 3 \\ - 1 \\ 0 \\ 0 \\ 0 \end{array} \right] + \lambda_ {2} \left[ \begin{array}{c} 3 \\ 0 \\ 9 \\ - 4 \\ - 1 \end{array} \right], \quad \lambda_ {1}, \lambda_ {2} \in \mathbb {R} \right\},\tag{2.55}
$$

这与前面凭“观察”得到的式 (2.50) 完全一致。

#### 计算逆矩阵

为了计算 $\pmb { A } \in \mathbb { R } ^ { n \times n }$ 的逆 $A ^ { - 1 }$，需要找到满足 $A X \ = \ I _ { n }$ 的矩阵 X。此时，$\pmb { X } = \pmb { A } ^ { - 1 }$。可以将 $A X \ = \ I _ { n }$ 写成一组需要同时求解的线性方程组，求解对象为 $\pmb { X } = \left[ \pmb { x } _ { 1 } | \cdot \cdot \cdot | \pmb { x } _ { n } \right]$。使用增广矩阵记法，可以紧凑地表示这一组方程组：

$$
\left[ \boldsymbol {A} | \boldsymbol {I} _ {n} \right] \quad \rightsquigarrow \dots \rightsquigarrow \quad \left[ \boldsymbol {I} _ {n} | \boldsymbol {A} ^ {- 1} \right].\tag{2.56}
$$

也就是说，将增广方程组化为简化行阶梯形后，就可以在其右侧读出逆矩阵。因此，求矩阵的逆等价于求解线性方程组。

**例 2.9（通过高斯消元计算逆矩阵）**

为求矩阵

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c} 1 & 0 & 2 & 0 \\ 1 & 1 & 0 & 0 \\ 1 & 2 & 0 & 1 \\ 1 & 1 & 1 & 1 \end{array} \right]\tag{2.57}
$$

的逆，写出增广矩阵

$$
\left[ \begin{array}{rrrr|rrrr} 1 & 0 & 2 & 0 & 1 & 0 & 0 & 0 \\ 1 & 1 & 0 & 0 & 0 & 1 & 0 & 0 \\ 1 & 2 & 0 & 1 & 0 & 0 & 1 & 0 \\ 1 & 1 & 1 & 1 & 0 & 0 & 0 & 1 \end{array} \right]
$$

并通过高斯消元将其化为简化行阶梯形：

$$
\left[ \begin{array}{rrrr|rrrr} 1 & 0 & 0 & 0 & - 1 & 2 & - 2 & 2 \\ 0 & 1 & 0 & 0 & 1 & - 1 & 2 & - 2 \\ 0 & 0 & 1 & 0 & 1 & - 1 & 1 & - 1 \\ 0 & 0 & 0 & 1 & - 1 & 0 & - 1 & 2 \end{array} \right],
$$

所需的逆矩阵就是右侧部分：

$$
\boldsymbol {A} ^ {- 1} = \left[ \begin{array}{c c c c} - 1 & 2 & - 2 & 2 \\ 1 & - 1 & 2 & - 2 \\ 1 & - 1 & 1 & - 1 \\ - 1 & 0 & - 1 & 2 \end{array} \right].\tag{2.58}
$$

计算乘积 $\boldsymbol{A}\boldsymbol{A}^{-1}$ 并确认结果为 $\boldsymbol{I}_4$，即可验证式 (2.58) 确实是所求的逆矩阵。

### 2.3.4 求解线性方程组的算法

下面简要讨论求解 $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{b}$ 形式线性方程组的方法。我们假设解存在；如果无解，就需要寻求近似解，本章不讨论这种情况。一种求近似解的方法是线性回归，第 9 章将详细介绍。

某些特殊情况下，我们能够求出逆 $A ^ { - 1 }$，于是 $A x \ = \ b$ 的解为 $x = A ^ { - 1 } b$。但这要求 A 是可逆方阵，而实际中往往并非如此。否则，在较弱的假设下，即 A 的各列必须线性无关（linearly independent），可以进行如下变换：

$$
\boldsymbol {A} \boldsymbol {x} = \boldsymbol {b} \iff \boldsymbol {A} ^ {\top} \boldsymbol {A} \boldsymbol {x} = \boldsymbol {A} ^ {\top} \boldsymbol {b} \iff \boldsymbol {x} = (\boldsymbol {A} ^ {\top} \boldsymbol {A}) ^ {- 1} \boldsymbol {A} ^ {\top} \boldsymbol {b}\tag{2.59}
$$

并使用 Moore–Penrose 伪逆（Moore–Penrose pseudo-inverse）$( A ^ { \top } A ) ^ { - 1 } A ^ { \top }$，求得满足 $\mathbf { { A } } \mathbf { { x } } = \mathbf { { b } }$ 的解 (2.59)，它也对应最小范数最小二乘解（minimum norm least-squares solution）。这种方法的缺点是，矩阵与矩阵相乘以及计算 $A ^ { \top } A$ 的逆，都需要大量计算。此外，出于数值精度的考虑，通常不建议显式计算逆或伪逆。因此，下面简要讨论求解线性方程组的其他方法。

高斯消元在计算行列式（4.1 节）、判断一组向量是否线性无关（2.5 节）、求矩阵的逆（2.2.2 节）、计算矩阵的秩（rank，2.6.2 节），以及确定向量空间的一组基（2.6.1 节）时，都起重要作用。对于包含数千个变量的线性方程组，高斯消元是一种直观且具有构造性的求解方法。但对于包含数百万个变量的方程组，它并不实用，因为所需算术运算的次数随联立方程数量的三次方增长。

实际中，大型线性方程组往往通过间接方法求解。一类是定常迭代法（stationary iterative method），例如 Richardson 法、Jacobi 法、Gauss–Seidel 法和逐次超松弛法（successive over-relaxation）；另一类是 Krylov 子空间法（Krylov subspace method），例如共轭梯度法（conjugate gradients）、广义极小残量法（generalized minimal residual）和双共轭梯度法（biconjugate gradients）。更多细节可参阅 Stoer and Burlirsch（2002）、Strang（2003）及 Liesen and Mehrmann（2015）的著作。

设 $\boldsymbol{x}_*$ 是 $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{b}$ 的一个解。这些迭代方法的核心思想是构造以下形式的迭代：

$$
\pmb {x} ^ {(k + 1)} = \pmb {C x} ^ {(k)} + \pmb {d}\tag{2.60}
$$

其中选取合适的 C 和 d，使每次迭代都减小残差误差 $\| \pmb { x } ^ { ( k + 1 ) } - \pmb { x } _ { * } \|$，并收敛到 ${ \pmb x } _ { \ast }$。3.1 节将介绍范数（norm）$\|\cdot\|$，它使我们能够计算向量之间的相似性。

> 译注：原文在这里使用 residual error 一词，但所列公式度量的是迭代值与真解之间的误差；通常所说的残差则是方程右端与当前矩阵乘积之差。这里保留原文公式与叙述，并标明这一术语差别。

## 2.4 向量空间

前面已经讨论了线性方程组及其求解方法（2.3 节），并看到线性方程组可以用矩阵与向量记法紧凑地表示，见式 (2.10)。下面进一步考察向量空间，也就是向量所在的、具有一定结构的空间。

本章开头曾非正式地描述向量：它们可以相加，也可以与标量相乘，结果仍是同类对象。现在可以将这一描述形式化了。我们先介绍群（group）的概念：群由一组元素及其上的运算组成，这种运算保持了集合的某些结构。

### 2.4.1 群

群在计算机科学中起重要作用。它不仅为集合上的运算提供基本框架，还广泛用于密码学、编码理论和图形学。

**定义 2.7（群）。** 考虑集合 $\mathcal { G }$ 及定义在 $\mathcal { G }$ 上的运算 $\otimes : { \mathcal { G } } \times { \mathcal { G } } \to { \mathcal { G } }$。如果满足以下条件，就称 $G : = ( \mathcal { G } , \otimes )$ 为群：

1. $\mathcal{G}$ 对 $\otimes$ 封闭：$\forall x,y\in\mathcal{G}:x\otimes y\in\mathcal{G}$。
2. 结合律：$\forall x,y,z\in\mathcal{G}:(x\otimes y)\otimes z=x\otimes(y\otimes z)$。
3. 单位元（neutral element）：$\exists e\in\mathcal{G}\ \forall x\in\mathcal{G}:x\otimes e=x$，且 $e\otimes x=x$。
4. 逆元（inverse element）：$\forall x\in\mathcal{G}\ \exists y\in\mathcal{G}:x\otimes y=e$，且 $y\otimes x=e$，其中 $e$ 是单位元。通常用 $x^{-1}$ 表示 $x$ 的逆元。

**注。** 逆元是相对于运算 $\otimes$ 定义的，不一定表示 $\textstyle { \frac { 1 } { x } }$。$\diamondsuit$

如果还满足 $\forall x,y\in\mathcal{G}:x\otimes y=y\otimes x$，那么 $G = ( \mathcal { G } , \otimes )$ 就是阿贝尔群（Abelian group），也称交换群。

**例 2.10（群）**

下面考察一些集合及其上的运算，判断它们是否构成群：

- $( \mathbb { Z } , + )$ 是阿贝尔群。

> $\mathbb{N}_0:=\mathbb{N}\cup\{0\}$。

- $( \mathbb { N } _ { 0 } , + )$ 不是群：虽然 $( \mathbb { N } _ { 0 } , + )$ 有单位元 0，但缺少逆元。

- $( \mathbb { Z } , \cdot )$ 不是群：虽然 $( \mathbb { Z } , \cdot )$ 有单位元 1，但对任意 $z \in \mathbb { Z } , z \neq \pm 1$，都不存在逆元。

- $(\mathbb{R},\cdot)$ 不是群，因为 0 没有逆元。

- $( \mathbb { R } \backslash \{ 0 \} , \cdot )$ 是阿贝尔群。

- 如果加法 + 按分量定义，那么 $( \mathbb { R } ^ { n } , + ) , ( \mathbb { Z } ^ { n } , + ) , n \in \mathbb { N }$ 都是阿贝尔群。这里的按分量相加是指

$$
\left(x _ {1}, \dots , x _ {n}\right) + \left(y _ {1}, \dots , y _ {n}\right) = \left(x _ {1} + y _ {1}, \dots , x _ {n} + y _ {n}\right).\tag{2.61}
$$

此时，$( x _ { 1 } , \cdot \cdot \cdot , x _ { n } ) ^ { - 1 } : = ( - x _ { 1 } , \cdot \cdot \cdot , - x _ { n } )$ 是逆元，$e = ( 0 , \cdots , 0 )$ 是单位元。

- 由 $m\times n$ 矩阵组成的 $\left( \mathbb { R } ^ { m \times n } , + \right)$ 是阿贝尔群，加法按式 (2.61) 逐分量定义。

- 再仔细考察 $( \mathbb { R } ^ { n \times n } , \cdot )$，即由 $n\times n$ 矩阵组成的集合，运算采用式 (2.13) 定义的矩阵乘法。

  - 封闭性与结合律可直接由矩阵乘法的定义得到。

  - 单位元：单位矩阵 $\mathcal{I}_{n}$ 是 $( \mathbb { R } ^ { n \times n } , \cdot )$ 中矩阵乘法“$\cdot$”的单位元。

  - 逆元：如果逆存在，即 A 是正则矩阵，那么 $A ^ { - 1 }$ 就是 $A \in \mathbb { R } ^ { n \times n }$ 的逆元。原文称，恰在这种情况下，$( \mathbb { R } ^ { n \times n } , \cdot )$ 是一个群，称为一般线性群。

> 译注：上段保留了原文的集合记号。群的集合应限定为可逆矩阵；全部方阵中包含不可逆矩阵，因此全部方阵在乘法下不构成群。紧接着的定义 2.8 给出了可逆性限制。

**定义 2.8（一般线性群）。** 所有正则（可逆）矩阵 $\pmb { A } \in \mathbb { R } ^ { n \times n }$ 组成的集合，在式 (2.13) 定义的矩阵乘法下构成群，称为一般线性群（general linear group）$G L ( n , \mathbb { R } )$。不过，由于矩阵乘法不满足交换律，该群不是阿贝尔群。

> 译注：此处“不是阿贝尔群”的表述适用于阶数至少为 2 的情形；阶数为 1 时，一般线性群就是非零实数的乘法群，是阿贝尔群。原文未在此句中注明这一边界。

### 2.4.2 向量空间

讨论群时，我们考察了集合 $\mathcal { G }$ 及 $\mathcal{G}$ 上的内部运算（inner operation），即只作用于 $\mathcal{G}$ 中元素的映射 ${ \mathcal { G } } \times { \mathcal { G } } \to { \mathcal { G } }$。下面考察的集合，除了内部运算 $+$，还具有外部运算（outer operation）$\cdot$，即将向量 $\boldsymbol { x } \in \mathcal G$ 与标量 $\lambda \in \mathbb { R }$ 相乘。可以把内部运算理解为某种加法，把外部运算理解为某种缩放。注意，内部／外部运算与内积／外积没有关系。

**定义 2.9（向量空间）。** 实向量空间 $V=(\mathcal{V},+,\cdot)$ 由集合 $\mathcal{V}$ 及以下两种运算组成：

$$
+: \mathcal {V} \times \mathcal {V} \rightarrow \mathcal {V}\tag{2.62}
$$

$$
\cdot : \mathbb {R} \times \mathcal {V} \to \mathcal {V}\tag{2.63}
$$

其中，

1. $(\mathcal{V},+)$ 是阿贝尔群。
2. 分配律：
   1. $\forall\lambda\in\mathbb{R},\boldsymbol{x},\boldsymbol{y}\in\mathcal{V}:\lambda\cdot(\boldsymbol{x}+\boldsymbol{y})=\lambda\cdot\boldsymbol{x}+\lambda\cdot\boldsymbol{y}$。
   2. $\forall\lambda,\psi\in\mathbb{R},\boldsymbol{x}\in\mathcal{V}:(\lambda+\psi)\cdot\boldsymbol{x}=\lambda\cdot\boldsymbol{x}+\psi\cdot\boldsymbol{x}$。
3. 结合律（外部运算）：$\forall\lambda,\psi\in\mathbb{R},\boldsymbol{x}\in\mathcal{V}:\lambda\cdot(\psi\cdot\boldsymbol{x})=(\lambda\psi)\cdot\boldsymbol{x}$。
4. 外部运算的单位元性质：$\forall\boldsymbol{x}\in\mathcal{V}:1\cdot\boldsymbol{x}=\boldsymbol{x}$。

元素 $\boldsymbol{x}\in\mathcal{V}$ 称为向量。$(\mathcal{V},+)$ 的单位元是零向量 $\boldsymbol{0}=[0,\ldots,0]^{\top}$，内部运算 $+$ 称为向量加法。元素 $\lambda\in\mathbb{R}$ 称为标量，外部运算 $\cdot$ 是标量乘法。注意，标量积（scalar product）是另一回事，将在 3.2 节介绍。

**注。** 对 $\boldsymbol{a},\boldsymbol{b}\in\mathbb{R}^{n}$，这里并未定义“向量乘法”$\boldsymbol{a}\boldsymbol{b}$。理论上可以定义逐元素乘法，使 $\boldsymbol{c}=\boldsymbol{a}\boldsymbol{b}$，其中 $c_j=a_jb_j$。许多编程语言都使用这种“数组乘法”，但从标准矩阵乘法规则看，它的数学意义有限：通常我们将向量看作 $n\times1$ 矩阵，因此可以考虑式 (2.13) 定义的矩阵乘法，但两个向量的维度此时并不匹配。这里定义的向量乘法只有以下两种：$\boldsymbol{a}\boldsymbol{b}^{\top}\in\mathbb{R}^{n\times n}$，即外积（outer product）；$\boldsymbol{a}^{\top}\boldsymbol{b}\in\mathbb{R}$，即内积／标量积／点积（inner/scalar/dot product）。

**例 2.11（向量空间）**

下面来看一些重要例子：

- $\mathcal{V}=\mathbb{R}^{n}$、$n\in\mathbb{N}$ 是向量空间，其运算定义如下：
  - 加法：对所有 $\boldsymbol{x},\boldsymbol{y}\in\mathbb{R}^{n}$，有 $\boldsymbol{x}+\boldsymbol{y}=(x_1,\ldots,x_n)+(y_1,\ldots,y_n)=(x_1+y_1,\ldots,x_n+y_n)$。
  - 标量乘法：对所有 $\lambda\in\mathbb{R}$、$\boldsymbol{x}\in\mathbb{R}^{n}$，有 $\lambda\boldsymbol{x}=\lambda(x_1,\ldots,x_n)=(\lambda x_1,\ldots,\lambda x_n)$。
- $\mathcal{V}=\mathbb{R}^{m\times n}$、$m,n\in\mathbb{N}$ 是向量空间，其运算为：
  - 加法：对所有 $\boldsymbol{A},\boldsymbol{B}\in\mathcal{V}$，逐元素定义 $\boldsymbol{A}+\boldsymbol{B}=\begin{bmatrix}a_{11}+b_{11}&\cdots&a_{1n}+b_{1n}\\\vdots&&\vdots\\a_{m1}+b_{m1}&\cdots&a_{mn}+b_{mn}\end{bmatrix}$。
  - 标量乘法：$\lambda\boldsymbol{A}=\begin{bmatrix}\lambda a_{11}&\cdots&\lambda a_{1n}\\\vdots&&\vdots\\\lambda a_{m1}&\cdots&\lambda a_{mn}\end{bmatrix}$，如 2.2 节所定义。请记住，$\mathbb{R}^{m\times n}$ 与 $\mathbb{R}^{mn}$ 等价。
- $\mathcal{V}=\mathbb{C}$，加法采用复数加法的标准定义。

**注。** 下面，当 $+$ 和 $\cdot$ 分别表示标准向量加法和标量乘法时，将向量空间 $(\mathcal{V},+,\cdot)$ 简记为 $V$。此外，为简化记法，用 $\boldsymbol{x}\in V$ 表示 $\mathcal{V}$ 中的向量。

**注。** 向量空间 $\mathbb { R } ^ { n } , \mathbb { R } ^ { n \times 1 } , \mathbb { R } ^ { 1 \times n }$ 仅在向量的书写方式上有所不同。下面不区分 $\mathbb { R } ^ { n }$ 和 $\mathbb { R } ^ { n \times 1 }$，这样就可以将 n 元组写成列向量：

$$
\boldsymbol {x} = \left[ \begin{array}{c} x _ {1} \\ \vdots \\ x _ {n} \end{array} \right].\tag{2.64}
$$

这简化了向量空间运算的记法。不过，为避免矩阵乘法中的混淆，仍然区分 $\mathbb { R } ^ { n \times 1 }$ 与 $\mathbb { R } ^ { 1 \times n }$，后者表示行向量。默认用 $\boldsymbol{x}$ 表示列向量，用它的转置 $\pmb { x } ^ { \top }$ 表示行向量，即 $\boldsymbol{x}$ 的转置。

### 2.4.3 向量子空间

下面介绍向量子空间（vector subspace）。直观地说，它是原向量空间所包含的一个集合，具有如下性质：对其中的元素进行向量空间运算，结果始终留在这个集合内。在这一意义上，它是“封闭的”。向量子空间是机器学习中的一个关键概念。例如，第 10 章将展示如何利用向量子空间进行降维。

**定义 2.10（向量子空间）。** 设 $V=(\mathcal{V},+,\cdot)$ 是向量空间，且 $\mathcal { U } \subseteq \mathcal { V } , \mathcal { U } \neq \emptyset$。将向量空间运算 $+$ 和 $\cdot$ 分别限制在 $\mathcal{U}\times\mathcal{U}$ 与 $\mathbb { R } \times \mathcal { U }$ 上，如果 $U = ( \mathcal { U } , + , \cdot )$ 仍为向量空间，就称其为 $V$ 的向量子空间，也称线性子空间（linear subspace）。用 $U \subseteq V$ 表示 U 是 V 的子空间。

如果 $\mathcal { U } \subseteq \mathcal { V }$ 且 V 是向量空间，那么 U 会自然地直接继承 V 的许多性质，因为这些性质对所有 $\boldsymbol{x}\in\mathcal{V}$ 成立，特别地，也对所有 $\pmb { x } \in \mathcal { U } \subseteq \mathcal { V }$ 成立。这包括阿贝尔群的性质、分配律、结合律和单位元。要判断 $(\mathcal{U},+,\cdot)$ 是否为 V 的子空间，仍需证明：

1. $\mathcal { U } \neq \emptyset$，特别是 $\mathbf { 0 } \in \mathcal { U }$。

2. $U$ 的封闭性：

   - 对外部运算封闭：$\forall \lambda \in \mathbb { R } \forall x \in \mathcal { U } : \lambda \pmb { x } \in \mathcal { U }$。

   - 对内部运算封闭：$\forall x , y \in \mathcal { U } : x + y \in \mathcal { U }$。

**例 2.12（向量子空间）**

下面来看一些例子：

- 对任意向量空间 $V$，平凡子空间（trivial subspace）是 $V$ 本身和 $\{\boldsymbol{0}\}$。

- 图 2.6 中只有 D 是 $\mathbb { R } ^ { 2 }$ 的子空间，这里采用通常的内部与外部运算。A 和 C 不满足封闭性，B 不包含 0。

- 含 n 个未知数 $\pmb { x } = [ x _ { 1 } , \ldots , x _ { n } ] ^ { \top }$ 的齐次线性方程组 $\mathbf { A } \mathbf { { x } } = \mathbf { 0 }$ 的解集是 $\mathbb { R } ^ { n }$ 的子空间。

- 非齐次线性方程组（inhomogeneous system）$\boldsymbol{A}\boldsymbol{x}=\boldsymbol{b}$、$\boldsymbol{b}\neq\boldsymbol{0}$ 的解集不是 $\mathbb{R}^{n}$ 的子空间。

- 任意多个子空间的交集仍是子空间。

![图 2.6：子空间与非子空间](<Images/02_Linear_Algebra_image_008.jpg>)

图 2.6 并非 $\mathbb{R}^{2}$ 的所有子集都是子空间。A 和 C 不满足封闭性，B 不包含 0，只有 D 是子空间。

**注。** 每个子空间 $U \subseteq ( \mathbb { R } ^ { n } , + , \cdot )$ 都是某个齐次线性方程组 $\pmb { A } \pmb { x } = \mathbf { 0 }$ 的解空间，其中 $\pmb { x } \in \mathbb { R } ^ { n }$。◇

## 2.5 线性无关

下面仔细考察可以对向量，也就是向量空间中的元素，进行哪些操作。特别地，向量可以相加，也可以与标量相乘。封闭性保证结果仍是同一向量空间中的向量。可以找到一组向量，通过相加和缩放表示向量空间中的每个向量。这样一组向量就是一组基，将在 2.6.1 节讨论。在此之前，需要先介绍线性组合与线性无关（linear independence）的概念。

> 译注：这里是原文的直观引入。能表示空间中每个向量的集合是生成集；要成为基，还需线性无关。严格定义见 2.6.1 节。

**定义 2.11（线性组合）。** 考虑向量空间 V 及有限个向量 $\pmb { x } _ { 1 } , \dotsc , \pmb { x } _ { k } \in V$。对于 $\boldsymbol{v}\in V$，如果它具有以下形式：

$$
\boldsymbol {v} = \lambda_ {1} \boldsymbol {x} _ {1} + \dots + \lambda_ {k} \boldsymbol {x} _ {k} = \sum_ {i = 1} ^ {k} \lambda_ {i} \boldsymbol {x} _ {i} \in V\tag{2.65}
$$

其中 $\lambda _ { 1 } , \ldots , \lambda _ { k } \in \mathbb { R }$，就称它为向量 $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ 的线性组合。

零向量总能写成 k 个向量 $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ 的线性组合，因为 $\boldsymbol{0}=\sum_{i=1}^{k}0\boldsymbol{x}_i$ 恒成立。下面关注的是，用一组向量的非平凡线性组合表示 0：也就是用向量 $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ 作线性组合，且式 (2.65) 中的系数 $\lambda_i$ 不全为 0。

**定义 2.12（线性相关与线性无关）。** 考虑向量空间 V，设 $k \in \mathbb { N }$ 且 $\pmb { x } _ { 1 } , \dotsc , \pmb { x } _ { k } \in V$。如果存在非平凡线性组合，使 $\boldsymbol{0}=\sum_{i=1}^{k}\lambda_i\boldsymbol{x}_i$，其中至少有一个 $\lambda _ { i } \neq 0$，就称向量 $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ 线性相关（linearly dependent）。如果只有平凡解，即 $\lambda_1=\cdots=\lambda_k=0$，则称向量 $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ 线性无关（linearly independent）。

线性无关是线性代数中最重要的概念之一。直观地说，一组线性无关的向量不存在冗余：移除其中任何一个向量，都会有所损失。接下来的几节将进一步形式化这一认识。

**例 2.13（线性相关的向量）**

一个地理例子有助于说明线性无关的概念。肯尼亚内罗毕的一位居民在描述卢旺达基加利的位置时，可能会说：“先向西北走 506 公里到乌干达坎帕拉，再向西南走 374 公里，就能到基加利。”这些信息足以描述基加利的位置，因为忽略海拔和地球表面曲率后，可以将地理坐标系视为二维向量空间。他还可能补充：“它在这里以西约 751 公里。”虽然这句话是正确的，但有了前面的信息，就不需要它来确定基加利的位置了，见图 2.7。在这个例子中，“向西北 506 公里”的向量（蓝色）与“向西南 374 公里”的向量（紫色）线性无关。这意味着西南方向的向量不能用西北方向的向量表示，反之亦然。然而，第三个“向西 751 公里”的向量（黑色）是前两个向量的线性组合，因而使这组向量线性相关。等价地，给定“向西 751 公里”和“向西南 374 公里”，也可以通过线性组合得到“向西北 506 公里”。

![图 2.7：地理位置与线性相关向量](<Images/02_Linear_Algebra_image_009.jpg>)

图 2.7 二维空间（平面）中线性相关向量的地理例子，方位仅作粗略近似。图内主要标签：Nairobi——内罗毕；Kampala——坎帕拉；Kigali——基加利；Northwest——西北；Southwest——西南；West——西。

**注。** 以下性质有助于判断向量是否线性无关：

- k 个向量要么线性相关，要么线性无关，没有第三种情况。

- 如果向量 $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ 中至少有一个是 $\boldsymbol{0}$，那么它们线性相关。如果其中两个向量相同，结论也一样。

- 向量 $\{ \pmb { x } _ { 1 } , \dots , \pmb { x } _ { k } : \pmb { x } _ { i } \neq \pmb { 0 } , i = 1 , \dots , k \} , k\geqslant2$ 线性相关，当且仅当其中至少一个向量是其余向量的线性组合。特别地，如果一个向量是另一个向量的倍数，即 $\pmb { x } _ { i } = \lambda \pmb { x } _ { j } , \lambda \in \mathbb { R }$，则集合 $\{ \pmb { x } _ { 1 } , \dots , \pmb { x } _ { k } : \pmb { x } _ { i } \neq \mathbf { 0 } , i = 1 , \dots , k \}$ 线性相关。

- 判断向量 $\pmb { x } _ { 1 } , \dotsc , \pmb { x } _ { k } \in V$ 是否线性无关的一种实用方法是高斯消元：将所有向量作为列排成矩阵 A，进行高斯消元，直到矩阵变为行阶梯形；此处不需要化为简化行阶梯形。

  - 主元列所对应的向量，相对于其左侧向量是线性无关的。注意，将向量组成矩阵时已经赋予它们一个顺序。

  - 非主元列可以表示为其左侧主元列的线性组合。例如，行阶梯形

    $$
    \left[ \begin{array}{c c c} 1 & 3 & 0 \\ 0 & 0 & 2 \end{array} \right]\tag{2.66}
    $$

    表明第一列和第三列是主元列。第二列是非主元列，因为它是第一列的 3 倍。

  所有列向量线性无关，当且仅当每一列都是主元列。如果至少存在一个非主元列，这些列及其对应的向量就线性相关。

**例 2.14**

考虑 $\mathbb { R } ^ { 4 }$ 中的向量

$$
\boldsymbol {x} _ {1} = \left[ \begin{array}{c} 1 \\ 2 \\ - 3 \\ 4 \end{array} \right], \quad \boldsymbol {x} _ {2} = \left[ \begin{array}{c} 1 \\ 1 \\ 0 \\ 2 \end{array} \right], \quad \boldsymbol {x} _ {3} = \left[ \begin{array}{c} - 1 \\ - 2 \\ 1 \\ 1 \end{array} \right].\tag{2.67}
$$

为判断它们是否线性相关，按照一般方法求解

$$
\lambda_ {1} \boldsymbol {x} _ {1} + \lambda_ {2} \boldsymbol {x} _ {2} + \lambda_ {3} \boldsymbol {x} _ {3} = \lambda_ {1} \left[ \begin{array}{c} 1 \\ 2 \\ - 3 \\ 4 \end{array} \right] + \lambda_ {2} \left[ \begin{array}{c} 1 \\ 1 \\ 0 \\ 2 \end{array} \right] + \lambda_ {3} \left[ \begin{array}{c} - 1 \\ - 2 \\ 1 \\ 1 \end{array} \right] = \mathbf {0}\tag{2.68}
$$

中的 $\lambda _ { 1 } , \ldots , \lambda _ { 3 }$。将向量 $\boldsymbol{x}_i$、$i=1,2,3$ 作为列组成矩阵，并进行初等行变换，直至识别出主元列：

$$
\left[\begin{array}{c c c}1&1&- 1\\2&1&- 2\\- 3&0&1\\4&2&1\end{array}\right] \quad \rightsquigarrow \dots \rightsquigarrow \quad \left[\begin{array}{c c c}1&1&- 1\\0&1&0\\0&0&1\\0&0&0\end{array}\right].\tag{2.69}
$$

这里，矩阵的每一列都是主元列。因此不存在非平凡解，要满足方程组，必须有 $\lambda _ { 1 } = 0 , \lambda _ { 2 } = 0 , \lambda _ { 3 } = 0$。所以，向量 ${ \pmb x } _ { 1 } , { \pmb x } _ { 2 } , { \pmb x } _ { 3 }$ 线性无关。

**注。** 考虑向量空间 V 中 k 个线性无关的向量 $\boldsymbol { b } _ { 1 } , \ldots , \boldsymbol { b } _ { k }$，以及它们的 m 个线性组合

$$
\begin{aligned}
\boldsymbol{x}_1&=\sum_{i=1}^{k}\lambda_{i1}\boldsymbol{b}_i,\\
&\vdots\\
\boldsymbol{x}_m&=\sum_{i=1}^{k}\lambda_{im}\boldsymbol{b}_i.
\end{aligned}
\tag{2.70}
$$

将以线性无关向量 $b _ { 1 } , \ldots , b _ { k }$ 为列的矩阵定义为 $\boldsymbol{B}=[\boldsymbol{b}_1,\ldots,\boldsymbol{b}_k]$，则可以写成

$$
\boldsymbol {x} _ {j} = \boldsymbol {B} \boldsymbol {\lambda} _ {j}, \quad \boldsymbol {\lambda} _ {j} = \left[ \begin{array}{c} \lambda_ {1 j} \\ \vdots \\ \lambda_ {k j} \end{array} \right], \quad j = 1, \ldots , m,\tag{2.71}
$$

这一更紧凑的形式。

我们要检验 $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { m }$ 是否线性无关。为此，按一般方法考察 $\sum_{j=1}^{m}\psi_j\boldsymbol{x}_j=\boldsymbol{0}$ 何时成立。利用式 (2.71)，得到

$$
\sum_ {j = 1} ^ {m} \psi_ {j} \boldsymbol {x} _ {j} = \sum_ {j = 1} ^ {m} \psi_ {j} \boldsymbol {B} \boldsymbol {\lambda} _ {j} = \boldsymbol {B} \sum_ {j = 1} ^ {m} \psi_ {j} \boldsymbol {\lambda} _ {j}.\tag{2.72}
$$

这意味着，$\{ \pmb { x } _ { 1 } , \ldots , \pmb { x } _ { m } \}$ 线性无关，当且仅当列向量 $\{\boldsymbol{\lambda}_1,\ldots,\boldsymbol{\lambda}_m\}$ 线性无关。

**注。** 在向量空间 $V$ 中，k 个向量 $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ 的 m 个线性组合，在 $m>k$ 时必然线性相关。

**例 2.15**

考虑一组线性无关的向量 $b _ { 1 } , b _ { 2 } , b _ { 3 } , b _ { 4 } \in \mathbb { R } ^ { n }$，以及

$$
\begin{array}{r c l r c l r c l} \boldsymbol {x} _ {1} & = & \boldsymbol {b} _ {1} & - & 2 \boldsymbol {b} _ {2} & + & \boldsymbol {b} _ {3} & - & \boldsymbol {b} _ {4} \\ \boldsymbol {x} _ {2} & = & - 4 \boldsymbol {b} _ {1} & - & 2 \boldsymbol {b} _ {2} & & & + & 4 \boldsymbol {b} _ {4} \\ \boldsymbol {x} _ {3} & = & 2 \boldsymbol {b} _ {1} & + & 3 \boldsymbol {b} _ {2} & - & \boldsymbol {b} _ {3} & - & 3 \boldsymbol {b} _ {4} \\ \boldsymbol {x} _ {4} & = & 17 \boldsymbol {b} _ {1} & - & 10 \boldsymbol {b} _ {2} & + & 11 \boldsymbol {b} _ {3} & + & \boldsymbol {b} _ {4} \end{array} .\tag{2.73}
$$

向量 $\pmb { x } _ { 1 } , \dotsc , \pmb { x } _ { 4 } \in \mathbb { R } ^ { n }$ 是否线性无关？为回答这个问题，我们考察下面这些列向量

$$
\left\{\left[ \begin{array}{c} 1 \\ - 2 \\ 1 \\ - 1 \end{array} \right], \left[ \begin{array}{c} - 4 \\ - 2 \\ 0 \\ 4 \end{array} \right], \left[ \begin{array}{c} 2 \\ 3 \\ - 1 \\ - 3 \end{array} \right], \left[ \begin{array}{c} 17 \\ - 10 \\ 11 \\ 1 \end{array} \right] \right\}\tag{2.74}
$$

是否线性无关。相应线性方程组的系数矩阵为

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c} 1 & - 4 & 2 & 17 \\ - 2 & - 2 & 3 & - 10 \\ 1 & 0 & - 1 & 11 \\ - 1 & 4 & - 3 & 1 \end{array} \right]\tag{2.75}
$$

其简化行阶梯形为

$$
\left[ \begin{array}{c c c c} 1 & 0 & 0 & - 7 \\ 0 & 1 & 0 & - 15 \\ 0 & 0 & 1 & - 18 \\ 0 & 0 & 0 & 0 \end{array} \right].\tag{2.76}
$$

可以看到，相应的线性方程组存在非平凡解：最后一列不是主元列，且 $\pmb { x } _ { 4 } = - 7 \pmb { x } _ { 1 } - 15 \pmb { x } _ { 2 } - 18 \pmb { x } _ { 3 }$。因此，$\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { 4 }$ 线性相关，因为 $\mathbf { x } _ { 4 }$ 可以表示为 $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { 3 }$ 的线性组合。

## 2.6 基与秩

在向量空间 $V$ 中，我们特别关注具有以下性质的向量集合 $\mathcal { A }$：任意向量 $v \in V$ 都能表示为 ${ \mathcal { A } }$ 中向量的线性组合。这些向量具有特殊作用，下面将刻画它们。

### 2.6.1 生成集与基

**定义 2.13（生成集与张成空间）。** 考虑向量空间 $V=(\mathcal{V},+,\cdot)$ 和向量集合 $\mathcal{A}=\{\boldsymbol{x}_1,\ldots,\boldsymbol{x}_k\}\subseteq\mathcal{V}$。如果每个向量 $\boldsymbol{v}\in\mathcal{V}$ 都能表示为 $\boldsymbol{x}_1,\ldots,\boldsymbol{x}_k$ 的线性组合，就称 $\mathcal{A}$ 为 $V$ 的生成集（generating set）。$\mathcal{A}$ 中向量的全部线性组合构成的集合，称为 $\mathcal{A}$ 的张成空间（span）。如果 $\mathcal{A}$ 张成向量空间 $V$，记作 $V=\operatorname{span}[\mathcal{A}]$ 或 $V=\operatorname{span}[\boldsymbol{x}_1,\ldots,\boldsymbol{x}_k]$。

生成集是一组张成向量空间或子空间的向量，也就是说，空间中的每个向量都能表示为生成集中向量的线性组合。下面进一步刻画能够张成向量空间或子空间的最小生成集。

**定义 2.14（基）。** 考虑向量空间 $V=(\mathcal{V},+,\cdot)$，以及 $\mathcal{A}\subseteq\mathcal{V}$。如果不存在更小的集合 $\tilde{\mathcal{A}}\subsetneq\mathcal{A}\subseteq\mathcal{V}$ 仍能张成 $V$，就称 $V$ 的生成集 $\mathcal{A}$ 是极小的（minimal）。$V$ 的每个线性无关生成集都是极小生成集，称为 $V$ 的一组基。

设 $V=(\mathcal{V},+,\cdot)$ 是向量空间，且 $\mathcal{B}\subseteq\mathcal{V}$、$\mathcal{B}\neq\emptyset$。以下命题等价：

- $\mathcal{B}$ 是 $V$ 的一组基。

- $\mathcal{B}$ 是极小生成集。

- $\mathcal{B}$ 是 $V$ 中极大的线性无关向量集，即向其中加入任何其他向量，都会使该集合线性相关。

- 每个向量 $\boldsymbol{x}\in V$ 都是 $\mathcal{B}$ 中向量的线性组合，且这种表示唯一。也就是说，如果

$$
\boldsymbol {x} = \sum_ {i = 1} ^ {k} \lambda_ {i} \boldsymbol {b} _ {i} = \sum_ {i = 1} ^ {k} \psi_ {i} \boldsymbol {b} _ {i}\tag{2.77}
$$

其中 $\lambda _ { i } , \psi _ { i } \in \mathbb { R } , b _ { i } \in \mathcal { B }$，那么必有 $\lambda _ { i } = \psi _ { i } , i = 1 , \ldots , k$。

> 基既是极小生成集，也是极大的线性无关向量集。

**例 2.16**

- 在 $\mathbb { R } ^ { 3 }$ 中，典范基／标准基（canonical/standard basis）为

  $$
  \mathcal {B} = \left\{\left[ \begin{array}{c} 1 \\ 0 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 0 \\ 1 \end{array} \right] \right\}.\tag{2.78}
  $$

- $\mathbb { R } ^ { 3 }$ 中其他不同的基还有

  $$
  \mathcal {B} _ {1} = \left\{\left[ \begin{array}{l} 1 \\ 0 \\ 0 \end{array} \right], \left[ \begin{array}{l} 1 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{l} 1 \\ 1 \\ 1 \end{array} \right] \right\}, \mathcal {B} _ {2} = \left\{\left[ \begin{array}{l} 0.5 \\ 0.8 \\ 0.4 \end{array} \right], \left[ \begin{array}{l} 1.8 \\ 0.3 \\ 0.3 \end{array} \right], \left[ \begin{array}{l} - 2.2 \\ - 1.3 \\ 3.5 \end{array} \right] \right\}.\tag{2.79}
  $$

- 集合

  $$
  \mathcal {A} = \left\{\left[ \begin{array}{c} 1 \\ 2 \\ 3 \\ 4 \end{array} \right], \left[ \begin{array}{c} 2 \\ - 1 \\ 0 \\ 2 \end{array} \right], \left[ \begin{array}{c} 1 \\ 1 \\ 0 \\ - 4 \end{array} \right] \right\}\tag{2.80}
  $$

  线性无关，但不是 $\mathbb{R}^{4}$ 的生成集，因此也不是它的一组基。例如，向量 $[1,0,0,0]^{\top}$ 就不能表示为 $\mathcal{A}$ 中元素的线性组合。

**注。** 每个向量空间 $V$ 都有一组基 $\mathcal{B}$。前面的例子表明，向量空间 $V$ 可以有许多不同的基，基并不唯一。不过，所有基包含的元素，即基向量，数量相同。

我们只考虑有限维向量空间 $V$。此时，$V$ 的维数（dimension）就是 $V$ 的基向量个数，记作 $\dim(V)$。如果 $U\subseteq V$ 是 $V$ 的子空间，那么 $\dim(U)\leq\dim(V)$，并且 $\dim(U)=\dim(V)$ 当且仅当 $U=V$。直观地说，向量空间的维数可以理解为空间中独立方向的数量。

> 向量空间的维数对应于它的基向量个数。

**注。** 向量空间的维数不一定等于一个向量中的元素个数。例如，向量空间 $V=\operatorname{span}\left[\begin{bmatrix}0\\1\end{bmatrix}\right]$ 是一维的，虽然它的基向量包含两个元素。

**注。** 可以通过以下步骤求子空间 $U=\operatorname{span}[\boldsymbol{x}_1,\ldots,\boldsymbol{x}_m]\subseteq\mathbb{R}^{n}$ 的一组基：

1. 将张成向量作为列组成矩阵 $\boldsymbol{A}$。

2. 求 A 的行阶梯形。

3. 与主元列对应的原张成向量，构成 $U$ 的一组基。

**例 2.17（确定一组基）**

设向量子空间 $U \subseteq \mathbb { R } ^ { 5 }$ 由以下向量张成：

$$
\boldsymbol {x} _ {1} = \left[ \begin{array}{c} 1 \\ 2 \\ - 1 \\ - 1 \\ - 1 \end{array} \right], \quad \boldsymbol {x} _ {2} = \left[ \begin{array}{c} 2 \\ - 1 \\ 1 \\ 2 \\ - 2 \end{array} \right], \quad \boldsymbol {x} _ {3} = \left[ \begin{array}{c} 3 \\ - 4 \\ 3 \\ 5 \\ - 3 \end{array} \right], \quad \boldsymbol {x} _ {4} = \left[ \begin{array}{c} - 1 \\ 8 \\ - 5 \\ - 6 \\ 1 \end{array} \right] \in \mathbb {R} ^ {5},\tag{2.81}
$$

我们希望找出 $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { 4 }$ 中哪些向量构成 U 的一组基。为此，需要检查 $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { 4 }$ 是否线性无关，也就是求解

$$
\sum_ {i = 1} ^ {4} \lambda_ {i} \boldsymbol {x} _ {i} = \mathbf {0},\tag{2.82}
$$

这给出一个齐次方程组，其矩阵为

$$
\left[ \boldsymbol {x} _ {1}, \boldsymbol {x} _ {2}, \boldsymbol {x} _ {3}, \boldsymbol {x} _ {4} \right] = \left[ \begin{array}{c c c c} 1 & 2 & 3 & - 1 \\ 2 & - 1 & - 4 & 8 \\ - 1 & 1 & 3 & - 5 \\ - 1 & 2 & 5 & - 6 \\ - 1 & - 2 & - 3 & 1 \end{array} \right].\tag{2.83}
$$

利用线性方程组的基本变换规则，得到行阶梯形

$$
\left[\begin{array}{r r r r}1&2&3&- 1\\2&- 1&- 4&8\\- 1&1&3&- 5\\- 1&2&5&- 6\\- 1&- 2&- 3&1\end{array}\right] \quad \rightsquigarrow \dots \rightsquigarrow \quad \left[\begin{array}{r r r r}1&2&3&- 1\\0&1&2&- 2\\0&0&0&1\\0&0&0&0\\0&0&0&0\end{array}\right].
$$

主元列指出了哪些向量线性无关。由行阶梯形可见，${ \pmb x } _ { 1 } , { \pmb x } _ { 2 } , { \pmb x } _ { 4 }$ 线性无关，因为线性方程组 $\lambda _ { 1 } \pmb { x } _ { 1 } + \lambda _ { 2 } \pmb { x } _ { 2 } + \lambda _ { 4 } \pmb { x } _ { 4 } = \mathbf { 0 }$ 只有在 $\lambda _ { 1 } = \lambda _ { 2 } = \lambda _ { 4 } = 0$ 时才能成立。因此，$\{ \pmb { x } _ { 1 } , \pmb { x } _ { 2 } , \pmb { x } _ { 4 } \}$ 是 U 的一组基。

### 2.6.2 秩

矩阵 $\pmb { { A } } \in \mathbb { R } ^ { m \times n }$ 中线性无关列的最大数量，等于线性无关行的最大数量，称为 A 的秩（rank），记为 rk(A)。

**注。** 矩阵的秩有以下重要性质：

- $\operatorname { r k } ( A ) = \operatorname { r k } ( A ^ { \top } )$，即列秩等于行秩。

- $\pmb { A } \in \mathbb { R } ^ { m \times n }$ 的各列张成子空间 $U \subseteq \mathbb { R } ^ { m }$，且 $\dim ( U ) =$ $\operatorname { r k } ( A )$。后面将把这个子空间称为像或值域（image 或 range）。对 A 进行高斯消元并识别主元列，可以找到 U 的一组基。

- $\pmb { { A } } \in \mathbb { R } ^ { m \times n }$ 的各行张成子空间 $W \subseteq \mathbb { R } ^ { n }$，且 $\dim ( W ) =$ $\operatorname { r k } ( A )$。对 $A^{\top}$ 进行高斯消元，可以找到 W 的一组基。

- 对所有 $\pmb { A } \in \mathbb { R } ^ { n \times n }$，A 正则（可逆）当且仅当 $\operatorname { r k } ( A ) = n$。

- 对所有 $\pmb { { A } } \in \mathbb { R } ^ { m \times n }$ 和 $\pmb { b } \in \mathbb { R } ^ { m }$，线性方程组 $\mathbf { A } { \boldsymbol { \mathbf { \mathit { x } } } } = \mathbf { \boldsymbol { \mathit { b } } }$ 有解，当且仅当 $\operatorname { r k } ( A ) = \operatorname { r k } ( A | b )$，其中 $[\boldsymbol{A}\mid\boldsymbol{b}]$ 表示增广方程组。

- 对 $\pmb { A } \in \mathbb { R } ^ { m \times n }$，方程 $\pmb { A } \pmb { x } = \mathbf { 0 }$ 的解子空间维数为 $n - \operatorname { r k } ( A )$。后面将把这个子空间称为核或零空间。

- 如果矩阵 $\pmb { A } \in \mathbb { R } ^ { m \times n }$ 的秩等于相同尺寸矩阵可能达到的最大秩，就称它满秩（full rank）。因此，满秩矩阵的秩是行数与列数中的较小者，即 $\operatorname { r k } ( A ) = \operatorname* { m i n } ( m , n )$。不满秩的矩阵称为秩亏矩阵（rank deficient）。

**例 2.18（秩）**

-

  $$
  \boldsymbol {A} = \left[ \begin{array}{l l l} 1 & 0 & 1 \\ 0 & 1 & 1 \\ 0 & 0 & 0 \end{array} \right].
  $$

  A 有两个线性无关的行／列，因此 $\operatorname{rk}(A)=2$。

-

  $$
  \boldsymbol {A} = \left[ \begin{array}{c c c} 1 & 2 & 1 \\ - 2 & - 3 & 1 \\ 3 & 5 & 0 \end{array} \right].
  $$

  用高斯消元确定其秩：

  $$
  \left[\begin{array}{c c c}1&2&1\\- 2&- 3&1\\3&5&0\end{array}\right] \quad \rightsquigarrow \dots \rightsquigarrow \quad \left[\begin{array}{c c c}1&2&1\\0&1&3\\0&0&0\end{array}\right]\tag{2.84}
  $$

  这里可以看到，线性无关的行和列的数量为 2，因此 $\operatorname{rk}(A)=2$。

## 2.7 线性映射

下面研究保持向量空间结构的映射，并由此定义坐标的概念。本章开头曾指出，向量可以相加，也可以与标量相乘，所得对象仍是向量。我们希望映射也保持这一性质。考虑两个实向量空间 $V , W$。如果映射 $\Phi:V\to W$ 满足

$$
\Phi (\boldsymbol {x} + \boldsymbol {y}) = \Phi (\boldsymbol {x}) + \Phi (\boldsymbol {y})\tag{2.85}
$$

$$
\Phi (\lambda \boldsymbol {x}) = \lambda \Phi (\boldsymbol {x})\tag{2.86}
$$

对所有 $\boldsymbol{x},\boldsymbol{y}\in V$ 和 $\lambda \in \mathbb { R }$ 都成立，就称它保持向量空间的结构。这可以概括为以下定义：

**定义 2.15（线性映射）。** 对于向量空间 $V,W$，如果映射 $\Phi : V \to W$ 满足

$$
\forall \boldsymbol {x}, \boldsymbol {y} \in V \forall \lambda , \psi \in \mathbb {R}: \Phi (\lambda \boldsymbol {x} + \psi \boldsymbol {y}) = \lambda \Phi (\boldsymbol {x}) + \psi \Phi (\boldsymbol {y}).\tag{2.87}
$$

就称其为线性映射，也称向量空间同态（vector space homomorphism）或线性变换（linear transformation）。

线性映射可以用矩阵表示，见 2.7.1 节。请记住，也可以将一组向量作为列组成矩阵。因此，使用矩阵时必须清楚它表示什么：一个线性映射，还是一组向量。第 4 章将进一步讨论线性映射。在继续之前，先简要介绍几种特殊映射。

**定义 2.16（单射、满射、双射）。** 考虑映射 $\Phi:\mathcal{V}\to\mathcal{W}$，其中 $\mathcal{V},\mathcal{W}$ 可以是任意集合。根据以下条件，对 $\Phi$ 作相应称呼：

- 单射（injective）：如果 $\forall x,y\in\mathcal{V}:\Phi(x)=\Phi(y)\implies x=y$。
- 满射（surjective）：如果 $\Phi(\mathcal{V})=\mathcal{W}$。
- 双射（bijective）：如果它既是单射又是满射。

如果 $\Phi$ 是满射，那么 $\mathcal{W}$ 中的每个元素，都可以通过 $\Phi$ 从 $\mathcal{V}$ 中“到达”。双射 $\Phi$ 可以“撤销”，即存在映射 $\Psi:\mathcal{W}\to\mathcal{V}$，使 $\Psi\circ\Phi(\boldsymbol{x})=\boldsymbol{x}$。此时称映射 $\Psi$ 为 $\Phi$ 的逆映射，通常记为 $\Phi^{-1}$。

利用这些定义，可以介绍向量空间 $V$ 与 $W$ 之间几种特殊的线性映射：

- 同构（isomorphism）：$\Phi:V\to W$ 既是线性的，又是双射。

- 自同态（endomorphism）：$\Phi:V\to V$ 是线性的。

- 自同构（automorphism）：$\Phi:V\to V$ 既是线性的，又是双射。

- 将 $\operatorname { i d } _ { V } : V \to V , x \mapsto x$ 定义为 $V$ 上的恒等映射或恒等自同构（identity mapping / identity automorphism）。

**例 2.19（同态）**

映射 $\Phi:\mathbb{R}^{2}\to\mathbb{C}$、$\Phi(\boldsymbol{x})=x_1+ix_2$ 是同态：

$$
\begin{array}{c} \Phi \left(\left[ \begin{array}{l} x _ {1} \\ x _ {2} \end{array} \right] + \left[ \begin{array}{l} y _ {1} \\ y _ {2} \end{array} \right]\right) = (x _ {1} + y _ {1}) + i (x _ {2} + y _ {2}) = x _ {1} + i x _ {2} + y _ {1} + i y _ {2} \\ = \Phi \left(\left[ \begin{array}{l} x _ {1} \\ x _ {2} \end{array} \right]\right) + \Phi \left(\left[ \begin{array}{l} y _ {1} \\ y _ {2} \end{array} \right]\right) \\ \Phi \left(\lambda \left[ \begin{array}{l} x _ {1} \\ x _ {2} \end{array} \right]\right) = \lambda x _ {1} + \lambda i x _ {2} = \lambda (x _ {1} + i x _ {2}) = \lambda \Phi \left(\left[ \begin{array}{l} x _ {1} \\ x _ {2} \end{array} \right]\right). \end{array}\tag{2.88}
$$

这也说明了为什么可以用 $\mathbb{R}^{2}$ 中的元组表示复数：存在一个双射线性映射，将 $\mathbb { R } ^ { 2 }$ 中元组的逐元素加法对应到复数集合中的加法。注意，上面只证明了线性性，没有证明双射性。

**定理 2.17（Axler（2015）中的定理 3.59）。** 有限维向量空间 $V$ 和 $W$ 同构，当且仅当 $\dim(V)=\dim(W)$。

定理 2.17 表明，两个维数相同的向量空间之间存在一个线性双射。直观地说，相同维数的向量空间在某种意义上是同一回事，因为它们可以相互转换，而不损失任何信息。

定理 2.17 也说明，可以同样看待 $\mathbb { R } ^ { m \times n }$（由 $m\times n$ 矩阵组成的向量空间）与 $\mathbb { R } ^ { m n }$（由长度为 mn 的向量组成的向量空间）：它们的维数都是 mn，并且存在将两者相互转换的线性双射。

**注。** 考虑向量空间 $V , W , X$，有以下性质：

- 对线性映射 $\Phi : V \to W$ 和 $\Psi : W \to X$，复合映射 $\Psi\circ\Phi:V\to X$ 也线性。

- 如果 $\Phi : V \to W$ 是同构，那么 $\Phi ^ { - 1 } : W \to V$ 也是同构。

- 如果 $\Phi:V\to W$、$\Psi:V\to W$ 线性，那么 $\Phi+\Psi$ 和 $\lambda\Phi$ 也线性，其中 $\lambda\in\mathbb{R}$。

### 2.7.1 线性映射的矩阵表示

任意 n 维向量空间都与 $\mathbb { R } ^ { n }$ 同构，见定理 2.17。考虑 n 维向量空间 V 的一组基 $\{ b _ { 1 } , \ldots , b _ { n } \}$。下面，基向量的顺序将十分重要，因此写成

$$
B = (\boldsymbol {b} _ {1}, \dots , \boldsymbol {b} _ {n})\tag{2.89}
$$

并将这一 n 元组称为 $V$ 的有序基（ordered basis）。

**注（记法）。** 到这里，记法开始变得稍微复杂，因此作一概括：$B=(\boldsymbol{b}_1,\ldots,\boldsymbol{b}_n)$ 是有序基；$\mathcal{B}=\{\boldsymbol{b}_1,\ldots,\boldsymbol{b}_n\}$ 是无序的基；$\boldsymbol{B}=[\boldsymbol{b}_1,\ldots,\boldsymbol{b}_n]$ 是以向量 $\boldsymbol{b}_1,\ldots,\boldsymbol{b}_n$ 为列的矩阵。

**定义 2.18（坐标）。** 考虑向量空间 V 及 $V$ 的有序基 $B = ( b _ { 1 } , \ldots , b _ { n } )$。任意 $\pmb { x } \in V$ 都有唯一表示，即线性组合

$$
\boldsymbol {x} = \alpha_ {1} \boldsymbol {b} _ {1} + \dots + \alpha_ {n} \boldsymbol {b} _ {n}\tag{2.90}
$$

这就是 $\boldsymbol{x}$ 关于 $B$ 的表示。系数 $\alpha _ { 1 } , \ldots , \alpha _ { n }$ 称为 x 关于 $B$ 的坐标（coordinates），而向量

$$
\boldsymbol {\alpha} = \left[ \begin{array}{c} \alpha_ {1} \\ \vdots \\ \alpha_ {n} \end{array} \right] \in \mathbb {R} ^ {n}\tag{2.91}
$$

称为 x 关于有序基 B 的坐标向量或坐标表示（coordinate vector / coordinate representation）。

一组基实际上定义了一个坐标系。我们熟悉的二维笛卡尔坐标系，由标准基向量 $e _ { 1 } , e _ { 2 }$ 张成。在这个坐标系中，向量 $\pmb { x } \in \mathbb { R } ^ { 2 }$ 的表示告诉我们应如何线性组合 $e _ { 1 }$ 与 $e _ { 2 }$，以得到 $\boldsymbol{x}$。不过，$\mathbb { R } ^ { 2 }$ 的任意一组基都能定义有效的坐标系，同一个向量 x 在基 $( b _ { 1 } , b _ { 2 } )$ 下可能具有不同的坐标表示。在图 2.8 中，x 关于标准基 $(\boldsymbol{e}_1,\boldsymbol{e}_2)$ 的坐标是 $[2,2]^{\top}$；而关于基 $\left( \boldsymbol { b } _ { 1 } , \boldsymbol { b } _ { 2 } \right)$，同一个向量 x 的表示为 $[1.09,0.72]^{\top}$，即 $\boldsymbol{x}=1.09\boldsymbol{b}_1+0.72\boldsymbol{b}_2$。后面几节将说明如何求出这种表示。

图 2.8 两组基向量定义了两个不同的坐标系。向量 x 的坐标表示取决于所选坐标系。

![图 2.8：标准基下的坐标](<Images/02_Linear_Algebra_image_010.jpg>)

![图 2.8：另一组基下的坐标](<Images/02_Linear_Algebra_image_011.jpg>)

**例 2.20**

考察几何向量 $\pmb { x } \in \mathbb { R } ^ { 2 }$，其关于 $\mathbb { R } ^ { 2 }$ 的标准基 $( e _ { 1 } , e _ { 2 } )$ 的坐标为 $[ 2 , 3 ] ^ { \top }$。这意味着可以写成 $\pmb { x } = 2 e _ { 1 } + 3 e _ { 2 }$。不过，并不一定要选择标准基来表示这个向量。如果使用基向量 $\pmb { b } _ { 1 } = [ 1 , - 1 ] ^ { \top } , \pmb { b } _ { 2 } = [ 1 , 1 ] ^ { \top }$，那么同一个向量关于 $( b _ { 1 } , b _ { 2 } )$ 的坐标就是 $\frac12[-1,5]^{\top}$，见图 2.9。

图 2.9 向量 $\boldsymbol{x}$ 在不同基下的坐标表示。

![图 2.9：同一向量在两组基下的表示](<Images/02_Linear_Algebra_image_012.jpg>)

**注。** 对于 n 维向量空间 V 及 $V$ 的有序基 B，映射 $\Phi : \mathbb { R } ^ { n } \to V , \Phi ( e _ { i } ) = \pmb { b } _ { i } , i = 1 , \dots , n$ 是线性的，并且根据定理 2.17 是同构，其中 $( e _ { 1 } , \ldots , e _ { n } )$ 是 $\mathbb { R } ^ { n }$ 的标准基。

现在可以明确建立矩阵与有限维向量空间之间线性映射的联系了。

**定义 2.19（变换矩阵）。** 考虑向量空间 $V , W$，其对应的有序基分别为 $B = ( b _ { 1 } , \ldots , b _ { n } )$ 和 $C=(\boldsymbol{c}_1,\ldots,\boldsymbol{c}_m)$。再考虑线性映射 $\Phi:V\to W$。对于 $j \in \{ 1 , \ldots , n \}$，

$$
\Phi (\boldsymbol {b} _ {j}) = \alpha_ {1 j} \boldsymbol {c} _ {1} + \dots + \alpha_ {m j} \boldsymbol {c} _ {m} = \sum_ {i = 1} ^ {m} \alpha_ {i j} \boldsymbol {c} _ {i}\tag{2.92}
$$

是 $\Phi ( b _ { j } )$ 关于 $C$ 的唯一表示。定义 $m\times n$ 矩阵 $\pmb { A } _ { \Phi }$ 的元素为

$$
A _ {\Phi} (i, j) = \alpha_ {i j},\tag{2.93}
$$

则称该矩阵为 Φ 关于 V 的有序基 B 和 W 的有序基 $C$ 的变换矩阵（transformation matrix）。

$\Phi(\boldsymbol{b}_j)$ 关于 $W$ 的有序基 $C$ 的坐标，构成 $A_{\Phi}$ 的第 $j$ 列。考虑有限维向量空间 $V,W$，其有序基分别为 $B,C$。线性映射 $\Phi:V\to W$ 的变换矩阵为 $A_{\Phi}$。如果 $\hat{\boldsymbol{x}}$ 是 $\boldsymbol{x}\in V$ 关于 $B$ 的坐标向量，而 $\hat{\boldsymbol{y}}$ 是 $\boldsymbol{y}=\Phi(\boldsymbol{x})\in W$ 关于 $C$ 的坐标向量，那么

$$
\hat {\boldsymbol {y}} = \boldsymbol {A} _ {\Phi} \hat {\boldsymbol {x}}.\tag{2.94}
$$

也就是说，变换矩阵可以将关于 $V$ 中某个有序基的坐标，映射为关于 $W$ 中某个有序基的坐标。

**例 2.21（变换矩阵）**

考虑同态 $\Phi \ : \ V \ \to \ W$，以及 V 的有序基 $B=(\boldsymbol{b}_1,\ldots,\boldsymbol{b}_3)$ 和 W 的有序基 $C = ( c _ { 1 } , \ldots , c _ { 4 } )$。若

$$
\begin{array}{l} \Phi (\boldsymbol {b} _ {1}) = \boldsymbol {c} _ {1} - \boldsymbol {c} _ {2} + 3 \boldsymbol {c} _ {3} - \boldsymbol {c} _ {4} \\ \Phi (\boldsymbol {b} _ {2}) = 2 \boldsymbol {c} _ {1} + \boldsymbol {c} _ {2} + 7 \boldsymbol {c} _ {3} + 2 \boldsymbol {c} _ {4} \\ \Phi (\boldsymbol {b} _ {3}) = 3 \boldsymbol {c} _ {2} + \boldsymbol {c} _ {3} + 4 \boldsymbol {c} _ {4} \end{array}\tag{2.95}
$$

那么，关于 $B$ 和 $C$ 的变换矩阵 $A _ { \Phi }$，对 $k = 1 , \ldots , 3$ 满足 $\Phi ( \boldsymbol { b } _ { k } ) =$ $\textstyle \sum _ { i = 1 } ^ { 4 } \alpha _ { i k } { \pmb { c } } _ { i }$，具体为

$$
\boldsymbol {A} _ {\Phi} = \left[\boldsymbol{\alpha}_1,\boldsymbol{\alpha}_2,\boldsymbol{\alpha}_3\right] = \left[ \begin{array}{c c c} 1 & 2 & 0 \\ - 1 & 1 & 3 \\ 3 & 7 & 1 \\ - 1 & 2 & 4 \end{array} \right],\tag{2.96}
$$

其中，$\boldsymbol{\alpha}_j$、$j=1,2,3$ 是 $\Phi ( \pmb { b } _ { j } )$ 关于 $C$ 的坐标向量。

**例 2.22（向量的线性变换）**

图 2.10 对 (a) 中以点表示的向量进行线性变换的三个例子：(b) 旋转 $45^{\circ}$；(c) 将水平方向坐标拉伸为原来的 2 倍；(d) 反射、旋转与拉伸的组合。

![图 2.10(a)：原始数据](<Images/02_Linear_Algebra_image_013.jpg>)

(a) 原始数据。

![图 2.10(b)：旋转](<Images/02_Linear_Algebra_image_014.jpg>)

(b) 旋转 $45^{\circ}$。

![图 2.10(c)：水平拉伸](<Images/02_Linear_Algebra_image_015.jpg>)

(c) 沿水平轴拉伸。

![图 2.10(d)：一般线性映射](<Images/02_Linear_Algebra_image_016.jpg>)

(d) 一般线性映射。

考虑对 $\mathbb { R } ^ { 2 }$ 中一组向量施加三种线性变换，其变换矩阵分别为

$$
\boldsymbol {A} _ {1} = \left[ \begin{array}{c c} \cos (\frac {\pi}{4}) & - \sin (\frac {\pi}{4}) \\ \sin (\frac {\pi}{4}) & \cos (\frac {\pi}{4}) \end{array} \right], \boldsymbol {A} _ {2} = \left[ \begin{array}{c c} 2 & 0 \\ 0 & 1 \end{array} \right], \boldsymbol {A} _ {3} = \frac {1}{2} \left[ \begin{array}{c c} 3 & - 1 \\ 1 & - 1 \end{array} \right].\tag{2.97}
$$

图 2.10 展示了对一组向量施加线性变换的三个例子。图 2.10(a) 包含 $\mathbb { R } ^ { 2 }$ 中的 400 个向量，每个向量用对应 $( x _ { 1 } , x _ { 2 } )$ 坐标处的一个点表示，这些向量排列成正方形。使用式 (2.97) 中的矩阵 $\pmb { A } _ { 1 }$ 对每个向量进行线性变换，得到图 2.10(b) 中旋转后的正方形。施加 $A _ { 2 }$ 所表示的线性映射，得到图 2.10(c) 中的矩形，其中每个 $x _ { 1 }$ 坐标都变为原来的 2 倍。图 2.10(d) 则展示了图 2.10(a) 中的原正方形经过 $A _ { 3 }$ 线性变换后的结果，这一变换是反射、旋转和拉伸的组合。

### 2.7.2 基变换

下面进一步考察：如果改变 $V$ 和 $W$ 中的基，线性映射 $\Phi:V\to W$ 的变换矩阵将如何改变。考虑两组有序基

$$
B = (\boldsymbol {b} _ {1}, \dots , \boldsymbol {b} _ {n}), \quad \tilde {B} = (\tilde {\boldsymbol {b}} _ {1}, \dots , \tilde {\boldsymbol {b}} _ {n})\tag{2.98}
$$

它们是 $V$ 的基；再考虑两组有序基

$$
C = (\pmb {c} _ {1}, \dots , \pmb {c} _ {m}), \quad \tilde {C} = (\tilde {\pmb {c}} _ {1}, \dots , \tilde {\pmb {c}} _ {m})\tag{2.99}
$$

它们是 $W$ 的基。此外，$A _ { \Phi } \in \mathbb { R } ^ { m \times n }$ 是线性映射 $\Phi:V\to W$ 关于基 $B$ 和 $C$ 的变换矩阵，$\tilde { \mathbf { A } } _ { \Phi } \in \mathbb { R } ^ { m \times n }$ 则对应于基 $\tilde{B}$ 和 $\tilde{C}$。下面研究 $\pmb { A }$ 与 $\tilde { \boldsymbol { A } }$ 的关系，也就是说，当基从 $B , C$ 改为 $\tilde { B } , \tilde { C }$ 时，能否以及如何将 $A _ { \Phi }$ 转换为 $\tilde { A } _ { \Phi }$。

**注。** 我们实际得到的是恒等映射 $\operatorname{id}_V$ 的不同坐标表示。在图 2.9 的情形中，这意味着将关于 $( e _ { 1 } , e _ { 2 } )$ 的坐标映射为关于 $( b _ { 1 } , b _ { 2 } )$ 的坐标，而不改变向量 ${ \pmb x }$ 本身。改变基并相应改变向量表示后，新基下的变换矩阵可能具有特别简单的形式，从而便于计算。

**例 2.23（基变换）**

考虑变换矩阵

$$
\boldsymbol {A} = \left[ \begin{array}{c c} 2 & 1 \\ 1 & 2 \end{array} \right]\tag{2.100}
$$

它是关于 $\mathbb { R } ^ { 2 }$ 中标准基的表示。如果定义新基

$$
B = (\left[ \begin{array}{c} 1 \\ 1 \end{array} \right], \left[ \begin{array}{c} 1 \\ - 1 \end{array} \right])\tag{2.101}
$$

就得到关于该基的对角变换矩阵

$$
\tilde {\pmb {A}} = \left[ \begin{array}{c c} 3 & 0 \\ 0 & 1 \end{array} \right]\tag{2.102}
$$

这就是关于 $B$ 的表示，比 A 更容易处理。

下面考察将一组基下的坐标向量转换成另一组基下坐标向量的映射。先给出主要结论，再作解释。

**定理 2.20（基变换）。** 考虑线性映射 $\Phi : V \to W$，以及有序基

$$
B = (\boldsymbol {b} _ {1}, \dots , \boldsymbol {b} _ {n}), \quad \tilde {B} = (\tilde {\boldsymbol {b}} _ {1}, \dots , \tilde {\boldsymbol {b}} _ {n})\tag{2.103}
$$

它们是 $V$ 的基；另有

$$
C = (\pmb {c} _ {1}, \dots , \pmb {c} _ {m}), \quad \tilde {C} = (\tilde {\pmb {c}} _ {1}, \dots , \tilde {\pmb {c}} _ {m})\tag{2.104}
$$

它们是 $W$ 的基。设 Φ 关于 $B$、$C$ 的变换矩阵为 $A _ { \Phi }$，那么关于 $\tilde { B }$、$\tilde { C }$ 的相应变换矩阵 $\tilde { A } _ { \Phi }$ 为

$$
\tilde {\boldsymbol {A}} _ {\Phi} = \boldsymbol {T} ^ {- 1} \boldsymbol {A} _ {\Phi} \boldsymbol {S}.\tag{2.105}
$$

这里，$\boldsymbol{S}\in\mathbb{R}^{n\times n}$ 是恒等映射 $\operatorname{id}_V$ 的变换矩阵，将关于 $\tilde { B }$ 的坐标映射为关于 $B$ 的坐标；$\pmb { T } \in \mathbb { R } ^ { m \times m }$ 是恒等映射 $\mathrm { i d } _ { W }$ 的变换矩阵，将关于 $\tilde { C }$ 的坐标映射为关于 $C$ 的坐标。

**证明。** 沿用 Drumm and Weil（2001）的方法，将 $V$ 的新基 $\tilde { B }$ 中的向量写成基 $B$ 中向量的线性组合：

$$
\tilde {\boldsymbol {b}} _ {j} = s _ {1 j} \boldsymbol {b} _ {1} + \dots + s _ {n j} \boldsymbol {b} _ {n} = \sum_ {i = 1} ^ {n} s _ {i j} \boldsymbol {b} _ {i}, \quad j = 1, \dots , n.\tag{2.106}
$$

类似地，将 $W$ 的新基 $\tilde { C }$ 中的向量写成基 $C$ 中向量的线性组合，得到

$$
\tilde {\boldsymbol {c}} _ {k} = t _ {1 k} \boldsymbol {c} _ {1} + \dots + t _ {m k} \boldsymbol {c} _ {m} = \sum_ {l = 1} ^ {m} t _ {l k} \boldsymbol {c} _ {l}, \quad k = 1, \ldots , m.\tag{2.107}
$$

定义 $S = ( ( s _ { i j } ) ) \in \mathbb { R } ^ { n \times n }$ 为将关于 $\tilde { B }$ 的坐标映射到关于 $B$ 的坐标的变换矩阵；定义 $\pmb { T } = \left( \left( t _ { l k } \right) \right) \in \mathbb { R } ^ { m \times m }$ 为将关于 $\tilde { C }$ 的坐标映射到关于 C 的坐标的变换矩阵。特别地，$\boldsymbol{S}$ 的第 $j$ 列是 $\tilde { \boldsymbol { b } } _ { j }$ 关于 $B$ 的坐标表示，而 T 的第 k 列是 $\tilde { c } _ { k }$ 关于 C 的坐标表示。注意，S 和 $\mathbf { T }$ 都是正则矩阵。

现在从两个角度考察 $\Phi ( \tilde { \pmb { b } } _ { j } )$。首先，施加映射 Φ，对所有 $j = 1 , \dotsc , n$ 有

$$
\Phi (\tilde {\boldsymbol {b}} _ {j}) = \sum_ {k = 1} ^ {m} \underbrace {\tilde {a} _ {k j} \tilde {\boldsymbol {c}} _ {k}} _ {\in W} \stackrel {(2.107)} {=} \sum_ {k = 1} ^ {m} \tilde {a} _ {k j} \sum_ {l = 1} ^ {m} t _ {l k} \boldsymbol {c} _ {l} = \sum_ {l = 1} ^ {m} \left(\sum_ {k = 1} ^ {m} t _ {l k} \tilde {a} _ {k j}\right) \boldsymbol {c} _ {l},\tag{2.108}
$$

这里先将新基向量 $\tilde { \boldsymbol { c } } _ { k } ~ \in ~ W$ 写成基向量 $\mathbf { \boldsymbol { c } } _ { l } ~ \in ~ W$ 的线性组合，再交换求和顺序。

另一种方式是将 $\tilde { \pmb { b } } _ { j } \in V$ 表示为 $b _ { j } \in V$ 的线性组合，得到

$$
\Phi (\tilde {\boldsymbol {b}} _ {j}) \stackrel {(2.106)} {=} \Phi \left(\sum_ {i = 1} ^ {n} s _ {i j} \boldsymbol {b} _ {i}\right) = \sum_ {i = 1} ^ {n} s _ {i j} \Phi (\boldsymbol {b} _ {i}) = \sum_ {i = 1} ^ {n} s _ {i j} \sum_ {l = 1} ^ {m} a _ {l i} \boldsymbol {c} _ {l}\tag{2.109a}
$$

$$
= \sum_ {l = 1} ^ {m} \left(\sum_ {i = 1} ^ {n} a _ {l i} s _ {i j}\right) \boldsymbol {c} _ {l}, \quad j = 1, \ldots , n,\tag{2.109b}
$$

这里利用了 Φ 的线性性。比较式 (2.108) 和式 (2.109b)，可知对所有 $j = 1 , \dotsc , n$ 和 $l = 1 , \ldots , m$，都有

$$
\sum_ {k = 1} ^ {m} t _ {l k} \tilde {a} _ {k j} = \sum_ {i = 1} ^ {n} a _ {l i} s _ {i j}\tag{2.110}
$$

因此，

$$
\boldsymbol {T} \tilde {\boldsymbol {A}} _ {\Phi} = \boldsymbol {A} _ {\Phi} \boldsymbol {S} \in \mathbb {R} ^ {m \times n},\tag{2.111}
$$

从而

$$
\tilde {\boldsymbol {A}} _ {\Phi} = \boldsymbol {T} ^ {- 1} \boldsymbol {A} _ {\Phi} \boldsymbol {S},\tag{2.112}
$$

定理 2.20 得证。

定理 2.20 表明：在 $V$ 中将 $B$ 换为 $\tilde{B}$，在 $W$ 中将 C 换为 $\tilde { C }$ 后，线性映射 $\Phi:V\to W$ 的变换矩阵 $A _ { \Phi }$ 被一个等价矩阵 $\tilde { \mathbf { A } } _ { \Phi }$ 取代，满足

$$
\tilde {\boldsymbol {A}} _ {\Phi} = \boldsymbol {T} ^ {- 1} \boldsymbol {A} _ {\Phi} \boldsymbol {S}.\tag{2.113}
$$

图 2.11 展示了这一关系。考虑同态 $\Phi:V\to W$，以及 $V$ 的有序基 B、$\tilde { B }$ 和 W 的有序基 $C , { \tilde { C } }$。映射 $\Phi _ { C B }$ 是 $\Phi$ 的一种具体表示，将 B 的基向量映射为 C 的基向量的线性组合。假设已知 $\Phi _ { C B }$ 关于有序基 B、C 的变换矩阵 $A _ { \Phi }$。在 $V$ 中将 $B$ 换为 $\tilde { B }$，在 $W$ 中将 $C$ 换为 $\tilde { C }$ 后，可以按以下方式确定相应的变换矩阵 $\tilde { \mathbf { A } } _ { \Phi }$：首先，求线性映射 $\Psi_{B\tilde{B}}:V\to V$ 的矩阵表示，将新基 $\tilde { B }$ 下的坐标映射为 $V$ 中“旧”基 $B$ 下唯一确定的坐标；然后，使用 $\Phi _ { C B } : V \to W$ 的变换矩阵 $A _ { \Phi }$，将这些坐标映射为 W 中关于 $C$ 的坐标；最后，通过线性映射 $\Xi _ { \tilde { C } C } : W \to W$，将关于 $C$ 的坐标映射为关于 ${ \tilde { C } }$ 的坐标。因此，线性映射 $\Phi _ { \tilde { C } \tilde { B } }$ 可以表示为涉及“旧”基的线性映射之复合：

$$
\Phi_ {\tilde {C} \tilde {B}} = \Xi_ {\tilde {C} C} \circ \Phi_ {C B} \circ \Psi_ {B \tilde {B}} = \Xi_ {C \tilde {C}} ^ {- 1} \circ \Phi_ {C B} \circ \Psi_ {B \tilde {B}}.\tag{2.114}
$$

具体来说，使用 $\Psi _ { B \tilde { B } } = \mathrm { i d } _ { V }$ 和 $\Xi _ { C \tilde { C } } = \mathrm { i d } _ { W }$，即把向量映射到自身、但采用不同基来表示的恒等映射。

![图 2.11：基变换映射的复合](<Images/02_Linear_Algebra_Figure_2_11.png>)

图 2.11 对同态 $\Phi:V\to W$，以及 $V$ 的有序基 $B,\tilde{B}$ 和 $W$ 的有序基 $C,\tilde{C}$（以蓝色标出），关于基 $\tilde{B},\tilde{C}$ 的映射 $\Phi_{\tilde{C}\tilde{B}}$，可以等价地表示为关于下标所指各组基的同态之复合：$\Phi_{\tilde{C}\tilde{B}}=\Xi_{\tilde{C}C}\circ\Phi_{CB}\circ\Psi_{B\tilde{B}}$。对应的变换矩阵用红色标出。图内 Vector spaces 表示向量空间，Ordered bases 表示有序基。

**定义 2.21（等价）。** 如果存在正则矩阵 $S ~ \in ~ \mathbb { R } ^ { n \times n }$ 和 $\pmb { T } \in \mathbb { R } ^ { m \times m }$，使 $\tilde { \pmb { A } } = \pmb { T } ^ { - 1 } \pmb { A } \pmb { S }$，就称两个矩阵 $\boldsymbol{A},\tilde{\boldsymbol{A}}\in\mathbb{R}^{m\times n}$ 等价（equivalent）。

**定义 2.22（相似）。** 如果存在正则矩阵 $\boldsymbol{S}\in\mathbb{R}^{n\times n}$，使 $\tilde { \pmb { A } } = \pmb { S } ^ { - 1 } \pmb { A } \pmb { S }$，就称两个矩阵 $\pmb { A } , \tilde { \pmb { A } } \in \mathbb { R } ^ { n \times n }$ 相似（similar）。

**注。** 相似矩阵总是等价的，但等价矩阵不一定相似。$\diamondsuit$

**注。** 考虑向量空间 $V , W , X$。定理 2.17 后的注已经指出，对于线性映射 $\Phi : V \to W$ 和 $\Psi : W \to X$，复合映射 $\Psi\circ\Phi:V\to X$ 也线性。如果相应映射的变换矩阵为 $A _ { \Phi }$ 和 $\pmb { A } _ { \Psi }$，那么复合映射的变换矩阵为 $\pmb { A } _ { \Psi \circ \Phi } = \pmb { A } _ { \Psi } \pmb { A } _ { \Phi }$。$\diamondsuit$

根据这条性质，可以从线性映射复合的角度看待基变换：

- $A _ { \Phi }$ 是线性映射 $\Phi _ { C B } : V \to W$ 关于基 $B , C$ 的变换矩阵。

- $\tilde { \mathbf { A } } _ { \Phi }$ 是线性映射 $\Phi _ { \tilde { C } \tilde { B } } : V \to W$ 关于基 $\tilde { B } , \tilde { C }$ 的变换矩阵。

- S 是线性映射 $\Psi_{B\tilde{B}}:V\to V$ 的变换矩阵。这个映射是自同构，用 $B$ 表示 $\tilde { B }$。通常，$\Psi = \operatorname { i d } _ { V }$ 是 $V$ 上的恒等映射。

- T 是线性映射 $\Xi _ { C \tilde { C } } : W \to W$ 的变换矩阵。这个映射是自同构，用 C 表示 $\tilde { C }$。通常，$\Xi = \mathrm { i d } _ { W }$ 是 $W$ 上的恒等映射。

如果只用基的名称非正式地表示这些变换，就有 $A_{\Phi}:B\to C$、$\tilde{A}_{\Phi}:\tilde{B}\to\tilde{C}$、$S:\tilde{B}\to B$、$T:\tilde{C}\to C$ 和 $T^{-1}:C\to\tilde{C}$，于是

$$
\tilde {B} \rightarrow \tilde {C} = \tilde {B} \rightarrow B \rightarrow C \rightarrow \tilde {C}\tag{2.115}
$$

$$
\tilde {\boldsymbol {A}} _ {\Phi} = \boldsymbol {T} ^ {- 1} \boldsymbol {A} _ {\Phi} \boldsymbol {S}.\tag{2.116}
$$

注意，式 (2.116) 的执行顺序是从右到左，因为向量放在矩阵右侧相乘，即 $\pmb { x } \mapsto \pmb { S x } \mapsto \pmb { A } _ { \Phi } ( \pmb { S x } ) \mapsto$ $\pmb { T } ^ { - 1 } \big ( \pmb { A } _ { \Phi } ( \pmb { S } \pmb { x } ) \big ) = \tilde { \pmb { A } } _ { \Phi } \pmb { x }$。

**例 2.24（基变换）**

考虑线性映射 $\Phi:\mathbb{R}^{3}\to\mathbb{R}^{4}$，其变换矩阵为

$$
\boldsymbol {A} _ {\Phi} = \left[ \begin{array}{c c c} 1 & 2 & 0 \\ - 1 & 1 & 3 \\ 3 & 7 & 1 \\ - 1 & 2 & 4 \end{array} \right]\tag{2.117}
$$

它对应的标准基为

$$
B = (\left[ \begin{array}{c} 1 \\ 0 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 0 \\ 1 \end{array} \right]), \quad C = (\left[ \begin{array}{c} 1 \\ 0 \\ 0 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 1 \\ 0 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 0 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 0 \\ 0 \\ 1 \end{array} \right]).\tag{2.118}
$$

求 Φ 关于以下新基的变换矩阵 $\tilde { \mathbf { A } } _ { \Phi }$：

$$
\tilde {B} = (\left[ \begin{array}{c} 1 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 1 \\ 1 \end{array} \right], \left[ \begin{array}{c} 1 \\ 0 \\ 1 \end{array} \right]) \in \mathbb {R} ^ {3}, \quad \tilde {C} = (\left[ \begin{array}{c} 1 \\ 1 \\ 0 \\ 0 \end{array} \right], \left[ \begin{array}{c} 1 \\ 0 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 1 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 1 \\ 0 \\ 0 \\ 1 \end{array} \right]).\tag{2.119}
$$

此时，

$$
\boldsymbol {S} = \left[ \begin{array}{c c c} 1 & 0 & 1 \\ 1 & 1 & 0 \\ 0 & 1 & 1 \end{array} \right], \qquad \boldsymbol {T} = \left[ \begin{array}{c c c c} 1 & 1 & 0 & 1 \\ 1 & 0 & 1 & 0 \\ 0 & 1 & 1 & 0 \\ 0 & 0 & 0 & 1 \end{array} \right],\tag{2.120}
$$

其中，S 的第 i 列是 $\tilde { \pmb { b } } _ { i }$ 关于 B 中基向量的坐标表示。因为 B 是标准基，所以很容易求出这一坐标表示。对于一般的基 $B$，则需要求解线性方程组，确定 $\lambda _ { i }$，使

$\begin{array} { r } { \sum _ { i = 1 } ^ { 3 } \lambda _ { i } \pmb { b } _ { i } = \tilde { \pmb { b } } _ { j } , j = 1 , \dots , 3 } \end{array}$。类似地，$\boldsymbol{T}$ 的第 $j$ 列，是 $\tilde { \boldsymbol { c } } _ { j }$ 关于 C 中基向量的坐标表示。

因此，得到

$$
\tilde{\boldsymbol{A}}_{\Phi}=\boldsymbol{T}^{-1}\boldsymbol{A}_{\Phi}\boldsymbol{S}
=\frac12\begin{bmatrix}1&1&-1&-1\\1&-1&1&-1\\-1&1&1&1\\0&0&0&2\end{bmatrix}
\begin{bmatrix}3&2&1\\0&4&2\\10&8&4\\1&6&3\end{bmatrix}
\tag{2.121a}
$$

$$
=\begin{bmatrix}-4&-4&-2\\6&0&0\\4&8&4\\1&6&3\end{bmatrix}.
\tag{2.121b}
$$ 

第 4 章将利用基变换寻找一组基，使自同态的变换矩阵在这组基下具有特别简单的对角形式。第 10 章将讨论数据压缩问题，寻找适合投影数据的基，同时尽量减小压缩损失。

### 2.7.3 像与核

线性映射的像和核是具有某些重要性质的向量子空间。下面更仔细地刻画它们。

**定义 2.23（像与核）。**

对于 $\Phi:V\to W$，定义核／零空间为

$$
\ker (\Phi) := \Phi^ {- 1} (\mathbf {0} _ {W}) = \{\boldsymbol {v} \in V: \Phi (\boldsymbol {v}) = \mathbf {0} _ {W} \}\tag{2.122}
$$

定义像／值域为

$$
\operatorname{Im} (\Phi) := \Phi (V) = \left\{\boldsymbol {w} \in W | \exists \boldsymbol {v} \in V: \Phi (\boldsymbol {v}) = \boldsymbol {w} \right\}.\tag{2.123}
$$

V 和 W 也分别称为 Φ 的定义域（domain）和陪域（codomain）。

直观地说，核由所有被 Φ 映射到单位元 ${ \mathbf { 0 } } _ { W } \in W$ 的向量 $v \in V$ 组成；像由所有可以从 V 中某个向量出发，经 Φ“到达”的向量 $\boldsymbol{w}\in W$ 组成。图 2.12 展示了这一关系。

![图 2.12：线性映射的核与像](<Images/02_Linear_Algebra_image_017.jpg>)

图 2.12 线性映射 Φ : V → W 的核与像。图内 ker(Φ) 表示核，Im(Φ) 表示像，0 下标 V 与 0 下标 W 分别表示两个空间的零向量。

**注。** 考虑线性映射 $\Phi : V \to W$，其中 $V , W$ 为向量空间。

- 恒有 $\Phi ( { \bf 0 } _ { V } ) = { \bf 0 } _ { W }$，因此 ${ \mathbf { 0 } _ { V } } \in \mathop { \ker } ( \Phi )$。特别地，零空间永不为空。

- $\operatorname{Im}(\Phi)\subseteq W$ 是 $W$ 的子空间，而 $\ker(\Phi)\subseteq V$ 是 $V$ 的子空间。

- Φ 为单射（一一映射），当且仅当 $\ker ( \Phi ) = \{ \mathbf { 0 } \}$。

**注（零空间与列空间）。** 考虑 $\boldsymbol{A}\in\mathbb{R}^{m\times n}$ 及线性映射 $\Phi:\mathbb{R}^{n}\to\mathbb{R}^{m}$、$\boldsymbol{x}\mapsto\boldsymbol{A}\boldsymbol{x}$。

- 设 $\pmb { A } = [ \pmb { a } _ { 1 } , \dots , \pmb { a } _ { n } ]$，其中 $\mathbf { a } _ { i }$ 为 A 的各列，则有

$$
\operatorname{Im}(\Phi)=\{\boldsymbol{A}\boldsymbol{x}:\boldsymbol{x}\in\mathbb{R}^{n}\}
=\left\{\sum_{i=1}^{n}x_i\boldsymbol{a}_i:x_1,\ldots,x_n\in\mathbb{R}\right\}
\tag{2.124a}
$$

$$
=\operatorname{span}[\boldsymbol{a}_1,\ldots,\boldsymbol{a}_n]\subseteq\mathbb{R}^{m},
\tag{2.124b}
$$ 

  即像是 A 的各列所张成的空间，也称列空间（column space）。因此，列空间（像）是 $\mathbb { R } ^ { m }$ 的子空间，其中 m 是矩阵的“高度”。

- $\operatorname{rk}(A)=\dim(\operatorname{Im}(\Phi))$。

- 核／零空间 ker(Φ) 是齐次线性方程组 $\mathbf { { \boldsymbol { A } } } \mathbf { { \boldsymbol { x } } } = \mathbf { { \boldsymbol { 0 } } }$ 的通解，它刻画了 $\mathbb { R } ^ { n }$ 中能够产生 $\mathbf { 0 } \in \mathbb { R } ^ { m }$ 的所有可能线性组合。

- 核是 $\mathbb{R}^{n}$ 的子空间，其中 n 是矩阵的“宽度”。

- 核关注各列之间的关系，可以用它确定一列是否以及如何表示为其他列的线性组合。

**例 2.25（线性映射的像与核）**

映射

$$
\Phi : \mathbb {R} ^ {4} \to \mathbb {R} ^ {2}, \quad \left[ \begin{array}{c} x _ {1} \\ x _ {2} \\ x _ {3} \\ x _ {4} \end{array} \right] \mapsto \left[ \begin{array}{c c c c} 1 & 2 & - 1 & 0 \\ 1 & 0 & 0 & 1 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \\ x _ {3} \\ x _ {4} \end{array} \right] = \left[ \begin{array}{c} x _ {1} + 2 x _ {2} - x _ {3} \\ x _ {1} + x _ {4} \end{array} \right]\tag{2.125a}
$$

$$
= x _ {1} \left[ \begin{array}{c} 1 \\ 1 \end{array} \right] + x _ {2} \left[ \begin{array}{c} 2 \\ 0 \end{array} \right] + x _ {3} \left[ \begin{array}{c} - 1 \\ 0 \end{array} \right] + x _ {4} \left[ \begin{array}{c} 0 \\ 1 \end{array} \right]\tag{2.125b}
$$

是线性的。为求 Im(Φ)，取变换矩阵各列的张成空间，得到

$$
\mathrm{Im} (\Phi) = \mathrm{span} [ \left[ \begin{array}{c} 1 \\ 1 \end{array} \right], \left[ \begin{array}{c} 2 \\ 0 \end{array} \right], \left[ \begin{array}{c} - 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 1 \end{array} \right] ].\tag{2.126}
$$

为计算 Φ 的核（零空间），需要求解 $A\boldsymbol{x}=\boldsymbol{0}$，也就是求解齐次方程组。通过高斯消元，将 A 化为简化行阶梯形：

$$
\left[\begin{array}{c c c c}1&2&- 1&0\\1&0&0&1\end{array}\right] \quad \rightsquigarrow \dots \rightsquigarrow \quad \left[\begin{array}{c c c c}1&0&0&1\\0&1&- \frac {1}{2}&- \frac {1}{2}\end{array}\right].\tag{2.127}
$$

该矩阵已为简化行阶梯形，可以使用减一技巧求核的一组基，见 2.3.3 节。也可以将非主元列（第 3、4 列）表示为主元列（第 1、2 列）的线性组合。第三列 ${ \bf { a } } _ { 3 }$ 等于第二列 $\mathbf { a } _ { 2 }$ 的 $- \frac 1 2$ 倍，因此 ${ \bf 0 } = { \bf a } _ { 3 } + \frac { 1 } { 2 } { \bf a } _ { 2 }$。同理，$\mathbf { a } _ { 4 } = \mathbf { a } _ { 1 } - \frac { 1 } { 2 } \mathbf { a } _ { 2 }$，所以 $\mathbf { 0 } = { \pmb a } _ { 1 } - \frac { 1 } { 2 } { \pmb a } _ { 2 } - { \pmb a } _ { 4 }$。综合得到核（零空间）为

$$
\ker (\Phi) = \operatorname{span} [ \left[ \begin{array}{c} 0 \\ \frac {1}{2} \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} - 1 \\ \frac {1}{2} \\ 0 \\ 1 \end{array} \right] ].\tag{2.128}
$$

**定理 2.24（秩–零度定理）。** 对向量空间 $V , W$ 及线性映射 $\Phi:V\to W$，有

$$
\dim (\ker (\Phi)) + \dim (\operatorname{Im} (\Phi)) = \dim (V).\tag{2.129}
$$

秩–零度定理（rank-nullity theorem）也称线性映射基本定理（fundamental theorem of linear mappings；Axler，2015，定理 3.22）。定理 2.24 直接给出以下推论：

- 如果 $\dim(\operatorname{Im}(\Phi))<\dim(V)$，则 $\ker(\Phi)$ 非平凡，即核中不只有 $\mathbf { 0 } _ { V }$，并且 $\dim ( \ker ( \Phi ) ) \geqslant 1$。

- 如果 $A _ { \Phi }$ 是 Φ 关于有序基的变换矩阵，且 $\dim(\operatorname{Im}(\Phi))<\dim(V)$，则线性方程组 $\boldsymbol{A}_{\Phi}\boldsymbol{x}=\boldsymbol{0}$ 有无穷多个解。

- 如果 $\dim ( V ) = \dim ( W )$，则有以下三者等价关系：

  Φ 为单射 $\iff$ Φ 为满射 $\iff$ Φ 为双射。

  这是因为 $\operatorname{Im}(\Phi)\subseteq W$。

## 2.8 仿射空间

下面进一步考察相对于原点发生偏移的空间，也就是不再是向量子空间的空间。此外，还将简要讨论这些仿射空间（affine space）之间映射的性质，它们与线性映射相似。

**注。** 机器学习文献有时没有清楚区分线性与仿射，因此可能把仿射空间或仿射映射称为线性空间或线性映射。

### 2.8.1 仿射子空间

**定义 2.25（仿射子空间）。** 设 V 是向量空间，$\pmb { x } _ { 0 } \in V$，且 $U \subseteq V$ 是子空间。那么，子集

$$
L = \boldsymbol {x} _ {0} + U := \left\{\boldsymbol {x} _ {0} + \boldsymbol {u}: \boldsymbol {u} \in U \right\}\tag{2.130a}
$$

$$
= \left\{\boldsymbol {v} \in V | \exists \boldsymbol {u} \in U: \boldsymbol {v} = \boldsymbol {x} _ {0} + \boldsymbol {u} \right\} \subseteq V\tag{2.130b}
$$

称为 V 的仿射子空间（affine subspace）或线性流形（linear manifold）。U 称为方向或方向空间（direction space），$\scriptstyle { \pmb x } _ { 0 }$ 称为支撑点（support point）。第 12 章中将把这样的子空间称为超平面（hyperplane）。

> 译注：超平面是仿射子空间的一种特殊情形，其维数比所在空间少 1；这一限制会在下面的例 2.26 中明确给出。

注意，当 $\boldsymbol{x}_0\notin U$ 时，按定义该仿射子空间不包含 0。因此，在 ${ \pmb x } _ { 0 } \not \in U$ 的情况下，仿射子空间不是 V 的线性子空间（向量子空间）。

仿射子空间的例子包括 $\mathbb { R } ^ { 3 }$ 中的点、直线和平面，它们不一定经过原点。

**注。** 考虑向量空间 V 的两个仿射子空间 $L = { \pmb x } _ { 0 } + U$ 和 $\tilde { L } = \tilde { \mathbf { x } } _ { 0 } + \tilde { U }$。那么，$L \subseteq { \tilde { L } }$ 当且仅当 $U \subseteq { \tilde { U } }$ 且 ${ \pmb x } _ { 0 } - { \pmb { \tilde { x } } } _ { 0 } \in \tilde { U }$。

仿射子空间常用参数描述。考虑 V 中 k 维仿射空间 ${ \boldsymbol { L } } = { \mathbf { { x } } } _ { 0 } + { \boldsymbol { U } }$。如果 $\left( \pmb { b } _ { 1 } , \dots , \pmb { b } _ { k } \right)$ 是 $U$ 的一组有序基，那么每个元素 $\boldsymbol { x } \in L$ 都能唯一地表示为

$$
\boldsymbol {x} = \boldsymbol {x} _ {0} + \lambda_ {1} \boldsymbol {b} _ {1} + \dots + \lambda_ {k} \boldsymbol {b} _ {k},\tag{2.131}
$$

其中 $\lambda _ { 1 } , \ldots , \lambda _ { k } \in \mathbb { R }$。这种表示称为 L 的参数方程（parametric equation），$\boldsymbol { b } _ { 1 } , \ldots , \boldsymbol { b } _ { k }$ 是方向向量，$\lambda _ { 1 } , \ldots , \lambda _ { k }$ 是参数。

**例 2.26（仿射子空间）**

- 一维仿射子空间称为直线，可写成 $\pmb { y } = \pmb { x } _ { 0 } + \lambda \pmb { b } _ { 1 }$，其中 $\lambda \in \mathbb { R }$，$U = \mathrm { s p a n } [ b _ { 1 } ] \ \subseteq \ \mathbb { R } ^ { n }$ 是 $\mathbb { R } ^ { n }$ 的一维子空间。这意味着，一条直线由支撑点 $\scriptstyle { \pmb x } _ { 0 }$ 和确定方向的向量 $b _ { 1 }$ 定义。图 2.13 给出了示意。

- $\mathbb { R } ^ { n }$ 的二维仿射子空间称为平面。平面的参数方程为 $\pmb { y } = \pmb { x } _ { 0 } + \lambda _ { 1 } \pmb { b } _ { 1 } + \lambda _ { 2 } \pmb { b } _ { 2 }$，其中 $\lambda _ { 1 } , \lambda _ { 2 } \in \mathbb { R }$，且 $U = \operatorname { s p a n } [ b _ { 1 } , b _ { 2 } ] \subseteq \mathbb { R } ^ { n }$。这意味着，一个平面由支撑点 $\boldsymbol{x}_0$ 和张成方向空间的两个线性无关向量 $b _ { 1 } , b _ { 2 }$ 定义。

- 在 $\mathbb { R } ^ { n }$ 中，$( n - 1 )$ 维仿射子空间称为超平面，对应参数方程为 $\begin{array} { r } { \pmb { y } = \pmb { x } _ { 0 } + \sum _ { i = 1 } ^ { n - 1 } \lambda _ { i } \pmb { b } _ { i } } \end{array}$，其中 $b _ { 1 } , \ldots , b _ { n - 1 }$ 构成 $\mathbb { R } ^ { n }$ 中 $( n - 1 )$ 维子空间 $U$ 的一组基。因此，超平面由支撑点 $\boldsymbol{x}_0$ 和张成方向空间的 $( n - 1 )$ 个线性无关向量 $b _ { 1 } , \ldots , b _ { n - 1 }$ 定义。在 $\mathbb { R } ^ { 2 }$ 中，直线也是超平面；在 $\mathbb { R } ^ { 3 }$ 中，平面也是超平面。

![图 2.13：仿射直线](<Images/02_Linear_Algebra_image_018.jpg>)

图 2.13 直线是仿射子空间。直线 $\boldsymbol{x}_0+\lambda\boldsymbol{b}_1$ 上的向量 $\boldsymbol{y}$ 位于仿射子空间 $L$ 中，其支撑点为 $\boldsymbol{x}_0$，方向为 $\boldsymbol{b}_1$。

**注（非齐次线性方程组与仿射子空间）。** 对 $\pmb { A } \in \mathbb { R } ^ { m \times n }$ 和 $\pmb { x } \in \mathbb { R } ^ { m }$，线性方程组 $A \lambda = x$ 的解集要么为空，要么是 $\mathbb { R } ^ { n }$ 中维数为 $n - \operatorname { r k } ( A )$ 的仿射子空间。特别地，线性方程 $\lambda _ { 1 } b _ { 1 } + . . . + \lambda _ { n } b _ { n } = x$，其中 $( \lambda _ { 1 } , \ldots , \lambda _ { n } ) \neq ( 0 , \ldots , 0 )$，其解集是 $\mathbb { R } ^ { n }$ 中的超平面。

在 $\mathbb { R } ^ { n }$ 中，每个 k 维仿射子空间都是某个非齐次线性方程组 $\mathbf { { A } } { \boldsymbol { x } } = { \boldsymbol { b } }$ 的解集，其中 $\boldsymbol{A}\in\mathbb{R}^{m\times n}$、$\boldsymbol{b}\in\mathbb{R}^{m}$，且 $\operatorname{rk}(A)=n-k$。请回顾，齐次方程组 $\pmb { A } \pmb { x } = \pmb { 0 }$ 的解集是向量子空间，也可以把它看作支撑点为 $\boldsymbol{x}_0=\boldsymbol{0}$ 的特殊仿射空间。◇

### 2.8.2 仿射映射

类似于 2.7 节讨论的向量空间之间的线性映射，也可以定义两个仿射空间之间的仿射映射（affine mapping）。线性映射与仿射映射关系密切，因此许多已知的线性映射性质也适用于仿射映射，例如线性映射的复合仍然线性，对应地，仿射映射的复合仍然仿射。

**定义 2.26（仿射映射）。** 对于两个向量空间 $V,W$、线性映射 $\Phi : V \to W$ 以及 $\mathbf { \pmb { a } } \in W$，映射

$$
\phi : V \to W\tag{2.132}
$$

$$
\boldsymbol {x} \mapsto \boldsymbol {a} + \Phi (\boldsymbol {x})\tag{2.133}
$$

称为从 V 到 W 的仿射映射。向量 a 称为 $\phi$ 的平移向量（translation vector）。

- 每个仿射映射 $\phi : V \to W$ 都是线性映射 $\Phi : V \to W$ 与 $W$ 中平移 $\tau : W \to W$ 的复合，即 $\phi = \tau \circ \Phi$。映射 Φ 与 τ 唯一确定。

- 仿射映射 $\phi:V\to W$ 和 $\phi^{\prime}:W\to X$ 的复合 $\phi ^ { \prime } \circ \phi$ 仍是仿射映射。

- 如果 $\phi$ 是双射，仿射映射保持几何结构不变，也保持维数和平行性。

## 2.9 延伸阅读

学习线性代数的资源很多，包括 Strang（2003）、Golan（2007）、Axler（2015）以及 Liesen and Mehrmann（2015）的教材。本章引言还列出了一些在线资源。这里仅介绍了高斯消元，但求解线性方程组还有许多其他方法。深入讨论可参阅 Stoer and Burlirsch（2002）、Golub and Van Loan（2012）以及 Horn and Johnson（2013）的数值线性代数教材。

本书区分线性代数主题，例如向量、矩阵、线性无关和基，与向量空间几何有关的主题。第 3 章将介绍内积，以及由内积诱导的范数。借助这些概念，可以定义角度、长度和距离，并进一步用于正交投影（orthogonal projection）。投影在许多机器学习算法中起关键作用，例如线性回归和主成分分析，分别将在第 9 章和第 10 章讨论。

## 习题

**2.1.** 考虑 $( \mathbb { R } \backslash \{ - 1 \} , \star )$，其中

$$
a \star b := a b + a + b, \qquad a, b \in \mathbb {R} \backslash \{- 1 \}\tag{2.134}
$$

**(a)** 证明 $( \mathbb { R } \backslash \{ - 1 \} , \star )$ 是阿贝尔群。

**(b)** 求解

$$
3 \star x \star x = 15
$$

这里在阿贝尔群 $( \mathbb { R } \backslash \{ - 1 \} , \star )$ 中求解，⋆ 由式 (2.134) 定义。

**2.2.** 设 n 属于 $\mathbb { N } \backslash \{ 0 \}$，$k , x$ 属于 $\mathbb { Z }$。将整数 k 的同余类（congruence class）$\bar { k }$ 定义为集合

$$
\begin{array}{r l} & {\overline {{k}} = \{x \in \mathbb {Z} \mid x - k = 0 (\mathrm{mod} n) \}} \\ & {\quad = \{x \in \mathbb {Z} \mid \exists a \in \mathbb {Z} \colon (x - k = n \cdot a) \}.} \end{array}
$$

将模 n 的所有同余类组成的集合定义为 $\mathbb { Z } / n \mathbb { Z }$，有时也记作 $\mathbb { Z } _ { n }$。由带余除法可知，这是一个包含 n 个元素的有限集合：

$$
\mathbb {Z} _ {n} = \{\overline {{0}}, \overline {{1}}, \dots , \overline {{n - 1}} \}
$$

对所有 ${ \overline { { a } } } , { \overline { { b } } } \in \mathbb { Z } _ { n }$，定义

$$
\overline {{a}} \oplus \overline {{b}} := \overline {{a + b}}
$$

**(a)** 证明 $( \mathbb { Z } _ { n } , \oplus )$ 是群。它是否为阿贝尔群？

**(b)** 对 $\mathbb { Z } _ { n }$ 中的所有 $\bar{a}$ 和 $\bar{b}$，定义另一种运算 $\otimes$：

$$
\overline {{a}} \otimes \overline {{b}} = \overline {{a \times b}},\tag{2.135}
$$

其中 $a \times b$ 表示 $\mathbb { Z }$ 中通常的乘法。

令 $n=5$。列出 $\mathbb { Z } _ { 5 } \backslash \{ \overline { { 0 } } \}$ 中各元素在运算 $\otimes$ 下的乘法表，即计算 $\mathbb { Z } _ { 5 } \backslash \{ \overline { { 0 } } \}$ 中所有 $\bar{a}$、$\bar{b}$ 的乘积 $\overline { { a } } \otimes \overline { { b } }$。

据此证明，$\mathbb { Z } _ { 5 } \backslash \{ \overline { { 0 } } \}$ 对 $\otimes$ 封闭，并且存在运算 $\otimes$ 的单位元。列出 $\mathbb { Z } _ { 5 } \backslash \{ \overline { { 0 } } \}$ 中所有元素在 $\otimes$ 下的逆元，从而得出 $( \mathbb { Z } _ { 5 } \backslash \{ \overline { { 0 } } \} , \otimes )$ 是阿贝尔群。

**(c)** 证明 $( \mathbb { Z } _ { 8 } \backslash \{ \overline { { 0 } } \} , \otimes )$ 不是群。

**(d)** 回顾 Bézout 定理：两个整数 a、b 互素，即 $\gcd(a,b)=1$，当且仅当存在整数 u、v 使 $au+bv=1$。证明 $( \mathbb { Z } _ { n } \backslash \{ \overline { { 0 } } \} , \otimes )$ 是群，当且仅当 $n\in\mathbb{N}\backslash\{0\}$ 是素数。

**2.3.** 考虑以下定义的 $3 \times 3$ 矩阵集合 $\mathcal { G }$：

$$
\mathcal {G} = \left\{\left[ \begin{array}{c c c} 1 & x & z \\ 0 & 1 & y \\ 0 & 0 & 1 \end{array} \right] \in \mathbb {R} ^ {3 \times 3}   \middle |   x, y, z \in \mathbb {R} \right\}
$$

定义 · 为标准矩阵乘法。

$( { \mathcal { G } } , \cdot )$ 是否为群？如果是，是否为阿贝尔群？说明理由。

**2.4.** 若乘积有定义，计算下列矩阵乘积：

**(a)**

$$
\left[ \begin{array}{c c} 1 & 2 \\ 4 & 5 \\ 7 & 8 \end{array} \right] \left[ \begin{array}{c c c} 1 & 1 & 0 \\ 0 & 1 & 1 \\ 1 & 0 & 1 \end{array} \right]
$$

**(b)**

$$
{\left[ \begin{array}{l l l} 1 & 2 & 3 \\ 4 & 5 & 6 \\ 7 & 8 & 9 \end{array} \right]} {\left[ \begin{array}{l l l} 1 & 1 & 0 \\ 0 & 1 & 1 \\ 1 & 0 & 1 \end{array} \right]}
$$

**(c)**

$$
\left[ \begin{array}{c c c} 1 & 1 & 0 \\ 0 & 1 & 1 \\ 1 & 0 & 1 \end{array} \right] \left[ \begin{array}{c c c} 1 & 2 & 3 \\ 4 & 5 & 6 \\ 7 & 8 & 9 \end{array} \right]
$$

**(d)**

$$
\left[ \begin{array}{c c c c} 1 & 2 & 1 & 2 \\ 4 & 1 & - 1 & - 4 \end{array} \right] \left[ \begin{array}{c c} 0 & 3 \\ 1 & - 1 \\ 2 & 1 \\ 5 & 2 \end{array} \right]
$$

**(e)**

$$
\left[ \begin{array}{c c} 0 & 3 \\ 1 & - 1 \\ 2 & 1 \\ 5 & 2 \end{array} \right] \left[ \begin{array}{c c c c} 1 & 2 & 1 & 2 \\ 4 & 1 & - 1 & - 4 \end{array} \right]
$$

**2.5.** 求以下非齐次线性方程组 $\mathbf { { A } } \mathbf { { x } } = \mathbf { { b } }$ 关于 x 的全部解组成的集合 S，其中 A 和 b 定义如下：

**(a)**

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c} 1 & 1 & - 1 & - 1 \\ 2 & 5 & - 7 & - 5 \\ 2 & - 1 & 1 & 3 \\ 5 & 2 & - 4 & 2 \end{array} \right], \quad \boldsymbol {b} = \left[ \begin{array}{c} 1 \\ - 2 \\ 4 \\ 6 \end{array} \right]
$$

**(b)**

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c c} 1 & - 1 & 0 & 0 & 1 \\ 1 & 1 & 0 & - 3 & 0 \\ 2 & - 1 & 0 & 1 & - 1 \\ - 1 & 2 & 0 & - 2 & - 1 \end{array} \right], \quad \boldsymbol {b} = \left[ \begin{array}{c} 3 \\ 6 \\ 5 \\ - 1 \end{array} \right]
$$

**2.6.** 用高斯消元求非齐次方程组 $\mathbf { A } { \boldsymbol { \mathbf { \mathit { x } } } } = \mathbf { \mathit { b } }$ 的全部解，其中

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c c c} 0 & 1 & 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1 & 1 & 0 \\ 0 & 1 & 0 & 0 & 0 & 1 \end{array} \right], \quad \boldsymbol {b} = \left[ \begin{array}{c} 2 \\ - 1 \\ 1 \end{array} \right].
$$

**2.7.** 求方程组 $A\boldsymbol{x}=12\boldsymbol{x}$ 关于 $\pmb { x } = \left[ \begin{array} { l } { x _ { 1 } } \\ { x _ { 2 } } \\ { x _ { 3 } } \end{array} \right] \in \mathbb { R } ^ { 3 }$ 的全部解，其中

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 6 & 4 & 3 \\ 6 & 0 & 9 \\ 0 & 8 & 0 \end{array} \right]
$$

并且 $\textstyle \sum _ { i = 1 } ^ { 3 } x _ { i } = 1$。

**2.8.** 若逆存在，求下列矩阵的逆：

**(a)**

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 2 & 3 & 4 \\ 3 & 4 & 5 \\ 4 & 5 & 6 \end{array} \right]
$$

**(b)**

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c} 1 & 0 & 1 & 0 \\ 0 & 1 & 1 & 0 \\ 1 & 1 & 0 & 1 \\ 1 & 1 & 1 & 0 \end{array} \right]
$$

**2.9.** 下列哪些集合是 $\mathbb { R } ^ { 3 }$ 的子空间？

**(a)** $A = \{ ( \lambda , \lambda + \mu ^ { 3 } , \lambda - \mu ^ { 3 } ) \mid \lambda , \mu \in \mathbb { R } \}$。

**(b)** $B = \{ ( \lambda ^ { 2 } , - \lambda ^ { 2 } , 0 ) \mid \lambda \in \mathbb { R } \}$。

**(c)** 设 $\gamma\in\mathbb{R}$。

$$
C = \left\{\left(\xi_ {1}, \xi_ {2}, \xi_ {3}\right) \in \mathbb {R} ^ {3} \mid \xi_ {1} - 2 \xi_ {2} + 3 \xi_ {3} = \gamma \right\}
$$

**(d)** $D = \{ ( \xi _ { 1 } , \xi _ { 2 } , \xi _ { 3 } ) \in \mathbb { R } ^ { 3 } \mid \xi _ { 2 } \in \mathbb { Z } \}$。

**2.10.** 下列各组向量是否线性无关？

**(a)**

$$
\boldsymbol {x} _ {1} = \left[ \begin{array}{l} 2 \\ - 1 \\ 3 \end{array} \right], \quad \boldsymbol {x} _ {2} = \left[ \begin{array}{l} 1 \\ 1 \\ - 2 \end{array} \right], \quad \boldsymbol {x} _ {3} = \left[ \begin{array}{l} 3 \\ - 3 \\ 8 \end{array} \right]
$$

**(b)**

$$
\boldsymbol {x} _ {1} = \left[ \begin{array}{l} 1 \\ 2 \\ 1 \\ 0 \\ 0 \end{array} \right], \quad \boldsymbol {x} _ {2} = \left[ \begin{array}{l} 1 \\ 1 \\ 0 \\ 1 \\ 1 \end{array} \right], \quad \boldsymbol {x} _ {3} = \left[ \begin{array}{l} 1 \\ 0 \\ 0 \\ 1 \\ 1 \end{array} \right]
$$

**2.11.** 将

$$
\boldsymbol {y} = \left[ \begin{array}{c} 1 \\ - 2 \\ 5 \end{array} \right]
$$

表示为下列向量的线性组合：

$$
\boldsymbol {x} _ {1} = \left[ \begin{array}{l} 1 \\ 1 \\ 1 \end{array} \right], \quad \boldsymbol {x} _ {2} = \left[ \begin{array}{l} 1 \\ 2 \\ 3 \end{array} \right], \quad \boldsymbol {x} _ {3} = \left[ \begin{array}{l} 2 \\ - 1 \\ 1 \end{array} \right]
$$

**2.12.** 考虑 $\mathbb { R } ^ { 4 }$ 的两个子空间：

$$
U_1=\operatorname{span}\left[\begin{bmatrix}1\\1\\-3\\1\end{bmatrix},\begin{bmatrix}2\\-1\\0\\-1\end{bmatrix},\begin{bmatrix}-1\\1\\-1\\1\end{bmatrix}\right],
\qquad
U_2=\operatorname{span}\left[\begin{bmatrix}-1\\-2\\2\\1\end{bmatrix},\begin{bmatrix}2\\-2\\0\\0\end{bmatrix},\begin{bmatrix}-3\\6\\-2\\-1\end{bmatrix}\right].
$$

求 $U _ { 1 } \cap U _ { 2 }$ 的一组基。

**2.13.** 考虑两个子空间 $U _ { 1 }$ 和 $U _ { 2 }$，其中 $U _ { 1 }$ 是齐次方程组 $\pmb { A } _ { 1 } \pmb { x } = \mathbf { 0 }$ 的解空间，$U _ { 2 }$ 是齐次方程组 $\pmb { A } _ { 2 } \pmb { x } = \mathbf { 0 }$ 的解空间，且

$$
\boldsymbol {A} _ {1} = \left[ \begin{array}{c c c} 1 & 0 & 1 \\ 1 & - 2 & - 1 \\ 2 & 1 & 3 \\ 1 & 0 & 1 \end{array} \right], \quad \boldsymbol {A} _ {2} = \left[ \begin{array}{c c c} 3 & - 3 & 0 \\ 1 & 2 & 3 \\ 7 & - 5 & 2 \\ 3 & - 1 & 2 \end{array} \right].
$$

**(a)** 求 $U _ { 1 } , U _ { 2 }$ 的维数。

**(b)** 分别求 $U _ { 1 }$ 和 $U _ { 2 }$ 的一组基。

**(c)** 求 $U _ { 1 } \cap U _ { 2 }$ 的一组基。

**2.14.** 考虑两个子空间 $U _ { 1 }$ 和 $U _ { 2 }$，其中 $U _ { 1 }$ 由 $\pmb { A } _ { 1 }$ 的各列张成，$U _ { 2 }$ 由 $A _ { 2 }$ 的各列张成，且

$$
\boldsymbol {A} _ {1} = \left[ \begin{array}{c c c} 1 & 0 & 1 \\ 1 & - 2 & - 1 \\ 2 & 1 & 3 \\ 1 & 0 & 1 \end{array} \right], \quad \boldsymbol {A} _ {2} = \left[ \begin{array}{c c c} 3 & - 3 & 0 \\ 1 & 2 & 3 \\ 7 & - 5 & 2 \\ 3 & - 1 & 2 \end{array} \right].
$$

**(a)** 求 $U _ { 1 } , U _ { 2 }$ 的维数。

**(b)** 分别求 $U _ { 1 }$ 和 $U _ { 2 }$ 的一组基。

**(c)** 求 $U _ { 1 } \cap U _ { 2 }$ 的一组基。

**2.15.** 设 $F = \{ ( x , y , z ) \in \mathbb { R } ^ { 3 } \mid x + y - z = 0 \}$，以及 $G = \{ ( a - b , a + b , a - 3 b ) \mid a , b \in \mathbb { R } \}$。

**(a)** 证明 F 和 G 是 $\mathbb { R } ^ { 3 }$ 的子空间。

**(b)** 不借助任何基向量，求 $F \cap G$。

**(c)** 分别求 F 和 $G$ 的一组基，利用所求基向量计算 $F \cap G$，并与上一问的结果核对。

**2.16.** 下列映射是否线性？

**(a)** 设 $a , b \in \mathbb { R }$。

$$
\begin{array}{c} \Phi : L ^ {1} ([ a, b ]) \to \mathbb {R} \\ f \mapsto \Phi (f) = \int_ {a} ^ {b} f (x) d x  , \end{array}
$$

其中 $L ^ { 1 } ( [ a , b ] )$ 表示 $[ a , b ]$ 上可积函数组成的集合。

**(b)**

$$
\begin{array}{c} \Phi : C ^ {1} \to C ^ {0} \\ f \mapsto \Phi (f) = f ^ {\prime}, \end{array}
$$

其中，对 $k\geqslant1$，$C^k$ 表示 $k$ 次连续可微函数组成的集合，$C ^ { 0 }$ 表示连续函数组成的集合。

**(c)**

$$
\begin{array}{c} \Phi : \mathbb {R} \to \mathbb {R} \\ x \mapsto \Phi (x) = \cos (x) \end{array}
$$

**(d)**

$$
\Phi : \mathbb {R} ^ {3} \to \mathbb {R} ^ {2}
$$

$$
\boldsymbol {x} \mapsto \left[ \begin{array}{c c c} 1 & 2 & 3 \\ 1 & 4 & 3 \end{array} \right] \boldsymbol {x}
$$

**(e)** 设 θ 属于 $[ 0 , 2 \pi [$，并且

$$
\Phi : \mathbb {R} ^ {2} \to \mathbb {R} ^ {2}
$$

$$
\pmb {x} \mapsto \left[ \begin{array}{c c} \cos (\theta) & \sin (\theta) \\ - \sin (\theta) & \cos (\theta) \end{array} \right] \pmb {x}
$$

**2.17.** 考虑线性映射

$$
\Phi : \mathbb {R} ^ {3} \to \mathbb {R} ^ {4}
$$

$$
\Phi \left(\left[ \begin{array}{c} x _ {1} \\ x _ {2} \\ x _ {3} \end{array} \right]\right) = \left[ \begin{array}{c} 3 x _ {1} + 2 x _ {2} + x _ {3} \\ x _ {1} + x _ {2} + x _ {3} \\ x _ {1} - 3 x _ {2} \\ 2 x _ {1} + 3 x _ {2} + x _ {3} \end{array} \right]
$$

- 求变换矩阵 $A _ { \Phi }$。

- 求 $\operatorname{rk}(A_{\Phi})$。

- 计算 Φ 的核与像。$\dim(\ker(\Phi))$ 和 $\dim(\operatorname{Im}(\Phi))$ 分别是多少？

**2.18.** 设 $E$ 是向量空间，$f$ 和 $g$ 是 $E$ 上的两个自同构，满足 $f\circ g=\operatorname{id}_E$，即 $f\circ g$ 是恒等映射 $\operatorname{id}_E$。证明 $\ker(f)=\ker(g\circ f)$、$\operatorname{Im}(g)=\operatorname{Im}(g\circ f)$，以及 $\ker(f)\cap\operatorname{Im}(g)=\{\boldsymbol{0}_E\}$。

**2.19.** 考虑自同态 $\Phi:\mathbb{R}^{3}\to\mathbb{R}^{3}$，其关于 $\mathbb { R } ^ { 3 }$ 中标准基的变换矩阵为

$$
\boldsymbol {A} _ {\Phi} = \left[ \begin{array}{c c c} 1 & 1 & 0 \\ 1 & - 1 & 0 \\ 1 & 1 & 1 \end{array} \right].
$$

**(a)** 求 ker(Φ) 和 Im(Φ)。

**(b)** 求关于以下基的变换矩阵 $\tilde { \mathbf { A } } _ { \Phi }$：

$$
B = (\left[ \begin{array}{c} 1 \\ 1 \\ 1 \end{array} \right], \left[ \begin{array}{c} 1 \\ 2 \\ 1 \end{array} \right], \left[ \begin{array}{c} 1 \\ 0 \\ 0 \end{array} \right]),
$$

即向新基 $B$ 作基变换。

**2.20.** 考虑 $\mathbb { R } ^ { 2 }$ 中的四个向量 $b _ { 1 } , b _ { 2 } , b _ { 1 } ^ { \prime } , b _ { 2 } ^ { \prime }$，它们在 $\mathbb { R } ^ { 2 }$ 的标准基下表示为

$$
\boldsymbol {b} _ {1} = \left[ \begin{array}{c} 2 \\ 1 \end{array} \right], \quad \boldsymbol {b} _ {2} = \left[ \begin{array}{c} - 1 \\ - 1 \end{array} \right], \quad \boldsymbol {b} _ {1} ^ {\prime} = \left[ \begin{array}{c} 2 \\ - 2 \end{array} \right], \quad \boldsymbol {b} _ {2} ^ {\prime} = \left[ \begin{array}{c} 1 \\ 1 \end{array} \right]
$$

并定义 $\textstyle \mathbb { R } ^ { 2 }$ 的两组有序基 $B = ( b _ { 1 } , b _ { 2 } )$ 和 $B ^ { \prime } = ( b _ { 1 } ^ { \prime } , b _ { 2 } ^ { \prime } )$。

**(a)** 证明 B 和 $B ^ { \prime }$ 是 $\mathbb { R } ^ { 2 }$ 的两组基，并画出这些基向量。

**(b)** 求将基 $B ^ { \prime }$ 下的坐标转换为基 $B$ 下坐标的矩阵 $P _ { 1 }$。

**(c)** 考虑 $\mathbb { R } ^ { 3 }$ 中的三个向量 $c_1,c_2,c_3$，它们在 $\mathbb { R } ^ { 3 }$ 的标准基下定义为

$$
\boldsymbol {c} _ {1} = \left[ \begin{array}{l} 1 \\ 2 \\ - 1 \end{array} \right], \quad \boldsymbol {c} _ {2} = \left[ \begin{array}{l} 0 \\ - 1 \\ 2 \end{array} \right], \quad \boldsymbol {c} _ {3} = \left[ \begin{array}{l} 1 \\ 0 \\ - 1 \end{array} \right]
$$

并定义 $C = ( c _ { 1 } , c _ { 2 } , c _ { 3 } )$。

**(i)** 证明 C 是 $\mathbb { R } ^ { 3 }$ 的一组基，例如可使用行列式，见 4.1 节。

**(ii)** 记 $C ^ { \prime } = ( c _ { 1 } ^ { \prime } , c _ { 2 } ^ { \prime } , c _ { 3 } ^ { \prime } )$ 为 $\mathbb { R } ^ { 3 }$ 的标准基。求从 $C$ 到 $C ^ { \prime }$ 的基变换矩阵 $\scriptstyle P _ { 2 }$。

**(d)** 考虑同态 $\Phi : \mathbb { R } ^ { 2 } \longrightarrow \mathbb { R } ^ { 3 }$，满足

$$
\begin{array}{r c l} \Phi (\boldsymbol {b} _ {1} + \boldsymbol {b} _ {2}) & = & \boldsymbol {c} _ {2} + \boldsymbol {c} _ {3} \\ \Phi (\boldsymbol {b} _ {1} - \boldsymbol {b} _ {2}) & = & 2 \boldsymbol {c} _ {1} - \boldsymbol {c} _ {2} + 3 \boldsymbol {c} _ {3} \end{array}
$$

其中 $B = ( b _ { 1 } , b _ { 2 } )$ 和 $C = ( c _ { 1 } , c _ { 2 } , c _ { 3 } )$ 分别为 $\textstyle \mathbb { R } ^ { 2 }$ 与 $\mathbb { R } ^ { 3 }$ 的有序基。

求 Φ 关于有序基 $B$ 和 $C$ 的变换矩阵 $A _ { \Phi }$。

**(e)** 求 Φ 关于基 $B ^ { \prime }$ 和 $C ^ { \prime }$ 的变换矩阵 $A^{\prime}$。

**(f)** 考虑向量 $\pmb { x } \in \mathbb { R } ^ { 2 }$，其关于 $B ^ { \prime }$ 的坐标为 $[ 2 , 3 ] ^ { \top }$。换言之，${ \pmb x } = 2 b _ { 1 } ^ { \prime } + 3 b _ { 2 } ^ { \prime }$。

**(i)** 计算 x 关于 $B$ 的坐标。

**(ii)** 据此计算 $\Phi ( { \pmb x } )$ 关于 $C$ 的坐标。

**(iii)** 再用 $\mathbf { } c _ { 1 } ^ { \prime } , \mathbf { } c _ { 2 } ^ { \prime } , c _ { 3 } ^ { \prime }$ 表示 $\Phi ( { \pmb x } )$。

**(iv)** 利用 x 关于 $B ^ { \prime }$ 的表示和矩阵 $A ^ { \prime }$，直接求得这一结果。

[^array-vector-operations]: 在计算机上实现时，要仔细检查数组运算是否确实执行了向量运算。
