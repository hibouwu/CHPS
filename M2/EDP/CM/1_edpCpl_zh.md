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

**Complément.** En présence d'aléas et de files d'attente (cf. CM3), lorsque le débit approche la capacité nominale et que l'utilisation $\rho$ tend vers $1$, le temps d'attente croît fortement (par exemple $\bar{R} \propto \frac{1}{1-\rho}$ pour une file M/M/1). Les contraintes de temps de réponse et les fluctuations de charge font donc généralement que la capacité d'usage $X_{\max}$ (telle que $R(X_{\max}) \le R_{\mathrm{cible}}$) reste inférieure à la capacité nominale. **补充说明。** 在存在随机波动与排队等待的系统中（见 CM3），当吞吐量逼近名义容量、利用率 $\rho \to 1$ 时，排队等待时间会急剧上升（例如 M/M/1 队列中 $\bar{R} \propto \frac{1}{1-\rho}$）。因此受响应时间上限 $R(X_{\max}) \le R_{\mathrm{cible}}$ 与负载波动的约束，实际可用容量通常低于理想名义容量。

## 9 MIPS et MFLOPS MIPS 与 MFLOPS

Avec $N_{\mathrm{inst}}$ instructions exécutées en $T_{\mathrm{exec}}$ secondes, les MIPS (millions d'instructions par seconde) valent : 设执行指令数为 $N_{\mathrm{inst}}$、执行时间为 $T_{\mathrm{exec}}$ 秒，则 MIPS（每秒百万条指令）为：

$$
\mathrm{MIPS} = \frac{N_{\mathrm{inst}}}{10^{6}T_{\mathrm{exec}}}
$$

Les MFLOPS comptent les millions d'opérations flottantes par seconde ; une instruction vectorielle ou FMA peut représenter plusieurs opérations. MFLOPS 统计每秒完成的百万次浮点运算；运算数不一定等于浮点指令数，例如向量指令和融合乘加（FMA）。

En notant $N_{\mathrm{FLOP}}$ le nombre d'opérations flottantes, $\mathrm{MFLOPS}=N_{\mathrm{FLOP}}/(10^6T_{\mathrm{exec}})$. Une FMA scalaire compte pour deux opérations, une multiplication et une addition. 浮点运算总数记为 $N_{\mathrm{FLOP}}$，则 $\mathrm{MFLOPS}=N_{\mathrm{FLOP}}/(10^6T_{\mathrm{exec}})$。标量 FMA 的一次乘法和一次加法合计为 2 次浮点运算。

Remarques : 说明：

- Les deux unités sont évaluées ici sous l'hypothèse simplificatrice que les instructions sont déjà en mémoire. 此处讨论采用简化测量条件，假设指令已全部在内存中（不计缺页或外存加载开销；这是简化测试前提，而非单位本身的定义要求）。
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

**Complément (dérivation et comparaison avec Amdahl).** Dans le cas idéal (sans surcoût de communication ni déséquilibre, ce qui donne l'égalité dans la borne ci-dessus), supposons que sur $P$ processeurs le problème agrandi prenne un temps total $T_P$, dont une fraction $s$ est séquentielle ($s T_P$, ex. initialisation et I/O qui ne croissent pas avec la taille) et une fraction $(1-s)$ est parfaitement parallèle ($(1-s)T_P$). Si un seul processeur devait exécuter ce même problème agrandi, la partie parallèle lui prendrait $P$ fois plus de temps :
$$
T_1' = s T_P + P(1-s)T_P.
$$
L'accélération mise à l'échelle (scaled speedup) vaut donc :
$$
\mathrm{Acc}(n, P) = \frac{T_1'}{T_P} = s + P(1-s) = P + (1-P)s.
$$
La différence fondamentale réside dans le **dénominateur de la fraction séquentielle** et le mode de passage à l'échelle :
- **Amdahl (strong scaling, taille $n$ fixée)** : $s_{\mathrm{Amdahl}} = 1 - F_a = \frac{T_{\mathrm{seq}}}{T_1}$ est mesuré sur $1$ processeur ; quand $P$ augmente, le temps parallèle $F_a T_1 / P$ rétrécit tandis que $T_{\mathrm{seq}}$ reste fixe.
- **Gustafson (weak scaling, travail par processeur quasi constant)** : $s = \frac{T_{\mathrm{seq}}}{T_P}$ est mesuré sur $P$ processeurs ; on maintient le travail parallèle par processeur (et donc $(1-s)T_P$) approximativement constant en augmentant la taille $n$ avec $P$ (soit $n \propto P$ si $n$ mesure le travail total, mais $n \propto P^{1/3}$ si le travail croît en $O(n^3)$ comme pour un produit matriciel $n\times n$), ce qui dilue le poids du code séquentiel dans le travail total $T_1'$. À problème et hypothèses d'exécution fixés, les deux fractions se convertissent d'ailleurs exactement l'une dans l'autre : Gustafson ne contredit pas Amdahl, il répond à une question d'échelle différente. **补充说明（推导及与 Amdahl 的本质区别）。** 在无额外通信与负载失衡开销的理想情况下（此时上式取等号），设扩大后的问题在 $P$ 个处理器上总耗时为 $T_P$，其中串行阶段耗时 $s T_P$（如不随问题规模膨胀的初始化等），并行阶段耗时 $(1-s)T_P$。若将这同一个扩大后的问题放到单处理器上串行执行，并行部分耗时将放大 $P$ 倍：
$$
T_1' = s T_P + P(1-s)T_P.
$$
由此得到扩展加速比（scaled speedup）：
$$
\mathrm{Acc}(n, P) = \frac{T_1'}{T_P} = s + P(1-s) = P + (1-P)s.
$$
两定律的核心区别在于**串行比例的分母基准与扩展方式不同**：
- **Amdahl（强扩展，固定规模 $n$）**：串行比例 $s_{\mathrm{Amdahl}} = 1 - F_a = \frac{T_{\mathrm{seq}}}{T_1}$ 以单核时间 $T_1$ 为分母；随 $P$ 增大，并行耗时 $\frac{F_a T_1}{P}$ 不断缩小，导致串行部分成为瓶颈。
- **Gustafson（弱扩展，保持单核工作量近似不变）**：串行比例 $s = \frac{T_{\mathrm{seq}}}{T_P}$ 以 $P$ 核并行时间 $T_P$ 为分母；通过随 $P$ 扩大问题规模 $n$ 使每个处理器的工作量（即并行耗时 $(1-s)T_P$）保持近似恒定（若 $n$ 直接代表总计算量则为 $n \propto P$；若如 $n\times n$ 矩阵乘法总计算量为 $O(n^3)$ 则对应 $n \propto P^{1/3}$），从而在总工作量 $T_1'$ 中稀释了串行开销的占比。对于同一具体问题和执行假设，这两个串行比例在代数上可以互相换算，因此 Gustafson 定律并非推翻 Amdahl 定律，而是刻画了随核数扩大问题规模时的加速潜力。

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
- **MTBF** (Mean Time Between Failures) : durée moyenne entre défaillances successives d'un système réparable ; préciser si les temps de réparation sont inclus. 可修复系统两次相邻失效之间的平均时长（使用时须明确是否包含修复停机时间）。

**Complément (relation entre uptime, downtime, MTTF, MTTR, MTBF, disponibilité et fiabilité).** En notant $\mathrm{uptime}$ la durée moyenne de bon fonctionnement ($\mathrm{MTTF}$) et $\mathrm{downtime}$ la durée moyenne de réparation ou d'indisponibilité ($\mathrm{MTTR}$, *Mean Time To Repair*), la disponibilité stationnaire s'écrit :
$$
A = \frac{\mathrm{uptime}}{\mathrm{uptime} + \mathrm{downtime}} = \frac{\mathrm{MTTF}}{\mathrm{MTTF} + \mathrm{MTTR}}.
$$
Attention aux deux conventions courantes pour le **MTBF** : lorsqu'on définit le MTBF comme la période moyenne d'un cycle complet entre deux pannes successives incluant la réparation ($\mathrm{MTBF} = \mathrm{MTTF} + \mathrm{MTTR}$), on a $A = \frac{\mathrm{MTTF}}{\mathrm{MTBF}}$ ; en revanche, certaines normes d'ingénierie (ex. NIST) définissent le MTBF comme le seul temps de fonctionnement cumulé divisé par le nombre de pannes (hors temps de réparation, soit l'équivalent du MTTF pour un système réparable). Enfin, ne pas confondre **fiabilité** et **disponibilité** : un système qui tombe en panne toutes les heures ($\mathrm{MTTF} = 1\text{ h}$) mais redémarre en $1\text{ ms}$ ($\mathrm{MTTR} \approx 0$) a une **disponibilité** $A \approx 100\%$, mais une **fiabilité** $R_{\mathrm{rel}}(T)$ très faible sur une mission de $T = 24\text{ h}$ (car une exécution HPC sans checkpointing sera interrompue dès la première panne). **补充说明（uptime、downtime、MTTF、MTTR、MTBF 与可用性、可靠性的关系）。** 设可修复系统每次正常运行的平均时长为 $\mathrm{uptime} = \mathrm{MTTF}$，每次故障修复停机的平均时长为 $\mathrm{downtime} = \mathrm{MTTR}$（Mean Time To Repair），则稳态可用性为：
$$
A = \frac{\mathrm{uptime}}{\mathrm{uptime} + \mathrm{downtime}} = \frac{\mathrm{MTTF}}{\mathrm{MTTF} + \mathrm{MTTR}}.
$$
需注意工程文献中 **MTBF** 的两种常见口径：若将 MTBF 定义为两次相邻故障起点之间包含修复时间在内的完整周期（即 $\mathrm{MTBF} = \mathrm{MTTF} + \mathrm{MTTR}$），则可写作 $A = \frac{\mathrm{MTTF}}{\mathrm{MTBF}}$；但也有部分标准（如 NIST）将 MTBF 定义为不含修复停机时间的累计正常运行时间除以失效次数（此时它与可修复系统的 MTTF 同义）。此外，切勿混淆**可靠性**与**可用性**：如果一台机器每小时崩溃一次（$\mathrm{MTTF} = 1\text{ h}$），但每次只需 $1\text{ ms}$ 即可瞬间重启恢复（$\mathrm{MTTR} \approx 0$），则它的**可用性** $A \approx 100\%$ 极高，但在 $T = 24\text{ h}$ 内的**可靠性** $R_{\mathrm{rel}}(T)$ 极低（未做检查点容错的 HPC 长作业只要遇到一次崩溃就会前功尽弃）。

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

**Complément (explication du paradoxe Whetstone).** En utilisant $N_{\mathrm{inst}} = \mathrm{MIPS} \times 10^6 \times T_{\mathrm{exec}}$, on retrouve le nombre total d'instructions exécutées dans chaque configuration :
- Avec coprocesseur : $N_{\mathrm{inst}} = 1.6 \times 10^6 \times 1.08 \approx 1.73 \times 10^6$ instructions (les opérations flottantes sont prises en charge directement par les instructions matérielles du coprocesseur).
- Sans coprocesseur : $N_{\mathrm{inst}} = 2.7 \times 10^6 \times 13.6 \approx 36.7 \times 10^6$ instructions (en l'absence de coprocesseur, chaque opération flottante doit être émulée en logiciel par une séquence de nombreuses instructions entières plus simples).
La configuration sans coprocesseur exécute donc environ $21.25$ fois plus d'instructions à un débit d'instructions par seconde plus élevé ($2.7$ vs $1.6\text{ MIPS}$), mais met $12.6$ fois plus de temps pour accomplir le même programme. **补充说明（Whetstone 悖论的定量解释）。** 由 $N_{\mathrm{inst}} = \mathrm{MIPS} \times 10^6 \times T_{\mathrm{exec}}$ 可以反推出两种配置实际执行的指令总数：
- 有浮点协处理器：$N_{\mathrm{inst}} = 1.6 \times 10^6 \times 1.08 \approx 1.73 \times 10^6$ 条指令（浮点运算直接由协处理器指令完成，总指令数很少）。
- 无浮点协处理器：$N_{\mathrm{inst}} = 2.7 \times 10^6 \times 13.6 \approx 36.7 \times 10^6$ 条指令（缺少硬件协处理器时，每次浮点运算需通过软件库由多条简单整数指令模拟实现）。
无协处理器时执行了约 $21.25$ 倍数量的指令，每秒指令吞吐数看似更高（$2.7 > 1.6\text{ MIPS}$），但完成同一任务的总时间却慢了约 $12.6$ 倍。

### 17.3 Déterminisme 确定性

Un test répété devrait donner la même valeur de métrique (en pratique, une bonne répétabilité sous conditions contrôlées, en documentant la variabilité observée). 理想情况下，重复测试应得到相同指标值（在实际系统测量中，要求在受控条件下具有良好可重复性，并如实报告多次测量的波动范围）。

### 17.4 Facilité de mesure 易测性

Une métrique difficile à mesurer risque d'être erronée et sera moins utilisée. 难以测量的指标容易引入测量误差，因此较少被采用。

## 18 Méthodes d'évaluation des performances 性能评估方法

Trois méthodes : 三类方法：

- **Modélisation analytique 数学建模** : abstraire le système en variables et équations pour calculer des indicateurs sous des hypothèses explicites. 将系统抽象为变量和方程，在明确假设下计算性能指标。
- **Simulation 仿真** : exécuter un modèle pour suivre son comportement dans des configurations choisies ; elle nécessite généralement moins d'hypothèses simplificatrices que la modélisation analytique, mais demande davantage de temps de développement et d'exécution. 运行系统模型以观察其在指定配置与输入下的演化；仿真所需的简化假设通常少于解析建模，但往往更耗时。
- **Mesure 实测** : observer une exécution réelle pour obtenir durées, événements et débits. 观察真实运行，获得执行时间、事件数量和吞吐量等数据。

Critères de choix : 选择依据包括：

- Existence du système 系统是否已存在
- Coût temporel 时间成本
- Budget 预算
- Précision souhaitée 所需精度

Si le système existe et est accessible, privilégier la mesure ; sinon, utiliser la simulation ou la modélisation. 若系统存在且可访问，可优先测量；否则可使用仿真或建模。

On compare souvent deux méthodes pour valider les résultats. 通常采用两种方法互相验证。

## 19 Objectifs de l'évaluation en HPC HPC 性能评估的目标

Une machine au débit théorique plus élevé exécutera-t-elle nécessairement l'application plus vite ? Il faut connaître la répartition du temps sur l'ancienne machine et la ressource améliorée sur la nouvelle. 买一台峰值算力更高的机器，应用就一定更快吗？要回答这个问题，需要知道应用在原机器上把时间花在哪里，以及新机器改善了哪一种资源。

L'évaluation HPC se rapproche du matériel : mesurer ses performances élémentaires, caractériser processeur et mémoire, comparer les architectures et estimer les gains technologiques. Deux principes méthodologiques s'imposent : HPC 性能评估因此更贴近硬件：测量基础性能，刻画处理器、内存与其他部件的行为，比较硬件方案，并判断技术变化可能带来多少收益。在方法上尤其强调两点：

- **Isoler un facteur.** Utiliser des microbenchmarks ciblés, éventuellement proches des limites de la ressource, pour observer saturation et évolution des performances. **把单个因素测清楚。** 用针对性的微基准施加负载，必要时测试接近资源极限的情况，观察饱和与性能变化。
- **Contrôler le travail réellement exécuté.** Vérifier, voire écrire, l'assembleur pour identifier les instructions et accès effectivement exécutés malgré les transformations du compilateur ou de l'environnement. **控制实际执行的工作。** 为避免编译器或运行环境改变实验含义，有时需要检查乃至编写汇编，确认真正执行了哪些指令、哪些数据访问。

Il faut relier ces mesures à l'application : une bande passante élevée sous un certain motif d'accès ne garantit pas que l'application l'exploite ; cela dépend de ses accès et de son parallélisme. 这些基础测量还要回到应用：内存带宽测得很高，只说明这台机器在相应访问方式下能提供这样的带宽；应用能否利用它，取决于自己的访问模式和并行程度。

## 20 Parallélisme et performance 并行性与性能

### 20.1 Loi d'Amdahl : identifier le travail répartissable Amdahl 定律：先看哪些时间能被分摊

Pour un problème fixe de durée séquentielle $T_1$, la fraction séquentielle vaut $s$ ; le reste est idéalement réparti sur $P$ processeurs, sans surcoût : 设固定问题在单处理器上的执行时间为 $T_1$，其中串行部分占比为 $s$；其余部分理想地分配到 $P$ 个处理器，暂不计额外开销：

Dans cette section, $s=1-F_a$ et $S(P)$ est le même speedup que $\mathrm{Acc}$ en §10 ; $s$ n'est pas la fraction mesurée sur le temps parallèle agrandi du §14. 本节中 $s=1-F_a$，$S(P)$ 与 §10 的 $\mathrm{Acc}$ 都表示加速比；此处 $s$ 的时间基准（以 $T_1$ 为分母）不同于 §14 在扩大问题的并行运行时间 $T_P$ 上定义的比例。

$$
T_P=T_1\left(s+\frac{1-s}{P}\right),\qquad
S(P)=\frac{T_1}{T_P}=\frac{1}{s+(1-s)/P}.
$$

Pour $s>0$, l'accélération tend vers $1/s$ lorsque $P$ augmente. 当 $s>0$ 时，随着 $P$ 增大，加速比趋近 $1/s$。

**Exemple.** Sur 100 secondes, 10 sont séquentielles ($s = 0.1$). Avec 10 processeurs, le temps idéal vaut $10+90/10=19$ secondes, soit un speedup d'environ $5.26$ ; même avec une infinité de processeurs ($P \to \infty$), le speedup ne dépassera jamais $1/0.1 = 10$. **例子。** 一个任务原来需要 $100$ 秒，其中 $10$ 秒必须串行（$s = 0.1$）。使用 $10$ 个处理器后，理想时间是 $10+90/10=19$ 秒，加速比约为 $5.26$；即便处理器数量趋于无穷（$P \to \infty$），加速比也绝不会超过 $1/0.1 = 10$。

Le modèle suppose une taille fixe et une référence séquentielle définie. Communications, synchronisation, ordonnancement et déséquilibre ajoutent des coûts à modéliser ; le nombre de cœurs n'invalide pas à lui seul la relation. 模型要求固定问题规模及明确的串行基准。实际通信、同步、调度与负载不均衡通常还会增加时间；大规模并行时应把这些因素单独建模。核心数量增加本身不会使 Amdahl 的关系失效。

### 20.2 Parallélisme explicite et implicite 显式并行与隐式并行

On distingue souvent deux modes d'organisation du parallélisme : 通常将并行的组织方式分为两类：

- **Parallélisme explicite 显式并行** : parallélisme organisé avec MPI ou OpenMP, où découpage des tâches, distribution des données et coordinations doivent être explicitement programmés. 用 MPI、OpenMP 等明确组织的并行：程序需要显式表达任务划分、数据分配及必要的同步与通信协调。
- **Parallélisme implicite 隐式并行** : jobs indépendants, tirages Monte Carlo et explorations paramétriques (balayage de paramètres), souvent lançables en parallèle par un script ou un ordonnanceur de travaux. 多个独立作业、Monte Carlo 抽样和参数扫描：这些工作单元之间具有天然的独立性（embarrassingly parallel），可由外部脚本或作业调度器直接并发启动。

**Complément.** Le qualificatif « implicite » ne dispense pas d'organiser l'exécution, les entrées/sorties et les flux aléatoires. Par ailleurs, MPI est une norme d'interface de communication par passage de messages (utilisable en C, C++, Fortran, etc.) et OpenMP une interface de programmation à mémoire partagée à base de directives, et non deux langages de programmation indépendants. **补充说明。** “隐式”并不意味着无需组织执行：脚本、调度器、I/O 竞争和独立随机数流仍需要正确配置。此外，MPI 是消息传递通信接口标准，OpenMP 是基于编译指导语句的共享内存并行编程规范，二者都不是独立的编程语言。

### 20.3 Scale-up et Speed-up : préciser l'objectif Scale-up 与 Speed-up：先明确评估对象

On distingue deux objectifs lors de la montée en charge : 扩展能力可以从两种不同目标来审视：

| Terme 术语 | Question 关注的问题 | Grandeurs observables 可以观察的量 |
|---|---|---|
| Scale-up | Peut-on servir davantage de tâches, utilisateurs ou transactions identiques simultanément ? 能否同时支持更多相同任务、用户或事务？ | Capacité concurrente, tâches par seconde et temps de réponse 并发容量、每秒完成的任务数，以及相应响应时间 |
| Speed-up | Une tâche donnée peut-elle se terminer plus tôt ? 一项给定任务能否更早完成？ | Temps de réalisation et accélération par rapport à une référence 完成时间及相对于基准的加速比 |

**Exemple.** Exécuter simultanément 100 simulations indépendantes raccourcit le traitement du lot, sans nécessairement accélérer chaque simulation. Répartir une simulation sur plusieurs processeurs vise à accélérer celle-ci. **例子。** 把 100 个独立模拟从串行运行改为同时运行，整批任务会更早完成，但每个模拟自身未必变快。把单个模拟的计算拆给多个处理器协同完成，则是在缩短这一个模拟的完成时间。

Ces notions ne correspondent pas directement au strong/weak scaling : ceux-ci définissent la variation de taille avec le nombre de processeurs, tandis qu'ici on distingue les objectifs de traitement. 这里的 Scale-up 与 Speed-up 与第 13 节的 strong/weak scaling 不构成一一对应关系：强弱扩展规定的是“处理器数变化时问题规模如何变化”，而这里区分的是“希望提升系统并发吞吐容量还是缩短单任务耗时”。

### 20.4 Exploration paramétrique et Monte Carlo 参数扫描与 Monte Carlo 的例子

**Exploration paramétrique.** Exécuter $n$ simulations indépendantes avec différents paramètres ; les distribuer peut raccourcir le délai global, mais collecte des résultats, chargement et contention coûtent encore du temps. **参数扫描。** 对同一程序使用不同输入参数，执行 $n$ 次相互独立的模拟。如果资源充足，可以将它们分发到多台机器，缩短全部结果收齐的时间；但汇总结果、加载输入与共享资源竞争仍可能产生开销。

**Monte Carlo.** Pour de nombreux essais aléatoires indépendants, distinguer deux modes de comparaison : **Monte Carlo 模拟。** 对于大量相互独立的随机试验，需要区分两种比较方式：

- Nombre total d'essais fixé : réduire le temps total. 固定试验总数 $N$：并行执行的目标是缩短总时间。
- Temps total fixé : davantage de ressources peuvent permettre plus d'essais et une estimation plus précise. 固定总运行时间 $T$：更多计算资源允许完成更多次试验 $N$，从而改善统计估计精度。

**Complément.** Pour des observations i.i.d. de variance finie $\sigma^2$, l'erreur standard de la moyenne empirique vaut $\sigma / \sqrt{N}$ (cf. CM2 §2.6.1). Multiplier le nombre d'échantillons $N$ par $P$ réduit donc l'incertitude statistique d'un facteur $\sqrt{P}$. Le parallélisme n'améliore pas la qualité de chaque échantillon individuel, et il est impératif d'attribuer des graines ou sous-flux pseudo-aléatoires indépendants à chaque processus pour éviter de dupliquer exactement les mêmes tirages. **补充说明。** 对独立同分布、方差为 $\sigma^2$ 的样本均值，其标准误差为 $\sigma / \sqrt{N}$（见 CM2 §2.6.1）。将总试验次数 $N$ 扩大 $P$ 倍，统计误差会按 $1/\sqrt{P}$ 缩小。并行化本身不会提高单个样本的精度；并行实现时必须保证各工作进程使用相互独立的随机数种子或子流，避免不同进程重复生成完全相同的随机数序列。

### 20.5 Pourquoi certains codes passent-ils mieux à l'échelle ? 为什么有的代码更容易扩展？

Certains codes (comme Linpack pour l'algèbre linéaire dense) exploitent bien les processeurs supplémentaires ; d'autres sont limités par les dépendances, le découpage ou la communication. 有些代码（如稠密线性代数基准 Linpack）能很好地利用新增处理器；而另一些代码则受限于算法自身的依赖关系、网格划分方式或通信成本。

Quand le calcul par processeur diminue, échanges et synchronisations peuvent peser davantage. Questions à poser : 随着每个处理器分到的计算量减少，数据交换和同步开销往往占据更大比例。分析可扩展性时可以依次追问：

1. Le travail parallélisable est-il suffisant ? 可并行的工作量是否足够大？
2. La charge est-elle équilibrée ? 各处理器分到的工作是否均衡？
3. Peut-on recouvrir communication et calcul ? 通信能否与计算重叠？
4. Les synchronisations font-elles attendre les processeurs rapides ? 同步是否迫使较快的处理器等待最慢的处理器？

Ces questions relient le speedup au comportement du programme. Voir l'[annexe](1_edpCpl_zh_annex.md) pour les communications, NUMA et les modèles. 这些问题把加速比曲线与程序行为直接联系起来。关于通信拓扑、NUMA 与性能模型的进一步讨论见 [annex](1_edpCpl_zh_annex.md)。

## 21 Ensemble de travail, cache et localité 工作集、缓存命中与局部性

Une instruction ou donnée présente dans le cache étudié produit un hit ; sinon, un miss nécessite un accès à un niveau inférieur de la hiérarchie. 处理器需要的指令或数据如果已在所考察的缓存中，访问就是一次命中（hit）；否则发生缺失（miss），需要向更低一级存储层次取数据。

$$
\mathrm{miss\ ratio}=\frac{\text{缓存缺失次数}}{\text{对应的访问次数}}.
$$

Numérateur et dénominateur doivent concerner le même événement, niveau de cache et périmètre ; les taux de miss L1 et dernier niveau ne répondent pas à la même question. 分子和分母必须属于同一种事件、同一个缓存层级及同一测量范围。例如 L1 数据缓存缺失率与末级缓存（LLC）缺失率回答的是不同问题。

### 21.1 Pourquoi un petit programme peut-il être plus rapide ? “程序很小”为什么可能更快？

Si les données réutilisées restent en cache, les accès suivants sollicitent moins les niveaux lents. Distinguer : 如果反复使用的数据能留在缓存中，后续访问可减少对更慢存储层次的请求。理解这里的“小”，需要区分三个概念：

- **Empreinte mémoire :** espace occupé par les instructions et les données. **内存占用**：程序的指令和数据总共占据多少内存空间。
- **Ensemble de travail actif :** instructions et données réellement réutilisées pendant la phase étudiée. **活跃工作集**：在所考察执行阶段中实际反复访问的指令和数据集合。
- **Workload :** notion générale incluant tâches, tailles, accès et arrivées. **工作负载**：整门课中的广义概念，包括任务类型、数据规模、访问行为、到达方式等。

**Complément.** Un petit ensemble de travail actif favorise les hits après chargement initial, mais ne supprime ni les défauts obligatoires du premier accès (*compulsory/cold misses*), ni les défauts de conflit d'associativité (*conflict misses*), ni les invalidations de cohérence ou interférences entre threads partageant le cache. **补充说明。** 活跃工作集小于缓存容量有利于数据复用命中，但并不能消除首次访问的冷缺失（cold misses）、组相联映射冲突缺失（conflict misses）以及多核共享缓存时的线程干扰或一致性失效。

### 21.2 Comment la localité influence-t-elle les accès ? 局部性怎样影响访问？

- **Localité temporelle :** réutiliser rapidement une donnée récente, par exemple un petit tableau dans une boucle. **时间局部性**：近期访问过的数据很快再次被访问，例如在循环中重复使用同一个小数组或累加变量。
- **Localité spatiale :** accéder rapidement à des adresses voisines, comme lors d'un parcours séquentiel. **空间局部性**：访问某个地址后，很快访问其邻近地址，例如按连续内存顺序遍历数组（充分复用同一条缓存行）。

Les instructions répétées ont souvent une bonne localité ; les données nécessitent une optimisation adaptée. Le blocage vise notamment à réutiliser les données avant leur éviction. 反复执行的循环指令通常天然具有较好的局部性；而数据访问往往需要结合算法调优。循环分块（loop tiling / blocking）的核心目的，就是让一个数据子块在被逐出缓存之前完成尽可能多的计算复用。

**Exemple.** La même boucle sur un petit tableau ou un tableau dépassant le cache peut solliciter différents niveaux mémoire ; documenter taille et état des caches. **例子。** 顺序处理一个小数组和一个远大于缓存的大数组，即使执行完全相同的循环代码，实际访问的也是不同的存储层次（L1/L2 缓存 vs 主存 DRAM）。因此比较结果时必须记录数组规模和缓存状态（冷缓存或热缓存）。

## 22 Latence, bande passante, utilisation et autres métriques HPC HPC 中的延迟、带宽、利用率与其他指标

| Métrique 指标 | Question 回答的问题 | Exemples et limites 例子及解释边界 |
|---|---|---|
| Latence 延迟 | Durée entre émission et achèvement d'une opération ? 一个操作从发出到完成要多久？ | Accès mémoire, aller-retour réseau, réponse d'une base de données 内存访问、网络消息往返、数据库请求响应 |
| Débit ou bande passante 吞吐量或带宽 | Travail ou données transférées par unité de temps ? 单位时间完成多少工作或传输多少数据？ | GB/s, Gb/s, FLOP/s ; distinguer octets B et bits b GB/s、Gb/s、FLOP/s；须区分字节 B 与比特 b |
| Utilisation 利用率 | Degré d'occupation pendant l'observation ? 某资源在观察期内被使用到什么程度？ | Temps CPU occupé, occupation du lien ; définition selon la ressource et l'outil CPU 忙碌时间比例、链路占用等；计数口径因资源和工具而异 |

**Faible latence et forte bande passante sont deux objectifs distincts.** Des accès dépendants peuvent attendre chaque requête, tandis que des accès concurrents saturent la bande passante. Estimer la latence par la moitié d'un aller-retour ping-pong suppose notamment des trajets et surcoûts approximativement symétriques. **低延迟与高带宽是两个不同的目标。** 前后依赖的串行访存受制于每次请求的往返等待延迟；而大量独立的并发请求则可以把数据通路的带宽占满。用网络 ping-pong 往返时间（RTT）除以 2 来估计单程延迟，隐含了往返路径与两端软件处理开销近似对称的假设。

Autres métriques importantes en HPC : 其他常见 HPC 评估指标包括：

- **Fraction du pic théorique 实测占理论峰值比** : le rapport performance mesurée/pic théorique ($R_{\max}/R_{\mathrm{peak}}$) décrit la fraction du pic matériel atteinte ; le distinguer de l'efficacité parallèle $E = S(P)/P$. 实测性能与硬件理论峰值之比描述了硬件算力潜能的发挥程度，应与第 11 节的并行效率 $E = S(P)/P$ 区分。
- **Fiabilité et disponibilité 可靠性与可用性** : la fiabilité concerne la survie sans erreur ni défaillance sur $[0,T]$ ; la disponibilité mesure la fraction de temps de service, comme aux sections 15–16. 可靠性关注给定时长内无故障持续运行的能力；可用性关注可提供服务的时间比例，定义见第 15–16 节。
- **Performance/prix et performance/puissance 性能价格比与性能功耗比** : comparer performance/prix sur un périmètre de coût cohérent (achat matériel seul vs coût total de possession TCO) ; performance/puissance peut s'exprimer en FLOP/s/W, mais l'énergie totale consommée ($E_{\mathrm{énergie}} = P_{\mathrm{moy}} \times T_{\mathrm{exec}}$) dépend aussi de la durée d'exécution. 性能/价格需使用一致的成本口径；性能/功耗常用 FLOP/s/W（如 Green500），但完成一次任务的总能耗还取决于运行时间。

**Complément.** Saturation d'une ressource, goulot d'étranglement (*bottleneck*) et chemin critique (*critical path*) sont trois notions distinctes : une forte utilisation sur une ressource mérite examen mais ne prouve pas à elle seule qu'elle limite le temps global si ce travail est recouvert en parallèle ; le chemin critique est la plus longue chaîne de tâches dépendantes qui détermine la durée minimale d'achèvement du programme. **补充说明。** 资源饱和、性能瓶颈与关键路径是三个不同概念：某项资源利用率高值得排查，但如果它与其他更慢的操作并行重叠，则未必是限制总时间的全局瓶颈；关键路径则是决定程序最短完成时间的依赖链。

## 23 Identifier les goulots de performance 判断程序的性能瓶颈（xxx-bound）

### 23.1 Classer selon la ressource limitante 用“限制在哪里”理解分类

| Catégorie 类别 | Limitation principale 主要限制 | Exemple 用于理解的例子 |
|---|---|---|
| CPU / compute-bound | Capacité d'exécution d'instructions ou d'opérations 处理器执行指令或算术运算的能力 | Noyau arithmétique avec bonne réutilisation des données en cache 数据在缓存中复用充分、算术运算密集的计算内核（如分块矩阵乘法） |
| Memory bandwidth-bound | Débit de transfert au niveau mémoire étudié 所考察内存层次的数据传输速度上限 | Parcours de grands tableaux avec peu de calcul par élément 对大数组进行流式连续读写、每元素算术运算很少（如向量加法） |
| Memory latency-bound | Données trop lentes à revenir et attente difficile à masquer 所需数据返回延迟太长，且难以用并发工作隐藏等待 | Parcours de pointeurs avec adresses dépendantes 下一次访存地址依赖上一次读取结果的指针追踪（如链表/图遍历） |
| I/O-bound | Bande passante ou latence du stockage et des chemins I/O 存储设备或文件/网络 I/O 路径的带宽与延迟 | Gros fichiers ou nombreuses petites requêtes de lecture/écriture 频繁读写大文件或大量零碎小 I/O 请求 |

**Complément.** Un diagnostic précis ne se réduit ni à la seule fréquence CPU ni au seul taux de cache miss : un code peut être limité par les dépendances entre instructions ou le débit d'un port d'exécution spécifique dans le cœur, et un taux de miss élevé n'entraîne un goulot *bandwidth-bound* ou *latency-bound* que si le matériel ne parvient pas à masquer ces accès par le préchargement (*prefetching*) et le parallélisme mémoire (MLP). **补充说明。** 诊断不能简单将 CPU-bound 等同于受限于主频，也不能单凭高缓存缺失率直接下结论：计算受限可能源于指令间依赖链或特定执行端口吞吐上限；而高缓存缺失率只有在硬件预取与访存级并行（MLP）无法掩盖访存开销时，才会真正表现为内存带宽或内存延迟瓶颈。

### 23.2 I/O-bound : localiser le temps d'entrée-sortie I/O-bound：先确认 I/O 时间花在哪里

Outils et leviers courants pour analyser et atténuer les limitations d'entrée-sortie : 排查与缓解 I/O 瓶颈的常见工具与手段包括 `iostat`、并行 I/O（如 MPI-IO）、条带化（striping）、高速固态存储（SSD / NVMe）以及软件架构调整。

Ces options répondent à différentes limites : striping pour répartir les transferts sur plusieurs cibles de stockage, faible latence pour les petites requêtes aléatoires, regroupement ou réduction des I/O au niveau applicatif. Identifier d'abord périphérique, système de fichiers, réseau ou motif d'accès. 这些手段针对的是不同层面的限制：条带化将数据分散到多个存储目标（OST/磁盘），以提高顺序大块传输的聚合带宽；低延迟介质（SSD）有助于改善大量零碎随机小请求；应用层则可通过合并小请求、异步 I/O 重叠或减少冗余读写获益。优化前应先定位瓶颈在存储介质、并行文件系统、互连网络还是应用的访问模式。

Éviter les limitations I/O sur les nœuds de calcul est un objectif courant en HPC, mais une application de traitement de données peut légitimement comporter des phases I/O importantes. 在 HPC 中通常希望避免计算节点长时间空等 I/O，但数据密集型应用本身就包含必要的 I/O 阶段，应针对具体阶段特征做系统调优。

### 23.3 Pourquoi 100 % CPU ne suffit-il pas au diagnostic ? CPU 显示 100%，为什么还不能下结论？

Une expérience simple consiste à faire varier la fréquence du processeur et à observer la performance de l'application : 一种直观的诊断实验是改变处理器主频，观察应用性能随之变化的敏感度：

- Une amélioration sensible et quasi proportionnelle avec la fréquence suggère une limitation par le calcul ou la latence interne au cœur. 性能随主频升高而显著改善，提示处理器核心内部的计算或执行周期很可能是主要限制。
- Une faible variation suggère d'autres ressources à examiner, notamment la mémoire principale ou les entrées-sorties. 性能随主频变化很小，提示瓶颈可能位于核心外部（如主存带宽、外存 I/O 或同步等待）。

L'utilisation CPU rapportée par le système d'exploitation décrit surtout l'occupation du thread planifié sur un cœur logique. Les cycles d'attente mémoire (*memory stalls*) et l'attente active (*spin-waiting*) dans MPI/OpenMP comptent comme temps CPU occupé : **100 % CPU ne signifie donc pas calcul au pic**. 操作系统报告的 CPU 利用率主要反映线程在逻辑核上的调度驻留状态。处理器流水线因等待内存返回而停顿的周期（memory stall cycles），以及并行运行时库中的忙等待轮询（spin-waiting），在操作系统看来都属于“CPU 100% 忙碌”。因此 **100% CPU 利用率绝不等于处理器正在满负荷执行有效算术运算**。

**Complément.** Pour qu'un test de variation de fréquence soit rigoureux, il faut fixer la taille du problème, le nombre de threads, l'affinité (épinglage des threads aux cœurs), le régime thermique et relever la fréquence effective réelle (hors fluctuations Turbo). Noter aussi que sur certaines architectures, la fréquence de l'anneau d'interconnexion ou du cache L3 (*uncore*) peut varier avec l'état de puissance, et que l'insensibilité à la fréquence CPU peut venir d'une attente de synchronisation ou d'I/O aussi bien que de la mémoire. **补充说明。** 进行变主频实验时，必须固定数据规模、线程数、核绑定（thread pinning）、散热状态，并监测实际生效的运行频率（排除动态睿频干扰）。此外，对 CPU 主频不敏感也可能源于同步屏障等待或 I/O 阻塞，仍需结合硬件计数器或微基准进一步确认是否为内存受限。

### 23.4 Le goulot dépend du programme, de l'entrée et de la machine 瓶颈是“程序、输入和机器”的共同结果

Deux facteurs font fréquemment basculer la nature du goulot : 两个常见变化会直接改变同一段代码的瓶颈类型：

1. Une taille d'entrée différente peut faire dépasser la capacité du cache et transformer un noyau *compute-bound* (en cache L1/L2) en noyau *memory bandwidth-bound* (en DRAM). 输入数据规模增大时，活跃工作集可能从装得进缓存变为溢出到主存，使原本受限于算力的程序转为受限于主存带宽。
2. Un autre processeur peut modifier l'équilibre matériel calcul/bande passante (ex. davantage de cœurs ou d'unités SIMD pour la même bande passante mémoire) et déplacer le goulot. 更换处理器架构后，机器的峰值算力与内存带宽之比（machine balance）发生改变，同一程序在新机器上可能表现出不同的瓶颈。

Qualifier la limitation pour une machine, une entrée et une configuration précises. Le [complément Roofline](1_edpCpl_zh_annex.md#annex-roofline) formalise graphiquement cette relation entre intensité arithmétique, bande passante et pic de calcul. 因此，性能结论必须表述为“该程序在某台机器、某个输入规模和运行配置下受某资源限制”，而不能给代码贴上脱离硬件与规模的永久标签。关于算术强度（Arithmetic Intensity）、内存带宽与算力屋顶的定量关系，详见 [Roofline 模型补充](1_edpCpl_zh_annex.md#annex-roofline)。

## 24 Mesurer les métriques classiques : STREAM et calcul flottant 测量经典性能指标：STREAM 与浮点性能

### 24.1 Que mesure STREAM ? STREAM 在测什么？

STREAM caractérise la bande passante mémoire soutenue avec des opérations vectorielles simples sur de grands tableaux (devant dépasser largement la taille du dernier niveau de cache). Le tableau suivant compte les lectures et écritures **utiles** de l'algorithme par itération pour des éléments `double` de 8 octets : STREAM 用大数组上的简单流式操作刻画可持续主存带宽（数组大小须远超末级缓存容量）。下表按每个双精度元素（`double`）占 $8$ 字节，统计每次迭代算法层面的**有效数据读写量**：

| Noyau 内核 | Opération 操作形式 | Accès par élément 每元素读写 | Octets utiles 有效字节数 | Opérations flottantes 浮点运算数 |
|---|---|---|---:|---:|
| Copy | `c[i] = a[i]` | Une lecture, une écriture 一读一写 | 16 B | 0 |
| Scale | `c[i] = scalar * a[i]` | Une lecture, une écriture 一读一写 | 16 B | 1 |
| Add | `c[i] = a[i] + b[i]` | Deux lectures, une écriture 两读一写 | 24 B | 1 |
| Triad | `c[i] = a[i] + scalar * b[i]` | Deux lectures, une écriture 两读一写 | 24 B | 2 |

Une multiplication et une addition dans Triad comptent pour 2 FLOP, même si le compilateur émet une seule instruction FMA. La réduction en lecture seule `Tot = Tot + a[i]` (1 lecture = 8 B, 1 FLOP par élément) sert parfois de test complémentaire en dehors des quatre noyaux STREAM standard. 在 Triad 中，一次乘法加一次加法按算法运算量计为 $2\text{ FLOP}$（即使编译器生成了一条融合乘加 FMA 指令）。此外，纯读取归约 `Tot = Tot + a[i]`（每元素一读 $8\text{ B}$、$1\text{ FLOP}$）常作为辅助对比测试，但不属于上表四个标准 STREAM 内核。

Calcul de la bande passante effective $B_{\mathrm{eff}}$ : si $V_{\mathrm{utile}}$ est le volume utile en octets et $T_{\mathrm{exec}}$ la durée en secondes, elle s'exprime en octets/s : 有效带宽记为 $B_{\mathrm{eff}}$；设算法规定的有效读写总量为 $V_{\mathrm{utile}}$ 字节、执行时间为 $T_{\mathrm{exec}}$ 秒，则：

$$
B_{\mathrm{eff}}=\frac{V_{\mathrm{utile}}}{T_{\mathrm{exec}}}.
$$

**Exemple.** Triad sur $N = 10^7$ doubles transfère $V_{\mathrm{utile}} = 24\times10^7\text{ B} = 240\text{ MB}$ utiles ; si l'exécution dure $T_{\mathrm{exec}} = 0.01\text{ s}$, la bande passante STREAM rapportée vaut $B_{\mathrm{eff}} = 24\text{ GB/s}$ ($10^9\text{ B/s}$). **例子。** Triad 处理 $N = 10^7$ 个双精度元素，有效数据量为 $V_{\mathrm{utile}} = 24\times10^7\text{ B} = 240\text{ MB}$；若耗时 $T_{\mathrm{exec}} = 0.01\text{ s}$，则按 STREAM 规则报告的有效带宽为 $B_{\mathrm{eff}} = 24\text{ GB/s}$（十进制单位）。

### 24.2 Trafic utile et trafic réel du bus mémoire 有效流量与实际内存总线流量

Les caches modifient le trafic réel sur le bus mémoire : avec une politique d'écriture **write-allocate** (allocation à l'écriture, standard sur la plupart des caches CPU), lorsqu'un cœur écrit dans `c[i]` et que la ligne de cache correspondante n'est pas présente dans le cache, le contrôleur doit **d'abord lire la ligne entière depuis la DRAM** vers le cache (*Read For Ownership*, RFO) avant d'y modifier `c[i]`, puis réécrire plus tard la ligne sale en DRAM lors de son éviction. 缓存写策略会改变主存总线上的实际物理流量：在常见的**写分配（write-allocate）**缓存策略下，当处理器执行普通写入 `c[i] = ...` 且目标地址不在缓存中时，硬件必须**先把目标缓存行从主存读入缓存**（Read For Ownership，占 $8\text{ B}$/元素），修改后再在后续替换时**将脏行写回主存**（又占 $8\text{ B}$/元素）。

**Complément (comparaison des comptages d'octets).** Ainsi, pour une écriture ordinaire avec *write-allocate*, chaque store `c[i]` engendre en réalité **1 lecture + 1 écriture** sur le bus DRAM (l'écriture est « comptée deux fois » en trafic matériel) :
- **Copy / Scale** : $16\text{ B}$ utiles pour l'algorithme, mais $8\text{ B (lecture de }a\text{)} + 8\text{ B (RFO de }c\text{)} + 8\text{ B (writeback de }c\text{)} = 24\text{ B}$ réellement transférés sur le bus DRAM.
- **Add / Triad** : $24\text{ B}$ utiles pour l'algorithme, mais $16\text{ B (lectures de }a,b\text{)} + 8\text{ B (RFO de }c\text{)} + 8\text{ B (writeback de }c\text{)} = 32\text{ B}$ réellement transférés sur le bus DRAM.
En revanche, si le compilateur utilise des **instructions d'écriture non temporelles** (*streaming stores / cache-bypass*, ex. `movntpd` sur x86), l'écriture contourne le cache sans lecture préalable RFO, et le trafic matériel retombe à $16\text{ B}$ et $24\text{ B}$. La convention officielle [STREAM](https://www.cs.virginia.edu/stream/ref.html) utilise toujours les octets utiles ($16\text{ B}$ et $24\text{ B}$), tandis que les compteurs matériels du contrôleur mémoire mesurent le trafic physique réel ($24\text{ B}$ et $32\text{ B}$ avec write-allocate) : il ne faut jamais mélanger les deux conventions. **补充说明（两种字节计数口径对比）。** 因此，在普通写分配（write-allocate）路径下，每次写入 `c[i]` 在主存总线上实际产生**一次读加一次写**（即“写被算作两次总线传输”）：
- **Copy / Scale**：算法有效字节数为 $16\text{ B}$，但主存总线实际传输了 $8\text{ B（读 }a\text{）} + 8\text{ B（读入 }c\text{ 所在缓存行）} + 8\text{ B（写回 }c\text{）} = 24\text{ B}$。
- **Add / Triad**：算法有效字节数为 $24\text{ B}$，但主存总线实际传输了 $16\text{ B（读 }a,b\text{）} + 8\text{ B（读入 }c\text{ 所在缓存行）} + 8\text{ B（写回 }c\text{）} = 32\text{ B}$。
反之，若编译器生成了绕过缓存的**非时间局部性流式写指令**（streaming stores / non-temporal stores，如 x86 上的 `movntpd`），则直接向内存写入而无需先读入缓存行，实际总线流量就回到 $16\text{ B}$ 与 $24\text{ B}$。[STREAM 官方规范](https://www.cs.virginia.edu/stream/ref.html)统一按算法有效字节数（$16\text{ B}$ 和 $24\text{ B}$）计算报告带宽，而硬件内存控制器计数器测出的是实际物理总线流量，比较时切勿将两种口径混为一谈。

Pour mesurer la mémoire principale, utiliser assez de données et examiner le plateau de bande passante avec les threads. De petits tableaux peuvent mesurer surtout le cache ; la progression n'est pas toujours linéaire. 测量主存带宽时必须使用远大于末级缓存的数据规模，并观察随线程数增加带宽如何趋于饱和平台；过小的数组测到的是缓存带宽，而多线程达到内存控制器上限后带宽将不再随核数线性增长。

### 24.3 Pourquoi contextualiser MFLOPS et MIPS ? MFLOPS / MIPS 为什么仍要配合上下文？

Le mélange d'instructions, la vectorisation (SIMD) et l'alimentation en données par la mémoire influencent directement le débit d'opérations observé ; deux programmes résolvant le même problème peuvent exécuter des nombres d'instructions et d'opérations très différents. 程序中的指令构成比例、SIMD 向量化程度以及内存数据供给速度都会直接影响实测运算吞吐量；两个完成相同任务的程序完全可能执行不同数量与类型的指令。

Calculer les FLOP/s à partir des opérations flottantes réellement effectuées et de leur durée, pas du nombre total d'instructions. Les MIPS restent des millions d'instructions par seconde (parfois ironiquement surnommés *Meaningless Indicator of Processor Speed*) ; comparer toujours tâche, taille, précision, correction et durée d'exécution. 实际 FLOP/s 必须由真正完成的浮点运算数和相应执行时间计算，不能把整数、访存或控制指令混入分子。MIPS 的字面定义是每秒百万条指令（在性能界也常被戏称为 *Meaningless Indicator of Processor Speed*，“毫无意义的处理器速度指标”，以警示跨架构直接比数值的陷阱）。在对比不同实现时，必须同时报告所执行的任务、问题规模、数值精度、结果正确性以及总完成时间。

## 25 Microbenchmarks et compteurs matériels 获取性能证据：微基准与硬件计数器

### 25.1 Poser une question assez précise 先问一个足够具体的问题

Un microbenchmark isole un facteur : parcourir séquentiellement un grand tableau explore la bande passante ; enchaîner des adresses dépendantes (`p = a[p]`) empêche le recouvrement des requêtes et explore la latence mémoire. Un même volume de données transféré ne garantit donc pas la même grandeur physique mesurée. 微基准（microbenchmark）用于隔离并测量单一硬件特征：连续流式访问大数组可以测出带宽上限；而构造前后依赖的指针追踪（`p = a[p]`）则会消除访存重叠，专门暴露单次访存延迟。因此，即使两个测试搬运了相同总量的数据，测到的物理特征也可能完全不同。

L'accès aux compteurs matériels de performance (PMU) repose sur des interfaces système et des bibliothèques dédiées telles que `perf` (`perf_event`), Perfmon, Perfctr ou PAPI (qui fournit une interface portable multiplateforme : [présentation officielle](https://icl.utk.edu/papi/)). Les événements disponibles et leur sémantique exacte dépendent de la microarchitecture du processeur. 读取硬件性能监控单元（PMU）通常借助系统接口或跨平台库，如 Linux `perf`、Perfmon、Perfctr 或 PAPI（提供统一的跨平台性能计数编程接口，见 [PAPI 官方说明](https://icl.utk.edu/papi/)）。具体可测的事件名称与精确含义取决于底层处理器微架构。

### 25.2 Que peut-on lire dans les compteurs ? 从计数器读出什么？

| Événement 硬件计数事件 | Question possible 可以帮助回答的问题 | Points à vérifier 解释时要核对的口径 |
|---|---|---|
| Cycles 周期数 | Combien de cycles consomme une phase ? 某段程序消耗多少处理器周期？ | Cycles cœur effectifs ou cycles de référence à fréquence fixe 核心实际时钟周期与固定参考周期的区别，以及动态调频的影响 |
| Cycles de blocage 停顿周期 | Quelles étapes du pipeline sont bloquées ? 流水线在哪些阶段受阻停顿？ | Définition et recouvrements entre causes de stall ; ne pas additionner arbitrairement 事件定义与不同停顿原因的重叠关系；不可随意直接相加 |
| Instructions, instructions flottantes 指令数、浮点指令数 | Combien et quels types d'instructions sont exécutés ? 执行了多少、哪类指令？ | Instructions retirées (*retired*) vs exécutées spéculativement, largeur SIMD, FMA 已退休指令与投机执行指令的区别，SIMD 向量宽度（如 AVX-512 一条指令含 8 个双精度元素）及 FMA |
| Load / store 访存指令数 | Combien d'opérations de lecture et d'écriture sont émises ? 发出了多少次读写操作？ | Nombre d'instructions mémoire distinct du volume en octets ; hits possibles en cache 访存指令条数不等于实际传输字节数，且访问可能命中各级缓存 |
| Branches et mauvaises prédictions 分支及预测失败 | Le contrôle de flux pénalise-t-il le pipeline ? 分支控制流是否造成显著冲刷开销？ | Distinguer nombre total de branchements et taux de mauvaise prédiction 区分分支指令总数与分支预测失败（branch misprediction）次数 |
| Défauts de cache 缓存缺失 | Quel niveau de la hiérarchie mémoire limite l'alimentation ? 哪个存储层级的数据供给存在瓶颈？ | Distinguer nombre absolu de misses, miss ratio (par accès) et MPKI (misses pour 1000 instructions) 区分缺失绝对次数、该级缓存缺失率（除以该级访问数）与每千条指令缺失数（MPKI） |

**Complément.** Ces compteurs orientent l'analyse mais ne fournissent un diagnostic fiable que si l'on vérifie la définition matérielle exacte de chaque événement : par exemple, sur de nombreux processeurs modernes, une seule instruction SIMD FMA `vfmadd231pd` sur un registre de 512 bits (8 `double`) compte pour $1$ instruction retirée, mais réalise $8 \times 2 = 16\text{ FLOP}$. **补充说明。** 硬件计数器是定位瓶颈的有力线索，但解读时必须核对微架构手册中的精确定义：例如在支持 AVX-512 的处理器上，一条 512 位双精度融合乘加指令 `vfmadd231pd` 在指令计数器中仅计为 $1$ 条指令，但它对 $8$ 个双精度元素各做了一次乘法和一次加法，实际完成了 $8 \times 2 = 16\text{ FLOP}$。

### 25.3 Pourquoi mesurer par groupes ? 为什么需要分批测量？

Les événements microarchitecturaux observables se comptent par centaines, mais chaque cœur physique ne dispose que d'un petit nombre de registres compteurs matériels simultanés (souvent 4 à 8 compteurs programmables). Deux solutions existent : 处理器支持观测的微架构事件多达数百种，但每个物理核心同时可用的硬件计数寄存器数量非常有限（通常只有 4 到 8 个可编程计数器）。为此通常采用两种方式：

1. **Répétition par groupes 分组重复运行** : exécuter plusieurs fois le même workload en observant à chaque passage un petit groupe d'événements compatibles, tout en gardant entrées, phase mesurée et environnement aussi constants que possible. 对同一工作负载重复运行多次，每次只采集一组互不冲突的硬件事件；重复实验时须保持输入数据、计时阶段和运行环境严格一致。
2. **Multiplexage temporel 事件时间多路复用** : l'outil (perf, PAPI) permute périodiquement les groupes d'événements sur les compteurs physiques au cours d'une seule exécution, puis extrapole le total au prorata du temps d'activation ($N_{\mathrm{estimé}} = N_{\mathrm{mesuré}} \times \frac{T_{\mathrm{total}}}{T_{\mathrm{actif}}}$). Cela introduit un léger surcoût et une erreur d'échantillonnage, surtout si le programme traverse des phases courtes au comportement très variable (voir le [guide PAPI](https://icl.utk.edu/projects/papi/files/documentation/PAPI_USER_GUIDE.htm)). 由工具在单次运行中按时间片轮流切换不同事件复用物理计数器，再按各事件实际开启的时间比例缩放估算总计数（$N_{\mathrm{estimé}} = N_{\mathrm{mesuré}} \times \frac{T_{\mathrm{total}}}{T_{\mathrm{actif}}}$）。这种方式会引入切换开销与采样外推误差，当程序包含短促且行为剧烈变化的阶段时误差尤为明显（参见 [PAPI 用户指南的 multiplexing 说明](https://icl.utk.edu/projects/papi/files/documentation/PAPI_USER_GUIDE.htm)）。

### 25.4 Construire une explication vérifiable 把线索串成可检验的解释

**Exemple.** Pour diagnostiquer un parcours de tableau anormalement lent, mesurer d'abord la durée d'exécution, les défauts du dernier niveau de cache (LLC misses) et la bande passante mémoire effective. Si la bande passante mesurée approche le plafond soutenu d'un microbenchmark STREAM sur la même machine, l'hypothèse d'une limitation par la bande passante mémoire (*memory bandwidth-bound*) est solidement étayée ; si en revanche la bande passante effective est très faible malgré de nombreux misses, examiner les dépendances d'adresses (latence), le manque de parallélisme ou les synchronisations. **例子。** 若发现某段大数组遍历代码很慢，可先测执行时间、末级缓存缺失（LLC misses）和实际内存带宽。如果实测带宽已逼近同机器上 STREAM 微基准的持续带宽上限，则“受限于主存带宽”的判断就有充分证据支持；反之，如果缓存缺失很多但实测内存带宽较低，应进一步检查访存并发度、访问延迟（如地址依赖、跨 NUMA 访问）和同步等待。

Modifier ensuite un facteur ciblé (ex. disposition des données en mémoire, blocage pour le cache ou nombre de threads), puis vérifier que le temps d'exécution et les compteurs matériels évoluent conformément à l'hypothèse. 随后针对性地改变一个因素（如将结构体数组 AoS 改为数组结构体 SoA、加入循环分块或调整线程数），再检验执行时间与硬件计数器是否按理论预期同步改善。完整的性能结论需要这种“观测—假设—干预验证”的闭环证据链，而不能仅停留在“cache miss 很多”或“CPU 很忙”的表面现象。

## 26 Comparer et interpréter les résultats 如何比较和解释性能结果

Une valeur numérique isolée ne prend son sens que par comparaison avec une référence explicite : ancienne version du code, exécution séquentielle sur un cœur, autre implémentation algorithmique ou borne matérielle mesurée par un microbenchmark comparable. 孤立的性能数值没有意义，必须结合明确的参照尺度才能回答实际问题：参照对象可以是优化前的旧版本、单核串行基线、另一种算法实现，或同机器上微基准测出的硬件能力上限。

Préciser systématiquement cinq éléments lors de toute comparaison : 任何严谨的性能对比都应明确交代以下五个要素：

- **Tâche :** calcul réalisé, taille d'entrée, précision numérique (FP64, FP32, FP16) et validité des résultats. **任务**：实际完成了什么计算，输入规模、数值精度（如双精度、单精度或半精度）以及结果是否正确可比。
- **Environnement :** machine (processeur, mémoire, interconnexion), nombre de threads ou processus, compilateur, drapeaux d'optimisation et politique d'affinité. **环境**：硬件平台（处理器型号、内存配置、互连网络）、线程或进程数、编译器版本、编译优化选项及核绑定配置。
- **Référence :** système ou version servant de base de comparaison, unités exactes, périmètre chronométré (avec ou sans initialisation/I/O) et conventions de comptage des octets ou des FLOP. **基准**：以谁为参照基线，指标的确切单位、计时范围（是否包含初始化与 I/O）以及字节或浮点运算的统计口径。
- **Variabilité :** nombre de répétitions, dispersion observée (moyenne, médiane, intervalle de confiance ou quartiles, cf. CM2), sans sélectionner uniquement le meilleur tirage (*cherry-picking*). **波动**：重复实验的次数与结果分布特征（均值、中位数、置信区间或分位数，见 CM2），避免只挑最好看的一次数据报告。
- **Interprétation :** observations factuelles, preuves issues des compteurs ou microbenchmarks, et conditions de validité (taille, architecture) au-delà desquelles la conclusion peut changer. **解释**：区分客观观测事实与因果推论，给出硬件计数器或微基准的支撑证据，并指明结论成立的边界条件（当数据规模或硬件改变时结论可能随之改变）。

**Exemple.** Dire qu'un noyau s'exécute en $0.2\text{ s}$ indique seulement s'il respecte une contrainte de temps réel ; pour démontrer un gain d'optimisation, il faut fournir le temps de référence dans les mêmes conditions (par exemple $0.4\text{ s}$ auparavant, soit un speedup de $2\times$), tout en vérifiant que la taille du problème, la précision numérique et l'exactitude de la sortie n'ont pas été dégradées. **例子。** 仅报告“耗时 $0.2\text{ s}$”只能说明是否满足某个截止时间要求；若要证明优化有效，必须同时给出同条件下的旧版基线时间（例如原耗时 $0.4\text{ s}$，对应加速比为 $2\times$），并确认没有通过缩小问题规模、降低浮点精度或牺牲结果正确性来换取速度。

Cette démarche relie structure du parallélisme et localité des accès aux métriques, à l'identification des goulots et aux preuves mesurées. Les modèles analytiques complémentaires (Roofline, Hockney $\alpha$-$\beta$), les outils de profilage et les rappels mathématiques sont regroupés dans l'[annexe](1_edpCpl_zh_annex.md). 综上所述，HPC 性能评估的主线是：从程序的并行结构与数据局部性出发，选择恰当的性能指标，结合微基准与硬件计数器定位真实瓶颈，并在受控、可复现的参照基准下解释测量结果。关于 Roofline 模型、通信延迟-带宽（$\alpha$-$\beta$）模型等补充材料，见 [第一课 annex](1_edpCpl_zh_annex.md)。
