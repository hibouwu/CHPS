# Annexe du cours 1 : compléments HPC et préparation des cours suivants 第一课 Annex：HPC 扩展与后续课程预习

[第一课中文正文](1_edpCpl_zh.md) · [课程目录](../README.md) · [今年教师课件](1_edpCpl.pdf)

本文件承接原中文笔记第 19–35 节，使用 A1–A17 编号，保留其中的背景、模型、工具与后续课程预习内容。部分基础概念与新版正文重合，可作复习；Roofline、LogP、BSP 等扩展没有在当前 CM1 的对应正文页展开，不作为教师已授内容的证明。

格式说明：法语在前、中文在后，同一行以空格隔开，撇号统一为 '。法语优先依据对应课件及法语讲义，必要时沿用已有订正；中文补充、校注和附录中没有对应原文的部分配以法语译写，仍属补充材料。

Lire d'abord les [sections 19–26 du cours principal](1_edpCpl_zh.md), puis consulter cette annexe selon les besoins. Les noms d'outils servent de repères ; vérifier leur documentation actuelle pour l'installation et l'utilisation. 跟课时先读 [正文第 19–26 节](1_edpCpl_zh.md)，本附录按需要查阅。这里保留的工具名称用于了解用途，具体安装与运行方式应另查当前文档。

## Guide de lecture 阅读导航

| Complément recherché 需要补充的内容 | Section de l'annexe 本附录位置 | Ancienne section 原笔记位置 |
|---|---|---|
| Contexte HPC, hypothèses d'Amdahl et pic théorique HPC 背景、Amdahl 假设、峰值性能 | A1–A3 | Sections 19–21 第 19–21 节 |
| Roofline, autres modèles, communication et synchronisation Roofline、其他模型、通信与同步 | A4–A5 | Sections 22–23 第 22–23 节 |
| Niveaux d'évaluation, outils et synthèse HPC 评估层次、工具与 HPC 扩展小结 | A6–A7 | Sections 24–25 第 24–25 节 |
| Préparation : workloads, modélisation, simulation et mesure 工作负载、建模、仿真和测量预习 | A8–A12 | Sections 26–30 第 26–30 节 |
| Limites, méthodes, erreurs et présentation 模型局限、方法、常见陷阱与结果展示 | A13–A17 | Sections 31–35 第 31–35 节 |

Cours suivants : [workloads](2_edp_zh.md), [modélisation et files d'attente](3_edp_zh.md), [simulation et mesure](45_edp_zh.md). 后续课程的对应入口：[工作负载](2_edp_zh.md)、[数学建模与排队模型](3_edp_zh.md)、[仿真与测量](45_edp_zh.md)。

## A1 Évaluation des performances pour le HPC 高性能计算（HPC）中的性能评估

### A1.1 Motivation et problématique en HPC 动机与问题（Motivation et problématique —HPC）

En calcul haute performance, l'évaluation est essentielle pour : 在高性能计算（HPC, High Performance Computing / Calcul Haute Performance）中，性能评估对于以下方面至关重要：

- Comprendre le comportement parallèle des programmes ; 理解程序在并行执行中的行为；
- Localiser les goulots d'étranglement ; 定位性能瓶颈（goulots d'étranglement）；
- Guider l'optimisation et le passage à l'échelle ; 指导调优（optimisation）与扩展；
- Choisir une architecture adaptée ; 选择合理的硬件架构（architectures）；
- Concevoir des algorithmes parallèles efficaces ; 设计高效并行算法；
- Comparer implémentations et plateformes. 比较不同实现、不同平台的性能差异。

La complexité HPC vient d'une architecture à plusieurs niveaux : HPC 系统的复杂性来自多层次架构：

- Processeurs multicœurs 多核处理器（multi‐core CPUs）
- Accélérateurs hétérogènes, notamment GPU 异构加速器（GPU / accelerators）
- Réseau d'interconnexion multinœud 多节点互连网络（réseau d'interconnexion）
- Stockage distribué 分布式存储系统

Outre les métriques de base, il faut donc considérer architecture et modèle de parallélisme. 因此，HPC 性能评估不仅需要基本指标，还必须考虑架构特性与并行模型。

## A2 Parallélisme et performance 并行性与性能

La performance HPC dépend du degré de parallélisme et de l'efficacité d'utilisation des ressources. 在 HPC 中，性能依赖于并行度（parallélisme）和资源利用效率（efficacité d'utilisation des ressources）。

### A2.1 Rappel sur l'accélération parallèle 并行加速比：回顾（Speedup）

Accélération $\mathrm{Acc}$ : rapport du temps séquentiel $T_{\mathrm{séquentiel}}$ au temps parallèle $T_{\mathrm{parallèle}}$ pour la même tâche ; $P$ est le nombre de processeurs. 加速比记为 $\mathrm{Acc}$，是同一任务的串行执行时间 $T_{\mathrm{séquentiel}}$ 与并行执行时间 $T_{\mathrm{parallèle}}$ 之比，$P$ 为处理器数量：

$$
\mathrm{Acc} = \frac{T_{\mathrm{séquentiel}}}{T_{\mathrm{parallèle}}}
$$

Dans le cas idéal : 理想情况下：

$$
\mathrm{Acc} (P) = P
$$

Communications, synchronisation et cohérence des caches peuvent éloigner le speedup de la linéarité. 但在实际 HPC 中，由于通信（communication）、同步（synchronisation）、缓存一致性等开销，加速比会偏离线性。

### A2.2 Limites de la loi d'Amdahl Amdahl 定律的限制

Amdahl considère une taille de problème fixe. Ses limites sont liées aux hypothèses : Amdahl 定律考虑固定问题规模（strong scaling）。其局限在于：

- Fraction parallélisable fixe ; 假设并行部分比例固定；
- Répartition idéale de la partie parallèle, sans surcoût supplémentaire de communication ou de synchronisation ; 假设并行部分可理想均分，忽略额外通信、同步等开销；
- Les surcoûts à grande échelle et les variations de taille exigent un autre traitement ; le nombre de cœurs n'invalide pas à lui seul la relation à taille fixe. 大规模系统中的额外开销和问题规模变化需要另行建模；核心数量本身不会让 Amdahl 的固定规模关系失效；

Utiliser Amdahl à taille fixe et Gustafson-Barsis pour un problème agrandi, en précisant leurs références temporelles. 固定规模分析可使用 Amdahl 模型；扩大规模的分析可使用 Gustafson-Barsis 模型，并明确两者的时间基准。

> Précision : l'ancienne affirmation selon laquelle Amdahl ne s'appliquerait plus avec beaucoup de cœurs était excessive ; elle est corrigée selon les hypothèses du modèle. 校注：原笔记“核心数很大时 Amdahl 不再适用”的说法过强，已按模型假设修正。

## A3 Métriques classiques en HPC HPC 中的经典性能指标（Métriques classiques dans le HPC）

Métriques usuelles : HPC 领域中的指标包括：

- Accélération $\mathrm{Acc}$ : gain de temps par rapport à une référence. 加速比 $\mathrm{Acc}$：相对于基准的执行时间收益。
- Efficacité parallèle $E=\mathrm{Acc}/P$ : accélération par processeur. 并行效率 $E=\mathrm{Acc}/P$：每个处理器对应的加速收益。
- Performance flottante, FLOP/s : opérations flottantes exécutées par seconde. 浮点性能：每秒完成的浮点运算数。
- Utilisation $U=b/T$ : temps occupé $b$ divisé par la durée d'observation $T$. 利用率 $U=b/T$：忙碌时长 $b$ 占观察时长 $T$ 的比例。
- Coût de communication 通信开销（coût de communication）
- Équilibrage de charge 负载均衡（load balancing）

### A3.1 Performance flottante 浮点性能（FLOPS）

Les FLOPS mesurent les opérations flottantes par seconde. Pic théorique : FLOPS（Floating Point Operations Per Second）：衡量每秒可执行浮点运算数量。理论峰值性能（peak performance）：

$$
P_{\mathrm{peak}} = N_{\mathrm{cœurs}}\times f\times N_{\mathrm{FLOP/cycle/cœur}}
$$

Ici, $P_{\mathrm{peak}}$ est le débit flottant théorique en FLOP/s, $N_{\mathrm{cœurs}}$ le nombre de cœurs, $f$ leur fréquence en cycles/s et $N_{\mathrm{FLOP/cycle/cœur}}$ le nombre d'opérations par cycle et par cœur pour la précision et le chemin considérés. $P_{\mathrm{peak}}$ 表示理论浮点吞吐量，单位为 FLOP/s；$N_{\mathrm{cœurs}}$ 为核心数，$f$ 为时钟频率（周期/秒），$N_{\mathrm{FLOP/cycle/cœur}}$ 为指定精度和执行路径下每核心、每周期的浮点运算数。这里 $P_{\mathrm{peak}}$ 是性能量，区别于表示处理器数量的 $P$。

La performance réelle est souvent inférieure au pic, notamment à cause de : 实际性能通常远低于理论值，受制于：

- Bande passante mémoire 内存带宽（memory bandwidth）
- Goulots de débit 吞吐瓶颈（bottlenecks）
- Mélange d'instructions 指令混合（instruction mix）
- Comportement des caches et localité 缓存行为（cache locality）
- Communication et synchronisation 通信、同步开销

<a id="annex-roofline"></a>

## A4 Modèles et limites 性能模型与局限（Modèles et lacunes）

Modèles HPC courants : HPC 常用的性能模型包括：

- **Amdahl / Gustafson** : relier fraction séquentielle, nombre de processeurs et potentiel d'accélération selon la taille du problème. 根据问题规模及时间基准，分析串行比例、处理器数量与加速潜力的关系。
- **Roofline** : comparer les plafonds de calcul et de bande passante à l'aide de l'intensité arithmétique. 用算术强度比较算力上限与带宽上限，公式见下文。
- **LogP** : décrire la communication par la latence $L$, le surcoût processeur $o$, l'intervalle minimal $g$ entre envois ou réceptions successifs et le nombre de processeurs $P$. 用通信延迟 $L$、处理器收发开销 $o$、连续发送或接收的最小间隔 $g$ 及处理器数量 $P$ 描述通信成本（[cours de Berkeley / Berkeley 课程说明](https://people.eecs.berkeley.edu/~demmel/cs267/lecture09/lecture09.html)）。
- **BSP** : organiser le calcul en super-étapes de travail local et de communication, séparées par des synchronisations globales. 将并行程序组织为包含本地计算和通信的超步，超步之间进行全局同步（[rapport d'Oxford / Oxford 模型说明](https://www.cs.ox.ac.uk/techreports/oucl/tr-15-96.html)）。

Ils servent à : 这些模型用于：

- Estimer la performance d'un algorithme ; 估计算法性能；
- Analyser une limitation de calcul ; 分析是否受算力限制（compute‐bound）；
- Analyser une limitation de bande passante mémoire ; 分析是否受内存带宽限制（memory‐bound）；
- Quantifier les communications. 量化通信成本。

### A4.1 Modèle Roofline Roofline 性能模型

Roofline fournit une borne de performance : Roofline 模型给出性能上限：

$$
\mathrm{Performance} \leq \min(P_{\mathrm{peak}}, I \times \mathrm{BW})
$$

Avec : 其中：

- $P_{\mathrm{peak}}$ : plafond de calcul en FLOP/s, défini en A3.1. $P_{\mathrm{peak}}$：A3.1 定义的算力上限，单位为 FLOP/s。
- $I$ : intensité arithmétique, opérations flottantes divisées par les octets transférés au niveau mémoire choisi, en FLOP/octet. $I$：算术强度，即浮点运算数除以所选存储层级传输的字节数，单位为 FLOP/byte。
- $\mathrm{BW}$ : bande passante au même niveau mémoire, en octets/s ; $I\,\mathrm{BW}$ est donc en FLOP/s. $\mathrm{BW}$：同一存储层级的带宽，单位为 byte/s，因此 $I\,\mathrm{BW}$ 与算力上限具有相同单位 FLOP/s。

Il distingue deux domaines : 它区分两类程序：

- Limitation par la bande passante mémoire 内存带宽受限（memory‐bound）
- Limitation par le débit de calcul 计算性能受限（compute‐bound）

Le modèle compare plafonds de calcul et de bande passante. Octets et bande passante doivent concerner le même niveau mémoire ; la borne n'est pas une performance garantie. Voir la [présentation du Berkeley Lab](https://amcr.lbl.gov/departments/computer-science-department/ppan/roofline-performance-model/). 该模型帮助比较算力上限与带宽上限。算术强度的字节数和带宽必须针对同一存储层级；上限也不等于实际可达到的性能。模型说明见 [Berkeley Lab 的 Roofline 介绍](https://amcr.lbl.gov/departments/computer-science-department/ppan/roofline-performance-model/)。

## A5 Communication et synchronisation 通信与同步开销（Communications et synchronisation）

Dans un programme parallèle, considérer : 在并行程序中必须考虑：

- Communications point à point 点对点通信（point‐to‐point）
- Communications collectives 集体通信（collectives）
- Barrières de synchronisation 同步屏障（barrières）
- Protocoles de cohérence des caches 缓存一致性协议
- Coût des accès NUMA NUMA 访问成本

Le coût dépend de la taille des messages, de la latence, de la bande passante et du calcul recouvrable ; préciser unités et tailles des opérations comparées. 通信成本取决于消息大小、互连延迟、带宽和可重叠的计算量；比较时应明确通信操作与计算操作的单位和规模。

## A6 Méthodes d'évaluation en HPC HPC 中的性能评估方法（Évaluation dans le HPC）

Elles incluent généralement : HPC 性能评估通常包括：

- Microbenchmarks 微基准测试（microbenchmarks）
- Tests de noyaux de calcul 内核（kernel）测试
- Tests d'applications réelles 真实应用测试（applications réelles）
- Simulation HPC 仿真（simulation HPC）
- Analyse de traces 跟踪（tracing）分析

Exemples d'outils : 工具示例：

- Tests MPI : IMB et OSU Benchmarks MPI 测试套件：IMB、OSU Benchmarks
- Analyse : perf, VTune, TAU et HPCToolkit 性能分析工具：perf、VTune、TAU、HPCToolkit
- Traçage : Paraver et Score-P 跟踪系统：Paraver、Score-P

## A7 Synthèse des compléments HPC HPC 扩展内容小结（Résumé HPC）

La première partie de cette annexe traite : 本附录前半部分讨论：

- Importance de la performance HPC ; HPC 性能的重要性；
- Modèles de speedup et limites ; 并行加速模型及其局限；
- Écart entre FLOPS théoriques et performance réelle ; FLOPS 与实际性能差距；
- Roofline et autres modèles ; Roofline 等性能模型；
- Effets des communications et synchronisations ; 通信与同步的影响；
- Méthodes et outils d'évaluation HPC. HPC 中的评估方法与工具。

## A8 Workloads 工作负载

Le workload représente les tâches que le système doit rencontrer en usage réel. 在性能评估中，工作负载（workload）用于代表系统在真实使用中将面对的任务类型。

On souhaite généralement qu'il permette de : 选择或构造工作负载时，通常希望它能够：

- Représenter fidèlement le cas réel ; 准确反映真实场景；
- Reproduire l'expérience sur différents systèmes ; 能在不同系统间复现；
- Comparer les configurations ; 能用于比较不同配置；
- Faire apparaître les goulots ; 能引出性能瓶颈；
- Rester cohérent avec la méthode d'évaluation. 对评估方式（建模、仿真、测量）保持一致性。

### A8.1 Classification des workloads 工作负载的分类

Deux classes usuelles : 工作负载通常分为两类：

#### 1. Charge synthétique 合成工作负载（synthetic workload）

- Construite artificiellement ; 由人工构造；
- Contrôlable et répétable ; 可控、可重复；
- Souvent utilisée dans les microbenchmarks ; 通常用于微基准测试（microbenchmarks）；
- Simple, réglable et facile à analyser ; 特点：简单、可调整、易于分析；
- Exemples : multiplication matricielle de taille fixe, tests de motifs d'accès. 示例：固定大小的矩阵乘法、循环访问模式测试等。

#### 2. Charge réelle 真实工作负载（workload réel）

- Issue d'applications réelles ; 来自实际应用；
- Représentative du comportement effectif ; 代表实际系统的行为；
- Révèle des interactions complexes ; 能揭示复杂交互；
- Parfois difficile à contrôler et à reproduire ; 但可能不可控、难以重现；
- Exemples HPC : CFD, dynamique moléculaire et météorologie. 示例：真实 HPC 应用，如 CFD、分子动力学、天气模拟等。

### A8.2 Caractéristiques des workloads 工作负载特性

Choisir les caractéristiques selon le système ; elles ne sont pas toutes nécessaires dans chaque expérience : 根据系统类型选择需要描述的特征；并非每个实验都同时需要下列所有特征：

- Taux d'arrivée moyen $\lambda$ : requêtes soumises par unité de temps. 平均到达率 $\lambda$：单位时间提交的请求数量。
- Temps de service moyen $s$, de taux associé $\mu=1/s$. 平均服务时间 $s$，对应服务率 $\mu=1/s$。
- Modèle de parallélisme 并行度模式（modèle de parallélisme）
- Motifs d'accès et localité mémoire 数据访问模式（localité, patterns mémoire）
- Motifs de communication 通信模式（communication patterns）
- Comportement I/O I/O 行为
- Consommation CPU, mémoire et réseau 资源消耗特征（CPU, mémoire, réseau）

### A8.3 Exemples de workloads 工作负载类型示例

Traitement par lots 批处理型（batch workloads）

- Tâches longues ; 长时间运行的任务；
- Intensives en données ou en calcul ; 数据密集或计算密集；
- Très fréquent en HPC. HPC 中非常常见。

Charges interactives 交互式（interactive workloads）

- Réponse rapide attendue ; 需要快速响应；
- Métrique typique : temps de réponse. 典型指标为响应时间（temps de réponse）；

Charges transactionnelles 事务型（transactionnel）

- Fréquentes dans les bases de données ; 常见于数据库；
- Métriques telles que TPS. 指标包括 TPS（transactions per second）。

## A9 Modélisation mathématique 数学建模

La modélisation approche le comportement par des relations mathématiques, notamment quand le système n'existe pas ou n'est pas mesurable. Avantages : 数学建模用数学方法近似描述系统行为，也常用于系统尚不存在或无法直接测量的情形。主要优势：

- Évaluation rapide ; 评估速度快；
- Pas de système réel nécessaire ; 不需要真实系统；
- Prédiction de scénarios futurs ; 可预测未来场景；
- Comparaison de nombreuses entrées et configurations dans le domaine des hypothèses. 可在模型假设允许的范围内比较大量输入与配置。

Inconvénients : 缺点：

- Nombreuses hypothèses ; 需要大量假设；
- Écart possible avec le réel ; 可能与现实偏离；
- Détails souvent abstraits. 细节通常被抽象化；

### A9.1 Étapes de modélisation 数学建模的步骤

1. Définir le système ; 定义要分析的系统；

2. Identifier ses composants principaux ; 确定系统的主要组成部分；

3. Définir paramètres et variables ; 定义参数和变量；

4. Écrire les équations du système ; 写出描述系统的数学方程；

5. Résoudre les équations ou simuler leur évolution ; 求解这些方程或模拟其运行；

6. Analyser les résultats ; 分析结果；

7. Valider par comparaison avec des données réelles. 验证模型与真实数据是否一致。

### A9.2 Modèles de files d'attente 队列模型

Ils décrivent : 队列模型用于描述：

- Arrivée des requêtes ; 请求的到来；
- Attente ; 等待；
- Service ; 服务（service）；
- Départ. 离开。

Modèles courants : 常见模型：

- **M/M/1** : arrivées de Poisson, services exponentiels et un serveur. 泊松到达、指数服务时间、一个服务台。
- **M/M/$k$** : mêmes hypothèses avec $k$ serveurs identiques en parallèle, notés $C$ dans CM3. 相同到达与服务假设下，使用 $k$ 个并行的相同服务台；CM3 用 $C$ 表示该数量。
- **M/G/1** : arrivées de Poisson et un serveur, avec une loi générale des temps de service. 泊松到达、一个服务台，服务时间允许采用一般分布。
- **G/G/1** : un serveur avec des lois générales pour les intervalles d'arrivée et les temps de service. 一个服务台，到达间隔与服务时间均采用一般分布。

Ces noms résument les lois d'arrivée, de service et le nombre de serveurs ; les conditions de stabilité et les formules sont développées dans [CM3](3_edp_zh.md). 这些名称概括到达规律、服务规律和服务台数量，稳定条件与计算公式见 [CM3](3_edp_zh.md)。

Ils permettent de prévoir : 它们用于预测：

- Temps moyen d'attente $w$ 平均等待时间 $w$
- Temps moyen de réponse $r=w+s$ 平均响应时间 $r=w+s$
- Utilisation $U$ 利用率 $U$
- Nombre moyen de clients en attente $q$, ou dans le système entier $n$ 仅等待队列中的平均客户数 $q$，或整个系统中的平均客户数 $n$

## A10 Simulation 仿真

La simulation s'utilise quand le système réel n'est pas directement mesurable ou que la modélisation analytique ne suffit pas. 仿真是在无法直接测量真实系统、或数学建模不够精确时使用的一种方法。

Types de simulation : 类型包括：

- Simulation à événements discrets 离散事件仿真（simulation à événements discrets）
- Simulation continue 连续仿真（simulation continue）
- Modèles hybrides 模拟 ‐ 仿真混合模型（modèles hybrides）

Avantages : 优势：

- Description plus détaillée ; la validité dépend du modèle et des entrées ; 能纳入较细的系统行为；准确性取决于模型及输入是否可信；
- Prise en compte de systèmes complexes ; 可处理复杂系统；
- Pas de matériel réel nécessaire. 不需要真实硬件；

Inconvénients : 缺点：

- Coût temporel élevé ; 非常耗时（时间成本高）；
- Modèle complexe ; 模型复杂；
- Ressources de calcul importantes. 需要大量计算资源；

### A10.1 Étapes d'une simulation à événements discrets 离散事件仿真的典型步骤

1. Définir les entités ; 定义系统实体（entités）；

2. Définir les événements ; 定义事件（événements）；

3. Définir les états du système ; 定义系统状态（états du système）；

4. Construire l'ordonnanceur d'événements ; 构建事件调度器（ordonnanceur d'événements）；

5. Définir la collecte statistique ; 定义统计收集方式；

6. Exécuter et collecter les données ; 运行仿真，收集数据；

7. Analyser et valider les résultats. 分析、验证仿真结果；

## A11 Mesure 测量

Si le système existe et est accessible, la mesure renseigne sur l'exécution réelle. Représentativité, surcoût des outils et bruit influencent les résultats ; vérifier la répétabilité. 当系统存在且可访问时，测量能提供实际运行证据。结果仍受工作负载代表性、测量工具开销和环境噪声影响，需检验可重复性。

Difficultés principales : 主要挑战：

- Système nécessairement accessible ; 系统必须可用；
- Perturbation possible des utilisateurs ; 测试可能干扰真实用户；
- Paramètres parfois incontrôlables ; 某些参数不可控；
- Résultats bruités. 测量结果可能受噪音影响；

### A11.1 Éléments de la mesure 测量的组成要素

- Outils de mesure ; 测量工具（outils de mesure）；
- Compteurs de performance ; 性能计数器（compteurs de performance）；
- Traçage d'événements ; 事件跟踪（tracing）；
- Journaux ; 日志（logs）；
- Horodatages. 时间戳（timestamps）；

### A11.2 Exigences de mesure 测量的关键要求

- Répétabilité 可重复性（répétabilité）
- Exactitude 正确性（exactitude）
- Faible perturbation 最小侵入（faible perturbation）
- Précision élevée 高精度（précision）
- Variété des données collectées 多样化数据（variété des données collectées）

### A11.3 Exemples de méthodes 测量方法示例

#### 1. Profilage Profiling（性能剖析）

- Nombre d'appels des fonctions ; 统计函数执行次数；
- Relations dans la pile d'appels ; 栈调用关系；
- Part du temps CPU. CPU 时间占比；

#### 2. Traçage Tracing（事件跟踪）

- Chronologie des événements ; 跟踪事件时间线；
- Comportement visible dans les limites des événements et de la résolution enregistrés. 在所记录事件和时间精度的范围内展示程序行为；

#### 3. Benchmarking 基准测试

- Tester la performance sur des tâches fixes ; 使用固定任务测试性能；
- Comparer différents systèmes. 可用于不同系统之间比较；

### A11.4 Exemples d'outils de mesure 测量工具示例

- perf
- PAPI（Performance API）
- gprof
- valgrind
- HPCToolkit
- Intel VTune
- Score-P / Paraver

## A12 Comparaison : modélisation, simulation et mesure 综合对比：建模 vs 仿真 vs 测量

- Modélisation : rapide mais abstraite. 数学建模（modélisation）：快速，但抽象。
- Simulation : plus détaillée, avec erreur de modèle et coût de calcul. 仿真（simulation）：可表达更多细节，但有模型误差和计算成本。
- Mesure : réelle mais exige un système existant. 测量（mesure）：真实但需要系统存在。

Dans une évaluation professionnelle : 在专业性能评估中：

Combiner deux ou trois méthodes pour chercher des conclusions concordantes ; leur accord ne remplace pas la vérification des hypothèses communes. 通常结合两种或三种方法，检查结论是否相互支持；多种方法一致也不能代替对共同假设的检查。

## A13 Limites des modèles 模型的局限（Lacunes des modèles）

Les hypothèses simplificatrices facilitent la résolution ; vérifier leur pertinence : 模型通过简化假设减少求解难度，因此必须检查假设是否适合当前问题：

- Simplifications fréquentes : tâches indépendantes, coût linéaire des communications et répartition uniforme. 常见简化包括任务独立、通信开销线性增长、负载均匀分布。
- Selon l'abstraction, NUMA, caches, topologie, communications irrégulières et bruit système peuvent être omis. 根据抽象层次，模型可能省略 NUMA、多级缓存、网络拓扑、不规则通信与操作系统噪声。
- Cas extrêmes et variations d'entrée peuvent dépasser le domaine validé. 极端情况与输入变化可能超出模型经过验证的范围。
- Chaque modèle cible certains aspects : Roofline relie intensité, bande passante et pic, sans expliquer seul toutes les latences ou synchronisations. 不同模型关注不同方面。例如基本 Roofline 连接算术强度、带宽和算力上限，无法独自解释所有延迟与同步问题。

Les modèles guident les prédictions et l'analyse ; vérifier leur applicabilité avec mesures ou simulations. 模型适合提出预测和指导分析；还应结合实测或仿真检查其适用性。

## A14 Méthodologie d'évaluation HPC HPC 性能评估的综合方法论（Méthodologie d'évaluation pour le HPC）

1. **Définir le but :** goulots, comparaison, optimisation, choix matériel ou passage à l'échelle. **定义目标。** 寻找瓶颈、比较算法、优化程序、选择硬件，或评估扩展能力。
2. **Choisir les métriques :** speedup, efficacité, utilisation, FLOP/s, débit I/O ou communication, avec unités et périmètre. **选择指标。** 根据目标选择加速比、效率、利用率、FLOP/s、I/O 吞吐量或通信开销，并定义单位与测量范围。
3. **Choisir le workload :** tâches, tailles et accès représentatifs. **选择工作负载。** 让任务、规模与访问行为能代表要研究的场景。
4. **Choisir les méthodes :** modélisation, simulation, mesure, seules ou combinées. **选择方法。** 使用数学建模、仿真、实测中的一项或多项。
5. **Concevoir les expériences :** facteurs et contrôles, répétitions et, au besoin, ordre aléatoire. **设计实验。** 明确变化参数和控制变量，重复运行，必要时随机化运行次序。
6. **Collecter et analyser :** moyennes, variances, intervalles et valeurs aberrantes, avec justification de leur traitement. **收集与分析。** 检查均值、方差、置信区间和异常值；说明异常值处理理由。
7. **Interpréter et présenter :** graphiques, modèles et scalabilité, hypothèses et limites. **解释与呈现。** 用图表、模型对比和扩展性分析说明结果，记录假设及限制。

## A15 Erreurs fréquentes 性能评估中的常见陷阱

Erreurs courantes d'évaluation : 性能评估中常见错误包括：

- Métriques inadaptées ; 不恰当的性能指标；
- Perturbation par les outils ; 工具本身干扰程序性能；
- Aléas du système ignorés ; 忽略现实系统中的随机性；
- Workload inadéquat ; 工作负载不匹配；
- Conclusion à partir d'un seul point ; 使用单一数据点得出错误结论；
- Mauvaise interprétation des benchmarks ; 错误解释基准测试结果；
- Hiérarchie mémoire négligée ; 未考虑内存层次结构的影响；
- Communication et synchronisation ignorées ; 忽略通信与同步成本；
- Confiance excessive dans MIPS ou FLOPS ; 过度依赖 MIPS 或 FLOPS；
- Scénarios incomplets. 案例设计不完整；

La checklist de Raj Jain aide à éviter ces erreurs. Raj Jain 的 checklist 可用于避免这些陷阱。

## A16 Présentation des résultats 性能结果展示方法

- Choisir courbes, barres ou graphiques de speedup et d'efficacité selon la question. 根据问题选择折线图、柱状图或加速比/效率曲线。
- Indiquer unités, référence, sens des barres d'erreur et répétitions. 标清单位、比较基准、误差条的含义与重复次数。
- Justifier une échelle logarithmique pour éviter les mauvaises interprétations. 使用对数刻度时说明原因，避免读者误判变化幅度。
- Expliquer tendances et causes possibles, en distinguant faits et hypothèses. 解释趋势及可能原因，并区分观测事实和推测。
- Documenter hypothèses, limites, plateforme, compilation et optimisations. 写明模型假设、局限、测试平台、编译选项与优化配置。

Les graphiques doivent préciser comparateurs, conditions et portée des conclusions. 图表应让读者知道比较对象、测量条件及结论适用范围。

## A17 Récapitulatif des thèmes complémentaires 原笔记扩展主题回顾

Ces thèmes relèvent en partie du cours, en partie de compléments ; ils ne prouvent pas le contenu effectivement enseigné ou évalué cette année : 原笔记及本附录涉及的主题如下；其中部分对应课程主线，部分属于扩展，不能据此推断今年的授课或考试范围：

- Concepts de base 性能评估的基本概念（concepts de base）
- Caractéristiques des workloads 工作负载特性（workloads）
- Métriques de performance 性能指标（temps de réponse, débit, speedup, efficacité, fiabilité, disponibilité）
- Checklist de Raj Jain 避免错误的 checklist（Raj Jain）
- Modélisation, simulation et mesure 性能评估方法（modélisation, simulation, mesure）
- Analyse des performances HPC 并行性能分析（HPC）
- Modèles d'Amdahl et de Gustafson-Barsis 加速比模型（Amdahl, Gustafson-Barsis）
- Communication, synchronisation et surcoûts parallèles 通信、同步与并行开销
- Modèle Roofline Roofline 模型
- Outils HPC HPC 性能工具

Ces contenus permettent de s'exercer à : 这些材料可以用于练习：

1. Évaluer correctement un système ; 正确评估一个系统的性能；

2. Choisir les métriques appropriées ; 选择合适的性能指标；

3. Combiner plusieurs méthodes ; 使用多种方法进行分析；

4. Identifier goulots et pistes d'optimisation HPC ; 在 HPC 环境中识别瓶颈与优化方向；

5. Présenter clairement les résultats. 清晰展示性能结果；

Relier ces thèmes à des questions et expériences concrètes plutôt que mémoriser seulement noms de modèles et d'outils. 进一步学习时，应把这些主题对应回具体问题和实验，而不只记忆模型与工具名称。
