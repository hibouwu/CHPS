# Singular Value Decomposition

“The SVD is absolutely a high point of linear algebra.”– Gilbert Strang and Kae Borre 

## 7.1 Introduction

In Chapter 3, we learned that certain types of matrices, which are referred to as positive semidefinite matrices, can be expressed in the following form: 

$$
A = V \Delta V ^ {T}
$$

Here, V is a $d \times d$ matrix with orthonormal columns, and $\Delta$ is a $d \times d$ diagonal matrix with nonnegative eigenvalues of $A .$ The orthogonal matrix $V$ can also be viewed as a rotation/reflection matrix, the diagonal matrix $\Delta$ as a nonnegative scaling matrix along axes directions, and the matrix $V ^ { T }$ is the inverse of $V$ . By factorizing the matrix A into simpler matrices, we are expressing a linear transform as a sequence of simpler linear transformations (such as rotation and scaling). This chapter will study the generalization of this type of factorization to arbitrary matrices. This generalized form of factorization is referred to as singular value decomposition. 

Singular value decomposition generalizes the factorization approach to arbitrary matrices that might not even be square. Given an $n \times d$ matrix B, singular value decomposition decomposes it as follows: 

$$
B = Q \Sigma P ^ {T}
$$

Here, $B$ is an $n \times d$ matrix, $Q$ is an $n \times n$ matrix with orthonormal columns, $\Sigma$ is an $n \times d$ rectangular diagonal matrix with nonnegative entries, and P is a $d \times d$ matrix with orthonormal columns. The notion of a rectangular diagonal matrix is discussed in Figure 1.3 of Chapter 1 in which only entries with indices of the form (i, i) (i.e., with the same row and column indices) are non-zero. The columns of $Q$ and the columns of $P$ are referred to as $l e f t$ singular vectors and right singular vectors, respectively. The entries of $\Sigma$ are referred to as singular values, and they are arranged in non-increasing order (by convention). We emphasize that the diagonal matrix Σ is nonnegative. 

Singular value decomposition has some insightful linear algebra properties in terms of enabling the discovery of all four fundamental subspaces of the matrix B. Furthermore, if exact decomposition is not essential, singular value decomposition provides the ability to approximate B very well with small portions of the factor matrices Q, P, and Σ. This is an optimization-centric view of singular value decomposition. The optimization-centric view naturally generalizes to the broader concept of low-rank matrix factorization, which lies at the heart of many machine learning applications (cf. Chapter 8). 

We will first approach singular value decomposition simply from a linear algebra point of view, as a way of exploring the row and column spaces of a matrix. This view is, however, incomplete because it does not provide an understanding of the compression-centric properties of singular value decomposition. Therefore, we will also present singular value de composition in terms of the optimization-centric view together with its natural applications to compression and dimensionality reduction. 

This chapter is organized as follows. In the next section, we will introduce singular value decomposition from the point of view of linear algebra. An optimization-centric view of singular value decomposition is presented in Section 7.3. Both these views expose somewhat different properties of singular value decomposition. Singular value decomposition (SVD) has numerous applications in machine learning, and an overview is provided in Section 7.4. Numerical algorithms for singular value decomposition are introduced in Section 7.5. A summary is given in Section 7.6. 

## 7.2 SVD: A Linear Algebra Perspective

Singular value decomposition (SVD) is a generalization of the concept of diagonalization, which is discussed in Chapter 3. While diagonalization with nonnegative eigenvalues and orthogonal eigenvectors is only assured for square, symmetric, and positive semidefinite matrices, singular value decomposition is assured for any matrix, irrespective of its size or other properties. Since we have already explored the diagonalization of square matrices, we will first study the singular value decomposition of square matrices in order to show how singular value decomposition is a natural generalization of diagonalization. Then, we wil generalize these ideas to rectangular matrices. 

## 7.2.1 Singular Value Decomposition of a Square Matrix

In this section, we will discuss the existence of a singular value decomposition of a square m m matrix B. First, we note that the matrices $B ^ { \check { T } } B$ and $B B ^ { T }$ are positive semidefinite and symmetric (cf. Lemma 3.3.14 of Chapter 3). Therefore, these matrices are diagonalizable with orthonormal eigenvectors and nonnegative eigenvalues. In the following, we show that these matrices share eigenvalues, and their eigenvectors are also related. 

Lemma 7.2.1 Let B be a square, m m matrix. Then, the following results are true: 

1. $I f { \overline { { p } } }$ is a unit eigenvector of $B ^ { T } B$ with non-zero eigenvalue λ, then Bp is an eigenvector of $B B ^ { T }$ with the same eigenvalue λ. Furthermore, the norm of Bp is $\sqrt { \lambda }$ 

2. $I f \overline { { q } }$ is a unit eigenvector of $B B ^ { T }$ with non-zero eigenvalue λ, then $B ^ { T } \overline { { { q } } }$ is an eigenvector of $B ^ { T } B$ with the same eigenvalue λ. Furthermore, the norm of $B ^ { T } \overline { { { q } } }$ is $\sqrt { \lambda }$ 

Proof: We only show the first part of the above result, because the proof of the second part is exactly identical by working with $B ^ { T }$ instead of B throughout the proof. $\operatorname { I f } { \overline { { p } } }$ is an eigenvector of $B ^ { T } B$ with eigenvalue λ, we have the following: 

$$
\begin{array}{r l} & B ^ {T} B \overline {{p}} = \lambda \overline {{p}} \\ & B B ^ {T} [ B \overline {{p}} ] = \lambda [ B \overline {{p}} ] \quad \{\mathrm{Pre-multiplyingwith} B \} \end{array}
$$

In other words, Bp is an eigenvector of $B B ^ { T }$ with eigenvalue λ. 

The squared norm of Bp may be computed as follows: 

$$
\begin{array}{c} \| B \overline {{p}} \| ^ {2} = [ p ^ {T} B ^ {T} ] [ B \overline {{p}} ] = p ^ {T} \underbrace {[ B ^ {T} B \overline {{p}} ]} _ {\lambda \overline {{p}}} \\ = \overline {{p}} ^ {T} [ \lambda \overline {{p}} ] = \lambda \| \overline {{p}} \| ^ {2} = \lambda \end{array}
$$

The last of these equalities follows from the fact that $\overline { { p } }$ is a unit eigenvector. Since the squared norm of Bp is λ, it follows that the norm of Bp is $\sqrt { \lambda }$ 

The pairing of the eigenvectors/eigenvalues of $B ^ { T } B$ and $B B ^ { T }$ can also be expressed as the following corollary: 

Corollary 7.2.1 (Eigenvector Pairing) Let B be a square, m m matrix. Then, the matrices $B ^ { T } B$ and BB<sup>T</sup> have the same set of m eigenvalues $\lambda _ { 1 } \ldots \lambda _ { m }$ . Let the m orthonormal eigenvectors of the symmetric matrix $B ^ { T } B$ be denoted by $\overline { { p } } _ { 1 } \ldots . \overline { { p } } _ { m }$ with eigenvalues $\lambda _ { 1 } \ldots \lambda _ { m }$ . Then, it is possible to find m orthonormal eigenvectors $\overline { { q } } _ { 1 } \ldots . \overline { { q } } _ { m }$ of $B \bar { B } ^ { T }$ , such that the following holds: 

$$
\overline {{q}} _ {i} \sqrt {\lambda_ {i}} = B \overline {{p}} _ {i}
$$

Proof: This proof works by defining each $\overline { { q } } _ { i }$ as a function of ${ \overline { { p } } } _ { i }$ . Let there be $r \leq m$ nonzero eigenvalues. In the case when ${ \overline { { p } } } _ { i }$ is associated with a non-zero eigenvalue, we define $\overline { { q } } _ { i } = B \overline { { p } } _ { i } / \sqrt { \lambda _ { i } } .$ , and Lemma 7.2.1 ensures that each $\overline { { q } } _ { i }$ is a unit eigenvector of $B B ^ { T }$ . The extracted eigenvectors $\overline { { q } } _ { 1 } \ldots \overline { { q } } _ { r }$ for non-zero eigenvalues are orthogonal to one another: 

$$
\overline {{q}} _ {i} ^ {T} \overline {{q}} _ {j} = (B \overline {{p}} _ {i}) ^ {T} (B \overline {{p}} _ {j}) / \lambda = \overline {{p}} _ {i} ^ {T} ([ B ^ {T} B ] \overline {{p}} _ {j}) / \lambda = \overline {{p}} _ {i} ^ {T} \overline {{p}} _ {j} = 0
$$

Next, we focus on the remaining $( m - r )$ zero eigenvectors of both $B ^ { T } B$ and $B B ^ { T }$ . Anyzero eigenvector $\overline { { q } } _ { i }$ of $B B ^ { T }$ and any zero eigenvector of $B ^ { T } B$ trivially satisfies $\overline { { q } } _ { i } \sqrt { \lambda _ { i } } = B \overline { { p } } _ { i }$ because both sides evaluate to zero. The key point is that $B ^ { T } B \overline { { p } } _ { i } = \overline { { 0 } }$ implies that $B { \overline { { p } } } _ { i } = { \overline { { 0 } } }$ (see Exercise 2 of Chapter 2). Therefore, we can pair the zero eigenvectors of $B ^ { T } B$ and$\dot { B } B ^ { T }$ arbitrarily. 厂

Corollary 7.2.1 provides a way of pairing the eigenvectors of $B ^ { T } B$ and $B B ^ { T }$ in such a way that the condition $\overline { { q } } _ { i } \sqrt { \lambda _ { i } } = B \overline { { p } } _ { i }$ is always satisfied for any pair of eigenvectors $( \overline { { p } } _ { i } , \overline { { q } } _ { i } )$ . This observation can be used to write these paired relationships in matrix form. This way of expressing the pairing is referred to as singular value decomposition. 

Theorem 7.2.1 (Existence of SVD) Let the columns of the m m matrix P contain the m orthonormal eigenvectors of the m m matrix $B ^ { T } B$ , and let Σ be an m m diagonal matrix with diagonal entries containing the square-root of the corresponding eigenvalues. By convention, the columns of P and Σ are ordered, so that the singular values are in nonincreasing order. Then, it is possible to find an m m orthogonal matrix Q containing the orthonormal eigenvectors of $\bar { B } B ^ { T }$ , such that the following holds: 

$$
B = Q \Sigma P ^ {T}
$$

Proof: Corollary 7.2.1 ensures that for any ordered set $\overline { { p } } _ { 1 } \dots \overline { { p } } _ { m }$ of eigenvectors of $B ^ { T } B .$ an ordered set $\overline { { q } } _ { 1 } \ldots . \overline { { q } } _ { m }$ of eigenvectors of $\dot { B } B ^ { T }$ exists, so that the following is satisfied for each $i \in \{ 1 \ldots m \}$ : 

$$
\overline {{q}} _ {i} \sqrt {\lambda} = B \overline {{p}} _ {i}
$$

One can write the m vector-centric relationships as a single matrix-centric relationship: 

$$
[ \overline {{q}} _ {1}, \dots , \overline {{q}} _ {m} ] \Sigma = B [ \overline {{p}} _ {1} \dots \overline {{p}} _ {m} ]
$$

Here, $\Sigma$ is an $m \times m$ diagonal matrix whose $( i , i )$ th entry is $\sqrt { \lambda _ { i } }$ . One can write the above relationship in the following form: 

$$
Q \Sigma = B P
$$

Here, $P$ is an $m \times m$ orthogonal matrix with columns containing $\overline { { p } } _ { 1 } \dots \overline { { p } } _ { m }$ , and $Q$ is an $m \times m$ orthogonal matrix with columns containing $\overline { { q } } _ { 1 } \ldots \overline { { q } } _ { m }$ . Post-multiplication of both sides with$P ^ { T }$ and setting $P P ^ { T } = I$ yields $Q \Sigma P ^ { T } = B$ . Therefore, a singular value decomposition ofa square matrix B always exists. 厂

Consider the following matrix B and its derived scatter matrix $B ^ { T } B ;$ 

$$
B = \left[ \begin{array}{c c c} 1 4 & 8 & - 6 \\ 2 1 & 1 1 & 1 4 \\ 1 6 & - 6 & 2 \end{array} \right], \quad B ^ {T} B = \left[ \begin{array}{c c c} 8 9 3 & 2 4 7 & 2 4 2 \\ 2 4 7 & 2 2 1 & 9 4 \\ 2 4 2 & 9 4 & 2 3 6 \end{array} \right]
$$

On performing the eigendecomposition of $B ^ { T } B$ we obtain eigenvectors proportional to $[ 3 , 1 , 1 ] ^ { T } , \ [ 1 , - 1 , - 2 ] ^ { T }$ , and $[ 1 , - 7 , 4 ] ^ { T }$ (although the vectors need to be unit normalized to create $P )$ . The corresponding eigenvalues are 1052, 162, and 232, and the square-roots of these eigenvalues are the singular values, which can be used to create the diagonal matrix $\Sigma .$ Since we have $B = Q \Sigma P ^ { \breve { T } }$ , the matrix $Q$ can then be obtained as $B P \Sigma ^ { - 1 }$ , which is as follows: 

$$
Q = \underbrace {\left[ \begin{array}{c c c} 1 4 & 8 & - 6 \\ 2 1 & 1 1 & 1 4 \\ 1 6 & - 6 & 2 \end{array} \right]} _ {B} \underbrace {\left[ \begin{array}{c c c} 3 / \sqrt {1 1} & 1 / \sqrt {6} & 1 / \sqrt {6 6} \\ 1 / \sqrt {1 1} & - 1 / \sqrt {6} & - 7 / \sqrt {6 6} \\ 1 / \sqrt {1 1} & - 2 / \sqrt {6} & 4 / \sqrt {6 6} \end{array} \right]} _ {P} \underbrace {\left[ \begin{array}{c c c} 4 \sqrt {6 6} & 0 & 0 \\ 0 & 9 \sqrt {2} & 0 \\ 0 & 0 & 2 \sqrt {3 3} \end{array} \right] ^ {- 1}} _ {\Sigma^ {- 1}}
$$

Upon performing this multiplication, we obtain a matrix $Q$ whose columns are proportional to $[ 1 , \bar { 2 } , 1 ] ^ { T } , [ 1 , \bar { - 1 } , 1 ] ^ { T }$ , and $[ - 1 , 0 , 1 ] ^ { T }$ , although the matrix $Q$ is obtained in terms of unit normalized columns. Therefore, the $S V D$ of matrix B can be expressed as $Q \Sigma P ^ { T }$ as follows: 

$$
\underbrace {\left[ \begin{array}{c c c} 1 / \sqrt {6} & 1 / \sqrt {3} & - 1 / \sqrt {2} \\ 2 / \sqrt {6} & - 1 / \sqrt {3} & 0 \\ 1 / \sqrt {6} & 1 / \sqrt {3} & 1 / \sqrt {2} \end{array} \right]} _ {Q} \underbrace {\left[ \begin{array}{c c c} 4 \sqrt {6 6} & 0 & 0 \\ 0 & 9 \sqrt {2} & 0 \\ 0 & 0 & 2 \sqrt {3 3} \end{array} \right]} _ {\Sigma} \underbrace {\left[ \begin{array}{c c c} 3 / \sqrt {1 1} & 1 / \sqrt {6} & 1 / \sqrt {6 6} \\ 1 / \sqrt {1 1} & - 1 / \sqrt {6} & - 7 / \sqrt {6 6} \\ 1 / \sqrt {1 1} & - 2 / \sqrt {6} & 4 / \sqrt {6 6} \end{array} \right] ^ {T}} _ {P ^ {T}}
$$

One important point is that we derived $Q$ from $P ,$ rather than independently diagonalizing $B B ^ { T }$ and $B ^ { T } B _ { : }$ , and doing the latter might lead to incorrect results because of sign dependence between $Q$ and $P .$ For example, one could use $- Q$ and $- P$ as the decomposition matrices without changing the product of the matrices. However, we cannot use $- Q$ and $P$ to create an SVD. The signs of matching pairs of singular vectors are also interdependent. 

SVD also decomposes non-diagonalizable matrices, such as the following: 

$$
\left[ \begin{array}{c c} 0 & - 7 \\ 0 & 0 \end{array} \right] = \underbrace {\left[ \begin{array}{c c} - 1 & 0 \\ 0 & 1 \end{array} \right]} _ {Q} \underbrace {\left[ \begin{array}{c c} 7 & 0 \\ 0 & 0 \end{array} \right]} _ {\Sigma} \underbrace {\left[ \begin{array}{c c} 0 & 1 \\ 1 & 0 \end{array} \right]} _ {P ^ {T}}
$$

Note that the above matrix has no diagonalization, since it is nilpotent (see Exercise 26 of Chapter 3). However, it has a valid singular value decomposition. Furthermore, even though this matrix only has zero eigenvalues, it has a non-zero singular value of 7, containing one of the key scaling factors of the transformation. In fact, SVD has the neat property of relating arbitrary (square) matrices to positive semidefinite ones with the use of polar decomposition, which explicitly separates out the rotreflection matrix from the scaling (positive semidefinite) matrix: 

Lemma 7.2.2 (Polar Decomposition) Any square matrix can be expressed in the form US, where U is an orthogonal matrix, and S is a symmetric positive semidefinite matrix. 

Proof: One can write the SVD of a square matrix as $Q \Sigma P ^ { T } = ( Q P ^ { T } ) ( P \Sigma P ^ { T } )$ . The matrix$Q P ^ { T }$ can be set to $U ,$ and it is orthogonal because of the closure of orthogonal matricesunder multiplication (cf. Chapter 2). Furthermore, S can be set to $P \Sigma P ^ { T }$ , which is positivesemidefinite because of the nonnegativity of Σ. 厂

The polar decomposition is geometrically insightful, because it tells us that every matrix multiplication causes an anisotropic scaling along orthogonal directions with nonnegative scale factors, followed by rotreflection. When the rotreflection component is missing, the resulting matrix is positive semidefinite. The matrix U is also the nearest orthogonal matrix to B, just as $[ \cos ( \theta ) , \sin ( \theta ) ] ^ { T }$ is the nearest unit vector to the polar coordinates $r [ \cos ( \theta ) , \sin ( \theta ) ] ^ { T }$ 

Problem 7.2.1 Let B be a symmetric and square matrix, which is negative semidefinite. Show that the singular value decomposition of B is of the form $B = Q \Sigma P ^ { T }$ , where $Q = - P$ 

The important point of the previous exercise is to emphasize the fact that the singular values need to be nonnegative. We provide another exercise to emphasize this fact: 

Problem 7.2.2 Suppose that somebody gave you an $m \times m$ matrix B and a decomposition of the form $B = Q \Sigma P ^ { T }$ , where Q and P are both orthogonal matrices of size $m \times m$ , and Σ is an m m diagonal matrix. However, you are told that some of the entries of Σ are negative. Discuss how you would adjust the decomposition in order to convert it into a standard form of singular value decomposition. 

Problem 7.2.3 Suppose that the eigendecomposition of a $3 \times 3$ symmetric matrix A can be written as follows: 

$$
A = V \Delta V ^ {T} = \left[ \begin{array}{l l l} v _ {1 1} & v _ {1 2} & v _ {1 3} \\ v _ {2 1} & v _ {2 2} & v _ {2 3} \\ v _ {3 1} & v _ {3 2} & v _ {3 3} \end{array} \right] \left[ \begin{array}{l l l} 5 & 0 & 0 \\ 0 & - 2 & 0 \\ 0 & 0 & - 3 \end{array} \right] \left[ \begin{array}{l l l} v _ {1 1} & v _ {2 1} & v _ {3 1} \\ v _ {1 2} & v _ {2 2} & v _ {3 2} \\ v _ {1 3} & v _ {2 3} & v _ {3 3} \end{array} \right]
$$

What is the singular value decomposition of this matrix? 

The number of non-zero singular values yields the rank of the original matrix. 

Lemma 7.2.3 Let B be an $m \times m$ matrix with rank $k \leq m$ . Let the singular value decomposition of B be $B = Q \Sigma P ^ { T }$ , where $Q , \Sigma$ , and $P ^ { T }$ are $m \times m$ matrices. Then, exactly $m - k$ singular values must be zeros. 

Proof: As discussed in Corollary 2.6.3, multiplication with a non-singular (or orthogonal) matrix does not change the rank of a matrix. Therefore, the rank of $B = Q \Sigma P ^ { T }$ is the same as that of Σ. Since the rank of Σ is equal to the number of non-zero singular values, the result follows. 

## 7.2.2 Square SVD to Rectangular SVD via Padding

Consider the special case in which the matrix B is obtained by padding an $n \times d$ matrix D with additional rows or columns of zero values, so that we have a square matrix B with $m = \operatorname* { m a x } \{ n , d \}$ rows and columns. This type of padding leads to natural way of performing SVD of rectangular matrices because portions of the (unnecessarily large) factored matrices of the padded matrix can be extracted to create a decomposition of the original matrix (without the padding). For example, while working with an $n \times d$ matrix denoted by $D ,$ one can factorize it into a sequence of an $n \times n$ orthogonal matrix, an $n \times d$ rectangular diagonal matrix, and ${ \textbf { a } } d \times d$ orthogonal matrix. These three (smaller) matrices can be extracted directly as portions of the three (larger) factors of the $m \times m$ matrix B. Consider a situation where an $n \times d$ matrix D is padded with zeros (in either rows or columns) in order to obtain the square matrix B. In such cases, it can be shown that singular value decomposition has one of the following two types of block diagonal structures of factor matrices: 

Lemma 7.2.4 (Block Diagonal Structure of Padded SVD) Let B be an m $\times \textit { m }$ matrix obtained by padding the $n \times d$ matrix D with either zero rows or zero columns, where $m = m a x \{ n , d \}$ . Then, depending on whether n or d is greater, a singular value decomposition $B = { \bar { Q } } \Sigma { \bar { P } } ^ { T }$ exists with one of the following two types of forms: 

$$
B = [ D 0 ] = Q \underbrace {\left[ \begin{array}{c c} \Sigma_ {1} & 0 \\ 0 & 0 \end{array} \right]} _ {\Sigma} \underbrace {\left[ \begin{array}{c c} P _ {1} & 0 \\ 0 & P _ {2} \end{array} \right] ^ {T}} _ {P ^ {T}}, \quad [ W h e n d <   n ]
$$

$$
B = \left[ \begin{array}{c} D \\ 0 \end{array} \right] = \underbrace {\left[ \begin{array}{c c} Q _ {1} & 0 \\ 0 & Q _ {2} \end{array} \right]} _ {Q} \underbrace {\left[ \begin{array}{c c} \Sigma_ {1} & 0 \\ 0 & 0 \end{array} \right]} _ {\Sigma} P ^ {T}, [ W h e n n <   d ]
$$

The matrices, $Q , P _ { i }$ , and Σ are all of sizes $m \times m$ , as is normally the case for square $S V D$ The matrix $P _ { 1 }$ is of size $d \times d ,$ and $Q _ { 1 } \textit { i s }$ of size $n \times n$ . The matrices $P _ { 2 }$ and $Q _ { 2 }$ are of sizes $( m - d ) \times ( m - d )$ and $( m - n ) \times ( m - n )$ , respectively. The matrix $\Sigma _ { 1 }$ is of size min $\{ n , d \} \times m i n \{ n , d \}$ 

Proof Sketch: Consider the first case above where $B = [ D \ 0 ]$ and $d < n$ . In such a case, $B ^ { T } B$ will only have a single non-zero block of size $d \times d$ in the upper-left corner. As a result, it will have at most d non-zero eigenvalues, the square-roots of which can be used to create the $d \times d$ diagonal matrix $\Sigma _ { 1 }$ . The eigenvectors of its upper-left block will be contained in the $d \times d$ matrix $P _ { 1 }$ . Let the $( n - d ) \times ( n - d )$ matrix $P _ { 2 }$ be created by stacking up any set of $( n - d )$ orthonormal column vectors in $\mathcal { R } ^ { ( n - d ) }$ . It remains to show that if matrix $P$ and $\Sigma$ are constructed using $P _ { 1 } , P _ { 2 }$ , and $\Sigma _ { 1 }$ using the block structure shown on the right-hand side of the first relationship above, then $( \mathrm { i } ) \ P$ will contains both the non-zero and zero eigenvectors of $B ^ { T } B$ , and (ii) the matrix $\Sigma ^ { 2 }$ contains the eigenvalues of $B ^ { T } B$ . This can be achieved by showing that the ith column of $P$ is a right-eigenvector of $B ^ { T } B$ with the corresponding eigenvalue contained in the ith diagonal entry of $\Sigma ^ { 2 }$ . The result holds because for $i \leq d ,$ the eigenvectors and eigenvalues are inherited from eigenvectors of the upper-left block of $B ^ { T } B$ with size $d { \times } d .$ . These eigenvectors are contained in $P _ { 1 }$ and the padding simply adds $( n - d )$ zero values both to the ith column of $B ^ { T } B$ and to the ith column of $P .$ . For $i > d ,$ , any n-dimensional vector with zero values in the first $d$ components can be shown to be an eigenvector of $B ^ { T } B$ (with 0 eigenvalue) because of the block structure of $B ^ { T } B$ Furthermore, the matrix $P$ can be shown to be orthogonal because both of its blocks are orthogonal matrices. The matrix $Q$ can be extracted from B, Σ, and $P$ using the methods discussed in the proof of Theorem 7.2.1. Therefore, one can create an SVD respecting the block diagonal structure in the first case of the statement of the lemma (when $n > d )$ . The second case for $n < d$ can be proven using a similar argument. ■ 

Instead of using singular value decomposition on the padded matrix $B ,$ , one can directly decompose the matrix D by pulling out portions of the block structure of padded SVD: 

$$
\begin{array}{l} D = Q \left[ \begin{array}{c} \Sigma_ {1} \\ 0 \end{array} \right] P _ {1} ^ {T}, \quad [ \text {When} d <   n ] \\ D = Q _ {1} [ \Sigma_ {1} 0 ] P ^ {T}, \quad [ \text {When} n <   d ] \end{array}
$$

Both $Q$ and $P$ are square, and only the $n \times d$ diagonal matrix $\Sigma$ is rectangular in both relationships. The square submatrix $\Sigma _ { 1 }$ is of size min $\{ n , d \} \times \operatorname* { m i n } \{ n , d \}$ , and the $n \times d$ matrix $\Sigma$ is obtained by padding it with $| n - d |$ zero rows or columns. Unlike the SVD of $B ,$ the right singular vectors and left singular vectors of $D$ are no longer of the same dimensionality. The left singular vector matrix is always of size $n \times n$ , whereas the right singular vector matrix is always of size $d \times d .$ . This is the standard form of rectangular singular value decomposition. However, other variations of singular value decomposition are even more economical, and will be discussed in the next section. 

## 7.2.3 Several Definitions of Rectangular Singular Value Decomposition

We start with a formal summary of the rectangular SVD derived in the previous section: 

Definition 7.2.1 (Singular Value Decomposition) Consider an $n \times d$ matrix D with real-valued entries. Such a matrix can always be factorized into three matrices as follows: 

$$
D = Q \Sigma P ^ {T}
$$

Here, $Q$ is an $n \times n$ matrix with orthonormal columns containing the left singular vectors, Σ is an $n \times d$ rectangular “diagonal” matrix with diagonal entries containing the nonnegative singular values in non-increasing order, and $P$ is ${ \textit { a d } } \times d$ matrix with orthonormal columns containing the right singular vectors. 

We present a number of important properties of the right singular vectors and left singular vectors below. These properties follow directly from the discussion in the previous section: 

1. The $n$ columns of $Q ,$ , which are referred to as the left singular vectors, correspond to the $n$ eigenvectors of the $n \times n$ matrix $D D ^ { T }$ . Note that these eigenvectors are orthonormal because $D D ^ { T }$ is a symmetric matrix. 

2. The d columns of $P ,$ , which correspond to the right singular vectors, correspond to the d eigenvectors of the $d \times d$ matrix $D ^ { T } D$ . These eigenvectors are orthonormal because $D ^ { T } D$ is a symmetric matrix. 

3. The diagonal entries of the $n \times d$ rectangular diagonal matrix Σ contain the singular values, which are the square-roots of the min $\{ n , d \}$ largest eigenvalues of $D ^ { T } D$ or $D D ^ { T }$ 

4. By convention, the columns of $Q , P ;$ , and Σ are ordered by non-increasing singular value. 

The above form of singular value decomposition is also referred to as full singular value decomposition. Note that either $Q$ or P will be larger than the original matrix D when $n \neq d ,$ , and the $n \times d$ matrix Σ is of the same size as the original matrix. In fact, the larger of $Q$ and $P$ will contain $| n - d |$ unmatched eigenvectors that are not represented in the min $\{ n , d \}$ diagonal entries of Σ. This would seem wasteful. 

A more economical form of the decomposition is economy singular value decomposition, which can be derived from the spectral decomposition of the matrix. Let $\sigma _ { r r }$ be the $( r , r )$ th entry of $\Sigma , \overline { { q } } _ { \tau }$ be the rth column of $Q ,$ , and $\overline { { p } } _ { r }$ be the rth column of $P$ . Then, the matrix product $Q \Sigma P ^ { T }$ can be decomposed into the sum of rank-1 matrices: 

$$
D = Q \Sigma P ^ {T} = \sum_ {r = 1} ^ {\min \{n, d \}} \sigma_ {r r} \overline {{q}} _ {r} \overline {{p}} _ {r} ^ {T}\tag{7.1}
$$

The right-hand side of the above result is obtained by simply applying one of the funda mental ways of characterizing matrix multiplication (cf. Lemma 1.2.1 of Chapter 1) to the product of the matrices $( Q \Sigma )$ and $P ^ { T }$ . The above form of the decomposition is also referred to as the spectral decomposition of the matrix D. Each of the min $\{ n , d \}$ terms (i.e., the $n \times d$ matrix $\sigma _ { r r } \overline { { q } } _ { r } \overline { { p } } _ { r } ^ { T } )$ in the above summation is referred to as a latent component of the original $n \times d$ matrix D. This term is referred to as a latent component, because it represents the independent, hidden (or latent) pieces of the matrix D. Note that each $\overline { { q } } _ { r } ^ { T } \overline { { p } } _ { r }$ is a rank-1 matrix of size $n \times d ,$ , because it is obtained from the product of an n-dimensional column vector with a d-dimensional row vector. The above form of the spectral decomposition provides the insight necessary to propose a form of SVD, referred to as economy singular value decomposition. The idea is that each term of Equation 7.1 can be used to create one of the $p = \operatorname* { m i n } \{ n , d \}$ columns of each of the decomposed matrices: 

Definition 7.2.2 (Economy Singular Value Decomposition) Consider an $n \times d$ matrix D with real-valued entries, where $p = m i n \{ n , d \}$ . Such a matrix can always be factorized into three matrices as follows: 

$$
D = Q \Sigma P ^ {T}
$$

Here, Q is an $n \times p$ matrix with orthonormal columns containing the left-singular vectors, Σ is an $p \times p$ diagonal matrix with diagonal entries containing nonnegative singular values in non-increasing order, and $P$ is a d $\times p$ matrix with orthonormal columns containing the right-singular vectors. 

One of the two matrices $Q$ and P may no longer be square, as we are shedding unmatched singular vectors from the larger of the two matrices in full singular value decomposition. 

One can further reduce the size of the decomposition by observing that some of the min $\{ n , d \}$ values of $\sigma _ { r r }$ might be zero. Such a situation will occur in the case of a matrix $D$ with rank k that is strictly smaller than min $\{ n , d \}$ . In such cases, one can keep only the $k < \mathrm { m i n } \{ n , d \}$ strictly positive singular values without affecting the sum. Assume that the singular values are ordered by non-increasing value, so that $\sigma _ { 1 1 } \geq \sigma _ { 2 2 } \geq . . . \geq \sigma _ { k k }$ . In such a case, we can write the above decomposition as follows: 

$$
D = \sum_ {r = 1} ^ {k} \sigma_ {r r} \overline {{q}} _ {r} \overline {{p}} _ {r} ^ {T}\tag{7.2}
$$

Note that the above summation uses all the k strictly positive singular values. This leads to a slightly different form of singular value decomposition, which is referred to as compact singular value decomposition or reduced singular value decomposition. Compact singular value decomposition is defined as follows: 

Definition 7.2.3 (Compact Singular Value Decomposition) Consider an $n \times d$ matrix D with real-valued entries, which has rank $k \leq m i n \{ n , d \}$ . Such a matrix can always be factorized into three matrices as follows: 

$$
D = Q \Sigma P ^ {T}
$$

Here, $Q$ is an $n \times k$ matrix with orthonormal columns containing the left-singular vectors, Σ is an $k \times k$ diagonal matrix with diagonal entries containing all the positive singular values in non-increasing order, and P is a d $\times k$ matrix with orthonormal columns containing the right-singular vectors. 

The compact version of singular value decomposition can factorize a matrix into much smaller matrices, especially if $k \ll \operatorname* { m i n } \{ n , d \}$ . The number of entries in D is $n \cdot d ,$ whereas the total number of entries in the three factorized matrices is $( n + d + k ) \cdot k$ . The latter value can often be much smaller. If one is willing to take this argument further and lose some representation accuracy, further reduction in the sizes of the factorized matrices can be achieved with truncated singular value decomposition. Truncated singular value decomposition is, in fact, the primary way in which SVD is used in real applications. 

## 7.2.4 Truncated Singular Value Decomposition

In many real applications, it suffices to be able to reconstruct the matrices approximately. Consider the spectral decomposition of the matrix D based on the discussion in the previous section: 

$$
D = Q \Sigma P ^ {T} = \sum_ {r = 1} ^ {\min \{n, d \}} \sigma_ {r r} \overline {{q}} _ {r} \overline {{p}} _ {r} ^ {T}\tag{7.3}
$$

Instead of only dropping the additive components for which $\sigma _ { r r } = 0$ , we might also drop those components for which $\sigma _ { r r }$ is very small. In other words, we keep the top-k values of $\sigma _ { r r }$ in the decomposition (like compact SVD), except that k might be smaller than the number of non-zero singular values. In such a case, we obtain an approximation $D _ { k }$ of the original matrix D, which is also referred to as the rank-k approximation of the $n \times d$ matrix D: 

$$
D \approx D _ {k} = \sum_ {r = 1} ^ {k} \sigma_ {r r} \overline {{q}} _ {r} \overline {{p}} _ {r} ^ {T}\tag{7.4}
$$

Note that Equation 7.4 for truncated singular value decomposition is the same as that for compact singular value decomposition (cf. Equation 7.2); the only difference is that the value of k is no longer chosen to ensure zero information loss. Consequently, we can express truncated singular value decomposition as a matrix factorization as follows: 

$$
D \approx D _ {k} = Q _ {k} \Sigma_ {k} P _ {k} ^ {T}\tag{7.5}
$$

Here, $Q _ { k }$ is an $n \times k$ matrix with columns containing the top-k left singular vectors, $\Sigma _ { k }$ is ${ \mathrm { ~ a ~ } } k \times k$ diagonal matrix containing the top-k singular values, and $P _ { k }$ is a $d \times k$ matrix with columns containing the top-k right singular vectors. It is not difficult to see that the matrix $D _ { k }$ is of rank-k, and therefore it is viewed as a low-rank approximation of D. 

Almost all forms of matrix factorization, including singular value decomposition, are low-rank approximations of the original matrix. Truncated singular value decomposition can retain a surprisingly large level of accuracy using values of k that are much smaller than min $\{ n , d \}$ . This is because only a very small proportion of the singular values are large in real-world matrices. In such cases, $D _ { k }$ becomes an excellent approximation of D by retaining the few singular vectors that are large. 

A useful property of truncated singular value decomposition is that it is also possible to create a lower dimensional representation of the data by changing the basis to $P _ { k }$ , so that each d-dimensional data point is now represented in only k dimensions. In other words, we change the axes so that the basis vectors correspond to the columns of $P _ { k }$ . This trans formation is achieved by post-multiplying the data matrix D with $P _ { k }$ to obtain the $n \times k$ matrix $U _ { k }$ . By post-multiplying Equation 7.5 with $P _ { k }$ and using $P _ { k } ^ { T } P _ { k } = I _ { k }$ , we obtain the following: 

$$
U _ {k} = D P _ {k} = Q _ {k} \Sigma_ {k}\tag{7.6}
$$

Each row of $U _ { k }$ contains a reduced k-dimensional representation of the corresponding row in D. Therefore, we can obtain a reduced representation of the data either by post-multiplying the data matrix with the matrix containing the dominant right singular vectors (i.e., using $D P _ { k } )$ , or we can simply scale the dominant left singular vectors with the singular values (i.e., using $Q _ { k } \Sigma _ { k } )$ . Both these types of methods are used in real applications, depending on whether n or d is larger. 

The reduction in dimensionality can be very significant in some domains such as images and text. Image data are often represented by matrices of numbers corresponding to pixels. For example, an image corresponding to an $8 0 7 \times 6 1 1$ matrix of numbers is illustrated in Figure $7 . 1 ( \mathrm { a } )$ . Only the first 75 singular values are represented in Figure 7.1(b). The remaining $6 1 1 - 7 5 = 5 3 6$ singular values are not shown because they are very small. The rapid decay in singular values is quite evident in the figure. It is this rapid decay that enables effective truncation without loss of accuracy. In the text domain, each document is represented as a row in a matrix with as many dimensions as the number of words. The value of each entry is the frequency of the word in the corresponding document. Note that this matrix is sparse, which is a standard use-case for SVD. The word-frequency matrix D might have $n = 1 0 ^ { 6 }$ and $d = 1 0 ^ { 5 }$ . In such cases, truncated SVD might often yield excellent approximations of the matrix by using $k \approx 4 0 0$ . This represents a drastic level of reduction in the dimensionality of representation. The use of SVD in text is also referred to as latent semantic analysis because of its ability to discover latent (hidden) topics represented by the rank-1 matrices of the spectral decomposition. 

![image](<Images/07_Singular_Value_Decomposition_image_001.jpg>)



(a) An $8 0 7 \times 6 1 1$ image


![image](<Images/07_Singular_Value_Decomposition_image_002.jpg>)



(b) First 75 singular values



Figure 7.1: The rapid decay in singular values for an $8 0 7 \times 6 1 1$ image


## 7.2.4.1 Relating Truncation Loss to Singular Values

A natural question arises as to the amount of accuracy loss caused by truncation. Here, it is important to understand that the spectral decomposition of SVD expresses a matrix as a sum of matrices that are Frobenius orthogonal in terms of their Frobenius inner product: 

Definition 7.2.4 (Frobenius Inner Product and Orthogonality) The Frobenius inner product $\langle A , B \rangle _ { F }$ between $n \times d$ matrices $A = \left[ a _ { i j } \right]$ and $B = \left[ b _ { i j } \right]$ is equal to $\textstyle \sum _ { i } \sum _ { j } a _ { i j } b _ { i j }$ which is equal to the trace of $A ^ { T } B$ 

$$
\langle A, B \rangle_ {F} = \langle B, A \rangle_ {F} = t r (A ^ {T} B) = t r (A B ^ {T})
$$

Two matrices are Frobenius orthogonal if their Frobenius inner product is 0. 

The squared Frobenius norm is a special case of the Frobenius inner product. The Frobenius orthogonality of matrices can be viewed in a similar way to the pairwise orthogonality of vectors by simply converting each matrix into a vector representation. One simply flattens all the entries of each matrix into a vector and computes the dot product between them. Many of the norm properties of sums of pairwise orthogonal vectors are also inherited by matrices. This is not particularly surprising because one can view the set of all $n \times d$ matrices as a vector space in $\mathcal { R } ^ { n \times d }$ and an inner product that behaves similarly to the dot product. For example, the Frobenius inner product also satisfies the Pythagorean theorem: 

Lemma 7.2.5 Let A and B be two $n \times d$ matrices that are Frobenius orthogonal. Then, the squared Frobenius norm of $( A + B )$ can be expressed in terms of the Frobenius norms of A and B as follows: 

$$
\| A + B \| _ {F} ^ {2} = \| A \| _ {F} ^ {2} + \| B \| _ {F} ^ {2}
$$

Proof: The above result is relatively easy to show by expressing the Frobenius norm in terms of the trace of the matrix: 

$$
\begin{array}{c} \| A + B \| _ {F} ^ {2} = \operatorname{tr} [ (A + B) ^ {T} (A + B) ] = \operatorname{tr} (A ^ {T} A) + \underbrace {\operatorname{tr} (A ^ {T} B) + \operatorname{tr} (B ^ {T} A)} _ {= 0} + \operatorname{tr} (B ^ {T} B) \\ = \| A \| _ {F} ^ {2} + \| B \| _ {F} ^ {2} \end{array}
$$

Note that we used Frobenius orthogonality to set some of the terms to 0. ■ One can generalize the above result to the sum of any number of matrices by recursively applying the above lemma. 

Corollary 7.2.2 Let $A _ { 1 } \ldots A _ { k }$ be any set of k matrices of the same size that are all Frobenius orthogonal to one another. Then, the squared Frobenius norm of the sum of these matrices can be expressed in terms of the Frobenius norms of the individual matrices as follows: 

$$
\| \sum_ {i = 1} ^ {k} A _ {i} \| _ {F} ^ {2} = \sum_ {i = 1} ^ {k} \| A _ {i} \| _ {F} ^ {2}
$$

One can generalize the above result to the case where a weighted sum of the matrices is used. We leave the proof of the generalized result as an exercise: 

Corollary 7.2.3 Let $A _ { 1 } \ldots A _ { k }$ be any set of k matrices of the same size that are all Frobenius orthogonal to one another. Then, the Frobenius norm of a linear combination of these matrices can be expressed in terms of the Frobenius norms of the individual matrices as follows: 

$$
\| \sum_ {i = 1} ^ {k} \sigma_ {i} A _ {i} \| _ {F} ^ {2} = \sum_ {i = 1} ^ {k} \sigma_ {i} ^ {2} \| A _ {i} \| _ {F} ^ {2}
$$

Here, each $\sigma _ { i }$ is a scalar weight. 

Next, we will show that the rank-1 matrices of spectral decomposition are all Frobenius orthogonal to one another: 

Lemma 7.2.6 Let $\overline { { q } } _ { i }$ and $\overline { { q } } _ { j }$ be orthogonal to one another, and also let ${ \overline { { p } } } _ { i }$ and ${ \overline { { p } } } _ { j }$ be orthogonal. Then, the rank-1 matrices $D _ { i } = \overline { { q } } _ { i } \overline { { p } } _ { i } ^ { T }$ and $D _ { j } = \overline { { q } } _ { j } \overline { { p } } _ { j } ^ { T }$ are Frobenius orthogonal. 

Proof: One can show that the matrices $D _ { i }$ and $D _ { j }$ are Frobenius orthogonal by showing that the trace of $D _ { i } ^ { T } D _ { j }$ is 0. Therefore, we have: 

$$
\operatorname{tr} (D _ {i} ^ {T} D _ {j}) = \operatorname{tr} ([ \overline {{p}} _ {i} \overline {{q}} _ {i} ^ {T} ] [ \overline {{q}} _ {j} \overline {{p}} _ {j} ^ {T} ]) = \operatorname{tr} (\overline {{p}} _ {i} \underbrace {[ \overline {{q}} _ {i} ^ {T} \overline {{q}} _ {j} ]} _ {0} \overline {{p}} _ {j} ^ {T}) = 0
$$

Note that we used the orthogonality of $\overline { { q } } _ { i }$ and $\overline { { q } } _ { j }$ in the above proof, but we did not use theorthogonality of ${ \overline { { p } } } _ { i }$ and ${ \overline { { p } } } _ { j }$ . This lemma can be shown to be true under the weaker conditionsthat either of the vector pairs $( \overline { { q } } _ { i } , \overline { { q } } _ { j } )$ and $( \overline { { p } } _ { i } , \overline { { p } } _ { j } )$ are orthogonal. 厂The matrix $\overline { { q } } _ { i } \overline { { p } } _ { i } ^ { T }$ in the spectral decomposition is the outer-product of two vectors with unitnorm. The Frobenius norm of such a matrix can be shown to be 1.

Lemma 7.2.7 Let ${ \overline { { p } } } _ { i }$ and $\overline { { q } } _ { i }$ be a pair of vectors with unit norm. The Frobenius norm of the rank-1 matrix of the form $D _ { i } = \overline { { q } } _ { i } \overline { { p } } _ { i } ^ { T }$ is 1. 

Proof: The Frobenius norm of $D _ { i }$ can be expressed in terms of the trace as follows: 

$$
\| D _ {i} \| _ {F} ^ {2} = \operatorname{tr} (D _ {i} ^ {T} D _ {i}) = \operatorname{tr} (\overline {{p}} _ {i} \underbrace {[ \overline {{q}} _ {i} ^ {T} \overline {{q}} _ {i} ]} _ {= 1} \overline {{p}} _ {i} ^ {T}) = \operatorname{tr} (\overline {{p}} _ {i} \overline {{p}} _ {i} ^ {T}) = \operatorname{tr} (\underbrace {\overline {{p}} _ {i} ^ {T} \overline {{p}} _ {i}} _ {= 1}) = 1
$$

Let us now take a moment to examine the spectral decomposition of the matrix created by truncated SVD. We replicate the spectral decomposition of rank-k truncated SVD from Equation 7.4 here: 

$$
D \approx D _ {k} = Q _ {k} \Sigma_ {k} P _ {k} ^ {T} = \sum_ {r = 1} ^ {k} \sigma_ {r r} \overline {{q}} _ {r} \overline {{p}} _ {r} ^ {T}\tag{7.7}
$$

Here, it is evident that the spectral decomposition on the right-hand side contains a bunch of Frobenius orthogonal matrices. Each of these matrices has a Frobenius norm of 1, but they are weighted by $\sigma _ { r r }$ . Therefore, taking the Frobenius norm of all expressions in Equation 7.7, we obtain the following (based on Corollary 7.2.3): 

$$
\| D \| _ {F} ^ {2} \approx \| D _ {k} \| _ {F} ^ {2} = \| \sum_ {r = 1} ^ {k} \sigma_ {r r} \overline {{q}} _ {r} \overline {{p}} _ {r} ^ {T} \| _ {F} ^ {2} = \sum_ {r = 1} ^ {k} \sigma_ {r r} ^ {2} \underbrace {\| \overline {{q}} _ {r} \overline {{p}} _ {r} ^ {T} \| _ {F} ^ {2}} _ {= 1} = \sum_ {r = 1} ^ {k} \sigma_ {r r} ^ {2}
$$

Therefore, we obtain the result that the squared Frobenius norm of the rank-k approximation is equal to the sum of the squares of the top-k singular values. The squared Frobenius norm of a matrix is referred to as its energy (cf. Section 1.2.6 of Chapter 1). Therefore, the lost energy is equal to the sum of the squares of the smallest singular values (excluding the top-k singular values), which is also a measure of the squared error of the approximation. In fact, Section 7.3 shows that SVD provides a rank-k approximation of the matrix D, which has the smallest squared error among the universe of all possible rank-k approximations. 

## 7.2.4.2 Geometry of Rank-k Truncation

The rank-k truncation reduces the dimensionality of the data, because the rank-k approximation $D _ { k } = Q _ { k } \Sigma _ { k } P _ { k } ^ { T }$ no longer requires d dimensions for representation. Rather, it can be expressed in $k \ll d$ dimensions, which translates to significant space savings. One can simply rotate the truncated representation to a k-dimensional basis without further loss of accuracy. As discussed in Equation 7.6, one can obtain an $n \times k$ reduced representation matrix $U _ { k }$ as follows: 

$$
U _ {k} = D P _ {k} = Q _ {k} \Sigma_ {k}\tag{7.8}
$$

Each row of $U _ { k } = D P _ { k }$ contains a k-dimensional representation of the corresponding row in D. The k columns of $P _ { k }$ contain the top eigenvectors of the scatter matrix $D ^ { T } D$ , and they preserve the directions with the largest possible scatter among all possible directions. We will explicitly show this result in Section 7.3, which provides an optimization-centric view of SVD. This situation is illustrated for a 3-dimensional data set in Figure 7.2, in which most of the energy is retained in one or two eigenvectors with the largest scatter. Therefore, by projecting the data onto this new axis system, most of the scatter of the data about the origin (i.e., energy) can be preserved in one or two dimensions. 

In order to understand the geometric effect of the dimensionality reduction achieved by singular value decomposition, consider a large data set in which all points are normally distributed in a perfect ellipsoid centered at the origin, and the standard deviation along the ith axis of the ellipsoid is $\beta _ { i }$ . Singular value decomposition will find all the axes of this ellipsoid as the right singular vectors, and the ith singular value will be $\sigma _ { i } = \beta _ { i }$ . An example of an origin-centered ellipsoid and its three axes directions is shown in Figure 7.3. These three axes directions are the right singular vectors. The left singular vectors may be obtained by applying the same approach to the transpose of the data set. 

## 7.2.4.3 Example of Truncated SVD

We provide an example of truncated SVD with the use of a toy text collection, which has 6 documents and 6 words. The $( i , j ) \mathrm { t h }$ in the data matrix D is the frequency of word $j$ in document i. The $6 \times 6$ data matrix D is defined over the following vocabulary: 

lion, tiger, cheetah, jaguar, porsche, ferrari 

![image](<Images/07_Singular_Value_Decomposition_image_003.jpg>)



Figure 7.2: Most of energy of the data is retained in the projection along the one or two largest eigenvectors of the $3 \times 3$ matrix $D ^ { T } D$


![image](<Images/07_Singular_Value_Decomposition_image_004.jpg>)



Figure 7.3: SVD models the data to be distributed in an ellipsoid centered at the origin



The frequencies of the words in each document of the data matrix D are illustrated below:


<table><tr><td><eq>D = \left( \begin{array}{ccccccccc}  &amp; \text{lion} &amp; \text{tiger} &amp; \text{cheetah} &amp; \text{jaguar} &amp; \text{porsche} &amp; \text{ferrari} \\ \text{Document-1} &amp; 2 &amp; 2 &amp; 1 &amp; 2 &amp; 0 &amp; 0 \\ \text{Document-2} &amp; 2 &amp; 3 &amp; 3 &amp; 3 &amp; 0 &amp; 0 \\ \text{Document-3} &amp; 1 &amp; 1 &amp; 1 &amp; 1 &amp; 0 &amp; 0 \\ \text{Document-4} &amp; 2 &amp; 2 &amp; 2 &amp; 3 &amp; 1 &amp; 1 \\ \text{Document-5} &amp; 0 &amp; 0 &amp; 0 &amp; 1 &amp; 1 &amp; 1 \\ \text{Document-6} &amp; 0 &amp; 0 &amp; 0 &amp; 2 &amp; 1 &amp; 2 \end{array} \right)</eq></td></tr></table>

Note that this matrix represents topics related to both cars and cats. The first three documents are primarily related to cats, the fourth is related to both, and the last two are primarily related to cars. The word “jaguar” is ambiguous because it could correspond to either a car or a cat. We perform an SVD of rank-2 to capture the two latent components in the collection, which is as follows: 

$$
\begin{array}{l} D \approx Q _ {2} \Sigma_ {2} P _ {2} ^ {T} \\ \approx \left( \begin{array}{c c} - 0. 4 1 & 0. 1 7 \\ - 0. 6 5 & 0. 3 1 \\ - 0. 2 3 & 0. 1 3 \\ - 0. 5 6 & - 0. 2 0 \\ - 0. 1 0 & - 0. 4 6 \\ - 0. 1 9 & - 0. 7 8 \end{array} \right) \left( \begin{array}{c c} 8. 4 & 0 \\ 0 & 3. 3 \end{array} \right) \left( \begin{array}{c c c c c c} - 0. 4 1 & - 0. 4 9 & - 0. 4 4 & - 0. 6 1 & - 0. 1 0 & - 0. 1 2 \\ 0. 2 1 & 0. 3 1 & 0. 2 6 & - 0. 3 7 & - 0. 4 4 & - 0. 6 8 \end{array} \right) \\ = \left( \begin{array}{c c c c c c} 1. 5 5 & 1. 8 7 & 1. 6 7 & 1. 9 1 & 0. 1 0 & 0. 0 4 \\ 2. 4 6 & 2. 9 8 & 2. 6 6 & 2. 9 5 & 0. 1 0 & - 0. 0 3 \\ 0. 8 9 & 1. 0 8 & 0. 9 6 & 1. 0 4 & 0. 0 1 & - 0. 0 4 \\ 1. 8 1 & 2. 1 1 & 1. 9 1 & 3. 1 4 & 0. 7 7 & 1. 0 3 \\ 0. 0 2 & - 0. 0 5 & - 0. 0 2 & 1. 0 6 & 0. 7 4 & 1. 1 1 \\ 0. 1 0 & - 0. 0 2 & 0. 0 4 & 1. 8 9 & 1. 2 8 & 1. 9 2 \end{array} \right) \end{array}
$$

The reconstructed matrix is a very good approximation of the original data matrix D. One can also obtain a 2-dimensional embedding of each row of D as $D P _ { 2 } = Q _ { 2 } \Sigma _ { 2 }$ : 

$$
D P _ {2} = Q _ {2} \Sigma_ {2} \approx \left( \begin{array}{c c} - 3. 4 6 & 0. 5 7 \\ - 5. 4 4 & 1. 0 3 \\ - 1. 9 5 & 0. 4 1 \\ - 4. 7 4 & - 0. 6 6 \\ - 0. 8 3 & - 1. 4 9 \\ - 1. 5 7 & - 2. 5 4 \end{array} \right)
$$

It is clear that the reduced representations of the first three rows are quite similar, which is not surprising. After all the corresponding documents belong to similar topics. At the same time, the reduced representations of the last two rows are also similar. The fourth row seems to be somewhat different because it contains a combination of two topics. Therefore, the latent components seem to capture the hidden “concepts” in the data matrix. In this case, these hidden concepts correspond to cats and cars. 

## 7.2.5 Two Interpretations of SVD

In this section, we will discuss two interpretations of SVD, which correspond to the datacentric and the transformation-centric interpretations of SVD. 

In the data-centric interpretation, SVD is viewed as a way of providing an orthogonal basis for both the row space and the column space of the data matrix D. Note that QR decomposition (cf. Section 2.7.2 of Chapter 2) can provide an orthonormal basis for either the row space or the column space (depending on whether it is performed on the matrix or its transpose), but not both simultaneously. Consider the compact SVD of the $n \times d$ data matrix D of rank k: 

$$
D = Q \Sigma P ^ {T}
$$

The $d \times k$ matrix P contains the d-dimensional basis vectors of the (transposed) rows of D in its columns; there are k of them because the original data matrix has rank k. The $n \times k$ matrix Q contains the n-dimensional basis vectors of the columns of D in its columns. In other words, SVD simultaneously finds the basis sets of both the (transposed) rows and the columns of the data matrix. The square of the ith diagonal entry of the matrix Σ provides a quantification of the energy of the 1-dimensional data set $D { \overline { { p } } } _ { i }$ obtained by projecting it along the ith right singular vector. Directions with larger scatter obviously retain larger information about the data set. For example, when the singular value $\sigma _ { i i }$ is small, each value in $D { \overline { { p } } } _ { i }$ tends to be close to zero. When truncated SVD is used instead of compact SVD, we are restricting ourselves to finding approximate basis sets rather than exact basis sets. In other words, we can use these basis sets to represent all the rows in the data matrix approximately, but not exactly. This ability of truncated SVD to simultaneously find approximate bases for the row space and column space is shown in Figure 7.4. Note that each of the k pieces $\sigma _ { i i } \overline { { q } } _ { i } \overline { { p } } _ { i } ^ { T }$ represents a portion of D corresponding to a latent (or hidden) component of the matrix. Truncated SVD, therefore, represents a matrix in terms of its dominant hidden components. 

![image](<Images/07_Singular_Value_Decomposition_image_005.jpg>)



Figure 7.4: Interpretation of SVD in terms of the basis vectors of rows and columns of D


SVD can also be interpreted from a transformation-centric point of view, especially when it is performed on square matrices. Consider a square $d \times d$ matrix A, which is used to transform the d-dimensional rows of the $n \times d$ data matrix D into the d-dimensional rows of the $n \times d$ matrix DA. One can replace A with its SVD $Q \Sigma P ^ { T }$ , which corresponds to a sequence of rotation/reflection, anisotropic scaling, and another rotation/reflection. This seems very similar to what happens in diagonalization of positive semidefinite matrices. The only difference is that the two rotations/reflections cancel each other out in positive semidefinite matrices, whereas they do not cancel each other out in SVD. SVD implies that any linear transformation can be expressed as a combination of rotation/reflection and scaling. Another way of viewing this point is that if we have an $n \times d$ data matrix D, whose scatter plot is an origin-centered ellipsoid in d-dimensions, and we multiply it with an arbitrary $d \times d$ matrix A to create the matrix DA, the resulting scatter plot will still be a re-scaled and re-oriented ellipsoid! Both the left and right singular vectors will affect the final orientation, and the singular values will affect the scaling. An example of a transformation of a 2-dimensional scatter plot is illustrated in Figure 7.5. 

Both the aforementioned interpretations are rooted in linear algebra. SVD can also be interpreted from an optimization-centric point of view, wherein it tries to find an approximate factorization that preserves the maximum energy from the data set. In Section 7.3, we will explore this optimization-centric interpretation, which is a gateway to more general forms of matrix factorization (cf. Chapter 8). 

![image](<Images/07_Singular_Value_Decomposition_image_006.jpg>)



Figure 7.5: The transformation-centric interpretation of SVD as a pair of rotations/reflections and a distortion


## 7.2.6 Is Singular Value Decomposition Unique?

Given a data matrix, the SVD is a relatively restricted form of decomposition compared to other types of decompositions like the QR method. For example, the QR decomposition varies drastically according to the order in which one processes the different vectors that are orthogonalized. However, the SVD is much more specialized, and can sometimes be close to unique (irrespective of the numerical algorithm used). In Section 3.3.3, you learned that the diagonalization of a square matrix is unique (after imposing sign and normalization conventions) if there are no repeated eigenvalues. Singular value decomposition can be viewed as a generalization of the diagonalization of positive semidefinite matrices (with orthonormal eigenvectors) to matrices that are not symmetric or even square (with orthonormal singular vectors). Interestingly, the condition for uniqueness of singular value decomposition is also similar to that of diagonalization — the non-zero singular values need to be distinct. 

We first consider the singular value decomposition of a square matrix B. The singular value decomposition is almost unique, if and only if all the eigenvalues of $B ^ { T } B$ and $\overset { \sim } { B } B ^ { T }$ are distinct. In such cases, singular value decomposition is unique up to multiplication of any column of Q with 1, and multiplication of any column of P by 1. Note that if we multiply the ith column of Q by 1 and we also multiply the ith column of P by 1, the product $Q \Sigma P ^ { T }$ remains unchanged. Throughout this chapter, the definition of the word “uniqueness” is slightly relaxed to allow for this type of reflection. 

Lemma 7.2.8 (Condition for Uniqueness) Consider a square matrix B of size $m \times m$ which is such that all the eigenvalues of $B ^ { T } B ^ { \dot { } }$ (and $B B ^ { T } )$ are distinct. Then, the singular value decomposition of B is unique up to the multiplication of the singular vectors by 1. 

Note that if the singular values are not distinct, then one can choose any orthonormal basis of the eigenspace of the tied eigenvalues of $B ^ { T } B$ as the corresponding right singular vectors in $P ^ { T }$ . The corresponding left singular vectors are obtained by pre-multiplying each of the these right-singular vectors with B and scaling the result to unit norm (cf. Lemma 7.2.1). In fact, there are an infinite number of possible (orthonormal) basis systems to choose from in the subspace corresponding to the tied eigenvectors (by simply selecting any basis of the tied eigenvectors). Therefore, ties in the singular values always ensure that singular value decomposition is not unique in a very fundamental way. 

The above discussion pertains only to the singular value decomposition of square matri ces. What about the singular value decomposition of rectangular matrices? One can generalize the uniqueness result of Lemma 7.2.8 to rectangular singular value decomposition, as long as we use the compact variant of singular value decomposition in which only non-zero singular values are included. 

Lemma 7.2.9 (Uniqueness of Compact SVD) Consider an $n \times d$ matrix D, which is such that all the non-zero singular values are distinct. Then, the compact singular value decomposition of D is unique up to the multiplication of the singular vectors by 1. 

In addition, truncated SVD will also be unique, as long as the retained singular values in the decomposition are distinct. Truncated singular value decomposition is very likely to be unique in real applications, because most of the (exact or approximate) ties in singular values often occur at the lower-order singular values at or near zero. The truncation process often removes most of these singular values. 

## 7.2.7 Two-Way Versus Three-Way Decompositions

Singular value decomposition is inherently defined as a three-way factorization $Q \Sigma P ^ { T }$ , in which the leftmost factor $Q$ provides a basis for the column space, the rightmost factor $P ^ { T }$ provides a basis for the row space, and the diagonal matrix Σ provides a quantification of the relative importance of the different basis vectors. Although this division of labor is elegant, two-way decompositions are often more popular in the literature on matrix factorization. In the two-way decomposition, an $n \times d$ matrix D is factorized into an $n \times k$ matrix U and a $d \times k$ matrix V, where k is the rank of the decomposition: 

$$
D \approx U V ^ {T}\tag{7.9}
$$

If the original matrix D has rank larger than k, the above decomposition is only approximate (like truncated SVD). One can convert any three-way factorization like SVD into a two-way factorization as follows: 

$$
D \approx \underbrace {(Q \Sigma)} _ {U} \underbrace {P ^ {T}} _ {V ^ {T}}
$$

In the case of ${ \mathrm { S V D } } ,$ it is natural to absorb the diagonal matrix within $Q ,$ , because $U = Q \Sigma$ provides the coordinates of the data point in the k-dimensional basis space corresponding to the columns of $V = P$ . When converting a three-way decomposition into a two-way decomposition, the general preference is to keep the normalization of the right factor and absorb the diagonal matrix in the left factor. However, the reality is that the 2-way decomposition has a much lower level of uniqueness as compared to 3-way decomposition. For example, one could absorb Σ in $V ^ { T }$ instead of $U .$ . Furthermore, one could scale U and V in all sorts of ways without affecting the product $U V ^ { T }$ . For example, if we multiply each entry of U by 2, we can divide each entry of V by 2 to get the same product $U V ^ { T }$ . Furthermore, we can apply this trick to just a particular (say, rth) column of each of U and V to get the same result. In this sense, two-way factorizations are often ambiguously defined, unless one takes care to have clear normalization rules for one of the factors. Nevertheless, two-way factorizations are extremely useful in other forms of dimensionality reduction (like nonnegative matrix factorization) because of the simplicity in working with only two matrices in optimization formulations. Many forms of factorization use optimization models over two factors, which are relatively simple from the perspective of optimization algorithms like gradient descent. The good news that two-way factorizations can always be converted to a standardized three-way factorization like SVD by using the procedure discussed below. 

In singular value decomposition, the $( r , r )$ th diagonal entry is chosen in such a way that the rth columns of the left-most factor matrix Q and the right-most factor matrix $P$ become normalized to unit norm. In other words, the diagonal matrix contains the scaling factors which create the ambiguity in 2-way factorization in terms of their distribution between U and $V .$ . Consider a two-way matrix factorization $D \approx U V ^ { T }$ into $n \times k$ and $d \times k$ matrices $U$ and $V ,$ respectively. We can convert it into a near-unique (ignoring column reflection) three-way matrix factorization of the following form: 

$$
D \approx Q \Sigma P ^ {T}\tag{7.10}
$$

Here, $Q$ is a normalized $n \times k$ matrix (derived from $U )$ $P$ is a normalized $d \times k$ matrix (derived from $V )$ , and Σ is a $k \times k$ diagonal matrix in which the diagonal entries contain the nonnegative normalization factors for the k concepts. Each of the columns of $Q$ and $P$ satisfy the constraint that its $L _ { \mathrm { { 2 } } } \mathrm { { - n o r m } }$ (or $L _ { \mathrm { 1 } } \mathrm { - n o r m } )$ is one unit. It is common to use $L _ { 2 ^ { - } }$ normalization in methods like singular value decomposition and $\scriptstyle L _ { 1 } - \mathrm { n o r m a l i z a t i o n }$ in some variations of nonnegative matrix factorization (discussed in Chapter 8). For the purpose of discussion, let us assume that we use $\scriptstyle L _ { 2 } - \mathrm { n o r m a l i z a t i o n }$ . Then, the conversion from two-way factorization to three-way factorization can be achieved as follows: 

1. For each $r \in \{ 1 \ldots k \}$ , divide the rth column $\overline { { U } } _ { r }$ of $U$ with its $L _ { 2 } \mathrm { - n o r m ~ } \| \overline { { U } } _ { r } \|$ . The resulting matrix is denoted by $Q$ 

2. For each $r \in \{ 1 \ldots k \}$ , divide the rth column $\overline { { V } } _ { r }$ of V with its L -norm $\| \overline { { V } } _ { r } \|$ . The resulting matrix is denoted by $P .$ 

3. Create a k k diagonal matrix $\Sigma ,$ , in which the $( r , r )$ th diagonal entry is the nonnegative value $\| \overline { { U } } _ { r } \| \cdot \| \overline { { V } } _ { r } \|$ 

It is easy to show that the matrices $Q , \Sigma ,$ and P satisfy the following relationship: 

$$
Q \Sigma P ^ {T} = U V ^ {T}\tag{7.11}
$$

It is noteworthy that all diagonal entries of $\Sigma$ are always nonnegative because of how the normalization is done. The optimization-centric view of SVD, which is discussed in the next section, uses two-way factorization in order to create compact optimization formulations. In general, two-way decompositions are more common in optimization-centric matrix fac torization, because it is simpler to work with fewer matrices (and optimization variables). 

## 7.3 SVD: An Optimization Perspective

The previous section provides a linear algebra perspective of singular value decomposition. While it provides insights about the existence/uniqueness of full SVD or even compact SVD, it makes no claim on the comparative accuracy of truncated SVD to the best possible lowrank approximation of the matrix. Another important point is that linear algebra can be used to derive full SVD, but it does not work for other forms of matrix factorization. In many cases, one may want to have constraints on the factors that move them away from properties of vector spaces. For example, if we want to put arbitrary constraints on the factors (such as nonnegative factors), it suddenly becomes very difficult to use techniques from linear algebra. The problem is that the space of nonnegative vectors is not even a vector space, and therefore the principles of linear algebra no longer apply. As we will see in the next chapter, many forms of matrix factorization use different choices of objective functions and constraints in order to control the properties of the factorization. Controlling the properties of the factorization is the key to being able to use them in different types of machine learning models, and these properties will be explored in Chapter 8. The optimization perspective is useful in all these cases. The most important result that arises from optimization-centric analysis is the following: 

Truncated SVD provides the best possible rank-k approximation of a matrix in terms of squared error. 

An important point is that SVD also happens to provide a factorization $D \approx U V ^ { T } = Q \Sigma P ^ { T }$ which is such that the columns of each of $U$ and V are orthogonal. However, even if we allow factorizations $D \approx U V ^ { T }$ in which the columns of each of $U$ and V are not necessarily orthogonal, one would not gain anything from this relaxation in terms of accuracy. In other words, even for the optimization problem of minimizing the squared error of unconstrained low-rank factorization of D into $U$ and $V ^ { T }$ , one of the alternative optima is a pair of matrices $U$ and $V .$ , such that the columns of each of the matrices are orthogonal. This section will show this beautiful property of SVD by approaching it from an optimization perspective. 

In the following exposition, we will consistently work with the two-way factorization $D \approx U V ^ { T }$ rather than the three-way factorization $D \approx Q \Sigma P ^ { T }$ . Here, D is an $n \times d$ matrix, U is an $n \times k$ matrix, and V is a $d \times k$ matrix. The hyperparameter k is the rank of the factorization. In such a case, the columns of each of $U$ and V are mutually orthogonal, although there is some ambiguity in how these columns are scaled. Therefore, we will make the assumption that the columns of V are scaled to unit norm. 

## 7.3.1 A Maximization Formulation with Basis Orthogonality

First, we present an optimization model that assumes orthonormality of the columns of the matrix V . In such a case, we have $V ^ { T } V = I$ , and therefore the reduced representation of D can be obtained as $U = D V$ . Therefore, one way of formulating singular value decomposition is to maximize the energy of the matrix $U = D V$ as follows: 

$$
\begin{array}{c} \text {Maximize} _ {V} \| D V \| _ {F} ^ {2} (O P) \\ \text {subject to:} \\ V ^ {T} V = I _ {k} \end{array}
$$

We refer to this optimization problem as (OP). Here, V is a $d \times k$ matrix, and the $n \times k$ matrix $U = D V$ is not included in the optimization formulation. The objective function of this problem (in minimization form) is not convex even for simple versions of this problem such as $k = 1$ . Nevertheless, it can still be solved optimally because of the specialized structure of the problem. It is important to note that one can decompose $\| D V \| _ { F } ^ { 2 }$ in terms of the sums of L -norms of the k columns of DV. Therefore, if $\overline { { V } } _ { r }$ is the rth column of $V .$ one can simplify the objective function as follows: 

$$
\| D V \| _ {F} ^ {2} = \sum_ {r = 1} ^ {k} \| D \overline {{V}} _ {r} \| ^ {2} = \sum_ {r = 1} ^ {k} \overline {{V}} _ {r} ^ {T} [ D ^ {T} D ] \overline {{V}} _ {r}
$$

Note that this optimization problem is the same as the norm-constrained optimization problem introduced in Section 6.6 of Chapter 6. The solution to this problem corresponds to the top-k eigenvectors of $D ^ { T } D$ . Recall from the previous section that the eigenvalues of $D ^ { T } D$ are $\sigma _ { 1 1 } ^ { 2 } \dots \sigma _ { r r } ^ { 2 } .$ , which are the same as the squares of the singular values of $D _ { \ast }$ 

Furthermore, the energy retained in DV is equal to $\scriptstyle \sum _ { r = 1 } ^ { k } \sigma _ { r r } ^ { 2 }$ based on the discussion in Section 6.6 of Chapter 6. This is consistent with the energy retained by truncated singular value decomposition (cf. Section 7.2.4). We have, therefore, just shown that the energy retained by truncated SVD (cf. Section 7.2.4) is as large as possible among all possible orthonormal basis systems V. We summarize this result as follows: 

Lemma 7.3.1 The optimal solution V for the optimization problem $( O P )$ is obtained by setting the columns of V to the largest eigenvectors in $D ^ { T } D$ 

We can also show that the transformed representation $U \ = \ D V$ contains the (scaled) eigenvectors of $D D ^ { T }$ 

Lemma 7.3.2 Let $U \ = \ D V$ be the transformed representation of the data, when V is obtained using $( O P )$ . Then U contains the scaled eigenvectors of $D \bar { D } ^ { T }$ 

Proof: Let the n-dimensional column vector $\overline { { U } } _ { r }$ contain the rth column of $D V$ . This is equal to $D \overline { { V } } _ { r }$ , where $\overline { { V } } _ { r }$ contains the rth column of $V .$ . In other words, we have: 

$$
\overline {{U}} _ {r} = D \overline {{V}} _ {r}
$$

Multiplying both sides with $D D ^ { T }$ , we obtain the following: 

$$
D D ^ {T} \overline {{U}} _ {r} = (D D ^ {T}) D \overline {{V}} _ {r} = D \underbrace {[ (D ^ {T} D) \overline {{V}} _ {r} ]} _ {\propto \overline {{V}} _ {r}} \propto D \overline {{V}} _ {r} = \overline {{U}} _ {r}
$$

In other words, $\overline { { U } } _ { 1 } \dots \overline { { U } } _ { k }$ are the eigenvectors of $D D ^ { T }$ . The only difference is that the columns of $V$ are scaled to unit norm, whereas those of $U$ are not. 

Since $D D ^ { T }$ is a symmetric matrix, its eigenvectors $\overline { { U } } _ { 1 } \ldots \overline { { U } } _ { k }$ will be mutually orthogonal as well. Note that this optimization model only uses the assumption that the columns of V are orthogonal, and we were able to automatically derive the fact that the columns of $U = D V$ are mutually orthogonal. 

## 7.3.2 A Minimization Formulation with Residuals

The aforementioned optimization model tries to maximize the retained energy $\| U \| _ { F } ^ { 2 } =$ $\| D V \| _ { F } ^ { 2 }$ in the projected matrix DV. An alternative approach is to minimize the lost energy, which is $\| D - \bar { U } \bar { V } ^ { T } \| _ { F } ^ { 2 }$ . The matrix $R = ( D - U V ^ { T } )$ is commonly referred to as the residual matrix from an approximate factorization $D \approx U V ^ { T }$ 

Consider the following unconstrained optimization problem, which is obtained by dropping the orthonormality constraints on the columns of $V { : }$ 

$$
\text { Minimize } _ {U, V} J = \| D - U V ^ {T} \| _ {F} ^ {2}
$$

The optimization problem is also referred to as unconstrained matrix factorization. Here, U is an $n \times k$ matrix, and V is a $d \times k$ matrix. This objective function is not convex, but can nevertheless be optimized easily. This optimization problem is an example of the fact that not all non-convex problems are impossible to solve. 

First, note that even though this problem is unconstrained, we can find at least one optimal V with orthonormal columns. This is because we can replace any optimal solution pair $( U , V ) = ( U ^ { 0 } , V ^ { 0 } )$ with the pair $( U ^ { 0 } R ^ { T } , Q )$ , where $V ^ { 0 } = Q R$ is the QR-decomposition of $V ^ { 0 }$ , and Q, R are $d \times k$ and $k \times k$ matrices, respectively. Both solutions have the same ob jective function value, since the product of both pairs of matrices is $U ^ { 0 } R ^ { T } { \cal Q } ^ { T }$ . Furthermore, as shown in Figure 8.1 of Chapter 8, a necessary condition for optimality of this matrix factorization problem is as follows: 

$$
D V - U V ^ {T} V = 0
$$

The solution with orthonormal columns of V (obtained via QR decomposition of any optimal $V ^ { 0 } )$ , satisfies $V ^ { T } V = I ,$ , and, therefore, the condition simplifies to $U = D V$ . Substituting for U in the optimization formulation, the unconstrained matrix factorization problem has the same objective function value as that of minimizing $\| D - U V ^ { T } \| ^ { 2 } = \| D - D V V ^ { T } \| _ { F } ^ { 2 }$ subject to $\bar { V } ^ { T } V = I _ { k }$ . The sum of the squared Frobenius norms of DV and $D - D V V ^ { \tilde { T } }$ can be shown<sup>1</sup> to be the constant $\| D \| _ { F } ^ { 2 }$ , and therefore this minimization problem reduces to the maximization of the Frobenius norm of DV . This is exactly the problem (OP) of the previous section. Therefore, the unconstrained minimization formulation with residuals also yields the top eigenvectors of $D D ^ { T }$ and $D ^ { T } D$ for U and V , respectively, as one of the alternate optima. In other words, we have the following important result: 

Theorem 7.3.1 Truncated singular value decomposition provides one of the alternate optima to unconstrained matrix factorization. 

## 7.3.3 Generalization to Matrix Factorization Methods

The formulation contained in the previous section is the most basic form of optimizationcentric matrix factorization. By changing the objective function and the constraints, other forms of matrix factorization can be supported. All matrix factorization methods have the following general form: 

Maximize similarity between entries of D and $U V ^ { T }$ 

subject to: 

Constraints on U and V 

For example, probabilistic matrix factorization methods use a log-likelihood function rather than the Frobenius norm as the optimization function. Similarly, various types of nonneg ative matrix factorization impose nonnegativity constraints on U and V. Logistic matrix factorization methods apply a logistic function on the entries of $U V ^ { T }$ in order to materialize the probability that a particular entry is 1. Such an approach works well for matrices with binary entries. Therefore, the optimization framework of unconstrained matrix factorization provides a starting point for factorizations with different properties. These methods will be discussed in detail in Chapter 8. Most matrix factorization formulations are not convex. Nevertheless, gradient descent works quite well in these cases. 

## 7.3.4 Principal Component Analysis

Principal component analysis (PCA) is very closely related to SVD. SVD tries to find a kdimensional subspace, so that projecting the data points in that subspace maximizes their aggregate squared distances about the origin; in contrast, principal component analysis tries to preserve the aggregate squared distances about the data mean. The aggregate squared distances about the data mean are captured by the variance (albeit in averaged form). As a result, given a data set D, the relationship between SVD and PCA is as follows: 

PCA performs exactly the same dimensionality reduction as SVD on a meancentered data set $D _ { \ast }$ 

When the data is not mean-centered up front, PCA and SVD will yield different results. In PCA, we first mean-center the data set by subtracting the d-dimensional mean-vector of the full data set D from each row as follows: 

$$
M = D - \underbrace {\overline {{1}} \overline {{\mu}}} _ {n \times d}
$$

Here, $\overline { { 1 } }$ is a column vector of n ones, and $\overline { { \mu } }$ is a d-dimensional row vector containing the mean values of each of the d dimensions. Therefore, 1 $\overline { { \mu } }$ is an $n \times d$ matrix in which each row is the mean vector ${ \overline { { \mu } } } .$ We compute the covariance matrix $C$ as follows: 

$$
C = \frac {M ^ {T} M}{n}
$$

The covariance matrix $C$ is a d $\times \ d$ matrix, in which the $( i , j )$ th entry is simply the covariance between the dimensions i and $j$ . The diagonal entries are the dimension-specific variances. Like the scatter matrix $D ^ { T } D$ in SVD, the covariance matrix in SVD is also positive semidefinite. The covariance matrix may be approximately diagonalized at rank-k as follows: 

$$
C \approx V \Delta V ^ {T}
$$

Here, V is a $d \times k$ matrix with columns containing the top-k eigenvectors, and $\Delta$ is a $k \times k$ diagonal matrix with the diagonal entries containing the top-k eigenvalues (which are always nonnegative for the positive semidefinite matrix $C \propto M ^ { T } M )$ . The $( r , r )$ th diagonal entry is therefore denoted by the nonnegative value $\lambda _ { r } ^ { 2 } .$ , and it represents the rth eigenvalue. As we will see later, the value of $\lambda _ { r } ^ { 2 }$ is equal to the variance of the rth column of the k-dimensional projection $D V$ of the matrix $D$ . Instead of referring to the eigenvectors as singular vectors (as in SVD), they are referred to as principal components in PCA. Note that if one were to perform singular value decomposition on the mean-centered matrix M, the right singular vectors are the PCA eigenvectors, and the rth singular value $\sigma _ { r r }$ of SVD is related to the eigenvalue $\lambda _ { r } ^ { 2 }$ of PCA as follows: 

$$
\lambda_ {r} ^ {2} = \frac {\sigma_ {r r} ^ {2}}{n}
$$

The additional factor of $n$ in the denominator comes from dividing $M ^ { T } M$ by n to obtain the covariance matrix The $n \times k$ matrix $U$ containing the k-dimensional representation of the n rows of D is defined by projecting the rows of M on the columns of $V$ : 

$$
U = M V
$$

We make the following observations about PCA: 

1. The matrix $U$ is mean-centered just like the mean-centered data set M. In other words, the reduced representation of the data is also mean-centered. Note that the sum of the rows of U is given by $\begin{array} { r } { \overline { { 1 } } U = \overline { { 1 } } [ M V ] = \underbracket { [ \overline { { 1 } } M ] } _ { \qquad } V } \end{array}$ 

2. The covariance of the matrix $U$ is the diagonal matrix $\Delta .$ . Consider the case in which the matrix V contains the k columns $\overline { { v } } _ { 1 } \ldots \overline { { v } } _ { k }$ . Since the matrix U is mean-centered, its covariance matrix is given by $U ^ { T } U / n .$ , which can be simplified as follows: 

$$
\begin{array}{c} \frac {U ^ {T} U}{n} = V ^ {T} \frac {[ M ^ {T} M ]}{n} V = [ \overline {{v}} _ {1} \ldots \overline {{v}} _ {k} ] ^ {T} (C [ \overline {{v}} _ {1} \ldots \overline {{v}} _ {k} ]) \\ = [ \overline {{v}} _ {1} \ldots \overline {{v}} _ {k} ] ^ {T} [ \lambda_ {1} ^ {2} \overline {{v}} _ {1} \ldots \lambda_ {k} ^ {2} \overline {{v}} _ {k} ] = \Delta \end{array}
$$

In the above simplification, we used the fact that each $\overline { { v } } _ { i }$ is an eigenvector of the covariance matrix $C ,$ and that these k vectors are orthonormal. Therefore, $\overline { { v } } _ { i } \cdot \overline { { v } } _ { j }$ is 1 when $i = j$ , and 0, otherwise. As a result, the diagonal entries of $\Delta$ will contain $\lambda _ { 1 } ^ { 2 } \ldots \lambda _ { k } ^ { 2 } .$ 

3. The retained variance in the data is given by $\textstyle \sum _ { i = 1 } ^ { k } \lambda _ { i } ^ { 2 }$ . This is easy to show because the covariance matrix of U is $\Delta$ . Therefore, the sum of its diagonal entries, which is $\textstyle \sum _ { i = 1 } ^ { k } \lambda _ { i } ^ { 2 }$ , yields the retained variance. 

All of the above results show that PCA has very similar properties to SVD. In order to completely reconstruct the data from U and $V ^ { T }$ , one also needs to store the mean vector ${ \overline { { \mu } } } ,$ which was used to mean-center the data. In other words, the original (uncentered) data set can be reconstructed by using the following approach: 

$$
D \approx D _ {p c a} = U V ^ {T} + \overline {{1}} \overline {{\mu}}\tag{7.12}
$$

The amount of overhead for storing $\overline { { \mu } }$ is small, and it asymptotically vanishes for large data sets. 

The mean-centering of PCA helps in improving the accuracy of the approximation. In order to understand this point, we have shown an example of a 3-dimensional data set that is not originally mean-centered in Figure 7.6. Most of the data is distributed near a plane far away from the origin (before preprocessing or mean-centering). In this case, a 2-dimensional hyperplane can approximate the data quite well, where the mean-centering process ensures that the PCA hyperplane passed through the mean of the original data set. This is not the case for SVD, which will struggle to approximate the data without using all the three dimensions. It can be explicitly shown that the accuracy of PCA is at least as good as that of SVD for the same number of eigenvectors. 

![image](<Images/07_Singular_Value_Decomposition_image_007.jpg>)



Figure 7.6: PCA for data that is not originally mean-centered


Problem 7.3.1 Consider an n d data set D, whose rank-k approximations using truncated SVD and PCA are $D _ { s v d }$ and $D _ { p c a }$ , respectively (see Equation 7.12). Then, the information loss in PCA can never be larger that that in SVD: 

$$
\| D - D _ {p c a} \| _ {F} ^ {2} \leq \| D - D _ {s v d} \| _ {F} ^ {2}
$$

For mean-centered data, the accuracy of the two methods is identical because $D _ { p c a } = D _ { s v d }$ 

The geometric intuition for the above exercise is that PCA finds a k-dimensional hyperplane that must pass through the mean of the data, whereas SVD finds the k-dimensional hyperplane passing through the origin. The former provides better reconstruction. However, as the next exercise shows, the difference is usually not too large. 

Problem 7.3.2 Show that the squared error of SVD at a truncation rank $o f \left( k + 1 \right)$ is no larger than the squared error of PCA at a truncation rank of k for any $k \geq 1$ 

A hint for solving the above problem is to show using Lemma 2.6.2 of Chapter 2 that the mean-corrected reconstruction $D _ { p c a }$ (cf. Equation 7.12) has rank at most (k + 1). The SVD of D at rank-(k + 1) will provide a better rank-(k + 1) reconstruction because of its optimality properties. 

## 7.4 Applications of Singular Value Decomposition

Singular value decomposition has numerous applications in machine learning. The following will provide an overview of some of the key applications of singular value decomposition. 

## 7.4.1 Dimensionality Reduction

The most widely used application of singular value decomposition and principal component analysis is dimensionality reduction. Given a $d \times k$ basis matrix V, both PCA and SVD transform the $n \times d$ data matrix D to the $n \times k$ data matrix DV. In other words, each d-dimensional row in D is transformed to a k-dimensional row in DV. 

The above dimensionality reduction can be performed with either PCA or with SVD. What types of data sets are more suitable for PCA, and which ones are suitable for SVD? PCA is often used for numerical data of modest dimensionality that is not sparse, whereas SVD is often used for sparse and high-dimensional data. A classical example of a data domain that is more suitable to the use of SVD as opposed to PCA is text data. Note that if one attempted to use PCA on text data, the mean-centering process would destroy the sparsity of the data. Destroying the sparsity of the data results in dense matrices that are computationally difficult to process from a practical point of view. When SVD is used for text data, it is referred to as latent semantic analysis or LSA. A detailed discussion of latent semantic analysis for text is provided in [2]. 

Singular value decomposition is often used for compression of images. An image can be represented as a matrix of pixels, which can be compressed using SVD. In cases where there are multiple colors in the image, each color channel is processed as a separate matrix. An image matrix is often of full rank, although the lower ranks have very small singular values. Figure 7.7 illustrates the case of an image of size 807 611 in which the 611th singular value is non-zero. The rank of the image matrix is therefore 611, and the full-rank reconstruction of Figure 7.7(d) is identical to the original image. Obviously, there are no space advantages of full-rank reconstruction, and one must use truncation. Using a rank that is too low, such as 5, loses a lot of information, and the resulting image does not show too many useful details (cf. Figure 7.7(a)). An SVD of rank-50 loses only a small amount of detail, as shown in Figure 7.7(b). Furthermore, an SVD of rank-200 is virtually indistinguishable from the original image (cf. Figure 7.7(c)). 

![image](<Images/07_Singular_Value_Decomposition_image_008.jpg>)



(a) Rank-5


![image](<Images/07_Singular_Value_Decomposition_image_009.jpg>)



(b) Rank-50


![image](<Images/07_Singular_Value_Decomposition_image_010.jpg>)



(c) Rank-200


![image](<Images/07_Singular_Value_Decomposition_image_011.jpg>)



(d) Original (Rank-611)



Figure 7.7: SVD reconstruction at different ranks. The reconstruction at rank-200 is nearly identical to that of the full-rank image


With certain types of images, noisy artifacts of the image can even be removed by the SVD truncation at intermediate values of the rank. This is because the dropping of the lowerorder components leads to the discarding of the grainy noise components rather than the informative portions of the image. Therefore, the “lossiness” of the low-rank reconstruction is sometimes useful. This is an issue, which will be discussed in the next section. 

## 7.4.2 Noise Removal

One interesting side effect of dimensionality reduction is that it often reduces the amount of noise in the data. For example, if image data is corrupted with some amount of noise, it is often helpful to reconstruct it with truncated SVD. The basic intuition is that a minor amount of noise is often independent of the aggregate patterns in the data. Therefore, this noise often shows up in the lower-order components of SVD, which are largely independent of the dominant patterns in the higher-order components. This type of behavior is also exhibited in text data, where singular value decomposition tends to improve the retrieval accuracy. In the particular case of text, singular value decomposition reduces the noise and ambiguity effects inherent in languages; two examples of such ambiguity effects are synonymy and polysemy. For example, the fact that a word might have multiple meanings might be viewed as a kind of noise in the lower order components of SVD. The higher-order components of SVD tend to focus on the correlations, and therefore they do a much better job at disambiguating a word based on its context. A detailed discussion of the noise removal effects of SVD may be found in [7, 33]. This type of behavior is also observed in the case of image data reconstruction. In many cases, the quality of reconstruction of blurry images is higher with the use of intermediate values of the ranks. 

## 7.4.3 Finding the Four Fundamental Subspaces in Linear Algebra

The four fundamental subspaces in linear algebra are the row space, the column space, the right null space, and the left null space (cf. Section 2.4 of Chapter 2). Consider an $n \times d$ matrix D with rank $r \leq \operatorname* { m i n } \{ n , d \}$ . Let the full SVD of D be given by ${ \cal D } = { \cal Q } \Sigma { \cal P } ^ { T }$ . Then, the four fundamental subspaces of linear algebra are given by the following: 

1. The r non-zero right singular vectors of D define an orthogonal basis for the row space of D. This is because the vector $D ^ { T } \overline { { x } } = P \Sigma ^ { T } [ Q ^ { T } \overline { { x } } ] = [ \breve { P } \Sigma ^ { T } ] \overline { { y } }$ can always be shown to be a linear combination of the non-zero right singular vectors [non-zero columns of $P \Sigma ^ { T } ]$ for any $\overline { { x } } \in \mathcal { R } ^ { n }$ 

2. The r non-zero left singular vectors of D define an orthogonal basis for the column space of D. This is because the vector $D \overline { { x } } = Q \Sigma [ P ^ { T } \overline { { x } } ] = [ Q \Sigma ] \overline { { z } }$ can always be shown to be a linear combination of the non-zero left singular vectors [non-zero columns of QΣ] for any $\overline { { x } } \in \mathcal { R } ^ { d }$ 

3. The $( d - r )$ zero right singular vectors contained in the columns of P define an orthog onal basis for the right null space of D, because the right null space is the orthogonal complementary space to the row space of D. 

4. The $( n { - } r )$ zero left singular vectors contained in the columns of Q define an orthogonal basis for the left null space of D. This is because the left null space is the orthogonal complementary space to the column space of D. 

Problem 7.4.1 In Chapter 2, we showed that the row rank of a matrix is the same as its column rank. This value is referred to as the matrix rank, which is used throughout this chapter. Discuss why the existence of SVD provides an alternative proof that the row rank of a matrix is the same as its column rank. 

## 7.4.4 Moore-Penrose Pseudoinverse

The Moore-Penrose pseudoinverse can be used for solving systems of linear equations, and for providing a solution to the problem of linear regression (cf. Section 4.7.1.1 of Chapter 4). SVD can be used to efficiently compute the Moore-Penrose pseudoinverse. Consider the compact SVD of an $n \times d$ matrix D of rank $k \leq \operatorname* { m i n } \{ n , d \}$ 

$$
D = Q \Sigma P ^ {T}
$$

Here, Q is an $n \times k$ matrix, Σ is a $k \times k$ diagonal matrix with only positive diagonal entries, and P is ${ \mathrm { ~ a ~ } } d \times k$ matrix. Note that all diagonal entries of Σ are positive and Σ is a square matrix, because we are using the compact SVD rather than the full SVD. Then, the pseudoinverse $D ^ { + }$ of D is given by the following: 

$$
\begin{array}{c} D ^ {+} = \lim _ {\lambda \to 0 ^ {+}} (D ^ {T} D + \lambda I _ {d}) ^ {- 1} D ^ {T} = \lim _ {\lambda \to 0 ^ {+}} P (\Sigma^ {2} + \lambda I _ {k}) ^ {- 1} \Sigma Q ^ {T} \\ = P \underbrace {[ \lim _ {\lambda \to 0 ^ {+}} (\Sigma^ {2} + \lambda I _ {k}) ^ {- 1} \Sigma ]} _ {\Sigma^ {- 1}} Q ^ {T} = P \Sigma^ {- 1} Q ^ {T} \end{array}
$$

The matrix $\Sigma ^ { - 1 }$ is obtained by replacing each diagonal entry in Σ by its reciprocal. 

## 7.4.4.1 Ill-Conditioned Square Matrices

As discussed in Section 2.9 of Chapter 2, a singular (square) matrix might occasionally appear to be non-singular because of computational errors in fixed-precision computers while arriving at that matrix. Inverting such matrices directly can cause numerical overflows. In such cases, one wants to detect this situation, and compute the pseudoinverse of the nearest singular approximation, rather than the direct inverse. This situation is detected using the condition number of the $d \times d$ matrix $D ,$ which is defined as the ratio of the largest value of $\| D { \overline { { x } } } \| / \| { \overline { { x } } } \|$ to the smallest value of $\| D { \overline { { x } } } \| / \| { \overline { { x } } } \|$ over all vectors $\overline { { x } } \in \mathcal { R } ^ { d }$ (cf. Definition 2.9.1 of Chapter 2). An interesting result is that the condition number can be expressed in terms of the ratio of the singular values of the matrix: 

Lemma 7.4.1 The condition number of a matrix is the ratio of its largest singular value to its smallest singular value. 

The above lemma can be shown by showing that the scaling ratio $\| D { \overline { { x } } } \| / \| { \overline { { x } } } \|$ of vector $\textstyle { \overline { { x } } }$ is maximized by choosing x to be the largest right singular vector of the matrix, and the scaling ratio is minimized by choosing the smallest right singular vector. As a result, the condition number is the ratio of the two quantities. 

Lemma 7.4.2 The maximum value of $\| D \overline { { x } } \|$ for $m \times m$ matrix D is $\sigma _ { 1 }$ for unit vector ${ \overline { { x } } } ,$ where $\sigma _ { 1 }$ is the largest singular value. A similar result holds for the minimum value of $\| D \overline { { x } } \|$ 

Proof: One can express $Q \Sigma P ^ { T }$ , where $Q$ and $P$ are rotation matrices. Therefore, $P ^ { T } { \overline { { x } } }$ can be written as another unit vector ${ \overline { { x } } } ^ { \prime }$ . Let $x _ { 1 } \ldots x _ { m }$ be the components of ${ \overline { { x } } } ^ { \prime }$ . The value $\Sigma \overline { { x } } ^ { \prime }$ has the norm of $\sigma _ { 1 }$ , when the first component of the unit vector ${ \overline { { x } } } ^ { \prime }$ is 1 and all other components are 0. This vector ${ \overline { { x } } } ^ { \prime }$ is obtained by choosing $\textstyle { \overline { { x } } }$ to be the largest right singular vector of D. Furthermore, the squared norm of $\Sigma \overline { { x } } ^ { \prime }$ for any other vector $\overline { { x } } ^ { \prime } = [ f _ { 1 } \ldots f _ { m } ]$ is $\scriptstyle \sum _ { i = 1 } ^ { m } f _ { i } ^ { 2 } \sigma _ { i } ^ { 2 }$ , where $\textstyle \sum _ { i = 1 } ^ { m } f _ { i } ^ { 2 } = 1$ . This squared norm is the weighted average of $\sigma _ { 1 } ^ { 2 } \ldots \sigma _ { m } ^ { 2 } ,$ which can be no larger than $\sigma _ { 1 } ^ { 2 }$ . The result follows. 

Problem 7.4.2 Show that a real eigenvalue of a square matrix can never be larger in magnitude than the largest singular value of the matrix. Also show that a real eigenvalue can never be smaller in magnitude than the smallest singular value of the matrix. 

Poorly conditioned matrices will become obvious in SVD when all singular values are positive but are different by orders of magnitude. How can one invert such a matrix without causing overflows? Note that one need not even use all the positive singular values in SVD. Rather, one can use truncated SVD, and remove the smaller singular values. In other words, if the truncated SVD of rank-k is $Q _ { k } \Sigma _ { k } P _ { k } ^ { T }$ , then the resulting inverse is $P _ { k } \Sigma _ { k } ^ { - 1 } Q _ { k } ^ { T }$ . Surprisingly, truncating very small singular values often has a beneficial effect in terms of prediction accuracy, when using the Moore-Penrose pseudoinverse in machine learning applications like least-squares regression. This is because it helps in reducing the effect of computational errors caused by the numerical inexactness of floating point representation in computers. Such computational errors might cause singular values that ought to be zero to take on small values like $1 0 ^ { - 6 }$ . This approach can also help with solving ill-conditioned systems of equations. Furthermore, truncating small singular values has a regularization effect, when the Moore-Penrose pseudoinverse is used to compute the solution to machine learning problems like linear regression. This improves the performance on out-of-sample predictions. This issue is discussed in the next section, and is an example of the fact that the goals of optimization in machine learning are often different from those of traditional optimization (see Section 4.5.3 of Chapter 4). 

## 7.4.5 Solving Linear Equations and Linear Regression

The problem of solving homogeneous linear equations is that of finding the solution to the homogeneous system of equations $A { \overline { { x } } } = 0$ , where A is an $n \times d$ matrix and x is a d-dimensional column vector. In other words, we want to discover the right null space of A. Singular value decomposition is a natural way to achieve this goal because the right singular vectors contain the basis of the rows of A, and the zero singular values correspond to the null space. If x is a right-singular vector of A with zero singular value, then the eigenvector properties of A also yield $A { \overline { { x } } } = 0$ . What happens when there is no zero singular value? In such a case, there is no solution to this system of linear equations, although one can find a (unit normalized) solution x in which $\| { \dot { A } } { \overline { { x } } } \| ^ { 2 }$ is minimized. As shown in Lemma 7.4.2, the minimum value is the smallest singular value. Furthermore, this optimum value of x is the right singular vector. We leave this problem as an exercise: 

Problem 7.4.3 The unit-normalized solution to the problem of minimizing $\| A { \overline { { x } } } \| ^ { 2 }$ is the smallest right-singular vector of A. 

Singular value decomposition can also be used for solving the system of equations $A { \overline { { x } } } = { \overline { { b } } }$ Here, b is an n-dimensional column vector. Solving the system equations $A { \overline { { x } } } = { \overline { { b } } }$ is a special case of the (more general) problem of minimizing $\dot { \| } A \overline { { x } } - \dot { \bar { b } } \| ^ { 2 }$ . This is identical to the problem of linear regression. One can use the Moore-Penrose pseudoinverse is used to compute the solution to least-squares regression (cf. Section 4.7.1.1 of Chapter 4): 

$$
\overline {{x}} = A ^ {+} \overline {{b}}\tag{7.13}
$$

Using truncated SVD instead of SVD is beneficial from the perspective of regularization. In the event that the original data matrix A is mean-centered, and truncated SVD is used to compute the pseudoinverse, the resulting solution is referred to as principal components regression. 

## 7.4.6 Feature Preprocessing and Whitening in Machine Learning

Principal component analysis is used for feature preprocessing in machine learning, by first reducing the dimensionality of the data and then normalizing the newly transformed features, so that the variance along each transformed direction is the same. Let $V _ { k }$ be the $d \times k$ matrix containing the top-k eigenvectors found by principal component analysis. Then, the first step is to transform the mean-centered data matrix D to the k-dimensional representation $U _ { k }$ as follows: 

$$
U _ {k} = D V _ {k}
$$

The next step is to divide each column of $U _ { k }$ by its standard deviation. As a result, the original data distribution becomes roughly spherical in shape. This type of approach is referred to as whitening. 

This type of data distribution works much more effectively with gradient-descent algorithms. This is because widely varying variances along different directions also lead to loss functions in which different directions have different levels of curvature. Examples of two loss functions with different levels of curvature are illustrated in Figure 5.2 of Chapter 5. A loss function like Figure 5.2(a) tends to be more easily optimized with gradient descent algorithms. Normalizing the data to have unit variance in all directions tends to reduce obvious forms of ill-conditioning in the loss function. As a result, gradient-descent tends to become much faster. Furthermore, the normalization of the data in this way sometimes prevents some subsets of features from having undue influence on the final results. 

![image](<Images/07_Singular_Value_Decomposition_image_012.jpg>)



Figure 7.8: An example of the whitening of an ellipsoidal data distribution by principal component analysis and its use in outlier detection


This type of preprocessing is also used in unsupervised applications like outlier detection. In fact, whitening is arguably more important in unsupervised applications because one does not have labels to provide guidance about the relative importance of different directions in the data. An example of the whitening of an ellipsoidal data distribution is illustrated in Figure 7.8. The resulting data distribution has a spherical shape. 

## 7.4.7 Outlier Detection

The whitening approach described in the previous section is also used for outlier detection. The resulting technique is also referred to as soft PCA or the Mahalanobis method. The overall approach uses two steps: 

1. First, the $n \times d$ data matrix D is mean-centered, and PCA is used to transform it to an n k data matrix $U _ { k } = D V _ { k }$ . Here, $V _ { k }$ contains the top-k eigenvectors of the covariance matrix. Each column of $U _ { k }$ is normalized to unit variance. This type of approach will tend to increase the absolute distance of outliers from the data mean when they deviate along low-variance directions. In fact, for low-dimensional data, the value of the rank, k, might be the full dimensionality but the distortion of the ellipsoidal data distribution to a spherical distribution will change the relative propensity of different points to be considered outliers. 

2. The squared distance of each point from the data mean is reported as its outlier score. 

Although some of the low-variance principal components may be dropped (in order to avoid directions in which variances are caused by computational errors), the primary goal of whitening is to change the relative importance of the independent directions, so as to emphasize relative variations along the principal directions. It is the distortion of the shape of the data distribution that is the key to the discovery of non-obvious outliers. For example, the point A is further from the center of the original data distribution, as compared to point B. However, the point A is aligned along the elongated axis of the data distribution, and therefore it is much more consistent with overall shape of the distribution. This pattern becomes more obvious when we apply principal component analysis to the data distribution. This tends to separate B from the data distribution and the distance from the center of the data distribution provides an outlier score that is larger for point B as compared to point A. The resulting method is referred to as soft PCA because its uses soft distortions of the data distribution rather than truncation of low-variance directions. In fact, low-variance directions are more important in this case for discovering outliers. This approach is also referred to as the Mahalanobis method because the distance of each point from the center of the data distribution after PCA-based normalization is equivalent to the Mahalanobis distance. Intuitively, the Mahalanobis distance is the exponent of the Gaussian distribution, which assumes that the original data has an ellipsoidal shape. The whitening along principal component directions simply discovers which points are unlikely to belong to this Gaussian distribution. 

Definition 7.4.1 (Mahalanobis Distance) Let $\overline { { X } }$ be a d-dimensional row vector from the data set and $\overline { { \mu } }$ be the mean (row vector) of a data set. Let C be the $d \times d$ covariance matrix of a d-dimensional data set in which the $( i , j )$ th entry is the covariance between the dimensions i and $j$ . Then, the squared Mahalanobis distance of the point $\overline { { X } }$ is given by the following: 

$$
M a h a (\overline {{X}}, \overline {{\mu}}) ^ {2} = (\overline {{X}} - \overline {{\mu}}) C ^ {- 1} (\overline {{X}} - \overline {{\mu}}) ^ {T}\tag{7.14}
$$

At first glance, the Mahalanobis distance seems to have little to do with PCA or to normalization of points by the standard deviations along principal components. However, the key point is that the covariance matrix can be expressed as $V \Delta V ^ { T }$ , where the columns of V contain the eigenvectors. Then, the Mahalanobis distance can be expressed in terms of the eigenvectors as follows: 

$$
M a h a (\overline {{X}}, \overline {{\mu}}) ^ {2} = (\overline {{X}} - \overline {{\mu}}) C ^ {- 1} (\overline {{X}} - \overline {{\mu}}) ^ {T}\tag{7.15}
$$

$$
= (\overline {{X}} - \overline {{\mu}}) [ V \Delta V ^ {T} ] ^ {- 1} (\overline {{X}} - \overline {{\mu}}) ^ {T}\tag{7.16}
$$

$$
= \underbrace {[ (\overline {{X}} - \overline {{\mu}}) V ]} _ {\Delta^ {- 1} [ (\overline {{X}} - \overline {{\mu}}) V ] ^ {T}}\tag{7.17}
$$

$$
\mathrm{BasisChange}
$$

Note that postmultiplying $( { \overline { { X } } } - { \overline { { \mu } } } )$ with V results in mean-centering with $\overline { { \mu } }$ and then transformation to the orthonormal basis system in the columns of $V .$ . Multiplying with $\Delta ^ { - 1 / 2 }$ simply scales each dimension with the inverse of the standard deviation. Consider the following definition of the row vector $\overline { Z }$ containing the scaled coordinates of the data points: 

$$
\overline {{Z}} = (\overline {{X}} - \overline {{\mu}}) V \Delta^ {- 1 / 2}
$$

Note that the matrix $\Delta ^ { - 1 / 2 }$ is a diagonal matrix containing the inverse of the standard deviation along each principal component. This approach transforms the mean-centered row vector $( { \overline { { X } } } - { \overline { { \mu } } } )$ to a new basis and normalizes it with the standard deviation along each principal component. It is not difficult to see that the row vector $\overline { { Z } }$ is the whitened coordinate representation of the row vector $\overline { { X } }$ , and the squared Mahalanobis distance is given by $\| { \overline { { Z } } } \| ^ { 2 }$ . Furthermore, one can easily verify that $\| \overline { { Z } } \| ^ { 2 } = \overline { { Z } } \overline { { Z } } ^ { T }$ simplifies to the covariance-based definition of Mahalanobis distance in Equation 7.17. A detailed discussion of the Mahalanobis method is provided in [4]. One can even combine the Mahalanobis method with feature engineering in order to discover non-obvious outliers. One example of such a feature engineering approach is discussed in the next section. 

## 7.4.8 Feature Engineering

Singular value decomposition uses the eigenvectors of the dot product similarity matrix $D D ^ { T }$ as the left singular vectors, and the eigenvectors of the scatter matrix $D ^ { T } \dot { D }$ are the right singular vectors. The decomposition $D = Q \Sigma P ^ { T }$ provides the left singular vectors in the columns of $Q$ and the right singular vectors in the columns of $P .$ . The (scaled) left singular vectors $Q \Sigma$ provide the embedding, whereas the right singular vectors $P$ provide the basis. Either of the two matrices can be used to compute the transformed data in the standard version of SVD. While the direct extraction of the right singular vectors is more common because of the intuitive appeal of a basis, the left singular vectors can directly provide the embeddings (without worrying about a basis). In some application centric settings, no multidimensional representation of the data is available, but only a similarity matrix $S$ is available. For example, S might represent the pairwise similarities between a set of small graph objects. In such cases, one can assume that the provided similarity matrix corresponds to $D D ^ { T }$ for some unknown $n \times n$ matrix $D _ { ; }$ , whose rows contain the multidimensional representations of the graph objects. Note that the matrix D might have as many as n dimensions because any set of n objects (together with the origin) always defines an n-dimensional plane. In such cases, one can simply diagonalize S as follows: 

$$
S = D D ^ {T} = Q \Sigma^ {2} Q ^ {T} = (Q \Sigma) (Q \Sigma) ^ {T}
$$

The $n \times n$ matrix QΣ is provides the multidimensional embeddings of the points in its rows. If the similarity matrix $S$ was derived by using dot products on multidimensional data, then the resulting representation will provide the vanilla SVD embedding of $D .$ Note that any rotated representation DV of D will provide the same embedding, because $( D V ) ( D V ) ^ { T } = D ( V ^ { T } V ) { \bar { D } } = D D ^ { T }$ . We cannot control the basis in which the unknown matrix $D$ is represented in the final embedding $Q \Sigma ;$ ; singular value decomposition happens to choose the basis in which the columns of the embedded representation are orthogonal. This type of approach works only when the similarity matrix $S$ is positive semidefinite, because the eigenvalues in $\Sigma ^ { 2 }$ need to be nonnegative. Such similarity matrices are referred to as kernel matrices. You will learn more about kernel matrices in Chapter 9. 

This type of approach is referred to as feature engineering, because we can convert any arbitrary object (e.g., graph) to a multidimensional representation by using the pairwise similarities between them. For example, one can combine the Mahalanobis method for outlier detection (see previous section) with the feature engineering approach discussed in this section. Consider a set of n graphs with an $n \times n$ similarity matrix S. We wish to identify the graphs that should be labeled as outliers. One can extract the embedding QΣ from the diagonalization $S = Q \Sigma ^ { 2 } Q ^ { T }$ . By whitening the representation, one obtains the embedding $Q$ in which each column has unit variance. The distance of each row in $Q$ from the mean of the rows of $Q$ provides the kernel Mahalanobis outlier score. Even for multidimensional data, one can extract more insightful features by replacing the dot products in $D D ^ { T }$ with other similarity functions between points. In Chapter 9, we will provide specific examples of such similarity functions. 

## 7.5 Numerical Algorithms for SVD

In this section, we will discuss some simple algorithms for singular value decomposition. These algorithms are not optimized for efficiency, but they provide the basic ideas for some of the advanced algorithms. Given an n d matrix D, the simplest (and most naive) approach is to find the eigenvectors of $D ^ { T } D$ or $D D ^ { T }$ using the approach discussed in Section 3.5 of Chapter 3. The choice of using either $D ^ { T } D$ or $\check { D } \bar { D } ^ { T }$ depends on which matrix is smaller. Using the former helps in finding the right singular vectors, whereas using the latter helps in finding the left singular vectors. In most cases, we only need to find the top-k singular vectors, where $k \ll \mathrm { m b o x } \{ n , d \}$ . If we use $D ^ { T } D$ to compute the $d \times k$ matrix $P$ containing the right singular vectors, the left singular vectors will be contained in the $n \times k$ matrix $Q = D P \Sigma ^ { - 1 }$ . The $k \times k$ matrix Σ is computed by placing the square root of the eigenvalues on the diagonal of the matrix. We can assume that we are only interested in non-zero singular vectors, and therefore Σ is invertible. On the other hand, if the left singular vectors are found by diagonalizing $D D ^ { T }$ , then the matrix P can be computed as $P = \bar { D } ^ { T } Q \Sigma ^ { - 1 }$ 

This approach is inefficient for sparse matrices. For example, consider a text data set in which each row contains about 100 non-zero values, but the dimensionality d of the row is $1 0 ^ { 5 }$ . Similarly, the collection contains $1 0 ^ { 6 }$ documents, which is not large by modern standards. The number of non-zero entries in D is $1 0 ^ { 8 }$ , which is much smaller than the total number of entries in $D .$ . Therefore, this is a sparse matrix for which special data structures can be used. $\mathrm { O n }$ the other hand, $D ^ { T } D$ is a dense matrix that contains $1 0 ^ { 1 0 }$ entries. Therefore, it is inefficient to work with $D ^ { T } D$ as compared to $D$ . In the following, we present the generalization of the power method discussed in Section 3.5 that works with $D$ rather than $D ^ { T } D$ . It is noteworthy that this method is not optimized for efficiency, but it provides the starting points for understanding some efficient methods such as the Lanczos algorithm [52]. In recent years, methods based on QR decomposition have become more popular. A specific example is the Golub and Kahan algorithm [52]. 

## The Power Method

The power method can find the dominant eigenvector of any matrix (like $D ^ { T } D )$ by first ini tializing it to a random d-dimensional column vector $\overline { { p } } _ { 1 }$ and then repeatedly pre-multiplying with $D ^ { \check { T } } D$ and scaling to unit norm. However, $D ^ { T } D$ is dense, and one has to be careful about how these operations are performed. To reduce the number of operations, it makes sense to compute the operations in the order dictated by the brackets in $[ D ^ { T } ( D \overline { { p } } ) ]$ ]. Therefore, we repeat the following step to convergence: 

$$
\overline {{p}} _ {1} \Leftarrow \frac {[ D ^ {T} (D \overline {{p}} _ {1}) ]}{\| [ D ^ {T} (D \overline {{p}} _ {1}) ] \|}
$$

The projection of the data matrix D on the vector $\overline { { p } } _ { 1 }$ has an energy that is equal to the square of the first singular value. Therefore, the first singular value $\sigma _ { 1 1 }$ is obtained by using the $L _ { \mathrm { { 2 } } } \mathrm { { - n o r m } }$ of the vector $D \overline { { p } } _ { 1 }$ . The first column $\overline { { q } } _ { 1 }$ of $Q$ is obtained by a single execution of the following step: 

$$
\overline {{q}} _ {1} \Leftarrow \frac {D \overline {{p}} _ {1}}{\sigma_ {1 1}}\tag{7.18}
$$

The above result is a 1-dimensional simplification of $Q \ = \ D P \Sigma ^ { - 1 }$ . This completes the determination of the first set of singular vectors and singular values. The next eigenvector and eigenvalue pair is obtained by making use of the spectral decomposition of Equation 7.1. One possibility is to remove the rank-1 component contributed by the first set of singular vectors by adjusting the data matrix as follows: 

$$
D \Leftarrow D - \sigma_ {1 1} \overline {{q}} _ {1} \overline {{p}} _ {1} ^ {T}\tag{7.19}
$$

Once the impact of the first component has been removed, we can repeat the process to obtain the second set of singular vectors from the modified matrix. The main problem with this approach is that the removal of spectral components hurts the sparsity of $D$ 

Therefore, in order to avoid hurting the sparsity of D, one need not explicitly remove the rank-1 matrix $\overline { { q } } _ { 1 } \overline { { p } } _ { 1 } ^ { T }$ from D. Rather, the original matrix D is used, and the second set of singular vectors can be computed by using the following iterative step (that removes the effect of the first component within the iterations): 

$$
\begin{array}{l} \overline {{p}} _ {2} \Leftarrow (D ^ {T} - \sigma_ {1 1} \overline {{p}} _ {1} \overline {{q}} _ {1} ^ {T}) ([ D - \sigma_ {1 1} \overline {{q}} _ {1} \overline {{p}} _ {1} ^ {T} ] \overline {{p}} _ {2}) \\ \overline {{p}} _ {2} \Leftarrow \frac {\overline {{p}} _ {2}}{\| \overline {{p}} _ {2} \|} \end{array}
$$

When computing a quantity like $[ D - \sigma _ { 1 1 } \overline { { q } } _ { 1 } \overline { { p } } _ { 1 } ^ { T } ] \overline { { p } } _ { 2 }$ , one computes $D \overline { { p } } _ { 2 }$ and $\overline { { q } } _ { 1 } [ \overline { { p } } _ { 1 } ^ { T } \overline { { p } } _ { 2 } ]$ separately. Note that the order of operations in $\overline { { q } } _ { 1 } [ \overline { { p } } _ { 1 } ^ { T } \overline { { p } } _ { 2 } ]$ is preferred to the order $[ \overline { { q } } _ { 1 } \overline { { p } } _ { 1 } ^ { T } ] \overline { { p } } _ { 2 }$ to ensure that one never has to store large and dense matrices. Therefore, the associativity property of matrix multiplication comes in handy to ensure that one is always working with multiplications between vectors, or between vectors and sparse matrices. This basic idea can be generalized to finding the kth singular vector: 

$$
\begin{array}{l} \overline {{p}} _ {k} \Leftarrow (D ^ {T} - \sum_ {r = 1} ^ {k - 1} \sigma_ {r r} \overline {{p}} _ {r} \overline {{q}} _ {r} ^ {T}) ([ D - \sum_ {r = 1} ^ {k - 1} \sigma_ {r r} \overline {{q}} _ {r} \overline {{p}} _ {r} ^ {T} ] \overline {{p}} _ {k}) \\ \overline {{p}} _ {k} \Leftarrow \frac {\overline {{p}} _ {k}}{\| \overline {{p}} _ {k} \|} \end{array}
$$

In each case, it is possible to control the order of multiplication of matrices, so that one never has to work with dense matrices. The singular value $\sigma _ { k k }$ is the norm of $D \overline { { p } } _ { k }$ . The kth left singular vector can be derived from the kth right singular vector as follows: 

$$
\overline {{q}} _ {k} \Leftarrow \frac {D \overline {{p}} _ {k}}{\sigma_ {k k}}\tag{7.20}
$$

The entire process is repeated m times to obtain the rank-m singular value decomposition. 

## 7.6 Summary

Singular value decomposition is one of the most fundamental techniques among a class of methods called matrix factorization. We present a linear algebra and an optimization perspective on singular value decomposition. These perspectives provide different insights: 

The linear algebra perspective is helpful is showing that a singular value decomposition exists, and the singular vectors are the eigenvectors of $D D ^ { \check { T } }$ and $D ^ { T } D$ 

The optimization perspective shows that singular value decomposition provides a matrix factorization with the least error. The optimization perspective can be generalized to other forms of matrix factorization, which is the subject of the next chapter. 

Singular value decomposition has numerous applications in machine learning applications like least-squares regression. The basic ideas in singular value decomposition also provide the foundations for kernel methods, which are discussed in Chapter 9. 

## 7.7 Further Reading

A discussion of SVD is provided in various linear algebra books [77, 122, 123, 130]. The fact that SVD provides an optimal solution to unconstrained matrix factorization was first pointed out in the Eckart-Young theorem [41]. Different types of numerical algorithms for singular value decomposition are discussed in [52, 130]. The noise reduction properties of singular value decomposition are discussed in [7]. The use of singular value decomposition methods in outlier detection is discussed in [4]. 

## 7.8 Exercises

1. Use SVD to show the push-through identity of Problem 1.2.13 for any $n \times d$ matrix D and scalar $\lambda > 0 \mathrm { : }$ 

$$
(\lambda I _ {d} + D ^ {T} D) ^ {- 1} D ^ {T} = D ^ {T} (\lambda I _ {n} + D D ^ {T}) ^ {- 1}
$$

This exercise is almost the same as Problem 1.2.13 in Chapter 1. 

2. Let D be an $n \times d$ data matrix, and $\overline { y }$ be an n-dimensional column vector containing the dependent variables of linear regression. The Tikhonov regularization solution to linear regression (cf. Section 4.7.1 of Chapter 4) predicts the dependent variables of a test instance $\overline { { Z } }$ using the following equation: 

$$
\mathrm{Prediction} (\overline {{Z}}) = \overline {{Z}} \overline {{W}} = \overline {{Z}} (D ^ {T} D + \lambda I) ^ {- 1} D ^ {T} \overline {{y}}
$$

Here, the vectors $\overline { { Z } }$ and $\overline { W }$ are treated as $1 \times d$ and $d \times 1$ matrices, respectively. Show using the result of Exercise 1, how you can write the above prediction purely in terms of similarities between training points or between $\overline { { Z } }$ and training points. 

3. Suppose that you are given a truncated SVD $D \approx Q \Sigma P ^ { T }$ of rank-k. Show how you can use this solution to derive an alternative rank-k decomposition $Q ^ { \prime } \Sigma ^ { \prime } P ^ { \prime T }$ in which the unit columns of $Q \ ( \mathrm { o r / a n d } \ P )$ might not be mutually orthogonal and the truncation error is the same. 

4. Suppose that you are given a truncated SVD $D \approx Q \Sigma P ^ { T }$ of rank-k. Two of the nonzero singular values are identical. The corresponding right singular vectors are $[ 1 , 0 , 0 ] ^ { T }$ and $[ 0 , \bar { 1 } , 0 ] ^ { T }$ . Show how you can use this solution to derive an alternative rank-k SVD $Q ^ { \prime } \Sigma ^ { \prime } P ^ { \prime T }$ for which the truncation error is the same. At least some columns of matrices $Q ^ { \prime }$ and $P ^ { \prime }$ need to be non-trivially different from the corresponding columns in $Q$ and ${ \cal P } \ ( \mathrm { i . e . }$ , the ith column of $Q ^ { \prime }$ should not be derivable from the ith column of $Q$ by simply multiplying with either 1 or +1). Give a specific example of how you might manipulate the right singular vectors to obtain a non-trivially different solution. 

5. Suppose that you are given a particular solution $\overline { { x } } = \overline { { x } } _ { 0 }$ that satisfies the system of equations $A { \overline { { x } } } = { \overline { { b } } }$ . Here, A is an $n \times d$ matrix, x is a d-dimensional vector of variables, and $\bar { b }$ is an n-dimensional vector of constants. Show that all possible solutions to this system of equations are of the form $\overline { { x } } _ { 0 } + \overline { { v } }$ , where $\overline { { v } }$ is any vector drawn from a vector space $\nu .$ . Show that can be found easily using SVD. [Hint: Think about the system of equations $A { \overline { { x } } } = 0 . ]$ 

6. Consider the $n \times d$ matrix D. Construct the $( n + d ) \times ( n + d )$ matrix B as follows: 

$$
B = \left[ \begin{array}{l l} 0 & D ^ {T} \\ D & 0 \end{array} \right]
$$

Note that the matrix B is square and symmetric. Show that diagonalizing B yields all the information needed for constructing the SVD of D. [Hint: Relate the eigenvectors of B to the singular vectors of SVD.] 

7. Consider the following matrix A whose SVD is given by the following: 

$$
A = \left[ \begin{array}{c c} {- 1 / \sqrt {2}} & {1 / \sqrt {2}} \\ {1 / \sqrt {2}} & {1 / \sqrt {2}} \end{array} \right] \left[ \begin{array}{c c} {4} & {0} \\ {0} & {2} \end{array} \right] \left[ \begin{array}{c c} {1} & {0} \\ {0} & {1} \end{array} \right] ^ {T}
$$

Compute the inverse of A without explicitly materializing A. 

8. Consider the following 2-way factorization of the matrix $A { : }$ 

$$
A = U V ^ {T} = \left[ \begin{array}{l l} 4 & 1 \\ 3 & 2 \end{array} \right] \left[ \begin{array}{l l} 1 & 2 \\ 1 & 1 \end{array} \right] ^ {T}
$$

Convert this factorization into a $3 \mathrm { - w a y }$ factorization $Q \Sigma P ^ { T }$ in each of the following ways: 

(a) The $L _ { \mathrm { { 2 } } } \mathrm { { - n o r m } }$ of each column of Q and P is 1. 

(b) The $L _ { \mathrm { 1 } } \mathrm { - n o r m }$ of each column of $Q$ and $P$ is 1. 

The second form of decomposition is used for nonnegative factorizations with proba bilistic interpretability. 

9. Suppose that you add a small amount of noise to each entry of an $n \times d$ matrix D with rank $r \ll$ d and $n \gg d .$ The noise is drawn from a Gaussian distribution, whose variance $\lambda > 0$ is much smaller than the smallest non-zero singular value of $D .$ . The non-zero singular values of D are $\sigma _ { 1 1 } \dots . \sigma _ { r r }$ . What do you expect the rank of the modified matrix $D ^ { \prime }$ to become? 

10. Consider the unconstrained optimization problem of minimizing the Frobenius norm $\| D - U V ^ { T } \| _ { F } ^ { 2 }$ , which is equivalent to SVD. Here, D is an $n \times d$ data matrix, $U$ is an $n \times k$ matrix, and $V$ is a $d \times k$ matrix. 

(a) Use differential calculus to show that the optimal solution satisfies the following conditions: 

$$
\begin{array}{l} {D V = U V ^ {T} V} \\ {D ^ {T} U = V U ^ {T} U} \end{array}
$$

(b) Let $E = D - U V ^ { T }$ be a matrix of errors from the current solutions $U$ and $V .$ Show that an alternative way to solve this optimization problem is by using the following gradient-descent updates: 

$$
\begin{array}{c} {U \Leftarrow U + \alpha E V} \\ {V \Leftarrow V + \alpha E ^ {T} U} \end{array}
$$

Here, $\alpha > 0$ is the step-size. 

(c) Will the resulting solution necessarily contain mutually orthogonal columns in U and $V ?$ 

11. Suppose that you change the objective function of SVD in Exercise 10 to add penalties on large values of the parameters. This is often done to reduce overfitting and improve generalization power of the solution. The new objective function to be minimized is as follows: 

$$
J = \| D - U V ^ {T} \| _ {F} ^ {2} + \lambda (\| U \| _ {F} ^ {2} + \| V \| _ {F} ^ {2})
$$

Here, $\lambda > 0$ defines the penalty. How would your answers to Exercise 10 change? 

12. Recall from Chapter 3 that the determinant of a square matrix is equal to the product of its eigenvalues. Show that the determinant of a square matrix is also equal to the product of its singular values but only in absolute magnitude. Show that the Frobenius norm of the inverse of a d d square matrix A is equal to the sum of squared inverses of the singular values of A. 

13. Show using SVD that a square matrix A is symmetric $( \mathrm { i . e . , } A = A ^ { T } )$ if and only if $A A ^ { T } = A ^ { \check { T } } A$ 

14. Suppose that you are given the following valid SVD of a matrix: 

$$
D = \left[ \begin{array}{c c c} 1 & 0 & 0 \\ 0 & 1 / \sqrt {2} & 1 / \sqrt {2} \\ 0 & 1 / \sqrt {2} & - 1 / \sqrt {2} \end{array} \right] \left[ \begin{array}{c c c} 2 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{array} \right] \left[ \begin{array}{c c c} 1 & 0 & 0 \\ 0 & 1 / \sqrt {2} & - 1 / \sqrt {2} \\ 0 & 1 / \sqrt {2} & 1 / \sqrt {2} \end{array} \right]
$$

Is the SVD of this matrix unique? You may ignore multiplication of singular vectors by 1 as violating uniqueness. If the SVD is unique, discuss why this is the case. If the SVD is not unique, provide an alternative SVD of this matrix 

15. State a simple way to find the SVD of (a) a diagonal matrix with both positive and negative entries that are all different; and (b) an orthogonal matrix. Is the SVD unique in these cases? 

16. Show that the largest singular value of $( A + B )$ is at most the sum of the largest singular values of each of A and B. Also show that the largest singular value of AB is at most the product of the largest singular values of A and B. Finally, show that the largest singular value of a matrix is a convex function of the matrix entries. 

17. If A is a square matrix, use SVD to show that $A A ^ { T }$ and $A ^ { T } A$ are similar. What happens when A is rectangular? 

18. The Frobenius norm of a matrix A is defined as the trace of either $A A ^ { T }$ or $A ^ { T } A$ . Let P be a $d \times k$ matrix with orthonormal columns. Let D be an $n \times d$ data matrix. Show that the squared Frobenius norm of DP is the same as that of $D P P ^ { T }$ . Interpret the matrices DP and $D P P ^ { T }$ in terms of their relationship with D, when P contains the top-k right singular vectors of the SVD of D. 

19. Consider two data matrices $D _ { 1 }$ and $D _ { 2 }$ that share the same scatter matrix $D _ { 1 } ^ { T } D _ { 1 } =$ $D _ { 2 } ^ { T } D _ { 2 }$ but are otherwise different. We aim to show that the columns of one are rotre flections of the other and vice versa. Show that a partially shared (full) singular value decomposition can be found for $D _ { 1 }$ and $D _ { 2 }$ , so that $D _ { 1 } = Q _ { 1 } \Sigma P ^ { T }$ and $D _ { 2 } = Q _ { 2 } \Sigma P ^ { T }$ Use this fact to show that $D _ { 2 } = Q _ { 1 2 } D _ { 1 }$ for some orthogonal matrix $Q _ { 1 2 }$ 

20. Let ${ \boldsymbol { A } } = { \overline { { a } } } { \overline { { b } } } ^ { T }$ be a rank-1 matrix for vectors $\overline { { a } } , \overline { { b } } \in \mathcal { R } ^ { n }$ . Find the non-zero eigenvectors, eigenvalues, singular vectors, and singular values of A. 

21. What are the singular values of (i) a $d \times d$ Givens rotation matrix, (ii) a $d \times d$ Householder reflection matrix, (iii) a $d \times d$ projection matrix of rank r, (iv) a $2 \times 2$ shear matrix $A = \left[ a _ { i j } \right]$ with 1s along the diagonal, and a value of $a _ { 1 2 } = 2$ in the upper right corner. 

22. Consider an $n \times d$ matrix A with linearly independent columns and non-zero singular values $\sigma _ { 1 } \ldots \sigma _ { d }$ . Find the non-zero singular values of $A ^ { T } ( A A ^ { T } ) ^ { 5 } , A ^ { T } ( A A ^ { T } ) ^ { 5 } A$ 2 $\overset { \smile } { A } ( A ^ { T } A ) ^ { - 2 } A ^ { T }$ , and $A ( A ^ { T } A ) ^ { - 1 } A ^ { T }$ . Do you recognize the last of these matrices? Which of these matrices have economy SVDs with zero singular values in addition to the non zero singular values? 

23. Suppose that you have the $n \times 3$ scatterplot matrix D of an ellipsoid in 3-dimensions, whose three axes have lengths 3, 2, and 1, respectively. The axes directions of this ellipsoid are $[ 1 , 1 , 0 ] , [ 1 , - 1 , 0 ]$ , and [0, 0, 1]. You multiply the scatter plot matrix D with a $3 \times 3$ transformation matrix A to obtain the scatter plot $D ^ { \prime } = D A$ of a new ellipsoid, in which the axes [1, 1, 1], [1, 2, 1], and $[ 1 , 0 , - 1 ]$ have lengths 12, 6, and 5, respectively. Write the singular value decompositions of two possible matrices that can perform the transformation. You should be able to write down the SVDs with very little numerical calculation. [The answer to this question is not unique, as the specific mapping of points between the two ellipsoids is not known. For example, an axis direction in the original ellipsoid may or may not match with an axis direction in the transformed ellipsoid.] 

24. Regularization impact: Consider the regularized least-squares regression problem of minimizing $\| \bar { A } \overline { { x } } - \bar { b } \| ^ { 2 } + \lambda \| \overline { { x } } \| ^ { 2 }$ for d-dimensional optimization vector ${ \overline { { x } } } ,$ , ndimensional vector b, nonnegative scalar λ, and $n \times d$ matrix A. There are several ways of showing that the norm of the optimum solution $\overline { { x } } = \overline { { x } } ^ { * }$ is non-increasing with increasing $\lambda$ (and this is also intuitively clear from the nature of the optimization formulation). Use SVD to show that the optimum solution $\overline { { x } } ^ { \ast } = ( A ^ { T } A + \mathsf { \bar { \lambda } } I _ { d } ) ^ { - 1 } A ^ { T } \overline { { b } }$ has non-increasing norm with increasing λ. 

25. The function $f ( \lambda )$ arises commonly in spherically constrained least-squares regression: 

$$
f (\lambda) = \overline {{b}} ^ {T} A (A ^ {T} A + \lambda I) ^ {- 2} A ^ {T} \overline {{b}}
$$

Here, A is an $n \times d$ matrix of rank-r, $\bar { b }$ is an n-dimensional column vector, and $\lambda > 0$ is an optimization parameter. Furthermore, $A = Q \Sigma P ^ { T }$ is the reduced SVD of A with $n \times r$ matrix $Q , d \times r$ matrix $P ,$ and $r \times r$ diagonal matrix Σ. The diagonal elements of Σ are $\sigma _ { 1 1 } \dots \sigma _ { r r }$ . Show that $f ( \lambda )$ can be written in scalar form as follows: 

$$
f (\lambda) = \sum_ {i = 1} ^ {r} \left(\frac {\sigma_ {i i} c _ {i}}{\sigma_ {i i} ^ {2} + \lambda}\right) ^ {2}
$$

Here, $c _ { i }$ is the ith component of $Q ^ { T } { \bar { b } } .$ 

26. Pseudoinverse properties: Show using SVD that $A A ^ { + } A = A$ and $A ^ { + } A A ^ { + } = A ^ { + }$ Also show using SVD that $A A ^ { + }$ is a symmetric and idempotent matrix (which is an alternative definition of a projection matrix). 

27. Compute the compact SVD of the matrix A along with the Moore-Penrose pseudoinverse: 

$$
A = \left[ \begin{array}{c c c} 2 & 1 & 3 \\ 1 & 2 & 0 \end{array} \right]
$$

28. Generalized singular value decomposition: The generalized singular value de composition of an $n \times d$ matrix D is given by ${ \cal D } = { \cal Q } \bar { \Sigma } { \cal P } ^ { T }$ , where $Q ^ { \stackrel { \smile } { T } } S _ { 1 } Q = I$ and 

$P ^ { T } S _ { 2 } P = I$ . Here, $S _ { 1 }$ and $S _ { 2 }$ are (given) $n \times n$ and $d \times d$ positive definite matrices, and therefore the singular vectors in Q and P are orthogonal from the perspective of the generalized definition of inner products. Show how to reduce generalized singular value decomposition to a singular value decomposition on a modified version of D. [Hint: Pre-multiply and post-multiply D with appropriate square-root matrices.] 