# Quiz

## Ch.02 Memory layout and cache blocking

### *Q.1 Qu'est ce que la localité spatiale ? Qu'est ce que la localité temporelle ? 什么是空间局部性？什么是时间局部性？

**Réponse**

- La localité spatiale : si on accède à une adresse, il est probable qu'on accède ensuite à des adresses voisines ou proches. 空间局部性：如果访问了某个地址，那么接下来很可能访问与它相邻或接近的地址。
- La localité temporelle : si une donnée vient d'être utilisée, il est probable qu'elle soit réutilisée bientôt. 时间局部性：如果某个数据刚刚被访问过，那么在不久之后很可能再次访问它。
- Le cache exploite la localité spatiale en transférant les données par cache lines, et la localité temporelle en conservant les données récemment utilisées, ce qui réduit le coût moyen des accès mémoire. 高速缓存通过按 cache line（缓存行）搬运相邻数据来利用空间局部性，通过保留最近访问过的数据来利用时间局部性，从而减少平均访存开销。

### *Q.2 Quelle est la difference entre le cache L1i et L1d ? `L1i` 和 `L1d` cache 有什么区别？

**Réponse** `L1i` est le cache d'instructions : il stocke les instructions du flot d'exécution. `L1d` est le cache de données : il stocke les données lues ou écrites par le programme.  `L1i` 是指令缓存，用来给处理器前端提供指令流中的指令；`L1d` 是数据缓存，保存程序读写的数据。

### *Q.3 Expliquer qu'est ce que le TLB ? 解释什么是 TLB

**Réponse** Le TLB, pour Translation Lookaside Buffer, est un petit cache de traductions d'adresses virtuelles vers adresses physiques.  TLB 是虚拟地址到物理地址转换结果的小缓存。

### Q.4 Qu'est-ce qu'une cache line ? Pourquoi l'accès contigu est-il plus efficace ? 什么是 cache line？为什么连续访问更高效？

**Réponse** Une cache line est l'unité matérielle de remplissage du cache. cache line 是缓存装填的硬件基本单位。
L’accès contigu est plus efficace parce qu’il permet d’utiliser plusieurs données utiles d’une même ligne, ce qui réduit les misses, améliore la localité spatiale et limite les accès coûteux aux niveaux supérieurs du cache ou à la mémoire. 连续访问更高效，因为它能利用同一行中多个有用数据，减少未命中，提高空间局部性，并限制昂贵的更高级别缓存或内存访问。

### Q.5 Quelle est la différence entre `row-major` et `column-major` ? Pourquoi cela change-t-il la bonne façon de parcourir un tableau ? `row-major` 和 `column-major` 有什么区别？为什么这会改变遍历数组的最佳方式？

**Réponse** `row-major` et `column-major` décrivent la façon dont un tableau est linéarisé en mémoire. En `row-major`, la dimension colonne est contiguë ; en `column-major`, c’est la dimension ligne. `row-major` 和 `column-major` 描述的是数组在内存中的线性展开方式。`row-major` 下列维度连续，`column-major` 下行维度连续。
La boucle interne suit en général cette dimension contiguë pour mieux préserver la localité spatiale, la bande passante et souvent la vectorisation. 因此最内层循环通常会沿着这个连续维度走，以更好地保持空间局部性、带宽利用，并常常更利于向量化。

### *Q.6 Qu'est ce qu'un tableau de structure (Structure of Arrays, SoA) ? 什么是 SoA（结构分量分数组）？

**Réponse** En SoA, chaque champ est stocké dans son propre tableau, par exemple `x[]`, `y[]`, `z[]`. SoA 中每个字段各自存成一个数组，例如 `x[]`、`y[]`、`z[]`。

### *Q.7 Qu'est ce qu'une structure de tableau (Array of Structures, AoS) ? 什么是 AoS（数组元素为结构体）？

**Réponse** En AoS, on stocke un tableau dont chaque élément est une structure complète, par exemple `particles[i]` contenant tous les champs d'une particule.  AoS 是“结构体数组”：数组里的每个元素都是一个完整结构体，例如 `particles[i]` 同时包含某个粒子的所有字段。

### *Q.8 Expliquez dans quelles cas il est plus judicieux d'utiliser l'une ou l'autre. 解释在什么情况下更适合使用 SoA 或 AoS

**Réponse** SoA est généralement meilleur quand les calculs parcourent un même champ sur beaucoup d'éléments, car les accès deviennent contigus et vectorisables. AoS est souvent préférable quand on manipule un objet complet à la fois, quand la lisibilité prime, ou quand plusieurs champs du même objet sont utilisés ensemble à chaque accès. Le bon choix dépend donc du motif d'accès dominant. 当计算模式是“跨很多元素处理同一个字段”时，SoA 通常更合适，因为访问连续、也更利于向量化；当程序是“每次处理一个完整对象”且多个字段总被一起访问时，AoS 往往更自然。最终应根据主要访问模式选择。

### Q.9 Pourquoi l'ordre des champs d'une structure peut-il changer sa taille mémoire ? 为什么结构体字段顺序会改变其内存大小？

**Réponse** Chaque type a une contrainte d'alignement, donc le compilateur ajoute du padding pour placer chaque champ sur une adresse valide. L'ordre des champs change ainsi le padding interne, et parfois le padding final pour que les éléments d'un tableau de structures restent alignés. Il vaut mieux perdre quelques octets que provoquer des accès désalignés, souvent plus lents. 每种类型都有对齐要求，因此编译器会加入 padding，让每个字段落在合法地址上。字段顺序会改变内部填充量，有时也会改变结构体末尾的补齐，以保证结构体数组中的元素仍然对齐。相比产生未对齐访问，浪费少量字节通常代价更低。

### Q.10 Qu'est-ce que le cache blocking ? Pourquoi améliore-t-il les performances ? 什么是 cache blocking？为什么它能提高性能？

**Réponse** Le cache blocking consiste à réduire le working set pour qu’un petit bloc reste dans le cache pendant sa réutilisation. cache blocking 的本质是缩小 working set，让一个小数据块在复用期间留在 cache 中。
On recharge alors moins souvent les mêmes données, on augmente leur réutilisation dans le cache et on réduit les accès mémoire inutiles. 这样同一数据就不必反复重取，cache 中的数据复用也会更高，同时还能减少不必要的内存访问。

## Ch.03 NUMA

### *Q.1 Qu'est ce qu'une architecture NUMA ? Expliquer qu'est ce que l'“effet NUMA” ? 什么是 NUMA 架构？解释什么是“NUMA 效应”

**Réponse** Une architecture NUMA répartit physiquement la mémoire par nœuds, donc un cœur atteint plus vite sa mémoire locale qu'une mémoire distante. NUMA 架构把内存在物理上分布到多个节点，因此核心访问本地内存会比访问远端内存更快。
L'effet NUMA est la perte de performance provoquée par des accès fréquents à des pages placées sur un autre nœud, car chaque accès traverse plus de liens et consomme de la bande passante distante. NUMA 效应就是频繁访问远端页时产生的性能下降，因为每次访问都要经过更多互连并消耗远端带宽。

### *Q.2 Expliquer ce qu'est la politique de “first touch”. 解释什么是“first touch”策略

**Réponse** Le first touch signifie qu'une page physique n'est réellement allouée qu'au premier accès effectif, souvent à la première écriture. Elle est alors placée sur le nœud NUMA du thread qui la touche. first touch 指的是：物理页只有在第一次真正访问时才会被分配，实践中通常是第一次写入时。此时该页会放到首次触碰它的线程所在的 NUMA 节点。

### *Q.3 Est ce que le first touch permet toujours de bien gérer les effets NUMA ? Expliquez la réponse. first touch 是否总能很好地处理 NUMA 效应？请解释

**Réponse** Non. Il n'aide que si l'initialisation ressemble au schéma d'accès futur. Si un thread place toutes les pages puis que d'autres les utilisent, ces pages deviennent distantes pour la plupart d'entre eux. 不一定。它只有在初始化方式和后续真实访问模式接近时才有效。如果一个线程先放置了所有页，而后续由其他线程使用，那么这些页对大多数线程都会变成远端页。

### *Q.4 Qu'est ce que le false-sharing ou faux-partage ? Comment peut-on l'éviter ? 什么是伪共享？如何避免？

**Réponse** Le false sharing apparaît quand plusieurs threads écrivent des données différentes situées dans la même cache line. Le partage logique n'existe pas, mais la cohérence agit quand même au niveau de la ligne, qui invalide et migre entre cœurs. 伪共享是指多个线程写入的是不同数据，但这些数据位于同一条 cache line 中。逻辑上并没有共享同一变量，但一致性仍按整条 line 工作，于是它会在核心之间失效和迁移。
On l'évite en séparant les écritures par cache line : padding, alignement, partitionnement des données et scheduling plus propre. 避免方法是把不同线程的写入分离到不同 cache line：padding、对齐、更好的数据划分和调度。

### Q.5 Qu'est-ce que la cache coherency ? Pourquoi peut-elle coûter cher ? 什么是 cache coherency？为什么它会带来开销？

**Réponse** La cache coherency garantit que lorsqu'un cœur écrit une donnée partagée, les autres cœurs ne continuent pas à lire une copie périmée de cette donnée. cache coherency 保证当一个核心写入共享数据后，其他核心不会继续读取这份数据的过期副本。
Son coût vient surtout des invalidations et des transferts de cache lines lors des écritures, ce qui ajoute messages, latence et migrations, surtout entre sockets. 它的开销主要来自写入时的 cache line 失效和转移，这会增加消息、延迟和 line 迁移，跨 socket 时尤其昂贵。

### Q.6 Pourquoi l'accès à un cache distant sur le même socket, puis sur un autre socket, est-il plus lent ? Comment peut-on limiter ce problème ? 为什么访问同 socket 的远端 cache、以及跨 socket 的远端 cache 更慢？如何缓解这个问题？

**Réponse** Un cache distant est plus lent car la requête traverse plus de niveaux et de liens ; sur un autre socket, elle franchit en plus l'interconnexion inter-socket. Le chemin plus long augmente la latence et réduit la bande passante utile. 远端 cache 更慢，因为请求要穿过更多层级和链路；若在另一个 socket 上，还要额外经过 socket 间互连。路径更长会提高延迟并降低有效带宽。
On limite cela par l'affinité et par un placement cohérent des threads et des données. 缓解方法是设置好亲和性，并让线程和数据的放置与访问模式一致。

### Q.7 Pourquoi une initialisation parallèle est-elle souvent meilleure qu'une initialisation séquentielle sur une machine NUMA ? 为什么在 NUMA 机器上，并行初始化通常比顺序初始化更好？

**Réponse** Une initialisation séquentielle place souvent trop de pages sur un seul nœud, car un seul thread les touche en premier. Une initialisation parallèle répartit au contraire le first touch entre les threads qui utiliseront les données, donc aligne mieux placement physique et calcul. 顺序初始化常常会把太多页放到同一个节点，因为首次触碰它们的是同一个线程。并行初始化则把 first touch 分散到后续真正使用数据的线程上，因此更能让物理放置和计算对应起来。

### Q.8 Quel est le lien entre data locality et NUMA locality ? 数据局部性和 NUMA 局部性之间是什么关系？

**Réponse** La data locality consiste à garder les données près du calcul. La NUMA locality est la même idée à l’échelle des nœuds mémoire : les données doivent être placées près des cœurs qui les utilisent. 数据局部性就是让数据尽量靠近计算。NUMA 局部性则是同样的思想在内存节点层面上的体现：应尽量让数据放在使用它们的核心附近。

### Q.9 Quelle est la différence entre true sharing et false sharing ? 真共享和伪共享有什么区别？

**Réponse** Le true sharing correspond à un vrai partage de la même donnée entre threads ; le coût de cohérence est alors normal. Le false sharing produit presque le même coût matériel, mais sans vrai partage : seules des données distinctes cohabitent dans la même cache line. 真共享是多个线程确实共享同一个数据，因此一致性开销是正常的。伪共享在硬件上的代价几乎类似，但并没有真正共享同一变量，只是不同数据碰巧落在同一条 cache line 里。

### Q.10 Pourquoi NUMA affecte-t-il aussi la bande passante et les périphériques d'I/O ? 为什么 NUMA 也会影响带宽和 I/O 设备？

**Réponse** NUMA affecte aussi la bande passante, car les accès distants passent par des liens partagés qui peuvent saturer. Le même raisonnement vaut pour l'I/O attaché à un socket : GPU, NIC ou stockage sont plus efficaces lorsqu'ils sont utilisés depuis les cœurs proches. NUMA 影响的不只是延迟，也影响带宽，因为远端访问要经过可能饱和的共享互连。这个原理对挂在某个 socket 上的 I/O 设备同样成立：GPU、网卡、存储若由附近核心使用会更高效。

## Ch.04 The Roofline model

### Q.1 Qu'est-ce que le modèle Roofline ? 什么是 Roofline 模型？

**Réponse** Le modèle Roofline relie la performance d'un code à deux plafonds : un plafond mémoire fixé par la bande passante, et un plafond calcul fixé par le pic de FLOPs. Il sert à voir rapidement si un noyau est surtout limité par les transferts ou par le calcul. Roofline 模型把代码性能和两个上限联系起来：一个是由带宽决定的内存上限，另一个是由峰值 FLOPs 决定的计算上限。它用来快速判断一个内核主要受访存限制还是受算力限制。

![le modèle Roofline](roofline.png)

According to its Operational Intensity (Ratio of operations per bytes moved), one program is either memory-bound or compute-bound. 根据算术强度（每字节移动的操作数），程序要么受内存限制，要么受计算限制。

### Q.2 Quelle est la différence entre une application memory-bound et compute-bound ? 什么是 memory-bound 和 compute-bound，它们有什么区别？

**Réponse** Une application memory-bound attend surtout les données ; une application compute-bound bute surtout sur le plafond de FLOPs. La première s'améliore surtout par la localité et la réduction du trafic, la seconde par vectorisation, ILP et meilleure exploitation des unités de calcul. memory-bound 程序主要是在等数据；compute-bound 程序主要是撞到了 FLOPs 上限。前者主要靠改善局部性和减少流量来优化，后者则更多依赖向量化、ILP 和更充分地利用计算单元。

## Ch.05 Tools

### *Q.1 Citez 4 outils d'analyse et d'optimisation des performances et expliquez leurs usages. 列举 4 种性能分析与优化工具并说明其用途

**Réponse** `perf + KDAB Hotspot` servent à lire les événements matériels et à localiser visuellement où le temps et les stalls partent ; `gprof` donne un profil au niveau des fonctions ; `MAQAO` analyse finement le code machine et les limites microarchitecturales ; `TAU` profile et trace les applications parallèles pour exposer calcul, communication et synchronisation. `perf + KDAB Hotspot` 用来读取硬件事件并可视化时间和停顿耗在哪里；`gprof` 提供函数级性能剖析；`MAQAO` 细致分析机器码和微架构瓶颈；`TAU` 用 profiling 和 tracing 揭示并行程序中的计算、通信和同步行为。

## Ch.06 Compilers

### Q.1 Quel est le rôle du préprocesseur ? 预处理器的作用是什么？

**Réponse** Le préprocesseur réécrit le code avant compilation : il inclut les en-têtes, développe les macros et résout les compilations conditionnelles comme `#ifdef`. Le compilateur ne voit donc pas le fichier source original, mais le texte déjà transformé par cette étape. 预处理器会在正式编译前重写源代码：插入头文件、展开宏、处理 `#ifdef` 这类条件编译。因此编译器真正看到的并不是原始源码，而是预处理后的文本。

### Q.2 Qu'est-ce que GIMPLE ? Pourquoi est-il utile ? 什么是 GIMPLE？为什么它有用？

**Réponse** `GIMPLE` est une représentation intermédiaire simplifiée de GCC, proche du code à trois adresses. `GIMPLE` 是 GCC 的一种简化中间表示，接近三地址代码。
En cassant les expressions complexes en opérations élémentaires et en rendant le flot plus explicite, elle facilite les passes d'optimisation comme la propagation, la vectorisation ou les optimisations de boucles. 它把复杂表达式拆成基本操作，并让控制流更显式，因此更便于实现传播、向量化、循环优化等各种优化 pass。

### Q.3 Quel est le rôle du middle-end ? 中端（middle-end）的作用是什么？

**Réponse** Le middle-end réalise l'essentiel des optimisations indépendantes de l'architecture cible. Il travaille sur l'IR, transforme le programme pour réduire le travail inutile ou mieux exposer le parallélisme, puis transmet une version plus optimisable au back-end. 中端负责大部分与具体硬件无关的优化。它在中间表示上改写程序，以减少无效工作或更好暴露并行性，然后把更适合目标机器生成代码的版本交给后端。

## Ch.07 ILP

### *Q.1 Qu'est ce que l'Instruction Level Parallelism (ILP) ? En quoi cela est important pour les performances d'un code ? 什么是指令级并行（ILP）？为什么它对程序性能很重要？

**Réponse** L'ILP correspond à la possibilité d'exécuter ou de faire avancer en parallèle plusieurs instructions indépendantes. ILP 指的是多条彼此独立的指令可以并行执行或并行推进。
Il est notamment exploité grâce au pipeline, qui permet de faire coexister plusieurs instructions à différents stades d'exécution. Plus le code expose de telles instructions, moins les unités d'exécution restent inactives et plus le processeur peut exécuter plus d'instructions utiles par cycle. 处理器会通过流水线来利用这种并行性，也就是让多条指令同时处在不同的执行阶段。代码能暴露的独立指令越多，执行单元越不容易空转，处理器每个周期完成的指令就越多。

## Ch.08 Vectorization

### *Q.1 Comment fonctionne la vectorisation ? 向量化是如何工作的？

**Réponse** La vectorisation utilise des instructions SIMD pour appliquer la même opération à plusieurs éléments en une seule instruction. Elle augmente donc le nombre d'opérations utiles par instruction émise et améliore le débit surtout lorsque les accès sont réguliers et que les dépendances sont faibles ; un bon alignement aide souvent les performances, mais n'est pas toujours une condition nécessaire. 向量化利用 SIMD 指令在一条指令里同时处理多个元素。因此每发射一条指令就能完成更多有效运算；当数据访问较规则、依赖较少时，整体吞吐量通常会提高。良好的对齐通常有助于性能，但并不是绝对必要条件。

## Ch.09 MPI

### *Q.1 Qu'est ce que la bande passante (bandwidth) lors de l'envoi d'un message MPI ? MPI 消息发送中的带宽是什么？

**Réponse** En MPI, la bande passante est le débit de données soutenu une fois le transfert lancé. Elle domine le coût des gros messages, car quand la taille augmente, c'est surtout la quantité d'octets par seconde que le réseau peut fournir qui fixe le temps total. 在 MPI 中，带宽是消息启动后能够持续提供的数据传输速率。它主要决定大消息的代价，因为消息一旦很大，总时间主要取决于网络每秒能搬多少字节。

### *Q.2 Qu'est ce que la latence (latency) lors de l'envoi d'un message MPI ? MPI 消息发送中的延迟是什么？

**Réponse** En MPI, la latence est le coût fixe pour initier un message avant que le débit soutenu ne compte vraiment. Elle domine surtout les petits messages, car le temps de démarrage y pèse plus lourd que le temps passé à transférer les données elles-mêmes. 在 MPI 中，延迟是消息真正进入传输前的固定启动开销。它主要影响小消息，因为这时启动成本往往比实际搬运数据的时间更大。

### Q.3 Qu'est-ce que le domain decomposition ? Pourquoi est-il nécessaire ? 什么是 domain decomposition（域分解）？为什么它是必要的？

**Réponse** Le domain decomposition répartit simultanément les données et le calcul entre processus, souvent en donnant un sous-domaine de maillage à chacun. domain decomposition 是把数据和计算同时切分给多个进程，网格计算里通常表现为每个进程负责一个子域。
Il est nécessaire parce que le coût MPI dépend directement de ce découpage : un mauvais partitionnement augmente frontières, communications et déséquilibres, donc détruit la scalabilité. 它之所以关键，是因为 MPI 的通信量、边界大小和负载均衡都直接取决于这个切分；切分不好，可扩展性就会变差。

### Q.4 Quelle est la différence entre une décomposition verticale et une décomposition horizontale d'un stencil 2D ? 二维 stencil 的垂直分解和水平分解有什么区别？

**Réponse** Dans une décomposition verticale, chaque processus reçoit une bande de colonnes ; avec un stockage `row-major`, les données de bord sont alors souvent moins contiguës, ce qui peut imposer des accès stridés ou du packing lors des échanges. Dans une décomposition horizontale, chaque processus reçoit un bloc de lignes ; avec ce même stockage, les frontières sont souvent plus contiguës et plus faciles à regrouper. Le coût réel dépend donc du layout mémoire et du schéma d'échange, pas seulement du mot “vertical” ou “horizontal”. 在垂直分解中，每个进程得到若干列；在 `row-major` 存储下，这些边界数据往往不够连续，通信时可能出现跨步访问或需要额外打包。在水平分解中，每个进程得到若干行；在同样的存储布局下，边界通常更连续，也更容易聚合。实际代价因此取决于内存布局和交换方式，而不只是“垂直”或“水平”这两个名字。

### *Q.5 Qu'appelle-t-on des mailles “fantômes” (ou ghost cells) ? Quelle est leur utilité ? 什么叫“幽灵单元”或“鬼单元”？它们有什么作用？

**Réponse** Les ghost cells, ou halo cells, sont des copies locales des données voisines stockées autour d'un sous-domaine. 幽灵单元或 halo cells 是存放在子域边界周围的邻居数据本地副本。
Elles transforment un besoin de données distantes en lecture locale entre deux échanges de halo, ce qui évite de communiquer à chaque opération sur la frontière. 它们把原本对远端数据的需求，变成两次 halo 交换之间的本地读取，从而避免边界上的每一步操作都通信。

### Q.6 Qu'est-ce que l'asynchronous progression ? 什么是 asynchronous progression（异步推进）？

**Réponse** L'asynchronous progression est la capacité de MPI à faire avancer un message pendant que l'application calcule. Son intérêt est le recouvrement calcul/communication, mais ce gain n'existe que si l'implémentation progresse réellement en arrière-plan. 异步推进是指 MPI 能在程序计算的同时继续推进消息传输。它的价值在于实现计算与通信重叠，但前提是实现确实会在后台推进消息。

### Q.7 Pourquoi une communication MPI non bloquante ne progresse-t-elle pas toujours toute seule ? 为什么 MPI 非阻塞通信并不一定会自己自动推进？

**Réponse** Une communication non bloquante n'assure pas automatiquement une progression complète en arrière-plan. Selon l'implémentation MPI, les messages peuvent ne progresser que lorsque le thread appelle à nouveau des fonctions MPI. D'autres implémentations utilisent un thread de progression, un cœur dédié, ou parfois une aide de la carte réseau. C'est pourquoi non bloquant ne veut pas toujours dire recouvrement effectif. 非阻塞通信并不保证消息一定会在后台自动完成。具体是否推进，取决于 MPI 实现：有些实现只有在线程再次调用 MPI 函数时消息才会继续推进；另一些会使用专门的 progression 线程、独立核心，甚至借助网卡来推进。因此，“非阻塞”并不总是意味着“真的实现了通信与计算重叠”。

### *Q.8 Quelle est la différence entre `MPI_Barrier` et `MPI_Ibarrier` ? `MPI_Barrier` 和 `MPI_Ibarrier` 有什么区别？

**Réponse** `MPI_Barrier` synchronise de façon bloquante : le processus s'arrête jusqu'à ce que tous arrivent. `MPI_Barrier` 是阻塞式同步：进程会停住直到所有进程都到达。
`MPI_Ibarrier` lance la même synchronisation mais rend la main immédiatement, ce qui permet de recouvrir l'attente avec du calcul ou d'autres communications avant `MPI_Test` ou `MPI_Wait`. `MPI_Ibarrier` 发起同样的同步但立刻返回，因此可以先用计算或其他通信去覆盖等待，再通过 `MPI_Test` 或 `MPI_Wait` 检查结束。

### *Q.9 Citez 2 topologies réseaux différentes. Expliquez leurs avantages et inconvénients. 列举两种不同的网络拓扑，并说明其优缺点

**Réponse** Un anneau est simple et peu coûteux, mais son diamètre est plus grand et les messages traversent souvent plusieurs sauts. Un fat-tree réduit mieux la contention et soutient mieux la bande passante globale, mais au prix d'un réseau plus cher et plus complexe. 环形拓扑简单便宜，但网络直径较大，消息常常需要经过多个跳点。Fat-tree 更能缓解争用并提供更高整体带宽，但代价是网络更贵、结构也更复杂。

### *Q.10 Schématiser les échanges de messages entre 8 rangs MPI pour une implémentation efficace de `MPI_Gather`. Expliquer pourquoi un tel choix. 画出 8 个 MPI rank 之间实现高效 `MPI_Gather` 时的消息交换示意，并解释为什么这样设计

**Réponse** Une implémentation efficace peut par exemple utiliser un arbre binomial : étape 1, `1 -> 0`, `3 -> 2`, `5 -> 4`, `7 -> 6` ; étape 2, `2 -> 0`, `6 -> 4` ; étape 3, `4 -> 0`. L'idée est de réduire la profondeur à `log2(p)` et d'éviter que le rang racine reçoive tout simultanément, ce qui limite la contention et la surcharge au sommet. 一种高效实现例如可以采用二项树：第 1 步 `1 -> 0`、`3 -> 2`、`5 -> 4`、`7 -> 6`；第 2 步 `2 -> 0`、`6 -> 4`；第 3 步 `4 -> 0`。核心思想是把深度降到 `log2(p)`，并避免根进程同时接收所有消息，从而减小争用和根节点压力。

## Ch.10 Placement

### Q.1 Pourquoi le placement est-il important ? 为什么 placement 很重要？

**Réponse** Le placement détermine quels cœurs, caches, nœuds NUMA et liens de communication un thread ou un processus utilisera réellement. Un mauvais placement casse la localité mémoire, augmente les accès distants et peut faire passer des communications sur des chemins plus coûteux. placement 决定了线程或进程实际会用到哪些核心、缓存、NUMA 节点和通信链路。放置不当会破坏内存局部性、增加远端访问，并让通信走上更昂贵的路径。

### Q.2 Qu'est-ce que `OMP_PLACES` et `OMP_PROC_BIND` ? `OMP_PLACES` 和 `OMP_PROC_BIND` 是什么？

**Réponse** `OMP_PLACES` décrit l'ensemble des ressources matérielles candidates pour les threads OpenMP, par exemple des cœurs ou des sockets. `OMP_PROC_BIND` dit ensuite si les threads doivent y rester attachés et selon quelle politique de répartition ; ensemble, ils contrôlent donc l'affinité réelle. `OMP_PLACES` 描述 OpenMP 线程可绑定的硬件资源集合，比如核心或 socket。`OMP_PROC_BIND` 则规定线程是否固定在那里以及按什么策略分配；两者合在一起决定实际亲和性。

### Q.3 Quelle est la différence entre `close` et `spread` ? `close` 和 `spread` 有什么区别？

**Réponse** `close` compacte les threads sur des places voisines pour favoriser le partage de caches et parfois la proximité mémoire. `spread` les écarte pour répartir la pression sur les ressources et occuper plus largement la machine ; le bon choix dépend donc du besoin dominant entre partage/localité et dispersion/équilibrage. `close` 会把线程尽量压到相邻位置上，有利于共享缓存，有时也更利于内存接近。`spread` 则把线程拉开，以分散资源压力并更广地占用机器；因此该选哪种策略取决于你更需要共享/局部性，还是分散/均衡。

## Ch.11 Scalability

### Q.1 Qu'est-ce que la loi d'Amdahl ? 什么是 Amdahl 定律？

**Réponse** La loi d'Amdahl donne la borne haute du speedup quand une partie du programme reste séquentielle. Même avec un nombre infini de processeurs, cette fraction non parallélisable fixe un plafond incompressible sur le temps total. Amdahl 定律给出了存在串行部分时并行加速比的上限。即使处理器数量无限大，那部分无法并行化的工作仍会形成不可消除的时间下限。

### Q.2 Pourquoi la loi d'Amdahl limite-t-elle le speedup ? 为什么 Amdahl 定律会限制 speedup？

**Réponse** Elle limite le speedup parce que le parallélisme n'accélère pas la fraction séquentielle. Quand on ajoute des processeurs, le temps parallèle baisse, mais le temps séquentiel reste presque constant et finit par dominer le total. 它会限制加速比，因为并行化并不能加速串行部分。随着处理器增加，并行部分的时间会下降，但串行时间几乎不变，最终就会主导总时间。

### *Q.3 Quelle est la différence entre scalabilité forte (strong scaling) et scalabilité faible (weak scaling) ? 强可扩展性和弱可扩展性有什么区别？

**Réponse** La strong scaling mesure ce que l'on gagne sur un problème fixe quand on augmente les ressources. 强可扩展性看的是固定问题规模下，增加资源能带来多少收益。
La weak scaling mesure si le temps reste stable quand on augmente à la fois ressources et taille du problème pour garder une charge similaire par processeur. 弱可扩展性看的是在同时增加资源和问题规模、并保持每个处理器负载近似不变时，运行时间能否保持稳定。

### Q.4 Pourquoi un petit changement dans un schéma de communication peut-il changer fortement la scalabilité ? 为什么通信模式中一个小改动也会显著改变可扩展性？

**Réponse** Un petit changement peut modifier la profondeur des communications, la contention ou le degré de sérialisation entre processus. Comme ces coûts grossissent avec le nombre de rangs, un schéma à peine différent localement peut produire une scalabilité très différente globalement. 一个看似很小的改动也可能改变通信深度、争用程度或进程间串行化水平。由于这些成本会随着 rank 数增加被放大，因此局部上略有不同的通信模式，最终可能带来非常不同的全局可扩展性。

## Ch.12 Threads-Synchronisation

### *Q.1 Donner les différences (avantages, inconvénients) entre attente active et attente passive. 给出主动等待和被动等待的区别（优点、缺点）

**Réponse** L'attente active garde le cœur occupé à tester en boucle une condition ; elle minimise la latence de réaction mais gaspille du temps CPU et de l'énergie. 主动等待会让核心一直循环检测条件，因此响应延迟低，但会浪费 CPU 时间和能量。
L'attente passive cède le processeur jusqu'au réveil ; elle économise les ressources mais paie un surcoût de réveil et de replanification. 被动等待会把处理器让出去直到被唤醒，因此更省资源，但要付出唤醒和重新调度的额外开销。

### Q.2 Quelle est la différence entre `#pragma omp critical` et `#pragma omp atomic` ? `#pragma omp critical` 和 `#pragma omp atomic` 有什么区别？

**Réponse** `critical` sérialise une section arbitraire via un verrou implicite ; il est général mais ajoute plus de contention et de surcoût. `atomic` ne protège qu'une opération mémoire simple que le matériel peut souvent réaliser directement ; il est donc plus limité, mais généralement moins coûteux. `critical` 通过隐式锁串行化任意代码段，因此更通用，但争用和开销也更大。`atomic` 只保护简单的内存操作，硬件往往能直接支持，所以功能更受限，但通常成本更低。
