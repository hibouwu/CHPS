# Évaluation des performances : workloads 性能评估：工作负载

## 1 Introduction 引言

Il existe deux classes de workloads : charges réelles et charges synthétiques. 存在两类工作负载：真实负载和合成负载。

### 1.1 Les charges réelles 真实负载

- Observées ou mesurées pendant une exécution sur un système réel. 在真实系统运行期间直接观察或测量得到。
- Une exécution et son contexte complet ne sont pas exactement reproductibles ; une trace peut être rejouée dans les limites des événements enregistrés. 一次真实运行及其完整环境难以精确复现；已记录的轨迹可以重放，但只能复现轨迹中保留的事件。

Avantages : 优点：

- Représentativité optimale 代表性最优
- Richesse des détails 细节丰富

Inconvénients : 缺点：

- Grande taille 数据量大
- Contexte initial difficile à reproduire intégralement 原始运行环境难以完全复现
- Extraction parfois difficile 提取有时较为困难

### 1.2 Les charges synthétiques 合成负载

- Créées selon des caractéristiques déterminées pour représenter un contexte ou comportement précis. 根据设定的特征人工构造，用以代表特定的运行场景或行为。
- Peuvent être répétées à l'infini. 可以无限次重复运行。

Avantages : 优点：

- Développement rapide 开发快速
- Répétition à l'infini 可无限重复
- Taille réduite 数据量小
- Portabilité 可移植性好

Inconvénients : 缺点：

- Représentativité moindre 代表性相对较低
- Nombreuses approximations 包含较多近似假设

**Complément — exécution réelle, trace et charge synthétique 真实运行、轨迹重放与合成负载的关系。** Une *exécution réelle* dépend de l'état instantané de l'OS, des caches et des autres processus, ce qui la rend non déterministe d'un essai à l'autre. Une *trace* fige une exécution réelle sous forme de journal d'événements horodatés (ex. liste d'accès disque ou mémoire) : elle est rejouable à l'identique, mais un simple rejeu à horodatages fixes (boucle ouverte) ne réagit pas si le nouveau système répond plus vite ou plus lentement (sauf recours à des traces élastiques enregistrant les dépendances). Une *charge synthétique* peut être construite à partir des caractéristiques statistiques extraites d'une trace (taux moyen $\lambda$, loi des tailles, localité) ou directement spécifiée selon les besoins de l'expérience afin de faire varier facilement les paramètres. **真实运行**受操作系统调度、缓存状态和背景噪声影响，每次运行难以完全一致；**轨迹（trace）**将某次真实运行录制成事件日志（如 I/O 请求序列），虽可重放，但简单的固定时间戳重放属于开环回放，无法随新系统的快慢动态改变后续请求（除非采用额外记录依赖关系的弹性轨迹）；**合成负载**则既可以依据真实轨迹提取的统计特征（如到达速度 $\lambda$、请求大小分布、地址局部性）构造，也可以按实验设计需求直接设定参数。

## 2 Sélection des workloads 工作负载的选择

La sélection de la charge détermine l'utilité et l'exactitude des résultats de l'évaluation. Quatre aspects majeurs : 工作负载的选择决定了性能评估结果的实用性与准确性，需重点考虑四个方面：

1. Service délivré par le système 系统提供的服务

2. Niveau de détail demandé 所需的细节级别

3. Représentativité des charges 负载的代表性

4. Alignement temporel 时间对齐

### 2.1 Service délivré 提供的服务

Le système est un fournisseur de services. Isoler le service étudié des autres services disponibles. 待分析系统被视为服务提供者；必须明确界定所研究的目标服务，并将其与系统提供的其他服务区分开。

Remarque : un service indépendant du contexte est plus représentatif et ne limite pas la validité des résultats à un contexte particulier. 备注：独立于特定上下文的服务更具代表性，不会把分析结论局限于某一个特殊场景。

Exemple d'analyse du stockage : 示例（存储系统分析）：

- Le système étudié est le stockage, le disque étant le composant fournissant le service. 研究对象是整个存储系统，而磁盘只是其中提供底层存储服务的组件。
- Choisir des métriques au niveau système : temps de réponse moyen ou TPS, plutôt que seul temps d'accès au disque. 评价指标应选在系统服务层级（如平均响应时间、每秒事务数 TPS），而非仅看底层磁盘的硬件访问时间。

**Complément — frontière du service 服务边界的意义。** Le temps d'accès physique au disque (recherche + rotation + transfert) ignore le cache de pages du système d'exploitation, la file d'attente de l'ordonnanceur I/O et le contrôleur RAID. Placer la frontière au niveau du *service de stockage* permet de mesurer la performance réellement perçue par l'application cliente. 底层磁盘硬件访问时间只反映磁头寻道、旋转和传输耗时，忽略了操作系统页缓存（Page Cache）、I/O 调度队列及控制器的影响；将边界设在“存储服务”层级，测出的响应时间和吞吐量才对应上层应用实际感受到的性能。

### 2.2 Niveau de détail 细节级别

#### 2.2.1 Relation avec la méthode d'évaluation 与评估方法的关系

- La modélisation mathématique exige moins de détails, souvent des moyennes ou distributions. 数学建模所需的细节较少，通常只需平均值或概率分布（如第三课的 $\lambda$、$\mu$ 与分布类型）。
- Simulation et mesure utilisent des charges horodatées : traces ou charges exécutables. 仿真和实测则需要带时间戳的细粒度负载：事件轨迹（traces）或可直接运行的程序负载。

#### 2.2.2 Traitement des traces 轨迹处理

Les traces sont souvent volumineuses et détaillées : 轨迹通常数据量庞大且细节繁杂：

- Utiliser des traces de haut niveau pour réduire les données à analyser. 可采用高层级轨迹（如记录系统调用或事务级事件，而非逐条指令）以缩减数据规模。
- Adapter leur finesse aux résultats obtenus et souhaités. 应根据目标分析精度来裁剪轨迹的粒度。

### 2.3 Représentativité 代表性

Un workload de test doit représenter une application, un comportement ou une classe d'applications partageant des paramètres. 测试负载必须能够代表某个目标应用、某类特定行为，或具有共同特征的一类应用。

La charge et l'application doivent correspondre sur : 测试负载与目标应用需在以下维度保持一致：

- Taux d'arrivée moyen $\lambda$ : nombre de requêtes soumises par unité de temps. 平均到达速度 $\lambda$：单位时间内提交的请求数量。
- Ressources demandées 请求占用的资源类型与规模。
- Profil d'utilisation des ressources 资源使用画像（各资源随时间的负载比例与访问模式）。

### 2.4 Alignement temporel 时间对齐

La charge doit suivre et représenter les variations temporelles du comportement du système. 工作负载必须反映系统行为随时间的演变规律。

Niveaux possibles : 可分为三个级别：

- Faible : tendance temporelle uniquement. 弱：仅反映宏观的时间变化趋势（如全天平均流量的涨落）。
- Fort : reproduction précise de tous les événements. 强：精确复现所有事件发生的时刻与先后顺序。
- Intermédiaire : changements clés de la tendance. 中等：捕捉构成行为趋势转折的关键阶段变化。

### 2.5 Autres critères de sélection 其他选择标准

#### 2.5.1 Bien utiliser les résultats de calibration 合理设置负载水平

Les niveaux de charge décrivent les régimes d'utilisation : 不同的负载水平用于考察系统在不同运行区域的表现：

- Faible : temps de réponse de base avec peu d'attente. 低负载：排队极少，用于估计无排队竞争时的基准响应时间 $r_0$。
- Typique : utilisation courante. 典型负载：评估系统在日常工作压力下的常规表现。
- Proche de la saturation : capacité de débit et croissance du temps de réponse. 接近饱和的高负载：测试系统的最大吞吐能力上限，以及排队导致的响应时间急剧上升。

Le meilleur ou pire cas dépend de la métrique : débit élevé ne signifie pas faible temps de réponse. “最好”或“最坏”情况取决于所选指标：高负载下吞吐量可能达到最高（对吞吐量是好情况），但排队等待也最严重（对响应时间是最坏情况）。

#### 2.5.2 Répétition 重复性

La même charge doit produire des résultats comparables à chaque exécution. 同一负载在相同条件下多次运行，应产生可比较的一致结果。

Remarque : une forte variabilité des résultats conduit à de larges intervalles de confiance et rend la charge moins commode. 备注：若每次运行结果波动过大，会导致置信区间过宽，需要大量重复实验才能得到可靠均值。

### 2.6 Intervalle de confiance 置信区间

Un intervalle exprime l'incertitude sur un paramètre, ici la moyenne de population $\mu$, estimée par la moyenne d'échantillon $\bar X$. À 95 %, environ 95 % des intervalles construits par répétition de la procédure couvrent $\mu$ ; cela n'attribue pas une probabilité à un intervalle déjà fixé. Ici, $\mu$ est une moyenne statistique, pas le taux de service de CM3. 置信区间用于量化对总体参数（此处为总体均值 $\mu$，用样本均值 $\bar X$ 估计）的不确定性。95% 置信水平是指：若用同一抽样与计算方法反复构造许多区间，长期约有 95% 的区间会覆盖真实总体均值 $\mu$（注意：此处的 $\mu$ 表示统计总体均值，不是第三课中的服务速度）。

À confiance égale, un intervalle plus étroit est plus précis. Pour les mêmes données, augmenter la confiance élargit l'intervalle. 在置信水平相同时，区间越窄说明估计越精确；而在同一批样本数据下，要求更高的置信水平（如从 95% 提高到 99%）必然会使区间变宽。

#### 2.6.1 Calcul de l'intervalle 置信区间的计算

Pour des observations indépendantes, lorsque l'approximation normale de la moyenne convient : 对独立观测样本，当样本均值适用正态近似时：

Notations : $X_i$ est la mesure $i$, $n$ le nombre de mesures, $\bar X$ leur moyenne et $s$ leur écart type empirique ; $1-\alpha$ est le niveau de confiance et $z_{1-\alpha/2}$ le quantile correspondant de la loi normale standard. 符号说明：$X_i$ 为第 $i$ 次观测值，$n$ 为样本数，$\bar X$ 为样本均值，$s$ 为样本标准差，$1-\alpha$ 为置信水平，$z_{1-\alpha/2}$ 为标准正态分布的双侧临界值。

$$
\left[\bar X-z_{1-\alpha/2}\frac{s}{\sqrt n},\quad \bar X+z_{1-\alpha/2}\frac{s}{\sqrt n}\right].
$$

Pour une population normale de variance inconnue, remplacer $z_{1-\alpha/2}$ par le quantile de Student $t_{1-\alpha/2,n-1}$ à $n-1$ degrés de liberté. Le terme $s/\sqrt n$ est l'erreur standard estimée de la moyenne, et non la dispersion d'une mesure isolée ; voir [CM4–5 §5](45_edp_zh.md). 若总体服从正态分布但方差未知（尤其是小样本），应将 $z_{1-\alpha/2}$ 替换为自由度为 $n-1$ 的 Student $t$ 分布分位数 $t_{1-\alpha/2,n-1}$（详见 [CM4–5 §5](45_edp_zh.md)）。

**Complément — pourquoi diviser par $\sqrt{n}$ et valeurs usuelles de $z$ 为什么分母有 $\sqrt{n}$ 及常用临界值。** Si $X_1,\dots,X_n$ sont indépendantes de variance $\sigma^2$, la variance de leur moyenne $\bar X=\frac{1}{n}\sum_{i=1}^n X_i$ vaut $\operatorname{Var}(\bar X)=\frac{1}{n^2}\sum_{i=1}^n\sigma^2=\frac{\sigma^2}{n}$, d'où un écart type de la moyenne (erreur standard) égal à $\frac{\sigma}{\sqrt{n}}\approx\frac{s}{\sqrt{n}}$. Sous cette approximation normale (à niveau de confiance fixé, pour des observations indépendantes et une variance empirique $s^2$ stable), réduire de moitié la largeur de l'intervalle demande donc de multiplier par environ $4$ le nombre de mesures $n$. Sous la loi normale standard, les intervalles $\pm 1\sigma$, $\pm 2\sigma$ et $\pm 3\sigma$ couvrent environ $68.27\%$, $95.45\%$ et $99.73\%$ ; les quantiles exacts pour des niveaux de confiance bilatéraux de $90\%$, $95\%$ et $99\%$ sont respectivement $z_{0.95}\approx 1.645$, $z_{0.975}\approx 1.960$ et $z_{0.995}\approx 2.576$. 因为 $n$ 次独立测量的样本均值 $\bar X=\frac{1}{n}\sum_{i=1}^n X_i$ 的方差为 $\operatorname{Var}(\bar X)=\frac{1}{n^2}\sum_{i=1}^n\sigma^2=\frac{\sigma^2}{n}$，开方后得到**均值的标准误差（Standard Error）为 $\frac{\sigma}{\sqrt{n}}\approx\frac{s}{\sqrt{n}}$**（注意区分单次测量的波动 $s$ 与均值估计的误差 $s/\sqrt{n}$）。这也意味着：**在相同置信水平、观测独立且样本方差稳定的正态近似下，若想把置信区间宽度缩小一半，重复测量次数 $n$ 约需增加到原来的 $4$ 倍**。在标准正态分布下，$\pm 1\sigma$、$\pm 2\sigma$、$\pm 3\sigma$ 分别覆盖约 $68.27\%$、$95.45\%$、$99.73\%$（精确双侧临界值在 $90\%$、$95\%$、$99\%$ 下分别为 $1.645$、$1.960$、$2.576$）。

## 3 Caractérisation des workloads 工作负载的特征化

Quel que soit le type de charge, extraire les caractéristiques clés du contexte étudié. 无论工作负载属于哪一类，都需要提取其关键特征来刻画所研究的运行场景。

### 3.1 Intérêt 目的

- Représenter ou identifier le contexte. 表征或识别所研究的运行场景。
- Produire une charge synthétique liée au réel mais répétable à l'infini. 据此构造既贴近真实负载特征、又能无限重复运行的合成负载。

### 3.2 Implémentation 实施方法

Techniques statistiques : moyennes pour résumer le niveau, dispersion et quantiles pour décrire les fluctuations, histogrammes pour visualiser la distribution et clustering pour séparer des groupes. 常用统计方法包括：用平均值概括总体水平，用离散指标和分位数刻画波动，用直方图展示分布形态，并用聚类区分异质类别。

### 3.3 Moyennes et facteurs de dispersion 平均值与离散指标

#### 3.3.1 Moyennes 平均值

La technique la plus simple résume par une seule valeur les valeurs possibles d'un paramètre et donne sa tendance. 最简单的方法是用单一数值概括某参数在负载中的所有取值，以反映其中心趋势。

Le choix entre moyenne arithmétique, géométrique ou harmonique dépend du paramètre. 常见平均值有算术平均、几何平均和调和平均，须根据参数的物理意义选择。

Soient $x_1,\ldots,x_n$ les $n$ observations du paramètre $X$. On distingue ci-dessous les moyennes arithmétique $\bar X_{\mathrm A}$, géométrique $\bar X_{\mathrm G}$ et harmonique $\bar X_{\mathrm H}$ ; sans indice, $\bar X$ désigne ensuite la moyenne arithmétique. 设参数 $X$ 有 $n$ 个观测值 $x_1,\ldots,x_n$。以下分别用 $\bar X_{\mathrm A}$、$\bar X_{\mathrm G}$、$\bar X_{\mathrm H}$ 表示算术、几何与调和平均；后文不带下标的 $\bar X$ 默认指算术平均。

Moyenne arithmétique $\bar X_{\mathrm A}$ : somme divisée par l'effectif, adaptée par exemple à des durées mesurées sur des requêtes de même poids. 算术平均 $\bar X_{\mathrm A}$：总和除以样本数，适用于可直接相加的量（如等权重请求的耗时，或等时间段内的速度）。

$$
\bar X_{\mathrm A} = \frac{1}{n} \sum_{i = 1} ^{n} x _{i}
$$

Moyenne géométrique $\bar X_{\mathrm G}$ : moyenne multiplicative de valeurs strictement positives, utile pour résumer des ratios normalisés à des références comparables. 几何平均 $\bar X_{\mathrm G}$：对正数作连乘后再开 $n$ 次方，适用于汇总已归一化的相对性能比或加速比（如 SPEC 基准测试）。

$$
\bar X_{\mathrm G} = \left(\prod_{i = 1} ^{n} x _{i}\right) ^{1 / n}
$$

Moyenne harmonique $\bar X_{\mathrm H}$ : inverse de la moyenne des inverses, adaptée à des vitesses positives lorsque chaque segment porte la même quantité de travail. 调和平均 $\bar X_{\mathrm H}$：倒数的算术平均的倒数，适用于**每个样本对应相同工作量（或相同距离）时的速度平均**。

$$
\bar X_{\mathrm H} = \frac{n}{\frac{1}{x _{1}} + \frac{1}{x _{2}} + \cdots + \frac{1}{x _{n}}}
$$

Exemples : 示例：

- Temps moyen de réponse : moyenne arithmétique. 平均响应时间：算术平均。
- Taux global de défauts de cache : défauts totaux / accès totaux, soit une moyenne arithmétique pondérée par les accès. 总体缓存未命中率：总未命中次数 $\div$ 总访问次数，等价于按每次运行的访问次数加权的算术平均。
- Vitesse moyenne sur distances égales : harmonique ; sur durées égales : arithmétique. 等距离（或等工作量）下的平均速度：调和平均；等时间段下的平均速度：算术平均。

**Complément — pourquoi et comment choisir entre $\bar X_{\mathrm A}$, $\bar X_{\mathrm H}$ et $\bar X_{\mathrm G}$ 三种平均值的选择原则与推导。** Le choix d'une moyenne repose sur l'invariant physique que l'on souhaite conserver : 选择哪种平均值，取决于**哪个总量在物理上具有可加性（或可乘性）**：
1. **Dérivation de la moyenne harmonique pour les vitesses 速度为何用调和平均：** Si $n$ segments portent chacun la *même quantité de travail* $W$ (ex. même nombre d'instructions ou même distance) et sont exécutés aux vitesses $v_1,\dots,v_n$, la durée du segment $i$ vaut $t_i=\frac{W}{v_i}$. La vitesse moyenne globale est le travail total divisé par le temps total : 若 $n$ 个阶段各自完成**相同的工作量 $W$**（如相同指令数或相同路程），速度分别为 $v_1,\dots,v_n$，则第 $i$ 阶段耗时为 $t_i=\frac{W}{v_i}$。总平均速度必须等于“总工作量 $\div$ 总时间”：
   $$\bar v = \frac{\text{Travail total}}{\text{Temps total}} = \frac{nW}{\sum_{i=1}^n t_i} = \frac{nW}{\sum_{i=1}^n \frac{W}{v_i}} = \frac{n}{\sum_{i=1}^n \frac{1}{v_i}} = \bar X_{\mathrm H}$$
   En revanche, si chaque segment dure le *même temps* $T$, le travail du segment $i$ vaut $W_i=v_i T$, et $\bar v=\frac{\sum v_i T}{nT}=\frac{1}{n}\sum v_i=\bar X_{\mathrm A}$. 反之，若每个阶段持续**相同的时间 $T$**，则总工作量为 $\sum v_i T$，总平均速度为 $\frac{\sum v_i T}{nT}=\bar X_{\mathrm A}$（算术平均）。
2. **Pourquoi la moyenne géométrique pour des ratios normalisés 归一化比值为何用几何平均：** Pour comparer deux machines A et B sur $n$ programmes de temps $T_{\mathrm{A},i}$ et $T_{\mathrm{B},i}$, le rapport des moyennes géométriques vérifie $\frac{\bar X_{\mathrm G}(\mathrm A)}{\bar X_{\mathrm G}(\mathrm B)}=\left(\prod_{i=1}^n\frac{T_{\mathrm{A},i}}{T_{\mathrm{B},i}}\right)^{1/n}$ : le classement relatif entre A et B reste **invariant quelle que soit la machine de référence choisie pour normaliser**, propriété que la moyenne arithmétique ne respecte pas. 对多组基准测试的相对比值 $\frac{T_{\mathrm{A},i}}{T_{\mathrm{B},i}}$，几何平均满足 $\left(\prod_{i=1}^n\frac{T_{\mathrm{A},i}}{T_{\mathrm{B},i}}\right)^{1/n}=\frac{\bar X_{\mathrm G}(\mathrm A)}{\bar X_{\mathrm G}(\mathrm B)}$，即**无论选哪台机器作为归一化基准，两台被测系统的相对优劣比例都保持不变**；若对相对比值误用算术平均，更换基准机器就可能颠倒排名结论。 Notice aussi l'inégalité classique $\bar X_{\mathrm H}\le\bar X_{\mathrm G}\le\bar X_{\mathrm A}$ (avec égalité si et seulement si tous les $x_i$ sont égaux). 此外恒有均值不等式 $\bar X_{\mathrm H}\le\bar X_{\mathrm G}\le\bar X_{\mathrm A}$（当且仅当所有 $x_i$ 相等时取等号）。

#### 3.3.2 Moyenne pondérée 加权平均值

Chaque valeur de la charge est associée à un coefficient déterminant son poids. 加权平均值将每个不同的观测值 $x_i$ 与反映其重要程度或出现频数的权重系数 $p_i$ 关联起来。

Moyenne arithmétique pondérée : 算术加权平均值：

$$
\bar{X} = \frac{\sum_{i = 1} ^{n} p _{i} x _{i}}{\sum_{i = 1} ^{n} p _{i}}
$$

Les poids $p_i$ sont non négatifs et leur somme strictement positive. 其中 $p_i$ 为非负权重，且权重总和大于零。

#### 3.3.3 Facteur de dispersion 离散指标

La moyenne seule ne suffit pas lorsque les valeurs sont très variables. 当参数取值波动较大时，仅靠平均值无法反映数据的分散程度（例如 $\{10,10,10\}$ 与 $\{0,10,20\}$ 的均值同为 $10$，但稳定性截然不同）。

La variance de population est notée $\sigma^2$ ; à partir des $n>1$ observations, on l'estime par la variance empirique corrigée $s^2$ (souvent aussi notée $\sigma^2$ par abus de notation) : 总体方差记为 $\sigma^2$；由 $n>1$ 个样本观测值估计时，采用修正样本方差 $s^2$（分母取 $n-1$ 以消除用样本均值 $\bar X$ 代替总体均值带来的偏差；部分讲义中也直接简记为 $\sigma^2$）：

$$
s^2 = \frac{1}{n - 1} \sum_{i = 1} ^{n} (x_i - \bar X)^2
$$

L'écart type empirique $s$ est la racine carrée de $s^2$ et garde l'unité des observations : 样本标准差 $s$ 是样本方差的平方根，其量纲与原观测值一致：

$$
s = \sqrt{s^2}
$$

Le coefficient de variation empirique $CV$ compare l'écart type à la moyenne ; pour une grandeur positive de moyenne $\bar X>0$ : 样本变异系数 $CV$ 是标准差与均值的无量纲比值，用于衡量相对波动大小（便于比较不同单位或不同量级的指标）：

$$
CV = s/\bar X
$$

Remarque 1 : un écart type empirique nul ne garantit pas que les exécutions futures soient constantes. 备注 1：样本标准差为零仅说明本次采样的观测值恰好相同，不能保证未来运行永远恒定。

Remarque 2 : si la dispersion est élevée, regrouper les valeurs en classes peut être plus pertinent. 备注 2：若标准差或 $CV$ 很大，说明负载可能混杂了多种不同模式，宜先将样本分箱或聚类后再分别分析。

### 3.4 Quantiles et histogrammes 分位数与直方图

#### 3.4.1 Définition des quantiles 分位数定义

Les quantiles sont des points qui partagent une série ordonnée en $q$ parties d'effectifs comparables. 分位数是将从小到大排序后的数据集划分为 $q$ 个等比例区间的分割点。

##### Quantiles usuels : 最常用的分位数：

- Centiles : cent parties. 百分位数（100-分位数）：将有序样本分为 100 等份。
- Déciles : dix parties. 十分位数（10-分位数）：将有序样本分为 10 等份。
- Quartiles : quatre parties. 四分位数（4-分位数）：将有序样本分为 4 等份（即 $25\%, 50\%, 75\%$）。
- Médiane : deux parties. 中位数（2-分位数）：将有序样本分为左右各 $50\%$ 的 2 等份。

#### 3.4.2 Calcul des quantiles 分位数计算

Pour une proportion $p\in(0,1)$, le quantile empirique $Q_p$ peut être défini par $Q_p=\inf\{x:F_n(x)\ge p\}$, où $F_n(x)=\#\{i:x_i\le x\}/n$ est la proportion des $n$ observations inférieures ou égales à $x$. 对比例 $p\in(0,1)$，经验分位数定义为 $Q_p=\inf\{x:F_n(x)\ge p\}$，其中经验分布函数 $F_n(x)=\#\{i:x_i\le x\}/n$ 表示样本中不大于 $x$ 的比例。直观地说，将 $n$ 个数据从小到大排好序后，**$Q_p$ 就是排在第 $\lceil np\rceil$ 个位置（即累计比例首次达到或超过 $p$）的那个样本值**：

- Premier décile ($Q_{0.10}$) : plus petite valeur observée couvrant au moins 10 % des observations. 第 1 个十分位数（$Q_{0.10}$）：使至少 10% 的观测值不大于它的最小样本值。
- Troisième quartile ($Q_{0.75}$) : plus petite valeur observée couvrant au moins 75 % des observations. 第 3 个四分位数（$Q_{0.75}$）：使至少 75% 的观测值不大于它的最小样本值。

#### 3.4.3 Exemple 示例

| Valeur 值 | 4 | 7 | 9 | 11 | 13 | 15 | 18 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Effectif 出现次数 | 6 | 5 | 10 | 6 | 2 | 7 | 4 |

- Premier quartile $Q_1 = 7$, au moins 25 % des valeurs lui sont inférieures ou égales. 第 1 四分位数 $Q_1 = 7$（至少 25% 的值不大于它）。
- Troisième quartile $Q_3 = 15$, au moins 75 % des valeurs lui sont inférieures ou égales. 第 3 四分位数 $Q_3 = 15$（至少 75% 的值不大于它）。
- Médiane $Q_2 = 9$, les observations 20 et 21 valent toutes deux 9. 中位数 $Q_2 = 9$（排序后第 20、21 个观测值均为 9）。

**Complément — détail du calcul par effectifs cumulés 用累计频数手算上述分位数的步骤。** Le nombre total d'observations vaut $N=6+5+10+6+2+7+4=40$. En cumulant les effectifs dans l'ordre croissant des valeurs : 先求总样本数 $N=6+5+10+6+2+7+4=40$，再按值从小到大累加出现次数（确定每个值占用的排名区间）：
- Valeur $4$ : rangs $1\text{ à }6$ (cumul $6/40=15\%$) ;
- Valeur $7$ : rangs $7\text{ à }11$ (cumul $11/40=27.5\%$) $\implies$ le rang $0.25\times 40=10$ tombe sur **$Q_1=7$** ;
- Valeur $9$ : rangs $12\text{ à }21$ (cumul $21/40=52.5\%$) $\implies$ les rangs centraux $20$ et $21$ tombent sur **$\text{Médiane}=9$** ;
- Valeurs $11$ et $13$ : rangs $22\text{ à }27$ puis $28\text{ à }29$ (cumul $29/40=72.5\%$) ;
- Valeur $15$ : rangs $30\text{ à }36$ (cumul $36/40=90\%$) $\implies$ le rang $0.75\times 40=30$ tombe sur **$Q_3=15$**.

#### 3.4.4 Écart interquartile 四分位距

L'écart interquartile est noté $IQR=Q_3-Q_1$, avec $Q_1=Q_{0.25}$ et $Q_3=Q_{0.75}$. 四分位距记为 $IQR=Q_3-Q_1$（即第 3 四分位数减去第 1 四分位数），表示剔除首尾各 25% 极端值后**中间 50% 数据的跨度**。

Un écart plus grand ou plus petit traduit une dispersion plus forte ou plus faible. 四分位距越大，说明中间主体数据越分散；越小则越集中。

Ici, $Q_3-Q_1=15-7=8$ décrit l'étendue de la moitié centrale ; son importance dépend du contexte et de l'unité. 在上例中，$IQR=Q_3-Q_1=15-7=8$；其绝对大小需结合数据的物理单位与量级来评判。

#### 3.4.5 Médiane 中位数

Autre nom du quantile d'ordre 1/2, valeur centrale d'une série croissante. 即 $50\%$ 分位数，表示升序排列样本的中心位置值。

Elle est moins sensible aux valeurs aberrantes que la moyenne. 与算术平均值相比，中位数具有**抗离群值（稳健性）**：个别极大或极小的异常值不会改变中心排名位置。

Soient $u_1\le\cdots\le u_m$ les observations triées, de nombre total $m$ : 设升序排列后的全部观测值为 $u_1\le\cdots\le u_m$（总数为 $m$），中位数计算公式为：

- Avec $m=2n+1$ observations (impair) : médiane $=u_{n+1}$. 若样本量 $m=2n+1$ 为奇数：取正中间第 $n+1$ 项，中位数 $= u _{n + 1}$。
- Avec $m=2n$ observations (pair) : médiane $=(u_n+u_{n+1})/2$. 若样本量 $m=2n$ 为偶数：取中间第 $n$ 项与第 $n+1$ 项的均值，中位数 $= \frac{u _{n} + u _{n + 1}} {2}$。

**Complément (conventions sur les quantiles empiriques).** Pour un effectif pair $m=2n$, la définition par fonction de répartition inverse (§3.4.2) donne $Q_{0.5}=u_n$, tandis que la définition symétrique de la médiane prend la moyenne $(u_n+u_{n+1})/2$ (par exemple sur $\{1,2,3,4\}$, la première donne $2$ et la seconde $2.5$). Dans les deux exemples ci-dessous, $u_n=u_{n+1}$, si bien que les deux conventions coïncident. **补充说明（经验分位数的两种常见约定）。** 当样本量为偶数 $m=2n$ 时，按 §3.4.2 经验分布反函数定义会取第 $n$ 项 $u_n$，而对称中位数定义则取中间两项的均值 $(u_n+u_{n+1})/2$（例如对 $\{1,2,3,4\}$，前者得 $2$，后者得 $2.5$）。在下文两个课程算例中，由于正中间两项数值恰好相等（$u_n=u_{n+1}$），两种约定给出完全相同的结果。

#### 3.4.6 Exemple 1 : médiane, moyenne et mode 示例 1：中位数、平均值与众数

| Valeur 值 | 4 | 7 | 9 | 11 | 13 | 15 | 18 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Effectif 出现次数 | 6 | 5 | 10 | 6 | 2 | 7 | 4 |

- Moyenne pondérée : $\bar X = \frac{4\times 6+7\times 5+9\times 10+11\times 6+13\times 2+15\times 7+18\times 4}{40} = \frac{418}{40} = 10.45$. 加权平均值：$\frac{418}{40}=10.45$。
- Médiane : $9$ (les observations de rangs 20 et 21 valent 9). 中位数：$9$（共 $40$ 项，第 20、21 项均为 $9$）。
- Mode : $9$ (valeur la plus fréquente, d'effectif 10). 众数：$9$（出现次数最多的值，共出现 $10$ 次）。

#### 3.4.7 Exemple 2 : médiane, moyenne et mode 示例 2：中位数、平均值与众数（异常值影响对比）

| Valeur 值 | 32 | 41 | 48 | 58 | 60 | 97 | 124 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Effectif 出现次数 | 15 | 10 | 15 | 15 | 15 | 2 | 6 |

- Moyenne pondérée : $\bar X = \frac{32\times 15+41\times 10+48\times 15+58\times 15+60\times 15+97\times 2+124\times 6}{78} = \frac{4318}{78} \approx 55.4$, tirée vers le haut par les valeurs extrêmes (97 et 124). 加权平均值：$\frac{4318}{78}\approx 55.4$（被右侧极少数大值 $97$ 和 $124$ 明显拉高）。
- Médiane : $48$ (sur $N=78$ observations, les effectifs cumulés sont $15, 25, 40\dots$ ; les rangs 39 et 40 valent donc 48). 中位数：$48$（总样本数 $N=78$，累计频数依次为 $15, 25, 40\dots$，故第 39、40 项均落在 $48$，不受尾部大值干扰）。
- Modes : $32, 48, 58\text{ et }60$ (ex æquo avec l'effectif maximal 15 : distribution multimodale). 众数：$32, 48, 58, 60$（出现次数同为最高值 $15$，属于多峰分布）。

#### 3.4.8 Représentation graphique de la variabilité 离散程度的图形表示：箱线图

La boîte à moustaches est particulièrement adaptée à la représentation d'un échantillon variable. 箱线图是一种非常适合直观展示样本离散程度、偏态与尾部特征的统计图形工具。

Elle montre notamment : 箱线图可呈现以下统计特征：

- La moitié centrale, entre les quartiles 25 % ($Q_1=Q_{0.25}$) et 75 % ($Q_3=Q_{0.75}$), dont la hauteur est l'$IQR$ ; 中间 50% 数据的分布区间（箱体下沿为第 1 四分位数 $Q_1=Q_{0.25}$，上沿为第 3 四分位数 $Q_3=Q_{0.75}$，箱体高度即四分位距 $IQR$）；
- La position de la médiane, ainsi que la moyenne lorsqu'elle est marquée en complément ; 中位数（箱内横线）以及可另行标出的平均值位置（中位数偏离箱体中心或偏离均值可反映分布偏斜程度）；
- Les points situés au-delà des moustaches (valeurs extrêmes ou aberrantes selon la règle choisie) ; 超出须线范围的外侧数据点（极端值，是否判定为离群点取决于所采用的须线规则）；
- Les moustaches, qui représentent dans la convention du cours les quantiles 5 % ($Q_{0.05}$) et 95 % ($Q_{0.95}$) (d'autres conventions utilisent les extrêmes de l'échantillon ou les observations les plus éloignées dans la limite de $1.5\,IQR$). 上下须线端点：本课介绍以 5% 分位数（$Q_{0.05}$）和 95% 分位数（$Q_{0.95}$）作为须线端点的约定（其他常见约定包括取样本极值，或按 Tukey 规则延伸到 $1.5\,IQR$ 判别边界以内最外侧的观测值）。

*Boîtes à moustaches du temps de réponse selon le pas d'accès* 不同访问步长下的响应时间箱线图

![不同访问步长下的响应时间箱线图](Images/2_edp_01.jpg)

L'axe horizontal est le pas d'accès, le vertical le temps de réponse. Comparer médianes, boîtes puis points de forte latence : un comportement typique proche n'exclut pas des queues différentes. 图中横轴为访问步长，纵轴为响应时间。读图时先比较中位数和箱体高度（主体 50% 请求的表现），再观察上方须线与高延迟外侧点：即使中位数相近，不同步长下的长尾延迟也可能相差悬殊。

#### 3.4.9 Analyse plus fine de la variabilité 异质样本的进一步细分

Si une forte variabilité révèle un échantillon hétérogène : 当整体方差很大、数据呈现出多种截然不同的行为模式（异质样本）时：

Identifier d'abord ses classes par une technique de clustering, puis les analyser séparément. 应先用聚类算法将混合样本拆分为内部同质的若干子类别，再对每个类别分别计算统计指标（否则把读写混合或大小请求直接平均会掩盖真实特征）。

### 3.5 Classification 聚类分类

#### 3.5.1 Technique k-means k-means 聚类

K-means regroupe les points à partir des distances entre les éléments. k-means 算法根据样本点在特征空间中的距离远近，自动将数据划分为 $C$ 个紧凑的簇。

Les données peuvent décrire des grandeurs quantitatives, comme durée, taille ou débit, ou des événements qualitatifs préalablement encodés de manière appropriée en valeurs numériques. 特征可以是定量指标（如持续时间、请求大小、吞吐量），也可以是经过适当编码转化为数值的定性属性（注意：无序类别不宜随意编码为 $1,2,3$ 以免人为引入虚假的大小和距离关系；此外不同量纲的特征通常需先做归一化以防大数值特征主导距离）。

#### 3.5.2 Classification par k-means k-means 算法流程

En HPC, les données sont le plus souvent quantitatives ; on emploie couramment la distance euclidienne. 在高性能计算中，被分析的特征多为定量数值，最常用欧几里得距离（即两点坐标差的平方和开方，$\|x-y\|_2=\sqrt{\sum_d(x_d-y_d)^2}$）。

##### Étapes de k-means : k-means 迭代步骤：

1. Choisir $C$ centres initiaux $\mathrm{Ctr}_1,\ldots,\mathrm{Ctr}_C$ pour $C$ classes ; $C$ est le nombre de groupes, souvent noté $k$ dans le nom k-means. 选定聚类数 $C$（即算法名称 k-means 中的 $k$），并初始化 $C$ 个簇中心 $\mathrm{Ctr}_1,\ldots,\mathrm{Ctr}_C$（初始中心的选择会影响最终收敛到的局部最优解）。

2. Affecter chaque point à son centre le plus proche. 分配步骤：计算每个样本点到各中心 $\mathrm{Ctr}_j$ 的距离，将其归入距离最近的中心所属的类别。

3. Recalculer les centres $\mathrm{Ctr}_{\mathrm{new}}$ comme barycentres des classes. 更新步骤：计算每个新形成类别内所有点的质心（均值向量），作为新的簇中心 $\mathrm{Ctr}_{\mathrm{new}}$。

4. Répéter 2 et 3 avec $\mathrm{Ctr}\gets\mathrm{Ctr}_{\mathrm{new}}$ jusqu'à convergence. 令 $\mathrm{Ctr}\gets\mathrm{Ctr}_{\mathrm{new}}$，交替重复步骤 2 和步骤 3，直至满足收敛条件。

#### 3.5.3 Calcul du barycentre 质心计算

Barycentre $G$ d'un groupe de $N$ points $n_i$, avec poids $p_i\ge0$ de somme positive ; ici $n_i$ est un point ou vecteur de caractéristiques, pas un effectif : 设某类别包含 $N$ 个样本点（特征向量）$n_1,\dots,n_N$，对应非负权重 $p_i$，则该类的加权质心 $G$ 为（注意此处 $n_i$ 表示第 $i$ 个样本的坐标向量，不是人数）：

$$
G = \frac{1}{\sum_{i = 1} ^{N} p _{i}} \sum_{i = 1} ^{N} p _{i} n _{i} \quad \text{其中} \sum_{i = 1} ^{N} p _{i} \neq 0
$$

Pour des points de poids identiques : 当所有样本点权重相等（$p_i=1$）时，质心即为各点坐标的算术平均：

$$
G = \frac{1}{N} \sum_{i = 1} ^{N} n _{i}
$$

#### 3.5.4 Condition de convergence 收敛条件

Convergence lorsque les affectations ne changent plus entre deux itérations. 当某次迭代后所有样本点所属的类别与上一轮完全相同（质心不再移动）时，算法达到收敛。

On peut aussi imposer un nombre maximal d'itérations. 实际实现中也常设置最大迭代次数上限以强制终止。

*K-means : de l'initialisation aux groupes stables* k-means 从初始化到稳定聚类的迭代过程

![k-means 从初始化到稳定聚类的迭代过程](Images/2_edp_02.jpg)

Dans la figure, 0a contient les données et 0b initialise quatre centres. Affectation au centre le plus proche et recalcul des barycentres alternent jusqu'au regroupement stable 4a. 图中 `0a` 为原始未分类数据点，`0b` 随机放置了 4 个初始中心；随后不断交替执行“按最近距离划分区域”与“将中心移至区域质心”，直到 `4a` 中 4 个簇的边界和中心不再变化。

### 3.6 Autres outils : histogrammes 其他工具：直方图

#### 3.6.1 Histogramme simple 单参数直方图

L'histogramme simple, à un paramètre, compte les observations ayant des valeurs proches. 单参数直方图将取值范围划分为若干连续区间（分箱 bins），统计落在每个区间内的观测样本数量。

Il relie la représentation empirique des observations et quantiles à la description par une distribution, par exemple normale. 它是连接离散实测数据与连续概率分布模型（如正态分布、指数分布）的桥梁：通过观察直方图的形状，可以判断负载参数适合用哪种理论概率分布来近似拟合。

#### 3.6.2 Histogrammes multiples 多参数联合直方图

Utilisés pour plusieurs paramètres liés, le plus souvent deux ou trois. 当需要同时考察两个或三个参数之间的相关性（如“请求大小”与“到达间隔”是否相关）时，使用多维直方图。

Pour deux paramètres, des tours de hauteurs différentes se placent sur une grille. 二维直方图在平面网格上用不同高度的柱体（如同棋盘上的塔）表示两个参数组合同时出现的频数。

## 4 Workloads synthétiques 合成工作负载

### 4.1 Paramètres à générer 要生成的参数

Paramètres courants en HPC : 在高性能计算中，合成负载最常需要生成的四类核心参数是：

1. Timing : dates $\mathrm{date}_i$, intervalles $\delta t$ et taux moyen $\lambda$. 时序参数：事件到达时刻 $\mathrm{date}_i$、相邻到达间隔 $\delta t$ 与平均到达速度 $\lambda$。

2. Adresses d'accès $\mathrm{adr}$ dans un espace de $M$ adresses. 访存或磁盘访问地址 $\mathrm{adr}$（地址空间共包含 $M$ 个可选离散地址）。

3. Nombre de sources $N_{\mathrm{src}}$ ; il ne détermine pas à lui seul la loi des intervalles. 负载源数量 $N_{\mathrm{src}}$（仅凭源数量本身不能直接决定到达间隔的分布类型）。

4. Temps d'exécution ou de service, de moyenne $s$ ; le taux de service correspondant est $\mu=1/s$. Ici, $s$ est une durée, pas l'écart type de la partie statistique. 单次执行或服务耗时，平均值记为 $s$，对应的服务速度为 $\mu=1/s$（注意此处 $s$ 表示平均服务时间，不是第 2、3 节中的样本标准差）。

Leurs valeurs sont générées selon des lois de probabilité. 上述参数的取值通常借助伪随机数发生器与概率分布逆变换来生成。

### 4.2 Génération du timing 生成：时序

#### 4.2.1 Temps inter-arrivées 到达间隔时间

Générer les dates d'arrivée des instructions, accès cache ou disque, et tâches : 生成指令、缓存/磁盘访问请求或计算任务的到达时刻，需依据以下三个要素：

- À partir d'une date de référence : zéro au démarrage ou date d'un événement ; 参考基准时刻 $\mathrm{date}_{\mathrm{ref}}$：可取 $0$（系统启动时刻）或前一个关联事件的发生时刻；
- Selon une fréquence représentant la pression exercée sur le système ; 到达频率（到达速度 $\lambda$）：反映外部对被测系统施加的负载压力大小；
- Selon un mode d'utilisation caractérisant le comportement de l'application. 使用模式：刻画应用发出请求的时间规律（平稳、周期或突发）。

#### 4.2.2 Taux ou fréquence d'arrivée 到达速度或频率

Noté $\lambda$, il donne le nombre moyen d'instructions, requêtes ou tâches soumises par unité de temps ; ce taux d'entrée n'est pas nécessairement le débit de sortie. 记为 $\lambda$，表示单位时间内提交的平均指令、请求或任务数量（注意 $\lambda$ 是外部输入速度，若系统过载或阻塞，未必等于系统实际完成的输出吞吐量）。

Il intervient avec le mode d'utilisation dans la génération d'intervalles représentatifs. 将平均到达速度 $\lambda$ 与具体的使用模式结合，即可生成具有代表性的到达间隔序列。

##### Modes d'utilisation : 常见使用模式：

- Fixe 固定间隔模式（等间隔周期到达）
- Ordinaire 普通随机模式（泊松到达／指数分布间隔）
- En rafales 突发模式（成批簇集到达）
- Périodique ON/OFF, à queue lourde, etc. 周期性启停模式（ON/OFF）、重尾分布模式等

#### 4.2.3 Utilisation fixe 固定间隔模式

Les dates $\mathrm{date}_i$ sont séparées par un intervalle fixe $\delta t=1/\lambda$, à partir de la référence $\mathrm{date}_{\mathrm{ref}}$ ; $i$ est l'indice de l'événement. 相邻到达时刻 $\mathrm{date}_i$ 之间保持严格恒定的时间间隔 $\delta t=1/\lambda$（对应第三课 Kendall 记号中的确定性分布 `D`），其中 $\mathrm{date}_{\mathrm{ref}}$ 为参考起点，$i$ 为事件序号。

Les arrivées sont périodiques. 请求呈严格的周期性到达。

Aucune loi aléatoire n'est nécessaire : incrémenter la date de $\delta t$. 无需生成随机数，直接按固定步长 $\delta t$ 累加即可得到各事件的到达时刻：

$$
\mathrm{date} _{i} = \mathrm{date} _{\mathrm{ref}} + i \times \delta t
$$

#### 4.2.4 Utilisation ordinaire 普通随机模式（泊松过程）

Dans un processus de Poisson homogène de taux $\lambda>0$, le nombre d'arrivées sur une durée $\Delta$ suit $\operatorname{Poisson}(\lambda\Delta)$ ; les intervalles sont indépendants, de loi $\operatorname{Exp}(\lambda)$ et de moyenne $1/\lambda$. Distinguer comptage et intervalle. 在速度为 $\lambda>0$ 的齐次泊松过程中，任意长度为 $\Delta$ 的时间窗内到达的事件个数服从泊松分布 $\operatorname{Poisson}(\lambda\Delta)$；而相邻两次到达之间的时间间隔 $\delta t$ 则独立同分布，服从参数为 $\lambda$ 的指数分布 $\operatorname{Exp}(\lambda)$（均值为 $1/\lambda$，对应第三课 Kendall 记号中的 `M`）。需注意区分“离散计数（泊松）”与“连续时间间隔（指数）”。

##### Génération des dates : 到达时刻生成步骤：

1. Tirer $u$ uniformément sur $(0,1)$, sans les bornes. 生成开区间 $(0,1)$ 上的均匀分布随机数 $u\sim\mathcal{U}(0,1)$。

2. Calculer l'intervalle par : 用逆变换公式计算本次到达间隔 $\delta t$：

$$
\delta t = - \frac{1}{\lambda} \ln(u)
$$

3. Ajouter $\delta t$ à la date précédente pour obtenir la date courante : $\mathrm{date}_i = \mathrm{date}_{i-1} + \delta t$. 将 $\delta t$ 加到上一个事件的到达时刻上，即得当前事件的到达时刻 $\mathrm{date}_i = \mathrm{date}_{i-1} + \delta t$。

**Complément — dérivation par inversion de la loi exponentielle 指数间隔生成公式的逆变换推导。** La fonction de répartition de $\delta t\sim\operatorname{Exp}(\lambda)$ est $F(t)=\mathbb{P}(\delta t\le t)=1-e^{-\lambda t}$. Si $v\sim\mathcal{U}(0,1)$, poser $F(\delta t)=v$ donne $1-e^{-\lambda\delta t}=v$, soit $e^{-\lambda\delta t}=1-v$. Comme $u=1-v$ suit aussi la loi uniforme sur $(0,1)$, on obtient $e^{-\lambda\delta t}=u\implies\delta t=-\frac{1}{\lambda}\ln(u)$. 指数分布 $\operatorname{Exp}(\lambda)$ 的累积分布函数为 $F(t)=1-e^{-\lambda t}$。根据逆变换采样法，令 $F(\delta t)=v\sim\mathcal{U}(0,1)$，则 $e^{-\lambda\delta t}=1-v$。由于 $u=1-v$ 同样服从 $(0,1)$ 上的均匀分布，两边取自然对数即得 $\delta t=-\frac{1}{\lambda}\ln(u)$。

#### 4.2.5 Utilisation en rafales 突发模式

Les rafales arrivent selon un processus de Poisson de taux $\lambda_b$ ; leur taille $G(p)$ suit une loi géométrique de paramètre $p$, de moyenne $1/p$. 在突发模型中，“一簇突发（rafale / burst）”整体按速度为 $\lambda_b$ 的泊松过程到达；而每次突发内部包含的事件个数 $G(p)\in\{1,2,3,\dots\}$ 服从参数为 $p\in(0,1)$ 的几何分布，平均每次突发包含 $1/p$ 个事件（注意此处的 $p$ 是几何分布的成功概率参数，不是 §3.4 的分位比例）。

##### Deux étapes de génération : 生成突发负载分两步：

1. Générer la taille $G(p)$ de la rafale. 生成每次突发所含的事件个数 $G(p)$；

2. Générer les dates des événements du workload. 生成各个事件的到达时刻。

La taille de la rafale est son nombre d'événements : 突发大小 $G(p)$ 的生成方法：

1. Tirer $u$ uniformément dans $(0,1)$. 生成 $(0,1)$ 上的均匀分布随机数 $u\sim\mathcal{U}(0,1)$。

2. Calculer la taille par : 用下式计算突发包含的事件数（向上取整 $\lceil\cdot\rceil$）：

$$
G (p) = \left\lceil \frac{\ln(u)}{\ln(1 - p)} \right\rceil
$$

##### Dates des événements : 事件到达时刻的生成步骤：

1. Générer des intervalles exponentiels entre rafales, puis les cumuler en dates. 先按速度为 $\lambda_b$ 的指数分布生成相邻两次突发之间的时间间隔 $\delta t_b=-\frac{1}{\lambda_b}\ln(u_b)$，累加得到每次突发的到达时刻；

2. Générer la taille, puis autant d'événements à cette date. 对每次突发生成其大小 $G(p)$，并在该突发时刻一次性生成 $G(p)$ 个同时到达的事件（变体模型也可以在突发持续期内按微小间隔分散排列这 $G(p)$ 个事件）。

**Complément — dérivation de la loi géométrique et taux moyen d'événements 几何分布取整公式推导与总事件到达速度。**
1. **Pourquoi le plafond $\left\lceil\frac{\ln(u)}{\ln(1-p)}\right\rceil$ 为什么用对数向上取整：** Pour une loi géométrique sur $\{1,2,\dots\}$, $\mathbb{P}(G=k)=(1-p)^{k-1}p$ et la fonction de répartition vaut $F(k)=\mathbb{P}(G\le k)=1-(1-p)^k$. Par inversion, on choisit $G=k$ lorsque $F(k-1)<v\le F(k)$ avec $v\sim\mathcal{U}(0,1)$, soit $(1-p)^k\le 1-v<(1-p)^{k-1}$. En posant $u=1-v\sim\mathcal{U}(0,1)$ et en divisant par $\ln(1-p)<0$ (ce qui inverse les inégalités), il vient $k-1<\frac{\ln(u)}{\ln(1-p)}\le k$, c'est-à-dire exactement $k=\left\lceil\frac{\ln(u)}{\ln(1-p)}\right\rceil$ (pour $0<p<1$ ; si $p=1$, $G\equiv 1$). 取值在 $\{1,2,\dots\}$ 上的几何分布满足 $\mathbb{P}(G=k)=(1-p)^{k-1}p$，累积分布为 $F(k)=\mathbb{P}(G\le k)=1-(1-p)^k$。逆变换法在 $F(k-1)<v\le F(k)$ 时取 $G=k$，令 $u=1-v\sim\mathcal{U}(0,1)$ 即得 $(1-p)^k\le u<(1-p)^{k-1}$。两边取自然对数并除以负数 $\ln(1-p)<0$（不等号方向反转），得到 $k-1<\frac{\ln(u)}{\ln(1-p)}\le k$，这恰好就是向上取整 $k=\left\lceil\frac{\ln(u)}{\ln(1-p)}\right\rceil$（要求 $0<p<1$；若 $p=1$ 则恒取 $1$）。
2. **Taux de rafales vs taux d'événements 区分突发到达速度与总事件到达速度：** Si les rafales arrivent au taux moyen $\lambda_b$ et que chaque rafale contient en moyenne $\mathbb{E}[G(p)]=1/p$ événements (indépendamment des dates), le taux moyen total d'arrivée des événements vaut $\lambda=\frac{\lambda_b}{p}$. 若每单位时间平均到达 $\lambda_b$ 次突发，每次突发平均包含 $1/p$ 个事件，则系统收到的**单个事件的总平均到达速度为 $\lambda=\frac{\lambda_b}{p}$**。

### 4.3 Génération des adresses 生成：访问地址

Les accès mémoire ou disque peuvent être uniformes dans l'espace ou concentrés dans des zones à localité spatiale, les hot spots. 内存或磁盘的访问地址既可以均匀分布在全部地址空间中，也可以呈现出**空间局部性**——即大量访问集中在少数特定区域（称为**热点 / hot spots**）。

#### 4.3.1 Distribution uniforme 均匀地址分布

Les adresses suivent une loi uniforme sur les $M$ adresses disponibles. 所有 $M$ 个可选地址被访问的概率完全相等：

1. Tirer $u$ uniformément dans $[0,1)$. 在半开区间 $[0,1)$ 内生成均匀随机数 $u\sim\mathcal{U}[0,1)$；

2. Adapter à la taille de l'espace d'adressage par discrétisation : 按地址空间总数 $M$ 缩放并向下取整，映射到离散地址编号 $\{0,1,\dots,M-1\}$：

$$
\mathrm{adr}=\lfloor uM\rfloor\in\{0,\ldots,M-1\}
$$

#### 4.3.2 Hot spots 热点地址分布

Génération uniforme à l'intérieur des zones, avec un facteur de concentration pour les zones actives : 热点模型将地址空间划分为若干区域，对活跃区域赋予更高的集中因子 $a$，并在每个区域内部保持均匀分布：

- Diviser l'espace en sous-ensembles ; 将总地址空间划分为 $R$ 个互不重叠的子区域（设第 $j$ 个区域包含 $M_j$ 个地址，$\sum_{j=1}^R M_j = M$）；
- Identifier les plus actifs ; 确定其中的活跃热点区域；
- Associer un facteur de concentration $a$ aux zones actives ($a>1$ pour les zones actives, $a=1$ pour les autres). 为每个区域关联一个相对集中因子 $a_j$（活跃热点区域取 $a_j>1$，普通区域取 $a_j=1$）。

**Complément — comment tirer une adresse avec facteur de concentration $a$ 如何用集中因子生成热点地址。** Les facteurs $a_j$ sont des poids relatifs par adresse (ou par zone), et non directement des probabilités. Par exemple, si chaque adresse de la zone $j$ reçoit un poids relatif $a_j$, le poids total de la zone $j$ est $W_j=a_j M_j$ ; on procède alors en deux étapes : 集中因子 $a_j$ 是相对权重而非直接的概率（概率之和必须为 $1$）。若将 $a_j$ 视为区域 $j$ 内单个地址的相对访问权重，则区域 $j$ 的总权重为 $W_j=a_j M_j$，生成一次访问分两步：
1. **Choix de la zone 选择区域：** tirer la zone $j$ avec la probabilité normalisée $P_j=\frac{W_j}{\sum_{r=1}^R W_r}=\frac{a_j M_j}{\sum_{r=1}^R a_r M_r}$ ; 按归一化概率 $P_j=\frac{a_j M_j}{\sum_{r=1}^R a_r M_r}$ 随机抽中某个区域 $j$；
2. **Choix de l'adresse dans la zone 区域内均匀取址：** tirer ensuite une adresse uniformément parmi les $M_j$ adresses de la zone $j$. 再在区域 $j$ 包含的 $M_j$ 个地址中按均匀分布随机抽取一个具体地址。

### 4.4 Génération du nombre de sources 生成：负载源数量

La charge peut provenir d'un utilisateur ou d'une application, ou de plusieurs sources. 工作负载可以来自单个用户/应用（单源负载），也可以来自多个并发实体（多源负载）。

#### 4.4.1 Charge à une source 单源负载

Voir les sections précédentes. 即前文 §4.2–4.3 所述的生成方法。

#### 4.4.2 Charge à plusieurs sources (modèle d'Erlang) 多源／多阶段负载（Erlang 模型）

Bien que présentée sous l'intitulé « plusieurs sources », la formule suivante décrit la génération d'intervalles suivant une loi d'Erlang d'ordre $k$, de moyenne totale $\frac{1}{\lambda}$ (chaque étape en série ayant un taux $k\lambda$) : 虽然标题沿用“多源”，但下式实际刻画的是按 $k$ 阶 Erlang 分布（$E_k$）生成总均值为 $\frac{1}{\lambda}$ 的到达间隔的多阶段模型（将每次间隔拆为 $k$ 个速度为 $k\lambda$ 的独立指数阶段串联）：

1. Tirer indépendamment $k$ nombres $u_1,\ldots,u_k\in(0,1)$ uniformes. 独立生成 $k$ 个 $(0,1)$ 上的均匀分布随机数 $u_1,\ldots,u_k\sim\mathcal{U}(0,1)$；

2. Calculer l'intervalle d'attente avec le taux cible $\lambda$ : 用目标平均到达速度 $\lambda$ 计算总间隔时间 $t$：

$$
t = - \left(\frac{1}{\lambda k}\right) \times \ln \left(\prod_{i = 1} ^{k} u _{i}\right)
$$

**Complément — dérivation, loi des grands nombres et distinction avec la superposition de sources 公式推导、大数定律以及与“多泊松源叠加”的区别。**
1. **Dérivation et loi des grands nombres 推导与大数定律：** Chaque étape $i$ dure $t_i=-\frac{1}{k\lambda}\ln(u_i)=\frac{1}{k}X_i$, où $X_1,\dots,X_k\overset{\text{i.i.d.}}{\sim}\operatorname{Exp}(\lambda)$ ont pour moyenne $\frac{1}{\lambda}$ et pour variance $\frac{1}{\lambda^2}$. La somme $t=\sum_{i=1}^k t_i=-\frac{1}{k\lambda}\ln\left(\prod_{i=1}^k u_i\right)=\frac{1}{k}\sum_{i=1}^k X_i$ est donc la **moyenne arithmétique de $k$ variables exponentielles indépendantes**, de moyenne $\mathbb{E}[t]=\frac{1}{\lambda}$ et de variance $\operatorname{Var}(t)=\frac{1}{k\lambda^2}$ ($CV=\frac{1}{\sqrt{k}}$). Par la **loi des grands nombres**, $k=1$ donne la loi exponentielle $\operatorname{Exp}(\lambda)$, et lorsque $k\to\infty$, la variance tend vers $0$ et $t$ converge vers l'intervalle constant $\frac{1}{\lambda}$ (voir [CM3 §6.4](3_edp_zh.md)). 每个子阶段耗时 $t_i=-\frac{1}{k\lambda}\ln(u_i)=\frac{1}{k}X_i$，其中 $X_i\overset{\text{i.i.d.}}{\sim}\operatorname{Exp}(\lambda)$。将 $k$ 个阶段相加（利用 $\sum\ln u_i=\ln\prod u_i$）即得上式。由于 $t=\frac{1}{k}\sum_{i=1}^k X_i$ 恰好是 $k$ 个独立同分布指数随机变量的算术平均值，其总均值为 $\frac{1}{\lambda}$、总方差为 $\frac{1}{k\lambda^2}$。当 $k=1$ 时就是指数分布；随 $k$ 增大，由**大数定律**，快慢波动相互抵消，当 $k\to\infty$ 时退化为固定常数间隔 $\frac{1}{\lambda}$（详见 [第三课 §6.4](3_edp_zh.md)）。
2. **Ne pas confondre étapes en série et sources indépendantes en parallèle 区分“串联 $k$ 阶段”与“并联多源叠加”：** En théorie des probabilités, la superposition directe de $N_{\mathrm{src}}$ processus de Poisson indépendants de taux $\lambda_1,\dots,\lambda_{N_{\mathrm{src}}}$ forme encore un processus de Poisson (de taux total $\sum\lambda_i$, donc à intervalles exponentiels), et non une loi d'Erlang. La loi $\operatorname{Erlang}(k)$ apparaît lorsque chaque arrivée observée résulte de **$k$ sous-étapes exponentielles en série** (ou lorsqu'un filtre ne déclenche une requête qu'une fois toutes les $k$ arrivées poissonniennes). 需要注意物理含义：若将多个独立的泊松负载源直接并联叠加，合流后仍然是泊松过程（间隔仍服从指数分布，只是总到达速度变为各源之和）；而此处的 $k$ 阶 Erlang 分布对应的是**串联经过 $k$ 个独立指数阶段**（或每收到 $k$ 个泊松子事件才打包触发一次请求）。

## 5 Workloads réels 真实工作负载

Deux sources de charges réelles : 真实负载主要通过以下两种途径获取：

1. Collecte pendant l'exécution d'applications utilisateurs. 在被测系统上运行真实用户应用期间直接采集；

2. Collecte pendant l'exécution de benchmarks. 在被测系统上运行标准基准测试程序期间采集。

### 5.1 Benchmarks 基准测试

#### 5.1.1 Définition 定义

Partie du code utilisateur représentative du comportement de l'application. 从真实用户应用中提炼出的、最能代表该类应用核心计算或访存行为的标准测试程序（或核心代码片段 kernel）。

#### 5.1.2 Exemples 示例

- Calcul : SPEC, Linpack, Livermore, NAS. 计算类基准（测试处理器、内存层次及编译器综合性能）：SPEC、Linpack（稠密线性代数，用于 TOP500）、Livermore Loops、NAS Parallel Benchmarks（NPB）。
- Entrées-sorties : Bonnie et IOzone. I/O 存储基准：Bonnie、IOzone。

### 5.2 Applications utilisateurs 用户应用

- Exécuter l'application étudiée ou une application représentative de sa classe. 直接运行待分析的目标用户应用（或该应用类别的代表性程序）；
- Collecter la charge produite pendant cette exécution. 采集运行期间产生的实际负载轨迹；
- La réutiliser dans d'autres contextes d'exécution, ou 将采集到的轨迹重用于其他系统配置或仿真环境中，或者
- Extraire ses caractéristiques et les modéliser par des distributions pour élargir les cas analysables. 提取其统计特征并拟合为概率分布模型（转化为 §4 的合成负载或第三课的解析模型），以扩展可分析的场景范围。

#### 5.2.1 Précautions 注意事项

Avant l'exécution, définir les mesures souhaitées et préparer les outils d'extraction de la charge. 在运行应用进行采集前，必须预先明确要测量的指标边界，并配置好性能计数器或轨迹采集工具（以控制探针开销与数据量）。

Pour approfondir, voir le cours ultérieur sur la mesure. 关于测量工具、开销控制与实验设计的具体方法，详见后续测量章节（[CM4–5](45_edp_zh.md)）。

### 5.3 Paramètres des workloads réels 真实工作负载的采集参数

Qu'il s'agisse de benchmarks ou d'applications : 无论是运行基准测试还是真实用户应用：

La collecte porte sur les événements qui modifient l'état du système : 数据采集都聚焦于会改变系统状态的底层或系统级事件，例如：

- Changements de contexte 进程／线程上下文切换
- Déplacements de la tête de disque 磁盘磁头寻道与读写请求
- Réception ou envoi de messages, etc. 网络或进程间消息的发送与接收等

Enregistrer dates, nombres par unité de temps, tailles, etc. 采集时通常记录这些事件的发生时间戳、单位时间内的发生次数、数据块或消息大小等属性。
