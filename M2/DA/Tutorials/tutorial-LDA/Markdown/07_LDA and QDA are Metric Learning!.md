## 7. LDA and QDA are Metric Learning!

Recall Eq. (28) which is the scaled posterior for the QDA. First, assume that the covariance matrices are all equal (as we have in LDA) and they all are the identity matrix: 

$$
\boldsymbol {\Sigma} _ {1} = \dots = \boldsymbol {\Sigma} _ {| \mathcal {C} |} = \boldsymbol {I},\tag{37}
$$

which means that all the classes are assumed to be spherically distributed in the d dimensional space. After this assumption, the Eq. (28) becomes: 

$$
\delta_ {k} (\boldsymbol {x}) = - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) + \ln (\pi_ {k}),\tag{38}
$$

because $| I | = 1 , \ln ( 1 ) = 0$ , and $\pmb { I } ^ { - 1 } = \pmb { I }$ . If we assume that the priors are all equal, the term ln(π ) is constant and can be dropped: 

$$
\delta_ {k} (\boldsymbol {x}) = - \frac {1}{2} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) = - \frac {1}{2} d _ {k} ^ {2},\tag{39}
$$

where $d _ { k }$ is the Euclidean distance from the mean of the k-th class: 

$$
d _ {k} = \left\| \boldsymbol {x} - \boldsymbol {\mu} _ {k} \right\| _ {2} = \sqrt {\left(\boldsymbol {x} - \boldsymbol {\mu} _ {k}\right) ^ {\top} \left(\boldsymbol {x} - \boldsymbol {\mu} _ {k}\right)}.\tag{40}
$$

Thus, the QDA or LDA reduce to simple Euclidean distance from the means of classes if the covariance matrices are all identity matrix and the priors are equal. Simple distance from the mean of classes is one of the simplest classification methods where the used metric is Euclidean distance. 

![image](<Images/07_LDA_and_QDA_are_Metric_Learning_image_001.jpg>)



Figure 2. The QDA and LDA where the covariance matrices are identity matrix. For equal priors, the QDA and LDA reduce to simple classification using Euclidean distance from means of classes. Changing the prior modifies the location of decision boundary where even one point can be classified differently for different priors.


The Eq. (39) has a very interesting message. We know that in metric Multi-Dimensional Scaling (MDS) (Cox & Cox, 2000) and kernel Principal Component Analysis (PCA), we have (see (Ham et al., 2004) and Chapter 2 in (Strange & Zwiggelaar, 2014)): 

$$
\boldsymbol {K} = - \frac {1}{2} \boldsymbol {H} \boldsymbol {D} \boldsymbol {H},\tag{41}
$$

where $D \in \mathbb { R } ^ { n \times n }$ is the distance matrix whose elements are the distances between the data instances, $\ b { K } \in \mathbb { R } ^ { n \times n }$ is the kernel matrix over the data instances, $\mathbb { R } ^ { n \times n } \ni H : =$ $\pmb { I } - ( 1 / n ) \mathbf { 1 1 } ^ { \top }$ is the centering matrix, and $\mathbb { R } ^ { n } \ni \mathbf { 1 } : =$ $[ 1 , 1 , \ldots , 1 ] ^ { \top }$ . If the elements of the distance matrix D are obtained using Euclidean distance, the MDS is equivalent to Principal Component Analysis (PCA) (Jolliffe, 2011). 

Comparing Eqs. (39) and (41) shows an interesting connection between the posterior of a class in QDA and the kernel over the the data instances of the class. In this comparison, the Eq. (41) should be considered for a class and not the entire data, so $\pmb { K } \in \mathbb { R } ^ { n _ { k } \times n _ { k } }$ $D \in \mathbb { R } ^ { n _ { k } \times n _ { k } }$ , and $\pmb { H } \in \mathbb { R } ^ { n _ { k } \times n _ { k } }$ 

Now, consider the case where still the covariance matrices are all identity matrix but the priors are not equal. In this case, we have Eq. (38). If we take an exponential (inverse of logarithm) from this expression, the $\pi _ { k }$ becomes a scale factor (weight). This means that we still are using distance metric to measure the distance of an instance from the means of classes but we are scaling the distances by the priors of classes. If a class happens more, i.e., its prior is larger, it must have a larger posterior so we reduce the distance from the mean of its class. In other words, we move the decision boundary according to the prior of classes (see Fig. 2). 

As the next step, consider a more general case where the covariance matrices are not equal as we have in QDA. We apply Singular Value Decomposition (SVD) to the covariance matrix of the k-th class: 

$$
\pmb {\Sigma} _ {k} = \pmb {U} _ {k} \pmb {\Lambda} _ {k} \pmb {U} _ {k} ^ {\top},
$$

where the left and right matrices of singular vectors are equal because the covariance matrix is symmetric. Therefore: 

$$
\pmb {\Sigma} _ {k} ^ {- 1} = \pmb {U} _ {k} \pmb {\Lambda} _ {k} ^ {- 1} \pmb {U} _ {k} ^ {\top},
$$

where $\pmb { U } _ { k } ^ { - 1 } \ : = \ : \pmb { U } _ { k } ^ { \top }$ because it is an orthogonal matrix. Therefore, we can simplify the following term: 

$$
\begin{array}{r l} & (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Sigma} _ {k} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) \\ & = (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {U} _ {k} \boldsymbol {\Lambda} _ {k} ^ {- 1} \boldsymbol {U} _ {k} ^ {\top} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) \\ & = (\boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Lambda} _ {k} ^ {- 1} (\boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}). \end{array}
$$

As $\boldsymbol { \Lambda } _ { k } ^ { - 1 }$ is a diagonal matrix with non-negative elements (because it is covariance), we can decompose it as: 

$$
\boldsymbol {\Lambda} _ {k} ^ {- 1} = \boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} \boldsymbol {\Lambda} _ {k} ^ {- 1 / 2}.
$$

Therefore: 

$$
\begin{array}{r l} & (\boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Lambda} _ {k} ^ {- 1} (\boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}) \\ & = (\boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} \boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} (\boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}) \\ & \overset {(a)} {=} (\boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}) ^ {\top} \\ & (\boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {x} - \boldsymbol {\Lambda} _ {k} ^ {- 1 / 2} \boldsymbol {U} _ {k} ^ {\top} \boldsymbol {\mu} _ {k}), \end{array}
$$

where (a) is because $\boldsymbol { \Lambda } _ { k } ^ { - \top / 2 } = \boldsymbol { \Lambda } _ { k } ^ { - 1 / 2 }$ because it is diagonal. We define the following transformation: 

$$
\phi_ {k}: \pmb {x} \mapsto \pmb {\Lambda} _ {k} ^ {- 1 / 2} \pmb {U} _ {k} ^ {\top} \pmb {x},\tag{42}
$$

which also results in the transformation of the mean: $\phi _ { k } : $ $\pmb { \mu } \mapsto \mathbf { { A } } _ { k } ^ { - 1 / 2 } \pmb { U } _ { k } ^ { \top } \pmb { \mu }$ . Therefore, the Eq. (28) can be restated as: 

$$
\begin{array}{l} \delta_ {k} (\boldsymbol {x}) = - \frac {1}{2} \ln (| \boldsymbol {\Sigma} _ {k} |) \\ - \frac {1}{2} \left(\phi_ {k} (\boldsymbol {x}) - \phi_ {k} (\boldsymbol {\mu} _ {k})\right) ^ {\top} \left(\phi_ {k} (\boldsymbol {x}) - \phi_ {k} (\boldsymbol {\mu} _ {k})\right) + \ln (\pi_ {k}). \end{array}\tag{43}
$$

Ignoring the terms $- ( 1 / 2 ) \ln ( | \Sigma _ { k } | )$ and $\ln ( \pi _ { k } )$ , we can see that the transformation has changed the covariance matrix of the class to identity matrix. Therefore, the QDA (and also LDA) can be seen as simple comparison of distances from the means of classes after applying a transformation to the data of every class. In other words, we are learning the metric using the SVD of covariance matrix of every class. Thus, LDA and QDA can be seen as metric learning (Yang & Jin, 2006; Kulis, 2013) in a perspective. Note that in metric learning, a valid distance metric is defined as (Yang & Jin, 2006): 

$$
d _ {\boldsymbol {A}} ^ {2} (\boldsymbol {x}, \boldsymbol {\mu} _ {k}) := | | \boldsymbol {x} - \boldsymbol {\mu} _ {k} | | _ {\boldsymbol {A}} ^ {2} = (\boldsymbol {x} - \boldsymbol {\mu} _ {k}) ^ {\top} \boldsymbol {A} (\boldsymbol {x} - \boldsymbol {\mu} _ {k}),\tag{44}
$$

where A is a positive semi-definite matrix, i.e., $A \succeq 0$ In QDA, we are also using $( { \pmb x } - { \pmb \mu } _ { k } ) ^ { \top } \pmb { \Sigma } _ { k } ^ { - 1 } ( { \pmb x } - { \pmb \mu } _ { k } )$ . The covariance matrix is positive semi-definite according to the characteristics of covariance matrix. Moreover, according to characteristics of a positive semi-definite matrix, the inverse of a positive semi-definite matrix is positive semidefinite so $\bar { \boldsymbol { \Sigma } } _ { k } ^ { - 1 } \succeq 0$ . Therefore, QDA is using metric learning (and as will be discussed in next section, it can be seen as a manifold learning method, too). 

It is also noteworthy that the QDA and LDA can also be seen as Mahalanobis distance (McLachlan, 1999; De Maesschalck et al., 2000) which is also a metric: 

$$
d _ {M} ^ {2} (\boldsymbol {x}, \boldsymbol {\mu}) := | | \boldsymbol {x} - \boldsymbol {\mu} | | _ {M} ^ {2} = (\boldsymbol {x} - \boldsymbol {\mu}) ^ {\top} \boldsymbol {\Sigma} ^ {- 1} (\boldsymbol {x} - \boldsymbol {\mu}),\tag{45}
$$

where Σ is the covariance matrix of the cloud of data whose mean is $\pmb { \mu } .$ The intuition of Mahalanobis distance is that if we have several data clouds (e.g., classes), the distance from the class with larger variance should be scaled down because that class is taking more of the space so it is more probable to happen. The scaling down shows in the inverse of covariance matrix. Comparing $( { \pmb x } - { \pmb \mu } _ { k } ) ^ { \top } \pmb { \Sigma } _ { k } ^ { - 1 } ( { \pmb x } - { \pmb \mu } _ { k } )$ in QDA or LDA with Eq. (45) shows that QDA and LDA are sort of using Mahalanobis distance. 

