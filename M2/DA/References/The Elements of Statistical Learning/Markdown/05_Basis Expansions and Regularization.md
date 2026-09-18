Basis Expansions and Regularization 

## 5.1 Introduction

We have already made use of models linear in the input features, both for regression and classification. Linear regression, linear discriminant analysis, logistic regression and separating hyperplanes all rely on a linear model. It is extremely unlikely that the true function $f ( X )$ is actually linear in $X$ . In regression problems, $f ( X ) = \operatorname { E } ( Y | X )$ will typically be nonlinear and nonadditive in $X$ , and representing $f ( X )$ by a linear model is usually a convenient, and sometimes a necessary, approximation. Convenient because a linear model is easy to interpret, and is the first-order Taylor approximation to $f ( X )$ . Sometimes necessary, because with N small and/or $p$ large, a linear model might be all we are able to fit to the data without overfitting. Likewise in classification, a linear, Bayes-optimal decision boundary implies that some monotone transformation of $\operatorname* { P r } ( Y = 1 | X )$ is linear in X. This is inevitably an approximation. 

In this chapter and the next we discuss popular methods for moving beyond linearity. The core idea in this chapter is to augment/replace the vector of inputs X with additional variables, which are transformations of $X$ , and then use linear models in this new space of derived input features. Denote by $h _ { m } ( X ) \ : \ \mathbb { R } ^ { p } \ \mapsto \ \mathbb { R }$ the mth transformation of X, $m =$ $1 , \ldots , M$ . We then model 

$$
f (X) = \sum_ {m = 1} ^ {M} \beta_ {m} h _ {m} (X),\tag{5.1}
$$

a linear basis expansion in X. The beauty of this approach is that once the basis functions $h _ { m }$ have been determined, the models are linear in these new variables, and the fitting proceeds as before. 

Some simple and widely used examples of the $h _ { m }$ are the following: 

$h _ { m } ( X ) = X _ { m } , m = 1 , \ldots , p$ recovers the original linear model. 

$h _ { m } ( X ) = X _ { j } ^ { 2 } \mathrm { o r } h _ { m } ( X ) = X _ { j } X _ { k }$ allows us to augment the inputs with polynomial terms to achieve higher-order Taylor expansions. Note, however, that the number of variables grows exponentially in the degree of the polynomial. A full quadratic model in $p$ variables requires $O ( p ^ { 2 } )$ square and cross-product terms, or more generally $O ( p ^ { d } )$ for a degree-d polynomial. 

$h _ { m } ( X ) = \log ( X _ { j } ) , \sqrt { X _ { j } } , . .$ . permits other nonlinear transformations of single inputs. More generally one can use similar functions involving several inputs, such as $h _ { m } ( X ) = | | X | |$ 

$h _ { m } ( X ) \ : = \ : I ( L _ { m } \leq X _ { k } < U _ { m } )$ , an indicator for a region of $X _ { k }$ . By breaking the range of $X _ { k }$ up into $M _ { k }$ such nonoverlapping regions results in a model with a piecewise constant contribution for $X _ { k }$ 

Sometimes the problem at hand will call for particular basis functions $h _ { m }$ such as logarithms or power functions. More often, however, we use the basis expansions as a device to achieve more flexible representations for $f ( X )$ Polynomials are an example of the latter, although they are limited by their global nature—tweaking the coefficients to achieve a functional form in one region can cause the function to flap about madly in remote regions. In this chapter we consider more useful families of piecewise-polynomials and splines that allow for local polynomial representations. We also discuss the wavelet bases, especially useful for modeling signals and images. These methods produce a dictionary $\mathcal { D }$ consisting of typically a very large number $| \mathcal D |$ of basis functions, far more than we can afford to fit to our data. Along with the dictionary we require a method for controlling the complexity of our model, using basis functions from the dictionary. There are three common approaches: 

Restriction methods, where we decide before-hand to limit the class of functions. Additivity is an example, where we assume that our model has the form 

$$
\begin{array}{r c l} f (X) & = & \sum_ {j = 1} ^ {p} f _ {j} (X _ {j}) \\ & = & \sum_ {j = 1} ^ {p} \sum_ {m = 1} ^ {M _ {j}} \beta_ {j m} h _ {j m} (X _ {j}). \end{array}\tag{5.2}
$$

The size of the model is limited by the number of basis functions $M _ { j }$ used for each component function $f _ { j }$ 

Selection methods, which adaptively scan the dictionary and include only those basis functions $h _ { m }$ that contribute significantly to the fit of the model. Here the variable selection techniques discussed in Chapter 3 are useful. The stagewise greedy approaches such as CART, MARS and boosting fall into this category as well. 

Regularization methods where we use the entire dictionary but restrict the coefficients. Ridge regression is a simple example of a regularization approach, while the lasso is both a regularization and selection method. Here we discuss these and more sophisticated methods for regularization. 

## 5.2 Piecewise Polynomials and Splines

We assume until Section 5.7 that X is one-dimensional. A piecewise polynomial function f(X) is obtained by dividing the domain of X into contiguous intervals, and representing f by a separate polynomial in each interval. Figure 5.1 shows two simple piecewise polynomials. The first is piecewise constant, with three basis functions: 

$$
h _ {1} (X) = I (X <   \xi_ {1}), \quad h _ {2} (X) = I (\xi_ {1} \leq X <   \xi_ {2}), \quad h _ {3} (X) = I (\xi_ {2} \leq X).
$$

Since these are positive over disjoint regions, the least squares estimate of the model $\begin{array} { r } { f ( X ) = \sum _ { m = 1 } ^ { 3 } \beta _ { m } h _ { m } ( X ) } \end{array}$ amounts to $\hat { \beta } _ { m } = \bar { Y } _ { m }$ , the mean of Y in the mth region. 

The top right panel shows a piecewise linear fit. Three additional basis functions are needed: $h _ { m + 3 } = h _ { m } ( X ) X , \ m = 1 , \ldots , 3$ . Except in special cases, we would typically prefer the third panel, which is also piecewise linear, but restricted to be continuous at the two knots. These continuity restrictions lead to linear constraints on the parameters; for example, $f ( \xi _ { 1 } ^ { - } ) = f ( \xi _ { 1 } ^ { + } )$ implies that $\beta _ { 1 } + \xi _ { 1 } \beta _ { 4 } = \beta _ { 2 } + \xi _ { 1 } \beta _ { 5 }$ . In this case, since there are two restrictions, we expect to get back two parameters, leaving four free parameters. 

A more direct way to proceed in this case is to use a basis that incorporates the constraints: 

$$
h _ {1} (X) = 1, \quad h _ {2} (X) = X, \quad h _ {3} (X) = (X - \xi_ {1}) _ {+}, \quad h _ {4} (X) = (X - \xi_ {2}) _ {+},
$$

where $t _ { + }$ denotes the positive part. The function $h _ { 3 }$ is shown in the lower right panel of Figure 5.1. We often prefer smoother functions, and these can be achieved by increasing the order of the local polynomial. Figure 5.2 shows a series of piecewise-cubic polynomials fit to the same data, with 


Piecewise Constant


![image](<Images/05_Basis_Expansions_and_Regularization_image_001.jpg>)



Piecewise Linear


![image](<Images/05_Basis_Expansions_and_Regularization_image_002.jpg>)



Continuous Piecewise Linear



Piecewise-linear Basis Function


![image](<Images/05_Basis_Expansions_and_Regularization_image_003.jpg>)


![image](<Images/05_Basis_Expansions_and_Regularization_image_004.jpg>)



FIGURE 5.1. The top left panel shows a piecewise constant function fit to some artificial data. The broken vertical lines indicate the positions of the two knots $\xi _ { 1 }$ and $\xi _ { 2 }$ . The blue curve represents the true function, from which the data were generated with Gaussian noise. The remaining two panels show piecewise linear functions fit to the same data—the top right unrestricted, and the lower left restricted to be continuous at the knots. The lower right panel shows a piecewise– linear basis function, $h _ { 3 } ( X ) = ( X - \xi _ { 1 } ) _ { + }$ , continuous at $\xi _ { 1 }$ . The black points indicate the sample evaluations $h _ { 3 } ( x _ { i } ) , \ i = 1 , . . . , N$


## Piecewise Cubic Polynomials

![image](<Images/05_Basis_Expansions_and_Regularization_image_005.jpg>)


![image](<Images/05_Basis_Expansions_and_Regularization_image_006.jpg>)



Continuous First Derivative


![image](<Images/05_Basis_Expansions_and_Regularization_image_007.jpg>)



Continuous Second Derivative


![image](<Images/05_Basis_Expansions_and_Regularization_image_008.jpg>)



FIGURE 5.2. A series of piecewise-cubic polynomials, with increasing orders of continuity.


increasing orders of continuity at the knots. The function in the lower right panel is continuous, and has continuous first and second derivatives at the knots. It is known as a cubic spline. Enforcing one more order of continuity would lead to a global cubic polynomial. It is not hard to show (Exercise 5.1) that the following basis represents a cubic spline with knots at $\xi _ { 1 }$ and $\xi _ { 2 }$ : 

$$
\begin{array}{l l l} h _ {1} (X) = 1, & h _ {3} (X) = X ^ {2}, & h _ {5} (X) = (X - \xi_ {1}) _ {+} ^ {3}, \\ h _ {2} (X) = X, & h _ {4} (X) = X ^ {3}, & h _ {6} (X) = (X - \xi_ {2}) _ {+} ^ {3}. \end{array}\tag{5.3}
$$

There are six basis functions corresponding to a six-dimensional linear space of functions. A quick check confirms the parameter count: (3 regions) (4 parameters per $\mathrm { r e g i o n ) \ - ( 2 \ k n o t s ) { \times } ( 3 }$ constraints per knot)= 6. 

More generally, an order-M spline with knots $\xi _ { j } , ~ j ~ = ~ 1 , \ldots , K$ is a piecewise-polynomial of order M, and has continuous derivatives up to order $M - 2$ . A cubic spline has $M = 4$ . In fact the piecewise-constant function in Figure 5.1 is an order-1 spline, while the continuous piecewise linear function is an order-2 spline. Likewise the general form for the truncated-power basis set would be 

$$
\begin{array}{r c l} {h _ {j} (X)} & = & {X ^ {j - 1}, j = 1, \ldots , M,} \\ {h _ {M + \ell} (X)} & = & {(X - \xi_ {\ell}) _ {+} ^ {M - 1}, \ell = 1, \ldots , K.} \end{array}
$$

It is claimed that cubic splines are the lowest-order spline for which the knot-discontinuity is not visible to the human eye. There is seldom any good reason to go beyond cubic-splines, unless one is interested in smooth derivatives. In practice the most widely used orders are M = 1, 2 and 4. 

These fixed-knot splines are also known as regression splines. One needs to select the order of the spline, the number of knots and their placement. One simple approach is to parameterize a family of splines by the number of basis functions or degrees of freedom, and have the observations $x _ { i }$ determine the positions of the knots. For example, the expression bs $( \mathbf { x } , \mathsf { d f } = 7 )$ in R generates a basis matrix of cubic-spline functions evaluated at the N observations in x, with the $7 - 3 = 4 ^ { 1 }$ interior knots at the appropriate percentiles of x (20, 40, 60 and 80th.) One can be more explicit, however; bs(x, degree=1, knots = c(0.2, 0.4, 0.6)) generates a basis for linear splines, with three interior knots, and returns an $N \times 4$ matrix. 

Since the space of spline functions of a particular order and knot sequence is a vector space, there are many equivalent bases for representing them (just as there are for ordinary polynomials.) While the truncated power basis is conceptually simple, it is not too attractive numerically: powers of large numbers can lead to severe rounding problems. The B-spline basis, described in the Appendix to this chapter, allows for efficient computations even when the number of knots K is large. 

## 5.2.1 Natural Cubic Splines

We know that the behavior of polynomials fit to data tends to be erratic near the boundaries, and extrapolation can be dangerous. These problems are exacerbated with splines. The polynomials fit beyond the boundary knots behave even more wildly than the corresponding global polynomials in that region. This can be conveniently summarized in terms of the pointwise variance of spline functions fit by least squares (see the example in the next section for details on these variance calculations). Figure 5.3 compares the pointwise variances for a variety of different models. The explosion of the variance near the boundaries is clear, and inevitably is worst for cubic splines. 

![image](<Images/05_Basis_Expansions_and_Regularization_image_009.jpg>)



FIGURE 5.3. Pointwise variance curves for four different models, with X consisting of 50 points drawn at random from U[0, 1], and an assumed error model with constant variance. The linear and cubic polynomial fits have two and four degrees of freedom, respectively, while the cubic spline and natural cubic spline each have six degrees of freedom. The cubic spline has two knots at 0.33 and 0.66, while the natural spline has boundary knots at 0.1 and 0.9, and four interior knots uniformly spaced between them.


A natural cubic spline adds additional constraints, namely that the function is linear beyond the boundary knots. This frees up four degrees of freedom (two constraints each in both boundary regions), which can be spent more profitably by sprinkling more knots in the interior region. This tradeoff is illustrated in terms of variance in Figure 5.3. There will be a price paid in bias near the boundaries, but assuming the function is linear near the boundaries (where we have less information anyway) is often considered reasonable. 

A natural cubic spline with K knots is represented by K basis functions. One can start from a basis for cubic splines, and derive the reduced basis by imposing the boundary constraints. For example, starting from the truncated power series basis described in Section 5.2, we arrive at (Exercise 5.4): 

$$
N _ {1} (X) = 1, \quad N _ {2} (X) = X, \quad N _ {k + 2} (X) = d _ {k} (X) - d _ {K - 1} (X),\tag{5.4}
$$

where 

$$
d _ {k} (X) = \frac {(X - \xi_ {k}) _ {+} ^ {3} - (X - \xi_ {K}) _ {+} ^ {3}}{\xi_ {K} - \xi_ {k}}.\tag{5.5}
$$

Each of these basis functions can be seen to have zero second and third derivative for $X \geq \xi _ { K }$ 

## 5.2.2 Example: South African Heart Disease (Continued)

In Section 4.4.2 we fit linear logistic regression models to the South African heart disease data. Here we explore nonlinearities in the functions using natural splines. The functional form of the model is 

$$
\operatorname{logit} \left[ \operatorname * {P r} (\mathsf {c h d} | X) \right] = \theta_ {0} + h _ {1} (X _ {1}) ^ {T} \theta_ {1} + h _ {2} (X _ {2}) ^ {T} \theta_ {2} + \dots + h _ {p} (X _ {p}) ^ {T} \theta_ {p},\tag{5.6}
$$

where each of the $\theta _ { j }$ are vectors of coefficients multiplying their associated vector of natural spline basis functions $h _ { j }$ 

We use four natural spline bases for each term in the model. For example, with $X _ { 1 }$ representing sbp, $h _ { 1 } ( X _ { 1 } )$ is a basis consisting of four basis functions. This actually implies three rather than two interior knots (chosen at uniform quantiles of sbp), plus two boundary knots at the extremes of the data, since we exclude the constant term from each of the $h _ { j }$ 

Since famhist is a two-level factor, it is coded by a simple binary or dummy variable, and is associated with a single coefficient in the fit of the model. 

More compactly we can combine all p vectors of basis functions (and the constant term) into one big vector $h ( X )$ , and then the model is simply $h ( X ) ^ { T } \theta$ , with total number of parameters d $\begin{array} { r } { \mathrm { f } = 1 + \sum _ { j = 1 } ^ { p } \mathrm { d f } _ { j } } \end{array}$ , the sum of the parameters in each component term. Each basis function is evaluated at each of the N samples, resulting in a N  df basis matrix H. At this point the model is like any other linear logistic model, and the algorithms described in Section 4.4.1 apply. 

We carried out a backward stepwise deletion process, dropping terms from this model while preserving the group structure of each term, rather than dropping one coefficient at a time. The AIC statistic (Section 7.5) was used to drop terms, and all the terms remaining in the final model would cause AIC to increase if deleted from the model (see Table 5.1). Figure 5.4 shows a plot of the final model selected by the stepwise regression. The functions displayed are $\hat { f } _ { j } ( X _ { j } ) ~ = ~ h _ { j } ( X _ { j } ) ^ { \check { T } } \hat { \theta } _ { j }$ for each variable $X _ { j }$ . The covariance matrix $\operatorname { C o v } ( \hat { \theta } ) = \Sigma$ is estimated by $\hat { \mathbf { \boldsymbol { \Sigma } } } = ( \mathbf { H } ^ { T } \mathbf { W } \mathbf { H } ) ^ { - 1 }$ , where W is the diagonal weight matrix from the logistic regression. Hence $v _ { j } ( X _ { j } ) =$ $\mathrm { V a r } [ \hat { f } _ { j } ( X _ { j } ) ] = h _ { j } ( X _ { j } ) ^ { T } \hat { \Sigma } _ { j j } h _ { j } ( X _ { j } )$ is the pointwise variance function of $\hat { f } _ { j } ^ { \phantom { \dagger } } ,$ where Cov $( \hat { \theta } _ { j } ) = \hat { \Sigma } _ { j j }$ is the appropriate sub-matrix of $\hat { \Sigma }$ . The shaded region in each panel is defined by $\hat { f } _ { j } ( X _ { j } ) \pm 2 \sqrt { v _ { j } ( X _ { j } ) }$ 

The AIC statistic is slightly more generous than the likelihood-ratio test (deviance test). Both sbp and obesity are included in this model, while they were not in the linear model. The figure explains why, since their contributions are inherently nonlinear. These effects at first may come as a surprise, but an explanation lies in the nature of the retrospective data. These measurements were made sometime after the patients suffered a heart attack, and in many cases they had already benefited from a healthier diet and lifestyle, hence the apparent increase in risk at low values for obesity and sbp. Table 5.1 shows a summary of the selected model. 

![image](<Images/05_Basis_Expansions_and_Regularization_image_010.jpg>)


![image](<Images/05_Basis_Expansions_and_Regularization_image_011.jpg>)


![image](<Images/05_Basis_Expansions_and_Regularization_image_012.jpg>)


![image](<Images/05_Basis_Expansions_and_Regularization_image_013.jpg>)


![image](<Images/05_Basis_Expansions_and_Regularization_image_014.jpg>)


![image](<Images/05_Basis_Expansions_and_Regularization_image_015.jpg>)



FIGURE 5.4. Fitted natural-spline functions for each of the terms in the final model selected by the stepwise procedure. Included are pointwise standard-error bands. The rug plot at the base of each figure indicates the location of each of the sample values for that variable (jittered to break ties).



TABLE 5.1. Final logistic regression model, after stepwise deletion of natural splines terms. The column labeled $^ { 6 } L R T ^ { 9 }$ is the likelihood-ratio test statistic when that term is deleted from the model, and is the change in deviance from the full model (labeled “none”).


<table><tr><td>Terms</td><td>Df</td><td>Deviance</td><td>AIC</td><td>LRT</td><td>P-value</td></tr><tr><td>none</td><td></td><td>458.09</td><td>502.09</td><td></td><td></td></tr><tr><td>sbp</td><td>4</td><td>467.16</td><td>503.16</td><td>9.076</td><td>0.059</td></tr><tr><td>tobacco</td><td>4</td><td>470.48</td><td>506.48</td><td>12.387</td><td>0.015</td></tr><tr><td>ldl</td><td>4</td><td>472.39</td><td>508.39</td><td>14.307</td><td>0.006</td></tr><tr><td>famhist</td><td>1</td><td>479.44</td><td>521.44</td><td>21.356</td><td>0.000</td></tr><tr><td>obesity</td><td>4</td><td>466.24</td><td>502.24</td><td>8.147</td><td>0.086</td></tr><tr><td>age</td><td>4</td><td>481.86</td><td>517.86</td><td>23.768</td><td>0.000</td></tr></table>

## 5.2.3 Example: Phoneme Recognition

In this example we use splines to reduce flexibility rather than increase it; the application comes under the general heading of functional modeling. In the top panel of Figure 5.5 are displayed a sample of 15 log-periodograms for each of the two phonemes “aa” and “ao” measured at 256 frequencies. The goal is to use such data to classify a spoken phoneme. These two phonemes were chosen because they are difficult to separate. 

The input feature is a vector x of length 256, which we can think of as a vector of evaluations of a function X(f) over a grid of frequencies f. In reality there is a continuous analog signal which is a function of frequency, and we have a sampled version of it. 

The gray lines in the lower panel of Figure 5.5 show the coefficients of a linear logistic regression model fit by maximum likelihood to a training sample of 1000 drawn from the total of 695 “aa”s and 1022 “ao”s. The coefficients are also plotted as a function of frequency, and in fact we can think of the model in terms of its continuous counterpart 

$$
\log \frac {\operatorname* {P r} (\mathrm{aa} | X)}{\operatorname* {P r} (\mathrm{ao} | X)} = \int X (f) \beta (f) d f,\tag{5.7}
$$


Phoneme Examples


![image](<Images/05_Basis_Expansions_and_Regularization_image_016.jpg>)



Phoneme Classification: Raw and Restricted Logistic Regression


![image](<Images/05_Basis_Expansions_and_Regularization_image_017.jpg>)



FIGURE 5.5. The top panel displays the log-periodogram as a function of frequency for 15 examples each of the phonemes $^ { 6 6 } a a ^ { 5 7 }$ and $^ { 6 6 } a o ^ { 5 9 }$ sampled from a total of 695 $^ { 6 } a a ^ { 9 } s$ and 1022 $^ { 4 6 } a o ^ { 9 3 } s$ . Each log-periodogram is measured at 256 uniformly spaced frequencies. The lower panel shows the coefficients (as a function of frequency) of a logistic regression fit to the data by maximum likelihood, using the 256 log-periodogram values as inputs. The coefficients are restricted to be smooth in the red curve, and are unrestricted in the jagged gray curve.


which we approximate by 

$$
\sum_ {j = 1} ^ {2 5 6} X (f _ {j}) \beta (f _ {j}) = \sum_ {j = 1} ^ {2 5 6} x _ {j} \beta_ {j}.\tag{5.8}
$$

The coefficients compute a contrast functional, and will have appreciable values in regions of frequency where the log-periodograms differ between the two classes. 

The gray curves are very rough. Since the input signals have fairly strong positive autocorrelation, this results in negative autocorrelation in the coefficients. In addition the sample size effectively provides only four observations per coefficient. 

Applications such as this permit a natural regularization. We force the coefficients to vary smoothly as a function of frequency. The red curve in the lower panel of Figure 5.5 shows such a smooth coefficient curve fit to these data. We see that the lower frequencies offer the most discriminatory power. Not only does the smoothing allow easier interpretation of the contrast, it also produces a more accurate classifier: 

<table><tr><td></td><td>Raw</td><td>Regularized</td></tr><tr><td>Training error</td><td>0.080</td><td>0.185</td></tr><tr><td>Test error</td><td>0.255</td><td>0.158</td></tr></table>

The smooth red curve was obtained through a very simple use of natural cubic splines. We can represent the coefficient function as an expansion of splines $\begin{array} { r } { \beta ( f ) = \sum _ { m = 1 } ^ { M } h _ { m } ( f ) \theta _ { m } } \end{array}$ . In practice this means that $\beta = \mathbf { H } \theta$ where, H is a $p \times M$ basis matrix of natural cubic splines, defined on the set of frequencies. Here we used $M = 1 2$ basis functions, with knots uniformly placed over the integers 1, 2, . . . , 256 representing the frequencies. Since $\mathbf { \bar { \boldsymbol { x } } } ^ { T } \beta = \boldsymbol { x } ^ { T } \mathbf { H } \theta$ , we can simply replace the input features x by their filtered versions $\boldsymbol { x } ^ { * } = \mathbf { H } ^ { T } \boldsymbol { x }$ , and fit θ by linear logistic regression on the $x ^ { * }$ . The red curve is thus $\hat { \beta } ( f ) = h ( f ) ^ { T } \hat { \theta }$ 

## 5.3 Filtering and Feature Extraction

In the previous example, we constructed a $p \times M$ basis matrix H, and then transformed our features x into new features $\boldsymbol { x } ^ { * } = \mathbf { H } ^ { T } \boldsymbol { x }$ . These filtered versions of the features were then used as inputs into a learning procedure: in the previous example, this was linear logistic regression. 

Preprocessing of high-dimensional features is a very general and powerful method for improving the performance of a learning algorithm. The preprocessing need not be linear as it was above, but can be a general (nonlinear) function of the form $x ^ { * } = g ( x )$ . The derived features $x ^ { * }$ can then be used as inputs into any (linear or nonlinear) learning procedure. 

For example, for signal or image recognition a popular approach is to first transform the raw features via a wavelet transform $\boldsymbol { x } ^ { * } = \mathbf { H } ^ { T } \boldsymbol { x }$ (Section 5.9) and then use the features $x ^ { * }$ as inputs into a neural network (Chapter 11). Wavelets are effective in capturing discrete jumps or edges, and the neural network is a powerful tool for constructing nonlinear functions of these features for predicting the target variable. By using domain knowledge to construct appropriate features, one can often improve upon a learning method that has only the raw features x at its disposal. 

## 5.4 Smoothing Splines

Here we discuss a spline basis method that avoids the knot selection problem completely by using a maximal set of knots. The complexity of the fit is controlled by regularization. Consider the following problem: among all functions $f ( x )$ with two continuous derivatives, find one that minimizes the penalized residual sum of squares 

$$
\operatorname{RSS} (f, \lambda) = \sum_ {i = 1} ^ {N} \left\{y _ {i} - f \left(x _ {i}\right) \right\} ^ {2} + \lambda \int \left\{f ^ {\prime \prime} (t) \right\} ^ {2} d t,\tag{5.9}
$$

where λ is a fixed smoothing parameter. The first term measures closeness to the data, while the second term penalizes curvature in the function, and λ establishes a tradeoff between the two. Two special cases are: 

$\lambda = 0 : f$ can be any function that interpolates the data. 

$\lambda = \infty$ : the simple least squares line fit, since no second derivative can be tolerated. 

These vary from very rough to very smooth, and the hope is that $\lambda \in ( 0 , \infty )$ indexes an interesting class of functions in between. 

The criterion (5.9) is defined on an infinite-dimensional function space— in fact, a Sobolev space of functions for which the second term is defined. Remarkably, it can be shown that (5.9) has an explicit, finite-dimensional, unique minimizer which is a natural cubic spline with knots at the unique values of the $x _ { i } , \ i = 1 , \dotsc , N$ (Exercise 5.7). At face value it seems that the family is still over-parametrized, since there are as many as N knots, which implies N degrees of freedom. However, the penalty term translates to a penalty on the spline coefficients, which are shrunk some of the way toward the linear fit. 

Since the solution is a natural spline, we can write it as 

$$
f (x) = \sum_ {j = 1} ^ {N} N _ {j} (x) \theta_ {j},\tag{5.10}
$$

![image](<Images/05_Basis_Expansions_and_Regularization_image_018.jpg>)



FIGURE 5.6. The response is the relative change in bone mineral density measured at the spine in adolescents, as a function of age. A separate smoothing spline was fit to the males and females, with $\lambda \approx 0 . 0 0 0 2 2$ . This choice corresponds to about 12 degrees of freedom.


where the $N _ { j } ( x )$ are an N-dimensional set of basis functions for representing this family of natural splines (Section 5.2.1 and Exercise 5.4). The criterion thus reduces to 

$$
\mathrm{RSS} (\theta , \lambda) = (\mathbf {y} - \mathbf {N} \theta) ^ {T} (\mathbf {y} - \mathbf {N} \theta) + \lambda \theta^ {T} \boldsymbol {\Omega} _ {N} \theta ,\tag{5.11}
$$

where $\{ { \bf N } \} _ { i j } = N _ { j } ( x _ { i } )$ and $\begin{array} { r } { \{ \Omega _ { N } \} _ { j k } = \int N _ { j } ^ { \prime \prime } ( t ) N _ { k } ^ { \prime \prime } ( t ) d t } \end{array}$ . The solution is easily seen to be 

$$
\hat {\boldsymbol {\theta}} = (\mathbf {N} ^ {T} \mathbf {N} + \lambda \boldsymbol {\Omega} _ {N}) ^ {- 1} \mathbf {N} ^ {T} \mathbf {y},\tag{5.12}
$$

a generalized ridge regression. The fitted smoothing spline is given by 

$$
\hat {f} (x) = \sum_ {j = 1} ^ {N} N _ {j} (x) \hat {\theta} _ {j}.\tag{5.13}
$$

Efficient computational techniques for smoothing splines are discussed in the Appendix to this chapter. 

Figure 5.6 shows a smoothing spline fit to some data on bone mineral density (BMD) in adolescents. The response is relative change in spinal BMD over two consecutive visits, typically about one year apart. The data are color coded by gender, and two separate curves were fit. This simple summary reinforces the evidence in the data that the growth spurt for females precedes that for males by about two years. In both cases the smoothing parameter λ was approximately 0.00022; this choice is discussed in the next section. 

## 5.4.1 Degrees of Freedom and Smoother Matrices

We have not yet indicated how λ is chosen for the smoothing spline. Later in this chapter we describe automatic methods using techniques such as cross-validation. In this section we discuss intuitive ways of prespecifying the amount of smoothing. 

A smoothing spline with prechosen λ is an example of a linear smoother (as in linear operator). This is because the estimated parameters in (5.12) are a linear combination of the $y _ { i }$ . Denote by $\hat { \mathbf { f } }$ the N-vector of fitted values ${ \hat { f } } ( x _ { i } )$ at the training predictors $x _ { i }$ . Then 

$$
\begin{array}{r c l} \hat {\mathbf {f}} & = & \mathbf {N} (\mathbf {N} ^ {T} \mathbf {N} + \lambda \boldsymbol {\Omega} _ {N}) ^ {- 1} \mathbf {N} ^ {T} \mathbf {y} \\ & = & \mathbf {S} _ {\lambda} \mathbf {y}. \end{array}\tag{5.14}
$$

Again the fit is linear in $\mathbf { y } ,$ , and the finite linear operator $\mathbf { S } _ { \lambda }$ is known as the smoother matrix. One consequence of this linearity is that the recipe for producing $\hat { \mathbf { f } }$ from $\mathbf { y }$ does not depend on y itself; $\mathbf { S } _ { \lambda }$ depends only on the $x _ { i }$ and $\lambda$ . 

Linear operators are familiar in more traditional least squares fitting as well. Suppose $\mathbf { B } _ { \xi }$ is a $N \times M$ matrix of M cubic-spline basis functions evaluated at the N training points $x _ { i }$ , with knot sequence $\xi ,$ and $M \ll N$ Then the vector of fitted spline values is given by 

$$
\begin{array}{r c l} \hat {\mathbf {f}} & = & \mathbf {B} _ {\xi} (\mathbf {B} _ {\xi} ^ {T} \mathbf {B} _ {\xi}) ^ {- 1} \mathbf {B} _ {\xi} ^ {T} \mathbf {y} \\ & = & \mathbf {H} _ {\xi} \mathbf {y}. \end{array}\tag{5.15}
$$

Here the linear operator $\mathbf { H } _ { \xi }$ is a projection operator, also known as the hat matrix in statistics. There are some important similarities and differences between $\mathbf { H } _ { \xi }$ and $\mathbf { S } _ { \lambda }$ : 

Both are symmetric, positive semidefinite matrices. 

$\mathbf { H } _ { \xi } \mathbf { H } _ { \xi } = \mathbf { H } _ { \xi }$ (idempotent), while $\mathbf { S } _ { \lambda } \mathbf { S } _ { \lambda } \preceq \mathbf { S } _ { \lambda }$ , meaning that the righthand side exceeds the left-hand side by a positive semidefinite matrix. This is a consequence of the shrinking nature of $\mathbf { S } _ { \lambda }$ , which we discuss further below. 

$\mathbf { H } _ { \xi }$ has rank M, while $\mathbf { S } _ { \lambda }$ has rank N. 

The expression $M = \mathrm { t r a c e } ( \mathbf { H } _ { \xi } )$ gives the dimension of the projection space, which is also the number of basis functions, and hence the number of parameters involved in the fit. By analogy we define the effective degrees of 

freedom of a smoothing spline to be 

$$
\mathrm{df} _ {\lambda} = \mathrm{trace} (\mathbf {S} _ {\lambda}),\tag{5.16}
$$

the sum of the diagonal elements of $\mathbf { S } _ { \lambda }$ . This very useful definition allows us a more intuitive way to parameterize the smoothing spline, and indeed many other smoothers as well, in a consistent fashion. For example, in Figure 5.6 we specified $\mathrm { { d f } } _ { \lambda } = 1 2$ for each of the curves, and the corresponding $\lambda \approx 0 . 0 0 0 2 2$ was derived numerically by solving trace $\mathbf { \left( S _ { \lambda \lambda } \right) } = 1 2$ . There are many arguments supporting this definition of degrees of freedom, and we cover some of them here. 

Since $\mathbf { S } _ { \lambda }$ is symmetric (and positive semidefinite), it has a real eigendecomposition. Before we proceed, it is convenient to rewrite $\mathbf { S } _ { \lambda }$ in the Reinsch form 

$$
\mathbf {S} _ {\lambda} = (\mathbf {I} + \lambda \mathbf {K}) ^ {- 1},\tag{5.17}
$$

where K does not depend on λ (Exercise 5.9). Since $\hat { \mathbf { f } } = \mathbf { S } _ { \lambda } \mathbf { y }$ solves 

$$
\min _ {\mathbf {f}} (\mathbf {y} - \mathbf {f}) ^ {T} (\mathbf {y} - \mathbf {f}) + \lambda \mathbf {f} ^ {T} \mathbf {K} \mathbf {f},\tag{5.18}
$$

K is known as the penalty matrix, and indeed a quadratic form in K has a representation in terms of a weighted sum of squared (divided) second differences. The eigen-decomposition of $\mathbf { S } _ { \lambda }$ is 

$$
\mathbf {S} _ {\lambda} = \sum_ {k = 1} ^ {N} \rho_ {k} (\lambda) \mathbf {u} _ {k} \mathbf {u} _ {k} ^ {T}\tag{5.19}
$$

with 

$$
\rho_ {k} (\lambda) = \frac {1}{1 + \lambda d _ {k}},\tag{5.20}
$$

and $d _ { k }$ the corresponding eigenvalue of K. Figure 5.7 (top) shows the results of applying a cubic smoothing spline to some air pollution data (128 observations). Two fits are given: a smoother fit corresponding to a larger penalty λ and a rougher fit for a smaller penalty. The lower panels represent the eigenvalues (lower left) and some eigenvectors (lower right) of the corresponding smoother matrices. Some of the highlights of the eigenrepresentation are the following: 

The eigenvectors are not affected by changes in λ, and hence the whole family of smoothing splines (for a particular sequence x) indexed by λ have the same eigenvectors. 

$\begin{array} { r } { \mathbf { S } _ { \lambda } \mathbf { y } = \sum _ { k = 1 } ^ { N } \mathbf { u } _ { k } \rho _ { k } ( \lambda ) \langle \mathbf { u } _ { k } , \mathbf { y } \rangle } \end{array}$ , and hence the smoothing spline operates by decomposing y w.r.t. the (complete) basis $\left\{ { \bf u } _ { k } \right\}$ , and differentially shrinking the contributions using $\rho _ { k } ( \lambda )$ . This is to be contrasted with a basis-regression method, where the components are either left alone, or shrunk to zero—that is, a projection matrix such as $\mathbf { H } _ { \xi }$ above has M eigenvalues equal to 1, and the rest are 0. For this reason smoothing splines are referred to as shrinking smoothers, while regression splines are projection smoothers (see Figure 3.17 on page 80). 

![image](<Images/05_Basis_Expansions_and_Regularization_image_019.jpg>)



Daggot Pressure Gradient


![image](<Images/05_Basis_Expansions_and_Regularization_image_020.jpg>)



FIGURE 5.7. (Top:) Smoothing spline fit of ozone concentration versus Daggot pressure gradient. The two fits correspond to different values of the smoothing parameter, chosen to achieve five and eleven effective degrees of freedom, defined by $d f _ { \lambda } = t r a c e ( \mathbf { S } _ { \lambda } )$ . (Lower left:) First 25 eigenvalues for the two smoothing-spline matrices. The first two are exactly 1, and all are $\geq 0$ . (Lower right:) Third to sixth eigenvectors of the spline smoother matrices. In each case, ${ \bf u } _ { k }$ is plotted against x, and as such is viewed as a function of x. The rug at the base of the plots indicate the occurrence of data points. The damped functions represent the smoothed versions of these functions (using the 5 df smoother).


The sequence of $\mathbf { u } _ { k }$ , ordered by decreasing $\rho _ { k } ( \lambda )$ , appear to increase in complexity. Indeed, they have the zero-crossing behavior of polynomials of increasing degree. Since $\mathbf { S } _ { \lambda } \mathbf { u } _ { k } = \rho _ { k } ( \lambda ) \mathbf { u } _ { k }$ , we see how each of the eigenvectors themselves are shrunk by the smoothing spline: the higher the complexity, the more they are shrunk. If the domain of X is periodic, then the $\mathbf { u } _ { k }$ are sines and cosines at different frequencies. 

The first two eigenvalues are always one, and they correspond to the two-dimensional eigenspace of functions linear in x (Exercise 5.11), which are never shrunk. 

The eigenvalues $\rho _ { k } ( \lambda ) = 1 / ( 1 + \lambda d _ { k } )$ are an inverse function of the eigenvalues $d _ { k }$ of the penalty matrix K, moderated by $\lambda ; \lambda$ controls the rate at which the $\rho _ { k } ( \lambda )$ decrease to zero. $d _ { 1 } = d _ { 2 } = 0$ and again linear functions are not penalized. 

One can reparametrize the smoothing spline using the basis vectors $\mathbf { u } _ { k }$ (the Demmler–Reinsch basis). In this case the smoothing spline solves 

$$
\min _ {\boldsymbol {\theta}} \left\| \mathbf {y} - \mathbf {U} \boldsymbol {\theta} \right\| ^ {2} + \lambda \boldsymbol {\theta} ^ {T} \mathbf {D} \boldsymbol {\theta},\tag{5.21}
$$

where U has columns $\mathbf { u } _ { k }$ and D is a diagonal matrix with elements $d _ { k }$ 

$\mathrm { d f } _ { \lambda } = \mathrm { t r a c e } ( \mathbf { S } _ { \lambda } ) = \sum _ { k = 1 } ^ { N } \rho _ { k } ( \lambda )$ . For projection smoothers, all the eigenvalues are 1, each one corresponding to a dimension of the projection subspace. 

Figure 5.8 depicts a smoothing spline matrix, with the rows ordered with x. The banded nature of this representation suggests that a smoothing spline is a local fitting method, much like the locally weighted regression procedures in Chapter 6. The right panel shows in detail selected rows of S, which we call the equivalent kernels. As $\lambda  0 , \mathrm { d f } _ { \lambda }  N$ , and $\mathbf { S } _ { \lambda } \to \mathbf { I }$ 2 the N-dimensional identity matrix. As $\lambda \to \infty , \mathrm { d f } _ { \lambda } \to 2 .$ and $\mathbf { S } _ { \lambda } \to \mathbf { H }$ , the hat matrix for linear regression on x. 

## 5.5 Automatic Selection of the Smoothing Parameters

The smoothing parameters for regression splines encompass the degree of the splines, and the number and placement of the knots. For smoothing splines, we have only the penalty parameter λ to select, since the knots are at all the unique training $X \mathrm { { s } }$ , and cubic degree is almost always used in practice. 


Equivalent Kernels


![image](<Images/05_Basis_Expansions_and_Regularization_image_021.jpg>)



FIGURE 5.8. The smoother matrix for a smoothing spline is nearly banded, indicating an equivalent kernel with local support. The left panel represents the elements of S as an image. The right panel shows the equivalent kernel or weighting function in detail for the indicated rows.


Selecting the placement and number of knots for regression splines can be a combinatorially complex task, unless some simplifications are enforced. The MARS procedure in Chapter 9 uses a greedy algorithm with some additional approximations to achieve a practical compromise. We will not discuss this further here. 

## 5.5.1 Fixing the Degrees of Freedom

Since $\mathrm { d f } _ { \lambda } = \mathrm { t r a c e } ( \mathbf { S } _ { \lambda } )$ is monotone in λ for smoothing splines, we can invert the relationship and specify λ by fixing df. In practice this can be achieved by simple numerical methods. So, for example, in R one can use smooth.spline $( \mathbf { x } , \mathbf { y } , { \mathsf { d f } } { = } 6 )$ to specify the amount of smoothing. This encourages a more traditional mode of model selection, where we might try a couple of different values of df, and select one based on approximate F-tests, residual plots and other more subjective criteria. Using df in this way provides a uniform approach to compare many different smoothing methods. It is particularly useful in generalized additive models (Chapter 9), where several smoothing methods can be simultaneously used in one model. 

## 5.5.2 The Bias–Variance Tradeoff

Figure 5.9 shows the effect of the choice of $\operatorname { d f } _ { \lambda }$ when using a smoothing spline on a simple example: 

$$
\begin{array}{c} Y = f (X) + \varepsilon , \\ f (X) = \frac {\sin (1 2 (X + 0 . 2))}{X + 0 . 2}, \end{array}\tag{5.22}
$$

with $X \sim U [ 0 , 1 ]$ and $\varepsilon \sim N ( 0 , 1 )$ . Our training sample consists of $N = 1 0 0$ pairs $x _ { i } , y _ { i }$ drawn independently from this model. 

The fitted splines for three different values of $\operatorname { d f } _ { \lambda }$ are shown. The yellow shaded region in the figure represents the pointwise standard error of $\hat { f } _ { \lambda }$ , that is, we have shaded the region between ${ \hat { f } } _ { \lambda } ( x ) \pm 2 \cdot \sec ( { \hat { f } } _ { \lambda } ( x ) )$ . Since $\hat { \mathbf { f } } = \mathbf { S } _ { \lambda } \mathbf { y }$ 

$$
\begin{array}{r c l} \operatorname{Cov} (\hat {\mathbf {f}}) & = & \mathbf {S} _ {\lambda} \operatorname{Cov} (\mathbf {y}) \mathbf {S} _ {\lambda} ^ {T} \\ & = & \mathbf {S} _ {\lambda} \mathbf {S} _ {\lambda} ^ {T}. \end{array}\tag{5.23}
$$

The diagonal contains the pointwise variances at the training $x _ { i }$ . The bias is given by 

$$
\begin{array}{r c l} \text {Bias} (\hat {\mathbf {f}}) & = & \mathbf {f} - \operatorname{E} (\hat {\mathbf {f}}) \\ & = & \mathbf {f} - \mathbf {S} _ {\lambda} \mathbf {f}, \end{array}\tag{5.24}
$$

![image](<Images/05_Basis_Expansions_and_Regularization_image_022.jpg>)


![image](<Images/05_Basis_Expansions_and_Regularization_image_023.jpg>)


![image](<Images/05_Basis_Expansions_and_Regularization_image_024.jpg>)


![image](<Images/05_Basis_Expansions_and_Regularization_image_025.jpg>)



FIGURE 5.9. The top left panel shows the EPE(λ) and CV(λ) curves for a realization from a nonlinear additive error model (5.22). The remaining panels show the data, the true functions (in purple), and the fitted curves (in green) with yellow shaded $\pm 2 \times$ standard error bands, for three different values of $d f _ { \lambda }$


where f is the (unknown) vector of evaluations of the true f at the training $X \mathrm { { s } }$ . The expectations and variances are with respect to repeated draws of samples of size $N = 1 0 0$ from the model (5.22). In a similar fashion $\mathrm { V a r } ( \hat { f } _ { \lambda } ( x _ { 0 } ) )$ and $\operatorname { B i a s } ( { \hat { f } } _ { \lambda } ( x _ { 0 } ) )$ can be computed at any point $x _ { 0 }$ (Exercise 5.10). The three fits displayed in the figure give a visual demonstration of the bias-variance tradeoff associated with selecting the smoothing parameter. 

$\mathrm { d f } _ { \lambda } = 5$ : The spline under fits, and clearly trims down the hills and fills in the valleys. This leads to a bias that is most dramatic in regions of high curvature. The standard error band is very narrow, so we estimate a badly biased version of the true function with great reliability! 

$\mathrm { d f } _ { \lambda } = 9$ : Here the fitted function is close to the true function, although a slight amount of bias seems evident. The variance has not increased appreciably. 

$\mathrm { d f } _ { \lambda } = 1 5 $ : The fitted function is somewhat wiggly, but close to the true function. The wiggliness also accounts for the increased width of the standard error bands—the curve is starting to follow some individual points too closely. 

Note that in these figures we are seeing a single realization of data and hence fitted spline $\hat { f }$ in each case, while the bias involves an expectation $\operatorname { E } ( { \hat { f } } )$ . We leave it as an exercise (5.10) to compute similar figures where the bias is shown as well. The middle curve seems “just right,” in that it has achieved a good compromise between bias and variance. 

The integrated squared prediction error (EPE) combines both bias and variance in a single summary: 

$$
\begin{array}{r c l} \mathrm{EPE} (\hat {f} _ {\lambda}) & = & \mathrm{E} (Y - \hat {f} _ {\lambda} (X)) ^ {2} \\ & = & \mathrm{Var} (Y) + \mathrm{E} \left[ \mathrm{Bias} ^ {2} (\hat {f} _ {\lambda} (X)) + \mathrm{Var} (\hat {f} _ {\lambda} (X)) \right] \\ & = & \sigma^ {2} + \mathrm{MSE} (\hat {f} _ {\lambda}). \end{array}\tag{5.25}
$$

Note that this is averaged both over the training sample (giving rise to ${ \hat { f } } _ { \lambda } )$ and the values of the (independently chosen) prediction points (X, Y ). EPE is a natural quantity of interest, and does create a tradeoff between bias and variance. The blue points in the top left panel of Figure 5.9 suggest that $\mathrm { d f } _ { \lambda } = 9$ is spot on! 

Since we don’t know the true function, we do not have access to EPE, and need an estimate. This topic is discussed in some detail in Chapter 7, and techniques such as K-fold cross-validation, GCV and $C _ { p }$ are all in common use. In Figure 5.9 we include the N-fold (leave-one-out) cross-validation curve: 

$$
\begin{array}{r c l} \mathrm{CV} (\hat {f} _ {\lambda}) & = & \frac {1}{N} \sum_ {i = 1} ^ {N} (y _ {i} - \hat {f} _ {\lambda} ^ {(- i)} (x _ {i})) ^ {2} \\ & = & \frac {1}{N} \sum_ {i = 1} ^ {N} \left(\frac {y _ {i} - \hat {f} _ {\lambda} (x _ {i})}{1 - S _ {\lambda} (i , i)}\right) ^ {2}, \end{array}\tag{5.26}
$$

(5.27) 

which can (remarkably) be computed for each value of λ from the original fitted values and the diagonal elements $S _ { \lambda } ( { i , i } )$ of $\mathbf { S } _ { \lambda }$ (Exercise 5.13). 

The EPE and CV curves have a similar shape, but the entire CV curve is above the EPE curve. For some realizations this is reversed, and overall the CV curve is approximately unbiased as an estimate of the EPE curve. 

## 5.6 Nonparametric Logistic Regression

The smoothing spline problem (5.9) in Section 5.4 is posed in a regression setting. It is typically straightforward to transfer this technology to other domains. Here we consider logistic regression with a single quantitative input X. The model is 

$$
\log \frac {\operatorname* {P r} (Y = 1 | X = x)}{\operatorname* {P r} (Y = 0 | X = x)} = f (x),\tag{5.28}
$$

which implies 

$$
\operatorname * {P r} (Y = 1 | X = x) = \frac {e ^ {f (x)}}{1 + e ^ {f (x)}}.\tag{5.29}
$$

Fitting $f ( x )$ in a smooth fashion leads to a smooth estimate of the conditional probability $\operatorname* { P r } ( Y = 1 | x )$ , which can be used for classification or risk scoring. 

We construct the penalized log-likelihood criterion 

$$
\begin{array}{r c l} \ell (f; \lambda) & = & \sum_ {i = 1} ^ {N} \left[ y _ {i} \log p (x _ {i}) + (1 - y _ {i}) \log (1 - p (x _ {i})) \right] - \frac {1}{2} \lambda \int \{f ^ {\prime \prime} (t) \} ^ {2} d t \\ & = & \sum_ {i = 1} ^ {N} \left[ y _ {i} f (x _ {i}) - \log (1 + e ^ {f (x _ {i})}) \right] - \frac {1}{2} \lambda \int \{f ^ {\prime \prime} (t) \} ^ {2} d t, \end{array} \tag {5.30}
$$

where we have abbreviated $p ( x ) = \operatorname* { P r } ( Y = 1 | x )$ . The first term in this expression is the log-likelihood based on the binomial distribution (c.f. Chapter 4, page 120). Arguments similar to those used in Section 5.4 show that the optimal f is a finite-dimensional natural spline with knots at the unique values of x. This means that we can represent $\begin{array} { r } { f ( x ) = \sum _ { j = 1 } ^ { N } N _ { j } ( x ) \theta _ { j } } \end{array}$ . We compute the first and second derivatives 

$$
\frac {\partial \ell (\theta)}{\partial \theta} = \mathbf {N} ^ {T} (\mathbf {y} - \mathbf {p}) - \lambda \boldsymbol {\Omega} \theta ,\tag{5.31}
$$

$$
{\frac {\partial^ {2} \ell (\theta)}{\partial \theta \partial \theta^ {T}}} = {- \mathbf {N} ^ {T} \mathbf {W N} - \lambda \boldsymbol {\Omega},}\tag{5.32}
$$

where p is the N-vector with elements $p ( x _ { i } )$ , and W is a diagonal matrix of weights $p ( x _ { i } ) ( 1 - p ( x _ { i } ) )$ . The first derivative (5.31) is nonlinear in θ, so we need to use an iterative algorithm as in Section 4.4.1. Using Newton– Raphson as in (4.23) and (4.26) for linear logistic regression, the update equation can be written 

$$
\begin{array}{r c l} \theta^ {\text {new}} & = & (\mathbf {N} ^ {T} \mathbf {W} \mathbf {N} + \lambda \boldsymbol {\Omega}) ^ {- 1} \mathbf {N} ^ {T} \mathbf {W} \left(\mathbf {N} \theta^ {\text {old}} + \mathbf {W} ^ {- 1} (\mathbf {y} - \mathbf {p})\right) \\ & = & (\mathbf {N} ^ {T} \mathbf {W} \mathbf {N} + \lambda \boldsymbol {\Omega}) ^ {- 1} \mathbf {N} ^ {T} \mathbf {W} \mathbf {z}. \end{array}\tag{5.33}
$$

We can also express this update in terms of the fitted values 

$$
\begin{array}{r c l} \mathbf {f} ^ {\mathrm{new}} & = & \mathbf {N} (\mathbf {N} ^ {T} \mathbf {W} \mathbf {N} + \lambda \boldsymbol {\Omega}) ^ {- 1} \mathbf {N} ^ {T} \mathbf {W} \left(\mathbf {f} ^ {\mathrm{old}} + \mathbf {W} ^ {- 1} (\mathbf {y} - \mathbf {p})\right) \\ & = & \mathbf {S} _ {\lambda , w} \mathbf {z}. \end{array}\tag{5.34}
$$

Referring back to (5.12) and (5.14), we see that the update fits a weighted smoothing spline to the working response z (Exercise 5.12). 

The form of (5.34) is suggestive. It is tempting to replace $\mathbf { S } _ { \lambda , w }$ by any nonparametric (weighted) regression operator, and obtain general families of nonparametric logistic regression models. Although here x is onedimensional, this procedure generalizes naturally to higher-dimensional x. These extensions are at the heart of generalized additive models, which we pursue in Chapter 9. 

## 5.7 Multidimensional Splines

So far we have focused on one-dimensional spline models. Each of the approaches have multidimensional analogs. Suppose $X \in \mathbb { R } ^ { 2 }$ , and we have a basis of functions $h _ { 1 k } ( X _ { 1 } ) , \ k = 1 , \ldots , M _ { 1 }$ for representing functions of coordinate $X _ { 1 }$ , and likewise a set of $M _ { 2 }$ functions $h _ { 2 k } ( X _ { 2 } )$ for coordinate $X _ { 2 }$ . Then the $M _ { 1 } \times M _ { 2 }$ dimensional tensor product basis defined by 

$$
g _ {j k} (X) = h _ {1 j} (X _ {1}) h _ {2 k} (X _ {2}), j = 1, \ldots , M _ {1}, k = 1, \ldots , M _ {2}\tag{5.35}
$$

can be used for representing a two-dimensional function: 

$$
g (X) = \sum_ {j = 1} ^ {M _ {1}} \sum_ {k = 1} ^ {M _ {2}} \theta_ {j k} g _ {j k} (X).\tag{5.36}
$$

![image](<Images/05_Basis_Expansions_and_Regularization_image_026.jpg>)



FIGURE 5.10. A tensor product basis of B-splines, showing some selected pairs. Each two-dimensional function is the tensor product of the corresponding one dimensional marginals.


Figure 5.10 illustrates a tensor product basis using B-splines. The coefficients can be fit by least squares, as before. This can be generalized to d dimensions, but note that the dimension of the basis grows exponentially fast—yet another manifestation of the curse of dimensionality. The MARS procedure discussed in Chapter 9 is a greedy forward algorithm for including only those tensor products that are deemed necessary by least squares. 

Figure 5.11 illustrates the difference between additive and tensor product (natural) splines on the simulated classification example from Chapter 2. A logistic regression model logit $[ \mathrm { P r } ( T | x ) ] = h ( x ) ^ { T } \theta$ is fit to the binary response, and the estimated decision boundary is the contour $h ( x ) ^ { T } { \hat { \theta } } \ = \ 0$ The tensor product basis can achieve more flexibility at the decision boundary, but introduces some spurious structure along the way. 


Additive Natural Cubic Splines - 4 df each


![image](<Images/05_Basis_Expansions_and_Regularization_image_027.jpg>)



Natural Cubic Splines - Tensor Product - 4 df each


![image](<Images/05_Basis_Expansions_and_Regularization_image_028.jpg>)



FIGURE 5.11. The simulation example ofFigure 2.1. The upper panel shows the decision boundary of an additive logistic regression model, using natural splines in each of the two coordinates (total $d f = 1 + ( 4 - 1 ) + ( 4 - 1 ) = 7 )$ . The lower panel shows the results of using a tensor product of natural spline bases in each coordinate (total $d f = 4 \times 4 = 1 6 )$ . The broken purple boundary is the Bayes decision boundary for this problem.


One-dimensional smoothing splines (via regularization) generalize to higher dimensions as well. Suppose we have pairs $y _ { i } , x _ { i }$ with $x _ { i } \in \mathbb { R } ^ { d }$ , and we seek a d-dimensional regression function $f ( x )$ . The idea is to set up the problem 

$$
\min _ {f} \sum_ {i = 1} ^ {N} \{y _ {i} - f (x _ {i}) \} ^ {2} + \lambda J [ f ],\tag{5.37}
$$

where $J$ is an appropriate penalty functional for stabilizing a function $f$ in $\mathbb { R } ^ { d }$ . For example, a natural generalization of the one-dimensional roughness penalty (5.9) for functions on $\mathbb { R } ^ { 2 }$ is 

$$
J [ f ] = \int \int_ {\mathbb {R} ^ {2}} \left[ \left(\frac {\partial^ {2} f (x)}{\partial x _ {1} ^ {2}}\right) ^ {2} + 2 \left(\frac {\partial^ {2} f (x)}{\partial x _ {1} \partial x _ {2}}\right) ^ {2} + \left(\frac {\partial^ {2} f (x)}{\partial x _ {2} ^ {2}}\right) ^ {2} \right] d x _ {1} d x _ {2}.\tag{5.38}
$$

Optimizing (5.37) with this penalty leads to a smooth two-dimensional surface, known as a thin-plate spline. It shares many properties with the one-dimensional cubic smoothing spline: 

as $\lambda  0$ , the solution approaches an interpolating function [the one with smallest penalty (5.38)]; 

as $\lambda \to \infty$ , the solution approaches the least squares plane; 

for intermediate values of λ, the solution can be represented as a linear expansion of basis functions, whose coefficients are obtained by a form of generalized ridge regression. 

The solution has the form 

$$
f (x) = \beta_ {0} + \beta^ {T} x + \sum_ {j = 1} ^ {N} \alpha_ {j} h _ {j} (x),\tag{5.39}
$$

where $h _ { j } ( \boldsymbol { x } ) = | | \boldsymbol { x } - \boldsymbol { x } _ { j } | | ^ { 2 } \log | | \boldsymbol { x } - \boldsymbol { x } _ { j } | |$ . These $h _ { j }$ are examples of radial basis functions, which are discussed in more detail in the next section. The coefficients are found by plugging (5.39) into (5.37), which reduces to a finite-dimensional penalized least squares problem. For the penalty to be finite, the coefficients $\alpha _ { j }$ have to satisfy a set of linear constraints; see Exercise 5.14. 

Thin-plate splines are defined more generally for arbitrary dimension $d ,$ for which an appropriately more general J is used. 

There are a number of hybrid approaches that are popular in practice, both for computational and conceptual simplicity. Unlike one-dimensional smoothing splines, the computational complexity for thin-plate splines is $O ( N ^ { 3 } )$ , since there is not in general any sparse structure that can be exploited. However, as with univariate smoothing splines, we can get away with substantially less than the N knots prescribed by the solution (5.39). 

![image](<Images/05_Basis_Expansions_and_Regularization_image_029.jpg>)



FIGURE 5.12. A thin-plate spline fit to the heart disease data, displayed as a contour plot. The response is systolic blood pressure, modeled as a function of age and obesity. The data points are indicated, as well as the lattice of points used as knots. Care should be taken to use knots from the lattice inside the convex hull of the data (red), and ignore those outside (green).


In practice, it is usually sufficient to work with a lattice of knots covering the domain. The penalty is computed for the reduced expansion just as before. Using K knots reduces the computations to $O ( N K ^ { 2 } + K ^ { 3 } )$ . Figure 5.12 shows the result of fitting a thin-plate spline to some heart disease risk factors, representing the surface as a contour plot. Indicated are the location of the input features, as well as the knots used in the fit. Note that λ was specified via $\mathrm { d f } _ { \lambda } = \mathrm { t r a c e } ( S _ { \lambda } ) = 1 5$ 

More generally one can represent $f \in \mathbb { R } ^ { d }$ as an expansion in any arbitrarily large collection of basis functions, and control the complexity by applying a regularizer such as (5.38). For example, we could construct a basis by forming the tensor products of all pairs of univariate smoothing-spline basis functions as in (5.35), using, for example, the univariate B-splines recommended in Section 5.9.2 as ingredients. This leads to an exponential growth in basis functions as the dimension increases, and typically we have to reduce the number of functions per coordinate accordingly. 

The additive spline models discussed in Chapter 9 are a restricted class of multidimensional splines. They can be represented in this general formulation as well; that is, there exists a penalty J[f] that guarantees that the solution has the form $f ( X ) = \alpha + f _ { 1 } ( X _ { 1 } ) + \cdot \cdot \cdot + f _ { d } ( X _ { d } )$ and that each of the functions $f _ { j }$ are univariate splines. In this case the penalty is somewhat degenerate, and it is more natural to assume that f is additive, and then simply impose an additional penalty on each of the component functions: 

$$
\begin{array}{r c l} J [ f ] & = & J (f _ {1} + f _ {2} + \dots + f _ {d}) \\ & = & \sum_ {j = 1} ^ {d} \int f _ {j} ^ {\prime \prime} (t _ {j}) ^ {2} d t _ {j}. \end{array}\tag{5.40}
$$

These are naturally extended to ANOVA spline decompositions, 

$$
f (X) = \alpha + \sum_ {j} f _ {j} (X _ {j}) + \sum_ {j <   k} f _ {j k} (X _ {j}, X _ {k}) + \dots ,\tag{5.41}
$$

where each of the components are splines of the required dimension. There are many choices to be made: 

The maximum order of interaction—we have shown up to order 2 above. 

Which terms to include—not all main effects and interactions are necessarily needed. 

What representation to use—some choices are: 

– regression splines with a relatively small number of basis functions per coordinate, and their tensor products for interactions; 

– a complete basis as in smoothing splines, and include appropriate regularizers for each term in the expansion. 

In many cases when the number of potential dimensions (features) is large, automatic methods are more desirable. The MARS and MART procedures (Chapters 9 and 10, respectively), both fall into this category. 

## 5.8 Regularization and Reproducing Kernel Hilbert Spaces

![image](<Images/05_Basis_Expansions_and_Regularization_image_030.jpg>)


In this section we cast splines into the larger context of regularization methods and reproducing kernel Hilbert spaces. This section is quite technical and can be skipped by the disinterested or intimidated reader. 

A general class of regularization problems has the form 

$$
\min _ {f \in \mathcal {H}} \left[ \sum_ {i = 1} ^ {N} L (y _ {i}, f (x _ {i})) + \lambda J (f) \right]\tag{5.42}
$$

where $L ( y , f ( x ) )$ is a loss function, $J ( f )$ is a penalty functional, and $\mathcal { H }$ is a space of functions on which $J ( f )$ is defined. Girosi et al. (1995) describe quite general penalty functionals of the form 

$$
J (f) = \int_ {\mathbb {R} ^ {d}} \frac {| \tilde {f} (s) | ^ {2}}{\tilde {G} (s)} d s,\tag{5.43}
$$

where $\tilde { f }$ denotes the Fourier transform of $f ,$ and $\tilde { G }$ is some positive function that falls of to zero as $| | s | | \to \infty$ . The idea is that $1 / { \tilde { G } }$ increases the penalty for high-frequency components of $f .$ . Under some additional assumptions they show that the solutions have the form 

$$
f (X) = \sum_ {k = 1} ^ {K} \alpha_ {k} \phi_ {k} (X) + \sum_ {i = 1} ^ {N} \theta_ {i} G (X - x _ {i}),\tag{5.44}
$$

where the $\phi _ { k }$ span the null space of the penalty functional $^ { J , }$ and G is the inverse Fourier transform of $\tilde { G }$ . Smoothing splines and thin-plate splines fall into this framework. The remarkable feature of this solution is that while the criterion (5.42) is defined over an infinite-dimensional space, the solution is finite-dimensional. In the next sections we look at some specific examples. 

## 5.8.1 Spaces of Functions Generated by Kernels

An important subclass of problems of the form (5.42) are generated by a positive definite kernel $K ( x , y )$ , and the corresponding space of functions $\mathcal { H } _ { K }$ is called a reproducing kernel Hilbert space (RKHS). The penalty functional J is defined in terms of the kernel as well. We give a brief and simplified introduction to this class of models, adapted from Wahba (1990) and Girosi et al. (1995), and nicely summarized in Evgeniou et al. (2000). 

Let x, $y \in \mathbb { R } ^ { p }$ . We consider the space of functions generated by the linear span of $\{ K ( \cdot , y ) , \ y \in \mathbb { R } ^ { p } ) \}$ ; i.e arbitrary linear combinations of the form $\begin{array} { r } { f ( x ) = \sum _ { m } \alpha _ { m } K ( x , y _ { m } ) } \end{array}$ , where each kernel term is viewed as a function of the first argument, and indexed by the second. Suppose that K has an eigen-expansion 

$$
K (x, y) = \sum_ {i = 1} ^ {\infty} \gamma_ {i} \phi_ {i} (x) \phi_ {i} (y)\tag{5.45}
$$

with $\begin{array} { r } { \gamma _ { i } \geq 0 , \sum _ { i = 1 } ^ { \infty } \gamma _ { i } ^ { 2 } < \infty } \end{array}$ . Elements of $\mathcal { H } _ { K }$ have an expansion in terms of these eigen-functions, 

$$
f (x) = \sum_ {i = 1} ^ {\infty} c _ {i} \phi_ {i} (x),\tag{5.46}
$$

with the constraint that 

$$
| | f | | _ {\mathcal {H} _ {K}} ^ {2} \stackrel {\mathrm{def}} {=} \sum_ {i = 1} ^ {\infty} c _ {i} ^ {2} / \gamma_ {i} <   \infty ,\tag{5.47}
$$

where $| | f | | _ { \mathcal { H } _ { K } }$ is the norm induced by $K$ . The penalty functional in (5.42) for the space $\mathcal { H } _ { K }$ is defined to be the squared norm $J ( f ) = | | f | | _ { \mathcal { H } _ { K } } ^ { 2 }$ . The quantity $J ( f )$ can be interpreted as a generalized ridge penalty, where functions with large eigenvalues in the expansion (5.45) get penalized less, and vice versa. 

Rewriting (5.42) we have 

$$
\min _ {f \in \mathcal {H} _ {K}} \left[ \sum_ {i = 1} ^ {N} L (y _ {i}, f (x _ {i})) + \lambda | | f | | _ {\mathcal {H} _ {K}} ^ {2} \right]\tag{5.48}
$$

or equivalently 

$$
\min _ {\{c _ {j} \} _ {1} ^ {\infty}} \left[ \sum_ {i = 1} ^ {N} L (y _ {i}, \sum_ {j = 1} ^ {\infty} c _ {j} \phi_ {j} (x _ {i})) + \lambda \sum_ {j = 1} ^ {\infty} c _ {j} ^ {2} / \gamma_ {j} \right].\tag{5.49}
$$

It can be shown (Wahba, 1990, see also Exercise 5.15) that the solution to (5.48) is finite-dimensional, and has the form 

$$
f (x) = \sum_ {i = 1} ^ {N} \alpha_ {i} K (x, x _ {i}).\tag{5.50}
$$

The basis function $h _ { i } ( x ) = K ( x , x _ { i } )$ (as a function of the first argument) is known as the representer of evaluation at $x _ { i }$ in $\mathcal { H } _ { K }$ , since for $f \in \mathcal { H } _ { K }$ , it is easily seen that $\langle K ( \cdot , x _ { i } ) , f \rangle _ { \mathcal { H } _ { K } } = f ( x _ { i } )$ . Similarly $\langle K ( \cdot , x _ { i } ) , K ( \cdot , x _ { j } ) \rangle _ { \mathcal { H } _ { K } } =$ $K ( x _ { i } , x _ { j } )$ (the reproducing property of $\mathcal { H } _ { K } )$ , and hence 

$$
J (f) = \sum_ {i = 1} ^ {N} \sum_ {j = 1} ^ {N} K (x _ {i}, x _ {j}) \alpha_ {i} \alpha_ {j}\tag{5.51}
$$

for $\begin{array} { r } { f ( x ) = \sum _ { i = 1 } ^ { N } \alpha _ { i } K ( x , x _ { i } ) } \end{array}$ 

In light of (5.50) and (5.51), (5.48) reduces to a finite-dimensional criterion 

$$
\min _ {\boldsymbol {\alpha}} L (\mathbf {y}, \mathbf {K} \boldsymbol {\alpha}) + \lambda \boldsymbol {\alpha} ^ {T} \mathbf {K} \boldsymbol {\alpha}.\tag{5.52}
$$

We are using a vector notation, in which K is the $N \times N$ matrix with ijth entry $K ( x _ { i } , x _ { j } )$ and so on. Simple numerical algorithms can be used to optimize (5.52). This phenomenon, whereby the infinite-dimensional problem (5.48) or (5.49) reduces to a finite dimensional optimization problem, has been dubbed the kernel property in the literature on support-vector machines (see Chapter 12). 

There is a Bayesian interpretation of this class of models, in which f is interpreted as a realization of a zero-mean stationary Gaussian process, with prior covariance function K. The eigen-decomposition produces a series of orthogonal eigen-functions $\phi _ { j } ( x )$ with associated variances $\gamma _ { j }$ . The typical scenario is that “smooth” functions $\phi _ { j }$ have large prior variance, while “rough” $\phi _ { j }$ have small prior variances. The penalty in (5.48) is the contribution of the prior to the joint likelihood, and penalizes more those components with smaller prior variance (compare with (5.43)). 

For simplicity we have dealt with the case here where all members of are penalized, as in (5.48). More generally, there may be some components in that we wish to leave alone, such as the linear functions for cubic smoothing splines in Section 5.4. The multidimensional thin-plate splines of Section 5.7 and tensor product splines fall into this category as well. In these cases there is a more convenient representation $\mathcal { H } = \mathcal { H } _ { 0 } \oplus \mathcal { H } _ { 1 }$ with the null space $\mathcal { H } _ { \mathrm { 0 } }$ consisting of, for example, low degree polynomials in x that do not get penalized. The penalty becomes $J ( f ) = \| P _ { 1 } f \|$ where $P _ { 1 }$ is the orthogonal projection of f onto $\mathcal { H } _ { 1 }$ . The solution has the form $\begin{array} { r } { f ( x ) = \sum _ { j = 1 } ^ { M } \beta _ { j } \bar { h } _ { j } ( x ) + \sum _ { i = 1 } ^ { N } \alpha _ { i } K ( x , x _ { i } ) } \end{array}$ , where the first term represents an expansion in $\mathcal { H } _ { \mathrm { 0 } }$ . From a Bayesian perspective, the coefficients of components in $\mathcal { H } _ { \mathrm { 0 } }$ have improper priors, with infinite variance. 

## 5.8.2 Examples of RKHS

The machinery above is driven by the choice of the kernel K and the loss function L. We consider first regression using squared-error loss. In this case (5.48) specializes to penalized least squares, and the solution can be characterized in two equivalent ways corresponding to (5.49) or (5.52): 

$$
\min _ {\{c _ {j} \} _ {1} ^ {\infty}} \sum_ {i = 1} ^ {N} \left(y _ {i} - \sum_ {j = 1} ^ {\infty} c _ {j} \phi_ {j} (x _ {i})\right) ^ {2} + \lambda \sum_ {j = 1} ^ {\infty} \frac {c _ {j} ^ {2}}{\gamma_ {j}}\tag{5.53}
$$

an infinite-dimensional, generalized ridge regression problem, or 

$$
\min _ {\boldsymbol {\alpha}} (\mathbf {y} - \mathbf {K} \boldsymbol {\alpha}) ^ {T} (\mathbf {y} - \mathbf {K} \boldsymbol {\alpha}) + \lambda \boldsymbol {\alpha} ^ {T} \mathbf {K} \boldsymbol {\alpha}.\tag{5.54}
$$

The solution for α is obtained simply as 

$$
\hat {\boldsymbol {\alpha}} = (\mathbf {K} + \lambda \mathbf {I}) ^ {- 1} \mathbf {y},\tag{5.55}
$$

and 

$$
\hat {f} (x) = \sum_ {j = 1} ^ {N} \hat {\alpha} _ {j} K (x, x _ {j}).\tag{5.56}
$$

The vector of N fitted values is given by 

$$
\hat {\textbf {f}} = \textbf {K} \hat {\alpha}
$$

$$
= \mathbf {K} (\mathbf {K} + \lambda \mathbf {I}) ^ {- 1} \mathbf {y}\tag{5.57}
$$

$$
= \left(\mathbf {I} + \lambda \mathbf {K} ^ {- 1}\right) ^ {- 1} \mathbf {y}.\tag{5.58}
$$

The estimate (5.57) also arises as the kriging estimate of a Gaussian random field in spatial statistics (Cressie, 1993). Compare also (5.58) with the smoothing spline fit (5.17) on page 154. 

## Penalized Polynomial Regression

The kernel $K ( x , y ) \ : = \ : ( \langle x , y \rangle + 1 ) ^ { d }$ (Vapnik, 1996), for $x , y \in \mathbb { R } ^ { p }$ , has $\begin{array} { r } { M = \binom { p + d } { d } } \end{array}$ eigen-functions that span the space of polynomials in $\mathbb { R } ^ { p }$ of total degree d. For example, with $p = 2$ and $d = 2$ ， $M = 6$ and 

$$
{ K ( x , y ) } { = } { 1 + 2 x _ { 1 } y _ { 1 } + 2 x _ { 2 } y _ { 2 } + x _ { 1 } ^ { 2 } y _ { 1 } ^ { 2 } + x _ { 2 } ^ { 2 } y _ { 2 } ^ { 2 } + 2 x _ { 1 } x _ { 2 } y _ { 1 } y _ { 2 } }\tag{5.59}
$$

$$
= \sum_ {m = 1} ^ {M} h _ {m} (x) h _ {m} (y)\tag{5.60}
$$

with 

$$
h (x) ^ {T} = (1, \sqrt {2} x _ {1}, \sqrt {2} x _ {2}, x _ {1} ^ {2}, x _ {2} ^ {2}, \sqrt {2} x _ {1} x _ {2}).\tag{5.61}
$$

One can represent $h$ in terms of the M orthogonal eigen-functions and eigenvalues of $K$ 

$$
h (x) = \mathbf {V D} _ {\gamma} ^ {\frac {1}{2}} \phi (x),\tag{5.62}
$$

where $\mathbf { D } _ { \boldsymbol { \gamma } } = \mathrm { d i a g } ( \gamma _ { 1 } , \gamma _ { 2 } , \dots , \gamma _ { M } )$ , and V is $M \times M$ and orthogonal. 

Suppose we wish to solve the penalized polynomial regression problem 

$$
\min _ {\{\beta_ {m} \} _ {1} ^ {M}} \sum_ {i = 1} ^ {N} \left(y _ {i} - \sum_ {m = 1} ^ {M} \beta_ {m} h _ {m} (x _ {i})\right) ^ {2} + \lambda \sum_ {m = 1} ^ {M} \beta_ {m} ^ {2}.\tag{5.63}
$$

Substituting (5.62) into (5.63), we get an expression of the form (5.53) to optimize (Exercise 5.16). 

The number of basis functions $M = \left( { \begin{array} { c } { p + d } \\ { d } \end{array} } \right)$ can be very large, often much larger than N. Equation (5.55) tells us that if we use the kernel representation for the solution function, we have only to evaluate the kernel $N ^ { 2 }$ times, and can compute the solution in $O ( N ^ { 3 } )$ operations. 

This simplicity is not without implications. Each of the polynomials $h _ { m }$ in (5.61) inherits a scaling factor from the particular form of $K$ , which has a bearing on the impact of the penalty in (5.63). We elaborate on this in the next section. 

![image](<Images/05_Basis_Expansions_and_Regularization_image_031.jpg>)



FIGURE 5.13. Radial kernels $k _ { k } ( x )$ for the mixture data, with scale parameter $\nu = 1$ . The kernels are centered at five points $x _ { m }$ chosen at random from the 200.


## Gaussian Radial Basis Functions

In the preceding example, the kernel is chosen because it represents an expansion of polynomials and can conveniently compute high-dimensional inner products. In this example the kernel is chosen because of its functional form in the representation (5.50). 

The Gaussian kernel $K ( x , y ) = e ^ { - \nu | | x - y | | ^ { 2 } }$ along with squared-error loss, for example, leads to a regression model that is an expansion in Gaussian radial basis functions, 

$$
k _ {m} (x) = e ^ {- \nu | | x - x _ {m} | | ^ {2}}, m = 1, \ldots , N,\tag{5.64}
$$

each one centered at one of the training feature vectors $x _ { m }$ . The coefficients are estimated using (5.54). 

Figure 5.13 illustrates radial kernels in $\mathbb { R } ^ { 1 }$ using the first coordinate of the mixture example from Chapter 2. We show five of the 200 kernel basis functions $k _ { m } ( x ) = K ( x , x _ { m } )$ 

Figure 5.14 illustrates the implicit feature space for the radial kernel with $\boldsymbol { x } \in \mathbb { R } ^ { 1 }$ . We computed the $2 0 0 \times 2 0 0$ kernel matrix K, and its eigendecomposition $\mathbf { \Phi } \mathbf { \Phi } \mathbf { \Phi } \mathbf { \Phi } \mathbf { \Phi } \mathbf { \Phi } \mathbf { \bar { \Phi } } ^ { T }$ . We can think of the columns of Φ and the corresponding eigenvalues in $\mathbf { D } _ { \gamma }$ as empirical estimates of the eigen expansion $( 5 . 4 5 ) ^ { 2 }$ . Although the eigenvectors are discrete, we can represent them as functions on $\mathbb { R } ^ { 1 }$ (Exercise 5.17). Figure 5.15 shows the largest 50 eigenvalues of K. The leading eigenfunctions are smooth, and they are successively more wiggly as the order increases. This brings to life the penalty in (5.49), where we see the coefficients of higher-order functions get penalized more than lower-order ones. The right panel in Figure 5.14 shows the corresponding feature space representation of the eigenfunctions 


Orthonormal Basis Φ


![image](<Images/05_Basis_Expansions_and_Regularization_image_032.jpg>)



Feature Space H


![image](<Images/05_Basis_Expansions_and_Regularization_image_033.jpg>)



FIGURE 5.14. (Left panel) The first 16 normalized eigenvectors of K, the 200 200 kernel matrix for the first coordinate of the mixture data. These are viewed as estimates $\hat { \phi } _ { \ell }$ of the eigenfunctions in (5.45), and are represented as functions in $\mathbb { R } ^ { 1 }$ with the observed values superimposed in color. They are arranged in rows, starting at the top left. (Right panel) Rescaled versions $h _ { \ell } = \sqrt { \hat { \gamma } } _ { \ell } \hat { \phi } _ { \ell }$ of the functions in the left panel, for which the kernel computes the “inner product.”


![image](<Images/05_Basis_Expansions_and_Regularization_image_034.jpg>)



FIGURE 5.15. The largest 50 eigenvalues of K; all those beyond the 30th are effectively zero.


$$
h _ {\ell} (x) = \sqrt {\hat {\gamma}} _ {\ell} \hat {\phi} _ {\ell} (x), \ell = 1, \dots , N.\tag{5.65}
$$

Note that $\langle h ( x _ { i } ) , h ( x _ { i ^ { \prime } } ) \rangle = K ( x _ { i } , x _ { i ^ { \prime } } )$ . The scaling by the eigenvalues quickly shrinks most of the functions down to zero, leaving an effective dimension of about 12 in this case. The corresponding optimization problem is a standard ridge regression, as in (5.63). So although in principle the implicit feature space is infinite dimensional, the effective dimension is dramatically lower because of the relative amounts of shrinkage applied to each basis function. The kernel scale parameter $\nu$ plays a role here as well; larger ν implies more local $k _ { m }$ functions, and increases the effective dimension of the feature space. See Hastie and Zhu (2006) for more details. 

It is also known (Girosi et al., 1995) that a thin-plate spline (Section 5.7) is an expansion in radial basis functions, generated by the kernel 

$$
K (x, y) = \| x - y \| ^ {2} \log (\| x - y \|).\tag{5.66}
$$

Radial basis functions are discussed in more detail in Section 6.7. 

## Support Vector Classifiers

The support vector machines of Chapter 12 for a two-class classification problem have the form $\begin{array} { r } { f ( x ) = \alpha _ { 0 } + \sum _ { i = 1 } ^ { N } \alpha _ { i } K ( x , x _ { i } ) } \end{array}$ , where the parameters are chosen to minimize 

$$
\min _ {\alpha_ {0}, \boldsymbol {\alpha}} \left\{\sum_ {i = 1} ^ {N} [ 1 - y _ {i} f (x _ {i}) ] _ {+} + \frac {\lambda}{2} \boldsymbol {\alpha} ^ {T} \mathbf {K} \boldsymbol {\alpha} \right\},\tag{5.67}
$$

where $y _ { i } \in \{ - 1 , 1 \}$ , and $[ z ] _ { + }$ denotes the positive part of $z .$ This can be viewed as a quadratic optimization problem with linear constraints, and requires a quadratic programming algorithm for its solution. The name support vector arises from the fact that typically many of the $\hat { \alpha } _ { i } = 0$ [due to the piecewise-zero nature of the loss function in (5.67)], and so $\hat { f }$ is an expansion in a subset of the $K ( \cdot , x _ { i } )$ . See Section 12.3.3 for more details. 

## 5.9 Wavelet Smoothing

We have seen two different modes of operation with dictionaries of basis functions. With regression splines, we select a subset of the bases, using either subject-matter knowledge, or else automatically. The more adaptive procedures such as MARS (Chapter 9) can capture both smooth and nonsmooth behavior. With smoothing splines, we use a complete basis, but then shrink the coefficients toward smoothness. 

![image](<Images/05_Basis_Expansions_and_Regularization_image_035.jpg>)



FIGURE 5.16. Some selected wavelets at different translations and dilations for the Haar and symmlet families. The functions have been scaled to suit the display.


Wavelets typically use a complete orthonormal basis to represent functions, but then shrink and select the coefficients toward a sparse representation. Just as a smooth function can be represented by a few spline basis functions, a mostly flat function with a few isolated bumps can be represented with a few (bumpy) basis functions. Wavelets bases are very popular in signal processing and compression, since they are able to represent both smooth and/or locally bumpy functions in an efficient way—a phenomenon dubbed time and frequency localization. In contrast, the traditional Fourier basis allows only frequency localization. 

Before we give details, let’s look at the Haar wavelets in the left panel of Figure 5.16 to get an intuitive idea of how wavelet smoothing works. The vertical axis indicates the scale (frequency) of the wavelets, from low scale at the bottom to high scale at the top. At each scale the wavelets are “packed in” side-by-side to completely fill the time axis: we have only shown a selected subset. Wavelet smoothing fits the coefficients for this basis by least squares, and then thresholds (discards, filters) the smaller coefficients. Since there are many basis functions at each scale, it can use bases where it needs them and discard the ones it does not need, to achieve time and frequency localization. The Haar wavelets are simple to understand, but not smooth enough for most purposes. The symmlet wavelets in the right panel of Figure 5.16 have the same orthonormal properties, but are smoother. 

Figure 5.17 displays an NMR (nuclear magnetic resonance) signal, which appears to be composed of smooth components and isolated spikes, plus some noise. The wavelet transform, using a symmlet basis, is shown in the lower left panel. The wavelet coefficients are arranged in rows, from lowest scale at the bottom, to highest scale at the top. The length of each line segment indicates the size of the coefficient. The bottom right panel shows the wavelet coefficients after they have been thresholded. The threshold procedure, given below in equation (5.69), is the same soft-thresholding rule that arises in the lasso procedure for linear regression (Section 3.4.2). Notice that many of the smaller coefficients have been set to zero. The green curve in the top panel shows the back-transform of the thresholded coefficients: this is the smoothed version of the original signal. In the next section we give the details of this process, including the construction of wavelets and the thresholding rule. 

## 5.9.1 Wavelet Bases and the Wavelet Transform

![image](<Images/05_Basis_Expansions_and_Regularization_image_036.jpg>)


In this section we give details on the construction and filtering of wavelets. Wavelet bases are generated by translations and dilations of a single scaling function $\phi ( x )$ (also known as the $f a t h e r )$ . The red curves in Figure 5.18 are the Haar and symmlet-8 scaling functions. The Haar basis is particularly easy to understand, especially for anyone with experience in analysis of variance or trees, since it produces a piecewise-constant representation. Thus if $\phi ( x ) = I ( x \in [ 0 , 1 ] )$ , then $\phi _ { 0 , k } ( x ) = \phi ( x - k )$ , k an integer, generates an orthonormal basis for functions with jumps at the integers. Call this $r e f \mathrm { - }$ erence space $V _ { 0 }$ . The dilations $\phi _ { 1 , k } ( x ) = \sqrt { 2 } \phi ( 2 x - k )$ form an orthonormal basis for a space $V _ { 1 } ~ \supset ~ V _ { 0 }$ of functions piecewise constant on intervals of length $\begin{array} { l } { { \frac { 1 } { 2 } } } \end{array}$ . In fact, more generally we have $\cdots \supset V _ { 1 } \supset V _ { 0 } \supset V _ { - 1 } \supset \cdots$ where each $V _ { j }$ is spanned by $\phi _ { j , k } = 2 ^ { j / 2 } \phi ( 2 ^ { j } x - k )$ 

Now to the definition of wavelets. In analysis of variance, we often represent a pair of means $\mu _ { 1 }$ and $\mu _ { 2 }$ by their grand mean $\begin{array} { r } { \mu = \frac { 1 } { 2 } ( \mu _ { 1 } + \mu _ { 2 } ) } \end{array}$ , and then a contrast $\begin{array} { r } { \alpha = \frac { 1 } { 2 } ( \mu _ { 1 } - \mu _ { 2 } ) } \end{array}$ . A simplification occurs if the contrast α is very small, because then we can set it to zero. In a similar manner we might represent a function in $V _ { j + 1 }$ by a component in $V _ { j }$ plus the component in the orthogonal complement $W _ { j }$ of $V _ { j }$ to $V _ { j + 1 }$ , written as $V _ { j + 1 } = V _ { j } \oplus W _ { j }$ The component in $W _ { j }$ represents detail, and we might wish to set some elements of this component to zero. It is easy to see that the functions $\psi ( x - k )$ 


NMR Signal


![image](<Images/05_Basis_Expansions_and_Regularization_image_037.jpg>)



Wavelet Transform - Original Signa


![image](<Images/05_Basis_Expansions_and_Regularization_image_038.jpg>)



Wavelet Transform - WaveShrunk Signal


![image](<Images/05_Basis_Expansions_and_Regularization_image_039.jpg>)



FIGURE 5.17. The top panel shows an NMR signal, with the wavelet-shrunk version superimposed in green. The lower left panel represents the wavelet transform of the original signal, down to $V _ { 4 }$ , using the symmlet-8 basis. Each coefficient is represented by the height (positive or negative) of the vertical bar. The lower right panel represents the wavelet coefficients after being shrunken using the waveshrink function in S-PLUS, which implements the SureShrink method of wavelet adaptation of Donoho and Johnstone.


![image](<Images/05_Basis_Expansions_and_Regularization_image_040.jpg>)


![image](<Images/05_Basis_Expansions_and_Regularization_image_041.jpg>)


![image](<Images/05_Basis_Expansions_and_Regularization_image_042.jpg>)



ψ(x)


![image](<Images/05_Basis_Expansions_and_Regularization_image_043.jpg>)



ψ(x)



FIGURE 5.18. The Haar and symmlet father (scaling) wavelet $\phi ( x )$ and mother wavelet $\psi ( x )$


generated by the mother wavelet $\psi ( x ) = \phi ( 2 x ) - \phi ( 2 x - 1 )$ form an orthonormal basis for $W _ { 0 }$ for the Haar family. Likewise $\psi _ { j , k } = 2 ^ { j / 2 } \psi ( 2 ^ { j } x - k )$ form a basis for $W _ { j }$ 

Now $V _ { j + 1 } = V _ { j } \oplus W _ { j } = V _ { j - 1 } \oplus W _ { j - 1 } \oplus W _ { j }$ , so besides representing a function by its level-j detail and level-j rough components, the latter can be broken down to level-(j  1) detail and rough, and so on. Finally we get a representation of the form $V _ { J } = V _ { 0 } \oplus W _ { 0 } \oplus W _ { 1 } \cdot \cdot \cdot \oplus W _ { J - 1 }$ . Figure 5.16 on page 175 shows particular wavelets $\psi _ { j , k } ( x )$ 

Notice that since these spaces are orthogonal, all the basis functions are orthonormal. In fact, if the domain is discrete with $N = 2 ^ { J }$ (time) points, this is as far as we can go. There are $2 ^ { j }$ basis elements at level $j ,$ , and adding up, we have a total of $2 ^ { J } - 1$ elements in the $W _ { j }$ , and one in $V _ { 0 }$ This structured orthonormal basis allows for a multiresolution analysis, which we illustrate in the next section. 

While helpful for understanding the construction above, the Haar basis is often too coarse for practical purposes. Fortunately, many clever wavelet bases have been invented. Figures 5.16 and 5.18 include the Daubechies symmlet-8 basis. This basis has smoother elements than the corresponding Haar basis, but there is a tradeoff: 

Each wavelet has a support covering 15 consecutive time intervals, rather than one for the Haar basis. More generally, the symmlet-p family has a support of $2 p - 1$ consecutive intervals. The wider the support, the more time the wavelet has to die to zero, and so it can achieve this more smoothly. Note that the effective support seems to be much narrower. 

The symmlet-p wavelet $\psi ( x )$ has $p$ vanishing moments; that is, 

$$
\int \psi (x) x ^ {j} d x = 0, j = 0, \dots , p - 1.
$$

One implication is that any order-p polynomial over the $N = 2 ^ { J }$ times points is reproduced exactly in $V _ { 0 }$ (Exercise 5.18). In this sense $V _ { 0 }$ is equivalent to the null space of the smoothing-spline penalty. The Haar wavelets have one vanishing moment, and $V _ { 0 }$ can reproduce any constant function. 

The symmlet-p scaling functions are one of many families of wavelet generators. The operations are similar to those for the Haar basis: 

If $V _ { 0 }$ is spanned by $\phi ( x - k )$ , then $V _ { 1 } \supset V _ { 0 }$ is spanned by $\phi _ { 1 , k } ( x ) =$ ${ \sqrt { 2 } } \phi ( 2 x - k )$ and $\begin{array} { r } { \phi ( x ) = \sum _ { k \in \mathcal { Z } } h ( k ) \phi _ { 1 , k } ( x ) } \end{array}$ , for some filter coefficients $h ( k )$ 

$W _ { 0 }$ is spanned by $\begin{array} { r } { \psi ( x ) = \sum _ { k \in \mathcal Z } g ( k ) \phi _ { 1 , k } ( x ) } \end{array}$ , with filter coefficients $g ( k ) = ( - 1 ) ^ { 1 - k } h ( 1 - k )$ 

## 5.9.2 Adaptive Wavelet Filtering

![image](<Images/05_Basis_Expansions_and_Regularization_image_044.jpg>)


Wavelets are particularly useful when the data are measured on a uniform lattice, such as a discretized signal, image, or a time series. We will focus on the one-dimensional case, and having $N = 2 ^ { J }$ lattice-points is convenient. Suppose y is the response vector, and W is the $N \times N$ orthonormal wavelet basis matrix evaluated at the N uniformly spaced observations. Then $\mathbf { y } ^ { * } =$ $\mathbf { W } ^ { T } \mathbf { y }$ is called the wavelet transform of $\mathbf { y }$ (and is the full least squares regression coefficient). A popular method for adaptive wavelet fitting is known as SURE shrinkage (Stein Unbiased Risk Estimation, Donoho and Johnstone (1994)). We start with the criterion 

$$
\min _ {\boldsymbol {\theta}} | | \mathbf {y} - \mathbf {W} \boldsymbol {\theta} | | _ {2} ^ {2} + 2 \lambda | | \boldsymbol {\theta} | | _ {1},\tag{5.68}
$$

which is the same as the lasso criterion in Chapter 3. Because W is orthonormal, this leads to the simple solution: 

$$
\hat {\theta} _ {j} = \mathrm{sign} (y _ {j} ^ {*}) (| y _ {j} ^ {*} | - \lambda) _ {+}.\tag{5.69}
$$

The least squares coefficients are translated toward zero, and truncated at zero. The fitted function (vector) is then given by the inverse wavelet transform $\hat { \mathbf { f } } = \mathbf { W } \hat { \boldsymbol { \theta } }$ 

A simple choice for λ is $\lambda = \sigma \sqrt { 2 \log N }$ , where $\sigma$ is an estimate of the standard deviation of the noise. We can give some motivation for this choice. Since W is an orthonormal transformation, if the elements of y are white noise (independent Gaussian variates with mean 0 and variance $\sigma ^ { 2 } )$ , then so are $\mathbf { y } ^ { * }$ . Furthermore if random variables $Z _ { 1 } , Z _ { 2 } , \dots , Z _ { N }$ are white noise, the expected maximum of $| Z _ { j } | , j = 1 , \dotsc , N$ is approximately $\sigma { \sqrt { 2 \log N } }$ Hence all coefficients below $\sigma { \sqrt { 2 \log N } }$ are likely to be noise and are set to zero. 

The space W could be any basis of orthonormal functions: polynomials, natural splines or cosinusoids. What makes wavelets special is the particular form of basis functions used, which allows for a representation localized in time and in frequency. 

Let’s look again at the NMR signal of Figure 5.17. The wavelet transform was computed using a symmlet 8 basis. Notice that the coefficients do not descend all the way to $V _ { 0 }$ , but stop at $V _ { 4 }$ which has 16 basis functions. As we ascend to each level of detail, the coefficients get smaller, except in locations where spiky behavior is present. The wavelet coefficients represent characteristics of the signal localized in time (the basis functions at each level are translations of each other) and localized in frequency. Each dilation increases the detail by a factor of two, and in this sense corresponds to doubling the frequency in a traditional Fourier representation. In fact, a more mathematical understanding of wavelets reveals that the wavelets at a particular scale have a Fourier transform that is restricted to a limited range or octave of frequencies. 

The shrinking/truncation in the right panel was achieved using the SURE approach described in the introduction to this section. The orthonormal $N \times N$ basis matrix W has columns which are the wavelet basis functions evaluated at the N time points. In particular, in this case there will be 16 columns corresponding to the $\phi _ { 4 , k } ( x )$ , and the remainder devoted to the $\psi _ { j , k } ( x ) , j = 4 , \ldots , 1 1$ . In practice λ depends on the noise variance, and has to be estimated from the data (such as the variance of the coefficients at the highest level). 

Notice the similarity between the SURE criterion (5.68) on page 179, and the smoothing spline criterion (5.21) on page 156: 

Both are hierarchically structured from coarse to fine detail, although wavelets are also localized in time within each resolution level. 

The splines build in a bias toward smooth functions by imposing differential shrinking constants $d _ { k }$ . Early versions of SURE shrinkage treated all scales equally. The S+wavelets function waveshrink() has many options, some of which allow for differential shrinkage. 

The spline $L _ { 2 }$ penalty cause pure shrinkage, while the SURE $L _ { 1 }$ penalty does shrinkage and selection. 

More generally smoothing splines achieve compression of the original signal by imposing smoothness, while wavelets impose sparsity. Figure 5.19 compares a wavelet fit (using SURE shrinkage) to a smoothing spline fit (using cross-validation) on two examples different in nature. For the NMR data in the upper panel, the smoothing spline introduces detail everywhere in order to capture the detail in the isolated spikes; the wavelet fit nicely localizes the spikes. In the lower panel, the true function is smooth, and the noise is relatively high. The wavelet fit has let in some additional and unnecessary wiggles—a price it pays in variance for the additional adaptivity. 

The wavelet transform is not performed by matrix multiplication as in $\mathbf { y } ^ { * } = \mathbf { W } ^ { T } \mathbf { y }$ . In fact, using clever pyramidal schemes $\mathbf { y } ^ { * }$ can be obtained in $O ( N )$ computations, which is even faster than the N log(N) of the fast Fourier transform (FFT). While the general construction is beyond the scope of this book, it is easy to see for the Haar basis (Exercise 5.19). Likewise, the inverse wavelet transform Wθ<sup>ˆ</sup> is also $O ( N )$ 

This has been a very brief glimpse of this vast and growing field. There is a very large mathematical and computational base built on wavelets. Modern image compression is often performed using two-dimensional wavelet representations. 

## Bibliographic Notes

Splines and B-splines are discussed in detail in de Boor (1978). Green and Silverman (1994) and Wahba (1990) give a thorough treatment of smoothing splines and thin-plate splines; the latter also covers reproducing kernel Hilbert spaces. See also Girosi et al. (1995) and Evgeniou et al. (2000) for connections between many nonparametric regression techniques using RKHS approaches. Modeling functional data, as in Section 5.2.3, is covered in detail in Ramsay and Silverman (1997). 

Daubechies (1992) is a classic and mathematical treatment of wavelets. Other useful sources are Chui (1992) and Wickerhauser (1994). Donoho and Johnstone (1994) developed the SURE shrinkage and selection technology from a statistical estimation framework; see also Vidakovic (1999). Bruce and Gao (1996) is a useful applied introduction, which also describes the wavelet software in S-PLUS. 

## Exercises

Ex. 5.1 Show that the truncated power basis functions in (5.3) represent a basis for a cubic spline with the two knots as indicated. 

![image](<Images/05_Basis_Expansions_and_Regularization_image_045.jpg>)


![image](<Images/05_Basis_Expansions_and_Regularization_image_046.jpg>)



FIGURE 5.19. Wavelet smoothing compared with smoothing splines on two examples. Each panel compares the SURE-shrunk wavelet fit to the cross-validated smoothing spline fit.


Ex. 5.2 Suppose that $B _ { i , M } ( x )$ is an order-M B-spline defined in the Appendix on page 186 through the sequence (5.77)–(5.78). 

(a) Show by induction that $B _ { i , M } ( x ) = 0$ for $x \notin [ \tau _ { i } , \tau _ { i + M } ]$ . This shows, for example, that the support of cubic B-splines is at most 5 knots. 

(b) Show by induction that $B _ { i , M } ( x ) > 0$ for $x \in ( \tau _ { i } , \tau _ { i + M } )$ . The B-splines are positive in the interior of their support. 

(c) Show by induction that $\begin{array} { r } { \sum _ { i = 1 } ^ { K + M } B _ { i , M } ( x ) = 1 \forall x \in [ \xi _ { 0 } , \xi _ { K + 1 } ] , } \end{array}$ 

(d) Show that $B _ { i , M }$ is a piecewise polynomial of order M (degree $M - 1 )$ on $[ \xi _ { 0 } , \xi _ { K + 1 } ]$ , with breaks only at the knots $\xi _ { 1 } , \dots , \xi _ { K }$ 

(e) Show that an order-M B-spline basis function is the density function of a convolution of M uniform random variables. 

Ex. 5.3 Write a program to reproduce Figure 5.3 on page 145. 

Ex. 5.4 Consider the truncated power series representation for cubic splines with K interior knots. Let 

$$
f (X) = \sum_ {j = 0} ^ {3} \beta_ {j} X ^ {j} + \sum_ {k = 1} ^ {K} \theta_ {k} (X - \xi_ {k}) _ {+} ^ {3}.\tag{5.70}
$$

Prove that the natural boundary conditions for natural cubic splines (Section 5.2.1) imply the following linear constraints on the coefficients: 

$$
\begin{array}{r l} & {\beta_ {2} = 0, \qquad \sum_ {k = 1} ^ {K} \theta_ {k} = 0,} \\ & {\beta_ {3} = 0, \qquad \sum_ {k = 1} ^ {K} \xi_ {k} \theta_ {k} = 0.} \end{array}\tag{5.71}
$$

Hence derive the basis (5.4) and (5.5). 

Ex. 5.5 Write a program to classify the phoneme data using a quadratic discriminant analysis (Section 4.3). Since there are many correlated features, you should filter them using a smooth basis of natural cubic splines (Section 5.2.3). Decide beforehand on a series of five different choices for the number and position of the knots, and use tenfold cross-validation to make the final selection. The phoneme data are available from the book website www-stat.stanford.edu/ElemStatLearn. 

Ex. 5.6 Suppose you wish to fit a periodic function, with a known period T. Describe how you could modify the truncated power series basis to achieve this goal. 

Ex. 5.7 Derivation of smoothing splines (Green and Silverman, 1994). Suppose that $N \geq 2$ , and that g is the natural cubic spline interpolant to the pairs $\{ x _ { i } , z _ { i } \} _ { 1 } ^ { N }$ , with $a < x _ { 1 } < \cdot \cdot \cdot < x _ { N } < b $ . This is a natural spline with a knot at every $x _ { i } { \mathrm { i } }$ ; being an N-dimensional space of functions, we can determine the coefficients such that it interpolates the sequence $z _ { i }$ exactly. Let $\tilde { g }$ be any other differentiable function on [a, b] that interpolates the N pairs. 

(a) Let $h ( x ) = \tilde { g } ( x ) - g ( x )$ . Use integration by parts and the fact that $g$ is a natural cubic spline to show that 

$$
\begin{array}{r c l} \int_ {a} ^ {b} g ^ {\prime \prime} (x) h ^ {\prime \prime} (x) d x & = & - \sum_ {j = 1} ^ {N - 1} g ^ {\prime \prime \prime} (x _ {j} ^ {+}) \{h (x _ {j + 1}) - h (x _ {j}) \} \\ & = & 0. \end{array}\tag{5.72}
$$

(b) Hence show that 

$$
\int_ {a} ^ {b} \tilde {g} ^ {\prime \prime} (t) ^ {2} d t \geq \int_ {a} ^ {b} g ^ {\prime \prime} (t) ^ {2} d t,
$$

and that equality can only hold if h is identically zero in $[ a , b ]$ 

(c) Consider the penalized least squares problem 

$$
\min _ {f} \left[ \sum_ {i = 1} ^ {N} (y _ {i} - f (x _ {i})) ^ {2} + \lambda \int_ {a} ^ {b} f ^ {\prime \prime} (t) ^ {2} d t \right].
$$

Use (b) to argue that the minimizer must be a cubic spline with knots at each of the $x _ { i }$ 

Ex. 5.8 In the appendix to this chapter we show how the smoothing spline computations could be more efficiently carried out using a $( N + 4 )$ dimensional basis of B-splines. Describe a slightly simpler scheme using a (N +2) dimensional B-spline basis defined on the $N - 2$ interior knots. 

Ex. 5.9 Derive the Reinsch form $\mathbf { S } _ { \lambda } = ( \mathbf { I } + \lambda \mathbf { K } ) ^ { - 1 }$ for the smoothing spline. 

Ex. 5.10 Derive an expression for $\mathrm { V a r } ( \hat { f } _ { \lambda } ( x _ { 0 } ) )$ and $\mathrm { b i a s } ( \hat { f } _ { \lambda } ( x _ { 0 } ) )$ . Using the example (5.22), create a version of Figure 5.9 where the mean and several (pointwise) quantiles of $\hat { f } _ { \lambda } ( x )$ are shown. 

Ex. 5.11 Prove that for a smoothing spline the null space of K is spanned by functions linear in $X$ 

Ex. 5.12 Characterize the solution to the following problem, 

$$
\min _ {f} \operatorname{RSS} (f, \lambda) = \sum_ {i = 1} ^ {N} w _ {i} \left\{y _ {i} - f \left(x _ {i}\right) \right\} ^ {2} + \lambda \int \left\{f ^ {\prime \prime} (t) \right\} ^ {2} d t,\tag{5.73}
$$

where the $w _ { i } \geq 0$ are observation weights. 

Characterize the solution to the smoothing spline problem (5.9) when the training data have ties in $X$ 

Ex. 5.13 You have fitted a smoothing spline $\hat { f } _ { \lambda }$ to a sample of N pairs $( x _ { i } , y _ { i } )$ . Suppose you augment your original sample with the pair $x _ { 0 } , { \hat { f } } _ { \lambda } ( x _ { 0 } )$ ， and refit; describe the result. Use this to derive the N-fold cross-validation formula (5.26). 

Ex. 5.14 Derive the constraints on the $\alpha _ { j }$ in the thin-plate spline expansion (5.39) to guarantee that the penalty $J ( f )$ is finite. How else could one ensure that the penalty was finite? 

Ex. 5.15 This exercise derives some of the results quoted in Section 5.8.1. Suppose $K ( x , y )$ satisfying the conditions (5.45) and let $f ( x ) \in { \mathcal { H } } _ { K }$ . Show that 

(a) $\langle K ( \cdot , x _ { i } ) , f \rangle _ { \mathcal { H } _ { K } } = f ( x _ { i } )$ 

(b) $\langle K ( \cdot , x _ { i } ) , K ( \cdot , x _ { j } ) \rangle _ { \mathcal { H } _ { K } } = K ( x _ { i } , x _ { j } )$ 

(c) If $\begin{array} { r } { g ( x ) = \sum _ { i = 1 } ^ { N } \alpha _ { i } K ( x , x _ { i } ) } \end{array}$ , then 

$$
J (g) = \sum_ {i = 1} ^ {N} \sum_ {j = 1} ^ {N} K (x _ {i}, x _ {j}) \alpha_ {i} \alpha_ {j}.
$$

Suppose that $\tilde { g } ( x ) = g ( x ) + \rho ( x )$ , with ${ \boldsymbol \rho } ( { \boldsymbol { x } } ) \in \mathcal { H } _ { K }$ , and orthogonal in $\mathcal { H } _ { K }$ to each of $K ( x , x _ { i } ) , \ i = 1 , \dots , N$ . Show that 

(d) 

$$
\sum_ {i = 1} ^ {N} L \left(y _ {i}, \tilde {g} \left(x _ {i}\right)\right) + \lambda J (\tilde {g}) \geq \sum_ {i = 1} ^ {N} L \left(y _ {i}, g \left(x _ {i}\right)\right) + \lambda J (g)\tag{5.74}
$$

with equality if $\rho ( x ) = 0$ 

Ex. 5.16 Consider the ridge regression problem (5.53), and assume $M \geq N$ Assume you have a kernel K that computes the inner product $K ( x , y ) =$ $\begin{array} { r } { \sum _ { m = 1 } ^ { M } h _ { m } ( x ) h _ { m } ( y ) } \end{array}$ 

(a) Derive (5.62) on page 171 in the text. How would you compute the matrices V and $\mathbf { D } _ { \gamma }$ , given $K ?$ Hence show that (5.63) is equivalent to (5.53). 

(b) Show that 

$$
\begin{array}{r c l} \hat {\mathbf {f}} & = & \mathbf {H} \hat {\boldsymbol {\beta}} \\ & = & \mathbf {K} (\mathbf {K} + \lambda \mathbf {I}) ^ {- 1} \mathbf {y}, \end{array}\tag{5.75}
$$

where H is the $N \times M$ matrix of evaluations $h _ { m } ( x _ { i } )$ , and ${ \bf K } = { \bf H } { \bf H } ^ { T }$ the $N \times N$ matrix of inner-products $h ( x _ { i } ) ^ { T } h ( x _ { j } )$ 

(c) Show that 

$$
\begin{array}{r c l} \hat {f} (x) & = & h (x) ^ {T} \hat {\pmb {\beta}} \\ & = & \sum_ {i = 1} ^ {N} K (x, x _ {i}) \hat {\pmb {\alpha}} _ {i} \end{array}\tag{5.76}
$$

and $\hat { \pmb { \alpha } } = ( \mathbf { K } + \lambda \mathbf { I } ) ^ { - 1 } \mathbf { y } .$ 

(d) How would you modify your solution if $M < N ?$ 

Ex. 5.17 Show how to convert the discrete eigen-decomposition of K in Section 5.8.2 to estimates of the eigenfunctions of K. 

Ex. 5.18 The wavelet function $\psi ( x )$ of the symmlet-p wavelet basis has vanishing moments up to order $p .$ Show that this implies that polynomials of order p are represented exactly in $V _ { 0 }$ , defined on page 176. 

Ex. 5.19 Show that the Haar wavelet transform of a signal of length $N = 2 ^ { J }$ can be computed in $O ( N )$ computations. 

## Appendix: Computations for Splines

![image](<Images/05_Basis_Expansions_and_Regularization_image_047.jpg>)


In this Appendix, we describe the B-spline basis for representing polynomial splines. We also discuss their use in the computations of smoothing splines. 

## B-splines

Before we can get started, we need to augment the knot sequence defined in Section 5.2. Let $\xi _ { 0 } < \xi _ { 1 }$ and $\xi _ { K } < \xi _ { K + 1 }$ be two boundary knots, which typically define the domain over which we wish to evaluate our spline. We now define the augmented knot sequence τ such that 

$$
\bullet \tau_ {1} \leq \tau_ {2} \leq \dots \leq \tau_ {M} \leq \xi_ {0};
$$

τ<sub>j+M</sub> = ξ<sub>j</sub> , j = 1,    , K; 

$$
\bullet \xi_ {K + 1} \leq \tau_ {K + M + 1} \leq \tau_ {K + M + 2} \leq \dots \leq \tau_ {K + 2 M}.
$$

The actual values of these additional knots beyond the boundary are arbitrary, and it is customary to make them all the same and equal to $\xi _ { 0 }$ and $\xi _ { K + 1 }$ , respectively. 

Denote by $B _ { i , m } ( x )$ the ith B-spline basis function of order $m$ for the knot-sequence τ , $m \leq M$ . They are defined recursively in terms of divided 

differences as follows: 

$$
B _ {i, 1} (x) = \left\{ \begin{array}{l l} 1 & \text { if } \tau_ {i} \leq x <   \tau_ {i + 1} \\ 0 & \text { otherwise } \end{array} \right.\tag{5.77}
$$

for $i = 1 , \dots , K + 2 M - 1$ . These are also known as Haar basis functions. 

$$
\begin{array}{r c l} B _ {i, m} (x) & = & \frac {x - \tau_ {i}}{\tau_ {i + m - 1} - \tau_ {i}} B _ {i, m - 1} (x) + \frac {\tau_ {i + m} - x}{\tau_ {i + m} - \tau_ {i + 1}} B _ {i + 1, m - 1} (x) \\ \text { for } i = 1, \ldots , K + 2 M - m. \end{array}\tag{5.78}
$$

Thus with $M = 4 , B _ { i , 4 } , i = 1 , \cdots , K + 4$ are the $K + 4$ cubic B-spline basis functions for the knot sequence ξ. This recursion can be continued and will generate the B-spline basis for any order spline. Figure 5.20 shows the sequence of B-splines up to order four with knots at the points $0 . 0 , 0 . 1 , \dots , 1 . 0$ . Since we have created some duplicate knots, some care has to be taken to avoid division by zero. If we adopt the convention that $B _ { i , 1 } = 0 { \mathrm { ~ i f ~ } } \tau _ { i } = \tau _ { i + 1 }$ , then by induction $B _ { i , m } = 0 { \mathrm { ~ i f ~ } } \tau _ { i } = \tau _ { i + 1 } =$ $\dots = \tau _ { i + m }$ . Note also that in the construction above, only the subset $B _ { i , m } , \ i \ = \ M - m + 1 , . . . , M + K$ are required for the B-spline basis of order $m < M$ with knots $\xi .$ 

To fully understand the properties of these functions, and to show that they do indeed span the space of cubic splines for the knot sequence, requires additional mathematical machinery, including the properties of divided differences. Exercise 5.2 explores these issues. 

The scope of B-splines is in fact bigger than advertised here, and has to do with knot duplication. If we duplicate an interior knot in the construction of the $\tau$ sequence above, and then generate the B-spline sequence as before, the resulting basis spans the space of piecewise polynomials with one less continuous derivative at the duplicated knot. In general, if in addition to the repeated boundary knots, we include the interior knot $\xi _ { j }$ $1 \leq r _ { j } \leq M$ times, then the lowest-order derivative to be discontinuous at $x = \xi _ { j }$ will be order $M - r _ { j }$ . Thus for cubic splines with no repeats, $r _ { j } = 1 , j = 1 , \ldots , K$ , and at each interior knot the third derivatives (4 1) are discontinuous. Repeating the jth knot three times leads to a discontinuous 1st derivative; repeating it four times leads to a discontinuous zeroth derivative, i.e., the function is discontinuous at $x = \xi _ { j }$ . This is exactly what happens at the boundary knots; we repeat the knots M times, so the spline becomes discontinuous at the boundary knots (i.e., undefined beyond the boundary). 

The local support of B-splines has important computational implications, especially when the number of knots K is large. Least squares computations with N observations and $K + M$ variables (basis functions) take $O ( N ( K + M ) ^ { 2 } + ( K + M ) ^ { 3 } )$ flops (floating point operations.) If K is some appreciable fraction of N, this leads to $O ( N ^ { 3 } )$ algorithms which becomes unacceptable for large N. If the N observations are sorted, the $N \times ( K { + } M )$ regression matrix consisting of the $K + M$ B-spline basis functions evaluated at the N points has many zeros, which can be exploited to reduce the computational complexity back to $O ( N )$ . We take this up further in the next section. 


B-splines of Order 1


![image](<Images/05_Basis_Expansions_and_Regularization_image_048.jpg>)



B-splines of Order 2


![image](<Images/05_Basis_Expansions_and_Regularization_image_049.jpg>)



B-splines of Order 3


![image](<Images/05_Basis_Expansions_and_Regularization_image_050.jpg>)



B-splines of Order 4


![image](<Images/05_Basis_Expansions_and_Regularization_image_051.jpg>)



FIGURE 5.20. The sequence of B-splines up to order four with ten knots evenly spaced from 0 to 1. The B-splines have local support; they are nonzero on an interval spanned by $M + 1$ knots.


## Computations for Smoothing Splines

Although natural splines (Section 5.2.1) provide a basis for smoothing splines, it is computationally more convenient to operate in the larger space of unconstrained B-splines. We write $\begin{array} { r } { f ( x ) = \sum _ { 1 } ^ { N \det + 4 } \gamma _ { j } B _ { j } ( x ) } \end{array}$ , where $\gamma _ { j }$ are coefficients and the $B _ { j }$ are the cubic B-spline basis functions. The solution looks the same as before, 

$$
\hat {\boldsymbol {\gamma}} = (\mathbf {B} ^ {T} \mathbf {B} + \lambda \boldsymbol {\Omega} _ {B}) ^ {- 1} \mathbf {B} ^ {T} \mathbf {y},\tag{5.79}
$$

except now the $N \times N$ matrix N is replaced by the $N \times ( N + 4 )$ matrix B, and similarly the $( N + 4 ) \times ( N + 4 )$ penalty matrix $\Omega _ { B }$ replaces the $N \times N$ dimensional $\Omega _ { N }$ . Although at face value it seems that there are no boundary derivative constraints, it turns out that the penalty term automatically imposes them by giving effectively infinite weight to any non zero derivative beyond the boundary. In practice, $\hat { \gamma }$ is restricted to a linear subspace for which the penalty is always finite. 

Since the columns of B are the evaluated B-splines, in order from left to right and evaluated at the sorted values of X, and the cubic B-splines have local support, B is lower 4-banded. Consequently the matrix M $=$ $\left( \mathbf { B } ^ { \mathbf { T } } \mathbf { B } + \lambda \boldsymbol { \Omega } \right)$ is 4-banded and hence its Cholesky decomposition ${ \bf M } = { \bf L L ^ { T } }$ can be computed easily. One then solves $\mathbf { L L } ^ { T } \boldsymbol { \gamma } = \mathbf { B } ^ { T } \mathbf { y }$ by back-substitution to give $\gamma$ and hence the solution $\hat { f }$ in $O ( N )$ operations. 

In practice, when N is large, it is unnecessary to use all N interior knots, and any reasonable thinning strategy will save in computations and have negligible effect on the fit. For example, the smooth.spline function in $\mathrm { S } -$ PLUS uses an approximately logarithmic strategy: if $N < 5 0$ all knots are included, but even at $N = 5$ , 000 only 204 knots are used. 