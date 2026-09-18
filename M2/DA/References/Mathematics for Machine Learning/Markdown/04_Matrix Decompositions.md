# 4 Matrix Decompositions

![image](<Images/04_Matrix_Decompositions_image_001.jpg>)

In Chapters 2 and 3, we studied ways to manipulate and measure vectors, projections of vectors, and linear mappings. Mappings and transformations of vectors can be conveniently described as operations performed by matrices. Moreover, data is often represented in matrix form as well, e.g., where the rows of the matrix represent different people and the columns describe different features of the people, such as weight, height, and socioeconomic status. In this chapter, we present three aspects of matrices: how to summarize matrices, how matrices can be decomposed, and how these decompositions can be used for matrix approximations. 

We first consider methods that allow us to describe matrices with just a few numbers that characterize the overall properties of matrices. We will do this in the sections on determinants (Section 4.1) and eigenvalues (Section 4.2) for the important special case of square matrices. These characteristic numbers have important mathematical consequences and allow us to quickly grasp what useful properties a matrix has. From here we will proceed to matrix decomposition methods: An analogy for matrix decomposition is the factoring of numbers, such as the factoring of 21 into prime numbers $7\cdot3$. For this reason matrix decomposition is also often referred to as matrix factorization. Matrix decompositions are used to describe a matrix by means of a different representation using factors of interpretable matrices. 

We will first cover a square-root-like operation for symmetric, positive definite matrices, the Cholesky decomposition (Section 4.3). From here we will look at two related methods for factorizing matrices into canonical forms. The first one is known as matrix diagonalization (Section 4.4), which allows us to represent the linear mapping using a diagonal transformation matrix if we choose an appropriate basis. The second method, singular value decomposition (Section 4.5), extends this factorization to non-square matrices, and it is considered one of the fundamental concepts in linear algebra. These decompositions are helpful, as matrices representing numerical data are often very large and hard to analyze. We conclude the chapter with a systematic overview of the types of matrices and the characteristic properties that distinguish them in the form of a matrix taxonomy (Section 4.7). 

The methods that we cover in this chapter will become important in both subsequent mathematical chapters, such as Chapter 6, but also in applied chapters, such as dimensionality reduction in Chapters 10 or density estimation in Chapter 11. This chapter’s overall structure is depicted in the mind map of Figure 4.1.

![image](<Images/04_Matrix_Decompositions_Figure_4_1.png>)

Figure 4.1 A mind map of the concepts introduced in this chapter, along with where they are used in other parts of the book.

This material is published by Cambridge University Press as Mathematics for Machine Learning by Marc Peter Deisenroth, A. Aldo Faisal, and Cheng Soon Ong (2020). This version is free to view and download for personal use only. Not for re-distribution, re-sale, or use in derivative works. © by M. P. Deisenroth, A. A. Faisal, and C. S. Ong, 2024. https://mml-book.com.

## 4.1 Determinant and Trace

> The determinant notation $|A|$ must not be confused with the absolute value.

Determinants are important concepts in linear algebra. A determinant is a mathematical object in the analysis and solution of systems of linear equations. Determinants are only defined for square matrices $A \in \mathbb { R } ^ { n \times n }$, i.e., matrices with the same number of rows and columns. In this book, we write the determinant as det(A) or sometimes as $| A |$ so that 

$$
\det (\boldsymbol {A}) = \left| \begin{array}{c c c c} a _ {1 1} & a _ {1 2} & \ldots & a _ {1 n} \\ a _ {2 1} & a _ {2 2} & \ldots & a _ {2 n} \\ \vdots & & \ddots & \vdots \\ a _ {n 1} & a _ {n 2} & \ldots & a _ {n n} \end{array} \right|.\tag{4.1}
$$

The determinant of a square matrix $A \in \mathbb { R } ^ { n \times n }$ is a function that maps A onto a real number. Before providing a definition of the determinant for general $n \times n$ matrices, let us have a look at some motivating examples, and define determinants for some special matrices. 

**Example 4.1 (Testing for Matrix Invertibility)**

Let us begin with exploring if a square matrix A is invertible (see Section 2.2.2). For the smallest cases, we already know when a matrix is invertible. If A is a $1 \times 1$ matrix, i.e., it is a scalar number, then $\begin{array} { r } { \pmb { A } = \pmb { a } \implies \pmb { A } ^ { - 1 } = \frac { 1 } { a } } \end{array}$ . Thus $\begin{array} { r } { a \ \frac { 1 } { a } = 1 } \end{array}$ holds, if and only if $a \neq 0$ 

For $2 \times 2$ matrices, by the definition of the inverse (Definition 2.3), we know that $\pmb { A } \pmb { A } ^ { - 1 } = \pmb { I }$ . Then, with (2.24), the inverse of A is 

$$
\pmb {A} ^ {- 1} = \frac {1}{a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1}} \left[ \begin{array}{c c} a _ {2 2} & - a _ {1 2} \\ - a _ {2 1} & a _ {1 1} \end{array} \right].\tag{4.2}
$$

Hence, A is invertible if and only if 

$$
a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1} \neq 0.\tag{4.3}
$$

This quantity is the determinant of $A \in \mathbb { R } ^ { 2 \times 2 }$ , i.e., 

$$
\det (\boldsymbol {A}) = \left| \begin{array}{c c} a _ {1 1} & a _ {1 2} \\ a _ {2 1} & a _ {2 2} \end{array} \right| = a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1}.\tag{4.4}
$$

Example 4.1 points already at the relationship between determinants and the existence of inverse matrices. The next theorem states the same result for $n \times n$ matrices. 

**Theorem 4.1.** For any square matrix $A \in \mathbb { R } ^ { n \times n }$ it holds that A is invertible if and only if $\det(A)\neq0$. 

We have explicit (closed-form) expressions for determinants of small matrices in terms of the elements of the matrix. For $n = 1$ 

$$
\det (\boldsymbol {A}) = \det (a _ {1 1}) = a _ {1 1}.\tag{4.5}
$$

For $n=2$, 

$$
\det (\boldsymbol {A}) = \left| \begin{array}{c c} a _ {1 1} & a _ {1 2} \\ a _ {2 1} & a _ {2 2} \end{array} \right| = a _ {1 1} a _ {2 2} - a _ {1 2} a _ {2 1},\tag{4.6}
$$

which we have observed in the preceding example. 

For $n = 3$ (known as Sarrus’ rule), 

$$
\begin{array}{r l} & {\left| \begin{array}{l l l} a _ {1 1} & a _ {1 2} & a _ {1 3} \\ a _ {2 1} & a _ {2 2} & a _ {2 3} \\ a _ {3 1} & a _ {3 2} & a _ {3 3} \end{array} \right| = a _ {1 1} a _ {2 2} a _ {3 3} + a _ {2 1} a _ {3 2} a _ {1 3} + a _ {3 1} a _ {1 2} a _ {2 3}} \\ & {- a _ {3 1} a _ {2 2} a _ {1 3} - a _ {1 1} a _ {3 2} a _ {2 3} - a _ {2 1} a _ {1 2} a _ {3 3}.} \end{array}\tag{4.7}
$$

For a memory aid of the product terms in Sarrus’ rule, try tracing the elements of the triple products in the matrix.

We call a square matrix $\boldsymbol T$ an upper-triangular matrix if $T_{ij}=0$ for $i>j$, i.e., the matrix is zero below its diagonal. Analogously, we define a lower-triangular matrix as a matrix with zeros above its diagonal. For a triangular matrix $\boldsymbol T\in\mathbb R^{n\times n}$, the determinant is the product of the diagonal elements, i.e.,

$$
\det (\boldsymbol {T}) = \prod_ {i = 1} ^ {n} T _ {i i}.\tag{4.8}
$$

**Example 4.2 (Determinants as Measures of Volume)**

The notion of a determinant is natural when we consider it as a mapping from a set of $n$ vectors spanning an object in $\mathbb R^n$. It turns out that the determinant $\det(\boldsymbol A)$ is the signed volume of an $n$-dimensional parallelepiped formed by columns of the matrix $\boldsymbol A$.

> The determinant is the signed volume of the parallelepiped formed by the columns of the matrix.

For $n=2$, the columns of the matrix form a parallelogram; see Figure 4.2. As the angle between vectors gets smaller, the area of a parallelogram shrinks, too. Consider two vectors $\boldsymbol b,\boldsymbol g$ that form the columns of a matrix $\boldsymbol A=[\boldsymbol b,\boldsymbol g]$. Then, the absolute value of the determinant of $\boldsymbol A$ is the area of the parallelogram with vertices $\boldsymbol 0,\boldsymbol b,\boldsymbol g,\boldsymbol b+\boldsymbol g$. In particular, if $\boldsymbol b,\boldsymbol g$ are linearly dependent so that $\boldsymbol b=\lambda\boldsymbol g$ for some $\lambda\in\mathbb R$, they no longer form a two-dimensional parallelogram. Therefore, the corresponding area is 0. On the contrary, if $\boldsymbol b,\boldsymbol g$ are linearly independent and are multiples of the canonical basis vectors $\boldsymbol e_1,\boldsymbol e_2$ then they can be written as $\boldsymbol b=\begin{bmatrix}b\\0\end{bmatrix}$ and $\boldsymbol g=\begin{bmatrix}0\\g\end{bmatrix}$, and the determinant is $\begin{vmatrix}b&0\\0&g\end{vmatrix}=bg-0=bg$.

Figure 4.2 The area of the parallelogram (shaded region) spanned by the vectors $\boldsymbol b$ and $\boldsymbol g$ is $|\det([\boldsymbol b,\boldsymbol g])|$.

![Figure 4.2](<Images/04_Matrix_Decompositions_image_003.jpg>)

The sign of the determinant indicates the orientation of the spanning vectors $\boldsymbol b,\boldsymbol g$ with respect to the standard basis $(\boldsymbol e_1,\boldsymbol e_2)$. In our figure, flipping the order to $\boldsymbol g,\boldsymbol b$ swaps the columns of $\boldsymbol A$ and reverses the orientation of the shaded area. This becomes the familiar formula: area = height $\times$ length. This intuition extends to higher dimensions. In $\mathbb R^3$, we consider three vectors $\boldsymbol r,\boldsymbol b,\boldsymbol g\in\mathbb R^3$ spanning the edges of a parallelepiped, i.e., a solid with faces that are parallel parallelograms (see Figure 4.3). The absolute value of the determinant of the $3\times3$ matrix $[\boldsymbol r,\boldsymbol b,\boldsymbol g]$ is the volume of the solid. Thus, the determinant acts as a function that measures the signed volume formed by column vectors composed in a matrix.

Figure 4.3 The volume of the parallelepiped (shaded volume) spanned by vectors $\boldsymbol r,\boldsymbol b,\boldsymbol g$ is $|\det([\boldsymbol r,\boldsymbol b,\boldsymbol g])|$.

![Figure 4.3](<Images/04_Matrix_Decompositions_Figure_4_3.png>)

> The sign of the determinant indicates the orientation of the spanning vectors.

Consider the three linearly independent vectors $\boldsymbol r,\boldsymbol g,\boldsymbol b\in\mathbb R^3$ given as

$$
\boldsymbol {r} = \left[ \begin{array}{c} 2 \\ 0 \\ - 8 \end{array} \right], \quad \boldsymbol {g} = \left[ \begin{array}{c} 6 \\ 1 \\ 0 \end{array} \right], \quad \boldsymbol {b} = \left[ \begin{array}{c} 1 \\ 4 \\ - 1 \end{array} \right].\tag{4.9}
$$

Writing these vectors as the columns of a matrix

$$
\boldsymbol {A} = [ \boldsymbol {r}, \boldsymbol {g}, \boldsymbol {b} ] = \left[ \begin{array}{c c c} 2 & 6 & 1 \\ 0 & 1 & 4 \\ - 8 & 0 & - 1 \end{array} \right]\tag{4.10}
$$

allows us to compute the desired volume as

$$
V = | \det (\boldsymbol {A}) | = 186.\tag{4.11}
$$

Computing the determinant of an $n\times n$ matrix requires a general algorithm to solve the cases for $n>3$, which we are going to explore in the following. Theorem 4.2 below reduces the problem of computing the determinant of an $n\times n$ matrix to computing the determinant of $(n-1)\times(n-1)$ matrices. By recursively applying the Laplace expansion (Theorem 4.2), we can therefore compute determinants of $n\times n$ matrices by ultimately computing determinants of $2\times2$ matrices.

**Theorem 4.2 (Laplace Expansion).** Consider a matrix $\boldsymbol A\in\mathbb R^{n\times n}$. Then, for all $j=1,\dots,n$:

1. Expansion along column $j$

$$
\det (\boldsymbol {A}) = \sum_ {k = 1} ^ {n} (- 1) ^ {k + j} a _ {k j} \det (\boldsymbol {A} _ {k, j}).\tag{4.12}
$$

2. Expansion along row $j$

$$
\det (\boldsymbol {A}) = \sum_ {k = 1} ^ {n} (- 1) ^ {k + j} a _ {j k} \det (\boldsymbol {A} _ {j, k}).\tag{4.13}
$$

Here $\boldsymbol A_{k,j}\in\mathbb R^{(n-1)\times(n-1)}$ is the submatrix of $\boldsymbol A$ that we obtain when deleting row $k$ and column $j$.

> $\det(\boldsymbol A_{k,j})$ is called a minor and $(-1)^{k+j}\det(\boldsymbol A_{k,j})$ a cofactor.

**Example 4.3 (Laplace Expansion)**

Let us compute the determinant of

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 1 & 2 & 3 \\ 3 & 1 & 2 \\ 0 & 0 & 1 \end{array} \right]\tag{4.14}
$$

using the Laplace expansion along the first row. Applying (4.13) yields

$$
\begin{array}{c} \left| \begin{array}{c c c} 1 & 2 & 3 \\ 3 & 1 & 2 \\ 0 & 0 & 1 \end{array} \right| = (- 1) ^ {1 + 1} \cdot 1 \left| \begin{array}{c c} 1 & 2 \\ 0 & 1 \end{array} \right| \\ + (- 1) ^ {1 + 2} \cdot 2 \left| \begin{array}{c c} 3 & 2 \\ 0 & 1 \end{array} \right| + (- 1) ^ {1 + 3} \cdot 3 \left| \begin{array}{c c} 3 & 1 \\ 0 & 0 \end{array} \right|. \end{array}\tag{4.15}
$$

We use (4.6) to compute the determinants of all $2\times2$ matrices and obtain

$$
\det (\boldsymbol {A}) = 1 (1 - 0) - 2 (3 - 0) + 3 (0 - 0) = - 5.\tag{4.16}
$$

For completeness we can compare this result to computing the determinant using Sarrus’ rule (4.7):

$$
\det (\boldsymbol {A}) = 1 \cdot 1 \cdot 1 + 3 \cdot 0 \cdot 3 + 0 \cdot 2 \cdot 2 - 0 \cdot 1 \cdot 3 - 1 \cdot 0 \cdot 2 - 3 \cdot 2 \cdot 1 = 1 - 6 = - 5.\tag{4.17}
$$

For $\boldsymbol A\in\mathbb R^{n\times n}$ the determinant exhibits the following properties:

- The determinant of a matrix product is the product of the corresponding determinants, $\det(\boldsymbol A\boldsymbol B)=\det(\boldsymbol A)\det(\boldsymbol B)$.
- Determinants are invariant to transposition, i.e., $\det(\boldsymbol A)=\det(\boldsymbol A^\top)$.
- If $\boldsymbol A$ is regular (invertible), then $\det(\boldsymbol A^{-1})=\frac{1}{\det(\boldsymbol A)}$.
- Similar matrices (Definition 2.22) possess the same determinant. Therefore, for a linear mapping $\Phi:V\to V$ all transformation matrices $\boldsymbol A_\Phi$ of $\Phi$ have the same determinant. Thus, the determinant is invariant to the choice of basis of a linear mapping.
- Adding a multiple of a column/row to another one does not change $\det(\boldsymbol A)$.
- Multiplication of a column/row with $\lambda\in\mathbb R$ scales $\det(\boldsymbol A)$ by $\lambda$. In particular, $\det(\lambda\boldsymbol A)=\lambda^n\det(\boldsymbol A)$.
- Swapping two rows/columns changes the sign of $\det(\boldsymbol A)$.

Because of the last three properties, we can use Gaussian elimination (see Section 2.1) to compute $\det(\boldsymbol A)$ by bringing $\boldsymbol A$ into row-echelon form. We can stop Gaussian elimination when we have $\boldsymbol A$ in a triangular form where the elements below the diagonal are all 0. Recall from (4.8) that the determinant of a triangular matrix is the product of the diagonal elements.

**Theorem 4.3.** A square matrix $\boldsymbol A\in\mathbb R^{n\times n}$ has $\det(\boldsymbol A)\neq0$ if and only if $\operatorname{rk}(\boldsymbol A)=n$. In other words, $\boldsymbol A$ is invertible if and only if it is full rank.

When mathematics was mainly performed by hand, the determinant calculation was considered an essential way to analyze matrix invertibility. However, contemporary approaches in machine learning use direct numerical methods that superseded the explicit calculation of the determinant. For example, in Chapter 2, we learned that inverse matrices can be computed by Gaussian elimination. Gaussian elimination can thus be used to compute the determinant of a matrix.

Determinants will play an important theoretical role for the following sections, especially when we learn about eigenvalues and eigenvectors (Section 4.2) through the characteristic polynomial.

**Definition 4.4.** The trace of a square matrix $\boldsymbol A\in\mathbb R^{n\times n}$ is defined as

$$
\operatorname{tr} (\boldsymbol {A}) := \sum_ {i = 1} ^ {n} a _ {i i},\tag{4.18}
$$

i.e., the trace is the sum of the diagonal elements of $\boldsymbol A$.

The trace satisfies the following properties:

- $\operatorname{tr}(\boldsymbol A+\boldsymbol B)=\operatorname{tr}(\boldsymbol A)+\operatorname{tr}(\boldsymbol B)$ for $\boldsymbol A,\boldsymbol B\in\mathbb R^{n\times n}$
- $\operatorname{tr}(\alpha\boldsymbol A)=\alpha\operatorname{tr}(\boldsymbol A)$, $\alpha\in\mathbb R$ for $\boldsymbol A\in\mathbb R^{n\times n}$
- $\operatorname{tr}(\boldsymbol I_n)=n$
- $\operatorname{tr}(\boldsymbol A\boldsymbol B)=\operatorname{tr}(\boldsymbol B\boldsymbol A)$ for $\boldsymbol A\in\mathbb R^{n\times k}$, $\boldsymbol B\in\mathbb R^{k\times n}$

It can be shown that only one function satisfies these four properties together – the trace (Gohberg et al., 2012).

The properties of the trace of matrix products are more general. Specifically, the trace is invariant under cyclic permutations, i.e.,

$$
\operatorname{tr} (\boldsymbol {A K L}) = \operatorname{tr} (\boldsymbol {K L A})\tag{4.19}
$$

for matrices $\boldsymbol A\in\mathbb R^{a\times k}$, $\boldsymbol K\in\mathbb R^{k\times l}$, $\boldsymbol L\in\mathbb R^{l\times a}$. This property generalizes to products of an arbitrary number of matrices. As a special case of (4.19), it follows that for two vectors $\boldsymbol x,\boldsymbol y\in\mathbb R^n$

$$
\operatorname{tr} \left(\boldsymbol {x} \boldsymbol {y} ^ {\top}\right) = \operatorname{tr} \left(\boldsymbol {y} ^ {\top} \boldsymbol {x}\right) = \boldsymbol {y} ^ {\top} \boldsymbol {x} \in \mathbb {R}.\tag{4.20}
$$

> The trace is invariant under cyclic permutations.

Given a linear mapping $\Phi:V\to V$, where $V$ is a vector space, we define the trace of this map by using the trace of matrix representation of $\Phi$. For a given basis of $V$, we can describe $\Phi$ by means of the transformation matrix $\boldsymbol A$. Then the trace of $\Phi$ is the trace of $\boldsymbol A$. For a different basis of $V$, it holds that the corresponding transformation matrix $\boldsymbol B$ of $\Phi$ can be obtained by a basis change of the form $\boldsymbol S^{-1}\boldsymbol A\boldsymbol S$ for suitable $\boldsymbol S$ (see Section 2.7.2). For the corresponding trace of $\Phi$, this means

$$
\operatorname{tr} (\boldsymbol {B}) = \operatorname{tr} \left(\boldsymbol {S} ^ {- 1} \boldsymbol {A} \boldsymbol {S}\right) \stackrel {(4.19)} {=} \operatorname{tr} \left(\boldsymbol {A} \boldsymbol {S} \boldsymbol {S} ^ {- 1}\right) = \operatorname{tr} (\boldsymbol {A}).\tag{4.21}
$$

Hence, while matrix representations of linear mappings are basis dependent the trace of a linear mapping $\Phi$ is independent of the basis.

In this section, we covered determinants and traces as functions characterizing a square matrix. Taking together our understanding of determinants and traces we can now define an important equation describing a matrix $\boldsymbol A$ in terms of a polynomial, which we will use extensively in the following sections.

**Definition 4.5 (Characteristic Polynomial).** For $\lambda\in\mathbb R$ and a square matrix $\boldsymbol A\in\mathbb R^{n\times n}$

$$
\displaystyle p_{\boldsymbol A}(\lambda):=\det(\boldsymbol A-\lambda\boldsymbol I)\tag{4.22a}
$$

$$
\displaystyle \phantom{p_{\boldsymbol A}(\lambda)}=c_0+c_1\lambda+c_2\lambda^2+\dots+c_{n-1}\lambda^{n-1}+(-1)^n\lambda^n,\tag{4.22b}
$$

$c_0,\dots,c_{n-1}\in\mathbb R$, is the characteristic polynomial of $\boldsymbol A$. In particular,

$$
c _ {0} = \det (\boldsymbol {A}),\tag{4.23}
$$

$$
c _ {n - 1} = (- 1) ^ {n - 1} \operatorname{tr} (\boldsymbol {A}).\tag{4.24}
$$

The characteristic polynomial (4.22a) will allow us to compute eigenvalues and eigenvectors, covered in the next section.

## 4.2 Eigenvalues and Eigenvectors

We will now get to know a new way to characterize a matrix and its associated linear mapping. Recall from Section 2.7.1 that every linear mapping has a unique transformation matrix given an ordered basis. We can interpret linear mappings and their associated transformation matrices by performing an “eigen” analysis. As we will see, the eigenvalues of a linear mapping will tell us how a special set of vectors, the eigenvectors, is transformed by the linear mapping. 

> Eigen is a German word meaning “characteristic”, “self”, or “own”.

**Definition 4.6.** Let $\pmb { A } \in \mathbb { R } ^ { n \times n }$ be a square matrix. Then $\lambda \in \mathbb { R }$ is an eigenvalue of A and $\pmb { x } \in \mathbb { R } ^ { n } \backslash \{ \mathbf { 0 } \}$ is the corresponding eigenvector of A if 

$$
\boldsymbol {A} \boldsymbol {x} = \lambda \boldsymbol {x}.\tag{4.25}
$$

We call (4.25) the eigenvalue equation. 

**Remark.** In the linear algebra literature and software, it is often a convention that eigenvalues are sorted in descending order, so that the largest eigenvalue and associated eigenvector are called the first eigenvalue and its associated eigenvector, and the second largest called the second eigenvalue and its associated eigenvector, and so on. However, textbooks and publications may have different or no notion of orderings. We do not want to presume an ordering in this book if not stated explicitly. 

The following statements are equivalent: 

- $\lambda$ is an eigenvalue of $\boldsymbol A\in\mathbb R^{n\times n}$.
- There exists an $\boldsymbol x\in\mathbb R^n\backslash\{\boldsymbol0\}$ with $\boldsymbol A\boldsymbol x=\lambda\boldsymbol x$, or equivalently, $(\boldsymbol A-\lambda\boldsymbol I_n)\boldsymbol x=\boldsymbol0$ can be solved non-trivially, i.e., $\boldsymbol x\neq\boldsymbol0$.
- $\operatorname{rk}(\boldsymbol A-\lambda\boldsymbol I_n)<n$.
- $\det(\boldsymbol A-\lambda\boldsymbol I_n)=0$.

**Definition 4.7 (Collinearity and Codirection).** Two vectors that point in the same direction are called codirected. Two vectors are collinear if they point in the same or the opposite direction. 

**Remark (Non-uniqueness of eigenvectors).** If x is an eigenvector of A associated with eigenvalue $\lambda ,$ then for any $c \in \mathbb { R } \backslash \{ 0 \}$ it holds that cx is an eigenvector of A with the same eigenvalue since 

$$
\boldsymbol {A} (c \boldsymbol {x}) = c \boldsymbol {A} \boldsymbol {x} = c \lambda \boldsymbol {x} = \lambda (c \boldsymbol {x}).\tag{4.26}
$$

Thus, all vectors that are collinear to x are also eigenvectors of A.

**Theorem 4.8.** $\lambda\in\mathbb R$ is an eigenvalue of $\boldsymbol A\in\mathbb R^{n\times n}$ if and only if $\lambda$ is a root of the characteristic polynomial $p_{\boldsymbol A}(\lambda)$ of $\boldsymbol A$.

**Definition 4.9.** Let a square matrix $\boldsymbol A$ have an eigenvalue $\lambda_i$. The algebraic multiplicity of $\lambda_i$ is the number of times the root appears in the characteristic polynomial.

**Definition 4.10 (Eigenspace and Eigenspectrum).** For $\boldsymbol A\in\mathbb R^{n\times n}$, the set of all eigenvectors of $\boldsymbol A$ associated with an eigenvalue $\lambda$ spans a subspace of $\mathbb R^n$, which is called the eigenspace of $\boldsymbol A$ with respect to $\lambda$ and is denoted by $E_\lambda$. The set of all eigenvalues of $\boldsymbol A$ is called the eigenspectrum, or just spectrum, of $\boldsymbol A$.

If $\lambda$ is an eigenvalue of $\boldsymbol A\in\mathbb R^{n\times n}$, then the corresponding eigenspace $E_\lambda$ is the solution space of the homogeneous system of linear equations $(\boldsymbol A-\lambda\boldsymbol I)\boldsymbol x=\boldsymbol0$. Geometrically, the eigenvector corresponding to a nonzero eigenvalue points in a direction that is stretched by the linear mapping. The eigenvalue is the factor by which it is stretched. If the eigenvalue is negative, the direction of the stretching is flipped.

**Example 4.4 (The Case of the Identity Matrix)**

The identity matrix $\boldsymbol I\in\mathbb R^{n\times n}$ has characteristic polynomial $p_{\boldsymbol I}(\lambda)=\det(\boldsymbol I-\lambda\boldsymbol I)=(1-\lambda)^n=0$, which has only one eigenvalue $\lambda=1$ that occurs $n$ times. Moreover, $\boldsymbol I\boldsymbol x=\lambda\boldsymbol x=1\boldsymbol x$ holds for all vectors $\boldsymbol x\in\mathbb R^n\backslash\{\boldsymbol0\}$. Because of this, the sole eigenspace $E_1$ of the identity matrix spans $n$ dimensions, and all $n$ standard basis vectors of $\mathbb R^n$ are eigenvectors of $\boldsymbol I$.

Useful properties regarding eigenvalues and eigenvectors include the following:

- A matrix $\boldsymbol A$ and its transpose $\boldsymbol A^\top$ possess the same eigenvalues, but not necessarily the same eigenvectors.
- The eigenspace $E_\lambda$ is the null space of $\boldsymbol A-\lambda\boldsymbol I$ since

$$
\boldsymbol {A} \boldsymbol {x} = \lambda \boldsymbol {x} \iff \boldsymbol {A} \boldsymbol {x} - \lambda \boldsymbol {x} = \mathbf {0}\tag{4.27a}
$$

$$
\Longleftrightarrow (\boldsymbol {A} - \lambda \boldsymbol {I}) \boldsymbol {x} = \boldsymbol {0} \Longleftrightarrow \boldsymbol {x} \in \ker (\boldsymbol {A} - \lambda \boldsymbol {I}).\tag{4.27b}
$$

- Similar matrices (see Definition 2.22) possess the same eigenvalues. Therefore, a linear mapping $\Phi$ has eigenvalues that are independent of the choice of basis of its transformation matrix. This makes eigenvalues, together with the determinant and the trace, key characteristic parameters of a linear mapping as they are all invariant under basis change.
- Symmetric, positive definite matrices always have positive, real eigenvalues.

**Example 4.5 (Computing Eigenvalues, Eigenvectors, and Eigenspaces)**

Let us find the eigenvalues and eigenvectors of the $2\times2$ matrix

$$
\boldsymbol {A} = \left[ \begin{array}{c c} 4 & 2 \\ 1 & 3 \end{array} \right].\tag{4.28}
$$

**Step 1: Characteristic Polynomial.** From our definition of the eigenvector $\boldsymbol x\neq\boldsymbol0$ and eigenvalue $\lambda$ of $\boldsymbol A$, there will be a vector such that $\boldsymbol A\boldsymbol x=\lambda\boldsymbol x$, i.e., $(\boldsymbol A-\lambda\boldsymbol I)\boldsymbol x=\boldsymbol0$. Since $\boldsymbol x\neq\boldsymbol0$, this requires that the kernel (null space) of $\boldsymbol A-\lambda\boldsymbol I$ contains more elements than just $\boldsymbol0$. This means that $\boldsymbol A-\lambda\boldsymbol I$ is not invertible and therefore $\det(\boldsymbol A-\lambda\boldsymbol I)=0$. Hence, we need to compute the roots of the characteristic polynomial (4.22a) to find the eigenvalues.

**Step 2: Eigenvalues.** The characteristic polynomial is

$$
p _ {\boldsymbol {A}} (\lambda) = \det (\boldsymbol {A} - \lambda \boldsymbol {I})\tag{4.29a}
$$

$$
= \det \left(\left[ \begin{array}{c c} 4 & 2 \\ 1 & 3 \end{array} \right] - \left[ \begin{array}{c c} \lambda & 0 \\ 0 & \lambda \end{array} \right]\right) = \left| \begin{array}{c c} 4 - \lambda & 2 \\ 1 & 3 - \lambda \end{array} \right|\tag{4.29b}
$$

$$
= (4 - \lambda) (3 - \lambda) - 2 \cdot 1.\tag{4.29c}
$$

We factorize the characteristic polynomial and obtain

$$
p (\lambda) = (4 - \lambda) (3 - \lambda) - 2 \cdot 1 = 10 - 7 \lambda + \lambda^ {2} = (2 - \lambda) (5 - \lambda)\tag{4.30}
$$

giving the roots $\lambda_1=2$ and $\lambda_2=5$.

**Step 3: Eigenvectors and Eigenspaces.** We find the eigenvectors that correspond to these eigenvalues by looking at vectors $\boldsymbol x$ such that

$$
\left[ \begin{array}{c c} 4 - \lambda & 2 \\ 1 & 3 - \lambda \end{array} \right] \boldsymbol {x} = \boldsymbol {0}.\tag{4.31}
$$

For $\lambda=5$ we obtain

$$
\left[ \begin{array}{c c} 4 - 5 & 2 \\ 1 & 3 - 5 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \end{array} \right] = \left[ \begin{array}{c c} - 1 & 2 \\ 1 & - 2 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \end{array} \right] = \mathbf {0}.\tag{4.32}
$$

We solve this homogeneous system and obtain a solution space

$$
E _ {5} = \operatorname{span} [ \left[ \begin{array}{c} 2 \\ 1 \end{array} \right] ].\tag{4.33}
$$

This eigenspace is one-dimensional as it possesses a single basis vector.

Analogously, we find the eigenvector for $\lambda=2$ by solving the homogeneous system of equations

$$
\left[ \begin{array}{c c} 4 - 2 & 2 \\ 1 & 3 - 2 \end{array} \right] \boldsymbol {x} = \left[ \begin{array}{c c} 2 & 2 \\ 1 & 1 \end{array} \right] \boldsymbol {x} = \boldsymbol {0}.\tag{4.34}
$$

This means any vector $\boldsymbol x=\begin{bmatrix}x_1\\x_2\end{bmatrix}$, where $x_2=-x_1$, such as $\begin{bmatrix}1\\-1\end{bmatrix}$, is an eigenvector with eigenvalue 2. The corresponding eigenspace is given as

$$
E _ {2} = \operatorname{span} [ \left[ \begin{array}{c} 1 \\ - 1 \end{array} \right] ].\tag{4.35}
$$

The two eigenspaces $E _ { 5 }$ and $E _ { 2 }$ in Example 4.5 are one-dimensional as they are each spanned by a single vector. However, in other cases we may have multiple identical eigenvalues (see Definition 4.9) and the eigenspace may have more than one dimension. 

**Definition 4.11.** Let $\lambda _ { i }$ be an eigenvalue of a square matrix A. Then the geometric multiplicity of $\lambda _ { i }$ is the number of linearly independent eigenvectors associated with $\lambda _ { i }$. In other words, it is the dimensionality of the eigenspace spanned by the eigenvectors associated with $\lambda _ { i }$.

**Remark.** A specific eigenvalue’s geometric multiplicity must be at least one because every eigenvalue has at least one associated eigenvector. An eigenvalue’s geometric multiplicity cannot exceed its algebraic multiplicity, but it may be lower. 

**Example 4.6**

The matrix $A = { \left[ \begin{array} { l l } { 2 } & { 1 } \\ { 0 } & { 2 } \end{array} \right] }$ has two repeated eigenvalues $\lambda _ { 1 } = \lambda _ { 2 } = 2$ and an algebraic multiplicity of 2. The eigenvalue has, however, only one distinct unit eigenvector $\pmb { x } _ { 1 } = \left[ \begin{array} { l } { 1 } \\ { 0 } \end{array} \right]$ and, thus, geometric multiplicity 1.

### Graphical Intuition in Two Dimensions

Let us gain some intuition for determinants, eigenvectors, and eigenvalues using different linear mappings. Figure 4.4 depicts five transformation matrices $\boldsymbol A_1,\dots,\boldsymbol A_5$ and their impact on a square grid of points, centered at the origin:

- $\boldsymbol A_1=\begin{bmatrix}\frac12&0\\0&2\end{bmatrix}$. The direction of the two eigenvectors correspond to the canonical basis vectors in $\mathbb R^2$, i.e., to two cardinal axes. The vertical axis is extended by a factor of 2 (eigenvalue $\lambda_1=2$), and the horizontal axis is compressed by factor $\frac12$ (eigenvalue $\lambda_2=\frac12$). The mapping is area preserving ($\det(\boldsymbol A_1)=1=2\cdot\frac12$).
- $\boldsymbol A_2=\begin{bmatrix}1&\frac12\\0&1\end{bmatrix}$ corresponds to a shearing mapping, i.e., it shears the points along the horizontal axis to the right if they are on the positive half of the vertical axis, and to the left vice versa. This mapping is area preserving ($\det(\boldsymbol A_2)=1$). The eigenvalue $\lambda_1=1=\lambda_2$ is repeated and the eigenvectors are collinear (drawn here for emphasis in two opposite directions). This indicates that the mapping acts only along one direction (the horizontal axis).
- $\boldsymbol A_3=\begin{bmatrix}\cos(\frac\pi6)&-\sin(\frac\pi6)\\\sin(\frac\pi6)&\cos(\frac\pi6)\end{bmatrix}=\frac12\begin{bmatrix}\sqrt3&-1\\1&\sqrt3\end{bmatrix}$. The matrix $\boldsymbol A_3$ rotates the points by $\frac\pi6\,\mathrm{rad}=30^\circ$ counter-clockwise and has only complex eigenvalues, reflecting that the mapping is a rotation (hence, no eigenvectors are drawn). A rotation has to be volume preserving, and so the determinant is 1. For more details on rotations, we refer to Section 3.9.
- $\boldsymbol A_4=\begin{bmatrix}1&-1\\-1&1\end{bmatrix}$ represents a mapping in the standard basis that collapses a two-dimensional domain onto one dimension. Since one eigenvalue is 0, the space in direction of the (blue) eigenvector corresponding to $\lambda_1=0$ collapses, while the orthogonal (red) eigenvector stretches space by a factor $\lambda_2=2$. Therefore, the area of the image is 0.
- $\boldsymbol A_5=\begin{bmatrix}1&\frac12\\\frac12&1\end{bmatrix}$ is a shear-and-stretch mapping that scales space by 75% since $|\det(\boldsymbol A_5)|=\frac34$. It stretches space along the (red) eigenvector of $\lambda_2$ by a factor 1.5 and compresses it along the orthogonal (blue) eigenvector by a factor 0.5.

> In geometry, the area-preserving properties of this type of shearing parallel to an axis is also known as Cavalieri’s principle of equal areas for parallelograms (Katz, 2004).

Figure 4.4 Determinants and eigenspaces. Overview of five linear mappings and their associated transformation matrices $\boldsymbol A_i\in\mathbb R^{2\times2}$ projecting 400 color-coded points $\boldsymbol x\in\mathbb R^2$ (left column) onto target points $\boldsymbol A_i\boldsymbol x$ (right column). The central column depicts the first eigenvector, stretched by its associated eigenvalue $\lambda_1$, and the second eigenvector stretched by its eigenvalue $\lambda_2$. Each row depicts the effect of one of five transformation matrices $\boldsymbol A_i$ with respect to the standard basis.

![Figure 4.4](<Images/04_Matrix_Decompositions_Figure_4_4.png>)

**Example 4.7 (Eigenspectrum of a Biological Neural Network)**

Figure 4.5 Caenorhabditis elegans neural network (Kaiser and Hilgetag, 2006). (a) Symmetrized connectivity matrix; (b) Eigenspectrum. 

![image](<Images/04_Matrix_Decompositions_image_018.jpg>)

(a) Connectivity matrix.

![image](<Images/04_Matrix_Decompositions_image_019.jpg>)

(b) Eigenspectrum.

Methods to analyze and learn from network data are an essential component of machine learning methods. The key to understanding networks is the connectivity between network nodes, especially if two nodes are connected to each other or not. In data science applications, it is often useful to study the matrix that captures this connectivity data. 

We build a connectivity/adjacency matrix $\pmb { A } \in \mathbb { R } ^ { 277 \times 277 }$ of the complete neural network of the worm C.Elegans. Each row/column represents one of the 277 neurons of this worm’s brain. The connectivity matrix A has a value of $a _ { i j } = 1$ if neuron i talks to neuron $j$ through a synapse, and $a _ { i j } = 0$ otherwise. The connectivity matrix is not symmetric, which implies that eigenvalues may not be real valued. Therefore, we compute a symmetrized version of the connectivity matrix as $\pmb { A } _ { s y m } : = \pmb { A } + \pmb { A } ^ { \top }$ . This new matrix $A _ { \it { s y m } }$ is shown in Figure 4.5(a) and has a nonzero value $a _ { i j }$ if and only if two neurons are connected (white pixels), irrespective of the direction of the connection. In Figure 4.5(b), we show the corresponding eigenspectrum of $A _ { \it { s y m } }$ . The horizontal axis shows the index of the eigenvalues, sorted in descending order. The vertical axis shows the corresponding eigenvalue. The S-like shape of this eigenspectrum is typical for many biological neural networks. The underlying mechanism responsible for this is an area of active neuroscience research. 

**Theorem 4.12.** The eigenvectors $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { n }$ of a matrix $A \in \mathbb { R } ^ { n \times n }$ with n distinct eigenvalues $\lambda _ { 1 } , \ldots , \lambda _ { n }$ are linearly independent. 

This theorem states that eigenvectors of a matrix with n distinct eigenvalues form a basis of $\mathbb { R } ^ { n }$ 

**Definition 4.13.** A square matrix $\pmb { A } \in \mathbb { R } ^ { n \times n }$ is defective if it possesses fewer than n linearly independent eigenvectors. 

A non-defective matrix $\pmb { A } \in \mathbb { R } ^ { n \times n }$ does not necessarily require n distinct eigenvalues, but it does require that the eigenvectors form a basis of $\mathbb { R } ^ { n }$ . Looking at the eigenspaces of a defective matrix, it follows that the sum of the dimensions of the eigenspaces is less than n. Specifically, a defective matrix has at least one eigenvalue $\lambda _ { i }$ with an algebraic multiplicity $m > 1$ and a geometric multiplicity of less than $m .$ 

**Remark.** A defective matrix cannot have n distinct eigenvalues, as distinct eigenvalues have linearly independent eigenvectors (Theorem 4.12). 

**Theorem 4.14.** Given a matrix $\pmb { A } \in \mathbb { R } ^ { m \times n }$ , we can always obtain a symmetric, positive semidefinite matrix $\boldsymbol{S} \in \mathbb { R } ^ { n \times n }$ by defining 

$$
\boldsymbol {S} := \boldsymbol {A} ^ {\top} \boldsymbol {A}.\tag{4.36}
$$

**Remark.** If $\operatorname { r k } ( A ) = n$, then $S : = A ^ { \top } A$ is symmetric, positive definite. 

Understanding why Theorem 4.14 holds is insightful for how we can use symmetrized matrices: Symmetry requires $\boldsymbol S=\boldsymbol S^\top$, and by inserting (4.36) we obtain $\boldsymbol S=\boldsymbol A^\top\boldsymbol A=\boldsymbol A^\top(\boldsymbol A^\top)^\top=(\boldsymbol A^\top\boldsymbol A)^\top=\boldsymbol S^\top$. Moreover, positive semidefiniteness (Section 3.2.3) requires that $\boldsymbol x^\top\boldsymbol S\boldsymbol x\geq0$ and inserting (4.36) we obtain $\boldsymbol x^\top\boldsymbol S\boldsymbol x=\boldsymbol x^\top\boldsymbol A^\top\boldsymbol A\boldsymbol x=(\boldsymbol x^\top\boldsymbol A^\top)(\boldsymbol A\boldsymbol x)=(\boldsymbol A\boldsymbol x)^\top(\boldsymbol A\boldsymbol x)\geq0$, because the dot product computes a sum of squares (which are themselves non-negative).

**Theorem 4.15 (Spectral Theorem).** If $A \in \mathbb { R } ^ { n \times n }$ is symmetric, there exists an orthonormal basis of the corresponding vector space V consisting of eigenvectors of A, and each eigenvalue is real. 

A direct implication of the spectral theorem is that the eigendecomposition of a symmetric matrix A exists (with real eigenvalues), and that we can find an ONB of eigenvectors so that $\pmb { A } = \pmb { P } \pmb { D } \pmb { P } ^ { \top }$ , where D is diagonal and the columns of $\pmb { P }$ contain the eigenvectors. 

**Example 4.8**

Consider the matrix 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 3 & 2 & 2 \\ 2 & 3 & 2 \\ 2 & 2 & 3 \end{array} \right].\tag{4.37}
$$

The characteristic polynomial of A is 

$$
p _ {\boldsymbol {A}} (\lambda) = - (\lambda - 1) ^ {2} (\lambda - 7),\tag{4.38}
$$

so that we obtain the eigenvalues $\lambda _ { 1 } ~ = ~ 1$ and $\lambda _ { 2 } \ = \ 7 ,$ where $\lambda _ { 1 }$ is a repeated eigenvalue. Following our standard procedure for computing eigenvectors, we obtain the eigenspaces 

$$
E _ {1} = \operatorname{span} [ \underbrace {\left[ \begin{array}{c} - 1 \\ 1 \\ 0 \end{array} \right]} _ {=: \boldsymbol {x} _ {1}}, \underbrace {\left[ \begin{array}{c} - 1 \\ 0 \\ 1 \end{array} \right]} _ {=: \boldsymbol {x} _ {2}} ], \quad E _ {7} = \operatorname{span} [ \underbrace {\left[ \begin{array}{c} 1 \\ 1 \\ 1 \end{array} \right]} _ {=: \boldsymbol {x} _ {3}} ].\tag{4.39}
$$

We see that $\mathbf { { x } _ { 3 } }$ is orthogonal to both $\mathbf { x } _ { 1 }$ and $\mathbf { \mathcal { x } } _ { 2 }$ . However, since $\pmb { x } _ { 1 } ^ { \top } \pmb { x } _ { 2 } =1\neq0$, they are not orthogonal. The spectral theorem (Theorem 4.15) states that there exists an orthogonal basis, but the one we have is not orthogonal. However, we can construct one. 

To construct such a basis, we exploit the fact that $\mathbf { \boldsymbol { x } } _ { 1 } , \mathbf { \boldsymbol { x } } _ { 2 }$ are eigenvectors associated with the same eigenvalue λ. Therefore, for any $\alpha , \beta \in \mathbb { R }$ it holds that 

$$
\boldsymbol {A} \left(\alpha \boldsymbol {x} _ {1} + \beta \boldsymbol {x} _ {2}\right) = \boldsymbol {A} \boldsymbol {x} _ {1} \alpha + \boldsymbol {A} \boldsymbol {x} _ {2} \beta = \lambda \left(\alpha \boldsymbol {x} _ {1} + \beta \boldsymbol {x} _ {2}\right),\tag{4.40}
$$

i.e., any linear combination of $\mathbf { x } _ { 1 }$ and $\mathbf { \boldsymbol { x } } _ { 2 }$ is also an eigenvector of A associated with λ. The Gram-Schmidt algorithm (Section 3.8.3) is a method for iteratively constructing an orthogonal/orthonormal basis from a set of basis vectors using such linear combinations. Therefore, even if $\mathbf { x } _ { 1 }$ and $\mathbf { \boldsymbol { x } } _ { 2 }$ are not orthogonal, we can apply the Gram-Schmidt algorithm and find eigenvectors associated with $\lambda _ { 1 } = 1$ that are orthogonal to each other (and to $\mathbf { { x } } _ { 3 } )$ . In our example, we will obtain 

$$
\boldsymbol {x} _ {1} ^ {\prime} = \left[ \begin{array}{c} - 1 \\ 1 \\ 0 \end{array} \right], \quad \boldsymbol {x} _ {2} ^ {\prime} = \frac {1}{2} \left[ \begin{array}{c} - 1 \\ - 1 \\ 2 \end{array} \right],\tag{4.41}
$$

which are orthogonal to each other, orthogonal to $\boldsymbol{x}_3$, and eigenvectors of A associated with $\lambda _ { 1 } = 1$ 

Before we conclude our considerations of eigenvalues and eigenvectors it is useful to tie these matrix characteristics together with the concepts of the determinant and the trace. 

**Theorem 4.16.** The determinant of a matrix $\pmb { A } \in \mathbb { R } ^ { n \times n }$ is the product of its eigenvalues, i.e., 

$$
\det (\boldsymbol {A}) = \prod_ {i = 1} ^ {n} \lambda_ {i},\tag{4.42}
$$

where $\lambda _ { i } \in \mathbb { C }$ are (possibly repeated) eigenvalues of A. 


**Theorem 4.17.** The trace of a matrix $A \in \mathbb { R } ^ { n \times n }$ is the sum of its eigenvalues, i.e., 

$$
\operatorname{tr} (\boldsymbol {A}) = \sum_ {i = 1} ^ {n} \lambda_ {i},\tag{4.43}
$$


where $\lambda _ { i } \in \mathbb { C }$ are (possibly repeated) eigenvalues of A. 

Figure 4.6 Geometric interpretation of eigenvalues. The eigenvectors of A get stretched by the corresponding eigenvalues. The area of the unit square changes by $| \lambda _ { 1 } \lambda _ { 2 } |$ , the perimeter changes by a factor of $\frac { 1 } { 2 } ( | \lambda _ { 1 } | + | \lambda _ { 2 } | )$ 

![Figure 4.6](<Images/04_Matrix_Decompositions_image_020.jpg>)

Let us provide a geometric intuition of these two theorems. Consider a matrix $A \in \mathbb { R } ^ { 2 \times 2 }$ that possesses two linearly independent eigenvectors $\mathbf { x } _ { 1 } , \mathbf { x } _ { 2 } .$ . For this example, we assume $( \pmb { x } _ { 1 } , \pmb { x } _ { 2 } )$ are an ONB of $\mathbb { R } ^ { 2 }$ so that they are orthogonal and the area of the square they span is 1; see Figure 4.6. From Section 4.1, we know that the determinant computes the change of area of unit square under the transformation A. In this example, we can compute the change of area explicitly: Mapping the eigenvectors using A gives us vectors ${ \pmb v } _ { 1 } = { \pmb A } { \pmb x } _ { 1 } = \lambda _ { 1 } { \pmb x } _ { 1 }$ and ${ \pmb v } _ { 2 } = { \pmb A } { \pmb x } _ { 2 } = \lambda _ { 2 } { \pmb x } _ { 2 }$ , i.e., the new vectors ${ \mathbf { } } v _ { i }$ are scaled versions of the eigenvectors ${ \mathbf { } } x _ { i } ,$ and the scaling factors are the corresponding eigenvalues $\lambda _ { i } , v _ { 1 } , v _ { 2 }$ are still orthogonal, and the area of the rectangle they span is $| \lambda _ { 1 } \lambda _ { 2 } |$ 

Given that $\mathbf { \boldsymbol { x } } _ { 1 } , \mathbf { \boldsymbol { x } } _ { 2 }$ (in our example) are orthonormal, we can directly compute the perimeter of the unit square as $2 ( 1 + 1 )$ . Mapping the eigenvectors using A creates a rectangle whose perimeter is $2 ( | \lambda _ { 1 } | + | \lambda _ { 2 } | )$ Therefore, the sum of the absolute values of the eigenvalues tells us how the perimeter of the unit square changes under the transformation matrix A. 

**Example 4.9 (Google’s PageRank – Webpages as Eigenvectors)**

Google uses the eigenvector corresponding to the maximal eigenvalue of a matrix A to determine the rank of a page for search. The idea for the PageRank algorithm, developed at Stanford University by Larry Page and Sergey Brin in 1996, was that the importance of any web page can be approximated by the importance of pages that link to it. For this, they write down all web sites as a huge directed graph that shows which page links to which. PageRank computes the weight (importance) $x _ { i } \geqslant 0$ of a web site $a _ { i }$ by counting the number of pages pointing to $a _ { i }$ . Moreover, PageRank takes into account the importance of the web sites that link to $a _ { i }$ . The navigation behavior of a user is then modeled by a transition matrix A of this graph that tells us with what (click) probability somebody will end up on a different web site. The matrix A has the property that for any initial rank/importance vector x of a web site the sequence $x , A x , A ^ { 2 } x , \ldots$ converges to a vector $\pmb { x } ^ { * }$ . This vector is called the PageRank and satisfies $\pmb { A } \pmb { x } ^ { * } = \pmb { x } ^ { * }$ , i.e., it is an eigenvector (with corresponding eigenvalue 1) of A. After normalizing $\mathbf { \boldsymbol { x } } ^ { * }$ , such that $\| \pmb { x } ^ { * } \| = 1$ , we can interpret the entries as probabilities. More details and different perspectives on PageRank can be found in the original technical report (Page et al., 1999). 

## 4.3 Cholesky Decomposition

There are many ways to factorize special types of matrices that we encounter often in machine learning. In the positive real numbers, we have the square-root operation that gives us a decomposition of the number into identical components, e.g., $9 = 3 \cdot 3$ . For matrices, we need to be careful that we compute a square-root-like operation on positive quantities. For symmetric, positive definite matrices (see Section 3.2.3), we can choose from a number of square-root equivalent operations. The Cholesky decomposition/Choleskyfactorization provides a square-root equivalent operation on symmetric, positive definite matrices that is useful in practice. 

Theorem 4.18 (Cholesky Decomposition). A symmetric, positive definite matrix A can be factorized into a product $A = L L ^ { \top }$ , where L is a lowertriangular matrix with positive diagonal elements: 

$$
\left[ \begin{array}{c c c} a _ {1 1} & \dots & a _ {1 n} \\ \vdots & \ddots & \vdots \\ a _ {n 1} & \dots & a _ {n n} \end{array} \right] = \left[ \begin{array}{c c c} l _ {1 1} & \dots & 0 \\ \vdots & \ddots & \vdots \\ l _ {n 1} & \dots & l _ {n n} \end{array} \right] \left[ \begin{array}{c c c} l _ {1 1} & \dots & l _ {n 1} \\ \vdots & \ddots & \vdots \\ 0 & \dots & l _ {n n} \end{array} \right].\tag{4.44}
$$

L is called the Choleskyfactor of A, and L is unique. 

Example 4.10 (Cholesky Factorization) 

Consider a symmetric, positive definite matrix $\pmb { A } \in \mathbb { R } ^ { 3 \times 3 }$ . We are interested in finding its Cholesky factorization $\pmb { A } = \pmb { L } \pmb { L } ^ { \top } , \mathrm { i . e . }$ 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} a _ {1 1} & a _ {2 1} & a _ {3 1} \\ a _ {2 1} & a _ {2 2} & a _ {3 2} \\ a _ {3 1} & a _ {3 2} & a _ {3 3} \end{array} \right] = \boldsymbol {L} \boldsymbol {L} ^ {\top} = \left[ \begin{array}{c c c} l _ {1 1} & 0 & 0 \\ l _ {2 1} & l _ {2 2} & 0 \\ l _ {3 1} & l _ {3 2} & l _ {3 3} \end{array} \right] \left[ \begin{array}{c c c} l _ {1 1} & l _ {2 1} & l _ {3 1} \\ 0 & l _ {2 2} & l _ {3 2} \\ 0 & 0 & l _ {3 3} \end{array} \right].\tag{4.45}
$$

Multiplying out the right-hand side yields 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} l _ {1 1} ^ {2} & l _ {2 1} l _ {1 1} & l _ {3 1} l _ {1 1} \\ l _ {2 1} l _ {1 1} & l _ {2 1} ^ {2} + l _ {2 2} ^ {2} & l _ {3 1} l _ {2 1} + l _ {3 2} l _ {2 2} \\ l _ {3 1} l _ {1 1} & l _ {3 1} l _ {2 1} + l _ {3 2} l _ {2 2} & l _ {3 1} ^ {2} + l _ {3 2} ^ {2} + l _ {3 3} ^ {2} \end{array} \right].\tag{4.46}
$$

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

Comparing the left-hand side of (4.45) and the right-hand side of (4.46) shows that there is a simple pattern in the diagonal elements $l _ { i i } \mathbf { \cdot }$ 

$$
l _ {1 1} = \sqrt {a _ {1 1}}, l _ {2 2} = \sqrt {a _ {2 2} - l _ {2 1} ^ {2}}, l _ {3 3} = \sqrt {a _ {3 3} - (l _ {3 1} ^ {2} + l _ {3 2} ^ {2})}.\tag{4.47}
$$

Similarly for the elements below the diagonal $( l _ { i j }$ , where $i > j )$ , there is also a repeating pattern: 

$$
l _ {2 1} = \frac {1}{l _ {1 1}} a _ {2 1}, \quad l _ {3 1} = \frac {1}{l _ {1 1}} a _ {3 1}, \quad l _ {3 2} = \frac {1}{l _ {2 2}} (a _ {3 2} - l _ {3 1} l _ {2 1}).\tag{4.48}
$$

Thus, we constructed the Cholesky decomposition for any symmetric, positive definite $3 \times 3$ matrix. The key realization is that we can backward calculate what the components $l _ { i j }$ for the $\pmb { L }$ should be, given the values $a _ { i j }$ for A and previously computed values of $l _ { i j }$ 

The Cholesky decomposition is an important tool for the numerical computations underlying machine learning. Here, symmetric positive definite matrices require frequent manipulation, e.g., the covariance matrix of a multivariate Gaussian variable (see Section 6.5) is symmetric, positive definite. The Cholesky factorization of this covariance matrix allows us to generate samples from a Gaussian distribution. It also allows us to perform a linear transformation of random variables, which is heavily exploited when computing gradients in deep stochastic models, such as the variational auto-encoder (Jimenez Rezende et al., 2014; Kingma and Welling, 2014). The Cholesky decomposition also allows us to compute determinants very efficiently. Given the Cholesky decomposition $\bar { A } = L L ^ { \top }$ , we know that det $( A ) = \operatorname* { d e t } ( L ) \operatorname* { d e t } ( L ^ { \top } ) = \operatorname* { d e t } ( L ) ^ { 2 }$ . Since $\pmb { L }$ is a triangular matrix, the determinant is simply the product of its diagonal entries so that det $\begin{array} { r } { \left( \boldsymbol { A } \right) = \prod _ { i } l _ { i i } ^ { 2 } } \end{array}$ . Thus, many numerical software packages use the Cholesky decomposition to make computations more efficient. 

## 4.4 Eigendecomposition and Diagonalization

A diagonal matrix is a matrix that has value zero on all off-diagonal elements, i.e., they are of the form 

$$
\boldsymbol {D} = \left[ \begin{array}{c c c} c _ {1} & \dots & 0 \\ \vdots & \ddots & \vdots \\ 0 & \dots & c _ {n} \end{array} \right].\tag{4.49}
$$

They allow fast computation of determinants, powers, and inverses. The determinant is the product of its diagonal entries, a matrix power $D ^ { k }$ is given by each diagonal element raised to the power $k ,$ and the inverse $\pmb { D } ^ { - 1 }$ is the reciprocal of its diagonal elements if all of them are nonzero. 

In this section, we will discuss how to transform matrices into diagonal form. This is an important application of the basis change we discussed in Section 2.7.2 and eigenvalues from Section 4.2. 

Recall that two matrices A, D are similar (Definition 2.22) if there exists an invertible matrix $P ,$ , such that $\pmb { { \cal D } } = \pmb { { \cal P } } ^ { - 1 } \pmb { { \cal A } } \pmb { { \cal P } }$ . More specifically, we will look at matrices A that are similar to diagonal matrices D that contain the eigenvalues of A on the diagonal. 

Definition 4.19 (Diagonalizable). A matrix $\pmb { A } \in \mathbb { R } ^ { n \times n }$ is diagonalizable if it is similar to a diagonal matrix, i.e., if there exists an invertible matrix $P \in \mathbb { R } ^ { n \times n }$ such that $\pmb { { \cal D } } = \pmb { { \cal P } } ^ { - 1 } \pmb { { \cal A } } \pmb { { \cal P } }$ 

In the following, we will see that diagonalizing a matrix $A \in \mathbb { R } ^ { n \times n }$ is a way of expressing the same linear mapping but in another basis (see Section 2.6.1), which will turn out to be a basis that consists of the eigenvectors of A. 

Let $A \in \mathbb { R } ^ { n \times n }$ , let $\lambda _ { 1 } , \ldots , \lambda _ { n }$ be a set of scalars, and let $p _ { 1 } , \ldots , p _ { n }$ be a set of vectors in R<sup>n</sup>. We define $P : = [ \pmb { p } _ { 1 } , \ldots , \pmb { p } _ { n } ]$ and let $D \in \mathbb { R } ^ { n \times n }$ be a diagonal matrix with diagonal entries $\lambda _ { 1 } , \ldots , \lambda _ { n }$ . Then we can show that 

$$
A P = P D\tag{4.50}
$$

if and only if $\lambda _ { 1 } , \ldots , \lambda _ { n }$ are the eigenvalues of A and $p _ { 1 } , \ldots , p _ { n }$ are corresponding eigenvectors of A. 

We can see that this statement holds because 

$$
\boldsymbol {A} \boldsymbol {P} = \boldsymbol {A} [ \boldsymbol {p} _ {1}, \dots , \boldsymbol {p} _ {n} ] = [ \boldsymbol {A} \boldsymbol {p} _ {1}, \dots , \boldsymbol {A} \boldsymbol {p} _ {n} ],\tag{4.51}
$$

$$
\boldsymbol {P} \boldsymbol {D} = [ \boldsymbol {p} _ {1}, \ldots , \boldsymbol {p} _ {n} ] \left[ \begin{array}{c c c} \lambda_ {1} & & 0 \\ & \ddots & \\ 0 & & \lambda_ {n} \end{array} \right] = [ \lambda_ {1} \boldsymbol {p} _ {1}, \ldots , \lambda_ {n} \boldsymbol {p} _ {n} ].\tag{4.52}
$$

Thus, (4.50) implies that 

$$
\boldsymbol {A} \boldsymbol {p} _ {1} = \lambda_ {1} \boldsymbol {p} _ {1}\tag{4.53}
$$

$$
\begin{array}{c} \vdots \\ A \boldsymbol {p} _ {n} = \lambda_ {n} \boldsymbol {p} _ {n}. \end{array}\tag{4.54}
$$

Therefore, the columns of P must be eigenvectors of A. 

Our definition of diagonalization requires that $P \in \mathbb { R } ^ { n \times n }$ is invertible, i.e., P has full rank (Theorem 4.3). This requires us to have n linearly independent eigenvectors $p _ { 1 } , . . . , p _ { n } , \mathrm { i . e . }$ , the $\mathbf { \nabla } _ { \pmb { p } _ { i } }$ form a basis of $\mathbb { R } ^ { n }$ 

Theorem 4.20 (Eigendecomposition). A square matrix $A \in \mathbb { R } ^ { n \times n }$ can be factored into 

$$
\boldsymbol {A} = \boldsymbol {P D P} ^ {- 1},\tag{4.55}
$$

where $P \in \mathbb { R } ^ { n \times n }$ and D is a diagonal matrix whose diagonal entries are the eigenvalues of A, if and only if the eigenvectors of Aform a basis of R<sup>n</sup>. 

![image](<Images/04_Matrix_Decompositions_image_021.jpg>)


Theorem 4.20 implies that only non-defective matrices can be diagonalized and that the columns of P are the n eigenvectors of $\pmb { A }$ . For symmetric matrices we can obtain even stronger outcomes for the eigenvalue decom position. 

Theorem 4.21. A symmetric matrix $\ b { S } \in \mathbb { R } ^ { n \times n }$ can always be diagonalized. 

Theorem 4.21 follows directly from the spectral theorem 4.15. Moreover, the spectral theorem states that we can find an ONB of eigenvectors of $\mathbb { R } ^ { n }$ . This makes $_ { \pmb { P } }$ an orthogonal matrix so that $\pmb { D } = \pmb { P } ^ { \top } \pmb { A } \pmb { P }$ 

Remark. The Jordan normal form of a matrix offers a decomposition that works for defective matrices (Lang, 1987) but is beyond the scope of this book. 

## Geometric Intuition for the Eigendecomposition

We can interpret the eigendecomposition of a matrix as follows (see also Figure 4.7): Let A be the transformation matrix of a linear mapping with respect to the standard basis $e _ { i }$ (blue arrows). $P ^ { - 1 }$ performs a basis change from the standard basis into the eigenbasis. Then, the diagonal D scales the vectors along these axes by the eigenvalues $\lambda _ { i } .$ . Finally, $_ { r }$ transforms these scaled vectors back into the standard/canonical coordinates yielding $\lambda _ { i } { \pmb p } _ { i }$ 

Figure 4.7 Intuition behind the eigendecomposition as sequential transformations. Top-left to bottom-left: $P ^ { - 1 }$ performs a basis change (here drawn in $\mathbb { R } ^ { \overset { \sim } { 2 } }$ and depicted as a rotation-like operation) from the standard basis into the eigenbasis. Bottom-left to bottom-right: D performs a scaling along the remapped orthogonal eigenvectors, depicted here by a circle being stretched to an ellipse. Bottom-right to top-right: $_ { r }$ undoes the basis change (depicted as a reverse rotation) and restores the original coordinate frame. 

## Example 4.11 (Eigendecomposition)

Let us compute the eigendecomposition of $\begin{array} { r } { A = \frac { 1 } { 2 } \left\lceil \begin{array} { l l } { 5 } & { - 2 } \\ { - 2 } & { 5 } \end{array} \right\rceil } \end{array}$ 

Step 1: Compute eigenvalues and eigenvectors. The characteristic 

polynomial of A is 

$$
\det (\boldsymbol {A} - \lambda \boldsymbol {I}) = \det \left(\left[ \begin{array}{c c} \frac {5}{2} - \lambda & - 1 \\ - 1 & \frac {5}{2} - \lambda \end{array} \right]\right)\tag{4.56a}
$$

$$
= \left(\frac {5}{2} - \lambda\right) ^ {2} - 1 = \lambda^ {2} - 5 \lambda + \frac {2 1}{4} = (\lambda - \frac {7}{2}) (\lambda - \frac {3}{2}).\tag{4.56b}
$$

Therefore, the eigenvalues of A are $\begin{array} { r } { \lambda _ { 1 } = \frac { 7 } { 2 } } \end{array}$ and $\begin{array} { r } { \lambda _ { 2 } = \frac { 3 } { 2 } } \end{array}$ (the roots of the characteristic polynomial), and the associated (normalized) eigenvectors are obtained via 

$$
\boldsymbol {A} \boldsymbol {p} _ {1} = \frac {7}{2} \boldsymbol {p} _ {1}, \quad \boldsymbol {A} \boldsymbol {p} _ {2} = \frac {3}{2} \boldsymbol {p} _ {2}.\tag{4.57}
$$

This yields 

$$
\boldsymbol {p} _ {1} = \frac {1}{\sqrt {2}} \left[ \begin{array}{c} 1 \\ - 1 \end{array} \right], \quad \boldsymbol {p} _ {2} = \frac {1}{\sqrt {2}} \left[ \begin{array}{c} 1 \\ 1 \end{array} \right].\tag{4.58}
$$

Step 2: Check for existence. The eigenvectors $\mathbf { \boldsymbol { p } } _ { 1 } , \mathbf { \boldsymbol { p } } _ { 2 }$ form a basis of $\mathbb { R } ^ { 2 }$ Therefore, A can be diagonalized. 

Step 3: Construct the matrix $_ { \pmb { P } }$ to diagonalize A. We collect the eigenvectors of A in P so that 

$$
\boldsymbol {P} = \left[ \boldsymbol {p} _ {1}, \boldsymbol {p} _ {2} \right] = \frac {1}{\sqrt {2}} \left[ \begin{array}{c c} 1 & 1 \\ - 1 & 1 \end{array} \right].\tag{4.59}
$$

We then obtain 

$$
\boldsymbol {P} ^ {- 1} \boldsymbol {A} \boldsymbol {P} = \left[ \begin{array}{c c} \frac {7}{2} & 0 \\ 0 & \frac {3}{2} \end{array} \right] = \boldsymbol {D}.\tag{4.60}
$$

Figure 4.7 visualizes the 

eigendecomposition 

Equivalently, we get (exploiting that $P ^ { - 1 } = P ^ { \top }$ since the eigenvectors $\pmb { p } _ { 1 }$ and $\pmb { p } _ { 2 }$ in this example form an ONB) 

$$
\boldsymbol {A} = \left[ \begin{array}{c c} 5 & - 2 \\ - 2 & 5 \end{array} \right]
$$

as a sequence of linear 

$$
\underbrace {\frac {1}{2} \left[ \begin{array}{c c} 5 & - 2 \\ - 2 & 5 \end{array} \right]} _ {A} = \underbrace {\frac {1}{\sqrt {2}} \left[ \begin{array}{c c} 1 & 1 \\ - 1 & 1 \end{array} \right]} _ {P} \underbrace {\left[ \begin{array}{c c} \frac {7}{2} & 0 \\ 0 & \frac {3}{2} \end{array} \right]} _ {D} \underbrace {\frac {1}{\sqrt {2}} \left[ \begin{array}{c c} 1 & - 1 \\ 1 & 1 \end{array} \right]} _ {P ^ {- 1}}.\tag{4.61}
$$

transformations. 

Diagonal matrices D can efficiently be raised to a power. Therefore, we can find a matrix power for a matrix $A \in \mathbb { R } ^ { n \times n }$ via the eigenvalue decomposition (if it exists) so that 

$$
\boldsymbol {A} ^ {k} = \left(\boldsymbol {P D P} ^ {- 1}\right) ^ {k} = \boldsymbol {P D} ^ {k} \boldsymbol {P} ^ {- 1}.\tag{4.62}
$$

Computing $D ^ { k }$ is efficient because we apply this operation individually to any diagonal element. 

Assume that the eigendecomposition $A = P D P ^ { - 1 }$ exists. Then, 

$$
\det (\boldsymbol {A}) = \det (\boldsymbol {P D P} ^ {- 1}) = \det (\boldsymbol {P}) \det (\boldsymbol {D}) \det (\boldsymbol {P} ^ {- 1})\tag{4.63a}
$$

4.5 Singular Value Decomposition 

$$
= \det (\boldsymbol {D}) = \prod_ {i} d _ {i i}\tag{4.63b}
$$

allows for an efficient computation of the determinant of A. 

The eigenvalue decomposition requires square matrices. It would be useful to perform a decomposition on general matrices. In the next section, we introduce a more general matrix decomposition technique, the singular value decomposition. 

## 4.5 Singular Value Decomposition

The singular value decomposition (SVD) of a matrix is a central matrix decomposition method in linear algebra. It has been referred to as the “fundamental theorem of linear algebra” (Strang, 1993) because it can be applied to all matrices, not only to square matrices, and it always exists. Moreover, as we will explore in the following, the SVD of a matrix $A ,$ which represents a linear mapping $\Phi : V \to W$ , quantifies the change between the underlying geometry of these two vector spaces. We recommend the work by Kalman (1996) and Roy and Banerjee (2014) for a deeper overview of the mathematics of the SVD. 

Theorem 4.22 (SVD Theorem). Let $\pmb { A } \in \mathbb { R } ^ { m \times n }$ be a rectangular matrix of rank $r \in [ 0 , \operatorname* { m i n } ( m , n ) ]$ . The SVD of A is a decomposition of the form 

$$
m \boxed {A} ^ {n} = m \boxed {U} ^ {m} m \boxed {\Sigma} ^ {n} \boxed {V ^ {\top}} _ {u} ^ {n}\tag{4.64}
$$

with an orthogonal matrix $\pmb { U } \in \mathbb { R } ^ { m \times m }$ with column vectors $\mathbf { { u } } _ { i } , i = 1 , \ldots , m ,$ and an orthogonal matrix $V \in \mathbb { R } ^ { n \times n }$ with column vectors $v _ { j } , j = 1 , \dotsc , n$ Moreover, Σ is an $m \times n$ matrix with $\Sigma _ { i i } = \sigma _ { i } \geqslant 0$ and $\Sigma _ { i j } = 0 , \ : i \neq j$ 

The diagonal entries $\sigma _ { i } , i = 1 , \ldots , r .$ , of Σ are called the singular values, $\mathbf { \Delta } \mathbf { u } _ { i }$ are called the left-singular vectors, and ${ \pmb v } _ { j }$ are called the right-singular vectors. By convention, the singular values are ordered, i.e., $\sigma _ { 1 } \geqslant \sigma _ { 2 } \geqslant$ $\sigma _ { r } \geqslant 0$ 

The singular value matrix Σ is unique, but it requires some attention. Observe that the $\pmb { \Sigma } \in \mathbb { R } ^ { m \times n }$ is rectangular. In particular, Σ is of the same size as A. This means that Σ has a diagonal submatrix that contains the singular values and needs additional zero padding. Specifically, if $m > n ,$ then the matrix Σ has diagonal structure up to row n and then consists of 

Figure 4.8 Intuition behind the SVD of a matrix $\pmb { A } \in \mathbb { R } ^ { 3 \times 2 }$ as sequential transformations. Top-left to bottom-left: $\mathbf { } _ { V } ^ { \top }$ performs a basis change in $\mathbb { R } ^ { 2 }$ Bottom-left to bottom-right: Σ scales and maps from $\mathbb { R } ^ { 2 }$ to $\mathbb { R } ^ { 3 }$ . The ellipse in the bottom-right lives in $\mathbb { R } ^ { 3 } .$ . The third dimension is orthogonal to the surface of the elliptical disk. Bottom-right to top-right: U performs a basis change within R<sup>3</sup>. 

![image](<Images/04_Matrix_Decompositions_image_022.jpg>)


$\mathbf { 0 } ^ { \top }$ row vectors from $n + 1$ to m below so that 

$$
\boldsymbol {\Sigma} = \left[ \begin{array}{c c c} \sigma_ {1} & 0 & 0 \\ 0 & \ddots & 0 \\ 0 & 0 & \sigma_ {n} \\ 0 & \ldots & 0 \\ \vdots & & \vdots \\ 0 & \ldots & 0 \end{array} \right].\tag{4.65}
$$

If $m \ < \ n$ , the matrix Σ has a diagonal structure up to column m and columns that consist of 0 from $m + 1$ to n: 

$$
\boldsymbol {\Sigma} = \left[ \begin{array}{c c c c c c} \sigma_ {1} & 0 & 0 & 0 & \ldots & 0 \\ 0 & \ddots & 0 & \vdots & & \vdots \\ 0 & 0 & \sigma_ {m} & 0 & \ldots & 0 \end{array} \right].\tag{4.66}
$$

Remark. The SVD exists for any matrix $\pmb { A } \in \mathbb { R } ^ { m \times n }$ 

♢ 

## 4.5.1 Geometric Intuitions for the SVD

The SVD offers geometric intuitions to describe a transformation matrix A. In the following, we will discuss the SVD as sequential linear transformations performed on the bases. In Example 4.12, we will then apply transformation matrices of the SVD to a set of vectors in $\mathbb { R } ^ { 2 }$ , which allows us to visualize the effect of each transformation more clearly. 

The SVD of a matrix can be interpreted as a decomposition of a corresponding linear mapping (recall Section 2.7.1) $\Phi : \mathbb { R } ^ { n }  \mathbb { R } ^ { m }$ into three operations; see Figure 4.8. The SVD intuition follows superficially a similar structure to our eigendecomposition intuition, see Figure $4 . 7 \colon$ Broadly speaking, the SVD performs a basis change via $V ^ { ^ { \top } }$ followed by a scaling and augmentation (or reduction) in dimensionality via the singular value matrix Σ. Finally, it performs a second basis change via $U .$ . The SVD entails a number of important details and caveats, which is why we will review our intuition in more detail. 

Assume we are given a transformation matrix of a linear mapping $\Phi$ : $\mathbb { R } ^ { n } \to \mathbb { R } ^ { m }$ with respect to the standard bases B and $C$ of $\mathbb { R } ^ { n }$ and $\mathbb { R } ^ { m } { } _ { : }$ respectively. Moreover, assume a second basis $\tilde { B }$ of $\mathbb { R } ^ { n }$ and $\tilde { C }$ of $\mathbb { R } ^ { m }$ . Then 

1. The matrix $V$ performs a basis change in the domain $\mathbb { R } ^ { n }$ from $\tilde { B }$ (represented by the red and orange vectors ${ \pmb v } _ { 1 }$ and ${ \pmb v } _ { 2 }$ in the top-left of Figure 4.8) to the standard basis B. $\pmb { V } ^ { \top } = \pmb { V } ^ { - 1 }$ performs a basis change from $B$ to $\tilde { B } .$ . The red and orange vectors are now aligned with the canonical basis in the bottom-left of Figure 4.8. 

2. Having changed the coordinate system to ${ \tilde { B } } _ { : }$ , Σ scales the new coordinates by the singular values $\sigma _ { i }$ (and adds or deletes dimensions), i.e., Σ is the transformation matrix of Φ with respect to $\tilde { B }$ and ${ \tilde { C } } ,$ represented by the red and orange vectors being stretched and lying in the $e _ { 1 } – e _ { 2 }$ plane, which is now embedded in a third dimension in the bottom-right of Figure 4.8. 

3. U performs a basis change in the codomain $\mathbb { R } ^ { m }$ from $\tilde { C }$ into the canonical basis of $\mathbb { R } ^ { m }$ , represented by a rotation of the red and orange vectors out of the $e _ { 1 } – e _ { 2 }$ plane. This is shown in the top-right of Figure 4.8. 

The SVD expresses a change of basis in both the domain and codomain. This is in contrast with the eigendecomposition that operates within the same vector space, where the same basis change is applied and then undone. What makes the SVD special is that these two different bases are simultaneously linked by the singular value matrix Σ. 

## Example 4.12 (Vectors and the SVD)

Consider a mapping of a square grid of vectors $\mathcal { X } \in \mathbb { R } ^ { 2 }$ that fit in a box of size $2 \times 2$ centered at the origin. Using the standard basis, we map these vectors using 

$$
\begin{array}{r l} \boldsymbol {A} & = \left[ \begin{array}{c c} 1 & - 0. 8 \\ 0 & 1 \\ 1 & 0 \end{array} \right] = \boldsymbol {U} \boldsymbol {\Sigma} \boldsymbol {V} ^ {\top} \\ & = \left[ \begin{array}{c c c} - 0. 7 9 & 0 & - 0. 6 2 \\ 0. 3 8 & - 0. 7 8 & - 0. 4 9 \\ - 0. 4 8 & - 0. 6 2 & 0. 6 2 \end{array} \right] \left[ \begin{array}{c c} 1. 6 2 & 0 \\ 0 & 1. 0 \\ 0 & 0 \end{array} \right] \left[ \begin{array}{c c} - 0. 7 8 & 0. 6 2 \\ - 0. 6 2 & - 0. 7 8 \end{array} \right]. \end{array}\tag{4.67a}
$$

(4.67b) 

We start with a set of vectors $\mathcal { X }$ (colored dots; see top-left panel of Figure 4.9) arranged in a grid. We then apply $V ^ { \top } \in \mathbb { R } ^ { 2 \times \hat { 2 } }$ , which rotates $\mathcal { X } .$ The rotated vectors are shown in the bottom-left panel of Figure 4.9. We now map these vectors using the singular value matrix Σ to the codomain $\mathbb { R } ^ { 3 }$ (see the bottom-right panel in Figure 4.9). Note that all vectors lie in the $x _ { 1 } { - } x _ { 2 }$ plane. The third coordinate is always 0. The vectors in the $x _ { 1 } { - } x _ { 2 }$ plane have been stretched by the singular values. 

The direct mapping of the vectors by A to the codomain $\mathbb { R } ^ { 3 }$ equals the transformation of by $U \pmb { \Sigma } \pmb { V } ^ { \top }$ , where U performs a rotation within the codomain $\mathbb { R } ^ { 3 }$ so that the mapped vectors are no longer restricted to the $x _ { 1 } { - } x _ { 2 }$ plane; they still are on a plane as shown in the top-right panel of Figure 4.9. 

Figure 4.9 SVD and mapping of vectors (represented by discs). The panels follow the same anti-clockwise structure of Figure 4.8. 

![image](<Images/04_Matrix_Decompositions_image_023.jpg>)


![image](<Images/04_Matrix_Decompositions_image_024.jpg>)


![image](<Images/04_Matrix_Decompositions_image_025.jpg>)


![image](<Images/04_Matrix_Decompositions_image_026.jpg>)


## 4.5.2 Construction of the SVD

We will next discuss why the SVD exists and show how to compute it in detail. The SVD of a general matrix shares some similarities with the eigendecomposition of a square matrix. 

Remark. Compare the eigendecomposition of an SPD matrix 

$$
\pmb {S} = \pmb {S} ^ {\top} = \pmb {P D P} ^ {\top}\tag{4.68}
$$

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

## 4.5 Singular Value Decomposition

with the corresponding SVD 

$$
\boldsymbol {S} = \boldsymbol {U} \boldsymbol {\Sigma} \boldsymbol {V} ^ {\top}.\tag{4.69}
$$

If we set 

$$
\boldsymbol {U} = \boldsymbol {P} = \boldsymbol {V}, \quad \boldsymbol {D} = \boldsymbol {\Sigma},\tag{4.70}
$$

we see that the SVD of SPD matrices is their eigendecomposition. 

In the following, we will explore why Theorem 4.22 holds and how the SVD is constructed. Computing the SVD of $\pmb { A } \in \mathbb { R } ^ { m \times n }$ is equivalent to finding two sets of orthonormal bases $U = ( \pmb { u } _ { 1 } , \dots , \pmb { u } _ { m } )$ and $V =$ $( { \pmb v } _ { 1 } , \ldots , { \pmb v } _ { n } )$ of the codomain $\mathbb { R } ^ { m }$ and the domain $\mathbb { R } ^ { n }$ , respectively. From these ordered bases, we will construct the matrices U and $V$ 

Our plan is to start with constructing the orthonormal set of rightsingular vectors $\pmb { v } _ { 1 } , \dots , \pmb { v } _ { n } \in \mathbb { R } ^ { n }$ . We then construct the orthonormal set of left-singular vectors $\pmb { u } _ { 1 } , \ldots , \pmb { u } _ { m } \in \mathbb { R } ^ { m }$ . Thereafter, we will link the two and require that the orthogonality of the ${ \mathbf { } } v _ { i }$ is preserved under the transformation of $A .$ . This is important because we know that the images $\mathbf { \nabla } _ { \mathbf { A } v _ { i } }$ form a set of orthogonal vectors. We will then normalize these images by scalar factors, which will turn out to be the singular values. 

Let us begin with constructing the right-singular vectors. The spectral theorem (Theorem 4.15) tells us that the eigenvectors of a symmetric matrix form an ONB, which also means it can be diagonalized. Moreover, from Theorem 4.14 we can always construct a symmetric, positive semidefinite matrix $\pmb { A } ^ { \top } \pmb { A } \ \in \ \mathbb { R } ^ { n \times n }$ from any rectangular matrix ${ \textbf { \textit { A } } } \in$ $\mathbb { R } ^ { m \times n }$ . Thus, we can always diagonalize $A ^ { \top } A$ and obtain 

$$
\boldsymbol {A} ^ {\top} \boldsymbol {A} = \boldsymbol {P} \boldsymbol {D} \boldsymbol {P} ^ {\top} = \boldsymbol {P} \left[ \begin{array}{c c c} \lambda_ {1} & \dots & 0 \\ \vdots & \ddots & \vdots \\ 0 & \dots & \lambda_ {n} \end{array} \right] \boldsymbol {P} ^ {\top},\tag{4.71}
$$

where $_ { \pmb { P } }$ is an orthogonal matrix, which is composed of the orthonormal eigenbasis. The $\lambda _ { i } \geqslant 0$ are the eigenvalues of $\boldsymbol { A } ^ { \top } \boldsymbol { A }$ . Let us assume the SVD of A exists and inject (4.64) into (4.71). This yields 

$$
\boldsymbol {A} ^ {\top} \boldsymbol {A} = (\boldsymbol {U} \boldsymbol {\Sigma} \boldsymbol {V} ^ {\top}) ^ {\top} (\boldsymbol {U} \boldsymbol {\Sigma} \boldsymbol {V} ^ {\top}) = \boldsymbol {V} \boldsymbol {\Sigma} ^ {\top} \boldsymbol {U} ^ {\top} \boldsymbol {U} \boldsymbol {\Sigma} \boldsymbol {V} ^ {\top},\tag{4.72}
$$

where $U , V$ are orthogonal matrices. Therefore, with $U ^ { \top } U = I$ we obtain 

$$
\boldsymbol {A} ^ {\top} \boldsymbol {A} = \boldsymbol {V} \boldsymbol {\Sigma} ^ {\top} \boldsymbol {\Sigma} \boldsymbol {V} ^ {\top} = \boldsymbol {V} \left[ \begin{array}{c c c} \sigma_ {1} ^ {2} & 0 & 0 \\ 0 & \ddots & 0 \\ 0 & 0 & \sigma_ {n} ^ {2} \end{array} \right] \boldsymbol {V} ^ {\top}.\tag{4.73}
$$

Comparing now (4.71) and (4.73), we identify 

$$
\boldsymbol {V} ^ {\top} = \boldsymbol {P} ^ {\top},
$$

$$
\sigma_ {i} ^ {2} = \lambda_ {i}.\tag{4.74}
$$

(4.75) 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



Therefore, the eigenvectors of $A ^ { \top } A$ that compose P are the right-singular vectors V of A (see (4.74)). The eigenvalues of $A ^ { \top } A$ are the squared singular values of Σ (see (4.75)). 

To obtain the left-singular vectors $U _ { z }$ , we follow a similar procedure. We start by computing the SVD of the symmetric matrix $\boldsymbol { A } \boldsymbol { A } ^ { \intercal } \in \mathbb { R } ^ { m \times m }$ (instead of the previous $\pmb { A } ^ { \top } \pmb { A } \in \mathbb { R } ^ { n \times n } )$ . The SVD of A yields 

$$
\begin{array}{l} \boldsymbol {A} \boldsymbol {A} ^ {\top} = (\boldsymbol {U} \boldsymbol {\Sigma} \boldsymbol {V} ^ {\top}) (\boldsymbol {U} \boldsymbol {\Sigma} \boldsymbol {V} ^ {\top}) ^ {\top} = \boldsymbol {U} \boldsymbol {\Sigma} \boldsymbol {V} ^ {\top} \boldsymbol {V} \boldsymbol {\Sigma} ^ {\top} \boldsymbol {U} ^ {\top} \\ = \boldsymbol {U} \left[ \begin{array}{c c c} \sigma_ {1} ^ {2} & 0 & 0 \\ 0 & \ddots & 0 \\ 0 & 0 & \sigma_ {m} ^ {2} \end{array} \right] \boldsymbol {U} ^ {\top}. \end{array}\tag{4.76a}
$$

(4.76b) 

The spectral theorem tells us that $\pmb { A } \pmb { A } ^ { \top } = \pmb { S } \pmb { D } \pmb { S } ^ { \top }$ can be diagonalized and we can find an ONB of eigenvectors of $A A ^ { \top }$ , which are collected in S. The orthonormal eigenvectors of $A A ^ { \top }$ are the left-singular vectors U and form an orthonormal basis in the codomain of the SVD. 

This leaves the question of the structure of the matrix Σ. Since $A A ^ { \top }$ and $A ^ { \top } A$ have the same nonzero eigenvalues (see page 106), the nonzero entries of the Σ matrices in the SVD for both cases have to be the same. 

The last step is to link up all the parts we touched upon so far. We have an orthonormal set of right-singular vectors in $V$ . To finish the construction of the SVD, we connect them with the orthonormal vectors $U .$ . To reach this goal, we use the fact the images of the ${ \mathbf { } } v _ { i }$ under A have to be orthogonal, too. We can show this by using the results from Section 3.4. We require that the inner product between $\mathbf { \nabla } _ { \mathbf { A } v _ { i } }$ and $\mathbf { \nabla } A v _ { j }$ must be 0 for $i \neq j$ . For any two orthogonal eigenvectors $\mathbf { } { \pmb v } _ { i } , { \pmb v } _ { j } , i \neq j$ , it holds that 

$$
\left(\boldsymbol {A} \boldsymbol {v} _ {i}\right) ^ {\top} \left(\boldsymbol {A} \boldsymbol {v} _ {j}\right) = \boldsymbol {v} _ {i} ^ {\top} \left(\boldsymbol {A} ^ {\top} \boldsymbol {A}\right) \boldsymbol {v} _ {j} = \boldsymbol {v} _ {i} ^ {\top} \left(\lambda_ {j} \boldsymbol {v} _ {j}\right) = \lambda_ {j} \boldsymbol {v} _ {i} ^ {\top} \boldsymbol {v} _ {j} = 0.\tag{4.77}
$$

For the case $m \ \geqslant \ r ,$ , it holds that $\{ A v _ { 1 } , \ldots , A v _ { r } \}$ is a basis of an $r \mathrm { - }$ dimensional subspace of $\mathbb { R } ^ { m }$ 

To complete the SVD construction, we need left-singular vectors that are orthonormal: We normalize the images of the right-singular vectors $\mathbf { A } \pmb { v } _ { i }$ and obtain 

$$
\boldsymbol {u} _ {i} := \frac {\boldsymbol {A} \boldsymbol {v} _ {i}}{\| \boldsymbol {A} \boldsymbol {v} _ {i} \|} = \frac {1}{\sqrt {\lambda_ {i}}} \boldsymbol {A} \boldsymbol {v} _ {i} = \frac {1}{\sigma_ {i}} \boldsymbol {A} \boldsymbol {v} _ {i},\tag{4.78}
$$

where the last equality was obtained from (4.75) and (4.76b), showing us that the eigenvalues of $A A ^ { \top }$ are such that $\sigma _ { i } ^ { 2 } = \lambda _ { i }$ 

Therefore, the eigenvectors of $A ^ { \top } A$ , which we know are the rightsingular vectors ${ \mathbf { } } v _ { i s }$ and their normalized images under A, the left-singular vectors ${ \bf { u } } _ { i } ,$ , form two self-consistent ONBs that are connected through the singular value matrix Σ. 

Let us rearrange (4.78) to obtain the singular value equation 

$$
\boldsymbol {A} \boldsymbol {v} _ {i} = \sigma_ {i} \boldsymbol {u} _ {i}, \quad i = 1, \dots , r.\tag{4.79}
$$

## 4.5 Singular Value Decomposition

This equation closely resembles the eigenvalue equation (4.25), but the vectors on the left- and the right-hand sides are not the same. 

For $n < m , ( 4 . 7 9 )$ holds only for $i \leqslant n ,$ but (4.79) says nothing about the $\mathbf { \Delta } \mathbf { u } _ { i }$ for $i > n$ . However, we know by construction that they are orthonormal. Conversely, for $m < n , ( 4 . 7 9 )$ holds only for $i \leqslant m$ . For $i > m$ we have $\mathbf { } A \pmb { v } _ { i } = \mathbf { 0 }$ and we still know that the ${ \mathbf { } } v _ { i }$ form an orthonormal set. This means that the SVD also supplies an orthonormal basis of the kernel (null space) of $A ,$ , the set of vectors x with $\pmb { A } \pmb { x } = \mathbf { 0 }$ (see Section 2.7.3). 

Concatenating the ${ \mathbf { } } v _ { i }$ as the columns of V and the $\mathbf { \Delta } \mathbf { u } _ { i }$ as the columns of U yields 

$$
\boldsymbol {A} \boldsymbol {V} = \boldsymbol {U} \boldsymbol {\Sigma},\tag{4.80}
$$

where Σ has the same dimensions as $\pmb { A }$ and a diagonal structure for rows $1 , \ldots , r$ . Hence, right-multiplying with $V ^ { ^ { \top } }$ yields $\mathbf { \pmb { A } } = \pmb { U } \pmb { \Sigma V } ^ { \top }$ , which is the SVD of $\pmb { A }$ . 

## Example 4.13 (Computing the SVD)

Let us find the singular value decomposition of 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 1 & 0 & 1 \\ - 2 & 1 & 0 \end{array} \right].\tag{4.81}
$$

The SVD requires us to compute the right-singular vectors $v _ { j } ,$ the singular values $\sigma _ { k }$ , and the left-singular vectors $\mathbf { \Delta } \mathbf { u } _ { i }$ 

Step 1: Right-singular vectors as the eigenbasis of $A ^ { \top } A$ 

We start by computing 

$$
\boldsymbol {A} ^ {\top} \boldsymbol {A} = \left[ \begin{array}{c c} 1 & - 2 \\ 0 & 1 \\ 1 & 0 \end{array} \right] \left[ \begin{array}{c c c} 1 & 0 & 1 \\ - 2 & 1 & 0 \end{array} \right] = \left[ \begin{array}{c c c} 5 & - 2 & 1 \\ - 2 & 1 & 0 \\ 1 & 0 & 1 \end{array} \right].\tag{4.82}
$$

We compute the singular values and right-singular vectors $\boldsymbol { v } _ { j }$ through the eigenvalue decomposition of $A ^ { \top } A$ , which is given as 

$$
\boldsymbol {A} ^ {\top} \boldsymbol {A} = \left[ \begin{array}{c c c} \frac {5}{\sqrt {3 0}} & 0 & \frac {- 1}{\sqrt {6}} \\ \frac {- 2}{\sqrt {3 0}} & \frac {1}{\sqrt {5}} & \frac {- 2}{\sqrt {6}} \\ \frac {1}{\sqrt {3 0}} & \frac {2}{\sqrt {5}} & \frac {1}{\sqrt {6}} \end{array} \right] \left[ \begin{array}{c c c} 6 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 0 \end{array} \right] \left[ \begin{array}{c c c} \frac {5}{\sqrt {3 0}} & \frac {- 2}{\sqrt {3 0}} & \frac {1}{\sqrt {3 0}} \\ 0 & \frac {1}{\sqrt {5}} & \frac {2}{\sqrt {5}} \\ \frac {- 1}{\sqrt {6}} & \frac {- 2}{\sqrt {6}} & \frac {1}{\sqrt {6}} \end{array} \right] = \boldsymbol {P D P} ^ {\top},\tag{4.83}
$$

and we obtain the right-singular vectors as the columns of $_ { \pmb { P } }$ so that 

$$
\boldsymbol {V} = \boldsymbol {P} = \left[ \begin{array}{c c c} \frac {5}{\sqrt {3 0}} & 0 & \frac {- 1}{\sqrt {6}} \\ \frac {- 2}{\sqrt {3 0}} & \frac {1}{\sqrt {5}} & \frac {- 2}{\sqrt {6}} \\ \frac {1}{\sqrt {3 0}} & \frac {2}{\sqrt {5}} & \frac {1}{\sqrt {6}} \end{array} \right].\tag{4.84}
$$

Step 2: Singular-value matrix. 

As the singular values $\sigma _ { i }$ are the square roots of the eigenvalues of 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



$A ^ { \top } A$ we obtain them straight from D. Since rk $( A ) = 2$ , there are only two nonzero singular values: $\sigma _ { 1 } = \sqrt { 6 }$ and $\sigma _ { 2 } = 1$ . The singular value matrix must be the same size as $A _ { i }$ , and we obtain 

$$
\boldsymbol {\Sigma} = \left[ \begin{array}{c c c} \sqrt {6} & 0 & 0 \\ 0 & 1 & 0 \end{array} \right].\tag{4.85}
$$

Step 3: Left-singular vectors as the normalized image of the rightsingular vectors. 

We find the left-singular vectors by computing the image of the rightsingular vectors under A and normalizing them by dividing them by their corresponding singular value. We obtain 

$$
\pmb {u} _ {1} = \frac {1}{\sigma_ {1}} \pmb {A} \pmb {v} _ {1} = \frac {1}{\sqrt {6}} \left[ \begin{array}{l l l} 1 & 0 & 1 \\ - 2 & 1 & 0 \end{array} \right] \left[ \begin{array}{l} \frac {5}{\sqrt {3 0}} \\ \frac {- 2}{\sqrt {3 0}} \\ \frac {1}{\sqrt {3 0}} \end{array} \right] = \left[ \begin{array}{l} \frac {1}{\sqrt {5}} \\ - \frac {2}{\sqrt {5}} \end{array} \right],\tag{4.86}
$$

$$
\boldsymbol {u} _ {2} = \frac {1}{\sigma_ {2}} \boldsymbol {A} \boldsymbol {v} _ {2} = \frac {1}{1} \left[ \begin{array}{c c c} 1 & 0 & 1 \\ - 2 & 1 & 0 \end{array} \right] \left[ \begin{array}{c} 0 \\ \frac {1}{\sqrt {5}} \\ \frac {2}{\sqrt {5}} \end{array} \right] = \left[ \begin{array}{c} \frac {2}{\sqrt {5}} \\ \frac {1}{\sqrt {5}} \end{array} \right],\tag{4.87}
$$

$$
\boldsymbol {U} = \left[ \boldsymbol {u} _ {1}, \boldsymbol {u} _ {2} \right] = \frac {1}{\sqrt {5}} \left[ \begin{array}{c c} 1 & 2 \\ - 2 & 1 \end{array} \right].\tag{4.88}
$$

Note that on a computer the approach illustrated here has poor numerical behavior, and the SVD of A is normally computed without resorting to the eigenvalue decomposition of $A ^ { \top } A$ 

## 4.5.3 Eigenvalue Decomposition vs. Singular Value Decomposition

Let us consider the eigendecomposition $A = P D P ^ { - 1 }$ and the SVD $A =$ $U \pmb { \Sigma } \pmb { V } ^ { \top }$ and review the core elements of the past sections. 

The SVD always exists for any matrix $\mathbb { R } ^ { m \times n }$ . The eigendecomposition is only defined for square matrices $\mathbb { R } ^ { n \times n }$ and only exists if we can find a basis of eigenvectors of $\mathbb { R } ^ { n }$ 

The vectors in the eigendecomposition matrix $_ { P }$ are not necessarily orthogonal, $\mathrm { i . e . }$ , the change of basis is not a simple rotation and scaling. On the other hand, the vectors in the matrices $U$ and $V$ in the SVD are orthonormal, so they do represent rotations. 

Both the eigendecomposition and the SVD are compositions of three linear mappings: 

1. Change of basis in the domain 

2. Independent scaling of each new basis vector and mapping from domain to codomain 

3. Change of basis in the codomain 

![image](<Images/04_Matrix_Decompositions_image_027.jpg>)



Figure 4.10 Movie ratings of three people for four movies and its SVD decomposition.


A key difference between the eigendecomposition and the SVD is that in the SVD, domain and codomain can be vector spaces of different dimensions. 

In the SVD, the left- and right-singular vector matrices U and V are generally not inverse of each other (they perform basis changes in dif ferent vector spaces). In the eigendecomposition, the basis change matrices P and $P ^ { - 1 }$ are inverses of each other. 

In the SVD, the entries in the diagonal matrix Σ are all real and nonnegative, which is not generally true for the diagonal matrix in the eigendecomposition. 

The SVD and the eigendecomposition are closely related through their projections 

– The left-singular vectors of A are eigenvectors of $A A ^ { \top }$ 

– The right-singular vectors of A are eigenvectors of $A ^ { \top } A$ 

– The nonzero singular values of A are the square roots of the nonzero eigenvalues of both $A A ^ { \top }$ and $A ^ { \top } A$ 

For symmetric matrices $A \in \mathbb { R } ^ { n \times n }$ , the eigenvalue decomposition and the SVD are one and the same, which follows from the spectral theorem 4.15. 

Example 4.14 (Finding Structure in Movie Ratings and Consumers) Let us add a practical interpretation of the SVD by analyzing data on people and their preferred movies. Consider three viewers (Ali, Beatrix, Chandra) rating four different movies (Star Wars, Blade Runner, Amelie, Delicatessen). Their ratings are values between 0 (worst) and 5 (best) and encoded in a data matrix $\pmb { A } \in \mathbb { R } ^ { 4 \times 3 }$ as shown in Figure 4.10. Each row represents a movie and each column a user. Thus, the column vectors of movie ratings, one for each viewer, are $\begin{array} { r } { \pmb { x } _ { \mathrm { A l i } } , \pmb { x } _ { \mathrm { B e a t r i x } } , \pmb { x } _ { \mathrm { C h a n d r a } } . } \end{array}$ 

These two “spaces” are only meaningfully spanned by the respective viewer and movie data if the data itself covers a sufficient diversity of viewers and movies. 

Factoring A using the SVD offers us a way to capture the relationships of how people rate movies, and especially if there is a structure linking which people like which movies. Applying the SVD to our data matrix A makes a number of assumptions: 

1. All viewers rate movies consistently using the same linear mapping. 

2. There are no errors or noise in the ratings. 

3. We interpret the left-singular vectors $\mathbf { \Delta } \mathbf { u } _ { i }$ as stereotypical movies and the right-singular vectors ${ \pmb v } _ { j }$ as stereotypical viewers. 

We then make the assumption that any viewer’s specific movie preferences can be expressed as a linear combination of the ${ \pmb v } _ { j }$ . Similarly, any movie’s like-ability can be expressed as a linear combination of the $\mathbf { \Delta } \mathbf { u } _ { i }$ . Therefore, a vector in the domain of the SVD can be interpreted as a viewer in the “space” of stereotypical viewers, and a vector in the codomain of the SVD correspondingly as a movie in the “space” of stereotypical movies. Let us inspect the SVD of our movie-user matrix. The first left-singular vector ${ \pmb u } _ { 1 }$ has large absolute values for the two science fiction movies and a large first singular value (red shading in Figure 4.10). Thus, this groups a type of users with a specific set of movies (science fiction theme). Similarly, the first right-singular ${ \pmb v } _ { 1 }$ shows large absolute values for Ali and Beatrix, who give high ratings to science fiction movies (green shading in Figure 4.10). This suggests that ${ \pmb v } _ { 1 }$ reflects the notion of a science fiction lover. 

Similarly, ${ \bf { u } } _ { 2 } ,$ seems to capture a French art house film theme, and ${ \pmb v } _ { 2 }$ indicates that Chandra is close to an idealized lover of such movies. An idealized science fiction lover is a purist and only loves science fiction movies, so a science fiction lover ${ \pmb v } _ { 1 }$ gives a rating of zero to everything but science fiction themed—this logic is implied by the diagonal substructure for the singular value matrix Σ. A specific movie is therefore represented by how it decomposes (linearly) into its stereotypical movies. Likewise, a person would be represented by how they decompose (via linear combination) into movie themes. 

It is worth to briefly discuss SVD terminology and conventions, as there are different versions used in the literature. While these differences can be confusing, the mathematics remains invariant to them. 

For convenience in notation and abstraction, we use an SVD notation where the SVD is described as having two square left- and right-singular vector matrices, but a non-square singular value matrix. Our definition (4.64) for the SVD is sometimes called the full SVD. 

Some authors define the SVD a bit differently and focus on square singular matrices. Then, for $\pmb { A } \in \mathbb { R } ^ { m \times n }$ and m $\geqslant n _ { : }$ 

$$
\mathbf {A} _ {m \times n} = \mathbf {U} _ {m \times n} \sum_ {n \times n} \mathbf {V} ^ {\top}.\tag{4.89}
$$

Sometimes this formulation is called the reduced SVD (e.g., Datta (2010)) or the SVD (e.g., Press et al. (2007)). This alternative format changes merely how the matrices are constructed but leaves the mathematical structure of the SVD unchanged. The convenience of this alternative formulation is that Σ is diagonal, as in the eigenvalue decomposition. 

In Section 4.6, we will learn about matrix approximation techniques using the SVD, which is also called the truncated SVD. 

It is possible to define the SVD of a rank-r matrix A so that U is an $m \times r$ matrix, Σ a diagonal matrix $r \times r ,$ and V an $r \times n$ matrix. This construction is very similar to our definition, and ensures that the diagonal matrix Σ has only nonzero entries along the diagonal. The main convenience of this alternative notation is that Σ is diagonal, as in the eigenvalue decomposition. 

A restriction that the SVD for A only applies to $m \times n$ matrices with m $> n$ is practically unnecessary. When $m < n ,$ the SVD decomposition will yield Σ with more zero columns than rows and, consequently, the singular values $\sigma _ { m + 1 } , \ldots , \sigma _ { n }$ are 0. 

The SVD is used in a variety of applications in machine learning from least-squares problems in curve fitting to solving systems of linear equations. These applications harness various important properties of the SVD, its relation to the rank of a matrix, and its ability to approximate matrices of a given rank with lower-rank matrices. Substituting a matrix with its SVD has often the advantage of making calculation more robust to numerical rounding errors. As we will explore in the next section, the SVD’s ability to approximate matrices with “simpler” matrices in a principled manner opens up machine learning applications ranging from dimensionality reduction and topic modeling to data compression and clustering. 

## 4.6 Matrix Approximation

We considered the SVD as a way to factorize $\pmb { A } = \pmb { U } \pmb { \Sigma } \pmb { V } ^ { \top } \in \mathbb { R } ^ { m \times n }$ into the product of three matrices, where $\pmb { U } \in \mathbb { R } ^ { m \times m }$ and $V \in \mathbb { R } ^ { n \times n }$ are orthogonal and Σ contains the singular values on its main diagonal. Instead of doing the full SVD factorization, we will now investigate how the SVD allows us to represent a matrix A as a sum of simpler (low-rank) matrices $A _ { i }$ , which lends itself to a matrix approximation scheme that is cheaper to compute than the full SVD. 

We construct a rank-1 matrix $\pmb { A } _ { i } \in \mathbb { R } ^ { m \times n }$ as 

$$
\boldsymbol {A} _ {i} := \boldsymbol {u} _ {i} \boldsymbol {v} _ {i} ^ {\top},\tag{4.90}
$$

which is formed by the outer product of the ith orthogonal column vector of U and V. Figure 4.11 shows an image of Stonehenge, which can be represented by a matrix $\pmb { A } \in \mathbb { R } ^ { 1 4 3 2 \times 1 9 1 0 }$ , and some outer products $A _ { i } ,$ as defined in (4.90). 

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

Figure 4.11 Image processing with the SVD. (a) The original grayscale image is a $1 , 4 3 2 \times 1 , 9 1 0$ matrix of values between 0 (black) and 1 (white). (b)–(f) Rank-1 matrices 

$A _ { 1 } , \dotsc , A _ { 5 }$ and their corresponding singular values $\sigma _ { 1 } , \ldots , \sigma _ { 5 } .$ The grid-like structure of each rank-1 matrix is imposed by the outer-product of the left and right-singular vectors. 

![image](<Images/04_Matrix_Decompositions_image_028.jpg>)



(a) Original image A.


![image](<Images/04_Matrix_Decompositions_image_029.jpg>)



Matrix Decompositions



(b) A , σ ≈ 228, 052.


![image](<Images/04_Matrix_Decompositions_image_030.jpg>)



(c) A , σ ≈ 40, 647.


![image](<Images/04_Matrix_Decompositions_image_031.jpg>)



(d) $\pmb { A } _ { 3 }$ , $\sigma _ { 3 }$ ≈ 26, 125.


![image](<Images/04_Matrix_Decompositions_image_032.jpg>)



(e) $\mathbf { A } _ { 4 } ,$ $\sigma _ { 4 }$ ≈ 20, 232.


![image](<Images/04_Matrix_Decompositions_image_033.jpg>)



(f) $A _ { 5 } ,$ $\sigma _ { 5 }$ ≈ 15, 436.


A matrix $\pmb { A } \in \mathbb { R } ^ { m \times n }$ of rank r can be written as a sum of rank-1 matrices $\mathbf { A } _ { i }$ so that 

$$
\boldsymbol {A} = \sum_ {i = 1} ^ {r} \sigma_ {i} \boldsymbol {u} _ {i} \boldsymbol {v} _ {i} ^ {\top} = \sum_ {i = 1} ^ {r} \sigma_ {i} \boldsymbol {A} _ {i},\tag{4.91}
$$

where the outer-product matrices $A _ { i }$ are weighted by the ith singular value $\sigma _ { i }$ . We can see why (4.91) holds: The diagonal structure of the singular value matrix Σ multiplies only matching left- and right-singular vectors $\mathbf { \boldsymbol { u } } _ { i } \mathbf { \boldsymbol { v } } _ { i } ^ { \top }$ and scales them by the corresponding singular value $\sigma _ { i }$ . All terms $\begin{array} { r } { \sum _ { i j } { \pmb u } _ { i } { \pmb v } _ { j } ^ { \top } } \end{array}$ vanish for $i \neq j$ because Σ is a diagonal matrix. Any terms $i > r$ vanish because the corresponding singular values are 0. 

In (4.90), we introduced rank-1 matrices $A _ { i }$ . We summed up the $r$ individual rank-1 matrices to obtain a rank-r matrix $A ;$ see (4.91). If the sum does not run over all matrices $A _ { i } , i = 1 , \ldots , r ,$ but only up to an intermediate value $k < r$ , we obtain a rank-k approximation 

$$
\widehat {\boldsymbol {A}} (k) := \sum_ {i = 1} ^ {k} \sigma_ {i} \boldsymbol {u} _ {i} \boldsymbol {v} _ {i} ^ {\top} = \sum_ {i = 1} ^ {k} \sigma_ {i} \boldsymbol {A} _ {i}\tag{4.92}
$$

of A with r $\hat { \bf \Phi } ( \widehat { \bf A } ( k ) ) = k$ . Figure 4.12 shows low-rank approximations $\hat { \bf A } ( k )$ of an original image A of Stonehenge. The shape of the rocks becomes increasingly visible and clearly recognizable in the rank-5 approximation. While the original image requires 1, 432 1, 910 = 2, 735, 120 numbers, the rank-5 approximation requires us only to store the five singular values and the five left- and right-singular vectors (1, 432 and 1, 910- dimensional each) for a total of $5 \cdot ( 1 , 4 3 2 + 1 , 9 1 0 + 1 ) = 1 6$ , 715 numbers – just above 0.6% of the original. 

To measure the difference (error) between A and its rank-k approximation $\hat { \bf A } ( k )$ , we need the notion of a norm. In Section 3.1, we already used 

## 4.6 Matrix Approximation

![image](<Images/04_Matrix_Decompositions_image_034.jpg>)



(a) Original image A.


![image](<Images/04_Matrix_Decompositions_image_035.jpg>)


![image](<Images/04_Matrix_Decompositions_image_036.jpg>)



(b) Rank-1 approximation Ab (1).(c) Rank-2 approximation $\widehat { \mathbf { A } } ( 2 )$


![image](<Images/04_Matrix_Decompositions_image_037.jpg>)



Figure 4.12 Image reconstruction with the SVD. (a) Original image. (b)–(f) Image reconstruction using the low-rank approximation of the SVD, where the rank-k approximation is given by Ab (k) = $\textstyle \sum _ { i = 1 } ^ { k } \sigma _ { i } A _ { i }$


![image](<Images/04_Matrix_Decompositions_image_038.jpg>)


![image](<Images/04_Matrix_Decompositions_image_039.jpg>)



(d) Rank-3 approximation $\widehat { \mathbf { A } } ( 3 )$ .(e) Rank-4 approximation Ab (4).(f) Rank-5 approximation $\widehat { \mathbf { A } } ( 5 )$


norms on vectors that measure the length of a vector. By analogy we can also define norms on matrices. 

Definition 4.23 (Spectral Norm of a Matrix). For $\pmb { x } \in \mathbb { R } ^ { n } \backslash \{ \mathbf { 0 } \}$ , the spectral norm of a matrix $\pmb { A } \in \mathbb { R } ^ { m \times n }$ is defined as 

$$
\| \boldsymbol {A} \| _ {2} := \max _ {\boldsymbol {x}} \frac {\| \boldsymbol {A x} \| _ {2}}{\| \boldsymbol {x} \| _ {2}}.\tag{4.93}
$$

We introduce the notation of a subscript in the matrix norm (left-hand side), similar to the Euclidean norm for vectors (right-hand side), which has subscript 2. The spectral norm (4.93) determines how long any vector x can at most become when multiplied by A. 

Theorem 4.24. The spectral norm of A is its largest singular value $\sigma _ { 1 }$ . 

We leave the proof of this theorem as an exercise. 

Theorem 4.25 (Eckart-Young Theorem (Eckart and Young, 1936)). Consider a matrix $\pmb { A } \in \mathbb { R } ^ { m \times n }$ of rank r and let $B \in \mathbb { R } ^ { m \times n }$ be a matrix of rank k. For any $k \leqslant r$ with $\begin{array} { r } { \hat { \pmb { A } } ( k ) = \sum _ { i = 1 } ^ { k } \sigma _ { i } \pmb { u } _ { i } \pmb { v } _ { i } ^ { \top } } \end{array}$ it holds that 

$$
\widehat {\boldsymbol {A}} (k) = \operatorname{argmin} _ {\mathrm{rk} (\boldsymbol {B}) = k} \left\| \boldsymbol {A} - \boldsymbol {B} \right\| _ {2},\tag{4.94}
$$

$$
\left\| \pmb {A} - \widehat {\pmb {A}} (k) \right\| _ {2} = \sigma_ {k + 1}.\tag{4.95}
$$

The Eckart-Young theorem states explicitly how much error we introduce by approximating A using a rank-k approximation. We can interpret the rank-k approximation obtained with the SVD as a projection of the full-rank matrix A onto a lower-dimensional space of rank-at-most-k matrices. Of all possible projections, the SVD minimizes the error (with respect to the spectral norm) between A and any rank-k approximation. 

We can retrace some of the steps to understand why (4.95) should hold. 

We observe that the difference between $A - { \widehat { A } } ( k )$ is a matrix containing the sum of the remaining rank-1 matrices 

$$
\boldsymbol {A} - \widehat {\boldsymbol {A}} (k) = \sum_ {i = k + 1} ^ {r} \sigma_ {i} \boldsymbol {u} _ {i} \boldsymbol {v} _ {i} ^ {\top}.\tag{4.96}
$$

By Theorem 4.24, we immediately obtain $\sigma _ { k + 1 }$ as the spectral norm of the difference matrix. Let us have a closer look at (4.94). If we assume that there is another matrix B with $\operatorname { r k } ( B ) \leqslant k$ , such that 

$$
\left\| \boldsymbol {A} - \boldsymbol {B} \right\| _ {2} <   \left\| \boldsymbol {A} - \widehat {\boldsymbol {A}} (k) \right\| _ {2},\tag{4.97}
$$

then there exists an at least $( n - k )$ -dimensional null space $Z \subseteq \mathbb { R } ^ { n }$ , such that $\mathbf { \boldsymbol { x } } \in Z$ implies that $\pmb { B x = 0 }$ . Then it follows that 

$$
\left\| \boldsymbol {A} \boldsymbol {x} \right\| _ {2} = \left\| (\boldsymbol {A} - \boldsymbol {B}) \boldsymbol {x} \right\| _ {2},\tag{4.98}
$$

and by using a version of the Cauchy-Schwartz inequality (3.17) that encompasses norms of matrices, we obtain 

$$
\left\| \boldsymbol {A} \boldsymbol {x} \right\| _ {2} \leqslant \left\| \boldsymbol {A} - \boldsymbol {B} \right\| _ {2} \left\| \boldsymbol {x} \right\| _ {2} <   \sigma_ {k + 1} \left\| \boldsymbol {x} \right\| _ {2}.\tag{4.99}
$$

However, there exists a $( k + 1 )$ )-dimensional subspace where $\left. A x \right. _ { 2 } \geqslant$ $\sigma _ { k + 1 } \left\| \pmb { x } \right\| _ { 2 } ,$ which is spanned by the right-singular vectors $v _ { j } , j \leqslant k + 1$ of A. Adding up dimensions of these two spaces yields a number greater than $n ,$ as there must be a nonzero vector in both spaces. This is a contradiction of the rank-nullity theorem (Theorem 2.24) in Section 2.7.3. 

The Eckart-Young theorem implies that we can use SVD to reduce a rank-r matrix A to a rank-k matrix $\hat { \pmb { A } }$ in a principled, optimal (in the spectral norm sense) manner. We can interpret the approximation of A by a rank-k matrix as a form of lossy compression. Therefore, the low-rank approximation of a matrix appears in many machine learning applications, e.g., image processing, noise filtering, and regularization of ill-posed problems. Furthermore, it plays a key role in dimensionality reduction and principal component analysis, as we will see in Chapter 10. 

## Example 4.15 (Finding Structure in Movie Ratings and Consumers (continued))

Coming back to our movie-rating example, we can now apply the concept of low-rank approximations to approximate the original data matrix. Recall that our first singular value captures the notion of science fiction theme in movies and science fiction lovers. Thus, by using only the first singular value term in a rank-1 decomposition of the movie-rating matrix, we obtain the predicted ratings 

$$
\boldsymbol {A} _ {1} = \boldsymbol {u} _ {1} \boldsymbol {v} _ {1} ^ {\top} = \left[ \begin{array}{l} - 0. 6 7 1 0 \\ - 0. 7 1 9 7 \\ - 0. 0 9 3 9 \\ - 0. 1 5 1 5 \end{array} \right] \left[ \begin{array}{l l l} - 0. 7 3 6 7 & - 0. 6 5 1 5 & - 0. 1 8 1 1 \end{array} \right]\tag{4.100a}
$$

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

$$
= \left[ \begin{array}{c c c} 0. 4 9 4 3 & 0. 4 3 7 2 & 0. 1 2 1 5 \\ 0. 5 3 0 2 & 0. 4 6 8 9 & 0. 1 3 0 3 \\ 0. 0 6 9 2 & 0. 0 6 1 2 & 0. 0 1 7 0 \\ 0. 1 1 1 6 & 0. 0 9 8 7 & 0. 0 2 7 4 \end{array} \right]\tag{4.100b}
$$

This first rank-1 approximation $\pmb { A } _ { 1 }$ is insightful: it tells us that Ali and Beatrix like science fiction movies, such as Star Wars and Bladerunner (entries have values $> 0 . 4 )$ , but fails to capture the ratings of the other movies by Chandra. This is not surprising, as Chandra’s type of movies is not captured by the first singular value. The second singular value gives us a better rank-1 approximation for those movie-theme lovers: 

$$
\begin{array}{r l} \boldsymbol {A} _ {2} & = \boldsymbol {u} _ {2} \boldsymbol {v} _ {2} ^ {\top} = \left[ \begin{array}{c} 0. 0 2 3 6 \\ 0. 2 0 5 4 \\ - 0. 7 7 0 5 \\ - 0. 6 0 3 0 \end{array} \right] \left[ \begin{array}{c c c} 0. 0 8 5 2 & 0. 1 7 6 2 & - 0. 9 8 0 7 \end{array} \right] \\ & = \left[ \begin{array}{c c c} 0. 0 0 2 0 & 0. 0 0 4 2 & - 0. 0 2 3 1 \\ 0. 0 1 7 5 & 0. 0 3 6 2 & - 0. 2 0 1 4 \\ - 0. 0 6 5 6 & - 0. 1 3 5 8 & 0. 7 5 5 6 \\ - 0. 0 5 1 4 & - 0. 1 0 6 3 & 0. 5 9 1 4 \end{array} \right]. \end{array}\tag{4.101a}
$$

(4.101b) 

In this second rank-1 approximation $A _ { 2 }$ , we capture Chandra’s ratings and movie types well, but not the science fiction movies. This leads us to consider the rank-2 approximation $\widehat { \mathbf { A } } ( 2 )$ , where we combine the first two rank-1 approximations 

$$
\widehat {\boldsymbol {A}} (2) = \sigma_ {1} \boldsymbol {A} _ {1} + \sigma_ {2} \boldsymbol {A} _ {2} = \left[ \begin{array}{c c c} 4. 7 8 0 1 & 4. 2 4 1 9 & 1. 0 2 4 4 \\ 5. 2 2 5 2 & 4. 7 5 2 2 & - 0. 0 2 5 0 \\ 0. 2 4 9 3 & - 0. 2 7 4 3 & 4. 9 7 2 4 \\ 0. 7 4 9 5 & 0. 2 7 5 6 & 4. 0 2 7 8 \end{array} \right].\tag{4.102}
$$

$\widehat { \mathbf { A } } ( 2 )$ is similar to the original movie ratings table 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 5 & 4 & 1 \\ 5 & 5 & 0 \\ 0 & 0 & 5 \\ 1 & 0 & 4 \end{array} \right],\tag{4.103}
$$

and this suggests that we can ignore the contribution of $A _ { 3 }$ . We can interpret this so that in the data table there is no evidence of a third movietheme/movie-lovers category. This also means that the entire space of movie-themes/movie-lovers in our example is a two-dimensional space spanned by science fiction and French art house movies and lovers. 

Figure 4.13 A functional phylogeny of matrices encountered in machine learning. 

![image](<Images/04_Matrix_Decompositions_image_040.jpg>)


## 4.7 Matrix Phylogeny

In Chapters 2 and 3, we covered the basics of linear algebra and analytic geometry. In this chapter, we looked at fundamental characteristics of matrices and linear mappings. Figure 4.13 depicts the phylogenetic tree of relationships between different types of matrices (black arrows indicating “is a subset of”) and the covered operations we can perform on them (in blue). We consider all real matrices $\pmb { A } \in \mathbb { R } ^ { n \times m }$ . For non-square matrices (where $n \neq m )$ , the SVD always exists, as we saw in this chapter. Focusing on square matrices $A \in \mathbb { R } ^ { n \times n }$ , the determinant informs us whether a square matrix possesses an inverse matrix, i.e., whether it belongs to the class of regular, invertible matrices. If the square $n \times n$ matrix possesses n linearly independent eigenvectors, then the matrix is non-defective and an eigendecomposition exists (Theorem 4.12). We know that repeated eigenvalues may result in defective matrices, which cannot be diagonalized. 

The word “phylogenetic” describes how we capture the relationships among individuals or groups and derived from the Greek words for “tribe” and “source”. 

Non-singular and non-defective matrices are not the same. For example, a rotation matrix will be invertible (determinant is nonzero) but not diagonalizable in the real numbers (eigenvalues are not guaranteed to be real numbers). 

We dive further into the branch of non-defective square $n \times n$ matrices. A is normal if the condition $\pmb { A } ^ { \top } \pmb { A } = \pmb { A } \pmb { A } ^ { \top }$ holds. Moreover, if the more restrictive condition holds that $\pmb { A } ^ { \top } \pmb { A } = \pmb { A } \pmb { A } ^ { \top } = \pmb { I } ,$ , then A is called orthogonal (see Definition 3.8). The set of orthogonal matrices is a subset of the regular (invertible) matrices and satisfies $\mathbf { \bar { A } } ^ { \top } = A ^ { - 1 }$ 

Normal matrices have a frequently encountered subset, the symmetric matrices $\ b { S } \in \mathbb { R } ^ { n \times n }$ , which satisfy $S \stackrel { \cdot } { = } S ^ { \top }$ . Symmetric matrices have only real eigenvalues. A subset of the symmetric matrices consists of the positive definite matrices P that satisfy the condition of ${ \pmb x } ^ { \top } { \pmb P } { \pmb x } > 0$ for all $\pmb { x } \in \mathbb { R } ^ { n } \backslash \{ \mathbf { 0 } \}$ . In this case, a unique Cholesky decomposition exists (Theorem 4.18). Positive definite matrices have only positive eigenvalues and are always invertible $( \mathrm { i . e . }$ , have a nonzero determinant). 

Another subset of symmetric matrices consists of the diagonal matrices D. Diagonal matrices are closed under multiplication and addition, but do not necessarily form a group (this is only the case if all diagonal entries are nonzero so that the matrix is invertible). A special diagonal matrix is the identity matrix I. 

## 4.8 Further Reading

Most of the content in this chapter establishes underlying mathematics and connects them to methods for studying mappings, many of which are at the heart of machine learning at the level of underpinning software solutions and building blocks for almost all machine learning theory. Matrix characterization using determinants, eigenspectra, and eigenspaces provides fundamental features and conditions for categorizing and analyzing matrices. This extends to all forms of representations of data and map pings involving data, as well as judging the numerical stability of computational operations on such matrices (Press et al., 2007). 

Determinants are fundamental tools in order to invert matrices and compute eigenvalues “by hand”. However, for almost all but the smallest instances, numerical computation by Gaussian elimination outperforms determinants (Press et al., 2007). Determinants remain nevertheless a powerful theoretical concept, e.g., to gain intuition about the orientation of a basis based on the sign of the determinant. Eigenvectors can be used to perform basis changes to transform data into the coordinates of meaningful orthogonal, feature vectors. Similarly, matrix decomposition methods, such as the Cholesky decomposition, reappear often when we compute or simulate random events (Rubinstein and Kroese, 2016). Therefore, the Cholesky decomposition enables us to compute the reparametrization trick where we want to perform continuous differentiation over random variables, e.g., in variational autoencoders (Jimenez Rezende et al., 2014; Kingma and Welling, 2014). 

Eigendecomposition is fundamental in enabling us to extract meaningful and interpretable information that characterizes linear mappings. 

Therefore, the eigendecomposition underlies a general class of machine learning algorithms called spectral methods that perform eigendecomposition of a positive-definite kernel. These spectral decomposition methods encompass classical approaches to statistical data analysis, such as the following: 

Principal component analysis (PCA (Pearson, 1901), see also Chapter 10), in which a low-dimensional subspace, which explains most of the variability in the data, is sought. 

Fisher discriminant analysis, which aims to determine a separating hyperplane for data classification (Mika et al., 1999). 

Multidimensional scaling (MDS) (Carroll and Chang, 1970). 

The computational efficiency of these methods typically comes from finding the best rank-k approximation to a symmetric, positive semidefinite matrix. More contemporary examples of spectral methods have different origins, but each of them requires the computation of the eigenvectors and eigenvalues of a positive-definite kernel, such as Isomap (Tenenbaum et al., 2000), Laplacian eigenmaps (Belkin and Niyogi, 2003), Hessian eigenmaps (Donoho and Grimes, 2003), and spectral clustering (Shi and Malik, 2000). The core computations of these are generally underpinned by low-rank matrix approximation techniques (Belabbas and Wolfe, 2009) as we encountered here via the SVD. 

The SVD allows us to discover some of the same kind of information as the eigendecomposition. However, the SVD is more generally applicable to non-square matrices and data tables. These matrix factorization methods become relevant whenever we want to identify heterogeneity in data when we want to perform data compression by approximation, e.g., instead of storing n m values just storing (n+m)k values, or when we want to perform data pre-processing, e.g., to decorrelate predictor variables of a design matrix (Ormoneit et al., 2001). The SVD operates on matrices, which we can interpret as rectangular arrays with two indices (rows and columns). The extension of matrix-like structure to higher-dimensional arrays are called tensors. It turns out that the SVD is the special case of a more general family of decompositions that operate on such tensors (Kolda and Bader, 2009). SVD-like operations and low-rank approximations on tensors are, for example, the Tucker decomposition (Tucker, 1966) or the CP decomposition (Carroll and Chang, 1970). 

The SVD low-rank approximation is frequently used in machine learning for computational efficiency reasons. This is because it reduces the amount of memory and operations with nonzero multiplications we need to perform on potentially very large matrices of data (Trefethen and Bau III, 1997). Moreover, low-rank approximations are used to operate on matrices that may contain missing values as well as for purposes of lossy compression and dimensionality reduction (Moonen and De Moor, 1995; Markovsky, 2011). 

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

## Exercises

4.1 Compute the determinant using the Laplace expansion (using the first row) and the Sarrus rule for 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 1 & 3 & 5 \\ 2 & 4 & 6 \\ 0 & 2 & 4 \end{array} \right].
$$

4.2 Compute the following determinant efficiently: 

$$
\left[ \begin{array}{c c c c c} 2 & 0 & 1 & 2 & 0 \\ 2 & - 1 & 0 & 1 & 1 \\ 0 & 1 & 2 & 1 & 2 \\ - 2 & 0 & 2 & - 1 & 2 \\ 2 & 0 & 0 & 1 & 1 \end{array} \right].
$$

4.3 Compute the eigenspaces of 

a. 

$$
\boldsymbol {A} := \left[ \begin{array}{c c} 1 & 0 \\ 1 & 1 \end{array} \right]
$$

b. 

$$
\boldsymbol {B} := \left[ \begin{array}{c c} - 2 & 2 \\ 2 & 1 \end{array} \right]
$$

4.4 Compute all eigenspaces of 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c} 0 & - 1 & 1 & 1 \\ - 1 & 1 & - 2 & 3 \\ 2 & - 1 & 0 & 0 \\ 1 & - 1 & 1 & 0 \end{array} \right].
$$

4.5 Diagonalizability of a matrix is unrelated to its invertibility. Determine for the following four matrices whether they are diagonalizable and/or invertible 

$$
\left[ \begin{array}{c c} 1 & 0 \\ 0 & 1 \end{array} \right], \quad \left[ \begin{array}{c c} 1 & 0 \\ 0 & 0 \end{array} \right], \quad \left[ \begin{array}{c c} 1 & 1 \\ 0 & 1 \end{array} \right], \quad \left[ \begin{array}{c c} 0 & 1 \\ 0 & 0 \end{array} \right].
$$

4.6 Compute the eigenspaces of the following transformation matrices. Are they diagonalizable? 

a. For 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 2 & 3 & 0 \\ 1 & 4 & 3 \\ 0 & 0 & 1 \end{array} \right]
$$

b. For 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c} 1 & 1 & 0 & 0 \\ 0 & 0 & 0 & 0 \\ 0 & 0 & 0 & 0 \\ 0 & 0 & 0 & 0 \end{array} \right]
$$

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

4.7 Are the following matrices diagonalizable? If yes, determine their diagonal form and a basis with respect to which the transformation matrices are diagonal. If no, give reasons why they are not diagonalizable. 

a. 

$$
\mathbf {A} = \left[ \begin{array}{l l} 0 & 1 \\ - 8 & 4 \end{array} \right]
$$

b. 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 1 & 1 & 1 \\ 1 & 1 & 1 \\ 1 & 1 & 1 \end{array} \right]
$$

c. 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c c} 5 & 4 & 2 & 1 \\ 0 & 1 & - 1 & - 1 \\ - 1 & - 1 & 3 & 0 \\ 1 & 1 & - 1 & 2 \end{array} \right]
$$

d. 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 5 & - 6 & - 6 \\ - 1 & 4 & 2 \\ 3 & - 6 & - 4 \end{array} \right]
$$

4.8 Find the SVD of the matrix 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 3 & 2 & 2 \\ 2 & 3 & - 2 \end{array} \right].
$$

4.9 Find the singular value decomposition of 

$$
\boldsymbol {A} = \left[ \begin{array}{c c} 2 & 2 \\ - 1 & 1 \end{array} \right].
$$

4.10 Find the rank-1 approximation of 

$$
\boldsymbol {A} = \left[ \begin{array}{c c c} 3 & 2 & 2 \\ 2 & 3 & - 2 \end{array} \right]
$$

4.11 Show that for any $\pmb { A } \in \mathbb { R } ^ { m \times n }$ the matrices $A ^ { \top } A$ and $A A ^ { \top }$ possess the same nonzero eigenvalues. 

4.12 Show that for x $\neq \mathbf { 0 }$ Theorem 4.24 holds, i.e., show that 

$$
\max _ {\boldsymbol {x}} \frac {\| \boldsymbol {A} \boldsymbol {x} \| _ {2}}{\| \boldsymbol {x} \| _ {2}} = \sigma_ {1},
$$

where $\sigma _ { 1 }$ is the largest singular value of $\pmb { A } \in \mathbb { R } ^ { m \times n }$ 