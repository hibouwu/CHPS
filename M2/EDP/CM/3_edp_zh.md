# Évaluation des performances : modélisation mathématique et files d'attente 性能评估：数学建模与排队论

## 0 Introduction 建模导论

### 0.1 Définition 定义

La modélisation mathématique est un outil relativement simple, qui consiste en l'abstraction du système réel en un ensemble de fonctions mathématiques, représentant ses principales fonctionnalités/services afin d'analyser le comportement dudit système. 数学建模 (modélisation mathématique) 是一个相对简单的工具，它将真实系统 (système réel) 抽象为一组数学函数，用以表示其主要功能/服务 (fonctionnalités/services)，从而分析该系统的行为。

### 0.2 Formalismes de description 描述形式化

Le système peut être décrit par différents formalismes : 系统可以用不同的形式化方法描述：

- **Files d'attente 排队模型** — Représentent l'arrivée, l'attente et le service des clients pour calculer notamment le temps de réponse, le débit et l'utilisation des ressources. 用客户的到达、等待和接受服务来描述资源竞争，从而计算响应时间、吞吐量和资源利用率等指标。

- **Réseaux de files d'attente 排队网络** — Relient plusieurs files d'attente pour étudier la circulation des clients entre ressources et les goulets d'étranglement du système. 将多个排队节点连接起来，描述请求在 CPU、磁盘或不同服务之间的流转，并分析整体响应时间和瓶颈，是排队模型的扩展。

- **Chaînes de Markov 马尔可夫链** — Décrivent des transitions probabilistes entre états, le futur étant conditionnellement indépendant du passé lorsque l'état présent est connu. 用状态及其概率转移描述系统演化，并假设在已知当前状态的条件下，未来与过去的历史无关。

- **Automates à états finis / automates temporisés 有限状态自动机／时间自动机** — Décrivent les états et les événements qui déclenchent les transitions, avec des horloges dans le cas temporisé pour exprimer des contraintes de temps. 用状态和触发状态切换的事件描述系统行为，时间自动机进一步引入时钟，以表达超时、截止时间等约束。

- **Réseaux de Petri Petri 网** — Utilisent des places, des transitions et des jetons pour représenter la concurrence, la synchronisation et le partage des ressources. 用库所、变迁和令牌表示并发、同步及资源共享关系，可用于分析死锁等问题。

- **Graphes de tâches 任务图** — Représentent les tâches par des sommets et leurs dépendances par des arcs afin d'analyser le parallélisme et, avec des durées, le chemin critique. 用节点表示任务、用有向边表示依赖关系，从而分析可并行的任务，并在给定任务耗时后确定关键路径。

- **Équations différentielles / modèles fluides 微分方程／流体模型** — Décrivent l'évolution continue de grandeurs agrégées, par exemple une approximation du volume de travail en attente, pour étudier la dynamique et la stabilité du système. 用连续变量及其变化速度描述系统的宏观演化，例如将排队工作量近似为连续流量，以分析动态变化和稳定性。

**Complément — lien entre les formalismes 方法之间的联系。** Ces formalismes ne sont pas exclusifs : une file M/M/1 peut être représentée par une chaîne de Markov à temps continu, tandis que des réseaux de Petri temporisés ou stochastiques permettent d'ajouter des durées aux interactions. 这些方法可以相互联系：例如 M/M/1 排队模型可以表示为连续时间马尔可夫链，而时间 Petri 网或随机 Petri 网可进一步为交互过程加入时间信息。

## 1 Introduction aux files d'attente 排队论导论

### 1.1 Files d'attente 排队论

Une théorie mathématique, basée sur les probabilités et utilisée pour l'évaluation des performances des systèmes où des clients peuvent arriver et demandent l'acquisition de ressources pour une certaine durée. 排队论是一种基于概率论的数学理论 (théorie mathématique)，用于评估一类系统的性能：在这类系统中，客户 (clients，如计算任务、进程或 I/O 请求) 会陆续到达，并请求占用系统资源 (ressources，如 CPU、内存或磁盘) 一段时间。

Certains clients doivent donc patienter avant d'être servis, puis quittent le système. 当请求的资源正被占用时，新到达的客户就必须在队列中等待，直到获得服务并在完成后离开系统。

La file d'attente est alimentée par le flux d'arrivée des clients et vidée par les serveurs (ressources). 等待队列 (file d'attente) 由不断进入的客户到达流 (flux d'arrivée) 填充，并由提供服务的服务器 (serveurs，即系统资源) 逐个处理清空。

**Complément — pourquoi les probabilités ? 为什么需要概率论？** Même si la capacité moyenne de traitement dépasse la demande moyenne, l'aléa sur les instants d'arrivée et sur les durées de service crée des engorgements temporaires. La théorie des probabilités permet de quantifier ces fluctuations pour calculer les temps d'attente et la taille des files. 即使系统的平均处理能力大于平均到达需求，客户到达时刻和服务耗时的随机波动（如短时突发请求）仍会造成暂时拥堵。概率论的作用正是刻画这种随机性，从而算出平均等待时间、队长和资源利用率等指标。

### 1.2 Conditions d'application 应用条件

Lorsque la capacité de service est supérieure à la demande — pour un seul serveur, le taux d'arrivée moyen $\lambda$ est inférieur au taux de service $\mu$, soit $\lambda<\mu$ — le système n'est pas saturé. 当系统的服务能力大于到达需求时，系统处于**未饱和状态 (non saturé)**；对单服务器，平均到达速度记为 $\lambda$，服务速度记为 $\mu$，条件为 $\lambda<\mu$。

Pour les modèles à capacité infinie étudiés dans ce cours, cette condition est nécessaire pour utiliser les formules de régime permanent (voir §2.5, §5.4 et §6.5–6.6). La théorie des files d'attente traite toutefois aussi les régimes transitoires et les systèmes saturés : cette condition ne limite donc pas le domaine de la théorie elle-même. 对本课研究的无限容量模型，只有在服务能力大于到达需求时才能使用稳态公式（具体解释见 §2.5、§5.4 及 §6.5–6.6）。不过排队论本身也可研究瞬态和饱和情况，不能将稳态条件理解为整个理论的适用范围。

*Arrivée, attente, service et départ* 到达、排队、服务与离开

![到达、排队、服务与离开](Images/3_edp_p05.png)

**Complément — lecture du schéma et lien avec la suite 图示解读与后文衔接。** Le schéma ci-dessus résume le cycle de vie d'un client en quatre étapes : **arrivée** $\rightarrow$ **file d'attente (buffer)** $\rightarrow$ **service (serveur)** $\rightarrow$ **départ**. Il faut dès maintenant distinguer la *file d'attente* (attente seule) du *système complet* (file + serveur) : cette distinction sera reprise en §2.2 pour les temps ($w$ vs $r$), en §4.2 pour les effectifs ($q$ vs $n$) et en §5.5 pour la loi de Little. 上图概括了一个客户在单站点中的完整生命周期：**到达（Arrivée）$\rightarrow$ 队列等待（File d'attente）$\rightarrow$ 接受服务（Service）$\rightarrow$ 离开（Départ）**。读图时需注意区分狭义的“队列（仅指等待缓冲区）”与广义的“系统（等待队列 + 服务器）”，这一边界区分直接对应后文 §2.2 的等待时间与响应时间、§4.2 的符号表以及 §5.5 Little 定律的三种应用范围。

### 1.3 Modélisation analytique : intérêt et limites 分析建模的优势与局限

#### 1.3.1 Intérêt 优势

La modélisation mathématique permet l'évaluation d'un nombre considérable de configurations possibles du système à analyser ainsi que des charges qu'il est susceptible de supporter. 数学建模允许评估待分析系统的大量可能配置 (configurations possibles) 以及其可能承受的负载(charges)。

#### 1.3.2 Limites 局限

Les hypothèses et les approximations sur lesquelles se base la modélisation peuvent restreindre le champ d'application de ses résultats et impacter leur précision. 建模所基于的假设和近似 (hypothèses et approximations) 可能限制其结果的应用范围并影响其精度(précision)。

## 2 Modèles de files d'attente 排队模型

### 2.1 Généralités 通用概念

#### 2.1.1 Vocabulaire 词汇表

- Ressource (CPU, mémoire, disque…) ≡ serveur 资源 (CPU, 内存, 磁盘...) 服务器 (serveur)

- Job, processus, requête I/O ≡ client 作业 (Job), 进程 (Processus), IO 请求 客户 (client)

#### 2.1.2 Définition 定义

Les clients attendent dans une file que le serveur soit libre pour les servir. 客户在队列中等待，直到服务器空闲来服务他们。

Le serveur sélectionne, selon une stratégie définie, un client en attente dans la file à servir. 服务器根据定义的策略 (stratégie définie) 从等待队列中选择一个客户进行服务。

### 2.2 Notions clés 关键概念

- Temps de séjour = temps de réponse : moyenne notée $r$, incluant l'attente et le service. 逗留时间 = 响应时间：平均值记为 $r$，包含等待和服务两部分。

- Temps d'attente : moyenne notée $w$, avant le début du service. 等待时间：平均值记为 $w$，指开始接受服务之前的等待。

- Loi de service : distribution des temps de service, de moyenne $s$ ; le taux de service est noté $\mu=1/s$. 服务规律：服务时间的分布，平均服务时间记为 $s$，服务速度记为 $\mu=1/s$。

- Stratégie de service : champ $D$ de la notation de Kendall (§6.4), par exemple FIFO. 服务策略：在 Kendall 记号（§6.4）中用字段 $D$ 表示，例如 FIFO。

- Processus d'arrivée : taux moyen noté $\lambda$ ; $\lambda$ seul ne décrit pas toute la loi du processus. 到达过程：平均到达速度记为 $\lambda$；仅有 $\lambda$ 不能完整描述到达过程的概率规律。

*Attente et séjour* 等待时间与逗留时间

![等待时间与逗留时间](Images/3_edp_p08.png)

**Complément.** Le temps de séjour comprend l'attente et le service ; en moyenne, $r=w+s$. Il faut préciser la frontière du système pour ne pas confondre l'attente en file et le temps de réponse de la requête complète. 逗留时间包含等待和服务两部分，平均值满足 $r=w+s$。计算指标时先明确系统边界，避免把排队时间与整个请求的响应时间混用。

### 2.3 Stratégies de sélection 选择策略

- FIFO : premier arrivé dans la file, premier servi. FIFO: 先到先服务

- LIFO : dernier arrivé dans la file, premier servi. LIFO: 后到先服务

- Random : aléatoire (au hasard). Random: 随机

- Round Robin : cyclique. Round Robin: 循环

- Time sharing (TS) : temps partagé, valable surtout pour la ressource processeur. Time Sharing (TS): 时间共享，主要适用于处理器资源

- Priorités : sélection selon un indicateur ou un niveau de priorité. 优先级：按优先级标记或等级选择客户

### 2.4 Réseaux de files d'attente 排队网络

Les serveurs et les files peuvent être interconnectés pour former un réseau de files d'attente. 服务器和队列可以互连形成排队网络 (réseau de files d'attente)。

*Stations interconnectées* 互连的排队网络

![互连的排队网络](Images/3_edp_p10.png)

### 2.5 Régime permanent et transitoire 稳态与瞬态

#### 2.5.1 Régime transitoire 瞬态

Régime d'évolution d'un système qui n'a pas encore atteint son régime stable ou permanent. Il peut apparaître lors de l'amorce du système ou de sa modification. 系统尚未达到稳定或稳态的演化状态 (régime d'évolution)。它可能在系统启动 (amorce) 或修改时出现。

*Régime transitoire* 瞬态向稳定状态的演化示意

![瞬态向稳定状态的演化示意](Images/3_edp_p11.png)

#### 2.5.2 Régime permanent 稳态

Régime de stabilité que le système atteint après un certain temps de fonctionnement. Dans un régime stationnaire, la distribution des états ne dépend plus du temps. Un régime périodique établi reste dépendant de la phase et doit être distingué de la stationnarité stricte. 系统在一定运行时间后达到的稳定状态 (régime de stabilité)。严格的平稳分布不随时间变化；达到稳定周期的系统仍依赖周期内的相位，应与严格平稳状态区分。

**Complément.** En régime stationnaire, la distribution des états et les moyennes sont constantes, mais la taille réelle de la file continue de fluctuer. Qu'une unité d'exécution reste occupée à 100 % sur une fenêtre finie ne signifie donc pas que la file est instable : des travaux prêts accumulés en amont (par exemple des MMA prêtes pour un Tensor Core) peuvent simplement combler un ralentissement temporaire de l'alimentation (voir §6.7). 稳态下不变的是状态概率分布和长期均值，实际队长仍会随时波动。因此，执行单元在某段时间内连续满载并不意味着队列不稳定：前面积压的就绪工作（如可执行的 MMA 工作）可以填补后续供应变慢的空档，使其在该时间段内保持满载（完整硬件讨论见 §6.7）。

### 2.6 Paramètres de performance 性能参数

Dans un réseau de files d'attente, on définit les paramètres de performance, en régime transitoire comme en régime permanent : 在排队网络中，瞬态和稳态下的性能参数定义为：

- Débit ou fréquence d'arrivée et de sortie : $\lambda$ pour le taux d'arrivée ; sur une période $T$, $a/T$ à l'entrée et $d/T$ à la sortie, où $a$ et $d$ comptent les arrivées et les départs ; ces débits s'égalisent à long terme à l'équilibre. 到达速度与离开速度：到达速度记为 $\lambda$；在观察时长 $T$ 内，到达数量为 $a$、离开数量为 $d$，对应 $a/T$ 与 $d/T$，两者在流量平衡时长期相等。

- Nombre moyen de clients dans le système : $n$, incluant l'attente et le service ; dans la file seule : $q$. 系统中的平均客户数记为 $n$，包含等待中和服务中的客户；仅等待队列中的平均客户数记为 $q$。

- Temps moyen de séjour : $r=w+s$, avec $w$ le temps moyen d'attente et $s$ le temps moyen de service. 平均逗留时间记为 $r=w+s$，其中 $w$ 为平均等待时间，$s$ 为平均服务时间。

- Taux d'utilisation du serveur : $U$, proportion du temps pendant laquelle le serveur est occupé. 服务器利用率记为 $U$，表示服务器处于忙碌状态的时间比例。

### 2.7 Condition de stabilité 稳定性条件

Avant d'utiliser les formules stationnaires ci-dessous, il faut vérifier que le système admet le régime stable correspondant. 使用后文稳态公式前，需要先验证系统能否达到相应的稳定状态。

En régime stationnaire, le débit moyen en entrée est égal au débit moyen en sortie. Cette égalité n'est toutefois pas une condition suffisante de stabilité : pour M/M/1 à capacité infinie, le cas $\lambda=\mu$ n'admet pas de distribution stationnaire normalisable. 稳态下平均入口吞吐量等于平均出口吞吐量。但流量相等本身不是稳定的充分条件，例如无限容量 M/M/1 在 $\lambda=\mu$ 时无可归一化的稳态分布。

### 2.8 Topologies et classes 拓扑与类别

Selon leurs topologies, les réseaux de files d'attente peuvent être : 根据拓扑结构，排队网络可以是：

- Ouverts : des clients arrivent de l'extérieur ; après un service, ils rejoignent une autre station ou quittent le système. Le nombre de clients présents peut varier et des boucles internes restent possibles. Pour le réseau de Jackson ouvert considéré, chaque station doit satisfaire sa condition de stabilité. 开放式 (Ouverts)：存在外部到达和离开；服务后可以去另一站或离开，网络内客户总数可变化，内部路由仍可有反馈环。对本课的开放 Jackson 网络，每个站点都必须满足稳定条件

- Fermés : une population fixe circule dans le réseau, sans arrivée ni départ externe. 封闭式 (Fermés)：固定客户群在网络内循环，没有外部到达和离开

### 2.9 Complément : réseaux fermés 封闭网络的补充说明

#### Définition 定义

Un réseau de files d'attente fermé a un nombre fixe de clients $N$ qui circulent à travers les différents serveurs et files d'attente. 封闭式排队网络有固定数量 $N$ 的客户在不同服务器和队列之间循环。

Il n'y a ni arrivée ni départ externe ; les clients circulent entre les stations du réseau. 客户在网络内部循环；没有外部到达和外部离开，但各站点之间仍有客户流动。

#### Remarques 备注

- Un réseau fermé représente une population fixe de clients. Cela ne fixe pas, à lui seul, une capacité de buffer propre à chaque station. 封闭网络表示客户总数固定；这不等于各站点的缓冲区都设有独立的容量限制

- Parce que l'effectif total $N$ en circulation est borné, aucune file ne peut croître vers l'infini : un système matériel à concurrence fixe (nombre fixe de tâches ou de requêtes en vol) diffère donc fondamentalement d'une file ouverte à arrivées externes indépendantes. 由于在途客户总数 $N$ 有上界，任何站点的队列都不会无限增长；因此具有**固定并发度**的硬件或软件系统（如固定数量的在途请求或循环任务），在稳定性机制上与外部独立无界到达的开放队列（如后文的 M/M/1）有本质区别

- La résolution de tels modèles reste plus complexe. 此类模型的求解更为复杂

*Réseau fermé* 封闭网络示意

![封闭网络示意](Images/3_edp_07.jpg)

## 3 Réseaux de files d'attente ouverts 开放式排队网络

### 3.1 Définition 定义

Un réseau de files d'attente ouvert est un réseau où : 开放式排队网络是这样的网络：

1. Les clients arrivent d'une source externe ; 客户从外部源 (source externe) 到达

2. Ils sont servis par les différents serveurs ; 被不同的服务器服务

3. Ils sont dirigés vers une autre station ou vers la sortie selon le routage. 服务后按路由进入另一站点，或离开系统

### 3.2 Remarques 备注

- On suppose un routage permettant à chaque client de quitter le réseau avec probabilité 1. 模型假设路由使客户最终以概率 1 离开网络

- Une population source illimitée peut ainsi alimenter le flux entrant ; les clients quittent le système après leur parcours. 潜在客户源可以无限地向系统提供客户；客户完成其路径后离开系统

*Réseau ouvert* 开放式排队网络

![开放式排队网络](Images/3_edp_p17.png)

### 3.3 Réseaux de Jackson Jackson 网络

Caractéristiques du réseau de Jackson considéré : Jackson 网络的特征：

- Mono-classe de clients 单类客户 (Mono-classe de clients)

- Arrivées poissoniennes 泊松到达 (Arrivées Poissoniennes)

- Un serveur par station, avec des temps de service exponentiels indépendants. 本节模型中每个站点一个服务器，服务时间独立且服从指数分布

- File de capacité illimitée, discipline FIFO 无限容量队列，FIFO 规则 (File de capacité illimitée, Discipline FIFO)

- Routage probabiliste 概率路由 (Routage probabiliste)

### 3.4 Exemple 示例

Considérons le réseau de Jackson suivant et ses probabilités de routage : 考虑如下 Jackson 网络及其路由概率：

*Réseau de Jackson et routage* Jackson 网络及路由概率

![Jackson 网络及路由概率](Images/3_edp_p19.png)

Dans cet exemple, $\lambda$ est le taux d'arrivée externe total du réseau, $\lambda_i$ le taux d'arrivée total à la station $i$ (flux externe et routage interne compris), et $\mu_i$ le taux de service de son serveur. 本例中，$\lambda$ 表示网络的外部总到达速度，$\lambda_i$ 表示站点 $i$ 接收的总到达速度（包含外部输入与内部路由），$\mu_i$ 表示该站点服务器的服务速度。

$$
\lambda_1=\frac{\lambda}{2},\qquad
\lambda_2=\frac{\lambda}{2}+\frac14\lambda_1=\frac{5\lambda}{8},
$$

$$
\lambda_3=\frac34\lambda_1+\frac15\lambda_2=\frac{\lambda}{2},\qquad
\lambda_4=\lambda_3=\frac{\lambda}{2}.
$$

**Complément.** Le taux d'arrivée à chaque station est la somme du flux externe et des flux reçus après routage. Pour chaque station $i$, vérifier $\lambda_i<\mu_i$ avec le taux total reçu ; il ne suffit pas de comparer le taux d'arrivée externe du réseau au taux de service d'un seul serveur. 各站点的到达速度是外部输入与上游路由流量之和。稳定性须逐站检查 $\lambda_i<\mu_i$，不能只比较网络的外部到达速度与某一台服务器的服务速度。

## 4 Processus de modélisation 建模过程

### 4.1 Hypothèses 假设

#### 4.1.1 Hypothèses à considérer avant la modélisation 建模前需考虑的假设

Équilibre du flux des clients : sur une observation à long terme, le débit moyen de sortie doit être égal au débit moyen d'entrée. Sur une fenêtre finie, le nombre d'arrivées et celui des départs peuvent différer en raison de la variation du nombre de clients présents. 客户流的平衡 (Équilibre du flux des clients)：长期观察下，平均离开速度应等于平均到达速度。有限观察窗口内，到达总数与离开总数可以因系统内人数变化而不同。

Comportement à une étape : dans le modèle à événements élémentaires considéré, les événements surviennent un par un. Une arrivée, un départ ou un transfert entre stations modifie l'état de manière incrémentale. 单步行为 (Comportement à une étape)：在本节采用的基本事件模型中，事件逐个发生。一次到达、离开或站点间转移都会使系统状态发生增量变化。

##### Remarques sur les événements élémentaires 关于单步行为的备注

- Les arrivées et les départs par lots sont exclus de ce modèle simple. 本节简单模型不考虑成批到达和成批离开

- Des déplacements distincts ne se produisent pas simultanément ; un transfert d'un client entre deux stations reste un seul événement de routage. 不同的移动事件不同时发生；同一客户从一个站点转移到另一个站点仍算一个路由事件

Homogénéité : dans le modèle simple considéré, le taux moyen d'arrivée et le taux de service d'un serveur occupé ne dépendent pas de l'état du système. Le taux total de départ peut toutefois dépendre du nombre de serveurs occupés. 齐次性 (Homogénéité)：在本节简单模型中，平均到达速度和单台忙碌服务器的服务速度不依赖系统状态；总离开速度仍可能随忙碌服务器数量变化。

##### Exclusivité 独占性

- Un client ne peut se trouver qu'à une seule station à la fois, en service ou en attente. 一个客户同一时刻只能位于一个站点（服务中或等待中）

- Dans ce modèle à serveurs exclusifs, un client ne demande pas deux services simultanément et chaque serveur ne sert qu'un client à la fois. 在本节独占服务器模型中，一个客户不同时请求两个服务，每台服务器同一时刻只服务一个客户

Service non bloquant : dans le modèle considéré, un service en cours peut s'achever sans attendre la libération d'une autre ressource ou d'une place dans une station en aval. 非阻塞服务 (Service non-bloquant)：在本节模型中，正在进行的服务可以完成，无须等待其他资源释放或下游站点出现空位。

##### Indépendance 独立性

Les clients n'interagissent pas et ne se synchronisent pas entre eux dans ce modèle. Si des tâches doivent attendre d'autres tâches, franchir une barrière de synchronisation ou détenir plusieurs ressources, il faut modéliser ces dépendances séparément. 本模型中的客户之间不发生交互，也不互相同步。若任务需要等待其他任务完成、同步屏障或持有多个资源，就必须把这些依赖另行建模。

**Complément.** Ces hypothèses définissent les modèles simples étudiés ici ; elles ne sont pas des restrictions universelles de la théorie des files d'attente. Un transfert entre deux stations est un seul événement de routage, même s'il diminue d'une unité l'effectif de la station de départ et augmente d'une unité celui de la station d'arrivée. 这些假设限定本节使用的简单模型，不是整个排队论的通用要求。站点间的一次转移可以同时使上一站人数减一、下一站人数加一，仍属于一次路由事件。

### 4.2 Notation 符号表

Dans le reste du cours, on utilisera la notation suivante : 在课程的其余部分，我们将使用以下符号：

| Symbole 符号 | Commentaire 说明 |
| --- | --- |
| $s$ | Temps de service moyen pour un client 客户的平均服务时间 |
| $\mu$ | Taux de service d'un serveur occupé, $\mu=1/s$ 单台服务器忙碌时的服务速度，$\mu=1/s$ |
| $\lambda$ | Taux d'arrivée moyen 平均到达速度 |
| $\lambda_i,\mu_i$ | Taux d'arrivée total et taux de service de la station $i$ 站点 $i$ 的总到达速度与服务速度 |
| $\rho$ | Intensité du trafic : $\lambda/\mu$ pour M/M/1 ; $\lambda/(C\mu)$ pour M/M/C (§6.6.2) 流量强度：M/M/1 中为 $\lambda/\mu$，M/M/C 中为 $\lambda/(C\mu)$（见 §6.6.2） |
| $r$ | Temps de séjour ou de réponse moyen, attente et service compris 平均逗留时间或响应时间，包含等待与服务 |
| $w$ | Temps d'attente moyen avant le service 开始服务前的平均等待时间 |
| $q$ | Nombre moyen de clients dans la file d'attente 仅等待队列中的平均客户数 |
| $n$ | Nombre moyen de clients dans le système, en attente et en service 系统中的平均客户数（等待 + 服务中） |
| $U$ | Fraction du temps pendant laquelle le serveur observé est occupé 所观察服务器处于忙碌状态的时间比例 |
| $T$ | Durée de la période d'observation 观察时长 |
| $b$ | Temps total d'occupation du serveur pendant $T$, d'où $U=b/T$ 观察期 $T$ 内服务器的累计忙碌时长，因此 $U=b/T$ |
| $a$ | Nombre d'arrivées pendant $T$ 观察期 $T$ 内的到达数量 |
| $d$ | Nombre de départs pendant $T$ 观察期 $T$ 内的离开数量 |
| $C$ | Nombre de serveurs identiques 相同服务器的数量 |
| $B$ | Capacité totale du système dans Kendall : attente et service compris (§6.4) Kendall 记号中的系统总容量，包含等待与服务位置（见 §6.4） |
| $N$ | Population fixe d'un réseau fermé (§2.9), effectif moyen dans la forme générale de Little (§5.5), ou population source potentielle dans Kendall (§6.4), selon le contexte 按上下文分别表示封闭网络的固定客户总数（§2.9）、Little 通式中的平均客户数（§5.5），或 Kendall 记号中的潜在客户源总体规模（§6.4） |
| $t$ | Temps moyen associé à la frontière choisie dans la forme générale de Little (§5.5) Little 通式中与所选系统边界对应的平均时间（见 §5.5） |
| $P_k$ | Probabilité stationnaire d'avoir exactement $k$ clients dans le système, attente et service compris 系统中恰有 $k$ 个客户的稳态概率，包含等待与服务中的客户 |
| $P_0$ | Probabilité stationnaire que le système soit vide 系统为空的稳态概率 |
| $P_a$ | Probabilité qu'un client arrivant doive attendre ; l'indice $a$ n'est pas le compteur d'arrivées 到达客户需要等待的概率；下标 $a$ 不是到达数量 |
| $A$ | Charge offerte totale $A=\lambda/\mu$ en §6.6.2 ; en §6.4, le champ $A$ de Kendall désigne la loi des temps inter-arrivées §6.6.2 中为总业务量 $A=\lambda/\mu$；§6.4 中的 Kendall 字段 $A$ 则表示到达间隔分布 |

**Complément.** Dans les formules de performance, $n$ est un nombre moyen de clients. Dans $P_k$, $k$ est un nombre entier de clients et $P_k$ la probabilité de cet état. 性能公式中的 $n$ 表示平均人数；状态概率 $P_k$ 中的 $k$ 则是整数人数，两者不要混淆。

## 5 L'analyse opérationnelle 操作分析

### 5.1 Vue globale 整体视图

L'analyse débute en considérant le système à analyser comme une boîte noire, à l'entrée de laquelle arrivent des jobs (clients) à traiter (servir) et à la sortie de laquelle figurent des jobs traités. 分析从将待分析系统视为黑盒 (boîte noire) 开始，其输入端到达待处理的作业（客户），输出端是已处理的作业。

*Vue globale de l'analyse opérationnelle* 操作分析中的系统边界

![操作分析中的系统边界](Images/3_edp_p25.png)

### 5.2 Caractérisation 特征化

Les caractéristiques du système sont évaluées par mesure ou par hypothèse (utilisateur, fabricant/constructeur). L'évaluation du comportement du système pourra alors s'effectuer dans ce contexte précis. 系统特征通过测量或假设（用户、制造商/构造商）进行评估。然后可以在这个精确的环境中评估系统的行为。

### 5.3 Lois d'utilisation 利用率法则

#### 5.3.1 Taux d'arrivée $\lambda$ 到达速度 $\lambda$

On observe le système pendant une période $T$, durant laquelle $a$ clients sont arrivés ; on en déduit le taux d'arrivée $\lambda$ : 在时间周期 T 内观察系统，期间有 a 个客户到达，我们推导出到达速度 λ：

$$
\lambda = \frac{a}{T}
$$

#### 5.3.2 Utilisation du serveur $U$ 服务器利用率 $U$

Si le serveur a été occupé pendant $b$ unités de temps durant la période d'observation $T$, on en déduit son utilisation $U$ : 如果服务器在整个观察期 T 内仅被占用 b 个时间单位，我们推导出服务器利用率 U：

$$
U = \frac{b}{T} = \frac{b}{d} \times \frac{d}{T}
$$

$d$ étant le nombre de clients servis, $b/d$ est le temps moyen pour servir un client et $d/T$ le taux de départ des clients. Sous l'hypothèse d'équilibre des flux, le taux d'entrée est égal au taux de sortie, d'où : 其中 d 是被服务的客户数量， $\textstyle{\frac{b} {d}}$ 是服务一个客户的平均时间， $\textstyle{\frac{d} {T}}$ 是客户的离开速度。根据平衡假设 (hypothèse d'équilibre)，入口流必须等于出口流，因此：

$$
\begin{array}{c} {U = \frac{b}{d} \times \frac{d}{T} = s \times \frac{d}{T}} \\ {U = \lambda \times s} \end{array}
$$

### 5.4 L'intensité du trafic $\rho$ 流量强度 $\rho$

Pour un seul serveur, l'intensité du trafic $\rho$ compare le taux d'arrivée $\lambda$ au taux de service $\mu$ : 对单服务器，流量强度 $\rho$ 表示平均到达速度 $\lambda$ 与服务速度 $\mu$ 的比值：

$$
\rho = \frac{\lambda}{\mu}
$$

Pour la file M/M/1 de capacité infinie : 对无限容量 M/M/1：

- $\rho<1$ : régime stationnaire, $U=\rho$ et probabilité d'inactivité $1-\rho$. $\rho<1$：存在稳态，$U=\rho$，服务器空闲概率为 $1-\rho$。

- $\rho=1$ : cas critique, sans distribution stationnaire normalisable. $\rho=1$：临界状态，不存在可归一化的稳态概率分布。

- $\rho>1$ : la demande dépasse la capacité de service ; les clients s'accumulent et il n'existe pas de temps d'attente moyen stationnaire fini. $\rho>1$：到达需求超过服务能力，客户持续积累，没有有限的稳态平均等待时间。

L'utilisation physique reste comprise dans $[0,1]$. Lorsque $\rho>1$, la charge offerte dépasse la capacité ; cela ne signifie ni une utilisation supérieure à 100 %, ni un temps d'attente immédiatement infini pour chaque client déjà arrivé. 实际忙碌时间比例始终在 $[0,1]$ 内；$\rho>1$ 表示需求超过容量，并不意味着服务器利用率超过 100%。也不意味着每个已到达客户的等待时间立即变成无穷。

### 5.5 Loi de Little Little 定律

#### 5.5.1 Définition 定义

La loi de Little est une loi générale qui peut s'appliquer à tout système sous les conditions d'existence des moyennes considérées : Little 定律是在所讨论平均量存在的条件下，可应用于各种系统的通用法则：

- Elle n'exige pas de distribution particulière des temps inter-arrivées ou de service. 不要求到达间隔或服务时间服从某个特定分布

- Il n'est pas nécessaire de connaître les détails de l'ordonnancement interne. 不要求知道系统内部的具体调度细节

- On utilise ici sa forme stationnaire : les moyennes à long terme doivent exister et être finies ; le nombre de clients, le temps de séjour et le débit doivent correspondre à la même frontière du système et au même flux de clients. 本节使用其稳态形式：长期平均量须存在且有限，人数、逗留时间和吞吐量应对应同一系统边界与同一客户流

#### 5.5.2 Formule 公式

Le nombre moyen de clients $N$, le temps moyen de séjour ou de réponse $t$ et le débit moyen $\lambda$ d'un système en régime permanent sont reliés par : 稳态系统的平均客户数量 (N)、平均逗留时间或响应时间 (t) 和平均吞吐量 λ 根据以下定律相关联：

$$
\boxed{N = t \times \lambda}
$$

Ici, $N$ et $t$ sont des notations générales : pour le système complet, $N=n$ et $t=r$ ; pour la file seule, $N=q$ et $t=w$ ; pour le service seul, $t=s$. Ce $N$ est une moyenne associée à la frontière choisie, et non nécessairement la population fixe du réseau fermé de §2.9. 这里的 $N$ 和 $t$ 是通用记号：对整个系统，$N=n$、$t=r$；对等待队列，$N=q$、$t=w$；仅考察服务部分时，$t=s$。此处的 $N$ 是所选边界内的平均客户数，不一定是 §2.9 封闭网络中的固定客户总数。

#### 5.5.3 Importance 重要性

- Elle permet de calculer l'un des trois paramètres $(N,t,\lambda)$ en fonction des deux autres. 允许根据其他两个参数计算三个参数 (N,t,λ) 中的一个

- Elle peut s'appliquer à différentes frontières du système : 可针对不同的系统边界使用：

- Un buffer uniquement 仅缓冲区

- Un buffer et un serveur 缓冲区 + 服务器

- Le serveur de la file 队列的服务器

#### 5.5.4 Applications 应用

Un buffer uniquement : $N$ représente le nombre moyen de clients dans la file d'attente, $t$ le temps moyen d'attente avant le service et $\lambda$ le flux d'arrivée (ou de départ) des clients. 仅缓冲区 (Un buffer uniquement) N 表示队列中客户的平均数量，t 表示服务前的平均等待时间，λ表示客户的到达（或离开）流。

Un buffer et un serveur : $N$ représente le nombre moyen de clients dans le système (en attente ou en service), $t$ le temps moyen de séjour (attente et service) et $\lambda$ le flux d'arrivée. 缓冲区 + 服务器 (Un buffer + serveur) N 表示系统中客户的平均数量（队列中或服务中），t 表示平均逗留时间（等待和服务），λ 表示到达流。

Le serveur de la file : $N$ représente le nombre moyen de clients en service, $t$ le temps moyen de service et $\lambda$ le flux d'arrivée. 队列的服务器 (Le serveur de la file) N 表示服务中客户的平均数量，t 表示平均服务时间，λ 表示到达流。

## 6 L'analyse stochastique 随机分析

### 6.1 Limites des lois d'utilisation et de Little 利用率法则和 Little 定律的局限

Les lois d'utilisation et de Little ne supposent aucune loi de probabilité particulière pour les temps inter-arrivées et de service. Elles sont indépendantes de la forme de ces distributions. 它们不考虑关于到达间隔 (inter-arrivées) 和服务的概率法则 (lois de probabilité) 的任何假设。它们完全独立于分布 (distributions)。

### 6.2 Intérêt de l'analyse stochastique 随机分析的优势

La connaissance des distributions permet d'effectuer une analyse stochastique et d'affiner ainsi l'analyse du système en fournissant des résultats plus détaillés que ceux de l'analyse opérationnelle. 了解分布允许进行随机分析，从而通过提供比操作分析更详细的结果来细化系统分析。

### 6.3 Définition 定义

Avec l'analyse stochastique, le système n'est plus une boîte noire. On peut obtenir des résultats détaillés, tels que : 通过随机分析，系统不再是黑盒。这允许获得关于所分析系统的详细结果，例如：

- Le temps d'attente moyen d'un client $w$ 客户的平均等待时间 $w$

- Le nombre moyen de clients dans la file $q$ 队列中的平均客户数 $q$

- La probabilité d'avoir un certain nombre de clients en attente, à déduire des probabilités d'état $P_k$ en distinguant attente et service. 有一定数量客户等待的概率，可由状态概率 $P_k$ 推得，计算时需区分等待中的客户与服务中的客户。

- Le temps de réponse moyen $r$ 平均响应时间 $r$

### 6.4 Notation de Kendall Kendall 符号

Le système est composé d'une file d'attente et d'un ou plusieurs serveurs. Il est représenté par la notation $A/S/C/B/N/D$, avec : 系统由一个队列和一个或多个服务器组成。它将用词 $A / S / C / B / N / D$ 表示：

- A : loi des temps inter-arrivées (l'écart de temps $T$ entre deux arrivées consécutives, de moyenne $\mathbb{E}[T]=1/\lambda$) ; **M**, **D**, **$E_k$** et **G** caractérisent la forme et la variabilité de cette durée : A：相邻两次客户到达之间的**时间间隔 $T$ 的概率分布**（设平均间隔固定为 $\mathbb{E}[T]=1/\lambda$），四个代号具体刻画该时间间隔的分布形态与波动大小：
  - **M** (*Markovien / Memoryless*，马尔可夫／无记忆指数分布) : $T\sim\operatorname{Exp}(\lambda)$, de densité $f(t)=\lambda e^{-\lambda t}$ ($t\ge 0$), de moyenne $\frac{1}{\lambda}$ et de variance $\sigma^2=\frac{1}{\lambda^2}$ (coefficient de variation $CV=\frac{\sigma}{\mathbb{E}[T]}=1$). C'est la seule loi continue **sans mémoire** : $\mathbb{P}(T>t_0+t\mid T>t_0)=\mathbb{P}(T>t)=e^{-\lambda t}$ (le temps déjà attendu n'influence pas le temps restant). Des intervalles exponentiels indépendants de taux $\lambda$ équivalent exactement à un processus de comptage de Poisson de taux $\lambda$. $T\sim\operatorname{Exp}(\lambda)$，概率密度为 $f(t)=\lambda e^{-\lambda t}$（$t\ge 0$），**均值 $\frac{1}{\lambda}$、方差 $\sigma^2=\frac{1}{\lambda^2}$（变异系数 $CV=\frac{\sigma}{\mathbb{E}[T]}=1$）**。它是连续时间下唯一具有**无记忆性**的分布：$\mathbb{P}(T>t_0+t\mid T>t_0)=\mathbb{P}(T>t)=e^{-\lambda t}$（已经等了多久完全不影响接下来还要等多久，因此系统状态只需记录当前人数，可直接建成马尔可夫链）。“相邻间隔独立且服从 $\operatorname{Exp}(\lambda)$”在数学上严格等价于“单位时间内到达个数服从泊松过程 $\operatorname{Poisson}(\lambda)$”。
  - **D** (*Déterministe*，确定性常数分布) : la durée est constante, $T\equiv\frac{1}{\lambda}$, de variance nulle ($\sigma^2=0$, $CV=0$). Il n'y a aucun aléa (ex. déclenchement par horloge à période fixe, ou instruction matérielle à latence fixe). 时间间隔恒为常数 $T\equiv\frac{1}{\lambda}$，**均值 $\frac{1}{\lambda}$、方差 $\sigma^2=0$（$CV=0$）**，没有任何随机波动（如固定周期的硬件定时器触发，或固定周期指令的执行耗时）。
  - **$E_k$** (*Erlang-$k$*，$k$ 阶爱尔朗分布) : modélise une durée totale $T=T_1+T_2+\dots+T_k$ décomposée en **$k$ étapes exponentielles indépendantes en série**, chacune de taux $k\lambda$ (moyenne $\frac{1}{k\lambda}$ par étape) afin de conserver la moyenne totale $\mathbb{E}[T]=k\times\frac{1}{k\lambda}=\frac{1}{\lambda}$. 表示一个总时长 $T=T_1+T_2+\dots+T_k$ 由 **$k$ 个相互独立的指数分布子阶段串联相加**而成。为保持总平均时间仍为 $\frac{1}{\lambda}$，每个子阶段的平均耗时设为 $\frac{1}{k\lambda}$（即 $T_i\sim\operatorname{Exp}(k\lambda)$）：
    - **Mécanisme physique 物理机制与例子** : en arrivée ($A=E_k$), un client n'entre dans le système qu'après $k$ sous-événements poissonniens successifs (ex. un contrôleur qui n'émet une requête qu'après avoir accumulé $k$ paquets élémentaires) ; en service ($S=E_k$), le traitement traverse $k$ sous-étapes séquentielles aléatoires (ex. requête disque décomposée en étapes successives). 用于到达（$A=E_k$）时，表示每累计发生 $k$ 次泊松子事件才触发一次实际到达（如攒够 $k$ 个小数据包才触发一次批处理请求）；用于服务（$S=E_k$）时，表示一次服务必须依次闯过 $k$ 道随机耗时的子工序才算完成。
    - **Densité, variance et lien entre M et D 密度函数、方差收敛及与 M/D 的关系** : sa densité vaut $f(t)=\frac{(k\lambda)^k t^{k-1}e^{-k\lambda t}}{(k-1)!}$ ($t\ge 0$) ; par indépendance des $k$ étapes, les variances s'additionnent : 其概率密度为 $f(t)=\frac{(k\lambda)^k t^{k-1}e^{-k\lambda t}}{(k-1)!}$（$t\ge 0$），且因 $k$ 个阶段独立，各阶段的快慢波动相互抵消，**总方差缩小为指数分布的 $1/k$**：
      $$\mathbb{E}[T]=\frac{1}{\lambda},\qquad \sigma^2=\operatorname{Var}(T)=k\times\frac{1}{(k\lambda)^2}=\frac{1}{k\lambda^2},\qquad CV=\frac{1}{\sqrt{k}}$$
      Ainsi, comme $T=\frac{1}{k}\sum_{i=1}^k X_i$ est la moyenne de $k$ variables $\operatorname{Exp}(\lambda)$ indépendantes : pour $k=1$, $E_1=\text{M}$ ($\sigma^2=1/\lambda^2$) ; quand $k$ croît, les fluctuations se compensent ; et par la **loi des grands nombres**, quand $k\to\infty$, $\sigma^2\to 0$ et $E_k$ converge vers la moyenne constante **D** ($1/\lambda$). 由于 $T=\frac{1}{k}\sum_{i=1}^k X_i$ 本质上是 $k$ 个独立同分布 $\operatorname{Exp}(\lambda)$ 随机变量的算术平均值：**$k=1$ 时 $E_1$ 就是纯随机的指数分布 M**；$k$ 越大，各阶段的快慢越互相抵消；根据**大数定律（loi des grands nombres）**，**当 $k\to\infty$ 时样本均值收敛到数学期望 $\frac{1}{\lambda}$（方差趋于 $0$），$E_k$ 退化为固定常数分布 D**。
  - **G** (*Général*，一般分布) : loi quelconque de moyenne $\frac{1}{\lambda}$ et de variance $\sigma^2$ arbitraire (pouvant être plus régulière que M si $CV<1$, ou plus irrégulière/à rafales si $CV>1$). À taux moyens $\lambda$ et $\mu$ identiques, plus la variance $\sigma^2$ des arrivées ou des services est faible (par ex. passer de M à $E_k$ puis à D), plus la file d'attente moyenne est courte. 任意概率分布，仅设均值为 $\frac{1}{\lambda}$、方差为任意 $\sigma^2$（当 $CV<1$ 时比指数分布更规律，当 $CV>1$ 时则比指数分布更具突发性／重尾性）。在平均速度 $\lambda$ 和 $\mu$ 相同的前提下，到达或服务时间的**方差 $\sigma^2$ 越小（即从 M $\to E_k \to$ D 越规律），随机扎堆越少，平均排队长度和等待时间就越短**。

- S : distribution des temps de service $S$ (durée de traitement d'un client par un serveur, de moyenne $s=1/\mu$), décrite par les mêmes codes (**M**, **D**, **$E_k$**, **G**) en remplaçant $\lambda$ par $\mu$. S：**单次服务时间的分布**（服务器处理一个客户的耗时规律，均值为 $s=1/\mu$），使用与 $A$ 完全相同的四个代号（**M**、**D**、**$E_k$**、**G**，将上述公式中的 $\lambda$ 替换为 $\mu$ 即可）。

- C : nombre de serveurs identiques. Des serveurs hétérogènes nécessitent un modèle adapté, par exemple des stations distinctes ; la notation simple à C serveurs identiques ne suffit pas à les décrire. C: 相同服务器的数量。异构服务器需要适当的模型，例如拆分为不同站点；这一简化的 C 台相同服务器记法不足以描述异构情况

- B : capacité totale du système, soit le nombre maximal de clients présents, en attente et en service ; elle est supposée infinie par défaut. B: 系统的总容量，即等待中与服务中的客户数量上限；默认假设为无限

- N : taille de la population source potentielle, supposée infinie par défaut ; elle est distincte de la capacité B du système. N: 潜在客户源的总体规模，假设为无限以简化分析

- D : ordre ou stratégie de service, par exemple FIFO ou LIFO. D: 服务顺序或策略 (ordre ou stratégie de service)：FIFO、LIFO 等

Les majuscules $A,S,D$ désignent ici des champs de Kendall : $A$ n'est pas la charge offerte de §6.6.2, $S$ n'est pas le temps moyen $s$, et le champ de discipline $D$ se distingue du code « D » signifiant une durée déterministe dans les champs $A$ ou $S$. 这里的大写 $A,S,D$ 是 Kendall 记号的字段：$A$ 不是 §6.6.2 的总业务量，$S$ 不是平均服务时间 $s$，服务策略字段 $D$ 也不同于在 $A$ 或 $S$ 字段中表示确定性时间的分布代码 D。

**Complément — capacité finie $B$, contre-pression et systèmes matériels 有限容量 $B$、反压与硬件系统。** Dans un système matériel réel, les files ont une capacité finie $B$ et la concurrence $N$ est souvent bornée. Lorsque la file approche de sa limite, un mécanisme de **contre-pression (backpressure / stall)** ralentit ou bloque l'émetteur en amont : cela explique pourquoi *cette file locale* ne croît pas à l'infini, mais l'attente peut alors se reporter vers l'amont (et la contre-pression n'augmente pas, à elle seule, l'offre de travail lorsque la file manque déjà de clients). En revanche, le modèle M/M/1 ci-dessous suppose $B=\infty$, $N=\infty$ et des arrivées externes indépendantes sans contre-pression. 真实硬件中的队列容量 $B$ 有限，且并发规模 $N$ 往往有界。当队列接近满时，**反压（backpressure / stall）**会阻塞或减缓上游发射：这解释了为何**该局部队列**不会无限增长，但等待可能因此转移到前端或更上游（要判断整个系统是否稳定，必须把上游一并算入；且反压本身不会增加工作供应）。下文的 M/M/1 模型则默认 $B=\infty$、$N=\infty$ 且外部独立到达无反压，应用时需注意两者的机制差异。

### 6.5 Cas M/M/1 M/M/1 情况

C'est le cas le plus simple : 这是最简单的情况：

- Les arrivées forment un processus de Poisson de taux $\lambda$ ; les temps inter-arrivées sont indépendants et exponentiels de paramètre $\lambda$. 到达为速度 $\lambda$ 的泊松过程；到达间隔独立且服从参数 $\lambda$ 的指数分布

- Les temps de service suivent une loi exponentielle de taux $\mu$, de moyenne $s=1/\mu$. 服务时间服从速度为 $\mu$ 的指数分布，平均服务时间为 $s=1/\mu$。

- Il y a un seul serveur : $C=1$. 只有一个服务器，即 $C=1$。

- La capacité totale du système est infinie : $B=\infty$ (par défaut). 系统总容量无限，即 $B=\infty$（默认）。

- La population source est infinie : $N=\infty$ (par défaut). 潜在客户源的总体规模无限，即 $N=\infty$（默认）。

- La discipline de service est FIFO : $D=\mathrm{FIFO}$ (par défaut). 服务策略为 FIFO，即 $D=\mathrm{FIFO}$（默认）。

#### 6.5.1 Paramètres de performance en régime stationnaire 稳态下的性能参数

Les formules suivantes supposent $0<\lambda<\mu$, des arrivées de Poisson et des temps de service exponentiels indépendants, indépendants du processus d'arrivée. Pour $\lambda=0$, utiliser les limites correspondantes. 以下公式要求 $0<\lambda<\mu$，到达过程与独立指数服务时间相互独立；$\lambda=0$ 时取相应极限。

Débit $\lambda$ : la file est stable, donc les flux s'équilibrent : 吞吐量 $\lambda$：队列稳定，因此到达速度与离开速度平衡：

$$
\mathrm{Débit} = \lambda
$$

Taux d'utilisation du serveur $U$ : c'est la probabilité que le serveur soit occupé : 服务器利用率 $U$：即服务器被占用的概率：

$$
U = \frac{\lambda}{\mu} = \rho
$$

Probabilité que le système soit vide $P_0$ 系统为空的概率 $P_0$

$$
P _{0} = 1 - \rho
$$

Probabilité qu'un client arrivant doive attendre $P_a$ 到达客户需要等待的概率 $P_a$

$$
P _{a} = \rho
$$

Nombre moyen de clients dans le système $n$ 系统中的平均客户数 $n$

$$
n = \frac{\rho}{(1 - \rho)}
$$

Temps moyen de séjour $r$, déduit de la loi de Little : 平均逗留时间 $r$，由 Little 定律推导：

$$
r = \frac{n}{\lambda} = \frac{1}{\mu(1 - \rho)}
$$

Il peut se décomposer en : 可分解为：

$$
r = \frac{1}{\mu} + \frac{\rho}{\mu(1 - \rho)}
$$

Temps moyen d'attente $w$ 队列中的平均等待时间 $w$

$$
w = \frac{\rho}{\mu(1 - \rho)}
$$

Nombre moyen de clients dans la file $q$ 等待队列中的平均客户数 $q$

$$
q = w \times \lambda = \frac{\rho^{2}}{(1 - \rho)}
$$

En régime stationnaire, la probabilité $P_0$ d'avoir 0 client dans le système est : 稳态下，系统中有 0 个客户的概率 $P_0$ 为：

$$
P _{0} = (1 - \rho)
$$

La probabilité $P_k$ d'avoir $k$ clients dans le système est : 系统中恰有 $k$ 个客户的概率 $P_k$ 为：

$$
P_k=(1-\rho)\rho^k,\qquad k=0,1,2,\ldots
$$

**Complément — pourquoi $\rho<1$ est requis et pourquoi $\rho=1$ ne peut pas utiliser ces formules 为什么要求 $\rho<1$ 以及 $\rho=1$ 为何不能直接套公式。** Dans M/M/1 à capacité infinie, la normalisation $\sum_{k=0}^{\infty}P_k=1$ utilise la série géométrique $\sum_{k=0}^{\infty}\rho^k=\frac{1}{1-\rho}$, qui ne converge que si $\rho<1$. À l'équilibre, l'utilisation moyenne vaut $U=1-P_0=\rho<1$ : la probabilité de système vide $P_0=1-\rho>0$ est indispensable pour absorber les fluctuations aléatoires des arrivées et des services. Lorsque $\rho\to 1^-$, $P_0\to 0$ et l'effectif moyen $n=\frac{\rho}{1-\rho}$ (ainsi que $q$, $w$ et $r$) diverge vers $+\infty$. Pour $\rho=1$ ($\lambda=\mu$), tous les états auraient le même poids dans la récurrence ($P_k=P_0$), ce qui ne permet aucune distribution stationnaire normalisable : la file effectue une marche aléatoire sans dérive de retour et ne possède pas d'état stationnaire fini. 在无限容量 M/M/1 中，状态概率归一化 $\sum_{k=0}^{\infty}P_k=1$ 依赖几何级数 $\sum_{k=0}^{\infty}\rho^k=\frac{1}{1-\rho}$，仅当 $\rho<1$ 时收敛。稳态下服务器平均利用率为 $U=1-P_0=\rho<1$：系统必须保留非零的空闲概率 $P_0=1-\rho>0$，才能消化随机到达与服务耗时带来的突发积压。当 $\rho\to 1^-$ 时，$P_0\to 0$，平均队长 $n=\frac{\rho}{1-\rho}$（以及 $q,w,r$）中的分母趋于 $0$，结果发散至无穷大；当 $\rho=1$（$\lambda=\mu$）时，递推关系给出所有状态等权（$P_k=P_0$），无法归一化为概率分布，因此不能直接套用稳态公式。

### 6.6 Cas M/M/C M/M/C 情况

Le cas précédent est étendu à $C$ serveurs identiques (processeurs ou disques), chacun de taux de service $\mu$ et de temps moyen de service $s=1/\mu$, avec des temps de service indépendants ; le taux d'arrivée total reste noté $\lambda$. 将前一种情况扩展为 $C$ 个相同服务器（处理器或磁盘），每台服务速度为 $\mu$、平均服务时间为 $s=1/\mu$，各次服务时间相互独立；系统的总到达速度仍记为 $\lambda$。

Les jobs ou requêtes I/O attendent d'être servis dans la même file. 作业/IO 请求在同一队列中等待被服务。

Si l'un des C serveurs est disponible, il prend en charge un job ou une requête I/O de la file. 如果 C 个服务器中有一个可用，它将服务队列中的一个作业/IO 请求。

#### 6.6.1 Condition de stabilité 稳定性条件

Pour atteindre la stabilité, le nombre moyen de clients arrivant par unité de temps doit être inférieur au nombre de clients que les C serveurs peuvent traiter par unité de temps. 为了达到稳定性，单位时间内到达队列的平均客户数量必须小于 C 个服务器单位时间内能够处理的客户数量。

D'où : 因此：

$$
\lambda < C \mu
$$

#### 6.6.2 Paramètres de performance en régime stationnaire 稳态下的性能参数

On distingue la charge offerte totale $A$ et l'utilisation moyenne d'un serveur $\rho$ : 区分总业务量 $A$ 与单台服务器的平均利用率 $\rho$：

$$
A=\frac{\lambda}{\mu},\qquad \rho=\frac{\lambda}{C\mu}=\frac{A}{C}<1.
$$

**Remarque sur la notation 记号说明.** Certaines présentations notent $\rho$ tantôt l'utilisation moyenne par serveur $\lambda/(C\mu)$, tantôt la charge totale $\lambda/\mu$. Pour éviter toute ambiguïté, on note ici $A=\lambda/\mu$ la charge offerte et $\rho=A/C$ l'utilisation moyenne par serveur. $\mu$ est le taux de chaque serveur, et $A$ est distinct du nombre d'arrivées $a$ mesuré pendant $T$. 不同资料中有时会混用 $\rho$ 表示单台服务器利用率 $\lambda/(C\mu)$ 或总业务量 $\lambda/\mu$。为避免歧义，以下统一用 $A=\lambda/\mu$ 表示总业务量、$\rho=A/C$ 表示每台服务器的平均利用率；$\mu$ 是每台服务器的服务速度，$A$ 与前文观测期间的到达数量 $a$ 不同。

**Débit $\lambda$ :** il vaut $\lambda$ en régime stationnaire. **吞吐量 $\lambda$：** 稳态下等于总到达速度。

**Probabilité que le système soit vide $P_0$ :** **系统为空的概率 $P_0$：**

$$
P_0=\left[\sum_{k=0}^{C-1}\frac{A^k}{k!}+\frac{A^C}{C!(1-\rho)}\right]^{-1}.
$$

**Probabilité qu'un client arrivant doive attendre $P_a$ (Erlang C) :** **到达客户需要等待的概率 $P_a$（Erlang C）：**

$$
P_a=P_0\frac{A^C}{C!(1-\rho)}
    =P_0\frac{A^C}{(C-1)!(C-A)}.
$$

**Nombre moyen de clients dans le système $n$ :** **系统中的平均客户数 $n$：**

$$
n=A+\frac{\rho P_a}{1-\rho}
 =A\left(1+\frac{P_a}{C-A}\right).
$$

**Temps moyen de séjour $r$ :** par application de la loi de Little : **平均逗留时间 $r$：** 由 Little 定律得到：

$$
r=\frac n\lambda=\frac1\mu\left(1+\frac{P_a}{C-A}\right)
 =\frac1\mu+\frac{P_a}{C\mu-\lambda}.
$$

**Temps moyen d'attente $w$ :** **平均等待时间 $w$：**

$$
w=\frac{P_a}{C\mu-\lambda}
 =\frac{P_0A^C}{\mu(C-1)!(C-A)^2}.
$$

**Nombre moyen de clients dans la file $q$ :** $q=\lambda w$. Ces formules supposent des arrivées de Poisson, des services exponentiels indépendants, des serveurs identiques, une file FIFO commune de capacité infinie et la condition de stabilité. Pour $C=1$, on retrouve les formules M/M/1. **队列中的平均客户数 $q$：** $q=\lambda w$。这些公式要求泊松到达、独立指数服务时间、相同服务器、共同的无限容量 FIFO 队列及稳定条件。令 $C=1$，可退化为前一节的 M/M/1 公式。

### 6.7 Complément : discussion appliquée au matériel (exemple GPU / Tensor Core) 补充：硬件系统中的满载与排队分析（以 GPU / Tensor Core 为例）

Après l'étude des modèles théoriques (M/M/1, M/M/C, loi de Little, réseaux ouverts et fermés), cette section examine comment interpréter une situation matérielle courante : **« l'alimentation en instructions ralentit momentanément, mais l'unité d'exécution (par exemple un Tensor Core exécutant des instructions MMA) reste à plein régime »**. 学完上述排队模型后，本节讨论如何将理论边界应用于真实硬件场景：**“某段时间内前端指令供应变慢，但后端执行单元（如执行 MMA 的 Tensor Core）依然保持持续满载”**。

#### 6.7.1 Deux précautions de modélisation 两个建模前提与条件修正

Avant d'appliquer un modèle de file simple au matériel, deux raccourcis courants doivent être nuancés : 在把简单排队模型套用到硬件流水线前，需要先修正两个常见的过度简化表述：

1. **« Tant qu'il y a du travail dans la file, le serveur est à plein régime » (« 队列里有工作，服务器就满载 »)** — Cet énoncé vaut pour un modèle à serveur unique sans blocage interne, où tout client présent est immédiatement éligible au service (hypothèses de §4.1). Dans le matériel, des instructions présentes dans un buffer peuvent encore attendre des opérandes, la résolution de dépendances de données ou la libération d'autres ressources d'exécution : **avoir un arriéré en file ne signifie donc pas automatiquement disposer d'instructions MMA prêtes à être exécutées immédiatement**. 这一说法仅适用于“客户一旦在队中就具备服务条件、且无内部阻塞”的理想模型（§4.1 假设）。在硬件中，排在队列里的指令还可能在等待操作数就绪、数据依赖解除或执行资源空闲，因此**“有队列积压”未必意味着“有可立即执行的 MMA 工作”**。
2. **« Une file de capacité finie n'explose pas, donc le système est stable » (« 有限队列不会爆炸，所以系统稳定 »)** — Une capacité finie $B$ et la contre-pression (backpressure) garantissent seulement que *la longueur de cette file locale* reste bornée. L'attente peut toutefois se déplacer vers le front-end ou plus en amont ; pour juger de la stabilité globale, il faut inclure ces étages amont. De plus, **la contre-pression explique pourquoi la file ne croît pas indéfiniment, mais n'augmente pas l'offre de travail** : si l'unité manque déjà de travail exécutable, ajouter de la contre-pression ne relèvera pas son utilisation. 有限容量 $B$ 与反压只能直接说明**该局部队列的长度有界**，等待可能被转移到前端或更上游；判断整个系统是否稳定必须把上游一并计入。此外，**反压主要解释“队列为什么不会无限增长”，但反压本身不会增加工作供应**——若队列原本就经常缺活，加入反压并不能提高执行单元利用率；要解释“为什么能持续满载”，仍需看是否始终有足够的、可执行的工作。

#### 6.7.2 Six mécanismes pouvant expliquer le plein régime observé 解释观测到持续满载的六种可能机制

1. **Arrivées régulières ou fluctuations compensées 输入更有规律，或快慢波动相互抵消**
   L'hypothèse d'arrivées de Poisson indépendantes de M/M/1 ne s'applique pas automatiquement à un flux d'instructions. Dans un modèle illustratif où l'unité traite $10$ unités de travail par tranche de temps et reçoit une séquence périodique stricte : M/M/1 的独立泊松到达假设并不自动适用于指令流。考虑一个纯粹的示意模型：执行单元每个时间段处理 $10$ 份工作，而输入严格按周期重复：
   - Entrée 输入 : $15, 5, 15, 5, 15, 5\dots$ ; Traitement 处理 : $10, 10, 10, 10, 10, 10\dots$ ; Arriéré en fin de tranche 积压 : $5, 0, 5, 0, 5, 0\dots$
   Si le travail de chaque tranche est disponible dès le début de la tranche, un buffer de taille $5$ suffit pour maintenir l'unité à 100 % d'utilisation : l'offre moyenne égale la capacité ($10$), l'arriéré reste borné et aucune contre-pression n'est déclenchée. Les boucles régulières, l'ordonnancement statique ou le pipeline logiciel (software pipelining) créent souvent une structure temporelle où une forte offre est suivie d'un creux compensateur. Au-delà du taux moyen $\lambda$, il faut donc examiner l'amplitude des fluctuations, la durée maximale des creux et la corrélation temporelle. 若每段工作在该段开始时即可用，队列只需容纳 $5$ 份积压就能一直满载：平均输入等于处理能力，积压有界，且无需触发反压。程序中的重复循环、固定调度或软件流水（software pipelining）都可能产生比独立随机到达更规律的供给。因此除平均到达速度外，还需看波动幅度、断供最长时间以及快慢之间的相关性（需结合具体执行轨迹判断）。

2. **Entrelacement de plusieurs warps ou chaînes d'instructions indépendantes 多个 warp 或多条独立指令链交错供给**
   Un warp isolé alterne souvent : *préparation des données $\rightarrow$ émission MMA $\rightarrow$ attente de dépendance $\rightarrow$ tour suivant*. Mais l'unité d'exécution reçoit la superposition de plusieurs sources : 单个 warp 可能经历“准备数据 $\rightarrow$ 发 MMA $\rightarrow$ 等待依赖 $\rightarrow$ 准备下一轮”，但执行单元看到的是多个来源的合流：
   - warp A bloqué $\rightarrow$ warp B émet ; warp B bloqué $\rightarrow$ warp C émet ; warp C bloqué $\rightarrow$ warp A de nouveau prêt. warp A 暂时不能发 $\rightarrow$ warp B 可以发；warp B 暂时不能发 $\rightarrow$ warp C 可以发；warp C 暂时不能发 $\rightarrow$ warp A 又可以发。
   Chaque source subit des pauses, mais leur flux agrégé peut alimenter l'unité en continu sans même nécessiter une file profonde d'instructions MMA déjà émises : le vivier de warps éligibles et le parallélisme d'instructions (ILP) au sein d'un même warp comblent les creux. La documentation NVIDIA distingue explicitement les warps *actifs*, *éligibles (prêts)* et *sélectionnés (émis)*, et rappelle qu'un stall de warp n'impacte pas toujours la performance globale ([Nsight Compute — Scheduler & Stalls](https://docs.nvidia.com/nsight-compute/ProfilingGuide/#sections-and-rules)). *Limite :* si tous les warps attendent simultanément la même barrière ou la même donnée mémoire, multiplier les sources ne comblera pas le creux. 每个来源都有停顿，合起来却可能持续供给，甚至不必假设存在很深的已发射 MMA 队列；可供选择的就绪 warp 以及同一 warp 内的独立工作也能填补空档。NVIDIA 调度说明明确区分了活跃 warp、就绪（eligible）warp 和实际选中发射的 warp，并指出单个 warp 停顿未必影响整体性能（见 [Nsight Compute 调度与停顿说明](https://docs.nvidia.com/nsight-compute/ProfilingGuide/#sections-and-rules)）。其限制在于：若所有 warp 同时等待同一同步屏障或同一种数据供应，增加来源数量也无法填平空档。

3. **Travail en vol dans le pipeline couvrant la latence 流水线允许多份工作同时在途，并发覆盖完成延迟**
   Il faut distinguer une longue file d'attente amont du travail *déjà engagé dans le pipeline d'exécution* mais non encore terminé. Dans un pipeline abstrait de latence $16$ cycles acceptant un nouveau travail tous les $4$ cycles (aux cycles $0, 4, 8, 12\dots$), une fois le pipeline rempli, une opération s'achève tous les $4$ cycles. Par la loi de Little (§5.5) : 这与“等待队列很长”相关但有区别：有些工作已进入执行流水线，只是尚未完成。假设一个抽象流水线从进入到完成需 $16$ 个周期，每隔 $4$ 个周期可接受一份新工作（第 $0,4,8,12\dots$ 周期），填满后即可每 $4$ 个周期完成一份。由 Little 定律（§5.5）：
   $$\text{Travail moyen en vol (平均在途工作数)} = \text{Débit de complétion (完成吞吐量)} \times \text{Temps moyen en vol (平均在途时间)}$$
   Ici, un débit de $1/4$ par cycle sur $16$ cycles correspond à $4$ travaux en vol en moyenne : cet effectif couvre la latence du pipeline et ne traduit pas un engorgement incontrôlé (ces chiffres sont purement illustratifs et le plein débit reste soumis aux dépendances, aux conflits de ressources et au rythme d'alimentation). 在该示意例子中，每 $4$ 周期完成一份对应平均 $4$ 份工作同时在途。这些在途工作是在覆盖执行延迟，并非失控积压（此为一般流水线示意，不可直接等同于某代 Tensor Core 的具体硬件参数，且满吞吐仍受依赖、资源冲突和供给节奏制约）。

4. **Arriéré initial important non encore épuisé sur la fenêtre d'observation 初始积压足够大，观察窗口内尚未耗尽**
   Même si l'alimentation moyenne ultérieure est inférieure à la capacité ($\lambda < \mu$), l'unité peut rester pleine longtemps. Avec $\mu = 10$ et $\lambda = 8$ unités par tranche de temps, si $100$ unités exécutables sont déjà prêtes au début de l'observation, la vitesse nette de résorption vaut : 即使后续平均供应低于处理能力（$\lambda < \mu$），执行单元也可能连续满载很久。设简化模型中 $\mu=10\text{ 份/时间单位}$、$\lambda=8\text{ 份/时间单位}$，且观察开始时已存有 $100$ 份可执行工作，则执行端持续满载时积压的净消耗速度为：
   $$\mu - \lambda = 2$$
   L'arriéré soutient alors un plein régime pendant : 因此大约可支撑持续满载的时间为：
   $$T = \frac{100}{10 - 8} = 50 \text{ unités de temps (个时间单位)}$$
   Observer 100 % d'utilisation sur ces $50$ unités est donc totalement compatible avec une sous-alimentation à long terme ($\lambda < \mu$), en particulier si la mesure ne porte que sur la boucle principale ou démarre après une phase de préparation. 在这 $50$ 个时间单位内看到 100% 利用率，与长期供应不足（$\lambda < \mu$）完全兼容。若测量只截取计算主循环，或工作在测量开始前已准备好，尤其需要考虑这种观察窗口效应。

5. **Dénominateur statistique de « 100 % d'utilisation » “利用率 100%”的统计分母不同**
   L'écart peut provenir de la définition de la métrique plutôt que du matériel. Une unité inactive pendant $100$ cycles puis au maximum pendant $100$ cycles est utilisée à $50\%$ sur les $200$ cycles écoulés (`elapsed`), mais à $100\%$ sur ses seuls cycles actifs (`active`). Nsight Compute distingue explicitement `.pct_of_peak_sustained_active` et `.pct_of_peak_sustained_elapsed` ([Nsight Compute — Metrics Structure](https://docs.nvidia.com/nsight-compute/ProfilingGuide/#metrics-structure)). Il faut donc vérifier si « plein régime » désigne : une instruction en cours, un slot d'émission occupé, le débit crête du pipeline Tensor, ou le débit global du kernel. 有时并非调度机制改变，而是测量分母不同。例如某单元前 $100$ 个周期空闲、后 $100$ 个周期按峰值工作，按全部 $200$ 个经过周期（elapsed）算为 $50\%$，若仅按活跃周期（active）归一化则可能显示 $100\%$。Nsight Compute 明确区分 `.pct_of_peak_sustained_active` 与 `.pct_of_peak_sustained_elapsed`（见 [Nsight Compute 指标说明](https://docs.nvidia.com/nsight-compute/ProfilingGuide/#metrics-structure)）。因此需先确认“满载”是指有工作在执行、发射槽被占用、Tensor 流水线达峰值吞吐，还是整个 kernel 吞吐接近峰值，不能直接互换。

6. **Quantité de travail par instruction non uniforme 所比较的“指令数量”不代表相同工作量**
   Si les instructions MMA successives diffèrent par leurs dimensions de matrice, leur précision ou leur chemin d'exécution, compter les instructions émises par cycle ne mesure pas directement la demande imposée à l'unité : 若前后发射的是不同形状、精度或执行路径的 MMA，“每周期发了几条指令”无法直接反映对执行单元的服务需求。简化模型中更合适的比较是：
   $$\text{Taux de demande de service (到达的服务需求速度)} = \text{Instructions par unité de temps (每单位时间到达的指令数)} \times \text{Demande moyenne par instruction (每条指令的平均服务需求)}$$
   Une baisse du nombre d'instructions n'implique pas une baisse proportionnelle du travail à exécuter ; $\lambda$ et $\mu$ ne peuvent être unifiés qu'après avoir fixé le type d'instruction et la frontière de mesure. 指令条数减少不一定意味着需执行的工作量同比减少；只有固定指令类型与计量边界后，才适合抽象为统一的 $\lambda$ 和 $\mu$。

#### 6.7.3 Grille de diagnostic 现象与解释对照表

| Phénomène observé 观察到的现象 | Explication à privilégier 更值得考虑的解释 |
| --- | --- |
| L'amont ne ralentit que lorsque la file approche de la saturation 队列接近满时，上游才发慢 | Contre-pression (backpressure) 反压 |
| L'entrée suit un rythme répétitif et l'arriéré oscille dans une plage fixe 输入存在重复节奏，积压在固定范围内循环 | Arrivées régulières ou fluctuations contrôlées 规律输入或受控波动 |
| Un warp se bloque mais d'autres warps continuent d'émettre 单个 warp 停顿，其他 warp 持续发射 | Entrelacement de sources multiples 多来源交错供给 |
| Le travail en vol reste borné tout en maintenant un débit de sortie continu 在途工作数有界，但能持续完成工作 | Concurrence du pipeline couvrant la latence 流水线并发覆盖延迟 |
| Plein régime au début, puis le manque d'alimentation apparaît 开始阶段满载，随后供应不足暴露出来 | Arriéré initial et effet de fenêtre d'observation 初始积压与观察窗口 |
| L'utilisation change nettement selon l'intervalle ou la métrique choisie 换统计区间或指标后，利用率明显变化 | Dénominateur de mesure ou périmètre d'observation 测量分母或观察范围 |
| Le nombre d'instructions baisse sans baisse proportionnelle de la charge exécutée 指令数下降，执行需求却没有同比下降 | Volume de travail par instruction différent 指令工作量不同 |

Dans un cas réel de Tensor Core, plusieurs facteurs — *sources multiples fournissant assez de travail indépendant, pipeline maintenant un volume suffisant en vol, et ressources finies limitant l'entrée par contre-pression* — peuvent coexister. Identifier le facteur déterminant exige d'inspecter les instructions exactes, leurs dépendances et la définition des compteurs matériellement mesurés. 对实际的 Tensor Core 场景，“多来源提供足够的独立工作、流水线保持足够的在途量、有限资源通过反压限制继续进入”往往同时成立；究竟哪一因素主导了满载，需结合具体指令、依赖关系和性能计数器定义来判断，不能仅凭“后面发慢了但 Tensor Core 仍很忙”就断定只是某一个内部队列在起作用。
