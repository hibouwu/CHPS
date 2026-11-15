> 双语阅读版：保留原文语言，每个小题单独换行，原文与中文在同一行用空格连接；题目说明与小题之间留空行，公式、数值和图片共用。原文按转换稿整理，修正明显的重音、断词与标点错误；题意以原 PDF 为准。已有中文审查注单独保留，属于补充说明。
> 参考答案：法语在前、中文紧随，置于各小题下一行；依据链接指向本地课件或练习。这是按材料推导的复习答案，并非教师官方答案。计算题注明数值约定，开放题给出一种可行方案；题面缺失条件保留参数，读图近似与精确计算分别标明。

[原 PDF](DataML-CHPS-2024-examen.pdf) · [原文转换稿](DataML-CHPS-2024-examen.md) · [试卷目录](README.md)

# Data & Apprentissage 数据与学习

novembre 2024 2024 年 11 月 Examen final 期末考试 Le sujet est imprimé sur 3 pages – Durée 2 heures 试卷共印为 3 页，时长 2 小时。 Les documents et notes de cours ne sont pas autorisés. L’utilisation de smartphones et l’accès à des ressources documentaires sur Internet sont interdits. L’examen est à réaliser individuellement et toute tentative de collaboration entre étudiants sera sévèrement sanctionnée. 不允许使用资料或课堂笔记。禁止使用手机或访问互联网上的文档资源。考试须独立完成，学生之间任何试图协作的行为都会受到严厉处罚。

> **分值核对：** 原 PDF 五道大题标分依次为 4、5、4、3、3，合计 19 分。本转换稿照录原分值，不推定其应为 20 分或自行补分。

## Exercice 1. General course understanding [4 points] 第 1 题：课程总体理解 [4 分]

Please provide concise replies to each question. 请简明回答以下各题。

1\. Quote one example of algorithm in each of the three main categories of machine learning methods (local, global, ensemble). 针对机器学习方法的三大类别（局部、全局、集成），各举一个算法例子。\
**Réponse (FR) :** Selon le cours, les trois grandes catégories (non strictement disjointes) sont :
- **Méthode locale :** $k$ plus proches voisins ($k$-NN) (ou arbre de décision) ;
- **Méthode globale :** régression Ridge (ou SVM, optimisant un objectif global) ;
- **Méthode d’ensemble :** Forêts aléatoires (Random Forests) ou Bagging *(le Boosting appartient quant à lui à la fois aux méthodes globales et d’ensemble)*. **答案（中文）：** 按课程划分的三大家族（彼此并非完全互斥）各举一例如下：
- **局部方法**：$k$ 近邻（$k$-NN）（或决策树）；
- **全局方法**：岭回归（Ridge）（或支持向量机 SVM，通过全局目标函数求解）；
- **集成方法**：随机森林（Random Forests）或 Bagging*（课件也将 Boosting 同时归入全局与集成方法）*。 **依据：** [第一课：算法与流程](../Lectures/01_intro/02_algorithms_and_pipeline.md)。

2\. Explain what is the trade-off between estimation error and approximation error in machine learning and how can this be solved? 解释机器学习中估计误差与近似误差之间的权衡，以及如何处理这种权衡。\
**Réponse (FR) :** En notant $R$ le risque vrai, $f^*$ l’optimum sans restriction (règle de Bayes) et $f_{\mathcal{H}}^*=\arg\min_{f\in\mathcal{H}} R(f)$ le meilleur modèle dans la classe d’hypothèses $\mathcal{H}$, l’excès de risque d’un modèle appris $\hat f_n\in\mathcal{H}$ se décompose en :
$$R(\hat f_n)-R(f^*) = \underbrace{\big[R(\hat f_n)-R(f_{\mathcal{H}}^*)\big]}_{\text{Erreur d'estimation}} + \underbrace{\big[R(f_{\mathcal{H}}^*)-R(f^*)\big]}_{\text{Erreur d'approximation}}$$
*(plus une éventuelle erreur d’optimisation si la minimisation empirique est inexacte)*.
- **Le compromis :** si $\mathcal{H}$ est trop simple, l’erreur d’approximation est élevée (sous-apprentissage) ; si $\mathcal{H}$ est trop riche par rapport à la taille $n$ de l’échantillon, l’erreur d’approximation diminue mais l’erreur d’estimation augmente (surapprentissage).
- **Comment le résoudre :** contrôler la capacité de $\mathcal{H}$ par **régularisation** ($\lambda\Omega(f)$) ou sélection de modèle, calibrer les hyperparamètres par **validation croisée**, et lorsque c’est possible, **augmenter le nombre de données $n$**. **答案（中文）：** 设 $R$ 为真实风险，$f^*$ 为无函数类限制的全局理论最优解，$f_{\mathcal{H}}^*$ 为假设空间 $\mathcal{H}$ 内的最优解，则所选模型 $\hat f_n\in\mathcal{H}$ 的超额风险可分解为**估计误差 + 近似误差**两项（见上式；若经验风险最小化不精确，还会包含优化误差）：
- **权衡本质**：假设空间 $\mathcal{H}$ 过简单时，近似误差大（欠拟合）；扩大 $\mathcal{H}$ 可降低近似误差，但在样本量 $n$ 有限时估计误差反而增大（过拟合）。
- **处理方法**：通过**正则化**（$\lambda\Omega(f)$）或限制模型复杂度来控制容量，用**交叉验证**校准复杂度/正则化强度以最小化两者之和，并在条件允许时**增加训练样本量 $n$** 来压低估计误差。 **依据：** [第一课：学习框架](../Lectures/01_intro/01_data_and_learning.md) · [第一课：误差与偏差—方差](../Lectures/01_intro/04_hypotheses_and_bias_variance.md) · [第六课：深度学习](../Lectures/06_DL_zh.md)。

3\. What is the optimization strategy in deep learning? 深度学习采用什么优化策略？\
**Réponse (FR) :** On minimise un risque empirique (éventuellement régularisé) par **descente de gradient stochastique par mini-lots (*mini-batch SGD*)** ou ses variantes adaptatives (**Adam**, RMSprop) :
$$\theta_{t+1}=\theta_t-\eta_t\nabla_\theta\!\left[\frac{1}{|B_t|}\sum_{i\in B_t}\ell(f_\theta(x_i),y_i)+\lambda\Omega(\theta)\right]\Bigg|_{\theta=\theta_t}.$$
À chaque étape, la **rétropropagation** calcule efficacement le gradient de tous les paramètres grâce à la dérivation en chaîne sur le mini-lot $B_t$, puis l’optimiseur met à jour $\theta$. L’objectif étant non convexe, une bonne **initialisation**, un calendrier de **taux d’apprentissage** $\eta_t$, une taille de lot adaptée et l’**arrêt précoce (*early stopping*)** sont déterminants. **答案（中文）：** 深度学习采用**小批量随机梯度下降（mini-batch SGD）**及其自适应优化器（如 **Adam**、RMSprop）最小化（可带正则项的）经验风险（见上式）。每步在前向传播计算小批量 $B_t$ 的损失后，利用**反向传播（Backpropagation）**基于链式法则高效计算全网梯度并更新参数 $\theta$。由于目标高度非凸，合适的权重初始化、学习率调度（$\eta_t$）、批大小设置以及早停（early stopping）尤为关键。 **依据：** [第六课：深度学习](../Lectures/06_DL_zh.md)。

4\. Give an example of hyperparameter in a specific machine learning method and explain how it can be calibrated. 针对某种具体的机器学习方法，给出一个超参数例子，并解释如何校准它。\
**Réponse (FR) :** **Exemple :** le coefficient de régularisation $\lambda$ en régression Ridge (ou la profondeur maximale `max_depth` d’un arbre de décision). Il n’est pas appris par minimisation sur le jeu d’entraînement seul, car cela mènerait toujours à une complexité excessive ($\lambda=0$).
**Calibration par validation croisée ($K$ plis) :** (1) réserver un jeu de test indépendant pour l’évaluation finale ; (2) définir une grille de valeurs candidates pour $\lambda$ (ou procéder par recherche aléatoire/bayésienne) ; (3) pour chaque candidat, entraîner le modèle sur $K-1$ plis et mesurer l’erreur sur le pli de validation restant, puis moyenner sur les $K$ plis ; (4) retenir $\lambda^*$ minimisant ce risque de validation, réentraîner le modèle sur l’ensemble des données de développement et l’évaluer une seule fois sur le test. *(Pour des séries temporelles, remplacer le $K$-pli aléatoire par une validation chronologique.)* **答案（中文）：** **示例**：岭回归中的正则化强度 $\lambda$（或决策树的最大深度 `max_depth`）。超参数不能仅靠训练集拟合误差确定（否则会趋向 $\lambda=0$ 或最大深度而过拟合）。
**校准流程（$K$ 折交叉验证）**：① 先划分并隔离最终测试集；② 设定候选集合（网格、随机或贝叶斯采样）；③ 对每个候选值，依次在 $K-1$ 折上训练并在剩余 1 折上计算验证误差，求 $K$ 折平均风险；④ 选出验证误差最小的 $\lambda^*$，用全部开发数据（训练+验证）重新训练最终模型，并在独立测试集上评估一次（时间序列须采用保持时序的划分）。 **依据：** [第二课：正则化与验证](../Lectures/02_LM/06_regularization_and_validation.md) · [Lab1](../Exercises/Lab1/Lab1_zh.ipynb) · [作业一第 4 题：数据划分](../Exercises/Assignment1/guide/04_data_splitting.md)。

## Exercice 2. Course understanding - Decision trees [5 points] 第 2 题：课程理解——决策树 [5 分]

1\. What is a decision tree in the context of binary classification? 在二分类问题中，什么是决策树？\
**Réponse (FR) :** En classification binaire ($Y\in\{0,1\}$), un arbre de décision est un classifieur hiérarchique qui partitionne récursivement l’espace des entrées $\mathcal{X}$ en régions disjointes (des boîtes rectangulaires dans le cas de coupures univariées $x_j\le s$) via une suite de tests aux nœuds internes. Chaque feuille porte une étiquette prédite dans $\{0,1\}$ (ou la fréquence empirique de la classe positive dans la région correspondante). **答案（中文）：** 在二分类（$Y\in\{0,1\}$）中，决策树是一种分层模型：通过在内部节点逐层施加特征测试（通常为单变量阈值 $x_j\le s$），将输入空间 $\mathcal{X}$ 递归划分为互不相交的矩形区域（叶单元）；每个叶节点赋予一个 $\{0,1\}$ 类别标签（或该区域内正类的经验比例）。 **依据：** [第五课：SVM、树与集成](../Lectures/05_NLM_zh.md) · [Lab2](../Exercises/Lab2/Lab2_zh.ipynb)。

2\. Consider a new point x, what is the label y assigned by the decision tree? 对一个新的点 $x$，决策树会赋予它什么标签 $y$？\
**Réponse (FR) :** On fait descendre $x$ depuis la racine en évaluant à chaque nœud interne la condition (par ex. $x_j\le s$ ? branche gauche sinon droite) jusqu’à atteindre une unique feuille $L(x)$. L’étiquette attribuée est la **classe majoritaire** des observations d’apprentissage tombées dans $L(x)$ : $\hat y(x)=\arg\max_{c\in\{0,1\}} n_{L(x),c}$ (ou par seuillage de la proportion positive $n_{L(x),1}/n_{L(x)}$ selon le coût des erreurs). **答案（中文）：** 从根节点出发，按每个内部节点的判断条件（例如检验 $x_j\le s$ 决定走左分支还是右分支）逐层下移，直到落入唯一的叶节点 $L(x)$；随后取训练集中落入该叶的**多数类**作为预测标签 $\hat y(x)=\arg\max_{c\in\{0,1\}} n_{L(x),c}$（也可结合错分代价对叶内正类频率设定判定阈值）。 **依据：** [第五课：SVM、树与集成](../Lectures/05_NLM_zh.md) · [Lab2](../Exercises/Lab2/Lab2_zh.ipynb)。

3\. Consider a set of supervised classification data. Provide the pseudocode in order to train a decision tree classifier. 给定一组监督分类数据，给出训练决策树分类器的伪代码。\
**Réponse (FR) :** On construit l’arbre de manière gloutonne et récursive (*top-down*) en maximisant à chaque division la réduction d’impureté (par ex. indice de Gini $I(S)=1-\sum_c p_c^2$ ou entropie) :

```text
Fonction GrowTree(S, profondeur) :
  Si condition_d_arret(S, profondeur) :
    Retourner Feuille(classe_majoritaire(S))
  (j*, t*) <- argmax_{(j,t) admissible} [ I(S) - (|S_L|/|S|)*I(S_L) - (|S_R|/|S|)*I(S_R) ]
     avec S_L = {x in S : x_j <= t}, S_R = S \ S_L
  Si gain_max <= epsilon :
    Retourner Feuille(classe_majoritaire(S))
  gauche <- GrowTree(S_L, profondeur + 1)
  droite <- GrowTree(S_R, profondeur + 1)
  Retourner Noeud(test: x_{j*} <= t*, gauche, droite)
```
*(Suivi éventuellement d’un élagage postérieur par coût-complexité calibré sur validation.)* **答案（中文）：** 采用自顶向下的贪心递归算法构建分类树（常用 Gini 不纯度 $I(S)=1-\sum_c p_c^2$ 或交叉熵，伪代码见上）：若当前样本子集 $S$ 满足停止条件则返回叶节点（赋予多数类）；否则遍历各特征 $j$ 与合法切分阈值 $t$，选出使加权不纯度下降 $\Delta I = I(S)-\frac{|S_L|}{|S|}I(S_L)-\frac{|S_R|}{|S|}I(S_R)$ 最大的分裂 $(j^*, t^*)$（若无合法正增益则直接返回叶节点），建立内部节点并对左右子集 $S_L,S_R$ 递归建树（建树后可再配合验证集做代价复杂度剪枝）。 **依据：** [第五课：SVM、树与集成](../Lectures/05_NLM_zh.md) · [Lab2](../Exercises/Lab2/Lab2_zh.ipynb)。

4\. Give at least two stopping rules of the training procedure of decision trees. 至少给出两条决策树训练过程的停止规则。\
**Réponse (FR) :** Parmi les règles d’arrêt usuelles, on peut citer :
1. **Nœud pur :** toutes les observations de $S$ appartiennent à la même classe ($I(S)=0$).
2. **Profondeur maximale atteinte :** `profondeur == max_depth`.
3. **Effectif insuffisant :** $|S| < \text{min\_samples\_split}$, ou aucune coupure ne laisse au moins `min_samples_leaf` points dans chaque fils.
4. **Gain d’impureté insuffisant :** $\max_{(j,t)} \Delta I < \text{min\_impurity\_decrease}$. **答案（中文）：** 常见停止规则至少可列出如下几条（任选两条即可）：
1. **节点已纯**：当前子集样本全部属于同一类别（不纯度 $I(S)=0$）；
2. **达到最大深度**：当前节点深度等于预先设定的 `max_depth`；
3. **样本数不足**：节点样本数小于 `min_samples_split`，或任何切分都会使子节点样本数小于 `min_samples_leaf`；
4. **不纯度下降过小**：所有候选分裂带来的最大增益 $\Delta I$ 低于预设最小阈值 `min_impurity_decrease`。 **依据：** [第五课：SVM、树与集成](../Lectures/05_NLM_zh.md) · [Lab2](../Exercises/Lab2/Lab2_zh.ipynb)。

5\. Give at least two hyperparameters of decision trees. 至少给出两个决策树超参数。\
**Réponse (FR) :** Contrôlant la complexité (et réglés par validation, contrairement aux variables/seuils appris) :
- **Profondeur maximale** (`max_depth`) et **nombre maximal de feuilles** (`max_leaf_nodes`) ;
- **Taille minimale** pour diviser un nœud (`min_samples_split`) ou dans une feuille (`min_samples_leaf`) ;
- **Critère d’impureté** (Gini ou entropie), gain minimal et paramètre d’**élagage** ($\alpha$). **答案（中文）：** 决策树的典型超参数包括（任举两例，需与训练学得的分裂特征和阈值区分）：
- **树规模限制**：最大深度（`max_depth`）、最大叶节点数（`max_leaf_nodes`）；
- **样本量与增益约束**：节点分裂最少样本数（`min_samples_split`）、叶节点最少样本数（`min_samples_leaf`）；
- **度量与剪枝参数**：不纯度准则（Gini 指数或交叉熵）、最小不纯度下降阈值以及后剪枝复杂度惩罚系数 $\alpha$。 **依据：** [第五课：SVM、树与集成](../Lectures/05_NLM_zh.md) · [Lab2](../Exercises/Lab2/Lab2_zh.ipynb)。

6\. Is it possible to monitor the number of cells of the tree using the training data? 能否利用训练数据控制树的叶单元数量？\
**Réponse (FR) :** **Oui** : chaque feuille de l’arbre correspond à une cellule de la partition. Sur les données d’entraînement, on contrôle le nombre de cellules soit **directement** (en fixant `max_leaf_nodes` lors de la croissance gloutonne), soit **indirectement** via la profondeur maximale (au plus $2^D$ feuilles), `min_samples_leaf`, ou l’**élagage coût-complexité** $\min_T \big[R_{\mathrm{train}}(T)+\alpha\,|\mathrm{feuilles}(T)|\big]$. Attention toutefois : la sélection de la valeur optimale de feuilles (ou de $\alpha$) doit se faire sur un jeu de **validation**, car l’erreur d’entraînement seule favorise toujours le plus grand nombre de cellules (surapprentissage). **答案（中文）：** **可以。** 决策树的每一个叶节点就对应输入空间划分中的一个区域单元。训练阶段既可以**直接限制**最大叶节点数（`max_leaf_nodes`），也可以通过最大深度（$D$ 层至多 $2^D$ 个叶）、叶节点最少样本数或**代价复杂度剪枝**目标 $R_{\mathrm{train}}(T)+\alpha|\mathrm{feuilles}(T)|$ 来调控叶单元数量。但必须注意：具体选择多少个叶单元（或选多大的 $\alpha$）不能只看训练误差，而要借助**验证集**来选定，以免单元过多导致过拟合。 **依据：** [第五课：SVM、树与集成](../Lectures/05_NLM_zh.md) · [Lab2](../Exercises/Lab2/Lab2_zh.ipynb)。

7\. What are the pros and cons of decision trees? 决策树有哪些优点和缺点？\
**Réponse (FR) :**
- **Avantages :** très interprétables à faible profondeur (règles explicites), sélection intégrée des variables, modélisation naturelle des interactions et non-linéarités, aucune standardisation requise (invariance monotone pour les coupures univariées) et utilisables en classification comme en régression.
- **Inconvénients :** forte **variance** et **instabilité** (un léger changement des données peut modifier toute la structure), forte tendance au **surapprentissage** si l’arbre est profond, construction gloutonne sous-optimale, frontières strictement parallèles aux axes (peu adaptées aux frontières obliques/diagonales) et incapacité à extrapoler en régression (prédictions constantes hors domaine). **答案（中文）：**
- **优点**：浅层树可解释性极强（直观规则）、自带特征选择、无需特征标准化（单变量切分对单调缩放不变）、天然捕捉非线性与特征交互，且可同时用于分类与回归。
- **缺点**：**方差大、模型不稳定**（数据微小扰动可能大幅改变整棵树）、深树极易**过拟合**、贪心分裂未必得到全局最优树、决策边界只能轴对齐（拟合斜边界低效），且回归任务中叶值恒定导致区间外**不善外推**。 **依据：** [第五课：SVM、树与集成](../Lectures/05_NLM_zh.md) · [Lab2](../Exercises/Lab2/Lab2_zh.ipynb) · [Lab3](../Exercises/Lab3/Lab3_zh.ipynb)。

8\. Is it possible to solve the drawbacks of decision trees? 能否克服决策树的缺点？\
**Réponse (FR) :** **Oui en grande partie**, grâce à deux leviers :
1. **Contrôler la complexité d’un arbre unique** (profondeur maximale, taille minimale des feuilles, élagage coût-complexité validé) pour limiter le surapprentissage.
2. **Utiliser des méthodes d’ensemble :** le **Bagging** et les **Forêts aléatoires (*Random Forests*)** agrègent de nombreux arbres construits sur des échantillons bootstrap (et sous-ensembles aléatoires de variables) afin de réduire drastiquement la **variance** et stabiliser les frontières ; le **Gradient Boosting** combine séquentiellement des arbres peu profonds pour réduire le **biais** et approcher des frontières complexes.
*(En contrepartie, on perd l’interprétabilité immédiate d’un arbre unique, et les moyennes d’arbres restent incapables d’extrapoler des tendances hors du domaine appris.)* **答案（中文）：** **大部分缺点可以显著缓解**：
1. **控制单棵树复杂度**（限制深度、设定叶节点最小样本数并结合验证集剪枝）来抑制过拟合；
2. **采用集成方法**：用 **Bagging 与随机森林（Random Forests）** 对大量自助采样树（及随机特征子集分裂）取均值或投票，可大幅降低**方差**与结构不稳定性；用 **梯度提升（Gradient Boosting）** 序列化叠加浅树修正残差，可显著降低**偏差**并更精细地逼近斜边界。
*（需要权衡的是：集成模型牺牲了单棵小树的直观可读性，且基于常值叶的树集成在训练域外仍难以有效外推线性趋势。）* **依据：** [第五课：SVM、树与集成](../Lectures/05_NLM_zh.md) · [Lab3](../Exercises/Lab3/Lab3_zh.ipynb)。

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

a) Considering the data of Table 1, apply the OLS by making the numerical calculations and report the fitted model and its Root Mean Squared Error (RMSE). 使用表 1 中的数据，进行数值计算以应用 OLS，并给出拟合模型及其均方根误差（RMSE）。\
**Réponse (FR) :** Pour un modèle linéaire $\hat y = a x + b$, la méthode OLS donne $\hat a = \frac{S_{xy}}{S_{xx}}$ et $\hat b = \bar y - \hat a\,\bar x$. Sur les $N=4$ points du Tableau 1 :
- Moyennes : $\bar x = \frac{2.2+0.9+0.4-0.6}{4} = 0.725$, $\bar y = \frac{1.2+2+1-1}{4} = 0.8$.
- Sommes centrées : $S_{xx} = (1.475)^2+(0.175)^2+(-0.325)^2+(-1.325)^2 = 4.0675$, $S_{xy} = (1.475)(0.4)+(0.175)(1.2)+(-0.325)(0.2)+(-1.325)(-1.8) = 3.12$.
- Paramètres : $\hat a = \frac{3.12}{4.0675} = \frac{1248}{1627} \simeq 0.7671$, $\hat b = 0.8 - \hat a \times 0.725 = \frac{1984}{8135} \simeq 0.2439$.

La droite ajustée est $\hat y = 0.7671\,x + 0.2439$. En évaluant la somme des carrés des résidus avec les coefficients exacts ($\mathrm{SSR} \simeq 2.4868$), on obtient un $\mathrm{RMSE}$ d’ajustement :
$$\mathrm{RMSE} = \sqrt{\frac{2.486785}{4}} \simeq 0.7885.$$
**答案（中文）：** 设线性模型为 $\hat y = ax+b$，OLS 解析解为 $\hat a=S_{xy}/S_{xx}$、$\hat b=\bar y-\hat a\bar x$。对表 1 中 $N=4$ 个数据点依次计算：
- 均值：$\bar x = 0.725$，$\bar y = 0.8$；
- 中心化平方和与交叉积和：$S_{xx} = 4.0675$，$S_{xy} = 3.12$；
- 拟合参数：$\hat a = \frac{3.12}{4.0675} = \frac{1248}{1627} \approx 0.7671$，$\hat b = 0.8 - \hat a\times 0.725 = \frac{1984}{8135} \approx 0.2439$。

所得拟合模型为 $\hat y = 0.7671\,x + 0.2439$。用未舍入的精确系数计算残差平方和约为 $2.4868$，故训练集 $\mathrm{RMSE}=\sqrt{2.486785/4}\approx 0.7885$。 **依据：** [第二课：最小二乘](../Lectures/02_LM/01_linear_models_and_least_squares.md) · [Lab1](../Exercises/Lab1/Lab1_zh.ipynb)。

| i | 1 | 2 | 3 | 4 |
| --- | --- | --- | --- | --- |
| xi | 2.2 | 0.9 | 0.4 | -0.6 |
| yi | 1.2 | 2 | 1 | -1 |

Table 1 – Practical example: data points $P = \{ ( x _ { i } , y _ { i } ) , i = 1 . . . 4 \}$ 表 1：实际示例，数据点 $P=\{(x_i,y_i),i=1,\ldots,4\}$。\
b) In a given dataset P, the datapoints are assumed to be distributed in a circular shape (e.g. see the figure below). We are interested to learn a circular model $C ( c , r )$ that best fits the data. Recall that the standard equation of a 2D circle centered at $c = ( x _ { c } , y _ { c } )$ and of radius r is: $( x - x _ { c } ) ^ { 2 } + ( y - y _ { c } ) ^ { 2 } = r ^ { 2 }$ . Develop in detail how this problem could be solved with the generalized RANSAC approach. 给定数据集 $P$，假设数据点大致沿圆形分布（如下图）。希望学习最贴合数据的圆模型 $C(c,r)$。回顾二维圆的标准方程：圆心为 $c=(x_c,y_c)$、半径为 $r$ 时，$(x-x_c)^2+(y-y_c)^2=r^2$。详细说明如何用广义 RANSAC 方法解决这一问题。\
**Réponse (FR) :** Pour adapter RANSAC au modèle circulaire $C(c,r)$ (3 paramètres : $x_c, y_c, r$), la taille d’échantillon minimal passe de $2$ à **$s=3$ points** :

1. **Échantillonnage minimal et ajustement candidat :** tirer aléatoirement $3$ points $p_1, p_2, p_3 \in P$ non colinéaires (rejeter le tirage si les points sont quasi alignés). Le centre candidat $c=(x_c,y_c)$ se trouve à l’intersection des médiatrices en résolvant le système linéaire $2\times 2$ obtenu par soustraction des équations du cercle :
   $$2(p_2-p_1)^T c = \|p_2\|_2^2 - \|p_1\|_2^2, \qquad 2(p_3-p_1)^T c = \|p_3\|_2^2 - \|p_1\|_2^2,$$
   puis le rayon candidat vaut $r = \|p_1 - c\|_2$.
2. **Calcul du résidu géométrique et consensus :** pour chaque point $p_i \in P$, évaluer sa distance radiale exacte au cercle candidat (préférable au résidu algébrique qui dépend de l’échelle de $r$) :
   $$e_i = \big|\,\|p_i - c\|_2 - r\,\big|.$$
   Former l’ensemble des *inliers* $I_t = \{i : e_i \le \tau\}$, où $\tau>0$ dépend de l’amplitude du bruit de mesure.
3. **Nombre d’itérations et sélection :** répéter $T$ fois, avec $T \ge \lceil \log(1-p)/\log(1-w^3)\rceil$ pour garantir avec probabilité $p$ qu’au moins un triplet tiré soit entièrement composé d’inliers (de proportion $w$). Conserver le meilleur consensus $I^*$ de taille maximale (en départageant par la plus faible erreur sur les inliers).
4. **Réajustement final sur tous les inliers :** affiner $(c^*, r^*)$ sur l’ensemble $I^*$ par moindres carrés (minimiser $\sum_{i\in I^*}(\|p_i-c\|_2 - r)^2$ sous $r>0$, initialisé par la solution du triplet optimal) pour réduire l’effet du bruit d’échantillonnage. **答案（中文）：** 将标准 RANSAC 推广到二维圆拟合 $C(c,r)$（含三个参数 $x_c, y_c, r$），核心改动在于**最小抽样样本数变为 $s=3$**、模型求解与几何残差定义如下：

1. **最小抽样与候选圆求解**：每轮从 $P$ 中随机抽取 3 个不共线的点 $p_1, p_2, p_3$（若接近共线则舍弃重抽）。将三点分别代入圆方程后两两相减，可消去二次项得到关于圆心 $c=(x_c,y_c)$ 的 $2\times 2$ 线性方程组（见上式），解出 $c$ 后半径即为 $r=\|p_1-c\|_2$。
2. **几何径向残差与共识集筛选**：对全体 $N$ 个点计算到候选圆周的**正交（径向）距离**：$e_i=\big|\,\|p_i-c\|_2 - r\,\big|$（物理含义明确，优于受半径大小影响的代数残差 $(x-x_c)^2+(y-y_c)^2-r^2$）；以噪声尺度阈值 $\tau$ 划分内点共识集 $I_t=\{i : e_i\le\tau\}$。
3. **迭代次数与最佳共识保留**：由于每次需同时抽中 3 个内点（内点比例记为 $w$），迭代轮数需满足 $T\ge\lceil\log(1-p)/\log(1-w^3)\rceil$；保留内点数 $|I_t|$ 最大的共识集 $I^*$（平局时取内点误差之和最小者）。
4. **全局内点精修拟合**：迭代结束后，利用全部内点 $I^*$ 求解非线性最小二乘 $\min_{c,\,r>0}\sum_{i\in I^*}(\|p_i-c\|_2 - r)^2$（以最佳候选圆或代数拟合为初值），从而消除仅靠 3 个点拟合带来的噪声放大。 **依据：** [Lab1](../Exercises/Lab1/Lab1_zh.ipynb) · [作业一第 1 题：RANSAC](../Exercises/Assignment1/guide/01_ransac.md)。

![image](<Images/DataML-CHPS-2024-examen/image_001.jpg>)

## Exercice 5. Clustering [3 points] 第 5 题：聚类 [3 分]

> **解题边界提示（非原题）：** 标准 k-means 的交替步骤使目标值不增，多次随机重启有助于寻找更好的解，但不保证有限次重启找到全局最优。软 k-means 的题目要求自行提出概率分配方案；讨论收敛时，应同时说明该方案对应的目标及更新规则。

a) Give the k-means objective function, the pseudocode of the clustering algorithm, explain with simple arguments: why the procedure converges, and how it can be used to approximate the globally optimal solution containing the best possible centroids. 给出 k-means 的目标函数及聚类算法伪代码，并用简单论据解释算法为何收敛，以及如何用它近似寻找包含最佳质心的全局最优解。\
**Réponse (FR) :** L’objectif du $k$-means est de minimiser l’inertie intra-classe :
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

- **Pourquoi il converge :** chaque affectation associe à chaque point le centre le plus proche, et chaque mise à jour remplace chaque centre par la moyenne arithmétique de son groupe (qui minimise exactement la somme des carrés des distances intra-groupe). Ainsi $J\ge 0$ décroît à chaque étape ; comme il n’existe qu’un nombre **fini** de partitions possibles (au plus $k^N$), l’algorithme s’arrête en un nombre fini d’itérations sur un minimum local.
- **Approximation de l’optimum global :** la minimisation exacte de $J$ étant NP-difficile et l’objectif non convexe, on lance l’algorithme avec **plusieurs initialisations aléatoires** indépendantes (ou mieux avec **k-means++**, qui disperse les centres initiaux proportionnellement à $D(x)^2$) et l’on retient la solution présentant la plus faible inertie $J$ (sans garantie absolue d’atteindre l’optimum global en un nombre fini d’essais). **答案（中文）：** $k$-means 的目标是最小化簇内平方距离和 $J(z,c)=\sum_{i=1}^N\|x_i-c_{z_i}\|_2^2$（算法伪代码见上）：交替执行 **① 最近中心分配** 与 **② 簇内均值更新**（空簇需重置），直至分组不再改变。

- **为何收敛**：分配步选最近中心、更新步取簇均值（恰好唯一最小化该簇平方距离和），两步都使 $J\ge 0$ 单调不增。由于 $N$ 个点分 $k$ 簇的划分总数有限（至多 $k^N$ 种，配合固定平局规则防循环），算法必在有限步内停止并收敛到局部极小解。
- **如何近似寻找全局最优质心**：最小化 $J$ 是非凸 NP 难问题，单次运行易陷入劣质局部最优。实践上可通过**多次独立随机初始化**（或先用 **k-means++** 依距离平方按概率分散选出初始中心）多次运行，并选取最终目标值 $J$ 最小的那组划分与质心作为全局最优解的近似（但有限次重启不保证必得真正全局最优）。 **依据：** [Lab4](../Exercises/Lab4/Lab4_zh.ipynb) · [Lab5](../Exercises/Lab5/Lab5_zh.ipynb)。

b) We are interested about a soft k-means that would use a probabilistic datapoint-to-cluster assignment (similar to Gaussian Mixture Modeling). Propose a way to define this probabilistic assignment, give an updated pseudocode for this case, and argue whether or not this would converge. 希望构造一种软 k-means，采用数据点到簇的概率分配方式（类似高斯混合模型）。提出定义这种概率分配的方法，给出更新后的伪代码，并论证它是否收敛。\
**Réponse (FR) :** Une définition classique associe à chaque point $x_i$ un vecteur de probabilités d’appartenance (responsabilités) $r_{ij}\in[0,1]$ ($\sum_{j=1}^k r_{ij}=1$) via une fonction **softmax** de paramètre de température $\tau>0$ :
$$r_{ij}=\frac{\exp\!\big(-\|x_i-c_j\|_2^2/\tau\big)}{\sum_{\ell=1}^k \exp\!\big(-\|x_i-c_\ell\|_2^2/\tau\big)}.$$
Cela revient à minimiser l’objectif régularisé par l’entropie $F(r,c)=\sum_{i=1}^N\sum_{j=1}^k r_{ij}\|x_i-c_j\|_2^2+\tau\sum_{i=1}^N\sum_{j=1}^k r_{ij}\log r_{ij}$, qui s’identifie à l’algorithme **EM** pour un mélange gaussien (GMM) à poids égaux et covariance sphérique fixée $\sigma^2 I$ avec $\tau=2\sigma^2$.

```text
Entrée : données X = {x_1,...,x_N}, nombre de clusters k, température tau > 0
Initialiser k centres c_1, ..., c_k
Répéter :
  1. Affectation souple (E-step) : pour i = 1..N, j = 1..k :
       r_{ij} <- exp(-||x_i - c_j||^2 / tau) / somme_{l=1..k} exp(-||x_i - c_l||^2 / tau)
  2. Mise à jour (M-step) : pour j = 1..k :
       c_j <- (somme_{i=1..N} r_{ij} x_i) / (somme_{i=1..N} r_{ij})
Jusqu’à stabilisation des centres (ou |Delta F| < epsilon)
```

- **Convergence :** l’étape 1 minimise exactement $F(r,c)$ par rapport à $r$ (à $c$ fixé) et l’étape 2 minimise exactement $F(r,c)$ par rapport à $c$ (à $r$ fixé). Comme $F$ est monotone décroissant à chaque étape et minoré ($F(r,c)\ge -N\tau\log k$), la suite des valeurs de l’objectif **converge** vers un point stationnaire (minimum local). **答案（中文）：** 类比高斯混合模型（GMM），可引入带温度参数 $\tau>0$ 的 **softmax** 概率分配（责任度）$r_{ij}\in[0,1]$（满足 $\sum_j r_{ij}=1$）：
$$r_{ij}=\frac{\exp(-\|x_i-c_j\|_2^2/\tau)}{\sum_{\ell=1}^k \exp(-\|x_i-c_\ell\|_2^2/\tau)}.$$
这对应最小化熵正则化目标函数 $F(r,c)=\sum_{i,j}r_{ij}\|x_i-c_j\|_2^2+\tau\sum_{i,j}r_{ij}\log r_{ij}$，并且恰好等价于等混合权、固定球形协方差 $\sigma^2 I$（取 $\tau=2\sigma^2$）的 GMM **EM 算法**。更新伪代码为交替执行：**① 软分配（E 步）**按上式计算 $r_{ij}$；**② 加权更新（M 步）**置 $c_j=\frac{\sum_i r_{ij}x_i}{\sum_i r_{ij}}$，直至中心收敛或 $F$ 变化小于阈值。

- **收敛性论证**：E 步与 M 步分别在固定对方变量时严格最小化同一个目标函数 $F(r,c)$，故 $F$ 每步单调不增；由于概率熵有界，存在下界 $F(r,c)\ge -N\tau\log k$，因此目标函数值必然**收敛**至某个局部极小/驻点。 **依据：** [Lab4](../Exercises/Lab4/Lab4_zh.ipynb) · [Lab5](../Exercises/Lab5/Lab5_zh.ipynb)。

c) If we initialize k-means with the solution of soft k-means, would the clusters change or not, and why? Give elements of comparison for the two aforementioned hard and soft k-means approaches? Which are the cases where the latter is better to be used? 若以软 k-means 的解初始化 k-means，簇会改变吗？为什么？比较上述硬 k-means 与软 k-means，并说明哪些情况下更适合采用后者。\
**Réponse (FR) :**
1. **Changement de clusters :** **en général oui.** Dans la solution de soft k-means, chaque centre est une **moyenne pondérée** de tous les points ($0<r_{ij}<1$), influencée par les points frontaliers des autres groupes. Lorsqu’on démarre le k-means dur avec ces centres, chaque point est réaffecté exclusivement au centre le plus proche ($r_{ij}\in\{0,1\}$) : la moyenne arithmétique de ces groupes durs diffère généralement de la moyenne pondérée précédente, ce qui déplace les centres et modifie les frontières (sauf cas limite où $\tau\to 0^+$ ou clusters très séparés avec poids déjà quasi binaires).
2. **Comparaison :**
   - *K-means dur* produit une partition nette, est plus rapide (pas d’exponentielles ni de matrice $N\times k$ de responsabilités) et ne requiert pas de régler $\tau$.
   - *Soft k-means* fournit des **degrés d’appartenance probabilistes** $r_{ij}$ mesurant l’incertitude aux frontières et possède un objectif plus lisse, mais coûte plus cher, exige le choix de $\tau$ et suppose toujours des clusters isotropes sous cette forme (contrairement à un GMM complet à covariances libres). Aucun des deux n’est intrinsèquement robuste aux outliers.
3. **Quand préférer le soft k-means :** lorsque les clusters **se chevauchent** (*overlapping*), lorsque les frontières sont ambiguës, ou lorsque l’application nécessite de quantifier l’incertitude d’appartenance plutôt que d’imposer une décision binaire stricte. **答案（中文）：**
1. **簇是否会改变**：**通常会改变。** 软 k-means 的收敛中心是全体样本以 $r_{ij}\in(0,1)$ 为权的**加权均值**（受跨界样本拉动）。将其作为硬 k-means 初值后，硬分配强行把每个点只归给最近中心（权重变为 $0/1$），随后计算的硬簇均值一般不再等于原来的软加权均值，因此中心发生偏移，边界点的归属也随之改变（仅当 $\tau\to 0^+$ 或各簇分离极远、权重原本就接近 $0/1$ 时才保持不变）。
2. **硬 vs 软 k-means 对比**：硬 k-means 输出非此即彼的清晰划分，无需保存 $N\times k$ 权重矩阵、计算更快且不需调温度 $\tau$；软 k-means 目标更光滑并能输出样本的**不确定度 / 归属概率**，但计算更慢且引入超参数 $\tau$，标准形式仍隐含球形等大簇假设（处理椭球簇需用自由协方差 GMM）；两者本身都不抗离群点。
3. **更适合采用软 k-means 的场景**：**簇之间存在重叠**、大量样本处于模糊边界地带，或下游决策需要利用概率成员度（而非生硬的硬切分）时。 **依据：** [Lab4](../Exercises/Lab4/Lab4_zh.ipynb) · [Lab5](../Exercises/Lab5/Lab5_zh.ipynb)。

d) Describe a procedure that would use a bootstrap approach, i.e. multiple randomized k-means solutions, to compute an outlier score for each datapoint. Discuss its properties in perspective with Isolation Forest. 描述一种利用 bootstrap 思路、即多个随机化 k-means 解，为每个数据点计算离群分数的流程。将它与 Isolation Forest 对照，讨论其性质。\
**Réponse (FR) :**
**Procédure Bootstrap + $k$-means :**
Pour $b = 1, \dots, B$ :
1. Générer un échantillon bootstrap $X^{(b)}$ de taille $N$ par tirage avec remise dans $X$, et ajuster un $k$-means (avec initialisation aléatoire / k-means++) pour obtenir $k$ centres $\{c_{b,j}\}_{j=1}^k$ et éventuellement l’écart-type interne de chaque cluster $\sigma_{b,j}$.
2. Pour chaque point $x_i\in X$ (idéalement évalué *out-of-bag* sur les modèles $b$ qui n’ont pas tiré $x_i$, afin de limiter l’effet de masquage), calculer la distance au centre le plus proche, éventuellement normalisée par la dispersion locale du cluster :
   $$s_b(x_i) = \min_{j=1..k} \frac{\|x_i - c_{b,j}\|_2}{\sigma_{b,j} + \varepsilon} \quad (\text{ou simplement } \min_j \|x_i - c_{b,j}\|_2).$$
3. Agréger sur les réplicats par moyenne ou médiane : $S(x_i)=\operatorname{moyenne}_b\,s_b(x_i)$. Plus $S(x_i)$ est grand, plus $x_i$ est suspect d’être un *outlier* (seuil choisi sur validation).

**Comparaison avec *Isolation Forest* (iForest) :**
- **Hypothèses géométriques :** Bootstrap-$k$-means mesure une **distance à des prototypes** : il suppose implicitement des groupes compacts/sphériques, dépend fortement du choix de $k$ et de la normalisation des variables, et peut subir un effet de *masquage* si un groupe d’outliers forme son propre centre (ou pénaliser à tort un petit cluster normal isolé). À l’inverse, **Isolation Forest** repose sur des coupures aléatoires parallèles aux axes (sans hypothèse de forme ni paramètre $k$) et score chaque point via sa **profondeur moyenne d’isolement** : les points rares et isolés sont séparés en très peu de coupes.
- **Passation à l’échelle et précision :** Isolation Forest gère naturellement des densités multiples et s’exécute très rapidement en sous-échantillonnant par arbre, alors que Bootstrap-$k$-means stabilise la variance d’un seul $k$-means mais reste tributaire de la métrique euclidienne et du nombre de clusters $k$. **答案（中文）：**
**基于 Bootstrap + 随机化 $k$-means 的离群评分流程：**
重复 $b=1,\dots,B$ 轮：① 从原数据有放回自助采样（Bootstrap）得到 $X^{(b)}$，配合随机初始化训练一次 $k$-means，得到 $k$ 个中心 $\{c_{b,j}\}_{j=1}^k$ 及对应簇内离散尺度 $\sigma_{b,j}$；② 对每个样本 $x_i$（理想情况下只在该点未入袋 *out-of-bag* 的模型上计算，以减少异常点自成一簇的影响），计算其到最近簇中心的**簇尺度归一化距离**（也可简化为欧氏距离，但后者对密度差异敏感）：
$$s_b(x_i)=\min_{j=1..k}\frac{\|x_i - c_{b,j}\|_2}{\sigma_{b,j} + \varepsilon};$$
③ 将 $B$ 轮分数取平均或中位数作为最终离群分数 $S(x_i)$，分数越高越可能是异常点（再由验证集定阈值）。

**与 Isolation Forest 的性质对比：**
- **几何假设与超参数**：Bootstrap-$k$-means 本质是**基于原型的距离度量**，隐含簇呈球形且由中心良好代表的前提，结果受簇数 $k$、特征量纲与局部密度影响较大（若一群异常点在采样中占住一个中心还会发生漏检，而稀少但正常的孤立小簇也可能被误判）。**Isolation Forest** 则用随机轴对齐超平面递归切分数据，以**平均隔离路径长度**作为异常指标（越易被快速隔离越异常），**无需预设 $k$**，也不依赖球形簇假设。
- **密度适应与效率**：Bootstrap 虽降低了单次 $k$-means 的随机不稳定性，但仍受限于 $k$-means 本身的度量与形状假设；Isolation Forest 配合子采样对多密度簇、高维数据和大样本都具有很好的效率与适应性（但因轴对齐切分，在存在强倾斜相关性时也可能不如旋转或基于距离的方法敏锐）。 **依据：** [Lab3](../Exercises/Lab3/Lab3_zh.ipynb) · [Lab4](../Exercises/Lab4/Lab4_zh.ipynb) · [作业二](../Exercises/Assignment2/Assignments2_zh.ipynb)。
