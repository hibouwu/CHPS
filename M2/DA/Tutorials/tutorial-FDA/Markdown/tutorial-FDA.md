# Fisher and Kernel Fisher Discriminant Analysis: Tutorial

Benyamin Ghojogh 

BGHOJOGH@UWATERLOO.CA 

Department of Electrical and Computer Engineering, 

Machine Learning Laboratory, University of Waterloo, Waterloo, ON, Canada 

Fakhri Karray 

KARRAY@UWATERLOO.CA 

Department of Electrical and Computer Engineering, 

Centre for Pattern Analysis and Machine Intelligence, University of Waterloo, Waterloo, ON, Canada 

Mark Crowley 

MCROWLEY@UWATERLOO.CA 

Department of Electrical and Computer Engineering, 

Machine Learning Laboratory, University of Waterloo, Waterloo, ON, Canada 

## Abstract

This is a detailed tutorial paper which explains the Fisher discriminant Analysis (FDA) and kernel FDA. We start with projection and reconstruction. Then, one- and multi-dimensional FDA subspaces are covered. Scatters in two- and then multi-classes are explained in FDA. Then, we discuss on the rank of the scatters and the dimensionality of the subspace. A real-life example is also provided for interpreting FDA. Then, possible singularity of the scatter is discussed to introduce robust FDA. PCA and FDA directions are also compared. We also prove that FDA and linear discriminant analysis are equivalent. Fisher forest is also introduced as an ensemble of fisher subspaces useful for handling data with different features and dimensionality. Afterwards, kernel FDA is explained for both one- and multi-dimensional subspaces with both two- and multi-classes. Finally, some simulations are performed on AT&T face dataset to illustrate FDA and compare it with PCA. 

## 1. Introduction

Assume we have a dataset of instances or data points $\{ ( { \pmb x } _ { i } , { \pmb y } _ { i } ) \} _ { i = 1 } ^ { n }$ with sample size n and dimensionality ${ \pmb x } _ { i } \in \mathrm { \Sigma }$ R<sup>d</sup> and $\pmb { y } _ { i } ~ \in ~ \mathbb { R } ^ { \ell }$ The $\{ { \pmb x } _ { i } \} _ { i = 1 } ^ { n }$ are the input data to the model and the $\{ \boldsymbol { y } _ { i } \} _ { i = 1 } ^ { n }$ are the observations (labels). We define $\mathbb { R } ^ { d \times n } \ni X : = \left[ \pmb { x } _ { 1 } , . . . , \pmb { x } _ { n } \right]$ and $\mathbb { R } ^ { \ell \times n } \ni$ $Y : = [ { \pmb y } _ { 1 } , \dots , { \pmb y } _ { n } ]$ . We can also have an out-of-sample data point, $\pmb { x } _ { t } \in \mathbb { R } ^ { d }$ , which is not in the training set. If there are $n _ { t }$ out-of-sample data points, $\{ \pmb { x } _ { t , i } \} _ { 1 } ^ { n _ { t } }$ , we define $\mathbb { R } ^ { d \times n _ { t } } \ni { \bf X } _ { t } : = \left[ { \pmb { x } } _ { t , 1 } , . . . , { \pmb { x } } _ { t , n _ { t } } \right]$ . Usually, the data points exist on a subspace or sub-manifold. Subspace or manifold learning tries to learn this sub-manifold (Ghojogh et al., 2019b). 

Here, we consider the case where the observations $\{ \pmb { y } _ { i } \} _ { i = 1 } ^ { n }$ come from a discrete set so that the task is classification. Assume the dataset consists of c classes, $\{ \pmb { x } _ { i } ^ { ( 1 ) } \} _ { i = 1 } ^ { n _ { 1 } } , \ldots , \{ \pmb { x } _ { i } ^ { ( c ) } \} _ { i = 1 } ^ { n _ { c } }$ where $n _ { j }$ denotes the sample size (cardinality) of the the j-th class. 

We want to find a subspace (or sub-manifold) which separates the classes as much as possible while the data also become as spread as possible. Fisher Discriminant Analysis (FDA) (Friedman et al., 2009) pursues this goal. It was first proposed in (Fisher, 1936) by Sir. Ronald Aylmer Fisher (1890 – 1962) who was a genius in statistics. He proposed many important concepts in the modern statistics, such as variance (Fisher, 1919), FDA (Fisher, 1936), Fisher information (Frieden, 2004), Analysis of Variance (ANOVA) (Fisher, 1992), etc. The paper (Fisher, 1936), which proposed FDA, was the first paper introducing the well-known Iris flower dataset. Note that Fisher’s work was mostly concentrating on the statistics in the area of genetics. Much of his work was about variance making no wonder for us why FDA is all about variance and scatters. Kernel FDA (Mika et al., 1999; 2000) performs the goal of FDA in the feature space. The FDA and kernel FDA have had many different applications. Some examples for applications of FDA are face recognition (Fisherfaces) (Belhumeur et al., 1997; Etemad & Chellappa, 1997; Zhao et al., 1999), action recognition (Fisherposes) (Ghojogh et al., 2017; Mokari et al., 2018), and gesture recognition (Samadani et al., 2013). Some examples for applications of kernel FDA are face recognition (kernel Fisherfaces) (Yang, 2002; Liu et al., 2004) and palmprint Recognition (Wang & Ruan, 2006). 

In the literature, sometimes, FDA is referred to as Linear Discriminant Analysis (LDA) or Fisher LDA (FLDA). This is because FDA and LDA (Ghojogh & Crowley, 2019a) are equivalent although LDA is a classification method and not a subspace learning algorithm. In this paper, we will prove why they are equivalent. 

## 2. Projection Formulation

## 2.1. Projection

Assume we have a data point $\pmb { x } \in \mathbb { R } ^ { d }$ . We want to project this data point onto the vector space spanned by p vectors $\{ \pmb { u } _ { 1 } , \ldots , \pmb { u } _ { p } \}$ where each vector is d-dimensional and usually $p \ll d .$ . We stack these vectors column-wise in matrix $\pmb { U } = [ \pmb { u } _ { 1 } , \ldots , \pmb { u } _ { p } ] \in \mathbb { R } ^ { d \times p }$ . In other words, we want to project x onto the column space of U, denoted by $\mathbb { C } { \mathrm { o l } } ( U )$ The projection of $\pmb { x } \in \mathbb { R } ^ { d }$ onto $\mathbb { C } \mathrm { o l } ( U ) \in \mathbb { R } ^ { p }$ and then its representation in the $\mathbb { R } ^ { d }$ (its reconstruction) can be seen as a linear system of equations: 

$$
\mathbb {R} ^ {d} \ni \widehat {\boldsymbol {x}} := \boldsymbol {U} \boldsymbol {\beta},\tag{1}
$$

where we should find the unknown coefficients $\beta \in \mathbb { R } ^ { p }$ If the x lies in the Col(U) or span $\{ u _ { 1 } , \ldots , u _ { p } \}$ , this linear system has exact solution, so ${ \widehat { \pmb { x } } } = { \pmb x } = { \pmb U } \beta$ . However, if x does not lie in this space, there is no any solution $\beta$ for $x = U \beta$ and we should solve for projection of x onto $\mathbb { C } \mathrm { o l } ( U )$ or span $\{ \pmb { u } _ { 1 } , \ldots , \pmb { u } _ { p } \}$ and then its reconstruction. In other words, we should solve for Eq. (1). In this case, xb and x are different and we have a residual: 

$$
\boldsymbol {r} = \boldsymbol {x} - \widehat {\boldsymbol {x}} = \boldsymbol {x} - \boldsymbol {U} \boldsymbol {\beta},\tag{2}
$$

which we want to be small. As can be seen in Fig. 1, the smallest residual vector is orthogonal to Col(U); therefore: 

$$
\begin{array}{r l} \boldsymbol {x} - \boldsymbol {U} \boldsymbol {\beta} \perp \boldsymbol {U} & \Longrightarrow \boldsymbol {U} ^ {\top} (\boldsymbol {x} - \boldsymbol {U} \boldsymbol {\beta}) = 0, \\ & \Longrightarrow \boldsymbol {\beta} = (\boldsymbol {U} ^ {\top} \boldsymbol {U}) ^ {- 1} \boldsymbol {U} ^ {\top} \boldsymbol {x}. \end{array}\tag{3}
$$

It is noteworthy that the Eq. (3) is also the formula of coefficients in linear regression (Friedman et al., 2009) where the input data are the rows of U and the labels are x; however, our goal here is different. 

Plugging Eq. (3) in Eq. (1) gives us: 

$$
\widehat {\boldsymbol {x}} = \boldsymbol {U} (\boldsymbol {U} ^ {\top} \boldsymbol {U}) ^ {- 1} \boldsymbol {U} ^ {\top} \boldsymbol {x}.
$$

We define: 

$$
\mathbb {R} ^ {d \times d} \ni \boldsymbol {\Pi} := \boldsymbol {U} (\boldsymbol {U} ^ {\top} \boldsymbol {U}) ^ {- 1} \boldsymbol {U} ^ {\top},\tag{4}
$$

as “projection matrix” because it projects x onto $\mathbb { C } { \mathrm { o l } } ( U )$ (and reconstructs back). Note that Π is also referred to as the “hat matrix” in the literature because it puts a hat on top of x. 

![image](<Images/tutorial-FDA/image_001.jpg>)



Figure 1. The residual and projection onto the column space of U.


If the vectors $\{ u _ { 1 } , \ldots , u _ { p } \}$ are orthonormal (the matrix U is orthogonal), we have $\bar { \pmb { U } } ^ { \top } = \pmb { U } ^ { - 1 }$ and thus $U ^ { \top } U = I .$ Therefore, Eq. (4) is simplified: 

$$
\boldsymbol {\Pi} = \boldsymbol {U} \boldsymbol {U} ^ {\top}.\tag{5}
$$

So, we have: 

$$
\widehat {\boldsymbol {x}} = \boldsymbol {\Pi} \boldsymbol {x} = \boldsymbol {U} \boldsymbol {U} ^ {\top} \boldsymbol {x}.\tag{6}
$$

## 2.2. Projection onto a Subspace

In subspace learning, the projection of a vector $\pmb { x } \in \mathbb { R } ^ { d }$ onto the column space of $U \in \mathbb { R } ^ { d \times p }$ (a p-dimensional subspace spanned by $\{ u _ { j } \} _ { j = 1 } ^ { p }$ where $\boldsymbol { u } _ { j } \in \mathbb { R } ^ { d } )$ is defined as: 

$$
\begin{array}{l} \mathbb {R} ^ {p} \ni \widetilde {\boldsymbol {x}} := \boldsymbol {U} ^ {\top} \boldsymbol {x}, \\ \mathbb {R} ^ {d} \ni \widehat {\boldsymbol {x}} := \boldsymbol {U} \boldsymbol {U} ^ {\top} \boldsymbol {x} = \boldsymbol {U} \widetilde {\boldsymbol {x}}, \end{array}\tag{7}
$$

(8) 

where $\widetilde { \pmb x }$ and xb denote the projection and reconstruction of x, respectively. 

If we have n data points, $\{ { \pmb x } _ { i } \} _ { i = 1 } ^ { n }$ , which can be stored column-wise in a matrix $\boldsymbol { X } \in \mathbb { R } ^ { d \times n }$ , the projection and reconstruction of X are defined as: 

$$
\begin{array}{l} \mathbb {R} ^ {p \times n} \ni \widetilde {\boldsymbol {X}} := \boldsymbol {U} ^ {\top} \boldsymbol {X}, \\ \mathbb {R} ^ {d \times n} \ni \widehat {\boldsymbol {X}} := \boldsymbol {U} \boldsymbol {U} ^ {\top} \boldsymbol {X} = \boldsymbol {U} \widetilde {\boldsymbol {X}}, \end{array}\tag{9}
$$

(10) 

respectively. 

If we have an out-of-sample data point $\mathbf { \Delta } _ { \mathbf { \mathcal { X } } _ { t } }$ which was not used in calculation of U, the projection and reconstruction of it are defined as: 

$$
\mathbb {R} ^ {p} \ni \widetilde {\boldsymbol {x}} _ {t} := \boldsymbol {U} ^ {\top} \boldsymbol {x} _ {t},\tag{11}
$$

$$
\mathbb {R} ^ {d} \ni \widehat {\boldsymbol {x}} _ {t} := \boldsymbol {U} \boldsymbol {U} ^ {\top} \boldsymbol {x} _ {t} = \boldsymbol {U} \widetilde {\boldsymbol {x}} _ {t},\tag{12}
$$

respectively. 

In case we have $n _ { t }$ out-of-sample data points, $\{ \pmb { x } _ { t , i } \} _ { i = 1 } ^ { n _ { t } }$ which can be stored column-wise in a matrix $\boldsymbol X _ { t } \in \mathbb R ^ { d \times n _ { t } }$ the projection and reconstruction of $X _ { t }$ are defined as: 

$$
\mathbb {R} ^ {p \times n _ {t}} \ni \widetilde {\boldsymbol {X}} _ {t} := \boldsymbol {U} ^ {\top} \boldsymbol {X} _ {t},\tag{13}
$$

$$
\mathbb {R} ^ {d \times n _ {t}} \ni \widehat {\boldsymbol {X}} _ {t} := \boldsymbol {U} \boldsymbol {U} ^ {\top} \boldsymbol {X} _ {t} = \boldsymbol {U} \widetilde {\boldsymbol {X}} _ {t},\tag{14}
$$

respectively. 

For the properties of the projection matrix U, refer to (Ghojogh & Crowley, 2019c). 

## 2.2.1. PROJECTION ONTO A ONE-DIMENSIONAL SUBSPACE

Considering the data $\{ { \pmb x } _ { i } \} _ { i = 1 } ^ { n }$ , the mean of data is: 

$$
\mathbb {R} ^ {d} \ni \boldsymbol {\mu} _ {x} := \frac {1}{n} \sum_ {i = 1} ^ {n} \boldsymbol {x} _ {i},\tag{15}
$$

and the centered data point x is: 

$$
\mathbb {R} ^ {d} \ni \breve {\boldsymbol {x}} := \boldsymbol {x} - \boldsymbol {\mu} _ {x}.\tag{16}
$$

The centered data X is: 

$$
\mathbb {R} ^ {d \times n} \ni \breve {\boldsymbol {X}} := \boldsymbol {X} - \boldsymbol {\mu} _ {x} = \boldsymbol {X} \boldsymbol {H},\tag{17}
$$

where $\breve { \pmb { X } } = [ \breve { \pmb { x } } _ { 1 } , \varrho _ { 1 } , \breve { \pmb { x } } _ { n } ] \ \in \ \mathbb { R } ^ { d \times n }$ and $\mathbb { R } ^ { n \times n } \ni H : =$ $\pmb { I } - ( 1 / n ) \mathbf { 1 1 } ^ { \top }$ is the centering matrix (see Appendix A in (Ghojogh & Crowley, 2019c)). 

In Eq. (8), if $p = 1$ , we are projecting x onto only one vector u and reconstruct it. If the data point is centered, the reconstruction is: 

$$
\widehat {\boldsymbol {x}} = \boldsymbol {u} \boldsymbol {u} ^ {\top} \breve {\boldsymbol {x}}.
$$

The squared length (squared $\ell _ { 2 } { \mathrm { - n o r m } } )$ of this reconstructed vector is: 

$$
\begin{array}{l} | | \widehat {\boldsymbol {x}} | | _ {2} ^ {2} = | | \boldsymbol {u} \boldsymbol {u} ^ {\top} \breve {\boldsymbol {x}} | | _ {2} ^ {2} = (\boldsymbol {u} \boldsymbol {u} ^ {\top} \breve {\boldsymbol {x}}) ^ {\top} (\boldsymbol {u} \boldsymbol {u} ^ {\top} \breve {\boldsymbol {x}}) \\ = \breve {\boldsymbol {x}} ^ {\top} \boldsymbol {u} \underbrace {\boldsymbol {u} ^ {\top} \boldsymbol {u}} _ {1} \boldsymbol {u} ^ {\top} \breve {\boldsymbol {x}} \stackrel {(a)} {=} \breve {\boldsymbol {x}} ^ {\top} \boldsymbol {u}   \boldsymbol {u} ^ {\top} \breve {\boldsymbol {x}} \stackrel {(b)} {=} \boldsymbol {u} ^ {\top} \breve {\boldsymbol {x}}   \breve {\boldsymbol {x}} ^ {\top} \boldsymbol {u}, \end{array}\tag{18}
$$

where (a) is because u is a unit (normal) vector, i.e., $\pmb { u } ^ { \top } \pmb { u } = | | \pmb { u } | | _ { 2 } ^ { 2 } = 1$ , and (b) is because $\breve { \pmb { x } } ^ { \top } \pmb { u } = \pmb { u } ^ { \top } \breve { \pmb { x } } \in \mathbb { R }$ Suppose we have n data points $\{ { \pmb x } _ { i } \} _ { i = 1 } ^ { n }$ where $\{ \breve { \pmb { x } } _ { i } \} _ { i = 1 } ^ { n }$ are the centered data. The summation of the squared lengths of their projections $\{ \widehat { \pmb x } _ { i } \} _ { i = 1 } ^ { n }$ is: 

$$
\sum_ {i = 1} ^ {n} | | \widehat {\boldsymbol {x}} _ {i} | | _ {2} \stackrel {(1 8)} {=} \sum_ {i = 1} ^ {n} \boldsymbol {u} ^ {\top} \breve {\boldsymbol {x}} _ {i} \breve {\boldsymbol {x}} _ {i} ^ {\top} \boldsymbol {u} = \boldsymbol {u} ^ {\top} \Big (\sum_ {i = 1} ^ {n} \breve {\boldsymbol {x}} _ {i} \breve {\boldsymbol {x}} _ {i} ^ {\top} \Big) \boldsymbol {u}.\tag{19}
$$

Considering $\breve { \pmb { X } } = [ \breve { \pmb { x } } _ { 1 } , \dots , \breve { \pmb { x } } _ { n } ] \in \mathbb { R } ^ { d \times n }$ , we have: 

$$
\begin{array}{r l} \mathbb {R} ^ {d \times d} \ni \boldsymbol {S} & := \sum_ {i = 1} ^ {n} (\boldsymbol {x} _ {i} - \boldsymbol {\mu} _ {x}) (\boldsymbol {x} _ {i} - \boldsymbol {\mu} _ {x}) ^ {\top} \stackrel {(1 6)} {=} \sum_ {i = 1} ^ {n} \breve {\boldsymbol {x}} _ {i} \breve {\boldsymbol {x}} _ {i} ^ {\top} \\ & = \breve {\boldsymbol {X}} \breve {\boldsymbol {X}} ^ {\top} \stackrel {(1 7)} {=} \boldsymbol {X} \boldsymbol {H} \boldsymbol {H} \boldsymbol {X} ^ {\top}, \end{array} \tag {20}
$$

where S is called the “covariance matrix” or “scatter ma-$\operatorname { t r i x } ^ { \prime \prime }$ . If the data were already centered, we would have $S = X X ^ { \top }$ 

Plugging Eq. (20) in Eq. (19) gives us: 

$$
\sum_ {i = 1} ^ {n} | | \widehat {\boldsymbol {x}} _ {i} | | _ {2} ^ {2} = \boldsymbol {u} ^ {\top} \boldsymbol {S u}.\tag{21}
$$

Note that we can also say that $\mathbf { \boldsymbol { u } } ^ { \top } \mathbf { \boldsymbol { S } } \mathbf { \boldsymbol { u } }$ is the variance of the projected data onto PCA subspace. In other words, $\pmb { u } ^ { \top } \bar { \pmb { S } } \pmb { u } ^ { \top } = \mathbb { V } \mathbf { a r } ( \pmb { u } ^ { \top } \breve { \pmb { X } } )$ . This makes sense because when some non-random thing (here u) is multiplied to the random data (here ${ \check { X } } ) ,$ it will have squared (quadratic) effect on variance, and $\mathbf { \boldsymbol { u } } ^ { \top } \mathbf { \boldsymbol { S } } \mathbf { \boldsymbol { u } }$ is quadratic in u. 

Therefore, $\mathbf { \boldsymbol { u } } ^ { \top } \mathbf { \boldsymbol { S } } \mathbf { \boldsymbol { u } }$ can be interpreted in two ways: (I) the squared length of reconstruction and (II) the variance of projection. 

If we consider the n data points in the matrix $\pmb { X } \in \mathbb { R } ^ { d \times n }$ the squared length of reconstruction of the centered data is: 

$$
\begin{array}{l} | | \widehat {\boldsymbol {X}} | | _ {F} ^ {2} = | | \boldsymbol {u} \boldsymbol {u} ^ {\top} \breve {\boldsymbol {X}} | | _ {F} ^ {2} = \mathbf {t r} \big ((\boldsymbol {u} \boldsymbol {u} ^ {\top} \breve {\boldsymbol {X}}) ^ {\top} (\boldsymbol {u} \boldsymbol {u} ^ {\top} \breve {\boldsymbol {X}}) \big) \\ \qquad = \mathbf {t r} (\breve {\boldsymbol {X}} ^ {\top} \boldsymbol {u} \underbrace {\boldsymbol {u} ^ {\top} \boldsymbol {u}} _ {1} \boldsymbol {u} ^ {\top} \breve {\boldsymbol {X}}) \stackrel {(a)} {=} \mathbf {t r} (\breve {\boldsymbol {X}} ^ {\top} \boldsymbol {u} \boldsymbol {u} ^ {\top} \breve {\boldsymbol {X}}) \\ \qquad \stackrel {(b)} {=} \mathbf {t r} (\boldsymbol {u} ^ {\top} \breve {\boldsymbol {X}} \breve {\boldsymbol {X}} ^ {\top} \boldsymbol {u}) \stackrel {(c)} {=} \boldsymbol {u} ^ {\top} \breve {\boldsymbol {X}} \breve {\boldsymbol {X}} ^ {\top} \boldsymbol {u} \stackrel {(2 0)} {=} \boldsymbol {u} ^ {\top} \boldsymbol {S u}, \end{array}
$$

where $\mathbf { t r } ( . )$ denotes the trace of matrix, (a) is because u is a unit vector, (b) is because of the cyclic property of the trace, and (c) is because $\ b u ^ { \top } \breve { \ b X } \breve { \ b X } ^ { \top }$ u is a scalar. Hence, we have: 

$$
| | \widehat {\boldsymbol {X}} | | _ {F} ^ {2} = \boldsymbol {u} ^ {\top} \boldsymbol {S u}.\tag{22}
$$

## 2.2.2. PROJECTION ONTO A MULTI-DIMENSIONAL SUBSPACE

In Eq. (10), if $p > 1$ , we are projecting the data onto a subspace with dimensionality more than one (spanned by $\{ u _ { j } \} _ { j = 1 } ^ { p } )$ and then reconstruct back. If the data X are assumed to be centered, the reconstruction is: 

$$
\widehat {\boldsymbol {X}} = \boldsymbol {U} \boldsymbol {U} ^ {\top} \breve {\boldsymbol {X}}.
$$

The squared length (squared Frobenius Norm) of this reconstructed matrix is: 

$$
\begin{array}{l} | | \widehat {\boldsymbol {X}} | | _ {F} ^ {2} = | | \boldsymbol {U} \boldsymbol {U} ^ {\top} \breve {\boldsymbol {X}} | | _ {F} ^ {2} = \mathbf {t r} \big ((\boldsymbol {U} \boldsymbol {U} ^ {\top} \breve {\boldsymbol {X}}) ^ {\top} (\boldsymbol {U} \boldsymbol {U} ^ {\top} \breve {\boldsymbol {X}}) \big) \\ \qquad = \mathbf {t r} (\breve {\boldsymbol {X}} ^ {\top} \boldsymbol {U} \underbrace {\boldsymbol {U} ^ {\top} \boldsymbol {U}} _ {\boldsymbol {I}} \boldsymbol {U} ^ {\top} \breve {\boldsymbol {X}}) \stackrel {(a)} {=} \mathbf {t r} (\breve {\boldsymbol {X}} ^ {\top} \boldsymbol {U} \boldsymbol {U} ^ {\top} \breve {\boldsymbol {X}}) \\ \qquad \stackrel {(b)} {=} \mathbf {t r} (\boldsymbol {U} ^ {\top} \breve {\boldsymbol {X}} \breve {\boldsymbol {X}} ^ {\top} \boldsymbol {U}) \stackrel {(2 0)} {=} \mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} \boldsymbol {U}), \end{array}
$$

where (a) is because U is an orthogonal matrix (its columns are orthonormal) and (b) is because of the cyclic property of trace. Thus, we have: 

$$
| | \widehat {\boldsymbol {X}} | | _ {F} ^ {2} = \mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} \boldsymbol {U}).\tag{23}
$$

## 3. Fisher Discriminant Analysis 3.1. One-dimensional Subspace

## 3.1.1. SCATTERS IN TWO-CLASS CASE

Assume we have two classes, $\{ \pmb { x } _ { i } ^ { ( 1 ) } \} _ { i = 1 } ^ { n _ { 1 } }$ and $\{ \pmb { x } _ { i } ^ { ( 2 ) } \} _ { i = 1 } ^ { n _ { 2 } }$ where $n _ { 1 }$ and $n _ { 2 }$ denote the sample size of the first and second class, respectively, and $\pmb { x } _ { i } ^ { ( j ) }$ denotes the i-th instance of the j-th class. 

If the data instances of the j-th class are projected onto a one-dimensional subspace (vector u) by $\pmb { u } ^ { \top } \pmb { x } _ { i } ^ { ( j ) }$ , the mean and the variance of the projected data are $\pmb { u } ^ { \top } \pmb { \mu } _ { j }$ and ${ \bf \nabla } { \bf { u } } ^ { \top } { \bf S } _ { j } { \bf u } ,$ respectively, where $\mu _ { j }$ and $S _ { j }$ are the mean and covariance matrix (scatter) of the $j \cdot$ -th class. The mean of the $j \cdot$ -th class is: 

$$
\mathbb {R} ^ {d} \ni \boldsymbol {\mu} _ {j} := \frac {1}{n _ {j}} \sum_ {i = 1} ^ {n _ {j}} \boldsymbol {x} _ {i} ^ {(j)}.\tag{24}
$$

According to Appendix A, after projection onto the onedimensional subspace, the distance between the means of classes is: 

$$
\begin{array}{l} \mathbb {R} \ni d _ {B} := (\boldsymbol {u} ^ {\top} \boldsymbol {\mu} _ {1} - \boldsymbol {u} ^ {\top} \boldsymbol {\mu} _ {2}) ^ {\top} (\boldsymbol {u} ^ {\top} \boldsymbol {\mu} _ {1} - \boldsymbol {u} ^ {\top} \boldsymbol {\mu} _ {2}) \\ \qquad = (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {u} \boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) \\ \stackrel {{(a)}} {{=}} \mathbf {t r} \big ((\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {u} \boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) \big) \\ \stackrel {{(b)}} {{=}} \mathbf {t r} \big (\boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {u} \big) \\ \stackrel {{(c)}} {{=}} \boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {u} \stackrel {{(d)}} {{=}} \boldsymbol {u} ^ {\top} S _ {B}   \boldsymbol {u}, \end{array}\tag{25}
$$

where (a) is because $( \pmb { \mu } _ { 1 } - \pmb { \mu } _ { 2 } ) ^ { \top } \pmb { u } \pmb { u } ^ { \top } ( \pmb { \mu } _ { 1 } - \pmb { \mu } _ { 2 } )$ is a scalar, (b) is because of the cyclic property of trace, (c) is because ${ \pmb u } ^ { \top } ( { \pmb \mu } _ { 1 } - { \pmb \mu } _ { 2 } ) ( { \pmb \mu } _ { 1 } - { \pmb \mu } _ { 2 } ) ^ { \top } ;$ u is a scalar, and (d) is because we define: 

$$
\mathbb {R} ^ {d \times d} \ni \pmb {S} _ {B} := (\pmb {\mu} _ {1} - \pmb {\mu} _ {2}) (\pmb {\mu} _ {1} - \pmb {\mu} _ {2}) ^ {\top},\tag{26}
$$

as the between-scatter of classes. 

The Eq. (25) can also be interpreted according to Eq. (22): the $d _ { B }$ is the variance of projection of the class means or the squared length of reconstruction of the class means. 

We saw that the variance of projection is ${ \pmb u } ^ { \top } { \pmb S } _ { j } { \pmb u }$ for the j-th class. If we add up the variances of projections of the two classes, we have: 

$$
\begin{array}{r l} \mathbb {R} \ni d _ {W} & := \boldsymbol {u} ^ {\top} \boldsymbol {S} _ {1} \boldsymbol {u} + \boldsymbol {u} ^ {\top} \boldsymbol {S} _ {2} \boldsymbol {u} = \boldsymbol {u} ^ {\top} (\boldsymbol {S} _ {1} + \boldsymbol {S} _ {2}) \boldsymbol {u} \\ & \stackrel {(a)} {=} \boldsymbol {u} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {u}, \end{array}\tag{27}
$$

where: 

$$
\mathbb {R} ^ {d \times d} \ni S _ {W} := S _ {1} + S _ {2},\tag{28}
$$

is the within-scatter of classes. According to Eq. (22), the $d _ { W }$ is the summation of projection variance of class instances or the summation of the reconstruction length of class instances. 

3.1.2. SCATTERS IN MULTI-CLASS CASE: VARIANT 1 Assume $\{ \pmb { x } _ { i } ^ { ( j ) } \} _ { i = 1 } ^ { n _ { j } }$ are the instances of the j-th class where we have multiple number of classes. In this case, the between-scatter is defined as: 

$$
\mathbb {R} ^ {d \times d} \ni \boldsymbol {S} _ {B} := \sum_ {j = 1} ^ {c} (\boldsymbol {\mu} _ {j} - \boldsymbol {\mu}) (\boldsymbol {\mu} _ {j} - \boldsymbol {\mu}) ^ {\top},\tag{29}
$$

where c is the number of classes and: 

$$
\mathbb {R} ^ {d} \ni \boldsymbol {\mu} := \frac {1}{\sum_ {k = 1} ^ {c} n _ {k}} \sum_ {j = 1} ^ {c} n _ {j} \boldsymbol {\mu} _ {j} = \frac {1}{n} \sum_ {i = 1} ^ {n} \boldsymbol {x} _ {i},\tag{30}
$$

is the weighted mean of means of classes or the total mean of data. 

It is noteworthy that some researches define the betweenscatter in a weighted way: 

$$
\mathbb {R} ^ {d \times d} \ni \boldsymbol {S} _ {B} := \sum_ {j = 1} ^ {c} n _ {j} (\boldsymbol {\mu} _ {j} - \boldsymbol {\mu}) (\boldsymbol {\mu} _ {j} - \boldsymbol {\mu}) ^ {\top}.\tag{31}
$$

If we extend the Eq. (28) to c number of classes, the withinscatter is defined as: 

$$
\begin{array}{l} \mathbb {R} ^ {d \times d} \ni \boldsymbol {S} _ {W} := \sum_ {j = 1} ^ {c} \boldsymbol {S} _ {j} \\ \stackrel {{(2 0)}} {{=}} \sum_ {j = 1} ^ {c} \sum_ {i = 1} ^ {n _ {j}} (\boldsymbol {x} _ {i} ^ {(j)} - \boldsymbol {\mu} _ {j}) (\boldsymbol {x} _ {i} ^ {(j)} - \boldsymbol {\mu} _ {j}) ^ {\top}, \end{array}\tag{32}
$$

(33) 

where $n _ { j }$ is the sample size of the j-th class. 

In this case, the $d _ { B }$ and $d _ { W }$ are: 

$$
\mathbb {R} \ni d _ {B} := \pmb {u} ^ {\top} \pmb {S} _ {B} \pmb {u},
$$

$$
\mathbb {R} \ni d _ {W} := \boldsymbol {u} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {u},\tag{34}
$$

(35) 

where $S _ { B }$ and $S _ { W }$ are Eqs. (29) and (33). 

## 3.1.3. SCATTERS IN MULTI-CLASS CASE: VARIANT 2

There is another variant for multi-class case in FDA. In this variant, the within-scatter is the same as Eq. (33). The between-scatter is, however, different. 

The total-scatter is defined as the covariance matrix of the whole data, regardless of classes (Welling, 2005): 

$$
\mathbb {R} ^ {d \times d} \ni \boldsymbol {S} _ {T} := \frac {1}{n} \sum_ {i = 1} ^ {n} (\boldsymbol {x} _ {i} - \boldsymbol {\mu}) (\boldsymbol {x} _ {i} - \boldsymbol {\mu}) ^ {\top},\tag{36}
$$

where the total mean $\pmb { \mu }$ is the Eq. (30). We can also use the scaled total-scatter by dropping the $1 / n$ factor. On the other hand, the total scatter is equal to the summation of the within- and between-scatters: 

$$
\boldsymbol {S} _ {T} = \boldsymbol {S} _ {W} + \boldsymbol {S} _ {B}.\tag{37}
$$

Therefore, the between-scatter, in this variant, is obtained as: 

$$
\boldsymbol {S} _ {B} := \boldsymbol {S} _ {T} - \boldsymbol {S} _ {W}.\tag{38}
$$

## 3.1.4. FISHER SUBSPACE: VARIANT 1

In FDA, we want to maximize the projection variance (scatter) of means of classes and minimize the projection variance (scatter) of class instances. In other words, we want to maximize $d _ { B }$ and minimize $d _ { W }$ . The reason is that after projection, we want the within scatter of every class to be small and the between scatter of classes to be large; therefore, the instances of every class get close to one another and the classes get far from each other. The two mentioned optimization problems are: 

$$
\underset {\boldsymbol {u}} {\text { maximize }} d _ {B} (\boldsymbol {u}),\tag{39}
$$

$$
\underset {\boldsymbol {u}} {\text { minimize }} d _ {W} (\boldsymbol {u}).\tag{40}
$$

We can merge these two optimization problems as a regularized optimization problem: 

$$
\underset {\boldsymbol {u}} {\text { maximize }} d _ {B} (\boldsymbol {u}) - \alpha d _ {W} (\boldsymbol {u}),\tag{41}
$$

where $\alpha > 0$ is the regularization parameter. Another way of merging Eqs. (39) and (40) is: 

$$
\underset {\boldsymbol {u}} {\text { maximize }} f (\boldsymbol {u}) := \frac {d _ {B} (\boldsymbol {u})}{d _ {W} (\boldsymbol {u})} = \frac {\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {B} \boldsymbol {u}}{\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {u}},\tag{42}
$$

where $f ( \pmb { u } ) \in \mathbb { R }$ is referred to as the Fisher criterion (Xu & Lu, 2006). The Fisher criterion is a generalized Rayleigh-Ritz Quotient (see Appendix B): 

$$
f (\boldsymbol {u}) \stackrel {(1 5 8)} {=} R (\boldsymbol {S} _ {B}, \boldsymbol {S} _ {W}; \boldsymbol {u}).\tag{43}
$$

According to Eq. (165) in Appendix B, the optimization in Eq. (42) is equivalent to: 

$$
\begin{array}{l l} \underset {\boldsymbol {u}} {\text { maximize }} & \boldsymbol {u} ^ {\top} \boldsymbol {S} _ {B}   \boldsymbol {u} \\ \text { subject   to } & \boldsymbol {u} ^ {\top} \boldsymbol {S} _ {W}   \boldsymbol {u} = 1. \end{array}\tag{44}
$$

The Lagrangian (Boyd & Vandenberghe, 2004) is: 

$$
\mathcal {L} = \boldsymbol {w} ^ {\top} \boldsymbol {S} _ {B} \boldsymbol {w} - \lambda (\boldsymbol {w} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {w} - 1),
$$

where λ is the Lagrange multiplier. Equating the derivative of L to zero gives: 

$$
\begin{array}{l} \mathbb {R} ^ {d} \ni \frac {\partial \mathcal {L}}{\partial \boldsymbol {u}} = 2   S _ {B}   \boldsymbol {u} - 2   \lambda   S _ {W}   \boldsymbol {u} \stackrel {{\text { set }}} {{=}} \boldsymbol {0} \\ \implies 2   S _ {B}   \boldsymbol {u} = 2   \lambda   S _ {W}   \boldsymbol {u} \implies S _ {B}   \boldsymbol {u} = \lambda   S _ {W}   \boldsymbol {u}, \end{array}\tag{45}
$$

which is a generalized eigenvalue problem $( S _ { B } , S _ { W } )$ according to (Ghojogh et al., 2019a). The u is the eigenvector with the largest eigenvalue (because the optimization is maximization) and the λ is the corresponding eigenvalue. The u is referred to as the Fisher direction or Fisher axis. The projection and reconstruction are according to Eqs. (9) and (10), respectively, where $\textbf { \em u } \in \mathbb { R } ^ { d }$ is used instead of 

$U \in \mathbb { R } ^ { d \times p }$ . The out-of-sample projection and reconstruction are according to Eqs. (13) and (14), respectively, with u rather than U. 

One possible solution to the generalized eigenvalue problem $( S _ { B } , S _ { W } )$ is (Ghojogh et al., 2019a): 

$$
\begin{array}{l} \boldsymbol {S} _ {B} \boldsymbol {u} = \lambda \boldsymbol {S} _ {W} \boldsymbol {u} \implies \boldsymbol {S} _ {W} ^ {- 1} \boldsymbol {S} _ {B} \boldsymbol {u} = \lambda \boldsymbol {u} \\ \implies \boldsymbol {u} = \mathbf {e i g} (\boldsymbol {S} _ {W} ^ {- 1} \boldsymbol {S} _ {B}), \end{array}\tag{46}
$$

where eig(.) denotes the eigenvector of the matrix with the largest eigenvalue. Although the solution in Eq. (46) is a little dirty (Ghojogh et al., 2019a) because $S _ { w }$ might be singular and not invertible, but this solution is very common for FDA. In some researches, the diagonal of $S _ { W }$ is strengthened slightly to make it full rank and invertible (Ghojogh et al., 2019a): 

$$
\pmb {u} = \mathbf {e i g} ((\pmb {S} _ {W} + \varepsilon \pmb {I}) ^ {- 1} \pmb {S} _ {B}),\tag{47}
$$

where ε is a very small positive number, large enough to make $\pmb { S } _ { W }$ full rank. 

In a future section, we will cover robust FDA which tackles this problem. On the other hand, the generalized eigenvalue problem $( S _ { B } , S _ { W } )$ has a rigorous solution (Ghojogh et al., 2019a; Wang, 2015) which does not require non-singularity of $S _ { W }$ 

Another way to solve the optimization in Eq. (42) is taking derivative from the Fisher criterion: 

$$
\begin{array}{l} \mathbb {R} ^ {d} \ni \frac {\partial f (\boldsymbol {u})}{\partial \boldsymbol {u}} = \frac {1}{(\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {u}) ^ {2}} \times \\ \left[ (\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {u}) (2 \boldsymbol {S} _ {B} \boldsymbol {u}) - (\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {B} \boldsymbol {u}) (2 \boldsymbol {S} _ {W} \boldsymbol {u}) \right] \stackrel {{\text { set }}} {{=}} \boldsymbol {0} \end{array}
$$

$$
\stackrel {(a)} {\Longrightarrow} \boldsymbol {S} _ {B} \boldsymbol {u} = \frac {\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {B} \boldsymbol {u}}{\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {u}} \boldsymbol {S} _ {W} \boldsymbol {u},\tag{48}
$$

where (a) is because ${ \pmb u } ^ { \top } { \pmb S } _ { W }$ u is a scalar. The Eq. (48) which is a generalized eigenvalue problem $( S _ { B } , S _ { W } )$ (Ghojogh et al., 2019a) with u and $( { \pmb u } ^ { \top } { \pmb S } _ { B } { \pmb u } ) / ( { \pmb u } ^ { \top } { \pmb S } _ { W } { \pmb u } )$ as the eigenvector with the largest eigenvalue (because the optimization is maximization) and the corresponding eigenvalue, respectively. Therefore, the Fisher criterion is the eigenvalue ofthe Fisher direction. 

## 3.1.5. FISHER SUBSPACE: VARIANT 2

Another way to find the FDA direction is to consider another version of Fisher criterion. According to Eq. (38) for $S _ { B }$ , the Fisher criterion becomes (Welling, 2005): 

$$
\begin{array}{c} f (\boldsymbol {u}) = \frac {\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {B} \boldsymbol {u}}{\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {u}} \stackrel {(3 8)} {=} \frac {\boldsymbol {u} ^ {\top} (\boldsymbol {S} _ {T} - \boldsymbol {S} _ {W}) \boldsymbol {u}}{\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {u}} \\ = \frac {\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {T} \boldsymbol {u} - \boldsymbol {u} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {u}}{\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {u}} = \frac {\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {T} \boldsymbol {u}}{\boldsymbol {u} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {u}} - 1. \end{array}\tag{49}
$$

The −1 is a constant and is dropped in the optimization; therefore: T 

$$
\underset {\boldsymbol {u}} {\text { maximize }} \quad \boldsymbol {u} ^ {\top} \boldsymbol {S} _ {T} \boldsymbol {u}\tag{50}
$$

$$
\text { subject   to } \quad \boldsymbol {u} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {u} = 1,
$$

whose solution is similarly obtained as: 

$$
\boldsymbol {S} _ {T} \boldsymbol {u} = \lambda \boldsymbol {S} _ {W} \boldsymbol {u},\tag{51}
$$

which is a generalized eigenvalue problem $( S _ { T } , S _ { W } )$ according to (Ghojogh et al., 2019a). 

## 3.2. Multi-dimensional Subspace

In case the Fisher subspace is the span of several Fisher directions, $\{ u _ { j } \} _ { j = 1 } ^ { p }$ where $u _ { j } \in \mathbb { R } ^ { d }$ , the $d _ { B }$ and d<sub>W</sub> are defined as: 

$$
\mathbb {R} \ni d _ {B} := \mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {B} \boldsymbol {U}),\tag{52}
$$

$$
\mathbb {R} \ni d _ {W} := \mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {U}),\tag{53}
$$

where $\mathbb { R } ^ { d \times p } \ni \pmb { U } = [ \pmb { u } _ { 1 } , \dots , \pmb { u } _ { p } ]$ . In this case, maximizing the Fisher criterion is: 

$$
\underset {\boldsymbol {U}} {\text { maximize }} f (\boldsymbol {U}) := \frac {d _ {B} (\boldsymbol {U})}{d _ {W} (\boldsymbol {U})} = \frac {\mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {B} \boldsymbol {U})}{\mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {U})}.\tag{54}
$$

The Fisher criterion $f ( U )$ is a generalized Rayleigh-Ritz Quotient (see Appendix B). According to Eq. (165) in $\mathsf { A p } \cdot$ pendix B, the optimization in Eq. (54) is equivalent to: 

$$
\begin{array}{l l} \underset {\boldsymbol {U}} {\text { maximize }} & \mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {B} \boldsymbol {U}) \\ \text { subject   to } & \boldsymbol {U} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {U} = \boldsymbol {I}. \end{array}\tag{55}
$$

The Lagrangian (Boyd & Vandenberghe, 2004) is: 

$$
\mathcal {L} = \operatorname{tr} \left(\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {B} \boldsymbol {U}\right) - \operatorname{tr} \left(\boldsymbol {\Lambda} ^ {\top} \left(\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {U} - \boldsymbol {I}\right)\right),
$$

where $\pmb { \Lambda } \in \mathbb { R } ^ { d \times d }$ is a diagonal matrix whose diagonal entries are the Lagrange multipliers. Equating the derivative of L to zero gives: 

$$
\begin{array}{l} \mathbb {R} ^ {d \times p} \ni \frac {\partial \mathcal {L}}{\partial \boldsymbol {U}} = 2   \boldsymbol {S} _ {B}   \boldsymbol {U} - 2   \boldsymbol {S} _ {W}   \boldsymbol {U} \boldsymbol {\Lambda} \stackrel {{\text { set }}} {{=}} \boldsymbol {0} \\ \implies 2   \boldsymbol {S} _ {B}   \boldsymbol {U} = 2   \boldsymbol {S} _ {W}   \boldsymbol {U} \boldsymbol {\Lambda} \implies \boldsymbol {S} _ {B}   \boldsymbol {U} = \boldsymbol {S} _ {W}   \boldsymbol {U} \boldsymbol {\Lambda}, \end{array}\tag{56}
$$

which is a generalized eigenvalue problem $( S _ { B } , S _ { W } )$ according to (Ghojogh et al., 2019a). The columns of U are the eigenvectors sorted by largest to smallest eigenvalues (because the optimization is maximization) and the diagonal entries of Λ are the corresponding eigenvalues. The columns of U are referred to as the Fisher directions or Fisher axes. The projection and reconstruction are according to Eqs. (9) and (10), respectively. The out-of-sample projection and reconstruction are according to Eqs. (13) and (14), respectively. 

One possible solution to the generalized eigenvalue problem $( S _ { B } , S _ { W } )$ is (Ghojogh et al., 2019a): 

$$
\begin{array}{l} \boldsymbol {S} _ {B} \boldsymbol {U} = \boldsymbol {S} _ {W} \boldsymbol {U} \boldsymbol {\Lambda} \implies \boldsymbol {S} _ {W} ^ {- 1} \boldsymbol {S} _ {B} \boldsymbol {U} = \boldsymbol {U} \boldsymbol {\Lambda} \\ \implies \boldsymbol {U} = \mathbf {e i g} (\boldsymbol {S} _ {W} ^ {- 1} \boldsymbol {S} _ {B}), \end{array}\tag{57}
$$

where $\mathbf { e i g } ( . )$ denotes the eigenvectors of the matrix stacked column-wise. Again, we can have (Ghojogh et al., 2019a): 

$$
\boldsymbol {U} = \mathbf {e i g} ((\boldsymbol {S} _ {W} + \varepsilon \boldsymbol {I}) ^ {- 1} \boldsymbol {S} _ {B}),\tag{58}
$$

Another way to solve the optimization in Eq. (54) is taking derivative from the Fisher criterion: 

$$
\mathbb {R} ^ {d \times p} \ni \frac {\partial f (\boldsymbol {U})}{\partial \boldsymbol {U}} = \frac {1}{\left(\operatorname{tr} \left(\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {U}\right)\right) ^ {2}} \times
$$

$$
\left[ \mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {U}) (2 \boldsymbol {S} _ {B} \boldsymbol {U}) - \mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {B} \boldsymbol {U}) (2 \boldsymbol {S} _ {W} \boldsymbol {U}) \right] \stackrel {{\text { set }}} {{=}} \mathbf {0}
$$

$$
\stackrel {(a)} {\Longrightarrow} \boldsymbol {S} _ {B} \boldsymbol {U} = \frac {\mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {B} \boldsymbol {U})}{\mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {U})} \boldsymbol {S} _ {W} \boldsymbol {U},\tag{59}
$$

where (a) is because $\mathbf { t r } ( \pmb { U } ^ { \top } \pmb { S } _ { W } \pmb { U } )$ is a scalar. The Eq. (59) which is a generalized eigenvalue problem $( S _ { B } , S _ { W } )$ (Ghojogh et al., 2019a) with columns of U as the eigenvectors and $( { \pmb u } _ { j } ^ { \top } { \pmb S } _ { B } { \pmb u } _ { j } ) / ( { \pmb u } _ { j } ^ { \top } { \pmb S } _ { W } { \pmb u } _ { j } )$ as the j-th largest eigenvalue (because the optimization is maximization). 

Again, another way to find the FDA directions is to consider another version of Fisher criterion. According to Eq. (38) for $S _ { B }$ , the Fisher criterion becomes (Welling, 2005): 

$$
f (\boldsymbol {U}) = \frac {\mathbf {t r} \big (\boldsymbol {U} ^ {\top} (\boldsymbol {S} _ {T} - \boldsymbol {S} _ {W}) \boldsymbol {U} \big)}{\mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {U})} = \frac {\mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {T} \boldsymbol {U})}{\mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {U})} - 1.\tag{60}
$$

The −1 is a constant and is dropped in the optimization; therefore: 

$$
\begin{array}{l l} \underset {\boldsymbol {U}} {\text { maximize }} & \mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {T} \boldsymbol {U}) \\ \text { subject   to } & \boldsymbol {U} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {U} = \boldsymbol {I}, \end{array}\tag{61}
$$

whose solution is similarly obtained as: 

$$
\pmb {S} _ {T} \pmb {U} = \pmb {S} _ {W} \pmb {U} \pmb {\Lambda},\tag{62}
$$

which is a generalized eigenvalue problem $( S _ { T } , S _ { W } )$ according to (Ghojogh et al., 2019a). 

## 3.3. Discussion on Dimensionality of the Fisher Subspace

In general, the rank of a covariance (scatter) matrix over the d-dimensional data with sample size n is at most min $( d , n \textrm { -- } 1 )$ . The d is because the covariance matrix is a $d \times d$ matrix and the n is because we iterate over n data instances for calculating the covariance matrix. The −1 is because of subtracting the mean in calculation of the covariance matrix. For clarification, assume we only have one instance which becomes zero after removing the mean. This makes the covariance matrix a zero matrix. 

According to Eq. (33), the rank of the $\pmb { S } _ { W }$ is at most min $( d , n - 1 )$ because all the instances of all the classes are considered. Hence, the rank of $\pmb { S } _ { W }$ is also at most $\operatorname* { m i n } ( d , n - 1 )$ . According to Eq. (29), the rank of the $S _ { B }$ is at most min $( d , c - 1 )$ because we have c iterations in its calculation. 

In Eq. (57), we have $S _ { W } ^ { - 1 } S _ { B }$ whose rank is: 

$$
\begin{array}{l} \mathbf {r a n k} (S _ {W} ^ {- 1} S _ {B}) \leq \min \left(\mathbf {r a n k} (S _ {W} ^ {- 1}), \mathbf {r a n k} (S _ {B})\right) \\ \leq \min \left(\min (d, n - 1), \min (d, c - 1)\right) \\ = \min (d, n - 1, c - 1) \stackrel {(a)} {=} c - 1, \end{array}\tag{63}
$$

where (a) is because we usually have $c < d , n$ . Therefore, the rank of $S _ { W } ^ { - 1 } S _ { B }$ is limited because of the rank of $S _ { B }$ which is at most $c - 1$ 

According to Eq. (57), the c − 1 leading eigenvalues wil be valid and the rest are zero or very small. Therefore, the $p ,$ which is the dimensionality of the Fisher subspace, is at most c−1. The c−1 leading eigenvectors are considered as the Fisher directions and the rest of eigenvectors are invalid and ignored. 

## 4. Interpretation of FDA: The Example of a Man with Weak Eyes

In this section, we interpret the FDA using a real-life example in order to better understand the essence of Fisher’s method. Consider a man which has two eye problems: (1) he is color-blind and (2) his eyes are also very weak. 

Suppose there are two sets of balls with red and blue colors. The man wants to discriminate the balls into red and blue classes; however, he needs help because of his eye problems. 

First, consider his color-blindness. In order to help him, we separate the balls into two sets of red and blue. In other words, we increase the distances of the balls with different colors to give him a clue that which balls belong to the same class. This means that we are increasing the betweenscatter of the two classes to help him. 

Second, consider his very weak eyes. although the balls with different colors are almost separated, everything is blue to him. Thus, we put the balls of the same color closer to one another. In other words, we decrease the withinscatter of every class. In this way, the man sees every class as almost one blurry ball so he can discriminate the classes better. 

Recall Eq. (57) which includes $S _ { W } ^ { - 1 } S _ { B }$ . The $S _ { B }$ implies that we want to increase the between-scatter as we did in the first help. The $S _ { W } ^ { - 1 }$ implies that we want to decrease the within-scatter as done in the second help to the man. 

In conclusion, FDA increases the between-scatter and decreases the within-scatter (collapses each class (Globerson & Roweis, 2006)), at the same time, for better discrimination of the classes. 

## 5. Robust Fisher Discriminant Analysis

Robust FDA (RFDA) (Deng et al., 2007; Guo & Wang, 2015), has also addressed the problem of singularity (or close to singularity) of $S _ { W }$ . In RFDA, the $S _ { W }$ is decomposed using eigenvalue decomposition (Ghojogh et al., 2019a): 

$$
\pmb {S} _ {W} = \pmb {\Phi} ^ {\top} \pmb {\Lambda} \pmb {\Phi},\tag{64}
$$

where $\Phi$ and $\pmb { \Lambda } = \mathbf { d i a g } ( [ \lambda _ { 1 } , \ldots , \lambda _ { d } ] ^ { \top } )$ include the eigenvectors and eigenvalues of $S _ { W }$ , respectively. The eigenvalues are sorted as $\lambda _ { 1 } \geq \cdots \geq \lambda _ { d }$ and the eigenvectors (columns of $\Phi )$ are sorted accordingly. If $\pmb { S } _ { W }$ is close to singularity, the first $d ^ { \prime }$ eigenvalues are valid and the rest $( d - d ^ { \prime } )$ eigenvalues are either very small or zero. The appropriate $d ^ { \prime }$ is obtained as: 

$$
d ^ {\prime} := \arg \min _ {m} \left(\frac {\sum_ {j = 1} ^ {m} \lambda_ {j}}{\sum_ {k = 1} ^ {d} \lambda_ {k}} \geq 0. 9 8\right).\tag{65}
$$

In RFDA, the $( d - d ^ { \prime } )$ invalid eigenvalues are replaced with $\lambda _ { * } \colon$ 

$$
\mathbb {R} ^ {d \times d} \ni \boldsymbol {\Lambda} ^ {\prime} := \mathbf {d i a g} ([ \lambda_ {1}, \dots , \lambda_ {d ^ {\prime}}, \lambda_ {*}, \dots , \lambda_ {*} ] ^ {\top}),\tag{66}
$$

where (Deng et al., 2007): 

$$
\lambda_ {*} := \frac {1}{d - d ^ {\prime}} \sum_ {j = d ^ {\prime} + 1} ^ {d} \lambda_ {j}.\tag{67}
$$

Hence, the $\pmb { S } _ { W }$ is replaced with $\boldsymbol { S _ { W } ^ { \prime } }$ : 

$$
\mathbb {R} ^ {d \times d} \ni S _ {W} ^ {\prime} := \boldsymbol {\Phi} ^ {\top} \boldsymbol {\Lambda} ^ {\prime} \boldsymbol {\Phi},\tag{68}
$$

and the robust Fisher directions are the eigenvectors of the generalized eigenvalue problem $( \boldsymbol { S } _ { B } , \boldsymbol { S } _ { W } ^ { \prime } )$ (Ghojogh et al., 2019a). 

## 6. Comparison of FDA and PCA Directions

The FDA directions capture the directions where the instances of different classes fall apart and the instances in one class fall close to each other. On the other hand, the PCA directions capture the directions where the data have maximum variance (spread) regardless of the classes (Ghojogh & Crowley, 2019c). In some datasets, the FDA and PCA are orthogonal and in some datasets, they are parallel. Other cases between these two extreme cases can happen for some datasets. This depends on the spread of classes in the dataset. Figure 2 shows these cases for some twodimensional datasets. 

![image](<Images/tutorial-FDA/image_002.jpg>)



Figure 2. Comparison of FDA and PCA directions for twodimensional data with two classes: (a) a case where FDA and PCA are orthogonal, (b) a case where FDA and PCA are equivalent (parallel), and (c) a case between the two extreme cases of (a) and (b).


Moreover, considering the Eq. (38) for $S _ { B } ,$ , the Fisher criterion becomes Eqs. (49) and (60) for one-dimensional and multi-dimensional Fisher subspaces, respectively. In these equations, the −1 is a constant and is dropped in the optimization. This has an important message about FDA: the Fisher direction is maximizing the total variance (spread) of data, as also done in PCA, while at the same time, it minimizes the within-scatters of classes (by making use of the class labels). In other words, the optimization of FDA is equivalent to (we repeat Eq. (61) here): 

$$
\begin{array}{l l} \underset {\boldsymbol {U}} {\text { maximize }} & \mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {T} \boldsymbol {U}) \\ \text { subject   to } & \boldsymbol {U} ^ {\top} \boldsymbol {S} _ {W} \boldsymbol {U} = \boldsymbol {I}, \end{array}\tag{69}
$$

while the optimization of the PCA is (Ghojogh & Crowley, 2019c): 

$$
\begin{array}{l l} \underset {\boldsymbol {U}} {\text { maximize }} & \mathbf {t r} (\boldsymbol {U} ^ {\top} \boldsymbol {S} _ {T} \boldsymbol {U}) \\ \text { subject   to } & \boldsymbol {U} ^ {\top} \boldsymbol {U} = \boldsymbol {I}. \end{array}\tag{70}
$$

The solutions to Eqs. (69) and (70) are the generalized eigenvalue problem $( S _ { T } , S _ { W } )$ and the eigenvalue problem for $S _ { T }$ , respectively (Ghojogh et al., 2019a). 

## 7. FDA ≡ LDA

The FDA is also referred to as Linear Discriminant Analysis (LDA) and Fisher LDA (FLDA). Note that FDA is a manifold (subspace) learning method and LDA (Ghojogh & Crowley, 2019a) is a classification method. However, LDA can be seen as a metric learning method (Ghojogh & Crowley, 2019a) and as metric learning is a manifold learning method (see Appendix A), there is a connection between FDA and LDA. 

We know that FDA is a projection-based subspace learning method. Consider the projection vector u. According to Eq. (7), the projection of data x is: 

$$
\boldsymbol {x} \mapsto \boldsymbol {u} ^ {\top} \boldsymbol {x},\tag{71}
$$

which can be done for all the data instances of every class. Thus, the mean and the covariance matrix of the class are transformed as: 

$$
\boldsymbol {\mu} \mapsto \boldsymbol {u} ^ {\top} \boldsymbol {\mu},\tag{72}
$$

$$
\pmb {\Sigma} \mapsto \pmb {u} ^ {\top} \pmb {\Sigma} \pmb {u},\tag{73}
$$

because of characteristics of mean and variance. 

According to Eq. (42), the Fisher criterion is the ratio of the between-class variance, $\sigma _ { b } ^ { 2 } .$ , and within-class variance, $\sigma _ { w } ^ { 2 }$ : 

$$
f := \frac {\sigma_ {b} ^ {2}}{\sigma_ {w} ^ {2}} = \frac {(\boldsymbol {u} ^ {\top} \boldsymbol {\mu} _ {2} - \boldsymbol {u} ^ {\top} \boldsymbol {\mu} _ {1}) ^ {2}}{\boldsymbol {u} ^ {\top} \boldsymbol {\Sigma} _ {2} \boldsymbol {u} + \boldsymbol {u} ^ {\top} \boldsymbol {\Sigma} _ {1} \boldsymbol {u}} = \frac {(\boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})) ^ {2}}{\boldsymbol {u} ^ {\top} (\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1}) \boldsymbol {u}}.\tag{74}
$$

The FDA maximizes the Fisher criterion: 

$$
\underset {\boldsymbol {u}} {\text { maximize }} \quad \frac {\left(\boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {2}}{\boldsymbol {u} ^ {\top} (\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1})   \boldsymbol {u}},\tag{75}
$$

which can be restated as: 

$$
\begin{array}{l l} \underset {\boldsymbol {u}} {\text { maximize }} & \left(\boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {2}, \\ \text { subject   to } & \boldsymbol {u} ^ {\top} (\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1})   \boldsymbol {u} = 1, \end{array}\tag{76}
$$

according to Rayleigh-Ritz quotient method (Croot, 2005). The Lagrangian (Boyd & Vandenberghe, 2004) is: 

$$
\mathcal {L} = \left(\boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {2} - \lambda \big (\boldsymbol {u} ^ {\top} (\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1})   \boldsymbol {u} - 1 \big),
$$

where λ is the Lagrange multiplier. Equating the derivative of L to zero gives: 

$$
\begin{array}{l} \frac {\partial \mathcal {L}}{\partial \boldsymbol {u}} = 2 \left(\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1}\right) ^ {2} \boldsymbol {u} - 2 \lambda \left(\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1}\right) \boldsymbol {u} \stackrel {{\text { set }}} {{=}} \boldsymbol {0} \\ \implies \left(\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1}\right) ^ {2} \boldsymbol {u} = \lambda \left(\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1}\right) \boldsymbol {u}, \end{array}
$$

which is a generalized eigenvalue problem $\left( ( \mu _ { 2 } \textrm { -- } \right)$ $\pmb { \mu } _ { 1 } ) ^ { 2 } , ( \pmb { \Sigma } _ { 2 } + \pmb { \Sigma } _ { 1 } ) \big )$ according to (Ghojogh et al., 2019a). 

The projection vector is the eigenvector of $( \pmb { \Sigma } _ { 2 } ~ +$ $\Sigma _ { 1 } ) ^ { - 1 } ( \pmb { \mu } _ { 2 } - \pmb { \mu } _ { 1 } ) ^ { 2 }$ ; therefore, we can say: 

$$
\pmb {u} \propto (\pmb {\Sigma} _ {2} + \pmb {\Sigma} _ {1}) ^ {- 1} (\pmb {\mu} _ {2} - \pmb {\mu} _ {1}) ^ {2}.\tag{77}
$$

On the other hand, in LDA, the decision function is (Ghojogh & Crowley, 2019a): 

$$
\begin{array}{r l} & 2 \left(\boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {\top} \boldsymbol {x} \\ & \quad + \left(\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}\right) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) = 0, \end{array}\tag{78}
$$

Moreover, in LDA, the covariance matrices are assumed to be equal (Ghojogh & Crowley, 2019a): $\pmb { \Sigma } _ { 1 } = \pmb { \Sigma } _ { 2 } =$ Σ. Therefore, in LDA, the Eq. (77) becomes (Ghojogh & Crowley, 2019a): 

$$
\boldsymbol {u} \propto (2 \boldsymbol {\Sigma}) ^ {- 1} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1}) ^ {2} \propto \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1}) ^ {2}.\tag{79}
$$

According to Eq. (71), we have: 

$$
\boldsymbol {u} ^ {\top} \boldsymbol {x} \propto \left(\boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1}) ^ {2}\right) ^ {\top} \boldsymbol {x}.\tag{80}
$$

Comparing Eq. (80) with Eq. (78) shows that LDA and FDA are equivalent up to a scaling factor $( \mu _ { 1 } \textrm { -- }$ $\pmb { \mu } _ { 2 } ) ^ { \top } \pmb { \Sigma } ^ { - 1 } ( \pmb { \mu } _ { 1 } - \pmb { \mu } _ { 2 } )$ . Note that this term is multiplied as an exponential factor before taking logarithm to obtain Eq. (78), so this term a scaling factor (see (Ghojogh & Crowley, 2019a) for more details). It should be noted that in manifold (subspace) learning, the scale does not matter because all the distances scale similarly. Hence, we can say that LDA and FDA are equivalent: 

$$
\mathrm{LDA} \equiv \mathrm{FDA}.\tag{81}
$$

Therefore, the two subspaces ofFDA and LDA are the same subspace. This sheds light to why LDA and FDA are used interchangeably in the literature. 

Note that LDA assumes one (and not several) Gaussian for every class (Ghojogh & Crowley, 2019a) and so does the FDA because they are equivalent. That is why FDA faces problem for multi-modal data (Sugiyama, 2007). 

## 8. Fisher Forest

If the data include several different types of data which may even have different dimensionality. Some examples of these types of data are different key-poses in action human action recognition or different facial expressions that a face can have. In this case, we can use the Fisher forest (Ghojogh & Mohammadzade, 2017). Note that forest here does not imply an ensemble of trees but means an ensemble of the Fisher subspaces. 

Let the number of the data types be z and let the dimensionality of the `-th data type be $d _ { \lvert \ell \rvert }$ . We usually have a dataset $\{ { \pmb x } _ { i } \} _ { i = 1 } ^ { n }$ where $\pmb { x } _ { i } \in \mathbb { R } ^ { d }$ . Every type of data is the whole dataset but having only a subset of the features, i.e., $\{ \pmb { x } _ { i \mid \ell } \} _ { i = } ^ { n }$ where $\pmb { x } _ { i | \ell } \in \mathbb { R } ^ { d _ { | \ell } }$ . The features of the `-th type are a subset of the features of the dataset, i.e., $d _ { \mid \ell } \leq d .$ . Note that, we do not necessarily have the same value for $d _ { \lvert \ell }$ in all the data types. The i-th instance of the j-th class having the `-th type is denoted by $\pmb { x } _ { i \vert \ell } ^ { ( j ) }$ 

For example, in the key-poses of human action, the important of skeletal joints can be different in various key-poses (Ghojogh & Mohammadzade, 2017). Thus, some joints are taken in a specific key-joint and some other are taken in another key-pose. Note that a key-pose can have five key-joints but another key-pose can have three key-joints. Another example is using different landmarks for different facial expressions; for example, eye-brows, lips, and chin for wondering but just lips for smiling. As can be seen, Fisher forest can be useful for handling the data types with different features and even dimensionality. 

The between- and within-scatters for the `-th data types (for all $\ell \in \{ 1 , \ldots , z \} )$ are defined as (Ghojogh & Mohammadzade, 2017): 

$$
\mathbb {R} ^ {d _ {\ell} \times d _ {\ell}} \ni \boldsymbol {S} _ {B | \ell} := \sum_ {j = 1} ^ {c} n _ {j} (\boldsymbol {\mu} _ {j | \ell} - \boldsymbol {\mu} _ {| \ell}) (\boldsymbol {\mu} _ {j | \ell} - \boldsymbol {\mu} _ {| \ell}) ^ {\top},\tag{82}
$$

$$
\mathbb {R} ^ {d _ {\ell} \times d _ {\ell}} \ni \boldsymbol {S} _ {W | \ell} := \sum_ {j = 1} ^ {c} \sum_ {i = 1} ^ {n _ {j}} (\boldsymbol {x} _ {i | \ell} ^ {(j)} - \boldsymbol {\mu} _ {j | \ell}) (\boldsymbol {x} _ {i | \ell} ^ {(j)} - \boldsymbol {\mu} _ {j | \ell}) ^ {\top},\tag{83}
$$

where: 

$$
\mathbb {R} ^ {d _ {| \ell}} \ni \boldsymbol {\mu} _ {j | \ell} := \frac {1}{n _ {j}} \sum_ {i = 1} ^ {n _ {j}} \boldsymbol {x} _ {i | \ell} ^ {(j)},\tag{84}
$$

$$
\mathbb {R} ^ {d _ {| \ell}} \ni \pmb {\mu} _ {| \ell} := \frac {1}{n} \sum_ {i = 1} ^ {n} \pmb {x} _ {i | \ell}.\tag{85}
$$

The `-th Fisher subspace is spanned by the eigenvectors of $S _ { W | \ell } ^ { - 1 } S _ { B | \ell }$ 

Hence, z Fisher subspaces are trained. In the test phase, the data instance is projected onto every subspace. If we want to classify the data instance in the projected subspaces, we will have z classification results after projection onto these z subspaces. We can then use majority voting for a final classification of the data instance (Ghojogh & Mohammadzade, 2017). The effectiveness of the majority voting can be explained because of ensemble learning (Polikar, 2012; Ghojogh & Crowley, 2019b). We can also normalize the distances in the subspaces of Fisher forest for the sake of classification (see (Ghojogh & Mohammadzade, 2017) for more details). 

## 9. Kernel Fisher Discriminant Analysis

## 9.1. Kernels and Hilbert Space

Suppose that $\phi : { \pmb x }  \mathcal { H }$ is a function which maps the data x to Hilbert space (feature space). The φ is called pulling function. In other words, ${ \pmb x } \mapsto \phi ( { \pmb x } )$ . Let t denote the dimensionality of the feature space, i.e., $\phi ( { \pmb x } ) \in \mathbb { R } ^ { t }$ while $\pmb { x } \in \mathbb { R } ^ { d }$ . Note that we usually have $t \gg d .$ 

If X denotes the set of points, i.e., $\textbf { \em x } \in ~ \mathcal { X }$ , the kernel of two vectors $\scriptstyle { \mathbf { \mathscr { x } } } _ { 1 }$ and $\mathbf { \boldsymbol { x } } _ { 2 }$ is $k : \mathcal { X } \times \mathcal { X } $ R and is defined as (Hofmann et al., 2008; Herbrich, 2001): 

$$
k (\boldsymbol {x} _ {1}, \boldsymbol {x} _ {2}) := \phi (\boldsymbol {x} _ {1}) ^ {\top} \phi (\boldsymbol {x} _ {2}),\tag{86}
$$

which is a measure of similarity between the two vectors because the inner product captures similarity. 

We can compute the kernel of two matrices $\pmb { X } _ { 1 } \in \mathbb { R } ^ { d \times n _ { 1 } }$ and $\pmb { X } _ { 2 } \in \mathbb { R } ^ { d \times n _ { 2 } }$ and have a kernel matrix (also called Gram matrix): 

$$
\mathbb {R} ^ {n _ {1} \times n _ {2}} \ni \boldsymbol {K} (\boldsymbol {X} _ {1}, \boldsymbol {X} _ {2}) := \boldsymbol {\Phi} (\boldsymbol {X} _ {1}) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X} _ {2}),\tag{87}
$$

where $\Phi ( X _ { 1 } ) : = [ \phi ( \pmb { x } _ { 1 } ) , \dots , \phi ( \pmb { x } _ { n } ) ] \in \mathbb { R } ^ { t \times n _ { 1 } }$ is the matrix of mapped $X _ { 1 }$ to the feature space. The $\Phi ( \pmb { X } _ { 2 } ) ~ \in$ $\mathbb { R } ^ { t \times n _ { 2 } }$ is defined similarly. We can compute the kernel matrix of dataset $\boldsymbol { X } \in \mathbb { R } ^ { d \times \dot { n } }$ over itself: 

$$
\mathbb {R} ^ {n \times n} \ni \boldsymbol {K} _ {x} := \boldsymbol {K} (\boldsymbol {X}, \boldsymbol {X}) = \boldsymbol {\Phi} (\boldsymbol {X}) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X}),\tag{88}
$$

where $\Phi ( X ) : = [ \phi (  { \mathbf { x } } _ { 1 } ) , \dots , \phi (  { \mathbf { x } } _ { n } ) ] \in \mathbb { R } ^ { t \times n }$ is the pulled (mapped) data. 

Note that in kernel methods, the pulled data $\Phi ( X )$ are usually not available and merely the kernel matrix $\pmb { K } ( \pmb { X } , \pmb { X } )$ which is the inner product of the pulled data with itself, is available. 

There exist different types of kernels. Some of the most well-known kernels are: 

$$
\text { Linear: } k (\boldsymbol {x} _ {1}, \boldsymbol {x} _ {2}) = \boldsymbol {x} _ {1} ^ {\top} \boldsymbol {x} _ {2} + c _ {1},\tag{89}
$$

$$
\text { Polynomial: } k (\boldsymbol {x} _ {1}, \boldsymbol {x} _ {2}) = (c _ {1} \boldsymbol {x} _ {1} ^ {\top} \boldsymbol {x} _ {2} + c _ {2}) ^ {c _ {3}},\tag{90}
$$

$$
\text { Gaussian: } k (\boldsymbol {x} _ {1}, \boldsymbol {x} _ {2}) = \exp \left(- \frac {| | \boldsymbol {x} _ {1} - \boldsymbol {x} _ {2} | | _ {2} ^ {2}}{2 \sigma^ {2}}\right),\tag{91}
$$

$$
\text { Sigmoid: } k (\boldsymbol {x} _ {1}, \boldsymbol {x} _ {2}) = \tanh (c _ {1} \boldsymbol {x} _ {1} ^ {\top} \boldsymbol {x} _ {2} + c _ {2}),\tag{92}
$$

where $c _ { 1 } , c _ { 2 } , c _ { 3 }$ , and σ are scalar constants. The Gaussian and Sigmoid kernels are also called Radial Basis Function (RBF) and hyperbolic tangent, respectively. Note that the Gaussian kernel can also be written as exp $\left( - \gamma | | \pmb { x } _ { 1 } - \pmb { x } _ { 2 } | | _ { 2 } ^ { 2 } \right)$ where $\gamma > 0$ 

It is noteworthy to mention that in the RBF kernel, the dimensionality of the feature space is infinite. The reason lies in the Maclaurin series expansion (Taylor series expansion at zero) of this kernel: 

$$
\exp (- \gamma r) \approx 1 - \gamma r + \frac {\gamma^ {2}}{2 !} r ^ {2} - \frac {\gamma^ {3}}{3 !} r ^ {3} + \ldots ,
$$

where $r : = | | \pmb { x } _ { 1 } - \pmb { x } _ { 2 } | | _ { 2 } ^ { 2 }$ , which is infinite dimensional with respect to r. 

## 9.2. One-dimensional Subspace

## 9.2.1. SCATTERS IN TWO-CLASS CASE

The Eq. (26) in the feature space is: 

$$
\begin{array}{c} \mathbb {R} ^ {t \times t} \ni \Phi (\boldsymbol {S} _ {B}) := \\ \left(\phi (\boldsymbol {\mu} _ {1}) - \phi (\boldsymbol {\mu} _ {2})\right) \left(\phi (\boldsymbol {\mu} _ {1}) - \phi (\boldsymbol {\mu} _ {2})\right) ^ {\top}, \end{array}\tag{93}
$$

where the mean of the $j \cdot$ th class in the feature space is: 

$$
\mathbb {R} ^ {t} \ni \phi (\boldsymbol {\mu} _ {j}) := \frac {1}{n _ {j}} \sum_ {i = 1} ^ {n _ {j}} \phi (\boldsymbol {x} _ {i} ^ {(j)}).\tag{94}
$$

According to the representation theory (Alperin, 1993), any solution (direction) $\phi ( \pmb { u } ) ~ \in ~ \mathcal { H }$ must lie in the span of $ { \mathbf { \hat { \mu } } } ^ { 6 6 }  { \mathrm { a l l } } ^ { 5 }$ the training vectors mapped to ${ \mathcal { H } } , \operatorname { i . e . } , \Phi ( X ) =$ $[ \phi ( \pmb { x } _ { 1 } ) , \dots , \phi ( \pmb { x } _ { n } ) ] \ \in \ \mathbb { R } ^ { t \times n }$ (usually $t \gg d )$ . Note that H denotes the Hilbert space (feature space). Therefore, we can state that: 

$$
\mathbb {R} ^ {t} \ni \phi (\boldsymbol {u}) = \sum_ {i = 1} ^ {n} \theta_ {i} \phi (\boldsymbol {x} _ {i}) = \Phi (\boldsymbol {X}) \boldsymbol {\theta},\tag{95}
$$

where $\mathbb { R } ^ { n } \ni \pmb { \theta } : = [ \theta _ { 1 } , . . . , \theta _ { n } ] ^ { \top }$ is the unknown vector of coefficients, and $\boldsymbol { \phi } ( \boldsymbol { u } ) \in \mathbb { R } ^ { t }$ is the pulled Fisher direction to the feature space. The pulled directions can be put together in $\mathbb { R } ^ { t \times p } \ni \Phi ( U ) : = [ \phi ( \boldsymbol { u } _ { 1 } ) , \ldots , \phi ( \boldsymbol { u } _ { p } ) ]$ 

$$
\mathbb {R} ^ {t \times p} \ni \Phi (\boldsymbol {U}) = \Phi (\boldsymbol {X}) \Theta ,\tag{96}
$$

where $\pmb { \Theta } : = [ \pmb { \theta } _ { 1 } , \dots , \pmb { \theta } _ { p } ] \in \mathbb { R } ^ { n \times p }$ 

The $d _ { B }$ in the feature space is: 

$$
\mathbb {R} \ni d _ {B} := \boldsymbol {\phi} (\boldsymbol {u}) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {S} _ {B}) \boldsymbol {\phi} (\boldsymbol {u})\tag{97}
$$

$$
\stackrel {(a)} {=} \boldsymbol {\theta} ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X}) ^ {\top} \bigl (\phi (\boldsymbol {\mu} _ {1}) - \phi (\boldsymbol {\mu} _ {2}) \bigr)
$$

$$
\left(\phi (\boldsymbol {\mu} _ {1}) - \phi (\boldsymbol {\mu} _ {2})\right) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X}) \boldsymbol {\theta},\tag{98}
$$

where (a) is because of Eqs. (93). and (95). 

For the j-th class (here $j \in \{ 1 , 2 \} )$ , we have: 

$$
\boldsymbol {\theta} ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X}) ^ {\top} \phi (\boldsymbol {\mu} _ {j}) \stackrel {(9 5)} {=} \sum_ {i = 1} ^ {n} \theta_ {i} \phi (\boldsymbol {x} _ {i}) ^ {\top} \phi (\boldsymbol {\mu} _ {j})
$$

$$
\stackrel {(9 4)} {=} \frac {1}{n _ {j}} \sum_ {i = 1} ^ {n} \sum_ {k = 1} ^ {n _ {j}} \theta_ {i} \boldsymbol {\phi} (\boldsymbol {x} _ {i}) ^ {\top} \boldsymbol {\phi} (\boldsymbol {x} _ {k} ^ {(j)})
$$

$$
\stackrel {(8 6)} {=} \frac {1}{n _ {j}} \sum_ {i = 1} ^ {n} \sum_ {k = 1} ^ {n _ {j}} \theta_ {i} k (\boldsymbol {x} _ {i}, \boldsymbol {x} _ {k} ^ {(j)}) = \boldsymbol {\theta} ^ {\top} \boldsymbol {m} _ {j},\tag{99}
$$

where $m _ { j } \in \mathbb { R } ^ { n }$ whose i-th entry is: 

$$
\boldsymbol {m} _ {j} (i) := \frac {1}{n _ {j}} \sum_ {k = 1} ^ {n _ {j}} k (\boldsymbol {x} _ {i}, \boldsymbol {x} _ {k} ^ {(j)}).\tag{100}
$$

Hence, Eq. (98) becomes: 

$$
d _ {B} \stackrel {(9 9)} {=} \boldsymbol {\theta} ^ {\top} (\boldsymbol {m} _ {1} - \boldsymbol {m} _ {2}) (\boldsymbol {m} _ {1} - \boldsymbol {m} _ {2}) ^ {\top} \boldsymbol {\theta} = \boldsymbol {\theta} ^ {\top} M \boldsymbol {\theta},\tag{101}
$$

where: 

$$
\mathbb {R} ^ {n \times n} \ni M := (\boldsymbol {m} _ {1} - \boldsymbol {m} _ {2}) (\boldsymbol {m} _ {1} - \boldsymbol {m} _ {2}) ^ {\top},\tag{102}
$$

is the between-scatter in kernel FDA. Hence, the Eq. (98) becomes: 

$$
d _ {B} = \phi (\pmb {u}) ^ {\top} \pmb {\Phi} (\pmb {S} _ {B}) \phi (\pmb {u}) = \pmb {\theta} ^ {\top} M \pmb {\theta}.\tag{103}
$$

The Eq. (33) in the feature space is: 

$$
\begin{array}{l} \mathbb {R} ^ {t \times t} \ni \Phi (\boldsymbol {S} _ {W}) := \\ \sum_ {j = 1} ^ {c} \sum_ {i = 1} ^ {n _ {j}} \bigl (\phi (\boldsymbol {x} _ {i} ^ {(j)}) - \phi (\boldsymbol {\mu} _ {j}) \bigr) \bigl (\phi (\boldsymbol {x} _ {i} ^ {(j)}) - \phi (\boldsymbol {\mu} _ {j}) \bigr) ^ {\top}. \end{array}\tag{104}
$$

The $d _ { W }$ in the feature space is: 

$$
\begin{array}{l} \mathbb {R} \ni d _ {W} := \boldsymbol {\phi} (\boldsymbol {u}) ^ {\top} \boldsymbol {\Phi} (S _ {W})   \boldsymbol {\phi} (\boldsymbol {u}) \\ \stackrel {(a)} {=} \Big (\sum_ {\ell = 1} ^ {n} \theta_ {\ell}   \boldsymbol {\phi} (\boldsymbol {x} _ {\ell}) ^ {\top} \Big) \Big (\sum_ {j = 1} ^ {c} \sum_ {i = 1} ^ {n _ {j}} \big (\boldsymbol {\phi} (\boldsymbol {x} _ {i} ^ {(j)}) - \boldsymbol {\phi} (\boldsymbol {\mu} _ {j}) \big) \\ \qquad \qquad \qquad \big (\boldsymbol {\phi} (\boldsymbol {x} _ {i} ^ {(j)}) - \boldsymbol {\phi} (\boldsymbol {\mu} _ {j}) \big) ^ {\top} \Big) \Big (\sum_ {k = 1} ^ {n} \theta_ {k}   \boldsymbol {\phi} (\boldsymbol {x} _ {k}) \Big) \\ = \sum_ {j = 1} ^ {c} \sum_ {\ell = 1} ^ {n} \sum_ {i = 1} ^ {n _ {j}} \sum_ {k = 1} ^ {n} \Big (\theta_ {\ell}   \boldsymbol {\phi} (\boldsymbol {x} _ {\ell}) ^ {\top} \big (\boldsymbol {\phi} (\boldsymbol {x} _ {i} ^ {(j)}) - \boldsymbol {\phi} (\boldsymbol {\mu} _ {j}) \big) \\ \qquad \qquad \qquad \big (\boldsymbol {\phi} (\boldsymbol {x} _ {i} ^ {(j)}) - \boldsymbol {\phi} (\boldsymbol {\mu} _ {j}) \big) ^ {\top} \theta_ {k}   \boldsymbol {\phi} (\boldsymbol {x} _ {k}) \Big) \end{array}
$$

$$
\begin{array}{l}\stackrel {(9 4)} {=} \sum_ {j = 1} ^ {c} \sum_ {\ell = 1} ^ {n} \sum_ {i = 1} ^ {n _ {j}} \sum_ {k = 1} ^ {n}\\\left(\theta_ {\ell} \phi (\boldsymbol {x} _ {\ell}) ^ {\top} \big (\phi (\boldsymbol {x} _ {i} ^ {(j)}) - \frac {1}{n _ {j}} \sum_ {e = 1} ^ {n _ {j}} \phi (\boldsymbol {x} _ {e} ^ {(j)})\right)\\\left(\phi (\boldsymbol {x} _ {i} ^ {(j)}) - \frac {1}{n _ {j}} \sum_ {z = 1} ^ {n _ {j}} \phi (\boldsymbol {x} _ {z} ^ {(j)})\right) ^ {\top} \theta_ {k} \phi (\boldsymbol {x} _ {k})\left. \right)\end{array}
$$

$$
\begin{array}{l} \stackrel {(8 6)} {=} \sum_ {j = 1} ^ {c} \sum_ {\ell = 1} ^ {n} \sum_ {i = 1} ^ {n _ {j}} \sum_ {k = 1} ^ {n} \\ \left(\theta_ {\ell} k (\boldsymbol {x} _ {\ell}, \boldsymbol {x} _ {i} ^ {(j)}) - \frac {1}{n _ {j}} \sum_ {e = 1} ^ {n _ {j}} \theta_ {\ell} k (\boldsymbol {x} _ {\ell}, \boldsymbol {x} _ {e} ^ {(j)})\right) \\ \left(\theta_ {k} k (\boldsymbol {x} _ {i} ^ {(j)}, \boldsymbol {x} _ {k}) - \frac {1}{n _ {j}} \sum_ {z = 1} ^ {n _ {j}} \theta_ {k} k (\boldsymbol {x} _ {z} ^ {(j)}, \boldsymbol {x} _ {k})\right) \end{array}
$$

$$
\begin{array}{r l} \stackrel {(b)} {=} & \sum_ {j = 1} ^ {c} \sum_ {\ell = 1} ^ {n} \sum_ {i = 1} ^ {n _ {j}} \sum_ {k = 1} ^ {n} \\ & \left(\theta_ {\ell}   k (\boldsymbol {x} _ {\ell}, \boldsymbol {x} _ {i} ^ {(j)}) - \frac {1}{n _ {j}} \sum_ {e = 1} ^ {n _ {j}} \theta_ {\ell}   k (\boldsymbol {x} _ {\ell}, \boldsymbol {x} _ {e} ^ {(j)})\right) \\ & \left(\theta_ {k}   k (\boldsymbol {x} _ {k}, \boldsymbol {x} _ {i} ^ {(j)}) - \frac {1}{n _ {j}} \sum_ {z = 1} ^ {n _ {j}} \theta_ {k}   k (\boldsymbol {x} _ {k}, \boldsymbol {x} _ {z} ^ {(j)})\right) \end{array}
$$

$$
\begin{array}{l}= \sum_ {j = 1} ^ {c} \sum_ {\ell = 1} ^ {n} \sum_ {i = 1} ^ {n _ {j}} \sum_ {k = 1} ^ {n}\\\left(\theta_ {\ell} \theta_ {k} k (\pmb {x} _ {\ell}, \pmb {x} _ {i} ^ {(j)}) k (\pmb {x} _ {k}, \pmb {x} _ {i} ^ {(j)}) \right.\\- \frac {2 \theta_ {\ell} \theta_ {k}}{n _ {j}} \sum_ {z = 1} ^ {n _ {j}} k (\pmb {x} _ {\ell}, \pmb {x} _ {i} ^ {(j)}) k (\pmb {x} _ {k}, \pmb {x} _ {z} ^ {(j)})\\+ \frac {\theta_ {\ell} \theta_ {k}}{n _ {j} ^ {2}} \sum_ {e = 1} ^ {n _ {j}} \sum_ {z = 1} ^ {n _ {j}} k (\pmb {x} _ {\ell}, \pmb {x} _ {e} ^ {(j)}) k (\pmb {x} _ {k}, \pmb {x} _ {z} ^ {(j)})\left. \right)\end{array}
$$

$$
\begin{array}{l} = \sum_ {j = 1} ^ {c} \sum_ {\ell = 1} ^ {n} \sum_ {i = 1} ^ {n _ {j}} \sum_ {k = 1} ^ {n} \\ \left(\theta_ {\ell}   \theta_ {k}   k (\boldsymbol {x} _ {\ell}, \boldsymbol {x} _ {i} ^ {(j)})   k (\boldsymbol {x} _ {k}, \boldsymbol {x} _ {i} ^ {(j)}) \right. \\ \left. - \frac {\theta_ {\ell}   \theta_ {k}}{n _ {j}} \sum_ {z = 1} ^ {n _ {j}} k (\boldsymbol {x} _ {\ell}, \boldsymbol {x} _ {i} ^ {(j)})   k (\boldsymbol {x} _ {k}, \boldsymbol {x} _ {z} ^ {(j)})\right) \\ = \sum_ {j = 1} ^ {c} \left(\sum_ {\ell = 1} ^ {n} \sum_ {i = 1} ^ {n _ {j}} \sum_ {k = 1} ^ {n} \left(\theta_ {\ell}   \theta_ {k}   k (\boldsymbol {x} _ {\ell}, \boldsymbol {x} _ {i} ^ {(j)})   k (\boldsymbol {x} _ {k}, \boldsymbol {x} _ {i} ^ {(j)})\right) \right. \\ \left. - \sum_ {\ell = 1} ^ {n} \sum_ {i = 1} ^ {n _ {j}} \sum_ {k = 1} ^ {n} \left(\frac {\theta_ {\ell}   \theta_ {k}}{n _ {j}} \sum_ {z = 1} ^ {n _ {j}} k (\boldsymbol {x} _ {\ell}, \boldsymbol {x} _ {i} ^ {(j)})   k (\boldsymbol {x} _ {k}, \boldsymbol {x} _ {z} ^ {(j)})\right)\right) \end{array}
$$

$$
\begin{array}{l} \stackrel {(c)} {=} \sum_ {j = 1} ^ {c} \left(\boldsymbol {\theta} ^ {\top} \boldsymbol {K} _ {j} \boldsymbol {K} _ {j} ^ {\top} \boldsymbol {\theta} - \boldsymbol {\theta} ^ {\top} \boldsymbol {K} _ {j} \frac {1}{n _ {j}} \mathbf {1 1} ^ {\top} \boldsymbol {K} _ {j} ^ {\top} \boldsymbol {\theta}\right) \\ = \sum_ {j = 1} ^ {c} \boldsymbol {\theta} ^ {\top} \boldsymbol {K} _ {j} \left(\boldsymbol {I} - \frac {1}{n _ {j}} \mathbf {1 1} ^ {\top}\right) \boldsymbol {K} _ {j} ^ {\top} \boldsymbol {\theta} \\ \stackrel {(d)} {=} \sum_ {j = 1} ^ {c} \boldsymbol {\theta} ^ {\top} \boldsymbol {K} _ {j} \boldsymbol {H} _ {j} \boldsymbol {K} _ {j} ^ {\top} \boldsymbol {\theta} = \boldsymbol {\theta} ^ {\top} \left(\sum_ {j = 1} ^ {c} \boldsymbol {K} _ {j} \boldsymbol {H} _ {j} \boldsymbol {K} _ {j} ^ {\top}\right) \boldsymbol {\theta}, \end{array}
$$

where (a) is because of Eqs. (104) and (95), (b) is because $k ( \pmb { x } _ { 1 } , \pmb { x } _ { 2 } ) = k ( \pmb { x } _ { 2 } , \pmb { x } _ { 1 } ) \in \mathbb { R }$ , and (c) is because $K _ { j } \in$ $\mathbb { R } ^ { n \times n _ { j } }$ is the kernel matrix of the whole training data and the training data of the j-th class. The (a, b)-th element of $K _ { j }$ is: 

$$
\pmb {K} _ {j} (a, b) := k (\pmb {x} _ {a}, \pmb {x} _ {b} ^ {(j)}).\tag{105}
$$

The (d) is because: 

$$
\mathbb {R} ^ {n _ {j} \times n _ {j}} \ni \boldsymbol {H} _ {j} := \boldsymbol {I} - \frac {1}{n _ {j}} \boldsymbol {1 1} ^ {\top},\tag{106}
$$

is the centering matrix (see Appendix A in (Ghojogh & Crowley, 2019c)). 

We define: 

$$
\mathbb {R} ^ {n \times n} \ni \boldsymbol {N} := \sum_ {j = 1} ^ {c} \boldsymbol {K} _ {j} \boldsymbol {H} _ {j} \boldsymbol {K} _ {j} ^ {\top},\tag{107}
$$

as the within-scatter in kernel FDA. Hence, the $d _ { W }$ becomes: 

$$
d _ {W} = \boldsymbol {\phi} (\boldsymbol {u}) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {S} _ {W}) \boldsymbol {\phi} (\boldsymbol {u}) = \boldsymbol {\theta} ^ {\top} \boldsymbol {N} \boldsymbol {\theta}.\tag{108}
$$

The kernel Fisher criterion is: 

$$
f (\boldsymbol {\theta}) := \frac {d _ {B} (\boldsymbol {\theta})}{d _ {W} (\boldsymbol {\theta})} = \frac {\phi (\boldsymbol {u}) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {S} _ {B}) \phi (\boldsymbol {u})}{\phi (\boldsymbol {u}) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {S} _ {W}) \phi (\boldsymbol {u})} = \frac {\boldsymbol {\theta} ^ {\top} \boldsymbol {M} \boldsymbol {\theta}}{\boldsymbol {\theta} ^ {\top} \boldsymbol {N} \boldsymbol {\theta}},\tag{109}
$$

where the $\pmb { \theta } \in \mathbb { R } ^ { n }$ is the kernel Fisher direction. 

Similar to the solution of Eq. (42), the solution to maximization of Eq. (109) is: 

$$
\boldsymbol {M} \boldsymbol {\theta} = \lambda \boldsymbol {N} \boldsymbol {\theta},\tag{110}
$$

which is a generalized eigenvalue problem $( M , N )$ according to (Ghojogh et al., 2019a). The θ is the eigenvector with the largest eigenvalue (because the optimization is maximization) and the λ is the corresponding eigenvalue. The θ is the kernel Fisher direction or kernel Fisher axis. 

Again, one possible solution to the generalized eigenvalue problem (M, N) is (Ghojogh et al., 2019a): 

$$
\boldsymbol {\theta} = \mathbf {e i g} (\boldsymbol {N} ^ {- 1} \boldsymbol {M}),\tag{111}
$$

or (Ghojogh et al., 2019a): 

$$
\boldsymbol {\theta} = \mathbf {e i g} ((\boldsymbol {N} + \varepsilon \boldsymbol {I}) ^ {- 1} \boldsymbol {M}),\tag{112}
$$

where $\mathbf { e i g } ( . )$ denotes the eigenvector of the matrix with the largest eigenvalue. 

The projection and reconstruction of the training data poin $\mathbf { \Delta } _ { \mathbf { \mathcal { X } } _ { i } }$ and the out-of-sample data point $\mathbf { \Delta } _ { \mathbf { \mathcal { X } } _ { t } }$ are: 

$$
\begin{array}{r l} \mathbb {R} \ni \phi (\widetilde {\boldsymbol {x}} _ {i}) & = \phi (\boldsymbol {u}) ^ {\top} \phi (\boldsymbol {x} _ {i}) \stackrel {(9 5)} {=} \boldsymbol {\theta} ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X}) ^ {\top} \phi (\boldsymbol {x} _ {i}) \\ & = \boldsymbol {\theta} ^ {\top} \boldsymbol {k} (\boldsymbol {X}, \boldsymbol {x} _ {i}), \end{array}\tag{113}
$$

$$
\mathbb {R} ^ {t} \ni \phi (\widehat {\boldsymbol {x}} _ {i}) = \phi (\boldsymbol {u}) \phi (\boldsymbol {u}) ^ {\top} \phi (\boldsymbol {x} _ {i})
$$

$$
\stackrel {(9 5)} {=} \boldsymbol {\Phi} (\boldsymbol {X}) \boldsymbol {\theta} \boldsymbol {\theta} ^ {\top} \boldsymbol {k} (\boldsymbol {X}, \boldsymbol {x} _ {i}),\tag{114}
$$

$$
\mathbb {R} \ni \phi (\widetilde {\boldsymbol {x}} _ {t}) = \boldsymbol {\theta} ^ {\top} \boldsymbol {k} (\boldsymbol {X}, \boldsymbol {x} _ {t}),\tag{115}
$$

$$
\mathbb {R} ^ {t} \ni \phi (\widehat {\boldsymbol {x}} _ {t}) = \Phi (\boldsymbol {X}) \boldsymbol {\theta} \boldsymbol {\theta} ^ {\top} \boldsymbol {k} (\boldsymbol {X}, \boldsymbol {x} _ {t}).\tag{116}
$$

However, in reconstruction expressions, the $\Phi ( X )$ is not necessarily available; therefore, in kernel FDA, similar to kernel PCA (Ghojogh & Crowley, 2019c), reconstruction cannot be done. For the whole training and out-of-sample data, the projections are: 

$$
\mathbb {R} ^ {1 \times n} \ni \boldsymbol {\Phi} (\widetilde {\boldsymbol {X}}) = \boldsymbol {\theta} ^ {\top} \boldsymbol {K} (\boldsymbol {X}, \boldsymbol {X}),\tag{117}
$$

$$
\mathbb {R} ^ {1 \times n _ {t}} \ni \boldsymbol {\Phi} (\widetilde {\boldsymbol {X}} _ {t}) = \boldsymbol {\theta} ^ {\top} \boldsymbol {K} (\boldsymbol {X}, \boldsymbol {X} _ {t}).\tag{118}
$$

9.2.2. SCATTERS IN MULTI-CLASS CASE: VARIANT 1 In multi-class case for kernel FDA, the within-scatter is the same as in the two-class case, which is Eq. (107) and $d _ { W }$ is also Eq. (108). However, the between-scatter is different. The between-scatter, Eq. (29), in the feature space is: 

$$
\begin{array}{l} \mathbb {R} ^ {t \times t} \ni \Phi (\boldsymbol {S} _ {B}) := \\ \sum_ {j = 1} ^ {c} \left(\phi (\boldsymbol {\mu} _ {j}) - \phi (\boldsymbol {\mu})\right) \left(\phi (\boldsymbol {\mu} _ {j}) - \phi (\boldsymbol {\mu})\right) ^ {\top}, \end{array}\tag{119}
$$

where the total mean in the feature space is: 

$$
\mathbb {R} ^ {t} \ni \phi (\boldsymbol {\mu}) := \frac {1}{\sum_ {k = 1} ^ {c} n _ {k}} \sum_ {j = 1} ^ {c} n _ {j} \phi (\boldsymbol {\mu} _ {j}) = \frac {1}{n} \sum_ {i = 1} ^ {n} \phi (\boldsymbol {x} _ {i}),\tag{120}
$$

The $d _ { B }$ in the feature space is: 

$$
\begin{array}{l} \mathbb {R} \ni d _ {B} := \phi (\boldsymbol {u}) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {S} _ {B})   \phi (\boldsymbol {u}) \\ \stackrel {(a)} {=} \sum_ {j = 1} ^ {c} \boldsymbol {\theta} ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X}) ^ {\top} \big (\phi (\boldsymbol {\mu} _ {j}) - \phi (\boldsymbol {\mu}) \big) \\ \qquad \qquad \qquad \qquad \big (\phi (\boldsymbol {\mu} _ {j}) - \phi (\boldsymbol {\mu}) \big) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X})   \boldsymbol {\theta}, \end{array}\tag{121}
$$

where (a) is because of Eqs. (119) and (95). We have: 

$$
\begin{array}{l} \boldsymbol {\theta} ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X}) ^ {\top} \boldsymbol {\phi} (\boldsymbol {\mu}) \stackrel {(9 5)} {=} \sum_ {i = 1} ^ {n} \theta_ {i}   \boldsymbol {\phi} (\boldsymbol {x} _ {i}) ^ {\top} \boldsymbol {\phi} (\boldsymbol {\mu}) \\ \stackrel {(1 2 0)} {=} \frac {1}{n} \sum_ {i = 1} ^ {n} \sum_ {k = 1} ^ {n} \theta_ {i}   \boldsymbol {\phi} (\boldsymbol {x} _ {i}) ^ {\top} \boldsymbol {\phi} (\boldsymbol {x} _ {k}) \\ \stackrel {(8 6)} {=} \frac {1}{n} \sum_ {i = 1} ^ {n} \sum_ {k = 1} ^ {n} \theta_ {i}   k (\boldsymbol {x} _ {i}, \boldsymbol {x} _ {k}) = \boldsymbol {\theta} ^ {\top} \boldsymbol {m} _ {*}, \end{array}\tag{122}
$$

where $m _ { * } \in \mathbb { R } ^ { n }$ whose i-th entry is: 

$$
\boldsymbol {m} _ {*} (i) := \frac {1}{n} \sum_ {k = 1} ^ {n} k (\boldsymbol {x} _ {i}, \boldsymbol {x} _ {k}).\tag{123}
$$

According to Eqs. (99) and (122), the Eq. (121) becomes: 

$$
d _ {B} = \boldsymbol {\theta} ^ {\top} \sum_ {j = 1} ^ {c} (\boldsymbol {m} _ {j} - \boldsymbol {m} _ {*}) (\boldsymbol {m} _ {j} - \boldsymbol {m} _ {*}) ^ {\top} \boldsymbol {\theta} = \boldsymbol {\theta} ^ {\top} M \boldsymbol {\theta},\tag{124}
$$

where: 

$$
\mathbb {R} ^ {n \times n} \ni M := \sum_ {j = 1} ^ {c} (\boldsymbol {m} _ {j} - \boldsymbol {m} _ {*}) (\boldsymbol {m} _ {j} - \boldsymbol {m} _ {*}) ^ {\top},\tag{125}
$$

is the between-scatter in kernel FDA. Similar to Eq. (31), some researches consider the following instead: 

$$
\mathbb {R} ^ {n \times n} \ni M := \sum_ {j = 1} ^ {c} n _ {j} \left(\boldsymbol {m} _ {j} - \boldsymbol {m} _ {*}\right) \left(\boldsymbol {m} _ {j} - \boldsymbol {m} _ {*}\right) ^ {\top}.\tag{126}
$$

Hence, the Eq. (121) becomes: 

$$
d _ {B} = \boldsymbol {\phi} (\boldsymbol {u}) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {S} _ {B}) \boldsymbol {\phi} (\boldsymbol {u}) = \boldsymbol {\theta} ^ {\top} \boldsymbol {M} \boldsymbol {\theta},\tag{127}
$$

where M here is Eq. (125) or (126). 

The Fisher direction is again Eq. (109) and the solution is again the generalized eigenvalue problem (M, N) according to (Ghojogh et al., 2019a). 

## 9.2.3. SCATTERS IN MULTI-CLASS CASE: VARIANT 2

Again, in the second version of multi-class case for kerne FDA, the within-scatter is the same as in the two-class case, which is Eq. (107) and d is also Eq. (108). 

For the between scatter in in the second version, we start with the Eqs. (49) and (50). We kernelize the objective function of the Eq. (50): 

$$
d _ {T} := \boldsymbol {\phi} (\boldsymbol {u}) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {S} _ {T}) \boldsymbol {\phi} (\boldsymbol {u}),\tag{128}
$$

where total-scatter, Eq. (36), is pulled as: 

$$
\begin{array}{l} \mathbb {R} ^ {t \times t} \ni \Phi (\boldsymbol {S} _ {T}) := \\ \sum_ {k = 1} ^ {n} \left(\phi (\boldsymbol {x} _ {k}) - \phi (\boldsymbol {\mu})\right) \left(\phi (\boldsymbol {x} _ {k}) - \phi (\boldsymbol {\mu})\right) ^ {\top}. \end{array}\tag{129}
$$

According to Eqs. (95), (128), and (129), we have: 

$$
\begin{array}{c} d _ {T} = \sum_ {k = 1} ^ {n} \boldsymbol {\theta} ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X}) ^ {\top} \bigl (\phi (\boldsymbol {x} _ {k}) - \phi (\boldsymbol {\mu}) \bigr) \\ \bigl (\phi (\boldsymbol {x} _ {k}) - \phi (\boldsymbol {\mu}) \bigr) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X})   \boldsymbol {\theta}. \end{array}
$$

According to Eq. (122), we have: 

$$
\boldsymbol {\theta} ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X}) ^ {\top} \phi (\boldsymbol {\mu}) = \boldsymbol {\theta} ^ {\top} \boldsymbol {m} _ {*},\tag{130}
$$

where m<sub>∗</sub> is Eq. (123). On the other hand, we have: 

$$
\begin{array}{r l} \boldsymbol {\theta} ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X}) ^ {\top} \boldsymbol {\phi} (\boldsymbol {x} _ {k}) & \stackrel {(9 5)} {=} \sum_ {i = 1} ^ {n} \theta_ {i} \boldsymbol {\phi} (\boldsymbol {x} _ {i}) ^ {\top} \boldsymbol {\phi} (\boldsymbol {x} _ {k}) \\ & \stackrel {(8 6)} {=} \sum_ {i = 1} ^ {n} \theta_ {i} k (\boldsymbol {x} _ {i}, \boldsymbol {x} _ {k}) = \boldsymbol {\theta} ^ {\top} \boldsymbol {g} _ {k}, \end{array}\tag{131}
$$

where $\mathbf { \Delta } _ { \mathbf { { g } } _ { k } } \in \mathbb { R } ^ { n }$ whose i-th entry is: 

$$
\boldsymbol {g} _ {k} (i) := k (\boldsymbol {x} _ {i}, \boldsymbol {x} _ {k}).\tag{132}
$$

Hence: 

$$
d _ {T} = \sum_ {k = 1} ^ {n} \boldsymbol {\theta} ^ {\top} (\boldsymbol {g} _ {k} - \boldsymbol {m} _ {*}) (\boldsymbol {g} _ {k} - \boldsymbol {m} _ {*}) ^ {\top} \boldsymbol {\theta} = \boldsymbol {\theta} ^ {\top} \boldsymbol {G} \boldsymbol {\theta},\tag{133}
$$

where: 

$$
\mathbb {R} ^ {n \times n} \ni \boldsymbol {G} := \sum_ {k = 1} ^ {n} (\boldsymbol {g} _ {k} - \boldsymbol {m} _ {*}) (\boldsymbol {g} _ {k} - \boldsymbol {m} _ {*}) ^ {\top}.\tag{134}
$$

The denominator of the Fisher criterion in the feature space is again the Eq. (108). 

The optimization will be similar to Eq. (50) but in the feature space: 

$$
\begin{array}{l l} \underset {\boldsymbol {\theta}} {\text { maximize }} & \boldsymbol {\theta} ^ {\top} \boldsymbol {G}   \boldsymbol {\theta} \\ \text { subject   to } & \boldsymbol {\theta} ^ {\top} \boldsymbol {N}   \boldsymbol {\theta} = 1, \end{array}\tag{135}
$$

whose solution is similarly obtained as: 

$$
\boldsymbol {G} \boldsymbol {\theta} = \lambda \boldsymbol {N} \boldsymbol {\theta},\tag{136}
$$

which is a generalized eigenvalue problem $( G , N )$ according to (Ghojogh et al., 2019a). 

## 9.3. Multi-dimensional Subspace

In the previous section, the one-dimensional kernel Fisher subspace was discussed. In multi-dimensional kernel Fisher subspace, the within- and between-scatters are the same but the fisher criterion is different. According to Eq. (96), the $d _ { B }$ and $d _ { W }$ are: 

$$
\begin{array}{l} d _ {B} = \mathbf {t r} \big (\phi (\boldsymbol {U}) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {S} _ {B})   \phi (\boldsymbol {U}) \big) = \mathbf {t r} (\boldsymbol {\Theta} ^ {\top} \boldsymbol {M} \boldsymbol {\Theta}), \\ d _ {W} = \mathbf {t r} \big (\phi (\boldsymbol {U}) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {S} _ {W})   \phi (\boldsymbol {U}) \big) = \mathbf {t r} (\boldsymbol {\Theta} ^ {\top} \boldsymbol {N} \boldsymbol {\Theta}), \end{array}\tag{137}
$$

(138) 

where $\mathbb { R } ^ { n \times p } \ni \Theta = [ \pmb { \theta } _ { 1 } , \dots , \pmb { \theta } _ { p } ]$ and $M \in \mathbb { R } ^ { n \times n }$ and $\ b { N } \in \mathbb { R } ^ { n \times n }$ are the between- and within-scatters, respectively, determined for either two-class or multi-class case. The Fisher criterion becomes: 

$$
\begin{array}{l} f (\boldsymbol {\Theta}) := \frac {d _ {B} (\boldsymbol {\Theta})}{d _ {W} (\boldsymbol {\Theta})} = \frac {\mathbf {t r} \big (\phi (\boldsymbol {U}) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {S} _ {B})   \phi (\boldsymbol {U}) \big)}{\mathbf {t r} \big (\phi (\boldsymbol {U}) ^ {\top} \boldsymbol {\Phi} (\boldsymbol {S} _ {W})   \phi (\boldsymbol {U}) \big)} \\ = \frac {\mathbf {t r} (\boldsymbol {\Theta} ^ {\top} \boldsymbol {M} \boldsymbol {\Theta})}{\mathbf {t r} (\boldsymbol {\Theta} ^ {\top} \boldsymbol {N} \boldsymbol {\Theta})}, \end{array}\tag{139}
$$

where the columns of Θ are the kernel Fisher directions. Similar to Eq. (54), the solution to maximization of this criterion is: 

$$
M \Theta = N \Theta \Lambda ,\tag{140}
$$

![image](<Images/tutorial-FDA/image_003.jpg>)



Figure 3. The projection directions (ghost faces) of FDA and PCA for the first four classes of facial AT&T dataset.


the generalized eigenvalue problem $( M , N )$ according to (Ghojogh et al., 2019a). The columns of Θ are the eigenvectors sorted from the largest to smallest eigenvalues (because the optimization is maximization) and the diagonal entries of Λ are the corresponding eigenvalues. 

Again, we can have another variant of kernel FDA for the multi-dimensional sub-space where the optimization is (similar to Eq. (135)): 

$$
\begin{array}{l l} \underset {\Theta} {\text { maximize }} & \mathbf {t r} (\boldsymbol {\Theta} ^ {\top} \boldsymbol {G}   \boldsymbol {\Theta}) \\ \text { subject   to } & \boldsymbol {\Theta} ^ {\top} \boldsymbol {N}   \boldsymbol {\Theta} = \boldsymbol {I}, \end{array}\tag{141}
$$

whose solution is similarly obtained as: 

$$
\boldsymbol {G} \boldsymbol {\Theta} = \boldsymbol {N} \boldsymbol {\Theta} \boldsymbol {\Lambda},\tag{142}
$$

which is a generalized eigenvalue problem $( G , N )$ according to (Ghojogh et al., 2019a). 

As mentioned before, in kernel FDA, we do not have reconstruction. The projection of the training data point $\mathbf { \Delta } _ { \mathbf { \mathcal { X } } _ { i } }$ and the out-of-sample data point $\mathbf { \Delta } _ { \mathbf { \mathcal { X } } _ { t } }$ are: 

$$
\mathbb {R} ^ {p} \ni \phi (\widetilde {\boldsymbol {x}} _ {i}) = \boldsymbol {\Phi} (\boldsymbol {U}) ^ {\top} \phi (\boldsymbol {x} _ {i}) \stackrel {(9 6)} {=} \boldsymbol {\Theta} ^ {\top} \boldsymbol {\Phi} (\boldsymbol {X}) ^ {\top} \phi (\boldsymbol {x} _ {i})
$$

$$
= \boldsymbol {\Theta} ^ {\top} \boldsymbol {k} (\boldsymbol {X}, \boldsymbol {x} _ {i}),\tag{143}
$$

$$
\mathbb {R} ^ {p} \ni \phi (\widetilde {\boldsymbol {x}} _ {t}) = \boldsymbol {\Theta} ^ {\top} \boldsymbol {k} (\boldsymbol {X}, \boldsymbol {x} _ {t}).\tag{144}
$$

For the whole training and out-of-sample data, the projections are: 

$$
\mathbb {R} ^ {p \times n} \ni \Phi (\widetilde {\boldsymbol {X}}) = \boldsymbol {\Theta} ^ {\top} \boldsymbol {K} (\boldsymbol {X}, \boldsymbol {X}),
$$

$$
\mathbb {R} ^ {p \times n _ {t}} \ni \boldsymbol {\Phi} (\widetilde {\boldsymbol {X}} _ {t}) = \boldsymbol {\Theta} ^ {\top} \boldsymbol {K} (\boldsymbol {X}, \boldsymbol {X} _ {t}).\tag{145}
$$

(146) 

## 9.4. Discussion on Dimensionality of the Kernel Fisher Subspace

According to Eq. (107), the rank of the N is at most min $( n , c )$ because the matrix is $n \times n$ and its calculation includes c iterations. Hence, the rank of $N ^ { - 1 }$ is also at most min $. ( n , c )$ . According to $\operatorname { E q } .$ . (126), the rank of the M is at most mi $\mathsf { \Omega } _ { \mathsf { l } } ( n , c - 1 )$ ) because the matrix is $n \times n ,$ we have c iterations in its calculation, and −1 is because of subtracting the mean (refer to the explanation in Section 3.3). 

In Eq. (111), we have $N ^ { - 1 } M$ whose rank is: 

$$
\begin{array}{l} \mathbf {r a n k} (N ^ {- 1} M) \leq \min \left(\mathbf {r a n k} (N ^ {- 1}), \mathbf {r a n k} (M)\right) \\ \leq \min \left(\min (n, c), \min (n, c - 1)\right) \\ = \min (n, c, c - 1) \stackrel {(a)} {=} c - 1, \end{array} \tag {1}\tag{147}
$$

where (a) is because we usually have $c < n$ . Therefore, the rank of $N ^ { - 1 } M$ is limited because of the rank of M which is at most $c - 1$ 

According to Eq. (111), the c − 1 leading eigenvalues will be valid and the rest are zero or very small. Therefore, the $p ,$ which is the dimensionality of the kernel Fisher subspace, is at most $c - 1$ . The $c - 1$ leading eigenvectors are considered as the kernel Fisher directions and the rest of eigenvectors are invalid and ignored. 

## 10. Simulations

For the simulations, we used the AT&T face dataset which includes 400 images, 40 subjects, and 10 images per subject. The images of every person have different poses and expressions. For better visualization of separation of classes in the projection subspace, we only used the images of the first four subjects. The dataset, except for reconstruction experiments, was standardized so that its mean and variance became zero and one, respectively. 

## 10.1. Visualization of the Projection Directions

First, we used the entire 40 images for training FDA, kernel FDA, PCA, and kernel PCA where the used kernels are linear, Radial Basis Function (RBF), and cosine kernels. As we have four classes, the number of FDA directions is three. The three FDA directions and the top ten PCA directions for the used dataset are shown in Fig. 3. As can be seen, the projection directions of a facial dataset are some facial features which are like ghost faces. That is why the facial projection directions are also referred to as ghost faces. The ghost faces in FDA and PCA are also referred to as Fisherfaces (Belhumeur et al., 1997; Etemad & Chellappa, 1997; Zhao et al., 1999) and eigenfaces (Turk & 

![image](<Images/tutorial-FDA/image_004.jpg>)



Figure 4. The projection of the first four classes of AT&T dataset onto FDA and kernel FDA subspaces where the used kernels were linear, RBF, and cosine kernels.


Pentland, 1991a;b), respectively. In Fig. 3, the projection directions have captured different facial features which discriminate the data with respect to the maximum variance in PCA and maximum class separation and minimum within class scatter in FDA. The captured features are eyes, eyeglasses, nose, cheeks, chin, lips, eyebrows, and hair, which are the most important facial features. This figure does not include projection directions of kernel FDA and kernel PCA because in kernel FDA, the projection directions are n-dimensional and not d dimensional, and in kernel PCA, the projection directions are not available (see (Ghojogh & Crowley, 2019c)). Note that the face recognition using kernel FDA and kernel PCA are referred to as kernel Fisherfaces (Yang, 2002; Liu et al., 2004) and kernel eigenfaces (Yang et al., 2000), respectively. 

![image](<Images/tutorial-FDA/image_005.jpg>)



Figure 5. The projection of the first four classes of AT&T dataset onto PCA and kernel PCA subspaces where the used kernels were linear, RBF, and cosine kernels.


## 10.2. Projection of the Training Data

The projection of the images onto FDA and kernel FDA subspaces are shown in Fig. 4 where the linear, Radial Basis Function (RBF), and cosine kernels were used. The projection of the images using PCA and kernel PCA are also shown in Fig. 5. As can be seen, the FDA and kernel FDA subspaces have separated the classes much better than the PCA and kernel PCA subspaces. This is because the FDA and kernel FDA make use of the class labels in order to separate the classes in the subspace while the PCA and kernel 

PCA only capture the variance (spread) of data regardless of class labels. 

## 10.3. Reconstruction of Images

Figure 6 illustrates the reconstruction of some of the training images. The FDA has used its three projection directions for reconstruction. For reconstruction in PCA, we once used the top three PCA directions and one used the whole d PCA directions. 

As can be seen in this figure, the reconstruction of PCA is much better than FDA. This makes sense because PCA is the best linear method for reconstruction having the least squared error (see (Ghojogh & Crowley, 2019c)). However, the responsibility of FDA is not reconstruction but separation of the classes. Thus, the FDA directions try to separate the classes as much as possible and do not necessarily care for a good reconstruction. Recall Fig. 2 which shows different cases for FDA and PCA directions. According to this figure, even in some datasets, FDA direction is orthogonal to PCA direction which is the best direction for reconstruction. It is noteworthy that reconstruction cannot be done in kernel FDA, so as in kernel PCA (see (Ghojogh & Crowley, 2019c)) as was mentioned before. Moreover, note that reconstruction can be done in FDA also for the out-of-sample data. Here, for the sake of brevity, we do not provide simulation for it. 

## 10.4. Out-of-sample Projection

We took the first six images of each of the first four subjects in the AT&T dataset as the training images and the rest as the test (out-of-sample) images. The projection of the training and the out-of-sample images onto FDA and kernel FDA (using linear, RBF, and cosine kernels) are shown in Fig. 7. This figure shows that projection of out-of-sample images have been properly carried on in FDA and kernel FDA. 

## 11. Conclusion

This paper was a tutorial paper introducing FDA and kernel FDA in detail. Various concepts about FDA, such as rank of scatters, dimensionality of the subspace, an example for interpretation, robust FDA, equivalency to LDA, and Fisher forest were explained and discussed. Both cases of twoand multi-classes were covered for FDA and kernel FDA. Finally, some simulations were performed to validate the theory in practice and compare to the unsupervised PCA method. 

## Acknowledgment

The authors hugely thank Prof. Ali Ghodsi (see his great online courses (Ghodsi, 2017; 2015)), Prof. Mu Zhu, Prof. Hoda Mohammadzade, and other professors whose courses have partly covered the materials mentioned in this tutorial 

![image](<Images/tutorial-FDA/image_006.jpg>)



Figure 6. The reconstruction of four sample faces of AT&T datasets in FDA and PCA.


paper. 

## A. Metric Learning

The general form of metric (Peltonen et al., 2004) is usually defined as a form similar to Mahalanobis distance (McLachlan, 1999; De Maesschalck et al., 2000). The metric is: 

$$
| | \pmb {x} _ {i} - \pmb {x} _ {j} | | _ {\pmb {A}} := (\pmb {x} _ {i} - \pmb {x} _ {j}) ^ {\top} \pmb {A} (\pmb {x} _ {i} - \pmb {x} _ {j}),\tag{148}
$$

where: 

$$
\boldsymbol {A} = \boldsymbol {U} \boldsymbol {U} ^ {\top} \succeq 0,\tag{149}
$$

to have a valid distance metric. Most of the metric learning algorithms (Kulis et al., 2013) are optimization problems where A is unknown to make data points in same class (similar pairs) closer to each other, and points in different classes far apart from each other. We have: 

$$
\begin{array}{r l} \left| \left| \boldsymbol {x} _ {i} - \boldsymbol {x} _ {j} \right| \right| _ {\boldsymbol {A}} & \stackrel {(1 4 9)} {=} \left(\boldsymbol {x} _ {i} - \boldsymbol {x} _ {j}\right) ^ {\top} \boldsymbol {U} \boldsymbol {U} ^ {\top} \left(\boldsymbol {x} _ {i} - \boldsymbol {x} _ {j}\right) \\ & = \left(\boldsymbol {U} ^ {\top} \boldsymbol {x} _ {i} - \boldsymbol {U} ^ {\top} \boldsymbol {x} _ {j}\right) ^ {\top} \left(\boldsymbol {U} ^ {\top} \boldsymbol {x} _ {i} - \boldsymbol {U} ^ {\top} \boldsymbol {x} _ {j}\right), \end{array} \tag {150}\tag{151}
$$

so this metric is equivalent to projection of data with projection matrix U and then using Euclidean distance in the embedded space (Peltonen et al., 2004). Therefore, Metric learning can be considered as a feature extraction (Ghojogh et al., 2019b) and manifold learning method (Alipanahi et al., 2008; Globerson & Roweis, 2006). 

![image](<Images/tutorial-FDA/image_007.jpg>)



(a)


![image](<Images/tutorial-FDA/image_008.jpg>)



(b)


![image](<Images/tutorial-FDA/image_009.jpg>)



(c)


![image](<Images/tutorial-FDA/image_010.jpg>)



(d)



Figure 7. The first two dimensions of the projection of both training and out-of-sample instances in the first four classes of AT&T dataset onto subspaces of (a) FDA, (b) kernel FDA using linear kernel, (c) kernel FDA using RBF kernel, and (d) kernel FDA using cosine kernel.


## B. Rayleigh-Ritz Quotient

The Rayleigh-Ritz quotient or Rayleigh quotient is defined as (Parlett, 1998; Croot, 2005): 

$$
\mathbb {R} \ni R (\boldsymbol {A}, \boldsymbol {x}) := \frac {\boldsymbol {x} ^ {\top} \boldsymbol {A} \boldsymbol {x}}{\boldsymbol {x} ^ {\top} \boldsymbol {x}},\tag{152}
$$

where A is a symmetric matrix and x is a non-zero vector: 

$$
\boldsymbol {A} = \boldsymbol {A} ^ {\top}, \boldsymbol {x} \neq \mathbf {0}.\tag{153}
$$

One of the properties of the Rayleigh-Ritz quotient is: 

$$
R (\boldsymbol {A}, c \boldsymbol {x}) = R (\boldsymbol {A}, \boldsymbol {x}),\tag{154}
$$

where c is a scalar. The proof is that: 

$$
\begin{array}{c} R (\boldsymbol {A}, c \boldsymbol {x}) = \frac {(c \boldsymbol {x}) ^ {\top} \boldsymbol {A}   c \boldsymbol {x}}{(c \boldsymbol {x}) ^ {\top} c \boldsymbol {x}} \stackrel {(a)} {=} \frac {c \boldsymbol {x} ^ {\top} \boldsymbol {A}   c \boldsymbol {x}}{c \boldsymbol {x} ^ {\top} c \boldsymbol {x}} \\ \stackrel {(b)} {=} \frac {c ^ {2}}{c ^ {2}} \times \frac {\boldsymbol {x} ^ {\top} \boldsymbol {A}   \boldsymbol {x}}{\boldsymbol {x} ^ {\top} \boldsymbol {x}} \stackrel {(1 5 2)} {=} R (\boldsymbol {A}, \boldsymbol {x}), \end{array}
$$

where (a) and (b) are because c is a scalar. 

Because of the Eq. (154), the optimization of the Rayleigh-Ritz quotient has an equivalent (Croot, 2005): 

$$
\begin{array}{l l} \underset {\boldsymbol {x}} {\text { minimize / maximize }} & R (\boldsymbol {A}, \boldsymbol {x}) \overset {(a)} {=} \\ \underset {\boldsymbol {x}} {\text { minimize / maximize }} & R (\boldsymbol {A}, \boldsymbol {x}) \\ \text { subject   to } & | | \boldsymbol {x} | | _ {2} = 1, \\ \underset {\boldsymbol {x}} {\text { minimize / maximize }} & \boldsymbol {x} ^ {\top} \boldsymbol {A}   \boldsymbol {x} \\ \text { subject   to } & | | \boldsymbol {x} | | _ {2} = 1, \end{array}\tag{155}
$$

where (a) is because if we define $\begin{array} { r } { \pmb { y } : = \left( 1 / | | \pmb { x } | | _ { 2 } \right) \pmb { x } , } \end{array}$ , the Rayleigh-Ritz quotient is: 

$$
R (\boldsymbol {A}, \boldsymbol {y}) = \frac {\boldsymbol {y} ^ {\top} \boldsymbol {A} \boldsymbol {y}}{\boldsymbol {y} ^ {\top} \boldsymbol {y}} = \frac {1 / | | \boldsymbol {x} | | _ {2} ^ {2}}{1 / | | \boldsymbol {x} | | _ {2} ^ {2}} \times \frac {\boldsymbol {x} ^ {\top} \boldsymbol {A} \boldsymbol {x}}{\boldsymbol {x} ^ {\top} \boldsymbol {x}} = R (\boldsymbol {A}, \boldsymbol {x}),\tag{156}
$$

and: 

$$
\left| \left| \boldsymbol {y} \right| \right| _ {2} ^ {2} = \frac {1}{\left| \left| \boldsymbol {x} \right| \right| _ {2} ^ {2}} \times \left| \left| \boldsymbol {x} \right| \right| _ {2} ^ {2} = 1 \implies \left| \left| \boldsymbol {y} \right| \right| _ {2} = 1.\tag{157}
$$

Thus, we have $R ( A , y )$ subject to $| | \pmb { y } | | _ { 2 } = 1$ . Changing the dummy variable y to x gives the Eq. (155). The (b) notices ${ \pmb x } ^ { \top } { \pmb x } = 1$ because of the constraint $| | { \pmb x } | | _ { 2 } = 1$ 

Note that the constraint in Eq. (155) can be equal to any constant which is proved similarly. Moreover, note that the value of constant in the constraint is not important because it will be removed after taking derivative from the Lagrangian in optimization (Boyd & Vandenberghe, 2004). 

The generalized Rayleigh-Ritz quotient or generalized Rayleigh quotient is defined as (Parlett, 1998; Ghojogh et al., 2019a): 

$$
\mathbb {R} \ni R (\boldsymbol {A}, \boldsymbol {B}; \boldsymbol {x}) := \frac {\boldsymbol {x} ^ {\top} \boldsymbol {A} \boldsymbol {x}}{\boldsymbol {x} ^ {\top} \boldsymbol {B} \boldsymbol {x}},\tag{158}
$$

where A and B are symmetric matrices and x is a non-zero vector: 

$$
\boldsymbol {A} = \boldsymbol {A} ^ {\top}, \boldsymbol {B} = \boldsymbol {B} ^ {\top}, \boldsymbol {x} \neq \mathbf {0}.\tag{159}
$$

If the symmetric B is positive definite: 

$$
\boldsymbol {B} \succ 0,\tag{160}
$$

it has a Cholesky decomposition: 

$$
\boldsymbol {B} = \boldsymbol {C C} ^ {\top},\tag{161}
$$

where C is a lower triangular matrix. In case $B \succ 0$ , the generalized Rayleigh-Ritz quotient can be converted to a Rayleigh-Ritz quotient: 

$$
R (\boldsymbol {A}, \boldsymbol {B}; \boldsymbol {x}) = R (\boldsymbol {D}, \boldsymbol {C} ^ {\top} \boldsymbol {x}),\tag{162}
$$

where: 

$$
\boldsymbol {D} := \boldsymbol {C} ^ {- 1} \boldsymbol {A} \boldsymbol {C} ^ {- \top}.\tag{163}
$$

The proof is: 

$$
\begin{array}{l} \text { RHS } = R (D, C ^ {\top} x) \stackrel {(1 5 2)} {=} \frac {(C ^ {\top} x) ^ {\top} D (C ^ {\top} x)}{(C ^ {\top} x) ^ {\top} (C ^ {\top} x)} \\ \stackrel {(1 6 3)} {=} \frac {x ^ {\top} C C ^ {- 1} A (C C ^ {- 1}) ^ {\top} x}{x ^ {\top} (C C ^ {\top}) x} \stackrel {(a)} {=} \frac {x ^ {\top} A x}{x ^ {\top} B x} \\ \stackrel {(1 5 8)} {=} R (A, B; x) = \text { LHS }, \quad \text { Q.E.D. }, \end{array}
$$

where RHS and LHS are short for right and left hand sides and (a) is because of Eq. (161) and $C C ^ { - 1 } = I$ because C is a square matrix. 

Similarly, one of the properties of the generalized Rayleigh-Ritz quotient is: 

$$
R (\boldsymbol {A}, \boldsymbol {B}; c \boldsymbol {x}) = R (\boldsymbol {A}, \boldsymbol {B}; \boldsymbol {x}),\tag{164}
$$

where c is a scalar. The proof is that: 

$$
\begin{array}{c} R (\boldsymbol {A}, \boldsymbol {B}; c \boldsymbol {x}) = \frac {(c \boldsymbol {x}) ^ {\top} \boldsymbol {A}   c \boldsymbol {x}}{(c \boldsymbol {x}) ^ {\top} \boldsymbol {B}   c \boldsymbol {x}} \stackrel {{(a)}} {{=}} \frac {c \boldsymbol {x} ^ {\top} \boldsymbol {A}   c \boldsymbol {x}}{c \boldsymbol {x} ^ {\top} \boldsymbol {B}   c \boldsymbol {x}} \\ \stackrel {{(b)}} {{=}} \frac {c ^ {2}}{c ^ {2}} \times \frac {\boldsymbol {x} ^ {\top} \boldsymbol {A}   \boldsymbol {x}}{\boldsymbol {x} ^ {\top} \boldsymbol {B}   \boldsymbol {x}} \stackrel {{(1 5 8)}} {{=}} R (\boldsymbol {A}, \boldsymbol {B}; \boldsymbol {x}), \end{array}
$$

where (a) and (b) are because c is a scalar. 

Because of the Eq. (164), the optimization of the generalized Rayleigh-Ritz quotient has an equivalent: 

$$
\begin{array}{l l} \underset {\boldsymbol {x}} {\text { minimize / maximize }} & R (\boldsymbol {A}, \boldsymbol {B}; \boldsymbol {x}) \equiv \\ \underset {\boldsymbol {x}} {\text { minimize / maximize }} & \boldsymbol {x} ^ {\top} \boldsymbol {A}   \boldsymbol {x} \\ \text { subject   to } & \boldsymbol {x} ^ {\top} \boldsymbol {B}   \boldsymbol {x} = 1, \end{array}\tag{165}
$$

for a similar reason that we provided for the Rayleigh-Ritz quotient. the constraint can be equal to any constant because in the derivative of Lagrangian, the constant will be dropped. 

## References



Alipanahi, Babak, Biggs, Michael, and Ghodsi, Ali. Distance metric learning vs. Fisher discriminant analysis. In Proceedings of the 23rd national conference on Artificial intelligence, volume 2, pp. 598–603, 2008. 





Alperin, Jonathan L. Local representation theory: Modular representations as an introduction to the local representation theory offinite groups, volume 11. Cambridge University Press, 1993. 





Belhumeur, Peter N, Hespanha, Joao P, and Kriegman,˜ David J. Eigenfaces vs. Fisherfaces: Recognition using class specific linear projection. IEEE Transactions on Pattern Analysis & Machine Intelligence, (7):711–720, 1997. 





Boyd, Stephen and Vandenberghe, Lieven. Convex optimization. Cambridge university press, 2004. 





Croot, Ernie. The Rayleigh principle for finding eigenvalues. Technical report, Georgia Institute of Technology, School of Mathematics, 2005. Online: http://people.math.gatech.edu/∼ecroot/notes_linear.pdf, Accessed: March 2019. 





De Maesschalck, Roy, Jouan-Rimbaud, Delphine, and Massart, Desir´ e L. The Mahalanobis distance.´ Chemometrics and intelligent laboratory systems, 50(1):1–18, 2000. 





Deng, Weihong, Hu, Jiani, Guo, Jun, and Zhang, Honggang. Robust discriminant analysis of gabor feature for face recognition. In Fourth International Conference on Fuzzy Systems and Knowledge Discovery (FSKD 2007), volume 3, pp. 248–252. IEEE, 2007. 





Etemad, Kamran and Chellappa, Rama. Discriminant analysis for recognition of human face images. Journal ofthe Optical Society ofAmerica A, 14(8):1724–1733, 1997. 





Fisher, Ronald A. Xv.the correlation between relatives on the supposition of mendelian inheritance. Earth and Environmental Science Transactions ofthe Royal Society of Edinburgh, 52(2):399–433, 1919. 





Fisher, Ronald A. The use of multiple measurements in taxonomic problems. Annals ofeugenics, 7(2):179–188, 1936. 





Fisher, Ronald Aylmer. Statistical methods for research workers. In Breakthroughs in statistics, pp. 66–70. Springer, 1992. 





Frieden, B Roy. Science from Fisher information: a unification. Cambridge University Press, 2004. 





Friedman, Jerome, Hastie, Trevor, and Tibshirani, Robert. The elements of statistical learning, volume 2. Springer series in statistics New York, NY, USA, 2009. 





Ghodsi, Ali. Classification course, department of statistics and actuarial science, university of Waterloo. Online Youtube Videos, 2015. Accessed: January 2019. 





Ghodsi, Ali. Data visualization course, department of statistics and actuarial science, university of Waterloo. Online Youtube Videos, 2017. Accessed: January 2019. 





Ghojogh, Benyamin and Crowley, Mark. Linear and quadratic discriminant analysis: Tutorial. arXiv preprint arXiv:1906.02590, 2019a. 





Ghojogh, Benyamin and Crowley, Mark. The theory behind overfitting, cross validation, regularization, bagging, and boosting: Tutorial. arXiv preprint arXiv:1905.12787, 2019b. 





Ghojogh, Benyamin and Crowley, Mark. Unsupervised and supervised principal component analysis: Tutorial. arXiv preprint arXiv:1906.03148, 2019c. 





Ghojogh, Benyamin and Mohammadzade, Hoda. Automatic extraction of key-poses and key-joints for action recognition using 3d skeleton data. In 2017 10th Iranian Conference on Machine Vision and Image Processing (MVIP), pp. 164–170. IEEE, 2017. 





Ghojogh, Benyamin, Mohammadzade, Hoda, and Mokari, Mozhgan. Fisherposes for human action recognition using kinect sensor data. IEEE Sensors Journal, 18(4): 1612–1627, 2017. 





Ghojogh, Benyamin, Karray, Fakhri, and Crowley, Mark. Eigenvalue and generalized eigenvalue problems: Tutorial. arXiv preprint arXiv:1903.11240, 2019a. 





Ghojogh, Benyamin, Samad, Maria N, Mashhadi, Sayema Asif, Kapoor, Tania, Ali, Wahab, Karray, Fakhri, and Crowley, Mark. Feature selection and feature extraction in pattern analysis: A literature review. arXiv preprint arXiv:1905.02845, 2019b. 





Globerson, Amir and Roweis, Sam T. Metric learning by collapsing classes. In Advances in neural information processing systems, pp. 451–458, 2006. 





Guo, Ming and Wang, Zhelong. A feature extraction method for human action recognition using body-worn inertial sensors. In 2015 IEEE 19th International Conference on Computer Supported Cooperative Work in Design (CSCWD), pp. 576–581. IEEE, 2015. 





Herbrich, Ralf. Learning kernel classifiers: theory and algorithms. Mit Press, 2001. 





Hofmann, Thomas, Scholkopf, Bernhard, and Smola,¨ Alexander J. Kernel methods in machine learning. The annals ofstatistics, pp. 1171–1220, 2008. 





Kulis, Brian et al. Metric learning: A survey. Foundations and Trends R in Machine Learning, 5(4):287–364, 2013. 





Liu, Qingshan, Lu, Hanqing, and Ma, Songde. Improving kernel Fisher discriminant analysis for face recognition. IEEE transactions on circuits and systemsfor video technology, 14(1):42–49, 2004. 





McLachlan, Goeffrey J. Mahalanobis distance. Resonance, 4(6):20–26, 1999. 





Mika, Sebastian, Ratsch, Gunnar, Weston, Jason, ¨ Scholkopf, Bernhard, and M¨ uller, Klaus-Robert. Fisher¨ discriminant analysis with kernels. In Proceedings ofthe 1999 IEEE signal processing society workshop on Neural networks for signal processing IX, pp. 41–48. IEEE, 1999. 





Mika, Sebastian, Ratsch, Gunnar, Weston, Jason,¨ Scholkopf, Bernhard, Smola, Alex J, and M ¨ uller, Klaus-¨ Robert. Invariant feature extraction and classification in kernel spaces. In Advances in neural information processing systems, pp. 526–532, 2000. 





Mokari, Mozhgan, Mohammadzade, Hoda, and Ghojogh, Benyamin. Recognizing involuntary actions from 3d skeleton data using body states. Scientia Iranica, 2018. 





Parlett, Beresford N. The symmetric eigenvalue problem. Classics in Applied Mathematics, 20, 1998. 





Peltonen, Jaakko, Klami, Arto, and Kaski, Samuel. Improved learning of Riemannian metrics for exploratory analysis. Neural Networks, 17(8-9):1087–1100, 2004. 





Polikar, Robi. Ensemble learning. In Ensemble machine learning, pp. 1–34. Springer, 2012. 





Samadani, Ali-Akbar, Ghodsi, Ali, and Kulic, Dana. Dis-´ criminative functional analysis of human movements. Pattern Recognition Letters, 34(15):1829–1839, 2013. 





Sugiyama, Masashi. Dimensionality reduction of multimodal labeled data by local fisher discriminant analysis. Journal of machine learning research, 8(May):1027– 1061, 2007. 





Turk, Matthew and Pentland, Alex. Eigenfaces for recognition. Journal of cognitive neuroscience, 3(1):71–86, 1991a. 





Turk, Matthew A and Pentland, Alex P. Face recognition using eigenfaces. In Computer Vision and Pattern Recognition, 1991. Proceedings CVPR’91., IEEE Computer Society Conference on, pp. 586–591. IEEE, 1991b. 





Wang, Ruye. Generalized eigenvalue problem. http://fourier.eng.hmc.edu/e161/lectures/algebra/node7.html, 2015. Accessed: January 2019. 





Wang, Yanxia and Ruan, Qiuqi. Kernel fisher discriminant analysis for palmprint recognition. In 18th International Conference on Pattern Recognition (ICPR’06), volume 4, pp. 457–460. IEEE, 2006. 





Welling, Max. Fisher linear discriminant analysis. Technical report, Department of Computer Science, University of Toronto, 2005. 





Xu, Yong and Lu, Guangming. Analysis on Fisher discriminant criterion and linear separability of feature space. In 2006 International Conference on Computational Intelligence and Security, volume 2, pp. 1671–1676. IEEE, 2006. 





Yang, M-H, Ahuja, Narendra, and Kriegman, David. Face recognition using kernel eigenfaces. In Image processing, 2000. proceedings. 2000 international conference on, volume 1, pp. 37–40. IEEE, 2000. 





Yang, Ming-Hsuan. Kernel Eigenfaces vs. kernel Fisherfaces: Face recognition using kernel methods. In Proceedings of the fifth IEEE international conference on automatic face and gesture recognition, pp. 215–220, 2002. 





Zhao, Wenyi, Chellappa, Rama, and Phillips, P Jonathon. Subspace linear discriminant analysis for face recognition. Citeseer, 1999. 

