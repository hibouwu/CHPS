## 4. Quadratic Discriminant Analysis for Binary Classification

In Quadratic Discriminant Analysis (QDA), we relax the assumption of equality of the covariance matrices: 

$$
\pmb {\Sigma} _ {1} \neq \pmb {\Sigma} _ {2},\tag{24}
$$

which means the covariances are not necessarily equal (if they are actually equal, the decision boundary will be linear and QDA reduces to LDA). 

Therefore, the Eq. (17) becomes: 

$$
\begin{array}{l} \frac {1}{\sqrt {(2 \pi) ^ {d} | \boldsymbol {\Sigma} _ {1} |}} \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {1})}{2}\right) \pi_ {1} \\ = \frac {1}{\sqrt {(2 \pi) ^ {d} | \boldsymbol {\Sigma} _ {2} |}} \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {2})}{2}\right) \pi_ {2}, \\ \stackrel {{(a)}} {{\Longrightarrow}} - \frac {d}{2} \ln (2 \pi) - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {1} |) \\ \qquad - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {1}) + \ln (\pi_ {1}) \\ \qquad = - \frac {d}{2} \ln (2 \pi) - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {2} |) \\ \qquad - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {2}) + \ln (\pi_ {2}), \end{array}
$$

where (a) takes natural logarithm from the sides of equation. According to Eq. (19), we have: 

$$
\begin{array}{l} - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {1} |) - \frac {1}{2} \boldsymbol {x} ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {x} - \frac {1}{2} \boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1} \\ + \boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {x} + \ln (\pi_ {1}) \\ = - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {2} |) - \frac {1}{2} \boldsymbol {x} ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {x} - \frac {1}{2} \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2} \\ + \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {x} + \ln (\pi_ {2}). \end{array}
$$

Therefore, if we multiply the sides of equation by 2, we have: 

$$
\begin{array}{l} \boldsymbol {x} ^ {\top} (\boldsymbol {\Sigma} _ {1} - \boldsymbol {\Sigma} _ {2}) ^ {- 1} \boldsymbol {x} + 2 \left(\boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2} - \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1}\right) ^ {\top} \boldsymbol {x} \\ \quad + (\boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2}) + \ln \Big (\frac {| \boldsymbol {\Sigma} _ {1} |}{| \boldsymbol {\Sigma} _ {2} |} \Big) \\ \quad + 2 \ln (\frac {\pi_ {2}}{\pi_ {1}}) = 0, \end{array}\tag{25}
$$

which is in the quadratic form $\pmb { x } ^ { \top } \pmb { A } \pmb { x } + \pmb { b } ^ { \top } \pmb { x } + c = 0$ Therefore, if we consider Gaussian distributions for the two classes, the decision boundary of classification is quadratic. Because of quadratic decision boundary which discriminates the two classes, this method is named quadratic discriminant analysis. 

For obtaining Eq. (25), we brought the expressions to the right side which was corresponding to the second class; therefore, if we use $\delta ( \pmb { x } ) : \bar { \mathbb { R } ^ { d } }  \bar { \mathbb { R } }$ as the left-hand-side expression (function) in Eq. (25): 

$$
\begin{array}{l} \delta (\boldsymbol {x}) := \boldsymbol {x} ^ {\top} (\boldsymbol {\Sigma} _ {1} - \boldsymbol {\Sigma} _ {2}) ^ {- 1} \boldsymbol {x} + 2 \left(\boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2} - \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1}\right) ^ {\top} \boldsymbol {x} \\ \quad + (\boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2}) + \ln \Bigl (\frac {| \boldsymbol {\Sigma} _ {1} |}{| \boldsymbol {\Sigma} _ {2} |} \Bigr) + 2 \ln (\frac {\pi_ {2}}{\pi_ {1}}), \end{array}\tag{26}
$$

the class of an instance x is estimated as the Eq. (22). If the priors of two classes are equal, i.e., $\pi _ { 1 } = \pi _ { 2 }$ , the $\operatorname { E q }$ (20) becomes: 

$$
\begin{array}{l} \boldsymbol {x} ^ {\top} (\boldsymbol {\Sigma} _ {1} - \boldsymbol {\Sigma} _ {2}) ^ {- 1} \boldsymbol {x} + 2 (\boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2} - \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {x} \\ + (\boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} _ {1} ^ {- 1} \boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} _ {2} ^ {- 1} \boldsymbol {\mu} _ {2}) + \ln \Bigl (\frac {| \boldsymbol {\Sigma} _ {1} |}{| \boldsymbol {\Sigma} _ {2} |} \Bigr) = 0, \end{array}\tag{27}
$$

whose left-hand-side expression can be considered as $\delta ( { \pmb x } )$ in Eq. (22). 

