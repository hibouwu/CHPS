# Travail de projet ce mois

## 1 Parallélisme de données synchrone par mini-batch avec `MPI_Allreduce`

口语化解释：这一大节主要是在讲，分布式训练最基本的同步数据并行是怎么做的，以及后来又是怎么一步步把通信做得更高效的。

### 1.1 Baseline `non-overlap, non-bucketed`

口语化解释：这一小节可以理解成“最原始、最朴素的版本”。每个进程各算各的梯度，算完之后大家一起做一次同步，再用同样的结果更新模型。

L'entraînement distribué repose sur une stratégie classique de parallélisme de données synchrone fondée sur MPI.
中文解释：分布式训练采用的是一种基于 MPI 的经典同步数据并行策略。
Chaque processus MPI, c'est-à-dire chaque `rang`, maintient une réplique complète du modèle.
中文解释：每个 MPI 进程，也就是每个 `rank`，都会保存一份完整的模型副本。
Concernant les données, chaque rang appelle `dataset->load()` et charge localement le jeu de données, puis construit à partir de son propre `rang` et de `world_size` une partition logique via `makeShard(...)`.
中文解释：在数据方面，每个 rank 都会调用 `dataset->load()` 在本地加载数据集，然后根据自己的 `rank` 和 `world_size` 通过 `makeShard(...)` 构造一个逻辑上的数据分片。
Chaque rang n'entraîne donc le modèle que sur son shard local, mais conserve une copie complète des paramètres.
中文解释：因此，每个 rank 只在自己的本地分片上训练，但依然保留全部参数的一份完整拷贝。

Soit $B_r$ la taille du mini-batch local traité par le rang $r$ à une étape donnée, et $g_r$ la somme locale des gradients calculés à partir de ce mini-batch.
中文解释：设 $B_r$ 是第 $r$ 个 rank 在某一步中处理的本地 mini-batch 大小，$g_r$ 是基于这个 mini-batch 计算得到的本地梯度和。
Une fois la rétropropagation locale terminée sur chaque rang, une opération `Allreduce` est utilisée pour effectuer la somme globale des gradients locaux sur l'ensemble des processus, ce qui donne :
中文解释：当每个 rank 的本地反向传播完成后，会通过一次 `Allreduce` 操作对所有进程上的本地梯度求全局和，得到：
$$
g_{\mathrm{sum}}=\sum_{r=0}^{\mathrm{world\_size}-1} g_r
$$
De même, les tailles de mini-batch locales sont additionnées afin d'obtenir la taille globale du batch :
中文解释：同样地，各个本地 mini-batch 的大小也会被累加，从而得到全局 batch 的大小：
$$
B_{\mathrm{global}}=\sum_{r=0}^{\mathrm{world\_size}-1} B_r
$$
Le gradient moyen global effectivement utilisé pour la mise à jour des paramètres est alors :
中文解释：随后，真正用于参数更新的就是这个全局平均梯度：
$$
g_{\mathrm{global}}=\frac{1}{B_{\mathrm{global}}}g_{\mathrm{sum}}
=\frac{1}{B_{\mathrm{global}}}\sum_{r=0}^{\mathrm{world\_size}-1} g_r
$$

Une fois ce gradient moyen global obtenu, chaque rang applique exactement la même mise à jour sur sa propre réplique complète du modèle :
中文解释：在得到这个全局平均梯度后，每个 rank 都会对自己的完整模型副本执行完全相同的更新：
$$
\theta \leftarrow \theta-\eta\, g_{\mathrm{global}}
$$
où $\theta$ désigne les paramètres du modèle et $\eta$ le taux d'apprentissage.
中文解释：其中 $\theta$ 表示模型参数，$\eta$ 表示学习率。
Comme tous les rangs utilisent à chaque itération le même gradient agrégé, les paramètres mis à jour restent identiques sur l'ensemble des processus.
中文解释：由于所有 rank 在每次迭代中使用的都是同一个聚合梯度，所以更新后的参数在所有进程之间始终保持一致。
Autrement dit, cette implémentation correspond à un schéma classique de parallélisme de données synchrone : chaque processus maintient une réplique complète du modèle, calcule localement ses gradients sur un mini-batch distinct, puis une opération `Allreduce` assure la synchronisation globale des gradients avant une mise à jour synchronisée des paramètres.
中文解释：换句话说，这个实现就是一种标准的同步数据并行方案：每个进程维护完整模型副本，在不同的 mini-batch 上本地计算梯度，然后通过 `Allreduce` 完成全局梯度同步，最后同步更新参数。
Dans la baseline actuelle, la synchronisation est réalisée de manière bloquante, paramètre par paramètre, via `MPI_Allreduce`.
中文解释：在当前的 baseline 中，这种同步是通过阻塞式、逐参数调用 `MPI_Allreduce` 来完成的。
Dans le code, ce mode correspond aujourd'hui à `Grad Sync Mode = per_param`.
中文解释：在代码里，这个模式目前对应 `Grad Sync Mode = per_param`。

### 1.2 Optimisation 1 — Gradient bucketing

口语化解释：这一小节讲的是第一层优化思路。核心不是改训练规则，而是把很多零碎的小通信打包成几次大的通信，减少来回折腾的成本。

La première optimisation introduite au-dessus de la baseline consiste à remplacer la synchronisation paramètre par paramètre par une synchronisation par `bucket`.
中文解释：在 baseline 之上引入的第一项优化，是把逐参数同步改成按 `bucket` 同步。
L'idée est de regrouper plusieurs gradients de paramètres dans un buffer contigu avant de lancer la collective MPI.
中文解释：核心思想是在发起 MPI 集体通信之前，先把多个参数梯度打包到一个连续缓冲区中。
Par rapport à l'approche initiale, cela réduit le nombre d'appels à `MPI_Allreduce`, amortit le coût des petites réductions et fournit une granularité de communication plus réaliste pour les étapes suivantes.
中文解释：与最初的方法相比，这样可以减少 `MPI_Allreduce` 的调用次数，摊薄小规模归约的开销，并为后续优化提供更合理的通信粒度。

Concrètement, un `BucketManager` construit une partition statique des paramètres entraînables selon leur ordre dans `trainable_params_`, puis associe à chaque paramètre un `bucket`, un offset et une longueur dans un buffer contigu.
中文解释：具体来说，`BucketManager` 会按照参数在 `trainable_params_` 中的顺序，对可训练参数做一个静态划分，并为每个参数分配所属的 `bucket`、在连续缓冲区中的偏移量以及长度。
La règle retenue est simple : un paramètre ne peut pas être coupé sur plusieurs `bucket`, et un très gros paramètre occupe à lui seul un `bucket`.
中文解释：采用的规则很简单：一个参数不能被切分到多个 `bucket` 中，而特别大的参数会单独占用一个 `bucket`。
Le `BucketManager` est partagé par les deux modes `bucketed` et `overlap_bucketed`, ce qui garantit que la représentation des buckets, l'ordre des paramètres et la logique `pack/unpack` restent identiques dans les deux cas.
中文解释：`BucketManager` 由 `bucketed` 和 `overlap_bucketed` 两种模式共用，从而保证两种情况下的 bucket 表示、参数顺序以及 `pack/unpack` 逻辑完全一致。

Dans le mode `non-overlap, bucketed`, la communication est toujours déclenchée à la fin du backward, mais elle s'effectue bucket par bucket : les gradients sont copiés dans les buffers de `bucket`, chaque `bucket` est réduit via `MPI_Allreduce`, puis les résultats sont recopiés dans les gradients des paramètres.
中文解释：在 `non-overlap, bucketed` 模式下，通信仍然是在整个 backward 结束后才触发，但执行方式变成逐 bucket 进行：先把梯度复制进 bucket 缓冲区，再对每个 bucket 调用 `MPI_Allreduce`，最后把结果拷回各参数梯度中。
Cette optimisation conserve exactement la même sémantique mathématique que la baseline : seul le regroupement des gradients avant communication change.
中文解释：这项优化在数学语义上与 baseline 完全一致，变化的只有通信前梯度的组织方式。
Elle permet donc d'évaluer isolément l'effet du `bucketing`, sans encore introduire de recouvrement entre calcul et communication.
中文解释：因此，它可以单独评估 `bucketing` 本身的效果，而不引入计算与通信重叠的因素。

### 1.3 Optimisation 2 — Recouvrement communication-calcul avec `MPI_Iallreduce`

口语化解释：这一小节是在前面 bucket 的基础上再往前走一步，不等整个 backward 全做完才通信，而是边算边发，尽量把通信时间藏到计算时间里面。

Une fois le `bucketing` stabilisé, une seconde optimisation consiste à lancer certaines communications avant la fin complète du backward afin de rechercher un recouvrement partiel entre communication et calcul.
中文解释：在 `bucketing` 稳定之后，第二项优化是尝试在 backward 尚未完全结束前就启动部分通信，以实现通信和计算的部分重叠。
Cette version repose sur le même `BucketManager`, mais remplace le lancement en fin de backward par un déclenchement événementiel.
中文解释：这个版本仍然依赖同一个 `BucketManager`，但把原来在 backward 末尾统一启动通信的方式改成了事件驱动式触发。
Lorsqu'un gradient de paramètre devient `final-ready`, le runtime distribué est notifié.
中文解释：当某个参数梯度进入 `final-ready` 状态时，分布式运行时就会收到通知。
Dès que tous les paramètres actifs d'un `bucket` sont prêts, ce `bucket` est empaqueté et sa communication est lancée de manière asynchrone via `MPI_Iallreduce`.
中文解释：一旦某个 `bucket` 中所有活跃参数都准备好了，这个 `bucket` 就会被打包，并通过 `MPI_Iallreduce` 异步发起通信。
Le backward peut alors continuer pendant que certaines communications sont déjà en vol.
中文解释：这样一来，backward 计算可以继续执行，而部分通信已经在后台进行了。

Pour supporter ce mode `overlap, bucketed`, `DistributedContext` n'expose plus uniquement des collectives bloquantes, mais aussi un petit wrapper de requêtes asynchrones fondé sur `MPI_Iallreduce`, ainsi que des primitives `wait` et `waitAll`.
中文解释：为了支持这种 `overlap, bucketed` 模式，`DistributedContext` 不再只提供阻塞式集体通信，还提供了一个基于 `MPI_Iallreduce` 的异步请求封装，以及 `wait` 和 `waitAll` 这样的等待原语。
Au-dessus, un runtime explicite `BucketedOverlapRuntime` gère le cycle de vie de chaque étape : `beginStep(...)`, réception des événements `onParameterGradReady(...)`, notification `onBackwardComplete()`, puis `finalizeAndGetGlobalBatch()`.
中文解释：在更上层，一个显式的运行时 `BucketedOverlapRuntime` 负责管理每个训练步骤的生命周期，包括 `beginStep(...)`、接收 `onParameterGradReady(...)` 事件、处理 `onBackwardComplete()` 通知，以及最后的 `finalizeAndGetGlobalBatch()`。
Le mode `non-overlap, bucketed` est, lui aussi, encapsulé dans un objet dédié `StepBoundaryBucketedSync`, mais reste piloté à la frontière de l'étape.
中文解释：`non-overlap, bucketed` 模式也被封装进了专门的对象 `StepBoundaryBucketedSync`，不过它仍然是在步骤边界处统一驱动的。
Avant `optimizer_.step()`, le runtime attend la fin de toutes les requêtes, dépile les `bucket` et garantit que tous les gradients sont cohérents.
中文解释：在执行 `optimizer_.step()` 之前，运行时会等待所有请求完成，解包各个 `bucket`，并确保所有梯度都处于一致状态。

Ces trois modes, `non-overlap, non-bucketed`, `non-overlap, bucketed` et `overlap, bucketed`, partagent volontairement la même sémantique mathématique : dans tous les cas, chaque rang applique une mise à jour synchrone fondée sur le gradient global moyen.
中文解释：这三种模式，即 `non-overlap, non-bucketed`、`non-overlap, bucketed` 和 `overlap, bucketed`，是有意保持相同数学语义的：无论哪种情况，每个 rank 都基于全局平均梯度执行同步更新。
La différence ne porte donc pas sur la règle d'optimisation elle-même, mais sur la manière d'organiser la synchronisation et sur la capacité du système à réduire les surcoûts de communication.
中文解释：因此，它们之间的差异不在于优化规则本身，而在于如何组织同步流程，以及系统降低通信额外开销的能力。

### 1.4 Résultat pratique et déplacement du goulot d'étranglement

口语化解释：这一小节是在说，前面的优化不是没效果，而是效果出来以后，主要瓶颈已经不再是通信，而是卷积计算本身了。

Les mesures historiques les plus récentes sur `Tiny-ImageNet`, avec un CNN à trois étages convolutifs, `world_size = 16`, `batch_size = 64`, `Grad Sync Mode = overlap_bucketed` et `bucket_size_bytes = 4 MiB`, montrent une époque d'environ `630 s`, dont `543 s` pour `fwd_bwd` et `59 s` pour `sync_total`.
中文解释：在 `Tiny-ImageNet` 上最近的历史测量结果显示，使用三层卷积 CNN、`world_size = 16`、`batch_size = 64`、`Grad Sync Mode = overlap_bucketed` 和 `bucket_size_bytes = 4 MiB` 时，一个 epoch 大约需要 `630 s`，其中 `543 s` 用于 `fwd_bwd`，`59 s` 用于 `sync_total`。
Ces chiffres doivent cependant être lus comme des enregistrements de profiling non requalifiés : tant que `overlap_bucketed` n'a pas repassé une qualification multi-rang complète, ils ne doivent pas être interprétés comme une preuve actuelle de gain overlap benchmark.
中文解释：不过，这些数字目前只能看作尚未重新验证的 profiling 记录；只要 `overlap_bucketed` 还没有重新通过完整的多 rank 资格验证，就不能把它们当作当前 overlap 性能提升的基准证据。

Autrement dit, les optimisations distribuées mises en place ont bien réduit la part relative de la communication, mais elles n'ont pas changé la nature du goulot d'étranglement principal.
中文解释：换句话说，已经实现的分布式优化确实降低了通信在总时间中的相对占比，但并没有改变主要瓶颈的本质。
Celui-ci s'est déplacé vers le calcul CNN lui-même, en particulier les opérations liées aux convolutions et aux réarrangements mémoire associés.
中文解释：这个瓶颈已经转移到了 CNN 本身的计算上，尤其是卷积相关操作以及伴随的内存重排。
La suite du travail ne doit donc pas se concentrer uniquement sur le `bucketed overlap`, mais aussi sur les noyaux CPU des couches convolutionnelles.
中文解释：因此，后续工作不能只盯着 `bucketed overlap`，还必须关注卷积层的 CPU 计算内核。

## 2 Refonte du backward et optimisation du hot path autograd

口语化解释：这一大节主要讲自动求导系统的内部重构。重点不是“数学上算得不对”，而是“工程上太重、太难调度”，所以要把 backward 变成更明确、更可控的执行过程。

### 2.1 modèle initial

口语化解释：这一小节是在回顾旧版本怎么工作的。它能用，也能算对，但更像一个先跑起来的原型，而不是适合继续扩展的正式架构。

L'implémentation initiale de l'autodiff reposait sur un schéma très direct : pendant la phase forward, chaque opérateur construisait son `Node` de sortie puis lui associait une lambda `backwardFn` via `setBackwardFn(...)`.
中文解释：最初的自动求导实现采用的是一种非常直接的方案：在 forward 阶段，每个算子都会构造自己的输出 `Node`，然后通过 `setBackwardFn(...)` 给它绑定一个 `backwardFn` lambda。
Cette lambda capturait à la fois l'état du forward nécessaire au backward, par exemple les matrices d'entrée, les informations de broadcast, le cache `im2col` ou les indices du pooling, et la règle locale de dérivation.
中文解释：这个 lambda 会同时捕获 backward 所需的 forward 状态，比如输入矩阵、broadcast 信息、`im2col` 缓存或者 pooling 索引，以及对应的局部求导规则。
Au moment de l'entraînement, l'appel à `loss_node->backward()` collectait les nœuds atteignables en sens inverse afin de former une séquence d'exécution backward, puis exécutait chaque `backwardFn` selon l'ordre inverse des dépendances topologiques.
中文解释：训练时，调用 `loss_node->backward()` 会收集所有在反向方向上可达的节点，形成一个 backward 执行序列，然后按照拓扑依赖的逆序执行每个 `backwardFn`。
Cette approche est simple et suffisante pour la première phase du projet, car elle permet de faire fonctionner correctement le MLP, les fonctions d'activation, les fonctions de perte, puis les couches CNN ajoutées par la suite.
中文解释：这种方法简单直接，也足以支撑项目第一阶段，因为它可以正确驱动 MLP、激活函数、损失函数，以及之后加入的 CNN 层。

### 2.2 limites du modèle initial

口语化解释：这一小节是在指出旧设计真正的问题。不是梯度错了，而是系统根本不知道“哪个梯度现在算完了、能不能立刻拿去做别的事”。

Cependant, ce modèle où chaque nœud porte sa propre fermeture anonyme n'est réellement adapté qu'à un prototype.
中文解释：但是，这种每个节点都自带匿名闭包的模型，本质上只适合原型阶段。
Le problème n'est pas qu'il calcule mal les gradients, mais qu'il n'exprime pas explicitement l'état d'exécution du backward.
中文解释：问题不在于它梯度算错了，而在于它没有显式表达 backward 执行过程中的状态。
Dans l'ancien système, chaque backward local calculait sa dérivée puis écrivait immédiatement dans le gradient du parent via `addGrad(...)`.
中文解释：在旧系统里，每个局部 backward 算完自己的导数后，就立刻通过 `addGrad(...)` 写入父节点的梯度。
Mathématiquement, cela est correct ; en revanche, du point de vue du runtime, le système ne voit qu'un fait très grossier : « un nœud vient de modifier le buffer de gradient de son parent ».
中文解释：从数学上说这当然没问题；但从运行时角度看，系统只能看到一个非常粗糙的事实：“某个节点刚刚修改了其父节点的梯度缓冲区”。
Il n'a aucun moyen de savoir si cette écriture correspond à une contribution partielle ou à la dernière contribution attendue.
中文解释：它无法知道这次写入到底只是部分贡献，还是最后一次所需贡献。
En conséquence, le processus de fusion des contributions, le moment où le gradient de sortie d'un nœud devient `final-ready`, et le moment où un gradient de paramètre peut déclencher un événement de communication ou de profilage ne sont jamais représentés explicitement.
中文解释：因此，贡献合并的过程、某个节点输出梯度何时变成 `final-ready`，以及参数梯度何时可以触发通信或 profiling 事件，这些关键时刻都没有被显式表示出来。
Pour un entraînement synchrone classique, où toute la synchronisation est faite après la fin complète du backward, cette limite reste supportable ; mais pour du recouvrement communication-calcul, des hooks de paramètres `final-ready`, du bucketing, une planification CUDA par stream, ou des graphes plus complexes de type Transformer, cela devient directement une limite structurelle.
中文解释：对于传统的同步训练，因为所有同步都发生在 backward 全部结束之后，所以这个缺陷还可以忍受；但对于通信计算重叠、`final-ready` 参数钩子、bucketing、基于 stream 的 CUDA 调度，或者 Transformer 这类更复杂的图结构，这就会直接变成结构性限制。

Autrement dit, l'ancien système sait produire des gradients corrects, mais il ne sait pas décrire précisément où en est l'exécution du backward à un instant donné.
中文解释：换句话说，旧系统能算出正确梯度，但它无法精确描述 backward 在某个时刻执行到了什么阶段。
Cette absence de sémantique runtime explicite devient problématique dès que l'on cherche à déclencher des événements intermédiaires, par exemple une communication distribuée ou un mécanisme de profilage au moment exact où un gradient devient exploitable.
中文解释：一旦我们希望在梯度刚刚可用的精确时刻触发中间事件，比如分布式通信或 profiling 机制，缺少这种显式 runtime 语义就会变成明显问题。

### 2.3 refonte vers un moteur d'exécution explicite

口语化解释：这一小节讲的是重构后的核心变化。简单说，就是把原来分散在各个节点里的 backward 逻辑，统一交给一个中央 engine 来调度，这样系统才真正知道执行进度。

La refonte réalisée ici ne vise donc pas à changer les formules de gradient, mais à transformer le backward en un processus explicite piloté par un moteur d'exécution central.
中文解释：因此，这次重构的目标不是改变梯度公式，而是把 backward 改造成一个由中央执行引擎显式驱动的过程。
Dans la nouvelle version, `Node` conserve son interface externe, mais porte désormais des métadonnées autograd plus explicites : `requires_grad`, `is_leaf`, `is_parameter`, un `grad` alloué paresseusement, la liste explicite des dépendances d'entrée `inputs`, un `GradFn` optionnel, ainsi qu'un `BackwardContext` stocké par valeur.
中文解释：在新版本中，`Node` 保留了原有外部接口，但现在带有更明确的 autograd 元数据，包括 `requires_grad`、`is_leaf`、`is_parameter`、按需延迟分配的 `grad`、显式输入依赖列表 `inputs`、可选的 `GradFn`，以及按值存储的 `BackwardContext`。
De plus, seuls les nœuds de sortie pour lesquels `requires_grad=true` reçoivent effectivement un `grad_fn`, un `context` et des `inputs` ; les chemins constants ne construisent donc plus d'état backward inutile.
中文解释：此外，只有那些 `requires_grad=true` 的输出节点才真正拥有 `grad_fn`、`context` 和 `inputs`，因此常量路径不会再额外构建无用的 backward 状态。
Enfin, `Node::backward()` n'exécute plus directement l'ancien enchaînement reverse-topo basé sur les lambdas, mais délègue désormais cette responsabilité à un `AutogradEngine`.
中文解释：最后，`Node::backward()` 不再直接执行旧式基于 lambda 的 reverse-topo 流程，而是把这项责任交给了 `AutogradEngine`。

`AutogradEngine` constitue le changement structurel principal de cette étape.
中文解释：`AutogradEngine` 是这一阶段最核心的结构性变化。
À partir du nœud de loss, il reconstruit le sous-graphe atteignable en backward et maintient, pour chaque nœud, le nombre de contributions de gradient provenant de l'aval qui n'ont pas encore été reçues.
中文解释：它从 loss 节点出发，重建 backward 方向上可达的子图，并为每个节点维护一个“尚未收到的下游梯度贡献数”。
Un nœud n'entre dans la `ready queue` que lorsque son gradient de sortie a reçu toutes ses contributions.
中文解释：只有当某个节点的输出梯度收齐了所有贡献之后，它才会进入 `ready queue`。
Le système exprime ainsi pour la première fois une sémantique explicite essentielle pour l'entraînement distribué : le moment où le gradient de sortie d'un nœud devient `final-ready`.
中文解释：这样，系统第一次显式表达了分布式训练非常关键的一层语义，也就是某个节点的输出梯度何时变成 `final-ready`。

En parallèle, la logique backward des opérateurs de base et des fonctions de perte a été déplacée vers des objets explicites `GradFn` et `BackwardContext` : `BackwardContext` conserve par valeur les caches nécessaires au backward, tandis que `GradFn` calcule uniquement les contributions de gradient à propager aux entrées, sans modifier directement `grad` des parents.
中文解释：与此同时，基础算子和损失函数的 backward 逻辑被迁移到了显式的 `GradFn` 和 `BackwardContext` 对象中：`BackwardContext` 按值保存 backward 所需缓存，而 `GradFn` 只负责计算应传播到输入端的梯度贡献，不再直接修改父节点的 `grad`。
Toute l'accumulation de gradients et toute la décision de passage à l'état ready sont désormais centralisées dans l'engine.
中文解释：所有梯度累加以及何时进入 ready 状态的判断，现在都统一集中在 engine 中完成。

Cette migration est maintenant complète sur le chemin de production.
中文解释：这项迁移现在已经在生产路径上完成。
Les opérateurs élémentaires (`add`, `mul`, `matmul`, `sum`, `mean`), les activations, les fonctions de perte, les couches linéaires, `MaxPool2D` et `Conv2D` ont tous été portés vers `GradFn + BackwardContext + AutogradEngine`.
中文解释：基础算子（`add`、`mul`、`matmul`、`sum`、`mean`）、激活函数、损失函数、线性层、`MaxPool2D` 和 `Conv2D` 都已经迁移到了 `GradFn + BackwardContext + AutogradEngine` 体系下。
La couche de compatibilité historique basée sur `setBackwardFn(...)`, les anciennes arêtes `parents_` et la logique `reverse-topo` legacy ont été supprimées.
中文解释：基于 `setBackwardFn(...)` 的旧兼容层、老的 `parents_` 边以及 legacy 的 `reverse-topo` 逻辑都已经被删除。
Autrement dit, le backward n'utilise plus qu'une seule sémantique : `Node.inputs + GradFn + BackwardContext + AutogradEngine`.
中文解释：也就是说，当前的 backward 已经只剩下一套统一语义：`Node.inputs + GradFn + BackwardContext + AutogradEngine`。

Cette étape était particulièrement importante pour la suite distribuée.
中文解释：这一步对后续的分布式工作尤其关键。
Le fait de disposer d'un événement `parameter-ready` explicite permet désormais au runtime de synchronisation d'être branché directement sur le moment où un gradient de paramètre devient exploitable.
中文解释：因为现在有了显式的 `parameter-ready` 事件，同步运行时就可以直接挂接在参数梯度变得可用的那个时刻。
C'est précisément ce point d'appui qui rend possible le mode `bucketed + overlap` décrit dans la section précédente, sans réintroduire de logique de communication ad hoc dans les couches ou dans le `Trainer`.
中文解释：正是这个支点，使前一节描述的 `bucketed + overlap` 模式成为可能，同时又不需要把临时性的通信逻辑重新塞回各层或 `Trainer` 中。

### 2.4 optimisation du hot path de l'engine

口语化解释：这一小节是在说，结构重构完成后，还得继续抠性能细节，把 engine 自己带来的额外开销再往下压，不然框架本身会抢走太多时间。

Une fois la refonte structurelle terminée, un second travail a consisté à réduire le coût propre du runtime autograd.
中文解释：在结构性重构完成之后，第二项工作就是降低 autograd runtime 自身的开销。
Le problème était cette fois différent : les gradients étaient corrects, mais le moteur d'exécution restait encore coûteux sur des graphes CNN de taille réelle.
中文解释：这一次的问题不一样：梯度本身已经正确，但执行引擎在真实规模的 CNN 图上仍然代价偏高。
L'optimisation réalisée ne modifie toujours pas les formules de gradient ; elle vise seulement à retirer du chemin critique plusieurs surcoûts de framework.
中文解释：这里做的优化依然没有修改梯度公式，它的目标只是把若干框架层面的额外成本从关键路径中移除。

Premièrement, l'état d'exécution du backward est maintenant indexé localement pour chaque appel à `backward()`.
中文解释：首先，backward 的执行状态现在会针对每次 `backward()` 调用建立本地索引。
Au lieu de manipuler l'état des nœuds via des structures de recherche centrées sur des pointeurs et des objets `shared_ptr`, l'engine collecte le sous-graphe atteignable de cette exécution, lui assigne des indices denses locaux et accède ensuite à `states[index]`.
中文解释：engine 不再通过依赖指针和 `shared_ptr` 的查找结构来管理节点状态，而是收集本次执行可达的子图，为其分配稠密的本地索引，然后直接访问 `states[index]`。
Deuxièmement, les `GradientContribution` n'embarquent plus de `shared_ptr<Node>` comme cible ; ils transportent directement un `target_index` dense.
中文解释：其次，`GradientContribution` 不再携带 `shared_ptr<Node>` 作为目标，而是直接传递一个稠密的 `target_index`。
Enfin, les petites listes de contributions sont stockées dans un conteneur inline de capacité fixe (`InlineContributionList<4>`), ce qui évite les petites allocations dynamiques dans la grande majorité des opérateurs de production.
中文解释：最后，较小的贡献列表会存放在一个固定容量的 inline 容器中（`InlineContributionList<4>`），从而在绝大多数生产算子中避免小块动态分配。

Troisièmement, le chemin de fusion des gradients a été resserré.
中文解释：第三，梯度合并路径也被进一步收紧了。
`Matrix` expose désormais une primitive `addInPlace(...)`, et `Node::addGrad(...)` n'effectue plus qu'une matérialisation initiale du buffer de gradient suivie d'une accumulation inplace sur buffer contigu.
中文解释：`Matrix` 现在提供了 `addInPlace(...)` 原语，而 `Node::addGrad(...)` 只负责首次物化梯度缓冲区，然后在连续缓冲区上进行原地累加。
Le runtime distingue en outre explicitement le coût du `first-write` (`engine_grad_merge_first_write`) et celui des accumulations ultérieures (`engine_grad_merge_accumulate`), ce qui permet de savoir si le coût résiduel provient encore du framework ou simplement du trafic mémoire inhérent aux gros tenseurs.
中文解释：此外，runtime 还显式区分了首次写入 `first-write`（`engine_grad_merge_first_write`）和后续累加（`engine_grad_merge_accumulate`）的成本，这样就能判断残余开销究竟仍来自框架本身，还是只是大张量不可避免的内存流量。

Les mesures historiques obtenues sur `Tiny-ImageNet` suggèrent que cette première phase d'optimisation du hot path a réduit le coût du backward.
中文解释：在 `Tiny-ImageNet` 上得到的历史测量结果表明，这一阶段对 hot path 的优化确实降低了 backward 的成本。
Dans une configuration `CNN + Tiny-ImageNet + 16 rangs MPI + overlap_bucketed`, le temps `fwd_bwd` est passé d'environ `753 s` à `543 s` sur une époque de référence, ce qui indique que le runtime autograd était probablement un goulot d'étranglement réel.
中文解释：在 `CNN + Tiny-ImageNet + 16 个 MPI rank + overlap_bucketed` 的配置下，参考 epoch 的 `fwd_bwd` 时间从大约 `753 s` 降到了 `543 s`，这说明 autograd runtime 很可能确实曾是一个真实瓶颈。
Après optimisation, `engine_grad_merge_accumulate` ne représente plus qu'environ `2.5 s`, alors que `engine_grad_merge_first_write` reste autour de `45 s`.
中文解释：优化之后，`engine_grad_merge_accumulate` 只剩下大约 `2.5 s`，而 `engine_grad_merge_first_write` 仍然在 `45 s` 左右。
Ici encore, ces valeurs restent des mesures historiques de profiling : elles appuient une lecture d'ingénierie du hot path, mais ne suffisent pas à elles seules à requalifier `overlap_bucketed` comme résultat benchmark validé.
中文解释：同样地，这些数值依旧只是历史 profiling 数据：它们支持我们对 hot path 的工程分析，但单靠这些数据还不足以把 `overlap_bucketed` 重新认定为已经验证通过的 benchmark 结果。

En revanche, le profilage montre aussi que le moteur autograd n'est plus le seul responsable dominant.
中文解释：另一方面，profiling 也显示 autograd 引擎已经不再是唯一的主要耗时来源。
Une fois ces surcoûts réduits, les hotspots principaux redeviennent des opérations directement liées aux convolutions : `conv2d_forward_im2col`, `conv2d_forward_gemm`, `conv2d_backward_dX_gemm`, `conv2d_backward_dW_gemm` et `conv2d_backward_col2im`.
中文解释：在这些额外开销下降之后，主要热点重新变成了直接和卷积相关的操作：`conv2d_forward_im2col`、`conv2d_forward_gemm`、`conv2d_backward_dX_gemm`、`conv2d_backward_dW_gemm` 以及 `conv2d_backward_col2im`。
Autrement dit, le travail sur l'engine a déplacé le goulot d'étranglement vers les kernels convolutionnels eux-mêmes, ce qui est précisément l'effet recherché : après avoir retiré une part significative du coût de framework, le profil reflète désormais plus fidèlement les limites réelles du backend CPU.
中文解释：换句话说，对 engine 的优化已经把瓶颈转移到了卷积内核本身，这正是想要达到的效果：在去掉相当一部分框架成本之后，当前的 profiling 更真实地反映了 CPU backend 的实际极限。

## 3 Mise à jour du jeu de données Tiny-ImageNet

口语化解释：这一节讲的是实验对象为什么从 MNIST 换到 Tiny-ImageNet。原因很直接，MNIST 太简单了，已经不太能体现真实分布式训练里会遇到的性能和收敛问题。

Le jeu de données MNIST étant trop simple pour mettre réellement en évidence les avantages et les difficultés de l'entraînement distribué, nous avons fait évoluer l'expérimentation vers Tiny-ImageNet.
中文解释：由于 MNIST 过于简单，无法真正体现分布式训练的优势和难点，因此实验已经转向 Tiny-ImageNet。
Ce jeu de données contient 200 classes, avec 500 images d'entraînement et 50 images de validation par classe.
中文解释：这个数据集包含 200 个类别，每个类别有 500 张训练图像和 50 张验证图像。
Les images sont au format couleur, ce qui rend la tâche plus réaliste et plus exigeante que MNIST.
中文解释：这些图像是彩色的，因此相比 MNIST，这个任务更真实，也更有挑战性。

La logique de chargement des données a donc été adaptée au format de Tiny-ImageNet, et la boucle d'entraînement a également été ajustée afin que le modèle puisse traiter correctement ce nouveau jeu de données.
中文解释：因此，数据加载逻辑已经针对 Tiny-ImageNet 的格式进行了适配，训练循环也做了相应调整，以确保模型能够正确处理这个新数据集。

En pratique, l'ensemble d'entraînement contient 100 000 images (200 classes × 500 images par classe), l'ensemble de validation 10 000 images (200 classes × 50 images par classe), et l'ensemble de test 10 000 images.
中文解释：在实际规模上，训练集共有 100000 张图像（200 类 × 每类 500 张），验证集有 10000 张图像（200 类 × 每类 50 张），测试集也有 10000 张图像。

À ce stade, les performances du modèle restent cependant limitées.
中文解释：不过，到目前为止，模型性能仍然比较有限。
Sur les expériences distribuées les plus récentes en CPU, une époque peut encore prendre de l'ordre de 10 minutes selon la configuration MPI, la taille de batch locale et le mode de synchronisation.
中文解释：在最近的 CPU 分布式实验中，一个 epoch 依然可能需要大约 10 分钟，具体取决于 MPI 配置、本地 batch 大小以及同步模式。
La convergence demeure également faible sur la configuration CNN actuellement utilisée : la précision de test reste basse après peu d'époques, ce qui suggère qu'il reste à la fois un travail d'optimisation système et un travail de réglage du modèle.
中文解释：当前使用的 CNN 配置在收敛性方面也仍然偏弱：训练若干个 epoch 后测试精度依然较低，这说明后面既需要继续做系统优化，也需要对模型本身进行调参和改进。

La suite du travail devra donc porter sur deux directions complémentaires : d'une part l'accélération plus poussée du calcul, en particulier des chemins `im2col/col2im` et du backward convolutionnel ; d'autre part l'amélioration de l'architecture ou du réglage du modèle, afin d'améliorer à la fois l'efficacité de l'entraînement et la qualité finale des résultats.
中文解释：因此，后续工作应沿着两个互补方向推进：一方面要进一步加速计算，尤其是 `im2col/col2im` 路径和卷积 backward；另一方面要改进模型结构或训练配置，以同时提升训练效率和最终效果。
