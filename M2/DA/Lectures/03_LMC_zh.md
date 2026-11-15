# 分类问题与参数方法：原文与中文逐段对照

> 正文按原课件顺序排列，英文或法语原文后紧跟中文；例子、练习、重复正文、公式、图表及文献均保留。图中文字保留原图语言。原课件错误与必要辨析以独立“译注”标明。

[原 PDF](03_LMC.pdf) · [原文转换稿](03_LMC.md) · [逐块对应清单](Translation-audit/2026-09-28-coverage.json) · [课程目录](../README.md)

**本讲目录**

- [分类问题与参数方法](#section-01)
- [分类数据：例子](#section-02)
- [这些数据可以支持哪些决策？](#section-03)
- [分类数据的概率模型](#section-04)
- [分类问题的理论框架](#section-05)
- [评价准则：分类器的误差](#section-06)
- [分类中的过拟合（续）](#section-07)
- [复杂度调整](#section-08)
- [实践中的留出法](#section-09)
- [方法 1：线性判别分析（LDA）与二次判别分析（QDA）](#section-10)
- [线性判别分析（LDA）](#section-11)
- [线性判别分析（续）](#section-12)
- [二次判别分析（QDA）](#section-13)
- [方法 2：Fisher 判别分析（FDA）](#section-14)
- [方法 3：线性逻辑回归](#section-15)
- [生成式方法的局限](#section-16)
- [从分类到评分：ROC 曲线与 AUC](#section-17)
- [Neyman–Pearson 分类器](#section-18)
- [评分的最优解](#section-19)
- [实用准则：ROC 曲线下面积（AUC）](#section-20)
- [评分的性能度量](#section-21)
- [评分的性能度量](#section-22)
- [评分的性能度量](#section-23)
- [非参数线性判别算法](#section-24)
- [感知机算法（Rosenblatt，1958）](#section-25)
- [一般感知机算法](#section-26)
- [Novikoff 定理](#section-27)
- [场景 1：具有良好泛化能力的超平面](#section-28)
- [Karush–Kuhn–Tucker 条件](#section-29)
- [规范最优超平面](#section-30)

**重点定理与概念解释速查：**

- [分类与评分的区别、生成式与判别式建模对比](#reading-generative-vs-discriminative)
- [0/1 训练误差、过拟合与留出法／交叉验证的统计性质](#reading-classification-risk-and-holdout)
- [高斯混合、马氏距离与 LDA / QDA / 正则化判别分析推导](#reading-lda-qda-derivation)
- [Fisher 判别分析（FDA）、广义瑞利商与特征值求解](#reading-fisher-discriminant)
- [线性逻辑回归：对数似然凹性、Newton–Raphson 与 IRLS 推导](#reading-logistic-regression-irls)
- [Neyman–Pearson 引理、ROC 曲线性质与 AUC 概率等价性证明](#reading-roc-neyman-pearson-auc)
- [超平面有符号距离、感知机更新几何与 Novikoff 定理证明](#reading-perceptron-novikoff)
- [最大间隔超平面（SVM）、拉格朗日对偶与 KKT 支持向量分类](#reading-svm-duality-kkt)

M2 CHPS

**[Data & Apprentissage] Introduction à la science des données et à l'apprentissage**

**数据科学与机器学习导论**

Nicolas Vayatis

<a id="section-01"></a>

Problème de classification, méthodes paramétriques

## 分类问题与参数方法

<a id="section-02"></a>

**Données de classification - Exemples**

## 分类数据：例子

**• Diagnostic médical :**

### 医学诊断

- X : résultats des analyses médicales

  X：医学检查结果。
- $Y$ : diagnostic,

  $Y$：诊断。
- $Y = +1$ si le patient est en bonne santé, et $Y = -1$ sinon

  如果患者健康，则 $Y = +1$；否则 $Y = -1$。

**- Risque de crédit :**

### 信用风险

- X : données socio-économiques d'un individu,

  X：个人的社会经济数据。
- $Y$ : indicateur de défaut de paiement,

  $Y$：违约指标。
- $Y = +1$ si l'emprunteur est fiable, et $Y = -1$ sinon

  如果借款人可靠，则 $Y = +1$；否则 $Y = -1$。

**- Anti-spam :**

### 垃圾邮件识别

- X : descripteur d'un email,

  X：邮件的描述特征。
- $Y$ : statut de l'email,

  $Y$：邮件的状态。
- $Y = +1$ si le message est un spam, et $Y = -1$ sinon

  如果邮件是垃圾邮件，则 $Y = +1$；否则 $Y = -1$。

<a id="section-03"></a>

**Quelles décisions pour ces données ?**

## 这些数据可以支持哪些决策？

**1 Classification**

### 1. 分类

But : Prédire les nouveaux labels Y

目标：预测新的标签 Y。

Satisfaits si l'erreur de classification est faible

如果分类错误率低，就认为结果令人满意。

**② Scoring**

### 2. 评分

But : Ranger les X dans une liste

目标：将 X 排列成一个列表。

Satisfaits si beaucoup de Y = +1 sont en tête de liste

如果列表前端有许多 Y = +1 的对象，就认为结果令人满意。

1. Modèle probabiliste des données de classification

   分类数据的概率模型。
2. Cadre théorique du problème de classification

   分类问题的理论框架。
3. Méthodes de classification paramétriques (linéaires) classiques

   经典的参数化（线性）分类方法。
1. Analyse discriminante (LDA/QDA)

   判别分析（LDA/QDA）。
2. Analyse discriminante de Fischer (FDA)

   Fisher 判别分析（FDA）。
3. Régression logistique linéaire

   线性逻辑回归。

**4 De la classification au scoring (ciblage) : la courbe ROC et l'aire AUC**

### 4. 从分类到评分（定向筛选）：ROC 曲线与 AUC 面积

5. 5 Algorithme du perceptron : linéaire et non-paramétrique!

   感知机算法：线性且非参数！

<a id="classification-model"></a>

<a id="section-04"></a>

**Modèle probabiliste des données de classification**

## 分类数据的概率模型

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

<a id="reading-generative-vs-discriminative"></a>

**Complément — classification vs scoring, et modélisation générative vs discriminative**

**补充——分类与评分的区别，以及生成式与判别式建模**

Les sections 3 et 4 introduisent deux distinctions fondamentales qui structurent tout le cours : la **nature de la décision** (classer ou ordonner) et la **manière de factoriser la loi jointe** $\mathcal{L}(X,Y)$.

第 3 节与第 4 节引入了贯穿全课的两组核心区分：**决策任务的形式**（硬分类还是排序评分）以及**联合分布 $\mathcal{L}(X,Y)$ 的分解方式**（生成式还是判别式）。

1. **Classification binaire vs Scoring (ordonnancement) 二分类与评分（排序）的区别**
   Un classifieur $g:\mathcal{X}\to\{-1,+1\}$ prend une décision binaire immédiate pour chaque observation (ex. bloquer ou laisser passer un email). À l'inverse, une fonction de *scoring* $s:\mathcal{X}\to\mathbb{R}$ attribue un score continu permettant de trier les individus par priorité (ex. classer des dossiers de crédit du plus sûr au plus risqué, ou cibler les $10\%$ de patients les plus susceptibles de bénéficier d'un examen). Un bon score n'a pas besoin d'avoir un seuil fixé à l'avance : il suffit que les exemples positifs ($Y=+1$) reçoivent des scores systématiquement plus élevés que les exemples négatifs ($Y=-1$), ce que mesureront la courbe ROC et l'AUC aux §17–20.

   分类器 $g:\mathcal{X}\to\{-1,+1\}$ 对每个样本直接给出二元硬决策（例如拦截或放行一封邮件）。而**评分函数（scoring）** $s:\mathcal{X}\to\mathbb{R}$ 则输出连续分数，用于对样本做优先级排序（例如将信贷申请人按违约风险从低到高排列，或筛选最需要复查的前 $10\%$ 患者）。优秀的评分规则不必预先固定单一阈值，只要正例（$Y=+1$）的得分整体高于负例（$Y=-1$）即可——这正是后文 §17–20 用 ROC 曲线和 AUC 衡量的性质。

2. **Deux factorisations de la loi jointe 联合分布的两种分解与建模路径**
   Par la formule des probabilités composées, la loi jointe du couple $(X,Y)$ s'écrit de deux façons symétriques, qui conduisent à des stratégies d'estimation très différentes :

   由条件概率乘法公式，随机变量对 $(X,Y)$ 的联合分布有两种对称的分解方式，对应截然不同的统计估计策略：

| Approche / 建模范式 | Factorisation modélisée / 所建模的分布分解 | Quantités estimées / 需要估计的对象 | Exemples dans ce cours / 本课代表方法 | Avantages et limites / 优势与局限 |
|---|---|---|---|---|
| **Générative / 生成式方法** | $\mathcal{L}(Y)\otimes\mathcal{L}(X\mid Y)$ | Prior $p=\mathbb{P}(Y=+1)$ et lois conditionnelles par classe $P_+, P_-$ / 先验 $p=\mathbb{P}(Y=+1)$ 与各类别的类条件分布 $P_+, P_-$ | LDA (§11), QDA (§13), Naive Bayes | Permet d'échantillonner de nouveaux $X$ et d'utiliser Bayes pour obtenir $\eta(x)$, mais exige de spécifier toute la loi de $X\mid Y$ en dimension $d$ / 可生成新样本并由 Bayes 公式反推 $\eta(x)$，但必须对 $d$ 维特征的完整条件分布作参数假设 |
| **Discriminative probabiliste / 概率判别式方法** | $\mathcal{L}(Y\mid X)$ directement / 直接对 $\mathcal{L}(Y\mid X)$ 建模 | Probabilité a posteriori $\eta(x)=\mathbb{P}(Y=+1\mid X=x)$ / 直接估计后验概率函数 $\eta(x)=\mathbb{P}(Y=+1\mid X=x)$ | Régression logistique (§15), k-NN (§19 du cours 5), arbres | Évite de modéliser la loi marginale $P_X$ ou les corrélations complexes entre coordonnées de $X$ ; plus robuste si $X\mid Y$ n'est pas gaussien / 无需对边际分布 $P_X$ 或特征间的复杂分布建模，当 $X\mid Y$ 偏离高斯假设时往往更稳健 |
| **Discriminative géométrique / 几何／非参数判别式** | Frontière de décision directe / 直接寻找决策边界 | Fonction de décision $f(x)$ et classifieur $g(x)=\operatorname{sgn}(f(x))$ / 决策函数 $f(x)$ 与分类器 $g(x)=\operatorname{sgn}(f(x))$ | FDA (§14), Perceptron (§25), SVM (§28) | Cible directement la séparation entre classes sans estimer de densités ni de probabilités calibrées / 直接针对分类边界优化，不估计概率密度，但原始输出不直接给出校准后的后验概率 |

**Dérivation : formule de Bayes pour $\eta(x)$ et règle du rapport de vraisemblance**

**推导：后验概率 $\eta(x)$ 的 Bayes 公式与似然比判别规则**

Supposons que les lois conditionnelles $P_+=\mathcal{L}(X\mid Y=+1)$ et $P_-=\mathcal{L}(X\mid Y=-1)$ admettent des densités $f_+(x)$ et $f_-(x)$ par rapport à une mesure commune (notées $dP_+(x)$ et $dP_-(x)$ dans le support). La densité marginale de $X$ est le mélange :

设类条件分布 $P_+=\mathcal{L}(X\mid Y=+1)$ 与 $P_-=\mathcal{L}(X\mid Y=-1)$ 关于同一参考测度具有密度 $f_+(x)$ 与 $f_-(x)$（课件中记作 $dP_+(x)$ 与 $dP_-(x)$）。于是输入 $X$ 的边际密度为两者的混合分布：

$$
f_X(x) = p f_+(x) + (1-p) f_-(x), \qquad \text{où } p = \mathbb{P}(Y=+1).
$$

Par la formule de Bayes, la probabilité a posteriori de la classe $+1$ sachant $X=x$ vaut :

由 Bayes 公式，给定 $X=x$ 时类别为 $+1$ 的后验概率为：

$$
\eta(x) = \mathbb{P}(Y=+1\mid X=x) = \frac{p f_+(x)}{p f_+(x) + (1-p) f_-(x)}.
$$

Comme vu au [cours 1 (section 7)](01_intro/07_bayes_and_learning_bounds.md#reading-bayes-solutions), le classifieur de Bayes qui minimise le risque de mauvaise classification $\mathbb{P}(g(X)\neq Y)$ prédit $+1$ lorsque $\eta(x) > 1/2$ (et $-1$ lorsque $\eta(x) < 1/2$). Or :

如[第一课第 7 篇](01_intro/07_bayes_and_learning_bounds.md#reading-bayes-solutions)所证，最小化误分类概率 $\mathbb{P}(g(X)\neq Y)$ 的 Bayes 最优分类器在 $\eta(x) > 1/2$ 时预测 $+1$（在 $\eta(x) < 1/2$ 时预测 $-1$）。由代数等价变形：

$$
\eta(x) > \frac{1}{2}
\iff \frac{p f_+(x)}{p f_+(x) + (1-p) f_-(x)} > \frac{1}{2}
\iff p f_+(x) > (1-p) f_-(x)
\iff \frac{f_+(x)}{f_-(x)} > \frac{1-p}{p}.
$$

Cette équivalence montre que comparer la probabilité a posteriori $\eta(x)$ au seuil $1/2$ revient exactement à comparer le **rapport de vraisemblance** $f_+(x)/f_-(x)$ au rapport des probabilités a priori $(1-p)/p$. C'est le point de départ commun de la LDA/QDA (§11–13) et du test de Neyman–Pearson (§17–18).

这一等价式说明：将后验概率 $\eta(x)$ 与阈值 $1/2$ 比较，在数学上严格等价于将**似然比（likelihood ratio）** $f_+(x)/f_-(x)$ 与先验概率之比 $(1-p)/p$ 比较。这既是后文推导 LDA/QDA（§11–13）的出发点，也是 Neyman–Pearson 最优检验（§17–18）的理论基础。

<a id="section-05"></a>

Cadre théorique du problème de classification

## 分类问题的理论框架

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

<a id="section-06"></a>

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
- Attention ! si on s'intéresse seulement à ce type d'erreur, on risque d'avoir des problèmes...

  注意！如果只关注这类误差，就可能出现问题……

![image](<Images/03_LMC/image_001.jpg>)

![image](<Images/03_LMC/image_002.jpg>)

<a id="section-07"></a>

**Overfitting en classification (suite)**

## 分类中的过拟合（续）

Underfitting and Overfitting

欠拟合与过拟合

negative example positive example new patient

负例；正例；新患者。

<a id="section-08"></a>

**Calibration de la complexité**

## 复杂度调整

![image](<Images/03_LMC/image_003.jpg>)

<a id="section-09"></a>

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

<a id="reading-classification-risk-and-holdout"></a>

**Complément — pourquoi l'erreur d'apprentissage $\hat{L}_n(g)$ est biaisée et comment le holdout estime $L(g)$**

**补充——为什么训练误差 $\hat{L}_n(g)$ 会低估真实风险，以及留出法如何估计 $L(g)$**

Pour un classifieur $g$ **fixé à l'avance** indépendamment des données, chaque indicateur d'erreur $Z_i = \mathbb{I}_{[g(X_i)\neq Y_i]}$ suit une loi de Bernoulli de paramètre $L(g) = \mathbb{P}(g(X)\neq Y)$, de sorte que $\mathbb{E}[\hat{L}_n(g)] = L(g)$. En revanche, lorsque le classifieur $\hat{g}_n$ est **choisi à partir de l'échantillon d'apprentissage** pour minimiser $\hat{L}_n$, il s'adapte aux fluctuations particulières de ces $n$ points : en moyenne, $\mathbb{E}[\hat{L}_n(\hat{g}_n)] \le L(\hat{g}_n)$. Plus la famille de classifieurs est flexible (frontière très sinueuse sur la figure de la section 7), plus cet écart d'optimisme (surapprentissage / *overfitting*) est grand.

对于一个**预先固定**、与数据无关的分类器 $g$，每个误判指示变量 $Z_i = \mathbb{I}_{[g(X_i)\neq Y_i]}$ 服从参数为 $L(g) = \mathbb{P}(g(X)\neq Y)$ 的 Bernoulli 分布，因此经验误差满足无偏性 $\mathbb{E}[\hat{L}_n(g)] = L(g)$。然而，一旦分类器 $\hat{g}_n$ 是**根据这批训练样本选出来**以极小化 $\hat{L}_n$ 的，它就会顺应这 $n$ 个样本的偶然波动，导致训练误差系统性地偏乐观：$\mathbb{E}[\hat{L}_n(\hat{g}_n)] \le L(\hat{g}_n)$。候选分类器族越复杂（如第 7 节图中曲折绕过每个样本点的分界面），这种乐观偏差（即**过拟合**）就越严重。

Dans la stratégie du **holdout** (§9), si $\hat{g}$ a été appris uniquement sur la base d'apprentissage $D_n = \{(X_1,Y_1),\dots,(X_n,Y_n)\}$, alors, **conditionnellement à $D_n$**, le classifieur $\hat{g}$ est fixe et les $m$ points de la base de test sont i.i.d. et indépendants de $D_n$. Le nombre d'erreurs de test $m \hat{L}_m'(\hat{g})$ suit donc, sachant $D_n$, une loi binomiale $\mathrm{Bin}(m, L(\hat{g}))$ :

在**留出法（holdout）**（§9）中，只要 $\hat{g}$ 完全在训练集 $D_n = \{(X_1,Y_1),\dots,(X_n,Y_n)\}$ 上训练得到，那么**在给定训练集 $D_n$ 的条件下**，$\hat{g}$ 就是一个确定的函数，而测试集的 $m$ 个样本与 $D_n$ 独立同分布。因此，给定 $D_n$ 时，测试集上的错误个数 $m \hat{L}_m'(\hat{g})$ 严格服从二项分布 $\mathrm{Bin}(m, L(\hat{g}))$：

$$
\mathbb{E}\big[\hat{L}_m'(\hat{g}) \;\big|\; D_n\big] = L(\hat{g}),
\qquad
\operatorname{Var}\big(\hat{L}_m'(\hat{g}) \;\big|\; D_n\big) = \frac{L(\hat{g})\big(1 - L(\hat{g})\big)}{m} \le \frac{1}{4m}.
$$

Si la taille totale $N = n + m$ des données est limitée, le holdout impose un compromis : prendre $m$ trop petit rend l'estimateur de test $\hat{L}_m'$ très bruité (variance en $1/m$), tandis que prendre $m$ trop grand réduit $n$ et dégrade l'apprentissage de $\hat{g}$. La **validation croisée à $K$ blocs** (*$K$-fold cross-validation*, étudiée au [cours 2, section 6](02_LM/06_regularization_and_validation.md#reading-cross-validation)) résout ce dilemme en faisant jouer à chaque observation le rôle de test exactement une fois. Attention toutefois : dès qu'un jeu de validation sert à choisir un hyperparamètre (comme $k$ pour k-NN ou $C$ pour SVM), l'erreur minimale sur ce jeu de validation redevient légèrement optimiste ; l'évaluation finale nécessite donc un jeu de test séparé qui n'a participé ni à l'entraînement ni au réglage des hyperparamètres.

当总样本量 $N = n + m$ 有限时，留出法面临两难：$m$ 太小会使测试误差估计量的方差（与 $1/m$ 成正比）过大，结果依赖单次划分的运气；$m$ 太大则会削减训练样本量 $n$，使学到的分类器 $\hat{g}$ 本身变差。**$K$ 折交叉验证**（详见[第二课第 6 篇](02_LM/06_regularization_and_validation.md#reading-cross-validation)）通过轮流让每个子块充当验证集，兼顾了训练样本量与评估稳定性。但需要注意：一旦用验证集从多个超参数（如 k-NN 的 $k$ 或 SVM 的 $C$）中挑出了误差最小者，该验证误差本身也会因为“挑最小”而再次产生轻微乐观偏差；严格报告最终泛化性能时，仍需保留一份既未参与训练也未参与调参的独立测试集。

<a id="section-10"></a>

Méthode # 1 : Analyse discriminante linéaire (LDA) et quadratique (QDA)

## 方法 1：线性判别分析（LDA）与二次判别分析（QDA）

**Rappel : loi gaussienne multivariée**

### 回顾：多元高斯分布

**Multivariate Gaussian models**

### 多元高斯模型

- Similar to univariate case

  与一元情形类似。

$$
\mathcal {N} (\underline {{{{x}}}}; \underline {{{{\mu}}}}, \Sigma) = \frac {1}{(2 \pi) ^ {d / 2}} | \Sigma | ^ {- 1 / 2} \exp \left\{- \frac {1}{2} (\underline {{{{x}}}} - \underline {{{{\mu}}}}) \Sigma^ {- 1} (\underline {{{{x}}}} - \underline {{{{\mu}}}}) ^ {T} \right\}
$$

![image](<Images/03_LMC/image_004.jpg>)

$$
\begin{array}{l} \mu = \text{长度为 d 的行向量} \\ \Sigma = \text{d×d 矩阵} \end{array}
$$

$|\Sigma| = \text{矩阵行列式}$

Maximum likelihood estimate:

最大似然估计：

$$
\bar {\mu} = \frac {1}{m} \sum_ {j} x ^ {(j)}
$$

$$
\bar {\Sigma} = \frac {1}{m} \sum_ {j} (\underline {{x}} ^ {(j)} - \underline {{\mu}}) ^ {T} (\underline {{x}} ^ {(j)} - \underline {{\mu}})
$$

(average of dxd matrices)

（对 d×d 矩阵取平均。）

> **译注：** 这里给出的是高斯均值与协方差的形式解。均值未知、协方差要求正定的非退化模型，需要中心化样本协方差正定才存在对应的最大似然解；样本不足或落在低维仿射子空间中时不能直接求逆。QDA 要逐类检查，LDA 检查合并类内散布矩阵。

**Rappel : mélange gaussien en 2D**

### 回顾：二维高斯混合

![image](<Images/03_LMC/image_005.jpg>)

b

![image](<Images/03_LMC/image_006.jpg>)

**Hypothèse : le modèle paramétrique de mélange gaussien**

### 假设：参数化高斯混合模型

- $X \in \mathbb{R}^d$ et $Y \in \{1, \ldots, K\}$

  $X \in \mathbb{R}^d$，且 $Y \in \{1, \ldots, K\}$。
- Forme paramétrique gaussienne pour la loi a posteriori

  后验分布采用高斯参数形式。

$$
\mathbb {P} (X \mid Y = k) \sim \mathcal {N} (m _ {k}, \Sigma_ {k}), \quad \text{密度} f _ {k}
$$

> **译注：** 原页写“后验分布”，但式中是给定类别后的输入分布，即类条件分布；类别后验是下一式中的 $\eta_k(x)$。

- Paramètre de mélange $\pi_{k}$ pour la classe $Y = k$

  第 $Y = k$ 类的混合参数为 $\pi_{k}$。
- On exprime alors :

  于是可以写出：

$$
\eta_ {k} (x) = \mathbb {P} (Y = k \mid X = x) = \frac {\pi_ {k} f _ {k} (x)}{\sum_ {j = 1} ^ {K} \pi_ {j} f _ {j} (x)}
$$

<a id="discriminant-analysis"></a>

<a id="section-11"></a>

**Analyse discriminante linéaire (LDA)**

## 线性判别分析（LDA）

- On suppose que $\Sigma_{k} = \Sigma, \forall k$

  假设 $\Sigma_{k} = \Sigma, \forall k$。
- On exprime alors :

  于是可以写出：

$$
\begin{array}{r l} \log \left(\frac {\eta_ {k} (x)}{\eta_ {j} (x)}\right) & = \frac {\pi_ {k} f _ {k} (x)}{\pi_ {j} f _ {j} (x)} \\ & = \log \left(\frac {f _ {k} (x)}{f _ {j} (x)}\right) + \log \left(\frac {\pi_ {k}}{\pi_ {j}}\right) \\ & = - \frac {1}{2} (m _ {k} + m _ {j}) ^ {T} \Sigma^ {- 1} (m _ {k} + m _ {j}) \\ & \quad + \log \left(\frac {\pi_ {k}}{\pi_ {j}}\right) + x ^ {T} \Sigma^ {- 1} (m _ {k} - m _ {j}) \end{array}
$$

> **译注：** 原页第一行右边漏了 log，第三行的均值二次项也有笔误。正确展开为 $\log\frac{\eta_k(x)}{\eta_j(x)}=x^T\Sigma^{-1}(m_k-m_j)-\tfrac12(m_k^T\Sigma^{-1}m_k-m_j^T\Sigma^{-1}m_j)+\log\frac{\pi_k}{\pi_j}$。原式保留于上方。

- Equation linéaire en x!

  关于 x 的线性方程！

<a id="section-12"></a>

**Analyse discriminante linéaire (suite)**

## 线性判别分析（续）

![image](<Images/03_LMC/image_007.jpg>)

<a id="section-13"></a>

**Analyse discriminante quadratique (QDA)**

## 二次判别分析（QDA）

- Cas où les matrices $\Sigma_{k}$ , $\forall k$ sont distinctes

  矩阵 $\Sigma_{k}$、$\forall k$ 不同的情形。
- On obtient dans ce cas des fonctions discriminantes :

  此时得到如下判别函数：

$$
\delta_ {k} (x) = - \frac {1}{2} (x - m _ {k}) ^ {T} \Sigma_ {k} ^ {- 1} (x - m _ {k})
$$

$$
+ \log (\pi_ {k}) - \frac {1}{2} \log d e t (\Sigma_ {k})
$$

- Séparatrices quadratiques en $x!$

  关于 $x!$ 的二次分界面。
- Estimation des matrices $\Sigma_{k}$ coûteuse en grande dimension

  在高维情况下，估计矩阵 $\Sigma_{k}$ 的代价很高。
- Alors : LDA avec termes de couplage ou QDA ?

  那么，是带耦合项的 LDA，还是 QDA？
- Idée : régulariser la matrice par interpolation

  思路：通过插值对矩阵作正则化。

$$
\hat {\Sigma} _ {k} (\lambda) = \lambda \hat {\Sigma} _ {k} (\lambda) + (1 - \lambda) \hat {\Sigma}
$$

cf. Friedman (1989)

参见 Friedman（1989）。

- Variations autour de régularisation et parcimonie

  围绕正则化与稀疏性的变体。

<a id="reading-lda-qda-derivation"></a>

**Complément — géométrie de la distance de Mahalanobis, dérivation complète de LDA/QDA et comptage des paramètres**

**补充——马氏距离的几何意义、LDA/QDA 判别函数的完整推导与高维参数复杂度**

Dans le modèle de mélange gaussien (§10–13), chaque classe $k\in\{1,\dots,K\}$ est caractérisée par son poids a priori $\pi_k = \mathbb{P}(Y=k)$, son centre $m_k \in \mathbb{R}^d$ et sa matrice de covariance $\Sigma_k \in \mathbb{R}^{d\times d}$ (symétrique définie positive). La densité gaussienne $f_k(x)$ ne dépend de $x$ qu'à travers la **distance de Mahalanobis au carré** :

在高斯混合分类模型（§10–13）中，每个类别 $k\in\{1,\dots,K\}$ 由先验概率 $\pi_k = \mathbb{P}(Y=k)$、均值向量 $m_k \in \mathbb{R}^d$ 和对称正定协方差矩阵 $\Sigma_k \in \mathbb{R}^{d\times d}$ 刻画。高斯密度 $f_k(x)$ 对输入 $x$ 的依赖完全体现在**马氏距离（Mahalanobis distance）的平方**上：

$$
d_{\Sigma_k}^2(x, m_k) = (x - m_k)^T \Sigma_k^{-1} (x - m_k).
$$

Contrairement à la distance euclidienne $\|x-m_k\|_2^2$ (dont les lignes de niveau sont des sphères et qui traite toutes les directions de manière identique), la distance de Mahalanobis pondère chaque direction propre de $\Sigma_k$ par l'inverse de sa variance : un écart de $1$ unité le long d'une direction de très faible variance est beaucoup plus pénalisé qu'un même écart le long d'une direction très dispersée. Les surfaces d'égale densité $f_k(x)=\text{cste}$ sont donc des **ellipsoïdes** centrés en $m_k$, dont les axes principaux sont les vecteurs propres de $\Sigma_k$ et les demi-longueurs d'axes sont proportionnelles aux racines carrées des valeurs propres $\sqrt{\lambda_j(\Sigma_k)}$.

与欧氏距离 $\|x-m_k\|_2^2$（等高面为球面，对所有方向一视同仁）不同，马氏距离将 $\Sigma_k$ 的每个特征方向按该方向方差的倒数加权：在方差极小的方向上偏离 $1$ 个单位，比在方差很大的方向上偏离 $1$ 个单位受到的惩罚大得多。因此，等密度面 $f_k(x)=\text{常数}$ 是以 $m_k$ 为中心的**椭球面**，椭球的主轴方向由 $\Sigma_k$ 的特征向量决定，半轴长度与特征值平方根 $\sqrt{\lambda_j(\Sigma_k)}$ 成正比。

**Dérivation : du rapport des densités gaussiennes aux frontières quadratiques (QDA) et linéaires (LDA)**

**推导：从高斯密度比到二次分界面（QDA）与线性超平面（LDA）**

Pour comparer deux classes $k$ et $j$, calculons le logarithme du rapport des probabilités a posteriori $\eta_k(x)/\eta_j(x)$. Comme le dénominateur $f_X(x)=\sum_{l=1}^K \pi_l f_l(x)$ est commun à toutes les classes, il se simplifie :

为比较类别 $k$ 与类别 $j$，计算后验概率之比的对数 $\log\frac{\eta_k(x)}{\eta_j(x)}$。由于边际密度分母 $f_X(x)=\sum_{l=1}^K \pi_l f_l(x)$ 对所有类别相同，直接约去：

$$
\begin{aligned}
\log\left(\frac{\eta_k(x)}{\eta_j(x)}\right)
&= \log\left(\frac{\pi_k f_k(x)}{\pi_j f_j(x)}\right) = \log\left(\frac{\pi_k}{\pi_j}\right) + \log f_k(x) - \log f_j(x) \\
&= \log\left(\frac{\pi_k}{\pi_j}\right) - \frac{1}{2}\log\det(\Sigma_k) + \frac{1}{2}\log\det(\Sigma_j) \\
&\quad - \frac{1}{2}(x - m_k)^T \Sigma_k^{-1} (x - m_k) + \frac{1}{2}(x - m_j)^T \Sigma_j^{-1} (x - m_j).
\end{aligned}
$$

C'est exactement la différence $\delta_k(x) - \delta_j(x)$ entre les **fonctions discriminantes quadratiques de la QDA** (§13) :

这正是 §13 中**二次判别分析（QDA）判别函数**之差 $\delta_k(x) - \delta_j(x)$，其中单类判别函数定义为：

$$
\delta_k(x) = -\frac{1}{2}(x - m_k)^T \Sigma_k^{-1} (x - m_k) - \frac{1}{2}\log\det(\Sigma_k) + \log(\pi_k).
$$

En développant le produit quadratique $(x-m_k)^T\Sigma_k^{-1}(x-m_k) = x^T\Sigma_k^{-1}x - 2x^T\Sigma_k^{-1}m_k + m_k^T\Sigma_k^{-1}m_k$ (car $\Sigma_k^{-1}$ est symétrique, donc $m_k^T\Sigma_k^{-1}x = x^T\Sigma_k^{-1}m_k$), la frontière d'indifférence $\delta_k(x) = \delta_j(x)$ s'écrit :

利用 $\Sigma_k^{-1}$ 的对称性（从而 $m_k^T\Sigma_k^{-1}x = x^T\Sigma_k^{-1}m_k$），将二次型展开为 $(x-m_k)^T\Sigma_k^{-1}(x-m_k) = x^T\Sigma_k^{-1}x - 2x^T\Sigma_k^{-1}m_k + m_k^T\Sigma_k^{-1}m_k$，两类判别边界 $\delta_k(x) = \delta_j(x)$ 可写为：

$$
-\frac{1}{2} x^T \big(\Sigma_k^{-1} - \Sigma_j^{-1}\big) x + x^T \big(\Sigma_k^{-1} m_k - \Sigma_j^{-1} m_j\big) - \frac{1}{2}\big(m_k^T\Sigma_k^{-1}m_k - m_j^T\Sigma_j^{-1}m_j\big) - \frac{1}{2}\log\frac{\det\Sigma_k}{\det\Sigma_j} + \log\frac{\pi_k}{\pi_j} = 0.
$$

- **Cas général (QDA, $\Sigma_k \neq \Sigma_j$) :** Le terme quadratique en $x^T(\Sigma_k^{-1}-\Sigma_j^{-1})x$ subsiste ; la surface séparatrice est une **quadrique** dans $\mathbb{R}^d$ (paraboloïde, ellipsoïde ou hyperboloïde selon les signes des valeurs propres de $\Sigma_k^{-1}-\Sigma_j^{-1}$).
- **一般情形（QDA，$\Sigma_k \neq \Sigma_j$）：** 二次项 $x^T(\Sigma_k^{-1}-\Sigma_j^{-1})x$ 不为零，分界面是 $\mathbb{R}^d$ 中的**二次曲面**（椭圆面、抛物面或双曲面，取决于 $\Sigma_k^{-1}-\Sigma_j^{-1}$ 特征值的正负号）。
- **Cas homoscédastique (LDA, $\Sigma_k = \Sigma$ pour tout $k$) :** Lorsque toutes les classes partagent la même covariance $\Sigma$, on a $\Sigma_k^{-1} - \Sigma_j^{-1} = 0$ et $\log(\det\Sigma_k/\det\Sigma_j) = 0$. Les termes quadratiques en $x$ et les déterminants s'annulent identiquement ! Il reste une équation **affine en $x$** :
- **同协方差情形（LDA，对所有 $k$ 有 $\Sigma_k = \Sigma$）：** 当所有类别共享同一个协方差矩阵 $\Sigma$ 时，$\Sigma_k^{-1} - \Sigma_j^{-1} = 0$ 且 $\log(\det\Sigma_k/\det\Sigma_j) = 0$，关于 $x$ 的二次项与行列式项完全抵消！此时对数后验比退化为**关于 $x$ 的仿射（线性）函数**：

$$
\log\left(\frac{\eta_k(x)}{\eta_j(x)}\right)
= \underbrace{\big(\Sigma^{-1}(m_k - m_j)\big)^T}_{\beta_{kj}^T} x
\;\underbrace{- \frac{1}{2}(m_k - m_j)^T \Sigma^{-1}(m_k + m_j) + \log\left(\frac{\pi_k}{\pi_j}\right)}_{b_{kj}}.
$$

En particulier, si $\pi_k = \pi_j$, l'hyperplan séparateur passe exactement par le milieu $\frac{1}{2}(m_k+m_j)$ du segment reliant les deux centres, et son vecteur normal est $\beta = \Sigma^{-1}(m_k - m_j)$. Si $\Sigma = \sigma^2 I_d$ (covariances sphériques), $\beta$ est colinéaire à $m_k - m_j$ (bissectrice perpendiculaire euclidienne) ; si $\Sigma$ est anisotrope, $\Sigma^{-1}$ fait pivoter l'hyperplan pour tenir compte de l'allongement des nuages de points (comme illustré sur la figure de la section 12).

特别地，当两类先验相等（$\pi_k = \pi_j$）时，分隔超平面恰好经过两类中心连线的中点 $\frac{1}{2}(m_k+m_j)$，其法向量为 $\beta = \Sigma^{-1}(m_k - m_j)$。若 $\Sigma = \sigma^2 I_d$（球形协方差），法向量直接指向均值差 $m_k - m_j$（即欧氏垂直平分面）；若 $\Sigma$ 各向异性，乘上 $\Sigma^{-1}$ 会根据点云的拉伸方向旋转分隔超平面（如第 12 节图示）。

**Pourquoi la QDA souffre-t-elle en grande dimension et comment fonctionne la régularisation de Friedman (1989) ?**

**为什么 QDA 在高维下代价高昂，以及 Friedman（1989）的插值正则化如何工作？**

En dimension $d$ avec $K$ classes, une matrice de covariance symétrique $\Sigma_k \in \mathbb{R}^{d\times d}$ possède $d(d+1)/2$ paramètres libres :

在 $d$ 维空间、$K$ 个类别的设定下，每个对称协方差矩阵 $\Sigma_k \in \mathbb{R}^{d\times d}$ 含有 $d(d+1)/2$ 个独立参数：

- **LDA** estime $K-1$ poids a priori, $K$ vecteurs moyennes ($Kd$ paramètres) et **une seule** covariance commune $\Sigma$ ($d(d+1)/2$ paramètres, estimée par la covariance intra-classe groupée $\hat{\Sigma} = \frac{1}{n}\sum_{k=1}^K \sum_{Y_i=k}(X_i-\hat{m}_k)(X_i-\hat{m}_k)^T$), soit $(K-1) + Kd + \frac{d(d+1)}{2}$ paramètres.
- **LDA** 只需估计 $K-1$ 个先验概率、$K$ 个均值向量（$Kd$ 个参数）以及**一个共享的**合并类内协方差矩阵 $\hat{\Sigma} = \frac{1}{n}\sum_{k=1}^K \sum_{Y_i=k}(X_i-\hat{m}_k)(X_i-\hat{m}_k)^T$（$d(d+1)/2$ 个参数），总参数量为 $(K-1) + Kd + \frac{d(d+1)}{2}$。
- **QDA** estime **une matrice $\Sigma_k$ par classe**, soit $(K-1) + Kd + K\frac{d(d+1)}{2}$ paramètres. Par exemple, pour $d=100$ et $K=10$, la QDA doit estimer $10 \times 5050 = 50\,500$ coefficients de covariance contre $5\,050$ pour la LDA ! De plus, si l'effectif $n_k$ d'une classe est inférieur ou égal à $d$, la covariance empirique $\hat{\Sigma}_k$ est de rang au plus $n_k - 1 < d$ : elle est **singulière** ($\det\hat{\Sigma}_k = 0$) et ne peut pas être inversée.
- **QDA** 则需**为每个类别单独估计一个 $\Sigma_k$**，总参数量达 $(K-1) + Kd + K\frac{d(d+1)}{2}$。例如当 $d=100, K=10$ 时，QDA 仅协方差参数就有 $10 \times 5050 = 50\,500$ 个，而 LDA 只需 $5\,050$ 个！更重要的是，只要某类的样本数 $n_k \le d$，该类的样本协方差矩阵 $\hat{\Sigma}_k$ 的秩至多为 $n_k - 1 < d$，必然**奇异不可逆**（$\det\hat{\Sigma}_k = 0$）。

La **Regularized Discriminant Analysis (RDA)** de Friedman (1989) résout ce problème par compromis biais–variance en interpolant entre la covariance par classe $\hat{\Sigma}_k$ et la covariance commune $\hat{\Sigma}$ (et éventuellement l'identité $\hat{\sigma}^2 I_d$) :

Friedman（1989）提出的**正则化判别分析（RDA）**通过偏差—方差权衡解决这一问题，将单类协方差估计 $\hat{\Sigma}_k$ 与合并协方差估计 $\hat{\Sigma}$ 作凸组合插值（注：原课件第 509 行公式右端写成了 $\hat{\Sigma}_k(\lambda)$，标准定义为对经验协方差 $\hat{\Sigma}_k$ 插值）：

$$
\hat{\Sigma}_k(\lambda) = \lambda \hat{\Sigma}_k + (1 - \lambda) \hat{\Sigma}, \qquad \lambda \in [0, 1].
$$

Pour $\lambda=1$, on retrouve la QDA ; pour $\lambda=0$, on retrouve la LDA. Lorsque meme $\hat{\Sigma}$ est mal conditionnée (cas $d > n$), on ajoute un second rétrécissement vers la matrice identité : $\hat{\Sigma}_k(\lambda,\gamma) = (1-\gamma)\hat{\Sigma}_k(\lambda) + \gamma \frac{\operatorname{Tr}(\hat{\Sigma}_k(\lambda))}{d} I_d$, ce qui garantit l'inversibilité pour tout $\gamma \in (0,1]$ exactement comme dans la régression Ridge.

当 $\lambda=1$ 时退化为 QDA，当 $\lambda=0$ 时退化为 LDA。若连合并协方差 $\hat{\Sigma}$ 也病态或不可逆（如 $d > n$），还可进一步向单位矩阵收缩：$\hat{\Sigma}_k(\lambda,\gamma) = (1-\gamma)\hat{\Sigma}_k(\lambda) + \gamma \frac{\operatorname{Tr}(\hat{\Sigma}_k(\lambda))}{d} I_d$，这与岭回归（Ridge）加 $\gamma I_d$ 保证正定可逆的机制完全一致。

<a id="section-14"></a>

Méthode # 2 : Analyse discriminante de Fisher (FDA)

## 方法 2：Fisher 判别分析（FDA）

**Principe de l'analyse discriminante de Fisher**

### Fisher 判别分析的原理

- Hypothèse : On considère deux lois gaussiennes pour $\mathcal{L}(X \mid Y)$

  假设：对 $\mathcal{L}(X \mid Y)$ 考虑两个高斯分布。
- Heuristique : On considère le séparateur linéaire qui maximise la distance entre les centres des lois projetées normalisée par la variance totale des projections sur le vecteur normal au séparateur.

  启发式思路：考虑一个线性分隔面，使两个分布投影后的中心距离相对于投影总方差最大；投影方向取分隔面的法向量。

![image](<Images/03_LMC/image_008.jpg>)

![image](<Images/03_LMC/image_009.jpg>)

Plus formellement : Notations pour i = 1, 2

更形式化地说：对 i = 1,2 使用以下记号。

- Gaussiennes $\mathcal{N}(\mu_i, \Sigma_i)$ échantillonnées en données de classification binaires

  从高斯分布 $\mathcal{N}(\mu_i, \Sigma_i)$ 中采样得到二分类数据。
- Estimateurs empiriques des paramètres $\hat{\mu}_{i}$ , $\hat{\Sigma}_{i}$

  参数的经验估计量 $\hat{\mu}_{i}$、$\hat{\Sigma}_{i}$。
- Centres projetés sur un vecteur $u \in \mathbb{R}^d: m_i(u) = u^T \hat{\mu}_i$

  投影到向量 $u \in \mathbb{R}^d: m_i(u) = u^T \hat{\mu}_i$ 上的中心。
- Dispersion des observations projetées :

  投影后观测的离散程度：

$$
\hat {S} _ {i} ^ {2} (u) = \sum_ {j: Y _ {j} = i} \left(u ^ {T} X _ {j} - m _ {i} (u)\right) ^ {2}
$$

- Critère à maximiser pour $u \in \mathbb{R}^d$ :

  对 $u \in \mathbb{R}^d$ 要最大化的准则：

$$
J (u) = \frac {(m _ {1} (u) - m _ {2} (u)) ^ {2}}{\hat {S} _ {1} ^ {2} (u) + \hat {S} _ {2} ^ {2} (u)} = \frac {u ^ {T} S _ {B} u}{u ^ {T} S _ {W} u}
$$

où $S_{B}$ et $S_{W}$ peuvent être interprétées comme des matrices de dispersion inter et intra-classes.

其中 $S_{B}$ 和 $S_{W}$ 分别可解释为类间散布矩阵与类内散布矩阵。

- La solution par lagrangien est obtenue via la résolution du problème aux valeurs propres :

  使用拉格朗日方法，通过求解以下特征值问题得到解：

$$
S _ {B} u = \lambda S _ {W} u
$$

Si $S_{W}$ de rang plein, alors la solution est explicite :

如果 $S_{W}$ 满秩，则解有显式表达：

$$
u = S _ {W} ^ {- 1} \big (\hat {\mu} _ {1} - \hat {\mu} _ {2} \big)
$$

- A noter que la direction $u$ n'est pas liée à la direction obtenue pour la PCA.

  注意，方向 $u$ 与 PCA 得到的方向无关。

<a id="reading-fisher-discriminant"></a>

**Complément — quotient de Rayleigh généralisé, dérivation de la solution de Fisher et comparaison avec la PCA**

**补充——广义瑞利商、Fisher 判别方向的拉格朗日推导及与 PCA 的对比**

L'analyse discriminante de Fisher (FDA) cherche une direction de projection $u \in \mathbb{R}^d \setminus \{0\}$ telle que les projections scalaires $u^T X_j$ des deux classes soient à la fois **le plus éloignées possible en moyenne** et **le plus concentrées possible à l'intérieur de chaque classe**.

Fisher 判别分析（FDA）寻找一个非零投影方向 $u \in \mathbb{R}^d \setminus \{0\}$，使得两类样本在该方向上的标量投影 $u^T X_j$ 满足：**类间均值距离尽可能大，同时类内投影方差之和尽可能小**。

En écrivant la différence des moyennes projetées au carré et la somme des dispersions intra-classes sous forme matricielle, on fait apparaître deux matrices symétriques semi-définies positives $S_B$ (*Between-class scatter*) et $S_W$ (*Within-class scatter*) :

将投影均值差平方与类内离散度之和写成二次型，即可定义半正定的**类间散布矩阵 $S_B$** 与**类内散布矩阵 $S_W$**：

$$
\big(m_1(u) - m_2(u)\big)^2 = \big(u^T(\hat{\mu}_1 - \hat{\mu}_2)\big)^2 = u^T \underbrace{(\hat{\mu}_1 - \hat{\mu}_2)(\hat{\mu}_1 - \hat{\mu}_2)^T}_{S_B} u,
$$

$$
\hat{S}_1^2(u) + \hat{S}_2^2(u) = u^T \underbrace{\left(\sum_{i=1}^2 \sum_{j:Y_j=i} (X_j - \hat{\mu}_i)(X_j - \hat{\mu}_i)^T\right)}_{S_W} u.
$$

Le critère de Fisher $J(u) = \frac{u^T S_B u}{u^T S_W u}$ est un **quotient de Rayleigh généralisé**. Remarquons que $J(\alpha u) = \frac{\alpha^2 u^T S_B u}{\alpha^2 u^T S_W u} = J(u)$ pour tout scalaire $\alpha \neq 0$ : seule la **direction** de $u$ compte, pas sa norme.

Fisher 准则 $J(u) = \frac{u^T S_B u}{u^T S_W u}$ 称为**广义瑞利商（generalized Rayleigh quotient）**。注意对任意非零标量 $\alpha \neq 0$，都有 $J(\alpha u) = \frac{\alpha^2 u^T S_B u}{\alpha^2 u^T S_W u} = J(u)$，即准则对缩放不变，只有 $u$ 的**方向**有意义，其长度可任意归一化。

**Dérivation : optimisation par lagrangien et pourquoi $u \propto S_W^{-1}(\hat{\mu}_1 - \hat{\mu}_2)$**

**推导：拉格朗日乘子法求解广义特征值问题及显式解的导出**

Puisque $J(u)$ est invariant par changement d'échelle $u \mapsto \alpha u$, maximiser $J(u)$ sur $\mathbb{R}^d \setminus \{0\}$ (en supposant $S_W$ définie positive) est strictement équivalent au problème sous contrainte :

由于 $J(u)$ 关于缩放 $u \mapsto \alpha u$ 不变，在 $S_W$ 正定的条件下，无约束最大化 $J(u)$ 等价于固定分母为 $1$ 并最大化分子：

$$
\max_{u \in \mathbb{R}^d} \; u^T S_B u \qquad \text{sous la contrainte / 满足} \quad u^T S_W u = 1.
$$

Formons le lagrangien $\mathcal{L}(u, \lambda) = u^T S_B u - \lambda (u^T S_W u - 1)$. Comme $S_B$ et $S_W$ sont symétriques, l'annulation du gradient par rapport à $u$ donne :

构造拉格朗日函数 $\mathcal{L}(u, \lambda) = u^T S_B u - \lambda (u^T S_W u - 1)$。利用 $S_B, S_W$ 的对称性，令关于 $u$ 的梯度为零：

$$
\nabla_u \mathcal{L}(u, \lambda) = 2 S_B u - 2 \lambda S_W u = 0 \implies S_B u = \lambda S_W u.
$$

En multipliant à gauche par $u^T$ et en utilisant $u^T S_W u = 1$, on voit que $\lambda = u^T S_B u = J(u)$ : le maximum $J(u)$ est donc la **plus grande valeur propre généralisée** du couple $(S_B, S_W)$.

左乘 $u^T$ 并代入 $u^T S_W u = 1$，可知乘子 $\lambda = u^T S_B u = J(u)$，因此目标函数的最大值就是矩阵对 $(S_B, S_W)$ 的**最大广义特征值**。

Dans le cas binaire ($K=2$), il n'est même pas nécessaire de diagonaliser une matrice $d\times d$ ! En effet, $S_B = (\hat{\mu}_1 - \hat{\mu}_2)(\hat{\mu}_1 - \hat{\mu}_2)^T$ est de **rang 1** : pour tout vecteur $u$, le produit

在二分类（$K=2$）情形下，甚至不需要做矩阵特征分解！因为 $S_B = (\hat{\mu}_1 - \hat{\mu}_2)(\hat{\mu}_1 - \hat{\mu}_2)^T$ 是**秩 1 矩阵**，对任意向量 $u$，乘积

$$
S_B u = (\hat{\mu}_1 - \hat{\mu}_2)\underbrace{\big((\hat{\mu}_1 - \hat{\mu}_2)^T u\big)}_{\text{scalaire / 标量 } c} = c (\hat{\mu}_1 - \hat{\mu}_2)
$$

est toujours colinéaire au vecteur différence des moyennes $\hat{\mu}_1 - \hat{\mu}_2$. Si $S_W$ est définie positive (inversible) et $\hat{\mu}_1 \neq \hat{\mu}_2$, l'équation $S_B u = \lambda S_W u$ avec $\lambda > 0$ implique donc $\lambda u = c S_W^{-1}(\hat{\mu}_1 - \hat{\mu}_2)$, c'est-à-dire, à une constante multiplicative non nulle près :

永远与均值差向量 $\hat{\mu}_1 - \hat{\mu}_2$ 共线。因此，当 $S_W$ 正定（可逆）且 $\hat{\mu}_1 \neq \hat{\mu}_2$ 时，方程 $S_B u = \lambda S_W u$（$\lambda > 0$）直接给出 $\lambda u = c S_W^{-1}(\hat{\mu}_1 - \hat{\mu}_2)$。相差一个非零比例常数，最优投影方向即为：

$$
u^* = S_W^{-1}(\hat{\mu}_1 - \hat{\mu}_2).
$$

On retrouve exactement la direction normale de l'hyperplan de la LDA (§11) ! La différence est que la FDA se formule comme un problème d'optimisation géométrique du rapport variance inter / variance intra sans imposer a priori la normalité des observations (voir le [tutoriel FDA du cours](../Tutorials/tutorial-FDA/Markdown/tutorial-FDA.md)).

这与 §11 中 LDA 超平面的法向量方向完全一致！区别在于 FDA 直接从“最大化类间方差与类内方差之比”的几何优化出发，推导过程本身不需要预先假设数据服从高斯分布（详见课程配套的 [FDA 专题教程](../Tutorials/tutorial-FDA/Markdown/tutorial-FDA.md)）。

**Pourquoi la direction de la FDA diffère-t-elle de celle de la PCA ?**

**为什么 FDA 的投影方向与主成分分析（PCA）截然不同？**

- **PCA (non supervisée) :** ignore totalement les étiquettes $Y_j$ et maximise la variance totale projetée $u^T S_T u / \|u\|_2^2$. Si deux classes forment deux nuages très allongés horizontalement (grande variance selon $x_1$, par ex. $\operatorname{Var}(X^{(1)})=100$) mais séparés verticalement (centres $(0,+1)$ et $(0,-1)$, petite variance intra-classe $\operatorname{Var}(X^{(2)}\mid Y)=0.01$), la première composante principale de la PCA choisit l'axe horizontal $(1,0)^T$, sur lequel les deux classes se superposent complètement !
- **PCA（无监督）：** 完全忽略标签 $Y_j$，只追求投影后的总体方差最大。设想两类样本在水平方向 $x_1$ 上拉得很长（例如 $\operatorname{Var}(X^{(1)})=100$），但在垂直方向 $x_2$ 上上下平行排布（中心分别为 $(0,+1)$ 与 $(0,-1)$，类内垂直方差仅为 $\operatorname{Var}(X^{(2)}\mid Y)=0.01$）。此时 PCA 的第一主成分会选择总方差最大的水平轴 $(1,0)^T$，投影后两类完全重叠，分类信息彻底丢失！
- **FDA (supervisée) :** divise par la variance intra-classe $u^T S_W u$ et choisit l'axe vertical $(0,1)^T$, où les deux classes sont parfaitement séparées.
- **FDA（有监督）：** 利用标签将类间距离除以类内方差 $u^T S_W u$，从而精准选出垂直轴 $(0,1)^T$，使两类在投影后完全分离。

<a id="logistic-model"></a>

<a id="section-15"></a>

Méthode # 3 : Régression logistique linéaire

## 方法 3：线性逻辑回归

- On $a: Y \in \{1, \ldots, K\}$ , $X \in \mathbb{R}^d$

  设 $Y\in\{1,\ldots,K\}$，$X\in\mathbb R^d$。
- On pose $\eta_k(x) = \mathbb{P}\{Y = k \mid X = x\}$ pour $k \in \{1, \ldots, K\}$

  对 $k \in \{1, \ldots, K\}$，记 $\eta_k(x) = \mathbb{P}\{Y = k \mid X = x\}$。
- On suppose que $\forall k$ , qu'il existe $\theta_k \in \mathbb{R}^d$ tel que

  假设 $\forall k$，存在 $\theta_k \in \mathbb{R}^d$，使得

$$
\log \left(\frac {\eta_ {k} (x)}{\eta_ {K} (x)}\right) = \theta_ {k} ^ {T} x
$$

- Ou bien :

  或者写成：

$$
\eta_ {k} (x) = \frac {\exp (\theta_ {k} ^ {T} x)}{1 + \sum_ {j = 1} ^ {K - 1} \exp (\theta_ {j} ^ {T} x)}
$$

et $\theta_{K}=1$ .

并且 $\theta_{K}=1$。

Fit d'un modèle de régression logistique

### 拟合逻辑回归模型

- On note $\theta = (\theta_1, \ldots, \theta_{K-1})$ et $\eta_k(x) = p_k(x, \theta)$

  记 $\theta = (\theta_1, \ldots, \theta_{K-1})$ 和 $\eta_k(x) = p_k(x, \theta)$。
- Log-vraisemblance

  对数似然：

$$
\ell (\theta) = \sum_ {i = 1} ^ {n} \log p _ {k} (X _ {i}, \theta)
$$

- Cas où $K = 2$ , $\theta \in \mathbb{R}^d$ , $p(x, \theta) = p_1(x, \theta)$

  $K = 2$、$\theta \in \mathbb{R}^d$、$p(x, \theta) = p_1(x, \theta)$ 的情形。

$$
\begin{array}{l} \ell (\theta) = \sum_ {i = 1} ^ {n} \big (Y _ {i} \log p (X _ {i}, \theta) + (1 - Y _ {i}) \log (1 - p (X _ {i}, \theta)) \big) \\ = \sum_ {i = 1} ^ {n} \big (Y _ {i} \theta^ {T} X _ {i} - \log (1 + \exp (\theta^ {T} X _ {i})) \big) \end{array}
$$

- Equation de score

  得分方程：

$$
\frac {\partial \ell}{\partial \theta} (\theta) = \sum_ {i = 1} ^ {n} X _ {i} \big (Y _ {i} - p (X _ {i}, \theta) \big) = 0
$$

- Matrice hessienne

  Hessian 矩阵：

$$
H _ {\ell} (\theta) = - \sum_ {i = 1} ^ {n} X _ {i} X _ {i} ^ {T} p (X _ {i}, \theta) \big (1 - p (X _ {i}, \theta) \big)
$$

- Schéma itératif de Newton-Raphson

  Newton–Raphson 迭代格式：

$$
\theta_ {t + 1} = \theta_ {t} - (H _ {\ell} (\theta_ {t})) ^ {- 1} \frac {\partial \ell}{\partial \theta} (\theta_ {t})
$$

- Se ramène à un estimateur des moindres carrés pondéré...

  归结为加权最小二乘估计……

<a id="section-16"></a>

**Limites des méthodes génératives**

## 生成式方法的局限

> **译注：** 原课件使用这个标题，但前面介绍的逻辑回归属于判别式方法，不属于生成式方法。

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

<a id="reading-logistic-regression-irls"></a>

**Complément — régression logistique, concavité de la log-vraisemblance, Newton–Raphson et moindres carrés repondérés (IRLS)**

**补充——逻辑回归、对数似然的凹性、Newton–Raphson 迭代与迭代重加权最小二乘（IRLS）**

Au lieu de modéliser séparément les densités $f_k(x)$ des entrées dans chaque classe comme la LDA, la **régression logistique linéaire** (§15) postule directement que les *log-odds* (logarithmes des rapports de probabilités a posteriori par rapport à une classe de référence $K$) sont des fonctions linéaires de $x$ :

与 LDA 分别对各类别的输入密度 $f_k(x)$ 建模不同，**线性逻辑回归**（§15）直接假设各类别相对于基准类 $K$ 的**对数几率（log-odds / logit）**是输入 $x$ 的线性函数：

$$
\log\left(\frac{\eta_k(x)}{\eta_K(x)}\right) = \theta_k^T x, \qquad k = 1, \dots, K-1.
$$

Comme la somme des probabilités vaut $\sum_{k=1}^K \eta_k(x) = 1$, on a $\eta_k(x) = \eta_K(x)\exp(\theta_k^T x)$ pour $k \le K-1$, d'où $\eta_K(x)\big(1 + \sum_{j=1}^{K-1}\exp(\theta_j^T x)\big) = 1$. On obtient ainsi la paramétrisation *softmax* (ou *log-linéaire*) :

由于所有类别的后验概率之和为 $\sum_{k=1}^K \eta_k(x) = 1$，将 $\eta_k(x) = \eta_K(x)\exp(\theta_k^T x)$（$k \le K-1$）代入求和，即得 $\eta_K(x)\big(1 + \sum_{j=1}^{K-1}\exp(\theta_j^T x)\big) = 1$，从而导出多分类的 **softmax（对数线性）** 表达式（注：课件第 624 行写 $\theta_K = 1$ 实指基准类的指数项 $\exp(\theta_K^T x) \equiv 1$，即取基准类参数向量 $\theta_K = 0$）：

$$
\eta_k(x) = \frac{\exp(\theta_k^T x)}{1 + \sum_{j=1}^{K-1} \exp(\theta_j^T x)} \quad (1 \le k \le K-1),
\qquad
\eta_K(x) = \frac{1}{1 + \sum_{j=1}^{K-1} \exp(\theta_j^T x)}.
$$

Dans le cas binaire ($K=2$, avec étiquette codée $Y_i \in \{0,1\}$ dans la log-vraisemblance de la section 15), la probabilité de la classe positive s'écrit à l'aide de la **fonction sigmoïde (logistique)** $\sigma(z) = \frac{e^z}{1+e^z} = \frac{1}{1+e^{-z}}$ :

在二分类情形下（$K=2$，第 15 节写对数似然时将标签编码为 $Y_i \in \{0,1\}$），正类后验概率由**逻辑（sigmoid）函数** $\sigma(z) = \frac{e^z}{1+e^z} = \frac{1}{1+e^{-z}}$ 给出：

$$
p(x, \theta) = \mathbb{P}(Y=1\mid X=x) = \sigma(\theta^T x) = \frac{\exp(\theta^T x)}{1 + \exp(\theta^T x)}.
$$

**Dérivation : équation de score, matrice hessienne négative et équivalence Newton–Raphson / IRLS**

**推导：得分方程、负半定 Hessian 矩阵，以及为什么 Newton–Raphson 归结为加权最小二乘（IRLS）**

Pour $Y_i \in \{0,1\}$, la probabilité conditionnelle d'observer $Y_i$ sachant $X_i$ s'écrit de manière compacte $p(X_i,\theta)^{Y_i}\big(1-p(X_i,\theta)\big)^{1-Y_i}$. Sur $n$ observations indépendantes, la log-vraisemblance conditionnelle vaut :

对 $Y_i \in \{0,1\}$，给定 $X_i$ 观测到 $Y_i$ 的条件概率可紧凑地写为 $p(X_i,\theta)^{Y_i}\big(1-p(X_i,\theta)\big)^{1-Y_i}$。在 $n$ 个独立样本上，条件对数似然为：

$$
\begin{aligned}
\ell(\theta)
&= \sum_{i=1}^n \Big[ Y_i \log p(X_i,\theta) + (1 - Y_i)\log\big(1 - p(X_i,\theta)\big) \Big] \\
&= \sum_{i=1}^n \Big[ Y_i \log\frac{p(X_i,\theta)}{1-p(X_i,\theta)} + \log\big(1 - p(X_i,\theta)\big) \Big] \\
&= \sum_{i=1}^n \Big[ Y_i \theta^T X_i - \log\big(1 + \exp(\theta^T X_i)\big) \Big].
\end{aligned}
$$

1. **Gradient (équation de score) 梯度（得分方程） :** Comme $\frac{d}{dz}\log(1+e^z) = \frac{e^z}{1+e^z} = \sigma(z) = p(x,\theta)$, la dérivation par rapport au vecteur $\theta \in \mathbb{R}^d$ donne immédiatement :
   由于 $\frac{d}{dz}\log(1+e^z) = \frac{e^z}{1+e^z} = \sigma(z) = p(x,\theta)$，对参数向量 $\theta \in \mathbb{R}^d$ 求梯度立得：

$$
\nabla\ell(\theta) = \sum_{i=1}^n X_i \big(Y_i - p(X_i, \theta)\big) = \mathbf{X}^T (\mathbf{Y} - \mathbf{p}(\theta)) = 0,
$$

où $\mathbf{X} \in \mathbb{R}^{n\times d}$ est la matrice de design de lignes $X_i^T$, $\mathbf{Y} = (Y_1,\dots,Y_n)^T$ et $\mathbf{p}(\theta) = \big(p(X_1,\theta),\dots,p(X_n,\theta)\big)^T$. À l'optimum, les résidus de probabilité $Y_i - p(X_i,\hat{\theta})$ sont orthogonaux à chaque colonne de $\mathbf{X}$.

其中 $\mathbf{X} \in \mathbb{R}^{n\times d}$ 是以 $X_i^T$ 为行的设计矩阵，$\mathbf{Y} = (Y_1,\dots,Y_n)^T$，$\mathbf{p}(\theta) = \big(p(X_1,\theta),\dots,p(X_n,\theta)\big)^T$。在极大似然解处，概率残差向量 $Y_i - p(X_i,\hat{\theta})$ 与设计矩阵 $\mathbf{X}$ 的每一列正交。

2. **Matrice hessienne et concavité Hessian 矩阵与凹性证明 :** Comme $\frac{d}{dz}\sigma(z) = \sigma(z)(1-\sigma(z))$, on a $\nabla_\theta p(X_i,\theta) = p(X_i,\theta)\big(1-p(X_i,\theta)\big) X_i$. En dérivant une seconde fois :
   利用 $\frac{d}{dz}\sigma(z) = \sigma(z)(1-\sigma(z))$，有 $\nabla_\theta p(X_i,\theta) = p(X_i,\theta)\big(1-p(X_i,\theta)\big) X_i$。再次求导得到 Hessian 矩阵：

$$
H_\ell(\theta) = \nabla^2\ell(\theta) = -\sum_{i=1}^n p(X_i,\theta)\big(1 - p(X_i,\theta)\big) X_i X_i^T = -\mathbf{X}^T \mathbf{W}(\theta) \mathbf{X},
$$

où $\mathbf{W}(\theta) = \operatorname{diag}\big(w_1(\theta),\dots,w_n(\theta)\big)$ avec $w_i(\theta) = p(X_i,\theta)\big(1-p(X_i,\theta)\big) \in (0, 1/4]$. Pour tout vecteur $v \in \mathbb{R}^d$,

其中对角权重矩阵 $\mathbf{W}(\theta) = \operatorname{diag}\big(w_1(\theta),\dots,w_n(\theta)\big)$ 的对角元为预测伯努利方差 $w_i(\theta) = p(X_i,\theta)\big(1-p(X_i,\theta)\big) \in (0, 1/4]$。对任意向量 $v \in \mathbb{R}^d$：

$$
v^T H_\ell(\theta) v = -\sum_{i=1}^n w_i(\theta) (X_i^T v)^2 \le 0.
$$

La matrice hessienne $H_\ell(\theta)$ est donc **semi-définie négative** partout (et strictement définie négative dès que $\mathbf{X}$ est de rang plein $d$) : la log-vraisemblance $\ell(\theta)$ est **concave**, ce qui exclut tout mauvais maximum local !

因此 Hessian 矩阵 $H_\ell(\theta)$ 处处**负半定**（当 $\mathbf{X}$ 满列秩 $d$ 时严格负定）：对数似然 $\ell(\theta)$ 是关于 $\theta$ 的**凹函数**（等价于负对数似然／逻辑损失是凸函数），不会陷入局部次优极大值！

3. **Pourquoi Newton–Raphson se ramène à des moindres carrés pondérés (IRLS) 为什么 Newton–Raphson 迭代归结为加权最小二乘（IRLS） :** En substituant $\nabla\ell(\theta_t) = \mathbf{X}^T(\mathbf{Y}-\mathbf{p}_t)$ et $H_\ell(\theta_t) = -\mathbf{X}^T\mathbf{W}_t\mathbf{X}$ dans le schéma de Newton–Raphson :
   将 $\nabla\ell(\theta_t) = \mathbf{X}^T(\mathbf{Y}-\mathbf{p}_t)$ 与 $H_\ell(\theta_t) = -\mathbf{X}^T\mathbf{W}_t\mathbf{X}$ 代入 Newton–Raphson 迭代公式：

$$
\begin{aligned}
\theta_{t+1}
&= \theta_t - \big(H_\ell(\theta_t)\big)^{-1} \nabla\ell(\theta_t) \\
&= \theta_t + \big(\mathbf{X}^T \mathbf{W}_t \mathbf{X}\big)^{-1} \mathbf{X}^T (\mathbf{Y} - \mathbf{p}_t) \\
&= \big(\mathbf{X}^T \mathbf{W}_t \mathbf{X}\big)^{-1} \mathbf{X}^T \mathbf{W}_t \underbrace{\Big(\mathbf{X}\theta_t + \mathbf{W}_t^{-1}(\mathbf{Y} - \mathbf{p}_t)\Big)}_{\mathbf{z}_t}.
\end{aligned}
$$

On reconnaît exactement la formule des **moindres carrés pondérés** $\arg\min_\theta (\mathbf{z}_t - \mathbf{X}\theta)^T \mathbf{W}_t (\mathbf{z}_t - \mathbf{X}\theta)$ avec la pseudo-réponse courante $z_{t,i} = X_i^T\theta_t + \frac{Y_i - p_{t,i}}{p_{t,i}(1-p_{t,i})}$ et les poids $w_{t,i} = p_{t,i}(1-p_{t,i})$ : d'où le nom **IRLS (*Iteratively Reweighted Least Squares*)**.

最后一行的形式正是以工作响应向量 $z_{t,i} = X_i^T\theta_t + \frac{Y_i - p_{t,i}}{p_{t,i}(1-p_{t,i})}$ 为目标、以 $w_{t,i} = p_{t,i}(1-p_{t,i})$ 为样本权重的**加权最小二乘解** $\arg\min_\theta (\mathbf{z}_t - \mathbf{X}\theta)^T \mathbf{W}_t (\mathbf{z}_t - \mathbf{X}\theta)$！这就是教材末句“归结为加权最小二乘估计”即 **IRLS（迭代重加权最小二乘）** 的完整数学由来。

**LDA vs Régression logistique : même forme linéaire des log-odds, mais hypothèses différentes**

**LDA 与逻辑回归的联系与区别：同为线性对数几率，但假设强度不同**

La LDA (§11) et la régression logistique (§15) conduisent toutes deux à un log-odds linéaire $\log\frac{\eta_1(x)}{\eta_2(x)} = b + \beta^T x$. Cependant, la LDA obtient $(\beta, b)$ en supposant que $X\mid Y=k$ est **gaussien homoscédastique**, ce qui oblige à estimer les moyennes et les $d(d+1)/2$ paramètres de covariance. La régression logistique n'impose aucune loi paramétrique sur $X$ (qui peut contenir des variables binaires, discrètes ou asymétriques) et n'estime que les $d$ paramètres de la frontière. En contrepartie, si les deux classes sont **strictement linéairement séparables** dans l'échantillon, la log-vraisemblance logistique non pénalisée n'atteint son suprémum ($0$) qu'à l'infini ($\|\theta\|\to\infty$, les probabilités prédites tendant vers $0$ et $1$) et le maximum de vraisemblance fini n'existe pas. Ajouter une pénalité coercive ($\lambda > 0$) restaure l'existence d'un minimiseur fini : une pénalité Ridge $\lambda\|\theta\|_2^2$ (sur l'ensemble des paramètres) rend l'objectif strictement convexe et garantit donc un minimiseur fini **unique**, tandis qu'une pénalité Lasso $\lambda\|\theta\|_1$ garantit l'**existence** d'au moins un minimiseur fini mais pas nécessairement son unicité en présence de variables colinéaires ou dupliquées (voir aussi le [tutoriel LDA, section 9](../Tutorials/tutorial-LDA/Markdown/09_Relation%20to%20Logistic%20Regression.md)).

LDA（§11）与逻辑回归（§15）都给出线性的对数后验几率 $\log\frac{\eta_1(x)}{\eta_2(x)} = b + \beta^T x$。但 LDA 通过假设 $X\mid Y=k$ 服从**同协方差高斯分布**来反推 $(\beta,b)$，必须估计均值和 $d(d+1)/2$ 个协方差参数；逻辑回归则不对 $X$ 的分布作高斯假设（因此 $X$ 中可以包含二元特征、离散计数或偏态变量），直接估计分界面的参数。需要注意的一个边界情形是：如果训练样本**严格线性可分**，无惩罚逻辑回归的对数似然只有当 $\|\theta\|\to\infty$（预测概率趋于阶跃的 $0$ 或 $1$）时才逼近上确界 $0$，此时有限的极大似然解不存在。加入强制性（coercive）正则化项（$\lambda > 0$）可恢复有限最优解的**存在性**：对全部参数施加 $\ell_2$（Ridge）惩罚 $\lambda\|\theta\|_2^2$ 会使目标函数严格凸（对数似然严格凹），从而保证有限最优解**唯一**；而施加 $\ell_1$（Lasso）惩罚 $\lambda\|\theta\|_1$ 虽能保证有限最优解**存在**，但因 $\ell_1$ 范数非严格凸，当存在共线或重复特征时解不必唯一（例如两个样本 $x_1=(1,1), y_1=1$ 与 $x_2=(-1,-1), y_2=0$ 下最小化逻辑损失加 $\frac{1}{2}(|\theta_1|+|\theta_2|)$，所有满足 $\theta_1,\theta_2\ge 0$ 且 $\theta_1+\theta_2=\log 3$ 的参数均为最优解；另参见课程配套的 [LDA 专题教程第 9 节](../Tutorials/tutorial-LDA/Markdown/09_Relation%20to%20Logistic%20Regression.md)）。

<a id="scoring"></a>

<a id="section-17"></a>

De la classification au scoring : Courbe ROC et AUC

## 从分类到评分：ROC 曲线与 AUC

- Décomposition de l'erreur de classification

  分类误差的分解：

$$
L (g) = \mathbb {P} \left\{g (X) = + 1, Y = - 1 \right\} + \mathbb {P} \left\{g (X) = - 1, Y = + 1 \right\}
$$

- Taux de faux positifs

  假阳性率。

$$
\alpha (g) = \mathbb {P} \left\{g (X) = + 1 \mid Y = - 1 \right\}
$$

- Taux de vrais positifs

  真阳性率。

$$
\beta (g) = \mathbb {P} \left\{g (X) = + 1 \mid Y = + 1 \right\}
$$

- On remarque que :

  注意到：

$$
L (g) = \mathbb {P} \{Y \neq g (X) \} = (1 - p) \alpha (g) + p (1 - \beta (g))
$$

**Diagramme α-β**

### α–β 图

- Pour une proportion $p$ fixée, une erreur de classification fixée $L(g) = L$ , on a :

  对固定比例 $p$ 和固定分类误差 $L(g) = L$，有：

$$
\beta = \left(\frac {1 - p}{p}\right) \alpha + 1 - \frac {L}{p}
$$

![image](<Images/03_LMC/image_010.jpg>)

- Sous l'observation $X$ , tester

  给定观测 $X$，检验

$$
H _ {0}: Y = - 1 \quad \text{对立假设} \quad H _ {1}: Y = + 1
$$

- Statistique de test optimale (Neyman-Pearson)

  最优检验统计量（Neyman–Pearson）：

$$
T ^ {*} (X) = \frac {1 - p}{p} \cdot \frac {\eta (X)}{1 - \eta (X)}
$$

• $\alpha = \text{第一类错误率}$

- $\beta =$ Puissance du test

  $\beta =$：检验功效。

<a id="section-18"></a>

**Classifieur de Neyman-Pearson**

## Neyman–Pearson 分类器

- Pour $\alpha$ fixé, la région de rejet est :

  对固定的 $\alpha$，拒绝域为：

$$
R _ {\alpha} ^ {*} = \left\{x: \eta (x) > Q ^ {-} (\eta , \alpha) \right\}
$$

$$
Q^-(\eta,\alpha)=\mathcal L(\eta(X)\mid Y=-1)\text{ 的 }(1-\alpha)\text{ 分位数}.
$$

- Soit le classifieur :

  定义分类器：

$$
g _ {\alpha} ^ {*} (x) = 2 \mathbb {I} \left\{x \in R _ {\alpha} ^ {*} \right\} - 1
$$

- En général : $L(g_{\alpha}^{*}) > L^{*}$ sauf si $Q^{-}(\eta, \alpha) = 1/2$

  一般有 $L(g_{\alpha}^{*}) > L^{*}$，除非 $Q^{-}(\eta, \alpha) = 1/2$。

> **译注：** 原句的“除非”过强：不同阈值若在有概率质量的区域产生相同决策，也可能达到相同的 Bayes 风险；离散评分的精确误报水平还可能需要阈值处随机化。

- Soit $\beta^{*}(\alpha) = \beta(g_{\alpha}^{*})$

  令 $\beta^{*}(\alpha) = \beta(g_{\alpha}^{*})$。

![image](<Images/03_LMC/image_011.jpg>)

Notations
Performance d'une règle de scoring

### 记号：评分规则的性能

- Consider $s: \mathbb{R}^d \to \mathbb{R}$ a detector response (socring rule)

  考虑一个检测器的响应 $s: \mathbb{R}^d \to \mathbb{R}$，即评分规则。
- A hit corresponds to $Y = +1$ , an alarm to $\{s(X) \geq t\}$

  命中对应 $Y = +1$，报警对应 $\{s(X) \geq t\}$。
- True positive rate and false positive rate :

  真阳性率与假阳性率：

$$
\begin{array}{l l} \beta (s, t) = & \mathbb {P} \left\{s (X) \geq t \mid Y = + 1 \right\} \quad (\text {TPR}) \to \max \\ \alpha (s, t) = & \mathbb {P} \left\{s (X) \geq t \mid Y = - 1 \right\} \quad (\text {FPR}) \to \min \end{array}
$$

- Main point : trade-off required since

  关键点：需要权衡，因为

$$
\begin{array}{l l l l} \beta (s, t) \to 1 & \text{但} & \alpha (s, t) \to 1 & \text{当} t \to - \infty \\ \alpha (s, t) \to 0 & \text{但} & \beta (s, t) \to 0 & \text{当} t \to + \infty \end{array}
$$

Courbes ROC idéales

### 理想 ROC 曲线

![image](<Images/03_LMC/image_012.jpg>)

![image](<Images/03_LMC/image_013.jpg>)

- Pour $s: \mathbb{R}^d \to \mathbb{R}$ règle fixée

  对固定的规则 $s: \mathbb{R}^d \to \mathbb{R}$。
- Courbe ROC d'une règle de scoring s :

  评分规则 s 的 ROC 曲线：

$$
t \in \mathbb {R} \mapsto (\alpha_ {s} (t), \beta_ {s} (t))
$$

<a id="section-19"></a>

**Optimal elements for scoring**

## 评分的最优解

- $X \in \mathbb{R}^d$ - observation vector in a high dimensional space

  $X \in \mathbb{R}^d$：高维空间中的观测向量。
- $Y \in \{-1, +1\}$ - binary diagnosis (i.e. classification data)

  $Y \in \{-1, +1\}$：二元诊断，即分类数据。
- Key theoretical quantity (posterior probability)

  关键理论量（后验概率）：

$$
\eta (x) = \mathbb {P} \{Y = 1 \mid X = x \}, \quad \forall x \in \mathbb {R} ^ {d}
$$

- Optimal scoring rules :

  最优评分规则：

$\Rightarrow$ increasing transformations of $\eta$

$\Rightarrow$ $\eta$ 的递增变换。

<a id="section-20"></a>

Critère pratique - Aire sous la courbe ROC (AUC)

## 实用准则：ROC 曲线下面积（AUC）

- Pour toute règle de scoring $s$ , soit :

  对任意评分规则 $s$，令：

$$
\begin{array}{l l} \text {AUC} (s) & = \int_ {0} ^ {1} \text {ROC} (s, \alpha) d \alpha \\ & = \mathbb {P} \{s (X) > s (X ^ {\prime}) | Y > Y ^ {\prime} \} \\ & \qquad + \frac {1}{2} \mathbb {P} \{s (X) = s (X ^ {\prime}) | Y > Y ^ {\prime} \} \end{array}
$$

où $(X, Y)$ , $(X', Y')$ i.i.d.

其中 $(X, Y)$、$(X', Y')$ 独立同分布。

- AUC maximale

  最大 AUC：

$$
\mathrm{AUC} ^ {*} = \mathrm{AUC} (\eta) = \frac {1}{2} + \frac {\mathbb {E} (| \eta (X) - \eta (X ^ {\prime}) |)}{4 p (1 - p)},
$$

- La convergence au sens de l'AUC correspond à la convergence $L_{1}$ des courbes ROC

  AUC 意义下的收敛对应于 ROC 曲线的 $L_{1}$ 收敛。

> **译注：** 这里应结合最优 ROC 包络理解面积差与 $L_1$ 差距。任意两条相交 ROC 曲线的 AUC 接近，不保证两条曲线接近。

**- Curves :**

### 曲线

- ROC curve

  ROC 曲线。
- (Precision-Recall curve)

  （精确率—召回率曲线。）
- (Lift curve)

  （提升曲线。）

**- Summaries :**

### 汇总指标

- AUC (global measure)

  AUC（全局度量）。
- Partial AUC

  部分 AUC。

(Dodd and Pepe '03)

（Dodd 与 Pepe，2003。）

**- Local AUC**

### 局部 AUC

(Clémençon and Vayatis '07)

（Clémençon 与 Vayatis，2007。）

![image](<Images/03_LMC/image_014.jpg>)

ROC curves.

ROC 曲线。

**- Curves :**

### 曲线

- ROC curve

  ROC 曲线。
- (Precision-Recall curve)

  （精确率—召回率曲线。）
- (Lift curve)

  （提升曲线。）

**- Summaries :**

### 汇总指标

- AUC (global measure)

  AUC（全局度量）。
• Partial AUC
(Dodd and Pepe '03)

- 部分 AUC（Dodd 与 Pepe，2003）。

**- Local AUC**

### 局部 AUC

(Clémençon and Vayatis '07)

（Clémençon 与 Vayatis，2007。）

![image](<Images/03_LMC/image_015.jpg>)

ROC curves.

ROC 曲线。

<a id="section-21"></a>

**Performance measures for scoring**

## 评分的性能度量

**- Curves :**

### 曲线

- ROC curve

  ROC 曲线。
- (Precision-Recall curve)

  （精确率—召回率曲线。）
- (Lift curve)

  （提升曲线。）

**- Summaries :**

### 汇总指标

- AUC (global measure)

  AUC（全局度量）。
• Partial AUC
(Dodd and Pepe '03)

- 部分 AUC（Dodd 与 Pepe，2003）。
- Local AUC
(Clémençon and Vayatis '07)

- 局部 AUC（Clémençon 与 Vayatis，2007）。

![image](<Images/03_LMC/image_016.jpg>)

Partial AUC.

部分 AUC。

<a id="section-22"></a>

**Performance measures for scoring**

## 评分的性能度量

**- Curves :**

### 曲线

- ROC curve

  ROC 曲线。
- (Precision-Recall curve)

  （精确率—召回率曲线。）
- (Lift curve)

  （提升曲线。）

**- Summaries :**

### 汇总指标

- AUC (global measure)

  AUC（全局度量）。
• Partial AUC
(Dodd and Pepe '03)

- 部分 AUC（Dodd 与 Pepe，2003）。
- Local AUC
(Clémençon and Vayatis '07)

- 局部 AUC（Clémençon 与 Vayatis，2007）。

![image](<Images/03_LMC/image_017.jpg>)

Inconsistency of Partial AUC.

部分 AUC 的不一致性。

<a id="section-23"></a>

**Performance measures for scoring**

## 评分的性能度量

**- Curves :**

### 曲线

- ROC curve

  ROC 曲线。
- (Precision-Recall curve)

  （精确率—召回率曲线。）
- (Lift curve)

  （提升曲线。）

**- Summaries :**

### 汇总指标

- AUC (global measure)

  AUC（全局度量）。
• Partial AUC
(Dodd and Pepe '03)

- 部分 AUC（Dodd 与 Pepe，2003）。
- Local AUC
(Clémençon and Vayatis '07)

- 局部 AUC（Clémençon 与 Vayatis，2007）。

![image](<Images/03_LMC/image_018.jpg>)

Local AUC.

局部 AUC。

<a id="reading-roc-neyman-pearson-auc"></a>

**Complément — lemme de Neyman–Pearson, géométrie de la courbe ROC et interprétation probabiliste de l'AUC**

**补充——Neyman–Pearson 引理、ROC 曲线的几何性质与 AUC 的概率等价性证明**

Les sections 17 à 23 passent de la classification à coût symétrique au problème du **scoring** et de la **détection sous contrainte de fausses alarmes**.

第 17 至 23 节从对称误判率分类过渡到**评分排序（scoring）**与**受控误报率下的最优检测**。

1. **Pourquoi l'erreur globale $L(g)$ ne suffit pas (classes déséquilibrées et coûts asymétriques) 为什么总体错误率 $L(g)$ 往往不够用（类别不平衡与非对称代价）**
   La relation $L(g) = (1-p)\alpha(g) + p(1-\beta(g))$ (§17) montre que l'erreur globale mélange deux types d'erreurs aux conséquences très différentes :
   - $\alpha(g) = \mathbb{P}(g(X)=+1 \mid Y=-1)$ : **taux de faux positifs (FPR / erreur de première espèce)** — déclencher une fausse alarme chez un individu sain ou bloquer un email légitime.
   - $1 - \beta(g) = \mathbb{P}(g(X)=-1 \mid Y=+1)$ : **taux de faux négatifs (FNR / erreur de deuxième espèce)**, complémentaire du **taux de vrais positifs (TPR / sensibilité / rappel / puissance)** $\beta(g) = \mathbb{P}(g(X)=+1 \mid Y=+1)$.
   Si la classe positive est rare ($p = 0.01$, ex. fraude ou maladie rare), le classifieur trivial $g \equiv -1$ obtient $\alpha=0, \beta=0$ et une erreur globale $L(g) = p = 1\%$ en ratant $100\%$ des cas positifs ! Par ailleurs, dans le plan $(\alpha, \beta)$, les droites d'iso-erreur $\beta = \frac{1-p}{p}\alpha + 1 - \frac{L}{p}$ ont pour pente $\frac{1-p}{p}$ : minimiser $L(g)$ revient à chercher le point de la région atteignable qui touche la droite de pente $\frac{1-p}{p}$ la plus haute (c'est-à-dire d'ordonnée à l'origine $1 - L/p$ maximale).

   分解式 $L(g) = (1-p)\alpha(g) + p(1-\beta(g))$（§17）表明，总体分类误差混合了性质截然不同的两类错误：
   - $\alpha(g) = \mathbb{P}(g(X)=+1 \mid Y=-1)$：**假阳性率（FPR／第一类错误率／误报率）**，即把负例误判为正例。
   - $1 - \beta(g) = \mathbb{P}(g(X)=-1 \mid Y=+1)$：**假阴性率（FNR／第二类错误率／漏报率）**，其补集 $\beta(g) = \mathbb{P}(g(X)=+1 \mid Y=+1)$ 即为**真阳性率（TPR／灵敏度／召回率／检验功效）**。
   当正类极少（如 $p = 0.01$ 的欺诈检测或罕见病筛查）时，全猜负类的平凡分类器 $g \equiv -1$ 有 $\alpha=0, \beta=0$，总体错误率低至 $L(g) = p = 1\%$，却漏掉了 $100\%$ 的真正例！此外，在 $(\alpha,\beta)$ 平面上，等错误率线 $\beta = \frac{1-p}{p}\alpha + 1 - \frac{L}{p}$ 的斜率为 $\frac{1-p}{p}$：最小化 $L(g)$ 几何上等价于用斜率为 $\frac{1-p}{p}$ 的直线从上方切触可达区域，使纵截距 $1 - L/p$ 最大。

2. **Classification de Neyman–Pearson et optimalité de $\eta(X)$ (§18–19) Neyman–Pearson 准则与后验概率 $\eta(X)$ 的最优性**
   Dans beaucoup d'applications (radar, diagnostic, ciblage budgété), on fixe un budget maximal de fausses alarmes $\alpha_0 \in (0,1)$ et l'on cherche à maximiser le taux de détection $\beta(g)$ sous la contrainte $\alpha(g) \le \alpha_0$. D'après le **lemme de Neyman–Pearson**, le test le plus puissant seuille le rapport de vraisemblance $\frac{dP_+}{dP_-}(X) = \frac{1-p}{p}\frac{\eta(X)}{1-\eta(X)}$. Comme la fonction $u \mapsto \frac{1-p}{p}\frac{u}{1-u}$ est strictement croissante sur $[0,1)$, seuiller $T^*(X)$ est strictement équivalent à seuiller la probabilité a posteriori $\eta(X)$ au quantile d'ordre $1-\alpha_0$ de la loi de $\eta(X)$ sous $Y=-1$.
   Plus généralement (**§19**), toute transformation strictement croissante $\phi\circ\eta$ de $\eta$ induit exactement le même ordre sur les observations et possède donc la **même courbe ROC optimale** $\beta^*(\alpha)$ !

   在雷达检测、医学筛查或预算受限的定向营销中，人们通常先规定可容忍的最大误报率上限 $\alpha_0 \in (0,1)$，再在此约束下最大化命中率 $\beta(g)$。根据统计学中的 **Neyman–Pearson 引理**，固定第一类错误率 $\alpha_0$ 时功效 $\beta$ 最大的检验必定是对似然比统计量 $T^*(X) = \frac{dP_+}{dP_-}(X) = \frac{1-p}{p}\frac{\eta(X)}{1-\eta(X)}$ 进行阈值截断。由于 $u \mapsto \frac{1-p}{p}\frac{u}{1-u}$ 在 $[0,1)$ 上严格单调递增，对 $T^*(X)$ 设阈值完全等价于对后验概率 $\eta(X)$ 在负类分布的 $1-\alpha_0$ 分位数 $Q^-(\eta,\alpha_0)$ 处设阈值。
   更一般地（**§19**），对 $\eta(x)$ 施加任意**严格单调递增变换** $\phi\circ\eta$，都不会改变任意两个样本得分的高低次序，因此当阈值遍历 $\mathbb{R}$ 时会掃出**完全相同的最优 ROC 曲线** $\beta^*(\alpha)$！

**Dérivation : pourquoi l'aire géométrique sous la courbe ROC égale la probabilité de classement pair-à-pair (AUC)**

**推导：为什么 ROC 曲线下的几何面积恰好等于正负样本对的正确排序概率（AUC）**

Soient $(X,Y)$ et $(X',Y')$ deux couples indépendants de même loi $P$. Conditionnellement à l'événement $\{Y > Y'\} = \{Y=+1, Y'=-1\}$, la variable $X$ suit la loi positive $P_+$ et la variable $X'$ suit indépendamment la loi négative $P_-$. Supposons pour simplifier que les scores $s(X)$ et $s(X')$ ont des lois continues (sans ex-aequo, soit $\mathbb{P}(s(X)=s(X')\mid Y>Y')=0$).

设 $(X,Y)$ 与 $(X',Y')$ 是独立同分布的两个样本对。在事件 $\{Y > Y'\} = \{Y=+1, Y'=-1\}$ 的条件下，$X \sim P_+$ 与 $X' \sim P_-$ 相互独立。先考虑得分分布连续（无平局，即 $\mathbb{P}(s(X)=s(X')\mid Y>Y')=0$）的情形。

Pour tout seuil $t \in \mathbb{R}$, rappelons que $\beta_s(t) = \mathbb{P}(s(X) \ge t \mid Y=+1)$ et $\alpha_s(t) = \mathbb{P}(s(X') \ge t \mid Y=-1) = 1 - F_-(t)$, où $F_-$ est la fonction de répartition de $s(X')$ sachant $Y'=-1$. Lorsque $t$ décroît de $+\infty$ à $-\infty$, $\alpha = \alpha_s(t)$ croît de $0$ à $1$ avec $d\alpha = -dF_-(t)$. L'aire géométrique sous la courbe ROC vaut alors, par conditionnement par rapport à $t = s(X')$ :

对任意阈值 $t \in \mathbb{R}$，回记 $\beta_s(t) = \mathbb{P}(s(X) \ge t \mid Y=+1)$，$\alpha_s(t) = \mathbb{P}(s(X') \ge t \mid Y=-1) = 1 - F_-(t)$，其中 $F_-$ 是负类得分 $s(X')$ 的累积分布函数。当阈值 $t$ 从 $+\infty$ 降到 $-\infty$ 时，横坐标 $\alpha = \alpha_s(t)$ 从 $0$ 增至 $1$，且微分满足 $d\alpha = -dF_-(t)$。于是 ROC 曲线下的几何面积可通过对 $t = s(X')$ 取条件期望化为：

$$
\begin{aligned}
\operatorname{AUC}(s)
&= \int_0^1 \beta_s\big(\alpha_s^{-1}(\alpha)\big)\, d\alpha
 = \int_{-\infty}^{+\infty} \beta_s(t)\, dF_-(t) \\
&= \int_{-\infty}^{+\infty} \mathbb{P}\big(s(X) \ge t \;\big|\; Y=+1\big)\, dF_-(t) \\
&= \mathbb{E}_{X'\sim P_-}\Big[\mathbb{P}\big(s(X) > s(X') \;\big|\; Y=+1, X'\big)\Big] \\
&= \mathbb{P}\big(s(X) > s(X') \;\big|\; Y=+1, Y'=-1\big).
\end{aligned}
$$

Si la loi du score présente des atomes (ex. arbre de décision ou scores discrets pouvant produire des ex-aequo $s(X)=s(X')$), relier linéairement les points $(\alpha_s(t),\beta_s(t))$ aux sauts ajoute l'aire des trapèzes correspondants, ce qui introduit exactement le terme de demi-probabilité $\frac{1}{2}\mathbb{P}(s(X)=s(X')\mid Y>Y')$ de la formule de la section 20 !

若得分分布含有离散点质量（例如决策树叶节点得分可能出现平局 $s(X)=s(X')$），在 ROC 图上用线段连接跳跃点会形成梯形，梯形三角形部分的面积恰好对应第 20 节公式中的平局折半项 $\frac{1}{2}\mathbb{P}(s(X)=s(X')\mid Y>Y')$！

**Exemple numérique à 4 points 手算示例（4 个样本） :** Supposons 2 positifs de scores $\{0.9, 0.4\}$ et 2 négatifs de scores $\{0.6, 0.2\}$. Il y a $2\times 2 = 4$ paires $(X_+, X_-)$ :
- Pour $s(X_+)=0.9$ : bat $0.6$ et $0.2$ ($2$ paires gagnantes).
- Pour $s(X_+)=0.4$ : perd contre $0.6$, mais bat $0.2$ ($1$ paire gagnante).
Au total, $3$ paires sur $4$ sont bien ordonnées, donc $\operatorname{AUC}(s) = 3/4 = 0.75$. Un score aléatoire donne $\operatorname{AUC} = 0.5$ (diagonale $\beta=\alpha$) ; un ordonnancement parfait donne $\operatorname{AUC} = 1$.

**4 样本手算示例：** 设 2 个正例得分为 $\{0.9, 0.4\}$，2 个负例得分为 $\{0.6, 0.2\}$。共有 $2\times 2 = 4$ 个正负样本对 $(X_+, X_-)$：
- 正例 $0.9$：高于负例 $0.6$ 和 $0.2$（胜 $2$ 对）；
- 正例 $0.4$：低于负例 $0.6$，但高于负例 $0.2$（胜 $1$ 对）。
4 对中有 3 对排序正确，故 $\operatorname{AUC}(s) = 3/4 = 0.75$。纯随机打分对应对角线 $\beta=\alpha$，其 $\operatorname{AUC}=0.5$；所有正例得分均高于负例时 $\operatorname{AUC}=1$。

**AUC globale vs Partial AUC vs Local AUC (§20–23) : pourquoi regarder le début de la courbe ?**

**全局 AUC、部分 AUC 与局部 AUC（§20–23）：为什么要特别关注曲线左端？**

L'AUC globale intègre $\alpha$ sur tout $[0,1]$, accordant le même poids aux seuils très bas ($\alpha \approx 0.9$, où l'on déclenche presque toujours l'alarme) qu'aux seuils très sélectifs ($\alpha \le \alpha_0 \ll 1$, soit le haut de la liste triée). Or, deux courbes ROC $s_1$ et $s_2$ peuvent se croiser (figure de la section 20) : $s_1$ peut être bien meilleure sur $[0, \alpha_0]$ mais avoir la même AUC globale que $s_2$. La **Partial AUC** $\int_0^{\alpha_0} \operatorname{ROC}(s,\alpha)\,d\alpha$ (Dodd & Pepe, 2003) et la **Local AUC** (Clémençon & Vayatis, 2007) concentrent l'évaluation sur la zone de faible taux de faux positifs $\alpha \in [0, \alpha_0]$ correspondant aux individus placés tout en tête de liste. Attention toutefois (section 22) : maximiser naïvement l'aire partielle sur $[0,\alpha_0]$ sans contrainte de monotonie du rapport de vraisemblance peut être *inconsistant* si la sous-famille de modèles est mal paramétrée, d'où les méthodes dédiées de *local ranking* étudiées par Clémençon et Vayatis.

全局 AUC 在整个 $\alpha \in [0,1]$ 上积分，把高误报区（如 $\alpha \approx 0.9$）与低误报区（$\alpha \le \alpha_0 \ll 1$，对应排序列表最顶端）一视同仁。然而两条 ROC 曲线可能相交（如第 20 节图示）：规则 $s_1$ 在列表前端 $[0,\alpha_0]$ 明显占优，全局面积却可能与 $s_2$ 相同。**部分 AUC（Partial AUC）** $\int_0^{\alpha_0} \operatorname{ROC}(s,\alpha)\,d\alpha$（Dodd & Pepe, 2003）与**局部 AUC（Local AUC）**（Clémençon & Vayatis, 2007）专门聚焦于低误报区间 $[0,\alpha_0]$（即最值得优先采取行动的前端样本）。但如第 22 节图所示，在受限函数类中直接极大化未校准的部分 AUC 可能出现统计不一致性，因此需要 Clémençon 与 Vayatis（2007）针对局部排序设计的专门优化准则。

<a id="section-24"></a>

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

![image](<Images/03_LMC/image_019.jpg>)

Scénario 1

场景 1

![image](<Images/03_LMC/image_020.jpg>)

Scénario 2

场景 2

- Forme des fonctions de décision :

  决策函数的形式：

$$
f (x) = b + <   \beta , x >
$$

où $b\in \mathbb{R},\beta \in \mathbb{R}^d$

其中 $b\in \mathbb{R},\beta \in \mathbb{R}^d$。

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

où $x_{0} \in H$

其中 $x_{0} \in H$。

![image](<Images/03_LMC/image_021.jpg>)

A separating hyperplane $(\boldsymbol{w}, b) \in \mathbb{R}^{n} \times \mathbb{R}$ for a 2D training set.

二维训练集的分隔超平面 $(\boldsymbol{w}, b) \in \mathbb{R}^{n} \times \mathbb{R}$。

Attention! ici $w = \beta$ ...

注意！这里 $w = \beta$……

<a id="section-25"></a>

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

<a id="section-26"></a>

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

<a id="section-27"></a>

**Théorème de Novikoff**

## Novikoff 定理

Si les populations sont linéairement séparables alors l'algorithme du perceptron converge en un nombre fini $T \leq n$ d'étapes où :

如果两个群体线性可分，则感知机算法在有限的 $T \leq n$ 步内收敛，其中：

$$
T \leq \frac {2 R ^ {2}}{M ^ {2}}
$$

avec $M = \min_{1 \leq i \leq n} \{y_i d(x_i, H^*)\}$ pour un certain séparateur $H^*$ .

这里，对某个分隔面 $H^*$，有 $M = \min_{1 \leq i \leq n} \{y_i d(x_i, H^*)\}$。

> **译注：** 原课件写出的 $T\le n$ 不普遍成立。标准感知机界按错误更新次数计数，使用同一增广空间中的样本半径和分隔间隔；不能直接把原空间的几何距离与增广间隔混用。

- Défaut du perceptron : mauvaise généralisation

  感知机的缺点：泛化能力差。
- Vertu du perceptron : algorithme séquentiel (online)

  感知机的优点：序贯（在线）算法。

<a id="reading-perceptron-novikoff"></a>

**Complément — géométrie de la distance signée, mise à jour du Perceptron et preuve complète du théorème de Novikoff (1962)**

**补充——有符号距离的几何推导、感知机更新机制与 Novikoff 定理（1962）的完整证明**

1. **Pourquoi $d(x,H) = \frac{b + \langle\beta,x\rangle}{\|\beta\|}$ est la distance signée à l'hyperplan $H$ (§24) 为什么 $d(x,H) = \frac{b + \langle\beta,x\rangle}{\|\beta\|}$ 是点到超平面的有符号距离**
   Soit $H = \{z \in \mathbb{R}^d : b + \langle\beta, z\rangle = 0\}$ avec $\beta \neq 0$. Pour tout couple de points $z_1, z_2 \in H$, on a $\langle\beta, z_1 - z_2\rangle = (-b) - (-b) = 0$ : le vecteur $\beta$ est donc orthogonal à la direction de l'hyperplan, et $\beta^* = \frac{\beta}{\|\beta\|}$ est son vecteur normal unitaire pointant vers le demi-espace $\{f(x) > 0\}$.
   Pour un point quelconque $x \in \mathbb{R}^d$, sa projection orthogonale sur $H$ s'obtient en projetant le vecteur $x - x_0$ (où $x_0 \in H$ vérifie $\langle\beta, x_0\rangle = -b$) sur la normale unitaire $\beta^*$ :

   设超平面 $H = \{z \in \mathbb{R}^d : b + \langle\beta, z\rangle = 0\}$（$\beta \neq 0$）。对超平面上任意两点 $z_1, z_2 \in H$，有 $\langle\beta, z_1 - z_2\rangle = (-b) - (-b) = 0$，说明 $\beta$ 垂直于超平面，单位法向量 $\beta^* = \frac{\beta}{\|\beta\|}$ 指向正半空间 $\{f(x) > 0\}$。
   对空间中任一点 $x \in \mathbb{R}^d$，任取超平面上一点 $x_0 \in H$（满足 $\langle\beta, x_0\rangle = -b$），将位移向量 $x - x_0$ 向单位法向量 $\beta^*$ 投影，即得 $x$ 到 $H$ 的**有符号距离（signed distance）**：

$$
d(x, H) = \langle\beta^*, x - x_0\rangle = \frac{1}{\|\beta\|}\big(\langle\beta, x\rangle - \langle\beta, x_0\rangle\big) = \frac{b + \langle\beta, x\rangle}{\|\beta\|}.
$$

   La distance géométrique (toujours $\ge 0$) entre $x$ et $H$ est $|d(x,H)|$. Le point $x_i$ d'étiquette $y_i \in \{-1, +1\}$ est correctement classé (et situé hors de $H$) si et seulement si $y_i$ et $d(x_i,H)$ ont le même signe, c'est-à-dire si la **marge géométrique** $y_i d(x_i, H) = \frac{y_i(b + \langle\beta, x_i\rangle)}{\|\beta\|} > 0$.

   点 $x$ 到超平面 $H$ 的欧氏几何距离（非负）即为 $|d(x,H)|$。带标签 $y_i \in \{-1, +1\}$ 的样本 $x_i$ 被严格正确分类，当且仅当 $y_i$ 与有符号距离 $d(x_i,H)$ 同号，即该点的**几何间隔（geometric margin）** $y_i d(x_i, H) = \frac{y_i(b + \langle\beta, x_i\rangle)}{\|\beta\|} > 0$。

2. **Intuition géométrique de la mise à jour du Perceptron (§25–26) 感知机更新规则的几何直觉**
   Dans la version homogène ($b=0$), lorsque l'observation $(x_i, y_i)$ est mal classée ($y_i\langle\beta_{t-1}, x_i\rangle \le 0$), l'algorithme pose $\beta_t = \beta_{t-1} + y_i x_i$. Que devient la marge fonctionnelle sur ce même point après la mise à jour ?

   在齐次感知机（$b=0$）中，一旦样本 $(x_i, y_i)$ 被当前超平面误判（即 $y_i\langle\beta_{t-1}, x_i\rangle \le 0$），算法执行更新 $\beta_t = \beta_{t-1} + y_i x_i$。考察更新后该样本点上的符号内积变化：

$$
y_i \langle\beta_t, x_i\rangle = y_i \langle\beta_{t-1} + y_i x_i, x_i\rangle = y_i \langle\beta_{t-1}, x_i\rangle + \underbrace{y_i^2}_{=1} \|x_i\|^2 = y_i \langle\beta_{t-1}, x_i\rangle + \|x_i\|^2.
$$

   La quantité $y_i\langle\beta, x_i\rangle$ augmente donc strictement de $\|x_i\|^2 > 0$ : l'hyperplan pivote en direction de $y_i x_i$ pour corriger l'erreur. On peut aussi voir cette règle comme une **descente de sous-gradient stochastique** (avec pas $\eta=1$) sur la perte du Perceptron $\ell_{\text{perc}}(\beta; x_i, y_i) = \max\big(0, -y_i\langle\beta, x_i\rangle\big)$, dont le sous-gradient vaut $-y_i x_i$ lorsque $y_i\langle\beta, x_i\rangle \le 0$ et $0$ sinon !

   可以看到，$y_i\langle\beta, x_i\rangle$ 严格增加了 $\|x_i\|^2 > 0$：法向量朝 $y_i x_i$ 方向旋转，把刚被误判的点往正确一侧推。从现代优化视角看，这完全等价于对**感知机损失函数** $\ell_{\text{perc}}(\beta; x_i, y_i) = \max\big(0, -y_i\langle\beta, x_i\rangle\big)$ 做步长为 $\eta=1$ 的**随机次梯度下降（SGD）**：当误判时次梯度为 $-y_i x_i$，正确分类时梯度为 $0$（不更新）！

**Dérivation : preuve complète du théorème de Novikoff (1962) et rôle du rapport $(R/M)^2$**

**推导：Novikoff 定理（1962）的完整证明与半径间隔比 $(R/M)^2$ 的含义**

Démontrons d'abord le théorème dans le cas homogène ($b=0$), puis expliquons la réduction du cas général ($b\neq 0$). Supposons que les données soient linéairement séparables par un hyperplan passant par l'origine de vecteur normal unitaire $u^* \in \mathbb{R}^d$ ($\|u^*\| = 1$) avec une marge géométrique $M > 0$ :

先证明过原点超平面（$b=0$）的标准情形，再说明带截距（$b\neq 0$）的一般情形如何归结为此。假设数据可被单位法向量为 $u^* \in \mathbb{R}^d$（$\|u^*\| = 1$）的超平面以几何间隔 $M > 0$ 线性分开，且所有样本包含在半径为 $R$ 的球内：

$$
\forall i \in \{1,\dots,n\}, \qquad y_i \langle u^*, x_i\rangle \ge M > 0 \quad \text{et} \quad \|x_i\| \le R.
$$

Notons $\beta_0 = 0$, et numérotons uniquement les étapes $t = 1, 2, \dots, T$ où **une erreur est commise** sur un exemple $(x_{i_t}, y_{i_t})$, c'est-à-dire où $y_{i_t}\langle\beta_{t-1}, x_{i_t}\rangle \le 0$ et $\beta_t = \beta_{t-1} + y_{i_t} x_{i_t}$. L'idée de Novikoff consiste à encadrer $\|\beta_T\|$ de deux façons :

设初值 $\beta_0 = 0$，并仅对**发生误判并触发更新**的步数编号为 $t = 1, 2, \dots, T$（对应误判样本 $(x_{i_t}, y_{i_t})$，满足 $y_{i_t}\langle\beta_{t-1}, x_{i_t}\rangle \le 0$ 及 $\beta_t = \beta_{t-1} + y_{i_t} x_{i_t}$）。Novikoff 证明的核心思想是从上下两个方向夹逼第 $T$ 次错误更新后的范数 $\|\beta_T\|$：

1. **Borne inférieure (croissance linéaire du produit scalaire avec $u^*$) 下界（与真实法向量 $u^*$ 的内积线性增长） :**
   À chaque erreur $t$, le produit scalaire avec $u^*$ augmente d'au moins $M$ :

   每次错误更新时，$\beta_t$ 与理想法向量 $u^*$ 的内积至少增加 $M$：

$$
\langle\beta_t, u^*\rangle = \langle\beta_{t-1}, u^*\rangle + y_{i_t}\langle u^*, x_{i_t}\rangle \ge \langle\beta_{t-1}, u^*\rangle + M.
$$

   Par récurrence à partir de $\beta_0 = 0$, après $T$ erreurs, $\langle\beta_T, u^*\rangle \ge T M$. Par l'inégalité de Cauchy–Schwarz et $\|u^*\| = 1$ :

   由 $\beta_0 = 0$ 递推 $T$ 次，并利用 Cauchy–Schwarz 不等式及 $\|u^*\| = 1$，得到 $\|\beta_T\|$ 的线性下界：

$$
T M \le \langle\beta_T, u^*\rangle \le \|\beta_T\|\,\|u^*\| = \|\beta_T\|.
$$

2. **Borne supérieure (croissance sous-linéaire de la norme $\|\beta_T\|$) 上界（范数平方 $\|\beta_T\|^2$ 至多线性增长） :**
   Développons la norme au carré lors de la $t$-ième erreur, en utilisant le fait que $y_{i_t}\langle\beta_{t-1}, x_{i_t}\rangle \le 0$ (puisque l'exemple a été mal classé) et $\|x_{i_t}\|^2 \le R^2$ :

   展开第 $t$ 次错误更新后的范数平方，利用触发更新的条件 $y_{i_t}\langle\beta_{t-1}, x_{i_t}\rangle \le 0$ 以及 $\|x_{i_t}\|^2 \le R^2$：

$$
\|\beta_t\|^2 = \|\beta_{t-1} + y_{i_t} x_{i_t}\|^2 = \|\beta_{t-1}\|^2 + \underbrace{2 y_{i_t}\langle\beta_{t-1}, x_{i_t}\rangle}_{\le 0} + y_{i_t}^2 \|x_{i_t}\|^2 \le \|\beta_{t-1}\|^2 + R^2.
$$

   Par récurrence à partir de $\|\beta_0\|^2 = 0$, on obtient $\|\beta_T\|^2 \le T R^2$, soit $\|\beta_T\| \le \sqrt{T}\, R$.

   由 $\|\beta_0\|^2 = 0$ 累加 $T$ 次，得 $\|\beta_T\|^2 \le T R^2$，即 $\|\beta_T\| \le \sqrt{T}\, R$。

3. **Conclusion 联立上下界得出结论 :** En combinant les deux inégalités :
   将上下界联立：

$$
T M \le \|\beta_T\| \le \sqrt{T}\, R \implies T^2 M^2 \le T R^2 \implies T \le \frac{R^2}{M^2}.
$$

Dans le cas général avec ordonnée à l'origine $b$ (§26), on plonge les données dans $\mathbb{R}^{d+1}$ en posant $\tilde{x}_i = (x_i, R)^T$ et $\tilde{\beta} = (\beta, b/R)^T$, de sorte que $\|\tilde{x}_i\|^2 = \|x_i\|^2 + R^2 \le 2R^2$ : le rayon au carré dans l'espace augmenté devient $2R^2$, d'où le facteur $2R^2/M^2$ affiché à la section 27 (où $M$ désigne alors la marge dans l'espace augmenté).

在带截距 $b$ 的一般情形（§26）下，将样本增广到 $\mathbb{R}^{d+1}$：令 $\tilde{x}_i = (x_i, R)^T$、$\tilde{\beta} = (\beta, b/R)^T$，则增广向量的模长平方满足 $\|\tilde{x}_i\|^2 = \|x_i\|^2 + R^2 \le 2R^2$。将上式中的半径平方替换为增广空间的 $2R^2$，就得到第 27 节课件中的上界 $T \le \frac{2R^2}{M^2}$（其中 $M$ 对应增广空间中的间隔）。

**Remarques cruciales sur cette borne 关于该定理的三个关键说明 :**
- La borne ne dépend **pas** de la dimension $d$ de l'espace ni de la taille $n$ de l'échantillon, mais uniquement du rapport géométrique $(R/M)^2$. Si la marge $M$ est très petite (classes presque accolées), le nombre d'erreurs $T$ avant convergence peut dépasser largement $n$ (il faut alors parcourir la base d'apprentissage sur plusieurs époques).
- Si les données **ne sont pas linéairement séparables**, l'algorithme du Perceptron ne converge jamais et oscille indéfiniment.
- Même dans le cas séparable, le Perceptron s'arrête dès qu'il trouve *un* hyperplan séparateur : cet hyperplan dépend de l'ordre de présentation des exemples et passe souvent très près de certains points d'apprentissage, ce qui explique sa **mauvaise généralisation** (§27) et motive la recherche de l'hyperplan à marge maximale (SVM) à la section 28 !

- 该上界**不显式依赖空间维度 $d$ 或样本总数 $n$**，而只取决于几何比值 $(R/M)^2$。当间隔 $M$ 很小时（两类点云靠得很近），收敛前的错误更新次数 $T$ 完全可能大于 $n$（需要对训练集循环扫描多轮 epoch）。
- 如果训练集**不是线性可分的**，感知机算法不会收敛，而会无限循环震荡。
- 即使数据线性可分，感知机只要找到**任意一个**能分开训练集的超平面就会立刻停止：最终停在哪个超平面取决于样本输入的先后顺序，且分界面往往紧贴某些训练点，导致**泛化能力不佳**（§27）——这直接引出了第 28 节寻找**最大间隔超平面（SVM）**的核心动机！

<a id="maximum-margin"></a>

<a id="section-28"></a>

Scénario 1 - hyperplan à bonne généralisation

## 场景 1：具有良好泛化能力的超平面

Question : hyperplan se trouvant à distance maximale de chaque population ?

问题：是否存在与每个群体的距离都尽可能大的超平面？

![image](<Images/03_LMC/image_022.jpg>)

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

![image](<Images/03_LMC/image_023.jpg>)

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

<a id="section-29"></a>

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

> **译注：** 由等式确定截距时应选取满足 $0<\widehat\alpha_j<C$ 的自由支持向量；任取非零系数的支持向量不一定满足边界等式。

<a id="section-30"></a>

**Canonical Optimal Hyperplane**

## 规范最优超平面

![image](<Images/03_LMC/image_024.jpg>)

⇒ Représentation parcimonieuse ("sparse") des SVM

⇒ SVM 的稀疏表示。

- Classification non supervisée (sans labels)

  无监督分类（没有标签）。
- Autres algorithmes de classification, non-paramétriques, non-linéaires

  其他分类算法：非参数、非线性。
- Calibration de la complexité et régularisation de problèmes d'optimisation

  复杂度调整与优化问题的正则化。

<a id="reading-svm-duality-kkt"></a>

**Complément — normalisation canonique de la marge, dualité lagrangienne des SVM et interprétation KKT des vecteurs de support**

**补充——规范超平面缩放、SVM 拉格朗日对偶推导与 KKT 支持向量分类机制**

Les sections 28 à 30 constituent le cœur géométrique et algorithmique des **Machines à Vecteurs de Support (SVM)** linéaires.

第 28 至 30 节构成了线性**支持向量机（SVM）**的几何与凸优化核心。

1. **Pourquoi peut-on poser $M = 1/\|\beta\|$ ? (Normalisation canonique, §28) 为什么可以令几何间隔 $M = 1/\|\beta\|$？（规范超平面归一化，§28）**
   Pour tout facteur strictement positif $\kappa > 0$, multiplier $(\beta, b)$ par $\kappa$ ne change ni l'hyperplan $H = \{x : b + \langle\beta, x\rangle = 0\}$, ni le signe de $f(x)$, ni la distance géométrique $d(x_i, H) = \frac{b + \langle\beta, x_i\rangle}{\|\beta\|}$. Parmi tous les multiples $(\kappa\beta, \kappa b)$ qui représentent le même hyperplan séparateur, on peut fixer l'échelle $\kappa$ de manière unique en imposant que le point d'apprentissage le plus proche de $H$ vérifie :

   对任意正数 $\kappa > 0$，将参数 $(\beta, b)$ 同乘 $\kappa$ 不会改变超平面 $H = \{x : b + \langle\beta, x\rangle = 0\}$ 的几何位置，也不会改变点到超平面的几何距离 $d(x_i, H) = \frac{b + \langle\beta, x_i\rangle}{\|\beta\|}$。为了消除这一尺度冗余，我们可以在代表同一超平面的所有 $(\kappa\beta, \kappa b)$ 中唯一固定尺度 $\kappa$，规定离超平面最近的训练样本满足函数间隔等于 $1$（即**规范超平面，canonical hyperplane**）：

$$
\min_{1 \le i \le n} y_i (b + \langle\beta, x_i\rangle) = 1.
$$

   Sous cette normalisation canonique, la contrainte $\forall i,\; y_i(b + \langle\beta, x_i\rangle) \ge 1$ est satisfaite et la distance géométrique minimale de l'échantillon à l'hyperplan vaut exactement :

   在此规范化约定下，所有样本满足约束 $y_i(b + \langle\beta, x_i\rangle) \ge 1$，且训练集到超平面的最小几何距离（即**几何间隔 $M$**）恰好等于：

$$
M = \min_{1 \le i \le n} \frac{y_i (b + \langle\beta, x_i\rangle)}{\|\beta\|} = \frac{1}{\|\beta\|}.
$$

   La largeur totale de la bande vide séparant les deux classes (entre les hyperplans de marge $b+\langle\beta,x\rangle = +1$ et $b+\langle\beta,x\rangle = -1$) vaut $2M = \frac{2}{\|\beta\|}$. Maximiser $M = 1/\|\beta\|$ revient donc à minimiser $\|\beta\|$, ou de manière équivalente la fonction **strictement convexe et quadratique différentiable** $\frac{1}{2}\|\beta\|^2$ sous contraintes affines !

   两类间隔边界超平面 $b+\langle\beta,x\rangle = +1$ 与 $b+\langle\beta,x\rangle = -1$ 之间的缓冲带总宽度为 $2M = \frac{2}{\|\beta\|}$。因此，最大化几何间隔 $M = 1/\|\beta\|$ 完全等价于最小化 $\|\beta\|$，进而转化为在线性不等式约束下最小化**光滑严格凸二次函数** $\frac{1}{2}\|\beta\|^2$ 的凸二次规划（QP）问题！

2. **Variables ressorts $\xi_i$ et paramètre de compromis $C$ (Marge souple / Soft-margin SVM) 松弛变量 $\xi_i$ 与权衡参数 $C$（软间隔 SVM）**
   Lorsque les classes se chevauchent (Scénario 2), le problème à marge dure ($y_i f(x_i) \ge 1$) n'a pas de solution réalisable. Chaque variable ressort $\xi_i \ge 0$ mesure de combien le point $x_i$ enfreint sa frontière de marge :
   - $\xi_i = 0$ : $x_i$ respecte la marge ($y_i f(x_i) \ge 1$).
   - $0 < \xi_i < 1$ : $x_i$ est **dans la bande de marge** mais reste du bon côté de l'hyperplan séparateur ($0 < y_i f(x_i) < 1$, donc bien classé !).
   - $\xi_i = 1$ : $x_i$ est exactement sur l'hyperplan séparateur ($f(x_i) = 0$).
   - $\xi_i > 1$ : $x_i$ est du mauvais côté de l'hyperplan ($y_i f(x_i) < 0$, **mal classé**).
   Ainsi, $\sum_{i=1}^n \xi_i$ borne supérieurement le nombre d'erreurs d'apprentissage $\sum_{i=1}^n \mathbb{I}_{[y_i f(x_i) \le 0]}$. Le paramètre $C > 0$ règle le compromis : un **grand $C$** pénalise fortement les $\xi_i$ (bande étroite, risque de surapprentissage ; lorsque l'échantillon est linéairement séparable de sorte que le problème à marge dure est réalisable, la limite $C\to+\infty$ redonne la marge dure, tandis que si les données ne sont pas séparables, aucun hyperplan à marge dure n'existe quel que soit $C$), alors qu'un **petit $C$** accepte davantage d'intrusions dans la marge pour obtenir une bande plus large et plus stable.

   当两类样本存在重叠或噪声（场景 2）时，硬间隔约束 $y_i f(x_i) \ge 1$ 无可行解。引入非负松弛变量 $\xi_i \ge 0$ 度量样本 $x_i$ 违背间隔边界的程度：
   - $\xi_i = 0$：$x_i$ 位于间隔边界上或间隔外侧安全区（$y_i f(x_i) \ge 1$）；
   - $0 < \xi_i < 1$：$x_i$ **侵入了间隔带内部**，但仍在分隔超平面正确一侧（$0 < y_i f(x_i) < 1$，分类依然正确！）；
   - $\xi_i = 1$：$x_i$ 恰好落在分隔超平面 $H$ 上（$f(x_i) = 0$）；
   - $\xi_i > 1$：$x_i$ 越过了分隔超平面（$y_i f(x_i) < 0$，**发生误分类**）。
   因此，$\sum_{i=1}^n \xi_i$ 是训练集误判个数 $\sum_{i=1}^n \mathbb{I}_{[y_i f(x_i) \le 0]}$ 的凸上界。超参数 $C > 0$ 控制间隔宽度与违约代价的权衡：**$C$ 很大**时严惩违约（间隔带变窄，容错率低；当训练样本本身线性可分、硬间隔问题可行时，令 $C\to+\infty$ 才退化为硬间隔 SVM，若数据不可分则无论 $C$ 多大都无法满足硬间隔约束）；**$C$ 较小**时允许少量点进入间隔带，换取更宽、更稳健的整体间隔。

**Dérivation : passage du problème primal au problème dual et conditions KKT (§28–29)**

**推导：从原问题到拉格朗日对偶问题及 KKT 条件（§28–29）**

En introduisant les multiplicateurs de Lagrange $\alpha_i \ge 0$ pour les contraintes $y_i(b + \langle\beta,x_i\rangle) - (1-\xi_i) \ge 0$ et $\mu_i \ge 0$ pour les contraintes $\xi_i \ge 0$, le lagrangien standard s'écrit (notons le signe $-$ devant $\sum \mu_i\xi_i$ dans la convention standard où $\mu_i \ge 0$ ; dans le support §28–29, la première page écrit $+\sum\mu_i\xi_i$ puis la page KKT écrit la relation standard $\alpha_i + \mu_i = C$ avec $\mu_i \ge 0$) :

为不等式约束 $1 - \xi_i - y_i(b + \langle\beta,x_i\rangle) \le 0$ 引入拉格朗日乘子 $\alpha_i \ge 0$，为 $\xi_i \ge 0$（即 $-\xi_i \le 0$）引入拉格朗日乘子 $\mu_i \ge 0$，标准拉格朗日函数写作（注：课件第 1434 行与第 1450 行在 $\mu_i$ 的正负号上与第 1484 行 KKT 页相差一个负号，按第 1484 行标准约定 $\mu_i \ge 0$ 推导最为清晰）：

$$
\mathcal{L}(\beta, b, \xi, \alpha, \mu)
= \frac{1}{2}\|\beta\|^2 + C\sum_{i=1}^n \xi_i - \sum_{i=1}^n \alpha_i \Big[y_i(b + \langle\beta, x_i\rangle) - (1 - \xi_i)\Big] - \sum_{i=1}^n \mu_i \xi_i.
$$

Pour obtenir la fonction duale $g(\alpha, \mu) = \inf_{\beta, b, \xi} \mathcal{L}(\beta, b, \xi, \alpha, \mu)$, annulons les dérivées partielles par rapport aux variables primales $(\beta, b, \xi_i)$ :

为求对偶函数 $g(\alpha, \mu) = \inf_{\beta, b, \xi} \mathcal{L}(\beta, b, \xi, \alpha, \mu)$，令 $\mathcal{L}$ 关于原变量 $(\beta, b, \xi_i)$ 的偏导数为零：

$$
\begin{aligned}
\nabla_\beta \mathcal{L} = 0 &\implies \beta = \sum_{i=1}^n \alpha_i y_i x_i, \\
\frac{\partial \mathcal{L}}{\partial b} = 0 &\implies \sum_{i=1}^n \alpha_i y_i = 0, \\
\frac{\partial \mathcal{L}}{\partial \xi_i} = 0 &\implies C - \alpha_i - \mu_i = 0 \iff \alpha_i + \mu_i = C.
\end{aligned}
$$

Comme $\alpha_i \ge 0$ et $\mu_i = C - \alpha_i \ge 0$, la troisième condition équivaut à la **contrainte de boîte** $0 \le \alpha_i \le C$. En reportant ces trois relations dans $\mathcal{L}$, les termes en $b$ et en $\xi_i$ disparaissent complètement :

由于 $\alpha_i \ge 0$ 且 $\mu_i = C - \alpha_i \ge 0$，第三式等价于**盒式约束（box constraint）** $0 \le \alpha_i \le C$。将上述三式代回 $\mathcal{L}$，含 $b$ 和 $\xi_i$ 的项全部抵消：

$$
\begin{aligned}
\mathcal{L}
&= \frac{1}{2}\sum_{i=1}^n\sum_{j=1}^n \alpha_i\alpha_j y_i y_j \langle x_i, x_j\rangle - \sum_{i=1}^n\sum_{j=1}^n \alpha_i\alpha_j y_i y_j \langle x_i, x_j\rangle + \sum_{i=1}^n \alpha_i \\
&= \sum_{i=1}^n \alpha_i - \frac{1}{2}\sum_{i=1}^n\sum_{j=1}^n \alpha_i\alpha_j y_i y_j \langle x_i, x_j\rangle,
\end{aligned}
$$

ce qui donne exactement le programme quadratique dual de la section 28 ! Par le théorème de Slater (problème primal convexe à contraintes affines), le saut de dualité est nul et les conditions KKT (§29), notamment les deux relations d'**écart complémentaire** (*complementary slackness*) :

这正是第 28 节给出的对偶二次规划问题！由凸优化的 Slater 条件（目标凸二次、约束全为仿射不等式），强对偶性成立，且最优解充要地满足 §29 的 KKT 条件，特别是两条**互补松弛条件（complementary slackness）**：

$$
\alpha_i \big[y_i f(x_i) - (1 - \xi_i)\big] = 0 \qquad \text{et} \qquad \mu_i \xi_i = (C - \alpha_i)\xi_i = 0,
$$

déterminent entièrement la géométrie des points par rapport à la marge :

这两条互补松弛条件将所有训练样本按 $\hat{\alpha}_i$ 的取值精确划分为三类几何位置：

| Valeur du multiplicateur $\hat{\alpha}_i$ / 对偶乘子 $\hat{\alpha}_i$ 的取值 | Conséquence par KKT ($\hat{\mu}_i = C - \hat{\alpha}_i$) / 由 KKT 推出的松弛变量与函数间隔 | Position géométrique de $x_i$ / 样本点 $x_i$ 的几何位置与角色 |
|---|---|---|
| **$\hat{\alpha}_i = 0$** / （非支持向量） | $\hat{\mu}_i = C > 0 \implies \hat{\xi}_i = 0$ et $y_i\hat{f}(x_i) \ge 1$ | **Hors de la bande de marge (ou au bord)** : retirer ce point de l'échantillon ne changerait pas l'optimalité de $\hat{f}$ ! / **位于间隔带外侧安全区（或恰在间隔边界上）**：从训练集中删去该点，不会改变 $\hat{f}$ 的最优性！ |
| **$0 < \hat{\alpha}_i < C$** / （自由支持向量） | $\hat{\mu}_i > 0 \implies \hat{\xi}_i = 0$, et $\hat{\alpha}_i > 0 \implies y_i\hat{f}(x_i) = 1 - \hat{\xi}_i = 1$ | **Vecteur de support libre** : repose exactement sur l'hyperplan de marge $b+\langle\hat{\beta},x\rangle = \pm 1$. Sert à calculer l'ordonnée à l'origine $\hat{b} = y_j - \langle\hat{\beta}, x_j\rangle$. / **自由支持向量**：精确落在间隔边界 $b+\langle\hat{\beta},x\rangle = \pm 1$ 上，可直接代入等式反解截距 $\hat{b} = y_j - \langle\hat{\beta}, x_j\rangle$。 |
| **$\hat{\alpha}_i = C$** / （有界支持向量） | $\hat{\mu}_i = 0 \implies \hat{\xi}_i \ge 0$ et $y_i\hat{f}(x_i) = 1 - \hat{\xi}_i \le 1$ | **Vecteur de support borné** : a pénétré dans la bande de marge ($\hat{\xi}_i \in (0,1)$, bien classé), touche la frontière ($\hat{\xi}_i=0$), ou est mal classé ($\hat{\xi}_i > 1$). / **有界支持向量**：侵入间隔带内部（$0<\hat{\xi}_i<1$，仍分类正确）、恰在边界上（$\hat{\xi}_i=0$），或越界误判（$\hat{\xi}_i > 1$）。 |

Enfin, remarquons la **dualité de la parcimonie** entre le cours 2 et le cours 3 : le LASSO ($\ell_1$ sur $\beta$) produit une solution **parcimonieuse dans les variables** (seules quelques coordonnées $\hat{\beta}_j$ sont non nulles), tandis que le SVM produit une solution **parcimonieuse dans les observations** ($\hat{\beta} = \sum_{i\in I} \hat{\alpha}_i y_i x_i$ ne dépend que des vecteurs de support $i \in I$, car la perte *hinge* $\max(0, 1 - y_i f(x_i))$ a une pente strictement nulle sur toute la demi-droite $y_i f(x_i) > 1$).

最后，可以对比第二课与第三课中**两种不同维度的“稀疏性”**：第二课的 LASSO（对参数施加 $\ell_1$ 惩罚）产生的是**特征维度的稀疏性**（只有少数特征系数 $\hat{\beta}_j \neq 0$）；而本讲的 SVM 产生的是**样本维度的稀疏性**（由于合页损失 $\max(0, 1-y_i f(x_i))$ 在 $y_i f(x_i) > 1$ 整个安全区内恒为零、导数为零，所有安全区内的样本乘子 $\hat{\alpha}_i = 0$，法向量 $\hat{\beta} = \sum_{i\in I} \hat{\alpha}_i y_i x_i$ 仅由少数支持向量 $i\in I$ 线性张成）。
