
# 100 Questions de révision - Lecture 5 : Introduction à OpenMP / 100 道复习题 - 第五讲：OpenMP 入门

## I. Concepts et Modèle d'Exécution / 概念与执行模型 (1-15)

1. **Qu'est-ce que OpenMP ? / 什么是 OpenMP？**
    * Une interface de programmation standard (API) pour le parallélisme à mémoire partagée. (用于共享内存并行的标准编程接口 (API)。)
2. **Sur quels éléments repose OpenMP ? / OpenMP 基于哪些元素？**
    * Directives de compilation (#pragma), bibliothèque d'exécution, variables d'environnement. (编译指令 (#pragma)，运行时库，环境变量。)
3. **Quel est le modèle d'exécution d'OpenMP ? / OpenMP 的执行模型是什么？**
    * Fork-Join.
4. **Comment appelle-t-on le fil d'exécution initial ? / 初始线程叫什么？**
    * Le fil maître (Master thread). (主线程。)
5. **Que se passe-t-il à l'entrée d'une région parallèle ? / 进入并行区域时会发生什么？**
    * Le maître crée une équipe (team) de fils d'exécution (Fork). (主线程创建一组线程 (Fork)。)
6. **Que se passe-t-il à la sortie d'une région parallèle ? / 退出并行区域时会发生什么？**
    * Les fils esclaves sont détruits (ou mis en veille), seul le maître continue (Join). (从线程被销毁（或休眠），只有主线程继续 (Join)。)
7. **Quelle directive crée une région parallèle ? / 哪个指令创建并行区域？**
    * `#pragma omp parallel`.
8. **Par défaut, comment est la mémoire dans une région parallèle ? / 默认情况下，并行区域中的内存是怎样的？**
    * Partagée (Shared). (共享的。)
9. **Chaque thread a-t-il sa propre pile (stack) ? / 每个线程都有自己的栈吗？**
    * Oui. (是的。)
10. **Quelle variable d'environnement définit le nombre de threads ? / 哪个环境变量定义线程数？**
    * `OMP_NUM_THREADS`.
11. **Quelle fonction C permet de définir le nombre de threads dynamiquement ? / 哪个 C 函数可以动态定义线程数？**
    * `omp_set_num_threads(int)`.
12. **Quelle est la priorité de définition du nombre de threads (Env vs Code) ? / 定义线程数的优先级是怎样的（环境变量 vs 代码）？**
    * Code (`num_threads` clause) > Fonction (`omp_set_num_threads`) > Env (`OMP_NUM_THREADS`).
13. **Si rien n'est spécifié, combien de threads sont utilisés ? / 如果未指定，使用多少个线程？**
    * Généralement le nombre de cœurs logiques disponibles. (通常是可用的逻辑核心数。)
14. **Peut-on imbriquer des régions parallèles ? / 可以嵌套并行区域吗？**
    * Oui, si le support est activé (`omp_set_nested`). (可以，如果启用了支持。)
15. **OpenMP supporte-t-il le parallélisme de tâches ? / OpenMP 支持任务并行吗？**
    * Oui (depuis la version 3.0). (支持（自 3.0 版起）。)

## II. Directives de Base et Partage de Travail / 基本指令与工作分担 (16-35)

1. **Quelle est la syntaxe d'une directive OpenMP en C ? / C 语言中 OpenMP 指令的语法是什么？**
    * `#pragma omp directive [clauses]`.
2. **Que fait `#pragma omp parallel` sans autre directive ? / 没有其他指令的 `#pragma omp parallel` 做什么？**
    * Tous les threads exécutent le bloc de code (duplication du travail). (所有线程执行代码块（工作重复）。)
3. **Comment paralléliser une boucle `for` ? / 如何并行化 `for` 循环？**
    * `#pragma omp parallel for` (ou `#pragma omp for` dans une région parallèle).
4. **Quelle est la condition pour paralléliser une boucle ? / 并行化循环的条件是什么？**
    * Les itérations doivent être indépendantes (pas de dépendance de données). (迭代必须是独立的（无数据依赖）。)
5. **Que fait `#pragma omp sections` ? / `#pragma omp sections` 做什么？**
    * Définit des blocs de code différents à exécuter en parallèle. (定义要并行执行的不同代码块。)
6. **Que fait `#pragma omp single` ? / `#pragma omp single` 做什么？**
    * Le bloc est exécuté par un seul thread (n'importe lequel). (该块仅由一个线程（任意）执行。)
7. **Que fait `#pragma omp master` ? / `#pragma omp master` 做什么？**
    * Le bloc est exécuté uniquement par le fil maître. (该块仅由主线程执行。)
8. **Quelle est la différence entre `single` et `master` concernant la synchronisation ? / `single` 和 `master` 在同步方面有什么区别？**
    * `single` a une barrière implicite à la fin, `master` non. (`single` 结尾有隐式屏障，`master` 没有。)
9. **Comment répartir les itérations d'une boucle de manière statique ? / 如何静态分配循环迭代？**
    * `schedule(static, chunk)`.
10. **Comment répartir les itérations de manière dynamique ? / 如何动态分配迭代？**
    * `schedule(dynamic, chunk)`.
11. **Qu'est-ce que `nowait` ? / 什么是 `nowait`？**
    * Supprime la barrière implicite à la fin d'une construction de partage de travail. (删除工作分担结构末尾的隐式屏障。)
12. **Peut-on sortir d'une boucle parallèle avec `break` ? / 可以用 `break` 跳出并行循环吗？**
    * Non, interdit. (不行，禁止。)
13. **L'itérateur de boucle (ex: `i`) est-il partagé ou privé par défaut dans `omp for` ? / `omp for` 中的循环迭代器（如 `i`）默认是共享还是私有？**
    * Privé. (私有。)
14. **Que fait `collapse(n)` ? / `collapse(n)` 做什么？**
    * Fusionne `n` boucles imbriquées pour augmenter le parallélisme. (合并 `n` 个嵌套循环以增加并行度。)
15. **Que se passe-t-il si le nombre d'itérations est inférieur au nombre de threads ? / 如果迭代次数少于线程数会发生什么？**
    * Certains threads ne feront rien. (有些线程什么也不做。)
16. **Comment paralléliser seulement une partie d'une fonction avec OpenMP ? / 如何使用 OpenMP 仅并行化函数的一部分？**
    * En englobant cette partie avec des accolades `{ ... }` sous la directive. (将该部分用花括号 `{ ... }` 包围在指令下。)
17. **Quelle clause permet de définir le nombre de threads pour une région spécifique ? / 哪个子句允许为特定区域定义线程数？**
    * `num_threads(n)`.
18. **Que fait la clause `ordered` ? / `ordered` 子句做什么？**
    * Force l'exécution séquentielle d'une partie de la boucle (dans l'ordre des itérations). (强制按顺序执行循环的一部分。)
19. **Avec `schedule(static)`, qui exécute l'itération 0 ? / 使用 `schedule(static)`，谁执行迭代 0？**
    * Le thread 0 (généralement). (通常是线程 0。)
20. **Quel schedule est le meilleur si le temps de calcul varie par itération ? / 如果计算时间随迭代变化，哪种 schedule 最好？**
    * `dynamic` (ou `guided`).

## III. Gestion des Données (Clauses) / 数据管理（子句） (36-60)

1. **Que fait la clause `private(x)` ? / `private(x)` 子句做什么？**
    * Crée une copie non-initialisée de `x` pour chaque thread. (为每个线程创建一个未初始化的 `x` 副本。)
2. **Les modifications sur une variable `private` sont-elles visibles après la région parallèle ? / 并行区域后 `private` 变量的修改可见吗？**
    * Non. (不可见。)
3. **Que fait `firstprivate(x)` ? / `firstprivate(x)` 做什么？**
    * Comme `private`, mais initialise la copie avec la valeur de `x` avant la région. (像 `private`，但用区域前的 `x` 值初始化副本。)
4. **Que fait `lastprivate(x)` ? / `lastprivate(x)` 做什么？**
    * Copie la valeur de la dernière itération (ou section) dans la variable d'origine à la sortie. (退出时将最后一次迭代（或 section）的值复制到原始变量。)
5. **Que fait `shared(x)` ? / `shared(x)` 做什么？**
    * Tous les threads accèdent à la même variable `x`. (所有线程访问同一个变量 `x`。)
6. **Quel est le risque principal avec `shared` ? / `shared` 的主要风险是什么？**
    * Race Condition. (竞争条件。)
7. **Que fait `default(none)` ? / `default(none)` 做什么？**
    * Force le programmeur à spécifier le statut (shared/private) de toutes les variables. (强制程序员指定所有变量的状态。)
8. **Que fait `default(shared)` ? / `default(shared)` 做什么？**
    * Rend toutes les variables visibles partagées par défaut. (默认使所有可见变量共享。)
9. **Dans une fonction appelée depuis une région parallèle, les variables locales sont-elles partagées ? / 在并行区域调用的函数中，局部变量是共享的吗？**
    * Non, elles sont sur la pile du thread (donc privées). (不，它们在线程栈上（因此是私有的）。)
10. **Les variables globales (static/extern) sont-elles partagées par défaut ? / 全局变量（static/extern）默认是共享的吗？**
    * Oui. (是的。)
11. **Les variables allouées dynamiquement (malloc) sont-elles partagées ? / 动态分配 (malloc) 的变量是共享的吗？**
    * Le pointeur peut être privé ou partagé, mais la mémoire pointée est partagée (heap). (指针可以是私有或共享，但指向的内存是共享的（堆）。)
12. **Comment faire une somme parallèle ? / 如何进行并行求和？**
    * Utiliser la clause `reduction(+:sum)`.
13. **Comment fonctionne `reduction(op:var)` ? / `reduction(op:var)` 如何工作？**
    * Crée une copie privée initialisée (ex: 0 pour +), puis combine les résultats à la fin. (创建初始化的私有副本（如 + 为 0），然后在结束时合并结果。)
14. **Quelle est la valeur initiale pour une réduction `*` (multiplication) ? / 乘法归约 `*` 的初始值是多少？**
    * 1.
15. **Si je déclare `int x` *dans* la boucle parallèle, est-il shared ou private ? / 如果我在并行循环*内部*声明 `int x`，它是 shared 还是 private？**
    * Private (automatiquement). (私有（自动）。)
16. **Que se passe-t-il si plusieurs threads écrivent dans un tableau à des indices différents ? / 如果多个线程写入数组的不同索引会发生什么？**
    * C'est sûr (pas de race condition), mais risque de "False Sharing" si indices proches. (安全（无竞争条件），但如果索引接近可能有“伪共享”风险。)
17. **Qu'est-ce que le False Sharing ? / 什么是伪共享？**
    * Ralentissement dû au partage de la même ligne de cache par des variables indépendantes. (由于独立变量共享同一缓存行而导致的减速。)
18. **Comment éviter le False Sharing ? / 如何避免伪共享？**
    * Padding (remplissage) ou utilisation de variables locales/réduction. (填充或使用局部变量/归约。)
19. **La clause `threadprivate` sert à quoi ? / `threadprivate` 子句有什么用？**
    * Rend une variable globale privée et persistante pour chaque thread. (使全局变量对每个线程私有且持久。)
20. **`copyin` est utilisé avec quelle autre clause ? / `copyin` 与哪个子句一起使用？**
    * `threadprivate` (pour initialiser les valeurs des threads esclaves).

## IV. Synchronisation / 同步 (61-80)

1. **Quelle directive pose une barrière explicite ? / 哪个指令设置显式屏障？**
    * `#pragma omp barrier`.
2. **Que fait `#pragma omp critical` ? / `#pragma omp critical` 做什么？**
    * Assure qu'un seul thread exécute le bloc à la fois (Mutex). (确保一次只有一个线程执行该块 (Mutex)。)
3. **Peut-on nommer une section critique ? / 可以命名临界区吗？**
    * Oui (`critical (name)`). Si non nommé, global lock. (可以。未命名则是全局锁。)
4. **Que fait `#pragma omp atomic` ? / `#pragma omp atomic` 做什么？**
    * Rend une opération mémoire simple (lecture/écriture/update) atomique. (使简单的内存操作（读/写/更新）原子化。)
5. **Quelle est la différence entre `atomic` et `critical` ? / `atomic` 和 `critical` 有什么区别？**
    * `atomic` est plus léger (souvent instruction matérielle) mais limité aux opérations simples. (`atomic` 更轻量（通常是硬件指令）但仅限于简单操作。)
6. **`x++` peut-il être atomique ? / `x++` 可以是原子的吗？**
    * Oui (`#pragma omp atomic`).
7. **`x = expensive_function()` peut-il être atomique ? / `x = expensive_function()` 可以是原子的吗？**
    * Non, seul l'assignation, pas le calcul. (不，只有赋值，不是计算。)
8. **Où y a-t-il des barrières implicites ? / 哪里有隐式屏障？**
    * Fin de `parallel`, `for`, `sections`, `single`.
9. **Comment supprimer une barrière implicite ? / 如何删除隐式屏障？**
    * Clause `nowait`.
10. **Pourquoi utiliser `nowait` ? / 为什么使用 `nowait`？**
    * Pour réduire l'attente si les threads suivants n'ont pas besoin des résultats. (如果后续线程不需要结果，减少等待。)
11. **Qu'est-ce qui est plus rapide : atomic ou critical ? / atomic 和 critical 哪个更快？**
    * Atomic.
12. **Qu'est-ce qu'un Lock OpenMP ? / 什么是 OpenMP 锁？**
    * `omp_lock_t` (fonctions `omp_init_lock`, `omp_set_lock`, ...).
13. **Pourquoi préférer les directives aux fonctions de Lock ? / 为什么优先选指令而不是锁函数？**
    * Plus simple, moins d'erreurs (oubli d'unlock). (更简单，错误更少（忘记解锁）。)
14. **La réduction implique-t-elle une synchronisation ? / 归约意味着同步吗？**
    * Oui, à la fin pour combiner les résultats. (是的，最后合并结果时。)
15. **Que se passe-t-il si un thread atteint une barrière et pas les autres ? / 如果一个线程到达屏障而其他没有会发生什么？**
    * Il attend (Deadlock si les autres n'arrivent jamais). (它等待（如果其他人永远不到达则死锁）。)
16. **Peut-on placer une barrière dans un `if` ? / 可以在 `if` 中放置屏障吗？**
    * Dangereux : tous les threads doivent prendre le même chemin ou l'éviter. (危险：所有线程必须走相同的路径或都避开它。)
17. **La directive `master` a-t-elle une barrière ? / `master` 指令有屏障吗？**
    * Non.
18. **`ordered` synchronise-t-il tout le monde ? / `ordered` 会同步所有人吗？**
    * Non, il ordonne juste l'exécution d'un bloc spécifique. (不，它只是排序特定块的执行。)
19. **`flush` sert à quoi ? / `flush` 有什么用？**
    * Assure la cohérence de la vue mémoire (Memory Consistency). (确保内存视图的一致性。)
20. **Les opérations atomiques impliquent-elles un flush ? / 原子操作意味着 flush 吗？**
    * Oui. (是的。)

## V. Tâches et Avancé / 任务与高级 (81-100)

1. **Que fait `#pragma omp task` ? / `#pragma omp task` 做什么？**
    * Crée une tâche asynchrone qui sera exécutée par un thread de l'équipe. (创建一个由于团队线程执行的异步任务。)
2. **Où utilise-t-on souvent les tâches ? / 通常在哪里使用任务？**
    * Boucles `while`, récursion, structures irrégulières (listes, arbres). (`while` 循环，递归，不规则结构（列表，树）。)
3. **Qui exécute une tâche ? / 谁执行任务？**
    * N'importe quel thread disponible (y compris celui qui l'a créée). (任何可用线程（包括创建它的线程）。)
4. **Que fait `#pragma omp taskwait` ? / `#pragma omp taskwait` 做什么？**
    * Attend la fin des tâches filles directes. (等待直接子任务结束。)
5. **Quelle directive est nécessaire pour lancer des tâches initiales ? / 启动初始任务需要哪个指令？**
    * `#pragma omp parallel` puis souvent `#pragma omp single`.
6. **Qu'est-ce que `omp_get_thread_num()` ? / `omp_get_thread_num()` 是什么？**
    * Retourne l'ID du thread courant (0 à N-1). (返回当前线程 ID。)
7. **Qu'est-ce que `omp_get_num_threads()` ? / `omp_get_num_threads()` 是什么？**
    * Retourne le nombre total de threads dans l'équipe. (返回团队中的总线程数。)
8. **Que fait `#pragma omp simd` ? / `#pragma omp simd` 做什么？**
    * Force la vectorisation de la boucle (utilisation registres AVX/SSE). (强制循环向量化（使用 AVX/SSE 寄存器）。)
9. **Peut-on combiner `parallel for` et `simd` ? / 可以组合 `parallel for` 和 `simd` 吗？**
    * Oui (`#pragma omp parallel for simd`).
10. **Qu'est-ce que le support "Target" (OpenMP 4.0+) ? / "Target" 支持 (OpenMP 4.0+) 是什么？**
    * Déchargement (Offloading) vers GPU ou accélérateurs. (卸载到 GPU 或加速器。)
11. **Comment spécifier une dépendance de tâche ? / 如何指定任务依赖？**
    * Clause `depend(in: x, out: y)`.
12. **À quoi sert `taskgroup` ? / `taskgroup` 有什么用？**
    * Attend toutes les tâches créées dans le bloc (y compris les descendantes). (等待块中创建的所有任务（包括后代）。)
13. **Quelle est la différence entre `taskwait` et `taskgroup` ? / `taskwait` 和 `taskgroup` 有什么区别？**
    * `taskwait`: enfants directs seulement. `taskgroup`: tout le sous-graphe. (`taskwait`：仅直接子任务。`taskgroup`：整个子图。)
14. **Comment mesurer le temps avec OpenMP ? / 如何用 OpenMP 测量时间？**
    * `omp_get_wtime()`.
15. **Est-ce que `printf` est Thread-safe ? / `printf` 是线程安全的吗？**
    * Oui, mais l'ordre des lignes est indéterminé. (是，但行顺序不确定。)
16. **Si je fais `printf` dans une boucle parallèle, l'ordre est-il 0, 1, 2... ? / 如果我在并行循环中 `printf`，顺序是 0, 1, 2... 吗？**
    * Non, aléatoire. (不，随机。)
17. **Pour une boucle for de 100 itérations et 4 threads, combien d'itérations par thread en `schedule(static)` ? / 对于 100 次迭代和 4 个线程的循环，`schedule(static)` 每个线程多少次？**
    * 25 (blocs contigus par défaut). (25（默认连续块）。)
18. **Et avec `schedule(static, 1)` ? / 使用 `schedule(static, 1)` 呢？**
    * 25 aussi, mais entrelacées (Cyclic distribution). (也是 25，但是在交错的（循环分布）。)
19. **Qu'est-ce qu'une "Untied Task" ? / 什么是 "Untied Task"？**
    * Tâche qui peut être suspendue et reprise par un autre thread. (可以被挂起并由另一个线程恢复的任务。)
20. **Comment limiter la profondeur de parallélisme imbriqué ? / 如何限制嵌套并行深度？**
    * `OMP_MAX_ACTIVE_LEVELS`.
21. **Que se passe-t-il si un thread fait `exit()` ? / 如果一个线程执行 `exit()` 会发生什么？**
    * Tout le programme s'arrête. (整个程序停止。)
22. **Les directives OpenMP sont-elles portables ? / OpenMP 指令是可移植的吗？**
    * Oui, si le compilateur supporte OpenMP (gcc -fopenmp). (是的，如果编译器支持。)
23. **Que fait le compilateur si on compile sans `-fopenmp` ? / 如果编译时不带 `-fopenmp`，编译器会怎么做？**
    * Il ignore les `#pragma omp` (code séquentiel). (忽略 `#pragma omp`（串行代码）。)
24. **Pourquoi utiliser `if` dans une clause `parallel` ? / 为什么在 `parallel` 子句中使用 `if`？**
    * Pour désactiver le parallélisme si les données sont trop petites (éviter l'overhead). (如果数据太小，禁用并行（避免开销）。)
25. **Quelle est la surcharge principale d'OpenMP ? / OpenMP 的主要开销是什么？**
    * Création de threads et synchronisation. (创建线程和同步。)

## VI. Exercices Pratiques de Code / 实战代码练习 (1-20)

### Régions Parallèles de Base / 基础并行区域

1. **Avec `OMP_NUM_THREADS=4`, que fait ce code ? / 当 `OMP_NUM_THREADS=4` 时，这段代码做什么？**

    ```c
    #pragma omp parallel
    printf("A");
    printf("B");
    ```

    * Affiche "A" 4 fois (en parallèle/désordre), puis "B" 1 fois (séquentiel/maître). (打印 "A" 4 次（并行/乱序），然后 "B" 1 次（串行/主线程）。) *Attention: l'accolade manquante applique parallel uniquement au premier printf.*

2. **Quelle clause désactive le parallélisme si N < 1000 ? / 如果 N < 1000，哪个子句禁用并行？**

    ```c
    #pragma omp parallel if(N >= 1000)
    ```

    * `if(condition)`.

3. **Quel thread exécute ce code ? / 哪个线程执行这段代码？**

    ```c
    #pragma omp parallel num_threads(4)
    if (omp_get_thread_num() == 0) printf("Master");
    ```

    * Le thread 0 (Master).

4. **Comment définir le nombre de threads depuis le code (C) ? / 如何在代码 (C) 中定义线程数？**
    * `omp_set_num_threads(int n)` avant la région parallèle.

### Partage de Travail (Work Sharing) / 工作分担

1. **Qui exécute quoi ici (4 threads, 8 itérations) ? / 这里谁执行什么（4线程，8次迭代）？**

    ```c
    #pragma omp parallel for schedule(static)
    for(int i=0; i<8; i++) ...
    ```

    * T0: 0-1, T1: 2-3, T2: 4-5, T3: 6-7. (Blocs contigus équitables. / 均匀的连续块。)

2. **Qui exécute le bloc `single` ? / 谁执行 `single` 块？**
    * Le premier thread qui arrive (pas forcément le maître). (第一个到达的线程。)

3. **Quelle est la différence entre `single` et `master` ? / `single` 和 `master` 的区别？**
    * `single`: barrière implicite à la fin. `master`: pas de barrière, seul thread 0 exécute. (`single`：结束后有隐式屏障。`master`：无屏障，仅线程 0 执行。)

4. **Comment paralléliser ceci correctement ? / 如何正确并行化这个？**

    ```c
    for(int i=0; i<N; i++) a[i] = foo(i);
    for(int i=0; i<N; i++) b[i] = bar(a[i]);
    ```

    * Deux `#pragma omp parallel for` séparés (ou un grand `parallel` avec deux `for nowait` et une barrière entre eux si dépendance). (两个分开的 `#pragma omp parallel for`。)

### Gestion des Données (Data Scope) / 数据作用域

1. **Quelle est la valeur finale de `a` ? / `a` 的最终值是多少？**

    ```c
    int a = 0;
    #pragma omp parallel private(a)
    { a = 1; }
    printf("%d", a);
    ```

    * `0`. (La modification est sur la copie privée. / 修改是在私有副本上。)

2. **Quelle est la valeur initiale de `x` dans la boucle ? / 循环中 `x` 的初始值是多少？**

    ```c
    int x = 5;
    #pragma omp parallel for firstprivate(x)
    for(...) { printf("%d", x); x++; }
    ```

    * `5` pour chaque thread (au début de chaque itération/thread). (每个线程为 `5`。)

3. **Que se passe-t-il avec `lastprivate(i)` ? / `lastprivate(i)` 会发生什么？**
    * La valeur de `i` correspondant à la *dernière itération* séquentielle est copiée à l'extérieur. (对应于*最后一次*串行迭代的 `i` 值被复制到外部。)

4. **`default(none)` est-il recommandé ? Pourquoi ? / 推荐使用 `default(none)` 吗？为什么？**
    * Oui. Il force à réfléchir à la portée de chaque variable (évite les bugs de partage accidentel). (是的。它强制思考每个变量的作用域（避免意外共享导致的 bug）。)

### Synchronisation et Réductions / 同步与归约

1. **Comment corriger la Race Condition ici ? / 如何修正这里的竞争条件？**

    ```c
    int sum = 0;
    #pragma omp parallel for
    for(int i=0; i<N; i++) sum += A[i];
    ```

    * Ajouter `reduction(+:sum)` à la directive pragma. (添加 `reduction(+:sum)`。)

2. **Quelle est la différence entre `atomic` et `critical` ? / `atomic` 和 `critical` 的区别？**
    * `atomic` est pour une seule instruction mémoire (plus rapide). `critical` est pour un bloc de code. (`atomic` 针对单条内存指令（更快）。`critical` 针对代码块。)

3. **Que fait `nowait` ici ? / `nowait` 这里做什么？**

    ```c
    #pragma omp for nowait
    for(...) { ... }
    ```

    * Les threads n'attendent pas les autres à la fin de la boucle et continuent l'exécution. (线程在循环结束时不等待其他人，继续执行。)

4. **Quel est le risque de supprimer une barrière ? / 删除屏障有什么风险？**
    * Lecture de données pas encore produites par un autre thread (Race condition). (读取其他线程尚未生成的数据（竞争条件）。)

### Tâches et Avancé / 任务与高级

1. **Que fait `#pragma omp task` ? / `#pragma omp task` 做什么？**
    * Crée une tâche qui sera exécutée plus tard par n'importe quel thread de l'équipe. (创建一个稍后由团队中任意线程执行的任务。)

2. **Pourquoi utiliser `taskwait` ? / 为什么使用 `taskwait`？**
    * Pour s'assurer que les tâches filles sont finies avant de continuer (ex: calcul récursif). (确保子任务在继续前完成（例如：递归计算）。)

3. **Que fait `schedule(dynamic, 1)` ? / `schedule(dynamic, 1)` 做什么？**
    * Distribue les itérations une par une aux threads qui en demandent (Load Balancing). (将迭代逐个分发给请求的线程（负载均衡）。)

4. **Comment empêcher deux threads d'écrire sur la même ligne de cache (False Sharing) ? / 如何防止两个线程写入同一缓存行（伪共享）？**
    * Utiliser des variables locales et une réduction, ou ajouter du "padding" entre les données. (使用局部变量并归约，或在数据间添加“填充”。)
