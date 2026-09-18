# Linear and Quadratic Discriminant Analysis: Tutorial

Benyamin Ghojogh 

Department of Electrical and Computer Engineering, 

BGHOJOGH@UWATERLOO.CA 

Machine Learning Laboratory, University of Waterloo, Waterloo, ON, Canada 

Mark Crowley 

MCROWLEY@UWATERLOO.CA 

Department of Electrical and Computer Engineering, 

Machine Learning Laboratory, University of Waterloo, Waterloo, ON, Canada 

## Abstract

This tutorial explains Linear Discriminant Analysis (LDA) and Quadratic Discriminant Analysis (QDA) as two fundamental classification methods in statistical and probabilistic learning. We start with the optimization of decision boundary on which the posteriors are equal. Then, LDA and QDA are derived for binary and multiple classes. The estimation of parameters in LDA and QDA are also covered. Then, we explain how LDA and QDA are related to metric learning, kernel principal component analysis, Mahalanobis distance, logistic regression, Bayes optimal classifier, Gaussian naive Bayes, and likelihood ratio test. We also prove that LDA and Fisher discriminant analysis are equivalent. We finally clarify some of the theoretical concepts with simulations we provide. 

## 1. Introduction

Assume we have a dataset of instances $\{ ( \pmb { x } _ { i } , y _ { i } ) \} _ { i = 1 } ^ { n }$ with sample size n and dimensionality $\pmb { x } _ { i } \in \mathbb { R } ^ { d } \mathrm { a n d } y _ { i } \in \mathbb { R }$ . The $y _ { i } { ' } s$ are the class labels. We would like to classify the space of data using these instances. Linear Discriminant Analysis (LDA) and Quadratic discriminant Analysis (QDA) (Friedman et al., 2009) are two well-known supervised classification methods in statistical and probabilistic learning. This paper is a tutorial for these two classifiers where the theory for binary and multi-class classification are detailed. Then, relations of LDA and QDA to metric learning, kernel Principal Component Analysis (PCA), Fisher Discriminant Analysis (FDA), logistic regression, Bayes optimal classifier, Gaussian naive Bayes, and Likelihood Ratio Test (LRT) are explained for better understanding of these two fundamental methods. Finally, some experiments on synthetic datasets are reported and analyzed for illustration. 

## 2. Optimization for the Boundary of Classes

First suppose the data is one dimensional, $x \in \mathbb { R }$ . Assume we have two classes with the Cumulative Distribution Functions (CDF) $F _ { 1 } ( x )$ and $F _ { 2 } ( x )$ , respectively. Let the Probability Density Functions (PDF) of these CDFs be: 

$$
f _ {1} (x) = \frac {\partial F _ {1} (x)}{\partial x},\tag{1}
$$

$$
f _ {2} (x) = \frac {\partial F _ {2} (x)}{\partial x},\tag{2}
$$

respectively. 

We assume that the two classes have normal (Gaussian) distribution which is the most common and default distribution in the real-world applications. The mean of one of the two classes is greater than the other one; we assume $\mu _ { 1 } < \mu _ { 2 }$ . An instance $x \in \mathbb { R }$ belongs to one of these two classes: 

$$
x \sim \left\{ \begin{array}{l l} \mathcal {N} (\mu_ {1}, \sigma_ {1} ^ {2}), & \text {if} x \in \mathcal {C} _ {1}, \\ \mathcal {N} (\mu_ {2}, \sigma_ {2} ^ {2}), & \text {if} x \in \mathcal {C} _ {2}, \end{array} \right.\tag{3}
$$

where $\mathcal { C } _ { 1 }$ and $\mathcal { C } _ { 2 }$ denote the first and second class, respectively. 

For an instance $x ,$ we may have an error in estimation of the class it belongs to. At a point, which we denote by $x ^ { * }$ the probability of the two classes are equal; therefore, the point $x ^ { * }$ is on the boundary of the two classes. As we have $\mu _ { 1 } < \mu _ { 2 }$ , we can say $\mu _ { 1 } < x ^ { * } < \mu _ { 2 }$ as shown in Fig. 1. Therefore, if $x < x ^ { * } \ \mathrm { o r } \ x > x ^ { * }$ the instance x belongs to the first and second class, respectively. Hence, estimating $x \ < \ x ^ { * } \ \mathrm { o r } \ x \ > \ x ^ { * }$ to respectively belong to the second and first class is an error in estimation of the class. This probability of the error can be stated as: 

$$
\mathbb {P} (\text { error }) = \mathbb {P} (x > x ^ {*}, x \in \mathcal {C} _ {1}) + \mathbb {P} (x <   x ^ {*}, x \in \mathcal {C} _ {2}).\tag{4}
$$

![image](<Images/02_Optimization_for_the_Boundary_of_Classes_image_001.jpg>)



Figure 1. Two Gaussian density functions where they are equal a the point $x ^ { * }$ .


As we have $\mathbb { P } ( A , B ) = \mathbb { P } ( A | B ) \mathbb { P } ( B )$ , we can say: 

$$
\begin{array}{c} \mathbb {P} (\text { error }) = \mathbb {P} (x > x ^ {*} \mid x \in \mathcal {C} _ {1})   \mathbb {P} (x \in \mathcal {C} _ {1}) \\ + \mathbb {P} (x <   x ^ {*} \mid x \in \mathcal {C} _ {2})   \mathbb {P} (x \in \mathcal {C} _ {2}), \end{array}\tag{5}
$$

which we want to minimize: 

$$
\underset {x ^ {*}} {\text { minimize }} \quad \mathbb {P} (\text { error }),\tag{6}
$$

by finding the best boundary of classes, i.e., $x ^ { * }$ According to the definition of CDF, we have: 

$$
\begin{array}{l} \mathbb {P} (x <   c, x \in \mathcal {C} _ {1}) = F _ {1} (c), \\ \implies \mathbb {P} (x > x ^ {*}, x \in \mathcal {C} _ {1}) = 1 - F _ {1} (x ^ {*}), \\ \mathbb {P} (x <   x ^ {*}, x \in \mathcal {C} _ {2}) = F _ {2} (x ^ {*}). \end{array}\tag{7}
$$

(8) 

According to the definition of PDF, we have: 

$$
\mathbb {P} (x \in \mathcal {C} _ {1}) = f _ {1} (x) = \pi_ {1},\tag{9}
$$

$$
\mathbb {P} (x \in \mathcal {C} _ {2}) = f _ {2} (x) = \pi_ {2},\tag{10}
$$

where we denote the priors $f _ { 1 } ( x )$ and $f _ { 2 } ( x )$ by $\pi _ { 1 }$ and $\pi _ { 2 }$ , respectively. 

Hence, Eqs. (5) and (6) become: 

$$
\underset {x ^ {*}} {\text { minimize }} \left(1 - F _ {1} (x ^ {*})\right) \pi_ {1} + F _ {2} (x ^ {*})   \pi_ {2}.\tag{11}
$$

We take derivative for the sake of minimization: 

$$
\begin{array}{l} \frac {\partial \mathbb {P} (\text { error })}{\partial x ^ {*}} = - f _ {1} (x ^ {*})   \pi_ {1} + f _ {2} (x ^ {*})   \pi_ {2} \stackrel {{\text { set }}} {{=}} 0, \\ \implies f _ {1} (x ^ {*})   \pi_ {1} = f _ {2} (x ^ {*})   \pi_ {2}. \end{array}\tag{12}
$$

Another way to obtain this expression is equating the posterior probabilities to have the equation of the boundary of classes: 

$$
\mathbb {P} (x \in \mathcal {C} _ {1} \mid X = x) \stackrel {\text { set }} {=} \mathbb {P} (x \in \mathcal {C} _ {2} \mid X = x).\tag{13}
$$

According to Bayes rule, the posterior is: 

$$
\begin{array}{c} \mathbb {P} (x \in \mathcal {C} _ {1} \mid X = x) = \frac {\mathbb {P} (X = x \mid x \in \mathcal {C} _ {1})   \mathbb {P} (x \in \mathcal {C} _ {1})}{\mathbb {P} (X = x)} \\ = \frac {f _ {1} (x)   \pi_ {1}}{\sum_ {k = 1} ^ {| \mathcal {C} |} \mathbb {P} (X = x \mid x \in \mathcal {C} _ {k})   \pi_ {k}}, \end{array}\tag{14}
$$

where |C| is the number of classes which is two here. The $f _ { 1 } ( x )$ and $\pi _ { 1 }$ are the likelihood (class conditional) and prior probabilities, respectively, and the denominator is the marginal probability. 

Therefore, Eq. (13) becomes: 

$$
\begin{array}{c} \frac {f _ {1} (x)   \pi_ {1}}{\sum_ {i = 1} ^ {| \mathcal {C} |} \mathbb {P} (X = x   |   x \in \mathcal {C} _ {i})   \pi_ {i}} \\ \stackrel {{\text { set }}} {{=}} \frac {f _ {2} (x)   \pi_ {2}}{\sum_ {i = 1} ^ {| \mathcal {C} |} \mathbb {P} (X = x   |   x \in \mathcal {C} _ {i})   \pi_ {i}} \\ \implies f _ {1} (x)   \pi_ {1} = f _ {2} (x)   \pi_ {2}. \end{array}\tag{15}
$$

Now let us think of data as multivariate data with dimensionality $d .$ The PDF for multivariate Gaussian distribution, $\pmb { x } \sim \mathcal { N } ( \pmb { \mu } , \pmb { \Sigma } )$ is: 

$$
f (\pmb {x}) = \frac {1}{\sqrt {(2 \pi) ^ {d} | \pmb {\Sigma} |}} \exp \Big (- \frac {(\pmb {x} - \pmb {\mu}) ^ {\top} \pmb {\Sigma} ^ {- 1} (\pmb {x} - \pmb {\mu})}{2} \Big),\tag{16}
$$

where $\pmb { x } \in \mathbb { R } ^ { d } , \pmb { \mu } \in \mathbb { R } ^ { d }$ is the mean, $\pmb { \Sigma } \in \mathbb { R } ^ { d \times d }$ is the covariance matrix, and |.| is the determinant of matrix. The $\pi \approx 3$ .14 in this equation should not be confused with the $\pi _ { k }$ (prior) in Eq. (12) or (15). Therefore, the Eq. (12) or (15) becomes: 

$$
\begin{array}{l} \frac {1}{\sqrt {(2 \pi) ^ {d} | \boldsymbol {\Sigma} _ {1} |}} \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {1})}{2}\right) \pi_ {1} \\ = \frac {1}{\sqrt {(2 \pi) ^ {d} | \boldsymbol {\Sigma} _ {2} |}} \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {2})}{2}\right) \pi_ {2}, \end{array}\tag{17}
$$

where the distributions of the first and second class are $\mathcal { N } ( \mu _ { 1 } , \Sigma _ { 1 } )$ and $\mathcal { N } ( \mu _ { 2 } , \Sigma _ { 2 } )$ ), respectively. 

## 3. Linear Discriminant Analysis for Binary Classification

In Linear Discriminant Analysis (LDA), we assume that the two classes have equal covariance matrices: 

$$
\boldsymbol {\Sigma} _ {1} = \boldsymbol {\Sigma} _ {2} = \boldsymbol {\Sigma}.\tag{18}
$$

Therefore, the Eq. (17) becomes: 

$$
\begin{array}{r l} & {\frac {1}{\sqrt {(2 \pi) ^ {d} | \boldsymbol {\Sigma} |}} \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {1})}{2}\right) \pi_ {1}} \\ & {= \frac {1}{\sqrt {(2 \pi) ^ {d} | \boldsymbol {\Sigma} |}} \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {2})}{2}\right) \pi_ {2},} \\ & {\implies \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {1})}{2}\right) \pi_ {1}} \\ & {\qquad = \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {2})}{2}\right) \pi_ {2},} \\ & {\overset {(a)} {\Longrightarrow} - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {1}) + \ln (\pi_ {1})} \\ & {\qquad = - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {2}) + \ln (\pi_ {2}),} \end{array}
$$

where (a) takes natural logarithm from the sides of equation. 

We can simplify this term as: 

$$
\begin{array}{r l} & {\left(\pmb {x} - \pmb {\mu} _ {1}\right) ^ {\top} \pmb {\Sigma} ^ {- 1} (\pmb {x} - \pmb {\mu} _ {1}) = (\pmb {x} ^ {\top} - \pmb {\mu} _ {1} ^ {\top}) \pmb {\Sigma} ^ {- 1} (\pmb {x} - \pmb {\mu} _ {1})} \\ & {= \pmb {x} ^ {\top} \pmb {\Sigma} ^ {- 1} \pmb {x} - \pmb {x} ^ {\top} \pmb {\Sigma} ^ {- 1} \pmb {\mu} _ {1} - \pmb {\mu} _ {1} ^ {\top} \pmb {\Sigma} ^ {- 1} \pmb {x} + \pmb {\mu} _ {1} ^ {\top} \pmb {\Sigma} ^ {- 1} \pmb {\mu} _ {1}} \end{array}
$$

$$
\stackrel {(a)} {=} \boldsymbol {x} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} + \boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {\mu} _ {1} - 2 \boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x},\tag{19}
$$

where (a) is because $\pmb { x } ^ { \top } \pmb { \Sigma } ^ { - 1 } \pmb { \mu } _ { 1 } ~ = ~ \pmb { \mu } _ { 1 } ^ { \top } \pmb { \Sigma } ^ { - 1 } \pmb { x }$ as it is a scalar and ${ \boldsymbol { \Sigma } } ^ { - 1 }$ is symmetric so $ { \boldsymbol { \Sigma } } ^ { - \top } =  { \boldsymbol { \Sigma } } ^ { - 1 }$ . Thus, we have: 

$$
\begin{array}{l} - \frac {1}{2} \boldsymbol {x} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} - \frac {1}{2} \boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {\mu} _ {1} + \boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} + \ln (\pi_ {1}) \\ = - \frac {1}{2} \boldsymbol {x} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} - \frac {1}{2} \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {\mu} _ {2} + \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} + \ln (\pi_ {2}). \end{array}
$$

Therefore, if we multiply the sides of equation by 2, we have: 

$$
\begin{array}{l} 2 \left(\boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {\top} \boldsymbol {x} \\ \quad + \left(\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}\right) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) \big) + 2 \ln (\frac {\pi_ {2}}{\pi_ {1}}) = 0, \end{array}\tag{20}
$$

which is the equation of a line in the form of $\pmb { a } ^ { \top } \pmb { x } + b = 0$ Therefore, if we consider Gaussian distributions for the two classes where the covariance matrices are assumed to be equal, the decision boundary of classification is a line. Because of linearity of the decision boundary which discriminates the two classes, this method is named linear discriminant analysis. 

For obtaining Eq. (20), we brought the expressions to the right side which was corresponding to the second class; therefore, if we use $\delta ( \pmb { x } ) : \bar { \mathbb { R } ^ { d } }  \bar { \mathbb { R } }$ as the left-hand-side expression (function) in Eq. (20): 

$$
\begin{array}{l} \delta (\boldsymbol {x}) := 2 \left(\boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {\top} \boldsymbol {x} \\ \qquad + \left(\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}\right) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) \big) + 2 \ln (\frac {\pi_ {2}}{\pi_ {1}}), \end{array}\tag{21}
$$

the class of an instance x is estimated as: 

$$
\widehat {\mathcal {C}} (x) = \left\{ \begin{array}{l l} 1, & \text { if } \delta (\boldsymbol {x}) <   0, \\ 2, & \text { if } \delta (\boldsymbol {x}) > 0. \end{array} \right.\tag{22}
$$

If the priors of two classes are equal, i.e., $\pi _ { 1 } = \pi _ { 2 }$ , the Eq. (20) becomes: 

$$
\begin{array}{c} 2 \left(\boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {\top} \boldsymbol {x} \\ + \left(\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}\right) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) = 0, \end{array}\tag{23}
$$

whose left-hand-side expression can be considered as $\delta ( { \pmb x } )$ in Eq. (22). 

## 4. Quadratic Discriminant Analysis for Binary Classification

In Quadratic Discriminant Analysis (QDA), we relax the assumption of equality of the covariance matrices: 

$$
\pmb {\Sigma} _ {1} \neq \pmb {\Sigma} _ {2},\tag{24}
$$

which means the covariances are not necessarily equal (if they are actually equal, the decision boundary will be linear and QDA reduces to LDA). 

Therefore, the Eq. (17) becomes: 

$$
\begin{array}{l} \frac {1}{\sqrt {(2 \pi) ^ {d} | \boldsymbol {\Sigma} _ {1} |}} \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {1})}{2}\right) \pi_ {1} \\ = \frac {1}{\sqrt {(2 \pi) ^ {d} | \boldsymbol {\Sigma} _ {2} |}} \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {2})}{2}\right) \pi_ {2}, \\ \stackrel {{(a)}} {{\Longrightarrow}} - \frac {d}{2} \ln (2 \pi) - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {1} |) \\ \qquad - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {1}) + \ln (\pi_ {1}) \\ \qquad = - \frac {d}{2} \ln (2 \pi) - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {2} |) \\ \qquad - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {2}) + \ln (\pi_ {2}), \end{array}
$$

where (a) takes natural logarithm from the sides of equation. According to Eq. (19), we have: 

$$
\begin{array}{l} - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {1} |) - \frac {1}{2} \boldsymbol {x} ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {x} - \frac {1}{2} \boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1} \\ + \boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {x} + \ln (\pi_ {1}) \\ = - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {2} |) - \frac {1}{2} \boldsymbol {x} ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {x} - \frac {1}{2} \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2} \\ + \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {x} + \ln (\pi_ {2}). \end{array}
$$

Therefore, if we multiply the sides of equation by 2, we have: 

$$
\begin{array}{l} \boldsymbol {x} ^ {\top} (\boldsymbol {\Sigma} _ {1} - \boldsymbol {\Sigma} _ {2}) ^ {- 1} \boldsymbol {x} + 2 \left(\boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2} - \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1}\right) ^ {\top} \boldsymbol {x} \\ \quad + (\boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2}) + \ln \Big (\frac {| \boldsymbol {\Sigma} _ {1} |}{| \boldsymbol {\Sigma} _ {2} |} \Big) \\ \quad + 2 \ln (\frac {\pi_ {2}}{\pi_ {1}}) = 0, \end{array}\tag{25}
$$

which is in the quadratic form $\pmb { x } ^ { \top } \pmb { A } \pmb { x } + \pmb { b } ^ { \top } \pmb { x } + c = 0$ Therefore, if we consider Gaussian distributions for the two classes, the decision boundary of classification is quadratic. Because of quadratic decision boundary which discriminates the two classes, this method is named quadratic discriminant analysis. 

For obtaining Eq. (25), we brought the expressions to the right side which was corresponding to the second class; therefore, if we use $\delta ( \pmb { x } ) : \bar { \mathbb { R } ^ { d } }  \bar { \mathbb { R } }$ as the left-hand-side expression (function) in Eq. (25): 

$$
\begin{array}{l} \delta (\boldsymbol {x}) := \boldsymbol {x} ^ {\top} (\boldsymbol {\Sigma} _ {1} - \boldsymbol {\Sigma} _ {2}) ^ {- 1} \boldsymbol {x} + 2 \left(\boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2} - \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1}\right) ^ {\top} \boldsymbol {x} \\ \quad + (\boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2}) + \ln \Bigl (\frac {| \boldsymbol {\Sigma} _ {1} |}{| \boldsymbol {\Sigma} _ {2} |} \Bigr) + 2 \ln (\frac {\pi_ {2}}{\pi_ {1}}), \end{array}\tag{26}
$$

the class of an instance x is estimated as the Eq. (22). If the priors of two classes are equal, i.e., $\pi _ { 1 } = \pi _ { 2 }$ , the $\operatorname { E q }$ (20) becomes: 

$$
\begin{array}{l} \boldsymbol {x} ^ {\top} (\boldsymbol {\Sigma} _ {1} - \boldsymbol {\Sigma} _ {2}) ^ {- 1} \boldsymbol {x} + 2 (\boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2} - \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {x} \\ + (\boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2}) + \ln \Bigl (\frac {| \boldsymbol {\Sigma} _ {1} |}{| \boldsymbol {\Sigma} _ {2} |} \Bigr) = 0, \end{array}\tag{27}
$$

whose left-hand-side expression can be considered as $\delta ( { \pmb x } )$ in Eq. (22). 

## 5. LDA and QDA for Multi-class Classification

Now we consider multiple classes, which can be more than two, indexed by $k \in \{ 1 , \ldots , | { \mathcal { C } } | \}$ . Recall Eq. (12) or (15) where we are using the scaled posterior, i.e., $f _ { k } ( { \pmb x } ) \pi _ { k } . \operatorname { A c - }$ cording to Eq. (16), we have: 

$$
\begin{array}{l} f _ {k} (\boldsymbol {x}) \pi_ {k} \\ = \frac {1}{\sqrt {(2 \pi) ^ {d} | \boldsymbol {\Sigma} _ {k} |}} \exp \Big (- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {k})}{2} \Big) \pi_ {k}. \end{array}
$$

Taking natural logarithm gives: 

$$
\begin{array}{c} \ln (f _ {k} (\boldsymbol {x})   \pi_ {k}) = - \frac {d}{2} \ln (2 \pi) - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {k} |) \\ - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) + \ln (\pi_ {k}). \end{array}
$$

We drop the constant term $- ( d / 2 ) \ln ( 2 \pi )$ which is the same for all classes (note that this term is multiplied before taking the logarithm). Thus, the scaled posterior of the k-th class becomes: 

$$
\begin{array}{c} \delta_ {k} (\boldsymbol {x}) := - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {k} |) \\ - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) + \ln (\pi_ {k}). \end{array}\tag{28}
$$

In QDA, the class of the instance x is estimated as: 

$$
\widehat {\mathcal {C}} (\boldsymbol {x}) = \arg \max _ {k} \delta_ {k} (\boldsymbol {x}),\tag{29}
$$

because it maximizes the posterior of that class. In this expression, $\delta ( { \pmb x } )$ is Eq. (28). 

In LDA, we assume that the covariance matrices of the k classes are equal: 

$$
\boldsymbol {\Sigma} _ {1} = \dots = \boldsymbol {\Sigma} _ {| \mathcal {C} |} = \boldsymbol {\Sigma}.\tag{30}
$$

Therefore, the Eq. (28) becomes: 

$$
\begin{array}{l} \delta_ {k} (\boldsymbol {x}) = - \frac {1}{2} \ln (| \boldsymbol {\Sigma} |) \\ - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) + \ln (\pi_ {k}) = - \frac {1}{2} \ln (| \boldsymbol {\Sigma} |) \\ - \frac {1}{2} \boldsymbol {x} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} - \frac {1}{2} \boldsymbol {\mu} _ {k} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {\mu} _ {k} + \boldsymbol {\mu} _ {k} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} + \ln (\pi_ {k}). \end{array}
$$

We drop the constant terms $- ( 1 / 2 ) \ln ( | \Sigma | )$ and $- ( 1 / 2 ) \bar { \mathbf { \Phi } } \bar { \mathbf { x } } ^ { \top } \bar { \mathbf { \Xi } } \bar { \mathbf { x } } ^ { - 1 } \mathbf { \Lambda }$ which are the same for all classes (note that before taking the logarithm, the term $- ( 1 / 2 ) \ln ( | \Sigma | )$ is multiplied and the term $- ( 1 / 2 ) \mathbf { \boldsymbol { x } } ^ { \intercal } \mathbf { \boldsymbol { \Sigma } } ^ { - 1 }$ x is multiplied as an exponential term). Thus, the scaled posterior of the k-th class becomes: 

$$
\delta_ {k} (\boldsymbol {x}) := \boldsymbol {\mu} _ {k} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} - \frac {1}{2} \boldsymbol {\mu} _ {k} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {\mu} _ {k} + \ln (\pi_ {k}).\tag{31}
$$

In LDA, the class of the instance x is determined by Eq. (29), where δ(x) is Eq. (31), because it maximizes the posterior of that class. 

In conclusion, QDA and LDA deal with maximizing the posterior of classes but work with the likelihoods (class conditional) and priors. 

## 6. Estimation of Parameters in LDA and QDA

In LDA and QDA, we have several parameters which are required in order to calculate the posteriors. These parameters are the means and the covariance matrices of classes and the priors of classes. 

The priors of the classes are very tricky to calculate. It is somewhat a chicken and egg problem because we want to know the class probabilities (priors) to estimate the class of an instance but we do not have the priors and should estimate them. Usually, the prior of the k-th class is estimated according to the sample size of the k-th class: 

$$
\widehat {\pi} _ {k} = \frac {n _ {k}}{n},\tag{32}
$$

where $n _ { k }$ and n are the number of training instances in the k-th class and in total, respectively. This estimation considers Bernoulli distribution for choosing every instance out of the overall training set to be in the k-th class. 

The mean of the k-th class can be estimated using the Maximum Likelihood Estimation (MLE), or Method of Moments (MOM), for the mean of a Gaussian distribution: 

$$
\mathbb {R} ^ {d} \ni \widehat {\boldsymbol {\mu}} _ {k} = \frac {1}{n _ {k}} \sum_ {i = 1} ^ {n} \boldsymbol {x} _ {i} \mathbb {I} \big (\mathcal {C} (\boldsymbol {x} _ {i}) = k \big),\tag{33}
$$

where I(.) is the indicator function which is one and zero if its condition is satisfied and not satisfied, respectively. In QDA, the covariance matrix of the k-th class is estimated using MLE: 

$$
\begin{array}{l} \mathbb {R} ^ {d \times d} \ni \widehat {\boldsymbol {\Sigma}} _ {k} = \\ \frac {1}{n _ {k}} \sum_ {i = 1} ^ {n} (\boldsymbol {x} _ {i} - \widehat {\boldsymbol {\mu}} _ {k}) (\boldsymbol {x} _ {i} - \widehat {\boldsymbol {\mu}} _ {k}) ^ {\top} \mathbb {I} \big (\mathcal {C} (\boldsymbol {x} _ {i}) = k \big). \end{array}\tag{34}
$$

Or we can use the unbiased estimation of the covariance matrix: 

$$
\begin{array}{l} \mathbb {R} ^ {d \times d} \ni \widehat {\boldsymbol {\Sigma}} _ {k} = \\ \frac {1}{n _ {k} - 1} \sum_ {i = 1} ^ {n} (\boldsymbol {x} _ {i} - \widehat {\boldsymbol {\mu}} _ {k}) (\boldsymbol {x} _ {i} - \widehat {\boldsymbol {\mu}} _ {k}) ^ {\top} \mathbb {I} \big (\mathcal {C} (\boldsymbol {x} _ {i}) = k \big). \end{array}\tag{35}
$$

In LDA, we assume that the covariance matrices of the classes are equal; therefore, we use the weighted average of the estimated covariance matrices as the common covariance matrix in LDA: 

$$
\mathbb {R} ^ {d \times d} \ni \widehat {\boldsymbol {\Sigma}} = \frac {\sum_ {k = 1} ^ {| \mathcal {C} |} n _ {k} \widehat {\boldsymbol {\Sigma}} _ {k}}{\sum_ {r = 1} ^ {| \mathcal {C} |} n _ {r}} = \frac {\sum_ {k = 1} ^ {| \mathcal {C} |} n _ {k} \widehat {\boldsymbol {\Sigma}} _ {k}}{n},\tag{36}
$$

where the weights are the cardinality of the classes. 

## 7. LDA and QDA are Metric Learning!

Recall Eq. (28) which is the scaled posterior for the QDA. First, assume that the covariance matrices are all equal (as we have in LDA) and they all are the identity matrix: 

$$
\boldsymbol {\Sigma} _ {1} = \dots = \boldsymbol {\Sigma} _ {| \mathcal {C} |} = \boldsymbol {I},\tag{37}
$$

which means that all the classes are assumed to be spherically distributed in the d dimensional space. After this assumption, the Eq. (28) becomes: 

$$
\delta_ {k} (\boldsymbol {x}) = - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) + \ln (\pi_ {k}),\tag{38}
$$

because $| I | = 1 , \ln ( 1 ) = 0$ , and $\pmb { I } ^ { - 1 } = \pmb { I }$ . If we assume that the priors are all equal, the term ln(π ) is constant and can be dropped: 

$$
\delta_ {k} (\boldsymbol {x}) = - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) = - \frac {1}{2} d _ {k} ^ {2},\tag{39}
$$

where $d _ { k }$ is the Euclidean distance from the mean of the k-th class: 

$$
d _ {k} = \left\| \boldsymbol {x} - \boldsymbol {\mu} _ {k} \right\| _ {2} = \sqrt {\left(\boldsymbol {x} - \boldsymbol {\mu} _ {k}\right) ^ {\top} \left(\boldsymbol {x} - \boldsymbol {\mu} _ {k}\right)}.\tag{40}
$$

Thus, the QDA or LDA reduce to simple Euclidean distance from the means of classes if the covariance matrices are all identity matrix and the priors are equal. Simple distance from the mean of classes is one of the simplest classification methods where the used metric is Euclidean distance. 

![image](<Images/07_LDA_and_QDA_are_Metric_Learning_image_001.jpg>)



Figure 2. The QDA and LDA where the covariance matrices are identity matrix. For equal priors, the QDA and LDA reduce to simple classification using Euclidean distance from means of classes. Changing the prior modifies the location of decision boundary where even one point can be classified differently for different priors.


The Eq. (39) has a very interesting message. We know that in metric Multi-Dimensional Scaling (MDS) (Cox & Cox, 2000) and kernel Principal Component Analysis (PCA), we have (see (Ham et al., 2004) and Chapter 2 in (Strange & Zwiggelaar, 2014)): 

$$
\boldsymbol {K} = - \frac {1}{2} \boldsymbol {H} \boldsymbol {D} \boldsymbol {H},\tag{41}
$$

where $D \in \mathbb { R } ^ { n \times n }$ is the distance matrix whose elements are the distances between the data instances, $\ b { K } \in \mathbb { R } ^ { n \times n }$ is the kernel matrix over the data instances, $\mathbb { R } ^ { n \times n } \ni H : =$ $\pmb { I } - ( 1 / n ) \mathbf { 1 1 } ^ { \top }$ is the centering matrix, and $\mathbb { R } ^ { n } \ni \mathbf { 1 } : =$ $[ 1 , 1 , \ldots , 1 ] ^ { \top }$ . If the elements of the distance matrix D are obtained using Euclidean distance, the MDS is equivalent to Principal Component Analysis (PCA) (Jolliffe, 2011). 

Comparing Eqs. (39) and (41) shows an interesting connection between the posterior of a class in QDA and the kernel over the the data instances of the class. In this comparison, the Eq. (41) should be considered for a class and not the entire data, so $\pmb { K } \in \mathbb { R } ^ { n _ { k } \times n _ { k } }$ $D \in \mathbb { R } ^ { n _ { k } \times n _ { k } }$ , and $\pmb { H } \in \mathbb { R } ^ { n _ { k } \times n _ { k } }$ 

Now, consider the case where still the covariance matrices are all identity matrix but the priors are not equal. In this case, we have Eq. (38). If we take an exponential (inverse of logarithm) from this expression, the $\pi _ { k }$ becomes a scale factor (weight). This means that we still are using distance metric to measure the distance of an instance from the means of classes but we are scaling the distances by the priors of classes. If a class happens more, i.e., its prior is larger, it must have a larger posterior so we reduce the distance from the mean of its class. In other words, we move the decision boundary according to the prior of classes (see Fig. 2). 

As the next step, consider a more general case where the covariance matrices are not equal as we have in QDA. We apply Singular Value Decomposition (SVD) to the covariance matrix of the k-th class: 

$$
\pmb {\Sigma} _ {k} = \pmb {U} _ {k} \pmb {\Lambda} _ {k} \pmb {U} _ {k} ^ {\top},
$$

where the left and right matrices of singular vectors are equal because the covariance matrix is symmetric. Therefore: 

$$
\pmb {\Sigma} _ {k} ^ {- 1} = \pmb {U} _ {k} \pmb {\Lambda} _ {k} ^ {- 1} \pmb {U} _ {k} ^ {\top},
$$

where $\pmb { U } _ { k } ^ { - 1 } \ : = \ : \pmb { U } _ { k } ^ { \top }$ because it is an orthogonal matrix. Therefore, we can simplify the following term: 

$$
\begin{array}{r l} & (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) \\ & = (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {U} _ {k} \boldsymbol {\Lambda} _ {k} ^ {- 1} \boldsymbol {U} _ {k} ^ {\top} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) \\ & = (\boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Lambda} _ {k} ^ {- 1} (\boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}). \end{array}
$$

As $\boldsymbol { \Lambda } _ { k } ^ { - 1 }$ is a diagonal matrix with non-negative elements (because it is covariance), we can decompose it as: 

$$
\boldsymbol {\Lambda} _ {k} ^ {- 1} = \boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} \boldsymbol {\Lambda} _ {k} ^ {- 1 / 2}.
$$

Therefore: 

$$
\begin{array}{r l} & (\boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Lambda} _ {k} ^ {- 1} (\boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}) \\ & = (\boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} \boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} (\boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}) \\ & \overset {(a)} {=} (\boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}) ^ {\top} \\ & (\boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}), \end{array}
$$

where (a) is because $\boldsymbol { \Lambda } _ { k } ^ { - \top / 2 } = \boldsymbol { \Lambda } _ { k } ^ { - 1 / 2 }$ because it is diagonal. We define the following transformation: 

$$
\phi_ {k}: \pmb {x} \mapsto \pmb {\Lambda} _ {k} ^ {- 1 / 2} \pmb {U} _ {k} ^ {\top} \pmb {x},\tag{42}
$$

which also results in the transformation of the mean: $\phi _ { k } : $ $\pmb { \mu } \mapsto \mathbf { { A } } _ { k } ^ { - 1 / 2 } \pmb { U } _ { k } ^ { \top } \pmb { \mu }$ . Therefore, the Eq. (28) can be restated as: 

$$
\begin{array}{l} \delta_ {k} (\boldsymbol {x}) = - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {k} |) \\ - \frac {1}{2} \left(\phi_ {k} (\boldsymbol {x}) - \phi_ {k} (\boldsymbol {\mu} _ {k})\right) ^ {\top} \left(\phi_ {k} (\boldsymbol {x}) - \phi_ {k} (\boldsymbol {\mu} _ {k})\right) + \ln (\pi_ {k}). \end{array}\tag{43}
$$

Ignoring the terms $- ( 1 / 2 ) \ln ( | \Sigma _ { k } | )$ and $\ln ( \pi _ { k } )$ , we can see that the transformation has changed the covariance matrix of the class to identity matrix. Therefore, the QDA (and also LDA) can be seen as simple comparison of distances from the means of classes after applying a transformation to the data of every class. In other words, we are learning the metric using the SVD of covariance matrix of every class. Thus, LDA and QDA can be seen as metric learning (Yang & Jin, 2006; Kulis, 2013) in a perspective. Note that in metric learning, a valid distance metric is defined as (Yang & Jin, 2006): 

$$
d _ {\boldsymbol {A}} ^ {2} (\boldsymbol {x}, \boldsymbol {\mu} _ {k}) := | | \boldsymbol {x} - \boldsymbol {\mu} _ {k} | | _ {\boldsymbol {A}} ^ {2} = (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {A} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}),\tag{44}
$$

where A is a positive semi-definite matrix, i.e., $A \succeq 0$ In QDA, we are also using $( { \pmb x } - { \pmb \mu } _ { k } ) ^ { \top } \pmb { \Sigma } _ { k } ^ { - 1 } ( { \pmb x } - { \pmb \mu } _ { k } )$ . The covariance matrix is positive semi-definite according to the characteristics of covariance matrix. Moreover, according to characteristics of a positive semi-definite matrix, the inverse of a positive semi-definite matrix is positive semidefinite so $\bar { \boldsymbol { \Sigma } } _ { k } ^ { - 1 } \succeq 0$ . Therefore, QDA is using metric learning (and as will be discussed in next section, it can be seen as a manifold learning method, too). 

It is also noteworthy that the QDA and LDA can also be seen as Mahalanobis distance (McLachlan, 1999; De Maesschalck et al., 2000) which is also a metric: 

$$
d _ {M} ^ {2} (\boldsymbol {x}, \boldsymbol {\mu}) := | | \boldsymbol {x} - \boldsymbol {\mu} | | _ {M} ^ {2} = (\boldsymbol {x} - \boldsymbol {\mu}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu}),\tag{45}
$$

where Σ is the covariance matrix of the cloud of data whose mean is $\pmb { \mu } .$ The intuition of Mahalanobis distance is that if we have several data clouds (e.g., classes), the distance from the class with larger variance should be scaled down because that class is taking more of the space so it is more probable to happen. The scaling down shows in the inverse of covariance matrix. Comparing $( { \pmb x } - { \pmb \mu } _ { k } ) ^ { \top } \pmb { \Sigma } _ { k } ^ { - 1 } ( { \pmb x } - { \pmb \mu } _ { k } )$ in QDA or LDA with Eq. (45) shows that QDA and LDA are sort of using Mahalanobis distance. 

$$
8. \mathrm{LDA} \stackrel {?} {=} \mathrm{FDA}
$$

In the previous section, we saw that LDA and QDA can be seen as metric learning. We know that metric learning can be seen as a family of manifold learning methods. We briefly explain the reason of this assertion: As $A \succeq 0 .$ , we can say $\overset { \vartriangle } { \boldsymbol { A } } = \boldsymbol { U } \boldsymbol { U } ^ { \top } \succeq 0$ . Therefore, Eq. (44) becomes: 

$$
\begin{array}{c} | | \boldsymbol {x} - \boldsymbol {\mu} _ {k} | | _ {\boldsymbol {A}} ^ {2} = (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {U} \boldsymbol {U} ^ {\top} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) \\ = (\boldsymbol {U} ^ {\top} \boldsymbol {x} - \boldsymbol {U} ^ {\top} \boldsymbol {\mu} _ {k}) ^ {\top} (\boldsymbol {U} ^ {\top} \boldsymbol {x} - \boldsymbol {U} ^ {\top} \boldsymbol {\mu} _ {k}), \end{array}
$$

which means that metric learning can be seen as comparison of simple Euclidean distances after the transformation $\phi : \pmb { x } \mapsto \pmb { U } ^ { \top } \pmb { x }$ which is a projection into a subspace with projection matrix U. Thus, metric learning is a manifold learning approach. This gives a hint that the Fisher Discriminant Analysis (FDA) (Fisher, 1936; Welling, 2005), which is a manifold learning approach (Tharwat et al., 2017), might have a connection to LDA; especially, because the names FDA and LDA are often used interchangeably in the literature. Actually, other names of FDA are Fisher LDA (FLDA) and even LDA. 

We know that if we project (transform) the data of a class using a projection vector u $, \in \mathbb { R } ^ { p }$ to a $p$ dimensional subspace $( p \leq d )$ , i.e.: 

$$
\boldsymbol {x} \mapsto \boldsymbol {u} ^ {\top} \boldsymbol {x},\tag{46}
$$

for all data instances of the class, the mean and the covariance matrix of the class are transformed as: 

$$
\boldsymbol {\mu} \mapsto \boldsymbol {u} ^ {\top} \boldsymbol {\mu},\tag{47}
$$

$$
\boldsymbol {\Sigma} \mapsto \boldsymbol {u} ^ {\top} \boldsymbol {\Sigma} \boldsymbol {u},\tag{48}
$$

because of characteristics of mean and variance. 

The Fisher criterion (Xu & Lu, 2006) is the ratio of the between-class variance, $\sigma _ { b } ^ { 2 } .$ , and within-class variance, $\sigma _ { w } ^ { 2 }$ : 

$$
f := \frac {\sigma_ {b} ^ {2}}{\sigma_ {w} ^ {2}} = \frac {(\boldsymbol {u} ^ {\top} \boldsymbol {\mu} _ {2} - \boldsymbol {u} ^ {\top} \boldsymbol {\mu} _ {1}) ^ {2}}{\boldsymbol {u} ^ {\top} \boldsymbol {\Sigma} _ {2} \boldsymbol {u} + \boldsymbol {u} ^ {\top} \boldsymbol {\Sigma} _ {1} \boldsymbol {u}} = \frac {(\boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})) ^ {2}}{\boldsymbol {u} ^ {\top} (\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1}) \boldsymbol {u}}.\tag{49}
$$

The FDA maximizes the Fisher criterion: 

$$
\underset {\boldsymbol {u}} {\text { maximize }} \frac {\left(\boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {2}}{\boldsymbol {u} ^ {\top} (\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1})   \boldsymbol {u}},\tag{50}
$$

which can be restated as: 

$$
\begin{array}{l l} \underset {\boldsymbol {u}} {\text { maximize }} & \left(\boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {2}, \\ \text { subject   to } & \boldsymbol {u} ^ {\top} (\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1})   \boldsymbol {u} = 1, \end{array}\tag{51}
$$

according to Rayleigh-Ritz quotient method (Croot, 2005). The Lagrangian (Boyd & Vandenberghe, 2004) is: 

$$
\mathcal {L} = \left(\boldsymbol {u} ^ {\top} \left(\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1}\right)\right) ^ {2} - \lambda \left(\boldsymbol {u} ^ {\top} \left(\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1}\right) \boldsymbol {u} - 1\right),
$$

where λ is the Lagrange multiplier. Equating the derivative of $\mathcal { L }$ to zero gives: 

$$
\begin{array}{l} \frac {\partial \mathcal {L}}{\partial \boldsymbol {u}} = 2 \left(\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1}\right) ^ {2} \boldsymbol {u} - 2 \lambda \left(\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1}\right) \boldsymbol {u} \stackrel {{\text { set }}} {{=}} \boldsymbol {0} \\ \implies \left(\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1}\right) ^ {2} \boldsymbol {u} = \lambda \left(\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1}\right) \boldsymbol {u}, \end{array}
$$

which is a generalized eigenvalue problem $\left( ( \mu _ { 2 } \textrm { -- } \right)$ $\pmb { \mu } _ { 1 } ) ^ { 2 } , ( \pmb { \Sigma } _ { 2 } + \pmb { \Sigma } _ { 1 } ) \big )$ according to (Ghojogh et al., 2019b). The projection vector is the eigenvector of $( \pmb { \Sigma } _ { 2 } ~ +$ $\Sigma _ { 1 } ) ^ { - 1 } ( \pmb { \mu } _ { 2 } - \pmb { \mu } _ { 1 } ) ^ { 2 }$ ; therefore, we can say: 

$$
\pmb {u} \propto (\pmb {\Sigma} _ {2} + \pmb {\Sigma} _ {1}) ^ {- 1} (\pmb {\mu} _ {2} - \pmb {\mu} _ {1}) ^ {2}.
$$

In LDA, the equality of covariance matrices is assumed. Thus, according to Eq. (18), we can say: 

$$
\pmb {u} \propto (2 \pmb {\Sigma}) ^ {- 1} (\pmb {\mu} _ {2} - \pmb {\mu} _ {1}) ^ {2} \propto \pmb {\Sigma} ^ {- 1} (\pmb {\mu} _ {2} - \pmb {\mu} _ {1}) ^ {2}.\tag{52}
$$

According to Eq. (46), we have: 

$$
\boldsymbol {u} ^ {\top} \boldsymbol {x} \propto \left(\boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1}) ^ {2}\right) ^ {\top} \boldsymbol {x}.\tag{53}
$$

Comparing Eq. (53) with Eq. (23) shows that LDA and FDA are equivalent up to a scaling factor $( \mu _ { 1 } \textrm { -- }$ ${ \pmb \mu } _ { 2 } ) ^ { \top } { \pmb \Sigma } ^ { - 1 } ( { \pmb \mu } _ { 1 } - { \pmb \mu } _ { 2 } )$ (note that this term is multiplied as an exponential factor before taking logarithm to obtain Eq. (23), so this term a scaling factor). Hence, we can say: 

$$
\mathrm{LDA} \equiv \mathrm{FDA}.\tag{54}
$$

In other words, FDA projects into a subspace. On the other hand, according to Section 7, LDA can be seen as a metric learning with a subspace where the Euclidean distance is used after projecting onto that subspace. The two subspaces of FDA and LDA are the same subspace. It should be noted that in manifold (subspace) learning, the scale does not matter because all the distances scale similarly. Note that LDA assumes one (and not several) Gaussian for every class and so does the FDA. That is why FDA faces problem for multi-modal data (Sugiyama, 2007). 

## 9. Relation to Logistic Regression

According to Eqs. (16) and (32), Gaussian and Bernoulli distributions are used for likelihood (class conditional) and prior, respectively, in LDA and QDA. Thus, we are making assumptions for the likelihood and prior, although we finally work with posterior in LDA and QDA according to Eq. (15). Logistic regression (Kleinbaum et al., 2002) says why do we make assumptions on the likelihood and prior when we want to work on posterior finally. Let us make assumption directly for the posterior. 

In logistic regression, first a linear function is applied to the data to have $\beta ^ { \top } { \boldsymbol x } ^ { \prime }$ where $\mathbb { R } ^ { d + 1 } \ni \pmb { x } ^ { \prime } = [ \pmb { x } ^ { \top } , \hat { 1 } ] ^ { \top }$ and $\beta \in \mathbb { R } ^ { d + 1 }$ include the intercept. Then, logistic function is used in order to have a value in range $( 0 , 1 )$ to simulate probability. Therefore, in logistic regression, the posterior is assumed to be: 

$$
\begin{array}{l} \mathbb {P} (\mathcal {C} (\boldsymbol {x}) \mid X = \boldsymbol {x}) \\ = \Big (\frac {\exp (\boldsymbol {\beta} ^ {\top} \boldsymbol {x} ^ {\prime})}{1 + \exp (\boldsymbol {\beta} ^ {\top} \boldsymbol {x} ^ {\prime})} \Big) ^ {\mathcal {C} (\boldsymbol {x})} \Big (\frac {1}{1 + \exp (\boldsymbol {\beta} ^ {\top} \boldsymbol {x} ^ {\prime})} \Big) ^ {1 - \mathcal {C} (\boldsymbol {x})}, \end{array}\tag{55}
$$

where $\mathcal { C } ( \pmb { x } ) \in \{ - 1 , + 1 \}$ for the two classes. Logistic regression considers the coefficient $\beta$ as the parameter to be optimized and uses Newton’s method (Boyd & Vandenberghe, 2004) for the optimization. Therefore, in summary, logistic regression makes assumption on the posterior while LDA and QDA make assumption on likelihood and prior. 

## 10. Relation to Bayes Optimal Classifier and Gaussian Naive Bayes

The Bayes classifier maximizes the posteriors of the classes (Murphy, 2012): 

$$
\widehat {\mathcal {C}} (\boldsymbol {x}) = \arg \max _ {k} \mathbb {P} (\boldsymbol {x} \in \mathcal {C} _ {k} \mid X = \boldsymbol {x}).\tag{56}
$$

According to Eq. (14) and Bayes rule, we have: 

$$
\mathbb {P} (\boldsymbol {x} \in \mathcal {C} _ {k} \mid X = \boldsymbol {x}) \propto \mathbb {P} (X = \boldsymbol {x} \mid \boldsymbol {x} \in \mathcal {C} _ {k}) \underbrace {\mathbb {P} (\boldsymbol {x} \in \mathcal {C} _ {k})} _ {\pi_ {k}},\tag{57}
$$

where the denominator of posterior (the marginal) which is: 

$$
\mathbb {P} (X = \boldsymbol {x}) = \sum_ {r = 1} ^ {| \mathcal {C} |} \mathbb {P} (X = \boldsymbol {x} \mid \boldsymbol {x} \in \mathcal {C} _ {r}) \pi_ {r},
$$

is ignored because it is not dependent on the classes $\mathcal { C } _ { 1 }$ to $\mathcal { C } _ { | \mathcal { C } | }$ 

According to Eq. (57), the posterior can be written in terms of likelihood and prior; therefore, Eq. (56) can be restated as: 

$$
\widehat {\mathcal {C}} (\boldsymbol {x}) = \arg \max _ {k} \pi_ {k} \mathbb {P} (X = \boldsymbol {x} \mid \boldsymbol {x} \in \mathcal {C} _ {k}).\tag{58}
$$

Note that the Bayes classifier does not make any assumption on the posterior, prior, and likelihood, unlike LDA and QDA which assume the uni-modal Gaussian distribution for the likelihood (and we may assume Bernoulli distribution for the prior in LDA and QDA according to Eq. (32)). Therefore, we can say the difference of Bayes and QDA is in assumption of uni-modal Gaussian distribution for the likelihood (class conditional); hence, if the likelihoods are already uni-modal Gaussian, the Bayes classifier reduces to QDA. Likewise, the difference of Bayes and LDA is in assumption of Gaussian distribution for the likelihood (class conditional) and equality of covariance matrices of classes; thus, if the likelihoods are already Gaussian and the covariance matrices are already equal, the Bayes classifier reduces to LDA. 

It is noteworthy that the Bayes classifier is an optimal classifier because it can be seen as an ensemble of hypotheses (models) in the hypothesis (model) space and no other ensemble of hypotheses can outperform it (see Chapter $^ { 6 , }$ Page 175 in (Mitchell, 1997)). In the literature, it is referred to as Bayes optimal classifier. To better formulate the explained statements, the Bayes optimal classifier estimates the class as: 

$$
\widehat {\mathcal {C}} (\boldsymbol {x}) = \arg \max _ {\mathcal {C} _ {k} \in \mathcal {C}} \sum_ {h _ {j} \in \mathcal {H}} \mathbb {P} \left(\mathcal {C} _ {k} \mid h _ {j}\right) \mathbb {P} \left(\mathcal {D} \mid h _ {j}\right) \mathbb {P} \left(h _ {j}\right),\tag{59}
$$

where $\mathcal { C } : = \{ \mathcal { C } _ { 1 } , . . . , \mathcal { C } _ { | \mathcal { C } | } \} , \mathcal { D } : = \{ \pmb { x } _ { i } \} _ { i = 1 } ^ { n }$ is the training set, $h _ { j }$ is a hypothesis for estimating the class of instances, and H is the hypothesis space including all possible hypotheses. 

According to Bayes rule, similar to what we had for $\operatorname { E q }$ (57), we have: 

$$
\mathbb {P} (h _ {j} \mid \mathcal {D}) \propto \mathbb {P} (\mathcal {D} \mid h _ {j}) \mathbb {P} (h _ {j}).
$$

Therefore, Eq. (59) becomes (Mitchell, 1997): 

$$
\widehat {\mathcal {C}} (\boldsymbol {x}) = \arg \max _ {\mathcal {C} _ {k} \in \mathcal {C}} \sum_ {h _ {j} \in \mathcal {H}} \mathbb {P} (\mathcal {C} _ {k} \mid h _ {j}) \mathbb {P} (h _ {j} \mid \mathcal {D}),\tag{60}
$$

In conclusion, the Bayes classifier is optimal. Therefore, if the likelihoods of classes are Gaussian, QDA is an optimal classifier and if the likelihoods are Gaussian and the covariance matrices are equal, the LDA is an optimal classifier. Often, the distributions in the natural life are Gaussian; especially, because of central limit theorem (Hazewinkel, 2001), the summation of independent and identically distributed (iid) variables is Gaussian and the signals usually add in the real world. This explains why LDA and QDA are very effective classifiers in machine learning. We also saw that FDA is equivalent to LDA. Thus, the reason of effectiveness of the powerful FDA classifier becomes clear. We have seen the very successful performance of FDA and LDA in different applications, such as face recognition (Belhumeur et al., 1997; Etemad & Chellappa, 1997; Zhao et al., 1999), action recognition (Ghojogh et al., 2017; Mokari et al., 2018), and EEG classification (Malekmohammadi et al., 2019). 

Implementing Bayes classifier is difficult in practice so we approximate it by naive Bayes (Zhang, 2004). $\operatorname { I f } x _ { j }$ denotes the j-th dimension (feature) of $\pmb { x } = [ x _ { 1 } , \ldots , x _ { d } ] ^ { \top }$ , Eq. (58) is restated as: 

$$
\widehat {\mathcal {C}} (\boldsymbol {x}) = \arg \max _ {k} \pi_ {k} \mathbb {P} (x _ {1}, x _ {2}, \dots , x _ {d} | \boldsymbol {x} \in \mathcal {C} _ {k}).\tag{61}
$$

The term $\mathbb { P } ( x _ { 1 } , x _ { 2 } , \ldots , x _ { d } | \pmb { x } \in \mathcal { C } _ { k } )$ is very difficult to compute as the features are possibly correlated. Naive Bayes relaxes this possibility and naively assumes that the features are conditionally independent (⊥⊥) when they are conditioned on the class: 

$$
\begin{array}{l} \mathbb {P} (x _ {1}, x _ {2}, \ldots , x _ {d} \mid \boldsymbol {x} \in \mathcal {C} _ {k}) \\ \stackrel {{\perp}} {{\approx}} \mathbb {P} (x _ {1} \mid \mathcal {C} _ {k})   \mathbb {P} (x _ {2} \mid \mathcal {C} _ {k})   \dots   \mathbb {P} (x _ {d} \mid \mathcal {C} _ {k}) = \prod_ {j = 1} ^ {d} \mathbb {P} (x _ {j} \mid \mathcal {C} _ {k}). \end{array}
$$

Therefore, Eq. (61) becomes: 

$$
\widehat {\mathcal {C}} (\boldsymbol {x}) = \arg \max _ {k} \pi_ {k} \prod_ {j = 1} ^ {d} \mathbb {P} (x _ {j} \mid \mathcal {C} _ {k}).\tag{62}
$$

In Gaussian naive Bayes, univariate Gaussian distribution is assumed for the likelihood (class conditional) of every feature: 

$$
\mathbb {P} (x _ {j} \mid \mathcal {C} _ {k}) = \frac {1}{\sqrt {2 \pi \sigma_ {k} ^ {2}}} \exp \Bigl (- \frac {(x _ {j} - \mu_ {k}) ^ {2}}{2 \sigma_ {k} ^ {2}} \Bigr),\tag{63}
$$

where the mean and unbiased variance are estimated as: 

$$
\mathbb {R} \ni \widehat {\mu} _ {k} = \frac {1}{n _ {k}} \sum_ {i = 1} ^ {n} x _ {i, j} \mathbb {I} \big (\mathcal {C} (\boldsymbol {x} _ {i}) = k \big),\tag{64}
$$

$$
\mathbb {R} \ni \widehat {\sigma} _ {k} ^ {2} = \frac {1}{n _ {k} - 1} \sum_ {i = 1} ^ {n} (x _ {i, j} - \widehat {\mu} _ {k}) ^ {2} \mathbb {I} \big (\mathcal {C} (\boldsymbol {x} _ {i}) = k \big),\tag{65}
$$

where $x _ { i , j }$ denotes the j-th feature of the i-th training instance. The prior can again be estimated using Eq. (32). 

According to Eqs. (62) and (63), Gaussian naive Bayes is equivalent to QDA where the covariance matrices are diagonal, i.e., the off-diagonal of the covariance matrices are ignored. Therefore, we can say that QDA is more powerful than Gaussian naive Bayes because Gaussian naive Bayes is a simplified version of QDA. Moreover, it is obvious that Gaussian naive Bayes and QDA are equivalent for one dimensional data. Comparing to LDA, the Gaussian naive Bayes is equivalent to LDA if the covariance matrices are diagonal and they are all equal, i.e., $\sigma _ { 1 } ^ { 2 } = \cdots = \sigma _ { | { \mathcal { C } } | } ^ { 2 } ;$ therefore, LDA and Gaussian naive Bayes have their own assumptions, one on the off-diagonal of covariance matrices and the other one on equality of the covariance matrices. As Gaussian naive Bayes has some level of optimality (Zhang, 2004), it becomes clear why LDA and QDA are such effective classifiers. 

## 11. Relation to Likelihood Ratio Test

Consider two hypotheses for estimating some parameter, a null hypothesis $H _ { 0 }$ and an alternative hypothesis $H _ { A }$ The probability P(reject $H _ { 0 } \mid H _ { 0 } )$ is called type 1 error, false positive error, or false alarm error. The probability P(accept $H _ { 0 } \mid H _ { A } )$ is called type 2 error or false negative error. The P(reject $H _ { 0 } \mid H _ { 0 } )$ is also called significance level, while 1 − P(accept $H _ { 0 } \mid H _ { A } ) = \operatorname { \mathbb { P } } ( \operatorname { r e j e c t } H _ { 0 } \mid H _ { A } )$ is called power. 

If $L ( \theta _ { A } )$ and $L ( \theta _ { 0 } )$ are the likelihoods (probabilities) for the alternative and null hypotheses, the likelihood ratio is: 

$$
\Lambda = \frac {L (\theta_ {A})}{L (\theta_ {0})} = \frac {f (\boldsymbol {x} ; \theta_ {A})}{f (\boldsymbol {x} ; \theta_ {0})}.\tag{66}
$$

The Likelihood Ratio Test (LRT) (Casella & Berger, 2002) rejects the $H _ { 0 }$ in favor of $H _ { A }$ if the likelihood ratio is greater than a threshold, i.e., $\Lambda \geq t .$ The LRT is a very effective statistical test because according to the Neyman-Pearson lemma (Neyman & Pearson, 1933), it has the largest power among all statistical tests with the same significance level. 

If the sample size is large, $n \to \infty$ , and the $\theta _ { A }$ is estimated using MLE, the logarithm of the likelihood ratio asymptotically has the distribution of $\chi ^ { 2 }$ under the null hypothesis (White, 1984; Casella & Berger, 2002): 

$$
2 \ln (\Lambda) \stackrel {H _ {0}} {\sim} \chi_ {(d f)} ^ {2},\tag{67}
$$

where the degree of freedom of $\chi ^ { 2 }$ distribution is $d f : =$ dim $( H _ { A } ) - \mathrm { d i m } ( H _ { 0 } )$ and dim(.) is the number of unspecified parameters in the hypothesis. 

There is a connection between LDA or QDA and the LRT (Lachenbruch & Goldstein, 1979). Recall Eq. (12) or (15) which can be restated as: 

$$
\frac {f _ {2} (\pmb {x}) \pi_ {2}}{f _ {1} (\pmb {x}) \pi_ {1}} = 1,\tag{68}
$$

which is for the decision boundary. The Eq. (22) dealt with the difference of $f _ { 2 } ( x ) \pi _ { 2 }$ and $f _ { 1 } ( x ) \pi _ { 1 } ;$ however, here we are dealing with their ratio. Recall Fig. 1 where if we move $x ^ { * }$ to the right and left, the ratio $f _ { 2 } ( x ^ { * } ) \pi _ { 2 } / f _ { 1 } ( x ^ { * } ) \pi _ { 1 }$ decreases and increases, respectively, because the probabilities of the first and second class happening change. In other words, moving the $x ^ { * }$ changes the significance level and power. Therefore, Eq. (68) can be used to have a statistical test where the posteriors are used in the ratio, as we also used posteriors in LDA and QDA. The null/alternative hypothesis an be considered to be the mean and covariance of the first/second class. In other words, the two hypotheses say that the point belongs to a specific class. Hence, if the ratio is larger than a value t, the instance x is estimated to belong to the second class; otherwise, the first class is chosen. According to Eq. (16), the Eq. (68) becomes: 

$$
\frac {(| \pmb {\Sigma} _ {2} |) ^ {- 1 / 2} \exp \left(- \frac {1}{2} (\pmb {x} - \pmb {\mu} _ {2}) ^ {\top} \pmb {\Sigma} _ {2} ^ {- 1} (\pmb {x} - \pmb {\mu} _ {2})\right) \pi_ {2}}{(| \pmb {\Sigma} _ {1} |) ^ {- 1 / 2} \exp \left(- \frac {1}{2} (\pmb {x} - \pmb {\mu} _ {1}) ^ {\top} \pmb {\Sigma} _ {1} ^ {- 1} (\pmb {x} - \pmb {\mu} _ {1})\right) \pi_ {1}} \geq t,\tag{69}
$$

for QDA. In LDA, the covariance matrices are equal, so: 

$$
\frac {\exp \left(- \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {2})\right) \pi_ {2}}{\exp \left(- \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {1})\right) \pi_ {1}} \geq t.\tag{70}
$$

As can be seen, changing the priors change impacts the ratio as expected. Moreover, the value of t can be chosen according to the desired significance level in the $\chi ^ { 2 }$ distribution using the $\chi ^ { 2 }$ table. The Eqs. (69) and (70) show the relation of LDA and QDA with LRT. As the LRT has the largest power (Neyman & Pearson, 1933), the effectiveness of LDA and QDA in classification is explained from a hypothesis testing point of view. 

## 12. Simulations

In this section, we report some simulations which make the concepts of tutorial clearer by illustration. 

## 12.1. Experiments with Equal Class Sample Sizes

We created a synthetic dataset of three classes each of which is a two dimensional Gaussian distribution. The means and covariance matrices of the three Gaussians from which the class samples were randomly drawn are: 

![image](<Images/12_Simulations_image_001.jpg>)



(a)


![image](<Images/12_Simulations_image_002.jpg>)



(b)


![image](<Images/12_Simulations_image_003.jpg>)



(c)


![image](<Images/12_Simulations_image_004.jpg>)



(d)


![image](<Images/12_Simulations_image_005.jpg>)



(e)


![image](<Images/12_Simulations_image_006.jpg>)



(f)


![image](<Images/12_Simulations_image_007.jpg>)



(g)



Figure 3. The synthetic dataset: (a) three classes each with size 200, (b) two classes each with size 200, (c) three classes each with size 10, (d) two classes each with size 10, (e) three classes with sizes 200, 100, and 10, (f) two classes with sizes 200 and 10, and (g) two classes with sizes 400 and 200 where the larger class has two modes.


$$
\boldsymbol {\mu} _ {1} = [ - 4, 4 ] ^ {\top}, \boldsymbol {\mu} _ {2} = [ 3, - 3 ] ^ {\top}, \boldsymbol {\mu} _ {1} = [ - 3, 3 ] ^ {\top},
$$

$$
\boldsymbol {\Sigma} _ {1} = \left[ \begin{array}{c c} 1 0 & 1 \\ 1 & 5 \end{array} \right], \boldsymbol {\Sigma} _ {2} = \left[ \begin{array}{c c} 3 & 0 \\ 0 & 4 \end{array} \right], \boldsymbol {\Sigma} _ {3} = \left[ \begin{array}{c c} 6 & 1. 5 \\ 1. 5 & 4 \end{array} \right].
$$

The three classes are shown in Fig. 3-a where each has sample size 200. Experiments were performed on the three classes. We also performed experiments on two of the three classes to test a binary classification. The two classes are shown in Fig. 3-b. The LDA, QDA, naive Bayes, and 

![image](<Images/12_Simulations_image_008.jpg>)



(a)


![image](<Images/12_Simulations_image_009.jpg>)



(b)


![image](<Images/12_Simulations_image_010.jpg>)



(c)


![image](<Images/12_Simulations_image_011.jpg>)



(d)


![image](<Images/12_Simulations_image_012.jpg>)



(e)


![image](<Images/12_Simulations_image_013.jpg>)



(f)


![image](<Images/12_Simulations_image_014.jpg>)



(g)


![image](<Images/12_Simulations_image_015.jpg>)



(h)



Figure 4. Experiments with equal class sample sizes: (a) LDA for two classes, (b) QDA for two classes, (c) Gaussian naive Bayes for two classes, (d) Bayes for two classes, (e) LDA for three classes, (f) QDA for three classes, (g) Gaussian naive Bayes for three classes, and (h) Bayes for three classes.


Bayes classifications of the two and three classes are shown in Fig. 4. For both binary and ternary classification with LDA and QDA, we used Eqs. (31) and (28), respectively, with Eq. (29). We also estimated the mean and covariance using Eqs. (33), (35), and (36). For Gaussian naive Bayes, we used Eqs. (62) and (63) and estimated the parameters using Eqs. (64) and (65). For Bayes classifier, we used Eq. (58) with Eq. (63) but we do not estimate the mean and variance; except, in order to use the exact likelihoods in Eq. (58), we use the exact mean and covariance matrices of the distributions which we sampled from. We, however, estimated the priors. The priors were estimated using Eq. (32) for all the classifiers. 

![image](<Images/12_Simulations_image_016.jpg>)



(a)


![image](<Images/12_Simulations_image_017.jpg>)



(b)


![image](<Images/12_Simulations_image_018.jpg>)



(c)


![image](<Images/12_Simulations_image_019.jpg>)



(d)


![image](<Images/12_Simulations_image_020.jpg>)



(e)


![image](<Images/12_Simulations_image_021.jpg>)



(f)


![image](<Images/12_Simulations_image_022.jpg>)



(g)


![image](<Images/12_Simulations_image_023.jpg>)



(h)



Figure 5. Experiments with small class sample sizes: (a) LDA for two classes, (b) QDA for two classes, (c) Gaussian naive Bayes for two classes, (d) Bayes for two classes, (e) LDA for three classes, (f) QDA for three classes, (g) Gaussian naive Bayes for three classes, and (h) Bayes for three classes.


As can be seen in Fig. 4, the space is partitioned into two/three parts and this validates the assertion that LDA and QDA can be considered as metric learning methods as discussed in Section 7. As expected, the boundaries of 

LDA and QDA are linear and curvy (quadratic), respectively. The results of QDA, Gaussian naive Bayes, and Bayes are very similar although they have slight differences. This is because the classes are already Gaussian so if the estimates of means and covariance matrices are accurate enough, QDA and Bayes are equivalent. The classes are Gaussians and the off-diagonal elements of covariance matrices are also small compared to the diagonal; therefore, naive Bayes is also behaving similarly. 

![image](<Images/12_Simulations_image_024.jpg>)



(a)


![image](<Images/12_Simulations_image_025.jpg>)



(b)


![image](<Images/12_Simulations_image_026.jpg>)



(c)


![image](<Images/12_Simulations_image_027.jpg>)



(d)


![image](<Images/12_Simulations_image_028.jpg>)



(e)


![image](<Images/12_Simulations_image_029.jpg>)



(f)


![image](<Images/12_Simulations_image_030.jpg>)



(g)


![image](<Images/12_Simulations_image_031.jpg>)



(h)



Figure 6. Experiments with different class sample sizes: (a) LDA for two classes, (b) QDA for two classes, (c) Gaussian naive Bayes for two classes, (d) Bayes for two classes, (e) LDA for three classes, (f) QDA for three classes, (g) Gaussian naive Bayes for three classes, and (h) Bayes for three classes.


## 12.2. Experiments with Small Class Sample Sizes

According to Monte-Carlo approximation (Robert & Casella, 2013), the estimates in Eqs. (33), (35), (64) and (65) are more accurate if the sample size goes to infinity, i.e., $n  \infty$ . Therefore, if the sample size is small, we expect mode difference between QDA and Bayes classifiers. We made a synthetic dataset with three or two classes with the same mentioned means and covariance matrices. The sample size of every class was 10. Figures 3-c and 3-d show these datasets. The results of LDA, QDA, Gaussian naive Bayes, and Bayes classifiers for this dataset are shown in Fig. 5. As can be seen, now, the results of QDA, Gaussian naive Bayes, and Bayes are different for the reason explained. 

![image](<Images/12_Simulations_image_032.jpg>)



(a)


![image](<Images/12_Simulations_image_033.jpg>)



(b)


![image](<Images/12_Simulations_image_034.jpg>)



(c)


![image](<Images/12_Simulations_image_035.jpg>)



(d)



Figure 7. Experiments with multi-modal data: (a) LDA, (b) QDA, (c) Gaussian naive Bayes, and (d) Bayes.


## 12.3. Experiments with Different Class Sample Sizes

According to Eq. (32) used in Eqs. (28), (31), (58), and (62), the prior of a class changes by the sample size of the class. In order to see the effect of sample size, we made a synthetic dataset with different class sizes, i.e., 200, 100, and 10, shown in Figs. 3-e, 3-f. We used the same mentioned means and covariance matrices. The results are shown in Fig. 6. As can be seen, the class with small sample size has covered a small portion of space in discrimination which is expected because its prior is small according to Eq. (32); therefore, its posterior is small. On the other hand, the class with large sample size has covered a larger portion because of a larger prior. 

## 12.4. Experiments with Multi-Modal Data

As mentioned in Section 8, LDA and QDA assume unimodal Gaussian distribution for every class and thus FDA or LDA faces problem for multi-modal data (Sugiyama, 2007). For testing this, we made a synthetic dataset with two classes, one with sample size 400 having two modes of Gaussians and the other with sample size 200 having one mode. We again used the same mentioned means and covariance matrices. The dataset is shown in Fig. 3-g. 

The results of the LDA, QDA, Gaussian naive Bayes, and Bayes classifiers for this dataset are shown in Fig. 7. The mean and covariance matrix of the larger class, although it has two modes, were estimated using Eqs. (33), (35), (64) and (65) in LDA, QDA, and Gaussian naive Bayes. However, for the likelihood used in Bayes classifier, i.e., in Eq. (58), we need to know the exact multi-modal distribution. Therefore, we fit a mixture of two Gaussians (Ghojogh et al., 2019a) to the data of the larger class: 

$$
\mathbb {P} (X = \boldsymbol {x} \mid \boldsymbol {x} \in \mathcal {C} _ {k}) = \sum_ {k = 1} ^ {2} w _ {k} f (\boldsymbol {x}; \boldsymbol {\mu} _ {k}, \boldsymbol {\Sigma} _ {k}),\tag{71}
$$

where $f ( \pmb { x } ; \pmb { \mu } _ { k } , \pmb { \Sigma } _ { k } )$ is $\operatorname { E q } .$ . (16) and we the fitted parame-

ters were: 

$$
\begin{array}{l} \boldsymbol {\mu} _ {1} = [ - 3. 8 8, 4 ] ^ {\top}, \boldsymbol {\mu} _ {2} = [ 3. 0 4, - 2. 9 2 ] ^ {\top}, \\ \boldsymbol {\Sigma} _ {1} = \left[ \begin{array}{c c} 9. 2 7 & 0. 7 9 \\ 0. 7 9 & 4. 8 2 \end{array} \right], \boldsymbol {\Sigma} _ {2} = \left[ \begin{array}{c c} 2. 8 7 & 0. 0 3 \\ 0. 0 3 & 3. 7 8 \end{array} \right], \\ w _ {1} = 0. 4 9, w _ {2} = 0. 5 0 2. \end{array}
$$

As Fig. 7 shows, LDA has not performed well enough as expected. The performance of QDA is more acceptable than LDA but still not good enough because QDA also assumes a uni-modal Gaussian for every class. The result of Gaussian naive Bayes is very different from the Bayes here because the Gaussian naive Bayes assumes unimodal Gaussian with diagonal covariance for every class. Finally, the Bayes has the best result as it takes into account the multi-modality of the data and it is optimum (Mitchell, 1997). 

## 13. Conclusion and Future Work

This paper was a tutorial paper for LDA and QDA as two fundamental classification methods. We explained the relations of these two methods with some other methods in machine learning, manifold (subspace) learning, metric learning, statistics, and statistical testing. Some simulations were also provided for better clarification. 

This paper focused on LDA and QDA which are discriminators with one and two polynomial degrees of freedom, respectively. As the future work, we will work on a tutorial paper for non-linear discriminant analysis using kernels (Baudat & Anouar, 2000; Li et al., 2003; Lu et al., 2003), which is called kernel discriminant analysis, to have discriminators with more than two degrees of freedom. 

## Acknowledgment

The authors hugely thank Prof. Ali Ghodsi (see his great online related courses (Ghodsi, 2015; 2017)), Prof. Mu Zhu, Prof. Hoda Mohammadzade, and other professors whose courses have partly covered the materials mentioned in this tutorial paper. 

## References



Baudat, Gaston and Anouar, Fatiha. Generalized discriminant analysis using a kernel approach. Neural computation, 12(10):2385–2404, 2000. 





Belhumeur, Peter N, Hespanha, Joao P, and Kriegman,˜ David J. Eigenfaces vs. Fisherfaces: Recognition using class specific linear projection. IEEE Transactions on Pattern Analysis & Machine Intelligence, (7):711–720, 1997. 





Boyd, Stephen and Vandenberghe, Lieven. Convex optimization. Cambridge university press, 2004. 





Casella, George and Berger, Roger L. Statistical inference, volume 2. Duxbury Pacific Grove, CA, 2002. 





Cox, Trevor F and Cox, Michael AA. Multidimensional scaling. Chapman and hall/CRC, 2000. 





Croot, Ernie. The Rayleigh principle for finding eigenvalues. Technical report, Georgia Institute of Technology, School of Mathematics, 2005. Online: http://people.math.gatech.edu/∼ecroot/notes_linear.pdf, Accessed: March 2019. 





De Maesschalck, Roy, Jouan-Rimbaud, Delphine, and Massart, Desir´ e L. The Mahalanobis distance.´ Chemometrics and intelligent laboratory systems, 50(1):1–18, 2000. 





Etemad, Kamran and Chellappa, Rama. Discriminant analysis for recognition of human face images. Journal ofthe Optical Society ofAmerica A, 14(8):1724–1733, 1997. 





Fisher, Ronald A. The use of multiple measurements in taxonomic problems. Annals of eugenics, 7(2):179–188, 1936. 





Friedman, Jerome, Hastie, Trevor, and Tibshirani, Robert. The elements of statistical learning, volume 2. Springer series in statistics, New York, NY, USA, 2009. 





Ghodsi, Ali. Classification course, department of statistics and actuarial science, university of Waterloo. Online Youtube Videos, 2015. Accessed: January 2019. 





Ghodsi, Ali. Data visualization course, department of statistics and actuarial science, university of Waterloo. Online Youtube Videos, 2017. Accessed: January 2019. 





Ghojogh, Benyamin, Mohammadzade, Hoda, and Mokari, Mozhgan. Fisherposes for human action recognition using Kinect sensor data. IEEE Sensors Journal, 18(4): 1612–1627, 2017. 





Ghojogh, Benyamin, Ghojogh, Aydin, Crowley, Mark, and Karray, Fakhri. Fitting a mixture distribution to data: Tutorial. arXiv preprint arXiv:1901.06708, 2019a. 





Ghojogh, Benyamin, Karray, Fakhri, and Crowley, Mark. Eigenvalue and generalized eigenvalue problems: Tutorial. arXiv preprint arXiv:1903.11240, 2019b. 





Ham, Ji Hun, Lee, Daniel D, Mika, Sebastian, and Scholkopf, Bernhard. A kernel view of the dimensional-¨ ity reduction of manifolds. In International Conference on Machine Learning, 2004. 





Hazewinkel, Michiel. Central limit theorem. Encyclopedia of Mathematics, Springer, 2001. 





Jolliffe, Ian. Principal component analysis. Springer, 2011. 





Kleinbaum, David G, Dietz, K, Gail, M, Klein, Mitchel, and Klein, Mitchell. Logistic regression. Springer, 2002. 





Kulis, Brian. Metric learning: A survey. Foundations and Trends R in Machine Learning, 5(4):287–364, 2013. 





Lachenbruch, Peter A and Goldstein, M. Discriminant analysis. Biometrics, pp. 69–85, 1979. 





Li, Yongmin, Gong, Shaogang, and Liddell, Heather. Recognising trajectories of facial identities using kernel discriminant analysis. Image and Vision Computing, 21 (13-14):1077–1086, 2003. 





Lu, Juwei, Plataniotis, Konstantinos N, and Venetsanopoulos, Anastasios N. Face recognition using kernel direct discriminant analysis algorithms. IEEE Transactions on Neural Networks, 14(1):117–126, 2003. 





Malekmohammadi, Alireza, Mohammadzade, Hoda, Chamanzar, Alireza, Shabany, Mahdi, and Ghojogh, Benyamin. An efficient hardware implementation for a motor imagery brain computer interface system. Scientia Iranica, 26:72–94, 2019. 





McLachlan, Goeffrey J. Mahalanobis distance. Resonance, 4(6):20–26, 1999. 





Mitchell, Thomas. Machine learning. McGraw Hill Higher Education, 1997. 





Mokari, Mozhgan, Mohammadzade, Hoda, and Ghojogh, Benyamin. Recognizing involuntary actions from 3d skeleton data using body states. Scientia Iranica, 2018. 





Murphy, Kevin P. Machine learning: a probabilistic perspective. MIT press, 2012. 





Neyman, Jerzy and Pearson, Egon Sharpe. IX. On the problem of the most efficient tests of statistical hypotheses. Philosophical Transactions of the Royal Society of London. Series A, Containing Papers of a Mathematical or Physical Character, 231(694-706):289–337, 1933. 





Robert, Christian and Casella, George. Monte Carlo statistical methods. Springer Science & Business Media, 2013. 





Strange, Harry and Zwiggelaar, Reyer. Open Problems in Spectral Dimensionality Reduction. Springer, 2014. 





Sugiyama, Masashi. Dimensionality reduction of multimodal labeled data by local fisher discriminant analysis. Journal of machine learning research, 8(May):1027– 1061, 2007. 





Tharwat, Alaa, Gaber, Tarek, Ibrahim, Abdelhameed, and Hassanien, Aboul Ella. Linear discriminant analysis: A detailed tutorial. AI communications, 30(2):169–190, 2017. 





Welling, Max. Fisher linear discriminant analysis. Technical report, University of Toronto, Toronto, Ontario, Canada, 2005. 





White, Halbert. Asymptotic theory for econometricians. Academic press, 1984. 





Xu, Yong and Lu, Guangming. Analysis on fisher discriminant criterion and linear separability of feature space. In 2006 International Conference on Computational Intelligence and Security, volume 2, pp. 1671–1676. IEEE, 2006. 





Yang, Liu and Jin, Rong. Distance metric learning: A comprehensive survey. Technical report, Department of Computer Science and Engineering, Michigan State University, 2006. 





Zhang, Harry. The optimality of naive Bayes. In American Associationfor Artificial Intelligence (AAAI), 2004. 





Zhao, Wenyi, Chellappa, Rama, and Phillips, P Jonathon. Subspace linear discriminant analysis for face recognition. Citeseer, 1999. 

