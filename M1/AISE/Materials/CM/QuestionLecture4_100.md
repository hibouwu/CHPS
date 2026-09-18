
# 100 Questions de révision - Lecture 4 : Concurrence et Parallélisme / 100 道复习题 - 第四讲：并发与并行

## I. Concepts Fondamentaux / 基本概念 (1-15)

1. **Qu'est-ce qu'un système concurrent ? / 什么是并发系统？**
    * Système où plusieurs activités s'exécutent simultanément et interagissent. (多个活动同时执行并相互交互的系统。)
2. **Donnez un exemple quotidien de système concurrent. / 举一个并发系统的日常例子。**
    * Serveur Web, contrôle de véhicule, OS, calcul scientifique. (Web 服务器、车辆控制、OS、科学计算。)
3. **Quelle est la différence entre parallélisme matériel et logiciel ? / 硬件并行和软件并行有什么区别？**
    * Matériel: Multi-cœurs, GPU. Logiciel: Processus, Threads gérés par l'OS. (硬件：多核、GPU。软件：OS 管理的进程、线程。)
4. **Qu'est-ce que l'implémentation séquentielle ? / 什么是串行实现？**
    * Calculs réalisés un par un sur une seule ressource. (在单一资源上逐个执行计算。)
5. **Qu'est-ce que l'implémentation parallèle ? / 什么是并行实现？**
    * Calculs décomposés et exécutés simultanément sur plusieurs ressources. (计算被分解并在多个资源上同时执行。)
6. **Pourquoi utilise-t-on le calcul parallèle ? / 为什么要使用并行计算？**
    * Pour résoudre des problèmes trop grands ou trop lents pour une seule machine. (为了解决对于单台机器来说太大或太慢的问题。)
7. **Qu'est-ce que le "High Performance Computing" (HPC) ? / 什么是“高性能计算” (HPC)？**
    * Utilisation de supercalculateurs pour des simulations massives. (使用超级计算机进行大规模模拟。)
8. **Quel est l'ordre de grandeur de puissance d'un supercalculateur Exascale ? / Exascale 超级计算机的计算能力大概是多少？**
    * $10^{18}$ flops.
9. **Qu'est-ce qu'un "flop" ? / 什么是 "flop"？**
    * Floating Point Operation Per Second. (每秒浮点运算次数。)
10. **Quelles sont les problématiques majeures du HPC ? / HPC 的主要问题有哪些？**
    * Passage à l'échelle, hétérogénéité, précision, coût énergétique. (可扩展性、异构性、精度、能耗。)
11. **Qu'est-ce que le passage à l'échelle (scalability) ? / 什么是可扩展性 (scalability)？**
    * Capacité à maintenir l'efficacité quand on augmente le nombre de processeurs. (增加处理器数量时保持效率的能力。)
12. **Qu'est-ce que l'hétérogénéité matérielle ? / 什么是硬件异构性？**
    * Mélange de CPU, GPU, FPGA dans un même système. (系统中混合使用 CPU、GPU、FPGA。)
13. **Pourquoi le transfert de données est-il un problème ? / 为什么数据传输是个问题？**
    * Il coûte du temps et de l'énergie (souvent plus que le calcul). (它消耗时间和能量（通常比计算更多）。)
14. **Quelle est la limite physique actuelle des fréquences processeur ? / 当前处理器频率的物理限制是什么？**
    * Environ 3-5 GHz (Mur de la chaleur/puissance). (约 3-5 GHz（热/功耗墙）。)
15. **Comment augmenter la puissance sans augmenter la fréquence ? / 如何在不增加频率的情况下提高性能？**
    * Augmenter le nombre de cœurs (Parallélisme). (增加核心数（并行）。)

## II. Architectures Mémoire / 内存架构 (16-30)

1. **Qu'est-ce qu'une architecture à mémoire partagée ? / 什么是共享内存架构？**
    * Tous les processeurs accèdent à la même mémoire globale. (所有处理器访问同一全局内存。)
2. **Quel est l'avantage principal de la mémoire partagée ? / 共享内存的主要优势是什么？**
    * Communication facile et rapide (latence faible). (通信简单快速（低延迟）。)
3. **Quel est l'inconvénient principal de la mémoire partagée ? / 共享内存的主要缺点是什么？**
    * Extensibilité limitée (Bus congestionné). (可扩展性有限（总线拥塞）。)
4. **Donnez un exemple de machine à mémoire partagée. / 举一个共享内存机器的例子。**
    * Un ordinateur portable multi-cœur, un nœud de calcul standard. (多核笔记本、标准计算节点。)
5. **Qu'est-ce qu'une architecture à mémoire distribuée ? / 什么是分布式内存架构？**
    * Chaque processeur a sa propre mémoire privée. (每个处理器都有自己的私有内存。)
6. **Comment communiquent les processeurs en mémoire distribuée ? / 分布式内存中的处理器如何通信？**
    * Par échange de messages explicite (Réseau). (通过显式消息传递（网络）。)
7. **Quel est l'avantage principal de la mémoire distribuée ? / 分布式内存的主要优势是什么？**
    * Grande extensibilité (Scale out). (高可扩展性。)
8. **Quel est l'inconvénient principal de la mémoire distribuée ? / 分布式内存的主要缺点是什么？**
    * Latence élevée, programmation complexe. (高延迟，编程复杂。)
9. **Donnez un exemple de système à mémoire distribuée. / 举一个分布式内存系统的例子。**
    * Un cluster de calcul (PlaFRIM, Supercalculateurs). (计算集群。)
10. **Qu'est-ce que NUMA ? / 什么是 NUMA？**
    * Non-Uniform Memory Access (Hybride: partagée mais avec des zones locales plus rapides). (非统一内存访问。)
11. **Quel type de réseau relie souvent les nœuds HPC ? / HPC 节点通常通过什么类型的网络连接？**
    * Infiniband, Ethernet haute performance (100Gb/s+).
12. **La latence est-elle plus faible en mémoire partagée ou distribuée ? / 哪种架构延迟更低？**
    * Partagée. (共享内存。)
13. **Quel modèle est "implicite" pour la communication ? / 哪种模型的通信是“隐式”的？**
    * Mémoire partagée (Threads).
14. **Quel modèle est "explicite" pour la communication ? / 哪种模型的通信是“显式”的？**
    * Mémoire distribuée (MPI) ou IPC.
15. **Peut-on combiner les deux architectures ? / 可以结合这两种架构吗？**
    * Oui, Clusters de nœuds multi-cœurs (Hybride MPI+OpenMP). (可以，多核节点集群。)

## III. Types de Parallélisme / 并行类型 (31-45)

1. **Qu'est-ce que le parallélisme de données ? / 什么是数据并行？**
    * Même opération appliquée sur un grand ensemble de données. (对大数据集应用相同操作。)
2. **Donnez un exemple de parallélisme de données. / 举一个数据并行的例子。**
    * Addition de deux vecteurs, traitement d'image. (向量加法、图像处理。)
3. **Qu'est-ce que le Pipelining (Chaîne de traitement) ? / 什么是流水线 (Pipelining)？**
    * Découpage d'une tâche en étapes séquentielles exécutées en parallèle sur des données différentes. (将任务分解为顺序步骤，在不同数据上并行执行。)
4. **Donnez un exemple de pipeline sous Unix. / 举一个 Unix 下的流水线例子。**
    * `grep ... | tr ... | sed ...`.
5. **Qu'est-ce que le parallélisme de tâches ? / 什么是任务并行？**
    * Opérations différentes exécutées simultanément (sur données identiques ou non). (同时执行不同的操作。)
6. **Quelle est la différence entre parallélisme de tâches et de données ? / 任务并行和数据并行有什么区别？**
    * Données = même code, données différentes. Tâches = code différent. (数据并行=相同代码不同数据。任务并行=不同代码。)
7. **Le calcul d'itinéraires GPS indépendants est-il du parallélisme de tâches ou de données ? / 独立 GPS 路线计算是任务并行还是数据并行？**
    * Parallélisme de tâches (chaque itinéraire est un calcul unique).
8. **La simulation numérique météo est-elle plutôt données ou tâches ? / 天气数值模拟偏向数据还是任务？**
    * Données (Maillage de l'espace). (数据（空间网格）。)
9. **Qu'est-ce que le SIMD ? / 什么是 SIMD？**
    * Single Instruction, Multiple Data (Parallélisme de données matériel).
10. **Qu'est-ce que le MIMD ? / 什么是 MIMD？**
    * Multiple Instruction, Multiple Data (Parallélisme de tâches).
11. **Quelle architecture convient le mieux au SIMD ? / 哪种架构最适合 SIMD？**
    * GPU ou processeurs vectoriels.
12. **Comment paralléliser une boucle `for` simple (sans dépendances) ? / 如何并行化简单的 `for` 循环（无依赖）？**
    * Parallélisme de données (chaque thread prend une partie des itérations).
13. **Si l'étape N+1 dépend de l'étape N, peut-on paralléliser directement ? / 如果步骤 N+1 依赖于步骤 N，能直接并行吗？**
    * Non (Dépendance de données).
14. **Le tube `A | B` permet-il à A et B de tourner en parallèle ? / 管道 `A | B` 允许 A 和 B 并行运行吗？**
    * Oui (Producteur/Consommateur).
15. **Quelle est la limite théorique de l'accélération parallèle ? / 并行加速的理论极限是什么？**
    * Loi d'Amdahl (limitée par la partie séquentielle). (Amdahl 定律（受限于串行部分）。)

## IV. Modèles d'Exécution et Communication / 执行模型与通信 (46-60)

1. **Quels sont les deux principaux modèles d'entités d'exécution ? / 两个主要的执行实体模型是什么？**
    * Processus et Threads. (进程和线程。)
2. **Comment communiquent les processus sans mémoire partagée ? / 无共享内存的进程如何通信？**
    * Sockets, Tubes, Messages.
3. **Comment communiquent les threads ? / 线程如何通信？**
    * Via les variables globales / tas partagé. (通过全局变量/共享堆。)
4. **Lors d'un fork, comment modifier une variable du père depuis le fils ? / fork 时，子进程如何修改父进程的变量？**
    * Impossible directement (nécessite IPC ou mémoire partagée explicite). (无法直接修改（需要 IPC 或显式共享内存）。)
5. **Lors d'un pthread_create, un thread peut-il modifier la mémoire du main ? / pthread_create 时，线程可以修改 main 的内存吗？**
    * Oui, si on lui passe un pointeur. (可以，如果传递指针。)
6. **Que signifie "COW" pour un processus ? / 对进程来说 "COW" 是什么意思？**
    * Les pages ne sont dupliquées qu'à l'écriture.
7. **Quel est l'avantage de l'échange de messages ? / 消息传递的优点是什么？**
    * Fonctionne entre machines différentes, pas de race condition mémoire *directe*. (适用于不同机器，无*直接*内存竞态。)
8. **Quel est l'inconvénient de l'échange de messages ? / 消息传递的缺点是什么？**
    * Copie des données (lent). (数据复制（慢）。)
9. **Quel est l'avantage de la mémoire partagée ? / 共享内存的优点是什么？**
    * Pas de copie, accès immédiat. (无复制，立即访问。)
10. **Quel est le risque majeur de la mémoire partagée ? / 共享内存的主要风险是什么？**
    * Condition de concurrence (Data Race). (竞争条件。)
11. **Qu'est-ce que MPI ? / MPI 是什么？**
    * Un standard pour l'échange de messages (Message Passing Interface).
12. **Qu'est-ce que OpenMP ? / OpenMP 是什么？**
    * Une API pour la mémoire partagée (directives pragma).
13. **Qu'est-ce que Pthreads ? / Pthreads 是什么？**
    * Le standard POSIX pour les threads (bas niveau).
14. **Pthreads est-il une bibliothèque ou un langage ? / Pthreads 是库还是语言？**
    * Une bibliothèque C.
15. **StartPU est-il pour mémoire partagée ou distribuée ? / StarPU 是用于共享还是分布式内存？**
    * Surtout mémoire partagée (gestion de tâches hétérogènes CPU/GPU).

## V. Concurrence et Synchronisation / 并发与同步 (61-80)

1. **Définissez "Condition de Concurrence" (Race Condition). / 定义“竞争条件”。**
    * Le résultat dépend de l'ordre arbitraire d'exécution (non-déterministe). (结果取决于任意的执行顺序（不确定性）。)
2. **Qu'est-ce qu'une "Section Critique" ? / 什么是“临界区”？**
    * Partie du code accédant à une ressource partagée modifiable. (访问可修改共享资源的代码部分。)
3. **Quelle propriété doit avoir l'accès à une section critique ? / 访问临界区必须具备什么属性？**
    * Exclusion Mutuelle (Atomicité). (互斥（原子性）。)
4. **Qu'est-ce qu'un Mutex ? / 什么是 Mutex？**
    * Mutual Exclusion lock (Verrou).
5. **Quelles sont les deux opérations sur un Mutex ? / Mutex 的两个操作是什么？**
    * Lock (Verrouiller) et Unlock (Déverrouiller).
6. **Que se passe-t-il si on essaie de Lock un Mutex déjà pris ? / 试图 Lock 一个已被占用的 Mutex 会怎样？**
    * On est bloqué (en attente) jusqu'à ce qu'il soit libéré. (被阻塞（等待）直到释放。)
7. **Qu'est-ce qu'un "Deadlock" (Interblocage) ? / 什么是 "Deadlock"（死锁）？**
    * Deux processus s'attendent mutuellement indéfiniment. (两个进程无限期互相等待。)
8. **Comment éviter les accès concurrents sur un compteur partagé ? / 如何避免共享计数器的并发访问？**
    * Utiliser un Mutex ou une instruction atomique. (使用 Mutex 或原子指令。)
9. **Qu'est-ce qu'une variable atomique ? / 什么是原子变量？**
    * Variable dont la lecture/écriture/modification est indivisible matériellement. (读/写/修改在硬件上不可分割的变量。)
10. **Pourquoi ne pas mettre tout le programme dans un Mutex ? / 为什么不把整个程序都放在 Mutex 里？**
    * On perdrait tout parallélisme (séquentialisation). (会失去所有并行性（串行化）。)
11. **Qu'est-ce qu'une Barrière ? / 什么是屏障？**
    * Point de rendez-vous où tous les threads doivent arriver avant de continuer. (所有线程必须到达才能继续的会合点。)
12. **Qu'est-ce qu'une Condition Variable ? / 什么是条件变量？**
    * Primitive permettant d'attendre qu'une condition soit vraie (signalée par un autre thread). (允许等待条件为真（由另一线程通知）的原语。)
13. **Le modèle Producteur-Consommateur utilise quelle synchronisation ? / 生产者-消费者模型使用什么同步？**
    * Condition Variables (et Mutex).
14. **Quelle est la différence entre Mutex et Sémaphore ? / Mutex 和信号量有什么区别？**
    * Mutex: propriété (un seul titulaire). Sémaphore: compteur (N permis). (Mutex：所有权（单一持有者）。信号量：计数器（N 个许可）。)
15. **En C Pthreads, comment copier une variable dans un thread ? / 在 C Pthreads 中，如何将变量复制到线程？**
    * Lui passer la **valeur** (cast en void*) ou une copie allouée dynamiquement. (传递**值**或动态分配的副本。)
16. **Pourquoi passer l'adresse d'une variable locale (stack) à un thread est dangereux ? / 为什么传递局部变量（栈）地址给线程很危险？**
    * Risque que la fonction parente retourne et détruise la pile avant l'utilisation. (父函数可能在线程使用前返回并销毁栈。)
17. **Qu'est-ce qu'un programme déterministe ? / 什么是确定性程序？**
    * Mêmes entrées -> Toujours même sortie. (输入相同 -> 输出永远相同。)
18. **Un programme parallèle est-il toujours non-déterministe ? / 并行程序总是非确定性的吗？**
    * Non, s'il est correctement synchronisé, il doit être déterministe (au niveau logique). (不，如果正确同步，它应该是确定性的。)
19. **Que fait `pthread_join` ? / `pthread_join` 做什么？**
    * Attend la fin d'un thread. (等待线程结束。)
20. **Quelle est la technique "Sommes locales" ? / 什么是“局部求和”技术？**
    * Chaque thread calcule une somme partielle, puis met à jour la somme globale une seule fois (réduit la contention). (每个线程计算部分和，然后只更新一次全局和（减少争用）。)

## VI. Paradigmes de Programmation / 编程范式 (81-100)

1. **Décrivez le modèle Fork-Join. / 描述 Fork-Join 模型。**
    * Le maître crée des travailleurs, ils travaillent, le maître les attend. (主线程创建工作线程，工作线程工作，主线程等待它们。)
2. **Quelle bibliothèque utilise souvent Fork-Join ? / 哪个库经常使用 Fork-Join？**
    * OpenMP.
3. **Décrivez le modèle Graphe de Tâches. / 描述任务图模型。**
    * Tâches avec dépendances (DAG), exécutées quand leurs dépendances sont prêtes. (具有依赖关系的任务 (DAG)，在依赖就绪时执行。)
4. **Quel est l'avantage du Graphe de Tâches ? / 任务图的优点是什么？**
    * Synchronisation implicite, équilibrage de charge automatique. (隐式同步，自动负载均衡。)
5. **Donnez un exemple de bibliothèque de Graphe de Tâches. / 举一个任务图库的例子。**
    * StarPU, OmpSs.
6. **Décrivez le modèle Échange de Messages (SPMD). / 描述消息传递模型 (SPMD)。**
    * Single Program Multiple Data. N copies du programme s'exécutent et communiquent. (单程序多数据。N 个程序副本运行并通信。)
7. **Quel est le standard dominant pour SPMD ? / SPMD 的主导标准是什么？**
    * MPI.
8. **CUDA est utilisé pour quel matériel ? / CUDA 用于什么硬件？**
    * GPU NVIDIA.
9. **Quel paradigme est le plus "facile" pour commencer ? / 哪个范式最容易上手？**
    * Mémoire partagée / OpenMP (souvent incrémental). (共享内存 / OpenMP（通常是增量式的）。)
10. **Qu'est-ce que l'équilibrage de charge (Load Balancing) ? / 什么是负载均衡？**
    * Répartir le travail équitablement pour que tous les cœurs finissent en même temps. (公平分配工作，以便所有核心同时完成。)
11. **Qu'est-ce que la granularité d'une tâche ? / 什么是任务的粒度？**
    * La taille/durée de la tâche. (任务的大小/持续时间。)
12. **Faut-il des tâches fines ou grossières ? / 需要细粒度还是粗粒度任务？**
    * Compromis : trop fines = overhead, trop grosses = mauvais équilibrage. (权衡：太细=开销大，太粗=均衡差。)
13. **Qu'est-ce que l'overhead de création de thread ? / 什么是创建线程的开销？**
    * Temps et ressources pour allouer la pile et structures noyau. (分配栈和内核结构的时间和资源。)
14. **Comment réduire l'overhead de création ? / 如何减少创建开销？**
    * Thread Pool (Réutiliser les threads). (线程池。)
15. **Un algorithme optimal en séquentiel est-il toujours optimal en parallèle ? / 串行最优算法在并行中总是最优吗？**
    * Non, la parallélisabilité compte. (不，并行性很重要。)
16. **Qu'est-ce que la loi d'Amdahl ? / 什么是 Amdahl 定律？**
    * Elle prédit l'accélération maximale théorique en fonction de la part séquentielle. (根据串行比例预测最大理论加速比。)
17. **Si 50% du code est séquentiel, quelle est l'accélération max avec une infinité de cœurs ? / 如果 50% 代码是串行的，无限核心的最大加速比是多少？**
    * x2 (Le temps est dominé par la partie séquentielle).
18. **Qu'est-ce que l'Hyperthreading (SMT) ? / 什么是超线程 (SMT)？**
    * 2 threads matériels sur un seul cœur physique (partagent les unités de calcul). (单物理核上的 2 个硬件线程。)
19. **Faut-il toujours utiliser tous les cœurs disponibles ? / 总是需要使用所有可用核心吗？**
    * Non, parfois la contention mémoire ralentit tout. (不，有时内存争用会拖慢整体速度。)
20. **Comment déboguer un programme parallèle ? / 如何调试并行程序？**
    * Outils spécialisés (Valgrind/Helgrind, ThreadSanitizer), logs, réduction du nombre de threads. (专用工具、日志、减少线程数。)

## VII. Exercices Pratiques de Code / 实战代码练习 (1-20)

### Processus et Fork / 进程与 Fork

1. **Quel est l'affichage de ce code ? / 这段代码的输出是什么？**

    ```c
    int x = 10;
    if (fork() == 0) {
        x++;
        printf("Child: %d\n", x);
    } else {
        wait(NULL);
        printf("Parent: %d\n", x);
    }
    ```

    * `Child: 11`, `Parent: 10`. (Les processus ont des espaces d'adressage séparés. / 进程拥有独立的地址空间。)

2. **Combien de fois "Hello" est-il affiché ? / "Hello" 会被打印几次？**

    ```c
    for(int i=0; i<3; i++) {
        fork();
    }
    printf("Hello\n");
    ```

    * 8 fois. ($2^3 = 8$ processus sont créés au total. / 总共创建了 $2^3 = 8$ 个进程。)

3. **Que devient le processus fils si le père termine sans l'attendre ? / 如果父进程不等待子进程就结束，子进程会变成什么？**
    * Orphelin (adopté par `init` ou `systemd`). (孤儿进程（被 `init` 或 `systemd` 收养）。)

4. **Que devient le processus fils s'il termine avant que le père ne fasse `wait` ? / 如果子进程在父进程 `wait` 之前结束，子进程会变成什么？**
    * Zombie (Il attend que son code de retour soit lu). (僵尸进程（等待其返回码被读取）。)

### Threads et Mémoire Partagée / 线程与共享内存

1. **Quel est l'affichage possible de ce code ? / 这段代码的输出可能是？**

    ```c
    int g = 0;
    void* run(void* arg) { g = 1; return NULL; }
    int main() {
        pthread_t t;
        pthread_create(&t, NULL, run, NULL);
        pthread_join(t, NULL);
        printf("%d", g);
    }
    ```

    * `1`. (Les threads partagent les variables globales. / 线程共享全局变量。)

2. **Quel est le problème avec ce passage d'argument ? / 这个参数传递有什么问题？**

    ```c
    void* run(void* arg) { int* p = (int*)arg; printf("%d", *p); }
    int main() {
        for(int i=0; i<10; i++) 
            pthread_create(&t, NULL, run, &i); 
    }
    ```

    * Race Condition sur `i`. La valeur de `i` peut changer avant que le thread ne la lise. (关于 `i` 的竞争条件。`i` 的值可能在线程读取之前改变。)

3. **Comment corriger le problème du passage d'argument ci-dessus ? / 如何修正上面的参数传递问题？**
    * Passer la valeur directement castée : `(void*)(intptr_t)i`, ou allouer un `int` dynamiquement pour chaque thread. (直接传递转换后的值，或者为每个线程动态分配 `int`。)

4. **Que se passe-t-il si un thread appelle `exit(0)` ? / 如果一个线程调用 `exit(0)` 会发生什么？**
    * Tout le processus (et tous les threads) se termine immédiatement. (整个进程（以及所有线程）立即终止。)

### Synchronisation et Mutex / 同步与互斥锁

1. **Quel est le problème ici ? / 这里有什么问题？**

    ```c
    int cpt = 0;
    void* inc(void* a) { 
        for(int i=0; i<1000; i++) cpt++; 
    }
    ```

    * Race Condition. `cpt++` n'est pas atomique (Lecture-Modif-Écriture). (竞争条件。`cpt++` 不是原子的（读-改-写）。)

10. **Quelle est la valeur minimale possible de `cpt` (2 threads, 1000 inc) ? / `cpt` 的最小可能值是多少（2个线程，1000次递增）？**
    * 2 (Théoriquement, si écrasements massifs). En pratique souvent > 1000 mais < 2000. (2（理论上，如果发生大规模覆盖）。实际上通常 > 1000 但 < 2000。)

11. **Que se passe-t-il ici ? / 这里发生了什么？**

    ```c
    pthread_mutex_lock(&m);
    pthread_mutex_lock(&m); // Second appel
    ```

    * Deadlock (Interblocage). Le thread s'attend lui-même (si mutex non-récursif). (死锁。线程等待自己（如果 mutex 非递归）。)

12. **Dans quel ordre les threads acquièrent-ils le lock ? / 线程获取锁的顺序是什么？**
    * Indeterminé. Le système d'exploitation décide. (不确定。由操作系统决定。)

### Communication (Pipes/Cond) / 通信 (管道/条件变量)

13. **Que fait ce code ? / 这段代码做什么？**

    ```c
    int fd[2]; pipe(fd);
    if(fork()==0) { close(fd[0]); write(fd[1], "A", 1); }
    else { close(fd[1]); read(fd[0], buf, 1); }
    ```

    * Communication unidirectionnelle Fils -> Père. (子进程 -> 父进程的单向通信。)

14. **Pourquoi fermer les descripteurs inutilisés dans un pipe ? / 为什么要关闭管道中未使用的描述符？**
    * Pour que `read` retourne 0 (EOF) quand tous les écrivains sont fermés. Sinon, deadlock possible. (以便当所有写入端关闭时 `read` 返回 0 (EOF)。否则可能死锁。)

15. **Que manque-t-il ici pour une Condition Variable ? / 条件变量这里缺了什么？**

    ```c
    pthread_cond_wait(&cond, &mutex);
    ```

    * Une boucle `while(condition_non_remplie)` autour du wait pour gérer les réveils spontanés. (wait 周围需要一个 `while` 循环来处理虚假唤醒。)

16. **À quoi sert `pthread_cond_broadcast` ? / `pthread_cond_broadcast` 有什么用？**
    * Réveille *tous* les threads en attente sur la condition (ex: barrière). (唤醒该条件上等待的*所有*线程。)

### Conception Parallèle / 并行设计

17. **Quel modèle est utilisé ici ? / 这里使用了什么模型？**

    ```c
    while(1) { item = produce(); put_buffer(item); } // Thread 1
    while(1) { item = get_buffer(); consume(item); } // Thread 2
    ```

    * Producteur-Consommateur. (生产者-消费者。)

18. **Comment implémenter une barrière pour N threads ? / 如何为 N 个线程实现屏障？**
    * Un compteur protégé par mutex + Condition variable. Le dernier réveille tout le monde. (由 mutex 保护的计数器 + 条件变量。最后一个唤醒所有人。)

19. **Quelle est la différence entre `wait(NULL)` et `pthread_join` ? / `wait(NULL)` 和 `pthread_join` 的区别？**
    * `wait`: attend n'importe quel processus fils. `join`: attend un thread spécifique. (`wait`：等待任意子进程。`join`：等待特定线程。)

20. **Peut-on utiliser des pointeurs dans de la mémoire partagée (IPC shm) ? / 可以在共享内存 (IPC shm) 中使用指针吗？**
    * Non (ou difficilement), car les adresses virtuelles peuvent différer entre processus. Utiliser des offsets. (不行（或很难），因为进程间的虚拟地址可能不同。使用偏移量。)
