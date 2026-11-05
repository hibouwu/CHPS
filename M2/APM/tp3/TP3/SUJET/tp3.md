# APM — TP3：原理讲解与本机对照

**M2 — Architecture et programmation d’accélérateurs matériels, 2026–2027**  
**M2 — 硬件加速器体系结构与编程，2026–2027 学年**  
Enseignant / 教师：adrien.roussel@cea.fr

[原题 PDF](tp3.pdf) · [TP3 入口](../../README.md) · [完整程序](../SOLUTION/dgemm_tp3.cu) · [实测记录](../RESULTS/local-2026-11-05/README.md)

**ROMEO 作业已完成，请用 [GH200 逐题实测解答](tp3_romeo.md) 获取目标集群的答案。** 本页保留详细原理和最初的 RTX 5070 Laptop GPU 数据；例如教师 kernel 在本机理论 occupancy 为 66.67%，在 ROMEO 为 100%。具体资源值与 SASS 分布不能跨平台直接套用。[ROMEO 完整记录](../RESULTS/romeo-817906/README.md)

> Les objectifs sont de calculer l’occupation d’un kernel sur le GPU et d’optimiser son exécution. Ce TP prolonge le DGEMM utilisant des accès coalescés et de la mémoire partagée.

本实验延续使用合并访问和共享内存的 DGEMM：先计算一个 SM 上允许驻留多少 block、多少 warp，再通过提高线程内数据复用来优化执行。各题保持 PDF 顺序；法语题干修正了拼写和排版，答案中明确区分原始代码与修正版。

## 阅读前先明确：我们计算什么？

SM 是 GPU 中承载线程块执行的处理单元。一个 block 必须整体分配到一个 SM，其线程分为若干 warp。warp 的线程数由 `prop.warpSize` 给出，本机是 32。驻留（active / resident）意味着资源已经分配给它；不意味着它在当前周期一定能够发射指令。

$$
\mathrm{Occupancy}_{\mathrm{theoretical}}
=\frac{\text{可同时驻留的 warp 数/SM}}{\text{硬件最大 warp 数/SM}}\times100\%.
$$

> L’API d’occupancy prédit une capacité de résidence pour un kernel et une configuration donnés. Elle ne mesure ni l’activité réelle pendant l’exécution ni les performances. Un grand nombre de warps résidents peut aider à masquer les latences, sans garantir que davantage de warps soient prêts à exécuter une instruction.

CUDA occupancy API 给出特定 kernel、block 大小及动态共享内存申请量对应的**理论驻留容量**。实际平均 occupancy 还受网格大小、尾部 block 和执行过程影响；这里没有运行性能分析器测量实际平均 occupancy。

本实验的矩阵按行存储，计算：

$$
C_{M\times N}\leftarrow\alpha A_{M\times K}B_{K\times N}+\beta C_{M\times N}.
$$

教师 kernel 的约定是 `blockIdx.x` 选择输出的行 tile，`blockIdx.y` 选择列 tile；每个 block 计算一个 $32\times32$ 输出 tile，每个线程计算其中一个元素，因此使用 1024 线程，即 32 个 warp。这里的 x/y 是程序的映射约定。

### 原始代码与解答版本

教师文件 [dgemm-shared.cu](../CODE/dgemm-shared.cu)、[Makefile](../CODE/Makefile)、[parse_sass.sh](../CODE/parse_sass.sh) 和原题 PDF 均原样保留。完整解答放在 `SOLUTION/`，不要直接用教师 `main` 验证性能或正确性：

| 原始文件中的情况 | 对题目或运行的影响 | 解答中的处理 |
|---|---|---|
| 两个静态共享数组共 16 KiB，启动时又传入 16 KiB 动态共享内存 | 实际用户申请共 32 KiB；`sharedSizeBytes` 仅报告静态部分 | 对原始启动单独报告 32 KiB；修正版动态参数为 0 |
| 使用向上取整网格，却没有处理边界 | 默认 `N=1000` 时读写越界；K 尾块也不完整 | 安全版本越界加载补 0，仅在有效行列写回；所有线程仍到达 barrier |
| `free(A)` 后又 `cudaFree(A)`，B/C 同样如此 | 释放了错误的地址，设备分配没有正确释放 | 释放 `dA/dB/dC/dC0`；主机数组由 `std::vector` 管理 |
| `DBG` 只打印局部值，CPU 参考覆盖 C | 不能构成全矩阵正确性检查 | 保存非零初始 C，使用独立 CPU 参考与逐元素 GPU 版本对照 |
| 没有系统检查 CUDA 返回值 | 启动失败可能被误当成性能结果 | CUDA 调用、启动、同步均检查错误 |

`SOLUTION/dgemm_tp3.cu` 包含教师源文件时仅重命名其 `main`，调用的原始 `dgemm_shared` 函数体不变。原始 kernel 仅在 M、N、K 都是 32 的倍数时执行；其他尺寸只执行安全版本。

### 本机实测的固定上下文

2026-11-05，RTX 5070 Laptop GPU，计算能力 12.0，36 SM；CUDA Runtime 13.0，Clang 22.1.8，目标 `sm_120`。以下数值来自这次编译生成的二进制，换 GPU、编译器或选项后应重新查询。

| 查询项 | 本机值 |
|---|---:|
| `prop.sharedMemPerMultiprocessor` | 102400 B = 100 KiB |
| `prop.sharedMemPerBlock` | 49152 B = 48 KiB |
| `prop.sharedMemPerBlockOptin` | 101376 B = 99 KiB |
| `prop.reservedSharedMemPerBlock` | 1024 B |
| `prop.maxThreadsPerMultiProcessor` | 1536 |
| `prop.maxThreadsPerBlock` | 1024 |
| `prop.regsPerMultiprocessor` / `prop.regsPerBlock` | 65536 / 65536 个 32-bit 寄存器 |
| `prop.maxBlocksPerMultiProcessor` | 24 |
| `prop.warpSize` | 32 |

来源：[设备与 kernel 查询日志](../RESULTS/local-2026-11-05/run1/case_256_256_256.log)。硬件属性以运行时查询为准，不能将不同计算能力的 Blackwell GPU 参数混用。

## I. Multiplication de matrices — DGEMM 分析

### 1. GPU Occupancy

为避免原题中的符号混淆，将共享内存、线程和寄存器的 block 上限分别写为 $B_S$、$B_T$、$B_R$。PDF 在后两节也使用了 `Blocs_SMEM`，这里修正这个下标笔误。

#### 1.1 La limite de la mémoire partagée — 共享内存限制

##### Q1 — 查询 SM 与 block 的共享内存上限

> **Question.** Grâce à `cudaGetDeviceProperties`, obtenez la taille maximale de SMEM disponible par SM ainsi que la taille maximale de SMEM allouable par un seul bloc.

**题目：** 使用 `cudaGetDeviceProperties`，查询每个 SM 的共享内存容量，以及单个 block 可分配的共享内存上限。

> **Réponse.** Utiliser `sharedMemPerMultiprocessor`, `sharedMemPerBlock` et `sharedMemPerBlockOptin`. La limite avec opt-in nécessite une configuration explicite du kernel pour les grandes allocations dynamiques ; elle n’est pas automatiquement la limite du lancement courant.

**解答：** 查询代码如下。`CUDA_CHECK` 定义在[完整程序](../SOLUTION/dgemm_tp3.cu)中，后续片段复用这里的 `prop`、`attr` 和 `device`。

```cpp
int device = 0;
CUDA_CHECK(cudaGetDevice(&device));
cudaDeviceProp prop{};
CUDA_CHECK(cudaGetDeviceProperties(&prop, device));
printf("SM: %zu B\n", prop.sharedMemPerMultiprocessor);
printf("block (default): %zu B\n", prop.sharedMemPerBlock);
printf("block (opt-in): %zu B\n", prop.sharedMemPerBlockOptin);
```

本机分别为 **100 KiB/SM、48 KiB/block 默认上限、99 KiB/block opt-in 上限**。大于默认上限的动态共享内存需要显式 opt-in；`cudaFuncAttributePreferredSharedMemoryCarveout` 只是共享内存与 L1 容量划分的偏好，不能代替 opt-in。这里的 kernel 不需要超过 48 KiB。

##### Q2 — 查询 kernel 每个 block 的共享内存需求

> **Question.** `cudaFuncGetAttributes` fournit la quantité de mémoire partagée demandée par bloc relative au kernel. Affichez-la.

**题目：** 用 `cudaFuncGetAttributes` 查询并输出 kernel 每个 block 的共享内存需求。

> **Réponse.** `attr.sharedSizeBytes` donne la mémoire partagée statique : 16384 octets. Ajouter la mémoire dynamique indiquée au lancement. Le lancement fourni réserve 16384 octets dynamiques supplémentaires, soit 32768 octets utilisateur par bloc au total.

**解答：**

```cpp
cudaFuncAttributes attr{};
CUDA_CHECK(cudaFuncGetAttributes(&attr, dgemm_shared));
size_t dynamic_bytes = 2 * 32 * 32 * sizeof(double); // lancement fourni
size_t user_smem = attr.sharedSizeBytes + dynamic_bytes;
printf("static=%zu dynamic=%zu total=%zu B\n",
       attr.sharedSizeBytes, dynamic_bytes, user_smem);
```

静态数组 `As[32*32]` 和 `Bs[32*32]` 的总大小为：

$$
S_{\mathrm{static}}=2\times32\times32\times8=16384\ \mathrm{B}.
$$

原始 `<<<grid, block, 16384, stream>>>` 的第三个参数还会**额外申请** 16384 B 动态共享内存，虽然函数体没有使用 `extern __shared__`。所以原始启动的用户共享内存需求是 **32768 B/block**。将第三个参数改为 `0` 才是只申请这两个静态数组的 **16384 B/block**。

`attr.maxDynamicSharedSizeBytes` 是允许的动态申请上限，也不能作为本次申请量。占用计算还可能计入系统保留空间和分配取整，交由 Q12 的 API 核对。[CUDA 函数属性说明](https://docs.nvidia.com/cuda/cuda-runtime-api/structcudaFuncAttributes.html)

##### Q3 — 由共享内存计算 block 数量上限

> **Question.** À partir des deux questions précédentes, calculez la quantité maximale physique de blocs que la mémoire partagée du SM peut contenir simultanément avant de saturer.

**题目：** 根据 SM 容量和每个 block 的需求，计算只考虑共享内存时的同时驻留 block 数量上限。

> **Réponse.** Dans le modèle simplifié du sujet, $B_S=\lfloor S_{SM}/S_{bloc}\rfloor$. On obtient 3 pour le lancement fourni, et 6 après suppression de la réservation dynamique inutile. Ces nombres ne sont pas encore le nombre final de blocs résidents.

**解答：** 按原题的简化公式：

$$
B_S=\left\lfloor\frac{S_{SM}}{S_{\mathrm{static}}+S_{\mathrm{dynamic}}}\right\rfloor.
$$

原始启动：$\lfloor102400/32768\rfloor=\boxed{3}$；去掉多余动态内存后：$\lfloor102400/16384\rfloor=\boxed{6}$。

这是**只计用户共享内存的容量上界**。本机还有 1024 B/block 的保留共享内存；例如按 $16384+1024$ 计算只能放下 5 块，此外还要考虑实际 carveout 和分配粒度。后面本机最终受线程或寄存器限制，这个差异不改变最终的 occupancy。若用户共享内存为 0，公式分母不能取 0，应将这一项视为不限制。

#### 1.2 Threads — 线程限制

##### Q4 — 查询每个 SM 的最大线程数

> **Question.** Grâce à `cudaGetDeviceProperties`, récupérez le nombre maximal de threads par SM.

**题目：** 查询每个 SM 的最大驻留线程数。

> **Réponse.** Lire `prop.maxThreadsPerMultiProcessor` : 1536 threads sur le GPU testé. Ne pas confondre cette valeur avec `maxThreadsPerBlock`, qui vaut 1024.

**解答：**

```cpp
printf("threads/SM = %d\n", prop.maxThreadsPerMultiProcessor);
```

答案为 **1536 threads/SM**，单个 block 的最大线程数则是 **1024**。

##### Q5 — 由线程数计算 block 数量上限

> **Question.** Calculez le nombre maximum théorique de blocs qu’un SM peut exécuter simultanément à partir du nombre de threads par bloc utilisé.

**题目：** 根据每个 block 的线程数，计算只考虑线程容量时每个 SM 可同时驻留的 block 数。

> **Réponse.** Avec 1024 threads par bloc, $B_T=\lfloor1536/1024\rfloor=1$. Les 512 places restantes ne peuvent pas accueillir la moitié d’un autre bloc de 1024 threads.

**解答：**

$$
T_b=32\times32=1024,\qquad
B_T=\left\lfloor\frac{1536}{1024}\right\rfloor=\boxed{1}.
$$

一个 block 不能拆开驻留在多个 SM 上，因此剩余的 512 个线程名额放不下第二个完整 block。

#### 1.3 La limite des registres — 寄存器限制

##### Q6 — 查询每线程和每 warp 的寄存器需求

> **Question.** Avec `cudaFuncGetAttributes`, affichez le nombre de registres utilisés par thread et calculez la valeur par warp.

**题目：** 查询每个线程的寄存器数量，并计算每个 warp 的原始需求。

> **Réponse.** `attr.numRegs` vaut 28 pour le kernel fourni dans cette compilation. Un warp de 32 threads demande donc $28\times32=896$ registres de 32 bits avant arrondi d’allocation.

**解答：**

```cpp
printf("registers/thread = %d\n", attr.numRegs);
printf("registers/warp (raw) = %d\n", attr.numRegs * prop.warpSize);
```

本次教师 kernel 为 **28 个 32-bit 寄存器/thread**，原始需求为 **896 个寄存器/warp**。寄存器计数的单位不是字节，也不是 `double` 变量个数；一个 `double` 的值需要两个 32-bit 寄存器。这个值来自编译器资源分配，不能只数源码局部变量来得到。

##### Q7 — 按分配粒度取整，计算每个 block 的寄存器需求

> **Question.** En utilisant l’arrondi à l’unité d’allocation des registres présenté dans le sujet, déterminez le nombre de warps par bloc puis le nombre de registres par bloc.

**题目：** 按原题给出的寄存器分配粒度取整，计算每个 block 的 warp 数及寄存器需求。

> **Réponse.** Dans le modèle pédagogique avec une unité de 256 registres par warp : $R_w=\lceil896/256\rceil\times256=1024$, $W_b=\lceil1024/32\rceil=32$, puis $R_b=1024\times32=32768$ registres.

**解答：** 原题的 `getRegisterAllocationUnitSize` 返回的是**分配单位**，不是已经分配好的每 warp 寄存器总数。按题设的 $U=256$：

$$
W_b=\left\lceil\frac{T_b}{W}\right\rceil=32,
\quad R_w=U\left\lceil\frac{rW}{U}\right\rceil
=256\left\lceil\frac{28\times32}{256}\right\rceil=1024,
$$

$$
R_b=W_bR_w=32\times1024=\boxed{32768}.
$$

```cpp
auto round_up = [](size_t value, size_t unit) {
    return (value + unit - 1) / unit * unit;
};
int threads = 1024;
int warps_per_block = (threads + prop.warpSize - 1) / prop.warpSize;
size_t registers_per_warp = round_up(attr.numRegs * prop.warpSize, 256);
size_t registers_per_block = registers_per_warp * warps_per_block;
```

必须用向上取整计算 warp 数，例如 33 线程占 2 个 warp。原题中的 `major >= 3` 不能证明所有后续架构都遵循相同资源分配规则；这里把它作为课堂模型。实际计算还可能受 SM 子分区、warp 分配粒度等约束，Q12 使用 CUDA API 核对。

##### Q8 — 由寄存器计算 block 数量上限

> **Question.** Avec le nombre maximal de registres par SM et le nombre de registres nécessaires par bloc, combien de blocs peut-on exécuter simultanément sous cette contrainte ?

**题目：** 根据每个 SM 的寄存器总量与每个 block 的需求，计算只考虑寄存器时可同时驻留的 block 数。

> **Réponse.** `prop.regsPerMultiprocessor` vaut 65536. Le modèle donne $B_R=\lfloor65536/32768\rfloor=2$. Il faut aussi respecter la limite de registres par bloc.

**解答：**

$$
B_R=\left\lfloor\frac{R_{SM}}{R_b}\right\rfloor
=\left\lfloor\frac{65536}{32768}\right\rfloor=\boxed{2}.
$$

这里的寄存器容量允许 2 个 block，线程容量却只允许 1 个。资源约束必须同时满足。

#### 1.4 Occupation sur GPU — 汇总驻留上限

##### Q9 — 计算每个 SM 的最大 warp 数

> **Question.** Calculez le nombre maximal de warps actifs par SM à partir des propriétés du device.

**题目：** 根据设备属性计算 SM 最大驻留 warp 数。

> **Réponse.** $W_{max}=1536/32=48$ warps par SM.

**解答：**

$$
W_{max}=\frac{\texttt{prop.maxThreadsPerMultiProcessor}}{\texttt{prop.warpSize}}
=\frac{1536}{32}=\boxed{48}.
$$

##### Q10 — 计算当前 kernel 可驻留的 warp 数

> **Question.** À partir du minimum entre les trois nombres de blocs calculés précédemment, calculez combien de warps peuvent être actifs en même temps sur un SM.

**题目：** 取上述三种 block 数上限的最小值，计算每个 SM 可同时驻留的 warp 数。

> **Réponse.** Pour le lancement fourni, $B=\min(3,1,2)=1$ ; on obtient $W_{actifs}=1\times32=32$. Il faut également respecter le maximum matériel de blocs et de warps par SM.

**解答：** 按题设计算：

$$
B_{\mathrm{sujet}}=\min(B_S,B_T,B_R)=\min(3,1,2)=1,
\qquad W_{actifs}=B_{\mathrm{sujet}}W_b=\boxed{32}.
$$

更完整的手算还应纳入硬件 block 数上限及 warp 容量：

$$
B=\min\left(B_S,B_T,B_R,
\texttt{prop.maxBlocksPerMultiProcessor},
\left\lfloor\frac{W_{max}}{W_b}\right\rfloor\right).
$$

此外要先检查单 block 是否超过线程、共享内存、寄存器上限。这里 $\min(3,1,2,24,1)=1$，结果不变。去掉多余动态共享内存后，$B_S$ 变大，最终仍是 1。

##### Q11 — 计算 occupancy

> **Question.** Calculez l’occupancy.

**题目：** 计算理论 occupancy。

> **Réponse.** $\mathrm{Occupancy}=32/48\times100\%=66{,}67\%$.

**解答：**

$$
\mathrm{Occupancy}=\frac{BW_b}{W_{max}}\times100\%
=\frac{1\times32}{48}\times100\%=\boxed{66.67\%}.
$$

它不等于 `nvidia-smi` 的 GPU utilization，也不是 FLOP 利用率。若网格只有一个 block，资源模型仍会给出这个单 SM 驻留容量，但大部分 SM 根本分不到工作。

#### 1.5 Vérification par l’API CUDA — API 核对

##### Q12 — 用 CUDA occupancy API 核对

> **Question.** Utilisez `cudaOccupancyMaxActiveBlocksPerMultiprocessor` et vérifiez sa valeur par rapport au résultat précédent.

**题目：** 使用该 API，核对前面手算的结果。

> **Réponse.** L’API renvoie un nombre de blocs par SM, pas directement un pourcentage. Avec 1024 threads et 16384 octets dynamiques, elle renvoie 1 bloc, donc 32 warps et 66,67 %. Avec 0 octet dynamique, elle renvoie également 1 bloc.

**解答：**

```cpp
int active_blocks = 0;
CUDA_CHECK(cudaOccupancyMaxActiveBlocksPerMultiprocessor(
    &active_blocks, dgemm_shared, 1024, dynamic_bytes));
int active_warps = active_blocks * ((1024 + prop.warpSize - 1) / prop.warpSize);
double occupancy = 100.0 * active_warps /
                   (prop.maxThreadsPerMultiProcessor / prop.warpSize);
printf("blocks=%d warps=%d occupancy=%.2f%%\n",
       active_blocks, active_warps, occupancy);
```

最后一个参数必须与真实启动中的**动态**共享内存字节数一致。不要把静态与动态总和传进去，否则 API 会再次加上静态部分。本次原始动态参数为 16384；修正版为 0。

本机两种启动都返回 **1 block/SM、32 warp/SM、66.67%**，与手算最终结果一致。如果以后不一致，应检查静态/动态内存、保留量、分配粒度、block 硬件上限、编译后二进制及 SM 子分区限制。[CUDA occupancy API](https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__OCCUPANCY.html)

#### 1.6 Conclusion — 分析结果

##### Q13 — 对当前 kernel 的 occupancy 得出结论

> **Question.** Que concluez-vous de l’occupation du kernel sur GPU ?

**题目：** 对该 kernel 的 GPU occupancy 有什么结论？

> **Réponse.** Sur le GPU testé, la taille de 1024 threads par bloc limite la résidence à un seul bloc, soit 66,67 %. Retirer la mémoire dynamique inutilisée économise une ressource mais ne change pas ici cette limite. Pour réduire le nombre de threads tout en conservant un tile de sortie de 32×32, on peut confier plusieurs résultats à chaque thread. Il faudra vérifier le coût en registres et mesurer le temps : une meilleure occupation n’est pas une garantie de meilleures performances.

**解答：** 当前首要驻留限制是 **1024 线程/block 与 1536 线程/SM 不匹配**。去掉额外申请的动态共享内存是合理修正，但本机 occupancy 仍为 66.67%。接下来让一个线程负责多个输出，可以用较少线程完成同样大的输出 tile，并增加复用；是否提高 occupancy，要看新 kernel 的寄存器与共享内存需求，是否加速则要计时验证。

实际 Q17 中每线程寄存器从安全基线的 32 增至 64，API 允许 4 个 256 线程的 block，同时仍是 32 个 warp，因此 occupancy **仍为 66.67%**。这是一次完整的“提出优化 → 编译查询 → 检查约束”的结果。

### 2. Analyse statique — SASS 静态分析

##### Q14 — 提取 kernel 的 SASS

> **Question.** Essayez d’extraire le SASS de la dernière version de DGEMM implémentée.

**题目：** 提取 DGEMM 实现的 SASS。

> **Réponse.** Utiliser `cuobjdump --dump-sass`. Si le binaire contient plusieurs kernels ou architectures, sélectionner le kernel et la cible étudiés avant de compter les instructions.

**解答：** 在 `SOLUTION/` 中编译后执行：

```bash
cuobjdump --dump-sass dgemm_tp3.exe > all_kernels.sass
cuobjdump --dump-sass --function _Z12dgemm_sharediiidPKdS0_dPd \
    dgemm_tp3.exe > original.sass
bash ../CODE/parse_sass.sh original.sass > original_counts.md
```

`_Z12dgemm_sharediiidPKdS0_dPd` 是教师函数本次构建的符号名，可从 `Function :` 行确认。解答程序还包含安全基线与优化版，不能把三个 kernel 的计数混在一起。当前只构建 `sm_120`；多架构二进制还应按架构分别分析。

已保留 [原始 kernel SASS](../RESULTS/local-2026-11-05/run1/original.sass)、[安全基线 SASS](../RESULTS/local-2026-11-05/run1/shared_safe.sass)、[优化版 SASS](../RESULTS/local-2026-11-05/run1/tiled_tm4.sass)。命令语义参见 [NVIDIA Binary Utilities](https://docs.nvidia.com/cuda/cuda-binary-utilities/index.html)。

##### Q15 — 指令统计与各类操作的含义

> **Question.** Avec `parse_sass.sh`, donnez le type d’opération le plus exécuté et expliquez à quoi correspond chaque type. Le script génère un tableau Markdown trié par nombre d’occurrences décroissant.

**题目：** 用脚本统计指令分布，指出数量最多的类型，并解释指令含义。

> **Réponse.** Le script compte des occurrences **statiques**, pas les exécutions dynamiques. Dans notre binaire, le kernel fourni contient 112 instructions comptées ; `NOP` arrive en tête avec 25 occurrences, puis `IMAD` avec 12. `LDS` apparaît 6 fois et `DFMA` 5 fois. Il serait incorrect d’affirmer que `LDS` est nécessairement l’instruction la plus exécutée pendant le calcul.

**解答：** 实际运行教师脚本得到下表前几项，完整分布见[原始统计表](../RESULTS/local-2026-11-05/run1/original_counts.md)：

| 指令 | 静态次数 | 占 112 条的比例 |
|---|---:|---:|
| NOP | 25 | 22.32% |
| IMAD | 12 | 10.71% |
| LDC | 7 | 6.25% |
| MOV / LEA / LDS | 各 6 | 各 5.36% |
| LDCU / DFMA | 各 5 | 各 4.46% |

本次**静态数量最多的是 `NOP`**。其中部分出现在正常退出后的填充区；不能据此得出运行时间由 NOP 主导。循环中的一条指令可执行许多次，循环外的指令可能只执行一次，谓词也影响线程是否实际执行操作。循环展开、向量加载和编译器调度都会改变静态分布。

| 原始统计中出现的指令类型 | 含义 |
|---|---|
| `LDG` / `STG` | 从全局内存加载 / 向全局内存存储 |
| `LDS` / `STS` | 从共享内存加载 / 向共享内存存储；如 `.64`、`.128` 后缀表示访问宽度 |
| `LDC` / `LDCU` | 常量内存加载 / 加载到 uniform 寄存器；可能用于 kernel 参数 |
| `DFMA` / `DMUL` | FP64 融合乘加 / FP64 乘法；一个 DFMA 对应 2 FLOP |
| `HFMA2` | 两路半精度融合乘加；出现一条此指令不代表整个 DGEMM 改用了半精度 |
| `IMAD` | 整数乘加，常用于地址与下标计算 |
| `IADD` / `IADD3` / `UIADD3` | 整数加法 / 三输入整数加法 / uniform 整数加法 |
| `LEA` / `ULEA` | 地址生成 / uniform 地址生成 |
| `MOV` / `UMOV` | 普通 / uniform 寄存器数据移动 |
| `S2R` / `S2UR` | 将线程/块等特殊寄存器内容读到普通 / uniform 寄存器 |
| `ISETP` / `UISETP` | 整数比较并生成普通 / uniform 谓词 |
| `LOP3` | 三输入逻辑查找表运算 |
| `SHF` / `USHF` | 普通 / uniform 漏斗移位，常用于下标与位操作 |
| `BRA` / `EXIT` | 分支 / 退出 kernel |
| `BAR` | block 内 barrier 同步 |
| `NOP` | 无操作，可能用于调度或代码填充 |

uniform 寄存器用于 warp 统一的数值。教师脚本将这些新指令中的一部分统一显示成“计算/控制指令”，上表补充了说明。脚本按助记符统计并去掉后缀，因此 `LDS.64` 和 `LDS.128` 都算作一条 `LDS`；数量也不能直接换算为读取字节数。新架构或不同反汇编格式还需检查解析器是否支持其谓词形式。

##### Q16 — 从 LDS 与 FMA 延迟讨论优化方向

> **Question.** Une instruction de type LDS coûte entre 20 et 40 cycles, et une FMA entre 4 et 8 cycles. Quelle conclusion pouvez-vous faire ?

**题目：** 若 LDS 延迟为 20–40 cycles、FMA 为 4–8 cycles，可以得出什么结论？

> **Réponse.** En prenant ces valeurs comme hypothèses du sujet, une dépendance sur un chargement partagé peut coûter davantage qu’une opération arithmétique. Réutiliser une valeur chargée dans plusieurs FMA et garder plusieurs accumulateurs indépendants est donc une piste pertinente. Les latences ne s’additionnent pas directement en un temps d’exécution : chevauchement, débit, dépendances et architecture interviennent. Les valeurs indiquées ne sont pas des mesures de notre GPU.

**解答：** 若每读取两个共享内存操作数只做一次乘加，读取后的依赖等待可能难以隐藏。让读入的值参与多次 FMA，可以减少单位计算对应的共享内存读取，并用多个独立累加器增加可调度的计算。

但不能将静态 `LDS` 数量乘以 20–40，再将 FMA 数量乘以 4–8，就声称测出了时间或瓶颈。这些是题设延迟假设，未在本机测量；延迟也不同于吞吐率，多 warp 与独立指令可以重叠执行。对于 DGEMM，还应区分 FP64 的 `DFMA` 与其他精度的 FMA。当前证据足以提出线程内复用这一方向，尚不足以认定运行时间主要由 LDS 延迟决定。

## II. Optimisation — 线程内复用

##### Q17 — 提高每个线程的算术强度

> **Question.** À partir du constat précédent, augmentez l’intensité arithmétique par thread pour améliorer les performances.

**题目：** 根据前面的分析，提高每个线程的算术强度，并验证优化效果。

> **Réponse.** Chaque thread calcule quatre éléments de C dans une même colonne. Pour chaque k, il charge une valeur de B et la réutilise dans quatre produits, avec quatre valeurs de A et quatre accumulateurs. Le bloc conserve un tile de sortie de 32×32 et 16 KiB de mémoire partagée, mais utilise 256 threads au lieu de 1024. Le code complet est `dgemm_safe<4>` dans le programme fourni.

**解答：** 将同一输出 tile 内的 4 行交给一个线程，仍保持 32 列。对 `tid=0...255`：

```cpp
int col = threadIdx.x % 32;
int row0 = (threadIdx.x / 32) * 4;
double acc[4] = {};
// As/Bs are populated cooperatively, then __syncthreads().
for (int k = 0; k < 32; ++k) {
    double b = Bs[k * 32 + col];
    for (int t = 0; t < 4; ++t)
        acc[t] = fma(As[(row0 + t) * 32 + k], b, acc[t]);
}
// __syncthreads() before replacing As/Bs with the next K tile.
```

例如 `tid=35` 时，`col=3`、`row0=4`，这个线程计算 tile 内的 `(4,3)`、`(5,3)`、`(6,3)`、`(7,3)`。`B[k,3]` 只读入一次，就供四个累加器使用。完整程序在编译期展开这些固定长度循环，最终指令选择以 SASS 为准。

原来每个 k，每个线程读取两个 `double`，完成 1 FMA；现在读取五个 `double`，完成 4 FMA。因此只考虑**线程从共享内存读取的逻辑操作数字节**：

$$
I_{\mathrm{old}}=\frac{2}{2\times8}=0.125\ \mathrm{FLOP/B},
\qquad
I_{\mathrm{new}}=\frac{4\times2}{(4+1)\times8}=0.2\ \mathrm{FLOP/B}.
$$

该比值提高 **1.6 倍**。等价地，计算 4 个输出的一个 k 步，从逻辑上 8 次共享操作数读取减为 5 次。它不是实测的共享内存事务数，也不是整个 kernel 相对于 DRAM 的算术强度。block 仍读取同样的 A/B tile、产生同样的 C tile，其理想全局内存复用没有因这个改动自动提高。

协作加载也必须随线程数变化。现在只有 256 线程，每个共享数组有 1024 项，每线程要加载 4 项：

```cpp
for (int p = threadIdx.x; p < 32 * 32; p += 256) {
    // Compute global row/column for this A/B entry.
    // Store the valid value, or 0.0 outside the matrix bounds.
}
__syncthreads();
```

只改 `blockDim` 为 256 而不改加载逻辑，会留下未初始化的共享内存；直接保留原来“一线程一个输出”的计算方式也会漏掉结果。边界线程不能在 barrier 前提前返回。完整实现已包括协作加载、K 尾块补 0、所有线程参与两次同步、输出边界判断以及每次计时前还原初始 C。

**本机资源结果：**

| 版本 | 线程/block | 寄存器/thread | 用户共享内存/block | API blocks/SM | API warps/SM | 理论 occupancy |
|---|---:|---:|---:|---:|---:|---:|
| 教师 kernel，额外动态申请保留 | 1024 | 28 | 32 KiB | 1 | 32 | 66.67% |
| 教师 kernel，去掉额外动态申请 | 1024 | 28 | 16 KiB | 1 | 32 | 66.67% |
| 安全基线 `dgemm_safe<1>` | 1024 | 32 | 16 KiB | 1 | 32 | 66.67% |
| 优化版 `dgemm_safe<4>` | 256 | 64 | 16 KiB | 4 | 32 | 66.67% |

优化版中，按课堂模型每块需要 $64\times256=16384$ 个寄存器，寄存器容量允许 4 块；4 块共 $4\times8=32$ warp。block 数增加了，warp 数并没有增加。

**正确性与计时结果：** 9 组尺寸检查通过；小尺寸对 CPU 做全量比较，1000 和 1024 阶对 CPU 检查 128 个确定性位置，并对两个安全 GPU 版本做全量比较。每次都使用非零 C、`alpha=1.25`、`beta=-0.5`，检查完整 DGEMM 语义。memcheck、racecheck、synccheck、initcheck 在记录的代表尺寸上均通过。

在每批 2 次预热、7 次 CUDA event 计时，取中位数的条件下，安全基线相对于优化版的时间比值为：

| 方阵阶数 | 第 1 批加速比 | 第 2 批加速比 | 第 3 批加速比 |
|---|---:|---:|---:|
| 256 | 1.041× | 1.041× | 1.041× |
| 1000 | 1.099× | 0.994× | 1.013× |
| 1024 | 1.022× | 1.054× | 1.043× |

大于 1 表示优化版更快；1000 阶第 2 批略慢。桌面 GPU 同时承担显示任务，未锁定频率，批间波动明显，因此可以报告实现了线程内复用且部分尺寸获得小幅改善，**不能声称所有尺寸稳定加速，也不能声称提高了本机 occupancy**。这些计时仅覆盖 kernel，排除主机与设备传输、C 重置及分配时间。完整时间、原始样本和限制见[验证记录](../RESULTS/local-2026-11-05/README.md)。

> **Conclusion expérimentale.** Le tiling par thread augmente la réutilisation logique en mémoire partagée, mais le coût en registres maintient ici l’occupancy à 66,67 %. Le gain temporel reste modeste et varie selon la taille et la série de mesures. On ne peut pas en déduire une accélération générale, ni une amélioration de l’occupancy effectivement mesurée.

## 复现与核对

在 `TP3/SOLUTION/` 中，CUDA 与宿主编译器匹配时：

```bash
make ARCH=sm_90           # GH200 示例；按实际 GPU 更换
./dgemm_tp3.exe 256
./dgemm_tp3.exe 63 65 37 7
python3 validate.py --compiler nvcc --arch sm_90 --output ../RESULTS/my-run
```

本机 Clang 路径：

```bash
python3 validate.py --compiler clang --arch sm_120 --output ../RESULTS/my-local-run
```

输出目录必须尚不存在，防止覆盖旧证据。脚本保留环境、编译命令及失败日志、资源属性、正确性、3 批计时、sanitizer、各 kernel 的 SASS 与教师脚本统计表，以及源文件和二进制 SHA-256。程序默认边长为 256，也支持 `M N K [repeats]`。

本机普通 `nvcc` 因 GCC 16 高于 CUDA 13.0 支持范围而失败，Clang 编译成功但给出“CUDA 版本高于其最新部分支持版本 12.9”的警告；两份日志都保留。这里没有跳过版本检查，也没有使用快速数学选项。本页数值属于本机运行，随后完成的 ROMEO 数据见 [GH200 实测版](tp3_romeo.md)。

参考定义：[设备属性](https://docs.nvidia.com/cuda/cuda-runtime-api/structcudaDeviceProp.html)、[函数属性](https://docs.nvidia.com/cuda/cuda-runtime-api/structcudaFuncAttributes.html)、[occupancy API](https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__OCCUPANCY.html)、[occupancy 与优化实践](https://docs.nvidia.com/cuda/cuda-c-best-practices-guide/index.html#occupancy)、[SASS 工具与指令](https://docs.nvidia.com/cuda/cuda-binary-utilities/index.html)。
