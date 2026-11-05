# APM — TP3：ROMEO GH200 逐题实测解答

2026–2027 学年 · 2026-11-05 实测 · [原题 PDF](tp3.pdf) · [详细原理与本机对照](tp3.md) · [完整代码](../SOLUTION/dgemm_tp3.cu) · [ROMEO 验证记录](../RESULTS/romeo-817906/README.md)

> Cette version répond aux Q1–Q17 avec les mesures du job Slurm 817906 sur `romeo-a052`, GPU GH200, CUDA 12.9, cible `sm_90`. Le job est terminé avec l’état `COMPLETED` et le code `0:0`.

本页使用 **ROMEO 作业 817906** 的实际结果作答，保持原题 Q1–Q17 顺序。环境为 GH200 120GB、132 SM、计算能力 9.0、nvcc 12.9.41、GCC 11.5.0；作业用时 28 秒，状态 **COMPLETED / 0:0**。原始运行日志、二进制和源快照已回传，48 个远端文件的哈希核对通过。

追加实测：[作业 818095 对比 5 与 6 blocks/SM](../RESULTS/romeo-818095/README.md)。同一优化源码默认编译为 42 寄存器/thread，API 返回 5 块、62.5%；增加 `--maxrregcount=40` 后实际为 40 寄存器/thread，API 返回 6 块、75%。以下原始答案保留默认配置结果，追加配置与计时见 Q17 末尾。

区分三个函数版本：教师原始 `dgemm_shared`（仅支持 M/N/K 为 32 的倍数）、边界安全基线 `dgemm_safe<1>`、每线程计算 4 个结果的 `dgemm_safe<4>`。原始启动还额外申请了未使用的 16 KiB 动态共享内存，因此另记录去掉该申请后的启动。以下 Q1–Q12 以教师原始 kernel 为对象，Q13、Q17 再比较安全基线和优化版。

理论 occupancy 是“资源允许驻留的 warp 数 / 硬件最大驻留 warp 数”。它与实际测得的平均 occupancy、GPU utilization、运算吞吐率和运行时间分别是不同指标。

**课堂讲解复核：** [作业 818143](../RESULTS/romeo-818143/README.md) 按 70:06–74:58 的课堂内容测试了原始 kernel：一维 `1024×1×1` 与正确改写索引后的二维 `32×32×1` 都是 **32 寄存器/thread、2 blocks/SM、64 warps/SM、100% 理论 occupancy**。这正是下文 Q1–Q13 的原始 kernel；此前的 5/6 块对应 Q17 每块 256 线程的优化版。

## Q1 — 查询 SM 与 block 的共享内存上限

> **Question.** Grâce à `cudaGetDeviceProperties`, obtenez la taille maximale de SMEM disponible par SM ainsi que la taille maximale de SMEM allouable par un seul bloc.

**题目：** 使用 `cudaGetDeviceProperties`，查询每个 SM 的共享内存容量，以及单个 block 可分配的共享内存上限。

> **Réponse.** Sur le GH200 : 233472 octets par SM, 49152 octets par bloc par défaut, et 232448 octets avec opt-in. Lire respectivement `sharedMemPerMultiprocessor`, `sharedMemPerBlock` et `sharedMemPerBlockOptin`.

**解答：** GH200 查询结果为 **228 KiB/SM、48 KiB/block 默认上限、227 KiB/block opt-in 上限**。后者需要显式配置，不能当作当前启动已申请的量。

```cpp
int device = 0;
CUDA_CHECK(cudaGetDevice(&device));
cudaDeviceProp prop{};
CUDA_CHECK(cudaGetDeviceProperties(&prop, device));
printf("SM=%zu default=%zu optin=%zu B\n", prop.sharedMemPerMultiprocessor,
       prop.sharedMemPerBlock, prop.sharedMemPerBlockOptin);
```

`CUDA_CHECK` 的定义及可编译完整程序见 [dgemm_tp3.cu](../SOLUTION/dgemm_tp3.cu)。

## Q2 — 查询 kernel 每个 block 的共享内存需求

> **Question.** `cudaFuncGetAttributes` fournit la quantité de mémoire partagée demandée par bloc relative au kernel. Affichez-la.

**题目：** 用 `cudaFuncGetAttributes` 查询并输出 kernel 每个 block 的共享内存需求。

> **Réponse.** `attr.sharedSizeBytes` vaut 16384 octets. Le lancement fourni ajoute 16384 octets dynamiques, soit 32768 octets utilisateur par bloc. Sans cette réservation inutile, le total est de 16384 octets.

**解答：** 两个静态数组合计：

$$S_{static}=2\times32\times32\times8=16384\ \mathrm{B}.$$

```cpp
cudaFuncAttributes attr{};
CUDA_CHECK(cudaFuncGetAttributes(&attr, dgemm_shared));
size_t dynamic_bytes = 16384; // third launch argument in the teacher's main
size_t total_user_bytes = attr.sharedSizeBytes + dynamic_bytes;
```

所以**教师原始启动申请 32 KiB/block**，去掉未使用的动态部分后为 **16 KiB/block**。`sharedSizeBytes` 只报告用户静态部分；本机还有 1024 B/block 系统保留量，最终用 occupancy API 核对。

## Q3 — 由共享内存计算 block 数量上限

> **Question.** À partir des deux questions précédentes, calculez la quantité maximale physique de blocs que la mémoire partagée du SM peut contenir simultanément avant de saturer.

**题目：** 根据 SM 容量和每个 block 的需求，计算只考虑共享内存时的同时驻留 block 数量上限。

> **Réponse.** Le modèle du sujet donne 7 blocs pour le lancement fourni, puis 14 si la mémoire dynamique inutilisée est supprimée. Ce sont uniquement des plafonds liés à la mémoire partagée.

**解答：** 按课堂公式，只计用户共享内存：

$$B_S=\left\lfloor\frac{233472}{32768}\right\rfloor=\boxed{7}.$$

去掉额外动态申请后：

$$B_S=\left\lfloor\frac{233472}{16384}\right\rfloor=\boxed{14}.$$

系统保留量、分配取整与实际 carveout 也可能限制驻留，因此这些比值不是最终 block 数。本次最终受线程/寄存器限制，手算与 API 的最终值一致。

## Q4 — 查询每个 SM 的最大线程数

> **Question.** Grâce à `cudaGetDeviceProperties`, récupérez le nombre maximal de threads par SM.

**题目：** 查询每个 SM 的最大驻留线程数。

> **Réponse.** `prop.maxThreadsPerMultiProcessor` vaut 2048 sur ce GH200. La limite par bloc reste 1024.

**解答：** **最大 2048 threads/SM，最大 1024 threads/block。** 两个属性含义不同：

```cpp
printf("threads/SM=%d threads/block=%d\n",
       prop.maxThreadsPerMultiProcessor, prop.maxThreadsPerBlock);
```

## Q5 — 由线程数计算 block 数量上限

> **Question.** Calculez le nombre maximum théorique de blocs qu’un SM peut exécuter simultanément à partir du nombre de threads par bloc utilisé.

**题目：** 根据每个 block 的线程数，计算只考虑线程容量时每个 SM 可同时驻留的 block 数。

> **Réponse.** Avec 1024 threads par bloc, le plafond est de deux blocs par SM : floor(2048/1024)=2.

**解答：** 原始 kernel 每个 block 有 $32\times32=1024$ 个线程，因此：

$$B_T=\left\lfloor\frac{2048}{1024}\right\rfloor=\boxed{2}.$$

与本机 RTX 5070 的 1536 threads/SM 不同，GH200 的线程容量正好能容纳两个这样的 block。

## Q6 — 查询每线程和每 warp 的寄存器需求

> **Question.** Avec `cudaFuncGetAttributes`, affichez le nombre de registres utilisés par thread et calculez la valeur par warp.

**题目：** 查询每个线程的寄存器数量，并计算每个 warp 的原始需求。

> **Réponse.** Le kernel fourni utilise 32 registres de 32 bits par thread dans cette compilation nvcc/SM90. Un warp demande donc 32×32=1024 registres avant arrondi.

**解答：** 本次 `attr.numRegs = 32`，所以每 warp 的原始需求为：

$$r=32,\qquad R_{warp,raw}=32\times32=\boxed{1024}.$$

```cpp
printf("registers/thread=%d raw/warp=%d\n", attr.numRegs,
       attr.numRegs * prop.warpSize);
```

单位是 32-bit 寄存器个数。安全基线与优化版分别为 40、42 个/thread，不能用教师 kernel 的 32 代替。

## Q7 — 按分配粒度取整，计算每个 block 的寄存器需求

> **Question.** En utilisant l’arrondi à l’unité d’allocation des registres présenté dans le sujet, déterminez le nombre de warps par bloc puis le nombre de registres par bloc.

**题目：** 按原题给出的寄存器分配粒度取整，计算每个 block 的 warp 数及寄存器需求。

> **Réponse.** Avec l’unité de 256 du modèle pédagogique : 1024 registres par warp après arrondi, 32 warps par bloc, puis 32768 registres par bloc.

**解答：** 按原题给出的 256 个寄存器分配单位：

$$W_b=\left\lceil\frac{1024}{32}\right\rceil=32,$$

$$R_w=256\left\lceil\frac{32\times32}{256}\right\rceil=1024,$$

$$R_b=W_bR_w=32\times1024=\boxed{32768}.$$

原题函数返回的是分配粒度，而不是每 warp 的实际总量。`major >= 3` 是题目给出的简化规则，不能作为所有架构资源分配规律的证明；这里最终仍需和 API 对照。

## Q8 — 由寄存器计算 block 数量上限

> **Question.** Avec le nombre maximal de registres par SM et le nombre de registres nécessaires par bloc, combien de blocs peut-on exécuter simultanément sous cette contrainte ?

**题目：** 根据每个 SM 的寄存器总量与每个 block 的需求，计算只考虑寄存器时可同时驻留的 block 数。

> **Réponse.** Le GH200 fournit 65536 registres par SM. Le modèle donne deux blocs : floor(65536/32768)=2.

**解答：** `prop.regsPerMultiprocessor = 65536`，因此：

$$B_R=\left\lfloor\frac{65536}{32768}\right\rfloor=\boxed{2}.$$

同时检查每 block 的寄存器上限。本次 32768 没有超过 `prop.regsPerBlock = 65536`。

## Q9 — 计算每个 SM 的最大 warp 数

> **Question.** Calculez le nombre maximal de warps actifs par SM à partir des propriétés du device.

**题目：** 根据设备属性计算 SM 最大驻留 warp 数。

> **Réponse.** Le nombre maximal de warps résidents par SM est 2048/32=64.

**解答：** GH200 的 warp 大小为 32：

$$W_{max}=\frac{\texttt{maxThreadsPerMultiProcessor}}{\texttt{warpSize}}
=\frac{2048}{32}=\boxed{64}.$$

这是硬件上限，不是当前 grid 中实际有多少 warp 在运行。

## Q10 — 计算当前 kernel 可驻留的 warp 数

> **Question.** À partir du minimum entre les trois nombres de blocs calculés précédemment, calculez combien de warps peuvent être actifs en même temps sur un SM.

**题目：** 取上述三种 block 数上限的最小值，计算每个 SM 可同时驻留的 warp 数。

> **Réponse.** Le minimum des trois plafonds est min(7,2,2)=2 blocs. Avec 32 warps par bloc, on obtient 64 warps par SM. Les limites matérielles de 32 blocs et de 64 warps sont également respectées.

**解答：** 教师原始启动：

$$B=\min(7,2,2)=2,\qquad W_{active}=2\times32=\boxed{64}.$$

加入硬件 block 数上限及 warp 容量：

$$B=\min\left(7,2,2,32,\left\lfloor64/32\right\rfloor\right)=2.$$

去掉多余动态共享内存后，仅第一项从 7 变成 14，最终仍为 2。

## Q11 — 计算 occupancy

> **Question.** Calculez l’occupancy.

**题目：** 计算理论 occupancy。

> **Réponse.** L’occupancy théorique du kernel fourni est 64/64×100%=100 %. Cette valeur n’est ni une mesure de l’activité moyenne ni une preuve de performance optimale.

**解答：** 教师 kernel 在这块 GH200 上的理论 occupancy 为：

$$\mathrm{Occupancy}=\frac{64}{64}\times100\%=\boxed{100\%}.$$

这与本机结果 **66.67%** 不同，必须按目标设备和真实二进制重算。理论 100% 不表示所有周期都有指令发射，也不表示所有 grid 大小都能让 132 个 SM 全部达到此容量。

## Q12 — 用 CUDA occupancy API 核对

> **Question.** Utilisez `cudaOccupancyMaxActiveBlocksPerMultiprocessor` et vérifiez sa valeur par rapport au résultat précédent.

**题目：** 使用该 API，核对前面手算的结果。

> **Réponse.** L’API renvoie 2 blocs par SM pour le kernel fourni, aussi bien avec 16384 octets dynamiques qu’avec zéro. Cela confirme les 64 warps et les 100 % calculés.

**解答：** 实际 API 返回 **2 blocks/SM**，对应 **64 warps/SM、100%**，与 Q10–Q11 一致。

```cpp
int blocks = 0;
CUDA_CHECK(cudaOccupancyMaxActiveBlocksPerMultiprocessor(
    &blocks, dgemm_shared, 1024, dynamic_bytes));
int warps = blocks * ((1024 + prop.warpSize - 1) / prop.warpSize);
double occupancy = 100.0 * warps /
                   (prop.maxThreadsPerMultiProcessor / prop.warpSize);
```

最后一个参数只传**动态**共享内存申请量，原始启动为 16384，修正后为 0，不能传静态加动态的总和。证据见[资源查询日志](../RESULTS/romeo-817906/case_256_256_256.log)。

## Q13 — 对当前 kernel 的 occupancy 得出结论

> **Question.** Que concluez-vous de l’occupation du kernel sur GPU ?

**题目：** 对该 kernel 的 GPU occupancy 有什么结论？

> **Réponse.** Le kernel fourni atteint déjà 100 % d’occupancy théorique sur ce GH200. On ne peut donc pas justifier l’optimisation uniquement par une augmentation de ce pourcentage. Le tiling par thread peut réduire les chargements et augmenter la réutilisation. La version sûre passe de 50 % à 62,5 %, tandis que la version fournie reste à 100 %.

**解答：** **教师原始 kernel 在 GH200 上已经达到理论 100%。** 所以不能照搬本机“1024 线程太大，只能放 1 个 block”的结论。

本次另外两个版本的资源结果为：

| 版本 | 寄存器/thread | API blocks/SM | warp/SM | 理论 occupancy |
|---|---:|---:|---:|---:|
| 教师 kernel | 32 | 2 | 64 | 100% |
| 安全基线 `dgemm_safe<1>` | 40 | 1 | 32 | 50% |
| 优化版 `dgemm_safe<4>` | 42 | 5 | 40 | 62.5% |

安全基线加入边界保护后的完整编译版本使用更多寄存器。应分别比较这些实现：优化版相对安全基线提高了理论 occupancy，但相对教师 kernel 降低了理论 occupancy。Q17 的大矩阵计时仍更快，说明性能还取决于数据复用、指令组织等因素。

## Q14 — 提取 kernel 的 SASS

> **Question.** Essayez d’extraire le SASS de la dernière version de DGEMM implémentée.

**题目：** 提取 DGEMM 实现的 SASS。

> **Réponse.** Extraire le SASS du binaire réellement exécuté avec `cuobjdump --dump-sass`, puis sélectionner le symbole du kernel pour éviter de mélanger plusieurs fonctions.

**解答：** 本次实际执行二进制已回传并保留。在 `SOLUTION/` 中可复现：

```bash
cuobjdump --dump-sass --function _Z12dgemm_sharediiidPKdS0_dPd \
  ../RESULTS/romeo-817906/dgemm_tp3.exe > original.sass
bash ../CODE/parse_sass.sh original.sass > original_counts.md
```

已保存[教师 kernel SASS](../RESULTS/romeo-817906/original.sass)、[安全基线 SASS](../RESULTS/romeo-817906/shared_safe.sass)和[优化版 SASS](../RESULTS/romeo-817906/tiled_tm4.sass)，均对应 `sm_90`。

## Q15 — 指令统计与各类操作的含义

> **Question.** Avec `parse_sass.sh`, donnez le type d’opération le plus exécuté et expliquez à quoi correspond chaque type. Le script génère un tableau Markdown trié par nombre d’occurrences décroissant.

**题目：** 用脚本统计指令分布，指出数量最多的类型，并解释指令含义。

> **Réponse.** Dans le kernel fourni compilé pour SM90, LDS est le mnémonique le plus fréquent : 48 occurrences sur 160, soit 30 %. DFMA apparaît 33 fois, soit 20,62 %. Le script compte des instructions statiques, pas les exécutions dynamiques.

**解答：** 本次 GH200 的[教师脚本统计](../RESULTS/romeo-817906/original_counts.md)为：

| 指令 | 静态出现次数 | 比例 | 含义 |
|---|---:|---:|---|
| LDS | 48 | 30.00% | 共享内存读取 |
| DFMA | 33 | 20.62% | FP64 融合乘加 |
| IMAD | 11 | 6.88% | 整数乘加，常用于索引与地址 |
| NOP | 10 | 6.25% | 无操作，可用于调度或填充 |
| LEA | 9 | 5.62% | 地址生成 |
| ULDC | 7 | 4.38% | 向 uniform 寄存器加载常量 |

其他指令含义：LDG/STG 为全局加载/存储，STS 为共享存储，LDC 为常量加载，DMUL 为 FP64 乘法；IADD3/UIADD3、UIMAD、LEA/ULEA、SHF/USHF、LOP3 用于整数、地址或逻辑计算；ISETP 生成条件谓词；S2R/S2UR/CS2R 读取特殊寄存器；UMOV 进行 uniform 数据移动；BAR 为 barrier，BRA/EXIT 为分支与退出。教师脚本对部分新指令只给出通用描述。

这里**静态数量最多的是 LDS**；但不能说它已被证明是“动态执行最多”或“最耗时”。原始本机 Clang/SM120 构建的静态第一名是 NOP，两种结果分别适用于各自二进制。

## Q16 — 从 LDS 与 FMA 延迟讨论优化方向

> **Question.** Une instruction de type LDS coûte entre 20 et 40 cycles, et une FMA entre 4 et 8 cycles. Quelle conclusion pouvez-vous faire ?

**题目：** 若 LDS 延迟为 20–40 cycles、FMA 为 4–8 cycles，可以得出什么结论？

> **Réponse.** Avec les latences données dans le sujet, réutiliser une valeur chargée en mémoire partagée dans plusieurs FMA est une piste cohérente. Cela ne démontre pas que LDS limite le temps total : latence, débit, dépendances et recouvrement sont distincts. Ces latences n’ont pas été mesurées ici.

**解答：** 把题目给出的 20–40 cycles 与 4–8 cycles 视作假设，可以提出：**减少每次 FMA 所需的共享内存读取，让一次加载服务于多次计算**。

不能把静态条数乘以延迟，再相加当作 kernel 时间。指令可能重叠执行，延迟与吞吐率不同，warp/线程内独立指令也会影响等待隐藏。DGEMM 使用的是 FP64 `DFMA`，也不能直接套用任意精度 FMA 的参数。本次没有测量这些指令延迟或用 NCU 定位瓶颈。

## Q17 — 提高每个线程的算术强度

> **Question.** À partir du constat précédent, augmentez l’intensité arithmétique par thread pour améliorer les performances.

**题目：** 根据前面的分析，提高每个线程的算术强度，并验证优化效果。

> **Réponse.** Chaque thread calcule quatre résultats de C dans la même colonne et réutilise une valeur de B dans quatre FMA. Le tile reste 32×32, avec 256 threads et 16 KiB de mémoire partagée. Sur le GH200, l’occupancy théorique passe de 50 % pour la base sûre à 62,5 %. À N=4096, le gain mesuré sur trois séries est de 2,337 à 2,352 fois par rapport à la base sûre, et de 1,705 à 1,721 fois par rapport au kernel fourni sans mémoire dynamique inutile.

**解答：** 完整实现为 [dgemm_safe<4>](../SOLUTION/dgemm_tp3.cu)，每线程保存 4 个累加器：

```cpp
int col = threadIdx.x % 32;
int row0 = (threadIdx.x / 32) * 4;
double acc[4] = {};
// As/Bs have been loaded cooperatively and synchronized.
for (int k = 0; k < 32; ++k) {
    double b = Bs[k * 32 + col];
    for (int t = 0; t < 4; ++t)
        acc[t] = fma(As[(row0 + t) * 32 + k], b, acc[t]);
}
```

每个 block 仍算一个 32×32 tile，但仅需 256 线程。共享数组有 1024 项，每线程通过步长 256 的循环加载 4 项；边缘元素补 0，所有线程到达两次 barrier，写回时检查输出边界。

相对于线程读取的逻辑共享内存字节，旧版每 k 用 2 个 double 做 1 FMA，新版用 5 个 double 做 4 FMA：

$$I_{old}=2/(2\times8)=0.125\ \mathrm{FLOP/B},$$

$$I_{new}=8/(5\times8)=0.2\ \mathrm{FLOP/B}.$$

该口径下提高 **1.6 倍**；这不是实测事务数，也不是相对 DRAM 的算术强度。block 的理想全局数据量仍相同。

寄存器取整后每 warp 为 $256\lceil42\times32/256\rceil=1536$ 个，每块 $1536\times8=12288$ 个。API 允许 5 块，共 $5\times8=40$ warp，occupancy 为 $40/64=62.5\%$。

三批实测，每批 2 次预热、7 次 CUDA event 计时，取中位数：

| 阶数 | 相对安全基线加速比，三批 | 相对教师 kernel（去掉多余动态申请），三批 |
|---|---|---|
| 256 | 1.028× / 1.028× / 1.026× | 0.927× / 0.929× / 0.932× |
| 1000 | 2.036× / 1.943× / 1.953× | 原始 kernel 不支持该边界尺寸 |
| 1024 | 1.952× / 2.053× / 1.946× | 1.583× / 1.674× / 1.584× |
| 2048 | 2.052× / 2.045× / 2.028× | 1.619× / 1.612× / 1.603× |
| 4096 | 2.352× / 2.337× / 2.342× | 1.721× / 1.705× / 1.710× |

大于 1 表示优化版更快。4096 阶第 1 批中位数为：安全基线 **38.878239 ms**，教师修正启动 **28.442656 ms**，优化版 **16.529312 ms**。256 阶相对教师 kernel 稍慢，所以不能声称所有尺寸都受益。

9 组基本尺寸以及新增的 2048、4096 阶检查均通过；大尺寸 CPU 为 128 个位置抽样，两个安全 GPU 版本做全量对照。代表尺寸的 memcheck、racecheck、synccheck、initcheck 全部通过。计时仅覆盖 kernel；未锁频、执行顺序固定，没有测实际平均 occupancy，也不能把总加速全部归因于某一个因素。原始样本、误差和全部限制见[ROMEO 验证记录](../RESULTS/romeo-817906/README.md)。

### Q17 追加验证：6 blocks/SM 能否实现？

> Le job 818095 confirme que la même source, compilée avec `--maxrregcount=40`, utilise 40 registres par thread et permet 6 blocs par SM selon l’API CUDA, soit 75 % d’occupancy théorique. La compilation par défaut conserve 42 registres et 5 blocs, soit 62,5 %. Aucun spill n’est rapporté dans les deux cas. Le gain en temps dépend de la taille : amélioration à N=2048, mais régression à N=4096.

**已实测可以。** 在同一份源码和同一块 GH200 上，默认编译的优化版为 **42 寄存器/thread、5 blocks/SM、62.5%**；增加 `--maxrregcount=40` 后，实际为 **40 寄存器/thread、6 blocks/SM、75%**，且无寄存器 spill。两版的正确性与代表尺寸 sanitizer 检查均通过。

三批中，40 寄存器版在 2048 阶相对默认版加速 **1.113–1.129 倍**，但在 4096 阶反而慢约 **4.0%–4.4%**，所以默认编译选项未改。这里的 6 是 CUDA API 确认的理论驻留容量，未测实际平均 occupancy；不能直接推断同学使用的源码或编译配置。完整命令、资源和计时见[作业 818095 对照记录](../RESULTS/romeo-818095/README.md)。
