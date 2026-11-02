# TD2：CUDA 入门——用 Monte Carlo 方法近似 π（Prise en main de CUDA – Approximation de π）

原题：[td2.pdf](td2.pdf) · CPU 代码：[pi.c](../CODE/pi.c) · [Makefile](../CODE/Makefile)

> Les objectifs de ce TD sont :
> - Configuration d’une grille simple
> - Écriture d’un premier kernel CUDA
> - Allocation mémoire sur l’accélérateur

本次习题课的目标：

- 配置一个简单的网格
- 编写第一个 CUDA kernel
- 在加速器上分配内存

## I 问题描述（Description du problème）

> Le calcul de π est un problème fréquemment étudié pour l’apprentissage du parallélisme. L’une des méthodes les plus courantes est la méthode approchée de type Monte Carlo.
>
> On construit un carré de côté c = 1 et de centre O. En ce même centre, nous traçons un cercle de rayon r = 1. Pour comprendre la procédure d’approximation de π, nous avons besoin de connaître l’aire de ce cercle via la formule $A=\pi r^2$. Dans notre cas, nous obtenons $A=\pi$.

计算 π 是学习并行编程时经常研究的问题，最常见的方法之一是 Monte Carlo 近似法。

作一个边长 $c=1$、中心为 O 的正方形，再以同一中心画一个半径 $r=1$ 的圆。要理解 π 的近似过程，需要用 $A=\pi r^2$ 求这个圆的面积；这里 $A=\pi$。

> Intéressons-nous uniquement à un quart de la figure. Imaginons maintenant que l’on joue à un jeu de fléchettes, et que l’on prend cette figure pour cible. La méthode de Monte Carlo consiste à prendre un nombre infini de fléchettes et de les lancer de manière aléatoire en direction de la cible. Par conséquent, le nombre de fléchettes se trouvant dans le cercle tendra vers l’aire du quart de cercle. En pratique, P se calcule comme le nombre de fléchettes dans le cercle divisé par le nombre total de fléchettes, d’où l’approximation de π.
>
> Pour finir cet algorithme, il nous reste donc à vérifier après un tir si la fléchette se trouve dans le quart de cercle de la cible. Un point a de coordonnées (x, y) se trouve à l’intérieur du quart de cercle si la distance qui le sépare de l’origine O(0, 0) est inférieure ou égale à 1, soit $x^2+y^2\le1$ (cf. théorème de Pythagore).

只看图形的四分之一。设想玩掷飞镖游戏，把这张图当作靶子。Monte Carlo 方法就是向靶子随机投出无穷多支飞镖，于是落在圆内的飞镖比例趋近于四分之一圆的面积。实际计算时，P 等于落在圆内的飞镖数除以飞镖总数，由此得到 π 的近似值。

算法的最后一步是每投一次就判断飞镖是否落在四分之一圆内：坐标为 (x, y) 的点 a 到原点 O(0, 0) 的距离不超过 1，即 $x^2+y^2\le1$ 时（勾股定理），它位于四分之一圆内。

$$
P\simeq\frac A4=\frac\pi4,\qquad P=\frac{H}{T},\qquad \pi\simeq4\,\frac HT
$$

> $H$ : nombre de fléchettes dans le cercle ; $T$ : nombre total de fléchettes. Les figures 1 à 3 (distribution des points, quart de cercle cible) sont dans le PDF du sujet.

$H$：落在圆内的飞镖数；$T$：飞镖总数。图 1–3（点的分布、作为靶子的四分之一圆）见原题 PDF。

> **译注：**开头“边长为 1 的正方形与同心、半径为 1 的圆”在几何上对不上：半径为 1 的圆比边长为 1 的正方形大。算法实际是在单位正方形 $[0,1]\times[0,1]$ 中均匀取点，统计满足 $x^2+y^2\le1$ 的点；四分之一圆面积为 $\pi/4$，正方形面积为 1。

$$
\widehat\pi=4\frac{H}{T},\qquad
\operatorname{SE}(\widehat\pi)=4\sqrt{\frac{p(1-p)}T},\quad p=\frac\pi4.
$$

> L’erreur statistique typique décroît comme `1/sqrt(T)` sous l’hypothèse de tirages indépendants. Multiplier le nombre de tirs par 100 réduit cette échelle d’erreur d’un facteur 10, pas 100.

在独立采样假设下，典型统计误差按 `1/sqrt(T)` 缩小。采样数增加 100 倍，误差尺度约缩小 10 倍，而不是 100 倍。

## II 问题转化（Transposition du problème）

### Q.1 串行 C 程序（Version séquentielle）

> **Q.1 :** A l’aide de la description du problème dans la section précédente, écrire un programme séquentiel en C qui permet de calculer l’approximation de π par la méthode de Monte Carlo.

**题目：**根据上一节对问题的描述，用 C 编写一个串行程序，用 Monte Carlo 方法计算 π 的近似值。

> **Réponse :** Le fichier [pi.c](../CODE/pi.c) contient déjà cette boucle. `10E7` signifie **100 000 000** tirs, pas dix millions.

**解答：**[pi.c](../CODE/pi.c) 已有这一循环。注意 `10E7` 表示 **100 000 000** 次采样，不是一千万次。

```c
uint64_t hits = 0;
srand(2026);
for (uint64_t trial = 0; trial < trials; ++trial) {
    double x = rand() / (double)RAND_MAX;
    double y = rand() / (double)RAND_MAX;
    if (x * x + y * y <= 1.0) ++hits;
}
double pi = 4.0 * (double)hits / (double)trials;
```

### Q.2 OpenMP 多线程版本（Version multi-thread）

> **Q.2 :** Proposer une version parallèle du code précédent écrite avec OpenMP. Pour ce faire, chaque thread lancera un nombre `TRIALS_PER_THREAD` de fléchettes et stockera localement son résultat partiel de π dans un tableau accessible par tous les threads. La moyenne des différentes valeurs trouvées sera ensuite calculée sur le thread principal et donnera ainsi la valeur finale estimée de π.

**题目：**给出上述代码用 OpenMP 编写的并行版本。每个线程投掷 `TRIALS_PER_THREAD` 支飞镖，把自己得到的 π 的部分结果存入一个所有线程都能访问的数组；随后在主线程上求这些值的平均，作为 π 的最终估计值。

> **Réponse :** Chaque thread effectue `trials_per_thread` tirs, écrit une estimation dans sa case, puis le thread principal prend la moyenne. Il faut un état aléatoire **privé**, pas des appels concurrents à un générateur global partagé. Exemple pédagogique C/POSIX pour Linux (`stdlib.h`, `stdint.h`, `omp.h`) :
>
> `rand_r` est une solution pédagogique POSIX, pas une preuve de qualité ou d’indépendance statistique des flux. La fin de la région parallèle garantit que le tableau est rempli. La moyenne simple est correcte parce que tous les threads font le même nombre de tirs ; sinon, additionner les nombres de succès et de tirs, puis calculer `4*sum(hits)/sum(trials)`.

**解答：**每个线程进行 `trials_per_thread` 次采样，把估计值写入自己的数组元素，再由主线程求平均。随机数生成器的状态必须是**线程私有**的，不能让线程竞争同一个全局状态。下面给出适用于 Linux 的 C/POSIX 教学片段，需要 `stdlib.h`、`stdint.h`、`omp.h`：

`rand_r` 是 POSIX 教学用法，不能据此证明随机序列的质量或统计独立性。并行区域结束时，所有线程已经完成写入。各线程采样数相同，所以可以直接平均；若采样数不同，应汇总命中数和总采样数，再计算 `4*sum(hits)/sum(trials)`。

```c
int capacity = omp_get_max_threads(), used = 0;
double *partial = malloc((size_t)capacity * sizeof(*partial));
#pragma omp parallel shared(partial, used)
{
    int tid = omp_get_thread_num();
    unsigned int state = 2026u + 104729u * (unsigned int)tid;
    uint64_t hits = 0;
    #pragma omp single
    used = omp_get_num_threads();
    for (uint64_t trial = 0; trial < trials_per_thread; ++trial) {
        double x = rand_r(&state) / (double)RAND_MAX;
        double y = rand_r(&state) / (double)RAND_MAX;
        if (x*x + y*y <= 1.0) ++hits;
    }
    partial[tid] = 4.0 * hits / trials_per_thread;
}
double pi = 0.0;
for (int tid = 0; tid < used; ++tid) pi += partial[tid];
pi /= used;
free(partial);
```

## III CUDA 入门（Prise en main avec CUDA）

> Les méthodes de type Monte Carlo se prêtent très bien aux accélérateurs de calculs type GPGPU car chaque thread exécute les mêmes suites d’instructions, sur des données différentes. Nous allons voir maintenant comment porter ce programme sur un accélérateur de ce type en utilisant le SDK CUDA.

Monte Carlo 类方法很适合 GPGPU 这类计算加速器，因为每个线程执行相同的指令序列，只是处理的数据不同。下面用 CUDA SDK 把这个程序移植到这类加速器上。

### Q.3 网格配置（Configuration de la grille）

> **Q.3 :** Pour ce problème, nous allons utiliser une grille 1D pour lancer un grand nombre de threads en simultané. Proposer une configuration de kernel qui s’exécutera sur 512 blocs contenant chacun 256 threads.

**题目：**本问题使用一维网格同时启动大量线程。给出一个在 512 个线程块上执行、每块含 256 个线程的 kernel 配置。

> **Réponse :** `512` blocs de `256` threads donnent **131 072 threads**. Avec `R=TRIALS_PER_THREAD`, le nombre total de tirs est `131072*R`.

**解答：**`512` 个块，每块 `256` 个线程，共 **131 072 个线程**。若 `R=TRIALS_PER_THREAD`，总采样数为 `131072*R`。

### Q.4 设备内存分配（Allocation mémoire）

> **Q.4 :** A l’instar de la version OpenMP, nous allons calculer un résultat de π par thread CUDA. Ce résultat doit être stocké en mémoire sur le GPU pour pouvoir être ensuite utilisé côté hôte pour faire la moyenne des valeurs de π trouvées. A l’aide des fonctions du SDK CUDA, allouer un vecteur sur la mémoire du device qui permettra de stocker chaque résultat partiel.

**题目：**和 OpenMP 版本一样，每个 CUDA 线程计算一个 π 的结果。这个结果要存放在 GPU 内存中，之后在主机端用来求所有 π 值的平均。用 CUDA SDK 的函数在设备内存上分配一个向量，用于存放各个部分结果。

> **Réponse :** Allouer le vecteur avec `cudaMalloc((void **)&d_partial, bytes)`. Un `double` par thread nécessite `131072*8=1048576` octets, soit **1 MiB**.

**解答：**用 `cudaMalloc((void **)&d_partial, bytes)` 分配。每线程存一个 `double`，共 `131072*8=1048576` 字节，即 **1 MiB**。

### Q.5 把结果复制回主机（Rapatriement des résultats）

> **Q.5 :** Les résultats partiels doivent être manipulés par l’hôte après l’exécution des threads pour faire la moyenne de ceux-ci. Toujours à l’aide des fonctions du SDK CUDA, donner la fonction qui permet de copier les données de l’accélérateur vers le CPU, ainsi que sa position relative dans le code.

**题目：**线程执行完毕后，主机要处理这些部分结果并求平均。仍用 CUDA SDK 的函数，给出把数据从加速器复制到 CPU 的函数，以及它在代码中的相对位置。

> **Réponse :** `cudaMemcpy(h_partial, d_partial, bytes, cudaMemcpyDeviceToHost)`. La copie D2H se place après le lancement du kernel ; dans le même stream, elle permet ensuite le calcul CPU de la moyenne. Le code hôte ci-dessous couvre Q.3 à Q.5.

**解答：**用 `cudaMemcpy(h_partial, d_partial, bytes, cudaMemcpyDeviceToHost)`，放在 kernel 启动之后；同一 stream 中的先后顺序保证随后可以在 CPU 求平均。下面的主机端代码同时对应 Q.3–Q.5。

```cpp
const int blocks = 512, threads = 256;
const int count = blocks * threads;
size_t bytes = (size_t)count * sizeof(double);
double *d_partial;
double *h_partial = (double *)malloc(bytes);
CUDA_CHECK(cudaMalloc((void **)&d_partial, bytes));
monte_carlo<<<blocks, threads>>>(d_partial, trials_per_thread, 2026ULL);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaMemcpy(h_partial, d_partial, bytes, cudaMemcpyDeviceToHost));
double pi = 0.0;
for (int i = 0; i < count; ++i) pi += h_partial[i];
pi /= count;
CUDA_CHECK(cudaFree(d_partial));
free(h_partial);
```

### Q.6 编写 kernel（Écriture du kernel）

> **Q.6 :** Passons maintenant à l’écriture du kernel qui s’exécutera sur l’accélérateur de calculs. Pour chaque lancer de fléchette, un thread CUDA doit générer deux nombres aléatoires : x pour l’ordonnée, et y pour l’abscisse. A l’aide de la description du problème, écrire le kernel CUDA correspondant. Un thread doit lancer `TRIALS_PER_THREAD` fléchettes, compter le nombre de fléchettes qui se trouve dans le quart de cercle, et ainsi en déduire une approximation de π. Cette valeur approchée sera ensuite stockée dans une case du vecteur allouée précédemment sur le GPU.
>
> NB : La génération de nombres aléatoires avec CUDA se fait via la bibliothèque Curand. Les fonctions utiles à cette question sont définies dans le header `curand_kernel.h`. L’initialisation de la graine se fait avec la méthode `unsigned int curand_init(unsigned long long seed, unsigned long long sequence, unsigned long long offset, curandState_t state)`. La génération d’un nombre aléatoire dans l’intervalle [0, 1] se fait ensuite avec la méthode `float curand_uniform(curandState_t state)`.

**题目：**现在编写在计算加速器上执行的 kernel。每投一支飞镖，一个 CUDA 线程要生成两个随机数：x 作纵坐标，y 作横坐标。根据问题描述写出相应的 CUDA kernel：一个线程投掷 `TRIALS_PER_THREAD` 支飞镖，统计落在四分之一圆内的数量，由此推出 π 的近似值，并把它存入前面在 GPU 上分配的向量的一个元素中。

注：CUDA 中用 cuRAND 库生成随机数，本题需要的函数定义在头文件 `curand_kernel.h` 中。题目给出的种子初始化函数为 `unsigned int curand_init(unsigned long long seed, unsigned long long sequence, unsigned long long offset, curandState_t state)`，在 [0, 1] 内生成随机数的函数为 `float curand_uniform(curandState_t state)`。

> **译注：**原题有两处笔误：一是 x、y 的横纵坐标说反了，x 通常是横坐标；二是 cuRAND 函数原型不完整，实际签名为 `void curand_init(unsigned long long seed, unsigned long long subsequence, unsigned long long offset, curandState_t *state)` 和 `float curand_uniform(curandState_t *state)`，状态参数是指针，`curand_uniform` 的取值区间是 (0, 1]。

> **Réponse :** Un état cuRAND local par thread et une séquence identifiée par `tid` évitent de donner exactement les mêmes tirs à tous les threads. Définir le kernel avant le code de lancement :
>
> Exiger `trials>0`. Les API prennent un **pointeur d’état** ; le prototype donné dans le sujet est incomplet. `curand_init` retourne `void`, et les fonctions uniformes de cuRAND produisent des valeurs dans `(0,1]`. Cette convention discrète n’invalide pas le modèle du quart de disque. Avec des générateurs CPU et GPU différents, on ne demande pas l’égalité bit à bit des estimations de π : vérifier le compte total, la plage `[0,4]`, la reproductibilité à configuration fixée et le comportement statistique.

**解答：**每个线程使用局部 cuRAND 状态，以 `tid` 区分序列，避免所有线程生成完全相同的采样。下面的 kernel 应定义在启动代码之前：

要求 `trials>0`。API 接收的是**状态指针**；原题给出的函数原型不完整。`curand_init` 的返回类型是 `void`，cuRAND 的均匀随机函数取值范围是 `(0,1]`。这种离散端点约定不改变四分之一圆的建模方法。CPU 和 GPU 若使用不同随机数生成器，不要求 π 估计值逐位相等；应检查采样总数、结果是否位于 `[0,4]`、固定配置下能否复现，以及统计误差的变化。

```cpp
#include <curand_kernel.h>
__global__ void monte_carlo(double *partial, unsigned long long trials,
                            unsigned long long seed) {
    unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;
    curandStatePhilox4_32_10_t state;
    curand_init(seed, (unsigned long long)tid, 0ULL, &state);
    unsigned long long hits = 0;
    for (unsigned long long trial = 0; trial < trials; ++trial) {
        double x = curand_uniform_double(&state);
        double y = curand_uniform_double(&state);
        if (x*x + y*y <= 1.0) ++hits;
    }
    partial[tid] = 4.0 * (double)hits / (double)trials;
}
```
