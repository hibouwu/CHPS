# Linear Regression

![image](<Images/09_Linear_Regression_image_001.jpg>)


In the following, we will apply the mathematical concepts from Chapters 2, $5 , 6 ,$ and $7$ to solve linear regression (curve fitting) problems. In regression, we aim to find a function $f$ that maps inputs x $\in \mathbb { R } ^ { D }$ to corresponding function values $f ( \pmb { x } ) \in \mathbb { R }$ . We assume we are given a set of training inputs ${ \bf { x } } _ { n }$ and corresponding noisy observations $y _ { n } = f ( \pmb { x } _ { n } ) + \epsilon ,$ , where ϵ is an i.i.d. random variable that describes measurement/observation noise and potentially unmodeled processes (which we will not consider further in this chapter). Throughout this chapter, we assume zero-mean Gaussian noise. Our task is to find a function that not only models the training data, but generalizes well to predicting function values at input locations that are not part of the training data (see Chapter 8). An illustration of such a regression problem is given in Figure 9.1. A typical regression setting is given in Figure 9.1(a): For some input values $x _ { n } ,$ we observe (noisy) function values $y _ { n } = f ( x _ { n } ) + \epsilon .$ . The task is to infer the function f that generated the data and generalizes well to function values at new input locations. A possible solution is given in Figure 9.1(b), where we also show three distributions centered at the function values $f ( x )$ that represent the noise in the data. 

Regression is a fundamental problem in machine learning, and regression problems appear in a diverse range of research areas and applica-

![image](<Images/09_Linear_Regression_image_002.jpg>)



(a) Regression problem: observed noisy function values from which we wish to infer the underlying function that generated the data.


![image](<Images/09_Linear_Regression_image_003.jpg>)



Figure 9.1 (a) Dataset; (b) possible solution to the regression problem.



(b) Regression solution: possible function that could have generated the data (blue) with indication of the measurement noise of the function value at the corresponding inputs (orange distributions).


Normally, the type of noise could also be a “model choice”, but we fix the noise to be Gaussian in this chapter. 

tions, including time-series analysis (e.g., system identification), control and robotics (e.g., reinforcement learning, forward/inverse model learning), optimization (e.g., line searches, global optimization), and deeplearning applications (e.g., computer games, speech-to-text translation, image recognition, automatic video annotation). Regression is also a key ingredient of classification algorithms. Finding a regression function requires solving a variety of problems, including the following: 

Choice of the model (type) and the parametrization of the regression function. Given a dataset, what function classes (e.g., polynomials) are good candidates for modeling the data, and what particular parametrization (e.g., degree of the polynomial) should we choose? Model selection, as discussed in Section 8.6, allows us to compare various models to find the simplest model that explains the training data reasonably well. 

Finding good parameters. Having chosen a model of the regression function, how do we find good model parameters? Here, we will need to look at different loss/objective functions (they determine what a “good” fit is) and optimization algorithms that allow us to minimize this loss. 

Overfitting and model selection. Overfitting is a problem when the regression function fits the training data “too well” but does not generalize to unseen test data. Overfitting typically occurs if the underlying model (or its parametrization) is overly flexible and expressive; see Section 8.6. We will look at the underlying reasons and discuss ways to mitigate the effect of overfitting in the context of linear regression. 

Relationship between loss functions and parameter priors. Loss functions (optimization objectives) are often motivated and induced by probabilistic models. We will look at the connection between loss functions and the underlying prior assumptions that induce these losses. 

Uncertainty modeling. In any practical setting, we have access to only a finite, potentially large, amount of (training) data for selecting the model class and the corresponding parameters. Given that this finite amount of training data does not cover all possible scenarios, we may want to describe the remaining parameter uncertainty to obtain a measure of confidence of the model’s prediction at test time; the smaller the training set, the more important uncertainty modeling. Consistent modeling of uncertainty equips model predictions with confidence bounds. 

In the following, we will be using the mathematical tools from Chapters 3, 5, 6 and 7 to solve linear regression problems. We will discuss maximum likelihood and maximum a posteriori (MAP) estimation to find optimal model parameters. Using these parameter estimates, we will have a brief look at generalization errors and overfitting. Toward the end of this chapter, we will discuss Bayesian linear regression, which allows us to reason about model parameters at a higher level, thereby removing some of the problems encountered in maximum likelihood and MAP estimation. 

## 9.1 Problem Formulation

Because of the presence of observation noise, we will adopt a probabilistic approach and explicitly model the noise using a likelihood function. More specifically, throughout this chapter, we consider a regression problem with the likelihood function 

$$
p (y \mid \boldsymbol {x}) = \mathcal {N} \bigl (y \mid f (\boldsymbol {x}), \sigma^ {2} \bigr).\tag{9.1}
$$

Here, $\pmb { x } \in \mathbb { R } ^ { D }$ are inputs and $y \in \mathbb { R }$ are noisy function values (targets). With (9.1), the functional relationship between x and y is given as 

$$
y = f (\boldsymbol {x}) + \epsilon ,\tag{9.2}
$$

where $\epsilon \sim \mathcal { N } ( 0 , \sigma ^ { 2 } )$ is independent, identically distributed (i.i.d.) Gaussian measurement noise with mean 0 and variance $\sigma ^ { 2 }$ . Our objective is to find a function that is close (similar) to the unknown function $f$ that generated the data and that generalizes well. 

In this chapter, we focus on parametric models, i.e., we choose a parametrized function and find parameters θ that “work well” for modeling the data. For the time being, we assume that the noise variance $\sigma ^ { 2 }$ is known and focus on learning the model parameters θ. In linear regression, we consider the special case that the parameters θ appear linearly in our model. An example of linear regression is given by 

$$
p (y \mid \boldsymbol {x}, \boldsymbol {\theta}) = \mathcal {N} \big (y \mid \boldsymbol {x} ^ {\top} \boldsymbol {\theta}, \sigma^ {2} \big)\tag{9.3}
$$

$$
\Longleftrightarrow y = \boldsymbol {x} ^ {\top} \boldsymbol {\theta} + \epsilon , \quad \epsilon \sim \mathcal {N} (0, \sigma^ {2}),\tag{9.4}
$$

where $\pmb { \theta } \in \mathbb { R } ^ { D }$ are the parameters we seek. The class of functions described by $( 9 . 4 )$ are straight lines that pass through the origin. In (9.4), we chose a parametrization $f ( \mathbf { x } ) = \mathbf { x } ^ { \top } \pmb \theta .$ 

The likelihood in (9.3) is the probability density function of $y$ evaluated at ${ \pmb x } ^ { \top } { \pmb \theta } .$ . Note that the only source of uncertainty originates from the observation noise (as x and $\pmb \theta$ are assumed known in (9.3)). Without observation noise, the relationship between x and y would be deterministic and (9.3) would be a Dirac delta. 

## Example 9.1

For $x , \theta \in \mathbb { R }$ the linear regression model in (9.4) describes straight lines (linear functions), and the parameter θ is the slope of the line. Figure 9.2(a) shows some example functions for different values of θ. 

The linear regression model in (9.3)–(9.4) is not only linear in the parameters, but also linear in the inputs x. Figure 9.2(a) shows examples of such functions. We will see later that $y = \phi ^ { \top } ( { \pmb x } ) { \pmb \theta }$ for nonlinear transformations $\phi$ is also a linear regression model because “linear regression” 

292 

Figure 9.2 Linear regression example. (a) Example functions that fall into this category; (b) training set; (c) maximum likelihood estimate. 

![image](<Images/09_Linear_Regression_image_004.jpg>)



(a) Example functions (straight lines) that can be described using the linear model in (9.4).


![image](<Images/09_Linear_Regression_image_005.jpg>)



(b) Training set.


![image](<Images/09_Linear_Regression_image_006.jpg>)



(c) Maximum likelihood estimate.


refers to models that are “linear in the parameters”, i.e., models that describe a function by a linear combination of input features. Here, a “feature” is a representation $\phi ( { \pmb x } )$ of the inputs ${ \pmb x } .$ 

In the following, we will discuss in more detail how to find good parameters θ and how to evaluate whether a parameter set “works well”. For the time being, we assume that the noise variance $\sigma ^ { 2 }$ is known. 

## 9.2 Parameter Estimation

training set 

Figure 9.3 Probabilistic graphical model for linear regression. Observed random variables are shaded, deterministic/ known values are without circles. 

Consider the linear regression setting (9.4) and assume we are given a training set $\mathcal { D } : = \{ ( \pmb { x } _ { 1 } , y _ { 1 } ) , \dots , ( \pmb { x } _ { N } , y _ { N } ) \}$ consisting of N inputs ${ \pmb x } _ { n } \in \qquad $ $\mathbb { R } ^ { D }$ and corresponding observations/targets $y _ { n } \in \mathbb { R } , n = 1 , . . . , N$ . The corresponding graphical model is given in Figure 9.3. Note that $y _ { i }$ and $y _ { j }$ are conditionally independent given their respective inputs ${ \pmb x } _ { i } , { \pmb x } _ { j }$ so that the likelihood factorizes according to 

$$
p (\mathcal {Y} \mid \mathcal {X}, \boldsymbol {\theta}) = p (y _ {1}, \dots , y _ {N} \mid \boldsymbol {x} _ {1}, \dots , \boldsymbol {x} _ {N}, \boldsymbol {\theta})\tag{9.5a}
$$

![image](<Images/09_Linear_Regression_image_007.jpg>)


$$
= \prod_ {n = 1} ^ {N} p (y _ {n} \mid \boldsymbol {x} _ {n}, \boldsymbol {\theta}) = \prod_ {n = 1} ^ {N} \mathcal {N} \left(y _ {n} \mid \boldsymbol {x} _ {n} ^ {\top} \boldsymbol {\theta}, \sigma^ {2}\right),\tag{9.5b}
$$

where we defined ${ \mathcal { X } } : = \{ { \pmb x } _ { 1 } , \ldots , { \pmb x } _ { N } \}$ and $\mathcal { Y } : = \{ y _ { 1 } , . . . , y _ { N } \}$ as the sets of training inputs and corresponding targets, respectively. The likelihood and the factors $p ( y _ { n } \mid \pmb { x } _ { n } , \pmb { \theta } )$ are Gaussian due to the noise distribution; see (9.3). 

In the following, we will discuss how to find optimal parameters ${ \pmb { \theta } } ^ { * } \in$ $\mathbb { R } ^ { D }$ for the linear regression model (9.4). Once the parameters $\pmb { \theta } ^ { * }$ are found, we can predict function values by using this parameter estimate in (9.4) so that at an arbitrary test input ${ \pmb x } _ { \mathrm { : } }$ the distribution of the corresponding target $y _ { * }$ is 

$$
p (y _ {*} \mid \boldsymbol {x} _ {*}, \boldsymbol {\theta} ^ {*}) = \mathcal {N} \big (y _ {*} \mid \boldsymbol {x} _ {*} ^ {\top} \boldsymbol {\theta} ^ {*}, \sigma^ {2} \big).\tag{9.6}
$$

In the following, we will have a look at parameter estimation by maximizing the likelihood, a topic that we already covered to some degree in Section 8.3. 

## 9.2.1 Maximum Likelihood Estimation

A widely used approach to finding the desired parameters $\pmb { \theta } _ { \mathrm { M L } }$ is maximum likelihood estimation, where we find parameters $\pmb { \theta } _ { \mathrm { M I } }$ that maximize the likelihood (9.5b). Intuitively, maximizing the likelihood means maximizing the predictive distribution of the training data given the model parameters. We obtain the maximum likelihood parameters as 

$$
\boldsymbol {\theta} _ {\mathrm{ML}} \in \arg \max _ {\boldsymbol {\theta}} p (\mathcal {Y} | \mathcal {X}, \boldsymbol {\theta}).\tag{9.7}
$$

Remark. The likelihood $p ( \pmb { y } | \pmb { x } , \pmb { \theta } )$ is not a probability distribution in θ: It is simply a function of the parameters θ but does not integrate to 1 $( \mathrm { i . e . , }$ it is unnormalized), and may not even be integrable with respect to $\pmb \theta .$ However, the likelihood in (9.7) is a normalized probability distribution in y. $\diamondsuit$ 

To find the desired parameters $\pmb { \theta } _ { \mathrm { M L } }$ that maximize the likelihood, we typically perform gradient ascent (or gradient descent on the negative likelihood). In the case of linear regression we consider here, however, a closed-form solution exists, which makes iterative gradient descent un necessary. In practice, instead of maximizing the likelihood directly, we apply the log-transformation to the likelihood function and minimize the negative log-likelihood. 

Remark (Log-Transformation). Since the likelihood (9.5b) is a product of N Gaussian distributions, the log-transformation is useful since (a) it does not suffer from numerical underflow, and (b) the differentiation rules will turn out simpler. More specifically, numerical underflow will be a problem when we multiply N probabilities, where N is the number of data points, since we cannot represent very small numbers, such as $1 0 ^ { - 2 5 6 }$ Furthermore, the log-transform will turn the product into a sum of logprobabilities such that the corresponding gradient is a sum of individual gradients, instead of a repeated application of the product rule (5.46) to compute the gradient of a product of N terms. 

To find the optimal parameters $\pmb { \theta } _ { \mathrm { M L } }$ of our linear regression problem, we minimize the negative log-likelihood 

$$
- \log p (\mathcal {Y} \mid \mathcal {X}, \boldsymbol {\theta}) = - \log \prod_ {n = 1} ^ {N} p (y _ {n} \mid \boldsymbol {x} _ {n}, \boldsymbol {\theta}) = - \sum_ {n = 1} ^ {N} \log p (y _ {n} \mid \boldsymbol {x} _ {n}, \boldsymbol {\theta}),\tag{9.8}
$$

where we exploited that the likelihood (9.5b) factorizes over the number of data points due to our independence assumption on the training set. 

In the linear regression model (9.4), the likelihood is Gaussian (due to the Gaussian additive noise term), such that we arrive at 

$$
\log p (y _ {n} \mid \boldsymbol {x} _ {n}, \boldsymbol {\theta}) = - \frac {1}{2 \sigma^ {2}} (y _ {n} - \boldsymbol {x} _ {n} ^ {\top} \boldsymbol {\theta}) ^ {2} + \mathrm{const},\tag{9.9}
$$

where the constant includes all terms independent of θ. Using (9.9) in the 

Maximizing the likelihood means maximizing the predictive distribution of the (training) data given the parameters. The likelihood is not a probability distribution in the parameters. 

negative log-likelihood (9.8), we obtain (ignoring the constant terms) 

The negative log-likelihood function is also called error function. design matrix The squared error is often used as a measure of distance. Recall from Section 3.1 that $\| \pmb { x } \| ^ { 2 } = \pmb { x } ^ { \top } \pmb { x }$ if we choose the dot product as the inner product. 

Ignoring the possibility of duplicate data points, rk $\mathbf { X } ) = D$ ${ \mathrm { i f ~ } } N \geqslant D , { \mathrm { i . e . , } }$ we do not have more parameters than data points. 

$$
\begin{array}{l} \mathcal {L} (\boldsymbol {\theta}) := \frac {1}{2 \sigma^ {2}} \sum_ {n = 1} ^ {N} (y _ {n} - \boldsymbol {x} _ {n} ^ {\top} \boldsymbol {\theta}) ^ {2} \\ \qquad = \frac {1}{2 \sigma^ {2}} (\boldsymbol {y} - \boldsymbol {X} \boldsymbol {\theta}) ^ {\top} (\boldsymbol {y} - \boldsymbol {X} \boldsymbol {\theta}) = \frac {1}{2 \sigma^ {2}} \| \boldsymbol {y} - \boldsymbol {X} \boldsymbol {\theta} \| ^ {2}, \end{array}\tag{9.10a}
$$

(9.10b) 

where we define the design matrix $\pmb { X } : = [ \pmb { x } _ { 1 } , \ldots , \pmb { x } _ { N } ] ^ { \top } \in \mathbb { R } ^ { N \times D }$ as the collection of training inputs and $\pmb { y } : = [ y _ { 1 } , \dots , y _ { N } ] ^ { \top } \in \mathbb { R } ^ { N }$ as a vector that collects all training targets. Note that the nth row in the design matrix X corresponds to the training input ${ \bf { x } } _ { n }$ . In (9.10b), we used the fact that the sum of squared errors between the observations $y _ { n }$ and the corresponding model prediction $\pmb { x } _ { n } ^ { \top } \pmb { \theta }$ equals the squared distance between y and Xθ. 

With (9.10b), we have now a concrete form of the negative log-likelihood function we need to optimize. We immediately see that (9.10b) is quadratic in $\pmb { \theta } .$ This means that we can find a unique global solution $\pmb { \theta } _ { \mathrm { M L } }$ for minimizing the negative log-likelihood ${ \mathcal { L } } .$ . We can find the global optimum by computing the gradient of ${ \mathcal { L } } ,$ setting it to 0 and solving for θ. 

Using the results from Chapter 5, we compute the gradient of $\mathcal { L }$ with respect to the parameters as 

$$
\frac {\mathrm{d} \mathcal {L}}{\mathrm{d} \boldsymbol {\theta}} = \frac {\mathrm{d}}{\mathrm{d} \boldsymbol {\theta}} \left(\frac {1}{2 \sigma^ {2}} (\boldsymbol {y} - \boldsymbol {X} \boldsymbol {\theta}) ^ {\top} (\boldsymbol {y} - \boldsymbol {X} \boldsymbol {\theta})\right)\tag{9.11a}
$$

$$
= \frac {1}{2 \sigma^ {2}} \frac {\mathrm{d}}{\mathrm{d} \boldsymbol {\theta}} \left(\boldsymbol {y} ^ {\top} \boldsymbol {y} - 2 \boldsymbol {y} ^ {\top} \boldsymbol {X} \boldsymbol {\theta} + \boldsymbol {\theta} ^ {\top} \boldsymbol {X} ^ {\top} \boldsymbol {X} \boldsymbol {\theta}\right)\tag{9.11b}
$$

$$
= \frac {1}{\sigma^ {2}} (- \pmb {y} ^ {\top} \pmb {X} + \pmb {\theta} ^ {\top} \pmb {X} ^ {\top} \pmb {X}) \in \mathbb {R} ^ {1 \times D}.\tag{9.11c}
$$

The maximum likelihood estimator $\pmb { \theta } _ { \mathrm { M L } }$ solves $\begin{array} { r } { \frac { \mathrm { d } \mathcal { L } } { \mathrm { d } \theta } = \mathbf { 0 } ^ { \top } } \end{array}$ (necessary optimality condition) and we obtain 

$$
\frac {\mathrm{d} \mathcal {L}}{\mathrm{d} \boldsymbol {\theta}} = \mathbf {0} ^ {\top} \stackrel {(9. 1 1 \mathrm{c})} {\Longleftrightarrow} \boldsymbol {\theta} _ {\mathrm{ML}} ^ {\top} \boldsymbol {X} ^ {\top} \boldsymbol {X} = \boldsymbol {y} ^ {\top} \boldsymbol {X}\tag{9.12a}
$$

$$
\Longleftrightarrow \boldsymbol {\theta} _ {\mathrm{ML}} ^ {\top} = \boldsymbol {y} ^ {\top} \boldsymbol {X} (\boldsymbol {X} ^ {\top} \boldsymbol {X}) ^ {- 1}\tag{9.12b}
$$

$$
\Longleftrightarrow \boldsymbol {\theta} _ {\mathrm{ML}} = (\boldsymbol {X} ^ {\top} \boldsymbol {X}) ^ {- 1} \boldsymbol {X} ^ {\top} \boldsymbol {y}.\tag{9.12c}
$$

We could right-multiply the first equation by $( X ^ { \top } X ) ^ { - 1 }$ because $\boldsymbol { X } ^ { \top } \boldsymbol { X }$ is positive definite if rk $( \pmb { X } ) = \pmb { D }$ , where rk $( X )$ denotes the rank of X. 

Remark. Setting the gradient to $\mathbf { 0 } ^ { \top }$ is a necessary and sufficient condition, and we obtain a global minimum since the Hessian $\nabla _ { \pmb { \theta } } ^ { 2 } { \mathcal { L } } ( \pmb { \theta } ) = \pmb { X } ^ { \top } \pmb { X } \in$ $\mathbb { R } ^ { D \times D }$ is positive definite. ◇ 

Remark. The maximum likelihood solution in (9.12c) requires us to solve a system of linear equations of the form $\mathbf { { \boldsymbol { A } } } \theta = \mathbf { \boldsymbol { b } }$ with $\bar { A } = ( X ^ { \top } X )$ and $\pmb { b } = \pmb { X } ^ { \top } \pmb { y }$ 

## Example 9.2 (Fitting Lines)

Let us have a look at Figure 9.2, where we aim to fit a straight line $f ( x ) =$ $\theta x$ , where θ is an unknown slope, to a dataset using maximum likelihood estimation. Examples of functions in this model class (straight lines) are shown in Figure $9 . 2 ( \mathrm { a } )$ . For the dataset shown in Figure 9.2(b), we find the maximum likelihood estimate of the slope parameter θ using (9.12c) and obtain the maximum likelihood linear function in Figure 9.2(c). 

## Maximum Likelihood Estimation with Features

So far, we considered the linear regression setting described in (9.4), which allowed us to fit straight lines to data using maximum likelihood estimation. However, straight lines are not sufficiently expressive when it comes to fitting more interesting data. Fortunately, linear regression offers us a way to fit nonlinear functions within the linear regression framework: Since “linear regression” only refers to “linear in the parameters”, we can perform an arbitrary nonlinear transformation $\phi ( { \pmb x } )$ of the inputs x and then linearly combine the components of this transformation. The corresponding linear regression model is 

$$
\begin{array}{c} p (y \mid \boldsymbol {x}, \boldsymbol {\theta}) = \mathcal {N} \big (y \mid \boldsymbol {\phi} ^ {\top} (\boldsymbol {x}) \boldsymbol {\theta},   \sigma^ {2} \big) \\ \Longleftrightarrow y = \boldsymbol {\phi} ^ {\top} (\boldsymbol {x}) \boldsymbol {\theta} + \epsilon = \sum_ {k = 0} ^ {K - 1} \theta_ {k} \phi_ {k} (\boldsymbol {x}) + \epsilon  , \end{array}\tag{9.13}
$$

where $\phi : \mathbb { R } ^ { D }  \mathbb { R } ^ { K }$ is a (nonlinear) transformation of the inputs x and $\phi _ { k } : \mathbb { R } ^ { D } $ R is the kth component of the feature vector $\phi$ . Note that the model parameters θ still appear only linearly. 

## Example 9.3 (Polynomial Regression)

We are concerned with a regression problem $y = \phi ^ { \top } ( x ) \theta { + } \epsilon .$ , where $x \in \mathbb { R }$ and $\pmb \theta \in \mathbb { R } ^ { K }$ . A transformation that is often used in this context is 

$$
\boldsymbol {\phi} (x) = \left[ \begin{array}{c} \phi_ {0} (x) \\ \phi_ {1} (x) \\ \vdots \\ \phi_ {K - 1} (x) \end{array} \right] = \left[ \begin{array}{c} 1 \\ x \\ x ^ {2} \\ x ^ {3} \\ \vdots \\ x ^ {K - 1} \end{array} \right] \in \mathbb {R} ^ {K}.\tag{9.14}
$$

This means that we $^ { \mathfrak { s o } } \mathrm { l i f f } ^ { \mathfrak { n } }$ the original one-dimensional input space into a K-dimensional feature space consisting of all monomials $x ^ { k }$ for $k =$ $0 , \ldots , K - 1$ With these features, we can model polynomials of degree ⩽ K 1 within the framework of linear regression: A polynomial of degree 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



K 1 is 

$$
f (x) = \sum_ {k = 0} ^ {K - 1} \theta_ {k} x ^ {k} = \boldsymbol {\phi} ^ {\top} (x) \boldsymbol {\theta},\tag{9.15}
$$

where $\phi$ is defined in (9.14) and $\pmb \theta = [ \theta _ { 0 } , \dots , \theta _ { K - 1 } ] ^ { \top } \in \mathbb { R } ^ { K }$ contains the (linear) parameters $\theta _ { k }$ 

Let us now have a look at maximum likelihood estimation of the parameters θ in the linear regression model (9.13). We consider training inputs ${ \pmb x } _ { n } \in \mathbb { R } ^ { D }$ and targets $y _ { n } \in \mathbb R , n = 1 , . . . , N$ , and define thefeature matrix (design matrix) as 

$$
\boldsymbol {\Phi} := \left[ \begin{array}{c} \boldsymbol {\phi} ^ {\top} (\boldsymbol {x} _ {1}) \\ \vdots \\ \boldsymbol {\phi} ^ {\top} (\boldsymbol {x} _ {N}) \end{array} \right] = \left[ \begin{array}{c c c} \phi_ {0} (\boldsymbol {x} _ {1}) & \dots & \phi_ {K - 1} (\boldsymbol {x} _ {1}) \\ \phi_ {0} (\boldsymbol {x} _ {2}) & \dots & \phi_ {K - 1} (\boldsymbol {x} _ {2}) \\ \vdots & & \vdots \\ \phi_ {0} (\boldsymbol {x} _ {N}) & \dots & \phi_ {K - 1} (\boldsymbol {x} _ {N}) \end{array} \right] \in \mathbb {R} ^ {N \times K},\tag{9.16}
$$

where $\Phi _ { i j } = \phi _ { j } ( \pmb { x } _ { i } )$ and $\phi _ { j } : \mathbb { R } ^ { D }  \mathbb { R } .$ 

Example 9.4 (Feature Matrix for Second-order Polynomials) For a second-order polynomial and N training points $x _ { n } ~ \in ~ \mathbb { R } , n ~ =$ $1 , \ldots , N$ , the feature matrix is 

$$
\boldsymbol {\Phi} = \left[ \begin{array}{c c c} 1 & x _ {1} & x _ {1} ^ {2} \\ 1 & x _ {2} & x _ {2} ^ {2} \\ \vdots & \vdots & \vdots \\ 1 & x _ {N} & x _ {N} ^ {2} \end{array} \right].\tag{9.17}
$$

With the feature matrix Φ defined in (9.16), the negative log-likelihood for the linear regression model (9.13) can be written as 

$$
- \log p (\mathcal {Y} \mid \mathcal {X}, \boldsymbol {\theta}) = \frac {1}{2 \sigma^ {2}} (\boldsymbol {y} - \boldsymbol {\Phi} \boldsymbol {\theta}) ^ {\top} (\boldsymbol {y} - \boldsymbol {\Phi} \boldsymbol {\theta}) + \text { const }  .\tag{9.18}
$$

Comparing (9.18) with the negative log-likelihood in (9.10b) for the “feature-free” model, we immediately see we just need to replace X with Φ. Since both X and Φ are independent of the parameters $\pmb \theta$ that we wish to optimize, we arrive immediately at the maximum likelihood estimate 

$$
\boldsymbol {\theta} _ {\mathrm{ML}} = \left(\boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi}\right) ^ {- 1} \boldsymbol {\Phi} ^ {\top} \boldsymbol {y}\tag{9.19}
$$

for the linear regression problem with nonlinear features defined in (9.13). Remark. When we were working without features, we required $\boldsymbol { X } ^ { \top } \boldsymbol { X }$ to be invertible, which is the case when $\operatorname { r k } ( { \boldsymbol { X } } ) = D ,$ i.e., the columns of X 

## 9.2 Parameter Estimation

are linearly independent. In (9.19), we therefore require $\Phi ^ { \top } \Phi \in \mathbb { R } ^ { K \times K }$ to be invertible. This is the case if and only if rk $( \Phi ) = K$ 

## Example 9.5 (Maximum Likelihood Polynomial Fit)

![image](<Images/09_Linear_Regression_image_008.jpg>)



(a) Regression dataset.


![image](<Images/09_Linear_Regression_image_009.jpg>)



Figure 9.4 Polynomial regression: (a) dataset consisting of (x<sub>n</sub>, y<sub>n</sub>) pairs, $n = 1 , \ldots , 1 0 ;$ (b) maximum likelihood polynomial of degree 4.


(b) Polynomial of degree 4 determined by maximum likelihood estimation. 

Consider the dataset in Figure 9.4(a). The dataset consists of $N = 1 0$ pairs $( x _ { n } , y _ { n } )$ , where $x _ { n } \sim \mathcal { U } [ - 5 , 5 ]$ and $y _ { n } = - \sin ( x _ { n } / 5 ) + \cos ( x _ { n } ) + \epsilon _ { \scriptscriptstyle 3 }$ where $\epsilon \sim \mathcal { N } ( 0 , 0 . 2 ^ { 2 } )$ 

We fit a polynomial of degree 4 using maximum likelihood estimation, i.e., parameters $\pmb { \theta } _ { \mathrm { M L } }$ are given in (9.19). The maximum likelihood estimate yields function values $\phi ^ { \top } ( x _ { * } ) \theta _ { \mathrm { M L } }$ at any test location $x _ { * }$ . The result is shown in Figure 9.4(b). 

## Estimating the Noise Variance

Thus far, we assumed that the noise variance $\sigma ^ { 2 }$ is known. However, we can also use the principle of maximum likelihood estimation to obtain the maximum likelihood estimator $\sigma _ { \mathrm { M L } } ^ { 2 }$ for the noise variance. To do this, we follow the standard procedure: We write down the log-likelihood, compute its derivative with respect to $\sigma ^ { 2 } > 0$ , set it to 0, and solve. The log-likelihood is given by 

$$
\log p (\mathcal {Y} | \mathcal {X}, \boldsymbol {\theta}, \sigma^ {2}) = \sum_ {n = 1} ^ {N} \log \mathcal {N} \big (y _ {n} | \boldsymbol {\phi} ^ {\top} (\boldsymbol {x} _ {n}) \boldsymbol {\theta}, \sigma^ {2} \big)\tag{9.20a}
$$

$$
= \sum_ {n = 1} ^ {N} \left(- \frac {1}{2} \log (2 \pi) - \frac {1}{2} \log \sigma^ {2} - \frac {1}{2 \sigma^ {2}} (y _ {n} - \boldsymbol {\phi} ^ {\top} (\boldsymbol {x} _ {n}) \boldsymbol {\theta}) ^ {2}\right)\tag{9.20b}
$$

$$
= - \frac {N}{2} \log \sigma^ {2} - \frac {1}{2 \sigma^ {2}} \underbrace {\sum_ {n = 1} ^ {N} (y _ {n} - \boldsymbol {\phi} ^ {\top} (\boldsymbol {x} _ {n}) \boldsymbol {\theta}) ^ {2}} _ {=: s} + \text { const }.\tag{9.20c}
$$



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



The partial derivative of the log-likelihood with respect to $\sigma ^ { 2 }$ is then 

$$
\frac {\partial \log p (\mathcal {Y} | \mathcal {X} , \pmb {\theta} , \sigma^ {2})}{\partial \sigma^ {2}} = - \frac {N}{2 \sigma^ {2}} + \frac {1}{2 \sigma^ {4}} s = 0\tag{9.21a}
$$

$$
\Longleftrightarrow \frac {N}{2 \sigma^ {2}} = \frac {s}{2 \sigma^ {4}}\tag{9.21b}
$$

so that we identify 

$$
\sigma_ {\mathrm{ML}} ^ {2} = \frac {s}{N} = \frac {1}{N} \sum_ {n = 1} ^ {N} (y _ {n} - \boldsymbol {\phi} ^ {\top} (\pmb {x} _ {n}) \pmb {\theta}) ^ {2}.\tag{9.22}
$$

Therefore, the maximum likelihood estimate of the noise variance is the empirical mean of the squared distances between the noise-free function values $\phi ^ { \top } ( { \pmb x } _ { n } ) \pmb \theta$ and the corresponding noisy observations $y _ { n }$ at input locations ${ \bf { x } } _ { n }$ 

## 9.2.2 Overfitting in Linear Regression

We just discussed how to use maximum likelihood estimation to fit linear models (e.g., polynomials) to data. We can evaluate the quality of the model by computing the error/loss incurred. One way of doing this is to compute the negative log-likelihood (9.10b), which we minimized to determine the maximum likelihood estimator. Alternatively, given that the noise parameter $\sigma ^ { 2 }$ is not a free model parameter, we can ignore the scaling by $1 / \sigma ^ { 2 }$ , so that we end up with a squared-error-loss function $\lVert y - \bar { \Phi } \theta \rVert ^ { 2 }$ . Instead of using this squared loss, we often use the root mean square error (RMSE) 

$$
\sqrt {\frac {1}{N} \left\| \boldsymbol {y} - \boldsymbol {\Phi} \boldsymbol {\theta} \right\| ^ {2}} = \sqrt {\frac {1}{N} \sum_ {n = 1} ^ {N} (y _ {n} - \boldsymbol {\phi} ^ {\top} (\boldsymbol {x} _ {n}) \boldsymbol {\theta}) ^ {2}},\tag{9.23}
$$

which (a) allows us to compare errors of datasets with different sizes and (b) has the same scale and the same units as the observed function values $y _ { n }$ . For example, if we fit a model that maps post-codes (x is given in latitude, longitude) to house prices (y-values are EUR) then the RMSE is also measured in EUR, whereas the squared error is given in EUR<sup>2</sup>. If we choose to include the factor $\sigma ^ { 2 }$ from the original negative log-likelihood (9.10b), then we end up with a unitless objective, i.e., in the preceding example, our objective would no longer be in EUR or $\mathrm { E U R ^ { 2 } }$ 

For model selection (see Section 8.6), we can use the RMSE (or the negative log-likelihood) to determine the best degree of the polynomial by finding the polynomial degree M that minimizes the objective. Given that the polynomial degree is a natural number, we can perform a brute-force search and enumerate all (reasonable) values of M. For a training set of size N it is sufficient to test $0 \leqslant M \leqslant N - 1$ . For $M < N$ , the maximum likelihood estimator is unique. For $M \geqslant N$ , we have more parameters 

## 9.2 Parameter Estimation

![image](<Images/09_Linear_Regression_image_010.jpg>)



(a) $M = 0$


![image](<Images/09_Linear_Regression_image_011.jpg>)



(b) M = 1


![image](<Images/09_Linear_Regression_image_012.jpg>)



299



(c) $M = 3$



Figure 9.5 Maximum likelihood fits for different polynomial degrees M.


![image](<Images/09_Linear_Regression_image_013.jpg>)



(d) $M = 4$


![image](<Images/09_Linear_Regression_image_014.jpg>)



(e) $M = 6$


![image](<Images/09_Linear_Regression_image_015.jpg>)



(f) $M = 9$


than data points, and would need to solve an underdetermined system of linear equations $( \Phi ^ { \top } \Phi$ in (9.19) would also no longer be invertible) so that there are infinitely many possible maximum likelihood estimators. 

Figure 9.5 shows a number of polynomial fits determined by maximum likelihood for the dataset from Figure $9 . 4 ( \mathrm { a } )$ with $N = 1 0$ observations. We notice that polynomials of low degree (e.g., constants $( M = 0 )$ or linear $( M = 1 ) )$ fit the data poorly and, hence, are poor representations of the true underlying function. For degrees $M = 3 , \ldots , 6 ,$ , the fits look plausible and smoothly interpolate the data. When we go to higher-degree polynomials, we notice that they fit the data better and better. In the extreme case of $M = N - 1 = 9$ , the function will pass through every single data point. However, these high-degree polynomials oscillate wildly and are a poor representation of the underlying function that generated the data, such that we suffer from overfitting. 

Remember that the goal is to achieve good generalization by making accurate predictions for new (unseen) data. We obtain some quantitative insight into the dependence of the generalization performance on the polynomial of degree M by considering a separate test set comprising 200 data points generated using exactly the same procedure used to generate the training set. As test inputs, we chose a linear grid of 200 points in the interval of [ 5, 5]. For each choice of M, we evaluate the RMSE (9.23) for both the training data and the test data. 

Looking now at the test error, which is a qualitive measure of the gen eralization properties of the corresponding polynomial, we notice that initially the test error decreases; see Figure 9.6 (orange). For fourth-order polynomials, the test error is relatively low and stays relatively constant up to degree 5. However, from degree 6 onward the test error increases signif icantly, and high-order polynomials have very bad generalization properties. In this particular example, this also is evident from the corresponding 

The case of M = N − 1 is extreme in the sense that otherwise the null space of the corresponding system of linear equations would be non-trivial, and we would have infinitely many optimal solutions to the linear regression problem. 

overfitting Note that the noise variance $\sigma ^ { 2 } > 0 .$ 

![image](<Images/09_Linear_Regression_image_016.jpg>)


maximum likelihood fits in Figure 9.5. Note that the training error (blue curve in Figure 9.6) never increases when the degree of the polynomial increases. In our example, the best generalization (the point of the smallest test error) is obtained for a polynomial of degree $M = 4$ 

## 9.2.3 Maximum A Posteriori Estimation

We just saw that maximum likelihood estimation is prone to overfitting. We often observe that the magnitude of the parameter values becomes relatively large if we run into overfitting (Bishop, 2006). 

To mitigate the effect of huge parameter values, we can place a prior distribution $p ( \pmb \theta )$ on the parameters. The prior distribution explicitly encodes what parameter values are plausible (before having seen any data). For example, a Gaussian prior $p ( \theta ) \ = \ \mathcal { N } ( 0 , 1 )$ on a single parameter $\theta$ encodes that parameter values are expected lie in the interval $[ - 2 , 2 ]$ (two standard deviations around the mean value). Once a dataset $x , y$ is available, instead of maximizing the likelihood we seek parameters that maximize the posterior distribution $p ( \pmb \theta | \mathcal { X } , \mathcal { Y } )$ . This procedure is called maximum a posteriori (MAP) estimation. 

The posterior over the parameters $\theta ,$ given the training data $x , y$ , is obtained by applying Bayes’ theorem (Section 6.3) as 

$$
p (\boldsymbol {\theta} \mid \mathcal {X}, \mathcal {Y}) = \frac {p (\mathcal {Y} \mid \mathcal {X} , \boldsymbol {\theta}) p (\boldsymbol {\theta})}{p (\mathcal {Y} \mid \mathcal {X})}.\tag{9.24}
$$

Since the posterior explicitly depends on the parameter prior $p ( \pmb \theta )$ , the prior will have an effect on the parameter vector we find as the maximizer of the posterior. We will see this more explicitly in the following. The parameter vector $\theta _ { \mathrm { M A P } }$ that maximizes the posterior (9.24) is the MAP estimate. 

To find the MAP estimate, we follow steps that are similar in flavor to maximum likelihood estimation. We start with the log-transform and compute the log-posterior as 

$$
\log p (\boldsymbol {\theta} \mid \mathcal {X}, \mathcal {Y}) = \log p (\mathcal {Y} \mid \mathcal {X}, \boldsymbol {\theta}) + \log p (\boldsymbol {\theta}) + \mathrm{const},\tag{9.25}
$$

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

where the constant comprises the terms that are independent of θ. We see that the log-posterior in (9.25) is the sum of the log-likelihood $p ( \mathcal { V } | \mathcal { X } , \pmb { \theta } )$ and the log-prior log $p ( \pmb \theta )$ so that the MAP estimate will be a “compromise” between the prior (our suggestion for plausible parameter values before observing data) and the data-dependent likelihood. 

To find the MAP estimate $\theta _ { \mathrm { M A P } } { \mathrm { . } }$ , we minimize the negative log-posterior distribution with respect to $\theta ,$ i.e., we solve 

$$
\boldsymbol {\theta} _ {\text { MAP }} \in \arg \min _ {\boldsymbol {\theta}} \left\{- \log p (\mathcal {Y} \mid \mathcal {X}, \boldsymbol {\theta}) - \log p (\boldsymbol {\theta}) \right\}.\tag{9.26}
$$

The gradient of the negative log-posterior with respect to θ is 

$$
- \frac {\mathrm{d} \log p (\pmb {\theta} | \mathcal {X} , \mathcal {Y})}{\mathrm{d} \pmb {\theta}} = - \frac {\mathrm{d} \log p (\mathcal {Y} | \mathcal {X} , \pmb {\theta})}{\mathrm{d} \pmb {\theta}} - \frac {\mathrm{d} \log p (\pmb {\theta})}{\mathrm{d} \pmb {\theta}},\tag{9.27}
$$

where we identify the first term on the right-hand side as the gradient of the negative log-likelihood from (9.11c). 

With a (conjugate) Gaussian prior $p ( \pmb \theta ) = \mathcal { N } \big ( \mathbf 0 , b ^ { 2 } \pmb I \big )$ on the parameters $\theta ,$ the negative log-posterior for the linear regression setting (9.13), we obtain the negative log posterior 

$$
- \log p (\boldsymbol {\theta} \mid \mathcal {X}, \mathcal {Y}) = \frac {1}{2 \sigma^ {2}} (\boldsymbol {y} - \boldsymbol {\Phi} \boldsymbol {\theta}) ^ {\top} (\boldsymbol {y} - \boldsymbol {\Phi} \boldsymbol {\theta}) + \frac {1}{2 b ^ {2}} \boldsymbol {\theta} ^ {\top} \boldsymbol {\theta} + \text { const }  .\tag{9.28}
$$

Here, the first term corresponds to the contribution from the log-likelihood, and the second term originates from the log-prior. The gradient of the logposterior with respect to the parameters $\pmb \theta$ is then 

$$
- \frac {\mathrm{d} \log p (\boldsymbol {\theta} \mid \mathcal {X} , \mathcal {Y})}{\mathrm{d} \boldsymbol {\theta}} = \frac {1}{\sigma^ {2}} (\boldsymbol {\theta} ^ {\top} \boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi} - \boldsymbol {y} ^ {\top} \boldsymbol {\Phi}) + \frac {1}{b ^ {2}} \boldsymbol {\theta} ^ {\top}.\tag{9.29}
$$

We will find the MAP estimate $\theta _ { \mathrm { M A P } }$ by setting this gradient to $\mathbf { 0 } ^ { \top }$ and solving for $\theta _ { \mathrm { M A P } }$ . We obtain 

$$
\frac {1}{\sigma^ {2}} (\pmb {\theta} ^ {\top} \pmb {\Phi} ^ {\top} \pmb {\Phi} - \pmb {y} ^ {\top} \pmb {\Phi}) + \frac {1}{b ^ {2}} \pmb {\theta} ^ {\top} = \pmb {0} ^ {\top}\tag{9.30a}
$$

$$
\Longleftrightarrow \boldsymbol {\theta} ^ {\top} \left(\frac {1}{\sigma^ {2}} \boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi} + \frac {1}{b ^ {2}} \boldsymbol {I}\right) - \frac {1}{\sigma^ {2}} \boldsymbol {y} ^ {\top} \boldsymbol {\Phi} = \boldsymbol {0} ^ {\top}\tag{9.30b}
$$

$$
\Longleftrightarrow \boldsymbol {\theta} ^ {\top} \left(\boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi} + \frac {\sigma^ {2}}{b ^ {2}} \boldsymbol {I}\right) = \boldsymbol {y} ^ {\top} \boldsymbol {\Phi}\tag{9.30c}
$$

$$
\Longleftrightarrow \boldsymbol {\theta} ^ {\top} = \boldsymbol {y} ^ {\top} \boldsymbol {\Phi} \left(\boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi} + \frac {\sigma^ {2}}{b ^ {2}} \boldsymbol {I}\right) ^ {- 1}\tag{9.30d}
$$

so that the MAP estimate is (by transposing both sides of the last equality) 

$$
\boldsymbol {\theta} _ {\mathrm{MAP}} = \left(\boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi} + \frac {\sigma^ {2}}{b ^ {2}} \boldsymbol {I}\right) ^ {- 1} \boldsymbol {\Phi} ^ {\top} \boldsymbol {y}.\tag{9.31}
$$

Comparing the MAP estimate in (9.31) with the maximum likelihood estimate in (9.19), we see that the only difference between both solutions is the additional term $\begin{array} { r } { \frac { \sigma ^ { 2 } } { b ^ { 2 } } I } \end{array}$ in the inverse matrix. This term ensures that 

$\Phi ^ { \top }$ Φ is symmetric, positive semi definite. The additional term in (9.31) is strictly positive definite so that the inverse exists. 

$\begin{array} { r } { \Phi ^ { \top } \Phi + \frac { \sigma ^ { 2 } } { b ^ { 2 } } I } \end{array}$ is symmetric and strictly positive definite (i.e., its inverse exists and the MAP estimate is the unique solution of a system of linear equations). Moreover, it reflects the impact of the regularizer. 

## Example 9.6 (MAP Estimation for Polynomial Regression)

In the polynomial regression example from Section 9.2.1, we place a Gaussian prior $p ( \pmb \theta ) = \mathcal { N } ( \mathbf 0 , I )$ on the parameters θ and determine the MAP estimates according to (9.31). In Figure 9.7, we show both the maximum likelihood and the MAP estimates for polynomials of degree 6 (left) and degree 8 (right). The prior (regularizer) does not play a significant role for the low-degree polynomial, but keeps the function relatively smooth for higher-degree polynomials. Although the MAP estimate can push the boundaries of overfitting, it is not a general solution to this problem, so we need a more principled approach to tackle overfitting. 

Figure 9.7 Polynomial regression: maximum likelihood and MAP estimates. (a) Polynomials of degree 6; (b) polynomials of degree 8. 

![image](<Images/09_Linear_Regression_image_017.jpg>)



(a) Polynomials of degree 6.


![image](<Images/09_Linear_Regression_image_018.jpg>)



(b) Polynomials of degree 8.


## 9.2.4 MAP Estimation as Regularization

Instead of placing a prior distribution on the parameters $\theta ,$ it is also possible to mitigate the effect of overfitting by penalizing the amplitude of the parameter by means of regularization. In regularized least squares, we consider the loss function 

$$
\left\| \boldsymbol {y} - \boldsymbol {\Phi} \boldsymbol {\theta} \right\| ^ {2} + \lambda \left\| \boldsymbol {\theta} \right\| _ {2} ^ {2},\tag{9.32}
$$

which we minimize with respect to $\pmb \theta$ (see Section 8.2.3). Here, the first term is a data $- f i t$ term (also called misfit term), which is proportional to the negative log-likelihood; see (9.10b). The second term is called the regularizer, and the regularization parameter $\lambda \geqslant 0$ controls the “strictness” of the regularization. 

Remark. Instead of the Euclidean norm $\left\| \cdot \right\| _ { 2 }$ , we can choose any p-norm $\left\| \cdot \right\| _ { p }$ in (9.32). In practice, smaller values for $p$ lead to sparser solutions. Here, “sparse” means that many parameter values $\theta _ { d } = 0 _ { i }$ , which is also useful for variable selection. For $p = 1$ , the regularizer is called LASSO (least absolute shrinkage and selection operator) and was proposed by Tibshirani (1996). $\diamondsuit$ 

The regularizer $\lambda \left. \pmb { \theta } \right. _ { 2 } ^ { 2 }$ in (9.32) can be interpreted as a negative log-Gaussian prior, which we use in MAP estimation; see (9.26). More specifically, with a Gaussian prior $p ( \pmb \theta ) = \mathcal { N } ( \mathbf 0 , b ^ { 2 } \pmb I )$ , we obtain the negative log-Gaussian prior 

$$
- \log p (\boldsymbol {\theta}) = \frac {1}{2 b ^ {2}} \| \boldsymbol {\theta} \| _ {2} ^ {2} + \text { const }\tag{9.33}
$$

so that for $\begin{array} { r } { \lambda = \frac { 1 } { 2 b ^ { 2 } } } \end{array}$ the regularization term and the negative log-Gaussian prior are identical. 

Given that the regularized least-squares loss function in (9.32) consists of terms that are closely related to the negative log-likelihood plus a negative log-prior, it is not surprising that, when we minimize this loss, we obtain a solution that closely resembles the MAP estimate in (9.31). More specifically, minimizing the regularized least-squares loss function yields 

$$
\boldsymbol {\theta} _ {\mathrm{RLS}} = \left(\boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi} + \lambda \boldsymbol {I}\right) ^ {- 1} \boldsymbol {\Phi} ^ {\top} \boldsymbol {y},\tag{9.34}
$$

which is identical to the MAP estimate in (9.31) for $\textstyle \lambda = { \frac { \sigma ^ { 2 } } { b ^ { 2 } } }$ , where $\sigma ^ { 2 }$ is the noise variance and $b ^ { 2 }$ the variance of the (isotropic) Gaussian prior $p ( \pmb \theta ) = \mathcal { N } \big ( \mathbf 0 , b ^ { 2 } \pmb I \big )$ 

So far, we have covered parameter estimation using maximum likelihood and MAP estimation where we found point estimates $\pmb { \theta } ^ { * }$ that optimize an objective function (likelihood or posterior). We saw that both maximum likelihood and MAP estimation can lead to overfitting. In the next section, we will discuss Bayesian linear regression, where we use Bayesian inference (Section 8.4) to find a posterior distribution over the unknown parameters, which we subsequently use to make predictions. More specifically, for predictions we will average over all plausible sets of parameters instead of focusing on a point estimate. 

## 9.3 Bayesian Linear Regression

Previously, we looked at linear regression models where we estimated the model parameters θ, e.g., by means of maximum likelihood or MAP estimation. We discovered that MLE can lead to severe overfitting, in particular, in the small-data regime. MAP addresses this issue by placing a prior on the parameters that plays the role of a regularizer. 

Bayesian linear regression pushes the idea of the parameter prior a step further and does not even attempt to compute a point estimate of the parameters, but instead the full posterior distribution over the parameters is taken into account when making predictions. This means we do not fit any parameters, but we compute a mean over all plausible parameters settings (according to the posterior). 

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

## 9.3.1 Model

In Bayesian linear regression, we consider the model 

$$
\begin{array}{l l} \text {prior} & p (\boldsymbol {\theta}) = \mathcal {N} \big (\boldsymbol {m} _ {0},   \boldsymbol {S} _ {0} \big)  , \\ \text {likelihood} & p (y \mid \boldsymbol {x}, \boldsymbol {\theta}) = \mathcal {N} \big (y \mid \boldsymbol {\phi} ^ {\top} (\boldsymbol {x}) \boldsymbol {\theta},   \sigma^ {2} \big)  , \end{array}\tag{9.35}
$$

![image](<Images/09_Linear_Regression_image_019.jpg>)


where we now explicitly place a Gaussian prior $p ( \pmb \theta ) = \mathcal { N } \big ( m _ { 0 } , S _ { 0 } \big )$ on $\theta ,$ which turns the parameter vector into a random variable. This allows us to write down the corresponding graphical model in Figure 9.8, where we made the parameters of the Gaussian prior on $\pmb \theta$ explicit. The full probabilistic model, i.e., the joint distribution of observed and unobserved random variables, y and $\theta ,$ , respectively, is 

$$
p (y, \boldsymbol {\theta} \mid \boldsymbol {x}) = p (y \mid \boldsymbol {x}, \boldsymbol {\theta}) p (\boldsymbol {\theta}).\tag{9.36}
$$

## 9.3.2 Prior Predictions

In practice, we are usually not so much interested in the parameter values $\pmb \theta$ themselves. Instead, our focus often lies in the predictions we make with those parameter values. In a Bayesian setting, we take the parameter distribution and average over all plausible parameter settings when we make predictions. More specifically, to make predictions at an input $^ { \mathbf { x } } { } _ { * }$ we integrate out $\pmb \theta$ and obtain 

$$
p (y _ {*} \mid \boldsymbol {x} _ {*}) = \int p (y _ {*} \mid \boldsymbol {x} _ {*}, \pmb {\theta}) p (\pmb {\theta}) \mathrm{d} \pmb {\theta} = \mathbb {E} _ {\pmb {\theta}} [ p (y _ {*} \mid \boldsymbol {x} _ {*}, \pmb {\theta}) ],\tag{9.37}
$$

which we can interpret as the average prediction of $y _ { * } \mid x _ { * } , \theta$ for all plausible parameters $\pmb \theta$ according to the prior distribution $p ( \pmb \theta )$ . Note that predictions using the prior distribution only require us to specify the input $^ { \mathbf { x } } { } _ { * }$ , but no training data. 

In our model (9.35), we chose a conjugate (Gaussian) prior on $\pmb \theta$ so that the predictive distribution is Gaussian as well (and can be computed in closed form): With the prior distribution $p ( \pmb \theta ) = \mathcal { N } \big ( m _ { 0 } , S _ { 0 } \big )$ , we obtain the predictive distribution as 

$$
p (y _ {*} \mid \boldsymbol {x} _ {*}) = \mathcal {N} \big (\boldsymbol {\phi} ^ {\top} (\boldsymbol {x} _ {*}) \boldsymbol {m} _ {0}, \boldsymbol {\phi} ^ {\top} (\boldsymbol {x} _ {*}) \boldsymbol {S} _ {0} \boldsymbol {\phi} (\boldsymbol {x} _ {*}) + \sigma^ {2} \big),\tag{9.38}
$$

where we exploited that (i) the prediction is Gaussian due to conjugacy (see Section $6 . 6 )$ and the marginalization property of Gaussians (see Section 6.5), (ii) the Gaussian noise is independent so that 

$$
\mathbb {V} [ y _ {*} ] = \mathbb {V} _ {\pmb {\theta}} [ \pmb {\phi} ^ {\top} (\pmb {x} _ {*}) \pmb {\theta} ] + \mathbb {V} _ {\epsilon} [ \epsilon ],\tag{9.39}
$$

and (iii) $y _ { * }$ is a linear transformation of $\pmb \theta$ so that we can apply the rules for computing the mean and covariance of the prediction analytically by using (6.50) and (6.51), respectively. In (9.38), the term $\phi ^ { \top } ( { \pmb x } _ { * } ) S _ { 0 } \phi ( { \pmb x } _ { * } )$ in the predictive variance explicitly accounts for the uncertainty associated with the parameters $\theta ,$ whereas $\sigma ^ { 2 }$ is the uncertainty contribution due to the measurement noise. 

If we are interested in predicting noise-free function values $f ( x _ { * } ) =$ $\phi ^ { \top } ( x _ { * } ) \theta$ instead of the noise-corrupted targets $y _ { * }$ we obtain 

$$
p (f (\boldsymbol {x} _ {*})) = \mathcal {N} \big (\boldsymbol {\phi} ^ {\top} (\boldsymbol {x} _ {*}) \boldsymbol {m} _ {0}, \boldsymbol {\phi} ^ {\top} (\boldsymbol {x} _ {*}) \boldsymbol {S} _ {0} \boldsymbol {\phi} (\boldsymbol {x} _ {*}) \big),\tag{9.40}
$$

which only differs from (9.38) in the omission of the noise variance $\sigma ^ { 2 }$ in the predictive variance. 

Remark (Distribution over Functions). Since we can represent the distribution $p ( \pmb \theta )$ using a set of samples $\pmb \theta _ { i }$ and every sample $\pmb \theta _ { i }$ gives rise to a function $f _ { i } ( \cdot ) = \mathbf { \bar { \theta } } _ { i } ^ { \top } \boldsymbol { \phi } ( \cdot )$ , it follows that the parameter distribution $p ( \pmb \theta )$ induces a distribution $p ( f ( \cdot ) )$ over functions. Here we use the notation ( ) to explicitly denote a functional relationship. 

## Example 9.7 (Prior over Functions)

![image](<Images/09_Linear_Regression_image_020.jpg>)



(a) Prior distribution over functions.


![image](<Images/09_Linear_Regression_image_021.jpg>)



(b) Samples from the prior distribution over functions.


Let us consider a Bayesian linear regression problem with polynomials of degree 5. We choose a parameter prior $p ( \pmb \theta ) = \mathcal { N } \big ( \mathbf 0 , \frac { 1 } { 4 } \pmb I \big )$ . Figure 9.9 visualizes the induced prior distribution over functions (shaded area: dark gray: 67% confidence bound; light gray: 95% confidence bound) induced by this parameter prior, including some function samples from this prior. 

A function sample is obtained by first sampling a parameter vector $\theta _ { i } \sim p ( \theta )$ and then computing $f _ { i } ( \cdot ) = \pmb { \theta } _ { i } ^ { \top } \phi ( \cdot )$ . We used 200 input locations $x _ { * } ~ \in ~ [ - 5 , 5 ]$ to which we apply the feature function $\phi ( \cdot )$ . The uncertainty (represented by the shaded area) in Figure 9.9 is solely due to the parameter uncertainty because we considered the noise-free predictive distribution (9.40). 

So $\operatorname { f a r } ,$ we looked at computing predictions using the parameter prior $p ( \pmb \theta )$ . However, when we have a parameter posterior (given some training data , ), the same principles for prediction and inference hold as in (9.37) – we just need to replace the prior $p ( \pmb \theta )$ with the posterior $p ( \pmb \theta | \mathcal { X } , \mathcal { Y } )$ . In the following, we will derive the posterior distribution in detail before using it to make predictions. 

## 9.3.3 Posterior Distribution

Given a training set of inputs ${ \pmb x } _ { n } \in \mathbb { R } ^ { D }$ and corresponding observations $y _ { n } \in \mathbb { R } , n = 1 , \dots , N$ , we compute the posterior over the parameters using Bayes’ theorem as 

$$
p (\boldsymbol {\theta} \mid \mathcal {X}, \mathcal {Y}) = \frac {p (\mathcal {Y} \mid \mathcal {X} , \boldsymbol {\theta}) p (\boldsymbol {\theta})}{p (\mathcal {Y} \mid \mathcal {X})},\tag{9.41}
$$

where $\mathcal { X }$ is the set of training inputs and the collection of corresponding training targets. Furthermore, $p ( \mathcal { V } | \mathcal { X } , \pmb { \theta } )$ is the likelihood, $p ( \pmb \theta )$ the parameter prior, and 

$$
p (\mathcal {Y} \mid \mathcal {X}) = \int p (\mathcal {Y} \mid \mathcal {X}, \boldsymbol {\theta}) p (\boldsymbol {\theta}) \mathrm{d} \boldsymbol {\theta} = \mathbb {E} _ {\boldsymbol {\theta}} [ p (\mathcal {Y} \mid \mathcal {X}, \boldsymbol {\theta}) ]\tag{9.42}
$$

the marginal likelihood/evidence, which is independent of the parameters $\pmb \theta$ and ensures that the posterior is normalized, i.e., it integrates to 1. We can think of the marginal likelihood as the likelihood averaged over all possible parameter settings (with respect to the prior distribution $p ( \pmb \theta ) )$ . 

Theorem 9.1 (Parameter Posterior). In our model (9.35), the parameter posterior (9.41) can be computed in closed form as 

$$
p (\boldsymbol {\theta} \mid \mathcal {X}, \mathcal {Y}) = \mathcal {N} \bigl (\boldsymbol {\theta} \mid \boldsymbol {m} _ {N}, \boldsymbol {S} _ {N} \bigr),\tag{9.43a}
$$

$$
\boldsymbol {S} _ {N} = (\boldsymbol {S} _ {0} ^ {- 1} + \sigma^ {- 2} \boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi}) ^ {- 1},\tag{9.43b}
$$

$$
\pmb {m} _ {N} = \pmb {S} _ {N} (\pmb {S} _ {0} ^ {- 1} \pmb {m} _ {0} + \sigma^ {- 2} \pmb {\Phi} ^ {\top} \pmb {y}),\tag{9.43c}
$$

where the subscript N indicates the size of the training set. 

Proof Bayes’ theorem tells us that the posterior $p ( \pmb \theta | \mathcal { X } , \mathcal { Y } )$ is proportional to the product of the likelihood $p ( \mathcal { V } | \mathcal { X } , \pmb { \theta } )$ and the prior $p ( \pmb \theta )$ 

$$
\text { Posterior } \quad p (\boldsymbol {\theta} \mid \mathcal {X}, \mathcal {Y}) = \frac {p (\mathcal {Y} \mid \mathcal {X} , \boldsymbol {\theta}) p (\boldsymbol {\theta})}{p (\mathcal {Y} \mid \mathcal {X})}\tag{9.44a}
$$

$$
\text { Likelihood } \quad p (\mathcal {Y} \mid \mathcal {X}, \boldsymbol {\theta}) = \mathcal {N} (\boldsymbol {y} \mid \boldsymbol {\Phi} \boldsymbol {\theta}, \sigma^ {2} \boldsymbol {I})\tag{9.44b}
$$

$$
\text { Prior } \quad p (\boldsymbol {\theta}) = \mathcal {N} \bigl (\boldsymbol {\theta} \mid \boldsymbol {m} _ {0},   \boldsymbol {S} _ {0} \bigr).\tag{9.44c}
$$

Instead of looking at the product of the prior and the likelihood, we can transform the problem into log-space and solve for the mean and covariance of the posterior by completing the squares. 

The sum of the log-prior and the log-likelihood is 

$$
\log \mathcal {N} (\boldsymbol {y} \mid \boldsymbol {\Phi} \boldsymbol {\theta}, \sigma^ {2} \boldsymbol {I}) + \log \mathcal {N} (\boldsymbol {\theta} \mid \boldsymbol {m} _ {0}, \boldsymbol {S} _ {0})\tag{9.45a}
$$

$$
= - \frac {1}{2} \left(\sigma^ {- 2} (\boldsymbol {y} - \boldsymbol {\Phi} \boldsymbol {\theta}) ^ {\top} (\boldsymbol {y} - \boldsymbol {\Phi} \boldsymbol {\theta}) + (\boldsymbol {\theta} - \boldsymbol {m} _ {0}) ^ {\top} S _ {0} ^ {- 1} (\boldsymbol {\theta} - \boldsymbol {m} _ {0})\right) + \text { const }\tag{9.45b}
$$

where the constant contains terms independent of $\pmb \theta .$ We will ignore the constant in the following. We now factorize (9.45b), which yields 

$$
\begin{array}{l} - \frac {1}{2} \left(\sigma^ {- 2} \boldsymbol {y} ^ {\top} \boldsymbol {y} - 2 \sigma^ {- 2} \boldsymbol {y} ^ {\top} \boldsymbol {\Phi} \boldsymbol {\theta} + \boldsymbol {\theta} ^ {\top} \sigma^ {- 2} \boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi} \boldsymbol {\theta} + \boldsymbol {\theta} ^ {\top} \boldsymbol {S} _ {0} ^ {- 1} \boldsymbol {\theta} \right. \\ - 2 \boldsymbol {m} _ {0} ^ {\top} \boldsymbol {S} _ {0} ^ {- 1} \boldsymbol {\theta} + \boldsymbol {m} _ {0} ^ {\top} \boldsymbol {S} _ {0} ^ {- 1} \boldsymbol {m} _ {0}) \\ = - \frac {1}{2} \left(\boldsymbol {\theta} ^ {\top} \left(\sigma^ {- 2} \boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi} + \boldsymbol {S} _ {0} ^ {- 1}\right) \boldsymbol {\theta} - 2 \left(\sigma^ {- 2} \boldsymbol {\Phi} ^ {\top} \boldsymbol {y} + \boldsymbol {S} _ {0} ^ {- 1} \boldsymbol {m} _ {0}\right) ^ {\top} \boldsymbol {\theta}\right) + \text {const}, \end{array} \tag {9.46a}\tag{9.46b}
$$

where the constant contains the black terms in (9.46a), which are independent of $\pmb { \theta } .$ . The orange terms are terms that are linear in $\theta ,$ and the blue terms are the ones that are quadratic in $\pmb \theta .$ Inspecting (9.46b), we find that this equation is quadratic in $\pmb { \theta } .$ The fact that the unnormalized log-posterior distribution is a (negative) quadratic form implies that the posterior is Gaussian, i.e., 

$$
p (\boldsymbol {\theta} \mid \mathcal {X}, \mathcal {Y}) = \exp (\log p (\boldsymbol {\theta} \mid \mathcal {X}, \mathcal {Y})) \propto \exp (\log p (\mathcal {Y} \mid \mathcal {X}, \boldsymbol {\theta}) + \log p (\boldsymbol {\theta}))\tag{9.47a}
$$

$$
\propto \exp \left(- \frac {1}{2} \big (\boldsymbol {\theta} ^ {\top} (\sigma^ {- 2} \boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi} + \boldsymbol {S} _ {0} ^ {- 1}) \boldsymbol {\theta} - 2 (\sigma^ {- 2} \boldsymbol {\Phi} ^ {\top} \boldsymbol {y} + \boldsymbol {S} _ {0} ^ {- 1} \boldsymbol {m} _ {0}) ^ {\top} \boldsymbol {\theta} \big)\right),\tag{9.47b}
$$

where we used (9.46b) in the last expression. 

The remaining task is it to bring this (unnormalized) Gaussian into the form that is proportional to $\mathcal { N } ( \pmb { \theta } | \pmb { m } _ { N } , \pmb { S } _ { N } )$ , i.e., we need to identify the mean $\mathbf {  { m } } _ { N }$ and the covariance matrix $S _ { N }$ . To do this, we use the concept of completing the squares. The desired log-posterior is 

$$
\begin{array}{l} \log \mathcal {N} \big (\boldsymbol {\theta} \mid \boldsymbol {m} _ {N},   \boldsymbol {S} _ {N} \big) = - \frac {1}{2} (\boldsymbol {\theta} - \boldsymbol {m} _ {N}) ^ {\top} \boldsymbol {S} _ {N} ^ {- 1} (\boldsymbol {\theta} - \boldsymbol {m} _ {N}) + \text {const} \\ \qquad = - \frac {1}{2} \big (\boldsymbol {\theta} ^ {\top} \boldsymbol {S} _ {N} ^ {- 1} \boldsymbol {\theta} - 2 \boldsymbol {m} _ {N} ^ {\top} \boldsymbol {S} _ {N} ^ {- 1} \boldsymbol {\theta} + \boldsymbol {m} _ {N} ^ {\top} \boldsymbol {S} _ {N} ^ {- 1} \boldsymbol {m} _ {N} \big). \end{array}\tag{9.48a}
$$

(9.48b) 

Here, we factorized the quadratic form $( { \pmb \theta } - { \pmb m } _ { N } ) ^ { \top } { \pmb S } _ { N } ^ { - 1 } ( { \pmb \theta } - { \pmb m } _ { N } )$ into a term that is quadratic in $\pmb \theta$ alone (blue), a term that is linear in $\pmb \theta$ (orange), and a constant term (black). This allows us now to find $S _ { N }$ and m by matching the colored expressions in (9.46b) and (9.48b), which yields 

$$
\boldsymbol {S} _ {N} ^ {- 1} = \boldsymbol {\Phi} ^ {\top} \sigma^ {- 2} \boldsymbol {I} \boldsymbol {\Phi} + \boldsymbol {S} _ {0} ^ {- 1}\tag{9.49a}
$$

$$
\Longleftrightarrow \boldsymbol {S} _ {N} = \left(\sigma^ {- 2} \boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi} + \boldsymbol {S} _ {0} ^ {- 1}\right) ^ {- 1}\tag{9.49b}
$$

and 

$$
\pmb {m} _ {N} ^ {\top} \pmb {S} _ {N} ^ {- 1} = \left(\sigma^ {- 2} \pmb {\Phi} ^ {\top} \pmb {y} + \pmb {S} _ {0} ^ {- 1} \pmb {m} _ {0}\right) ^ {\top}
$$

$$
\Longleftrightarrow \boldsymbol {m} _ {N} = \boldsymbol {S} _ {N} \left(\sigma^ {- 2} \boldsymbol {\Phi} ^ {\top} \boldsymbol {y} + \boldsymbol {S} _ {0} ^ {- 1} \boldsymbol {m} _ {0}\right).\tag{9.50a}
$$

(9.50b) 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



Remark (General Approach to Completing the Squares). If we are given an equation 

$$
\boldsymbol {x} ^ {\top} \boldsymbol {A} \boldsymbol {x} - 2 \boldsymbol {a} ^ {\top} \boldsymbol {x} + \operatorname{const} _ {1},\tag{9.51}
$$

where $\pmb { A }$ is symmetric and positive definite, which we wish to bring into the form 

$$
\left(\boldsymbol {x} - \boldsymbol {\mu}\right) ^ {\top} \boldsymbol {\Sigma} (\boldsymbol {x} - \boldsymbol {\mu}) + \operatorname{const} _ {2},\tag{9.52}
$$

we can do this by setting 

$$
\boldsymbol {\Sigma} := \boldsymbol {A},\tag{9.53}
$$

$$
\pmb {\mu} := \pmb {\Sigma} ^ {- 1} \pmb {a}\tag{9.54}
$$

and $\mathrm { c o n s t _ { 2 } } = \mathrm { c o n s t _ { 1 } } - \mu ^ { \top } \Sigma \mu$ 

♢ 

We can see that the terms inside the exponential in (9.47b) are of the form (9.51) with 

$$
\boldsymbol {A} := \sigma^ {- 2} \boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi} + \boldsymbol {S} _ {0} ^ {- 1},\tag{9.55}
$$

$$
\boldsymbol {a} := \sigma^ {- 2} \boldsymbol {\Phi} ^ {\top} \boldsymbol {y} + \boldsymbol {S} _ {0} ^ {- 1} \boldsymbol {m} _ {0}.\tag{9.56}
$$

Since ${ \mathbf { } } A , a$ can be difficult to identify in equations like (9.46a), it is often helpful to bring these equations into the form (9.51) that decouples quadratic term, linear terms, and constants, which simplifies finding the desired solution. 

## 9.3.4 Posterior Predictions

In (9.37), we computed the predictive distribution of $y _ { * }$ at a test input x<sub>∗</sub> using the parameter prior $p ( \pmb \theta )$ . In principle, predicting with the parameter posterior $p ( \pmb \theta | \mathcal { X } , \mathcal { Y } )$ is not fundamentally different given that in our conjugate model the prior and posterior are both Gaussian (with different parameters). Therefore, by following the same reasoning as in Section 9.3.2, we obtain the (posterior) predictive distribution 

$$
p (y _ {*} \mid \mathcal {X}, \mathcal {Y}, \boldsymbol {x} _ {*}) = \int p (y _ {*} \mid \boldsymbol {x} _ {*}, \boldsymbol {\theta}) p (\boldsymbol {\theta} \mid \mathcal {X}, \mathcal {Y}) \mathrm{d} \boldsymbol {\theta}\tag{9.57a}
$$

$$
= \int \mathcal {N} \left(y _ {*} \mid \phi^ {\top} \left(\boldsymbol {x} _ {*}\right) \boldsymbol {\theta}, \sigma^ {2}\right) \mathcal {N} \left(\boldsymbol {\theta} \mid \boldsymbol {m} _ {N}, \boldsymbol {S} _ {N}\right) \mathrm{d} \boldsymbol {\theta}\tag{9.57b}
$$

$$
= \mathcal {N} \big (y _ {*} \mid \boldsymbol {\phi} ^ {\top} (\boldsymbol {x} _ {*}) \boldsymbol {m} _ {N}, \boldsymbol {\phi} ^ {\top} (\boldsymbol {x} _ {*}) \boldsymbol {S} _ {N} \boldsymbol {\phi} (\boldsymbol {x} _ {*}) + \sigma^ {2} \big)\tag{9.57c}
$$

E[y<sub>∗</sub> | X, Y, x<sub>∗</sub>] = ϕ<sup>⊤</sup>(x<sub>∗</sub>)m<sub>N</sub> = $\phi ^ { \top } ( { \pmb x } _ { * } ) { \pmb \theta } _ { \mathrm { M A P } } ,$ 

The term ${ \phi } ^ { \top } ( { \pmb x } _ { * } ) { \pmb S } _ { N } { \phi } ( { \pmb x } _ { * } )$ reflects the posterior uncertainty associated with the parameters θ. Note that $S _ { N }$ depends on the training inputs through Φ; see (9.43b). The predictive mean $\phi ^ { \top } ( { \pmb x } _ { * } ) m _ { N }$ coincides with the predictions made with the MAP estimate $\theta _ { \mathrm { M A P } }$ 

Remark (Marginal Likelihood and Posterior Predictive Distribution). By replacing the integral in (9.57a), the predictive distribution can be equivalently written as the expectation $\mathbb { E } _ { \pmb { \theta } \mid x , y } [ p ( y _ { \ast } \mid \pmb { x } _ { \ast } , \pmb { \theta } ) ]$ , where the expectation is taken with respect to the parameter posterior $p ( \pmb \theta | \mathcal { X } , \mathcal { Y } )$ 

Writing the posterior predictive distribution in this way highlights a close resemblance to the marginal likelihood (9.42). The key difference between the marginal likelihood and the posterior predictive distribution are (i) the marginal likelihood can be thought of predicting the training targets y and not the test targets $y _ { * }$ , and (ii) the marginal likelihood averages with respect to the parameter prior and not the parameter posterior. ◇ 

Remark (Mean and Variance of Noise-Free Function Values). In many cases, we are not interested in the predictive distribution $p ( y _ { * } | \mathcal { X } , \mathcal { Y } , x _ { * } )$ of a (noisy) observation $y _ { * }$ . Instead, we would like to obtain the distribution of the (noise-free) function values $f ( { \pmb x } _ { * } ) = \phi ^ { \top } ( { \pmb x } _ { * } ) \pmb \theta$ . We determine the corresponding moments by exploiting the properties of means and variances, which yields 

$$
\begin{array}{r} \mathbb {E} [ f (\pmb {x} _ {*}) | \mathcal {X}, \mathcal {Y} ] = \mathbb {E} _ {\pmb {\theta}} [ \phi^ {\top} (\pmb {x} _ {*}) \pmb {\theta} | \mathcal {X}, \mathcal {Y} ] = \phi^ {\top} (\pmb {x} _ {*}) \mathbb {E} _ {\pmb {\theta}} [ \pmb {\theta} | \mathcal {X}, \mathcal {Y} ] \\ = \phi^ {\top} (\pmb {x} _ {*}) \pmb {m} _ {N} = \pmb {m} _ {N} ^ {\top} \phi (\pmb {x} _ {*}), \end{array}\tag{9.58}
$$

$$
\begin{array}{r l} & {\mathbb {V} _ {\boldsymbol {\theta}} [ f (\boldsymbol {x} _ {*}) \mid \mathcal {X}, \mathcal {Y} ] = \mathbb {V} _ {\boldsymbol {\theta}} [ \phi^ {\top} (\boldsymbol {x} _ {*}) \boldsymbol {\theta} \mid \mathcal {X}, \mathcal {Y} ]} \\ & {\qquad = \phi^ {\top} (\boldsymbol {x} _ {*}) \mathbb {V} _ {\boldsymbol {\theta}} [ \boldsymbol {\theta} \mid \mathcal {X}, \mathcal {Y} ] \phi (\boldsymbol {x} _ {*})} \\ & {\qquad = \phi^ {\top} (\boldsymbol {x} _ {*}) S _ {N} \phi (\boldsymbol {x} _ {*}).} \end{array}\tag{9.59}
$$

We see that the predictive mean is the same as the predictive mean for noisy observations as the noise has mean 0, and the predictive variance only differs by $\sigma ^ { 2 }$ , which is the variance of the measurement noise: When we predict noisy function values, we need to include $\sigma ^ { 2 }$ as a source of uncertainty, but this term is not needed for noise-free predictions. Here, the only remaining uncertainty stems from the parameter posterior. 

Remark (Distribution over Functions). The fact that we integrate out the parameters θ induces a distribution over functions: If we sample $\theta _ { i } \sim$ $p ( \pmb \theta | \mathcal { X } , \mathcal { Y } )$ from the parameter posterior, we obtain a single function realization $\theta _ { i } ^ { \top } \phi ( \cdot )$ . The mean function, i.e., the set of all expected function values $\mathbb { E } _ { \pmb { \theta } } [ \bar { f } ( \cdot ) | \pmb { \theta } , \mathcal { X } , \mathcal { Y } ]$ , of this distribution over functions is $m _ { N } ^ { \top } \phi ( \cdot )$ The (marginal) variance, i.e., the variance of the function $f ( \cdot )$ , is given by $\phi ^ { \top } ( \cdot ) S _ { N } \phi ( \cdot )$ 

## Example 9.8 (Posterior over Functions)

Let us revisit the Bayesian linear regression problem with polynomials of degree 5. We choose a parameter prior $p ( \pmb \theta ) = \mathcal { N } \big ( \mathbf 0 , \frac { 1 } { 4 } \pmb I \big )$ . Figure 9.9 visualizes the prior over functions induced by the parameter prior and sample functions from this prior. 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



Figure 9.10 shows the posterior over functions that we obtain via Bayesian linear regression. The training dataset is shown in panel (a); panel (b) shows the posterior distribution over functions, including the functions we would obtain via maximum likelihood and MAP estimation. The function we obtain using the MAP estimate also corresponds to the posterior mean function in the Bayesian linear regression setting. Panel (c) shows some plausible realizations (samples) of functions under that posterior over functions. 

Figure 9.10 Bayesian linear regression and posterior over functions. (a) training data; (b) posterior distribution over functions; (c) Samples from the posterior over functions. 

![image](<Images/09_Linear_Regression_image_022.jpg>)



(a) Training data.


![image](<Images/09_Linear_Regression_image_023.jpg>)


![image](<Images/09_Linear_Regression_image_024.jpg>)



(b) Posterior over functions rep- (c) Samples from the posterior resented by the marginal uncer- over functions, which are intainties (shaded) showing the duced by the samples from the 67% and 95% predictive con- parameter posterior. fidence bounds, the maximum likelihood estimate (MLE) and the MAP estimate (MAP), the latter of which is identical to the posterior mean function.


Figure 9.11 shows some posterior distributions over functions induced by the parameter posterior. For different polynomial degrees $M ,$ , the left panels show the maximum likelihood function $\theta _ { \mathrm { M L } } ^ { \top } \phi ( \cdot )$ , the MAP function $\theta _ { \mathrm { M A P } } ^ { \top } \phi ( \cdot )$ (which is identical to the posterior mean function), and the 67% and 95% predictive confidence bounds obtained by Bayesian linear regression, represented by the shaded areas. 

The right panels show samples from the posterior over functions: Here, we sampled parameters $\pmb \theta _ { i }$ from the parameter posterior and computed the function $\phi ^ { \top } ( { \pmb x } _ { * } ) \pmb \theta _ { i }$ , which is a single realization of a function under the posterior distribution over functions. For low-order polynomials, the parameter posterior does not allow the parameters to vary much: The sampled functions are nearly identical. When we make the model more flexible by adding more parameters (i.e., we end up with a higher-order polynomial), these parameters are not sufficiently constrained by the posterior, and the sampled functions can be easily visually separated. We also see in the corresponding panels on the left how the uncertainty increases, especially at the boundaries. 

Although for a seventh-order polynomial the MAP estimate yields a reasonable fit, the Bayesian linear regression model additionally tells us that 

311 

## 9.3 Bayesian Linear Regression

![image](<Images/09_Linear_Regression_image_025.jpg>)



(a) Posterior distribution for polynomials of degree M = 3 (left) and samples from the posterior over functions (right).


![image](<Images/09_Linear_Regression_image_026.jpg>)


![image](<Images/09_Linear_Regression_image_027.jpg>)


![image](<Images/09_Linear_Regression_image_028.jpg>)



Figure 9.11 Bayesian linear regression. Left panels: Shaded areas indicate the 67% (dark gray) and 95% (light gray) predictive confidence bounds. The mean of the Bayesian linear regression model coincides with the MAP estimate. The predictive uncertainty is the sum of the noise term and the posterior parameter uncertainty, which depends on the location of the test input. Right panels: sampled functions from the posterior distribution.



(b) Posterior distribution for polynomials of degree M = 5 (left) and samples from the posterior over functions (right).


![image](<Images/09_Linear_Regression_image_029.jpg>)


![image](<Images/09_Linear_Regression_image_030.jpg>)



(c) Posterior distribution for polynomials of degree M = 7 (left) and samples from the posterior over functions (right).


the posterior uncertainty is huge. This information can be critical when we use these predictions in a decision-making system, where bad decisions can have significant consequences (e.g., in reinforcement learning or robotics). 

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

## 9.3.5 Computing the Marginal Likelihood

In Section 8.6.2, we highlighted the importance of the marginal likelihood for Bayesian model selection. In the following, we compute the marginal likelihood for Bayesian linear regression with a conjugate Gaussian prior on the parameters, i.e., exactly the setting we have been discussing in this chapter. 

Just to recap, we consider the following generative process: 

$$
\boldsymbol {\theta} \sim \mathcal {N} (\boldsymbol {m} _ {0}, \boldsymbol {S} _ {0})\tag{9.60a}
$$

$$
y _ {n} \mid \boldsymbol {x} _ {n}, \boldsymbol {\theta} \sim \mathcal {N} \left(\boldsymbol {x} _ {n} ^ {\top} \boldsymbol {\theta}, \sigma^ {2}\right),\tag{9.60b}
$$

The marginal likelihood can be interpreted as the expected likelihood under the prior, $\mathrm { i . e . , }$ $\mathbb { E } _ { \pmb { \theta } } [ p ( \mathcal { V } | \mathcal { X } , \pmb { \theta } ) ]$ . 

$n = 1 , \ldots , N$ . The marginal likelihood is given by 

$$
p (\mathcal {Y} \mid \mathcal {X}) = \int p (\mathcal {Y} \mid \mathcal {X}, \pmb {\theta}) p (\pmb {\theta}) \mathrm{d} \pmb {\theta}\tag{9.61a}
$$

$$
= \int \mathcal {N} (\boldsymbol {y} | \boldsymbol {X} \boldsymbol {\theta}, \sigma^ {2} \boldsymbol {I}) \mathcal {N} (\boldsymbol {\theta} | \boldsymbol {m} _ {0}, \boldsymbol {S} _ {0}) \mathrm{d} \boldsymbol {\theta},\tag{9.61b}
$$

where we integrate out the model parameters θ. We compute the marginal likelihood in two steps: First, we show that the marginal likelihood is Gaussian (as a distribution in $_ { y ) }$ ; second, we compute the mean and covariance of this Gaussian. 

1. The marginal likelihood is Gaussian: From Section 6.5.2, we know that (i) the product of two Gaussian random variables is an (unnormalized) Gaussian distribution, and (ii) a linear transformation of a Gaussian random variable is Gaussian distributed. In (9.61b), we require a linear transformation to bring $\mathcal { N } ( \pmb { y } | \pmb { X \theta } , \sigma ^ { 2 } \pmb { I } )$  into the form $\mathcal { N } ( \pmb { \theta } | \pmb { \mu } , \pmb { \Sigma } )$ for some $\mu , \Sigma$ . Once this is done, the integral can be solved in closed form. The result is the normalizing constant of the product of the two Gaussians. The normalizing constant itself has Gaussian shape; see (6.76). 

2. Mean and covariance. We compute the mean and covariance matrix of the marginal likelihood by exploiting the standard results for means and covariances of affine transformations of random variables; see Section 6.4.4. The mean of the marginal likelihood is computed as 

$$
\mathbb {E} [ \mathcal {Y} \mid \mathcal {X} ] = \mathbb {E} _ {\boldsymbol {\theta}, \epsilon} [ \boldsymbol {X} \boldsymbol {\theta} + \epsilon ] = \boldsymbol {X} \mathbb {E} _ {\boldsymbol {\theta}} [ \boldsymbol {\theta} ] = \boldsymbol {X} \boldsymbol {m} _ {0}.\tag{9.62}
$$

Note that $\epsilon \sim \mathcal { N } ( 0 , \sigma ^ { 2 } I )$ is a vector of i.i.d. random variables. The covariance matrix is given as 

$$
\operatorname{Cov} [ \mathcal {Y} | \mathcal {X} ] = \operatorname{Cov} _ {\boldsymbol {\theta}, \epsilon} [ \boldsymbol {X} \boldsymbol {\theta} + \epsilon ] = \operatorname{Cov} _ {\boldsymbol {\theta}} [ \boldsymbol {X} \boldsymbol {\theta} ] + \sigma^ {2} \boldsymbol {I}\tag{9.63a}
$$

$$
= \boldsymbol {X} \operatorname{Cov} _ {\boldsymbol {\theta}} [ \boldsymbol {\theta} ] \boldsymbol {X} ^ {\top} + \sigma^ {2} \boldsymbol {I} = \boldsymbol {X} \boldsymbol {S} _ {0} \boldsymbol {X} ^ {\top} + \sigma^ {2} \boldsymbol {I}.\tag{9.63b}
$$

Hence, the marginal likelihood is 

$$
p (\mathcal {Y} | \mathcal {X}) = (2 \pi) ^ {- \frac {N}{2}} \det (\boldsymbol {X} \boldsymbol {S} _ {0} \boldsymbol {X} ^ {\top} + \sigma^ {2} \boldsymbol {I}) ^ {- \frac {1}{2}}\tag{9.64a}
$$

$$
\cdot \exp \left(- \frac {1}{2} (\boldsymbol {y} - \boldsymbol {X m} _ {0}) ^ {\top} (\boldsymbol {X S} _ {0} \boldsymbol {X} ^ {\top} + \sigma^ {2} \boldsymbol {I}) ^ {- 1} (\boldsymbol {y} - \boldsymbol {X m} _ {0})\right)
$$

## 9.4 Maximum Likelihood as Orthogonal Projection

![image](<Images/09_Linear_Regression_image_031.jpg>)


![image](<Images/09_Linear_Regression_image_032.jpg>)



(a) Regression dataset consisting of noisy observations $y _ { n }$ (blue) of function values $f ( x _ { n } )$ at input locations $x _ { n }$



Figure 9.12 Geometric interpretation of least squares. (a) Dataset; (b) maximum likelihood solution interpreted as a projection.



(b) The orange dots are the projections of the noisy observations (blue dots) onto the line $\theta _ { \mathrm { M L } } x$ . The maximum likelihood solution to a linear regression problem finds a subspace (line) onto which the overall projection error (orange lines) of the observations is minimized.


$$
= \mathcal {N} (\boldsymbol {y} \mid \boldsymbol {X m} _ {0}, \boldsymbol {X S} _ {0} \boldsymbol {X} ^ {\top} + \sigma^ {2} \boldsymbol {I}).\tag{9.64b}
$$

Given the close connection with the posterior predictive distribution (see Remark on Marginal Likelihood and Posterior Predictive Distribution earlier in this section), the functional form of the marginal likelihood should not be too surprising. 

## 9.4 Maximum Likelihood as Orthogonal Projection

Having crunched through much algebra to derive maximum likelihood and MAP estimates, we will now provide a geometric interpretation of maximum likelihood estimation. Let us consider a simple linear regression setting 

$$
y = x \theta + \epsilon , \quad \epsilon \sim \mathcal {N} (0, \sigma^ {2}),\tag{9.65}
$$

in which we consider linear functions $f : \mathbb { R }  \mathbb { R }$ that go through the origin (we omit features here for clarity). The parameter θ determines the slope of the line. Figure 9.12(a) shows a one-dimensional dataset. 

With a training data set $\left\{ ( x _ { 1 } , y _ { 1 } ) , \dotsc , ( x _ { N } , y _ { N } ) \right\}$ we recall the results from Section 9.2.1 and obtain the maximum likelihood estimator for the slope parameter as 

$$
\theta_ {\mathrm{ML}} = \left(\boldsymbol {X} ^ {\top} \boldsymbol {X}\right) ^ {- 1} \boldsymbol {X} ^ {\top} \boldsymbol {y} = \frac {\boldsymbol {X} ^ {\top} \boldsymbol {y}}{\boldsymbol {X} ^ {\top} \boldsymbol {X}} \in \mathbb {R},\tag{9.66}
$$

where $\begin{array} { r } { \pmb { X } = [ x _ { 1 } , \dotsc , x _ { N } ] ^ { \top } \in \mathbb { R } ^ { N } , \pmb { y } = [ y _ { 1 } , \dotsc , y _ { N } ] ^ { \top } \in \mathbb { R } ^ { N } . } \end{array}$ 

This means for the training inputs X we obtain the optimal (maximum likelihood) reconstruction of the training targets as 

$$
\pmb {X} \theta_ {\mathrm{ML}} = \pmb {X} \frac {\pmb {X} ^ {\top} \pmb {y}}{\pmb {X} ^ {\top} \pmb {X}} = \frac {\pmb {X} \pmb {X} ^ {\top}}{\pmb {X} ^ {\top} \pmb {X}} \pmb {y},\tag{9.67}
$$



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



i.e., we obtain the approximation with the minimum least-squares error between y and $X \theta .$ 

As we are looking for a solution of $y = X \theta$ , we can think of linear regression as a problem for solving systems of linear equations. Therefore, we can relate to concepts from linear algebra and analytic geometry that we discussed in Chapters 2 and 3. In particular, looking carefully at (9.67) we see that the maximum likelihood estimator $\theta _ { \mathrm { M L } }$ in our example from (9.65) effectively does an orthogonal projection of $\textbf {  { y } }$ onto the one-dimensional subspace spanned by $\boldsymbol { X }$ . Recalling the results on orthogonal projections from Section 3.8, we identify $\frac { x x ^ { \top } } { X ^ { \top } X }$ as the projection matrix, $\theta _ { \mathrm { M L } }$ as the coordinates of the projection onto the one-dimensional subspace of $\mathbb { R } ^ { N }$ spanned by X and $\pmb { X \theta } _ { \mathrm { M L } }$ as the orthogonal projection of y onto this subspace. 

Therefore, the maximum likelihood solution provides also a geometrically optimal solution by finding the vectors in the subspace spanned by X that are “closest” to the corresponding observations y, where “closest” means the smallest (squared) distance of the function values $y _ { n }$ to $x _ { n } \theta$ . This is achieved by orthogonal projections. Figure 9.12(b) shows the projection of the noisy observations onto the subspace that minimizes the squared distance between the original dataset and its projection (note that the x-coordinate is fixed), which corresponds to the maximum likelihood solution. 

In the general linear regression case where 

$$
y = \boldsymbol {\phi} ^ {\top} (\boldsymbol {x}) \boldsymbol {\theta} + \epsilon , \quad \epsilon \sim \mathcal {N} (0, \sigma^ {2})\tag{9.68}
$$

with vector-valued features $\pmb { \phi } ( \pmb { x } ) \in \mathbb { R } ^ { K }$ , we again can interpret the maximum likelihood result 

$$
\pmb {y} \approx \Phi \pmb {\theta} _ {\mathrm{ML}},\tag{9.69}
$$

$$
\boldsymbol {\theta} _ {\mathrm{ML}} = \left(\boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi}\right) ^ {- 1} \boldsymbol {\Phi} ^ {\top} \boldsymbol {y}\tag{9.70}
$$

as a projection onto a K-dimensional subspace of $\mathbb { R } ^ { N }$ , which is spanned by the columns of the feature matrix $\Phi ;$ see Section 3.8.2. 

If the feature functions $\phi _ { k }$ that we use to construct the feature matrix Φ are orthonormal (see Section 3.7), we obtain a special case where the columns of Φ form an orthonormal basis (see Section 3.5), such that $\Phi ^ { \top } \Phi = I$ . This will then lead to the projection 

$$
\boldsymbol {\Phi} \left(\boldsymbol {\Phi} ^ {\top} \boldsymbol {\Phi}\right) ^ {- 1} \boldsymbol {\Phi} ^ {\top} \boldsymbol {y} = \boldsymbol {\Phi} \boldsymbol {\Phi} ^ {\top} \boldsymbol {y} = \left(\sum_ {k = 1} ^ {K} \phi_ {k} \phi_ {k} ^ {\top}\right) \boldsymbol {y}\tag{9.71}
$$

so that the maximum likelihood projection is simply the sum of projections of $\textbf {  { y } }$ onto the individual basis vectors $\phi _ { k } , \mathrm { i . e . }$ , the columns of $\Phi$ . Furthermore, the coupling between different features has disappeared due to the orthogonality of the basis. Many popular basis functions in signal processing, such as wavelets and Fourier bases, are orthogonal basis functions. 

## 9.5 Further Reading

When the basis is not orthogonal, one can convert a set of linearly inde pendent basis functions to an orthogonal basis by using the Gram-Schmidt process; see Section 3.8.3 and (Strang, 2003). 

## 9.5 Further Reading

In this chapter, we discussed linear regression for Gaussian likelihoods and conjugate Gaussian priors on the parameters of the model. This allowed for closed-form Bayesian inference. However, in some applications we may want to choose a different likelihood function. For example, in a binary classification setting, we observe only two possible (categorical) outcomes, and a Gaussian likelihood is inappropriate in this setting. Instead, we can choose a Bernoulli likelihood that will return a probability of the predicted label to be 1 (or 0). We refer to the books by Barber (2012), Bishop (2006), and Murphy (2012) for an in-depth introduction to classification problems. A different example where non-Gaussian likelihoods are important is count data. Counts are non-negative integers, and in this case a Binomial or Poisson likelihood would be a better choice than a Gaussian. All these examples fall into the category of generalized linear models, a flexible generalization of linear regression that allows for response variables that have error distributions other than a Gaussian distribution. The GLM generalizes linear regression by allowing the linear model to be related to the observed values via a smooth and invertible function $\sigma ( \cdot )$ that may be nonlinear so that $y = \sigma ( f ( { \pmb x } ) )$ ), where $f ( { \pmb x } ) = { \pmb \theta } ^ { \top } \phi ( { \pmb x } )$ is the linear regression model from (9.13). We can therefore think of a generalized linear model in terms of function composition $y = \sigma \circ f ,$ , where $f$ is a linear regression model and σ the activation function. Note that although we are talking about “generalized linear models”, the outputs y are no longer linear in the parameters θ. In logistic regression, we choose the logistic sigmoid $\begin{array} { r } { \sigma ( f ) = \frac { 1 } { 1 + \exp ( - f ) } \in [ 0 , 1 ] } \end{array}$ ], which can be interpreted as the probability of observing $y = 1$ of a Bernoulli random variable $y \in \{ 0 , 1 \}$ The function $\sigma ( \cdot )$ is called transfer function or activation function, and its inverse is called the canonical link function. From this perspective, it is also clear that generalized linear models are the building blocks of (deep) feedforward neural networks: If we consider a generalized linear model $\pmb { y } = \sigma ( \pmb { A } \pmb { x } + \pmb { b } )$ , where A is a weight matrix and b a bias vector, we identify this generalized linear model as a single-layer neural network with activation function $\sigma ( \cdot )$ . We can now recursively compose these functions via 

$$
\begin{array}{c} \boldsymbol {x} _ {k + 1} = \boldsymbol {f} _ {k} (\boldsymbol {x} _ {k}) \\ \boldsymbol {f} _ {k} (\boldsymbol {x} _ {k}) = \sigma_ {k} (\boldsymbol {A} _ {k} \boldsymbol {x} _ {k} + \boldsymbol {b} _ {k}) \end{array}\tag{9.72}
$$

for $k = 0 , \ldots , K - 1$ , where $\scriptstyle { \pmb x } _ { 0 }$ are the input features and $\scriptstyle { \pmb x } _ { K } \ = \ { \pmb y }$ are the observed outputs, such that $\pmb { f } _ { K - 1 } \circ \cdots \circ \pmb { f } _ { 0 }$ is a K-layer deep neural network. Therefore, the building blocks of this deep neural network are the generalized linear models defined in (9.72). Neural networks (Bishop, 1995; Goodfellow et al., 2016) are significantly more expressive and flexible than linear regression models. However, maximum likelihood parameter estimation is a non-convex optimization problem, and marginalization of the parameters in a fully Bayesian setting is analytically intractable. 

We briefly hinted at the fact that a distribution over parameters induces a distribution over regression functions. Gaussian processes (Rasmussen and Williams, 2006) are regression models where the concept of a distribution over function is central. Instead of placing a distribution over parameters, a Gaussian process places a distribution directly on the space of functions without the “detour” via the parameters. To do so, the Gaussian process exploits the kernel trick (Scholkopf and Smola¨ , 2002), which allows us to compute inner products between two function values $f ( \pmb { x } _ { i } ) , f ( \pmb { x } _ { j } )$ only by looking at the corresponding input $\mathbf { \Delta } _ { x _ { i } , \mathbf { \Delta } _ { x _ { j } } }$ . A Gaussian process is closely related to both Bayesian linear regression and support vector regression but can also be interpreted as a Bayesian neural network with a single hidden layer where the number of units tends to infinity (Neal, 1996; Williams, 1997). Excellent introductions to Gaussian processes can be found in MacKay (1998) and Rasmussen and Williams (2006). 

We focused on Gaussian parameter priors in the discussions in this chapter, because they allow for closed-form inference in linear regression models. However, even in a regression setting with Gaussian likelihoods, we may choose a non-Gaussian prior. Consider a setting, where the inputs are $\pmb { x } \in \mathbb { R } ^ { D }$ and our training set is small and of size $N \ll D$ . This means that the regression problem is underdetermined. In this case, we can choose a parameter prior that enforces sparsity, i.e., a prior that tries to set as many parameters to 0 as possible (variable selection). This prior provides a stronger regularizer than the Gaussian prior, which often leads to an increased prediction accuracy and interpretability of the model. The Laplace prior is one example that is frequently used for this purpose. A linear regression model with the Laplace prior on the parameters is equivalent to linear regression with L1 regularization (LASSO) (Tibshirani, 1996). The Laplace distribution is sharply peaked at zero (its first derivative is discontinuous) and it concentrates its probability mass closer to zero than the Gaussian distribution, which encourages parameters to be 0. Therefore, the nonzero parameters are relevant for the regression problem, which is the reason why we also speak of “variable selection”. 