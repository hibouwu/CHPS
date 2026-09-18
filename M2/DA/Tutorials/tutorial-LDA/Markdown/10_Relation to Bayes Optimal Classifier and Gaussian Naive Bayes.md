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

