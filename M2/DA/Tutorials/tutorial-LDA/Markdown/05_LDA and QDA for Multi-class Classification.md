## 5. LDA and QDA for Multi-class Classification

Now we consider multiple classes, which can be more than two, indexed by $k \in \{ 1 , \ldots , | { \mathcal { C } } | \}$ . Recall Eq. (12) or (15) where we are using the scaled posterior, i.e., $f _ { k } ( { \pmb x } ) \pi _ { k } . \operatorname { A c - }$ cording to Eq. (16), we have: 

$$
\begin{array}{l} f _ {k} (\boldsymbol {x}) \pi_ {k} \\ = \frac {1}{\sqrt {(2 \pi) ^ {d} | \boldsymbol {\Sigma} _ {k} |}} \exp \Big (- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {k})}{2} \Big) \pi_ {k}. \end{array}
$$

Taking natural logarithm gives: 

$$
\begin{array}{c} \ln (f _ {k} (\boldsymbol {x})   \pi_ {k}) = - \frac {d}{2} \ln (2 \pi) - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {k} |) \\ - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) + \ln (\pi_ {k}). \end{array}
$$

We drop the constant term $- ( d / 2 ) \ln ( 2 \pi )$ which is the same for all classes (note that this term is multiplied before taking the logarithm). Thus, the scaled posterior of the k-th class becomes: 

$$
\begin{array}{c} \delta_ {k} (\boldsymbol {x}) := - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {k} |) \\ - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) + \ln (\pi_ {k}). \end{array}\tag{28}
$$

In QDA, the class of the instance x is estimated as: 

$$
\widehat {\mathcal {C}} (\boldsymbol {x}) = \arg \max _ {k} \delta_ {k} (\boldsymbol {x}),\tag{29}
$$

because it maximizes the posterior of that class. In this expression, $\delta ( { \pmb x } )$ is Eq. (28). 

In LDA, we assume that the covariance matrices of the k classes are equal: 

$$
\boldsymbol {\Sigma} _ {1} = \dots = \boldsymbol {\Sigma} _ {| \mathcal {C} |} = \boldsymbol {\Sigma}.\tag{30}
$$

Therefore, the Eq. (28) becomes: 

$$
\begin{array}{l} \delta_ {k} (\boldsymbol {x}) = - \frac {1}{2} \ln (| \boldsymbol {\Sigma} |) \\ - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) + \ln (\pi_ {k}) = - \frac {1}{2} \ln (| \boldsymbol {\Sigma} |) \\ - \frac {1}{2} \boldsymbol {x} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} - \frac {1}{2} \boldsymbol {\mu} _ {k} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {\mu} _ {k} + \boldsymbol {\mu} _ {k} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} + \ln (\pi_ {k}). \end{array}
$$

We drop the constant terms $- ( 1 / 2 ) \ln ( | \Sigma | )$ and $- ( 1 / 2 ) \bar { \mathbf { \Phi } } \bar { \mathbf { x } } ^ { \top } \bar { \mathbf { \Xi } } \bar { \mathbf { x } } ^ { - 1 } \mathbf { \Lambda }$ which are the same for all classes (note that before taking the logarithm, the term $- ( 1 / 2 ) \ln ( | \Sigma | )$ is multiplied and the term $- ( 1 / 2 ) \mathbf { \boldsymbol { x } } ^ { \intercal } \mathbf { \boldsymbol { \Sigma } } ^ { - 1 }$ x is multiplied as an exponential term). Thus, the scaled posterior of the k-th class becomes: 

$$
\delta_ {k} (\boldsymbol {x}) := \boldsymbol {\mu} _ {k} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} - \frac {1}{2} \boldsymbol {\mu} _ {k} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {\mu} _ {k} + \ln (\pi_ {k}).\tag{31}
$$

In LDA, the class of the instance x is determined by Eq. (29), where δ(x) is Eq. (31), because it maximizes the posterior of that class. 

In conclusion, QDA and LDA deal with maximizing the posterior of classes but work with the likelihoods (class conditional) and priors. 

