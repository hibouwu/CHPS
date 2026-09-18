# Data & Apprentissage

> **日期核对：** 源文件名包含 2022，但 PDF 题面落款为 2023 年 3 月。保留文件名，按题面日期辨认考试；它与 2023 年 11 月的试卷不同。

Mars 2023 

Examen final 

Le sujet est imprim´e sur 3 pages – Dur´ee 2 heures 

LLes documents et notes de cours sont autoris´ees. L’utilisation de smartphones et acc`es `a des ressources documentaires sur internet est interdit. L’examen est `a r´ealiser individuellement et toute tentative de collaboration entre ´etudiants sera s´ev´erement sanctionn´ee. 

## Exercice 1. Restitution du cours

[10 points] 

R´epondre aux questions suivantes en maximum 5-10 lignes par question. 

1. Quels sont les liens entre machine learning et simulation num´erique ? 

2. Pr´eciser la dif´erence entre donn´ees de classification et probl`eme de classification. 

3. Discuter les choix possibles des crit`eres d’´evaluation d’une m´ethode d’apprentissage dans le cas de donn´ees de classification. 

4. Citer les trois grandes familles d’algorithmes d’apprentissage supervis´e en donnant deux exemples d’algorithmes par famille. 

5. En quoi consiste le compromis ”biais-variance” en apprentissage ? 

6. D´ecrire les principales caract´eristiques d’un algorithme d’apprentissage supervis´e de votre choix. Pr´eciser les param`etres choisis par le data scientist et les param`etres ”appris” par l’algorithme. 

7. Quels avantages pr´esentent les arbres de d´ecision sur la majorit´e des autres algorithmes ? 

8. Quel sch´ema d’optimisation g´en´erique est utilis´e dans la calibration des architectures de type Deep Learning? 

9. Peut-on r´esoudre le probl`eme de la calibration d’hyperparam`etres par une technique d’optimisation ? Fournir une r´eponse argument´ee en pr´ecisant la nature du probl`eme d’un point de vue num´erique, ses caract´eristiques g´en´erales et le type de solution qui pourrait ˆetre envisag´ee. 

10. Mentionner deux probl´ematiques concr`etes de mise en oeuvre dans les applications r´eelles. On prendra l’exemple de la d´etection d’anomalies (supervis´ee) sur une chaˆıne de production industrielle instrument´ee par un r´eseaux de capteurs mesurant des grandeurs physiques en continu (qualit´e des flux entrants et des flux sortants, vibrations, etc.). 

## Exercice 2. Regression and robust estimation

[4 points] 

a) Let P be a set of N 2-dimensional points, $p _ { i } = ( x _ { i } , y _ { i } )$ . Assume that we want to find the line that best fits the points of P. Present in detail how the Ordinary Least Squares (OLS) works when fitting a linear model by estimating its parameters. 

b) Considering the data of Table 1, apply the OLS by making the numerical calculations and report the fitted model and its Root Mean Squared Error (RMSE). 

<table><tr><td>i</td><td>1</td><td>2</td><td>3</td><td>4</td></tr><tr><td>xi</td><td>-0.5</td><td>0.3</td><td>0.7</td><td>1.5</td></tr><tr><td>yi</td><td>1.2</td><td>2.0</td><td>1.0</td><td>-1.0</td></tr></table>


Table 1 – Practical example : data points $P = \{ ( x _ { i } , y _ { i } ) , i = 1 . . . 4 \}$


c) Describe in detail the standard RANSAC method and algorithm for linear regression. Give insights about the sensitivity to its parameters. What is the difference to a typical bootstrapping estimation procedure ? 

d) Imagine that the data acquisition of the N data instances, $X = \{ x _ { 1 } , . . . , x _ { N } \}$ , has a variable quality $q _ { i }$ for each instance x . A domain expert, who is responsible for the data, provides you a data matrix $D \in \mathbb { R } ^ { N \times ( d + 1 ) }$ where the last column contains non-negative real values that correspond to the quality indicators, $q _ { i } \ge 0 , \forall i = 1 , . . . , N )$ 

Investigate the statistical properties of X by applying RANSAC for the robust estimation of $\delta = | | \mu - m | | _ { 2 } ,$ , where $\mu$ is the center of the instances in the set, and m is the medoid instance of the set, which has the shortest average distance to the other objects. 

## Exercice 3. Clustering

[4 points] 

a) Give a pseudocode for the k-means clustering algorithm and explain with simple arguments : why the procedure converges, and why multiple (re)runs are suggested. 

b) Suppose we initialize the clusters by assigning each of the N data instances to one of the k clusters uniformly at random. How does this compare qualitatively to the typical initialization strategy? Will it converge ; faster or slower ? 

c) Consider the 1D dataset $X \ = \ \{ 1 , 1 . 5 , 2 , 2 . 5 , 5 . 4 , 6 , 9 , 1 0 \}$ . Simulate all the steps of a 2-means solution using the k-farthest initialization, and fill Table 2 below. 

d) Given the clusters found in (c), summarize the dataset by providing two ‘typical’ data examples. Explain your answer and comment on how well each of them serves its role. 

e) Give three or more cluster linkage criteria that are used in hierarchical agglomerative clustering, and provide the formulas to compute them. In the following figures, draw the cluster hierarchy that would be computed by each of these criteria. 

<table><tr><td>step</td><td>centers</td><td><eq>x_{1}</eq></td><td><eq>x_{2}</eq></td><td><eq>x_{3}</eq></td><td><eq>x_{4}</eq></td><td><eq>x_{5}</eq></td><td><eq>x_{6}</eq></td><td><eq>x_{7}</eq></td><td><eq>x_{8}</eq></td><td>MSE</td></tr><tr><td>1</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>2</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>3</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>4</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>


Table 2 – k-means iterations. Compute the MSE only for the first and the final iterations.


![image](<Images/DataML-CHPS-2022-examen_image_001.jpg>)


![image](<Images/DataML-CHPS-2022-examen_image_002.jpg>)


![image](<Images/DataML-CHPS-2022-examen_image_003.jpg>)


## Exercice 4. Decision Trees

[2 points] 

a) Draw directly on the figure below, the way (roughly) a regression tree (RT) would approximate the data of the time-series, for depth = 1 and depth = 2. 

![image](<Images/DataML-CHPS-2022-examen_image_004.jpg>)



b) Draw on the right of the figure, the RT for depth = 2.


c) You trained your RT to approximate the function f(·) using the above dataset. Now, other clients ask you to directly predict for their data, because they believe they are of the same nature but a bit transformed. Specifically, let $f _ { \# } ( \cdot )$ be clients’ functions : 

client c1) $f _ { 1 } ( x ) \ = 3 f ( x )$ 

client c2) $f _ { 2 } ( 3 x ) = f ( x )$ ; 

client c3) $f _ { 3 } ( x ) = [ f _ { 1 } ( x ) + f _ { 2 } ( 3 x ) ] ^ { 2 }$ 

What would you answer? Is it feasible ? Which jobs would you accept and how would you manage in each of the cases $\it { ? }$ 