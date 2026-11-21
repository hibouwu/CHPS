# Implémentation des verrous · 锁的实现

[目录](README.md) · [教师英文讲义（53 页）](../../GitLab/cours/02-locks.pdf) · [本讲实验](../../GitLab/locks/Readme.md)

## De la lecture à une acquisition indivisible · 从读状态到原子获锁

[原讲义第 1–4 页](../../GitLab/cours/02-locks.pdf#page=1)

**FR** Deux threads peuvent lire un verrou libre avant que l'un ou l'autre n'écrive « occupé ». Les deux entreraient alors dans la section critique. L'acquisition doit faire observer le test et le changement d'état comme une seule action. Un chargement atomique suivi d'un stockage atomique laisse encore un intervalle entre les deux.

**中文** 两个线程都可能在任一方写「忙」之前看到锁是空闲的，于是双双进入临界区。获锁必须让其他线程把检查和改写看成一个不可分割的动作。即使读和写分别是原子的，两者之间依然有竞争窗口。

## Modèle de machine · 抽象机器模型

[原讲义第 5–8 页](../../GitLab/cours/02-locks.pdf#page=5)

**FR** Le modèle initial suppose des lectures et écritures de mots indivisibles et des instructions observées dans l'ordre prévu. Quand `x` passe de `0` à `0x101`, le lecteur voit une valeur complète. Si le producteur écrit d'abord `x = 0x101` puis `y = 0x202`, un lecteur qui lit le nouveau `y` puis `x` doit voir le nouveau `x` dans ce modèle. Le cours lève ensuite ces hypothèses pour distinguer atomicité et ordre mémoire.

**中文** 起始模型假设机器字的读写不可撕裂，指令按约定顺序被观察。若 `x` 从 `0` 改成 `0x101`，读取者会看到一个完整值。在这个模型里，若生产者先写 `x = 0x101` 再写 `y = 0x202`，先读到新 `y` 再读 `x` 的线程应当看到新 `x`。后续要放开这些假设，分开分析原子性和内存顺序。

## Algorithme de la boulangerie · Bakery 取号算法

[原讲义第 9–13 页](../../GitLab/cours/02-locks.pdf#page=9)

**FR** Pour `N` threads, `num[i]` est le numéro du thread `i`, et 0 indique qu'il ne demande pas le verrou. Le thread signale qu'il choisit son numéro avec `entering[i]`, prend 1 plus le maximum lu, puis termine le choix. Deux threads peuvent prendre le même numéro. L'ordre lexicographique `(num[i], i)` donne la priorité au plus petit couple non nul. Quand un concurrent choisit encore son numéro, le pseudo-code de la p. 11 reprend le balayage avec `goto restart`. Sans cette vérification, le thread 3 pourrait entrer alors que le thread 2 a calculé le même numéro sans encore l'avoir publié. À la sortie, on remet son numéro à 0. Le balayage examine les `N` participants.

**中文** 对 `N` 个线程，`num[i]` 是线程 `i` 的号，0 表示它不在竞争。线程先用 `entering[i]` 表明自己正在选号码，再取读到的最大号码加一，最后清除选号标志。两人可能同号，因此以 `(num[i], i)` 的字典序判断先后，较小的非零号二元组优先。第 11 页新版伪代码遇到尚在取号的人会 `goto restart` 重新扫描。否则，线程 2 算完号码还没写回时，线程 3 可能已用同号进入。解锁时把自己的号清零。每轮扫描涉及 `N` 个参与者。

## Cohérence des caches et contention · 缓存一致性与争用

[原讲义第 14–20 页](../../GitLab/cours/02-locks.pdf#page=14)

**FR** Les caches échangent des lignes entières, couramment de 64 octets dans l'exemple. Plusieurs cœurs peuvent détenir une copie d'une ligne partagée. Pour la modifier, un cœur obtient la permission d'écrire et invalide les autres copies concernées. Deux écritures sur `tab[0]` et `tab[1]` peuvent donc se gêner si les deux éléments sont sur la même ligne. C'est le faux partage. Sous contention, les écritures répétées sur le mot d'un verrou multiplient les transferts de cette ligne.

**中文** 缓存以整行为单位交换数据，课件以常见的 64 字节行举例。同一行可以在多个核中保存共享副本，修改前则需要取得写权限，让相关副本失效。因此，分别写 `tab[0]` 和 `tab[1]`，也可能争抢同一行，这就是伪共享。锁争用时若一直改写同一个锁字，缓存行会频繁在核之间转移。

## Atomicité, réordonnancement et relaxed · 原子性、重排和 relaxed

[原讲义第 21–29 页](../../GitLab/cours/02-locks.pdf#page=21)

**FR** En C, `atomic_load` et `atomic_store` s'appliquent à un objet atomique. Le compilateur et le processeur ont des règles distinctes de réordonnancement. Les exemples de TSO et de barrières d'assemblage illustrent le niveau matériel. Avec `memory_order_relaxed`, chaque accès atomique reste indivisible et respecte l'ordre de modification de son objet. En revanche, lire la nouvelle valeur atomique de `y` ne suffit pas à publier une écriture sur `x` effectuée plus tôt par l'autre thread. Des accès ordinaires conflictuels sans synchronisation constituent une course de données en C.

**中文** C 中的 `atomic_load`、`atomic_store` 用于原子对象。编译器和处理器各有重排规则，课件的 TSO 和汇编屏障例子讲的是硬件层。`memory_order_relaxed` 保留原子访问的不可分割性，以及单对象的修改顺序。但读到原子 `y` 的新值，还不足以发布另一线程更早对 `x` 的写。在 C 中，无同步的普通冲突访问构成数据竞争。

## Publication release–acquire · 用 release–acquire 发布数据

[原讲义第 30 页](../../GitLab/cours/02-locks.pdf#page=30)

**FR** Le producteur initialise des données, puis publie un indicateur atomique avec `release`. Si la lecture `acquire` lit cette publication, les écritures d'initialisation précèdent l'utilisation par le lecteur. Dans l'exemple ci-dessous, `x` est atomique, `y` et `z` sont écrits une seule fois par le producteur, et le lecteur ne lit les données qu'après avoir observé la publication.

**中文** 生产者先初始化数据，再用 `release` 写原子标志。消费者的一次 `acquire` 如果读到这次发布，发布前的初始化就先于它随后对数据的访问。下例中 `x` 是原子标志，`y` 和 `z` 由生产者一次性写入，读取方确认发布后才使用它们。

```c
/* Producer */
z = 1;
y = 17;
atomic_store_explicit(&x, 42, memory_order_release);

/* Consumer */
if (atomic_load_explicit(&x, memory_order_acquire) == 42) {
    /* Use y and z. */
}
```

**FR** L'exemple utilise `&x` dans les deux opérations atomiques et place les lectures ordinaires après le test. La diapositive 30 exprime cette condition dans sa conclusion, mais son pseudo-code lit ensuite `y` et `z` sans test.

**中文** 示例补上两个原子接口需要的 `&x`，也把普通变量的读取放在条件内。课件第 30 页的结论写了这个前提，但原伪代码随后无条件读了 `y` 和 `z`。

## Dépendance et cohérence séquentielle · 依赖顺序与顺序一致性

[原讲义第 31–33 页](../../GitLab/cours/02-locks.pdf#page=31)

**FR** L'idée du modèle `consume` présenté en cours est de suivre une dépendance côté lecteur, par exemple charger un pointeur puis accéder à travers lui. Dans l'exemple de la p. 31, la lecture ultérieure de `x` ne dépend pas de `r1`, et l'objet `z` n'est pas déclaré atomique. Pour la cohérence séquentielle (`seq_cst`), les opérations concernées se placent dans un ordre total commun, compatible avec l'ordre des threads. À la p. 32, les deux résultats contrastés restent possibles, comme le montre la trace ci-dessous. Le reste du cours adopte implicitement des accès atomiques séquentiellement cohérents dans ses pseudo-codes.

**中文** 课件介绍的 `consume` 模型沿读取端的依赖传播，比如先读取指针，再经该指针访问对象。第 31 页随后读 `x` 的动作并不依赖 `r1`，而且 `z` 也没有声明为原子变量。顺序一致性（`seq_cst`）要求相关操作可放进一个公共全序，同时保持各线程内部顺序。第 32 页给出的两组读值可以共存，下面就是一个合法交错。后续伪代码默认访问是顺序一致的原子操作。

```text
T4: read x → 0
T1: write x = 1
T3: read x → 1
T3: read y → 0
T2: write y = 1
T4: read y → 1
```

## Verrou tournant · Exchange 自旋锁

[原讲义第 34–40 页](../../GitLab/cours/02-locks.pdf#page=34)

**FR** `atomic_exchange` installe une valeur et renvoie l'ancienne dans la même opération de lecture–modification–écriture. Quand plusieurs threads écrivent `BUSY`, un seul reçoit l'ancien état `FREE` et acquiert le verrou. La libération remet `FREE`. Sous faible contention, l'acquisition est courte. Sous forte contention, chaque tentative d'échange réclame la permission d'écrire la même ligne.

**中文** `atomic_exchange` 在同一个原子读改写中安装新值并返回旧值。多个线程尝试写入 `BUSY`，只有拿到原状态 `FREE` 的那个获锁。释放时写回 `FREE`。低争用下路径很短，高争用下每次交换尝试都需要同一缓存行的写权限。

## Verrou à tickets · 票据锁

[原讲义第 41–46 页](../../GitLab/cours/02-locks.pdf#page=41)

**FR** `atomic_fetch_add(&ticket, 1)` renvoie un ticket unique et incrémente le distributeur. Le thread attend que `screen`, le numéro servi, atteigne son propre ticket. La sortie incrémente `screen`. Les concurrents tournent sur des lectures, mais chacun observe la même ligne. Le pseudo-code utilise `screen < my` sous l'hypothèse de numéros croissants sans retour à zéro.

**中文** `atomic_fetch_add(&ticket, 1)` 原子发号，返回旧值作为唯一票号。线程只读等待当前服务号 `screen` 到达自己的号码，释放时推进 `screen`。等待者避免反复写入，但仍盯着同一行。课件用 `screen < my`，对应票号单调且不回绕的假设。

## Verrou MCS et passage de relais · MCS 队列锁与交接

[原讲义第 47–53 页](../../GitLab/cours/02-locks.pdf#page=47)

**FR** Une comparaison-échange (CAS) écrit la nouvelle valeur seulement si la valeur courante correspond à celle attendue. En C, `atomic_compare_exchange_strong` met aussi à jour `expected` en cas d'échec. MCS utilise un nœud local à chaque thread (`_Thread_local`), un pointeur global de fin de file et un indicateur par nœud. L'arrivant installe son nœud en fin de file par échange atomique, le relie à son prédécesseur, puis attend sur son propre `isFree`. Si à la libération `my.next` est nul, le propriétaire tente de remplacer le pointeur de fin de file par `NULL` s'il pointe toujours sur son nœud. En cas d'échec, un successeur a pu modifier ce pointeur sans encore publier le lien. Le propriétaire attend ce lien puis signale le successeur. La file FIFO limite la compétition sur une même adresse. Un successeur préempté peut toutefois retarder toute la file.

**中文** CAS（比较并交换）只有当前值匹配预期时才写入。C 的 `atomic_compare_exchange_strong` 失败时还会更新 `expected`。MCS 使用每个线程各自的节点（`_Thread_local`）、一个全局队尾和每节点一个许可标志。新线程通过原子交换成为新队尾，接到前驱之后，再等自己的 `isFree`。释放时若 `my.next` 为 NULL，先尝试用 CAS 把队尾从自己改为 NULL。失败说明后继可能已改队尾而尚未接好链接，此时等链接出现，再给后继放行。FIFO 队列减少对同一地址的争抢，但队首若被抢占，后面的线程也会延迟。

| Verrou / 锁 | Attente / 等待位置 | Contention / 争用开销 |
|---|---|---|
| Exchange | Mot commun, échanges / 共享锁字，反复交换 | Écritures répétées / 反复争写权限 |
| Ticket | Compteur servi, lectures / 读服务号 | Invalidation à chaque passage / 交接使共享副本失效 |
| MCS | Indicateur propre, lectures / 读自己的标志 | Liaison puis passage au successeur / 接链后只通知后继 |

## Vérification rapide · 自检

- **FR** Qu'est-ce qui rend le résultat du CAS pertinent pour MCS ? Il discrimine la file vide d'un successeur qui a réservé sa place sans écrire le lien. **中文** MCS 为什么需要判断 CAS 结果？用来区分队列真空与后继已占队尾却尚未接链。
- **FR** Un accès relaxed peut-il lire un mot déchiré ? Il est atomique, même s'il ne construit pas la relation de publication entre deux objets. **中文** relaxed 会读到半个原子字吗？访问依然原子，只是单凭它不能在两个对象间建立发布关系。
