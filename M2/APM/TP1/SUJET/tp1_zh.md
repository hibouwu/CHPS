# APM — TP1：内存访问优化（optimisation des accès mémoire）

> **M2 — Architecture et programmation d’accélérateurs matériels, 2026–2027**  
> Université de Versailles Saint-Quentin-en-Yvelines — Université Paris-Saclay  
> **Enseignant :** adrien.roussel@cea.fr  
> **Sous-titre du sujet :** utilisation de la mémoire partagée

**M2 — 硬件加速器体系结构与编程，2026–2027 学年**  
凡尔赛圣康坦昂伊夫林大学 — 巴黎萨克雷大学  
**教师：** adrien.roussel@cea.fr  
**原题副标题：** 共享内存的使用

原题：[tp1.pdf](tp1.pdf) · [法语版](tp1.md) · 代码：[Partie1](../CODE/Partie1/) · [Partie2](../CODE/Partie2/) · [实测记录](../RESULTS/)

## 实验目标与说明（Objectifs et conventions）

> L’objectif de ce TP est de comprendre les différentes mémoires d’un GPU et leur utilisation pour un calcul classique d’algèbre linéaire : le produit matriciel. Le sujet annonce la mémoire globale, la mémoire partagée, la mémoire constante et la mémoire unifiée.

本实验通过线性代数中的典型计算——矩阵乘法，理解 GPU 上不同类型的内存及其使用方式。题目介绍中提到了全局内存、共享内存、常量内存和统一内存。

> Les objectifs sont :

实验目标如下：

> - maîtriser la chaîne de compilation CUDA ;
> - comprendre les accès mémoire sur le GPU ;
> - optimiser les performances avec la mémoire partagée.

- 掌握 CUDA 编译流程；
- 理解 GPU 上的内存访问；
- 利用共享内存优化性能。

> Le code principal prolonge celui de la séance précédente. Les questions Q.1 à Q.12 présentes dans ce document portent sur la compilation et une première multiplication en mémoire globale ; elles ne demandent pas encore de kernel en mémoire partagée.

主要代码延续上一次实验的实现。本文件中的 Q.1～Q.12 涉及编译流程和使用全局内存的第一版矩阵乘法，尚未要求实现共享内存 kernel。

> **Remarque :** le répertoire des fichiers intermédiaires est uniformisé en `CUDAIMG` (le texte original mélange `TMP` et `CUDAIMG`). Les tirets des options sont corrigés. L’accumulateur de l’exemple est passé de `float` à `double`, conformément aux matrices et à `dgemm.c`.
>
> Les mesures proviennent d’un GH200 sur ROMEO (9 octobre 2026) ; les commandes de reproduction figurent en fin de document. Les indications Ruche du sujet sont conservées.

> **译注：** 原题混用了 `TMP` 和 `CUDAIMG`，这里统一为 `CUDAIMG`，并修正了命令选项中的横线。示例中的累加变量由 `float` 改为 `double`，与矩阵类型及 `dgemm.c` 保持一致。
>
> 实测数据来自 ROMEO 上的 GH200（2026-10-09），复现命令见文末。题目原有的 Ruche 环境说明保留。

## I. 编译流程（Chaîne de compilation）

> Sur Ruche, rechercher le module CUDA disponible avec `module spider cuda`, puis charger le module correspondant avec `module load cuda` si ce nom est disponible, ou avec son nom versionné. Depuis le répertoire contenant [tp1_check.cu](../CODE/Partie1/tp1_check.cu), exécuter :

在 Ruche 上先用 `module spider cuda` 查询可用的 CUDA 模块，再加载对应模块。如果存在名为 `cuda` 的模块，可以执行 `module load cuda`；否则使用查询到的带版本模块名。在 [tp1_check.cu](../CODE/Partie1/tp1_check.cu) 所在目录执行：

```bash
mkdir -p CUDAIMG
nvcc --keep --keep-dir CUDAIMG -c tp1_check.cu
ls CUDAIMG
```

> Les fichiers intermédiaires sont conservés dans `CUDAIMG`. L’option `-c` produit un fichier objet, sans édition de liens vers un exécutable.

中间文件保存在 `CUDAIMG` 中。`-c` 表示生成目标文件，不继续链接为可执行程序。

### Q.1 — 识别编译产物（Identifier les fichiers produits）

> **Question.** Quel fichier correspond au PTX ? Lequel correspond au binaire CUDA ?

**题目：** 哪个文件是 PTX？哪个文件是 CUDA 二进制文件？

> **Réponse.** Le fichier `.ptx` contient le code intermédiaire textuel pour le GPU. Le fichier `.cubin` contient le code machine GPU pour une architecture donnée. Un fichier `.fatbin` peut regrouper du PTX et/ou des cubins pour plusieurs cibles. Le fichier `.o` est l’objet côté hôte contenant notamment le code hôte et le code GPU embarqué ; ce n’est pas un cubin. Les noms précis dépendent de la version de `nvcc` et des options de compilation. Voir la [documentation NVIDIA de nvcc](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html).

**参考答案：** `.ptx` 文件包含面向 GPU 的文本形式中间代码。`.cubin` 文件包含针对某一 GPU 架构生成的机器代码。`.fatbin` 可以打包一个或多个目标架构的 PTX 和／或 cubin。`.o` 是主机侧目标文件，其中包含主机代码及嵌入的 GPU 代码等内容，它本身不是 cubin。具体文件名取决于 `nvcc` 版本和编译选项。参见 [NVIDIA nvcc 文档](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html)。

> **Observation sur ROMEO.** La commande utilisée est `nvcc -O3 -arch=sm_90 --keep --keep-dir CUDAIMG -c tp1_check.cu`. Le PTX est [tp1_check.ptx](../RESULTS/romeo-738578/CUDAIMG/tp1_check.ptx), le code machine GPU est [tp1_check.sm_90.cubin](../RESULTS/romeo-738578/CUDAIMG/tp1_check.sm_90.cubin), et le conteneur est [tp1_check.fatbin](../RESULTS/romeo-738578/CUDAIMG/tp1_check.fatbin). Le programme fourni affiche `TEST PASSED !` à l’exécution.

**ROMEO 实测：** 本次明确使用 `nvcc -O3 -arch=sm_90 --keep --keep-dir CUDAIMG -c tp1_check.cu`，生成的 PTX 为 [tp1_check.ptx](../RESULTS/romeo-738578/CUDAIMG/tp1_check.ptx)，GPU 机器代码为 [tp1_check.sm_90.cubin](../RESULTS/romeo-738578/CUDAIMG/tp1_check.sm_90.cubin)，打包文件为 [tp1_check.fatbin](../RESULTS/romeo-738578/CUDAIMG/tp1_check.fatbin)。原始程序执行输出 `TEST PASSED !`。

### Q.2 — 识别编译为 PTX 的代码（Identifier le code compilé en PTX）

> **Question.** Quelles parties de `tp1_check.cu` sont conservées pour être compilées en PTX ?

**题目：** `tp1_check.cu` 中哪些部分被保留下来，编译为 PTX？

> **Réponse.** Dans le fichier fourni, le code de calcul destiné au GPU est :

**参考答案：** 所给文件中，在 GPU 上执行的计算代码是：

```cpp
__global__ void kernel(int *v) {
    *v = 1;
}
```

> Ce kernel devient un point d’entrée PTX, avec les déclarations nécessaires. `main`, les affichages, les requêtes sur le GPU, `malloc`, les appels `cudaMalloc`/`cudaMemcpy`/`cudaFree` et la vérification finale restent côté hôte. L’expression de lancement `kernel<<<...>>>` est transformée en code hôte qui déclenche le kernel ; le corps du kernel s’exécute sur le GPU.

该 kernel 会生成 PTX 入口及必要的声明。`main`、输出语句、GPU 信息查询、`malloc`、`cudaMalloc`／`cudaMemcpy`／`cudaFree` 调用和最终结果检查都留在主机侧。`kernel<<<...>>>` 启动表达式被转换为触发 kernel 的主机代码；kernel 函数体在 GPU 上运行。

> **Preuve dans le PTX produit.** Le point d’entrée est `.visible .entry _Z6kernelPi`. Les instructions `mov.u32 %r1, 1` et `st.global.u32 [%rd2], %r1` réalisent l’écriture de l’entier 1 dans la mémoire globale pointée par le paramètre.

**实际 PTX 证据：** 入口为 `.visible .entry _Z6kernelPi`，关键指令为 `mov.u32 %r1, 1` 和 `st.global.u32 [%rd2], %r1`，对应向参数指向的全局内存写入整数 1。

### Q.3 — 理解 `_30` 后缀（Interpréter le suffixe `_30`）

> **Question.** À quoi correspond le suffixe `_30` des fichiers créés ?

**题目：** 生成文件名称中的 `_30` 后缀表示什么？

> **Réponse.** Dans les anciens noms contenant `compute_30` ou `sm_30`, `30` désigne la capacité de calcul **3.0**, associée à Kepler. `compute_30` désigne la cible virtuelle et `sm_30` la cible machine. Ce n’est ni la version de CUDA ni le nombre de threads. Ce suffixe vient d’un ancien environnement : il n’est pas garanti avec la commande actuelle. Il faut examiner les fichiers réellement produits et la ligne `.target` du PTX. Voir la [documentation historique de nvcc](https://docs.nvidia.com/cuda/archive/8.0/cuda-compiler-driver-nvcc/index.html).

**参考答案：** 旧版文件名中的 `compute_30` 或 `sm_30` 对应 **3.0 计算能力**，属于 Kepler 架构。`compute_30` 表示虚拟架构目标，`sm_30` 表示机器代码目标。它不表示 CUDA 版本，也不表示线程数。这个后缀来自旧实验环境，当前编译命令不一定产生它。应查看实际生成的文件以及 PTX 的 `.target` 声明。参见 [历史版本 nvcc 文档](https://docs.nvidia.com/cuda/archive/8.0/cuda-compiler-driver-nvcc/index.html)。

> **Environnement mesuré.** Le GH200 a une capacité de calcul 9.0. Le fichier produit porte le suffixe `.sm_90.cubin` et le PTX déclare `.version 8.8` et `.target sm_90`. Aucune cible `_30` n’a été produite dans cette exécution.

**本次环境：** GH200 的计算能力为 9.0。生成文件使用 `.sm_90.cubin` 后缀，PTX 声明为 `.version 8.8`、`.target sm_90`；本次没有生成 `_30` 目标。

## II. 矩阵乘法（Multiplication matricielle）

> La mémoire globale est accessible aux threads d’une grille. Nous utilisons `cudaMalloc` et `cudaFree` pour allouer et libérer les tableaux du GPU.

全局内存可由网格中的线程访问。本实验用 `cudaMalloc` 和 `cudaFree` 分配、释放 GPU 数组。

> Le fichier séquentiel [dgemm.c](../CODE/Partie2/dgemm.c) calcule :

提供的串行程序 [dgemm.c](../CODE/Partie2/dgemm.c) 计算：

$$
C \leftarrow \alpha AB + \beta C.
$$

> Compléter ce programme pour déporter le calcul sur le GPU, en utilisant l’extension `.cu`. Ici, les matrices sont carrées, de taille $N \times N$, stockées par lignes dans des tableaux contigus de $N^2$ valeurs `double`. La case $(i,j)$ se trouve à l’indice `i * N + j`.

从这里开始，补全该程序，将计算移到 GPU，并把源文件扩展名改为 `.cu`。这里的三个矩阵均为 $N \times N$ 方阵，按行存储在包含 $N^2$ 个 `double` 元素的连续数组中。第 $(i,j)$ 个元素对应下标 `i * N + j`。

> Pour des matrices et scalaires déjà initialisés, l’algorithme séquentiel est :

矩阵和标量完成初始化后，串行计算过程如下：

```cpp
for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
        double sum = 0.0;
        for (int k = 0; k < N; k++) {
            sum += A[i * N + k] * B[k * N + j];
        }
        C[i * N + j] = alpha * sum + beta * C[i * N + j];
    }
}
```

> Les extraits des réponses sont à intégrer progressivement au programme, pas à concaténer tels quels. Ils supposent `N > 0`, des allocations hôte réussies, `#include <cuda_runtime.h>` et la macro `CUDA_CHECK` fourni dans `tp1_check.cu`. Conserver les fonctions `init`, `dgemm` et `get_elapsedtime` de `dgemm.c`. Pour Q.11, ajouter `<vector>` et `<cmath>`. Définir les kernels hors de `main` ; placer allocations, copies et lancements dans `main`.

各题代码片段用于逐步补全程序，不能不加调整地直接全部拼接。以下假设 `N > 0`、主机内存分配成功，已包含 `<cuda_runtime.h>`，并复用 `tp1_check.cu` 中的 `CUDA_CHECK` 宏。保留 `dgemm.c` 中的 `init`、`dgemm` 和 `get_elapsedtime` 函数。Q.11 还需要 `<vector>` 和 `<cmath>`。kernel 定义放在 `main` 外，内存分配、复制和启动代码放在 `main` 内。

### 1. 内存分配与数据传输（Allocation et transfert de données）

### Q.4 — 在 GPU 上分配矩阵（Allouer les matrices sur le GPU）

> **Question.** Avec `cudaMalloc`, allouer trois tableaux de $N^2$ éléments : deux opérandes et un résultat. Utiliser un stockage contigu et libérer les allocations avec `cudaFree` en fin de programme.

**题目：** 用 `cudaMalloc` 在 GPU 上分配三个各含 $N^2$ 个元素的数组，分别保存两个输入矩阵和结果矩阵。使用连续存储，并在程序结束时用 `cudaFree` 释放。

> **Réponse.** Chaque tableau occupe $N^2 \times \mathrm{sizeof(double)}$ octets, soit $8N^2$ octets pour les `double` CUDA.

**参考答案：** 每个矩阵需要 $N^2 \times \mathrm{sizeof(double)}$ 字节。CUDA 中 `double` 占 8 字节，因此每个矩阵为 $8N^2$ 字节。

```cpp
size_t bytes = (size_t)N * N * sizeof(double);
double *d_A = nullptr, *d_B = nullptr, *d_C = nullptr;
CUDA_CHECK(cudaMalloc((void **)&d_A, bytes));
CUDA_CHECK(cudaMalloc((void **)&d_B, bytes));
CUDA_CHECK(cudaMalloc((void **)&d_C, bytes));
```

> Après la récupération et la vérification du résultat :

结果回传并检查完毕后释放：

```cpp
CUDA_CHECK(cudaFree(d_A));
CUDA_CHECK(cudaFree(d_B));
CUDA_CHECK(cudaFree(d_C));
```

> Les tableaux hôte `A`, `B` et `C`, alloués avec `malloc`, sont libérés séparément avec `free`.

主机上的 `A`、`B`、`C` 若由 `malloc` 分配，仍需分别调用 `free` 释放。

### Q.5 — 将数据复制到 GPU（Copier les données vers le GPU）

> **Question.** Transférer les données initialisées sur l’hôte vers le GPU avec `cudaMemcpy`.

**题目：** 使用 `cudaMemcpy`，把主机端已初始化的数据传输到 GPU。

> **Réponse.** Après `init(A, B, C, N)`, copier les trois matrices :

**参考答案：** 执行 `init(A, B, C, N)` 后，复制三个矩阵：

```cpp
CUDA_CHECK(cudaMemcpy(d_A, A, bytes, cudaMemcpyHostToDevice));
CUDA_CHECK(cudaMemcpy(d_B, B, bytes, cudaMemcpyHostToDevice));
CUDA_CHECK(cudaMemcpy(d_C, C, bytes, cudaMemcpyHostToDevice));
```

> Il faut aussi initialiser `d_C`, car le calcul lit l’ancienne valeur de $C$ dans $\beta C$. Dans le programme fourni, `beta = 1` et $C$ est initialement nulle ; `cudaMalloc` ne met pas la mémoire à zéro.

`d_C` 也必须初始化，因为计算中的 $\beta C$ 会读取原来的 $C$。所给程序中 `beta = 1`，$C$ 初始为零；`cudaMalloc` 不会自动把分配的内存清零。

### 2. kernel 配置（Configuration du kernel）

### Q.6 — 设置线程块和网格（Définir les blocs et la grille）

> **Question.** Utiliser `dim3` pour définir des blocs 2D de $32 \times 32$ threads, soit 1 024 threads par bloc. Prévoir un thread par élément de $C$. Pour simplifier, choisir $N$ multiple de 32.

**题目：** 使用 `dim3` 创建二维线程块，每块 $32 \times 32$，共 1 024 个线程。网格需要有足够的线程，使每个线程负责结果矩阵的一个元素。为简化处理，令 $N$ 为 32 的倍数。

> **Réponse.** On prend l’axe `x` pour les colonnes et l’axe `y` pour les lignes.

**参考答案：** 用 `x` 方向对应列，`y` 方向对应行。

```cpp
dim3 block(32, 32);
dim3 grid((N + block.x - 1) / block.x,
          (N + block.y - 1) / block.y);
```

> Si $N$ est multiple de 32, la grille contient $(N/32) \times (N/32)$ blocs, soit exactement $N^2$ threads. Pour $N=1024$, cela donne $32 \times 32$ blocs. L’arrondi supérieur couvre aussi les autres tailles, avec le test de limites de Q.10. Vérifier que le GPU accepte 1 024 threads par bloc et les dimensions demandées ; cette configuration imposée par le sujet n’est pas nécessairement la plus performante.

当 $N$ 为 32 的倍数时，网格包含 $(N/32) \times (N/32)$ 个线程块，总计恰好 $N^2$ 个线程。例如，$N=1024$ 时网格为 $32 \times 32$ 个线程块。上述向上取整写法也能覆盖其他大小，但需要配合 Q.10 的边界检查。应确认 GPU 支持每块 1 024 个线程及所要求的各维大小；题目指定的配置不一定是性能最好的配置。

### Q.7 — 启动空 kernel（Lancer un kernel vide）

> **Question.** Écrire puis lancer un kernel encore vide sur la grille définie précédemment.

**题目：** 编写一个暂时不执行计算的空 kernel，并在前面配置的网格上启动它。

> **Réponse.** `__global__` déclare une fonction exécutée sur le GPU et appelée depuis l’hôte.

**参考答案：** `__global__` 声明一个由主机调用、在 GPU 上执行的函数。

```cpp
__global__ void empty_kernel() {
}

// In main():
empty_kernel<<<grid, block>>>();
CUDA_CHECK(cudaGetLastError());
```

> Le lancement est asynchrone vis-à-vis de l’hôte. `cudaGetLastError` vérifie les erreurs de lancement ; les erreurs d’exécution doivent aussi être contrôlées lors d’une synchronisation ou de la copie suivante.

kernel 启动对主机是异步的。`cudaGetLastError` 检查启动错误；执行期间的错误还需要在同步或后续复制时检查。

### Q.8 — 回传结果（Récupérer le résultat）

> **Question.** Après l’exécution du kernel, transférer le résultat vers l’hôte.

**题目：** kernel 执行后，将矩阵乘法结果传回主机。

> **Réponse.** Copier `d_C` vers `C` :

**参考答案：** 将 `d_C` 复制到主机数组 `C`：

```cpp
CUDA_CHECK(cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost));
```

> Ici, le kernel et la copie utilisent le même flux par défaut. La copie GPU vers CPU attend les opérations précédentes de ce flux et ne retourne qu’une fois le résultat disponible sur l’hôte. À l’étape Q.7, le kernel vide laisse simplement les valeurs initiales inchangées.

这里的 kernel 和复制操作使用同一个默认流。GPU 到 CPU 的复制会等待该流中的前序操作，且返回时结果已可供主机使用。在 Q.7 的空 kernel 阶段，矩阵还没有参与计算，复制回来的只是初始值。

### 3. 编写 kernel（Écriture du kernel）

### Q.9 — 计算行列下标（Calculer les indices）

> **Question.** À partir des indices et dimensions de la grille, calculer la ligne et la colonne de l’élément de $C$ associé au thread.

**题目：** 根据网格的维度和线程索引，计算该线程负责的 $C$ 元素的行号与列号。

> **Réponse.**

**参考答案：**

```cpp
int row = blockIdx.y * blockDim.y + threadIdx.y;
int col = blockIdx.x * blockDim.x + threadIdx.x;
```

> Le thread traite `C[row * N + col]`. Deux threads valides différents traitent deux éléments différents.

该线程负责 `C[row * N + col]`。不同的有效线程对应不同的矩阵元素。

### Q.10 — 计算 C 的一个元素（Calculer un élément de C）

> **Question.** Pour chaque thread, calculer l’élément de $C$ correspondant.

**题目：** 每个线程在 GPU kernel 中完成对应的 $C$ 元素计算。

> **Réponse.** Le thread parcourt la ligne `row` de $A$ et la colonne `col` de $B$, puis applique les coefficients $\alpha$ et $\beta$.

**参考答案：** 线程遍历 $A$ 的第 `row` 行和 $B$ 的第 `col` 列，计算点积，再应用 $\alpha$ 和 $\beta$。

```cpp
__global__ void dgemm_kernel(int N, double alpha,
                             const double *A, const double *B,
                             double beta, double *C) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row >= N || col >= N) return;

    double sum = 0.0;
    for (int k = 0; k < N; k++) {
        sum += A[row * N + k] * B[k * N + col];
    }
    C[row * N + col] = alpha * sum + beta * C[row * N + col];
}
```

> Pour les coefficients du programme fourni, remplacer le lancement vide et la copie de Q.8 par :

使用原程序中的系数，将空 kernel 启动和 Q.8 的回传代码替换为：

```cpp
double alpha = 1.0, beta = 1.0;
dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost));
```

> Aucun `__syncthreads()` n’est nécessaire : chaque thread accumule dans une variable locale et écrit un élément distinct. Cette première version utilise la mémoire globale pour les matrices.

这里不需要 `__syncthreads()`：每个线程使用自己的局部累加变量，并写入不同的元素。这一版矩阵乘法通过全局内存访问矩阵。

### 4. 性能分析（Analyse des performances）

### Q.11 — 测量并比较运行时间（Mesurer et comparer les temps）

> **Question.** Utiliser `cudaEventElapsedTime` pour mesurer le temps GPU. Examiner le coût du produit matriciel et du transfert du résultat vers l’hôte, puis comparer au calcul CPU séquentiel.

**题目：** 使用 `cudaEventElapsedTime` 测量 GPU 时间，考察矩阵乘法及结果回传到主机的耗时，并与 CPU 串行版本比较。

> **Réponse.** Mesurer séparément le kernel avec deux événements CUDA et le temps « lancement + calcul + retour de $C$ » avec l’horloge hôte `get_elapsedtime`. Le second inclut les frais de lancement et de mesure, mais exclut les allocations et les copies initiales CPU vers GPU. Pour un temps complet de l’application, il faudrait inclure ces étapes aussi. `cudaEventElapsedTime` renvoie des millisecondes ; les événements doivent être terminés avant la lecture. Voir la [documentation NVIDIA des événements CUDA](https://docs.nvidia.com/cuda/cuda-runtime-api/cuda_runtime_api/group__CUDART__EVENT.html).

**参考答案：** 用两个 CUDA event 测量 kernel 时间，同时用主机计时函数 `get_elapsedtime` 测量“启动、计算、回传 $C$”这一过程。后者包含启动和计时开销，但不包括内存分配及最初的 CPU 到 GPU 复制。如果要统计整个应用的完整耗时，还应把这些步骤纳入范围。`cudaEventElapsedTime` 返回毫秒，读取前需要确保事件已经完成。参见 [NVIDIA CUDA event 文档](https://docs.nvidia.com/cuda/cuda-runtime-api/cuda_runtime_api/group__CUDART__EVENT.html)。

> Le bloc suivant **remplace** le lancement et la récupération de Q.10. Le placer après les copies de Q.5 et la configuration de Q.6, avant tout calcul modifiant `C`, avec `alpha = 1.0` et `beta = 1.0` définis. Il conserve une copie du $C$ initial pour que CPU et GPU calculent la même opération.

以下代码**替换** Q.10 的启动和回传部分。放在 Q.5 数据复制、Q.6 网格配置之后，并且放在任何会修改 `C` 的计算之前；预先定义 `alpha = 1.0`、`beta = 1.0`。代码保留初始 $C$，让 CPU 和 GPU 计算相同的表达式。

```cpp
// Keep the same initial C for the CPU, warm-up and measured GPU run.
std::vector<double> C_initial(C, C + (size_t)N * N);
std::vector<double> C_cpu = C_initial;

double cpu_start = get_elapsedtime();
dgemm(N, N, N, alpha, A, B, beta, C_cpu.data());
double cpu_ms = (get_elapsedtime() - cpu_start) * 1e3;

// Warm-up (excluded from timing).
dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaDeviceSynchronize());
CUDA_CHECK(cudaMemcpy(d_C, C_initial.data(), bytes,
                      cudaMemcpyHostToDevice));
CUDA_CHECK(cudaDeviceSynchronize());

cudaEvent_t start, stop;
CUDA_CHECK(cudaEventCreate(&start));
CUDA_CHECK(cudaEventCreate(&stop));

double gpu_start = get_elapsedtime();
CUDA_CHECK(cudaEventRecord(start));
dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaEventRecord(stop));
CUDA_CHECK(cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost));
double gpu_with_copy_ms = (get_elapsedtime() - gpu_start) * 1e3;

CUDA_CHECK(cudaEventSynchronize(stop));
float kernel_ms = 0.0f;
CUDA_CHECK(cudaEventElapsedTime(&kernel_ms, start, stop));
CUDA_CHECK(cudaEventDestroy(start));
CUDA_CHECK(cudaEventDestroy(stop));

printf("CPU: %.3f ms\n", cpu_ms);
printf("GPU kernel: %.3f ms\n", kernel_ms);
printf("GPU kernel + D2H (host): %.3f ms\n", gpu_with_copy_ms);
printf("Speedup (kernel): %.3f\n", cpu_ms / kernel_ms);
printf("Speedup (kernel + D2H): %.3f\n", cpu_ms / gpu_with_copy_ms);

bool correct = true;
for (size_t i = 0; i < C_initial.size(); i++) {
    double tolerance = 1e-10 + 1e-10 * std::abs(C_cpu[i]);
    if (!std::isfinite(C[i]) || !std::isfinite(C_cpu[i]) ||
        std::abs(C[i] - C_cpu[i]) > tolerance) {
        correct = false;
        break;
    }
}
printf("Validation: %s\n", correct ? "PASSED" : "FAILED");
```

> La tolérance proposée est un contrôle pratique pour ce TP, à adapter à l’échelle des données et à $N$. Un échec doit être étudié avant toute comparaison de performances. Pour les données de `init`, $A_{ik}=i$, $B_{kj}=k$ et $C^{(0)}=0$ ; avec $\alpha=\beta=1$, on peut aussi vérifier $C_{ij}=iN(N-1)/2$.

示例误差容限用于本实验的基本检查，应根据数据尺度和 $N$ 调整。如果检查失败，应先排查结果，再比较性能。按照 `init` 的初始化，$A_{ik}=i$、$B_{kj}=k$、$C^{(0)}=0$；当 $\alpha=\beta=1$ 时，还可以用 $C_{ij}=iN(N-1)/2$ 验证结果。

> Répéter les mesures après échauffement, restaurer `d_C` depuis `C_initial` avant chaque répétition, hors chronométrage, puis rapporter une médiane. Sinon, avec $\beta=1$, les lancements successifs accumulent des résultats différents. Noter le CPU, le GPU, la version CUDA, $N$ et les options de compilation. Les mesures obtenues sont présentées ci-dessous.

预热后重复测量，并在每次测量之前将 `C_initial` 重新复制到 `d_C`，这次恢复不计入时间，最后报告中位数。否则在 $\beta=1$ 时，重复启动会不断累加结果。记录 CPU、GPU、CUDA 版本、$N$ 和编译选项。本次实测结果如下。

> **Conditions ROMEO.** Mesures du 9 octobre 2026 à 14 h 27, heure de Paris, sur `romeo-a057`, job Slurm `738578`. GPU NVIDIA GH200 120GB ; un cœur ARM Neoverse-V2 du CPU Grace, fixé au CPU 280 ; CUDA 12.9.41, GCC 11.5.0, pilote 590.48.01. Compilation avec `-O3 -arch=sm_90`. Matrices en `double`, blocs `32×32`, données de la fonction `init` fournie et `alpha = beta = 1`.

**ROMEO 实测条件：** 2026 年 10 月 9 日 14:27（巴黎时间），节点 `romeo-a057`，Slurm 作业 `738578`。GPU 为 NVIDIA GH200 120GB，CPU 为 Grace 的 ARM Neoverse-V2 单核（绑定 CPU 280）；CUDA 12.9.41、GCC 11.5.0、驱动 590.48.01。使用 `-O3 -arch=sm_90` 编译。矩阵为 `double`，线程块为 `32×32`，采用原始 `init` 数据及 `alpha = beta = 1`。

> Chaque implémentation est exécutée une fois pour l’échauffement, puis mesurée 5 fois. Chaque colonne de temps donne sa propre médiane. Le CPU conserve la boucle séquentielle `i → j → k`, sans BLAS ni multithreading. Les tableaux hôte sont en mémoire pageable ordinaire. Les événements encadrent uniquement le kernel ; la mesure hôte « avec retour » inclut le lancement, l’enregistrement des événements, le calcul et la copie GPU→CPU, mais exclut allocations, initialisation et copies initiales CPU→GPU. Validation, échauffement et restauration du C initial sont hors chronométrage.

CPU 与 GPU 各预热一次，随后分别测量 5 次，表中每一列耗时均取各自中位数。CPU 保留题目中的 `i → j → k` 串行循环，未使用 BLAS 或多线程。主机数组使用普通可分页内存。事件测量只包围 kernel；“含回传”列使用主机时钟，包含启动、事件记录、计算及 GPU→CPU 复制，不包含分配、初始化和最初的 CPU→GPU 复制。校验、预热和每次恢复初始 C 均在计时区间之外。

| N | CPU 串行 / ms<br>CPU séquentiel / ms | GPU kernel / ms<br>Kernel GPU / ms | GPU 含回传 / ms<br>GPU avec retour / ms | kernel 加速比<br>Accélération kernel | 含回传加速比<br>Accélération avec retour |
|---:|---:|---:|---:|---:|---:|
| 256 | 11.966112 | 0.036736 | 0.055616 | 325.73× | 215.16× |
| 512 | 205.259776 | 0.093152 | 0.121568 | 2203.49× | 1688.44× |
| 1024 | 1846.268896 | 0.577568 | 0.644448 | 3196.63× | 2864.89× |

> Pour ces trois tailles, le calcul GPU reste plus rapide que le CPU fourni, même avec le retour du résultat. Les fortes accélérations sont relatives à la triple boucle naïve ; elles ne mesurent pas un gain face à une bibliothèque BLAS optimisée ou à un CPU multicœur. Le bénéfice de la mémoire partagée n’est pas mesuré ici.

这说明，对本实验的三种规模，GPU 版本在包含结果回传后仍快于所给的 CPU 串行实现。较大的加速比以朴素三重循环为基线，不能推广为相对于优化 BLAS 或多核 CPU 的加速比。这里也没有测量共享内存优化的收益。

> **Validation.** Pour les trois tailles de performance, les résultats CPU et GPU coïncident exactement avec $C_{ij}=iN(N-1)/2$ : erreur absolue maximale nulle. Des cas supplémentaires `N = 1, 31, 32, 33, 65`, avec valeurs fractionnaires signées, C initial non nul, `alpha = 0.75` et `beta = -0.5`, passent tous la comparaison à une référence accumulée en `long double`. L’erreur absolue maximale est d’environ $2.164\times10^{-15}$. Le `memcheck` de Compute Sanitizer pour `N=33` rapporte **0 errors** ; ce temps instrumenté est exclu du tableau de performance.

**正确性：** 三种性能测试的 CPU、GPU 结果均与解析式 $C_{ij}=iN(N-1)/2$ 完全一致，最大绝对误差为 0。另对 `N = 1, 31, 32, 33, 65` 使用正负小数、非零初始 C、`alpha = 0.75` 和 `beta = -0.5`，与 `long double` 累加参考比较，全部通过，最大绝对误差约为 $2.164\times10^{-15}$。`N=33` 的 Compute Sanitizer `memcheck` 报告 **0 errors**；其插桩运行时间不进入性能表。

> [Journal complet](../RESULTS/romeo-738578/run.log) · [Mesures individuelles et médianes](../RESULTS/romeo-738578/measurements.json) · [Fin du job Slurm](../RESULTS/romeo-738578/slurm-accounting.txt)

[完整日志](../RESULTS/romeo-738578/run.log) · [原始测量及中位数](../RESULTS/romeo-738578/measurements.json) · [Slurm 完成记录](../RESULTS/romeo-738578/slurm-accounting.txt)

### Q.12 — 复杂度和 FLOP/s（Complexité et FLOP/s）

> **Question.** Quelle est la complexité arithmétique ? Calculer le débit en FLOP/s de l’implémentation.

**题目：** 算法的算术复杂度是多少？计算实现的每秒浮点运算次数。

> **Réponse.** Il y a $N^2$ éléments à calculer et $N$ étapes par produit scalaire : le travail total est $\Theta(N^3)$. Chaque thread effectue $\Theta(N)$ opérations ; le parallélisme ne change pas le travail arithmétique total.

**参考答案：** 一共需要计算 $N^2$ 个元素，每个元素的点积循环执行 $N$ 次，因此总算术工作量为 $\Theta(N^3)$。每个线程完成 $\Theta(N)$ 的工作；并行执行不会改变总算术工作量。

> Avec une multiplication et une addition par itération, on utilise conventionnellement :

每轮点积执行一次乘法和一次加法，通常采用以下运算量约定：

$$
F \simeq 2N^3.
$$

> Le comptage littéral du code ajoute deux multiplications et une addition par élément pour $\alpha\,\mathrm{sum}+\beta C$, soit $2N^3+3N^2$ opérations avant simplifications du compilateur. Une FMA compte pour deux FLOP, même si elle est exécutée comme une seule instruction.

如果按照源代码逐项计数，$\alpha\,\mathrm{sum}+\beta C$ 还为每个元素增加两次乘法和一次加法，因此在编译器简化之前为 $2N^3+3N^2$ 次浮点运算。即使乘加融合为一条 FMA 指令，仍按两个 FLOP 计数。

> Pour un temps $t_s$ en secondes, ou $t_{ms}$ en millisecondes :

若时间 $t_s$ 的单位是秒，或 $t_{ms}$ 的单位是毫秒，则：

$$
P_{\mathrm{FLOP/s}} = \frac{2N^3}{t_s},
\qquad
P_{\mathrm{GFLOP/s}} = \frac{2N^3}{t_{ms}\,10^6}.
$$

```cpp
double operations = 2.0 * N * N * N;
double kernel_gflops = operations / (kernel_ms * 1e6);
printf("GPU kernel: %.3f GFLOP/s\n", kernel_gflops);
```

> Avec $N=1024$, $2N^3=2\,147\,483\,648$ FLOP. Insérer le temps réellement mesuré pour obtenir le débit. Utiliser `kernel_ms` pour le débit du kernel ; utiliser `gpu_with_copy_ms` donne un débit effectif incluant le retour du résultat, à nommer explicitement. Les copies ne sont pas comptées comme des FLOP. Les débits mesurés sur ROMEO sont présentés ci-dessous.

当 $N=1024$ 时，$2N^3=2\,147\,483\,648$ FLOP。代入实际测得的时间，才能得到吞吐率。使用 `kernel_ms` 得到 kernel 吞吐率；使用 `gpu_with_copy_ms` 得到包含结果回传的有效吞吐率，需要明确标注。内存复制不计为 FLOP。本次 ROMEO 实测吞吐率如下。

| N | CPU / GFLOP/s | GPU kernel / GFLOP/s<br>Kernel GPU / GFLOP/s | GPU 含回传 / GFLOP/s<br>GPU avec retour / GFLOP/s |
|---:|---:|---:|---:|
| 256 | 2.804 | 913.394 | 603.326 |
| 512 | 1.308 | 2881.693 | 2208.112 |
| 1024 | 1.163 | 3718.149 | 3332.285 |

> Par exemple, pour $N=1024$ :

以 $N=1024$ 为例：

$$
P_{\mathrm{kernel}}=\frac{2\times1024^3}{0.577567995\times10^6}
\simeq 3718.149\ \mathrm{GFLOP/s}.
$$

> Ce débit est celui de cette version en mémoire globale, dans la configuration mesurée.

这是该全局内存版本在本次配置下的实测吞吐率。

## III. 完整程序与 ROMEO 复现（Programme complet et reproduction sur ROMEO）

> L’implémentation complète est [dgemm.cu](../CODE/Partie2/dgemm.cu). Le script [run_romeo.sh](../CODE/run_romeo.sh) compile, vérifie et mesure le programme. Les fichiers fournis `dgemm.c` et `tp1_check.cu` sont conservés.

完整实现见 [dgemm.cu](../CODE/Partie2/dgemm.cu)，自动编译、校验和测量脚本见 [run_romeo.sh](../CODE/run_romeo.sh)。原始 `dgemm.c` 与 `tp1_check.cu` 均保留。

> Le répertoire distant est `/gpfs/projet/r260073/hibouwu/coursework/apm-tp1-20261009`. Les sources mesurées sont archivées dans [source](../RESULTS/romeo-738578/source/), avec le manifeste [source.sha256](../RESULTS/romeo-738578/source.sha256).

远程目录为 `/gpfs/projet/r260073/hibouwu/coursework/apm-tp1-20261009`。实测源码快照保存在 [source](../RESULTS/romeo-738578/source/)，校验清单见 [source.sha256](../RESULTS/romeo-738578/source.sha256)。

> Depuis le terminal local, se connecter puis exécuter via Slurm :

从本地终端连接，再通过 Slurm 执行：

```bash
ssh romeo
cd /gpfs/projet/r260073/hibouwu/coursework/apm-tp1-20261009/CODE
srun --account=r260073 --partition=instant --constraint=armgpu \
    --nodes=1 --ntasks=1 --cpus-per-task=1 --mem=4G \
    --gpus-per-node=1 --time=00:15:00 --job-name=apm-tp1 \
    --cpu-bind=cores bash ./run_romeo.sh
```

> Le script charge CUDA 12.9 sur le nœud de calcul et conserve le journal et les fichiers intermédiaires dans `RESULTS/romeo-numéro_du_job/`. Ne pas exécuter le programme GPU sur le nœud de connexion. La commande demande un nouveau job.

脚本会在计算节点加载 CUDA 12.9，将日志和中间文件保存到 `RESULTS/romeo-作业号/`。不要在登录节点直接执行 GPU 程序。上述命令会新申请一个作业。

> Dans une allocation GPU personnelle déjà active, après chargement de CUDA, on peut aussi compiler et exécuter depuis `CODE` :

若已经进入自己的 GPU 分配，并加载了 CUDA，也可以在 `CODE` 目录手动编译运行：

```bash
nvcc -std=c++17 -O3 -arch=sm_90 -Xcompiler=-Wall,-Wextra \
    Partie2/dgemm.cu -o dgemm
./dgemm 1024 5
./dgemm 33 2 general
```

> Les arguments sont la taille de matrice, le nombre de mesures et l’option `general` pour les données de validation. Sans argument, le programme utilise `N=1024`, 5 mesures et les données du sujet. Les exécutables rapatriés sont des binaires aarch64 destinés aux nœuds de calcul ROMEO correspondants.

参数依次是矩阵大小、测量次数以及可选的 `general` 校验输入。省略参数时使用 `N=1024`、5 次测量和原题输入。本地取回的可执行文件为 aarch64 架构，应在 ROMEO 对应计算节点运行。
