# TD1：CUDA 索引与执行模型（APM 2026-2027）

原题：[td1.pdf](td1.pdf) · 代码：[tp1.cu](tp1.cu) · CPU 模拟：[tp1_cpu.cpp](tp1_cpu.cpp)

> Les objectifs de ce TD sont :
> - Compréhension du modèle d’exécution
> - Émulation sur CPU
> - Calcul d’indice global

本次习题课的目标：

- 理解执行模型
- 在 CPU 上进行模拟
- 计算全局索引

## I 全局索引的计算（Calcul d’indice global）

> Les indices commencent à 0. On aplatit les coordonnées en prenant **x comme dimension la plus rapide, puis y, puis z**. `blockIdx` est la position du bloc dans la grille, `gridDim` le nombre de blocs par dimension ; `threadIdx` est la position du thread dans le bloc, `blockDim` le nombre de threads par dimension.

以下解答均从 0 开始编号，并按 **x 维最快、y 维其次、z 维最慢** 的顺序，把多维坐标展平成一维编号。`blockIdx` 是块在网格中的坐标，`gridDim` 是各维的块数；`threadIdx` 是线程在块中的坐标，`blockDim` 是各维的线程数。这些变量都可在 CUDA kernel 中使用。

### Q.1 二维网格中的块编号（Indice d'un bloc dans une grille 2D）

> **Q.1 :** En utilisant les variables prédéfinies par CUDA dans un kernel, calculer l'indice global d'un block dans une grille 2D

**题目：**在 kernel 中使用 CUDA 的预定义变量，计算二维网格中一个线程块的全局索引。

> **Réponse :** Une ligne de la grille (à `blockIdx.y` fixé) contient `gridDim.x` blocs : on compte les lignes complètes, puis la position dans la ligne.

**解答：**同一行（固定 `blockIdx.y`）有 `gridDim.x` 个块，因此前面完整的行贡献 `blockIdx.y * gridDim.x` 个块，再加上本行的 `blockIdx.x`：

```cpp
unsigned int block_id = blockIdx.y * gridDim.x + blockIdx.x;
```

### Q.2 三维网格中的块编号（Indice d'un bloc dans une grille 3D）

> **Q.2 :** En utilisant les variables prédéfinies par CUDA dans un kernel, calculer l'indice global d'un block dans une grille 3D

**题目：**在 kernel 中使用 CUDA 的预定义变量，计算三维网格中一个线程块的全局索引。

> **Réponse :** Un plan z complet contient `gridDim.x * gridDim.y` blocs ; on applique le même raisonnement dimension par dimension.

**解答：**一个完整的 z 层有 `gridDim.x * gridDim.y` 个块：

```cpp
unsigned int block_id = (blockIdx.z * gridDim.y + blockIdx.y)
                      * gridDim.x + blockIdx.x;
```

### Q.3 三维块中的线程总数（Taille d'un bloc 3D）

> **Q.3 :** En utilisant les variables prédéfinies par CUDA dans un kernel, calculer la taille (nombre de threads) d'un bloc défini en 3D

**题目：**在 kernel 中使用 CUDA 的预定义变量，计算一个按三维定义的线程块的大小（线程数）。

> **Réponse :** Le nombre de threads d’un bloc est le produit des trois dimensions du bloc.

```cpp
unsigned int threads_per_block = blockDim.x * blockDim.y * blockDim.z;
```

### Q.4 线程在三维块内的线性编号（Indice d'un thread dans un bloc 3D）

> **Q.4 :** En utilisant les variables prédéfinies par CUDA dans un kernel, calculer l'indice global d'un thread dans un bloc 3D

**题目：**在 kernel 中使用 CUDA 的预定义变量，计算三维线程块中一个线程的全局索引。

> **Réponse :** Cet indice numérote les threads **dans un bloc**, de `0` à `threads_per_block - 1`. Malgré l’expression « indice global » du sujet, ce n’est pas encore l’indice dans toute la grille.

**解答：**这里的编号覆盖**一个块内**的所有线程，范围是 `0` 到 `threads_per_block - 1`。题目所说的 *indice global ... dans un bloc 3D* 可理解为把块内三维坐标转换成一个唯一的一维编号；它还不是整张网格中的线程编号。

```cpp
unsigned int thread_id_in_block = (threadIdx.z * blockDim.y + threadIdx.y)
                                * blockDim.x + threadIdx.x;
```

### Q.5 三维网格、三维块中的线程线性编号（Indice d'un thread dans une grille 3D de blocs 3D）

> **Q.5 :** En vous servant des questions précédentes, calculer l'indice global d'un thread dans une grille 3D composée de blocs 3D

**题目：**利用前面几题的结果，计算由三维线程块组成的三维网格中一个线程的全局索引。

> **Réponse :** Chaque bloc qui précède le bloc courant contient `threads_per_block` threads. Pour `gridDim=(2,2,2)`, `blockDim=(4,2,2)`, `blockIdx=(1,0,1)` et `threadIdx=(2,1,0)` : `block_id=5`, `threads_per_block=16`, `thread_id_in_block=6`, d’où **86**. Pour accéder à un tableau spatial 3D, calculer plutôt `gx`, `gy`, `gz` dimension par dimension, puis aplatir selon l’ordre de stockage du tableau.

**解答：**每个排在当前块之前的块都有 `threads_per_block` 个线程，所以：

```cpp
unsigned int block_id = (blockIdx.z * gridDim.y + blockIdx.y)
                      * gridDim.x + blockIdx.x;
unsigned int threads_per_block = blockDim.x * blockDim.y * blockDim.z;
unsigned int thread_id_in_block = (threadIdx.z * blockDim.y + threadIdx.y)
                                * blockDim.x + threadIdx.x;
unsigned int global_thread_id = block_id * threads_per_block
                              + thread_id_in_block;
```

例如 `gridDim = (2, 2, 2)`、`blockDim = (4, 2, 2)`，取 `blockIdx = (1, 0, 1)`、`threadIdx = (2, 1, 0)`：块编号是 `(1 * 2 + 0) * 2 + 1 = 5`，每块有 `16` 个线程，块内线程编号是 `(0 * 2 + 1) * 4 + 2 = 6`，最终编号为 `5 * 16 + 6 = 86`。

> 如果目的是按空间位置访问一个三维数组，也可以先逐维计算 `gx = blockIdx.x * blockDim.x + threadIdx.x`、`gy = blockIdx.y * blockDim.y + threadIdx.y`、`gz = blockIdx.z * blockDim.z + threadIdx.z`，再按数组的存储顺序展平。这种数组位置编号与上面的“先给块编号，再给块内线程编号”通常不同，不应混用。

## II 执行模型与 CUDA SDK（Modèle d’exécution et SDK CUDA）

> Dans cette partie nous considérons le fichier td2.cu.

本部分以文件 td2.cu 为研究对象。

> **译注：**题目写的是 `td2.cu`，目录里实际提供的是 [`tp1.cu`](tp1.cu)，以下 Q.6–Q.9 按这份代码作答。

### Q.6 主机端与设备端的分工（Partie hôte et partie device）

> **Q.6 :** Quelle partie du programme doit s'exécuter sur l'hôte ?
> Quelle partie sur le device ?

**题目：**程序的哪一部分应在主机端执行？
哪一部分应在设备端执行？

> **Réponse :** `main`, les allocations, l’initialisation, les copies et l’instruction de lancement s’exécutent sur le CPU. Le corps de la fonction `__global__ kernel` s’exécute sur le GPU. Un appel à `cudaMalloc` est du code hôte qui alloue de la mémoire device.

**解答：**`main` 在主机（CPU）上运行：分配和初始化 `h_x`、`h_y`，通过 `cudaMalloc` 分配设备内存，用 `cudaMemcpy` 传输数据，确定 `dimBlock` 和 `dimGrid`，发起 kernel，复制结果并释放内存。声明为 `__global__` 的 `kernel` 在设备（GPU）上执行；每个设备线程计算自己的 `i`，在 `i < N` 时更新 `d_y[i]`。`kernel<<<...>>>` 这一调用语句由主机执行，它启动设备端计算。

### Q.7 程序计算什么（Que calcule ce programme ?）

> **Q.7 :** Que calcule ce programme ?
> (si vous ne savez pas répondre à cette question, répondre à la suivante pourra vous aider).

**题目：**这个程序计算什么？
（如果你无法回答这个问题，先回答下一题可能会有所帮助。）

> **Réponse :** Il effectue une opération AXPY : `y[i] = 3.14 * x[i] + y[i]`, avec `x[i] = 1/(i+1)` et `y[i] = (i-1)/(i+1)` au départ, donc `y[i] = (i+2.14)/(i+1)` ; ainsi `y[0] = 2.14`. Le programme recopie le résultat puis libère les tableaux, sans l’afficher.

**解答：**对 `i = 0, 1, ..., 999`，程序执行一次 `y[i] = 3.14 * x[i] + y[i]`（AXPY 运算）。初始化给出 `x[i] = 1/(i+1)`、原 `y[i] = (i-1)/(i+1)`，所以新值为 `(i + 2.14)/(i+1)`。例如 `y[0] = 2.14`。代码把结果复制回 `h_y` 后就释放内存，没有打印结果。

### Q.8 线程块与线程数量（Nombre de blocs et de threads）

> **Q.8 :** Combien y a-t-il de blocs au total ?
> Combien de threads par blocs ?
> Combien de threads au total ?

**题目：**总共有多少个线程块？
每个线程块有多少个线程？
总共有多少个线程？

> **Réponse :** Avec `N=1000` et 64 threads par bloc, il faut `ceil(1000/64)=16` blocs. Les **1024 threads lancés** comprennent **1000 threads utiles** et **24 threads hors limites**, éliminés par `if (i < N)`.

**解答：**`dimBlock = (64, 1, 1)`，每块 `64` 个线程；`dimGrid = (ceil(1000/64), 1, 1) = (16, 1, 1)`，共 `16` 个块。因此启动 `16 * 64 = 1024` 个线程，其中 `1000` 个满足 `i < N` 并更新数组，最后 `24` 个线程因边界判断不执行更新。

### Q.9 在 CPU 上模拟 GPU（Émuler le GPU sur CPU）

> **Q.9 :** Émuler sur CPU le comportement du GPU sans utiliser le SDK CUDA.
> Pour ce faire, réécrire le programme parallèle en C/C++ avec les contraintes suivantes :

**题目：**不使用 CUDA SDK，在 CPU 上模拟 GPU 的行为。
为此，请按照以下要求，用 C/C++ 重写该并行程序：

> **Réponse :** Conserver deux ensembles de tableaux, les copies, une fonction kernel et les deux boucles bloc/thread ; le [programme CPU complet](tp1_cpu.cpp) existe déjà. Il s’agit d’une émulation séquentielle de l’indexation et du flux des données ; elle ne reproduit ni les warps ni l’ordonnancement réel du GPU.

**解答：**1. utilisation de nouveaux tableaux à utiliser pour le "kernel"  
   使用供“kernel”使用的新数组。

2. copie des données en entrées et en sorties du "kernel"  
   复制“kernel”的输入数据和输出数据。

3. utilisation d'une fonction kernel  
   使用一个 kernel 函数。

4. utillisation des grilles de blocs et de threads  
   使用线程块和线程的网格结构。

5. calcul d'un indice global pour accéder aux cases des tableaux  
   计算全局索引，以访问数组中的元素。

**解答：** 可运行的纯 C++ 模拟见 [`tp1_cpu.cpp`](tp1_cpu.cpp)。它另外创建供 kernel 使用的 `d_x`、`d_y` 数组，模拟输入和输出复制，按 `16` 个块、每块 `64` 个线程遍历，并在 `kernel` 函数中计算 `i = block_idx * block_dim + thread_idx`；超出 `N` 的线程直接返回。运行命令：

```sh
g++ -std=c++17 -O2 tp1_cpu.cpp -o tp1_cpu
./tp1_cpu
```

这里的逐线程循环是串行模拟：保留了原程序的索引和数据流，但不模拟 GPU 实际的并行调度。
