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

