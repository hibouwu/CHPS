> 双语阅读版：保留原文语言，每个小题单独换行，原文与中文在同一行用空格连接；题目说明与小题之间留空行，公式、数值和图片共用。原文按转换稿整理，修正明显的重音、断词与标点错误；题意以原 PDF 为准。已有中文审查注单独保留，属于补充说明。
> 参考答案：法语在前、中文紧随，置于各小题下一行；依据链接指向本地课件或练习。这是按材料推导的复习答案，并非教师官方答案。计算题注明数值约定，开放题给出一种可行方案；题面缺失条件保留参数，读图近似与精确计算分别标明。

[原 PDF](DataML-CHPS-2023-examen.pdf) · [原文转换稿](DataML-CHPS-2023-examen.md) · [试卷目录](README.md)

# Data & Apprentissage 数据与学习

13 novembre 2023 2023 年 11 月 13 日 Examen final 期末考试 Le sujet est imprimé sur 2 pages – Durée 2 heures 试卷共印为 2 页，时长 2 小时。 Les documents et notes de cours sont autorisés. L’utilisation de smartphones et l’accès à des ressources documentaires sur Internet sont interdits. L’examen est à réaliser individuellement et toute tentative de collaboration entre étudiants sera sévèrement sanctionnée. 允许使用资料和课堂笔记。禁止使用手机或访问互联网上的文档资源。考试须独立完成，学生之间任何试图协作的行为都会受到严厉处罚。

## Exercice 1. Understanding of main concepts of the course [10 points] 第 1 题：课程核心概念理解 [10 分]

Answer the following questions in 5 to 10 lines. 请用 5–10 行回答以下各题。

1\. What is the so-called “bias-variance” trade-off in Machine Learning? 机器学习中所谓的“偏差—方差”权衡是什么？\
**Réponse (FR) :** En régression quadratique, sous $Y=f^*(X)+\varepsilon$ avec $\mathbb{E}[\varepsilon\mid X]=0$ et $\operatorname{Var}(\varepsilon\mid X)=\sigma^2$, l’erreur quadratique moyenne en un point $x$ se décompose en :
$$\mathbb{E}\big[(\hat f_n(x)-Y)^2\big]=\underbrace{\big(\mathbb{E}[\hat f_n(x)]-f^*(x)\big)^2}_{\text{Biais}^2}+\underbrace{\operatorname{Var}(\hat f_n(x))}_{\text{Variance}}+\underbrace{\sigma^2}_{\text{Bruit irréductible}}.$$
Un modèle trop simple (ou trop régularisé) sous-apprend : biais élevé, variance faible. Un modèle trop flexible sur-apprend le bruit de l’échantillon fini : biais faible, mais variance élevée. Le compromis consiste à ajuster la complexité ou la régularisation par validation afin de minimiser la somme $\text{Biais}^2+\text{Variance}$, puis à évaluer le modèle une seule fois sur un jeu de test indépendant. **答案（中文）：** 在平方损失回归中，设 $Y=f^*(X)+\varepsilon$（$\mathbb{E}[\varepsilon\mid X]=0$，$\operatorname{Var}(\varepsilon\mid X)=\sigma^2$），点 $x$ 处的期望预测误差可分解为**偏差平方 + 估计方差 + 不可约噪声**（见上式）。模型过于简单（或正则化过强）会**欠拟合**（高偏差、低方差）；模型过于灵活则会记住有限样本中的噪声而**过拟合**（低偏差、高方差）。实践上通过验证集调节复杂度或正则化强度，使“偏差平方 + 方差”之和最小，并在独立测试集上做一次性评估。 **依据：** [第一课：误差与偏差—方差](../Lectures/01_intro/04_hypotheses_and_bias_variance.md) · [第二课：正则化与验证](../Lectures/02_LM/06_regularization_and_validation.md) · [Lab1](../Exercises/Lab1/Lab1_zh.ipynb)。

2\. Define a theoretical criterion to assess the performance of a scoring algorithm (such as logistic regression for instance). 定义一个用于评价评分算法（例如逻辑回归）性能的理论准则。\
**Réponse (FR) :** Un critère théorique central est l’**AUC (aire sous la courbe ROC)**. Pour un score $s(X)$ et un seuil mobile $t\in\mathbb{R}$, la courbe ROC trace le taux de vrais positifs $\mathrm{TPR}(t)=\mathbb{P}(s(X)\ge t\mid Y=1)$ en fonction du taux de faux positifs $\mathrm{FPR}(t)=\mathbb{P}(s(X)\ge t\mid Y=0)$. Son aire vaut :
$$\mathrm{AUC}=\int_0^1 \mathrm{ROC}(u)\,du = \mathbb{P}\big(s(X^+)>s(X^-)\big)+\frac{1}{2}\mathbb{P}\big(s(X^+)=s(X^-)\big),$$
c’est-à-dire la probabilité qu’un individu positif tiré au hasard reçoive un score supérieur à celui d’un négatif. L’AUC évalue la qualité du **classement** indépendamment d’un seuil particulier ; en présence de classes très déséquilibrées on la complète par l’aire Précision–Rappel (PR-AUC), et si l’on souhaite des probabilités bien calibrées, par la **log-loss**. **答案（中文）：** 经典的理论准则之一是 **ROC 曲线下面积（AUC）**。对任意实值评分函数 $s(X)$，随着阈值 $t$ 变化，ROC 曲线以假阳性率 $\mathrm{FPR}(t)=\mathbb{P}(s(X)\ge t\mid Y=0)$ 为横轴、真正率 $\mathrm{TPR}(t)=\mathbb{P}(s(X)\ge t\mid Y=1)$ 为纵轴刻画检出能力与误报之间的权衡。AUC 等于随机抽取一个正例与一个负例时，正例得分高于负例的概率（平局计 0.5，见上式），可在不固定具体阈值的前提下评价**排序能力**。若类别极度不平衡可补充 **PR-AUC**；若关心预测概率本身的准确度与校准，则需结合 **log-loss**。 **依据：** [第三课：分类与评分](../Lectures/03_LMC_zh.md)。

3\. How to estimate a sparse linear model? 如何估计稀疏线性模型？\
**Réponse (FR) :** On utilise le **Lasso** (*Least Absolute Shrinkage and Selection Operator*), qui pénalise l’erreur quadratique empirique par la norme $\ell_1$ des poids :
$$\min_{w\in\mathbb{R}^d,\, b\in\mathbb{R}}\;\frac{1}{N}\sum_{i=1}^N (y_i - w^T x_i - b)^2 + \lambda\|w\|_1.$$
Contrairement à Ridge ($\ell_2^2$), qui rétrécit tous les coefficients vers zéro sans les annuler, la géométrie non lisse de la boule $\ell_1$ (sommets sur les axes) annule exactement de nombreuses composantes de $w$ lorsque $\lambda$ augmente, réalisant ainsi une **sélection de variables** automatique. En pratique : on ne pénalise pas l’ordonnée à l’origine $b$, on standardise les variables à partir du seul jeu d’entraînement, et on choisit $\lambda$ par validation croisée. **答案（中文）：** 通常使用 **Lasso** 估计稀疏线性模型：在最小化均方误差时加入权重向量的 $\ell_1$ 范数惩罚（见上式）。与仅将系数收缩但很少变为零的岭回归（$\ell_2^2$ 惩罚）不同，$\ell_1$ 惩罚在零点不可微，能够将许多无关特征的系数**精确压缩为零**，从而同时完成拟合与变量选择。实践上需注意：**不惩罚截距 $b$**、仅用训练集统计量对特征做标准化、并通过交叉验证调节正则化强度 $\lambda$（高度共线特征下选中子集可能不稳定）。 **依据：** [第二课：正则化与验证](../Lectures/02_LM/06_regularization_and_validation.md) · [Lab1](../Exercises/Lab1/Lab1_zh.ipynb)。

4\. What are the hyperparameters of decision tree algorithms? 决策树算法有哪些超参数？\
**Réponse (FR) :** Contrairement aux variables de coupure, aux seuils $s$ et aux prédictions dans les feuilles (qui sont **appris** sur les données), les hyperparamètres contrôlent la complexité de l’arbre avant ou pendant la construction et sont réglés par validation :
- **Critères de structure / arrêt :** profondeur maximale (`max_depth`), nombre maximal de feuilles (`max_leaf_nodes`), nombre minimal d’échantillons requis pour diviser un nœud (`min_samples_split`) ou dans une feuille (`min_samples_leaf`), diminution minimale d’impureté pour autoriser une coupure.
- **Critère de séparation et élagage :** fonction d’impureté (indice de **Gini** ou **entropie** en classification ; **MSE/MAE** en régression) et paramètre d’élagage coût-complexité ($\alpha$). **答案（中文）：** 与从数据中“学得”的分裂特征、分裂阈值和叶节点预测值不同，决策树的超参数在训练前由人工设定、并通过验证集调节，主要包括：
- **树规模与早停控制**：最大深度（`max_depth`）、最大叶节点数（`max_leaf_nodes`）、分裂所需最少样本数（`min_samples_split`）、叶节点最少样本数（`min_samples_leaf`）、允许分裂的最小不纯度下降量；
- **分裂准则与剪枝**：不纯度/损失度量（分类常用 **Gini 指数**或**交叉熵**，回归常用 **MSE**）以及代价复杂度后剪枝强度参数 $\alpha$。 **依据：** [第五课：SVM、树与集成](../Lectures/05_NLM_zh.md) · [Lab2](../Exercises/Lab2/Lab2_zh.ipynb)。

5\. What are the two main ingredients of ensemble methods? 集成方法的两个主要组成要素是什么？\
**Réponse (FR) :** Une méthode d’ensemble repose sur deux ingrédients essentiels :
1. **Générer des prédicteurs de base diversifiés** (des modèles dont les erreurs ne sont pas toutes identiques) : par rééchantillonnage *bootstrap* (Bagging), en ajoutant un sous-échantillonnage aléatoire de variables à chaque nœud pour décorréler les arbres (Forêts aléatoires), ou par apprentissage séquentiel ciblant les erreurs résiduelles des modèles précédents (Boosting).
2. **Agréger leurs prédictions** pour obtenir un prédicteur final plus précis et plus stable : par moyenne en régression ou vote majoritaire/pondéré en classification (Bagging/Forêts aléatoires réduisent surtout la variance ; Boosting réduit surtout le biais). **答案（中文）：** 集成方法的核心在于以下两个要素：
1. **构造具有差异性（多样性）的基础学习器**：若所有基模型犯完全相同的错误，集成就无法带来提升。因此需要通过有放回重采样（Bagging）、每次分裂随机筛选特征子集来降低树间相关性（随机森林），或按序针对前序模型残差/错分样本迭代拟合（Boosting）来引入差异；
2. **组合（聚合）各个基模型的输出**：回归任务通常取均值或加权和，分类任务通常采用多数投票或加权投票（Bagging 与随机森林主要降低方差，Boosting 主要降低偏差）。 **依据：** [第五课：SVM、树与集成](../Lectures/05_NLM_zh.md) · [Lab3](../Exercises/Lab3/Lab3_zh.ipynb)。

6\. What is the mathematical space of functions for deep feedforward neural networks and what are the hyperparameters of such algorithms? 深度前馈神经网络对应怎样的数学函数空间？这类算法有哪些超参数？\
**Réponse (FR) :** Pour une architecture fixée à $L$ couches cachées, l’espace des fonctions est une famille paramétrée obtenue par **composition alternée d’applications affines et d’activations non linéaires** agissant composante par composante :
$$\mathcal{H}=\Big\{x\mapsto A_{L+1}\circ\sigma_L\circ A_L\circ\cdots\circ\sigma_1\circ A_1(x) : \theta=\{(W_\ell,b_\ell)\}_{\ell=1}^{L+1}\Big\}, \quad A_\ell(u)=W_\ell u+b_\ell.$$
*(Ce n’est généralement pas un espace vectoriel, car la somme de deux réseaux d’architecture fixée n’appartient pas à $\mathcal{H}$.)* Alors que les matrices de poids $W_\ell$ et vecteurs de biais $b_\ell$ sont **appris**, les **hyperparamètres** comprennent :
- **Architecture et régularisation :** profondeur $L$, largeur de chaque couche, fonctions d’activation $\sigma_\ell$ (ReLU, tanh, etc.), taux de *dropout*, pénalisation $\ell_2$ (*weight decay*).
- **Optimisation :** algorithme (SGD, Adam), taux d’apprentissage et son calendrier, taille de mini-lot et nombre d’époques (*early stopping*). **答案（中文）：** 固定网络结构（$L$ 个隐藏层）时，深度前馈神经网络对应的函数类是由**仿射变换与逐分量非线性激活函数交替复合**而成的参数化函数族（公式见上，通常**不是**线性向量空间）。其中权重矩阵 $W_\ell$ 与偏置向量 $b_\ell$ 由训练学得，而超参数可分为两类：
- **架构与正则化超参数**：网络深度 $L$、各层宽度、激活函数类型 $\sigma_\ell$（如 ReLU、tanh）、权值衰减系数（$\ell_2$ 正则）、Dropout 比例；
- **优化与训练超参数**：优化器选择（SGD、Adam 等）、学习率及调度策略、小批量大小（batch size）和训练轮数（或早停策略）。 **依据：** [第六课：深度学习](../Lectures/06_DL_zh.md)。

7\. What is the role of penalization in machine learning? 惩罚项在机器学习中有什么作用？\
**Réponse (FR) :** La pénalisation (régularisation) consiste à minimiser le risque empirique augmenté d’un terme de complexité $\widehat R_n(\theta)+\lambda\Omega(\theta)$ (avec $\lambda\ge 0$ réglé par validation). Elle joue plusieurs rôles clés : (1) **prévenir le surapprentissage** et améliorer la généralisation en acceptant un léger biais pour réduire fortement la variance ; (2) **stabiliser les problèmes mal posés** ou à variables fortement colinéaires (par ex. la norme $\ell_2^2$ en Ridge rend $(X^TX+\lambda I)$ inversible) ; (3) **imposer une structure souhaitée**, telle que la parcimonie et la sélection de variables via la norme $\ell_1$ (Lasso). Une pénalisation trop forte entraîne au contraire du sous-apprentissage. **答案（中文）：** 惩罚项（正则化）将优化目标从单纯最小化经验风险改为 $\widehat R_n(\theta)+\lambda\Omega(\theta)$（$\lambda\ge 0$ 由验证选定），主要有三大作用：① **控制模型复杂度、防止过拟合**：以轻微增加偏差为代价大幅降低方差，改善测试集泛化性能；② **改善病态问题与数值稳定性**：例如岭回归中的 $\ell_2^2$ 惩罚可解决特征多重共线性、使矩阵求逆良态；③ **注入特定结构先验**：例如 $\ell_1$ 惩罚（Lasso）诱发参数稀疏性以实现变量选择（若 $\lambda$ 过大则会欠拟合）。 **依据：** [第二课：正则化与验证](../Lectures/02_LM/06_regularization_and_validation.md)。

8\. How to achieve numerical optimization in machine learning methods? Give at least one specific example. 如何对机器学习方法进行数值优化？请至少给出一个具体例子。\
**Réponse (FR) :** On écrit d’abord l’objectif (perte empirique + éventuelle pénalisation), puis on choisit un solveur adapté à sa **convexité** et à sa **régularité** :
- Formes fermées / algèbre linéaire : décompositions **QR ou SVD** pour les moindres carrés (OLS/Ridge).
- Objectifs convexes lisses sans forme fermée (ex. régression logistique) : descente de gradient, L-BFGS ou méthode de Newton.
- Pénalités non lisses (ex. Lasso) : descente par coordonnées ou méthodes proximales.
- Objectifs non convexes à grande échelle (réseaux profonds) : **descente de gradient stochastique par mini-lots (mini-batch SGD / Adam)** avec gradients calculés par **rétropropagation**.

**Exemple concret :** pour la régression logistique pénalisée $\ell_2$, la fonction objectif $L(w)$ est convexe et différentiable ; on initialise $w_0$ et on itère $w_{t+1}=w_t-\eta\nabla L(w_t)$ jusqu’à ce que $\|\nabla L(w_t)\|$ soit inférieur à une tolérance (en choisissant convenablement le pas $\eta$). **答案（中文）：** 在写出“经验损失 + 正则项”的优化目标后，根据目标函数的**凸性与光滑性**选用相应数值求解器：① **闭式/矩阵分解法**（如 OLS 与岭回归使用 QR 或 SVD 分解）；② **光滑凸目标的迭代优化**（如逻辑回归采用梯度下降、拟牛顿 L-BFGS 或牛顿法）；③ **非光滑正则项求解**（如 Lasso 采用坐标下降或近端梯度法）；④ **大规模非凸优化**（深度网络采用小批量 SGD 或 Adam 配合反向传播求梯度）。

**具体例子**：在 $\ell_2$ 正则化逻辑回归中，目标函数 $L(w)$ 光滑且严格凸，可从初值 $w_0$ 出发执行梯度下降 $w_{t+1}=w_t-\eta\nabla L(w_t)$，设置合适步长 $\eta$（或线搜索），迭代至梯度范数小于预设收敛阈值为止。 **依据：** [第二课：最小二乘](../Lectures/02_LM/01_linear_models_and_least_squares.md) · [第二课：正则化与验证](../Lectures/02_LM/06_regularization_and_validation.md) · [第六课：深度学习](../Lectures/06_DL_zh.md)。

## Exercice 2. Clustering [3 points] 第 2 题：聚类 [3 分]

a) Give the k-means objective function, the pseudocode of the clustering algorithm, explain with simple arguments: why the procedure converges and why multiple (re)runs are suggested. 给出 k-means 的目标函数及聚类算法伪代码，并用简单论据解释算法为何收敛，以及为什么建议多次重新运行。\
**Réponse (FR) :** L’algorithme de Lloyd cherche à minimiser l’inertie intra-classe :
$$J(z,c)=\sum_{i=1}^N \|x_i - c_{z_i}\|_2^2 = \sum_{j=1}^k \sum_{i\in C_j} \|x_i - c_j\|_2^2.$$

```text
Entrée : données X = {x_1,...,x_N}, nombre de clusters k
Initialiser k centres c_1, ..., c_k
Répéter :
  1. Affectation : pour i = 1..N, z_i <- argmin_{j=1..k} ||x_i - c_j||^2
     (avec règle déterministe en cas d’égalité)
  2. Mise à jour : pour j = 1..k :
       si C_j = {i : z_i = j} est non vide : c_j <- (1/|C_j|) * somme_{i in C_j} x_i
       sinon : réinitialiser le cluster vide c_j
Jusqu’à stabilisation des affectations z (ou diminution négligeable de J)
```

- **Convergence :** à l’étape 1, choisir le centre le plus proche ne peut pas augmenter $J$ ; à l’étape 2, la moyenne arithmétique de $C_j$ minimise exactement la somme des carrés des distances dans $C_j$, donc $J$ ne peut pas augmenter non plus. Comme $J\ge 0$ décroît de manière monotone et que le nombre de partitions possibles est **fini** (au plus $k^N$), l’algorithme termine en un nombre fini d’itérations sur un optimum local (avec une règle d’égalité évitant les cycles).
- **Relances multiples :** $J$ étant **non convexe**, la solution dépend fortement de l’initialisation. On effectue plusieurs exécutions aléatoires (ou **k-means++**) afin de retenir le partitionnement de plus faible inertie. **答案（中文）：** 常规 k-means 的目标函数是最小化簇内平方距离和（惯量）$J(z,c)=\sum_{i=1}^N\|x_i-c_{z_i}\|_2^2$（伪代码见上）：初始化 $k$ 个中心后，交替执行 **① 分配步**（将样本分配给最近的中心）和 **② 更新步**（非空簇的新中心更新为簇内均值；空簇需单独重置），直至分配不再变化。

- **为何收敛**：分配步选最近中心、更新步取簇均值（恰好是最小化组内平方距离和的最优点），两步都不会增大非负目标 $J$。由于 $J\ge 0$ 单调不增，且将 $N$ 个样本分为 $k$ 簇的划分总数**有限**（至多 $k^N$ 种，配合确定性平局规则可防循环），算法必在有限步内停止于某个局部稳定解。
- **为何建议多次重新运行**：目标函数 $J$ **非凸**，存在多个局部极小值，对初始中心非常敏感，因此需要多组随机重启（或使用 **k-means++**）并保留目标值 $J$ 最小的解。 **依据：** [Lab4](../Exercises/Lab4/Lab4_zh.ipynb) · [Lab5](../Exercises/Lab5/Lab5_zh.ipynb)。

b) We are interested about a soft k-means that would use a probabilistic datapoint-to-cluster assignment. Propose a way to define this probabilistic assignment, give an updated pseudocode for this case, and argue whether or not this would converge. 希望构造一种采用数据点到簇的概率分配方式的软 k-means。提出定义这种概率分配的方法，给出更新后的伪代码，并论证它是否收敛。\
**Réponse (FR) :** Une formulation standard consiste à introduire des responsabilités $r_{ij}\in[0,1]$ ($\sum_{j=1}^k r_{ij}=1$) qui décroissent exponentiellement avec la distance au carré (fonction **softmax** de température / paramètre de raideur $\tau>0$) :
$$r_{ij}=\frac{\exp\!\big(-\|x_i-c_j\|_2^2/\tau\big)}{\sum_{\ell=1}^k \exp\!\big(-\|x_i-c_\ell\|_2^2/\tau\big)}.$$
Cela minimise l’objectif régularisé par l’entropie $F(r,c)=\sum_{i=1}^N\sum_{j=1}^k r_{ij}\|x_i-c_j\|_2^2+\tau\sum_{i=1}^N\sum_{j=1}^k r_{ij}\log r_{ij}$ (et coïncide avec l’algorithme **EM** pour un mélange gaussien à poids égaux et covariance sphérique fixée $\sigma^2 I$ avec $\tau=2\sigma^2$).

```text
Entrée : données X = {x_1,...,x_N}, nombre de clusters k, température tau > 0
Initialiser k centres c_1, ..., c_k
Répéter :
  1. Affectation souple (E-step) : pour chaque i = 1..N et j = 1..k,
       r_{ij} <- exp(-||x_i - c_j||^2 / tau) / somme_{l=1..k} exp(-||x_i - c_l||^2 / tau)
  2. Mise à jour (M-step) : pour j = 1..k,
       c_j <- (somme_{i=1..N} r_{ij} x_i) / (somme_{i=1..N} r_{ij})
Jusqu’à stabilisation des centres (ou |Delta F| < epsilon)
```

- **Convergence :** l’étape 1 minimise exactement $F(r,c)$ par rapport à $r$ (à $c$ fixé) et l’étape 2 minimise exactement $F(r,c)$ par rapport à $c$ (à $r$ fixé). Comme $F$ est décroissant à chaque étape et minoré ($F(r,c)\ge -N\tau\log k$), la suite des valeurs $F(r^{(t)},c^{(t)})$ **converge** vers un point stationnaire (là encore sans garantie d’optimum global). **答案（中文）：** 一种经典做法是使用带温度（刚度）参数 $\tau>0$ 的 **softmax** 形式定义样本 $x_i$ 属于第 $j$ 簇的概率责任度 $r_{ij}\in[0,1]$（满足 $\sum_j r_{ij}=1$）：
$$r_{ij}=\frac{\exp(-\|x_i-c_j\|_2^2/\tau)}{\sum_{\ell=1}^k \exp(-\|x_i-c_\ell\|_2^2/\tau)}.$$
这对应最小化熵正则化目标 $F(r,c)=\sum_{i,j}r_{ij}\|x_i-c_j\|_2^2+\tau\sum_{i,j}r_{ij}\log r_{ij}$（也等价于各组分等权、球形固定协方差 $\sigma^2 I$ 且 $\tau=2\sigma^2$ 的高斯混合模型 **EM** 算法）。更新后的伪代码为在固定中心下用上式计算权重矩阵 $r_{ij}$（E 步），再在更新步计算加权均值 $c_j=\frac{\sum_i r_{ij}x_i}{\sum_i r_{ij}}$（M 步），交替迭代直至中心或目标 $F$ 变化小于阈值。

- **收敛性论证**：E 步与 M 步分别在固定对方时严格最小化同一个目标函数 $F(r,c)$，因此 $F$ 每步单调不增；又因为熵项有界使得 $F(r,c)\ge -N\tau\log k$ 存在下界，故目标函数序列必然收敛并趋于局部稳定解（同样不保证全局最优）。 **依据：** [Lab4](../Exercises/Lab4/Lab4_zh.ipynb) · [Lab5](../Exercises/Lab5/Lab5_zh.ipynb)。

c) Is the clustering solution found by the soft k-means a local minimum for the typical k-means? In other words, if we initialize k-means with the solution of soft k-means, would the clusters change or not and why? 软 k-means 得到的聚类解是否是常规 k-means 的局部极小解？换言之，若以软 k-means 的解初始化 k-means，簇会改变吗？为什么？\
**Réponse (FR) :** **En général non**, et les clusters **peuvent changer**. À un optimum de soft k-means, chaque centre est une **moyenne pondérée** de l’ensemble des points avec des poids non nuls ($0<r_{ij}<1$), notamment influencée par les points situés aux frontières entre clusters. Si l’on réinitialise le k-means classique (dur) avec ces centres :
1. Dès l’étape d’affectation dure, chaque point est attribué exclusivement à son centre le plus proche ($r_{ij}\in\{0,1\}$) ;
2. À l’étape de mise à jour, la moyenne non pondérée de cette partition dure ne coïncide généralement pas avec la moyenne pondérée du soft k-means : les centres se déplacent donc et peuvent provoquer un changement de partition.

*(Exception :* les clusters restent inchangés si les affectations souples sont déjà quasi binaires, par exemple lorsque $\tau\to 0^+$ ou lorsque les groupes sont très bien séparés, de sorte que les deux types de moyennes coïncident.)* **答案（中文）：** **通常不是，聚类结果一般会发生变化。** 在软 k-means 的收敛解处，每个中心 $c_j$ 是所有样本按概率 $r_{ij}\in(0,1)$ 算出的**加权均值**，会受到边界模糊点与其他簇样本的牵引。若用这组中心初始化常规硬 k-means：
1. 硬分配会强行把每个点只划给最近的一个中心（权重变成 $0/1$）；
2. 随后的硬均值更新通常不再等于原来的软加权均值，因此中心发生移动，继而可能引起部分边界样本重新分配并使簇划分改变。

*例外情况：* 当温度 $\tau\to 0^+$ 或各簇原本分离得非常清晰时，软分配已接近非 0 即 1 的硬分配，两种均值几乎相等，此时簇划分可能保持不变。 **依据：** [Lab5](../Exercises/Lab5/Lab5_zh.ipynb)。

d) Give additional elements of comparison for the two aforementioned hard and soft k-means approaches? Which are the cases where the latter is better to be used? 进一步比较上述硬 k-means 与软 k-means。哪些情况下更适合采用后者？\
**Réponse (FR) :**
- **Représentation et incertitude :** le k-means dur fournit une partition tranchée, plus rapide et moins coûteuse en mémoire (un seul indice par point). Le k-means souple fournit une **distribution de probabilités d’appartenance** $r_{ij}$, quantifiant l’incertitude pour les points proches des frontières.
- **Sensibilité et coût :** le soft k-means est plus lent (calcul d’exponentielles et somme pondérée sur tous les couples) et introduit un hyperparamètre supplémentaire $\tau$ (ou la variance dans un GMM). De plus, sous sa forme sphérique, il reste limité à des clusters de forme approximativement isotrope (un GMM à covariances libres est nécessaire pour des formes ellipsoïdales) et aucun des deux n’est intrinsèquement robuste aux outliers.
- **Quand préférer le soft k-means :** lorsque les clusters **se chevauchent** (*overlapping*), lorsque les frontières sont ambiguës ou lorsqu’on souhaite exploiter les degrés d’appartenance probabilistes (détection d’ambiguïté, pré-entraînement/caractéristiques souples, modélisation de mélanges). **答案（中文）：**
- **输出信息与代价对比**：硬 k-means 给出非此即彼的明确划分，计算简单、无需存储 $N\times k$ 的概率矩阵；软 k-means 保留了每个样本对各簇的**归属概率 / 不确定度**，目标函数更光滑，但计算开销更大且多了一个需要选择的超参数（温度 $\tau$）。此外，上述标准软 k-means 隐含等大球形簇假设（若簇呈不同椭球形状需推广到自由协方差的 GMM），且两者本身都不抗离群点。
- **更适合使用软 k-means 的场景**：**簇之间存在重叠**、边界样本归属模糊，或者下游任务需要利用样本的**软概率成员度**（例如评估分类置信度、检测跨界过渡样本、概率混合建模）而非生硬切分时。 **依据：** [Lab4](../Exercises/Lab4/Lab4_zh.ipynb) · [Lab5](../Exercises/Lab5/Lab5_zh.ipynb)。

## Exercice 3. Graphical models [4 points] 第 3 题：概率图模型 [4 分]

> **审查注（2026-09-15，非原题）：** 题干没有给出传感器失效时报警保持静默的概率。即使按 $b\to c\to a$ 的链式结构并采用 $a\perp b\mid c$，仍需设 $q=P(a=0\mid c=0)$，不能自行假定它是 0、1 或 0.99。题中已知量给出 $P(c=0)=0.039$，因此 $P(a=0)=0.95139+0.039q$，且 $P(b=0\mid a=0)=(0.0693+0.03q)/(0.95139+0.039q)$。条件概率表中 $c=0$ 的一列及后两问应保留 $q$，或等待补充题面；边际独立性也不能仅由图上存在一条路径就断言。原题正文在下方保留。

A security system relies on a battery, a sensor, and an alarm. Consider the three respective binary random variables a, b, c. When the alarm fires: a = 1; when the battery functions properly: b = 1; and when the sensor functions properly: c = 1. Otherwise, those variables take a value equal to 0. The system architecture is very simple: the battery powers the sensor, and the sensor feeds information to the controller of the alarm that decides to fire to signify a threat. The system manual informs us that: 某安全系统由电池、传感器和报警器构成。考虑三个二元随机变量 $a,b,c$：报警器响起时 $a=1$，电池正常工作时 $b=1$，传感器正常工作时 $c=1$；否则相应变量取 0。系统结构很简单：电池为传感器供电，传感器向报警控制器提供信息，控制器决定是否响起以表示存在威胁。系统手册给出以下信息：\
• the probability for the battery to fail is 0.1 电池失效的概率为 0.1。\
• the probability for the sensor to fail is 0.01 when the battery is ok, and 0.3 when the battery is not ok. 电池正常时，传感器失效的概率为 0.01；电池失效时，传感器失效的概率为 0.3。\
• the probability for the alarm to be silent is 0.99, when the sensor works fine. 传感器正常工作时，报警器保持静默的概率为 0.99。

a) Give the graphical model that involves the variables of this problem, and translate all the known information given by the manual to proper writing with probabilities (it does not involve calculations). 给出包含这些变量的概率图模型，并将手册中的全部已知信息写成恰当的概率表达式（不需要计算）。\
**Réponse (FR) :** Selon l’architecture causale décrite (la batterie alimente le capteur, qui transmet l’information à l’alarme), le modèle graphique est une **chaîne markovienne (réseau bayésien)** $b \to c \to a$, traduisant l’indépendance conditionnelle $a \perp b \mid c$ et la factorisation :
$$p(a,b,c)=p(b)\,p(c\mid b)\,p(a\mid c).$$
Les informations du manuel s’écrivent :
- $P(b=0)=0.1$ (d’où $P(b=1)=0.9$) ;
- $P(c=0\mid b=1)=0.01$ (d’où $P(c=1\mid b=1)=0.99$) et $P(c=0\mid b=0)=0.3$ (d’où $P(c=1\mid b=0)=0.7$) ;
- $P(a=0\mid c=1)=0.99$ (d’où $P(a=1\mid c=1)=0.01$).

*(Remarque : le manuel ne précise pas le comportement de l’alarme lorsque le capteur tombe en panne ; on note ce paramètre manquant $q=P(a=0\mid c=0)\in[0,1]$, d’où $P(a=1\mid c=0)=1-q$.)* **答案（中文）：** 根据“电池供电给传感器、传感器控制报警器”的因果顺序，概率图模型为**链式贝叶斯网络**：$b \to c \to a$，即在给定 $c$ 的条件下 $a$ 与 $b$ 条件独立（$a\perp b\mid c$），联合概率分解为 $p(a,b,c)=p(b)\,p(c\mid b)\,p(a\mid c)$。手册信息可写成：
- $P(b=0)=0.1$，$P(b=1)=0.9$；
- $P(c=0\mid b=1)=0.01$，$P(c=1\mid b=1)=0.99$；$P(c=0\mid b=0)=0.3$，$P(c=1\mid b=0)=0.7$；
- $P(a=0\mid c=1)=0.99$，$P(a=1\mid c=1)=0.01$。

*(题面未说明传感器失效时报警器静默的概率，记为参数 $q=P(a=0\mid c=0)\in[0,1]$，则 $P(a=1\mid c=0)=1-q$。)* **依据：** [Lab5](../Exercises/Lab5/Lab5_zh.ipynb) · [作业二](../Exercises/Assignment2/Assignments2_zh.ipynb)。

b) Give the $2 \times 2$ table of the probability $p ( a = 1 | b , c )$ . Examine if a and b are independent. 给出概率 $p(a=1\mid b,c)$ 的 $2\times2$ 表格。考察 $a$ 与 $b$ 是否独立。\
**Réponse (FR) :** Comme $a \perp b \mid c$, on a $P(a=1\mid b,c)=P(a=1\mid c)$ : les deux lignes ($b=0$ et $b=1$) de la table ci-dessous sont donc identiques. En revanche, pour l’**indépendance marginale** entre $a$ et $b$, il faut marginaliser sur $c$ :
- $P(a=1\mid b=1)=(1-q)(0.01)+0.01(0.99)=0.0199-0.01\,q$,
- $P(a=1\mid b=0)=(1-q)(0.30)+0.01(0.70)=0.307-0.30\,q$.

Ces deux quantités diffèrent pour tout $q\neq 0.99$ : **$a$ et $b$ ne sont donc pas marginalement indépendants** en général (sauf cas dégénéré $q=0.99$ où la loi de $a$ ne dépend plus de $c$). **答案（中文）：** 由条件独立性 $a\perp b\mid c$ 可知 $P(a=1\mid b,c)=P(a=1\mid c)$，因此下方 $2\times 2$ 表中 $b=0$ 与 $b=1$ 两行完全相同。但检验 $a$ 与 $b$ 是否**边际独立**需对 $c$ 求和比较边际条件概率：
- $P(a=1\mid b=1)=(1-q)\times 0.01 + 0.01\times 0.99 = 0.0199 - 0.01\,q$；
- $P(a=1\mid b=0)=(1-q)\times 0.30 + 0.01\times 0.70 = 0.307 - 0.30\,q$。

仅当 $q=0.99$（即传感器是否正常根本不影响报警率）时两者相等；对于其他所有 $q\in[0,1]$，$a$ 与 $b$ **边际不独立（相关）**。 **依据：** [Lab5](../Exercises/Lab5/Lab5_zh.ipynb)。

| $P(a=1\mid b,c)$ | $c=0$ | $c=1$ |
| --- | --- | --- |
| $b=0$ | $1-q$ | $0.01$ |
| $b=1$ | $1-q$ | $0.01$ |

c) Compute the probability for the alarm to be silent. 计算报警器保持静默的概率。\
**Réponse (FR) :** On marginalise d’abord sur l’état $b$ de la batterie pour obtenir la loi du capteur $c$ :
$$P(c=0)=P(c=0\mid b=1)P(b=1)+P(c=0\mid b=0)P(b=0)=0.01\times 0.9+0.3\times 0.1=0.039,$$
$$P(c=1)=1-0.039=0.961.$$
En marginalisant ensuite sur $c$, la probabilité que l’alarme reste silencieuse est :
$$P(a=0)=P(a=0\mid c=1)P(c=1)+P(a=0\mid c=0)P(c=0)=0.99\times 0.961 + 0.039\,q = 0.95139 + 0.039\,q \in [0.95139,\,0.99039].$$
**答案（中文）：** 先对电池状态 $b$ 边缘化求出传感器状态概率：
$$P(c=0)=0.01\times 0.9 + 0.3\times 0.1 = 0.039,\qquad P(c=1)=0.961.$$
再对传感器状态 $c$ 求和得到报警器静默概率：
$$P(a=0)=0.99\times 0.961 + 0.039\,q = 0.95139 + 0.039\,q,$$
随缺失参数 $q\in[0,1]$ 取值在 $[0.95139,\,0.99039]$ 之间。 **依据：** [Lab5](../Exercises/Lab5/Lab5_zh.ipynb)。

d) Suppose we don’t hear any alarm and we have no information about whether the sensor functions correctly. What is the probability of the battery to be malfunctioning? 假设没有听到报警，且不知道传感器是否正常工作。电池失效的概率是多少？\
**Réponse (FR) :** Par la règle de Bayes :
$$P(b=0\mid a=0)=\frac{P(a=0,\,b=0)}{P(a=0)}.$$
Le numérateur s’obtient en marginalisant sur $c$ :
$$P(a=0,\,b=0)=P(b=0)\big[P(a=0\mid c=1)P(c=1\mid b=0)+P(a=0\mid c=0)P(c=0\mid b=0)\big]=0.1\,(0.99\times 0.7 + 0.3\,q)=0.0693+0.03\,q.$$
En divisant par $P(a=0)$ trouvé en (c), on obtient :
$$P(b=0\mid a=0)=\frac{0.0693+0.03\,q}{0.95139+0.039\,q},$$
fonction croissante de $q$ comprise approximativement entre $0.07284$ (pour $q=0$) et $0.10026$ (pour $q=1$). **答案（中文）：** 由贝叶斯公式 $P(b=0\mid a=0)=\frac{P(a=0,b=0)}{P(a=0)}$，其中分子对 $c$ 求和得：
$$P(a=0,b=0)=0.1\times(0.99\times 0.7 + 0.3\,q)=0.0693+0.03\,q.$$
代入 (c) 中求出的 $P(a=0)$，即得电池失效的后验概率：
$$P(b=0\mid a=0)=\frac{0.0693+0.03\,q}{0.95139+0.039\,q},$$
它随 $q\in[0,1]$ 单调递增，数值范围约为 $[0.07284,\,0.10026]$。 **依据：** [Lab5](../Exercises/Lab5/Lab5_zh.ipynb)。

## Exercice 4. Regression and robust estimation [3 points] 第 4 题：回归与稳健估计 [3 分]

a) Let P be a set of N 2-dimensional points, $p _ { i } = ( x _ { i } , y _ { i } )$ . Assume that we want to find the line that best fits the points of P. Present in detail how the Ordinary Least Squares (OLS) works when fitting a linear model by estimating its parameters. 设 $P$ 为由 $N$ 个二维点 $p_i=(x_i,y_i)$ 构成的集合。希望找到最贴合这些点的直线。详细说明普通最小二乘法（OLS）如何通过估计参数拟合线性模型。\
**Réponse (FR) :** On modélise la droite par $\hat y_i = a x_i + b$ et l’on cherche $(a,b)$ minimisant la somme des carrés des résidus verticaux :
$$S(a,b)=\sum_{i=1}^N (y_i - a x_i - b)^2.$$
L’annulation des dérivées partielles $\frac{\partial S}{\partial a}=0$ et $\frac{\partial S}{\partial b}=0$ donne les équations normales. Lorsque les abscisses ne sont pas toutes égales ($S_{xx}=\sum_{i=1}^N (x_i-\bar x)^2>0$), la solution unique est :
$$\hat a = \frac{S_{xy}}{S_{xx}} = \frac{\sum_{i=1}^N (x_i-\bar x)(y_i-\bar y)}{\sum_{i=1}^N (x_i-\bar x)^2}, \qquad \hat b = \bar y - \hat a\,\bar x.$$
On mesure ensuite l’erreur d’ajustement par $\mathrm{RMSE}=\sqrt{\frac{1}{N}\sum_{i=1}^N(y_i-\hat a x_i-\hat b)^2}$ (distincte de l’erreur de test et de l’estimateur du bruit divisant par $N-2$). En dimension $d$, avec une colonne de $1$ dans la matrice de design $X$, on résout $\min_\beta\|y-X\beta\|_2^2$ via QR ou SVD (formule $\hat\beta=(X^TX)^{-1}X^Ty$ sous hypothèse de rang colonne plein). **答案（中文）：** OLS 假设模型为直线 $\hat y_i=ax_i+b$，通过最小化纵向残差平方和 $S(a,b)=\sum_{i=1}^N(y_i-ax_i-b)^2$ 来估计参数。令偏导 $\partial S/\partial a=0$ 与 $\partial S/\partial b=0$，在横坐标不全相同（$S_{xx}>0$）时得到唯一闭式解 $\hat a=S_{xy}/S_{xx}$ 与 $\hat b=\bar y-\hat a\bar x$（公式见上）。训练集拟合优度用 $\mathrm{RMSE}=\sqrt{\frac{1}{N}\sum_i(y_i-\hat y_i)^2}$ 衡量。多维情况下则在设计矩阵 $X$ 中加入全 1 列并求 $\min_\beta\|y-X\beta\|_2^2$，列满秩时正规方程解为 $(X^TX)^{-1}X^Ty$，实际常用 QR 或 SVD 分解保证数值稳定性。 **依据：** [第二课：最小二乘](../Lectures/02_LM/01_linear_models_and_least_squares.md) · [Lab1](../Exercises/Lab1/Lab1_zh.ipynb)。

b) Considering the data of Table 1, apply the OLS by making the numerical calculations and report the fitted model and its Root Mean Squared Error (RMSE). 使用表 1 中的数据，进行数值计算以应用 OLS，并给出拟合模型及其均方根误差（RMSE）。\
**Réponse (FR) :** Pour les $N=4$ points du Tableau 1 :
- Moyennes : $\bar x = \frac{2.2+0.9+0.4-0.6}{4} = 0.725$, $\bar y = \frac{1.2+2+1-1}{4} = 0.8$.
- Sommes centrées : $S_{xx} = (1.475)^2+(0.175)^2+(-0.325)^2+(-1.325)^2 = 4.0675$, $S_{xy} = (1.475)(0.4)+(0.175)(1.2)+(-0.325)(0.2)+(-1.325)(-1.8) = 3.12$.
- Coefficients : $\hat a = \frac{3.12}{4.0675} = \frac{1248}{1627} \simeq 0.7671$, $\hat b = 0.8 - \hat a \times 0.725 = \frac{1984}{8135} \simeq 0.2439$.

La droite ajustée est $\hat y = 0.7671\,x + 0.2439$. Avec les coefficients non arrondis, la somme des carrés des résidus vaut environ $2.4868$, d’où :
$$\mathrm{RMSE} = \sqrt{\frac{2.486785}{4}} \simeq 0.7885.$$
**答案（中文）：** 针对表 1 中的 $N=4$ 个数据点计算如下：
- 均值：$\bar x = 0.725$，$\bar y = 0.8$；
- 中心化平方和与交叉积和：$S_{xx} = 4.0675$，$S_{xy} = 3.12$；
- 回归系数：$\hat a = \frac{3.12}{4.0675} = \frac{1248}{1627} \approx 0.7671$，$\hat b = 0.8 - \hat a\times 0.725 = \frac{1984}{8135} \approx 0.2439$。

拟合直线为 $\hat y = 0.7671\,x + 0.2439$。按未舍入的精确系数计算，残差平方和约为 $2.4868$，故训练集 $\mathrm{RMSE}=\sqrt{2.486785/4}\approx 0.7885$。 **依据：** [第二课：最小二乘](../Lectures/02_LM/01_linear_models_and_least_squares.md) · [Lab1](../Exercises/Lab1/Lab1_zh.ipynb)。

| i | 1 | 2 | 3 | 4 |
| --- | --- | --- | --- | --- |
| xi | 2.2 | 0.9 | 0.4 | -0.6 |
| yi | 1.2 | 2 | 1 | -1 |

Table 1 – Practical example: data points $P = \{ ( x _ { i } , y _ { i } ) , i = 1 . . . 4 \}$ 表 1：实际示例，数据点 $P=\{(x_i,y_i),i=1,\ldots,4\}$。\
c) Describe in detail the standard RANSAC method for linear regression. Explain how each of the several linear models produced internally can ‘grade’ datapoints for being outliers, and conversely how the datapoints can ‘grade’ each such linear model for being a good regressor. 详细描述用于线性回归的标准 RANSAC 方法。解释算法内部产生的多个线性模型分别如何评价数据点成为离群点的程度；反过来，数据点又如何评价每个线性模型作为回归器的好坏。\
**Réponse (FR) :** **Algorithme RANSAC pour la régression linéaire :** Répéter $T$ fois (avec typiquement $T \ge \lceil \log(1-p)/\log(1-w^2)\rceil$ où $w$ est la proportion estimée d’inliers et $p$ la probabilité de succès visée) :
1. Tirer aléatoirement un sous-ensemble minimal de $2$ points d’abscisses distinctes et ajuster une droite candidate $h_t(x)=a_t x + b_t$.
2. Calculer le résidu de chaque point $r_{i,t}=|y_i - h_t(x_i)|$ et identifier l’ensemble consensus (inliers) $I_t = \{i : r_{i,t} \le \tau\}$.
3. Conserver le meilleur consensus $I^*$ (taille maximale $|I_t|$, en départageant les égalités par la plus faible erreur sur les inliers).
À la fin des $T$ itérations, réajuster la droite finale par OLS sur tous les inliers de $I^*$.

**Système de « notation » mutuelle entre modèles candidats et données :**
- **Comment chaque modèle $h_t$ note les points comme outliers :** pour tout point $p_i$, $h_t$ mesure son écart via le résidu $r_{i,t}=|y_i - h_t(x_i)|$ (score continu d’anomalie) ou l’indicateur binaire d’exclusion $\mathbb{I}(r_{i,t}>\tau)$. En observant l’ensemble des bons modèles de consensus (ou le modèle final $h^*$), les points qui conservent systématiquement un grand résidu / de nombreux votes d’exclusion sont identifiés comme *outliers*.
- **Comment les points notent chaque modèle $h_t$ :** chaque point $p_i$ accorde un « vote » de validation à $h_t$ s’il se trouve dans la bande de tolérance, $\mathbb{I}(r_{i,t}\le\tau)=1$ (ou contribue à une perte tronquée bornée $\min(r_{i,t}^2,\tau^2)$ dans la variante MSAC). La qualité globale du modèle $h_t$ est donc notée par la somme des votes reçus des données, c’est-à-dire la taille de son consensus $|I_t|=\sum_{i=1}^N \mathbb{I}(r_{i,t}\le\tau)$ (avec départage par l’erreur des inliers). **答案（中文）：** **标准线性回归 RANSAC 算法：** 重复 $T$ 轮（按内点比例 $w$ 与期望成功率 $p$ 通常取 $T\ge\lceil\log(1-p)/\log(1-w^2)\rceil$）：① 随机抽取 2 个横坐标不同的最小样本点拟合候选直线 $h_t(x)=a_tx+b_t$；② 对全部 $N$ 个样本计算纵向残差 $r_{i,t}=|y_i-h_t(x_i)|$，把满足 $r_{i,t}\le\tau$ 的点划入内点共识集 $I_t$；③ 记录内点数 $|I_t|$ 最大的共识集 $I^*$（相同时比内点误差）。循环结束后，仅用 $I^*$ 中的全部内点重新运行 OLS 得到稳健直线。

**模型与数据点之间的双向“评分”机制：**
- **候选直线 $h_t$ 如何评价数据点是否为离群点**：模型用每个点的残差 $r_{i,t}=|y_i-h_t(x_i)|$ 作为连续的离群程度分数，或用指示函数 $\mathbb{I}(r_{i,t}>\tau)$ 给出二元离群判定。综合多个高共识候选模型（或最终最优模型）的判定，经常落于容差带之外且残差很大的点会被评为高置信度的离群点。
- **数据点如何评价每个候选模型 $h_t$ 的好坏**：每个数据点根据自己是否落在模型周围的阈值带内向 $h_t$ 投“内点支持票” $\mathbb{I}(r_{i,t}\le\tau)$（或在 MSAC 变体中给出截断损失 $\min(r_{i,t}^2,\tau^2)$）。所有数据点的投票之和 $|I_t|=\sum_{i=1}^N \mathbb{I}(r_{i,t}\le\tau)$ 就是该候选模型获得的评分——共识集越大（平局时内点残差越小），该回归模型得分越高。 **依据：** [Lab1](../Exercises/Lab1/Lab1_zh.ipynb) · [作业一第 1 题：RANSAC](../Exercises/Assignment1/guide/01_ransac.md)。
