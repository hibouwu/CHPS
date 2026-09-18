Linear Methods for Regression 

## 3.1 Introduction

A linear regression model assumes that the regression function $\operatorname { E } ( Y | X )$ is linear in the inputs $X _ { 1 } , \ldots , X _ { p } .$ . Linear models were largely developed in the precomputer age of statistics, but even in today’s computer era there are still good reasons to study and use them. They are simple and often provide an adequate and interpretable description of how the inputs affect the output. For prediction purposes they can sometimes outperform fancier nonlinear models, especially in situations with small numbers of training cases, low signal-to-noise ratio or sparse data. Finally, linear methods can be applied to transformations of the inputs and this considerably expands their scope. These generalizations are sometimes called basis-function methods, and are discussed in Chapter 5. 

In this chapter we describe linear methods for regression, while in the next chapter we discuss linear methods for classification. On some topics we $\mathrm { g o }$ into considerable detail, as it is our firm belief that an understanding of linear methods is essential for understanding nonlinear ones. In fact, many nonlinear techniques are direct generalizations of the linear methods discussed here. 

## 3.2 Linear Regression Models and Least Squares

As introduced in Chapter 2, we have an input vector $X ^ { T } = ( X _ { 1 } , X _ { 2 } , \ldots , X _ { p } )$ and want to predict a real-valued output $Y$ . The linear regression model has the form 

$$
f (X) = \beta_ {0} + \sum_ {j = 1} ^ {p} X _ {j} \beta_ {j}.\tag{3.1}
$$

The linear model either assumes that the regression function $\operatorname { E } ( Y | X )$ is linear, or that the linear model is a reasonable approximation. Here the $\beta _ { j }$ ’s are unknown parameters or coefficients, and the variables $X _ { j }$ can come from different sources: 

quantitative inputs; 

transformations of quantitative inputs, such as log, square-root or square; 

basis expansions, such as $X _ { 2 } = X _ { 1 } ^ { 2 } , X _ { 3 } = X _ { 1 } ^ { 3 }$ , leading to a polynomial representation; 

numeric or “dummy” coding of the levels of qualitative inputs. For example, if G is a five-level factor input, we might create $X _ { j } , ~ j =$ $1 , \ldots , 5$ , such that $X _ { j } = I ( G = j )$ . Together this group of $X _ { j }$ represents the effect of G by a set of level-dependent constants, since in $\textstyle \sum _ { j = 1 } ^ { 5 } X _ { j } \beta _ { j }$ , one of the $X _ { j ^ { \mathrm { s } } }$ is one, and the others are zero. 

interactions between variables, for example, $X _ { 3 } = X _ { 1 } \cdot X _ { 2 }$ 

No matter the source of the $X _ { j }$ , the model is linear in the parameters. 

Typically we have a set of training data $\left( x _ { 1 } , y _ { 1 } \right) . . . \left( x _ { N } , y _ { N } \right)$ from which to estimate the parameters $\beta .$ Each $x _ { i } = ( x _ { i 1 } , x _ { i 2 } , \ldots , x _ { i p } ) ^ { T }$ is a vector of feature measurements for the ith case. The most popular estimation method is least squares, in which we pick the coefficients $\bar { \boldsymbol { \beta } } = ( \beta _ { 0 } , \beta _ { 1 } , \ldots , \beta _ { p } ) ^ { T }$ to minimize the residual sum of squares 

$$
\begin{array}{r c l} \text {RSS} (\beta) & = & \sum_ {i = 1} ^ {N} (y _ {i} - f (x _ {i})) ^ {2} \\ & = & \sum_ {i = 1} ^ {N} \Bigl (y _ {i} - \beta_ {0} - \sum_ {j = 1} ^ {p} x _ {i j} \beta_ {j} \Bigr) ^ {2}. \end{array}\tag{3.2}
$$

From a statistical point of view, this criterion is reasonable if the training observations $( x _ { i } , y _ { i } )$ represent independent random draws from their population. Even if the $x _ { i } \mathrm { { ' s } }$ were not drawn randomly, the criterion is still valid if the $y _ { i } \mathrm { \dot { s } }$ are conditionally independent given the inputs $x _ { i }$ . Figure 3.1 illustrates the geometry of least-squares fitting in the $\mathbb { R } ^ { p + 1 }$ -dimensional space occupied by the pairs (X, Y ). Note that (3.2) makes no assumptions about the validity of model (3.1); it simply finds the best linear fit to the data. Least squares fitting is intuitively satisfying no matter how the data arise; the criterion measures the average lack of fit. 

![image](<Images/03_Linear_Methods_for_Regression_image_001.jpg>)



FIGURE 3.1. Linear least squares fitting with $X \ \in \ \mathbb { R } ^ { 2 }$ . We seek the linear function of X that minimizes the sum of squared residuals from $Y$


How do we minimize (3.2)? Denote by X the $N \times ( p + 1 )$ matrix with each row an input vector (with a 1 in the first position), and similarly let $\mathbf { y }$ be the N-vector of outputs in the training set. Then we can write the residual sum-of-squares as 

$$
\operatorname{RSS} (\beta) = \left(\mathbf {y} - \mathbf {X} \beta\right) ^ {T} (\mathbf {y} - \mathbf {X} \beta).\tag{3.3}
$$

This is a quadratic function in the $p + 1$ parameters. Differentiating with respect to $\beta$ we obtain 

$$
\begin{array}{l} \frac {\partial \mathrm{RSS}}{\partial \beta} = - 2 \mathbf {X} ^ {T} (\mathbf {y} - \mathbf {X} \beta) \\ \frac {\partial^ {2} \mathrm{RSS}}{\partial \beta \partial \beta^ {T}} = 2 \mathbf {X} ^ {T} \mathbf {X}. \end{array}\tag{3.4}
$$

Assuming (for the moment) that X has full column rank, and hence $\mathbf { X } ^ { T } \mathbf { X }$ is positive definite, we set the first derivative to zero 

$$
\mathbf {X} ^ {T} (\mathbf {y} - \mathbf {X} \beta) = 0\tag{3.5}
$$

to obtain the unique solution 

$$
\hat {\beta} = (\mathbf {X} ^ {T} \mathbf {X}) ^ {- 1} \mathbf {X} ^ {T} \mathbf {y}.\tag{3.6}
$$

![image](<Images/03_Linear_Methods_for_Regression_image_002.jpg>)



FIGURE 3.2. The N-dimensional geometry of least squares regression with two predictors. The outcome vector y is orthogonally projected onto the hyperplane spanned by the input vectors $\mathbf { x } _ { 1 }$ and $\mathbf { x } _ { 2 }$ . The projection $\hat { \mathbf { y } }$ represents the vector of the least squares predictions


The predicted values at an input vector $x _ { 0 }$ are given by ${ \hat { f } } ( x _ { 0 } ) = ( 1 : x _ { 0 } ) ^ { T } { \hat { \beta } } ;$ the fitted values at the training inputs are 

$$
\hat {\mathbf {y}} = \mathbf {X} \hat {\boldsymbol {\beta}} = \mathbf {X} (\mathbf {X} ^ {T} \mathbf {X}) ^ {- 1} \mathbf {X} ^ {T} \mathbf {y},\tag{3.7}
$$

where ${ \hat { y } } _ { i } = { \hat { f } } ( x _ { i } )$ . The matrix $\mathbf { H } = \mathbf { X } ( \mathbf { X } ^ { T } \mathbf { X } ) ^ { - 1 } \mathbf { X } ^ { T }$ appearing in equation (3.7) is sometimes called the “hat” matrix because it puts the hat on $\mathbf { y } .$ 

Figure 3.2 shows a different geometrical representation of the least squares estimate, this time in $\mathbb { R } ^ { N }$ . We denote the column vectors of X by $\mathbf { x } _ { 0 } , \mathbf { x } _ { 1 } , \ldots , \mathbf { x } _ { p } ,$ 2 with $\mathbf { x } _ { 0 } \equiv 1$ . For much of what follows, this first column is treated like any other. These vectors span a subspace of $\mathbb { R } ^ { N }$ , also referred to as the column space of X. We minimize RSS $( \beta ) = \| \mathbf { y } - \mathbf { X } \beta \| ^ { 2 }$ by choosing $\hat { \beta }$ so that the residual vector $\mathbf y - \hat { \mathbf y }$ is orthogonal to this subspace. This orthogonality is expressed in (3.5), and the resulting estimate $\hat { \mathbf { y } }$ is hence the orthogonal projection of y onto this subspace. The hat matrix H computes the orthogonal projection, and hence it is also known as a projection matrix. 

It might happen that the columns of X are not linearly independent, so that X is not of full rank. This would occur, for example, if two of the inputs were perfectly correlated, $( \mathrm { e . g . , \ x _ { 2 } = 3 x _ { 1 } ) }$ . Then $\mathbf { X } ^ { T } \mathbf { X }$ is singular and the least squares coefficients $\hat { \beta }$ are not uniquely defined. However, the fitted values $\hat { \mathbf { y } } = \mathbf { X } { \hat { \boldsymbol { \beta } } } $ are still the projection of y onto the column space of $\mathbf { X } ;$ ; there is just more than one way to express that projection in terms of the column vectors of X. The non-full-rank case occurs most often when one or more qualitative inputs are coded in a redundant fashion. There is usually a natural way to resolve the non-unique representation, by recoding and/or dropping redundant columns in $\mathbf { X }$ . Most regression software packages detect these redundancies and automatically implement some strategy for removing them. Rank deficiencies can also occur in signal and image analysis, where the number of inputs $p$ can exceed the number of training cases N. In this case, the features are typically reduced by filtering or else the fitting is controlled by regularization (Section 5.2.3 and Chapter 18). 

Up to now we have made minimal assumptions about the true distribution of the data. In order to pin down the sampling properties of ${ \hat { \boldsymbol { \beta } } } .$ we now assume that the observations $y _ { i }$ are uncorrelated and have constant variance $\sigma ^ { 2 }$ , and that the $x _ { i }$ are fixed (non random). The variance–covariance matrix of the least squares parameter estimates is easily derived from (3.6) and is given by 

$$
\operatorname{Var} (\hat {\beta}) = (\mathbf {X} ^ {T} \mathbf {X}) ^ {- 1} \sigma^ {2}.\tag{3.8}
$$

Typically one estimates the variance $\sigma ^ { 2 }$ by 

$$
\hat {\sigma} ^ {2} = \frac {1}{N - p - 1} \sum_ {i = 1} ^ {N} (y _ {i} - \hat {y} _ {i}) ^ {2}.
$$

The $N - p - 1$ rather than N in the denominator makes $\hat { \sigma } ^ { 2 }$ an unbiased estimate of $\sigma ^ { 2 } \colon \operatorname { E } ( \hat { \sigma } ^ { 2 } ) = \sigma ^ { 2 }$ 

To draw inferences about the parameters and the model, additional assumptions are needed. We now assume that (3.1) is the correct model for the mean; that is, the conditional expectation of Y is linear in $X _ { 1 } , \ldots , X _ { p }$ We also assume that the deviations of $Y$ around its expectation are additive and Gaussian. Hence 

$$
\begin{array}{r c l} Y & = & \operatorname{E} (Y | X _ {1}, \ldots , X _ {p}) + \varepsilon \\ & = & \beta_ {0} + \sum_ {j = 1} ^ {p} X _ {j} \beta_ {j} + \varepsilon , \end{array}\tag{3.9}
$$

where the error $\varepsilon$ is a Gaussian random variable with expectation zero and variance $\sigma ^ { 2 }$ , written $\varepsilon \sim N ( 0 , \sigma ^ { 2 } )$ 

Under (3.9), it is easy to show that 

$$
\hat {\beta} \sim N (\beta , (\mathbf {X} ^ {T} \mathbf {X}) ^ {- 1} \sigma^ {2}).\tag{3.10}
$$

This is a multivariate normal distribution with mean vector and variance– covariance matrix as shown. Also 

$$
(N - p - 1) \hat {\sigma} ^ {2} \sim \sigma^ {2} \chi_ {N - p - 1} ^ {2},\tag{3.11}
$$

a chi-squared distribution with $N - p - 1$ degrees of freedom. In addition $\hat { \beta }$ and $\hat { \sigma } ^ { 2 }$ are statistically independent. We use these distributional properties to form tests of hypothesis and confidence intervals for the parameters $\beta _ { j }$ 

![image](<Images/03_Linear_Methods_for_Regression_image_003.jpg>)



FIGURE 3.3. The tail probabilities $\operatorname* { P r } ( | Z | > z )$ for three distributions, $t _ { 3 0 }$ , t<sub>100</sub> and standard normal. Shown are the appropriate quantiles for testing significance at the $p = 0 . 0 5$ and 0.01 levels. The difference between t and the standard normal becomes negligible for N bigger than about 100.


To test the hypothesis that a particular coefficient $\beta _ { j } = 0$ , we form the standardized coefficient or Z-score 

$$
z _ {j} = \frac {\hat {\beta} _ {j}}{\hat {\sigma} \sqrt {v _ {j}}},\tag{3.12}
$$

where $v _ { j }$ is the jth diagonal element of $( \mathbf { X } ^ { T } \mathbf { X } ) ^ { - 1 }$ . Under the null hypothesis that $\beta _ { j } = 0 , z _ { j }$ is distributed as $t _ { N - p - 1 }$ (a t distribution with $N - p - 1$ degrees of freedom), and hence a large (absolute) value of $z _ { j }$ will lead to rejection of this null hypothesis. If $\hat { \sigma }$ is replaced by a known value $\sigma ,$ , then $z _ { j }$ would have a standard normal distribution. The difference between the tail quantiles of a t-distribution and a standard normal become negligible as the sample size increases, and so we typically use the normal quantiles (see Figure 3.3). 

Often we need to test for the significance of groups of coefficients simultaneously. For example, to test if a categorical variable with k levels can be excluded from a model, we need to test whether the coefficients of the dummy variables used to represent the levels can all be set to zero. Here we use the F statistic, 

$$
F = \frac {(\mathrm{RSS} _ {0} - \mathrm{RSS} _ {1}) / (p _ {1} - p _ {0})}{\mathrm{RSS} _ {1} / (N - p _ {1} - 1)},\tag{3.13}
$$

where $\mathrm { R S S _ { 1 } }$ is the residual sum-of-squares for the least squares fit of the bigger model with $p _ { 1 } + 1$ parameters, and ${ \mathrm { R S S } } _ { 0 }$ the same for the nested smaller model with $p _ { 0 } + 1$ parameters, having $p _ { 1 } - p _ { 0 }$ parameters constrained to be zero. The F statistic measures the change in residual sum-of-squares per additional parameter in the bigger model, and it is normalized by an estimate of $\sigma ^ { 2 }$ . Under the Gaussian assumptions, and the null hypothesis that the smaller model is correct, the F statistic will have a $F _ { p _ { 1 } - p _ { 0 } , N - p _ { 1 } - 1 }$ distribution. It can be shown (Exercise 3.1) that the $z _ { j }$ in (3.12) are equivalent to the $F$ statistic for dropping the single coefficient $\beta _ { j }$ from the model. For large N, the quantiles of $F _ { p _ { 1 } - p _ { 0 } , N - p _ { 1 } - 1 }$ approach those of $\chi _ { p _ { 1 } - p _ { 0 } } ^ { 2 } / ( p _ { 1 } - p _ { 0 } )$ 

Similarly, we can isolate $\beta _ { j }$ in (3.10) to obtain a $1 - 2 \alpha$ confidence interval for $\beta _ { j }$ : 

$$
(\hat {\beta} _ {j} - z ^ {(1 - \alpha)} v _ {j} ^ {\frac {1}{2}} \hat {\sigma}, \hat {\beta} _ {j} + z ^ {(1 - \alpha)} v _ {j} ^ {\frac {1}{2}} \hat {\sigma}).\tag{3.14}
$$

Here $z ^ { ( 1 - \alpha ) }$ is the $1 - \alpha$ percentile of the normal distribution: 

$$
\begin{array}{r c l} z ^ {(1 - 0. 0 2 5)} & = & 1. 9 6, \\ z ^ {(1 -. 0 5)} & = & 1. 6 4 5, \text {etc.} \end{array}
$$

Hence the standard practice of reporting ${ \hat { \beta } } \pm 2 \cdot \sec ( { \hat { \beta } } )$ amounts to an approximate 95% confidence interval. Even if the Gaussian error assumption does not hold, this interval will be approximately correct, with its coverage approaching $1 - 2 \alpha$ as the sample size $N \to \infty$ 

In a similar fashion we can obtain an approximate confidence set for the entire parameter vector $\beta _ { i }$ namely 

$$
C _ {\beta} = \{\beta | (\hat {\beta} - \beta) ^ {T} \mathbf {X} ^ {T} \mathbf {X} (\hat {\beta} - \beta) \leq \hat {\sigma} ^ {2} \chi_ {p + 1} ^ {(1 - \alpha)} \},\tag{3.15}
$$

where $\chi _ { \ell } ^ { 2 ^ { \left( 1 - \alpha \right) } }$ is the $1 - \alpha$ percentile of the chi-squared distribution on ℓ degrees of freedom: for example, $\chi _ { 5 } ^ { 2 ^ { ( 1 - 0 . 0 5 ) } } = 1 1 . 1 , \chi _ { 5 } ^ { 2 ^ { ( 1 - 0 . 1 ) } } = 9 . 2$ . This confidence set for β generates a corresponding confidence set for the true function $f ( x ) = x ^ { T } \beta$ , namely $\{ x ^ { T } \beta | \beta \in C _ { \beta } \}$ (Exercise 3.2; see also Figure 5.4 in Section 5.2.2 for examples of confidence bands for functions). 

## 3.2.1 Example: Prostate Cancer

The data for this example come from a study by Stamey et al. (1989). They examined the correlation between the level of prostate-specific antigen and a number of clinical measures in men who were about to receive a radical prostatectomy. The variables are log cancer volume (lcavol), log prostate weight (lweight), age, log of the amount of benign prostatic hyperplasia (lbph), seminal vesicle invasion (svi), log of capsular penetration (lcp), Gleason score (gleason), and percent of Gleason scores 4 or 5 (pgg45). The correlation matrix of the predictors given in Table 3.1 shows many strong correlations. Figure 1.1 (page 3) of Chapter 1 is a scatterplot matrix showing every pairwise plot between the variables. We see that svi is a binary variable, and gleason is an ordered categorical variable. We see, for example, that both lcavol and lcp show a strong relationship with the response lpsa, and with each other. We need to fit the effects jointly to untangle the relationships between the predictors and the response. 


TABLE 3.1. Correlations of predictors in the prostate cancer data.


<table><tr><td></td><td>lcavol</td><td>lweight</td><td>age</td><td>lbph</td><td>svi</td><td>lcp</td><td>gleason</td></tr><tr><td>lweight</td><td>0.300</td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>age</td><td>0.286</td><td>0.317</td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>lbph</td><td>0.063</td><td>0.437</td><td>0.287</td><td></td><td></td><td></td><td></td></tr><tr><td>svi</td><td>0.593</td><td>0.181</td><td>0.129</td><td>-0.139</td><td></td><td></td><td></td></tr><tr><td>lcp</td><td>0.692</td><td>0.157</td><td>0.173</td><td>-0.089</td><td>0.671</td><td></td><td></td></tr><tr><td>gleason</td><td>0.426</td><td>0.024</td><td>0.366</td><td>0.033</td><td>0.307</td><td>0.476</td><td></td></tr><tr><td>pgg45</td><td>0.483</td><td>0.074</td><td>0.276</td><td>-0.030</td><td>0.481</td><td>0.663</td><td>0.757</td></tr></table>


TABLE 3.2. Linear model fit to the prostate cancer data. The Z score is the coefficient divided by its standard error (3.12). Roughly a Z score larger than two in absolute value is significantly nonzero at the $p = 0 . 0 5$ level.


<table><tr><td>Term</td><td>Coefficient</td><td>Std. Error</td><td>Z Score</td></tr><tr><td>Intercept</td><td>2.46</td><td>0.09</td><td>27.60</td></tr><tr><td>lcavol</td><td>0.68</td><td>0.13</td><td>5.37</td></tr><tr><td>lweight</td><td>0.26</td><td>0.10</td><td>2.75</td></tr><tr><td>age</td><td>-0.14</td><td>0.10</td><td>-1.40</td></tr><tr><td>lbph</td><td>0.21</td><td>0.10</td><td>2.06</td></tr><tr><td>svi</td><td>0.31</td><td>0.12</td><td>2.47</td></tr><tr><td>lcp</td><td>-0.29</td><td>0.15</td><td>-1.87</td></tr><tr><td>gleason</td><td>-0.02</td><td>0.15</td><td>-0.15</td></tr><tr><td>pgg45</td><td>0.27</td><td>0.15</td><td>1.74</td></tr></table>

We fit a linear model to the log of prostate-specific antigen, lpsa, after first standardizing the predictors to have unit variance. We randomly split the dataset into a training set of size 67 and a test set of size 30. We applied least squares estimation to the training set, producing the estimates, standard errors and Z-scores shown in Table 3.2. The Z-scores are defined in (3.12), and measure the effect of dropping that variable from the model. A Z-score greater than 2 in absolute value is approximately significant at the 5% level. (For our example, we have nine parameters, and the 0.025 tail quantiles of the $t _ { 6 7 - 9 }$ distribution are 2.002!) The predictor lcavol shows the strongest effect, with lweight and svi also strong. Notice that lcp is not significant, once lcavol is in the model (when used in a model without lcavol, lcp is strongly significant). We can also test for the exclusion of a number of terms at once, using the F-statistic (3.13). For example, we consider dropping all the non-significant terms in Table 3.2, namely age, 

lcp, $\mathtt { g l }$ eason, and pgg45. We get 

$$
F = \frac {(3 2 . 8 1 - 2 9 . 4 3) / (9 - 5)}{2 9 . 4 3 / (6 7 - 9)} = 1. 6 7,\tag{3.16}
$$

which has a p-value of 0.17 $( \mathrm { P r } ( F _ { 4 , 5 8 } > 1 . 6 7 ) = 0 . 1 7 )$ , and hence is not significant. 

The mean prediction error on the test data is 0.521. In contrast, prediction using the mean training value of lpsa has a test error of 1.057, which is called the “base error rate.” Hence the linear model reduces the base error rate by about 50%. We will return to this example later to compare various selection and shrinkage methods. 

## 3.2.2 The Gauss–Markov Theorem

One of the most famous results in statistics asserts that the least squares estimates of the parameters $\beta$ have the smallest variance among all linear unbiased estimates. We will make this precise here, and also make clear that the restriction to unbiased estimates is not necessarily a wise one. This observation will lead us to consider biased estimates such as ridge regression later in the chapter. We focus on estimation of any linear combination of the parameters $\theta = a ^ { T } \beta ;$ ; for example, predictions $f ( x _ { 0 } ) = x _ { 0 } ^ { T } \beta$ are of this form. The least squares estimate of $a ^ { T } \beta$ is 

$$
\hat {\theta} = a ^ {T} \hat {\beta} = a ^ {T} (\mathbf {X} ^ {T} \mathbf {X}) ^ {- 1} \mathbf {X} ^ {T} \mathbf {y}.\tag{3.17}
$$

Considering X to be fixed, this is a linear function $\mathbf { c } _ { 0 } ^ { T } \mathbf { y }$ of the response vector $\mathbf { y }$ . If we assume that the linear model is correct, $a ^ { T } { \hat { \boldsymbol { \beta } } }$ is unbiased since 

$$
\begin{array}{r c l} \mathrm{E} (a ^ {T} \hat {\beta}) & = & \mathrm{E} (a ^ {T} (\mathbf {X} ^ {T} \mathbf {X}) ^ {- 1} \mathbf {X} ^ {T} \mathbf {y}) \\ & = & a ^ {T} (\mathbf {X} ^ {T} \mathbf {X}) ^ {- 1} \mathbf {X} ^ {T} \mathbf {X} \beta \\ & = & a ^ {T} \beta . \end{array}\tag{3.18}
$$

The Gauss–Markov theorem states that if we have any other linear estimator $\widetilde { \boldsymbol { \theta } } = \mathbf { c } ^ { T } \mathbf { y }$ that is unbiased for $a ^ { T } \beta$ , that is, $\begin{array} { r } { \operatorname { E } ( \mathbf { c } ^ { T } \mathbf { y } ) = a ^ { T } \boldsymbol { \beta } } \end{array}$ , then 

$$
\operatorname{Var} (a ^ {T} \hat {\beta}) \leq \operatorname{Var} (\mathbf {c} ^ {T} \mathbf {y}).\tag{3.19}
$$

The proof (Exercise 3.3) uses the triangle inequality. For simplicity we have stated the result in terms of estimation of a single parameter $a ^ { T } \beta$ , but with a few more definitions one can state it in terms of the entire parameter vector $\beta$ (Exercise 3.3). 

Consider the mean squared error of an estimator $\tilde { \theta }$ in estimating $\theta \colon$ 

$$
\begin{array}{r c l} \mathrm{MSE} (\tilde {\theta}) & = & \mathrm{E} (\tilde {\theta} - \theta) ^ {2} \\ & = & \mathrm{Var} (\tilde {\theta}) + [ \mathrm{E} (\tilde {\theta}) - \theta ] ^ {2}. \end{array}\tag{3.20}
$$

## 3. Linear Methods for Regression

The first term is the variance, while the second term is the squared bias. The Gauss-Markov theorem implies that the least squares estimator has the smallest mean squared error of all linear estimators with no bias. However, there may well exist a biased estimator with smaller mean squared error. Such an estimator would trade a little bias for a larger reduction in variance. Biased estimates are commonly used. Any method that shrinks or sets to zero some of the least squares coefficients may result in a biased estimate. We discuss many examples, including variable subset selection and ridge regression, later in this chapter. From a more pragmatic point of view, most models are distortions of the truth, and hence are biased; picking the right model amounts to creating the right balance between bias and variance. We go into these issues in more detail in Chapter 7. 

Mean squared error is intimately related to prediction accuracy, as discussed in Chapter 2. Consider the prediction of the new response at input $x _ { 0 }$ 2 

$$
Y _ {0} = f (x _ {0}) + \varepsilon_ {0}.\tag{3.21}
$$

Then the expected prediction error of an estimate $\tilde { f } ( x _ { 0 } ) = x _ { 0 } ^ { T } \tilde { \beta }$ is 

$$
\begin{array}{r c l} \mathrm{E} (Y _ {0} - \tilde {f} (x _ {0})) ^ {2} & = & \sigma^ {2} + \mathrm{E} (x _ {0} ^ {T} \tilde {\beta} - f (x _ {0})) ^ {2} \\ & = & \sigma^ {2} + \mathrm{MSE} (\tilde {f} (x _ {0})). \end{array}\tag{3.22}
$$

Therefore, expected prediction error and mean squared error differ only by the constant $\sigma ^ { 2 }$ , representing the variance of the new observation $y _ { 0 }$ 

## 3.2.3 Multiple Regression from Simple Univariate Regression

The linear model (3.1) with $p > 1$ inputs is called the multiple linear regression model. The least squares estimates (3.6) for this model are best understood in terms of the estimates for the univariate $( p \ = \ 1 )$ linear model, as we indicate in this section. 

Suppose first that we have a univariate model with no intercept, that is, 

$$
Y = X \beta + \varepsilon .\tag{3.23}
$$

The least squares estimate and residuals are 

$$
\begin{array}{l} \hat {\beta} = \frac {\sum_ {1} ^ {N} x _ {i} y _ {i}}{\sum_ {1} ^ {N} x _ {i} ^ {2}}, \\ r _ {i} = y _ {i} - x _ {i} \hat {\beta}. \end{array}\tag{3.24}
$$

In convenient vector notation, we let $\mathbf { y } = ( y _ { 1 } , \ldots , y _ { N } ) ^ { T } , \mathbf { x } = ( x _ { 1 } , \ldots , x _ { N } ) ^ { T }$ and define 

$$
\begin{array}{r c l} \langle \mathbf {x}, \mathbf {y} \rangle & = & \sum_ {i = 1} ^ {N} x _ {i} y _ {i}, \\ & = & \mathbf {x} ^ {T} \mathbf {y}, \end{array}\tag{3.25}
$$

the inner product between x and $\mathbf { y } ^ { 1 }$ . Then we can write 

$$
\hat {\beta} = \frac {\langle \mathbf {x} , \mathbf {y} \rangle}{\langle \mathbf {x} , \mathbf {x} \rangle},\tag{3.26}
$$

$$
\mathbf {r} = \mathbf {y} - \mathbf {x} \hat {\boldsymbol {\beta}}.
$$

As we will see, this simple univariate regression provides the building block for multiple linear regression. Suppose next that the inputs $\mathbf { x } _ { 1 } , \mathbf { x } _ { 2 } , \ldots , \mathbf { x } _ { p }$ (the columns of the data matrix X) are orthogonal; that is $\left. \mathbf { x } _ { j } , \mathbf { x } _ { k } \right. = 0$ for all $j \neq k$ . Then it is easy to check that the multiple least squares estimates $\dot { \beta } _ { j }$ are equal to $\langle \mathbf { x } _ { j } , \mathbf { y } \rangle / \langle \mathbf { x } _ { j } , \mathbf { x } _ { j } \rangle$ —the univariate estimates. In other words, when the inputs are orthogonal, they have no effect on each other’s parameter estimates in the model. 

Orthogonal inputs occur most often with balanced, designed experiments (where orthogonality is enforced), but almost never with observational data. Hence we will have to orthogonalize them in order to carry this idea further. Suppose next that we have an intercept and a single input x. Then the least squares coefficient of x has the form 

$$
\hat {\beta} _ {1} = \frac {\langle \mathbf {x} - \bar {x} \mathbf {1} , \mathbf {y} \rangle}{\langle \mathbf {x} - \bar {x} \mathbf {1} , \mathbf {x} - \bar {x} \mathbf {1} \rangle},\tag{3.27}
$$

where $\bar { x } = \textstyle \sum _ { i } x _ { i } / N$ , and ${ \bf 1 } = { \bf x } _ { 0 }$ , the vector of N ones. We can view the estimate $( 3 . 2 7 )$ as the result of two applications of the simple regression (3.26). The steps are: 

1. regress x on 1 to produce the residual $\mathbf { z } = \mathbf { x } - \bar { x } \mathbf { 1 }$ ; 

2. regress y on the residual z to give the coefficient $\hat { \beta } _ { 1 }$ . 

In this procedure, “regress b on $\mathbf { a } ^ { \dag }$ means a simple univariate regression of b on a with no intercept, producing coefficient $\hat { \gamma } = \langle \mathbf { a } , \mathbf { b } \rangle / \langle \mathbf { a } , \mathbf { a } \rangle$ and residual vector b $- \hat { \gamma } \mathbf { a }$ . We say that b is adjusted for a, or is “orthogonalized” with respect to a. 

Step 1 orthogonalizes x with respect to $\mathbf { x } _ { 0 } = \mathbf { 1 }$ . Step 2 is just a simple univariate regression, using the orthogonal predictors 1 and z. Figure 3.4 shows this process for two general inputs $\mathbf { x } _ { 1 }$ and $\mathbf { x } _ { 2 }$ . The orthogonalization does not change the subspace spanned by $\mathbf { x } _ { 1 }$ and $\mathbf { x } _ { 2 }$ , it simply produces an orthogonal basis for representing it. 

This recipe generalizes to the case of p inputs, as shown in Algorithm 3.1. Note that the inputs $\mathbf { z } _ { 0 } , \ldots , \mathbf { z } _ { j - 1 }$ in step 2 are orthogonal, hence the simple regression coefficients computed there are in fact also the multiple regression coefficients. 

![image](<Images/03_Linear_Methods_for_Regression_image_004.jpg>)



FIGURE 3.4. Least squares regression by orthogonalization of the inputs. The vector $\mathbf { x } _ { 2 }$ is regressed on the vector $\mathbf { x } _ { 1 }$ , leaving the residual vector z. The regression of y on z gives the multiple regression coefficient of $\mathbf { x } _ { 2 }$ . Adding together the projections of y on each of $\mathbf { x } _ { 1 }$ and z gives the least squares $f i t { \hat { \mathbf { y } } }$


Algorithm 3.1 Regression by Successive Orthogonalization.

1. Initialize $z_{0} = x_{0} = 1$ .
2. For $j = 1, 2, \ldots, p$ Regress $x_{j}$ on $z_{0}, z_{1}, \ldots, z_{j-1}$ to produce coefficients $\hat{\gamma}_{\ell j} = \langle z_{\ell}, x_{j} \rangle / \langle z_{\ell}, z_{\ell} \rangle$ , $\ell = 0, \ldots, j - 1$ and residual vector $z_{j} = x_{j} - \sum_{k=0}^{j-1} \hat{\gamma}_{kj} z_{k}$ .
3. Regress y on the residual $z_{p}$ to give the estimate $\hat{\beta}_{p}$ . 

The result of this algorithm is 

$$
\hat {\beta} _ {p} = \frac {\langle \mathbf {z} _ {p} , \mathbf {y} \rangle}{\langle \mathbf {z} _ {p} , \mathbf {z} _ {p} \rangle}.\tag{3.28}
$$

Re-arranging the residual in step 2, we can see that each of the $\mathbf { x } _ { j }$ is a linear combination of the $\mathbf { z } _ { k } , \ k \leq j$ . Since the $\mathbf { z } _ { j }$ are all orthogonal, they form a basis for the column space of X, and hence the least squares projection onto this subspace is $\hat { \mathbf { y } }$ . Since $\mathbf { z } _ { p }$ alone involves $\mathbf { x } _ { p }$ (with coefficient 1), we see that the coefficient (3.28) is indeed the multiple regression coefficient of y on $\mathbf { x } _ { p }$ . This key result exposes the effect of correlated inputs in multiple regression. Note also that by rearranging the $\mathbf { x } _ { j }$ , any one of them could be in the last position, and a similar results holds. Hence stated more generally, we have shown that the jth multiple regression coefficient is the univariate regression coefficient of y on $\mathbf { x } _ { j \cdot 0 1 2 \ldots ( j - 1 ) ( j + 1 ) \ldots , p }$ , the residual after regressing $\mathbf { x } _ { j }$ on $\mathbf { x } _ { 0 } , \mathbf { x } _ { 1 } , \ldots , \mathbf { x } _ { j - 1 } , \mathbf { x } _ { j + 1 } , \ldots , \mathbf { x } _ { p } .$ 

The multiple regression coefficient $\hat { \beta } _ { j }$ represents the additional contribution of $\mathbf { \dot { x } } _ { j }$ on y, after x<sub>j</sub> has been adjusted for $\mathbf { x } _ { 0 } , \mathbf { x } _ { 1 } , \ldots , \mathbf { x } _ { j - 1 }$ 2 x<sub>j+1</sub>, . . . , x<sub>p</sub>. 

If $\mathbf { x } _ { p }$ is highly correlated with some of the other $\mathbf { x } _ { k } { } ^ { \prime } \mathbf { s }$ , the residual vector $\mathbf { z } _ { p }$ will be close to zero, and from (3.28) the coefficient $\hat { \beta } _ { p }$ will be very unstable. This will be true for all the variables in the correlated set. In such situations, we might have all the Z-scores (as in Table 3.2) be small— any one of the set can be deleted—yet we cannot delete them all. From (3.28) we also obtain an alternate formula for the variance estimates (3.8), 

$$
\mathrm{Var} (\hat {\beta} _ {p}) = \frac {\sigma^ {2}}{\langle \mathbf {z} _ {p} , \mathbf {z} _ {p} \rangle} = \frac {\sigma^ {2}}{\| \mathbf {z} _ {p} \| ^ {2}}.\tag{3.29}
$$

In other words, the precision with which we can estimate $\hat { \beta } _ { p }$ depends on the length of the residual vector $\mathbf { z } _ { p } ;$ ; this represents how much of $\mathbf { x } _ { p }$ is unexplained by the other $\mathbf { x } _ { k } { } ^ { \prime } \mathbf { s }$ 

Algorithm 3.1 is known as the Gram–Schmidt procedure for multiple regression, and is also a useful numerical strategy for computing the estimates. We can obtain from it not just $\hat { \beta } _ { p }$ , but also the entire multiple least squares fit, as shown in Exercise 3.4. 

We can represent step 2 of Algorithm 3.1 in matrix form: 

$$
\mathbf {X} = \mathbf {Z} \boldsymbol {\Gamma},\tag{3.30}
$$

where Z has as columns the $\mathbf { z } _ { j }$ (in order), and Γ is the upper triangular matrix with entries $\hat { \gamma } _ { k j }$ . Introducing the diagonal matrix D with jth diagonal entry $D _ { j j } = \| \mathbf { z } _ { j } \|$ , we get 

$$
\begin{array}{r c l} \mathbf {X} & = & \mathbf {Z D} ^ {- 1} \mathbf {D} \boldsymbol {\Gamma} \\ & = & \mathbf {Q R}, \end{array}\tag{3.31}
$$

the so-called QR decomposition of X. Here Q is an $N \times ( p + 1 )$ ) orthogonal matrix, $\mathbf { Q } ^ { T } \mathbf { Q } = \mathbf { I }$ , and R is a $( p + 1 ) \times ( p + 1 )$ upper triangular matrix. 

The QR decomposition represents a convenient orthogonal basis for the column space of X. It is easy to see, for example, that the least squares solution is given by 

$$
\hat {\boldsymbol {\beta}} = \mathbf {R} ^ {- 1} \mathbf {Q} ^ {T} \mathbf {y},\tag{3.32}
$$

$$
{\hat {\mathbf {y}}} = {\mathbf {Q} \mathbf {Q} ^ {T} \mathbf {y}.}\tag{3.33}
$$

Equation (3.32) is easy to solve because R is upper triangular (Exercise 3.4). 

## 3.2.4 Multiple Outputs

Suppose we have multiple outputs $Y _ { 1 } , Y _ { 2 } , \dots , Y _ { K }$ that we wish to predict from our inputs $X _ { 0 } , X _ { 1 } , X _ { 2 } , \ldots , X _ { p } ,$ . We assume a linear model for each output 

$$
Y _ {k} = \beta_ {0 k} + \sum_ {j = 1} ^ {p} X _ {j} \beta_ {j k} + \varepsilon_ {k}\tag{3.34}
$$

$$
= f _ {k} (X) + \varepsilon_ {k}.\tag{3.35}
$$

With N training cases we can write the model in matrix notation 

$$
\mathbf {Y} = \mathbf {X B} + \mathbf {E}.\tag{3.36}
$$

Here Y is the $N \times K$ response matrix, with ik entry $y _ { i k } , \mathbf { X }$ is the $N \times ( p + 1 )$ input matrix, B is the $( p + 1 ) \times K$ matrix of parameters and E is the $N \times K$ matrix of errors. A straightforward generalization of the univariate loss function (3.2) is 

$$
\operatorname{RSS} (\mathbf {B}) = \sum_ {k = 1} ^ {K} \sum_ {i = 1} ^ {N} (y _ {i k} - f _ {k} (x _ {i})) ^ {2}\tag{3.37}
$$

$$
= \operatorname{tr} [ (\mathbf {Y} - \mathbf {X B}) ^ {T} (\mathbf {Y} - \mathbf {X B}) ].\tag{3.38}
$$

The least squares estimates have exactly the same form as before 

$$
\hat {\mathbf {B}} = (\mathbf {X} ^ {T} \mathbf {X}) ^ {- 1} \mathbf {X} ^ {T} \mathbf {Y}.\tag{3.39}
$$

Hence the coefficients for the kth outcome are just the least squares estimates in the regression of $\mathbf { y } _ { k }$ on $\mathbf { x } _ { 0 } , \mathbf { x } _ { 1 } , \ldots , \mathbf { x } _ { p }$ . Multiple outputs do not affect one another’s least squares estimates. 

If the errors $\boldsymbol { \varepsilon } = \left( \varepsilon _ { 1 } , \dots , \varepsilon _ { K } \right)$ in (3.34) are correlated, then it might seem appropriate to modify (3.37) in favor of a multivariate version. Specifically, suppose $\mathrm { C o v } ( \varepsilon ) = \Sigma$ , then the multivariate weighted criterion 

$$
\operatorname{RSS} (\mathbf {B}; \boldsymbol {\Sigma}) = \sum_ {i = 1} ^ {N} (y _ {i} - f (x _ {i})) ^ {T} \boldsymbol {\Sigma} ^ {- 1} (y _ {i} - f (x _ {i}))\tag{3.40}
$$

arises naturally from multivariate Gaussian theory. Here $f ( x )$ is the vector function $( f _ { 1 } ( x ) , \ldots , f _ { K } ( x ) ) ^ { T }$ , and $y _ { i }$ the vector of K responses for observation i. However, it can be shown that again the solution is given by (3.39); K separate regressions that ignore the correlations (Exercise 3.11). If the $\Sigma _ { i }$ vary among observations, then this is no longer the case, and the solution for B no longer decouples. 

In Section 3.7 we pursue the multiple outcome problem, and consider situations where it does pay to combine the regressions. 

## 3.3 Subset Selection

There are two reasons why we are often not satisfied with the least squares estimates (3.6). 

The first is prediction accuracy: the least squares estimates often have low bias but large variance. Prediction accuracy can sometimes be improved by shrinking or setting some coefficients to zero. By doing so we sacrifice a little bit of bias to reduce the variance of the predicted values, and hence may improve the overall prediction accuracy. 

The second reason is interpretation. With a large number of predictors, we often would like to determine a smaller subset that exhibit the strongest effects. In order to get the “big picture,” we are willing to sacrifice some of the small details. 

In this section we describe a number of approaches to variable subset selection with linear regression. In later sections we discuss shrinkage and hybrid approaches for controlling variance, as well as other dimension-reduction strategies. These all fall under the general heading model selection. Model selection is not restricted to linear models; Chapter 7 covers this topic in some detail. 

With subset selection we retain only a subset of the variables, and eliminate the rest from the model. Least squares regression is used to estimate the coefficients of the inputs that are retained. There are a number of different strategies for choosing the subset. 

## 3.3.1 Best-Subset Selection

Best subset regression finds for each $k \in \{ 0 , 1 , 2 , \ldots , p \}$ the subset of size k that gives smallest residual sum of squares (3.2). An efficient algorithm— the leaps and bounds procedure (Furnival and Wilson, 1974)—makes this feasible for p as large as 30 or 40. Figure 3.5 shows all the subset models for the prostate cancer example. The lower boundary represents the models that are eligible for selection by the best-subsets approach. Note that the best subset of size 2, for example, need not include the variable that was in the best subset of size 1 (for this example all the subsets are nested). The best-subset curve (red lower boundary in Figure 3.5) is necessarily decreasing, so cannot be used to select the subset size k. The question of how to choose k involves the tradeoff between bias and variance, along with the more subjective desire for parsimony. There are a number of criteria that one may use; typically we choose the smallest model that minimizes an estimate of the expected prediction error. 

Many of the other approaches that we discuss in this chapter are similar, in that they use the training data to produce a sequence of models varying in complexity and indexed by a single parameter. In the next section we use cross-validation to estimate prediction error and select k; the AIC criterion is a popular alternative. We defer more detailed discussion of these and other approaches to Chapter 7. 

![image](<Images/03_Linear_Methods_for_Regression_image_005.jpg>)



FIGURE 3.5. All possible subset models for the prostate cancer example. At each subset size is shown the residual sum-of-squares for each model of that size.


## 3.3.2 Forward- and Backward-Stepwise Selection

Rather than search through all possible subsets (which becomes infeasible for p much larger than 40), we can seek a good path through them. Forwardstepwise selection starts with the intercept, and then sequentially adds into the model the predictor that most improves the fit. With many candidate predictors, this might seem like a lot of computation; however, clever updating algorithms can exploit the QR decomposition for the current fit to rapidly establish the next candidate (Exercise 3.9). Like best-subset regression, forward stepwise produces a sequence of models indexed by k, the subset size, which must be determined. 

Forward-stepwise selection is a greedy algorithm, producing a nested sequence of models. In this sense it might seem sub-optimal compared to best-subset selection. However, there are several reasons why it might be preferred: 

Computational; for large p we cannot compute the best subset sequence, but we can always compute the forward stepwise sequence (even when $p \gg N )$ 

Statistical; a price is paid in variance for selecting the best subset of each size; forward stepwise is a more constrained search, and will have lower variance, but perhaps more bias. 

![image](<Images/03_Linear_Methods_for_Regression_image_006.jpg>)



FIGURE 3.6. Comparison offour subset-selection techniques on a simulated linear regression problem $Y = X ^ { T } { \boldsymbol { \beta } } + \varepsilon$ . There are $N = 3 0 0$ observations on $p = 3 1$ standard Gaussian variables, with pairwise correlations all equal to 0.85. For 10 of the variables, the coefficients are drawn at random from a $N ( 0 , 0 . 4 )$ distribution; the rest are zero. The noise $\varepsilon \sim N ( 0 , 6 . 2 5 )$ ), resulting in a signal-to-noise ratio of 0.64. Results are averaged over 50 simulations. Shown is the mean-squared error of the estimated coefficient ${ \hat { \beta } } ( k )$ at each step from the true $\beta$


Backward-stepwise selection starts with the full model, and sequentially deletes the predictor that has the least impact on the fit. The candidate for dropping is the variable with the smallest Z-score (Exercise 3.10). Backward selection can only be used when $N > p ,$ while forward stepwise can always be used. 

Figure 3.6 shows the results of a small simulation study to compare best-subset regression with the simpler alternatives forward and backward selection. Their performance is very similar, as is often the case. Included in the figure is forward stagewise regression (next section), which takes longer to reach minimum error. 

On the prostate cancer example, best-subset, forward and backward selection all gave exactly the same sequence of terms. 

Some software packages implement hybrid stepwise-selection strategies that consider both forward and backward moves at each step, and select the “best” of the two. For example in the R package the step function uses the AIC criterion for weighing the choices, which takes proper account of the number of parameters fit; at each step an add or drop will be performed that minimizes the AIC score. 

Other more traditional packages base the selection on F-statistics, adding “significant” terms, and dropping “non-significant” terms. These are out of fashion, since they do not take proper account of the multiple testing issues. It is also tempting after a model search to print out a summary of the chosen model, such as in Table 3.2; however, the standard errors are not valid, since they do not account for the search process. The bootstrap (Section 8.2) can be useful in such settings. 

Finally, we note that often variables come in groups (such as the dummy variables that code a multi-level categorical predictor). Smart stepwise procedures (such as step in R) will add or drop whole groups at a time, taking proper account of their degrees-of-freedom. 

## 3.3.3 Forward-Stagewise Regression

Forward-stagewise regression (FS) is even more constrained than forwardstepwise regression. It starts like forward-stepwise regression, with an intercept equal to ${ \bar { y } } .$ , and centered predictors with coefficients initially all 0. At each step the algorithm identifies the variable most correlated with the current residual. It then computes the simple linear regression coefficient of the residual on this chosen variable, and then adds it to the current coefficient for that variable. This is continued till none of the variables have correlation with the residuals—i.e. the least-squares fit when $N > p$ 

Unlike forward-stepwise regression, none of the other variables are adjusted when a term is added to the model. As a consequence, forward stagewise can take many more than p steps to reach the least squares fit, and historically has been dismissed as being inefficient. It turns out that this “slow fitting” can pay dividends in high-dimensional problems. We see in Section 3.8.1 that both forward stagewise and a variant which is slowed down even further are quite competitive, especially in very highdimensional problems. 

Forward-stagewise regression is included in Figure 3.6. In this example it takes over 1000 steps to get all the correlations below $1 0 ^ { - 4 }$ . For subset size k, we plotted the error for the last step for which there where k nonzero coefficients. Although it catches up with the best fit, it takes longer to do so. 

## 3.3.4 Prostate Cancer Data Example (Continued)

Table 3.3 shows the coefficients from a number of different selection and shrinkage methods. They are best-subset selection using an all-subsets search, ridge regression, the lasso, principal components regression and partial least squares. Each method has a complexity parameter, and this was chosen to minimize an estimate of prediction error based on tenfold cross-validation; full details are given in Section 7.10. Briefly, cross-validation works by dividing the training data randomly into ten equal parts. The learning method is fit—for a range of values of the complexity parameter—to nine-tenths of the data, and the prediction error is computed on the remaining one-tenth. This is done in turn for each one-tenth of the data, and the ten prediction error estimates are averaged. From this we obtain an estimated prediction error curve as a function of the complexity parameter. 

Note that we have already divided these data into a training set of size 67 and a test set of size 30. Cross-validation is applied to the training set, since selecting the shrinkage parameter is part of the training process. The test set is there to judge the performance of the selected model. 

The estimated prediction error curves are shown in Figure 3.7. Many of the curves are very flat over large ranges near their minimum. Included are estimated standard error bands for each estimated error rate, based on the ten error estimates computed by cross-validation. We have used the “one-standard-error” rule—we pick the most parsimonious model within one standard error of the minimum (Section 7.10, page 244). Such a rule acknowledges the fact that the tradeoff curve is estimated with error, and hence takes a conservative approach. 

Best-subset selection chose to use the two predictors lcvol and lweight. The last two lines of the table give the average prediction error (and its estimated standard error) over the test set. 

## 3.4 Shrinkage Methods

By retaining a subset of the predictors and discarding the rest, subset selection produces a model that is interpretable and has possibly lower prediction error than the full model. However, because it is a discrete process— variables are either retained or discarded—it often exhibits high variance, and so doesn’t reduce the prediction error of the full model. Shrinkage methods are more continuous, and don’t suffer as much from high variability. 

## 3.4.1 Ridge Regression

Ridge regression shrinks the regression coefficients by imposing a penalty on their size. The ridge coefficients minimize a penalized residual sum of 

![image](<Images/03_Linear_Methods_for_Regression_image_007.jpg>)



FIGURE 3.7. Estimated prediction error curves and their standard errors for the various selection and shrinkage methods. Each curve is plotted as a function of the corresponding complexity parameter for that method. The horizontal axis has been chosen so that the model complexity increases as we move from left to right. The estimates of prediction error and their standard errors were obtained by tenfold cross-validation; full details are given in Section 7.10. The least complex model within one standard error of the best is chosen, indicated by the purple vertical broken lines.



TABLE 3.3. Estimated coefficients and test error results, for different subset and shrinkage methods applied to the prostate data. The blank entries correspond to variables omitted.


<table><tr><td>Term</td><td>LS</td><td>Best Subset</td><td>Ridge</td><td>Lasso</td><td>PCR</td><td>PLS</td></tr><tr><td>Intercept</td><td>2.465</td><td>2.477</td><td>2.452</td><td>2.468</td><td>2.497</td><td>2.452</td></tr><tr><td>lcavol</td><td>0.680</td><td>0.740</td><td>0.420</td><td>0.533</td><td>0.543</td><td>0.419</td></tr><tr><td>lweight</td><td>0.263</td><td>0.316</td><td>0.238</td><td>0.169</td><td>0.289</td><td>0.344</td></tr><tr><td>age</td><td>-0.141</td><td></td><td>-0.046</td><td></td><td>-0.152</td><td>-0.026</td></tr><tr><td>lbph</td><td>0.210</td><td></td><td>0.162</td><td>0.002</td><td>0.214</td><td>0.220</td></tr><tr><td>svi</td><td>0.305</td><td></td><td>0.227</td><td>0.094</td><td>0.315</td><td>0.243</td></tr><tr><td>lcp</td><td>-0.288</td><td></td><td>0.000</td><td></td><td>-0.051</td><td>0.079</td></tr><tr><td>gleason</td><td>-0.021</td><td></td><td>0.040</td><td></td><td>0.232</td><td>0.011</td></tr><tr><td>pgg45</td><td>0.267</td><td></td><td>0.133</td><td></td><td>-0.056</td><td>0.084</td></tr><tr><td>Test Error</td><td>0.521</td><td>0.492</td><td>0.492</td><td>0.479</td><td>0.449</td><td>0.528</td></tr><tr><td>Std Error</td><td>0.179</td><td>0.143</td><td>0.165</td><td>0.164</td><td>0.105</td><td>0.152</td></tr></table>

squares, 

$$
\hat {\beta} ^ {\text { ridge }} = \underset {\beta} {\operatorname{argmin}} \biggl \{\sum_ {i = 1} ^ {N} \bigl (y _ {i} - \beta_ {0} - \sum_ {j = 1} ^ {p} x _ {i j} \beta_ {j} \bigr) ^ {2} + \lambda \sum_ {j = 1} ^ {p} \beta_ {j} ^ {2} \biggr \}.\tag{3.41}
$$

Here $\lambda \geq 0$ is a complexity parameter that controls the amount of shrinkage: the larger the value of λ, the greater the amount of shrinkage. The coefficients are shrunk toward zero (and each other). The idea of penalizing by the sum-of-squares of the parameters is also used in neural networks, where it is known as weight decay (Chapter 11). 

An equivalent way to write the ridge problem is 

$$
\begin{array}{l} \hat {\beta} ^ {\text { ridge }} = \underset {\beta} {\operatorname{argmin}} \sum_ {i = 1} ^ {N} \Big (y _ {i} - \beta_ {0} - \sum_ {j = 1} ^ {p} x _ {i j} \beta_ {j} \Big) ^ {2}, \\ \text { subject   to } \sum_ {j = 1} ^ {p} \beta_ {j} ^ {2} \leq t, \end{array}\tag{3.42}
$$

which makes explicit the size constraint on the parameters. There is a oneto-one correspondence between the parameters λ in (3.41) and t in (3.42). When there are many correlated variables in a linear regression model, their coefficients can become poorly determined and exhibit high variance. A wildly large positive coefficient on one variable can be canceled by a similarly large negative coefficient on its correlated cousin. By imposing a size constraint on the coefficients, as in (3.42), this problem is alleviated. 

The ridge solutions are not equivariant under scaling of the inputs, and so one normally standardizes the inputs before solving (3.41). In addition, notice that the intercept $\beta _ { 0 }$ has been left out of the penalty term. Penalization of the intercept would make the procedure depend on the origin chosen for $Y ;$ that is, adding a constant c to each of the targets $y _ { i }$ would not simply result in a shift of the predictions by the same amount c. It can be shown (Exercise 3.5) that the solution to (3.41) can be separated into two parts, after reparametrization using centered inputs: each $x _ { i j }$ gets replaced by $x _ { i j } - { \bar { x } } _ { j }$ . We estimate $\beta _ { 0 }$ by $\begin{array} { r } { \bar { y } = \frac { 1 } { N } \sum _ { 1 } ^ { N } y _ { i } } \end{array}$ . The remaining coefficients get estimated by a ridge regression without intercept, using the centered $\boldsymbol { x } _ { i j }$ . Henceforth we assume that this centering has been done, so that the input matrix X has $p$ (rather than $p + 1 )$ columns. 

Writing the criterion in (3.41) in matrix form, 

$$
\mathrm{RSS} (\lambda) = (\mathbf {y} - \mathbf {X} \beta) ^ {T} (\mathbf {y} - \mathbf {X} \beta) + \lambda \beta^ {T} \beta ,\tag{3.43}
$$

the ridge regression solutions are easily seen to be 

$$
\hat {\beta} ^ {\mathrm{ridge}} = (\mathbf {X} ^ {T} \mathbf {X} + \lambda \mathbf {I}) ^ {- 1} \mathbf {X} ^ {T} \mathbf {y},\tag{3.44}
$$

where I is the $p \times p$ identity matrix. Notice that with the choice of quadratic penalty $\beta ^ { T } \beta$ , the ridge regression solution is again a linear function of y. The solution adds a positive constant to the diagonal of $\mathbf { X } ^ { T } \mathbf { X }$ before inversion. This makes the problem nonsingular, even if $\mathbf { X } ^ { T } \mathbf { X }$ is not of full rank, and was the main motivation for ridge regression when it was first introduced in statistics (Hoerl and Kennard, 1970). Traditional descriptions of ridge regression start with definition (3.44). We choose to motivate it via (3.41) and (3.42), as these provide insight into how it works. 

Figure 3.8 shows the ridge coefficient estimates for the prostate cancer example, plotted as functions of df(λ), the effective degrees of freedom implied by the penalty λ (defined in (3.50) on page 68). In the case of orthonormal inputs, the ridge estimates are just a scaled version of the least squares estimates, that is, ${ \hat { \beta } } ^ { \mathrm { r i d g e } } = { \hat { \beta } } / ( 1 + \stackrel { \cdot } { \lambda } )$ 

Ridge regression can also be derived as the mean or mode of a posterior distribution, with a suitably chosen prior distribution. In detail, suppose $y _ { i } \sim N ( \beta _ { 0 } + x _ { i } ^ { T } \beta , \sigma ^ { 2 } )$ , and the parameters $\beta _ { j }$ are each distributed as $N ( 0 , \tau ^ { 2 } )$ , independently of one another. Then the (negative) log-posterior density of $\beta$ , with $\tau ^ { 2 }$ and $\sigma ^ { 2 }$ assumed known, is equal to the expression in curly braces in (3.41), with $\lambda = \sigma ^ { 2 } / \tau ^ { 2 }$ (Exercise 3.6). Thus the ridge estimate is the mode of the posterior distribution; since the distribution is Gaussian, it is also the posterior mean. 

The singular value decomposition (SVD) of the centered input matrix X gives us some additional insight into the nature of ridge regression. This decomposition is extremely useful in the analysis of many statistical methods. The SVD of the $N \times p$ matrix X has the form 

$$
\mathbf {X} = \mathbf {U D V} ^ {T}.\tag{3.45}
$$

![image](<Images/03_Linear_Methods_for_Regression_image_008.jpg>)



FIGURE 3.8. Profiles of ridge coefficients for the prostate cancer example, as the tuning parameter λ is varied. Coefficients are plotted versus df(λ), the effective degrees of freedom. A vertical line is drawn at $\mathrm { d f } \ = \ 5 . 0 $ , the value chosen by cross-validation.


Here U and V are $N \times p$ and $p \times p$ orthogonal matrices, with the columns of U spanning the column space of X, and the columns of V spanning the row space. D is a $p \times p$ diagonal matrix, with diagonal entries $d _ { 1 } \geq d _ { 2 } \geq$ $\cdots \geq d _ { p } \geq 0$ called the singular values of X. If one or more values $d _ { j } = 0$ 2 X is singular. 

Using the singular value decomposition we can write the least squares fitted vector as 

$$
\begin{array}{r c l} \mathbf {X} \hat {\beta} ^ {\mathrm{ls}} & = & \mathbf {X} (\mathbf {X} ^ {T} \mathbf {X}) ^ {- 1} \mathbf {X} ^ {T} \mathbf {y} \\ & = & \mathbf {U U} ^ {T} \mathbf {y}, \end{array}\tag{3.46}
$$

after some simplification. Note that $\mathbf { U } ^ { T } \mathbf { y }$ are the coordinates of y with respect to the orthonormal basis U. Note also the similarity with (3.33); Q and U are generally different orthogonal bases for the column space of X (Exercise 3.8). 

Now the ridge solutions are 

$$
\begin{array}{r c l} \mathbf {X} \hat {\beta} ^ {\text {ridge}} & = & \mathbf {X} (\mathbf {X} ^ {T} \mathbf {X} + \lambda \mathbf {I}) ^ {- 1} \mathbf {X} ^ {T} \mathbf {y} \\ & = & \mathbf {U}   \mathbf {D} (\mathbf {D} ^ {2} + \lambda \mathbf {I}) ^ {- 1} \mathbf {D}   \mathbf {U} ^ {T} \mathbf {y} \\ & = & \sum_ {j = 1} ^ {p} \mathbf {u} _ {j} \frac {d _ {j} ^ {2}}{d _ {j} ^ {2} + \lambda} \mathbf {u} _ {j} ^ {T} \mathbf {y}, \end{array}\tag{3.47}
$$

where the $\mathbf { u } _ { j }$ are the columns of U. Note that since $\lambda \geq 0$ , we have $d _ { j } ^ { 2 } / ( d _ { j } ^ { 2 } +$ $\lambda ) \leq 1$ . Like linear regression, ridge regression computes the coordinates of y with respect to the orthonormal basis U. It then shrinks these coordinates by the factors $d _ { j } ^ { 2 } / ( d _ { j } ^ { 2 } + \lambda )$ . This means that a greater amount of shrinkage is applied to the coordinates of basis vectors with smaller $d _ { j } ^ { 2 }$ 

What does a small value of $d _ { j } ^ { 2 }$ mean? The SVD of the centered matrix X is another way of expressing the principal components of the variables in X. The sample covariance matrix is given by $\bar { \mathbf { S } } = \mathbf { X } ^ { T } \mathbf { X } / N$ , and from (3.45) we have 

$$
\mathbf {X} ^ {T} \mathbf {X} = \mathbf {V D} ^ {2} \mathbf {V} ^ {T},\tag{3.48}
$$

which is the eigen decomposition of $\mathbf { X } ^ { T } \mathbf { X }$ (and of S, up to a factor $N )$ The eigenvectors $v _ { j }$ (columns of V) are also called the principal components (or Karhunen–Loeve) directions of X. The first principal component direction $v _ { 1 }$ has the property that $\mathbf { z } _ { 1 } = \mathbf { X } v _ { 1 }$ has the largest sample variance amongst all normalized linear combinations of the columns of X. This sample variance is easily seen to be 

$$
\mathrm{Var} (\mathbf {z} _ {1}) = \mathrm{Var} (\mathbf {X} v _ {1}) = \frac {d _ {1} ^ {2}}{N},\tag{3.49}
$$

and in fact $\mathbf { z } _ { 1 } = \mathbf { X } v _ { 1 } = \mathbf { u } _ { 1 } d _ { 1 }$ . The derived variable $\mathbf { z } _ { 1 }$ is called the first principal component of X, and hence $\mathbf { u } _ { 1 }$ is the normalized first principal component. Subsequent principal components $\mathbf { z } _ { j }$ have maximum variance $d _ { j } ^ { 2 } / N$ , subject to being orthogonal to the earlier ones. Conversely the last principal component has minimum variance. Hence the small singular values $d _ { j }$ correspond to directions in the column space of X having small variance, and ridge regression shrinks these directions the most. 

![image](<Images/03_Linear_Methods_for_Regression_image_009.jpg>)



FIGURE 3.9. Principal components of some input data points. The largest principal component is the direction that maximizes the variance of the projected data, and the smallest principal component minimizes that variance. Ridge regression projects y onto these components, and then shrinks the coefficients of the low– variance components more than the high-variance components.


Figure 3.9 illustrates the principal components of some data points in two dimensions. If we consider fitting a linear surface over this domain (the Y -axis is sticking out of the page), the configuration of the data allow us to determine its gradient more accurately in the long direction than the short. Ridge regression protects against the potentially high variance of gradients estimated in the short directions. The implicit assumption is that the response will tend to vary most in the directions of high variance of the inputs. This is often a reasonable assumption, since predictors are often chosen for study because they vary with the response variable, but need not hold in general. 

In Figure 3.7 we have plotted the estimated prediction error versus the quantity 

$$
\begin{array}{r c l} \mathrm{df} (\lambda) & = & \mathrm{tr} [ \mathbf {X} (\mathbf {X} ^ {T} \mathbf {X} + \lambda \mathbf {I}) ^ {- 1} \mathbf {X} ^ {T} ], \\ & = & \mathrm{tr} (\mathbf {H} _ {\lambda}) \\ & = & \sum_ {j = 1} ^ {p} \frac {d _ {j} ^ {2}}{d _ {j} ^ {2} + \lambda}. \end{array}\tag{3.50}
$$

This monotone decreasing function of λ is the effective degrees of freedom of the ridge regression fit. Usually in a linear-regression fit with $p$ variables, the degrees-of-freedom of the fit is $p ,$ the number of free parameters. The idea is that although all $p$ coefficients in a ridge fit will be non-zero, they are fit in a restricted fashion controlled by λ. Note that df $( \lambda ) = p$ when $\lambda \ : = \ : 0$ (no regularization) and $\mathrm { d f } ( \lambda )  0$ as $\lambda  \infty$ . Of course there is always an additional one degree of freedom for the intercept, which was removed apriori. This definition is motivated in more detail in Section 3.4.4 and Sections 7.4–7.6. In Figure 3.7 the minimum occurs at $\mathrm { d f } ( \lambda ) = 5 . 0$ Table 3.3 shows that ridge regression reduces the test error of the full least squares estimates by a small amount. 

## 3.4.2 The Lasso

The lasso is a shrinkage method like ridge, with subtle but important differences. The lasso estimate is defined by 

$$
\begin{array}{r c l} \hat {\beta} ^ {\text {lasso}} & = & \underset {\beta} {\operatorname{argmin}} \sum_ {i = 1} ^ {N} \Bigl (y _ {i} - \beta_ {0} - \sum_ {j = 1} ^ {p} x _ {i j} \beta_ {j} \Bigr) ^ {2} \\ & & \text {subject to} \sum_ {j = 1} ^ {p} | \beta_ {j} | \leq t. \end{array}\tag{3.51}
$$

Just as in ridge regression, we can re-parametrize the constant $\beta _ { 0 }$ by standardizing the predictors; the solution for $\hat { \beta } _ { 0 }$ is ${ \bar { y } } .$ , and thereafter we fit a model without an intercept (Exercise 3.5). In the signal processing literature, the lasso is also known as basis pursuit (Chen et al., 1998). 

We can also write the lasso problem in the equivalent Lagrangian form 

$$
\hat {\beta} ^ {\text {lasso}} = \underset {\beta} {\operatorname{argmin}} \bigg \{\frac {1}{2} \sum_ {i = 1} ^ {N} \big (y _ {i} - \beta_ {0} - \sum_ {j = 1} ^ {p} x _ {i j} \beta_ {j} \big) ^ {2} + \lambda \sum_ {j = 1} ^ {p} | \beta_ {j} | \bigg \}.\tag{3.52}
$$

Notice the similarity to the ridge regression problem (3.42) or (3.41): the $L _ { 2 }$ ridge penalty $\textstyle \sum _ { 1 } ^ { \cdot p } \beta _ { j } ^ { 2 }$ is replaced by the $L _ { 1 }$ lasso penalty $\sum _ { 1 } ^ { p } | \beta _ { j } |$ . This latter constraint makes the solutions nonlinear in the $y _ { i }$ , and there is no closed form expression as in ridge regression. Computing the lasso solution is a quadratic programming problem, although we see in Section 3.4.4 that efficient algorithms are available for computing the entire path of solutions as λ is varied, with the same computational cost as for ridge regression. Because of the nature of the constraint, making t sufficiently small will cause some of the coefficients to be exactly zero. Thus the lasso does a kind of continuous subset selection. If t is chosen larger than $t _ { 0 } = \sum _ { 1 } ^ { p } | \hat { \beta } _ { j } |$ (where $\hat { \beta } _ { j } = \hat { \beta } _ { j } ^ { \mathrm { l s } }$ , the least squares estimates), then the lasso estimates are the $\hat { \beta } _ { j } { } ^ { \dag } \mathrm { s }$ On the other hand, for $t = t _ { 0 } / 2$ say, then the least squares coefficients are shrunk by about 50% on average. However, the nature of the shrinkage is not obvious, and we investigate it further in Section 3.4.4 below. Like the subset size in variable subset selection, or the penalty parameter in ridge regression, t should be adaptively chosen to minimize an estimate of expected prediction error. 

In Figure 3.7, for ease of interpretation, we have plotted the lasso prediction error estimates versus the standardized parameter $s = t / \textstyle \sum _ { 1 } ^ { p } | \hat { \beta } _ { j } |$ A value $\hat { s } \approx 0 . 3 6$ was chosen by 10-fold cross-validation; this caused four coefficients to be set to zero (fifth column of Table 3.3). The resulting model has the second lowest test error, slightly lower than the full least squares model, but the standard errors of the test error estimates (last line of Table 3.3) are fairly large. 

Figure 3.10 shows the lasso coefficients as the standardized tuning parameter $s = t / \textstyle \sum _ { 1 } ^ { p } | \hat { \beta } _ { j } |$ is varied. $\mathrm { A t } \ s \ = 1 . 0$ these are the least squares estimates; they decrease to 0 as $s \to 0$ . This decrease is not always strictly monotonic, although it is in this example. A vertical line is drawn at $s = 0 . 3 6$ , the value chosen by cross-validation. 

## 3.4.3 Discussion: Subset Selection, Ridge Regression and the Lasso

In this section we discuss and compare the three approaches discussed so far for restricting the linear regression model: subset selection, ridge regression and the lasso. 

In the case of an orthonormal input matrix X the three procedures have explicit solutions. Each method applies a simple transformation to the least squares estimate $\hat { \beta } _ { j }$ , as detailed in Table 3.4. 

Ridge regression does a proportional shrinkage. Lasso translates each coefficient by a constant factor λ, truncating at zero. This is called “soft thresholding,” and is used in the context of wavelet-based smoothing in Section 5.9. Best-subset selection drops all variables with coefficients smaller than the Mth largest; this is a form of “hard-thresholding.” 

Back to the nonorthogonal case; some pictures help understand their relationship. Figure 3.11 depicts the lasso (left) and ridge regression (right) when there are only two parameters. The residual sum of squares has elliptical contours, centered at the full least squares estimate. The constraint region for ridge regression is the disk $\beta _ { 1 } ^ { 2 } + \beta _ { 2 } ^ { 2 } \leq t$ , while that for lasso is the diamond $| \beta _ { 1 } | + | \beta _ { 2 } | \le t$ . Both methods find the first point where the elliptical contours hit the constraint region. Unlike the disk, the diamond has corners; if the solution occurs at a corner, then it has one parameter $\beta _ { j }$ equal to zero. When $p > 2$ , the diamond becomes a rhomboid, and has many corners, flat edges and faces; there are many more opportunities for the estimated parameters to be zero. 

![image](<Images/03_Linear_Methods_for_Regression_image_010.jpg>)



FIGURE 3.10. Profiles of lasso coefficients, as the tuning parameter t is varied. Coefficients are plotted versus $s = t / \sum _ { 1 } ^ { p } | \hat { \beta } _ { j } |$ . A vertical line is drawn at $s = 0 . 3 6$ the value chosen by cross-validation. Compare Figure 3.8 on page 65; the lasso profiles hit zero, while those for ridge do not. The profiles are piece-wise linear, and so are computed only at the points displayed; see Section 3.4.4 for details.



TABLE 3.4. Estimators of $\beta _ { j }$ in the case of orthonormal columns of X. M and λ are constants chosen by the corresponding techniques; sign denotes the sign of its argument $( \pm 1 )$ , and $x _ { + }$ denotes “positive part” of x. Below the table, estimators are shown by broken red lines. The $4 5 ^ { \circ }$ line in gray shows the unrestricted estimate for reference.


<table><tr><td>Estimator</td><td>Formula</td></tr><tr><td>Best subset (size M)</td><td><eq>\hat{\beta}_{j} \cdot I(|\hat{\beta}_{j}| \geq |\hat{\beta}_{(M)}|)</eq></td></tr><tr><td>Ridge</td><td><eq>\hat{\beta}_{j}/(1 + \lambda)</eq></td></tr><tr><td>Lasso</td><td><eq>\text{sign}(\hat{\beta}_{j})(|\hat{\beta}_{j}| - \lambda)_{+}</eq></td></tr></table>

![image](<Images/03_Linear_Methods_for_Regression_image_011.jpg>)



FIGURE 3.11. Estimation picture for the lasso $( l e f t )$ and ridge regression (right). Shown are contours of the error and constraint functions. The solid blue areas are the constraint regions $| \beta _ { 1 } | + | \beta _ { 2 } | \le t$ and $\beta _ { 1 } ^ { 2 ^ { - } } + \beta _ { 2 } ^ { 2 } \leq t ^ { 2 }$ , respectively, while the red ellipses are the contours of the least squares error function.


We can generalize ridge regression and the lasso, and view them as Bayes estimates. Consider the criterion 

$$
\tilde {\beta} = \underset {\beta} {\operatorname{argmin}} \left\{\sum_ {i = 1} ^ {N} \left(y _ {i} - \beta_ {0} - \sum_ {j = 1} ^ {p} x _ {i j} \beta_ {j}\right) ^ {2} + \lambda \sum_ {j = 1} ^ {p} | \beta_ {j} | ^ {q} \right\}\tag{3.53}
$$

for $q \geq 0$ . The contours of constant value of $\textstyle \sum _ { j } | \beta _ { j } | ^ { q }$ are shown in Figure 3.12, for the case of two inputs. 

Thinking of $| \beta _ { j } | ^ { q }$ as the log-prior density for $\beta _ { j }$ , these are also the equicontours of the prior distribution of the parameters. The value $q = 0$ corresponds to variable subset selection, as the penalty simply counts the number of nonzero parameters; $q = 1$ corresponds to the lasso, while $q = 2$ to ridge regression. Notice that for $q \leq 1$ , the prior is not uniform in direction, but concentrates more mass in the coordinate directions. The prior corresponding to the $q = 1$ case is an independent double exponential (or Laplace) distribution for each input, with density $( 1 / 2 \tau ) \exp ( - | \beta | / \tau )$ and $\tau = 1 / \lambda$ The case $q = 1 \ \mathrm { ( l a s s o ) }$ is the smallest $q$ such that the constraint region is convex; non-convex constraint regions make the optimization problem more difficult. 

In this view, the lasso, ridge regression and best subset selection are Bayes estimates with different priors. Note, however, that they are derived as posterior modes, that is, maximizers of the posterior. It is more common to use the mean of the posterior as the Bayes estimate. Ridge regression is also the posterior mean, but the lasso and best subset selection are not. 

Looking again at the criterion (3.53), we might try using other values of $q$ besides 0, 1, or 2. Although one might consider estimating $q$ from the data, our experience is that it is not worth the effort for the extra variance incurred. Values of $q \in ( 1 , 2 )$ suggest a compromise between the lasso and ridge regression. Although this is the case, with $q > 1 , | \beta _ { j } | ^ { q }$ is differentiable at 0, and so does not share the ability of lasso $( q = 1 )$ for setting coefficients exactly to zero. Partly for this reason as well as for computational tractability, Zou and Hastie (2005) introduced the elasticnet penalty 

![image](<Images/03_Linear_Methods_for_Regression_image_012.jpg>)



FIGURE 3.12. Contours of constant value of $\textstyle \sum _ { j } | \beta _ { j } | ^ { q }$ for given values of $q .$ .


![image](<Images/03_Linear_Methods_for_Regression_image_013.jpg>)



FIGURE 3.13. Contours of constant value of $\textstyle \sum _ { j } | \beta _ { j } | ^ { q }$ for $q = 1 . 2$ (left plot), and the elastic-net penalty $\begin{array} { r l } { \sum _ { j } ( \alpha \beta _ { j } ^ { 2 } + ( 1 - \alpha ) | \beta _ { j } | ) } & { { } } \end{array}$ for $\alpha = 0 . 2$ (right plot). Although visually very similar, the elastic-net has sharp (non-differentiable) corners, while the $q = 1 . 2$ penalty does not.


$$
\lambda \sum_ {j = 1} ^ {p} \bigl (\alpha \beta_ {j} ^ {2} + (1 - \alpha) | \beta_ {j} | \bigr),\tag{3.54}
$$

a different compromise between ridge and lasso. Figure 3.13 compares the $L _ { q }$ penalty with $q = 1 . 2$ and the elastic-net penalty with $\alpha = 0 . 2 $ ; it is hard to detect the difference by eye. The elastic-net selects variables like the lasso, and shrinks together the coefficients of correlated predictors like ridge. It also has considerable computational advantages over the $L _ { q }$ penalties. We discuss the elastic-net further in Section 18.4. 

## 3.4.4 Least Angle Regression

Least angle regression (LAR) is a relative newcomer (Efron et al., 2004), and can be viewed as a kind of “democratic” version of forward stepwise regression (Section 3.3.2). As we will see, LAR is intimately connected with the lasso, and in fact provides an extremely efficient algorithm for computing the entire lasso path as in Figure 3.10. 

Forward stepwise regression builds a model sequentially, adding one variable at a time. At each step, it identifies the best variable to include in the active set, and then updates the least squares fit to include all the active variables. 

Least angle regression uses a similar strategy, but only enters “as much” of a predictor as it deserves. At the first step it identifies the variable most correlated with the response. Rather than fit this variable completely, LAR moves the coefficient of this variable continuously toward its leastsquares value (causing its correlation with the evolving residual to decrease in absolute value). As soon as another variable “catches up” in terms of correlation with the residual, the process is paused. The second variable then joins the active set, and their coefficients are moved together in a way that keeps their correlations tied and decreasing. This process is continued until all the variables are in the model, and ends at the full least-squares fit. Algorithm 3.2 provides the details. The termination condition in step 5 requires some explanation. If $p > N - 1$ , the LAR algorithm reaches a zero residual solution after $N - 1$ steps (the 1 is because we have centered the data). 

Algorithm 3.2 Least Angle Regression.

1. Standardize the predictors to have mean zero and unit norm. Start with the residual $\mathbf{r} = \mathbf{y} - \bar{\mathbf{y}}, \beta_1, \beta_2, \ldots, \beta_p = 0$ .

2. Find the predictor $\mathbf{x}_j$ most correlated with $\mathbf{r}$ .

3. Move $\beta_j$ from 0 towards its least-squares coefficient $\langle \mathbf{x}_j, \mathbf{r} \rangle$ , until some other competitor $\mathbf{x}_k$ has as much correlation with the current residual as does $\mathbf{x}_j$ .

4. Move $\beta_j$ and $\beta_k$ in the direction defined by their joint least squares coefficient of the current residual on $(\mathbf{x}_j, \mathbf{x}_k)$ , until some other competitor $\mathbf{x}_l$ has as much correlation with the current residual.

5. Continue in this way until all $p$ predictors have been entered. After $\min(N - 1, p)$ steps, we arrive at the full least-squares solution.

Suppose $\mathcal{A}_k$ is the active set of variables at the beginning of the $k$ th step, and let $\beta_{\mathcal{A}_k}$ be the coefficient vector for these variables at this step; there will be $k - 1$ nonzero values, and the one just entered will be zero. If $\mathbf{r}_k = \mathbf{y} - \mathbf{X}_{\mathcal{A}_k} \beta_{\mathcal{A}_k}$ is the current residual, then the direction for this step is

[\delta_k = (\mathbf{X}_{\mathcal{A}_k}^T \mathbf{X}_{\mathcal{A}_k})^{-1} \mathbf{X}_{\mathcal{A}_k}^T \mathbf{r}_k]

(3.55)

The coefficient profile then evolves as $\beta_{\mathcal{A}_k}(\alpha) = \beta_{\mathcal{A}_k} + \alpha \cdot \delta_k$ . Exercise 3.23 verifies that the directions chosen in this fashion do what is claimed: keep the correlations tied and decreasing. If the fit vector at the beginning of this step is $\hat{\mathbf{f}}_k$ , then it evolves as $\hat{\mathbf{f}}_k(\alpha) = \hat{\mathbf{f}}_k + \alpha \cdot \mathbf{u}_k$ , where $\mathbf{u}_k = \mathbf{X}_{\mathcal{A}_k} \delta_k$ is the new fit direction. The name “least angle” arises from a geometrical interpretation of this process; $\mathbf{u}_k$ makes the smallest (and equal) angle with each of the predictors in $\mathcal{A}_k$ (Exercise 3.24). Figure 3.14 shows the absolute correlations decreasing and joining ranks with each step of the LAR algorithm, using simulated data. 

By construction the coefficients in LAR change in a piecewise linear fashion. Figure 3.15 [left panel] shows the LAR coefficient profile evolving as a function of their $L _ { 1 }$ arc length <sup>2</sup>. Note that we do not need to take small steps and recheck the correlations in step 3; using knowledge of the covariance of the predictors and the piecewise linearity of the algorithm, we can work out the exact step length at the beginning of each step (Exercise 3.25). 

![image](<Images/03_Linear_Methods_for_Regression_image_014.jpg>)



FIGURE 3.14. Progression of the absolute correlations during each step of the LAR procedure, using a simulated data set with six predictors. The labels at the top of the plot indicate which variables enter the active set at each step. The step length are measured in units of $L _ { 1 }$ arc length.


![image](<Images/03_Linear_Methods_for_Regression_image_015.jpg>)


![image](<Images/03_Linear_Methods_for_Regression_image_016.jpg>)



FIGURE 3.15. Left panel shows the LAR coefficient profiles on the simulated data, as a function of the $L _ { 1 }$ arc length. The right panel shows the Lasso profile. They are identical until the dark-blue coefficient crosses zero at an arc length of about 18.


The right panel of Figure 3.15 shows the lasso coefficient profiles on the same data. They are almost identical to those in the left panel, and differ for the first time when the blue coefficient passes back through zero. For the prostate data, the LAR coefficient profile turns out to be identical to the lasso profile in Figure 3.10, which never crosses zero. These observations lead to a simple modification of the LAR algorithm that gives the entire lasso path, which is also piecewise-linear. 

## Algorithm 3.2a Least Angle Regression: Lasso Modification.

4a. If a non-zero coefficient hits zero, drop its variable from the active set of variables and recompute the current joint least squares direction. 

The LAR(lasso) algorithm is extremely efficient, requiring the same order of computation as that of a single least squares fit using the p predictors. Least angle regression always takes $p$ steps to get to the full least squares estimates. The lasso path can have more than $p$ steps, although the two are often quite similar. Algorithm 3.2 with the lasso modification 3.2a is an efficient way of computing the solution to any lasso problem, especially when $p \gg N$ . Osborne et al. (2000a) also discovered a piecewise-linear path for computing the lasso, which they called a homotopy algorithm. 

We now give a heuristic argument for why these procedures are so similar. Although the LAR algorithm is stated in terms of correlations, if the input features are standardized, it is equivalent and easier to work with innerproducts. Suppose $\mathcal { A }$ is the active set of variables at some stage in the algorithm, tied in their absolute inner-product with the current residuals $\mathbf { y } - \mathbf { X } { \boldsymbol { \beta } } $ . We can express this as 

$$
\mathbf {x} _ {j} ^ {T} (\mathbf {y} - \mathbf {X} \beta) = \boldsymbol {\gamma} \cdot \boldsymbol {s} _ {j}, \forall j \in \mathcal {A}\tag{3.56}
$$

where $s _ { j } \in \{ - 1 , 1 \}$ indicates the sign of the inner-product, and $\gamma$ is the common value. Also $| \mathbf { x } _ { k } ^ { T } ( \mathbf { y } - \mathbf { X } \beta ) | \leq \gamma ~ \forall k ~ \notin ~ \mathcal { A } .$ . Now consider the lasso criterion (3.52), which we write in vector form 

$$
R (\beta) = \frac {1}{2} | | \mathbf {y} - \mathbf {X} \beta | | _ {2} ^ {2} + \lambda | | \beta | | _ {1}.\tag{3.57}
$$

Let be the active set of variables in the solution for a given value of λ. For these variables $R ( \beta )$ is differentiable, and the stationarity conditions give 

$$
\mathbf {x} _ {j} ^ {T} (\mathbf {y} - \mathbf {X} \beta) = \lambda \cdot \mathrm{sign} (\beta_ {j}), \forall j \in \mathcal {B}\tag{3.58}
$$

Comparing (3.58) with (3.56), we see that they are identical only if the sign of $\beta _ { j }$ matches the sign of the inner product. That is why the LAR algorithm and lasso start to differ when an active coefficient passes through zero; condition (3.58) is violated for that variable, and it is kicked out of the active set . Exercise 3.23 shows that these equations imply a piecewiselinear coefficient profile as $\lambda$ decreases. The stationarity conditions for the non-active variables require that 

$$
| \mathbf {x} _ {k} ^ {T} (\mathbf {y} - \mathbf {X} \beta) | \leq \lambda ,   \forall k \not \in \mathcal {B},\tag{3.59}
$$

which again agrees with the LAR algorithm. 

Figure 3.16 compares LAR and lasso to forward stepwise and stagewise regression. The setup is the same as in Figure 3.6 on page 59, except here $N = 1 0 0$ here rather than 300, so the problem is more difficult. We see that the more aggressive forward stepwise starts to overfit quite early (well before the 10 true variables can enter the model), and ultimately performs worse than the slower forward stagewise regression. The behavior of LAR and lasso is similar to that of forward stagewise regression. Incremental forward stagewise is similar to LAR and lasso, and is described in Section 3.8.1. 

## Degrees-of-Freedom Formula for LAR and Lasso

Suppose that we fit a linear model via the least angle regression procedure, stopping at some number of steps $k < p ,$ or equivalently using a lasso bound t that produces a constrained version of the full least squares fit. How many parameters, or “degrees of freedom” have we used? 

Consider first a linear regression using a subset of k features. If this subset is prespecified in advance without reference to the training data, then the degrees of freedom used in the fitted model is defined to be k. Indeed, in classical statistics, the number of linearly independent parameters is what is meant by “degrees of freedom.” Alternatively, suppose that we carry out a best subset selection to determine the “optimal” set of k predictors. Then the resulting model has k parameters, but in some sense we have used up more than k degrees of freedom. 

We need a more general definition for the effective degrees of freedom of an adaptively fitted model. We define the degrees of freedom of the fitted vector $\hat { \mathbf { y } } = \left( \hat { y } _ { 1 } , \hat { y } _ { 2 } , \dots , \hat { y } _ { N } \right)$ as 

$$
\mathrm{df} (\hat {\mathbf {y}}) = \frac {1}{\sigma^ {2}} \sum_ {i = 1} ^ {N} \operatorname{Cov} (\hat {y} _ {i}, y _ {i}).\tag{3.60}
$$

Here $\operatorname { C o v } ( \hat { y } _ { i } , y _ { i } )$ refers to the sampling covariance between the predicted value $\hat { y } _ { i }$ and its corresponding outcome value $y _ { i }$ . This makes intuitive sense: the harder that we fit to the data, the larger this covariance and hence $\operatorname { d f } ( { \hat { \mathbf { y } } } )$ . Expression (3.60) is a useful notion of degrees of freedom, one that can be applied to any model prediction $\hat { \mathbf { y } }$ . This includes models that are adaptively fitted to the training data. This definition is motivated and discussed further in Sections 7.4–7.6. 

![image](<Images/03_Linear_Methods_for_Regression_image_017.jpg>)



FIGURE 3.16. Comparison of LAR and lasso with forward stepwise, forward stagewise (FS) and incremental forward stagewise $( F S _ { 0 } )$ regression. The setup is the same as in Figure 3.6, except $N = 1 0 0$ here rather than 300. Here the slower FS regression ultimately outperforms forward stepwise. LAR and lasso show similar behavior to FS and $F S _ { 0 }$ . Since the procedures take different numbers of steps (across simulation replicates and methods), we plot the MSE as a function of the fraction of total $L _ { 1 }$ arc-length toward the least-squares $\mathit { f i t }$


Now for a linear regression with k fixed predictors, it is easy to show that d $\mathbf { \hat { y } } ( \hat { \mathbf { y } } ) = k$ . Likewise for ridge regression, this definition leads to the closed-form expression (3.50) on page 68: $\mathrm { d } \mathbf { f } ( \hat { \mathbf { y } } ) = \mathrm { t r } ( \mathbf { S } _ { \lambda } )$ . In both these cases, (3.60) is simple to evaluate because the fit $\hat { \mathbf { y } } = \mathbf { H } _ { \lambda } \mathbf { y }$ is linear in $\mathbf { y }$ If we think about definition (3.60) in the context of a best subset selection of size $k ,$ it seems clear that df(yˆ) will be larger than k, and this can be verified by estimating $\mathrm { C o v } ( \hat { y } _ { i } , y _ { i } ) / \sigma ^ { 2 }$ directly by simulation. However there is no closed form method for estimating $\operatorname { d f } ( { \hat { \mathbf { y } } } )$ for best subset selection. 

For LAR and lasso, something magical happens. These techniques are adaptive in a smoother way than best subset selection, and hence estimation of degrees of freedom is more tractable. Specifically it can be shown that after the kth step of the LAR procedure, the effective degrees of freedom of the fit vector is exactly k. Now for the lasso, the (modified) LAR procedure often takes more than p steps, since predictors can drop out. Hence the definition is a little different; for the lasso, at any stage $\operatorname { d f } ( { \hat { \mathbf { y } } } )$ approximately equals the number of predictors in the model. While this approximation works reasonably well anywhere in the lasso path, for each k it works best at the last model in the sequence that contains k predictors. A detailed study of the degrees of freedom for the lasso may be found in Zou et al. (2007). 

## 3.5 Methods Using Derived Input Directions

In many situations we have a large number of inputs, often very correlated. The methods in this section produce a small number of linear combinations $Z _ { m } , m = 1 , \ldots , M$ of the original inputs $X _ { j }$ , and the $Z _ { m }$ are then used in place of the $X _ { j }$ as inputs in the regression. The methods differ in how the linear combinations are constructed. 

## 3.5.1 Principal Components Regression

In this approach the linear combinations $Z _ { m }$ used are the principal components as defined in Section 3.4.1 above. 

Principal component regression forms the derived input columns $\mathbf { z } _ { m } =$ ${ \bf X } v _ { m }$ , and then regresses y on $\mathbf { z } _ { 1 } , \mathbf { z } _ { 2 } , \dots , \mathbf { z } _ { M }$ for some $M \leq p$ . Since the $\mathbf { z } _ { m }$ are orthogonal, this regression is just a sum of univariate regressions: 

$$
\hat {\mathbf {y}} _ {(M)} ^ {\mathrm{pcr}} = \bar {y} \mathbf {1} + \sum_ {m = 1} ^ {M} \hat {\theta} _ {m} \mathbf {z} _ {m},\tag{3.61}
$$

where $\hat { \theta } _ { m } = \langle \mathbf { z } _ { m } , \mathbf { y } \rangle / \langle \mathbf { z } _ { m } , \mathbf { z } _ { m } \rangle$ . Since the $\mathbf { z } _ { m }$ are each linear combinations of the original $\mathbf { x } _ { j }$ , we can express the solution (3.61) in terms of coefficients of the $\mathbf { x } _ { j }$ (Exercise 3.13): 

$$
\hat {\beta} ^ {\mathrm{pcr}} (M) = \sum_ {m = 1} ^ {M} \hat {\theta} _ {m} v _ {m}.\tag{3.62}
$$

As with ridge regression, principal components depend on the scaling of the inputs, so typically we first standardize them. Note that if $M = p$ , we would just get back the usual least squares estimates, since the columns of $\mathbf { Z } = \mathbf { U } \mathbf { D }$ span the column space of $\mathbf { X }$ . For $M < p$ we get a reduced regression. We see that principal components regression is very similar to ridge regression: both operate via the principal components of the input matrix. Ridge regression shrinks the coefficients of the principal components (Figure 3.17), shrinking more depending on the size of the corresponding eigenvalue; principal components regression discards the $p - M$ smallest eigenvalue components. Figure 3.17 illustrates this. 

![image](<Images/03_Linear_Methods_for_Regression_image_018.jpg>)



FIGURE 3.17. Ridge regression shrinks the regression coefficients of the principal components, using shrinkage factors $d _ { j } ^ { 2 } / ( d _ { j } ^ { 2 } + \lambda )$ as in (3.47). Principal component regression truncates them. Shown are the shrinkage and truncation patterns corresponding to Figure 3.7, as a function of the principal component index.


In Figure 3.7 we see that cross-validation suggests seven terms; the resulting model has the lowest test error in Table 3.3. 

## 3.5.2 Partial Least Squares

This technique also constructs a set of linear combinations of the inputs for regression, but unlike principal components regression it uses y (in addition to X) for this construction. Like principal component regression, partial least squares (PLS) is not scale invariant, so we assume that each $\mathbf { x } _ { j }$ is standardized to have mean 0 and variance 1. PLS begins by computing $\hat { \varphi } _ { 1 j } = \langle \mathbf { x } _ { j } , \mathbf { y } \rangle$ for each $j$ . From this we construct the derived input $\begin{array} { r } { { \bf z } _ { 1 } = \sum _ { j } \hat { \varphi } _ { 1 j } { \bf x } _ { j } } \end{array}$ , which is the first partial least squares direction. Hence in the construction of each $\mathbf { z } _ { m }$ , the inputs are weighted by the strength of their univariate effect on $\mathbf { y } ^ { 3 }$ . The outcome y is regressed on $\mathbf { z } _ { 1 }$ giving coefficient $\widehat { \theta } _ { 1 }$ , and then we orthogonalize $\mathbf { x } _ { 1 } , \ldots , \mathbf { x } _ { p }$ with respect to $\mathbf { z } _ { 1 }$ . We continue this process, until $M \leq p$ directions have been obtained. In this manner, partial least squares produces a sequence of derived, orthogonal inputs or directions $\mathbf { z } _ { 1 } , \mathbf { z } _ { 2 } , \dots , \mathbf { z } _ { M }$ . As with principal-component regression, if we were to construct all $M = p$ directions, we would get back a solution equivalent to the usual least squares estimates; using $M < p$ directions produces a reduced regression. The procedure is described fully in Algorithm 3.3. 

Algorithm 3.3 Partial Least Squares.

1. Standardize each $x_{j}$ to have mean zero and variance one. Set $\hat{\mathbf{y}}^{(0)} = \bar{y}\mathbf{1}$ , and $\mathbf{x}_{j}^{(0)} = \mathbf{x}_{j}, j = 1, \ldots, p$ .

2. For $m = 1, 2, \ldots, p$ (a) $z_{m} = \sum_{j=1}^{p} \hat{\varphi}_{mj} x_{j}^{(m-1)}$ , where $\hat{\varphi}_{mj} = \langle x_{j}^{(m-1)}, y \rangle$ .

(b) $\hat{\theta}_{m} = \langle z_{m}, y \rangle / \langle z_{m}, z_{m} \rangle$ .

(c) $\hat{\mathbf{y}}^{(m)} = \hat{\mathbf{y}}^{(m-1)} + \hat{\theta}_{m} z_{m}$ .

(d) Orthogonalize each $x_{j}^{(m-1)}$ with respect to $z_{m}: x_{j}^{(m)} = x_{j}^{(m-1)} - [\langle z_{m}, x_{j}^{(m-1)} \rangle / \langle z_{m}, z_{m} \rangle] z_{m}, j = 1, 2, \ldots, p$ .

3. Output the sequence of fitted vectors $\{\hat{\mathbf{y}}^{(m)}\}_{1}^{p}$ . Since the $\{z_{\ell}\}_{1}^{m}$ are linear in the original $x_{j}$ , so is $\hat{\mathbf{y}}^{(m)} = X \hat{\beta}^{\text{pls}}(m)$ . These linear coefficients can be recovered from the sequence of PLS transformations. 

In the prostate cancer example, cross-validation chose M = 2 PLS directions in Figure 3.7. This produced the model given in the rightmost column of Table 3.3. 

What optimization problem is partial least squares solving? Since it uses the response y to construct its directions, its solution path is a nonlinear function of y. It can be shown (Exercise 3.15) that partial least squares seeks directions that have high variance and have high correlation with the response, in contrast to principal components regression which keys only on high variance (Stone and Brooks, 1990; Frank and Friedman, 1993). In particular, the mth principal component direction $v _ { m }$ solves: 

$$
\begin{array}{c} \max _ {\alpha} \operatorname{Var} (\mathbf {X} \alpha) \\ \text {subject to} | | \alpha | | = 1, \alpha^ {T} \mathbf {S} v _ {\ell} = 0, \ell = 1, \ldots , m - 1, \end{array}\tag{3.63}
$$

where S is the sample covariance matrix of the $\mathbf { x } _ { j }$ . The conditions $\alpha ^ { T } \mathbf { S } v _ { \ell } =$ 0 ensures that $\mathbf { z } _ { m } = \mathbf { X } \alpha$ is uncorrelated with all the previous linear combinations $\mathbf { z } _ { \ell } = \mathbf { X } v _ { \ell }$ . The mth PLS direction $\hat { \varphi } _ { m }$ solves: 

$$
\begin{array}{c} \max _ {\alpha} \operatorname{Corr} ^ {2} (\mathbf {y}, \mathbf {X} \alpha) \operatorname{Var} (\mathbf {X} \alpha) \\ \text {subject to} | | \alpha | | = 1, \alpha^ {T} \mathbf {S} \hat {\varphi} _ {\ell} = 0, \ell = 1, \ldots , m - 1. \end{array}\tag{3.64}
$$

Further analysis reveals that the variance aspect tends to dominate, and so partial least squares behaves much like ridge regression and principal components regression. We discuss this further in the next section. 

If the input matrix X is orthogonal, then partial least squares finds the least squares estimates after $m = 1$ steps. Subsequent steps have no effect since the $\hat { \varphi } _ { m j }$ are zero for $m > 1$ (Exercise 3.14). It can also be shown that the sequence of PLS coefficients for $m = 1 , 2 , \hdots , p$ represents the conjugate gradient sequence for computing the least squares solutions (Exercise 3.18). 

## 3.6 Discussion: A Comparison of the Selection and Shrinkage Methods

There are some simple settings where we can understand better the relationship between the different methods described above. Consider an example with two correlated inputs $X _ { 1 }$ and $X _ { 2 }$ , with correlation $\rho .$ . We assume that the true regression coefficients are $\beta _ { 1 } = 4$ and $\beta _ { 2 } = 2$ . Figure 3.18 shows the coefficient profiles for the different methods, as their tuning parameters are varied. The top panel has $\rho = 0 . 5$ , the bottom panel $\rho = - 0 . 5$ The tuning parameters for ridge and lasso vary over a continuous range, while best subset, PLS and PCR take just two discrete steps to the least squares solution. In the top panel, starting at the origin, ridge regression shrinks the coefficients together until it finally converges to least squares. PLS and PCR show similar behavior to ridge, although are discrete and more extreme. Best subset overshoots the solution and then backtracks. The behavior of the lasso is intermediate to the other methods. When the correlation is negative (lower panel), again PLS and PCR roughly track the ridge path, while all of the methods are more similar to one another. 

It is interesting to compare the shrinkage behavior of these different methods. Recall that ridge regression shrinks all directions, but shrinks low-variance directions more. Principal components regression leaves M high-variance directions alone, and discards the rest. Interestingly, it can be shown that partial least squares also tends to shrink the low-variance directions, but can actually inflate some of the higher variance directions. This can make PLS a little unstable, and cause it to have slightly higher prediction error compared to ridge regression. A full study is given in Frank and Friedman (1993). These authors conclude that for minimizing prediction error, ridge regression is generally preferable to variable subset selection, principal components regression and partial least squares. However the improvement over the latter two methods was only slight. 

To summarize, PLS, PCR and ridge regression tend to behave similarly. Ridge regression may be preferred because it shrinks smoothly, rather than in discrete steps. Lasso falls somewhere between ridge regression and best subset regression, and enjoys some of the properties of each. 

![image](<Images/03_Linear_Methods_for_Regression_image_019.jpg>)



ρ = 0.5


![image](<Images/03_Linear_Methods_for_Regression_image_020.jpg>)



FIGURE 3.18. Coefficient profiles from different methods for a simple problem: two inputs with correlation 0.5, and the true regression coefficients $\beta = ( 4 , 2 )$


## 3.7 Multiple Outcome Shrinkage and Selection

As noted in Section 3.2.4, the least squares estimates in a multiple-output linear model are simply the individual least squares estimates for each of the outputs. 

To apply selection and shrinkage methods in the multiple output case, one could apply a univariate technique individually to each outcome or simultaneously to all outcomes. With ridge regression, for example, we could apply formula (3.44) to each of the K columns of the outcome matrix $Y .$ using possibly different parameters λ, or apply it to all columns using the same value of λ. The former strategy would allow different amounts of regularization to be applied to different outcomes but require estimation of k separate regularization parameters $\lambda _ { 1 } , \ldots , \lambda _ { k }$ , while the latter would permit all k outputs to be used in estimating the sole regularization parameter λ. 

Other more sophisticated shrinkage and selection strategies that exploit correlations in the different responses can be helpful in the multiple output case. Suppose for example that among the outputs we have 

$$
Y _ {k} = f (X) + \varepsilon_ {k}\tag{3.65}
$$

$$
Y _ {\ell} = f (X) + \varepsilon_ {\ell};\tag{3.66}
$$

i.e., (3.65) and (3.66) share the same structural part $f ( X )$ in their models. It is clear in this case that we should pool our observations on $Y _ { k }$ and $Y _ { l }$ to estimate the common $f .$ 

Combining responses is at the heart of canonical correlation analysis (CCA), a data reduction technique developed for the multiple output case. Similar to PCA, CCA finds a sequence of uncorrelated linear combinations $\mathbf { X } v _ { m } , \ m \ = \ 1 , \ldots , M$ of the $\mathbf { x } _ { j }$ , and a corresponding sequence of uncorrelated linear combinations $\mathbf { Y } u _ { m }$ of the responses $\mathbf { y } _ { k }$ , such that the correlations 

$$
\mathrm{Corr} ^ {2} (\mathbf {Y} u _ {m}, \mathbf {X} v _ {m})\tag{3.67}
$$

are successively maximized. Note that at most $M = \operatorname* { m i n } ( K , p )$ directions can be found. The leading canonical response variates are those linear combinations (derived responses) best predicted by the $\mathbf { x } _ { j } ;$ in contrast, the trailing canonical variates can be poorly predicted by the $\mathbf { x } _ { j }$ , and are candidates for being dropped. The CCA solution is computed using a generalized SVD of the sample cross-covariance matrix ${ \bf Y } ^ { T } { \bf X } / N$ (assuming Y and X are centered; Exercise 3.20). 

Reduced-rank regression (Izenman, 1975; van der Merwe and Zidek, 1980) formalizes this approach in terms of a regression model that explicitly pools information. Given an error covariance $\mathrm { C o v } ( \varepsilon ) = \Sigma$ , we solve the following restricted multivariate regression problem: 

$$
\hat {\mathbf {B}} ^ {\mathrm{rr}} (m) = \underset {\operatorname{rank} (\mathbf {B}) = m} {\operatorname{argmin}} \sum_ {i = 1} ^ {N} (y _ {i} - \mathbf {B} ^ {T} x _ {i}) ^ {T} \boldsymbol {\Sigma} ^ {- 1} (y _ {i} - \mathbf {B} ^ {T} x _ {i}).\tag{3.68}
$$

With Σ replaced by the estimate $\mathbf { Y } ^ { T } \mathbf { Y } / N$ , one can show (Exercise 3.21) that the solution is given by a CCA of Y and X: 

$$
\hat {\mathbf {B}} ^ {\mathrm{rr}} (m) = \hat {\mathbf {B}} \mathbf {U} _ {m} \mathbf {U} _ {m} ^ {-},\tag{3.69}
$$

where ${ \mathbf { U } } _ { m }$ is the $K \times m$ sub-matrix of U consisting of the first m columns, and U is the $K \times M$ matrix of $l e f t$ canonical vectors $u _ { 1 } , u _ { 2 } , \ldots , u _ { M } . \ \mathbf { U } _ { m } ^ { - }$ is its generalized inverse. Writing the solution as 

$$
\hat {\mathbf {B}} ^ {\mathrm{rr}} (M) = (\mathbf {X} ^ {T} \mathbf {X}) ^ {- 1} \mathbf {X} ^ {T} (\mathbf {Y} \mathbf {U} _ {m}) \mathbf {U} _ {m} ^ {-},\tag{3.70}
$$

we see that reduced-rank regression performs a linear regression on the pooled response matrix $\mathbf { Y U } _ { m } .$ , and then maps the coefficients (and hence the fits as well) back to the original response space. The reduced-rank fits are given by 

$$
\begin{array}{c} \hat {\mathbf {Y}} ^ {\mathrm{rr}} (m) = \mathbf {X} (\mathbf {X} ^ {T} \mathbf {X}) ^ {- 1} \mathbf {X} ^ {T} \mathbf {Y} \mathbf {U} _ {m} \mathbf {U} _ {m} ^ {-} \\ = \mathbf {H Y P} _ {m}, \end{array}\tag{3.71}
$$

where H is the usual linear regression projection operator, and $\mathbf { P } _ { m }$ is the rank-m CCA response projection operator. Although a better estimate of Σ would be $( \mathbf { Y } - \mathbf { \bar { X } } \hat { \mathbf { B } } ) ^ { T } ( \mathbf { Y } - \mathbf { X } \hat { \mathbf { B } } ) / ( \bar { N } - p K )$ , one can show that the solution remains the same (Exercise 3.22). 

Reduced-rank regression borrows strength among responses by truncating the CCA. Breiman and Friedman (1997) explored with some success shrinkage of the canonical variates between X and Y, a smooth version of reduced rank regression. Their proposal has the form (compare (3.69)) 

$$
\hat {\mathbf {B}} ^ {\mathrm{c+w}} = \hat {\mathbf {B}} \mathbf {U} \boldsymbol {\Lambda} \mathbf {U} ^ {- 1},\tag{3.72}
$$

where Λ is a diagonal shrinkage matrix $( \mathrm { t h e } \mathrm { \Omega } ^ { \mathrm { \tiny ~ * ~ } } \mathrm { c } + \mathrm { w } ^ { \mathrm { \tiny ~ * ~ } }$ stands for “Curds and Whey,” the name they gave to their procedure). Based on optimal prediction in the population setting, they show that Λ has diagonal entries 

$$
\lambda_ {m} = \frac {c _ {m} ^ {2}}{c _ {m} ^ {2} + \frac {p}{N} (1 - c _ {m} ^ {2})}, m = 1, \ldots , M,\tag{3.73}
$$

where $c _ { m }$ is the mth canonical correlation coefficient. Note that as the ratio of the number of input variables to sample size $p / N$ gets small, the shrinkage factors approach 1. Breiman and Friedman (1997) proposed modified versions of Λ based on training data and cross-validation, but the general form is the same. Here the fitted response has the form 

$$
\hat {\mathbf {Y}} ^ {\mathrm{c} + \mathrm{w}} = \mathbf {H Y S} ^ {\mathrm{c} + \mathrm{w}},\tag{3.74}
$$

where $\mathbf { S } ^ { \mathrm { c + w } } = \mathbf { U } \pmb { \Lambda } \mathbf { U } ^ { - 1 }$ is the response shrinkage operator. 

Breiman and Friedman (1997) also suggested shrinking in both the $Y$ space and X space. This leads to hybrid shrinkage models of the form 

$$
\hat {\mathbf {Y}} ^ {\mathrm{ridge,c+w}} = \mathbf {A} _ {\lambda} \mathbf {Y} \mathbf {S} ^ {\mathrm{c+w}},\tag{3.75}
$$

where $\mathbf { A } _ { \lambda } = \mathbf { X } ( \mathbf { X } ^ { T } \mathbf { X } + \lambda \mathbf { I } ) ^ { - 1 } \mathbf { X } ^ { T }$ is the ridge regression shrinkage operator, as in (3.46) on page 66. Their paper and the discussions thereof contain many more details. 

## 3.8 More on the Lasso and Related Path Algorithms

Since the publication of the LAR algorithm (Efron et al., 2004) there has been a lot of activity in developing algorithms for fitting regularization paths for a variety of different problems. In addition, $L _ { 1 }$ regularization has taken on a life of its own, leading to the development of the field compressed sensing in the signal-processing literature. (Donoho, 2006a; Candes, 2006). In this section we discuss some related proposals and other path algorithms, starting of with a precursor to the LAR algorithm. 

## 3.8.1 Incremental Forward Stagewise Regression

Here we present another LAR-like algorithm, this time focused on forward stagewise regression. Interestingly, efforts to understand a flexible nonlinear regression procedure (boosting) led to a new algorithm for linear models (LAR). In reading the first edition of this book and the forward stagewise 

Algorithm 3.4 Incremental Forward Stagewise Regression— $FS_{\epsilon}$ .
1. Start with the residual r equal to y and $\beta_{1}, \beta_{2}, \ldots, \beta_{p} = 0$ . All the predictors are standardized to have mean zero and unit norm.
2. Find the predictor $x_{j}$ most correlated with r
3. Update $\beta_{j} \leftarrow \beta_{j} + \delta_{j}$ , where $\delta_{j} = \epsilon \cdot \text{sign}[\langle x_{j}, r \rangle]$ and $\epsilon > 0$ is a small step size, and set $r \leftarrow r - \delta_{j} x_{j}$ .
4. Repeat steps 2 and 3 many times, until the residuals are uncorrelated with all the predictors. 

Algorithm 16.1 of Chapter $1 6 ^ { 4 }$ , our colleague Brad Efron realized that with linear models, one could explicitly construct the piecewise-linear lasso paths of Figure 3.10. This led him to propose the LAR procedure of Section 3.4.4, as well as the incremental version of forward-stagewise regression presented here. 


FS<sub>ǫ</sub>


![image](<Images/03_Linear_Methods_for_Regression_image_021.jpg>)


![image](<Images/03_Linear_Methods_for_Regression_image_022.jpg>)



FIGURE 3.19. Coefficient profiles for the prostate data. The left panel shows incremental forward stagewise regression with step size $\epsilon = 0 . 0 1$ . The right panel shows the infinitesimal version $F S _ { 0 }$ obtained letting $\epsilon  0$ . This profile was fit by the modification 3.2b to the LAR Algorithm 3.2. In this example the $F S _ { 0 }$ profiles are monotone, and hence identical to those of lasso and LAR.


Consider the linear-regression version of the forward-stagewise boosting algorithm 16.1 proposed in Section 16.1 (page 608). It generates a coefficient profile by repeatedly updating (by a small amount ǫ) the coefficient of the variable most correlated with the current residuals. Algorithm 3.4 gives the details. Figure 3.19 (left panel) shows the progress of the algorithm on the prostate data with step size $\epsilon = 0 . 0 1$ . If $\delta _ { j } = \langle \mathbf { x } _ { j } , \mathbf { r } \rangle$ (the least-squares coefficient of the residual on jth predictor), then this is exactly the usual forward stagewise procedure (FS) outlined in Section 3.3.3. 

Here we are mainly interested in small values of ǫ. Letting $\epsilon  0$ gives the right panel of Figure 3.19, which in this case is identical to the lasso path in Figure 3.10. We call this limiting procedure infinitesimal forward stagewise regression or $\mathrm { F S _ { 0 } }$ . This procedure plays an important role in non-linear, adaptive methods like boosting (Chapters 10 and 16) and is the version of incremental forward stagewise regression that is most amenable to theoretical analysis. B¨uhlmann and Hothorn (2007) refer to the same procedure as “L2boost”, because of its connections to boosting. 

Efron originally thought that the LAR Algorithm 3.2 was an implementation of $\mathrm { F S _ { 0 } }$ , allowing each tied predictor a chance to update their coefficients in a balanced way, while remaining tied in correlation. However, he then realized that the LAR least-squares fit amongst the tied predictors can result in coefficients moving in the opposite direction to their correlation, which cannot happen in Algorithm 3.4. The following modification of the LAR algorithm implements FS<sub>0</sub>: 

Algorithm 3.2b Least Angle Regression: $FS_0$ Modification.  
4. Find the new direction by solving the constrained least squares problem $\min_{b}||\mathbf{r} - \mathbf{X}_{\mathcal{A}}b||_2^2$ subject to $b_j s_j \geq 0, j \in \mathcal{A}$ , where $s_j$ is the sign of $\langle \mathbf{x}_j, \mathbf{r} \rangle$ . 

The modification amounts to a non-negative least squares fit, keeping the signs of the coefficients the same as those of the correlations. One can show that this achieves the optimal balancing of infinitesimal “update turns” for the variables tied for maximal correlation (Hastie et al., 2007). Like lasso, the entire $\mathrm { F S _ { 0 } }$ path can be computed very efficiently via the LAR algorithm. 

As a consequence of these results, if the LAR profiles are monotone nonincreasing or non-decreasing, as they are in Figure 3.19, then all three methods—LAR, lasso, and $\mathrm { F S _ { 0 } }$ —give identical profiles. If the profiles are not monotone but do not cross the zero axis, then LAR and lasso are identical. 

Since $\mathrm { F S _ { 0 } }$ is different from the lasso, it is natural to ask if it optimizes a criterion. The answer is more complex than for lasso; the $\mathrm { F S _ { 0 } }$ coefficient profile is the solution to a differential equation. While the lasso makes optimal progress in terms of reducing the residual sum-of-squares per unit increase in $L _ { \mathrm { 1 } } \mathrm { - n o r m }$ of the coefficient vector $ { \beta } ,  { \mathrm { \ F S } } _ { 0 }$ is optimal per unit increase in $L _ { 1 }$ arc-length traveled along the coefficient path. Hence its coefficient path is discouraged from changing directions too often. 

$\mathrm { F S _ { 0 } }$ is more constrained than lasso, and in fact can be viewed as a monotone version of the lasso; see Figure 16.3 on page 614 for a dramatic example. $\mathrm { F S _ { 0 } }$ may be useful in $p \gg N$ situations, where its coefficient profiles are much smoother and hence have less variance than those of lasso. More details on $\mathrm { F S _ { 0 } }$ are given in Section 16.2.3 and Hastie et al. (2007). Figure 3.16 includes $\mathrm { F S _ { 0 } }$ where its performance is very similar to that of the lasso. 

## 3.8.2 Piecewise-Linear Path Algorithms

The least angle regression procedure exploits the piecewise linear nature of the lasso solution paths. It has led to similar “path algorithms” for other regularized problems. Suppose we solve 

$$
\hat {\beta} (\lambda) = \mathrm{argmin} _ {\beta} \left[ R (\beta) + \lambda J (\beta) \right],\tag{3.76}
$$

with 

$$
R (\beta) = \sum_ {i = 1} ^ {N} L (y _ {i}, \beta_ {0} + \sum_ {j = 1} ^ {p} x _ {i j} \beta_ {j}),\tag{3.77}
$$

where both the loss function L and the penalty function $J$ are convex. Then the following are sufficient conditions for the solution path $\hat { \beta } ( \lambda )$ to be piecewise linear (Rosset and Zhu, 2007): 

1. R is quadratic or piecewise-quadratic as a function of $\beta _ { i }$ , and 

2. J is piecewise linear in $\beta .$ 

This also implies (in principle) that the solution path can be efficiently computed. Examples include squared- and absolute-error loss, “Huberized” losses, and the $L _ { 1 } , L _ { \infty }$ penalties on $\beta$ . Another example is the “hinge loss” function used in the support vector machine. There the loss is piecewise linear, and the penalty is quadratic. Interestingly, this leads to a piecewiselinear path algorithm in the dual space; more details are given in Section 12.3.5. 

## 3.8.3 The Dantzig Selector

Candes and Tao (2007) proposed the following criterion: 

$$
\min _ {\beta} | | \beta | | _ {1} \text { subject   to } | | \mathbf {X} ^ {T} (\mathbf {y} - \mathbf {X} \beta) | | _ {\infty} \leq s.\tag{3.78}
$$

They call the solution the Dantzig selector (DS). It can be written equivalently as 

$$
\min _ {\beta} | | \mathbf {X} ^ {T} (\mathbf {y} - \mathbf {X} \beta) | | _ {\infty} \text { subject   to } | | \beta | | _ {1} \leq t.\tag{3.79}
$$

Here $| | \cdot | | _ { \infty }$ denotes the $L _ { \infty }$ norm, the maximum absolute value of the components of the vector. In this form it resembles the lasso, replacing squared error loss by the maximum absolute value of its gradient. Note that as t gets large, both procedures yield the least squares solution if $N < p . \mathrm { ~ H ~ } p \geq N$ , they both yield the least squares solution with minimum $L _ { 1 }$ norm. However for smaller values of t, the DS procedure produces a different path of solutions than the lasso. 

Candes and Tao (2007) show that the solution to DS is a linear programming problem; hence the name Dantzig selector, in honor of the late 

George Dantzig, the inventor of the simplex method for linear programming. They also prove a number of interesting mathematical properties for the method, related to its ability to recover an underlying sparse coefficient vector. These same properties also hold for the lasso, as shown later by Bickel et al. (2008). 

Unfortunately the operating properties of the DS method are somewhat unsatisfactory. The method seems similar in spirit to the lasso, especially when we look at the lasso’s stationary conditions (3.58). Like the LAR algorithm, the lasso maintains the same inner product (and correlation) with the current residual for all variables in the active set, and moves their coefficients to optimally decrease the residual sum of squares. In the process, this common correlation is decreased monotonically (Exercise 3.23), and at all times this correlation is larger than that for non-active variables. The Dantzig selector instead tries to minimize the maximum inner product of the current residual with all the predictors. Hence it can achieve a smaller maximum than the lasso, but in the process a curious phenomenon can occur. If the size of the active set is $m$ , there will be m variables tied with maximum correlation. However, these need not coincide with the active set! Hence it can include a variable in the model that has smaller correlation with the current residual than some of the excluded variables (Efron et al., 2007). This seems unreasonable and may be responsible for its sometimes inferior prediction accuracy. Efron et al. (2007) also show that DS can yield extremely erratic coefficient paths as the regularization parameter s is varied. 

## 3.8.4 The Grouped Lasso

In some problems, the predictors belong to pre-defined groups; for example genes that belong to the same biological pathway, or collections of indicator (dummy) variables for representing the levels of a categorical predictor. In this situation it may be desirable to shrink and select the members of a group together. The grouped lasso is one way to achieve this. Suppose that the $p$ predictors are divided into L groups, with $p \ell$ the number in group ℓ. For ease of notation, we use a matrix $\mathbf { X } _ { \ell }$ to represent the predictors corresponding to the ℓth group, with corresponding coefficient vector $\beta _ { \ell }$ The grouped-lasso minimizes the convex criterion 

$$
\min _ {\beta \in \mathbb {R} ^ {p}} \left(| | \mathbf {y} - \beta_ {0} \mathbf {1} - \sum_ {\ell = 1} ^ {L} \mathbf {X} _ {\ell} \beta_ {\ell} | | _ {2} ^ {2} + \lambda \sum_ {\ell = 1} ^ {L} \sqrt {p _ {\ell}} | | \beta_ {\ell} | | _ {2}\right),\tag{3.80}
$$

where the $\sqrt { p _ { \ell } }$ terms accounts for the varying group sizes, and $| | \cdot | | _ { 2 }$ is the Euclidean norm (not squared). Since the Euclidean norm of a vector $\beta _ { \ell }$ is zero only if all of its components are zero, this procedure encourages sparsity at both the group and individual levels. That is, for some values of λ, an entire group of predictors may drop out of the model. This procedure was proposed by Bakin (1999) and Lin and Zhang (2006), and studied and generalized by Yuan and Lin (2007). Generalizations include more general $L _ { 2 }$ norms $| | \boldsymbol { \eta } | | _ { K } = ( \eta ^ { T } K \eta ) ^ { 1 / 2 }$ , as well as allowing overlapping groups of predictors (Zhao et al., 2008). There are also connections to methods for fitting sparse additive models (Lin and Zhang, 2006; Ravikumar et al., 2008). 

## 3.8.5 Further Properties of the Lasso

A number of authors have studied the ability of the lasso and related procedures to recover the correct model, as N and p grow. Examples of this work include Knight and Fu (2000), Greenshtein and Ritov (2004), Tropp (2004), Donoho (2006b), Meinshausen (2007), Meinshausen and B¨uhlmann (2006), Tropp (2006), Zhao and Yu (2006), Wainwright (2006), and Bunea et al. (2007). For example Donoho (2006b) focuses on the $p > N$ case and considers the lasso solution as the bound t gets large. In the limit this gives the solution with minimum $L _ { 1 }$ norm among all models with zero training error. He shows that under certain assumptions on the model matrix X, if the true model is sparse, this solution identifies the correct predictors with high probability. 

Many of the results in this area assume a condition on the model matrix of the form 

$$
\max _ {j \in \mathcal {S} ^ {c}} | | \mathbf {x} _ {j} ^ {T} \mathbf {X} _ {\mathcal {S}} (\mathbf {X} _ {\mathcal {S}} ^ {T} \mathbf {X} _ {\mathcal {S}}) ^ {- 1} | | _ {1} \leq (1 - \epsilon) \text {   for   some   } \epsilon \in (0, 1 ].\tag{3.81}
$$

Here indexes the subset of features with non-zero coefficients in the true underlying model, and $\mathbf { X } _ { \mathcal { S } }$ are the columns of X corresponding to those features. Similarly $S ^ { c }$ are the features with true coefficients equal to zero, and $\mathbf { X } _ { \mathcal { S } ^ { c } }$ the corresponding columns. This says that the least squares coefficients for the columns of $\mathbf { X } _ { \mathcal { S } ^ { c } }$ on $\mathbf { X } _ { \mathcal { S } }$ are not too large, that is, the “good” variables are not too highly correlated with the nuisance variables $S ^ { c }$ 

Regarding the coefficients themselves, the lasso shrinkage causes the estimates of the non-zero coefficients to be biased towards zero, and in general they are not consistent<sup>5</sup>. One approach for reducing this bias is to run the lasso to identify the set of non-zero coefficients, and then fit an unrestricted linear model to the selected set of features. This is not always feasible, if the selected set is large. Alternatively, one can use the lasso to select the set of non-zero predictors, and then apply the lasso again, but using only the selected predictors from the first step. This is known as the relaxed lasso (Meinshausen, 2007). The idea is to use cross-validation to estimate the initial penalty parameter for the lasso, and then again for a second penalty parameter applied to the selected set of predictors. Since the variables in the second step have less “competition” from noise variables, cross-validation will tend to pick a smaller value for λ, and hence their coefficients will be shrunken less than those in the initial estimate. 

Alternatively, one can modify the lasso penalty function so that larger coefficients are shrunken less severely; the smoothly clipped absolute deviation (SCAD) penalty of Fan and Li (2005) replaces $\lambda | \beta |$ by $J _ { a } ( \beta , \lambda )$ , where 

$$
\frac {d J _ {a} (\beta , \lambda)}{d \beta} = \lambda \cdot \mathrm{sign} (\beta) \Big [ I (| \beta | \leq \lambda) + \frac {(a \lambda - | \beta |) _ {+}}{(a - 1) \lambda} I (| \beta | > \lambda) \Big ]\tag{3.82}
$$

for some $a \ge 2$ . The second term in square-braces reduces the amount of shrinkage in the lasso for larger values of $\beta _ { i }$ , with ultimately no shrinkage as $a  \infty$ . Figure 3.20 shows the SCAD penalty, along with the lasso and 

![image](<Images/03_Linear_Methods_for_Regression_image_023.jpg>)


![image](<Images/03_Linear_Methods_for_Regression_image_024.jpg>)


![image](<Images/03_Linear_Methods_for_Regression_image_025.jpg>)



FIGURE 3.20. The lasso and two alternative non-convex penalties designed to penalize large coefficients less. For SCAD we use $\lambda = 1$ and $a = 4$ , and $\textstyle \nu = { \frac { 1 } { 2 } }$ in the last panel.


$| \beta | ^ { 1 - \nu }$ . However this criterion is non-convex, which is a drawback since it makes the computation much more difficult. The adaptive lasso (Zou, 2006) uses a weighted penalty of the form $\textstyle \sum _ { j = 1 } ^ { p } w _ { j } | \beta _ { j } |$ where $w _ { j } = 1 / | \hat { \beta } _ { j } | ^ { \nu } , \hat { \beta } _ { j }$ is the ordinary least squares estimate and $\nu > 0$ . This is a practical approximation to the $| \beta | ^ { q }$ penalties $( q = 1 - \nu$ here) discussed in Section 3.4.3. The adaptive lasso yields consistent estimates of the parameters while retaining the attractive convexity property of the lasso. 

## 3.8.6 Pathwise Coordinate Optimization

An alternate approach to the LARS algorithm for computing the lasso solution is simple coordinate descent. This idea was proposed by Fu (1998) and Daubechies et al. (2004), and later studied and generalized by Friedman et al. (2007), Wu and Lange (2008) and others. The idea is to fix the penalty parameter λ in the Lagrangian form (3.52) and optimize successively over each parameter, holding the other parameters fixed at their current values. 

Suppose the predictors are all standardized to have mean zero and unit norm. Denote by $\tilde { \beta } _ { k } ( \lambda )$ the current estimate for $\beta _ { k }$ at penalty parameter λ. We can rearrange (3.52) to isolate $\beta _ { j }$ 

$$
R (\tilde {\beta} (\lambda), \beta_ {j}) = \frac {1}{2} \sum_ {i = 1} ^ {N} \left(y _ {i} - \sum_ {k \neq j} x _ {i k} \tilde {\beta} _ {k} (\lambda) - x _ {i j} \beta_ {j}\right) ^ {2} + \lambda \sum_ {k \neq j} | \tilde {\beta} _ {k} (\lambda) | + \lambda | \beta_ {j} |,\tag{3.83}
$$

where we have suppressed the intercept and introduced a factor $\frac { 1 } { 2 }$ for convenience. This can be viewed as a univariate lasso problem with response variable the partial residual $\begin{array} { r } { y _ { i } - \tilde { y } _ { i } ^ { ( j ) } = y _ { i } - \sum _ { k \neq j } x _ { i k } \tilde { \beta } _ { k } ( \lambda ) } \end{array}$ . This has an explicit solution, resulting in the update 

$$
\tilde {\beta} _ {j} (\lambda) \leftarrow S \left(\sum_ {i = 1} ^ {N} x _ {i j} (y _ {i} - \tilde {y} _ {i} ^ {(j)}), \lambda\right).\tag{3.84}
$$

Here $S ( t , \lambda ) = \mathrm { s i g n } ( t ) ( | t | - \lambda ) _ { + }$ is the soft-thresholding operator in Table 3.4 on page 71. The first argument to $S ( \cdot )$ is the simple least-squares coefficient of the partial residual on the standardized variable $\boldsymbol { x } _ { i j }$ . Repeated iteration of (3.84)—cycling through each variable in turn until convergence—yields the lasso estimate $\hat { \beta } ( \lambda )$ 

We can also use this simple algorithm to efficiently compute the lasso solutions at a grid of values of λ. We start with the smallest value $\lambda _ { \mathrm { m a x } }$ for which $\hat { \beta } ( \lambda _ { \mathrm { m a x } } ) = 0$ , decrease it a little and cycle through the variables until convergence. Then λ is decreased again and the process is repeated, using the previous solution as a “warm start” for the new value of λ. This can be faster than the LARS algorithm, especially in large problems. A key to its speed is the fact that the quantities in (3.84) can be updated quickly as $j$ varies, and often the update is to leave $\tilde { \beta } _ { j } = 0$ . On the other hand, it delivers solutions over a grid of λ values, rather than the entire solution path. The same kind of algorithm can be applied to the elastic net, the grouped lasso and many other models in which the penalty is a sum of functions of the individual parameters (Friedman et al., 2010). It can also be applied, with some substantial modifications, to the fused lasso (Section 18.4.2); details are in Friedman et al. (2007). 

## 3.9 Computational Considerations

Least squares fitting is usually done via the Cholesky decomposition of the matrix $\mathbf { X } ^ { T } \mathbf { X }$ or a QR decomposition of X. With N observations and p features, the Cholesky decomposition requires $p ^ { 3 } + N p ^ { 2 } / 2$ operations, while the QR decomposition requires $N p ^ { 2 }$ operations. Depending on the relative size of N and $p ,$ the Cholesky can sometimes be faster; on the other hand, it can be less numerically stable (Lawson and Hansen, 1974). Computation of the lasso via the LAR algorithm has the same order of computation as a least squares fit. 

## 3. Linear Methods for Regression

## Bibliographic Notes

Linear regression is discussed in many statistics books, for example, Seber (1984), Weisberg (1980) and Mardia et al. (1979). Ridge regression was introduced by Hoerl and Kennard (1970), while the lasso was proposed by Tibshirani (1996). Around the same time, lasso-type penalties were proposed in the basis pursuit method for signal processing (Chen et al., 1998). The least angle regression procedure was proposed in Efron et al. (2004); related to this is the earlier homotopy procedure of Osborne et al. (2000a) and Osborne et al. (2000b). Their algorithm also exploits the piecewise linearity used in the LAR/lasso algorithm, but lacks its transparency. The criterion for the forward stagewise criterion is discussed in Hastie et al. (2007). Park and Hastie (2007) develop a path algorithm similar to least angle regression for generalized regression models. Partial least squares was introduced by Wold (1975). Comparisons of shrinkage methods may be found in Copas (1983) and Frank and Friedman (1993). 

## Exercises

Ex. 3.1 Show that the $F$ statistic (3.13) for dropping a single coefficient from a model is equal to the square of the corresponding z-score (3.12). 

Ex. 3.2 Given data on two variables $X$ and $Y$ , consider fitting a cubic polynomial regression model $\textstyle f ( X ) = \sum _ { j = 0 } ^ { 3 } \beta _ { j } X ^ { j }$ . In addition to plotting the fitted curve, you would like a 95% confidence band about the curve. Consider the following two approaches: 

1. At each point $x _ { 0 }$ , form a 95% confidence interval for the linear function $\begin{array} { r } { \ r { a ^ { T } \hat { \beta } } = \sum _ { j = 0 } ^ { 3 } \beta _ { j } x _ { 0 } ^ { j } } \end{array}$ 

2. Form a 95% confidence set for $\beta$ as in (3.15), which in turn generates confidence intervals for $f ( x _ { 0 } )$ 

How do these approaches differ? Which band is likely to be wider? Conduct a small simulation experiment to compare the two methods. 

## Ex. 3.3 Gauss–Markov theorem:

(a) Prove the Gauss–Markov theorem: the least squares estimate of a parameter $a ^ { T } \beta$ has variance no bigger than that of any other linear unbiased estimate of $a ^ { T } \beta$ (Section 3.2.2). 

(b) The matrix inequality $\mathbf { B } \preceq \mathbf { A }$ holds if A B is positive semidefinite. Show that if $\hat { \mathbf { V } }$ is the variance-covariance matrix of the least squares estimate of $\beta$ and $\tilde { \mathbf { V } }$ is the variance-covariance matrix of any other linear unbiased estimate, then $\hat { \mathbf { V } } \preceq \tilde { \mathbf { V } }$ 

Ex. 3.4 Show how the vector of least squares coefficients can be obtained from a single pass of the Gram–Schmidt procedure (Algorithm 3.1). Represent your solution in terms of the QR decomposition of X. 

Ex. 3.5 Consider the ridge regression problem (3.41). Show that this problem is equivalent to the problem 

$$
\hat {\beta} ^ {c} = \underset {\beta^ {c}} {\operatorname{argmin}} \Biggl \{\sum_ {i = 1} ^ {N} \bigl [ y _ {i} - \beta_ {0} ^ {c} - \sum_ {j = 1} ^ {p} (x _ {i j} - \bar {x} _ {j}) \beta_ {j} ^ {c} \bigr ] ^ {2} + \lambda \sum_ {j = 1} ^ {p} \beta_ {j} ^ {c 2} \Biggr \}.\tag{3.85}
$$

Give the correspondence between $\beta ^ { c }$ and the original $\beta$ in (3.41). Characterize the solution to this modified criterion. Show that a similar result holds for the lasso. 

Ex. 3.6 Show that the ridge regression estimate is the mean (and mode) of the posterior distribution, under a Gaussian prior $\boldsymbol \beta \sim N ( 0 , \tau \mathbf { I } )$ , and Gaussian sampling model $\mathbf { y } \sim N ( \mathbf { X } { \boldsymbol { \beta } } , \sigma ^ { 2 } \mathbf { I } ) $ . Find the relationship between the regularization parameter λ in the ridge formula, and the variances $\tau$ and $\sigma ^ { 2 }$ 

Ex. 3.7 Assume $y _ { i } \sim N ( \beta _ { 0 } + x _ { i } ^ { T } \beta , \sigma ^ { 2 } ) , i = 1 , 2 , \dots , N$ , and the parameters $\beta _ { j } , ~ j ~ = ~ 1 , \ldots , p$ are each distributed as $N ( 0 , \tau ^ { 2 } )$ , independently of one another. Assuming $\sigma ^ { 2 }$ and $\tau ^ { 2 }$ are known, and $\beta _ { 0 }$ is not governed by a prior (or has a flat improper prior), show that the (minus) log-posterior density of $\beta$ is proportional to $\begin{array} { r } { \sum _ { i = 1 } ^ { N } ( y _ { i } - \beta _ { 0 } - \sum _ { j } x _ { i j } \beta _ { j } ) ^ { 2 } + \lambda \sum _ { j = 1 } ^ { p } \beta _ { j } ^ { 2 } } \end{array}$ where $\lambda = \sigma ^ { 2 } / \tau ^ { 2 }$ 

Ex. 3.8 Consider the QR decomposition of the uncentered $N \times ( p + 1 )$ matrix X (whose first column is all ones), and the SVD of the $N \times p$ centered matrix $\tilde { \mathbf { X } }$ . Show that $\mathbf { Q } _ { 2 }$ and U span the same subspace, where $\mathbf { Q } _ { 2 }$ is the sub-matrix of $\mathbf { Q }$ with the first column removed. Under what circumstances will they be the same, up to sign flips? 

Ex. 3.9 Forward stepwise regression. Suppose we have the QR decomposition for the $N \times q$ matrix $\mathbf { X } _ { 1 }$ in a multiple regression problem with response $\mathbf { y } ,$ and we have an additional $p - q$ predictors in the matrix $\mathbf { X } _ { 2 }$ . Denote the current residual by r. We wish to establish which one of these additional variables will reduce the residual-sum-of squares the most when included with those in $\mathbf { X } _ { 1 }$ . Describe an efficient procedure for doing this. 

Ex. 3.10 Backward stepwise regression. Suppose we have the multiple regression fit of y on $\mathbf { X } ,$ along with the standard errors and Z-scores as in Table 3.2. We wish to establish which variable, when dropped, will increase the residual sum-of-squares the least. How would you do this? 

Ex. 3.11 Show that the solution to the multivariate linear regression problem (3.40) is given by (3.39). What happens if the covariance matrices $\Sigma _ { i }$ are different for each observation? 

Ex. 3.12 Show that the ridge regression estimates can be obtained by ordinary least squares regression on an augmented data set. We augment the centered matrix X with $p$ additional rows $\sqrt { \lambda } \mathbf { I }$ , and augment y with $p$ zeros. By introducing artificial data having response value zero, the fitting procedure is forced to shrink the coefficients toward zero. This is related to the idea of hints due to Abu-Mostafa (1995), where model constraints are implemented by adding artificial data examples that satisfy them. 

Ex. 3.13 Derive the expression (3.62), and show that $\hat { \beta } ^ { \mathrm { p c r } } ( p ) = \hat { \beta } ^ { \mathrm { l s } }$ 

Ex. 3.14 Show that in the orthogonal case, PLS stops after $m = 1$ steps, because subsequent $\hat { \varphi } _ { m j }$ in step 2 in Algorithm 3.3 are zero. 

Ex. 3.15 Verify expression (3.64), and hence show that the partial least squares directions are a compromise between the ordinary regression coefficient and the principal component directions. 

Ex. 3.16 Derive the entries in Table 3.4, the explicit forms for estimators in the orthogonal case. 

Ex. 3.17 Repeat the analysis of Table 3.3 on the spam data discussed in Chapter 1. 

Ex. 3.18 Read about conjugate gradient algorithms (Murray et al., 1981, for example), and establish a connection between these algorithms and partial least squares. 

Ex. 3.19 Show that $\| \hat { \beta } ^ { \mathrm { { r i d g e } } } \|$ increases as its tuning parameter $\lambda  0$ . Does the same property hold for the lasso and partial least squares estimates? For the latter, consider the “tuning parameter” to be the successive steps in the algorithm. 

Ex. 3.20 Consider the canonical-correlation problem (3.67). Show that the leading pair of canonical variates $u _ { 1 }$ and $v _ { 1 }$ solve the problem 

$$
\max_{\substack{u^{T}(\mathbf{Y}^{T}\mathbf{Y})u = 1\\ v_{T}(\mathbf{X}^{T}\mathbf{X})v = 1}}u^{T}(\mathbf{Y}^{T}\mathbf{X})v,\tag{3.86}
$$

a generalized SVD problem. Show that the solution is given by $u _ { 1 } =$ $( \mathbf { \bar { Y } } ^ { T } \mathbf { Y } ) ^ { - \frac { 1 } { 2 } } u _ { 1 } ^ { * }$ , and $v _ { 1 } = ( \mathbf { X } ^ { T } \mathbf { X } ) ^ { - \frac { 1 } { 2 } } v _ { 1 } ^ { * }$ , where $u _ { 1 } ^ { * }$ and $v _ { 1 } ^ { * }$ are the leading left and right singular vectors in 

$$
(\mathbf {Y} ^ {T} \mathbf {Y}) ^ {- \frac {1}{2}} (\mathbf {Y} ^ {T} \mathbf {X}) (\mathbf {X} ^ {T} \mathbf {X}) ^ {- \frac {1}{2}} = \mathbf {U} ^ {*} \mathbf {D} ^ {*} \mathbf {V} ^ {* T}.\tag{3.87}
$$

Show that the entire sequence $u _ { m } , v _ { m } , m = 1 , \ldots , \operatorname* { m i n } ( K , p )$ is also given by (3.87). 

Ex. 3.21 Show that the solution to the reduced-rank regression problem (3.68), with Σ estimated by $\mathbf { Y } ^ { T } \mathbf { Y } / N$ , is given by (3.69). Hint: Transform 

Y to $\mathbf { Y } ^ { * } = \mathbf { Y } \mathbf { \Sigma } ^ { - \frac { 1 } { 2 } }$ , and solved in terms of the canonical vectors $\boldsymbol { u } _ { m } ^ { * }$ . Show that $\mathbf { U } _ { m } = \pmb { \Sigma } ^ { - \frac { 1 } { 2 } } \mathbf { U } _ { m } ^ { * }$ , and a generalized inverse is $\mathbf { U } _ { m } ^ { - } = \mathbf { U } _ { m } ^ { * } { } ^ { T } \pmb { \Sigma } ^ { \frac { 1 } { 2 } }$ 

Ex. 3.22 Show that the solution in Exercise 3.21 does not change if Σ is estimated by the more natural quantity $( \mathbf { Y } - \mathbf { X } \hat { \mathbf { B } } ) ^ { T } ( \mathbf { Y } - \mathbf { X } \hat { \mathbf { B } } ) / ( \tilde { N } - p K )$ 

Ex. 3.23 Consider a regression problem with all variables and response having mean zero and standard deviation one. Suppose also that each variable has identical absolute correlation with the response: 

$$
\frac {1}{N} | \langle \mathbf {x} _ {j}, \mathbf {y} \rangle | = \lambda , j = 1, \ldots , p.
$$

Let $\hat { \beta }$ be the least-squares coefficient of y on X, and let $\mathbf { u } ( \alpha ) = \alpha \mathbf { X } { \hat { \boldsymbol { \beta } } } $ for $\alpha \in [ 0 , 1 ]$ be the vector that moves a fraction α toward the least squares fit u. Let RSS be the residual sum-of-squares from the full least squares fit. 

(a) Show that 

$$
\frac {1}{N} | \langle \mathbf {x} _ {j}, \mathbf {y} - \mathbf {u} (\alpha) \rangle | = (1 - \alpha) \lambda , j = 1, \ldots , p,
$$

and hence the correlations of each $\mathbf { x } _ { j }$ with the residuals remain equal in magnitude as we progress toward u. 

(b) Show that these correlations are all equal to 

$$
\lambda (\alpha) = \frac {(1 - \alpha)}{\sqrt {(1 - \alpha) ^ {2} + \frac {\alpha (2 - \alpha)}{N} \cdot R S S}} \cdot \lambda ,
$$

and hence they decrease monotonically to zero. 

(c) Use these results to show that the LAR algorithm in Section 3.4.4 keeps the correlations tied and monotonically decreasing, as claimed in (3.55). 

Ex. 3.24 LAR directions. Using the notation around equation (3.55) on page 74, show that the LAR direction makes an equal angle with each of the predictors in $\mathcal { A } _ { k }$ 

Ex. 3.25 LAR look-ahead (Efron et al., 2004, Sec. 2). Starting at the beginning of the kth step of the LAR algorithm, derive expressions to identify the next variable to enter the active set at step k + 1, and the value of α at which this occurs (using the notation around equation (3.55) on page 74). 

Ex. 3.26 Forward stepwise regression enters the variable at each step that most reduces the residual sum-of-squares. LAR adjusts variables that have the most (absolute) correlation with the current residuals. Show that these two entry criteria are not necessarily the same. [Hint: let $\mathbf { x } _ { j \ldots A }$ be the jth variable, linearly adjusted for all the variables currently in the model. Show that the first criterion amounts to identifying the $j$ for which Cor $( \mathbf { x } _ { j . \mathcal { A } } , \mathbf { r } )$ is largest in magnitude. 

Ex. 3.27 Lasso and LAR: Consider the lasso problem in Lagrange multiplier form: with $\begin{array} { r } { L ( \beta ) = \frac 1 2 \sum _ { i } ( y _ { i } - \sum _ { j } x _ { i j } \beta _ { j } ) ^ { 2 } } \end{array}$ , we minimize 

$$
L (\beta) + \lambda \sum_ {j} | \beta_ {j} |\tag{3.88}
$$

for fixed $\lambda > 0$ 

(a) Setting $\beta _ { j } = \beta _ { j } ^ { + } - \beta _ { j } ^ { - }$ with $\beta _ { j } ^ { + } , \beta _ { j } ^ { - } \ \geq 0$ , expression (3.88) becomes $\begin{array} { r } { L ( \beta ) + \lambda \sum _ { j } ( \bar { \beta _ { j } ^ { + } } + \bar { \beta _ { j } ^ { - } } ) } \end{array}$ . Show that the Lagrange dual function is 

$$
L (\beta) + \lambda \sum_ {j} (\beta_ {j} ^ {+} + \beta_ {j} ^ {-}) - \sum_ {j} \lambda_ {j} ^ {+} \beta_ {j} ^ {+} - \sum_ {j} \lambda_ {j} ^ {-} \beta_ {j} ^ {-}\tag{3.89}
$$

and the Karush–Kuhn–Tucker optimality conditions are 

$$
\begin{array}{r c l} \nabla L (\beta) _ {j} + \lambda - \lambda_ {j} ^ {+} & = & 0 \\ - \nabla L (\beta) _ {j} + \lambda - \lambda_ {j} ^ {-} & = & 0 \\ \lambda_ {j} ^ {+} \beta_ {j} ^ {+} & = & 0 \\ \lambda_ {j} ^ {-} \beta_ {j} ^ {-} & = & 0, \end{array}
$$

along with the non-negativity constraints on the parameters and all the Lagrange multipliers. 

(b) Show that $| \nabla L ( \beta ) _ { j } | \le \lambda \forall j$ , and that the KKT conditions imply one of the following three scenarios: 

$$
\begin{array}{r c l} \lambda = 0 & \Rightarrow & \nabla L (\beta) _ {j} = 0   \forall j \\ \beta_ {j} ^ {+} > 0,   \lambda > 0 & \Rightarrow & \lambda_ {j} ^ {+} = 0,   \nabla L (\beta) _ {j} = - \lambda <   0,   \beta_ {j} ^ {-} = 0 \\ \beta_ {j} ^ {-} > 0,   \lambda > 0 & \Rightarrow & \lambda_ {j} ^ {-} = 0,   \nabla L (\beta) _ {j} = \lambda > 0,   \beta_ {j} ^ {+} = 0. \end{array}
$$

Hence show that for any “active” predictor having $\beta _ { j } \neq 0$ , we must have $L ( \beta ) _ { j } = - \lambda$ if $\beta _ { j } > 0$ , and $\nabla L ( \beta ) _ { j } = \lambda$ if $\beta _ { j } < 0$ . Assuming the predictors are standardized, relate λ to the correlation between the jth predictor and the current residuals. 

(c) Suppose that the set of active predictors is unchanged for $\lambda _ { 0 } \geq \lambda \geq \lambda _ { 1 }$ Show that there is a vector $\gamma _ { 0 }$ such that 

$$
\hat {\beta} (\lambda) = \hat {\beta} (\lambda_ {0}) - (\lambda - \lambda_ {0}) \gamma_ {0}\tag{3.90}
$$

Thus the lasso solution path is linear as $\lambda$ ranges from $\lambda _ { 0 }$ to $\lambda _ { 1 }$ (Efron et al., 2004; Rosset and Zhu, 2007). 

Ex. 3.28 Suppose for a given t in (3.51), the fitted lasso coefficient for variable $X _ { j }$ is ${ \hat { \beta } } _ { j } = a$ . Suppose we augment our set of variables with an identical copy $X _ { j } ^ { * } = X _ { j }$ . Characterize the effect of this exact collinearity by describing the set of solutions for $\hat { \beta } _ { j }$ and $\hat { \beta } _ { j } ^ { * }$ , using the same value of t. 

Ex. 3.29 Suppose we run a ridge regression with parameter λ on a single variable $X$ , and get coefficient a. We now include an exact copy $X ^ { * } = X$ and refit our ridge regression. Show that both coefficients are identical, and derive their value. Show in general that if m copies of a variable $X _ { j }$ are included in a ridge regression, their coefficients are all the same. 

Ex. 3.30 Consider the elastic-net optimization problem: 

$$
\min _ {\beta} | | \mathbf {y} - \mathbf {X} \beta | | ^ {2} + \lambda \big [ \alpha | | \beta | | _ {2} ^ {2} + (1 - \alpha) | | \beta | | _ {1} \big ].\tag{3.91}
$$

Show how one can turn this into a lasso problem, using an augmented version of X and $\mathbf { y }$ . 