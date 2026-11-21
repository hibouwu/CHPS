# Algorithmes non bloquants · 非阻塞算法

[目录](README.md) · [教师英文讲义（76 页）](../../GitLab/cours/03-non-blocking.pdf) · [本讲实验](../../GitLab/non-blocking/Readme.md)

## Loi d'Amdahl et garanties de progression · Amdahl 定律与进展保证

[原讲义第 1–4 页](../../GitLab/cours/03-non-blocking.pdf#page=1)

**FR** Soit $T$ le temps sur un thread, $p$ la fraction de ce temps parallélisable, et $n$ le nombre de threads. Si cette fraction se répartit idéalement et que les surcoûts sont négligés, $T_n=T((1-p)+p/n)$ et l'accélération $S_n=T/T_n$ tend vers $1/(1-p)$ pour $p<1$. Avec $p=0{,}75$, la limite est 4. Les garanties de progression s'emboîtent. *Wait-free* donne une borne sur le nombre de ses propres pas nécessaires à chaque opération. *Lock-free* garantit la progression du système, même si un appel particulier peut échouer sans cesse. *Obstruction-free* garantit qu'un appel finit si son thread exécute suffisamment longtemps seul.

**中文** 记 $T$ 为单线程耗时，$p$ 为其中可并行的时间比例，$n$ 为线程数。若并行部分能理想均分并忽略额外开销，$T_n=T((1-p)+p/n)$，加速比 $S_n=T/T_n$ 在 $p<1$ 时趋近 $1/(1-p)$。例如 $p=0.75$，上限是 4。三种进展保证由强到弱包含。*Wait-free* 给出每次操作所需自身执行步数的上界。*Lock-free* 保证系统整体继续完成操作，单次调用仍可能不断失败。*Obstruction-free* 保证一个线程独占执行足够久时能完成当前操作。

## Pile et comparaison-échange · 栈与 CAS

[原讲义第 5–11 页](../../GitLab/cours/03-non-blocking.pdf#page=5)

**FR** Une pile LIFO empile et dépile au même endroit, `head`. La version avec verrou protège la mise à jour entière. Dans la version sans verrou, `push` lit `head`, relie le nouveau nœud à ce sommet, puis tente un CAS sur `head`. Après échec, il doit relire le sommet et reconstruire le lien. `pop` lit le sommet et son successeur, puis tente de substituer le successeur par CAS. Pour un `pop` vide, la lecture d'un sommet nul fournit le point de linéarisation. Pour une modification réussie, c'est le CAS qui la rend visible. Le modèle suppose que les nœuds restent valides pendant leur utilisation.

**中文** LIFO 栈在同一端 `head` 入栈和出栈。加锁版保护整个更新过程。无锁版 `push` 读出 `head`，让新节点接向这个栈顶，再用 CAS 替换 `head`。失败后要重新读栈顶并重设新节点的链接。`pop` 读出栈顶和后继，再尝试用 CAS 把后继设为新栈顶。空栈操作的线性化点可取观察到空的那次读取，实际修改的线性化点是成功的 CAS。这里假设使用中的节点保持有效。

```text
push(new):
    repeat:
        top = load(head)
        new.next = top
    until CAS(&head, top, new) succeeds
```

## File FIFO et sentinelle · FIFO 队列与哨兵

[原讲义第 12–19 页](../../GitLab/cours/03-non-blocking.pdf#page=12)

**FR** Une file retire le plus ancien élément et ajoute à l'autre extrémité. Dans la version à verrou, la tête et la queue sont mises à jour sous protection. Dans la version sans verrou, `head` pointe sur une sentinelle et le premier élément se trouve dans `head.next`. Au départ, `head == tail` et la sentinelle n'a pas de successeur. Après un ajout concurrent, `tail` peut encore pointer vers un nœud qui possède déjà un successeur. Le lien dans la liste représente l'ajout effectué, et la mise à jour de `tail` remet le pointeur auxiliaire à jour.

**中文** 队列从头取出最早的元素，从尾加入新元素。加锁版在保护下更新头和尾。无锁版让 `head` 指向哨兵，第一个元素在 `head.next`。起始时 `head == tail`，哨兵无后继。并发入队后，`tail` 可能还停在一个已有后继的节点上。链表链接表示元素已经加入，推进 `tail` 是维护辅助指针。

## Enfiler seul ou à deux · 单线程入队和并发帮助

[原讲义第 20–36 页](../../GitLab/cours/03-non-blocking.pdf#page=20) · [B、C 并行的动画起点](../../GitLab/cours/03-non-blocking.pdf#page=24)

**FR** Pour enfiler A, on relie A au dernier nœud en remplaçant son `next` nul par CAS. On tente ensuite d'avancer `tail` jusqu'à A. Si deux threads veulent enfiler B et C sur le même lien, un seul peut transformer ce `next` nul. L'autre peut observer que `tail.next` existe déjà, aider à avancer `tail` et recommencer à partir du nouveau bout. L'ajout se linéarise sur le CAS réussi de `next`. Le CAS sur `tail` peut être exécuté par un autre thread.

**中文** A 入队时，先用 CAS 把最后节点空的 `next` 改为 A，然后尝试将 `tail` 推进到 A。B 和 C 若争抢同一个空链接，只有一方能成功。另一方发现 `tail.next` 已经非空，就可以先帮助推进 `tail`，再从新的末端重试。入队的线性化点是写 `next` 的成功 CAS。更新 `tail` 的 CAS 可以由别的线程执行。

## Défiler et déplacer la sentinelle · 出队与移动哨兵

[原讲义第 37–40 页](../../GitLab/cours/03-non-blocking.pdf#page=37)

**FR** Le retrait observe la sentinelle courante `res` et son successeur. Sans successeur, il peut répondre « vide » au point d'observation. Sinon, le CAS fait du successeur la nouvelle sentinelle et l'appel renvoie sa valeur. L'ancienne sentinelle quitte la structure. La nouvelle existe toujours comme support du prochain retrait. Un échec de CAS indique qu'un concurrent a changé l'état observé. Une suite d'échecs pour un seul appel est compatible avec la progression globale.

**中文** 出队先观察当前哨兵 `res` 与它的后继。若无后继，可在这次观察时判定为空。否则用 CAS 让后继成为新哨兵，返回这个节点原先保存的值。旧哨兵离开结构，新哨兵留着供下一次出队使用。CAS 失败表示其他线程改了所观察的状态。一个调用连续失败，依然可能与整体进展并存。

## Liste triée et suppression logique · 有序链表与逻辑删除

[原讲义第 41–48 页](../../GitLab/cours/03-non-blocking.pdf#page=41)

**FR** Dans une liste triée, une insertion peut prendre un nœud comme prédécesseur au moment où un autre thread veut le supprimer. Déconnecter le nœud sans marquage peut rendre l'insertion inaccessible. Le schéma de Harris réunit adresse du successeur et bit de suppression dans le même mot `next`. Le bit de poids faible est disponible lorsque les adresses sont suffisamment alignées. Le CAS qui marque `cur.next` supprime logiquement `cur`. Le CAS du lien entrant peut ensuite le détacher physiquement.

**中文** 有序链表中，一个线程可能正在把某节点当作插入前驱，另一个线程却要删掉它。若直接摘链，刚插入的元素可能随被删节点一同丢出链表。Harris 算法把后继地址和删除位放在同一个 `next` 字中。地址对齐时可借用最低位。标记 `cur.next` 的成功 CAS 逻辑删除 `cur`，后续再用入边上的 CAS 物理摘链。

## Parcourir, aider et effacer · 遍历、帮助摘链和删除

[原讲义第 49–69 页](../../GitLab/cours/03-non-blocking.pdf#page=49) · [删除 17 的动画](../../GitLab/cours/03-non-blocking.pdf#page=60)

**FR** Pendant le parcours, `pred` désigne l'adresse du lien qui mène au nœud courant `cur`. Si le lien sortant de `cur` est marqué, un thread peut remplacer le lien entrant par le successeur, puis continuer. Après échec du CAS, il repart d'un état contrôlé. Pour supprimer 17, on cherche d'abord sa clé puis on marque son lien sortant. Le détachement peut ensuite être réalisé par l'appelant ou un autre thread. Une recherche de 13 s'arrête à 17 dans la liste triée si aucun 13 n'a été rencontré.

**中文** 遍历时，`pred` 是指向当前节点 `cur` 的链接地址。若 `cur` 的出边已被标记，就尝试把入边改指它的后继，然后继续走。CAS 失败则从可重新验证的位置开始。删除 17 时，先定位该关键字，再标记 17 的出边。之后可由原调用者或其他线程摘链。查找 13 时，如果有序遍历已到 17 且此前未遇到 13，就能判断未找到。

## Insérer et vérifier la liaison · 插入并验证接点

[原讲义第 70–76 页](../../GitLab/cours/03-non-blocking.pdf#page=70)

**FR** Pour insérer 14, on trouve l'intervalle ordonné, initialise le lien du nouveau nœud vers son successeur et tente le CAS sur le lien du prédécesseur. Le mot comparé contient le pointeur attendu et son état de marquage. Si le prédécesseur a été supprimé ou si le lien a changé, il faut retrouver l'emplacement. Séparer la marque et le lien laisserait une fenêtre entre leur contrôle et l'insertion. Après un détachement physique, la mémoire du nœud doit rester valide tant qu'un autre participant peut encore le déréférencer. La réutilisation d'une adresse peut aussi provoquer ABA. L'exercice local sur la pile permet de revenir sur ce point.

**中文** 插入 14 时，先按顺序找到区间，让新节点指向对应后继，再对前驱的链接执行 CAS。参加比较的同一个字同时含有预期指针和标记状态。如果前驱被删除或者链接被改动，应重新找插入位置。若分开验证指针与标记，就会在最后一次检查和插入之间留出窗口。节点摘链后，只要其他线程仍可能解引用它，就要保留这块内存。地址复用也可能造成 ABA。可以用本讲栈实验回头验证这个问题。

## Vérification rapide · 自检

- **FR** Distinguer le point de linéarisation, la progression et la récupération mémoire. Le premier fixe l'effet abstrait. La deuxième détermine quels appels pourront finir. La troisième protège les nœuds encore observables. **中文** 区分线性化点、进展和回收。第一项确定抽象操作何时生效，第二项说明完成有何保证，第三项保护仍可能被访问的节点。
- **FR** Un `tail` en retard empêche-t-il toute opération ? Les threads voient le lien déjà publié et peuvent aider à avancer le pointeur. **中文** `tail` 落后会挡住所有操作吗？其他线程能从已发布的后继链接出发帮助推进队尾。
