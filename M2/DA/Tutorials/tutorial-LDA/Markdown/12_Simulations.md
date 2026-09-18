## 12. Simulations

In this section, we report some simulations which make the concepts of tutorial clearer by illustration. 

## 12.1. Experiments with Equal Class Sample Sizes

We created a synthetic dataset of three classes each of which is a two dimensional Gaussian distribution. The means and covariance matrices of the three Gaussians from which the class samples were randomly drawn are: 

![image](<Images/12_Simulations_image_001.jpg>)



(a)


![image](<Images/12_Simulations_image_002.jpg>)



(b)


![image](<Images/12_Simulations_image_003.jpg>)



(c)


![image](<Images/12_Simulations_image_004.jpg>)



(d)


![image](<Images/12_Simulations_image_005.jpg>)



(e)


![image](<Images/12_Simulations_image_006.jpg>)



(f)


![image](<Images/12_Simulations_image_007.jpg>)



(g)



Figure 3. The synthetic dataset: (a) three classes each with size 200, (b) two classes each with size 200, (c) three classes each with size 10, (d) two classes each with size 10, (e) three classes with sizes 200, 100, and 10, (f) two classes with sizes 200 and 10, and (g) two classes with sizes 400 and 200 where the larger class has two modes.


$$
\boldsymbol {\mu} _ {1} = [ - 4, 4 ] ^ {\top}, \boldsymbol {\mu} _ {2} = [ 3, - 3 ] ^ {\top}, \boldsymbol {\mu} _ {1} = [ - 3, 3 ] ^ {\top},
$$

$$
\boldsymbol {\Sigma} _ {1} = \left[ \begin{array}{c c} 1 0 & 1 \\ 1 & 5 \end{array} \right], \boldsymbol {\Sigma} _ {2} = \left[ \begin{array}{c c} 3 & 0 \\ 0 & 4 \end{array} \right], \boldsymbol {\Sigma} _ {3} = \left[ \begin{array}{c c} 6 & 1. 5 \\ 1. 5 & 4 \end{array} \right].
$$

The three classes are shown in Fig. 3-a where each has sample size 200. Experiments were performed on the three classes. We also performed experiments on two of the three classes to test a binary classification. The two classes are shown in Fig. 3-b. The LDA, QDA, naive Bayes, and 

![image](<Images/12_Simulations_image_008.jpg>)



(a)


![image](<Images/12_Simulations_image_009.jpg>)



(b)


![image](<Images/12_Simulations_image_010.jpg>)



(c)


![image](<Images/12_Simulations_image_011.jpg>)



(d)


![image](<Images/12_Simulations_image_012.jpg>)



(e)


![image](<Images/12_Simulations_image_013.jpg>)



(f)


![image](<Images/12_Simulations_image_014.jpg>)



(g)


![image](<Images/12_Simulations_image_015.jpg>)



(h)



Figure 4. Experiments with equal class sample sizes: (a) LDA for two classes, (b) QDA for two classes, (c) Gaussian naive Bayes for two classes, (d) Bayes for two classes, (e) LDA for three classes, (f) QDA for three classes, (g) Gaussian naive Bayes for three classes, and (h) Bayes for three classes.


Bayes classifications of the two and three classes are shown in Fig. 4. For both binary and ternary classification with LDA and QDA, we used Eqs. (31) and (28), respectively, with Eq. (29). We also estimated the mean and covariance using Eqs. (33), (35), and (36). For Gaussian naive Bayes, we used Eqs. (62) and (63) and estimated the parameters using Eqs. (64) and (65). For Bayes classifier, we used Eq. (58) with Eq. (63) but we do not estimate the mean and variance; except, in order to use the exact likelihoods in Eq. (58), we use the exact mean and covariance matrices of the distributions which we sampled from. We, however, estimated the priors. The priors were estimated using Eq. (32) for all the classifiers. 

![image](<Images/12_Simulations_image_016.jpg>)



(a)


![image](<Images/12_Simulations_image_017.jpg>)



(b)


![image](<Images/12_Simulations_image_018.jpg>)



(c)


![image](<Images/12_Simulations_image_019.jpg>)



(d)


![image](<Images/12_Simulations_image_020.jpg>)



(e)


![image](<Images/12_Simulations_image_021.jpg>)



(f)


![image](<Images/12_Simulations_image_022.jpg>)



(g)


![image](<Images/12_Simulations_image_023.jpg>)



(h)



Figure 5. Experiments with small class sample sizes: (a) LDA for two classes, (b) QDA for two classes, (c) Gaussian naive Bayes for two classes, (d) Bayes for two classes, (e) LDA for three classes, (f) QDA for three classes, (g) Gaussian naive Bayes for three classes, and (h) Bayes for three classes.


As can be seen in Fig. 4, the space is partitioned into two/three parts and this validates the assertion that LDA and QDA can be considered as metric learning methods as discussed in Section 7. As expected, the boundaries of 

LDA and QDA are linear and curvy (quadratic), respectively. The results of QDA, Gaussian naive Bayes, and Bayes are very similar although they have slight differences. This is because the classes are already Gaussian so if the estimates of means and covariance matrices are accurate enough, QDA and Bayes are equivalent. The classes are Gaussians and the off-diagonal elements of covariance matrices are also small compared to the diagonal; therefore, naive Bayes is also behaving similarly. 

![image](<Images/12_Simulations_image_024.jpg>)



(a)


![image](<Images/12_Simulations_image_025.jpg>)



(b)


![image](<Images/12_Simulations_image_026.jpg>)



(c)


![image](<Images/12_Simulations_image_027.jpg>)



(d)


![image](<Images/12_Simulations_image_028.jpg>)



(e)


![image](<Images/12_Simulations_image_029.jpg>)



(f)


![image](<Images/12_Simulations_image_030.jpg>)



(g)


![image](<Images/12_Simulations_image_031.jpg>)



(h)



Figure 6. Experiments with different class sample sizes: (a) LDA for two classes, (b) QDA for two classes, (c) Gaussian naive Bayes for two classes, (d) Bayes for two classes, (e) LDA for three classes, (f) QDA for three classes, (g) Gaussian naive Bayes for three classes, and (h) Bayes for three classes.


## 12.2. Experiments with Small Class Sample Sizes

According to Monte-Carlo approximation (Robert & Casella, 2013), the estimates in Eqs. (33), (35), (64) and (65) are more accurate if the sample size goes to infinity, i.e., $n  \infty$ . Therefore, if the sample size is small, we expect mode difference between QDA and Bayes classifiers. We made a synthetic dataset with three or two classes with the same mentioned means and covariance matrices. The sample size of every class was 10. Figures 3-c and 3-d show these datasets. The results of LDA, QDA, Gaussian naive Bayes, and Bayes classifiers for this dataset are shown in Fig. 5. As can be seen, now, the results of QDA, Gaussian naive Bayes, and Bayes are different for the reason explained. 

![image](<Images/12_Simulations_image_032.jpg>)



(a)


![image](<Images/12_Simulations_image_033.jpg>)



(b)


![image](<Images/12_Simulations_image_034.jpg>)



(c)


![image](<Images/12_Simulations_image_035.jpg>)



(d)



Figure 7. Experiments with multi-modal data: (a) LDA, (b) QDA, (c) Gaussian naive Bayes, and (d) Bayes.


## 12.3. Experiments with Different Class Sample Sizes

According to Eq. (32) used in Eqs. (28), (31), (58), and (62), the prior of a class changes by the sample size of the class. In order to see the effect of sample size, we made a synthetic dataset with different class sizes, i.e., 200, 100, and 10, shown in Figs. 3-e, 3-f. We used the same mentioned means and covariance matrices. The results are shown in Fig. 6. As can be seen, the class with small sample size has covered a small portion of space in discrimination which is expected because its prior is small according to Eq. (32); therefore, its posterior is small. On the other hand, the class with large sample size has covered a larger portion because of a larger prior. 

## 12.4. Experiments with Multi-Modal Data

As mentioned in Section 8, LDA and QDA assume unimodal Gaussian distribution for every class and thus FDA or LDA faces problem for multi-modal data (Sugiyama, 2007). For testing this, we made a synthetic dataset with two classes, one with sample size 400 having two modes of Gaussians and the other with sample size 200 having one mode. We again used the same mentioned means and covariance matrices. The dataset is shown in Fig. 3-g. 

The results of the LDA, QDA, Gaussian naive Bayes, and Bayes classifiers for this dataset are shown in Fig. 7. The mean and covariance matrix of the larger class, although it has two modes, were estimated using Eqs. (33), (35), (64) and (65) in LDA, QDA, and Gaussian naive Bayes. However, for the likelihood used in Bayes classifier, i.e., in Eq. (58), we need to know the exact multi-modal distribution. Therefore, we fit a mixture of two Gaussians (Ghojogh et al., 2019a) to the data of the larger class: 

$$
\mathbb {P} (X = \boldsymbol {x} \mid \boldsymbol {x} \in \mathcal {C} _ {k}) = \sum_ {k = 1} ^ {2} w _ {k} f (\boldsymbol {x}; \boldsymbol {\mu} _ {k}, \boldsymbol {\Sigma} _ {k}),\tag{71}
$$

where $f ( \pmb { x } ; \pmb { \mu } _ { k } , \pmb { \Sigma } _ { k } )$ is $\operatorname { E q } .$ . (16) and we the fitted parame-

ters were: 

$$
\begin{array}{l} \boldsymbol {\mu} _ {1} = [ - 3. 8 8, 4 ] ^ {\top}, \boldsymbol {\mu} _ {2} = [ 3. 0 4, - 2. 9 2 ] ^ {\top}, \\ \boldsymbol {\Sigma} _ {1} = \left[ \begin{array}{c c} 9. 2 7 & 0. 7 9 \\ 0. 7 9 & 4. 8 2 \end{array} \right], \boldsymbol {\Sigma} _ {2} = \left[ \begin{array}{c c} 2. 8 7 & 0. 0 3 \\ 0. 0 3 & 3. 7 8 \end{array} \right], \\ w _ {1} = 0. 4 9, w _ {2} = 0. 5 0 2. \end{array}
$$

As Fig. 7 shows, LDA has not performed well enough as expected. The performance of QDA is more acceptable than LDA but still not good enough because QDA also assumes a uni-modal Gaussian for every class. The result of Gaussian naive Bayes is very different from the Bayes here because the Gaussian naive Bayes assumes unimodal Gaussian with diagonal covariance for every class. Finally, the Bayes has the best result as it takes into account the multi-modality of the data and it is optimum (Mitchell, 1997). 

