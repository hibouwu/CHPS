## 8. LDA and FDA

$$
8. \mathrm{LDA} \stackrel {?} {=} \mathrm{FDA}
$$

In the previous section, we saw that LDA and QDA can be seen as metric learning. We know that metric learning can be seen as a family of manifold learning methods. We briefly explain the reason of this assertion: As $A \succeq 0 .$ , we can say $\overset { \vartriangle } { \boldsymbol { A } } = \boldsymbol { U } \boldsymbol { U } ^ { \top } \succeq 0$ . Therefore, Eq. (44) becomes: 

$$
\begin{array}{c} | | \boldsymbol {x} - \boldsymbol {\mu} _ {k} | | _ {\boldsymbol {A}} ^ {2} = (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {U} \boldsymbol {U} ^ {\top} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) \\ = (\boldsymbol {U} ^ {\top} \boldsymbol {x} - \boldsymbol {U} ^ {\top} \boldsymbol {\mu} _ {k}) ^ {\top} (\boldsymbol {U} ^ {\top} \boldsymbol {x} - \boldsymbol {U} ^ {\top} \boldsymbol {\mu} _ {k}), \end{array}
$$

which means that metric learning can be seen as comparison of simple Euclidean distances after the transformation $\phi : \pmb { x } \mapsto \pmb { U } ^ { \top } \pmb { x }$ which is a projection into a subspace with projection matrix U. Thus, metric learning is a manifold learning approach. This gives a hint that the Fisher Discriminant Analysis (FDA) (Fisher, 1936; Welling, 2005), which is a manifold learning approach (Tharwat et al., 2017), might have a connection to LDA; especially, because the names FDA and LDA are often used interchangeably in the literature. Actually, other names of FDA are Fisher LDA (FLDA) and even LDA. 

We know that if we project (transform) the data of a class using a projection vector u $, \in \mathbb { R } ^ { p }$ to a $p$ dimensional subspace $( p \leq d )$ , i.e.: 

$$
\boldsymbol {x} \mapsto \boldsymbol {u} ^ {\top} \boldsymbol {x},\tag{46}
$$

for all data instances of the class, the mean and the covariance matrix of the class are transformed as: 

$$
\boldsymbol {\mu} \mapsto \boldsymbol {u} ^ {\top} \boldsymbol {\mu},\tag{47}
$$

$$
\boldsymbol {\Sigma} \mapsto \boldsymbol {u} ^ {\top} \boldsymbol {\Sigma} \boldsymbol {u},\tag{48}
$$

because of characteristics of mean and variance. 

The Fisher criterion (Xu & Lu, 2006) is the ratio of the between-class variance, $\sigma _ { b } ^ { 2 } .$ , and within-class variance, $\sigma _ { w } ^ { 2 }$ : 

$$
f := \frac {\sigma_ {b} ^ {2}}{\sigma_ {w} ^ {2}} = \frac {(\boldsymbol {u} ^ {\top} \boldsymbol {\mu} _ {2} - \boldsymbol {u} ^ {\top} \boldsymbol {\mu} _ {1}) ^ {2}}{\boldsymbol {u} ^ {\top} \boldsymbol {\Sigma} _ {2} \boldsymbol {u} + \boldsymbol {u} ^ {\top} \boldsymbol {\Sigma} _ {1} \boldsymbol {u}} = \frac {(\boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})) ^ {2}}{\boldsymbol {u} ^ {\top} (\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1}) \boldsymbol {u}}.\tag{49}
$$

The FDA maximizes the Fisher criterion: 

$$
\underset {\boldsymbol {u}} {\text { maximize }} \frac {\left(\boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {2}}{\boldsymbol {u} ^ {\top} (\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1})   \boldsymbol {u}},\tag{50}
$$

which can be restated as: 

$$
\begin{array}{l l} \underset {\boldsymbol {u}} {\text { maximize }} & \left(\boldsymbol {u} ^ {\top} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1})\right) ^ {2}, \\ \text { subject   to } & \boldsymbol {u} ^ {\top} (\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1})   \boldsymbol {u} = 1, \end{array}\tag{51}
$$

according to Rayleigh-Ritz quotient method (Croot, 2005). The Lagrangian (Boyd & Vandenberghe, 2004) is: 

$$
\mathcal {L} = \left(\boldsymbol {u} ^ {\top} \left(\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1}\right)\right) ^ {2} - \lambda \left(\boldsymbol {u} ^ {\top} \left(\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1}\right) \boldsymbol {u} - 1\right),
$$

where λ is the Lagrange multiplier. Equating the derivative of $\mathcal { L }$ to zero gives: 

$$
\begin{array}{l} \frac {\partial \mathcal {L}}{\partial \boldsymbol {u}} = 2 \left(\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1}\right) ^ {2} \boldsymbol {u} - 2 \lambda \left(\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1}\right) \boldsymbol {u} \stackrel {{\text { set }}} {{=}} \boldsymbol {0} \\ \implies \left(\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1}\right) ^ {2} \boldsymbol {u} = \lambda \left(\boldsymbol {\Sigma} _ {2} + \boldsymbol {\Sigma} _ {1}\right) \boldsymbol {u}, \end{array}
$$

which is a generalized eigenvalue problem $\left( ( \mu _ { 2 } \textrm { -- } \right)$ $\pmb { \mu } _ { 1 } ) ^ { 2 } , ( \pmb { \Sigma } _ { 2 } + \pmb { \Sigma } _ { 1 } ) \big )$ according to (Ghojogh et al., 2019b). The projection vector is the eigenvector of $( \pmb { \Sigma } _ { 2 } ~ +$ $\Sigma _ { 1 } ) ^ { - 1 } ( \pmb { \mu } _ { 2 } - \pmb { \mu } _ { 1 } ) ^ { 2 }$ ; therefore, we can say: 

$$
\pmb {u} \propto (\pmb {\Sigma} _ {2} + \pmb {\Sigma} _ {1}) ^ {- 1} (\pmb {\mu} _ {2} - \pmb {\mu} _ {1}) ^ {2}.
$$

In LDA, the equality of covariance matrices is assumed. Thus, according to Eq. (18), we can say: 

$$
\pmb {u} \propto (2 \pmb {\Sigma}) ^ {- 1} (\pmb {\mu} _ {2} - \pmb {\mu} _ {1}) ^ {2} \propto \pmb {\Sigma} ^ {- 1} (\pmb {\mu} _ {2} - \pmb {\mu} _ {1}) ^ {2}.\tag{52}
$$

According to Eq. (46), we have: 

$$
\boldsymbol {u} ^ {\top} \boldsymbol {x} \propto \left(\boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {\mu} _ {2} - \boldsymbol {\mu} _ {1}) ^ {2}\right) ^ {\top} \boldsymbol {x}.\tag{53}
$$

Comparing Eq. (53) with Eq. (23) shows that LDA and FDA are equivalent up to a scaling factor $( \mu _ { 1 } \textrm { -- }$ ${ \pmb \mu } _ { 2 } ) ^ { \top } { \pmb \Sigma } ^ { - 1 } ( { \pmb \mu } _ { 1 } - { \pmb \mu } _ { 2 } )$ (note that this term is multiplied as an exponential factor before taking logarithm to obtain Eq. (23), so this term a scaling factor). Hence, we can say: 

$$
\mathrm{LDA} \equiv \mathrm{FDA}.\tag{54}
$$

In other words, FDA projects into a subspace. On the other hand, according to Section 7, LDA can be seen as a metric learning with a subspace where the Euclidean distance is used after projecting onto that subspace. The two subspaces of FDA and LDA are the same subspace. It should be noted that in manifold (subspace) learning, the scale does not matter because all the distances scale similarly. Note that LDA assumes one (and not several) Gaussian for every class and so does the FDA. That is why FDA faces problem for multi-modal data (Sugiyama, 2007). 

