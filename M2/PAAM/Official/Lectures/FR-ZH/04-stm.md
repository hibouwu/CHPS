# Mémoire transactionnelle · 事务内存

[目录](README.md) · [教师英文讲义（54 页）](../../GitLab/cours/04-stm.pdf) · [本讲实验](../../GitLab/stm/Readme.md)

## Bloc atomique et composition · 原子块与操作组合

[原讲义第 1–4 页](../../GitLab/cours/04-stm.pdf#page=1)

**FR** Un grand verrou sérialise des opérations parfois indépendantes. Avec plusieurs verrous, le programme doit gérer l'ordre d'acquisition et la composition. La mémoire transactionnelle (TM) propose un bloc `atomic { ... }` dont les modifications apparaissent comme une opération entière aux autres transactions. Si `x` vaut 21, « ajouter 1 » puis « multiplier par 2 » donne 44, et l'ordre inverse donne 43. Les deux résultats s'expliquent par l'exécution de blocs entiers. Le bloc transactionnel est une abstraction de plusieurs opérations sur l'état partagé.

**中文** 大锁会让原本独立的工作串行。用多把锁又要管理加锁顺序和操作组合。事务内存（TM）提供 `atomic { ... }`，让其他事务把整个块的修改看成一次作用。若 `x` 初值为 21，先加 1 再乘 2 得 44，反过来得到 43。两个结果都能用整体执行的事务解释。原子块描述的是对共享状态的一组操作。

## Attendre avec retry et proposer une alternative · retry 等待与 orElse 备选分支

[原讲义第 5–9 页](../../GitLab/cours/04-stm.pdf#page=5)

**FR** Dans l'interface de mémoire transactionnelle logicielle (STM) du cours, `retry` abandonne l'essai et attend un changement parmi les états lus. L'ensemble de lecture indique à l'exécution sur quels changements attendre. Pour déplacer un élément de `src` vers `dst`, une seule transaction externe englobe les deux opérations. Un `retry` interne fait reprendre le bloc externe, évitant un retrait visible sans insertion. Avec `orElse`, l'échec par `retry` de la première branche permet d'essayer la seconde. L'exemple retourne immédiatement `null` si la file ne fournit pas d'élément.

**中文** 在课件的软件事务内存（STM）接口中，`retry` 放弃这次尝试，等待读过的状态有变化。运行时根据读集合确定要等什么。把元素从 `src` 搬到 `dst` 时，一个外层事务包住出队和入队，内部的 `retry` 会让整个外层块重来，避免只完成出队。使用 `orElse` 时，第一分支若执行 `retry`，就尝试备选分支。课件用它演示队列为空时立即返回 `null`。

## Conflits et journaux redo/undo · 冲突与重做、撤销日志

[原讲义第 10–14 页](../../GitLab/cours/04-stm.pdf#page=10)

**FR** Un verrou global donne une première implémentation pessimiste. Une implémentation optimiste autorise plusieurs essais simultanés, puis vérifie leurs dépendances. Si une transaction produit successivement `b` et `c` sur une même adresse, une autre transaction ne doit pas dépendre du seul état intermédiaire `b`. Avec un journal redo, on garde les nouvelles valeurs en privé, puis on les publie après validation. Avec un journal undo, on modifie la mémoire et on garde les anciennes valeurs pour pouvoir annuler. Le système doit aussi gérer les lecteurs pour empêcher qu'ils s'appuient sur un état intermédiaire.

**中文** 全局锁给出一种悲观实现。乐观实现允许多个事务同时试执行，随后验证读取依赖。若一个事务先后对同一地址写 `b` 和 `c`，其他事务不应依赖仅存在于中途的 `b`。redo 日志私下保存新值，验证成功后再发布。undo 日志会修改共享内存并保存旧值，以便撤销。运行时仍要管理读者，防止它们依赖中间状态。

**FR** À la p. 13, deux essais partent de `x=20`. Si celui qui produit 40 valide en premier, l'autre doit refaire ou abandonner son calcul de 21. À la p. 14, l'annulation restaure `z` à 30 sans effacer la mise à jour indépendante de `y` à 6.

**中文** 第 13 页两个试执行都从 `x=20` 开始。若准备写 40 的事务先提交，另一个基于旧值算出的 21 就需要重算或丢弃。第 14 页的撤销把 `z` 恢复到 30，同时保留另一事务把 `y` 改成 6 的更新。

## Détection et supports d'implémentation · 冲突检测与实现方式

[原讲义第 15–16 页](../../GitLab/cours/04-stm.pdf#page=15)

**FR** Une détection précoce (*eager*) contrôle les conflits au cours des accès. Une détection tardive (*lazy*) repousse une partie des contrôles jusqu'à la validation. Ce choix s'ajoute à celui du journal. La HTM s'appuie sur le matériel, la STM sur l'instrumentation logicielle et la HyTM combine les deux. La capacité d'une transaction et les causes d'abandon dépendent de l'implémentation.

**中文** 早期检测（*eager*）在访问过程中检查冲突，延迟检测（*lazy*）把部分检查推到提交。这是日志设计以外的一项取舍。HTM 借助硬件，STM 通过软件记录与验证，HyTM 混合使用两者。事务容量与中止条件取决于具体实现。

## Versions et lecture de ses propres écritures · 版本号与读取自己的写入

[原讲义第 17–22 页](../../GitLab/cours/04-stm.pdf#page=17)

**FR** La première STM associe un numéro de version à chaque emplacement. L'essai mémorise les versions lues et garde ses modifications dans un journal privé. La validation prend un verrou, vérifie les versions, puis applique les changements. Dans l'exemple, `a=10`, `b=21`, `e=8`. La transaction calcule `a=a+b` soit 31, puis `c=a-e` soit 23, puis `b=c` soit 23. La deuxième ligne doit lire la nouvelle valeur de `a` dans le journal privé. `e` fait partie des lectures à valider sans être écrit.

**中文** 第一版 STM 为每个位置配一个版本号。试执行记住所读版本，把修改写到私有日志。提交时加锁、核对版本，再公开更新。例子初值 `a=10`、`b=21`、`e=8`。事务先做 `a=a+b` 得 31，再做 `c=a-e` 得 23，最后 `b=c` 得 23。第二句必须读出私有日志里的新 `a`。`e` 需要验证，却不需要写回。

## Transactions zombies · 僵尸事务

[原讲义第 23–35 页](../../GitLab/cours/04-stm.pdf#page=23) · [除零例子](../../GitLab/cours/04-stm.pdf#page=30)

**FR** Dans le premier scénario, un thread vérifie que `x` est non nul, mais un autre valide `x=null` avant le nouvel accès à `x` pour l'appel. Le second scénario combine deux variables. L'état passe de `(x,y)=(4,5)` à `(217,4)`. La transaction peut lire l'ancien `x=4` et le nouveau `y=4`, puis tenter de calculer `1/(4-4)`. Aucun des états validés n'a `x=y`. Rejeter la transaction lors du commit arriverait après l'erreur. Il faut empêcher qu'une transaction continue avec des lectures incompatibles.

**中文** 第一个情形里，一个线程判断 `x` 非空，但另一个事务在调用所用的下一次读取前提交了 `x=null`。第二个情形涉及两个变量。状态从 `(x,y)=(4,5)` 更新为 `(217,4)`；某事务却先读旧 `x=4)，再读新 `y=4`，接着算 `1/(4-4)`。两个已提交状态都没有 `x=y`。等提交时再拒绝已来不及阻止除零，所以要及时阻止事务用不兼容的读值继续执行。

## Horloge globale et instantané · 全局时钟与快照

[原讲义第 36–45 页](../../GitLab/cours/04-stm.pdf#page=36)

**FR** Soit `G` l'horloge globale, qui donne la version du prochain commit, et `S` sa copie prise au démarrage. Lors d'une lecture dans l'état partagé, une version `v >= S` impose l'abandon. Au commit, sous verrou, on revérifie l'ensemble de lecture, on écrit les nouvelles paires avec la version `G`, puis on incrémente `G`. Dans l'animation, le lecteur démarre à `S=100`. Le nouvel `y` a la version 100, même si l'horloge est ensuite passée à 101. L'égalité à la borne suffit pour abandonner.

**中文** 令 `G` 为全局时钟，表示下一次提交可使用的版本，`S` 是事务开始时取的副本。从共享状态读取时，若版本 `v >= S` 就中止。提交时持锁复查读集合，将新值以版本 `G` 写回，再递增 `G`。动画中读事务从 `S=100` 开始，新 `y` 的版本为 100，即使全局时钟后来变成 101，这次读取仍因等于边界而中止。

## Paires immuables et publication · 不可变值—版本对与发布

[原讲义第 46–51 页](../../GitLab/cours/04-stm.pdf#page=46)

**FR** Une paire immuable `(valeur, version)` évite de combiner une nouvelle valeur avec un ancien compteur. Un commit prépare de nouveaux objets et change les références publiées. Une lecture consulte d'abord l'ensemble d'écriture privé. Sinon, elle charge une paire, vérifie sa version et enregistre l'adresse dans l'ensemble de lecture. Le commit utilise un verrou. Pour exécuter ce modèle, il faut également publier correctement références et horloge selon le langage et garder les anciennes paires vivantes tant qu'un lecteur s'en sert.

**中文** 不可变的 `(值, 版本)` 避免新值与旧计数器被拼在一起。提交时先准备新对象，再替换对外发布的引用。读操作先查私有写集合，否则读取共享值—版本对、校验版本并把位置加入读集合。提交通过一把锁串行保护。实际实现还要按语言内存模型发布引用和时钟，并保留仍被读者使用的旧值对。

## Temporisation, effets externes et mesures · 退避、外部副作用与性能

[原讲义第 52–54 页](../../GitLab/cours/04-stm.pdf#page=52)

**FR** Après un conflit, un délai aléatoire croissant peut décaler les nouveaux essais. Dans le pseudo-code de la p. 52, l'appel récursif remet la fenêtre à 16. Une boucle doit conserver la fenêtre entre les essais pour obtenir l'effet voulu. Un envoi ou une écriture externe peut survivre à un abandon de la transaction, d'où la nécessité d'organiser ces effets autour du commit. Sur le test à deux cœurs, 100 threads effectuent chacun 10 000 incréments. Le cours rapporte 3,0 s en STM sans temporisation, 0,48 s avec temporisation et 0,19 s avec un verrou.

**中文** 冲突后逐渐拉大随机退避窗口，可以错开新的尝试。第 52 页伪代码的递归调用会把窗口重设为 16。要实现预期效果，需让窗口在重试循环中持续存在。发送消息或写外部文件后，事务中止也未必能撤回动作，因此要安排它与提交的关系。课件的双核测试让 100 个线程各做 10 000 次递增，无退避 STM、退避 STM 和锁分别用了 3.0、0.48 和 0.19 秒。

## Vérification rapide · 自检

- **FR** Une lecture au compteur 100 est-elle acceptée pour `S=100` ? Elle est rejetée dans la convention du cours, qui consomme `G` avant de l'incrémenter. **中文** `S=100` 时能否读版本 100？按课件先用 `G` 再递增的约定，必须中止当前事务。
- **FR** Pourquoi un commit correct ne suffit-il pas ? Le corps peut déjà avoir calculé à partir d'un instantané incohérent ou réalisé un effet externe. **中文** 为什么仅保证提交正确还不够？事务体可能已经用不一致快照计算，或者产生了外部副作用。
