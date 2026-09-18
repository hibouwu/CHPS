# GotoBLAS AVX-512 实现与调参计划

本文记录 AVX-512 GotoBLAS 风格 GEMM 的最小正确性路径与后续调参计划。当前仓库已经有一组真实的 AVX-512 正确性微内核，可由 `MATMUL_IMPL=omp_gotoblas_avx512` 与 `MATMUL_GOTO_KERNEL=avx512_*` 触发。

本文目标是把已经完成的最小实现边界写清楚，并保留后续候选内核形状、正确性验证矩阵和调参协议。当前 AVX-512 路径已经完成正确性接入，并已有 Stage 1/2/3 阶段性调参结果；这些结果仍不等同于最终固定配置验证，也不构成 AVX-512 相对 AVX2 的性能结论。

## 1. 范围与当前仓库状态

当前 GotoBLAS 风格路径位于 `src/gemm/GEMMGotoBLAS.cpp`。AVX2 路径仍由 `MATMUL_IMPL=omp_gotoblas_avx2` 触发，默认内核仍是 `avx2_8x8`，并保留原有 AVX2/FMA 检查与 AVX2 内核形状集合。运行条件仍是 `Matrix::matmul_into` 的输入没有转置。

`MATMUL_IMPL=omp_gotoblas_avx512` 现在不再是 AVX2 别名。该路径会检查 AVX-512F，选择 AVX-512 内核族，并在当前正确性版本中支持 `avx512_4x16`、`avx512_8x16`、`avx512_16x16`、`avx512_20x16`、`avx512_4x32`、`avx512_8x32` 和 `avx512_12x32`。如果用户在 AVX-512 路径下指定 AVX2 形状，例如 `avx2_8x8`，代码会报错而不是静默混用 AVX2 微内核。

本文边界仍然是正确性状态与阶段性调参计划。当前实现不声称最终 AVX-512 调参已完成；已有结论仅限于 Stage 1 内核形状筛选、Stage 2 单线程分块尺寸调参和 Stage 3 多线程 Mc/Nc 经验调参，尚未完成固定配置 final validation 和 AVX2 基线对比。

## 2. AVX-512 正确性实现状态

本节汇总当前最小 AVX-512 正确性路径的实现状态：入口、微内核、打包、边界块和测试覆盖。它描述的是已经接入的正确性能力，不包含调参或性能结论。

### 2.1 代码入口与分发接口

顶层选择器是 `MATMUL_IMPL`，解析逻辑在 `src/gemm/matmul_dispatch.cpp`。GotoBLAS 相关取值包括 `omp_gotoblas_avx2` 和 `omp_gotoblas_avx512`；二者都声明在 `include/gemm/matmul_internal.hpp`。公共实现入口分别是 `sgemm_omp_gotoblas_avx2` 和 `sgemm_omp_gotoblas_avx512`，其中 AVX-512 入口现在有独立 AVX-512F 检查。

微内核形状当前由内部 `KernelShape` 表和 `MATMUL_GOTO_KERNEL` 环境变量选择。AVX2 形状包括 `avx2_8x8`、`avx2_12x8`、`avx2_13x8`、`avx2_4x16`、`avx2_5x16` 和 `avx2_6x16`，并保留 `8x8` 这类既有短名。AVX-512 形状包括 `avx512_4x16`、`avx512_8x16`、`avx512_16x16`、`avx512_20x16`、`avx512_4x32`、`avx512_8x32` 和 `avx512_12x32`，没有添加 `4x16`、`8x16` 或 `4x32` 这类短名，以避免未来不同 ISA 家族之间的命名歧义。

`run_selected_microkernel` 负责把完整块分发给完整块内核，把边界块分发给对应边界内核，并按 ISA 家族拒绝不匹配的形状。分块参数通过 `MATMUL_MC`、`MATMUL_NC` 和 `MATMUL_KC` 进入，也兼容旧别名：`MATMUL_PACK_M`、`MATMUL_PACK_N` 和 `MATMUL_PACK_K`。这些访问器在进程内缓存第一次观察到的值，因此测试和基准测试驱动必须在第一次矩阵乘调用前设置这些环境变量。

### 2.2 AVX-512 已实现微内核与设计候选

当前 AVX-512 路径的实现默认形状是 `avx512_8x32`。它已经通过正确性路径接入，并与第 2 阶段单线程调参选出的默认路径候选保持一致。对 float32，单个 ZMM 寄存器有 16 个通道；`nr=32` 每行使用两个 ZMM 累加寄存器，分别覆盖低 16 列和高 16 列。

如果运行时未显式设置 `MATMUL_GOTO_KERNEL`，`MATMUL_IMPL=omp_gotoblas_avx512` 会选择 `avx512_8x32`。`avx512_8x16` 仍保留为已实现的正确性候选和筛选参考，但不再是 AVX-512 路径的默认形状。

当前 `nr=16` 系列内核对每个 `k` 将 `packed_B[k * nr : k * nr + 16]` 作为一个 ZMM 载入，再广播 `mr` 个 `packed_A[k * mr + i]` 值执行 FMA 更新。`nr=32` 系列每行使用两个 ZMM 累加寄存器，分别覆盖低 16 列和高 16 列。所有完整块内核都从 `C` 读取初始值，最后写回 `C`，保持与 AVX2 完整块内核一致的累加语义。

当前已经接入正确性路径的候选包括 `nr=16` 的 `mr=4,8,16,20`，以及 `nr=32` 的 `mr=4,8,12`。这只说明它们具备可运行的正确性路径，不应在没有指令组合、降频行为和工作负载计时数据之前声称任何形状更优。

### 2.3 打包与对齐要求

当前打包布局原则上可以复用。`packed_A[k * mr + i]` 保存 `A` 微面板的一列，并对缺失行补零。`packed_B[k * nr + j]` 保存 `B` 微面板的一行，并对缺失列补零。对于 AVX-512 按行组织的外积内核，这种布局合适：`nr=16` 系列每个 `B_r(p,:)` 由一个 ZMM 加载，`nr=32` 系列则由低 16 列和高 16 列两个 ZMM 加载。

对齐决策是统一将 `PackedWorkspace` 的 `packed_A` 和 `packed_B` 分配升级到 64 字节对齐。这个选择满足 AVX-512 打包工作区的需求，同时不破坏 AVX2，因为 64B 对齐也满足 AVX2 对 32B 对齐的要求。

外部矩阵 `C` 仍可使用非对齐或带掩码的载入 / 存储，因为行主序输出矩阵无法保证每一行、每一个列偏移都满足 64 字节对齐。对齐约束应优先作用于打包工作区。

### 2.4 边界块处理策略

AVX-512 当前使用带掩码的载入 / 存储处理 N 方向尾列。对 `nr=16` 系列，单个 `__mmask16` 表示最多 16 个有效列；对 `nr=32` 系列，低 16 列和高 16 列分别使用一个掩码。这样可以避免默认退回标量清理路径，并保持与完整块相同的算术结构。

M 方向尾行可以继续沿用当前策略：`pack_a_micro_panel` 对缺失行补零，边界内核只对有效行条件回写。这样算术路径仍然是向量化路径，同时避免写出逻辑输出块。

标量边界处理不是默认实现方案。当前正确性路径直接验证带掩码的 SIMD 边界路径，因为小 N 和边界密集的 NN 形状是目标工作负载的一部分。

### 2.5 正确性验证计划

正确性测试与朴素参考实现比较。当前 `tests/test_gemm_microkernels.cpp` 覆盖所有 AVX-512 形状的完整块 / 边界微内核；`tests/test_gemm_gotoblas_driver.cpp` 在 `TEST_GEMM_GOTOBLAS_IMPL=avx512` 模式下显式设置 `MATMUL_IMPL=omp_gotoblas_avx512`，并对每个 AVX-512 形状设置对应的 `MATMUL_GOTO_KERNEL` 后覆盖驱动端矩阵乘法。

当前 AVX-512 驱动测试矩阵对每个形状使用其自身的 `mr/nr` 生成完整块、多个完整块、M 边界、N 边界、M/N 同时边界，以及小 K 的 `K = 1, 2, 3, 5, 16`。其中 `avx512_8x16` 仍覆盖原始要求中的 `(8,128,16)`、`(16,256,32)`、`(9,128,16)`、`(7,128,16)`、`(8,128,17)`、`(8,128,31)`、`(8,128,1)`、`(9,128,17)` 和 `(3,5,7)`。

NN 真实形状覆盖包含 `(32,784,128)` 和 `(32,128,10)`。如果当前机器或 CI 不支持 AVX-512F，AVX-512 测试会输出清晰的跳过信息并返回成功，而不是错误失败。

## 3. AVX-512 分块参数建模

本节给出 AVX-512 分块尺寸候选的限制条件建模。它沿用 `BlockedSizeCherche.md` 中“先由寄存器、缓存、TLB 给出可行域，再由实验筛选”的思路，但只保留 AVX-512 第一轮调参所需的轻量推导。以下公式用于生成候选和过滤明显不合适的点，不构成性能结论。

### 3.1 符号与建模假设

当前 AVX-512 路径已经实现 `avx512_4x16`、`avx512_8x16`、`avx512_16x16`、`avx512_20x16`、`avx512_4x32`、`avx512_8x32` 和 `avx512_12x32` 的正确性内核，但分块尺寸建模仍以这些形状的可行域为边界。微内核更新的寄存器块与打包微面板仍记为 $C_r \in \mathbb{R}^{m_r \times n_r}$、$A_r \in \mathbb{R}^{m_r \times k_c}$、$B_r \in \mathbb{R}^{k_c \times n_r}$；外层宏面板记为 $A_c \in \mathbb{R}^{m_c \times k_c}$、$B_c \in \mathbb{R}^{k_c \times n_c}$。

当前打包语义是代码事实，需要单列保留：

$$
\texttt{packed\_A}[p \cdot m_r + i] = A_r(i,p),
\qquad
\texttt{packed\_B}[p \cdot n_r + j] = B_r(p,j).
$$

数据类型为 float32，元素字节数为 $S_{\text{data}}=4$。AVX-512 ZMM 寄存器在 float32 下包含 16 个通道，因此 $N_{\text{vec}}=16$。当前微内核的 SIMD 方向仍沿 $n_r$：每次 $p$ 迭代加载一个 $B_r(p,:)$ ZMM 向量，并广播 $A_r(i,p)$ 更新对应的 $C_r(i,:)$ 累加寄存器。这与当前 AVX2 按行组织的外积路径保持一致，不改变向量化方向。

外层工作集假设也与 AVX2 路径一致：$A_c$ 是线程私有打包工作集，$B_c$ 是在 `pc/jc` 层打包后由线程共享读取的打包工作集。这些都是建模前提，用于组织候选空间，不是关于 AVX-512 性能优劣的结论。

本节沿用 AVX2 文档中的三类语句口径：精确等式只描述代码语义和缓冲区尺寸；可行域不等式只用于过滤明显不合理的参数；启发式中心值只用于生成候选中心。三者都不能替代实测。

### 3.2 $m_r$ 与 $n_r$ 约束

令 $n_r = t \cdot N_{\text{vec}}$。当前正确性实现覆盖 $t=1$ 的 `nr=16` 系列，也覆盖 $t=2$ 的 `avx512_4x32`。其中 `nr=16` 使得每个 $B_r(p,:)$ 可以由单个 ZMM 寄存器承载，边界块也能用一个 `__mmask16` 表示 N 方向有效列；`nr=32` 则每行需要两个 ZMM 累加寄存器，并在 N 边界时维护两个掩码。为保持第一轮搜索规模可控，本节只讨论 $t \in \{1,2\}$，即 $n_r \in \{16,32\}$；$n_r=48$ 或更宽的 N 方向内核暂不进入默认候选集合。

吞吐下界先沿用 AVX2 文档中的一阶模型：

$$
m_r \cdot n_r \ge 64.
$$

对当前 `avx512_8x16`，有 $8 \cdot 16 = 128$，满足该下界。寄存器预算需要按 AVX-512 的 32 个 ZMM 寄存器重新写：累加寄存器数量为 $m_r \cdot \frac{n_r}{16}$，每次迭代中保留的 $B$ 向量数量近似为 $\frac{n_r}{16}$，并预留 $\delta \in [2,4]$ 给广播、掩码、地址计算和调度余量。因此核心可行性约束为

$$
m_r \cdot \frac{n_r}{16} + \frac{n_r}{16} + \delta \le 32.
$$

分情况代入后得到：

- 当 $n_r=16$，约束为 $m_r + 1 + \delta \le 32$，结合吞吐下界 $m_r \cdot 16 \ge 64$，保守取 $\delta=4$ 时有 $4 \le m_r \le 27$。
- 当 $n_r=32$，约束为 $2m_r + 2 + \delta \le 32$，结合吞吐下界 $m_r \cdot 32 \ge 64$，保守取 $\delta=4$ 时有 $2 \le m_r \le 13$。

这个原始可行域很宽，不能直接全部进入第一轮调参。需要再用实现复杂度、C 块回写压力、B 向量数量、边界掩码复杂度和搜索规模做工程裁剪。当前已经实现并验证正确性的形状是 `avx512_4x16`、`avx512_8x16`、`avx512_16x16`、`avx512_20x16`、`avx512_4x32`、`avx512_8x32` 和 `avx512_12x32`；它们都在寄存器预算内，但该分析只证明可行，不证明最优。

当前已实现正确性的组合先进入内核形状筛选，再根据实测热图结果重新分级。`avx512_4x32` 仍只保留为压力测试 / 兜底候选，不进入主调参排名。扩展筛选还临时比较了 `avx512_14x16`、`avx512_18x16`、`avx512_6x32` 和 `avx512_10x32`，但这些不改变本节对原始正确性列表的代码事实描述。

| 内核形状 | 类别 | 状态 | 保留原因 |
| --- | --- | --- | --- |
| `avx512_8x32` | 第 1 阶段后的主候选 | 已实现正确性路径 | 当前默认路径主候选；组合热图上对主流 FC 与宽输出 FC 最稳定 |
| `avx512_16x16` | 第 1 阶段后的小 N 观察候选 | 已实现正确性路径 | 在 `N=10` 工作负载上优于宽 `nr=32` 形状；当前记录但不推进为默认路径 |
| `avx512_8x16` | 次级候选 / 不再推进主线调参 | 已实现正确性路径 | `nr=16` 基准形状，但第 1 阶段后不再作为主线默认候选推进 |
| `avx512_10x32` | 次级候选 / 不再推进主线调参 | 扩展筛选形状 | 部分工作负载接近最优，但整体稳定性不如 `8x32` |
| `avx512_12x32` | 次级候选 / 不再推进主线调参 | 已实现正确性路径 | 部分工作负载接近或达到最优，但寄存器压力和存储压力更高，不作为默认候选 |
| `avx512_4x16` | 从主线调参中排除 | 已实现正确性路径 | 第 1 阶段上整体明显偏弱，不继续作为主线调参对象 |
| `avx512_20x16` | 从主线调参中排除 | 已实现正确性路径 | 未体现继续增大 `mr` 的收益，可能受分块不规则、存储压力和调度压力影响 |
| `avx512_4x32` | 压力测试 / 兜底 | 已实现正确性路径 | 严格 L1 组相联模型不支持中心值，只用于压力测试和兜底行为验证 |

因此，当前 AVX-512 $(m_r,n_r)$ 正确性 / 调参候选集合写为

$$
\{(4,16),(8,16),(16,16),(20,16),(4,32),(8,32),(12,32)\}.
$$

这些组合现在都已经完成正确性接入；第 1 阶段后的调参分类只决定后续分块尺寸搜索范围，不改变正确性状态。Stage 2 曾继续比较 `avx512_8x32` 和 `avx512_16x16`，但当前后续主线只推进 `avx512_8x32` 默认路径；压力测试 / 兜底集合只用于边界行为验证，不参与主调参排名。该分类不表示全局最优性或 AVX-512 相对 AVX2 的性能结论。

### 3.3 $k_c$ 缓存与 TLB 约束

$k_c$ 的中心值仍从 L1 组映射模型给出。与 AVX2 文档一致，$K_c$ 不是一个脱离内核形状的全局常数，而是要对每个 $(m_r,n_r)$ 分别生成。若 $C_{A_r}$ 表示 $A_r$ 在 L1 每个组中占据的缓存行数，$C_{B_r}$ 表示 $B_r$ 对应的行数，则轻量约束为：

$$
m_r k_c S_{\text{data}} = C_{A_r} N_{L1} C_{L1},
\qquad
C_{A_r} + C_{B_r} \le W_{L1} - 1,
$$

$$
C_{B_r} \approx \left\lceil \frac{n_r}{m_r} C_{A_r} \right\rceil.
$$

取 $W_{L1}=8$、$N_{L1}=64$、$C_{L1}=64\text{B}$、$S_{\text{data}}=4\text{B}$，可得到简化表达 $k_c^{\text{center}} \approx \frac{1024 \cdot C_{A_r}}{m_r}$。对 `avx512_8x16`，$\frac{n_r}{m_r}=2$，所以 $C_{A_r}^{\max}=\left\lfloor \frac{7}{1+2}\right\rfloor=2$。因此中心值为

$$
k_c^{\text{center}} \approx \frac{1024 \cdot 2}{8} = 256.
$$

默认 `8x16` 的第一轮 $K_c$ 候选应围绕该中心生成，核心集合为

$$
K_c \in \{192, 256, 320\}.
$$

可以额外保留 $384$ 作为扩展候选，但它不是由上述模型中心直接推出，只用于扩大后续搜索边界。若保留与 AVX2 文档一致的生成口径，可写为 $\mathcal{K}_{\mathrm{L1}} = \mathrm{Align}_{g_k}(\{ \alpha\, k_c^{\text{center}} : \alpha \in \mathcal{A}_k \})$，其中第一轮可取 $g_k=32$、$\mathcal{A}_k=\{0.75,1.0,1.25\}$，再按工程需要加入扩展候选。

TLB 层只做裁剪。若页大小为 $P=4096$，则页覆盖约束保留为单列公式：

$$
\operatorname{pages}(A_c) \approx
\left\lceil \frac{m_c k_c S_{\text{data}}}{P} \right\rceil,
\qquad
\operatorname{pages}(B_c) \approx
\left\lceil \frac{k_c n_c S_{\text{data}}}{P} \right\rceil.
$$

第一轮只要求 $A_c$ 页数约束在 50--60 页左右，并检查 $B_c$ 不形成异常宽的页覆盖。这个规则用于过滤候选，不作为新的中心值来源。

按同一口径代入当前 7 个 AVX-512 正确性形状，可得到第一轮 $K_c$ 候选表。这里的 “TLB 裁剪后” 仍只表示页覆盖过滤，不表示性能优劣。`avx512_4x32` 虽然列出小 $K_c$ 兜底候选，但不进入主候选集合，也不参与主调参排名。

| 内核形状 | $(m_r,n_r)$ | $C_{A_r}^{\max}$ | $k_c^{center}$ | $\mathcal{K}_{L1}$ | TLB 裁剪后 $\mathcal{K}$ | 说明 |
| --- | ---: | ---: | ---: | --- | --- | --- |
| `avx512_4x16` | $(4,16)$ | 1 | $256.0$ | $\{192,256,320\}$ | $\{192,256,320\}$ | 最小 `nr=16` 行高 |
| `avx512_8x16` | $(8,16)$ | 2 | $256.0$ | $\{192,256,320\}$ | $\{192,256,320\}$ | 默认基准形状 |
| `avx512_16x16` | $(16,16)$ | 3 | $192.0$ | $\{160,192,256\}$ | $\{160,192,256\}$ | 较高 `nr=16` 行高 |
| `avx512_20x16` | $(20,16)$ | 3 | $153.6$ | $\{128,160,192\}$ | $\{128,160,192\}$ | 激进 `nr=16` 行高 |
| `avx512_4x32` | $(4,32)$ | 0 | n/a | n/a | $\{64,96,128\}$ | 实现可行；严格 L1 组相联模型不可行，仅保留压力测试 / 兜底小 $K_c$ |
| `avx512_8x32` | $(8,32)$ | 1 | $128.0$ | $\{96,128,160\}$ | $\{96,128,160\}$ | 中等宽 N 方向候选 |
| `avx512_12x32` | $(12,32)$ | 1 | $85.3$ | $\{64,96,128\}$ | $\{64,96,128\}$ | 较激进宽 N 方向候选 |

`avx512_4x32` 是当前候选里的特殊情况。它的代码路径已经实现并通过正确性测试，因此这里的“不可行”只指严格 L1 组映射模型不可行，不是实现不可行。对 $(4,32)$，$n_r/m_r=8$，即使取最小的 $C_{A_r}=1$，近似也会得到 $C_{B_r}\approx 8$，从而 $C_{A_r}+C_{B_r}=9>W_{L1}-1$。因此严格沿用 AVX2 的 L1 组映射模型时没有正的 $C_{A_r}^{\max}$，不能从该模型推出中心值。文档保留 `avx512_4x32` 的小 $K_c$ 集合只是为了后续实测验证宽 N 方向内核的边界行为，不把它视为模型支持的主候选。

所以，与 AVX2 比较，AVX-512 的 $K_c$ 约束现在是完整的：筛选候选按同一 L1+TLB 流程生成；`4x32` 被明确标记为实现可行但严格模型不可行，并使用单独的小 $K_c$ 兜底集合。第 1 阶段后是否继续进入主调参由实测热图决定，而不是只由模型可行域决定。

### 3.4 $m_c / n_c$ 候选生成（单线程基线）

给定内核形状和 $k_c$ 后，$m_c$ 控制线程私有 $A_c$ 体积，$n_c$ 控制共享 $B_c$ 体积。因此不是先固定一个全局 $M_c/N_c$ 再给它随意配 $K_c$，而是按层次生成：先选 `KernelShape`，再按该形状的 $K_c$ 候选生成对应的 $M_c/N_c$ 候选。第一轮单线程基线可以用缓存尺度上界做粗筛：

$$
m_c^{\max} \approx \frac{65536}{k_c}, \qquad
n_c^{\max} \approx \frac{262144}{k_c}.
$$

这里的常数只表示候选生成时的缓存尺度体积预算，而不是硬件容量的精确分配策略。等价地，它来自 $m_c k_c S_{\text{data}} \lesssim \rho_A S_{\text{private}}$ 与 $k_c n_c S_{\text{data}} \lesssim \rho_B S_{\text{shared}}$，其中 $\rho_A,\rho_B$ 是保守余量系数，不是硬件常数。实际候选仍应再通过 TLB 页覆盖做裁剪。对 $P=4096$ 和 $S_{\text{data}}=4$：

$$
\operatorname{pages}(A_c) \approx \frac{m_c k_c}{1024},
\qquad
\operatorname{pages}(B_c) \approx \frac{k_c n_c}{1024}.
$$

第一轮可沿用 AVX2 文档的保守口径：$A_c$ 的有效页预算约为 54，$B_c$ 使用一个远小于 L2 DTLB 容量的保守预算，例如 192，用于裁掉过宽 $B_c$ 面板。这些预算只承担裁剪作用。

第一轮 AVX-512 分块尺寸候选集合保持较小，但不能使用所有内核共享的统一 $M_c$ 集合。在第一轮调参中，要求 $M_c \ge m_r$，并优先选择 $M_c$ 为 $m_r$ 的整数倍，以减少 M 边界块并保证宏内核分块对齐。因此 $M_c$ 必须按内核形状生成。第 1 阶段内核形状筛选完成后，这张表不再表示所有形状都会进入后续主调参；它只记录第一轮比较时使用过的候选生成口径。

| 内核形状 | 类别 | $M_c$ 候选 |
| --- | --- | --- |
| `avx512_4x16` | 从主线调参中排除 | $\{16,32,48,64\}$ |
| `avx512_8x16` | 次级候选 / 不再推进主线调参 | $\{16,32,48,64\}$ |
| `avx512_16x16` | 第 1 阶段后的小 N 观察候选 | $\{32,48,64\}$ |
| `avx512_20x16` | 从主线调参中排除 | $\{40,60,80\}$ |
| `avx512_8x32` | 第 1 阶段后的主候选 | $\{16,32,48,64\}$ |
| `avx512_12x32` | 次级候选 / 不再推进主线调参 | $\{24,48,72\}$ |
| `avx512_4x32` | 压力测试 / 兜底 | $\{16,32,48,64\}$ |

若写成候选生成关系，则为 $\mathcal{M}_{\text{pruned}} \subseteq \mathcal{M}_{\text{cache}}$、$\mathcal{N}_{\text{pruned}} \subseteq \mathcal{N}_{\text{cache}}$。其中缓存层给出基础尺度，TLB 层剔除页覆盖过大的点。$N_c$ 不允许使用全局候选集合；所有 $N_c$ 候选必须按 $K_c$ 表进行裁剪，不允许形成 `KernelShape × Kc × Mc × global Nc` 的全局笛卡尔积。

| $K_c$ | 缓存 / TLB 裁剪后的 $N_c$ 候选 |
| ---: | --- |
| 64 | $\{256,384,512,640,768,1024\}$ |
| 96 | $\{256,384,512,640,768,1024\}$ |
| 128 | $\{256,384,512,640,768,1024\}$ |
| 160 | $\{256,384,512,640,768,1024\}$ |
| 192 | $\{256,384,512,640,768,1024\}$ |
| 224 | $\{256,384,512,640,768\}$ |
| 256 | $\{256,384,512,640,768\}$ |
| 320 | $\{256,384,512\}$ |

把 3.3 的 $K_c$ 表和本节的 $M_c/N_c$ 表合并后，第一轮筛选候选按如下规则展开。下表只记录候选生成口径；第 1 阶段后的最终筛选分类由 3.5 汇总。

| 内核形状 | 类别 | $K_c$ 候选 | 使用的 $M_c/N_c$ 行 |
| --- | --- | --- | --- |
| `avx512_8x32` | 第 2 阶段默认路径候选 | $\{96,128,160\}$ | 形状专属 $M_c$ 行 + 匹配的 $K_c$ 行 |
| `avx512_16x16` | 第 2 阶段小 N 观察候选 | $\{160,192,256\}$ | 形状专属 $M_c$ 行 + 匹配的 $K_c$ 行 |
| `avx512_8x16` | 筛选参考 | $\{192,256,320\}$ | 形状专属 $M_c$ 行 + 匹配的 $K_c$ 行 |
| `avx512_12x32` | 筛选参考 | $\{64,96,128\}$ | 形状专属 $M_c$ 行 + 匹配的 $K_c$ 行 |
| `avx512_4x16` | 筛选参考 | $\{192,256,320\}$ | 形状专属 $M_c$ 行 + 匹配的 $K_c$ 行 |
| `avx512_20x16` | 筛选参考 | $\{128,160,192\}$ | 形状专属 $M_c$ 行 + 匹配的 $K_c$ 行 |
| `avx512_4x32` | 压力测试 / 兜底 | $\{64,96,128\}$ | 小 $K_c$ 兜底行 |

这些值是阶段性候选集合，用于组织单线程调参。实际脚本必须按 `KernelShape -> Kc -> shape-specific Mc -> Kc-pruned Nc` 这一层次展开；第 1 阶段筛选后再决定哪些形状进入后续精筛。

### 3.5 第 1 阶段：内核形状筛选实验

第 1 阶段的目的只是筛选内核形状，并收缩后续分块尺寸调参的搜索范围。该阶段比较当前已实现的 AVX-512 正确性候选，以及扩展筛选中加入的少量邻近形状；它只决定哪些形状进入第 2 阶段，不决定最终分块尺寸。

实验使用当前代表工作负载集合，覆盖主流 FC、小 N 分类头、宽输出 FC，以及 skinny-K 卷积反传类 GEMM：

- `conv_dx_extremely_skinny_k_nn` / `cnn_conv2_dX_b32` / `3200x16x150`
- `fc_forward_mainstream_nn` / `mlp_fc1_b32` / `32x784x128`
- `fc_head_small_n_nn` / `mlp_fc2_b32` / `32x128x10`
- `fc_wide_output_nn` / `mlp_fc1_hidden256_b32` / `32x784x256`

筛选图使用相对热图：每个单元格表示某个内核形状在同一工作负载下，相对于当前自定义候选最佳点的比例。第 1 张图用于观察主候选分层，第 2 张组合热图用于比较优胜形状附近的 $K_c/M_c/N_c$ 组合。相对热图只用于排序和收缩搜索范围，绝对 GFLOPS 由第 2 阶段结果表报告。

![avx512_relative_to_best_primary_heatmap](../../output/ExperienceGEMM/GotoBLASBlockedAVX512/stage2_blocked_candidates/summary/plots/avx512_relative_to_best_primary_heatmap.png)

![avx512_stage2_combined_relative_heatmap](../../output/ExperienceGEMM/GotoBLASBlockedAVX512/stage2_combined/summary/plots/avx512_stage2_combined_relative_heatmap.png)

核心结论是：`avx512_8x32` 在非小 N 工作负载上整体最稳定，保留为默认路径候选；`avx512_16x16` 在 `N=10` 工作负载上更合适，作为已观察到的小 N 优胜形状记录。`avx512_4x16` 与 `avx512_20x16` 不再进入主线调参；`avx512_10x32` 与 `avx512_12x32` 降级为次级参考。

| 结果类别 | Kernel shape | 处理 |
| --- | --- | --- |
| default-path candidate | `avx512_8x32` | 进入第 2 阶段 |
| small-N observed winner | `avx512_16x16` | 进入第 2 阶段记录表现；当前不作为后续主线验证对象 |
| secondary | `avx512_8x16` / `avx512_10x32` / `avx512_12x32` | 不进入主线调参 |
| discarded | `avx512_4x16` / `avx512_20x16` | 淘汰 |
| stress / fallback only | `avx512_4x32` | 不参与主排名 |

### 3.6 第 2 阶段：单线程分块尺寸调参实验

第 2 阶段围绕第 1 阶段保留的两个形状做单线程分块尺寸调参：`avx512_8x32` 作为默认路径候选，`avx512_16x16` 用于记录小 N 表现。候选范围只在各自模型支持的 $K_c/M_c/N_c$ 附近展开，不重新打开全局内核形状搜索。

这一步对应“基于优胜候选的继续精筛”：保持相同代表工作负载、单线程执行协议和汇总口径，只对两个保留形状的 $K_c/M_c/N_c$ 做局部加密采样。参数级热图按 `KernelShape + workload + Kc + Mc + Nc` 分组，分别查看 `Kc x Mc`（单元格取最佳 `Nc`）和 `Kc x Nc`（单元格取最佳 `Mc`）。

| KernelShape | Kc | Mc candidates | Nc candidates | Combination count |
| --- | ---: | --- | --- | ---: |
| `avx512_8x32` | 96 | `{32,48,64}` | `{384,512,640,768,1024}` | 15 |
| `avx512_8x32` | 128 | `{32,48,64}` | `{384,512,640,768,1024}` | 15 |
| `avx512_8x32` | 160 | `{32,48,64}` | `{384,512,640,768,1024}` | 15 |
| `avx512_16x16` | 160 | `{32,48,64}` | `{256,384,512,640,768,1024}` | 18 |
| `avx512_16x16` | 192 | `{32,48,64}` | `{256,384,512,640,768,1024}` | 18 |
| `avx512_16x16` | 256 | `{32,48,64}` | `{256,384,512,640,768}` | 15 |

因此，第 2 阶段单线程精筛合计 96 个分块尺寸组合。这个集合的作用是在第 1 阶段优胜区域附近补足中间点，并检查 `Kc/Mc/Nc` 平台区是否稳定。

当前代表工作负载的优胜者如下：

| 工作负载 | 最佳内核 | Kc | Mc | Nc | GFLOPS 中位数 |
| --- | --- | ---: | ---: | ---: | ---: |
| `conv_dx_extremely_skinny_k_nn` / `cnn_conv2_dX_b32` / `3200x16x150` | `avx512_8x32` | 128 | 32 | 640 | 29.59 |
| `fc_forward_mainstream_nn` / `mlp_fc1_b32` / `32x784x128` | `avx512_8x32` | 160 | 32 | 384 | 47.74 |
| `fc_head_small_n_nn` / `mlp_fc2_b32` / `32x128x10` | `avx512_16x16` | 160 | 64 | 512 | 10.10 |
| `fc_wide_output_nn` / `mlp_fc1_hidden256_b32` / `32x784x256` | `avx512_8x32` | 160 | 32 | 512 | 51.55 |

阶段性推荐配置如下：

| 用途 | KernelShape | Kc | Mc | Nc | 理由 |
| --- | --- | ---: | ---: | ---: | --- |
| AVX-512 单线程默认候选 | `avx512_8x32` | 160 | 32 | 512 | 在非小 N 工作负载上最佳或接近最佳；`Nc=384/512` 附近呈稳定平台 |
| 已观察到的小 N 优胜点 | `avx512_16x16` | 160 | 64 | 512 | 在 `N=10` 上最佳；当前记录结果但不进入后续多线程验证 |

![alt text](../../output/ExperienceGEMM/GotoBLASBlockedAVX512/stage2_blocked_tuning/summary/plots/stage2_relative_to_best_heatmap.png)

`avx512_8x32, Kc=160, Mc=32, Nc=512` 因此作为当前阶段唯一推进的单线程默认路径候选。`avx512_16x16, Kc=160, Mc=64, Nc=512` 只作为 small-N observed winner 记录。skinny-K 的单点最佳使用 `Kc=128`，但目前证据不足以引入单独特化规则；因此后续阶段仍以 $K_c=160$ 作为默认路径代表值。

### 3.7 第 3 阶段：多线程 Mc/Nc 经验调参

第 3 阶段固定 `MATMUL_IMPL=omp_gotoblas_avx512`、`KernelShape=avx512_8x32` 与 `Kc=160`，只扫描 `Mc/Nc`。目的不是重新打开内核形状搜索，也不是做 AVX2 comparison，而是检查第 2 阶段单线程配置 `Mc=32,Nc=512` 是否仍适合作为多线程 fixed scaling config。

实验使用 `Threads={1,2,4,8}`、`Mc={8,16,24,32,48,64,72}`、`Nc={256,320,384,448,512,640,768}`，workload set 仍为四个 representative NN GEMM。主指标是跨 representative workloads 的 overall geomean GFLOPS；family-level heatmap 用于检查是否存在单一 workload family 的异常退化，overall geomean 用于选择 fixed scaling config。为保证多线程结果可重复，运行时固定 `OMP_DYNAMIC=false`、`OMP_PROC_BIND=true`、`OMP_PLACES=cores`、`OPENBLAS_NUM_THREADS=1`、`MKL_NUM_THREADS=1`。

严格优胜点如下。它们说明最佳点会随线程数移动，但不应直接把每个 strict winner 写成 dispatch 规则。

| T | strict winner Mc | strict winner Nc | fixed Kc | Geomean GFLOPS |
| ---: | ---: | ---: | ---: | ---: |
| 1 | 16 | 384 | 160 | 29.084506 |
| 2 | 16 | 256 | 160 | 48.229486 |
| 4 | 8 | 448 | 160 | 71.221667 |
| 8 | 8 | 384 | 160 | 83.146494 |

保守推荐如下。低线程下可以记录 `Mc=16` 的 empirical table；若需要一个固定 scaling 配置，则优先采用多线程下稳定的平台区代表值 `Mc=8,Nc=448,Kc=160`。

| 用途 | T | 推荐 Mc | 推荐 Nc | 固定 Kc |
| --- | ---: | ---: | ---: | ---: |
| Thread-aware empirical table | 1 | 16 | 384 | 160 |
| Thread-aware empirical table | 2 | 16 | 448 | 160 |
| Thread-aware empirical table | 4 | 8 | 448 | 160 |
| Thread-aware empirical table | 8 | 8 | 448 | 160 |
| Fixed scaling config for multi-thread scaling | 1,2,4,8 | 8 | 448 | 160 |

该固定配置是为了 multi-thread scaling 的一致性选择，不是每个线程数的 strict winner；`T=1/2` 的 strict winner 已在 empirical table 中单独记录。整体 heatmap 的主要结论是 `Mc` 是主导变量。`T=4/8` 下 `Mc=8` 一整行明显高于 `Mc=16/32`；其中 `T=8` 下 `Mc=8` 约为 81.5--83.1 GFLOPS，而 `Mc=32` 约为 47 GFLOPS。因此，`Mc=32,Nc=512` 不能继续作为 AVX-512 多线程 fixed scaling config。

`Nc` 更接近平台参数。对 `Mc=8`，`T=4` 下 `Nc=384/448/512` 基本处于同一平台，`T=8` 下 `Nc=256/384/448` 近似同平台，`Nc=512` 稍低但仍接近。因此选择 `Nc=448` 是保守平台代表值，而不是证明 `Nc=448` 是全局最优。

![overall_T4_mcnc_heatmap](../../output/ExperienceGEMM/GotoBLASBlockedAVX512/thread_aware_mcnc/summary/plots/overall_T4_mcnc_heatmap.png)

![overall_T8_mcnc_heatmap](../../output/ExperienceGEMM/GotoBLASBlockedAVX512/thread_aware_mcnc/summary/plots/overall_T8_mcnc_heatmap.png)

这里的 `Mc=8` 是由当前 `ic / M` 多线程并行下的任务粒度驱动出来的经验收缩，不否定第 2 阶段单线程 cache/TLB 口径。`Kc` 本轮仍固定为 160；除非后续在 `Mc=8,Nc=448` 下仍观察到稳定 skinny-K regression，否则不引入 `Kc=128` 特化。

### 3.8 小结

第 1 阶段筛选后，`avx512_8x32` 保留为默认路径候选；第 2 阶段单线程分块尺寸调参给出 `avx512_8x32, Kc=160, Mc=32, Nc=512`，它仍只表示单线程默认路径候选。

第 3 阶段多线程 Mc/Nc sweep 表明，`Mc=32,Nc=512` 不适合作为多线程 fixed scaling config。当前 AVX-512 多线程 fixed scaling config 推荐为 `avx512_8x32, Kc=160, Mc=8, Nc=448`。`avx512_16x16` 仍仅作为 small-N observed winner 记录；若后续 small-N regression 不可接受，再重新评估 fallback。下一步应先对固定配置做 final validation，再进入固定 AVX2 baseline comparison。

## 4. 基准测试与调参计划

规划脚本目录：

```text
scripts/ExperienceGEMM/GotoBLASBlockedAVX512
```

规划输出目录：

```text
output/ExperienceGEMM/GotoBLASBlockedAVX512
```

当前脚本：

- `run_avx512_stage2_blocked_tuning.py`
- `summarize_avx512_stage2_blocked_tuning.py`
- `plot_avx512_stage2_heatmaps.py`
- `run_avx512_thread_aware_mcnc_tuning.py`
- `summarize_avx512_thread_aware_mcnc_tuning.py`
- `plot_avx512_thread_aware_mcnc_heatmaps.py`

计划中的后续脚本与实验：

- 下一步：对 `avx512_8x32, Kc=160, Mc=8, Nc=448` 做固定配置 final validation。
- 后续：`run_avx2_vs_avx512_comparison.py`

Final validation 应至少输出 GFLOPS、`speedup_vs_T1`、`parallel_efficiency`、per-workload results 和 regression flags。第 2 阶段参数级热图是单线程分块尺寸调参的主证据；第 3 阶段 thread-aware Mc/Nc heatmap 是多线程 fixed scaling config 的主证据。

## 5. AVX2 与 AVX-512 对比协议

公平比较必须使用同一工作负载集合、同一线程数、同一测量协议、同一预热策略和同一汇总统计方式。AVX2 基线应显式固定，例如指定 `MATMUL_IMPL=omp_gotoblas_avx2`、`MATMUL_GOTO_KERNEL=<chosen_avx2_baseline>`，以及作为基线使用的 AVX2 分块参数。

不能预设 AVX-512 一定更快。更宽的向量可能改变 CPU 频率行为，小 N 边界、掩码开销、打包开销和缓存覆盖都可能抵消甚至反转理论通道宽度优势。结果应同时报告绝对时间和相对固定 AVX2 基线的加速比。

比较时应区分完整块大 GEMM 场景与类 NN 形状，例如小 `N`、skinny `K` 或大量尾块的工作负载。把这些混成单一总览数字会掩盖最容易暴露 AVX-512 开销的场景。

## 6. Fixed Strong-scaling Comparison

本节固定来自 `run_fixed_strong_scaling_comparison.py` 的阶段性结论。实验使用两组 workload：

- **training-trace workload set** — 7 个形状，从真实 CNN+MLP 训练 trace 中提取（见 `Docs/report/ActualTrainingGemmFamilies.md`）。
- **square-reference** — 2 个方阵形状（256×256×256 与 512×512×512），作为传统 BLAS 参考，不代表训练问题族。

两组 workload 混合在同一次实验运行中。下文对每组分别描述结论，不允许跨组外推。

### 6.1 实验配置

| 实现 | `MATMUL_IMPL` | 微内核 | Kc | Mc | Nc | 线程控制 |
| --- | --- | --- | ---: | ---: | ---: | --- |
| AVX2 GotoBLAS | `omp_gotoblas_avx2` | `avx2_8x8` | 384 | 8 | 448 | `OMP_NUM_THREADS` |
| AVX-512 GotoBLAS | `omp_gotoblas_avx512` | `avx512_8x32` | 160 | 8 | 448 | `OMP_NUM_THREADS` |
| OpenBLAS | `blas` (cblas_sgemm) | n/a | n/a | n/a | n/a | `OPENBLAS_NUM_THREADS` |

两个自定义路径均为固定 config custom GotoBLAS path。OpenBLAS 使用 `OPENBLAS_NUM_THREADS` 控制线程数；实验中 GotoBLAS 分块变量（`MATMUL_GOTO_KERNEL`、`MATMUL_MC`、`MATMUL_NC`、`MATMUL_KC`）在 OpenBLAS 运行时均已从环境变量中清除，OpenBLAS 能够正常扩展。因此，OpenBLAS 不再是单线程参考线，而是有效的多线程 library baseline。

线程配置：`Threads={1,2,4,8}`，`OMP_PROC_BIND=true`，`OMP_PLACES=cores`，`OMP_DYNAMIC=false`。每个 workload × 实现 × 线程数组合取 3 次 sample 的中位 GFLOPS；整体汇总使用跨所有 workload 的几何均值。

原始数据：`output/ExperienceGEMM/GotoBLASBlockedAVX512/fixed_strong_scaling_comparison/raw_results.csv`（324 行，全部 Status=ok）。

### 6.2 Training-trace workload set

Training-trace workload 从真实 MNIST 训练 trace 中提取，覆盖以下 GEMM 问题族：
`conv_fwd_medium_k_nn`、`conv_dx_extremely_skinny_k_nn`、`conv_dw_transposed_very_skinny_m`、`conv_fwd_very_skinny_k_small_n_nn`、`fc_forward_mainstream_nn`。
完整问题族描述见 `Docs/report/ActualTrainingGemmFamilies.md`。

**重要 caveat：** 自定义 AVX2/AVX-512 实现只处理非转置 GEMM（`!transA && !transB`）。训练中的转置调用（dW 路径：`conv_dw_transposed_very_skinny_m`）在生产路径中回退到 BLAS；benchmark 只测量相同 M/K/N 维度下的非转置 GEMM 吞吐。因此 benchmark 结果不等同于转置路径的实际快速路径结论。

下图展示所有 9 个 workload（7 个 training-trace + 2 个 square-reference）的整体几何均值 GFLOPS 随线程数的变化。图注说明：该曲线包含 square-reference workload，不能单独视为 training-trace 结论。

![overall_geomean_gflops_by_threads](../../output/ExperienceGEMM/GotoBLASBlockedAVX512/fixed_strong_scaling_comparison/summary/plots/overall_geomean_gflops_by_threads.png)

*图：整体几何均值 GFLOPS（全部 9 个 workload：7 training-trace + 2 square-reference）。*

下图展示自定义路径相对 OpenBLAS 的比例（%），同样包含全部 9 个 workload。

![relative_to_openblas_by_threads](../../output/ExperienceGEMM/GotoBLASBlockedAVX512/fixed_strong_scaling_comparison/summary/plots/relative_to_openblas_by_threads.png)

*图：自定义路径相对 OpenBLAS 的 GFLOPS 比例（%）。100% 表示与 OpenBLAS 持平。*

**整体 geomean 结论（training-trace 主导）：**

在修正 OpenBLAS 线程控制后，OpenBLAS 是最强的 library baseline。整体几何均值结果如下：

| Threads | AVX2 GFLOPS | AVX-512 GFLOPS | OpenBLAS GFLOPS | AVX-512 / OpenBLAS |
| ---: | ---: | ---: | ---: | ---: |
| 1 | 26.1 | 27.6 | 43.4 | 63.7% |
| 2 | 41.7 | 45.0 | 67.5 | 66.6% |
| 4 | 64.4 | 67.4 | 101.1 | 66.7% |
| 8 | 84.4 | 89.4 | 118.2 | 75.7% |

AVX-512 fixed config 相比 AVX2 fixed baseline 有稳定但有限的整体提升（geomean 约 +5%）。但两者均低于 OpenBLAS，AVX-512 约为 OpenBLAS 的 64%–76%。该结果支持 AVX-512 路径相对 AVX2 的阶段性收益，同时也说明自定义 GotoBLAS 路径距离成熟 BLAS 库仍有差距。

**Per-workload 例外：**

`cnn_conv2_dx_b32 (3200×16×150)`（Conv2 dX，skinny-K 形状）在高线程数下自定义路径领先：

| Threads | AVX2 | AVX-512 | OpenBLAS |
| ---: | ---: | ---: | ---: |
| 1 | 30.9 | 29.8 | 45.8 |
| 4 | 93.6 | 91.2 | 110.3 |
| 8 | **132.0** | 126.7 | 103.0 |

该形状在 T=8 下 AVX2 (132 GFLOPS) > AVX-512 (127) > OpenBLAS (103)。这是 skinny-K 大 M 形状在多核展开时 OpenBLAS 线程池扩展受限的局部现象，不能外推到其他 workload family。

下图展示该 workload 的 per-workload 曲线：

![workload_conv2_dx](../../output/ExperienceGEMM/GotoBLASBlockedAVX512/fixed_strong_scaling_comparison/summary/plots/workload_conv_dx_extremely_skinny_k_nn_cnn_conv2_dx_b32_3200x16x150.png)

*图：cnn_conv2_dx_b32 (3200×16×150) — skinny-K 形状，T=8 下自定义路径领先。*

`mlp_fc1_b32 (32×784×128)` 与 `cnn_fc1_b32 (32×400×120)` 等 FC 形状：OpenBLAS 在所有线程数下均领先，AVX-512 领先 AVX2 但差距不大。

### 6.3 Square-reference GEMM

Square-reference workload（256×256×256 与 512×512×512）用于传统 BLAS 参考，不代表训练问题族，结论不能外推到 training-trace workload。

下图展示 square_matrix 系列的几何均值 GFLOPS：

![family_geomean_square](../../output/ExperienceGEMM/GotoBLASBlockedAVX512/fixed_strong_scaling_comparison/summary/plots/family_geomean_gflops_by_threads_square_matrix.png)

*图：square_matrix 系列（256×256×256 + 512×512×512）几何均值 GFLOPS。*

三方实现都能有效扩展。但 "AVX-512 在 T=8 最高" 仅对 square_256 成立；square_512 在 T=8 下 OpenBLAS (436 GFLOPS) 高于 AVX-512 (394)。关键数据如下：

| WorkloadId | Threads | AVX2 | AVX-512 | OpenBLAS | 胜者 |
| --- | ---: | ---: | ---: | ---: | --- |
| square_256 | 4 | 183 | 203 | 208 | OpenBLAS |
| square_256 | 8 | 298 | **334** | 261 | AVX-512 |
| square_512 | 4 | 200 | 223 | **250** | OpenBLAS |
| square_512 | 8 | 354 | 394 | **436** | OpenBLAS |

Square-reference 结论：AVX-512 fixed config 在规则方阵场景下有竞争力，在 square_256 T=8 时最高；但 OpenBLAS 在 T=4 对所有方阵规模仍具优势，在 square_512 T=8 仍是最强。不能写"AVX-512 在所有线程数和所有规模上无条件优于 OpenBLAS"。该结果不能外推到 training-trace workload。

### 6.4 综合解读

| 场景 | 主要观察 | 阶段性解读 |
| --- | --- | --- |
| training-trace 整体 geomean | OpenBLAS overall geomean 最高；AVX-512 约 +5% vs AVX2 | AVX-512 有 AVX2 内部阶段性收益；自定义路径仍低于成熟 BLAS |
| cnn_conv2_dx_b32 skinny-K (T=8) | AVX2 > AVX-512 > OpenBLAS | 局部现象，不能外推；OpenBLAS 在该形状高线程下反而有限 |
| square_256 (T=8) | AVX-512 最高 | 规则方阵高线程场景下有竞争力；不能外推到 training-trace |
| square_512 (T≥4) | OpenBLAS 最高 | AVX-512 在较大方阵多线程时与 OpenBLAS 仍有差距 |
| Conv dW / 转置路径 | benchmark 只测非转置代理形状 | 转置生产路径回退 BLAS；benchmark 结论不等同于完整训练 FLOPs 的自定义覆盖 |

OpenBLAS 是修正线程控制后的有效多线程 library baseline，不再是单线程参考线。两个自定义 GotoBLAS 路径都能有效扩展，但 geomean 结果表明在典型训练 workload 上仍低于 OpenBLAS。
