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

