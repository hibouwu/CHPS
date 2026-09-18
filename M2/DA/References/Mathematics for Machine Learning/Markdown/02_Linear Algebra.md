# 2 Linear Algebra

![Chapter 2 emblem](<Images/02_Linear_Algebra_image_001.jpg>)

When formalizing intuitive concepts, a common approach is to construct a set of objects (symbols) and a set of rules to manipulate these objects. This is known as an algebra. Linear algebra is the study of vectors and certain rules to manipulate vectors. The vectors many of us know from school are called “geometric vectors”, which are usually denoted by a small arrow above the letter, e.g., $\vec{x}$ and $\vec{y}$ . In this book, we discuss more general concepts of vectors and use a bold letter to represent them, e.g., $\boldsymbol{x}$ and $\boldsymbol{y}$. 

In general, vectors are special objects that can be added together and multiplied by scalars to produce another object of the same kind. From an abstract mathematical viewpoint, any object that satisfies these two properties can be considered a vector. Here are some examples of such vector objects: 

1. Geometric vectors. This example of a vector may be familiar from high school mathematics and physics. Geometric vectors – see Figure 2.1(a) – are directed segments, which can be drawn (at least in two dimensions). Two geometric vectors $\vec { x }$ , $\vec { y }$ can be added, such that $\vec{x}+\vec{y}=\vec{z}$ is another geometric vector. Furthermore, multiplication by a scalar $\lambda { \vec { x } } , \lambda \in \mathbb { R } ,$ is also a geometric vector. In fact, it is the original vector scaled by $\lambda .$ Therefore, geometric vectors are instances of the vector concepts introduced previously. Interpreting vectors as geometric vectors enables us to use our intuitions about direction and magnitude to reason about mathematical operations. 

2. Polynomials are also vectors; see Figure 2.1(b): Two polynomials can be added together, which results in another polynomial; and they can be multiplied by a scalar $\lambda\in\mathbb{R}$, and the result is a polynomial as well. Therefore, polynomials are (rather unusual) instances of vectors. Note that polynomials are very different from geometric vectors. While geometric vectors are concrete “drawings”, polynomials are abstract concepts. However, they are both vectors in the sense previously described. 

3. Audio signals are vectors. Audio signals are represented as a series of numbers. We can add audio signals together, and their sum is a new audio signal. If we scale an audio signal, we also obtain an audio signal. Therefore, audio signals are a type of vector, too. 

4. Elements of $\mathbb { R } ^ { n }$ (tuples of $n$ real numbers) are vectors. $\mathbb { R } ^ { n }$ is more abstract than polynomials, and it is the concept we focus on in this book. For instance, 

$$
\boldsymbol {a} = \left[ \begin{array}{c} 1 \\ 2 \\ 3 \end{array} \right] \in \mathbb {R} ^ {3}\tag{2.1}
$$

is an example of a triplet of numbers. Adding two vectors $\boldsymbol{a}, \boldsymbol{b} \in \mathbb{R}^{n}$ component-wise results in another vector: $\pmb { a } + \pmb { b } = \pmb { c } \in \mathbb { R } ^ { n }$ . Moreover, multiplying $\pmb { a } \in \mathbb { R } ^ { n }$ by $\lambda \in \mathbb { R }$ results in a scaled vector $\lambda\boldsymbol{a}\in\mathbb{R}^{n}$. Considering vectors as elements of $\mathbb { R } ^ { n }$ has an additional benefit that it loosely corresponds to arrays of real numbers on a computer.[^array-vector-operations] Many programming languages support array operations, which allow for convenient implementation of algorithms that involve vector operations. 

![image](<Images/02_Linear_Algebra_image_002.jpg>)

(a) Geometric vectors.

![image](<Images/02_Linear_Algebra_image_003.jpg>)

(b) Polynomials.

Figure 2.1 Different types of vectors. Vectors can be surprising objects, including (a) geometric vectors and (b) polynomials.

Linear algebra focuses on the similarities between these vector concepts. We can add them together and multiply them by scalars. We will largely focus on vectors in $\mathbb { R } ^ { n }$ since most algorithms in linear algebra are formulated in $\mathbb { R } ^ { n }$ . We will see in Chapter 8 that we often consider data to be represented as vectors in $\mathbb { R } ^ { n }$ . In this book, we will focus on finite-dimensional vector spaces, in which case there is a 1:1 correspondence between any kind of vector and $\mathbb { R } ^ { n }$ . When it is convenient, we will use intuitions about geometric vectors and consider array-based algorithms. 

One major idea in mathematics is the idea of “closure”. This is the question: What is the set of all things that can result from my proposed operations? In the case of vectors: What is the set of vectors that can result by starting with a small set of vectors, and adding them to each other and scaling them? This results in a vector space (Section 2.4). The concept of a vector space and its properties underlie much of machine learning. The concepts introduced in this chapter are summarized in Figure 2.2. 

This chapter is mostly based on the lecture notes and books by Drumm and Weil (2001), Strang (2003), Hogben (2013), Liesen and Mehrmann (2015), as well as [Pavel Grinfeld’s Linear Algebra series](http://tinyurl.com/nahclwm). Other excellent resources are [Gilbert Strang’s Linear Algebra course at MIT](http://tinyurl.com/bdfbu8s5) and the [Linear Algebra Series by 3Blue1Brown](https://tinyurl.com/h5g4kps). 

![image](<Images/02_Linear_Algebra_image_004.jpg>)

Figure 2.2 A mind map of the concepts introduced in this chapter, along with where they are used in other parts of the book.

Linear algebra plays an important role in machine learning and general mathematics. The concepts introduced in this chapter are further expanded to include the idea of geometry in Chapter 3. In Chapter 5, we will discuss vector calculus, where a principled knowledge of matrix operations is essential. In Chapter 10, we will use projections (to be introduced in Section 3.8) for dimensionality reduction with principal component analysis (PCA). In Chapter 9, we will discuss linear regression, where linear algebra plays a central role for solving least-squares problems. 

## 2.1 Systems of Linear Equations

Systems of linear equations play a central part of linear algebra. Many problems can be formulated as systems of linear equations, and linear algebra gives us the tools for solving them. 

**Example 2.1**

A company produces products $N _ { 1 } , \ldots , N _ { n }$ for which resources $R _ { 1 } , \ldots , R _ { m }$ are required. To produce a unit of product $N _ { j } , a _ { i j }$ units of resource $R _ { i }$ are needed, where $i = 1 , \ldots , m$ and $j = 1 , \dots , n .$ 

The objective is to find an optimal production plan, i.e., a plan of how many units $x _ { j }$ of product $N _ { j }$ should be produced if a total of $b _ { i }$ units of resource $R _ { i }$ are available and (ideally) no resources are left over. 

If we produce $x _ { 1 } , \ldots , x _ { n }$ units of the corresponding products, we need a total of 

$$
a _ {i 1} x _ {1} + \dots + a _ {i n} x _ {n}\tag{2.2}
$$

many units of resource $R _ { i }$ . An optimal production plan $( x _ { 1 } , \ldots , x _ { n } ) \in \mathbb { R } ^ { n }$ therefore, has to satisfy the following system of equations: 

$$
\begin{array}{c} a _ {1 1} x _ {1} + \dots + a _ {1 n} x _ {n} = b _ {1} \\ \vdots \\ a _ {m 1} x _ {1} + \dots + a _ {m n} x _ {n} = b _ {m} \end{array} ,\tag{2.3}
$$

where $a _ { i j } \in \mathbb { R }$ and $b _ { i } \in \mathbb { R }$ 

Equation (2.3) is the general form of a system of linear equations, and $x _ { 1 } , \ldots , x _ { n }$ are the unknowns of this system. Every n-tuple $( x _ { 1 } , \ldots , x _ { n } ) \in$ $\mathbb { R } ^ { n }$ that satisfies (2.3) is a solution of the linear equation system. 

**Example 2.2**

The system of linear equations 

$$
\begin{array}{rcrcrcl}
x_1 & + & x_2 & + & x_3 & = & 3 \quad (1) \\
x_1 & - & x_2 & + & 2x_3 & = & 2 \quad (2) \\
2x_1 & & & + & 3x_3 & = & 1 \quad (3)
\end{array}
\tag{2.4}
$$ 

has no solution: Adding the first two equations yields $2 x _ { 1 } + 3 x _ { 3 } = 5$ , which contradicts the third equation (3). 

Let us have a look at the system of linear equations 

$$
\begin{array}{rcrcrcll} x _ {1} & + & x _ {2} & + & x _ {3} & = & 3 & (1) \\ x _ {1} & - & x _ {2} & + & 2 x _ {3} & = & 2 & (2) \\ & & x _ {2} & + & x _ {3} & = & 2 & (3) \end{array} .\tag{2.5}
$$

From the first and third equation, it follows that $x _ { 1 } = 1$ . From $( 1 ) + ( 2 )$ we get $2x_1+3x_3=5$, i.e., $x_3=1$ . From (3), we then get that $x_2=1$. Therefore, (1, 1, 1) is the only possible and unique solution (verify that (1, 1, 1) is a solution by plugging in). 

As a third example, we consider 

$$
\begin{array}{c c c c c c c c} x _ {1} & + & x _ {2} & + & x _ {3} & = & 3 & (1) \\ x _ {1} & - & x _ {2} & + & 2 x _ {3} & = & 2 & (2) \\ 2 x _ {1} & & & + & 3 x _ {3} & = & 5 & (3) \end{array}\tag{2.6}
$$

Since $( 1 ) + ( 2 ) = ( 3 )$ , we can omit the third equation (redundancy). From (1) and (2), we get $2 x _ { 1 } = 5 { - } 3 x _ { 3 }$ and $2 x _ { 2 } = 1 + x _ { 3 }$ . We define $x_3=a\in\mathbb{R}$ as a free variable, such that any triplet 

$$
\left(\frac {5}{2} - \frac {3}{2} a, \frac {1}{2} + \frac {1}{2} a, a\right), \quad a \in \mathbb {R}\tag{2.7}
$$

is a solution of the system of linear equations, i.e., we obtain a solution set that contains infinitely many solutions. 

In general, for a real-valued system of linear equations we obtain either no, exactly one, or infinitely many solutions. Linear regression (Chapter 9) solves a version of Example 2.1 when we cannot solve the system of linear equations. 

**Remark (Geometric Interpretation of Systems of Linear Equations).** In a system of linear equations with two variables $x _ { 1 } , x _ { 2 }$ , each linear equation defines a line on the $x_1x_2$-plane . Since a solution to a system of linear equations must satisfy all equations simultaneously, the solution set is the intersection of these lines. This intersection set can be a line (if the linear equations describe the same line), a point, or empty (when the lines are parallel). An illustration is given in Figure 2.3 for the system 

$$
\begin{array}{l} {4 x _ {1} + 4 x _ {2} = 5} \\ {2 x _ {1} - 4 x _ {2} = 1} \end{array}\tag{2.8}
$$

where the solution space is the point $( x _ { 1 } , x _ { 2 } ) = ( 1 , { \textstyle \frac { 1 } { 4 } } )$ . Similarly, for three variables, each linear equation determines a plane in three-dimensional space. When we intersect these planes, i.e., satisfy all linear equations at the same time, we can obtain a solution set that is a plane, a line, a point or empty (when the planes have no common intersection).

![Figure 2.3: Intersection of two lines](<Images/02_Linear_Algebra_image_005.jpg>)

Figure 2.3 The solution space of a system of two linear equations with two variables can be geometrically interpreted as the intersection of two lines. Every linear equation represents a line. 

For a systematic approach to solving systems of linear equations, we will introduce a useful compact notation. We collect the coefficients $a _ { i j }$ into vectors and collect the vectors into matrices. In other words, we write the system from (2.3) in the following form: 

$$
\left[ \begin{array}{c} a _ {1 1} \\ \vdots \\ a _ {m 1} \end{array} \right] x _ {1} + \left[ \begin{array}{c} a _ {1 2} \\ \vdots \\ a _ {m 2} \end{array} \right] x _ {2} + \dots + \left[ \begin{array}{c} a _ {1 n} \\ \vdots \\ a _ {m n} \end{array} \right] x _ {n} = \left[ \begin{array}{c} b _ {1} \\ \vdots \\ b _ {m} \end{array} \right]\tag{2.9}
$$

$$
\Longleftrightarrow \left[ \begin{array}{c c c} a _ {1 1} & \dots & a _ {1 n} \\ \vdots & & \vdots \\ a _ {m 1} & \dots & a _ {m n} \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ \vdots \\ x _ {n} \end{array} \right] = \left[ \begin{array}{c} b _ {1} \\ \vdots \\ b _ {m} \end{array} \right].\tag{2.10}
$$

In the following, we will have a close look at these matrices and define computation rules. We will return to solving linear equations in Section 2.3. 

## 2.2 Matrices

Matrices play a central role in linear algebra. They can be used to compactly represent systems of linear equations, but they also represent linear functions (linear mappings) as we will see later in Section 2.7. Before we discuss some of these interesting topics, let us first define what a matrix is and what kind of operations we can do with matrices. We will see more properties of matrices in Chapter 4. 

**Definition 2.1 (Matrix).** With $m,n\in\mathbb{N}$ a real-valued $(m,n)$ matrix $\boldsymbol{A}$ is an $m\cdot n$-tuple of elements $a_{ij}$, $i=1,\ldots,m$, $j=1,\ldots,n$, which is ordered according to a rectangular scheme consisting of $m$ rows and $n$ columns:

$$
\boldsymbol{A}=\begin{bmatrix}
a_{11}&a_{12}&\cdots&a_{1n}\\
a_{21}&a_{22}&\cdots&a_{2n}\\
\vdots&\vdots&&\vdots\\
a_{m1}&a_{m2}&\cdots&a_{mn}
\end{bmatrix},\quad a_{ij}\in\mathbb{R}.
\tag{2.11}
$$

By convention $(1,n)$-matrices are called rows and $(m,1)$-matrices are called columns. These special matrices are also called row/column vectors.

$\mathbb{R}^{m\times n}$ is the set of all real-valued $(m,n)$-matrices. $\boldsymbol{A}\in\mathbb{R}^{m\times n}$ can be equivalently represented as $\boldsymbol{a}\in\mathbb{R}^{mn}$ by stacking all $n$ columns of the matrix into a long vector; see Figure 2.4.

![Figure 2.4: Stacking matrix columns](<Images/02_Linear_Algebra_image_006.jpg>)

Figure 2.4 By stacking its columns, a matrix $\boldsymbol{A}$ can be represented as a long vector $\boldsymbol{a}$.

### 2.2.1 Matrix Addition and Multiplication

The sum of two matrices $\boldsymbol{A}\in\mathbb{R}^{m\times n}$, $\boldsymbol{B}\in\mathbb{R}^{m\times n}$ is defined as the element-wise sum, i.e.,

$$
\boldsymbol{A}+\boldsymbol{B}:=\begin{bmatrix}
a_{11}+b_{11}&\cdots&a_{1n}+b_{1n}\\
\vdots&&\vdots\\
a_{m1}+b_{m1}&\cdots&a_{mn}+b_{mn}
\end{bmatrix}\in\mathbb{R}^{m\times n}.
\tag{2.12}
$$

For matrices $\boldsymbol{A}\in\mathbb{R}^{m\times n}$, $\boldsymbol{B}\in\mathbb{R}^{n\times k}$, the elements $c_{ij}$ of the product $\boldsymbol{C}=\boldsymbol{A}\boldsymbol{B}\in\mathbb{R}^{m\times k}$ are computed as

$$
c_{ij}=\sum_{l=1}^{n}a_{il}b_{lj},\quad i=1,\ldots,m,\quad j=1,\ldots,k.
\tag{2.13}
$$

> Note the size of the matrices.

```python
C = np.einsum('il,lj', A, B)
```

This means, to compute element $c _ { i j }$ we multiply the elements of the ith row of A with the jth column of B and sum them up. Later in Section 3.2, we will call this the dot product of the corresponding row and column. In cases, where we need to be explicit that we are performing multiplication, we use the notation $\pmb { A } \cdot \pmb { B }$ to denote multiplication (explicitly showing “$\cdot$”).

> There are $n$ columns in $\boldsymbol{A}$ and $n$ rows in $\boldsymbol{B}$ so that we can compute $a_{il}b_{lj}$ for $l=1,\ldots,n$.
>
> Commonly, the dot product between two vectors $\boldsymbol{a},\boldsymbol{b}$ is denoted by $\boldsymbol{a}^{\top}\boldsymbol{b}$ or $\langle\boldsymbol{a},\boldsymbol{b}\rangle$. 

Remark. Matrices can only be multiplied if their “neighboring” dimensions match. For instance, an $n\times k$-matrix $\boldsymbol{A}$ can be multiplied with a $k\times m$-matrix $\boldsymbol{B}$, but only from the left side: 

$$
\underbrace {A} _ {n \times k} \underbrace {B} _ {k \times m} = \underbrace {C} _ {n \times m}\tag{2.14}
$$

The product $\boldsymbol{B}\boldsymbol{A}$ is not defined if $m\neq n$ since the neighboring dimensions do not match. 

Remark. Matrix multiplication is not defined as an element-wise operation on matrix elements, i.e., $c_{ij}\neq a_{ij}b_{ij}$ (even if the size of $A , B$ was chosen appropriately). This kind of element-wise multiplication often appears in programming languages when we multiply (multi-dimensional) arrays with each other, and is called a Hadamard product. 

**Example 2.3**

$$
\text { For   } \boldsymbol {A} = \left[ \begin{array}{l l l} 1 & 2 & 3 \\ 3 & 2 & 1 \end{array} \right] \in \mathbb {R} ^ {2 \times 3},   \boldsymbol {B} = \left[ \begin{array}{l l} 0 & 2 \\ 1 & - 1 \\ 0 & 1 \end{array} \right] \in \mathbb {R} ^ {3 \times 2},   \text { we   obtain }
$$

$$
\boldsymbol {A} \boldsymbol {B} = \left[ \begin{array}{c c c} 1 & 2 & 3 \\ 3 & 2 & 1 \end{array} \right] \left[ \begin{array}{c c} 0 & 2 \\ 1 & - 1 \\ 0 & 1 \end{array} \right] = \left[ \begin{array}{c c} 2 & 3 \\ 2 & 5 \end{array} \right] \in \mathbb {R} ^ {2 \times 2},\tag{2.15}
$$

$$
\boldsymbol {B} \boldsymbol {A} = \left[ \begin{array}{c c} 0 & 2 \\ 1 & - 1 \\ 0 & 1 \end{array} \right] \left[ \begin{array}{c c c} 1 & 2 & 3 \\ 3 & 2 & 1 \end{array} \right] = \left[ \begin{array}{c c c} 6 & 4 & 2 \\ - 2 & 0 & 2 \\ 3 & 2 & 1 \end{array} \right] \in \mathbb {R} ^ {3 \times 3}.\tag{2.16}
$$

From this example, we can already see that matrix multiplication is not commutative, i.e., $\boldsymbol{A}\boldsymbol{B}\neq\boldsymbol{B}\boldsymbol{A}$; see also Figure 2.5 for an illustration. 

![Figure 2.5: Shapes of AB and BA](<Images/02_Linear_Algebra_image_007.jpg>)

Figure 2.5 Even if both matrix multiplications $AB$ and $BA$ are defined, the dimensions of the results can be different.

**Definition 2.2 (Identity Matrix).** In $\mathbb { R } ^ { n \times n }$ , we define the identity matrix 

$$
\boldsymbol {I} _ {n} := \left[ \begin{array}{c c c c c c} 1 & 0 & \dots & 0 & \dots & 0 \\ 0 & 1 & \dots & 0 & \dots & 0 \\ \vdots & \vdots & \ddots & \vdots & \ddots & \vdots \\ 0 & 0 & \dots & 1 & \dots & 0 \\ \vdots & \vdots & \ddots & \vdots & \ddots & \vdots \\ 0 & 0 & \dots & 0 & \dots & 1 \end{array} \right] \in \mathbb {R} ^ {n \times n}\tag{2.17}
$$

as the $n\times n$-matrix containing 1 on the diagonal and 0 everywhere else. 

Now that we defined matrix multiplication, matrix addition and the identity matrix, let us have a look at some properties of matrices: 

- **Associativity:** 

$$
\forall \boldsymbol {A} \in \mathbb {R} ^ {m \times n}, \boldsymbol {B} \in \mathbb {R} ^ {n \times p}, \boldsymbol {C} \in \mathbb {R} ^ {p \times q}: (\boldsymbol {A B}) \boldsymbol {C} = \boldsymbol {A} (\boldsymbol {B C})\tag{2.18}
$$

- **Distributivity:** 

$$
\forall \boldsymbol {A}, \boldsymbol {B} \in \mathbb {R} ^ {m \times n}, \boldsymbol {C}, \boldsymbol {D} \in \mathbb {R} ^ {n \times p}: (\boldsymbol {A} + \boldsymbol {B}) \boldsymbol {C} = \boldsymbol {A C} + \boldsymbol {B C}\tag{2.19a}
$$

$$
\boldsymbol {A} (\boldsymbol {C} + \boldsymbol {D}) = \boldsymbol {A C} + \boldsymbol {A D}\tag{2.19b}
$$

- **Multiplication with the identity matrix:** 

$$
\forall \boldsymbol {A} \in \mathbb {R} ^ {m \times n}: \boldsymbol {I} _ {m} \boldsymbol {A} = \boldsymbol {A} \boldsymbol {I} _ {n} = \boldsymbol {A}\tag{2.20}
$$

Note that ${ \pmb { I } } _ { m } \neq { \pmb { I } } _ { n }$ for $m\neq n$. 

### 2.2.2 Inverse and Transpose

**Definition 2.3 (Inverse).** Consider a square matrix $A \in \mathbb { R } ^ { n \times n }$ . Let matrix $B \in \mathbb { R } ^ { n \times n }$ have the property that $A B = I _ { n } = B A$ . B is called the inverse of A and denoted by $A^{-1}$. 

> A square matrix possesses the same number of columns and rows.

Unfortunately, not every matrix A possesses an inverse $A ^ { - 1 }$ . If this inverse does exist, A is called regular/invertible/nonsingular, otherwise singular/noninvertible. When the matrix inverse exists, it is unique. In Section 2.3, we will discuss a general way to compute the inverse of a matrix by solving a system of linear equations. 

**Remark (Existence of the Inverse of a $2\times2$-matrix).** Consider a matrix 

$$
\boldsymbol {A} := \left[ \begin{array}{c c} a _ {1 1} & a _ {1 2} \\ a _ {2 1} & a _ {2 2} \end{array} \right] \in \mathbb {R} ^ {2 \times 2}.\tag{2.21}
$$

If we multiply A with 

$$
\boldsymbol {A} ^ {\prime} := \left[ \begin{array}{c c} a _ {2 2} & - a _ {1 2} \\ - a _ {2 1} & a _ {1 1} \end{array} \right]\tag{2.22}
$$

we obtain 

$$
\boldsymbol {A} \boldsymbol {A} ^ {\prime} = \left[ \begin{array}{c c} a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1} & 0 \\ 0 & a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1} \end{array} \right] = (a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1}) \boldsymbol {I}.\tag{2.23}
$$

Therefore, 

$$
\pmb {A} ^ {- 1} = \frac {1}{a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1}} \left[ \begin{array}{c c} a _ {2 2} & - a _ {1 2} \\ - a _ {2 1} & a _ {1 1} \end{array} \right]\tag{2.24}
$$

if and only if $a _ { 1 1 } a _ { 2 2 } - a _ { 1 2 } a _ { 2 1 } \neq 0$ . In Section 4.1, we will see that $a_{11}a_{22}-a_{12}a_{21}$ is the determinant of a $2\times2$-matrix. Furthermore, we can generally use the determinant to check whether a matrix is invertible. 

**Example 2.4 (Inverse Matrix)**

The matrices 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 1 & 2 & 1 \\ 4 & 4 & 5 \\ 6 & 7 & 7 \end{array} \right], \quad \boldsymbol {B} = \left[ \begin{array}{c c c} - 7 & - 7 & 6 \\ 2 & 1 & - 1 \\ 4 & 5 & - 4 \end{array} \right]\tag{2.25}
$$

are inverse to each other since $AB=I=BA$. 

**Definition 2.4 (Transpose).** For $\pmb { A } \in \mathbb { R } ^ { m \times n }$ the matrix $B \in \mathbb { R } ^ { n \times m }$ with $b _ { i j } = a _ { j i }$ is called the transpose of A. We write $\boldsymbol{B}=\boldsymbol{A}^{\top}$. 

In general, $A ^ { \top }$ can be obtained by writing the columns of A as the rows of $A ^ { \top }$ . The following are important properties of inverses and transposes: 

> The main diagonal (sometimes called “principal diagonal”, “primary diagonal”, “leading diagonal”, or “major diagonal”) of a matrix $\boldsymbol{A}$ is the collection of entries $A_{ij}$ where $i=j$.

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

> The scalar case of (2.28) is $\frac{1}{2+4}=\frac{1}{6}\neq\frac{1}{2}+\frac{1}{4}$.

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

**Definition 2.5 (Symmetric Matrix).** A matrix $A \in \mathbb { R } ^ { n \times n }$ is symmetric if $\boldsymbol{A}=\boldsymbol{A}^{\top}$. 

Note that only $( n , n )$ -matrices can be symmetric. Generally, we call $( n , n )$ -matrices also square matrices because they possess the same number of rows and columns. Moreover, if A is invertible, then so is $A ^ { \top }$ , and $( A ^ { - 1 } ) ^ { \top } = ( A ^ { \top } ) ^ { - 1 } = : A ^ { - \top }$ 

**Remark (Sum and Product of Symmetric Matrices).** The sum of symmetric matrices $\pmb { A } , \pmb { B } \in \mathbb { R } ^ { n \times n }$ is always symmetric. However, although their product is always defined, it is generally not symmetric: 

$$
\left[ \begin{array}{c c} 1 & 0 \\ 0 & 0 \end{array} \right] \left[ \begin{array}{c c} 1 & 1 \\ 1 & 1 \end{array} \right] = \left[ \begin{array}{c c} 1 & 1 \\ 0 & 0 \end{array} \right].\tag{2.32}
$$

### 2.2.3 Multiplication by a Scalar

Let us look at what happens to matrices when they are multiplied by a scalar $\lambda \in \mathbb { R }$ . Let $\pmb { A } \in \mathbb { R } ^ { m \times n }$ and $\lambda \in \mathbb { R }$ . Then $\lambda A=K$, $K_{ij}=\lambda a_{ij}$. Practically, λ scales each element of A. For $\lambda , \psi \in \mathbb { R } ,$ the following holds: 

- **Associativity:** 

$$
(\lambda \psi) \boldsymbol {C} = \lambda (\psi \boldsymbol {C}), \quad \boldsymbol {C} \in \mathbb {R} ^ {m \times n}
$$

- $\lambda ( B C ) = ( \lambda B ) C = B ( \lambda C ) = ( B C ) \lambda , \quad B \in \mathbb { R } ^ { m \times n } , C \in \mathbb { R } ^ { n \times k } .$ 

Note that this allows us to move scalar values around. 

- $( \lambda C ) ^ { \top } = C ^ { \top } \lambda ^ { \top } = C ^ { \top } \lambda = \lambda C ^ { \top }$ since $\lambda = \lambda ^ { \top }$ for all $\lambda\in\mathbb{R}$. 

- **Distributivity:** 

$$
(\lambda + \psi) \boldsymbol {C} = \lambda \boldsymbol {C} + \psi \boldsymbol {C}, \quad \boldsymbol {C} \in \mathbb {R} ^ {m \times n}
$$

$$
\lambda (\boldsymbol {B} + \boldsymbol {C}) = \lambda \boldsymbol {B} + \lambda \boldsymbol {C}, \quad \boldsymbol {B}, \boldsymbol {C} \in \mathbb {R} ^ {m \times n}
$$

**Example 2.5 (Distributivity)**

If we define 

$$
\boldsymbol {C} := \left[ \begin{array}{c c} 1 & 2 \\ 3 & 4 \end{array} \right],\tag{2.33}
$$

then for any $\lambda , \psi \in \mathbb { R }$ we obtain 

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

### 2.2.4 Compact Representations of Systems of Linear Equations

If we consider the system of linear equations 

$$
\begin{array}{l} 2 x _ {1} + 3 x _ {2} + 5 x _ {3} = 1 \\ 4 x _ {1} - 2 x _ {2} - 7 x _ {3} = 8 \\ 9 x _ {1} + 5 x _ {2} - 3 x _ {3} = 2 \end{array}\tag{2.35}
$$

and use the rules for matrix multiplication, we can write this equation system in a more compact form as 

$$
\left[ \begin{array}{c c c} 2 & 3 & 5 \\ 4 & - 2 & - 7 \\ 9 & 5 & - 3 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \\ x _ {3} \end{array} \right] = \left[ \begin{array}{c} 1 \\ 8 \\ 2 \end{array} \right].\tag{2.36}
$$

Note that $x _ { 1 }$ scales the first column, $x _ { 2 }$ the second one, and $x _ { 3 }$ the third one. 

Generally, a system of linear equations can be compactly represented in their matrix form as $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{b}$; see (2.3), and the product $\boldsymbol{A}\boldsymbol{x}$ is a (linear) combination of the columns of $\pmb { A }$ . We will discuss linear combinations in more detail in Section 2.5. 

## 2.3 Solving Systems of Linear Equations

In (2.3), we introduced the general form of an equation system, i.e., 

$$
\begin{array}{c} a _ {1 1} x _ {1} + \dots + a _ {1 n} x _ {n} = b _ {1} \\ \vdots \\ a _ {m 1} x _ {1} + \dots + a _ {m n} x _ {n} = b _ {m}, \end{array}\tag{2.37}
$$

where $a _ { i j } \in \mathbb { R }$ and $b _ { i } \in \mathbb { R }$ are known constants and $x _ { j }$ are unknowns, $i = 1 , \ldots , m , j = 1 , \ldots , n$ . Thus far, we saw that matrices can be used as a compact way of formulating systems of linear equations so that we can write $\mathbf { { A } } \mathbf { { x } } = \mathbf { { b } } ,$ see (2.10). Moreover, we defined basic matrix operations, such as addition and multiplication of matrices. In the following, we will focus on solving systems of linear equations and provide an algorithm for finding the inverse of a matrix. 

### 2.3.1 Particular and General Solution

Before discussing how to generally solve systems of linear equations, let us have a look at an example. Consider the system of equations 

$$
\left[ \begin{array}{c c c c} 1 & 0 & 8 & - 4 \\ 0 & 1 & 2 & 12 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \\ x _ {3} \\ x _ {4} \end{array} \right] = \left[ \begin{array}{c} 42 \\ 8 \end{array} \right].\tag{2.38}
$$

The system has two equations and four unknowns. Therefore, in general we would expect infinitely many solutions. This system of equations is in a particularly easy form, where the first two columns consist of a 1 and a 0. Remember that we want to find scalars $x _ { 1 } , \ldots , x _ { 4 }$ , such that $\textstyle \sum _ { i = 1 } ^ { 4 } x _ { i } c _ { i } = b ,$ where we define $c _ { i }$ to be the ith column of the matrix and b the right-hand-side of (2.38). A solution to the problem in (2.38) can be found immediately by taking 42 times the first column and 8 times the second column so that 

$$
\boldsymbol {b} = \left[ \begin{array}{c} 42 \\ 8 \end{array} \right] = 42 \left[ \begin{array}{c} 1 \\ 0 \end{array} \right] + 8 \left[ \begin{array}{c} 0 \\ 1 \end{array} \right].\tag{2.39}
$$

Therefore, a solution is $[ 42 , 8 , 0 , 0 ] ^ { \top }$ . This solution is called a particular solution or special solution. However, this is not the only solution of this system of linear equations. To capture all the other solutions, we need to be creative in generating 0 in a non-trivial way using the columns of the matrix: Adding 0 to our special solution does not change the special solution. To do so, we express the third column using the first two columns (which are of this very simple form) 

$$
\left[ \begin{array}{c} 8 \\ 2 \end{array} \right] = 8 \left[ \begin{array}{c} 1 \\ 0 \end{array} \right] + 2 \left[ \begin{array}{c} 0 \\ 1 \end{array} \right]\tag{2.40}
$$

so that ${ \bf 0 } = 8 { { c } _ { 1 } } + 2 { { c } _ { 2 } } - 1 { { c } _ { 3 } } + 0 { { c } _ { 4 } }$ and $( x _ { 1 } , x _ { 2 } , x _ { 3 } , x _ { 4 } ) = ( 8 , 2 , - 1 , 0 )$ . In fact, any scaling of this solution by $\lambda _ { 1 } \in \mathbb { R }$ produces the 0 vector, i.e., 

$$
\left[ \begin{array}{c c c c} 1 & 0 & 8 & - 4 \\ 0 & 1 & 2 & 12 \end{array} \right] \left(\lambda_ {1} \left[ \begin{array}{c} 8 \\ 2 \\ - 1 \\ 0 \end{array} \right]\right) = \lambda_ {1} (8 \boldsymbol {c} _ {1} + 2 \boldsymbol {c} _ {2} - \boldsymbol {c} _ {3}) = \boldsymbol {0}.\tag{2.41}
$$

Following the same line of reasoning, we express the fourth column of the matrix in (2.38) using the first two columns and generate another set of non-trivial versions of 0 as 

$$
\left[ \begin{array}{c c c c} 1 & 0 & 8 & - 4 \\ 0 & 1 & 2 & 12 \end{array} \right] \left(\lambda_ {2} \left[ \begin{array}{c} - 4 \\ 12 \\ 0 \\ - 1 \end{array} \right]\right) = \lambda_ {2} (- 4 \boldsymbol {c} _ {1} + 12 \boldsymbol {c} _ {2} - \boldsymbol {c} _ {4}) = \mathbf {0}\tag{2.42}
$$

for any $\lambda _ { 2 } \in \mathbb { R }$ . Putting everything together, we obtain all solutions of the equation system in (2.38), which is called the general solution, as the set 

$$
\left\{\boldsymbol {x} \in \mathbb {R} ^ {4}: \boldsymbol {x} = \left[ \begin{array}{c} 42 \\ 8 \\ 0 \\ 0 \end{array} \right] + \lambda_ {1} \left[ \begin{array}{c} 8 \\ 2 \\ - 1 \\ 0 \end{array} \right] + \lambda_ {2} \left[ \begin{array}{c} - 4 \\ 12 \\ 0 \\ - 1 \end{array} \right], \lambda_ {1}, \lambda_ {2} \in \mathbb {R} \right\}.\tag{2.43}
$$

**Remark.** The general approach we followed consisted of the following three steps: 

1. Find a particular solution to $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{b}$. 

2. Find all solutions to $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{0}$. 

3. Combine the solutions from steps 1. and 2. to the general solution. 

Neither the general nor the particular solution is unique. 

The system of linear equations in the preceding example was easy to solve because the matrix in (2.38) has this particularly convenient form, which allowed us to find the particular and the general solution by inspection. However, general equation systems are not of this simple form. Fortunately, there exists a constructive algorithmic way of transforming any system of linear equations into this particularly simple form: Gaussian elimination. Key to Gaussian elimination are elementary transformations of systems of linear equations, which transform the equation system into a simple form. Then, we can apply the three steps to the simple form that we just discussed in the context of the example in (2.38). 

### 2.3.2 Elementary Transformations

Key to solving a system of linear equations are elementary transformations that keep the solution set the same, but that transform the equation system into a simpler form: 

- Exchange of two equations (rows in the matrix representing the system of equations) 

- Multiplication of an equation (row) with a constant $\lambda \in \mathbb { R } \backslash \{ 0 \}$ 

- Addition of two equations (rows) 

**Example 2.6**

For $a\in\mathbb{R}$, we seek all solutions of the following system of equations: 

$$
\begin{array}{rcrcrcrcrcl}- 2 x _ {1} & + & 4 x _ {2} & - & 2 x _ {3} & - & x _ {4} & + & 4 x _ {5} & = & - 3 \\ 4 x _ {1} & - & 8 x _ {2} & + & 3 x _ {3} & - & 3 x _ {4} & + & x _ {5} & = & 2 \\ x _ {1} & - & 2 x _ {2} & + & x _ {3} & - & x _ {4} & + & x _ {5} & = & 0 \\ x _ {1} & - & 2 x _ {2} & & & - & 3 x _ {4} & + & 4 x _ {5} & = & a \\ \end{array} .\tag{2.44}
$$

We start by converting this system of equations into the compact matrix notation $A x = b .$ We no longer mention the variables x explicitly and build the augmented matrix (in the form $[\boldsymbol{A}\mid\boldsymbol{b}]$) 

$$
\left[\begin{array}{rrrrr|r}
-2&4&-2&-1&4&-3\\
4&-8&3&-3&1&2\\
1&-2&1&-1&1&0\\
1&-2&0&-3&4&a
\end{array}\right]
\qquad R_1\leftrightarrow R_3
$$

where we used the vertical line to separate the left-hand side from the right-hand side in (2.44). We use $\rightsquigarrow$ to indicate a transformation of the augmented matrix using elementary transformations.

> The augmented matrix $[\boldsymbol{A}\mid\boldsymbol{b}]$ compactly represents the system of linear equations $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{b}$.

Swapping Rows 1 and 3 leads to

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

When we now apply the indicated transformations (e.g., subtract Row 1 four times from Row 2), we obtain

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

This (augmented) matrix is in a convenient form, the row-echelon form (REF). Reverting this compact notation back into the explicit notation with the variables we seek, we obtain 

$$
\begin{array}{rcrcrcrcrcl} x _ {1} & - & 2 x _ {2} & + & x _ {3} & - & x _ {4} & + & x _ {5} & = & 0 \\ & & & & x _ {3} & - & x _ {4} & + & 3 x _ {5} & = & - 2 \\ & & & & & & x _ {4} & - & 2 x _ {5} & = & 1 \\ & & & & & & & & 0 & = & a + 1 \end{array}\tag{2.45}
$$

Only for $a = - 1$ this system can be solved. A particular solution is 

$$
{\left[ \begin{array}{l} x _ {1} \\ x _ {2} \\ x _ {3} \\ x _ {4} \\ x _ {5} \end{array} \right]} = {\left[ \begin{array}{l} 2 \\ 0 \\ - 1 \\ 1 \\ 0 \end{array} \right]}\tag{2.46}
$$

The general solution, which captures the set of all possible solutions, is 

$$
\left\{\boldsymbol {x} \in \mathbb {R} ^ {5}: \boldsymbol {x} = \left[ \begin{array}{c} 2 \\ 0 \\ - 1 \\ 1 \\ 0 \end{array} \right] + \lambda_ {1} \left[ \begin{array}{c} 2 \\ 1 \\ 0 \\ 0 \\ 0 \end{array} \right] + \lambda_ {2} \left[ \begin{array}{c} 2 \\ 0 \\ - 1 \\ 2 \\ 1 \end{array} \right], \quad \lambda_ {1}, \lambda_ {2} \in \mathbb {R} \right\}.\tag{2.47}
$$

In the following, we will detail a constructive way to obtain a particular and general solution of a system of linear equations. 

**Remark (Pivots and Staircase Structure).** The leading coefficient of a row (first nonzero number from the left) is called the pivot and is always strictly to the right of the pivot of the row above it. Therefore, any equation system in row-echelon form always has a “staircase” structure. 

**Definition 2.6 (Row-Echelon Form).** A matrix is in row-echelon form if 

- All rows that contain only zeros are at the bottom of the matrix; correspondingly, all rows that contain at least one nonzero element are on top of rows that contain only zeros. 

- Looking at nonzero rows only, the first nonzero number from the left (also called the pivot or the leading coefficient) is always strictly to the right of the pivot of the row above it. 

> In other texts, it is sometimes required that the pivot is 1.

**Remark (Basic and Free Variables).** The variables corresponding to the pivots in the row-echelon form are called basic variables and the other variables are free variables. For example, in (2.45), $x _ { 1 } , x _ { 3 } , x _ { 4 }$ are basic variables, whereas $x _ { 2 } , x _ { 5 }$ are free variables. ◇ 

**Remark (Obtaining a Particular Solution).** The row-echelon form makes our lives easier when we need to determine a particular solution. To do this, we express the right-hand side of the equation system using the pivot columns, such that $\boldsymbol{b}=\sum_{i=1}^{P}\lambda_i\boldsymbol{p}_i$ , where $p _ { i } , i = 1 , \ldots , P$ , are the pivot columns. The $\lambda _ { i }$ are determined easiest if we start with the rightmost pivot column and work our way to the left. 

In the previous example, we would try to find $\lambda _ { 1 } , \lambda _ { 2 } , \lambda _ { 3 }$ so that 

$$
\lambda_ {1} \left[ \begin{array}{c} 1 \\ 0 \\ 0 \\ 0 \end{array} \right] + \lambda_ {2} \left[ \begin{array}{c} 1 \\ 1 \\ 0 \\ 0 \end{array} \right] + \lambda_ {3} \left[ \begin{array}{c} - 1 \\ - 1 \\ 1 \\ 0 \end{array} \right] = \left[ \begin{array}{c} 0 \\ - 2 \\ 1 \\ 0 \end{array} \right].\tag{2.48}
$$

From here, we find relatively directly that $\lambda _ { 3 } = 1 , \lambda _ { 2 } = - 1 , \lambda _ { 1 } = 2$ . When we put everything together, we must not forget the non-pivot columns for which we set the coefficients implicitly to 0. Therefore, we get the particular solution $\boldsymbol{x}=[2,0,-1,1,0]^{\top}$. 

**Remark (Reduced Row Echelon Form).** An equation system is in reduced row-echelon form (also: row-reduced echelon form or row canonical form) if 

- It is in row-echelon form. 

- Every pivot is 1. 

- The pivot is the only nonzero entry in its column. 

The reduced row-echelon form will play an important role later in Section 2.3.3 because it allows us to determine the general solution of a system of linear equations in a straightforward way. 

**Remark (Gaussian Elimination).** Gaussian elimination is an algorithm that performs elementary transformations to bring a system of linear equations into reduced row-echelon form. 

**Example 2.7 (Reduced Row Echelon Form)**

Verify that the following matrix is in reduced row-echelon form (the pivots are in bold): 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c c} \mathbf {1} & 3 & 0 & 0 & 3 \\ 0 & 0 & \mathbf {1} & 0 & 9 \\ 0 & 0 & 0 & \mathbf {1} & - 4 \end{array} \right].\tag{2.49}
$$

The key idea for finding the solutions of $\pmb { A } \pmb { x } = \pmb { 0 }$ is to look at the nonpivot columns, which we will need to express as a (linear) combination of the pivot columns. The reduced row echelon form makes this relatively straightforward, and we express the non-pivot columns in terms of sums and multiples of the pivot columns that are on their left: The second column is 3 times the first column (we can ignore the pivot columns on the right of the second column). Therefore, to obtain 0, we need to subtract the second column from three times the first column. Now, we look at the fifth column, which is our second non-pivot column. The fifth column can be expressed as 3 times the first pivot column, 9 times the second pivot column, and $-4$ times the third pivot column. We need to keep track of the indices of the pivot columns and translate this into 3 times the first column, 0 times the second column (which is a non-pivot column), 9 times the third column (which is our second pivot column), and $-4$ times the fourth column (which is the third pivot column). Then we need to subtract the fifth column to obtain 0. In the end, we are still solving a homogeneous equation system. 

To summarize, all solutions of $\pmb { A } \pmb { x } = \mathbf { 0 } , \pmb { x } \in \mathbb { R } ^ { 5 }$ are given by 

$$
\left\{\boldsymbol {x} \in \mathbb {R} ^ {5}: \boldsymbol {x} = \lambda_ {1} \left[ \begin{array}{c} 3 \\ - 1 \\ 0 \\ 0 \\ 0 \end{array} \right] + \lambda_ {2} \left[ \begin{array}{c} 3 \\ 0 \\ 9 \\ - 4 \\ - 1 \end{array} \right], \quad \lambda_ {1}, \lambda_ {2} \in \mathbb {R} \right\}.\tag{2.50}
$$

### 2.3.3 The Minus-1 Trick

In the following, we introduce a practical trick for reading out the solutions $\boldsymbol{x}$ of a homogeneous system of linear equations $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{0}$, where $\boldsymbol{A}\in\mathbb{R}^{k\times n}$, $\boldsymbol{x}\in\mathbb{R}^{n}$. 

To start, we assume that A is in reduced row-echelon form without any rows that just contain zeros, i.e., 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c c c c c c c c c c c c} 0 & \dots & 0 & \mathbf {1} & * & \dots & * & 0 & * & \dots & * & 0 & * & \dots & * \\ \vdots & & \vdots & 0 & 0 & \dots & 0 & \mathbf {1} & * & \dots & * & \vdots & \vdots & & \vdots \\ \vdots & & \vdots & \vdots & \vdots & & \vdots & 0 & \vdots & & \vdots & \vdots & \vdots & & \vdots \\ \vdots & & \vdots & \vdots & \vdots & & \vdots & \vdots & \vdots & & \vdots & 0 & \vdots & & \vdots \\ 0 & \dots & 0 & 0 & 0 & \dots & 0 & 0 & 0 & \dots & 0 & \mathbf {1} & * & \dots & * \end{array} \right],\tag{2.51}
$$

where $*$ can be an arbitrary real number, with the constraints that the first nonzero entry per row must be 1 and all other entries in the corresponding column must be 0. The columns $j _ { 1 } , \dots , j _ { k }$ with the pivots (marked in bold) are the standard unit vectors $e _ { 1 } , \ldots , e _ { k } \in \mathbb { R } ^ { k }$ . We extend this matrix to an $n \times n$ -matrix $\tilde{\boldsymbol{A}}$ by adding $n - k$ rows of the form 

$$
\left[ \begin{array}{c c c c c c c} 0 & \dots & 0 & - 1 & 0 & \dots & 0 \end{array} \right]\tag{2.52}
$$

so that the diagonal of the augmented matrix $\tilde { \boldsymbol { A } }$ contains either $1$ or $-1$. Then, the columns of $\tilde{\boldsymbol{A}}$ that contain the $-1$ as pivots are solutions of the homogeneous equation system $\mathbf { { \boldsymbol { A } } } \mathbf { { \boldsymbol { x } } } = \mathbf { { \boldsymbol { 0 } } }$ . To be more precise, these columns form a basis (Section 2.6.1) of the solution space of $\mathbf { { \boldsymbol { A } } } \mathbf { { \boldsymbol { x } } } = \mathbf { { \boldsymbol { 0 } } }$ which we will later call the kernel or null space (see Section 2.7.3). 

**Example 2.8 (Minus-1 Trick)**

Let us revisit the matrix in (2.49), which is already in reduced REF: 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c c} 1 & 3 & 0 & 0 & 3 \\ 0 & 0 & 1 & 0 & 9 \\ 0 & 0 & 0 & 1 & - 4 \end{array} \right].\tag{2.53}
$$

We now augment this matrix to a $5 \times 5$ matrix by adding rows of the form (2.52) at the places where the pivots on the diagonal are missing and obtain 

$$
\tilde {\boldsymbol {A}} = \left[ \begin{array}{c c c c c} 1 & 3 & 0 & 0 & 3 \\ 0 & - \mathbf {1} & 0 & 0 & 0 \\ 0 & 0 & 1 & 0 & 9 \\ 0 & 0 & 0 & 1 & - 4 \\ 0 & 0 & 0 & 0 & - \mathbf {1} \end{array} \right].\tag{2.54}
$$

From this form, we can immediately read out the solutions of $\mathbf { A } \mathbf { { x } } = \mathbf { 0 }$ by taking the columns of $\tilde{\boldsymbol{A}}$, which contain $-1$ on the diagonal: 

$$
\left\{\boldsymbol {x} \in \mathbb {R} ^ {5}: \boldsymbol {x} = \lambda_ {1} \left[ \begin{array}{c} 3 \\ - 1 \\ 0 \\ 0 \\ 0 \end{array} \right] + \lambda_ {2} \left[ \begin{array}{c} 3 \\ 0 \\ 9 \\ - 4 \\ - 1 \end{array} \right], \quad \lambda_ {1}, \lambda_ {2} \in \mathbb {R} \right\},\tag{2.55}
$$

which is identical to the solution in (2.50) that we obtained by “insight”. 

#### Calculating the Inverse

To compute the inverse $A ^ { - 1 }$ of $\pmb { A } \in \mathbb { R } ^ { n \times n }$ , we need to find a matrix X that satisfies $A X \ = \ I _ { n }$ . Then, $\pmb { X } = \pmb { A } ^ { - 1 }$ . We can write this down as a set of simultaneous linear equations $A X \ = \ I _ { n }$ , where we solve for $\pmb { X } = \left[ \pmb { x } _ { 1 } | \cdot \cdot \cdot | \pmb { x } _ { n } \right]$ . We use the augmented matrix notation for a compact representation of this set of systems of linear equations and obtain 

$$
\left[ \boldsymbol {A} | \boldsymbol {I} _ {n} \right] \quad \rightsquigarrow \dots \rightsquigarrow \quad \left[ \boldsymbol {I} _ {n} | \boldsymbol {A} ^ {- 1} \right].\tag{2.56}
$$

This means that if we bring the augmented equation system into reduced row-echelon form, we can read out the inverse on the right-hand side of the equation system. Hence, determining the inverse of a matrix is equivalent to solving systems of linear equations. 

**Example 2.9 (Calculating an Inverse Matrix by Gaussian Elimination)**

To determine the inverse of 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c} 1 & 0 & 2 & 0 \\ 1 & 1 & 0 & 0 \\ 1 & 2 & 0 & 1 \\ 1 & 1 & 1 & 1 \end{array} \right]\tag{2.57}
$$

we write down the augmented matrix 

$$
\left[ \begin{array}{rrrr|rrrr} 1 & 0 & 2 & 0 & 1 & 0 & 0 & 0 \\ 1 & 1 & 0 & 0 & 0 & 1 & 0 & 0 \\ 1 & 2 & 0 & 1 & 0 & 0 & 1 & 0 \\ 1 & 1 & 1 & 1 & 0 & 0 & 0 & 1 \end{array} \right]
$$

and use Gaussian elimination to bring it into reduced row-echelon form 

$$
\left[ \begin{array}{rrrr|rrrr} 1 & 0 & 0 & 0 & - 1 & 2 & - 2 & 2 \\ 0 & 1 & 0 & 0 & 1 & - 1 & 2 & - 2 \\ 0 & 0 & 1 & 0 & 1 & - 1 & 1 & - 1 \\ 0 & 0 & 0 & 1 & - 1 & 0 & - 1 & 2 \end{array} \right],
$$

such that the desired inverse is given as its right-hand side: 

$$
\boldsymbol {A} ^ {- 1} = \left[ \begin{array}{c c c c} - 1 & 2 & - 2 & 2 \\ 1 & - 1 & 2 & - 2 \\ 1 & - 1 & 1 & - 1 \\ - 1 & 0 & - 1 & 2 \end{array} \right].\tag{2.58}
$$

We can verify that (2.58) is indeed the inverse by performing the multiplication $\boldsymbol{A}\boldsymbol{A}^{-1}$ and observing that we recover $\boldsymbol{I}_4$. 

### 2.3.4 Algorithms for Solving a System of Linear Equations

In the following, we briefly discuss approaches to solving a system of linear equations of the form $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{b}$ . We make the assumption that a solution exists. Should there be no solution, we need to resort to approximate solutions, which we do not cover in this chapter. One way to solve the approximate problem is using the approach of linear regression, which we discuss in detail in Chapter 9. 

In special cases, we may be able to determine the inverse $A ^ { - 1 }$ , such that the solution of $A x \ = \ b$ is given as $x = A ^ { - 1 } b$ . However, this is only possible if A is a square matrix and invertible, which is often not the case. Otherwise, under mild assumptions (i.e., A needs to have linearly independent columns) we can use the transformation 

$$
\boldsymbol {A} \boldsymbol {x} = \boldsymbol {b} \iff \boldsymbol {A} ^ {\top} \boldsymbol {A} \boldsymbol {x} = \boldsymbol {A} ^ {\top} \boldsymbol {b} \iff \boldsymbol {x} = (\boldsymbol {A} ^ {\top} \boldsymbol {A}) ^ {- 1} \boldsymbol {A} ^ {\top} \boldsymbol {b}\tag{2.59}
$$

and use the Moore-Penrose pseudo-inverse $( A ^ { \top } A ) ^ { - 1 } A ^ { \top }$ to determine the solution (2.59) that solves $\mathbf { { A } } \mathbf { { x } } = \mathbf { { b } } ,$ which also corresponds to the minimum norm least-squares solution. A disadvantage of this approach is that it requires many computations for the matrix-matrix product and computing the inverse of $A ^ { \top } A$ . Moreover, for reasons of numerical precision it is generally not recommended to compute the inverse or pseudo-inverse. In the following, we therefore briefly discuss alternative approaches to solving systems of linear equations. 

Gaussian elimination plays an important role when computing determinants (Section 4.1), checking whether a set of vectors is linearly independent (Section 2.5), computing the inverse of a matrix (Section 2.2.2), computing the rank of a matrix (Section 2.6.2), and determining a basis of a vector space (Section 2.6.1). Gaussian elimination is an intuitive and constructive way to solve a system of linear equations with thousands of variables. However, for systems with millions of variables, it is impractical as the required number of arithmetic operations scales cubically in the number of simultaneous equations. 

In practice, systems of many linear equations are solved indirectly, by either stationary iterative methods, such as the Richardson method, the Jacobi method, the Gauß-Seidel method, and the successive over-relaxation method, or Krylov subspace methods, such as conjugate gradients, generalized minimal residual, or biconjugate gradients. We refer to the books by Stoer and Burlirsch (2002), Strang (2003), and Liesen and Mehrmann (2015) for further details. 

Let $\boldsymbol{x}_*$ be a solution of $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{b}$ . The key idea of these iterative methods is to set up an iteration of the form 

$$
\pmb {x} ^ {(k + 1)} = \pmb {C x} ^ {(k)} + \pmb {d}\tag{2.60}
$$

for suitable C and d that reduces the residual error $\| \pmb { x } ^ { ( k + 1 ) } - \pmb { x } _ { * } \|$ in every iteration and converges to ${ \pmb x } _ { \ast }$ . We will introduce norms $\|\cdot\|$, which allow us to compute similarities between vectors, in Section 3.1. 

## 2.4 Vector Spaces

Thus far, we have looked at systems of linear equations and how to solve them (Section 2.3). We saw that systems of linear equations can be compactly represented using matrix-vector notation (2.10). In the following, we will have a closer look at vector spaces, i.e., a structured space in which vectors live. 

In the beginning of this chapter, we informally characterized vectors as objects that can be added together and multiplied by a scalar, and they remain objects of the same type. Now, we are ready to formalize this, and we will start by introducing the concept of a group, which is a set of elements and an operation defined on these elements that keeps some structure of the set intact. 

### 2.4.1 Groups

Groups play an important role in computer science. Besides providing a fundamental framework for operations on sets, they are heavily used in cryptography, coding theory, and graphics. 

**Definition 2.7 (Group).** Consider a set $\mathcal { G }$ and an operation $\otimes : { \mathcal { G } } \times { \mathcal { G } } \to { \mathcal { G } }$ defined on $\mathcal { G }$ . Then $G : = ( \mathcal { G } , \otimes )$ is called a group if the following hold: 

1. Closure of $\mathcal{G}$ under $\otimes$: $\forall x,y\in\mathcal{G}:x\otimes y\in\mathcal{G}$.
2. Associativity: $\forall x,y,z\in\mathcal{G}:(x\otimes y)\otimes z=x\otimes(y\otimes z)$.
3. Neutral element: $\exists e\in\mathcal{G}\ \forall x\in\mathcal{G}:x\otimes e=x$ and $e\otimes x=x$.
4. Inverse element: $\forall x\in\mathcal{G}\ \exists y\in\mathcal{G}:x\otimes y=e$ and $y\otimes x=e$, where $e$ is the neutral element. We often write $x^{-1}$ to denote the inverse element of $x$.

Remark. The inverse element is defined with respect to the operation $\otimes$ and does not necessarily mean $\textstyle { \frac { 1 } { x } }$ $\diamondsuit$ 

If additionally $\forall x,y\in\mathcal{G}:x\otimes y=y\otimes x$, then $G = ( \mathcal { G } , \otimes )$ is an Abelian group (commutative). 

**Example 2.10 (Groups)**

Let us have a look at some examples of sets with associated operations and see whether they are groups: 

- $( \mathbb { Z } , + )$ is an Abelian group. 

> $\mathbb{N}_0:=\mathbb{N}\cup\{0\}$. 

- $( \mathbb { N } _ { 0 } , + )$ is not a group: Although $( \mathbb { N } _ { 0 } , + )$ possesses a neutral element (0), the inverse elements are missing. 

- $( \mathbb { Z } , \cdot )$ is not a group: Although $( \mathbb { Z } , \cdot )$ contains a neutral element (1), the inverse elements for any $z \in \mathbb { Z } , z \neq \pm 1$ , are missing. 

- $(\mathbb{R},\cdot)$ is not a group since 0 does not possess an inverse element. 

- $( \mathbb { R } \backslash \{ 0 \} , \cdot )$ is Abelian. 

- $( \mathbb { R } ^ { n } , + ) , ( \mathbb { Z } ^ { n } , + ) , n \in \mathbb { N }$ are Abelian if + is defined componentwise, i.e., 

$$
\left(x _ {1}, \dots , x _ {n}\right) + \left(y _ {1}, \dots , y _ {n}\right) = \left(x _ {1} + y _ {1}, \dots , x _ {n} + y _ {n}\right).\tag{2.61}
$$

Then, $( x _ { 1 } , \cdot \cdot \cdot , x _ { n } ) ^ { - 1 } : = ( - x _ { 1 } , \cdot \cdot \cdot , - x _ { n } )$ is the inverse element and $e = ( 0 , \cdots , 0 )$ is the neutral element. 

- $\left( \mathbb { R } ^ { m \times n } , + \right)$ , the set of $m\times n$-matrices is Abelian (with componentwise addition as defined in (2.61)). 

- Let us have a closer look at $( \mathbb { R } ^ { n \times n } , \cdot )$ , i.e., the set of $n\times n$-matrices with matrix multiplication as defined in (2.13). 

  - Closure and associativity follow directly from the definition of matrix multiplication. 

  - Neutral element: The identity matrix ${ \cal { I } } _ { n }$ is the neutral element with respect to matrix multiplication “$\cdot$” in $( \mathbb { R } ^ { n \times n } , \cdot )$ 

  - Inverse element: If the inverse exists (A is regular), then $A ^ { - 1 }$ is the inverse element of $A \in \mathbb { R } ^ { n \times n }$ and in exactly this case $( \mathbb { R } ^ { n \times n } , \cdot )$ is a group, called the general linear group. 

**Definition 2.8 (General Linear Group).** The set of regular (invertible) matrices $\pmb { A } \in \mathbb { R } ^ { n \times n }$ is a group with respect to matrix multiplication as defined in (2.13) and is called general linear group $G L ( n , \mathbb { R } )$ . However, since matrix multiplication is not commutative, the group is not Abelian. 

### 2.4.2 Vector Spaces

When we discussed groups, we looked at sets $\mathcal { G }$ and inner operations on $\mathcal{G}$, i.e., mappings ${ \mathcal { G } } \times { \mathcal { G } } \to { \mathcal { G } }$ that only operate on elements in $\mathcal{G}$. In the following, we will consider sets that in addition to an inner operation $+$ also contain an outer operation $\cdot$, the multiplication of a vector $\boldsymbol { x } \in \mathcal G$ by a scalar $\lambda \in \mathbb { R }$ . We can think of the inner operation as a form of addition, and the outer operation as a form of scaling. Note that the inner/outer operations have nothing to do with inner/outer products. 

**Definition 2.9 (Vector Space).** A real-valued vector space $V=(\mathcal{V},+,\cdot)$ is a set $\mathcal{V}$ with two operations 

$$
+: \mathcal {V} \times \mathcal {V} \rightarrow \mathcal {V}\tag{2.62}
$$

$$
\cdot : \mathbb {R} \times \mathcal {V} \to \mathcal {V}\tag{2.63}
$$

where

1. $(\mathcal{V},+)$ is an Abelian group.
2. Distributivity:
   1. $\forall\lambda\in\mathbb{R},\boldsymbol{x},\boldsymbol{y}\in\mathcal{V}:\lambda\cdot(\boldsymbol{x}+\boldsymbol{y})=\lambda\cdot\boldsymbol{x}+\lambda\cdot\boldsymbol{y}$.
   2. $\forall\lambda,\psi\in\mathbb{R},\boldsymbol{x}\in\mathcal{V}:(\lambda+\psi)\cdot\boldsymbol{x}=\lambda\cdot\boldsymbol{x}+\psi\cdot\boldsymbol{x}$.
3. Associativity (outer operation): $\forall\lambda,\psi\in\mathbb{R},\boldsymbol{x}\in\mathcal{V}:\lambda\cdot(\psi\cdot\boldsymbol{x})=(\lambda\psi)\cdot\boldsymbol{x}$.
4. Neutral element with respect to the outer operation: $\forall\boldsymbol{x}\in\mathcal{V}:1\cdot\boldsymbol{x}=\boldsymbol{x}$.

The elements $\boldsymbol{x}\in\mathcal{V}$ are called vectors. The neutral element of $(\mathcal{V},+)$ is the zero vector $\boldsymbol{0}=[0,\ldots,0]^{\top}$, and the inner operation $+$ is called vector addition. The elements $\lambda\in\mathbb{R}$ are called scalars and the outer operation $\cdot$ is a multiplication by scalars. Note that a scalar product is something different, and we will get to this in Section 3.2.

**Remark.** A “vector multiplication” $\boldsymbol{a}\boldsymbol{b}$, $\boldsymbol{a},\boldsymbol{b}\in\mathbb{R}^{n}$, is not defined. Theoretically, we could define an element-wise multiplication, such that $\boldsymbol{c}=\boldsymbol{a}\boldsymbol{b}$ with $c_j=a_jb_j$. This “array multiplication” is common to many programming languages but makes mathematically limited sense using the standard rules for matrix multiplication: By treating vectors as $n\times1$ matrices (which we usually do), we can use the matrix multiplication as defined in (2.13). However, then the dimensions of the vectors do not match. Only the following multiplications for vectors are defined: $\boldsymbol{a}\boldsymbol{b}^{\top}\in\mathbb{R}^{n\times n}$ (outer product), $\boldsymbol{a}^{\top}\boldsymbol{b}\in\mathbb{R}$ (inner/scalar/dot product).

**Example 2.11 (Vector Spaces)**

Let us have a look at some important examples:

- $\mathcal{V}=\mathbb{R}^{n}$, $n\in\mathbb{N}$ is a vector space with operations defined as follows:
  - Addition: $\boldsymbol{x}+\boldsymbol{y}=(x_1,\ldots,x_n)+(y_1,\ldots,y_n)=(x_1+y_1,\ldots,x_n+y_n)$ for all $\boldsymbol{x},\boldsymbol{y}\in\mathbb{R}^{n}$.
  - Multiplication by scalars: $\lambda\boldsymbol{x}=\lambda(x_1,\ldots,x_n)=(\lambda x_1,\ldots,\lambda x_n)$ for all $\lambda\in\mathbb{R}$, $\boldsymbol{x}\in\mathbb{R}^{n}$.
- $\mathcal{V}=\mathbb{R}^{m\times n}$, $m,n\in\mathbb{N}$ is a vector space with
  - Addition: $\boldsymbol{A}+\boldsymbol{B}=\begin{bmatrix}a_{11}+b_{11}&\cdots&a_{1n}+b_{1n}\\\vdots&&\vdots\\a_{m1}+b_{m1}&\cdots&a_{mn}+b_{mn}\end{bmatrix}$ is defined elementwise for all $\boldsymbol{A},\boldsymbol{B}\in\mathcal{V}$.
  - Multiplication by scalars: $\lambda\boldsymbol{A}=\begin{bmatrix}\lambda a_{11}&\cdots&\lambda a_{1n}\\\vdots&&\vdots\\\lambda a_{m1}&\cdots&\lambda a_{mn}\end{bmatrix}$ as defined in Section 2.2. Remember that $\mathbb{R}^{m\times n}$ is equivalent to $\mathbb{R}^{mn}$.
- $\mathcal{V}=\mathbb{C}$, with the standard definition of addition of complex numbers.

**Remark.** In the following, we will denote a vector space $(\mathcal{V},+,\cdot)$ by $V$ when $+$ and $\cdot$ are the standard vector addition and scalar multiplication. Moreover, we will use the notation $\boldsymbol{x}\in V$ for vectors in $\mathcal{V}$ to simplify notation.

**Remark.** The vector spaces $\mathbb { R } ^ { n } , \mathbb { R } ^ { n \times 1 } , \mathbb { R } ^ { 1 \times n }$ are only different in the way we write vectors. In the following, we will not make a distinction between $\mathbb { R } ^ { n }$ and $\mathbb { R } ^ { n \times 1 }$ , which allows us to write n-tuples as column vectors 

$$
\boldsymbol {x} = \left[ \begin{array}{c} x _ {1} \\ \vdots \\ x _ {n} \end{array} \right].\tag{2.64}
$$

This simplifies the notation regarding vector space operations. However, we do distinguish between $\mathbb { R } ^ { n \times 1 }$ and $\mathbb { R } ^ { 1 \times n }$ (the row vectors) to avoid confusion with matrix multiplication. By default, we write $\boldsymbol{x}$ to denote a column vector, and a row vector is denoted by $\pmb { x } ^ { \top }$ , the transpose of $\boldsymbol{x}$. 

### 2.4.3 Vector Subspaces

In the following, we will introduce vector subspaces. Intuitively, they are sets contained in the original vector space with the property that when we perform vector space operations on elements within this subspace, we will never leave it. In this sense, they are “closed”. Vector subspaces are a key idea in machine learning. For example, Chapter 10 demonstrates how to use vector subspaces for dimensionality reduction. 

**Definition 2.10 (Vector Subspace).** Let $V=(\mathcal{V},+,\cdot)$ be a vector space and $\mathcal { U } \subseteq \mathcal { V } , \mathcal { U } \neq \emptyset$ . Then $U = ( \mathcal { U } , + , \cdot )$ is called vector subspace of $V$ (or linear subspace) if U is a vector space with the vector space operations $+$ and $\cdot$ restricted to $\mathcal{U}\times\mathcal{U}$ and $\mathbb { R } \times \mathcal { U }$ . We write $U \subseteq V$ to denote a subspace U of V. 

If $\mathcal { U } \subseteq \mathcal { V }$ and V is a vector space, then U naturally inherits many properties directly from V because they hold for all $\boldsymbol{x}\in\mathcal{V}$, and in particular for all $\pmb { x } \in \mathcal { U } \subseteq \mathcal { V }$ . This includes the Abelian group properties, the distributivity, the associativity and the neutral element. To determine whether $(\mathcal{U},+,\cdot)$ is a subspace of V we still do need to show 

1. $\mathcal { U } \neq \emptyset ,$ in particular: $\mathbf { 0 } \in \mathcal { U }$ 

2. Closure of $U$: 

   - With respect to the outer operation: $\forall \lambda \in \mathbb { R } \forall x \in \mathcal { U } : \lambda \pmb { x } \in \mathcal { U } .$ 

   - With respect to the inner operation: $\forall x , y \in \mathcal { U } : x + y \in \mathcal { U } .$ 

**Example 2.12 (Vector Subspaces)**

Let us have a look at some examples: 

- For every vector space $V$, the trivial subspaces are $V$ itself and $\{\boldsymbol{0}\}$. 

- Only example D in Figure 2.6 is a subspace of $\mathbb { R } ^ { 2 }$ (with the usual inner/ outer operations). In A and C, the closure property is violated; B does not contain 0. 

- The solution set of a homogeneous system of linear equations $\mathbf { A } \mathbf { { x } } = \mathbf { 0 }$ with n unknowns $\pmb { x } = [ x _ { 1 } , \ldots , x _ { n } ] ^ { \top }$ is a subspace of $\mathbb { R } ^ { n }$ 

- The solution of an inhomogeneous system of linear equations $\boldsymbol{A}\boldsymbol{x}=\boldsymbol{b}$, $\boldsymbol{b}\neq\boldsymbol{0}$ is not a subspace of $\mathbb{R}^{n}$. 

- The intersection of arbitrarily many subspaces is a subspace itself. 

![image](<Images/02_Linear_Algebra_image_008.jpg>)

Figure 2.6 Not all subsets of $\mathbb{R}^{2}$ are subspaces. In A and C, the closure property is violated; B does not contain 0. Only D is a subspace.

**Remark.** Every subspace $U \subseteq ( \mathbb { R } ^ { n } , + , \cdot )$ is the solution space of a homogeneous system of linear equations $\pmb { A } \pmb { x } = \mathbf { 0 }$ for $\pmb { x } \in \mathbb { R } ^ { n }$ ◇ 

## 2.5 Linear Independence

In the following, we will have a close look at what we can do with vectors (elements of the vector space). In particular, we can add vectors together and multiply them with scalars. The closure property guarantees that we end up with another vector in the same vector space. It is possible to find a set of vectors with which we can represent every vector in the vector space by adding them together and scaling them. This set of vectors is a basis, and we will discuss them in Section 2.6.1. Before we get there, we will need to introduce the concepts of linear combinations and linear independence. 

**Definition 2.11 (Linear Combination).** Consider a vector space V and a finite number of vectors $\pmb { x } _ { 1 } , \dotsc , \pmb { x } _ { k } \in V$ . Then, every $\boldsymbol{v}\in V$ of the form 

$$
\boldsymbol {v} = \lambda_ {1} \boldsymbol {x} _ {1} + \dots + \lambda_ {k} \boldsymbol {x} _ {k} = \sum_ {i = 1} ^ {k} \lambda_ {i} \boldsymbol {x} _ {i} \in V\tag{2.65}
$$

with $\lambda _ { 1 } , \ldots , \lambda _ { k } \in \mathbb { R }$ is a linear combination of the vectors $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ 

The 0-vector can always be written as the linear combination of k vectors $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ because $\boldsymbol{0}=\sum_{i=1}^{k}0\boldsymbol{x}_i$ is always true. In the following, we are interested in non-trivial linear combinations of a set of vectors to represent 0, i.e., linear combinations of vectors $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ , where not all coefficients $\lambda_i$ in (2.65) are 0. 

**Definition 2.12 (Linear (In)dependence).** Let us consider a vector space V with $k \in \mathbb { N }$ and $\pmb { x } _ { 1 } , \dotsc , \pmb { x } _ { k } \in V$ . If there is a non-trivial linear combination, such that $\boldsymbol{0}=\sum_{i=1}^{k}\lambda_i\boldsymbol{x}_i$ with at least one $\lambda _ { i } \neq 0$ , the vectors $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ are linearly dependent. If only the trivial solution exists, i.e., $\lambda_1=\cdots=\lambda_k=0$, the vectors $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ are linearly independent. 

Linear independence is one of the most important concepts in linear algebra. Intuitively, a set of linearly independent vectors consists of vectors that have no redundancy, i.e., if we remove any of those vectors from the set, we will lose something. Throughout the next sections, we will formalize this intuition more. 

**Example 2.13 (Linearly Dependent Vectors)**

A geographic example may help to clarify the concept of linear independence. A person in Nairobi (Kenya) describing where Kigali (Rwanda) is might say ,“You can get to Kigali by first going 506 km Northwest to Kampala (Uganda) and then 374 km Southwest.”. This is sufficient information to describe the location of Kigali because the geographic coordinate system may be considered a two-dimensional vector space (ignoring altitude and the Earth’s curved surface). The person may add, “It is about 751 km West of here.” Although this last statement is true, it is not necessary to find Kigali given the previous information (see Figure 2.7 for an illustration). In this example, the “506 km Northwest” vector (blue) and the “374 km Southwest” vector (purple) are linearly independent. This means the Southwest vector cannot be described in terms of the Northwest vector, and vice versa. However, the third “751 km West” vector (black) is a linear combination of the other two vectors, and it makes the set of vectors linearly dependent. Equivalently, given “751 km West” and “374 km Southwest” can be linearly combined to obtain “506 km Northwest”. 

![image](<Images/02_Linear_Algebra_image_009.jpg>)

Figure 2.7 Geographic example (with crude approximations to cardinal directions) of linearly dependent vectors in a two-dimensional space (plane).

**Remark.** The following properties are useful to find out whether vectors are linearly independent: 

- k vectors are either linearly dependent or linearly independent. There is no third option. 

- If at least one of the vectors $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ is $\boldsymbol{0}$ then they are linearly dependent. The same holds if two vectors are identical. 

- The vectors $\{ \pmb { x } _ { 1 } , \dots , \pmb { x } _ { k } : \pmb { x } _ { i } \neq \pmb { 0 } , i = 1 , \dots , k \} , k\geqslant2$, are linearly dependent if and only if (at least) one of them is a linear combination of the others. In particular, if one vector is a multiple of another vector, i.e., $\pmb { x } _ { i } = \lambda \pmb { x } _ { j } , \lambda \in \mathbb { R }$ then the set $\{ \pmb { x } _ { 1 } , \dots , \pmb { x } _ { k } : \pmb { x } _ { i } \neq \mathbf { 0 } , i = 1 , \dots , k \}$ is linearly dependent. 

- A practical way of checking whether vectors $\pmb { x } _ { 1 } , \dotsc , \pmb { x } _ { k } \in V$ are linearly independent is to use Gaussian elimination: Write all vectors as columns of a matrix A and perform Gaussian elimination until the matrix is in row echelon form (the reduced row-echelon form is unnecessary here): 

  - The pivot columns indicate the vectors, which are linearly independent of the vectors on the left. Note that there is an ordering of vectors when the matrix is built. 

  - The non-pivot columns can be expressed as linear combinations of the pivot columns on their left. For instance, the row-echelon form 

    $$
    \left[ \begin{array}{c c c} 1 & 3 & 0 \\ 0 & 0 & 2 \end{array} \right]\tag{2.66}
    $$

    tells us that the first and third columns are pivot columns. The second column is a non-pivot column because it is three times the first column. 

  All column vectors are linearly independent if and only if all columns are pivot columns. If there is at least one non-pivot column, the columns (and, therefore, the corresponding vectors) are linearly dependent. 

**Example 2.14**

Consider $\mathbb { R } ^ { 4 }$ with 

$$
\boldsymbol {x} _ {1} = \left[ \begin{array}{c} 1 \\ 2 \\ - 3 \\ 4 \end{array} \right], \quad \boldsymbol {x} _ {2} = \left[ \begin{array}{c} 1 \\ 1 \\ 0 \\ 2 \end{array} \right], \quad \boldsymbol {x} _ {3} = \left[ \begin{array}{c} - 1 \\ - 2 \\ 1 \\ 1 \end{array} \right].\tag{2.67}
$$

To check whether they are linearly dependent, we follow the general approach and solve 

$$
\lambda_ {1} \boldsymbol {x} _ {1} + \lambda_ {2} \boldsymbol {x} _ {2} + \lambda_ {3} \boldsymbol {x} _ {3} = \lambda_ {1} \left[ \begin{array}{c} 1 \\ 2 \\ - 3 \\ 4 \end{array} \right] + \lambda_ {2} \left[ \begin{array}{c} 1 \\ 1 \\ 0 \\ 2 \end{array} \right] + \lambda_ {3} \left[ \begin{array}{c} - 1 \\ - 2 \\ 1 \\ 1 \end{array} \right] = \mathbf {0}\tag{2.68}
$$

for $\lambda _ { 1 } , \ldots , \lambda _ { 3 }$ . We write the vectors $\boldsymbol{x}_i$, $i=1,2,3$, as the columns of a matrix and apply elementary row operations until we identify the pivot columns: 

$$
\left[\begin{array}{c c c}1&1&- 1\\2&1&- 2\\- 3&0&1\\4&2&1\end{array}\right] \quad \rightsquigarrow \dots \rightsquigarrow \quad \left[\begin{array}{c c c}1&1&- 1\\0&1&0\\0&0&1\\0&0&0\end{array}\right].\tag{2.69}
$$

Here, every column of the matrix is a pivot column. Therefore, there is no non-trivial solution, and we require $\lambda _ { 1 } = 0 , \lambda _ { 2 } = 0 , \lambda _ { 3 } = 0$ to solve the equation system. Hence, the vectors ${ \pmb x } _ { 1 } , { \pmb x } _ { 2 } , { \pmb x } _ { 3 }$ are linearly independent. 

**Remark.** Consider a vector space V with k linearly independent vectors $\boldsymbol { b } _ { 1 } , \ldots , \boldsymbol { b } _ { k }$ and m linear combinations 

$$
\begin{aligned}
\boldsymbol{x}_1&=\sum_{i=1}^{k}\lambda_{i1}\boldsymbol{b}_i,\\
&\vdots\\
\boldsymbol{x}_m&=\sum_{i=1}^{k}\lambda_{im}\boldsymbol{b}_i.
\end{aligned}
\tag{2.70}
$$

Defining $\boldsymbol{B}=[\boldsymbol{b}_1,\ldots,\boldsymbol{b}_k]$ as the matrix whose columns are the linearly independent vectors $b _ { 1 } , \ldots , b _ { k }$ , we can write 

$$
\boldsymbol {x} _ {j} = \boldsymbol {B} \boldsymbol {\lambda} _ {j}, \quad \boldsymbol {\lambda} _ {j} = \left[ \begin{array}{c} \lambda_ {1 j} \\ \vdots \\ \lambda_ {k j} \end{array} \right], \quad j = 1, \ldots , m,\tag{2.71}
$$

in a more compact form. 

We want to test whether $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { m }$ are linearly independent. For this purpose, we follow the general approach of testing when $\sum_{j=1}^{m}\psi_j\boldsymbol{x}_j=\boldsymbol{0}$. With (2.71), we obtain 

$$
\sum_ {j = 1} ^ {m} \psi_ {j} \boldsymbol {x} _ {j} = \sum_ {j = 1} ^ {m} \psi_ {j} \boldsymbol {B} \boldsymbol {\lambda} _ {j} = \boldsymbol {B} \sum_ {j = 1} ^ {m} \psi_ {j} \boldsymbol {\lambda} _ {j}.\tag{2.72}
$$

This means that $\{ \pmb { x } _ { 1 } , \ldots , \pmb { x } _ { m } \}$ are linearly independent if and only if the column vectors $\{\boldsymbol{\lambda}_1,\ldots,\boldsymbol{\lambda}_m\}$ are linearly independent. 

**Remark.** In a vector space $V$, m linear combinations of k vectors $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { k }$ are linearly dependent if $m>k$. 

**Example 2.15**

Consider a set of linearly independent vectors $b _ { 1 } , b _ { 2 } , b _ { 3 } , b _ { 4 } \in \mathbb { R } ^ { n }$ and 

$$
\begin{array}{r c l r c l r c l} \boldsymbol {x} _ {1} & = & \boldsymbol {b} _ {1} & - & 2 \boldsymbol {b} _ {2} & + & \boldsymbol {b} _ {3} & - & \boldsymbol {b} _ {4} \\ \boldsymbol {x} _ {2} & = & - 4 \boldsymbol {b} _ {1} & - & 2 \boldsymbol {b} _ {2} & & & + & 4 \boldsymbol {b} _ {4} \\ \boldsymbol {x} _ {3} & = & 2 \boldsymbol {b} _ {1} & + & 3 \boldsymbol {b} _ {2} & - & \boldsymbol {b} _ {3} & - & 3 \boldsymbol {b} _ {4} \\ \boldsymbol {x} _ {4} & = & 17 \boldsymbol {b} _ {1} & - & 10 \boldsymbol {b} _ {2} & + & 11 \boldsymbol {b} _ {3} & + & \boldsymbol {b} _ {4} \end{array} .\tag{2.73}
$$

Are the vectors $\pmb { x } _ { 1 } , \dotsc , \pmb { x } _ { 4 } \in \mathbb { R } ^ { n }$ linearly independent? To answer this question, we investigate whether the column vectors 

$$
\left\{\left[ \begin{array}{c} 1 \\ - 2 \\ 1 \\ - 1 \end{array} \right], \left[ \begin{array}{c} - 4 \\ - 2 \\ 0 \\ 4 \end{array} \right], \left[ \begin{array}{c} 2 \\ 3 \\ - 1 \\ - 3 \end{array} \right], \left[ \begin{array}{c} 17 \\ - 10 \\ 11 \\ 1 \end{array} \right] \right\}\tag{2.74}
$$

are linearly independent. The reduced row-echelon form of the corresponding linear equation system with coefficient matrix 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c} 1 & - 4 & 2 & 17 \\ - 2 & - 2 & 3 & - 10 \\ 1 & 0 & - 1 & 11 \\ - 1 & 4 & - 3 & 1 \end{array} \right]\tag{2.75}
$$

is given as 

$$
\left[ \begin{array}{c c c c} 1 & 0 & 0 & - 7 \\ 0 & 1 & 0 & - 15 \\ 0 & 0 & 1 & - 18 \\ 0 & 0 & 0 & 0 \end{array} \right].\tag{2.76}
$$

We see that the corresponding linear equation system is non-trivially solvable: The last column is not a pivot column, and $\pmb { x } _ { 4 } = - 7 \pmb { x } _ { 1 } - 15 \pmb { x } _ { 2 } - 18 \pmb { x } _ { 3 }$. Therefore, $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { 4 }$ are linearly dependent as $\mathbf { x } _ { 4 }$ can be expressed as a linear combination of $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { 3 }$.

## 2.6 Basis and Rank

In a vector space $V ,$ we are particularly interested in sets of vectors $\mathcal { A }$ that possess the property that any vector $v \in V$ can be obtained by a linear combination of vectors in ${ \mathcal { A } } .$ These vectors are special vectors, and in the following, we will characterize them. 

### 2.6.1 Generating Set and Basis

**Definition 2.13 (Generating Set and Span).** Consider a vector space $V=(\mathcal{V},+,\cdot)$ and set of vectors $\mathcal{A}=\{\boldsymbol{x}_1,\ldots,\boldsymbol{x}_k\}\subseteq\mathcal{V}$. If every vector $\boldsymbol{v}\in\mathcal{V}$ can be expressed as a linear combination of $\boldsymbol{x}_1,\ldots,\boldsymbol{x}_k$, $\mathcal{A}$ is called a generating set of $V$. The set of all linear combinations of vectors in $\mathcal{A}$ is called the span of $\mathcal{A}$. If $\mathcal{A}$ spans the vector space $V$, we write $V=\operatorname{span}[\mathcal{A}]$ or $V=\operatorname{span}[\boldsymbol{x}_1,\ldots,\boldsymbol{x}_k]$.

Generating sets are sets of vectors that span vector (sub)spaces, i.e., every vector can be represented as a linear combination of the vectors in the generating set. Now, we will be more specific and characterize the smallest generating set that spans a vector (sub)space. 

**Definition 2.14 (Basis).** Consider a vector space $V=(\mathcal{V},+,\cdot)$ and $\mathcal{A}\subseteq\mathcal{V}$. A generating set $\mathcal{A}$ of $V$ is called minimal if there exists no smaller set $\tilde{\mathcal{A}}\subsetneq\mathcal{A}\subseteq\mathcal{V}$ that spans $V$. Every linearly independent generating set of $V$ is minimal and is called a basis of $V$.

Let $V=(\mathcal{V},+,\cdot)$ be a vector space and $\mathcal{B}\subseteq\mathcal{V}$, $\mathcal{B}\neq\emptyset$. Then, the following statements are equivalent:

- $\mathcal{B}$ is a basis of $V$. 

- $\mathcal{B}$ is a minimal generating set. 

- $\mathcal{B}$ is a maximal linearly independent set of vectors in $V$, i.e., adding any other vector to this set will make it linearly dependent. 

- Every vector $\boldsymbol{x}\in V$ is a linear combination of vectors from $\mathcal{B}$, and every linear combination is unique, i.e., with 

$$
\boldsymbol {x} = \sum_ {i = 1} ^ {k} \lambda_ {i} \boldsymbol {b} _ {i} = \sum_ {i = 1} ^ {k} \psi_ {i} \boldsymbol {b} _ {i}\tag{2.77}
$$

and $\lambda _ { i } , \psi _ { i } \in \mathbb { R } , b _ { i } \in \mathcal { B }$ it follows that $\lambda _ { i } = \psi _ { i } , i = 1 , \ldots , k .$ 

> A basis is a minimal generating set and a maximal linearly independent set of vectors.

**Example 2.16**

- In $\mathbb { R } ^ { 3 }$ , the canonical/standard basis is 

  $$
  \mathcal {B} = \left\{\left[ \begin{array}{c} 1 \\ 0 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 0 \\ 1 \end{array} \right] \right\}.\tag{2.78}
  $$

- Different bases in $\mathbb { R } ^ { 3 }$ are 

  $$
  \mathcal {B} _ {1} = \left\{\left[ \begin{array}{l} 1 \\ 0 \\ 0 \end{array} \right], \left[ \begin{array}{l} 1 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{l} 1 \\ 1 \\ 1 \end{array} \right] \right\}, \mathcal {B} _ {2} = \left\{\left[ \begin{array}{l} 0.5 \\ 0.8 \\ 0.4 \end{array} \right], \left[ \begin{array}{l} 1.8 \\ 0.3 \\ 0.3 \end{array} \right], \left[ \begin{array}{l} - 2.2 \\ - 1.3 \\ 3.5 \end{array} \right] \right\}.\tag{2.79}
  $$

- The set 

  $$
  \mathcal {A} = \left\{\left[ \begin{array}{c} 1 \\ 2 \\ 3 \\ 4 \end{array} \right], \left[ \begin{array}{c} 2 \\ - 1 \\ 0 \\ 2 \end{array} \right], \left[ \begin{array}{c} 1 \\ 1 \\ 0 \\ - 4 \end{array} \right] \right\}\tag{2.80}
  $$

  is linearly independent, but not a generating set (and no basis) of $\mathbb{R}^{4}$: For instance, the vector $[1,0,0,0]^{\top}$ cannot be obtained by a linear combination of elements in $\mathcal{A}$. 

**Remark.** Every vector space $V$ possesses a basis $\mathcal{B}$. The preceding examples show that there can be many bases of a vector space $V$, i.e., there is no unique basis. However, all bases possess the same number of elements, the basis vectors. 

We only consider finite-dimensional vector spaces $V$. In this case, the dimension of $V$ is the number of basis vectors of $V$, and we write $\dim(V)$. If $U\subseteq V$ is a subspace of $V$, then $\dim(U)\leq\dim(V)$ and $\dim(U)=\dim(V)$ if and only if $U=V$. Intuitively, the dimension of a vector space can be thought of as the number of independent directions in this vector space.

> The dimension of a vector space corresponds to the number of its basis vectors.

**Remark.** The dimension of a vector space is not necessarily the number of elements in a vector. For instance, the vector space $V=\operatorname{span}\left[\begin{bmatrix}0\\1\end{bmatrix}\right]$ is one-dimensional, although the basis vector possesses two elements.

**Remark.** A basis of a subspace $U=\operatorname{span}[\boldsymbol{x}_1,\ldots,\boldsymbol{x}_m]\subseteq\mathbb{R}^{n}$ can be found by executing the following steps:

1. Write the spanning vectors as columns of a matrix $\boldsymbol{A}$. 

2. Determine the row-echelon form of A. 

3. The spanning vectors associated with the pivot columns are a basis of $U .$ 

**Example 2.17 (Determining a Basis)**

For a vector subspace $U \subseteq \mathbb { R } ^ { 5 }$ , spanned by the vectors 

$$
\boldsymbol {x} _ {1} = \left[ \begin{array}{c} 1 \\ 2 \\ - 1 \\ - 1 \\ - 1 \end{array} \right], \quad \boldsymbol {x} _ {2} = \left[ \begin{array}{c} 2 \\ - 1 \\ 1 \\ 2 \\ - 2 \end{array} \right], \quad \boldsymbol {x} _ {3} = \left[ \begin{array}{c} 3 \\ - 4 \\ 3 \\ 5 \\ - 3 \end{array} \right], \quad \boldsymbol {x} _ {4} = \left[ \begin{array}{c} - 1 \\ 8 \\ - 5 \\ - 6 \\ 1 \end{array} \right] \in \mathbb {R} ^ {5},\tag{2.81}
$$

we are interested in finding out which vectors $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { 4 }$ are a basis for U. For this, we need to check whether $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { 4 }$ are linearly independent. Therefore, we need to solve 

$$
\sum_ {i = 1} ^ {4} \lambda_ {i} \boldsymbol {x} _ {i} = \mathbf {0},\tag{2.82}
$$

which leads to a homogeneous system of equations with matrix 

$$
\left[ \boldsymbol {x} _ {1}, \boldsymbol {x} _ {2}, \boldsymbol {x} _ {3}, \boldsymbol {x} _ {4} \right] = \left[ \begin{array}{c c c c} 1 & 2 & 3 & - 1 \\ 2 & - 1 & - 4 & 8 \\ - 1 & 1 & 3 & - 5 \\ - 1 & 2 & 5 & - 6 \\ - 1 & - 2 & - 3 & 1 \end{array} \right].\tag{2.83}
$$

With the basic transformation rules for systems of linear equations, we obtain the row-echelon form 

$$
\left[\begin{array}{r r r r}1&2&3&- 1\\2&- 1&- 4&8\\- 1&1&3&- 5\\- 1&2&5&- 6\\- 1&- 2&- 3&1\end{array}\right] \quad \rightsquigarrow \dots \rightsquigarrow \quad \left[\begin{array}{r r r r}1&2&3&- 1\\0&1&2&- 2\\0&0&0&1\\0&0&0&0\\0&0&0&0\end{array}\right].
$$

Since the pivot columns indicate which set of vectors is linearly independent, we see from the row-echelon form that ${ \pmb x } _ { 1 } , { \pmb x } _ { 2 } , { \pmb x } _ { 4 }$ are linearly independent (because the system of linear equations $\lambda _ { 1 } \pmb { x } _ { 1 } + \lambda _ { 2 } \pmb { x } _ { 2 } + \lambda _ { 4 } \pmb { x } _ { 4 } = \mathbf { 0 }$ can only be solved with $\lambda _ { 1 } = \lambda _ { 2 } = \lambda _ { 4 } = 0 )$ . Therefore, $\{ \pmb { x } _ { 1 } , \pmb { x } _ { 2 } , \pmb { x } _ { 4 } \}$ is a basis of U. 

### 2.6.2 Rank

The number of linearly independent columns of a matrix $\pmb { { A } } \in \mathbb { R } ^ { m \times n }$ equals the number of linearly independent rows and is called the rank of A and is denoted by rk(A). 

**Remark.** The rank of a matrix has some important properties: 

- $\operatorname { r k } ( A ) = \operatorname { r k } ( A ^ { \top } )$ , i.e., the column rank equals the row rank. 

- The columns of $\pmb { A } \in \mathbb { R } ^ { m \times n }$ span a subspace $U \subseteq \mathbb { R } ^ { m }$ with $\dim ( U ) =$ $\operatorname { r k } ( A )$ . Later we will call this subspace the image or range. A basis of U can be found by applying Gaussian elimination to A to identify the pivot columns. 

- The rows of $\pmb { { A } } \in \mathbb { R } ^ { m \times n }$ span a subspace $W \subseteq \mathbb { R } ^ { n }$ with $\dim ( W ) =$ $\operatorname { r k } ( A )$ . A basis of W can be found by applying Gaussian elimination to $A^{\top}$. 

- For all $\pmb { A } \in \mathbb { R } ^ { n \times n }$ it holds that A is regular (invertible) if and only if $\operatorname { r k } ( A ) = n$ 

- For all $\pmb { { A } } \in \mathbb { R } ^ { m \times n }$ and all $\pmb { b } \in \mathbb { R } ^ { m }$ it holds that the linear equation system $\mathbf { A } { \boldsymbol { \mathbf { \mathit { x } } } } = \mathbf { \boldsymbol { \mathit { b } } }$ can be solved if and only if $\operatorname { r k } ( A ) = \operatorname { r k } ( A | b )$ , where $[\boldsymbol{A}\mid\boldsymbol{b}]$ denotes the augmented system. 

- For $\pmb { A } \in \mathbb { R } ^ { m \times n }$ the subspace of solutions for $\pmb { A } \pmb { x } = \mathbf { 0 }$ possesses dimension $n - \operatorname { r k } ( A )$ . Later, we will call this subspace the kernel or the null space. 

- A matrix $\pmb { A } \in \mathbb { R } ^ { m \times n }$ has full rank if its rank equals the largest possible rank for a matrix of the same dimensions. This means that the rank of a full-rank matrix is the lesser of the number of rows and columns, i.e., $\operatorname { r k } ( A ) = \operatorname* { m i n } ( m , n )$ . A matrix is said to be rank deficient if it does not have full rank. 

**Example 2.18 (Rank)** 

-

  $$
  \boldsymbol {A} = \left[ \begin{array}{l l l} 1 & 0 & 1 \\ 0 & 1 & 1 \\ 0 & 0 & 0 \end{array} \right].
  $$

  A has two linearly independent rows/columns so that rk $( A ) = 2 .$ 

-

  $$
  \boldsymbol {A} = \left[ \begin{array}{c c c} 1 & 2 & 1 \\ - 2 & - 3 & 1 \\ 3 & 5 & 0 \end{array} \right].
  $$

  We use Gaussian elimination to determine the rank: 

  $$
  \left[\begin{array}{c c c}1&2&1\\- 2&- 3&1\\3&5&0\end{array}\right] \quad \rightsquigarrow \dots \rightsquigarrow \quad \left[\begin{array}{c c c}1&2&1\\0&1&3\\0&0&0\end{array}\right]\tag{2.84}
  $$

  Here, we see that the number of linearly independent rows and columns is 2, such that $\operatorname{rk}(A)=2$. 

## 2.7 Linear Mappings

In the following, we will study mappings on vector spaces that preserve their structure, which will allow us to define the concept of a coordinate. In the beginning of the chapter, we said that vectors are objects that can be added together and multiplied by a scalar, and the resulting object is still a vector. We wish to preserve this property when applying the mapping: Consider two real vector spaces $V , W$ . A mapping $\Phi:V\to W$ preserves the structure of the vector space if 

$$
\Phi (\boldsymbol {x} + \boldsymbol {y}) = \Phi (\boldsymbol {x}) + \Phi (\boldsymbol {y})\tag{2.85}
$$

$$
\Phi (\lambda \boldsymbol {x}) = \lambda \Phi (\boldsymbol {x})\tag{2.86}
$$

for all $\boldsymbol{x},\boldsymbol{y}\in V$ and $\lambda \in \mathbb { R }$ . We can summarize this in the following definition: 

**Definition 2.15 (Linear Mapping).** For vector spaces $V,W$, a mapping $\Phi : V \to W$ is called a linear mapping (or vector space homomorphism/ linear transformation) if 

$$
\forall \boldsymbol {x}, \boldsymbol {y} \in V \forall \lambda , \psi \in \mathbb {R}: \Phi (\lambda \boldsymbol {x} + \psi \boldsymbol {y}) = \lambda \Phi (\boldsymbol {x}) + \psi \Phi (\boldsymbol {y}).\tag{2.87}
$$

It turns out that we can represent linear mappings as matrices (Section 2.7.1). Recall that we can also collect a set of vectors as columns of a matrix. When working with matrices, we have to keep in mind what the matrix represents: a linear mapping or a collection of vectors. We will see more about linear mappings in Chapter 4. Before we continue, we will briefly introduce special mappings. 

**Definition 2.16 (Injective, Surjective, Bijective).** Consider a mapping $\Phi:\mathcal{V}\to\mathcal{W}$, where $\mathcal{V},\mathcal{W}$ can be arbitrary sets. Then $\Phi$ is called

- Injective if $\forall x,y\in\mathcal{V}:\Phi(x)=\Phi(y)\implies x=y$.
- Surjective if $\Phi(\mathcal{V})=\mathcal{W}$.
- Bijective if it is injective and surjective.

If $\Phi$ is surjective, then every element in $\mathcal{W}$ can be “reached” from $\mathcal{V}$ using $\Phi$. A bijective $\Phi$ can be “undone”, i.e., there exists a mapping $\Psi:\mathcal{W}\to\mathcal{V}$ so that $\Psi\circ\Phi(\boldsymbol{x})=\boldsymbol{x}$. This mapping $\Psi$ is then called the inverse of $\Phi$ and normally denoted by $\Phi^{-1}$.

With these definitions, we introduce the following special cases of linear mappings between vector spaces $V$ and $W$: 

- Isomorphism: $\Phi:V\to W$ linear and bijective 

- Endomorphism: $\Phi:V\to V$ linear 

- Automorphism: $\Phi:V\to V$ linear and bijective 

- We define $\operatorname { i d } _ { V } : V \to V , x \mapsto x$ as the identity mapping or identity automorphism in $V$. 

**Example 2.19 (Homomorphism)**

The mapping $\Phi:\mathbb{R}^{2}\to\mathbb{C}$, $\Phi(\boldsymbol{x})=x_1+ix_2$, is a homomorphism: 

$$
\begin{array}{c} \Phi \left(\left[ \begin{array}{l} x _ {1} \\ x _ {2} \end{array} \right] + \left[ \begin{array}{l} y _ {1} \\ y _ {2} \end{array} \right]\right) = (x _ {1} + y _ {1}) + i (x _ {2} + y _ {2}) = x _ {1} + i x _ {2} + y _ {1} + i y _ {2} \\ = \Phi \left(\left[ \begin{array}{l} x _ {1} \\ x _ {2} \end{array} \right]\right) + \Phi \left(\left[ \begin{array}{l} y _ {1} \\ y _ {2} \end{array} \right]\right) \\ \Phi \left(\lambda \left[ \begin{array}{l} x _ {1} \\ x _ {2} \end{array} \right]\right) = \lambda x _ {1} + \lambda i x _ {2} = \lambda (x _ {1} + i x _ {2}) = \lambda \Phi \left(\left[ \begin{array}{l} x _ {1} \\ x _ {2} \end{array} \right]\right). \end{array}\tag{2.88}
$$

This also justifies why complex numbers can be represented as tuples in $\mathbb{R}^{2}$: There is a bijective linear mapping that converts the elementwise addition of tuples in $\mathbb { R } ^ { 2 }$ into the set of complex numbers with the corresponding addition. Note that we only showed linearity, but not the bijection. 

**Theorem 2.17 (Theorem 3.59 in Axler (2015)).** Finite-dimensional vector spaces $V$ and $W$ are isomorphic if and only if $\dim(V)=\dim(W)$ . 

Theorem 2.17 states that there exists a linear, bijective mapping between two vector spaces of the same dimension. Intuitively, this means that vector spaces of the same dimension are kind of the same thing, as they can be transformed into each other without incurring any loss. 

Theorem 2.17 also gives us the justification to treat $\mathbb { R } ^ { m \times n }$ (the vector space of $m \times n { \mathrm { - m a t r i c e s } } )$ and $\mathbb { R } ^ { m n }$ (the vector space of vectors of length mn) the same, as their dimensions are mn, and there exists a linear, bijective mapping that transforms one into the other. 

**Remark.** Consider vector spaces $V , W , X$ . Then: 

- For linear mappings $\Phi : V \to W$ and $\Psi : W \to X$ , the mapping $\Psi\circ\Phi:V\to X$ is also linear. 

- If $\Phi : V \to W$ is an isomorphism, then $\Phi ^ { - 1 } : W \to V$ is an isomorphism, too. 

- If $\Phi:V\to W$, $\Psi:V\to W$ are linear, then $\Phi+\Psi$ and $\lambda\Phi$, $\lambda\in\mathbb{R}$, are linear, too.

### 2.7.1 Matrix Representation of Linear Mappings

Any n-dimensional vector space is isomorphic to $\mathbb { R } ^ { n }$ (Theorem 2.17). We consider a basis $\{ b _ { 1 } , \ldots , b _ { n } \}$ of an n-dimensional vector space V. In the following, the order of the basis vectors will be important. Therefore, we write 

$$
B = (\boldsymbol {b} _ {1}, \dots , \boldsymbol {b} _ {n})\tag{2.89}
$$

and call this n-tuple an ordered basis of $V .$ 

**Remark (Notation).** We are at the point where notation gets a bit tricky. Therefore, we summarize some parts here. $B=(\boldsymbol{b}_1,\ldots,\boldsymbol{b}_n)$ is an ordered basis, $\mathcal{B}=\{\boldsymbol{b}_1,\ldots,\boldsymbol{b}_n\}$ is an (unordered) basis, and $\boldsymbol{B}=[\boldsymbol{b}_1,\ldots,\boldsymbol{b}_n]$ is a matrix whose columns are the vectors $\boldsymbol{b}_1,\ldots,\boldsymbol{b}_n$.

**Definition 2.18 (Coordinates).** Consider a vector space V and an ordered basis $B = ( b _ { 1 } , \ldots , b _ { n } )$ of $V$ . For any $\pmb { x } \in V$ we obtain a unique representation (linear combination) 

$$
\boldsymbol {x} = \alpha_ {1} \boldsymbol {b} _ {1} + \dots + \alpha_ {n} \boldsymbol {b} _ {n}\tag{2.90}
$$

of $\boldsymbol{x}$ with respect to $B$. Then $\alpha _ { 1 } , \ldots , \alpha _ { n }$ are the coordinates of x with respect to $B ,$ and the vector 

$$
\boldsymbol {\alpha} = \left[ \begin{array}{c} \alpha_ {1} \\ \vdots \\ \alpha_ {n} \end{array} \right] \in \mathbb {R} ^ {n}\tag{2.91}
$$

is the coordinate vector/coordinate representation of x with respect to the ordered basis B. 

A basis effectively defines a coordinate system. We are familiar with the Cartesian coordinate system in two dimensions, which is spanned by the canonical basis vectors $e _ { 1 } , e _ { 2 }$ . In this coordinate system, a vector $\pmb { x } \in \mathbb { R } ^ { 2 }$ has a representation that tells us how to linearly combine $e _ { 1 }$ and $e _ { 2 }$ to obtain $\boldsymbol{x}$. However, any basis of $\mathbb { R } ^ { 2 }$ defines a valid coordinate system, and the same vector x from before may have a different coordinate representation in the $( b _ { 1 } , b _ { 2 } )$ basis. In Figure 2.8, the coordinates of x with respect to the standard basis $(\boldsymbol{e}_1,\boldsymbol{e}_2)$ is $[2,2]^{\top}$ . However, with respect to the basis $\left( \boldsymbol { b } _ { 1 } , \boldsymbol { b } _ { 2 } \right)$ the same vector x is represented as $[1.09,0.72]^{\top}$ , i.e., $\boldsymbol{x}=1.09\boldsymbol{b}_1+0.72\boldsymbol{b}_2$ . In the following sections, we will discover how to obtain this representation. 

Figure 2.8 Two different coordinate systems defined by two sets of basis vectors. A vector x has different coordinate representations depending on which coordinate system is chosen. 

![image](<Images/02_Linear_Algebra_image_010.jpg>)

![image](<Images/02_Linear_Algebra_image_011.jpg>)

**Example 2.20**

Let us have a look at a geometric vector $\pmb { x } \in \mathbb { R } ^ { 2 }$ with coordinates $[ 2 , 3 ] ^ { \top }$ with respect to the standard basis $( e _ { 1 } , e _ { 2 } )$ of $\mathbb { R } ^ { 2 }$ . This means, we can write $\pmb { x } = 2 e _ { 1 } + 3 e _ { 2 }$ . However, we do not have to choose the standard basis to represent this vector. If we use the basis vectors $\pmb { b } _ { 1 } = [ 1 , - 1 ] ^ { \top } , \pmb { b } _ { 2 } = [ 1 , 1 ] ^ { \top }$ we will obtain the coordinates $\frac12[-1,5]^{\top}$ to represent the same vector with respect to $( b _ { 1 } , b _ { 2 } )$ (see Figure 2.9). 

Figure 2.9 Different coordinate representations of a vector $\boldsymbol{x}$, depending on the choice of basis.

![image](<Images/02_Linear_Algebra_image_012.jpg>)

Remark. For an n-dimensional vector space V and an ordered basis B of $V ,$ the mapping $\Phi : \mathbb { R } ^ { n } \to V , \Phi ( e _ { i } ) = \pmb { b } _ { i } , i = 1 , \dots , n$ , is linear (and because of Theorem 2.17 an isomorphism), where $( e _ { 1 } , \ldots , e _ { n } )$ is the standard basis of $\mathbb { R } ^ { n }$ 

Now we are ready to make an explicit connection between matrices and linear mappings between finite-dimensional vector spaces. 

**Definition 2.19 (Transformation Matrix).** Consider vector spaces $V , W$ with corresponding (ordered) bases $B = ( b _ { 1 } , \ldots , b _ { n } )$ and $C=(\boldsymbol{c}_1,\ldots,\boldsymbol{c}_m)$. Moreover, we consider a linear mapping $\Phi:V\to W$ . For $j \in \{ 1 , \ldots , n \}$ 

$$
\Phi (\boldsymbol {b} _ {j}) = \alpha_ {1 j} \boldsymbol {c} _ {1} + \dots + \alpha_ {m j} \boldsymbol {c} _ {m} = \sum_ {i = 1} ^ {m} \alpha_ {i j} \boldsymbol {c} _ {i}\tag{2.92}
$$

is the unique representation of $\Phi ( b _ { j } )$ with respect to $C$. Then, we call the $m\times n$-matrix $\pmb { A } _ { \Phi }$ , whose elements are given by 

$$
A _ {\Phi} (i, j) = \alpha_ {i j},\tag{2.93}
$$

the transformation matrix of Φ (with respect to the ordered bases B of V and $C$ of W). 

The coordinates of $\Phi(\boldsymbol{b}_j)$ with respect to the ordered basis $C$ of $W$ are the $j$-th column of $A_{\Phi}$. Consider (finite-dimensional) vector spaces $V,W$ with ordered bases $B,C$ and a linear mapping $\Phi:V\to W$ with transformation matrix $A_{\Phi}$. If $\hat{\boldsymbol{x}}$ is the coordinate vector of $\boldsymbol{x}\in V$ with respect to $B$ and $\hat{\boldsymbol{y}}$ the coordinate vector of $\boldsymbol{y}=\Phi(\boldsymbol{x})\in W$ with respect to $C$, then

$$
\hat {\boldsymbol {y}} = \boldsymbol {A} _ {\Phi} \hat {\boldsymbol {x}}.\tag{2.94}
$$

This means that the transformation matrix can be used to map coordinates with respect to an ordered basis in $V$ to coordinates with respect to an ordered basis in $W$ 

**Example 2.21 (Transformation Matrix)**

Consider a homomorphism $\Phi \ : \ V \ \to \ W$ and ordered bases $B=(\boldsymbol{b}_1,\ldots,\boldsymbol{b}_3)$ of V and $C = ( c _ { 1 } , \ldots , c _ { 4 } )$ of W. With 

$$
\begin{array}{l} \Phi (\boldsymbol {b} _ {1}) = \boldsymbol {c} _ {1} - \boldsymbol {c} _ {2} + 3 \boldsymbol {c} _ {3} - \boldsymbol {c} _ {4} \\ \Phi (\boldsymbol {b} _ {2}) = 2 \boldsymbol {c} _ {1} + \boldsymbol {c} _ {2} + 7 \boldsymbol {c} _ {3} + 2 \boldsymbol {c} _ {4} \\ \Phi (\boldsymbol {b} _ {3}) = 3 \boldsymbol {c} _ {2} + \boldsymbol {c} _ {3} + 4 \boldsymbol {c} _ {4} \end{array}\tag{2.95}
$$

the transformation matrix $A _ { \Phi }$ with respect to $B$ and $C$ satisfies $\Phi ( \boldsymbol { b } _ { k } ) =$ $\textstyle \sum _ { i = 1 } ^ { 4 } \alpha _ { i k } { \pmb { c } } _ { i }$ for $k = 1 , \ldots , 3$ and is given as 

$$
\boldsymbol {A} _ {\Phi} = \left[\boldsymbol{\alpha}_1,\boldsymbol{\alpha}_2,\boldsymbol{\alpha}_3\right] = \left[ \begin{array}{c c c} 1 & 2 & 0 \\ - 1 & 1 & 3 \\ 3 & 7 & 1 \\ - 1 & 2 & 4 \end{array} \right],\tag{2.96}
$$

where the $\boldsymbol{\alpha}_j$, $j=1,2,3$ , are the coordinate vectors of $\Phi ( \pmb { b } _ { j } )$ with respect to $C .$ 

**Example 2.22 (Linear Transformations of Vectors)**

Figure 2.10 Three examples of linear transformations of the vectors shown as dots in (a); (b) Rotation by $45^{\circ}$; (c) Stretching of the horizontal coordinates by 2; (d) Combination of reflection, rotation and stretching. 

![image](<Images/02_Linear_Algebra_image_013.jpg>)

(a) Original data.

![image](<Images/02_Linear_Algebra_image_014.jpg>)

(b) Rotation by $45^{\circ}$.

![image](<Images/02_Linear_Algebra_image_015.jpg>)

(c) Stretch along the horizontal axis.

![image](<Images/02_Linear_Algebra_image_016.jpg>)

(d) General linear mapping.

We consider three linear transformations of a set of vectors in $\mathbb { R } ^ { 2 }$ with the transformation matrices 

$$
\boldsymbol {A} _ {1} = \left[ \begin{array}{c c} \cos (\frac {\pi}{4}) & - \sin (\frac {\pi}{4}) \\ \sin (\frac {\pi}{4}) & \cos (\frac {\pi}{4}) \end{array} \right], \boldsymbol {A} _ {2} = \left[ \begin{array}{c c} 2 & 0 \\ 0 & 1 \end{array} \right], \boldsymbol {A} _ {3} = \frac {1}{2} \left[ \begin{array}{c c} 3 & - 1 \\ 1 & - 1 \end{array} \right].\tag{2.97}
$$

Figure 2.10 gives three examples of linear transformations of a set of vectors. Figure 2.10(a) shows 400 vectors in $\mathbb { R } ^ { 2 }$ , each of which is represented by a dot at the corresponding $( x _ { 1 } , x _ { 2 } )$ -coordinates. The vectors are arranged in a square. When we use matrix $\pmb { A } _ { 1 }$ in (2.97) to linearly transform each of these vectors, we obtain the rotated square in Figure 2.10(b). If we apply the linear mapping represented by $A _ { 2 }$ , we obtain the rectangle in Figure 2.10(c) where each $x _ { 1 }$ -coordinate is stretched by 2. Figure 2.10(d) shows the original square from Figure 2.10(a) when linearly transformed using $A _ { 3 } ,$ which is a combination of a reflection, a rotation, and a stretch. 

### 2.7.2 Basis Change

In the following, we will have a closer look at how transformation matrices of a linear mapping $\Phi:V\to W$ change if we change the bases in $V$ and $W$ . Consider two ordered bases 

$$
B = (\boldsymbol {b} _ {1}, \dots , \boldsymbol {b} _ {n}), \quad \tilde {B} = (\tilde {\boldsymbol {b}} _ {1}, \dots , \tilde {\boldsymbol {b}} _ {n})\tag{2.98}
$$

of $V$ and two ordered bases 

$$
C = (\pmb {c} _ {1}, \dots , \pmb {c} _ {m}), \quad \tilde {C} = (\tilde {\pmb {c}} _ {1}, \dots , \tilde {\pmb {c}} _ {m})\tag{2.99}
$$

of $W$. Moreover, $A _ { \Phi } \in \mathbb { R } ^ { m \times n }$ is the transformation matrix of the linear mapping $\Phi:V\to W$ with respect to the bases $B$ and $C ,$ and $\tilde { \mathbf { A } } _ { \Phi } \in \mathbb { R } ^ { m \times n }$ is the corresponding transformation mapping with respect to $\tilde{B}$ and $\tilde{C}$. In the following, we will investigate how $\pmb { A }$ and $\tilde { \boldsymbol { A } }$ are related, $\mathrm { i . e . }$ , how/ whether we can transform $A _ { \Phi }$ into $\tilde { A } _ { \Phi }$ if we choose to perform a basis change from $B , C$ to $\tilde { B } , \tilde { C }$ 

Remark. We effectively get different coordinate representations of the identity mapping $\operatorname{id}_V$. In the context of Figure 2.9, this would mean to map coordinates with respect to $( e _ { 1 } , e _ { 2 } )$ onto coordinates with respect to $( b _ { 1 } , b _ { 2 } )$ without changing the vector ${ \pmb x } .$ . By changing the basis and correspondingly the representation of vectors, the transformation matrix with respect to this new basis can have a particularly simple form that allows for straightforward computation. 

**Example 2.23 (Basis Change)**

Consider a transformation matrix 

$$
\boldsymbol {A} = \left[ \begin{array}{c c} 2 & 1 \\ 1 & 2 \end{array} \right]\tag{2.100}
$$

with respect to the canonical basis in $\mathbb { R } ^ { 2 }$ . If we define a new basis 

$$
B = (\left[ \begin{array}{c} 1 \\ 1 \end{array} \right], \left[ \begin{array}{c} 1 \\ - 1 \end{array} \right])\tag{2.101}
$$

we obtain a diagonal transformation matrix 

$$
\tilde {\pmb {A}} = \left[ \begin{array}{c c} 3 & 0 \\ 0 & 1 \end{array} \right]\tag{2.102}
$$

with respect to $B$, which is easier to work with than A. 

In the following, we will look at mappings that transform coordinate vectors with respect to one basis into coordinate vectors with respect to a different basis. We will state our main result first and then provide an explanation. 

**Theorem 2.20 (Basis Change).** For a linear mapping $\Phi : V \to W$ , ordered bases 

$$
B = (\boldsymbol {b} _ {1}, \dots , \boldsymbol {b} _ {n}), \quad \tilde {B} = (\tilde {\boldsymbol {b}} _ {1}, \dots , \tilde {\boldsymbol {b}} _ {n})\tag{2.103}
$$

of $V$ and 

$$
C = (\pmb {c} _ {1}, \dots , \pmb {c} _ {m}), \quad \tilde {C} = (\tilde {\pmb {c}} _ {1}, \dots , \tilde {\pmb {c}} _ {m})\tag{2.104}
$$

of $W ,$ and a transformation matrix $A _ { \Phi }$ of Φ with respect to $B$ and $C ,$ the corresponding transformation matrix $\tilde { A } _ { \Phi }$ with respect to the bases $\tilde { B }$ and $\tilde { C }$ is given as 

$$
\tilde {\boldsymbol {A}} _ {\Phi} = \boldsymbol {T} ^ {- 1} \boldsymbol {A} _ {\Phi} \boldsymbol {S}.\tag{2.105}
$$

Here, $\boldsymbol{S}\in\mathbb{R}^{n\times n}$ is the transformation matrix of $\operatorname{id}_V$ that maps coordinates with respect to $\tilde { B }$ onto coordinates with respect to $B ,$ and $\pmb { T } \in \mathbb { R } ^ { m \times m }$ is the transformation matrix of $\mathrm { i d } _ { W }$ that maps coordinates with respect to $\tilde { C }$ onto coordinates with respect to $C .$ 

**Proof.** Following Drumm and Weil (2001), we can write the vectors of the new basis $\tilde { B }$ of $V$ as a linear combination of the basis vectors of $B ,$ such that 

$$
\tilde {\boldsymbol {b}} _ {j} = s _ {1 j} \boldsymbol {b} _ {1} + \dots + s _ {n j} \boldsymbol {b} _ {n} = \sum_ {i = 1} ^ {n} s _ {i j} \boldsymbol {b} _ {i}, \quad j = 1, \dots , n.\tag{2.106}
$$

Similarly, we write the new basis vectors $\tilde { C }$ of $W$ as a linear combination of the basis vectors of $C$, which yields 

$$
\tilde {\boldsymbol {c}} _ {k} = t _ {1 k} \boldsymbol {c} _ {1} + \dots + t _ {m k} \boldsymbol {c} _ {m} = \sum_ {l = 1} ^ {m} t _ {l k} \boldsymbol {c} _ {l}, \quad k = 1, \ldots , m.\tag{2.107}
$$

We define $S = ( ( s _ { i j } ) ) \in \mathbb { R } ^ { n \times n }$ as the transformation matrix that maps coordinates with respect to $\tilde { B }$ onto coordinates with respect to $B$ and $\pmb { T } = \left( \left( t _ { l k } \right) \right) \in \mathbb { R } ^ { m \times m }$ as the transformation matrix that maps coordinates with respect to $\tilde { C }$ onto coordinates with respect to C. In particular, the $j$-th column of $\boldsymbol{S}$ is the coordinate representation of $\tilde { \boldsymbol { b } } _ { j }$ with respect to $B$ and the kth column of T is the coordinate representation of $\tilde { c } _ { k }$ with respect to C. Note that both S and $\mathbf { T }$ are regular. 

We are going to look at $\Phi ( \tilde { \pmb { b } } _ { j } )$ from two perspectives. First, applying the mapping Φ, we get that for all $j = 1 , \dotsc , n$ 

$$
\Phi (\tilde {\boldsymbol {b}} _ {j}) = \sum_ {k = 1} ^ {m} \underbrace {\tilde {a} _ {k j} \tilde {\boldsymbol {c}} _ {k}} _ {\in W} \stackrel {(2.107)} {=} \sum_ {k = 1} ^ {m} \tilde {a} _ {k j} \sum_ {l = 1} ^ {m} t _ {l k} \boldsymbol {c} _ {l} = \sum_ {l = 1} ^ {m} \left(\sum_ {k = 1} ^ {m} t _ {l k} \tilde {a} _ {k j}\right) \boldsymbol {c} _ {l},\tag{2.108}
$$

where we first expressed the new basis vectors $\tilde { \boldsymbol { c } } _ { k } ~ \in ~ W$ as linear combinations of the basis vectors $\mathbf { \boldsymbol { c } } _ { l } ~ \in ~ W$ and then swapped the order of summation. 

Alternatively, when we express the $\tilde { \pmb { b } } _ { j } \in V$ as linear combinations of $b _ { j } \in V$ , we arrive at 

$$
\Phi (\tilde {\boldsymbol {b}} _ {j}) \stackrel {(2.106)} {=} \Phi \left(\sum_ {i = 1} ^ {n} s _ {i j} \boldsymbol {b} _ {i}\right) = \sum_ {i = 1} ^ {n} s _ {i j} \Phi (\boldsymbol {b} _ {i}) = \sum_ {i = 1} ^ {n} s _ {i j} \sum_ {l = 1} ^ {m} a _ {l i} \boldsymbol {c} _ {l}\tag{2.109a}
$$

$$
= \sum_ {l = 1} ^ {m} \left(\sum_ {i = 1} ^ {n} a _ {l i} s _ {i j}\right) \boldsymbol {c} _ {l}, \quad j = 1, \ldots , n,\tag{2.109b}
$$

where we exploited the linearity of Φ. Comparing (2.108) and (2.109b), it follows for all $j = 1 , \dotsc , n$ and $l = 1 , \ldots , m$ that 

$$
\sum_ {k = 1} ^ {m} t _ {l k} \tilde {a} _ {k j} = \sum_ {i = 1} ^ {n} a _ {l i} s _ {i j}\tag{2.110}
$$

and, therefore, 

$$
\boldsymbol {T} \tilde {\boldsymbol {A}} _ {\Phi} = \boldsymbol {A} _ {\Phi} \boldsymbol {S} \in \mathbb {R} ^ {m \times n},\tag{2.111}
$$

such that 

$$
\tilde {\boldsymbol {A}} _ {\Phi} = \boldsymbol {T} ^ {- 1} \boldsymbol {A} _ {\Phi} \boldsymbol {S},\tag{2.112}
$$

which proves Theorem 2.20. 

Theorem 2.20 tells us that with a basis change in $V$ ($B$ is replaced with $\tilde{B}$) and $W$ (C is replaced with $\tilde { C } )$ , the transformation matrix $A _ { \Phi }$ of a linear mapping $\Phi:V\to W$ is replaced by an equivalent matrix $\tilde { \mathbf { A } } _ { \Phi }$ with 

$$
\tilde {\boldsymbol {A}} _ {\Phi} = \boldsymbol {T} ^ {- 1} \boldsymbol {A} _ {\Phi} \boldsymbol {S}.\tag{2.113}
$$

Figure 2.11 illustrates this relation: Consider a homomorphism $\Phi:V\to W$ and ordered bases B, $\tilde { B }$ of $V$ and $C , { \tilde { C } }$ of W. The mapping $\Phi _ { C B }$ is an instantiation of $\Phi$ and maps basis vectors of B onto linear combinations of basis vectors of C. Assume that we know the transformation matrix $A _ { \Phi }$ of $\Phi _ { C B }$ with respect to the ordered bases B, C. When we perform a basis change from $B$ to $\tilde { B }$ in $V$ and from $C$ to $\tilde { C }$ in $W$, we can determine the corresponding transformation matrix $\tilde { \mathbf { A } } _ { \Phi }$ as follows: First, we find the matrix representation of the linear mapping $\Psi_{B\tilde{B}}:V\to V$ that maps coordinates with respect to the new basis $\tilde { B }$ onto the (unique) coordinates with respect to the “old” basis $B$ (in $V )$ . Then, we use the transformation matrix $A _ { \Phi }$ of $\Phi _ { C B } : V \to W$ to map these coordinates onto the coordinates with respect to $C$ in W. Finally, we use a linear mapping $\Xi _ { \tilde { C } C } : W \to W$ to map the coordinates with respect to $C$ onto coordinates with respect to ${ \tilde { C } } .$ Therefore, we can express the linear mapping $\Phi _ { \tilde { C } \tilde { B } }$ as a composition of linear mappings that involve the “old” basis: 

$$
\Phi_ {\tilde {C} \tilde {B}} = \Xi_ {\tilde {C} C} \circ \Phi_ {C B} \circ \Psi_ {B \tilde {B}} = \Xi_ {C \tilde {C}} ^ {- 1} \circ \Phi_ {C B} \circ \Psi_ {B \tilde {B}}.\tag{2.114}
$$

Concretely, we use $\Psi _ { B \tilde { B } } = \mathrm { i d } _ { V }$ and $\Xi _ { C \tilde { C } } = \mathrm { i d } _ { W }$ , i.e., the identity mappings that map vectors onto themselves, but with respect to a different basis. 

![Figure 2.11: Composition of basis-change mappings](<Images/02_Linear_Algebra_Figure_2_11.png>)

Figure 2.11 For a homomorphism $\Phi:V\to W$ and ordered bases $B,\tilde{B}$ of $V$ and $C,\tilde{C}$ of $W$ (marked in blue), we can express the mapping $\Phi_{\tilde{C}\tilde{B}}$ with respect to the bases $\tilde{B},\tilde{C}$ equivalently as a composition of the homomorphisms $\Phi_{\tilde{C}\tilde{B}}=\Xi_{\tilde{C}C}\circ\Phi_{CB}\circ\Psi_{B\tilde{B}}$ with respect to the bases in the subscripts. The corresponding transformation matrices are in red.

**Definition 2.21 (Equivalence).** Two matrices $\boldsymbol{A},\tilde{\boldsymbol{A}}\in\mathbb{R}^{m\times n}$ are equivalent if there exist regular matrices $S ~ \in ~ \mathbb { R } ^ { n \times n }$ and $\pmb { T } \in \mathbb { R } ^ { m \times m }$ , such that $\tilde { \pmb { A } } = \pmb { T } ^ { - 1 } \pmb { A } \pmb { S }$ 

**Definition 2.22 (Similarity).** Two matrices $\pmb { A } , \tilde { \pmb { A } } \in \mathbb { R } ^ { n \times n }$ are similar if there exists a regular matrix $\boldsymbol{S}\in\mathbb{R}^{n\times n}$ with $\tilde { \pmb { A } } = \pmb { S } ^ { - 1 } \pmb { A } \pmb { S }$ 

Remark. Similar matrices are always equivalent. However, equivalent matrices are not necessarily similar. $\diamondsuit$ 

Remark. Consider vector spaces $V , W , X$ . From the remark that follows Theorem 2.17, we already know that for linear mappings $\Phi : V \to W$ and $\Psi : W \to X$ the mapping $\Psi\circ\Phi:V\to X$ is also linear. With transformation matrices $A _ { \Phi }$ and $\pmb { A } _ { \Psi }$ of the corresponding mappings, the overall transformation matrix is $\pmb { A } _ { \Psi \circ \Phi } = \pmb { A } _ { \Psi } \pmb { A } _ { \Phi }$ $\diamondsuit$ 

In light of this remark, we can look at basis changes from the perspective of composing linear mappings: 

- $A _ { \Phi }$ is the transformation matrix of a linear mapping $\Phi _ { C B } : V \to W$ with respect to the bases $B , C .$ 

- $\tilde { \mathbf { A } } _ { \Phi }$ is the transformation matrix of the linear mapping $\Phi _ { \tilde { C } \tilde { B } } : V \to W$ with respect to the bases $\tilde { B } , \tilde { C } .$ 

- S is the transformation matrix of a linear mapping $\Psi_{B\tilde{B}}:V\to V$ (automorphism) that represents $\tilde { B }$ in terms of $B$. Normally, $\Psi = \operatorname { i d } _ { V }$ is the identity mapping in $V$ 

- T is the transformation matrix of a linear mapping $\Xi _ { C \tilde { C } } : W \to W$ (automorphism) that represents $\tilde { C }$ in terms of C. Normally, $\Xi = \mathrm { i d } _ { W }$ is the identity mapping in $W$ 

If we (informally) write down the transformations just in terms of bases, then $A_{\Phi}:B\to C$, $\tilde{A}_{\Phi}:\tilde{B}\to\tilde{C}$, $S:\tilde{B}\to B$, $T:\tilde{C}\to C$ and $T^{-1}:C\to\tilde{C}$, and

$$
\tilde {B} \rightarrow \tilde {C} = \tilde {B} \rightarrow B \rightarrow C \rightarrow \tilde {C}\tag{2.115}
$$

$$
\tilde {\boldsymbol {A}} _ {\Phi} = \boldsymbol {T} ^ {- 1} \boldsymbol {A} _ {\Phi} \boldsymbol {S}.\tag{2.116}
$$

Note that the execution order in (2.116) is from right to left because vectors are multiplied at the right-hand side so that $\pmb { x } \mapsto \pmb { S x } \mapsto \pmb { A } _ { \Phi } ( \pmb { S x } ) \mapsto$ $\pmb { T } ^ { - 1 } \big ( \pmb { A } _ { \Phi } ( \pmb { S } \pmb { x } ) \big ) = \tilde { \pmb { A } } _ { \Phi } \pmb { x }$ 

**Example 2.24 (Basis Change)**

Consider a linear mapping $\Phi:\mathbb{R}^{3}\to\mathbb{R}^{4}$ whose transformation matrix is 

$$
\boldsymbol {A} _ {\Phi} = \left[ \begin{array}{c c c} 1 & 2 & 0 \\ - 1 & 1 & 3 \\ 3 & 7 & 1 \\ - 1 & 2 & 4 \end{array} \right]\tag{2.117}
$$

with respect to the standard bases 

$$
B = (\left[ \begin{array}{c} 1 \\ 0 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 0 \\ 1 \end{array} \right]), \quad C = (\left[ \begin{array}{c} 1 \\ 0 \\ 0 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 1 \\ 0 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 0 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 0 \\ 0 \\ 1 \end{array} \right]).\tag{2.118}
$$

We seek the transformation matrix $\tilde { \mathbf { A } } _ { \Phi }$ of Φ with respect to the new bases 

$$
\tilde {B} = (\left[ \begin{array}{c} 1 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 1 \\ 1 \end{array} \right], \left[ \begin{array}{c} 1 \\ 0 \\ 1 \end{array} \right]) \in \mathbb {R} ^ {3}, \quad \tilde {C} = (\left[ \begin{array}{c} 1 \\ 1 \\ 0 \\ 0 \end{array} \right], \left[ \begin{array}{c} 1 \\ 0 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 1 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 1 \\ 0 \\ 0 \\ 1 \end{array} \right]).\tag{2.119}
$$

Then, 

$$
\boldsymbol {S} = \left[ \begin{array}{c c c} 1 & 0 & 1 \\ 1 & 1 & 0 \\ 0 & 1 & 1 \end{array} \right], \qquad \boldsymbol {T} = \left[ \begin{array}{c c c c} 1 & 1 & 0 & 1 \\ 1 & 0 & 1 & 0 \\ 0 & 1 & 1 & 0 \\ 0 & 0 & 0 & 1 \end{array} \right],\tag{2.120}
$$

where the ith column of S is the coordinate representation of $\tilde { \pmb { b } } _ { i }$ in terms of the basis vectors of B. Since B is the standard basis, the coordinate representation is straightforward to find. For a general basis $B$, we would need to solve a linear equation system to find the $\lambda _ { i }$ such that 

$\begin{array} { r } { \sum _ { i = 1 } ^ { 3 } \lambda _ { i } \pmb { b } _ { i } = \tilde { \pmb { b } } _ { j } , j = 1 , \dots , 3 } \end{array}$ . Similarly, the $j$-th column of $\boldsymbol{T}$ is the coordinate representation of $\tilde { \boldsymbol { c } } _ { j }$ in terms of the basis vectors of C. 

Therefore, we obtain 

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

In Chapter 4, we will be able to exploit the concept of a basis change to find a basis with respect to which the transformation matrix of an endomorphism has a particularly simple (diagonal) form. In Chapter 10, we will look at a data compression problem and find a convenient basis onto which we can project the data while minimizing the compression loss. 

### 2.7.3 Image and Kernel

The image and kernel of a linear mapping are vector subspaces with certain important properties. In the following, we will characterize them more carefully. 

**Definition 2.23 (Image and Kernel).** 

For $\Phi:V\to W$ , we define the kernel/null space 

$$
\ker (\Phi) := \Phi^ {- 1} (\mathbf {0} _ {W}) = \{\boldsymbol {v} \in V: \Phi (\boldsymbol {v}) = \mathbf {0} _ {W} \}\tag{2.122}
$$

and the image/range 

$$
\operatorname{Im} (\Phi) := \Phi (V) = \left\{\boldsymbol {w} \in W | \exists \boldsymbol {v} \in V: \Phi (\boldsymbol {v}) = \boldsymbol {w} \right\}.\tag{2.123}
$$

We also call V and W also the domain and codomain of Φ, respectively. 

Intuitively, the kernel is the set of vectors $v \in V$ that Φ maps onto the neutral element ${ \mathbf { 0 } } _ { W } \in W$ . The image is the set of vectors $\boldsymbol{w}\in W$ that can be “reached” by Φ from any vector in V. An illustration is given in Figure 2.12. 

![image](<Images/02_Linear_Algebra_image_017.jpg>)

Figure 2.12 Kernel and image of a linear mapping Φ : V → W.

**Remark.** Consider a linear mapping $\Phi : V \to W$ , where $V , W$ are vector spaces. 

- It always holds that $\Phi ( { \bf 0 } _ { V } ) = { \bf 0 } _ { W }$ and, therefore, ${ \mathbf { 0 } _ { V } } \in \mathop { \ker } ( \Phi )$ . In particular, the null space is never empty. 

- $\operatorname{Im}(\Phi)\subseteq W$ is a subspace of $W$, and $\ker(\Phi)\subseteq V$ is a subspace of $V$. 

- Φ is injective (one-to-one) if and only if $\ker ( \Phi ) = \{ \mathbf { 0 } \}$ 

**Remark (Null Space and Column Space).** Let us consider $\boldsymbol{A}\in\mathbb{R}^{m\times n}$ and a linear mapping $\Phi:\mathbb{R}^{n}\to\mathbb{R}^{m}$, $\boldsymbol{x}\mapsto\boldsymbol{A}\boldsymbol{x}$. 

- For $\pmb { A } = [ \pmb { a } _ { 1 } , \dots , \pmb { a } _ { n } ]$ , where $\mathbf { a } _ { i }$ are the columns of A, we obtain 

$$
\operatorname{Im}(\Phi)=\{\boldsymbol{A}\boldsymbol{x}:\boldsymbol{x}\in\mathbb{R}^{n}\}
=\left\{\sum_{i=1}^{n}x_i\boldsymbol{a}_i:x_1,\ldots,x_n\in\mathbb{R}\right\}
\tag{2.124a}
$$

$$
=\operatorname{span}[\boldsymbol{a}_1,\ldots,\boldsymbol{a}_n]\subseteq\mathbb{R}^{m},
\tag{2.124b}
$$ 

  i.e., the image is the span of the columns of A, also called the column space. Therefore, the column space (image) is a subspace of $\mathbb { R } ^ { m }$ , where m is the “height” of the matrix. 

- $\operatorname{rk}(A)=\dim(\operatorname{Im}(\Phi))$. 

- The kernel/null space ker(Φ) is the general solution to the homogeneous system of linear equations $\mathbf { { \boldsymbol { A } } } \mathbf { { \boldsymbol { x } } } = \mathbf { { \boldsymbol { 0 } } }$ and captures all possible linear combinations of the elements in $\mathbb { R } ^ { n }$ that produce $\mathbf { 0 } \in \mathbb { R } ^ { m }$ 

- The kernel is a subspace of $\mathbb{R}^{n}$, where n is the “width” of the matrix. 

- The kernel focuses on the relationship among the columns, and we can use it to determine whether/how we can express a column as a linear combination of other columns. 

**Example 2.25 (Image and Kernel of a Linear Mapping)**

The mapping

$$
\Phi : \mathbb {R} ^ {4} \to \mathbb {R} ^ {2}, \quad \left[ \begin{array}{c} x _ {1} \\ x _ {2} \\ x _ {3} \\ x _ {4} \end{array} \right] \mapsto \left[ \begin{array}{c c c c} 1 & 2 & - 1 & 0 \\ 1 & 0 & 0 & 1 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \\ x _ {3} \\ x _ {4} \end{array} \right] = \left[ \begin{array}{c} x _ {1} + 2 x _ {2} - x _ {3} \\ x _ {1} + x _ {4} \end{array} \right]\tag{2.125a}
$$

 

$$
= x _ {1} \left[ \begin{array}{c} 1 \\ 1 \end{array} \right] + x _ {2} \left[ \begin{array}{c} 2 \\ 0 \end{array} \right] + x _ {3} \left[ \begin{array}{c} - 1 \\ 0 \end{array} \right] + x _ {4} \left[ \begin{array}{c} 0 \\ 1 \end{array} \right]\tag{2.125b}
$$

is linear. To determine Im(Φ), we can take the span of the columns of the transformation matrix and obtain 

$$
\mathrm{Im} (\Phi) = \mathrm{span} [ \left[ \begin{array}{c} 1 \\ 1 \end{array} \right], \left[ \begin{array}{c} 2 \\ 0 \end{array} \right], \left[ \begin{array}{c} - 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 1 \end{array} \right] ].\tag{2.126}
$$

To compute the kernel (null space) of Φ, we need to solve $A\boldsymbol{x}=\boldsymbol{0}$, i.e., we need to solve a homogeneous equation system. To do this, we use Gaussian elimination to transform A into reduced row-echelon form: 

$$
\left[\begin{array}{c c c c}1&2&- 1&0\\1&0&0&1\end{array}\right] \quad \rightsquigarrow \dots \rightsquigarrow \quad \left[\begin{array}{c c c c}1&0&0&1\\0&1&- \frac {1}{2}&- \frac {1}{2}\end{array}\right].\tag{2.127}
$$

This matrix is in reduced row-echelon form, and we can use the Minus-1 Trick to compute a basis of the kernel (see Section 2.3.3). Alternatively, we can express the non-pivot columns (columns 3 and 4) as linear combinations of the pivot columns (columns 1 and 2). The third column ${ \bf { a } } _ { 3 }$ is equivalent to $- \frac 1 2$ times the second column $\mathbf { a } _ { 2 }$ . Therefore, ${ \bf 0 } = { \bf a } _ { 3 } + \frac { 1 } { 2 } { \bf a } _ { 2 }$ . In the same way, we see that $\mathbf { a } _ { 4 } = \mathbf { a } _ { 1 } - \frac { 1 } { 2 } \mathbf { a } _ { 2 }$ and, therefore, $\mathbf { 0 } = { \pmb a } _ { 1 } - \frac { 1 } { 2 } { \pmb a } _ { 2 } - { \pmb a } _ { 4 }$. Overall, this gives us the kernel (null space) as 

$$
\ker (\Phi) = \operatorname{span} [ \left[ \begin{array}{c} 0 \\ \frac {1}{2} \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} - 1 \\ \frac {1}{2} \\ 0 \\ 1 \end{array} \right] ].\tag{2.128}
$$

**Theorem 2.24 (Rank-Nullity Theorem).** For vector spaces $V , W$ and a linear mapping $\Phi:V\to W$ it holds that 

$$
\dim (\ker (\Phi)) + \dim (\operatorname{Im} (\Phi)) = \dim (V).\tag{2.129}
$$

The rank-nullity theorem is also referred to as the fundamental theorem of linear mappings (Axler, 2015, theorem 3.22). The following are direct consequences of Theorem 2.24: 

- If $\dim(\operatorname{Im}(\Phi))<\dim(V)$, then $\ker(\Phi)$ is non-trivial, i.e., the kernel contains more than $\mathbf { 0 } _ { V }$ and $\dim ( \ker ( \Phi ) ) \geqslant 1$ 

- If $A _ { \Phi }$ is the transformation matrix of Φ with respect to an ordered basis and $\dim(\operatorname{Im}(\Phi))<\dim(V)$ , then the system of linear equations $\boldsymbol{A}_{\Phi}\boldsymbol{x}=\boldsymbol{0}$ has infinitely many solutions. 

- If $\dim ( V ) = \dim ( W )$ , then the three-way equivalence 

  Φ is injective $\iff$ Φ is surjective $\iff$ Φ is bijective 

  holds since $\operatorname{Im}(\Phi)\subseteq W$.

## 2.8 Affine Spaces

In the following, we will take a closer look at spaces that are offset from the origin, i.e., spaces that are no longer vector subspaces. Moreover, we will briefly discuss properties of mappings between these affine spaces, which resemble linear mappings. 

**Remark.** In the machine learning literature, the distinction between linear and affine is sometimes not clear so that we can find references to affine spaces/mappings as linear spaces/mappings. 

### 2.8.1 Affine Subspaces

**Definition 2.25 (Affine Subspace).** Let V be a vector space, $\pmb { x } _ { 0 } \in V$ and $U \subseteq V$ a subspace. Then the subset 

$$
L = \boldsymbol {x} _ {0} + U := \left\{\boldsymbol {x} _ {0} + \boldsymbol {u}: \boldsymbol {u} \in U \right\}\tag{2.130a}
$$

$$
= \left\{\boldsymbol {v} \in V | \exists \boldsymbol {u} \in U: \boldsymbol {v} = \boldsymbol {x} _ {0} + \boldsymbol {u} \right\} \subseteq V\tag{2.130b}
$$

is called affine subspace or linear manifold of V. U is called direction or direction space, and $\scriptstyle { \pmb x } _ { 0 }$ is called support point. In Chapter 12, we refer to such a subspace as a hyperplane. 

Note that the definition of an affine subspace excludes 0 if $\boldsymbol{x}_0\notin U$. Therefore, an affine subspace is not a (linear) subspace (vector subspace) of V for ${ \pmb x } _ { 0 } \not \in U$ 

Examples of affine subspaces are points, lines, and planes in $\mathbb { R } ^ { 3 }$ , which do not (necessarily) go through the origin. 

**Remark.** Consider two affine subspaces $L = { \pmb x } _ { 0 } + U$ and $\tilde { L } = \tilde { \mathbf { x } } _ { 0 } + \tilde { U }$ of a vector space V. Then, $L \subseteq { \tilde { L } }$ if and only if $U \subseteq { \tilde { U } }$ and ${ \pmb x } _ { 0 } - { \pmb { \tilde { x } } } _ { 0 } \in \tilde { U }$ 

Affine subspaces are often described by parameters: Consider a k-dimensional affine space ${ \boldsymbol { L } } = { \mathbf { { x } } } _ { 0 } + { \boldsymbol { U } }$ of V. If $\left( \pmb { b } _ { 1 } , \dots , \pmb { b } _ { k } \right)$ is an ordered basis of $U$ , then every element $\boldsymbol { x } \in L$ can be uniquely described as 

$$
\boldsymbol {x} = \boldsymbol {x} _ {0} + \lambda_ {1} \boldsymbol {b} _ {1} + \dots + \lambda_ {k} \boldsymbol {b} _ {k},\tag{2.131}
$$

where $\lambda _ { 1 } , \ldots , \lambda _ { k } \in \mathbb { R }$ . This representation is called parametric equation of L with directional vectors $\boldsymbol { b } _ { 1 } , \ldots , \boldsymbol { b } _ { k }$ and parameters $\lambda _ { 1 } , \ldots , \lambda _ { k }$ 

**Example 2.26 (Affine Subspaces)**

- One-dimensional affine subspaces are called lines and can be written as $\pmb { y } = \pmb { x } _ { 0 } + \lambda \pmb { b } _ { 1 }$ where $\lambda \in \mathbb { R }$ and $U = \mathrm { s p a n } [ b _ { 1 } ] \ \subseteq \ \mathbb { R } ^ { n }$ is a one-dimensional subspace of $\mathbb { R } ^ { n }$ . This means that a line is defined by a support point $\scriptstyle { \pmb x } _ { 0 }$ and a vector $b _ { 1 }$ that defines the direction. See Figure 2.13 for an illustration. 

- Two-dimensional affine subspaces of $\mathbb { R } ^ { n }$ are called planes. The parametric equation for planes is $\pmb { y } = \pmb { x } _ { 0 } + \lambda _ { 1 } \pmb { b } _ { 1 } + \lambda _ { 2 } \pmb { b } _ { 2 }$ , where $\lambda _ { 1 } , \lambda _ { 2 } \in \mathbb { R }$ and $U = \operatorname { s p a n } [ b _ { 1 } , b _ { 2 } ] \subseteq \mathbb { R } ^ { n }$ . This means that a plane is defined by a support point $\boldsymbol{x}_0$ and two linearly independent vectors $b _ { 1 } , b _ { 2 }$ that span the direction space. 

- In $\mathbb { R } ^ { n }$ , the $( n - 1 )$ -dimensional affine subspaces are called hyperplanes, and the corresponding parametric equation is $\begin{array} { r } { \pmb { y } = \pmb { x } _ { 0 } + \sum _ { i = 1 } ^ { n - 1 } \lambda _ { i } \pmb { b } _ { i } } \end{array}$ where $b _ { 1 } , \ldots , b _ { n - 1 }$ form a basis of an $( n - 1 )$-dimensional subspace $U$ of $\mathbb { R } ^ { n }$ . This means that a hyperplane is defined by a support point $\boldsymbol{x}_0$ and $( n - 1 )$ linearly independent vectors $b _ { 1 } , \ldots , b _ { n - 1 }$ that span the direction space. In $\mathbb { R } ^ { 2 }$ , a line is also a hyperplane. In $\mathbb { R } ^ { 3 }$ , a plane is also a hyperplane. 

![Figure 2.13: Affine line](<Images/02_Linear_Algebra_image_018.jpg>)

Figure 2.13 Lines are affine subspaces. Vectors $\boldsymbol{y}$ on a line $\boldsymbol{x}_0+\lambda\boldsymbol{b}_1$ lie in an affine subspace $L$ with support point $\boldsymbol{x}_0$ and direction $\boldsymbol{b}_1$.

**Remark (Inhomogeneous systems of linear equations and affine subspaces).** For $\pmb { A } \in \mathbb { R } ^ { m \times n }$ and $\pmb { x } \in \mathbb { R } ^ { m }$ , the solution of the system of linear equations $A \lambda = x$ is either the empty set or an affine subspace of $\mathbb { R } ^ { n }$ of dimension $n - \operatorname { r k } ( A )$ . In particular, the solution of the linear equation $\lambda _ { 1 } b _ { 1 } + . . . + \lambda _ { n } b _ { n } = x$ , where $( \lambda _ { 1 } , \ldots , \lambda _ { n } ) \neq ( 0 , \ldots , 0 )$ , is a hyperplane in $\mathbb { R } ^ { n }$ 

In $\mathbb { R } ^ { n }$ , every k-dimensional affine subspace is the solution of an inhomogeneous system of linear equations $\mathbf { { A } } { \boldsymbol { x } } = { \boldsymbol { b } }$ , where $\boldsymbol{A}\in\mathbb{R}^{m\times n}$, $\boldsymbol{b}\in\mathbb{R}^{m}$ and $\operatorname{rk}(A)=n-k$ . Recall that for homogeneous equation systems $\pmb { A } \pmb { x } = \pmb { 0 }$ the solution was a vector subspace, which we can also think of as a special affine space with support point $\boldsymbol{x}_0=\boldsymbol{0}$ ◇ 

### 2.8.2 Affine Mappings

Similar to linear mappings between vector spaces, which we discussed in Section 2.7, we can define affine mappings between two affine spaces. Linear and affine mappings are closely related. Therefore, many properties that we already know from linear mappings, e.g., that the composition of linear mappings is a linear mapping, also hold for affine mappings. 

**Definition 2.26 (Affine Mapping).** For two vector spaces $V,W$, a linear mapping $\Phi : V \to W$ , and $\mathbf { \pmb { a } } \in W$ , the mapping 

$$
\phi : V \to W\tag{2.132}
$$

$$
\boldsymbol {x} \mapsto \boldsymbol {a} + \Phi (\boldsymbol {x})\tag{2.133}
$$

is an affine mapping from V to W. The vector a is called the translation vector of $\phi .$ 

- Every affine mapping $\phi : V \to W$ is also the composition of a linear mapping $\Phi : V \to W$ and a translation $\tau : W \to W$ in $W$, such that $\phi = \tau \circ \Phi$ . The mappings Φ and τ are uniquely determined. 

- The composition $\phi ^ { \prime } \circ \phi$ of affine mappings $\phi:V\to W$, $\phi^{\prime}:W\to X$ is affine. 

- If $\phi$ is bijective, affine mappings keep the geometric structure invariant. They then also preserve the dimension and parallelism. 

## 2.9 Further Reading

There are many resources for learning linear algebra, including the textbooks by Strang (2003), Golan (2007), Axler (2015), and Liesen and Mehrmann (2015). There are also several online resources that we mentioned in the introduction to this chapter. We only covered Gaussian elimination here, but there are many other approaches for solving systems of linear equations, and we refer to numerical linear algebra textbooks by Stoer and Burlirsch (2002), Golub and Van Loan (2012), and Horn and Johnson (2013) for an in-depth discussion. 

In this book, we distinguish between the topics of linear algebra (e.g., vectors, matrices, linear independence, basis) and topics related to the geometry of a vector space. In Chapter 3, we will introduce the inner product, which induces a norm. These concepts allow us to define angles, lengths and distances, which we will use for orthogonal projections. Projections turn out to be key in many machine learning algorithms, such as linear regression and principal component analysis, both of which we will cover in Chapters 9 and 10, respectively.

## Exercises

**2.1.** We consider $( \mathbb { R } \backslash \{ - 1 \} , \star )$ , where 

$$
a \star b := a b + a + b, \qquad a, b \in \mathbb {R} \backslash \{- 1 \}\tag{2.134}
$$

**(a)** Show that $( \mathbb { R } \backslash \{ - 1 \} , \star )$ is an Abelian group. 

**(b)** Solve 

$$
3 \star x \star x = 15
$$

in the Abelian group $( \mathbb { R } \backslash \{ - 1 \} , \star )$ , where ⋆ is defined in (2.134). 

**2.2.** Let n be in $\mathbb { N } \backslash \{ 0 \}$ . Let $k , x$ be in $\mathbb { Z }$. We define the congruence class $\bar { k }$ of the integer k as the set 

$$
\begin{array}{r l} & {\overline {{k}} = \{x \in \mathbb {Z} \mid x - k = 0 (\mathrm{mod} n) \}} \\ & {\quad = \{x \in \mathbb {Z} \mid \exists a \in \mathbb {Z} \colon (x - k = n \cdot a) \}.} \end{array}
$$

We now define $\mathbb { Z } / n \mathbb { Z }$ (sometimes written $\mathbb { Z } _ { n }$) as the set of all congruence classes modulo n. Euclidean division implies that this set is a finite set containing n elements: 

$$
\mathbb {Z} _ {n} = \{\overline {{0}}, \overline {{1}}, \dots , \overline {{n - 1}} \}
$$

For all ${ \overline { { a } } } , { \overline { { b } } } \in \mathbb { Z } _ { n }$ , we define 

$$
\overline {{a}} \oplus \overline {{b}} := \overline {{a + b}}
$$

**(a)** Show that $( \mathbb { Z } _ { n } , \oplus )$ is a group. Is it Abelian? 

**(b)** We now define another operation $\otimes$ for all $\bar{a}$ and $\bar{b}$ in $\mathbb { Z } _ { n }$ as 

$$
\overline {{a}} \otimes \overline {{b}} = \overline {{a \times b}},\tag{2.135}
$$

where $a \times b$ represents the usual multiplication in $\mathbb { Z }$ 

Let $n=5$ . Draw the times table of the elements of $\mathbb { Z } _ { 5 } \backslash \{ \overline { { 0 } } \}$ under $\otimes$, i.e., calculate the products $\overline { { a } } \otimes \overline { { b } }$ for all $\bar{a}$ and $\bar{b}$ in $\mathbb { Z } _ { 5 } \backslash \{ \overline { { 0 } } \}$ 

Hence, show that $\mathbb { Z } _ { 5 } \backslash \{ \overline { { 0 } } \}$ is closed under $\otimes$ and possesses a neutral element for $\otimes$. Display the inverse of all elements in $\mathbb { Z } _ { 5 } \backslash \{ \overline { { 0 } } \}$ under $\otimes$. Conclude that $( \mathbb { Z } _ { 5 } \backslash \{ \overline { { 0 } } \} , \otimes )$ is an Abelian group. 

**(c)** Show that $( \mathbb { Z } _ { 8 } \backslash \{ \overline { { 0 } } \} , \otimes )$ is not a group. 

**(d)** We recall that the Bézout theorem states that two integers a and b are relatively prime $( \mathrm { i . e . , } g c d ( a , b ) = 1 )$ if and only if there exist two integers u and v such that au + bv = 1. Show that $( \mathbb { Z } _ { n } \backslash \{ \overline { { 0 } } \} , \otimes )$ is a group if and only if $n\in\mathbb{N}\backslash\{0\}$ is prime. 

**2.3.** Consider the set $\mathcal { G }$ of $3 \times 3$ matrices defined as follows: 

$$
\mathcal {G} = \left\{\left[ \begin{array}{c c c} 1 & x & z \\ 0 & 1 & y \\ 0 & 0 & 1 \end{array} \right] \in \mathbb {R} ^ {3 \times 3}   \middle |   x, y, z \in \mathbb {R} \right\}
$$

We define · as the standard matrix multiplication. 

Is $( { \mathcal { G } } , \cdot )$ a group? If yes, is it Abelian? Justify your answer. 

**2.4.** Compute the following matrix products, if possible: 

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

**2.5.** Find the set S of all solutions in x of the following inhomogeneous linear systems $\mathbf { { A } } \mathbf { { x } } = \mathbf { { b } } ,$ where A and b are defined as follows: 

**(a)**

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c} 1 & 1 & - 1 & - 1 \\ 2 & 5 & - 7 & - 5 \\ 2 & - 1 & 1 & 3 \\ 5 & 2 & - 4 & 2 \end{array} \right], \quad \boldsymbol {b} = \left[ \begin{array}{c} 1 \\ - 2 \\ 4 \\ 6 \end{array} \right]
$$

**(b)**

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c c} 1 & - 1 & 0 & 0 & 1 \\ 1 & 1 & 0 & - 3 & 0 \\ 2 & - 1 & 0 & 1 & - 1 \\ - 1 & 2 & 0 & - 2 & - 1 \end{array} \right], \quad \boldsymbol {b} = \left[ \begin{array}{c} 3 \\ 6 \\ 5 \\ - 1 \end{array} \right]
$$

**2.6.** Using Gaussian elimination, find all solutions of the inhomogeneous equation system $\mathbf { A } { \boldsymbol { \mathbf { \mathit { x } } } } = \mathbf { \mathit { b } }$ with 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c c c} 0 & 1 & 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1 & 1 & 0 \\ 0 & 1 & 0 & 0 & 0 & 1 \end{array} \right], \quad \boldsymbol {b} = \left[ \begin{array}{c} 2 \\ - 1 \\ 1 \end{array} \right].
$$

**2.7.** Find all solutions in $\pmb { x } = \left[ \begin{array} { l } { x _ { 1 } } \\ { x _ { 2 } } \\ { x _ { 3 } } \end{array} \right] \in \mathbb { R } ^ { 3 }$ of the equation system $A\boldsymbol{x}=12\boldsymbol{x}$, where 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 6 & 4 & 3 \\ 6 & 0 & 9 \\ 0 & 8 & 0 \end{array} \right]
$$

and $\textstyle \sum _ { i = 1 } ^ { 3 } x _ { i } = 1$ 

**2.8.** Determine the inverses of the following matrices if possible:

**(a)**

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 2 & 3 & 4 \\ 3 & 4 & 5 \\ 4 & 5 & 6 \end{array} \right]
$$

**(b)**

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c} 1 & 0 & 1 & 0 \\ 0 & 1 & 1 & 0 \\ 1 & 1 & 0 & 1 \\ 1 & 1 & 1 & 0 \end{array} \right]
$$

**2.9.** Which of the following sets are subspaces of $\mathbb { R } ^ { 3 }$? 

**(a)** $A = \{ ( \lambda , \lambda + \mu ^ { 3 } , \lambda - \mu ^ { 3 } ) \mid \lambda , \mu \in \mathbb { R } \}$ 

**(b)** $B = \{ ( \lambda ^ { 2 } , - \lambda ^ { 2 } , 0 ) \mid \lambda \in \mathbb { R } \}$ 

**(c)** Let $\gamma\in\mathbb{R}$. 

$$
C = \left\{\left(\xi_ {1}, \xi_ {2}, \xi_ {3}\right) \in \mathbb {R} ^ {3} \mid \xi_ {1} - 2 \xi_ {2} + 3 \xi_ {3} = \gamma \right\}
$$

**(d)** $D = \{ ( \xi _ { 1 } , \xi _ { 2 } , \xi _ { 3 } ) \in \mathbb { R } ^ { 3 } \mid \xi _ { 2 } \in \mathbb { Z } \}$ 

**2.10.** Are the following sets of vectors linearly independent?

**(a)**

$$
\boldsymbol {x} _ {1} = \left[ \begin{array}{l} 2 \\ - 1 \\ 3 \end{array} \right], \quad \boldsymbol {x} _ {2} = \left[ \begin{array}{l} 1 \\ 1 \\ - 2 \end{array} \right], \quad \boldsymbol {x} _ {3} = \left[ \begin{array}{l} 3 \\ - 3 \\ 8 \end{array} \right]
$$

**(b)**

$$
\boldsymbol {x} _ {1} = \left[ \begin{array}{l} 1 \\ 2 \\ 1 \\ 0 \\ 0 \end{array} \right], \quad \boldsymbol {x} _ {2} = \left[ \begin{array}{l} 1 \\ 1 \\ 0 \\ 1 \\ 1 \end{array} \right], \quad \boldsymbol {x} _ {3} = \left[ \begin{array}{l} 1 \\ 0 \\ 0 \\ 1 \\ 1 \end{array} \right]
$$

**2.11.** Write 

$$
\boldsymbol {y} = \left[ \begin{array}{c} 1 \\ - 2 \\ 5 \end{array} \right]
$$

as linear combination of 

$$
\boldsymbol {x} _ {1} = \left[ \begin{array}{l} 1 \\ 1 \\ 1 \end{array} \right], \quad \boldsymbol {x} _ {2} = \left[ \begin{array}{l} 1 \\ 2 \\ 3 \end{array} \right], \quad \boldsymbol {x} _ {3} = \left[ \begin{array}{l} 2 \\ - 1 \\ 1 \end{array} \right]
$$

**2.12.** Consider two subspaces of $\mathbb { R } ^ { 4 }$ : 

$$
U_1=\operatorname{span}\left[\begin{bmatrix}1\\1\\-3\\1\end{bmatrix},\begin{bmatrix}2\\-1\\0\\-1\end{bmatrix},\begin{bmatrix}-1\\1\\-1\\1\end{bmatrix}\right],
\qquad
U_2=\operatorname{span}\left[\begin{bmatrix}-1\\-2\\2\\1\end{bmatrix},\begin{bmatrix}2\\-2\\0\\0\end{bmatrix},\begin{bmatrix}-3\\6\\-2\\-1\end{bmatrix}\right].
$$

Determine a basis of $U _ { 1 } \cap U _ { 2 }$ 

**2.13.** Consider two subspaces $U _ { 1 }$ and $U _ { 2 }$ , where $U _ { 1 }$ is the solution space of the homogeneous equation system $\pmb { A } _ { 1 } \pmb { x } = \mathbf { 0 }$ and $U _ { 2 }$ is the solution space of the homogeneous equation system $\pmb { A } _ { 2 } \pmb { x } = \mathbf { 0 }$ with 

$$
\boldsymbol {A} _ {1} = \left[ \begin{array}{c c c} 1 & 0 & 1 \\ 1 & - 2 & - 1 \\ 2 & 1 & 3 \\ 1 & 0 & 1 \end{array} \right], \quad \boldsymbol {A} _ {2} = \left[ \begin{array}{c c c} 3 & - 3 & 0 \\ 1 & 2 & 3 \\ 7 & - 5 & 2 \\ 3 & - 1 & 2 \end{array} \right].
$$

**(a)** Determine the dimension of $U _ { 1 } , U _ { 2 }$ 

**(b)** Determine bases of $U _ { 1 }$ and $U _ { 2 }$ . 

**(c)** Determine a basis of $U _ { 1 } \cap U _ { 2 }$ 

**2.14.** Consider two subspaces $U _ { 1 }$ and $U _ { 2 }$ , where $U _ { 1 }$ is spanned by the columns of $\pmb { A } _ { 1 }$ and $U _ { 2 }$ is spanned by the columns of $A _ { 2 }$ with 

$$
\boldsymbol {A} _ {1} = \left[ \begin{array}{c c c} 1 & 0 & 1 \\ 1 & - 2 & - 1 \\ 2 & 1 & 3 \\ 1 & 0 & 1 \end{array} \right], \quad \boldsymbol {A} _ {2} = \left[ \begin{array}{c c c} 3 & - 3 & 0 \\ 1 & 2 & 3 \\ 7 & - 5 & 2 \\ 3 & - 1 & 2 \end{array} \right].
$$

**(a)** Determine the dimension of $U _ { 1 } , U _ { 2 }$ 

**(b)** Determine bases of $U _ { 1 }$ and $U _ { 2 }$ 

**(c)** Determine a basis of $U _ { 1 } \cap U _ { 2 }$ 

**2.15.** Let $F = \{ ( x , y , z ) \in \mathbb { R } ^ { 3 } \mid x + y - z = 0 \}$ and $G = \{ ( a - b , a + b , a - 3 b ) \mid a , b \in \mathbb { R } \}$ 

**(a)** Show that F and G are subspaces of $\mathbb { R } ^ { 3 }$ 

**(b)** Calculate $F \cap G$ without resorting to any basis vector. 

**(c)** Find one basis for F and one for $G$, calculate $F \cap G$ using the basis vectors previously found and check your result with the previous question. 

**2.16.** Are the following mappings linear? 

**(a)** Let $a , b \in \mathbb { R } .$ 

$$
\begin{array}{c} \Phi : L ^ {1} ([ a, b ]) \to \mathbb {R} \\ f \mapsto \Phi (f) = \int_ {a} ^ {b} f (x) d x  , \end{array}
$$

where $L ^ { 1 } ( [ a , b ] )$ denotes the set of integrable functions on $[ a , b ]$ 

**(b)**

$$
\begin{array}{c} \Phi : C ^ {1} \to C ^ {0} \\ f \mapsto \Phi (f) = f ^ {\prime}, \end{array}
$$

where for $k \geqslant 1 , C ^ { k }$ denotes the set of $k$ times continuously differentiable functions, and $C ^ { 0 }$ denotes the set of continuous functions. 

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

**(e)** Let θ be in $[ 0 , 2 \pi [$ and 

$$
\Phi : \mathbb {R} ^ {2} \to \mathbb {R} ^ {2}
$$

$$
\pmb {x} \mapsto \left[ \begin{array}{c c} \cos (\theta) & \sin (\theta) \\ - \sin (\theta) & \cos (\theta) \end{array} \right] \pmb {x}
$$

**2.17.** Consider the linear mapping 

$$
\Phi : \mathbb {R} ^ {3} \to \mathbb {R} ^ {4}
$$

$$
\Phi \left(\left[ \begin{array}{c} x _ {1} \\ x _ {2} \\ x _ {3} \end{array} \right]\right) = \left[ \begin{array}{c} 3 x _ {1} + 2 x _ {2} + x _ {3} \\ x _ {1} + x _ {2} + x _ {3} \\ x _ {1} - 3 x _ {2} \\ 2 x _ {1} + 3 x _ {2} + x _ {3} \end{array} \right]
$$

- Find the transformation matrix $A _ { \Phi }$. 

- Determine $\operatorname{rk}(A_{\Phi})$. 

- Compute the kernel and image of Φ. What are $\dim(\ker(\Phi))$ and $\dim(\operatorname{Im}(\Phi))$? 

**2.18.** Let $E$ be a vector space. Let $f$ and $g$ be two automorphisms on $E$ such that $f\circ g=\operatorname{id}_E$ (i.e., $f\circ g$ is the identity mapping $\operatorname{id}_E$). Show that $\ker(f)=\ker(g\circ f)$, $\operatorname{Im}(g)=\operatorname{Im}(g\circ f)$ and that $\ker(f)\cap\operatorname{Im}(g)=\{\boldsymbol{0}_E\}$.

**2.19.** Consider an endomorphism $\Phi:\mathbb{R}^{3}\to\mathbb{R}^{3}$ whose transformation matrix (with respect to the standard basis in $\mathbb { R } ^ { 3 }$) is 

$$
\boldsymbol {A} _ {\Phi} = \left[ \begin{array}{c c c} 1 & 1 & 0 \\ 1 & - 1 & 0 \\ 1 & 1 & 1 \end{array} \right].
$$

**(a)** Determine ker(Φ) and Im(Φ). 

**(b)** Determine the transformation matrix $\tilde { \mathbf { A } } _ { \Phi }$ with respect to the basis 

$$
B = (\left[ \begin{array}{c} 1 \\ 1 \\ 1 \end{array} \right], \left[ \begin{array}{c} 1 \\ 2 \\ 1 \end{array} \right], \left[ \begin{array}{c} 1 \\ 0 \\ 0 \end{array} \right]),
$$

i.e., perform a basis change toward the new basis $B$. 

**2.20.** Let us consider $b _ { 1 } , b _ { 2 } , b _ { 1 } ^ { \prime } , b _ { 2 } ^ { \prime }$ , 4 vectors of $\mathbb { R } ^ { 2 }$ expressed in the standard basis of $\mathbb { R } ^ { 2 }$ as 

$$
\boldsymbol {b} _ {1} = \left[ \begin{array}{c} 2 \\ 1 \end{array} \right], \quad \boldsymbol {b} _ {2} = \left[ \begin{array}{c} - 1 \\ - 1 \end{array} \right], \quad \boldsymbol {b} _ {1} ^ {\prime} = \left[ \begin{array}{c} 2 \\ - 2 \end{array} \right], \quad \boldsymbol {b} _ {2} ^ {\prime} = \left[ \begin{array}{c} 1 \\ 1 \end{array} \right]
$$

and let us define two ordered bases $B = ( b _ { 1 } , b _ { 2 } )$ and $B ^ { \prime } = ( b _ { 1 } ^ { \prime } , b _ { 2 } ^ { \prime } )$ of $\textstyle \mathbb { R } ^ { 2 }$ . 

**(a)** Show that B and $B ^ { \prime }$ are two bases of $\mathbb { R } ^ { 2 }$ and draw those basis vectors. 

**(b)** Compute the matrix $P _ { 1 }$ that performs a basis change from $B ^ { \prime }$ to $B$. 

**(c)** We consider $c_1,c_2,c_3$ , three vectors of $\mathbb { R } ^ { 3 }$ defined in the standard basis of $\mathbb { R } ^ { 3 }$ as 

$$
\boldsymbol {c} _ {1} = \left[ \begin{array}{l} 1 \\ 2 \\ - 1 \end{array} \right], \quad \boldsymbol {c} _ {2} = \left[ \begin{array}{l} 0 \\ - 1 \\ 2 \end{array} \right], \quad \boldsymbol {c} _ {3} = \left[ \begin{array}{l} 1 \\ 0 \\ - 1 \end{array} \right]
$$

and we define $C = ( c _ { 1 } , c _ { 2 } , c _ { 3 } )$ 

**(i)** Show that C is a basis of $\mathbb { R } ^ { 3 }$ , e.g., by using determinants (see Section 4.1). 

**(ii)** Let us call $C ^ { \prime } = ( c _ { 1 } ^ { \prime } , c _ { 2 } ^ { \prime } , c _ { 3 } ^ { \prime } )$ the standard basis of $\mathbb { R } ^ { 3 }$ . Determine the matrix $\scriptstyle P _ { 2 }$ that performs the basis change from $C$ to $C ^ { \prime }$ . 

**(d)** We consider a homomorphism $\Phi : \mathbb { R } ^ { 2 } \longrightarrow \mathbb { R } ^ { 3 }$ , such that 

$$
\begin{array}{r c l} \Phi (\boldsymbol {b} _ {1} + \boldsymbol {b} _ {2}) & = & \boldsymbol {c} _ {2} + \boldsymbol {c} _ {3} \\ \Phi (\boldsymbol {b} _ {1} - \boldsymbol {b} _ {2}) & = & 2 \boldsymbol {c} _ {1} - \boldsymbol {c} _ {2} + 3 \boldsymbol {c} _ {3} \end{array}
$$

where $B = ( b _ { 1 } , b _ { 2 } )$ and $C = ( c _ { 1 } , c _ { 2 } , c _ { 3 } )$ are ordered bases of $\textstyle \mathbb { R } ^ { 2 }$ and $\mathbb { R } ^ { 3 }$ , respectively. 

Determine the transformation matrix $A _ { \Phi }$ of Φ with respect to the ordered bases $B$ and $C$. 

**(e)** Determine $A^{\prime}$, the transformation matrix of Φ with respect to the bases $B ^ { \prime }$ and $C ^ { \prime }$ . 

**(f)** Let us consider the vector $\pmb { x } \in \mathbb { R } ^ { 2 }$ whose coordinates in $B ^ { \prime }$ are $[ 2 , 3 ] ^ { \top }$. In other words, ${ \pmb x } = 2 b _ { 1 } ^ { \prime } + 3 b _ { 2 } ^ { \prime }$ 

**(i)** Calculate the coordinates of x in $B$. 

**(ii)** Based on that, compute the coordinates of $\Phi ( { \pmb x } )$ expressed in $C$. 

**(iii)** Then, write $\Phi ( { \pmb x } )$ in terms of $\mathbf { } c _ { 1 } ^ { \prime } , \mathbf { } c _ { 2 } ^ { \prime } , c _ { 3 } ^ { \prime }$ 

**(iv)** Use the representation of x in $B ^ { \prime }$ and the matrix $A ^ { \prime }$ to find this result directly.

[^array-vector-operations]: Be careful to check whether array operations actually perform vector operations when implementing on a computer.
