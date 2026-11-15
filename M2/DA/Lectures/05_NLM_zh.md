# 非线性方法：SVM、局部方法与集成：原文与中文逐段对照

> 正文按原课件顺序排列，英文或法语原文后紧跟中文；例子、练习、重复正文、公式、图表及文献均保留。图中文字保留原图语言。原课件错误与必要辨析以独立“译注”标明。

[原 PDF](05_NLM.pdf) · [原文转换稿](05_NLM.md) · [逐块对应清单](Translation-audit/2026-09-28-coverage.json) · [课程目录](../README.md)

**本讲目录**

- [非线性方法：SVM、局部方法与集成](#section-01)
- [回顾：分类数据的概率模型](#section-02)
- [分类问题的形式化](#section-03)
- [评价准则：分类器的误差](#section-04)
- [实践中的留出法](#section-05)
- [生成式方法的局限](#section-06)
- [非参数线性判别算法](#section-07)
- [感知机算法（Rosenblatt，1958）](#section-08)
- [一般感知机算法](#section-09)
- [Novikoff 定理](#section-10)
- [场景 1：具有良好泛化能力的超平面](#section-11)
- [Karush–Kuhn–Tucker 条件](#section-12)
- [规范最优超平面](#section-13)
- [基于局部性的非线性模型](#section-14)
- [无需优化的正则化：直方图](#section-15)
- [这类正则化的组成要素](#section-16)
- [从直方图到机器学习](#section-17)
- [两类常见的局部方法](#section-18)
- [局部方法 1：k 近邻（k-NN）](#section-19)
- [局部方法 2：基于划分的方法（决策树）](#section-20)
- [关于局部方法的要点](#section-21)
- [浅层且高效的机器学习算法：集成方法](#section-22)
- [集成方法：出发点](#section-23)
- [决策树集成：一般原理](#section-24)
- [决策树集成：得到的分类器](#section-25)
- [决策树集成：三种常见方法](#section-26)
- [集成方法 1：Bagging 与随机森林](#section-27)
- [一般而言，bootstrap 是什么？](#section-28)
- [集成方法 2：Boosting](#section-29)
- [推断原则](#section-30)
- [经验风险最小化（ERM）](#section-31)
- [高效算法](#section-32)

**重点定理与概念解释速查：**

- [从线性分类回顾到非线性扩展：为什么 SVM 只依赖样本内积](#reading-recap-linear-to-nonlinear)
- [核技巧（Kernel Trick）、正定核（Mercer 条件）与核 SVM 的超参数几何](#reading-kernel-svm-mercer)
- [局部正则化、$k$ 近邻（$k$-NN）与 Stone 普遍一致性定理（$k_n\to\infty, k_n/n\to 0$）](#reading-knn-stone-consistency)
- [基于划分的局部方法（决策树／CART）、不纯度准则、剪枝与超立方体划分一致性](#reading-decision-trees-cart-pruning)
- [Bootstrap 抽样概率、Bagging 与随机森林的方差分解及 1-NN Bagging 一致性定理](#reading-bagging-random-forests-variance)
- [Boosting 与 AdaBoost：指数损失函数空间梯度下降完整推导（课件练习解答）与间隔理论](#reading-boosting-adaboost-functional-gd)
- [再生核 Hilbert 空间（RKHS）惩罚风险、凸替代损失（$\varphi$-风险）与分类校准定理证明](#reading-convex-surrogates-calibration)

**[Data & Apprentissage] Introduction à la science des données et à l'apprentissage**

**数据科学与机器学习导论**

Nicolas Vayatis

<a id="section-01"></a>

Méthodes non linéaires : SVM, méthodes locales, ensembles

## 非线性方法：SVM、局部方法与集成

<a id="section-02"></a>

Rappel
Modèle probabiliste des données de classification

## 回顾：分类数据的概率模型

**Modèle probabiliste pour la classification supervisée**

### 监督分类的概率模型

- $(X, Y)$ - couple de variables aléatoires de loi de probabilité inconnue $P$

  $(X, Y)$：一对概率分布 $P$ 未知的随机变量。
- $X \in \mathcal{X}$ - observation sur un espace mesurable (e.g. $\mathbb{R}^d$ )

  $X \in \mathcal{X}$：可测空间上的观测，例如 $\mathbb{R}^d$。
- $Y \in \{-1, +1\}$ - label/classe binaire (par simplicité)

  $Y \in \{-1, +1\}$：二元标签／类别（为简单起见）。

→ Description de la loi jointe $P = \mathcal{L}(X, Y)$ du couple aléatoire $(X, Y)$ à partir des lois conditionnelles?

→ 如何从条件分布描述随机变量对 $(X, Y)$ 的联合分布 $P = \mathcal{L}(X, Y)$？

**Description de la loi jointe**

### 联合分布的描述

1. Approche générative : $\mathcal{L}(X, Y) = \mathcal{L}(Y) \otimes \mathcal{L}(X \mid Y)$

   生成式方法：$\mathcal{L}(X, Y) = \mathcal{L}(Y) \otimes \mathcal{L}(X \mid Y)$。
- Modèle de type mélange de paramètre :

  混合模型，其参数为：

$$
p = \mathbb {P} \{Y = + 1 \} \in [ 0, 1 ]
$$

- Lois conditionnelles sur $\mathbb{R}^d$ :

  $\mathbb{R}^d$ 上的条件分布：

$$
P _ {+} = \mathcal {L} (X \mid Y = + 1) \quad \text{且} \quad P _ {-} = \mathcal {L} (X \mid Y = - 1)
$$

2. Approche discriminative $\mathcal{L}(X,Y)=\mathcal{L}(X)\otimes\mathcal{L}(Y\mid X)$

   判别式方法：$\mathcal{L}(X,Y)=\mathcal{L}(X)\otimes\mathcal{L}(Y\mid X)$。
- Loi marginale sur $\mathbb{R}^{d}: P_{X} = \mathcal{L}(X)$

  $\mathbb{R}^{d}: P_{X} = \mathcal{L}(X)$ 上的边际分布。
- Meilleure prévision :

  最佳预测：

$$
\eta (x) = \mathbb {P} \{Y = + 1 \mid X = x \}, \quad \forall x \in \mathbb {R} ^ {d}
$$

- Loi marginale (les "dP" désignent les densités des lois) :

  边际分布（“dP”表示分布的密度）：

$$
d P _ {X} = p d P _ {+} + (1 - p) d P _ {-}
$$

- Probabilité a posteriori (fonction de régression) :

  后验概率（回归函数）：

$$
\forall x \in \mathcal {X}, \qquad \eta (x) = \frac {p d P _ {+}}{p d P _ {+} + (1 - p) d P _ {-}} (x)
$$

- Une remarque :

  一个备注：

$$
\eta (x) > \frac {1}{2} \quad \Leftrightarrow \quad p d P _ {+} (x) > (1 - p) d P _ {-} (x)
$$

<a id="section-03"></a>

Formalisation du problème de classification

## 分类问题的形式化

**Le problème de classification binaire**

### 二分类问题

- Données disponibles : $(x_1, y_1), \ldots, (x_n, y_n)$ , $x_i \in \mathbb{R}^d$ , $y_i \in \{-1, +1\}$

  可用数据：$(x_1, y_1), \ldots, (x_n, y_n)$，$x_i \in \mathbb{R}^d$，$y_i \in \{-1, +1\}$。
- Problème : prédiction du label y connaissant x

  问题：已知 x，预测标签 y。
- On cherche : un classifieur $g$ : $\mathbb{R}^d \to \{-1, +1\}$

  要寻找：一个分类器 $g$：$\mathbb{R}^d \to \{-1, +1\}$。
- Question : trouver un classifieur $g$ qui "généralise" bien.

  问题：找到一个能够良好“泛化”的分类器 $g$。
- Idée : on choisit $g$ qui "interprète" bien, mais pas trop!

  思路：选择一个能够很好地“解释”数据、但又不过度解释的 $g$！
- Concrètement : souvent on cherche une fonction de décision $f: \mathbb{R}^{d} \to \mathbb{R}$ et on y associe le classifieur $g = \text{sgn}(f)$

  具体而言：通常先寻找决策函数 $f: \mathbb{R}^{d} \to \mathbb{R}$，再将其与分类器 $g = \text{sgn}(f)$ 对应。

<a id="section-04"></a>

**Critère d'évaluation : erreur d'un classifieur**

## 评价准则：分类器的误差

- Etant donnée une observation $x$ , un classifieur $g$ réalise une prédiction $g(x)$ à comparer à la classe $y$ .

  给定一个观测 $x$，分类器 $g$ 作出预测 $g(x)$，将其与类别 $y$ 比较。

Erreur du classifieur = Taux d'observations mal classées

分类器的误差 = 被错误分类的观测所占比例。

$$
\hat {L} _ {n} (g) = \frac {1}{n} \sum_ {i = 1} ^ {n} \mathbb {I} _ {[ g (x _ {i}) \neq y _ {i} ]} = \frac {\# \{i : g (x _ {i}) \neq y _ {i} \}}{n}
$$

Cette erreur s'appelle aussi erreur d'apprentissage.

这个误差也称为训练误差。

- Un classifieur $g$ "interprète" convenablement les données si son erreur d'apprentissage est faible.

  如果分类器 $g$ 的训练误差低，就说它能够恰当地“解释”数据。

<a id="section-05"></a>

**En pratique : Stratégie du holdout**

## 实践中的留出法

- On sépare les données disponibles en deux sous-groupes :

  将可用数据分为两个子集：
- Base d'apprentissage : $(X_1, Y_1), \ldots, (X_n, Y_n)$

  训练集：$(X_1, Y_1), \ldots, (X_n, Y_n)$。
- Base de test: $(X_{n+1}, Y_{n+1}), \ldots, (X_{n+m}, Y_{n+m})$

  测试集：$(X_{n+1}, Y_{n+1}), \ldots, (X_{n+m}, Y_{n+m})$。
- L'erreur de test $\hat{L}_{m}^{\prime}(g) = \frac{1}{m}\sum_{j=1}^{m}\mathbb{I}_{[g(X_{n+j})\neq Y_{n+j}]}$ est une estimation de $L(g)$ pour tout classifieur $g$ (on peut conditionner par rapport à la base d'apprentissage si $g$ résulte d'un apprentissage).

  对任意分类器 $g$，测试误差 $\hat{L}_{m}^{\prime}(g) = \frac{1}{m}\sum_{j=1}^{m}\mathbb{I}_{[g(X_{n+j})\neq Y_{n+j}]}$ 是 $L(g)$ 的估计量（如果 $g$ 是学习得到的，可以对训练集取条件）。
- Meilleure pratique : la validation croisée pour rendre plus robuste l'estimateur de $L(g)$

  更好的实践：使用交叉验证，使 $L(g)$ 的估计更稳健。

<a id="section-06"></a>

**Limites des méthodes génératives**

## 生成式方法的局限

- Evoquées lors du dernier cours : analyse discriminante, régression logistique

  上一讲提到的方法：判别分析、逻辑回归。
- Modèles statistiques paramétriques : "All models are wrong"...

  参数统计模型：“所有模型都是错的”……
- Lourd a priori de modélisation : "... some are useful"

  很强的建模先验：“……但有些模型是有用的”。
- cadre gaussien

  高斯框架。
- modèle linéaire

  线性模型。
- Curse of dimensionality (cf. Bellmann)

  维数灾难（参见 Bellman）。

<a id="section-07"></a>

**Algorithms de discrimination linéaire non-paramétrique**

## 非参数线性判别算法

1. 1 les populations sont linéairement séparables

   两个群体线性可分。
2. les populations sont presque linéairement séparables

   两个群体近似线性可分。
3. les populations ne sont pas linéairement séparables

   两个群体不能线性分离。

**Séparabilité linéaire**

### 线性可分性

![image](<Images/05_NLM/image_001.jpg>)

Scénario 1

场景 1

![image](<Images/05_NLM/image_002.jpg>)

Scénario 2

场景 2

- Forme des fonctions de décision :

  决策函数的形式：

$$
f (x) = b + <   \beta , x >
$$

où $b \in \mathbb{R}$ , $\beta \in \mathbb{R}^d$ .

其中 $b \in \mathbb{R}$，$\beta \in \mathbb{R}^d$。

- L'équation $f(x) = 0$ définit un hyperplan séparateur $H$ dans $\mathbb{R}^d$

  方程 $f(x) = 0$ 在 $\mathbb{R}^d$ 中定义一个分隔超平面 $H$。
- Classifieur associé :

  对应的分类器：

$$
\forall x \in \mathbb {R} ^ {d} \quad g _ {f} (x) = \left\{ \begin{array}{l l} + 1 & \text{若} f (x) > 0 \\ - 1 & \text{若} f (x) \leq 0 \end{array} \right.
$$

1. $\beta^{*}=\frac{\beta}{\|\beta\|}$ est le vecteur normal à H

   $\beta^{*}=\frac{\beta}{\|\beta\|}$ 是 H 的法向量。

② $\forall x_{0} \in H, <\beta, x_{0} > = -b$

3. la distance signée (éventuellement négative!) d'un point $x \in R^{d}$ à H est donnée par

   点 $x \in R^{d}$ 到 H 的有符号距离（可以为负！）为

$$
d (x, H) = <   \beta^ {*}, x - x _ {0} > = \frac {1}{\| \beta \|} (b + <   \beta , x >)
$$

où $x_0 \in H$

其中 $x_0 \in H$。

![image](<Images/05_NLM/image_003.jpg>)

A separating hyperplane $(\boldsymbol{w}, b) \in \mathbb{R}^{n} \times \mathbb{R}$ for a 2D training set.

二维训练集的分隔超平面 $(\boldsymbol{w}, b) \in \mathbb{R}^{n} \times \mathbb{R}$。

Attention! ici $w = \beta$ ...

注意！这里 $w = \beta$……

<a id="section-08"></a>

Algorithme du perceptron (Rosenblatt, 1958)

## 感知机算法（Rosenblatt，1958）

Perceptron - version simplifiée b = 0

### 简化版本：b = 0

Génère une suite $\beta_{0},\ldots,\beta_{n}$ de valeurs pour $\beta$

生成参数 $\beta$ 的取值序列 $\beta_{0},\ldots,\beta_{n}$。

1. Initialisation - $\beta_{0} = 0$

   初始化：$\beta_{0} = 0$。
2. Etape i - on considère le couple $(x_{i}, y_{i})$ et on regarde s'il est correctement classé ou non

   第 i 步：考虑数据对 $(x_{i}, y_{i})$，检查它是否被正确分类。

$$
\beta_ {i} = \left\{ \begin{array}{l l} \beta_ {i - 1} & \text{若} y _ {i} \cdot <   \beta_ {i - 1}, x _ {i} > > 0 \\ \beta_ {i - 1} + y _ {i} x _ {i} & \text{若} y _ {i} \cdot <   \beta_ {i - 1}, x _ {i} > \leq 0 \end{array} \right.
$$

<a id="section-09"></a>

**Algorithme du perceptron général**

## 一般感知机算法

**Perceptron - version générale**

### 感知机：一般版本

- Paramètres :

  参数：
- taux d'apprentissage η

  学习率 η。
- rayon des observations $R = \max_{1 \leq i \leq n} \|x_i\|$

  观测的半径 $R = \max_{1 \leq i \leq n} \|x_i\|$。

**- Algorithme :**

### 算法

1. Initialisation - $\beta_{0}=0$ , $b_{0}=0$

   初始化：$\beta_{0}=0$，$b_{0}=0$。
2. Etape i - si $(x_{i}, y_{i})$ est mal classé par l'hyperplan $(b_{i-1}, \beta_{i-1})$ , alors :

   第 i 步：如果 $(x_{i}, y_{i})$ 被超平面 $(b_{i-1}, \beta_{i-1})$ 错误分类，则：

$$
{\beta_ {i}} {= \beta_ {i - 1} + \eta y _ {i} x _ {i}}
$$

$$
{b _ {i}} {= b _ {i - 1} + \eta y _ {i} ^ {2} R ^ {2}}
$$

> **译注：** 原课件截距更新含 $y_i^2$，在标签为 $\pm1$ 时会丢失符号；按增广向量 $(x_i,R)$ 的约定，应为 $b_i=b_{i-1}+\eta y_iR^2$。

sin on $\beta_{i}=\beta_{i-1},\ b_{i}=b_{i-1}$

否则 $\beta_{i}=\beta_{i-1},\ b_{i}=b_{i-1}$。

<a id="section-10"></a>

**Théorème de Novikoff**

## Novikoff 定理

Si les populations sont linéairement séparables alors l'algorithme du perceptron converge en un nombre fini $T \leq n$ d'étapes où :

如果两个群体线性可分，则感知机算法在有限的 $T \leq n$ 步内收敛，其中：

$$
T \leq \frac {2 R ^ {2}}{M ^ {2}}
$$

avec $M = \min_{1 \leq i \leq n} \{ y_i d(x_i, H^*) \}$ pour un certain séparateur $H^*$ .

这里，对某个分隔面 $H^*$，有 $M = \min_{1 \leq i \leq n} \{ y_i d(x_i, H^*) \}$。

> **译注：** 原课件写出的 $T\le n$ 不普遍成立。标准感知机界按错误更新次数计数，使用同一增广空间中的样本半径和分隔间隔；不能直接把原空间的几何距离与增广间隔混用。

- Défaut du perceptron : mauvaise généralisation

  感知机的缺点：泛化能力差。
- Vertu du perceptron : algorithme séquentiel (online)

  感知机的优点：序贯（在线）算法。

<a id="section-11"></a>

Scénario 1 - hyperplan à bonne généralisation

## 场景 1：具有良好泛化能力的超平面

Question : hyperplan se trouvant à distance maximale de chaque population ?

问题：是否存在与每个群体的距离都尽可能大的超平面？

![image](<Images/05_NLM/image_004.jpg>)

Problème d'optimisation

### 优化问题

$$
\max _ {\beta \in \mathbb {R} ^ {d}, b \in \mathbb {R}} M
$$

sous les contraintes :

约束条件：

$$
\forall i = 1, \dots , n, \quad y _ {i} \cdot d (x _ {i}, H) \geq M
$$

On rappelle :

回顾：

$$
d (x _ {i}, H) = \frac {1}{\| \beta \|} (b + <   \beta , x _ {i} >)
$$

Contraintes :

约束：

$$
\forall i = 1, \dots , n, \quad y _ {i} \cdot \frac {1}{\| \beta \|} (b + <   \beta , x _ {i} >) \geq M
$$

On peut très bien poser : $M = 1 / \|\beta\|$

完全可以设定：$M = 1 / \|\beta\|$。

Formulation équivalente

### 等价表述

$$
\min _ {\beta , b} \frac {1}{2} \| \beta \| ^ {2}
$$

sous les contraintes :

约束条件：

$$
\forall i = 1, \dots , n, \quad y _ {i} \cdot (b + <   \beta , x _ {i} >) \geq 1
$$

![image](<Images/05_NLM/image_005.jpg>)

$$
\text{场景 2：松弛变量（续）}
$$

On introduit $n$ variables supplémentaires ("slacks" ou "ressorts"): $\xi = (\xi_1, \ldots, \xi_n)$ avec $\xi_i \geq 0, \forall i$

引入 $n$ 个附加变量（“松弛变量”或“弹簧”）：$\xi = (\xi_1, \ldots, \xi_n)$，满足 $\xi_i \geq 0, \forall i$。

Nouveau problème d'optimisation

### 新的优化问题

$$
\min _ {\beta , b, \xi} \frac {1}{2} \| \beta \| ^ {2}
$$

sous les contraintes :

约束条件：

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

### 拉格朗日表述 I

$$
\min _ {\beta , b, \xi} \frac {1}{2} \| \beta \| ^ {2} + C \sum_ {i = 1} ^ {n} \xi_ {i}
$$

sous les contraintes :

约束条件：

$$
\begin{array}{r l} \forall i = 1, \ldots , n, & \xi_ {i} \geq 0 \\ & \xi_ {i} \geq 1 - [ y _ {i} \cdot (b + <   \beta , x _ {i} >) ] \end{array}
$$

Formulation lagrangienne II
Multiplicateurs de Lagrange : $\alpha = (\alpha_{1}, \ldots, \alpha_{n})$ , $\mu = (\mu_{1}, \ldots, \mu_{n})$ Formulation lagrangienne II

### 拉格朗日表述 II：拉格朗日乘子 $\alpha = (\alpha_{1}, \ldots, \alpha_{n})$、$\mu = (\mu_{1}, \ldots, \mu_{n})$

$$
\min _ {\beta , b, \xi} \frac {1}{2} \| \beta \| ^ {2} + C \sum_ {i = 1} ^ {n} \xi_ {i} - \sum_ {i = 1} ^ {n} \alpha_ {i} \left(y _ {i} \cdot (b + <   \beta , x _ {i} >) - (1 - \xi_ {i})\right) + \sum_ {i = 1} ^ {n} \mu_ {i} \xi_ {i}
$$

Conditions du premier ordre (gradient nul)

一阶条件（梯度为零）：

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

### 对偶表述

$$
\max _ {\alpha} \sum_ {i = 1} ^ {n} \alpha_ {i} - \frac {1}{2} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \alpha_ {i} \alpha_ {j} y _ {i} y _ {j} <   x _ {i}, x _ {j} >
$$

sous les contraintes :

约束条件：

$$
\begin{array}{r l} \forall i = 1, \ldots , n, & 0 \leq \alpha_ {i} \leq C \\ \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} & = 0 \end{array}
$$

On note $\hat{\alpha} = (\hat{\alpha}_1, \ldots, \hat{\alpha}_n)$ la solution de ce problème.

用 $\hat{\alpha} = (\hat{\alpha}_1, \ldots, \hat{\alpha}_n)$ 表示该问题的解。

<a id="section-12"></a>

**Conditions de Karush-Kuhn-Tucker**

## Karush–Kuhn–Tucker 条件

Conditions de Karush-Kuhn-Tucker

Karush–Kuhn–Tucker 条件：

$$
\begin{array}{r l} \forall i = 1, \ldots , n, & \alpha_ {i} (y _ {i} \cdot f (x _ {i}) - (1 - \xi_ {i})) = 0 \\ & y _ {i} \cdot f (x _ {i}) - (1 - \xi_ {i}) \geq 0 \\ & \alpha_ {i} + \mu_ {i} = C \\ & \mu_ {i} \xi_ {i} = 0 \\ & \beta = \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} x _ {i} \\ & \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} = 0 \end{array}
$$

Lien entre les coefficients et la position des observations

系数与观测位置的联系：

- si $\hat{\alpha}_i = 0$ alors $y_i \cdot f(x_i) \geq 1 \Rightarrow$ le point $x_i$ est bien classé
car $\mu_i = C > 0$ et on a $\xi_i = 0$

- 如果 $\hat{\alpha}_i = 0$，则 $y_i \cdot f(x_i) \geq 1 \Rightarrow$，点 $x_i$ 被正确分类，因为 $\mu_i = C > 0$，并且有 $\xi_i = 0$。
- si $0 < \hat{\alpha}_i < C$ alors $y_i \cdot f(x_i) = 1 \Rightarrow$ le point $x_i$ est sur la frontière de la marge
car $\mu_i > 0$ et $\xi_i = 0$

- 如果 $0 < \hat{\alpha}_i < C$，则 $y_i \cdot f(x_i) = 1 \Rightarrow$，点 $x_i$ 位于间隔边界上，因为 $\mu_i > 0$ 且 $\xi_i = 0$。
- si $\hat{\alpha}_i = C$ alors $y_i \cdot f(x_i) \leq 1 \Rightarrow$ le point $x_i$ dépasse la frontière de la marge
car $\mu_i = 0$ et donc $\xi_i \geq 0$

- 如果 $\hat{\alpha}_i = C$，则 $y_i \cdot f(x_i) \leq 1 \Rightarrow$，点 $x_i$ 越过间隔边界，因为 $\mu_i = 0$，所以 $\xi_i \geq 0$。

> **译注：** $\widehat\alpha_i=C$ 时只能推出 $y_if(x_i)\le1$，包括等号；不能断言该点严格越过间隔边界或一定误分类。

Phénomène remarquable!

一个值得注意的现象！

En pratique, beaucoup de $\hat{\alpha}_i$ sont nuls!

实际中，许多 $\hat{\alpha}_i$ 为零！

**Définition**

### 定义

Les $\hat{\alpha}_i \neq 0$ correspondent aux vecteurs de support. On note $I$ l'ensemble des indices parmi $\{1, \ldots, n\}$ correspondants.

$\hat{\alpha}_i \neq 0$ 对应支持向量。用 $I$ 表示 $\{1, \ldots, n\}$ 中相应索引构成的集合。

Représentation de la solution

### 解的表示

Fonction de décision :

决策函数：

$$
\hat {f} (x) = \hat {b} + \sum_ {i \in I} \hat {\alpha} _ {i} y _ {i} <   x _ {i}, x >
$$

où :

其中：

$$
\hat {\beta} = \sum_ {i \in I} \hat {\alpha} _ {i} y _ {i} x _ {i}, I = \{i: \hat {\alpha} _ {i} \neq 0 \}
$$

$$
\hat {b} = y _ {j} - \sum_ {i \in I} \hat {\alpha} _ {i} y _ {i} <   x _ {i}, x _ {j} >, \quad \text{对某个} j \in I
$$

<a id="section-13"></a>

**Canonical Optimal Hyperplane**

## 规范最优超平面

![image](<Images/05_NLM/image_006.jpg>)

⇒ Représentation parcimonieuse ("sparse") des SVM

⇒ SVM 的稀疏表示。

<a id="reading-recap-linear-to-nonlinear"></a>

**Complément — lien avec le cours 3 et pourquoi la formulation duale prépare le passage au non-linéaire**

**补充——与第三课的衔接，以及为什么 SVM 对偶形式天然通向非线性分类**

Les sections 2 à 13 rappellent les fondations du [cours 3 (`03_LMC_zh.md`)](03_LMC_zh.md), dont les démonstrations détaillées peuvent être consultées directement aux entrées suivantes :
- [Modèles génératifs vs discriminatifs et règle de Bayes](03_LMC_zh.md#reading-generative-vs-discriminative) (§2–6) ;
- [Distance signée, mise à jour géométrique du Perceptron et preuve du théorème de Novikoff](03_LMC_zh.md#reading-perceptron-novikoff) (§7–10) ;
- [Normalisation canonique $M=1/\|\beta\|$, dualité lagrangienne des SVM et classification KKT des vecteurs de support](03_LMC_zh.md#reading-svm-duality-kkt) (§11–13).

本讲第 2 至 13 节是对[第三课（`03_LMC_zh.md`）](03_LMC_zh.md)核心内容的快速回顾，各定理的完整数学证明可直接参阅第三课的对应扩展模块：
- [生成式与判别式建模对比及 Bayes 后验判别规则](03_LMC_zh.md#reading-generative-vs-discriminative)（对应本讲 §2–6）；
- [超平面有符号距离、感知机几何更新与 Novikoff 定理证明](03_LMC_zh.md#reading-perceptron-novikoff)（对应本讲 §7–10）；
- [规范超平面缩放 $M=1/\|\beta\|$、SVM 拉格朗日对偶推导与 KKT 支持向量分类](03_LMC_zh.md#reading-svm-duality-kkt)（对应本讲 §11–13）。

L'observation essentielle qui ouvre la suite de ce cours est que, dans le problème dual (§11) comme dans la fonction de décision finale (§12), **les vecteurs $x_i \in \mathbb{R}^d$ n'apparaissent jamais isolément, mais uniquement sous la forme de produits scalaires deux à deux** $\langle x_i, x_j\rangle$ (lors de l'entraînement) et $\langle x_i, x\rangle$ (lors de la prédiction) :

承上启下最关键的一点在于：无论是在 §11 的对偶二次规划目标中，还是在 §12 的最终决策函数中，**样本向量 $x_i \in \mathbb{R}^d$ 从未单独出现，而仅仅以两两内积的形式出现**——训练阶段只用到 $\langle x_i, x_j\rangle$，预测阶段只用到支持向量与新样本的内积 $\langle x_i, x\rangle$：

$$
\text{Entraînement / 训练 : } \langle x_i, x_j\rangle,
\qquad
\text{Prédiction / 预测 : } \hat{f}(x) = \hat{b} + \sum_{i\in I} \hat{\alpha}_i y_i \langle x_i, x\rangle.
$$

C'est cette propriété algébrique qui permet, dès les lignes suivantes, de remplacer $\mathbb{R}^d$ par un espace de caractéristiques de dimension arbitrairement grande sans calculer explicitement les coordonnées transformées.

正是这一代数结构，使得接下来只需将标准内积替换为核函数，就能在不显式计算高维特征坐标的前提下直接构造非线性分界面。

<a id="kernel-svm"></a>

- La plupart des problèmes de classification relèvent de séparations non-linéaires

  大多数分类问题需要非线性分隔。
- L'algorithme de construction de l'hyperplan à marges optimales ne fait intervenir les observations que sous la forme des produits scalaires $< x_i, x_j >$ pour tout $i, j$

  构造最优间隔超平面的算法只通过内积 $< x_i, x_j >$ 使用观测，其中 $i, j$。
- La fonction de décision dépend du produit scalaire entre le nouveau point $x$ et les vecteurs de support $x_i$

  决策函数依赖新点 $x$ 与支持向量 $x_i$ 之间的内积。
- Astuce du noyau ("kernel trick") : l'algorithme de construction de l'hyperplan à marges optimales ne dépend des observations qu'au travers des coefficients de la matrice de Gram

  核技巧：构造最优间隔超平面的算法只通过 Gram 矩阵的元素依赖于观测。

$$
K = \big (<   x _ {i}, x _ {j} > \big) _ {1 \leq i, j \leq n}
$$

- Méthodes à noyaux : on remplace le produit scalaire canonique par un noyau positif

  核方法：用一个正定核替换标准内积。

$$
k: \mathcal {X} \times \mathcal {X} \to \mathbb {R}
$$

et alors $K$ devient la matrice des $k(x_{i},x_{j})$ .

于是 $K$ 变为以 $k(x_{i},x_{j})$ 为元素的矩阵。

Formulation duale

### 对偶表述

$$
\max _ {\alpha} \sum_ {i = 1} ^ {n} \alpha_ {i} - \frac {1}{2} \sum_ {i = 1} ^ {n} \sum_ {j = 1} ^ {n} \alpha_ {i} \alpha_ {j} y _ {i} y _ {j} k (x _ {i}, x _ {j})
$$

sous les contraintes :

约束条件：

$$
\begin{array}{r l} \forall i = 1, \ldots , n, & 0 \leq \alpha_ {i} \leq C \\ \sum_ {i = 1} ^ {n} \alpha_ {i} y _ {i} & = 0 \end{array}
$$

Fonction de décision :

决策函数：

$$
\hat {f} (x) = \hat {b} + \sum_ {i \in I} \hat {\alpha} _ {i} k (x _ {i}, x)
$$

> **译注：** 原课件的核 SVM 决策函数漏了标签因子。若沿用上方对偶变量定义，应为 $\widehat f(x)=\widehat b+\sum_{i\in I}\widehat\alpha_i y_i k(x_i,x)$；只有把标签吸收到另一定义的系数中时才能省略它。

avec / indices des vecteurs de support.

其中 I 为支持向量的索引集合。

- noyaux polynomiaux

  多项式核。

$$
\begin{array}{r l} {k _ {r} (x, x ^ {\prime})} & {= (<   x, x ^ {\prime} >) ^ {r}} \\ {k _ {r, c} (x, x ^ {\prime})} & {= (<   x, x ^ {\prime} > + c) ^ {r}} \end{array}
$$

- noyau à fonctions de base radiales gaussiennes (RBF)

  高斯径向基函数核（RBF）。

$$
k _ {\sigma} (x, x ^ {\prime}) = \exp \left(- \frac {\| x - x ^ {\prime} \| ^ {2}}{2 \sigma^ {2}}\right)
$$

- noyau sigmoïde (réseau de neurones)

  sigmoid 核（神经网络）。

$$
k _ {\kappa , \theta} (x, x ^ {\prime}) = \tanh (\kappa <   x, x ^ {\prime} > + \theta)
$$

> **译注：** sigmoid 形式并非对任意参数、任意输入集合都构成正定核；使用核 SVM 时还需检查其适用条件。

- Sélection d'un noyau

  选择核。
- Réglage des paramètres : utilisation d'une base de validation

  参数调整：使用验证集。
- Mesures de performances : erreur sur la base de test

  性能度量：测试集上的误差。
- Comparaison à d'autres méthodes

  与其他方法比较。
- Extensions :

  扩展：
- problème de classification à plus de deux classes

  超过两个类别的分类问题。
- cas de populations très disproportionnées

  各群体比例极不均衡的情形。

<a id="reading-kernel-svm-mercer"></a>

**Complément — l'astuce du noyau (Kernel Trick), théorème de Mercer et géométrie des hyperparamètres $(C, \sigma)$**

**补充——核技巧（Kernel Trick）、Mercer 正定核条件与核 SVM 超参数 $(C, \sigma)$ 的几何作用**

Lorsque les deux populations ne sont pas linéairement séparables dans l'espace d'origine $\mathbb{R}^d$ (par exemple si la classe $+1$ est à l'intérieur d'un disque et la classe $-1$ à l'extérieur), l'idée consiste à plonger les observations dans un espace de Hilbert $\mathcal{H}$ de grande dimension (voire de dimension infinie) via une application non linéaire $\Phi : \mathcal{X} \to \mathcal{H}$, puis à y construire un hyperplan séparateur à marge maximale $f(x) = b + \langle\beta, \Phi(x)\rangle_{\mathcal{H}}$.

当两类样本在原始空间 $\mathbb{R}^d$ 中无法用超平面分开（例如正例分布在圆盘内部、负例分布在圆盘外部）时，核方法的核心思想是通过一个非线性特征映射 $\Phi : \mathcal{X} \to \mathcal{H}$，将数据嵌入到一个高维（甚至无限维）Hilbert 空间 $\mathcal{H}$ 中，并在 $\mathcal{H}$ 中构造最大间隔超平面 $f(x) = b + \langle\beta, \Phi(x)\rangle_{\mathcal{H}}$。

Grâce à la formulation duale, nous n'avons jamais besoin de calculer ni de stocker $\Phi(x) \in \mathcal{H}$ : il suffit de savoir évaluer le produit scalaire par un **noyau défini positif** (*positive semi-definite kernel*, caractérisé par le théorème de Mercer — toute matrice de Gram $K = \big(k(x_i,x_j)\big)_{1\le i,j\le n}$ doit être symétrique semi-définie positive, voir aussi le [cours 2, section 7](02_LM/07_kernels_and_extensions.md#reading-feature-map)) :

借助对偶表述，我们根本不需要显式计算或存储 $\Phi(x) \in \mathcal{H}$ 的坐标，只需直接计算特征空间中的内积——即满足 **Mercer 定理／半正定条件**（对任意有限样本集，Gram 矩阵 $K = \big(k(x_i,x_j)\big)_{1\le i,j\le n}$ 均对称半正定；参见[第二课第 7 篇](02_LM/07_kernels_and_extensions.md#reading-feature-map)）的**核函数** $k(x, x') = \langle\Phi(x), \Phi(x')\rangle_{\mathcal{H}}$：

| Noyau / 核函数 | Expression $k(x,x')$ / 数学表达式 | Espace $\mathcal{H}$ et frontière dans $\mathbb{R}^d$ / 对应特征空间与原空间分界面形状 | Rôle des hyperparamètres / 超参数的作用 |
|---|---|---|---|
| **Polynomial** / 多项式核 | $(\langle x, x'\rangle + c)^r$ | Monômes de degré $\le r$, dimension $\binom{d+r}{r}$ ; frontières polynomiales de degré $r$ (ellipses, hyperboles pour $r=2$). / 次数 $\le r$ 的全部单项式，维数 $\binom{d+r}{r}$；在原空间形成 $r$ 次代数曲面（$r=2$ 时为椭圆、双曲线等）。 | $r$ fixe le degré de courbure ; $c \ge 0$ dose le poids relatif des termes de bas degré par rapport au degré $r$. / $r$ 决定多项式阶数；$c \ge 0$ 调节低阶项与高阶项的相对权重。 |
| **Gaussien (RBF)** / 高斯径向基核 | $\exp\!\left(-\frac{\|x-x'\|^2}{2\sigma^2}\right)$ | Espace $\mathcal{H}$ de **dimension infinie** ; chaque vecteur de support $x_i$ place une « bosse » gaussienne locale centrée en $x_i$. / **无限维**特征空间；每个支持向量 $x_i$ 在其周围产生一个局部高斯钟形响应。 | $\sigma$ règle le rayon d'influence local : **petit $\sigma$** $\Rightarrow$ îlots très serrés autour des points (risque de surapprentissage) ; **grand $\sigma$** $\Rightarrow$ frontière très lisse. / $\sigma$ 控制局部影响半径：**$\sigma$ 过小**会在单个样本周围形成孤立小岛（严重过拟合）；**$\sigma$ 较大**则分界面平滑。 |
| **Sigmoïde** / Sigmoid 核 | $\tanh(\kappa\langle x,x'\rangle + \theta)$ | Analogue à une couche cachée de neurones à activation $\tanh$, mais **n'est semi-défini positif que pour certaines valeurs de $(\kappa,\theta)$**. / 形式类似含单隐藏层 $\tanh$ 的神经网络，但**仅在特定参数 $(\kappa,\theta)$ 下才满足半正定条件**。 | Si $K$ n'est pas semi-définie positive, le problème dual perd sa concavité et les solveurs QP standards peuvent diverger. / 若参数使 Gram 矩阵非半正定，对偶问题将失去凹性，标准二次规划求解器可能失效。 |

**Exemple : comment un noyau polynomial de degré 2 transforme un cercle en hyperplan et pourquoi le noyau RBF est de dimension infinie**

**示例：二次多项式核如何把环形边界变成超平面，以及为什么高斯 RBF 核对应无限维空间**

1. **Séparation circulaire en 2D par le noyau quadratique 二维同心圆分离的二次核映射 :**
   Supposons que dans $\mathbb{R}^2$, la classe $+1$ vérifie $x_1^2 + x_2^2 < 1$ et la classe $-1$ vérifie $x_1^2 + x_2^2 > 1$. Aucune droite de $\mathbb{R}^2$ ne peut les séparer. Utilisons le noyau polynomial homogène de degré $2$, $k(x, x') = (\langle x, x'\rangle)^2$, qui correspond au plongement dans $\mathbb{R}^3$ :

   设在二维平面 $\mathbb{R}^2$ 中，正类位于单位圆内 $x_1^2 + x_2^2 < 1$，负类位于单位圆外 $x_1^2 + x_2^2 > 1$，平面上不存在任何直线能将二者分开。采用齐次二次多项式核 $k(x, x') = (\langle x, x'\rangle)^2$，它对应从 $\mathbb{R}^2$ 到 $\mathbb{R}^3$ 的特征映射：

$$
\Phi(x_1, x_2) = \big(x_1^2,\; \sqrt{2} x_1 x_2,\; x_2^2\big)^T \in \mathbb{R}^3.
$$

   Dans $\mathbb{R}^3$, prenons le vecteur normal $\beta = (-1, 0, -1)^T$ et l'ordonnée à l'origine $b = 1$. L'hyperplan affine $b + \langle\beta, \Phi(x)\rangle_{\mathbb{R}^3} = 1 - x_1^2 - x_2^2 = 0$ est **un plan plat dans $\mathbb{R}^3$**, qui sépare parfaitement les deux classes et correspond exactement au cercle unité $x_1^2 + x_2^2 = 1$ dans $\mathbb{R}^2$ !

   在三维特征空间 $\mathbb{R}^3$ 中，取法向量 $\beta = (-1, 0, -1)^T$ 和截距 $b = 1$，则仿射超平面 $b + \langle\beta, \Phi(x)\rangle_{\mathbb{R}^3} = 1 - x_1^2 - x_2^2 = 0$ 在 $\mathbb{R}^3$ 中是一个**平直的平面**，它完美分开了两类样本，而投影回原平面 $\mathbb{R}^2$ 恰好就是单位圆周 $x_1^2 + x_2^2 = 1$！

2. **Pourquoi le noyau RBF gaussien correspond à un espace $\mathcal{H}$ de dimension infinie 为什么高斯 RBF 核对应无限维特征空间 :**
   Pour $x, x' \in \mathbb{R}$ (en prenant $\sigma = 1$ pour simplifier), factorisons et développons $\exp(x x')$ en série entière :

   以一维输入 $x, x' \in \mathbb{R}$（取 $\sigma=1$）为例，将高斯核展开并利用指数函数的泰勒级数 $\exp(x x') = \sum_{m=0}^\infty \frac{(x x')^m}{m!}$：

$$
k(x, x') = \exp\!\left(-\frac{(x - x')^2}{2}\right)
= e^{-x^2/2} e^{-(x')^2/2} \exp(x x')
= \sum_{m=0}^{+\infty} \underbrace{\left(e^{-x^2/2} \frac{x^m}{\sqrt{m!}}\right)}_{\Phi_m(x)} \underbrace{\left(e^{-(x')^2/2} \frac{(x')^m}{\sqrt{m!}}\right)}_{\Phi_m(x')}.
$$

   On voit que $k(x, x') = \langle\Phi(x), \Phi(x')\rangle_{\ell^2(\mathbb{N})}$ est le produit scalaire d'une suite infinie de fonctions coordonnées $\Phi(x) = (\Phi_0(x), \Phi_1(x), \dots) \in \ell^2(\mathbb{N})$, tout en s'évaluant en $O(d)$ opérations !

   由此可见，$k(x, x') = \langle\Phi(x), \Phi(x')\rangle_{\ell^2(\mathbb{N})}$ 严格等于无穷维序列空间 $\ell^2(\mathbb{N})$ 中特征映射 $\Phi(x) = (\Phi_0(x), \Phi_1(x), \dots)$ 的内积，但在原空间中只需 $O(d)$ 次运算即可直接算出！

<a id="local-methods"></a>

<a id="section-14"></a>

Modèles non linéaires basés sur la localité

## 基于局部性的非线性模型

**Other forms of regularization**

### 其他形式的正则化

- General idea : Regularized function estimation without global optimization

  总体思路：不进行全局优化的正则化函数估计。
- Two directions :

  两个方向：
- Local methods : nearest-neighbors and decision trees

  局部方法：最近邻与决策树。
- Ensemble methods: bagging, boosting, random forests

  集成方法：Bagging、Boosting、随机森林。

<a id="section-15"></a>

**Regularization without optimization The case of histograms**

## 无需优化的正则化：直方图

![image](<Images/05_NLM/image_007.jpg>)

![image](<Images/05_NLM/image_008.jpg>)

![image](<Images/05_NLM/image_009.jpg>)

![image](<Images/05_NLM/image_010.jpg>)

Distribution of the age of the passengers of the Titanic with bins varying from 1 year to 15 years

Titanic 乘客的年龄分布，分箱宽度从 1 年变化到 15 年。

<a id="section-16"></a>

**Ingredients for that type of regularization**

## 这类正则化的组成要素

- Histograms use two general ideas of locality (bins) and averaging (piecewise constant function)

  直方图使用两个一般思想：局部性（分箱）与平均（分段常数函数）。
- define local : which training data can be considered to be close to the point where a prediction has to be made?

  定义局部：哪些训练数据可以认为接近待预测的点？
- averaging (or voting if discrete outcome) : take the average of the values over each bin

  平均（若结果离散则为投票）：对每个分箱内的值取平均。
- Regularization through hyperparameter selection : find the optimal bin size amounts to finding the right hypothesis class

  通过超参数选择进行正则化：寻找最优分箱大小，相当于寻找恰当的假设类。

<a id="section-17"></a>

**From histograms to Machine Learning**

## 从直方图到机器学习

- In the previous example, the objective was to estimate a density function from a sample drawn from this distribution (problem known in the literature as nonparametric density estimation or kernel density estimation)

  在前面的例子中，目标是根据从某个分布中抽取的样本估计该分布的密度函数；文献中将这一问题称为非参数密度估计或核密度估计。

> **译注：** 直方图属于非参数密度估计；它与通常通过平滑核函数构造的核密度估计不应简单视为同义方法。

- Density estimation can be seen as an unsupervised learning problem

  密度估计可视为无监督学习问题。
- In the supervised setting, we establish the values of the function on every bin either by averaging (regression setup) or by voting (classification setup). The general terminology for averaging/voting is aggregating/combining.

  在监督学习设定下，通过平均（回归情形）或投票（分类情形）确定每个分箱上的函数值。平均／投票的通用名称是聚合／组合。

<a id="section-18"></a>

**Two popular types of local methods**

## 两类常见的局部方法

- Nearest neighbors : local are the closest points

  最近邻：局部点是距离最近的点。
- Partition-based rules (also called decision trees): local are the points within a cell from a partition of the input space only

  基于划分的规则，也称决策树：局部点仅指输入空间某个划分单元内的点。

Works for classification, regression and other problems... but here we will focus on classification

这些方法适用于分类、回归及其他问题……但这里重点讨论分类。

- Given :

  已知：
- Consider a sample of classification data

  考虑一个分类数据样本

$$
(X _ {1}, Y _ {1}) \dots (X _ {n}, Y _ {n})
$$

where $X_{i} \in R^{d}$ vector of independent variables,

其中 $X_{i} \in R^{d}$ 是自变量向量，

$Y_{i}\in \{1,\dots ,C\}$ the label

$Y_{i}\in \{1,\dots ,C\}$ 是标签。

- Want :

  希望：
- to predict the label y at any position x

  在任意位置 x 预测标签 y。

<a id="section-19"></a>

Local methods #1 : k-Nearest neighbors (k-NN)

## 局部方法 1：k 近邻（k-NN）

**k-Nearest Neighbor (1/4) Principle of the k-NN algorithm**

### k 近邻（1/4）：算法原理

**① Compute distances**

#### 1. 计算距离

- Compute pairwise distances $d(x, X_{i})$ for all $i = 1, \ldots, n$

  对所有 $i = 1, \ldots, n$，计算两两距离 $d(x, X_{i})$。

**② Sort training data**

#### 2. 对训练数据排序

- Sort the data points from the closest $X_{(1)}$ to the farthest $X_{(n)}$ (i.e. $d(x, X_{(1)}) \leq \ldots \leq d(x, X_{(n)})$

  将数据点从最近的 $X_{(1)}$ 排到最远的 $X_{(n)}$，即 $d(x, X_{(1)}) \leq \ldots \leq d(x, X_{(n)})$。

③ Prediction $\hat{h}(x,k)=$ Majority vote of the k-NN

#### 3. 预测 $\hat{h}(x,k)=$：k 个最近邻的多数投票

- Consider the labels $Y_{(1)}, \ldots, Y_{(k)}$ of the $k$ closest points to $x$ and take the majority vote

  考虑距离 $x$ 最近的 $k$ 个点的标签 $Y_{(1)}, \ldots, Y_{(k)}$，进行多数投票。

$$
\hat {h} (x, k) = \arg \max _ {c} \{\sum_ {l = 1} ^ {k} \mathbb {I} \{Y _ {(l)} = c \} \}
$$

**k-Nearest Neighbor (2/4) Principle of the k-NN algorithm**

### k 近邻（2/4）：算法原理

**kNN Algorithm**

#### kNN 算法

0. Look at the data

   观察数据。

![image](<Images/05_NLM/image_011.jpg>)

Say you want to classify the grey point into a class. Here, there are three potential classes - lime green, green and orange.

假设要将灰色点分到某个类别。这里有三个可能的类别：黄绿色、绿色和橙色。

1. Calculate distances

   计算距离。

![image](<Images/05_NLM/image_012.jpg>)

Start by calculating the distances between the grey point and all other points.

首先计算灰色点与其他所有点之间的距离。

**2. Find neighbours**

#### 2. 找到邻居

![image](<Images/05_NLM/image_013.jpg>)

Next, find the nearest neighbours by ranking points by increasing distance. The nearest neighbours (NNs) of the grey point are the ones closest in dataspace.

接下来按距离递增排列各点，找出最近邻。灰色点的最近邻就是数据空间中距离它最近的点。

**3. Vote on labels**

#### 3. 对标签投票

![image](<Images/05_NLM/image_014.jpg>)

Class wins the vote!

该类别赢得投票！

to be of class

归入该类别。

Vote on the predicted class labels based on the classes of the k nearest neighbours. Here, the labels were predicted based on the k=3 nearest neighbours.

根据 k 个最近邻的类别，对预测类别标签进行投票。这里基于 k = 3 个最近邻预测标签。

> **译注：** 原页图中文字写 k=3，但投票表中的计数为 2、1、1，共 4 票；此处按原文保留，并指出图文不一致。

Hyperparameters

### 超参数

- Choice of a distance $d$ between points of $\mathbb{R}^d$

  选择 $\mathbb{R}^d$ 中点之间的距离 $d$。
- Number k of Nearest Neighbors, estimated by cross-validation :

  最近邻个数 k，通过交叉验证估计：

![image](<Images/05_NLM/image_015.jpg>)

![image](<Images/05_NLM/image_016.jpg>)

![image](<Images/05_NLM/image_017.jpg>)

- Recall : classification error $L(h) = \mathbb{P}(Y \neq h(X))$ and $L^* = \inf L$

  回顾：分类误差 $L(h) = \mathbb{P}(Y \neq h(X))$，以及 $L^* = \inf L$。
- Consistency result :

  一致性结果：

$$
\mathbb {E} L \big (\hat {h} (\cdot , k _ {n}) \big) \to L ^ {*}
$$

under the condition: $k_{n} \rightarrow \infty$ and $k_{n}/n \rightarrow 0$ when $n \rightarrow \infty$

条件为：当 $n \rightarrow \infty$ 时，$k_{n} \rightarrow \infty$ 且 $k_{n}/n \rightarrow 0$。

- No closed-form solution for optimal $k_{n}$ (in practice, we use cross-validation)

  最优 $k_{n}$ 没有闭式解；实践中使用交叉验证。
- No theoretical clue on the choice of the distance (related to data representation and the physics of the problem)

  距离的选择没有理论线索，它与数据表示及问题的物理性质有关。

> **译注：** 原文的说法较强；这些一致性条件本身不能给出适合任意任务的最佳距离，但并不意味着距离选择完全没有理论研究。

<a id="reading-knn-stone-consistency"></a>

**Supplement — Stone's Universal Consistency Theorem for $k$-NN, the Bias–Variance Trade-off of $k_n$, and the Curse of Dimensionality.**

**补充——$k$ 近邻的 Stone 普适一致性定理、$k_n$ 的偏差–方差权衡与维数灾难。**

The $k$-Nearest Neighbor ($k$-NN) classifier is a purely nonparametric local method: instead of fitting global parameters, it estimates the class posterior probability $\mathbb{P}(Y=c\mid X=x)$ locally by the empirical fraction of class-$c$ points among the $k$ closest training observations to $x$:

$k$ 近邻（$k$-NN）分类器是一种纯粹的非参数局部方法：它不拟合全局参数，而是用距离 $x$ 最近的 $k$ 个训练样本中属于类别 $c$ 的经验比例，在局部估计后验概率 $\mathbb{P}(Y=c\mid X=x)$：

$$
\hat{\eta}_k^{(c)}(x) = \frac{1}{k}\sum_{l=1}^k \mathbb{I}\{Y_{(l)} = c\}, \qquad \hat{h}(x, k) = \arg\max_{c\in\{1,\dots,C\}} \hat{\eta}_k^{(c)}(x).
$$

**Stone's Theorem (1977)** establishes that $k$-NN is **universally Bayes-consistent**—that is, $\mathbb{E}[L(\hat{h}(\cdot, k_n))] \to L^*$ as $n\to\infty$ for **every** joint distribution $\mathbb{P}$ of $(X,Y)$—if and only if the neighborhood size $k_n$ satisfies the double asymptotic condition:

**Stone 定理（1977）**证明了 $k$-NN 具有**普适 Bayes 一致性**——即对 $(X,Y)$ 的**任意**联合分布 $\mathbb{P}$，当 $n\to\infty$ 时均有 $\mathbb{E}[L(\hat{h}(\cdot, k_n))] \to L^*$——当且仅当近邻数 $k_n$ 满足如下双重渐近条件：

$$
k_n \xrightarrow[n\to\infty]{} \infty \qquad \text{and} \qquad \frac{k_n}{n} \xrightarrow[n\to\infty]{} 0
$$

(for example, $k_n = \lfloor n^{2/(d+2)} \rfloor$ or $k_n = \lfloor \sqrt{n} \rfloor$). Each of the two conditions governs one side of the bias–variance trade-off:

（例如取 $k_n = \lfloor n^{2/(d+2)} \rfloor$ 或 $k_n = \lfloor \sqrt{n} \rfloor$）。这两个条件分别控制偏差–方差权衡的一端：

1. **Why $k_n \to \infty$ (Variance $\to 0$)**: Even if a neighbor $X_{(l)}$ is arbitrarily close to $x$, its label $Y_{(l)}$ is a noisy Bernoulli/categorical draw with conditional expectation $\eta(X_{(l)})$. Averaging over $k_n$ neighbors reduces the conditional variance of the empirical frequency at rate $O(1/k_n)$. If $k$ stays fixed (such as $1$-NN with $k=1$), label noise is never averaged out: for binary classification, Cover & Hart (1967) showed that as $n\to\infty$, the $1$-NN risk converges to $L_{\text{1-NN}}^\infty = 2\mathbb{E}[\eta(X)(1-\eta(X))]$. Since $L^* = \mathbb{E}[\min(\eta(X), 1-\eta(X))]$, we have the exact identity
   $$L_{\text{1-NN}}^\infty - L^* = \mathbb{E}\!\Big[\min\big(\eta(X), 1-\eta(X)\big)\,\big|2\eta(X) - 1\big|\Big] \ge 0 \qquad \big(\text{and } L^* \le L_{\text{1-NN}}^\infty \le 2L^*(1-L^*)\big).$$
   Thus $L_{\text{1-NN}}^\infty = L^*$ if and only if $\eta(X) \in \{0, 1/2, 1\}$ almost surely (i.e., either deterministic zero-noise labels $\eta(X)\in\{0,1\}$ or pure balanced coin-flip labels $\eta(X)=1/2$), and **$L_{\text{1-NN}}^\infty > L^*$ whenever $\mathbb{P}\big(\eta(X) \notin \{0, 1/2, 1\}\big) > 0$**.

   **为什么需要 $k_n \to \infty$（使方差 $\to 0$）**：即便某个近邻 $X_{(l)}$ 与 $x$ 任意接近，其标签 $Y_{(l)}$ 仍是带噪声的随机抽样（条件期望为 $\eta(X_{(l)})$）。对 $k_n$ 个近邻取平均可将经验频率的条件方差以 $O(1/k_n)$ 的速率压低。若 $k$ 保持固定（如 $k=1$ 的 $1$-NN），标签噪声永远无法被平均掉：Cover 与 Hart（1967）证明，在二分类下当 $n\to\infty$ 时，$1$-NN 的极限风险收敛到 $L_{\text{1-NN}}^\infty = 2\mathbb{E}[\eta(X)(1-\eta(X))]$。利用 $L^* = \mathbb{E}[\min(\eta(X), 1-\eta(X))]$，二者之差精确满足：
   $$L_{\text{1-NN}}^\infty - L^* = \mathbb{E}\!\Big[\min\big(\eta(X), 1-\eta(X)\big)\,\big|2\eta(X) - 1\big|\Big] \ge 0 \qquad \big(\text{且 } L^* \le L_{\text{1-NN}}^\infty \le 2L^*(1-L^*)\big)。$$
   由此可见，当且仅当几乎处处有 $\eta(X) \in \{0, 1/2, 1\}$（即零噪声 $\eta(X)\in\{0,1\}$ 或纯随机均衡噪声 $\eta(X)=1/2$，这也正是第 28 节原文注明的两类例外！）时才有 $L_{\text{1-NN}}^\infty = L^*$；**只要 $\mathbb{P}\big(\eta(X) \notin \{0, 1/2, 1\}\big) > 0$，就有 $L_{\text{1-NN}}^\infty > L^*$**。
2. **Why $k_n/n \to 0$ (Bias $\to 0$)**: For $\hat{\eta}_{k_n}(x)$ to estimate $\eta(x)$ rather than a global average, all $k_n$ neighbors must lie inside a ball $B(x, R_{(k_n)})$ whose radius $R_{(k_n)} = \|X_{(k_n)} - x\|$ shrinks to $0$. Because a ball capturing a fraction $k_n/n$ of the sample has probability mass $\mathbb{P}(B(x, R_{(k_n)})) \approx k_n/n$, requiring $k_n/n \to 0$ forces $R_{(k_n)} \to 0$ at every point $x$ in the support of $X$ (Stone's Lemma). When $\eta$ is continuous at $x$, $R_{(k_n)} \to 0$ immediately implies $\frac{1}{k_n}\sum_{l=1}^{k_n}\eta(X_{(l)}) \to \eta(x)$; for general measurable $\eta$ without continuity assumptions, Stone (1977) proved $L^1$ convergence by approximating $\eta$ with continuous functions of compact support.

   **为什么需要 $k_n/n \to 0$（使偏差 $\to 0$）**：要让 $\hat{\eta}_{k_n}(x)$ 估计局部的 $\eta(x)$ 而非全局平均，全部 $k_n$ 个近邻必须落在半径 $R_{(k_n)} = \|X_{(k_n)} - x\|$ 趋于 $0$ 的球 $B(x, R_{(k_n)})$ 内。由于包含 $k_n/n$ 比例样本的球具有概率质量 $\mathbb{P}(B(x, R_{(k_n)})) \approx k_n/n$，要求 $k_n/n \to 0$ 会迫使支撑集内每一点 $x$ 处的近邻半径 $R_{(k_n)} \to 0$（Stone 引理）。在 $\eta$ 连续的额外假设下，这直接给出局部偏差趋于零 $\frac{1}{k_n}\sum_{l=1}^{k_n}\eta(X_{(l)}) \to \eta(x)$；而在不对分布和 $\eta$ 作连续性假设的一般情形下，Stone（1977）通过紧支撑连续函数在 $L^1$ 中逼近可测函数 $\eta$，严格证明了普适一致性。

**Derivation: Pointwise Bias–Variance Decomposition of $k$-NN and the Curse of Dimensionality（$k$-NN 的逐点偏差–方差分解与维数灾难推导）**

Consider estimating a $L$-Lipschitz regression/posterior function $\eta(x) = \mathbb{E}[Y\mid X=x]$ where $\operatorname{Var}(Y\mid X=z) \le \sigma^2$, using $\hat{\eta}_k(x) = \frac{1}{k}\sum_{l=1}^k Y_{(l)}$. Conditioned on the training inputs $\mathbf{X}_n = (X_1,\dots,X_n)$:

考虑用 $\hat{\eta}_k(x) = \frac{1}{k}\sum_{l=1}^k Y_{(l)}$ 估计 $L$-Lipschitz 的回归／后验函数 $\eta(x) = \mathbb{E}[Y\mid X=x]$（其中 $\operatorname{Var}(Y\mid X=z) \le \sigma^2$）。在给定训练输入 $\mathbf{X}_n = (X_1,\dots,X_n)$ 的条件下：

$$
\mathbb{E}\!\left[\big(\hat{\eta}_k(x) - \eta(x)\big)^2 \,\middle|\, \mathbf{X}_n\right] = \underbrace{\left(\frac{1}{k}\sum_{l=1}^k \eta(X_{(l)}) - \eta(x)\right)^2}_{\text{Squared Bias (smoothing error)}} + \underbrace{\frac{1}{k^2}\sum_{l=1}^k \operatorname{Var}(Y_{(l)}\mid X_{(l)})}_{\text{Variance (noise error)}} \le L^2 \|X_{(k)} - x\|^2 + \frac{\sigma^2}{k}.
$$

If $X$ is uniformly distributed on $[0,1]^d$, a ball (or hypercube) around $x$ containing $k$ out of $n$ points covers a volume fraction $\ell^d \approx \frac{k}{n}$, so its radius/side length scales as $\ell \approx (k/n)^{1/d}$. Substituting $\|X_{(k)} - x\| \asymp (k/n)^{1/d}$ gives:

若 $X$ 在 $[0,1]^d$ 上均匀分布，则 $x$ 周围包含 $n$ 个点中 $k$ 个点的超立方体占总体积的比例约为 $\ell^d \approx \frac{k}{n}$，因此其边长／半径尺度为 $\ell \approx (k/n)^{1/d}$。代入 $\|X_{(k)} - x\| \asymp (k/n)^{1/d}$ 可得：

$$
\mathbb{E}\!\left[\big(\hat{\eta}_k(x) - \eta(x)\big)^2\right] \lesssim L^2 \left(\frac{k}{n}\right)^{2/d} + \frac{\sigma^2}{k}.
$$

Balancing the two terms with respect to $k$ sets $(k/n)^{2/d} \asymp k^{-1}$, yielding the optimal rate:

对 $k$ 平衡这两项，令 $(k/n)^{2/d} \asymp k^{-1}$，可得最优阶：

$$
k_n^* \asymp n^{\frac{2}{d+2}}, \qquad \mathbb{E}\!\left[\big(\hat{\eta}_{k_n^*}(x) - \eta(x)\big)^2\right] \lesssim n^{-\frac{2}{d+2}}.
$$

**The Curse of Dimensionality**: In low dimension ($d=2$), the MSE decays as $n^{-1/2}$; in high dimension ($d=100$), it decays as $n^{-2/102} \approx n^{-0.02}$. Geometrically, to capture just $q = k/n = 1\%$ of the data in $d=20$ dimensions, a local hypercube must have side length $\ell = 0.01^{1/20} \approx 0.794$ along **every** coordinate axis—meaning "nearest neighbors" in high dimensions are no longer local at all unless $n$ grows exponentially with $d$.

**维数灾难**：在低维（$d=2$）下，均方误差以 $n^{-1/2}$ 衰减；而在高维（$d=100$）下，衰减速率仅为 $n^{-2/102} \approx n^{-0.02}$。从几何上看，在 $d=20$ 维空间中，即便只想捕获 $q = k/n = 1\%$ 的数据，局部超立方体在**每一个**坐标轴上的边长也必须达到 $\ell = 0.01^{1/20} \approx 0.794$——这意味着除非样本量 $n$ 随维数 $d$ 指数级增长，否则高维空间中的“最近邻”根本不再具有局部性。

<a id="decision-trees"></a>

<a id="section-20"></a>

Local methods #2 : Partition-based (decision trees)

## 局部方法 2：基于划分的方法（决策树）

Partition-based classifier (1/4)

### 基于划分的分类器（1/4）

Computing the prediction for fixed partition
Denote the partition by $c = \bigcup_{j} \gamma_{j}$ with cells $\gamma_{j}$

对固定划分计算预测。用 $c = \bigcup_{j} \gamma_{j}$ 表示划分，其单元为 $\gamma_{j}$。

1. Find the cell $\gamma(x)$ where x falls

   找出 x 所在的单元 $\gamma(x)$。
2. Consider the training data in the cell $\gamma(x)$

   考虑单元 $\gamma(x)$ 中的训练数据。
3. 3 Prediction $\hat{h}(x,c)=$ Majority vote over the training data in cell $\gamma(x)$

   预测 $\hat{h}(x,c)=$：对单元 $\gamma(x)$ 中的训练数据进行多数投票。

![image](<Images/05_NLM/image_018.jpg>)

![image](<Images/05_NLM/image_019.jpg>)

**Partition-based classifier (2/4) Building data-driven partitions**

### 基于划分的分类器（2/4）：构建数据驱动的划分

- Start with all the training data and find a (simple) classifier which minimizes some cost function

  从所有训练数据开始，寻找一个使某个代价函数最小的简单分类器。
- Repeat the process with the subset of training data on each side of the frontier of the classifier $\longrightarrow$ this is called recursive partitioning

  对该分类器边界两侧的训练数据子集重复这一过程，$\longrightarrow$ 这称为递归划分。

![image](<Images/05_NLM/image_020.jpg>)

tree representation

树表示

recursive partitioning of the X-domain

X 定义域的递归划分

**Partition-based classifier (3/4) Hyperparameters**

### 基于划分的分类器（3/4）：超参数

- Cost function optimized locally (at the cell level for the data within the cell)

  局部优化的代价函数：在单元层面，针对单元内的数据优化。
- Number of minimal points in a cell

  每个单元中的最少点数。
- Maximal depth of the tree or total number of cells estimated by pruning the tree - pruning amounts to explore the class of all subpartitions (subtrees) and optimize a penalized criterion of the form

  树的最大深度或单元总数，通过剪枝估计。剪枝相当于探索所有子划分（子树）构成的类，并优化如下惩罚准则：

$$
\arg \min _ {c} \hat {L} _ {n} (h _ {c}) + \lambda | c |
$$

where $c \subset \hat{c}$ is the collection of subpartitions obtained from the learned partition by pruning from bottom to top

其中 $c \subset \hat{c}$ 是从已学得的划分出发、自下而上剪枝得到的子划分集合。

![image](<Images/05_NLM/image_021.jpg>)

- Case of regular partitions with cells which are hypercubes of $\mathbb{R}^d$ with edges of length $\delta_n$ :

  规则划分情形：单元是 $\mathbb{R}^d$ 中边长为 $\delta_n$ 的超立方体。

$$
\mathbb {E} L (\hat {h} (\cdot , \delta_ {n})) \to L ^ {*}
$$

under the condition: $n\delta_{n}^{d} \rightarrow \infty$ and $\delta_{n} \rightarrow 0$ when $n \rightarrow \infty$ (need enough data points in every cell and cell diameter go to zero as sample size grows)

条件为：当 $n \rightarrow \infty$ 时，$n\delta_{n}^{d} \rightarrow \infty$ 且 $\delta_{n} \rightarrow 0$；需要每个单元中有足够多的数据点，并且单元直径随样本量增加而趋于零。

- Case of data-driven partitions : VC and Rademacher theory applies

  数据驱动的划分：VC 理论和 Rademacher 理论适用。

<a id="section-21"></a>

**Take-home message on local methods**

## 关于局部方法的要点

**Major limitations :**

### 主要局限

- The $k$ -Nearest Neighbor method requires to store all the training data in order to predict the label of new entries.

  $k$ 近邻方法需要存储全部训练数据，才能预测新输入的标签。
- Decision trees are extremely unstable.

  决策树极不稳定。
- Both display prediction performance below state-of-the-art methods

  两者的预测性能都低于当时最先进的方法。

Virtue of decision trees :

### 决策树的优点

- Can handle missing/categorical data, scale change

  可以处理缺失数据、类别数据和尺度变化。
- Can be expressed in terms of logical rule $\longrightarrow$ explainable machine learning

  可以表述为逻辑规则，$\longrightarrow$ 可解释机器学习。

What can be saved from decision trees?

决策树中有哪些东西值得保留？

<a id="reading-decision-trees-cart-pruning"></a>

**Supplement — CART Recursive Splitting, Node Impurity Criteria (Gini vs. Entropy vs. Misclassification), and Cost-Complexity Pruning.**

**补充——CART 递归切分、节点不纯度准则（Gini 指数、熵与误分率）以及代价–复杂度剪枝。**

While $k$-NN defines neighborhoods via metric balls centered at test points, **decision trees** partition the input space $\mathbb{R}^d$ into $M = |c|$ disjoint axis-aligned rectangles (cells) $\gamma_1, \dots, \gamma_M$ and predict a constant label inside each leaf $\gamma_j$ by majority vote. Because finding the globally optimal partition of size $M$ is NP-hard, **CART (Classification and Regression Trees, Breiman et al., 1984)** builds the partition greedily from top to bottom via **recursive binary splitting**:

$k$-NN 通过以测试点为中心的度量球定义邻域，而**决策树**则将输入空间 $\mathbb{R}^d$ 划分为 $M = |c|$ 个互不相交的坐标轴对齐超矩形单元（叶子节点）$\gamma_1, \dots, \gamma_M$，并在每个叶子 $\gamma_j$ 内部通过多数投票预测常数标签。由于寻找大小为 $M$ 的全局最优划分是 NP-hard 问题，**CART（分类与回归树，Breiman 等，1984）**采用自顶向下的贪心**递归二元切分**（recursive binary splitting）来构建划分：

- Let $p_{\gamma, k} = \frac{1}{N_\gamma}\sum_{X_i\in\gamma}\mathbb{I}\{Y_i = k\}$ denote the empirical proportion of class $k\in\{1,\dots,C\}$ inside node $\gamma$ (containing $N_\gamma$ training points). At each node $\gamma$, CART searches over all feature indices $j\in\{1,\dots,d\}$ and split thresholds $s\in\mathbb{R}$ (dividing $\gamma$ into $\gamma_L = \{x\in\gamma : x^{(j)} \le s\}$ and $\gamma_R = \{x\in\gamma : x^{(j)} > s\}$) to maximize the **impurity reduction**:

  设 $p_{\gamma, k} = \frac{1}{N_\gamma}\sum_{X_i\in\gamma}\mathbb{I}\{Y_i = k\}$ 为节点 $\gamma$（含 $N_\gamma$ 个训练样本）内属于类别 $k\in\{1,\dots,C\}$ 的经验比例。在每个节点 $\gamma$ 处，CART 遍历所有特征下标 $j\in\{1,\dots,d\}$ 与切分阈值 $s\in\mathbb{R}$（将 $\gamma$ 切分为左子节点 $\gamma_L = \{x\in\gamma : x^{(j)} \le s\}$ 与右子节点 $\gamma_R = \{x\in\gamma : x^{(j)} > s\}$），以最大化**不纯度下降量**：

$$
\Delta I(\gamma \to \gamma_L, \gamma_R) = I(\gamma) - \left(\frac{N_{\gamma_L}}{N_\gamma} I(\gamma_L) + \frac{N_{\gamma_R}}{N_\gamma} I(\gamma_R)\right).
$$

| Impurity Criterion / 节点不纯度准则 | Mathematical Definition $I(\gamma)$ / 数学定义 $I(\gamma)$ | Binary Case ($p = p_{\gamma,1}$) / 二分类形式（$p = p_{\gamma,1}$） | Role in Tree Construction / 在决策树构建中的作用 |
| --- | --- | --- | --- |
| **Misclassification Error** / **分类错误率** | $1 - \max_{k} p_{\gamma, k}$ | $1 - \max(p, 1-p) = \min(p, 1-p)$ | Piecewise linear (not strictly concave); insensitive to changes in class probabilities that do not flip the majority class, so used for **pruning** rather than growing. / 分段线性（非严格凹）；对不改变多数类的概率变化不敏感，因此通常用于**剪枝**而非生长切分。 |
| **Gini Index** / **Gini 指数（CART 默认）** | $\sum_{k=1}^C p_{\gamma, k}(1 - p_{\gamma, k}) = 1 - \sum_{k=1}^C p_{\gamma, k}^2$ | $2p(1-p)$ | Strictly concave quadratic; equals expected error rate if labels inside $\gamma$ were randomly assigned according to $p_{\gamma,k}$. Fast to compute (no logarithms). / 严格凹二次函数；等于按分布 $p_{\gamma,k}$ 在节点内随机指派标签时的期望错误率。无需计算对数，速度快。 |
| **Cross-Entropy / Deviance** / **交叉熵／信息熵（ID3/C4.5）** | $-\sum_{k=1}^C p_{\gamma, k}\log_2 p_{\gamma, k}$ | $-p\log_2 p - (1-p)\log_2(1-p)$ | Strictly concave Shannon entropy; impurity reduction $\Delta I$ equals the **Mutual Information (Information Gain)** between the label and the binary split. / 严格凹的香农熵；不纯度下降量 $\Delta I$ 恰好等于标签与二元切分之间的**互信息（信息增益）**。 |

**Numerical Example & Proof: Why Strictly Concave Impurity (Gini / Entropy) Beats Misclassification Error for Growing Trees（为什么严格凹的 Gini／熵比误分率更适合生长决策树）**

Suppose a parent node $\gamma$ contains $800$ training samples: $400$ of class $+$ and $400$ of class $-$ ($p_\gamma = 0.5$). Compare two candidate splits:

假设父节点 $\gamma$ 含有 $800$ 个训练样本：$400$ 个正类 $+$ 和 $400$ 个负类 $-$（$p_\gamma = 0.5$）。比较如下两个候选切分：

- **Split A**: $\gamma_L$ has $(300+, 100-)$ ($p_L = 0.75$) and $\gamma_R$ has $(100+, 300-)$ ($p_R = 0.25$).
- **Split B**: $\gamma_L$ has $(200+, 400-)$ ($p_L = 1/3$) and $\gamma_R$ has $(200+, 0-)$ ($p_R = 1.0$, a completely pure node!).

Under **Misclassification Error** $I_{\mathrm{err}}(p) = \min(p, 1-p)$:
- Split A: $\frac{400}{800}(0.25) + \frac{400}{800}(0.25) = 0.25$ (200 errors total).
- Split B: $\frac{600}{800}(1/3) + \frac{200}{800}(0) = 0.25$ (200 errors total).
Misclassification error rates both splits identically, even though Split B isolates $200$ points into a $100\%$ pure node that needs no further splitting! Indeed, whenever both child nodes share the same majority class, $I_{\mathrm{err}}$ is linear on $[0, 1/2]$ and $[1/2, 1]$, so by Jensen's equality $\Delta I_{\mathrm{err}} = 0$.

在**误分率** $I_{\mathrm{err}}(p) = \min(p, 1-p)$ 下，切分 A 与切分 B 的加权不纯度均为 $0.25$（总共误分 200 个样本），误分率无法区分二者，尽管切分 B 已经分离出一个含 200 个样本的 $100\%$ 纯净子节点！事实上，当两个子节点保持同一个多数类时，$I_{\mathrm{err}}$ 在 $[0,1/2]$ 或 $[1/2,1]$ 上是线性的，导致 $\Delta I_{\mathrm{err}} = 0$。

Under **Gini Index** $I_{\mathrm{Gini}}(p) = 2p(1-p)$, which is **strictly concave** ($I''_{\mathrm{Gini}}(p) = -4 < 0$):
- Split A: $\frac{400}{800}\big(2\cdot\frac{3}{4}\cdot\frac{1}{4}\big) + \frac{400}{800}\big(2\cdot\frac{1}{4}\cdot\frac{3}{4}\big) = 0.375$.
- Split B: $\frac{600}{800}\big(2\cdot\frac{1}{3}\cdot\frac{2}{3}\big) + \frac{200}{800}(0) = \frac{3}{4}\cdot\frac{4}{9} = 0.333 < 0.375$.
Strict concavity guarantees by Jensen's inequality that $\Delta I(\gamma\to\gamma_L,\gamma_R) > 0$ whenever $p_{\gamma_L} \neq p_{\gamma_R}$, and actively rewards creating pure child nodes that simplify subsequent splits.

而在**严格凹**的 **Gini 指数** $I_{\mathrm{Gini}}(p) = 2p(1-p)$（$I''_{\mathrm{Gini}}(p) = -4 < 0$）下，切分 A 的加权 Gini 为 $0.375$，而切分 B 为 $0.333 < 0.375$。严格凹性由 Jensen 不等式保证了只要 $p_{\gamma_L} \neq p_{\gamma_R}$ 就有 $\Delta I > 0$，并且会优先奖励产生高纯度子节点的切分。

**Cost-Complexity Pruning and Consistency Conditions**:
- Growing a tree too deep leads to tiny leaves (even 1 point per leaf), zero training error, and extreme variance; stopping too early misses splits whose value only appears at the next level (the "horizon effect"). CART therefore grows a large tree $\hat{c}$ and prunes it bottom-up by minimizing the penalized empirical risk $\hat{L}_n(h_c) + \lambda |c|$, where $|c|$ is the number of leaves and $\lambda \ge 0$ is selected by cross-validation.
- For regular hypercube partitions of side length $\delta_n$, a cell has volume $\delta_n^d$, so the expected number of training points falling inside a cell scales as $n\delta_n^d$. Thus the two consistency conditions have the exact same bias–variance interpretation as Stone's conditions for $k$-NN:
  1. $n\delta_n^d \to \infty$: the expected number of training points per cell grows to infinity, driving within-cell estimation **variance** to $0$;
  2. $\delta_n \to \infty$ replaced by $\delta_n \to 0$: the cell diameter $\sqrt{d}\,\delta_n \to 0$, driving local approximation **bias** to $0$.

**代价–复杂度剪枝与一致性条件**：
- 树生长过深会导致叶子节点极小（甚至每个叶子仅 1 个样本）、训练误差为 0 但方差极大；过早停止切分又会错过那些“只有再切一层才能显现收益”的切分（视界效应）。因此 CART 的标准做法是先生成一棵充分大的树 $\hat{c}$，再自底向上最小化惩罚经验风险 $\hat{L}_n(h_c) + \lambda |c|$ 进行剪枝，其中 $|c|$ 为叶子节点总数，$\lambda \ge 0$ 由交叉验证选择。
- 对边长为 $\delta_n$ 的规则超立方体划分，每个单元的体积为 $\delta_n^d$，落入单个单元的期望训练样本数阶为 $n\delta_n^d$。因此其两条一致性条件与 $k$-NN 的 Stone 条件具有完全相同的偏差–方差含义：
  1. $n\delta_n^d \to \infty$：每个单元内的期望样本数趋于无穷，使单元内多数投票的**方差**趋于 $0$；
  2. $\delta_n \to 0$：单元直径 $\sqrt{d}\,\delta_n \to 0$，使分段常数逼近 $\eta(x)$ 的**偏差**趋于 $0$。

<a id="section-22"></a>

Shallow and efficient Machine Learning algorithms : Ensemble methods

## 浅层且高效的机器学习算法：集成方法

1. Bagging and Random Forests

   Bagging 与随机森林。
2. Boosting

   Boosting。

**Motivation for ensembles Pointers to other fields**

### 集成的动机：其他领域的线索

- Technology : the champions in data science competitions combine several methods to boost performance (e.g. BelKor team, winner of the Netflix challenge)

  技术：数据科学竞赛冠军将多种方法组合起来提高性能，例如 Netflix 挑战赛获胜者 BelKor 团队。
- Decision theory : Social choice theory

  决策理论：社会选择理论。
- Probability : Ergodic theorem

  概率论：遍历定理。
- Nonparametric statistics : aggregation estimators

  非参数统计：聚合估计量。

<a id="section-23"></a>

**Ensemble methods Starting point**

## 集成方法：出发点

- Consider we already have a machine learning algorithm with reasonable performance that we want to improve, e.g. decision tree, k-NN, SVM, ...

  假设已有一个性能尚可、希望进一步改进的机器学习算法，例如决策树、k-NN、SVM 等。
- The idea of the ensemble is to generate different functions from the same training data and the same hypothesis space

  集成的思想是：从相同训练数据与相同假设空间产生不同的函数。
- In the illustration coming next and most of the discussion, the basic hypothesis space is the one with decision trees obtained with orthogonal splits (such splits are called decision stumps).

  在接下来的示例及大部分讨论中，基础假设空间由通过正交切分得到的决策树构成；这样的切分称为决策树桩。

<a id="section-24"></a>

**Ensembles of decision trees General principle**

## 决策树集成：一般原理

- Generate a collection of weak predictors (ensemble) obtained with a basic Machine Learning algorithm (e.g. decision tree)

  使用基础机器学习算法，例如决策树，生成一组弱预测器，即集成。
- For every point $x$ , compute their individual predictions

  对每个点 $x$，计算各预测器的预测。
- Take an average or a majority vote of the individual predictions to determine the prediction of the ensemble

  对各预测取平均或多数投票，得到集成的预测。

![image](<Images/05_NLM/image_022.jpg>)

<a id="section-25"></a>

**Ensembles of decision trees Resulting classifier**

## 决策树集成：得到的分类器

![image](<Images/05_NLM/image_023.jpg>)

<a id="section-26"></a>

**Ensembles of decision trees Three popular methods**

## 决策树集成：三种常见方法

- Bagging (Breiman, 1996)

  Bagging（Breiman，1996）。
- Random forests (Amit-Geman, 1997; Breiman, 2000)

  随机森林（Amit–Geman，1997；Breiman，2000）。
- Boosting (Freund-Schapire, 1996)

  Boosting（Freund–Schapire，1996）。

<a id="bagging"></a>

<a id="section-27"></a>

Ensemble methods #1 : Bagging and Random Forests

## 集成方法 1：Bagging 与随机森林

**Bagging and Random Forests What is their hypothesis space?**

### Bagging 与随机森林的假设空间是什么？

- Denote by $\mathcal{H}$ the base hypothesis space (for the not so brilliant algorithm we already have, e.g. decision trees)

  用 $\mathcal{H}$ 表示基础假设空间，对应已有的那个表现不算出色的算法，例如决策树。
- Denote by $D_{n}$ the training data and assume that we can sample functions $\hat{h}_1, \ldots, \hat{h}_t$ (the ensemble) from $\mathcal{H}$ conditionally to $D_{n}$

  用 $D_{n}$ 表示训练数据，并假设在给定 $D_{n}$ 的条件下，能够从 $\mathcal{H}$ 中抽样得到函数 $\hat{h}_1, \ldots, \hat{h}_t$，即集成。
- With an ensemble of $T$ functions, the output of bagging/random forests is the average of those "random" (generated based on the data) functions:

  对由 $T$ 个函数组成的集成，Bagging／随机森林的输出是这些基于数据生成的“随机”函数的平均：

$$
\hat {f} _ {T} = \frac {1}{T} \sum_ {t = 1} ^ {T} \hat {h} _ {t}
$$

- The hypothesis space for those methods is the linear span of the base hypothesis space $\mathcal{H}$ . This can be a huge space!

  这些方法的假设空间是基础假设空间 $\mathcal{H}$ 的线性张成空间。这个空间可能非常大！

> **译注：** 上式实值平均函数属于基础函数类的凸包，因而属于线性张成空间；若随后取符号或最大概率类别，最终离散分类器不必属于这个空间。

- Bagging and random forests rely on bootstrap samples of the training data

  Bagging 与随机森林都依赖对训练数据进行 bootstrap 抽样。
- They differ by some different specifications of the recursive partitioning procedure to build each tree (no pruning involved)

  两者的区别在于构建每棵树时，对递归划分过程作了不同的规定；其中不进行剪枝。

<a id="section-28"></a>

**What is bootstrap in general?**

## 一般而言，bootstrap 是什么？

| Obs | X | Y |
| --- | --- | --- |
| 3 | 5.3 | 2.8 |
| 1 | 4.3 | 2.4 |
| 3 | 5.3 | 2.8 |

| 观测编号 | X | Y |
| --- | --- | --- |
| 3 | 5.3 | 2.8 |
| 1 | 4.3 | 2.4 |
| 3 | 5.3 | 2.8 |

![image](<Images/05_NLM/image_024.jpg>)

| Obs | X | Y |
| --- | --- | --- |
| 1 | 4.3 | 2.4 |
| 2 | 2.1 | 1.1 |
| 3 | 5.3 | 2.8 |

| 观测编号 | X | Y |
| --- | --- | --- |
| 1 | 4.3 | 2.4 |
| 2 | 2.1 | 1.1 |
| 3 | 5.3 | 2.8 |

Original Data (Z)

原始数据（Z）

| Obs | X | Y |
| --- | --- | --- |
| 2 | 2.1 | 1.1 |
| 3 | 5.3 | 2.8 |
| 1 | 4.3 | 2.4 |

| 观测编号 | X | Y |
| --- | --- | --- |
| 2 | 2.1 | 1.1 |
| 3 | 5.3 | 2.8 |
| 1 | 4.3 | 2.4 |

| Obs | X | Y |
| --- | --- | --- |
| 2 | 2.1 | 1.1 |
| 2 | 2.1 | 1.1 |
| 1 | 4.3 | 2.4 |

| 观测编号 | X | Y |
| --- | --- | --- |
| 2 | 2.1 | 1.1 |
| 2 | 2.1 | 1.1 |
| 1 | 4.3 | 2.4 |

- Consistency result for some idealized version of bagging

  某个理想化 Bagging 版本的一致性结果。
- Most important! Bagging can render inconsistent rules consistent!

  最重要的一点：Bagging 可以把不一致的规则变成一致规则！
- Biau, Devroye and Lugosi (2008) have considered bagging applied to 1-NN, given that 1-NN is inconsistent in general classification scenarios (except zero-noise or pure random labels)

  Biau、Devroye 和 Lugosi（2008）研究了将 Bagging 应用于 1-NN。一般分类情形下，1-NN 不一致，零噪声或纯随机标签的情形除外。
- Bagging applied to 1-NN classifier is consistent under some reasonable conditions on the sampling process

  在对采样过程施加某些合理条件后，对 1-NN 分类器进行 Bagging 可以得到一致性。

> **译注：** 上述结论依赖采样条件。“纯随机标签”的例外不能理解为任意与输入独立的标签分布：正负均衡是一个典型例外，类别比例不均衡时 1-NN 不会因此自动达到 Bayes 风险。

<a id="reading-bagging-random-forests-variance"></a>

**Supplement — Bootstrap OOB Probability, the Variance Formula for Correlated Predictors, Random Forests Feature Subsampling, and Biau–Devroye–Lugosi Consistency of Bagged $1$-NN.**

**补充——Bootstrap 袋外（OOB）概率、相关预测器平均的方差公式、随机森林特征子采样，以及 Bagged $1$-NN 的 Biau–Devroye–Lugosi 一致性。**

Deep, unpruned decision trees have **low bias** (they can approximate complex nonlinear boundaries) but **high variance** (small perturbations of the training set $D_n$ change the top split and cascade into completely different trees). **Bagging (Bootstrap Aggregating, Breiman, 1996)** and **Random Forests (Breiman, 2001)** stabilize high-variance base learners primarily by variance reduction:

深层、未剪枝的决策树具有**低偏差**（能够逼近复杂的非线性边界）但**高方差**（训练集 $D_n$ 的微小扰动就可能改变顶层切分，进而连锁产生完全不同的树结构）。**Bagging（Bootstrap 聚合，Breiman，1996）**与**随机森林（Random Forests，Breiman，2001）**主要通过降低方差来稳定这类高方差基学习器：

1. **Bootstrap Sampling & Out-Of-Bag (OOB) Error Estimation**: Each bootstrap dataset $D_n^{(t)}$ draws $n$ observations uniformly **with replacement** from $D_n$. For any specific training point $(X_i, Y_i)$, the probability that it is **never** selected in $n$ independent draws is:

   **Bootstrap 抽样与袋外（Out-Of-Bag, OOB）误差估计**：每个 bootstrap 数据集 $D_n^{(t)}$ 从 $D_n$ 中**有放回**地均匀抽取 $n$ 个样本。对任意给定的训练样本 $(X_i, Y_i)$，它在 $n$ 次独立抽取中**一次也未被抽中**的概率为：

   $$
   \mathbb{P}\!\left((X_i, Y_i) \notin D_n^{(t)}\right) = \left(1 - \frac{1}{n}\right)^n \xrightarrow[n\to\infty]{} e^{-1} \approx 0.3679.
   $$

   Thus, each bootstrap tree uses about $63.2\%$ of the unique training points and leaves out about $36.8\%$ as **Out-Of-Bag (OOB)** samples. By predicting each $(X_i, Y_i)$ using only the $\approx 0.368\,T$ trees for which it was out-of-bag, we obtain a convenient out-of-sample test error estimate (OOB error) without running separate $K$-fold cross-validation (note that because each bootstrap sample contains only $\approx 0.632\,n$ unique observations, OOB error behaves similarly to $K$-fold cross-validation with $K\approx 3$ and can be slightly pessimistic relative to the true risk of an ensemble trained on $n$ unique points).

   因此，每棵 bootstrap 树平均只用到约 $63.2\%$ 的不同训练样本，而留下约 $36.8\%$ 作为**袋外（OOB）样本**。对每个样本 $(X_i, Y_i)$，仅用那些未将其纳入训练集的约 $0.368\,T$ 棵树进行预测并汇总，即可在不额外运行 $K$ 折交叉验证的情况下获得方便的样本外测试误差估计（OOB 误差；注意由于每个 bootstrap 样本仅含约 $0.632\,n$ 个不同样本，OOB 评估行为类似于 $K\approx 3$ 折交叉验证，相对于在 $n$ 个独立样本上训练的模型风险通常略偏保守，不能无条件视为最终模型风险的精确无偏估计）。
2. **Why Random Forests Outperform Plain Bagging (Decorrelating Trees)**: Because all bootstrap samples $D_n^{(1)}, \dots, D_n^{(T)}$ come from the same dataset $D_n$, the trees $\hat{h}_1(x), \dots, \hat{h}_T(x)$ are identically distributed (mean $\mu(x)$, variance $\sigma^2(x)$) but **positively correlated** with pairwise correlation $\rho(x) = \operatorname{Corr}(\hat{h}_t(x), \hat{h}_s(x)) > 0$.

   **为什么随机森林优于普通 Bagging（去相关化）**：由于所有 bootstrap 样本 $D_n^{(1)}, \dots, D_n^{(T)}$ 都抽自同一个训练集 $D_n$，各棵树 $\hat{h}_1(x), \dots, \hat{h}_T(x)$ 虽然同分布（均值为 $\mu(x)$，方差为 $\sigma^2(x)$），但彼此之间存在**正相关**，记两两相关系数为 $\rho(x) = \operatorname{Corr}(\hat{h}_t(x), \hat{h}_s(x)) > 0$。

**Derivation: Variance of the Ensemble Average $\hat{f}_T(x) = \frac{1}{T}\sum_{t=1}^T \hat{h}_t(x)$（集成平均 $\hat{f}_T(x)$ 的方差公式推导）**

By the bilinearity of covariance, for $T$ identically distributed random variables $\hat{h}_1(x), \dots, \hat{h}_T(x)$ with variance $\sigma^2$ and pairwise correlation $\rho$ ($\operatorname{Cov}(\hat{h}_t(x), \hat{h}_s(x)) = \rho\sigma^2$ for $t\neq s$):

由协方差的双线性性质，对 $T$ 个方差为 $\sigma^2$、两两相关系数为 $\rho$（当 $t\neq s$ 时 $\operatorname{Cov}(\hat{h}_t(x), \hat{h}_s(x)) = \rho\sigma^2$）的同分布随机变量 $\hat{h}_1(x), \dots, \hat{h}_T(x)$：

$$
\begin{aligned}
\operatorname{Var}\!\left(\hat{f}_T(x)\right) &= \operatorname{Var}\!\left(\frac{1}{T}\sum_{t=1}^T \hat{h}_t(x)\right) = \frac{1}{T^2}\left[\sum_{t=1}^T \operatorname{Var}(\hat{h}_t(x)) + \sum_{t\neq s} \operatorname{Cov}(\hat{h}_t(x), \hat{h}_s(x))\right] \\
&= \frac{1}{T^2}\Big[T\sigma^2 + T(T-1)\rho\sigma^2\Big] = \frac{\sigma^2}{T} + \left(1 - \frac{1}{T}\right)\rho\sigma^2 \\
&= \underbrace{\rho\,\sigma^2}_{\text{irreducible correlation floor as } T\to\infty} + \underbrace{\frac{1-\rho}{T}\,\sigma^2}_{\text{vanishes as } T\to\infty}.
\end{aligned}
$$

- **Key Takeaway 1 (Behavior as $T\to\infty$)**: Averaging $T$ identically distributed trees leaves the expectation unchanged ($\mathbb{E}[\hat{f}_T(x)] = \mathbb{E}[\hat{h}_1(x)]$) while driving the Monte Carlo sampling variance $\frac{1-\rho}{T}\sigma^2$ to zero as $T\to\infty$; by the Strong Law of Large Numbers (conditional on $D_n$), $\hat{f}_T(x) \to \mathbb{E}[\hat{h}_1(x)\mid D_n]$ as $T\to\infty$, so the test error of the ensemble converges to a finite limit rather than diverging as $T\to\infty$ (note, however, that this variance formula is for the real-valued average $\hat{f}_T(x)$ under squared error and does not imply that 0–1 classification test error is strictly non-increasing at every finite $T$).
- **Key Takeaway 2 (Random Forests' Bias–Variance Trade-off)**: In plain Bagging, if one or two features are very strong predictors, almost every bootstrap tree will select those same features at the root node, making $\rho$ large and limiting the variance reduction. **Random Forests** inject extra randomness at every node split by restricting the split search to a random subset of $m_{\mathrm{try}} \ll d$ features (typically $m_{\mathrm{try}} = \lfloor\sqrt{d}\rfloor$ for classification or $\lfloor d/3\rfloor$ for regression). Although restricting candidate splits to $m_{\mathrm{try}} < d$ can slightly increase the bias of each individual tree $\hat{h}_t$, it substantially lowers inter-tree correlation $\rho$ and shrinks the variance floor $\rho\sigma^2$, usually yielding a net reduction in overall prediction error.

- **核心结论 1（$T\to\infty$ 的渐近性质）**：对 $T$ 棵同分布树取平均不会改变单个重采样树的期望（$\mathbb{E}[\hat{f}_T(x)] = \mathbb{E}[\hat{h}_1(x)]$），同时当 $T\to\infty$ 时将第二项蒙特卡洛方差 $\frac{1-\rho}{T}\sigma^2$ 压向 $0$；由条件于训练集 $D_n$ 的强大数定律，$\hat{f}_T(x) \to \mathbb{E}[\hat{h}_1(x)\mid D_n]$，因此当 $T\to\infty$ 时集成的泛化风险会收敛到有限极限，而不会因 $T$ 增大而发散（但需注意：上式是实值平均预测的方差公式，对于取多数投票符号后的 0–1 分类测试误差，不能由此推出它对任意有限 $T$ 都严格单调不增）。
- **核心结论 2（随机森林的偏差–方差权衡）**：在普通 Bagging 中，如果数据里有一两个极强的预测特征，几乎每棵 bootstrap 树都会在根节点选择相同的特征，导致树间相关系数 $\rho$ 很大，限制了降方差效果。**随机森林**在每个节点切分时，先从 $d$ 个特征中随机抽取 $m_{\mathrm{try}} \ll d$ 个候选特征子集（分类通常取 $m_{\mathrm{try}} = \lfloor\sqrt{d}\rfloor$，回归取 $\lfloor d/3\rfloor$），仅在该子集内寻找最优切分。虽然特征子采样（$m_{\mathrm{try}} < d$）可能略微增加单棵树 $\hat{h}_t$ 的偏差，但它打破了强特征对顶层切分的垄断，显著降低了树间相关性 $\rho$ 并压低渐近方差项 $\rho\sigma^2$，在绝大多数情形下带来总体预测误差的净下降。

3. **How Bagging Turns Inconsistent $1$-NN into a Consistent Classifier (Biau, Devroye & Lugosi, 2008)**:
   Why is $1$-NN generally inconsistent ($L_{\text{1-NN}}^\infty = 2\mathbb{E}[\eta(X)(1-\eta(X))] > L^*$ whenever $\mathbb{P}(\eta(X)\notin\{0,1/2,1\})>0$), yet **bagged $1$-NN** can achieve $\mathbb{E}[L(\hat{f}_{\mathrm{bag}})] \to L^*$? Suppose each bootstrap/subsample draws $m_n$ points from $D_n$ with resampling fraction $q_n = m_n / n$. In a single subsample, the $l$-th nearest neighbor $X_{(l)}$ of $x$ in the full dataset $D_n$ becomes the **$1$-nearest neighbor** in the subsample if and only if $X_{(1)}, \dots, X_{(l-1)}$ are all absent from the subsample and $X_{(l)}$ is present! For small $q_n$, this occurs with probability:

   **Bagging 如何将不一致的 $1$-NN 变为一致分类器（Biau, Devroye & Lugosi, 2008）**：
   为什么单个 $1$-NN 在一般有噪声情形下是不一致的（当 $\mathbb{P}(\eta(X)\notin\{0,1/2,1\})>0$ 时 $L_{\text{1-NN}}^\infty = 2\mathbb{E}[\eta(X)(1-\eta(X))] > L^*$），而**经过 Bagging 的 $1$-NN** 却能达到 Bayes 最优风险 $\mathbb{E}[L(\hat{f}_{\mathrm{bag}})] \to L^*$？设每次重采样从 $D_n$ 中抽取 $m_n$ 个样本（采样率 $q_n = m_n/n$）。在单次重采样样本中，原数据集里距离 $x$ 第 $l$ 近的样本 $X_{(l)}$ 成为该子样本中**第一近邻（$1$-NN）**，当且仅当前 $l-1$ 个更近的样本 $X_{(1)}, \dots, X_{(l-1)}$ 均未被抽中、且 $X_{(l)}$ 被抽中！当 $q_n$ 较小时，其概率（即 $X_{(l)}$ 在无限次重采样投票下获得的权重）约为：

   $$
   w_{n,l} \approx (1 - q_n)^{l-1} q_n.
   $$

   When $m_n \to \infty$ and $q_n = m_n / n \to 0$ (i.e., subsampling at a vanishing fraction rather than standard $m_n = n$), the geometric weights $w_{n,l}$ spread smoothly across the $O(1/q_n) = O(n/m_n) \to \infty$ nearest neighbors of $x$, with $\max_l w_{n,l} = q_n \to 0$. Thus, bagged $1$-NN acts as a **weighted $k_n$-NN classifier** with effective neighborhood size $k_{\mathrm{eff}} \asymp n/m_n \to \infty$ and $k_{\mathrm{eff}}/n \asymp 1/m_n \to 0$, satisfying Stone's universal consistency conditions!

   当重采样规模满足 $m_n \to \infty$ 且采样率 $q_n = m_n / n \to 0$ 时（即采用渐近消失比例的子采样，而非标准 $m_n = n$），几何分布权重 $w_{n,l}$ 会平滑地分摊到 $x$ 周围约 $O(1/q_n) = O(n/m_n) \to \infty$ 个近邻上，且单个近邻的最大权重 $\max_l w_{n,l} = q_n \to 0$。因此，Bagged $1$-NN 在数学上等价于一个**加权 $k_n$-NN 分类器**，其有效近邻数 $k_{\mathrm{eff}} \asymp n/m_n \to \infty$ 且 $k_{\mathrm{eff}}/n \asymp 1/m_n \to 0$，完美满足 Stone 普适一致性定理的双重条件！

<a id="boosting"></a>

<a id="section-29"></a>

Ensemble methods #2 : Boosting

## 集成方法 2：Boosting

**Historical perspective on Boosting**

### Boosting 的历史视角

- Original paper : Freund, Y. and Schapire, R. E. (ICML, 1996).

  原始论文：Freund, Y. 与 Schapire, R. E.（ICML，1996）。
- Interpretation of the optimization problem solved as stochastic gradient descent : Friedman, J. H. (CSDA, 2002).

  将所求解的优化问题解释为随机梯度下降：Friedman, J. H.（CSDA，2002）。
- Wald Memorial lecture (IMS, 2000): Leo Breiman declares that "understanding Boosting is the most important problem in Machine Learning"

  Wald 纪念讲座（IMS，2000）：Leo Breiman 宣称，“理解 Boosting 是机器学习中最重要的问题”。
- Proof of boosting consistency : Lugosi, G. and Vayatis, N. (Special issue with discussion of the Annals of Statistics, 2004).

  Boosting 一致性的证明：Lugosi, G. 与 Vayatis, N.（Annals of Statistics 含讨论的专刊，2004）。
- Xgboost, a scalable implementation : Chen, T. and Guestrin, C. (ACM SIGKDD, 2016).

  可扩展的实现 XGBoost：Chen, T. 与 Guestrin, C.（ACM SIGKDD，2016）。
- Input

  输入：
- Data sample $D_{n} = \{(X_{i}, Y_{i}) : i = 1, \dots, n\}$ with classification data $\{-1, +1\}$

  数据样本 $D_{n} = \{(X_{i}, Y_{i}) : i = 1, \dots, n\}$，其中分类数据满足 $\{-1, +1\}$。
- Base hypothesis class $\mathcal{H}$ of weak classifiers such as decision trees (assumed to be symmetric, i.e. $h \in \mathcal{H}$ iff $-h \in \mathcal{H}$ )

  弱分类器的基础假设类 $\mathcal{H}$，例如决策树；假设该类对称，即 $h \in \mathcal{H}$ 当且仅当 $-h \in \mathcal{H}$。
- Iterations $t = 1, \ldots, T$ .

  迭代 $t = 1, \ldots, T$。
- Compute weights $w_{t} > 0$ and weak classifiers $\widehat{h}_{t} \in H$

  计算权重 $w_{t} > 0$ 与弱分类器 $\widehat{h}_{t} \in H$。
- Output.

  输出：
- The Boosting classifier takes the sign of the following linear combination of weak classifiers: $\widehat{f}_n(x) = \sum_{t=1}^{T} w_t \widehat{h}_t(x)$

  Boosting 分类器对如下弱分类器线性组合取符号：$\widehat{f}_n(x) = \sum_{t=1}^{T} w_t \widehat{h}_t(x)$。
- Boosting distributions on the data : sequence of discrete probability distributions over $\{1, \ldots, n\}$ denoted by $\Pi_t$ , $t \geq 1$

  数据上的 Boosting 分布：定义在 $\{1, \ldots, n\}$ 上的一列离散概率分布，记为 $\Pi_t$，$t \geq 1$。
- Weighted training error: for any weak classifier $h \in \mathcal{H}$ and for $t \geq 1$

  加权训练误差：对任意弱分类器 $h \in \mathcal{H}$，以及 $t \geq 1$，

$$
\widehat {\varepsilon} _ {t} (h) = \sum_ {i = 1} ^ {n} \Pi_ {t} (i) \mathbb {I} \{h (X _ {i}) \neq Y _ {i} \}
$$

Boosting (3/7)

### Boosting（3/7）

Original Algorithm : AdaBoost

原始算法：AdaBoost。

1. Initialization. $\Pi_{1}$ is the uniform distribution on $\{1,\ldots,n\}$

   初始化：$\Pi_{1}$ 是 $\{1,\ldots,n\}$ 上的均匀分布。
2. Boosting iterations. For $t = 1, \ldots, T$ , find the weak classifier such that :

   Boosting 迭代：对 $t = 1, \ldots, T$，寻找满足下式的弱分类器：

$$
\widehat {h} _ {t} = \underset {h \in \mathcal {H}} {\arg \min} \widehat {\varepsilon} _ {t} (h)
$$

then set $e_{t}=\widehat{\varepsilon}_{t}(\widehat{h}_{t})$ and take the weight to be

然后令 $e_{t}=\widehat{\varepsilon}_{t}(\widehat{h}_{t})$，并取权重为

$$
w _ {t} = \frac {1}{2} \log \left(\frac {1 - e _ {t}}{e _ {t}}\right)
$$

3. Boosting distribution update. For any $i = 1, \ldots, n$ ,

   更新 Boosting 分布：对任意 $i = 1, \ldots, n$，

$$
\Pi_ {t + 1} (i) \propto \Pi_ {t} (i) \exp \left(- w _ {t} Y _ {i} \cdot \widehat {h} _ {t} (X _ {i})\right)
$$

![image](<Images/05_NLM/image_025.jpg>)

![image](<Images/05_NLM/image_026.jpg>)

![image](<Images/05_NLM/image_027.jpg>)

![image](<Images/05_NLM/image_028.jpg>)

![image](<Images/05_NLM/image_029.jpg>)

- Boosting can be interpreted as a functional gradient descent on the following functional :

  Boosting 可以解释为针对如下泛函进行的函数空间梯度下降：

$$
\hat {A} _ {n} (f) = \frac {1}{n} \sum_ {i = 1} ^ {n} \exp \left(- Y _ {i} f (X _ {i})\right)
$$

where f is taken in a hypothesis space which is the linear span of 'simple' set H of classifiers.

其中 f 所在的假设空间，是“简单”分类器集合 H 的线性张成空间。

- Exercise : why ?

  练习：为什么？

Refer to : J. Friedman, ?Greedy Function Approximation : A Gradient Boosting Machine?, The Annals of Statistics, Vol. 29, No. 5, 2001.

参见：J. Friedman，Greedy Function Approximation: A Gradient Boosting Machine（贪心函数逼近：梯度提升机），The Annals of Statistics，第 29 卷第 5 期，2001。

**Boosting (6/7)**

### Boosting（6/7）

**Hyperparameters for Gradient Boosting**

#### 梯度提升的超参数

- The number $T$ of iterations: the bigger, the higher the chance of overfitting.

  迭代次数 $T$：越大，过拟合的可能性越高。
- The stepsize $\eta$ is fixed: decreasing learning rate tends to improve generalization performance.

  步长 $\eta$ 固定：降低学习率往往可以改善泛化性能。

![image](<Images/05_NLM/image_030.jpg>)

Boosting (7/7)
A mystery not fully explained yet...

### Boosting（7/7）：尚未完全解释的谜题

The test error continues to drop along the iterations even though the training error is zero $\longrightarrow$ Regularization effect thanks to averaging ? ?

尽管训练误差已经为零，测试误差仍随迭代继续下降。$\longrightarrow$ 是平均带来的正则化效应吗？？

![image](<Images/05_NLM/image_031.jpg>)

- Python : scikit-learn

  Python：scikit-learn。
- R：
- rpart : recursive partitioning

  rpart：递归划分。
- caret : classification and regression training (SVM, random forest...)

  caret：分类与回归训练（SVM、随机森林等）。
- xgboost : extreme gradient boosting

  xgboost：极端梯度提升。

<a id="reading-boosting-adaboost-functional-gd"></a>

**Supplement — Solution to the Exercise ("Why is AdaBoost Functional Gradient Descent?"), Margin Theory of Boosting, and Bagging vs. Boosting.**

**补充——课件练习解答（“为什么 AdaBoost 是函数空间梯度下降？”）、Boosting 的间隔理论，以及 Bagging 与 Boosting 的对比。**

In contrast to Bagging—which trains deep, low-bias, high-variance trees **in parallel** on independent bootstrap samples to reduce **variance**—**Boosting** trains shallow, high-bias, low-variance weak learners (such as decision stumps or depth-2 trees) **sequentially** on adaptively reweighted versions of the training data, primarily reducing **bias** by building an additive expansion $f_T(x) = \sum_{t=1}^T w_t \hat{h}_t(x)$.

与在独立 bootstrap 样本上**并行**训练深层（低偏差、高方差）树以降低**方差**的 Bagging 相反，**Boosting** 在自适应重加权的训练数据上**串行**训练浅层（高偏差、低方差）弱学习器（如决策树桩或深度为 2 的浅树），通过构造加法展开 $f_T(x) = \sum_{t=1}^T w_t \hat{h}_t(x)$ 来重点降低**偏差**。

**Complete Proof (Solution to the Slide Exercise): Equivalence of AdaBoost and Stagewise Functional Optimization on Exponential Loss（课件练习完整证明——AdaBoost 与指数损失函数空间前向分步优化的等价性）**

Consider the empirical exponential risk functional $\hat{A}_n(f) = \frac{1}{n}\sum_{i=1}^n \exp(-Y_i f(X_i))$ where $Y_i \in \{-1, +1\}$ and $h \in \mathcal{H}$ takes values in $\{-1, +1\}$. At iteration $t$, given the current ensemble $f_{t-1}(x) = \sum_{s=1}^{t-1} w_s \hat{h}_s(x)$, **forward stagewise additive modeling** seeks the next weak learner $\hat{h}_t \in \mathcal{H}$ and step size $w_t > 0$ that greedily minimize $\hat{A}_n(f_{t-1} + w h)$:

考虑经验指数风险泛函 $\hat{A}_n(f) = \frac{1}{n}\sum_{i=1}^n \exp(-Y_i f(X_i))$，其中 $Y_i \in \{-1, +1\}$，弱分类器 $h \in \mathcal{H}$ 取值于 $\{-1, +1\}$。在第 $t$ 步迭代时，给定当前集成函数 $f_{t-1}(x) = \sum_{s=1}^{t-1} w_s \hat{h}_s(x)$，**前向分步加法模型**（forward stagewise additive modeling）贪心地寻找下一个弱分类器 $\hat{h}_t \in \mathcal{H}$ 与步长 $w_t > 0$，以最小化 $\hat{A}_n(f_{t-1} + w h)$：

$$
(\hat{h}_t, w_t) = \arg\min_{h\in\mathcal{H},\, w > 0} \frac{1}{n}\sum_{i=1}^n \exp\!\Big(-Y_i\big(f_{t-1}(X_i) + w\,h(X_i)\big)\Big).
$$

**Step 1: Unrolling the AdaBoost weights $\Pi_t(i)$**.
Define the unnormalized sample weight $\tilde{\Pi}_t(i) = \exp(-Y_i f_{t-1}(X_i))$ and normalized distribution $\Pi_t(i) = \tilde{\Pi}_t(i) / Z_t$ where $Z_t = \sum_{j=1}^n \tilde{\Pi}_t(j)$. Since $f_t(X_i) = f_{t-1}(X_i) + w_t \hat{h}_t(X_i)$, we have:

**第一步：展开 AdaBoost 样本权重 $\Pi_t(i)$**。
定义未归一化样本权重 $\tilde{\Pi}_t(i) = \exp(-Y_i f_{t-1}(X_i))$ 及归一化分布 $\Pi_t(i) = \tilde{\Pi}_t(i) / Z_t$（其中 $Z_t = \sum_{j=1}^n \tilde{\Pi}_t(j)$）。由于 $f_t(X_i) = f_{t-1}(X_i) + w_t \hat{h}_t(X_i)$，必有：

$$
\tilde{\Pi}_{t+1}(i) = \exp\!\big(-Y_i f_t(X_i)\big) = \tilde{\Pi}_t(i)\exp\!\big(-w_t Y_i \hat{h}_t(X_i)\big) \implies \Pi_{t+1}(i) \propto \Pi_t(i)\exp\!\big(-w_t Y_i \hat{h}_t(X_i)\big),
$$

which is **identical** to Step 3 of AdaBoost! Moreover, the functional gradient of $\hat{A}_n(f)$ evaluated at the training points $(X_1,\dots,X_n)$ is:

这与 AdaBoost 的**第 3 步分布更新公式完全一致**！此外，泛函 $\hat{A}_n(f)$ 在训练样本点 $(X_1,\dots,X_n)$ 处的负梯度为：

$$
-\frac{\partial \hat{A}_n(f)}{\partial f(X_i)}\Bigg|_{f = f_{t-1}} = \frac{1}{n} Y_i \exp\!\big(-Y_i f_{t-1}(X_i)\big) \propto Y_i\,\Pi_t(i).
$$

Thus, $\Pi_t(i)$ is the exact magnitude of the point-wise functional gradient at sample $i$.

因此，权重 $\Pi_t(i)$ 恰好是样本 $i$ 处函数空间负梯度的模长。

**Step 2: Finding the optimal weak classifier $\hat{h}_t$**.
Dividing the stagewise objective by the constant $Z_t / n$, we want to minimize:

**第二步：求解最优弱分类器 $\hat{h}_t$**。
将分步目标函数除以常数 $Z_t/n$，等价于最小化：

$$
J(h, w) = \sum_{i=1}^n \Pi_t(i) \exp\!\big(-w Y_i h(X_i)\big).
$$

Since $Y_i, h(X_i) \in \{-1, +1\}$, their product $Y_i h(X_i)$ equals $+1$ if $h(X_i) = Y_i$ and $-1$ if $h(X_i) \neq Y_i$. Splitting the sum into correctly and incorrectly classified points gives:

因为 $Y_i, h(X_i) \in \{-1, +1\}$，当 $h(X_i) = Y_i$ 时乘积 $Y_i h(X_i) = +1$；当 $h(X_i) \neq Y_i$ 时 $Y_i h(X_i) = -1$。将求和拆分为分类正确与分类错误两部分：

$$
\begin{aligned}
J(h, w) &= e^{-w} \sum_{i:\,h(X_i)=Y_i} \Pi_t(i) + e^{w} \sum_{i:\,h(X_i)\neq Y_i} \Pi_t(i) \\
&= e^{-w}\big(1 - \hat{\varepsilon}_t(h)\big) + e^{w}\,\hat{\varepsilon}_t(h) = e^{-w} + \big(e^{w} - e^{-w}\big)\,\hat{\varepsilon}_t(h),
\end{aligned}
$$

where $\hat{\varepsilon}_t(h) = \sum_{i=1}^n \Pi_t(i)\mathbb{I}\{h(X_i) \neq Y_i\}$ is the weighted training error. Because $e^w - e^{-w} > 0$ for any $w > 0$, minimizing $J(h, w)$ over $h \in \mathcal{H}$ is **independent of $w$** and reduces to:

其中 $\hat{\varepsilon}_t(h) = \sum_{i=1}^n \Pi_t(i)\mathbb{I}\{h(X_i) \neq Y_i\}$ 即加权训练误差。由于对任意 $w > 0$ 都有 $e^w - e^{-w} > 0$，关于 $h \in \mathcal{H}$ 最小化 $J(h, w)$ **与 $w$ 无关**，直接化简为：

$$
\hat{h}_t = \arg\min_{h\in\mathcal{H}} \hat{\varepsilon}_t(h),
$$

which is **identical** to Step 2a of AdaBoost! (Notice also that maximizing the inner product $\sum_{i=1}^n \big(-\frac{\partial \hat{A}_n}{\partial f(X_i)}\big) h(X_i) \propto \sum_{i=1}^n \Pi_t(i) Y_i h(X_i) = 1 - 2\hat{\varepsilon}_t(h)$ gives the exact same $\hat{h}_t$: choosing the weak classifier most aligned with the negative functional gradient.)

这与 AdaBoost 的**第 2a 步完全一致**！（同时注意到，最大化负梯度与基函数的内积 $\sum_{i=1}^n \big(-\frac{\partial \hat{A}_n}{\partial f(X_i)}\big) h(X_i) \propto \sum_{i=1}^n \Pi_t(i) Y_i h(X_i) = 1 - 2\hat{\varepsilon}_t(h)$ 同样等价于最小化 $\hat{\varepsilon}_t(h)$，即寻找与函数空间负梯度方向最对齐的弱分类器。）

**Step 3: Finding the optimal step size (line search) $w_t$**.
Let $e_t = \hat{\varepsilon}_t(\hat{h}_t) \in (0, 1/2)$ (assuming $\hat{h}_t$ is strictly better than random guessing; if $e_t > 1/2$, symmetry of $\mathcal{H}$ lets us replace $\hat{h}_t$ by $-\hat{h}_t$ with error $1 - e_t < 1/2$). Differentiating $J(\hat{h}_t, w) = (1 - e_t)e^{-w} + e_t e^w$ with respect to $w$ and setting to zero yields:

**第三步：求解最优步长（精确线搜索）$w_t$**。
记 $e_t = \hat{\varepsilon}_t(\hat{h}_t) \in (0, 1/2)$（假设弱分类器严格优于随机猜测；若 $e_t > 1/2$，由 $\mathcal{H}$ 的对称性取 $-\hat{h}_t$ 即可使误差变为 $1 - e_t < 1/2$）。将 $J(\hat{h}_t, w) = (1 - e_t)e^{-w} + e_t e^w$ 对 $w$ 求导并令其为零：

$$
\frac{\partial J(\hat{h}_t, w)}{\partial w} = -(1 - e_t)e^{-w} + e_t e^w = 0 \iff e^{2w} = \frac{1 - e_t}{e_t} \iff w_t = \frac{1}{2}\log\!\left(\frac{1 - e_t}{e_t}\right),
$$

which is **identical** to Step 2b of AdaBoost! Furthermore, plugging $w_t$ back into $J(\hat{h}_t, w_t)$ gives $J(\hat{h}_t, w_t) = 2\sqrt{e_t(1 - e_t)}$, so the empirical training error is upper-bounded by:

这与 AdaBoost 的**第 2b 步权重公式完全一致**！更进一步，将 $w_t$ 代回可得 $J(\hat{h}_t, w_t) = 2\sqrt{e_t(1 - e_t)}$；若记 $\gamma_t = \frac{1}{2} - e_t > 0$ 为弱分类器优于随机猜测的边际优势，利用 $1 - 4\gamma_t^2 \le e^{-4\gamma_t^2}$ 可得训练集 0–1 误差的指数衰减上界：

$$
\hat{L}_n(\hat{f}_T) \le \hat{A}_n(\hat{f}_T) = \prod_{t=1}^T 2\sqrt{e_t(1 - e_t)} = \prod_{t=1}^T \sqrt{1 - 4\gamma_t^2} \le \exp\!\left(-2\sum_{t=1}^T \gamma_t^2\right).
$$

**Explaining the "Boosting Mystery" (Margin Theory of Schapire et al., 1998, and Its Qualifications)**:
Why does the test error of AdaBoost often continue to decrease after the training error $\hat{L}_n(\hat{f}_T)$ has already hit $0$? Schapire, Freund, Bartlett & Lee (1998) proposed an explanation based on the **normalized classification margin** $\operatorname{margin}_T(X_i, Y_i) := \frac{Y_i \hat{f}_T(X_i)}{\sum_{t=1}^T w_t} \in [-1, +1]$:
- The 0–1 training error $\hat{L}_n(\hat{f}_T)$ only records whether $\operatorname{margin}_T(X_i, Y_i) > 0$, ignoring how close points are to the decision boundary. Schapire et al. (1998) proved that the test error is upper-bounded by the empirical fraction of training points with normalized margin $\le \theta$ plus a complexity penalty $O(\sqrt{V / (n\theta^2)})$, and that if every weak learner achieves edge $\gamma_t = \frac{1}{2} - e_t \ge \gamma > 0$, the fraction of training points with $\operatorname{margin}_T(X_i, Y_i) \le \theta$ decays to zero exponentially fast in $T$ for any $\theta < \frac{\gamma}{1+\gamma}$.
- **Important qualification (Rudin, Daubechies & Schapire, 2004)**: Note that while the unnormalized exponential risk $\hat{A}_n(\hat{f}_T)$ decreases monotonically with $T$, the normalization denominator $\sum_{t=1}^T w_t$ also grows with $T$. Consequently, decreasing $\hat{A}_n(\hat{f}_T)$ does **not** guarantee that the normalized margin distribution improves monotonically at every step, nor does AdaBoost necessarily converge to the maximum-$\ell_1$-margin combined classifier (Rudin et al., 2004 showed that AdaBoost can enter periodic cycles with suboptimal asymptotic margin). Moreover, if the data contain severe label noise / outliers, exponential loss $\exp(-Y_i f(X_i))$ assigns massive weights to mislabeled points, so large $T$ can eventually overfit noisy data unless regularized via step-size shrinkage ($\eta < 1$) or early stopping.

**解释“Boosting 谜题”（Schapire 等，1998 的间隔理论及其适用边界）**：
为什么当训练误差 $\hat{L}_n(\hat{f}_T)$ 已经降为 $0$ 后，AdaBoost 的测试误差在实际中往往还会随迭代继续下降？Schapire、Freund、Bartlett 与 Lee（1998）基于**归一化分类间隔** $\operatorname{margin}_T(X_i, Y_i) := \frac{Y_i \hat{f}_T(X_i)}{\sum_{t=1}^T w_t} \in [-1, +1]$ 提出了经典解释：
- 0–1 训练误差 $\hat{L}_n(\hat{f}_T)$ 只检查 $\operatorname{margin}_T(X_i, Y_i)$ 是否大于 $0$，而不区分样本离边界有多远。Schapire 等（1998）证明，组合分类器的真实风险可由训练集中满足 $\operatorname{margin}_T(X_i, Y_i) \le \theta$ 的经验比例加上复杂度项 $O(\sqrt{V/(n\theta^2)})$ 上界控制；且当每步弱分类器的优势满足 $\gamma_t = \frac{1}{2} - e_t \ge \gamma > 0$ 时，对任意 $\theta < \frac{\gamma}{1+\gamma}$，训练集中归一化间隔小于等于 $\theta$ 的样本比例会随 $T$ 呈指数衰减。
- **重要补充说明（Rudin, Daubechies & Schapire, 2004）**：需要注意的是，虽然未归一化的经验指数损失 $\hat{A}_n(\hat{f}_T)$ 随 $T$ 单调下降，但归一化间隔的分母 $\sum_{t=1}^T w_t$ 也在随 $T$ 增长，因此不能由 $\hat{A}_n(\hat{f}_T)$ 下降直接推出归一化间隔分布必然在每一步单调改善；事实上，Rudin 等（2004）证明了 AdaBoost 并不总是收敛到最大 $\ell_1$ 间隔组合分类器（可能进入次优间隔的周期循环）。此外，当数据存在较强标签噪声或离群点时，指数损失 $\exp(-Y_i f(X_i))$ 会给错标样本赋予极大权重，此时过大的 $T$ 仍会过拟合噪声，因此实践中常配合步长收缩率（$\eta < 1$）或早停法（early stopping）进行正则化。

| Dimension / 对比维度 | Bagging / Random Forests / Bagging／随机森林 | Boosting (AdaBoost / Gradient Boosting) / Boosting（AdaBoost／梯度提升） |
| --- | --- | --- |
| **Base Learner Choice** / **基学习器选择** | Deep, unpruned trees (**low bias, high variance**) / 深层未剪枝树（**低偏差、高方差**） | Shallow trees / decision stumps (**high bias, low variance**) / 浅层树／决策树桩（**高偏差、低方差**） |
| **Training Coupling** / **训练耦合方式** | **Parallel & independent** on bootstrap samples $D_n^{(t)}$ / 在各自 bootstrap 样本 $D_n^{(t)}$ 上**并行、独立**训练 | **Sequential & adaptive**: $\hat{h}_t$ focuses on errors/residuals of $f_{t-1}$ / **串行、自适应**：$\hat{h}_t$ 专门针对 $f_{t-1}$ 的错分样本或残差 |
| **Ensemble Combination** / **集成聚合方式** | Uniform average $\frac{1}{T}\sum_{t=1}^T \hat{h}_t(x)$ / 等权平均 $\frac{1}{T}\sum_{t=1}^T \hat{h}_t(x)$ | Weighted additive expansion $\sum_{t=1}^T w_t \hat{h}_t(x)$ / 加权线性组合 $\sum_{t=1}^T w_t \hat{h}_t(x)$ |
| **Primary Statistical Effect** / **主要统计作用** | Primarily reduces **variance** ($\frac{1-\rho}{T}\sigma^2 \to 0$ as $T\to\infty$; ensemble converges to $\mathbb{E}[\hat{h}_1\mid D_n]$) / 主要降低**方差**（当 $T\to\infty$ 时 $\frac{1-\rho}{T}\sigma^2 \to 0$，集成预测收敛于 $\mathbb{E}[\hat{h}_1\mid D_n]$） | Primarily reduces **bias** (and often improves empirical margins); can overfit noisy data if $T$ is too large / 主要降低**偏差**（并常能改善经验间隔分布）；在有噪声时 $T$ 过大可能过拟合 |

<a id="surrogate-loss"></a>

<a id="section-30"></a>

Les principes inférentiels

## 推断原则

- Une mesure d'erreur :

  一种误差度量：

$$
L (g) = \mathbb {P} \left\{Y \cdot g (X) <   0 \right\} = \mathbb {E} \left(\mathbb {I} _ {[ Y \cdot g (X) <   0 ]}\right)
$$

- Classifieur et erreur de Bayes :

  Bayes 分类器与 Bayes 误差：

$$
\begin{array}{r l} {g ^ {*}} & {= \underset {g} {\arg \min} L (g) = \operatorname{sgn} \left(\eta - \frac {1}{2}\right)} \\ {L ^ {*}} & {= L (g ^ {*})} \end{array}
$$

- Critère empirique :

  经验准则：

$$
\hat {L} _ {n} (g) = \frac {1}{n} \sum_ {i = 1} ^ {n} \mathbb {I} _ {[ Y _ {i} \cdot g (X _ {i}) <   0 ]}
$$

<a id="section-31"></a>

**Minimisation du risque empirique (ERM)**

## 经验风险最小化（ERM）

La théorie de Vapnik ('95 → ) a permis de développer des stratégies consistantes pour la classification de données en grande dimension.

Vapnik 的理论（1995 年起）使人们能够发展针对高维数据分类的一致策略。

**Inconvénients de l'ERM**

### ERM 的缺点

- algorithmique : problème NP-difficile .

  算法方面：NP-hard 问题。
- contrôle de la complexité : propriété de Glivenko-Cantelli pour éviter le surapprentissage (overfitting).

  复杂度控制：需要 Glivenko–Cantelli 性质以避免过拟合。

**Mais :**

### 但是

Les méthodes efficaces construisent les estimateurs dans des classes massives!

高效方法在非常庞大的函数类中构建估计量！

<a id="section-32"></a>

**Algorithms efficaces**

## 高效算法

**① Support Vector Machines - Vapnik (1995)**

### 1. 支持向量机：Vapnik（1995）

- Kernel trick : envoyer les données dans un espace de Hilbert où les données soient (presque) linéairement séparables

  核技巧：将数据映射到一个 Hilbert 空间，使数据在其中近似线性可分。
- Hyperplan à marge maximale : optimization convexe sous contraintes quadratiques

  最大间隔超平面：带二次约束的凸优化。

> **译注：** 按前文标准软间隔 SVM 的表述，目标是凸二次函数，约束为线性不等式；原文此处“二次约束”的说法不准确。

**② Boosting - Freund (1990) - Freund, Schapire (1996)**

### 2. Boosting：Freund（1990）；Freund、Schapire（1996）

- on commence avec une classe H de classifieurs simples

  从简单分类器的类 H 开始。
- puis on construit itérativement une combinaison linéaire de classifieurs simples qui fait décroître l'erreur empirique

  然后迭代构造简单分类器的线性组合，使经验误差下降。

"Boosting is the best off-the-shelf classifier in the world" - Breiman, 1996.

“Boosting 是世界上最好的开箱即用分类器。”——Breiman，1996。

Caractéristique commune

### 共同特征

Si on fait abstraction :

如果暂不考虑：

1. 1 des intuitions géometriques

   几何直觉；
2. de la dynamique particulière de chaque algorithme, alors :

   各算法特有的动态过程，那么：

Boosting et SVM peuvent s'envisager comme des :

Boosting 与 SVM 都可以看作：

**procédures de minimisation d'un risque convexe pénalisé dans des espaces fonctionnels massifs.**

### 在庞大的函数空间中最小化带惩罚的凸风险的过程。

Elles sont caractérisées par

它们的区别在于：

- des classes d'estimateurs différentes,

  估计量所属的类不同。
- des risques différents,

  风险不同。
- des pénalités différentes.

  惩罚项不同。
- Support Vector Machines - soit k un noyau positif

  支持向量机：设 k 为正定核。

$$
\mathcal {F} = \left\{f = \sum_ {i = 1} ^ {+ \infty} \alpha_ {i} k (x _ {i}, \cdot): \alpha_ {i} \in \mathbb {R}, x _ {i} \in \mathcal {X} \right\}
$$

- Boosting - soit $\mathcal{G}$ famille de classifieurs simples de VC dimension $V$ finie

  Boosting：设 $\mathcal{G}$ 是 VC 维 $V$ 有限的简单分类器族。

$$
\mathcal {F} = \left\{f = \sum_ {i = 1} ^ {+ \infty} w _ {i} g _ {i}: w _ {i} \in \mathbb {R}, g _ {i} \in \mathcal {G} \right\}
$$

Les deux algorithmes construisent des combinaisons linéaires de fonctions.

两种算法都构造函数的线性组合。

> **译注：** 若使用无限和定义函数类，需要另行规定收敛条件；这里只是原课件对函数空间的简写。

Cas des SVM - Retour sur la formulation lagrangienne l

### SVM 的情形：回到拉格朗日表述 I

On pose

设

$$
f (x) = \sum_ {i = 1} ^ {n} \alpha_ {i} k (x _ {i}, x)
$$

$$
\| f \| _ {\mathcal {F}} = \sqrt {\sum_ {i , j} \alpha_ {i} \alpha_ {j} k (x _ {i} , x _ {j})}
$$

Formulation lagrangienne I

### 拉格朗日表述 I

$$
\min _ {f \in \mathcal {F}} \frac {1}{2} \| f \| _ {\mathcal {F}} ^ {2} + C \sum_ {i = 1} ^ {n} \xi_ {i}
$$

sous les contraintes :

约束条件：

$$
\forall i = 1, \dots , n, \quad \xi_ {i} \geq \left(1 - y _ {i} \cdot f (x _ {i})\right) _ {+}
$$

On pose : $\varphi(x)=(1+x)_{+}$ "hinge loss"

设 $\varphi(x)=(1+x)_{+}$，称为 hinge loss（合页损失）。

Minimisation d'un risque pénalisé

### 惩罚风险的最小化

$$
\min _ {f \in \mathcal {F}} \frac {1}{2} \| f \| _ {\mathcal {F}} ^ {2} + C \sum_ {i = 1} ^ {n} \varphi (- y _ {i} f (x _ {i}))
$$

**Commentaires :**

### 说明

- formulation importante pour la théorie statistique

  这一表述对统计理论很重要。
- moins commode pour l'optimisation que la formulation duale

  对优化而言，它不如对偶表述方便。
- $\|f\|_{\mathcal{F}}$ fournit une mesure de régularité de $f$

  $\|f\|_{\mathcal{F}}$ 提供了对 $f$ 正则性的度量。
- Fonction de décision :

  决策函数：

$$
f: \mathcal {X} \to \mathbb {R}
$$

- Classifieur :

  分类器：

$$
g (x) = g _ {f} (x) = \operatorname{sgn} (f (x)) \in \{- 1, + 1 \}
$$

- Critère naturel :

  自然的准则：

$$
L (f) = \mathbb {P} \left\{Y \cdot f (X) <   0 \right\} = \mathbb {E} \left\{\mathbb {I} _ {[ Y \cdot f (X) <   0 ]} \right\}
$$

- Fonction de perte : $\varphi$ convexe, positive, telle que $\varphi(x) \geq \mathbb{I}_{\mathbb{R}_+}(x)$

  损失函数：$\varphi$ 凸、非负，并且满足 $\varphi(x) \geq \mathbb{I}_{\mathbb{R}_+}(x)$。
- Critère pratique ( $\varphi$ -risque) :

  实用准则（$\varphi$ 风险）：

$$
\begin{array}{r l} A (f) & = \mathbb {E} \varphi (- Y f (X)) \\ & = \mathbb {E} \left[ \eta (X) \varphi (- f (X)) + (1 - \eta (X)) \varphi (f (X)) \right] \end{array}
$$

其中 $\eta(X)=\mathbb P\{Y=1\mid X=x\}$。

> **译注：** 原页等号左侧写 $\eta(X)$，右侧使用固定输入 x；定义应统一写成 $\eta(x)=\mathbb P(Y=1\mid X=x)$。

Question : minimiser A revient-il à minimiser L ?

问题：最小化 A 是否等价于最小化 L？

On a seulement que : $L(f) \leq A(f)...$

仅有如下关系：$L(f) \leq A(f)...$。

![image](<Images/05_NLM/image_032.jpg>)

Fonctions cibles

### 目标函数

- Minimiseur de la fonctionnelle $A$ noté $f^{*}$

  泛函 $A$ 的极小点记为 $f^{*}$。
- Minimum du $\varphi$ -risque : $A^{*} = \min_{f} A(f) = A(f^{*})$

  最小 $\varphi$ 风险：$A^{*} = \min_{f} A(f) = A(f^{*})$。
- On peut montrer que $\operatorname{sgn}(f^{*}) = g^{*}$ le classifieur optimal

  可以证明，$\operatorname{sgn}(f^{*}) = g^{*}$ 是最优分类器。
- On peut également montrer que l'excès de risque en erreur de classification $L(f) - L^*$ est contrôlé par $A(f) - A^*$

  还可以证明，分类误差的超额风险 $L(f) - L^*$ 由 $A(f) - A^*$ 控制。

> **译注：** 分类校准结论需要对替代损失施加额外条件，不能仅由凸、非负、上界 0/1 损失推出。以下指数损失和 hinge 损失是具体例子；边界概率和并列最优情形还需单独处理。

- Exemples :

  例子：
- perte exponentielle (boosting)

  指数损失（Boosting）。

$$
f ^ {*} (x) = \frac {1}{2} \log \left(\frac {\eta (x)}{1 - \eta (x)}\right)
$$

- "hinge loss" (SVM)

  合页损失（SVM）。

$$
f ^ {*} (x) = \operatorname{sgn} (\eta (x) - 1 / 2) = g ^ {*} (x)
$$

- Explainability

  可解释性。
- Reinforcement Learning

  强化学习。
- Adapting these concepts to other problems :

  将这些概念应用到其他问题：
- either in terms of objectives : such as preference learning, scoring, ranking, anomaly detection, novelty detection...

  从目标角度：例如偏好学习、评分、排序、异常检测、新颖性检测等。
- or in terms of learning setups : online learning, unsupervised learning, transfer learning, multitask learning, budgeted learning, active learning...

  从学习设定角度：在线学习、无监督学习、迁移学习、多任务学习、预算受限学习、主动学习等。

<a id="reading-convex-surrogates-calibration"></a>

**Complément — Risque de substitution convexe ($\varphi$-risque), fonctions cibles optimales $f^*$ et calibration au sens de la classification (Zhang 2004 ; Bartlett, Jordan & McAuliffe 2006).**

**补充——凸替代风险（$\varphi$ 风险）、最优目标函数 $f^*$ 与分类校准定理（Zhang 2004；Bartlett, Jordan & McAuliffe 2006）。**

Les sections 30 à 32 unifient les SVM à noyaux et le Boosting sous un même paradigme statistique : au lieu de minimiser le risque empirique 0–1 $\hat{L}_n(f) = \frac{1}{n}\sum_{i=1}^n \mathbb{I}\{Y_i f(X_i) < 0\}$ (qui est non convexe, discontinu et NP-difficile à optimiser) sur une petite classe de VC-dimension finie, on minimise un **$\varphi$-risque convexe pénalisé** dans un espace fonctionnel massif $\mathcal{F}$ (un RKHS pour les SVM, ou l'enveloppe linéaire $\operatorname{span}(\mathcal{G})$ pour le Boosting) :

第 30 至 32 节将核 SVM 与 Boosting 统一到了同一个统计范式之下：我们不再去小容量（有限 VC 维）函数类上最小化非凸、不连续且 NP-hard 的 0–1 经验风险 $\hat{L}_n(f) = \frac{1}{n}\sum_{i=1}^n \mathbb{I}\{Y_i f(X_i) < 0\}$，而是在庞大的函数空间 $\mathcal{F}$（SVM 对应再生核 Hilbert 空间 RKHS，Boosting 对应弱分类器张成空间 $\operatorname{span}(\mathcal{G})$）中最小化**带惩罚的凸 $\varphi$ 风险**：

$$
\min_{f \in \mathcal{F}} \frac{1}{n}\sum_{i=1}^n \varphi\!\big(-Y_i f(X_i)\big) + \lambda\,\Omega(f),
$$

où $\varphi : \mathbb{R} \to \mathbb{R}_+$ est une fonction de perte de substitution convexe (dans la convention du cours où l'argument est $u = -Y f(X)$, une marge positive $Y f(X) > 0$ correspond à un argument négatif $u < 0$, tandis qu'une erreur de classification $Y f(X) < 0$ correspond à $u > 0$. Les pertes exponentielle $e^u$ et hinge $(1+u)_+$ majorent ponctuellement l'indicatrice $\mathbb{I}_{\mathbb{R}_+}(u)$ sur $\mathbb{R}$ ; la perte logistique en logarithme népérien $\log(1+e^u)$ vaut $\log 2 < 1$ en $u=0$, de sorte qu'il faut la diviser par $\log 2$, soit $\log_2(1+e^u)$, si l'on souhaite qu'elle majore ponctuellement $\mathbb{I}_{\mathbb{R}_+}(u)$).

其中 $\varphi : \mathbb{R} \to \mathbb{R}_+$ 是非负凸替代损失（注意本讲采用 $u = -Y f(X)$ 作为 $\varphi$ 的自变量：当分类间隔 $Y f(X) > 0$ 正确时，自变量 $u < 0$；当发生误判 $Y f(X) < 0$ 时，$u > 0$。指数损失 $e^u$ 与合页损失 $(1+u)_+$ 在整个 $\mathbb{R}$ 上逐点上界指示函数 $\mathbb{I}_{\mathbb{R}_+}(u)$；而自然对数形式的逻辑斯谛损失 $\log(1+e^u)$ 在 $u=0$ 处取值为 $\log 2 \approx 0.693 < 1$，在小负间隔区域小于 $1$，若要逐点上界 0–1 损失需按比例缩放为 $\log_2(1+e^u) = \frac{1}{\log 2}\log(1+e^u)$，但缩放不影响其极小点与分类校准性）。

**Dérivation : Calcul explicite des fonctions cibles $f^*(x)$ pour les pertes exponentielle, hinge et logistique（指数损失、合页损失与逻辑斯谛损失下最优目标函数 $f^*(x)$ 的精确推导）**

Par conditionnement par rapport à $X = x$, minimiser la fonctionnelle $A(f) = \mathbb{E}[\varphi(-Y f(X))]$ sur toutes les fonctions mesurables $f : \mathcal{X} \to \mathbb{R}$ revient à minimiser ponctuellement, pour chaque $x \in \mathcal{X}$, le $\varphi$-risque conditionnel :

通过对 $X = x$ 取条件期望，在所有可测函数 $f : \mathcal{X} \to \mathbb{R}$ 上最小化泛函 $A(f) = \mathbb{E}[\varphi(-Y f(X))]$ 等价于对每个 $x \in \mathcal{X}$ 逐点最小化条件 $\varphi$ 风险：

$$
\psi_\eta(a) := \eta(x)\,\varphi(-a) + \big(1 - \eta(x)\big)\,\varphi(a), \qquad a = f(x) \in \mathbb{R},
$$

où $\eta(x) = \mathbb{P}(Y = +1 \mid X = x) \in [0, 1]$. Calculons le minimiseur $f^*(x) = \arg\min_{a \in \mathbb{R}} \psi_\eta(a)$ pour les trois grandes pertes convexes :

其中 $\eta(x) = \mathbb{P}(Y = +1 \mid X = x) \in [0, 1]$。下面针对三种核心凸替代损失求极小点 $f^*(x) = \arg\min_{a \in \mathbb{R}} \psi_\eta(a)$：

1. **Perte exponentielle (Boosting) : $\varphi(u) = e^u$**.
   On a $\psi_\eta(a) = \eta(x) e^{-a} + (1 - \eta(x)) e^{a}$. Pour $\eta(x) \in (0, 1)$, la fonction est strictement convexe et dérivable :

   **指数损失（Boosting）：$\varphi(u) = e^u$**。
   此时 $\psi_\eta(a) = \eta(x) e^{-a} + (1 - \eta(x)) e^{a}$。当 $\eta(x) \in (0, 1)$ 时，该函数严格凸且可微，令导数为零：

   $$
   \psi'_\eta(a) = -\eta(x) e^{-a} + \big(1 - \eta(x)\big) e^{a} = 0 \iff e^{2a} = \frac{\eta(x)}{1 - \eta(x)} \iff f^*(x) = \frac{1}{2}\log\!\left(\frac{\eta(x)}{1 - \eta(x)}\right).
   $$

   Le minimum associé vaut $A^*(x) = \psi_\eta(f^*(x)) = 2\sqrt{\eta(x)(1 - \eta(x))}$.

   对应的逐点最小风险为 $A^*(x) = \psi_\eta(f^*(x)) = 2\sqrt{\eta(x)(1 - \eta(x))}$。
2. **Perte « hinge » (SVM) : $\varphi(u) = (1 + u)_+ = \max(0, 1 + u)$**.
   On a $\psi_\eta(a) = \eta(x)(1 - a)_+ + (1 - \eta(x))(1 + a)_+$. C'est une fonction affine par morceaux sur $(-\infty, -1]$, $[-1, 1]$ et $[1, +\infty)$ :
   - Sur $(-\infty, -1)$, $1-a > 2$ et $1+a < 0$, donc $\psi_\eta(a) = \eta(x)(1-a)$ est strictement décroissante (pente $-\eta(x) \le 0$) ;
   - Sur $(1, +\infty)$, $1-a < 0$ et $1+a > 2$, donc $\psi_\eta(a) = (1-\eta(x))(1+a)$ est strictement croissante (pente $1-\eta(x) \ge 0$).
   Le minimum est donc toujours atteint sur l'intervalle $[-1, 1]$, où $(1-a)_+ = 1-a$ et $(1+a)_+ = 1+a$, ce qui donne une fonction affine :

   **合页损失（SVM）：$\varphi(u) = (1 + u)_+ = \max(0, 1 + u)$**。
   此时 $\psi_\eta(a) = \eta(x)(1 - a)_+ + (1 - \eta(x))(1 + a)_+$。它在 $(-\infty, -1]$、$[-1, 1]$ 与 $[1, +\infty)$ 上是分段仿射函数：在 $(-\infty, -1)$ 上单调递减，在 $(1, +\infty)$ 上单调递增。因此最小值必在区间 $[-1, 1]$ 上达到；而在 $[-1, 1]$ 上 $(1-a)_+ = 1-a$ 且 $(1+a)_+ = 1+a$，化简为关于 $a$ 的线性函数：

   $$
   \forall a \in [-1, 1], \qquad \psi_\eta(a) = \eta(x)(1 - a) + \big(1 - \eta(x)\big)(1 + a) = 1 - \big(2\eta(x) - 1\big)a.
   $$

   - Si $\eta(x) > 1/2$, la pente $-(2\eta(x)-1) < 0$, donc l'unique minimiseur est $a^* = +1$ ;
   - Si $\eta(x) < 1/2$, la pente $-(2\eta(x)-1) > 0$, donc l'unique minimiseur est $a^* = -1$ ;
   - Par conséquent, $f^*(x) = \operatorname{sgn}(\eta(x) - 1/2) = g^*(x)$ ! (Notons que la perte hinge estime directement le signe de Bayes $g^*(x) \in \{-1, +1\}$, mais ne permet pas de reconstruire la probabilité $\eta(x)$ contrairement aux pertes exponentielle ou logistique.)

   当 $\eta(x) > 1/2$ 时斜率为负，唯一极小点为 $a^* = +1$；当 $\eta(x) < 1/2$ 时斜率为正，唯一极小点为 $a^* = -1$。因此 $f^*(x) = \operatorname{sgn}(\eta(x) - 1/2) = g^*(x)$！（注意：合页损失直接估计 Bayes 决策符号 $g^*(x) \in \{-1, +1\}$，因此不像指数损失或逻辑斯谛损失那样能从 $f^*(x)$ 反解出后验概率 $\eta(x)$。）
3. **Perte logistique (Régression logistique) : $\varphi(u) = \log(1 + e^u)$**.
   En annulant la dérivée $\psi'_\eta(a) = -\eta(x)\frac{e^{-a}}{1+e^{-a}} + (1-\eta(x))\frac{e^a}{1+e^a} = \frac{1}{1+e^{-a}} - \eta(x) = 0$, on obtient le log-odds $f^*(x) = \log\!\big(\frac{\eta(x)}{1-\eta(x)}\big)$.

   **逻辑斯谛损失（逻辑回归）：$\varphi(u) = \log(1 + e^u)$**。
   令导数 $\psi'_\eta(a) = \frac{1}{1+e^{-a}} - \eta(x) = 0$，即得对数几率 $f^*(x) = \log\!\big(\frac{\eta(x)}{1-\eta(x)}\big)$。

**Théorème de calibration (Zhang, 2004 ; Bartlett, Jordan & McAuliffe, 2006, Theorem 2)** :
Dans la convention $A(f) = \mathbb{E}[\varphi(-Y f(X))]$ utilisée dans ce cours, une perte convexe $\varphi$ est **calibrée pour la classification** (*classification-calibrated*) si et seulement si elle est dérivable en $0$ et vérifie **$\varphi'(0) > 0$** (Notons que l'article original de Bartlett, Jordan & McAuliffe, 2006 écrit la perte sous la forme $\phi(Y f(X)) = \varphi(-Y f(X))$, pour laquelle la condition s'écrit $\phi'(0) = -\varphi'(0) < 0$. Avec l'argument $u = -Y f(X)$ du cours, la dérivée de $\psi_\eta(a) = \eta(x)\varphi(-a) + (1-\eta(x))\varphi(a)$ en $a = 0$ vaut $\psi'_\eta(0) = (1 - 2\eta(x))\varphi'(0)$ : la condition $\varphi'(0) > 0$ — vérifiée par $e^u$ avec $\varphi'(0)=1$, $(1+u)_+$ avec $\varphi'(0)=1$, et $\log(1+e^u)$ avec $\varphi'(0)=1/2$ — garantit que $\psi'_\eta(0) < 0$ dès que $\eta(x) > 1/2$, forçant tout minimiseur à vérifier $f^*(x) > 0$, et que $\psi'_\eta(0) > 0$ dès que $\eta(x) < 1/2$, forçant $f^*(x) < 0$, d'où $\operatorname{sgn}(f^*(x)) = \operatorname{sgn}(\eta(x) - 1/2) = g^*(x)$). De plus, il existe une fonction convexe strictement croissante $\psi : [0, 1] \to \mathbb{R}_+$ avec $\psi(0) = 0$ (l'inéquation de comparaison de Zhang / Bartlett et al.) telle que pour toute fonction mesurable $f$ :

**分类校准定理（Zhang, 2004；Bartlett, Jordan & McAuliffe, 2006，定理 2）**：
在本讲采用 $A(f) = \mathbb{E}[\varphi(-Y f(X))]$ 的记号约定下，凸替代损失 $\varphi$ 被称为**分类校准的**（classification-calibrated），当且仅当 $\varphi$ 在 $0$ 处可微且满足 **$\varphi'(0) > 0$**（注意：Bartlett, Jordan & McAuliffe, 2006 原论文将损失记为 $\phi(Y f(X)) = \varphi(-Y f(X))$，因此原论文中写为 $\phi'(0) = -\varphi'(0) < 0$；而在本讲以 $u = -Y f(X)$ 为自变量的约定下，$\psi_\eta(a) = \eta(x)\varphi(-a) + (1-\eta(x))\varphi(a)$ 在 $a=0$ 处的导数为 $\psi'_\eta(0) = (1 - 2\eta(x))\varphi'(0)$。上面三个例子在 $u=0$ 处的导数分别为：指数损失 $\varphi'(0)=1 > 0$、合页损失 $\varphi'(0)=1 > 0$、逻辑斯谛损失 $\varphi'(0)=1/2 > 0$。正是 **$\varphi'(0) > 0$** 保证了当 $\eta(x) > 1/2$ 时 $\psi'_\eta(0) < 0$ 从而迫使极小点 $f^*(x) > 0$，当 $\eta(x) < 1/2$ 时 $\psi'_\eta(0) > 0$ 从而迫使 $f^*(x) < 0$，即 $\operatorname{sgn}(f^*(x)) = \operatorname{sgn}(\eta(x) - 1/2) = g^*(x)$）。进一步地，存在满足 $\psi(0) = 0$ 的严格递增凸函数 $\psi : [0, 1] \to \mathbb{R}_+$（Zhang / Bartlett 等比较不等式），使得对任意可测决策函数 $f$：

$$
\psi\!\big(L(f) - L^*\big) \le A(f) - A^* \qquad \text{(par exemple : } L(f) - L^* \le A(f) - A^* \text{ pour la perte hinge, } L(f) - L^* \le \sqrt{2\big(A(f) - A^*\big)} \text{ pour la perte exponentielle, et } L(f) - L^* \le 2\sqrt{A(f) - A^*} \text{ pour } \log(1+e^u)\text{).}
$$

Ainsi, toute suite d'estimateurs $\hat{f}_n$ dont l'excès de $\varphi$-risque $A(\hat{f}_n) - A^* \to 0$ voit son excès de risque de classification 0–1 $L(\hat{f}_n) - L^* \to 0$ !

（例如：对合页损失有线性控制 $L(f) - L^* \le A(f) - A^*$；对指数损失有 $L(f) - L^* \le \sqrt{2(A(f) - A^*)}$；对自然对数逻辑斯谛损失 $\log(1+e^u)$ 有 $L(f) - L^* \le 2\sqrt{A(f) - A^*}$。）因此，只要估计量序列 $\hat{f}_n$ 的替代超额风险满足 $A(\hat{f}_n) - A^* \to 0$，其 0–1 分类超额风险也随之满足 $L(\hat{f}_n) - L^* \to 0$！
