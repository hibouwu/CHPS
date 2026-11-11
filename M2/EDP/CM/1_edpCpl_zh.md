# Évaluation des performances : concepts de base et performance en HPC 性能评估：基础概念与 HPC 性能

## 1 Présentation générale du module 课程总体介绍

Ce module présente les objectifs, méthodes et techniques de l'évaluation des performances. Il couvre : 本模块介绍性能评估的目标、方法和技术。主要内容如下：

- Introduction : motivation, problématique, concepts de base et liens avec le HPC. 性能评估导论：动机、问题、基本概念、与 HPC 的关系。
- Méthodes et techniques d'évaluation. 性能评估方法与技术。
- Workloads, avec un complément de Sébastien Gougeaud. 工作负载，含 Sébastien Gougeaud 补充部分。
- Modélisation mathématique. 数学建模。
- Simulation. 仿真。
- Mesure, avec un complément de Sébastien Gougeaud. 测量，含 Sébastien Gougeaud 补充部分。

## 2 Plan du cours 课程计划

### Première partie : concepts de base 第一部分：基本概念

1. Motivation et problématique 动机与问题

2. Approche à suivre 评估步骤

3. Checklist pour éviter les erreurs 避免错误的检查表

4. Métriques de base 基本性能指标

5. Caractéristiques d'une bonne métrique 好指标的特性

6. Méthodes d'évaluation 性能评估的方法

### Deuxième partie : évaluation des performances pour le HPC 第二部分：HPC 中的性能评估

1. Objectifs 目标

2. Parallélisme et performance 并行性与性能

3. Métriques classiques dans le HPC HPC 中经典性能指标

4. Modèles et lacunes HPC 性能模型及其局限

5. Évaluation des systèmes HPC HPC 系统评估

## 3 Motivation et problématique 动机与问题

But de tout système : fournir le meilleur rapport coût/performance. 系统的目标是：提供最佳的成本/性能比。

Il faut donc évaluer les performances à toutes les étapes du cycle de vie du système : 因此，在系统生命周期的所有阶段都需要进行性能评估：

1. Conception : prédiction des performances. 设计阶段——性能预测。

2. Réalisation : choix matériel ou logiciel. 实现阶段——硬件或软件的选择。

3. Commercialisation : mise en valeur des métriques. 商用阶段——突出性能指标。

4. Utilisation : réglages selon le contexte. 使用阶段——根据上下文进行调优。

5. Maintenance et mise à jour : contrôle et monitoring. 维护与更新——系统控制与监控。

### 3.1 Objectifs de l'évaluation 性能评估的目标

- Mieux connaître la faisabilité d'un système ou d'une application et l'intérêt de son développement. 更好地了解一个系统或应用的可行性，以及开发/编码的价值。
- Détecter et comprendre les limitations d'un système. 发现和理解系统的限制。
- Cibler les améliorations : ajout de ressources, réorganisation des traitements ou des charges. 找到可以改进的方向：例如增加资源（如处理器）、改变任务组织方式、改变负载结构等。

## 4 Approche à suivre 评估流程

Les systèmes à analyser, leurs métriques, les techniques d'évaluation et les workloads associés sont multiples. 需要分析的系统可能是多种多样的，其性能指标、评估方法以及对应工作负载也各不相同。

L'approche générale suit néanmoins les étapes suivantes : 但总体评估步骤如下：

1. Définir le système à analyser et préciser le but à atteindre. 定义要分析的系统，明确目标。

2. Établir la liste des services à fournir. 列出系统应提供的服务列表。

3. Sélectionner les métriques de vitesse, de précision et de disponibilité. 选择用于衡量速度、精度、可用性的性能指标。

Poursuivre avec les étapes suivantes : 接下来继续以下步骤：

4. Lister les paramètres qui affectent les performances, en distinguant système et workload. 列出影响性能的参数（区分系统参数与工作负载参数）。

5. Sélectionner les facteurs à faire varier et leurs valeurs possibles. 从这些参数中选择在评估过程中可变化的因子，并设定它们的可能取值。

6. Choisir la méthode appropriée : modélisation mathématique, simulation ou mesure. 在数学建模、仿真和测量中选择最适合的评估方法。

Puis effectuer les étapes suivantes : 随后必须执行：

7. Choisir les charges synthétiques ou réelles à appliquer. 选择用于施加给系统的工作负载：合成工作负载或真实工作负载。

8. Concevoir des tests qui apportent un maximum d'informations sur le comportement du système. 设计测试集合，以最大化对系统行为的观察信息。

9. Collecter les données, puis les analyser et les interpréter statistiquement. 收集测试数据，使用统计方法分析和解释数据。

10. Présenter les résultats sous une forme claire, avec des graphiques adaptés. 使用清晰的结构和适当的图形方式展示结果。

## 5 Checklist pour éviter les erreurs — Raj Jain 避免错误的检查表

Les points suivants permettent de vérifier que l'analyse est complète et correcte : 以下是性能评估中常见的检查要点，确保分析完整且正确：

- Le système est-il correctement défini et les objectifs sont-ils clairs ? 系统是否正确定义？目标是否清晰？
- Les objectifs sont-ils formulés sans biais ? 目标是否以无偏方式陈述？
- Toutes les étapes de l'analyse ont-elles été suivies systématiquement ? 所有分析步骤是否系统地执行？
- Le problème est-il bien compris avant l'analyse ? 在分析前是否真正理解问题？
- Les métriques sont-elles pertinentes ? 性能指标是否与问题相关？
- Le workload convient-il au problème ? 所选工作负载是否合适？
- La technique d'évaluation est-elle appropriée ? 选择的评估技术是否适当？
- La liste des paramètres influençant les performances est-elle complète ? 列出的影响性能的参数是否完整？

Vérifications supplémentaires : 进一步检查：

- Les paramètres influents ont-ils été considérés comme facteurs variables ? 所有影响性能的参数是否作为可变化因子？
- Le plan d'expérience est-il efficace en temps et en résultats ? 实验设计是否在时间与结果之间取得良好平衡？
- Le niveau de détail est-il approprié ? 细节层次是否合理？
- Les données sont-elles accompagnées d'une analyse et d'une interprétation ? 数据是否附带分析和解释？
- L'analyse est-elle statistiquement correcte ? 分析是否统计上正确？
- Une analyse de sensibilité a-t-elle été effectuée ? 是否执行了敏感性分析？
- Les erreurs d'entrée peuvent-elles modifier sensiblement les résultats ? 输入误差是否会引起显著的输出变化？
- Les valeurs aberrantes ont-elles été traitées correctement ? 是否合理地处理了异常值？

Examiner également les points suivants : 进一步还应关注：

- Les évolutions futures du système et du workload ont-elles été prises en compte ? 是否考虑了未来系统或工作负载的变更？
- La variance des entrées a-t-elle été considérée ? 是否考虑了输入的方差？
- La variance des résultats a-t-elle été analysée ? 是否分析了结果的方差？
- L'analyse est-elle facile à expliquer ? 分析是否易于解释？
- La présentation convient-elle au public visé ? 展示风格是否符合目标读者？
- Les résultats sont-ils présentés graphiquement autant que possible ? 图形展示是否尽可能使用？
- Les hypothèses et les limites sont-elles clairement documentées ? 假设和限制是否清楚地记录？

## 6 Introduction aux métriques 性能指标简介

Métriques courantes : 以下为常见性能指标：

- **Temps de réponse $r$ 响应时间 $r$** : durée entre la requête et la réponse ; une valeur plus faible est préférable. 从发出请求到收到响应的时间，通常越小越好。
- **Débit $X$ 吞吐量 $X$** : quantité de travail achevée par unité de temps ; une valeur plus élevée est préférable à tâche identique. 单位时间完成的工作量，在任务相同的条件下通常越大越好。
- **Accélération $\mathrm{Acc}$ 加速比 $\mathrm{Acc}$** : rapport du temps de référence au temps étudié. 基准执行时间与当前执行时间的比值。
- **Efficacité $E$ 并行效率 $E$** : accélération rapportée au nombre de processeurs $P$. 加速比除以处理器数量 $P$。
- **Utilisation $U$ 资源利用率 $U$** : fraction du temps d'observation pendant laquelle la ressource est occupée. 观察期内资源处于忙碌状态的时间比例。
- **Fiabilité $R_{\mathrm{rel}}(T)$ 可靠性 $R_{\mathrm{rel}}(T)$** : probabilité de fournir un service correct sans défaillance pendant une durée $T$. 在给定时长 $T$ 内持续正确工作、没有发生失效的概率。
- **Disponibilité $A$ 可用性 $A$** : fraction du temps pendant laquelle le système peut fournir le service. 系统能够提供服务的时间比例。

Les sections suivantes définissent ces métriques et leurs conditions d'emploi. Le débit réalisé $X$ se distingue du taux d'arrivée $\lambda$ du cours 3 ; ils sont égaux à l'équilibre des flux. 后文分别说明这些指标及适用条件。实际完成吞吐量 $X$ 与 CM3 的到达速度 $\lambda$ 含义不同，在流量平衡时两者相等。

## 7 Temps de réponse 响应时间

Définition : le temps de réponse $r$ sépare la requête de l'utilisateur de la réponse du système ; $r_0$ désigne sa valeur sous charge minimale. Une charge accrue peut augmenter l'attente et donc $r$. 响应时间 $r$ 是从用户发出请求到系统返回响应的时间；最小负载下的基准值记为 $r_0$。负载增加可能带来更多等待，使 $r$ 增大。

Le facteur d'extension est défini par : 伸长因子定义为：

$$
\mathrm{stretchfactor} = \frac{r}{r_0}
$$

Il quantifie l'allongement du temps de réponse lorsque la charge augmente. 它衡量负载增长所带来的性能恶化程度。

Exemple en temps partagé : rapport du temps de réponse avec multiprogrammation à celui sans multiprogrammation. 例子：在分时系统中，使用多道程序时的响应时间与无多道程序时的响应时间之比即为伸长因子。

## 8 Débit 吞吐量

Définition : le débit $X=d/T$ est le nombre de requêtes achevées $d$ pendant une durée d'observation $T$, divisé par cette durée. 吞吐量记为 $X=d/T$，其中 $d$ 是观察期内完成的请求数，$T$ 是观察时长；它描述完成速度，不是请求到来的速度。

Unités selon le système : 不同系统的吞吐量单位：

- Système interactif : requêtes/s 交互式系统：requests/s
- CPU：MIPS，MFLOPS
- Traitement par lots : jobs/s 批处理：jobs/s
- Réseau : paquets/s, bits/s 网络：packets/s，bits/s
- Système transactionnel : transactions/s (TPS) 事务系统：transactions/s (TPS)

Le débit croît avec la charge jusqu'à une capacité maximale, comme la bande passante d'un réseau. 吞吐量随负载增加直到达到某种最大容量上限（类似网络带宽上限）。

### 8.1 Deux notions de capacité 容量的两种定义

1. Capacité nominale : débit maximal sous une charge idéale. 名义容量：系统在理想负载下能达到的最大吞吐量。

Exemple : après amorçage, un pipeline sans dépendance pénalisante ni branchement peut exécuter une instruction par cycle. 例：流水线填满后，无数据依赖停顿且无分支跳转的处理器可做到每周期完成一条指令。

2. Capacité d'usage : débit maximal compatible avec un temps de réponse acceptable. 可用容量：在保持用户可接受响应时间约束下可达到的最大吞吐量。

**Complément.** En file d'attente (cf. CM3), lorsque le débit approchant la capacité nominale fait tendre l'utilisation $\rho$ vers $1$, le temps d'attente explose ($\bar{R} \propto \frac{1}{1-\rho}$). La capacité d'usage correspond donc au débit maximal $X_{\max}$ tel que $R(X_{\max}) \le R_{\mathrm{cible}}$, toujours strictement inférieur à la capacité nominale. **补充说明。** 在排队系统中（见 CM3），当吞吐量逼近名义容量、利用率 $\rho \to 1$ 时，排队等待时间会急剧发散（$\bar{R} \propto \frac{1}{1-\rho}$）。因此可用容量对应满足响应时间上限 $R(X_{\max}) \le R_{\mathrm{cible}}$ 的最大吞吐量 $X_{\max}$，它严格小于理想名义容量。

## 9 MIPS et MFLOPS MIPS 与 MFLOPS

Avec $N_{\mathrm{inst}}$ instructions exécutées en $T_{\mathrm{exec}}$ secondes, les MIPS (millions d'instructions par seconde) valent : 设执行指令数为 $N_{\mathrm{inst}}$、执行时间为 $T_{\mathrm{exec}}$ 秒，则 MIPS（每秒百万条指令）为：

$$
\mathrm{MIPS} = \frac{N_{\mathrm{inst}}}{10^{6}T_{\mathrm{exec}}}
$$

Les MFLOPS comptent les millions d'opérations flottantes par seconde ; une instruction vectorielle ou FMA peut représenter plusieurs opérations. MFLOPS 统计每秒完成的百万次浮点运算；运算数不一定等于浮点指令数，例如向量指令和融合乘加（FMA）。

En notant $N_{\mathrm{FLOP}}$ le nombre d'opérations flottantes, $\mathrm{MFLOPS}=N_{\mathrm{FLOP}}/(10^6T_{\mathrm{exec}})$. Une FMA scalaire compte pour deux opérations, une multiplication et une addition. 浮点运算总数记为 $N_{\mathrm{FLOP}}$，则 $\mathrm{MFLOPS}=N_{\mathrm{FLOP}}/(10^6T_{\mathrm{exec}})$。标量 FMA 的一次乘法和一次加法合计为 2 次浮点运算。

Remarques : 说明：

- Les deux unités supposent que les instructions sont en mémoire. 二者假设指令全部在内存中。
- Les MIPS, en particulier, ne constituent pas une métrique fiable. 特别是 MIPS，不是可靠的性能指标。

**Complément.** Pourquoi MIPS est-il trompeur ? Dans $\mathrm{MIPS} = \frac{N_{\mathrm{inst}}}{10^6 T_{\mathrm{exec}}}$, le numérateur $N_{\mathrm{inst}}$ dépend du jeu d'instructions (ISA) et du compilateur, et non du travail utile accompli :
1. **Granularité des instructions (RISC vs CISC / SIMD / Coprocesseur)** : une opération complexe remplacée par une séquence de $k$ instructions simples augmente $N_{\mathrm{inst}}$ d'un facteur $k$. Si ces instructions simples s'exécutent vite dans le pipeline, le ratio $N_{\mathrm{inst}}/T_{\mathrm{exec}}$ (les MIPS) augmente alors même que le temps total $T_{\mathrm{exec}}$ s'allonge.
2. **MFLOPS vs MIPS** : pour un algorithme numérique donné, le nombre d'opérations mathématiques $N_{\mathrm{FLOP}}$ (ex. $2n^3$ pour une multiplication matricielle $n\times n$) est lié au problème, ce qui rend les MFLOPS plus comparables que les MIPS à algorithme fixé. **补充说明。** 为什么 MIPS 容易误导？在 $\mathrm{MIPS} = \frac{N_{\mathrm{inst}}}{10^6 T_{\mathrm{exec}}}$ 中，分子 $N_{\mathrm{inst}}$ 取决于指令集架构（ISA）与编译器，而非实际完成的有效工作量：
1. **指令粒度差异（RISC vs CISC / 向量化 / 协处理器）**：若一条复杂硬件指令被拆成 $k$ 条简单指令软件模拟，$N_{\mathrm{inst}}$ 会成倍膨胀；由于简单指令单条周期短，比值 $N_{\mathrm{inst}}/T_{\mathrm{exec}}$（即 MIPS）反而可能升高，而实际总耗时 $T_{\mathrm{exec}}$ 却大幅恶化（见 §17.2 Whetstone 反例）。
2. **MFLOPS 与 MIPS 的区别**：对于给定数值算法，浮点数学运算次数 $N_{\mathrm{FLOP}}$（如 $n\times n$ 矩阵乘法的 $2n^3$ 次运算）由问题规模决定，因此在固定算法下 MFLOPS 比 MIPS 更具可比性。

## 10 Accélération / Speedup 加速比

Définition : $\mathrm{Acc}$ compare le temps séquentiel $T_{\mathrm{séquentiel}}$ au temps parallèle $T_{\mathrm{parallèle}}$ pour la même tâche ; on les note aussi $T_1$ et $T_P$ pour $P$ processeurs. 加速比记为 $\mathrm{Acc}$，比较同一任务的串行时间 $T_{\mathrm{séquentiel}}$ 与并行时间 $T_{\mathrm{parallèle}}$；后文也用 $T_1$、$T_P$ 表示单处理器与 $P$ 个处理器的执行时间。

$$
\mathrm{Acc} = \frac{T _{\mathrm{séquentiel}}}{T _{\mathrm{parallèle}}}
$$

Loi d'Amdahl : Amdahl 定律：

$$
\mathrm{Acc} = \frac{1}{(1 - F _{a}) + \frac{F _{a}}{P}}
$$

Avec : 其中：

- $F_a$ : fraction du temps séquentiel de référence correspondant au travail parallélisable, avec $0\le F_a\le1$. $F_a$：可并行工作占串行基准执行时间 $T_1$ 的比例（$0\le F_a\le1$），不是源代码行数的比例。
- $P$ : nombre de processeurs. $P$：处理器数量。

**Complément (dérivation).** En décomposant le temps séquentiel $T_1$ en une partie purement séquentielle $(1-F_a)T_1$ et une partie parfaitement parallélisable $F_a T_1$, le temps sur $P$ processeurs sans surcoût vaut $T_P = (1-F_a)T_1 + \frac{F_a T_1}{P}$. Le rapport $\mathrm{Acc} = \frac{T_1}{T_P}$ donne immédiatement la formule, et lorsque $P \to \infty$, $\mathrm{Acc}_{\max} = \frac{1}{1-F_a}$ : la fraction séquentielle $(1-F_a)$ borne durement le gain maximal. **补充说明（推导）。** 将单核基准时间 $T_1$ 拆分为不可并行的串行部分 $(1-F_a)T_1$ 与可理想平摊的并行部分 $F_a T_1$，则在无额外开销时 $P$ 核耗时为 $T_P = (1-F_a)T_1 + \frac{F_a T_1}{P}$。取比值 $\mathrm{Acc} = \frac{T_1}{T_P}$ 即得 Amdahl 公式；当 $P \to \infty$ 时，$\mathrm{Acc}_{\max} = \frac{1}{1-F_a}$，说明串行时间占比 $(1-F_a)$ 直接锁死了加速比的理论上限。

### 10.1 Coût de parallélisation 并行化成本

L'accélération n'est généralement pas linéaire, notamment à cause de : 加速比通常不是线性的，因为并行化带来：

- Communications 通信
- Synchronisation 同步
- Ordonnancement, déséquilibre de charge, etc. 调度、负载不均衡等

Loi d'Amdahl enrichie : 扩展的 Amdahl 定律：

$$
\mathrm{Acc} = \frac{1}{(1 - F _{a}) + \frac{F _{a}}{P} + C _{t} (F _{a} , P)}
$$

$C_t$ est le surcoût temporel de parallélisation divisé par le temps séquentiel de référence ; il doit être sans dimension pour s'ajouter aux autres termes du dénominateur. 其中 $C_t(F_a, P) = \frac{T_{\mathrm{surcoût}}(P)}{T_1}$ 是并行化引入的额外时间除以串行基准时间 $T_1$，必须是无量纲量，才能与分母中的时间比例相加。

## 11 Efficacité 效率

Définition : l'efficacité parallèle $E$ rapporte l'accélération $\mathrm{Acc}$ au nombre de processeurs $P$ ; $E=1$ correspond à une accélération linéaire. 并行效率记为 $E$，等于加速比 $\mathrm{Acc}$ 除以处理器数量 $P$；$E=1$ 对应线性加速。

$$
E = \frac{\mathrm{Acc}}{P}
$$

Ou, de manière équivalente : 或等价地：

$$
E = \frac{T _{\mathrm{séquentiel}}}{T _{\mathrm{parallèle}} \times P}
$$

Une efficacité réduite peut venir du code séquentiel, du déséquilibre de charge, des communications, de la synchronisation ou d'autres surcoûts ; il faut les mesurer. 效率下降可能来自串行部分、负载不均衡、通信、同步或其他开销，需要结合测量判断。

## 12 Taux d'utilisation 资源利用率

Définition : l'utilisation $U=b/T$ est le temps d'occupation $b$ de la ressource divisé par la durée d'observation $T$, avec $0\le U\le1$. 利用率记为 $U=b/T$，其中 $b$ 是资源累计忙碌时长，$T$ 是观察时长，$0\le U\le1$。

Objectifs : 目标：

- Maximiser l'utilisation d'une ressource. 最大化单资源利用率
- Équilibrer la charge entre les ressources. 全系统实现负载均衡

L'efficacité parallèle $E$ et l'utilisation $U$ sont distinctes : une ressource peut être occupée par des communications ou une attente active. 并行效率 $E$ 与资源利用率 $U$ 不等同：资源可能在通信或忙等待（spin-waiting）时仍被计为“忙碌”，此时 $U$ 很高但有效并行效率 $E$ 很低。

## 13 Strong scaling et weak scaling 强扩展与弱扩展

### 13.1 Strong scaling 强扩展

À taille de problème $n$ constante, augmenter le nombre de processeurs $P$ ; comparer les temps $T_1(n)$ et $T_P(n)$ du même problème. 固定问题总规模 $n$，增加处理器数量 $P$，比较同一问题的执行时间 $T_1(n)$ 与 $T_P(n)$。

Dans le cas idéal : 理想情况：

$$
\mathrm{Acc} \rightarrow P, \qquad E \rightarrow 1
$$

### 13.2 Weak scaling 弱扩展

Augmenter la taille $n$ avec $P$ pour garder le travail par processeur approximativement constant ; si $n$ mesure le travail total, cela donne $n(P)=P\,n(1)$. 随处理器数量 $P$ 增大问题规模 $n$，使每个处理器承担的工作量近似不变；若 $n$ 表示总工作量，则为 $n(P)=P\,n(1)$，理想目标是并行执行时间 $T_P(n(P)) \approx T_1(n(1))$ 保持近似恒定。

## 14 Loi de Gustafson-Barsis Gustafson-Barsis 定律

Pour un calcul parallèle dont la taille augmente : 对于规模随处理器数增大的并行计算：

$$
\mathrm{Acc} (n, P) \leq P + (1 - P) s
$$

Ici, $s$ est la fraction séquentielle du temps de l'exécution parallèle du problème agrandi, $n$ sa taille et $P$ le nombre de processeurs. La fraction d'Amdahl utilise le temps séquentiel de référence ; les deux ne sont pas interchangeables. 这里的 $s$ 是扩大问题后，串行阶段占**并行运行总时间 $T_P$** 的比例，$n$ 是问题规模，$P$ 是处理器数量。Amdahl 模型中的串行比例以**单核串行基准时间 $T_1$** 为分母，两者不能直接混用；本课的比例 $s$ 也不同于 CM3 的平均服务时间 $s$。

Le modèle de Gustafson-Barsis montre le potentiel d'accélération pour des problèmes agrandis. 与 Amdahl 不同，该定律表明并行计算在大问题规模下可获得随 $P$ 线性增长的加速比。

**Complément (dérivation et comparaison avec Amdahl).** Supposons que sur $P$ processeurs le problème agrandi prenne un temps total $T_P$, dont une fraction $s$ est séquentielle ($s T_P$, ex. initialisation et I/O qui ne croissent pas avec la taille) et une fraction $(1-s)$ est parallèle ($(1-s)T_P$). Si un seul processeur devait exécuter ce même problème agrandi, la partie parallèle lui prendrait $P$ fois plus de temps :
$$
T_1' = s T_P + P(1-s)T_P.
$$
L'accélération mise à l'échelle (scaled speedup) vaut donc :
$$
\mathrm{Acc}(n, P) = \frac{T_1'}{T_P} = s + P(1-s) = P + (1-P)s.
$$
La différence fondamentale réside dans le **dénominateur de la fraction séquentielle** :
- **Amdahl (strong scaling, $n$ fixé)** : $s_{\mathrm{Amdahl}} = 1 - F_a = \frac{T_{\mathrm{seq}}}{T_1}$ est mesuré sur $1$ processeur ; quand $P$ augmente, le temps parallèle $F_a T_1 / P$ rétrécit tandis que $T_{\mathrm{seq}}$ reste fixe.
- **Gustafson (weak scaling, $n \propto P$)** : $s = \frac{T_{\mathrm{seq}}}{T_P}$ est mesuré sur $P$ processeurs ; on maintient le temps parallèle $(1-s)T_P$ constant en grossissant le problème, ce qui dilue le poids du code séquentiel dans le travail total $T_1'$. **补充说明（推导及与 Amdahl 的本质区别）。** 设扩大后的问题在 $P$ 个处理器上总耗时为 $T_P$，其中串行阶段耗时 $s T_P$（如不随网格规模膨胀的初始化等），并行阶段耗时 $(1-s)T_P$。若将这同一个扩大后的问题放到单处理器上串行执行，并行部分耗时将放大 $P$ 倍：
$$
T_1' = s T_P + P(1-s)T_P.
$$
由此得到扩展加速比（scaled speedup）：
$$
\mathrm{Acc}(n, P) = \frac{T_1'}{T_P} = s + P(1-s) = P + (1-P)s.
$$
两定律的核心区别在于**串行比例的分母基准不同**：
- **Amdahl（强扩展，固定规模 $n$）**：串行比例 $s_{\mathrm{Amdahl}} = 1 - F_a = \frac{T_{\mathrm{seq}}}{T_1}$ 以单核时间 $T_1$ 为分母；随 $P$ 增大，并行耗时 $\frac{F_a T_1}{P}$ 不断缩小，导致串行部分成为瓶颈。
- **Gustafson（弱扩展，规模随 $P$ 放大）**：串行比例 $s = \frac{T_{\mathrm{seq}}}{T_P}$ 以 $P$ 核并行时间 $T_P$ 为分母；通过随 $P$ 扩大问题规模使并行耗时 $(1-s)T_P$ 保持恒定，从而在总工作量 $T_1'$ 中稀释了串行开销的占比。

## 15 Fiabilité 可靠性

Définition : la fiabilité $R_{\mathrm{rel}}(T)$ est la probabilité de fournir un service correct sans défaillance pendant une durée $T$, à partir d'un système initialement opérationnel. 可靠性记为 $R_{\mathrm{rel}}(T)$，表示系统从正常状态开始，在时长 $T$ 内持续正确工作且不发生失效的概率。

Fiabilité des données : la redondance totale ou partielle protège leur intégrité. 数据可靠性：存储系统通过完全或部分冗余保证数据正确性。

Fiabilité du réseau : les messages parviennent à leurs destinataires. 网络可靠性：保证消息被成功送达目的地。

Métrique usuelle : temps moyen entre erreurs, MTBE. 常用指标：错误之间的平均时间 MTBE（Mean Time Between Errors）。

## 16 Disponibilité 可用性

Définition : la disponibilité $A$ est la fraction du temps pendant laquelle le système peut servir les utilisateurs. 可用性记为 $A$，表示系统能够提供服务的时间比例。

Uptime : fonctionnement normal ; downtime : indisponibilité. uptime：正常运行时间；downtime：停机不可用时间。

Indicateurs courants : 常用指标：

- **MTTF** (Mean Time To Failure) : durée moyenne avant une défaillance. 发生失效前的平均正常运行时长。
- **MTBF** (Mean Time Between Failures) : durée moyenne entre défaillances successives d'un système réparable ; préciser si les temps de réparation sont inclus. 可修复系统两次相邻失效之间的平均时长。

**Complément (relation entre MTTF, MTTR, MTBF, disponibilité et fiabilité).** Pour un système réparable alternant entre phases de bon fonctionnement (durée moyenne $\mathrm{MTTF}$, *uptime*) et phases de réparation (durée moyenne $\mathrm{MTTR}$, *Mean Time To Repair*, *downtime*), la période moyenne d'un cycle complet entre deux pannes successives est $\mathrm{MTBF} = \mathrm{MTTF} + \mathrm{MTTR}$. La disponibilité stationnaire vaut alors :
$$
A = \frac{\mathrm{uptime}}{\mathrm{uptime} + \mathrm{downtime}} = \frac{\mathrm{MTTF}}{\mathrm{MTTF} + \mathrm{MTTR}} = \frac{\mathrm{MTTF}}{\mathrm{MTBF}}.
$$
Ne pas confondre **fiabilité** et **disponibilité** : un système qui tombe en panne toutes les heures ($\mathrm{MTTF} = 1\text{ h}$) mais redémarre en $1\text{ ms}$ ($\mathrm{MTTR} \approx 0$) a une **disponibilité** $A \approx 100\%$, mais une **fiabilité** $R_{\mathrm{rel}}(T)$ très faible sur une mission de $T = 24\text{ h}$ (car une exécution HPC sans checkpointing sera interrompue dès la première panne). **补充说明（MTTF、MTTR、MTBF 与可用性、可靠性的关系）。** 对于可修复系统，系统在正常运行阶段（平均时长 $\mathrm{MTTF}$，即 uptime）与故障修复阶段（平均修复时长 $\mathrm{MTTR}$，即 downtime）之间交替循环，两次相邻故障起点的平均周期为 $\mathrm{MTBF} = \mathrm{MTTF} + \mathrm{MTTR}$。稳态可用性为：
$$
A = \frac{\mathrm{uptime}}{\mathrm{uptime} + \mathrm{downtime}} = \frac{\mathrm{MTTF}}{\mathrm{MTTF} + \mathrm{MTTR}} = \frac{\mathrm{MTTF}}{\mathrm{MTBF}}.
$$
注意区分**可靠性**与**可用性**：如果一台机器每小时崩溃一次（$\mathrm{MTTF} = 1\text{ h}$），但每次只需 $1\text{ ms}$ 即可瞬间重启恢复（$\mathrm{MTTR} \approx 0$），则它的**可用性** $A \approx 100\%$ 极高，但在 $T = 24\text{ h}$ 内的**可靠性** $R_{\mathrm{rel}}(T)$ 极低（未做检查点容错的 HPC 长作业只要遇到一次崩溃就会前功尽弃）。

## 17 Caractéristiques d'une bonne métrique 好指标的特征

### 17.1 Linéarité 线性

La métrique devrait varier aussi linéairement que possible avec la performance réelle. 指标应尽量与实际性能成线性关系。

Exemple : une échelle logarithmique peut conduire à des malentendus. 例：某些对数尺度的指标容易引起直观上的误解。

### 17.2 Fiabilité 可靠性

Une métrique fiable classe les systèmes selon leur performance réelle : un débit élevé est généralement préférable, un temps de réponse faible également. 一个可靠指标应使排序与实际性能排序一致：吞吐量通常越大越好，响应时间通常越小越好，不能统一理解为数值越大越好。

Contre-exemple : MIPS. 反例：MIPS。

Exemple du benchmark Whetstone : Whetstone 基准测试例子：

- Avec coprocesseur flottant : 1.08 s, 1.6 MIPS. 使用浮点协处理器：耗时 $1.08\text{ s}$，指标为 $1.6\text{ MIPS}$。
- Sans coprocesseur : 13.6 s, 2.7 MIPS. 不使用浮点协处理器：耗时 $13.6\text{ s}$，指标为 $2.7\text{ MIPS}$。

Le second cas affiche davantage de MIPS, mais prend environ 12.6 fois plus de temps : les MIPS ne reflètent pas ici la performance. 尽管第二种情况的 MIPS 数值更高，但实际耗时慢了约 $12.6$ 倍，说明 MIPS 不是可靠指标。

**Complément (explication du paradoxe Whetstone).** En multipliant $\mathrm{MIPS} \times T_{\mathrm{exec}}$, on retrouve le nombre total d'instructions exécutées $N_{\mathrm{inst}}$ :
- Avec coprocesseur : $N_{\mathrm{inst}} = 1.6 \times 10^6 \times 1.08 \approx 1.73 \times 10^6$ instructions (les opérations flottantes sont exécutées directement par quelques instructions matérielles du coprocesseur).
- Sans coprocesseur : $N_{\mathrm{inst}} = 2.7 \times 10^6 \times 13.6 \approx 36.7 \times 10^6$ instructions (chaque opération flottante est émulée en logiciel par des dizaines d'instructions entières très simples et rapides à décoder).
Le processeur sans coprocesseur exécute donc $21$ fois plus d'instructions à un rythme unitaire plus élevé ($2.7$ vs $1.6\text{ MIPS}$), mais met $12.6$ fois plus de temps pour accomplir le même programme. **补充说明（Whetstone 悖论的定量解释）。** 由 $N_{\mathrm{inst}} = \mathrm{MIPS} \times 10^6 \times T_{\mathrm{exec}}$ 可以反推出两种配置实际执行的指令总数：
- 有浮点协处理器：$N_{\mathrm{inst}} = 1.6 \times 10^6 \times 1.08 \approx 1.73 \times 10^6$ 条指令（浮点运算由协处理器硬件指令直接完成，单条指令耗时较长但指令数极少）。
- 无浮点协处理器：$N_{\mathrm{inst}} = 2.7 \times 10^6 \times 13.6 \approx 36.7 \times 10^6$ 条指令（每次浮点运算都被展开为数十条简单的整数移位/加减软件模拟指令）。
无协处理器时执行了约 $21$ 倍数量的简单整数指令，单条指令吞吐速度看似更快（$2.7 > 1.6\text{ MIPS}$），但完成同一任务的总时间却慢了 $12.6$ 倍。

### 17.3 Déterminisme 确定性

Un test répété devrait donner la même valeur de métrique. 重复测试应得到相同指标值。

### 17.4 Facilité de mesure 易测性

Une métrique difficile à mesurer risque d'être erronée et sera moins utilisée. 难以测量的指标容易引入测量误差，因此较少被采用。

## 18 Méthodes d'évaluation des performances 性能评估方法

Trois méthodes : 三类方法：

- **Modélisation analytique 数学建模** : abstraire le système en variables et équations pour calculer des indicateurs sous des hypothèses explicites. 将系统抽象为变量和方程，在明确假设下计算性能指标。
- **Simulation 仿真** : exécuter un modèle pour suivre son comportement dans des configurations choisies. 运行系统模型，观察它在指定配置与输入下如何演化。
- **Mesure 实测** : observer une exécution réelle pour obtenir durées, événements et débits. 观察真实运行，获得执行时间、事件数量和吞吐量等数据。

Critères de choix : 选择依据包括：

- Existence du système 系统是否已存在
- Coût temporel 时间成本
- Budget 预算
- Précision souhaitée 所需精度

Si le système existe et est accessible, privilégier la mesure ; sinon, utiliser la simulation ou la modélisation. 若系统存在且可访问，可优先测量；否则可使用仿真或建模。

On compare souvent deux méthodes pour valider les résultats. 通常采用两种方法互相验证。

## 19 Objectifs de l'évaluation en HPC HPC 性能评估的目标

> Correspondance : pages 42–43 du cours actuel. Les sections suivantes suivent les pages 42–62 ; les exemples et compléments sont des explications ajoutées. 对应今年教师课件第 42–43 页。下文按第 42–62 页的顺序展开；“例子”和“补充说明”为便于理解加入的解释。

Une machine au débit théorique plus élevé exécutera-t-elle nécessairement l'application plus vite ? Il faut connaître la répartition du temps sur l'ancienne machine et la ressource améliorée sur la nouvelle. 买一台峰值算力更高的机器，应用就一定更快吗？要回答这个问题，需要知道应用在原机器上把时间花在哪里，以及新机器改善了哪一种资源。

L'évaluation HPC se rapproche du matériel : mesurer ses performances élémentaires, caractériser processeur et mémoire, comparer les architectures et estimer les gains technologiques. Le cours souligne aussi : HPC 性能评估因此更贴近硬件：测量基础性能，刻画处理器、内存与其他部件的行为，比较硬件方案，并判断技术变化可能带来多少收益。课件还强调两点：

- **Isoler un facteur.** Utiliser des microbenchmarks ciblés, éventuellement proches des limites de la ressource, pour observer saturation et évolution des performances. **把单个因素测清楚。** 用针对性的微基准施加负载，必要时测试接近资源极限的情况，观察饱和与性能变化。
- **Contrôler le travail réellement exécuté.** Vérifier, voire écrire, l'assembleur pour identifier les instructions et accès effectivement exécutés malgré les transformations du compilateur ou de l'environnement. **控制实际执行的工作。** 为避免编译器或运行环境改变实验含义，有时需要检查乃至编写汇编，确认真正执行了哪些指令、哪些数据访问。

Il faut relier ces mesures à l'application : une bande passante élevée sous un certain motif d'accès ne garantit pas que l'application l'exploite ; cela dépend de ses accès et de son parallélisme. 这些基础测量还要回到应用：内存带宽测得很高，只说明这台机器在相应访问方式下能提供这样的带宽；应用能否利用它，取决于自己的访问模式和并行程度。

## 20 Parallélisme et performance 并行性与性能

> Correspondance : pages 44–50. 对应课件第 44–50 页。

### 20.1 Loi d'Amdahl : identifier le travail répartissable Amdahl 定律：先看哪些时间能被分摊

Pour un problème fixe de durée séquentielle $T_1$, la fraction séquentielle vaut $s$ ; le reste est idéalement réparti sur $P$ processeurs, sans surcoût : 设固定问题在单处理器上的执行时间为 $T_1$，其中串行部分占比为 $s$；其余部分理想地分配到 $P$ 个处理器，暂不计额外开销：

Dans cette section, $s=1-F_a$ et $S(P)$ est le même speedup que $\mathrm{Acc}$ en §10 ; $s$ n'est pas la fraction mesurée sur le temps parallèle agrandi du §14. 本节中 $s=1-F_a$，$S(P)$ 与 §10 的 $\mathrm{Acc}$ 都表示加速比；此处 $s$ 的时间基准不同于 §14 在扩大问题的并行运行时间上定义的比例。

$$
T_P=T_1\left(s+\frac{1-s}{P}\right),\qquad
S(P)=\frac{T_1}{T_P}=\frac{1}{s+(1-s)/P}.
$$

Pour $s>0$, l'accélération tend vers $1/s$ lorsque $P$ augmente. C'est la conclusion centrale de la page 45, appliquant la section 10 au HPC. 当 $s>0$ 时，随着 $P$ 增大，加速比趋近 $1/s$。这是课件第 45 页的核心结论，也是前面第 10 节在 HPC 情景中的应用。

**Exemple.** Sur 100 secondes, 10 sont séquentielles. Avec 10 processeurs, le temps idéal vaut $10+90/10=19$ secondes, soit un speedup d'environ 5.26 ; ajouter des processeurs ne supprime pas ces 10 secondes. **例子。** 一个任务原来需要 100 秒，其中 10 秒必须串行。使用 10 个处理器后，理想时间是 $10+90/10=19$ 秒，加速比约为 5.26；再增加处理器，也无法消除那 10 秒串行工作。

Le modèle suppose une taille fixe et une référence séquentielle définie. Communications, synchronisation, ordonnancement et déséquilibre ajoutent des coûts à modéliser ; le nombre de cœurs n'invalide pas à lui seul la relation. 模型要求固定问题规模及明确的串行基准。实际通信、同步、调度与负载不均衡通常还会增加时间；大规模并行时应把这些因素单独建模。核心数量增加本身不会使 Amdahl 的关系失效。

### 20.2 Parallélisme explicite et implicite 显式并行与隐式并行（Parallélisme explicite / implicite）

Le cours appelle **explicite** le parallélisme organisé avec MPI ou OpenMP : tâches, données et coordinations doivent être exprimées. 课件把用 MPI、OpenMP 等明确组织的并行称为**显式并行**：程序需要表达任务划分、数据分配及必要的协调。

Le parallélisme dit **implicite** inclut jobs indépendants, tirages Monte Carlo et explorations paramétriques, souvent lançables en parallèle par un script ou un ordonnanceur. 课件所说的**隐式并行**包括多个独立作业、Monte Carlo 抽样和参数扫描。这些工作单元之间常有天然的独立性，可以由外部脚本或作业调度器并发启动。

> Terminologie du cours : « implicite » ne dispense pas d'organiser l'exécution et les flux aléatoires. MPI est une interface de communication, OpenMP une spécification de programmation parallèle, pas deux langages indépendants. 术语说明：这里沿用课件的分类。“隐式”并不表示无需组织执行；脚本、调度器和随机数流仍需要正确配置。MPI 是通信接口，OpenMP 是并行编程规范，不能简单理解为两种独立的编程语言。

### 20.3 Scale-up et Speed-up : préciser l'objectif Scale-up 与 Speed-up：先明确评估对象

Les pages 47–48 distinguent deux objectifs : 第 47–48 页从两种目标讨论扩展能力：

| Terme du cours 课件术语 | Question 关注的问题 | Grandeurs observables 可以观察的量 |
|---|---|---|
| Scale-up | Peut-on servir davantage de tâches, utilisateurs ou transactions identiques simultanément ? 能否同时支持更多相同任务、用户或事务？ | Capacité concurrente, tâches par seconde et temps de réponse 并发容量、每秒完成的任务数，以及相应响应时间 |
| Speed-up | Une tâche donnée peut-elle se terminer plus tôt ? 一项给定任务能否更早完成？ | Temps de réalisation et accélération par rapport à une référence 完成时间及相对于基准的加速比 |

**Exemple.** Exécuter simultanément 100 simulations indépendantes raccourcit le traitement du lot, sans nécessairement accélérer chaque simulation. Répartir une simulation sur plusieurs processeurs vise à accélérer celle-ci. **例子。** 把 100 个独立模拟从串行运行改为同时运行，整批任务会更早完成，但每个模拟自身未必变快。把一个模拟的计算拆给多个处理器，则是在缩短这个模拟的完成时间。

Ces notions ne correspondent pas directement au strong/weak scaling : ceux-ci définissent la variation de taille avec le nombre de processeurs, tandis qu'ici on distingue les objectifs de traitement. 课件中的 Scale-up 按上述含义理解；它与第 13 节的 strong/weak scaling 不构成一一对应关系。强弱扩展规定的是“处理器数变化时问题规模怎样变化”，这里讨论的是“希望改善哪一种任务完成能力”。

### 20.4 Exploration paramétrique et Monte Carlo 参数扫描与 Monte Carlo 的例子

**Exploration paramétrique.** Exécuter $n$ simulations indépendantes avec différents paramètres ; les distribuer peut raccourcir le délai global, mais collecte des résultats, chargement et contention coûtent encore du temps. **参数扫描（exploration paramétrique）。** 对同一程序使用不同输入参数，执行 $n$ 次相互独立的模拟。如果资源充足，可以将它们分发到多台机器，缩短全部结果收齐的时间。汇总结果、加载输入与资源竞争仍可能产生开销。

**Monte Carlo.** La page 49 illustre de nombreux essais indépendants. Distinguer : **Monte Carlo。** 第 49 页以大量无依赖试验为例。需要区分两种比较：

- Nombre total d'essais fixé : réduire le temps total. 固定试验总数：并行执行的目标是缩短总时间。
- Temps total fixé : davantage de ressources peuvent permettre plus d'essais et une estimation plus précise. 固定总时间：更多计算资源可能支持更多试验，改善估计精度。

Complément : pour des observations i.i.d. de variance finie, l'erreur standard de la moyenne décroît comme l'inverse de la racine du nombre d'échantillons. Le parallélisme n'améliore pas chaque échantillon ; éviter des séquences aléatoires dupliquées entre processus. 补充说明：对独立同分布、方差有限的样本均值，标准误差按样本数的平方根倒数下降。并行化本身不会提高每个样本的精度；应避免各工作进程重复使用相同的随机数序列。

### 20.5 Pourquoi certains codes passent-ils mieux à l'échelle ? 为什么有的代码更容易扩展？

La page 50 cite Linpack : certains codes exploitent bien les processeurs supplémentaires ; d'autres sont limités par les dépendances, le découpage ou la communication. 第 50 页用 Linpack 举例说明，有些代码能较好地利用新增处理器；其他代码可能受问题自身的依赖关系、划分方式或通信成本限制。

Quand le calcul par processeur diminue, échanges et synchronisations peuvent peser davantage. Questions à poser : 随着每个处理器分到的计算减少，数据交换和同步可能占据更大比例。分析时可以依次问：

1. Le travail parallélisable est-il suffisant ? 可并行的工作是否足够多？
2. La charge est-elle équilibrée ? 各处理器分到的工作是否均衡？
3. Peut-on recouvrir communication et calcul ? 通信能否与计算重叠？
4. Les synchronisations font-elles attendre les processeurs rapides ? 同步是否迫使较快的处理器等待？

Ces questions relient le speedup au comportement du programme. Voir l'[annexe](1_edpCpl_zh_annex.md) pour les communications, NUMA et les modèles. 这些问题把加速比曲线与程序行为联系起来。通信、NUMA 与模型的进一步说明见 [annex](1_edpCpl_zh_annex.md)。

## 21 Ensemble de travail, cache et localité 工作集、缓存命中与局部性（Workload-cache MISS/HIT）

> Correspondance : page 51. 对应课件第 51 页。

Une instruction ou donnée présente dans le cache étudié produit un hit ; sinon, un miss nécessite un accès à un niveau inférieur de la hiérarchie. 处理器需要的指令或数据如果已在所考察的缓存中，访问就是一次命中（hit）；否则发生缺失（miss），需要向更低一级存储层次取数据。

$$
\mathrm{miss\ ratio}=\frac{\text{缓存缺失次数}}{\text{对应的访问次数}}.
$$

Numérateur et dénominateur doivent concerner le même événement, niveau de cache et périmètre ; les taux de miss L1 et dernier niveau ne répondent pas à la même question. 分子和分母必须属于同一种事件、同一个缓存层级及同一测量范围。例如 L1 数据缓存缺失率与末级缓存缺失率回答的是不同问题。

### 21.1 Pourquoi un petit programme peut-il être plus rapide ? “程序很小”为什么可能更快？

Si les données réutilisées restent en cache, les accès suivants sollicitent moins les niveaux lents. Distinguer : 如果反复使用的数据能留在缓存中，后续访问可减少对更慢存储层次的请求。理解这里的“小”，需要区分：

- **Empreinte mémoire :** espace occupé par les instructions et les données. **内存占用（memory footprint）**：程序的指令和数据占据多少空间。
- **Ensemble de travail actif :** instructions et données réellement réutilisées pendant la phase étudiée. **活跃工作集（working set）**：在所考察阶段中实际反复使用的指令和数据。
- **Workload :** notion générale incluant tâches, tailles, accès et arrivées. **工作负载（workload）**：整门课中的广义概念，包括任务类型、规模、访问行为、到达方式等。

> Précision : la page 51 emploie workload pour l'espace occupé ; on l'interprète ici comme empreinte ou ensemble de travail. Un petit ensemble favorise les hits, sans supprimer misses initiaux, conflits ou interférences. 校注：第 51 页把指令和数据占用的空间简写为 workload。本节将其按内存占用和工作集的语境解释。工作集较小有利于缓存命中，但首次访问、映射冲突、其他线程干扰等仍可能产生 miss，不能承诺“程序小就全部命中”。

### 21.2 Comment la localité influence-t-elle les accès ? 局部性怎样影响访问？

- **Localité temporelle :** réutiliser rapidement une donnée récente, par exemple un petit tableau dans une boucle. **时间局部性**：近期使用的数据很快再次使用，例如在循环中重复使用一个小数组。
- **Localité spatiale :** accéder rapidement à des adresses voisines, comme lors d'un parcours séquentiel. **空间局部性**：使用某个地址后，很快使用邻近地址，例如顺序遍历数组。

Les instructions répétées ont souvent une bonne localité ; les données nécessitent une optimisation adaptée. Le blocage vise notamment à réutiliser les données avant leur éviction. 课件指出，反复执行的指令往往有较好的局部性；数据访问则需要结合应用调优。分块处理的一个目的，就是让某一批数据在被逐出缓存前完成更多有用工作。

**Exemple.** La même boucle sur un petit tableau ou un tableau dépassant le cache peut solliciter différents niveaux mémoire ; documenter taille et état des caches. **例子。** 顺序处理一个小数组和一个远大于缓存的大数组，即使执行相同的循环语句，也可能访问不同的存储层次。因此比较结果时必须记录数组规模和缓存状态。

## 22 Latence, bande passante, utilisation et autres métriques HPC HPC 中的延迟、带宽、利用率与其他指标

> Correspondance : pages 52–53, Latence / Débit / Taux et Autres métriques. 对应课件第 52–53 页：Latence / Débit / Taux，Autres métriques。

| Métrique 指标 | Question 回答的问题 | Exemples et limites 例子及解释边界 |
|---|---|---|
| Latence 延迟（latence） | Durée entre émission et achèvement d'une opération ? 一个操作从发出到完成要多久？ | Accès mémoire, aller-retour réseau, réponse d'une base de données 内存访问、网络消息往返、数据库请求响应 |
| Débit ou bande passante 吞吐量或带宽（débit） | Travail ou données transférées par unité de temps ? 单位时间完成多少工作或传输多少数据？ | GB/s, Gb/s, FLOP/s ; distinguer octets B et bits b GB/s、Gb/s、FLOP/s；须区分字节 B 与比特 b |
| Utilisation 利用率（taux d'utilisation） | Degré d'occupation pendant l'observation ? 某资源在观察期内被使用到什么程度？ | Temps CPU occupé, occupation du lien ; définition selon la ressource et l'outil CPU 忙碌时间比例、链路占用等；计数口径因资源和工具而异 |

**Faible latence et forte bande passante sont deux objectifs distincts.** Des accès dépendants peuvent attendre chaque requête, tandis que des accès concurrents saturent la bande passante. Estimer la latence par la moitié d'un aller-retour ping-pong suppose notamment des trajets et surcoûts approximativement symétriques. **延迟低与带宽高是不同目标。** 单个依赖性访存可能受每次请求的等待时间影响；大量可并发请求则可能把数据通路的带宽占满。课件用网络 ping-pong 往返时间除以 2 近似单程延迟，这依赖往返路径和处理开销近似对称等条件。

La page 53 mentionne également efficacité, fiabilité, disponibilité, performance/prix et performance/puissance : 第 53 页还列出效率、可靠性、可用性、性能/价格及性能/功耗：

- Le rapport performance mesurée/pic théorique décrit la fraction du pic atteinte ; le distinguer de l'efficacité parallèle $S(P)/P$. 测得性能与相应理论峰值之比，描述达到峰值的程度。应与第 11 节的并行效率 $S(P)/P$ 区分。
- La fiabilité concerne erreurs et défaillances ; la disponibilité mesure le temps de service, comme aux sections 15–16. 可靠性关注错误或故障；可用性关注可提供服务的时间比例，定义沿用第 15–16 节。
- Comparer performance/prix sur un périmètre de coût cohérent ; performance/puissance peut s'exprimer en FLOP/s/W, mais l'énergie totale dépend aussi de la durée. 性能/价格需要使用可比的成本范围；性能/功耗可用 FLOP/s/W 表示。一次任务的总能耗还取决于运行时间。

> Précision : saturation, goulot et chemin critique sont distincts. Une forte utilisation mérite examen, sans prouver à elle seule une limitation globale ; le chemin critique est la chaîne de dépendances déterminant l'achèvement. 校注：课件把资源饱和与瓶颈、关键路径并列提示。资源接近饱和值得调查，但关键路径是决定完成时间的依赖链，两者概念不同；某项利用率高也不能单独证明它限制了整个应用。

## 23 Identifier les goulots de performance 判断程序的性能瓶颈（xxx-bound）

> Correspondance : pages 54–57. 对应课件第 54–57 页。

### 23.1 Classer selon la ressource limitante 用“限制在哪里”理解分类

| Catégorie 类别 | Limitation principale 主要限制 | Exemple 用于理解的例子 |
|---|---|---|
| CPU / compute-bound | Capacité d'exécution d'instructions ou d'opérations 处理器执行指令或运算的能力 | Noyau arithmétique avec bonne réutilisation des données 数据复用充分、算术运算密集的计算内核 |
| Memory bandwidth-bound | Débit de transfert au niveau mémoire étudié 所考察内存层次的数据传输速率 | Parcours de grands tableaux avec peu de calcul 对大数组进行连续读写，运算相对较少 |
| Memory latency-bound | Données trop lentes à revenir et attente difficile à masquer 所需数据返回得不够快，且难以用其他工作隐藏等待 | Parcours de pointeurs avec adresses dépendantes 下一次地址依赖上一次结果的指针追踪 |
| I/O-bound | Bande passante ou latence du stockage et des chemins I/O 存储或其他 I/O 路径的带宽、延迟等 | Gros fichiers ou nombreuses petites requêtes 频繁读写大文件或大量小请求 |

> Précision : la page 54 simplifie CPU-bound par la fréquence et associe memory-bound aux misses. Vérifier aussi débit d'instructions, dépendances, concurrence mémoire et caches ; un taux de miss élevé n'est qu'un indice. 校注：第 54 页把 CPU-bound 简化为受 CPU 频率限制，把 memory-bound 与高 miss 率关联。实际诊断还要看指令吞吐、依赖关系、访存并发及缓存层级等因素。高 miss 率是线索，不能单独作为内存瓶颈的判据。

### 23.2 I/O-bound : localiser le temps d'entrée-sortie I/O-bound：先确认 I/O 时间花在哪里

La page 55 cite `iostat`, parallélisation I/O, striping, SSD et changements d'architecture. 第 55 页提到 `iostat`、并行化 I/O、条带化（striping）、SSD 和架构调整。

Ces options répondent à différentes limites : striping pour répartir les transferts, faible latence pour les petites requêtes, regroupement ou réduction des I/O. Identifier d'abord périphérique, système de fichiers, réseau ou motif d'accès. 这些是不同方向：条带化可把数据分散到多个设备，增大顺序传输的并发能力；更低延迟的设备可能改善小请求；应用也可能通过合并请求或减少重复 I/O 获益。选择前应确认限制来自设备、文件系统、网络还是访问方式。

Éviter les limitations I/O est un objectif HPC, mais une application de données peut comporter des phases I/O importantes ; cela ne prouve pas une erreur de conception. 课件认为 HPC 计算节点应尽量避免被 I/O 限制，这是一种优化目标；数据密集应用确实可能包含重要的 I/O 阶段，不能仅因出现 I/O 瓶颈就认定程序设计错误。

### 23.3 Pourquoi 100 % CPU ne suffit-il pas au diagnostic ? CPU 显示 100%，为什么还不能下结论？

La page 56 propose de modifier la fréquence et d'observer la performance : 第 56 页提出的诊断办法是改变处理器频率，再观察应用性能如何变化：

- Une amélioration sensible avec la fréquence suggère une limitation de calcul. 性能随频率明显改善，提示处理器计算能力可能在限制该阶段。
- Une faible variation suggère d'autres ressources à examiner, notamment la mémoire. 性能变化很小，提示限制可能在其他资源，需要继续检查内存等因素。

L'utilisation CPU décrit surtout l'occupation et l'ordonnancement. Attentes mémoire et attente active peuvent compter comme temps CPU : **100 % CPU ne signifie pas calcul au pic**. CPU 利用率主要反映调度和忙碌状态；线程等待访存、执行忙等待时，也可能继续被计入 CPU 时间。因此 **100% CPU 不等于已经达到计算峰值**。

Complément : contrôler taille, threads, affinité, température et autres charges, et relever la fréquence réelle. Cache, contrôleur mémoire et politique de puissance interviennent aussi ; l'insensibilité à la fréquence ne prouve pas memory-bound. 补充说明：频率实验需要控制数据规模、线程数、绑定、温度和其他负载，并记录实际频率。缓存、内存控制器与功耗策略可能同时影响结果；“对频率不敏感”也可能来自 I/O、同步或其他限制，不能直接确诊 memory-bound。

### 23.4 Le goulot dépend du programme, de l'entrée et de la machine 瓶颈是“程序、输入和机器”的共同结果

La page 57 souligne deux variations : 第 57 页强调两个变化：

1. Une taille différente peut faire dépasser la capacité du cache et changer la limitation. 数据规模改变时，工作集可能从能装入缓存变为装不下，性能限制随之变化。
2. Un autre processeur peut modifier le rapport calcul/bande passante et donc le goulot. 更换处理器后，算力和带宽的相对关系可能改变，同一程序会表现出不同的限制。

Qualifier la limitation pour une machine, une entrée et une configuration précises. Le [complément Roofline](1_edpCpl_zh_annex.md#annex-roofline) aide à comparer calcul et bande passante. 所以应写“该程序在某台机器、某个输入规模和配置下受某资源限制”，而不是给程序永久贴一个标签。原笔记的 [Roofline 扩展](1_edpCpl_zh_annex.md#annex-roofline)可用于进一步理解算力与带宽之间的关系。

## 24 Mesurer les métriques classiques : STREAM et calcul flottant 测量经典性能指标：STREAM 与浮点性能

> Correspondance : pages 58–59. 对应课件第 58–59 页。

### 24.1 Que mesure STREAM ? STREAM 在测什么？

STREAM caractérise la bande passante mémoire soutenue avec des opérations sur tableaux. Le tableau compte les lectures et écritures utiles de l'algorithme pour des éléments de 8 octets : STREAM 用简单数组操作刻画持续内存带宽。各操作计算规则清楚，便于说明一次迭代需要搬运多少数据。下表按每个元素为 8 字节、算法需要的数据读写量计数：

| Noyau 内核 | Forme du cours 课件形式 | Accès par élément 每元素读写 | Octets utiles 有效字节数 | Opérations flottantes 浮点运算数 |
|---|---|---|---:|---:|
| Copy | `c[i] = a[i]` | Une lecture, une écriture 一读一写 | 16 B | 0 |
| Scale | `c[i] = scalar * a[i]` | Une lecture, une écriture 一读一写 | 16 B | 1 |
| Add | `c[i] = a[i] + b[i]` | Deux lectures, une écriture 两读一写 | 24 B | 1 |
| Triad | `c[i] = a[i] + scalar * b[i]` | Deux lectures, une écriture 两读一写 | 24 B | 2 |

Une multiplication et une addition comptent pour 2 FLOP, même avec une instruction FMA. La réduction `Tot = Tot + a[i]` est un exemple supplémentaire, distinct des quatre noyaux STREAM standard. 这里按惯例将一次乘法加一次加法计为 2 FLOP，即使编译器使用一条 FMA 指令。课件还列出 `Tot = Tot + a[i]` 的读访问归约例子；它是额外的测试思路，不属于上表的四个标准 STREAM 内核。

Calcul de la bande passante effective $B_{\mathrm{eff}}$ : si $V_{\mathrm{utile}}$ est le volume utile en octets et $T_{\mathrm{exec}}$ la durée en secondes, elle s'exprime en octets/s. 有效带宽记为 $B_{\mathrm{eff}}$；设算法规定的有效读写量为 $V_{\mathrm{utile}}$ 字节、执行时间为 $T_{\mathrm{exec}}$ 秒，则单位为字节/秒：

$$
B_{\mathrm{eff}}=\frac{V_{\mathrm{utile}}}{T_{\mathrm{exec}}}.
$$

**Exemple pédagogique.** Triad sur $10^7$ doubles transfère $24\times10^7$ octets utiles ; en 0.01 seconde, cela donne 24 GB/s décimaux. Ce sont des données de calcul, pas une mesure locale. **教学算例。** Triad 处理 $10^7$ 个双精度元素，有效流量为 $24\times10^7$ 字节；如果耗时 0.01 秒，则有效带宽为 24 GB/s（十进制单位）。这是演算数据，不是本机实测结果。

### 24.2 Trafic utile et trafic réel du bus mémoire 有效流量与实际内存总线流量

Les caches modifient le trafic réel : le write-allocate peut lire la ligne cible avant écriture ; certaines instructions ou politiques évitent cette lecture supplémentaire. 缓存策略会改变实际流量。例如普通缓存写入发生 write-allocate 时，写入目标缓存行可能先被读入；特定写指令与缓存策略可能避免这次额外读取。

La remarque « écriture comptée deux fois » de la page 58 dépend du chemin d'accès. Distinguer octets utiles, lectures de lignes et écritures de retour ; ne pas mélanger leurs débits. Voir la [référence STREAM](https://www.cs.virginia.edu/stream/ref.html). 因此第 58 页“写可能算两次”的提示需要结合访问路径理解：上表使用算法有效字节数；若分析实际总线流量，需要另说明缓存行读取、回写等开销。不能把两个口径混在同一个带宽结果中。[STREAM 官方参考](https://www.cs.virginia.edu/stream/ref.html)明确区分这些字节计数方式。

Pour mesurer la mémoire principale, utiliser assez de données et examiner le plateau de bande passante avec les threads. De petits tableaux peuvent mesurer surtout le cache ; la progression n'est pas toujours linéaire. 测量主存带宽时还要使用足够大的数据，并观察线程数增加后是否达到带宽平台；过小的数组可能主要测到缓存，多线程也不保证带宽一直线性增长。

### 24.3 Pourquoi contextualiser MFLOPS et MIPS ? MFLOPS / MIPS 为什么仍要配合上下文？

La page 59 rappelle l'influence du mélange d'instructions, de la vectorisation et de l'alimentation en données ; des programmes équivalents peuvent utiliser des instructions différentes. 第 59 页回到前半部分的提醒：浮点指令在程序中的比例、向量化和数据供给都会影响观测结果。两个程序即使完成相同任务，也可能使用不同数量与类型的指令。

Calculer les FLOP/s à partir des opérations flottantes réellement effectuées et de leur durée, pas du nombre total d'instructions. Les MIPS restent des millions d'instructions par seconde ; comparer tâche, taille, précision, correction et durée. 实际 FLOP/s 应由所完成的浮点运算数和相应执行时间计算，不能把所有指令数都当成浮点运算。MIPS 的课件戏称用于提醒比较陷阱；正式定义仍是每秒百万条指令。比较应用实现时，应同时报告任务、规模、精度或正确性要求及完成时间。

## 25 Microbenchmarks et compteurs matériels 获取性能证据：微基准与硬件计数器

> Correspondance : pages 60–61. 对应课件第 60–61 页。

### 25.1 Poser une question assez précise 先问一个足够具体的问题

Un microbenchmark isole un facteur : parcourir un grand tableau explore la bande passante ; enchaîner des adresses dépendantes réduit le recouvrement et explore la latence. Un même volume de données ne garantit pas la même grandeur mesurée. 微基准（microbenchmark）用于尽量隔离一个因素。例如，连续访问大数组可以观察带宽，而让后一次访存地址依赖前一次结果，可以减少访存重叠，帮助研究延迟。两种程序即使访问同样多的数据，也未必测到同一个量。

La page 60 cite Perfmon, Perfctr et PAPI comme repères ; événements et interfaces dépendent de la plateforme. PAPI fournit une interface d'accès multiplateforme aux compteurs : [présentation officielle](https://icl.utk.edu/papi/). 第 60 页列出硬件计数器接口与工具名称，如 Perfmon、Perfctr、PAPI。这里保留它们作为课件检索线索；具体事件与可用接口须以使用的平台为准。PAPI 提供跨平台访问性能计数信息的接口，见 [PAPI 官方说明](https://icl.utk.edu/papi/)。

### 25.2 Que peut-on lire dans les compteurs ? 从计数器读出什么？

| Événement 课件列出的事件 | Question possible 可以帮助回答的问题 | Points à vérifier 解释时要核对 |
|---|---|---|
| Cycles 周期数 | Combien de cycles consomme une phase ? 某段程序消耗多少处理器周期？ | Cycles cœur ou référence, effet de la fréquence 核心周期与参考周期的定义，以及频率变化 |
| Cycles de blocage 停顿周期（stalled cycles） | Quelles étapes sont bloquées ? 执行在哪些阶段受阻？ | Définition et recouvrements ; ne pas additionner arbitrairement 事件定义与重叠关系；不同停顿计数不能随意相加 |
| Instructions, instructions flottantes 指令数、浮点指令数 | Combien et quels types d'instructions ? 执行了多少、哪类指令？ | Instructions retirées ou autre comptage, largeur vectorielle, FMA 已退休还是其他计数口径，向量宽度及 FMA |
| Load / store | Combien de lectures et écritures ? 进行了多少读写操作？ | Opérations distinctes des octets mémoire ; hits possibles 操作数不等于实际内存字节数，访问可能命中缓存 |
| Branches et mauvaises prédictions 分支及预测失败 | Surcoût du contrôle de flux ? 控制流是否造成额外开销？ | Branches totales et mauvaises prédictions 分支总数与预测失败数的区别 |
| Défauts de cache 缓存缺失 | Quel niveau peut limiter l'alimentation ? 哪个层级的数据供给可能有问题？ | Distinguer nombre, taux et défauts par instruction 缺失次数、缺失率和每条指令的缺失数分母不同 |

Complément : ces questions orientent l'analyse ; elles ne garantissent ni des événements homonymes sur tout processeur, ni un diagnostic causal par un seul compteur. Lire leurs définitions matérielles et logicielles. 补充说明：表中的问题是分析方向，不保证某台处理器有同名事件，也不保证单个计数器能确定根因。应先读硬件及工具对事件的定义。

### 25.3 Pourquoi mesurer par groupes ? 为什么需要分批测量？

Les événements sont nombreux mais les compteurs physiques simultanés limités. Répéter le même workload avec des groupes d'événements, en gardant entrées, phase et environnement aussi constants que possible. 硬件可观察的事件种类很多，但可同时使用的物理计数器数量有限。课件建议对同一工作负载重复测量，每次观察一组事件；重复时要尽量保持输入、执行阶段和环境一致。

Le multiplexage mesure alternativement différents événements, puis estime ou extrapole les résultats ; il ajoute surcoût et limites de couverture, notamment si les phases changent. Voir le [guide PAPI](https://icl.utk.edu/projects/papi/files/documentation/PAPI_USER_GUIDE.htm). 工具也可能采用事件多路复用（multiplexing），在时间上轮流测量不同事件，再对结果估计或缩放。这样会引入开销和采样覆盖限制，程序阶段变化也可能影响解释。参见 [PAPI 用户指南的 multiplexing 说明](https://icl.utk.edu/projects/papi/files/documentation/PAPI_USER_GUIDE.htm)。

### 25.4 Construire une explication vérifiable 把线索串成可检验的解释

**Exemple pédagogique.** Pour un parcours lent, mesurer durée, misses et bande passante. Une bande passante proche d'un microbenchmark comparable soutient l'hypothèse d'une limitation de débit ; sinon examiner dépendances, parallélisme et synchronisation. **教学例子。** 如果发现大数组遍历很慢，可以先测完成时间，再观察缓存缺失和内存带宽。如果带宽接近同条件微基准的可持续水平，带宽限制的解释更有支持；如果带宽很低，则还要检查访问依赖、并行度、同步和其他开销。

Modifier ensuite disposition ou réutilisation des données, puis vérifier l'évolution attendue du temps et des compteurs. Des misses nombreux ou un CPU occupé ne suffisent pas à conclure. 随后改变一个相关因素，例如数据布局或复用方式，再看时间与计数器是否按预期变化。优化结论需要这些相互支持的证据；“miss 很多”或“CPU 很忙”只完成了观察的第一步。

## 26 Comparer et interpréter les résultats 如何比较和解释性能结果（Benchmarks et comparaison）

> Correspondance : page 62. 对应课件第 62 页。

Une valeur prend son sens par comparaison. Comme pour les masses astronomiques, il faut une échelle : ancienne version, exécution séquentielle, autre implémentation ou référence comparable. 一个数值要结合参照对象，才能回答实际问题。课件用天体质量比较举例：知道某个对象的质量之外，还需要一个尺度来理解它的大小。在性能分析中，相应的尺度可能是旧版本、单线程运行、另一种实现或同条件基准。

Préciser au minimum : 比较前至少说明：

- **Tâche :** calcul réalisé, taille d'entrée, précision et comparabilité des résultats. **任务**：完成了什么计算，输入规模、精度和结果是否可比。
- **Environnement :** machine, threads ou processus, compilation et configuration. **环境**：机器、线程或进程数、编译选项和相关运行配置。
- **Référence :** comparateur, unités, périmètre chronométré et conventions de comptage. **基准**：与谁比较，指标的单位、计时范围和字节/运算计数口径。
- **Variabilité :** répétitions et distribution, sans sélectionner uniquement le meilleur cas. **波动**：重复运行的次数与结果分布，避免只挑最好的一次。
- **Interprétation :** observations, preuves et conditions pouvant modifier la conclusion. **解释**：观察到什么、哪些证据支持当前判断、在哪些条件下结论可能变化。

**Exemple ajouté.** 0.2 seconde renseigne sur une échéance ; pour un gain, fournir aussi l'ancien temps comparable. Avec 0.4 seconde auparavant, le speedup vaut 2 ; vérifier correction, taille et précision. **补充例子。** “耗时 0.2 秒”可以用于判断是否满足时限；若要说明优化收益，还要给出相同条件下的旧时间。若旧时间为 0.4 秒，新实现的加速比为 2。随后仍要检查结果正确性，以及是否改变了问题规模或精度。

Cette partie relie parallélisme et accès aux données aux métriques, limitations et preuves mesurées. Les modèles, outils et préparations des cours suivants sont dans l'[annexe](1_edpCpl_zh_annex.md). 本课后半部分的主线是：从并行结构与数据访问出发，选择有意义的指标，定位可能的限制，再用测量和可比基准解释结果。更深入的模型、工具概览与后续课程预习材料集中放在 [第一课 annex](1_edpCpl_zh_annex.md)。

## Correspondance avec le PDF 课件页码对照

Pagination physique du PDF de 62 pages. Les sections 1–18 conservent les notes antérieures ; les sections 19–26 suivent les ajouts actuels. 页码为当前 62 页 PDF 的物理页。第 1–18 节保留原笔记正文；第 19–26 节按今年新增部分重组。

| Section des notes 中文正文 | Pages du cours 教师课件页码 | Titre de recherche en français 法文检索标题 |
|---|---|---|
| Section 19 第 19 节 | 42–43 | Evaluation des performances pour le HPC : Plan；Objectifs |
| Section 20 第 20 节 | 44–50 | Parallélisme et performance；Amdahl；Scale-UP；SPEED-UP |
| Section 21 第 21 节 | 51 | Workload-cache MISS/HIT |
| Section 22 第 22 节 | 52–53 | Latence/Débit/Taux；Autres métriques |
| Section 23 第 23 节 | 54–57 | xxx-bound；IO-bound；100% CPU；Considérations memory/CPU-bound |
| Section 24 第 24 节 | 58–59 | Evaluation des métriques classiques |
| Section 25 第 25 节 | 60–61 | Obtenir les valeurs；Compteurs de performance |
| Section 26 第 26 节 | 62 | Benchmarks et comparaison |
