![image](<Images/06_Probability_and_Distributions_image_001.jpg>)


# Probability and Distributions

Probability, loosely speaking, concerns the study of uncertainty. Probability can be thought of as the fraction of times an event occurs, or as a degree of belief about an event. We then would like to use this probability to measure the chance of something occurring in an experiment. As mentioned in Chapter 1, we often quantify uncertainty in the data, uncertainty in the machine learning model, and uncertainty in the predictions produced by the model. Quantifying uncertainty requires the idea of a random variable, which is a function that maps outcomes of random experiments to a set of properties that we are interested in. Associated with the random variable is a function that measures the probability that a particular outcome (or set of outcomes) will occur; this is called the probability distribution. 

Probability distributions are used as a building block for other concepts, such as probabilistic modeling (Section 8.4), graphical models (Section 8.5), and model selection (Section 8.6). In the next section, we present the three concepts that define a probability space (the sample space, the events, and the probability of an event) and how they are related to a fourth concept called the random variable. The presentation is deliberately slightly hand wavy since a rigorous presentation may occlude the intuition behind the concepts. An outline of the concepts presented in this chapter are shown in Figure 6.1. 

## 6.1 Construction of a Probability Space

The theory of probability aims at defining a mathematical structure to describe random outcomes of experiments. For example, when tossing a single coin, we cannot determine the outcome, but by doing a large number of coin tosses, we can observe a regularity in the average outcome. Using this mathematical structure of probability, the goal is to perform automated reasoning, and in this sense, probability generalizes logical reasoning (Jaynes, 2003). 

## 6.1.1 Philosophical Issues

When constructing automated reasoning systems, classical Boolean logic does not allow us to express certain forms of plausible reasoning. Consider 

## 172

![image](<Images/06_Probability_and_Distributions_image_002.jpg>)



Figure 6.1 A mind map of the concepts related to random variables and probability distributions, as described in this chapter.


the following scenario: We observe that A is false. We find B becomes less plausible, although no conclusion can be drawn from classical logic. We observe that B is true. It seems A becomes more plausible. We use this form of reasoning daily. We are waiting for a friend, and consider three possibilities: H1, she is on time; H2, she has been delayed by traffic; and H3, she has been abducted by aliens. When we observe our friend is late, we must logically rule out H1. We also tend to consider H2 to be more likely, though we are not logically required to do so. Finally, we may consider H3 to be possible, but we continue to consider it quite unlikely. How do we conclude H2 is the most plausible answer? Seen in this way, probability theory can be considered a generalization of Boolean logic. In the context of machine learning, it is often applied in this way to formalize the design of automated reasoning systems. Further arguments about how probability theory is the foundation of reasoning systems can be found in Pearl (1988). 

The philosophical basis of probability and how it should be somehow related to what we think should be true (in the logical sense) was studied by Cox (Jaynes, 2003). Another way to think about it is that if we are precise about our common sense we end up constructing probabilities. E. T. Jaynes (1922–1998) identified three mathematical criteria, which must apply to all plausibilities: 

1. The degrees of plausibility are represented by real numbers. 

2. These numbers must be based on the rules of common sense. 

“For plausible reasoning it is necessary to extend the discrete true and false values of truth to continuous plausibilities” (Jaynes, 2003). 

3. The resulting reasoning must be consistent, with the three following meanings of the word “consistent”: 

(a) Consistency or non-contradiction: When the same result can be reached through different means, the same plausibility value must be found in all cases. 

(b) Honesty: All available data must be taken into account. 

(c) Reproducibility: If our state of knowledge about two problems are the same, then we must assign the same degree of plausibility to both of them. 

The Cox–Jaynes theorem proves these plausibilities to be sufficient to define the universal mathematical rules that apply to plausibility p, up to transformation by an arbitrary monotonic function. Crucially, these rules are the rules of probability. 

Remark. In machine learning and statistics, there are two major interpretations of probability: the Bayesian and frequentist interpretations (Bishop, 2006; Efron and Hastie, 2016). The Bayesian interpretation uses probability to specify the degree of uncertainty that the user has about an event. It is sometimes referred to as “subjective probability” or “degree of belief”. The frequentist interpretation considers the relative frequencies of events of interest to the total number of events that occurred. The probability of an event is defined as the relative frequency of the event in the limit when one has infinite data. ◇ 

Some machine learning texts on probabilistic models use lazy notation and jargon, which is confusing. This text is no exception. Multiple distinct concepts are all referred to as “probability distribution”, and the reader has to often disentangle the meaning from the context. One trick to help make sense of probability distributions is to check whether we are trying to model something categorical (a discrete random variable) or something continuous (a continuous random variable). The kinds of questions we tackle in machine learning are closely related to whether we are considering categorical or continuous models. 

## 6.1.2 Probability and Random Variables

There are three distinct ideas that are often confused when discussing probabilities. First is the idea of a probability space, which allows us to quantify the idea of a probability. However, we mostly do not work directly with this basic probability space. Instead, we work with random variables (the second idea), which transfers the probability to a more convenient (often numerical) space. The third idea is the idea of a distribution or law associated with a random variable. We will introduce the first two ideas in this section and expand on the third idea in Section 6.2. 

Modern probability is based on a set of axioms proposed by Kolmogorov 

## 6.1 Construction of a Probability Space

(Grinstead and Snell, 1997; Jaynes, 2003) that introduce the three concepts of sample space, event space, and probability measure. The probability space models a real-world process (referred to as an experiment) with random outcomes. 

## The sample space Ω

The sample space is the set of all possible outcomes of the experiment, usually denoted by Ω. For example, two successive coin tosses have a sample space of hh, tt, ht, th , where “h” denotes “heads” and “t” denotes “tails”. 

## The event space

The event space is the space of potential results of the experiment. A subset A of the sample space Ω is in the event space if at the end of the experiment we can observe whether a particular outcome $\omega \in \Omega$ is in A. The event space is obtained by considering the collection of subsets of Ω, and for discrete probability distributions (Section 6.2.1) is often the power set of Ω. 

## The probability P

With each event $A \in { \mathcal { A } }$ , we associate a number $P ( A )$ that measures the probability or degree of belief that the event will occur. P(A) is called the probability of A. 

The probability of a single event must lie in the interval [0, 1], and the total probability over all outcomes in the sample space Ω must be 1, i.e., $P ( \Omega ) = 1$ . Given a probability space $( \Omega , A , P )$ , we want to use it to model some real-world phenomenon. In machine learning, we often avoid explicitly referring to the probability space, but instead refer to probabilities on quantities of interest, which we denote by . In this book, we refer to $\tau$ as the target space and refer to elements of $\tau$ as states. We introduce a function $\dot { X } : \bar { \Omega } \stackrel { \bar { } } {  } \mathcal { T }$ that takes an element of Ω (an outcome) and returns a particular quantity of interest x, a value in . This association/mapping from Ω to is called a random variable. For example, in the case of tossing two coins and counting the number of heads, a random variable X maps to the three possible outcomes: $X ( \mathrm { h h } ) = 2 , X ( \mathrm { h t } ) = 1 , X ( \mathrm { t h } ) = 1$ , and $X ( \mathrm { t t } ) = 0$ . In this particular case, $\mathcal { T } = \{ 0 , 1 , 2 \}$ , and it is the probabilities on elements of that we are interested in. For a finite sample space Ω and finite , the function corresponding to a random variable is essentially a lookup table. For any subset $S \subseteq \tau$ , we associate $P _ { X } ( S ) \in [ 0 , 1 ]$ (the probability) to a particular event occurring corresponding to the random variable X. Example 6.1 provides a concrete illustration of the terminology. 

Remark. The aforementioned sample space Ω unfortunately is referred to by different names in different books. Another common name for Ω is “state space” (Jacod and Protter, 2004), but state space is sometimes reserved for referring to states in a dynamical system (Hasselblatt and 

Katok, 2003). Other names sometimes used to describe Ω are: “sample description space”, “possibility space,” and “event space”. 

## Example 6.1

We assume that the reader is already familiar with computing probabilities of intersections and unions of sets of events. A gentler introduction to probability with many examples can be found in chapter 2 of Walpole et al. (2011). 

Consider a statistical experiment where we model a funfair game consisting of drawing two coins from a bag (with replacement). There are coins from USA (denoted as $) and UK (denoted as £) in the bag, and since we draw two coins from the bag, there are four outcomes in total. The state space or sample space Ω of this experiment is then ($, $), ($, £), (£, $), (£, £). Let us assume that the composition of the bag of coins is such that a draw returns at random a $ with probability 0.3. 

The event we are interested in is the total number of times the repeated draw returns $. Let us define a random variable X that maps the sample space Ω to , which denotes the number of times we draw $ out of the bag. We can see from the preceding sample space we can get zero $, one $, or two $s, and therefore $\bar { \mathcal { T } } = \{ 0 , 1 , 2 \}$ . The random variable X (a function or lookup table) can be represented as a table like the following: 

$$
X ((\mathbb {S}, \mathbb {S})) = 2\tag{6.1}
$$

$$
X ((\mathbb {S}, \mathcal {L})) = 1\tag{6.2}
$$

$$
X ((£, \mathbb {S})) = 1\tag{6.3}
$$

$$
X ((£, £)) = 0.\tag{6.4}
$$

Since we return the first coin we draw before drawing the second, this implies that the two draws are independent of each other, which we will discuss in Section 6.4.5. Note that there are two experimental outcomes, which map to the same event, where only one of the draws returns $. Therefore, the probability mass function (Section 6.2.1) of X is given by 

$$
\begin{array}{r l} P (X = 2) & = P ((,)) \\ & = P () \cdot P () \\ & = 0. 3 \cdot 0. 3 = 0. 0 9 \end{array}\tag{6.5}
$$

$$
\begin{array}{r l} P (X = 1) & = P ((, £) \cup (£,)) \\ & = P ((, £)) + P ((£,)) \\ & = 0. 3 \cdot (1 - 0. 3) + (1 - 0. 3) \cdot 0. 3 = 0. 4 2 \end{array}\tag{6.6}
$$

$$
\begin{array}{r l} P (X = 0) & = P ((£, £)) \\ & = P (£) \cdot P (£) \\ & = (1 - 0. 3) \cdot (1 - 0. 3) = 0. 4 9. \end{array}\tag{6.7}
$$

## 6.1 Construction of a Probability Space

In the calculation, we equated two different concepts, the probability of the output of X and the probability of the samples in Ω. For example, in (6.7) we say $P ( X = 0 ) = P ( ( \mathcal { L } , \mathcal { L } ) )$ . Consider the random variable $X : \Omega  \mathcal { T }$ and a subset $S \subseteq \tau$ (for example, a single element of $\tau _ { \ast }$ such as the outcome that one head is obtained when tossing two coins). Let $X ^ { - 1 } ( S )$ be the pre-image of S by X, i.e., the set of elements of Ω that map to S under $X ; \{ \omega \in \Omega : X ( \omega ) \in S \}$ . One way to understand the transformation of probability from events in Ω via the random variable X is to associate it with the probability of the pre-image of S (Jacod and Protter, 2004). For $S \subseteq { \mathcal { T } }$ , we have the notation 

$$
P _ {X} (S) = P (X \in S) = P (X ^ {- 1} (S)) = P (\{\omega \in \Omega : X (\omega) \in S \}).\tag{6.8}
$$

The left-hand side of (6.8) is the probability of the set of possible outcomes $( \boldsymbol { \mathrm { e . g . } }$ , number of $\$ 12$ that we are interested in. Via the random variable $X ,$ , which maps states to outcomes, we see in the right-hand side of (6.8) that this is the probability of the set of states (in Ω) that have the property $( \boldsymbol { \mathrm { e } } . \boldsymbol { \mathrm { g } } . , \boldsymbol { \Phi } \mathscr { L } , \mathscr { L } \boldsymbol { \Phi } )$ . We say that a random variable X is distributed according to a particular probability distribution $P _ { X }$ , which defines the probability mapping between the event and the probability of the outcome of the random variable. In other words, the function $P _ { X }$ or equivalently $P \circ X ^ { - 1 }$ is the law or distribution of random variable X. 

Remark. The target space, that is, the range of the random variable X, is used to indicate the kind of probability space, i.e., a random variable. When $\tau$ is finite or countably infinite, this is called a discrete random variable (Section 6.2.1). For continuous random variables (Section 6.2.2), we only consider $\mathcal { T } = \mathbb { R }$ or $\mathcal { T } = \mathbb { R } ^ { D }$ 

## 6.1.3 Statistics

Probability theory and statistics are often presented together, but they concern different aspects of uncertainty. One way of contrasting them is by the kinds of problems that are considered. Using probability, we can consider a model of some process, where the underlying uncertainty is captured by random variables, and we use the rules of probability to derive what happens. In statistics, we observe that something has happened and try to figure out the underlying process that explains the observations. In this sense, machine learning is close to statistics in its goals to construct a model that adequately represents the process that generated the data. We can use the rules of probability to obtain a “best-fitting” model for some data. 

Another aspect of machine learning systems is that we are interested in generalization error (see Chapter 8). This means that we are actually interested in the performance of our system on instances that we will observe in future, which are not identical to the instances that we have seen so far. This analysis of future performance relies on probability and statistics, most of which is beyond what will be presented in this chapter. The interested reader is encouraged to look at the books by Boucheron et al. (2013) and Shalev-Shwartz and Ben-David (2014). We will see more about statistics in Chapter 8. 

## 6.2 Discrete and Continuous Probabilities

Let us focus our attention on ways to describe the probability of an event as introduced in Section 6.1. Depending on whether the target space is discrete or continuous, the natural way to refer to distributions is different. When the target space $\tau$ is discrete, we can specify the probability that a random variable X takes a particular value $x \in \tau$ , denoted as $P ( X = x )$ The expression $P ( X = x )$ for a discrete random variable X is known as the probability massfunction. When the target space $\tau$ is continuous, e.g., the real line R, it is more natural to specify the probability that a random variable X is in an interval, denoted by $P ( a \leqslant X \leqslant b )$ for $a < b .$ . By convention, we specify the probability that a random variable X is less than a particular value $x ,$ denoted by $P ( X \leqslant x )$ . The expression $P ( X \leqslant x )$ for a continuous random variable X is known as the cumulative distribution function. We will discuss continuous random variables in Section 6.2.2. We will revisit the nomenclature and contrast discrete and continuous random variables in Section 6.2.3. 

Remark. We will use the phrase univariate distribution to refer to distributions of a single random variable (whose states are denoted by non-bold x). We will refer to distributions of more than one random variable as multivariate distributions, and will usually consider a vector of random variables (whose states are denoted by bold x). ◇ 

## 6.2.1 Discrete Probabilities

When the target space is discrete, we can imagine the probability distribution of multiple random variables as filling out a (multidimensional) array of numbers. Figure 6.2 shows an example. The target space of the joint probability is the Cartesian product of the target spaces of each of the random variables. We define the joint probability as the entry of both values jointly 

$$
P (X = x _ {i}, Y = y _ {j}) = \frac {n _ {i j}}{N},\tag{6.9}
$$

where $n _ { i j }$ is the number of events with state $x _ { i }$ and $y _ { j }$ and N the total number of events. The joint probability is the probability of the intersection of both events, that is, $P ( X = x _ { i } , Y = y _ { j } ) = P ( X = x _ { i } \cap Y = y _ { j } )$ Figure 6.2 illustrates the probability massfunction (pmf) of a discrete probability distribution. For two random variables $X$ and $Y _ { i }$ , the probability that $X = x$ and $Y = y$ is (lazily) written as $p ( x , y )$ and is called the joint probability. One can think of a probability as a function that takes state x and $y$ and returns a real number, which is the reason we write $p ( x , y )$ The marginal probability that X takes the value x irrespective of the value of random variable $Y$ is (lazily) written as $p ( x )$ . We write $X \sim p ( x )$ to denote that the random variable X is distributed according to $p ( x )$ . If we consider only the instances where $X = x ,$ , then the fraction of instances (the conditional probability) for which $Y = y$ is written (lazily) as $p ( y \mid x )$ 

![image](<Images/06_Probability_and_Distributions_image_003.jpg>)



Figure 6.2 Visualization of a discrete bivariate probability mass function, with random variables X and Y. This diagram is adapted from Bishop (2006).


## Example 6.2

Consider two random variables X and $Y ,$ , where X has five possible states and $Y$ has three possible states, as shown in Figure 6.2. We denote by $n _ { i j }$ the number of events with state $X ~ = ~ x _ { i }$ and $Y ~ = ~ y _ { j }$ , and denote by $N$ the total number of events. The value $c _ { i }$ is the sum of the individual frequencies for the ith column, that is, $\begin{array} { r } { c _ { i } = \sum _ { j = 1 } ^ { 3 } n _ { i j } } \end{array}$ . Similarly, the value $r _ { j }$ is the row sum, that is, $\textstyle r _ { j } = \sum _ { i = 1 } ^ { 5 } n _ { i j }$ . Using these definitions, we can compactly express the distribution of X and $Y$ 

The probability distribution of each random variable, the marginal probability, can be seen as the sum over a row or column 

$$
P (X = x _ {i}) = \frac {c _ {i}}{N} = \frac {\sum_ {j = 1} ^ {3} n _ {i j}}{N}\tag{6.10}
$$

and 

$$
P (Y = y _ {j}) = \frac {r _ {j}}{N} = \frac {\sum_ {i = 1} ^ {5} n _ {i j}}{N},\tag{6.11}
$$

where $c _ { i }$ and $r _ { j }$ are the ith column and jth row of the probability table, respectively. By convention, for discrete random variables with a finite number of events, we assume that probabilties sum up to one, that is, 

$$
\sum_ {i = 1} ^ {5} P (X = x _ {i}) = 1 \quad \text { and } \quad \sum_ {j = 1} ^ {3} P (Y = y _ {j}) = 1.\tag{6.12}
$$

The conditional probability is the fraction of a row or column in a par-



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



ticular cell. For example, the conditional probability of Y given X is 

$$
P (Y = y _ {j} \mid X = x _ {i}) = \frac {n _ {i j}}{c _ {i}},\tag{6.13}
$$

and the conditional probability of X given Y is 

$$
P (X = x _ {i} \mid Y = y _ {j}) = \frac {n _ {i j}}{r _ {j}}.\tag{6.14}
$$

In machine learning, we use discrete probability distributions to model categorical variables, i.e., variables that take a finite set of unordered values. They could be categorical features, such as the degree taken at university when used for predicting the salary of a person, or categorical labels, such as letters of the alphabet when doing handwriting recognition. Discrete distributions are also often used to construct probabilistic models that combine a finite number of continuous distributions (Chapter 11). 

## 6.2.2 Continuous Probabilities

We consider real-valued random variables in this section, i.e., we consider target spaces that are intervals of the real line R. In this book, we pretend that we can perform operations on real random variables as if we have discrete probability spaces with finite states. However, this simplification is not precise for two situations: when we repeat something infinitely often, and when we want to draw a point from an interval. The first situation arises when we discuss generalization errors in machine learning (Chapter 8). The second situation arises when we want to discuss continuous distributions, such as the Gaussian (Section 6.5). For our purposes, the lack of precision allows for a briefer introduction to probability. 

Remark. In continuous spaces, there are two additional technicalities, which are counterintuitive. First, the set of all subsets (used to define the event space in Section 6.1) is not well behaved enough. needs to be restricted to behave well under set complements, set intersections, and set unions. Second, the size of a set (which in discrete spaces can be obtained by counting the elements) turns out to be tricky. The size of a set is called its measure. For example, the cardinality of discrete sets, the length of an interval in R, and the volume of a region in $\mathbb { R } ^ { d }$ are all measures. Sets that behave well under set operations and additionally have a topology are called a Borel σ-algebra. Betancourt details a careful construction of probability spaces from set theory without being bogged down in technicalities; see https://tinyurl.com/yb3t6mfd. For a more precise construction, we refer to Billingsley (1995) and Jacod and Protter (2004). 

In this book, we consider real-valued random variables with their corresponding Borel σ-algebra. We consider random variables with values in $\mathbb { R } ^ { \bar { D } }$ to be a vector of real-valued random variables. 

Definition 6.1 (Probability Density Function). A function $f : \mathbb { R } ^ { D } $ R is called a probability density function (pdf ) if 

1. $\forall \pmb { x } \in \mathbb { R } ^ { D } : f ( \pmb { x } ) \geqslant 0$ 

2. Its integral exists and 

$$
\int_ {\mathbb {R} ^ {D}} f (\boldsymbol {x}) \mathrm{d} \boldsymbol {x} = 1.\tag{6.15}
$$

For probability mass functions (pmf) of discrete random variables, the integral in (6.15) is replaced with a sum (6.12). 

Observe that the probability density function is any function f that is non-negative and integrates to one. We associate a random variable X with this function f by 

$$
P (a \leqslant X \leqslant b) = \int_ {a} ^ {b} f (x) \mathrm{d} x,\tag{6.16}
$$

where a, $b \in \mathbb { R }$ and $x \in \mathbb { R }$ are outcomes of the continuous random variable X. States x $\in \mathbb { R } ^ { D }$ are defined analogously by considering a vector of $x \in \mathbb { R }$ . This association (6.16) is called the law or distribution of the random variable X. 

Remark. In contrast to discrete random variables, the probability of a continuous random variable X taking a particular value $P ( X = x )$ is zero. This is like trying to specify an interval in (6.16) where $a = b .$ ◇ 

Definition 6.2 (Cumulative Distribution Function). A cumulative distribution function (cdf) of a multivariate real-valued random variable X with states $\pmb { x } \in \mathbb { R } ^ { D }$ is given by 

$$
F _ {X} (\boldsymbol {x}) = P (X _ {1} \leqslant x _ {1}, \dots , X _ {D} \leqslant x _ {D}),\tag{6.17}
$$

where $X = [ X _ { 1 } , \ldots , X _ { D } ] ^ { \top } , \pmb { x } = [ x _ { 1 } , \ldots , x _ { D } ] ^ { \top } ,$ , and the right-hand side represents the probability that random variable $X _ { i }$ takes the value smaller than or equal to $x _ { i }$ 

The cdf can be expressed also as the integral of the probability density function $f ( { \pmb x } )$ so that 

$$
F _ {X} (\boldsymbol {x}) = \int_ {- \infty} ^ {x _ {1}} \dots \int_ {- \infty} ^ {x _ {D}} f (z _ {1}, \ldots , z _ {D}) \mathrm{d} z _ {1} \dots \mathrm{d} z _ {D}.\tag{6.18}
$$

Remark. We reiterate that there are in fact two distinct concepts when talking about distributions. First is the idea of a pdf (denoted by $f ( x ) )$ , which is a nonnegative function that sums to one. Second is the law of a random variable $X$ , that is, the association of a random variable X with the pdf $f ( x )$ 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



Figure 6.3 Examples of (a) discrete and (b) continuous uniform distributions. See Example 6.3 for details of the distributions. 

The actual values of these states are not meaningful here, and we deliberately chose numbers to drive home the point that we do not want to use (and should ignore) the ordering of the states. 

![image](<Images/06_Probability_and_Distributions_image_004.jpg>)



(a) Discrete distribution


![image](<Images/06_Probability_and_Distributions_image_005.jpg>)



(b) Continuous distribution


For most of this book, we will not use the notation $f ( x )$ and $F _ { X } ( x )$ as we mostly do not need to distinguish between the pdf and cdf. However, we will need to be careful about pdfs and cdfs in Section 6.7. 

## 6.2.3 Contrasting Discrete and Continuous Distributions

Recall from Section 6.1.2 that probabilities are positive and the total probability sums up to one. For discrete random variables (see (6.12)), this implies that the probability of each state must lie in the interval [0, 1]. However, for continuous random variables the normalization (see (6.15)) does not imply that the value of the density is less than or equal to 1 for all values. We illustrate this in Figure 6.3 using the uniform distribution for both discrete and continuous random variables. 

## Example 6.3

We consider two examples of the uniform distribution, where each state is equally likely to occur. This example illustrates some differences between discrete and continuous probability distributions. 

Let Z be a discrete uniform random variable with three states $\{ z =$ $- 1 . 1 , z = 0 . 3 , z = 1 . 5 \}$ . The probability mass function can be represented as a table of probability values: 

$$
\begin{array}{c c c c} & z & - 1. 1 & 0. 3 & 1. 5 \\ P (Z = z) \framebox {\frac {1}{3}} & \framebox {\frac {1}{3}} & \framebox {\frac {1}{3}} \end{array}
$$

Alternatively, we can think of this as a graph (Figure 6.3(a)), where we use the fact that the states can be located on the x-axis, and the y-axis represents the probability of a particular state. The y-axis in Figure 6.3(a) is deliberately extended so that is it the same as in Figure 6.3(b). 

Let X be a continuous random variable taking values in the range 0.9 ⩽ $X \leqslant 1 . 6 _ { : }$ , as represented by Figure 6.3(b). Observe that the height of the density can be greater than 1. However, it needs to hold that 


6.3 Sum Rule, Product Rule, and Bayes’ Theorem


<table><tr><td>Type</td><td>“Point probability”</td><td>“Interval probability”</td></tr><tr><td>Discrete</td><td><eq>P(X = x)</eq>Probability mass function</td><td>Not applicable</td></tr><tr><td>Continuous</td><td><eq>p(x)</eq>Probability density function</td><td><eq>P(X \leqslant x)</eq>Cumulative distribution function</td></tr></table>

$$
\int_ {0. 9} ^ {1. 6} p (x) \mathrm{d} x = 1.\tag{6.19}
$$

Remark. There is an additional subtlety with regards to discrete probability distributions. The states $z _ { 1 } , \ldots , z _ { d }$ do not in principle have any structure, i.e., there is usually no way to compare them, for example $z _ { 1 } = \mathrm { r e d } , z _ { 2 } = \mathrm { g r e e n } , z _ { 3 } = \mathrm { b l u e }$ . However, in many machine learning applications discrete states take numerical values, $\mathrm { e . g . , } z _ { 1 } = - 1 . 1 , z _ { 2 } =$ $0 . 3 , z _ { 3 } = 1 . 5$ , where we could say $z _ { 1 } < z _ { 2 } < z _ { 3 }$ . Discrete states that assume numerical values are particularly useful because we often consider expected values (Section 6.4.1) of random variables. 

Unfortunately, machine learning literature uses notation and nomenclature that hides the distinction between the sample space $\Omega ,$ the target space $\tau ,$ and the random variable X. For a value x of the set of possible outcomes of the random variable X, i.e., $x \in \mathcal { T } , p ( x )$ denotes the probability that random variable X has the outcome x. For discrete random variables, this is written as $P ( X = x )$ , which is known as the probability mass function. The pmf is often referred to as the “distribution”. For continuous variables, $p ( x )$ is called the probability density function (often referred to as a density). To muddy things even further, the cumulative distribution function $P ( X \leqslant x )$ is often also referred to as the “distribution”. In this chapter, we will use the notation X to refer to both univariate and multivariate random variables, and denote the states by x and x respectively. We summarize the nomenclature in Table 6.1. 

Remark. We will be using the expression “probability distribution” not only for discrete probability mass functions but also for continuous probability density functions, although this is technically incorrect. In line with most machine learning literature, we also rely on context to distinguish the different uses of the phrase probability distribution. 

## 6.3 Sum Rule, Product Rule, and Bayes’ Theorem

We think of probability theory as an extension to logical reasoning. As we discussed in Section 6.1.1, the rules of probability presented here follow 

Table 6.1 Nomenclature for probability distributions. 

We think of the outcome x as the argument that results in the probability p(x). 

naturally from fulfilling the desiderata (Jaynes, 2003, chapter 2). Probabilistic modeling (Section 8.4) provides a principled foundation for designing machine learning methods. Once we have defined probability distributions (Section 6.2) corresponding to the uncertainties of the data and our problem, it turns out that there are only two fundamental rules, the sum rule and the product rule. 

Recall from (6.9) that $p ( { \pmb x } , { \pmb y } )$ is the joint distribution of the two random variables $\mathbf { \nabla } _ { \mathbf { x } , \mathbf { y } }$ . The distributions $p ( { \pmb x } )$ and $p ( \pmb { y } )$ are the corresponding marginal distributions, and $p ( \pmb { y } \vert \pmb { x } )$ is the conditional distribution of y given x. Given the definitions of the marginal and conditional probability for discrete and continuous random variables in Section 6.2, we can now present the two fundamental rules in probability theory. 

The first rule, the sum rule, states that 

$$
p (\boldsymbol {x}) = \left\{ \begin{array}{l l} \sum_ {\boldsymbol {y} \in \mathcal {Y}} p (\boldsymbol {x}, \boldsymbol {y}) & \text { if } \boldsymbol {y} \text { is   discrete } \\ \int_ {\mathcal {Y}} p (\boldsymbol {x}, \boldsymbol {y}) \mathrm{d} \boldsymbol {y} & \text { if } \boldsymbol {y} \text { is   continuous } \end{array} \right.,\tag{6.20}
$$

where $\mathcal { V }$ are the states of the target space of random variable Y. This means that we sum out (or integrate out) the set of states y of the random variable Y. The sum rule is also known as the marginalization property. The sum rule relates the joint distribution to a marginal distribution. In general, when the joint distribution contains more than two random variables, the sum rule can be applied to any subset of the random variables, resulting in a marginal distribution of potentially more than one random variable. More concretely, if $\pmb { x } = [ x _ { 1 } , \ldots , x _ { D } ] ^ { \top }$ , we obtain the marginal 

$$
p (x _ {i}) = \int p (x _ {1}, \dots , x _ {D}) \mathrm{d} \boldsymbol {x} _ {\backslash i}\tag{6.21}
$$

by repeated application of the sum rule where we integrate/sum out all random variables except $x _ { i } ,$ which is indicated by $\backslash i ,$ , which reads $^ { \mathfrak { s } } \mathrm { a l l }$ except i.” 

Remark. Many of the computational challenges of probabilistic modeling are due to the application of the sum rule. When there are many variables or discrete variables with many states, the sum rule boils down to performing a high-dimensional sum or integral. Performing high-dimensional sums or integrals is generally computationally hard, in the sense that there is no known polynomial-time algorithm to calculate them exactly. ◇ 

The second rule, known as the product rule, relates the joint distribution to the conditional distribution via 

$$
p (\boldsymbol {x}, \boldsymbol {y}) = p (\boldsymbol {y} \mid \boldsymbol {x}) p (\boldsymbol {x}).\tag{6.22}
$$

The product rule can be interpreted as the fact that every joint distribution of two random variables can be factorized (written as a product) 

of two other distributions. The two factors are the marginal distribution of the first random variable $p ( { \pmb x } )$ , and the conditional distribution of the second random variable given the first $p ( \pmb { y } \vert \pmb { x } )$ . Since the ordering of random variables is arbitrary in $p ( { \pmb x } , { \pmb y } )$ , the product rule also implies $p ( { \pmb x } , { \pmb y } ) = p ( { \pmb x } \mid { \pmb y } ) p ( { \pmb y } )$ . To be precise, (6.22) is expressed in terms of the probability mass functions for discrete random variables. For continuous random variables, the product rule is expressed in terms of the probability density functions (Section 6.2.3). 

In machine learning and Bayesian statistics, we are often interested in making inferences of unobserved (latent) random variables given that we have observed other random variables. Let us assume we have some prior knowledge $p ( { \pmb x } )$ about an unobserved random variable $_ { \pmb { x } }$ and some relationship $p ( \pmb { y } \vert \pmb { x } )$ between x and a second random variable $^ { y , }$ which we can observe. If we observe $^ { y , }$ we can use Bayes’ theorem to draw some conclusions about x given the observed values of $\mathbf { \pmb { y } } .$ Bayes’ theorem (also Bayes’ rule or Bayes’ law) 

$$
\underbrace {p (\boldsymbol {x} \mid \boldsymbol {y})} _ {\text { posterior }} = \frac {\overbrace {p (\boldsymbol {y} \mid \boldsymbol {x})} ^ {\text { likelihood   prior }} \overbrace {p (\boldsymbol {x})} ^ {\text { evidence }}}{\underbrace {p (\boldsymbol {y})} _ {\text { evidence }}}\tag{6.23}
$$

is a direct consequence of the product rule in (6.22) since 

$$
p (\boldsymbol {x}, \boldsymbol {y}) = p (\boldsymbol {x} \mid \boldsymbol {y}) p (\boldsymbol {y})\tag{6.24}
$$

and 

$$
p (\pmb {x}, \pmb {y}) = p (\pmb {y} | \pmb {x}) p (\pmb {x})\tag{6.25}
$$

so that 

$$
p (\boldsymbol {x} \mid \boldsymbol {y}) p (\boldsymbol {y}) = p (\boldsymbol {y} \mid \boldsymbol {x}) p (\boldsymbol {x}) \iff p (\boldsymbol {x} \mid \boldsymbol {y}) = \frac {p (\boldsymbol {y} \mid \boldsymbol {x}) p (\boldsymbol {x})}{p (\boldsymbol {y})}.\tag{6.26}
$$

In (6.23), $p ( { \pmb x } )$ is the $p r i o r _ { \mathrm { { i } } }$ , which encapsulates our subjective prior knowledge of the unobserved (latent) variable x before observing any data. We can choose any prior that makes sense to us, but it is critical to ensure that the prior has a nonzero pdf (or pmf) on all plausible x, even if they are very rare. 

The likelihood $p ( \pmb { y } \vert \pmb { x } )$ describes how x and $\textbf {  { y } }$ are related, and in the case of discrete probability distributions, it is the probability of the data y if we were to know the latent variable x. Note that the likelihood is not a distribution in ${ \mathbf { } } ^ { \mathbf { } } \mathbf { { \mathbf { { x } } } } ,$ but only in $\mathbf { \pmb { y } } .$ . We call $p ( \pmb { y } \vert \pmb { x } )$ either the “likelihood of x (given $y ) ^ { \dag }$ or the “probability of $\textbf {  { y } }$ given $\pmb { x } ^ { \prime \prime }$ but never the likelihood of $\textbf {  { y } }$ (MacKay, 2003). 

The posterior $p ( { \pmb x } \mid { \pmb y } )$ is the quantity of interest in Bayesian statistics because it expresses exactly what we are interested in, i.e., what we know about x after having observed $\pmb { y }$ 

The quantity 

$$
p (\boldsymbol {y}) := \int p (\boldsymbol {y} \mid \boldsymbol {x}) p (\boldsymbol {x}) \mathrm{d} \boldsymbol {x} = \mathbb {E} _ {X} [ p (\boldsymbol {y} \mid \boldsymbol {x}) ]\tag{6.27}
$$

is the marginal likelihood/evidence. The right-hand side of (6.27) uses the expectation operator which we define in Section 6.4.1. By definition, the marginal likelihood integrates the numerator of (6.23) with respect to the latent variable x. Therefore, the marginal likelihood is independent of $^ { x , }$ and it ensures that the posterior $p ( { \pmb x } \mid { \pmb y } )$ is normalized. The marginal likelihood can also be interpreted as the expected likelihood where we take the expectation with respect to the prior $p ( { \pmb x } )$ ). Beyond normalization of the posterior, the marginal likelihood also plays an important role in Bayesian model selection, as we will discuss in Section 8.6. Due to the integration in (8.44), the evidence is often hard to compute. 

Bayes’ theorem (6.23) allows us to invert the relationship between x and y given by the likelihood. Therefore, Bayes’ theorem is sometimes called the probabilistic inverse. We will discuss Bayes’ theorem further in Section $8 . 4 .$ 

Remark. In Bayesian statistics, the posterior distribution is the quantity of interest as it encapsulates all available information from the prior and the data. Instead of carrying the posterior around, it is possible to focus on some statistic of the posterior, such as the maximum of the posterior, which we will discuss in Section 8.3. However, focusing on some statistic of the posterior leads to loss of information. If we think in a bigger context, then the posterior can be used within a decision-making system, and having the full posterior can be extremely useful and lead to decisions that are robust to disturbances. For example, in the context of model-based reinforcement learning, Deisenroth et al. (2015) show that using the full posterior distribution of plausible transition functions leads to very fast (data/sample efficient) learning, whereas focusing on the maximum of the posterior leads to consistent failures. Therefore, having the full posterior can be very useful for a downstream task. In Chapter 9, we will continue this discussion in the context of linear regression. 

## 6.4 Summary Statistics and Independence

We are often interested in summarizing sets of random variables and comparing pairs of random variables. A statistic of a random variable is a deterministic function of that random variable. The summary statistics of a distribution provide one useful view of how a random variable behaves, and as the name suggests, provide numbers that summarize and characterize the distribution. We describe the mean and the variance, two wellknown summary statistics. Then we discuss two ways to compare a pair of random variables: first, how to say that two random variables are independent; and second, how to compute an inner product between them. 

## 6.4.1 Means and Covariances

Mean and (co)variance are often useful to describe properties of probability distributions (expected values and spread). We will see in Section 6.6 that there is a useful family of distributions (called the exponential family), where the statistics of the random variable capture all possible information. 

The concept of the expected value is central to machine learning, and the foundational concepts of probability itself can be derived from the expected value (Whittle, 2000). 

Definition 6.3 (Expected Value). The expected value of a function $g : \mathbb { R } $ R of a univariate continuous random variable $X \sim p ( x )$ is given by 

$$
\mathbb {E} _ {X} [ g (x) ] = \int_ {\mathcal {X}} g (x) p (x) \mathrm{d} x.\tag{6.28}
$$

Correspondingly, the expected value of a function $g$ of a discrete random variable $X \sim p ( x )$ is given by 

$$
\mathbb {E} _ {X} [ g (x) ] = \sum_ {x \in \mathcal {X}} g (x) p (x),\tag{6.29}
$$

where is the set of possible outcomes (the target space) of the random variable X. 

In this section, we consider discrete random variables to have numerical outcomes. This can be seen by observing that the function g takes real numbers as inputs. 

Remark. We consider multivariate random variables X as a finite vector of univariate random variables $[ X _ { 1 } , \ldots , X _ { D } ] ^ { \top }$ . For multivariate random variables, we define the expected value element wise 

$$
\mathbb {E} _ {X} [ g (\boldsymbol {x}) ] = \left[ \begin{array}{c} \mathbb {E} _ {X _ {1}} [ g (x _ {1}) ] \\ \vdots \\ \mathbb {E} _ {X _ {D}} [ g (x _ {D}) ] \end{array} \right] \in \mathbb {R} ^ {D},
$$

(6.30) 

where the subscript $\mathbb { E } _ { X _ { d } }$ indicates that we are taking the expected value with respect to the dth element of the vector x. $\diamondsuit$ 

Definition 6.3 defines the meaning of the notation $\mathbb { E } _ { X }$ as the operator indicating that we should take the integral with respect to the probabil ity density (for continuous distributions) or the sum over all states (for discrete distributions). The definition of the mean (Definition 6.4), is a special case of the expected value, obtained by choosing g to be the identity function. 

Definition 6.4 (Mean). The mean of a random variable X with states 

x $\in \mathbb { R } ^ { D }$ is an average and is defined as 

$$
\mathbb {E} _ {X} [ \boldsymbol {x} ] = \left[ \begin{array}{c} \mathbb {E} _ {X _ {1}} [ x _ {1} ] \\ \vdots \\ \mathbb {E} _ {X _ {D}} [ x _ {D} ] \end{array} \right] \in \mathbb {R} ^ {D},\tag{6.31}
$$

where 

$$
\mathbb {E} _ {X _ {d}} [ x _ {d} ] := \left\{ \begin{array}{l l} \int_ {\mathcal {X}} x _ {d} p (x _ {d}) \mathrm{d} x _ {d} & \text { if   X   is   a   continuous   random   variable } \\ \sum_ {x _ {i} \in \mathcal {X}} x _ {i} p (x _ {d} = x _ {i}) & \text { if   X   is   a   discrete   random   variable } \end{array} \right.\tag{6.32}
$$

for $d = 1 , \ldots , D$ , where the subscript d indicates the corresponding dimension of x. The integral and sum are over the states $\mathcal { X }$ of the target space of the random variable X. 

In one dimension, there are two other intuitive notions of “average”, which are the median and the mode. The median is the “middle” value if we sort the values, i.e., 50% of the values are greater than the median and 50% are smaller than the median. This idea can be generalized to continuous values by considering the value where the cdf (Definition 6.2) is 0.5. For distributions, which are asymmetric or have long tails, the median provides an estimate of a typical value that is closer to human intuition than the mean value. Furthermore, the median is more robust to outliers than the mean. The generalization of the median to higher dimensions is non-trivial as there is no obvious way to “sort” in more than one dimension (Hallin et al., 2010; Kong and Mizera, 2012). The mode is the most frequently occurring value. For a discrete random variable, the mode is defined as the value of $x$ having the highest frequency of occurrence. For a continuous random variable, the mode is defined as a peak in the density $p ( { \pmb x } )$ . A particular density $p ( { \pmb x } )$ may have more than one mode, and furthermore there may be a very large number of modes in high-dimensional distributions. Therefore, finding all the modes of a distribution can be computationally challenging. 

## Example 6.4

Consider the two-dimensional distribution illustrated in Figure 6.4: 

$$
p (x) = 0. 4 \mathcal {N} \left(\boldsymbol {x} \mid \left[ \begin{array}{c} 1 0 \\ 2 \end{array} \right], \left[ \begin{array}{c c} 1 & 0 \\ 0 & 1 \end{array} \right]\right) + 0. 6 \mathcal {N} \left(\boldsymbol {x} \mid \left[ \begin{array}{c} 0 \\ 0 \end{array} \right], \left[ \begin{array}{c c} 8. 4 & 2. 0 \\ 2. 0 & 1. 7 \end{array} \right]\right).\tag{6.33}
$$

We will define the Gaussian distribution ${ \mathcal { N } } ( \mu , \sigma ^ { 2 } )$ in Section 6.5. Also shown is its corresponding marginal distribution in each dimension. Observe that the distribution is bimodal (has two modes), but one of the marginal distributions is unimodal (has one mode). The horizontal bimodal univariate distribution illustrates that the mean and median can be different from each other. While it is tempting to define the twodimensional median to be the concatenation of the medians in each dimension, the fact that we cannot define an ordering of two-dimensional points makes it difficult. When we say “cannot define an ordering”, we mean that there is more than one way to define the relation $< s 0$ that 

$$
\left[ \begin{array}{c} 3 \\ 0 \end{array} \right] <   \left[ \begin{array}{c} 2 \\ 3 \end{array} \right].
$$

![image](<Images/06_Probability_and_Distributions_image_006.jpg>)



Figure 6.4 Illustration of the mean, mode, and median for a two-dimensional dataset, as well as its marginal densities.


Remark. The expected value (Definition 6.3) is a linear operator. For example, given a real-valued function $f ( { \pmb x } ) = a g ( { \pmb x } ) + b h ( { \pmb x } )$ where $a , b \in \mathbb { R }$ and $\pmb { x } \in \mathbb { R } ^ { D }$ , we obtain 

$$
\mathbb {E} _ {X} [ f (\boldsymbol {x}) ] = \int f (\boldsymbol {x}) p (\boldsymbol {x}) \mathrm{d} \boldsymbol {x}\tag{6.34a}
$$

$$
= \int [ a g (\pmb {x}) + b h (\pmb {x}) ] p (\pmb {x}) \mathrm{d} \pmb {x}\tag{6.34b}
$$

$$
= a \int g (\boldsymbol {x}) p (\boldsymbol {x}) \mathrm{d} x + b \int h (\boldsymbol {x}) p (\boldsymbol {x}) \mathrm{d} \boldsymbol {x}\tag{6.34c}
$$

$$
= a \mathbb {E} _ {X} [ g (\boldsymbol {x}) ] + b \mathbb {E} _ {X} [ h (\boldsymbol {x}) ].\tag{6.34d}
$$

For two random variables, we may wish to characterize their correspon-

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

dence to each other. The covariance intuitively represents the notion of how dependent random variables are to one another. 

Definition 6.5 (Covariance (Univariate)). The covariance between two univariate random variables $X , Y \in \mathbb { R }$ is given by the expected product of their deviations from their respective means, i.e., 

$$
\operatorname{Cov} _ {X, Y} [ x, y ] := \mathbb {E} _ {X, Y} \bigl [ (x - \mathbb {E} _ {X} [ x ]) (y - \mathbb {E} _ {Y} [ y ]) \bigr ].\tag{6.35}
$$

Remark. When the random variable associated with the expectation or covariance is clear by its arguments, the subscript is often suppressed (for example, $\mathbb { E } _ { X } [ x ]$ is often written as E[x]). ◇ 

By using the linearity of expectations, the expression in Definition 6.5 can be rewritten as the expected value of the product minus the product of the expected values, i.e., 

$$
\operatorname{Cov} [ x, y ] = \mathbb {E} [ x y ] - \mathbb {E} [ x ] \mathbb {E} [ y ].\tag{6.36}
$$

The covariance of a variable with itself Cov[x, x] is called the variance and is denoted by $\mathbb { V } _ { X } [ x ]$ . The square root of the variance is called the standard deviation and is often denoted by $\sigma ( x )$ . The notion of covariance can be generalized to multivariate random variables. 

Definition 6.6 (Covariance (Multivariate)). If we consider two multivariate random variables X and Y with states $\pmb { x } \in \mathbb { R } ^ { D }$ and $\pmb { y } \in \mathbb { R } ^ { E }$ respectively, the covariance between X and Y is defined as 

$$
\operatorname{Cov} [ \boldsymbol {x}, \boldsymbol {y} ] = \mathbb {E} [ \boldsymbol {x} \boldsymbol {y} ^ {\top} ] - \mathbb {E} [ \boldsymbol {x} ] \mathbb {E} [ \boldsymbol {y} ] ^ {\top} = \operatorname{Cov} [ \boldsymbol {y}, \boldsymbol {x} ] ^ {\top} \in \mathbb {R} ^ {D \times E}.\tag{6.37}
$$

Definition 6.6 can be applied with the same multivariate random variable in both arguments, which results in a useful concept that intuitively captures the “spread” of a random variable. For a multivariate random variable, the variance describes the relation between individual dimensions of the random variable. 

Definition 6.7 (Variance). The variance of a random variable X with states $\pmb { x } \in \mathbb { R } ^ { D }$ and a mean vector $\pmb { \mu } \in \mathbb { R } ^ { D }$ is defined as 

$$
\mathbb {V} _ {X} [ \pmb {x} ] = \mathrm{Cov} _ {X} [ \pmb {x}, \pmb {x} ]\tag{6.38a}
$$

$$
= \mathbb {E} _ {X} [ (\pmb {x} - \pmb {\mu}) (\pmb {x} - \pmb {\mu}) ^ {\top} ] = \mathbb {E} _ {X} [ \pmb {x} \pmb {x} ^ {\top} ] - \mathbb {E} _ {X} [ \pmb {x} ] \mathbb {E} _ {X} [ \pmb {x} ] ^ {\top}\tag{6.38b}
$$

$$
= \left[ \begin{array}{c c c c} \operatorname{Cov} [ x _ {1}, x _ {1} ] & \operatorname{Cov} [ x _ {1}, x _ {2} ] & \ldots & \operatorname{Cov} [ x _ {1}, x _ {D} ] \\ \operatorname{Cov} [ x _ {2}, x _ {1} ] & \operatorname{Cov} [ x _ {2}, x _ {2} ] & \ldots & \operatorname{Cov} [ x _ {2}, x _ {D} ] \\ \vdots & \vdots & \ddots & \vdots \\ \operatorname{Cov} [ x _ {D}, x _ {1} ] & \ldots & \ldots & \operatorname{Cov} [ x _ {D}, x _ {D} ] \end{array} \right].\tag{6.38c}
$$

The $D \times D$ matrix in (6.38c) is called the covariance matrix of the multivariate random variable X. The covariance matrix is symmetric and positive semidefinite and tells us something about the spread of the data. On its diagonal, the covariance matrix contains the variances of the marginals 


6.4 Summary Statistics and Independence


![image](<Images/06_Probability_and_Distributions_image_007.jpg>)



(a) x and y are negatively correlated.


![image](<Images/06_Probability_and_Distributions_image_008.jpg>)



(b) x and y are positively correlated.


$$
p (x _ {i}) = \int p (x _ {1}, \dots , x _ {D}) \mathrm{d} x _ {\backslash i},\tag{6.39}
$$

where $^ { \mathfrak { a } } \backslash i ^ { \mathfrak { n } }$ denotes “all variables but $i ^ { \mathfrak { n } } .$ . The off-diagonal entries are the cross-covariance terms $\operatorname { C o v } [ x _ { i } , x _ { j } ]$ for $i , j = 1 , \ldots , D , \ i \neq j$ 

Remark. In this book, we generally assume that covariance matrices are positive definite to enable better intuition. We therefore do not discuss corner cases that result in positive semidefinite (low-rank) covariance matrices. 

When we want to compare the covariances between different pairs of random variables, it turns out that the variance of each random variable affects the value of the covariance. The normalized version of covariance is called the correlation. 

Definition 6.8 (Correlation). The correlation between two random variables $X , Y$ is given by 

$$
\operatorname{corr} [ x, y ] = \frac {\operatorname{Cov} [ x , y ]}{\sqrt {\mathbb {V} [ x ] \mathbb {V} [ y ]}} \in [ - 1, 1 ].\tag{6.40}
$$

The correlation matrix is the covariance matrix of standardized random variables, $x / \sigma ( x )$ . In other words, each random variable is divided by its standard deviation (the square root of the variance) in the correlation matrix. 

The covariance (and correlation) indicate how two random variables are related; see Figure 6.5. Positive correlation corr[x, y] means that when x grows, then $y$ is also expected to grow. Negative correlation means that as x increases, then y decreases. 

## 6.4.2 Empirical Means and Covariances

The definitions in Section 6.4.1 are often also called the population mean and covariance, as it refers to the true statistics for the population. In machine learning, we need to learn from empirical observations of data. Consider a random variable X. There are two conceptual steps to go from population statistics to the realization of empirical statistics. First, we use the fact that we have a finite dataset (of size N) to construct an empirical statistic that is a function of a finite number of identical random variables, $X _ { 1 } , \ldots , X _ { N }$ . Second, we observe the data, that is, we look at the realization $x _ { 1 } , \ldots , x _ { N }$ of each of the random variables and apply the empirical statistic. 

Specifically, for the mean (Definition 6.4), given a particular dataset we can obtain an estimate of the mean, which is called the empirical mean or sample mean. The same holds for the empirical covariance. 

Definition 6.9 (Empirical Mean and Covariance). The empirical mean vector is the arithmetic average of the observations for each variable, and it is defined as 

$$
\bar {\boldsymbol {x}} := \frac {1}{N} \sum_ {n = 1} ^ {N} \boldsymbol {x} _ {n},\tag{6.41}
$$

where ${ \pmb x } _ { n } \in \mathbb { R } ^ { D }$ 

Similar to the empirical mean, the empirical covariance matrix is a $D \times D$ matrix 

$$
\boldsymbol {\Sigma} := \frac {1}{N} \sum_ {n = 1} ^ {N} (\boldsymbol {x} _ {n} - \bar {\boldsymbol {x}}) (\boldsymbol {x} _ {n} - \bar {\boldsymbol {x}}) ^ {\top}.\tag{6.42}
$$

To compute the statistics for a particular dataset, we would use the realizations (observations) $\pmb { x } _ { 1 } , \ldots , \pmb { x } _ { N }$ and use (6.41) and (6.42). Empirical covariance matrices are symmetric, positive semidefinite (see Section 3.2.3). 

## 6.4.3 Three Expressions for the Variance

We now focus on a single random variable X and use the preceding empirical formulas to derive three possible expressions for the variance. The following derivation is the same for the population variance, except that we need to take care of integrals. The standard definition of variance, corresponding to the definition of covariance (Definition 6.5), is the expectation of the squared deviation of a random variable X from its expected value $\mu , \mathrm { i . e . }$ , 

$$
\mathbb {V} _ {X} [ x ] := \mathbb {E} _ {X} [ (x - \mu) ^ {2} ].\tag{6.43}
$$

The expectation in (6.43) and the mean $\mu = \operatorname { \mathbb { E } } _ { X } ( x )$ are computed using (6.32), depending on whether X is a discrete or continuous random variable. The variance as expressed in (6.43) is the mean of a new random variable $Z : = ( X - \mu ) ^ { 2 }$ 

When estimating the variance in (6.43) empirically, we need to resort to a two-pass algorithm: one pass through the data to calculate the mean $\mu$ using (6.41), and then a second pass using this estimate $\hat { \mu }$ calculate the variance. It turns out that we can avoid two passes by rearranging the terms. The formula in (6.43) can be converted to the so-called raw-score formula for variance: 

$$
\mathbb {V} _ {X} [ x ] = \mathbb {E} _ {X} [ x ^ {2} ] - \left(\mathbb {E} _ {X} [ x ]\right) ^ {2}.\tag{6.44}
$$

The expression in (6.44) can be remembered as “the mean of the square minus the square of the mean”. It can be calculated empirically in one pass through data since we can accumulate $x _ { i }$ (to calculate the mean) and $x _ { i } ^ { 2 }$ simultaneously, where $x _ { i }$ is the ith observation. Unfortunately, if implemented in this way, it can be numerically unstable. The raw-score version of the variance can be useful in machine learning, e.g., when deriving the bias–variance decomposition (Bishop, 2006). 

A third way to understand the variance is that it is a sum of pairwise differences between all pairs of observations. Consider a sample $x _ { 1 } , \ldots , x _ { N }$ of realizations of random variable X, and we compute the squared difference between pairs of $x _ { i }$ and $x _ { j }$ . By expanding the square, we can show that the sum of $N ^ { 2 }$ pairwise differences is the empirical variance of the observations: 

$$
\frac {1}{N ^ {2}} \sum_ {i, j = 1} ^ {N} (x _ {i} - x _ {j}) ^ {2} = 2 \left[ \frac {1}{N} \sum_ {i = 1} ^ {N} x _ {i} ^ {2} - \left(\frac {1}{N} \sum_ {i = 1} ^ {N} x _ {i}\right) ^ {2} \right].\tag{6.45}
$$

We see that (6.45) is twice the raw-score expression (6.44). This means that we can express the sum of pairwise distances (of which there are $N ^ { 2 }$ of them) as a sum of deviations from the mean (of which there are N). Geometrically, this means that there is an equivalence between the pairwise distances and the distances from the center of the set of points. From a computational perspective, this means that by computing the mean (N terms in the summation), and then computing the variance (again N terms in the summation), we can obtain an expression (left-hand side of (6.45)) that has $N ^ { 2 }$ terms. 

## 6.4.4 Sums and Transformations of Random Variables

We may want to model a phenomenon that cannot be well explained by textbook distributions (we introduce some in Sections 6.5 and 6.6), and hence may perform simple manipulations of random variables (such as adding two random variables). 

Consider two random variables X, Y with states x, $\pmb { y } \in \mathbb { R } ^ { D }$ . Then: 

$$
\mathbb {E} [ \boldsymbol {x} + \boldsymbol {y} ] = \mathbb {E} [ \boldsymbol {x} ] + \mathbb {E} [ \boldsymbol {y} ]\tag{6.46}
$$

$$
\mathbb {E} [ \boldsymbol {x} - \boldsymbol {y} ] = \mathbb {E} [ \boldsymbol {x} ] - \mathbb {E} [ \boldsymbol {y} ]\tag{6.47}
$$

$$
\mathbb {V} [ \boldsymbol {x} + \boldsymbol {y} ] = \mathbb {V} [ \boldsymbol {x} ] + \mathbb {V} [ \boldsymbol {y} ] + \operatorname{Cov} [ \boldsymbol {x}, \boldsymbol {y} ] + \operatorname{Cov} [ \boldsymbol {y}, \boldsymbol {x} ]\tag{6.48}
$$

$$
\mathbb {V} [ \boldsymbol {x} - \boldsymbol {y} ] = \mathbb {V} [ \boldsymbol {x} ] + \mathbb {V} [ \boldsymbol {y} ] - \operatorname{Cov} [ \boldsymbol {x}, \boldsymbol {y} ] - \operatorname{Cov} [ \boldsymbol {y}, \boldsymbol {x} ].\tag{6.49}
$$



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



Mean and (co)variance exhibit some useful properties when it comes to affine transformation of random variables. Consider a random variable $X$ with mean $\pmb { \mu }$ and covariance matrix $\pmb { \Sigma }$ and a (deterministic) affine transformation $\pmb { y } = \pmb { A x } + \pmb { b }$ of x. Then $\textbf {  { y } }$ is itself a random variable whose mean vector and covariance matrix are given by 

$$
\mathbb {E} _ {Y} [ \boldsymbol {y} ] = \mathbb {E} _ {X} [ \boldsymbol {A} \boldsymbol {x} + \boldsymbol {b} ] = \boldsymbol {A} \mathbb {E} _ {X} [ \boldsymbol {x} ] + \boldsymbol {b} = \boldsymbol {A} \boldsymbol {\mu} + \boldsymbol {b},\tag{6.50}
$$

$$
\mathbb {V} _ {Y} [ \boldsymbol {y} ] = \mathbb {V} _ {X} [ \boldsymbol {A x} + \boldsymbol {b} ] = \mathbb {V} _ {X} [ \boldsymbol {A x} ] = \boldsymbol {A} \mathbb {V} _ {X} [ \boldsymbol {x} ] \boldsymbol {A} ^ {\top} = \boldsymbol {A} \boldsymbol {\Sigma} \boldsymbol {A} ^ {\top},\tag{6.51}
$$

This can be shown directly by using the definition of the mean and covariance. 

respectively. Furthermore, 

$$
\operatorname{Cov} [ \boldsymbol {x}, \boldsymbol {y} ] = \mathbb {E} [ \boldsymbol {x} (\boldsymbol {A x} + \boldsymbol {b}) ^ {\top} ] - \mathbb {E} [ \boldsymbol {x} ] \mathbb {E} [ \boldsymbol {A x} + \boldsymbol {b} ] ^ {\top}
$$

$$
= \mathbb {E} [ \boldsymbol {x} ] \boldsymbol {b} ^ {\top} + \mathbb {E} [ \boldsymbol {x x} ^ {\top} ] \boldsymbol {A} ^ {\top} - \boldsymbol {\mu b} ^ {\top} - \boldsymbol {\mu \mu} ^ {\top} \boldsymbol {A} ^ {\top}\tag{6.52a}
$$

(6.52b) 

$$
= \boldsymbol {\mu} \boldsymbol {b} ^ {\top} - \boldsymbol {\mu} \boldsymbol {b} ^ {\top} + \left(\mathbb {E} [ \boldsymbol {x x} ^ {\top} ] - \boldsymbol {\mu} \boldsymbol {\mu} ^ {\top}\right) \boldsymbol {A} ^ {\top}\tag{6.52c}
$$

$$
\stackrel {(6. 3 8 \mathrm{b})} {=} \boldsymbol {\Sigma} \boldsymbol {A} ^ {\top},\tag{6.52d}
$$

where $\pmb { \Sigma } = \mathbb { E } [ \pmb { x } \pmb { x } ^ { \top } ] - \pmb { \mu } \pmb { \mu } ^ { \top }$ is the covariance of X. 

## 6.4.5 Statistical Independence

Definition 6.10 (Independence). Two random variables $X , Y$ are statistically independent if and only if 

$$
p (\boldsymbol {x}, \boldsymbol {y}) = p (\boldsymbol {x}) p (\boldsymbol {y}).\tag{6.53}
$$

Intuitively, two random variables X and $Y$ are independent if the value of $\textbf {  { y } }$ (once known) does not add any additional information about x (and vice versa). If $X , Y$ are (statistically) independent, then 

<sup>p(y</sup> | <sup>x)</sup> <sup>=</sup> <sup>p(y)</sup> 

$p ( { \pmb x } | { \pmb y } ) = p ( { \pmb x } )$ 

$$
\mathbb {V} _ {X, Y} [ \boldsymbol {x} + \boldsymbol {y} ] = \mathbb {V} _ {X} [ \boldsymbol {x} ] + \mathbb {V} _ {Y} [ \boldsymbol {y} ]
$$

$$
\mathbf {\Phi} \operatorname{Cov} _ {X, Y} [ \boldsymbol {x}, \boldsymbol {y} ] = \mathbf {0}
$$

The last point may not hold in converse, i.e., two random variables can have covariance zero but are not statistically independent. To understand why, recall that covariance measures only linear dependence. Therefore, random variables that are nonlinearly dependent could have covariance zero. 

## Example 6.5

Consider a random variable X with zero mean $( \mathbb { E } _ { X } [ x ] = 0 )$ and also $\mathbb { E } _ { X } [ x ^ { 3 } ] = 0$ . Let $y = x ^ { 2 }$ (hence, $Y$ is dependent on $X )$ and consider the covariance (6.36) between X and Y. But this gives 

$$
\operatorname{Cov} [ x, y ] = \mathbb {E} [ x y ] - \mathbb {E} [ x ] \mathbb {E} [ y ] = \mathbb {E} [ x ^ {3} ] = 0.\tag{6.54}
$$



Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 



In machine learning, we often consider problems that can be modeled as independent and identically distributed $( i . i . d . )$ random variables, $X _ { 1 } , \ldots , X _ { N }$ . For more than two random variables, the word “independent” (Definition 6.10) usually refers to mutually independent random variables, where all subsets are independent (see Pollard (2002, chapter 4) and Jacod and Protter (2004, chapter 3)). The phrase “identically distributed” means that all the random variables are from the same distribution. 

Another concept that is important in machine learning is conditional independence. 

Definition 6.11 (Conditional Independence). Two random variables X and $Y$ are conditionally independent given $Z$ if and only if 

$$
p (\boldsymbol {x}, \boldsymbol {y} \mid \boldsymbol {z}) = p (\boldsymbol {x} \mid \boldsymbol {z}) p (\boldsymbol {y} \mid \boldsymbol {z}) \quad \text { for   all } \quad \boldsymbol {z} \in \mathcal {Z}  ,\tag{6.55}
$$

where $\mathcal { Z }$ is the set of states of random variable Z. We write $X \perp \perp Y \mid Z$ to denote that X is conditionally independent of Y given $Z$ 

Definition 6.11 requires that the relation in (6.55) must hold true for every value of $_ { z . }$ . The interpretation of (6.55) can be understood as “given knowledge about $z ,$ the distribution of x and $\textbf {  { y } }$ factorizes”. Independence can be cast as a special case of conditional independence if we write X $Y \mid \emptyset .$ . By using the product rule of probability (6.22), we can expand the left-hand side of (6.55) to obtain 

$$
p (\boldsymbol {x}, \boldsymbol {y} \mid \boldsymbol {z}) = p (\boldsymbol {x} \mid \boldsymbol {y}, \boldsymbol {z}) p (\boldsymbol {y} \mid \boldsymbol {z}).\tag{6.56}
$$

By comparing the right-hand side of (6.55) with (6.56), we see that $p ( \pmb { y } \vert z )$ appears in both of them so that 

$$
p (\boldsymbol {x} \mid \boldsymbol {y}, \boldsymbol {z}) = p (\boldsymbol {x} \mid \boldsymbol {z}).\tag{6.57}
$$

Equation (6.57) provides an alternative definition of conditional independence, i.e., X $Y \mid Z$ . This alternative presentation provides the interpretation “given that we know $z ,$ , knowledge about $\textbf {  { y } }$ does not change our knowledge of $\scriptstyle { \pmb x } ^ { \prime \prime }$ 

## 6.4.6 Inner Products of Random Variables

Recall the definition of inner products from Section 3.2. We can define an inner product between random variables, which we briefly describe in this section. If we have two uncorrelated random variables $X , Y$ , then 

$$
\mathbb {V} [ x + y ] = \mathbb {V} [ x ] + \mathbb {V} [ y ].\tag{6.58}
$$

Since variances are measured in squared units, this looks very much like the Pythagorean theorem for right triangles $c ^ { 2 } = a ^ { 2 } + b ^ { 2 }$ 

In the following, we see whether we can find a geometric interpretation of the variance relation of uncorrelated random variables in (6.58). 

Figure 6.6 Geometry of random variables. If random variables X and Y are uncorrelated, they are orthogonal vectors in a corresponding vector space, and the Pythagorean theorem applies. 

![image](<Images/06_Probability_and_Distributions_image_009.jpg>)


Random variables can be considered vectors in a vector space, and we can define inner products to obtain geometric properties of random variables (Eaton, 2007). If we define 

$$
\langle X, Y \rangle := \operatorname{Cov} [ x, y ]\tag{6.59}
$$

for zero mean random variables X and $Y ,$ , we obtain an inner product. We see that the covariance is symmetric, positive definite, and linear in either argument. The length of a random variable is 

$$
\| X \| = \sqrt {\operatorname{Cov} [ x , x ]} = \sqrt {\mathbb {V} [ x ]} = \sigma [ x ],\tag{6.60}
$$

i.e., its standard deviation. The “longer” the random variable, the more uncertain it is; and a random variable with length 0 is deterministic. 

If we look at the angle θ between two random variables X, Y, we get 

$$
\cos \theta = \frac {\langle X , Y \rangle}{\| X \| \| Y \|} = \frac {\operatorname{Cov} [ x , y ]}{\sqrt {\mathbb {V} [ x ] \mathbb {V} [ y ]}},\tag{6.61}
$$

which is the correlation (Definition 6.8) between the two random variables. This means that we can think of correlation as the cosine of the angle between two random variables when we consider them geometrically. We know from Definition 3.7 that $X \perp Y \iff \langle X , Y \rangle = 0$ . In our case, this means that X and Y are orthogonal if and only if Cov[x, y] = 0, i.e., they are uncorrelated. Figure 6.6 illustrates this relationship. 

Remark. While it is tempting to use the Euclidean distance (constructed 

![image](<Images/06_Probability_and_Distributions_image_010.jpg>)



Figure 6.7 Gaussian distribution of two random variables x<sub>1</sub> and x<sub>2</sub>.



from the preceding definition of inner products) to compare probability distributions, it is unfortunately not the best way to obtain distances between distributions. Recall that the probability mass (or density) is posi tive and needs to add up to 1. These constraints mean that distributions live on something called a statistical manifold. The study of this space of probability distributions is called information geometry. Computing distances between distributions are often done using Kullback-Leibler divergence, which is a generalization of distances that account for properties of the statistical manifold. Just like the Euclidean distance is a special case of a metric (Section 3.3), the Kullback-Leibler divergence is a special case of two more general classes of divergences called Bregman divergences and f-divergences. The study of divergences is beyond the scope of this book, and we refer for more details to the recent book by Amari (2016), one of the founders of the field of information geometry.


## 6.5 Gaussian Distribution

The Gaussian distribution is the most well-studied probability distribution for continuous-valued random variables. It is also referred to as the normal distribution. Its importance originates from the fact that it has many computationally convenient properties, which we will be discussing in the following. In particular, we will use it to define the likelihood and prior for linear regression (Chapter 9), and consider a mixture of Gaussians for density estimation (Chapter 11). 

There are many other areas of machine learning that also benefit from using a Gaussian distribution, for example Gaussian processes, variational inference, and reinforcement learning. It is also widely used in other application areas such as signal processing $( \boldsymbol { \mathrm { e . g . } }$ , Kalman filter), control $( \boldsymbol { \mathrm { e . g . , } }$ linear quadratic regulator), and statistics $( \boldsymbol { \mathrm { e . g . } }$ , hypothesis testing). 

normal distribution The Gaussian distribution arises naturally when we consider sums of independent and identically distributed random variables. This is known as the central limit theorem (Grinstead and Snell, 1997). 


Figure 6.8 Gaussian distributions overlaid with 100 samples. (a) Onedimensional case; (b) two-dimensional case.


![image](<Images/06_Probability_and_Distributions_image_011.jpg>)



(a) Univariate (one-dimensional) Gaussian; The red cross shows the mean and the red line shows the extent of the variance.


## Probability and Distributions

![image](<Images/06_Probability_and_Distributions_image_012.jpg>)



(b) Multivariate (two-dimensional) Gaussian, viewed from top. The red cross shows the mean and the colored lines show the contour lines of the density.


For a univariate random variable, the Gaussian distribution has a density that is given by 

$$
p (x \mid \mu , \sigma^ {2}) = \frac {1}{\sqrt {2 \pi \sigma^ {2}}} \exp \left(- \frac {(x - \mu) ^ {2}}{2 \sigma^ {2}}\right).\tag{6.62}
$$

The multivariate Gaussian distribution is fully characterized by a mean vector $\pmb { \mu }$ and a covariance matrix Σ and defined as 

$$
p (\boldsymbol {x} \mid \boldsymbol {\mu}, \boldsymbol {\Sigma}) = (2 \pi) ^ {- \frac {D}{2}} | \boldsymbol {\Sigma} | ^ {- \frac {1}{2}} \exp \left(- \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu})\right),\tag{6.63}
$$

where $\pmb { x } \in \mathbb { R } ^ { D }$ . We write $p ( { \pmb x } ) = \mathcal { N } ( { \pmb x } \mid { \pmb \mu } , { \pmb \Sigma } )$ or $X \sim { \mathcal { N } } ( \mu , \Sigma )$ . Figure 6.7 shows a bivariate Gaussian (mesh), with the corresponding contour plot. Figure 6.8 shows a univariate Gaussian and a bivariate Gaussian with corresponding samples. The special case of the Gaussian with zero mean and identity covariance, that is, ${ \pmb \mu } = { \bf 0 }$ and $\Sigma = I ,$ , is referred to as the standard normal distribution. 

Gaussians are widely used in statistical estimation and machine learning as they have closed-form expressions for marginal and conditional distributions. In Chapter 9, we use these closed-form expressions extensively for linear regression. A major advantage of modeling with Gaussian random variables is that variable transformations (Section 6.7) are often not needed. Since the Gaussian distribution is fully specified by its mean and covariance, we often can obtain the transformed distribution by applying the transformation to the mean and covariance of the random variable. 

## 6.5.1 Marginals and Conditionals of Gaussians are Gaussians

In the following, we present marginalization and conditioning in the general case of multivariate random variables. If this is confusing at first reading, the reader is advised to consider two univariate random variables instead. Let X and $Y$ be two multivariate random variables, that may have different dimensions. To consider the effect of applying the sum rule of probability and the effect of conditioning, we explicitly write the Gaussian distribution in terms of the concatenated states $[ { \pmb x } ^ { \top } { \pmb y } ^ { \top } ] ^ { \top }$ so that 

$$
p (\boldsymbol {x}, \boldsymbol {y}) = \mathcal {N} \left(\left[ \begin{array}{c} \boldsymbol {\mu} _ {x} \\ \boldsymbol {\mu} _ {y} \end{array} \right], \left[ \begin{array}{c c} \boldsymbol {\Sigma} _ {x x} & \boldsymbol {\Sigma} _ {x y} \\ \boldsymbol {\Sigma} _ {y x} & \boldsymbol {\Sigma} _ {y y} \end{array} \right]\right)  ,\tag{6.64}
$$

where $\Sigma _ { x x } = \mathrm { C o v } [ { \pmb x } , { \pmb x } ]$ and $\begin{array} { r } { \Sigma _ { y y } = \mathrm { C o v } [ { \pmb y } , { \pmb y } ] } \end{array}$ are the marginal covariance matrices of x and y, respectively, and $\Sigma _ { x y } = \mathrm { C o v } [ { \pmb x } , { \pmb y } ]$ is the crosscovariance matrix between x and y. 

The conditional distribution $p ( { \pmb x } \mid { \pmb y } )$ is also Gaussian (illustrated in Figure 6.9(c)) and given by (derived in Section 2.3 of Bishop, 2006) 

$$
p (\boldsymbol {x} \mid \boldsymbol {y}) = \mathcal {N} \big (\boldsymbol {\mu} _ {x \mid y}, \boldsymbol {\Sigma} _ {x \mid y} \big)\tag{6.65}
$$

$$
\pmb {\mu} _ {x \mid y} = \pmb {\mu} _ {x} + \pmb {\Sigma} _ {x y} \pmb {\Sigma} _ {y y} ^ {- 1} (\pmb {y} - \pmb {\mu} _ {y})\tag{6.66}
$$

$$
\pmb {\Sigma} _ {x \mid y} = \pmb {\Sigma} _ {x x} - \pmb {\Sigma} _ {x y} \pmb {\Sigma} _ {y y} ^ {- 1} \pmb {\Sigma} _ {y x}.\tag{6.67}
$$

Note that in the computation of the mean in (6.66), the y-value is an observation and no longer random. 

Remark. The conditional Gaussian distribution shows up in many places, where we are interested in posterior distributions: 

The Kalman filter (Kalman, 1960), one of the most central algorithms for state estimation in signal processing, does nothing but computing Gaussian conditionals of joint distributions (Deisenroth and Ohlsson, 2011; Sarkk¨ a¨, 2013). 

Gaussian processes (Rasmussen and Williams, 2006), which are a practical implementation of a distribution over functions. In a Gaussian process, we make assumptions of joint Gaussianity of random variables. By (Gaussian) conditioning on observed data, we can determine a posterior distribution over functions. 

Latent linear Gaussian models (Roweis and Ghahramani, 1999; Murphy, 2012), which include probabilistic principal component analysis (PPCA) (Tipping and Bishop, 1999). We will look at PPCA in more detail in Section 10.7. 

The marginal distribution $p ( { \pmb x } )$ of a joint Gaussian distribution $p ( { \pmb x } , { \pmb y } )$ (see (6.64)) is itself Gaussian and computed by applying the sum rule (6.20) and given by 

$$
p (\boldsymbol {x}) = \int p (\boldsymbol {x}, \boldsymbol {y}) \mathrm{d} \boldsymbol {y} = \mathcal {N} \left(\boldsymbol {x} \mid \boldsymbol {\mu} _ {x}, \boldsymbol {\Sigma} _ {x x}\right).\tag{6.68}
$$

The corresponding result holds for $p ( \pmb { y } )$ , which is obtained by marginalizing with respect to x. Intuitively, looking at the joint distribution in (6.64), we ignore (i.e., integrate out) everything we are not interested in. This is illustrated in Figure 6.9(b). 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



## Example 6.6

Figure 6.9 (a) Bivariate Gaussian; (b) marginal of a joint Gaussian distribution is Gaussian; (c) the conditional distribution of a Gaussian is also Gaussian. 

![image](<Images/06_Probability_and_Distributions_image_013.jpg>)



(a) Bivariate Gaussian.


![image](<Images/06_Probability_and_Distributions_image_014.jpg>)



(b) Marginal distribution.


![image](<Images/06_Probability_and_Distributions_image_015.jpg>)



(c) Conditional distribution.



Consider the bivariate Gaussian distribution (illustrated in Figure 6.9):


$$
p (x _ {1}, x _ {2}) = \mathcal {N} \left(\left[ \begin{array}{c} 0 \\ 2 \end{array} \right], \left[ \begin{array}{c c} 0. 3 & - 1 \\ - 1 & 5 \end{array} \right]\right).\tag{6.69}
$$

We can compute the parameters of the univariate Gaussian, conditioned on $x _ { 2 } = - 1$ , by applying (6.66) and (6.67) to obtain the mean and variance respectively. Numerically, this is 

$$
\mu_ {x _ {1} \mid x _ {2} = - 1} = 0 + (- 1) \cdot 0. 2 \cdot (- 1 - 2) = 0. 6\tag{6.70}
$$

and 

$$
\sigma_ {x _ {1} \mid x _ {2} = - 1} ^ {2} = 0. 3 - (- 1) \cdot 0. 2 \cdot (- 1) = 0. 1.\tag{6.71}
$$

Therefore, the conditional Gaussian is given by 

$$
p (x _ {1} \mid x _ {2} = - 1) = \mathcal {N} (0. 6, 0. 1).\tag{6.72}
$$

The marginal distribution $p ( x _ { 1 } )$ , in contrast, can be obtained by applying (6.68), which is essentially using the mean and variance of the random variable $x _ { 1 }$ , giving us 

$$
p (x _ {1}) = \mathcal {N} (0, 0. 3).\tag{6.73}
$$



Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 



## 6.5.2 Product of Gaussian Densities

For linear regression (Chapter 9), we need to compute a Gaussian likelihood. Furthermore, we may wish to assume a Gaussian prior (Section 9.3). We apply Bayes’ Theorem to compute the posterior, which results in a multiplication of the likelihood and the prior, that is, the multiplication of two Gaussian densities. The product of two Gaussians $\mathcal { N } ( \pmb { x } | \pmb { a } , \mathbf { \tilde { A } } ) \mathcal { N } ( \pmb { x } | b , B )$ is a Gaussian distribution scaled by ${ \tt a c } \in \mathbb { R }$ , given by $\displaystyle c \mathcal { N } ( \pmb { x } | \pmb { c } , \pmb { C } )$ with 

$$
\boldsymbol {C} = \left(\boldsymbol {A} ^ {- 1} + \boldsymbol {B} ^ {- 1}\right) ^ {- 1}\tag{6.74}
$$

$$
\boldsymbol {c} = \boldsymbol {C} (\boldsymbol {A} ^ {- 1} \boldsymbol {a} + \boldsymbol {B} ^ {- 1} \boldsymbol {b})\tag{6.75}
$$

$$
c = (2 \pi) ^ {- \frac {D}{2}} | \boldsymbol {A} + \boldsymbol {B} | ^ {- \frac {1}{2}} \exp \left(- \frac {1}{2} (\boldsymbol {a} - \boldsymbol {b}) ^ {\top} (\boldsymbol {A} + \boldsymbol {B}) ^ {- 1} (\boldsymbol {a} - \boldsymbol {b})\right)\tag{6.76}
$$

The scaling constant c itself can be written in the form of a Gaussian density either in a or in b with an “inflated” covariance matrix $\mathbf { A } + \mathbf { B }$ $\mathrm { i . e . , } c = { \mathcal { N } } { \big ( } a \mid b , A + B { \big ) } = { \mathcal { N } } { \big ( } b \mid a , A + B { \big ) }$ 

Remark. For notation convenience, we will sometimes use $\mathcal { N } ( \pmb { x } | \pmb { m } , S )$ to describe the functional form of a Gaussian density even if x is not a random variable. We have just done this in the preceding demonstration when we wrote 

$$
c = \mathcal {N} (\boldsymbol {a} \mid \boldsymbol {b}, \boldsymbol {A} + \boldsymbol {B}) = \mathcal {N} (\boldsymbol {b} \mid \boldsymbol {a}, \boldsymbol {A} + \boldsymbol {B}).\tag{6.77}
$$

Here, neither a nor b are random variables. However, writing c in this way is more compact than (6.76). 

## 6.5.3 Sums and Linear Transformations

If $X , Y$ are independent Gaussian random variables $( \mathrm { i . e . } ,$ , the joint distribution is given as $p ( { \pmb x } , { \pmb y } ) = p ( { \pmb x } ) p ( { \pmb y } ) )$ with $p ( { \pmb x } ) = \mathcal { N } \big ( { \pmb x } \mid { \pmb \mu } _ { x } , { \pmb \Sigma } _ { x } \big )$ and $p ( \pmb { y } ) = \mathcal { N } \big ( \pmb { y } \mid \pmb { \mu } _ { y } , \pmb { \Sigma } _ { y } \big )$ , then ${ \pmb x } + { \pmb y }$ is also Gaussian distributed and given by 

$$
p (\boldsymbol {x} + \boldsymbol {y}) = \mathcal {N} \left(\boldsymbol {\mu} _ {x} + \boldsymbol {\mu} _ {y}, \boldsymbol {\Sigma} _ {x} + \boldsymbol {\Sigma} _ {y}\right).\tag{6.78}
$$

Knowing that $p ( { \pmb x } + { \pmb y } )$ is Gaussian, the mean and covariance matrix can be determined immediately using the results from (6.46) through (6.49). This property will be important when we consider i.i.d. Gaussian noise acting on random variables, as is the case for linear regression (Chapter 9). 

## Example 6.7

Since expectations are linear operations, we can obtain the weighted sum of independent Gaussian random variables 

$$
p (a \boldsymbol {x} + b \boldsymbol {y}) = \mathcal {N} \left(a \boldsymbol {\mu} _ {x} + b \boldsymbol {\mu} _ {y}, a ^ {2} \boldsymbol {\Sigma} _ {x} + b ^ {2} \boldsymbol {\Sigma} _ {y}\right).\tag{6.79}
$$



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



Remark. A case that will be useful in Chapter 11 is the weighted sum of Gaussian densities. This is different from the weighted sum of Gaussian random variables. 

In Theorem 6.12, the random variable x is from a density that is a mixture of two densities $p _ { 1 } ( x )$ and $p _ { 2 } ( x )$ , weighted by α. The theorem can be generalized to the multivariate random variable case, since linearity of expectations holds also for multivariate random variables. However, the idea of a squared random variable needs to be replaced by $\pmb { x } \pmb { x } ^ { \top }$ 

Theorem 6.12. Consider a mixture of two univariate Gaussian densities 

$$
p (x) = \alpha p _ {1} (x) + (1 - \alpha) p _ {2} (x),\tag{6.80}
$$

where the scalar $0 < \alpha < 1$ is the mixture weight, and $p _ { 1 } ( x )$ and $p _ { 2 } ( x )$ are univariate Gaussian densities (Equation (6.62)) with different parameters, i.e., $( \mu _ { 1 } , \sigma _ { 1 } ^ { 2 } ) \neq ( \mu _ { 2 } , \sigma _ { 2 } ^ { 2 } )$ 

Then the mean of the mixture density $p ( x )$ is given by the weighted sum of the means of each random variable: 

$$
\mathbb {E} [ x ] = \alpha \mu_ {1} + (1 - \alpha) \mu_ {2}.\tag{6.81}
$$

The variance of the mixture density $p ( x )$ is given by 

$$
\mathbb {V} [ x ] = \left[ \alpha \sigma_ {1} ^ {2} + (1 - \alpha) \sigma_ {2} ^ {2} \right] + \left(\left[ \alpha \mu_ {1} ^ {2} + (1 - \alpha) \mu_ {2} ^ {2} \right] - \left[ \alpha \mu_ {1} + (1 - \alpha) \mu_ {2} \right] ^ {2}\right)\tag{6.82}
$$

Proof The mean of the mixture density $p ( x )$ is given by the weighted sum of the means of each random variable. We apply the definition of the mean (Definition 6.4), and plug in our mixture (6.80), which yields 

$$
\mathbb {E} [ x ] = \int_ {- \infty} ^ {\infty} x p (x) \mathrm{d} x\tag{6.83a}
$$

$$
= \int_ {- \infty} ^ {\infty} (\alpha x p _ {1} (x) + (1 - \alpha) x p _ {2} (x)) d x\tag{6.83b}
$$

$$
= \alpha \int_ {- \infty} ^ {\infty} x p _ {1} (x) \mathrm{d} x + (1 - \alpha) \int_ {- \infty} ^ {\infty} x p _ {2} (x) \mathrm{d} x\tag{6.83c}
$$

$$
= \alpha \mu_ {1} + (1 - \alpha) \mu_ {2}.\tag{6.83d}
$$

To compute the variance, we can use the raw-score version of the variance from (6.44), which requires an expression of the expectation of the squared random variable. Here we use the definition of an expectation of a function (the square) of a random variable (Definition 6.3), 

$$
\mathbb {E} [ x ^ {2} ] = \int_ {- \infty} ^ {\infty} x ^ {2} p (x) \mathrm{d} x\tag{6.84a}
$$

$$
= \int_ {- \infty} ^ {\infty} \left(\alpha x ^ {2} p _ {1} (x) + (1 - \alpha) x ^ {2} p _ {2} (x)\right) \mathrm{d} x\tag{6.84b}
$$

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

## 6.5 Gaussian Distribution

$$
= \alpha \int_ {- \infty} ^ {\infty} x ^ {2} p _ {1} (x) \mathrm{d} x + (1 - \alpha) \int_ {- \infty} ^ {\infty} x ^ {2} p _ {2} (x) \mathrm{d} x\tag{6.84c}
$$

$$
= \alpha (\mu_ {1} ^ {2} + \sigma_ {1} ^ {2}) + (1 - \alpha) (\mu_ {2} ^ {2} + \sigma_ {2} ^ {2}),\tag{6.84d}
$$

where in the last equality, we again used the raw-score version of the variance (6.44) giving $\sigma ^ { 2 } = \mathbb { E } [ x ^ { 2 } ] - \mu ^ { 2 }$ . This is rearranged such that the expectation of a squared random variable is the sum of the squared mean and the variance. 

Therefore, the variance is given by subtracting (6.83d) from (6.84d), 

$$
\mathbb {V} [ x ] = \mathbb {E} [ x ^ {2} ] - (\mathbb {E} [ x ]) ^ {2}\tag{6.85a}
$$

$$
= \alpha (\mu_ {1} ^ {2} + \sigma_ {1} ^ {2}) + (1 - \alpha) (\mu_ {2} ^ {2} + \sigma_ {2} ^ {2}) - (\alpha \mu_ {1} + (1 - \alpha) \mu_ {2}) ^ {2}\tag{6.85b}
$$

$$
= \left[ \alpha \sigma_ {1} ^ {2} + (1 - \alpha) \sigma_ {2} ^ {2} \right]
$$

$$
+ \left(\left[ \alpha \mu_ {1} ^ {2} + (1 - \alpha) \mu_ {2} ^ {2} \right] - \left[ \alpha \mu_ {1} + (1 - \alpha) \mu_ {2} \right] ^ {2}\right).\tag{6.85c}
$$

Remark. The preceding derivation holds for any density, but since the Gaussian is fully determined by the mean and variance, the mixture density can be determined in closed form. $\diamondsuit$ 

For a mixture density, the individual components can be considered to be conditional distributions (conditioned on the component identity). Equation (6.85c) is an example of the conditional variance formula, also known as the law of total variance, which generally states that for two random variables X and Y it holds that $\mathbb { V } _ { X } [ x ] = \mathbb { E } _ { Y } [ \mathbb { V } _ { X } [ x | y ] ] + \mathbb { V } _ { Y } [ \mathbb { E } _ { X } [ x | y ] ]$ 2 i.e., the (total) variance of X is the expected conditional variance plus the variance of a conditional mean. 

We consider in Example 6.17 a bivariate standard Gaussian random variable X and performed a linear transformation Ax on it. The outcome is a Gaussian random variable with mean zero and covariance $A A ^ { \top }$ . Observe that adding a constant vector will change the mean of the distribution, without affecting its variance, that is, the random variable ${ \pmb x } + { \pmb \mu }$ is Gaussian with mean µ and identity covariance. Hence, any linear/affine transformation of a Gaussian random variable is Gaussian distributed. 

Consider a Gaussian distributed random variable $X \sim { \mathcal { N } } ( \mu , \Sigma )$ . For a given matrix A of appropriate shape, let $Y$ be a random variable such that $y = A x$ is a transformed version of ${ \bf { x } } .$ . We can compute the mean of $\textbf {  { y } }$ by exploiting that the expectation is a linear operator (6.50) as follows: 

$$
\mathbb {E} [ \boldsymbol {y} ] = \mathbb {E} [ \boldsymbol {A x} ] = \boldsymbol {A} \mathbb {E} [ \boldsymbol {x} ] = \boldsymbol {A} \boldsymbol {\mu}.\tag{6.86}
$$

Similarly the variance of $\textbf {  { y } }$ can be found by using (6.51): 

$$
\mathbb {V} [ \boldsymbol {y} ] = \mathbb {V} [ \boldsymbol {A x} ] = \boldsymbol {A V} [ \boldsymbol {x} ] \boldsymbol {A} ^ {\top} = \boldsymbol {A} \boldsymbol {\Sigma} \boldsymbol {A} ^ {\top}.\tag{6.87}
$$

This means that the random variable $\textbf {  { y } }$ is distributed according to 

$$
p (\boldsymbol {y}) = \mathcal {N} \left(\boldsymbol {y} \mid \boldsymbol {A} \boldsymbol {\mu}, \boldsymbol {A} \boldsymbol {\Sigma} \boldsymbol {A} ^ {\top}\right).\tag{6.88}
$$

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

Let us now consider the reverse transformation: when we know that a random variable has a mean that is a linear transformation of another random variable. For a given full rank matrix $\pmb { A } \in \mathbb { R } ^ { M \times N }$ , where $M \geqslant N$ let $\pmb { y } \in \mathbb { R } ^ { M }$ be a Gaussian random variable with mean Ax, i.e., 

$$
p (\boldsymbol {y}) = \mathcal {N} (\boldsymbol {y} \mid A \boldsymbol {x}, \boldsymbol {\Sigma}).\tag{6.89}
$$

What is the corresponding probability distribution $p ( { \pmb x } ) \ b { \ ? }$ If A is invertible, then we can write $x = A ^ { - 1 } y$ and apply the transformation in the previous paragraph. However, in general A is not invertible, and we use an approach similar to that of the pseudo-inverse (3.57). That is, we premultiply both sides with $A ^ { \top }$ and then invert $A ^ { \top } A$ , which is symmetric and positive definite, giving us the relation 

$$
\boldsymbol {y} = \boldsymbol {A} \boldsymbol {x} \iff (\boldsymbol {A} ^ {\top} \boldsymbol {A}) ^ {- 1} \boldsymbol {A} ^ {\top} \boldsymbol {y} = \boldsymbol {x}.\tag{6.90}
$$

Hence, x is a linear transformation of ${ \mathbf { } } ^ { \prime } { \mathbf { } }$ and we obtain 

$$
p (\boldsymbol {x}) = \mathcal {N} \left(\boldsymbol {x} \mid \left(\boldsymbol {A} ^ {\top} \boldsymbol {A}\right) ^ {- 1} \boldsymbol {A} ^ {\top} \boldsymbol {y}, \left(\boldsymbol {A} ^ {\top} \boldsymbol {A}\right) ^ {- 1} \boldsymbol {A} ^ {\top} \boldsymbol {\Sigma} \boldsymbol {A} \left(\boldsymbol {A} ^ {\top} \boldsymbol {A}\right) ^ {- 1}\right).\tag{6.91}
$$

## 6.5.4 Samplingfrom Multivariate Gaussian Distributions

We will not explain the subtleties of random sampling on a computer, and the interested reader is referred to Gentle (2004). In the case of a multivariate Gaussian, this process consists of three stages: first, we need a source of pseudo-random numbers that provide a uniform sample in the interval [0,1]; second, we use a non-linear transformation such as the Box-Muller transform (¨ Devroye, 1986) to obtain a sample from a univariate Gaussian; and third, we collate a vector of these samples to obtain a sample from a multivariate standard normal $\mathcal { N } ( \mathbf { 0 } , \pmb { I } )$ 

For a general multivariate Gaussian, that is, where the mean is non zero and the covariance is not the identity matrix, we use the properties of linear transformations of a Gaussian random variable. Assume we are interested in generating samples $\pmb { x } _ { i } , i = 1 , \ldots , n$ , from a multivariate Gaussian distribution with mean $\pmb { \mu }$ and covariance matrix Σ. We would like to construct the sample from a sampler that provides samples from the multivariate standard normal $\mathcal { N } ( \mathbf { 0 } , \pmb { I } )$ 

To obtain samples from a multivariate normal $\mathcal { N } ( \pmb { \mu } , \pmb { \Sigma } )$ , we can use the properties of a linear transformation of a Gaussian random variable: If $\mathbf { \boldsymbol { x } } \sim \mathcal { N } ( \mathbf { \boldsymbol { 0 } } , I )$ , then ${ \pmb y } = { \pmb A } { \pmb x } + { \pmb \mu } _ { 3 }$ , where $\boldsymbol { A } \boldsymbol { A } ^ { \intercal } = \boldsymbol { \Sigma }$ is Gaussian distributed with mean $\pmb { \mu }$ and covariance matrix Σ. One convenient choice of $\pmb { A }$ is to use the Cholesky decomposition (Section 4.3) of the covariance matrix $\pmb { \Sigma } = \pmb { A } \pmb { A } ^ { \top }$ . The Cholesky decomposition has the benefit that A is triangular, leading to efficient computation. 

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

## 6.6 Conjugacy and the Exponential Family

Many of the probability distributions “with names” that we find in statistics textbooks were discovered to model particular types of phenomena. For example, we have seen the Gaussian distribution in Section 6.5. The distributions are also related to each other in complex ways (Leemis and McQueston, 2008). For a beginner in the field, it can be overwhelming to figure out which distribution to use. In addition, many of these distributions were discovered at a time that statistics and computation were done by pencil and paper. It is natural to ask what are meaningful concepts in the computing age (Efron and Hastie, 2016). In the previous section, we saw that many of the operations required for inference can be conveniently calculated when the distribution is Gaussian. It is worth recalling at this point the desiderata for manipulating probability distributions in the machine learning context: 

1. There is some “closure property” when applying the rules of probability, e.g., Bayes’ theorem. By closure, we mean that applying a particular operation returns an object of the same type. 

2. As we collect more data, we do not need more parameters to describe the distribution. 

3. Since we are interested in learning from data, we want parameter estimation to behave nicely. 

It turns out that the class of distributions called the exponential family provides the right balance of generality while retaining favorable compu tation and inference properties. Before we introduce the exponential fam ily, let us see three more members of “named” probability distributions, the Bernoulli (Example 6.8), Binomial (Example 6.9), and Beta (Exam ple 6.10) distributions. 

## Example 6.8

The Bernoulli distribution is a distribution for a single binary random variable X with state x $\in \{ 0 , 1 \}$ . It is governed by a single continuous parameter $\mu \in [ 0 , 1 ]$ that represents the probability of $X = 1$ . The Bernoulli distribution Ber $( \mu )$ is defined as 

$$
p (x \mid \mu) = \mu^ {x} (1 - \mu) ^ {1 - x}, \quad x \in \{0, 1 \},\tag{6.92}
$$

$$
\mathbb {E} [ x ] = \mu ,\tag{6.93}
$$

$$
\mathbb {V} [ x ] = \mu (1 - \mu),\tag{6.94}
$$

where $\mathbb { E } [ x ]$ and $\mathbb { V } [ x ]$ are the mean and variance of the binary random variable X. 

An example where the Bernoulli distribution can be used is when we are interested in modeling the probability of “heads” when flipping a coin. 

![image](<Images/06_Probability_and_Distributions_image_016.jpg>)


Figure 6.10 Examples of the Binomial distribution for µ ∈ {0.1, 0.4, 0.75} and N = 15. 

![image](<Images/06_Probability_and_Distributions_image_017.jpg>)



Number m of observations $x = 1$ in $N = 1 5$ experiments


Remark. The rewriting above of the Bernoulli distribution, where we use Boolean variables as numerical 0 or 1 and express them in the exponents, is a trick that is often used in machine learning textbooks. Another occurence of this is when expressing the Multinomial distribution. 

## Example 6.9 (Binomial Distribution)

The Binomial distribution is a generalization of the Bernoulli distribution to a distribution over integers (illustrated in Figure 6.10). In particular, the Binomial can be used to describe the probability of observing m occurrences of $X = 1$ in a set of N samples from a Bernoulli distribution where $p ( X = 1 ) \ = \mu \in [ 0 , 1 ]$ . The Binomial distribution Bin $( N , \mu )$ is defined as 

$$
p (m \mid N, \mu) = \binom {N} {m} \mu^ {m} (1 - \mu) ^ {N - m},\tag{6.95}
$$

$$
\mathbb {E} [ m ] = N \mu ,\tag{6.96}
$$

$$
\mathbb {V} [ m ] = N \mu (1 - \mu),\tag{6.97}
$$

where $\mathbb { E } [ m ]$ and $\mathbb { V } [ m ]$ are the mean and variance of $m _ { \ i }$ , respectively. 

An example where the Binomial could be used is if we want to describe the probability of observing m “heads” in N coin-flip experiments if the probability for observing head in a single experiment is $\mu .$ 

## Example 6.10 (Beta Distribution)

We may wish to model a continuous random variable on a finite interval. The Beta distribution is a distribution over a continuous random variable $\mu \in [ 0 , 1 ]$ , which is often used to represent the probability for some binary event (e.g., the parameter governing the Bernoulli distribution). The Beta distribution $\mathtt { B e t a } ( \alpha , \beta )$ (illustrated in Figure 6.11) itself is governed by two parameters $\alpha > 0 , \beta > 0$ and is defined as 

$$
p (\mu \mid \alpha , \beta) = \frac {\Gamma (\alpha + \beta)}{\Gamma (\alpha) \Gamma (\beta)} \mu^ {\alpha - 1} (1 - \mu) ^ {\beta - 1}\tag{6.98}
$$

$$
\mathbb {E} [ \mu ] = \frac {\alpha}{\alpha + \beta}, \qquad \mathbb {V} [ \mu ] = \frac {\alpha \beta}{(\alpha + \beta) ^ {2} (\alpha + \beta + 1)}\tag{6.99}
$$

where $\Gamma ( \cdot )$ is the Gamma function defined as 

$$
\Gamma (t) := \int_ {0} ^ {\infty} x ^ {t - 1} \exp (- x) d x, \qquad t > 0.\tag{6.100}
$$

$$
\Gamma (t + 1) = t \Gamma (t).\tag{6.101}
$$

Note that the fraction of Gamma functions in (6.98) normalizes the Beta distribution. 

![image](<Images/06_Probability_and_Distributions_image_018.jpg>)



Figure 6.11 Examples of the Beta distribution for different values of α and β.


Intuitively, α moves probability mass toward 1, whereas $\beta$ moves prob ability mass toward 0. There are some special cases (Murphy, 2012): 

For $\alpha = 1 = \beta ,$ , we obtain the uniform distribution $\boldsymbol { \mathcal { U } } [ 0 , 1 ]$ 

For $\alpha , \beta < 1$ , we get a bimodal distribution with spikes at 0 and 1. 

For $\alpha , \beta > 1$ , the distribution is unimodal. 

For $\alpha , \beta > 1$ and $\alpha = \beta _ { i }$ , the distribution is unimodal, symmetric, and centered in the interval [0, 1], i.e., the mode/mean is at $\frac { 1 } { 2 }$ . 

Remark. There is a whole zoo of distributions with names, and they are related in different ways to each other (Leemis and McQueston, 2008). It is worth keeping in mind that each named distribution is created for a particular reason, but may have other applications. Knowing the reason behind the creation of a particular distribution often allows insight into how to best use it. We introduced the preceding three distributions to be able to illustrate the concepts of conjugacy (Section 6.6.1) and exponential families (Section 6.6.3). ◇ 

## 6.6.1 Conjugacy

According to Bayes’ theorem (6.23), the posterior is proportional to the product of the prior and the likelihood. The specification of the prior can be tricky for two reasons: First, the prior should encapsulate our knowledge about the problem before we see any data. This is often difficult to describe. Second, it is often not possible to compute the posterior distribution analytically. However, there are some priors that are computationally convenient: conjugate priors. 

Definition 6.13 (Conjugate Prior). A prior is conjugate for the likelihood function if the posterior is of the same form/type as the prior. 

Conjugacy is particularly convenient because we can algebraically calculate our posterior distribution by updating the parameters of the prior distribution. 

Remark. When considering the geometry of probability distributions, conjugate priors retain the same distance structure as the likelihood (Agarwal and Daum´e III, 2010). 

To introduce a concrete example of conjugate priors, we describe in Example 6.11 the Binomial distribution (defined on discrete random variables) and the Beta distribution (defined on continuous random variables). 

## Example 6.11 (Beta-Binomial Conjugacy)

Consider a Binomial random variable $x \sim \mathrm { B i n } ( N , \mu )$ where 

$$
p (x \mid N, \mu) = \binom {N} {x} \mu^ {x} (1 - \mu) ^ {N - x}, \quad x = 0, 1, \ldots , N,\tag{6.102}
$$

is the probability of finding x times the outcome “heads” in $N$ coin flips, where $\mu$ is the probability of a “head”. We place a Beta prior on the parameter $\mu ,$ that is, $\mu \sim$ Beta $( \alpha , \beta )$ , where 

$$
p (\mu \mid \alpha , \beta) = \frac {\Gamma (\alpha + \beta)}{\Gamma (\alpha) \Gamma (\beta)} \mu^ {\alpha - 1} (1 - \mu) ^ {\beta - 1}.\tag{6.103}
$$

If we now observe some outcome $x = h ,$ , that is, we see h heads in $N$ coin flips, we compute the posterior distribution on $\mu$ as 

$$
p (\mu \mid x = h, N, \alpha , \beta) \propto p (x \mid N, \mu) p (\mu \mid \alpha , \beta)\tag{6.104a}
$$

$$
\propto \mu^ {h} (1 - \mu) ^ {(N - h)} \mu^ {\alpha - 1} (1 - \mu) ^ {\beta - 1}\tag{6.104b}
$$

$$
= \mu^ {h + \alpha - 1} (1 - \mu) ^ {(N - h) + \beta - 1}\tag{6.104c}
$$


6.6 Conjugacy and the Exponential Family


<table><tr><td>Likelihood</td><td>Conjugate prior</td><td>Posterior</td></tr><tr><td>Bernoulli</td><td>Beta</td><td>Beta</td></tr><tr><td>Binomial</td><td>Beta</td><td>Beta</td></tr><tr><td>Gaussian</td><td>Gaussian/inverse Gamma</td><td>Gaussian/inverse Gamma</td></tr><tr><td>Gaussian</td><td>Gaussian/inverse Wishart</td><td>Gaussian/inverse Wishart</td></tr><tr><td>Multinomial</td><td>Dirichlet</td><td>Dirichlet</td></tr></table>


Table 6.2 Examples of conjugate priors for common likelihood functions. 


$$
\propto \operatorname{Beta} (h + \alpha , N - h + \beta),\tag{6.104d}
$$

i.e., the posterior distribution is a Beta distribution as the prior, i.e., the Beta prior is conjugate for the parameter $\mu$ in the Binomial likelihood function. 

In the following example, we will derive a result that is similar to the Beta-Binomial conjugacy result. Here we will show that the Beta distribution is a conjugate prior for the Bernoulli distribution. 

## Example 6.12 (Beta-Bernoulli Conjugacy)

Let $x \in \{ 0 , 1 \}$ be distributed according to the Bernoulli distribution with parameter $\theta \in [ 0 , 1 ]$ , that is, $p ( x = 1 | \theta ) = \theta$ . This can also be expressed as $p ( x | \theta ) = \theta ^ { x } \bar { ( 1 - \theta ) } ^ { 1 - x }$ . Let θ be distributed according to a Beta distribution with parameters $\alpha , \beta _ { z }$ , that is, $p ( \theta | \alpha , \beta ) \propto \theta ^ { \alpha - 1 } ( 1 - \theta ) ^ { \beta - 1 }$ 

Multiplying the Beta and the Bernoulli distributions, we get 

$$
p (\theta \mid x, \alpha , \beta) \propto p (x \mid \theta) p (\theta \mid \alpha , \beta)\tag{6.105a}
$$

$$
= \theta^ {x} (1 - \theta) ^ {1 - x} \theta^ {\alpha - 1} (1 - \theta) ^ {\beta - 1}\tag{6.105b}
$$

$$
= \theta^ {\alpha + x - 1} (1 - \theta) ^ {\beta + (1 - x) - 1}\tag{6.105c}
$$

$$
\propto p (\theta \mid \alpha + x, \beta + (1 - x)).\tag{6.105d}
$$

The last line is the Beta distribution with parameters $( \alpha + x , \beta + ( 1 - x ) )$ 

Table 6.2 lists examples for conjugate priors for the parameters of some standard likelihoods used in probabilistic modeling. Distributions such as Multinomial, inverse Gamma, inverse Wishart, and Dirichlet can be found in any statistical text, and are described in Bishop (2006), for example. 

The Beta distribution is the conjugate prior for the parameter $\mu$ in both the Binomial and the Bernoulli likelihood. For a Gaussian likelihood func tion, we can place a conjugate Gaussian prior on the mean. The reason why the Gaussian likelihood appears twice in the table is that we need to distinguish the univariate from the multivariate case. In the univariate (scalar) case, the inverse Gamma is the conjugate prior for the variance. In the multivariate case, we use a conjugate inverse Wishart distribution as a prior on the covariance matrix. The Dirichlet distribution is the conjugate prior for the multinomial likelihood function. For further details, we refer to Bishop (2006). 

## 6.6.2 Sufficient Statistics

Recall that a statistic of a random variable is a deterministic function of that random variable. For example, if $\pmb { x } = [ x _ { 1 } , \ldots , x _ { N } ] ^ { \top }$ is a vector of univariate Gaussian random variables, that is, $x _ { n } \sim \mathcal { N } ( \mu , \sigma ^ { 2 } )$ , then the sample mean $\begin{array} { r } { \hat { \mu } = \frac 1 N ( x _ { 1 } + \dots + x _ { N } ) } \end{array}$ is a statistic. Sir Ronald Fisher discovered the notion of sufficient statistics: the idea that there are statistics that will contain all available information that can be inferred from data corresponding to the distribution under consideration. In other words, sufficient statistics carry all the information needed to make inference about the population, that is, they are the statistics that are sufficient to represent the distribution. 

For a set of distributions parametrized by $\theta ,$ , let X be a random variable with distribution $p ( x \mid \theta _ { 0 } )$ given an unknown $\theta _ { 0 }$ . A vector $\phi ( x )$ of statistics is called sufficient statistics for $\theta _ { 0 }$ if they contain all possible information about $\theta _ { 0 }$ . To be more formal about “contain all possible information”, this means that the probability of x given $\theta$ can be factored into a part that does not depend on $\theta ,$ and a part that depends on $\theta$ only via $\phi ( x )$ The Fisher-Neyman factorization theorem formalizes this notion, which we state in Theorem 6.14 without proof. 

Theorem 6.14 (Fisher-Neyman). [Theorem 6.5 in Lehmann and Casella (1998)] Let X have probability density function $p ( x | \theta )$ . Then the statistics ϕ(x) are sufficientfor θ if and only $i f p ( x | \theta )$ can be written in the form 

$$
p (x \mid \theta) = h (x) g _ {\theta} (\phi (x)),\tag{6.106}
$$

where $h ( x )$ is a distribution independent of θ and $g _ { \theta }$ captures all the dependence on θ via sufficient statistics $\phi ( x )$ . 

If $p ( x \mid \theta )$ does not depend on $\theta ,$ then $\phi ( x )$ is trivially a sufficient statistic for any function $\phi .$ . The more interesting case is that $p ( x \mid \theta )$ is dependent only on $\phi ( x )$ and not $x$ itself. In this case, $\phi ( x )$ is a sufficient statistic for $\theta .$ 

In machine learning, we consider a finite number of samples from a distribution. One could imagine that for simple distributions (such as the Bernoulli in Example 6.8) we only need a small number of samples to estimate the parameters of the distributions. We could also consider the opposite problem: If we have a set of data (a sample from an unknown distribution), which distribution gives the best fit? A natural question to ask is, as we observe more data, do we need more parameters $\theta$ to describe the distribution? It turns out that the answer is yes in general, and this is studied in non-parametric statistics (Wasserman, 2007). A converse question is to consider which class of distributions have finite-dimensional sufficient statistics, that is the number of parameters needed to describe them does not increase arbitrarily. The answer is exponential family distributions, described in the following section. 

## 6.6.3 Exponential Family

There are three possible levels of abstraction we can have when considering distributions (of discrete or continuous random variables). At level one (the most concrete end of the spectrum), we have a particular named distribution with fixed parameters, for example a univariate Gaussian $\mathcal { N } ( 0 , 1 )$ with zero mean and unit variance. In machine learning, we often use the second level of abstraction, that is, we fix the parametric form (the univariate Gaussian) and infer the parameters from data. For example, we assume a univariate Gaussian $\mathcal { N } ( \mu , \sigma ^ { 2 } )$ with unknown mean $\mu$ and unknown variance $\sigma ^ { 2 }$ , and use a maximum likelihood fit to determine the best parameters $( \mu , \sigma ^ { 2 } )$ . We will see an example of this when considering linear regression in Chapter 9. A third level of abstraction is to consider families of distributions, and in this book, we consider the exponential family. The univariate Gaussian is an example of a member of the exponential family. Many of the widely used statistical models, including all the “named” models in Table 6.2, are members of the exponential family. They can all be unified into one concept (Brown, 1986). 

Remark. A brief historical anecdote: Like many concepts in mathematics and science, exponential families were independently discovered at the same time by different researchers. In the years 1935–1936, Edwin Pitman in Tasmania, Georges Darmois in Paris, and Bernard Koopman in New York independently showed that the exponential families are the only families that enjoy finite-dimensional sufficient statistics under repeated independent sampling (Lehmann and Casella, 1998). 

An exponential family is a family of probability distributions, parameterized by $\pmb \theta \in \mathbb { R } ^ { D }$ , of the form 

$$
p (\boldsymbol {x} \mid \boldsymbol {\theta}) = h (\boldsymbol {x}) \exp \left(\langle \boldsymbol {\theta}, \phi (\boldsymbol {x}) \rangle - A (\boldsymbol {\theta})\right),\tag{6.107}
$$

where $\phi ( { \pmb x } )$ is the vector of sufficient statistics. In general, any inner product (Section 3.2) can be used in (6.107), and for concreteness we will use the standard dot product here $( \langle \pmb \theta , \phi ( \pmb x ) \rangle = \pmb \theta ^ { \top } \phi ( \pmb x ) )$ . Note that the form of the exponential family is essentially a particular expression of $g _ { \theta } ( \phi ( x ) )$ 1 in the Fisher-Neyman theorem (Theorem 6.14). 

The factor $h ( { \pmb x } )$ can be absorbed into the dot product term by adding another entry $( \log h ( { \pmb x } ) )$ to the vector of sufficient statistics $\phi ( { \pmb x } )$ , and constraining the corresponding parameter $\theta _ { 0 } = 1$ . The term $A ( \pmb \theta )$ is the normalization constant that ensures that the distribution sums up or integrates to one and is called the log-partition function. A good intuitive notion of exponential families can be obtained by ignoring these two terms and considering exponential families as distributions of the form 

$$
p (\boldsymbol {x} \mid \boldsymbol {\theta}) \propto \exp \left(\boldsymbol {\theta} ^ {\top} \phi (\boldsymbol {x})\right).\tag{6.108}
$$

natural parameters 

For this form of parametrization, the parameters $\pmb \theta$ are called the natural parameters. At first glance, it seems that exponential families are a mundane transformation by adding the exponential function to the result of a dot product. However, there are many implications that allow for convenient modeling and efficient computation based on the fact that we can capture information about data in $\phi ( { \pmb x } )$ 

## Example 6.13 (Gaussian as Exponential Family)

Consider the univariate Gaussian distribution ${ \mathcal { N } } ( \mu , \sigma ^ { 2 } )$ . Let $\phi ( x ) = \biggl [ \frac { x } { x ^ { 2 } } \biggr ]$ Then by using the definition of the exponential family, 

$$
p (x \mid \boldsymbol {\theta}) \propto \exp (\theta_ {1} x + \theta_ {2} x ^ {2}).\tag{6.109}
$$

Setting 

$$
\pmb {\theta} = \left[ \frac {\mu}{\sigma^ {2}}, - \frac {1}{2 \sigma^ {2}} \right] ^ {\top}\tag{6.110}
$$

and substituting into (6.109), we obtain 

$$
p (x \mid \boldsymbol {\theta}) \propto \exp \left(\frac {\mu x}{\sigma^ {2}} - \frac {x ^ {2}}{2 \sigma^ {2}}\right) \propto \exp \left(- \frac {1}{2 \sigma^ {2}} (x - \mu) ^ {2}\right).\tag{6.111}
$$

Therefore, the univariate Gaussian distribution is a member of the exponential family with sufficient statistic $\phi ( x ) = { \Big [ } { x } { \Big ] }$ , and natural parameters given by $\pmb \theta$ in (6.110). 

## Example 6.14 (Bernoulli as Exponential Family)

Recall the Bernoulli distribution from Example 6.8 

$$
p (x \mid \mu) = \mu^ {x} (1 - \mu) ^ {1 - x}, \quad x \in \{0, 1 \}.\tag{6.112}
$$

This can be written in exponential family form 

$$
p (x \mid \mu) = \exp \left[ \log \left(\mu^ {x} (1 - \mu) ^ {1 - x}\right) \right]\tag{6.113a}
$$

$$
= \exp \left[ x \log \mu + (1 - x) \log (1 - \mu) \right]\tag{6.113b}
$$

$$
= \exp \left[ x \log \mu - x \log (1 - \mu) + \log (1 - \mu) \right]\tag{6.113c}
$$

$$
= \exp \left[ x \log {\frac {\mu}{1 - \mu}} + \log (1 - \mu) \right].\tag{6.113d}
$$

The last line (6.113d) can be identified as being in exponential family form (6.107) by observing that 

$$
h (x) = 1\tag{6.114}
$$



Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 



$$
\theta = \log {\frac {\mu}{1 - \mu}}\tag{6.115}
$$

$$
\phi (x) = x\tag{6.116}
$$

$$
A (\theta) = - \log (1 - \mu) = \log (1 + \exp (\theta)).\tag{6.117}
$$

The relationship between θ and $\mu$ is invertible so that 

$$
\mu = \frac {1}{1 + \exp (- \theta)}.\tag{6.118}
$$

The relation (6.118) is used to obtain the right equality of (6.117). 

Remark. The relationship between the original Bernoulli parameter $\mu$ and the natural parameter $\theta$ is known as the sigmoid or logistic function. Observe that $\mu \in \mathsf { \Gamma } ( 0 , 1 )$ but $\theta ~ \in ~ \mathbb { R }$ , and therefore the sigmoid function squeezes a real value into the range (0, 1). This property is useful in machine learning, for example it is used in logistic regression (Bishop, 2006, section 4.3.2), as well as as a nonlinear activation functions in neural net works (Goodfellow et al., 2016, chapter 6). 

It is often not obvious how to find the parametric form of the conjugate distribution of a particular distribution (for example, those in Table 6.2). Exponential families provide a convenient way to find conjugate pairs of distributions. Consider the random variable $\dot { X }$ is a member of the exponential family (6.107): 

$$
p (\boldsymbol {x} \mid \boldsymbol {\theta}) = h (\boldsymbol {x}) \exp \left(\langle \boldsymbol {\theta}, \phi (\boldsymbol {x}) \rangle - A (\boldsymbol {\theta})\right).\tag{6.119}
$$

Every member of the exponential family has a conjugate prior (Brown, 1986) 

$$
p (\boldsymbol {\theta} \mid \boldsymbol {\gamma}) = h _ {c} (\boldsymbol {\theta}) \exp \left(\left\langle \left[ \begin{array}{c} \boldsymbol {\gamma} _ {1} \\ \boldsymbol {\gamma} _ {2} \end{array} \right], \left[ \begin{array}{c} \boldsymbol {\theta} \\ - A (\boldsymbol {\theta}) \end{array} \right] \right\rangle - A _ {c} (\boldsymbol {\gamma})\right)  ,\tag{6.120}
$$

where $\gamma = \binom { \gamma _ { 1 } } { \gamma _ { 2 } }$ has dimension dim $( \pmb \theta ) + 1$ . The sufficient statistics of the conjugate prior are $\left[ - \stackrel { \theta } { A ( \theta ) } \right]$ . By using the knowledge of the general form of conjugate priors for exponential families, we can derive functional forms of conjugate priors corresponding to particular distributions. 

## Example 6.15

Recall the exponential family form of the Bernoulli distribution (6.113d) 

$$
p (x \mid \mu) = \exp \left[ x \log {\frac {\mu}{1 - \mu}} + \log (1 - \mu) \right].\tag{6.121}
$$



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



The canonical conjugate prior has the form 

$$
p (\mu \mid \alpha , \beta) = \frac {\mu}{1 - \mu} \exp \left[ \alpha \log \frac {\mu}{1 - \mu} + (\beta + \alpha) \log (1 - \mu) - A _ {c} (\boldsymbol {\gamma}) \right],\tag{6.122}
$$

where we defined $\gamma : = [ \alpha , \beta + \alpha ] ^ { \intercal }$ and $h _ { c } ( \mu ) : = \mu / ( 1 - \mu )$ . Equation (6.122) then simplifies to 

$$
p (\mu \mid \alpha , \beta) = \exp \left[ (\alpha - 1) \log \mu + (\beta - 1) \log (1 - \mu) - A _ {c} (\alpha , \beta) \right].\tag{6.123}
$$

Putting this in non-exponential family form yields 

$$
p (\mu \mid \alpha , \beta) \propto \mu^ {\alpha - 1} (1 - \mu) ^ {\beta - 1},\tag{6.124}
$$

which we identify as the Beta distribution (6.98). In example 6.12, we assumed that the Beta distribution is the conjugate prior of the Bernoulli distribution and showed that it was indeed the conjugate prior. In this example, we derived the form of the Beta distribution by looking at the canonical conjugate prior of the Bernoulli distribution in exponential family form. 

As mentioned in the previous section, the main motivation for exponential families is that they have finite-dimensional sufficient statistics. Additionally, conjugate distributions are easy to write down, and the conjugate distributions also come from an exponential family. From an inference perspective, maximum likelihood estimation behaves nicely because empirical estimates of sufficient statistics are optimal estimates of the population values of sufficient statistics (recall the mean and covariance of a Gaussian). From an optimization perspective, the log-likelihood function is concave, allowing for efficient optimization approaches to be applied (Chapter 7). 

## 6.7 Change of Variables/Inverse Transform

It may seem that there are very many known distributions, but in reality the set of distributions for which we have names is quite limited. Therefore, it is often useful to understand how transformed random variables are distributed. For example, assuming that X is a random variable distributed according to the univariate normal distribution $\mathcal { N } ( 0 , 1 )$ , what is the distribution of $X ^ { 2 } ?$ Another example, which is quite common in machine learning, is, given that $X _ { 1 }$ and $X _ { 2 }$ are univariate standard normal, what is the distribution of ${ \scriptstyle { \frac { 1 } { 2 } } } ( X _ { 1 } + X _ { 2 } ) ?$ 

One option to work out the distribution of ${ \scriptstyle { \frac { 1 } { 2 } } } ( X _ { 1 } + X _ { 2 } )$ is to calculate the mean and variance of $X _ { 1 }$ and $X _ { 2 }$ and then combine them. As we saw in Section $6 . 4 . 4 .$ , we can calculate the mean and variance of resulting random variables when we consider affine transformations of random variables. However, we may not be able to obtain the functional form of the distribution under transformations. Furthermore, we may be interested in nonlinear transformations of random variables for which closed-form expressions are not readily available. 

Remark (Notation). In this section, we will be explicit about random variables and the values they take. Hence, recall that we use capital letters $X , Y$ to denote random variables and small letters $x , y$ to denote the values in the target space $\tau$ that the random variables take. We will explicitly write pmfs of discrete random variables $X$ as $P ( X = x )$ . For continuous random variables X (Section 6.2.2), the pdf is written as $f ( x )$ and the cdf is written as $F _ { X } ( x )$ 

We will look at two approaches for obtaining distributions of transformations of random variables: a direct approach using the definition of a cumulative distribution function and a change-of-variable approach that uses the chain rule of calculus (Section 5.2.2). The change-of-variable approach is widely used because it provides a “recipe” for attempting to compute the resulting distribution due to a transformation. We will explain the techniques for univariate random variables, and will only briefly provide the results for the general case of multivariate random variables. 

Transformations of discrete random variables can be understood directly. Suppose that there is a discrete random variable X with pmf $P ( X =$ $x )$ (Section 6.2.1), and an invertible function $U ( x )$ . Consider the transformed random variable $Y : = U ( X )$ , with pmf $P ( \boldsymbol { Y } = \boldsymbol { y } )$ . Then 

$$
\begin{array}{c c} P (Y = y) = P (U (X) = y) & \text { transformation   of   interest } \\ = P (X = U ^ {- 1} (y)) & \text { inverse } \end{array}\tag{6.125a}
$$

(6.125b) 

where we can observe that $x = U ^ { - 1 } ( y )$ . Therefore, for discrete random variables, transformations directly change the individual events (with the probabilities appropriately transformed). 

## 6.7.1 Distribution Function Technique

The distribution function technique goes back to first principles, and uses the definition of a cdf $F _ { X } ( x ) = P ( X \leqslant x )$ and the fact that its differential is the pdf $f ( x )$ (Wasserman, 2004, chapter 2). For a random variable $X$ and a function $U$ , we find the pdf of the random variable $Y : = U ( X )$ by 

1. Finding the cdf: 

$$
F _ {Y} (y) = P (Y \leqslant y)\tag{6.126}
$$

2. Differentiating the cdf $F _ { Y } ( y )$ to get the pdf $f ( y )$ 

$$
f (y) = \frac {\mathrm{d}}{\mathrm{d} y} F _ {Y} (y).\tag{6.127}
$$

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

We also need to keep in mind that the domain of the random variable may have changed due to the transformation by $U$ 

## Example 6.16

Let $X$ be a continuous random variable with probability density function on $0 \leqslant x \leqslant 1$ 

$$
f (x) = 3 x ^ {2}.\tag{6.128}
$$

We are interested in finding the pdf of $Y = X ^ { 2 }$ 

The function $f$ is an increasing function of $x ,$ and therefore the resulting value of $y$ lies in the interval [0, 1]. We obtain 

$$
F _ {Y} (y) = P (Y \leqslant y)
$$

definition of cdf 

$$
= P (X ^ {2} \leqslant y)\tag{6.129a}
$$

transformation of interest 

$$
= P (X \leqslant y ^ {\frac {1}{2}})\tag{6.129b}
$$

inverse 

$$
= F _ {X} (y ^ {\frac {1}{2}})\tag{6.129c}
$$

definition of cdf 

$$
= \int_ {0} ^ {y ^ {\frac {1}{2}}} 3 t ^ {2} \mathrm{d} t\tag{6.129d}
$$

cdf as a definite integral 

$$
= \left[ t ^ {3} \right] _ {t = 0} ^ {t = y ^ {\frac {1}{2}}}\tag{6.129e}
$$

result of integration 

(6.129f) 

$$
= y ^ {\frac {3}{2}}, \quad 0 \leqslant y \leqslant 1.\tag{6.129g}
$$

Therefore, the cdf of $Y$ is 

$$
F _ {Y} (y) = y ^ {\frac {3}{2}}\tag{6.130}
$$

for $0 \leqslant y \leqslant 1$ . To obtain the pdf, we differentiate the cdf 

$$
f (y) = \frac {\mathrm{d}}{\mathrm{d} y} F _ {Y} (y) = \frac {3}{2} y ^ {\frac {1}{2}}\tag{6.131}
$$

for $0 \leqslant y \leqslant 1$ 

Functions that have inverses are called bijective functions (Section 2.7). 

In Example 6.16, we considered a strictly monotonically increasing function $f ( x ) = 3 x ^ { 2 }$ . This means that we could compute an inverse function. In general, we require that the function of interest $y = U ( x )$ has an inverse $x = U ^ { - 1 } ( y )$ . A useful result can be obtained by considering the cumulative distribution function $F _ { X } ( x )$ of a random variable X, and using it as the transformation $U ( x )$ . This leads to the following theorem. 

Theorem 6.15. [Theorem 2.1.10 in Casella and Berger (2002)] Let X be a continuous random variable with a strictly monotonic cumulative distribution function $F _ { X } ( x )$ . Then the random variable Y defined as 

$$
Y := F _ {X} (X)\tag{6.132}
$$

has a uniform distribution. 

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

Theorem 6.15 is known as the probability integral transform, and it is used to derive algorithms for sampling from distributions by transforming the result of sampling from a uniform random variable (Bishop, 2006). The algorithm works by first generating a sample from a uniform distribu tion, then transforming it by the inverse cdf (assuming this is available) to obtain a sample from the desired distribution. The probability integral transform is also used for hypothesis testing whether a sample comes from a particular distribution (Lehmann and Romano, 2005). The idea that the output of a cdf gives a uniform distribution also forms the basis of copu las (Nelsen, 2006). 

## 6.7.2 Change of Variables

The distribution function technique in Section 6.7.1 is derived from first principles, based on the definitions of cdfs and using properties of inverses, differentiation, and integration. This argument from first principles relies on two facts: 

1. We can transform the cdf of Y into an expression that is a cdf of X. 2. We can differentiate the cdf to obtain the pdf. 

Let us break down the reasoning step by step, with the goal of understanding the more general change-of-variables approach in Theorem 6.16. 

Remark. The name “change of variables” comes from the idea of changing the variable of integration when faced with a difficult integral. For univariate functions, we use the substitution rule of integration, 

$$
\int f (g (x)) g ^ {\prime} (x) \mathrm{d} x = \int f (u) \mathrm{d} u, \quad \text { where } \quad u = g (x).\tag{6.133}
$$

The derivation of this rule is based on the chain rule of calculus (5.32) and by applying twice the fundamental theorem of calculus. The fundamental theorem of calculus formalizes the fact that integration and differentiation are somehow “inverses” of each other. An intuitive understanding of the rule can be obtained by thinking (loosely) about small changes (differentials) to the equation $u = g ( x )$ , that is by considering $\Delta u = g ^ { \prime } ( x ) \Delta x$ as a differential of $u = g ( x )$ . By substituting $u = g ( x )$ , the argument inside the integral on the right-hand side of (6.133) becomes $f ( g ( x ) )$ ). By pretending that the term du can be approximated by du $\approx \Delta u = g ^ { \prime } ( x ) \Delta x$ , and that dx $\Delta x$ , we obtain (6.133). 

Consider a univariate random variable X, and an invertible function $U _ { ☉ }$ , which gives us another random variable $Y = U ( X )$ . We assume that random variable X has states $x \in [ a , b ]$ . By the definition of the cdf, we have 

$$
F _ {Y} (y) = P (Y \leqslant y).\tag{6.134}
$$



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



We are interested in a function $U$ of the random variable 

$$
P (Y \leqslant y) = P (U (X) \leqslant y),\tag{6.135}
$$

where we assume that the function $U$ is invertible. An invertible function on an interval is either strictly increasing or strictly decreasing. In the case that $U$ is strictly increasing, then its inverse $U ^ { - 1 }$ is also strictly increasing. By applying the inverse $U ^ { - 1 }$ to the arguments of $P ( U ( X ) \leqslant y )$ , we obtain 

$$
P (U (X) \leqslant y) = P (U ^ {- 1} (U (X)) \leqslant U ^ {- 1} (y)) = P (X \leqslant U ^ {- 1} (y)).\tag{6.136}
$$

The right-most term in (6.136) is an expression of the cdf of X. Recall the definition of the cdf in terms of the pdf 

$$
P (X \leqslant U ^ {- 1} (y)) = \int_ {a} ^ {U ^ {- 1} (y)} f (x) \mathrm{d} x.\tag{6.137}
$$

Now we have an expression of the cdf of $Y$ in terms of x: 

$$
F _ {Y} (y) = \int_ {a} ^ {U ^ {- 1} (y)} f (x) \mathrm{d} x.\tag{6.138}
$$

To obtain the pdf, we differentiate (6.138) with respect to $y \colon$ 

$$
f (y) = \frac {\mathrm{d}}{\mathrm{d} y} F _ {y} (y) = \frac {\mathrm{d}}{\mathrm{d} y} \int_ {a} ^ {U ^ {- 1} (y)} f (x) \mathrm{d} x.\tag{6.139}
$$

Note that the integral on the right-hand side is with respect to $x ,$ , but we need an integral with respect to y because we are differentiating with respect to $y .$ . In particular, we use (6.133) to get the substitution 

$$
\int f (U ^ {- 1} (y)) U ^ {- 1 ^ {\prime}} (y) \mathrm{d} y = \int f (x) \mathrm{d} x \quad \text { where } \quad x = U ^ {- 1} (y)  .\tag{6.140}
$$

Using (6.140) on the right-hand side of (6.139) gives us 

$$
f (y) = \frac {\mathrm{d}}{\mathrm{d} y} \int_ {a} ^ {U ^ {- 1} (y)} f _ {x} (U ^ {- 1} (y)) U ^ {- 1 ^ {\prime}} (y) \mathrm{d} y.\tag{6.141}
$$

We then recall that differentiation is a linear operator and we use the subscript x to remind ourselves that $f _ { x } ( U ^ { - 1 } ( y ) )$ is a function of x and not $y .$ Invoking the fundamental theorem of calculus again gives us 

$$
f (y) = f _ {x} \left(U ^ {- 1} (y)\right) \cdot \left(\frac {\mathrm{d}}{\mathrm{d} y} U ^ {- 1} (y)\right).\tag{6.142}
$$

Recall that we assumed that $U$ is a strictly increasing function. For decreasing functions, it turns out that we have a negative sign when we follow the same derivation. We introduce the absolute value of the differential to have the same expression for both increasing and decreasing $U$ : 

$$
f (y) = f _ {x} \left(U ^ {- 1} (y)\right) \cdot \left| \frac {\mathrm{d}}{\mathrm{d} y} U ^ {- 1} (y) \right|.\tag{6.143}
$$

This is called the change-of-variable technique. The term $\begin{array} { r } { \left| { \frac { \operatorname { d } } { \operatorname { d } y } } U ^ { - 1 } ( y ) \right| } \end{array}$ in (6.143) measures how much a unit volume changes when applying $U$ (see also the definition of the Jacobian in Section 5.3). 

Remark. In comparison to the discrete case in (6.125b), we have an additional factor $\begin{array} { r } { \left| { \frac { \operatorname { d } } { \operatorname { d } y } } U ^ { - 1 } ( y ) \right| } \end{array}$ . The continuous case requires more care because $P ( Y = y ) \stackrel { . } { = } 0$ for all $y .$ . The probability density function $f ( y )$ does not have a description as a probability of an event involving $y .$ . ◇ 

So far in this section, we have been studying univariate change of variables. The case for multivariate random variables is analogous, but complicated by fact that the absolute value cannot be used for multivariate functions. Instead, we use the determinant of the Jacobian matrix. Recall from (5.58) that the Jacobian is a matrix of partial derivatives, and that the existence of a nonzero determinant shows that we can invert the Jacobian. Recall the discussion in Section 4.1 that the determinant arises because our differentials (cubes of volume) are transformed into paral lelepipeds by the Jacobian. Let us summarize preceding the discussion in the following theorem, which gives us a recipe for multivariate change of variables. 

Theorem 6.16. [Theorem 17.2 in Billingsley (1995)] Let $f ( { \pmb x } )$ be the value of the probability density of the multivariate continuous random variable $X$ If the vector-valued function $\mathbf {  { y } } = U ( \mathbf {  { x } } )$ is differentiable and invertible for all values within the domain of $\mathbf { \delta } _ { \mathbf { x } , \mathbf { \delta } }$ then for corresponding values of $^ { y , }$ the probability density of $Y = U ( X )$ is given by 

$$
f (\boldsymbol {y}) = f _ {\boldsymbol {x}} \left(U ^ {- 1} (\boldsymbol {y})\right) \cdot \left| \det \left(\frac {\partial}{\partial \boldsymbol {y}} U ^ {- 1} (\boldsymbol {y})\right) \right|.\tag{6.144}
$$

The theorem looks intimidating at first glance, but the key point is that a change of variable of a multivariate random variable follows the procedure of the univariate change of variable. First we need to work out the inverse transform, and substitute that into the density of x. Then we calculate the determinant of the Jacobian and multiply the result. The following example illustrates the case of a bivariate random variable. 

## Example 6.17

Consider a bivariate random variable X with states $\pmb { x } = \left[ \begin{array} { l } { x _ { 1 } } \\ { x _ { 2 } } \end{array} \right]$ and probability density function 

$$
f \left(\left[ \begin{array}{c} x _ {1} \\ x _ {2} \end{array} \right]\right) = \frac {1}{2 \pi} \exp \left(- \frac {1}{2} \left[ \begin{array}{c} x _ {1} \\ x _ {2} \end{array} \right] ^ {\top} \left[ \begin{array}{c} x _ {1} \\ x _ {2} \end{array} \right]\right).\tag{6.145}
$$

We use the change-of-variable technique from Theorem 6.16 to derive the 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



effect of a linear transformation (Section 2.7) of the random variable. Consider a matrix $A \in \mathbb { R } ^ { 2 \times 2 }$ defined as 

$$
\boldsymbol {A} = \left[ \begin{array}{c c} a & b \\ c & d \end{array} \right].\tag{6.146}
$$

We are interested in finding the probability density function of the transformed bivariate random variable $Y$ with states $y = A x$ 

Recall that for change of variables we require the inverse transformation of x as a function of $\mathbf { \pmb { y } } .$ . Since we consider linear transformations, the inverse transformation is given by the matrix inverse (see Section 2.2.2). For $2 \times 2$ matrices, we can explicitly write out the formula, given by 

$$
\left[ \begin{array}{c} x _ {1} \\ x _ {2} \end{array} \right] = \boldsymbol {A} ^ {- 1} \left[ \begin{array}{c} y _ {1} \\ y _ {2} \end{array} \right] = \frac {1}{a d - b c} \left[ \begin{array}{c c} d & - b \\ - c & a \end{array} \right] \left[ \begin{array}{c} y _ {1} \\ y _ {2} \end{array} \right].\tag{6.147}
$$

Observe that $a d - b c$ is the determinant (Section 4.1) of A. The corresponding probability density function is given by 

$$
f (\boldsymbol {x}) = f \left(\boldsymbol {A} ^ {- 1} \boldsymbol {y}\right) = \frac {1}{2 \pi} \exp \left(- \frac {1}{2} \boldsymbol {y} ^ {\top} \boldsymbol {A} ^ {- \top} \boldsymbol {A} ^ {- 1} \boldsymbol {y}\right).\tag{6.148}
$$

The partial derivative of a matrix times a vector with respect to the vector is the matrix itself (Section 5.5), and therefore 

$$
\frac {\partial}{\partial \boldsymbol {y}} \boldsymbol {A} ^ {- 1} \boldsymbol {y} = \boldsymbol {A} ^ {- 1}.\tag{6.149}
$$

Recall from Section 4.1 that the determinant of the inverse is the inverse of the determinant so that the determinant of the Jacobian matrix is 

$$
\det \left(\frac {\partial}{\partial \boldsymbol {y}} \boldsymbol {A} ^ {- 1} \boldsymbol {y}\right) = \frac {1}{a d - b c}.\tag{6.150}
$$

We are now able to apply the change-of-variable formula from Theorem 6.16 by multiplying (6.148) with (6.150), which yields 

$$
f (\boldsymbol {y}) = f (\boldsymbol {x}) \left| \det \left(\frac {\partial}{\partial \boldsymbol {y}} \boldsymbol {A} ^ {- 1} \boldsymbol {y}\right) \right|\tag{6.151a}
$$

$$
= \frac {1}{2 \pi} \exp \left(- \frac {1}{2} \pmb {y} ^ {\top} \pmb {A} ^ {- \top} \pmb {A} ^ {- 1} \pmb {y}\right) | a d - b c | ^ {- 1}.\tag{6.151b}
$$

While Example 6.17 is based on a bivariate random variable, which allows us to easily compute the matrix inverse, the preceding relation holds for higher dimensions. 

Remark. We saw in Section 6.5 that the density $f ( { \pmb x } )$ in (6.148) is actually the standard Gaussian distribution, and the transformed density $f ( \boldsymbol { y } )$ is a bivariate Gaussian with covariance $\pmb { \Sigma } = \pmb { A } \pmb { A } ^ { \top }$ ◇ 

We will use the ideas in this chapter to describe probabilistic modeling in Section 8.4, as well as introduce a graphical language in Section 8.5. We will see direct machine learning applications of these ideas in Chapters 9 and 11. 

## 6.8 Further Reading

This chapter is rather terse at times. Grinstead and Snell (1997) and Walpole et al. (2011) provide more relaxed presentations that are suit able for self-study. Readers interested in more philosophical aspects of probability should consider Hacking (2001), whereas an approach that is more related to software engineering is presented by Downey (2014). An overview of exponential families can be found in Barndorff-Nielsen (2014). We will see more about how to use probability distributions to model machine learning tasks in Chapter 8. Ironically, the recent surge in interest in neural networks has resulted in a broader appreciation of probabilistic models. For example, the idea of normalizing flows (Jimenez Rezende and Mohamed, 2015) relies on change of variables for transforming random variables. An overview of methods for variational inference as applied to neural networks is described in chapters 16 to 20 of the book by Goodfellow et al. (2016). 

We side stepped a large part of the difficulty in continuous random variables by avoiding measure theoretic questions (Billingsley, 1995; Pollard, 2002), and by assuming without construction that we have real numbers, and ways of defining sets on real numbers as well as their appropriate frequency of occurrence. These details do matter, for example, in the specifi cation of conditional probability $p ( y \mid x )$ for continuous random variables $x , y$ (Proschan and Presnell, 1998). The lazy notation hides the fact that we want to specify that $X \ = \ x$ (which is a set of measure zero). Furthermore, we are interested in the probability density function of y. A more precise notation would have to say $\mathbb { E } _ { y } [ f ( y ) | \sigma ( x ) ]$ , where we take the expectation over y of a test function $f$ conditioned on the σ-algebra of x. A more technical audience interested in the details of probability theory have many options (Jaynes, 2003; MacKay, 2003; Jacod and Protter, 2004; Grimmett and Welsh, 2014), including some very technical discussions (Shiryayev, 1984; Lehmann and Casella, 1998; Dudley, 2002; Bickel and Doksum, 2006; C¸inlar, 2011). An alternative way to approach probability is to start with the concept of expectation, and “work backward” to derive the necessary properties of a probability space (Whittle, 2000). As machine learning allows us to model more intricate distributions on ever more complex types of data, a developer of probabilistic machine learning models would have to understand these more technical aspects. Ma chine learning texts with a probabilistic modeling focus include the books by MacKay (2003); Bishop (2006); Rasmussen and Williams (2006); Barber (2012); Murphy (2012). 



©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 



## Exercises

6.1 Consider the following bivariate distribution $p ( x , y )$ of two discrete random variables X and $Y$ . 

<table><tr><td>y1</td><td>0.01</td><td>0.02</td><td>0.03</td><td>0.1</td><td>0.1</td></tr><tr><td>y2</td><td>0.05</td><td>0.1</td><td>0.05</td><td>0.07</td><td>0.2</td></tr><tr><td>y3</td><td>0.1</td><td>0.05</td><td>0.03</td><td>0.05</td><td>0.04</td></tr></table>

Compute: 

a. The marginal distributions $p ( x )$ and $p ( y )$ 

b. The conditional distributions $p ( x | Y = y _ { 1 } )$ and $p ( y | X = x _ { 3 } )$ 

6.2 Consider a mixture of two Gaussian distributions (illustrated in Figure 6.4), 

$$
0. 4 \mathcal {N} \left(\left[ \begin{array}{c} 1 0 \\ 2 \end{array} \right], \left[ \begin{array}{c c} 1 & 0 \\ 0 & 1 \end{array} \right]\right) + 0. 6 \mathcal {N} \left(\left[ \begin{array}{c} 0 \\ 0 \end{array} \right], \left[ \begin{array}{c c} 8. 4 & 2. 0 \\ 2. 0 & 1. 7 \end{array} \right]\right).
$$

a. Compute the marginal distributions for each dimension. 

b. Compute the mean, mode and median for each marginal distribution. 

c. Compute the mean and mode for the two-dimensional distribution. 

You have written a computer program that sometimes compiles and sometimes not (code does not change). You decide to model the apparent stochasticity (success vs. no success) x of the compiler using a Bernoulli distribution with parameter $\mu \colon$ 

$$
p (x \mid \mu) = \mu^ {x} (1 - \mu) ^ {1 - x}, \quad x \in \{0, 1 \}.
$$

Choose a conjugate prior for the Bernoulli likelihood and compute the posterior distribution $p ( \mu | x _ { 1 } , \ldots , x _ { N } )$ . 

There are two bags. The first bag contains four mangos and two apples; the second bag contains four mangos and four apples. 

We also have a biased coin, which shows “heads” with probability 0.6 and “tails” with probability 0.4. If the coin shows “heads”. we pick a fruit at random from bag 1; otherwise we pick a fruit at random from bag 2. 

Your friend flips the coin (you cannot see the result), picks a fruit at random from the corresponding bag, and presents you a mango. 

What is the probability that the mango was picked from bag 2? 

Hint: Use Bayes’ theorem. 

6.5 Consider the time-series model 

$$
\begin{array}{c} \boldsymbol {x} _ {t + 1} = \boldsymbol {A} \boldsymbol {x} _ {t} + \boldsymbol {w}, \quad \boldsymbol {w} \sim \mathcal {N} (\boldsymbol {0}, \boldsymbol {Q}) \\ \boldsymbol {y} _ {t} = \boldsymbol {C} \boldsymbol {x} _ {t} + \boldsymbol {v}, \quad \boldsymbol {v} \sim \mathcal {N} (\boldsymbol {0}, \boldsymbol {R}), \end{array}
$$

where w, v are i.i.d. Gaussian noise variables. Further, assume that $p ( \pmb { x } _ { 0 } ) =$ $\mathcal { N } ( \mu _ { 0 } , \Sigma _ { 0 } )$ 

Draft (2024-01-15) of “Mathematics for Machine Learning”. Feedback: https://mml-book.com. 

a. What is the form of $p ( { \pmb x } _ { 0 } , { \pmb x } _ { 1 } , \ldots , { \pmb x } _ { T } ) ?$ Justify your answer (you do not have to explicitly compute the joint distribution). 

b. Assume that $p ( \pmb { x } _ { t } | \pmb { y } _ { 1 } , \dots , \pmb { y } _ { t } ) = \mathcal { N } \big ( \pmb { \mu } _ { t } , \pmb { \Sigma } _ { t } \big )$ 

1. Compute $p ( \pmb { x } _ { t + 1 } \mid \pmb { y } _ { 1 } , \ldots , \pmb { y } _ { t } )$ 

2. Compute $p ( \pmb { x } _ { t + 1 } , \pmb { y } _ { t + 1 } \mid \pmb { y } _ { 1 } , \dots , \pmb { y } _ { t } ) .$ 

3. At time t+1, we observe the value $\pmb { y } _ { t + 1 } = \hat { \pmb { y } }$ . Compute the conditional distribution $p ( \pmb { x } _ { t + 1 } | \pmb { y } _ { 1 } , \dots , \pmb { y } _ { t + 1 } )$ 

6.6 Prove the relationship in $_ { ( 6 . 4 4 ) }$ , which relates the standard definition of the variance to the raw-score expression for the variance. 

6.7 Prove the relationship in (6.45), which relates the pairwise difference between examples in a dataset with the raw-score expression for the variance. 

6.8 Express the Bernoulli distribution in the natural parameter form of the ex ponential family, see (6.107). 

6.9 Express the Binomial distribution as an exponential family distribution. Also express the Beta distribution is an exponential family distribution. Show that the product of the Beta and the Binomial distribution is also a member of the exponential family. 

6.10 Derive the relationship in Section 6.5.2 in two ways: 

a. By completing the square 

b. By expressing the Gaussian in its exponential family form 

The product of two Gaussians $\mathcal { N } \big ( \mathbf { { x } } \mid \mathbf { { a } } , A \big ) \mathcal { N } \big ( \mathbf { { x } } \mid b , B \big )$ is an unnormalized Gaussian distribution $c { \mathcal { N } } ( { \pmb x } | { \pmb c } , { \pmb C } )$ with 

$$
\boldsymbol {C} = \left(\boldsymbol {A} ^ {- 1} + \boldsymbol {B} ^ {- 1}\right) ^ {- 1}
$$

$$
\boldsymbol {c} = \boldsymbol {C} (\boldsymbol {A} ^ {- 1} \boldsymbol {a} + \boldsymbol {B} ^ {- 1} \boldsymbol {b})
$$

$$
c = (2 \pi) ^ {- \frac {D}{2}} | \boldsymbol {A} + \boldsymbol {B} | ^ {- \frac {1}{2}} \exp \left(- \frac {1}{2} (\boldsymbol {a} - \boldsymbol {b}) ^ {\top} (\boldsymbol {A} + \boldsymbol {B}) ^ {- 1} (\boldsymbol {a} - \boldsymbol {b})\right).
$$

Note that the normalizing constant c itself can be considered a (normalized) Gaussian distribution either in a or in b with an “inflated” covariance matrix $A + B , \operatorname { i . e . , } c = { \mathcal { N } } { \big ( } a \mid b , A + B { \big ) } = { \mathcal { N } } { \big ( } b \mid a , A + B { \big ) }$ 

## 6.11 Iterated Expectations.

Consider two random variables $x , y$ with joint distribution $p ( x , y )$ . Show that 

$$
\mathbb {E} _ {X} [ x ] = \mathbb {E} _ {Y} \left[ \mathbb {E} _ {X} [ x \mid y ] \right].
$$

Here, $\mathbb { E } _ { X } [ x \mid y ]$ denotes the expected value of x under the conditional distribution $p ( x \mid y )$ 

## 6.12 Manipulation of Gaussian Random Variables.

Consider a Gaussian random variable $\pmb { x } \sim \mathcal { N } \big ( \pmb { x } | \pmb { \mu } _ { x } , \pmb { \Sigma } _ { x } \big )$ , where $\pmb { x } \in \mathbb { R } ^ { D }$ Furthermore, we have 

$$
\boldsymbol {y} = \boldsymbol {A} \boldsymbol {x} + \boldsymbol {b} + \boldsymbol {w},
$$

where $\pmb { y } \in \mathbb { R } ^ { E } , \pmb { A } \in \mathbb { R } ^ { E \times D } , \pmb { b } \in \mathbb { R } ^ { E }$ , and ${ \pmb w } \sim \mathcal { N } \big ( { \pmb w } | { \bf 0 } , Q \big )$ is independent Gaussian noise. “Independent” implies that x and w are independent random variables and that Q is diagonal. 

a. Write down the likelihood $p ( \pmb { y } \vert \pmb { x } )$ 

b. The distribution $\begin{array} { r } { p ( { \pmb y } ) = \int p ( { \pmb y } | { \pmb x } ) p ( { \pmb x } ) } \end{array}$ dx is Gaussian. Compute the mean $\mu _ { y }$ and the covariance $\Sigma _ { y }$ . Derive your result in detail. 

©2024 M. P. Deisenroth, A. A. Faisal, C. S. Ong. Published by Cambridge University Press (2020). 

c. The random variable $\textbf {  { y } }$ is being transformed according to the measurement mapping 

$$
\boldsymbol {z} = \boldsymbol {C y} + \boldsymbol {v},
$$

where $\boldsymbol { z } \in \mathbb { R } ^ { F } , \boldsymbol { C } \in \mathbb { R } ^ { F \times E }$ , and ${ \pmb v } \sim \mathcal { N } \big ( { \pmb v } \mid { \bf 0 } , { \pmb R } \big )$ is independent Gaussian (measurement) noise. 

Write down $p ( z \mid \pmb { y } )$ 

Compute $p ( z )$ , i.e., the mean $\mu _ { z }$ and the covariance $\Sigma _ { z }$ . Derive your result in detail. 

d. Now, a value $\hat { \pmb y }$ is measured. Compute the posterior distribution $p ( \pmb { x } | \hat { \pmb y } )$ Hint for solution: This posterior is also Gaussian, i.e., we need to determine only its mean and covariance matrix. Start by explicitly computing the joint Gaussian $p ( { \pmb x } , { \pmb y } )$ . This also requires us to compute the cross-covariances $\mathrm { C o v } _ { \pmb { x } , \pmb { y } } [ \pmb { x } , \pmb { y } ]$ and $\mathrm { C o v } _ { { \pmb y } , { \pmb x } } [ { \pmb y } , { \pmb x } ]$ . Then apply the rules for Gaussian conditioning. 

## 6.13 Probability Integral Transformation

Given a continuous random variable $X ,$ , with cdf $F _ { X } ( x )$ , show that the random variable $Y : = F _ { X } ( X )$ is uniformly distributed (Theorem 6.15). 