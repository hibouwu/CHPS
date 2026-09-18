# Algorithmique et Programmation Parallèle TD 1 – Prise en main et Communications point-à-point bloquantes MPI / 并行算法与编程 TD 1 – 入门与阻塞式点对点 MPI 通信

## Exercice I : Prise en main / 练习 I：入门

**Question 1 :** Écrire un programme MPI où chaque processus affiche : / **问题 1：** 编写一个 MPI 程序，使每个进程输出：

- son rang
  其进程编号
- le nombre total de processus MPI
  MPI 进程的总数
- la machine hôte sur laquelle il s'exécute (fonction `MPI_Get_processor_name`)
  其运行的主机名（函数 `MPI_Get_processor_name`）
- le processus id (pid) (fonction `getpid`)
  进程 id（pid）（函数 `getpid`）

Le tester.
进行测试。

Les valeurs des pids sont elles identiques ? Explication ?
这些 pid 值是否相同？请解释。

**Réponse / 答案：**

- Code de référence / 参考代码 : [prise_en_main/correction1.c](prise_en_main/correction1.c)
- Les `pid` ne sont pas identiques : chaque rang MPI est un processus systeme distinct lance par l'environnement MPI. / 这些 `pid` 不相同：每个 MPI rank 都是由 MPI 运行时启动的独立操作系统进程。
- Plusieurs rangs peuvent partager le meme hote, mais chaque processus garde son propre `pid`. / 多个 rank 可以运行在同一台主机上，但每个进程仍然拥有各自的 `pid`。

**Question 2 :** Rajouter la déclaration d'une variable `ma_var` et afficher l'adresse de cette variable par processus. / **问题 2：** 添加变量 `ma_var` 的声明，并在每个进程中显示该变量的地址。

- Les adresses affichées sont elles identiques ? Explication ?
  显示的地址是否相同？请解释。

**Réponse / 答案：**

- Code de référence / 参考代码 : [prise_en_main/correction2.c](prise_en_main/correction2.c)
- La valeur numerique affichee peut etre identique ou differente selon les processus, mais ce n'est jamais une memoire partagee. / 显示出的十六进制地址在不同进程中可能相同也可能不同，但它绝不是同一块共享内存。
- Chaque processus MPI possede son propre espace d'adressage virtuel ; `ma_var` est donc une variable locale privee. / 每个 MPI 进程都有独立的虚拟地址空间，因此 `ma_var` 是各自私有的局部变量。

**Question 3 :** Rajouter une instruction `printf("Avant MPI_Init\n")` juste avant l'appel à `MPI_Init`. / **问题 3：** 在调用 `MPI_Init` 之前加入一条 `printf("Avant MPI_Init\n")` 语句。

Combien de message « Avant MPI_Init » apparaît à l'écran en fonction du nombre de processus MPI ? Explication ?
随着 MPI 进程数的不同，屏幕上会出现多少条 « Avant MPI_Init » 信息？请解释。

**Réponse / 答案：**

- Code de référence / 参考代码 : [prise_en_main/correction3.c](prise_en_main/correction3.c)
- Le message apparait une fois par processus MPI lance. Si on lance `P` processus, on obtient donc `P` lignes `Avant MPI_Init`. / 该消息会对每个启动的 MPI 进程各打印一次；如果启动 `P` 个进程，就会看到 `P` 行 `Avant MPI_Init`。
- La raison est que tous les processus executent le programme des le debut, y compris les instructions situees avant `MPI_Init`. L'ordre d'affichage peut varier. / 原因是所有进程都会从程序开头开始执行，包括 `MPI_Init` 之前的语句；输出顺序可能不同。

## Exercice II : Ping pong / 练习 II：Ping pong

On demande d'écrire 3 programmes MPI qui font intervenir 2 processus MPI.
要求编写 3 个使用 2 个 MPI 进程的程序。

On désigne par :
定义如下：

|P0 / 进程 0|P1 / 进程 1|
|---|---|
|P0, le processus MPI de rang 0. / P0，MPI 进程号为 0。|P1, le processus MPI de rang 1. / P1，MPI 进程号为 1。|

**Programme 1 (ping) :** / **程序 1（ping）：**

|P0 / 进程 0|P1 / 进程 1|
|---|---|
|P0 envoie un entier de valeur 10 à P1. / P0 向 P1 发送值为 10 的整数。||
||P1 affiche la valeur reçue. / P1 输出收到的数值。|

**Réponse / 答案：**

- Code de référence / 参考代码 : [ping_pong/corr_ping1.c](ping_pong/corr_ping1.c)
- `P0` envoie l'entier `10` avec `MPI_Send`, et `P1` le recoit avec `MPI_Recv` puis l'affiche. / `P0` 用 `MPI_Send` 发送整数 `10`，`P1` 用 `MPI_Recv` 接收后输出。

**Programme 2 (pong) :** / **程序 2（pong）：**

|P0 / 进程 0|P1 / 进程 1|
|---|---|
||P1 remplit et envoie un tableau de 10 réels double précision à P0[^1]. / P1 填充并向 P0 发送一个包含 10 个双精度实数的数组[^1]。|
|P0 affiche le contenu du tableau[^2]. / P0 输出该数组的内容[^2]。||

**Réponse / 答案：**

- Code de référence / 参考代码 : [ping_pong/corr_pong2.c](ping_pong/corr_pong2.c)
- `P1` remplit un tableau de `10` `double`, l'envoie a `P0`, puis `P0` affiche chaque case pour verifier le contenu recu. / `P1` 填充一个包含 `10` 个 `double` 的数组并发送给 `P0`，随后 `P0` 逐项输出以验证接收内容。

**Programme 3 (ping-pong) :** / **程序 3（ping-pong）：**

|P0 / 进程 0|P1 / 进程 1|
|---|---|
|P0 envoie la valeur 10 à P1. / P0 向 P1 发送值 10。||
||Après la réception de ce message, P1 doit attendre 5 secondes[^3] avant de remplir et envoyer un tableau de 10 réels à P0. / 在收到该消息后，P1 需要等待 5 秒[^3]，然后填充并向 P0 发送一个包含 10 个实数的数组。|
|P0 doit afficher le contenu de ce tableau. / P0 需要输出该数组的内容。||

**Réponse / 答案：**

- Code de référence / 参考代码 : [ping_pong/corr_ping_pong3.c](ping_pong/corr_ping_pong3.c)
- `P0` envoie d'abord un entier a `P1`, puis attend le tableau. `P1` recoit le jeton, attend `5` secondes avec `sleep`, remplit le tableau et le renvoie. / `P0` 先向 `P1` 发送一个整数，然后等待数组返回；`P1` 收到令牌后用 `sleep` 等待 `5` 秒，再填充数组并发回。

## Exercice III : Questions pièges / 练习 III：陷阱问题

Les programmes dans les fichiers `questions_pieges/pieges/piege*.c` comportent des erreurs.
`questions_pieges/pieges/piege*.c` 文件中的程序包含错误。

Expliquez les erreurs, apportez les corrections.
解释错误并给出修正。

**Réponse / 答案：**

- Piege A : un seul `MPI_Send` de `10` entiers ne peut pas etre recu par `10` `MPI_Recv` separes d'un entier ; il faut une reception unique de `10` entiers. / 陷阱 A：一次发送 `10` 个整数的 `MPI_Send` 不能拆成 `10` 次各接收 `1` 个整数的 `MPI_Recv`；应改为一次接收 `10` 个整数。 Code : [questions_pieges/corrections/correctionA.c](questions_pieges/corrections/correctionA.c)
- Piege B : la source attendue est mauvaise ; le rang `1` doit recevoir depuis le rang `0`, pas depuis lui-meme. / 陷阱 B：接收源写错了；`1` 号进程应从 `0` 号进程接收，而不是从自己接收。 Code : [questions_pieges/corrections/correctionB.c](questions_pieges/corrections/correctionB.c)
- Piege C : les tags ne correspondent pas (`1000` a l'envoi, `2000` a la reception), donc le message ne matche jamais. / 陷阱 C：发送和接收的标签不一致（发送是 `1000`，接收是 `2000`），因此消息永远无法匹配。 Code : [questions_pieges/corrections/correctionC.c](questions_pieges/corrections/correctionC.c)
- Piege D : le type MPI ne correspond pas (`MPI_INT` envoye, `MPI_DOUBLE` recu) ; il faut recevoir un `int`, puis convertir si necessaire. / 陷阱 D：MPI 数据类型不匹配（发送是 `MPI_INT`，接收却是 `MPI_DOUBLE`）；应先按 `int` 接收，再在本地进行类型转换。 Code : [questions_pieges/corrections/correctionD.c](questions_pieges/corrections/correctionD.c)

## Exercice IV : Deadlock / 练习 IV：死锁

Ouvrez le programme `deadlock/exercice/deadlock.c`.
打开程序 `deadlock/exercice/deadlock.c`。

Dans ce programme (valable uniquement pour deux processus MPI), les processus 0 et 1 veulent s'envoyer mutuellement les `n` octets contenus dans leurs buffers d'envois respectifs `buf_send` (voir section de code ci-dessous).
在该程序中（仅适用于两个 MPI 进程），进程 0 和 1 想相互发送各自发送缓冲区 `buf_send` 中包含的 `n` 个字节（见下面的代码段）。

```c
char *buf_send = realloc(n, sizeof(char));
char *buf_recv = realloc(n, sizeof(char));
if (rang == 0)
    vois = 1;
else
    vois = 0;
```

Dans ce programme, les processus 0 et 1 veulent s'envoyer mutuellement les `n` octets contenus dans leurs buffers d'envois respectifs `buf_send`.
在该程序中，进程 0 和 1 想相互发送各自发送缓冲区 `buf_send` 中的 `n` 个字节。

1. Déterminez (par exécution successive) la valeur seuil de `n` pour laquelle le programme bloque.
   通过逐步执行确定使程序阻塞的 `n` 的阈值。
2. Expliquez en quoi cette section de code n'est pas sure.
   解释为何这段代码不安全。
3. Remplacez l'envoi standard par :
   将标准发送替换为：
   - un envoi synchrone ; 同步发送；
   - un envoi bufferisé (en utilisant les fonctions `MPI_Buffer_attach` et `MPI_Buffer_detach` et la variable `MPI_BSEND_OVERHEAD`). 缓冲发送（使用函数 `MPI_Buffer_attach`、`MPI_Buffer_detach` 以及变量 `MPI_BSEND_OVERHEAD`）。
   - Comment se comporte le programme dans chacun des cas a et b ? Débloquez le programme pour chacun des cas.
   程序在 a 和 b 两种情况下的表现如何？分别使程序解除阻塞。
4. Réécrivez cette section de code pour qu'elle fonctionne quelle que soit la valeur `n` et ceci avec un envoi standard.
   重写这段代码，使其在任意 `n` 值下都能正常工作，并使用标准发送。

**Réponse / 答案：**

1. Avec `mpich-4.3.0`, le blocage apparait pour `n >= 65393`. Ce seuil depend de l'implementation MPI et du passage du protocole eager au protocole rendezvous. / 在 `mpich-4.3.0` 下，`n >= 65393` 时会发生阻塞；这个阈值取决于 MPI 实现以及从 eager 协议切换到 rendezvous 协议的时机。 Code : [deadlock/correction/deadlock.c](deadlock/correction/deadlock.c)
2. La section n'est pas sure car les deux processus font d'abord un `MPI_Send` bloquant. Tant que MPI bufferise le message cela peut passer, mais pour les grands messages les deux cotes peuvent attendre indefiniment la reception correspondante. / 这段代码不安全，因为两个进程都先执行阻塞式 `MPI_Send`。当 MPI 还能缓存消息时可能表面正常，但消息一大，两边就可能同时等待匹配接收而永久阻塞。
3. Avec `MPI_Ssend`, si les deux processus gardent l'ordre `send` puis `recv`, le programme bloque systematiquement ; il faut casser la symetrie, par exemple faire `Recv` puis `Ssend` sur un des deux rangs. / 使用 `MPI_Ssend` 时，如果两个进程都保持 `send` 后 `recv` 的顺序，程序会稳定死锁；必须打破对称，例如让其中一个 rank 先 `Recv` 再 `Ssend`。 Code : [deadlock/correction/echange_synchrone.c](deadlock/correction/echange_synchrone.c)
4. Avec `MPI_Bsend`, les deux processus peuvent envoyer puis recevoir sans bloquer, a condition d'attacher un tampon de taille au moins `n + MPI_BSEND_OVERHEAD` par processus. / 使用 `MPI_Bsend` 时，只要每个进程都附加至少 `n + MPI_BSEND_OVERHEAD` 大小的缓冲区，就可以先发送再接收而不死锁。 Code : [deadlock/correction/echange_buffer.c](deadlock/correction/echange_buffer.c)
5. Pour une solution sure avec `MPI_Send` standard quelle que soit la valeur de `n`, il faut encore casser la symetrie : par exemple `rang 0` fait `Send` puis `Recv`, et `rang 1` fait `Recv` puis `Send`. / 若要在任意 `n` 下都用标准 `MPI_Send` 安全运行，仍然需要打破对称：例如让 `0` 号进程先 `Send` 后 `Recv`，而 `1` 号进程先 `Recv` 后 `Send`。 Code : [deadlock/correction/echange_standard.c](deadlock/correction/echange_standard.c)

## Exercice V : Renumérotation d'un anneau[^4] / 练习 V：环的重新编号[^4]

Soit un anneau unidirectionnel de $P$ processus ayant leurs propres mémoires et ne communiquant que par envois de messages. Chaque processus possède un lien entrant (le lien ouest) et un lien sortant (le lien est), et une variable `me` contenant initialement 0 pour le processus 0, et -1 pour les autres.
设有一个由 $P$ 个进程组成的单向环，每个进程拥有独立内存，仅通过消息发送进行通信。每个进程有一个入链（西向）和一个出链（东向），并有变量 `me`：进程 0 初始为 0，其余进程初始为 -1。

Cet exercice vise à écrire une routine de numérotation des processus (initialisation correcte des variables `me`) sans connaissance du nombre de processus de l'anneau.
本练习旨在编写进程编号例程（正确初始化变量 `me`），且不需要知道环中的进程数量。

![image](https://cdn-mineru.openxlab.org.cn/result/2026-02-06/ff59cf3a-7822-43e3-a32c-3acabf70a070/c545949eabe4e2ae08f1b14264ba00130e3b4e46dba211a5e2f390564d0f1304.jpg)

Dans cet exercice les fonctions `send` et `recv` permettent d'échanger facilement des `int`. On supposera les envois de messages bloquants (ex : `send(data_int, est)`). On supposera les réceptions de messages bloquantes (ex : `recv(data_int, ouest)`).
在本练习中，函数 `send` 和 `recv` 便于交换 `int`。假设消息发送为阻塞式（例：`send(data_int, est)`），接收也为阻塞式（例：`recv(data_int, ouest)`）。

**Question 1 :** Écrire une routine de renumérotation (et une seule) s'exécutant dans chaque processus et qui affecte le bon numéro à chaque processus (qui écrit la bonne valeur dans chaque variable `me`), sans connaître le nombre total de processus ($P$). / **问题 1：** 编写一个（且仅一个）在每个进程中执行的重新编号例程，使每个进程获得正确编号（在变量 `me` 中写入正确值），且不需要知道进程总数（$P$）。

Vous pouvez utiliser autant de variables, d'instructions `send` et `recv`, et d'accès à la variable `me` de chaque processus que vous le désirez. Mais vous ne devez pas supposer connu le nombre de processus avant la renumérotation, ni partager des variables entre les processus (la mémoire est purement distribuée).
你可以使用任意数量的变量、`send`/`recv` 指令，以及对每个进程变量 `me` 的访问。但不能假设在重新编号前已知进程数，也不能在进程间共享变量（内存完全分布）。

MPI permet très simplement d'obtenir le rang d'un processus et le nombre total de processus. Néanmoins, nous allons écrire un programme MPI pour tester notre routine.
MPI 可以很容易地获得进程号和进程总数。不过我们将编写一个 MPI 程序来测试该例程。

**Réponse / 答案：**

- Idee : le processus pour lequel `me_old == 0` injecte la valeur `0` vers l'est. / 思路：满足 `me_old == 0` 的进程先向东发送数值 `0`。
- Chaque autre processus recoit une valeur `x` depuis l'ouest, fixe `me = x + 1`, puis transmet cette nouvelle valeur a l'est. / 其余进程从西侧接收数值 `x`，令 `me = x + 1`，再把这个新值继续向东发送。
- Quand le message revient au processus initial, toute la boucle a ete numerotee sans connaitre `P` a l'avance. / 当消息回到初始进程时，整个环就完成了编号，而且事先不需要知道 `P`。
- Implementations completes / 完整实现 : [RenumAnneau/Q3/renum_anneau.c](RenumAnneau/Q3/renum_anneau.c), [RenumAnneau/Q4/renum_nproc_anneau.c](RenumAnneau/Q4/renum_nproc_anneau.c)

**Question 2 :** Écrire un programme MPI qui initialise sur chaque processus les variables `me` (valeur avant renumérotation), `ouest` (rang MPI) et `est` (rang MPI). / **问题 2：** 编写一个 MPI 程序，在每个进程上初始化变量 `me`（重新编号前的值）、`ouest`（MPI 进程号）和 `est`（MPI 进程号）。

**Réponse / 答案：**

- Code de référence / 参考代码 : [RenumAnneau/Q2/init_anneau.c](RenumAnneau/Q2/init_anneau.c)
- L'initialisation correcte est `est = (rang + 1) % nproc`, `ouest = (rang + nproc - 1) % nproc`, `me = (rang == 0 ? 0 : -1)`. / 正确初始化为 `est = (rang + 1) % nproc`、`ouest = (rang + nproc - 1) % nproc`、`me = (rang == 0 ? 0 : -1)`。

**Question 3 :** Écrire une fonction / **问题 3：** 编写一个函数

```c
int numerotation(int me_old, int ouest, int est)
```

qui retourne `me` après renumérotation. Vous devez utiliser uniquement les fonctions `MPI_Send` et `MPI_Recv`. Vérifier dans le programme principal que la valeur retournée de `me` est bien égale au rang du processus.
该函数返回重新编号后的 `me`。你必须只使用 `MPI_Send` 和 `MPI_Recv`。在主程序中验证返回的 `me` 值确实等于进程号。

**Réponse / 答案：**

- Code de référence / 参考代码 : [RenumAnneau/Q3/renum_anneau.c](RenumAnneau/Q3/renum_anneau.c)
- Le processus initial (`me_old == 0`) envoie `0`, conserve `me = 0`, puis attend le retour du dernier message. Chaque autre processus recoit, incremente et retransmet. / 初始进程（`me_old == 0`）发送 `0`、保留 `me = 0`，然后等待最后一个消息返回；其他进程负责接收、加一并继续转发。
- La verification du programme principal consiste a tester `me == rang`. / 主程序中的验证条件就是检查 `me == rang`。

**Question 4 :** Écrire une fonction / **问题 4：** 编写一个函数

```c
void numerotation_nproc(int me_old, int ouest, int est, int *me, int *P)
```

qui retourne `*me` après renumérotation et le nombre total de processus dans `*P`. Vérifier dans le programme principal que la valeur retournée dans `*me` est bien égale au rang du processus et que celle dans `*P` est bien égale au nombre total de processus MPI.
该函数返回重新编号后的 `*me` 以及进程总数 `*P`。在主程序中验证 `*me` 等于进程号且 `*P` 等于 MPI 进程总数。

**Réponse / 答案：**

- Code de référence / 参考代码 : [RenumAnneau/Q4/renum_nproc_anneau.c](RenumAnneau/Q4/renum_nproc_anneau.c)
- Premiere phase : on renumerote exactement comme a la question 3 et le dernier rang fait remonter `P - 1` jusqu'au processus initial. / 第一阶段与问题 3 相同完成重新编号，最后一个进程把 `P - 1` 回传给初始进程。
- Deuxieme phase : le processus initial calcule `P`, puis diffuse cette valeur dans l'anneau pour que tout le monde la connaisse. / 第二阶段由初始进程算出 `P`，再把它沿环广播，使所有进程都知道总进程数。
- La verification finale est `(*me == rang && *P == nproc)`. / 最终验证条件是 `(*me == rang && *P == nproc)`。

## Exercice VI : Maître/Esclaves / 练习 VI：主从

**Question préparatoire 1 :** / **准备问题 1：**

Tout processus autre que 0 tire au hasard un temps d'attente. Écrire un programme où le processus de rang 0 affiche au fur et à mesure les rangs des processus dans leur ordre de terminaison.
除 0 号进程外，所有进程随机选择一个等待时间。编写一个程序，使 0 号进程按完成顺序逐步输出各进程的编号。

**Réponse / 答案：**

- Code de référence / 参考代码 : [master_slave/correction/q1_ordered_print.c](master_slave/correction/q1_ordered_print.c)
- Chaque esclave attend un temps aleatoire puis envoie un message vide avec l'etiquette `TAG_READY` au maitre. / 每个从进程随机等待一段时间后，用标签 `TAG_READY` 向主进程发送一个空消息。
- Le maitre fait `nproc - 1` receptions avec `MPI_ANY_SOURCE` et affiche `status.MPI_SOURCE`, ce qui donne naturellement l'ordre de terminaison. / 主进程使用 `MPI_ANY_SOURCE` 接收 `nproc - 1` 次，并输出 `status.MPI_SOURCE`，自然就得到了完成顺序。

**Question préparatoire 2 :** / **准备问题 2：**

Tout processus autre que 0 tire au hasard une taille d'un tableau d'entiers, remplit ce tableau, affiche la somme des éléments puis envoie son tableau au processus de rang 0 qui affiche la somme de chaque tableau reçu. Écrire un tel programme.
除 0 号进程外，所有进程随机选择一个整型数组大小，填充数组，输出元素之和，然后将数组发送给 0 号进程；0 号进程输出每个收到数组的元素和。编写该程序。

**Réponse / 答案：**

- Code de référence / 参考代码 : [master_slave/correction/q2_unkown_sizes.c](master_slave/correction/q2_unkown_sizes.c)
- Chaque esclave choisit une taille `nint`, remplit son tableau, calcule sa somme puis l'envoie a `0`. / 每个从进程先随机生成大小 `nint`，填充数组，计算本地总和后发送给 `0` 号进程。
- Le maitre utilise `MPI_Probe` puis `MPI_Get_count` pour connaitre la taille du message avant allocation et reception, puis recalcule la somme du tableau recu. / 主进程用 `MPI_Probe` 和 `MPI_Get_count` 先获知消息大小，再分配空间并接收，最后重新计算收到数组的总和。

**Question 3 :** / **问题 3：**

Ouvrir le fichier `master_slave/exercice/master_slave_exo.c`.
打开文件 `master_slave/exercice/master_slave_exo.c`。

Principe du programme :
程序原理：

- le processus 0 joue le rôle du maître, les autres processus sont les esclaves
  进程 0 作为主进程，其他进程为从进程
- tant qu'il y a des données à lire, le processus 0 lit des données (fonction `read_data`) et, pour une lecture, le maître envoie ce tableau au premier esclave disponible
  只要还有数据可读，进程 0 读取数据（函数 `read_data`），并将该数据发送给第一个可用的从进程
- chaque esclave attend du maître un message dont il ne connaît pas la nature par avance : « données à traiter » ou bien « fin du travail de l'esclave »
  每个从进程等待主进程发送的消息，但事先不知道消息类型：是“待处理数据”还是“从进程结束工作”
- si la nature du message est « données à traiter », l'esclave appellera la fonction `process_data` puis se mettra en attente du prochain message venant du maître
  如果消息类型为“待处理数据”，从进程调用 `process_data`，然后等待来自主进程的下一条消息
- si la nature du message est « fin du travail de l'esclave », l'esclave terminera son travail
  如果消息类型为“从进程结束工作”，从进程结束工作

Paralléliser ce programme avec MPI en complétant les rubriques /* TRAVAIL A FAIRE */. Ce programme fonctionnera avec au moins deux processus MPI.
通过补全 /* TRAVAIL A FAIRE */ 将该程序并行化。该程序至少在两个 MPI 进程下运行。

Quelques indications :
一些提示：

- utiliser les étiquettes des messages pour indiquer les natures des messages
  使用消息标签来表示消息类型
- la fonction `MPI_Probe` permet d'attendre n'importe quel type de message
  函数 `MPI_Probe` 可等待任意类型的消息
- la fonction `MPI_Get_count` permet de récupérer la taille d'un message à recevoir
  函数 `MPI_Get_count` 用于获取将接收消息的大小
- `MPI_ANY_SOURCE` et `MPI_ANY_TAG` permettent à `MPI_Recv` d'attendre un message de n'importe quelle source avec n'importe quelle étiquette
  `MPI_ANY_SOURCE` 和 `MPI_ANY_TAG` 允许 `MPI_Recv` 等待来自任意源、任意标签的消息

**Réponse / 答案：**

- Fichier a completer / 待补全文件 : [master_slave/exercice/master_slave_exo.c](master_slave/exercice/master_slave_exo.c)
- Correction de reference / 参考实现 : [master_slave/correction/q3_master_slave_mpi.c](master_slave/correction/q3_master_slave_mpi.c)
- Protocole conseille : les esclaves annoncent leur disponibilite avec `TAG_READY`, le maitre envoie soit des donnees avec `TAG_DATA + cptr`, soit un message vide de fin avec `TAG_END`. / 推荐协议：从进程用 `TAG_READY` 声明自己空闲，主进程要么用 `TAG_DATA + cptr` 发送数据，要么用空消息 `TAG_END` 通知结束。
- Cote esclave, `MPI_Probe` permet de distinguer la nature du prochain message, puis `MPI_Get_count` donne la taille exacte du tableau a recevoir. / 在从进程一侧，`MPI_Probe` 可以先判断下一条消息的类型，`MPI_Get_count` 则用于获取即将接收数组的准确长度。

## Références / 参考

[^1]: Vous êtes libres du contenu du tableau envoyé par P1.
  P1 发送的数组内容可自行决定。
[^2]: Vérifier qu'il s'agit bien du même contenu que celui de P1.
  验证内容与 P1 的内容一致。
[^3]: Utiliser la fonction `sleep` (`#include <unistd.h>`).
  使用 `sleep` 函数（`#include <unistd.h>`）。
[^4]: Exercice largement inspiré de celui écrit par Stéphane Vialle, Supelec.
  本练习很大程度上参考了 Stéphane Vialle（Supelec）编写的练习。
