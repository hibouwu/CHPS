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

