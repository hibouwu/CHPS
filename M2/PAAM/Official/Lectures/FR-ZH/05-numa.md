# Architectures NUMA · 非均匀内存访问

[目录](README.md) · [教师英文讲义（89 页）](../../GitLab/cours/05-numa.pdf) · [NUMA 实验](../../GitLab/numa/Readme.md)

## Pourquoi ajouter des cœurs · 为什么转向多核

[原讲义第 1–11 页](../../GitLab/cours/05-numa.pdf#page=1)

**FR** L'analyse de données, le calcul et les services demandent plus de débit. L'augmentation de fréquence rencontre des limites de consommation. Ajouter des cœurs offre davantage de ressources, mais leur utilisation dépend du parallélisme et de l'accès aux données. La comparaison de la p. 8 pose cette question avec un ordinateur portable et un serveur. La boucle présentée est monothread et lit des éléments non initialisés, ce qui empêche d'en faire une mesure rigoureuse de l'effet NUMA.

**中文** 数据分析、计算和服务都需要更高吞吐量，而提高频率受功耗限制。增加核心能提供更多算力，但能否用满取决于并行工作和数据访问。第 8 页用笔记本和服务器的时间差引出问题。图中的循环是单线程，还读取未初始化元素，因此这段代码不能当作严格的 NUMA 性能测量。

## Topologie, latence et congestion · 拓扑、延迟与拥塞

[原讲义第 12–20 页](../../GitLab/cours/05-numa.pdf#page=12) · [跨节点路径图](../../GitLab/cours/05-numa.pdf#page=18)

**FR** Un système NUMA fournit un espace d'adressage partagé, mais le chemin jusqu'à la mémoire dépend du cœur et du nœud physique de la page. Les résultats proches de 5 cycles du premier schéma relèvent des caches. Dans l'expérience AMD à huit nœuds, le cours rapporte environ 155 cycles en mémoire locale, 275 à un saut et 380 à deux sauts. Lorsque tous les cœurs concentrent leurs accès sur un nœud, même vers des lignes distinctes, l'exemple atteint environ 870 cycles. Distance topologique et contention sur le contrôleur ou l'interconnexion influencent donc les résultats.

**中文** NUMA 提供共享地址空间，但到达物理页的路径取决于执行核心和页面所在节点。开头矩阵接近 5 周期的结果来自缓存层次。课件的八节点 AMD 实验中，本地内存约 155 周期，一跳约 275 周期，两跳约 380 周期。当所有核心访问同一节点时，即使读不同缓存行，示例也达到约 870 周期。拓扑距离、内存控制器和互联争用都会影响结果。

## Pages physiques et affinité · 物理页放置与线程亲和性

[原讲义第 21–25 页](../../GitLab/cours/05-numa.pdf#page=21)

**FR** La table des pages relie chaque page virtuelle à une page physique d'un nœud. Le programme peut réserver une plage par `mmap`, puis utiliser une politique comme `mbind` pour orienter les allocations de cette plage. L'appel dans le cours est du pseudo-code. L'affinité fixe les CPU sur lesquels les threads peuvent s'exécuter. Le placement sélectionne les nœuds qui hébergent les pages. Leur coordination évite, par exemple, qu'un seul thread initialise toutes les pages sur son nœud avant que les travailleurs soient répartis.

**中文** 页表把虚拟页连到某个节点上的物理页。程序可用 `mmap` 保留地址区间，再通过 `mbind` 一类策略选择该区间的物理页来源。课件中的调用是简化伪代码。线程亲和性约束线程可在哪些 CPU 上运行，内存策略决定页面落在哪些节点。两者需要配合，例如避免工作线程分散之前，主线程先在自己的节点集中初始化所有页面。

## Effet des caches sur NUMA · 缓存如何影响 NUMA 开销

[原讲义第 26–27 页](../../GitLab/cours/05-numa.pdf#page=26)

**FR** Pour interpréter les chiffres du cours, posons $h$ comme probabilité de succès à chaque niveau atteint, de L1 à L3. La fraction atteignant la mémoire vaut alors $(1-h)^3$. Elle passe de 34,3 % pour $h=0{,}3$ à 2,7 % pour $h=0{,}7$. La latence de la mémoire locale ou distante pèse donc davantage lorsque les caches absorbent peu d'accès. Les diapos donnent environ 32 contre 156 cycles par instruction dans le premier cas et 7 contre 17 dans le second, pour leurs hypothèses de coût.

**中文** 为了理解课件数值，假设 L1 到 L3 每一级的条件命中率都是 $h$，即已到达该级以后再算命中概率。落到内存的比例是 $(1-h)^3$。$h=0.3$ 时约有 34.3% 到内存，$h=0.7$ 时只有 2.7%。缓存吸收的访问越少，本地和远程内存延迟的差别就越明显。按课件的开销假设，两种场景的好坏放置分别约为 32 对 156、7 对 17 周期每指令。

## Quatre politiques de placement · 四种放置策略

[原讲义第 28–42 页](../../GitLab/cours/05-numa.pdf#page=28) · [实测对比](../../GitLab/cours/05-numa.pdf#page=41)

| Politique / 策略 | Principe / 原理 | Compromis / 取舍 |
|---|---|---|
| Placement manuel / 手工放置 | Lier les travailleurs et les zones aux ressources voulues / 显式绑定工作线程和地址范围 | Robuste si l'affectation est stable / 适合分工稳定的程序 |
| Entrelacement / 交错 | Distribuer les pages à tour de rôle / 按页轮流分散到节点 | Répartit la pression, peut rallonger des trajets / 平衡带宽压力，但可能增加远程访存 |
| Premier accès (*first-touch*) / 首次触碰 | Placer en fonction du thread qui déclenche l'allocation / 由触发实际分配的线程影响放置 | Utile si celui qui initialise utilise ensuite la page / 初始化者也长期使用该页时效果好 |
| Carrefour / 动态迁移 | Migrer selon les congestions observées / 根据拥塞情况迁页 | Coût de migration et adaptation aux phases / 有迁移成本，并依赖对运行阶段的判断 |

**FR** L'étude compare Linux first-touch et l'entrelacement avec des pages de 4 Kio, chacun avec ou sans Carrefour. La référence de la figure est Linux first-touch, de rapport 1. Le choix dépend de la répartition des accès et des goulots d'étranglement.

**中文** 研究使用 4 KiB 页面，对比 Linux first-touch 和交错放置，两种都分别测试使用与不使用 Carrefour。图中基线 1 是 Linux first-touch。哪个策略更好取决于访问分布和瓶颈位置。

## Déséquilibre et choix de politique · 用访问不均衡判断策略

[原讲义第 43–52 页](../../GitLab/cours/05-numa.pdf#page=43)

**FR** Avec first-touch, soit $a_i$ le nombre d'accès au nœud $i$, et $\bar a$ la moyenne positive de ces nombres pour les huit nœuds. Le déséquilibre $D$ ci-dessous reproduit le tableau en prenant l'écart-type d'échantillon. Huit nœuds recevant la même charge donnent 0 %, un seul donne environ 283 %. La règle empirique est de garder first-touch si le déséquilibre est faible, de tester first-touch avec Carrefour s'il est modéré, puis l'entrelacement avec Carrefour s'il est fort. La p. 52 contient une mention contradictoire dans le texte, tandis que son schéma et les p. 50–51 indiquent l'entrelacement dans le dernier cas.

**中文** 在 first-touch 下，记 $a_i$ 为对节点 $i$ 的访问次数，$\bar a$ 为八个节点的正均值。下式用样本标准差定义不均衡程度 $D$，可以复现课件表格。八个节点均分访问时为 0%，全部集中在一个节点时约 283%。经验规则是低不均衡保持 first-touch，中等不均衡尝试 first-touch 加 Carrefour，高不均衡尝试交错加 Carrefour。第 52 页正文有一处与图不一致，高不均衡的策略按同页图和第 50–51 页理解为交错。

$$
D=\frac{\sqrt{\frac{1}{7}\sum_{i=1}^{8}(a_i-\bar a)^2}}{\bar a}.
$$

## Spark et diagnostic du ramasse-miettes · Spark 和垃圾回收瓶颈

[原讲义第 53–58 页](../../GitLab/cours/05-numa.pdf#page=53)

**FR** Le cours mesure Spark sur un tas de 40 Go, avec le ramasse-miettes Parallel Scavenge (PS). Le gain se tasse après une douzaine de cœurs. La ventilation du temps entre application et collecte montre que le débit du GC évolue moins bien que le calcul. Enlever des synchronisations inutiles, revoir les verrous et optimiser la file de vol de travail améliorent le débit. L'échelle NUMA reste un facteur pour les parcours d'objets.

**中文** 课件测试 Spark 的 40 GB 堆，垃圾回收器用 Parallel Scavenge（PS）。核数超过约 12 后，整体加速趋缓。区分应用和 GC（垃圾回收）时间后可见，GC 吞吐的扩展性落后于计算。去掉不必要的同步、优化锁及任务窃取队列后，吞吐改善，跨节点对象遍历仍有限制。

## NUMAGiC · 让 GC 在对象附近工作

[原讲义第 59–77 页](../../GitLab/cours/05-numa.pdf#page=59) · [同步以外的开销](../../GitLab/cours/05-numa.pdf#page=69) · [两种结果指标](../../GitLab/cours/05-numa.pdf#page=75)

**FR** NUMAGiC transmet au nœud propriétaire le travail sur les objets distants pour que la suite des accès soit locale. Un message pour chaque référence distante est trop cher. Garder les objets sur leur nœud d'allocation aide à réduire les échanges quand les allocations d'un même thread sont fortement liées. En mode local, les travailleurs gardent la localité et envoient le travail distant. Un travailleur inactif peut voler et traiter des objets distants pour rééquilibrer. La p. 75 donne le débit du GC en Go/s et la p. 76 l'accélération de l'application. Dans l'expérience, le temps d'achèvement est environ divisé par deux.

**中文** NUMAGiC 将远程对象的工作传给持有这个对象的节点，让后续访问尽量在本地发生。每个远程引用都发消息代价太高。如果同一线程分配的对象常相互引用，将对象保留在分配节点有助于减少跨节点消息。有本地工作时优先本地处理，并把远程工作发出去。没有本地工作时可以窃取远程对象的工作，平衡负载。第 75 页看 GC 的 GB/s，第 76 页看应用加速比。这组实验的整体完成时间约减半。

## Xen, topologie et changements de placement · Xen、拓扑与运行中迁移

[原讲义第 78–89 页](../../GitLab/cours/05-numa.pdf#page=78) · [拓扑变化](../../GitLab/cours/05-numa.pdf#page=86)

**FR** Dans une VM, les pages physiques vues par l'invité correspondent à des pages physiques gérées par l'hôte. Un vCPU est un processeur virtuel, un pCPU une ressource CPU physique. L'étude sur 29 applications compare Xen et XenNUMA, qui applique des politiques génériques côté hyperviseur. À 48 vCPU déjà épinglés, le nombre d'applications sous 50 % de surcoût passe de 12 à 23 avec le meilleur placement évalué. Un programme comme NUMAGiC a aussi besoin de connaître les distances. XPV expose la topologie initiale et notifie l'invité quand les vCPU migrent, afin que le système et son environnement d'exécution puissent réagir.

**中文** 虚拟机看到的客户机物理页最终由宿主机物理页承载。vCPU 是虚拟 CPU，pCPU 是物理 CPU 资源。课件在 29 个应用上比较 Xen 和 XenNUMA，后者在虚拟机监控层引入通用策略。在 48 个 vCPU 已绑定的实验中，选到所评估的最佳放置时，额外开销低于 50% 的应用从 12 个增到 23 个。NUMAGiC 这样的程序还需要知道实际距离。XPV 提供初始拓扑，vCPU 迁移时也会通知客户机，让操作系统和运行时做出调整。

## Vérification rapide · 自检

- **FR** Pourquoi l'entrelacement aide-t-il si le premier accès a placé presque toutes les pages sur un seul nœud ? Il répartit les demandes entre contrôleurs. **中文** first-touch 把页面集中到一个节点时，交错为什么可能更好？访问请求可以分摊到多个控制器。
- **FR** Quand envoyer un travail à distance plutôt que le voler ? Avec du travail local, envoyer préserve la localité. À l'arrêt, voler peut compenser le coût d'accès distant. **中文** 何时转发远程任务，何时自己窃取？有本地任务时转发能保留局部性，空闲时窃取可用更多并行度换取远程访问成本。
