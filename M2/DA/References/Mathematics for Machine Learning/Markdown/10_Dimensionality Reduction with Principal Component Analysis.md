## Dimensionality Reduction with Principal Component Analysis

Working directly with high-dimensional data, such as images, comes with some difficulties: It is hard to analyze, interpretation is difficult, visualization is nearly impossible, and (from a practical point of view) storage of the data vectors can be expensive. However, high-dimensional data often has properties that we can exploit. For example, high-dimensional data is often overcomplete, i.e., many dimensions are redundant and can be ex plained by a combination of other dimensions. Furthermore, dimensions in high-dimensional data are often correlated so that the data possesses an intrinsic lower-dimensional structure. Dimensionality reduction exploits structure and correlation and allows us to work with a more compact representation of the data, ideally without losing information. We can think of dimensionality reduction as a compression technique, similar to jpeg or mp3, which are compression algorithms for images and music. 

In this chapter, we will discuss principal component analysis (PCA), an algorithm for linear dimensionality reduction. PCA, proposed by Pearson (1901) and Hotelling (1933), has been around for more than 100 years and is still one of the most commonly used techniques for data compression and data visualization. It is also used for the identification of simple patterns, latent factors, and structures of high-dimensional data. In the 

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_001.jpg>)



(a) Dataset with x and x coordinates.


![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_002.jpg>)



(b) Compressed dataset where only the x coordinate is relevant.


![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_003.jpg>)



A 640 × 480 pixel color image is a data point in a million-dimensiona space, where every pixel responds to three dimensions, one for each color channel (red, green, blue).


Figure 10.1 Illustration: dimensionality reduction. (a) The original dataset does not vary much along the x direction. (b) The data from (a) can be represented using the x -coordinate alone with nearly no loss. 

signal processing community, PCA is also known as the Karhunen-Lo`eve transform. In this chapter, we derive PCA from first principles, drawing on our understanding of basis and basis change (Sections 2.6.1 and 2.7.2), projections (Section 3.8), eigenvalues (Section 4.2), Gaussian distributions (Section 6.5), and constrained optimization (Section 7.2). 

Dimensionality reduction generally exploits a property of high-dimensional data (e.g., images) that it often lies on a low-dimensional subspace. Figure 10.1 gives an illustrative example in two dimensions. Although the data in Figure 10.1(a) does not quite lie on a line, the data does not vary much in the x -direction, so that we can express it as if it were on a line – with nearly no loss; see Figure 10.1(b). To describe the data in Figure 10.1(b), only the $x _ { 1 }$ -coordinate is required, and the data lies in a one-dimensional subspace of $\mathbb { R } ^ { 2 }$ 

## 10.1 Problem Setting

In PCA, we are interested in finding projections $\scriptstyle { \tilde { \mathbf { x } } } _ { n }$ of data points ${ \bf { x } } _ { n }$ that are as similar to the original data points as possible, but which have a significantly lower intrinsic dimensionality. Figure 10.1 gives an illustration of what this could look like. 

More concretely, we consider an i.i.d. dataset ${ \mathcal { X } } = \{ { \pmb x } _ { 1 } , \ldots , { \pmb x } _ { N } \} , { \pmb x } _ { n } \in$ $\mathbb { R } ^ { D }$ , with mean 0 that possesses the data covariance matrix (6.42) 

$$
\boldsymbol {S} = \frac {1}{N} \sum_ {n = 1} ^ {N} \boldsymbol {x} _ {n} \boldsymbol {x} _ {n} ^ {\top}.\tag{10.1}
$$

Furthermore, we assume there exists a low-dimensional compressed representation (code) 

$$
\pmb {z} _ {n} = \pmb {B} ^ {\top} \pmb {x} _ {n} \in \mathbb {R} ^ {M}\tag{10.2}
$$

of ${ \pmb x } _ { n }$ , where we define the projection matrix 

$$
\boldsymbol {B} := \left[ \boldsymbol {b} _ {1}, \dots , \boldsymbol {b} _ {M} \right] \in \mathbb {R} ^ {D \times M}.\tag{10.3}
$$

We assume that the columns of B are orthonormal (Definition 3.7) so that $\pmb { b } _ { i } ^ { \top } \pmb { b } _ { j } = 0$ if and only if $i \neq j$ and $\pmb { b } _ { i } ^ { \top } \pmb { b } _ { i } = 1$ . We seek an M-dimensional subspace $U \subseteq \mathbb { R } ^ { D } , \mathrm { d i m } ( U ) = M < \dot { D }$ onto which we project the data. We denote the projected data by $\tilde { \pmb { x } } _ { n } \in U$ , and their coordinates (with respect to the basis vectors $b _ { 1 } , \dots , b _ { M }$ of U) by $z _ { n }$ . Our aim is to find projections $\tilde { \pmb { x } } _ { n } \in \mathbb { R } ^ { D }$ (or equivalently the codes $z _ { n }$ and the basis vectors $b _ { 1 } , \dotsc , - b _ { M } )$ so that they are as similar to the original data ${ \bf { x } } _ { n }$ and minimize the loss due to compression. 

## Example 10.1 (Coordinate Representation/Code)

Consider $\mathbb { R } ^ { 2 }$ with the canonical basis $\mathbf { e } _ { 1 } = [ 1 , 0 ] ^ { \top } , \mathbf { e } _ { 2 } = [ 0 , 1 ] ^ { \top }$ . From 

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_004.jpg>)



Figure 10.2 Graphical illustration of PCA. In PCA, we find a compressed version z of original data x The compressed data can be reconstructed into x˜, which lives in the original data space, but has an intrinsic lower-dimensional representation than x.


Chapter 2, we know that $\pmb { x } \in \mathbb { R } ^ { 2 }$ can be represented as a linear combination of these basis vectors, e.g., 

$$
\left[ \begin{array}{c} 5 \\ 3 \end{array} \right] = 5 e _ {1} + 3 e _ {2}.\tag{10.4}
$$

However, when we consider vectors of the form 

$$
\tilde {\boldsymbol {x}} = \left[ \begin{array}{c} 0 \\ z \end{array} \right] \in \mathbb {R} ^ {2}, \quad z \in \mathbb {R},\tag{10.5}
$$

they can always be written as $0 e _ { 1 } + z e _ { 2 }$ . To represent these vectors it is sufficient to remember/store the coordinate/code z of x˜ with respect to the $e _ { 2 }$ vector. 

More precisely, the set of x˜ vectors (with the standard vector addition and scalar multiplication) forms a vector subspace U (see Section 2.4) with dim $( U ) = 1$ because $U = \mathrm { s p a n } [ e _ { 2 } ]$ 

In Section 10.2, we will find low-dimensional representations that retain as much information as possible and minimize the compression loss. An alternative derivation of PCA is given in Section 10.3, where we will be looking at minimizing the squared reconstruction error $\| \pmb { x } _ { n } - \tilde { \pmb { x } } _ { n } \| ^ { 2 }$ between the original data ${ \bf { x } } _ { n }$ and its projection ${ \tilde { \mathbf { x } } } _ { n }$ 

Figure 10.2 illustrates the setting we consider in PCA, where z represents the lower-dimensional representation of the compressed data x˜ and plays the role of a bottleneck, which controls how much information can flow between x and x˜. In PCA, we consider a linear relationship between the original data x and its low-dimensional code z so that $z = B ^ { \intercal }$ x and $\tilde { \boldsymbol { x } } = B \boldsymbol { z }$ for a suitable matrix B. Based on the motivation of thinking of PCA as a data compression technique, we can interpret the arrows in Figure 10.2 as a pair of operations representing encoders and decoders. The linear mapping represented by B can be thought of as a decoder, which maps the low-dimensional code $\boldsymbol { z } \in \mathbb { R } ^ { M }$ back into the original data space $\mathbb { R } ^ { D }$ . Similarly, $B ^ { \top }$ can be thought of an encoder, which encodes the original data x as a low-dimensional (compressed) code z. 

Throughout this chapter, we will use the MNIST digits dataset as a re-

## 0123956389

occurring example, which contains 60,000 examples of handwritten digits 0 through 9. Each digit is a grayscale image of size 28 28, i.e., it contains 784 pixels so that we can interpret every image in this dataset as a vector $\pmb { x } \in \mathbb { R } ^ { 7 8 4 }$ . Examples of these digits are shown in Figure 10.3. 

## 10.2 Maximum Variance Perspective

Figure 10.1 gave an example of how a two-dimensional dataset can be represented using a single coordinate. In Figure 10.1(b), we chose to ignore the $x _ { 2 } .$ -coordinate of the data because it did not add too much information so that the compressed data is similar to the original data in Figure 10.1(a). We could have chosen to ignore the $x _ { 1 }$ -coordinate, but then the compressed data had been very dissimilar from the original data, and much information in the data would have been lost. 

If we interpret information content in the data as how “space filling” the dataset is, then we can describe the information contained in the data by looking at the spread of the data. From Section 6.4.1, we know that the variance is an indicator of the spread of the data, and we can derive PCA as a dimensionality reduction algorithm that maximizes the variance in the low-dimensional representation of the data to retain as much information as possible. Figure 10.4 illustrates this. 

Considering the setting discussed in Section 10.1, our aim is to find a matrix B (see (10.3)) that retains as much information as possible when compressing data by projecting it onto the subspace spanned by the columns $b _ { 1 } , \dots , b _ { M }$ of B. Retaining most information after data compression is equivalent to capturing the largest amount of variance in the low-dimensional code (Hotelling, 1933). 

Remark. (Centered Data) For the data covariance matrix in (10.1), we assumed centered data. We can make this assumption without loss of generality: Let us assume that $\pmb { \mu }$ is the mean of the data. Using the properties of the variance, which we discussed in Section 6.4.4, we obtain 

$$
\mathbb {V} _ {\boldsymbol {z}} [ \boldsymbol {z} ] = \mathbb {V} _ {\boldsymbol {x}} [ \boldsymbol {B} ^ {\top} (\boldsymbol {x} - \boldsymbol {\mu}) ] = \mathbb {V} _ {\boldsymbol {x}} [ \boldsymbol {B} ^ {\top} \boldsymbol {x} - \boldsymbol {B} ^ {\top} \boldsymbol {\mu} ] = \mathbb {V} _ {\boldsymbol {x}} [ \boldsymbol {B} ^ {\top} \boldsymbol {x} ],\tag{10.6}
$$

i.e., the variance of the low-dimensional code does not depend on the mean of the data. Therefore, we assume without loss of generality that the data has mean 0 for the remainder of this section. With this assumption the mean of the low-dimensional code is also 0 since $\begin{array} { r } { \mathbb { E } _ { z } [ z ] = \mathbb { E } _ { x } [ B ^ { \top } x ] = } \end{array}$ $\boldsymbol { B } ^ { \intercal } \mathbb { E } _ { \boldsymbol { x } } [ \boldsymbol { x } ] = \mathbf { 0 }$ ◇ 

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_005.jpg>)



Figure 10.4 PCA finds a lower-dimensional subspace (line) that maintains as much variance (spread of the data) as possible when the data (blue) is projected onto this subspace (orange).


10.2.1 Direction with Maximal Variance 

We maximize the variance of the low-dimensional code using a sequential approach. We start by seeking a single vector $\pmb { b } _ { 1 } \in \mathbb { R } ^ { D }$ that maximizes the variance of the projected data, i.e., we aim to maximize the variance of the first coordinate $z _ { 1 }$ of $\boldsymbol { z } \in \mathbb { R } ^ { M }$ so that 

$$
V _ {1} := \mathbb {V} [ z _ {1} ] = \frac {1}{N} \sum_ {n = 1} ^ {N} z _ {1 n} ^ {2}\tag{10.7}
$$

is maximized, where we exploited the i.i.d. assumption of the data and defined $z _ { 1 n }$ as the first coordinate of the low-dimensional representation $\pmb { z } _ { n } \in \mathbb { R } ^ { M }$ of ${ \pmb x } _ { n } \in \mathbb { R } ^ { D }$ . Note that first component of $z _ { n }$ is given by 

$$
\boldsymbol {z} _ {1 n} = \boldsymbol {b} _ {1} ^ {\top} \boldsymbol {x} _ {n},\tag{10.8}
$$

i.e., it is the coordinate of the orthogonal projection of ${ \bf { x } } _ { n }$ onto the onedimensional subspace spanned by $b _ { 1 }$ (Section 3.8). We substitute (10.8) into (10.7), which yields 

$$
\begin{array}{l} V _ {1} = \frac {1}{N} \sum_ {n = 1} ^ {N} (\boldsymbol {b} _ {1} ^ {\top} \boldsymbol {x} _ {n}) ^ {2} = \frac {1}{N} \sum_ {n = 1} ^ {N} \boldsymbol {b} _ {1} ^ {\top} \boldsymbol {x} _ {n} \boldsymbol {x} _ {n} ^ {\top} \boldsymbol {b} _ {1} \\ = \boldsymbol {b} _ {1} ^ {\top} \left(\frac {1}{N} \sum_ {n = 1} ^ {N} \boldsymbol {x} _ {n} \boldsymbol {x} _ {n} ^ {\top}\right) \boldsymbol {b} _ {1} = \boldsymbol {b} _ {1} ^ {\top} \boldsymbol {S b} _ {1}, \end{array}\tag{10.9a}
$$

(10.9b) 

where $\pmb { S }$ is the data covariance matrix defined in (10.1). In (10.9a), we have used the fact that the dot product of two vectors is symmetric with respect to its arguments, that is, $\bar { \pmb { b } } _ { 1 } ^ { \top } \pmb { x } _ { n } = \pmb { x } _ { n } ^ { \top } \pmb { b } _ { 1 }$ 

Notice that arbitrarily increasing the magnitude of the vector $b _ { 1 }$ increases $V _ { 1 }$ , that is, a vector $b _ { 1 }$ that is two times longer can result in $V _ { 1 }$ that is potentially four times larger. Therefore, we restrict all solutions to $\left. \boldsymbol { b } _ { 1 } \right. ^ { 2 } \bar { = } 1$ , which results in a constrained optimization problem in which we seek the direction along which the data varies most. 

With the restriction of the solution space to unit vectors the vector $b _ { 1 }$ that points in the direction of maximum variance can be found by the 

principal component 

constrained optimization problem 

$$
\begin{array}{l} \underset {\boldsymbol {b} _ {1}} {\max} \boldsymbol {b} _ {1} ^ {\top} \boldsymbol {S} \boldsymbol {b} _ {1} \\ \text {subject to} \| \boldsymbol {b} _ {1} \| ^ {2} = 1. \end{array}\tag{10.10}
$$

Following Section 7.2, we obtain the Lagrangian 

$$
\mathfrak {L} (\boldsymbol {b} _ {1}, \lambda) = \boldsymbol {b} _ {1} ^ {\top} \boldsymbol {S} \boldsymbol {b} _ {1} + \lambda_ {1} (1 - \boldsymbol {b} _ {1} ^ {\top} \boldsymbol {b} _ {1})\tag{10.11}
$$

to solve this constrained optimization problem. The partial derivatives of L with respect to $b _ { 1 }$ and $\lambda _ { 1 }$ are 

$$
\frac {\partial \mathfrak {L}}{\partial \boldsymbol {b} _ {1}} = 2 \boldsymbol {b} _ {1} ^ {\top} \boldsymbol {S} - 2 \lambda_ {1} \boldsymbol {b} _ {1} ^ {\top}, \quad \frac {\partial \mathfrak {L}}{\partial \lambda_ {1}} = 1 - \boldsymbol {b} _ {1} ^ {\top} \boldsymbol {b} _ {1},\tag{10.12}
$$

respectively. Setting these partial derivatives to 0 gives us the relations 

$$
\boldsymbol {S} \boldsymbol {b} _ {1} = \lambda_ {1} \boldsymbol {b} _ {1},\tag{10.13}
$$

$$
\boldsymbol {b} _ {1} ^ {\top} \boldsymbol {b} _ {1} = 1.\tag{10.14}
$$

By comparing this with the definition of an eigenvalue decomposition (Section 4.4), we see that $b _ { 1 }$ is an eigenvector of the data covariance matrix ${ \cal S } ,$ and the Lagrange multiplier $\lambda _ { 1 }$ plays the role of the corresponding eigenvalue. This eigenvector property (10.13) allows us to rewrite our variance objective (10.10) as 

$$
V _ {1} = \boldsymbol {b} _ {1} ^ {\top} \boldsymbol {S} \boldsymbol {b} _ {1} = \lambda_ {1} \boldsymbol {b} _ {1} ^ {\top} \boldsymbol {b} _ {1} = \lambda_ {1},\tag{10.15}
$$

i.e., the variance of the data projected onto a one-dimensional subspace equals the eigenvalue that is associated with the basis vector $b _ { 1 }$ that spans this subspace. Therefore, to maximize the variance of the low-dimensional code, we choose the basis vector associated with the largest eigenvalue of the data covariance matrix. This eigenvector is called the first principa component. We can determine the effect/contribution of the principal component $b _ { 1 }$ in the original data space by mapping the coordinate $z _ { 1 n }$ back into data space, which gives us the projected data point 

$$
\tilde {\pmb {x}} _ {n} = \pmb {b} _ {1} z _ {1 n} = \pmb {b} _ {1} \pmb {b} _ {1} ^ {\top} \pmb {x} _ {n} \in \mathbb {R} ^ {D}\tag{10.16}
$$

in the original data space. 

Remark. Although $\tilde { \mathbf { x } } _ { n }$ is a D-dimensional vector, it only requires a single coordinate $z _ { 1 n }$ to represent it with respect to the basis vector $\pmb { b } _ { 1 } \in \mathbb { R } ^ { D }$ . 

## 10.2.2 M-dimensional Subspace with Maximal Variance

Assume we have found the first $m - 1$ principal components as the $m - 1$ eigenvectors of S that are associated with the largest m 1 eigenvalues. Since S is symmetric, the spectral theorem (Theorem 4.15) states that we can use these eigenvectors to construct an orthonormal eigenbasis of an $( m - 1 )$ )-dimensional subspace of $\mathbb { R } ^ { D }$ . Generally, the mth principal component can be found by subtracting the effect of the first $m - 1$ principal components $b _ { 1 } , \ldots , b _ { m - 1 }$ from the data, thereby trying to find principal components that compress the remaining information. We then arrive at the new data matrix 

$$
\hat {\boldsymbol {X}} := \boldsymbol {X} - \sum_ {i = 1} ^ {m - 1} \boldsymbol {b} _ {i} \boldsymbol {b} _ {i} ^ {\top} \boldsymbol {X} = \boldsymbol {X} - \boldsymbol {B} _ {m - 1} \boldsymbol {X},\tag{10.17}
$$

where $\pmb { X } = [ \pmb { x } _ { 1 } , \dots , \pmb { x } _ { N } ] \in \mathbb { R } ^ { D \times N }$ contains the data points as column vectors and $\begin{array} { r } { \pmb { { B } } _ { m - 1 } : = \sum _ { i = 1 } ^ { m - 1 } \pmb { b } _ { i } \pmb { b } _ { i } ^ { \top } } \end{array}$ is a projection matrix that projects onto the subspace spanned by $b _ { 1 } , \ldots , b _ { m - 1 }$ 

Remark (Notation). Throughout this chapter, we do not follow the convention of collecting data $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { N }$ as the rows of the data matrix, but we define them to be the columns of $\boldsymbol { X }$ . This means that our data matrix X is a $D \times N$ matrix instead of the conventional $N \times D$ matrix. The reason for our choice is that the algebra operations work out smoothly without the need to either transpose the matrix or to redefine vectors as row vectors that are left-multiplied onto matrices. 

To find the mth principal component, we maximize the variance 

$$
V _ {m} = \mathbb {V} [ z _ {m} ] = \frac {1}{N} \sum_ {n = 1} ^ {N} z _ {m n} ^ {2} = \frac {1}{N} \sum_ {n = 1} ^ {N} (\pmb {b} _ {m} ^ {\top} \pmb {\hat {x}} _ {n}) ^ {2} = \pmb {b} _ {m} ^ {\top} \hat {\pmb {S}} \pmb {b} _ {m},\tag{10.18}
$$

subject to $\left\| \pmb { b } _ { m } \right\| ^ { 2 } = 1$ , where we followed the same steps as in (10.9b) and defined S<sup>ˆ</sup> as the data covariance matrix of the transformed dataset $\hat { \mathcal X } : = \{ \hat { \pmb x } _ { 1 } , \hdots , \hat { \pmb x } _ { N } \}$ . As previously, when we looked at the first principal component alone, we solve a constrained optimization problem and discover that the optimal solution $b _ { m }$ is the eigenvector of $\hat { \boldsymbol { S } }$ that is associated with the largest eigenvalue of $\hat { S }$ . 

It turns out that $b _ { m }$ is also an eigenvector of $S .$ . More generally, the sets of eigenvectors of $_ { s }$ and $\hat { \boldsymbol S }$ are identical. Since both S and $\hat { \boldsymbol { S } }$ are symmetric, we can find an ONB of eigenvectors (spectral theorem 4.15), i.e., there exist $D$ distinct eigenvectors for both $_ { s }$ and $\hat { \boldsymbol { S } } .$ . Next, we show that every eigenvector of S is an eigenvector of $\hat { \boldsymbol { S } } .$ . Assume we have already found eigenvectors $b _ { 1 } , \ldots , b _ { m - 1 }$ of $\hat { \boldsymbol { S } } .$ . Consider an eigenvector $\mathbf { } _ { b _ { i } }$ of $S _ { z }$ i.e., $S b _ { i } = \lambda _ { i } \pmb { b } _ { i }$ . In general, 

$$
\hat {\boldsymbol {S}} \boldsymbol {b} _ {i} = \frac {1}{N} \hat {\boldsymbol {X}} \hat {\boldsymbol {X}} ^ {\top} \boldsymbol {b} _ {i} = \frac {1}{N} (\boldsymbol {X} - \boldsymbol {B} _ {m - 1} \boldsymbol {X}) (\boldsymbol {X} - \boldsymbol {B} _ {m - 1} \boldsymbol {X}) ^ {\top} \boldsymbol {b} _ {i}\tag{10.19a}
$$

$$
= \left(\boldsymbol {S} - \boldsymbol {S} \boldsymbol {B} _ {m - 1} - \boldsymbol {B} _ {m - 1} \boldsymbol {S} + \boldsymbol {B} _ {m - 1} \boldsymbol {S} \boldsymbol {B} _ {m - 1}\right) \boldsymbol {b} _ {i}.\tag{10.19b}
$$

We distinguish between two cases. $\mathrm { I f } ~ i ~ \geqslant ~ m , ~ \mathrm { i . e . , } ~ b _ { i }$ is an eigenvector that is not among the first $m - 1$ principal components, then $b _ { i }$ is orthogonal to the first $m - 1$ principal components and $B _ { m - 1 } b _ { i } = 0 . { \mathrm { I f } } i < m , { \mathrm { i . e . } } ,$ $\mathbf { } _ { b _ { i } }$ is among the first $m - 1$ principal components, then $\mathbf { } _ { b _ { i } }$ is a basis vector of the principal subspace onto which $B _ { m - 1 }$ projects. Since $b _ { 1 } , \ldots , b _ { m - 1 }$ are an ONB of this principal subspace, we obtain $B _ { m - 1 } \pmb { b } _ { i } = \pmb { b } _ { i }$ . The two cases can be summarized as follows: 

$$
\boldsymbol {B} _ {m - 1} \boldsymbol {b} _ {i} = \boldsymbol {b} _ {i} \quad \text {if} i <   m, \qquad \boldsymbol {B} _ {m - 1} \boldsymbol {b} _ {i} = \mathbf {0} \quad \text {if} i \geqslant m.\tag{10.20}
$$

In the case $i \geqslant m ,$ by using (10.20) in (10.19b), we obtain $\hat { S } b _ { i } = ( S -$ $B _ { m - 1 } { \cal S } ) b _ { i } = { \cal S } b _ { i } = \lambda _ { i } b _ { i }$ , i.e., b is also an eigenvector of $\hat { \boldsymbol { S } }$ with eigenvalue $\lambda _ { i }$ . Specifically, 

$$
\hat {\pmb {S}} \pmb {b} _ {m} = \pmb {S} \pmb {b} _ {m} = \lambda_ {m} \pmb {b} _ {m}.\tag{10.21}
$$

Equation (10.21) reveals that $b _ { m }$ is not only an eigenvector of S but also of $\hat { \boldsymbol { S } } .$ . Specifically, $\lambda _ { m }$ is the largest eigenvalue of $\hat { \boldsymbol { S } }$ and $\lambda _ { m }$ is the mth largest eigenvalue of S, and both have the associated eigenvector $b _ { m }$ 

In the case $i < m ,$ by using (10.20) in (10.19b), we obtain 

$$
\hat {\boldsymbol {S}} \boldsymbol {b} _ {i} = (\boldsymbol {S} - \boldsymbol {S} \boldsymbol {B} _ {m - 1} - \boldsymbol {B} _ {m - 1} \boldsymbol {S} + \boldsymbol {B} _ {m - 1} \boldsymbol {S} \boldsymbol {B} _ {m - 1}) \boldsymbol {b} _ {i} = \boldsymbol {0} = 0 \boldsymbol {b} _ {i}\tag{10.22}
$$

This means that $b _ { 1 } , \dotsc , b _ { m - 1 }$ are also eigenvectors of $\hat { \cal S } ,$ , but they are associated with eigenvalue 0 so that $b _ { 1 } , \dotsc , b _ { m - 1 }$ span the null space of $\hat { \boldsymbol S }$ . 

Overall, every eigenvector of S is also an eigenvector of $\hat { \boldsymbol { S } } .$ . However, if the eigenvectors of S are part of the $( m - 1 )$ dimensional principal subspace, then the associated eigenvalue of $\hat { \boldsymbol { S } }$ is 0. 

With the relation (10.21) and $\pmb { b } _ { m } ^ { \top } \pmb { b } _ { m } = 1$ , the variance of the data projected onto the mth principal component is 

$$
V _ {m} = \boldsymbol {b} _ {m} ^ {\top} \boldsymbol {S} \boldsymbol {b} _ {m} \stackrel {(1 0. 2 1)} {=} \lambda_ {m} \boldsymbol {b} _ {m} ^ {\top} \boldsymbol {b} _ {m} = \lambda_ {m}.\tag{10.23}
$$

This means that the variance of the data, when projected onto an $M -$ dimensional subspace, equals the sum of the eigenvalues that are associated with the corresponding eigenvectors of the data covariance matrix. 

## Example 10.2 (Eigenvalues of MNIST “8”)

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_006.jpg>)



(a) Eigenvalues (sorted in descending order) of the data covariance matrix of all digits $\mathbf { \boldsymbol { \mathfrak { s } } } ^ { \flat }$ in the MNIST training set.


![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_007.jpg>)



(b) Variance captured by the principal components.


![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_008.jpg>)



Figure 10.6 Illustration of the projection approach: Find a subspace (line) that minimizes the length of the difference vector between projected (orange) and original (blue) data.


Taking all digits $" 8 "$ in the MNIST training data, we compute the eigenvalues of the data covariance matrix. Figure 10.5(a) shows the 200 largest eigenvalues of the data covariance matrix. We see that only a few of them have a value that differs significantly from 0. Therefore, most of the variance, when projecting data onto the subspace spanned by the corresponding eigenvectors, is captured by only a few principal components, as shown in Figure 10.5(b). 

Overall, to find an M-dimensional subspace of $\mathbb { R } ^ { D }$ that retains as much information as possible, PCA tells us to choose the columns of the matrix B in (10.3) as the M eigenvectors of the data covariance matrix S that are associated with the M largest eigenvalues. The maximum amount of variance PCA can capture with the first M principal components is 

$$
V _ {M} = \sum_ {m = 1} ^ {M} \lambda_ {m},\tag{10.24}
$$

where the $\lambda _ { m }$ are the M largest eigenvalues of the data covariance matrix S. Consequently, the variance lost by data compression via PCA is 

$$
J _ {M} := \sum_ {j = M + 1} ^ {D} \lambda_ {j} = V _ {D} - V _ {M}.\tag{10.25}
$$

Instead of these absolute quantities, we can define the relative variance captured as $\frac { V _ { M } } { V _ { D } }$ , and the relative variance lost by compression as $\begin{array} { r } { 1 - \frac { V _ { M } } { V _ { D } } } \end{array}$ 

## 10.3 Projection Perspective

In the following, we will derive PCA as an algorithm that directly minimizes the average reconstruction error. This perspective allows us to interpret PCA as implementing an optimal linear auto-encoder. We will draw heavily from Chapters 2 and 3. 

In the previous section, we derived PCA by maximizing the variance in the projected space to retain as much information as possible. In the 

Figure 10.7 Simplified projection setting. (a) A vector x $\mathbf { \Lambda } \in \mathbb { R } ^ { 2 }$ (red cross) shall be projected onto a one-dimensional subspace $U \subseteq \mathbb { R } ^ { 2 }$ spanned by b. (b) shows the difference vectors between x and some candidates x˜. 

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_009.jpg>)



(a) Setting.


![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_010.jpg>)



(b) Differences $\mathbf { x } - \tilde { \mathbf { x } } _ { i }$ for 50 different $\tilde { \mathbf { x } } _ { i }$ are shown by the red lines.



Vectors $\tilde { \mathbf { r } } \in U$ could be vectors on a plane in $\mathbb { R } ^ { 3 } .$ . The dimensionality of the plane is 2, but the vectors still have three coordinates with respect to the standard basis of $\mathbb { R } ^ { 3 }$


following, we will look at the difference vectors between the original data ${ \bf { x } } _ { n }$ and their reconstruction $\scriptstyle { \tilde { \mathbf { x } } } _ { n }$ and minimize this distance so that ${ \bf { x } } _ { n }$ and $\scriptstyle { \tilde { \mathbf { x } } } _ { n }$ are as close as possible. Figure 10.6 illustrates this setting. 

## 10.3.1 Setting and Objective

Assume an (ordered) orthonormal basis (ONB) $B = ( b _ { 1 } , \ldots , b _ { D } )$ of $\mathbb { R } ^ { D }$ i.e., $\pmb { b } _ { i } ^ { \top } \pmb { b } _ { j } = 1$ if and only if $i = j$ and 0 otherwise. 

From Section 2.5 we know that for a basis $\left( b _ { 1 } , \ldots , b _ { D } \right)$ of $\mathbb { R } ^ { D }$ any ${ \pmb x } \in$ $\mathbb { R } ^ { D }$ can be written as a linear combination of the basis vectors of R<sup>D</sup>, i.e., 

$$
\boldsymbol {x} = \sum_ {d = 1} ^ {D} \zeta_ {d} \boldsymbol {b} _ {d} = \sum_ {m = 1} ^ {M} \zeta_ {m} \boldsymbol {b} _ {m} + \sum_ {j = M + 1} ^ {D} \zeta_ {j} \boldsymbol {b} _ {j}\tag{10.26}
$$

for suitable coordinates $\zeta _ { d } \in \mathbb { R } .$ 

We are interested in finding vectors $\tilde { \textbf { \textit { x } } } \in \ \mathbb { R } ^ { D }$ , which live in lowerdimensional subspace $U \subseteq \mathbb { R } ^ { D }$ , dim $( U ) = M$ , so that 

$$
\tilde {\boldsymbol {x}} = \sum_ {m = 1} ^ {M} z _ {m} \boldsymbol {b} _ {m} \in U \subseteq \mathbb {R} ^ {D}\tag{10.27}
$$

is as similar to x as possible. Note that at this point we need to assume that the coordinates $z _ { m }$ of x˜ and $\zeta _ { m }$ of x are not identical. 

In the following, we use exactly this kind of representation of x˜ to find optimal coordinates z and basis vectors $b _ { 1 } , \dots , b _ { M }$ such that x˜ is as similar to the original data point x as possible, i.e., we aim to minimize the (Euclidean) distance $\lVert x - \tilde { { \boldsymbol { x } } } \rVert$ . Figure 10.7 illustrates this setting. 

Without loss of generality, we assume that the dataset ${ \mathcal { X } } = \{ { \pmb x } _ { 1 } , \ldots , { \pmb x } _ { N } \}$ , ${ \pmb x } _ { n } \in \mathbb { R } ^ { D }$ , is centered at $\mathbf { 0 } , \mathrm { i . e . , } \mathbb { E } [ \mathcal { X } ] = \mathbf { 0 }$ . Without the zero-mean assumption, we would arrive at exactly the same solution, but the notation would be substantially more cluttered. 

We are interested in finding the best linear projection of $\mathcal { X }$ onto a lowerdimensional subspace U of $\bar { \mathbb { R } } ^ { D }$ with dim $( U ) = M$ and orthonormal basis vectors $b _ { 1 } , \dots , b _ { M }$ . We will call this subspace U the principal subspace. The projections of the data points are denoted by 

$$
\tilde {\boldsymbol {x}} _ {n} := \sum_ {m = 1} ^ {M} z _ {m n} \boldsymbol {b} _ {m} = \boldsymbol {B} \boldsymbol {z} _ {n} \in \mathbb {R} ^ {D},\tag{10.28}
$$

where $z _ { n } : = [ z _ { 1 n } , \ldots , z _ { M n } ] ^ { \top } \in \mathbb { R } ^ { M }$ is the coordinate vector of ${ \tilde { \mathbf { x } } } _ { n }$ with respect to the basis $\left( \pmb { b } _ { 1 } , \dots , \pmb { b } _ { M } \right)$ . More specifically, we are interested in having the $\scriptstyle { \tilde { \mathbf { x } } } _ { n }$ as similar to ${ \bf { x } } _ { n }$ as possible. 

The similarity measure we use in the following is the squared distance (Euclidean norm) $\| { \pmb x } - { \tilde { { \pmb x } } } \| ^ { 2 }$ between x and x˜. We therefore define our ob jective as minimizing the average squared Euclidean distance (reconstruction reconstruction error error) (Pearson, 1901) 

$$
J _ {M} := \frac {1}{N} \sum_ {n = 1} ^ {N} \left\| \boldsymbol {x} _ {n} - \tilde {\boldsymbol {x}} _ {n} \right\| ^ {2},\tag{10.29}
$$

where we make it explicit that the dimension of the subspace onto which we project the data is $M$ . In order to find this optimal linear projection, we need to find the orthonormal basis of the principal subspace and the coordinates $\boldsymbol { z } _ { n } \in \mathbb { R } ^ { M }$ of the projections with respect to this basis. 

To find the coordinates $z _ { n }$ and the ONB of the principal subspace, we follow a two-step approach. First, we optimize the coordinates $z _ { n }$ for a given ONB $\left( \pmb { b } _ { 1 } , \dots , \pmb { b } _ { M } \right)$ ; second, we find the optimal ONB. 

## 10.3.2 Finding Optimal Coordinates

Let us start by finding the optimal coordinates $z _ { 1 n } , \ldots , z _ { M n }$ of the projections $\scriptstyle { \tilde { \mathbf { x } } } _ { n }$ for $n = 1 , \ldots , N$ . Consider Figure $1 0 . 7 ( \mathrm { b } )$ , where the principal subspace is spanned by a single vector b. Geometrically speaking, finding the optimal coordinates z corresponds to finding the representation of the linear projection x˜ with respect to b that minimizes the distance between $\tilde { \boldsymbol { x } } - \boldsymbol { x }$ . From Figure 10.7(b), it is clear that this will be the orthogonal projection, and in the following we will show exactly this. 

We assume an ONB $\left( \pmb { b } _ { 1 } , \dots , \pmb { b } _ { M } \right)$ of $U \subseteq \mathbb { R } ^ { D }$ . To find the optimal coordinates $z _ { m }$ with respect to this basis, we require the partial derivatives 

$$
\frac {\partial J _ {M}}{\partial z _ {i n}} = \frac {\partial J _ {M}}{\partial \tilde {\pmb {x}} _ {n}} \frac {\partial \tilde {\pmb {x}} _ {n}}{\partial z _ {i n}},\tag{10.30a}
$$

$$
\frac {\partial J _ {M}}{\partial \tilde {\pmb {x}} _ {n}} = - \frac {2}{N} (\pmb {x} _ {n} - \tilde {\pmb {x}} _ {n}) ^ {\top} \in \mathbb {R} ^ {1 \times D},\tag{10.30b}
$$

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

$$
\pmb {x} \in \mathbb {R} ^ {2}
$$

$$
\tilde {\boldsymbol {x}} \in U.
$$

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_011.jpg>)



(a) Distances $\lVert \pmb { x } - \tilde { \pmb { x } } \rVert$ for some ${ \tilde { \pmb { x } } } = z _ { 1 } { \pmb { b } } \in$ U = span[b]; see panel (b) for the setting.


![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_012.jpg>)



(b) The vector x˜ that minimizes the distance in panel (a) is its orthogonal projection onto U. The coordinate of the projection x˜ with respect to the basis vector b that spans U is the factor we need to scale b in order to “reach” x˜.


$$
\frac {\partial \tilde {\boldsymbol {x}} _ {n}}{\partial z _ {i n}} \stackrel {(1 0. 2 8)} {=} \frac {\partial}{\partial z _ {i n}} \left(\sum_ {m = 1} ^ {M} z _ {m n} \boldsymbol {b} _ {m}\right) = \boldsymbol {b} _ {i}\tag{10.30c}
$$

for $i = 1 , \ldots , M _ { \mathrm { { \scriptsize ~ ; ~ } } }$ , such that we obtain 

$$
\frac {\partial J _ {M}}{\partial z _ {i n}} \stackrel {{(1 0. 3 0 \mathrm{b})}} {{=}} - \frac {2}{N} (\boldsymbol {x} _ {n} - \tilde {\boldsymbol {x}} _ {n}) ^ {\top} \boldsymbol {b} _ {i} \stackrel {{(1 0. 2 8)}} {{=}} - \frac {2}{N} \left(\boldsymbol {x} _ {n} - \sum_ {m = 1} ^ {M} z _ {m n} \boldsymbol {b} _ {m}\right) ^ {\top} \boldsymbol {b} _ {i}\tag{10.31a}
$$

$$
\stackrel {\mathrm{ONB}} {=} - \frac {2}{N} (\boldsymbol {x} _ {n} ^ {\top} \boldsymbol {b} _ {i} - z _ {i n} \boldsymbol {b} _ {i} ^ {\top} \boldsymbol {b} _ {i}) = - \frac {2}{N} (\boldsymbol {x} _ {n} ^ {\top} \boldsymbol {b} _ {i} - z _ {i n}).\tag{10.31b}
$$

The coordinates of the optimal projection of x with respect to the basis vectors $b _ { 1 } , \dots , \pmb { b } _ { M }$ are the coordinates of the orthogonal projection of ${ \pmb x } _ { n }$ onto the principal subspace. 

since $b _ { i } ^ { \top } b _ { i } = 1$ . Setting this partial derivative to 0 yields immediately the optimal coordinates 

$$
z _ {i n} = \boldsymbol {x} _ {n} ^ {\top} \boldsymbol {b} _ {i} = \boldsymbol {b} _ {i} ^ {\top} \boldsymbol {x} _ {n}\tag{10.32}
$$

for $i = 1 , \ldots , M$ and $n = 1 , \ldots , N$ . This means that the optimal coordinates $z _ { i n }$ of the projection $\scriptstyle { \tilde { \mathbf { x } } } _ { n }$ are the coordinates of the orthogonal projection (see Section 3.8) of the original data point ${ \bf { x } } _ { n }$ onto the onedimensional subspace that is spanned by $b _ { i }$ . Consequently: 

The optimal linear projection $\scriptstyle { \tilde { \mathbf { x } } } _ { n }$ of ${ \bf { x } } _ { n }$ is an orthogonal projection. 

The coordinates of $\tilde { \mathbf { x } } _ { n }$ with respect to the basis $\left( \pmb { b } _ { 1 } , \dots , \pmb { b } _ { M } \right)$ are the coordinates of the orthogonal projection of ${ \bf { x } } _ { n }$ onto the principal subspace. 

An orthogonal projection is the best linear mapping given the objective (10.29). 

The coordinates $\zeta _ { m }$ of x in (10.26) and the coordinates $z _ { m }$ of x˜ in (10.27) 

must be identical for $m = 1 , \ldots , M$ since $U ^ { \perp } = \operatorname { s p a n } [ { \pmb b } _ { M + 1 } , \ldots , { \pmb b } _ { D } ]$ is the orthogonal complement (see Section $3 . 6 )$ of $U = \operatorname { s p a n } [ \pmb { b } _ { 1 } , \dots , \pmb { b } _ { M } ]$ 

Remark (Orthogonal Projections with Orthonormal Basis Vectors). Let us briefly recap orthogonal projections from Section 3.8. If $\left( b _ { 1 } , \ldots , b _ { D } \right)$ is an orthonormal basis of $\mathbb { R } ^ { D }$ then 

$$
\tilde {\boldsymbol {x}} = \boldsymbol {b} _ {j} (\boldsymbol {b} _ {j} ^ {\top} \boldsymbol {b} _ {j}) ^ {- 1} \boldsymbol {b} _ {j} ^ {\top} \boldsymbol {x} = \boldsymbol {b} _ {j} \boldsymbol {b} _ {j} ^ {\top} \boldsymbol {x} \in \mathbb {R} ^ {D}\tag{10.33}
$$

is the orthogonal projection of x onto the subspace spanned by the jth basis vector, and $z _ { j } = b _ { j } ^ { \intercal }$ x is the coordinate of this projection with respect to the basis vector $b _ { j }$ that spans that subspace since $z _ { j } \pmb { b } _ { j } = \tilde { \pmb { x } }$ . Figure 10.8(b) illustrates this setting. 

More generally, if we aim to project onto an M-dimensional subspace of $\mathbb { R } ^ { D }$ , we obtain the orthogonal projection of x onto the M-dimensional subspace with orthonormal basis vectors $b _ { 1 } , \dots , b _ { M }$ as 

$$
\tilde {\boldsymbol {x}} = \boldsymbol {B} (\underbrace {\boldsymbol {B} ^ {\top} \boldsymbol {B}} _ {= I}) ^ {- 1} \boldsymbol {B} ^ {\top} \boldsymbol {x} = \boldsymbol {B} \boldsymbol {B} ^ {\top} \boldsymbol {x},\tag{10.34}
$$

where we defined $B : = [ \pmb { b } _ { 1 } , \dotsc , \pmb { b } _ { M } ] \in \mathbb { R } ^ { D \times M }$ . The coordinates of this projection with respect to the ordered basis $\left( \pmb { b } _ { 1 } , \dots , \pmb { b } _ { M } \right)$ are $z : = B ^ { \top } x$ as discussed in Section 3.8. 

We can think of the coordinates as a representation of the projected vector in a new coordinate system defined by $\left( \pmb { b } _ { 1 } , \dots , \pmb { b } _ { M } \right)$ . Note that although $\tilde { \textbf { \em x } } \in \ \mathbb { R } ^ { D }$ , we only need M coordinates $z _ { 1 } , \dots , z _ { M }$ to represent this vector; the other $D - M$ coordinates with respect to the basis vectors $\left( { \pmb { b } } _ { M + 1 } , \ldots , { \pmb { b } } _ { D } \right)$ are always 0. 

So far we have shown that for a given ONB we can find the optimal coordinates of x˜ by an orthogonal projection onto the principal subspace. In the following, we will determine what the best basis is. 

## 10.3.3 Finding the Basis of the Principal Subspace

To determine the basis vectors $b _ { 1 } , \dots , b _ { M }$ of the principal subspace, we rephrase the loss function (10.29) using the results we have so far. This will make it easier to find the basis vectors. To reformulate the loss func tion, we exploit our results from before and obtain 

$$
\tilde {\boldsymbol {x}} _ {n} = \sum_ {m = 1} ^ {M} z _ {m n} \boldsymbol {b} _ {m} \stackrel {(1 0. 3 2)} {=} \sum_ {m = 1} ^ {M} (\boldsymbol {x} _ {n} ^ {\top} \boldsymbol {b} _ {m}) \boldsymbol {b} _ {m}.\tag{10.35}
$$

We now exploit the symmetry of the dot product, which yields 

$$
\tilde {\boldsymbol {x}} _ {n} = \left(\sum_ {m = 1} ^ {M} \boldsymbol {b} _ {m} \boldsymbol {b} _ {m} ^ {\top}\right) \boldsymbol {x} _ {n}.\tag{10.36}
$$



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



Figure 10.9 Orthogonal projection and displacement vectors. When projecting data points ${ \pmb x } _ { n }$ (blue) onto subspace $U _ { 1 }$ we obtain $\scriptstyle { \tilde { \mathbf { x } } } _ { n }$ (orange). The displacement vector ${ \tilde { \pmb x } } _ { n } - { \pmb x } _ { n }$ lies completely in the orthogonal complement $U _ { 2 }$ of $U _ { 1 }$ 

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_013.jpg>)


Since we can generally write the original data point ${ \bf { x } } _ { n }$ as a linear combination of all basis vectors, it holds that 

$$
\begin{array}{l} \boldsymbol {x} _ {n} = \sum_ {d = 1} ^ {D} z _ {d n} \boldsymbol {b} _ {d} \stackrel {(1 0. 3 2)} {=} \sum_ {d = 1} ^ {D} (\boldsymbol {x} _ {n} ^ {\top} \boldsymbol {b} _ {d}) \boldsymbol {b} _ {d} = \left(\sum_ {d = 1} ^ {D} \boldsymbol {b} _ {d} \boldsymbol {b} _ {d} ^ {\top}\right) \boldsymbol {x} _ {n} \\ = \left(\sum_ {m = 1} ^ {M} \boldsymbol {b} _ {m} \boldsymbol {b} _ {m} ^ {\top}\right) \boldsymbol {x} _ {n} + \left(\sum_ {j = M + 1} ^ {D} \boldsymbol {b} _ {j} \boldsymbol {b} _ {j} ^ {\top}\right) \boldsymbol {x} _ {n}, \end{array}\tag{10.37a}
$$

(10.37b) 

where we split the sum with $D$ terms into a sum over M and a sum over $D - M$ terms. With this result, we find that the displacement vector $\begin{array} { r l } { \pmb { x } _ { n } - \tilde { \pmb { x } } _ { n } , \mathrm { i . e . } } \end{array}$ , the difference vector between the original data point and its projection, is 

$$
\begin{array}{c} \boldsymbol {x} _ {n} - \tilde {\boldsymbol {x}} _ {n} = \left(\sum_ {j = M + 1} ^ {D} \boldsymbol {b} _ {j} \boldsymbol {b} _ {j} ^ {\top}\right) \boldsymbol {x} _ {n} \\ = \sum_ {j = M + 1} ^ {D} (\boldsymbol {x} _ {n} ^ {\top} \boldsymbol {b} _ {j}) \boldsymbol {b} _ {j}. \end{array}\tag{10.38a}
$$

(10.38b) 

This means the difference is exactly the projection of the data point onto the orthogonal complement of the principal subspace: We identify the matrix $\begin{array} { r } { \sum _ { j = M + 1 } ^ { D } { \pmb { b } } _ { j } { \pmb { b } } _ { j } ^ { \top } } \end{array}$ in (10.38a) as the projection matrix that performs this projection. Hence the displacement vector ${ \pmb x } _ { n } - \tilde { { \pmb x } } _ { 1 }$ lies in the subspace that is orthogonal to the principal subspace as illustrated in Figure 10.9. 

Remark (Low-Rank Approximation). In (10.38a), we saw that the projection matrix, which projects x onto $\tilde { \mathbf { x } } ,$ is given by 

$$
\sum_ {m = 1} ^ {M} \boldsymbol {b} _ {m} \boldsymbol {b} _ {m} ^ {\top} = \boldsymbol {B} \boldsymbol {B} ^ {\top}.\tag{10.39}
$$

By construction as a sum of rank-one matrices $\pmb { b } _ { m } \pmb { b } _ { m } ^ { \top }$ we see that $B B ^ { \top }$ i symmetric and has rank M. Therefore, the average squared reconstruction error can also be written as 

$$
\frac {1}{N} \sum_ {n = 1} ^ {N} \left\| \boldsymbol {x} _ {n} - \tilde {\boldsymbol {x}} _ {n} \right\| ^ {2} = \frac {1}{N} \sum_ {n = 1} ^ {N} \left\| \boldsymbol {x} _ {n} - \boldsymbol {B B} ^ {\top} \boldsymbol {x} _ {n} \right\| ^ {2}\tag{10.40a}
$$

$$
= \frac {1}{N} \sum_ {n = 1} ^ {N} \left\| (\boldsymbol {I} - \boldsymbol {B} \boldsymbol {B} ^ {\top}) \boldsymbol {x} _ {n} \right\| ^ {2}.\tag{10.40b}
$$

Finding orthonormal basis vectors $b _ { 1 } , \dots , b _ { M }$ , which minimize the difference between the original data ${ \bf { x } } _ { n }$ and their projections $\tilde { \mathbf { x } } _ { n } ,$ is equivalent to finding the best rank-M approximation $B B ^ { \top }$ of the identity matrix I (see Section 4.6). 

Now we have all the tools to reformulate the loss function (10.29). 

$$
J _ {M} = \frac {1}{N} \sum_ {n = 1} ^ {N} \| \boldsymbol {x} _ {n} - \tilde {\boldsymbol {x}} _ {n} \| ^ {2} \stackrel {(1 0. 3 8 b)} {=} \frac {1}{N} \sum_ {n = 1} ^ {N} \left\| \sum_ {j = M + 1} ^ {D} (\boldsymbol {b} _ {j} ^ {\top} \boldsymbol {x} _ {n}) \boldsymbol {b} _ {j} \right\| ^ {2}.\tag{10.41}
$$

We now explicitly compute the squared norm and exploit the fact that the $b _ { j }$ form an ONB, which yields 

$$
\begin{array}{l} J _ {M} = \frac {1}{N} \sum_ {n = 1} ^ {N} \sum_ {j = M + 1} ^ {D} (\boldsymbol {b} _ {j} ^ {\top} \boldsymbol {x} _ {n}) ^ {2} = \frac {1}{N} \sum_ {n = 1} ^ {N} \sum_ {j = M + 1} ^ {D} \boldsymbol {b} _ {j} ^ {\top} \boldsymbol {x} _ {n} \boldsymbol {b} _ {j} ^ {\top} \boldsymbol {x} _ {n} \\ = \frac {1}{N} \sum_ {n = 1} ^ {N} \sum_ {j = M + 1} ^ {D} \boldsymbol {b} _ {j} ^ {\top} \boldsymbol {x} _ {n} \boldsymbol {x} _ {n} ^ {\top} \boldsymbol {b} _ {j}, \end{array}\tag{10.42a}
$$

(10.42b) 

where we exploited the symmetry of the dot product in the last step to write $\pmb { b } _ { j } ^ { \top } \pmb { x } _ { n } = \pmb { x } _ { n } ^ { \top } \pmb { b } _ { j }$ . We now swap the sums and obtain 

$$
\begin{array}{l} J _ {M} = \sum_ {j = M + 1} ^ {D} \boldsymbol {b} _ {j} ^ {\top} \underbrace {\left(\frac {1}{N} \sum_ {n = 1} ^ {N} \boldsymbol {x} _ {n} \boldsymbol {x} _ {n} ^ {\top}\right)} _ {=: S} \boldsymbol {b} _ {j} = \sum_ {j = M + 1} ^ {D} \boldsymbol {b} _ {j} ^ {\top} \boldsymbol {S b} _ {j} \\ = \sum_ {j = M + 1} ^ {D} \operatorname{tr} (\boldsymbol {b} _ {j} ^ {\top} \boldsymbol {S b} _ {j}) = \sum_ {j = M + 1} ^ {D} \operatorname{tr} (\boldsymbol {S b} _ {j} \boldsymbol {b} _ {j} ^ {\top}) = \operatorname{tr} \Big (\underbrace {\left(\sum_ {j = M + 1} ^ {D} \boldsymbol {b} _ {j} \boldsymbol {b} _ {j} ^ {\top}\right) \boldsymbol {S}} _ {\text {projection matrix}} \Big), \end{array} \tag {10.43a}\tag{10.43b}
$$

where we exploited the property that the trace operator $\operatorname { t r } ( \cdot )$ (see (4.18)) is linear and invariant to cyclic permutations of its arguments. Since we assumed that our dataset is centered, i.e., $\mathbf { \mathbb { E } } [ \mathcal { X } ] = \mathbf { 0 }$ , we identify S as the data covariance matrix. Since the projection matrix in (10.43b) is constructed as a sum of rank-one matrices $\boldsymbol { b } _ { j } \boldsymbol { b } _ { j } ^ { \intercal }$ it itself is of rank $D - M$ 

Equation (10.43a) implies that we can formulate the average squared reconstruction error equivalently as the covariance matrix of the data, 

Figure 10.10 Embedding of MNIST digits 0 (blue) and 1 (orange) in a two-dimensional principal subspace using PCA. Four embeddings of the digits $^ { 6 } 0 ^ { \dag }$ and “1” in the principal subspace are highlighted in red with their corresponding original digit. 

projected onto the orthogonal complement of the principal subspace. Minimizing the average squared reconstruction error is therefore equivalent to minimizing the variance of the data when projected onto the subspace we ignore, i.e., the orthogonal complement of the principal subspace. Equivalently, we maximize the variance of the projection that we retain in the principal subspace, which links the projection loss immediately to the maximum-variance formulation of PCA discussed in Section 10.2. But this then also means that we will obtain the same solution that we obtained for the maximum-variance perspective. Therefore, we omit a derivation that is identical to the one presented in Section 10.2 and summarize the results from earlier in the light of the projection perspective. 

The average squared reconstruction error, when projecting onto the Mdimensional principal subspace, is 

$$
J _ {M} = \sum_ {j = M + 1} ^ {D} \lambda_ {j},\tag{10.44}
$$

where $\lambda _ { j }$ are the eigenvalues of the data covariance matrix. Therefore, to minimize (10.44) we need to select the smallest D M eigenvalues, which then implies that their corresponding eigenvectors are the basis of the orthogonal complement of the principal subspace. Consequently, this means that the basis of the principal subspace comprises the eigenvectors $b _ { 1 } , \dots , b _ { M }$ that are associated with the largest M eigenvalues of the data covariance matrix. 

## Example 10.3 (MNIST Digits Embedding)

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_014.jpg>)



Figure 10.10 visualizes the training data of the MMIST digits $" 0 "$ and $^ { \mathfrak { s } } \mathrm { 1 } ^ { \mathfrak { p } }$ embedded in the vector subspace spanned by the first two principal components. We observe a relatively clear separation between ${ } ^ { \mathfrak { s o } } { } ^ { \mathfrak { s } }$ (blue dots) and $^ { \mathfrak { \omega } } \mathfrak { I } ^ { \mathfrak { s } }$ (orange dots), and we see the variation within each individual


cluster. Four embeddings of the digits $" 0 "$ and $^ { \mathfrak { s } } \mathrm { 1 } ^ { \mathfrak { p } }$ in the principal subspace are highlighted in red with their corresponding original digit. The figure reveals that the variation within the set $\mathrm { o f } \ ^ { \mathrm { \infty } } 0 ^ { \mathrm { \prime } }$ is significantly greater than the variation within the set of “1”. 

## 10.4 Eigenvector Computation and Low-Rank Approximations

In the previous sections, we obtained the basis of the principal subspace as the eigenvectors that are associated with the largest eigenvalues of the data covariance matrix 

$$
\boldsymbol {S} = \frac {1}{N} \sum_ {n = 1} ^ {N} \boldsymbol {x} _ {n} \boldsymbol {x} _ {n} ^ {\top} = \frac {1}{N} \boldsymbol {X} \boldsymbol {X} ^ {\top},\tag{10.45}
$$

$$
\pmb {X} = [ \pmb {x} _ {1}, \dots , \pmb {x} _ {N} ] \in \mathbb {R} ^ {D \times N}.\tag{10.46}
$$

Note that X is a $D \times N$ matrix, $\mathrm { i . e . , }$ it is the transpose of the “typical” data matrix (Bishop, 2006; Murphy, 2012). To get the eigenvalues (and the corresponding eigenvectors) of S, we can follow two approaches: 

We perform an eigendecomposition (see Section 4.2) and compute the eigenvalues and eigenvectors of S directly. 

We use a singular value decomposition (see Section 4.5). Since S is symmetric and factorizes into $X \bar { X } ^ { \top }$ (ignoring the factor $\textstyle { \frac { 1 } { N } } )$ , the eigenvalues of $_ { s }$ are the squared singular values of $\boldsymbol { X }$ 

More specifically, the SVD of X is given by 

$$
\underbrace {\boldsymbol {X}} _ {D \times N} = \underbrace {\boldsymbol {U}} _ {D \times D} \underbrace {\boldsymbol {\Sigma}} _ {D \times N} \underbrace {\boldsymbol {V} ^ {\top}} _ {N \times N},\tag{10.47}
$$

where $U \in \mathbb { R } ^ { D \times D }$ and $V ^ { \top } \in \mathbb { R } ^ { N \times N }$ are orthogonal matrices and $\pmb { \Sigma } \in$ $\mathbb { R } ^ { D \times N }$ is a matrix whose only nonzero entries are the singular values $\sigma _ { i i } \geqslant$ 0. It then follows that 

$$
\boldsymbol {S} = \frac {1}{N} \boldsymbol {X} \boldsymbol {X} ^ {\top} = \frac {1}{N} \boldsymbol {U} \boldsymbol {\Sigma} \underbrace {\boldsymbol {V} ^ {\top} \boldsymbol {V}} _ {= \boldsymbol {I} _ {N}} \boldsymbol {\Sigma} ^ {\top} \boldsymbol {U} ^ {\top} = \frac {1}{N} \boldsymbol {U} \boldsymbol {\Sigma} \boldsymbol {\Sigma} ^ {\top} \boldsymbol {U} ^ {\top}.\tag{10.48}
$$

With the results from Section 4.5, we get that the columns of $U$ are the eigenvectors of $\pmb { X } \pmb { X } ^ { \top }$ (and therefore S). Furthermore, the eigenvalues $\lambda _ { d }$ of $\pmb { S }$ are related to the singular values of $\boldsymbol { X }$ via 

$$
\lambda_ {d} = \frac {\sigma_ {d} ^ {2}}{N}.\tag{10.49}
$$

This relationship between the eigenvalues of $\pmb { S }$ and the singular values of X provides the connection between the maximum variance view (Section 10.2) and the singular value decomposition. 

## 10.4.1 PCA Using Low-Rank Matrix Approximations

To maximize the variance of the projected data (or minimize the average squared reconstruction error), PCA chooses the columns of U in (10.48) to be the eigenvectors that are associated with the M largest eigenvalues of the data covariance matrix S so that we identify U as the projection matrix B in (10.3), which projects the original data onto a lower-dimensional subspace of dimension M. The Eckart-Young theorem (Theorem 4.25 in Section 4.6) offers a direct way to estimate the low-dimensional representation. Consider the best rank-M approximation 

$$
\tilde {\boldsymbol {X}} _ {M} := \operatorname{argmin} _ {\mathrm{rk} (\boldsymbol {A}) \leqslant M} \| \boldsymbol {X} - \boldsymbol {A} \| _ {2} \in \mathbb {R} ^ {D \times N}\tag{10.50}
$$

of $X ,$ , where $\left\| \cdot \right\| _ { 2 }$ is the spectral norm defined in (4.93). The Eckart-Young theorem states that $\tilde { \pmb { X } } _ { M }$ is given by truncating the SVD at the top-M singular value. In other words, we obtain 

$$
\tilde {\boldsymbol {X}} _ {M} = \underbrace {\boldsymbol {U} _ {M}} _ {D \times M} \underbrace {\boldsymbol {\Sigma} _ {M}} _ {M \times M} \underbrace {\boldsymbol {V} _ {M} ^ {\top}} _ {M \times N} \in \mathbb {R} ^ {D \times N}\tag{10.51}
$$

with orthogonal matrices $\pmb { U } _ { M } : = [ \pmb { u } _ { 1 } , \dots , \pmb { u } _ { M } ] \in \mathbb { R } ^ { D \times M }$ and $V _ { M } : =$ $[ { \pmb v } _ { 1 } , \dots , { \pmb v } _ { M } ] \in \mathbb { R } ^ { N \times M }$ and a diagonal matrix $\boldsymbol { \Sigma } _ { M } ^ { \mathsf { ^ { - } } } \in \mathbb { R } ^ { M \times M }$ whose diagonal entries are the M largest singular values of X. 

## 10.4.2 Practical Aspects

Finding eigenvalues and eigenvectors is also important in other fundamental machine learning methods that require matrix decompositions. In theory, as we discussed in Section 4.2, we can solve for the eigenvalues as roots of the characteristic polynomial. However, for matrices larger than 4 4 this is not possible because we would need to find the roots of a polynomial of degree 5 or higher. However, the Abel-Ruffini theorem (Ruffini, 1799; Abel, 1826) states that there exists no algebraic solution to this problem for polynomials of degree 5 or more. Therefore, in practice, we solve for eigenvalues or singular values using iterative methods, which are implemented in all modern packages for linear algebra. 

In many applications (such as PCA presented in this chapter), we only require a few eigenvectors. It would be wasteful to compute the full decomposition, and then discard all eigenvectors with eigenvalues that are beyond the first few. It turns out that if we are interested in only the first few eigenvectors (with the largest eigenvalues), then iterative processes, which directly optimize these eigenvectors, are computationally more efficient than a full eigendecomposition (or SVD). In the extreme case of only needing the first eigenvector, a simple method called the power iteration is very efficient. Power iteration chooses a random vector $\scriptstyle { \pmb x } _ { 0 }$ that is not in the null space of S and follows the iteration 

$$
\boldsymbol {x} _ {k + 1} = \frac {\boldsymbol {S x} _ {k}}{\| \boldsymbol {S x} _ {k} \|}, \quad k = 0, 1, \dots .\tag{10.52}
$$

This means the vector $\scriptstyle { \mathbf { { \mathit { x } } } } _ { k }$ is multiplied by S in every iteration and then normalized, i.e., we always have $\| \pmb { x } _ { k } \| = 1$ . This sequence of vectors converges to the eigenvector associated with the largest eigenvalue of S. The original Google PageRank algorithm (Page et al., 1999) uses such an algorithm for ranking web pages based on their hyperlinks. 

## 10.5 PCA in High Dimensions

In order to do PCA, we need to compute the data covariance matrix. In D dimensions, the data covariance matrix is a $D \times D$ matrix. Computing the eigenvalues and eigenvectors of this matrix is computationally expensive as it scales cubically in D. Therefore, PCA, as we discussed earlier, will be infeasible in very high dimensions. For example, if our ${ \bf { x } } _ { n }$ are images with 10,000 pixels $( \mathrm { e } . g . , 1 0 0 \times 1 0 0$ pixel images), we would need to compute the eigendecomposition of a $1 0 , 0 0 0 \times 1 0 , 0 0 0$ covariance matrix. In the following, we provide a solution to this problem for the case that we have substantially fewer data points than dimensions, i.e., $N \ll D .$ 

Assume we have a centered dataset $\pmb { x } _ { 1 } , \dots , \pmb { x } _ { N } , \pmb { x } _ { n } \in \mathbb { R } ^ { D }$ . Then the data covariance matrix is given as 

$$
\pmb {S} = \frac {1}{N} \pmb {X} \pmb {X} ^ {\top} \in \mathbb {R} ^ {D \times D},\tag{10.53}
$$

where $\pmb { X } = [ \pmb { x } _ { 1 } , \ldots , \pmb { x } _ { N } ]$ is a $D \times N$ matrix whose columns are the data points. 

We now assume that $N \ll D , \mathrm { i . e . }$ , the number of data points is smaller than the dimensionality of the data. If there are no duplicate data points, the rank of the covariance matrix S is N, so it has $D - N + 1$ many eigenvalues that are 0. Intuitively, this means that there are some redundancies. In the following, we will exploit this and turn the $D \times D$ covariance matrix into an $N \times N$ covariance matrix whose eigenvalues are all positive. 

In PCA, we ended up with the eigenvector equation 

$$
\boldsymbol {S} \boldsymbol {b} _ {m} = \lambda_ {m} \boldsymbol {b} _ {m}, \quad m = 1, \dots , M,\tag{10.54}
$$

where $b _ { m }$ is a basis vector of the principal subspace. Let us rewrite this equation a bit: With $\pmb { S }$ defined in (10.53), we obtain 

$$
\pmb {S} \pmb {b} _ {m} = \frac {1}{N} \pmb {X} \pmb {X} ^ {\top} \pmb {b} _ {m} = \lambda_ {m} \pmb {b} _ {m}.\tag{10.55}
$$

We now multiply $\pmb { X } ^ { \top } \in \mathbb { R } ^ { N \times D }$ from the left-hand side, which yields 

$$
\frac {1}{N} \underbrace {\boldsymbol {X} ^ {\top} \boldsymbol {X}} _ {N \times N} \underbrace {\boldsymbol {X} ^ {\top} \boldsymbol {b} _ {m}} _ {=: \boldsymbol {c} _ {m}} = \lambda_ {m} \boldsymbol {X} ^ {\top} \boldsymbol {b} _ {m} \iff \frac {1}{N} \boldsymbol {X} ^ {\top} \boldsymbol {X} \boldsymbol {c} _ {m} = \lambda_ {m} \boldsymbol {c} _ {m}  ,\tag{10.56}
$$

and we get a new eigenvector/eigenvalue equation: $\lambda _ { m }$ remains eigenvalue, which confirms our results from Section 4.5.3 that the nonzero eigenvalues of $X X ^ { \top }$ equal the nonzero eigenvalues of $\boldsymbol { X } ^ { \top } \boldsymbol { X }$ . We obtain the eigenvector of the matrix $\mathbf { \Psi } _ { N } ^ { 1 } \mathbf { \boldsymbol { X } } ^ { \top } \mathbf { \boldsymbol { X } } \in \mathbf { \tilde { \Psi } } \mathbb { R } ^ { N \times N }$ associated with $\lambda _ { m }$ as $\pmb { c } _ { m } : = \pmb { X } ^ { \top } \pmb { b } _ { m }$ . Assuming we have no duplicate data points, this matrix has rank N and is invertible. This also implies that $\begin{array} { r } { \frac { 1 } { N } \bar { \pmb X } ^ { \top } \bar { \pmb X } } \end{array}$ has the same (nonzero) eigenvalues as the data covariance matrix $\pmb { S }$ . But this is now an $N \times N$ matrix, so that we can compute the eigenvalues and eigenvectors much more efficiently than for the original $D \times D$ data covariance matrix. 

Now that we have the eigenvectors of $\scriptstyle { \frac { 1 } { N } } X ^ { \intercal } X$ , we are going to recover the original eigenvectors, which we still need for PCA. Currently, we know the eigenvectors of $\scriptstyle { \frac { 1 } { N } } X ^ { \intercal }$ X. If we left-multiply our eigenvalue/ eigenvector equation with $\boldsymbol { X }$ , we get 

$$
\underbrace {\frac {1}{N} \boldsymbol {X} \boldsymbol {X} ^ {\top}} _ {s} \boldsymbol {X} \boldsymbol {c} _ {m} = \lambda_ {m} \boldsymbol {X} \boldsymbol {c} _ {m}\tag{10.57}
$$

and we recover the data covariance matrix again. This now also means that we recover $X c _ { m }$ as an eigenvector of S. 

Remark. If we want to apply the PCA algorithm that we discussed in Section 10.6, we need to normalize the eigenvectors $X c _ { m }$ of $\pmb { S }$ so that they have norm 1. ◇ 

## 10.6 Key Steps of PCA in Practice

In the following, we will go through the individual steps of PCA using a running example, which is summarized in Figure 10.11. We are given a two-dimensional dataset (Figure 10.11(a)), and we want to use PCA to project it onto a one-dimensional subspace. 

1. Mean subtraction We start by centering the data by computing the mean µ of the dataset and subtracting it from every single data point. This ensures that the dataset has mean 0 (Figure 10.11(b)). Mean subtraction is not strictly necessary but reduces the risk of numerical problems. 

2. Standardization Divide the data points by the standard deviation $\sigma _ { d }$ of the dataset for every dimension $d = 1 , \ldots , D$ . Now the data is unit free, and it has variance 1 along each axis, which is indicated by the two arrows in Figure 10.11(c). This step completes the standardization of the data. 

3. Eigendecomposition of the covariance matrix Compute the data covariance matrix and its eigenvalues and corresponding eigenvectors. Since the covariance matrix is symmetric, the spectral theorem (Theorem 4.15) states that we can find an ONB of eigenvectors. In Figure 10.11(d), the eigenvectors are scaled by the magnitude of the corresponding eigenvalue. The longer vector spans the principal subspace, which we denote by U. The data covariance matrix is represented by the ellipse. 

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_015.jpg>)



(a) Original dataset.


![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_016.jpg>)



(b) Step 1: Centering by subtracting the mean from each data point.


![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_017.jpg>)



(b) centering; (c) divide by standard deviation; (d) eigendecomposi tion; (e) projection; (f) mapping back to original data space.



(c) Step 2: Dividing by the standard deviation to make the data unit free. Data has variance 1 along each axis.


![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_018.jpg>)



(d) Step 3: Compute eigenvalues and eigenvectors (arrows) of the data covariance matrix (ellipse).


![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_019.jpg>)



(e) Step 4: Project data onto the principal subspace.


![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_020.jpg>)



(f) Undo the standardization and move projected data back into the original data space from (a).


4. Projection We can project any data point $\pmb { x } _ { * } \in \mathbb { R } ^ { D }$ onto the principal subspace: To get this right, we need to standardize $^ { \mathbf { x } } { } ^ { \mathrm { ~ } }$ using the mean $\mu _ { d }$ and standard deviation $\sigma _ { d }$ of the training data in the dth dimension, respectively, so that 

$$
x _ {*} ^ {(d)} \leftarrow \frac {x _ {*} ^ {(d)} - \mu_ {d}}{\sigma_ {d}}, d = 1, \ldots , D,\tag{10.58}
$$

where $x _ { * } ^ { ( d ) }$ is the dth component of ${ \pmb x } _ { \ast }$ . We obtain the projection as 

$$
\tilde {\boldsymbol {x}} _ {*} = \boldsymbol {B} \boldsymbol {B} ^ {\top} \boldsymbol {x} _ {*}\tag{10.59}
$$

with coordinates 

$$
\boldsymbol {z} _ {*} = \boldsymbol {B} ^ {\top} \boldsymbol {x} _ {*}\tag{10.60}
$$

with respect to the basis of the principal subspace. Here, B is the matrix that contains the eigenvectors that are associated with the largest eigenvalues of the data covariance matrix as columns. PCA returns the coordinates (10.60), not the projections $\mathbf { x } _ { \ast }$ 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



Having standardized our dataset, (10.59) only yields the projections in the context of the standardized dataset. To obtain our projection in the original data space (i.e., before standardization), we need to undo the standardization (10.58) and multiply by the standard deviation before adding the mean so that we obtain 

$$
\tilde {x} _ {*} ^ {(d)} \leftarrow \tilde {x} _ {*} ^ {(d)} \sigma_ {d} + \mu_ {d}, d = 1, \ldots , D.\tag{10.61}
$$

Figure 10.11(f) illustrates the projection in the original data space. 

## Example 10.4 (MNIST Digits: Reconstruction)

In the following, we will apply PCA to the MNIST digits dataset, which contains 60,000 examples of handwritten digits 0 through 9. Each digit is an image of size $2 8 \times 2 8 ,$ , i.e., it contains 784 pixels so that we can interpret every image in this dataset as a vector $\pmb { x } \in \mathbb { R } ^ { 7 8 4 }$ . Examples of these digits are shown in Figure 10.3. 

Figure 10.12 Effect of increasing the number of principal components on reconstruction. 

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_021.jpg>)


For illustration purposes, we apply PCA to a subset of the MNIST digits, and we focus on the digit “8”. We used 5,389 training images of the digit “8” and determined the principal subspace as detailed in this chapter. We then used the learned projection matrix to reconstruct a set of test images, which is illustrated in Figure 10.12. The first row of Figure 10.12 shows a set of four original digits from the test set. The following rows show reconstructions of exactly these digits when using a principal subspace of dimensions 1, 10, 100, and 500, respectively. We see that even with a single-dimensional principal subspace we get a halfway decent reconstruction of the original digits, which, however, is blurry and generic. With an increasing number of principal components (PCs), the reconstructions become sharper and more details are accounted for. With 500 principal components, we effectively obtain a near-perfect reconstruction. If we were to choose 784 PCs, we would recover the exact digit without any compression loss. 

Figure 10.13 shows the average squared reconstruction error, which is 

$$
\frac {1}{N} \sum_ {n = 1} ^ {N} \| \pmb {x} _ {n} - \tilde {\pmb {x}} _ {n} \| ^ {2} = \sum_ {i = M + 1} ^ {D} \lambda_ {i},\tag{10.62}
$$

as a function of the number M of principal components. We can see that the importance of the principal components drops off rapidly, and only marginal gains can be achieved by adding more PCs. This matches exactly our observation in Figure 10.5, where we discovered that the most of the variance of the projected data is captured by only a few principal components. With about 550 $\mathrm { P C } s ,$ , we can essentially fully reconstruct the training data that contains the digit “8” (some pixels around the boundaries show no variation across the dataset as they are always black). 

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_022.jpg>)



Figure 10.13 Average squared reconstruction error as a function of the number of principal components. The average squared reconstruction error is the sum of the eigenvalues in the orthogonal complement of the principal subspace.


## 10.7 Latent Variable Perspective

In the previous sections, we derived PCA without any notion of a prob abilistic model using the maximum-variance and the projection perspectives. On the one hand, this approach may be appealing as it allows us to sidestep all the mathematical difficulties that come with probability theory, but on the other hand, a probabilistic model would offer us more flexibility and useful insights. More specifically, a probabilistic model would 

Come with a likelihood function, and we can explicitly deal with noisy observations (which we did not even discuss earlier) 

Allow us to do Bayesian model comparison via the marginal likelihood as discussed in Section 8.6 

View PCA as a generative model, which allows us to simulate new data 

Allow us to make straightforward connections to related algorithms 

Deal with data dimensions that are missing at random by applying Bayes’ theorem 

Give us a notion of the novelty of a new data point 

Give us a principled way to extend the model, e.g., to a mixture of PCA models 

Have the PCA we derived in earlier sections as a special case 

Allow for a fully Bayesian treatment by marginalizing out the model parameters 

By introducing a continuous-valued latent variable $z \in \mathbb { R } ^ { M }$ it is possible to phrase PCA as a probabilistic latent-variable model. Tipping and Bishop (1999) proposed this latent-variable model as probabilistic PCA (PPCA). PPCA addresses most of the aforementioned issues, and the PCA solution that we obtained by maximizing the variance in the projected space or by minimizing the reconstruction error is obtained as the special case of maximum likelihood estimation in a noise-free setting. 

## 10.7.1 Generative Process and Probabilistic Model

In PPCA, we explicitly write down the probabilistic model for linear dimensionality reduction. For this we assume a continuous latent variable $z \in \mathbb { R } ^ { M }$ with a standard-normal prior $p ( z ) = \mathcal { N } ( \mathbf { 0 } , I )$ and a linear relationship between the latent variables and the observed x data where 

$$
\boldsymbol {x} = \boldsymbol {B} \boldsymbol {z} + \boldsymbol {\mu} + \boldsymbol {\epsilon} \in \mathbb {R} ^ {D},\tag{10.63}
$$

where $\epsilon \sim \mathcal { N } ( \mathbf { 0 } , \sigma ^ { 2 } I )$ is Gaussian observation noise and $B \in \mathbb { R } ^ { D \times M }$ and $\pmb { \mu } \in \mathbb { R } ^ { D }$ describe the linear/affine mapping from latent to observed variables. Therefore, PPCA links latent and observed variables via 

$$
p (\boldsymbol {x} | \boldsymbol {z}, \boldsymbol {B}, \boldsymbol {\mu}, \sigma^ {2}) = \mathcal {N} \left(\boldsymbol {x} \mid \boldsymbol {B} \boldsymbol {z} + \boldsymbol {\mu}, \sigma^ {2} \boldsymbol {I}\right).\tag{10.64}
$$

Overall, PPCA induces the following generative process: 

$$
\boldsymbol {z} _ {n} \sim \mathcal {N} (\boldsymbol {z} | \boldsymbol {0}, \boldsymbol {I})\tag{10.65}
$$

$$
\boldsymbol {x} _ {n} \mid \boldsymbol {z} _ {n} \sim \mathcal {N} (\boldsymbol {x} \mid B \boldsymbol {z} _ {n} + \boldsymbol {\mu}, \sigma^ {2} \boldsymbol {I})\tag{10.66}
$$

To generate a data point that is typical given the model parameters, we follow an ancestral sampling scheme: We first sample a latent variable $z _ { n }$ from $p ( z )$ . Then we use $z _ { n }$ in (10.64) to sample a data point conditioned on the sampled $z _ { n } , { \mathrm { i . e . , } } x _ { n } \sim p ( { \pmb x } \mid z _ { n } , B , \mu , \sigma ^ { 2 } )$ 

This generative process allows us to write down the probabilistic model (i.e., the joint distribution of all random variables; see Section 8.4) as 

$$
p (\pmb {x}, \pmb {z} | \pmb {B}, \pmb {\mu}, \sigma^ {2}) = p (\pmb {x} | \pmb {z}, \pmb {B}, \pmb {\mu}, \sigma^ {2}) p (\pmb {z}),\tag{10.67}
$$

which immediately gives rise to the graphical model in Figure 10.14 using the results from Section 8.5. 

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_023.jpg>)



Figure 10.14 Graphical model for probabilistic PCA. The observations x<sub>n</sub> explicitly depend on corresponding latent variables $\begin{array} { r } { z _ { n } \sim \mathcal { N } ( \mathbf { 0 } , I ) } \end{array}$ . The model parameters B, µ and the likelihood parameter σ are shared across the dataset.


Remark. Note the direction of the arrow that connects the latent variables z and the observed data x: The arrow points from $\textit { z } \mathrm { t o } \textbf { \em x }$ , which means that the PPCA model assumes a lower-dimensional latent cause z for highdimensional observations x. In the end, we are obviously interested in finding something out $\mathrm { \ a b o u t { } } z \mathrm { \ g i v e n }$ some observations. To get there we will apply Bayesian inference to $\operatorname { \mathfrak { s } } _ { \mathrm { i n v e r t } } , { }$ the arrow implicitly and go from observations to latent variables. 

## Example 10.5 (Generating New Data Using Latent Variables)

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_024.jpg>)



Figure 10.15 Generating new MNIST digits. The latent variables z can be used to generate new data $\tilde { \mathbf { x } } = B z$ . The closer we stay to the training data, the more realistic the generated data.


Figure 10.15 shows the latent coordinates of the MNIST digits $" 8 "$ found by PCA when using a two-dimensional principal subspace (blue dots). We can query any vector $z _ { * }$ in this latent space and generate an image $\tilde { \mathbf { { x } } } _ { * } = $ $\pmb { B z }$ that resembles the digit “8”. We show eight of such generated images with their corresponding latent space representation. Depending on where we query the latent space, the generated images look different (shape, rotation, size, etc.). If we query away from the training data, we see more and more artifacts, e.g., the top-left and top-right digits. Note that the intrinsic dimensionality of these generated images is only two. 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



## 10.7.2 Likelihood and Joint Distribution

Using the results from Chapter $^ { 6 , }$ we obtain the likelihood of this probabilistic model by integrating out the latent variable z (see Section 8.4.3) so that 

$$
p (\boldsymbol {x} \mid \boldsymbol {B}, \boldsymbol {\mu}, \sigma^ {2}) = \int p (\boldsymbol {x} \mid \boldsymbol {z}, \boldsymbol {B}, \boldsymbol {\mu}, \sigma^ {2}) p (\boldsymbol {z}) \mathrm{d} \boldsymbol {z}\tag{10.68a}
$$

$$
= \int \mathcal {N} (\boldsymbol {x} | \boldsymbol {B z} + \boldsymbol {\mu}, \sigma^ {2} \boldsymbol {I}) \mathcal {N} (\boldsymbol {z} | \boldsymbol {0}, \boldsymbol {I}) \mathrm{d} \boldsymbol {z}.\tag{10.68b}
$$

From Section $6 . 5 _ { : }$ , we know that the solution to this integral is a Gaussian distribution with mean 

$$
\mathbb {E} _ {\boldsymbol {x}} [ \boldsymbol {x} ] = \mathbb {E} _ {\boldsymbol {z}} [ B \boldsymbol {z} + \boldsymbol {\mu} ] + \mathbb {E} _ {\epsilon} [ \epsilon ] = \boldsymbol {\mu}\tag{10.69}
$$

and with covariance matrix 

$$
\begin{array}{r} \mathbb {V} [ \boldsymbol {x} ] = \mathbb {V} _ {\boldsymbol {z}} [ \boldsymbol {B} \boldsymbol {z} + \boldsymbol {\mu} ] + \mathbb {V} _ {\boldsymbol {\epsilon}} [ \boldsymbol {\epsilon} ] = \mathbb {V} _ {\boldsymbol {z}} [ \boldsymbol {B} \boldsymbol {z} ] + \sigma^ {2} \boldsymbol {I} \\ = \boldsymbol {B} \mathbb {V} _ {\boldsymbol {z}} [ \boldsymbol {z} ] \boldsymbol {B} ^ {\top} + \sigma^ {2} \boldsymbol {I} = \boldsymbol {B} \boldsymbol {B} ^ {\top} + \sigma^ {2} \boldsymbol {I}. \end{array}\tag{10.70a}
$$

(10.70b) 

The likelihood in (10.68b) can be used for maximum likelihood or MAP estimation of the model parameters. 

Remark. We cannot use the conditional distribution in (10.64) for maximum likelihood estimation as it still depends on the latent variables. The likelihood function we require for maximum likelihood (or MAP) estimation should only be a function of the data x and the model parameters, but must not depend on the latent variables. ◇ 

From Section 6.5, we know that a Gaussian random variable z and a linear/affine transformation $\textbf { \em x } = \textbf { \em B z }$ of it are jointly Gaussian distributed. We already know the marginals $p ( z ) = \mathcal { N } \big ( z | \mathbf { 0 } , I \big )$ and $p ( { \pmb x } ) =$ $\mathcal { N } ( { \pmb x } | { \pmb \mu } , B B ^ { \top } + \sigma ^ { 2 } { \pmb I } )$ . The missing cross-covariance is given as 

$$
\operatorname{Cov} [ \boldsymbol {x}, \boldsymbol {z} ] = \operatorname{Cov} _ {\boldsymbol {z}} [ \boldsymbol {B} \boldsymbol {z} + \boldsymbol {\mu} ] = \boldsymbol {B} \operatorname{Cov} _ {\boldsymbol {z}} [ \boldsymbol {z}, \boldsymbol {z} ] = \boldsymbol {B}.\tag{10.71}
$$

Therefore, the probabilistic model of PPCA, i.e., the joint distribution of latent and observed random variables is explicitly given by 

$$
p (\boldsymbol {x}, \boldsymbol {z} \mid \boldsymbol {B}, \boldsymbol {\mu}, \sigma^ {2}) = \mathcal {N} \left(\left[ \begin{array}{c} \boldsymbol {x} \\ \boldsymbol {z} \end{array} \right]   \bigg |   \left[ \begin{array}{c} \boldsymbol {\mu} \\ \boldsymbol {0} \end{array} \right], \left[ \begin{array}{c c} \boldsymbol {B} \boldsymbol {B} ^ {\top} + \sigma^ {2} \boldsymbol {I} & \boldsymbol {B} \\ \boldsymbol {B} ^ {\top} & \boldsymbol {I} \end{array} \right]\right)  ,\tag{10.72}
$$

with a mean vector of length $D + M$ and a covariance matrix of size $( D + M ) \times ( D + M )$ 

## 10.7.3 Posterior Distribution

The joint Gaussian distribution $p ( \pmb { x } , z | \pmb { B } , \pmb { \mu } , \sigma ^ { 2 } )$ in (10.72) allows us to determine the posterior distribution $p ( \pmb { z } \vert \pmb { x } )$ immediately by applying the rules of Gaussian conditioning from Section 6.5.1. The posterior distribution of the latent variable given an observation x is then 

$$
p (\boldsymbol {z} \mid \boldsymbol {x}) = \mathcal {N} (\boldsymbol {z} \mid \boldsymbol {m}, \boldsymbol {C}),\tag{10.73}
$$

$$
\boldsymbol {m} = \boldsymbol {B} ^ {\top} (\boldsymbol {B B} ^ {\top} + \sigma^ {2} \boldsymbol {I}) ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu}),\tag{10.74}
$$

$$
\boldsymbol {C} = \boldsymbol {I} - \boldsymbol {B} ^ {\top} (\boldsymbol {B B} ^ {\top} + \sigma^ {2} \boldsymbol {I}) ^ {- 1} \boldsymbol {B}.\tag{10.75}
$$

Note that the posterior covariance does not depend on the observed data x. For a new observation ${ \bf { \delta } } _ { \bf { { x } } } ,$ in data space, we use (10.73) to determine the posterior distribution of the corresponding latent variable $\boldsymbol { z } _ { \ast }$ . The covariance matrix $C$ allows us to assess how confident the embedding is. A covariance matrix $C$ with a small determinant (which measures volumes) tells us that the latent embedding $z _ { * }$ is fairly certain. If we obtain a posterior distribution $p ( z _ { * } \mid x _ { * } )$ with much variance, we may be faced with an outlier. However, we can explore this posterior distribution to understand what other data points x are plausible under this posterior. To do this, we exploit the generative process underlying PPCA, which allows us to explore the posterior distribution on the latent variables by generating new data that is plausible under this posterior: 

1. Sample a latent variable $z _ { * } \sim p ( z | x _ { * } )$ from the posterior distribution over the latent variables (10.73). 

2. Sample a reconstructed vector $\tilde { \mathbf { \em x } } _ { * } \sim p ( \mathbf { \boldsymbol { x } } \mid z _ { * } , B , \mu , \sigma ^ { 2 } )$ from (10.64). 

If we repeat this process many times, we can explore the posterior distribution (10.73) on the latent variables $z _ { \ast }$ and its implications on the observed data. The sampling process effectively hypothesizes data, which is plausible under the posterior distribution. 

## 10.8 Further Reading

We derived PCA from two perspectives: (a) maximizing the variance in the projected space; (b) minimizing the average reconstruction error. However, PCA can also be interpreted from different perspectives. Let us recap what we have done: We took high-dimensional data $\pmb { x } \in \mathbb { R } ^ { D }$ and used a matrix $B ^ { \top }$ to find a lower-dimensional representation $z \in \mathbb { R } ^ { M }$ . The columns of B are the eigenvectors of the data covariance matrix S that are associated with the largest eigenvalues. Once we have a low-dimensional representation z, we can get a high-dimensional version of it (in the original data space) as $\pmb { x } \approx \tilde { \pmb { x } } = \pmb { B } z = \pmb { B } \pmb { B } ^ { \top } \pmb { x } \in \mathbb { R } ^ { D }$ , where $B B ^ { \top }$ is a projection matrix. 

We can also think of PCA as a linear auto-encoder as illustrated in Figure 10.16. An auto-encoder encodes the data ${ \pmb x } _ { n } \in \mathbb { R } ^ { D }$ to a code $\pmb { z } _ { n } \in \mathbb { R } ^ { M }$ and decodes it to a ${ \tilde { \mathbf { x } } } _ { n }$ similar to ${ \bf { x } } _ { n }$ . The mapping from the data to the code is called the encoder, and the mapping from the code back to the original data space is called the decoder. If we consider linear mappings where the code is given by $\pmb { z } _ { n } = \pmb { B } ^ { \top } \pmb { x } _ { n } \in \mathbb { R } ^ { M }$ and we are interested in minimizing the average squared error between the data ${ \bf { x } } _ { n }$ and its reconstruction $\tilde { \boldsymbol { x } } _ { n } = B z _ { n } , n = 1 , . . . , N$ , we obtain 

![image](<Images/10_Dimensionality_Reduction_with_Principal_Component_Analysis_image_025.jpg>)


$$
\frac {1}{N} \sum_ {n = 1} ^ {N} \| \boldsymbol {x} _ {n} - \tilde {\boldsymbol {x}} _ {n} \| ^ {2} = \frac {1}{N} \sum_ {n = 1} ^ {N} \left\| \boldsymbol {x} _ {n} - \boldsymbol {B B} ^ {\top} \boldsymbol {x} _ {n} \right\| ^ {2}.\tag{10.76}
$$

This means we end up with the same objective function as in (10.29) that we discussed in Section 10.3 so that we obtain the PCA solution when we minimize the squared auto-encoding loss. If we replace the linear mapping of PCA with a nonlinear mapping, we get a nonlinear auto-encoder. A prominent example of this is a deep auto-encoder where the linear functions are replaced with deep neural networks. In this context, the encoder is also known as a recognition network or inference network, whereas the decoder is also called a generator. 

Another interpretation of PCA is related to information theory. We can think of the code as a smaller or compressed version of the original data point. When we reconstruct our original data using the code, we do not get the exact data point back, but a slightly distorted or noisy version of it. This means that our compression is “lossy”. Intuitively, we want to maximize the correlation between the original data and the lowerdimensional code. More formally, this is related to the mutual information. We would then get the same solution to PCA we discussed in Section 10.3 by maximizing the mutual information, a core concept in information theory (MacKay, 2003). 

In our discussion on PPCA, we assumed that the parameters of the model, i.e., B, µ, and the likelihood parameter $\sigma ^ { 2 } .$ , are known. Tipping and Bishop (1999) describe how to derive maximum likelihood estimates for these parameters in the PPCA setting (note that we use a different notation in this chapter). The maximum likelihood parameters, when projecting D-dimensional data onto an M-dimensional subspace, are 

$$
\pmb {\mu} _ {\mathrm{ML}} = \frac {1}{N} \sum_ {n = 1} ^ {N} \pmb {x} _ {n},\tag{10.77}
$$

$$
\pmb {B} _ {\mathrm{ML}} = \pmb {T} (\pmb {\Lambda} - \sigma^ {2} \pmb {I}) ^ {\frac {1}{2}} \pmb {R},\tag{10.78}
$$

$$
\sigma_ {\mathrm{ML}} ^ {2} = \frac {1}{D - M} \sum_ {j = M + 1} ^ {D} \lambda_ {j},\tag{10.79}
$$

where $\pmb { T } \in \mathbb { R } ^ { D \times M }$ contains M eigenvectors of the data covariance matrix, $\pmb { \Lambda } = \mathrm { d i a g } ( \lambda _ { 1 } , \dots , \lambda _ { M } ) \in \mathbb { R } ^ { M \times M }$ is a diagonal matrix with the eigenvalues associated with the principal axes on its diagonal, and $\pmb { R } \in \mathbf { \bar { \mathbb { R } } } ^ { M \times M }$ is an arbitrary orthogonal matrix. The maximum likelihood solution $B _ { \mathrm { M I } }$ is unique up to an arbitrary orthogonal transformation, e.g., we can rightmultiply $B _ { \mathrm { M L } }$ with any rotation matrix R so that (10.78) essentially is a singular value decomposition (see Section 4.5). An outline of the proof is given by Tipping and Bishop (1999). 

The matrix $\Lambda - \sigma ^ { 2 } I$ in (10.78) is guaranteed to be positive semidefinite as the smallest eigenvalue of the data covariance matrix is bounded from below by the noise variance $\sigma ^ { 2 } ,$ 

The maximum likelihood estimate for $\pmb { \mu }$ given in (10.77) is the sample mean of the data. The maximum likelihood estimator for the observation noise variance $\sigma ^ { 2 }$ given in (10.79) is the average variance in the orthogonal complement of the principal subspace, i.e., the average leftover variance that we cannot capture with the first M principal components is treated as observation noise. 

In the noise-free limit where $\sigma  0$ , PPCA and PCA provide identical solutions: Since the data covariance matrix S is symmetric, it can be diagonalized (see Section 4.4), i.e., there exists a matrix $_ { \pmb { T } }$ of eigenvectors of $_ { s }$ so that 

$$
\pmb {S} = \pmb {T} \pmb {\Lambda} \pmb {T} ^ {- 1}.\tag{10.80}
$$

In the PPCA model, the data covariance matrix is the covariance matrix of the Gaussian likelihood $p ( { \pmb x } | B , { \pmb \mu } , \sigma ^ { 2 } )$ , which is $B B ^ { \top } + \sigma ^ { 2 } I$ , see (10.70b). For $\sigma  0$ , we obtain $B B ^ { \intercal }$ so that this data covariance must equal the PCA data covariance (and its factorization given in (10.80)) so that 

$$
\operatorname{Cov} [ \mathcal {X} ] = \boldsymbol {T} \boldsymbol {\Lambda} \boldsymbol {T} ^ {- 1} = \boldsymbol {B} \boldsymbol {B} ^ {\top} \iff \boldsymbol {B} = \boldsymbol {T} \boldsymbol {\Lambda} ^ {\frac {1}{2}} \boldsymbol {R},\tag{10.81}
$$

i.e., we obtain the maximum likelihood estimate in (10.78) for $\sigma = 0$ From (10.78) and (10.80), it becomes clear that (P)PCA performs a decomposition of the data covariance matrix. 

In a streaming setting, where data arrives sequentially, it is recommended to use the iterative expectation maximization (EM) algorithm for maximum likelihood estimation (Roweis, 1998). 

To determine the dimensionality of the latent variables (the length of the code, the dimensionality of the lower-dimensional subspace onto which we project the data), Gavish and Donoho (2014) suggest the heuristic that, if we can estimate the noise variance $\sigma ^ { 2 }$ of the data, we should discard all singular values smaller than $\frac { 4 \sigma { \sqrt { D } } } { \sqrt { 3 } }$ . Alternatively, we can use (nested) cross-validation (Section 8.6.1) or Bayesian model selection criteria (discussed in Section 8.6.2) to determine a good estimate of the intrinsic dimensionality of the data (Minka, 2001b). 

Similar to our discussion on linear regression in Chapter 9, we can place a prior distribution on the parameters of the model and integrate them out. By doing so, we (a) avoid point estimates of the parameters and the issues that come with these point estimates (see Section 8.6) and (b) allow for an automatic selection of the appropriate dimensionality M of the latent space. In this Bayesian PCA, which was proposed by Bishop (1999), a prior $p ( { \boldsymbol { \mu } } , B , \sigma ^ { 2 } )$ is placed on the model parameters. The generative process allows us to integrate the model parameters out instead of conditioning on them, which addresses overfitting issues. Since this integration is analytically intractable, Bishop (1999) proposes to use approximate inference methods, such as MCMC or variational inference. We refer to the work by Gilks et al. (1996) and Blei et al. (2017) for more details on these approximate inference techniques. 

In PPCA, we considered the linear model $p ( \pmb { x } _ { n } \mid z _ { n } ) = { \mathcal N } \big ( \pmb { x } _ { n } \mid B z _ { n } +$ $\mu , \sigma ^ { 2 } I )$ with prior $p ( z _ { n } ) = \mathcal { N } ( \mathbf { 0 } , I )$ , where all observation dimensions are affected by the same amount of noise. If we allow each observation dimension d to have a different variance $\sigma _ { d } ^ { 2 } .$ , we obtain factor analysis (FA) (Spearman, 1904; Bartholomew et al., 2011). This means that FA gives the likelihood some more flexibility than PPCA, but still forces the data to be explained by the model parameters B, $\pmb { \mu }$ .However, FA no longer allows for a closed-form maximum likelihood solution so that we need to use an iterative scheme, such as the expectation maximization algorithm, to estimate the model parameters. While in PPCA all stationary points are global optima, this no longer holds for FA. Compared to PPCA, FA does not change if we scale the data, but it does return different solutions if we rotate the data. 

An algorithm that is also closely related to PCA is independent component analysis (ICA (Hyvarinen et al., 2001)). Starting again with the latent-variable perspective $p ( { \pmb x } _ { n } \mid z _ { n } ) = { \mathcal { N } } \big ( { \pmb x } _ { n } \mid B z _ { n } + \pmb \mu , \sigma ^ { 2 } { \pmb I } \big )$ we now change the prior on $z _ { n }$ to non-Gaussian distributions. ICA can be used for blind-source separation. Imagine you are in a busy train station with many people talking. Your ears play the role of microphones, and they linearly mix different speech signals in the train station. The goal of blindsource separation is to identify the constituent parts of the mixed signals. As discussed previously in the context of maximum likelihood estimation for PPCA, the original PCA solution is invariant to any rotation. Therefore, PCA can identify the best lower-dimensional subspace in which the signals live, but not the signals themselves (Murphy, 2012). ICA addresses this issue by modifying the prior distribution $p ( z )$ on the latent sources to require non-Gaussian priors $p ( z )$ . We refer to the books by Hyvarinen et al. (2001) and Murphy (2012) for more details on ICA. 

PCA, factor analysis, and ICA are three examples for dimensionality reduction with linear models. Cunningham and Ghahramani (2015) provide a broader survey of linear dimensionality reduction. 

The (P)PCA model we discussed here allows for several important extensions. In Section 10.5, we explained how to do PCA when the input dimensionality D is significantly greater than the number N of data points. By exploiting the insight that PCA can be performed by computing (many) inner products, this idea can be pushed to the extreme by considering infinite-dimensional features. The kernel trick is the basis of kernel PCA and allows us to implicitly compute inner products between infinitedimensional features (Scholkopf et al.¨ , 1998; Scholkopf and Smola¨ , 2002). 

There are nonlinear dimensionality reduction techniques that are derived from PCA (Burges (2010) provides a good overview). The autoencoder perspective of PCA that we discussed previously in this section can be used to render PCA as a special case of a deep auto-encoder. In the deep auto-encoder, both the encoder and the decoder are represented by multilayer feedforward neural networks, which themselves are nonlinear mappings. If we set the activation functions in these neural networks to be the identity, the model becomes equivalent to PCA. A different approach to nonlinear dimensionality reduction is the Gaussian process latent-variable model (GP-LVM) proposed by Lawrence (2005). The GP-LVM starts off with the latent-variable perspective that we used to derive PPCA and replaces the linear relationship between the latent variables z and the observations x with a Gaussian process (GP). Instead of estimating the parameters of the mapping (as we do in PPCA), the GP-LVM marginalizes out the model parameters and makes point estimates of the latent variables z. Similar to Bayesian PCA, the Bayesian GP-LVM proposed by Titsias and Lawrence (2010) maintains a distribution on the latent variables z and uses approximate inference to integrate them out as well. 