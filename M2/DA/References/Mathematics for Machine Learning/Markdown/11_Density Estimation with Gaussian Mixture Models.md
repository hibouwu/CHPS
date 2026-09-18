![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_001.jpg>)


## Density Estimation with Gaussian Mixture Models

In earlier chapters, we covered already two fundamental problems in machine learning: regression (Chapter 9) and dimensionality reduction (Chapter 10). In this chapter, we will have a look at a third pillar of machine learning: density estimation. On our journey, we introduce important concepts, such as the expectation maximization (EM) algorithm and a latent variable perspective of density estimation with mixture models. 

When we apply machine learning to data we often aim to represent data in some way. A straightforward way is to take the data points themselves as the representation of the data; see Figure 11.1 for an example. However, this approach may be unhelpful if the dataset is huge or if we are interested in representing characteristics of the data. In density estimation, we represent the data compactly using a density from a parametric family, e.g., a Gaussian or Beta distribution. For example, we may be looking for the mean and variance of a dataset in order to represent the data compactly using a Gaussian distribution. The mean and variance can be found using tools we discussed in Section 8.3: maximum likelihood or maximum a posteriori estimation. We can then use the mean and variance of this Gaussian to represent the distribution underlying the data, i.e., we think of the dataset to be a typical realization from this distribution if we were to sample from it. 

Figure 11.1 Two-dimensional dataset that cannot be meaningfully represented by a Gaussian. 

![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_002.jpg>)



This material is published by Cambridge University Press as Mathematicsfor Machine Learning by Marc Peter Deisenroth, A. Aldo Faisal, and Cheng Soon Ong (2020). This version is free to view and download for personal use only. Not for re-distribution, re-sale, or use in derivative works. ©by M. P. Deisenroth, A. A. Faisal, and C. S. Ong, 2024. https://mml-book.com.


In practice, the Gaussian (or similarly all other distributions we encountered so far) have limited modeling capabilities. For example, a Gaussian approximation of the density that generated the data in Figure 11.1 would be a poor approximation. In the following, we will look at a more expressive family of distributions, which we can use for density estimation: mixture models. 

Mixture models can be used to describe a distribution $p ( { \pmb x } )$ by a convex combination of K simple (base) distributions 

$$
p (\boldsymbol {x}) = \sum_ {k = 1} ^ {K} \pi_ {k} p _ {k} (\boldsymbol {x})\tag{11.1}
$$

$$
0 \leqslant \pi_ {k} \leqslant 1, \quad \sum_ {k = 1} ^ {K} \pi_ {k} = 1,\tag{11.2}
$$

where the components $p _ { k }$ are members of a family of basic distributions, $\mathsf { e . g . }$ , Gaussians, Bernoullis, or Gammas, and the $\pi _ { k }$ are mixture weights. Mixture models are more expressive than the corresponding base distributions because they allow for multimodal data representations, i.e., they can describe datasets with multiple “clusters”, such as the example in Figure 11.1. 

We will focus on Gaussian mixture models (GMMs), where the basic distributions are Gaussians. For a given dataset, we aim to maximize the likelihood of the model parameters to train the GMM. For this purpose, we will use results from Chapter 5, Chapter 6, and Section 7.2. However, unlike other applications we discussed earlier (linear regression or PCA), we will not find a closed-form maximum likelihood solution. Instead, we will arrive at a set of dependent simultaneous equations, which we can only solve iteratively. 

## 11.1 Gaussian Mixture Model

A Gaussian mixture model is a density model where we combine a finite number of K Gaussian distributions $\mathcal { N } ( \pmb { x } | \pmb { \mu } _ { k } , \pmb { \Sigma } _ { k } )$ so that 

$$
p (\boldsymbol {x} \mid \boldsymbol {\theta}) = \sum_ {k = 1} ^ {K} \pi_ {k} \mathcal {N} \left(\boldsymbol {x} \mid \boldsymbol {\mu} _ {k}, \boldsymbol {\Sigma} _ {k}\right)\tag{11.3}
$$

$$
0 \leqslant \pi_ {k} \leqslant 1, \quad \sum_ {k = 1} ^ {K} \pi_ {k} = 1,\tag{11.4}
$$

where we defined $\pmb \theta : = \{ \pmb \mu _ { k } , \pmb \Sigma _ { k } , \pi _ { k } : k = 1 , \ldots , K \}$ as the collection of all parameters of the model. This convex combination of Gaussian distribution gives us significantly more flexibility for modeling complex densities than a simple Gaussian distribution (which we recover from (11.3) for $K = 1 )$ . An illustration is given in Figure 11.2, displaying the weighted 

Figure 11.2 Gaussian mixture model. The Gaussian mixture distribution (black) is composed of a convex combination of Gaussian distributions and is more expressive than any individual component. Dashed lines represent the weighted Gaussian components. 

![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_003.jpg>)



components and the mixture density, which is given as


$$
p (x \mid \boldsymbol {\theta}) = 0. 5 \mathcal {N} (x \mid - 2, \frac {1}{2}) + 0. 2 \mathcal {N} (x \mid 1, 2) + 0. 3 \mathcal {N} (x \mid 4, 1)\tag{11.5}
$$

## 11.2 Parameter Learning via Maximum Likelihood

Assume we are given a dataset $\mathcal { X } ~ = ~ \{ { \pmb x } _ { 1 } , \ldots , { \pmb x } _ { N } \}$ , where $x _ { n } , \ n \ =$ $1 , \ldots , N ,$ are drawn i.i.d. from an unknown distribution $p ( { \pmb x } )$ . Our objective is to find a good approximation/representation of this unknown distribution $p ( { \pmb x } )$ by means of a GMM with $K$ mixture components. The parameters of the GMM are the $K$ means $\mu _ { k } ,$ , the covariances $\Sigma _ { k } ,$ , and mixture weights $\pi _ { k } .$ . We summarize all these free parameters in $\pmb \theta : =$ $\{ \pi _ { k } , \pmb { \mu } _ { k } , \pmb { \Sigma } _ { k } : ~ k = 1 , \ldots , K \}$ 

## Example 11.1 (Initial Setting)

Figure 11.3 Initial setting: GMM (black) with mixture three mixture components (dashed) and seven data points (discs). 

![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_004.jpg>)



Throughout this chapter, we will have a simple running example that helps us illustrate and visualize important concepts.


We consider a one-dimensional dataset $\mathcal { X } = \{ - 3 , - 2 . 5 , - 1 , 0 , 2 , 4 , 5 \}$ consisting of seven data points and wish to find a GMM with $K \ : = \ : 3$ components that models the density of the data. We initialize the mixture components as 

$$
p _ {1} (x) = \mathcal {N} (x \mid - 4, 1)\tag{11.6}
$$

$$
p _ {2} (x) = \mathcal {N} (x \mid 0, 0. 2)\tag{11.7}
$$

$$
p _ {3} (x) = \mathcal {N} (x \mid 8, 3)\tag{11.8}
$$

and assign them equal weights $\pi _ { 1 } = \pi _ { 2 } = \pi _ { 3 } = { \frac { 1 } { 3 } }$ . The corresponding model (and the data points) are shown in Figure 11.3. 

In the following, we detail how to obtain a maximum likelihood estimate $\pmb { \theta } _ { \mathrm { M I } }$ of the model parameters θ. We start by writing down the likelihood, i.e., the predictive distribution of the training data given the parameters. We exploit our i.i.d. assumption, which leads to the factorized likelihood 

$$
p (\mathcal {X} \mid \boldsymbol {\theta}) = \prod_ {n = 1} ^ {N} p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta}), \quad p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta}) = \sum_ {k = 1} ^ {K} \pi_ {k} \mathcal {N} \left(\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {k}, \boldsymbol {\Sigma} _ {k}\right),\tag{11.9}
$$

where every individual likelihood term $p ( \pmb { x } _ { n } \mid \pmb { \theta } )$ is a Gaussian mixture density. Then we obtain the log-likelihood as 

$$
\log p (\mathcal {X} \mid \boldsymbol {\theta}) = \sum_ {n = 1} ^ {N} \log p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta}) = \underbrace {\sum_ {n = 1} ^ {N} \log \sum_ {k = 1} ^ {K} \pi_ {k} \mathcal {N} \left(\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {k} , \boldsymbol {\Sigma} _ {k}\right)} _ {=: \mathcal {L}}.\tag{11.10}
$$

We aim to find parameters ${ \pmb \theta } _ { \mathrm { M I } } ^ { * }$ that maximize the log-likelihood $\mathcal { L }$ defined in (11.10). Our “normal” procedure would be to compute the gradient $\mathrm { d } { \mathcal { L } } / \mathrm { d } \theta$ of the log-likelihood with respect to the model parameters $\theta ,$ set it to $\mathbf { 0 , }$ and solve for θ. However, unlike our previous examples for maximum likelihood estimation $( \mathsf { e . g . }$ , when we discussed linear regression in Section 9.2), we cannot obtain a closed-form solution. However, we can exploit an iterative scheme to find good model parameters $\pmb { \theta } _ { \mathrm { M L } }$ , which will turn out to be the EM algorithm for GMMs. The key idea is to update one model parameter at a time while keeping the others fixed. 

Remark. If we were to consider a single Gaussian as the desired density, the sum over $k$ in (11.10) vanishes, and the log can be applied directly to the Gaussian component, such that we get 

$$
\log \mathcal {N} (\boldsymbol {x} \mid \boldsymbol {\mu}, \boldsymbol {\Sigma}) = - \frac {D}{2} \log (2 \pi) - \frac {1}{2} \log \det (\boldsymbol {\Sigma}) - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu}).\tag{11.11}
$$

This simple form allows us to find closed-form maximum likelihood estimates of $\pmb { \mu }$ and $\Sigma ,$ as discussed in Chapter 8. In (11.10), we cannot move the log into the sum over k so that we cannot obtain a simple closed-form maximum likelihood solution. ◇ 

Any local optimum of a function exhibits the property that its gradient with respect to the parameters must vanish (necessary condition); see Chapter 7. In our case, we obtain the following necessary conditions when we optimize the log-likelihood in (11.10) with respect to the GMM parameters $\mu _ { k } , \Sigma _ { k } , \pi _ { k }$ 

$$
\frac {\partial \mathcal {L}}{\partial \boldsymbol {\mu} _ {k}} = \mathbf {0} ^ {\top} \iff \sum_ {n = 1} ^ {N} \frac {\partial \log p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})}{\partial \boldsymbol {\mu} _ {k}} = \mathbf {0} ^ {\top},\tag{11.12}
$$

$$
\frac {\partial \mathcal {L}}{\partial \boldsymbol {\Sigma} _ {k}} = \mathbf {0} \iff \sum_ {n = 1} ^ {N} \frac {\partial \log p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})}{\partial \boldsymbol {\Sigma} _ {k}} = \mathbf {0},\tag{11.13}
$$

$$
\frac {\partial \mathcal {L}}{\partial \pi_ {k}} = 0 \iff \sum_ {n = 1} ^ {N} \frac {\partial \log p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})}{\partial \pi_ {k}} = 0.\tag{11.14}
$$

For all three necessary conditions, by applying the chain rule (see Section 5.2.2), we require partial derivatives of the form 

$$
\frac {\partial \log p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})}{\partial \boldsymbol {\theta}} = \frac {1}{p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})} \frac {\partial p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})}{\partial \boldsymbol {\theta}},\tag{11.15}
$$

where $\pmb \theta = \{ \pmb \mu _ { k } , \pmb \Sigma _ { k } , \pi _ { k } , k = 1 , \ldots , K \}$ are the model parameters and 

$$
\frac {1}{p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})} = \frac {1}{\sum_ {j = 1} ^ {K} \pi_ {j} \mathcal {N} \left(\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {j} , \boldsymbol {\Sigma} _ {j}\right)}.\tag{11.16}
$$

In the following, we will compute the partial derivatives (11.12) through (11.14). But before we do this, we introduce a quantity that will play a central role in the remainder of this chapter: responsibilities. 

## 11.2.1 Responsibilities

We define the quantity 

$$
r _ {n k} := \frac {\pi_ {k} \mathcal {N} (\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {k} , \boldsymbol {\Sigma} _ {k})}{\sum_ {j = 1} ^ {K} \pi_ {j} \mathcal {N} (\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {j} , \boldsymbol {\Sigma} _ {j})}\tag{11.17}
$$

as the responsibility of the kth mixture component for the nth data point. The responsibility $r _ { n k }$ of the kth mixture component for data point ${ \bf { x } } _ { n }$ is proportional to the likelihood 

$$
p (\boldsymbol {x} _ {n} \mid \pi_ {k}, \boldsymbol {\mu} _ {k}, \boldsymbol {\Sigma} _ {k}) = \pi_ {k} \mathcal {N} \big (\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {k}, \boldsymbol {\Sigma} _ {k} \big)\tag{11.18}
$$

of the mixture component given the data point. Therefore, mixture components have a high responsibility for a data point when the data point could be a plausible sample from that mixture component. Note that $\pmb { r } _ { n } : = [ r _ { n 1 } , \ldots , r _ { n K } ] ^ { \top } \in \bar { \mathbb { R } } ^ { K }$ is a (normalized) probability vector, i.e., $\textstyle \sum _ { k } r _ { n k } = 1$ with $r _ { n k } \ \geqslant \ 0$ . This probability vector distributes probability mass among the K mixture components, and we can think of $\boldsymbol { r } _ { n }$ as a “soft assignment” of ${ \pmb x } _ { n }$ to the K mixture components. Therefore, the responsibility $r _ { n k }$ from (11.17) represents the probability that ${ \bf { x } } _ { n }$ has been generated by the kth mixture component. 

## Example 11.2 (Responsibilities)

For our example from Figure 11.3, we compute the responsibilities $r _ { n k }$ 

$$
\left[ \begin{array}{c c c} 1. 0 & 0. 0 & 0. 0 \\ 1. 0 & 0. 0 & 0. 0 \\ 0. 0 5 7 & 0. 9 4 3 & 0. 0 \\ 0. 0 0 1 & 0. 9 9 9 & 0. 0 \\ 0. 0 & 0. 0 6 6 & 0. 9 3 4 \\ 0. 0 & 0. 0 & 1. 0 \\ 0. 0 & 0. 0 & 1. 0 \end{array} \right] \in \mathbb {R} ^ {N \times K}.\tag{11.19}
$$

Here the nth row tells us the responsibilities of all mixture components for $x _ { n } .$ The sum of all K responsibilities for a data point (sum of every row) is 1. The kth column gives us an overview of the responsibility of the kth mixture component. We can see that the third mixture component (third column) is not responsible for any of the first four data points, but takes much responsibility of the remaining data points. The sum of all entries of a column gives us the values $N _ { k }$ , i.e., the total responsibility of the kth mixture component. In our example, we get $N _ { 1 } = 2 . 0 5 8$ $N _ { 2 } =$ $2 . 0 0 8 , N _ { 3 } = 2 . 9 3 4$ 

In the following, we determine the updates of the model parameters $\mu _ { k } , \Sigma _ { k } , \pi _ { k }$ for given responsibilities. We will see that the update equations all depend on the responsibilities, which makes a closed-form solution to the maximum likelihood estimation problem impossible. However, for given responsibilities we will be updating one model parameter at a time, while keeping the others fixed. After this, we will recompute the responsibilities. Iterating these two steps will eventually converge to a local optimum and is a specific instantiation of the EM algorithm. We will discuss this in some more detail in Section 11.3. 

## 11.2.2 Updating the Means

Theorem 11.1 (Update of the GMM Means). The update of the mean parameters $\begin{array} { r } { \mu _ { k } , k = 1 , \ldots , K , } \end{array}$ , of the GMM is given by 

$$
\pmb {\mu} _ {k} ^ {n e w} = \frac {\sum_ {n = 1} ^ {N} r _ {n k} \pmb {x} _ {n}}{\sum_ {n = 1} ^ {N} r _ {n k}},\tag{11.20}
$$

where the responsibilities $r _ { n k }$ are defined in (11.17). 

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

Remark. The update of the means $\pmb { \mu } _ { k }$ of the individual mixture components in (11.20) depends on all means, covariance matrices $\Sigma _ { k }$ , and mixture weights $\pi _ { k }$ via $r _ { n k }$ given in (11.17). Therefore, we cannot obtain a closed-form solution for all $\pmb { \mu } _ { k }$ at once. 

Proof From (11.15), we see that the gradient of the log-likelihood with respect to the mean parameters $\pmb { \mu } _ { k } , k = 1 , \ldots , K$ , requires us to compute the partial derivative 

$$
\begin{array}{l} \frac {\partial p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})}{\partial \boldsymbol {\mu} _ {k}} = \sum_ {j = 1} ^ {K} \pi_ {j} \frac {\partial \mathcal {N} (\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {j} , \boldsymbol {\Sigma} _ {j})}{\partial \boldsymbol {\mu} _ {k}} = \pi_ {k} \frac {\partial \mathcal {N} (\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {k} , \boldsymbol {\Sigma} _ {k})}{\partial \boldsymbol {\mu} _ {k}} \\ = \pi_ {k} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1} \mathcal {N} (\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {k}, \boldsymbol {\Sigma} _ {k}), \end{array}\tag{11.21a}
$$

(11.21b) 

where we exploited that only the kth mixture component depends on $\pmb { \mu } _ { k }$ We use our result from (11.21b) in (11.15) and put everything together so that the desired partial derivative of with respect to $\pmb { \mu } _ { k }$ is given as 

$$
\frac {\partial \mathcal {L}}{\partial \boldsymbol {\mu} _ {k}} = \sum_ {n = 1} ^ {N} \frac {\partial \log p (\boldsymbol {x} _ {n} | \boldsymbol {\theta})}{\partial \boldsymbol {\mu} _ {k}} = \sum_ {n = 1} ^ {N} \frac {1}{p (\boldsymbol {x} _ {n} | \boldsymbol {\theta})} \frac {\partial p (\boldsymbol {x} _ {n} | \boldsymbol {\theta})}{\partial \boldsymbol {\mu} _ {k}}\tag{11.22a}
$$

(11.22b) 

$$
= \sum_ {n = 1} ^ {N} r _ {n k} (\pmb {x} _ {n} - \pmb {\mu} _ {k}) ^ {\top} \pmb {\Sigma} _ {k} ^ {- 1}.\tag{11.22c}
$$

Here we used the identity from (11.16) and the result of the partial derivative in (11.21b) to get to (11.22b). The values $r _ { n k }$ are the responsibilities we defined in (11.17). 

We now solve (11.22c) for $\mu _ { k } ^ { \mathrm { n e w } }$ so that $\begin{array} { r } { \frac { \partial \mathcal { L } ( \boldsymbol { \mu } _ { k } ^ { \mathrm { n e w } } ) } { \partial \boldsymbol { \mu } _ { k } } = \mathbf { 0 } ^ { \top } } \end{array}$ and obtain 

$$
\sum_ {n = 1} ^ {N} r _ {n k} \boldsymbol {x} _ {n} = \sum_ {n = 1} ^ {N} r _ {n k} \boldsymbol {\mu} _ {k} ^ {\text { new }} \iff \boldsymbol {\mu} _ {k} ^ {\text { new }} = \frac {\sum_ {n = 1} ^ {N} r _ {n k} \boldsymbol {x} _ {n}}{\boxed {\sum_ {n = 1} ^ {N} r _ {n k}}} = \frac {1}{\boxed {N _ {k}}} \sum_ {n = 1} ^ {N} r _ {n k} \boldsymbol {x} _ {n},\tag{11.23}
$$

where we defined 

$$
N _ {k} := \sum_ {n = 1} ^ {N} r _ {n k}\tag{11.24}
$$

as the total responsibility of the kth mixture component for the entire dataset. This concludes the proof of Theorem 11.1. □ 

Intuitively, (11.20) can be interpreted as an importance-weighted Monte Carlo estimate of the mean, where the importance weights of data point ${ \bf { x } } _ { n }$ are the responsibilities $r _ { n k }$ of the kth cluster for $\mathbf { { x } } _ { n } , k = 1 , \ldots , K$ 

Therefore, the mean $\pmb { \mu } _ { k }$ is pulled toward a data point ${ \bf { x } } _ { n }$ with strength given by $r _ { n k }$ . The means are pulled stronger toward data points for which the corresponding mixture component has a high responsibility, i.e., a high likelihood. Figure 11.4 illustrates this. We can also interpret the mean update in (11.20) as the expected value of all data points under the distribution given by 

$$
\boldsymbol {r} _ {k} := \left[ r _ {1 k}, \dots , r _ {N k} \right] ^ {\top} / N _ {k},\tag{11.25}
$$

which is a normalized probability vector, i.e., 

Figure 11.4 Update of the mean parameter of mixture component in a GMM. The mean µ is being pulled toward individual data points with the weights given by the corresponding responsibilities. 

$$
\boldsymbol {\mu} _ {k} \leftarrow \mathbb {E} _ {\boldsymbol {r} _ {k}} [ \mathcal {X} ].\tag{11.26}
$$

## Example 11.3 (Mean Updates)

![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_005.jpg>)


![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_006.jpg>)



(a) GMM density and individual components prior to updating the mean values.


![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_007.jpg>)



(b) GMM density and individual components after updating the mean values.



Figure 11.5 Effect of updating the mean values in a GMM. (a) GMM before updating the mean values; (b) GMM after updating the mean values $\mu _ { k }$ while retaining the variances and mixture weights.


In our example from Figure 11.3, the mean values are updated as follows: 

$$
\mu_ {1}: - 4 \to - 2. 7\tag{11.27}
$$

$$
\mu_ {2}: 0 \to - 0. 4\tag{11.28}
$$

$$
\mu_ {3}: 8 \to 3. 7\tag{11.29}
$$

Here we see that the means of the first and third mixture component move toward the regime of the data, whereas the mean of the second component does not change so dramatically. Figure 11.5 illustrates this change, where Figure 11.5(a) shows the GMM density prior to updating the means and Figure 11.5(b) shows the GMM density after updating the mean values $\mu _ { k }$ 

The update of the mean parameters in (11.20) look fairly straight forward. However, note that the responsibilities $r _ { n k }$ are a function of $\pi _ { j } , \mu _ { j } , \Sigma _ { j }$ for all $j = 1 , \ldots , K$ , such that the updates in (11.20) depend on all parameters of the GMM, and a closed-form solution, which we obtained for linear regression in Section 9.2 or PCA in Chapter 10, cannot be obtained. 

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

## 11.2.3 Updating the Covariances

Theorem 11.2 (Updates of the GMM Covariances). The update of the covariance parameters $\Sigma _ { k } , k = 1 , \dots , K$ of the GMM is given by 

$$
\boldsymbol {\Sigma} _ {k} ^ {n e w} = \frac {1}{N _ {k}} \sum_ {n = 1} ^ {N} r _ {n k} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top},\tag{11.30}
$$

where $r _ { n k }$ and $N _ { k }$ are defined in (11.17) and (11.24), respectively. 

Proof To prove Theorem 11.2, our approach is to compute the partial derivatives of the log-likelihood $\mathcal { L }$ with respect to the covariances $\Sigma _ { k }$ , set them to 0, and solve for $\Sigma _ { k }$ . We start with our general approach 

$$
\frac {\partial \mathcal {L}}{\partial \boldsymbol {\Sigma} _ {k}} = \sum_ {n = 1} ^ {N} \frac {\partial \log p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})}{\partial \boldsymbol {\Sigma} _ {k}} = \sum_ {n = 1} ^ {N} \frac {1}{p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})} \frac {\partial p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})}{\partial \boldsymbol {\Sigma} _ {k}}.\tag{11.31}
$$

We already know $1 / p ( { \pmb x } _ { n } \mid { \pmb \theta } )$ from (11.16). To obtain the remaining partial derivative $\partial p ( { \pmb x } _ { n } \mid \pmb \theta ) / \partial { \pmb \Sigma } _ { k }$ , we write down the definition of the Gaussian distribution $p ( \pmb { x } _ { n } \mid \pmb { \theta } )$ (see (11.9)) and drop all terms but the kth. We then obtain 

$$
\begin{array}{l} \frac {\partial p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})}{\partial \boldsymbol {\Sigma} _ {k}} \\ = \frac {\partial}{\partial \boldsymbol {\Sigma} _ {k}} \left(\pi_ {k} (2 \pi) ^ {- \frac {D}{2}} \det (\boldsymbol {\Sigma} _ {k}) ^ {- \frac {1}{2}} \exp \left(- \frac {1}{2} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k})\right)\right) \end{array} \tag {11.32a}\tag{11.32b}
$$

$$
= \pi_ {k} (2 \pi) ^ {- \frac {D}{2}} \left[ \frac {\partial}{\partial \boldsymbol {\Sigma} _ {k}} \det (\boldsymbol {\Sigma} _ {k}) ^ {- \frac {1}{2}} \exp \left(- \frac {1}{2} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k})\right) \right.
$$

$$
\left. + \det (\pmb {\Sigma} _ {k}) ^ {- \frac {1}{2}} \frac {\partial}{\partial \pmb {\Sigma} _ {k}} \exp \left(- \frac {1}{2} (\pmb {x} _ {n} - \pmb {\mu} _ {k}) ^ {\top} \pmb {\Sigma} _ {k} ^ {- 1} (\pmb {x} _ {n} - \pmb {\mu} _ {k})\right) \right].\tag{11.32c}
$$

We now use the identities 

$$
\frac {\partial}{\partial \boldsymbol {\Sigma} _ {k}} \det (\boldsymbol {\Sigma} _ {k}) ^ {- \frac {1}{2} (5. 1 0 1)} - \frac {1}{2} \det (\boldsymbol {\Sigma} _ {k}) ^ {- \frac {1}{2}} \boldsymbol {\Sigma} _ {k} ^ {- 1},\tag{11.33}
$$

$$
\frac {\partial}{\partial \boldsymbol {\Sigma} _ {k}} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) \stackrel {(5. 1 0 3)} {=} - \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1}\tag{11.34}
$$

and obtain (after some rearranging) the desired partial derivative required in (11.31) as 

$$
\begin{array}{l} \frac {\partial p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})}{\partial \boldsymbol {\Sigma} _ {k}} = \pi_ {k} \mathcal {N} \big (\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {k},   \boldsymbol {\Sigma} _ {k} \big) \\ \quad \cdot \left[ - \frac {1}{2} (\boldsymbol {\Sigma} _ {k} ^ {- 1} - \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1}) \right]. \end{array}\tag{11.35}
$$

Putting everything together, the partial derivative of the log-likelihood 

with respect to $\Sigma _ { k }$ is given by 

$$
\begin{array}{l} \frac {\partial \mathcal {L}}{\partial \boldsymbol {\Sigma} _ {k}} = \sum_ {n = 1} ^ {N} \frac {\partial \log p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})}{\partial \boldsymbol {\Sigma} _ {k}} = \sum_ {n = 1} ^ {N} \frac {1}{p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})} \frac {\partial p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta})}{\partial \boldsymbol {\Sigma} _ {k}} \\ = \sum_ {n = 1} ^ {N} \underbrace {\frac {\pi_ {k} \mathcal {N} (\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {k} , \boldsymbol {\Sigma} _ {k})}{\sum_ {j = 1} ^ {K} \pi_ {j} \mathcal {N} (\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {j} , \boldsymbol {\Sigma} _ {j})}} _ {= r _ {n k}} \\ \cdot \left[ - \frac {1}{2} (\boldsymbol {\Sigma} _ {k} ^ {- 1} - \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1}) \right] \\ = - \frac {1}{2} \sum_ {n = 1} ^ {N} r _ {n k} (\boldsymbol {\Sigma} _ {k} ^ {- 1} - \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1}) \\ = - \frac {1}{2} \boldsymbol {\Sigma} _ {k} ^ {- 1} \underbrace {\sum_ {n = 1} ^ {N} r _ {n k}} _ {= N _ {k}} + \frac {1}{2} \boldsymbol {\Sigma} _ {k} ^ {- 1} \left(\sum_ {n = 1} ^ {N} r _ {n k} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top}\right) \boldsymbol {\Sigma} _ {k} ^ {- 1}. \end{array} \tag {11.36a}\tag{11.36d}
$$

We see that the responsibilities $r _ { n k }$ also appear in this partial derivative. Setting this partial derivative to 0, we obtain the necessary optimality condition 

$$
N _ {k} \boldsymbol {\Sigma} _ {k} ^ {- 1} = \boldsymbol {\Sigma} _ {k} ^ {- 1} \left(\sum_ {n = 1} ^ {N} r _ {n k} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top}\right) \boldsymbol {\Sigma} _ {k} ^ {- 1}\tag{11.37a}
$$

$$
\Longleftrightarrow N _ {k} \boldsymbol {I} = \left(\sum_ {n = 1} ^ {N} r _ {n k} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top}\right) \boldsymbol {\Sigma} _ {k} ^ {- 1}.\tag{11.37b}
$$

By solving for $\Sigma _ { k }$ , we obtain 

$$
\boldsymbol {\Sigma} _ {k} ^ {\text { new }} = \frac {1}{N _ {k}} \sum_ {n = 1} ^ {N} r _ {n k} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top},\tag{11.38}
$$

where $\boldsymbol { r } _ { k }$ is the probability vector defined in (11.25). This gives us a simple update rule for $\Sigma _ { k }$ for $k = 1 , \ldots , K$ and proves Theorem 11.2. 

Similar to the update of $\pmb { \mu } _ { k }$ in (11.20), we can interpret the update of the covariance in (11.30) as an importance-weighted expected value of the square of the centered data $\tilde { \mathcal { X } } _ { k } : = \{ \pmb { x } _ { 1 } - \pmb { \mu } _ { k } , \ldots , \pmb { x } _ { N } - \pmb { \mu } _ { k } \}$ 

## Example 11.4 (Variance Updates)

In our example from Figure 11.3, the variances are updated as follows: 

$$
\sigma_ {1} ^ {2}: 1 \to 0. 1 4\tag{11.39}
$$

$$
\sigma_ {2} ^ {2}: 0. 2 \to 0. 4 4
$$

$$
\sigma_ {3} ^ {2}: 3 \to 1. 5 3\tag{11.40}
$$

(11.41) 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



Here we see that the variances of the first and third component shrink significantly, whereas the variance of the second component increases slightly. 

Figure 11.6 illustrates this setting. Figure 11.6(a) is identical (but zoomed in) to Figure 11.5(b) and shows the GMM density and its individual components prior to updating the variances. Figure 11.6(b) shows the GMM density after updating the variances. 

Figure 11.6 Effect of updating the variances in a GMM. (a) GMM before updating the variances; (b) GMM after updating the variances while retaining the means and mixture weights. 

![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_008.jpg>)



(a) GMM density and individual components prior to updating the variances.


![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_009.jpg>)



(b) GMM density and individual components after updating the variances.


Similar to the update of the mean parameters, we can interpret (11.30) as a Monte Carlo estimate of the weighted covariance of data points ${ \bf { x } } _ { n }$ associated with the kth mixture component, where the weights are the responsibilities $r _ { n k }$ . As with the updates of the mean parameters, this update depends on all $\pi _ { j } , \pmb { \mu } _ { j } , \pmb { \Sigma } _ { j } , j = 1 , \ldots , K$ , through the responsibilities $r _ { n k : }$ , which prohibits a closed-form solution. 

## 11.2.4 Updating the Mixture Weights

Theorem 11.3 (Update of the GMM Mixture Weights). The mixture weights of the GMM are updated as 

$$
\pi_ {k} ^ {\text {new}} = \frac {N _ {k}}{N}, k = 1, \ldots , K,\tag{11.42}
$$

where N is the number of data points and $N _ { k }$ is defined in (11.24). 

Proof To find the partial derivative of the log-likelihood with respect to the weight parameters $\pi _ { k } , \ k \ = \ 1 , \ldots , K$ , we account for the constraint $\textstyle \sum _ { k } \pi _ { k } = 1$ by using Lagrange multipliers (see Section 7.2). The Lagrangian is 

$$
\mathfrak {L} = \mathcal {L} + \lambda \left(\sum_ {k = 1} ^ {K} \pi_ {k} - 1\right)\tag{11.43a}
$$

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



$$
= \sum_ {n = 1} ^ {N} \log \sum_ {k = 1} ^ {K} \pi_ {k} \mathcal {N} \left(\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {k}, \boldsymbol {\Sigma} _ {k}\right) + \lambda \left(\sum_ {k = 1} ^ {K} \pi_ {k} - 1\right),\tag{11.43b}
$$

where $\mathcal { L }$ is the log-likelihood from (11.10) and the second term encodes for the equality constraint that all the mixture weights need to sum up to 1. We obtain the partial derivative with respect to $\pi _ { k }$ as 

$$
\frac {\partial \mathfrak {L}}{\partial \pi_ {k}} = \sum_ {n = 1} ^ {N} \frac {\mathcal {N} (\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {k} , \boldsymbol {\Sigma} _ {k})}{\sum_ {j = 1} ^ {K} \pi_ {j} \mathcal {N} (\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {j} , \boldsymbol {\Sigma} _ {j})} + \lambda\tag{11.44a}
$$

$$
= \frac {1}{\pi_ {k}} \underbrace {\sum_ {n = 1} ^ {N} \frac {\pi_ {k} \mathcal {N} \left(\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {k} , \boldsymbol {\Sigma} _ {k}\right)}{\sum_ {j = 1} ^ {K} \pi_ {j} \mathcal {N} \left(\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {j} , \boldsymbol {\Sigma} _ {j}\right)}} _ {= N _ {k}} + \lambda = \frac {N _ {k}}{\pi_ {k}} + \lambda ,\tag{11.44b}
$$

and the partial derivative with respect to the Lagrange multiplier λ as 

$$
\frac {\partial \mathfrak {L}}{\partial \lambda} = \sum_ {k = 1} ^ {K} \pi_ {k} - 1.\tag{11.45}
$$

Setting both partial derivatives to 0 (necessary condition for optimum) yields the system of equations 

$$
\pi_ {k} = - \frac {N _ {k}}{\lambda},\tag{11.46}
$$

$$
1 = \sum_ {k = 1} ^ {K} \pi_ {k}.\tag{11.47}
$$

Using (11.46) in (11.47) and solving for $\pi _ { k } ,$ , we obtain 

$$
\sum_ {k = 1} ^ {K} \pi_ {k} = 1 \iff - \sum_ {k = 1} ^ {K} \frac {N _ {k}}{\lambda} = 1 \iff - \frac {N}{\lambda} = 1 \iff \lambda = - N.\tag{11.48}
$$

This allows us to substitute N for λ in (11.46) to obtain 

$$
\pi_ {k} ^ {\mathrm{new}} = \frac {N _ {k}}{N},\tag{11.49}
$$

which gives us the update for the weight parameters $\pi _ { k }$ and proves Theorem 11.3. □ 

We can identify the mixture weight in (11.42) as the ratio of the total responsibility of the kth cluster and the number of data points. Since $\begin{array} { r } { N = \sum _ { k } N _ { k } } \end{array}$ , the number of data points can also be interpreted as the total responsibility of all mixture components together, such that $\pi _ { k }$ is the relative importance of the kth mixture component for the dataset. 

Remark. Since $\begin{array} { r } { N _ { k } = \sum _ { i = 1 } ^ { N } r _ { n k } } \end{array}$ , the update equation (11.42) for the mixture weights $\pi _ { k }$ also depends on all $\pi _ { j } , \mu _ { j } , \Sigma _ { j } , j = 1 , \ldots , K$ via the responsibilities $r _ { n k }$ 

Figure 11.7 Effect of updating the mixture weights in a GMM. (a) GMM before updating the mixture weights; (b) GMM after updating the mixture weights while retaining the means and variances. Note the different scales of the vertical axes. 

## Example 11.5 (Weight Parameter Updates)

![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_010.jpg>)



(a) GMM density and individual components prior to updating the mixture weights.


![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_011.jpg>)



(b) GMM density and individual components after updating the mixture weights.


In our running example from Figure 11.3, the mixture weights are updated as follows: 

$$
\pi_ {1}: \frac {1}{3} \to 0. 2 9\tag{11.50}
$$

$$
\pi_ {2}: \frac {1}{3} \to 0. 2 9\tag{11.51}
$$

$$
\pi_ {3}: \frac {1}{3} \to 0. 4 2\tag{11.52}
$$

Here we see that the third component gets more weight/importance, while the other components become slightly less important. Figure 11.7 illustrates the effect of updating the mixture weights. Figure 11.7(a) is identical to Figure 11.6(b) and shows the GMM density and its individual components prior to updating the mixture weights. Figure 11.7(b) shows the GMM density after updating the mixture weights. 

Overall, having updated the means, the variances, and the weights once, we obtain the GMM shown in Figure 11.7(b). Compared with the initialization shown in Figure 11.3, we can see that the parameter updates caused the GMM density to shift some of its mass toward the data points. 

After updating the means, variances, and weights once, the GMM fit in Figure 11.7(b) is already remarkably better than its initialization from Figure 11.3. This is also evidenced by the log-likelihood values, which increased from 28.3 (initialization) to 14.4 after a full update cycle. 

## 11.3 EM Algorithm

Unfortunately, the updates in (11.20), (11.30), and (11.42) do not constitute a closed-form solution for the updates of the parameters $\mu _ { k } , \Sigma _ { k } , \pi _ { k }$ of the mixture model because the responsibilities $r _ { n k }$ depend on those parameters in a complex way. However, the results suggest a simple iterative scheme for finding a solution to the parameters estimation problem via maximum likelihood. The expectation maximization algorithm (EM algorithm) was proposed by Dempster et al. (1977) and is a general iterative scheme for learning parameters (maximum likelihood or MAP) in mixture models and, more generally, latent-variable models. 

In our example of the Gaussian mixture model, we choose initial values for $\mu _ { k } , \Sigma _ { k } , \pi _ { k }$ and alternate until convergence between 

E-step: Evaluate the responsibilities $r _ { n k }$ (posterior probability of data point n belonging to mixture component k). 

M-step: Use the updated responsibilities to reestimate the parameters $\mu _ { k } , \Sigma _ { k } , \pi _ { k }$ 

Every step in the EM algorithm increases the log-likelihood function (Neal and Hinton, 1999). For convergence, we can check the log-likelihood or the parameters directly. A concrete instantiation of the EM algorithm for estimating the parameters of a GMM is as follows: 

1. Initialize $\pmb { \mu } _ { k } , \pmb { \Sigma } _ { k } , \pi _ { k }$ 

2. E-step: Evaluate responsibilities $r _ { n k }$ for every data point ${ \bf { x } } _ { n }$ using current parameters $\pi _ { k } , \pmb { \mu } _ { k } , \pmb { \Sigma } _ { k }$ 

$$
r _ {n k} = \frac {\pi_ {k} \mathcal {N} (\pmb {x} _ {n} | \pmb {\mu} _ {k} , \pmb {\Sigma} _ {k})}{\sum_ {j} \pi_ {j} \mathcal {N} (\pmb {x} _ {n} | \pmb {\mu} _ {j} , \pmb {\Sigma} _ {j})}.\tag{11.53}
$$

3. M-step: Reestimate parameters $\pi _ { k } , \mu _ { k } , \Sigma _ { k }$ using the current responsibilities $r _ { n k }$ (from E-step): 

$$
\pmb {\mu} _ {k} = \frac {1}{N _ {k}} \sum_ {n = 1} ^ {N} r _ {n k} \pmb {x} _ {n},\tag{11.54}
$$

$$
\mu_ {k}
$$

$$
\boldsymbol {\Sigma} _ {k} = \frac {1}{N _ {k}} \sum_ {n = 1} ^ {N} r _ {n k} (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) (\boldsymbol {x} _ {n} - \boldsymbol {\mu} _ {k}) ^ {\top},\tag{11.55}
$$

$$
\pi_ {k} = \frac {N _ {k}}{N}.\tag{11.56}
$$

## Example 11.6 (GMM Fit)

![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_012.jpg>)



(a) Final GMM fit. After five iterations, the EM algorithm converges and returns this GMM.


![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_013.jpg>)



Figure 11.8 EM algorithm applied to the GMM from Figure 11.2. (a) Final GMM fit; (b) negative log-likelihood as a function of the EM iteration.



(b) Negative log-likelihood as a function of the EM iterations.


©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

Figure 11.9 Illustration of the EM algorithm for fitting a Gaussian mixture model with three components to a two-dimensional dataset. (a) Dataset; (b) negative log-likelihood (lower is better) as a function of the EM iterations. The red dots indicate the iterations for which the mixture components of the corresponding GMM fits are shown in (c) through (f). The yellow discs indicate the means of the Gaussian mixture components. Figure 11.10(a) shows the final GMM fit. 

![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_014.jpg>)



(a) Dataset.


![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_015.jpg>)


![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_016.jpg>)



(b) Negative log-likelihood.



(c) EM initialization.


![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_017.jpg>)



(d) EM after one iteration.


![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_018.jpg>)



(e) EM after 10 iterations.


![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_019.jpg>)



(f) EM after 62 iterations.


When we run EM on our example from Figure 11.3, we obtain the final result shown in Figure 11.8(a) after five iterations, and Figure 11.8(b) shows how the negative log-likelihood evolves as a function of the EM iterations. The final GMM is given as 

$$
\begin{array}{c} p (x) = 0. 2 9 \mathcal {N} \big (x \mid - 2. 7 5,   0. 0 6 \big) + 0. 2 8 \mathcal {N} \big (x \mid - 0. 5 0,   0. 2 5 \big) \\ + 0. 4 3 \mathcal {N} \big (x \mid 3. 6 4,   1. 6 3 \big)  . \end{array}\tag{11.57}
$$

We applied the EM algorithm to the two-dimensional dataset shown in Figure 11.1 with $K = 3$ mixture components. Figure 11.9 illustrates some steps of the EM algorithm and shows the negative log-likelihood as a function of the EM iteration (Figure 11.9(b)). Figure 11.10(a) shows 

## 11.4 Latent-Variable Perspective

![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_020.jpg>)



(a) GMM fit after 62 iterations.


![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_021.jpg>)



(b) Dataset colored according to the responsibilities of the mixture components.



Figure 11.10 GMM fit and responsibilities when EM converges. (a) GMM fit when EM converges; (b) each data point is colored according to the responsibilities of the mixture components.


the corresponding final GMM fit. Figure 11.10(b) visualizes the final responsibilities of the mixture components for the data points. The dataset is colored according to the responsibilities of the mixture components when EM converges. While a single mixture component is clearly responsible for the data on the left, the overlap of the two data clusters on the right could have been generated by two mixture components. It becomes clear that there are data points that cannot be uniquely assigned to a single component (either blue or yellow), such that the responsibilities of these two clusters for those points are around 0.5. 

## 11.4 Latent-Variable Perspective

We can look at the GMM from the perspective of a discrete latent-variable model, i.e., where the latent variable z can attain only a finite set of values. This is in contrast to PCA, where the latent variables were continuousvalued numbers in R<sup>M</sup>. 

The advantages of the probabilistic perspective are that (i) it will justify some ad hoc decisions we made in the previous sections, (ii) it allows for a concrete interpretation of the responsibilities as posterior probabil ities, and (iii) the iterative algorithm for updating the model parameters can be derived in a principled manner as the EM algorithm for maximum likelihood parameter estimation in latent-variable models. 

## 11.4.1 Generative Process and Probabilistic Model

To derive the probabilistic model for GMMs, it is useful to think about the generative process, i.e., the process that allows us to generate data, using a probabilistic model. 

We assume a mixture model with K components and that a data point x can be generated by exactly one mixture component. We introduce a binary indicator variable $z _ { k } \in \{ 0 , 1 \}$ with two states (see Section 6.2) that indicates whether the kth mixture component generated that data point 

so that 

$$
p (\boldsymbol {x} \mid z _ {k} = 1) = \mathcal {N} \bigl (\boldsymbol {x} \mid \boldsymbol {\mu} _ {k}, \boldsymbol {\Sigma} _ {k} \bigr).\tag{11.58}
$$

We define $z : = [ z _ { 1 } , \ldots , z _ { K } ] ^ { \top } \in \mathbb { R } ^ { K }$ as a probability vector consisting of $K - 1$ many 0s and exactly one 1. For example, for $K = 3 ,$ , a valid z would be $z = [ z _ { 1 } , z _ { 2 } , z _ { 3 } ] ^ { \top } = [ 0 , 1 , 0 ] ^ { \top }$ , which would select the second mixture component since $z _ { 2 } = 1$ 

Remark. Sometimes this kind of probability distribution is called “multinoulli”, a generalization of the Bernoulli distribution to more than two values (Murphy, 2012). ◇ 

The properties of z imply that $\textstyle \sum _ { k = 1 } ^ { K } z _ { k } = 1$ . Therefore, $_ z$ is a one-hot encoding (also: 1-of-K representation). 

Thus far, we assumed that the indicator variables $z _ { k }$ are known. However, in practice, this is not the case, and we place a prior distribution 

$$
p (\boldsymbol {z}) = \boldsymbol {\pi} = [ \pi_ {1}, \dots , \pi_ {K} ] ^ {\top}, \quad \sum_ {k = 1} ^ {K} \pi_ {k} = 1,\tag{11.59}
$$

on the latent variable z. Then the kth entry 

$$
\pi_ {k} = p (z _ {k} = 1)\tag{11.60}
$$

Figure 11.11 Graphical model for a GMM with a single data point. 

of this probability vector describes the probability that the kth mixture component generated data point x. 

![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_022.jpg>)


Remark (Sampling from a GMM). The construction of this latent-variable model (see the corresponding graphical model in Figure 11.11) lends itself to a very simple sampling procedure (generative process) to generate data: 

1. Sample $z ^ { ( i ) } \sim p ( z )$ 

2. Sample $\pmb { x } ^ { ( i ) } \sim p ( \pmb { x } | z ^ { ( i ) } = 1 )$ 

In the first step, we select a mixture component i (via the one-hot encoding z) at random according to $p ( z ) = \pi ;$ in the second step we draw a sample from the corresponding mixture component. When we discard the samples of the latent variable so that we are left with the $\pmb { x } ^ { ( i ) }$ , we have valid samples from the GMM. This kind of sampling, where samples of random variables depend on samples from the variable’s parents in the graphical model, is called ancestral sampling. $\diamondsuit$ 

Generally, a probabilistic model is defined by the joint distribution of the data and the latent variables (see Section 8.4). With the prior $p ( z )$ defined in (11.59) and (11.60) and the conditional $p ( { \pmb x } \mid z )$ from (11.58), we obtain all K components of this joint distribution via 

$$
p (\boldsymbol {x}, z _ {k} = 1) = p (\boldsymbol {x} \mid z _ {k} = 1) p (z _ {k} = 1) = \pi_ {k} \mathcal {N} \left(\boldsymbol {x} \mid \boldsymbol {\mu} _ {k}, \boldsymbol {\Sigma} _ {k}\right)\tag{11.61}
$$

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

for $k = 1 , \ldots , K$ , so that 

$$
p (\boldsymbol {x}, \boldsymbol {z}) = \left[ \begin{array}{c} p (\boldsymbol {x}, z _ {1} = 1) \\ \vdots \\ p (\boldsymbol {x}, z _ {K} = 1) \end{array} \right] = \left[ \begin{array}{c} \pi_ {1} \mathcal {N} \big (\boldsymbol {x} \mid \boldsymbol {\mu} _ {1},   \boldsymbol {\Sigma} _ {1} \big) \\ \vdots \\ \pi_ {K} \mathcal {N} \big (\boldsymbol {x} \mid \boldsymbol {\mu} _ {K},   \boldsymbol {\Sigma} _ {K} \big) \end{array} \right],\tag{11.62}
$$

which fully specifies the probabilistic model. 

## 11.4.2 Likelihood

To obtain the likelihood $p ( { \pmb x } | { \pmb \theta } )$ in a latent-variable model, we need to marginalize out the latent variables (see Section 8.4.3). In our case, this can be done by summing out all latent variables from the joint $p ( { \pmb x } , z )$ in (11.62) so that 

$$
p (\boldsymbol {x} \mid \boldsymbol {\theta}) = \sum_ {\boldsymbol {z}} p (\boldsymbol {x} \mid \boldsymbol {\theta}, \boldsymbol {z}) p (\boldsymbol {z} \mid \boldsymbol {\theta}), \quad \boldsymbol {\theta} := \left\{\boldsymbol {\mu} _ {k}, \boldsymbol {\Sigma} _ {k}, \pi_ {k}: k = 1, \dots , K \right\}.\tag{11.63}
$$

We now explicitly condition on the parameters θ of the probabilistic model, which we previously omitted. In (11.63), we sum over all K possible onehot encodings of $z ,$ which is denoted by $\textstyle \sum _ { z }$ . Since there is only a single nonzero single entry in each z there are only $K$ possible configurations/ settings of z. For example, if $K = 3 .$ , then z can have the configurations 

$$
\left[ \begin{array}{c} 1 \\ 0 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 1 \\ 0 \end{array} \right], \left[ \begin{array}{c} 0 \\ 0 \\ 1 \end{array} \right].\tag{11.64}
$$

Summing over all possible configurations of z in (11.63) is equivalent to looking at the nonzero entry of the z-vector and writing 

$$
\begin{array}{c} p (\boldsymbol {x} \mid \boldsymbol {\theta}) = \sum_ {\boldsymbol {z}} p (\boldsymbol {x} \mid \boldsymbol {\theta}, \boldsymbol {z}) p (\boldsymbol {z} \mid \boldsymbol {\theta}) \\ = \sum_ {k = 1} ^ {K} p (\boldsymbol {x} \mid \boldsymbol {\theta}, z _ {k} = 1) p (z _ {k} = 1 \mid \boldsymbol {\theta}) \end{array}\tag{11.65a}
$$

(11.65b) 

so that the desired marginal distribution is given as 

$$
\begin{array}{l} p (\boldsymbol {x} \mid \boldsymbol {\theta}) \stackrel {(1 1. 6 5 b)} {=} \sum_ {k = 1} ^ {K} p (\boldsymbol {x} \mid \boldsymbol {\theta}, z _ {k} = 1) p (z _ {k} = 1 | \boldsymbol {\theta}) \\ = \sum_ {k = 1} ^ {K} \pi_ {k} \mathcal {N} \big (\boldsymbol {x} \mid \boldsymbol {\mu} _ {k}, \boldsymbol {\Sigma} _ {k} \big), \end{array}\tag{11.66a}
$$

(11.66b) 

which we identify as the GMM model from (11.3). Given a dataset $\mathcal { X } ,$ , we immediately obtain the likelihood 

$$
p (\mathcal {X} \mid \boldsymbol {\theta}) = \prod_ {n = 1} ^ {N} p (\boldsymbol {x} _ {n} \mid \boldsymbol {\theta}) \stackrel {(1 1. 6 6 b)} {=} \prod_ {n = 1} ^ {N} \sum_ {k = 1} ^ {K} \pi_ {k} \mathcal {N} \left(\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {k}, \boldsymbol {\Sigma} _ {k}\right),\tag{11.67}
$$

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 


Figure 11.12 Graphical model for a GMM with N data points.


![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_023.jpg>)


which is exactly the GMM likelihood from (11.9). Therefore, the latentvariable model with latent indicators $z _ { k }$ is an equivalent way of thinking about a Gaussian mixture model. 

## 11.4.3 Posterior Distribution

Let us have a brief look at the posterior distribution on the latent variable z. According to Bayes’ theorem, the posterior of the kth component having generated data point x 

$$
p (z _ {k} = 1 \mid \boldsymbol {x}) = \frac {p (z _ {k} = 1) p (\boldsymbol {x} \mid z _ {k} = 1)}{p (\boldsymbol {x})},\tag{11.68}
$$

where the marginal $p ( { \pmb x } )$ is given in (11.66b). This yields the posterior distribution for the kth indicator variable $z _ { k }$ 

$$
p (z _ {k} = 1 \mid \boldsymbol {x}) = \frac {p (z _ {k} = 1) p (\boldsymbol {x} \mid z _ {k} = 1)}{\sum_ {j = 1} ^ {K} p (z _ {j} = 1) p (\boldsymbol {x} \mid z _ {j} = 1)} = \frac {\pi_ {k} \mathcal {N} \big (\boldsymbol {x} \mid \boldsymbol {\mu} _ {k} , \boldsymbol {\Sigma} _ {k} \big)}{\sum_ {j = 1} ^ {K} \pi_ {j} \mathcal {N} \big (\boldsymbol {x} \mid \boldsymbol {\mu} _ {j} , \boldsymbol {\Sigma} _ {j} \big)},\tag{11.69}
$$

which we identify as the responsibility of the kth mixture component for data point x. Note that we omitted the explicit conditioning on the GMM parameters $\pi _ { k } , \mu _ { k } , \Sigma _ { k }$ where $k = 1 , \ldots , K$ 

## 11.4.4 Extension to a Full Dataset

Thus far, we have only discussed the case where the dataset consists only of a single data point x. However, the concepts of the prior and posterior can be directly extended to the case of N data points ${ \mathcal { X } } : = \{ { \pmb x } _ { 1 } , \ldots , { \pmb x } _ { N } \}$ 

In the probabilistic interpretation of the GMM, every data point ${ \bf { x } } _ { n }$ possesses its own latent variable 

$$
\boldsymbol {z} _ {n} = \left[ z _ {n 1}, \dots , z _ {n K} \right] ^ {\top} \in \mathbb {R} ^ {K}.\tag{11.70}
$$

Previously (when we only considered a single data point x), we omitted the index $n ,$ but now this becomes important. 

## 11.4 Latent-Variable Perspective

We share the same prior distribution π across all latent variables $z _ { n } .$ The corresponding graphical model is shown in Figure 11.12, where we use the plate notation. 

The conditional distribution $p ( \pmb { x } _ { 1 } , \dots , \pmb { x } _ { N } | z _ { 1 } , \dots , z _ { N } )$ factorizes over the data points and is given as 

$$
p \left(\boldsymbol {x} _ {1}, \dots , \boldsymbol {x} _ {N} \mid \boldsymbol {z} _ {1}, \dots , \boldsymbol {z} _ {N}\right) = \prod_ {n = 1} ^ {N} p \left(\boldsymbol {x} _ {n} \mid \boldsymbol {z} _ {n}\right).\tag{11.71}
$$

To obtain the posterior distribution $p ( z _ { n k } = 1 | \pmb { x } _ { n } )$ , we follow the same reasoning as in Section 11.4.3 and apply Bayes’ theorem to obtain 

$$
\begin{array}{c} p (z _ {n k} = 1 \mid \boldsymbol {x} _ {n}) = \frac {p (\boldsymbol {x} _ {n} \mid z _ {n k} = 1) p (z _ {n k} = 1)}{\sum_ {j = 1} ^ {K} p (\boldsymbol {x} _ {n} \mid z _ {n j} = 1) p (z _ {n j} = 1)} \\ = \frac {\pi_ {k} \mathcal {N} \big (\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {k} , \boldsymbol {\Sigma} _ {k} \big)}{\sum_ {j = 1} ^ {K} \pi_ {j} \mathcal {N} \big (\boldsymbol {x} _ {n} \mid \boldsymbol {\mu} _ {j} , \boldsymbol {\Sigma} _ {j} \big)} = r _ {n k}. \end{array}\tag{11.72a}
$$

(11.72b) 

This means that $p ( z _ { k } = 1 | \pmb { x } _ { n } )$ is the (posterior) probability that the kth mixture component generated data point ${ \bf { x } } _ { n }$ and corresponds to the responsibility $r _ { n k }$ we introduced in (11.17). Now the responsibilities also have not only an intuitive but also a mathematically justified interpretation as posterior probabilities. 

## 11.4.5 EM Algorithm Revisited

The EM algorithm that we introduced as an iterative scheme for maximum likelihood estimation can be derived in a principled way from the latentvariable perspective. Given a current setting ${ \pmb \theta } ^ { ( t ) }$ of model parameters, the E-step calculates the expected log-likelihood 

$$
Q (\pmb {\theta} | \pmb {\theta} ^ {(t)}) = \mathbb {E} _ {\pmb {z} | \pmb {x}, \pmb {\theta} ^ {(t)}} [ \log p (\pmb {x}, \pmb {z} | \pmb {\theta}) ]\tag{11.73a}
$$

$$
= \int \log p (\pmb {x}, \pmb {z} | \pmb {\theta}) p (\pmb {z} | \pmb {x}, \pmb {\theta} ^ {(t)}) \mathrm{d} \pmb {z},\tag{11.73b}
$$

where the expectation of log $p ( \pmb { x } , z | \pmb { \theta } )$ is taken with respect to the posterior $p ( \boldsymbol { z } | \boldsymbol { x } , \boldsymbol { \theta } ^ { ( t ) } )$ of the latent variables. The M-step selects an updated set of model parameters $\pmb { \theta } ^ { ( t + 1 ) }$ by maximizing (11.73b). 

Although an EM iteration does increase the log-likelihood, there are no guarantees that EM converges to the maximum likelihood solution. It is possible that the EM algorithm converges to a local maximum of the log-likelihood. Different initializations of the parameters θ could be used in multiple EM runs to reduce the risk of ending up in a bad local optimum. We do not go into further details here, but refer to the excellent expositions by Rogers and Girolami (2016) and Bishop (2006). 

## 11.5 Further Reading

The GMM can be considered a generative model in the sense that it is straightforward to generate new data using ancestral sampling (Bishop, 2006). For given GMM parameters $\pi _ { k } , \mu _ { k } , \Sigma _ { k } , k = 1 , \ldots , K$ , we sample an index k from the probability vector $[ \pi _ { 1 } , \ldots , \pi _ { K } ] ^ { \top }$ and then sample a data point $\pmb { x } \sim \mathcal { N } ( \pmb { \mu } _ { k } , \pmb { \Sigma } _ { k } )$ . If we repeat this N times, we obtain a dataset that has been generated by a GMM. Figure 11.1 was generated using this procedure. 

Throughout this chapter, we assumed that the number of components K is known. In practice, this is often not the case. However, we could use nested cross-validation, as discussed in Section 8.6.1, to find good models. 

Gaussian mixture models are closely related to the K-means clustering algorithm. K-means also uses the EM algorithm to assign data points to clusters. If we treat the means in the GMM as cluster centers and ignore the covariances (or set them to I), we arrive at K-means. As also nicely described by MacKay (2003), K-means makes a “hard” assignment of data points to cluster centers $\pmb { \mu } _ { k }$ , whereas a GMM makes a “soft” assignment via the responsibilities. 

We only touched upon the latent-variable perspective of GMMs and the EM algorithm. Note that EM can be used for parameter learning in general latent-variable models, e.g., nonlinear state-space models (Ghahramani and Roweis, 1999; Roweis and Ghahramani, 1999) and for reinforcement learning as discussed by Barber (2012). Therefore, the latent-variable perspective of a GMM is useful to derive the corresponding EM algorithm in a principled way (Bishop, 2006; Barber, 2012; Murphy, 2012). 

We only discussed maximum likelihood estimation (via the EM algorithm) for finding GMM parameters. The standard criticisms of maximum likelihood also apply here: 

As in linear regression, maximum likelihood can suffer from severe overfitting. In the GMM case, this happens when the mean of a mixture component is identical to a data point and the covariance tends to 0. Then, the likelihood approaches infinity. Bishop (2006) and Barber (2012) discuss this issue in detail. 

We only obtain a point estimate of the parameters $\pi _ { k } , \mu _ { k } , \Sigma _ { k }$ for k = $1 , \ldots , K$ , which does not give any indication of uncertainty in the parameter values. A Bayesian approach would place a prior on the parameters, which can be used to obtain a posterior distribution on the parameters. This posterior allows us to compute the model evidence (marginal likelihood), which can be used for model comparison, which gives us a principled way to determine the number of mixture components. Unfortunately, closed-form inference is not possible in this setting because there is no conjugate prior for this model. However, approximations, such as variational inference, can be used to obtain an approximate posterior (Bishop, 2006). 

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

## 11.5 Further Reading

![image](<Images/11_Density_Estimation_with_Gaussian_Mixture_Models_image_024.jpg>)



Figure 11.13 Histogram (orange bars) and kernel density estimation (blue line). The kernel density estimator produces a smooth estimate of the underlying density, whereas the histogram is an unsmoothed count measure of how many data points (black) fall into a single bin.


In this chapter, we discussed mixture models for density estimation. There is a plethora of density estimation techniques available. In practice, we often use histograms and kernel density estimation. 

Histograms provide a nonparametric way to represent continuous densities and have been proposed by Pearson (1895). A histogram is constructed by “binning” the data space and count, how many data points fall into each bin. Then a bar is drawn at the center of each bin, and the height of the bar is proportional to the number of data points within that bin. The bin size is a critical hyperparameter, and a bad choice can lead to overfitting and underfitting. Cross-validation, as discussed in Section 8.2.4, can be used to determine a good bin size. 

Kernel density estimation, independently proposed by Rosenblatt (1956) and Parzen (1962), is a nonparametric way for density estimation. Given N i.i.d. samples, the kernel density estimator represents the underlying distribution as 

$$
p (\boldsymbol {x}) = \frac {1}{N h} \sum_ {n = 1} ^ {N} k \left(\frac {\boldsymbol {x} - \boldsymbol {x} _ {n}}{h}\right),\tag{11.74}
$$

where k is a kernel function, i.e., a nonnegative function that integrates to 1 and $h > 0$ is a smoothing/bandwidth parameter, which plays a similar role as the bin size in histograms. Note that we place a kernel on every single data point ${ \bf { x } } _ { n }$ in the dataset. Commonly used kernel functions are the uniform distribution and the Gaussian distribution. Kernel density estimates are closely related to histograms, but by choosing a suitable kernel, we can guarantee smoothness of the density estimate. Figure 11.13 illustrates the difference between a histogram and a kernel density estimator (with a Gaussian-shaped kernel) for a given dataset of 250 data points. 