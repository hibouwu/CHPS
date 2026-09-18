Chapter 2 

# Linear Transformations and Linear Systems

“You can’t criticize geometry. It is never wrong.”– Paul Rand 

## 2.1 Introduction

Machine learning algorithms work with data matrices, which can be viewed as collections of row vectors or as collections of column vectors. For example, one can view the rows of an n d data matrix D as a set of n points in a space of dimensionality d, and one can view the columns as features. These collections of row vectors and column vectors define vector spaces. In this chapter, we will introduce the basic properties of vector spaces and their connections to solving linear systems of equations. This problem is also a special case of the problem of linear regression, which is one of the fundamental building blocks of machine learning. 

We will also study matrix multiplication as a linear operator with geometric interpretation. As discussed in Section 1.3.2 of Chapter 1, multiplying a matrix with a vector can be used to implement rotation, scaling, and reflection operations on the vector. In fact, a multiplication of a vector with a matrix can be shown to be some combination of rotation, scaling, and reflection being applied to the vector. Much of linear algebra draws inspirations from Cartesian geometry. However, Cartesian geometry is often studied in only 2 or 3 dimensions On the other hand, linear algebra is naturally defined in spaces of any dimensionality. 

This chapter is organized as follows. The remainder of this section introduces the con cept of linear transformations. The next section provides a provides a basic understanding of the geometric properties of linear transformations. The basics of linear algebra are introduced in Section 2.3. The linear algebra of row spaces and column spaces is introduced in Section 2.4. The problem of solving systems of linear equations is discussed in Section 2.5. The notion of matrix rank is introduced in Section 2.6. Different methods for generating orthogonal basis sets are introduced in Section 2.7. In Section 2.8, we show that solving systems of linear equations is a special case of least-squares regression, which is one of the fundamental building blocks of machine learning. The issue of ill-conditioned matrices and ill-conditioned systems of equations is discussed in Section 2.9. Inner products are introduced in Section 2.10. Complex vector spaces are introduced in Section 2.11. A summary is given in Section 2.12. 

![image](<Images/02_Linear_Transformations_and_Linear_Systems_image_001.jpg>)



Figure 2.1: Mean-centering: a translation operation


## 2.1.1 What Is a Linear Transform?

Linear transformations are at the heart of operations performed on vectors in linear algebra, and they are typically accomplished by multiplying matrices and vectors. A linear transform is defined as follows: 

Definition 2.1.1 (Linear Transform) A vector-to-vector function f(x) defines a linear transform of x, if the following conditions are satisfied for any scalar c: 

$$
\begin{array}{l} f (c \overline {{x}}) = c \cdot f (\overline {{x}}), \forall \overline {{x}} i n d o m a i n o f f (\cdot) \\ f (\overline {{x}} + \overline {{y}}) = f (\overline {{x}}) + f (\overline {{y}}), \forall \overline {{x}}, \overline {{y}} i n d o m a i n o f f (\cdot) \end{array}
$$

A vector-to-vector function is a generalization of the notion of scalar functions, and it maps a d-dimensional vector to an n-dimensional vector for some d and n. Consider the function $f ( { \overline { { x } } } ) = A { \overline { { x } } }$ , which pre-multiplies the d-dimensional column vector x with the $n \times d$ matrix A to create an n-dimensional column vector. This function satisfies the conditions of Definition 2.1.1, and is therefore a linear transform. 

On the other hand, the translation operator is not a linear transform. Consider the translation of the d-dimensional vector x with the vector $\overline { { b } } = [ b _ { 1 } \ldots b _ { d } ] ^ { T }$ as follows: 

$$
f (\overline {{x}}) = \overline {{x}} + \overline {{b}}
$$

This transform does not obey the additive and multiplicative properties. The translation operation is often used in machine learning for mean-centering the data, where a constant mean vector is subtracted from each row of the data set. As a result, the mean value of each column of the transformed data set becomes 0. An example of the effect of mean-centering on the scatter plot of a 2-dimensional data set is illustrated in Figure 2.1. 

Translation is a special case of the class of affine transforms, which includes any transform of the form $f ( { \overline { { x } } } ) = A { \overline { { x } } } + { \overline { { c } } } .$ , where A is an n d matrix, x is d-dimensional vector, and c is an n-dimensional column vector. Stated simply, an affine transform is a combination of a linear transform with a translation. One can define an affine transform as follows: 

Definition 2.1.2 (Affine Transform) A vector-to-vector function $f ( { \overline { { x } } } )$ defines an affine transform of x, if the following condition is satisfied for any scalar λ: 

$$
f (\lambda \overline {{x}} + [ 1 - \lambda ] \overline {{y}}) = \lambda f (\overline {{x}}) + [ 1 - \lambda ] f (\overline {{y}}), \forall \overline {{x}}, \overline {{y}} i n d o m a i n o f f (\cdot)
$$

All linear transforms are special cases of affine transforms, but not vice versa. There is considerable confusion and ambiguity in the use of the terms “linear” and “affine” in mathematics. Many subfields of mathematics use the terms “linear” and “affine” interchangeably. For example, the simplest univariate function $f ( x ) = m \cdot x + b ,$ which is widely referred to as “linear,” allows a non-zero translation $b ;$ this would make it an affine transform. However, the notion of linear transform from the linear algebra perspective is much more restrictive, and it does not even include the univariate function $f ( x ) = m \cdot x + b$ , unless the bias term b is zero. The class of linear transforms (from the linear algebra perspective) can always be geometrically expressed as a sequence of one or more rotations, reflections, and dilations/contractions about the origin. The origin always maps to itself after these operations, and therefore translation is not included. Unfortunately, the use of the word “linear” in machine learning almost always allows translation (with copious use of bias terms), which makes the terminology somewhat confusing. In this book, the words “linear transform” or “linear operator” will be used in the context of linear algebra (where translation is not allowed). Terms such as “linear function” will be used in the context of machine learning (where translation is allowed). 

## 2.2 The Geometry of Matrix Multiplication

The discussion in the previous section already shows that the multiplication of a $d -$ dimensional vector with an $n \times d$ matrix is an example of a linear transformation. It turns out that the converse is also true: 

Lemma 2.2.1 (Linear Transformation Is Matrix Multiplication) Any linear mapping $f ( { \overline { { x } } } )$ from d-dimensional vectors to n-dimensional vectors can be represented as the matrix-to-vector product Ax by constructing A as follows. The columns of the $n \times d$ matrix $A$ are $f ( { \overline { { e } } } _ { 1 } ) \ldots f ( { \overline { { e } } } _ { d } )$ , where $\overline { { e } } _ { i }$ is the ith column of the $d \times d$ identity matrix. 

Proof: The result $f ( { \overline { { e } } } _ { i } ) = A { \overline { { e } } } _ { i }$ holds, because $A \overline { { e } } _ { i }$ returns the ith column of A, which is $f ( { \overline { { e } } } _ { i } )$ . Furthermore, one can express $f ( { \overline { { x } } } )$ for any vector $\overline { { x } } = [ x _ { 1 } \ldots x _ { d } ] ^ { T }$ as follows: 

$$
f (\overline {{x}}) = f (\sum_ {i = 1} ^ {d} x _ {i} \overline {{e}} _ {i}) = \sum_ {i = 1} ^ {d} x _ {i} f (\overline {{e}} _ {i}) = \sum_ {i = 1} ^ {d} x _ {i} [ A \overline {{e}} _ {i} ] = A [ \sum_ {i = 1} ^ {d} x _ {i} \overline {{e}} _ {i} ] = A \overline {{x}}
$$

Therefore, the linear transformation $f ( { \overline { { x } } } )$ can always be expressed as $A { \overline { { x } } } .$ Setting A to the scalar m yields a special case of the scalar-to-scalar linear function $f ( x ) =$ $m \cdot x + b \ ( { \mathrm { w i t h } } \ b = 0 )$ . For vector-to-vector transformations, one can either transform a row vector $\overline { y }$ as ${ \overline { { y } } } V$ or (equivalently) transform the column vector $\overline { { x } } = \overline { { y } } ^ { T }$ as $V ^ { T } { \overline { { x } } }$ 

$$
f (\overline {{y}}) = \overline {{y}} V \quad [ \text { Linear   transform   on   row   vector } \overline {{y}} ]
$$

$$
g (\overline {{x}}) = V ^ {T} \overline {{x}} \quad [ \mathrm{Sametransformoncolumnvector} \overline {{x}} = \overline {{y}} ^ {T} ]
$$

One can also treat a matrix-to-matrix multiplication between $n \times d$ matrix D and $d \times d$ matrix V as a linear transformation of the rows of the first matrix In other words, the ith row of the $n \times d$ matrix $D ^ { \prime } = D V$ is the transformed representation of the ith row of the original matrix D. Data matrices in machine learning often contain multidimensional points in their rows. 

Matrix transformations can be broken up into geometrically interpretable sequences of transformations by expressing matrices as products of simpler matrices (cf. Section 1.3 of Chapter 1): 

Observation 2.2.1 (Matrix Product as Sequence of Geometric Transformations) The geometric transformation caused by multiplying a vector with $V = V _ { 1 } V _ { 2 } \dots V _ { r }$ can be viewed a sequence of simpler geometric transformations by regrouping the product as follows: 

$$
\underbrace {\overline {{y}} V = ([ (\overline {{y}} V _ {1}) V _ {2} ] \ldots V _ {r})} _ {\text {For row vector \overline {{y}}}}, \qquad \underbrace {V ^ {T} \overline {{x}} = (V _ {r} ^ {T} [ V _ {r - 1} ^ {T} \ldots (V _ {1} ^ {T} \overline {{x}}) ])} _ \text {For column vector \overline {{x}} = \overline {{y}} ^ {T}}
$$

Note the groupings of the expressions using parentheses so that simple geometric operations corresponding to matrices $V _ { 1 } \ldots V _ { r }$ are sequentially applied to the corresponding vectors. In the following, we discuss some important geometric operators. We start with orthogonal operators. 

## Orthogonal Transformations

The orthogonal $2 \times 2$ matrices $V _ { r }$ and $V _ { c }$ that respectively rotate 2-dimensional row and column vectors by θ degrees in the counter-clockwise direction are as follows: 

$$
V _ {r} = \left[ \begin{array}{c c} \cos (\theta) & \sin (\theta) \\ - \sin (\theta) & \cos (\theta) \end{array} \right], V _ {c} = \left[ \begin{array}{c c} \cos (\theta) & - \sin (\theta) \\ \sin (\theta) & \cos (\theta) \end{array} \right]\tag{2.1}
$$

If we have an $n \times 2$ data matrix $D _ { : }$ , then the product $D V _ { r }$ will rotate each row of D using $V _ { r } .$ whereas the product $V _ { c } D ^ { T }$ will equivalently rotate each column of $D ^ { T }$ . One can also view a data rotation $D V _ { r }$ in terms of projection of the original data on a rotated axis system. Counter-clockwise rotation of the data with a fixed axis system is the same as clockwise rotation of the axis system with fixed data. In essence, the two columns of the transformation matrix $V _ { r }$ represent the mutually orthogonal unit vectors of a new axis system that is rotated clockwise by $\theta .$ These two new columns are shown on the left of Figure 2.2 for a counter clockwise rotation of $3 0 ^ { \circ }$ . The transformation returns the coordinates $D V _ { r }$ of the data points on these column vectors, because we are computing the dot product of each row of $D$ with the (unit length) columns of $V _ { r }$ . In this case, the columns of $V _ { r }$ (orthonormal directions in new axis system) make counter-clockwise angles of $- 3 0 ^ { \circ }$ and $6 0 ^ { \circ }$ with the vector $[ 1 , 0 ]$ Therefore, the corresponding matrix $V _ { r }$ is obtained by populating the columns with vectors of the form $[ \cos ( \theta ) , \sin ( \theta ) ] ^ { T }$ , where $\theta$ is the angle each new orthonormal axis direction makes with the vector [1, 0]. This results in the following matrix $V _ { r }$ 

$$
V _ {r} = \left[ \begin{array}{c c} \cos (- 3 0) & \cos (6 0) \\ \sin (- 3 0) & \sin (6 0) \end{array} \right] = \left[ \begin{array}{c c} \cos (3 0) & \sin (3 0) \\ - \sin (3 0) & \cos (3 0) \end{array} \right]\tag{2.2}
$$

After performing the projection of each data point on the new axes, we can reorient the figure so that the new axes are aligned with the original X- and Y-axes (as shown in the leftto-right transition of Figure 2.2). It is easy to see that the final result is a counter-clockwise rotation of the data points by $3 0 ^ { \circ }$ about the origin. 

![image](<Images/02_Linear_Transformations_and_Linear_Systems_image_002.jpg>)



Figure 2.2: An example of counter-clockwise rotation with $3 0 ^ { \circ }$ with matrix multiplication. The two columns of the transformation matrix are shown in the figure on the left


Orthogonal matrices might include reflections. Consider the following matrix: 

$$
V = \left[ \begin{array}{l l} 0 & 1 \\ 1 & 0 \end{array} \right]\tag{2.3}
$$

For any 2-dimensional data set contained in the $n \times 2$ matrix D, the transformation DV of the rows of D simply flips the two coordinates in each row of D. The resulting transformation cannot be expressed purely as a rotation. This is because this transformation changes the handedness of the data — for example, if the scatter plot of the n rows of the $n \times 2$ matrix D depicts a right hand, the scatter plot of the $n \times 2$ matrix $D V$ will depict a left hand. Intuitively, when you look at your reflection in the mirror, your left hand appears to be your right hand. This implies that a reflection needs to performed somewhere. The key point is that V can be expressed as the product of a counter-clockwise rotation of $9 0 ^ { \circ }$ , followed by a reflection across the vector [0, 1]: 

$$
V = \left[ \begin{array}{c c} \cos (9 0) & \sin (9 0) \\ - \sin (9 0) & \cos (9 0) \end{array} \right] \left[ \begin{array}{c c} - 1 & 0 \\ 0 & 1 \end{array} \right]
$$

When a row of D is post-multiplied with $V ,$ it is first rotated counter-clockwise with $9 0 °$ because of multiplication with the first matrix, and then its first coordinate is multiplied with 1 (i.e., reflection across the Y-axis [0, 1]) because of multiplication with the second matrix. An example of the above transformation can be elucidated by post-multiplying the 2-dimensional row vector [3, 4] with V: 

$$
[ 3, 4 ] V = \underbrace {[ 3 , 4 ] \left[ \begin{array}{c c} \cos (9 0) & \sin (9 0) \\ - \sin (9 0) & \cos (9 0) \end{array} \right]} _ {\text {Rotate 90^{\circ} counter - clockwise}} \left[ \begin{array}{c c} - 1 & 0 \\ 0 & 1 \end{array} \right] = \underbrace {[ - 4 , 3 ] \left[ \begin{array}{c c} - 1 & 0 \\ 0 & 1 \end{array} \right]} _ {\text {Reflect}} = [ 4, 3 ]
$$

Note that the intermediate result $[ - 4 , 3 ]$ is indeed a $9 0 °$ rotation of $[ 3 , 4 ]$ . The decomposition of an orthogonal matrix into rotations and reflections is not unique. For example, if we reflected across [1, 0] instead of $[ 0 , 1 ]$ in the above example, then a $2 7 0 ^ { \circ }$ counter-clockwise rotation will do the same job. 

An orthogonal matrix might correspond to a sequence of rotations in a space of dimensionality greater than 3. For example, if a 4-dimensional object in the xyzw-axis system is rotated once in the xy-plane with angle α and once in the zw-plane with angle $\beta ,$ , the two independent rotations cannot be expressed by a single angle or plane of rotation. However, the resulting $4 \times 4$ orthogonal matrix is still called a “rotation matrix” (in spite of being a sequence of rotations). In some cases, reflections are included with rotations. When a compulsory reflection is included in the sequence, the resulting matrix is referred to as a rotreflection matrix. 

Lemma 2.2.2 (Closure Under Multiplication) The product of any number of orthogonal matrices is always an orthogonal matrix. 

Proof: For any set of orthogonal matrices $A _ { 1 } , A _ { 2 } , \ldots A _ { n }$ , we can show the following: 

$$
(A _ {1} A _ {2} \dots A _ {n}) (A _ {1} A _ {2} \dots A _ {n}) ^ {T} = A _ {1} A _ {2} \dots A _ {n} A _ {n} ^ {T} A _ {n - 1} ^ {T} \dots A _ {1} ^ {T} = I
$$

One obtains the final result by repeatedly grouping pairs of adjacent orthogonal matrices like $A _ { n } A _ { n } ^ { T }$ , and replacing it with the identity matrix. Since the transpose of the product matrix $A _ { 1 } A _ { 2 } \ldots A _ { n }$ is also its inverse, it follows that the product matrix is orthogonal. What about the commutativity of the product of orthogonal matrices? At first glance, one might mistakenly assume that the product of rotation matrices is commutative. After all, it should not matter whether you first rotate an object $5 0 ^ { \circ }$ and then $3 0 ^ { \circ }$ or vice versa. However, this type of 2-dimensional visualization of commutativity breaks down in higher dimensions (or when reflection is combined with rotation even in two dimensions). In other words, the product of orthogonal matrices is not necessarily commutative. The main issue is that rotations in higher dimensions are associated with a vector referred to as the axis of rotation. Orthogonal matrices that do not correspond to the same axis of rotation may not be commutative; for example, if we successively rotate a sphere by $9 0 °$ about two mutually perpendicular axes, the point on the sphere closest to us will land at different places depending on which rotation occurs first. In order to understand this point, consider the following two $3 \times 3$ matrices $R _ { [ 1 , 0 , 0 ] }$ and $R _ { [ 0 , 1 , 0 ] }$ , which can perform counter-clockwise rotations of angles $\alpha , \beta$ about $[ 1 , 0 , \dot { 0 } ]$ and [0, 1, 0], respectively: 

$$
R _ {[ 1, 0, 0 ]} = \left[ \begin{array}{c c c} 1 & 0 & 0 \\ 0 & \cos (\alpha) & \sin (\alpha) \\ 0 & - \sin (\alpha) & \cos (\alpha) \end{array} \right], \qquad R _ {[ 0, 1, 0 ]} = \left[ \begin{array}{c c c} \cos (\beta) & 0 & \sin (\beta) \\ 0 & 1 & 0 \\ - \sin (\beta) & 0 & \cos (\beta) \end{array} \right]\tag{2.4}
$$

In order to understand the nature of orthogonal matrices in more than two dimensions, we ask the reader to convince themselves of the following facts: 

1. Post-multiplication of row vector $[ x , y , z ]$ with matrix $R _ { [ 1 , 0 , 0 ] }$ only rotates the vector about [1, 0, 0] (without changing the first coordinate), whereas the matrix $R _ { [ 0 , 1 , 0 ] }$ rotates this vector about [0, 1, 0] (without changing the second coordinate). 

2. The matrix $R _ { [ 1 , 0 , 0 ] } R _ { [ 0 , 1 , 0 ] }$ is a matrix with orthonormal rows and columns (which can be verified algebraically). 

3. The product of $R _ { [ 1 , 0 , 0 ] }$ and $R _ { [ 0 , 1 , 0 ] }$ is sensitive to the order of multiplication. Therefore, the order of rotations matters. 

All 3-dimensional rotation matrices can be geometrically expressed as a single rotation, albeit with an arbitrary axis of rotation. 

## Givens Rotations and Householder Reflections

It is not possible to express a rotation matrix using a single angle in dimensionalities greater than $3 -$ in such cases, independent rotations of different angles might be occurring in unrelated planes (e.g., xy-plane and zw-plane). Therefore, one must express a rotation transformation as a sequence of elementary rotations, each of which occurs in a 2-dimensional plane. One natural choice for defining an elementary rotation is the Givens rotation, which is a generalization of Equation 2.4 to higher dimensions. $\mathrm { ~ A ~ } d \times d$ Givens rotation always selects two coordinate axes and performs the rotation in that plane, so that post-multiplying a d-dimensional row vector with that rotation matrix changes only two coordinates. The $d \times d$ Givens rotation matrix is different from the $d \times d$ identity matrix in only $2 \times 2$ relevant entries; these entries are the same as those of a $2 \times 2$ rotation matrix. For example, the $4 \times 4$ Givens rotation matrix $G _ { r } ( 2 , 4 , \alpha )$ below rotates only the second and fourth coordinates counter-clockwise by α when post-multiplied to a row vector, and its transpose $G _ { c } ( 2 , 4 , \alpha )$ can be pre-multiplied to a column vector to achieve the same result: 

$$
\underbrace {G _ {r} (2 , 4 , \alpha) = \left[ \begin{array}{c c c c} 1 & 0 & 0 & 0 \\ 0 & \cos (\alpha) & 0 & \sin (\alpha) \\ 0 & 0 & 1 & 0 \\ 0 & - \sin (\alpha) & 0 & \cos (\alpha) \end{array} \right]} _ {\text {For row vectors}}, \quad \underbrace {G _ {c} (2 , 4 , \alpha) = \left[ \begin{array}{c c c c} 1 & 0 & 0 & 0 \\ 0 & \cos (\alpha) & 0 & - \sin (\alpha) \\ 0 & 0 & 1 & 0 \\ 0 & \sin (\alpha) & 0 & \cos (\alpha) \end{array} \right]} _ {\text {For column vectors}}
$$

The notations $G . ( \cdot , \cdot , \cdot )$ for row-wise and column-wise transformation matrices are respectively subscripted by either $^ { 6 } r ^ { 5 }$ or $^ { 6 6 } c . ^ { 5 9 }$ All orthogonal matrices can be decomposed into Givens rotations, although a reflection might also be needed. We state the following result [52], although a formal proof is omitted: 

Lemma 2.2.3 (Givens Geometric Decomposition) All $d \times d$ orthogonal matrices can be shown to be products of at most $O ( d ^ { 2 } )$ Givens rotations and at most a single elementary reflection matrix (obtained by negating one diagonal element of the identity matrix). 

The Givens rotation has many useful applications in numerical linear algebra [52]. 

Problem 2.2.1 Show that you can express a $d \times d$ elementary row interchange matrix as the product of a $9 0 °$ Givens rotation and an elementary reflection. 

So far we have introduced only diagonal reflection matrices that flip the sign of a vector component. The Householder reflection matrix is an orthogonal matrix that reflects a vector x in any “mirror” hyperplane of arbitrary orientation; such a hyperplane passes through the origin and its orientation is defined by an arbitrary normal vector $\overline { { v } }$ (of unit length). Assume that both $\textstyle { \overline { { x } } }$ and v are column vectors. First, note that the distance of $\textstyle { \overline { { x } } }$ from the “mirror” hyperplane is $c = { \overline { { x } } } \cdot { \overline { { v } } }$ . An object and its mirror image are separated by twice this distance along ${ \overline { { v } } } .$ Therefore, to perform the reflection of $\textstyle { \overline { { x } } }$ and create its mirror image ${ \overline { { x } } } ^ { \prime }$ one must subtract twice of $c \overline { { v } }$ from x: 

$$
\overline {{x}} ^ {\prime} \Leftarrow \overline {{x}} - 2 (\overline {{x}} \cdot \overline {{v}}) \overline {{v}} = \overline {{x}} - 2 (\overline {{v}} ^ {T} \overline {{x}}) \overline {{v}} = \overline {{x}} - 2 \overline {{v}} (\overline {{v}} ^ {T} \overline {{x}}) = \overline {{x}} - 2 (\overline {{v v}} ^ {T}) \overline {{x}} = \underbrace {(I - 2 \overline {{v}}   \overline {{v}} ^ {T})} _ {\text {Householder}} \overline {{x}}
$$

For any unit (column) vector $^ { \overline { { v } } , }$ the matrix $( I - 2 \overline { { v } } \overline { { v } } ^ { T } )$ is an elementary reflection matrix in the hyperplane perpendicular to $\overline { { v } }$ and passing through the origin. This matrix is referred to as the Householder reflection matrix. Any orthogonal matrix can be represented with fewer Householder reflections than Givens rotations; therefore, the former is a more expressive transform. 

Lemma 2.2.4 (Householder Geometric Decomposition) Any orthogonal matrix of size d $\times d$ can be expressed as the product of at most d Householder reflection matrices. 

Problem 2.2.2 (Reflection of a Reflection) Verify algebraically that the square of the Householder reflection matrix is the identity matrix. 

Problem 2.2.3 Show that the elementary reflection matrix, which varies from the identity matrix only in terms of flipping the sign of the ith diagonal element, is a special case of the Householder reflection matrix. 

Problem 2.2.4 (Generalized Householder) Show that a sequence ofk mutually orthogonal Householder transformations can be expressed as $I - 2 Q Q ^ { T }$ for a $d \times k$ matrix $Q$ containing orthonormal columns. Which $( d - k )$ -dimensional plane is this a reflection in $\mathscr { l }$ 

## Rigidity of Orthogonal Transformations

Dot products and Euclidean distances between vectors are unaffected by multiplicative transformations with orthogonal matrices. This is because an orthogonal transformation is a sequence of rotations and reflections, which does not change lengths and angles. This fact can also be shown algebraically. Consider two d-dimensional row vectors x and $\overline { y }$ that are respectively transformed to $\overline { { x } } V$ and $\overline { { y } } V$ using the $d \times d$ orthogonal matrix V. Then, the dot product between these transformed vectors is as follows: 

$$
[ \overline {{x}} V ] \cdot [ \overline {{y}} V ] = [ \overline {{x}} V ] [ \overline {{y}} V ] ^ {T} = [ \overline {{x}} V ] [ V ^ {T} \overline {{y}} ^ {T} ] = \overline {{x}} (V V ^ {T}) \overline {{y}} ^ {T} = \overline {{x}} (I) \overline {{y}} ^ {T} = \overline {{x}} \cdot \overline {{y}}
$$

This equivalence for dot products naturally carries over to Euclidean distances and angles, which are functions of dot products. This also means that orthogonal transformations preserve the sum of squares of Euclidean distances of the data points (i.e., rows of a data matrix $D )$ about the origin, which is also the (squared) Frobenius norm or energy of the $n \times d$ matrix $D _ { \ast }$ . When the $n \times d$ matrix D is multiplied with the $d \times d$ orthogonal matrix $V$ , the Frobenius norm of DV can be expressed in terms of the trace operator as follows: 

$$
\| D V \| _ {F} ^ {2} = \mathrm{tr} [ (D V) (D V) ^ {T} ] = \mathrm{tr} [ D (V V ^ {T}) D ^ {T} ] = \mathrm{tr} (D D ^ {T}) = \| D \| _ {F} ^ {2}
$$

Transformations that preserve distances between pairs of points are said to be rigid. Rotations and reflections not only preserve distances between points but also absolute distances of points from the origin. Translations (which are not linear transforms) are also rigid be cause they preserve distances between pairs of transformed points. However, translations usually do not preserve distances from the origin. 

## Scaling: A Non-rigid Transformation

In general, multiplication of a vector x with an arbitrary matrix V might change its length. If such a matrix can be decomposed into simpler geometric operator matrices as $V = V _ { 1 } V _ { 2 } \dots V _ { r }$ , it means that there must be some fundamental geometric transformation $V _ { i }$ among these operator matrices that does not preserve distances. This fundamental transformation is that of dilation/contraction (or, more generally, scaling). The basic form of this transformation scales the ith dimension of the vector x by a scaling factor $\lambda _ { i }$ . Such a transformation can be achieved by post-multiplying row vector $\textstyle { \overline { { x } } }$ with a $d \times$ d diagonal matrix $\Delta$ in which the ith diagonal entry is $\lambda _ { i }$ . Note that it is possible for the entries to be negative, in which case the reflection operation (along the corresponding axis direction) is combined with dilation/contraction. When the scaling factors across different dimensions are different, the scaling is said to be anisotropic. An example of a $2 \times 2$ matrix $\Delta$ corresponding to anisotropic scaling is as follows: 

$$
\Delta = \left[ \begin{array}{c c} 2 & 0 \\ 0 & 0. 5 \end{array} \right]
$$

Multiplying a 2-dimensional vector with this matrix scales the first coordinate by 2 and the second coordinate by 0.5. This transformation is not rigid because of non-unit scaling factors in various directions. Furthermore, if we flip the sign of the first diagonal entry by changing it from 2 to 2, then this transformation will combine positive dilation/contraction with reflection via the following decomposition: 

$$
\left[ \begin{array}{c c} - 2 & 0 \\ 0 & 0. 5 \end{array} \right] = \underbrace {\left[ \begin{array}{c c} 2 & 0 \\ 0 & 0 . 5 \end{array} \right]} _ {\text {Stretching}} \underbrace {\left[ \begin{array}{c c} - 1 & 0 \\ 0 & 1 \end{array} \right]} _ {\text {Reflection}}
$$

Thus, a reflection matrix is a special case of a scaling (diagonal) matrix 

## General Case: Combining Orthogonal and Scaling Transformations

Multiplying an $n \times d$ data matrix D with a diagonal matrix $\Delta$ to create DΔ results in scaling of the ith dimension (column) of the data matrix D with the ith diagonal entry of $\Delta$ . This is an example of axis-parallel scaling, where the directions of scaling are aligned with the axes of representation. Just as axis-parallel scalings are performed with diagonal matrices, scalings along arbitrary directions are performed with diagonalizable matrices (cf. Chapter 3). 

Consider the case in which we want to scale each 2-dimensional row of an $n \times 2$ data matrix in the direction [cos( 30), sin( 30)] by a factor of 2, and in the direction [cos(60), sin(60)] by a factor of 0.5. This can be achieved by (i) first rotating the data set D by an angle $3 0 ^ { \circ }$ by multiplying D with orthogonal matrix $V$ to create DV , (ii) then multiplying the resulting matrix DV with diagonal matrix $\Delta$ with diagonal entries 2 and 0.5 to create $( D V ) \Delta$ , and (iii) finally rotating the data set in the reverse direction (i.e., by angle $- 3 0 ^ { \circ } )$ by multiplying $D V \Delta$ with $V ^ { T }$ to create $( D V \Delta ) V ^ { T }$ . The resulting transformation can be regrouped using the associativity property of matrix multiplication as follows: 

$$
D ^ {\prime} = D (V \Delta V ^ {T})
$$

Such transformations of the form $V \Delta V ^ { T }$ will be discussed in Chapter 3. 

The matrix for performing the aforementioned anisotropic scaling along the two orthogonal vector directions $[ \cos ( - 3 0 ) , \sin ( - 3 0 ) ]$ and [cos(60), sin(60)] at scale factors of 2 and 0.5 can be obtained by defining V and $\Delta$ as follows: 

$$
V = \left[ \begin{array}{c c} \cos (- 3 0) & \cos (6 0) \\ \sin (- 3 0) & \sin (6 0) \end{array} \right] = \left[ \begin{array}{c c} \cos (3 0) & \sin (3 0) \\ - \sin (3 0) & \cos (3 0) \end{array} \right], \Delta = \left[ \begin{array}{c c} 2 & 0 \\ 0 & 0. 5 \end{array} \right]
$$

Therefore, we obtain the following transformation matrix $A = V \Delta V ^ { T }$ 

$$
A = \left[ \begin{array}{c c} \cos (3 0) & \sin (3 0) \\ - \sin (3 0) & \cos (3 0) \end{array} \right] \left[ \begin{array}{c c} 2 & 0 \\ 0 & 0. 5 \end{array} \right] \left[ \begin{array}{c c} \cos (3 0) & - \sin (3 0) \\ \sin (3 0) & \cos (3 0) \end{array} \right] = \left[ \begin{array}{c c} 1. 6 2 5 & - 0. 6 5 0 \\ - 0. 6 5 0 & 0. 8 7 5 \end{array} \right]
$$

Consider a square with coordinates at [0, 0], [0, 1], [1, 0], and [1, 1]. What happens to these coordinates after post-multiplication with the above matrix A? The origin is always transformed to the origin by a linear transformation, and therefore we only need to worry about the other three points by stacking them up into a $3 \times 2$ matrix denoted by matrix D. The resulting transformed matrix $D ^ { \prime } = D A$ is as follows: 

![image](<Images/02_Linear_Transformations_and_Linear_Systems_image_003.jpg>)



Figure 2.3: An example of anisotropic scaling along two mutually orthogonal directions


![image](<Images/02_Linear_Transformations_and_Linear_Systems_image_004.jpg>)



Figure 2.4: The transformation of Figure 2.3 as shown in terms of scaling along two directions


$$
D ^ {\prime} = D A = \left[ \begin{array}{c c} 1 & 0 \\ 0 & 1 \\ 1 & 1 \end{array} \right] \left[ \begin{array}{c c} 1. 6 2 5 & - 0. 6 5 0 \\ - 0. 6 5 0 & 0. 8 7 5 \end{array} \right] = \left[ \begin{array}{c c} 1. 6 2 5 & - 0. 6 5 0 \\ - 0. 6 5 0 & 0. 8 7 5 \\ 0. 9 7 5 & 0. 2 2 5 \end{array} \right]
$$

It is also helpful to understand the nature of the distortion pictorially. An example of the sequence of transformations in terms $V , \Delta , V ^ { T }$ (for a rectangular scatterplot) are shown in Figure 2.3. The corresponding data set $D ^ { \prime } = \dot { D } ( V \Delta V ^ { T } )$ and the scaling are shown in a concise way in Figure 2.4. One can also generalize this intuition to higher dimensions. 

Not all transformations can be expressed in the form $V \Delta V ^ { T }$ , as shown above. However, all is not lost. A beautiful result, referred to as singular value decomposition (cf. Chapter 7), states that any square matrix A can be expressed in the form $A \ = \ U \Delta V ^ { T }$ , where U and $V$ are both orthogonal matrices (which might be different) and $\Delta$ is a nonnegative scaling matrix. Therefore, all linear transformations defined by matrix multiplication can be expressed as a sequence of rotations/reflections, together with a single anisotropic scaling. This result can even be extended to rectangular matrices. 

## 2.3 Vector Spaces and Their Geometry

A vector space is an infinite set of vectors satisfying certain types of set closure properties under addition and scaling operations. One of the most important vector spaces in linear algebra is the set of all n-dimensional vectors: 

Definition 2.3.1 (Space of n-Dimensional Vectors) The space $\mathcal { R } ^ { n }$ consists of the set of all column vectors with n real components. 

By convention, the vectors in $\mathcal { R } ^ { n }$ are assumed to be column vectors in linear algebra. Geometrically, all vectors in $\mathcal { R } ^ { n }$ are assumed to have tails at the origin. This is unlike vectors in many scientific fields like physics, where the vector $\textstyle { \overline { { x } } }$ might have a tail at $\overline { { a } }$ and head at ${ \overline { { x } } } + { \overline { { a } } }$ . The space $\mathcal { R } ^ { n }$ contains an infinite set of vectors, because any real-valued component of an n-dimensional vector can have an infinite number of possible values. Furthermore, we can scale any vector from $\mathcal { R } ^ { n }$ or add two vectors from $\mathcal { R } ^ { n }$ to still stay in $\mathcal { R } ^ { n }$ . This is the defining property of a vector space, which might contain a subset of vectors from $\mathcal { R } ^ { n }$ 

Definition 2.3.2 (Vector Space in $\mathcal { R } ^ { n } )$ A subset of vectors  from $\mathcal { R } ^ { n }$ is a vector space, if it satisfies the following properties: 

1. $I f { \overline { { x } } } \in \nu$ then $c { \overline { { x } } } \in \nu$ for any scalar $c \in \mathcal { R }$ 

2. $I f \overline { { x } } , \overline { { y } } \in \mathcal { V } _ { \mathrm { : } }$ , then $\overline { { x } } + \overline { { y } } \in \mathcal { V } .$ 

The zero vector, denoted by ${ \overline { { 0 } } } ,$ , is included in all vector spaces, and always satisfies the additive identity ${ \overline { { x } } } + { \overline { { 0 } } } = { \overline { { x } } }$ . A singleton set containing the zero vector can also be considered a vector space (albeit a rather simple one), because it satisfies both the above properties. 

Consider the subset of vectors from $\mathcal { R } ^ { 3 }$ , such that the head of each vector lies on a 2-dimensional hyperplane passing through the origin (and the tail is the origin). This set of vectors is a vector space because adding or scaling vectors on an origin-centered hyperplane leads to other vectors on the same hyperplane. Furthermore, all multiples of an arbitrary vector like $[ 2 , 1 , 3 ] ^ { T }$ (i.e., all points on an infinite line in $\mathcal { R } ^ { 3 } )$ also form a vector space, which is also a special case of a hyperplane. In general, vector spaces that are subsets of $\mathcal { R } ^ { n }$ correspond to vectors sitting on an origin-centered hyperplane of dimensionality at most $n .$ Therefore, vector spaces in $\mathcal { R } ^ { n }$ can be nicely mapped to our geometric understanding of lower-dimensional hyperplanes. The origin-centered nature $o f$ these hyperplanes is important; the set of vectors with tails at the origin and heads on a hyperplane that is not origin-centered does not define a vector space, because this set of vectors is not closed under scaling and addition. Another example of a set of vectors that is not a vector space is the set of all vectors with only non-negative components in $\mathcal { R } ^ { 3 }$ , because it is not closed under multiplication with negative scalars. Other than the zero vector space, all vector spaces contain an infinite set of vectors. 

Finally, we observe that a fixed linear transformation of each element of a vector space results in another vector space, because of the way in which linear transformations preserve the properties of addition and scalar multiplication (cf. Definition 2.1.1). For example, multiplying all vectors on an origin-centered hyperplane with the same matrix results in a set of vectors sitting on another origin-centered hyperplane after undergoing a set of geometrically interpretable linear transformations (like origin-centered rotation and scaling). 

Definition 2.3.2 seems somewhat restrictive at first glance, because we have required all vector spaces to be subsets of $\mathcal { R } ^ { n }$ . The modern notion of a vector space is more general than vectors from $\mathcal { R } ^ { n }$ , because it allows all kinds of abstract objects to be considered “vectors” and infinite sets of such objects to be considered vector spaces (along with appropriately defined vector addition and scalar multiplication operations on these objects). For example, the space of all upper-triangular matrices of a specific size is a vector space, although the addition operation now corresponds to element-wise addition of the matrices. Similarly, the space of all polynomial functions of a specific maximum degree is a vector space, and the addition operation corresponds to addition of constituent monomial coefficients. In each case, the nature of the addition and multiplication operations, and the definition of the zero vector (such as the zero matrix or zero polynomial) depends on the type of object being considered. It is also possible for the components of vectors and the scalar $c$ in Definition 2.3.2 to be drawn from the complex domain (or other sets of values[^field-axioms] satisfying a set of properties known as the field axioms). Most of this book works with real-valued vector spaces, although we will occasionally consider vectors drawn from ${ \mathcal { C } } ^ { n }$ , where $\mathcal{C}$ corresponds to the field of complex numbers (cf. Section 2.11). 

The assumption that vector spaces are subsets of $\mathcal { R } ^ { n }$ is not as restrictive as one might think, because we can indirectly represent most vector spaces over a real field by mapping them to $\mathcal { R } ^ { n }$ . For example, the vector space of $m \times m$ upper-triangular matrices can be represented indirectly by populating a vector from $\mathcal { R } ^ { [ m ( m + \hat { 1 } ) / 2 ] }$ with matrix entries. Similarly, polynomials with a pre-defined maximum degree can be represented as finite-length vectors containing the coefficients of various monomials that constitute the polynomial. It can be formally shown that large classes of vector spaces over the real field can be indirectly represented using $\mathcal { R } ^ { n }$ , via the process of coordinate representation (cf. Section 2.3.1). Furthermore, staying in $\mathcal { R } ^ { n }$ has the distinct advantage of being able to work with easily understandable operations over matrices and vectors. 

Problem 2.3.1 Let $\overline { { x } } \in \mathcal { R } ^ { d }$ be a vector and A be an n d matrix. Is each of the following a vector space? (a) All x satisfying $A { \overline { { x } } } = { \overline { { 0 } } } ; ( b )$ All x satisfying $A { \overline { { x } } } \geq { \overline { { 0 } } } ; ( c )$ All x satisfying $A { \overline { { x } } } = { \overline { { b } } }$ for some non-zero $\bar { b } \in \mathcal { R } ^ { n } ; ( d )$ All n n matrices in which the row sums and column sums are the same for a particular matrix (but not necessarily across matrices). 

A subset of the vector space, which is itself a vector space, is referred to as a subspace: 

Definition 2.3.3 (Subspace) A vector space $s$ is a subspace of another vector space $\nu _ { i }$ $i f$ any vector ${ \overline { { x } } } \in S$ is also present in . In addition, when contains vectors not present in $\mathcal { S }$ , the subspace $s$ is a proper subspace of . 

The set notation $^ { 6 6 } \subseteq ^ { \prime 5 }$ is used to denote a subspace as in $\mathcal { S } \subseteq \mathcal { V }$ . The notation $^ { 6 6 } \subset ^ { \prime 9 }$ denotes a proper subspace of the parent space. The requirement that subspaces are vector spaces ensures that subspaces of $\mathcal { R } ^ { n }$ contain vectors residing on hyperplanes in n-dimensional space passing through the origin. When the hyperplane defining the subspace has dimensionality strictly less than $n _ { \mathrm { : } }$ the corresponding subspace is a proper subspace of $\mathcal { R } ^ { n }$ because nonhyperplane vectors in $\mathcal { R } ^ { n }$ are not members of the subspace. For example, the set of all scalar multiples of the vector $[ 2 , 1 , 5 ] ^ { T }$ defines a proper subspace of $\mathcal { R } ^ { 3 }$ , and it contains all vectors lying on a 1-dimensional hyperplane passing through the origin. However, vectors that do not lie on this 1-dimensional hyperplane are not members of the subspace. Similarly, the vectors $[ 1 , 0 , 0 ] ^ { T }$ and $[ 1 , 2 , 1 ] ^ { T }$ can be used to define a 2-dimensional hyperplane $\mathcal { V } _ { 1 }$ , each point on which is a linear combination of this pair of vectors. The set of vectors sitting on this hyperplane also define a proper subspace of $\mathcal { R } ^ { 3 }$ . Both the vectors $[ 5 , 4 , 2 ] ^ { T }$ and $[ 0 , 2 , 1 ] ^ { T }$ lie in this subspace because of the following: 

$$
{\left[ \begin{array}{l} 5 \\ 4 \\ 2 \end{array} \right]} = 3 {\left[ \begin{array}{l} 1 \\ 0 \\ 0 \end{array} \right]} + 2 {\left[ \begin{array}{l} 1 \\ 2 \\ 1 \end{array} \right]}, \qquad {\left[ \begin{array}{l} 0 \\ 2 \\ 1 \end{array} \right]} = {\left[ \begin{array}{l} 1 \\ 2 \\ 1 \end{array} \right]} - {\left[ \begin{array}{l} 1 \\ 0 \\ 0 \end{array} \right]}
$$

All scalar multiples of $[ 5 , 4 , 2 ] ^ { T }$ also define a vector space $\nu _ { 2 }$ that is a proper subspace of $\mathcal { V } _ { 1 }$ , because the line defining $\nu _ { 2 }$ sits on the hyperplane corresponding to $\nu _ { 1 }$ . In other words, we have $\mathcal { V } _ { 2 } \subset \mathcal { V } _ { 1 } \subset \mathcal { R } ^ { 3 }$ . For the vector space $\mathcal { R } ^ { 3 }$ , examples of proper subspaces could be the set of vectors sitting on (i) any 2-dimensional plane passing through the origin, (ii) any 1-dimensional line passing through the origin, and (iii) the zero vector. Furthermore, subspace relationships might exist among the lower-dimensional hyperplanes when one of them contains the other (e.g., a 1-dimensional line sitting on a plane in $\mathcal { R } ^ { 3 } )$ 

A set of vectors $\{ \overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d } \}$ is linearly dependent if a non-zero linear combination of these vectors sums to zero: 

Definition 2.3.4 (Linear Dependence) A set of non-zero vectors $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d }$ is linearly dependent, if a set of d scalars x $\mathbf { \nabla } \cdot \cdot \mathbf { \nabla } ^ { x _ { d } }$ can be found so that at least some of the scalars are non-zero, and the following condition is satisfied: 

$$
\sum_ {i = 1} ^ {d} x _ {i} \overline {{a}} _ {i} = \overline {{0}}
$$

We emphasize the fact that all scalars $x _ { 1 } \ldots x _ { d }$ cannot be zero. Such a coefficient set is said to be non-trivial. When no such set of non-zero scalars can be found, the resulting set of vectors is said to be linearly independent. It is relatively easy to show that a set of vectors $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d }$ that are mutually orthogonal must be linearly independent. If these vectors are linearly dependent, we must have non-trivial coefficients $x _ { 1 } \ldots x _ { d }$ , such that $\Sigma _ { i = 1 } ^ { d } x _ { i } \overline { { a } } _ { i } = \overline { { 0 } }$ However, taking the dot product of the linear dependence condition with each $\overline { { a } } _ { i }$ and setting each ${ \overline { { a } } } _ { i } \cdot { \overline { { a } } } _ { j } = 0$ for $i \neq j$ yields each $x _ { i } = 0$ , which is a trivial coefficient set. 

Consider the earlier example of three linearly dependent vectors $[ 0 , 2 , 1 ] ^ { T } , [ 1 , 2 , 1 ] ^ { T }$ , and $[ 1 , 0 , 0 ] ^ { T }$ , which lie on a 2-dimensional hyperplane passing through the origin. These vectors satisfy the following linear dependence condition: 

$$
\left[ \begin{array}{l} 0 \\ 2 \\ 1 \end{array} \right] - \left[ \begin{array}{l} 1 \\ 2 \\ 1 \end{array} \right] + \left[ \begin{array}{l} 1 \\ 0 \\ 0 \end{array} \right] = \overline {{0}}
$$

Therefore, the coefficients $x _ { 1 } , \ x _ { 2 }$ , and $x _ { 3 }$ of the linear dependence condition are $+ 1 , \ - 1$ and +1 in this case. The key point is that one only needs two of these three vectors to define the hyperplane on which all the vectors lie. This minimal set of vectors is also referred to as a basis, and is defined as follows: 

Definition 2.3.5 (Basis) A basis (or basis set) of a vector space $\mathcal { V } \subseteq \mathcal { R } ^ { n }$ is a minimal set of vectors $B = \{ \overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d } \} \subseteq \mathcal { V }$ , so that all vectors in can be expressed as linear combinations $o f \overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d }$ . In other words, for any vector $\overline { { v } } \in \mathcal { V }$ , we can find scalars $x _ { 1 } \ldots x _ { d }$ so that $\begin{array} { r } { \overline { { v } } = \sum _ { i = 1 } ^ { d } x _ { i } \overline { { a } } _ { i } } \end{array}$ , and one cannot do this for any proper subset of . 

It is helpful to think of a basis geometrically as a coordinate system of directions or axes, and the scalars $x _ { 1 } \ldots x _ { d }$ as coordinates in order to express vectors. For example, the two commonly used axis directions in the classical 2-dimensional plane of Cartesian geometry are $[ 1 , 0 ] ^ { T }$ and $[ 0 , 1 ] ^ { T }$ , although we could always rotate this axis system by θ to get a new set of axes $\{ [ \cos ( \theta ) , \sin ( \theta ) ] ^ { T } , [ - \sin ( \theta ) , \cos ( \theta ) ] ^ { T } \}$ and corresponding coordinates. Furthermore, the representative directions need not even be mutually orthogonal. For example, every point in $\mathcal { R } ^ { 2 }$ can be expressed as a linear combination of $[ 1 , 1 ] ^ { T }$ and $[ 1 , 2 ] ^ { T }$ . Clearly, the basis set is not unique, just as coordinate systems are not unique in classical Cartesian geometry. 

Note that the vectors in a basis must be linearly independent. This is because if the vectors in the basis are linearly dependent, we can drop any vector occurring in the linear dependence condition from without losing the ability to express all vectors in in terms of the remaining vectors. Furthermore, if the linear combination of a set of vectors cannot express a particular vector in $\overline { { v } } \in \mathcal { V }$ , one can add v to the set  without disturbing its linear independence. This process can be continued until all vectors in are expressed by a linear combination of the set . Therefore, an alternative definition of the basis as follows: 

Definition 2.3.6 (Basis: Alternative Definition) A basis (or basis set) of a vector space is a maximal set of linearly independent vectors in it. 

Both definitions of the basis are equivalent and can be derived from one another. An interesting artifact is that the vector space containing only the zero vector has an empty basis. A vector space containing non-zero vectors always has an infinite number of possible basis sets. For example, if we select any three linearly independent vectors in $\mathcal { R } ^ { 3 }$ (or even scale the vectors in a basis set), the resulting set of vectors is a valid basis of $\mathcal { R } ^ { 3 }$ . An important result, referred to as the dimension theorem of vector spaces, states that the size of every basis set of a vector space must be the same: 

Theorem 2.3.1 (Dimension Theorem for Vector Spaces) The number of members in every possible basis set of a vector space is always the same. This value is referred to as the dimensionality of the vector space. 

Proof: Suppose that we have two basis sets $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d }$ and $\overline { { b } } _ { 1 } \dots . \overline { { b } } _ { m }$ so that $d < m$ . In such a case, we will prove that a subset of the vectors in $\overline { { b } } _ { 1 } \dots . \overline { { b } } _ { m }$ must be linearly dependent, which is a contradiction with the pre-condition of the lemma. 

Each vector ${ \overline { { b } } } _ { i }$ is a linear combination of the basis vectors $\overline { { a } } _ { 1 } \ldots . \overline { { a } } _ { d } \colon$ 

$$
\overline {{{b}}} _ {i} = \sum_ {j = 1} ^ {d} \beta_ {i j} \overline {{{a}}} _ {j} \quad \forall i \in \{1 \dots m \}\tag{2.5}
$$

A key point is that we have $m > d$ linear dependence conditions (see Equation 2.5), and we can eliminate each of the d vectors $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d }$ at the cost of reducing one equation. For example, we can select a linear dependence condition in which $\overline { { a } } _ { 1 }$ occurs with a non-zero coefficient, and express $\overline { { a } } _ { 1 }$ as a linear combination of $\overline { { a } } _ { 2 } \ldots \overline { { a } } _ { d }$ and at least one of $\overline { { b } } _ { 1 } \dots \overline { { b } } _ { m } .$ This linear expression for $\overline { { a } } _ { 1 }$ is substituted in all the other linear dependence conditions. The linear dependence condition that was originally selected in order to create the expression for $\overline { { a } } _ { 1 }$ is dropped. This process reduces the number of linear dependence conditions and the number of vectors from the basis set $\{ \overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d } \}$ by 1. One can repeat this process with each of $\overline { { a } } _ { 2 } \ldots \overline { { a } } _ { d }$ , and in each case, the corresponding vector is eliminated while reducing the number of linear dependence conditions by 1. Therefore, after all the vectors $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d }$ have been eliminated, we will be left with $( m - d ) > 0$ linear conditions between ${ \overline { { b } } } _ { 1 } \dots { \overline { { b } } } _ { m } .$ This implies that $\overline { { b } } _ { 1 } \dots . \overline { { b } } _ { m }$ are linearly dependent. 

The notion of subspace dimensionality is identical to that of geometric dimensionality of hyperplanes in $\mathcal { R } ^ { n }$ . For example, any set of n linearly independent directions in $\mathcal { R } ^ { n }$ can be used to create a basis (or coordinate system) in $\mathcal { R } ^ { n }$ . For subspaces corresponding to lowerdimensional hyperplanes, we only need as many linearly independent vectors sitting on the hyperplane as are needed to uniquely define it. This value is the same as the geometric dimensionality of the hyperplane. This leads to the following result: 

Lemma 2.3.1 (Matrix Invertibility and Linear Independence) An $n \ \times \ n$ square matrix A has linearly independent columns/rows if and only if it is invertible. 

Proof: An $n \times n$ square matrix with linearly independent columns defines a basis for all vectors in $\mathcal { R } ^ { n }$ in its columns. Therefore, we can find n coefficient vectors $\overline { { x } } _ { 1 } , \hdots , \overline { { x } } _ { n } \in \mathcal { R } ^ { n }$ so that $A { \overline { { x } } } _ { i } = { \overline { { e } } } _ { i }$ for each i, where $\overline { { e } } _ { i }$ is the ith column of the identity matrix. These conditions can be written in matrix form as $A [ { \overline { { x } } } _ { 1 } \ldots x _ { n } ] = [ { \overline { { e } } } _ { 1 } \ldots { \overline { { e } } } _ { n } ] = I _ { n }$ . Since A and $[ \overline { { x } } _ { 1 } \ldots \overline { { x } } _ { d } ]$ multiply to yield the identity matrix, we have $A ^ { - 1 } = [ { \overline { { x } } } _ { 1 } \ldots x _ { n } ]$ . Conversely, if the matrix $A$ is invertible, multiplication of $A { \overline { { x } } } = { \overline { { 0 } } }$ with $A ^ { - 1 }$ shows that ${ \overline { { x } } } = { \overline { { 0 } } }$ is the only solution (which implies linear independence). One can show similar results with the rows. When vector spaces contain abstract objects like degree-p polynomials of the form $\scriptstyle \sum _ { i = 0 } ^ { p } c _ { i } t ^ { i }$ the basis contains simple instantiations of these objects like $\left\{ t ^ { 0 } , t ^ { 1 } , \ldots t ^ { p } \right\}$ . Choosing a basis like this allows as to use the coefficients $[ c _ { 0 } \ldots c _ { p } ] ^ { \dot { T } }$ of each polynomial as the new vectors space $\mathcal { R } ^ { p + 1 }$ . Carefully chosen basis sets allow us to automatically map all d-dimensional vector spaces over real fields to $\mathcal { R } ^ { d }$ for finite values of d. For example, might be a $d -$ dimensional subspace of $\mathcal { R } ^ { n }$ (for $d < n )$ . However, once we select d basis vectors, the set of d-dimensional combination coefficients for these vectors themselves create the “nicer” vector space $\mathcal { R } ^ { d }$ . Therefore, we have a one-to-one isomorphic mapping between any d-dimensional vector space and $\mathcal { R } ^ { d }$ 

## 2.3.1 Coordinates in a Basis System

Let $\overline { { v } } \in \mathcal { V } \subset \mathcal { R } ^ { n }$ be a vector drawn from a d-dimensional vector space for $d < n$ . In other words, the vector space contains all vectors sitting on a d-dimensional hyperplane in $\mathcal { R } ^ { n }$ . The coefficients $x _ { 1 } \ldots x _ { d } .$ , in terms of which the vector $\begin{array} { r } { \overline { { v } } = \sum _ { i = 1 } ^ { d } x _ { i } \overline { { a } } _ { i } } \end{array}$ is represented in a particular basis are referred to as its coordinates. A particular basis set of the vector space $\mathcal { R } ^ { n }$ , referred to as the standard basis, contains the n-dimensional column vectors $\{ \overline { { e } } _ { 1 } , . . . . \overline { { e } } _ { n } \}$ , where each $\overline { { e } } _ { i }$ contains a 1 in the ith entry and a value of 0 in all other entries. The standard basis set is often chosen by default, where the scalar components of vectors are the same as their coordinates. However, scalar components of vectors are not the same as their coordinates for arbitrary basis sets. The standard basis is restrictive because it cannot be used as the basis of a proper subspace of $\mathcal { R } ^ { n }$ 

An important result is that the coordinates of a vector in any basis must be unique: 

Lemma 2.3.2 (Uniqueness of Coordinates) The coordinates $\overline { { x } } = [ x _ { 1 } , \ldots , x _ { d } ] ^ { T }$ of any vector $\overline { { v } } \in \mathcal { V }$ in terms of a basis set ${ \cal B } = \{ \overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d } \}$ are always unique. 

Proof: Suppose that the coordinates are not unique, and we have two distinct sets of coordinates $x _ { 1 } \ldots x _ { d }$ and $y _ { 1 } \ldots y _ { d }$ . Then, we have $\begin{array} { r } { \overline { { v } } = \sum _ { i = 1 } ^ { d } x _ { i } \overline { { a } } _ { i } = \sum _ { i = 1 } ^ { d } y _ { i } \overline { { a } } _ { i } } \end{array}$ . Therefore, we have $\begin{array} { r } { \sum _ { i = 1 } ^ { d } ( x _ { i } - y _ { i } ) \overline { { a } } _ { i } = \overline { { v } } - \overline { { v } } = \overline { { 0 } } } \end{array}$ . This implies that the vectors $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d }$ are linearly dependent. This results in the contradiction from the statement of the lemma that $\boldsymbol { B }$ is a basis (unless the coordinate sets $x _ { 1 } \ldots x _ { d }$ and $y _ { 1 } \ldots y _ { d }$ are identical). 

How can one find these unique coordinates? When $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d }$ correspond to an orthonormal basis of , the coordinates are simply the dot products of v with these vectors. By taking the dot product of both sides of $\begin{array} { r } { \overline { { v } } = \sum _ { i = 1 } ^ { d } x _ { i } \overline { { a } } _ { i } } \end{array}$ with each $\overline { { a } } _ { j }$ and using orthonormality, it is easy to show that $x _ { j } = \overline { { v } } \cdot \overline { { a } } _ { j }$ . For example, if $\overline { { a } } _ { 1 } = [ 1 , 1 , 1 ] ^ { T } / \sqrt { 3 }$ and $\overline { { a } } _ { 2 } = [ 1 , - 1 , 0 ] ^ { T } / \sqrt { 2 }$ constitute the orthonormal basis set of vector space containing all points in the plane of these vectors, the vector $[ 2 , 0 , 1 ] ^ { T } \in \mathcal { V }$ can be shown to have coordinates $[ \sqrt { 3 } , \sqrt { 2 } ] ^ { T }$ (using the dot product method). Even though the basis vectors are drawn from $\mathcal { R } ^ { 3 }$ , the vector space  is a 2-dimensional plane, and it will have only two coordinates. 

It is much trickier to find the coordinates of a vector v in a non-orthogonal basis system. The general problem is that of solving the system of equations $A { \overline { { x } } } = { \overline { { v } } }$ for $\overline { { x } } = [ x _ { 1 } \ldots x _ { d } ] ^ { T }$ where the n-dimensional columns of the $n \times d$ matrix A contain the (linearly independent) basis vectors. The problem boils down to finding a solution to the system of equations $A { \overline { { x } } } = { \overline { { v } } }$ , where $A = [ \overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d } ]$ contains the basis vectors of the d-dimensional vector space $\mathcal { V } \subseteq \mathcal { R } ^ { n }$ . Note that the basis vectors are themselves represented using n components like the vectors of $\mathcal { R } ^ { n }$ , even though the vector space is a d-dimensional subspace of $\mathcal { R } ^ { n }$ and the coordinate vector x lies in $\mathcal { R } ^ { d }$ . If $d = n$ , and the matrix A is square, the solution is simply ${ \overline { { x } } } = A ^ { - 1 } { \overline { { v } } }$ . However, when A is not square, one may not be able to find valid coordinates, if v does not lie in $\nu \subset \mathcal { R } ^ { n }$ . This occurs when v does not geometrically lie on the hyperplane $H _ { A }$ defined by all possible linear combinations of the columns of A. However, one can find the best fit coordinates x by observing that the line joining the closest linear combination Ax of the columns of A to v must be orthogonal to the hyperplane $H _ { A }$ , and it is therefore also orthogonal to every column of A. The condition that $\left( A { \overline { { x } } } - { \overline { { v } } } \right)$ is orthogonal to every column of A can be expressed as the normal equation $A ^ { T } ( A { \overline { { x } } } - { \overline { { v } } } ) = { \overline { { 0 } } }$ . This results in the following: 

$$
\overline {{x}} = (A ^ {T} A) ^ {- 1} A ^ {T} \overline {{v}}\tag{2.6}
$$

The best-fit solution includes the exact solution when it is possible. The matrix $( A ^ { T } A ) ^ { - 1 } A ^ { T }$ is referred to as the left-inverse of the matrix A with linearly independent columns and we will encounter it repeatedly in this book via different derivations (see Section 2.8). 

In order to illustrate the nature of coordinate transformations, we will show the coordi nates of the same vector $[ 1 0 , 1 5 ] ^ { T }$ in three different basis sets including the standard basis set. The three basis sets correspond to the standard basis set, a basis set $\left\{ \left[ \frac { 3 } { 5 } , \frac { 4 } { 5 } \right] ^ { T } , \left[ - \frac { 4 } { 5 } , \frac { 3 } { 5 } \right] ^ { T } \right\}$ obtained by rotating each vector in the standard basis counter-clockwise by $\sin ^ { - 1 } ( 4 / 5 )$ and a non-orthogonal basis $\{ [ 1 , 1 ] ^ { T } , [ 1 , 2 ] ^ { T } \}$ in which the vectors are not even unit normalized. Each of these basis sets defines a coordinate system for representing $\mathcal { R } ^ { 2 }$ , and the non-orthogonal coordinate system seems very different from the conventional system of Cartesian coordinates. The corresponding basis directions are shown in Figure 2.5(a), (b), and (c), respectively. For the case of the standard basis in Figure 2.5(a), the coordinates of the vector $[ 1 0 , 1 5 ] ^ { T }$ are the same as its vector components (i.e., 10 and 15). However, this is not the case in any other basis. The coordinates of the vector $[ 1 0 , 1 5 ] ^ { T }$ in the orthonormal (rotated) basis of Figure 2.5(b) are $[ 1 8 , 1 ] ^ { T }$ , and the coordinates in the non-orthogonal basis of Figure 2.5(c) are $[ 5 , 5 ] ^ { T }$ . The explanation for these values of the coordinates arises from the decomposition of $[ 1 \dot { 0 } , 1 5 ] ^ { T }$ in terms of various basis sets: 

![image](<Images/02_Linear_Transformations_and_Linear_Systems_image_005.jpg>)



(a) Basis $\{ [ 1 , 0 ] ^ { T } , [ 0 , 1 ] ^ { T } \}$ (Standard basis)


![image](<Images/02_Linear_Transformations_and_Linear_Systems_image_006.jpg>)



(b) Basis 45 T 2 #5， 4 , u T (Rotated orthonormal basis)


![image](<Images/02_Linear_Transformations_and_Linear_Systems_image_007.jpg>)



(c) Basis $\{ [ 1 , 1 ] ^ { T } , [ 1 , 2 ] ^ { T } \}$ (Non-orthogonal basis)


Figure 2.5: Examples of different bases in $\mathcal { R } ^ { 2 }$ with corresponding coordinates of the same vector [10, 15]<sup>T</sup> . A basis set may be non-orthogonal and unnormalized, as in (c) 

![image](<Images/02_Linear_Transformations_and_Linear_Systems_image_008.jpg>)


Although the notion of a non-orthogonal coordinate system does exist in analytical geometry, it is rarely used in practice because of loss of visual interpretability of the coordinates. However, such non-orthogonal basis systems are very natural to linear algebra, where some loss of geometric intuition is often compensated by algebraic simplicity. 

## 2.3.2 Coordinate Transformations Between Basis Sets

The previous section discusses how different basis sets correspond to different coordinate systems for the vectors in $\mathcal { R } ^ { n }$ . A natural question arises as to how one can transform the coordinates $\scriptstyle { { \overline { { x } } } _ { a } }$ defined with respect to the n-dimensional basis set $\{ \overline { { a } } _ { 1 } , \ldots , \overline { { a } } _ { n } \}$ of $\mathcal { R } ^ { n }$ into the coordinates $\overline { { x } } _ { b }$ defined with respect to the n-dimensional basis set $\{ \overline { { b } } _ { 1 } , \ldots , \overline { { b } } _ { n } \}$ . The goal is to find an $n \times n$ matrix $P _ { a  b }$ that transforms $\overline { { x } } _ { a }$ to $\overline { { x } } _ { b }$ : 

$$
\overline {{x}} _ {b} = P _ {a \rightarrow b} \overline {{x}} _ {a}
$$

For example, how might one transform the coordinates in the orthogonal basis set of Figure 2.5(b) into the non-orthogonal system of Figure 2.5(c)? Here, the key point is to observe that the coordinates $\overline { { x } } _ { a }$ and $\overline { { x } } _ { b }$ are representations of the same vector, and they would therefore have the same coordinates in the standard basis. First, we use the basis sets to construct two $n \times n$ matrices $A = \left[ { \overline { { a } } } _ { 1 } \ldots \ldots { \overline { { a } } } _ { n } \right]$ and $B = [ \overline { { b } } _ { 1 } \ldots \overline { { b } } _ { n } ]$ . Since the coordinates $\scriptstyle { \overline { { x } } }$ of $\scriptstyle { { \overline { { x } } } _ { a } }$ and $\overline { { x } } _ { b }$ must be identical in the standard basis, we have the following: 

$$
A \overline {{{x}}} _ {a} = B \overline {{{x}}} _ {b} = \overline {{{x}}}
$$

We have already established (cf. Lemma 2.3.1) that square matrices defined by linearly independent vectors are invertible. Therefore, multiplying both sides with $B ^ { - 1 }$ , we obtain the following: 

$$
\overline {{x}} _ {b} = \underbrace {[ B ^ {- 1} A ]} _ {P _ {a \to b}} \overline {{x}} _ {a}
$$

In order to verify that this matrix does indeed perform the intended transformation, let us compute the coordinate transformation matrix from the system in Figure 2.5(b) to the system in Figure 2.5(c). Therefore, our matrices $A$ and $B$ in these two cases can be constructed using the basis vectors in Figure 2.5 as follows: 

$$
A = \left[ \begin{array}{c c} 3 / 5 & - 4 / 5 \\ 4 / 5 & 3 / 5 \end{array} \right], \quad B = \left[ \begin{array}{c c} 1 & 1 \\ 1 & 2 \end{array} \right], \quad B ^ {- 1} = \left[ \begin{array}{c c} 2 & - 1 \\ - 1 & 1 \end{array} \right]
$$

The coordinate transformation matrix can be computed as follows: 

$$
P _ {a \to b} = B ^ {- 1} A = \left[ \begin{array}{c c} 2 & - 1 \\ - 1 & 1 \end{array} \right] \left[ \begin{array}{c c} 3 / 5 & - 4 / 5 \\ 4 / 5 & 3 / 5 \end{array} \right] = \left[ \begin{array}{c c} 2 / 5 & - 1 1 / 5 \\ 1 / 5 & 7 / 5 \end{array} \right]
$$

In order to check whether this coordinate transformation works correctly, we want to check whether the coordinate $[ 1 8 , 1 ] ^ { T }$ in Figure 2.5(b) gets transformed to $[ 5 , 5 ] ^ { T }$ in Figure 2.5(c): 

$$
P _ {a \to b} \left[ \begin{array}{c} 1 8 \\ 1 \end{array} \right] = \left[ \begin{array}{c c} 2 / 5 & - 1 1 / 5 \\ 1 / 5 & 7 / 5 \end{array} \right] \left[ \begin{array}{c} 1 8 \\ 1 \end{array} \right] = \left[ \begin{array}{c} 5 \\ 5 \end{array} \right]
$$

Therefore, the transformation matrix correctly converts coordinates from one system to another. The main computational work involved in the transformation is in inverting the matrix B. One observation is that when $B$ is an orthogonal matrix, the transformation matrix simplifies to $B ^ { T } A$ . Furthermore, when the matrix A $( { \mathrm { i . e . } }$ , source representation) corresponds to the standard basis, the transformation matrix is $B ^ { T }$ . Therefore, working with orthonormal bases simplifies computations, which is why the identification of orthonorma basis sets is an important problem in its own right (cf. Section 2.7.1). 

It is also possible to perform coordinate transformations between basis sets that define a particular d-dimensional subspace of $\mathcal { R } ^ { n }$ , rather than all of $\mathcal { R } ^ { n }$ . Let $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d }$ amd $\overline { { b } } _ { 1 } \ldots \overline { { b } } _ { d }$ be two basis sets for this d-dimensional subspace , such that each of these basis vectors is expressed in terms of the standard basis of $\mathcal { R } ^ { n }$ . Furthermore, let $\overline { { x } } _ { a }$ and $\overline { { x } } _ { b }$ be two ddimensional coordinates of the same vector $\overline { { v } } \in \mathcal { V }$ in terms of the two basis sets. We want to transform the known coordinates $\scriptstyle { { \overline { { x } } } _ { a } }$ to the unknown coordinates $\overline { { x } } _ { b }$ in the second basis set (and find a best fit if the two basis sets represent different vector spaces). As in the previous case, let $A = [ \overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d } ]$ and $B = [ \overline { { b } } _ { 1 } \ldots \overline { { b } } _ { d } ]$ be two $n \times d$ matrices whose columns contain each of these two sets of basis vectors. Since $\overline { { x } } _ { a }$ and $\overline { { x } } _ { b }$ are coordinates of the same vector, and have the same coordinates in the standard basis of $\mathcal { R } ^ { n }$ , we have $A \overline { { x } } _ { a } = B \overline { { x } } _ { b }$ However, since the matrix B is not square, it cannot be inverted in order to solve for $\overline { { x } } _ { b }$ in terms of ${ \overline { { x } } } _ { a } ,$ and we sometimes might have to be content with a best fit. We observe that this best-fit problem is similar to what was derived in Equation 2 6 with the use of the normal equation, and $A \overline { { x } } _ { a } - B \overline { { x } } _ { b }$ needs to be orthogonal to every column of B in order to be a best-fit solution. This implies that $B ^ { T } ( A \overline { { x } } _ { a } - \bar { B } \overline { { x } } _ { b } ) = \overline { { 0 } }$ , and we have the following: 

$$
\overline {{x}} _ {b} = \underbrace {(B ^ {T} B) ^ {- 1} B ^ {T} A} _ {\mathcal {P} _ {a \to b}} \overline {{x}} _ {a}
$$

When B is square and invertible, it is easy to show that this solution simplifies to $B ^ { - 1 } A \overline { { x } } _ { a }$ 

![image](<Images/02_Linear_Transformations_and_Linear_Systems_image_009.jpg>)


![image](<Images/02_Linear_Transformations_and_Linear_Systems_image_010.jpg>)



(a) Span({A, B}) = Span({A, B, ¯}) Span({A, B, C}) = All vectors on hyperplane



(b) Span({A, B}) ≠ Span({A, B, ¯}) Span({A, B, ¯}) = All vectors in $\mathcal { R } ^ { 3 }$



Figure 2.6: The span of a set of linearly dependent vectors has lower dimension than the number of vectors in the set


## 2.3.3 Span of a Set of Vectors

Even though a vector space is naturally defined by a basis set (which is linearly independent), one can also define a vector space by using a set of linearly dependent vectors. This is achieved with the notion of span: 

Definition 2.3.7 (Span) The span of a finite set of vectors $\mathcal { A } = \{ \overline { { a } } _ { 1 } , \ldots , \overline { { a } } _ { d } \}$ is the vector space defined by all possible linear combinations of the vectors in : 

$$
S p a n (\mathcal {A}) = \{\overline {{v}}: \overline {{v}} = \sum_ {i = 1} ^ {d} x _ {i} \overline {{a}} _ {i}, \forall x _ {1} \dots x _ {d} \in \mathcal {R} \}
$$

For example, consider the vector spaces drawn on $\mathcal { R } ^ { 3 }$ . In this case, the span of the two vectors $[ \bar { 0 , 2 , 1 } ] ^ { T } , [ 1 , 2 , 1 ] ^ { T }$ is the set of all vectors lying on the 2-dimensional hyperplane defined by the vectors $[ \bar { 0 } , 2 , 1 ] ^ { T }$ and $[ 1 , 2 , 1 ] ^ { T }$ . Points that do not lie on this hyperplane do not lie in the span of two vectors. The span of an augmented set of three vectors, which additionally includes the vector $[ 1 , 0 , 0 ] ^ { \dot { T } } ;$ , is no different from the span of the first two vectors; this is because the vector $[ 1 , 0 , \dot { 0 } ] ^ { T }$ is linearly dependent on $[ 0 , \bar { 2 } , 1 ] ^ { T }$ and $] 1 , 2 , 1 ] ^ { T }$ Therefore, adding a vector to a set increases its span only when the added vector does not lie in the subspace defined by the span of . When the set contains linearly independent vectors, it is also a basis set of its span. 

A pictorial example of what a span captures in $\mathcal { R } ^ { 3 }$ is illustrated in Figure 2.6. In Fig ure 2.6(a), the three vectors ${ \overline { { A } } } , { \overline { { B } } } ,$ , and $\overline { { C } }$ lie on a hyperplane passing through the origin, although they are pairwise linearly independent. Therefore, any pair of them can span the 2-dimensional subspace containing all vectors lying on this hyperplane; however, the span of all three vectors is still this same subspace because of the linear dependence of the three vectors. Adding any number of vectors lying on the hyperplane to the set will not change the span of the set. On the other hand, the three vectors in Figure 2.6(b) are linearly independent, and therefore their span is $\mathcal { R } ^ { 3 }$ 

Since the three vectors in Figure 2.6(b) are linearly independent and span $\mathcal { R } ^ { 3 }$ , they can be used to create a valid coordinate system to represent any vector in $\mathcal { R } ^ { 3 }$ (albeit a non-orthogonal one). A natural question arises as to what would happen if one tried to use the three linearly dependent vectors ${ \overline { { A } } } , { \overline { { B } } } .$ , and $\overline { C }$ in Figure $2 . 6 ( \mathrm { a } )$ to create a “coordinate system” of $\mathcal { R } ^ { 3 }$ . First, note that any 3-dimensional vector that does not lie on the hyperplane of Figure $2 . 6 ( \mathrm { a } )$ cannot be represented as a linear combination of the three vectors A, ${ \overline { { B } } } ,$ and ${ \check { C } } .$ . Therefore, no valid coordinates would exist to represent such a vector. Furthermore, even in cases where $\bar { b }$ does lie on the hyperplane of Figure 2.6(a), the solution to $A { \overline { { x } } } = { \overline { { b } } }$ may not be unique because of linear dependence of the columns of A, and therefore unique “coordinates” may not exist. 

## 2.3.4 Machine Learning Example: Discrete Wavelet Transform

Basis transformations are used frequently in machine learning of time series. A time-series of length n can be treated as a point in $\mathcal { R } ^ { n }$ , where each real value represents the series value at a clock tick. For example, a time-series of temperatures collected each second over an hour would result in a vector from $\mathcal { R } ^ { 3 , 6 0 0 }$ . One common characteristic of time-series is that consecutive values are very similar in most real applications; for example, consecutive temperature readings would typically be the same almost all the time. Therefore, most of the information would be hidden in a few variations across time. The Haar wavelet transformation performs precisely a basis transformation that extracts the important variations. Typically, only a few such differences will be large, which results in a sparse vector. Aside from the space-efficiency advantages of doing so, some predictive algorithms seem to work better with coordinates that reflect trend differences. 

For example, consider the series $\overline { { s } } ~ = ~ [ 8 , 6 , 2 , 3 , 4 , 6 , 6 , 5 ] ^ { T }$ in $\mathcal { R } ^ { 8 }$ . The representation corresponds to the values in the standard basis. However, we want a basis in which the differences between contiguous regions of the series are emphasized. Therefore, we define the following set of 8 vectors to create a new basis in $\mathcal { R } ^ { 8 }$ together with an interpretation of what their coefficients represent to within a proportionality factor: 

<table><tr><td>Interpretation of basis coefficient</td><td>Unnormalized basis vectors</td><td>Basis vector norm</td></tr><tr><td>Series sum</td><td><eq>[1, 1, 1, 1, 1, 1, 1, 1]^T</eq></td><td><eq>\sqrt{8}</eq></td></tr><tr><td>Difference between halves</td><td><eq>[1, 1, 1, 1, -1, -1, -1, -1]^T</eq></td><td><eq>\sqrt{8}</eq></td></tr><tr><td>Difference between quarters</td><td><eq>[1, 1, -1, -1, 0, 0, 0, 0]^T</eq><eq>[0, 0, 0, 0, 1, 1, -1, -1]^T</eq></td><td><eq>\sqrt{4}</eq><eq>\sqrt{4}</eq></td></tr><tr><td>Difference between eighths</td><td><eq>[1, -1, 0, 0, 0, 0, 0]^T</eq><eq>[0, 0, 1, -1, 0, 0, 0, 0]^T</eq><eq>[0, 0, 0, 0, 1, -1, 0, 0]^T</eq><eq>[0, 0, 0, 0, 0, 0, 1, -1]^T</eq></td><td><eq>\sqrt{2}</eq><eq>\sqrt{2}</eq><eq>\sqrt{2}</eq><eq>\sqrt{2}</eq></td></tr></table>

Note that all basis vectors are orthogonal, although they are not normalized to unit norm. We would like to transform the time-series from the standard basis into this new set of orthogonal vectors (after normalization). The problem is simplified by the fact that we have to transform from a standard basis. As discussed at the end of the previous section, we can create an orthogonal matrix B using these vectors, and then simply multiply the time series $\overline { { s } } = [ 8 , 6 , 2 , 3 , 4 , 6 , 6 , 5 ] ^ { T }$ with $B ^ { T }$ to create the transformed representation. Note that the transposed matrix $B ^ { T }$ will contain the basis vectors in its rows rather than columns. For numerical and computational efficiency, we will not normalize the columns of B to unit norm up front, and simply normalize the coordinates of s after multiplying with the unnormalized matrix $B ^ { T }$ . Therefore, the unnormalized coordinates $\overline { { s } } _ { u }$ and normalized coordinates $\textstyle { \overline { { s } } } _ { n }$ can be computed as follows: 

$$
\overline {{s}} _ {u} = \underbrace {\left[ \begin{array}{c c c c c c c c} 1 & 1 & 1 & 1 & 1 & 1 & 1 & 1 \\ 1 & 1 & 1 & 1 & - 1 & - 1 & - 1 & - 1 \\ 1 & 1 & - 1 & - 1 & 0 & 0 & 0 & 0 \\ 0 & 0 & 0 & 0 & 1 & 1 & - 1 & - 1 \\ 1 & - 1 & 0 & 0 & 0 & 0 & 0 & 0 \\ 0 & 0 & 1 & - 1 & 0 & 0 & 0 & 0 \\ 0 & 0 & 0 & 0 & 1 & - 1 & 0 & 0 \\ 0 & 0 & 0 & 0 & 0 & 0 & 1 & - 1 \end{array} \right]} _ {B ^ {T}} \underbrace {\left[ \begin{array}{c} 8 \\ 6 \\ 2 \\ 3 \\ 4 \\ 6 \\ 6 \\ 5 \end{array} \right]} _ {\overline {{s}}} = \left[ \begin{array}{c} 4 0 \\ - 2 \\ 9 \\ - 1 \\ 2 \\ - 1 \\ - 2 \\ 1 \end{array} \right], \quad \overline {{s}} _ {n} = \left[ \begin{array}{c} 4 0 / \sqrt {8} \\ - 2 / \sqrt {8} \\ 9 / \sqrt {4} \\ - 1 / \sqrt {4} \\ 2 / \sqrt {2} \\ - 1 / \sqrt {2} \\ - 2 / \sqrt {2} \\ 1 / \sqrt {2} \end{array} \right]
$$

The rightmost vector $\overline { { s } } _ { n }$ contains the normalized wavelet coefficients. In many cases, the dimensionality of the time-series is reduced by dropping those coefficients that are very small in absolute magnitude. Therefore, a compressed representation of the time series can be created. Note that the matrix B is very sparse, and it contains $O ( n \log ( n ) )$ non-zero entries for a transformation in $\mathcal { R } ^ { n }$ . Furthermore, since the matrix only contains values from $\{ - 1 , 0 , + 1 \}$ , the matrix multiplication reduces to only addition or subtraction of vector components. In other words, such a matrix multiplication is very efficient. 

## 2.3.5 Relationships Among Subspaces of a Vector Space

In this section, we study the different types of relationships among the subspaces of a vector space. Although this section makes the assumption that all vector spaces are subspaces of $\mathcal { R } ^ { n }$ (because of the relevance to machine learning), the underlying results hold even under more general assumptions. First, we discuss the concept of disjoint vector spaces: 

Definition 2.3.8 (Disjoint Vector Spaces) Two vector spaces $\mathcal { U } \subseteq \mathcal { R } ^ { n }$ and $\mathcal { W } \subseteq \mathcal { R } ^ { n }$ are disjoint if and only if the two spaces do not contain any vector in common other than the zero vector. 

If and are disjoint with basis sets $B _ { u }$ and $B _ { w }$ , the union $B = B _ { u } \cup B _ { w }$ of these basis sets is a linearly independent set. Otherwise, we can apply the linear dependence condition to and place elements from each of the vector spaces on the two sides of the dependence condition to create a vector that lies in both and . This is a contradiction to the pre-condition of disjointedness. 

An origin-centered plane in $\mathcal { R } ^ { 3 }$ and an origin-centered line in $\mathcal { R } ^ { 3 }$ represent disjoint vector spaces as long as the line is not subsumed by the plane. However, vector spaces created by any pair of origin-centered planes in $\mathcal { R } ^ { 3 }$ are not disjoint because they intersect along a 1-dimensional line. The hyperplanes corresponding to two disjoint vector spaces must intersect only at the origin, which is a 0-dimensional vector space. A special case of disjointedness of vector spaces is that of orthogonality of the two spaces: 

Definition 2.3.9 (Orthogonal Vector Spaces) Two vector spaces $\mathcal { U } \subseteq \mathcal { R } ^ { n }$ and $\mathcal { W } \subseteq$ $\mathcal { R } ^ { n }$ are orthogonal if and only if for any pair of vectors ${ \overline { { u } } } \in { \mathcal { U } }$ and $\overline { { w } } \in \mathcal { W }$ , the dot product of the two vectors is 0: 

$$
\overline {{u}} \cdot \overline {{w}} = 0\tag{2.7}
$$

![image](<Images/02_Linear_Transformations_and_Linear_Systems_image_011.jpg>)



Figure 2.7: Illustration of complementary subspace


Disjoint pairs of vector spaces need not be orthogonal, but orthogonal pairs of vector spaces are always disjoint. One can show this result by contradiction. If the orthogonal vector spaces and are not disjoint, one can select ${ \overline { { u } } } \in { \mathcal { U } }$ and $\overline { { w } } \in \mathcal { W }$ to be the same non-zero vector $( \mathrm { i . e . , } \overline { { u } } = \overline { { w } } \neq \overline { { 0 } } )$ from the non-disjoint portion of the space, which cannot satisfy the condition of Equation 2.7 (and this results in a contradiction). 

Two orthogonal subspaces, such that the union of their basis sets span all of $\mathcal { R } ^ { n }$ are referred to as orthogonal complementary subspaces. 

Definition 2.3.10 (Orthogonal Complementary Subspace) Let be a subspace of $\mathcal { R } ^ { n }$ . Then, is an orthogonal complementary subspace of if and only if it satisfies the following properties: 

The spaces and are orthogonal (and therefore disjoint). 

The union of the basis sets of and forms a basis for $\mathcal { R } ^ { n }$ 

The notion of orthogonal complementary subspace is a special case of that of complementary subspaces. Two subspaces are complementary when they are disjoint and the union of their basis sets spans all of $\mathcal { R } ^ { n }$ . However, they need not be orthogonal. For a given subspace, there are an infinite number of complementary subspaces, whereas there is only one orthogonal complementary subspace. Consider the case in which the subspace of $\mathcal { R } ^ { 3 }$ is the set of all vectors lying on a 2-dimensional plane passing through the origin. This plane is shown in Figure 2.7. Then any of the infinite number of vectors that emanate from the origin and do not lie on this plane can be used as the singleton basis set to define a complementary 1-dimensional subspace of . However, there is a unique subspace defined by the vector perpendicular to this plane, which is the orthogonal complementary subspace with respect to . 

Problem 2.3.2 Consider two disjoint vector spaces in $\mathcal { R } ^ { 3 }$ with basis sets $\{ [ 1 , 1 , 1 ] ^ { T } \}$ and $\{ [ 1 , 0 , 0 ] ^ { T } , [ 0 , 1 , 0 ] ^ { T } \}$ , respectively. Express the vector $[ 0 , 1 , 1 ] ^ { T }$ as the sum of two vectors, such that each of them belongs to one of the two spaces. Note that you will have to solve a system of three linear equations to solve this problem. 

Problem 2.3.3 Let $\mathcal { U } \subset \mathcal { R } ^ { 3 }$ be defined by the basis set $\{ [ 1 , 0 , 0 ] ^ { T } , [ 0 , 1 , 0 ] ^ { T } \}$ . State the basis sets of two possible complementary subspaces of . In each case, provide a decomposition of the vector $[ 1 , 1 , 1 ] ^ { T }$ as a sum of vectors from these complementary subspaces. 

Problem 2.3.4 Let $\mathcal { U } \subset \mathcal { R } ^ { 3 }$ be defined by the basis set $\boldsymbol { B } = \{ [ 1 , 1 , 1 ] ^ { T } , [ 1 , - 1 , 1 ] ^ { T } \}$ . Formulate a system of equations to find the orthogonal complementary subspace  of . Use the orthogonality of and to propose a fast method to express the vector $[ 2 , 2 , 1 ] ^ { T }$ as a sum of vectors from these complementary subspaces. 

## 2.4 The Linear Algebra of Matrix Rows and Columns

The rows and columns of an $n \times d$ matrix A span vector spaces, referred to as row spaces and column spaces, respectively. 

Definition 2.4.1 (Row Spaces and Column Spaces) For an $n \times d$ matrix A, its column space is defined as the vector space spanned by its columns, and it is a subspace of $\mathcal { R } ^ { n }$ The row space of A is defined as the vector space spanned by the columns of $A ^ { T }$ (which are simply the transposed rows of A). The row space of A is a subspace of $\mathcal { R } ^ { d }$ 

A remarkable result in linear algebra is that the dimensionality of the row space (also referred to as row rank) and that of the column space (also referred to as column rank) of any $n \times d$ matrix A is the same. We will show this result slightly later. We have already shown this equivalence in some special cases where the rows of a square matrix must be linearly independent when the columns are linearly independent, and vice versa (cf. Lemma 2.3.1). Such matrices are said to be of full rank. Rectangular matrices are said to be of full rank when either the rows $o r$ the columns are linearly independent. The former is referred to as full row rank, whereas the latter is referred to as full column rank. 

Since the columns of an $n \times d$ matrix A might span only a subspace of $\mathcal { R } ^ { n }$ and the (transposed) rows of A might span only a subspace of $\mathcal { R } ^ { d }$ , how does one characterize the orthogonal complements of these subspaces? This is achieved with the notion of null spaces. 

Definition 2.4.2 (Null Space) The null space of a matrix A is the subspace of $\mathcal { R } ^ { d }$ containing all column vectors $\overline { { x } } \in \mathcal { R } ^ { d }$ , such that $A { \overline { { x } } } = { \overline { { 0 } } }$ 

The null space of a matrix A is essentially the orthogonal complementary subspace of the row space of A. The reason is that the condition $A { \overline { { x } } } = { \overline { { 0 } } }$ ensures that the dot product of x with each transposed row of A (or a linear combination of them) is 0. Note that if $d > n$ , the d-dimensional rows of A (after transposition to column vectors) will always span a proper subspace of $\mathcal { R } ^ { d }$ , whose orthogonal complement is non-empty; in other words, the null space of A will be non-empty in this case. For square and non-singular matrices, the null space only contains the zero vector. 

The notion of a null space refers to a right null space by default. This is because the vector x occurs on the right side of matrix A in the product Ax, which must evaluate to the zero vector. Similar to the definition of a right null space, one can define the $l e f t$ null space of a matrix, which is the orthogonal complement of the vector space spanned by the columns of the matrix. 

Definition 2.4.3 (Left Null Space) The left null space of an $n \times d$ matrix A is the subspace of $\mathcal { R } ^ { n }$ containing all column vectors $\overline { { x } } \in \mathcal { R } ^ { n }$ , such that $A ^ { T } { \overline { { x } } } = { \overline { { 0 } } }$ . The $l e f t$ null space of A is the orthogonal complementary subspace of the column space of A. 

Alternatively, the left null space of a matrix A contains all vectors $\textstyle { \overline { { x } } }$ satisfying $\overline { { x } } ^ { T } A = \overline { { 0 } } ^ { T }$ The row space, column space, the right null space, and the left null space are referred to as the four fundamental subspaces of linear algebra. 

![image](<Images/02_Linear_Transformations_and_Linear_Systems_image_012.jpg>)



Figure 2.8: The four fundamental subspaces of linear algebra for an $n \times d$ matrix A


In Figure 2.8, we have shown the relationships among the four fundamental subspaces of linear algebra for an $n \times d$ matrix A. In this particular case, the value of n is chosen to be greater than d. Multiplying A with any d-dimensional vector $\overline { { x } } \in \mathcal { R } ^ { d }$ maps to the column space of A (including the zero vector) because the vector Ax is a linear combination of the columns of A. Similarly, multiplying any n-dimensional vector $\overline { { y } } \in \mathcal { R } ^ { n }$ with $A ^ { T }$ to create the vector $A ^ { T } { \overline { { y } } }$ yields a member of the row space of $A$ , which is a linear combination of the (transposed) rows of A. Another noteworthy point in Figure 2.8 is that the ranks $o f$ the row space and the column space are the same. The equality is a fundamental result in linear algebra, which will be shown in a later section. The fixed value of the row rank and column rank is also referred to as the rank of the matrix. For example, consider the following $3 \times 4$ matrix: 

$$
A = \left[ \begin{array}{c c c c} 1 & 0 & 1 & 0 \\ 0 & 1 & 0 & 1 \\ 1 & 1 & 1 & 1 \end{array} \right]\tag{2.8}
$$

Note that neither the rows nor the columns of this matrix are linearly independent. The row space has the basis vectors $[ 1 , 0 , 1 , 0 ] ^ { T }$ , and $[ 0 , 1 , 0 , 1 ] ^ { T }$ , whereas the column space has the basis vectors $[ 1 , 0 , 1 ] ^ { T }$ , and $[ 0 , 1 , 1 ] ^ { T }$ . Therefore, the row rank is the same as the column rank, which is the same as the matrix rank of 2. 

Problem 2.4.1 Find a basis for each of the right and left null spaces of matrix A in Equation 2.8. 

Problem 2.4.2 For any $n \times d$ matrix A, show why the matrices $P = A ^ { T } A + \lambda I _ { d }$ and $Q = A A ^ { T } + \lambda I _ { n }$ always have an empty null space for any $\lambda > 0$ 

A hint for solving the above problem is to show that $\overline { { x } } ^ { T } P \overline { { x } }$ can never be zero. 

## 2.5 The Row Echelon Form of a Matrix

The row echelon form is useful for transforming matrices to simpler forms with elementary row operations (cf. Section 1.3.1 of Chapter 1) that are row equivalent to the original matrix. The material in this section is therefore based on the row operation concepts developed in Section 1.3.1. 

Definition 2.5.1 (Row and Column Equivalence) Two matrices are said to be row equivalent, if one matrix is obtained from the other by a sequence of elementary row operations such as row interchange, row addition, or multiplication of a row with a non-zero scalar. Similarly, two matrices are said to be column equivalent, if one matrix is obtained from the other with a sequence of elementary column operations. 

Note that applying elementary row operations does not change the vector space spanned by the rows of a matrix. This is because row interchange and non-zero scaling operations do not fundamentally change the (normalized) row set of the matrix. Furthermore, the span of any pair of row vectors $\{ \overline { { r } } _ { i } , \overline { { r } } _ { j } \}$ is the same as that of $\{ \overline { { { r } } } _ { i } , \overline { { { r } } } _ { i } + c \overline { { { r } } } _ { j } \}$ for non-zero scalar c because $\overline { { r } } _ { j }$ can be expressed in terms of the new set of rows as $[ ( \overline { { r } } _ { i } + c \overline { { r } } _ { j } ) - \overline { { r } } _ { i } ] / c .$ . Therefore, any vector in the span of the original set of rows is also in the span of the new set of rows. The converse can also be seen to be true because the new row vectors are directly expressed in terms of the original rows. Similarly, column operations do not change the column space. However, row operations do change the column space, and column operations do change the row space. These results are summarized as follows: 

Lemma 2.5.1 Elementary row operations do not change the vector space spanned by the rows, whereas elementary column operations do not change the vector space spanned by the columns. 

A particularly convenient row-equivalent conversion of the matrix A is the row echelon form, which is useful for solving linear systems of the type $A { \overline { { x } } } = { \overline { { b } } }$ . By applying the same row operations to both the matrix A and the vector b in the system of equations $A { \overline { { x } } } = { \overline { { b } } }$ , one can simplify the matrix A to a form that makes the system easily solvable. This is exactly the row echelon form, and the procedure is equivalent to the Gaussian elimination method for solving systems of equations. 

Definition 2.5.2 (Row Echelon Form) An $n \times d$ matrix A is said to be in row echelon form, if and only if (i) the leftmost non-zero entry in each row is 1, (ii) the column index of the leftmost non-zero entry in each row increases with row index, and (iii) all zero rows (if any) occur at the bottom of the matrix. 

All row echelon matrices are (rectangular) upper-triangular matrices, but the converse is not true. For example, consider the following pair of upper-triangular matrices: 

$$
A ^ {\prime} = \left[ \begin{array}{l l l l l} 1 & 7 & 4 & 3 & 5 \\ 0 & 0 & 1 & 7 & 6 \\ 0 & 0 & 0 & 1 & 3 \\ 0 & 0 & 0 & 0 & 1 \end{array} \right] \quad B ^ {\prime} = \left[ \begin{array}{l l l l l} 1 & 7 & 4 & 3 & 5 \\ 0 & 0 & 1 & 7 & 6 \\ 0 & 0 & 1 & 5 & 3 \\ 0 & 0 & 0 & 0 & 1 \end{array} \right]
$$

Here, the matrix $A ^ { \prime }$ is in row echelon form, whereas the matrix $B ^ { \prime }$ is not. This is because the leftmost non-zero entry of the second and third rows of matrix $B ^ { \prime }$ have the same column index. The increasing column index of the leading non-zero entry ensures that non-zero rows in echelon form are always linearly independent; adding rows in the order from bottom to top of the matrix to a set S always increases the span of S by 1. 

The bulk of the work in Gaussian elimination is to create a matrix in which the column index of the leftmost non-zero entry is different for each row; further row interchange operations can create a matrix in which the leftmost non-zero entry has an increasing column index, and row scaling operations can change the leftmost entry to 1. The entire process uses three phases: 

Row addition operations: We repeatedly identify pairs of rows, so that the column index of the leftmost non-zero entry is the same. For example, the second and third rows of matrix $B ^ { \prime }$ in the above example have a tied column index of the leftmost non-zero entry. The elementary row addition operation is applied to the pair so that one of these leftmost entries is set to 0. For example, consider two rows $\overline { { r } } _ { 1 }$ and $\overline { { r } } _ { 2 }$ with the same leftmost column index. If the leftmost non-zero entries of rows $\overline { { r } } _ { 1 }$ and $\overline { { r } } _ { 2 }$ have values 3 and $^ { 7 , }$ respectively, then we can change row $\overline { { r } } _ { 1 }$ to $\overline { { r } } _ { 1 } - ( 3 / 7 ) \overline { { r } } _ { 2 }$ , so that the leftmost entry of $\overline { { r } } _ { 1 }$ becomes 0. We could also change $\overline { { r } } _ { 2 }$ to $\overline { { r } } _ { 2 } - ( 7 / 3 ) \overline { { r } } _ { 1 }$ to achieve a similar effect. We always choose to perform the operation on the lower of the two rows in order to ensure that the corresponding operator matrix is a lower triangular matrix and the number of leading zeros in the lower row increases by 1. Since the matrix contains $n \times d$ entries, and each operation increases the number of leading zeros in the matrix, the procedure is guaranteed to succeed in removing column-index ties after $O ( n d )$ row addition operations [each of which requires $O ( d )$ time]. However, depending on the configuration of the original matrix, one may not be able to reach a matrix in which the column index of the leftmost non-zero entry always increases. For example, a $2 \times 2$ matrix with a value of 0 in the top-left corner and a value of 1 in every other entry can never be converted to upper-triangular form with row addition operations. 

Row interchange operations: In this phase, we permute the rows of the matrix, so that the column index of the leftmost non-zero entry increases with increasing column index. The permutation of the rows is achieved by interchanging “violating” pairs of rows repeatedly, which do not satisfy the aforementioned condition. Random selection of violating pairs will require $O ( d ^ { 2 } )$ interchanges, although more judicious selection can ensure that this is done in $O ( d )$ interchanges. 

Row scaling operations: Each row is divided by its leading non-zero entry to convert the matrix to row echelon form. 

All of the above operations can be implemented with the elementary row operations dis cussed in Section 1.3.1 of Chapter 1. 

## 2.5.1 LU Decomposition

The goal of LU decomposition is to express a matrix as the product of a (square) lower triangular matrix L and a (rectangular) upper triangular matrix U. However, it is not always possible to create an LU decomposition of a matrix without permuting its rows first. We provide an example in which row permutation is essential: 

Observation 2.5.1 A non-singular matrix $A = \left[ a _ { i j } \right]$ with $a _ { 1 1 } = 0$ can never be expressed in the form $A = L U$ , where $L = [ l _ { i j } ]$ is lower-triangular and $U = [ u _ { i j } ]$ is upper-triangular. 

The above observation can be shown by contradiction by assuming that $A = L U$ is possible. Since $A = L U$ , it can be shown that $a _ { 1 1 } = l _ { 1 1 } u _ { 1 1 }$ . In order for $a _ { 1 1 }$ to be zero, either $l _ { 1 1 }$ or $u _ { 1 1 }$ must be 0. In other words, either the first row of $L$ is zero or the first column of U is zero. This means that either the first row or the first column of $A = L U$ is zero. In other words, A cannot be non-singular, which is a contradiction. 

Let us examine the effect of the first two steps (row addition and interchange steps) of the Gaussian elimination algorithm, which already creates a rectangular upper triangular matrix U. Note that the row addition operations are always lower triangular matrices, because lower rows are always subtracted from upper rows. Furthermore, the sequence of row interchange operations is a permutation of rows, and can therefore be expressed as the permutation matrix $P .$ Therefore, we can express the first two steps of the Gaussian elimination process in terms of a permutation matrix $P$ and the m row-addition operations defined by lower-triangular matrices $L _ { 1 } \ldots L _ { m }$ 

$$
P L _ {m} L _ {m - 1} \ldots L _ {1} A = U
$$

Multiplying both sides with $P ^ { T }$ and the inverses of the lower-triangular matrices $L _ { i }$ in the proper sequence, we obtain the following: 

$$
A = \underbrace {L _ {1} ^ {- 1} L _ {2} ^ {- 1} \ldots L _ {m} ^ {- 1}} _ {L} P ^ {T} U
$$

The inverses and products of lower-triangular matrices are lower triangular (cf. Chapter 1). Therefore, we can consolidate these matrices to obtain a single lower-triangular matrix L of size $n \times n$ . In other words, we have the following: 

$$
A = L P ^ {T} U
$$

This is, however, not the standard form of the LU decomposition. With some bookkeeping, it is possible to obtain a decomposition in which the permutation matrix $P ^ { T }$ occurs before the lower-triangular matrix L (although these matrices would be different when re-ordered): 

$$
A = P ^ {T} L U
$$

One can also write this decomposition as $P A = L U$ . This is the standard form of LU decomposition. 

## 2.5.2 Application: Finding a Basis Set

The Gaussian elimination method can be used to find a basis set of a bunch of (possibly linearly dependent) vectors. Let $\overline { { a } } _ { 1 } \ldots . \overline { { a } } _ { n }$ be a set of n row vectors, each of which have d dimensions. Then, we can create an $n \times d$ matrix A whose rows are $\overline { { a } } _ { 1 } \ldots . \overline { { a } } _ { n }$ . The process discussed in the previous section can be applied to create the row echelon form. The nonzero rows in the reduced matrix are always linearly independent because of the fact that their leading entries have a different column index. In cases where the original rows of A are linearly dependent, and the rank k of the corresponding vector space is strictly less than $n ,$ the final $( n - k )$ rows of the row echelon matrix will be zero vectors. The reduced row vectors (which are non-zero) correspond to the linearly independent basis set. 

## 2.5.3 Application: Matrix Inversion

In order to invert a non-singular matrix A, we first perform row operations to convert it to the upper-triangular $d \times d$ matrix $U = [ u _ { i j } ]$ in row echelon form. For invertible/nonsingular matrices like U, it is possible to further convert the matrix U to an identity matrix with the use of only row operations. First, the non-diagonal entries on the $( d - 1 ) \mathrm { t h }$ row are converted to 0 by subtracting an appropriate multiple [which is $u _ { d - 1 , d } ]$ of the dth row from it. Then, the non-diagonal entries of the $( d - 2 ) \mathfrak { t }$ th row are converted to 0 by subtracting appropriate multiples [which are $u _ { d - 2 , d - 1 }$ and $u _ { d - 2 , d } ]$ of the $( d - 1 ) \mathrm { t h }$ and dth rows from it. In other words, the rows are processed in order of reducing row index, and at most $d ( d - 1 ) / 2$ row operations will be required. This approach works only when the matrix is nonsingular, or else some of the diagonal entries will be 0s. One can obtain the inverse of A by performing the same row operations starting with the identity matrix, as one performs these row operations on A to reach the identity matrix. A sequence of row operations that transforms A to the identity matrix will transform the identity matrix to $B = \bar { A } ^ { - 1 }$ . The idea is that we perform the same row operations on both sides of the equation $A A ^ { - 1 } = I$ . The row operations on the left-hand side $A A ^ { - 1 }$ can be performed on A until it is transformed to the identity matrix. 

## 2.5.4 Application: Solving a System of Linear Equations

Consider the problem where we want to find all solutions $\overline { { x } } = [ x _ { 1 } , x _ { 2 } , \ldots x _ { d } ] ^ { T }$ that satisfy $A { \overline { { x } } } = { \overline { { b } } } .$ , where A is an $n \times d$ matrix and b is an n-dimensional column vector. If the columns of the matrix A are $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d } , \overline { { b } }$ needs to be expressed as a linear combination of these columns. This is because the matrix condition ${ \bar { A } } { \overline { { x } } } = { \overline { { b } } }$ can be rewritten in terms of the columns of A as follows 

$$
\sum_ {i = 1} ^ {d} x _ {i} \overline {{a}} _ {i} = \overline {{b}}\tag{2.9}
$$

Depending on A and ${ \overline { { b } } } ,$ three cases arise: 

1. If the vector $\bar { b }$ does not occur in the column space of $A ,$ then no solution exists to this system of linear equations although best fits are possible. This case is studied in detail in Section 2.8. 

2. If the vector $\bar { b }$ occurs in the column space of A, and A has linearly independent columns (which implies that the columns form the basis of a d-dimensional subspace of $\mathcal { R } ^ { n } )$ , the solution is unique. This result is based on the uniqueness of coordinates (cf. Lemma 2.3.2). In the special case that A is square, the solution is simply ${ \overline { { x } } } = A ^ { - 1 } { \overline { { b } } }$ 

3. If the vector $\bar { b }$ occurs in the column space of A and the columns of A are linearly dependent, then an infinite number of solutions exists to $A { \overline { { x } } } = { \overline { { b } } } .$ . Note that if $\overline { { x } } _ { 1 }$ and $\overline { { x } } _ { 2 }$ are solutions, then $\lambda \overline { { x } } _ { 1 } + ( 1 - \lambda ) \overline { { x } } _ { 2 }$ is also a solution for any real $\lambda .$ 

The first situation arises very commonly in over-determined systems of linear equations where the number of rows of the matrix is much greater than the number of columns. It is possible for inconsistent systems of equations to occur even in matrices where the number of rows is less than the number of columns. In order to understand this point, consider the case where $\overline { { b } } = [ 1 , 1 ] ^ { T }$ , and a $2 \times 1 0 0$ matrix A contains two non-zero row vectors, so that the second row vector is twice the first. However, it is impossible to find any non-zero solution to the $A { \overline { { x } } } = { \overline { { b } } }$ unless the second component of $\bar { b }$ is twice the first. Similarly, the third case occurs more commonly in cases where the number of columns $d$ is greater than the number of rows $n ,$ but it is possible to find linearly dependent column vectors even when $d < n$ . We present some exercises in order to gain some intuition about these difficult cases: 

Problem 2.5.1 Suppose that no solution exists to the system of equations $A { \overline { { x } } } = { \overline { { b } } } _ { \mathrm { { i } } }$ , where $A$ is an $n \times d$ matrix and $\bar { b }$ is an n-dimensional column vector. Show that an n-dimensional column vector $\overline { z }$ must exist that satisfies $\overline { { z } } ^ { T } A = \overline { { 0 } }$ and $\overline { { z } } ^ { T } \bar { b } \neq \overline { { 0 } }$ 

The above practice exercise simply states that if a system of equations is inconsistent, then a weighted combination of the equations can always be found so that the left-hand side adds up to zero, whereas the right-hand side adds up to a non-zero quantity. As a hint to solve the exercise, note that $\bar { b }$ does not fully lie in the column space of $A .$ , but can be expressed as a sum of vectors from the column space and left null space of A. The vector $\overline { z }$ can be derived from this decomposition. 

Problem 2.5.2 Express the system of equations $\textstyle \sum _ { i = 1 } ^ { 5 } x _ { i } \ = \ 1 , \ \sum _ { i = 1 } ^ { 2 } x _ { i } \ = \ - 1$ , and $\textstyle \sum _ { i = 3 } ^ { 5 } x _ { i } \ = \ - 1$ as $A { \overline { { x } } } = { \overline { { b } } }$ for appropriately chosen $A$ and ${ \overline { { b } } } .$ Informally discuss by inspection why this system of equations is inconsistent. Now define a vector $\overline { z }$ satisfying the conditions of the previous exercise to show that the system is inconsistent. 

The process of row echelon conversion is useful to identify whether a system of equations is inconsistent, and also to characterize the set of solutions to a system of consistent equations. One can use a sequence of row operations to convert the linear system $A { \overline { { x } } } = { \overline { { b } } }$ to a new system $A ^ { \prime } \overline { { x } } = \overline { { b } } ^ { \prime }$ in which the matrix $A ^ { \prime }$ is in row echelon form. Whenever a row operation is performed on A, exactly the same operation is performed on ${ \overline { { b } } } .$ The resulting system $A ^ { \prime } \overline { { x } } = \overline { { b } } ^ { \prime }$ contains a wealth of information about the solutions to the original system. Inconsistent systems will contain zero rows at the bottom of $A ^ { \prime }$ after row echelon conversion, but a corresponding non-zero entry in the same row of $\overline { { b } } ^ { \prime }$ (try to explain this using Problem 2.5.1 while recognizing that $A ^ { \prime }$ contains linearly independent rows). Such a system can never have a solution because a zero value on the left is being equated with a non-zero value on the right. All zero rows in $A ^ { \prime }$ need to be matched with zero entries in $\overline { { b } } ^ { \prime }$ for the system to have a solution. 

Assuming that the system is not inconsistent, how does one detect systems with unique solutions? In such cases, each column will contain a leftmost non-zero entry of some row. It is possible for some of the rows to be zeros. We present two examples of matrices, the first of which satisfies the aforementioned property, and the second does not satisfy the property: 

$$
M ^ {\prime} = \left[ \begin{array}{l l l} 1 & 7 & 4 \\ 0 & 1 & 2 \\ 0 & 0 & 1 \\ 0 & 0 & 0 \end{array} \right] \quad N ^ {\prime} = \left[ \begin{array}{l l l l l} 1 & 7 & \mathbf {4} & 3 & 5 \\ 0 & 1 & \mathbf {9} & 7 & 6 \\ 0 & 0 & \mathbf {0} & 1 & 3 \\ 0 & 0 & \mathbf {0} & 0 & 1 \end{array} \right]
$$

Note that the matrix $N ^ { \prime }$ does not satisfy the uniqueness condition because the third column (whose entries are in bold) does not contain the leftmost non-zero entry of any row. Such a column is referred to as a free column because one can view the variable corresponding to it as a free parameter. If there is no free column, one will obtain a square, triangular, invertible matrix on dropping the zero rows of $A ^ { \prime }$ and corresponding zero entries of $\check { b ^ { \prime } }$ . For example, one obtains a square, triangular, and invertible matrix on dropping the zero rows of $M ^ { \prime }$ . This matrix will be an upper-triangular matrix, which has values of 1 along the diagonal. It is easy to find a unique solution by using backsubstitution. One can first set the last component of $\textstyle { \overline { { x } } }$ to the last component of $\overline { { b } } ^ { \prime }$ , and substitute it into the system of equations to obtain a smaller upper-triangular system. This process is applied iteratively to find all components of x. 

The final case is one in which some free columns exist, which are not the leading non zero entries of some row. The variables corresponding to the free columns can be set to any value, and a unique solution for the other variables can always be found. In this case, the solution space contains infinitely many solutions. Consider the following system in row echelon form: 

$$
\underbrace {\left[ \begin{array}{l l l l} 1 & 2 & 1 & - 3 \\ 0 & 0 & 1 & 2 \\ 0 & 0 & 0 & 0 \end{array} \right]} _ {A ^ {\prime}} \left[ \begin{array}{l} x _ {1} \\ x _ {2} \\ x _ {3} \\ x _ {4} \end{array} \right] = \left[ \begin{array}{l} 3 \\ 2 \\ 0 \end{array} \right]
$$

In this system of equations, the second and fourth columns do not contain any entry that are the leading non-zero entries of any row. Therefore, we can set $x _ { 2 }$ and $x _ { 4 }$ to arbitrary numerical values (say, α and $\beta )$ and also drop all the zero rows. Furthermore, setting $x _ { 2 }$ and $x _ { 4 }$ to numerical values will result in a system of equations with only two variables $x _ { 1 }$ and $x _ { 3 }$ (because $\alpha$ and $\beta$ are now constants rather than variables). The vector $\overline { { b } } ^ { \prime }$ on the right-hand size is adjusted to reflect the effect of these numerical constants. After making these adjustments, the aforementioned system becomes the following: 

$$
{\left[ \begin{array}{l l} 1 & 1 \\ 0 & 1 \end{array} \right]} {\left[ \begin{array}{l} x _ {1} \\ x _ {3} \end{array} \right]} = {\left[ \begin{array}{c} 3 - 2 \alpha + 3 \beta \\ 2 - 2 \beta \end{array} \right]}
$$

This system is a square $2 \times 2$ system of equations with a unique solution in terms of α and $\beta .$ The value of $x _ { 3 }$ is set to $2 - 2 \beta$ , and then back-substitution is used to derive $x _ { 1 } = 1 - 2 \alpha { + } 5 \beta$ Therefore, the set of solutions $[ x _ { 1 } , x _ { 2 } , x _ { 3 } , x _ { 4 } ]$ is defined as follows: 

$$
[ x _ {1}, x _ {2}, x _ {3}, x _ {4} ] = [ 1 - 2 \alpha + 5 \beta , \alpha , 2 - 2 \beta , \beta ]
$$

Here, $\alpha$ and $\beta$ can be set to arbitrary numerical values; therefore, the system has infinitely many solutions. 

Problem 2.5.3 (Coordinate Transformations with Row Echelon) Consider the vector space $\nu \subset \mathcal { R } ^ { n }$ with basis ${ \cal B } = \{ \overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d } \}$ , so that $d < n$ . Show how to use the row echelon method to find the d coordinates of $\overline { { v } } \in \mathcal { V }$ in the basis $B .$ 

## 2.6 The Notion of Matrix Rank

Any matrix can be reduced to a (rectangular) diagonal matrix with only row and column operations. The reason for this is that we can first use row operations to convert a matrix to row echelon form. This matrix is a (rectangular) upper-triangular matrix. Subsequently, we can reduce it to a diagonal matrix using column operations. First, column operations are used to move all free columns to the rightmost end of the matrix. The non-free columns are reduced to a diagonal matrix. This is done in order of increasing column index $j$ by subtracting appropriate multiples of all non-free columns up to index $( j - 1 )$ from that column. Then, all free columns are reduced to zero columns by subtracting appropriate multiples of the non-free columns (each of which has only one non-zero entry). This will result in a rectangular diagonal matrix in which all free columns are converted to zero columns. In other words, any $n \times d$ matrix A can be expressed in the following form: 

$$
R A C = \Delta
$$

Here, R is an $n \times n$ matrix that is the product of the elementary row operator matrices, $C$ is a $d \times d$ matrix that is the product of the elementary column operator matrices, and $\Delta$ is an $n \times d$ rectangular diagonal matrix. 

This result has the remarkable implication that the ranks of the row space and the column space of a matrix are the same. 

Lemma 2.6.1 The rank of the row space of a matrix is the same as that of its column space. 

Proof Sketch: The condition $R A = \Delta C ^ { - 1 }$ implies that the row rank of A is the same as the number of non-zero diagonal entries in $\Delta$ (since row operations do not change rank of $A$ according to Lemma 2.5.1, and $\Delta C ^ { - 1 }$ contains as many non-zero, linearly independent rows as the number of non-zero diagonal entries in $\Delta )$ . Similarly, the condition $A C = R ^ { - 1 } \Delta$ implies that the column rank of A is the same as the number of non-zero diagonal entries in $\Delta$ . Therefore, the row rank of A is the same as its column rank. 

The common value of the rank of the row space and the column space is referred to as the rank of a matrix. 

Definition 2.6.1 (Matrix Rank) The rank of a matrix is equal to the rank of its row space, which is the same as the rank of its column space. 

Two natural corollaries of the above result are the following: 

Corollary 2.6.1 The rank of an $n \times d$ matrix is at most min $\{ n , d \}$ 

The matrix A contains d columns and therefore the rank of the column space is at most d. Similarly, the rank of the row space is at most n. Since both ranks are the same, it follows that this value must be at most min $\{ n , d \}$ 

Corollary 2.6.2 Consider an $n \times d$ matrix A with rank $k \leq m i n \{ n , d \}$ . Then the rank of the null space of A is $d - k$ and the rank of the left null space of A is $n - k$ 

This follows from the fact that rows of A are d-dimensional vectors, and the null space of A is the orthogonal complement of the vector space defined by the (transposed) rows of A. Therefore, the rank of the null space of A must be $d - k$ . A similar argument can be made for the left null space of A. 

## 2.6.1 Effect of Matrix Operations on Rank

It is common to use matrix addition and multiplication operations in machine learning. In such cases, it is helpful to understand the effect of matrix addition and multiplication on the rank. In this context, we establish lower and upper bounds on the results obtained using matrix operations. 

Lemma 2.6.2 (Matrix Addition Upper Bound) Let A and B be two matrices with ranks a and $b ,$ respectively. Then, the rank of $A + B$ is at most $a + b$ 

Proof: Each row of $A + B$ can be expressed as a linear combination of the rows of A and the rows of $B .$ . Therefore, the rank of the row space of $( A + B )$ is at most $a + b$ One can show a similar result for the lower bound on matrix addition: 

Lemma 2.6.3 (Matrix Addition Lower Bound) Let A and B be two matrices with ranks a and $b ,$ respectively. Then, the rank of $A + B$ is at least $| a - b |$ 

Proof: The result follows directly from Lemma 2.6.2, because one can express the relationship $A + B = C$ as $A + \left( - C \right) = \left( - B \right)$ or as $B + ( - C ) = ( - A )$ . Therefore, if A and B have ranks $a$ and $b ,$ then the rank of C must be at least $| a - b |$ from the previous lemma. One can also derive upper and lower bounds for multiplication operations. 

Lemma 2.6.4 (Matrix Multiplication Upper Bound) Let A and B be two matrices with ranks a and b, respectively. Then, the rank of AB is at most min a, b . 

Proof: Each column of AB is a linear combination of the columns of A, where the linear combination coefficients defining the ith column of AB are provided in the ith column of B. Therefore, the rank of the column space of AB is no greater than that of the column space of A. However, the column space of a matrix is the same as its rank. Therefore, the matrix rank of AB is no greater than the matrix rank of A. 

Similarly, each row of AB is a linear combination of the rows of B, where the linear combination coefficients defining the ith row of AB are included in the ith row of A. Therefore, the rank of the row space of AB is no greater than that of the row space of B. However, the row space of a matrix is the same as its rank. Therefore, the matrix rank of AB is no greater than the matrix rank of B. Combining the above two results, we obtain the fact that rank of AB is no greater than min $\{ a , b \}$ 

Establishing a lower bound on the rank of the product of two matrices is much harder than establishing an upper bound; a useful bound exists only in some special cases. 

Lemma 2.6.5 (Matrix Multiplication Lower Bound) Let A and B be $n \times d$ and $d \times k$ matrices of ranks a and b, respectively. Then, the rank of AB is at least $a + b - d$ 

We omit a formal proof of this result, which is also referred to as Sylvester’s inequality. It is noteworthy that d is the shared dimension of the two matrices (thereby allowing multiplication), and the result is not particularly useful when $a + b \leq d .$ . In such a case, the lower bound on the rank becomes negative, which is trivially satisfied by every matrix and therefore not informative. A useful lower bound can be established when the two matrices have rank close to the shared dimension d (i.e., the maximum possible value). What about the case when one or both matrices are square and are exactly of full rank? Some natural corollaries of the above result are the following: 

Corollary 2.6.3 Multiplying a matrix A with a square matrix B of full rank does not change the rank of matrix A. 

Corollary 2.6.4 Let A and B be two square matrices. Then AB is non-singular if and only if A and B are both non-singular. 

In other words, the product is of full rank if and only if both matrices are of full rank. This result is important from the perspective of the invertibility of the Gram matrix $A ^ { T } A$ of the column space of A. Note that the Gram matrix often needs to be inverted in machine learning applications like linear regression. In such cases, the inversion of the Gram matrix is part of the closed-form solution (see, for example, Equation 1.29 of Chapter 1). It is helpful to know that the invertibility of the Gram matrix is determined by the linear independence of the columns of the underlying data matrix of feature variables: 

Lemma 2.6.6 (Linear Independence and Gram Matrix) The matrix $A ^ { T } A$ is said to be the Gram matrix of the column space of an $n \times d$ matrix A. The columns of the matrix A are linearly independent if and only if $A ^ { T } A$ is invertible. 

Proof: Consider the case where $A ^ { T } A$ is invertible. This means that the rank of $A ^ { T } A$ is $d ,$ and therefore the rank of each of the factors of $A ^ { T }$ A must also be at least d. This means that $A$ must have rank at least $d ,$ which is possible only when the d columns of A are linearly independent. 

Now suppose that A has linearly independent columns. Then, for any non-zero vector ${ \overline { { x } } } ,$ we have $\overline { { x } } ^ { T } A ^ { T } A \overline { { x } } = \| A \overline { { x } } \| ^ { 2 } \geq 0$ . This value can be zero only when $A { \overline { { x } } } = { \overline { { 0 } } }$ . However, we know that $A { \overline { { x } } } \neq { \overline { { 0 } } }$ for a non-zero vector ${ \overline { { x } } } .$ , because of the linear independence of the columns of A. In other words, ${ \overline { { x } } } ^ { T } A ^ { T }$ Ax is strictly positive, which is possible only when $A ^ { T } A { \overline { { x } } }$ is a non-zero vector. In other words, for any non-zero vector $\textstyle { \overline { { x } } }$ we have $A ^ { T } A { \overline { { x } } } \neq \overline { { 0 } }$ , which implies that the square matrix $A ^ { T } A$ has linearly independent columns. This is possible only when $A ^ { T } A$ is invertible (cf. Lemma 2.3.1). 

One can use a very similar approach to show the stronger result that the ranks of the matrices $A , A ^ { T } A$ , and $A A ^ { T }$ are the same (see Exercise 2). The matrix $A A ^ { T }$ is the Gram matrix of the row space of A, and is also referred to as the left Gram matrix. 

## 2.7 Generating Orthogonal Basis Sets

Orthogonal basis sets have many useful properties like ease of coordinate transformations, projections, and distance computation. In this section, we will discuss how to convert a non-orthogonal basis set to an orthogonal basis set with the use of Gram-Schmidt orthogonalization. We also provide an example of a useful orthogonal basis of $\mathcal { R } ^ { n }$ , which is obtained with the use of the discrete cosine transform. 

## 2.7.1 Gram-Schmidt Orthogonalization and QR Decomposition

It is desired to find an orthonormal basis set of the span of the non-orthogonal vectors $\mathcal { A } = \{ \overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d } \}$ . We first discuss the simpler case in which the vectors of $\mathcal { A }$ are linearly independent and the basis vectors are unnormalized. We assume that each $\overline { { a } } _ { i }$ is drawn from $\mathcal { R } ^ { n }$ and $n \geq d$ (to ensure linear independence of $\{ \overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d } \} )$ . Therefore, one is looking for an orthogonal basis of a subspace of $\mathcal { R } ^ { n }$ 

An orthogonal basis $\{ \overline { { q } } _ { 1 } \ldots \overline { { q } } _ { d } \}$ can be found with the use of Gram-Schmidt orthogo nalization. The basic idea of Gram-Schmidt orthogonalization is to successively remove the projections of previously generated vectors from a vector belonging to $\mathcal { A }$ to iteratively create orthogonal vectors. We start by setting the first basis vector $\overline { { q } } _ { 1 }$ to $\overline { { a } } _ { 1 }$ , and then adjust $\overline { { a } } _ { 2 }$ by removing its projection on $\overline { { q } } _ { 1 }$ from it in order to create $\overline { { q } } _ { 2 }$ , which is orthogonal to $\overline { { q } } _ { 1 }$ . Subsequently, the projections of $\overline { { a } } _ { 3 }$ on both $\overline { { q } } _ { 1 }$ and $\overline { { q } } _ { 2 }$ are removed from $\overline { { a } } _ { 3 }$ to create the next basis vector $\overline { { q } } _ { 3 }$ . This process is iteratively continued till all $d$ basis vectors are generated. If the set is a linearly independent set of basis vectors, the generated basis set $\{ \overline { { q } } _ { 1 } \ldots \overline { { q } } _ { d } \}$ will only contain non-zero vectors (or else we will obtain a linear dependence relation between $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { j }$ when $\overline { { q } } _ { j }$ evaluates to 0). These vectors can also be normalized by dividing each with its norm. Gram-Schmidt orthogonalization produces a basis set that depends on the order in which the vectors of $\mathcal { A }$ are processed. 

Next, we describe the process formally. In the initial step, $\overline { { q } } _ { 1 }$ is generated as follows: 

$$
\overline {{q}} _ {1} = \overline {{a}} _ {1}\tag{2.10}
$$

Subsequently, an iterative process is used for generating $\overline { { q } } _ { i }$ after $\overline { { q } } _ { 1 } \ldots \overline { { q } } _ { i - 1 }$ have been generated. The vector $\overline { { q } } _ { i }$ is generated by subtracting the projection of $\overline { { a } } _ { i }$ on the subspace defined by the already generated vectors $\overline { { q } } _ { 1 } \ldots \overline { { q } } _ { i - 1 }$ . Note that the projection of $\overline { { a } } _ { i }$ onto a previously generated $\overline { { q } } _ { r } \left( r < i \right)$ is simply $\frac { \overline { { a } } _ { i } { \cdot } \overline { { q } } _ { r } } { | | \overline { { q } } _ { r } | | }$ . Therefore, the process of generating $\overline { { q } } _ { i }$ is as follows: 

1. Compute $\begin{array} { r } { \overline { { q } } _ { i } = \overline { { a } } _ { i } - \sum _ { r = 1 } ^ { i - 1 } \frac { \left( \overline { { a } } _ { i } \cdot \overline { { q } } _ { r } \right) } { \| \overline { { q } } _ { r } \| } \frac { \overline { { q } } _ { r } } { \| \overline { { q } } _ { r } \| } = \overline { { a } } _ { i } - \sum _ { r = 1 } ^ { i - 1 } \frac { \left( \overline { { a } } _ { i } \cdot \overline { { q } } _ { r } \right) } { \overline { { q } } _ { r } \cdot \overline { { q } } _ { r } } \overline { { q } } _ { r } . } \end{array}$ 

2. Increment i by 1. 

This process is repeated for each $i = 2 \dots d .$ . This algorithm is referred to as the unnormalized Gram-Schmidt method. In practice, the vectors are scaled to unit norm after the process. 

We can show that the resulting vectors are mutually orthogonal by induction. For example, consider the case when we make the inductive assumption that $\overline { { q } } _ { 1 } \ldots \overline { { q } } _ { i - 1 }$ are orthogonal. Then, we can show that $\overline { { q } } _ { i }$ is also orthogonal to each $\overline { { q } } _ { j }$ for $j \in \{ 1 \ldots i - 1 \}$ 

$$
\overline {{q}} _ {j} \cdot \overline {{q}} _ {i} = \underbrace {\overline {{q}} _ {j} \cdot \left[ \overline {{a}} _ {i} - \sum_ {r = 1} ^ {i - 1} \frac {(\overline {{a}} _ {i} \cdot \overline {{q}} _ {r})}{\| \overline {{q}} _ {r} \|} \frac {\overline {{q}} _ {r}}{\| \overline {{q}} _ {r} \|} \right]} _ {[ \text {Drop terms using induction} ]} = \overline {{q}} _ {j} \cdot \overline {{a}} _ {i} - \frac {(\overline {{q}} _ {j} \cdot \overline {{q}} _ {j})}{\| \overline {{q}} _ {j} \| ^ {2}} (\overline {{q}} _ {j} \cdot \overline {{a}} _ {i}) = 0
$$

Therefore, the inductive assumption of mutual orthogonality can also be extended to $\overline { { q } } _ { i }$ from $\overline { { q } } _ { 1 } \ldots \overline { { q } } _ { i - 1 }$ 

Aside from the orthogonality of the generated basis, we need to show that the span of $\overline { { q } } _ { 1 } \ldots \overline { { q } } _ { i }$ remains the same as that of $\overline { { a } } _ { 1 } \ldots . \overline { { a } } _ { i }$ for all $i \ \leq \ d .$ . This result can be shown by induction. The result is trivially true at $i = 1$ . Now, make the inductive assumption that the span of $\overline { { q } } _ { 1 } \ldots \overline { { q } } _ { i - 1 }$ is the same as that of $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { i - 1 }$ . In each iterative step, adding $\overline { { q } } _ { i }$ to the current basis has the same effect as adding $\overline { { a } } _ { i }$ to the current basis, because $\overline { { q } } _ { i }$ is adjusted from $\overline { { a } } _ { i }$ additively using a linear combination of vectors $\left\{ \overline { { q } } _ { 1 } \ldots \overline { { q } } _ { i - 1 } \right\}$ already in the basis. Therefore, the span of $\overline { { q } } _ { 1 } \ldots \overline { { q } } _ { i }$ is the same as that of $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { i }$ 

What happens when the vectors in $\mathcal { A }$ are not linearly independent? In such cases, some of the generated vectors $\overline { { q } } _ { i }$ turn out to be zero vectors, and they are discarded as soon as they are computed. In such a case, the Gram-Schmidt method returns fewer than d basis vectors. As a specific example, in the case when $\overline { { a } } _ { 2 } = 3 \overline { { a } } _ { 1 }$ , it is easy to show that $\overline { { q } } _ { 2 } = \overline { { a } } _ { 2 } - 3 \overline { { q } } _ { 1 } = \overline { { a } } _ { 2 } - 3 \overline { { a } } _ { 1 }$ will be the zero vector. In general, when $\overline { { a } } _ { i }$ is linearly dependent on $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { i - 1 }$ , the projection of the vector $\overline { { a } } _ { i }$ on the subspace defined by $\overline { { q } } _ { 1 } \ldots \overline { { q } } _ { i - 1 }$ is itself; therefore, subtracting this projection of $\overline { { a } } _ { i }$ from $\overline { { a } } _ { i }$ will result in the zero vector. 

Problem 2.7.1 (A-Orthogonality) Two n-dimensional vectors $\textstyle { \overline { { x } } }$ and $\overline { y }$ are said to be A-orthogonal, if we have ${ \overline { { x } } } ^ { T } A { \overline { { y } } } = 0$ for an $n \times n$ invertible matrix A. Given a set of $d \leq n$ linearly independent vectors from $\mathcal { R } ^ { n }$ , show how to generate an A-orthogonal basis for them. 

Problem 2.7.2 (Randomized A-Orthogonality) Propose a method to find a randomized orthogonal basis of $\mathcal { R } ^ { n }$ using the Gram-Schmidt method. Now generalize the method to find a randomized A-orthogonal basis of $\mathcal { R } ^ { n }$ 

## 2.7.2 QR Decomposition

We first discuss the QR decomposition of an $n \times d$ matrix with linearly independent columns. Since the columns are linearly independent, we must have $n \geq d .$ . Gram-Schmidt orthogonalization can be used to decompose an $n \times d$ matrix $A$ with the linearly independent columns into the product of an $n \times d$ matrix $Q$ with orthonormal columns and an upper-triangular $d \times d$ matrix $R .$ . In other words, we want to compute the following $Q R$ decomposition: 

$$
A = Q R\tag{2.11}
$$

Consider an $n \times d$ matrix A with linearly independent columns $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d }$ . Then, we perform the Gram-Schmidt orthogonalization as discussed above (with the normalization step included), and construct the matrix $Q$ with orthonormal columns $\overline { { q } } _ { 1 } \ldots \overline { { q } } _ { d } \in \mathcal { R } ^ { n }$ obtained from Gram-Schmidt orthogonalization. The columns appear in the same order as obtained by processing $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d }$ by the Gram-Schmidt algorithm. Since the vectors $\overline { { a } } _ { 1 } \ldots \overline { { a } } _ { d }$ are linearly independent, one would derive a full set of d orthonormal basis vectors. Note that the projection of $\textstyle { \overline { { a } } } _ { r }$ on each $\overline { { q } } _ { j }$ is $\overline { { q } } _ { j } \cdot \overline { { a } } _ { r } .$ , which provides its jth coordinate in the new orthonormal basis. Therefore, we define a $d \times d$ matrix $R ,$ in which the $( j , r )$ th entry is $\overline { { q } } _ { j } \cdot \overline { { a } } _ { r }$ . For $j > r , { \bar { q } } _ { j }$ is orthogonal to the space spanned by $\overline { { a } } _ { 1 } \ldots . \overline { { a } } _ { r }$ , and therefore the value of $\overline { { q } } _ { j } \cdot \overline { { a _ { r } } }$ is 0. Therefore, the matrix R is upper triangular. It is easy to see that the rth column of the product QR is the appropriate linear combination of the orthonormal basis defined by Gram-Schmidt orthogonalization (to yield $\overline { { a } } _ { r } )$ , and therefore $A = Q R$ 

What happens when the columns of the $n \times d$ matrix A are not linearly independent? In such a case, the Gram-Schmidt process will yield the vectors $\overline { { q } } _ { 1 } \ldots . \overline { { q } } _ { d } .$ , which are either unit-normalized vectors or zero vectors. Assume that k of the vectors $\overline { { q } } _ { 1 } \ldots \overline { { q } } _ { d }$ are nonzero. We can assume that the zero vectors also have zero coordinates in the Gram-Schmidt representation, since the coordinates of zero vectors are irrelevant from a representational point of view. As in the previous case, we create the decomposition QR (including the zero columns in $Q$ and matching zero rows in $R )$ , where $Q$ is a $n \times d$ matrix and R is a $d \times d$ upper-triangular (rectangular) matrix. Subsequently, we drop all the zero columns from $Q ,$ and also drop the zero rows with matching indices from R. As a result, the matrix $Q$ is now of size $n \times k$ and the matrix R is of size $k \times d .$ . This provides the most concise, generalized QR decomposition of the original $n \times d$ matrix A. 

Problem 2.7.3 (Solving Linear Equations) Show how you can use QR decomposition to solve the system of equations $A { \overline { { x } } } = { \overline { { b } } }$ with back-substitution. Assume that A is a d d matrix with linearly independent columns and b is a d-dimensional column vector. 

## Leveraging Givens Rotations and Householder Reflections

The following section provides a brief overview of advanced methods for QR decomposition, and the reader may omit this section without loss of continuity. It is possible to perform QR decomposition of any $n \times d$ matrix A by applying $O ( n d )$ Givens rotations (defined on page 47) to the columns of A. Pre-multiplying a square matrix A with the Givens rotation matrix can be used to change a single entry below the diagonal to zero (without disturbing the entries already zeroed out), provided that the angle of rotation is properly chosen and the entries are zeroed in the proper order. The basic geometric principle behind zeroing an entry is that it is always possible to rotate a 2-dimensional vector for an appropriate angle until one of its coordinates is zeroed out. Pre-multiplying A with an $n \times n$ Givens rotation matrix performs an operation on each column vector of A. Although the column vectors of A are not 2-dimensional, Givens rotations always perform rotations in 2-dimensiona projections without affecting other coordinates, and therefore such an angle always exists. 

Given an $n \times d$ matrix A, the approach successively pre-multiplies A with an $n \times n$ Givens rotation matrix, so as to turn one entry below the diagonal to zero (without disturbing the entries that have already been turned to zero). The running matrix after pre-multiplication with orthogonal matrices is denoted by variable R, and this matrix is upper-triangular at the end of the process. Let $Q _ { 1 } \ldots Q _ { s }$ be Givens matrices successively chosen in this way, so that we have the following repeated process: 

$$
A = \underbrace {Q _ {1} ^ {T} Q _ {1}} _ {I} A = Q _ {1} ^ {T} \underbrace {Q _ {2} ^ {T} Q _ {2}} _ {I} \underbrace {Q _ {1} A} _ {R} = \ldots = \underbrace {(Q _ {1} ^ {T} \ldots Q _ {s} ^ {T})} _ {\text { Orthogonal } Q} \underbrace {(Q _ {s} Q _ {s - 1} \ldots Q _ {1} A)} _ {\text { Triangular } R}
$$

Therefore, the approach requires at most $O ( n d )$ Givens rotations, although far fewer rotations will be required for sparse matrices. Entries (below the diagonal) with the smallest column index $j$ are zeroed first, and those with the same column index are selected in order of decreasing row index $i .$ Based on the notations on page 47, the Givens matrix used for pre-multiplication of the current transformation R of A is $G _ { c } ( i - 1 , i , \alpha )$ , where α is chosen to zero out the $( i , j )$ th entry of the current matrix corresponding to running variable R. Multiplication of $G _ { c } ( i - 1 , i , \alpha )$ with R affects only the (i 1)th and ith entries of each column of R. If the lower-triangular portions of columns before index $j$ have already been set to $0 ,$ then multiplication with the Givens matrix will not affect them (since a rotation of a zero vector is a zero vector). Therefore, work already done on setting earlier column entries to 0 will remain undisturbed. Consider the current column index $j$ , whose entries are being set to 0. If the current matrix R contains entries $r _ { i j }$ , then one can pull out the portion of the product of the Givens matrix $G _ { c } ( i - 1 , i , \alpha )$ with $R$ corresponding to the rotation of the 2-dimensional vector $[ r _ { i - 1 , j } , r _ { i j } ] ^ { T }$ 

$$
\left[ \begin{array}{c c} \cos (\alpha) & - \sin (\alpha) \\ \sin (\alpha) & \cos (\alpha) \end{array} \right] \left[ \begin{array}{c} r _ {i - 1, j} \\ r _ {i j} \end{array} \right] = \left[ \begin{array}{c} \sqrt {r _ {i - 1 , j} ^ {2} + r _ {i j} ^ {2}} \\ 0 \end{array} \right]
$$

One can verify that the solution to the above system yields the following value of α: 

$$
\sin (\alpha) = \frac {- r _ {i j}}{\sqrt {r _ {i j} ^ {2} + r _ {i - 1 , j} ^ {2}}}, \quad \cos (\alpha) = \frac {r _ {i - 1 , j}}{\sqrt {r _ {i j} ^ {2} + r _ {i - 1 , j} ^ {2}}}\tag{2.12}
$$

Note that α takes on (absolute) value of $9 0 °$ , when $r _ { i - 1 , j }$ is 0 but $r _ { i j }$ is not 0. Furthermore, α is 0 or 180 when $r _ { i j }$ is already zero, and no rotation needs to be done (since $\mathrm { ~ a ~ } 1 8 0 ^ { \circ }$ rotation only flips the sign of $r _ { i - 1 , j } )$ . The ordering of the processing of the $O ( n d )$ entries is necessary to ensure that already zeroed entries are not disturbed by further rotations. The pseudocode for the process is as follows: 

$Q \Leftarrow I; R \Leftarrow A;$ for $j = 1$ to $d - 1$ do for $i = n$ down to $(j + 1)$ do Choose $\alpha$ based on Equation 2.12; $Q \Leftarrow Q G_{c}(i,i - 1,\alpha)^{T}; R \Leftarrow G_{c}(i,i - 1,\alpha)R;$ endfor   
endfor   
return $Q, R;$ 

For $n \geq d$ and a matrix A with linearly independent columns, the above approach will create an $n \times n$ matrix Q and an $n \times d$ matrix R. These matrices are larger than the ones obtained with the Gram-Schmidt method. However, the bottom $( n - d )$ rows of R will be zeros, and therefore one can drop the last $( n - d )$ columns of Q and the bottom $( n - d )$ rows of R without affecting the result. This yields a smaller QR decomposition with $n \times d$ matrix $Q$ and $d \times d$ matrix R. 

It is also possible to use this approach of iteratively modifying Q and R with Householder reflection matrices instead of Givens rotation matrices. In this case, at most (d 1) reflections will be needed to triangulize the matrix, because each iteration is able to zero out all the entries below the diagonal for a particular column (and the final one can be ignored). The columns are processed in order of increasing column index. The basic geometric principle is that for any n-dimensional coordinate vector (first column of A), it is possible to orient a (n 1)-dimensional “mirror” passing through the origin, so that the image of the vector is mapped to a point in which only the first coordinate is non-zero. Such a transformation is defined by multiplication with a Householder reflection matrix. We encourage the reader to visualize a 1-dimensional reflection plane in 2-dimensional space, so that a specific point $[ x , y ] ^ { T }$ is mapped to $[ \sqrt { x ^ { 2 } + y ^ { 2 } } , 0 ] ^ { T }$ . This principle also applies more generally to vectors in n-dimensional space, such as the first column $\overline { { c } } _ { 1 }$ of $A .$ . One can choose $\overline { { v } } _ { 1 }$ (normal vector to the “mirror” hyperplane) in the first iteration to be the unit vector joining $\overline { { c } } _ { 1 }$ to a column vector $\| \overline { { c } } _ { 1 } \| [ 1 , \bar { 0 } , \ldots , \bar { 0 } ] ^ { T }$ of equal length in which only the first component is nonzero. Therefore, we have $\overline { { v } } _ { 1 } \stackrel { \cdot } { \propto } ( \overline { { c } } _ { 1 } - \| \overline { { c } } _ { 1 } \| [ 1 , 0 , \ldots , 0 ] ^ { T } )$ , and it is scaled to unit norm. One can then compute the Householder matrix $Q _ { 1 } = ( I - 2 \overline { { v } } _ { 1 } \overline { { v } } _ { 1 } ^ { T } )$ . Pre-multiplying A with $Q _ { 1 }$ will zero the bottom $( n - 1 )$ ) entries of the first column $\overline { { c } } _ { 1 }$ of A. In subsequent iterations, the entries of the first row of the resulting matrix $R = Q _ { 1 } A$ remain frozen to their current values, and all modifications are performed only on the bottom $( n - 1 )$ ) rows. Therefore, the $n \times n$ Householder reflection matrix $Q _ { 2 } = \stackrel { \cdot } { ( } I - 2 \overline { { v } } _ { 2 } \overline { { v } } _ { 2 } ^ { T } )$ will be chosen in the second iteration so that any changes occur only in the bottom $( n - 1 )$ dimensions. The second iteration zeros out the bottom $( n - 2 )$ entries of the second column $\overline { { c } } _ { 2 }$ of the running matrix R. This is achieved by first copying $\overline { { c } } _ { 2 }$ to $\bar { c } _ { 2 , n - 1 }$ , resetting the first entry of $\bar { c } _ { 2 , n - 1 }$ to zero, evaluating unit vector $\overline { { \upsilon } } _ { 2 } \propto \overline { { c } } _ { 2 , n - 1 } - \| \overline { { c } } _ { 2 , n - 1 } \| [ 0 , 1 , 0 , \ldots 0 ] ^ { T }$ , and then updating $R \Leftarrow R \left( I - 2 \overline { { v } } _ { 2 } \overline { { v } } _ { 2 } ^ { T } \right)$ . In the next iteration, the Householder matrix is computed by defining $\bar { c } _ { 3 , n - 2 }$ as a partial copy of the vector $\overline { { c } } _ { 3 }$ with the first two entries set to zero. One can set the unit vector $\overline { { v } } _ { 3 } \propto \overline { { c } } _ { 3 , n - 2 } - \| \overline { { c } } _ { 3 , n - 1 } \| [ 0 , 0 , 1 , 0 , \ldots 0 ] ^ { T }$ , and then update $R \Leftarrow R \left( I - 2 \overline { { v } } _ { 3 } \overline { { v } } _ { 3 } ^ { T } \right)$ ). This process is iteratively applied to zero the appropriate number of entries of each column of $R .$ The final orthogonal matrix of the QR decomposition is obtained as $Q _ { 1 } ^ { T } \dots Q _ { d - 1 } ^ { T }$ . Careful implementation choices are required to reduce numerical errors. For example, in the first iteration, one can reflect $\overline { { c } } _ { 1 }$ to either $\| \overline { { c } } _ { 1 } \| [ 1 , 0 , \ldots 0 ] ^ { T }$ or to $- \| \overline { { c } } _ { 1 } \| [ 1 , 0 , \ldots 0 ] ^ { \hat { T } }$ . Selecting the further of the two choices reduces numerical errors. 

## 2.7.3 The Discrete Cosine Transform

The Gram-Schmidt basis does not expose any specific properties of a vector with the help of its coordinates. On the other hand, the wavelet basis discussed in Section 2.3.4 is an orthogonal basis that exposes local variations in a time series. The discrete cosine transform uses a basis with trigonometric properties in order to expose periodicity in a time series. 

Consider a time-series drawn from $\mathcal { R } ^ { n }$ , which has n values $( \mathrm { e . g . }$ ., temperatures) drawn at n equally spaced clock ticks. Choosing a basis in which each basis vector contains equally spaced samples of a cosine time-series of a particular periodicity allows a transformation in which the coordinates of the basis vectors can be interpreted as the amplitudes of the different periodic components of the series. For example, a time-series of temperatures over 10 years will have day-night variations as well as summer-winter variations, which will be captured by the coordinates of different basis vectors (periodic components). These coordinates are helpful in many machine learning applications. 

Consider a high-dimensional time series of length n, which is represented as a column vector in $\mathcal { R } ^ { n }$ . The n-dimensional basis vector of this time series with the largest possible periodicity uses n equally spaced samples of the cosine function ranging between 0 and $\pi$ radians. The samples of the cosine function are spaced at a distance of $\pi / n$ radians from one another, and a natural question arises as to where one might select the first sample. Although different variations of the discrete cosine transform select the first sample at different points of the cosine function, the most common choice is to ensure that the samples are symmetric about $\pi / 2$ , and therefore the first sample is chosen at $\pi / 2 n$ . This yields the following basis vector b: 

$$
\overline {{b}} = [ \cos (\pi / 2 n), \cos (3 \pi / 2 n), \ldots , \cos ([ 2 n - 1 ] \pi / 2 n) ] ^ {T}
$$

For a time-series of length $n ,$ this is the largest possible level of periodicity, where the entire basis vector is an n-dimensional sample of only half a cosine wave (covering π radians). To address smaller periodicities in the data, we would need more basis vectors in which the n-dimensional sample is drawn from a larger number of cosine waves (i.e., a larger angle than π). In other words, the n samples of the cosine function are obtained by sampling the cosine function at n points between 0 and $( j - 1 ) \pi$ for each value of $j \in \{ 1 , \ldots , n \}$ 

$$
\bar {b} _ {j} = [ \cos ([ j - 1 ] \pi / 2 n), \cos (3 [ j - 1 ] \pi / 2 n), \dots , \cos ([ 2 n - 1 ] [ j - 1 ] \pi / 2 n) ] ^ {T}
$$

Setting $j = 1$ yields $\overline { { b } } _ { 1 }$ as a column vector of 1s, which is not periodic, but is a useful basis vector for capturing constant offsets. The case of $j = 2$ corresponds to half a cosine wave as discussed above. 

One can create an unnormalized basis matrix $B = [ \overline { { b } } _ { 1 } \ldots \overline { { b } } _ { n } ]$ whose columns contain the basis vectors discussed above. Let us assume that the ith component of the jth basis vector $\overline { { b } } _ { j }$ is denoted by $b _ { i j }$ . In other words, the $( i , j )$ th entry of B is $b _ { i j }$ , where $b _ { i j }$ is defined as follows: 

$$
b _ {i j} = \cos \left(\frac {\pi (2 i - 1) (j - 1)}{2 n}\right), \quad \forall i, j \in \{1 \dots n \}
$$

The above basis matrix includes the non-periodic (special) basis vector, and it is unnormalized because the norm of each column is not 1. A key point is the columns of the basis matrix B are orthogonal: 

Lemma 2.7.1 (Orthogonality of Basis Vectors) The dot product of any pair of basis vectors $\bar { b } _ { p }$ and $\overline { { b } } _ { q }$ of the discrete cosine transform for $p \neq q$ is 0. 

Proof Sketch: We use the identity that $\cos ( x ) \mathrm { c o s } ( y ) = [ \cos ( x + y ) + \cos ( x - y ) ] / 2$ . Using this identity, it can be shown that the dot product between $\overline { { b } } _ { p }$ and $\overline { { b } } _ { q }$ is as follows: 

$$
\overline {{b}} _ {p} \cdot \overline {{b}} _ {q} = \frac {1}{2} \sum_ {i = 1} ^ {n} \cos \left(\frac {[ p + q ] [ 2 i - 1 ] \pi}{2 n}\right) + \frac {1}{2} \sum_ {i = 1} ^ {n} \cos \left(\frac {[ p - q ] [ 2 i - 1 ] \pi}{2 n}\right)
$$

The right-hand side can be broken up into the sum of two cosine series with their argumentsin arithmetic progression. This is a standard trigonometric identity [73]. Using the formulafor the sum of cosine series with arguments in arithmetic progression, these sums can beshown to be proportional to sin $( n \delta / 2 ) \mathrm { c o s } ( n \delta / 2 ) / \mathrm { s i n } ( \delta / 2 )$ sin $( n \delta ) / \mathrm { s i n } ( \delta / 2 )$ , where $\delta =$ $( p + q ) \pi / n$ in the first cosine series, and $\delta = ( p - q ) \pi / n$ in the second cosine series. Thevalue of sin(nδ) is 0 for both values of $\delta ,$ and therefore both series sum to 0. 厂

Lemma 2.7.2 (Norms of Basis Vectors) The norm of the special basis vector $\overline { { b } } _ { 1 }$ of the discrete cosine transform is $\sqrt { n }$ , whereas the norm of each $\overline { { b } } _ { p }$ for $p \in \{ 2 , \ldots , n \}$ is $\sqrt { n / 2 }$ 

Proof Sketch: The proof for $\overline { { b } } _ { 1 }$ is trivial. For $p > 1$ the squared norms of $\overline { { b } } _ { p }$ are the sums of squares of cosines with arguments in arithmetic progression. Here, we can use the trigonometric identity $\cos ^ { 2 } ( x ) = ( 1 + \cos ( 2 x ) ) / 2$ . Therefore, we obtain the following: 

$$
\| \bar {b} _ {p} \| ^ {2} = \frac {n}{2} + \frac {1}{2} \underbrace {\sum_ {i = 1} ^ {n} \cos \left(\frac {p [ 2 i - 1 ] \pi}{n}\right)}
$$

As in the proof of the previous lemma, the cosine series with angles in arithmetic progression sums to 0. The result follows. 

The basis matrix B is orthogonal after matrix normalization. One can normalize the matrix B by dividing all matrix entries with ${ \sqrt { n } } ,$ and then multiplying columns 2 through n with $\sqrt { 2 }$ . For example, an $8 \times 8$ normalized basis matrix for the cosine transform is as follows: 

$$
B = \frac {1}{2} \left[ \begin{array}{l l l l l l l l} \frac {1}{\sqrt {2}} & \cos (\frac {\pi}{1 6}) & \cos (\frac {2 \pi}{1 6}) & \cos (\frac {3 \pi}{1 6}) & \cos (\frac {4 \pi}{1 6}) & \cos (\frac {5 \pi}{1 6}) & \cos (\frac {6 \pi}{1 6}) & \cos (\frac {7 \pi}{1 6}) \\ \frac {1}{\sqrt {2}} & \cos (\frac {3 \pi}{1 6}) & \cos (\frac {6 \pi}{1 6}) & \cos (\frac {9 \pi}{1 6}) & \cos (\frac {1 2 \pi}{1 6}) & \cos (\frac {1 5 \pi}{1 6}) & \cos (\frac {1 8 \pi}{1 6}) & \cos (\frac {2 1 \pi}{1 6}) \\ \frac {1}{\sqrt {2}} & \cos (\frac {5 \pi}{1 6}) & \cos (\frac {1 0 \pi}{1 6}) & \cos (\frac {1 5 \pi}{1 6}) & \cos (\frac {2 0 \pi}{1 6}) & \cos (\frac {2 5 \pi}{1 6}) & \cos (\frac {3 0 \pi}{1 6}) & \cos (\frac {3 5 \pi}{1 6}) \\ \frac {1}{\sqrt {2}} & \cos (\frac {7 \pi}{1 6}) & \cos (\frac {1 4 \pi}{1 6}) & \cos (\frac {2 1 \pi}{1 6}) & \cos (\frac {2 8 \pi}{1 6}) & \cos (\frac {3 5 \pi}{1 6}) & \cos (\frac {4 2 \pi}{1 6}) & \cos (\frac {4 9 \pi}{1 6}) \\ \frac {1}{\sqrt {2}} & \cos (\frac {9 \pi}{1 6}) & \cos (\frac {1 8 \pi}{1 6}) & \cos (\frac {2 7 \pi}{1 6}) & \cos (\frac {3 6 \pi}{1 6}) & \cos (\frac {4 5 \pi}{1 6}) & \cos (\frac {5 4 \pi}{1 6}) & \cos (\frac {6 3 \pi}{1 6}) \\ \frac {1}{\sqrt {2}} & \cos (\frac {1 1 \pi}{1 6}) & \cos (\frac {2 2 \pi}{1 6}) & \cos (\frac {3 3 \pi}{1 6}) & \cos (\frac {4 4 \pi}{1 6}) & \cos (\frac {5 5 \pi}{1 6}) & \cos (\frac {6 6 \pi}{1 6}) & \cos (\frac {7 7 \pi}{1 6}) \\ \frac {1}{\sqrt {2}} & \cos (\frac {1 3 \pi}{1 6}) & \cos (\frac {2 6 \pi}{1 6}) & \cos (\frac {3 9 \pi}{1 6}) & \cos (\frac {5 2 \pi}{1 6}) & \cos (\frac {6 5 \pi}{1 6}) & \cos (\frac {7 8 \pi}{1 6}) & \cos (\frac {9 1 \pi}{1 6}) \\ \frac {1}{\sqrt {2}} & \cos (\frac {1 5 \pi}{1 6}) & \cos (\frac {3 0 \pi}{1 6}) & \cos (\frac {4 5 \pi}{1 6}) & \cos (\frac {6 0 \pi}{1 6}) & \cos (\frac {7 5 \pi}{1 6}) & \cos (\frac {9 0 \pi}{1 6}) & \cos (\frac {1 0 5 \pi}{1 6}) \end{array} \right]
$$

Consider the time-series $\overline { { s } } = [ 8 , 6 , 2 , 3 , 4 , 6 , 6 , 5 ] ^ { T }$ , which is the same example used in Section 2.3.4 on wavelet transformations. This time-series can be transformed to the basis of the discrete cosine transform by solving the system of equations $B { \overline { { x } } } = { \overline { { s } } }$ in order to compute the coordinates x. Since B is an orthogonal matrix, the solution x is given by $\overline { { x } } = B ^ { T } \overline { { s } }$ . The smaller coefficients can be set to 0 in order to enable space-efficient sparse representations. 

The focus on capturing periodicity makes the discrete cosine transform quite different from the wavelet transform. It is closely related to the discrete Fourier transform (cf. Sec tion 2.11.1), and the former is the preferred choice in some applications like jpeg compression. The discrete cosine transform has many variants depending on how one samples the cosine function to generate the basis vectors. The version presented in this section is referred to as DCT-II, and it is the most popular version of the transform [121]. 

## 2.8 An Optimization-Centric View of Linear Systems

Linear algebra is closely related to many problems in linear optimization, which recur frequently in machine learning. Indeed, solving a system of linear equations is a special case of one of the most fundamental problems in machine learning, which is referred to as linear regression. One way of solving the system of equations $A { \overline { { x } } } = { \overline { { b } } }$ is to view it as an optimization problem in which we want to minimize the objective function $\| A { \overline { { x } } } - { \overline { { b } } } \| ^ { 2 }$ . This is classical least-squares regression, which is the genesis of a vast array of models in machine learning. Least-squares regression tries to find the best possible fit to a system of equations (rather than an exact one). The minimum possible value of the objective function is 0, which occurs when a feasible solution exists for $A { \overline { { x } } } = { \overline { { b } } }$ . However, if the system of equations is inconsistent, the optimization problem will return the best possible fit with a non-zero (positive) optimal value. Therefore, the goal is to minimize the following objective function: 

$$
J = \underbrace {\| A \overline {{x}} - \overline {{b}} \| ^ {2}} _ {\mathrm{BestFit}}
$$

Although one can use calculus to solve this problem (see Section 4.7 of Chapter 4), we use a geometric argument. The closest approach from a point to a hyperplane is always orthogona to the hyperplane. The vector $( \overline { { b } } - A \overline { { x } } ) \in \mathcal { R } ^ { n }$ , which joins b to its closest approximation ${ \bar { b } } ^ { \prime } = A { \overline { { x } } }$ on the hyperplane defined by the column space of A, must be orthogonal to the hyperplane and therefore to every column of A (see Figure 2.9). Hence, we obtain the normal equation $A ^ { T } ( { \overline { { b } } } - A { \overline { { x } } } ) = { \overline { { 0 } } }$ , which yields the following: 

$$
\overline {{x}} = (A ^ {T} A) ^ {- 1} A ^ {T} \overline {{b}}\tag{2.13}
$$

The assumption here is that $A ^ { T } A$ is invertible, which can occur only when the columns of A are linearly independent (according to Lemma $2 . 6 . 6 )$ . This can happen only when A is $\mathrm { ~ a ~ } ^ { 6 6 } \mathrm { t a l l } ^ { 5 }$ matrix $( \mathrm { i . e . , } n \geq d )$ . The matrix $L = ( A ^ { T } A ) ^ { - 1 } A ^ { T }$ is referred to as the $l e f t -$ inverse of the matrix A, which is a generalization of the concept of a conventional inverse to rectangular matrices. In such a case, it is evident that we have $L A = ( A ^ { T } A ) ^ { - 1 } ( A ^ { T } A ) = I _ { d }$ Note that the identity matrix $I _ { d }$ is of size $d \times d .$ . However, AL will be a (possibly larger) $n \times n$ matrix, and it can never be the identity matrix when $n > d$ . Therefore, the left-inverse is a one-sided inverse. 

An important point is that there are many matrices L- for which $L ^ { \prime } A = I _ { d }$ , when the matrix A satisfies $d < n$ and has linearly independent columns, although the choice $( A ^ { T } A ) ^ { - 1 } A ^ { T }$ is the preferred one. In order to understand this point, let $\overline { { z } } _ { 1 } \ldots \overline { { z } } _ { d }$ be any set of n-dimensional row vectors such that ${ \overline { { z } } } _ { i } A = { \overline { { 0 } } }$ . As long as the tall matrix A is of rank strictly less than n (i.e., non-empty left null space), such a set of non-zero vectors can be found. Note that even if the rank of the left null space of A is 1, we can find d such vectors that are scalar multiplies of one another. We can stack up these d vectors into a $d \times n$ matrix $Z ,$ , such that the ith row contains the vector $\overline { { z } } _ { i }$ . Then, it can be shown that any $d \times n$ matrix $L _ { z }$ (in which Z is chosen according to the aforementioned procedure) is a left-inverse of $L \colon$ 

$$
L _ {z} = (A ^ {T} A) ^ {- 1} A ^ {T} + Z
$$

This is easy to show because we have: 

$$
L _ {z} A = ((A ^ {T} A) ^ {- 1} A ^ {T} + Z) A = \underbrace {(A ^ {T} A) ^ {- 1} (A ^ {T} A)} _ {I} + \underbrace {Z A} _ {0} = I
$$

Using $L _ { z }$ to solve the system of equations as $\overline { { x } } = L _ { z } \bar { b }$ will provide the same solution as ${ \overline { { x } } } = \not \left( A ^ { T } A \right) ^ { - 1 } A ^ { T } { \overline { { b } } } .$ when a consistent solution to the system of equations exists. However, it will not provide an equally good best-fit to an inconsistent system of equations because it was not derived from the optimization-centric view of linear systems. This is the reason that even though alternative left-inverses exist, only one of them is the preferred one. 

What happens when $n < d$ or when $( A ^ { T } A )$ is not invertible? In such a case, we have an infinite number of possible best-fit solutions, all of which have the same optimal value (which is typically but not $\mathrm { n e c e s s a r i l y ^ { 2 } \ 0 ) }$ . Although there are an infinite number of best-fit solutions, one can discriminate further using a conciseness criterion, according to which we want $\| { \overline { { x } } } \| ^ { 2 }$ as small as possible (as a secondary criterion) among alternative minima for $\| A { \overline { { x } } } - { \overline { { b } } } \| ^ { 2 }$ (which is the primary criterion). The conciseness criterion is a well-known principle in machine learning, wherein simple solutions are preferable over complex ones (see Chapter 4). When the rows of A are linearly independent, the most concise solution $\textstyle { \overline { { x } } }$ is the following (see Exercise 31): 

$$
\overline {{x}} = A ^ {T} (A A ^ {T}) ^ {- 1} \overline {{b}}\tag{2.14}
$$

The matrix $R = A ^ { T } ( A A ^ { T } ) ^ { - 1 }$ is said to be the right-inverse of A, because we have $A R =$ $( A A ^ { T } ) ( A A ^ { T } ) ^ { - 1 } = I _ { n }$ . The linear independence of the rows also ensures that the column space of A spans all of $\mathcal { R } ^ { n }$ and therefore the system is consistent for any vector b. It is also easy to verify that $A { \overline { { x } } } = ( A A ^ { T } ) ( A A ^ { T } ) ^ { - 1 } { \overline { { b } } } = { \bar { b } }$ 

Problem 2.8.1 What is the left-inverse of a matrix containing a single column-vector $[ a , b , c ] ^ { T } \mathcal { Q }$ 

The special case in which the matrix A is square and invertible is a “nice” case in which the left- and right-inverses turn out to be the same. 

Problem 2.8.2 If a matrix A is square and invertible, show that its left- and right-inverses both simplify to $A ^ { - 1 }$ 

Problem 2.8.3 Consider an $n \times d$ matrix A with linearly independent rows and $n < d$ How many matrices R are there that satisfy $A R = I _ { n } { \mathrm { ? } }$ 

## 2.8.1 Moore-Penrose Pseudoinverse

How does one solve inconsistent linear systems of the form $A { \overline { { x } } } = { \overline { { b } } } .$ , when neither the rows nor the columns of A are linearly independent (and, therefore, neither of $A ^ { T } A$ or $A A ^ { T }$ is invertible)? Although the following description will require some optimization results developed in later chapters, the goal of this presentation is to give the reader the full picture of different cases associated with linear systems (and the connections with optimization and machine learning). Therefore, at some points in this section, we use some results developed in later chapters (and it is not necessary for the reader to know the details of the underlying derivations at this stage to understand the broader intuition). 

A natural approach to addressing inconsistent linear systems in which neither the rows nor the columns of A are linearly independent is to combine the idea of finding a best-fit solution with a concise one. This is achieved by minimizing the following objective function: 

$$
J = \underbrace {\| A \overline {{x}} - \overline {{b}} \| ^ {2}} _ {\text {Best Fit}} + \underbrace {\lambda (\sum_ {i = 1} ^ {d} x _ {i} ^ {2})} _ {\text {Concise}}
$$

The additional term in the objective function is a regularization term, which tends to favor small absolute components of the vector x. This is precisely the conciseness criterion discussed in the previous section. The value $\lambda > 0$ is the regularization parameter, which regulates the relative importance of the best-fit term and the conciseness term. 

We have not yet introduced the methods required to compute the solution to the above optimization problem (which are discussed in Section 4.7 of Chapter 4). For now, we ask the reader to make the leap of faith that this optimization problem has the following alternative forms of the solution: 

$$
\begin{array}{l l} \overline {{x}} = (A ^ {T} A + \lambda I _ {d}) ^ {- 1} A ^ {T} \overline {{b}} & [ \text {Regularized left - inverse form} ] \\ \overline {{x}} = A ^ {T} (A A ^ {T} + \lambda I _ {n}) ^ {- 1} \overline {{b}} & [ \text {Regularized right - inverse form} ] \end{array}
$$

It is striking how similar both the above forms are to left- and right-inverses introduced in the previous section, and they are referred to as the regularized left inverses and right inverses, respectively. Both solutions turn out to be the same because of the push-through identity (cf. Problem 1.2.13 of Chapter 1). An important difference of the regularized form of the solution from the previous section is that both the matrices $\left( A ^ { T } A + \lambda I _ { d } \right)$ and $\left( A A ^ { T } + \lambda I _ { n } \right)$ are always invertible for $\lambda > 0$ (see Problem 2.4.2), irrespective of the linear independence of the rows and columns of $A .$ . How should be parameter $\lambda > 0$ be selected? If our primary goal is to find the best-fit solution, and the (limited) purpose of the regularization term is to only play a tie-breaking role among equally good fits (with the secondary conciseness criterion), it makes sense to allow λ to be infinitesimally small. 

In the limit that $\lambda  0 ^ { + }$ , these (equivalent) matrices are the same as the Moore-Penrose pseudoinverse. This provides the following limit-based definition: 

$$
\lim _ {\lambda \to 0 ^ {+}} (A ^ {T} A + \lambda I _ {d}) ^ {- 1} A ^ {T} = \lim _ {\lambda \to 0 ^ {+}} A ^ {T} (A A ^ {T} + \lambda I _ {n}) ^ {- 1} [ \mathrm{Moore-PenrosePseudoinverse} ]
$$

Note that λ approaches 0 from the right, and the function can be discontinuous at $\lambda = 0$ in the most general case. The conventional inverse, the left-inverse, and the right-inverse are special cases of the Moore-Penrose pseudoinverse. When the matrix A is invertible, all four inverses are the same. When only the columns of A are linearly independent, the Moore-Penrose pseudoinverse is the left-inverse. When only the rows of A are linearly independent, the Moore-Penrose pseudoinverse is the right-inverse. When neither the rows nor columns of $A$ are linearly independent, the Moore-Penrose pseudoinverse provides a generalized inverse that none of these special cases can provide. Therefore, the Moore-Penrose pseudoinverse respects both the best-fit and the conciseness criteria like the left- and right inverses. 

The Moore-Penrose pseudoinverse is computed as follows. An $n \times d$ matrix A of rank r has a generalized QR decomposition of the form $A = Q R$ , where $Q$ is an $n \times r$ matrix with orthonormal columns, and $R$ is a rectangular $r \times d$ upper-triangular matrix of full row rank. The matrix $R R ^ { T }$ is therefore invertible. Then, the pseudoinverse of A is as follows: 

$$
A ^ {+} = \lim _ {\lambda \rightarrow 0 ^ {+}} (R ^ {T} R + \lambda I _ {d}) ^ {- 1} R ^ {T} Q ^ {T} = \lim _ {\lambda \rightarrow 0 ^ {+}} R ^ {T} (R R ^ {T} + \lambda I _ {n}) ^ {- 1} Q ^ {T} = R ^ {T} (R R ^ {T}) ^ {- 1} Q ^ {T}
$$

We used $Q ^ { T } Q = I$ in the first step and the push-though identity in the second step. Another approach using singular value decomposition is discussed in Section 7.4.4. 

## 2.8.2 The Projection Matrix

The optimization-centric solution for solving over-determined systems of equations with $< n$ is a more general approach (as compared to the row echelon method), because it also provides an approximate solution to the inconsistent system of equations $A { \overline { { x } } } = { \overline { { b } } }$ . The optimization-centric approach recognizes that the linear system of equations is inconsistent when $\bar { b }$ does not lie in the span of the columns of $A .$ . Therefore, it is also able to “solve” this inconsistent system by projecting $\bar { b }$ on the hyperplane defined by the columns of A and then using this projection $\overline { { b } } ^ { \prime }$ to solve the modified (and consistent) system $A { \overline { { x } } } = { \overline { { b } } } ^ { \prime }$ . After all, $\overline { { b } } ^ { \prime }$ is the closest approximation of $\bar { b }$ within the span of the columns of A. Mapping from $\bar { b }$ to $\overline { { b } } ^ { \prime }$ can also be understood in the context of a linear transformation by a projection matrix. In this section, we will examine the nature of the projection matrix, because it turns out to be a useful linear operator in many settings of linear algebra and optimization. 

First, we will consider the simple case when the columns of A are orthonormal, and emphasize its orthogonality by using the notation $Q = A$ (which is commonly used for orthogonal matrices). Therefore, the system of equations is ${ \dot { Q } } { \overline { { x } } } = { \overline { { b } } }$ . The projection of an n-dimensional vector $\bar { b }$ on a d-dimensional orthonormal basis system (for $d < n )$ is easy to compute. For example, if the $n \times d$ matrix $Q$ contains $d$ orthonormal columns, then the coordinates of $\bar { b }$ on these vectors are given by the dot products with the columns. 

In other words, the coordinates are represented in the d-dimensional vector ${ \overline { { x } } } = Q ^ { T } { \overline { { b } } } { \mathrm { ~ } }$ Furthermore, the actual linear combination<sup>3</sup> of the columns of $Q$ with these coordinates is $\overline { { { b } } } ^ { \prime } = Q \overline { { { x } } } = Q Q ^ { T } \overline { { { b } } } .$ The vector $\overline { { b } } ^ { \prime }$ is the projection of $\bar { b }$ on the d-dimensional plane created by the columns of $Q .$ . Note that if the original matrix $Q$ is square, then its orthonormal columns would imply that $Q Q ^ { T } = Q ^ { T } Q = I ,$ , and therefore $\overline { { { b } } } ^ { \prime } = Q Q ^ { T } \ : \overline { { { b } } } = \overline { { { b } } } .$ . This is not particularly surprising because the projection of an n-dimensional vector on the full ndimensional space is itself. For cases in which the columns of $Q$ are orthonormal but the matrix $Q$ satisfies $d < n ,$ , the matrix $P = Q Q ^ { T }$ is the projection matrix. Projecting a column vector by pre-multiplying with $P$ might result in a different vector; however, projecting again by pre-multiplying with $P$ will not change the projection further. For example, projecting a vector in $\mathcal { R } ^ { \mathrm { i } }$ on a 2-dimensional plane will result in $\mathrm { a }$ “shadow” of the vector on the plane; projecting that smaller vector again on the same plane will not change it. Therefore, projection matrices always satisfy $P ^ { 2 } = P$ 

$$
P ^ {2} = (Q Q ^ {T}) (Q Q ^ {T}) = Q \underbrace {(Q ^ {T} Q)} _ {I} Q ^ {T} = Q Q ^ {T} = P\tag{2.15}
$$

This is referred to as the idempotent property of projection matrices. 

Next, we discuss the projection matrix of a more general $n \times d$ matrix A of full rank. Therefore, if x contains the coordinates of $\overline { { b } } ^ { \prime }$ in the basis of the column space of $A ,$ , we have ${ \bar { b } } ^ { \prime } = A { \overline { { x } } }$ . We want to minimize the squared distance $\| \overline { { b } } ^ { \prime } - \bar { b } \| ^ { 2 } = \| A \overline { { x } } - \bar { b } \| ^ { 2 }$ , because the projection is always the smallest distance to the plane. This is exactly the same problem as discussed in the optimization-centric view discussed in the previous section. Since we assume linearly independent columns with $d < n$ , one can use the left-inverse to obtain the following: 

$$
\overline {{x}} = (A ^ {T} A) ^ {- 1} A ^ {T} \bar {b}\tag{2.16}
$$

Note that x corresponds to the coordinate vector in terms of the columns of $A ,$ , which provides the best approximation $A { \overline { { x } } } = { \overline { { b } } } ^ { \prime }$ . The projection of $\bar { b }$ on the plane defined by the d linearly independent columns of A can also be represented in terms of the projection matrix: 

$$
\overline {{b}} ^ {\prime} = A \overline {{x}} = \underbrace {A (A ^ {T} A) ^ {- 1} A ^ {T}} _ {P} \overline {{b}}\tag{2.17}
$$

Therefore, the $n \times n$ projection matrix is $P = A ( A ^ { T } A ) ^ { - 1 } A ^ { T }$ . The projection matrix is always symmetric and satisfies $P ^ { T } = P$ . When the columns of A are orthonormal and $d < n$ , we have $A ^ { T } A = I$ , and it is easy to show that the projection matrix simplifies to $A A ^ { T }$ . Furthermore, the symmetric projection matrix always satisfies $P ^ { 2 } = P ;$ 

$$
P ^ {2} = A \underbrace {(A ^ {T} A) ^ {- 1} (A ^ {T} A)} _ {I} (A ^ {T} A) ^ {- 1} A ^ {T} = A (A ^ {T} A) ^ {- 1} A ^ {T} = P\tag{2.18}
$$

In fact, any symmetric matrix satisfying $P ^ { 2 } = P$ can be shown to be a projection matrix. The projection matrix is useful for finding the closest approximation of an n-dimensional vector $\bar { b }$ on a plane defined by fewer than n vectors, when the point does not lie on the plane. In fact, the classical problem of least-squares regression can be viewed as that of trying to project an n-dimensional column vector of response variables to its concisely modeled approximation on a d-dimensional plane using a coefficient vector containing the $d \ll n$ coordinates of the projection of the n-dimensional response variables. This situation is shown in Figure 2.9, where we assume that we have a $3 \times 2$ matrix A, which is such that the 3-dimensional vector b does not lie inside the span of the two columns of A. These two column vectors are shown in Figure 2.9. Multiplying $\bar { b }$ with the $3 \times 3$ projection matrix finds the closest approximation $\overline { { b } } ^ { \prime }$ of b which does lie in the span of the two columns. Subsequently, one can find the 2-dimensional vector of coordinates x of $\overline { { b } } ^ { \prime }$ in terms of the two columns, which is the same as computing the solution to $A { \overline { { x } } } = { \overline { { b } } } ^ { \prime }$ . The resulting vector x is exactly the solution to least-squares regression (cf. Section 4.7 of Chapter 4). 

![image](<Images/02_Linear_Transformations_and_Linear_Systems_image_013.jpg>)



Figure 2.9: The projection of the 3-dimensional vector $\bar { b }$ on to its closest 3-dimensional point $\overline { { b } } ^ { \prime }$ lying on a 2-dimensional plane defined by the columns of the $3 \times 2$ matrix A is shown for the inconsistent system $A { \overline { { x } } } = { \overline { { b } } }$ . Multiplying $\bar { b }$ with the $3 \times 3$ projection matrix yields $\overline { { b } } ^ { \prime }$


Multiplying an $n \times d$ matrix A with any non-singular $d \times d$ matrix B creates a matrix AB with the same projection matrix as A, because the projection matrix $( A B ) ( [ A B ] ^ { T } A B ) ^ { - 1 } ( A B ) ^ { T }$ can be algebraically simplified to the projection matrix of A after canceling B and $\dot { B } ^ { T }$ with their inverses. This is because the projection matrix of A only depends on the vector space spanned by the columns of A and post-multiplying A with a non-singular matrix does not change the span of its columns. Therefore, an efficient way of computing the projection matrix and the projection $\overline { { b } } ^ { \prime }$ of $\bar { b }$ is to use QR-decomposition $A = Q R$ to compute the projection matrix as $P = Q Q ^ { T }$ . Note that $Q$ is an $n \times d$ matrix like A, and R is a $d \times d$ upper-triangular matrix. The projection $\overline { { b } } ^ { \prime }$ can be computed as $Q Q ^ { T } \bar { b } .$ . The best-fit solution x to $A { \overline { { x } } } = { \overline { { b } } }$ is the solution to $Q R { \overline { { x } } } = { \overline { { b } } } ^ { \prime }$ as follows: 

$$
R \overline {{x}} = Q ^ {T} \overline {{b}} ^ {\prime} = Q ^ {T} Q Q ^ {T} \overline {{b}} = Q ^ {T} \overline {{b}}\tag{2.19}
$$

Backsubstitution can be used to solve $R { \overline { { x } } } = Q ^ { T } { \bar { b } } .$ . We provide an example of the use of QR-decomposition to compute the projection matrix: 

$$
A = \left[ \begin{array}{c c} 1 & 2 \\ 0 & 2 \\ 1 & 2 \end{array} \right] = Q R = \left[ \begin{array}{c c} 1 / \sqrt {2} & 0 \\ 0 & 1 \\ 1 / \sqrt {2} & 0 \end{array} \right] \left[ \begin{array}{c c} \sqrt {2} & 2 \sqrt {2} \\ 0 & 2 \end{array} \right]
$$

The projection matrix P can be computed as follows: 

$$
P = A (A ^ {T} A) ^ {- 1} A ^ {T} = Q Q ^ {T} = \left[ \begin{array}{c c c} 1 / 2 & 0 & 1 / 2 \\ 0 & 1 & 0 \\ 1 / 2 & 0 & 1 / 2 \end{array} \right]
$$

Problem 2.8.4 (Orthogonal Complementary Projections) Suppose that ${ \cal P } = { \cal Q } { \cal Q } ^ { T }$ is a projection matrix, where $Q$ is an $n \times d$ matrix with orthogonal columns. Show that $( I - P )$ is also a projection matrix in the orthogonal complementary vector space to the projection space of P. A hint is to show that $( I - P )$ can be expressed as $Q _ { 1 } Q _ { 1 } ^ { T }$ 

## 2.9 Ill-Conditioned Matrices and Systems

Ill-conditioned matrices are “almost” singular, and in some cases their non-singularity is only a result of numerical approximations that some algorithm might already have made during the computation of the matrix. Trying to invert such a matrix will result in very large entries, numerical overflows, and all types of round-of errors. In other words, the earlier errors will be greatly magnified. Consider the matrix A and its perturbation $A _ { \epsilon }$ : 

$$
A = \left[ \begin{array}{c c} 1 & 1 \\ 1 & 1 \end{array} \right], A _ {\epsilon} = \left[ \begin{array}{c c} 1 + 1 0 ^ {- 8} & 1 \\ 1 & 1 + 1 0 ^ {- 8} \end{array} \right]
$$

Note that the matrix A is singular, whereas the matrix $A _ { \epsilon }$ is invertible. The matrix $A _ { \epsilon }$ could easily have been created by computer finite-precision errors during computation of what was intended to be $A .$ . The inverse of the matrix can be approximated as follows: 

$$
A _ {\epsilon} ^ {- 1} \approx \frac {1 0 ^ {8}}{2} \left[ \begin{array}{c c} 1 + 1 0 ^ {- 8} / 2 & - 1 + 1 0 ^ {- 8} / 2 \\ - 1 + 1 0 ^ {- 8} / 2 & 1 + 1 0 ^ {- 8} / 2 \end{array} \right] = \frac {1 0 ^ {8}}{2} \left[ \begin{array}{c c} 1. 0 0 0 0 0 0 0 0 5 & - 0. 9 9 9 9 9 9 9 9 5 \\ - 0. 9 9 9 9 9 9 9 9 5 & 1. 0 0 0 0 0 0 0 5 \end{array} \right]
$$

It is evident that the inverse contains very large entries, and many entries need to be represented to a very high degree of precision in order to perform accurate multiplication with the original matrix. The combination of the two is a deadly cocktail because of the disproportionate effect of round-of errors and the possibility of numerical overflows in some cases. In order to understand the problematic aspects of this type of inversion, consider the case where one tries to solve the system of equations $A { \overline { { x } } } = { \overline { { b } } }$ . One of the properties of $A _ { \epsilon }$ is that $A _ { \epsilon } \overline { { x } }$ is always non-zero (because the matrix $A _ { \epsilon }$ is nonsingular), but the value of the norm $\| A _ { \epsilon } \overline { { x } } \|$ will vary a lot. For example, choosing $\overline { { x } } = [ 1 , 1 ]$ will result in $\| A { \overline { { x } } } \| \approx { \sqrt { 2 } }$ . On the other hand, choosing $\overline { { x } } = [ 1 , - 1 ] ^ { T }$ will result in $\lVert A \overline { { x } } \rVert = \mathrm { \ i } 0 ^ { - 8 } \sqrt { 2 }$ 

This type of variation can cause numerical problems in near-singular systems. Since the entries of $A _ { \epsilon } ^ { - 1 }$ are very large, small changes in $\bar { b }$ can lead to large and unstable changes in the solution x. The resulting solutions might sometimes not be semantically meaningful, if the non-singularity of $A _ { \epsilon }$ was caused by computational errors. For example, one would always be able to find a solution to $A _ { \epsilon } \overline { { x } } = \bar { b }$ , but in some cases the solution might be so large so as to cause a numerical overflow (caused by magnification of a tiny computational error). In the above case, using $\bar { b } = [ 1 , - 1 ] ^ { T }$ might lead to numerical problems, where all entries are of the order of $1 0 ^ { 8 }$ . The problem of ill-conditioning is ubiquitous in matrix operations and linear algebra. One can quantify the ill-conditioning of a square and invertible matrix A with the notion of condition numbers: 

Definition 2.9.1 (Condition Number) Let A be ${ \textit { a d } } { \times } d$ invertible matrix. Let $\| A { \overline { { x } } } \| / \| { \overline { { x } } } \|$ be the scaling ratio of vector x. Then, the condition number of A is defined as the ratio of the largest scaling ratio of A (over all d-dimensional vectors) to the smallest scaling ratio over all d-dimensional vectors. 

The smallest possible condition number of 1 occurs for the identity matrix (or any orthogonal matrix). After all, orthogonal matrices only rotate or reflect a vector without scaling it. Singular matrices have undefined condition numbers, and near-singular matrices have extremely large condition numbers. One can compute the condition number of a matrix using a method called singular value decomposition (cf. Section 7.4.4.1 of Chapter 7). The intuitive idea is that singular value decomposition tells us about the various scale factors in a linear transformation (also referred to as singular values). Therefore, the ratio of the largest to smallest scale factor gives us the condition number. See Section 7.4.4.1 of Chapter 7 on methods for solving ill-conditioned systems. 

## 2.10 Inner Products: A Geometric View

The dot product is a natural approach for measuring similarity in vector spaces. The inner product is a generalization of this concept. In some engineering applications, the similarity between two real-valued vectors is obtained as the dot product after stretching the vectors in some “important” directions with the linear transformation A. Therefore, we first provide a practical and easy-to-visualize definition of inner products that works only for $\mathcal { R } ^ { n }$ 

Definition 2.10.1 (Inner Products: Restricted Definition) A mapping from $\overline { { x } } , \overline { { y } } \in$ $\mathcal { R } ^ { n }$ to $\langle { \overline { { x } } } , { \overline { { y } } } \rangle \in { \mathcal { R } }$ is an inner product if and only $i f \left. { \overline { { x } } } , { \overline { { y } } } \right.$ is always equal to the dot product between Ax and Ay for some $n \times n$ non-singular matrix A. The inner product $\langle { \overline { { x } } } , { \overline { { y } } } \rangle$ can also be expressed using the Gram matrix $S = A ^ { T } A$ 

$$
\langle \overline {{x}}, \overline {{y}} \rangle = (A \overline {{x}}) ^ {T} (A \overline {{x}}) = \overline {{x}} ^ {T} [ A ^ {T} A ] \overline {{y}} = \overline {{x}} ^ {T} S \overline {{y}}
$$

When the linear transformation A is a rotreflection matrix, the matrix S is the identity matrix, and the inner product specializes to the normal dot product. The inner product also induces cosines and distances with respect to transformation A: 

$$
\mathrm{cosine} _ {A} (\overline {{x}}, \overline {{y}}) = \frac {\langle \overline {{x}} , \overline {{y}} \rangle}{\sqrt {\langle \overline {{x}} , \overline {{x}} \rangle} \sqrt {\langle \overline {{y}} , \overline {{y}} \rangle}} = \frac {\overline {{x}} ^ {T} S \overline {{y}}}\sqrt {\overline {{x}} ^ {T} S \overline {{x}}} \sqrt {\overline {{y}} ^ {T} S \overline {{y}}} = \frac {(A \overline {{x}}) ^ {T} (A \overline {{y}})}{\| A \overline {{x}} \| _ {2} \| A \overline {{y}} \| _ {2}}
$$

$$
\mathrm{distance} _ {A} (\overline {{x}}, \overline {{y}}) ^ {2} = \langle \overline {{x}} - \overline {{y}}, \overline {{x}} - \overline {{y}} \rangle = (\overline {{x}} - \overline {{y}}) ^ {T} S (\overline {{x}} - \overline {{y}}) = \| A \overline {{x}} - A \overline {{y}} \| _ {2} ^ {2}
$$

It is easy to see that the induced distances and angles correspond to our normal geometric understanding of lengths and angles after using the matrix A to perform a linear transformation on the vectors. The value $\sqrt { \langle \overline { { x } } - \overline { { y } } , \overline { { x } } - \overline { { y } } \rangle }$ is referred to as a metric, which satisfies all laws of Euclidean geometry, such as the triangle inequality. This is not particularly surprising, given that it is a Euclidean distance in transformed space. 

A more general definition of inner products that works beyond ${ \mathcal { R } } ^ { n } \left( \mathrm { e . g . } \right.$ , for abstract vector spaces) is based on particular axiomatic rules that need to be followed: 

Definition 2.10.2 (Inner-Product: General Definition) The real value $\langle \overline { { u } } , \overline { { v } } \rangle$ is an inner product between u and v, if it satisfies the following axioms for all u and v: 

Additivity: $\langle \overline{u},\overline{v} +\overline{w}\rangle = \langle \overline{u},\overline{v}\rangle +\langle \overline{u},\overline{w}\rangle ,\quad \langle \overline{v} +\overline{w},\overline{u}\rangle = \langle \overline{v},\overline{u}\rangle +\langle \overline{w},\overline{u}\rangle$ Multiplicativity: $\langle c\overline{u},\overline{v}\rangle = c\langle \overline{u},\overline{v}\rangle ,\quad \langle \overline{u},c\overline{v}\rangle = c\langle \overline{u},\overline{v}\rangle \forall c\in \mathcal{R}$ Commutativity: $\langle \overline{u},\overline{v}\rangle = \langle \overline{v},\overline{u}\rangle$ Positive definiteness: $\langle \overline{u},\overline{u}\rangle \geq 0$ with equality only for the zero vector 

Every finite-dimensional inner product $\langle { \overline { { x } } } , { \overline { { y } } } \rangle$ in $\mathcal { R } ^ { n }$ satisfying the above axioms can be shown to be equivalent to ${ \overline { { x } } } ^ { T } S { \overline { { y } } }$ for some carefully chosen Gram matrix $S = A ^ { T } A$ . Therefore, at least for finite-dimensional vector spaces in $\mathcal { R } ^ { n }$ , the linear transformation definition and $t h e$ axiomatic definition $o f \left. \overline { { x } } , \overline { { y } } \right.$ are equivalent. The following exercise shows how such a matrix $S$ can be constructed from the axiomatic definition of an inner product: 

Problem 2.10.1 (Axiomatic Inner-Product Is Transformed Dot Product) Suppose that the inner product $\langle { \overline { { x } } } , { \overline { { y } } } \rangle$ satisfies the axiomatic definition for all pairs $\overline { { x } } , \overline { { y } } \in \mathcal { R } ^ { n }$ . Show that the inner product $\langle { \overline { { x } } } , { \overline { { y } } } \rangle$ can also be expressed as $\overline { { x } } ^ { T } S \overline { { y } } .$ , where the $( i , j )$ th entry $o f S$ is $\langle \overline { { e } } _ { i } , \overline { { e } } _ { j } \rangle$ . Here, $\overline { { e } } _ { i }$ is the ith column of the $n \times n$ identity matrix. The next chapter shows that matrices like $S$ can always be expressed as $A ^ { T } A$ for $n \times n$ matrix A because of the positive definite axiom. Why is $\langle { \overline { { x } } } , { \overline { { y } } } \rangle$ equal to the vanilla dot product between Ax and Ay? 

Problem 2.10.2 Suppose that you are given all $n \times n$ real-valued inner products between pairs drawn from n linearly independent vectors in $\mathcal { R } ^ { n }$ . Show how you can compute $\langle { \overline { { x } } } , { \overline { { y } } } \rangle$ for any $\overline { { x } } , \overline { { y } } \in \mathcal { R } ^ { n }$ using the basic axioms of inner products. 

## 2.11 Complex Vector Spaces

As discussed earlier in this chapter, vector spaces can be defined over any $f i e l d$ that satisfies the field axioms. One such example of a field is the domain of complex numbers. A complex number is a value of the form $a + i b$ where $i = \sqrt { - 1 }$ . Complex numbers are often written in the polar form $r \left[ \cos ( \theta ) + i \sin ( \theta ) \right]$ , where $r = { \sqrt { a ^ { 2 } + b ^ { 2 } } }$ and $\theta = \cos ^ { - 1 } ( a / r )$ . One can also show the following Euler identity by comparing the Taylor expansions of the exponential and trigonometric series (see Problem 1.5.1): 

$$
\exp (i \theta) = \cos (\theta) + i \sin (\theta)
$$

The angle θ must be expressed in radians for this formula to hold. Therefore, a complex number may be represented as $r \cdot \exp ( i \theta )$ . The polar representation is very convenient in the context of many linear algebra operations. This is because the multiplication of two complex numbers is a simple matter of adding angular exponents and multiplying their magnitudes. This property is used in various types of matrix products. 

One can define a vector space over the complex domain using the same additive and multiplicative properties over ${ \mathcal { C } } ^ { n }$ as in $\mathcal { R } ^ { n }$ : 

Definition 2.11.1 (Vector Space in ${ \mathcal { C } } ^ { n } )$ A set of vectors that correspond to a subset $o f { \mathcal { C } } ^ { n }$ is a vector space, if it satisfies the following properties: 

1. $I f { \overline { { x } } } \in \nu$ then $c { \overline { { x } } } \in \nu$ for any scalar $c \in { \mathcal { C } }$ 

2. $I f \overline { { x } } , \overline { { y } } \in \mathcal { V } _ { \cdot }$ , then $\overline { { x } } + \overline { { y } } \in \mathcal { V } .$ 

Here, it is important to note that the multiplicative scalar is drawn from the complex domain. For example, the value of c could be a number such as $1 + i$ . This is an important difference from Definition 2.3.2 on real-valued vector spaces. The consequence of this fact is that one can still use the standard basis $\overline { { e } } _ { 1 } \ldots \overline { { e } } _ { n }$ to represent any vector in ${ \mathcal { C } } ^ { n }$ . Here, each $\overline { { e } } _ { i }$ is an n-dimensional vector with a 1 in the ith entry, and a 0 in all other entries. Although $\overline { { e } } _ { i }$ has real components, all real vectors are special cases of complex-valued vectors. Any vector $\overline { { x } } = [ x _ { 1 } \ldots x _ { d } ] ^ { T } \in \mathcal { C } ^ { n }$ can be expressed in terms of standard basis, where the ith coordinate is the complex number $x _ { i }$ . The key point is that the coordinates can also be complex values, since the vector space is defined over the complex field. We need to be able to perform operations such as projections in order to create coordinate representations. This is achieved with the notion of complex inner products. 

As in the case of real inner products, one wants to retain geometric properties of Euclidean spaces (like notions of lengths and angles). Generalizing inner products from the real domain to the complex domain can be tricky. In real-valued Euclidean spaces, the dot product of the vector with itself provides the squared norm. This definition does not work for complex vectors. For example, a blind computation of the real-valued definition of squared norm of $\overline { { v } } = [ 1 , 2 i ] ^ { T }$ results in the following: 

$$
\overline {{v}} ^ {T} \overline {{v}} = [ 1, 2 i ] \left[ \begin{array}{c} 1 \\ 2 i \end{array} \right] = 1 ^ {2} + 4 i ^ {2} = 1 - 4 = - 3\tag{2.20}
$$

We obtain a negative value for squared norm, which is intended to be a proxy for the squared length. Therefore, we need modified axioms for the complex-valued inner product $\langle \overline { { u } } , \overline { { v } } \rangle$ 

Additivity: u, v + w = u, v + u, w , v + w, u = v, u + w, u 

Multiplicativity: $\langle c { \overline { { u } } } , { \overline { { v } } } \rangle = c ^ { * } \langle { \overline { { u } } } , { \overline { { v } } } \rangle , \langle { \overline { { u } } } , c { \overline { { v } } } \rangle = c \langle { \overline { { u } } } , { \overline { { v } } } \rangle \forall c \in { \mathcal { C } }$ 

Conjugate symmetry: $\langle \overline { { u } } , \overline { { v } } \rangle = \langle \overline { { v } } , \overline { { u } } \rangle ^ { * }$ 

Positive definiteness: $\langle \overline { { u } } , \overline { { u } } \rangle \geq 0$ , with equality only for the zero vector 

The superscript ‘*’ indicates the conjugate of a complex number, which is obtained by negating the imaginary part of the number. The inner product computation of Equation 2.20 is invalid is because it violates the positive definite property. 

For a scalar complex number, its squared norm is defined by its product with its conjugate. For example, the squared norm of $a + i b$ is $( a - i b ) ( a + i b ) = a ^ { 2 } + b ^ { 2 }$ . In the case of vectors, we can combine transposition with conjugation in order to define inner products. The conjugate transpose of a complex vector or matrix is defined as follows: 

Definition 2.11.2 (Conjugate Transpose of Vector and Matrix) The conjugate transpose $\overline { { v } } ^ { * }$ of a complex vector $\overline { { v } }$ is obtained by transposing the vector and replacing each entry with its complex conjugate. The conjugate transpose $V ^ { * }$ of a complex matrix V is obtained by transposing the matrix and replacing each entry with its complex conjugate. 

Therefore, the conjugate transpose of $[ 1 , 2 i ] ^ { T }$ is $[ 1 , - 2 i ]$ , and the conjugate transpose of $\begin{array} { r } { [ 1 + i , 2 + 3 i ] ^ { T } \mathrm { ~ i s ~ } [ 1 - i , 2 - 3 i ] } \end{array}$ 

A popular way of defining<sup>4</sup> the inner product between vectors ${ \overline { { u } } } , { \overline { { v } } } \in { \mathcal { C } } ^ { n }$ , which is the direct analog of the dot product, is the following: 

$$
\langle \overline {{u}}, \overline {{v}} \rangle = \overline {{u}} ^ {*} \overline {{v}}\tag{2.21}
$$

The inner product can be a complex number. Unlike vectors in $\mathcal { R } ^ { n }$ , the inner product is not commutative over the complex domain, because $\langle \overline { { u } } , \overline { { v } } \rangle$ is the complex conjugate of $\langle \overline { { v } } , \overline { { u } } \rangle$ $( \mathrm { i . e . , c o n j u g a t e }$ symmetry property). The squared norm of a vector ${ \overline { { v } } } \in { \mathcal { C } } ^ { n }$ is defined as ${ \overline { { v } } } ^ { * } { \overline { { v } } }$ rather than $\boldsymbol { \overline { { v } } } ^ { T } \boldsymbol { \overline { { v } } } ;$ this is the inner product of the vector with itself. Based on this definition, the squared norm of $[ 1 , 2 i ] ^ { T }$ is $[ 1 , \bar { - } 2 i ] [ 1 , 2 i ] ^ { T }$ , which is $1 ^ { 2 } + 2 ^ { 2 } = 5$ . Similarly, the squared norm of $[ 1 + i , 2 + 3 i ] ^ { T } { \mathrm { ~ i s ~ } } ( 1 + i ) ( 1 - i ) + ( 2 + 3 i ) ( 2 - 3 i ) = 1 + 1 + 4 + 9 = 1 5$ . Note that both are positive, which is consistent with the positive definite property. 

As in the real domain, two complex vectors are orthogonal when their inner product is 0. In such a case, both the complex conjugates $\langle \overline { { u } } , \overline { { v } } \rangle$ and $\langle \overline { { v } } , \overline { { u } } \rangle$ are zero. 

Definition 2.11.3 (Orthogonality in ${ \mathcal { C } } ^ { n } )$ Two vectors $\overline { { u } }$ and v from ${ \mathcal { C } } ^ { n }$ are orthogonal if and only if $\overline { { u } } ^ { * } \overline { { v } } = \overline { { v } } ^ { * } \overline { { u } } = 0$ 

An orthonormal set of vectors in ${ \mathcal { C } } ^ { n }$ corresponds to any set of vectors $\overline { { v } } _ { 1 } \ldots \overline { { v } } _ { n }$ , such that $\overline { { \boldsymbol { v } } } _ { i } ^ { * } \overline { { \boldsymbol { v } } } _ { j }$ is 1 when $i = j$ , and 0, otherwise. Note that the standard basis is also orthogonal in ${ \mathcal { C } } ^ { n }$ . As in the real domain, an $n \times n$ matrix containing orthogonal columns from ${ \mathcal { C } } ^ { n }$ is referred to as orthogonal or unitary. 

Definition 2.11.4 (Orthogonal Matrix with Complex Entries) A matrix V with complex-valued entries is orthogonal or unitary if and only if $V V ^ { * } = V ^ { * } V = I$ 

It is relatively easy to compute the inverse of orthogonal matrices by simply computing their conjugate transposes. This idea has applications to the discrete Fourier transform. 

## 2.11.1 The Discrete Fourier Transform

The discrete Fourier transform is closely related to the discrete cosine transform, and it is capable of finding an orthonormal basis for time-series in the complex domain. As a practical matter, it is used as an alternative to the discrete cosine transform (cf. Section 2.7.3) for real-valued series with a high level of periodicity. 

Consider a complex-valued time series ${ \overline { { s } } } \in { \mathcal { C } } ^ { n }$ , which we would like to transform into a complex and orthogonal basis. The Fourier basis uses n mutually orthogonal basis vectors $\bar { b } _ { 1 } \ldots \bar { b } _ { n }$ from ${ \mathcal { C } } ^ { n }$ , so that the basis vector $\overline { { b } } _ { j }$ is defined as follows: 

$$
\overline {{b}} _ {j} = [ 1, \exp (\omega [ j - 1 ] i), \ldots , \underbrace {\exp (\omega [ k - 1 ] [ j - 1 ] i)} _ {k \text {th component}}, \ldots , \exp (\omega [ n - 1 ] [ j - 1 ] i) ] ^ {T} / \sqrt {n}
$$

Note that the value of i in the above does nor refer to a variable but to the imaginary number $\sqrt { - 1 }$ . The value of $\omega$ is $2 \pi / n$ in radians, and therefore each complex number is written in polar form. We make the following assertion: 

Lemma 2.11.1 (Orthonormality of Fourier Basis) The basis vectors $\bar { b } _ { 1 } \ldots \bar { b } _ { n }$ of the Fourier transform are orthonormal. 

Proof: It is easy to see that $\begin{array} { r } { \bar { b } _ { p } ^ { * } \bar { b } _ { p } = [ \sum _ { k = 0 } ^ { n - 1 } ( 1 / n ) \mathrm { e x p } ( 0 ) ] = 1 } \end{array}$ . On computing $\overline { { b } } _ { p } ^ { * } \overline { { b } } _ { q }$ for $p \neq q$ one can sum a geometric series of exponentials: 

$$
\overline {{b}} _ {p} ^ {*} \overline {{b}} _ {q} = \sum_ {k = 0} ^ {n - 1} \exp (k [ q - p ] \omega i) = \frac {\exp ([ n \omega ] [ q - p ] i) - 1}{\exp ([ q - p ] \omega i) - 1} = \overbrace {\frac {\exp (2 \pi [ q - p ] i)}{\exp ([ q - p ] \omega) - 1}} ^ {1} - 1 = 0
$$

One of the simplifications above uses the fact that $\exp ( i \theta )$ is 1 when θ is a multiple of $2 \pi$ . 


One can, therefore, create a basis matrix B whose columns contain the basis vectors $\bar { b } _ { 1 } \ldots \bar { b } _ { n }$ For example, the $8 \times 8$ basis matrix for transformation of vectors in $\mathcal { C } ^ { 8 }$ is as follows:


<table><tr><td rowspan="8"><eq>\frac{1}{\sqrt{8}}</eq></td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td></tr><tr><td>1</td><td><eq>\exp(\frac{2\pi i}{8})</eq></td><td><eq>\exp(\frac{4\pi i}{8})</eq></td><td><eq>\exp(\frac{6\pi i}{8})</eq></td><td><eq>\exp(\frac{8\pi i}{8})</eq></td><td><eq>\exp(\frac{10\pi i}{8})</eq></td><td><eq>\exp(\frac{12\pi i}{8})</eq></td><td><eq>\exp(\frac{14\pi i}{16})</eq></td></tr><tr><td>1</td><td><eq>\exp(\frac{4\pi i}{8})</eq></td><td><eq>\exp(\frac{8\pi i}{8})</eq></td><td><eq>\exp(\frac{12\pi i}{8})</eq></td><td><eq>\exp(\frac{16\pi i}{8})</eq></td><td><eq>\exp(\frac{20\pi i}{8})</eq></td><td><eq>\exp(\frac{24\pi i}{8})</eq></td><td><eq>\exp(\frac{28\pi i}{8})</eq></td></tr><tr><td>1</td><td><eq>\exp(\frac{6\pi i}{8})</eq></td><td><eq>\exp(\frac{12\pi i}{8})</eq></td><td><eq>\exp(\frac{18\pi i}{8})</eq></td><td><eq>\exp(\frac{24\pi i}{8})</eq></td><td><eq>\exp(\frac{30\pi i}{8})</eq></td><td><eq>\exp(\frac{36\pi i}{8})</eq></td><td><eq>\exp(\frac{42\pi i}{8})</eq></td></tr><tr><td>1</td><td><eq>\exp(\frac{8\pi i}{8})</eq></td><td><eq>\exp(\frac{16\pi i}{8})</eq></td><td><eq>\exp(\frac{24\pi i}{8})</eq></td><td><eq>\exp(\frac{32\pi i}{8})</eq></td><td><eq>\exp(\frac{40\pi i}{8})</eq></td><td><eq>\exp(\frac{48\pi i}{8})</eq></td><td><eq>\exp(\frac{56\pi i}{8})</eq></td></tr><tr><td>1</td><td><eq>\exp(\frac{10\pi i}{8})</eq></td><td><eq>\exp(\frac{20\pi i}{8})</eq></td><td><eq>\exp(\frac{30\pi i}{8})</eq></td><td><eq>\exp(\frac{40\pi i}{8})</eq></td><td><eq>\exp(\frac{50\pi i}{8})</eq></td><td><eq>\exp(\frac{60\pi i}{8})</eq></td><td><eq>\exp(\frac{70\pi i}{8})</eq></td></tr><tr><td>1</td><td><eq>\exp(\frac{12\pi i}{8})</eq></td><td><eq>\exp(\frac{24\pi i}{8})</eq></td><td><eq>\exp(\frac{36\pi i}{8})</eq></td><td><eq>\exp(\frac{48\pi i}{8})</eq></td><td><eq>\exp(\frac{60\pi i}{8})</eq></td><td><eq>\exp(\frac{72\pi i}{8})</eq></td><td><eq>\exp(\frac{84\pi i}{8})</eq></td></tr><tr><td>1</td><td><eq>\exp(\frac{14\pi i}{8})</eq></td><td><eq>\exp(\frac{28\pi i}{8})</eq></td><td><eq>\exp(\frac{42\pi i}{8})</eq></td><td><eq>\exp(\frac{56\pi i}{8})</eq></td><td><eq>\exp(\frac{70\pi i}{8})</eq></td><td><eq>\exp(\frac{84\pi i}{8})</eq></td><td><eq>\exp(\frac{98\pi i}{8})</eq></td></tr></table>


The matrix B is orthogonal, and therefore the basis transformation is length preserving:


$$
\| B \overline {{s}} \| ^ {2} = (B s) ^ {*} (B s) = s ^ {*} \underbrace {(B ^ {*} B)} _ {I} s = \| s \| ^ {2}
$$

Given a complex-valued time-series s from $\mathcal { C } ^ { 8 }$ , one can transform it to the Fourier basis by solving the system of equations $B { \overline { { x } } } = { \overline { { s } } }$ . The solution to this system is simply $\overline { { x } } = B ^ { * } \overline { { s } }$ which provides the complex coefficients of the series. As a practical matter, the approach is used for real-valued time series. For example, consider our running example of the timeseries $\overline { { s } } ~ = ~ [ 8 , 6 , 2 , 3 , 4 , 6 , 6 , 5 ] ^ { T }$ , which is used in Section 2.3.4 on the wavelet transform. One can simply pretend that this series is a special case of a complex-valued series, and compute the Fourier coefficients as $\overline { { x } } ~ = ~ B ^ { * } \overline { { s } }$ . The main problem with this approach is that it transforms a series from $\mathcal { R } ^ { 8 }$ to $\mathcal { C } ^ { 8 }$ , since the coordinates in $\textstyle { \overline { { x } } }$ will have imaginary components. A na¨ıve solution to this problem is to create a representation in $R ^ { 1 \breve { 6 } }$ that contains both real and imaginary parts of each component of ${ \overline { { x } } } .$ Therefore, the Fourier transformation contains twice the number of real-valued coefficients as the original series. This increase is a consequence of treating a real-valued time-series as a special case of a complex-valued series. Because of the real-valued nature of the original series, wasteful redundancy exists in the coordinate vector ${ \overline { { x } } } ,$ whose kth component is always the complex conjugate of the $( 8 - k )$ th component for all k. Therefore, one can keep only the first four components of the vector ${ \overline { { x } } } \in { \mathcal { C } } ^ { 8 }$ and unroll the real and imaginary components of these four complex numbers into $\mathcal { R } ^ { 8 }$ . Furthermore, one sets the small Fourier coefficients to zero in practice, which leads to space-efficient sparse vector representations. 

Problem 2.11.1 Use the $8 \times 8$ Fourier matrix proposed in this section in order to create the Fourier representation $o f \overline { { s } } = [ 8 , 6 , 2 , 3 , 4 , 6 , 6 , 5 ] ^ { T }$ 

## 2.12 Summary

Machine learning applications often use additive and multiplicative transformations with matrices, which correspond to the fundamental building blocks of linear algebra. These building blocks are utilized for different types of decompositions such as the QR decomposition and the LU decomposition. The decompositions are the workhorses to solution methodologies for many matrix-centric problems in machine learning. Specific examples include solving systems of linear equations and linear regression. 

## 2.13 Further Reading

Fundamental books on linear algebra include those by Strang [122, 123], David Lay [77], and Hofman-Kunze [62]. The matrix computation book by Golub and Van Loan [52] teaches important numerical methods. A discussion of numerical methods that combine linear algebra and optimization is provided in [99]. 

## 2.14 Exercises

1. If we have a square matrix A that satisfies $A ^ { 2 } = I$ , it is always the case that $A = \pm I$ Either prove the statement or provide a counterexample. 

2. Show that the matrices $A , A A ^ { T }$ , and $A ^ { T } A$ must always have the same rank for any $n \times d$ matrix A. Start by showing that $A { \overline { { x } } } = { \overline { { 0 } } }$ if and only if $A ^ { T } A { \overline { { x } } } = { \overline { { 0 } } }$ 

3. Provide a geometric interpretation of $A ^ { 9 }$ , where A is a $2 \times 2$ rotation matrix at a counter-clockwise angle of $6 0 ^ { \circ }$ 

4. Consider $6 \times 1 0$ matrices A and B of rank 6. What is the minimum and maximum possible rank of the $6 \times 6$ matrix $A B ^ { T }$ . Provide examples of A and B in each case. 

5. Use each of row reduction and Gram-Schmidt to find basis sets for the span of $\{ [ 1 , 2 , 1 ] ^ { T } , [ 2 , 1 , 1 ] ^ { T } , [ 3 , 3 , 2 ] ^ { T } \}$ . What are the best-fit coordinates of $[ 1 , 1 , 1 ] ^ { T }$ in each of these basis sets? Verify that the best-fit vector is the same in the two cases. 

6. Propose a test using Gram-Schmidt orthogonalization to identify whether two sets of (possibly linearly dependent) vectors span the same vector space. 

7. A $d \times d$ skew symmetric matrix satisfies $A ^ { T } = - A$ . Show that all diagonal elements of such a matrix are 0. Show that each $\overline { { x } } \in \mathcal { R } ^ { d }$ is orthogonal to Ax if and only if A is skew symmetric. What is the difference from a pure rotation by $9 0 ^ { \circ } ?$ 

8. Consider the $4 \times 4$ Givens matrix $G _ { c } ( 2 , 4 , 9 0 )$ based on the notations on page 47. This matrix performs a $9 0 °$ counter-clockwise rotation of a 4-dimensional column vector in the plane of the second and fourth dimensions. Show how to obtain this matrix as the product of two Householder reflection matrices. Think geometrically based on Section 2.2 in order to solve this problem. Is the answer to this question unique? 

9. Repeat Exercise 8 for a Givens matrix that rotates a column vector counter-clockwise for $1 0 ^ { \circ }$ instead of $9 0 ^ { \circ }$ 

10. Consider the $5 \times 5$ matrices A, B, and C, with ranks 5, 2, and 4, respectively. What is the minimum and maximum possible rank of $( A + B ) C$ 

11. Solve the following system of equations using the Gaussian elimination procedure: 

$$
{\left[ \begin{array}{l l l} 0 & 1 & 1 \\ 1 & 1 & 1 \\ 1 & 2 & 1 \end{array} \right]} {\left[ \begin{array}{l} x _ {1} \\ x _ {2} \\ x _ {3} \end{array} \right]} = {\left[ \begin{array}{l} 2 \\ 3 \\ 4 \end{array} \right]}
$$

Now use these row operations to create an LU decomposition. Is it possible to perform an LU decomposition of this matrix without the use of a permutation matrix? 

12. Solve the system of equations in the previous exercise using QR decomposition. Use the Gram-Schmidt method for orthogonalization. Use the QR decomposition to compute the inverse of the matrix if it exists. 

13. Why must the column space of matrix AB must be a subspace of the column space of A? Show that all four fundamental subspaces of $A ^ { k + 1 }$ must be the same as that of $A ^ { k }$ for some integer k. 

14. Consider a vector space $ { \mathcal { V } } \subset  { \mathcal { R } } ^ { 3 }$ and two of its possible basis sets $\begin{array} { r l } { B _ { 1 } } & { { } = } \end{array}$ $\{ [ 1 , 0 , 1 ] ^ { T } , [ 1 , 1 , 0 ] ^ { T } \}$ and $\boldsymbol { B } _ { 2 } = \{ [ 0 , 1 , - 1 ] ^ { T } , [ 2 , 1 , 1 ] ^ { T } \}$ . Show that $\boldsymbol { B } _ { 1 }$ and $B _ { 2 }$ are basis sets for the same vector space. What is the dimensionality of this vector space? Now consider a vector $\overline { { v } } \in \mathcal { V }$ with coordinates $[ 1 , 2 ] ^ { T }$ in basis $\boldsymbol { B } _ { 1 }$ , where the order of coordinates matches the order of listed basis vectors. What is the standard basis representation of v? What are the coordinates of v in $\textstyle B _ { 2 } ! $ 

15. Find the projection matrix of the following matrix using the QR method: 

$$
A = \left[ \begin{array}{l l} 3 & 6 \\ 0 & 1 \\ 4 & 8 \end{array} \right]
$$

How can you use the projection matrix to determine whether the vector $\bar { b } = [ 1 , 1 , 0 ] ^ { T }$ belongs to the column space of A? Find a solution (or best-fit solution) to $A { \overline { { x } } } = { \overline { { b } } }$ 

16. For the problem in Exercise 15, does a solution exist to $A ^ { T } { \overline { { x } } } = { \overline { { c } } } .$ , where $\overline { { c } } = [ 2 , 2 ] ^ { T } ?$ If no solution exists, find the best-fit. If one or more solutions exist, find the one for which x is as small as possible. 

17. Gram-Schmidt with Projection Matrix: Given a set of $m < n$ linearly independent vectors $\overline { { a } } _ { 1 } \ldots . \overline { { a } } _ { m }$ in $\mathcal { R } ^ { n }$ , let $A _ { r }$ be the $n \times r$ matrix defined as $A _ { r } = [ \overline { { a } } _ { 1 } , \overline { { a } } _ { 2 } , \ldots , \overline { { a } } _ { r } ]$ for each $r \in \{ 1 \ldots m \}$ . Show the result that after initializing $\overline { { q } } _ { 1 } = \overline { { a } } _ { 1 }$ , the unnormalized Gram-Schmidt vectors $\overline { { q } } _ { 2 } \ldots \overline { { q } } _ { m }$ of $\overline { { a } } _ { 2 } \dots \overline { { a } } _ { m }$ can be computed non-recursively using the projection matrix $P _ { s }$ as follows: 

$$
\overline {{q}} _ {s + 1} = [ I - A _ {s} (A _ {s} ^ {T} A _ {s}) ^ {- 1} A _ {s} ^ {T} ] \overline {{a}} _ {s + 1} = \overline {{a}} _ {s + 1} - [ P _ {s} \overline {{a}} _ {s + 1} ] \forall s \in \{1, \ldots , m - 1 \}
$$

18. Consider a $d \times d$ matrix A such that its right null space is identical to its column space. Show that d is even, and provide an example of such a matrix. 

19. Show that the columns of the $n \times d$ matrix A are linearly independent if and only if $f ( { \overline { { x } } } ) = A { \overline { { x } } }$ is a one-to-one function. 

20. Consider an $n \times n$ matrix A. Show that if the length of the vector Ax is strictly less than that of the vector x for all non-zero $\overline { { x } } \in \mathcal { R } ^ { n }$ , then $( A - I )$ is invertible. 

21. It is intuitively obvious that an $n \times n$ projection matrix P will always satisfy $\| \bar { P b } \| \leq$ $\lVert \bar { b } \rVert$ for any $\bar { b } \in \mathcal { R } ^ { n }$ , since it projects b on a lower-dimensional hyperplane. Show algebraically that $\left\| P \bar { b } \right\| \leq \left\| \bar { b } \right\|$ for any $\bar { b } \in \mathcal { R } ^ { n }$ . [Hint: Express the rank-d projection matrix $P = Q Q ^ { T }$ for $n \times d$ matrix Q and start by showing $\lVert Q Q ^ { T } \bar { b } \rVert = \lVert Q ^ { T } \bar { b } \rVert$ . What is the geometric interpretation of $Q ^ { T } \bar { b }$ and $Q Q ^ { T } \bar { b ! } ]$ 

22. Let A be a $1 0 \times 1 0$ matrix. If $A ^ { 2 }$ has rank 6, find the minimum and maximum possible ranks of A. Give examples of both matrices. 

23. Suppose that we have a system of equations $A { \overline { { x } } } = { \overline { { b } } }$ for some $n \times d$ matrix A. We multiply both sides of the above equation with a non-zero, $m \times n$ matrix B to obtain the new system $B A \overline { { x } } = B \overline { { b } }$ . Provide an example to show that the solution sets to the two systems need not be identical. How are the solution sets related in general? Provide one example of a sufficient condition on a rectangular matrix B under which they are identical. [For scalar equations, multiplying both sides by a scalar value does not change the equation unless that value is 0. This exercise shows that multiplying both sides of a vector equation with a matrix can have more intricate effects.] 

24. Show that every $n \times n$ Householder reflection matrix can be expressed as $Q _ { 1 } Q _ { 1 } ^ { T } -$ $Q _ { 2 } Q _ { 2 } ^ { T }$ , where concatenating the columns of $Q _ { 1 }$ and $Q _ { 2 }$ creates an $n \times n$ orthogonal ma trix, and $Q _ { 2 }$ contains a single column. What is the nature of the linear transformation, when $Q _ { 2 }$ contains more than one column? 

25. Show that if $B ^ { k }$ has the same rank as that of $B ^ { k + 1 }$ for a particular value of $k \geq 1$ then $B ^ { k }$ has the same rank as $B ^ { k + r }$ for all $r \geq 1$ 

26. Show that if an $n \times n$ matrix B has rank $( n - 1 )$ , and the matrix $B ^ { k }$ has rank $( n - k )$ then each matrix $B ^ { r }$ for r from 1 to k has rank $( n - r )$ . Show how to construct a chain of vectors $\overline { { v } } _ { 1 } \ldots \overline { { v } } _ { k }$ so that $B \overline { { v } } _ { i } = \overline { { v } } _ { i - 1 }$ for $i > 1$ , and $B { \overline { { v } } } _ { 1 } = { \overline { { 0 } } }$ . [Note: You will encounter a similar but more complex Jordan chain in Chapter 3.] 

27. Suppose that $B ^ { k } \overline { { v } } = \overline { { 0 } }$ for a particular vector v for some $k \geq 2$ , and $B ^ { r } { \overline { { v } } } \neq { \overline { { 0 } } }$ for all $r < k$ . Show that the vectors v, Bv, $B ^ { 2 } \overline { { v } } , \ldots , B ^ { k - 1 } \overline { { v } }$ must be linearly independent. 

28. Inverses with QR decomposition: Suppose you perform QR decomposition of an invertible $d \times d$ matrix as $A = Q R$ . Show how you can use this decomposition relationship for finding the inverse of A by solving d different triangular systems of linear equations, each of which can be solved by backsubstitution. Show how to compute the left or right inverse of a matrix with QR decomposition and back substitution. 

29. Least-squares error by QR decomposition: Let $A { \overline { { x } } } = { \overline { { b } } }$ be a system of equations in which the $n \times d$ matrix A has linearly independent columns. Suppose that you decompose $A = Q R$ , where Q is an $n \times d$ matrix with orthogonal columns and $R$ is a $d \times d$ upper-triangular matrix. Show that the best-fit error (using the least-squares model) is given by $\| \bar { b } \| ^ { 2 } - \| Q ^ { T } \bar { b } \| ^ { 2 }$ . How would you find the least-squares error via QR decomposition in the case that A does not have linearly independent columns or rows? [Hint: Think geometrically in terms of the projection matrix.] 

30. Consider a modified least-squares problem of minimizing $\| A \overline { { x } } - \bar { b } \| ^ { 2 } + \overline { { c } } ^ { T } \overline { { x } } .$ , where A is an $n \times d$ matrix, x, c are d-dimensional vectors, and $\bar { \overline { { b } } }$ is an n-dimensional vector. Show that the problem can be reduced to the standard least-squares problem as long as c lies in the row space of A. What happens when c does not lie in the row space of A? [Hint: First examine the univariate version of this problem.] 

31. Right-inverse yields concise solution: Let $\overline { { x } } = \overline { { v } }$ be any solution to the consistent system $A { \overline { { x } } } = { \overline { { b } } }$ with $n \times d$ matrix A containing linearly independent rows. Let $\textstyle { \overline { { v } } } _ { r } =$ $\overset { \cdot } { A } ^ { T } ( A A ^ { T } ) ^ { - 1 } \overline { { b } }$ be the solution given by the right inverse. Then, show the following: 

$$
\| \overline {{v}} \| ^ {2} = \| \overline {{v}} - \overline {{v}} _ {r} \| ^ {2} + \| \overline {{v}} _ {r} \| ^ {2} + 2 \overline {{v}} _ {r} ^ {T} (\overline {{v}} - \overline {{v}} _ {r}) \geq \| \overline {{v}} _ {r} \| ^ {2} + 2 \overline {{v}} _ {r} ^ {T} (\overline {{v}} - \overline {{v}} _ {r})
$$

Now show that $\overline { { v } } _ { r } ^ { T } ( \overline { { v } } - \overline { { v } } _ { r } ) = 0$ and therefore $\| \overline { { v } } \| ^ { 2 } \geq \| \overline { { v } } _ { r } \| ^ { 2 }$ 

32. Show that any $2 \times 2$ Givens rotation matrix is a product of at most two Householder reflection matrices. Think geometrically before wading into the algebra. Now generalize the proof to $d \times d$ matrices. 

33. Show algebraically that if two tall matrices of full rank have the same column space, then they have the same projection matrix. 

34. Construct $4 \times 3$ matrices A and B of rank 2 that are not multiples of one another, but with the same four fundamental subspaces of linear algebra. [Hint: $A = U V . ]$ 

35. Show that any Householder reflection matrix $( I - 2 { \overline { { v } } } { \overline { { v } } } ^ { T } )$ can be expressed as follows: 

$$
(I - 2 \overline {{v}} \overline {{v}} ^ {T}) = \left[ \begin{array}{c c} \cos (\theta) & \sin (\theta) \\ \sin (\theta) & - \cos (\theta) \end{array} \right]
$$

Relate $\overline { { v } }$ to θ geometrically. 

36. Show how any vector $\overline { { v } } \in \mathcal { R } ^ { n }$ can be transformed to $\overline { { w } } \in \mathcal { R } ^ { n }$ as ${ \overline { { w } } } = c H { \overline { { v } } } .$ , where c is a scalar and H is an $n \times n$ Householder reflection matrix. Think geometrically to solve this exercise. 

37. A block upper-triangular matrix is a generalization of a block diagonal matrix (cf. Section 1.2.3) that allows non-zero entries above the square, diagonal blocks. Consider a block upper-triangular matrix with invertible diagonal blocks. Make an argument why such a matrix is row equivalent to an invertible block diagonal matrix. Generalize the backsubstitution method to solving linear equations of the form $A { \overline { { x } } } = { \overline { { b } } }$ when A is block upper-triangular. You may assume that the diagonal blocks are easily invertible. 

38. If P is a projection matrix, show that $( P + \lambda I )$ is invertible for any $\lambda > 0$ . [Hint: Show that $\overline { { x } } ^ { T } ( P + \lambda I ) \overline { { x } } > 0$ for all x, and therefore $( P + \lambda I ) { \overline { { x } } } \neq 0 . ]$ 

39. If R is a Householder reflection matrix, show that $( R + I )$ is always singular, and that $( R + \lambda I )$ is invertible for any $\lambda \not \in \{ 1 , - 1 \}$ 

40. Length-preserving transforms are orthogonal: We already know that if A is an $n \times n$ orthogonal matrix, then $\| A { \overline { { x } } } \| = \| { \overline { { x } } } \|$ for all $\overline { { x } } \in \mathcal { R } ^ { n }$ . Prove the converse of this result that if $\| A { \overline { { x } } } \| = \| { \overline { { x } } } \|$ for all $\overline { { x } } \in \mathcal { R } ^ { n }$ , then A is orthogonal. 

41. Let A be a square $n \times n$ matrix so that $( A + I )$ has rank $( n - 2 )$ . Let $f ( x )$ be the polynomial $f ( x ) = x ^ { 3 } + x ^ { 2 } + x + 1$ . Show that $f ( A )$ has rank at most $( n - 2 )$ Furthermore, show that $f ( A )$ has rank exactly $( n - 2 )$ if A is symmetric. 

42. Suppose that a $d \times d$ matrix A exists along with d vectors $\overline { { x } } _ { 1 } \ldots \overline { { x } } _ { d }$ so that $\overline { { x } } _ { i } ^ { T } A \overline { { x } } _ { j }$ is zero if and only ${ \mathrm { i f ~ } } i \neq j$ . Show that the vectors $\overline { { x } } _ { 1 } \ldots \overline { { x } } _ { d }$ are linearly independent. Note that A need not be symmetric. 

43. Suppose that a $d \times d$ symmetric matrix S exists along with d vectors $\overline { { x } } _ { 1 } \ldots . \overline { { x } } _ { d }$ so that $\overline { { x } } _ { i } ^ { T } { \bar { S } } \overline { { x } } _ { j }$ is zero when $i \neq j$ and positive when $i = j$ . Show that $\langle \overline { { x } } , \overline { { y } } \rangle = \overline { { x } } ^ { T } S \overline { { y } }$ is a valid inner product over all $\overline { { x } } , \overline { { y } } \in \mathcal { R } ^ { d }$ . [Hint: The positive definite axiom is the hard part.] 

44. Cauchy-Schwarz and triangle inequality for general inner products: Let u and v be two vectors for which $\langle \overline { { u } } , \overline { { u } } \rangle = \langle \overline { { v } } , \overline { { v } } \rangle = 1$ . Show using only the inner-product axioms that $| \langle \overline { { u } } , \overline { { v } } \rangle | \leq 1$ . Now show the more general Cauchy-Schwarz inequality by defining u and v appropriately in terms of x and $\textstyle { \overline { { y } } } \colon$ 

$$
| \langle \overline {{x}}, \overline {{y}} \rangle | \leq \sqrt {\langle \overline {{x}} , \overline {{x}} \rangle \langle \overline {{y}} , \overline {{y}} \rangle}
$$

Now use this result (and the inner-product axioms) to prove the triangle inequality for the triangle formed by ${ \overline { { x } } } , { \overline { { y } } } ,$ and the origin: 

$$
\sqrt {\langle \overline {{x}} , \overline {{x}} \rangle} + \sqrt {\langle \overline {{y}} , \overline {{y}} \rangle} \geq \sqrt {\langle \overline {{x}} - \overline {{y}} , \overline {{x}} - \overline {{y}} \rangle}
$$

45. If the matrix computed by the polynomial function $\textstyle f ( A ) = \sum _ { i = 0 } ^ { d } c _ { i } A ^ { i }$ has rank strictly greater than that of A, is there anything you can say about the coefficients $c _ { 0 } \ldots c _ { d } ?$ 

46. Let S be a symmetric matrix and $g ( S ) = S ^ { 3 } - S ^ { 2 } + S$ . Without using the results of the next chapter, show that $g ( S )$ has the same rank as that of S. 

47. Let A be an $n \times m$ matrix and B be a $k \times d$ matrix. Show that the column space of $A X B$ is always a subspace of the column space of A, and the row space of $A X B$ is a subspace of the row space of B for any $m \times k$ matrix X. 

48. Suppose that A is an $n \times m$ matrix and B is a $k \times d$ matrix, both of full rectangular rank. You want to find the $m \times k$ matrix X so that $C = A X B$ , where C is a known $n \times d$ matrix. What should the shapes of each of A and B be (i.e., tall or wide) for the system of equations to be guaranteed to be consistent? Derive a closed-form expression for one solution, X, in terms of A, B, and C in this case. When is this solution unique? 

49. Suppose that A is an $n \times m$ matrix and B is a $k \times d$ matrix, both of full rectangular rank. A is tall and B is wide. The system of equations $C = A X B$ is inconsistent. You want to find the best-fit m k matrix X so that $\| C - A X B \| _ { F } ^ { 2 }$ is as small as possible, where $C$ is a known $n \times d$ matrix. So you model $Y \approx X B$ , and first fix $Y$ to the best-fit solution to $\| C - A Y \| _ { F } ^ { 2 }$ . Then, you find the best-fit solution to $\| Y - X B \| _ { F } ^ { 2 }$ for fixed Y. Use the normal equations to derive closed-form expressions for $X$ and $Y$ Show that the closed-form solution for X and the best-fit $C ^ { \prime }$ to $C$ are as follows: 

$$
X = \underbrace {(A ^ {T} A) ^ {- 1} A ^ {T}} _ {\text {Left Inverse}} C \underbrace {B ^ {T} (B B ^ {T}) ^ {- 1}} _ {\text {Right inverse}}, \quad C ^ {\prime} = \underbrace {A (A ^ {T} A) ^ {- 1} A ^ {T}} _ {\text {Project columns}} C \underbrace {B ^ {T} (B B ^ {T}) ^ {- 1} B} _ {\text {Project rows}}
$$

[Note: Sequential optimization of variables (like Y and X) is suboptimal in general, but it works in this case.] 

50. Challenge Problem: Let A be an $n \times m$ matrix and B be a $k \times d$ matrix. You want to find the $m \times k$ matrix X so that $C = A X B$ , where C is a known $n \times d$ matrix. Nothing is known about the linear independence of rows or columns of $A , B ,$ , and C. Propose a variation of the Gaussian elimination method to solve the system of equations $C =$ $A X B$ . How can you recognize inconsistent systems of equations or systems with an infinite number of solutions? [Note: Closed-form solution in Exercise 23 of Chapter 4.] 

51. Use the limit-based definition of the Moore-Penrose pseudoinverse to show that $A ^ { T } A A ^ { + } = A ^ { T }$ and $B ^ { + } B B ^ { T } = B ^ { T }$ . [Note: Proofs based on $\mathrm { Q R / S V D }$ are simple.] 

52. We know that the best-fit solution to $A { \overline { { x } } } = { \overline { { b } } }$ is given by ${ \overline { { x } } } ^ { * } = A ^ { + } { \overline { { b } } } .$ . For inconsistent systems, we have $A { \overline { { x } } } ^ { * } = A A ^ { + } { \overline { { b } } } \neq { \overline { { b } } }$ . Use the limit-based definition of $A ^ { + }$ to show that the matrix $A A ^ { + }$ is both symmetric and idempotent (which is an alternative definition of a projection matrix). What type of projection does $A A ^ { + }$ perform here?

[^field-axioms]: The field axioms are the properties of associativity, commutativity, distributivity, identity, and inverses. For example, real numbers, complex numbers, and rational numbers form a field. However, integers do not form a field. Refer to [Field](http://mathworld.wolfram.com/Field.html). Therefore, one can define vectors over the set of real numbers, complex numbers, or rational numbers. Although one can define vectors more restrictively over the set of integers, such vectors will not satisfy some fundamental rules of linear algebra required for them to be considered a vector space.
