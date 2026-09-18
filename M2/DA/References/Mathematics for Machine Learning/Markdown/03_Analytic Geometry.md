# 3 Analytic Geometry

![image](<Images/03_Analytic_Geometry_image_001.jpg>)

In Chapter 2, we studied vectors, vector spaces, and linear mappings at a general but abstract level. In this chapter, we will add some geometric interpretation and intuition to all of these concepts. In particular, we will look at geometric vectors and compute their lengths and distances or angles between two vectors. To be able to do this, we equip the vector space with an inner product that induces the geometry of the vector space. Inner products and their corresponding norms and metrics capture the intuitive notions of similarity and distances, which we use to develop the support vector machine in Chapter 12. We will then use the concepts of lengths and angles between vectors to discuss orthogonal projections, which will play a central role when we discuss principal component analysis in Chapter 10 and regression via maximum likelihood estimation in Chapter 9. Figure 3.1 gives an overview of how concepts in this chapter are related and how they are connected to other chapters of the book. 

Figure 3.1 A mind map of the concepts introduced in this chapter, along with when they are used in other parts of the book. 

![image](<Images/03_Analytic_Geometry_image_002.jpg>)

This material is published by Cambridge University Press as Mathematics for Machine Learning by Marc Peter Deisenroth, A. Aldo Faisal, and Cheng Soon Ong (2020). This version is free to view and download for personal use only. Not for re-distribution, re-sale, or use in derivative works. © by M. P. Deisenroth, A. A. Faisal, and C. S. Ong, 2024. https://mml-book.com.

## 3.1 Norms

When we think of geometric vectors, i.e., directed line segments that start at the origin, then intuitively the length of a vector is the distance of the “end” of this directed line segment from the origin. In the following, we will discuss the notion of the length of vectors using the concept of a norm. 

**Definition 3.1 (Norm).** A norm on a vector space V is a function 

$$
\| \cdot \|: V \to \mathbb {R},\tag{3.1}
$$

$$
\boldsymbol {x} \mapsto \| \boldsymbol {x} \|,\tag{3.2}
$$

which assigns each vector x its length $\| \pmb { x } \| \in \mathbb { R }$ , such that for all $\lambda \in \mathbb { R }$ and $\boldsymbol{x},\boldsymbol{y}\in V$ the following hold: 

- **Absolutely homogeneous:** $\| \lambda \pmb { x } \| = | \lambda | \| \pmb { x } \|$ 

- **Triangle inequality:** $\| { \pmb x } + { \pmb y } \| \leqslant \| { \pmb x } \| + \| { \pmb y } \|$ 

- **Positive definite:** $\| \pmb { x } \| \geqslant 0$ and $\| { \pmb x } \| = 0 \iff { \pmb x } = \mathbf { 0 }$ 

In geometric terms, the triangle inequality states that for any triangle, the sum of the lengths of any two sides must be greater than or equal to the length of the remaining side; see Figure 3.2 for an illustration. Definition 3.1 is in terms of a general vector space V (Section 2.4), but in this book we will only consider a finite-dimensional vector space $\mathbb { R } ^ { n }$. Recall that for a vector $\pmb { x } \in \mathbb { R } ^ { n }$ we denote the elements of the vector using a subscript, that is, $x _ { i }$ is the $i ^ { \mathrm { t h } }$ element of the vector x. 

![Figure 3.2: Triangle inequality](<Images/03_Analytic_Geometry_image_004.jpg>)

Figure 3.2 Triangle inequality.

**Example 3.1 (Manhattan Norm)**

The Manhattan norm on $\mathbb { R } ^ { n }$ is defined for $\pmb { x } \in \mathbb { R } ^ { n }$ as 

$$
\left\| \boldsymbol {x} \right\| _ {1} := \sum_ {i = 1} ^ {n} \left| x _ {i} \right|,\tag{3.3}
$$

where $| \cdot |$ is the absolute value. The left panel of Figure 3.3 shows all vectors $\boldsymbol{x}\in\mathbb{R}^{2}$ with $\| \pmb { x } \| _ { 1 } = 1$ . The Manhattan norm is also called $\ell_1$ norm. 

**Example 3.2 (Euclidean Norm)**

The Euclidean norm of $\pmb { x } \in \mathbb { R } ^ { n }$ is defined as 

$$
\| \boldsymbol {x} \| _ {2} := \sqrt {\sum_ {i = 1} ^ {n} x _ {i} ^ {2}} = \sqrt {\boldsymbol {x} ^ {\top} \boldsymbol {x}}\tag{3.4}
$$

and computes the Euclidean distance of x from the origin. The right panel of Figure 3.3 shows all vectors $\boldsymbol{x}\in\mathbb{R}^{2}$ with $\| \pmb { x } \| _ { 2 } = 1$ . The Euclidean norm is also called $\ell _ { 2 }$ norm. 

![image](<Images/03_Analytic_Geometry_image_003.jpg>)

Figure 3.3 For different norms, the red lines indicate the set of vectors with norm 1. Left: Manhattan norm; Right: Euclidean distance.

**Remark.** Throughout this book, we will use the Euclidean norm (3.4) by default if not stated otherwise. ◇ 

## 3.2 Inner Products

Inner products allow for the introduction of intuitive geometrical concepts, such as the length of a vector and the angle or distance between two vectors. A major purpose of inner products is to determine whether vectors are orthogonal to each other. 

### 3.2.1 Dot Product

We may already be familiar with a particular type of inner product, the scalar product/dot product in $\mathbb{R}^{n}$, which is given by 

$$
\boldsymbol {x} ^ {\top} \boldsymbol {y} = \sum_ {i = 1} ^ {n} x _ {i} y _ {i}.\tag{3.5}
$$

We will refer to this particular inner product as the dot product in this book. However, inner products are more general concepts with specific properties, which we will now introduce.

### 3.2.2 General Inner Products

Recall the linear mapping from Section 2.7, where we can rearrange the mapping with respect to addition and multiplication with a scalar. A bilinear mapping Ω is a mapping with two arguments, and it is linear in each argument, i.e., when we look at a vector space V then it holds that for all $\boldsymbol{x},\boldsymbol{y},\boldsymbol{z}\in V$, $\lambda,\psi\in\mathbb{R}$ that 

$$
\Omega (\lambda \boldsymbol {x} + \psi \boldsymbol {y}, \boldsymbol {z}) = \lambda \Omega (\boldsymbol {x}, \boldsymbol {z}) + \psi \Omega (\boldsymbol {y}, \boldsymbol {z})\tag{3.6}
$$

$$
\Omega (\boldsymbol {x}, \lambda \boldsymbol {y} + \psi \boldsymbol {z}) = \lambda \Omega (\boldsymbol {x}, \boldsymbol {y}) + \psi \Omega (\boldsymbol {x}, \boldsymbol {z}).\tag{3.7}
$$

Here, (3.6) asserts that Ω is linear in the first argument, and (3.7) asserts that Ω is linear in the second argument (see also (2.87)). 

**Definition 3.2.** Let V be a vector space and $\Omega:V\times V\to\mathbb{R}$ be a bilinear mapping that takes two vectors and maps them onto a real number. Then 

- Ω is called symmetric if $\Omega ( x , y ) = \Omega ( y , x )$ for all $x,y\in V$, i.e., the order of the arguments does not matter. 

- Ω is called positive definite if 

$$
\forall \boldsymbol {x} \in V \backslash \{\boldsymbol {0} \}: \Omega (\boldsymbol {x}, \boldsymbol {x}) > 0, \quad \Omega (\boldsymbol {0}, \boldsymbol {0}) = 0.\tag{3.8}
$$

**Definition 3.3.** Let $V$ be a vector space and $\Omega:V\times V\to\mathbb{R}$ be a bilinear mapping that takes two vectors and maps them onto a real number. Then 

- A positive definite, symmetric bilinear mapping $\Omega:V\times V\to\mathbb{R}$ is called an inner product on V. We typically write $\langle { \pmb x } , { \pmb y } \rangle$ instead of $\Omega ( { \pmb x } , { \pmb y } )$ . 

- The pair $\left( V , \langle \cdot , \cdot \rangle \right)$ is called an inner product space or (real) vector space with inner product. If we use the dot product defined in (3.5), we call $\left( V , \langle \cdot , \cdot \rangle \right)$ a Euclidean vector space. 

We will refer to these spaces as inner product spaces in this book. 

**Example 3.3 (Inner Product That Is Not the Dot Product)**

Consider $V = \mathbb { R } ^ { 2 }$ . If we define 

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle := x _ {1} y _ {1} - (x _ {1} y _ {2} + x _ {2} y _ {1}) + 2 x _ {2} y _ {2}\tag{3.9}
$$

then $\langle \cdot , \cdot \rangle$ is an inner product but different from the dot product. The proof will be an exercise. 

### 3.2.3 Symmetric, Positive Definite Matrices

Symmetric, positive definite matrices play an important role in machine learning, and they are defined via the inner product. In Section 4.3, we will return to symmetric, positive definite matrices in the context of matrix decompositions. The idea of symmetric positive semidefinite matrices is key in the definition of kernels (Section 12.4). 

Consider an n-dimensional vector space V with an inner product $\langle\cdot,\cdot\rangle:V\times V\to\mathbb{R}$ (see Definition 3.3) and an ordered basis $B = ( b _ { 1 } , \ldots , b _ { n } )$ of $V$. Recall from Section 2.6.1 that any vectors $\boldsymbol{x},\boldsymbol{y}\in V$ can be written as linear combinations of the basis vectors so that $\begin{array} { r } { \pmb { x } = \sum _ { i = 1 } ^ { n } { \psi _ { i } \pmb { b } _ { i } } \in V } \end{array}$ and $\begin{array} { r } { \pmb { y } = \sum _ { j = 1 } ^ { n } \lambda _ { j } \pmb { b } _ { j } \in V } \end{array}$ for suitable $\psi _ { i } , \lambda _ { j } \in \mathbb { R }$ . Due to the bilinearity of the inner product, it holds for all $\mathbf { { \pmb { x } } } , \mathbf { { \pmb { y } } } \in V$ that 

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle = \left\langle \sum_ {i = 1} ^ {n} \psi_ {i} \boldsymbol {b} _ {i}, \sum_ {j = 1} ^ {n} \lambda_ {j} \boldsymbol {b} _ {j} \right\rangle = \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \psi_ {i} \left\langle \boldsymbol {b} _ {i}, \boldsymbol {b} _ {j} \right\rangle \lambda_ {j} = \hat {\boldsymbol {x}} ^ {\top} \boldsymbol {A} \hat {\boldsymbol {y}},\tag{3.10}
$$

where $A _ { i j } : = \langle b _ { i } , b _ { j } \rangle$ and $\hat { \pmb x } , \hat { \pmb y }$ are the coordinates of x and y with respect to the basis B. This implies that the inner product $\langle \cdot , \cdot \rangle$ is uniquely determined through A. The symmetry of the inner product also means that A is symmetric. Furthermore, the positive definiteness of the inner product implies that 

$$
\forall \boldsymbol {x} \in V \backslash \{\mathbf {0} \}: \boldsymbol {x} ^ {\top} \boldsymbol {A} \boldsymbol {x} > 0.\tag{3.11}
$$

**Definition 3.4 (Symmetric, Positive Definite Matrix).** A symmetric matrix $\pmb { A } \in \mathbb { R } ^ { n \times n }$ that satisfies (3.11) is called symmetric, positive definite, or just positive definite. If only ⩾ holds in (3.11), then A is called symmetric, positive semidefinite. 

**Example 3.4 (Symmetric, Positive Definite Matrices)**

Consider the matrices 

$$
\boldsymbol {A} _ {1} = \left[ \begin{array}{c c} 9 & 6 \\ 6 & 5 \end{array} \right], \quad \boldsymbol {A} _ {2} = \left[ \begin{array}{c c} 9 & 6 \\ 6 & 3 \end{array} \right].\tag{3.12}
$$

$\pmb { A } _ { 1 }$ is positive definite because it is symmetric and 

$$
\pmb {x} ^ {\top} \pmb {A} _ {1} \pmb {x} = \left[ \begin{array}{c c} x _ {1} & x _ {2} \end{array} \right] \left[ \begin{array}{c c} 9 & 6 \\ 6 & 5 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \end{array} \right]\tag{3.13a}
$$

$$
= 9 x _ {1} ^ {2} + 12 x _ {1} x _ {2} + 5 x _ {2} ^ {2} = (3 x _ {1} + 2 x _ {2}) ^ {2} + x _ {2} ^ {2} > 0\tag{3.13b}
$$

for all ${ \pmb x } \in V \backslash \{ { \bf 0 } \}$ . In contrast, $A _ { 2 }$ is symmetric but not positive definite because $x ^ { \top } A _ { 2 } x = 9 x _ { 1 } ^ { 2 } + 12 x _ { 1 } x _ { 2 } + 3 x _ { 2 } ^ { 2 } = ( 3 x _ { 1 } + 2 x _ { 2 } ) ^ { 2 } - x _ { 2 } ^ { 2 }$ can be less than 0, e.g., for $\pmb { x } = [ 2 , - 3 ] ^ { \top }$ 

If $A \in \mathbb { R } ^ { n \times n }$ is symmetric, positive definite, then 

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle = \hat {\boldsymbol {x}} ^ {\top} \boldsymbol {A} \hat {\boldsymbol {y}}\tag{3.14}
$$

defines an inner product with respect to an ordered basis $B$, where $\hat{\boldsymbol{x}}$ and $\hat{\boldsymbol{y}}$ are the coordinate representations of $\boldsymbol{x},\boldsymbol{y}\in V$ with respect to B. 

**Theorem 3.5.** For a real-valued, finite-dimensional vector space $V$ and an ordered basis B of V, it holds that $\langle\cdot,\cdot\rangle:V\times V\to\mathbb{R}$ is an inner product if and only if there exists a symmetric, positive definite matrix $A \in \mathbb { R } ^ { n \times n }$ with 

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle = \hat {\boldsymbol {x}} ^ {\top} \boldsymbol {A} \hat {\boldsymbol {y}}.\tag{3.15}
$$

The following properties hold if $\pmb { A } \in \mathbb { R } ^ { n \times n }$ is symmetric and positive definite: 

- The null space (kernel) of A consists only of 0 because ${ \pmb x } ^ { \top } { \pmb A } { \pmb x } > 0$ for all $\mathbf { \boldsymbol { x } } \neq \mathbf { \boldsymbol { 0 } }$ . This implies that $A\boldsymbol{x}\neq\boldsymbol{0}$ if $\mathbf { \boldsymbol { x } } \neq \mathbf { 0 }$ 

- The diagonal elements $a _ { i i }$ of A are positive because $a _ { i i } = e _ { i } ^ { \top } A e _ { i } > 0$ , where $e _ { i }$ is the ith vector of the standard basis in $\mathbb { R } ^ { n }$ 

## 3.3 Lengths and Distances

In Section 3.1, we already discussed norms that we can use to compute the length of a vector. Inner products and norms are closely related in the sense that any inner product induces a norm 

$$
\| \boldsymbol {x} \| := \sqrt {\langle \boldsymbol {x} , \boldsymbol {x} \rangle}\tag{3.16}
$$

in a natural way, such that we can compute lengths of vectors using the inner product. However, not every norm is induced by an inner product. The Manhattan norm (3.3) is an example of a norm without a corresponding inner product. In the following, we will focus on norms that are induced by inner products and introduce geometric concepts, such as lengths, distances, and angles. 

**Remark (Cauchy-Schwarz Inequality).** For an inner product vector space $\left( V , \langle \cdot , \cdot \rangle \right)$ the induced norm $\| \cdot \|$ satisfies the Cauchy-Schwarz inequality 

$$
| \langle \boldsymbol {x}, \boldsymbol {y} \rangle | \leqslant \| \boldsymbol {x} \| \| \boldsymbol {y} \|.\tag{3.17}
$$

**Example 3.5 (Lengths of Vectors Using Inner Products)**

In geometry, we are often interested in lengths of vectors. We can now use an inner product to compute them using (3.16). Let us take $\pmb { x } = [ 1 , 1 ] ^ { \top } \in$ $\mathbb { R } ^ { 2 }$ . If we use the dot product as the inner product, with (3.16) we obtain 

$$
\| \boldsymbol {x} \| = \sqrt {\boldsymbol {x} ^ {\top} \boldsymbol {x}} = \sqrt {1 ^ {2} + 1 ^ {2}} = \sqrt {2}\tag{3.18}
$$

as the length of x. Let us now choose a different inner product: 

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle := \boldsymbol {x} ^ {\top} \left[ \begin{array}{c c} 1 & - \frac {1}{2} \\ - \frac {1}{2} & 1 \end{array} \right] \boldsymbol {y} = x _ {1} y _ {1} - \frac {1}{2} (x _ {1} y _ {2} + x _ {2} y _ {1}) + x _ {2} y _ {2}  .\tag{3.19}
$$

If we compute the norm of a vector, then this inner product returns smaller values than the dot product if $x _ { 1 }$ and $x _ { 2 }$ have the same sign (and $x_1x_2>0$); otherwise, it returns greater values than the dot product. With this inner product, we obtain 

$$
\langle \boldsymbol {x}, \boldsymbol {x} \rangle = x _ {1} ^ {2} - x _ {1} x _ {2} + x _ {2} ^ {2} = 1 - 1 + 1 = 1 \implies \| \boldsymbol {x} \| = \sqrt {1} = 1,\tag{3.20}
$$

such that x is “shorter” with this inner product than with the dot product. 

**Definition 3.6 (Distance and Metric).** Consider an inner product space $\left( V , \langle \cdot , \cdot \rangle \right)$ . Then 

$$
d (\boldsymbol {x}, \boldsymbol {y}) := \| \boldsymbol {x} - \boldsymbol {y} \| = \sqrt {\langle \boldsymbol {x} - \boldsymbol {y} , \boldsymbol {x} - \boldsymbol {y} \rangle}\tag{3.21}
$$

is called the distance between $\boldsymbol{x}$ and $\boldsymbol{y}$ for $\boldsymbol{x},\boldsymbol{y}\in V$ . If we use the dot product as the inner product, then the distance is called Euclidean distance. 

The mapping 

$$
d: V \times V \to \mathbb {R}\tag{3.22}
$$

$$
(\boldsymbol {x}, \boldsymbol {y}) \mapsto d (\boldsymbol {x}, \boldsymbol {y})\tag{3.23}
$$

is called a metric. 

**Remark.** Similar to the length of a vector, the distance between vectors does not require an inner product: a norm is sufficient. If we have a norm induced by an inner product, the distance may vary depending on the choice of the inner product. ◇ 

A metric d satisfies the following: 

1. d is positive definite, i.e., $d ( { \pmb x } , { \pmb y } ) \geqslant 0$ for all $\boldsymbol{x},\boldsymbol{y}\in V$ and $d(\boldsymbol{x},\boldsymbol{y})=0\iff\boldsymbol{x}=\boldsymbol{y}$ 

2. d is symmetric, i.e., $d ( \pmb { x } , \pmb { y } ) = d ( \pmb { y } , \pmb { x } )$ for all $\boldsymbol{x},\boldsymbol{y}\in V$ 

3. Triangle inequality: $d ( \pmb { x } , z ) \leqslant d ( \pmb { x } , \pmb { y } ) + d ( \pmb { y } , z )$ for all $\pmb { x } , \pmb { y } , \pmb { z } \in V$ 

**Remark.** At first glance, the lists of properties of inner products and metrics look very similar. However, by comparing Definition 3.3 with Definition 3.6 we observe that $\langle { \pmb x } , { \pmb y } \rangle$ and $d ( { \pmb x } , { \pmb y } )$ behave in opposite directions. Very similar $\boldsymbol{x}$ and $\boldsymbol{y}$ will result in a large value for the inner product and a small value for the metric. ◇ 

## 3.4 Angles and Orthogonality

In addition to enabling the definition of lengths of vectors, as well as the distance between two vectors, inner products also capture the geometry of a vector space by defining the angle $\omega$ between two vectors. We use the Cauchy-Schwarz inequality (3.17) to define angles $\omega$ in inner product spaces between two vectors x, y, and this notion coincides with our intuition in $\mathbb { R } ^ { 2 }$ and $\mathbb { R } ^ { 3 }$ . Assume that $\pmb { x } \neq \mathbf { 0 } , \pmb { y } \neq \mathbf { 0 }$ . Then 

$$
- 1 \leqslant \frac {\langle \boldsymbol {x} , \boldsymbol {y} \rangle}{\| \boldsymbol {x} \| \| \boldsymbol {y} \|} \leqslant 1.\tag{3.24}
$$

Therefore, there exists a unique $\omega \in [ 0 , \pi ]$ , illustrated in Figure 3.4, with 

$$
\cos \omega = \frac {\langle \boldsymbol {x} , \boldsymbol {y} \rangle}{\| \boldsymbol {x} \| \| \boldsymbol {y} \|}.\tag{3.25}
$$

Figure 3.4 When restricted to $[ 0 , \pi ]$ then $f ( \omega ) = \cos ( \omega )$ returns a unique number in the interval [−1, 1]. 

![image](<Images/03_Analytic_Geometry_image_005.jpg>)

The number $\omega$ is the angle between the vectors $\boldsymbol{x}$ and $\boldsymbol{y}$. Intuitively, the angle between two vectors tells us how similar their orientations are. For example, using the dot product, the angle between x and $\begin{array} { r } { \pmb { y } = 4 \pmb { x } } \end{array}$ , i.e., y is a scaled version of $x$, is 0: Their orientation is the same. 

**Example 3.6 (Angle between Vectors)**

Let us compute the angle between $\pmb { x } = [ 1 , 1 ] ^ { \top } \in \mathbb { R } ^ { 2 }$ and $\pmb { y } = [ 1 , 2 ] ^ { \top } \in \mathbb { R } ^ { 2 }$; see Figure 3.5, where we use the dot product as the inner product. Then we get 

$$
\cos \omega = \frac {\langle \boldsymbol {x} , \boldsymbol {y} \rangle}{\sqrt {\langle \boldsymbol {x} , \boldsymbol {x} \rangle \langle \boldsymbol {y} , \boldsymbol {y} \rangle}} = \frac {\boldsymbol {x} ^ {\top} \boldsymbol {y}}{\sqrt {\boldsymbol {x} ^ {\top} \boldsymbol {x y} ^ {\top} \boldsymbol {y}}} = \frac {3}{\sqrt {10}},\tag{3.26}
$$

and the angle between the two vectors is arccos $\left( { \frac { 3 } { \sqrt { 10 } } } \right) \approx 0.32 { \mathrm { r a d } }$ , which corresponds to about $18^{\circ}$ 

![image](<Images/03_Analytic_Geometry_image_006.jpg>)

Figure 3.5 The angle ω between two vectors x, y is computed using the inner product.

A key feature of the inner product is that it also allows us to characterize vectors that are orthogonal. 

**Definition 3.7 (Orthogonality).** Two vectors x and y are orthogonal if and only if $\langle { \pmb x } , { \pmb y } \rangle = 0$, and we write $\mathbf {  { x } } \perp \mathbf {  { y } }$ . If additionally $\| { \pmb x } \| = 1 = \| { \pmb y } \|$ , i.e., the vectors are unit vectors, then x and y are orthonormal. 

An implication of this definition is that the 0-vector is orthogonal to every vector in the vector space. 

**Remark.** Orthogonality is the generalization of the concept of perpendicularity to bilinear forms that do not have to be the dot product. In our context, geometrically, we can think of orthogonal vectors as having a right angle with respect to a specific inner product. 

**Example 3.7 (Orthogonal Vectors)**

![image](<Images/03_Analytic_Geometry_image_007.jpg>)

Figure 3.6 The angle ω between two vectors x, y can change depending on the inner product.

Consider two vectors $\pmb { x } = [ 1 , 1 ] ^ { \top } , \pmb { y } = [ - 1 , 1 ] ^ { \top } \in \mathbb { R } ^ { 2 }$ ; see Figure 3.6. We are interested in determining the angle ω between them using two different inner products. Using the dot product as the inner product yields an angle $\omega$ between x and $\boldsymbol{y}$ of $90^{\circ}$ , such that $\boldsymbol{x}\perp\boldsymbol{y}$ . However, if we choose the inner product 

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle = \boldsymbol {x} ^ {\top} \left[ \begin{array}{c c} 2 & 0 \\ 0 & 1 \end{array} \right] \boldsymbol {y},\tag{3.27}
$$

we get that the angle ω between x and $\boldsymbol{y}$ is given by 

$$
\cos \omega = \frac {\langle \boldsymbol {x} , \boldsymbol {y} \rangle}{\| \boldsymbol {x} \| \| \boldsymbol {y} \|} = - \frac {1}{3} \implies \omega \approx 1.91 \mathrm{rad} \approx 109.5 ^ {\circ},\tag{3.28}
$$

and x and y are not orthogonal. Therefore, vectors that are orthogonal with respect to one inner product do not have to be orthogonal with respect to a different inner product. 

**Definition 3.8 (Orthogonal Matrix).** A square matrix $\pmb { A } \in \mathbb { R } ^ { n \times n }$ is an orthogonal matrix if and only if its columns are orthonormal so that 

$$
\boldsymbol {A} \boldsymbol {A} ^ {\top} = \boldsymbol {I} = \boldsymbol {A} ^ {\top} \boldsymbol {A},\tag{3.29}
$$

which implies that 

$$
\boldsymbol {A} ^ {- 1} = \boldsymbol {A} ^ {\top},\tag{3.30}
$$

i.e., the inverse is obtained by simply transposing the matrix. 

> It is convention to call these matrices “orthogonal” but a more precise description would be “orthonormal”. Transformations with orthogonal matrices preserve distances and angles.

Transformations by orthogonal matrices are special because the length of a vector x is not changed when transforming it using an orthogonal matrix A. For the dot product, we obtain 

$$
\left\| \boldsymbol {A} \boldsymbol {x} \right\| ^ {2} = (\boldsymbol {A} \boldsymbol {x}) ^ {\top} (\boldsymbol {A} \boldsymbol {x}) = \boldsymbol {x} ^ {\top} \boldsymbol {A} ^ {\top} \boldsymbol {A} \boldsymbol {x} = \boldsymbol {x} ^ {\top} \boldsymbol {I} \boldsymbol {x} = \boldsymbol {x} ^ {\top} \boldsymbol {x} = \| \boldsymbol {x} \| ^ {2}.\tag{3.31}
$$

Moreover, the angle between any two vectors x, y, as measured by their inner product, is also unchanged when transforming both of them using an orthogonal matrix A. Assuming the dot product as the inner product, the angle of the images Ax and $\pmb { A } \pmb { y }$ is given as 

$$
\cos \omega = \frac {(\boldsymbol {A} \boldsymbol {x}) ^ {\top} (\boldsymbol {A} \boldsymbol {y})}{\| \boldsymbol {A} \boldsymbol {x} \| \| \boldsymbol {A} \boldsymbol {y} \|} = \frac {\boldsymbol {x} ^ {\top} \boldsymbol {A} ^ {\top} \boldsymbol {A} \boldsymbol {y}}{\sqrt {\boldsymbol {x} ^ {\top} \boldsymbol {A} ^ {\top} \boldsymbol {A} \boldsymbol {x} \boldsymbol {y} ^ {\top} \boldsymbol {A} ^ {\top} \boldsymbol {A} \boldsymbol {y}}} = \frac {\boldsymbol {x} ^ {\top} \boldsymbol {y}}{\| \boldsymbol {x} \| \| \boldsymbol {y} \|},\tag{3.32}
$$

which gives exactly the angle between x and $\boldsymbol{y}$. This means that orthogonal matrices A with $\pmb { A } ^ { \top } = \pmb { A } ^ { - 1 }$ preserve both angles and distances. It turns out that orthogonal matrices define transformations that are rotations (with the possibility of flips). In Section 3.9, we will discuss more details about rotations.

## 3.5 Orthonormal Basis

In Section 2.6.1, we characterized properties of basis vectors and found that in an n-dimensional vector space, we need n basis vectors, i.e., n vectors that are linearly independent. In Sections 3.3 and 3.4, we used inner products to compute the length of vectors and the angle between vectors. In the following, we will discuss the special case where the basis vectors are orthogonal to each other and where the length of each basis vector is 1. We will call this basis then an orthonormal basis. 

Let us introduce this more formally. 

**Definition 3.9 (Orthonormal Basis).** Consider an n-dimensional vector space $V$ and a basis $\{ b _ { 1 } , \ldots , b _ { n } \}$ of $V$ . If 

$$
\langle \boldsymbol {b} _ {i}, \boldsymbol {b} _ {j} \rangle = 0 \quad \text { for } i \neq j\tag{3.33}
$$

$$
\langle \pmb {b} _ {i}, \pmb {b} _ {i} \rangle = 1\tag{3.34}
$$

for all $i , j = 1 , \ldots , n$ then the basis is called an orthonormal basis (ONB). If only (3.33) is satisfied, then the basis is called an orthogonal basis. Note that (3.34) implies that every basis vector has length/norm 1. 

Recall from Section 2.6.1 that we can use Gaussian elimination to find a basis for a vector space spanned by a set of vectors. Assume we are given a set $\{ \tilde { b } _ { 1 } , \dots , \tilde { b } _ { n } \}$ of non-orthogonal and unnormalized basis vectors. We concatenate them into a matrix $\tilde { \pmb { B } } = [ \tilde { \pmb { b } } _ { 1 } , \dots , \tilde { \pmb { b } } _ { n } ]$ and apply Gaussian elimination to the augmented matrix (Section 2.3.2) $[\tilde{\boldsymbol{B}}\tilde{\boldsymbol{B}}^{\top}\mid\tilde{\boldsymbol{B}}]$ to obtain an orthonormal basis. This constructive way to iteratively build an orthonormal basis $\{ b _ { 1 } , \ldots , b _ { n } \}$ is called the Gram-Schmidt process (Strang, 2003). 

**Example 3.8 (Orthonormal Basis)**

The canonical/standard basis for a Euclidean vector space $\mathbb { R } ^ { n }$ is an orthonormal basis, where the inner product is the dot product of vectors. 

In $\mathbb { R } ^ { 2 }$ , the vectors 

$$
\boldsymbol {b} _ {1} = \frac {1}{\sqrt {2}} \left[ \begin{array}{c} 1 \\ 1 \end{array} \right], \quad \boldsymbol {b} _ {2} = \frac {1}{\sqrt {2}} \left[ \begin{array}{c} 1 \\ - 1 \end{array} \right]\tag{3.35}
$$

form an orthonormal basis since $\pmb { b } _ { 1 } ^ { \top } \pmb { b } _ { 2 } = 0$ and $\| \pmb { b } _ { 1 } \| = 1 = \| \pmb { b } _ { 2 } \|$ 

We will exploit the concept of an orthonormal basis in Chapter 12 and Chapter 10 when we discuss support vector machines and principal component analysis. 

## 3.6 Orthogonal Complement

Having defined orthogonality, we will now look at vector spaces that are orthogonal to each other. This will play an important role in Chapter 10, when we discuss linear dimensionality reduction from a geometric perspective. 

Consider a D-dimensional vector space V and an M-dimensional subspace $U \subseteq V$ . Then its orthogonal complement $U ^ { \perp }$ is a $( D - M )$ -dimensional subspace of $V$ and contains all vectors in $V$ that are orthogonal to every vector in U. Furthermore, $U \cap U ^ { \bot } = \{ { \bf 0 } \}$ so that any vector $\pmb { x } \in V$ can be uniquely decomposed into 

$$
\boldsymbol {x} = \sum_ {m = 1} ^ {M} \lambda_ {m} \boldsymbol {b} _ {m} + \sum_ {j = 1} ^ {D - M} \psi_ {j} \boldsymbol {b} _ {j} ^ {\perp}, \quad \lambda_ {m}, \psi_ {j} \in \mathbb {R},\tag{3.36}
$$

where $\left( \pmb { b } _ { 1 } , \dots , \pmb { b } _ { M } \right)$ is a basis of $U$ and $( \pmb { b } _ { 1 } ^ { \perp } , \ldots , \pmb { b } _ { D - M } ^ { \perp } )$ is a basis of $U ^ { \perp }$ 

Therefore, the orthogonal complement can also be used to describe a plane $U$ (two-dimensional subspace) in a three-dimensional vector space. More specifically, the vector w with $\| \pmb { w } \| = 1$ , which is orthogonal to the plane $U$, is the basis vector of $U ^ { \perp }$ . Figure 3.7 illustrates this setting. All vectors that are orthogonal to w must (by construction) lie in the plane $U$. The vector w is called the normal vector of $U$ 

Figure 3.7 A plane U in a three-dimensional vector space can be described by its normal vector, which spans its orthogonal complement $U ^ { \perp }$ 

![image](<Images/03_Analytic_Geometry_image_008.jpg>)

Generally, orthogonal complements can be used to describe hyperplanes in n-dimensional vector and affine spaces. 

## 3.7 Inner Product of Functions

Thus far, we looked at properties of inner products to compute lengths, angles and distances. We focused on inner products of finite-dimensional vectors. In the following, we will look at an example of inner products of a different type of vectors: inner products of functions. 

The inner products we discussed so far were defined for vectors with a finite number of entries. We can think of a vector $\pmb { x } \in \mathbb { R } ^ { n }$ as a function with n function values. The concept of an inner product can be generalized to vectors with an infinite number of entries (countably infinite) and also continuous-valued functions (uncountably infinite). Then the sum over individual components of vectors (see Equation (3.5) for example) turns into an integral. 

An inner product of two functions $u:\mathbb{R}\to\mathbb{R}$ and $v:\mathbb{R}\to\mathbb{R}$ can be defined as the definite integral 

$$
\langle u, v \rangle := \int_ {a} ^ {b} u (x) v (x) d x\tag{3.37}
$$

for lower and upper limits $a , b < \infty$ , respectively. As with our usual inner product, we can define norms and orthogonality by looking at the inner product. If (3.37) evaluates to 0, the functions u and v are orthogonal. To make the preceding inner product mathematically precise, we need to take care of measures and the definition of integrals, leading to the definition of a Hilbert space. Furthermore, unlike inner products on finite-dimensional vectors, inner products on functions may diverge (have infinite value). All this requires diving into some more intricate details of real and functional analysis, which we do not cover in this book. 

**Example 3.9 (Inner Product of Functions)**

If we choose $u = \sin ( x )$ and $v = \cos ( x )$ , the integrand $f ( x ) = u ( x ) v ( x )$ of (3.37), is shown in Figure 3.8. We see that this function is odd, i.e., $f ( - x ) = - f ( x )$ . Therefore, the integral with limits $a = - \pi , b = \pi$ of this product evaluates to 0. Therefore, sin and cos are orthogonal functions. 

![image](<Images/03_Analytic_Geometry_image_009.jpg>)

Figure 3.8 $f(x)=\sin(x)\cos(x)$. 

**Remark.** It also holds that the collection of functions 

$$
\{1, \cos (x), \cos (2 x), \cos (3 x), \dots \}\tag{3.38}
$$

is orthogonal if we integrate from $-\pi$ to $\pi$, i.e., any pair of functions are orthogonal to each other. The collection of functions in (3.38) spans a large subspace of the functions that are even and periodic on $[ - \pi , \pi )$ , and projecting functions onto this subspace is the fundamental idea behind Fourier series. 

In Section 6.4.6, we will have a look at a second type of unconventional inner products: the inner product of random variables.

## 3.8 Orthogonal Projections

Projections are an important class of linear transformations (besides rotations and reflections) and play an important role in graphics, coding theory, statistics and machine learning. In machine learning, we often deal with data that is high-dimensional. High-dimensional data is often hard to analyze or visualize. However, high-dimensional data quite often possesses the property that only a few dimensions contain most information, and most other dimensions are not essential to describe key properties of the data. When we compress or visualize high-dimensional data, we will lose information. To minimize this compression loss, we ideally find the most informative dimensions in the data. As discussed in Chapter 1, data can be represented as vectors, and in this chapter, we will discuss some of the fundamental tools for data compression. More specifically, we can project the original high-dimensional data onto a lower-dimensional feature space and work in this lower-dimensional space to learn more about the dataset and extract relevant patterns. For example, machine learning algorithms, such as principal component analysis (PCA) by Pearson (1901) and Hotelling (1933) and deep neural networks (e.g., deep auto-encoders (Deng et al., 2010)), heavily exploit the idea of dimensionality reduction. In the following, we will focus on orthogonal projections, which we will use in Chapter 10 for linear dimensionality reduction and in Chapter 12 for classification. Even linear regression, which we discuss in Chapter 9, can be interpreted using orthogonal projections. For a given lower-dimensional subspace, orthogonal projections of high-dimensional data retain as much information as possible and minimize the difference/ error between the original data and the corresponding projection. An illustration of such an orthogonal projection is given in Figure 3.9. Before we detail how to obtain these projections, let us define what a projection actually is. 

> “Feature” is a common expression for data representation.

![Figure 3.9: Orthogonal projection of a dataset](<Images/03_Analytic_Geometry_image_010.jpg>)

Figure 3.9 Orthogonal projection (orange dots) of a two-dimensional dataset (blue dots) onto a one-dimensional subspace (straight line).

**Definition 3.10 (Projection).** Let V be a vector space and $U \subseteq V$ a subspace of V . A linear mapping $\pi:V\to U$ is called a projection if $\pi ^ { 2 } = \pi \circ \pi = \pi$ 

Since linear mappings can be expressed by transformation matrices (see Section 2.7), the preceding definition applies equally to a special kind of transformation matrices, the projection matrices $P _ { \pi }$ , which exhibit the property that $P _ { \pi } ^ { 2 } = P _ { \pi }$ 

In the following, we will derive orthogonal projections of vectors in the inner product space $\left( \mathbb { R } ^ { n } , \langle \cdot , \cdot \rangle \right)$ onto subspaces. We will start with one-dimensional subspaces, which are also called lines. If not mentioned otherwise, we assume the dot product $\langle \pmb { x } , \pmb { y } \rangle = \pmb { x } ^ { \top } \pmb { y }$ as the inner product. 

### 3.8.1 Projection onto One-Dimensional Subspaces (Lines)

Assume we are given a line (one-dimensional subspace) through the origin with basis vector $b ~ \in ~ \mathbb { R } ^ { n }$ . The line is a one-dimensional subspace $U \subseteq \mathbb { R } ^ { n }$ spanned by b. When we project $\pmb { x } \in \mathbb { R } ^ { n }$ onto $U$ , we seek the vector $\pi _ { U } ( { \pmb x } ) \in U$ that is closest to x. Using geometric arguments, let us characterize some properties of the projection $\pi _ { U } ( { \pmb x } )$ (Figure 3.10(a) serves as an illustration): 

- The projection $\pi _ { U } ( { \pmb x } )$ is closest to $\boldsymbol{x}$, where “closest” implies that the distance $\| { \pmb x } - \pi _ { U } ( { \pmb x } ) \|$ is minimal. It follows that the segment $\pi _ { U } ( { \pmb x } ) - { \pmb x }$ from $\pi _ { U } ( { \pmb x } )$ to x is orthogonal to $U$ , and therefore the basis vector b of $U$ . The orthogonality condition yields $\langle \pi _ { U } ( { \pmb x } ) - { \pmb x } , { \pmb b } \rangle = 0$ since angles between vectors are defined via the inner product. 

- The projection $\pi _ { U } ( { \pmb x } )$ of x onto $U$ must be an element of U and, therefore, a multiple of the basis vector b that spans U. Hence, $\pi _ { U } ( { \pmb x } ) = \lambda { \pmb b }$ , for some $\lambda \in \mathbb { R }$ 

![image](<Images/03_Analytic_Geometry_image_011.jpg>)

(a) Projection of $\boldsymbol{x}\in\mathbb{R}^{2}$ onto a subspace U with basis vector b.

![image](<Images/03_Analytic_Geometry_image_012.jpg>)

Figure 3.10 Examples of projections onto one-dimensional subspaces.

(b) Projection of a two-dimensional vector x with $\| \pmb { x } \| = 1$ onto a one-dimensional subspace spanned by b.

> $\lambda$ is the coordinate of $\pi_U(\boldsymbol{x})$ with respect to $\boldsymbol{b}$.

In the following three steps, we determine the coordinate $\lambda$, the projection $\pi _ { U } ( { \pmb x } ) \in U$ , and the projection matrix ${ \pmb P } _ { \pi }$ that maps any $\mathbf { x } \in \mathbb { R } ^ { n }$ onto $U$: 

**1.** Finding the coordinate $\lambda$. The orthogonality condition yields 

$$
\langle \boldsymbol {x} - \pi_ {U} (\boldsymbol {x}), \boldsymbol {b} \rangle = 0 \stackrel {{\pi_ {U} (\boldsymbol {x}) = \lambda \boldsymbol {b}}} {{\Longleftrightarrow}} \langle \boldsymbol {x} - \lambda \boldsymbol {b}, \boldsymbol {b} \rangle = 0.\tag{3.39}
$$

We can now exploit the bilinearity of the inner product and arrive at 

$$
\langle \boldsymbol {x}, \boldsymbol {b} \rangle - \lambda \langle \boldsymbol {b}, \boldsymbol {b} \rangle = 0 \iff \lambda = \frac {\langle \boldsymbol {x} , \boldsymbol {b} \rangle}{\langle \boldsymbol {b} , \boldsymbol {b} \rangle} = \frac {\langle \boldsymbol {b} , \boldsymbol {x} \rangle}{\| \boldsymbol {b} \| ^ {2}}.\tag{3.40}
$$

> With a general inner product, we get $\lambda=\langle\boldsymbol{x},\boldsymbol{b}\rangle$ if $\|\boldsymbol{b}\|=1$.

In the last step, we exploited the fact that inner products are symmetric. If we choose $\langle \cdot , \cdot \rangle$ to be the dot product, we obtain 

$$
\lambda = \frac {\boldsymbol {b} ^ {\top} \boldsymbol {x}}{\boldsymbol {b} ^ {\top} \boldsymbol {b}} = \frac {\boldsymbol {b} ^ {\top} \boldsymbol {x}}{\| \boldsymbol {b} \| ^ {2}}.\tag{3.41}
$$

If $\|\boldsymbol{b}\|=1$ , then the coordinate λ of the projection is given by ${ \pmb b } ^ { \top } { \pmb x }$ 

**2.** Finding the projection point $\pi _ { U } ( { \pmb x } ) \in U$ . Since $\pi _ { U } ( { \pmb x } ) = \lambda { \pmb b }$, we immediately obtain with (3.40) that 

$$
\pi_ {U} (\boldsymbol {x}) = \lambda \boldsymbol {b} = \frac {\langle \boldsymbol {x} , \boldsymbol {b} \rangle}{\| \boldsymbol {b} \| ^ {2}} \boldsymbol {b} = \frac {\boldsymbol {b} ^ {\top} \boldsymbol {x}}{\| \boldsymbol {b} \| ^ {2}} \boldsymbol {b},\tag{3.42}
$$

where the last equality holds for the dot product only. We can also compute the length of $\pi _ { U } ( { \pmb x } )$ by means of Definition 3.1 as 

$$
\left\| \pi_ {U} (\boldsymbol {x}) \right\| = \left\| \lambda \boldsymbol {b} \right\| = | \lambda | \| \boldsymbol {b} \|.\tag{3.43}
$$

Hence, our projection is of length $| \lambda |$ times the length of b. This also adds the intuition that λ is the coordinate of $\pi _ { U } ( { \pmb x } )$ with respect to the basis vector b that spans our one-dimensional subspace $U$ 

If we use the dot product as an inner product, we get 

$$
\left\| \pi_ {U} (\boldsymbol {x}) \right\| \stackrel {(3.42)} {=} \frac {\left| \boldsymbol {b} ^ {\top} \boldsymbol {x} \right|}{\left\| \boldsymbol {b} \right\| ^ {2}} \left\| \boldsymbol {b} \right\| \stackrel {(3.25)} {=} | \cos \omega | \| \boldsymbol {x} \| \| \boldsymbol {b} \| \frac {\left\| \boldsymbol {b} \right\|}{\left\| \boldsymbol {b} \right\| ^ {2}} = | \cos \omega | \| \boldsymbol {x} \|.\tag{3.44}
$$

> The horizontal axis is a one-dimensional subspace.

Here, ω is the angle between x and b. This equation should be familiar from trigonometry: If $\|\boldsymbol{x}\|=1$ , then x lies on the unit circle. It follows that the projection onto the horizontal axis spanned by b is exactly cos ω, and the length of the corresponding vector $\pi _ { U } ( { \pmb x } ) = | \cos { \omega } |$ . An illustration is given in Figure 3.10(b). 

**3.** Finding the projection matrix ${ \pmb P } _ { \pi }$ . We know that a projection is a linear mapping (see Definition 3.10). Therefore, there exists a projection matrix $P _ { \pi }$, such that $\pi _ { U } ( { \pmb x } ) = P _ { \pi } { \pmb x }$ . With the dot product as inner product and 

$$
\pi_ {U} (\boldsymbol {x}) = \lambda \boldsymbol {b} = \boldsymbol {b} \lambda = \boldsymbol {b} \frac {\boldsymbol {b} ^ {\top} \boldsymbol {x}}{\| \boldsymbol {b} \| ^ {2}} = \frac {\boldsymbol {b b} ^ {\top}}{\| \boldsymbol {b} \| ^ {2}} \boldsymbol {x},\tag{3.45}
$$

we immediately see that 

$$
\boldsymbol {P} _ {\pi} = \frac {\boldsymbol {b b} ^ {\top}}{\| \boldsymbol {b} \| ^ {2}}.\tag{3.46}
$$

> Projection matrices are always symmetric.

Note that $b b ^ { \top }$ (and, consequently, $P_{\pi}$) is a symmetric matrix (of rank 1), and $\| \pmb { b } \| ^ { 2 } = \langle \pmb { b } , \pmb { b } \rangle$ is a scalar. 

The projection matrix $P _ { \pi }$ projects any vector $\pmb { x } \in \mathbb { R } ^ { n }$ onto the line through the origin with direction b (equivalently, the subspace $U$ spanned by b). 

**Remark.** The projection $\pi _ { U } ( \pmb { x } ) \in \mathbb { R } ^ { n }$ is still an n-dimensional vector and not a scalar. However, we no longer require n coordinates to represent the projection, but only a single one if we want to express it with respect to the basis vector b that spans the subspace $U$: $\lambda$ ◇ 

![image](<Images/03_Analytic_Geometry_image_013.jpg>)

Figure 3.11 Projection onto a two-dimensional subspace U with basis $b _ { 1 } , b _ { 2 }$ . The projection π<sub>U</sub> (x) of x $\in \mathbb { R } ^ { 3 }$ onto U can be expressed as a linear combination of $b _ { 1 } , b _ { 2 }$ and the displacement vector ${ \pmb x } - \pi _ { U } ( { \pmb x } )$ is orthogonal to both $\pmb { b } _ { 1 }$ and $b _ { 2 }$ 

**Example 3.10 (Projection onto a Line)**

Find the projection matrix ${ \pmb P } _ { \pi }$ onto the line through the origin spanned by $\pmb { b } = \left[ 1 \quad 2 \quad 2 \right] ^ { \top }$ . b is a direction and a basis of the one-dimensional subspace (line through origin). 

With (3.46), we obtain 

$$
\boldsymbol {P} _ {\pi} = \frac {\boldsymbol {b b} ^ {\top}}{\boldsymbol {b} ^ {\top} \boldsymbol {b}} = \frac {1}{9} \left[ \begin{array}{l} 1 \\ 2 \\ 2 \end{array} \right] \left[ \begin{array}{l l l} 1 & 2 & 2 \end{array} \right] = \frac {1}{9} \left[ \begin{array}{l l l} 1 & 2 & 2 \\ 2 & 4 & 4 \\ 2 & 4 & 4 \end{array} \right].\tag{3.47}
$$

Let us now choose a particular x and see whether it lies in the subspace spanned by b. For $\boldsymbol{x}=[1,1,1]^{\top}$ , the projection is 

$$
\pi_ {U} (\boldsymbol {x}) = \boldsymbol {P} _ {\pi} \boldsymbol {x} = \frac {1}{9} \left[ \begin{array}{c c c} 1 & 2 & 2 \\ 2 & 4 & 4 \\ 2 & 4 & 4 \end{array} \right] \left[ \begin{array}{c} 1 \\ 1 \\ 1 \end{array} \right] = \frac {1}{9} \left[ \begin{array}{c} 5 \\ 10 \\ 10 \end{array} \right] \in \operatorname{span} [ \left[ \begin{array}{c} 1 \\ 2 \\ 2 \end{array} \right] ].\tag{3.48}
$$

Note that the application of $P _ { \pi }$ to $\pi _ { U } ( { \pmb x } )$ does not change anything, i.e., $\pmb { P } _ { \pi } \pi _ { U } ( \pmb { x } ) = \pi _ { U } ( \pmb { x } )$ . This is expected because according to Definition 3.10, we know that a projection matrix ${ \pmb P } _ { \pi }$ satisfies $\boldsymbol { P } _ { \pi } ^ { 2 } \boldsymbol { x } = \boldsymbol { P } _ { \pi } \boldsymbol { x }$ for all x. 

**Remark.** With the results from Chapter 4, we can show that $\pi _ { U } ( { \pmb x } )$ is an eigenvector of $P_{\pi}$ , and the corresponding eigenvalue is 1.

### 3.8.2 Projection onto General Subspaces

In the following, we look at orthogonal projections of vectors $\pmb { x } \in \mathbb { R } ^ { n }$ onto lower-dimensional subspaces $U \subseteq \mathbb { R } ^ { n }$ with $\dim ( U ) = m \geqslant 1$ . An illustration is given in Figure 3.11. 

Assume that $\left( b _ { 1 } , \ldots , b _ { m } \right)$ is an ordered basis of U. Any projection $\pi _ { U } ( { \pmb x } )$ onto U is necessarily an element of U. Therefore, they can be represented as linear combinations of the basis vectors $b _ { 1 } , \ldots , b _ { m }$ of $U$ , such that $\begin{array} { r } { \pi _ { U } ( { \pmb x } ) = \sum _ { i = 1 } ^ { m } \lambda _ { i } \pmb { b } _ { i } } \end{array}$ 

> If U is given by a set of spanning vectors, which are not a basis, make sure you determine a basis $\pmb { b } _ { 1 } , \dots , \pmb { b } _ { m }$ before proceeding. 

> The basis vectors form the columns of $B\in\mathbb{R}^{n\times m}$, where $B=[\boldsymbol{b}_1,\ldots,\boldsymbol{b}_m]$.

As in the 1D case, we follow a three-step procedure to find the projection $\pi _ { U } ( { \pmb x } )$ and the projection matrix $P _ { \pi }$ : 

**1.** Find the coordinates $\lambda _ { 1 } , \ldots , \lambda _ { m }$ of the projection (with respect to the basis of U), such that the linear combination 

$$
\pi_ {U} (\boldsymbol {x}) = \sum_ {i = 1} ^ {m} \lambda_ {i} \boldsymbol {b} _ {i} = B \boldsymbol {\lambda},\tag{3.49}
$$

$$
\boldsymbol {B} = \left[ \boldsymbol {b} _ {1}, \dots , \boldsymbol {b} _ {m} \right] \in \mathbb {R} ^ {n \times m}, \quad \boldsymbol {\lambda} = \left[ \lambda_ {1}, \dots , \lambda_ {m} \right] ^ {\top} \in \mathbb {R} ^ {m},\tag{3.50}
$$

is closest to $\pmb { x } \in \mathbb { R } ^ { n }$ . As in the 1D case, “closest” means “minimum distance”, which implies that the vector connecting $\pi _ { U } ( \pmb { x } ) \in U$ and $\pmb { x } \in \mathbb { R } ^ { n }$ must be orthogonal to all basis vectors of $U$ . Therefore, we obtain m simultaneous conditions (assuming the dot product as the inner product) 

$$
\langle \pmb {b} _ {1}, \pmb {x} - \pi_ {U} (\pmb {x}) \rangle = \pmb {b} _ {1} ^ {\top} (\pmb {x} - \pi_ {U} (\pmb {x})) = 0\tag{3.51}
$$

$$
\vdots
$$

$$
\langle \pmb {b} _ {m}, \pmb {x} - \pi_ {U} (\pmb {x}) \rangle = \pmb {b} _ {m} ^ {\top} (\pmb {x} - \pi_ {U} (\pmb {x})) = 0\tag{3.52}
$$

which, with $\pi _ { U } ( { \pmb x } ) = B \lambda$ , can be written as 

$$
\boldsymbol {b} _ {1} ^ {\top} (\boldsymbol {x} - \boldsymbol {B} \boldsymbol {\lambda}) = 0\tag{3.53}
$$

$$
\begin{array}{c} \vdots \\ \boldsymbol {b} _ {m} ^ {\top} (\boldsymbol {x} - \boldsymbol {B} \boldsymbol {\lambda}) = 0 \end{array}\tag{3.54}
$$

such that we obtain a homogeneous linear equation system 

$$
\left[ \begin{array}{c} \boldsymbol {b} _ {1} ^ {\top} \\ \vdots \\ \boldsymbol {b} _ {m} ^ {\top} \end{array} \right] \left[ \begin{array}{c} \boldsymbol {x} - \boldsymbol {B} \boldsymbol {\lambda} \end{array} \right] = \mathbf {0} \iff \boldsymbol {B} ^ {\top} (\boldsymbol {x} - \boldsymbol {B} \boldsymbol {\lambda}) = \mathbf {0}\tag{3.55}
$$

$$
\Longleftrightarrow \boldsymbol {B} ^ {\top} \boldsymbol {B} \lambda = \boldsymbol {B} ^ {\top} \boldsymbol {x}.\tag{3.56}
$$

The last expression is called normal equation. Since $\pmb { b } _ { 1 } , \dots , \pmb { b } _ { m }$ are a basis of $U$ and, therefore, linearly independent, $\boldsymbol { B } ^ { \intercal } \boldsymbol { B } \in \mathbb { R } ^ { m \times m }$ is regular and can be inverted. This allows us to solve for the coefficients/ coordinates 

$$
\boldsymbol {\lambda} = \left(\boldsymbol {B} ^ {\top} \boldsymbol {B}\right) ^ {- 1} \boldsymbol {B} ^ {\top} \boldsymbol {x}.\tag{3.57}
$$

The matrix $( B ^ { \top } B ) ^ { - 1 } B ^ { \top }$ is also called the pseudo-inverse of $B$, which can be computed for non-square matrices B. It only requires that $B ^ { \top } B$ is positive definite, which is the case if B is full rank. In practical applications (e.g., linear regression), we often add a “jitter term” ϵI to $B ^ { \top } B$ to guarantee increased numerical stability and positive definiteness. This “ridge” can be rigorously derived using Bayesian inference. See Chapter 9 for details. 

**2.** Find the projection $\pi _ { U } ( { \pmb x } ) \in U$ . We already established that $\pi_U(\boldsymbol{x})=B\boldsymbol{\lambda}$. Therefore, with (3.57) 

$$
\pi_ {U} (\boldsymbol {x}) = \boldsymbol {B} (\boldsymbol {B} ^ {\top} \boldsymbol {B}) ^ {- 1} \boldsymbol {B} ^ {\top} \boldsymbol {x}.\tag{3.58}
$$

**3.** Find the projection matrix ${ \pmb P } _ { \pi }$ . From (3.58), we can immediately see that the projection matrix that solves $\pmb { P } _ { \pi } \pmb { x } = \pi _ { U } ( \pmb { x } )$ must be 

$$
\boldsymbol {P} _ {\pi} = \boldsymbol {B} (\boldsymbol {B} ^ {\top} \boldsymbol {B}) ^ {- 1} \boldsymbol {B} ^ {\top}.\tag{3.59}
$$

**Remark.** The solution for projecting onto general subspaces includes the 1D case as a special case: If $\dim(U)=1$ , then $B ^ { \top } B \in \mathbb { R }$ is a scalar and we can rewrite the projection matrix in (3.59) $\begin{array} { r } { \pmb { P } _ { \pi } = \pmb { B } ( \pmb { B } ^ { \top } \pmb { B } ) ^ { - 1 } \pmb { B } ^ { \top } } \end{array}$ as $\begin{array} { r } { { P } _ { \pi } = \frac { B B ^ { \top } } { B ^ { \top } B } } \end{array}$ , which is exactly the projection matrix in (3.46). ◇ 

**Example 3.11 (Projection onto a Two-dimensional Subspace)**

For a subspace $U=\operatorname{span}\left[\begin{bmatrix}1\\1\\1\end{bmatrix},\begin{bmatrix}0\\1\\2\end{bmatrix}\right]\subseteq\mathbb{R}^{3}$ and $\boldsymbol{x}=\begin{bmatrix}6\\0\\0\end{bmatrix}\in\mathbb{R}^{3}$ find the coordinates $\boldsymbol{\lambda}$ of x in terms of the subspace $U$, the projection point $\pi_U(\boldsymbol{x})$ and the projection matrix $P_{\pi}$.

First, we see that the generating set of $U$ is a basis (linear independence) and write the basis vectors of U into a matrix $\boldsymbol{B} = \left[ \begin{array} { l l } { 1 } & { 0 } \\ { 1 } & { 1 } \\ { 1 } & { 2 } \end{array} \right]$ 

Second, we compute the matrix $B ^ { \top } B$ and the vector $B^{\top}\boldsymbol{x}$ as 

$$
\boldsymbol {B} ^ {\top} \boldsymbol {B} = \left[ \begin{array}{c c c} 1 & 1 & 1 \\ 0 & 1 & 2 \end{array} \right] \left[ \begin{array}{c c} 1 & 0 \\ 1 & 1 \\ 1 & 2 \end{array} \right] = \left[ \begin{array}{c c} 3 & 3 \\ 3 & 5 \end{array} \right], \quad \boldsymbol {B} ^ {\top} \boldsymbol {x} = \left[ \begin{array}{c c c} 1 & 1 & 1 \\ 0 & 1 & 2 \end{array} \right] \left[ \begin{array}{c} 6 \\ 0 \\ 0 \end{array} \right] = \left[ \begin{array}{c} 6 \\ 0 \end{array} \right].\tag{3.60}
$$

Third, we solve the normal equation $B^{\top}B\boldsymbol{\lambda}=B^{\top}\boldsymbol{x}$ to find λ: 

$$
\left[ \begin{array}{c c} 3 & 3 \\ 3 & 5 \end{array} \right] \left[ \begin{array}{c} \lambda_ {1} \\ \lambda_ {2} \end{array} \right] = \left[ \begin{array}{c} 6 \\ 0 \end{array} \right] \iff \boldsymbol {\lambda} = \left[ \begin{array}{c} 5 \\ - 3 \end{array} \right].\tag{3.61}
$$

Fourth, the projection $\pi _ { U } ( { \pmb x } )$ of x onto $U$, i.e., into the column space of $B$ , can be directly computed via 

$$
\pi_ {U} (\boldsymbol {x}) = \boldsymbol {B} \boldsymbol {\lambda} = \left[ \begin{array}{c} 5 \\ 2 \\ - 1 \end{array} \right].\tag{3.62}
$$

> The projection error is also called the reconstruction error.

The corresponding projection error is the norm of the difference vector between the original vector and its projection onto U, i.e., 

$$
\left\| \boldsymbol {x} - \pi_ {U} (\boldsymbol {x}) \right\| = \left\| \left[ \begin{array}{c c c} 1 & - 2 & 1 \end{array} \right] ^ {\top} \right\| = \sqrt {6}.\tag{3.63}
$$

Fifth, the projection matrix (for any $\pmb { x } \in \mathbb { R } ^ { 3 }$) is given by 

$$
\boldsymbol {P} _ {\pi} = \boldsymbol {B} (\boldsymbol {B} ^ {\top} \boldsymbol {B}) ^ {- 1} \boldsymbol {B} ^ {\top} = \frac {1}{6} \left[ \begin{array}{c c c} 5 & 2 & - 1 \\ 2 & 2 & 2 \\ - 1 & 2 & 5 \end{array} \right].\tag{3.64}
$$

To verify the results, we can (a) check whether the displacement vector $\pi _ { U } ( { \pmb x } ) - { \pmb x }$ is orthogonal to all basis vectors of U, and (b) verify that $P _ { \pi } = P _ { \pi } ^ { 2 }$ (see Definition 3.10). 

**Remark.** The projections $\pi _ { U } ( { \pmb x } )$ are still vectors in $\mathbb{R}^{n}$ although they lie in an m-dimensional subspace $U \subseteq \mathbb { R } ^ { n }$ . However, to represent a projected vector we only need the m coordinates $\lambda _ { 1 } , \ldots , \lambda _ { m }$ with respect to the basis vectors $\pmb { b } _ { 1 } , \dots , \pmb { b } _ { m }$ of $U$ ◇ 

**Remark.** In vector spaces with general inner products, we have to pay attention when computing angles and distances, which are defined by means of the inner product. 

> We can find approximate solutions to unsolvable linear equation systems using projections.

Projections allow us to look at situations where we have a linear system Ax = b without a solution. Recall that this means that b does not lie in the span of A, i.e., the vector b does not lie in the subspace spanned by the columns of A. Given that the linear equation cannot be solved exactly, we can find an approximate solution. The idea is to find the vector in the subspace spanned by the columns of A that is closest to b, i.e., we compute the orthogonal projection of b onto the subspace spanned by the columns of A. This problem arises often in practice, and the solution is called the least-squares solution (assuming the dot product as the inner product) of an overdetermined system. This is discussed further in Section 9.4. Using reconstruction errors (3.63) is one possible approach to derive principal component analysis (Section 10.3). 

**Remark.** We just looked at projections of vectors x onto a subspace U with basis vectors $\{ b _ { 1 } , \ldots , b _ { k } \}$ . If this basis is an ONB, i.e., (3.33) and (3.34) are satisfied, the projection equation (3.58) simplifies greatly to 

$$
\pi_ {U} (\pmb {x}) = \pmb {B B} ^ {\top} \pmb {x}\tag{3.65}
$$

since $B ^ { \top } B = I$ with coordinates 

$$
\boldsymbol {\lambda} = \boldsymbol {B} ^ {\top} \boldsymbol {x}.\tag{3.66}
$$

This means that we no longer have to compute the inverse from (3.58), which saves computation time. ◇ 

### 3.8.3 Gram-Schmidt Orthogonalization

Projections are at the core of the Gram-Schmidt method that allows us to constructively transform any basis $\left( b _ { 1 } , \ldots , b _ { n } \right)$ of an n-dimensional vector space $V$ into an orthogonal/orthonormal basis $( \pmb { u } _ { 1 } , \dots , \pmb { u } _ { n } )$ of $V$. This basis always exists (Liesen and Mehrmann, 2015) and $\operatorname{span}[\boldsymbol{b}_1,\ldots,\boldsymbol{b}_n]=\operatorname{span}[\boldsymbol{u}_1,\ldots,\boldsymbol{u}_n]$ . The Gram-Schmidt orthogonalization method iteratively constructs an orthogonal basis $\left( \pmb { u } _ { 1 } , \dots , \pmb { u } _ { n } \right)$ from any basis $\left( b _ { 1 } , \ldots , b _ { n } \right)$ of V as follows: 

$$
\boldsymbol {u} _ {1} := \boldsymbol {b} _ {1}\tag{3.67}
$$

$$
\boldsymbol {u} _ {k} := \boldsymbol {b} _ {k} - \pi_ {\text { span } [ \boldsymbol {u} _ {1}, \dots , \boldsymbol {u} _ {k - 1} ]} (\boldsymbol {b} _ {k}), \quad k = 2, \dots , n.\tag{3.68}
$$

In (3.68), the kth basis vector $\boldsymbol{b}_k$ is projected onto the subspace spanned by the first $k - 1$ constructed orthogonal vectors $u _ { 1 } , \ldots , u _ { k - 1 } ;$ see Section 3.8.2. This projection is then subtracted from $b _ { k }$ and yields a vector $\boldsymbol{u}_k$ that is orthogonal to the $( k - 1 )$ -dimensional subspace spanned by $\pmb { u } _ { 1 } , \ldots , \pmb { u } _ { k - 1 }$ . Repeating this procedure for all n basis vectors $b _ { 1 } , \ldots , b _ { n }$ yields an orthogonal basis $\left( \pmb { u } _ { 1 } , \dots , \pmb { u } _ { n } \right)$ of $V$. If we normalize the $\boldsymbol{u}_k$ , we obtain an ONB where $\| \boldsymbol { u } _ { k } \| = 1$ for $k = 1 , \dots , n$ 

**Example 3.12 (Gram-Schmidt Orthogonalization)**

![Figure 3.12(a)](<Images/03_Analytic_Geometry_image_014.jpg>)

(a) Original non-orthogonal basis vectors $\boldsymbol{b}_1,\boldsymbol{b}_2$.

![Figure 3.12(b)](<Images/03_Analytic_Geometry_image_015.jpg>)

(b) First new basis vector $\boldsymbol{u}_1=\boldsymbol{b}_1$ and projection of $\boldsymbol{b}_2$ onto the subspace spanned by $\boldsymbol{u}_1$.

![Figure 3.12(c)](<Images/03_Analytic_Geometry_image_016.jpg>)

(c) Orthogonal basis vectors $\boldsymbol{u}_1$ and $\boldsymbol{u}_2=\boldsymbol{b}_2-\pi_{\operatorname{span}[\boldsymbol{u}_1]}(\boldsymbol{b}_2)$.

Figure 3.12 Gram-Schmidt orthogonalization. (a) non-orthogonal basis $( b _ { 1 } , b _ { 2 } )$ of $\mathbb { R } ^ { 2 } ;$ (b) first constructed basis vector ${ \pmb u } _ { 1 }$ and orthogonal projection of $\pmb { b } _ { 2 }$ onto span $[ { \pmb u } _ { 1 } ] ;$ (c) orthogonal basis $( \mathbf { \boldsymbol { u } } _ { 1 } , \mathbf { \boldsymbol { u } } _ { 2 } )$ of $\mathbb { R } ^ { 2 }$ 

Consider a basis $( b _ { 1 } , b _ { 2 } )$ of $\mathbb { R } ^ { 2 }$ , where 

$$
\boldsymbol {b} _ {1} = \left[ \begin{array}{c} 2 \\ 0 \end{array} \right], \quad \boldsymbol {b} _ {2} = \left[ \begin{array}{c} 1 \\ 1 \end{array} \right];\tag{3.69}
$$

see also Figure 3.12(a). Using the Gram-Schmidt method, we construct an orthogonal basis $( \pmb { u } _ { 1 } , \pmb { u } _ { 2 } )$ of $\mathbb { R } ^ { 2 }$ as follows (assuming the dot product as the inner product): 

$$
\boldsymbol {u} _ {1} := \boldsymbol {b} _ {1} = \left[ \begin{array}{c} 2 \\ 0 \end{array} \right],\tag{3.70}
$$

$$
\boldsymbol {u} _ {2} := \boldsymbol {b} _ {2} - \pi_ {\text {span} [ \boldsymbol {u} _ {1} ]} (\boldsymbol {b} _ {2}) \stackrel {(3.45)} {=} \boldsymbol {b} _ {2} - \frac {\boldsymbol {u} _ {1} \boldsymbol {u} _ {1} ^ {\top}}{\| \boldsymbol {u} _ {1} \| ^ {2}} \boldsymbol {b} _ {2} = \left[ \begin{array}{c} 1 \\ 1 \end{array} \right] - \left[ \begin{array}{c c} 1 & 0 \\ 0 & 0 \end{array} \right] \left[ \begin{array}{c} 1 \\ 1 \end{array} \right] = \left[ \begin{array}{c} 0 \\ 1 \end{array} \right].\tag{3.71}
$$

These steps are illustrated in Figures 3.12(b) and (c). We immediately see that $\boldsymbol{u}_1$ and ${ \bf { u } } _ { 2 }$ are orthogonal, i.e., $\pmb { u } _ { 1 } ^ { \top } \pmb { u } _ { 2 } = 0$

### 3.8.4 Projection onto Affine Subspaces

Figure 3.13 Projection onto an affine space. (a) original setting; (b) setting shifted by −x<sub>0</sub> so that x − x<sub>0</sub> can be projected onto the direction space U; (c) projection is translated back to x<sub>0</sub> + π<sub>U</sub>(x − x<sub>0</sub>), which gives the final orthogonal projection $\pi _ { L } ( { \pmb x } )$

![image](<Images/03_Analytic_Geometry_Figure_3_13.png>)

(a) Setting.

(b) Reduce problem to projection π<sub>U</sub> onto vector subspace.

(c) Add support point back in to get affine projection $\pi _ { L }$

Thus far, we discussed how to project a vector onto a lower-dimensional subspace U. In the following, we provide a solution to projecting a vector onto an affine subspace. 

Consider the setting in Figure 3.13(a). We are given an affine space $L =$ $x _ { 0 } + U$ , where $b _ { 1 } , b _ { 2 }$ are basis vectors of $U$ . To determine the orthogonal projection $\pi _ { L } ( \pmb { x } )$ of x onto $L$, we transform the problem into a problem that we know how to solve: the projection onto a vector subspace. In order to get there, we subtract the support point $\boldsymbol{x}_0$ from x and from $L$, so that $L - x _ { 0 } = U$ is exactly the vector subspace $U$. We can now use the orthogonal projections onto a subspace we discussed in Section 3.8.2 and obtain the projection $\pi _ { U } ( \pmb { x } - \pmb { x } _ { 0 } )$ , which is illustrated in Figure 3.13(b). This projection can now be translated back into L by adding $\boldsymbol{x}_0$, such that we obtain the orthogonal projection onto an affine space $L$ as 

$$
\pi_ {L} (\boldsymbol {x}) = \boldsymbol {x} _ {0} + \pi_ {U} (\boldsymbol {x} - \boldsymbol {x} _ {0}),\tag{3.72}
$$

where $\pi _ { U } ( \cdot )$ is the orthogonal projection onto the subspace $U$ , i.e., the direction space of $L$; see Figure 3.13(c). 

From Figure 3.13, it is also evident that the distance of x from the affine space $L$ is identical to the distance of $\boldsymbol{x}-\boldsymbol{x}_0$ from U, i.e., 

$$
d (\boldsymbol {x}, L) = \left\| \boldsymbol {x} - \pi_ {L} (\boldsymbol {x}) \right\| = \left\| \boldsymbol {x} - \left(\boldsymbol {x} _ {0} + \pi_ {U} (\boldsymbol {x} - \boldsymbol {x} _ {0})\right) \right\|\tag{3.73a}
$$

$$
= d (\boldsymbol {x} - \boldsymbol {x} _ {0}, \pi_ {U} (\boldsymbol {x} - \boldsymbol {x} _ {0})) = d (\boldsymbol {x} - \boldsymbol {x} _ {0}, U).\tag{3.73b}
$$

We will use projections onto an affine subspace to derive the concept of a separating hyperplane in Section 12.1.

## 3.9 Rotations

![image](<Images/03_Analytic_Geometry_image_018.jpg>)

Figure 3.14 A rotation rotates objects in a plane about the origin. If the rotation angle is positive, we rotate counterclockwise.

![image](<Images/03_Analytic_Geometry_image_019.jpg>)

Figure 3.15 The robotic arm needs to rotate its joints in order to pick up objects or to place them correctly. Figure taken from (Deisenroth et al., 2015).

Length and angle preservation, as discussed in Section 3.4, are the two characteristics of linear mappings with orthogonal transformation matrices. In the following, we will have a closer look at specific orthogonal transformation matrices, which describe rotations. 

A rotation is a linear mapping (more specifically, an automorphism of a Euclidean vector space) that rotates a plane by an angle θ about the origin, i.e., the origin is a fixed point. For a positive angle $\theta>0$ , by common convention, we rotate in a counterclockwise direction. An example is shown in Figure 3.14, where the transformation matrix is 

$$
\boldsymbol {R} = \left[ \begin{array}{c c} - 0.38 & - 0.92 \\ 0.92 & - 0.38 \end{array} \right].\tag{3.74}
$$

Important application areas of rotations include computer graphics and robotics. For example, in robotics, it is often important to know how to rotate the joints of a robotic arm in order to pick up or place an object, see Figure 3.15. 

Figure 3.16 Rotation of the standard basis in $\mathbb { R } ^ { 2 }$ by an angle θ. 

![image](<Images/03_Analytic_Geometry_image_020.jpg>)

### 3.9.1 Rotations in $\mathbb { R } ^ { 2 }$

Consider the standard basis $\{\boldsymbol{e}_1=[1,0]^{\top},\boldsymbol{e}_2=[0,1]^{\top}\}$ of $\mathbb { R } ^ { 2 }$ , which defines the standard coordinate system in $\mathbb { R } ^ { 2 }$ . We aim to rotate this coordinate system by an angle θ as illustrated in Figure 3.16. Note that the rotated vectors are still linearly independent and, therefore, are a basis of $\mathbb { R } ^ { 2 }$ . This means that the rotation performs a basis change. 

Rotations Φ are linear mappings so that we can express them by a rotation matrix $R ( \theta )$ . Trigonometry (see Figure 3.16) allows us to determine the coordinates of the rotated axes (the image of Φ) with respect to the standard basis in $\mathbb { R } ^ { 2 }$ . We obtain 

$$
\Phi (\boldsymbol {e} _ {1}) = \left[ \begin{array}{c} \cos \theta \\ \sin \theta \end{array} \right], \quad \Phi (\boldsymbol {e} _ {2}) = \left[ \begin{array}{c} - \sin \theta \\ \cos \theta \end{array} \right].\tag{3.75}
$$

Therefore, the rotation matrix that performs the basis change into the rotated coordinates $R ( \theta )$ is given as 

$$
\boldsymbol {R} (\theta) = \left[ \begin{array}{c c} \Phi (\boldsymbol {e} _ {1}) & \Phi (\boldsymbol {e} _ {2}) \end{array} \right] = \left[ \begin{array}{c c} \cos \theta & - \sin \theta \\ \sin \theta & \cos \theta \end{array} \right].\tag{3.76}
$$

### 3.9.2 Rotations in $\mathbb { R } ^ { 3 }$

In contrast to the $\mathbb { R } ^ { 2 }$ case, in $\mathbb { R } ^ { 3 }$ we can rotate any two-dimensional plane about a one-dimensional axis. The easiest way to specify the general rotation matrix is to specify how the images of the standard basis $e _ { 1 } , e _ { 2 } , e _ { 3 }$ are supposed to be rotated, and making sure these images $R e _ { 1 } , R e _ { 2 } , R e _ { 3 }$ are orthonormal to each other. We can then obtain a general rotation matrix R by combining the images of the standard basis. 

To have a meaningful rotation angle, we have to define what “counterclockwise” means when we operate in more than two dimensions. We use the convention that a “counterclockwise” (planar) rotation about an axis refers to a rotation about an axis when we look at the axis “head on, from the end toward the origin”. In $\mathbb { R } ^ { 3 }$ , there are therefore three (planar) rotations about the three standard basis vectors (see Figure 3.17): 

![image](<Images/03_Analytic_Geometry_image_021.jpg>)

Figure 3.17 Rotation of a vector (gray) in R<sup>3</sup> by an angle θ about the e<sub>3</sub>-axis. The rotated vector is shown in blue.

- Rotation about the $e _ { 1 }$ -axis 

$$
\boldsymbol {R} _ {1} (\theta) = \left[ \begin{array}{c c c} \Phi (\boldsymbol {e} _ {1}) & \Phi (\boldsymbol {e} _ {2}) & \Phi (\boldsymbol {e} _ {3}) \end{array} \right] = \left[ \begin{array}{c c c} 1 & 0 & 0 \\ 0 & \cos \theta & - \sin \theta \\ 0 & \sin \theta & \cos \theta \end{array} \right].\tag{3.77}
$$

Here, the $e _ { 1 }$ coordinate is fixed, and the counterclockwise rotation is performed in the $e _ { 2 } e _ { 3 }$ plane. 

- Rotation about the $e_2$-axis 

$$
\boldsymbol {R} _ {2} (\theta) = \left[ \begin{array}{c c c} \cos \theta & 0 & \sin \theta \\ 0 & 1 & 0 \\ - \sin \theta & 0 & \cos \theta \end{array} \right].\tag{3.78}
$$

If we rotate the $e _ { 1 } e _ { 3 }$ plane about the $e _ { 2 }$ axis, we need to look at the $e _ { 2 }$ axis from its “tip” toward the origin. 

- Rotation about the $e _ { 3 }$ -axis 

$$
\boldsymbol {R} _ {3} (\theta) = \left[ \begin{array}{c c c} \cos \theta & - \sin \theta & 0 \\ \sin \theta & \cos \theta & 0 \\ 0 & 0 & 1 \end{array} \right].\tag{3.79}
$$

Figure 3.17 illustrates this. 

### 3.9.3 Rotations in n Dimensions

The generalization of rotations from 2D and 3D to n-dimensional Euclidean vector spaces can be intuitively described as fixing $n - 2$ dimensions and restrict the rotation to a two-dimensional plane in the n-dimensional space. As in the three-dimensional case, we can rotate any plane (two-dimensional subspace of $\mathbb{R}^{n}$). 

**Definition 3.11 (Givens Rotation).** Let V be an n-dimensional Euclidean vector space and $\Phi:V\to V$ an automorphism with transformation matrix 

$$
\boldsymbol {R} _ {i j} (\theta) := \left[ \begin{array}{c c c c c} \boldsymbol {I} _ {i - 1} & \boldsymbol {0} & \dots & \dots & \boldsymbol {0} \\ \boldsymbol {0} & \cos \theta & \boldsymbol {0} & - \sin \theta & \boldsymbol {0} \\ \boldsymbol {0} & \boldsymbol {0} & \boldsymbol {I} _ {j - i - 1} & \boldsymbol {0} & \boldsymbol {0} \\ \boldsymbol {0} & \sin \theta & \boldsymbol {0} & \cos \theta & \boldsymbol {0} \\ \boldsymbol {0} & \dots & \dots & \boldsymbol {0} & \boldsymbol {I} _ {n - j} \end{array} \right] \in \mathbb {R} ^ {n \times n},\tag{3.80}
$$

for $1\leqslant i<j\leqslant n$ and $\theta\in\mathbb{R}$. Then $R _ { i j } ( \theta )$ is called a Givens rotation. Essentially, $R _ { i j } ( \theta )$ is the identity matrix $\scriptstyle { { \cal { I } } _ { n } }$ with 

$$
r _ {i i} = \cos \theta , r _ {i j} = - \sin \theta , r _ {j i} = \sin \theta , r _ {j j} = \cos \theta .\tag{3.81}
$$

In two dimensions $( \mathrm { i } . \mathsf { e } . , n = 2 )$ , we obtain (3.76) as a special case. 

### 3.9.4 Properties of Rotations

Rotations exhibit a number of useful properties, which can be derived by considering them as orthogonal matrices (Definition 3.8): 

- Rotations preserve distances, i.e., $\| x - y \| = \| R _ { \theta } ( { \pmb x } ) - { \pmb R } _ { \theta } ( \pmb y ) \|$ . In other words, rotations leave the distance between any two points unchanged after the transformation. 

- Rotations preserve angles, i.e., the angle between $\scriptstyle { R _ { \theta } } x$ and $\scriptstyle R _ { \theta } { \boldsymbol { y } }$ equals the angle between x and $\boldsymbol{y}$. 

- Rotations in three (or more) dimensions are generally not commutative. Therefore, the order in which rotations are applied is important, even if they rotate about the same point. Only in two dimensions vector rotations are commutative, such that $R ( \phi ) R ( \theta ) = R ( \theta ) R ( \phi )$ for all $\phi , \theta \in [ 0 , 2 \pi )$ . They form an Abelian group (with multiplication) only if they rotate about the same point (e.g., the origin). 

## 3.10 Further Reading

In this chapter, we gave a brief overview of some of the important concepts of analytic geometry, which we will use in later chapters of the book. For a broader and more in-depth overview of some of the concepts we presented, we refer to the following excellent books: Axler (2015) and Boyd and Vandenberghe (2018). 

Inner products allow us to determine specific bases of vector (sub)spaces, where each vector is orthogonal to all others (orthogonal bases) using the Gram-Schmidt method. These bases are important in optimization and numerical algorithms for solving linear equation systems. For instance, Krylov subspace methods, such as conjugate gradients or the generalized minimal residual method (GMRES), minimize residual errors that are orthogonal to each other (Stoer and Burlirsch, 2002). 

In machine learning, inner products are important in the context of kernel methods (Schölkopf and Smola, 2002). Kernel methods exploit the fact that many linear algorithms can be expressed purely by inner product computations. Then, the “kernel trick” allows us to compute these inner products implicitly in a (potentially infinite-dimensional) feature space, without even knowing this feature space explicitly. This allowed the “non-linearization” of many algorithms used in machine learning, such as kernel-PCA (Schölkopf et al., 1997) for dimensionality reduction. Gaussian processes (Rasmussen and Williams, 2006) also fall into the category of kernel methods and are the current state of the art in probabilistic regression (fitting curves to data points). The idea of kernels is explored further in Chapter 12. 

Projections are often used in computer graphics, e.g., to generate shadows. In optimization, orthogonal projections are often used to (iteratively) minimize residual errors. This also has applications in machine learning, e.g., in linear regression where we want to find a (linear) function that minimizes the residual errors, i.e., the lengths of the orthogonal projections of the data onto the linear function (Bishop, 2006). We will investigate this further in Chapter 9. PCA (Pearson, 1901; Hotelling, 1933) also uses projections to reduce the dimensionality of high-dimensional data. We will discuss this in more detail in Chapter 10. 

## Exercises

**3.1.** Show that $\langle \cdot , \cdot \rangle$ defined for all $\pmb { x } = [ x _ { 1 } , x _ { 2 } ] ^ { \top } \in \mathbb { R } ^ { 2 }$ and $\pmb { y } = [ y _ { 1 } , y _ { 2 } ] ^ { \top } \in \mathbb { R } ^ { 2 }$ by 

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle := x _ {1} y _ {1} - (x _ {1} y _ {2} + x _ {2} y _ {1}) + 2 (x _ {2} y _ {2})
$$

is an inner product. 

**3.2.** Consider $\mathbb { R } ^ { 2 }$ with $\langle \cdot , \cdot \rangle$ defined for all x and $\pmb { y }$ in $\mathbb { R } ^ { 2 }$ as 

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle := \boldsymbol {x} ^ {\top} \underbrace {\left[ \begin{array}{c c} 2 & 0 \\ 1 & 2 \end{array} \right]} _ {=: \boldsymbol {A}} \boldsymbol {y}.
$$

Is $\langle \cdot , \cdot \rangle$ an inner product? 

**3.3.** Compute the distance between 

$$
\boldsymbol {x} = \left[ \begin{array}{c} 1 \\ 2 \\ 3 \end{array} \right], \quad \boldsymbol {y} = \left[ \begin{array}{c} - 1 \\ - 1 \\ 0 \end{array} \right]
$$

using 

**(a)** $\langle \pmb { x } , \pmb { y } \rangle : = \pmb { x } ^ { \top } \pmb { y }$ 

**(b)** $\langle\boldsymbol{x},\boldsymbol{y}\rangle:=\boldsymbol{x}^{\top}\boldsymbol{A}\boldsymbol{y}$, $\boldsymbol{A}:=\begin{bmatrix}2&1&0\\1&3&-1\\0&-1&2\end{bmatrix}$.

**3.4.** Compute the angle between 

$$
\boldsymbol {x} = \left[ \begin{array}{c} 1 \\ 2 \end{array} \right], \quad \boldsymbol {y} = \left[ \begin{array}{c} - 1 \\ - 1 \end{array} \right]
$$

using 

**(a)** $\langle \pmb { x } , \pmb { y } \rangle : = \pmb { x } ^ { \top } \pmb { y }$ 

**(b)**

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle := \boldsymbol {x} ^ {\top} \boldsymbol {B} \boldsymbol {y}, \quad \boldsymbol {B} := \left[ \begin{array}{c c} 2 & 1 \\ 1 & 3 \end{array} \right]
$$

**3.5.** Consider the Euclidean vector space $\mathbb { R } ^ { 5 }$ with the dot product. A subspace $U \subseteq \mathbb { R } ^ { 5 }$ and $\pmb { x } \in \mathbb { R } ^ { 5 }$ are given by 

$$
U = \operatorname{span} [ \left[ \begin{array}{c} 0 \\ - 1 \\ 2 \\ 0 \\ 2 \end{array} \right], \left[ \begin{array}{c} 1 \\ - 3 \\ 1 \\ - 1 \\ 2 \end{array} \right], \left[ \begin{array}{c} - 3 \\ 4 \\ 1 \\ 2 \\ 1 \end{array} \right], \left[ \begin{array}{c} - 1 \\ - 3 \\ 5 \\ 0 \\ 7 \end{array} \right] ], \quad \boldsymbol {x} = \left[ \begin{array}{c} - 1 \\ - 9 \\ - 1 \\ 4 \\ 1 \end{array} \right].
$$

**(a)** Determine the orthogonal projection $\pi _ { U } ( { \pmb x } )$ of x onto $U$ 

**(b)** Determine the distance $d ( { \pmb x } , U )$ 

**3.6.** Consider $\mathbb { R } ^ { 3 }$ with the inner product 

$$
\langle \boldsymbol {x}, \boldsymbol {y} \rangle := \boldsymbol {x} ^ {\top} \left[ \begin{array}{c c c} 2 & 1 & 0 \\ 1 & 2 & - 1 \\ 0 & - 1 & 2 \end{array} \right] \boldsymbol {y}.
$$

Furthermore, we define $e_1,e_2,e_3$ as the standard/canonical basis in $\mathbb { R } ^ { 3 }$ 

**(a)** Determine the orthogonal projection $\pi _ { U } ( e _ { 2 } )$ of $e _ { 2 }$ onto 

$$
U = \operatorname{span} [ \boldsymbol {e} _ {1}, \boldsymbol {e} _ {3} ].
$$

Hint: Orthogonality is defined through the inner product. 

**(b)** Compute the distance $d ( e _ { 2 } , U )$ 

**(c)** Draw the scenario: standard basis vectors and $\pi _ { U } ( e _ { 2 } )$ 

**3.7.** Let V be a vector space and π an endomorphism of V. 

**(a)** Prove that π is a projection if and only if $\operatorname { i d } _ { V } - \pi$ is a projection, where $\operatorname { i d } _ { V }$ is the identity endomorphism on $V$. 

**(b)** Assume now that π is a projection. Calculate Im $( \operatorname { i d } _ { V } - \pi )$ and $\ker ( \mathrm { i d } _ { V } - \pi )$ as a function of Im(π) and ker(π). 

**3.8.** Using the Gram-Schmidt method, turn the basis $B ~ = ~ ( b _ { 1 } , b _ { 2 } )$ of a two-dimensional subspace $U \subseteq \mathbb { R } ^ { 3 }$ into an ONB $C = ( c _ { 1 } , c _ { 2 } )$ of U, where 

$$
\boldsymbol {b} _ {1} := \left[ \begin{array}{c} 1 \\ 1 \\ 1 \end{array} \right], \quad \boldsymbol {b} _ {2} := \left[ \begin{array}{c} - 1 \\ 2 \\ 0 \end{array} \right].
$$

**3.9.** Let $n \in \mathbb { N }$ and let $x _ { 1 } , \ldots , x _ { n } > 0$ be n positive real numbers so that $x _ { 1 } +$ $\ldots + x _ { n } = 1$ . Use the Cauchy-Schwarz inequality and show that 

**(a)** $\sum_{i=1}^{n}x_i^2\geqslant\frac1n$.

**(b)** $\sum_{i=1}^{n}\frac{1}{x_i}\geqslant n^2$.

Hint: Think about the dot product on $\mathbb { R } ^ { n }$ . Then, choose specific vectors $\boldsymbol{x},\boldsymbol{y}\in\mathbb{R}^{n}$ and apply the Cauchy-Schwarz inequality. 

**3.10.** Rotate the vectors 

$$
\pmb {x} _ {1} := \left[ \begin{array}{c} 2 \\ 3 \end{array} \right], \quad \pmb {x} _ {2} := \left[ \begin{array}{c} 0 \\ - 1 \end{array} \right]
$$

by $30^{\circ}$
