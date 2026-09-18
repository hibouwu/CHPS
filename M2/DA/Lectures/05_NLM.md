# [Data & Apprentissage] Introduction à la science des données et à l'apprentissage

Nicolas Vayatis 

Méthodes non linéaires : SVM, méthodes locales, ensembles 

Rappel
Modèle probabiliste des données de classification 

## Modèle probabiliste pour la classification supervisée

- $(X, Y)$ - couple de variables aléatoires de loi de probabilité inconnue $P$ 

- $X \in \mathcal{X}$ - observation sur un espace mesurable (e.g. $\mathbb{R}^d$ ) 

- $Y \in \{-1, +1\}$ - label/classe binaire (par simplicité) 

→ Description de la loi jointe $P = \mathcal{L}(X, Y)$ du couple aléatoire $(X, Y)$ à partir des lois conditionnelles? 

## Description de la loi jointe

① Approche générative : $\mathcal{L}(X, Y) = \mathcal{L}(Y) \otimes \mathcal{L}(X \mid Y)$ 

- Modèle de type mélange de paramètre : 

$$
p = \mathbb {P} \{Y = + 1 \} \in [ 0, 1 ]
$$

- Lois conditionnelles sur $\mathbb{R}^d$ : 

$$
P _ {+} = \mathcal {L} (X \mid Y = + 1) \quad \text { et } \quad P _ {-} = \mathcal {L} (X \mid Y = - 1)
$$

② Approche discriminative $\mathcal{L}(X,Y)=\mathcal{L}(X)\otimes\mathcal{L}(Y\mid X)$ 

- Loi marginale sur $\mathbb{R}^{d}: P_{X} = \mathcal{L}(X)$ 

• Meilleure prévision : 

$$
\eta (x) = \mathbb {P} \{Y = + 1 \mid X = x \}, \quad \forall x \in \mathbb {R} ^ {d}
$$

- Loi marginale (les "dP" désignent les densités des lois) : 

$$
d P _ {X} = p d P _ {+} + (1 - p) d P _ {-}
$$

- Probabilité a posteriori (fonction de régression) : 

$$
\forall x \in \mathcal {X}, \qquad \eta (x) = \frac {p d P _ {+}}{p d P _ {+} + (1 - p) d P _ {-}} (x)
$$

- Une remarque : 

$$
\eta (x) > \frac {1}{2} \quad \Leftrightarrow \quad p d P _ {+} (x) > (1 - p) d P _ {-} (x)
$$

Formalisation du problème de classification 

## Le problème de classification binaire

- Données disponibles : $(x_1, y_1), \ldots, (x_n, y_n)$ , $x_i \in \mathbb{R}^d$ , $y_i \in \{-1, +1\}$ 

- Problème : prédiction du label y connaissant x 

- On cherche : un classifieur $g$ : $\mathbb{R}^d \to \{-1, +1\}$ 

- Question : trouver un classifieur $g$ qui "généralise" bien. 

- Idée : on choisit $g$ qui "interprète" bien, mais pas trop! 

- Concrètement : souvent on cherche une fonction de décision $f: \mathbb{R}^{d} \to \mathbb{R}$ et on y associe le classifieur $g = \text{sgn}(f)$ 

## Critère d'évaluation : erreur d'un classifieur

- Etant donnée une observation $x$ , un classifieur $g$ réalise une prédiction $g(x)$ à comparer à la classe $y$ . 

Erreur du classifieur = Taux d'observations mal classées 

$$
\hat {L} _ {n} (g) = \frac {1}{n} \sum_ {i = 1} ^ {n} \mathbb {I} _ {[ g (x _ {i}) \neq y _ {i} ]} = \frac {\# \{i : g (x _ {i}) \neq y _ {i} \}}{n}
$$

Cette erreur s'appelle aussi erreur d'apprentissage. 

- Un classifieur $g$ "interprète" convenablement les données si son erreur d'apprentissage est faible. 

## En pratique : Stratégie du holdout

- On sépare les données disponibles en deux sous-groupes : 

- Base d'apprentissage : $(X_1, Y_1), \ldots, (X_n, Y_n)$ 

- Base de test: $(X_{n+1}, Y_{n+1}), \ldots, (X_{n+m}, Y_{n+m})$ 

- L'erreur de test $\hat{L}_{m}^{\prime}(g) = \frac{1}{m}\sum_{j=1}^{m}\mathbb{I}_{[g(X_{n+j})\neq Y_{n+j}]}$ est une estimation de $L(g)$ pour tout classifieur $g$ (on peut conditionner par rapport à la base d'apprentissage si $g$ résulte d'un apprentissage). 

- Meilleure pratique : la validation croisée pour rendre plus robuste l'estimateur de $L(g)$ 

## Limites des méthodes génératives

- Evoquées lors du dernier cours : analyse discriminante, régression logistique 

- Modèles statistiques paramétriques : "All models are wrong"... 

- Lourd a priori de modélisation : "... some are useful" 

- cadre gaussien 

- modèle linéaire 

- Curse of dimensionality (cf. Bellmann) 

## Algorithms de discrimination linéaire non-paramétrique

1 les populations sont linéairement séparables 

② les populations sont presque linéairement séparables 

③ les populations ne sont pas linéairement séparables 

## Séparabilité linéaire

![image](<Images/05_NLM/image_001.jpg>)



Scénario 1


![image](<Images/05_NLM/image_002.jpg>)



Scénario 2


- Forme des fonctions de décision : 

$$
f (x) = b + <   \beta , x >
$$

où $b \in \mathbb{R}$ , $\beta \in \mathbb{R}^d$ . 

- L'équation $f(x) = 0$ définit un hyperplan séparateur $H$ dans $\mathbb{R}^d$ 

• Classifieur associé : 

$$
\forall x \in \mathbb {R} ^ {d} \quad g _ {f} (x) = \left\{ \begin{array}{l l} + 1 & \text {si} f (x) > 0 \\ - 1 & \text {si} f (x) \leq 0 \end{array} \right.
$$

① $\beta^{*}=\frac{\beta}{\|\beta\|}$ est le vecteur normal à H 

② $\forall x_{0} \in H, <\beta, x_{0} > = -b$ 

③ la distance signée (éventuellement négative!) d'un point $x \in R^{d}$ à H est donnée par 

$$
d (x, H) = <   \beta^ {*}, x - x _ {0} > = \frac {1}{\| \beta \|} (b + <   \beta , x >)
$$

où $x_0 \in H$ 

![image](<Images/05_NLM/image_003.jpg>)


A separating hyperplane $(\boldsymbol{w}, b) \in \mathbb{R}^{n} \times \mathbb{R}$ for a 2D training set. 

Attention! ici $w = \beta$ ... 

Algorithme du perceptron (Rosenblatt, 1958) 

Perceptron - version simplifiée b = 0 

Génère une suite $\beta_{0},\ldots,\beta_{n}$ de valeurs pour $\beta$ 

① Initialisation - $\beta_{0} = 0$ 

② Etape i - on considère le couple $(x_{i}, y_{i})$ et on regarde s'il est correctement classé ou non 

$$
\beta_ {i} = \left\{ \begin{array}{l l} \beta_ {i - 1} & \text {si} y _ {i} \cdot <   \beta_ {i - 1}, x _ {i} > > 0 \\ \beta_ {i - 1} + y _ {i} x _ {i} & \text {si} y _ {i} \cdot <   \beta_ {i - 1}, x _ {i} > \leq 0 \end{array} \right.
$$

# Algorithme du perceptron général

## Perceptron - version générale

- Paramètres : 

• taux d'apprentissage η 

• rayon des observations $R = \max_{1 \leq i \leq n} \|x_i\|$ 

## - Algorithme :

① Initialisation - $\beta_{0}=0$ , $b_{0}=0$ 

② Etape i - si $(x_{i}, y_{i})$ est mal classé par l'hyperplan $(b_{i-1}, \beta_{i-1})$ , alors : 

$$
{\beta_ {i}} {= \beta_ {i - 1} + \eta y _ {i} x _ {i}}
$$

$$
{b _ {i}} {= b _ {i - 1} + \eta y _ {i} ^ {2} R ^ {2}}
$$

sin on $\beta_{i}=\beta_{i-1},\ b_{i}=b_{i-1}$ 

## Théorème de Novikoff

Si les populations sont linéairement séparables alors l'algorithme du perceptron converge en un nombre fini $T \leq n$ d'étapes où : 

$$
T \leq \frac {2 R ^ {2}}{M ^ {2}}
$$

avec $M = \min_{1 \leq i \leq n} \{ y_i d(x_i, H^*) \}$ pour un certain séparateur $H^*$ . 

- Défaut du perceptron : mauvaise généralisation 

- Vertu du perceptron : algorithme séquentiel (online) 

Scénario 1 - hyperplan à bonne 

généralisation 

Question : hyperplan se trouvant à distance maximale de chaque population ? 

![image](<Images/05_NLM/image_004.jpg>)


Problème d'optimisation 

$$
\max _ {\beta \in \mathbb {R} ^ {d}, b \in \mathbb {R}} M
$$

sous les contraintes : 

$$
\forall i = 1, \dots , n, \quad y _ {i} \cdot d (x _ {i}, H) \geq M
$$

On rappelle : 

$$
d (x _ {i}, H) = \frac {1}{\| \beta \|} (b + <   \beta , x _ {i} >)
$$

Contraintes : 

$$
\forall i = 1, \dots , n, \quad y _ {i} \cdot \frac {1}{\| \beta \|} (b + <   \beta , x _ {i} >) \geq M
$$

On peut très bien poser : $M = 1 / \|\beta\|$ 

Formulation équivalente 

$$
\min _ {\beta , b} \frac {1}{2} \| \beta \| ^ {2}
$$

sous les contraintes : 

$$
\forall i = 1, \dots , n, \quad y _ {i} \cdot (b + <   \beta , x _ {i} >) \geq 1
$$

![image](<Images/05_NLM/image_005.jpg>)


$$
\text { Scénario   2 - Variables   "ressorts" (suite) }
$$

On introduit $n$ variables supplémentaires ("slacks" ou "ressorts"): $\xi = (\xi_1, \ldots, \xi_n)$ avec $\xi_i \geq 0, \forall i$ 

Nouveau problème d'optimisation 

$$
\min _ {\beta , b, \xi} \frac {1}{2} \| \beta \| ^ {2}
$$

sous les contraintes : 

$$
\forall i = 1, \dots , n, y _ {i} \cdot (b + <   \beta , x _ {i} >) \geq 1 - \xi_ {i}
$$

$$
\xi_ {i} \geq 0
$$

$$
\sum_ {i = 1} ^ {n} \xi_ {i} \leq \Xi
$$

Formulation lagrangienne I 

$$
\min _ {\beta , b, \xi} \frac {1}{2} \| \beta \| ^ {2} + C \sum_ {i = 1} ^ {n} \xi_ {i}
$$

sous les contraintes : 

$$
\begin{array}{r l} \forall i = 1, \ldots , n, & \xi_ {i} \geq 0 \\ & \xi_ {i} \geq 1 - [ y _ {i} \cdot (b + <   \beta , x _ {i} >) ] \end{array}
$$

Formulation lagrangienne II
Multiplicateurs de Lagrange : $\alpha = (\alpha_{1}, \ldots, \alpha_{n})$ , $\mu = (\mu_{1}, \ldots, \mu_{n})$ Formulation lagrangienne II 

$$
\min _ {\beta , b, \xi} \frac {1}{2} \| \beta \| ^ {2} + C \sum_ {i = 1} ^ {n} \xi_ {i} - \sum_ {i = 1} ^ {n} \alpha_ {i} \left(y _ {i} \cdot (b + <   \beta , x _ {i} >) - (1 - \xi_ {i})\right) + \sum_ {i = 1} ^ {n} \mu_ {i} \xi_ {i}
$$

Conditions du premier ordre (gradient nul) 

$$
\beta = \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} x _ {i}
$$

$$
\sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} = 0
$$

$$
\forall i = 1, \ldots , n, \alpha_ {i} = C + \mu_ {i}
$$

Formulation duale 

$$
\max _ {\alpha} \sum_ {i = 1} ^ {n} \alpha_ {i} - \frac {1}{2} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \alpha_ {i} \alpha_ {j} y _ {i} y _ {j} <   x _ {i}, x _ {j} >
$$

sous les contraintes : 

$$
\begin{array}{r l} \forall i = 1, \ldots , n, & 0 \leq \alpha_ {i} \leq C \\ \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} & = 0 \end{array}
$$

On note $\hat{\alpha} = (\hat{\alpha}_1, \ldots, \hat{\alpha}_n)$ la solution de ce problème. 

## Conditions de Karush-Kuhn-Tucker

Conditions de Karush-Kuhn-Tucker 

$$
\begin{array}{r l} \forall i = 1, \ldots , n, & \alpha_ {i} (y _ {i} \cdot f (x _ {i}) - (1 - \xi_ {i})) = 0 \\ & y _ {i} \cdot f (x _ {i}) - (1 - \xi_ {i}) \geq 0 \\ & \alpha_ {i} + \mu_ {i} = C \\ & \mu_ {i} \xi_ {i} = 0 \\ & \beta = \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} x _ {i} \\ & \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} = 0 \end{array}
$$

Lien entre les coefficients et la position des observations 

- si $\hat{\alpha}_i = 0$ alors $y_i \cdot f(x_i) \geq 1 \Rightarrow$ le point $x_i$ est bien classé
car $\mu_i = C > 0$ et on a $\xi_i = 0$ 

- si $0 < \hat{\alpha}_i < C$ alors $y_i \cdot f(x_i) = 1 \Rightarrow$ le point $x_i$ est sur la frontière de la marge
car $\mu_i > 0$ et $\xi_i = 0$ 

- si $\hat{\alpha}_i = C$ alors $y_i \cdot f(x_i) \leq 1 \Rightarrow$ le point $x_i$ dépasse la frontière de la marge
car $\mu_i = 0$ et donc $\xi_i \geq 0$ 

Phénomène remarquable! 

En pratique, beaucoup de $\hat{\alpha}_i$ sont nuls! 

## Définition

Les $\hat{\alpha}_i \neq 0$ correspondent aux vecteurs de support. On note $I$ l'ensemble des indices parmi $\{1, \ldots, n\}$ correspondants. 

Représentation de la solution 

Fonction de décision : 

$$
\hat {f} (x) = \hat {b} + \sum_ {i \in I} \hat {\alpha} _ {i} y _ {i} <   x _ {i}, x >
$$

où : 

$$
\hat {\beta} = \sum_ {i \in I} \hat {\alpha} _ {i} y _ {i} x _ {i}, I = \{i: \hat {\alpha} _ {i} \neq 0 \}
$$

$$
\hat {b} = y _ {j} - \sum_ {i \in I} \hat {\alpha} _ {i} y _ {i} <   x _ {i}, x _ {j} >, \quad \text { pour   un   certain } j \in I
$$

## Canonical Optimal Hyperplane

![image](<Images/05_NLM/image_006.jpg>)



⇒ Représentation parcimonieuse ("sparse") des SVM


- La plupart des problèmes de classification relèvent de séparations non-linéaires 

- L'algorithme de construction de l'hyperplan à marges optimales ne fait intervenir les observations que sous la forme des produits scalaires $< x_i, x_j >$ pour tout $i, j$ 

- La fonction de décision dépend du produit scalaire entre le nouveau point $x$ et les vecteurs de support $x_i$ 

- Astuce du noyau ("kernel trick") : l'algorithme de construction de l'hyperplan à marges optimales ne dépend des observations qu'au travers des coefficients de la matrice de Gram 

$$
K = \big (<   x _ {i}, x _ {j} > \big) _ {1 \leq i, j \leq n}
$$

- Méthodes à noyaux : on remplace le produit scalaire canonique par un noyau positif 

$$
k: \mathcal {X} \times \mathcal {X} \to \mathbb {R}
$$

et alors $K$ devient la matrice des $k(x_{i},x_{j})$ . 

Formulation duale 

$$
\max _ {\alpha} \sum_ {i = 1} ^ {n} \alpha_ {i} - \frac {1}{2} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \alpha_ {i} \alpha_ {j} y _ {i} y _ {j} k (x _ {i}, x _ {j})
$$

sous les contraintes : 

$$
\begin{array}{r l} \forall i = 1, \ldots , n, & 0 \leq \alpha_ {i} \leq C \\ \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} & = 0 \end{array}
$$

Fonction de décision : 

$$
\hat {f} (x) = \hat {b} + \sum_ {i \in I} \hat {\alpha} _ {i} k (x _ {i}, x)
$$

avec / indices des vecteurs de support. 

- noyaux polynomiaux 

$$
\begin{array}{r l} {k _ {r} (x, x ^ {\prime})} & {= (<   x, x ^ {\prime} >) ^ {r}} \\ {k _ {r, c} (x, x ^ {\prime})} & {= (<   x, x ^ {\prime} > + c) ^ {r}} \end{array}
$$

- noyau à fonctions de base radiales gaussiennes (RBF) 

$$
k _ {\sigma} (x, x ^ {\prime}) = \exp \left(- \frac {\| x - x ^ {\prime} \| ^ {2}}{2 \sigma^ {2}}\right)
$$

- noyau sigmoïde (réseau de neurones) 

$$
k _ {\kappa , \theta} (x, x ^ {\prime}) = \tanh (\kappa <   x, x ^ {\prime} > + \theta)
$$

- Sélection d'un noyau 

- Réglage des paramètres : utilisation d'une base de validation 

- Mesures de performances : erreur sur la base de test 

- Comparaison à d'autres méthodes 

- Extensions : 

- problème de classification à plus de deux classes 

• cas de populations très disproportionnées 

Modèles non linéaires basés sur la localité 

## Other forms of regularization

- General idea : Regularized function estimation without global optimization 

- Two directions : 

- Local methods : nearest-neighbors and decision trees 

- Ensemble methods: bagging, boosting, random forests 

## Regularization without optimization The case of histograms

![image](<Images/05_NLM/image_007.jpg>)


![image](<Images/05_NLM/image_008.jpg>)


![image](<Images/05_NLM/image_009.jpg>)


![image](<Images/05_NLM/image_010.jpg>)



Distribution of the age of the passengers of the Titanic with bins varying from 1 year to 15 years


## Ingredients for that type of regularization

- Histograms use two general ideas of locality (bins) and averaging (piecewise constant function) 

- define local : which training data can be considered to be close to the point where a prediction has to be made? 

• averaging (or voting if discrete outcome) : take the average of the values over each bin 

- Regularization through hyperparameter selection : find the optimal bin size amounts to finding the right hypothesis class 

## From histograms to Machine Learning

- In the previous example, the objective was to estimate a density function from a sample drawn from this distribution (problem known in the literature as nonparametric density estimation or kernel density estimation) 

- Density estimation can be seen as an unsupervised learning problem 

- In the supervised setting, we establish the values of the function on every bin either by averaging (regression setup) or by voting (classification setup). The general terminology for averaging/voting is aggregating/combining. 

# Two popular types of local methods

- Nearest neighbors : local are the closest points 

- Partition-based rules (also called decision trees): local are the points within a cell from a partition of the input space only 

Works for classification, regression and other problems... but here we will focus on classification 

- Given : 

- Consider a sample of classification data 

$$
(X _ {1}, Y _ {1}) \dots (X _ {n}, Y _ {n})
$$

where $X_{i} \in R^{d}$ vector of independent variables, 

$Y_{i}\in \{1,\dots ,C\}$ the label 

- Want : 

• to predict the label y at any position x 

Local methods #1 : k-Nearest neighbors (k-NN) 

# k-Nearest Neighbor (1/4) Principle of the k-NN algorithm

## ① Compute distances

• Compute pairwise distances $d(x, X_{i})$ for all $i = 1, \ldots, n$ 

## ② Sort training data

- Sort the data points from the closest $X_{(1)}$ to the farthest $X_{(n)}$ (i.e. $d(x, X_{(1)}) \leq \ldots \leq d(x, X_{(n)})$ 

③ Prediction $\hat{h}(x,k)=$ Majority vote of the k-NN 

- Consider the labels $Y_{(1)}, \ldots, Y_{(k)}$ of the $k$ closest points to $x$ and take the majority vote 

$$
\hat {h} (x, k) = \arg \max _ {c} \{\sum_ {l = 1} ^ {k} \mathbb {I} \{Y _ {(l)} = c \} \}
$$

## k-Nearest Neighbor (2/4) Principle of the k-NN algorithm

## kNN Algorithm

0. Look at the data 

![image](<Images/05_NLM/image_011.jpg>)



Say you want to classify the grey point into a class. Here, there are three potential classes - lime green, green and orange.



1. Calculate distances


![image](<Images/05_NLM/image_012.jpg>)



Start by calculating the distances between the grey point and all other points.


## 2. Find neighbours

![image](<Images/05_NLM/image_013.jpg>)


Next, find the nearest neighbours by ranking points by increasing distance. The nearest neighbours (NNs) of the grey point are the ones closest in dataspace. 

## 3. Vote on labels

![image](<Images/05_NLM/image_014.jpg>)


Class wins the vote! 

to be of class 

Vote on the predicted class labels based on the classes of the k nearest neighbours. Here, the labels were predicted based on the k=3 nearest neighbours. 

Hyperparameters 

- Choice of a distance $d$ between points of $\mathbb{R}^d$ 

- Number k of Nearest Neighbors, estimated by cross-validation : 

![image](<Images/05_NLM/image_015.jpg>)


![image](<Images/05_NLM/image_016.jpg>)


![image](<Images/05_NLM/image_017.jpg>)


- Recall : classification error $L(h) = \mathbb{P}(Y \neq h(X))$ and $L^* = \inf L$ 

- Consistency result : 

$$
\mathbb {E} L \big (\hat {h} (\cdot , k _ {n}) \big) \to L ^ {*}
$$

under the condition: $k_{n} \rightarrow \infty$ and $k_{n}/n \rightarrow 0$ when $n \rightarrow \infty$ 

- No closed-form solution for optimal $k_{n}$ (in practice, we use cross-validation) 

- No theoretical clue on the choice of the distance (related to data representation and the physics of the problem) 

Local methods #2 : Partition-based (decision trees) 

Partition-based classifier (1/4) 

Computing the prediction for fixed partition
Denote the partition by $c = \bigcup_{j} \gamma_{j}$ with cells $\gamma_{j}$ 

① Find the cell $\gamma(x)$ where x falls 

② Consider the training data in the cell $\gamma(x)$ 

3 Prediction $\hat{h}(x,c)=$ Majority vote over the training data in cell $\gamma(x)$ 

![image](<Images/05_NLM/image_018.jpg>)


![image](<Images/05_NLM/image_019.jpg>)


## Partition-based classifier (2/4) Building data-driven partitions

- Start with all the training data and find a (simple) classifier which minimizes some cost function 

- Repeat the process with the subset of training data on each side of the frontier of the classifier $\longrightarrow$ this is called recursive partitioning 

![image](<Images/05_NLM/image_020.jpg>)



tree representation


recursive partitioning of the X-domain 

## Partition-based classifier (3/4) Hyperparameters

- Cost function optimized locally (at the cell level for the data within the cell) 

• Number of minimal points in a cell 

- Maximal depth of the tree or total number of cells estimated by pruning the tree - pruning amounts to explore the class of all subpartitions (subtrees) and optimize a penalized criterion of the form 

$$
\arg \min _ {c} \hat {L} _ {n} (h _ {c}) + \lambda | c |
$$

where $c \subset \hat{c}$ is the collection of subpartitions obtained from the learned partition by pruning from bottom to top 

![image](<Images/05_NLM/image_021.jpg>)


- Case of regular partitions with cells which are hypercubes of $\mathbb{R}^d$ with edges of length $\delta_n$ : 

$$
\mathbb {E} L (\hat {h} (\cdot , \delta_ {n})) \to L ^ {*}
$$

under the condition: $n\delta_{n}^{d} \rightarrow \infty$ and $\delta_{n} \rightarrow 0$ when $n \rightarrow \infty$ (need enough data points in every cell and cell diameter go to zero as sample size grows) 

- Case of data-driven partitions : VC and Rademacher theory applies 

## Take-home message on local methods

## Major limitations :

- The $k$ -Nearest Neighbor method requires to store all the training data in order to predict the label of new entries. 

- Decision trees are extremely unstable. 

- Both display prediction performance below state-of-the-art methods 

Virtue of decision trees : 

- Can handle missing/categorical data, scale change 

- Can be expressed in terms of logical rule $\longrightarrow$ explainable machine learning 

What can be saved from decision trees? 

Shallow and efficient Machine Learning algorithms : Ensemble methods 

1. Bagging and Random Forests 

2. Boosting 

# Motivation for ensembles Pointers to other fields

- Technology : the champions in data science competitions combine several methods to boost performance (e.g. BelKor team, winner of the Netflix challenge) 

- Decision theory : Social choice theory 

• Probability : Ergodic theorem 

• Nonparametric statistics : aggregation estimators 

# Ensemble methods Starting point

- Consider we already have a machine learning algorithm with reasonable performance that we want to improve, e.g. decision tree, k-NN, SVM, ... 

- The idea of the ensemble is to generate different functions from the same training data and the same hypothesis space 

- In the illustration coming next and most of the discussion, the basic hypothesis space is the one with decision trees obtained with orthogonal splits (such splits are called decision stumps). 

## Ensembles of decision trees General principle

- Generate a collection of weak predictors (ensemble) obtained with a basic Machine Learning algorithm (e.g. decision tree) 

- For every point $x$ , compute their individual predictions 

- Take an average or a majority vote of the individual predictions to determine the prediction of the ensemble 

![image](<Images/05_NLM/image_022.jpg>)


## Ensembles of decision trees Resulting classifier

![image](<Images/05_NLM/image_023.jpg>)


# Ensembles of decision trees Three popular methods

- Bagging (Breiman, 1996) 

• Random forests (Amit-Geman, 1997; Breiman, 2000) 

- Boosting (Freund-Schapire, 1996) 

Ensemble methods #1 : Bagging and Random Forests 

## Bagging and Random Forests What is their hypothesis space?

- Denote by $\mathcal{H}$ the base hypothesis space (for the not so brilliant algorithm we already have, e.g. decision trees) 

- Denote by $D_{n}$ the training data and assume that we can sample functions $\hat{h}_1, \ldots, \hat{h}_t$ (the ensemble) from $\mathcal{H}$ conditionally to $D_{n}$ 

- With an ensemble of $T$ functions, the output of bagging/random forests is the average of those "random" (generated based on the data) functions: 

$$
\hat {f} _ {T} = \frac {1}{T} \sum_ {t = 1} ^ {T} \hat {h} _ {t}
$$

- The hypothesis space for those methods is the linear span of the base hypothesis space $\mathcal{H}$ . This can be a huge space! 

- Bagging and random forests rely on bootstrap samples of the training data 

- They differ by some different specifications of the recursive partitioning procedure to build each tree (no pruning involved) 

## What is bootstrap in general?

<table><tr><td>Obs</td><td>X</td><td>Y</td></tr><tr><td>3</td><td>5.3</td><td>2.8</td></tr><tr><td>1</td><td>4.3</td><td>2.4</td></tr><tr><td>3</td><td>5.3</td><td>2.8</td></tr></table>

![image](<Images/05_NLM/image_024.jpg>)


<table><tr><td>Obs</td><td>X</td><td>Y</td></tr><tr><td>1</td><td>4.3</td><td>2.4</td></tr><tr><td>2</td><td>2.1</td><td>1.1</td></tr><tr><td>3</td><td>5.3</td><td>2.8</td></tr></table>


Original Data (Z) 


<table><tr><td>Obs</td><td>X</td><td>Y</td></tr><tr><td>2</td><td>2.1</td><td>1.1</td></tr><tr><td>3</td><td>5.3</td><td>2.8</td></tr><tr><td>1</td><td>4.3</td><td>2.4</td></tr></table>

<table><tr><td>Obs</td><td>X</td><td>Y</td></tr><tr><td>2</td><td>2.1</td><td>1.1</td></tr><tr><td>2</td><td>2.1</td><td>1.1</td></tr><tr><td>1</td><td>4.3</td><td>2.4</td></tr></table>

- Consistency result for some idealized version of bagging 

- Most important! Bagging can render inconsistent rules consistent! 

- Biau, Devroye and Lugosi (2008) have considered bagging applied to 1-NN, given that 1-NN is inconsistent in general classification scenarios (except zero-noise or pure random labels) 

- Bagging applied to 1-NN classifier is consistent under some reasonable conditions on the sampling process 

Ensemble methods #2 : Boosting 

## Historical perspective on Boosting

• Original paper : Freund, Y. and Schapire, R. E. (ICML, 1996). 

- Interpretation of the optimization problem solved as stochastic gradient descent : Friedman, J. H. (CSDA, 2002). 

- Wald Memorial lecture (IMS, 2000): Leo Breiman declares that "understanding Boosting is the most important problem in Machine Learning" 

- Proof of boosting consistency : Lugosi, G. and Vayatis, N. (Special issue with discussion of the Annals of Statistics, 2004). 

- Xgboost, a scalable implementation : Chen, T. and Guestrin, C. (ACM SIGKDD, 2016). 

- Input 

- Data sample $D_{n} = \{(X_{i}, Y_{i}) : i = 1, \dots, n\}$ with classification data $\{-1, +1\}$ 

- Base hypothesis class $\mathcal{H}$ of weak classifiers such as decision trees (assumed to be symmetric, i.e. $h \in \mathcal{H}$ iff $-h \in \mathcal{H}$ ) 

- Iterations $t = 1, \ldots, T$ . 

• Compute weights $w_{t} > 0$ and weak classifiers $\widehat{h}_{t} \in H$ 

- Output. 

- The Boosting classifier takes the sign of the following linear combination of weak classifiers: $\widehat{f}_n(x) = \sum_{t=1}^{T} w_t \widehat{h}_t(x)$ 

- Boosting distributions on the data : sequence of discrete probability distributions over $\{1, \ldots, n\}$ denoted by $\Pi_t$ , $t \geq 1$ 

- Weighted training error: for any weak classifier $h \in \mathcal{H}$ and for $t \geq 1$ 

$$
\widehat {\varepsilon} _ {t} (h) = \sum_ {i = 1} ^ {n} \Pi_ {t} (i) \mathbb {I} \{h (X _ {i}) \neq Y _ {i} \}
$$

Boosting (3/7) 

Original Algorithm : AdaBoost 

① Initialization. $\Pi_{1}$ is the uniform distribution on $\{1,\ldots,n\}$ 

② Boosting iterations. For $t = 1, \ldots, T$ , find the weak classifier such that : 

$$
\widehat {h} _ {t} = \underset {h \in \mathcal {H}} {\arg \min} \widehat {\varepsilon} _ {t} (h)
$$

then set $e_{t}=\widehat{\varepsilon}_{t}(\widehat{h}_{t})$ and take the weight to be 

$$
w _ {t} = \frac {1}{2} \log \left(\frac {1 - e _ {t}}{e _ {t}}\right)
$$

③ Boosting distribution update. For any $i = 1, \ldots, n$ , 

$$
\Pi_ {t + 1} (i) \propto \Pi_ {t} (i) \exp \left(- w _ {t} Y _ {i} \cdot \widehat {h} _ {t} (X _ {i})\right)
$$

![image](<Images/05_NLM/image_025.jpg>)


![image](<Images/05_NLM/image_026.jpg>)


![image](<Images/05_NLM/image_027.jpg>)


![image](<Images/05_NLM/image_028.jpg>)


![image](<Images/05_NLM/image_029.jpg>)


- Boosting can be interpreted as a functional gradient descent on the following functional : 

$$
\hat {A} _ {n} (f) = \frac {1}{n} \sum_ {i = 1} ^ {n} \exp \left(- Y _ {i} f (X _ {i})\right)
$$

where f is taken in a hypothesis space which is the linear span of 'simple' set H of classifiers. 

- Exercise : why ? 

Refer to : J. Friedman, ?Greedy Function Approximation : A Gradient Boosting Machine?, The Annals of Statistics, Vol. 29, No. 5, 2001. 

## Boosting (6/7)

## Hyperparameters for Gradient Boosting

- The number $T$ of iterations: the bigger, the higher the chance of overfitting. 

- The stepsize $\eta$ is fixed: decreasing learning rate tends to improve generalization performance. 

![image](<Images/05_NLM/image_030.jpg>)


Boosting (7/7)
A mystery not fully explained yet... 

The test error continues to drop along the iterations even though the training error is zero $\longrightarrow$ Regularization effect thanks to averaging ? ? 

![image](<Images/05_NLM/image_031.jpg>)


- Python : scikit-learn 

• R : 

- rpart : recursive partitioning 

- caret : classification and regression training (SVM, random forest...) 

- xgboost : extreme gradient boosting 

Les principes inférentiels 

- Une mesure d'erreur : 

$$
L (g) = \mathbb {P} \left\{Y \cdot g (X) <   0 \right\} = \mathbb {E} \left(\mathbb {I} _ {[ Y \cdot g (X) <   0 ]}\right)
$$

• Classifieur et erreur de Bayes : 

$$
\begin{array}{r l} {g ^ {*}} & {= \underset {g} {\arg \min} L (g) = \operatorname{sgn} \left(\eta - \frac {1}{2}\right)} \\ {L ^ {*}} & {= L (g ^ {*})} \end{array}
$$

• Critère empirique : 

$$
\hat {L} _ {n} (g) = \frac {1}{n} \sum_ {i = 1} ^ {n} \mathbb {I} _ {[ Y _ {i} \cdot g (X _ {i}) <   0 ]}
$$

## Minimisation du risque empirique (ERM)

La théorie de Vapnik ('95 → ) a permis de développer des stratégies consistantes pour la classification de données en grande dimension. 

## Inconvénients de l'ERM

- algorithmique : problème NP-difficile . 

- contrôle de la complexité : propriété de Glivenko-Cantelli pour éviter le surapprentissage (overfitting). 

## Mais :

Les méthodes efficaces construisent les estimateurs dans des classes massives! 

## Algorithms efficaces

## ① Support Vector Machines - Vapnik (1995)

- Kernel trick : envoyer les données dans un espace de Hilbert où les données soient (presque) linéairement séparables 

- Hyperplan à marge maximale : optimization convexe sous contraintes quadratiques 

## ② Boosting - Freund (1990) - Freund, Schapire (1996)

• on commence avec une classe H de classifieurs simples 

- puis on construit itérativement une combinaison linéaire de classifieurs simples qui fait décroître l'erreur empirique 

"Boosting is the best off-the-shelf classifier in the world" - Breiman, 1996. 

Caractéristique commune 

Si on fait abstraction : 

1 des intuitions géometriques 

② de la dynamique particulière de chaque algorithme, alors : 

Boosting et SVM peuvent s'envisager comme des : 

## procédures de minimisation d'un risque convexe pénalisé dans des espaces fonctionnels massifs.

Elles sont caractérisées par 

• des classes d'estimateurs différentes, 

• des risques différents, 

• des pénalités différentes. 

• Support Vector Machines - soit k un noyau positif 

$$
\mathcal {F} = \left\{f = \sum_ {i = 1} ^ {+ \infty} \alpha_ {i} k (x _ {i}, \cdot): \alpha_ {i} \in \mathbb {R}, x _ {i} \in \mathcal {X} \right\}
$$

- Boosting - soit $\mathcal{G}$ famille de classifieurs simples de VC dimension $V$ finie 

$$
\mathcal {F} = \left\{f = \sum_ {i = 1} ^ {+ \infty} w _ {i} g _ {i}: w _ {i} \in \mathbb {R}, g _ {i} \in \mathcal {G} \right\}
$$

Les deux algorithmes construisent des combinaisons linéaires de fonctions. 

Cas des SVM - Retour sur la formulation lagrangienne l 

On pose 

$$
f (x) = \sum_ {i = 1} ^ {n} \alpha_ {i} k (x _ {i}, x)
$$

$$
\| f \| _ {\mathcal {F}} = \sqrt {\sum_ {i , j} \alpha_ {i} \alpha_ {j} k (x _ {i} , x _ {j})}
$$

Formulation lagrangienne I 

$$
\min _ {f \in \mathcal {F}} \frac {1}{2} \| f \| _ {\mathcal {F}} ^ {2} + C \sum_ {i = 1} ^ {n} \xi_ {i}
$$

sous les contraintes : 

$$
\forall i = 1, \dots , n, \quad \xi_ {i} \geq \left(1 - y _ {i} \cdot f (x _ {i})\right) _ {+}
$$

On pose : $\varphi(x)=(1+x)_{+}$ "hinge loss" 

Minimisation d'un risque pénalisé 

$$
\min _ {f \in \mathcal {F}} \frac {1}{2} \| f \| _ {\mathcal {F}} ^ {2} + C \sum_ {i = 1} ^ {n} \varphi (- y _ {i} f (x _ {i}))
$$

## Commentaires :

- formulation importante pour la théorie statistique 

- moins commode pour l'optimisation que la formulation duale 

- $\|f\|_{\mathcal{F}}$ fournit une mesure de régularité de $f$ 

- Fonction de décision : 

$$
f: \mathcal {X} \to \mathbb {R}
$$

- Classifieur : 

$$
g (x) = g _ {f} (x) = \operatorname{sgn} (f (x)) \in \{- 1, + 1 \}
$$

- Critère naturel : 

$$
L (f) = \mathbb {P} \left\{Y \cdot f (X) <   0 \right\} = \mathbb {E} \left\{\mathbb {I} _ {[ Y \cdot f (X) <   0 ]} \right\}
$$

- Fonction de perte : $\varphi$ convexe, positive, telle que $\varphi(x) \geq \mathbb{I}_{\mathbb{R}_+}(x)$ 

• Critère pratique ( $\varphi$ -risque) : 

$$
\begin{array}{r l} A (f) & = \mathbb {E} \varphi (- Y f (X)) \\ & = \mathbb {E} \left[ \eta (X) \varphi (- f (X)) + (1 - \eta (X)) \varphi (f (X)) \right] \end{array}
$$

$\mathrm{o}\grave{\mathrm{u}}\eta (X) = \mathbb{P}\left\{Y = 1|X = x\right\}$ 

Question : minimiser A revient-il à minimiser L ? 

On a seulement que : $L(f) \leq A(f)...$ 

![image](<Images/05_NLM/image_032.jpg>)


Fonctions cibles 

- Minimiseur de la fonctionnelle $A$ noté $f^{*}$ 

• Minimum du $\varphi$ -risque : $A^{*} = \min_{f} A(f) = A(f^{*})$ 

- On peut montrer que $\operatorname{sgn}(f^{*}) = g^{*}$ le classifieur optimal 

- On peut également montrer que l'excès de risque en erreur de classification $L(f) - L^*$ est contrôlé par $A(f) - A^*$ 

- Exemples : 

• perte exponentielle (boosting) 

$$
f ^ {*} (x) = \frac {1}{2} \log \left(\frac {\eta (x)}{1 - \eta (x)}\right)
$$

- "hinge loss" (SVM) 

$$
f ^ {*} (x) = \operatorname{sgn} (\eta (x) - 1 / 2) = g ^ {*} (x)
$$

- Explainability 

- Reinforcement Learning 

- Adapting these concepts to other problems : 

- either in terms of objectives : such as preference learning, scoring, ranking, anomaly detection, novelty detection... 

- or in terms of learning setups : online learning, unsupervised learning, transfer learning, multitask learning, budgeted learning, active learning... 