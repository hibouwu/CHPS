# Évaluation des performances : simulation et mesure 性能评估：仿真与测量

[课程入口](../README.md) · [合并校订 PDF（45 页）](45_edp.pdf) · [法语阅读版](45_edp.md)

2026-11-02 同步：以 [2026 年教师原版（43 页）](<Originals/45_edp_2026.pdf>) 为基础，保留来自 2020 年旧版第 20–21 页的模拟器介绍；旧版原 PDF 当前已不在本目录。主 PDF 为合并校订阅读版；下文教师课件页码均指合并后的 45 页版。既有统计校注与中文补充保留，核对依据见[审校说明](../审校说明.md)。

格式说明：法语在前、中文在后，同一行以空格隔开，撇号统一为 '。法语优先依据对应课件及法语讲义，必要时沿用已有订正；中文补充、校注和附录中没有对应原文的部分配以法语译写，仍属补充材料。

## 1 Généralités 概论

### 1.1 Simulation 仿真

#### 1.1.1 But 目的 (But)

Observer le comportement d'un système dans diverses configurations et applications, même s'il n'existe pas encore au moment de l'évaluation. 能够在任何条件 (配置) 下观察任何系统的行为, 即使该系统在评估时尚不存在, 代表各种应用背景。

#### 1.1.2 Intérêts 优势

- Pas besoin de construire le système réel. 无需构建真实系统
- Tests contrôlables et répétables. 可以进行可控且可重复的测试
- Grande variété de scénarios de test. 测试场景无限制
- Résultats reproductibles par d'autres utilisateurs. 其他用户可以重现结果

#### 1.1.3 Exemples d'utilisation 应用示例

La simulation peut répondre aux questions suivantes : 仿真可以回答如下问题:

- Quel algorithme de placement convient le mieux à une application sur une architecture donnée ? 在给定架构上, 哪种放置算法 (algorithme de placement) 对某个应用更好?
- Quelle stratégie de cache convient le mieux à cette application ? 哪种缓存策略 (stratégie de cache) 对某个应用更好?
- Quels sont les effets des stratégies de partage de ressources sur l'équité et le débit ? 与某些共享资源管理策略相关的公平性 (équité) 和吞吐量 (débit) 特性是什么?

#### 1.1.4 Simulation et mesure 仿真与测量对比 (Simulation Vs. Mesure)

La mesure représente précisément le système réel, mais soulève des questions : 测量 (mesure).... 在精确性和真实系统代表性方面很好, 但是....

- Quelle part du résultat vient de dysfonctionnements ou de surcharges du système réel ? 结果中真实的系统故障/过载 (dysfonctionnements/surcharge) 占多大比例?
- Les expériences et résultats restent liés à la plateforme étudiée. 实验及其结果仅限于所分析的平台
- L'extrapolation est possible mais difficile à justifier. 外推是可能的, 但很难令人信服
- La reproduction par d'autres utilisateurs est difficile. 其他用户很难重现结果

### 1.2 Simulation : définition et classification 仿真: 定义与分类

#### 1.2.1 Définition 定义

Prévoir différents aspects du comportement d'un système en construisant une imitation. 通过创建模仿来尝试预测任何系统行为的不同方面。

#### 1.2.2 Classification 分类

Types de simulation : 存在不同类型的仿真:

- **Émulation 仿效** : reproduire le fonctionnement observable d'un système pour faire fonctionner des programmes ou interactions prévus pour lui. 重现目标系统的可观察行为，使面向它的程序或交互能够运行。
- **Simulation statique 静态仿真** : estimer un résultat sans suivre explicitement une chronologie d'états, par exemple une intégrale par Monte Carlo. 不显式推进系统状态的时间线，而是估计一个结果，例如用 Monte Carlo 计算积分。
- **Simulation à événements discrets 离散事件仿真** : faire évoluer l'état à chaque événement daté, par exemple une arrivée ou une fin de service. 根据带时间戳的事件推进系统状态，例如请求到达或服务完成。

### 1.3 Émulation et simulation statique 仿效与静态仿真

#### 1.3.1 Émulation 仿效

Imiter le comportement d'un système par un logiciel exécuté sur un autre système ; on emploie ici « 仿效 » pour distinguer l'émulation de la simulation au sens général. 通过在另一系统上运行的软件重现目标系统的行为；这里将 émulation 译为“仿效”，以区别于一般意义上的仿真。

Remarque : l'émulation peut fournir des résultats précis, au prix d'un surcoût important. 注意: 仿真产生相当精确的结果, 但作为代价会产生很大的开销 (overhead)。

#### 1.3.2 Simulation statique 静态仿真

Le cours prend Monte Carlo comme exemple de simulation sans évolution temporelle explicite. On peut arrêter selon le budget ou la précision, sans atteindre un équilibre dynamique. 本课以蒙特卡洛方法为例，讨论不显式描述系统随时间演化的静态仿真。可以按计算预算或估计精度停止；不要求达到动态系统的平衡状态。

## 2 Simulation à événements discrets 离散事件仿真

### 2.1 Définition de la simulation à événements discrets 离散事件仿真的定义

Représenter le système par des événements, leurs transitions et les fonctions associées. Son état évolue selon le temps et les événements externes ou générés par la simulation. 通过事件 (événements)、与之相关的转换 (transitions) 以及每当这些事件发生并执行相关转换时要执行的特定函数来表示系统。因此, 这是对功能模式的模仿, 根据时间和外部事件或仿真生成的事件进行状态改变。

### 2.2 Simulation distribuée 分布式仿真

L'exécution est répartie entre plusieurs sites qui coopèrent et communiquent selon un workflow et en respectant la causalité. 主要与仿真执行的方式有关: 分布式的, 利用不同站点的资源, 协作和通信, 同时遵守已建立的工作流模式 (schéma Workflow) 和因果关系原则 (principes de causalité)。

### 2.3 Exemple : simulation de CPU 仿真示例:CPU 仿真

Trois possibilités, par abstraction décroissante : 三种可能的仿真, 抽象级别递减:

- Simulation mathématique : flux macroscopiques de tâches et composants, à gros grain. 数学仿真 (Simulation mathématique): 任务和组件 (管道)(pipe) 的宏观流动, 采用粗粒度数学仿真
- Simulation à événements discrets : suivre les événements du processeur, éventuellement au niveau cycle si le modèle le prévoit. 离散事件仿真：跟踪处理器事件；模型可以细化到周期级，但“离散事件”本身不保证周期精确。
- Émulation : reproduire le comportement d'un CPU pour exécuter du code prévu pour lui ; la virtualisation est une technique distincte, même si elles peuvent être combinées. 仿效：重现目标 CPU 的行为以运行面向它的代码；虚拟化是另一类技术，二者可以结合使用。

### 2.4 Exemple : simulation de réseau 仿真示例: 通信网络仿真

Trois possibilités, par abstraction décroissante : 三种可能的仿真, 抽象级别递减:

- Simulation mathématique : flux macroscopiques et composants réseau à gros grain. 数学仿真: 网络任务和组件 (管道) 的宏观流动, 采用粗粒度数学仿真
- Simulation à événements discrets : suivi des paquets dans les composants du réseau. 离散事件仿真: 数据包级别的仿真, 通过网络不同组件进行微观跟踪
- Émulation : trafic réel traversant un réseau émulé. 仿效：让实际流量通过被仿效的网络环境。

### 2.5 Terminologie 术语

#### 2.5.1 Termes de base 基本术语

- Variables d'état : décrivent le système ; sauvegarder l'état permet de reprendre la simulation, par exemple taille de file et progression des tâches. 状态变量 (Variables d'état): 定义系统状态的变量, 保存的值允许停止的仿真稍后重新启动 (队列大小、任务消耗进度等)
- Événement : changement d'état, comme arrivée ou fin de job et panne d'un composant. 事件 (Événement): 系统状态的改变 (作业到达或完成、组件故障等)
- Temps continu ou discret : nature du domaine temporel où l'état est défini. 连续时间 (Temps continu) 与离散时间 (temps discret): 指示系统状态是否始终定义
- État continu ou discret : nature des valeurs des variables, par exemple temps, effectifs ou tailles. 连续状态 (État continu) 与离散状态 (état discret): 指示系统变量是连续的 (时间) 还是离散的(出现次数、大小)

### 2.6 Structure du simulateur à événements discrets 离散事件仿真器的结构

Modules nécessaires : 离散事件仿真器必须包含以下模块:

1. **Ordonnanceur d'événements 事件调度器** : conserver les événements futurs et choisir le prochain à traiter. 维护未来事件列表，选择下一个要处理的事件。

2. **Horloge globale $t_{\mathrm{sim}}$ 全局仿真时钟 $t_{\mathrm{sim}}$** : représenter la date dans le système simulé, distincte de la durée réelle d'exécution du simulateur. 表示被模拟系统中的当前时间，区别于仿真程序在真实机器上已经运行的时间。

3. **Procédures de traitement des événements 事件处理过程** : appliquer les changements d'état associés à l'événement choisi. 执行所选事件对应的状态更新。

4. **Mécanismes de génération d'événements 事件生成机制** : produire de nouveaux événements à partir de traces ou de lois de probabilité. 根据轨迹或概率分布生成后续事件。

5. **Enregistrement et filtrage des données 数据记录与过滤** : accumuler les compteurs et durées nécessaires aux indicateurs. 保存计算指标所需的事件计数和时间量。

#### 2.6.1 Ordonnanceur des événements 事件调度器 (L'ordonnanceur des événements)

Au cœur du simulateur, il doit : 调度器构成离散事件仿真器的核心, 其功能是:

- Maintenir les événements non traités dans un ordre temporel global ; 按全局时间顺序维护事件列表 (未处理的)
- Retirer l'événement approprié et le transmettre à sa procédure de traitement ; 通过从列表中删除适当的事件并将其传送到与之关联的处理过程来处理该事件
- Insérer les nouveaux événements dans l'ordre temporel et gérer leur ordonnancement ou suppression ; 在尊重列表时间顺序的前提下插入新事件, 并确保调度或删除事件的其他任务
- Coordonner l'horloge globale. 确保与全局时钟的协调

#### 2.6.2 Horloge globale 全局时钟 (L'horloge globale)

Référence temporelle mise à jour par l'ordonnanceur selon deux approches : 仿真的时间参考, 由调度器根据两种方法更新:

##### 1. Incrémentation par pas fixe 固定步长递增

Avancer de $\Delta t>0$ selon $t_{\mathrm{sim}}\gets t_{\mathrm{sim}}+\Delta t$, rechercher les événements prêts et les traiter. $\Delta t$ règle la finesse temporelle et le nombre de pas. 每次按固定步长 $\Delta t>0$ 更新时钟：$t_{\mathrm{sim}}\gets t_{\mathrm{sim}}+\Delta t$，再检查并处理就绪事件；步长影响时间分辨能力和更新次数。

##### 2. Incrémentation événementielle 事件驱动递增

Avancer directement à la date $t_e$ du prochain événement : $t_{\mathrm{sim}}\gets t_e$ ; les pas sont non uniformes et les périodes sans événement sont sautées. 时钟直接跳到下一事件的时刻 $t_e$，即 $t_{\mathrm{sim}}\gets t_e$；步长可以不同，不必逐步扫描没有事件的时间段。

Si plusieurs événements ont la même date, définir une règle de départage cohérente avec le modèle ; le tri par date ne détermine pas à lui seul leur ordre. 多个事件时间戳相同时，应规定符合模型因果关系的处理顺序，仅按时间排序不足以解决并列事件的先后问题。

#### 2.6.3 Traitement des événements 事件处理

- Chaque type d'événement possède une procédure simulant son effet sur le système. 每种类型的事件都与一个处理过程相关联, 该过程模拟当该事件发生时系统的行为
- La procédure peut modifier l'état et générer des événements ajoutés à la liste. 每个处理过程可以改变系统状态并生成其他事件, 这些事件将添加到调度器维护的列表中
- Le traitement dépend de la nature du système simulé. 实现的处理取决于被仿真系统的性质

#### 2.6.4 Génération des événements 事件生成

Deux grandes classes selon la technique de génération : 事件生成器根据所使用的生成技术进行分类。两个主要类别:

1. Orientée trace : événements observés sur un système réel, représentatifs mais volumineux, avec un seul point de validation et des biais possibles de collecte. 面向轨迹的类 (Classe orientée trace): 在真实系统上观察到的事件序列。具有代表性但体积非常大, 单一验证点, 收集引入偏差

2. Orientée loi de probabilité : événements de forme similaire, générés selon des distributions au début ou pendant la simulation. 面向概率分布的类 (Classe orientée loi de probabilité): 形式相似但由仿真器根据概率分布生成 (在开始时或伴随仿真过程)

#### 2.6.5 Enregistrement des données 数据记录

Maintenir variables d'état, compteurs d'événements et mesures temporelles pour produire statistiques et synthèses. 维护状态变量, 即事件计数器和时间测量变量, 以进行统计并总结结果。

Structures de données : 结构 (Structures):

- Listes ordonnées ou doublement chaînées 有序列表或双向链表 (Listes ordonnées ou doublement chaînées)
- Arbres 树 (Arbres)

Ces structures accélèrent insertion, recherche et modification, malgré des accès mémoire non uniformes. 这些是最常用的结构, 用于加速操作 (插入、查询、修改), 即使内存访问不均匀。

#### 2.6.6 Validation 验证

La validation évalue la précision fonctionnelle du modèle en demandant : 验证确定功能模型的精度水平, 回答以下问题:

- Le modèle capture-t-il les fonctionnalités essentielles ? 模型是否捕获了系统的基本功能?
- Les hypothèses sont-elles raisonnables ? 假设是否合理?
- Les entrées représentent-elles des cas réels ? 输入数据是否代表真实情况?
- Les résultats sont-ils raisonnables ? 获得的结果是否合理?
- Peut-on les expliquer ? 这些结果是否可以解释?

#### 2.6.7 Remarques sur la construction du simulateur 关于仿真器构建的注意事项

Bonnes pratiques de construction : 关于仿真器的构建:

- Programmation structurée, modularité, documentation et vérification des erreurs. 遵循良好实践: 结构化编程、模块化设计、文档、错误检查等
- Exécution pas à pas pour vérifier les passages par les états du système. 逐步执行以验证通过被仿真系统的所有状态
- Vérification de la cohérence et de la stabilité. 验证仿真器的一致性和稳定性
- Attention particulière aux cas limites. 强调特殊情况 (边界条件)(corner conditions) 的验证

### 2.7 Simulateurs populaires 流行的仿真器

> Complément conservé des pages 20–21 de l'ancienne version, supprimées du cours original 2026. 保留旧版第 20–21 页的补充内容；2026 年教师原版已删除这两页。

#### 2.7.1 Simulateurs de microprocesseurs 微处理器仿真器 (Simulateur de Microprocesseur)

De nombreux simulateurs standard au niveau cycle : 众多周期级标准仿真器:

http://pages.cs.wisc.edu/~arch/www/tools.html

#### 2.7.2 SimGrid

SimGrid : outil INRIA pour environnements distribués et hétérogènes, des réseaux de stations aux grilles de calcul ; adresse historique : http://simgrid.gforge.inria.fr/ 用于分布式和异构环境 (从工作站网络到计算网格) 的工具, 由 INRIA 开发:http://simgrid.gforge.inria.fr/

#### 2.7.3 Simulateurs de stockage 存储系统仿真器 (Simulateur de système de stockage)

Pionnier développé et maintenu au Parallel Data Lab de CMU : 先驱, 由并行数据实验室 (CMU) 开发/维护:

http://www.pdl.cmu.edu/DiskSim/

Simulateur de l'équipe : OGSSim, Li-PaRAD/UVSQ et CEA-DAM. 我们的:OGSSim. Li-PaRAD,UVSQ / CEA-DAM

## 3 Simulation par Monte Carlo 蒙特卡洛仿真

### 3.1 Historique 历史

N. Metropolis et S. Ulam [1947–1949] utilisent un procédé aléatoire pour un calcul numérique ; le nom évoque les jeux de hasard de Monte Carlo. N. Metropolis 和 S. Ulam [1947-1949], 使用随机过程来计算数值。因此暗指在蒙特卡洛 (Monte Carlo)进行的机会游戏。

### 3.2 Définition 定义

Évaluer itérativement un modèle déterministe avec des ensembles de variables aléatoires en entrée. 使用随机变量集作为输入, 迭代评估确定性模型的方法。

Un modèle déterministe redonne les mêmes résultats avec les mêmes entrées dans les mêmes conditions. 确定性模型 (modèle déterministe) 在相同条件下、使用相同输入重新计算多次时, 会给出相同的结果。

### 3.3 Applications 应用

Intégration multidimensionnelle, surfaces et volumes, risque financier, rentabilité et solvabilité en banque et assurance, dynamique moléculaire ou mouvements de populations. 蒙特卡洛方法的应用领域包括: 多维积分计算 (表面、体积)、金融风险评估、银行和保险部门的盈利能力或偿付能力、分子动力学或人口运动研究等。

Remarque : Monte Carlo nécessite de nombreuses évaluations, facilitées par le calcul parallèle. 注意 (Remarque): 蒙特卡洛方法需要非常大量的评估, 并行计算促进了这项任务。

### 3.4 Étapes de Monte Carlo 蒙特卡洛的步骤

Étapes d'une simulation Monte Carlo : 执行蒙特卡洛仿真遵循的不同步骤:

Notations : $k$ est le nombre de paramètres d'entrée, $i$ le numéro du tirage et $n$ le nombre de tirages ; $X_{ij}$ est la valeur du paramètre $j$ au tirage $i$, et $Y_i=f(X_{i1},\ldots,X_{ik})$ le résultat. 符号说明：$k$ 为输入参数个数，$i$ 为抽样编号，$n$ 为抽样总数；$X_{ij}$ 是第 $i$ 次抽样中第 $j$ 个参数的值，$Y_i=f(X_{i1},\ldots,X_{ik})$ 是对应输出。

1. Créer un modèle des paramètres $(X_1,X_2,\ldots,X_k)$. 为参数 $( X _{1} , X _{2} , . . . , X _{k} )$ 创建模型

2. Générer des valeurs aléatoires $(X_{i1},X_{i2},\ldots,X_{ik})$. 生成一组随机值 $( X _{i 1} , X _{i 2} , . . . , X _{i k} )$

3. Évaluer le modèle et stocker le résultat dans $Y_i$. 评估模型并将结果存储在 $Y_i$ 中

4. Répéter 2 et 3 pour i = 1..n, avec n suffisamment grand pour mobiliser la loi des grands nombres. 对 i = 1..n(n 非常大, 以使用大数定律) 重复步骤 2 和 3

5. Analyser avec histogrammes, moyennes, variances et intervalles de confiance. 使用直方图、平均值和方差、置信区间等分析结果

Pour des sorties indépendantes de même loi et de variance finie, la moyenne $\bar Y$ estime $\mathbb E[Y]$ et son erreur standard est estimée par $s_Y/\sqrt n$, où $s_Y$ est l'écart type empirique des sorties. Les formules d'intervalle sont présentées en §5.4–5.5. 对独立同分布、方差有限的输出，样本均值 $\bar Y$ 估计 $\mathbb E[Y]$，其标准误差估计为 $s_Y/\sqrt n$，其中 $s_Y$ 是输出样本的标准差；置信区间公式留到 §5.4–5.5。

### 3.5 Exemple Monte Carlo : calcul de $\pi$ 蒙特卡洛示例：计算 $\pi$

Tirer $N$ points indépendants et uniformes dans $[0,1]^2$ ; $N_B$ compte les points dans le quart de disque et $\widehat\pi$ est l'estimation de $\pi$. 在单位正方形 $[0,1]^2$ 中独立均匀抽取 $N$ 个点；$N_B$ 表示命中四分之一圆的点数，$\widehat\pi$ 表示对 $\pi$ 的估计值：

1. L'aire totale du disque vaut $\pi$ et celle du quart de disque dans le carré vaut $\pi/4$. 单位圆总面积为 $\pi$，正方形内的四分之一圆面积为 $\pi/4$。
2. Tirer indépendamment $x_{i1},x_{i2}\sim U(0,1)$ à chaque essai. 对每次抽样，独立生成 $x_{i1},x_{i2}\sim U(0,1)$。
3. Si $x_{i1}^2+x_{i2}^2<1$, incrémenter $N_B$ ; incrémenter le nombre total d'essais dans tous les cas. 若 $x_{i1}^2+x_{i2}^2<1$，将圆内点数 $N_B$ 加 1；无论是否命中，总抽样数都加 1。
4. Après $N$ tirages, utiliser : 抽样 $N$ 次后，使用：

$$
\frac{\pi}{4}\approx\frac{N_B}{N},\qquad \widehat\pi=4\frac{N_B}{N}.
$$

> Précision : la transcription avait perdu deux dénominateurs 4 et mal reconnu « cercle » ; ils sont vérifiables à la page 5 de l'ancien PDF chinois. $N_B$ compte bien les points dans le quart de disque. 校注：提取稿丢失了两处 $\pi/4$ 的分母，并将“圆”识别成数学符号；原中文 PDF 第 5 页能核对分母。这里也明确了 $N_B$ 是命中四分之一圆的点数。

## 4 Mesure 测量

### 4.1 Introduction à la mesure 测量: 引言

#### 4.1.1 Quoi mesurer ? 测量什么?

Nombre d'événements, durée entre événements, taille nécessaire au codage de l'information, etc. 事件出现次数、两个事件之间的持续时间、包含信息的大小等。

#### 4.1.2 Définition 定义

La mesure suit le fonctionnement du système par : 测量用于通过以下方式跟踪系统的运行:

1. Observation et collecte : prendre les mesures et rassembler l'information. 观察和收集 (L'observation et la collecte): 进行测量并收集由此产生的信息

2. Analyse : traiter statistiquement les données. 分析 (L'analyse): 使用统计技术处理收集的数据

3. Présentation : afficher les résultats sous des formes adaptées. 呈现 (La présentation): 以各种适当的形式显示结果

### 4.2 Terminologie de la mesure 测量: 术语

#### 4.2.1 Termes usuels 常用术语

- Événement : tout changement d'état, par exemple arrivée d'une requête ou d'un paquet et accès mémoire. 事件 (Événement): 系统状态的任何改变 (例如请求/数据包到达、内存访问等)
- Trace : liste ou journal d'événements. 轨迹 (Trace): 事件的列表或日志
- Surcoût : consommation supplémentaire de ressources. 开销 (Surcharge, overhead): 指示系统额外消耗的测量
- Résolution : niveau de détail de l'observation. 分辨率 (Résolution): 观察的详细程度
- Taille en entrée : nombre de bits pour coder un événement. 输入大小 (Taille en entrée): 编码事件的位数
- Portabilité : modifications nécessaires pour implémenter ou exécuter l'outil. 可移植性 (Portabilité)：为实现或执行测量工具需要进行的修改量

### 4.3 Phase d'observation et de collecte 观察/收集阶段 (Phase d'observation/collecte)

#### 4.3.1 Mécanismes d'observation 观察机制

1. Espionnage implicite : 隐式监视 (“Espionnage implicite”, Implicit spying):

Observer sans interférer avec le fonctionnement ; dans ce modèle idéal, sans impact de performance, en filtrant l'information utile. 在不干扰系统运行的情况下观察系统。对性能没有影响, 但使用过滤器保留有用信息。

2. Instrumentation explicite : 显式插桩 (Instrumentation explicite):

Insérer traceurs et sondes, par exemple au moyen de compteurs matériels. 使用硬件计数器等合并跟踪器、探针。

#### 4.3.2 Classes d'observation et de collecte 观察/收集类别

- En ligne : analyser pendant le monitoring. 在线 (On-line): 在监控期间分析结果
- Par lots : collecter d'abord, analyser ensuite. 批处理 (batch): 收集数据但分析推迟

#### 4.3.3 Stratégies de collecte 收集策略

- Événementielle : enregistrer à chaque événement. 事件驱动 (Event-driven): 每次事件出现时记录信息
- Trace : enregistrer aussi l'état, avec un surcoût en temps et en espace. 轨迹 (Trace): 还记录系统状态。因此在时间和空间上产生开销
- Échantillonnage : enregistrer périodiquement pour ajuster le surcoût. 采样 (Échantillonnage): 定期记录信息, 因此重新调整开销
- Mesure indirecte : déduire la métrique inaccessible à partir d'une autre métrique mesurable. 间接测量 (Mesure indirecte): 当要测量的度量不能直接测量时使用。确定另一个可测量的度量并推导/导出感兴趣的度量

### 4.4 Outils simples de collecte 简单的收集工具

Exemples : 示例:

Outre les instruments et logiciels spécialisés, certains outils simples restent efficaces et courants. 除了测量硬件和专用软件外, 还有一些简单但有效的工具, 经常用于测量。

Exemples d'outils : 我们列举:

`time`, `gettimeofday` (temps exprimé en microsecondes), `top`, `gprof`, etc. L'unité d'affichage n'est pas la résolution réelle de l'horloge. `time`、`gettimeofday`（以微秒表示时间）、`top`、`gprof` 等；表示单位不等于实际时钟分辨率。

### 4.5 Phase d'analyse 分析阶段

L'analyse dépend du contexte et des métriques ; elle est cruciale avec des mesures volumineuses, détaillées et bruitées. 任何评估的目的, 取决于上下文和度量。对于测量来说更重要, 因为收集的数据量大、细节丰富且有噪声。

#### 4.5.1 Analyse de variance, ANOVA 方差分析 (ANalysis Of VAriance, ANOVA)

Les répétitions peuvent présenter de grands écarts dus à la variabilité d'exécution ou à des erreurs de mesure. 在系统上进行测量时, 收集的数据呈现出可能很大的偏差, 这些偏差可能仅与测量的重复有关, 或者表示真实的测量误差。

L'ANOVA décompose la variation en effets entre alternatives et résidu intragroupe ; le résidu peut inclure une variabilité inexpliquée, pas seulement une erreur instrumentale. ANOVA 将总变异分解为方案间效应和组内残差；残差可能包含未解释的随机波动，不应全归因于测量仪器出错。

#### 4.5.2 Calcul de l'ANOVA ANOVA - 计算

Comparer $k$ alternatives, par exemple $k$ configurations, avec $n$ mesures indépendantes par alternative ; $y_{ij}$ est la mesure $i$ de l'alternative $j$, pour $i=1,\ldots,n$ et $j=1,\ldots,k$. 比较 $k$ 个备选方案（例如 $k$ 种配置），每个方案独立重复测量 $n$ 次；$y_{ij}$ 是第 $j$ 个方案的第 $i$ 次观测，总观测数为 $kn$。这里 $k$ 是方案数，$n$ 是每个方案的重复次数。

Calcul des moyennes : 计算平均值:

La moyenne du groupe $j$ est $\bar y_j$ et la moyenne globale des $kn$ observations est $\bar y$ : 第 $j$ 组的样本均值记为 $\bar y_j$，全部 $kn$ 个观测的总体样本均值记为 $\bar y$：

$$
\bar y_j=\frac1n\sum_{i=1}^n y_{ij},\qquad
\bar y=\frac1{kn}\sum_{j=1}^k\sum_{i=1}^n y_{ij}.
$$

Réécrire $y_{ij}=\bar y_j+e_{ij}$, où $e_{ij}=y_{ij}-\bar y_j$ est le résidu intragroupe. 测量可重写为 $y_{ij}=\bar y_j+e_{ij}$，其中 $e_{ij}=y_{ij}-\bar y_j$ 是相对本组均值的残差，包含组内尚未解释的波动。

La moyenne par alternative s'écrit : 按备选方案的测量平均值可以重写为:

$$
\bar{y} _{j} = \bar{y} + \alpha_{j}
$$

$\alpha_j=\bar y_j-\bar y$ est l'effet estimé de l'alternative $j$, avec $\sum_{j=1}^k\alpha_j=0$ dans ce plan équilibré. L'indice distingue cet effet du seuil de signification $\alpha$ utilisé pour le test. $\alpha_j=\bar y_j-\bar y$ 是第 $j$ 个方案的估计效应，在本节各组样本数相同的设计中有 $\sum_{j=1}^k\alpha_j=0$；带下标的 $\alpha_j$ 与后面检验的显著性水平 $\alpha$ 含义不同。

#### 4.5.3 Application de l'ANOVA ANOVA - 应用

Variation entre alternatives, somme des carrés $\mathrm{SSA}$ : elle mesure l'écart des moyennes de groupe à la moyenne globale. 组间平方和记为 $\mathrm{SSA}$，衡量各方案均值与全体样本均值之间的差异：

$$
\mathrm{SSA} = n \sum_{j = 1} ^{k} (\bar{y} _{j} - \bar{y}) ^{2}
$$

Variation résiduelle, somme des carrés $\mathrm{SSE}$ : elle mesure la dispersion des observations autour de leur propre moyenne de groupe. 组内残差平方和记为 $\mathrm{SSE}$，衡量同一方案各次观测相对本组均值的波动：

$$
\mathrm{SSE} = \sum_{j = 1} ^{k} \sum_{i = 1} ^{n} (y _{i j} - \bar{y} _{j}) ^{2}
$$

#### 4.5.4 ANOVA et test F ANOVA 和 F 检验 (F-test)

L'ANOVA à un facteur teste l'égalité des moyennes de k alternatives. Le modèle classique suppose des erreurs indépendantes, approximativement normales et de même variance. 单因素 ANOVA 检验 $k$ 个备选方案的总体均值是否相同。经典模型假设误差独立、近似正态且各组具有相同方差。

Les moyennes de carrés $S_a^2$ et $S_c^2$ divisent respectivement $\mathrm{SSA}$ et $\mathrm{SSE}$ par leurs degrés de liberté $k-1$ et $k(n-1)$ ; leur rapport est la statistique F, notée $F_{\mathrm{计算}}$ dans les formules. Plus l'écart entre groupes est grand relativement à la variation résiduelle, plus F est grand. 组间均方 $S_a^2$、组内均方 $S_c^2$ 分别由平方和除以自由度 $k-1$、$k(n-1)$ 得到；两者之比是检验统计量 $F_{\mathrm{计算}}$。组间差异相对于组内波动越大，$F$ 越大。

$$
S_a^2=\frac{\mathrm{SSA}}{k-1},\qquad
S_c^2=\frac{\mathrm{SSE}}{k(n-1)},\qquad
F_{\mathrm{计算}}=\frac{S_a^2}{S_c^2}.
$$

Lorsque 当

$$
F_{\mathrm{计算}}>F_{1-\alpha;\,k-1,\,k(n-1)}
$$

on rejette l'égalité des moyennes au niveau de signification $\alpha$. Le seuil $F_{1-\alpha;\,k-1,\,k(n-1)}$ est le quantile d'ordre $1-\alpha$ de la loi F avec ces deux degrés de liberté. 时，在显著性水平 $\alpha$ 下拒绝“各组均值相同”的原假设；$F_{1-\alpha;\,k-1,\,k(n-1)}$ 是分子、分母自由度分别为 $k-1$、$k(n-1)$ 的 F 分布的 $1-\alpha$ 分位数，即比较阈值。

> Précision : l'ancien PDF chinois p. 8 et le cours 2020 p. 34 inversaient l'inégalité ; elle est corrigée dans l'original 2026 p. 32, soit p. 34 du PDF consolidé. Le Markdown conserve la formule correcte et le PDF précise le test des moyennes. Ne pas rejeter ne prouve pas l'égalité. 校注：原中文 PDF 第 8 页与 2020 年教师旧版第 34 页将不等号方向写反；2026 年教师原版第 32 页已修正，合并校订版对应第 34 页。Markdown 保留正确公式，合并 PDF 也已修正检验均值相等的文字。未拒绝原假设不等于证明各组均值相同。

### 4.6 Phase de présentation 呈现阶段

#### 4.6.1 Paramètres du choix de présentation 呈现选择的参数

Trois paramètres à considérer selon le système : 与系统相关的选择, 但要考虑三个参数:

1. Fréquence de présentation en ligne 呈现频率 (在线)

2. Présentation hiérarchique 层次化表示 (résentation hiérarchique)

3. Points importants : seuils, événements anormaux, etc. 重要点: 阈值、异常事件等

#### 4.6.2 Outils simples et représentatifs 简单、流行和有代表性的工具

Moyennes, variance, écart type, quantiles et intervalles de confiance ; voir le cours sur les workloads. 一组简单的统计技术: 平均值、方差和标准差、分位数等 (参见工作负载课程), 以及置信区间。

## 5 Qualité de mesure 测量质量

### 5.1 Définition 定义

Quantifier erreurs et bruit pour caractériser la qualité par : 测量中的误差或噪声必须量化, 以通过以下方式确定这些测量的质量:

1. Justesse : proximité de la valeur mesurée avec la référence. 准确性 (Justesse, Accuracy): 指示测量值与标准值的接近程度

2. Précision : concordance de mesures répétées ; l'imprécision est le concept opposé, pas nécessairement un inverse numérique. 精密度 (Précision)：重复测量之间的一致程度；此处“逆”指相反概念，不是直接取数学倒数

3. Résolution : plus petit changement détectable et affichable. 分辨率 (Résolution): 是可检测和” 可显示” 的最小变化

### 5.2 Sources d'erreurs 误差来源

Instruments, partage entre utilisateurs, événements temps réel, interruptions réseau, synchronisation d'horloges, défauts de cache, exceptions et défauts de page. 测量仪器、用户之间的时间共享、实时事件 (例如网络接口中断)、时钟同步、不确定性事件 (缓存未命中、系统异常、页面错误等)

### 5.3 Quantification 量化

1. Justesse : difficile à quantifier. 准确性: 难以量化

2. La dispersion décrit la précision des répétitions ; les intervalles de confiance décrivent l'incertitude sur la moyenne. 精密度可通过重复测量的离散程度评估，均值估计的不确定性可用置信区间描述。
3. La résolution est la plus petite variation discernable par l'instrument ; l'intervalle sur la moyenne ne la remplace pas. 分辨率是仪器可辨识的最小变化，不能直接用均值置信区间替代。

### 5.4 Intervalle sur la moyenne : approximation de grand échantillon 平均值的置信区间：大样本近似

Pour des observations indépendantes, de variance finie et une moyenne approximativement normale : 当样本独立、方差有限且样本均值的正态近似合理时：

Notations : $X_i$ est une observation, $n$ leur nombre, $\mu$ la moyenne de population recherchée, $\bar X$ la moyenne observée et $s$ l'écart type empirique. Les bornes $c_1,c_2$ encadrent l'estimation de $\mu$ ; $z_{1-\alpha/2}$ est le quantile de la normale standard et $s/\sqrt n$ l'erreur standard estimée. 符号说明：$X_i$ 为单次观测，$n$ 为观测总数，$\mu$ 为要估计的总体均值，$\bar X$ 为样本均值，$s$ 为样本标准差；$c_1,c_2$ 是置信区间的下限、上限，$z_{1-\alpha/2}$ 为标准正态分位数，$s/\sqrt n$ 是均值的估计标准误差。这里 $n$ 指本次均值估计使用的样本总数，区别于 ANOVA 中每组的样本数；$\mu,s$ 也不同于 CM3 的服务率与服务时间。

$$
\begin{aligned}
c_1&=\bar X-z_{1-\alpha/2}\frac{s}{\sqrt n},\\
c_2&=\bar X+z_{1-\alpha/2}\frac{s}{\sqrt n}.
\end{aligned}
$$

$\alpha$ est le niveau de signification et $1-\alpha$ la confiance ; $\alpha=0.10$ ou $0.05$ correspond à 90 % ou 95 % de confiance. $\alpha$ 是显著性水平，$1-\alpha$ 是置信水平。$\alpha=0.10$、$0.05$ 分别对应 90%、95% 的置信水平。

> Précision : le cours 2020 p. 38 écrivait α = 0.9 ou 0.95 ; l'original 2026 p. 36 corrige en 0.1 ou 0.05 mais confond encore les noms. Le PDF consolidé p. 38 distingue les concepts. $n\ge30$ ne garantit pas à lui seul l'approximation normale. 校注：2020 年旧版第 38 页把 $\alpha$ 写为 0.9 或 0.95；2026 年教师原版第 36 页虽改为 0.1 或 0.05，仍误称 0.9 或 0.95 为显著性水平。合并 PDF 第 38 页已明确区分这两个概念。$n\ge30$ 只是经验提示，并不能保证任意数据都满足正态近似。

### 5.5 Intervalle de Student sur la moyenne 平均值的置信区间：Student 区间

Pour des observations indépendantes d'une population normale de variance inconnue : 对于来自正态总体的独立样本，当总体方差未知时：

$$
\begin{aligned}
c_1&=\bar X-t_{1-\alpha/2;n-1}\frac{s}{\sqrt n},\\
c_2&=\bar X+t_{1-\alpha/2;n-1}\frac{s}{\sqrt n}.
\end{aligned}
$$

Le seuil $t_{1-\alpha/2;n-1}$ est le quantile d'ordre $1-\alpha/2$ de la loi de Student à $n-1$ degrés de liberté ; les autres symboles sont ceux du §5.4. La formule n'est pas limitée à $n<30$. $t_{1-\alpha/2;n-1}$ 为自由度 $n-1$ 的 Student 分布的 $1-\alpha/2$ 分位数，其余符号同 §5.4。该式不局限于 $n<30$；样本变大时，Student 临界值接近标准正态临界值。

### 5.6 Exemple de quantification 误差量化示例

Huit observations du temps d'écriture d'un fichier : 文件写入时间的 8 次观测为：

| Numéro de mesure 测量编号 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Temps d'écriture $X_i$ (s) 写入时间 $X_i$（s） | 8.0 | 7.0 | 5.0 | 9.0 | 9.5 | 11.3 | 5.2 | 8.5 |

$$
\bar X=7.9375\ \mathrm{s},\qquad
s=\sqrt{\frac{\sum_{i=1}^{8}(X_i-\bar X)^2}{7}}\approx2.14472\ \mathrm{s}.
$$

À 90 % de confiance, $\alpha=0.1$ et $t_{0.95;7}\approx1.89458$, d'où : 对 90% 置信水平，$\alpha=0.1$、$t_{0.95;7}\approx1.89458$，得到：

$$
[c_1,c_2]\approx[6.50089,\ 9.37411]\ \mathrm{s}.
$$

> Précision : l'ancien calcul passait de 7.94 à 7.95 ; les notes recalculent à partir des données. L'intervalle estime le temps moyen, pas une écriture isolée. Le PDF consolidé p. 40 précise la moyenne et la couverture à long terme ; ses arrondis antérieurs restent conservés. 校注：原稿代入过程中将均值从 7.94 写为 7.95，中文阅读版按原始数据重算。区间估计的是总体平均写入时间，而非单次写入时间；合并 PDF 第 40 页已保留“平均时间”，并按重复构造区间的长期覆盖率解释 90%。PDF 的舍入数值仍保留原样。

### 5.7 Nombre de mesures à prévoir 所需测量次数（原题：Nombre d'alternatives）

Pour une demi-largeur absolue cible $\delta$, planifier le nombre total de mesures $n$ par approximation normale avec l'écart type pilote $s_0$ ; $\delta$ a l'unité de la grandeur mesurée et la largeur totale vaut $2\delta$. 若目标是均值置信区间的绝对半宽不超过 $\delta$，可用先导样本标准差 $s_0$ 规划总测量次数 $n$；$\delta$ 与原测量量单位相同，区间全宽为 $2\delta$：

$$
n\ge\left(\frac{z_{1-\alpha/2}s_0}{\delta}\right)^2.
$$

Avec une demi-largeur relative sans dimension $e_{\mathrm{rel}}$ et la moyenne pilote $\bar X_0$, poser $\delta=e_{\mathrm{rel}}|\bar X_0|$, d'où : 若采用无量纲的相对半宽 $e_{\mathrm{rel}}$，用先导样本均值 $\bar X_0$ 设置 $\delta=e_{\mathrm{rel}}|\bar X_0|$，于是：

$$
n\ge\left(\frac{z_{1-\alpha/2}s_0}{e_{\mathrm{rel}}|\bar X_0|}\right)^2.
$$

Valeurs pilotes arrondies du cours : $s_0=2.14$, $\bar X_0=7.94$, confiance 90 % et demi-largeur relative 3.5 % : 使用上例的课件舍入值 $s_0=2.14$、$\bar X_0=7.94$，以 90% 置信水平和相对半宽 3.5% 为目标：

$$
n\ge\left(\frac{1.64485\times2.14}{0.035\times7.94}\right)^2
\approx160.44.
$$

Arrondir au supérieur : planification initiale de **161 mesures**. 向上取整得到初步规划值 **161 次**。

> Précision : $(2.14\times1.895/(0.07\times7.94))^2\approx53.24$, pas 212.95. Remplacer la largeur 0.07 par la demi-largeur 0.035 avec le seuil pilote $t_{0.95;7}\approx1.895$ donne environ 212.95, soit **213 mesures**. Cette méthode diffère du calcul normal donnant 161. Avec huit observations pilotes, l'écart type reste incertain ; réévaluer éventuellement le seuil de Student, sans garantir la précision finale. 校注：原稿写出的 $(2.14\times1.895/(0.07\times7.94))^2$ 约等于 53.24，不能得到 212.95。将分母中的全宽 0.07 改为半宽 0.035，并固定使用先导样本的 $t_{0.95;7}\approx1.895$，才得到约 212.95，即 **213 次**。这与采用正态临界值所得的 161 次是不同的规划方法。先导样本只有 8 次，标准差仍有估计误差，可迭代采用新自由度的 Student 临界值；不能把规划值当作精度保证。

## 6 Conception d'un scénario de mesure 测量场景的设计

### 6.1 But 目的 (But)

- Minimiser les expériences tout en maximisant l'information. 在最大化收集信息的同时最小化实验数量
- Isoler l'effet de chaque facteur d'entrée. 隔离每个输入因子 (facteur) 的影响
- Identifier les interactions entre facteurs. 确定因子之间相互作用的影响
- Quantifier la part de l'erreur dans les résultats. 量化结果中的误差部分

### 6.2 Définition du plan d'expérience 实验设计: 定义 (Plan d'expérience : définition)

Répartir entre expériences les facteurs et leurs niveaux, c'est-à-dire leurs valeurs possibles. 实验之间因子数量和因子水平数量 (可能值)(niveaux, valeurs possibles) 的分布。

Pour $m$ facteurs ayant respectivement $L_1,\ldots,L_m$ niveaux, le nombre de configurations du plan complet est $N_{\mathrm{conf}}=\prod_{j=1}^m L_j$ ; avec $r$ répétitions par configuration, il faut $rN_{\mathrm{conf}}$ mesures. 设因子数为 $m$，各因子分别有 $L_1,\ldots,L_m$ 个水平，则完全因子设计包含 $N_{\mathrm{conf}}=\prod_{j=1}^m L_j$ 种配置；每种重复 $r$ 次时，总测量次数为 $rN_{\mathrm{conf}}$。配置数与重复次数应分开计算。

### 6.3 Classification des plans 实验设计: 分类 (Plan d'expérience : classification)

1. Plan simple : varier un facteur à partir d'une configuration initiale, pour une optimisation locale sans analyse d'interactions. 简单设计 (Plan simple): 从初始配置出发, 改变一个因子 (局部优化)。不分析交互作用。

2. Plan factoriel complet : tester toutes les combinaisons de niveaux ; le coût peut devenir prohibitif quand le nombre de facteurs ou de niveaux augmente. 完全因子设计：测试全部水平组合，能系统考察因子及其交互；因子或水平很多时成本较高，小规模时仍然可行。

3. Plan fractionnaire : choisir une fraction structurée des combinaisons pour réduire les essais, au prix d'effets pouvant être confondus. 部分因子设计：有结构地选择部分组合以减少试验次数，代价是某些主效应或交互效应可能混杂，须根据设计判断可识别的效应。

### 6.4 Exemple de plan 实验设计: 示例 (Plan d'expérience : Exemple)

Quatre facteurs {A, B, C, D}, trois niveaux chacun. 4 个因子 {A, B, C, D}，每个因子 3 个水平

Le plan complet comporte 81 combinaisons. 完全因子设计给出 81 种组合。

Le tableau orthogonal $L_9(3^4)$ réalise neuf essais pour quatre facteurs à trois niveaux, au lieu des 81 combinaisons. 下表采用 4 因子、每因子 3 水平的 $L_9(3^4)$ 正交表，用 9 次实验代替完整的 81 种组合。

Dans $L_9(3^4)$, l'indice 9 est le nombre d'essais et $3^4$ indique quatre colonnes à trois niveaux ; ce symbole $L_9$ nomme le tableau et ne représente pas un niveau $L_j$. 记号 $L_9(3^4)$ 中，下标 9 表示试验次数，$3^4$ 表示四列、每列三个水平；$L_9$ 是正交表名称，不是前文单个因子的水平数 $L_j$。

> Précision : le cours 2020 p. 45 parlait à tort d'un plan en étoile. L'original 2026 p. 43 mentionne neuf essais, mais leur capacité d'analyse des interactions doit être limitée. Chaque paire de colonnes contient une fois les neuf combinaisons ; toutes les interactions ne sont pas estimables indépendamment. Le PDF consolidé p. 45 le précise. 校注：2020 年旧版第 45 页称其为“星形设计”，与表格结构不符；2026 年教师原版第 43 页改写为 9 次实验，但交互作用说明仍需限定。每两列的 9 种水平组合各出现一次；9 次试验不能独立估计所有交互作用。合并 PDF 第 45 页已据此改写。

| Expérience 实验 (Expérience) | Facteur 1 因子 1(Fact1) | Facteur 2 因子 2(Fact2) | Facteur 3 因子 3(Fact3) | Facteur 4 因子 4(Fact4) |
| --- | --- | --- | --- | --- |
| 1 | A1 | B1 | C1 | D1 |
| 2 | A1 | B2 | C2 | D2 |
| 3 | A1 | B3 | C3 | D3 |
| 4 | A2 | B1 | C2 | D3 |
| 5 | A2 | B2 | C3 | D1 |
| 6 | A2 | B3 | C1 | D2 |
| 7 | A3 | B1 | C3 | D2 |
| 8 | A3 | B2 | C1 | D3 |
| 9 | A3 | B3 | C2 | D1 |

## 7 Synthèse 总结

Ce cours couvre deux méthodes d'évaluation : simulation et mesure. 本课程涵盖了性能评估中的仿真和测量两个重要方法:

### 7.1 Points clés de la simulation 仿真的关键要点

- Évaluer sans disposer du système réel. 仿真允许在不需要真实系统的情况下评估系统性能
- La simulation à événements discrets représente les événements, états et transitions ; c'est une méthode très courante. 离散事件仿真 (Simulation à événements discrets) 是最常用的方法, 通过事件、状态和转换来模拟系统行为
- Monte Carlo évalue itérativement un modèle déterministe à partir d'entrées aléatoires. 蒙特卡洛方法 (Méthode Monte Carlo) 用于使用随机变量迭代评估确定性模型
- Le simulateur comporte ordonnanceur, horloge globale, traitement et génération d'événements, et enregistrement des données. 仿真器必须包含: 事件调度器、全局时钟、事件处理过程、事件生成机制和数据记录机制

### 7.2 Points clés de la mesure 测量的关键要点

- Trois phases : observation et collecte, analyse, présentation. 测量涉及观察/收集、分析和呈现三个阶段
- Évaluer la qualité par justesse, précision et résolution. 测量质量通过准确性 (Justesse)、精度 (Précision) 和分辨率 (Résolution) 来评估
- ANOVA et intervalles de confiance aident à quantifier variabilité et incertitude. 统计方法如 ANOVA 和置信区间用于量化测量中的误差
- Les plans d'expérience maximisent l'information pour un nombre limité d'essais. 实验设计 (Plan d'expérience) 帮助最小化实验数量同时最大化收集的信息

### 7.3 Outils et ressources 重要工具和资源

- Simulateurs de microprocesseurs : http://pages.cs.wisc.edu/~arch/www/tools.html 微处理器仿真器: http://pages.cs.wisc.edu/~arch/www/tools.html
- SimGrid: http://simgrid.gforge.inria.fr/
- DiskSim: http://www.pdl.cmu.edu/DiskSim/
- OGSSim: https://github.com/liparad-storage/ogssim
- Outils simples : time, gettimeofday, top, gprof, etc. 简单测量工具: time, gettimeofday, top, gprof 等

## Annexe : formules importantes 附录：重要公式汇总

### Intervalles de confiance 置信区间

Sous les hypothèses précisées dans le texte, les intervalles sur la moyenne sont : 在正文说明的假设下，均值区间为：

$$
\bar X\pm z_{1-\alpha/2}\frac{s}{\sqrt n}
\quad\text{（大样本正态近似）},
$$

$$
\bar X\pm t_{1-\alpha/2;n-1}\frac{s}{\sqrt n}
\quad\text{（正态总体、方差未知）}.
$$

### ANOVA

$$
\bar y_j=\frac1n\sum_{i=1}^n y_{ij},\qquad
\bar y=\frac1{kn}\sum_{j=1}^k\sum_{i=1}^n y_{ij}.
$$

$$
\mathrm{SSA}=n\sum_{j=1}^k(\bar y_j-\bar y)^2,\qquad
\mathrm{SSE}=\sum_{j=1}^k\sum_{i=1}^n(y_{ij}-\bar y_j)^2.
$$

$$
F=\frac{\mathrm{SSA}/(k-1)}{\mathrm{SSE}/[k(n-1)]}.
$$

Rejeter l'égalité des moyennes si $F>F_{1-\alpha;k-1,k(n-1)}$. 当 $F>F_{1-\alpha;k-1,k(n-1)}$ 时拒绝各组均值相等的原假设。

### Nombre de mesures 所需测量次数

$$
n\ge\left(\frac{z_{1-\alpha/2}s_0}{e_{\mathrm{rel}}|\bar X_0|}\right)^2.
$$

$e_{\mathrm{rel}}$ est une demi-largeur relative ; arrondir au supérieur. Le résultat dépend du pilote et de la validité du modèle statistique. $e_{\mathrm{rel}}$ 为相对半宽；计算结果向上取整，且依赖先导样本和统计模型的适用性。


## Correspondance des pages PDF PDF 页码对照

| Contenu 内容 | Original du cours 2026 2026 年教师原版 | Version consolidée et corrigée 合并校订版 |
|---|---|---|
| Introduction et simulation à événements discrets 概论、离散事件仿真 | 1–19 | 1–19 |
| Simulateurs populaires, complément conservé 常用模拟器（保留旧版补充） | — | 20–21 |
| Monte Carlo, mesure et calcul ANOVA Monte Carlo、测量与 ANOVA 计算 | 20–31 | 22–33 |
| ANOVA et test F ANOVA 与 F 检验 | 32 | 34 |
| Présentation et qualité de mesure 结果呈现、测量质量 | 33–35 | 35–37 |
| Intervalle normal, α et confiance 正态近似区间、α 与置信水平 | 36 | 38 |
| Intervalle de Student Student 区间 | 37 | 39 |
| Exemple du temps moyen d'écriture 平均写入时间示例 | 38 | 40 |
| Nombre de mesures à prévoir 所需测量次数 | 39–40 | 41–42 |
| Plans d'expérience et tableau orthogonal L₉ 实验设计与 L₉ 正交表 | 41–43 | 43–45 |
