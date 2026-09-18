# omp BlockSize Packsize 的turing实验

本文档描述的是 blocked 系列参数筛选的计划实验协议（planned protocol），
用于指导后续在 `scripts/ExperienceGEMM/Blocked/` 下实现新的 benchmark 脚本。
仓库中现有的旧脚本仅作为历史实验参考，不视为本协议的完整实现。

## 参数定义和理论前提

blocking 和 packing 是优化 GEMM 性能的两大重要技术手段。

从时间局部性（temporal locality）的角度看，blocking 的目的，是让一批已经进入 cache 的 A、B 与 C 子块在被逐出之前完成尽可能多的复用。否则，数据尚未充分参与计算，就可能被后续访问的新数据替换。

在矩阵乘法

$$
C \leftarrow C + AB,
\qquad
A\in\mathbb{R}^{M\times K},\ B\in\mathbb{R}^{K\times N},\ C\in\mathbb{R}^{M\times N}
$$

中，panel（面板）指的是分块循环中切出的、会被后续 kernel（内核）重复访问的矩形子矩阵。对于固定的 $p$ 和 $j$，可从 $B$ 中取出一个大小为 $K_c\times N_c$ 的 panel：

$$
B_c = B[p:p+K_c,\ j:j+N_c].
$$

packing（打包）指的是：在局部计算前，将这样的 panel 复制到一个临时的连续缓冲区中，并按后续 kernel 更适合访问的顺序重新排列。它并不是显式地把数据放入某一级 cache，而是通过改变内存布局，使后续访存更连续、更规则。

若将 $B_c$ 打包为 row-major 的连续缓冲区 $\widetilde{B}_c$，则可写成

$$
\widetilde{B}_c[k,n] = B[p+k,\ j+n],
\qquad
0\le k<K_c,\quad 0\le n<N_c,
$$

其线性下标为

$$
\operatorname{idx}_{\widetilde{B}}(k,n)=kN_c+n.
$$

这样，原来嵌在大矩阵中、可能带有较大 leading dimension 的子矩阵，就被转换成一个紧凑的连续数组，便于后续计算反复访问同一 packed panel。

结合当前代码库，packing 需要区分两种实现：

1. `omp_blocked_packb`

只打包 $B$ 的 panel。实现上，外层仍按单一 `BlockSize` 做方形分块；每个线程分配一个 `packed_B(BS \times BS)` 缓冲区，并在每个 $(k,j)$ 子块上执行

$$
\widetilde{B}_c[k,n] = B[p+k,\ j+n].
$$

随后计算阶段直接从原始矩阵读取 $A$，只对 $B$ 使用 packed buffer。因此，这一路径的核心参数仍主要是统一的 `BlockSize`。

2. `omp_blocked_packab`

同时打包 $A$ 和 $B$。实现上不再只依赖单一方形块，而是分别使用 `PackM`、`PackN` 和 `PackK`（代码中也可由 `MATMUL_MC`、`MATMUL_NC`、`MATMUL_KC` 表示）控制 panel 形状。对应的打包形式为

$$
\widetilde{A}_c[m,k] = A[i+m,\ p+k],
\qquad
\widetilde{B}_c[k,n] = B[p+k,\ j+n].
$$

随后 kernel 在 packed buffer 上完成局部乘加。相比 `packb`，这一路径的参数空间更大，但也更接近 panel-based 的实现方式。

因此，本文中的核心参数需要分开理解：

- BlockSize: 对 `omp`、`omp_blocked` 和 `omp_blocked_packb`，它主要决定 loop tiling 的 tile size 和局部工作集大小。
- PackM / PackN / PackK: 对 `omp_blocked_packab`，它们决定 $A$ panel 与 $B$ panel 的形状，以及 packed buffer 的 footprint 和访问规律。

## 理论约束

当前实验的矩阵元素类型是 $\texttt{float32}$，即每个元素占 4 byte。实验中的候选参数不做完全自由搜索，而是先依据局部性、cache line、cache 容量和 TLB 约束生成第一轮筛选集合。

### 1. BlockSize 的一阶约束

对于最简单的 square blocked GEMM，若一次局部计算同时活跃一个 $A$ tile、一个 $B$ tile 和一个 $C$ tile，则可用如下近似关系为 BlockSize 的第一轮候选范围提供依据：

$$ 3b^2 s \le \alpha C_{\text{cache}} $$

其中：

- $b$：方形 tile 的边长；
- $s$：元素字节数；对当前 $\texttt{float32}$ 路径，$s=4$；
- $C_{\text{cache}}$：目标 cache 容量；
- $\alpha$：安全系数，满足 $\alpha < 1$，用于给 cache conflict、栈变量、预取污染和 TLB 等因素预留空间。

这个公式只作为 naive blocked GEMM 的一阶筛选依据，不直接给出最优值。实际最优 BlockSize 仍会受到访问顺序、cache associativity、多线程共享 cache 压力以及调度粒度的影响，因此必须通过实验验证。

若以当前平台的单核 cache 为目标，则由 `lscpu` 可知每个物理核心对应 32 KiB L1D cache 和 1024 KiB L2 cache。对当前 `float32` 路径有 $s=4$，因此约束可写成 $12b^2 \le \alpha C_{\text{cache}}$。据此反推，L1 对应 $b^2 \le \alpha \cdot 32768 / 12 \approx \alpha \cdot 2730.7$，在 $\alpha = 1$ 的极限下得到 $b \le 52.3$；L2 对应 $b^2 \le \alpha \cdot 1048576 / 12 \approx \alpha \cdot 87381.3$，在 $\alpha = 1$ 的极限下得到 $b \le 295.6$。这说明：如果目标是最简单的三 tile L1-resident 模型，则 `BlockSize` 的自然候选应落在 52 左右以下；若转而依赖更高层 cache，则候选范围可以进一步扩展到 200 以上。这里的上界只是理想化模型的反推结果，不代表最优值一定出现在边界附近；实际可用范围还会被 cache associativity、TLB、线程共享 cache 压力和访问顺序进一步收紧。

基于这一反推，本文将 `BlockSize` 的第一轮候选分成两层：

- 偏 L1 的候选：16, 32, 48
- 偏 L2 的候选：64, 128, 256

其中，前一组用于覆盖较小工作集在 L1 内复用的可能性；后一组则用于观察在超出 L1 后，是否仍能依赖 L2 容量获得稳定收益。

### 2. PackSize 的约束

BlockSize 与 PackSize 的作用不同。BlockSize 主要决定 loop tiling 后的活跃工作集大小；PackM / PackN / PackK 则主要决定 packed panel 的形状，以及内层计算时能否保持 contiguous、unit-stride 的规则访问。注意，我们在这里只研究 L1-oriented packing 的参数。

对 `omp_blocked_packb` 而言，packing 的目标是把 $B$ 的 panel 整理为连续内存布局；此时参数仍主要由统一的 `BlockSize` 控制。若只看每线程额外分配的 packed buffer，其大小近似为

$$
S_{\text{packB}} \approx sb^2.
$$

但若讨论局部计算阶段的活跃工作集，则仍需同时考虑 $A$ 和 $C$ 的访问，因此其工作集仍更接近 $s(b_A^2 + b_B^2 + b_C^2)$，只是其中 $B$ 的访问被改写为更连续的 packed 形式。换言之，`packb` 的收益主要来自 $B$ 侧访存模式的改善，而不是把工作集简化为只剩一个 packed buffer。

由于 `omp_blocked_packb` 仍由统一的 `BlockSize` 控制，且此处只考虑偏 L1 的候选，因此其第一轮搜索限定为 `BlockSize \in \{16,32,48\}`。这三组取值都落在前文由 L1 三 tile 模型反推出的量级之内；因此，对 `packb` 而言，不再额外引入独立的 `PackM / PackN / PackK` 搜索空间。

对 `omp_blocked_packab` 而言，packing 的目标则是同时控制 $A$ panel 与 $B$ panel 的 footprint。此时更合理的近似不再是 square tile 的 $3b^2s$ 模型，而是

$$
S_{\text{packAB}} = s(M_cK_c + K_cN_c + M_cN_c).
$$

其中 $M_cK_c$ 对应 packed $A$，$K_cN_c$ 对应 packed $B$，$M_cN_c$ 对应局部更新所需的 $C$ tile。作为第一轮参数筛选的 footprint 近似，可进一步要求 $s(M_cK_c + K_cN_c + M_cN_c) \le \alpha C_{\text{cache}}$。

因此，`PackM / PackN / PackK` 的选择会直接影响 packed buffer 的遍历规整性、边界处理开销、跨行访问模式以及局部工作集大小。

需要注意的是，`PackM / PackN / PackK` 不再完全服从上面的 square tile 模型，因为此时活跃数据更接近 packed panel，而不是原始的 $b \times b$ 子块。因此，packing 参数需要结合 panel footprint、目标 cache 容量与 TLB 覆盖范围单独设计。特别地，`PackK` 控制 reduction dimension 的长度：取值过大时，会同时放大 packed $A$ 与 packed $B$ 的 footprint，并增加 TLB 压力；取值过小时，则会增加 packing 次数和循环开销。因此，在第一轮搜索中让 `PackK` 比 `PackM / PackN` 扫得更细，是合理的实验设计，而不是任意扩大参数空间。

在当前 float32 路径下，$s=4$，因此 `packab` 的局部 footprint 可写成

$$ 
S_{\text{packAB}} = 4(M_cK_c + K_cN_c + M_cN_c)\ \text{bytes}.
$$

若进一步固定 $C_{\text{cache}}=\text{L1}=32$ KiB，并暂取 $\alpha=1$ 作为理论上界，则 `packab` 的第一轮 L1-oriented 候选需满足
$4(M_cK_c + K_cN_c + M_cN_c) \le 32768$，等价于 $M_cK_c + K_cN_c + M_cN_c \le 8192$。因此，`PackM / PackN / PackK` 不能按完整笛卡尔积自由组合，而应只保留满足该约束的组合。在当前候选集合 `PackM, PackN \in \{32,48,64,96,128\}`、`PackK \in \{16,32,48,64,96\}` 下，可行组合可整理为：

- `M_c=32`
  `N_c=32`: `K_c ∈ {16,32,48,64,96}`；`N_c=48`: `K_c ∈ {16,32,48,64}`；`N_c=64`: `K_c ∈ {16,32,48,64}`；`N_c=96`: `K_c ∈ {16,32}`；`N_c=128`: `K_c ∈ {16}`
- `M_c=48`
  `N_c=32`: `K_c ∈ {16,32,48,64}`；`N_c=48`: `K_c ∈ {16,32,48}`；`N_c=64`: `K_c ∈ {16,32}`；`N_c=96`: `K_c ∈ {16}`；`N_c=128`: 无可行解
- `M_c=64`
  `N_c=32`: `K_c ∈ {16,32,48,64}`；`N_c=48`: `K_c ∈ {16,32}`；`N_c=64`: `K_c ∈ {16,32}`；`N_c=96`: 无可行解；`N_c=128`: 无可行解
- `M_c=96`
  `N_c=32`: `K_c ∈ {16,32}`；`N_c=48`: `K_c ∈ {16}`；`N_c=64,96,128`: 无可行解
- `M_c=128`
  `N_c=32`: `K_c ∈ {16}`；其余 `N_c`: 无可行解

  一共 5+4+4+2+1+4+3+2+1+4+2+2+2+1+1 = 38 个可行组合。

从这一约束可以直接看到：当 `M_c` 和 `N_c` 取值增大时，允许的 `K_c` 上界会迅速下降，这也是 `PackK` 需要单独细扫、而 `PackM / PackN` 更适合先做较粗粒度分层测试的原因。

## 实验设计

基于上述参数定义和理论约束，本文设计了以下实验：

1. **第一轮筛选**：在矩阵大小 `\{64,128,256,512\}` 上进行参数筛选。对 `omp_blocked`，测试 `BlockSize ∈ {16,32,48,64,128,256}`；对 `omp_blocked_packb`，测试 `BlockSize ∈ {16,32,48}`；对 `omp_blocked_packab`，测试 `(M_c, N_c, K_c)∈\{32,48,64,96,128\}^2 \times \{16,32,48,64,96\}` 中满足前述 L1 footprint 约束的可行组合。第一轮的目标不是直接给出最终参数，而是缩小候选空间。
2. **第二轮复测**：对第一轮中保留的少数候选，在更大矩阵 `1024` 和 `2048` 上复测，以确认这些候选在较大工作负载下是否仍保持优势。最终参数以第二轮结果为准，而不是以前一轮的小矩阵结果直接定案。

在筛选阶段，每个组合测试 1000 次，并搜索并行线程数为 1, 2, 4, 8，以观察不同线程数下的性能表现和稳定性。最终在第二轮确认参数后，再基于保留的最优配置进行线程扩展与实现间性能对比。

## 目录组织

为避免不同实现与不同阶段的脚本、CSV 和图表混在同一目录下，blocked 系列实验采用单独的脚本目录和输出目录：

- 脚本目录：`scripts/ExperienceGEMM/Blocked/`
- 输出目录：`output/ExperienceGEMM/Blocked/`

在这两个根目录下，再按实现划分子目录：

- `omp_blocked/`
- `omp_blocked_packb/`
- `omp_blocked_packab/`

对每个实现，进一步按实验阶段划分子目录：

- `screening_small/`：第一轮筛选，对应矩阵大小 `64,128,256,512`
- `rescreen_large/`：第二轮复测，对应矩阵大小 `1024,2048`
- `summary/`：聚合表、最终图和面向报告的摘要结果

因此，一个推荐的目录结构如下：

```text
scripts/ExperienceGEMM/Blocked/
  omp_blocked/
  omp_blocked_packb/
  omp_blocked_packab/

output/ExperienceGEMM/Blocked/
  omp_blocked/
    screening_small/
    rescreen_large/
    summary/
  omp_blocked_packb/
    screening_small/
    rescreen_large/
    summary/
  omp_blocked_packab/
    screening_small/
    rescreen_large/
    summary/
```

这种组织方式的目的，是让不同实现、不同阶段和不同类型的 artifact 保持分离。目录负责表达实验语义；文件名则尽量只表达具体内容，例如 `results.csv`、`aggregates.csv`、`heatmap_packk_32.png`，避免使用过长且难以维护的文件名来同时编码实现名、阶段和版本信息。

以下命令从仓库根目录运行。benchmark 进程内部已通过 `taskset -c 0-7` 绑核；
外层 bash 脚本也建议加 `taskset -c 0-7` 以避免调度开销。

```bash
# Round 1：第一轮筛选（矩阵 64–512，REPS=1000）
# 需要 sudo 权限用于 cpupower 锁频（不可用时自动跳过）
sudo taskset -c 0-7 bash scripts/ExperienceGEMM/Blocked/omp_blocked/screening_small.sh
sudo taskset -c 0-7 bash scripts/ExperienceGEMM/Blocked/omp_blocked_packb/screening_small.sh
sudo taskset -c 0-7 bash scripts/ExperienceGEMM/Blocked/omp_blocked_packab/screening_small.sh

# 聚合 + 自动选出第二轮候选
python3 scripts/ExperienceGEMM/Blocked/summarize.py all --phase screening_small
python3 scripts/ExperienceGEMM/Blocked/select_candidates.py all

# Round 2：第二轮复测（矩阵 1024–2048，候选文件自动读取）
sudo taskset -c 0-7 bash scripts/ExperienceGEMM/Blocked/omp_blocked/rescreen_large.sh
sudo taskset -c 0-7 bash scripts/ExperienceGEMM/Blocked/omp_blocked_packb/rescreen_large.sh
sudo taskset -c 0-7 bash scripts/ExperienceGEMM/Blocked/omp_blocked_packab/rescreen_large.sh

python3 scripts/ExperienceGEMM/Blocked/summarize.py all --phase rescreen_large
```

## 当前结果摘要

按上述两轮流程执行后，当前平台上的 blocked 系列候选可先总结如下。

1. `omp_blocked`

第一轮筛选在 `64` 至 `512` 的方阵集合上保留了 `BlockSize = 64, 128, 256` 三组候选。第二轮在 `1024` 与 `2048` 上复测后，三者整体表现接近：`256` 在 `1024` 上略优，`128` 在 `2048` 上最优，`64` 略慢。因此，若需要给该路径选取单一代表参数，则当前更适合保留 `BlockSize = 128`，因为它在大矩阵上的表现更均衡。

2. `omp_blocked_packb`

第一轮筛选后进入第二轮的候选为 `BlockSize = 16, 32, 48`。在 `1024` 与 `2048` 的复测中，`48` 在两组矩阵上都优于 `32` 和 `16`，其中 `16` 明显最差。因此，当前平台下 `omp_blocked_packb` 的代表参数可取 `BlockSize = 48`。

3. `omp_blocked_packab`

第一轮 L1-oriented 可行组合筛选后，第二轮保留的三组候选为：

- `(PackM, PackN, PackK) = (32, 128, 16)`
- `(32, 96, 32)`
- `(64, 64, 32)`

在 `1024` 与 `2048` 的复测中，`(32, 128, 16)` 在全部线程配置下均保持第一，`(32, 96, 32)` 次之，`(64, 64, 32)` 再次之。因此，当前平台下 `omp_blocked_packab` 的代表参数可取 `(PackM, PackN, PackK) = (32, 128, 16)`。

需要说明的是，当前第二轮复测的重复次数并非完全同口径：`omp_blocked` 的复测结果仍来自 `REPS=1000` 的运行，而 `omp_blocked_packb` 与 `omp_blocked_packab` 的第二轮复测使用了 `REPS=100`。这不影响各自路径内部的候选筛选，但若要对三条路径的第二轮结果做严格横向比较，仍建议后续统一复测口径。

## 最终基线性能对比

前两轮实验确定参数后，再在不同线程数下测试与其他实现的性能对比，脚本如下：

```bash
# 运行脚本
scripts/ExperienceGEMM/find_optimal_threads.sh # 结果输出至 output/thread_scaling.csv
# scripts/ExperienceGEMM/find_optimal_threads_avx512.sh # 结果输出至 output/thread_scaling_avx512.csv

# 运行绘图脚本，将 thread_scaling_avx512.csv 和 thread_scaling.csv 的结果对比到同一张图上
python3 scripts/ExperienceGEMM/plot_scaling.py

# 生成的图表：
# output/ExperienceGEMM/BLAS1/scaling_plot_advanced.png：执行时间
# output/ExperienceGEMM/BLAS1/hw_metric_instructions.png：总指令数
```
