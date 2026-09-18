## 3. Linear Discriminant Analysis for Binary Classification

In Linear Discriminant Analysis (LDA), we assume that the two classes have equal covariance matrices: 

$$
\boldsymbol {\Sigma} _ {1} = \boldsymbol {\Sigma} _ {2} = \boldsymbol {\Sigma}.\tag{18}
$$

Therefore, the Eq. (17) becomes: 

$$
\begin{array}{r l} & {\frac {1}{\sqrt {(2 \pi) ^ {d} | \boldsymbol {\Sigma} |}} \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {1})}{2}\right) \pi_ {1}} \\ & {= \frac {1}{\sqrt {(2 \pi) ^ {d} | \boldsymbol {\Sigma} |}} \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {2})}{2}\right) \pi_ {2},} \\ & {\implies \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {1})}{2}\right) \pi_ {1}} \\ & {\qquad = \exp \left(- \frac {(\boldsymbol {x} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {2})}{2}\right) \pi_ {2},} \\ & {\overset {(a)} {\Longrightarrow} - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {1}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {1}) + \ln (\pi_ {1})} \\ & {\qquad = - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {2}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {2}) + \ln (\pi_ {2}),} \end{array}
$$

where (a) takes natural logarithm from the sides of equation. 

We can simplify this term as: 

$$
\begin{array}{r l} & {\left(\pmb {x} - \pmb {\mu} _ {1}\right) ^ {\top} \pmb {\Sigma} ^ {- 1} (\pmb {x} - \pmb {\mu} _ {1}) = (\pmb {x} ^ {\top} - \pmb {\mu} _ {1} ^ {\top}) \pmb {\Sigma} ^ {- 1} (\pmb {x} - \pmb {\mu} _ {1})} \\ & {= \pmb {x} ^ {\top} \pmb {\Sigma} ^ {- 1} \pmb {x} - \pmb {x} ^ {\top} \pmb {\Sigma} ^ {- 1} \pmb {\mu} _ {1} - \pmb {\mu} _ {1} ^ {\top} \pmb {\Sigma} ^ {- 1} \pmb {x} + \pmb {\mu} _ {1} ^ {\top} \pmb {\Sigma} ^ {- 1} \pmb {\mu} _ {1}} \end{array}
$$

$$
\stackrel {(a)} {=} \boldsymbol {x} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} + \boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {\mu} _ {1} - 2 \boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x},\tag{19}
$$

where (a) is because $\pmb { x } ^ { \top } \pmb { \Sigma } ^ { - 1 } \pmb { \mu } _ { 1 } ~ = ~ \pmb { \mu } _ { 1 } ^ { \top } \pmb { \Sigma } ^ { - 1 } \pmb { x }$ as it is a scalar and ${ \boldsymbol { \Sigma } } ^ { - 1 }$ is symmetric so $ { \boldsymbol { \Sigma } } ^ { - \top } =  { \boldsymbol { \Sigma } } ^ { - 1 }$ . Thus, we have: 

$$
\begin{array}{l} - \frac {1}{2} \boldsymbol {x} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} - \frac {1}{2} \boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {\mu} _ {1} + \boldsymbol {\mu} _ {1} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} + \ln (\pi_ {1}) \\ = - \frac {1}{2} \boldsymbol {x} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} - \frac {1}{2} \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {\mu} _ {2} + \boldsymbol {\mu} _ {2} ^ {\top} \boldsymbol {\Sigma} ^ {- 1} \boldsymbol {x} + \ln (\pi_ {2}). \end{array}
$$

Therefore, if we multiply the sides of equation by 2, we have: 

$$
\begin{array}{l} 2 \left(\boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {\top} \boldsymbol {x} \\ \quad + \left(\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}\right) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) \big) + 2 \ln (\frac {\pi_ {2}}{\pi_ {1}}) = 0, \end{array}\tag{20}
$$

which is the equation of a line in the form of $\pmb { a } ^ { \top } \pmb { x } + b = 0$ Therefore, if we consider Gaussian distributions for the two classes where the covariance matrices are assumed to be equal, the decision boundary of classification is a line. Because of linearity of the decision boundary which discriminates the two classes, this method is named linear discriminant analysis. 

For obtaining Eq. (20), we brought the expressions to the right side which was corresponding to the second class; therefore, if we use $\delta ( \pmb { x } ) : \bar { \mathbb { R } ^ { d } }  \bar { \mathbb { R } }$ as the left-hand-side expression (function) in Eq. (20): 

$$
\begin{array}{l} \delta (\boldsymbol {x}) := 2 \left(\boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {\top} \boldsymbol {x} \\ \qquad + \left(\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}\right) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) \big) + 2 \ln (\frac {\pi_ {2}}{\pi_ {1}}), \end{array}\tag{21}
$$

the class of an instance x is estimated as: 

$$
\widehat {\mathcal {C}} (x) = \left\{ \begin{array}{l l} 1, & \text { if } \delta (\boldsymbol {x}) <   0, \\ 2, & \text { if } \delta (\boldsymbol {x}) > 0. \end{array} \right.\tag{22}
$$

If the priors of two classes are equal, i.e., $\pi _ { 1 } = \pi _ { 2 }$ , the Eq. (20) becomes: 

$$
\begin{array}{c} 2 \left(\boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {\top} \boldsymbol {x} \\ + \left(\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}\right) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {1} - \boldsymbol {\mu} _ {2}) = 0, \end{array}\tag{23}
$$

whose left-hand-side expression can be considered as $\delta ( { \pmb x } )$ in Eq. (22). 

