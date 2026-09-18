# 100 Questions de révision - Lecture 1 : Architecture interne des systèmes d'exploitation 100 道复习题 - 第一讲：操作系统内部体系结构

1. **Comment programmables-t-on l'ordinateur ENIAC ? / 如何对 ENIAC 计算机进行编程？**
    * Par câblage manuel des unités. (通过手工布线。)
2. **L'ENIAC avait-il un système d'exploitation ? / ENIAC 有操作系统吗？**
    * Non. (没有。)
3. **Quelle innovation a permis l'automatisation du passage d'un programme à l'autre ? / 哪项创新使得程序间的自动切换成为可能？**
    * Le système de traitement par lots (Batch processing) avec un moniteur résident. (带有驻留监控程序的批处理系统。)
4. **Quel est l'objectif principal de la multiprogrammation ? / 多道程序设计的主要目标是什么？**
    * Optimiser l'utilisation du CPU en réduisant les temps morts lors des E/S. (通过减少 I/O 期间的空闲时间来优化 CPU 利用率。)
5. **Qu'est-ce que le "Spooling" ? / 什么是 "Spooling"（假脱机）？**
    * Le pré-chargement des programmes depuis les cartes vers le disque pour découpler l'E/S du CPU. (将程序从卡片预加载到磁盘，以解耦 I/O 和 CPU。)
6. **Quel problème majeur le Spooling et la multiprogrammation ont-ils introduit ? / Spooling 和多道程序设计引入了哪个主要问题？**
    * Le besoin de partage des ressources et de gestion de la concurrence. (资源共享和并发管理的需求。)
7. **Qu'est-ce que le "Temps Partagé" (Time Sharing) ? / 什么是“分时”系统？**
    * Partager le temps processeur en petits quantums pour servir plusieurs utilisateurs simultanément. (将处理器时间分成小的时间片，同时服务多个用户。)
8. **Quel est l'ordre de grandeur typique d'un quantum de temps ? / 一个典型的时间片大概是多长？**
    * Environ 20 ms. (大约 20 毫秒。)
9. **Quel composant matériel est indispensable pour reprendre le contrôle à la fin d'un quantum ? / 在时间片结束时收回控制权必不可少的硬件组件是什么？**
    * Une horloge avec interruptions (Timer). (带有中断功能的时钟/定时器。)
10. **Quelles sont les 3 étapes pour mettre en place le temps partagé ? / 实施分时系统的 3 个步骤是什么？**
    * Interruption horloge, Gestion utilisateurs (Login/UID), Sécurité (Modes d'exécution). (时钟中断，用户管理，安全机制。)
11. **Quels sont les deux modes d'exécution du processeur utilisés par l'OS ? / 操作系统使用的两种处理器执行模式是什么？**
    * Mode privilégié (Noyau) et Mode non-privilégié (Utilisateur). (特权模式/内核态，非特权模式/用户态。)
12. **Qui s'exécute en mode privilégié ? / 谁在特权模式下运行？**
    * Le noyau du système d'exploitation. (操作系统内核。)
13. **Comment une application demande-t-elle un service au noyau ? / 应用程序如何向内核请求服务？**
    * Via un appel système. (通过系统调用。)
14. **Quels sont les 5 rôles majeurs d'un OS ? / 操作系统的 5 个主要角色是什么？**
    * Rentabiliser l'usage, Partager les ressources, Offrir une interface, Permettre le développement, Garantir la sécurité. (提高效率，共享资源，提供接口，支持开发，保障安全。)
15. **Quelles ressources l'OS doit-il partager équitablement ? / 操作系统必须公平分配哪些资源？**
    * CPU, Mémoire, Disque, Réseau. (CPU，内存，磁盘，网络。)

16. **Citez 4 abstractions principales fournies par l'OS. / 列出操作系统提供的 4 个主要抽象。**
    * Processus, Fichier, Utilisateur, Communication (Socket/Pipe/Signal). (进程，文件，用户，通信。)
17. **Quelle est la philosophie d'UNIX résumée en une phrase ? / 用一句话概括 UNIX 的哲学？**
    * "Tout est fichier" (Everything is a file) et "KISS" (Keep It Simple, Stupid). (“一切皆文件”和“保持简单”。)
18. **En quels langages UNIX est-il principalement écrit ? / UNIX 主要用什么语言编写？**
    * C et Assembleur. (C 语言和汇编语言。)
19. **Qu'est-ce qu'un fichier sous UNIX ? / 在 UNIX 中什么是文件？**
    * Une suite d'octets sans structure interne imposée. (没有强制内部结构的字节序列。)
20. **Citez une norme standardisant les systèmes UNIX. / 列举一个标准化 UNIX 系统的规范。**
    * POSIX (IEEE Std 1003.1). (POSIX。)
21. **Qu'est-ce que "KISS" signifie dans le contexte UNIX ? / 在 UNIX 语境下 "KISS" 是什么意思？**
    * Des outils simples qui font une seule chose bien. (只做一件事并把它做好的简单工具。)
22. **Donnez un exemple d'appel système de gestion de fichier. / 举一个文件管理系统调用的例子。**
    * `open`, `read`, `write`, `close`.
23. **Donnez un exemple d'appel système de gestion d'identité. / 举一个身份管理系统调用的例子。**
    * `getuid`.
24. **Quelle famille de systèmes domine le calcul haute performance ? / 哪个系统家族在高性能计算领域占主导地位？**
    * GNU/Linux.
25. **À quoi servent les sections du manuel `man` ? / `man` 手册的各个章节有什么用？**
    * Organiser les pages par type (ex: 1=Commandes, 2=Appels système, 3=Bibliothèques). (按类型组织页面，如 1=命令，2=系统调用，3=库函数。)

26. **Que signifie TTY ? / TTY 是什么意思？**
    * Teletype (Télétype). (电传打字机。)
27. **Quelle est la différence entre un TTY physique et un PTY ? / 物理 TTY 和 PTY 有什么区别？**
    * TTY est lié au matériel/console, PTY est émulé par logiciel (ex: ssh, xterm). (TTY 与硬件/控制台相关，PTY 由软件模拟。)
28. **Quels sont les fichiers de périphériques associés à un PTY ? / 与 PTY 关联的设备文件有哪些？**
    * Maître (`/dev/ptmx`) et Esclave (`/dev/pts/N`). (主端 `/dev/ptmx` 和 从端 `/dev/pts/N`。)
29. **Comment accéder à une console virtuelle sous Linux ? / 如何在 Linux 下访问虚拟控制台？**
    * Ctrl + Alt + Fx (ex: F1, F2...).
30. **À quoi sert le Shell ? / Shell 有什么用？**
    * Lire, interpréter et exécuter des commandes. (读取、解释和执行命令。)
31. **Qu'est-ce qu'une commande interne (builtin) au Shell ? / 什么是 Shell 的内置命令（builtin）？**
    * Une commande exécutée directement par le processus Shell (ex: `cd`, `alias`), pas un binaire externe. (由 Shell 进程直接执行的命令，不是外部二进制文件。)
32. **À quoi sert la variable `PATH` ? / 变量 `PATH` 有什么用？**
    * Lister les répertoires où chercher les exécutables. (列出查找可执行文件的目录。)
33. **Quelle commande permet de savoir où se trouve un exécutable ? / 哪个命令可以查找可执行文件的位置？**
    * `which`.
34. **Que fait la commande `mkdir -p` ? / 命令 `mkdir -p` 做什么？**
    * Crée un dossier et ses parents s'ils n'existent pas. (创建目录及其父目录（如果不存在）。)
35. **Quelle est la différence entre `echo` et `cat` ? / `echo` 和 `cat` 有什么区别？**
    * `echo` affiche ses arguments, `cat` affiche le contenu d'un fichier. (`echo` 显示其参数，`cat` 显示文件内容。)
36. **Quelle commande permet de changer les droits d'un fichier ? / 哪个命令用于更改文件权限？**
    * `chmod`.
37. **À quoi sert `grep` ? / `grep` 有什么用？**
    * Recherche textuelle (expressions régulières). (文本搜索（正则表达式）。)
38. **Comment enchaîner la sortie d'une commande vers l'entrée d'une autre ? / 如何将一个命令的输出链接到另一个命令的输入？**
    * Avec un tube (Pipe `|`). (使用管道 `|`。)
39. **Quelle commande affiche les processus de tous les utilisateurs ? / 哪个命令显示所有用户的进程？**
    * `ps -aux` (ou `ps -ef`).
40. **Que contient `argv[argc]` dans la fonction main ? / main 函数中的 `argv[argc]` 包含什么？**
    * `NULL`.

41. **Définissez un processus. / 定义一个进程。**
    * Instance d'un programme en exécution avec sa propre mémoire et ressources. (具有自己内存和资源的正在运行的程序实例。)
42. **Qu'est-ce qu'un PID ? / 什么是 PID？**
    * Process Identifier (Identifiant unique de processus). (进程标识符。)
43. **Un processus peut-il avoir plusieurs parents ? / 一个进程可以有多个父进程吗？**
    * Non, un seul parent (PPID). (不行，只有一个父进程。)
44. **Que partage un processus fils avec son père après un `fork()` ? / `fork()` 后子进程与父进程共享什么？**
    * Les descripteurs de fichiers ouverts (et le code en lecture seule, via COW). (打开的文件描述符，以及只读代码（通过写时复制）。)
45. **Quelle est la valeur de retour de `fork()` pour le père ? / `fork()` 对父进程的返回值是什么？**
    * Le PID du fils. (子进程的 PID。)
46. **Quelle est la valeur de retour de `fork()` pour le fils ? / `fork()` 对子进程的返回值是什么？**
    * 0.
47. **Que se passe-t-il si `fork()` retourne -1 ? / 如果 `fork()` 返回 -1 会发生什么？**
    * Erreur, pas de processus créé. (错误，未创建进程。)
48. **Comment les espaces mémoire du père et du fils sont-ils liés après un fork ? / fork 后父子进程的内存空间有什么关系？**
    * Ils sont distincts (copiés), les modifications de l'un n'affectent pas l'autre. (它们是独立的（复制的），一方的修改不会影响另一方。)
49. **Quelle fonction permet de remplacer le programme courant par un autre ? / 哪个函数允许用另一个程序替换当前程序？**
    * Une fonction de la famille `exec` (ex: `execvp`). (`exec` 系列函数。)
50. **Lorsqu'on appelle `execvp`, le PID change-t-il ? / 调用 `execvp` 时，PID 会改变吗？**
    * Non. (不会。)
51. **À quoi sert `wait()` ? / `wait()` 有什么用？**
    * Attendre la fin d'un processus fils et récupérer son état. (等待子进程结束并获取其状态。)
52. **Qu'est-ce qu'un processus zombie ? / 什么是僵尸进程？**
    * Un processus terminé dont le père n'a pas encore fait `wait()`. (一个已结束但父进程尚未对其执行 `wait()` 的进程。)
53. **Quel est le premier processus lancé par le noyau (PID 1) ? / 内核启动的第一个进程（PID 1）是什么？**
    * `init` ou `systemd`.
54. **Quelle commande affiche l'arbre des processus ? / 哪个命令显示进程树？**
    * `pstree`.
55. **Où sont stockées les variables locales d'une fonction dans un processus ? / 进程中函数的局部变量存储在哪里？**
    * Sur la pile (Stack). (在栈上。)
56. **Où est stocké le code du programme ? / 程序代码存储在哪里？**
    * Dans le segment de texte (Text segment). (在代码段。)
57. **Où sont stockées les allocations dynamiques (`malloc`) ? / 动态分配 (`malloc`) 存储在哪里？**
    * Sur le tas (Heap). (在堆上。)
58. **Comment un shell lance-t-il une commande externe ? / Shell 如何启动外部命令？**
    * Il fait `fork()`, puis `exec()` dans le fils, et `wait()` dans le père. (它执行 `fork()`，然后在子进程中执行 `exec()`，父进程执行 `wait()`。)
59. **Comment lancer un processus en arrière-plan ? / 如何在后台启动进程？**
    * Ajouter `&` à la fin de la commande. (在命令末尾添加 `&`。)
60. **Quelle commande liste les tâches de fond du shell courant ? / 哪个命令列出当前 Shell 的后台任务？**
    * `jobs`.
61. **Qu'affiche `getppid()` ? / `getppid()` 显示什么？**
    * Le PID du parent. (父进程的 PID。)
62. **Si le père meurt avant le fils, qui devient le nouveau parent du fils ? / 如果父进程在子进程之前死亡，谁成为子进程的新父进程？**
    * Le processus `init` / `systemd` (PID 1) (ou un "subreaper").
63. **`execvp` retourne-t-il si tout se passe bien ? / 如果一切正常，`execvp` 会返回吗？**
    * Non, jamais. (不，永远不会。)
64. **Quel est l'avantage du Copy-On-Write lors d'un fork ? / fork 时写时复制（COW）的优势是什么？**
    * Économiser la mémoire et accélérer la création en ne copiant les pages que si elles sont modifiées. (通过仅在修改页面时才复制来节省内存并加速创建。)
65. **Peut-on partager des variables globales entre deux processus sans IPC ? / 不使用 IPC，两个进程可以共享全局变量吗？**
    * Non, mémoire séparée. (不能，内存是分开的。)

66. **Définissez un Thread. / 定义一个线程。**
    * Flux d'exécution au sein d'un processus. (进程内的执行流。)
67. **Quelle est la différence majeure mémoire entre Processus et Thread ? / 进程和线程在内存方面的主要区别是什么？**
    * Les threads partagent le même espace d'adressage (Tas, Globales), les processus non. (线程共享相同的地址空间（堆、全局变量），进程不共享。)
68. **Les threads partagent-ils la pile (Stack) ? / 线程共享栈吗？**
    * Non, chaque thread a sa propre pile. (不，每个线程都有自己的栈。)
69. **Quelle bibliothèque standard est utilisée pour les threads sous Linux ? / Linux 下使用哪个标准库进行各线程操作？**
    * POSIX Threads (`pthreads`).
70. **Quelle fonction crée un thread ? / 哪个函数创建线程？**
    * `pthread_create`.
71. **Quelle fonction attend la fin d'un thread ? / 哪个函数等待线程结束？**
    * `pthread_join`.
72. **Si un thread modifie une variable globale, les autres le voient-ils ? / 如果一个线程修改了全局变量，其他线程能看到吗？**
    * Oui. (能。)
73. **Qu'est-ce qu'un TID ? / 什么是 TID？**
    * Thread Identifier. (线程标识符。)
74. **Les threads partagent-ils les fichiers ouverts ? / 线程共享打开的文件吗？**
    * Oui. (共享。)
75. **La création d'un thread est-elle plus ou moins coûteuse que celle d'un processus ? / 创建线程比创建进程开销大还是小？**
    * Moins coûteuse (pas de copie de table des pages etc.). (开销小（无需复制页表等）。)
76. **Comment passer des arguments à un thread lors de sa création ? / 创建线程时如何传递参数？**
    * Via le 4ème argument `void *arg` de `pthread_create`. (通过 `pthread_create` 的第 4 个参数 `void *arg`。)
77. **Quel est le risque principal avec les variables partagées entre threads ? / 线程间共享变量的主要风险是什么？**
    * Les accès concurrents (Race conditions) nécessitant de la synchronisation. (需要同步的并发访问（竞争条件）。)

78. **Qu'est-ce qu'un signal ? / 什么是信号？**
    * Une interruption logicielle asynchrone. (异步软件中断。)
79. **Que fait le signal SIGINT ? / 信号 SIGINT 做什么？**
    * Interruption (généralement Ctrl+C). (中断（通常是 Ctrl+C）。)
80. **Que fait le signal SIGKILL ? / 信号 SIGKILL 做什么？**
    * Terminaison forcée immédiate. (立即强制终止。)
81. **Peut-on ignorer SIGKILL ? / 可以忽略 SIGKILL 吗？**
    * Non. (不能。)
82. **Quel signal est envoyé lors d'une erreur de segmentation ? / 发生段错误时发送哪个信号？**
    * `SIGSEGV`.
83. **Quel signal est envoyé lorsqu'un processus fils se termine ? / 子进程结束时发送哪个信号？**
    * `SIGCHLD`.
84. **Quelle fonction POSIX permet de gérer proprement les signaux ? / 哪个 POSIX 函数用于正确处理信号？**
    * `sigaction`.
85. **Quelle est la différence entre `signal()` (ancien) et `sigaction()` ? / `signal()`（旧）和 `sigaction()` 有什么区别？**
    * `sigaction` est plus portable et permet de définir des masques et drapeaux (`sa_mask`, `sa_flags`). (`sigaction` 可移植性更好，并允许定义掩码和标志。)
86. **Qu'est-ce que `sa_mask` ? / `sa_mask` 是什么？**
    * L'ensemble des signaux bloqués pendant l'exécution du gestionnaire. (处理程序执行期间阻塞的信号集合。)
87. **Comment envoyer un signal à un processus depuis le shell ? / 如何从 Shell 向进程发送信号？**
    * Commande `kill`.
88. **Comment un processus peut-il s'envoyer un signal à lui-même ? / 进程如何向自己发送信号？**
    * Fonction `raise()` ou `kill(getpid(), sig)`.
89. **À quoi sert `sigprocmask` ? / `sigprocmask` 有什么用？**
    * Bloquer ou débloquer des signaux pour le processus entier (section critique). (为整个进程阻塞或解除阻塞信号（临界区）。)
90. **À quoi sert `alarm(n)` ? / `alarm(n)` 有什么用？**
    * Envoyer `SIGALRM` au processus dans `n` secondes. (在 `n` 秒后向进程发送 `SIGALRM`。)
91. **Que fait `pause()` ? / `pause()` 做什么？**
    * Met le processus en sommeil jusqu'à l'arrivée d'un signal. (使进程休眠直到接收到信号。)
92. **Qu'est-ce que `SIGPIPE` ? / 什么是 `SIGPIPE`？**
    * Écriture dans un tube/socket fermé par le lecteur. (写入读取端已关闭的管道/套接字。)
93. **Qu'est-ce que `SIGWINCH` ? / 什么是 `SIGWINCH`？**
    * Changement de taille de la fenêtre terminal. (终端窗口大小改变。)
94. **Que se passe-t-il par défaut si on reçoit un signal non géré ? / 如果收到未处理的信号，默认会发生什么？**
    * Souvent la terminaison du processus (ou ignore, ou core dump selon le signal). (通常是进程终止（或忽略，或核心转储，取决于信号）。)
95. **Comment annuler une alarme en cours ? / 如何取消正在进行的闹钟？**
    * `alarm(0)`.

96. **Que signifie "daemons" dans `ps` ? / `ps` 中的 "daemons" 是什么意思？**
    * Processus d'arrière-plan sans terminal (services système). (无终端的后台进程（系统服务）。)
97. **À quoi sert `Ctrl+Z` dans un terminal ? / 终端中的 `Ctrl+Z` 有什么用？**
    * Envoie `SIGTSTP` pour suspendre le processus (Stop). (发送 `SIGTSTP` 以挂起进程。)
98. **Comment reprendre un processus suspendu en arrière-plan ? / 如何在后台恢复挂起的进程？**
    * Commande `bg`.
99. **Comment reprendre un processus suspendu en avant-plan ? / 如何在前台恢复挂起的进程？**
    * Commande `fg`.
100. **Quelle commande permet de voir la documentation d'un appel système ? / 哪个命令用于查看系统调用的文档？**
    * `man 2 <nom>`.

101. **Quels fichiers de périphériques représentent la console système et les consoles virtuelles ? / 系统控制台与虚拟控制台的设备文件是哪些？**
    * `/dev/console` pour la console système, `/dev/tty0` pour la console active, `/dev/tty1`-`/dev/tty6` pour les consoles virtuelles. (系统控制台 `/dev/console`，活动控制台 `/dev/tty0`，虚拟控制台 `/dev/tty1`-`/dev/tty6`。)
102. **Que représente `/dev/ttyS*` ? / `/dev/ttyS*` 表示什么？**
    * Les terminaux série (ports série classiques). (传统串口终端设备。)
103. **Pourquoi les PTY sont-ils indispensables pour `ssh` et les émulateurs de terminal ? / PTY 为什么对 ssh 和终端仿真器必不可少？**
    * Ils fournissent un comportement TTY au-dessus d'un canal logiciel (echo, modes canoniques, signaux) sans matériel physique. (在无物理终端时提供 TTY 语义：回显、规范模式、信号等。)
104. **Quelle est la différence fonctionnelle entre `/dev/ptmx` et `/dev/pts/N` ? / `/dev/ptmx` 与 `/dev/pts/N` 的功能差异？**
    * `/dev/ptmx` est le maître (allocation d'une paire PTY), `/dev/pts/N` est l'esclave utilisé par le shell. (`/dev/ptmx` 是主端用于分配，`/dev/pts/N` 是从端供 shell 使用。)

105. **Que contient `envp` dans `main(int argc, char **argv, char **envp)` ? / `envp` 包含什么？**
    * La liste des variables d'environnement sous forme `KEY=VALUE`, terminée par `NULL`. (环境变量列表 `KEY=VALUE`，以 `NULL` 结尾。)
106. **Quelle différence entre `execv`, `execvp` et `execve` ? / `execv`、`execvp`、`execve` 有何区别？**
    * `execv` prend un chemin explicite, `execvp` cherche dans `PATH`, `execve` permet de fournir un `envp`. (`execv` 需绝对/相对路径，`execvp` 查 `PATH`，`execve` 可传自定义环境。)
107. **Pourquoi `exec` ne retourne-t-il pas en cas de succes ? / 为什么 `exec` 成功时不返回？**
    * Il remplace l'image mémoire du processus courant. (因为直接替换当前进程的内存映像。)
108. **Dans une sequence `fork` + `exec` + `wait`, a quel moment le PID change-t-il ? / 在 `fork`+`exec`+`wait` 中 PID 何时改变？**
    * Au `fork` (nouveau PID pour le fils). `exec` conserve le PID du fils. (`fork` 创建子进程 PID，`exec` 不改变 PID。)

109. **Expliquez ce que signifie "pending" pour un signal bloque. / 说明被阻塞信号的 "pending" 含义。**
    * Le signal est en attente de livraison tant qu'il est bloque. (信号已到达但被挂起，待解阻后投递。)
110. **Pourquoi combiner `sigpending` et `sigsuspend` ? / 为什么组合使用 `sigpending` 与 `sigsuspend`？**
    * Pour detecter un signal en attente puis l'autoriser temporairement a etre livre en attendant. (先检查待处理信号，再临时放开掩码等待其投递。)
111. **Que se passe-t-il si un signal bloque arrive plusieurs fois ? / 同一被阻塞信号多次到达会怎样？**
    * Un seul signal peut rester en attente (non-queue) pour la plupart des signaux standards. (标准信号通常不排队，只保留一个 pending。)

112. **Quel risque cree un `fork()` sans `wait()` dans le parent ? / 父进程 `fork()` 后不 `wait()` 的风险？**
    * Creation de processus zombies. (产生僵尸进程。)
113. **Expliquez un scenario ou un zombie apparait. / 给出僵尸产生的场景解释。**
    * Le fils se termine, mais le pere n'appelle jamais `wait()`, son etat reste dans la table des processus. (子进程结束而父进程不回收，状态残留进程表。)
114. **Pourquoi une variable globale n'est-elle pas partagee entre deux processus apres `fork()` ? / 为什么 `fork()` 后全局变量不共享？**
    * Chaque processus a son propre espace d'adressage (copie logique avec COW). (进程地址空间独立，写时复制只在写时复制页。)
115. **Comparez un thread et un processus pour le partage de la memoire. / 比较线程与进程的内存共享。**
    * Threads partagent heap/globales, processus non; chaque thread garde sa pile. (线程共享堆/全局变量，进程不共享；线程各自有栈。)
116. **Donnez un exemple de condition de course simple. / 给出一个简单竞争条件示例。**
    * Deux threads incrementent une variable globale sans verrou, resultat imprevisible. (两个线程无锁递增全局变量，结果不确定。)

117. **Que represente le mode privilegie pour le noyau ? / 内核的特权模式意味着什么？**
    * Acces complet au materiel et aux ressources, execution protegee. (完全硬件访问与受保护执行。)
118. **Quel est l'objectif principal du noyau dans la gestion des ressources ? / 内核在资源管理中的主要目标？**
    * Partage equitable et securise des ressources (CPU, memoire, I/O). (公平且安全地共享资源。)
119. **Comment relier "tout est fichier" aux peripheriques TTY ? / "万物皆文件" 如何体现在 TTY 设备上？**
    * Les terminaux sont exposes comme fichiers dans `/dev`, accessibles via des descripteurs. (终端以 `/dev` 下文件形式呈现，可用文件描述符访问。)
120. **Pourquoi l'abstraction "fichier" simplifie-t-elle l'I/O ? / 文件抽象为何简化 I/O？**
    * Une interface unique (open/read/write/close) pour des supports differents. (统一接口处理不同设备。)

121. **Expliquez la difference entre TTY physique, console virtuelle et PTY. / 解释物理 TTY、虚拟控制台与 PTY 的区别。**
    * TTY physique lie au materiel, console virtuelle est un TTY local multiplexe, PTY est un TTY logiciel emule. (物理硬件终端、虚拟控制台为本地多路复用、PTY 为软件仿真。)
122. **Pourquoi le shell doit-il parfois etre un processus parent ? / 为什么 shell 常作为父进程？**
    * Il lance les commandes via `fork()` puis `wait()` pour gerer le cycle de vie. (通过 `fork()`+`wait()` 管理子进程生命周期。)
123. **Dans `ps`, que signifie une commande sans TTY ? / `ps` 中无 TTY 的进程意味着什么？**
    * Un service/daemon detache du terminal. (无终端后台服务/守护进程。)
124. **Quelle difference entre `SIGTERM` et `SIGKILL` en pratique ? / `SIGTERM` 与 `SIGKILL` 的实际区别？**
    * `SIGTERM` peut etre intercepte pour arret propre, `SIGKILL` termine immediatement. (`SIGTERM` 可被处理以优雅退出，`SIGKILL` 立即终止。)
125. **Donnez un exemple de scenario ou `SIGPIPE` survient. / 举例说明 `SIGPIPE` 触发场景。**
    * Un processus ecrit dans un tube dont le lecteur a ferme sa fin. (向读端已关闭的管道写入。)

126. **Quelle sortie produit ce programme ? / 该程序输出什么？**

    ```c
    int main(void) {
        printf("A");
        printf("B");
        printf("\n");
        return 0;
    }
    
    ```
    * `AB` (sur une seule ligne). (`AB` 同一行。)

127. **Quelle sortie produit ce programme ? / 该程序输出什么？**

    ```c
    int main(void) {
        printf("X");
        fork();
        printf("Y\n");
        return 0;
    }
    
    ```

    * Deux lignes contenant `XY` (ordre indetermine). (两行 `XY`，顺序不定。)
128. **Quelle sortie possible pour ce programme ? / 给出该程序的一种可能输出。**

    ```c
    int main(void) {
        pid_t c = fork();
        if (c == 0) {
            printf("C\n");
        } else {
            printf("P\n");
        }
        return 0;
    }
    
    ```
    * Soit `C` puis `P`, soit `P` puis `C`. (可能是 C 后 P，或 P 后 C。)
129. **Quelle sortie produit ce programme ? / 该程序输出什么？**

    ```c
    int main(void) {
        pid_t c = fork();
        if (c == 0) {
            printf("child\n");
        } else {
            wait(NULL);
            printf("parent\n");
        }
        return 0;
    }
    
    ```
    * `child` puis `parent`. (`child` 后 `parent`。)
130. **Quelle sortie possible pour ce programme ? / 该程序可能输出什么？**

    ```c
    int main(void) {
        pid_t c = fork();
        if (c == 0) {
            printf("1");
        } else {
            printf("2");
        }
        return 0;
    }
    
    ```

    * `12` ou `21` (sans retour ligne). (`12` 或 `21`（无换行）。)
131. **Quelle sortie produit ce programme ? / 该程序输出什么？**

    ```c
    int main(void) {
        int x = 1;
        pid_t c = fork();
        if (c == 0) {
            x += 1;
            printf("C %d\n", x);
        } else {
            x += 2;
            wait(NULL);
            printf("P %d\n", x);
        }
        return 0;
    }
    
    ```

    * `C 2` puis `P 3`. (`C 2` 后 `P 3`。)
132. **Quelle sortie produit ce programme ? / 该程序输出什么？**

    ```c
    int main(void) {
        int x = 1;
        pid_t c = fork();
        if (c == 0) {
            x += 5;
            printf("C %d\n", x);
        } else {
            printf("P %d\n", x);
        }
        return 0;
    }
    
    ```

    * Deux lignes: `C 6` et `P 1` (ordre indetermine). (两行 `C 6` 和 `P 1`，顺序不定。)
133. **Quelle sortie produit ce programme ? / 该程序输出什么？**

    ```c
    void *work(void *arg) {
        printf("T\n");
        return NULL;
    }
    int main(void) {
        pthread_t t;
        pthread_create(&t, NULL, work, NULL);
        pthread_join(t, NULL);
        printf("M\n");
        return 0;
    }
    
    ```

    * `T` puis `M` (deux lignes). (`T` 后 `M`（两行）。)
134. **Quelle sortie possible pour ce programme ? / 给出该程序的一种可能输出。**

    ```c
    void *work(void *arg) {
        printf("T\n");
        return NULL;
    }
    int main(void) {
        pthread_t t;
        pthread_create(&t, NULL, work, NULL);
        printf("M\n");
        pthread_join(t, NULL);
        return 0;
    }
    
    ```

    * `M` puis `T` ou `T` puis `M`. (`M` 后 `T` 或 `T` 后 `M`。)
135. **Quelle sortie produit ce programme ? / 该程序输出什么？**

    ```c
    void *work(void *arg) {
        int *x = (int *)arg;
        *x += 1;
        return NULL;
    }
    int main(void) {
        int x = 1;
        pthread_t t;
        pthread_create(&t, NULL, work, &x);
        x += 2;
        pthread_join(t, NULL);
        printf("%d\n", x);
        return 0;
    }
    
    ```

    * `4`. (`4`。)
136. **Quelle sortie possible pour ce programme ? / 该程序可能输出什么？**

    ```c
    void *work(void *arg) {
        int *x = (int *)arg;
        *x = *x + 1;
        return NULL;
    }
    int main(void) {
        int x = 0;
        pthread_t t;
        pthread_create(&t, NULL, work, &x);
        x = x + 2;
        pthread_join(t, NULL);
        printf("%d\n", x);
        return 0;
    }
    
    ```

    * `2` ou `3` selon l'ordre (race). (可能是 `2` 或 `3`，取决于竞态顺序。)
137. **Quelle sortie produit ce programme ? / 该程序输出什么？**

    ```c
    int main(void) {
        pid_t c = fork();
        if (c == 0) {
            execlp("echo", "echo", "OK", NULL);
            _exit(1);
        }
        wait(NULL);
        return 0;
    }
    
    ```

    * `OK`. (`OK`。)
138. **Quelle sortie possible pour ce programme ? / 给出该程序的一种可能输出。**

    ```c
    int main(void) {
        printf("A");
        pid_t c = fork();
        printf("B\n");
        return 0;
    }
    
    ```

    * Deux lignes `AB` (ordre indetermine), car `A` est duplique par fork. (两行 `AB`，顺序不定；`A` 在 fork 后被复制。)
139. **Quelle sortie possible pour ce programme ? / 该程序可能输出什么？**

    ```c
    int main(void) {
        printf("A\n");
        pid_t c = fork();
        if (c == 0) {
            printf("C\n");
        } else {
            printf("P\n");
        }
        return 0;
    }
    
    ```

    * `A` d'abord, puis `C` et `P` dans un ordre indetermine. (`A` 先输出，随后 `C` 与 `P` 顺序不定。)

140. **Quelle sortie produit ce programme ? / 该程序输出什么？**

    ```c
    int main(void) {
        pid_t c = fork();
        if (c == 0) {
            printf("child\n");
            _exit(0);
        } else {
            printf("parent\n");
        }
        return 0;
    }
    
    ```

    * Deux lignes: `child` et `parent` (ordre indetermine). (两行 `child` 和 `parent`，顺序不定。)
