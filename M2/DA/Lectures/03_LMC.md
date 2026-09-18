M2 CHPS 

# [Data & Apprentissage] Introduction à la science des données et à l'apprentissage

Nicolas Vayatis 

Problème de classification, méthodes paramétriques 

## Données de classification - Exemples

## • Diagnostic médical :

• X : résultats des analyses médicales 

- $Y$ : diagnostic, 

- $Y = +1$ si le patient est en bonne santé, et $Y = -1$ sinon 

## - Risque de crédit :

• X : données socio-économiques d'un individu, 

- $Y$ : indicateur de défaut de paiement, 

- $Y = +1$ si l'emprunteur est fiable, et $Y = -1$ sinon 

## - Anti-spam :

• X : descripteur d'un email, 

- $Y$ : statut de l'email, 

- $Y = +1$ si le message est un spam, et $Y = -1$ sinon 

## Quelles décisions pour ces données ?

## 1 Classification

But : Prédire les nouveaux labels Y 

Satisfaits si l'erreur de classification est faible 

## ② Scoring

But : Ranger les X dans une liste 

Satisfaits si beaucoup de Y = +1 sont en tête de liste 

① Modèle probabiliste des données de classification 

② Cadre théorique du problème de classification 

③ Méthodes de classification paramétriques (linéaires) classiques 

① Analyse discriminante (LDA/QDA) 

② Analyse discriminante de Fischer (FDA) 

③ Régression logistique linéaire 

## 4 De la classification au scoring (ciblage) : la courbe ROC et l'aire AUC

5 Algorithme du perceptron : linéaire et non-paramétrique! 

## Modèle probabiliste des données de classification

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

- Meilleure prévision : 

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

Cadre théorique du problème de classification 

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

- Attention ! si on s'intéresse seulement à ce type d'erreur, on risque d'avoir des problèmes... 

![image](<Images/03_LMC/image_001.jpg>)


![image](<Images/03_LMC/image_002.jpg>)


## Overfitting en classification (suite)

Underfitting and Overfitting 

negative example positive example new patient 

## Calibration de la complexité

![image](<Images/03_LMC/image_003.jpg>)


## En pratique : Stratégie du holdout

- On sépare les données disponibles en deux sous-groupes : 

- Base d'apprentissage : $(X_1, Y_1), \ldots, (X_n, Y_n)$ 

- Base de test: $(X_{n+1}, Y_{n+1}), \ldots, (X_{n+m}, Y_{n+m})$ 

- L'erreur de test $\hat{L}_{m}^{\prime}(g) = \frac{1}{m}\sum_{j=1}^{m}\mathbb{I}_{[g(X_{n+j})\neq Y_{n+j}]}$ est une estimation de $L(g)$ pour tout classifieur $g$ (on peut conditionner par rapport à la base d'apprentissage si $g$ résulte d'un apprentissage). 

- Meilleure pratique : la validation croisée pour rendre plus robuste l'estimateur de $L(g)$ 

Méthode # 1 : Analyse discriminante linéaire (LDA) et quadratique (QDA) 

## Rappel : loi gaussienne multivariée

## Multivariate Gaussian models

• Similar to univariate case 

$$
\mathcal {N} (\underline {{{{x}}}}; \underline {{{{\mu}}}}, \Sigma) = \frac {1}{(2 \pi) ^ {d / 2}} | \Sigma | ^ {- 1 / 2} \exp \left\{- \frac {1}{2} (\underline {{{{x}}}} - \underline {{{{\mu}}}}) \Sigma^ {- 1} (\underline {{{{x}}}} - \underline {{{{\mu}}}}) ^ {T} \right\}
$$

![image](<Images/03_LMC/image_004.jpg>)


$$
\begin{array}{l} \mu = \text { length - d   row   vector } \\ \Sigma = \text { d   x   d   matrix } \end{array}
$$

$|\Sigma| = \text{matrix determinant}$ 

Maximum likelihood estimate: 

$$
\bar {\mu} = \frac {1}{m} \sum_ {j} x ^ {(j)}
$$

$$
\bar {\Sigma} = \frac {1}{m} \sum_ {j} (\underline {{x}} ^ {(j)} - \underline {{\mu}}) ^ {T} (\underline {{x}} ^ {(j)} - \underline {{\mu}})
$$

(average of dxd matrices) 

## Rappel : mélange gaussien en 2D

![image](<Images/03_LMC/image_005.jpg>)



b


![image](<Images/03_LMC/image_006.jpg>)


## Hypothèse : le modèle paramétrique de mélange gaussien

- $X \in \mathbb{R}^d$ et $Y \in \{1, \ldots, K\}$ 

- Forme paramétrique gaussienne pour la loi a posteriori 

$$
\mathbb {P} (X \mid Y = k) \sim \mathcal {N} (m _ {k}, \Sigma_ {k}), \quad \text { densité } f _ {k}
$$

- Paramètre de mélange $\pi_{k}$ pour la classe $Y = k$ 

- On exprime alors : 

$$
\eta_ {k} (x) = \mathbb {P} (Y = k \mid X = x) = \frac {\pi_ {k} f _ {k} (x)}{\sum_ {j = 1} ^ {K} \pi_ {j} f _ {j} (x)}
$$

## Analyse discriminante linéaire (LDA)

- On suppose que $\Sigma_{k} = \Sigma, \forall k$ 

- On exprime alors : 

$$
\begin{array}{r l} \log \left(\frac {\eta_ {k} (x)}{\eta_ {j} (x)}\right) & = \frac {\pi_ {k} f _ {k} (x)}{\pi_ {j} f _ {j} (x)} \\ & = \log \left(\frac {f _ {k} (x)}{f _ {j} (x)}\right) + \log \left(\frac {\pi_ {k}}{\pi_ {j}}\right) \\ & = - \frac {1}{2} (m _ {k} + m _ {j}) ^ {T} \Sigma^ {- 1} (m _ {k} + m _ {j}) \\ & \quad + \log \left(\frac {\pi_ {k}}{\pi_ {j}}\right) + x ^ {T} \Sigma^ {- 1} (m _ {k} - m _ {j}) \end{array}
$$

• Equation linéaire en x! 

## Analyse discriminante linéaire (suite)

![image](<Images/03_LMC/image_007.jpg>)


## Analyse discriminante quadratique (QDA)

- Cas où les matrices $\Sigma_{k}$ , $\forall k$ sont distinctes 

- On obtient dans ce cas des fonctions discriminantes : 

$$
\delta_ {k} (x) = - \frac {1}{2} (x - m _ {k}) ^ {T} \Sigma_ {k} ^ {- 1} (x - m _ {k})
$$

$$
+ \log (\pi_ {k}) - \frac {1}{2} \log d e t (\Sigma_ {k})
$$

- Séparatrices quadratiques en $x!$ 

• Estimation des matrices $\Sigma_{k}$ coûteuse en grande dimension 

- Alors : LDA avec termes de couplage ou QDA ? 

- Idée : régulariser la matrice par interpolation 

$$
\hat {\Sigma} _ {k} (\lambda) = \lambda \hat {\Sigma} _ {k} (\lambda) + (1 - \lambda) \hat {\Sigma}
$$

cf. Friedman (1989) 

- Variations autour de régularisation et parcimonie 

Méthode # 2 : Analyse discriminante de Fisher (FDA) 

## Principe de l'analyse discriminante de Fisher

- Hypothèse : On considère deux lois gaussiennes pour $\mathcal{L}(X \mid Y)$ 

- Heuristique : On considère le séparateur linéaire qui maximise la distance entre les centres des lois projetées normalisée par la variance totale des projections sur le vecteur normal au séparateur. 

![image](<Images/03_LMC/image_008.jpg>)


![image](<Images/03_LMC/image_009.jpg>)


Plus formellement : Notations pour i = 1, 2 

- Gaussiennes $\mathcal{N}(\mu_i, \Sigma_i)$ échantillonnées en données de classification binaires 

• Estimateurs empiriques des paramètres $\hat{\mu}_{i}$ , $\hat{\Sigma}_{i}$ 

- Centres projetés sur un vecteur $u \in \mathbb{R}^d: m_i(u) = u^T \hat{\mu}_i$ 

- Dispersion des observations projetées : 

$$
\hat {S} _ {i} ^ {2} (u) = \sum_ {j: Y _ {j} = i} \left(u ^ {T} X _ {j} - m _ {i} (u)\right) ^ {2}
$$

- Critère à maximiser pour $u \in \mathbb{R}^d$ : 

$$
J (u) = \frac {(m _ {1} (u) - m _ {2} (u)) ^ {2}}{\hat {S} _ {1} ^ {2} (u) + \hat {S} _ {2} ^ {2} (u)} = \frac {u ^ {T} S _ {B} u}{u ^ {T} S _ {W} u}
$$

où $S_{B}$ et $S_{W}$ peuvent être interprétées comme des matrices de dispersion inter et intra-classes. 

- La solution par lagrangien est obtenue via la résolution du problème aux valeurs propres : 

$$
S _ {B} u = \lambda S _ {W} u
$$

Si $S_{W}$ de rang plein, alors la solution est explicite : 

$$
u = S _ {W} ^ {- 1} \big (\hat {\mu} _ {1} - \hat {\mu} _ {2} \big)
$$

- A noter que la direction $u$ n'est pas liée à la direction obtenue pour la PCA. 

Méthode # 3 : Régression logistique linéaire 

- On $a: Y \in \{1, \ldots, K\}$ , $X \in \mathbb{R}^d$ 

- On pose $\eta_k(x) = \mathbb{P}\{Y = k \mid X = x\}$ pour $k \in \{1, \ldots, K\}$ 

- On suppose que $\forall k$ , qu'il existe $\theta_k \in \mathbb{R}^d$ tel que 

$$
\log \left(\frac {\eta_ {k} (x)}{\eta_ {K} (x)}\right) = \theta_ {k} ^ {T} x
$$

- Ou bien : 

$$
\eta_ {k} (x) = \frac {\exp (\theta_ {k} ^ {T} x)}{1 + \sum_ {j = 1} ^ {K - 1} \exp (\theta_ {j} ^ {T} x)}
$$

et $\theta_{K}=1$ . 

Fit d'un modèle de régression logistique 

- On note $\theta = (\theta_1, \ldots, \theta_{K-1})$ et $\eta_k(x) = p_k(x, \theta)$ 

- Log-vraisemblance 

$$
\ell (\theta) = \sum_ {i = 1} ^ {n} \log p _ {k} (X _ {i}, \theta)
$$

- Cas où $K = 2$ , $\theta \in \mathbb{R}^d$ , $p(x, \theta) = p_1(x, \theta)$ 

$$
\begin{array}{l} \ell (\theta) = \sum_ {i = 1} ^ {n} \big (Y _ {i} \log p (X _ {i}, \theta) + (1 - Y _ {i}) \log (1 - p (X _ {i}, \theta)) \big) \\ = \sum_ {i = 1} ^ {n} \big (Y _ {i} \theta^ {T} X _ {i} - \log (1 + \exp (\theta^ {T} X _ {i})) \big) \end{array}
$$

- Equation de score 

$$
\frac {\partial \ell}{\partial \theta} (\theta) = \sum_ {i = 1} ^ {n} X _ {i} \big (Y _ {i} - p (X _ {i}, \theta) \big) = 0
$$

- Matrice hessienne 

$$
H _ {\ell} (\theta) = - \sum_ {i = 1} ^ {n} X _ {i} X _ {i} ^ {T} p (X _ {i}, \theta) \big (1 - p (X _ {i}, \theta) \big)
$$

• Schéma itératif de Newton-Raphson 

$$
\theta_ {t + 1} = \theta_ {t} - (H _ {\ell} (\theta_ {t})) ^ {- 1} \frac {\partial \ell}{\partial \theta} (\theta_ {t})
$$

- Se ramène à un estimateur des moindres carrés pondéré... 

## Limites des méthodes génératives

- Modèles statistiques paramétriques : "All models are wrong"... 

- Lourd a priori de modélisation : "... some are useful" 

- cadre gaussien 

- modèle linéaire 

- Curse of dimensionality (cf. Bellmann) 

De la classification au scoring : Courbe ROC et AUC 

- Décomposition de l'erreur de classification 

$$
L (g) = \mathbb {P} \left\{g (X) = + 1, Y = - 1 \right\} + \mathbb {P} \left\{g (X) = - 1, Y = + 1 \right\}
$$

• Taux de faux positifs 

$$
\alpha (g) = \mathbb {P} \left\{g (X) = + 1 \mid Y = - 1 \right\}
$$

• Taux de vrais positifs 

$$
\beta (g) = \mathbb {P} \left\{g (X) = + 1 \mid Y = + 1 \right\}
$$

- On remarque que : 

$$
L (g) = \mathbb {P} \{Y \neq g (X) \} = (1 - p) \alpha (g) + p (1 - \beta (g))
$$

## Diagramme α-β

- Pour une proportion $p$ fixée, une erreur de classification fixée $L(g) = L$ , on a : 

$$
\beta = \left(\frac {1 - p}{p}\right) \alpha + 1 - \frac {L}{p}
$$

![image](<Images/03_LMC/image_010.jpg>)


- Sous l'observation $X$ , tester 

$$
H _ {0}: Y = - 1 \quad \text {   contre   } \quad H _ {1}: Y = + 1
$$

• Statistique de test optimale (Neyman-Pearson) 

$$
T ^ {*} (X) = \frac {1 - p}{p} \cdot \frac {\eta (X)}{1 - \eta (X)}
$$

• $\alpha = \text{Erreur de première espèce}$ 

- $\beta =$ Puissance du test 

## Classifieur de Neyman-Pearson

- Pour $\alpha$ fixé, la région de rejet est : 

$$
R _ {\alpha} ^ {*} = \left\{x: \eta (x) > Q ^ {-} (\eta , \alpha) \right\}
$$

$$
Q ^ {-} (\eta , \alpha) = (1 - \alpha) \text {-quantile de} \mathcal {L} (\eta (X) \mid Y = - 1)
$$

- Soit le classifieur : 

$$
g _ {\alpha} ^ {*} (x) = 2 \mathbb {I} \left\{x \in R _ {\alpha} ^ {*} \right\} - 1
$$

- En général : $L(g_{\alpha}^{*}) > L^{*}$ sauf si $Q^{-}(\eta, \alpha) = 1/2$ 

- Soit $\beta^{*}(\alpha) = \beta(g_{\alpha}^{*})$ 

![image](<Images/03_LMC/image_011.jpg>)


Notations
Performance d'une règle de scoring 

- Consider $s: \mathbb{R}^d \to \mathbb{R}$ a detector response (socring rule) 

- A hit corresponds to $Y = +1$ , an alarm to $\{s(X) \geq t\}$ 

• True positive rate and false positive rate : 

$$
\begin{array}{l l} \beta (s, t) = & \mathbb {P} \left\{s (X) \geq t \mid Y = + 1 \right\} \quad (\text {TPR}) \to \max \\ \alpha (s, t) = & \mathbb {P} \left\{s (X) \geq t \mid Y = - 1 \right\} \quad (\text {FPR}) \to \min \end{array}
$$

- Main point : trade-off required since 

$$
\begin{array}{l l l l} \beta (s, t) \to 1 & \text {but} & \alpha (s, t) \to 1 & \text {when} t \to - \infty \\ \alpha (s, t) \to 0 & \text {but} & \beta (s, t) \to 0 & \text {when} t \to + \infty \end{array}
$$

Courbes ROC idéales 

![image](<Images/03_LMC/image_012.jpg>)


![image](<Images/03_LMC/image_013.jpg>)


- Pour $s: \mathbb{R}^d \to \mathbb{R}$ règle fixée 

- Courbe ROC d'une règle de scoring s : 

$$
t \in \mathbb {R} \mapsto (\alpha_ {s} (t), \beta_ {s} (t))
$$

## Optimal elements for scoring

- $X \in \mathbb{R}^d$ - observation vector in a high dimensional space 

- $Y \in \{-1, +1\}$ - binary diagnosis (i.e. classification data) 

• Key theoretical quantity (posterior probability) 

$$
\eta (x) = \mathbb {P} \{Y = 1 \mid X = x \}, \quad \forall x \in \mathbb {R} ^ {d}
$$

• Optimal scoring rules : 

$\Rightarrow$ increasing transformations of $\eta$ 

Critère pratique - Aire sous la courbe ROC (AUC) 

- Pour toute règle de scoring $s$ , soit : 

$$
\begin{array}{l l} \text {AUC} (s) & = \int_ {0} ^ {1} \text {ROC} (s, \alpha) d \alpha \\ & = \mathbb {P} \{s (X) > s (X ^ {\prime}) | Y > Y ^ {\prime} \} \\ & \qquad + \frac {1}{2} \mathbb {P} \{s (X) = s (X ^ {\prime}) | Y > Y ^ {\prime} \} \end{array}
$$

où $(X, Y)$ , $(X', Y')$ i.i.d. 

- AUC maximale 

$$
\mathrm{AUC} ^ {*} = \mathrm{AUC} (\eta) = \frac {1}{2} + \frac {\mathbb {E} (| \eta (X) - \eta (X ^ {\prime}) |)}{4 p (1 - p)},
$$

- La convergence au sens de l'AUC correspond à la convergence $L_{1}$ des courbes ROC 

## - Curves :

- ROC curve 

• (Precision-Recall curve) 

• (Lift curve) 

## - Summaries :

• AUC (global measure) 

- Partial AUC 

(Dodd and Pepe '03) 

## - Local AUC

(Clémençon and Vayatis '07) 

![image](<Images/03_LMC/image_014.jpg>)



ROC curves.


## - Curves :

- ROC curve 

• (Precision-Recall curve) 

• (Lift curve) 

## - Summaries :

• AUC (global measure) 

• Partial AUC
(Dodd and Pepe '03) 

## - Local AUC

(Clémençon and Vayatis '07) 

![image](<Images/03_LMC/image_015.jpg>)



ROC curves.


## Performance measures for scoring

## - Curves :

- ROC curve 

• (Precision-Recall curve) 

• (Lift curve) 

## - Summaries :

• AUC (global measure) 

• Partial AUC
(Dodd and Pepe '03) 

- Local AUC
(Clémençon and Vayatis '07) 

![image](<Images/03_LMC/image_016.jpg>)



Partial AUC.


## Performance measures for scoring

## - Curves :

- ROC curve 

• (Precision-Recall curve) 

• (Lift curve) 

## - Summaries :

• AUC (global measure) 

• Partial AUC
(Dodd and Pepe '03) 

- Local AUC
(Clémençon and Vayatis '07) 

![image](<Images/03_LMC/image_017.jpg>)



Inconsistency of Partial AUC.


## Performance measures for scoring

## - Curves :

- ROC curve 

• (Precision-Recall curve) 

• (Lift curve) 

## - Summaries :

• AUC (global measure) 

• Partial AUC
(Dodd and Pepe '03) 

- Local AUC
(Clémençon and Vayatis '07) 

![image](<Images/03_LMC/image_018.jpg>)



Local AUC.


## Algorithms de discrimination linéaire non-paramétrique

1 les populations sont linéairement séparables 

② les populations sont presque linéairement séparables 

③ les populations ne sont pas linéairement séparables 

## Séparabilité linéaire

![image](<Images/03_LMC/image_019.jpg>)



Scénario 1


![image](<Images/03_LMC/image_020.jpg>)



Scénario 2


- Forme des fonctions de décision : 

$$
f (x) = b + <   \beta , x >
$$

où $b\in \mathbb{R},\beta \in \mathbb{R}^d$ 

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

où $x_{0} \in H$ 

![image](<Images/03_LMC/image_021.jpg>)


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

avec $M = \min_{1 \leq i \leq n} \{y_i d(x_i, H^*)\}$ pour un certain séparateur $H^*$ . 

- Défaut du perceptron : mauvaise généralisation 

- Vertu du perceptron : algorithme séquentiel (online) 

Scénario 1 - hyperplan à bonne 

généralisation 

Question : hyperplan se trouvant à distance maximale de chaque population ? 

![image](<Images/03_LMC/image_022.jpg>)


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

![image](<Images/03_LMC/image_023.jpg>)


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

![image](<Images/03_LMC/image_024.jpg>)



⇒ Représentation parcimonieuse ("sparse") des SVM


• Classification non supervisée (sans labels) 

- Autres algorithmes de classification, non-paramétriques, non-linéaires 

- Calibration de la complexité et régularisation de problèmes d'optimisation 