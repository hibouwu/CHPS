# 100 Questions de révision - Lecture 3 : Gestion de la Mémoire et Exécution / 100 道复习题 - 第三讲：内存管理与程序执行

## I. Objectifs du Noyau et Processus / 内核目标与进程 (1-15)

1. **Quels sont les 2 objectifs fondamentaux du noyau concernant les ressources ? / 内核关于资源的两个基本目标是什么？**
    * Répartir équitablement les ressources et garantir la sécurité des données. (公平分配资源和保证数据安全。)
2. **Qu'est-ce qu'un processus ? / 什么是进程？**
    * Une instance d'un programme en cours d'exécution à un instant $t$. (t 时刻正在运行的程序实例。)
3. **De quoi dispose chaque processus en propre ? / 每个进程拥有什么独享资源？**
    * Son propre espace mémoire et des ressources système. (自己的内存空间和系统资源。)
4. **Quel est le défi principal de la cohabitation des processus ? / 进程共存的主要挑战是什么？**
    * Garantir l'isolation et la sécurité des données de chacun. (保证每个进程的数据隔离和安全。)
5. **Que faire si un processus est plus grand que la mémoire physique ? / 如果进程比物理内存大怎么办？**
    * Utiliser la mémoire virtuelle et le mécanisme d'évincement (swap). (使用虚拟内存和置换机制 (swap)。)
6. **Comment le noyau identifie-t-il le format d'un fichier exécutable ? / 内核如何识别可执行文件的格式？**
    * Grâce à un en-tête (header) spécifique et un "nombre magique". (通过特定的头部和“魔数”。)
7. **Que signifie ELF ? / ELF 是什么意思？**
    * Executable and Linkable Format. (可执行与可链接格式。)
8. **Citez une commande pour lire l'en-tête d'un fichier ELF. / 列举一个用于读取 ELF 文件头的命令。**
    * `readelf -h`.
9. **Quelle information cruciale contient l'en-tête ELF ? / ELF 头包含什么关键信息？**
    * Architecture cible, point d'entrée, type de fichier, etc. (目标架构、入口点、文件类型等。)
10. **Quelles sont les premières étapes de l'exécution d'un programme (via exec) ? / 程序执行（通过 exec）的前几个步骤是什么？**
    * Détection du type, projection en mémoire, préparation de l'interpréteur. (类型检测、映射到内存、准备解释器。)
11. **Quelle fonction est réellement le point d'entrée technique (avant main) ? / 哪个函数是真正的技术入口点（在 main 之前）？**
    * `_start`.
12. **Qui appelle la fonction `main()` ? / 谁调用 `main()` 函数？**
    * `__libc_start_main` (après initialisation via `_init`).
13. **Que signifie "Position-Independent Executable" (PIE) ? / "Position-Independent Executable" (PIE) 是什么意思？**
    * Le code peut être chargé à n'importe quelle adresse mémoire (sécurité améliorée). (代码可以加载到任何内存地址（提高安全性）。)
14. **Qu'est-ce que le "Magic Number" d'un fichier ELF (en hex) ? / ELF 文件的“魔数”是什么（十六进制）？**
    * `7f 45 4c 46` (.ELF).
15. **Quel est le rôle du "dynamic linker/loader" ? / "dynamic linker/loader" 的作用是什么？**
    * Charger les bibliothèques partagées nécessaires au lancement du programme. (加载程序启动所需的共享库。)

## II. Espace Mémoire : Pile et Tas / 内存空间：栈与堆 (16-35)

1. **Sur une architecture 64 bits, combien de bits sont réellement utilisés pour l'adressage (actuellement) ? / 在 64 位架构上，实际用于寻址的有多少位（目前）？**
    * 48 bits. (48 位。)
2. **Quelle est la taille de l'espace d'adressage virtuel théorique avec 48 bits ? / 48 位寻址的理论虚拟地址空间大小是多少？**
    * $2^{48}$ (= 256 Tio).
3. **Quels sont les deux segments principaux de données modifiables dans un processus ? / 进程中可修改数据的两个主要段是什么？**
    * La Pile (Stack) et le Tas (Heap). (栈和堆。)
4. **Quelle est la direction de croissance de la pile ? / 栈的增长方向是什么？**
    * Vers les adresses décroissantes (vers le bas). (向低地址方向（向下）。)
5. **Quelle est la direction de croissance du tas ? / 堆的增长方向是什么？**
    * Vers les adresses croissantes (vers le haut). (向高地址方向（向上）。)
6. **Qui gère la taille de la pile ? / 谁管理栈的大小？**
    * Le système d'exploitation (fixée au démarrage, souvent 8 Mo). (操作系统（启动时固定，通常 8 Mo）。)
7. **Que contient une "couche" (stack frame) de la pile ? / 栈的一个“层”（栈帧）包含什么？**
    * Arguments, variables locales, adresse de retour, pointeur de frame précédent. (参数、局部变量、返回地址、前一帧指针。)
8. **Quand une couche de pile est-elle créée ? / 什么时候创建栈帧？**
    * À chaque appel de fonction. (每次函数调用时。)
9. **Quand une couche de pile est-elle détruite ? / 什么时候销毁栈帧？**
    * Au retour de la fonction. (函数返回时。)
10. **Quelle commande permet de voir/changer la taille de la pile ? / 哪个命令可以查看/更改栈大小？**
    * `ulimit -s`.
11. **Qu'est-ce qu'un "Stack Overflow" ? / 什么是 "Stack Overflow"（栈溢出）？**
    * Dépassement de la capacité allouée à la pile (récursion infinie, trop de variables locales). (超出栈的分配容量（无限递归，过多局部变量）。)
12. **Qui gère l'allocation dans le tas ? / 谁管理堆的分配？**
    * Le programme lui-même (via `malloc`/`free`). (程序自己（通过 `malloc`/`free`）。)
13. **Le tas est-il contigu en mémoire physique ? / 堆在物理内存中是连续的吗？**
    * Pas nécessairement (fragmentation, pagination). (不一定（碎片化，分页）。)
14. **Le tas est-il contigu en mémoire virtuelle ? / 堆在虚拟内存中是连续的吗？**
    * Généralement oui (du point de vue du programme). (通常是（从程序角度看）。)
15. **Quelle fonction alloue de la mémoire dans le tas ? / 哪个函数在堆中分配内存？**
    * `malloc` (ou `calloc`, `realloc`).
16. **Quelle fonction libère de la mémoire du tas ? / 哪个函数释放堆内存？**
    * `free`.
17. **Que se passe-t-il si on oublie de `free` ? / 如果忘记 `free` 会发生什么？**
    * Fuite de mémoire (Memory Leak). (内存泄漏。)
18. **Les variables locales sont-elles persistantes après le retour de la fonction ? / 函数返回后局部变量还持久存在吗？**
    * Non. (不存在。)
19. **La mémoire du tas est-elle persistante après le retour de la fonction qui l'a allouée ? / 函数返回后，其分配的堆内存还持久存在吗？**
    * Oui, tant qu'elle n'est pas libérée explicitement. (存在，直到显式释放。)
20. **Qu'est-ce que le "Text Segment" ? / 什么是 "Text Segment"（代码段）？**
    * La zone contenant le code exécutable (lecture seule). (包含可执行代码的区域（只读）。)

## III. Mémoire Virtuelle et MMU / 虚拟内存与 MMU (36-60)

1. **Qu'est-ce qu'une adresse logique (ou virtuelle) ? / 什么是逻辑地址（或虚拟地址）？**
    * L'adresse vue par le programme, relative à son espace d'adressage. (程序看到的地址，相对于其地址空间。)
2. **Qu'est-ce qu'une adresse physique ? / 什么是物理地址？**
    * L'adresse réelle en mémoire RAM (matériel). (RAM 中的真实地址。)
3. **Quel composant traduit l'adresse logique en physique ? / 哪个组件将逻辑地址转换为物理地址？**
    * MMU (Memory Management Unit).
4. **La MMU est-elle logicielle ou matérielle ? / MMU 是软件还是硬件？**
    * Matérielle. (硬件。)
5. **Quel est l'avantage principal de la mémoire virtuelle pour l'isolation ? / 虚拟内存对隔离的主要优势是什么？**
    * Chaque processus a son propre espace, sans accès à la mémoire des autres. (每个进程都有自己的空间，无法访问其他进程的内存。)
6. **Qu'est-ce que la "Pagination" ? / 什么是“分页”？**
    * Découpage de la mémoire en blocs de taille fixe. (将内存划分为固定大小的块。)
7. **Quelle est la taille typique d'une page ? / 页面的典型大小是多少？**
    * 4 Kio ($2^{12}$ octets).
8. **Comment appelle-t-on le bloc correspondant en mémoire physique ? / 物理内存中对应的块叫什么？**
    * Cadre de page (Page Frame). (页帧。)
9. **Une page virtuelle doit-elle toujours être en mémoire physique ? / 虚拟页必须一直在物理内存中吗？**
    * Non (Swap, ou pas encore allouée). (不（Swap，或尚未分配）。)
10. **Qu'est-ce qu'une "Page Fault" (Défaut de page) ? / 什么是 "Page Fault"（缺页异常）？**
    * Accès à une page qui n'est pas présente en mémoire physique (ou invalide). (访问不在物理内存中的（或无效的）页面。)
11. **Qui gère le défaut de page ? / 谁处理缺页异常？**
    * Le noyau du système d'exploitation. (操作系统内核。)
12. **Où le noyau stocke-t-il les pages évincées ? / 内核将置换出的页面存放在哪里？**
    * Dans l'espace d'échange (Swap) sur le disque. (磁盘上的交换空间。)
13. **Qu'est-ce que la "Table des pages" (Page Table) ? / 什么是“页表”？**
    * Structure de données stockant les correspondances Page $\rightarrow$ Frame. (存储页 $\rightarrow$ 帧映射的数据结构。)
14. **Où est stockée la table des pages (généralement) ? / 页表通常存储在哪里？**
    * En mémoire physique (RAM). (在物理内存中。)
15. **Quel est le problème des tables des pages à un seul niveau ? / 单级页表有什么问题？**
    * Elles seraient trop grandes (consomment trop de mémoire). (它们太大了（消耗太多内存）。)
16. **Quelle solution est utilisée pour réduire la taille des tables des pages ? / 用什么方案来减小页表大小？**
    * Tables des pages à niveaux multiples (Multi-level page tables). (多级页表。)
17. **Qu'est-ce que le TLB ? / TLB 是什么？**
    * Translation Lookaside Buffer. (转换后备缓冲区。)
18. **À quoi sert le TLB ? / TLB 有什么用？**
    * Cacher (cache) les traductions récentes pour accélérer l'accès mémoire. (缓存最近的转换以加速内存访问。)
19. **Où se trouve le TLB ? / TLB 在哪里？**
    * Dans le processeur (CPU) / MMU. (在处理器/MMU 中。)
20. **Que se passe-t-il en cas de "TLB Miss" ? / 发生 "TLB Miss" 会怎样？**
    * On doit parcourir la table des pages en mémoire (lent). (必须遍历内存中的页表（慢）。)
21. **Qu'est-ce que l'évincement (Swapping) ? / 什么是置换 (Swapping)？**
    * Déplacer des pages peu utilisées de la RAM vers le disque. (将不常用的页面从 RAM 移至磁盘。)
22. **Quel critère est souvent utilisé pour choisir la page à évincer ? / 通常使用什么标准来选择要置换的页面？**
    * LRU (Least Recently Used) ou approximations (temps de résidence, état). (最近最少使用或近似算法。)
23. **Comment voir l'utilisation du swap sous Linux ? / 如何在 Linux 下查看 swap 使用情况？**
    * `free -h`, `top`, ou `cat /proc/swaps`.
24. **Pourquoi le swap est-il lent ? / 为什么 swap 慢？**
    * Car l'accès disque est des milliers de fois plus lent que la RAM. (因为磁盘访问比 RAM 慢数千倍。)
25. **Qu'est-ce que l'OOM Killer ? / 什么是 OOM Killer？**
    * Mécanisme qui tue des processus quand il n'y a plus de mémoire ni de swap. (当没有内存和 swap 时杀死进程的机制。)

## IV. Allocation Dynamique / 动态分配 (61-80)

1. **Citez 3 types d'allocation mémoire. / 列举 3 种内存分配类型。**
    * Statique, Automatique (Pile), Dynamique (Tas). (静态，自动（栈），动态（堆）。)
2. **Pourquoi l'allocation bas niveau (mmap/sbrk) est-elle coûteuse ? / 为什么低级分配 (mmap/sbrk) 很昂贵？**
    * Car elle implique des appels système (passage mode noyau). (因为它涉及系统调用（切换内核模式）。)
3. **Comment l'allocateur haut niveau (malloc) optimise-t-il les appels système ? / 高级分配器 (malloc) 如何优化系统调用？**
    * Il demande de gros blocs au noyau et gère lui-même les petites découpes. (它向内核申请大块内存，自己管理小块切分。)
4. **Qu'est-ce que la fragmentation interne ? / 什么是内部碎片？**
    * Espace perdu *à l'intérieur* d'un bloc alloué (ex: bloc de 64o pour 50o de données). (已分配块*内部*的浪费空间。)
5. **Qu'est-ce que la fragmentation externe ? / 什么是外部碎片？**
    * Espace libre morcelé en petits trous non contigus. (空闲空间被分割成不连续的小洞。)
6. **Citez une stratégie d'allocation (fit). / 列举一种分配策略。**
    * First Fit (Premier trouvé), Best Fit (Mieux ajusté). (首次适应，最佳适应。)
7. **Que fait `calloc` par rapport à `malloc` ? / `calloc` 相比 `malloc` 做什么？**
    * Il initialise la mémoire allouée à zéro. (它将分配的内存初始化为零。)
8. **Que fait `realloc` ? / `realloc` 做什么？**
    * Change la taille d'un bloc alloué (peut le déplacer si nécessaire). (更改已分配块的大小（如有必要可能会移动它）。)
9. **Quelle est l'unité minimale d'allocation pour le noyau ? / 内核的最小分配单位是什么？**
    * Une page (4 Kio). (一页。)
10. **Un malloc(10) consomme-t-il seulement 10 octets ? / malloc(10) 只消耗 10 字节吗？**
    * Non, il y a un surcoût pour les métadonnées de l'allocateur (header). (不，有分配器元数据的开销。)
11. **Est-ce que `free` rend toujours la mémoire à l'OS ? / `free` 总是把内存还给操作系统吗？**
    * Non, souvent elle est marquée "libre" pour de futurs `malloc` du même processus. (不，通常标记为“空闲”供同一进程后续 `malloc` 使用。)
12. **Qu'est-ce qu'une "Segmentation Fault" (Segfault) ? / 什么是“段错误”？**
    * Accès illégal à une adresse mémoire (hors segments valides). (非法访问内存地址。)
13. **Accéder à l'adresse 0 (NULL) provoque quoi ? / 访问地址 0 (NULL) 会引发什么？**
    * Segfault.
14. **Pourquoi l'allocation sur la pile est-elle plus rapide que sur le tas ? / 为什么栈分配比堆分配快？**
    * Juste un déplacement de registre (SP), pas de recherche de bloc libre. (只是移动寄存器 (SP)，无需搜索空闲块。)
15. **Jusqu'à quand une variable statique reste-t-elle en mémoire ? / 静态变量在内存中保留多久？**
    * Toute la durée de vie du programme. (程序的整个生命周期。)
16. **Où sont stockées les chaînes littérales (ex: "Bonjour") ? / 字面字符串（如 "Bonjour"）存储在哪里？**
    * Dans une section de données en lecture seule (souvent `.rodata`). (在只读数据段。)
17. **Peut-on modifier une chaîne littérale ? / 可以修改字面字符串吗？**
    * Non -> Segfault. (不行 -> 段错误。)
18. **L'OS peut-il refuser un malloc ? / 操作系统可以拒绝 malloc 吗？**
    * Oui, s'il n'y a plus de mémoire (retourne NULL). (可以，如果没有内存（返回 NULL）。)
19. **Qu'est-ce que l'overcommit ? / 什么是 overcommit？**
    * L'OS promet plus de mémoire qu'il n'en a physiquement, pariant que tout ne sera pas utilisé. (操作系统承诺比物理内存更多的内存，赌所有内存不会被全部使用。)
20. **Quelle commande permet de tracer les appels mémoire (`malloc`/`free`) ? / 哪个命令可以跟踪内存调用？**
    * `ltrace` (appels bibliothèque) ou `strace` (appels système `brk`/`mmap`). (`ltrace`（库调用）或 `strace`（系统调用）。)

## V. Partage de Mémoire et Copy-On-Write / 内存共享与写时复制 (81-100)

1. **Deux processus peuvent-ils partager la même page physique ? / 两个进程可以共享同一个物理页吗？**
    * Oui. (可以。)
2. **Quel segment est partagé par défaut entre processus exécutant le même programme ? / 执行相同程序的进程默认共享哪个段？**
    * Le segment de texte (Code). (代码段。)
3. **Que signifie COW ? / COW 是什么意思？**
    * Copy-On-Write. (写时复制。)
4. **Lors d'un `fork()`, la mémoire est-elle immédiatement copiée ? / `fork()` 时内存是立即复制的吗？**
    * Non, les pages sont marquées en lecture seule et partagées. (不，页面标记为只读并共享。)
5. **Quand la copie réelle a-t-elle lieu avec COW ? / COW 的实际复制发生在什么时候？**
    * Lorsqu'un des processus (père ou fils) tente d'**écrire** dans une page. (当任一进程试图**写入**页面时。)
6. **Quel est l'avantage du COW pour `fork()` suivi de `exec()` ? / 对于 `fork()` 后跟 `exec()`，COW 的优势是什么？**
    * On évite de copier tout l'espace mémoire inutilement avant de l'écraser. (避免在覆盖之前不必要地复制整个内存空间。)
7. **Les threads partagent-ils le segment de données (Tas) ? / 线程共享数据段（堆）吗？**
    * Oui, par définition. (是的，根据定义。)
8. **Les processus partagent-ils le segment de données ? / 进程共享数据段吗？**
    * Non (sauf mémoire partagée explicite). (不（除非显式共享内存）。)
9. **Comment créer explicitement une zone mémoire partagée entre processus ? / 如何在进程间显式创建共享内存区域？**
    * Via `mmap` (avec `MAP_SHARED`) ou `shmget`. (通过 `mmap` 或 `shmget`。)
10. **Si un thread modifie un pointeur sur le tas, les autres threads voient-ils le changement ? / 如果一个线程修改了堆上的指针，其他线程能看到变化吗？**
    * Oui. (能。)
11. **Dans l'exemple du cours, après un `fork`, si le fils modifie `val`, `val` change-t-il pour le père ? / 课程示例中，`fork` 后如果子进程修改 `val`，父进程的 `val` 会变吗？**
    * Non (COW a créé une copie pour le fils). (不会（COW 为子进程创建了副本）。)
12. **Dans l'exemple du cours avec `pthread`, si un thread modifie `val` (passé par pointeur), change-t-il pour le main ? / 课程示例中用 `pthread`，如果线程修改 `val`（通过指针传递），main 中的会变吗？**
    * Oui (même adresse physique). (会（物理地址相同）。)
13. **Que montre l'adresse des variables dans les threads ? / 线程中变量地址显示了什么？**
    * Elles sont identiques. (它们是相同的。)
14. **Quelle primitive de synchronisation est nécessaire pour protéger la mémoire partagée ? / 保护共享内存需要什么同步原语？**
    * Mutex (ou Sémaphore). (互斥锁（或信号量）。)
15. **Le noyau partage-t-il sa mémoire avec les processus utilisateurs ? / 内核与用户进程共享内存吗？**
    * Non, mais il est souvent mappé dans la partie haute de l'espace virtuel (mais inaccessible en mode utilisateur). (不，但它通常映射在虚拟空间的高端（但在用户模式下不可访问）。)
16. **Que se passe-t-il si deux threads écrivent au même endroit sans protection ? / 如果两个线程无保护地写入同一位置会发生什么？**
    * Race Condition (Indéterminisme). (竞争条件。)
17. **Le code des bibliothèques partagées (.so) est-il dupliqué en mémoire physique pour chaque processus ? / 共享库 (.so) 的代码在物理内存中为每个进程复制吗？**
    * Non, une seule copie physique est partagée par tous. (不，所有人共享一份物理副本。)
18. **Qu'est-ce que `gettid()` ? / 什么是 `gettid()`？**
    * Retourne l'identifiant du thread (Thread ID). (返回线程 ID。)
19. **Pourquoi l'adresse affichée par `printf` est-elle une adresse virtuelle ? / 为什么 `printf` 显示的地址是虚拟地址？**
    * Car le programme ne voit que son espace virtuel. (因为程序只能看到它的虚拟空间。)
20. **Comment savoir si deux processus partagent physiquement de la mémoire ? / 如何知道两个进程是否物理共享内存？**
    * Difficile depuis l'espace utilisateur, mais on peut inspecter `/proc/[pid]/maps` ou `smaps`. (在用户空间很难，但可以检查 .../maps。)
