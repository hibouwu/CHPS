# 往年 TP2：异步执行与 CUDA 流（Asynchronisme – Utilisation des Streams, APM 2025-2026）

题目：[tp2_sujet_2025-2026.pdf](tp2_sujet_2025-2026.pdf) · 教师解答：[tp2_correction.pdf](tp2_correction.pdf)（2024–2025 学年，题目与 2025–2026 版逐字相同）

标为“教师解答”的是老师 2024–2025 年的 Correction，老师没写的题由“解答”补上。原题提到的 `func` 源码、`graph.pdf` 和各个 `.cu` 程序都不在本地目录中。

> Les objectifs de ce TP sont :
> - Utilisation des Streams CUDA pour faire du calcul asynchrone.
> - Permettre le recouvrement des transferts mémoire par du calcul.

本实验的目标：

- 用 CUDA 流进行异步计算
- 让内存传输与计算重叠

## I 移植到 GPU（默认流）（Portage sur GPU – Stream par défaut）

> Le code source principal se situe dans la section CODE du présent TP. Le programme représente le calcul d’une fonction exponentielle sur un espace 1D.

主要源代码在本实验的 CODE 部分，程序在一维空间上计算一个指数函数。

### Q.1 把 func 移植到 GPU（Portage sur GPU）

> **Q.1 :** Portez la fonction « func » sur GPU, en configurant une grille 1D qui contient suffisamment de blocs et de threads pour couvrir l’ensemble du vecteur.

**题目：**把函数 `func` 移植到 GPU：配置一个一维网格，包含足够多的线程块和线程，覆盖整个向量。

> **Réponse :** Calculer `i=blockIdx.x*blockDim.x+threadIdx.x`, tester `i<N`, puis appliquer `func` à l’élément i. Le kernel est `__global__`, la grille contient `(N+threads-1)/threads` blocs.

**解答：**计算 `i=blockIdx.x*blockDim.x+threadIdx.x`，判断 `i<N`，然后对第 i 个元素执行 `func`。kernel 为 `__global__`，网格块数为 `(N+threads-1)/threads`。

## II 初始化流（Initialisation des Streams）

> Un flux (ou Stream) CUDA est une suite d’opérations qui sont exécutées selon l’ordre dans lequel elles sont appelées sur le GPU. Ce modèle de programmation est utilisé pour introduire de la concurrence sur le GPU :
> - Les opérations CUDA venant de différents flux peuvent s’exécuter de manière concurrente.
> - Les opérations CUDA entre différents flux peuvent être interchangées.
>
> Nous allons dans un premier temps créer et initialiser différents flux à partir du code réalisé lors de la question précédente.

CUDA 流（Stream）是一串按调用顺序在 GPU 上执行的操作。这种编程模型用于在 GPU 上引入并发：

- 来自不同流的 CUDA 操作可以并发执行；
- 不同流之间的 CUDA 操作可以交换先后。

我们先在上一题代码的基础上创建并初始化多个流。

### Q.2 创建并初始化 NSTREAMS 个流（Création des streams）

> **Q.2 :** Allouez un ensemble NSTREAMS de Streams CUDA et initialisez-les.

**题目：**分配一组共 NSTREAMS 个 CUDA 流，并初始化它们。

> **Réponse :** Créer NSTREAMS streams et donner à chacun une portion distincte. Sans quatrième paramètre de lancement, le stream par défaut est utilisé. Son mode legacy ajoute des dépendances avec les streams bloquants ; le mode par thread a d’autres règles. Un lancement de kernel n’est pas pour autant bloquant pour le CPU : ordre GPU et retour de l’appel hôte sont deux notions différentes.

**解答：**创建 NSTREAMS 个 stream，各处理互不相交的一段数据。省略启动语句第四个参数时使用默认 stream。legacy 模式与阻塞 stream 建立隐式依赖，per-thread 模式规则不同。kernel 启动不会因此变成对 CPU 的阻塞调用：GPU 操作顺序和主机调用返回是两个不同问题。

### Q.3 默认流（Stream par défaut）

> **Q.3 :** Sans spécifier de Stream sur lequel exécuter un kernel CUDA, quel stream est utilisé ? Quelle particularité a-t-il ?

**题目：**不指定在哪个流上执行 CUDA kernel 时，使用的是哪个流？它有什么特点？

> **Correction :** Le Stream par défaut est utilisé. Toutes les opérations CUDA sont synchrones sur ce flux, à l’exception de certaines opérations, telles que les lancements de kernels.

**教师解答：**使用默认流。在这个流上，除 kernel 启动等少数操作外，所有 CUDA 操作都是同步的。

> **译注：**说“所有操作都是同步的”不准确。默认流（legacy 模式）中的操作按提交顺序执行，并与其他阻塞流隐式同步；kernel 启动和 `cudaMemcpyAsync` 等对 CPU 仍是异步提交。用 `--default-stream per-thread` 编译时规则不同。

### Q.4 在不同的流上启动 kernel（Kernels sur plusieurs streams）

> **Q.4 :** Modifiez le lancement du kernel CUDA pour que NSTREAMS instances de ce kernel soient exécutées sur des Streams différents.

**题目：**修改 CUDA kernel 的启动方式，让这个 kernel 的 NSTREAMS 个实例在不同的流上执行。

> **Réponse :** Chaque stream traite un morceau disjoint du vecteur, `[begin, end[` pour le stream `s`, et le kernel reçoit le stream en quatrième paramètre de lancement : `func_kernel<<<blocks, threads, 0, streams[s]>>>(...)`. Ne pas faire traiter le vecteur entier par chacune des NSTREAMS instances : le travail serait multiplié et les écritures entreraient en conflit. Le code est donné en Q.6.

**解答：**每个流处理向量中互不相交的一段：第 `s` 个流处理 `[begin, end)`，启动时用第四个参数指定流：`func_kernel<<<blocks, threads, 0, streams[s]>>>(...)`。不能让 NSTREAMS 个实例各自处理整个向量，否则工作量成倍增加，写入还会相互冲突。代码见 Q.6。

### Q.5 性能观察（Performances observées）

> **Q.5 :** Qu’observez-vous au niveau des performances ? Pourquoi et comment les résoudre ?

**题目：**性能方面你观察到什么？原因是什么，怎样解决？

> **Correction :** Bien que les kernels s’exécutent de manière concurrente, les copies de données vers et depuis le device se font d’un seul bloc synchrone. Pour améliorer les performances, les copies doivent être asynchrones, il faut donc utiliser la fonction `cudaMemcpyAsync` ; elles pourront alors être recouvertes par du calcul.

**教师解答：**虽然 kernel 是并发执行的，但与设备之间的数据复制是整块同步完成的。要提高性能，复制必须是异步的，所以要用 `cudaMemcpyAsync`，这样复制才能与计算重叠。

> Plusieurs kernels ne garantissent pas le recouvrement : copies bloquantes, mémoire pageable, GPU saturé, petits morceaux et coût des lancements peuvent limiter le gain. Ne pas traiter le vecteur entier NSTREAMS fois, ce qui augmenterait le travail et pourrait créer des courses.

多个 kernel 不保证重叠：阻塞复制、可分页内存、GPU 饱和、分段过小或启动开销，都可能限制收益。不能让 NSTREAMS 个 kernel 各处理整个向量，否则会增加工作量，还可能造成竞争。

### Q.6 异步复制（Copies asynchrones）

> **Q.6 :** Utilisez la fonction `cudaMemcpyAsync` pour effectuer les copies mémoires vers et depuis le GPU. Quel effet a cette fonction ?
>
> NB : n’oubliez pas de synchroniser le host et le device avant de faire la vérification du résultat avec `cudaDeviceSynchronize` pour éviter toute corruption mémoire.

**题目：**用 `cudaMemcpyAsync` 完成与 GPU 之间的内存复制。这个函数有什么作用？

注：在检查结果之前，别忘了用 `cudaDeviceSynchronize` 同步主机和设备，以免内存数据被破坏。

> **Réponse :** `cudaMemcpyAsync` place la copie dans un stream. Pour permettre le recouvrement H2D/D2H usuel, allouer les buffers hôte avec `cudaMallocHost`, puis utiliser `cudaFreeHost`. Ne pas lire un résultat ou modifier une source avant la fin du transfert. Le matériel et les ressources disponibles conditionnent aussi le recouvrement.

**解答：**`cudaMemcpyAsync` 将复制排入 stream。为支持通常的 H2D/D2H 重叠，主机缓冲区用 `cudaMallocHost` 分配，以 `cudaFreeHost` 释放。传输结束前不能读取结果或改动源数据。实际重叠还受硬件和可用资源约束。

```cpp
cudaStream_t streams[NSTREAMS];
for (int s = 0; s < NSTREAMS; ++s)
    CUDA_CHECK(cudaStreamCreate(&streams[s]));
for (int s = 0; s < NSTREAMS; ++s) {
    size_t begin = (size_t)s * total / NSTREAMS;
    size_t end = (size_t)(s+1) * total / NSTREAMS;
    size_t count = end - begin;
    if (count == 0) continue;
    size_t bytes = count * sizeof(double);
    CUDA_CHECK(cudaMemcpyAsync(d_in+begin, h_in+begin, bytes,
                               cudaMemcpyHostToDevice, streams[s]));
    func_kernel<<<(count+255)/256, 256, 0, streams[s]>>>(
        d_in+begin, d_out+begin, count);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaMemcpyAsync(h_out+begin, d_out+begin, bytes,
                               cudaMemcpyDeviceToHost, streams[s]));
}
for (int s = 0; s < NSTREAMS; ++s)
    CUDA_CHECK(cudaStreamSynchronize(streams[s]));
// Check results, then release buffers after all their users have finished.
for (int s = 0; s < NSTREAMS; ++s)
    CUDA_CHECK(cudaStreamDestroy(streams[s]));
```

> Les buffers sont alloués avant l’extrait ; définir `func_kernel` à partir du source manquant. Les bornes par quotient traitent aussi le reste si `total` n’est pas divisible par NSTREAMS.

片段之前应完成缓冲区分配；`func_kernel` 按缺失的原程序定义。用商计算分段起止位置，也能处理 `total` 不能被 NSTREAMS 整除的余数。

### Q.7 cudaMallocHost 的作用（`cudaMallocHost`）

> **Q.7 :** À quoi sert la fonction `cudaMallocHost` ? Modifiez votre code en conséquence.

**题目：**`cudaMallocHost` 有什么用？据此修改代码。

> **Correction :** La copie asynchrone utilise un mécanisme DMA (Direct Memory Access). Le GPU a alors connaissance de l’adresse physique du tableau sur l’hôte. Par conséquent, celui-ci ne doit pas migrer la page physique au cours de son utilisation. D’où l’utilisation de mémoire punaisée (pinned memory). `cudaMallocHost` permet d’allouer de la mémoire punaisée dans la mémoire de l’hôte. L’appel système `malloc` ne permet pas d’allouer ce type de mémoire et est à proscrire lors de l’utilisation de copie asynchrone entre l’hôte et le GPU.

**教师解答：**异步复制使用 DMA（直接内存访问）机制，此时 GPU 知道主机上数组的物理地址，因此在使用期间这些物理页不能被迁移，所以要用锁页内存（pinned memory）。`cudaMallocHost` 用于在主机内存中分配锁页内存。系统调用 `malloc` 不能分配这种内存，在主机与 GPU 之间做异步复制时不应使用。

### Q.8 同步调用与异步调用（Appels synchrones et asynchrones）

> **Q.8 :** Classer les fonctions et les appels de kernels en deux catégories : les synchrones et les asynchrones.

**题目：**把这些函数和 kernel 调用分成两类：同步的和异步的。

> **Correction :**

**教师解答：**

| 同步调用（appel synchrone） | 异步调用（appel asynchrone） |
|---|---|
| `cudaMalloc`, `cudaFree` | `cudaMallocAsync` |
| `cudaMallocHost`, `cudaFreeHost` | `cudaFreeAsync` |
| `cudaStreamCreate`, `cudaStreamDestroy` | `cudaMemcpyAsync` |
| `cudaDeviceSynchronize` | `MyKernel` |

> **译注：**这张二分类表不是完整的 API 保证：`cudaEventRecord` 也是异步提交；`cudaStreamSynchronize`、`cudaEventSynchronize` 分别等待对应范围；D2H 的 `cudaMemcpy` 返回前保证主机数据可用；`cudaStreamDestroy` 可能在流中任务未完成时就返回，不能当作等待；传统的分配、释放可能引入同步，应放在流水循环之外。

### Q.9 两个流的依赖图（Graphe de dépendances）

> **Q.9 :** En fixant NSTREAMS = 2, dessiner un schéma représentant les différentes tâches sur les flux d’exécution ainsi que leurs dépendances. Nous prendrons comme notation :
> - A → B : l’exécution de B ne peut commencer tant que celle de A n’est pas terminée.
> - A ⇒ B : l’exécution de B ne peut se terminer tant que celle de A n’est pas terminée.
>
> Liste des tâches : création S0, création S1, Malloc Host, Thread Sync ; pour chaque moitié [0,N[ et [N,2N[ : requête et exécution de cpy H→D, de K1 et de cpy D→H.

**题目：**取 NSTREAMS = 2，画图表示各执行流上的任务及其依赖。记号约定：

- A → B：A 执行完之前，B 不能开始执行。
- A ⇒ B：A 执行完之前，B 不能结束执行。

任务列表：创建 S0、创建 S1、Malloc Host、Thread Sync；对两半数据 [0,N[ 和 [N,2N[ 各有：H→D 复制、K1、D→H 复制的“请求”和“执行”。

> **Correction :** Voir `graph.pdf`, où la flèche verte correspond à A ⇒ B.

**教师解答：**见 `graph.pdf`，其中绿色箭头表示 A ⇒ B（本地没有这个文件）。

> **Réponse :** Créations et allocations précèdent les soumissions. Une requête CPU précède l’opération GPU associée. Avec la notation du sujet, D2H $\Rightarrow$ fin de synchronisation. Les morceaux distincts n’imposent pas de dépendance entre les deux lignes ; le matériel peut pourtant les sérialiser.

**解答：**创建和分配先于提交，CPU 请求先于对应 GPU 操作。按题目记号，D2H $\Rightarrow$ 同步结束。互不相交的分段没有跨行数据依赖，但硬件仍可能将操作串行执行。

```text
S0 : H2D [0,N[  --> K0 [0,N[  --> D2H [0,N[  ----+
                                                 +--> wait --> CPU check
S1 : H2D [N,2N[ --> K1 [N,2N[ --> D2H [N,2N[ ----+
```

## III 时间测量（Mesure de temps）

### Q.10 用 gettimeofday 测程序时间（Temps du programme）

> **Q.10 :** Utiliser la fonction système `gettimeofday` pour mesurer le temps passé dans l’exécution du programme CUDA.

**题目：**用系统函数 `gettimeofday` 测量 CUDA 程序的执行时间。

> **Correction :** Voir le programme `stream_ex1_gettimeofday.cu` pour la correction.

**教师解答：**见程序 `stream_ex1_gettimeofday.cu`（本地没有这个文件）。

> **Réponse :** Prendre `gettimeofday` avant les opérations mesurées, attendre tous les travaux après leur soumission, puis prendre le temps final. Sans attente, on mesure la soumission. Convertir `Δt=(sec_fin-sec_debut)+1e-6*(usec_fin-usec_debut)` et annoncer si allocations et transferts sont inclus. Hors contrainte du sujet, une horloge monotone évite les ajustements d’heure système.

**解答：**被测操作前调用 `gettimeofday`，提交后等待所有任务，再取结束时间。不等待只能测到提交。换算 `Δt=(sec_fin-sec_debut)+1e-6*(usec_fin-usec_debut)`，并说明是否含分配和传输。不受题目限定时，单调时钟可避免系统时间调整的影响。

### Q.11 只测 kernel 的总时间（Temps total des kernels）

> **Q.11 :** Avec les fonctions `gettimeofday` et `cudaDeviceSynchronize`, mesurer le temps total d’exécution des kernels uniquement (sans compter le temps des transferts mémoire, etc.). Ici, on demande le temps total, pas le temps individuel des kernels.

**题目：**用 `gettimeofday` 和 `cudaDeviceSynchronize` 只测 kernel 的总执行时间（不含内存传输等时间）。这里要的是总时间，不是每个 kernel 各自的时间。

> **Correction :** Voir le programme `stream_ex1_kernels_gettimeofday.cu` pour la correction.

**教师解答：**见程序 `stream_ex1_kernels_gettimeofday.cu`（本地没有这个文件）。

> **Réponse :** Effectuer les H2D, appeler `cudaDeviceSynchronize`, prendre t0, soumettre tous les kernels, appeler `cudaDeviceSynchronize`, prendre t1, puis effectuer les D2H. `t1-t0` est la durée globale de cette phase, pas la somme des durées individuelles.

**解答：**先 H2D，调用 `cudaDeviceSynchronize`，记 t0，提交所有 kernel，调用 `cudaDeviceSynchronize`，记 t1，最后 D2H。`t1-t0` 是计算阶段的整体时长，不是各 kernel 时间之和。

### Q.12 这种测法的代价（Inconvénient de cette mesure）

> **Q.12 :** Quel est l’impact (inconvénient) sur l’exécution générale du programme de cette dernière façon de mesurer ? Vous pouvez vous aider du graphe de dépendance précédent et l’enrichir.

**题目：**上一种测量方法对程序的整体执行有什么影响（缺点）？可以借助并扩充前面的依赖图。

> **Correction :** Les appels à `cudaDeviceSynchronize` imposent 2 points de synchronisation entre les streams, introduisant ainsi une sérialisation des étapes : on effectue d’abord toutes les copies sur tous les streams, puis on exécute tous les kernels et enfin on termine par toutes les copies. On perd l’intérêt d’utiliser les copies asynchrones et l’exécution concurrente des kernels.

**教师解答：**调用 `cudaDeviceSynchronize` 会在各流之间加入 2 个同步点，使各阶段串行化：先完成所有流上的所有复制，再执行所有 kernel，最后完成所有回传复制。这样就失去了异步复制和 kernel 并发执行的好处。

> **译注：**两次屏障确实把传输和计算分成了独立阶段，破坏两者的重叠；但如果第二次屏障前提交了全部 kernel，这些 kernel 之间仍可能并发，所以“kernel 并发执行的好处也失去了”说得过头。

### Q.13 测每个 kernel 的时间（Temps de chaque kernel）

> **Q.13 :** Comment mesurer le temps de chacun des kernels avec la technique précédente ?

**题目：**用前面的方法，怎样测量每个 kernel 的时间？

> **Correction :** Si l’on ne dispose que de `cudaDeviceSynchronize` et de `gettimeofday` pour mesurer le temps de chaque kernel de chaque stream, alors on est obligé d’exécuter les streams les uns après les autres en forçant une synchronisation et un relevé de temps entre chaque stream. Il n’y a plus d’exécution concurrente entre kernels : ils s’exécutent les uns après les autres. Voir fichier `stream_ex1_onekernel_gettimeofday.cu`.

**教师解答：**如果只用 `cudaDeviceSynchronize` 和 `gettimeofday` 测每个流中每个 kernel 的时间，就只能让各流依次执行，在每个流之间强制同步并记录时间。kernel 之间不再并发，而是一个接一个执行。见文件 `stream_ex1_onekernel_gettimeofday.cu`（本地没有）。

### Q.14 用事件计时（Mesure avec les événements）

> **Q.14 :** Comment utiliser les événements (fonctions `cudaEvent*`) pour mesurer le temps de chaque kernel et le temps total de tous les kernels ? Commentaire par rapport à la façon précédente ?

**题目：**怎样用事件（`cudaEvent*` 函数）测量每个 kernel 的时间以及所有 kernel 的总时间？与前一种方法相比如何？

> **Correction :** Les appels à `cudaEventRecord` permettent de positionner les événements dans le flux séquentiel d’un stream. On peut ainsi marquer le début et la fin de l’exécution d’un kernel au sein d’un stream sans synchroniser les streams entre eux. La fonction `cudaEventSynchronize` permet d’attendre l’exécution réelle d’un événement. Voir fichier `stream_ex1_events.cu`.

**教师解答：**`cudaEventRecord` 把事件放进某个流的顺序执行序列中，这样就能在流内部标记一个 kernel 执行的开始和结束，而不必让各流相互同步。`cudaEventSynchronize` 用于等待事件真正执行到。见文件 `stream_ex1_events.cu`（本地没有）。

> Placer `start[s]` et `stop[s]` autour du kernel dans chaque stream s, attendre les événements finaux, calculer les durées. Ne pas les additionner pour obtenir la durée globale en présence de recouvrement. Pour mesurer l’enveloppe de tous les kernels à partir d’un début commun, utiliser un stream de coordination :

每个 stream s 内用 `start[s]`、`stop[s]` 包围 kernel，等待结束事件后算各自时间。存在重叠时，不能把这些时间相加作为总时间。可用协调 stream，从共同起点测量所有 kernel 的整体范围：

```text
Complete H2D before this kernel-only experiment.
Record global_start in coordination stream.
For every stream s:
    wait(global_start) in s
    record start[s] in s
    launch kernel[s] in s
    record stop[s] in s
For every stream s:
    wait(stop[s]) in coordination stream
Record global_stop in coordination stream.
Wait on global_stop at the host.
Elapsed(global_start,global_stop) = total kernel-phase duration.
Elapsed(start[s],stop[s]) = duration observed for kernel s.
```

> Utiliser `cudaStreamWaitEvent` pour les attentes et `cudaEventElapsedTime` pour les durées. Le début commun ajoute une contrainte : annoncer une phase « kernels seuls ». Pour mesurer le pipeline réel, conserver son ordre et mesurer son temps complet séparément. Un kernel sous concurrence peut durer plus longtemps qu’un kernel isolé.

stream 间等待使用 `cudaStreamWaitEvent`，时长计算使用 `cudaEventElapsedTime`。共同起点增加了依赖约束，应明确这是“只测 kernel”的阶段。测真实流水线时保留原顺序，另测完整时间。并发时一个 kernel 也可能比单独运行时更慢。

## IV 矩阵乘法（Multiplication matricielle）

### Q.15 多流矩阵乘法（GEMM multi-streams）

> **Q.15 :** Reprenez l’exercice de multiplication matricielle du TP1 et transformez le code pour le rendre multi-streams. Dans ce cas, un stream s’occupera d’un paquet de lignes à traiter. Essayez d’abord avec le kernel « coalescé » puis avec le kernel de multiplication par tuiles. Quels sont vos gains de performances par rapport à la version synchrone ?

**题目：**用 TP1 的矩阵乘法，把代码改成多流版本：每个流负责一批行。先用“合并访存”kernel 试，再用分块 kernel 试。与同步版本相比，性能提升多少？

> **Correction :** Voir `dgemm_async.cu`. Sur un GPU Quadro P5000 (driver 560.35.03 et CUDA 12.6), avec N = 4096 et N_STREAMS = 4 : pour des FP64, la version coalescée se fait en 0,80 s, soit 172 GFLOP/s ; la version par tuiles en 1,02 s, soit 135 GFLOP/s, donc environ 1,5 fois plus rapide que la version synchrone. Pour des FP32, la version coalescée se fait en 0,50 s, soit 273 GFLOP/s ; la version par tuiles en 0,18 s, soit 760 GFLOP/s, donc environ 1,3 fois plus rapide que la version synchrone.

**教师解答：**见 `dgemm_async.cu`（本地没有）。在 Quadro P5000（驱动 560.35.03，CUDA 12.6）上，N = 4096，N_STREAMS = 4：FP64 合并访存版本 0.80 s（172 GFLOP/s），分块版本 1.02 s（135 GFLOP/s），比同步版本快约 1.5 倍；FP32 合并访存版本 0.50 s（273 GFLOP/s），分块版本 0.18 s（760 GFLOP/s），比同步版本快约 1.3 倍。

> **译注：**按老师在[往年 TP1](tp1_correction.md) Q.21 给出的同一块 GPU 上的同步版时间（合并访存 FP64 1.31 s、FP32 0.88 s；分块 FP64 1.20 s、FP32 0.23 s），多流后的加速比为：FP64 合并访存约 1.6 倍、分块约 1.2 倍；FP32 合并访存约 1.8 倍、分块约 1.3 倍。原文 FP64 的“约 1.5 倍”与分块版本对不上。另外 FP64 下多流分块版本（135 GFLOP/s）反而比多流合并访存版本（172 GFLOP/s）慢。

> Découper A et C en paquets de lignes. Chaque stream transfère son A et son C initial si `β≠0`, calcule ses lignes, puis rapatrie son C. Tous les paquets utilisent **B entier** : le transférer une fois avant le pipeline et rendre cette disponibilité visible dans tous les streams. Adapter l’indice de ligne global ou passer des pointeurs décalés avec un nombre local de lignes ; conserver les gardes du kernel tuilé. Avec le kernel exact de 4.10, initialiser aussi C lorsque `beta=0`, ou modifier le calcul final pour qu’une branche `beta==0` écrive `alpha*sum` sans lire C ; sans cette adaptation, supprimer la copie de C laisserait une lecture de données non initialisées.

把 A、C 按行分包。每个 stream 传输自己的 A；`β≠0` 时也传输 C 初值；计算这些行，再回传 C。所有分包都需要**完整的 B**，因此在流水线前传一次 B，并保证所有 stream 等到它就绪。可使用全局行偏移，或传入偏移指针和局部行数；分块 kernel 仍要处理边界。若直接使用 4.10 的 kernel，`beta=0` 时也须初始化 C，或者把最终写入改成 `beta==0` 分支直接写 `alpha*sum`、不读取 C；没有这一修改就省略 C 的复制，会读取未初始化数据。

> Comparer coalescence et tuilage à données et périmètres égaux. Accélérer les transferts ne garantit pas un gain lorsque le GPU est déjà saturé. Les chiffres P5000 du corrigé ne prédisent pas un résultat GH200.

用相同输入和计时范围比较合并访问与分块版本。GPU 已饱和时，改善传输不保证加速。旧解答的 P5000 数字不能预测 GH200 的结果。
