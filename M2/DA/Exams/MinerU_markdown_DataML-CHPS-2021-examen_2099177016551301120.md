# Data & Apprentissage

8 novembre 2021 

## Examen

Le sujet est imprim´e sur 4 pages – Dur´ee 2 heures 

Aucun document n’est autoris´e. L’utilisation de smartphones et l’acc`es `a des ressources documentaires sur internet sont rigoureusement interdits. Toute collaboration entre ´etudiants pendant l’´epreuve sera s´ev´erement sanctionn´ee. 

## Exercice 1. Restitution du cours

R´epondre aux questions suivantes en 5 lignes maximum par question. 

1. Expliquer la dif´erence entre donn´ees de classification et probl`eme de classification. 

2. Donner la d´efinition de la courbe ROC. Quel est son int´erˆet ? 

3. D´ecrire le mod`ele de r´egression logistique et expliquer comment l’utiliser pour un probl`eme de classification ? Pour quel autre probl`eme d’apprentissage ce mod`ele peut-il ˆetre utilis´e ? 

4. D´ecrire le principe des m´ethodes d’apprentissage dites locales. Donner un exemple en indiquant les hyperparam`etres de la m´ethode. 

5. D´ecrire le principe des m´ethodes d’apprentissage dites globales. Pourquoi utiliset-on parfois des pertes convexes en apprentissage ? Quels autres choix de pertes conduisent `a des m´ethodes pratiques ? 

6. Quels sont les termes d’erreur permettant de rendre compte du ph´enom`ene de surapprentissage (overfitting) ? Discuter l’impact du temps de calcul (`a ressources fix´ees) quand la taille d’´echantillon augmente ? 

7. Evoquer les enjeux et la probl´ematique sous-jacente `a la calibration des hyperparam`etres d’une m´ethode d’apprentissage. 

8. Donner deux exemples d’applications du machine learning en lien avec des sujets de simulation num´erique. 

Practical example : data points 

## Exercice 2. Regression

a) Let P be a set of N 2-dimensional points, $p _ { i } = ( x _ { i } , y _ { i } )$ . Assume that we want to find the line that best fits the points of P. Present in detail how the Ordinary Least Squares (OLS) works when fitting a linear model by estimating its parameters. 

b) Considering the data ofTable 2, apply the OLS by making the numerical calculations and report the fitted model and its Root Mean Squared Error (RMSE). c) You are asked 

<table><tr><td>i</td><td>1</td><td>2</td><td>3</td><td>4</td></tr><tr><td>xi</td><td>2.0</td><td>1.0</td><td>0.5</td><td>-0.5</td></tr><tr><td>yi</td><td>1.2</td><td>2</td><td>1</td><td>-0.7</td></tr></table>

$$
P = \{(x _ {i}, y _ {i}), i = 1... 4 \}
$$

![image](<Images/DataML-CHPS-2021-examen_image_001.jpg>)


to try more complex polynomial models for this dataset. Which ones would you check, and which one would be the most complex that is meaningful to try? 

d) Explain the principle of Ridge Regression (RR). 

e) For a linear regression problem, you are given $N { = } 5 0$ datapoints, each one described by d=200 features. Which regression method would you prefer ? If you were asked to use specifically OLS, describe one way or more in which you would proceed. 

## Exercice 3. Decision Trees

![image](<Images/DataML-CHPS-2021-examen_image_002.jpg>)


a) Draw directly on the above figure the way $( r o u g h l y )$ a regression tree (RT) approximates the data of the time-series, for $d e p t h = 1$ and $\mathop { d e p t h } = 2$ 

assignment to cluster 

b) Draw on the right to the figure, a (rough) RT with depth = 2. 

c) How would an ensemble of RTs (each tree using random subsets of the data to train with) approximate the region $x \in [ 1 , 2 . 5 ]$ of this dataset ? Make a drawing and explain. 

d) You have trained your $R T _ { i n i t i a l }$ to approximate the unknown function f(·) using the dataset of the figure. Then, your intention is to use it also for unseen data of the same nature, which however are a bit transformed. Specifically, let $f _ { 1 } ( \cdot ) , f _ { 2 } ( \cdot )$ and $f _ { 3 } ( \cdot )$ be the new functions that can be expressed with repect to f(·) : 

case d1) $f _ { 1 } ( 5 x ) = f ( x )$ 

case d2) $f _ { 2 } ( x ) \ = 5 f ( x )$ 

case d3) $f _ { 3 } ( x ) \ = ( f ( x ) ) ^ { 5 }$ 

Do you have to retrain from scratch your RT to apply it in these cases ? If yes, why; if no, what is the alernative approach you would follow for $( d 1 ) – ( d 3 ) ?$ 

e) What would be the difference in (d) if the $R T _ { i n i t i a l }$ is a single tree or an ensemble model of several trees ? 

## Exercice 4. Clustering

a) Consider a special case of the 2-means algorithm : a k-means with k = 2 where, after the centers’ initialization, only one of them (defined by the user) gets updated while the second one remains always fixed. Give a pseudocode of this particular algorithm. 

b) You have the dataset $X = \{ 1 0 , 1 5 , 2 0 , 2 5 , 5 5 , 6 0 , 9 0 , 1 0 0 \}$ . Starting with centers at positions 35 and 80 (fixed), compute numerically all the steps of the algorihm of (a) until convergence to solution cˆ. For each step, fill the following table with the positions of the centers, the cluster to which datapoints is assigned, and the Mean Squared Error (MSE). 

<table><tr><td colspan="10">assignment to cluster</td></tr><tr><td>step</td><td>centers</td><td><eq>x_{1}</eq></td><td><eq>x_{2}</eq></td><td><eq>x_{3}</eq></td><td><eq>x_{4}</eq></td><td><eq>x_{5}</eq></td><td><eq>x_{6}</eq></td><td><eq>x_{7}</eq></td><td><eq>x_{8}</eq></td></tr><tr><td>1</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>2</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>3</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>4</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>5</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>6</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

c) Given the centers of ${ \hat { c } } ,$ summarize the dataset by providing two ‘typical’ data examples. Compare how well each cluster is represented by its center, and why. 

d) Given the centers of cˆ, now apply the standard 2-means (no restriction to center updates) and fill in the table below. 

<table><tr><td>step</td><td>centers</td><td><eq>x_{1}</eq></td><td><eq>x_{2}</eq></td><td><eq>x_{3}</eq></td><td><eq>x_{4}</eq></td><td><eq>x_{5}</eq></td><td><eq>x_{6}</eq></td><td><eq>x_{7}</eq></td><td><eq>x_{8}</eq></td><td>MSE</td></tr><tr><td>1</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>2</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr><tr><td>3</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr></table>

Data/Apprentissage 3 

e) During k-means, explain how is it possible that one cluster becomes empty ? In such case, describe a couple of reasonable heuristics that would allow the process to continue without reducing the cluser number k. 