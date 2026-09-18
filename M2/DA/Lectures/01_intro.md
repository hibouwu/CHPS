M2 CHPS 

[Data & Apprentissage] Introduction à la science des données et à l’apprentissage 

Nicolas Vayatis 

Introduction du cours 

Data science : information, pipelines, decisions 

• Why ? Information –> Data –> Predictions, decisions, knowledge... 

• How ? Building pipelines from sensors to decisions 

• For whom ? For humans ! with Humans in the loop (or not...) 

## The three pillars of data science

1 Hardware : sensors, computing power, telecommunications, interfaces 

2 Software environments : for design, testing and operations 

3 Mathematical modeling and algorithms : high dimensional statistics, dimension reduction, machine learning, network science, time series, etc. 

## Types of Machine Learning problems

![image](<Images/01_intro/image_001.jpg>)


## Symbolic AI vs. Machine Learning

The Traditional Programming Paradigm 

![image](<Images/01_intro/image_002.jpg>)


Machine Learning 

![image](<Images/01_intro/image_003.jpg>)


## The goal of machine learning

## Finding a function

• Example : Pedestrian detection from video cameras 

![image](<Images/01_intro/image_004.jpg>)


• What is the search space for such a function ? 

## The art of machine learning

## Solving the "bias-variance" trade-of

• Distance between solution provided by a learning method and the optimal solution (function) : sum of Approximation error and Estimation error 

Hypothesis class H 

![image](<Images/01_intro/image_005.jpg>)


• Learning a function amounts to : 

(a) chosing a search space (design process), 

(b) estimating the best function in this space (training process). 

## The three families of ML algorithms

## 1 Local methods : based on grouping and local voting (or averaging)

<sup>•</sup> k-Nearest-Neighbors 

<sup>•</sup> Kernel rules 

<sup>•</sup> Decision trees 

## 2 Global methods : based on functional optimization

<sup>•</sup> Regularized regression (Ridge, LASSO...) 

<sup>•</sup> Support Vector Machines 

<sup>•</sup> Boosting 

<sup>•</sup> Feedforward neural networks 

3 Ensemble methods : based on resampling and aggregation 

<sup>•</sup> Bagging 

<sup>•</sup> Boosting 

<sup>•</sup> Random forests 

• Shallow learning : often relates to Tikhonov’s regularization 

$$
\min _ {h \in \mathcal {H}} \left(\frac {1}{n} \sum_ {i = 1} ^ {n} \ell (h (X _ {i}), Y _ {i}) + \lambda_ {n} \cdot \mathrm{pen} (h, n)\right)
$$

<sup>•</sup> The penalty controls the variance term (Occam’s razzor) 

<sup>•</sup> It may also induce a desired structure of the function (e.g. sparsity). 

• Deep Learning : 

<sup>•</sup> Universal approximators (zero bias) 

<sup>•</sup> No penalty term in the optimization but lots of tricks in the implementation which amount to implicit regularization 

## The various frameworks of Machine Learning

![image](<Images/01_intro/image_006.jpg>)


## Machine Learning in the real world A full pipeline for data processing

• data collection and indexing 

• modeling, 

• preprocessing (data quality, filtering and information compression) 

• training, 

• evaluation, 

• monitoring, 

• capitalization 

• learning-to-learn 

• Data points are vectors in $\mathbb { R } ^ { d }$ 

• Setup : supervised, some unsupervised 

• Problems : classification, (scoring), regression, dimension reduction, clustering 

Focus on : a) problem setup, b) performance assessment, c) algorithms, d) principles and best-practice 

Supervised Machine Learning 

Learning and information 

The bias-variance trade-of 

Empirical Risk Minimization 

Supervised Machine Learning Learning and information 

## Learning like the twenty-question game

• Assume Nature has picked one function among K and we want to reveal this function 

• Assume we have an oracle answering YES or NO when we ask a question about this function 

• What is the optimal number n of questions to ask to find the unknown function ? 

## Brute force learning Finite case

• ISSUE : How many questions with answers YES or NO one has to ask the oracle to find THE function among K functions ? 

• STRATEGY : Proceed recursively by splitting the set of functions in two groups and asking whether THE function is the first group and removing the group which does not contain the function. This leads to the identification of the desired function with about log K questions. 

• ANSWER : Number of questions $n = \left\lceil { \frac { \log K } { \log 2 } } \right\rceil = \lceil \log _ { 2 } K \rceil$ 

• NB : this quantity represents the number of bits of information characterizing the function in the set of K functions 

## Shannon’s Information theory The origin of the log $\boldsymbol { K }$

• Number of bits to encode a collection of K functions where each function can occur with probability $P ( k )$ 

![image](<Images/01_intro/image_007.jpg>)


• Entropy of a distribution $P$ in information theory : 

$$
H (P) = - \sum_ {k = 1} ^ {K} P (k) \log_ {2} P (k) \leq \log_ {2} K
$$

## From questions to data

a. Exhaustive search in the zero-error case 

b. PAC learning in the zero-error case 

c. PAC learning in the general case 

PAC = Probably Approximately Correct 

L. Valiant (1984). A theory of the learnable. Communications of the ACM. 

From questions to data 

a. Zero error case (1/2) 

• Notations : Domain space X and label space $\mathcal { V } = \{ 0 , 1 \}$ 

• Zero-error setup : Consider a finite set of indicator functions 

$$
f _ {k}: \mathcal {X} \to \{0, 1 \}, \quad k = 1, \dots , K
$$

and a collection of data points $\left( x _ { i } , y _ { i } \right)$ such that there always exists some k for which $y _ { i } = f _ { k } ( x _ { i } )$ , for any index i 

• Worst case scenario : the collection of data points $x _ { i } \in { \mathcal { X } }$ is such that the cardinality of the set of vectors $\{ ( f _ { 1 } ( x _ { i } ) , \ldots , f _ { K } ( x _ { i } ) ) : i \geq 1 \}$ is maximal and equal to $2 ^ { K }$ 

• ISSUE : How many examples $( x _ { i } , y _ { i } ) \in \mathcal { X } \times \{ 0 , 1 \}$ to find the unknown indicator function among K possible indicator functions $f _ { k } : \mathcal { X } \to \{ 0 , 1 \} , k = 1 , \ldots , K \ ?$ 

• SAME ANSWER : Number of examples $n = \left\lceil { \frac { \log K } { \log 2 } } \right\rceil$ 

STRATEGY : One has to find a vector $x _ { j }$ such that half of the functions take value 1 and the other half take value 0 and ask the oracle whether the desired function takes value 1 or 0 on this vector and discard those functions taking the opposite value. Apply this n times. 

## From questions to data b. PAC in the zero-error case

• REMARK : it may be hard to find such an $x _ { j }$ which splits every subset of functions into two equal parts. 

• SAMPLING : Assume $X _ { 1 } , \ldots , X _ { n }$ is an IID sample 

• QUESTION : In the zero-error setup, how many examples $( X _ { i } , Y _ { i } )$ are required to find among a finite collection of indicator functions $f : \mathcal { X }  \{ 0 , 1 \}$ the one whose error probability is ε-close to zero with probability $1 - \delta ?$ 

• ANSWER : Number of examples 

$$
n = \left\lceil \frac {\log K + \log (1 / \delta)}{\varepsilon} \right\rceil
$$

(Proof left as an exercise) 

• ASSUME : among K functions, NONE of them commits zero error on the sample $\{ ( X _ { i } , Y _ { i } ) : i \geq 1 \}$ 

• SAME ISSUE AS BEFORE 

• ANSWER : Number of examples on average 

$$
n = \left\lceil \frac {\log K + \log (1 / \delta)}{2 \varepsilon^ {2}} \right\rceil
$$

Same dependency on K, the only change is in the constant. 

## PAC bound - General case Sketch of proof

• Hoefding’s inequality : 

<sup>•</sup> Consider $Z _ { 1 } , \ldots , Z _ { n }$ IID over [0, 1] and $\overline { { Z } } _ { n } = \frac { 1 } { n } \sum _ { i = 1 } ^ { n } Z _ { i }$ 

<sup>•</sup> We have, for any $t > 0$ 

$$
\mathbb {P} \{\overline {{Z}} _ {n} - \mathbb {E} (Z _ {1}) > \varepsilon \} \leq \exp (- 2 n \varepsilon^ {2})
$$

• Union bound : For any two measurable sets A, B, we have : 

$$
\mathbb {P} \{A \cup B \} \leq \mathbb {P} \{A \} + \mathbb {P} \{B \}
$$

• Proof arguments for PAC learnability (finite case) 

• PAC : From finite to infinite collection of functions 

• From "strategies" to "learning algorithms" 

• What is lost through random sampling ? the sample may not contain the optimal set of "questions".... 

Supervised Machine Learning The bias-variance decomposition in Machine Learning 

## General setup Notations

• Goal of learning : an optimal decision function $h ^ { * } : \mathcal { X } \to \mathcal { Y }$ $\mathcal { X }$ : domain set, Y : label set 

• Input of learning : 

<sup>•</sup> Training data : a set of labeled data 

$$
D _ {n} = \{(X _ {1}, Y _ {1}), \dots , (X _ {n}, Y _ {n}) \}
$$

of size n, where the $( X , Y ) ^ { \prime }$ s are in $\mathcal { X } \times \mathcal { V }$ 

<sup>•</sup> Hypothesis space : a collection $\mathcal { H }$ of candidate decision functions $h : \mathcal { X }  \mathcal { Y }$ 

• Output of learning : an empirical decision function $\widehat { h }$ in the hypothesis space $\mathcal { H }$ estimated from training data $D _ { n }$ 

• Reference in $\mathcal { H }$ : the best decision function $\bar { h }$ in the class (the more data, the closer $\widehat { h }$ to $\hat { h } )$ 

## The key trade-of in Machine Learning

• Denote by $L ( h )$ the error measure for any decision function h 

• We have : $L ( \bar { h } ) = \operatorname* { i n f } _ { \mathcal { H } } L$ , and $L ( h ^ { * } ) = \mathsf { i n f } L$ 

• Bias-Variance type decomposition of error for any output $\widehat { h }$ : 

$$
L (\widehat {h}) - L (h ^ {*}) = \underbrace {L (\widehat {h}) - L (\bar {h})} _ {\text { estimation   (stochastic)}} + \underbrace {L (\bar {h}) - L (h ^ {*})} _ {\text { approximation   (deterministic)}}
$$

Hypothesis class H 

![image](<Images/01_intro/image_008.jpg>)


## About approximation error

• Cybenko (1989) - Denseness result in the spirit of Stone-Weierstrass showing that any linear combination of compositions of sigmoid with linear functions is dense wrt the supremum norm in the space of continuous functions over the d-dimensional unit cube. 

• Barron (1994) - Approximation error bound involves a parameter quantifying the smoothness of the target function. 

• Status of this question in the regression setup : 

<sup>•</sup> For kernel machines : a full theory is available thanks to Smale (2003), Steinwart (2008). 

<sup>•</sup> For deep learning : recent work by Grohs, Perekrestenko, Elbrächter, and Bölcskei (2019) . 

<sup>•</sup> In the classification setup, tough problem, still open issue... 

What all students (should) know The bias-variance trade-of in statistical inference 

## The case of parametric estimation

$\Theta$ is a parameter set, subset of $\mathbb { R } ^ { p }$ 

$P _ { \theta }$ with $\theta \in \Theta$ is a parametric class of distributions 

$P _ { \theta ^ { * } }$ is the true distribution of the data for some $\theta ^ { \ast } \in \Theta$ (assumption) 

$\widehat { \theta } _ { n }$ is an estimator of $\theta ^ { * }$ based on a sample of size n 

• Mean-squared error decomposition : 

$$
\begin{array}{r l} & {\mathbb {E} \left(\| \widehat {\theta} _ {n} - \theta^ {*} \| ^ {2}\right) =} \\ & {\qquad \mathbb {E} \left(\left((\widehat {\theta} _ {n} - \mathbb {E} (\widehat {\theta} _ {n})) (\widehat {\theta} _ {n} - \mathbb {E} (\widehat {\theta} _ {n})) ^ {T}\right)\right) + \| \mathbb {E} (\widehat {\theta} _ {n}) - \theta^ {*} \| ^ {2}} \end{array}
$$

## The case of prediction error in ML

• Observations : scalar Y, d-dimensional covariate vectors X 

• Regression model : $Y = h ^ { \ast } ( X ) + \varepsilon$ 

• Random noise : ε independent of X 

• Sample-based predictor $\widehat { h } _ { n }$ 

• Mean-squared error at a fixed point $\left( x , y \right)$ 

$$
\mathbb {E} _ {n} \left((y - \widehat {h} _ {n} (x)) ^ {2}\right) = \left(\mathbb {E} _ {n} (\widehat {h} _ {n} (x)) - h ^ {*} (x)\right) ^ {2} + \mathbb {V} _ {n} \left(\widehat {h} _ {n} (x)\right) + \varepsilon^ {2}
$$

$( \mathbb { E } _ { n } , \mathbb { V } _ { n }$ : expectation and variance wrt training sample) 

MSE = Squared-bias term + Variance of predictions + Bayes error 

## The case of linear models

• True model : $h ^ { \ast } ( x ) = x ^ { T } \theta ^ { \ast }$ ,for some $\theta ^ { * } \in \mathbb { R } ^ { d }$ 

• Linear models : $h ( x ) = x ^ { T } \theta$ , where $\boldsymbol { \theta } \in \mathbb { R } ^ { d }$ 

• Matrix/vector notations : $\mathsf { X } \in \mathbb { R } ^ { n \times d } , \mathsf { Y } \in \mathbb { R } ^ { d } , \varepsilon \in \mathbb { R } ^ { n }$ 

• Assumption : X is of full rank 

• MLE : $\widehat { \theta } _ { n } ^ { \mathrm { M L E } } = ( \mathsf { X } ^ { T } \mathsf { X } ) ^ { - 1 } \mathsf { X } ^ { T } \mathsf { Y }$ 

• Plugin predictor : $\widehat { h } _ { n } ( x ) = x ^ { T } \widehat { \theta } _ { n } ^ { \mathrm { M L E } }$ 

• Computations : for fixed (x, y) 

<sup>•</sup> Bias term : $x ^ { T } \mathbb { E } _ { n } ( \widehat { \theta } _ { n } ^ { \mathrm { M L E } } - \theta ^ { * } ) = 0$ 

<sup>•</sup> Variance term : $\mathbb { E } _ { n } \left( ( x ^ { T } ( \mathsf { X } ^ { T } \mathsf { X } ) ^ { - 1 } \mathsf { X } ^ { T } \varepsilon ) ^ { 2 } \right)$ 

What theory says : By Gauss-Markov theorem, MLE is the lowest variance unbiased estimator... but not necessarily the one with minimal MSE. 

• Assumption : $\varepsilon \sim \mathcal { N } _ { n } ( 0 , \sigma ^ { 2 } I _ { n } )$ n-dimensional multivariate gaussian 

• Variance term : for any x 

$$
\begin{array}{r l} \mathbb {E} _ {y | x} \mathbb {V} _ {n} (x ^ {T} \widehat {\theta} _ {n}) & = \mathbb {E} _ {y | x} \mathbb {E} _ {n} ((x ^ {T} (\mathsf {X} ^ {T} \mathsf {X}) ^ {- 1} \mathsf {X} ^ {T} \boldsymbol {\varepsilon}) ^ {2}) \\ & = x ^ {T} \mathbb {E} _ {n} ((\mathsf {X} ^ {T} \mathsf {X}) ^ {- 1} \mathsf {X} ^ {T} \mathbb {E} _ {y | x} (\boldsymbol {\varepsilon} \boldsymbol {\varepsilon} ^ {T}) \mathsf {X} ((\mathsf {X} ^ {T} \mathsf {X}) ^ {- 1}) ^ {T} x) \\ & = \sigma^ {2} x ^ {T} \mathbb {E} _ {n} ((\mathsf {X} ^ {T} \mathsf {X}) ^ {- 1}) x \end{array}
$$

• Assumption : random design $x , x _ { i } \sim \mathcal { N } ( 0 , 1 )$ IID 

• ExE<sub>y|x</sub>Vn x<sup>T</sup> θbn = σ<sup>2</sup> · <sup>d</sup> 

General argument relies on Cochran’s theorem (gaussian case). 

## Explanation of the $d / n$ term

Property on the norm of projections of gaussian random vectors : 

• Assume $\textsf { Z }$ is a gaussian random vector $ { \mathcal { N } } _ { n } ( 0 , I _ { n } )$ in $\mathbb { R } ^ { n }$ , $\mathcal { H }$ is a linear subspace of $\mathbb { R } ^ { n }$ and $\Pi : \mathbb { R } ^ { n }  \mathbb { R } ^ { n }$ a linear projection onto $\mathcal { H }$ 

• Then : the random vector $\Pi _ { \mathcal { H } } Z$ has gaussian distribution $\mathcal { N } _ { n } ( 0 , \Pi )$ on $\mathbb { R } ^ { n }$ (linear transformation of a gaussian is a gaussian) 

• Furthermore : $\| \Pi Z \| ^ { 2 }$ follows a chi-square distribution with 

$$
\mathbb {E} (\| \Pi Z \| ^ {2}) = \dim (\mathcal {H})
$$

## From gaussian linear regression to ML

• What if d larger than n ? 

• What replaces the dimension d in nonlinear models ? 

• Other tasks than regression ? 

Supervised Machine Learning Empirical Risk Minimization (ERM) 

• Loss function : $\ell : \mathcal { V } \times \mathcal { V }  [ 0 , + \infty ]$ 

• Empirical risk of a decision rule h : this is a data-dependent functional 

$$
\widehat {L} _ {n} (h) = \frac {1}{n} \sum_ {i = 1} ^ {n} \ell (h (X _ {i}), Y _ {i})
$$

• ERM = Empirical Risk Minimization 

Learning from training data amounts to solving the following optimization problem 

$$
\widehat {h} _ {n} = \underset {h \in \mathcal {H}} {\arg \min} \widehat {L} _ {n} (h)
$$

where the minimization is restricted to the hypothesis space. 

1 The question of consistency : convergence of $\widehat { h } _ { n }$ wrt the sample size n ? 

2 What is the cost incurred for using training data instead of the actual data ? 

3 What is the nature of the trade-of to calibrate the complexity of the hypothesis space H ? 

![image](<Images/01_intro/image_009.jpg>)


![image](<Images/01_intro/image_010.jpg>)


![image](<Images/01_intro/image_011.jpg>)


Less is more : 

• It turns out that considering all measurable functions leads to overfitting $\Rightarrow \mathcal { H }$ has to be a restricted class ! 

But greed is good : 

• Algorithms which have the capacity to overfit means they have high representation power (arbitrary small approximation error) 

## The notion of true error

• Assumption : 

$( X , Y )$ is a pair of random variables with joint distribution P 

• True error of a decision rule h : this is a distribution-dependent functional 

$$
L (h) = \mathbb {E} (\ell (h (X), Y)) = \int \ell (h (x), y) d P (x, y)
$$

## Examples of tasks/problems

• Binary classification problem : Y takes 0-1 values 

$$
\ell (y, y ^ {\prime}) = \mathbb {I} \{y \neq y ^ {\prime} \} \quad \text { and } \quad L (h) = \mathbb {P} \left\{h (X) \neq Y \right\}
$$

• Regression : Y takes values in R 

$$
\ell (y, y ^ {\prime}) = \left(y - y ^ {\prime}\right) ^ {2} \quad \text { and } \quad L (h) = \mathbb {E} \big ((Y - h (X)) ^ {2} \big)
$$

## Optimal elements, consistency and bounds

• Bayes rule $h ^ { * }$ and Bayes error $L ^ { * }$ 

$$
h ^ {*} = \underset {h} {\arg \min} L (h) \quad \text { and } \quad L ^ {*} = L (h ^ {*})
$$

• (Strong) Consistency of an inference principle $\widehat { h } _ { n }$ 

$$
L (\widehat {h} _ {n}) \to L ^ {*}
$$

almost surely 

• The nonasymptotic bounds Eldorado : 

$$
L (\widehat {h} _ {n}) - L ^ {*} \leq U (n, \mathcal {H}) \quad \text { whp }
$$

Find optimal elements $h ^ { * }$ and $L ^ { * }$ in these two cases : 

• Binary classification problem : Y takes 0-1 values 

$$
\ell (y, y ^ {\prime}) = \mathbb {I} \{y \neq y ^ {\prime} \} \quad \text { and } \quad L (h) = \mathbb {P} \left\{h (X) \neq Y \right\}
$$

• Regression : Y takes values in $\mathbb { R }$ 

$$
\ell (y, y ^ {\prime}) = \left(y - y ^ {\prime}\right) ^ {2} \quad \text { and } \quad L (h) = \mathbb {E} \big ((Y - h (X)) ^ {2} \big)
$$

We shall use the notations $\eta ( x ) = \mathbb { E } ( Y \mid X = x )$ and use the fact that $\mathbb { E } ( Y ) = \mathbb { E } \big ( \mathbb { E } ( Y \mid X ) \big )$ 

## Estimation vs. approximation error Extension of bias-variance decomposition

• Proof idea : Add and retrieve $\widehat { L } ( \widehat { h } _ { n } ) \ , \ \widehat { L } ( \overline { { h } } ) , \ L ( \overline { { h } } )$ , then use the definition of ERM to upper bound the sum. Difference between $L$ and $\widehat { L }$ appear twice. 

• We have : 

$$
L (\widehat {h} _ {n}) - L ^ {*} \leq \underbrace {2 \sup _ {h \in \mathcal {H}} | L (h) - \widehat {L} _ {n} (h) |} _ {\text { estimation   (stochastic)}} + \underbrace {L (\overline {{h}}) - L ^ {*}} _ {\text { approximation   (deterministic)}}
$$

• Assume that the hypothesis class $\mathcal { H }$ of decision functions is finite and $h ^ { \ast } \notin \mathcal { H }$ 

• Then, we have, for any $\delta ,$ , with probability at least $1 - \delta$ 

$$
\forall h \in \mathcal {H}, L (h) \leq \widehat {L} _ {n} (h) + \sqrt {\frac {\log | \mathcal {H} | + \log \left(\frac {1}{\delta}\right)}{2 n}}
$$

<sup>•</sup> log $| \mathcal { H } | = \log K $ Statement in the introduction, see ! 

## Finite hypothesis class Sketch of proof

• Hoefding’s inequality : 

<sup>•</sup> Consider $Z _ { 1 } , \ldots , Z _ { n }$ IID over [0, 1] and $\overline { { Z } } _ { n } = \frac { 1 } { n } \sum _ { i = 1 } ^ { n } Z _ { i }$ 

<sup>•</sup> We have, for any $t > 0$ 

$$
\mathbb {P} \{\overline {{Z}} _ {n} - \mathbb {E} (Z _ {1}) > \varepsilon \} \leq \exp (- 2 n \varepsilon^ {2})
$$

• Union bound : For any two measurable sets A, B, we have : 

$$
\mathbb {P} \{A \cup B \} \leq \mathbb {P} \{A \} + \mathbb {P} \{B \}
$$

• Supervised Machine Learning 

<sup>•</sup> Linear models for supervised learning (2 sessions) 

<sup>•</sup> From linear to for nonlinear models (2 sessions) 

• Unupervised Machine Learning 

<sup>•</sup> Dimension reduction and clustering (1 session) 