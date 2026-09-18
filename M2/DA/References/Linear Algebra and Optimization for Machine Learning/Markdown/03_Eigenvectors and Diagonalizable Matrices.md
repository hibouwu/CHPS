Chapter 3 

# Eigenvectors and Diagonalizable Matrices

“Mathematics is the art of giving the same name to different things.” – Henri Poincare 

## 3.1 Introduction

Any square matrix A of size $d \times d$ can be considered a linear operator, which maps the d-dimensional column vector $\textstyle { \overline { { x } } }$ to the d-dimensional vector Ax. A linear transformation Ax is a combination of operations such as rotations, reflections, and scalings of a vector x. 

A diagonalizable matrix is a special type of linear operator that only corresponds to a simultaneous scaling along d different directions. These d different directions are referred to as eigenvectors and the d scale factors are referred to as eigenvalues. All such matrices can be decomposed using an invertible $d \times d$ matrix V and a diagonal d d matrix $\Delta$ : 

$$
A = V \Delta V ^ {- 1}
$$

The columns of V contain d eigenvectors and the diagonal entries of $\Delta$ contain the eigenvalues. For any $\overline { { x } } \in \mathcal { R } ^ { d }$ , one can geometrically interpret A x using the decomposition in terms of a sequence of three transformations: (i) Multiplication of x with $V ^ { - 1 }$ computes the coordinates of $\scriptstyle { \overline { { x } } }$ in a (possibly non-orthogonal) basis system corresponding to the columns (eigenvectors) of V, (ii) multiplication of $V ^ { - 1 } \overline { { x } }$ with $\Delta$ to create $\Delta V ^ { - 1 } \overline { { x } }$ dilates these coordinates with scale factors in $\Delta$ in the eigenvector directions, and (iii) final multiplication with $V$ to create $V \Delta V ^ { - 1 } \overline { { x } }$ transforms the coordinates back to the original basis system $( { \mathrm { i . e . } }$ the standard basis). The overall result is an anisotropic scaling in d eigenvector directions. Linear transformations that can be represented in this way correspond to diagonalizable matrices. A d d diagonalizable matrix represents a linear transformation corresponding to anisotropic scaling in d linearly independent directions. 

When the columns of matrix V are orthonormal vectors, we have $V ^ { - 1 } = V ^ { T }$ . In such a case, the scaling is done along mutually orthogonal directions, and the matrix A is always symmetric. This is because we have $A ^ { T } = V \Delta ^ { T } V ^ { T } = V \Delta V ^ { T } = A$ . The two cases of anisotropic scaling with orthogonal basis systems and non-orthogonal basis systems are shown in Figure 3.1. Here, the scale factors in the two directions are 0.5 and 1, which correspond to contraction and dilation, respectively. 

![image](<Images/03_Eigenvectors_and_Diagonalizable_Matrices_image_001.jpg>)



Figure 3.1: Examples of transformations caused by diagonal matrices. The transformation on the left occurs when the matrix A is symmetric


This chapter studies the properties of eigenvectors, diagonalizable matrices, and their applications. The concept of determinant is introduced in Section 3.2. The concepts of diagonalization, eigenvectors, and eigenvalues are discussed in Section 3.3. The special case of symmetric matrices is also discussed in this section. Machine learning applications and examples of symmetric matrices are given in Section 3.4. Numerical algorithms for finding eigenvectors and eigenvalues of diagonalizable matrices are discussed in Section 3.5. A summary is given in Section 3.6. 

## 3.2 Determinants

Imagine a scatter plot of n coordinate vectors $\overline { { x } } _ { 1 } \ldots \overline { { x } } _ { n } \in \mathcal { R } ^ { d }$ , which corresponds to the outline of a d-dimensional object. Multiplying these vectors with a d d matrix A to create the vectors $A { \overline { { x } } } _ { 1 } \ldots A { \overline { { x } } } _ { n }$ will result in a distortion of the object. When the matrix A is diagonalizable, this distortion is fully described by anisotropic scaling, which affects the “volume” of the object. How can one determine the scale factors of the transformation implied by multiplication with a matrix? To do so, one must first obtain some notion of the effect of a linear transformation on the volume of an object. This is achieved by the notion of the determinant of a square matrix, which can be viewed as a quantification of its “volume.” A rather loose but intuitive definition of the determinant is as follows: 

Definition 3.2.1 (Determinant: Geometric View) The determinant of a d d matrix is the (signed) volume of the d-dimensional parallelepiped defined by its row (or column) vectors. 

The determinant of a matrix A is denoted by det(A). The above definition is self-consistent because the volume defined by the row vectors and the volume defined by the column vectors of a square matrix can be mathematically shown to be the same. This definition is, however, incomplete because it does not define the sign of det(A). The sign of the determinant tells us about the effect of multiplication by A on the orientation of the basis system. For example, a Householder reflection matrix always has a determinant of 1 because it changes the orientation of the vectors it transforms. It is noteworthy that multiplying an $n \times 2$ data matrix containing the 2-dimensional scatter plot of a right hand (in its rows) with a $2 \times 2$ reflection matrix will change the scatter plot to that of a left hand. The sign of the determinant keeps track of this orientation effect of the linear transformation. The geometric view of useful because it provides us an intuitive idea of what the determinant actually computes in terms of absolute values. Consider the following two matrices: 

![image](<Images/03_Eigenvectors_and_Diagonalizable_Matrices_image_002.jpg>)


![image](<Images/03_Eigenvectors_and_Diagonalizable_Matrices_image_003.jpg>)



b) Non-orthogonal rows (Second row modified to [1,1,0])



Figure 3.2: Parallelepipeds before and after a row operation on the $3 \times 3$ identity matrix


$$
A = \left[ \begin{array}{l l l} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{array} \right], B = \left[ \begin{array}{l l l} 1 & 0 & 0 \\ 1 & 1 & 0 \\ 0 & 0 & 1 \end{array} \right]\tag{3.1}
$$

The parallelepipeds formed by the rows of each matrix are shown in Figure $3 . 2 ( \mathrm { a } )$ and (b), respectively. The determinant of both matrices can be shown to be 1, and both parallelepipeds have a base area of 1 and a height of 1. The first of these matrices is simply the identity matrix, which is an orthogonal matrix. An orthogonal matrix always forms a unit hypercube, and so the absolute value of its determinant is always 1. 

A matrix needs to be non-singular (i.e., invertible) in order for the determinant to be non-zero. For example, if we have a $3 \times 3$ matrix that has a rank of 2, then all three row vectors must lie on a 2-dimensional plane. Therefore, the parallelepiped formed by these three row vectors cannot have a non-zero 3-dimensional volume. The determinant of the $d \times d$ matrix A can also be defined in terms of $( d - 1 ) \times ( d - 1 )$ submatrices of A: 

Definition 3.2.2 (Determinant: Recursive View) Let $A = \left[ a _ { i j } \right]$ be a d d matrix and $A _ { i j }$ be the $( d - 1 ) \times ( d - 1 )$ matrix formed by dropping the ith row and jth column, while maintaining the relative ordering of retained rows and columns. The determinant $d e t ( A )$ is recursively defined as follows: 

1. If A is $a \textnormal { 1 } \times 1$ matrix, its determinant is equal to the single scalar inside it. 

2. If A is larger than $a \times 1 \times 1$ matrix, its determinant is given by the following expression for any fixed value of $j \in \{ 1 \ldots d \}$ 

$$
\det (A) = \sum_ {i = 1} ^ {d} (- 1) ^ {(i + j)} a _ {i j} \det (A _ {i j}) [ F i x e d c o l u m n j ]\tag{3.2}
$$

The above computation fixes a column $j ,$ , and then expands using all the elements of that column. Any choice of $j$ will yield the same determinant. It is also possible to fix a row i and expand along that row: 

$$
\det (A) = \sum_ {j = 1} ^ {d} (- 1) ^ {(i + j)} a _ {i j} \det (A _ {i j}) [ \text { Fixed   row } i ]\tag{3.3}
$$

The recursive definition implies that some matrices have easily computable determinants: 

Diagonal matrix: The determinant of a diagonal matrix is the product of its diagonal entries. 

Triangular matrix: The determinant of a triangular matrix is the product of its diagonal entries. 

A matrix containing a row (or column) of 0s will have a determinant of 0. 

Consider the following matrix: 

$$
A = \left[ \begin{array}{c c} a & b \\ c & d \end{array} \right]\tag{3.4}
$$

Using the above rule, the determinant of A can be shown to be $a d - b c$ by expanding along the first column. Now, let us consider the slightly larger matrix: 

$$
A = \left[ \begin{array}{l l l} a & b & c \\ d & e & f \\ g & h & i \end{array} \right]\tag{3.5}
$$

In this case, we can expand along the first column to obtain the following: 

$$
\begin{array}{l} \det (A) = a \cdot \det \left[ \begin{array}{c c} e & f \\ h & i \end{array} \right] - d \cdot \det \left[ \begin{array}{c c} b & c \\ h & i \end{array} \right] + g \cdot \det \left[ \begin{array}{c c} b & c \\ e & f \end{array} \right] \\ = a (e i - h f) - d (b i - h c) + g (b f - e c) \\ = a e i - a h f - d b i + d h c + g b f - g e c \end{array}
$$

An immediate observation is that the determinant contains $3 ! = 6$ terms, which is the number of possible ways in which three elements can be permuted. In fact, this perspective provides a permutation-centric definition of the determinant, which is also referred to as the Leibniz formula: 

Definition 3.2.3 (Determinant: Explicit Formula) Consider a d d matrix $A = [ a _ { i j } ]$ and let Σ be the set of all d! permutations of $\{ 1 \ldots d \}$ . In other words, for each $\sigma =$ $\sigma _ { 1 } \sigma _ { 2 } \ldots \sigma _ { d } \in \Sigma$ , the value of $\sigma _ { i }$ is a permuted integer from $\{ 1 \ldots d \}$ . The sign value (denoted by sgn(σ)) of a permutation $\sigma \in \Sigma \ i s \ { + } 1$ , if the permutation can be reached from $\{ 1 \ldots d \}$ with an even number of element interchanges and it $i s - 1$ otherwise. Then, the determinant of A is defined as follows: 

$$
d e t (A) = \sum_ {\sigma \in \Sigma} \left(s g n (\sigma) \prod_ {i = 1} ^ {d} a _ {i \sigma_ {i}}\right)\tag{3.6}
$$

The permutation-centric definition of a determinant is the most direct one, although it is difficult to use computationally, and it is not particularly intuitive. 

Problem 3.2.1 Suppose that you have a d d matrix A, which is not invertible. Provide an informal argument with the geometric view of determinants, as to why addition of i.i.d. Gaussian noise with variance λ to each entry of the matrix A will almost certainly make it invertible. 

## Useful Properties of Determinants

The recursive and geometric definitions of the determinant imply the following properties: 

1. Switching two rows (or columns) of a matrix A flips the sign of the determinant. 

2. The determinant of a matrix is the same as that of its transpose. 

$$
\det (A) = \det (A ^ {T})\tag{3.7}
$$

3. A matrix with two identical rows has a determinant of 0. This also means that adding or subtracting the multiple of row $j$ of the matrix from row i and using the result to replace row i does not change the determinant. Note that we are “shearing” the parallelepiped in the 2-dimensional plane defined by rows i and $j$ (as in Figure 3.2) without changing its volume. 

4. Multiplying a single row of the matrix A with c to create the new matrix $A ^ { \prime }$ results in multiplication of the determinant of A by a factor of $c$ (because we are scaling the volume of the matrix parallelepiped by c). 

$$
\det (A ^ {\prime}) = c \cdot \det (A)\tag{3.8}
$$

A natural corollary of the above result is that multiplying the entire $d \times d$ matrix by c scales its determinant by $c ^ { d }$ 

5. The determinant of a matrix A is non-zero only if the matrix is non-singular (i.e., invertible). Geometrically, a parallelepiped of linearly dependent vectors lies in a lower dimensional plane with zero volume. 

These results can also be used to derive an important product-wise property of determinants. 

Lemma 3.2.1 The determinant of the product of two matrices A and B is the product of their determinants: 

$$
d e t (A B) = d e t (A) \cdot d e t (B)\tag{3.9}
$$

Proof: Consider two matrices A and B. One can apply the same elementary row addition and interchange operations on A and AB to create matrices $A ^ { \prime }$ and $[ A B ] ^ { \prime }$ while maintaining $A ^ { \prime } B = [ A B ] ^ { \prime }$ . Furthermore, one can apply the same elementary column operations on $B$ and 

AB to create matrices $B ^ { \prime }$ and $[ A B ] ^ { \prime }$ while maintaining $A B ^ { \prime } = [ A B ] ^ { \prime }$ . Performing a row ad dition operation on A or a column addition operation on B has no effect on det(A) det(B), and there is also no effect on $\operatorname* { d e t } ( A B )$ when the same row/column operation is performed on $A B$ . Performing a row interchange on A or a column interchange on B has the same negation effect on det $( A ) \cdot \operatorname* { d e t } ( B )$ as on det $( A B )$ when the same operation is performed on $A B$ . By using row addition/interchange operations on $A$ and column addition/interchange operations on $B ,$ , one can obtain upper-triangular matrices $A ^ { \prime }$ and $B ^ { \prime }$ (see Chapter 2). Note that $A ^ { \prime } B ^ { \prime }$ is also upper-triangular since the product of two upper-triangular matrices is up per triangular. Furthermore, each diagonal entry of $A ^ { \prime } B ^ { \prime }$ is the product of the corresponding diagonal entries of $A ^ { \prime }$ and $B ^ { \prime }$ . Since the determinant of an upper-triangular matrix is equal to the product of its diagonal entries, it is easy to show that the product of the determinants of $A ^ { \prime }$ and $B ^ { \prime }$ is equal to the determinant of $A ^ { \prime } B ^ { \prime }$ . The same result, therefore, holds for A, B, and AB, since the sequence of row and column operations to obtain $A ^ { \prime } B ^ { \prime }$ from AB is the same as the concatenation of the sequence of row operations on A and column operations on $B$ to obtain $A ^ { \prime }$ and $B ^ { \prime }$ , respectively. As we have already discussed, each of these operations has the same effect on det $( A ) \cdot \operatorname* { d e t } ( B )$ as on det $( A B )$ . The result follows. ll 1. 

A corollary of this result is that the determinant of the inverse of a matrix is the inverse of its determinant: 

$$
\det (A ^ {- 1}) = \frac {\det (I)}{\det (A)} = \frac {1}{\det (A)}\tag{3.10}
$$

The product-wise property of determinants can be geometrically interpreted in terms of parallelepiped volumes: 

1. Multiplying matrix A with matrix B (in any order) always scales up the (parallelepiped) volume of B with the volume of A. Therefore, even though $A B \ne B A$ (in general), their volumes are always the same. 

2. Multiplying matrix A with a diagonal matrix with values $\lambda _ { 1 } \ldots \lambda _ { d }$ along the diagonal scales up the volume of A with $\lambda _ { 1 } \lambda _ { 2 } \ldots \lambda _ { d }$ . This is not particularly surprising because we are stretching the axes with these factors, which explains the nature of the scaling of the volume of the underlying parallelepiped. 

3. Multiplying A with a rotation matrix simply rotates the parallelepiped, and it does not change the determinant of the matrix. 

4. Reflecting a parallelepiped to its mirror image changes its sign without changing its volume. The sign of the determinant tells us a key fact about the orientation of the data created using multiplicative transformation with A. For example, consider an $n \times 2$ data set D containing the 2-dimensional scatter plot of a right hand in its rows. A negative determinant of a $2 \times 2$ matrix A means that multiplicative transformation of the $n \times 2$ data set D with A will result in a scatter plot of a right hand in D changing into that of a (possibly stretched and rotated) left hand in $D A$ 

5. Since all linear transformations are combinations of rotations, reflections, and scaling (see Chapter 7), one can compute the absolute effect of a linear transformation on the determinant by focusing only on the scaling portions of the transformation. 

The product-wise property of determinants is particularly useful for matrices with special structure. For example, an orthogonal matrix satisfies $A ^ { T } A = I$ , and therefore we have det $( A ) \mathrm { d e t } ( A ^ { T } ) = \mathrm { d e t } ( I ) = 1$ . Since the determinants of A and $A ^ { T }$ are equal, it follows that the square of the determinant of A is 1. 

Lemma 3.2.2 The determinant of an orthogonal matrix is either +1 or 1. 

One can use this result to simplify the determinant computation of a matrix with various types of decompositions containing orthogonal matrices. 

Problem 3.2.2 Consider a d  d matrix A that is decomposed into the form $A = Q \Sigma P ^ { T }$ where Q and P are d d orthonormal matrices, and Σ is a d d diagonal matrix containing the nonnegative values $\sigma _ { 1 } \ldots \sigma _ { d }$ . What is the absolute value of the determinant of A. Can the sign of the determinant be negative? Why or why not? Does the answer to any of the questions change when $Q = P \mathscr { ? }$ 

Problem 3.2.3 (Restricted Affine Property of Determinants) Consider two matrices A and B, which differ in exactly one row (say, the ith row). Show that for any scalar λ, we have det $( \lambda A + [ 1 - \lambda ] B ) = \lambda d e t ( A ) + [ 1 - \lambda ] d e t ( B )$ 

A hint for solving the above problem is to use the recursive definition of determinants. 

Problem 3.2.4 Work out the determinants of all the elementary row operator matrices introduced in Chapter 1. 

Problem 3.2.5 How can one compute the determinant from the QR decomposition or the LU decomposition of a square matrix. 

Problem 3.2.6 Consider a d d square matrix A such that $A = - A ^ { T }$ . Use the properties of determinants to show that if d is odd, then the matrix is singular. 

Problem 3.2.7 Suppose that you have a d d matrix in which the absolute value of every entry is no greater than 1. Show that the absolute value of the determinant is no greater than $( d ) ^ { d / 2 }$ . Provide an example of a $2 \times 2$ matrix in which the determinant is equal to this upper bound. [Hint: Think about the geometric view of determinants.] 

## 3.3 Diagonalizable Transformations and Eigenvectors

We will first define the notion of eigenvectors formally: 

Definition 3.3.1 (Eigenvectors and Eigenvalues) A d-dimensional column vector x is said to be an eigenvector of d d matrix A, if the following relationship is satisfied for some scalar λ: 

$$
A \overline {{x}} = \lambda \overline {{x}}\tag{3.11}
$$

The scalar λ is referred to as its eigenvalue. 

An eigenvector can be viewed as “stretching direction” of the matrix, where multiplying the vector with the matrix simply stretches the former. For example, the vectors $[ 1 , 1 ] ^ { T }$ and $[ 1 , - 1 ] ^ { T }$ are eigenvectors of the following matrix with eigenvalues 3 and 1, respectively: 

$$
{\left[ \begin{array}{l l} 1 & 2 \\ 2 & 1 \end{array} \right]} {\left[ \begin{array}{l} 1 \\ 1 \end{array} \right]} = 3 {\left[ \begin{array}{l} 1 \\ 1 \end{array} \right]}, {\left[ \begin{array}{l l} 1 & 2 \\ 2 & 1 \end{array} \right]} {\left[ \begin{array}{l} 1 \\ - 1 \end{array} \right]} = - 1 {\left[ \begin{array}{l} 1 \\ - 1 \end{array} \right]}
$$

Each member of the standard basis is an eigenvector of the diagonal matrix, with eigenvalue equal to the ith diagonal entry. All vectors are eigenvectors of the identity matrix. 

The number of eigenvectors of a $d \times d$ matrix A may vary, but only diagonalizable matrices represent anisotropic scaling in d linearly independent directions; therefore, we need to be able to find d linearly independent eigenvectors. Let $\overline { { v } } _ { 1 } \ldots \overline { { v } } _ { d }$ be d linearly independent eigenvectors and $\lambda _ { 1 } \ldots \lambda _ { d }$ be the corresponding eigenvalues. Therefore, the eigenvector condition holds in each case: 

$$
A \overline {{v}} _ {i} = \lambda_ {i} \overline {{v}} _ {i}, \quad \forall i \in \{1 \dots d \}\tag{3.12}
$$

One can rewrite this condition in matrix form: 

$$
A [ \overline {{v}} _ {1} \dots \overline {{v}} _ {d} ] = [ \lambda_ {1} \overline {{v}} _ {1} \dots \lambda_ {d} \overline {{v}} _ {d} ]\tag{3.13}
$$

By defining $V$ to be $\textmd { i d } \times d$ matrix containing $\overline { { v } } _ { 1 } \ldots \overline { { v } } _ { d }$ in its columns, and $\Delta$ to be a diagonal matrix containing $\lambda _ { 1 } \ldots \lambda _ { d }$ along the diagonal, one can rewrite Equation 3.13 as follows: 

$$
A V = V \Delta\tag{3.14}
$$

Post-nultiplying with $V ^ { - 1 }$ , we obtain the diagonalization of the matrix $A { : }$ 

$$
A = V \Delta V ^ {- 1}\tag{3.15}
$$

Note that V is an invertible $d \times d$ matrix containing linearly independent eigenvectors, and $\Delta$ is a $d \times d$ diagonal matrix, whose diagonal elements contain the eigenvalues of A. The matrix V is also referred to as a basis change matrix, because it tells us that the linear transformation A is a diagonal matrix $\Delta$ after changing the basis to the columns of V. 

The determinant of a diagonalizable matrix is defined by the product of its eigenval ues. Since diagonalizable matrices represent linear transforms corresponding to anisotropic scaling in arbitrary directions, a diagonalizable transform should scale up the volume of an object by the product of these scaling factors. It is helpful to think of the matrix A in terms of the transform it performs on the unit parallelepiped corresponding to the orthonormal columns of the identity matrix: 

$$
A = A I
$$

The transformation scales this unit parallelepiped with scaling factors $\lambda _ { 1 } \ldots \lambda _ { d }$ in d directions. The ith scaling multiplies the volume of the parallelepiped by $\lambda _ { i }$ . As a result, the final volume of the parallelepiped defined by the identity matrix (after all the scalings) is the product of $\lambda _ { 1 } \ldots \lambda _ { d }$ . This intuition provides the following result: 

Lemma 3.3.1 The determinant of a diagonalizable matrix is equal to the product of its eigenvalues. 

Proof: Let A be a $d \times d$ matrix with the following diagonalization: 

$$
A = V \Delta V ^ {- 1}\tag{3.16}
$$

By taking the determinant of both sides, we obtain the following: 

$$
\begin{array}{r l} \det (A) = \det (V \Delta V ^ {- 1}) = \det (V) \det (\Delta) \det (V ^ {- 1}) & [ \text {Productwise Property} ] \\ = \det (\Delta) [ \text {Since} \det (V ^ {- 1}) = 1 / \det (V) ] \end{array}
$$

Since the determinant of a diagonal matrix is equal to the product of its diagonal entries, the result follows. 

The presence of a zero eigenvalue implies that the matrix A is singular because its deter minant is zero. One can also infer this fact from the observation that the corresponding eigenvector $\overline { { v } }$ satisfies $A { \overline { { v } } } = { \overline { { 0 } } }$ . In other words, the matrix A is not of full rank because its null space is nonempty. A nonsingular, diagonalizable matrix can be inverted easily according to the following relationship: 

$$
(V \Delta V ^ {- 1}) ^ {- 1} = V \Delta^ {- 1} V ^ {- 1}\tag{3.17}
$$

Note that $\Delta ^ { - 1 }$ can be obtained by replacing each eigenvalue in the diagonal of $\Delta$ with its reciprocal. Matrices with zero eigenvalues cannot be inverted; the reciprocal of zero is not defined. 

Problem 3.3.1 Let A be a square, diagonalizable matrix. Consider a situation in which we add α to each diagonal entry of A to create $A ^ { \prime }$ . Show that $A ^ { \prime }$ has the same eigenvectors as $A _ { i }$ , and its eigenvalues are related to A by a difference of α. 

It is noteworthy that the ith eigenvector $\overline { { v } } _ { i }$ belongs to the null space of $A - \lambda _ { i } I$ because $( A - \lambda _ { i } I ) { \overline { { v } } } _ { i } = 0$ . In other words, the determinant of $A - \lambda _ { i } I$ must be zero. This polynomial expression that yields the eigenvalue roots is referred to as the characteristic polynomial of A. 

Definition 3.3.2 (Characteristic Polynomial) The characteristic polynomial of a $d { \times } d$ matrix A is the degree-d polynomial in λ obtained by expanding $d e t ( A - \lambda I )$ 

Note that this is a degree-d polynomial, which always has d roots (including repeated or complex roots) according to the fundamental theorem of algebra. The d roots of the characteristic polynomial of any $d \times d$ matrix are its eigenvalues. 

Observation 3.3.1 The characteristic polynomial $f ( \lambda )$ of $d \times d$ matrix A is a polynomial in λ of the following form, where $\lambda _ { 1 } \ldots \lambda _ { d }$ are eigenvalues of A: 

$$
d e t (A - \lambda I) = (\lambda_ {1} - \lambda) (\lambda_ {2} - \lambda) \dots (\lambda_ {d} - \lambda)\tag{3.18}
$$

Therefore, the eigenvalues and eigenvectors of a matrix A can be computed as follows: 

1. The eigenvalues of A can be computed by expanding det $( A - \lambda I )$ as a polynomial expression in $\lambda ,$ setting it to zero, and solving for λ. 

2. For each root $\lambda _ { i }$ of this polynomial, we solve the system of equations $( A - \lambda _ { i } I ) { \overline { { v } } } = 0$ in order to obtain one or more eigenvectors. The linearly independent eigenvectors with eigenvalue $\lambda _ { i }$ , therefore, define a basis of the right null space of $\left( A - \lambda _ { i } I \right)$ 

The characteristic polynomial of the $d \times d$ identity matrix is $( 1 - \lambda ) ^ { d }$ . This is consistent with the fact that an identity matrix has d repeated eigenvalues of 1, and every d-dimensional vector is an eigenvector belonging to the null space of $A - \lambda I$ . As another example, consider the following matrix: 

$$
B = \left[ \begin{array}{l l} 1 & 2 \\ 2 & 1 \end{array} \right]\tag{3.19}
$$

Then, the matrix $B - \lambda I$ can be written as follows: 

$$
B - \lambda I = \left[ \begin{array}{c c} 1 - \lambda & 2 \\ 2 & 1 - \lambda \end{array} \right]\tag{3.20}
$$

The determinant of the above expression $( 1 - \lambda ) ^ { 2 } - 4 = \lambda ^ { 2 } - 2 \lambda - 3$ , which is equivalent to $( 3 - \lambda ) ( - 1 - \lambda )$ . By setting this expression to zero, we obtain eigenvalues of 3 and 1, respectively. The corresponding eigenvectors are $[ 1 , 1 ] ^ { T }$ and $[ 1 , - 1 ] ^ { T }$ , respectively, which can be obtained from the null-spaces of each $\left( A - \lambda _ { i } I \right)$ 

We need to diagonalize B as $V \Delta V ^ { - 1 }$ . The matrix V can be constructed by stacking the eigenvectors in columns. The normalization of columns is not unique, although choosing V to have unit columns (which results in $V ^ { - 1 }$ having unit rows) is a common practice. One can then construct the diagonalization $B = V \Delta V ^ { - 1 }$ as follows: 

$$
B = \left[ \begin{array}{c c} 1 / \sqrt {2} & 1 / \sqrt {2} \\ 1 / \sqrt {2} & - 1 / \sqrt {2} \end{array} \right] \left[ \begin{array}{c c} 3 & 0 \\ 0 & - 1 \end{array} \right] \left[ \begin{array}{c c} 1 / \sqrt {2} & 1 / \sqrt {2} \\ 1 / \sqrt {2} & - 1 / \sqrt {2} \end{array} \right]
$$

Problem 3.3.2 Find the eigenvectors, eigenvalues, and a diagonalization of each of the following matrices: 

$$
A = \left[ \begin{array}{r r} 1 & 0 \\ - 1 & 2 \end{array} \right], \quad B = \left[ \begin{array}{r r} 1 & 1 \\ - 2 & 4 \end{array} \right]
$$

Problem 3.3.3 Consider a d d matrix A such that $A = - A ^ { T }$ . Show that all non-zero eigenvalues would need to occur in pairs, such that one member of the pair is the negative of the other. 

One can compute a polynomial of a square matrix A in the same way as one computes the polynomial of a scalar — the main differences are that non-zero powers of the scalar are replaced with powers of A and that the scalar term c in the polynomial is replaced by $c I .$ When one computes the characteristic polynomial in terms of its matrix, one always obtains the zero matrix! For example, if the matrix B is substituted in the aforementioned characteristic polynomial $\lambda ^ { 2 } - 2 \lambda - 3$ , we obtain the matrix $B ^ { 2 } - 2 B - 3 I$ : 

$$
B ^ {2} - 2 B - 3 I = {\left[ \begin{array}{l l} 5 & 4 \\ 4 & 5 \end{array} \right]} - 2 {\left[ \begin{array}{l l} 1 & 2 \\ 2 & 1 \end{array} \right]} - 3 {\left[ \begin{array}{l l} 1 & 0 \\ 0 & 1 \end{array} \right]} = 0
$$

This result is referred to as the Cayley-Hamilton theorem, and it is true for all matrices whether they are diagonalizable or not. 

Lemma 3.3.2 (Cayley-Hamilton Theorem) Let A be any matrix with characteristic polynomial $f ( \lambda ) = d e t ( A - \lambda I )$ . Then, $f ( A )$ evaluates to the zero matrix. 

The Cayley-Hamilton theorem is true in general for any square matrix A, but it can be proved more easily in some special cases. For example, when A is diagonalizable, it is easy to show the following for any polynomial function $f ( \dot { ) }$ 

$$
f (A) = V f (\Delta) V ^ {- 1}
$$

Applying a polynomial function to a diagonal matrix is equivalent to applying a polynomial function to each diagonal entry (eigenvalue). Applying the characteristic polynomial to an eigenvalue will yield 0. Therefore, $f ( \Delta )$ is a zero matrix, which implies that $f ( A )$ is a zero matrix. One interesting consequence of the Cayley-Hamilton theorem is that the inverse of a non-singular matrix can always be expressed as a polynomial of degree $( d - 1 ) !$ 

Lemma 3.3.3 (Polynomial Representation of Matrix Inverse) The inverse of an invertible $d \times d$ matrix A can be expressed as a polynomial of A of degree at most $( d - 1 )$ 

Proof: The constant term in the characteristic polynomial is the product of the eigenvalues, which is non-zero in the case of nonsingular matrices. Therefore, only in the case of nonsingular matrices, we can write the Cayley-Hamilton matrix polynomial $f ( A )$ in the form $f ( A ) = A [ g ( A ) ] + c I$ for some scalar constant $c \neq 0$ and matrix polynomial $g ( A )$ of degree $( d - 1 )$ . Since the Cayley-Hamilton polynomial $f ( A )$ evaluates to zero, we can rearrange the expression above to obtain A [ g(A)/c] = I. ■ 

$$
A \underbrace {\left[ - g (A) / c \right]} _ {A ^ {- 1}} = I.
$$

Problem 3.3.4 Show that any matrix polynomial of a $d \times d$ matrix can always be reduced to a matrix polynomial of degree at most $( d - 1 )$ 

The above lemma explains why the inverse shows many special properties $( \mathrm { e . g . }$ , commutativity of multiplication with inverse) shown by matrix polynomials. Similarly, both polynomials and inverses of triangular matrices are triangular. Triangular matrices contain eigenvalues on the main diagonal. 

Lemma 3.3.4 Let A be a d d triangular matrix. Then, the entries $\lambda _ { 1 } \ldots \lambda _ { d }$ on its main diagonal are its eigenvalues. 

Proof: Since $A - \lambda _ { i } I$ is singular for any eigenvalue $\lambda _ { i }$ , it follows that at least one of the diagonal values of the triangular matrix $A - \lambda _ { i } I$ must be zero. This can only occur if $\lambda _ { i }$ is a diagonal entry of A. The converse can be shown similarly. 

## 3.3.1 Complex Eigenvalues

It is possible for the characteristic polynomial of a matrix to have complex roots. In such a case, a real-valued matrix might be diagonalizable with complex eigenvectors/eigenvalues. Consider the case of the rotation transform, which is not diagonalizable with real eigenval ues. After all, it is hard to imagine a real-valued eigenvector that when transformed with $\textrm { a } 9 0 ^ { \circ }$ rotation would point in the same direction as the original vector. However, this is indeed possible when working in complex fields! The key point is that multiplication with the imaginary number i rotates a complex vector to an orthogonal orientation. One can verify that the complex vector ${ \overline { { u } } } = { \overline { { a } } } + i { \overline { { b } } }$ is always orthogonal to the vector ${ \overline { { v } } } = i [ { \overline { { a } } } + i { \overline { { b } } } ]$ using the definition of complex inner products (cf. Section 2.11 of Chapter 2). 

Consider the following $9 0 °$ rotation matrix of column vectors: 

$$
A = \left[ \begin{array}{c c} \cos (9 0) & - \sin (9 0) \\ \sin (9 0) & \cos (9 0) \end{array} \right] = \left[ \begin{array}{c c} 0 & - 1 \\ 1 & 0 \end{array} \right]
$$

The characteristic polynomial of A is $( \lambda ^ { 2 } + 1 )$ , which does not have any real-valued roots. The two complex roots of the polynomial are i and i. The corresponding eigenvectors are $[ - i , 1 ] ^ { T }$ and $[ i , 1 ] ^ { T }$ , respectively, and these eigenvectors can be found by solving the linear systems $( A - i I ) { \overline { { x } } } = 0$ and $( A + i I ) { \overline { { x } } } = 0$ . Solving a system of linear equations on a complex field of coefficients is fundamentally not different from how it is done in the real domain. We verify that the corresponding eigenvectors satisfy the eigenvalue scaling condition: 

$$
\left[ \begin{array}{c c} 0 & - 1 \\ 1 & 0 \end{array} \right] \left[ \begin{array}{c} - i \\ 1 \end{array} \right] = - i \left[ \begin{array}{c} - i \\ 1 \end{array} \right], \quad \left[ \begin{array}{c c} 0 & - 1 \\ 1 & 0 \end{array} \right] \left[ \begin{array}{c} i \\ 1 \end{array} \right] = i \left[ \begin{array}{c} i \\ 1 \end{array} \right]
$$

Each eigenvector is rotated by $9 0 ^ { \circ }$ because of multiplication with i or i. One can then put these eigenvectors (after normalization) in the columns of $V$ , and compute the matrix $V ^ { - 1 }$ which is also a complex matrix. The resulting diagonalization of A is as follows: 

$$
A = V \Delta V ^ {- 1} = \left[ \begin{array}{c c} - i / \sqrt {2} & i / \sqrt {2} \\ 1 / \sqrt {2} & 1 / \sqrt {2} \end{array} \right] \left[ \begin{array}{c c} - i & 0 \\ 0 & i \end{array} \right] \left[ \begin{array}{c c} i / \sqrt {2} & 1 / \sqrt {2} \\ - i / \sqrt {2} & 1 / \sqrt {2} \end{array} \right]
$$

It is evident that the use of complex numbers greatly extends the family of matrices that can be diagonalized. In fact, one can write the family of $2 \times 2$ rotation matrices at an angle θ (in radians) as follows: 

$$
\left[ \begin{array}{c c} \cos (\theta) & - \sin (\theta) \\ \sin (\theta) & \cos (\theta) \end{array} \right] = \left[ \begin{array}{c c} - i / \sqrt {2} & i / \sqrt {2} \\ 1 / \sqrt {2} & 1 / \sqrt {2} \end{array} \right] \left[ \begin{array}{c c} e ^ {- i \theta} & 0 \\ 0 & e ^ {i \theta} \end{array} \right] \left[ \begin{array}{c c} i / \sqrt {2} & 1 / \sqrt {2} \\ - i / \sqrt {2} & 1 / \sqrt {2} \end{array} \right]\tag{3.21}
$$

From Euler’s formula, it is known that $e ^ { i \theta } = \cos ( \theta ) + i \sin ( \theta )$ . It seems geometrically intuitive that multiplying a vector with the mth power of a θ-rotation matrix should rotate the vector m times to create an overall rotation of mθ. The above diagonalization also makes it algebraically obvious that the mth power of the θ-rotation matrix yields a rotation of mθ, because the diagonal entries in the mth power become $e ^ { \pm i m \theta }$ 

Problem 3.3.5 Show that all complex eigenvalues of a real matrix must occur in conjugate pairs of the form $a + b i$ and $a - b i$ . Also show that the corresponding eigenvectors also occur in similar pairs ${ \overline { { p } } } + i { \overline { { q } } }$ and $\overline { { p } } - i \overline { { q } }$ 

## 3.3.2 Left Eigenvectors and Right Eigenvectors

Throughout this book, we have defined an eigenvector as a column vector satisfying $A { \overline { { x } } } = \lambda { \overline { { x } } }$ for some scalar λ. Such an eigenvector is a right eigenvector because x occurs on the right side of the product Ax. When a vector is referred to as an “eigenvector” without any mention of “right” or “left,” it refers to a right eigenvector by default. 

A left eigenvector is a row vector y, such that ${ \overline { { y } } } A = \lambda { \overline { { y } } }$ for some scalar λ. It is necessary for y to be a row vector for y to occur on the left-hand side of the product $\overline { { y } } A$ . It is noteworthy that (the transposed representation of) a right eigenvector of a matrix need not be a left eigenvector and vice versa, unless the matrix A is symmetric. If the matrix A is symmetric, then the left and right eigenvectors are transpositions of one another. 

Lemma 3.3.5 If a matrix A is symmetric then each of its left eigenvectors is a right eigenvector after transposing the row vector into a column vector. Similarly, transposing each right eigenvector results in a row vector that is a left eigenvector. 

Proof: Let $\overline { y }$ be a left eigenvector. Then, we have $( { \overline { { y } } } A ) ^ { T } = \lambda { \overline { { y } } } ^ { T }$ . The left-hand side can be simplified to $A ^ { T } { \overline { { y } } } ^ { T } = { \overline { { A } } } { \overline { { y } } } ^ { T }$ . Re-writing with the simplified left-hand side, we have the following: 

$$
A \overline {{y}} ^ {T} = \lambda \overline {{y}} ^ {T}\tag{3.22}
$$

Therefore, $\overline { { y } } ^ { T }$ is a right eigenvector of A. A similar approach can be used to show that eachright eigenvector is a left eigenvector after transposition. 厂

This relationship between left and right eigenvectors holds only for symmetric matrices. How about the eigenvalues? It turns out that the left eigenvalues and right eigenvalues are the same irrespective of whether or not the matrix is symmetric. This is because the characteristic polynomial in both cases is det $( A - \lambda I ) = \operatorname* { d e t } ( A ^ { T } - \lambda I )$ 

Consider a diagonalizable $d \times d$ matrix A, which can be converted to its diagonalized matrix $\Delta$ as follows: 

$$
A = V \Delta V ^ {- 1}\tag{3.23}
$$

In this case, the right eigenvectors are the d columns of the $d \times d$ matrix V. However, the left eigenvectors are the rows of the matrix $V ^ { - 1 }$ . This is because the left eigenvectors of A are the right eigenvectors of $A ^ { T }$ after transposition. Transposing A yields the following; 

$$
A ^ {T} = (V \Delta V ^ {- 1}) ^ {T} = (V ^ {- 1}) ^ {T} \Delta V ^ {T}
$$

In other words, the right eigenvectors of $A ^ { T }$ are the columns of $( V ^ { - 1 } ) ^ { T }$ , which are the transposed rows of $V ^ { - \bar { 1 } }$ 

Problem 3.3.6 The right eigenvectors of a diagonalizable matrix $A = V \Delta V ^ { - 1 }$ are columns of V, whereas the left eigenvectors are rows of $\bar { V } ^ { - 1 }$ . Use this fact to infer the relationships between left and right eigenvectors of a diagonalizable matrix. 

## 3.3.3 Existence and Uniqueness of Diagonalization

The characteristic polynomial provides insights into the existence and uniqueness of a di agonalization. In this section, we assume that complex-valued diagonalization is allowed, although the original matrix is assumed to be real-valued. In order to perform the diag onalization, we need d linearly independent eigenvectors. We can then put the d linearly independent eigenvectors in the columns of matrix V and the eigenvalues along the diagona of $\Delta$ to perform the diagonalization $V \Delta V ^ { - 1 }$ . First, we note that the characteristic polynomial has at least one distinct root (which is possibly complex), and the minimum number of roots occurs when the same root is repeated d times. Given a root λ, the matrix $A - \lambda I$ is singular, since its determinant is 0. Therefore, we can find the vector x in the null space of $( A - \lambda I )$ ). Since this vector satisfies $( A - \lambda I ) { \overline { { x } } } = 0$ , it follows that it is an eigenvector. We summarize this result: 

Observation 3.3.2 A well-defined procedure exists for finding an eigenvector from each distinct root of the characteristic polynomial. Since the characteristic polynomial has at least one (possibly complex) root, every real matrix has at least one (possibly complex) eigenvector. 

Note that we might be able to find more than one eigenvector for an eigenvalue when the root is repeated, which is a key deciding factor in whether or not the matrix is diagonalizable. First, we show the important result that the eigenvectors belonging to distinct eigenvalues are linearly independent. 

Lemma 3.3.6 The eigenvectors belonging to distinct eigenvalues are linearly independent. 

Proof Sketch: Consider a situation where the characteristic polynomial of a $d \times d$ matrix A has $k \leq d$ distinct roots $\lambda _ { 1 } \ldots \lambda _ { k }$ . Let $\overline { { v } } _ { 1 } \ldots \overline { { v } } _ { k }$ represent eigenvectors belonging to these eigenvalues. 

Suppose that the eigenvectors are linearly dependent, and therefore we have $\begin{array} { r } { \sum _ { i = 1 } ^ { k } \alpha _ { i } \overline { { v } } _ { i } = } \end{array}$ 0 for scalars $\alpha _ { 1 } \ldots \alpha _ { k }$ (at least some of which must be non-zero). One can then pre-multiply the vector $\textstyle \sum _ { i = 1 } ^ { k } \alpha _ { i } { \overline { { v } } } _ { i }$ with the matrix $( A - \lambda _ { 2 } I ) ( A - \lambda _ { 3 } I ) \dots ( A - \lambda _ { k } I )$ in order to obtain the following: 

$$
\alpha_ {1} [ \prod_ {i = 2} ^ {k} (\lambda_ {1} - \lambda_ {i}) ] \overline {{v}} _ {1} = 0
$$

Since the eigenvalues are distinct, it follows that $\alpha _ { 1 } = 0$ . One can similarly show that each of $\alpha _ { 2 } \ldots \alpha _ { k }$ is zero. Therefore, we obtain a contradiction to our linear dependence assumption. 

In the special case that the matrix A has d distinct eigenvalues, one can construct an invertible matrix V from the eigenvectors. This makes the matrix A diagonalizable. 

Lemma 3.3.7 When the roots of the characteristic polynomial are distinct, one can find d linearly independent eigenvectors. Therefore, a (possibly complex-valued) diagonalization $A = V \Delta V ^ { - 1 }$ of a real-valued matrix A with d distinct roots always exists. 

In the case that the characteristic polynomial has distinct roots, one can not only show exis tence of a diagonalization, but we can also show that the diagonalization can be performed in an almost unique way (with possibly complex eigenvectors and eigenvalues). We use the word “almost” because one can multiply any eigenvector with any scalar, and it still remains an eigenvector with the same eigenvalue. If we scale the ith column of V by $c ,$ we can scale the ith row of $V ^ { - 1 }$ by $1 / c$ without affecting the result. Finally, one can shuffle the order of left/right eigenvectors in $V ^ { - 1 }$ , V and eigenvalues in $\Delta$ in the same way without affecting the product. By imposing a non-increasing eigenvector order, and a normalization and sign convention on the diagonalization (such as allowing only unit normalized eigenvectors in which the first non-zero component is positive), one can obtain a unique diagonalization. 

On the other hand, if the characteristic polynomial is of the form $\Pi _ { i } ( \lambda _ { i } - \lambda ) ^ { r _ { i } }$ , where at least one $r _ { i }$ is strictly greater than 1, the roots are not distinct. In such a case, the solution to $( A - \lambda _ { i } I ) \overline { { x } } = 0$ might be a vector space with dimensionality less than $r _ { i }$ . As a result, we may or may not be able to find the full set of d eigenvectors required to create the matrix V for diagonalization. 

The algebraic multiplicity of an eigenvalue $\lambda _ { i }$ is the number of times $\left( A - \lambda _ { i } I \right)$ occurs as a factor in the characteristic polynomial. For example, if A is a $d \times d$ matrix, its characteristic polynomial always contains d factors (including repetitions and complex-valued factors). We have already shown that an algebraic multiplicity of 1 for each eigenvalue is the simple case where a diagonalization exists. In the case where the algebraic multiplicities of some eigenvalues are strictly greater than 1, one of the following will occur: 

Exactly $r _ { i }$ linearly independent eigenvectors exist for each eigenvalue with algebraic multiplicity $r _ { i }$ . Any linear combination of these eigenvectors is also an eigenvector. In other words, a vector space of eigenvectors exists with rank $r _ { i }$ , and any basis of this vector space is a valid set of eigenvectors. Such a vector space corresponding to a specific eigenvalue is referred to as an eigenspace. In this case, one can perform the diagonalization $A = V \Delta V ^ { - 1 }$ by choosing the columns of V in an infinite number of possible ways as the basis vectors of all the underlying eigenspaces. 

If less that $r _ { i }$ eigenvectors exist for an eigenvalue with algebraic multiplicity $r _ { i } ,$ a diagonalization does not exist. The closest we can get to a diagonalization is the Jordan normal form (see Section 3.3.4). Such a matrix is said to be defective. 

In the first case above, it is no longer possible to have a unique diagonalization even after imposing a normalization and sign convention on the eigenvectors. 

For an eigenvalue $\lambda _ { i }$ with algebraic multiplicity $r _ { i }$ , the system of equations $( A - \lambda _ { i } I ) \overline { { x } } = 0$ might have as many as $r _ { i }$ solutions. When we have two or more distinct eigenvectors $( \mathrm { e . g . , } \overline { { v } } _ { 1 }$ and $\overline { { v } } _ { 2 } )$ for the same eigenvalue, any linear combination $\alpha \overline { { v } } _ { 1 } + \beta \overline { { v } } _ { 2 }$ will also be an eigenvector for all scalars $\alpha$ and $\beta .$ . Therefore, for creating a diagonalization $A = V \Delta V ^ { - 1 }$ , one can construct the columns of V in an infinite number of possible ways. The best example of this situation is the identity matrix in which any unit vector is an eigenvector with eigenvalue 1. One can “diagonalize” the (already diagonal) identity matrix I in an infinite number of possible ways $I = V \Delta V ^ { - 1 }$ , where $\Delta$ is identical to I and $V$ is any invertible matrix. 

Repeated eigenvalues also create the possibility that a diagonalization might not exist. This occurs when the number of linearly independent eigenvectors for an eigenvalue is less than its algebraic multiplicity. Even though the characteristic polynomial has d roots (including repetitions), one might have fewer than d eigenvectors. In such a case, the matrix is not diagonalizable. Consider the following matrix A: 

$$
A = \left[ \begin{array}{l l} 1 & 1 \\ 0 & 1 \end{array} \right]\tag{3.24}
$$

The characteristic polynomial is $( 1 - \lambda ) ^ { 2 }$ . Therefore, we obtain a single eigenvalue of $\lambda = 1$ with algebraic multiplicity of 2. However, the matrix $( A - \lambda I )$ has rank 1, and we obtain only a single eigenvector $[ 1 , 0 ] ^ { T }$ . Therefore, this matrix is not diagonalizable. Matrices containing repeated eigenvalues and missing eigenvectors of the repeated eigenvalues are not diagonalizable. The number of eigenvectors of an eigenvalue is referred to as its geometric multiplicity, which is at least 1 and at most the algebraic multiplicity. 

## 3.3.4 Existence and Uniqueness of Triangulization

Where do the “missing eigenvectors” of defective matrices go? Consider an eigenvalue with λ with multiplicity k. The characteristic polynomial only tells us that the null space of $( A - \lambda I ) ^ { k }$ has dimensionality k, but it does not guarantee this for $( A - \lambda I )$ . The key point is that the system of equations $( A - \lambda I ) ^ { k } { \overline { { x } } } = 0$ is guaranteed to have k linearly independent solutions, although the system of equations $( A - \lambda I ) { \overline { { x } } } = 0$ might have anywhere between 1 and k solutions. Can we somehow use this fact to get something close to a diagonalization? 

Let the system of equations $( A - \lambda I ) { \overline { { x } } } = 0$ have $r < k$ solutions. All the k solutions of $( A - \lambda I ) ^ { k } { \overline { { x } } } = 0$ are generalized eigenvectors and $r < k$ of them are ordinary eigenvectors. It is possible to decompose the set of k generalized eigenvectors into $r$ Jordan chains. The ith Jordan chain contains an ordered sequence of m(i) (generalized) eigenvectors out of the k eigenvectors, so that we have $\begin{array} { r } { \sum _ { i = 1 } ^ { r } m ( i ) = k } \end{array}$ . The sequence of generalized eigenvectors for the ith Jordan chain is denoted by $\overline { { v } } _ { 1 } \ldots \overline { { v } } _ { m ( i ) }$ , so that the first eigenvector $\overline { { v } } _ { 1 }$ is an ordinary eigenvector satisfying $A { \overline { { v } } } _ { 1 } ~ = ~ \lambda { \overline { { v } } } _ { 1 }$ , and the remaining satisfy the chain relation $A { \overline { { v } } } _ { j } = \lambda { \overline { { v } } } _ { j } + { \overline { { v } } } _ { j - 1 }$ for $j > 1$ . Note that these chain vectors are essentially obtained as $\overline { { v } } _ { m ( i ) - r } = ( A - \lambda I ) ^ { r } \overline { { v } } _ { m ( i ) }$ for each $r$ from 1 to $m ( i ) - 1$ . A full proof of the existence of Jordan chains is quite complex, and is omitted. 

The matrix V contains the generalized eigenvectors in its columns, with eigenvectors belonging to the same Jordan chain occurring consecutively in the same order as their chain relations, and with the ordinary eigenvector being the leftmost of this group of columns. This matrix $V$ can be used to create the Jordan normal form, which “almost” diagonalizes the matrix A with an upper-triangular matrix U: 

$$
A = V U V ^ {- 1}\tag{3.25}
$$

The upper-triangular matrix U is “almost” diagonal, and it contains diagonal entries containing eigenvalues in the same order as the corresponding generalized eigenvectors in V. In addition, at most $( d - 1 )$ entries, which are just above the diagonal, can be 0 or 1. An entry just above the diagonal is 0 if and only if the corresponding eigenvector is an ordinary eigenvector, and it is 1, if it is not an ordinary eigenvector. It is not difficult to verify that 

$A V = V U$ is the matrix representation of all the eigenvector relations (including chain relations), which implies that $A = V U V ^ { - 1 }$ . Each entry immediately above the diagonal is referred to as a super-diagonal entry. A large matrix may sometimes contain only a small number of repeated eigenvalues, and the number of non-zero entries above the diagonal is always bounded above by these repetitions. Therefore, the Jordan normal form contains a small number of super-diagonal 1s in additional to the non-zero entries on the diagonal. In the special case of diagonalizable matrices, the Jordan normal form is the diagonalization of the matrix. 

The existence of the Jordan normal form implies that all square matrices are triangulizable, although it is possible for the eigenvectors and eigenvalues to be complex even for real matrices. The triangulizability of a matrix is not unique. One can create different types of triangulizations by imposing different types of constraints on the basis vectors and the triangular matrix. For example, the Jordan normal form has a special structure of the upper-triangular matrix U, but no special structure on the basis vectors in V . Another form of triangulization is the Schur decomposition in which the basis change matrix P is orthogonal, and the upper-triangular matrix U contains the eigenvalues on the diagona with no other special properties: 

$$
A = P U P ^ {T}\tag{3.26}
$$

A Schur decomposition can be found using iterative QR decomposition, and it is one of the methods used for computing the eigenvalues of a matrix (cf. Section 3.5.1). The Schur decomposition of a symmetric matrix is the same as its diagonalization. This is because if we have $A = A ^ { T }$ , then we must have $P U P ^ { T } = P U ^ { T } P ^ { T }$ , which is the same as saying that $P ( U - U ^ { T } ) P ^ { T } = 0$ . Since P is non-singular, we must have $U = U ^ { T }$ . This is possible only when U is diagonal. A (possibly complex-valued) Schur decomposition of a real matrix always exists, although it might not be unique (just as the diagonalization is not unique). 

## Diagonalizability vs Triangulizibility: A Geometric View

How can one geometrically interpret the Jordan normal form? Note that each entry of 1 on the super-diagonal can be zeroed out by using an elementary row addition operator with the row below it, provided that we perform the elementary row addition operations from bottom to top order on consecutive pairs of rows. As we have already discussed, elementary row addition operations correspond to shear matrices. Multiplications with shear matrices cause transformations of the type that change the cube in Figure 3.2(a) to the parallelepiped in Figure 3.2(b). In fact, the transformation that would convert Figure 3.2(a) into Figure 3.2(b) is not a diagonalizable one; it cannot be represented purely as a stretching operation along specific directions, because changing a cube to a non-rectangular parallelepiped requires stretching in arbitrary directions, which would also change the directions of the parallelepiped edges from its axis-parallel orientation. See Figure 3.1 for an example of the effect of arbitrarily oriented scaling on axis-parallel edges. Therefore, additional rotations would be needed for re-alignment. Non-diagonalizable matrices always contain this type of “residual” rotation. 

Diagonalizable transforms are those in which a (possibly non-orthogonal) basis system exists along which one can scale the space. For non-diagonalizable matrices, scaling alone is not adequate. If we are additionally willing to allow some rotation after the scaling, nondiagonalizable transformations can be represented as well. As discussed in Lemma 7.2.2 of Chapter 7, every square matrix can be decomposed into the product of a diagonalizable matrix and the “residual” rotation matrix. This decomposition is referred to as the polar decomposition of a matrix. Note that rotation matrices are also diagonalizable, albeit with complex eigenvalues. Therefore, every real matrix can be expressed as the product of at most two diagonalizable matrices (although one might have complex eigenvalues). 

## 3.3.5 Similar Matrix Families Sharing Eigenvalues

Similar matrices are defined as follows: 

Definition 3.3.3 Two matrices A and B are said to be similar when $B = V A V ^ { - 1 }$ 

Similarity is a commutative and transitive property. In other words, if A and B are similar, then B and A are similar as well. Furthermore, if A and B are similar, and if B and C are similar, then A and C are also similar. Therefore, similar matrices form a family of related matrices. 

What do similar matrices mean? When we have two similar matrices A and B, then multiplying a vector with either A or B results in the same transformation of that vector as long as the basis is appropriately chosen in each case. For example, two similar matrices of size $3 \times 3$ might each correspond to a $6 0 ^ { \circ }$ rotation of a 3-dimensional vector, but the axis of rotation might be different. Similarly, two similar transforms might scale a vector by the same factors in different directions. One can interpret this point in terms of their Jordan normal forms. 

Lemma 3.3.8 (Jordan Normal Forms of Similar Matrices) Let A and B be two similar matrices satisfying $B = V A V ^ { - 1 }$ . Then, their Jordan normal forms (with possibly complex eigenvalues) will be related: 

$$
A = V _ {1} U V _ {1} ^ {- 1}, \quad B = V _ {2} U V _ {2} ^ {- 1}
$$

The matrix $V _ { 2 }$ is related to $V _ { 1 }$ as $V _ { 2 } = V V _ { 1 }$ 

The above lemma is easy to show by direct substitution of the Jordan form of A in the relationship $B = V A V ^ { - 1 }$ . An important consequence of the above result is that similar matrices are have the same eigenvalues (and their corresponding multiplicities). Furthermore, if one member of a similar family is diagonalizable, then all members are diagonalizable as well, and a diagonal matrix is included in the family. 

As introduced in Chapter 2, the sum of the diagonal entries of a matrix is referred to as its trace. The trace of a matrix A is equal to the sum of its eigenvalues, whether it is diagonalizable or not. 

Lemma 3.3.9 The traces of similar matrices are equal, and are equal of the sum of the eigenvalues of that family (whether it is diagonalizable or not). 

Proof: Here, we will use the property of the trace that $\operatorname { t r } ( G H ) \ = \ \operatorname { t r } ( H G )$ for square matrices G and H. Let A and B be similar matrices such that $A = V B V ^ { - 1 }$ . Then, we have the following: 

$$
\operatorname{tr} (A) = \operatorname{tr} (V [ B V ^ {- 1} ]) = \operatorname{tr} ([ B V ^ {- 1} ] V) = \operatorname{tr} (B [ V ^ {- 1} V ]) = \operatorname{tr} (B)
$$

Therefore, the traces of similar matrices are equal. This also implies that the trace of a matrix is equal to the trace of the upper-triangular matrix in its Jordan normal form (which is equal to the sum of the eigenvalues of the family). 

Similar matrices perform similar operations, but in different basis systems. For example, a similar family of diagonalizable matrices performs anisotropic scaling with the same factors, albeit in completely different eigenvector directions. 

Problem 3.3.7 (Householder Family) Show that all Householder reflection matrices are similar, and the family includes the elementary reflection matrix that differs from the identity matrix in one element. 

A hint for solving the above problem is that this matrix is diagonalizable. 

Problem 3.3.8 (Projection Family) Section 2.8.2 introduces the n n projection matrix $P = A ( A ^ { T } A ) ^ { - 1 } { \dot { A ^ { T } } }$ for $n \times d$ matrix A with full column rank d and $n > d .$ . Show that all projection matrices P obtained by varying A (but for particular values of n and d) are similar. What is the trace of P? Provide a geometric interpretation of $( I - P )$ and $( I - 2 P )$ 

A hint for solving this problem is to first express the projection matrix in the form $Q Q ^ { T }$ by using QR decomposition of A, where Q is an orthogonal matrix. Now extract the eigenvectors and eigenvalues of the projection matrix by using the properties of $Q ,$ , and verify that the eigenvalues are always the same for fixed values of n and d. 

Problem 3.3.9 (Givens Family) Show that all Givens matrices with the same rotation angle α are similar, because for any such pair of Givens matrices $G _ { 1 }$ and $G _ { 2 }$ , one can find a permutation matrix P such that $G _ { 2 } = P G _ { 1 } P ^ { T }$ . Now consider an orthogonal matrix Q that is not a permutation matrix. Provide a geometric interpretation of $Q G _ { 1 } Q ^ { T }$ 

For the reader who is familiar with graph adjacency matrices, we recommend the following exercise (or to return to it after reading Chapter 10): 

Problem 3.3.10 (Similarity in Graph Theory) Consider a graph $G _ { A }$ whose adjacency matrix is A. Show that the adjacency matrix B of the isomorphic graph $G _ { B }$ obtained by reordering the vertices of $G _ { A }$ is similar to matrix A. What type of matrix is used for the basis transformation between A and B? 

## Geometric Interpretability of Trace

Since the trace of a matrix is invariant to similarity transformations, a natural question arises as to whether it can be interpreted in a geometric way. The interpretation of the trace of a square matrix is not a simple one, especially when the underlying matrix is not symmetric. Fortunately, many of the square matrices encountered in machine learning appear in the form of Gram matrices $A ^ { T } A$ , where A is either an $n \times d$ data set or its transpose. Examples of such matrices include the regularized graph adjacency matrix, the covariance matrix and the dot product similarity matrix. We make the following observation: 

Observation 3.3.3 The trace of the Gram matrix $A ^ { T } A$ is equal to the energy in its base matrix A. 

The above observation follows directly from the definition of energy in Equation 1.23 of Chapter 1. One consequence of the observation is that if we apply an orthonormal similarity transformation AP on a data set contained in the $n \times d$ matrix A, its energy, which is equal to the trace of $P ^ { T } ( A ^ { T } A ) P$ does not change. This fact can be used to infer the result that the sum of the variances of all dimensions in a mean-centered data set is always the same, irrespective the choice of basis: 

Problem 3.3.11 (Covariance Family) Let D be a mean-centered n d data set with n rows and d dimensions, and let P be any d d orthogonal matrix. Let DP be the transformed $n \times d$ data set in the new orthogonal basis system. A covariance matrix is a d d matrix, in which $( i , j )$ th entry is the covariance between dimensions i and j, with diagonal entries representing variances. Show that all covariance matrices of $D P$ over different choices of orthogonal P are similar and they therefore have the same trace. 

## 3.3.6 Diagonalizable Matrix Families Sharing Eigenvectors

A diagonalizable matrix family that shares eigenvectors (but not eigenvalues) is referred to as simultaneously diagonalizable. This idea is complementary to the notion of diagonalizable, similar matrices that share eigenvalues, but not eigenvectors. 

Definition 3.3.4 (Simultaneous Diagonalizability) Two diagonalizable matrices A and B are said to be simultaneously diagonalizable, if a $d \times d$ invertible matrix V exists, such that the columns of V are the eigenvectors of both A and B. Therefore, we have the following: 

$$
\begin{array}{c} {A = V \Delta_ {1} V ^ {T}} \\ {B = V \Delta_ {2} V ^ {T}} \end{array}
$$

Here, $\Delta _ { 1 }$ and $\Delta _ { 2 }$ are diagonal matrices. 

The geometric interpretation of simultaneously diagonalizable matrices is that they perform anisotropic scaling in the same set of directions. However, the scaling factors might be dif ferent, since the diagonal matrices are different. Simultaneous diagonalizability is a property that is closely related to matrix commutativity. 

Lemma 3.3.10 Diagonalizable matrices are also simultaneously diagonalizable if and only if they are commutative. 

Problem 3.3.12 Let A and B be two diagonalizable matrices that share the same set of eigenvectors. Provide a geometric interpretation of why $A B = B A$ 

Problem 3.3.13 (Givens Commutative Family) The multiplication of rotation matrices in dimensionalities greater than 2 is not commutative in general. However, the $d \times d$ family of Givens rotation matrices $G _ { c } ( i , j , \theta )$ is known to commutative over fixed dimension pair i, j and varying θ. Provide a geometric interpretation of this commutativity. Now provide an algebraic interpretation in terms of simultaneous diagonalizability by generalizing Equation 3.21 to d d matrices. 

## 3.3.7 Symmetric Matrices

Symmetric matrices arise repeatedly in machine learning. This is because covariance matrices, dot-product matrices, (undirected) graph adjacency matrices, and similarity (kernel) matrices are used frequently in machine learning. Furthermore, many of the applications associated with such matrices require some type of diagonalization. One of the fundamental properties of symmetric matrices is that they are always diagonalizable, and have orthonor mal eigenvectors. This result is referred to as the spectral theorem: 

Theorem 3.3.1 (Spectral Theorem) Let A be a d d symmetric matrix with real entries. Then, A is always diagonalizable with real eigenvalues and has orthonormal, realvalued eigenvectors. In other words, A can be diagonalized in the form $A = V \Delta V ^ { T }$ with orthogonal matrix V. 

Proof: First, we need to show that the eigenvalues of A are real. Let (v, λ) represents a eigenvector-eigenvalue pair of a real matrix. We start with the most general assumption that this pair could be complex. Pre-multiplying the equation $A { \overline { { v } } } = \lambda { \overline { { v } } }$ with the conjugate transpose $\overline { { v } } ^ { \ast }$ of $^ { v , }$ we obtain $\overline { { v } } ^ { * } A \overline { { v } } = \lambda \overline { { v } } ^ { * } \overline { { v } } = \lambda \| \overline { { v } } \| ^ { 2 } = \lambda$ . In other words we have ${ \overline { { v } } } ^ { * } A { \overline { { v } } } = \lambda$ Taking the conjugate transpose of both sides of this $1 \times 1$ “matrix,” we obtain: 

$$
\lambda^ {*} = [ \overline {{v}} ^ {*} A \overline {{v}} ] ^ {*} = \overline {{v}} ^ {*} A ^ {*} [ \overline {{v}} ^ {*} ] ^ {*} = \overline {{v}} ^ {*} A ^ {*} \overline {{v}} = \overline {{v}} ^ {*} A \overline {{v}} = \lambda
$$

We used the real and symmetric nature of A in the above derivation. Therefore, the eigenvalue λ is equal to its conjugate, and it is real. The eigenvector v is also real because it belongs to the null space of the real matrix $( A - \lambda I )$ 

We claim that eigenvalues with multiplicity greater than 1 do not have missing eigenvectors. If there are missing eigenvectors, two non-zero vectors $\overline { { v } } _ { 1 }$ and $\overline { { v } } _ { 2 }$ must exist in a Jordan chain such that $A { \overline { { v } } } _ { 1 } = \lambda { \overline { { v } } } _ { 1 }$ and $A \overline { { { v } } } _ { 2 } = \lambda \overline { { { v } } } _ { 2 } + \overline { { { v } } } _ { 1 }$ (see Section 3.3.3). Then, we can show that $( A - \lambda I ) ^ { 2 } \overline { { v } } _ { 2 } = 0$ , by successively applying the eigenvector condition. Therefore, $\overline { { v } } _ { 2 } ^ { T } ( A - \lambda I ) ^ { \dot { 2 } } \overline { { v } } _ { 2 }$ is zero as well. At the same time, one can show the contradictory result that this quantity is non-zero by using the symmetric nature of the matrix A: 

$$
\overline {{v}} _ {2} ^ {T} (A - \lambda I) ^ {2} \overline {{v}} _ {2} = [ \overline {{v}} _ {2} ^ {T} (A ^ {T} - \lambda I ^ {T}) ] [ (A - \lambda I) \overline {{v}} _ {2} ] = \| (A - \lambda I) \overline {{v}} _ {2} \| ^ {2} = \| \overline {{v}} _ {1} \| ^ {2} \neq 0
$$

Therefore, we obtain a contradiction, and A is diagonalizable (with no missing eigenvectors). Next, we need to show that all eigenvectors are mutually orthogonal. Within the eigenspace of a repeated eigenvalue, we can always choose an orthonormal basis of eigenvectors. Furthermore, two eigenvectors $\overline { { v } } _ { 1 }$ and $\overline { { v } } _ { 2 }$ belonging to distinct eigenvalues $\lambda _ { 1 }$ and $\lambda _ { 2 }$ are also orthogonal. This is because transposing the scalar $\overline { { v } } _ { 1 } ^ { T } A \overline { { v } } _ { 2 }$ results in the same scalar $\overline { { v } } _ { 2 } ^ { T } A ^ { T } \overline { { v } } _ { 1 } = \overline { { v } } _ { 2 } ^ { T } A \overline { { v } } _ { 1 }$ . Using this, we can show the following: 

$$
\begin{array}{l} \overline {{v}} _ {1} ^ {T} \underbrace {[ A \overline {{v}} _ {2} ]} _ {\lambda_ {2} \overline {{v}} _ {2}} = \overline {{v}} _ {2} ^ {T} \underbrace {[ A \overline {{v}} _ {1} ]} _ {\lambda_ {1} \overline {{v}} _ {1}} \\ \lambda_ {1} (\overline {{v}} _ {1} \cdot \overline {{v}} _ {2}) = \lambda_ {2} (\overline {{v}} _ {1} \cdot \overline {{v}} _ {2}) \\ (\lambda_ {1} - \lambda_ {2}) (\overline {{v}} _ {1} \cdot \overline {{v}} _ {2}) = 0 \end{array}
$$

This is possible only when the dot product of the two eigenvectors is zero. 

Since the inverse of an orthogonal matrix is its transpose, it is common to write the diagonalization of symmetric matrices in the form $A \ : = \ : V \Delta V ^ { T }$ instead of $A = V \Delta V ^ { - 1 }$ Multiplying a data matrix D with a symmetric matrix represents anisotropic scaling of its rows along orthogonal axis directions. An example of such a scaling is illustrated on the left-hand side of Figure 3.1. 

The eigenvectors of a symmetric matrix A are not only orthogonal but also A-orthogonal. 

Definition 3.3.5 (A-Orthogonality) A set of column vectors $\overline { { v } } _ { 1 } \ldots \overline { { v } } _ { d }$ is A-orthogonal, if and only if $\overline { { v } } _ { i } ^ { T } A \overline { { v } } _ { j } = 0$ for all pairs [i, j] with $i \neq j$ 

The notion of A-orthogonality is a generalization of orthogonality, and setting $A = I$ reverts the definition to the usual notion of orthogonality. Note that $\check { v } _ { i } ^ { T } A \overline { { v } } _ { j }$ is simply a different choice of inner product from the vanilla dot product (cf. Definition 2.10.1). 

Lemma 3.3.11 The eigenvectors of a symmetric d d matrix A are A-orthogonal. 

Proof: For any pair of eigenvectors $\overline { { v } } _ { i }$ and $\overline { { v } } _ { j }$ with eigenvalues $\lambda _ { i }$ and $\lambda _ { j }$ , we have the following: 

$$
\overline {{v}} _ {i} ^ {T} A \overline {{v}} _ {j} = \overline {{v}} _ {i} ^ {T} [ \lambda_ {j} \overline {{v}} _ {j} ] = \lambda_ {j} \overline {{v}} _ {i} ^ {T} \overline {{v}} _ {j} = 0
$$

The result follows. 

![image](<Images/03_Eigenvectors_and_Diagonalizable_Matrices_image_004.jpg>)



Figure 3.3: Positive semidefinite transforms do not change angular orientations of points by more than $9 0 °$


One can use a natural generalization of Gram-Schmidt orthogonalization (cf. Problem 2.7.1) to find A-orthogonal basis sets (which is a more efficient choice than eigenvector computation). In many applications like conjugate gradient descent, one is often looking for Aorthogonal directions, where A is the Hessian of the optimization function. 

Problem 3.3.14 (Frobenius Norm vs Eigenvalues) Consider a matrix with real eigenvalues. Show that its squared Frobenius norm is at least equal to the sum of the squares of its eigenvalues, and that strict equality is observed for symmetric matrices. You will find the Schur decomposition helpful. 

## 3.3.8 Positive Semidefinite Matrices

A symmetric matrix is positive semidefinite if and only if all its eigenvalues are non-negative. From a geometric perspective, pre-multiplication of a set of d-dimensional vectors $\overline { { x } } _ { 1 } \ldots \overline { { x } } _ { n }$ with a d d positive semidefinite matrix A to create $A { \overline { { x } } } _ { 1 } \ldots A { \overline { { x } } } _ { n }$ will distort the scatterplot of the vectors (see Figure 3.3 for $d = 2 )$ , so that the scatter-plot is stretched along all the eigenvector directions with non-negative scale factors. For example, the scale factors in Figure 3.3 are 2 and 0.5. The nonnegativity of scale factors ensures that transformed vectors do not have large angles with respect to the original vectors (i.e., angles greater than 90◦). The angle between a data vector x and its transformed representation ${ \overline { { x } } } ^ { \prime } = A { \overline { { x } } }$ is shown in Figure 3.3; this angle is no greater than $9 0 ^ { \circ }$ because of the fact that the scale factors are nonnegative. Since the cosine of any such angle is nonnegative, it follows that the dot product $\check { x } ^ { \check { T } } ( A \overline { { x } } )$ between any column vector $\overline { { x } } \in \mathcal { R } ^ { d }$ and its transformed representation, Ax, is nonnegative. This observation provides the definition of positive semidefinite matrices: 

Definition 3.3.6 (Positive Semidefinite Matrix) A d d symmetric matrix A is positive semidefinite if and only if for any non-zero vector $\overline { { x } } \in \mathcal { R } ^ { d }$ , the following is true: 

$$
\overline {{x}} ^ {T} A \overline {{x}} \geq 0\tag{3.27}
$$

Figure 3.3 provides the pictorial intuition as to why Definition 3.3.6 is equivalent to stating that the eigenvalues are nonnegative. In the following, we show this result formally: 

Lemma 3.3.12 Definition 3.3.6 on positive semidefiniteness of a $d \times d$ symmetric matrix A is equivalent to stating that A has nonnegative eigenvalues. 

Proof: According to the spectral theorem, we can always diagonalize a symmetric matrix A as $V \Delta V ^ { T }$ . Suppose that the eigenvalues $\lambda _ { 1 } \ldots \lambda _ { d }$ in $\Delta$ are all nonnegative. Then, for any column vector ${ \overline { { x } } } ,$ let us denote $\overline { { y } } = { \cal V } ^ { T } \overline { { x } }$ . Furthermore, let the ith component of $\overline { y }$ be denoted by $y _ { i }$ . Therefore, we have: 

$$
\overline {{x}} ^ {T} A \overline {{x}} = \overline {{x}} ^ {T} V \Delta V ^ {T} \overline {{x}} = (V ^ {T} \overline {{x}}) ^ {T} \Delta (V ^ {T} \overline {{x}}) = \overline {{y}} ^ {T} \Delta \overline {{y}} = \sum_ {i = 1} ^ {d} \lambda_ {i} y _ {i} ^ {2}
$$

It is clear that the final expression on the right is nonnegative because each $\lambda _ { i }$ is nonnegative. Therefore, the matrix A is positive semidefinite according to Definition 3.3.6. 

To prove the converse, let us assume that A is positive semidefinite according to Defini tion 3.3.6. Therefore, it is the case that $\overline { { x } } ^ { T } A \overline { { x } } \geq 0$ for any x. Then, let us select x to be the ith column of $V$ (which is also the ith eigenvector). Then, because of the orthonormality of the columns of V, we have $V ^ { T } \overline { { x } } = \overline { { e } } _ { i }$ , where $\overline { { e } } _ { i }$ contains a single 1 in the ith position, and 0s in all other positions. As a result, we have the following: 

$$
\overline {{x}} ^ {T} A \overline {{x}} = \overline {{x}} ^ {T} V \Delta V ^ {T} \overline {{x}} = (V ^ {T} \overline {{x}}) ^ {T} \Delta (V ^ {T} \overline {{x}}) = \overline {{e}} _ {i} ^ {T} \Delta \overline {{e}} _ {i} = \lambda_ {i}
$$

Therefore, $\lambda _ { i }$ needs to be nonnegative because we know that $\overline { { x } } ^ { T } A \overline { { x } } \geq 0$ . The result follows. 

A minor variation on the notion of positive semidefinite matrix is that of a positive definite matrix, where the matrix A cannot be singular. 

Definition 3.3.7 (Positive Definite Matrix) A d d symmetric matrix A is positive definite if and only if for any non-zero vector $\overline { { x } } \in \mathcal { R } ^ { d }$ , the following is true: 

$$
\overline {{x}} ^ {T} A \overline {{x}} > 0\tag{3.28}
$$

The eigenvalues of such a matrix need to be strictly positive. 

Lemma 3.3.13 A symmetric matrix $A = V \Delta V ^ { T }$ is positive definite, $i f$ and only $i f$ it has positive eigenvalues. 

Unlike positive semidefinite matrices, positive definite matrices are guaranteed to be invertible. The inverse matrix is simply $V \bar { \Delta } ^ { - 1 } V ^ { T }$ ; here, $\Delta ^ { - 1 }$ can always be computed because none of the eigenvalues are zero. 

One can also define negative semidefinite matrices as those matrices in which every eigenvalue is non-positive, and $\overline { { x } } ^ { T } A \overline { { x } } \leq 0$ for each column vector x. A negative semidefinite matrix can be converted into a positive semidefinite matrix by reversing the sign of each entry in the matrix. A negative definite matrix is one in which every eigenvalue is strictly negative. Symmetric matrices with both positive and negative eigenvalues are said to be indefinite. 

Any matrix of the form $B B ^ { T }$ or $B ^ { T } B$ (i.e., Gram matrix form) is always positive semidef inite. The Gram matrix is fundamental to machine learning, and it appears repeatedly in different forms. Note that B need not be a square matrix. This provides yet another definition of positive semidefiniteness. 

Lemma 3.3.14 A d d matrix A is positive semi-definite if and only if it can be expressed in the form $B ^ { T } B$ for some matrix B. 

Proof: For any non-zero column vector $\overline { { x } } \in \mathcal { R } ^ { d }$ , we have: 

$$
\overline {{{x}}} ^ {T} B ^ {T} B \overline {{{x}}} = (B \overline {{{x}}}) ^ {T} (B \overline {{{x}}}) = \| B \overline {{{x}}} \| ^ {2} \geq 0
$$

The result follows. 

Conversely, any positive semidefinite matrix A can be expressed in the eigendecompo-sition form $\bar { A } = \bar { Q } \bar { \Sigma ^ { 2 } } Q ^ { T } = ( Q \Sigma ) ( Q \Sigma ) ^ { T }$ . Then, by setting $B \bar { = } ( Q \Sigma ) ^ { T }$ , we obtain the form$A = B ^ { T } B$ 厂

Note that we could also have stated this lemma using $B B ^ { T }$ instead of $B ^ { T } B .$ , and the proof is similar. We will use the above result extensively for kernel feature engineering in Chapter 9. 

Problem 3.3.15 If C is a positive semidefinite matrix, show that there exists a square-root matrix $\sqrt { C }$ that satisfies the following: 

$$
\sqrt {C} \sqrt {C} = C
$$

Problem 3.3.16 If a matrix C is positive definite, then so is $C ^ { - 1 }$ 

A hint for solving the above problems is to examine the eigendecomposition trick used in the proof of Lemma 3.3.14. 

## 3.3.9 Cholesky Factorization: Symmetric LU Decomposition

The fact that positive definite matrices can be symmetrically factorized into Gram matrix form is a useful result for kernel methods in machine learning. The use of eigendecomposition to achieve this goal is a natural choice, but not the only one. Given a factorization the $d \times d$ matrix as $A = B B ^ { T }$ , one can use any orthogonal $d \times d$ matrix P to create the alternative factorization $A = B ( P P ^ { T } ) B ^ { T } = ( B P ) ( B P ) ^ { T }$ . One of these infinite choices of symmetric factorizations of A is one in which B is lower-triangular. In other words, one can express the positive definite matrix A in the form $L L ^ { T }$ , where $L = [ l _ { i j } ]$ is some $d \times d$ lower-triangular matrix. This is referred to as the Cholesky factorization. 

The Cholesky decomposition is a special case of LU decomposition, and it can be used only for positive definite matrices. Although a matrix might have an infinite number of LU decompositions, a positive definite matrix has a unique Cholesky factorization. It is computationally more efficient to compute the Cholesky decomposition for positive definite matrices than the generic LU decomposition. 

Let the columns of the matrix $L = [ l _ { i j } ] _ { d \times d }$ be denoted by $\bar { l } _ { 1 } \ldots \bar { l } _ { d }$ . Furthermore, since the matrix $A = [ a _ { i j } ] _ { d \times d }$ is symmetric, we will focus only on the lower-triangular entries $a _ { i j }$ (with $i \geq j )$ to set up a system of equations that can be easily solved using back-substitution. First, note that for any $i \geq j$ , we have the following condition: 

$$
a _ {i j} = \underbrace {\sum_ {k = 1} ^ {d} l _ {i k} l _ {j k}} _ {A _ {i j} = (L L ^ {T}) _ {i j}} = \underbrace {\sum_ {k = 1} ^ {j} l _ {i k} l _ {j k}} _ {\text { Lower - triangular   } L}
$$

Note that the subscript for k only runs up to j instead of d for lower-triangular matrices and $i \geq j$ . This condition easily sets up a simple system of equations for computing the entries in each column of L one-by-one while back substituting the entries already computed, as long as we do the computations in the correct order. For example, we can compute the first column of L by setting $j = 1$ , and iterating over all $i \geq j$ j: 

$$
\begin{array}{l l} {l _ {1 1} = \sqrt {a _ {1 1}}} \\ {l _ {i 1} = a _ {i 1} / l _ {1 1}} & {\forall i > 1} \end{array}
$$

We can repeat the same process to compute the second column of L as follows: 

$$
\begin{array}{l} {l _ {2 2} = \sqrt {a _ {2 2} - l _ {2 1} ^ {2}}} \\ {l _ {i 2} = (a _ {i 2} - l _ {i 1} l _ {2 1}) / l _ {2 2} \forall i > 2} \end{array}
$$

A generalized iteration for the jth column yields the pseudocode for Cholesky factorization: 

Initialize $L = [0]_{d \times d}$ ;  
for $j = 1$ to $d$ do $l_{jj} = \sqrt{a_{jj} - \sum_{k=1}^{j-1} l_{jk}^2}$ ;  
for $i = j + 1$ to $d$ do $l_{ij} = (a_{ij} - \sum_{k=1}^{j-1} l_{ik} l_{jk}) / l_{jj}$ ;  
endfor  
endfor  
return $L = [l_{ij}]$ ; 

Each computation of $l _ { i j }$ requires $O ( d )$ time, and therefore the Cholesky method requires $O ( d ^ { 3 } )$ time. The above algorithm works for positive-definite matrices. If the matrix is singular and positive semi-definite, then at least one $l _ { j j }$ will be 0. This will cause a division by 0 during the computation of $l _ { i j }$ , which results in an undefined value. The decomposition is no longer unique, and a Cholesky factorization does not exist in such a case. One possibility is to add a small positive value to each diagonal entry of A to make it positive definite and then restart the factorization. If the matrix A is indefinite or negative semidefinite, it will show up during the computation of at least one $l _ { j j }$ , where one will be forced to compute the square-root of a negative quantity. The Cholesky factorization is the preferred approach for testing the positive definiteness of a matrix. 

Problem 3.3.17 (Solving a System of Equations) Show how you can solve the system of equations $( L L ^ { T } ) \dot { \overline { { x } } } = \overline { { b } }$ by successively solving two triangular systems of equations, the first of which is $L { \overline { { y } } } = { \bar { b } }$ . Use this fact to discuss the utility of Cholesky factorization in certain types of systems of equations. Where does the approach not apply? 

Problem 3.3.18 (Cholesky Factorization from Any Symmetric Factorization) Suppose that you are already given a symmetric factorization $B ^ { T } B$ of d d positive definite matrix A, where B is a tall matrix with linearly independent columns. Show that the Cholesky factorization of A can be extracted by performing the QR-decomposition of B. 

## 3.4 Machine Learning and Optimization Applications

The linear algebra ideas in this chapter are used frequently in machine learning and optimization. This section will provide an overview of the most important examples, which will be used throughout this book. 

## 3.4.1 Fast Matrix Operations in Machine Learning

Consider a situation, where one wants to compute $A ^ { k }$ for some positive integer k. Repeated matrix multiplication can be expensive. Furthermore, there is no way to compute $A ^ { k }$ , when k tends to $\infty$ in the limit. It turns out that diagonalization is very useful, even if it is complex valued. This is because one can express $\bar { A ^ { k } }$ as follows: 

$$
A ^ {k} = V \Delta^ {k} V ^ {- 1}\tag{3.29}
$$

Note that it is often easy to compute $\Delta ^ { k }$ , because we only need to exponentiate the individual entries along the diagonal. By using this approach, one can compute $A ^ { k }$ in relatively few operations. $\mathrm { A s ~ } k  \infty$ , it is often the case that $A ^ { k }$ will either vanish to 0 or explode to very large entries depending on whether the largest eigenvalue is less than 1 or whether it is greater than 1. One can easily compute a polynomial function in A by computing a polynomial function in $\Delta$ . These types of applications often arise when working with the adjacency matrices of graphs (cf. Chapter 10). 

## 3.4.2 Examples of Diagonalizable Matrices in Machine Learning

There are several positive semidefinite matrices that arise repeatedly in machine learning applications. This section will provide an overview of these matrices. 

## Dot Product Similarity Matrix

A dot product similarity matrix of an $n \times d$ data matrix D is an $n \times n$ matrix containing the pairwise dot products between the rows of D. 

Definition 3.4.1 Let D be an $n ~ \times$ d data matrix containing d-dimensional points in its rows. Let S be an $n \times n$ similarity matrix between the points, where the $( i , j ) t h$ entry is the dot product between the ith and jth rows of D. Therefore, the similarity matrix S is related to D as follows: 

$$
S = D D ^ {T}\tag{3.30}
$$

Since the dot product is in the form of a Gram matrix, it is positive semidefinite (cf. Lemma 3.3.14): 

## Observation 3.4.1 The dot product similarity matrix of a data set is positive semidefinite.

A dot product similarity matrix is an alternative way of specifying the data set, because one can recover the data set D from the similarity matrix to within rotations and reflections of the original data set. This is because each computational procedure for performing symmetric factorization $S = D ^ { \prime } D ^ { \prime T }$ of the similarity matrix might yield a a different $D ^ { \prime }$ , which can be viewed as a rotated and reflected version of D. Examples of such computational procedures include eigendecomposition or Cholesky factorization. All the alternatives yield the same dot product. After all, dot products are invariant to axis rotation of the coordinate system. Since machine learning applications are only concerned with the relative positions of points, this type of ambiguous recovery is adequate in most cases. One of the most common methods to “recover” a data matrix from a similarity matrix is to use eigendecomposition: 

$$
S = Q \Delta Q ^ {T}\tag{3.31}
$$

The matrix $\Delta$ contains only nonnegative eigenvalues of the positive semidefinite similarity matrix, and therefore we can create a new diagonal matrix $\Sigma$ containing the square-roots of the eigenvalues. Therefore, the similarity matrix $S$ can be written as follows: 

$$
S = Q \Sigma^ {2} Q ^ {T} = \underbrace {(Q \Sigma)} _ {D ^ {\prime}} \underbrace {(Q \Sigma) ^ {T}} _ {D ^ {\prime T}}\tag{3.32}
$$

Here, $D ^ { \prime } = Q \Sigma$ is an $n \times n$ data set containing n-dimensional representations of the n points. It seems somewhat odd that the new matrix $D ^ { \prime } = Q \Sigma$ is an $n \times n$ matrix. After all, if the similarity matrix represents dot products between d-dimensional data points for $d \ll n$ , we should expect the recovered matrix $D ^ { \prime }$ to be a rotated representation of D in d dimensions. What are the extra $( n - d )$ dimensions? Here, the key point is that if the similarity matrix $S$ was indeed created using dot products on d-dimensional points, then $D D ^ { T }$ will also have rank at most $d .$ Therefore, at least $( n - d )$ eigenvalues in $\Delta$ will be zeros, which correspond to dummy coordinates. 

But what if we did not use dot product similarity to calculate S from D? What if we used some other similarity function? It turns out that this idea is the essence of kernel methods in machine learning (cf. Chapter 9). Instead of using the dot product ${ \overline { { x } } } \cdot { \overline { { y } } }$ between two points, one often uses similarity functions such as the following: 

$$
\mathrm{Similarity} (\overline {{x}}, \overline {{y}}) = \exp (- \| \overline {{x}} - \overline {{y}} \| ^ {2} / \sigma^ {2})\tag{3.33}
$$

Here, $\sigma$ is a parameter that controls the sensitivity of the similarity function to distances between points. Such a similarity function is referred to as a Gaussian kernel. If we use a similarity function like this instead of the dot product, we might recover a data set that is different from the original data set from which the similarity was constructed. In fact this recovered data set may not have dummy coordinates, and all $n > d$ dimensions might be relevant. Furthermore, the recovered representations $Q \Sigma$ from such similarity functions might yield better results for machine learning applications than the original data set. This type of fundamental transformation of the data to a new representation is referred to as nonlinear feature engineering, and it goes beyond the natural (linear) transformations like rotation that are common in linear algebra. In fact, it is even possible to extract multidimensional representations from data sets of arbitrary objects between which only similarity is specified. For example, if we have a set of n graph or time-series objects, and we only have the $n \times n$ similarity matrix of these objects (and no multidimensional representation), we can use the aforementioned approach to create a multidimensional representation of each object for of-the-shelf learning algorithms. 

Problem 3.4.1 Suppose you were given a similarity matrix S that was constructed using some arbitrary heuristic (rather than dot products) on a set of n arbitrary objects $( e . g . ,$ graphs). As a result, the matrix is symmetric but not positive semidefinite. Discuss how you can repair the matrix S by modifying only its self-similarity $( i . e . ,$ diagonal) entries, so that the matrix becomes positive semidefinite. 

A hint for solving this problem is to examine the effect of adding a constant value to the diagonal on the eigenvalues. This trick is used frequently for applying kernel methods in machine learning, when a similarity matrix is constructed using an arbitrary heuristic. 

## Covariance Matrix

Another common matrix in machine learning is the covariance matrix. Just as the similarity matrix computes dot products between rows of matrix $D ,$ , the covariance matrix computes (scaled) dot products between columns of D after mean-centering the matrix. Consider a set of scalar values $x _ { 1 } \ldots x _ { n }$ . The mean $\mu$ and the variance $\sigma ^ { 2 }$ of these values are defined as follows: 

$$
\begin{array}{l} {\mu = \frac {\sum_ {i = 1} ^ {n} x _ {i}}{n}} \\ {\sigma^ {2} = \frac {\sum_ {i = 1} ^ {n} (x _ {i} - \mu) ^ {2}}{n} = \frac {\sum_ {i = 1} ^ {n} x _ {i} ^ {2}}{n} - \mu^ {2}} \end{array}
$$

Consider a data matrix in which two columns have values $x _ { 1 } \ldots x _ { n }$ and $y _ { 1 } \ldots y _ { n } .$ , respectively. Also assume that the means of the two columns are $\mu _ { x }$ and $\mu _ { y }$ . In this case, the covariance $\sigma _ { x y }$ is defined as follows: 

$$
\sigma_ {x y} = \frac {\sum_ {i = 1} ^ {n} (x _ {i} - \mu_ {x}) (y _ {i} - \mu_ {y})}{n} = \frac {\sum_ {i = 1} ^ {n} x _ {i} y _ {i}}{n} - \mu_ {x} \mu_ {y}
$$

The notion of covariance is an extension of variance, because $\sigma _ { x } ^ { 2 } = \sigma _ { x x }$ is simply the variance of $x _ { 1 } \ldots x _ { n }$ . If the data is mean-centered with $\mu _ { x } = \mu _ { y } = 0$ , the covariance simplifies to the following: 

$$
\sigma_ {x y} = \frac {\sum_ {i = 1} ^ {n} x _ {i} y _ {i}}{n} \quad [ \mathrm{Mean-centereddataonly} ]
$$

It is noteworthy that the expression on the right-hand side is simply a scaled version of the dot product between the columns, if we represent the x values and y values as an $n \times 2$ matrix. Note the close relationship to the similarity matrix, which contains dot products between all pairs of rows. Therefore, if we have an $n \times d$ data matrix $D _ { ; }$ , which is meancentered, we can compute the covariance between the column i and column $j$ using this approach. Such a matrix is referred to as the covariance matrix. 

Definition 3.4.2 (Covariance Matrix of Mean-Centered Data) Let D be an $n \times d$ mean-centered data matrix. Then, the covariance matrix C of D is defined as follows: 

$$
C = \frac {D ^ {T} D}{n}
$$

The unscaled version of the matrix, in which the factor of $n$ is not used in the denominator, is referred to as the scatter matrix. In other words, the scatter matrix is simply $D ^ { T } D$ . The scatter matrix is the Gram matrix of the column space of $D _ { : }$ , whereas the similarity matrix is the Gram matrix of the row space of $D$ . Like the similarity matrix, the scatter matrix and covariance matrix are both positive semidefinite, based on Lemma 3.3.14. 

The covariance matrix is often used for principal component analysis (cf. Section 7.3.4). Since the $d { \times } d$ covariance matrix $C$ is positive semidefinite, one can diagonalize it as follows: 

$$
C = P \Delta P ^ {T}\tag{3.34}
$$

The data set D is transformed to $D ^ { \prime } = D P$ , which is equivalent to representing each row of the original matrix D in the axis system of directions contained in the columns of $P .$ This new data set has some interesting properties in terms of its covariance structure. One can also write the diagonal matrix as $\Delta = P ^ { T } C P$ . The diagonal matrix $\Delta$ is the new covariance matrix of the transformed data $D ^ { \prime } = D P$ . In order to see why this is true, note that the transformed data is also mean centered because the sum of its columns can be shown to be 0. The covariance matrix of the transformed data is therefore $D ^ { \prime T } D ^ { \prime } / n =$ $( D P ) ^ { T } ( D P ) / n = P ^ { T } ( D ^ { T } D ) P / n$ . This expression simplifies to $P ^ { T } C P = \Delta$ . In other words, the transformation represents a decorrelated version of the data. 

The entries on the diagonal of $\Delta$ are the variances of the individual dimensions in the transformed data, and they represent the nonnegative eigenvalues of the positive semidefinite matrix C. Typically, only a few diagonal entries are large (in relative terms), which contain most of the variance in the data. The remaining low-variance directions can be dropped from the transformed representation. One can select a small subset of columns from P corresponding to the largest eigenvalues in order to create a $d \times k$ transformation matrix $P _ { k }$ , where $k \ll d .$ The $d \times k$ transformed data matrix is defined as $D _ { k } ^ { \prime } = D P _ { k }$ . Each row is a new k-dimensional representation of the data set. It turns out that this representation has a highly reduced dimensionality, but it still retains most of the data variability (like Euclidean distances between points). For mean-centered data, the discarded $( d - k )$ columns of $D P$ are not very informative because they are all very close to 0. In fact, one can show using optimization methods that this representation provides an optimal reduction of the data in k dimensions (or principal components), so that the least amount of variance in the data is lost. We will revisit this problem in Chapters 7 and 8. 

## 3.4.3 Symmetric Matrices in Quadratic Optimization

Many machine learning applications are posed as optimization problems over a squared objective function. Such objective functions are quadratic, because the highest term of the polynomial is 2. The simplest versions of these quadratic functions can be expressed as ${ \overline { { x } } } ^ { T } A { \overline { { x } } }$ , where A is a $d \times d$ matrix and $\textstyle { \overline { { x } } }$ is a d-dimensional column vector of optimization variables. The process of solving such optimization problems is referred to as quadratic programming. Quadratic programming is an extremely important class of problems in opti mization, because arbitrary functions can be locally approximated as quadratic functions by using the method of Taylor expansion (cf. Section 1.5.1 of Chapter 1). This principle forms the basis of many optimization techniques, such as the Newton method (cf. Chapter 5). 

The shape of the function ${ \overline { { x } } } ^ { T } A { \overline { { x } } }$ critically depends on the nature of the matrix A. Functions in which A is positive semidefinite correspond to convex functions, which take the shape of a bowl with a minimum but no maximum. Functions in which A is negative semidefinite are concave, and they take on the shape of an inverted bowl. Examples of convex and concave functions are illustrated in Figure 3.4. Formally, convex and concave functions satisfy the following properties for any pair of vectors $\overline { { x } } _ { 1 }$ and $\overline { { x } } _ { 2 }$ and any scalar $\lambda \in ( 0 , 1 )$ 

$$
\begin{array}{l l} f (\lambda \overline {{x}} _ {1} + (1 - \lambda) \overline {{x}} _ {2}) \leq \lambda f (\overline {{x}} _ {1}) + (1 - \lambda) f (\overline {{x}} _ {2}) & [ \text { Convex   function } ] \\ h (\lambda \overline {{x}} _ {1} + (1 - \lambda) \overline {{x}} _ {2}) \geq \lambda h (\overline {{x}} _ {1}) + (1 - \lambda) h (\overline {{x}} _ {2}) & [ \text { Concave   function } ] \end{array}
$$

Functions in which A is neither positive nor negative semidefinite $( \mathrm { i . e . , ~ } A$ is indefinite) have neither global maxima nor do they have global minima. Such quadratic functions have saddle points, which are inflection points looking like both maxima or minima, depending on which direction one approaches that point from. An example of an indefinite function is illustrated in Figure 3.6. 

Consider the quadratic function $f ( x _ { 1 } , x _ { 2 } ) = x _ { 1 } ^ { 2 } + x _ { 2 } ^ { 2 }$ , which is convex and has a single global minimum at (0, 0). If we plot this function in three dimensions with $f ( x _ { 1 } , x _ { 2 } )$ on the vertical axis in addition to the two horizontal axes representing $x _ { 1 }$ and $x _ { 2 } ,$ , we obtain an upright bowl, as shown in Figure $3 . 4 ( \mathrm { a } )$ . One can express $f ( x , y )$ in matrix form as follows: 

![image](<Images/03_Eigenvectors_and_Diagonalizable_Matrices_image_005.jpg>)


![image](<Images/03_Eigenvectors_and_Diagonalizable_Matrices_image_006.jpg>)



(a) Convex function $f ( x , y ) = x ^ { 2 } + y ^ { 2 }$



(b) Concave function $f ( x , y ) = - ( x ^ { 2 } + y ^ { 2 } )$



Figure 3.4: Illustration of convex and concave functions


$$
f (x _ {1}, x _ {2}) = [ x _ {1}, x _ {2} ] \left[ \begin{array}{l l} 1 & 0 \\ 0 & 1 \end{array} \right] \left[ \begin{array}{l} x _ {1} \\ x _ {2} \end{array} \right]
$$

In this case, the function represents a perfectly circular bowl, and the corresponding matrix A for representing the ellipse $\overline { { x } } ^ { T } A \overline { { x } } \ : = \ : r ^ { 2 }$ is the $2 \times 2$ identity matrix, which is a trivial form of a positive semidefinite matrix. We can also use various vertical cross sections of the circular bowl shown in Figure $\mathrm { 3 . 4 ( a ) }$ to create a contour plot, so that the value of $f ( x _ { 1 } , x _ { 2 } )$ at each point on a contour line is constant. The contour plot of the circular bowl in shown in Figure 3.5(a). Note that using the negative of the identity matrix (which is a negative semidefinite matrix) results in an inverted bowl, as shown in Figure 3.4(b). The negative of a convex function is always a concave function, and vice versa. Therefore, maximizing concave functions is almost exactly similar to minimizing convex functions. 

The function $f ( { \overline { { x } } } ) = { \overline { { x } } } ^ { T }$ Ax corresponds to a perfectly circular bowl, when A is set to the identity matrix (cf. Figures 3.4(a) and 3.5(a)). Changing A from the identity matrix leads to several interesting generalizations. First, if the diagonal entries of A are set to different (nonnegative) values, the circular bowl would become elliptical. For example, if the bowl is stretched twice in one direction as compared to the other, the diagonal entries would be in the ratio of $2 ^ { 2 } : 1 = 4 : 1$ . An example of such a function is following: 

$$
f (x _ {1}, x _ {2}) = 4 x _ {1} ^ {2} + x _ {2} ^ {2}
$$

One can represent this ellipse in matrix form as follows: 

$$
f (x _ {1}, x _ {2}) = [ x _ {1}, x _ {2} ] \left[ \begin{array}{l l} 4 & 0 \\ 0 & 1 \end{array} \right] \left[ \begin{array}{l} x _ {1} \\ x _ {2} \end{array} \right]
$$

The contour plot for this case is shown in Figure 3.5(b). Note that the vertical direction $x _ { 2 }$ is stretched even though the $x _ { 1 }$ direction has diagonal entry of 4. The diagonal entries are inverse squares of stretching factors. 

![image](<Images/03_Eigenvectors_and_Diagonalizable_Matrices_image_007.jpg>)



(a) Circular bowl


![image](<Images/03_Eigenvectors_and_Diagonalizable_Matrices_image_008.jpg>)



(b) Elliptical bowl


![image](<Images/03_Eigenvectors_and_Diagonalizable_Matrices_image_009.jpg>)


![image](<Images/03_Eigenvectors_and_Diagonalizable_Matrices_image_010.jpg>)



(c) Rotated elliptical bowl



(d) Rotated and translated elliptical bowl


Figure 3.5: Contour plots of quadratic functions created with $2 \times 2$ positive semidefinite matrices 

So far, we have only considered quadratic functions in which the stretching occurs along axis-parallel directions. Now, consider the case where we start with the diagonal matrix $\Delta$ and rotate using basis matrix $P _ { 5 }$ , where $P$ contains the two vectors that are oriented at $4 5 ^ { \circ }$ to the axes. Therefore, consider the following rotation matrix: 

$$
P = \left[ \begin{array}{c c} \cos (4 5) & \sin (4 5) \\ - \sin (4 5) & \cos (4 5) \end{array} \right]\tag{3.35}
$$

In this case, we use $A = P \Delta P ^ { T }$ in order to define ${ \overline { { x } } } ^ { T } A { \overline { { x } } }$ . The approach computes the coordinates of $\textstyle { \overline { { x } } }$ as ${ \overline { { y } } } = P ^ { T } { \overline { { x } } }$ , and then computes $f ( { \overline { { x } } } ) = { \overline { { x } } } ^ { T } A { \overline { { x } } } = { \overline { { y } } } ^ { T } \Delta { \overline { { y } } }$ . Note that we are stretching the coordinates of the new basis. The result is a stretched ellipse in the direction of the basis defined by the columns of $P$ (which is a $4 5 ^ { \circ }$ clockwise rotation matrix for column vectors). One can compute the matrix A in this case as follows: 

$$
A = \left[ \begin{array}{c c} \cos (4 5) & \sin (4 5) \\ - \sin (4 5) & \cos (4 5) \end{array} \right] \left[ \begin{array}{c c} 4 & 0 \\ 0 & 1 \end{array} \right] \left[ \begin{array}{c c} \cos (4 5) & \sin (4 5) \\ - \sin (4 5) & \cos (4 5) \end{array} \right] ^ {T} = \left[ \begin{array}{c c} 5 / 2 & - 3 / 2 \\ - 3 / 2 & 5 / 2 \end{array} \right]
$$

One can represent the corresponding function as follows: 

$$
f (x _ {1}, x _ {2}) = [ x _ {1}, x _ {2} ] \left[ \begin{array}{c c} 5 / 2 & - 3 / 2 \\ - 3 / 2 & 5 / 2 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \end{array} \right] = \frac {5}{2} (x _ {1} ^ {2} + x _ {2} ^ {2}) - 3 x _ {1} x _ {2}
$$

The term involving $x _ { 1 } x _ { 2 }$ captures the interactions between the attributes $x _ { 1 }$ and $x _ { 2 }$ . This is the direct result of a change of basis that is no longer aligned with the axis system. The contour plot of an ellipse that is aligned at $4 5 ^ { \circ }$ with the axes is shown in Figure 3.5(c). 

All these cases represent situations where the optimal solution to $f ( x _ { 1 } , x _ { 2 } )$ is at $( 0 , 0 )$ and the resulting function value is 0. How can we generalize to a function with optimum occurring at $\bar { b }$ and an optimum value of $c$ (which is a scalar)? The corresponding function is of the following form: 

$$
f (\overline {{x}}) = (\overline {{x}} - \overline {{b}}) ^ {T} A (\overline {{x}} - \overline {{b}}) + c\tag{3.36}
$$

The matrix A is equivalent to half the Hessian matrix of the quadratic function. The $d \times d$ Hessian matrix $H = [ h _ { i j } ]$ of a function of d variables is a symmetric matrix containing the second-order derivatives with respect to each pair of variables. 

$$
h _ {i j} = \frac {\partial^ {2} f (\overline {{x}})}{\partial x _ {i} \partial x _ {j}}\tag{3.37}
$$

Note that $\scriptstyle { { \overline { { x } } } ^ { T } } H { \overline { { x } } }$ represents the directional second derivative of the function $f ( { \overline { { x } } } )$ along $\scriptstyle { \overline { { x } } }$ (cf. Chapter 4), and it represents the second derivative of the rate of change of $f ( { \overline { { x } } } )$ , when moving along direction x. This value is always nonnegative for convex functions irrespective of x, which ensures that the value of $f ( { \overline { { x } } } )$ is minimum when the first derivative of the rate of change of $f ( { \overline { { x } } } )$ along each direction $\scriptstyle { \overline { { x } } }$ is 0. In other words, the Hessian needs to be positive semidefinite. This is a generalization of the condition $g ^ { \prime \prime } ( x ) \geq 0$ in 1-dimensional convex functions. We make the following assertion, which is shown formally in Chapter 4: 

Observation 3.4.2 Consider a quadratic function, whose quadratic term is of the form ${ \overline { { x } } } ^ { T } A { \overline { { x } } }$ . Then, the quadratic function is convex, if and only if the matrix A is positive semidefinite. 

Many quadratic functions in machine learning are of this form. A specific example is the dual objective function of a support vector machine (cf. Chapter 6). 

One can construct an example of the general form of the quadratic function by translating the $4 5 ^ { \circ }$ -oriented, origin-centered ellipse of Figure 3.5(c). For example, if we center the elliptical objective function at [1, 1] and add 2 to the optimal values, we obtain the function $( \overline { { x } } ^ { \hat { T } } - [ 1 , 1 ] ) \overset { \cdot } { A } ( \overline { { x } } - [ 1 , 1 ] ^ { T } ) + 2$ . The resulting objective function, which takes an optimal value of 2 at [1, 1] is shown below: 

$$
f (x _ {1}, x _ {2}) = \frac {5}{2} (x _ {1} ^ {2} + x _ {2} ^ {2}) - 2 (x _ {1} + x _ {2}) - 3 x _ {1} x _ {2} + 4\tag{3.38}
$$

This type of quadratic objective function is common in many machine learning algorithms. An example of the contour plot of a translated ellipse is shown in Figure $3 . 5 ( \mathrm { d } )$ , although it doe snot show the vertical translation by 2. 

It is noteworthy that the most general form of a quadratic function in multiple variables is as follows: 

$$
f (\overline {{x}}) = \overline {{x}} ^ {T} A ^ {\prime} \overline {{x}} + \overline {{b}} ^ {\prime T} \overline {{x}} + c ^ {\prime}\tag{3.39}
$$

Here, $A ^ { \prime }$ is a $d \times d$ symmetric matrix, $\overline { { b } } ^ { \prime }$ is a d-dimensional column vector, and $c ^ { \prime }$ is a scalar. In the 1-dimensional case, $A ^ { \prime }$ and $\overline { { b } } ^ { \prime }$ are replaced by scalars, and one obtains the familiar form $a x ^ { 2 } + b x + c$ of univariate quadratic functions. Furthermore, as long as $\overline { { b } } ^ { \prime }$ belongs to the column space of $A ^ { \prime }$ , one can convert the general form of Equation 3.39 to the vertex form of Equation 3.36. It is important for $\overline { { b } } ^ { \prime }$ to belong to the column space of $A ^ { \prime }$ for an optimum to exist. For example, the 2-dimensional function is $G ( x _ { 1 } , x _ { 2 } ) = x _ { 1 } ^ { 2 } + x _ { 2 }$ does not have a minimum because the function is partially linear in $x _ { 2 }$ . The vertex form of Equation 3.39 considers only strictly quadratic functions in which all cross-sections of the function are quadratic. Only strictly quadratic functions are interesting for optimization, because linear functions usually do not have a maximum or minimum. One can relate the coefficients of Equations 3.36 and 3.39 as follows: 

$$
A ^ {\prime} = A, \bar {b} ^ {\prime} = - 2 A \bar {b}, c ^ {\prime} = \bar {b} ^ {T} \bar {b} + c
$$

Given $A ^ { \prime } , \bar { b } ^ { \prime }$ and $c ^ { \prime } ,$ the main condition for being able to arrive at the vertex form of Equation 3.36 is the second condition $\bar { b } ^ { \prime } = - 2 A \bar { b } = - 2 A ^ { \prime } \bar { b }$ for which a solution will exist only when $\overline { { b } } ^ { \prime }$ occurs in the column space of $A ^ { \prime }$ . 

Finally, we discuss the case where the matrix A used to create the function ${ \overline { { x } } } ^ { T } A { \overline { { x } } }$ is indefinite, and has both positive and negative eigenvalues. An example of such a function is the following: 

$$
g (x _ {1}, x _ {2}) = [ x _ {1}, x _ {2} ] \left[ \begin{array}{c c} 1 & 0 \\ 0 & - 1 \end{array} \right] \left[ \begin{array}{c} x _ {1} \\ x _ {2} \end{array} \right] = x _ {1} ^ {2} - x _ {2} ^ {2}
$$

The gradient at (0, 0) is 0, which seems to be an optimum point. However, this point behaves like both a maximum and a minimum, when examining second derivatives. If we approach the point from the $x _ { 1 }$ direction, it seems like a minimum. If we approach it from the $x _ { 2 }$ direction, it seems like a maximum. This is because the directional second derivatives in the $x _ { 1 }$ and $x _ { 2 }$ directions are simply twice the diagonal entries (which are of opposite sign). The shape of the objective function resembles that of a riding saddle, and the point $( 0 , 0 )$ is referred to as a saddle point. An example of this type of objective function is shown in Figure 3.6. Objective functions containing such points are often notoriously hard for optimization. 

## 3.4.4 Diagonalization Application: Variable Separation for Optimization

Consider the quadratic function $f ( { \overline { { x } } } ) = { \overline { { x } } } ^ { T } A { \overline { { x } } } + { \overline { { b } } } ^ { T } { \overline { { x } } } + c$ . Unless the symmetric matrix A is diagonal, the resulting function contains terms of the form $x _ { i } x _ { j }$ . Such terms are referred to as interacting terms. Most real-world quadratic functions contain such terms. It is noteworthy that any multivariate quadratic function can be transformed to an additively separable function (without interacting terms) by basis transformation of the input variables of the function. This type of change in basis brings us back to using linear algebra tricks. Additively separable functions are much easier to optimize, because one can decompose the optimization problem into smaller optimization problems on individual variables. For example, a multivariate quadratic function would appear as a simple sum of univariate quadratic functions (each of which is extremely simple to optimize). One can show this simple result by using the linear algebra tricks that we have learned in this chapter. We first define the notion of separable functions: 

Definition 3.4.3 (Additively Separable Functions) A function $F ( x _ { 1 } , x _ { 2 } , \ldots , x _ { d } )$ in d variables is said to be additively separable, if it can be expressed in the following form for appropriately chosen univariate functions $f _ { 1 } ( \cdot ) , f _ { 2 } ( \cdot ) , \ldots f _ { d } ( \cdot )$ 

$$
F (x _ {1}, x _ {2}, \ldots , x _ {d}) = \sum_ {i = 1} ^ {d} f _ {i} (x _ {i})
$$

![image](<Images/03_Eigenvectors_and_Diagonalizable_Matrices_image_011.jpg>)



Figure 3.6: Illustration of quadratic function $g ( x , y ) = x ^ { 2 } - y ^ { 2 }$ created by indefinite matrix


Consider the following quadratic function defined on a d-dimensional vector ${ \begin{array} { r l } { { \overline { { x } } } } & { = } \end{array} } $ $[ x _ { 1 } , \ldots x _ { d } ] ^ { T }$ 

$$
f (\overline {{x}}) = \overline {{x}} ^ {T} A \overline {{x}} + \overline {{b}} ^ {T} \overline {{x}} + c
$$

Since A is a $d \times d$ symmetric matrix, one can diagonalize it as $A = V \Delta V ^ { T }$ , and use the variable transformation ${ \overline { { x } } } = V { \overline { { x } } } ^ { \prime }$ (which is the same as $\overline { { x } } ^ { \prime } = V ^ { T } \overline { { x } } )$ . On performing this transformation one obtains the new function $g ( \overline { { x } } ^ { \prime } ) ~ = ~ f ( V \overline { { x } } ^ { \prime } )$ , which is identical to the original function in a different basis. It is easy to show that the quadratic function may be expressed as follows: 

$$
f (V \overline {{x}} ^ {\prime}) = \overline {{x}} ^ {T} \Delta \overline {{x}} ^ {\prime} + \overline {{b}} ^ {T} V \overline {{x}} ^ {\prime} + c
$$

After this variable transformation, one obtains an additively separable function, because the matrix $\Delta$ is diagonal. One can solve for ${ \overline { { x } } } ^ { \prime }$ using d univariate optimizations, and then transform back ${ \overline { { x } } } ^ { \prime }$ to $\scriptstyle { \overline { { x } } }$ using ${ \overline { { x } } } = V { \overline { { x } } } ^ { \prime }$ 

Although this approach simplifies optimization, the problem is that eigenvector computation of A can be expensive. However, one can generalize this idea and try to find any matrix $V$ (with possibly non-orthogonal columns), which satisfies $A = V \Delta V ^ { T }$ for some diagonal matrix $\Delta .$ . Note that $A \stackrel { \cdot } { = } V \Delta V ^ { T }$ would $\mathrm { n o t ^ { 1 } }$ be a true diagonalization of A if the columns of $V$ are not orthonormal. However, it is good enough to create a separable transformation for optimization, which is what we really care about. The columns of such non-orthogonal matrices are computationally much easier to evaluate than true eigenvectors, and the transformed variables are referred to as conjugate directions. The columns of $V$ are referred to as A-orthogonal directions, because for any pair of (distinct) columns $\overline { { v } } _ { i }$ and $\overline { { v } } _ { j }$ , we have $\overline { { v } } _ { i } ^ { T } A \overline { { v } } _ { j } = \Delta _ { i j } = 0$ . There are an infinite number of possible ways of creating conjugate directions, and the eigenvectors represent a special case. In fact, a generalization of the Gram-Schmidt method can be used to find such directions (cf. Problem 2.7.1). This basic idea forms the principle of the conjugate gradient descent method discussed in Section 5.7.1 of Chapter 5, which can be used even for non-quadratic functions. Here, we provide a conceptual overview of the iterative conjugate gradient method for arbitrary (possibly non-quadratic) function $h ( \overline { { x } } )$ from current point $\overline { { x } } = \overline { { x } } _ { t } .$ 

1. Create a quadratic approximation $f ( { \overline { { x } } } )$ of non-quadratic function $h ( \overline { { x } } )$ using the second-order Taylor expansion of $h ( \overline { { x } } )$ at ${ \overline { { x } } } = { \overline { { x } } } _ { t }$ 

2. Compute the optimal solution $x ^ { * }$ of the quadratic function $f ( { \overline { { x } } } )$ using the separable variable optimization approach discussed above as a set of d univariate optimization problems. 

3. Set $\overline { { x } } _ { t + 1 } = \overline { { x } } ^ { * }$ and $t \Leftarrow t + 1$ . Go back to step 1. 

The approach is iterated to convergence. The aforementioned algorithm provides the conceptual basis for the conjugate gradient method. The detailed method is provided in Section 5.7.1 of Chapter 5. 

## 3.4.5 Eigenvectors in Norm-Constrained Quadratic Programming

A problem that arises frequently in different types of machine learning settings is one in which we wish to optimize $\check { x } ^ { T } A \bar { x }$ , where $\textstyle { \overline { { x } } }$ is constrained to unit norm. Here, A is a $d \times d$ symmetric data matrix. This type of problem arises in many feature engineering and dimensionality reduction applications like principal component analysis, singular value decomposition, and spectral clustering. Such an optimization problem is posed as follows: 

$$
\begin{array}{c} \text {Optimize} \overline {{x}} ^ {T} A \overline {{x}} \\ \text {subject to:} \\ \| \overline {{x}} \| ^ {2} = 1 \end{array}
$$

The optimization problem can be in either minimization or maximization form. Constraining the vector $\textstyle { \overline { { x } } }$ to be the unit vector fundamentally changes the nature of the optimization problem. Unlike the previous section, it is no longer important whether the matrix A is positive semidefinite or not. One would have a well-defined optimal solution, even if the matrix A is indefinite. Constraining the norm of the vector helps in avoiding vectors with unbounded magnitudes or trivial solutions (like the zero vector), even when the matrix A is indefinite. 

Let $\overline { { v } } _ { 1 } \ldots \overline { { v } } _ { d }$ be the d orthonormal eigenvectors of the symmetric matrix A. Note that the set of eigenvectors creates a basis for $\mathcal { R } ^ { d }$ , and therefore any d-dimensional vector $\textstyle { \overline { { x } } }$ can be expressed as a linear combination of $\overline { { v } } _ { 1 } \ldots \overline { { v } } _ { d }$ as follows: 

$$
\overline {{x}} = \sum_ {i = 1} ^ {d} \alpha_ {i} \overline {{v}} _ {i}\tag{3.40}
$$

We will re-parameterize this optimization problem in terms of the parameters $\alpha _ { 1 } \ldots \alpha _ { d }$ by substituting for x in the optimization problem. By making this substitution, and setting each $A { \overline { { v } } } _ { i } = \lambda _ { i } { \overline { { v } } } _ { i }$ , we obtain the following re-parameterized optimization problem: 

$$
\begin{array}{l} \text { Optimize } \sum_ {i = 1} ^ {d} \lambda_ {i} \alpha_ {i} ^ {2} \\ \text { subject   to: } \\ \sum_ {i = 1} ^ {d} \alpha_ {i} ^ {2} = 1 \end{array}
$$

The expression $\| { \overline { { x } } } \| ^ { 2 }$ in the constraint is simplified to $\begin{array} { r l } { \quad } & { { } ( \sum _ { i = 1 } ^ { d } \alpha _ { i } \overline { { v } } _ { i } ) \cdot ( \sum _ { i = 1 } ^ { d } \alpha _ { i } \overline { { v } } _ { i } ) } \end{array}$ ; we can expand it using the distributive property, and then we use the orthogonality of the eigenvectors to set ${ \overline { { v } } } _ { i } \cdot { \overline { { v } } } _ { j } = 0$ . The objective function value is $\textstyle \sum _ { i } \lambda _ { i } \alpha _ { i } ^ { 2 }$ , where the different $\alpha _ { i } ^ { 2 }$ sum to 1. Clearly, the minimum and maximum possible values of this objective function are achieved by setting the weight $\alpha _ { i } ^ { 2 }$ of a single value of $\lambda _ { i }$ to 1, which corresponds to the minimum or maximum possible eigenvalue (depending on whether the optimization problem is posed in minimization or maximization form): 

The maximum value of the norm-constrained quadratic optimization problem is obtained by setting x to the largest eigenvector of A. The minimum value is obtained by setting x to the smallest eigenvector of A. 

This problem can be generalized to finding a k-dimensional subspace. In other words, we want to find orthonormal vectors ${ \overline { { x } } } _ { 1 } \ldots { \overline { { x } } } _ { k } .$ , so that $\textstyle \sum _ { i } { \overline { { x } } } _ { i } A { \overline { { x } } } _ { i }$ is optimized: 

$$
\begin{array}{l} \text {Optimize} \sum_ {i = 1} ^ {k} \overline {{x}} _ {i} ^ {T} A \overline {{x}} _ {i} \\ \text {subject to:} \\ \| \overline {{x}} _ {i} \| ^ {2} = 1 \forall i \in \{1 \ldots k \} \\ \overline {{x}} _ {1} \ldots \overline {{x}} _ {k} \text {are mutually orthogonal} \end{array}
$$

The optimal solution to this problem can be derived using a similar procedure. We provide an alternative solution with the use of Lagrangian relaxation in Section 6.6 of Chapter 6. Here, we simply state the optimal solution: 

The maximum value of the norm-constrained quadratic optimization problem is obtained by using the largest k eigenvectors of A. The minimum value is obtained by using the smallest k eigenvectors of A. 

Intuitively, these results make geometric sense from the perspective of the anisotropic scal ing caused by symmetric matrices like A. The matrix A distorts the space with scale fac tors corresponding to the eigenvalues along orthonormal directions corresponding to the eigenvectors. The objective function tries to either maximize or minimize the aggregate projections of the distorted vectors $A { \overline { { x } } } _ { i }$ on the original vectors $\overline { { x } } _ { i }$ , which is sum of the dot products between $\overline { { x } } _ { i }$ and $A { \overline { { x } } } _ { i }$ . By picking the largest k eigenvectors (scaling directions), this sum is maximized. On the other hand, by picking the smallest k directions, this sum is minimized. 

## 3.5 Numerical Algorithms for Finding Eigenvectors

The simplest approach for finding eigenvectors of a d d matrix A is to first find the d roots $\lambda _ { 1 } \ldots \lambda _ { d }$ of the equation det $( A - \lambda I ) = 0$ . Some of the roots might be repeated. In the next step, one has to solve linear systems of the form $( A - \lambda _ { j } I ) \overline { { x } } = 0$ . This can be done using the 

Gaussian elimination method (cf. Section 2.5.4 of Chapter 2). However, polynomial equation solvers are sometimes numerically unstable and have a tendency to show ill-conditioning in real-world settings. Finding the roots of a polynomial equation is numerically harder than finding eigenvalues of a matrix! In fact, one of the many ways in which high-degree polynomial equations are solved in engineering disciplines is to first construct a companion matrix of the polynomial, such that the matrix has the same characteristic polynomial, and then find its eigenvalues: 

Problem 3.5.1 (Companion Matrix) Consider the following matrix: 

$$
A _ {2} = \left[ \begin{array}{c c} 0 & 1 \\ - c & - b \end{array} \right]
$$

Discuss why the roots of the polynomial equation $x ^ { 2 } + b x + c = 0$ can be computed using the eigenvalues of this matrix. Also show that finding the eigenvalues of the following $3 \times 3$ matrix yields the roots of $x ^ { 3 } + b x ^ { 2 } + c x + d = 0$ 

$$
A _ {3} = \left[ \begin{array}{c c c} 0 & 1 & 0 \\ 0 & 0 & 1 \\ - d & - c & - b \end{array} \right]
$$

Note that the matrix has a non-zero row and superdiagonal of 1s. Provide the general form of the $t \times t$ matrix $A _ { t }$ required for solving the polynomial equation $\begin{array} { r } { x ^ { t } + \sum _ { i = 0 } ^ { t - 1 } \hat { a _ { i } x ^ { i } } = 0 } \end{array}$ 

In some cases, algorithms for finding eigenvalues also yield the eigenvectors as a byproduct, which is particularly convenient. In the following, we present alternatives both for finding eigenvalues and for finding eigenvectors. 

## 3.5.1 The QR Method via Schur Decomposition

The QR algorithm uses the following two steps alternately in an iterative way: 

1. Decompose the matrix $A = Q R$ using the QR algorithm discussed in Section 2.7.2. Here, R is an upper-triangular matrix and Q is an orthogonal matrix. 

2. Iterate by using $A \Leftarrow Q ^ { T } A Q$ and go to the previous step. 

The matrix $Q ^ { T } A Q$ is similar to A, and therefore it has the same eigenvalues. A key result<sup>2</sup> is that applying the transformation $A \Leftarrow Q ^ { T } A Q$ repeatedly to A results in the uppertriangular matrix U of the Schur decomposition. In fact, if we keep track of the orthogonal matrices $Q _ { 1 } \ldots Q _ { s }$ obtained using QR decomposition (in that order) and denote their prod uct $Q _ { 1 } Q _ { 2 } \dots Q _ { s }$ by the single orthogonal matrix P, one can obtain the Schur decomposition of A in the following form: 

$$
A = P U P ^ {T}
$$

The diagonal entries of this converged matrix U contain the eigenvalues. In general, the triangulization of a matrix is a natural way of finding its eigenvalues. After the eigenvalues $\lambda _ { 1 } \ldots \lambda _ { d }$ have been found, the eigenvectors can be found by solving equations of the form $( A - \lambda _ { j } I ) \overline { { x } } = 0$ using the methods of Section 2.5.4 in Chapter 2. This approach is not fully optimized for computational speed, which can be improved by first transforming the matrix to Hessenberg form. The reader is referred to [52] for a detailed discussion. 

## 3.5.2 The Power Method for Finding Dominant Eigenvectors

The power method finds the eigenvector with the largest absolute eigenvalue of a matrix, which is also referred to as its dominant eigenvector or principal eigenvector. One caveat is that it is possible for the principal eigenvalue of a matrix to be complex, in which case the power method might not work. The following discussion assumes that the matrix has real-valued eigenvectors/eigenvalues, which is the case in many real-world applications. Furthermore, we usually do not need all the eigenvectors, but only the top few eigenvectors. The power method is designed to find only the top eigenvector, although it can be used to find the top few eigenvectors with some modifications. Unlike the QR method, one can find eigenvectors and eigenvalues simultaneously, without the need to solve systems of equations after finding the eigenvalues. The power method is an iterative method, and the underlying iterations are also referred to as von Mises iterations. 

Consider a $d \times d$ matrix A, which is diagonalizable with real eigenvalues. Since A is a diagonalizable matrix, multiplication with A results in anisotropic scaling. If we multiply any column vector $\overline { { x } } \in \mathcal { R } ^ { d }$ with A to create Ax, it will result in a linear distortion of x, in which directions corresponding to larger (absolute) eigenvalues are stretched to a greater degree. As a result, the (acute) angle between Ax and the largest eigenvector v will reduce from that between $\textstyle { \overline { { x } } }$ and v. If we keep repeating this process, the transformations will eventually result in a vector pointing in the direction of the largest (absolute) eigenvector. Therefore, the power method starts by first initializing the d components of the vector x to random values from a uniform distribution in [ 1, 1]. Subsequently, the following von Mises iteration is repeated to convergence: 

$$
\overline {{x}} \Leftarrow \frac {A \overline {{x}}}{\| A \overline {{x}} \|}
$$

Note that normalization of the vector in each iteration is essential to prevent overflow or underflow to arbitrarily large or small values. After convergence to the principal eigenvector v, one can compute the corresponding eigenvalue as the ratio of $\overline { { v } } ^ { T } \bar { A } \overline { { v } }$ to $\| \overline { { v } } \| ^ { 2 }$ , which is referred to as the Raleigh quotient. 

We now provide a formal justification. Consider a situation in which we represent the starting vector $\textstyle { \overline { { x } } }$ as a linear combination of the basis of d eigenvectors $\overline { { v } } _ { 1 } \ldots \overline { { v } } _ { d }$ with coefficients $\alpha _ { 1 } \ldots \alpha _ { d } \colon$ 

$$
\overline {{x}} = \sum_ {i = 1} ^ {d} \alpha_ {i} \overline {{v}} _ {i}\tag{3.41}
$$

If the eigenvalue of $\overline { { v } } _ { i }$ is $\lambda _ { i }$ , then multiplying with $A ^ { t }$ has the following effect: 

$$
A ^ {t} \overline {{x}} = \sum_ {i = 1} ^ {t} \alpha_ {i} A ^ {t} \overline {{v}} _ {i} = \sum_ {i = 1} ^ {t} \alpha_ {i} \lambda_ {i} ^ {t} \overline {{v}} _ {i} \propto \sum_ {i = 1} ^ {t} \alpha_ {i} (- 1) ^ {t} \frac {| \lambda_ {i} | ^ {t}}{\sum_ {j = 1} ^ {t} | \lambda_ {j} | ^ {t}} \overline {{v}} _ {i}
$$

When t becomes large, the quantity on the right-hand side will be dominated by the effect of the largest eigenvector. This is because the factor $| \lambda _ { 1 } ^ { t } |$ increases the proportional weight of the first eigenvector, when $\lambda _ { 1 }$ is the (strictly) largest eigenvalue. The fractional value $| \lambda _ { 1 } ^ { t } | / { \sum _ { j = 1 } ^ { t } | \lambda _ { j } ^ { t } | }$ will converge to 1 for the largest (absolute) eigenvector and to 0 for all others. As a result, the normalized version of $A ^ { t } { \overline { { x } } }$ will point in the direction of the largest (absolute) eigenvector $\overline { { v } } _ { 1 }$ . Note that this proof does depend on the fact that $\lambda _ { 1 }$ is strictly greater than the next eigenvalue, or else the convergence will not occur. Furthermore, if the top-2 eigenvalues are too similar, the convergence will be slow. However, large machine learning matrices $( \mathrm { e . g . }$ , covariance matrices) are often such that the top few eigenvalues are quite different in magnitude, and most of the similar eigenvalues are at the bottom with values of 0. Furthermore, even when there are ties in the eigenvalues, the power method tends to find a vector that lies within the span of the tied eigenvectors. 

Problem 3.5.2 (Inverse Power Iteration) Let A be an invertible matrix. Discuss how you can use $A ^ { - 1 }$ to discover the smallest eigenvector and eigenvalue of A in absolute magnitude. 

## Finding the Top-k Eigenvectors for Symmetric Matrices

In most machine learning applications, one is looking not for the top eigenvector, but for the top-k eigenvectors. It is possible to use the power method to find the top-k eigenvectors. In symmetric matrices, the eigenvectors $\overline { { v } } _ { 1 } \ldots \overline { { v } } _ { d }$ , which define the columns of the basis matrix V, are orthonormal according to the following diagonalization: 

$$
A = V \Delta V ^ {T}\tag{3.42}
$$

The above relationship can also be rearranged in terms of the column vectors of V and the eigenvalues $\lambda _ { 1 } \ldots \lambda _ { d }$ of $\Delta { \mathrm { i } }$ : 

$$
A = V \Delta V ^ {T} = \sum_ {i = 1} ^ {d} \lambda_ {i} [ \overline {{v}} _ {i} \overline {{v}} _ {i} ^ {T} ]\tag{3.43}
$$

This result follows from the fact that any matrix product can be expressed as the sum of outer products (cf. Lemma 1.2.1 of Chapter 1). Applying Lemma 1.2.1 to the product of $( V \Delta )$ and $V ^ { T }$ yields the above result. The decomposition implied by Equation 3.43 is referred to as a spectral decomposition of the matrix A. Each $\bar { v _ { i } } \bar { v } _ { i } ^ { T }$ is a rank-1 matrix of size $d \times d ,$ , and $\lambda _ { i }$ is the weight of this matrix component. As discussed in Section 7.2.3 of Chapter 7, spectral decomposition can be applied to any type of matrix (and not just symmetric matrices) using an idea referred to as singular value decomposition. 

Consider the case in which we have already found the top eigenvector $\lambda _ { 1 }$ with eigenvalue $\overline { { v } } _ { 1 }$ . Then, one can remove the effect of the top eigenvalue by creating the following modified matrix: 

$$
A ^ {\prime} = A - \lambda_ {1} \overline {{v}} _ {1} \overline {{v}} ^ {T}\tag{3.44}
$$

As a result, the second largest eigenvalue of A becomes the dominant eigenvalue of $A ^ { \prime }$ Therefore, by repeating the power iteration with $A ^ { \prime }$ , one can now determine the second largest eigenvector. The process can be repeated any number of times. 

When the matrix A is sparse, one disadvantage of this method is that $A ^ { \prime }$ might not be sparse. Sparsity is a desirable feature of matrix representations, because of the spaceand time-efficiency of sparse matrix operations. However, it is not necessary to represent the dense matrix $A ^ { \prime }$ explicitly. The matrix multiplication $A ^ { \prime } { \overline { { x } } }$ for the power method can be accomplished using the following relationship: 

$$
A ^ {\prime} \overline {{x}} = A \overline {{x}} - \lambda_ {1} \overline {{v}} _ {1} (\overline {{v}} _ {1} ^ {T} \overline {{x}})\tag{3.45}
$$

It is important to note how we have bracketed the second term on the right-hand side. This avoids the explicit computation of a rank-1 matrix (which is dense), and it can be accomplished with simple dot product computation between $\overline { { v } } _ { 1 }$ and x. This is an example of the fact that the associativity property of matrix multiplication is often used to ensure the best efficiency of matrix multiplication. One can also generalize these ideas to finding the top-k eigenvectors by removing the effect of the top-r eigenvectors from A when finding the (r + 1)th eigenvector. 

Problem 3.5.3 (Generalization to Asymmetric Matrices) The power method is de signed to find the single largest eigenvector. The approach for finding the top-k eigenvectors makes the additional assumption of a symmetric matrix. Discuss where the assumption of a symmetric matrix was used in this section. Can you find a way to generalize the approach to arbitrary matrices assuming that the top-k eigenvalues are distinct? 

A hint for the above problem is that the left eigenvectors and right eigenvectors may not be the same in asymmetric matrices (as in symmetric matrices) and both are needed in order to subtract the effect of dominant eigenvectors. 

Problem 3.5.4 (Finding Largest Eigenvectors) The power method finds the top-k eigenvectors of largest absolute magnitude. In most applications, we also care about the sign of the eigenvector. In other words, an eigenvalue of +1 is greater than 2, when sign is considered. Show how you can modify the power method to find the top-k eigenvectors of a symmetric matrix when sign is considered. 

The key point in the above exercise is to translate the eigenvalues to nonnegative values by modifying the matrix using the ideas already discussed in this section. 

## 3.6 Summary

Diagonalizable matrices represent a form of linear transformation, so that multiplication of a vector with such a matrix corresponds to anisotropic scaling of the vector in (possibly non-orthogonal) directions. Not all matrices are diagonalizable. Symmetric matrices are always diagonalizable, and they can be represented as scaling transformations in mutually orthogonal directions. When the scaling factors of symmetric matrices are nonnegative, they are referred to as positive semidefinite matrices. Such matrices frequently arise in different types of machine learning applications. Therefore, this chapter has placed a special emphasis on these types of matrices and their eigendecomposition properties. We also introduce a number of key optimization applications of such matrices, which sets the stage for more detailed discussions in later chapters. 

## 3.7 Further Reading

The concepts of diagonalization are discussed in the books by Strang [122, 123], David Lay [77], Hofman-Kunze [62], and Golub and Van Loan [52]. A discussion of numerical methods that combine linear algebra and optimization is provided in [99]. The field of convex optimization is studied in detail in [22]. 

## 3.8 Exercises

1. In Chapter 2, you learned that any d d orthogonal matrix A can be decomposed into $O ( d ^ { 2 } )$ Givens rotations and at most one elementary reflection. Discuss how the sign of the determinant of A determines whether or not a reflection is needed. 

2. In Chapter 2, you learned that any d d matrix A can be decomposed into at most O(d) Householder reflections. Discuss the effect of the sign of the determinant on the number of Householder reflections. 

3. Show that if a matrix A satisfies $A ^ { 2 } = 4 I$ , then all eigenvalues of A are 2 and 2. 

4. You are told that a 4 4 symmetric matrix has eigenvalues 4, 3, 2, and 2. You are given the values of eigenvectors belonging to the eigenvalues 4 and 3. Provide a procedure to reconstruct the entire matrix. [Hint: One eigenvalue is repeated and the matrix is symmetric.] 

5. Suppose that A is a square $d \times d$ matrix. The matrix $A ^ { \prime }$ is obtained by multiplying the ith row of A with $\gamma _ { i }$ and dividing the ith column of A with $\gamma _ { i }$ for each i. How are the eigenvectors of A are related to those of $A ^ { \prime } ?$ [Hint: Relate A and $A ^ { \prime }$ with matrix operators.] 

6. For a $4 \times 4$ matrix A with the following list of eigenvalues obtained from the characteristic polynomial, state in each case whether the matrix is guaranteed to be diagonalizable, invertible, both, or neither: (a) $\{ \lambda _ { 1 } , \lambda _ { 2 } , \lambda _ { 3 } , \lambda _ { 4 } \} = \{ 1 , 3 , 4 , 9 \}$ (b) $\{ \lambda _ { 1 } , \lambda _ { 2 } , \lambda _ { 3 } , \lambda _ { 4 } \} \ = \ \{ 1 , 3 , 3 , 9 \} \ ( \mathrm { c } ) \ \{ \lambda _ { 1 } , \lambda _ { 2 } , \lambda _ { 3 } , \lambda _ { 4 } \} \ = \ \{ 0 , 3 , 4 , 9 \} \ ( \mathrm { d } ) \ \{ \lambda _ { 1 } , \lambda _ { 2 } , \lambda _ { 3 } , \lambda _ { 4 } \} \ = \ 0 \ 3 ,$ 0, 3, 3, 9 (e) $\{ \lambda _ { 1 } , \lambda _ { 2 } , \lambda _ { 3 } , \lambda _ { 4 } \} = \{ 0 , 0 , 4 , 9 \}$ 

7. Show that any real-valued matrix of odd dimension must have at least one real eigen value. Show the related fact that the determinant of a real-valued matrix without any real eigenvalues is always positive. Furthermore, show that a real-valued matrix of even dimension with a negative determinant must have at least two distinct real valued eigenvalues. [Hint: Properties of polynomial roots.] 

8. In the Jordan normal form $A = V U V ^ { - 1 }$ , the upper triangular matrix U is in block diagonal form, where smaller upper-triangular matrices $U _ { 1 } \ldots U _ { r }$ are arranged along the diagonal of U. What is the effect of applying a polynomial function $f ( U )$ on the individual blocks $U _ { 1 } \dots U _ { r } ?$ Use this fact to provide a general proof of the Cayley Hamilton theorem. [Hint: Strictly triangular matrices are nilpotent.] 

9. Provide an example of a defective matrix whose square is diagonalizable. [Hint: Con struct a singular matrix in Jordan normal form.] 

10. Let A and B be $d \times d$ matrices. Show that the matrix $A B - B A$ can never be positive semidefinite unless it is the zero matrix. [Hint: Use properties of the trace.] 

11. Can the square of a matrix that does not have real eigenvalues be diagonalizable with real eigenvalues? If no, provide a proof. If yes, provide an example. 

12. If the matrices A, B, and AB are all symmetric, show that the matrices A and B must be simultaneously diagonalizable. [Hint: See Problem 1.2.7 in Chapter 1.] 

13. Suppose that the $d \times d$ matrix S is symmetric, positive semidefinite matrix, and the matrix D is of size $n \times d .$ Show that $D S D ^ { T }$ must also be a symmetric, positive semidefinite matrix. Note that $D S D ^ { T }$ is a matrix of inner products between rows of D, which is a generalization of the dot product matrix $D D ^ { \bar { T } }$ 

14. Let S be a positive semidefinite matrix, which can therefore be expressed in Gram matrix form as $S = B ^ { T } B$ (Lemma 3.3.14). Use this fact to show that a diagonal entry can never be negative. What does this imply for the convexity of quadratic functions? 

15. Show that if a matrix P satisfies $P ^ { 2 } = P .$ , then all its eigenvalues must be 1 or 0. 

16. Show that a matrix A is always similar to its transpose $A ^ { T }$ . [Hint: Show that if A is similar to U, then $A ^ { T }$ is similar to $U ^ { T }$ . Then show that a matrix U in Jordan normal form is similar to its transpose with the use of a permutation matrix.] 

17. Let x be a right eigenvector (column vector) of square matrix A with eigenvalue $\lambda _ { r }$ Let y be a left eigenvector (row vector) of A with eigenvalue $\lambda _ { l } \neq \lambda _ { r }$ . Show that x and $\overline { { y } } ^ { T }$ are orthogonal. [Hint: The spectral theorem contains a special case of this result. Problem 3.3.6 is also a special case for diagonalizable matrices.] 

18. True or False? (a) A matrix with all zero eigenvalues must be the zero matrix. (b) A symmetric matrix with all zero eigenvalues must be the zero matrix. 

19. Show that if λ is a non-zero eigenvalue of $A B ,$ , then it must also be a non-zero eigenvalue of BA. Why does this argument not work for zero eigenvalues? Furthermore, show that if either A or B is invertible, then AB and BA are similar. 

20. Is the quadratic function $f ( x _ { 1 } , x _ { 2 } , x _ { 3 } ) = 2 x _ { 1 } ^ { 2 } + 3 x _ { 2 } ^ { 2 } + 2 x _ { 3 } ^ { 2 } - 3 x _ { 1 } x _ { 2 } - x _ { 2 } x _ { 3 } - 2 x _ { 1 } x _ { 3 }$ convex? How about the function $g ( x _ { 1 } , x _ { 2 } , x _ { 3 } ) = 2 x _ { 1 } ^ { 2 } - 3 x _ { 2 } ^ { 2 } + 2 x _ { 3 } ^ { 2 } - 3 x _ { 1 } x _ { 2 } - x _ { 2 } x _ { 3 } - 2 x _ { 1 } x _ { 3 } \uparrow$ In each case, find the minimum of the objective function, subject to the constraint that the norm of $[ x _ { 1 } , x _ { 2 } , x _ { 3 } ] ^ { T }$ is 1. 

21. Consider the function $f ( x _ { 1 } , x _ { 2 } ) = x _ { 1 } ^ { 2 } + 3 x _ { 1 } x _ { 2 } + 6 x _ { 2 } ^ { 2 }$ . Propose a linear transformation of the variables so that the function is separable in terms of the new variables. Use the separable form of the objective function to find an optimal solution. 

22. Show that the difference between two similar, symmetric matrices must be indefinite, unless both matrices are the same. [Hint: Use properties of the trace.] 

23. Show that an nth root of a d d diagonalizable matrix can always be found, as long as we allow for complex roots. Provide a geometric interpretation of the resulting matrix in terms of its relationship to the original matrix in the case where the root is a real-valued matrix. 

24. Generate the equation of an ellipsoid centered at $[ 1 , - 1 , 1 ] ^ { T }$ , and whose axes directions are the orthogonal vectors $[ 1 , 1 , 1 ] ^ { T } , [ 1 , - 2 , 1 ] ^ { \dot { T } }$ , and $[ \bar { 1 } , 0 , - 1 ] ^ { T }$ . The ellipsoid is stretched in these directions in the ratio 1 : 2 : 3. The answer to this question is not unique, and it depends on the size of your ellipsoid. Use the matrix form of ellipsoids discussed in the chapter. [Be careful about the mapping of the stretching ratios to the eigenvalues of this matrix both in terms of magnitude and relative ordering.] 

25. If A and B are symmetric matrices whose eigenvalues lie in $[ \lambda _ { 1 } , \lambda _ { 2 } ]$ and $[ \gamma _ { 1 } , \gamma _ { 2 } ]$ , respectively, show that the eigenvalues of $A - B$ lie in $\left[ \lambda _ { 1 } - \gamma _ { 2 } , \lambda _ { 2 } - \gamma _ { 1 } \right]$ . [Think geometrically about the effect of the multiplication of a vector with $( A - B )$ . Also think of the norm-constrained optimization problem of $\overline { { x } } ^ { T } C \overline { { x } }$ for C chosen appropriately.] 

26. Nilpotent Matrix: Consider a non-zero, square matrix A satisfying $A ^ { k } = 0$ for some k. Such a matrix is referred to as nilpotent. Show that all eigenvalues are 0 and such a matrix is defective. 

27. Show that A is diagonalizable in each case if (i) it satisfies $A ^ { 2 } = A$ , and (ii) it satisfies $A ^ { 2 } = I$ 

28. Elementary Row Addition Matrix Is Defective: Show that the $d \times d$ elementary row addition matrix with 1s on the diagonal and a single non-zero of-diagonal entry is not diagonalizable. 

29. Symmetric and idempotent matrices: Show that any $n \times n$ matrix P satisfying $P ^ { 2 } = P$ and $P = P ^ { T }$ can be expressed in the form $Q Q ^ { T }$ for some $n \times d$ matrix Q with orthogonal columns (and is hence an alternative definition of a projection matrix). 

30. Diagonalizability and Nilpotency: Show that every square matrix can be expressed as the sum of a diagonalizable matrix and a nilpotent matrix (including zero matrices for either part). 

31. Suppose you are given the Cholesky factorization $L L ^ { T }$ of a positive-definite matrix A. Show how to compute the inverse of A using multiple applications of back substitution. 

32. Rotation in 3-d with arbitrary axis: Suppose that the vector $[ 1 , 2 , - 1 ] ^ { T }$ is the axis of a counter-clockwise rotation of θ degrees, just as $[ 1 , 0 , 0 ] ^ { T }$ is the axis of the counter-clockwise θ-rotation of a column vector with the Givens matrix: 

$$
R _ {[ 1, 0, 0 ]} = \left[ \begin{array}{c c c} 1 & 0 & 0 \\ 0 & \cos (\theta) & - \sin (\theta) \\ 0 & \sin (\theta) & \cos (\theta) \end{array} \right]
$$

Create a new orthogonal basis system of $\mathcal { R } ^ { 3 }$ that includes $[ 1 , 2 , - 1 ] ^ { T }$ . Now use the concept of similarity $R _ { [ 1 , 2 , - 1 ] } = P R _ { [ 1 , 0 , 0 ] } P ^ { T }$ to create a $6 0 ^ { \circ }$ rotation matrix M about the axis $[ 1 , 2 , - 1 ] ^ { T }$ . The main point is in knowing how to infer P from the aforementioned orthogonal basis system. Be careful of avoiding inadvertent reflections during the basis transformation by checking det $( P )$ . Now show how to recover the axis and angle of rotation from M using complex-valued diagonalization. [Hint: The eigenvalues are the same for similar matrices and the axis of rotation is an invariant direction.] 

33. Show how you can use the Jordan normal form of a matrix to quickly identify its rank and its four fundamental subspaces. 

34. Consider the following quadratic form: 

$$
f (x _ {1}, x _ {2}, x _ {3}) = x _ {1} ^ {2} + 2 x _ {2} ^ {2} + x _ {3} ^ {2} + a x _ {1} x _ {2} + x _ {2} x _ {3}
$$

Under what conditions on a is the function $f ( x _ { 1 } , x _ { 2 } , x _ { 3 } )$ convex? 

35. Useful for Kernel Methods: Consider an $n \times n$ non-singular matrix $A = B B ^ { T }$ which is the left Gram matrix of $n \times n$ matrix B. Propose an algorithm that takes $B$ as input and generates 100 different matrices, $B _ { 1 } \ldots B _ { 1 0 0 }$ , such that A is the left Gram matrix of each $B _ { i }$ . How many such matrices exist? Is it possible to obtain a $B _ { i }$ that is also symmetric like $A ?$ Is any $B _ { i }$ triangular? [Note: For an $n \times n$ similarity matrix A, the kth row of $B _ { i }$ is a multidimensional representation of the kth object.] 

36. Let P be an $n \times n$ nonnegative stochastic transition matrix of probabilities, so that the probabilities in each row sum to 1. Find a right eigenvector with eigenvalue 1 by inspection. Prove that no eigenvalue can be larger than 1. 

37. Suppose that $\begin{array} { r c l } { A } & { = } & { V \Delta V ^ { - 1 } } \end{array}$ is a diagonalizable matrix. Show that the matrix $\scriptstyle \operatorname* { l i m } _ { n \to \infty } ( I + A / n ) ^ { n }$ exists with finite entries. [This result holds for any square matrix, and the proof for the general case is a good challenge exercise.] 

38. Eigenvalues are scaling factors along specific directions. Construct a $2 \times 2$ diagonalizable matrix A and 2-dimensional vector x, so that each eigenvalue of A is less than 1 in absolute magnitude and the length of Ax is larger than that of x. Prove that any such matrix A cannot be symmetric. Explain both phenomena geometrically. 

39. Mahalanobis distance: Let $C = D ^ { T } D / n$ be the covariance matrix of an $n \times d$ mean-centered data set. The squared Mahalanobis distance of the ith row ${ \overline { { X } } } _ { i }$ of D to the mean of the data set (which is the origin in this case) is given by the following: 

$$
\delta_ {i} ^ {2} = \overline {{X}} _ {i} C ^ {- 1} \overline {{X}} _ {i} ^ {T}
$$

Let $C = P \Delta P ^ { T }$ be the diagonalization of $C ,$ and each row vector ${ \overline { { X } } } _ { i }$ be transformed to ${ \overline { { Z } } } _ { i } = { \overline { { X } } } _ { i } P$ . Normalize each attribute of the transformed data matrix $D P$ by dividing with its standard derivation to make its variance 1 along each dimension and to create the new rows $\overline { { Z } } _ { 1 } ^ { \prime } \ldots \overline { { Z } } _ { n } ^ { \prime }$ . Show that the Mahalanobis distance $\delta _ { i }$ is equal to $\| \overline { { Z } } _ { i } ^ { \prime } \|$ 

40. Non-orthogonal diagonalization of symmetric matrix: Consider the following diagonalization of a symmetric matrix: 

$$
{\left[ \begin{array}{l l l} 3 & 0 & 1 \\ 0 & 4 & 0 \\ 1 & 0 & 3 \end{array} \right]} = {\left[ \begin{array}{l l l} 1 / \sqrt {2} & 0 & 1 / \sqrt {2} \\ 0 & 1 & 0 \\ 1 / \sqrt {2} & 0 & - 1 / \sqrt {2} \end{array} \right]} {\left[ \begin{array}{l l l} 4 & 0 & 0 \\ 0 & 4 & 0 \\ 0 & 0 & 2 \end{array} \right]} {\left[ \begin{array}{l l l} 1 / \sqrt {2} & 0 & 1 / \sqrt {2} \\ 0 & 1 & 0 \\ 1 / \sqrt {2} & 0 & - 1 / \sqrt {2} \end{array} \right]}
$$

Find an alternative diagonalization $V \Delta V ^ { - 1 }$ in which at least some column pairs of V are not orthogonal. [Hint: Try modifying this diagonalization using tied eigenvectors.] 

41. You have a 100000 100 sparse matrix D, and you want to compute the dominant eigenvector of its left Gram matrix $D D ^ { T }$ . Unfortunately, $D D ^ { T }$ is a non-sparse matrix of size $1 0 0 0 0 0 \times 1 0 0 0 0 0$ , which causes computational problems. Show how you can implement the power method using only sparse matrix-vector multiplications. 

42. Multiple choice: Suppose $\overline { { x } } _ { i } ^ { T } A \overline { { x } } _ { i } > 0$ for d vectors $\overline { { x } } _ { 1 } \ldots \overline { { x } } _ { d }$ and $d \times d$ symmetric matrix A. Then, A is always positive definite if the different $\overline { { x } } _ { i } \mathrm { ^ { * } s }$ are (i) linearly independent, (ii) orthogonal, (iii) A-orthogonal, (iv) any of the above, or (v) none of the above? Justify your answer. 

43. Convert the diagonalization in the statement of Exercise 40 into Gram matrix form $A = B ^ { T } B$ and then compute the Cholesky factorization $A = L L ^ { T } = R ^ { T } R$ using the QR decomposition $B = Q R$ 