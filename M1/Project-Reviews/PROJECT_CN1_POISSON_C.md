# Poisson 1D Heat Equation Solver in C

## 1. One-line Positioning
适合投递数值计算 / 科研计算 / C 后端基础工程方向，重点是有限差分离散、LAPACK 带状矩阵求解、迭代法验证与基础性能测量。

## 2. Recruiter Summary
该项目用 C 实现一维稳态热方程的 Poisson 问题求解，把有限差分离散后的三对角线性系统分别交给直接法和迭代法处理。项目覆盖 LAPACK General Band 存储、`dgbtrf/dgbtrs/dgbsv` 调用、手写三对角 LU、Richardson/Jacobi/Gauss-Seidel 迭代，以及 CSR/CSC 稀疏格式扩展。报告给出了解析解校验、残差/前向误差、迭代次数和 Docker 环境下的计时结果，适合作为数值方法和 C 科学计算能力的证据。

## 3. My Work
- 项目整体内容：C 语言实现一维 Poisson/热方程有限差分求解，包含直接法、迭代法、带状矩阵存储、CSR/CSC 稀疏格式、验证脚本和性能绘图脚本。
- 时间范围：git 可确认项目时间为 2025-12-03 至 2026-01-02；Jianye 个人提交时间范围相同。
- 我实际完成或主要参与的内容：git 历史显示该仓库共有 14 个提交，提交作者均为 Jianye SHI；当前关键源码和报告的 `git blame` 也全部归 Jianye，包括 `src/lib_poisson1D.c`、`src/lib_poisson1D_richardson.c`、`src/tp_poisson1D_direct.c`、`src/tp_poisson1D_iter.c`、`include/lib_poisson1D.h` 和 `RapportBuild/rapport.tex`。因此可以把直接法、迭代法、矩阵结构、报告和实验脚本作为本人完成内容表述。
- 需要人工确认的个人贡献：若课程提供了初始模板或老师发放的 skeleton，需要补充说明哪些函数来自模板；git 只能证明当前仓库提交/行归属，不能证明原始模板边界。

## 4. Technical Stack
- 语言：C
- 数值库：BLAS, LAPACK
- LAPACK 接口：General Band (GB), `dgbtrf`, `dgbtrs`, `dgbsv`, `dgbmv`
- 数值方法：有限差分、三对角 LU、Richardson、Jacobi、Gauss-Seidel、CSR/CSC SpMV
- 构建与环境：Makefile, Docker, GCC `-O2`
- 脚本与输出：`scripts/benchmark_direct.sh`, `scripts/benchmark_iter.sh`, `scripts/plot_benchmark.py`, `scripts/plot_convergence.py`, `RapportBuild/Images/benchmark_plot.png`, `RapportBuild/Images/convergence_comparison.png`

## 5. Work Path / 工作路径
- baseline 是什么：一维稳态热方程 `-kT''=g`，Dirichlet 边界，二阶中心差分离散为三对角系统 `Au=f`。
- 遇到的主要问题是什么：需要在正确性、存储格式和求解效率之间建立可验证实现；迭代法在 `N>=100` 且最大 1000 次迭代时无法达到设定容差。
- 如何定位问题：用 `g=0` 的线性解析解、前向误差、相对残差、LAPACK 参考结果和收敛曲线验证。
- 做了哪些实现、重构或优化：实现 LAPACK General Band 存储、LAPACK 直接法、手写三对角 LU、Richardson/Jacobi/Gauss-Seidel，并扩展 CSR/CSC 结构和 SpMV。
- 如何验证：`N=10/100` 误差表、`N=100/1000/10000` 直接法计时表、迭代次数表、benchmark/convergence 图。
- 结果如何：直接法在 `N=10000` 上约 `0.56-0.57 ms`；三对角 LU 误差 `<1e-14`；Gauss-Seidel 在 `N=10` 达到 `1e-3` 需要 45 次，Richardson/Jacobi 需要 88 次。
- 还有什么局限：性能实验条件较简单；迭代法最大迭代次数限制为 1000；CSR/CSC 只在 `N=10` 上展示正确性；若存在课程模板代码，需要补充模板边界。

## 6. Evidence Map

| Claim | Evidence | File / Path | Confidence | Interview Risk |
|---|---|---|---|---|
| 项目求解一维稳态热方程，经有限差分离散为三对角线性系统 | 报告 Introduction 和 Discrétisation 章节给出 PDE、边界条件和矩阵形式 | `CN1/TP_Poisson_C/RapportBuild/rapport.tex` | High | 可能被追问离散符号和边界项如何进入右端项 |
| 使用 C、BLAS、LAPACK 和 Docker 环境 | 报告 Environnement 章节明确说明 | `CN1/TP_Poisson_C/RapportBuild/rapport.tex`; `CN1/TP_Poisson_C/docker/Dockerfile` | High | 需要能解释 LAPACK band storage 参数 |
| 实现/使用 LAPACK GB 直接法和三对角 LU | 报告列出 `dgbtrf/dgbtrs/dgbsv`，并描述 `dgbtrftridiag` | `CN1/TP_Poisson_C/RapportBuild/rapport.tex`; `CN1/TP_Poisson_C/src/lib_poisson1D.c` | High | 手写 LU 是否带 pivoting、稳定性条件会被问 |
| 直接法在 `N=10000` 上约 `0.56-0.57 ms` | 报告 Temps d'Exécution 表格 | `CN1/TP_Poisson_C/RapportBuild/rapport.tex`; `CN1/TP_Poisson_C/RapportBuild/Images/benchmark_plot.png` | High | 需补充实验条件：单次/多次统计、CPU 频率控制不完整 |
| 迭代法包括 Richardson、Jacobi、Gauss-Seidel | 报告 Méthodes Itératives 章节和 `tp_poisson1D_iter.c` 路径 | `CN1/TP_Poisson_C/RapportBuild/rapport.tex`; `CN1/TP_Poisson_C/src/tp_poisson1D_iter.c` | High | 需解释 Richardson 最优参数为何与 Jacobi 曲线重合 |
| `N=10` 下 Gauss-Seidel 45 次、Richardson/Jacobi 88 次达到 `1e-3` | 报告迭代次数表 | `CN1/TP_Poisson_C/RapportBuild/rapport.tex` | High | 迭代次数依赖容差和初值，需说明条件 |
| CSR/CSC 结构和 SpMV 被扩展用于 Richardson | 报告 Exercice 10 描述结构和 `IMPLEM=3/4` | `CN1/TP_Poisson_C/RapportBuild/rapport.tex`; `CN1/TP_Poisson_C/include/lib_poisson1D.h` | Medium | 只看到报告描述，需现场指认具体实现函数 |
| 该项目为 Jianye SHI 报告 | 标题页 `\author{Jianye SHI}` | `CN1/TP_Poisson_C/RapportBuild/rapport.tex` | High | 不等于每行代码均为个人完成 |
| 当前仓库核心代码和报告由 Jianye 提交并在 blame 中归属 Jianye | `shortlog` 显示 14 个提交均为 Jianye；关键文件 blame 全部为 Jianye | `CN1/TP_Poisson_C/.git`; `src/lib_poisson1D.c`; `src/lib_poisson1D_richardson.c`; `src/tp_poisson1D_direct.c`; `src/tp_poisson1D_iter.c`; `include/lib_poisson1D.h`; `RapportBuild/rapport.tex` | High | git 不能区分课程初始模板和本人新增代码，需要说明模板边界 |
| 项目开发时间为 2025-12-03 至 2026-01-02 | git 首尾提交日期 | `CN1/TP_Poisson_C/.git` | High | 只代表仓库历史，不代表课程布置/截止日期 |

## 7. Detailed Project Experience / 详细项目经历母版
项目整体目标是从物理方程出发，完成一维稳态热传导问题的数值求解闭环：PDE 建模、有限差分离散、线性系统构造、求解器实现、正确性验证和基础性能比较。核心技术对象是 Poisson 1D 三对角矩阵，它天然适合带状存储和线性复杂度求解。

我承担或主要参与的模块可以用 git 历史支撑：仓库提交作者均为 Jianye SHI，关键源码和报告当前行归属也均为 Jianye。因此可以将矩阵构造与 GB 存储、直接法求解入口、迭代法入口、CSR/CSC 数据结构、validation/benchmark 脚本与报告整理写作本人项目工作。保留的风险是课程 skeleton 可能已有部分接口或空函数。

技术实现上，直接法部分使用 LAPACK General Band 格式组织三对角矩阵，并通过 `dgbtrf/dgbtrs/dgbsv` 完成 factorization/solve；同时报告描述了无 pivoting 的手写三对角 LU。迭代法部分以 SpMV 为核心，分别构造 Richardson、Jacobi 和 Gauss-Seidel 更新，并用相对残差作为停止准则。CSR/CSC 部分将三对角矩阵泛化为稀疏结构，为更复杂网格问题预留接口。

关键代码路径包括 `src/lib_poisson1D.c`、`src/lib_poisson1D_richardson.c`、`src/tp_poisson1D_direct.c`、`src/tp_poisson1D_iter.c`、`include/lib_poisson1D.h`、`scripts/benchmark_direct.sh` 和 `scripts/plot_convergence.py`。

实验验证方式包括解析解比较、LAPACK 参考比较、相对残差、前向误差、不同 N 的计时和迭代次数统计。可量化结果包括直接法 `N=10000` 约 `0.56-0.57 ms`，三对角 LU 误差 `<1e-14`，以及 `N=10` 下 Gauss-Seidel 比 Richardson/Jacobi 迭代次数约少一半。

局限和风险是：性能数字缺少完整统计协议，CSR/CSC 验证规模小，迭代法在 `N>=100` 未在 1000 次内达到容差，不能夸大为通用高性能稀疏求解器。

适合写进简历的是：有限差分建模、LAPACK band solver、迭代法比较、误差/残差验证。只适合面试展开的是：GB/CSR/CSC 存储细节、迭代法收敛条件、为什么 condition number 随 `O(N^2)` 变差。

## 8. Resume Bullet Candidates / 简历要点候选

### 训练系统 / AI Infrastructure 方向
弱相关，不建议作为该方向简历主项目。
- 可作为数值计算背景补充：实现 C/LAPACK 线性系统求解与验证脚本，为后续训练系统中的矩阵计算理解提供基础。

### HPC / 性能优化方向
- 用 LAPACK General Band 存储求解 1D Poisson 三对角系统，对比手写三对角 LU 与 LAPACK 直接法，`N=10000` 计时约 `0.56-0.57 ms`（需补充实验条件）。
- 通过 benchmark 脚本和 log-log 图验证带状直接法在该 1D 问题上的近线性增长趋势。
- 对 Richardson/Jacobi/Gauss-Seidel 做迭代次数对比，观察 Gauss-Seidel 在 `N=10` 下 45 次达到 `1e-3`。
- 扩展 CSR/CSC 稀疏格式和 SpMV 路径，将 Richardson 从 band storage 泛化到 sparse storage。

### C++ 后端 / 系统开发方向
弱相关，不建议作为 C++ 后端主项目；项目主体是 C。
- 用 C 组织数值库接口、Makefile/Docker 环境和 CLI 求解入口，完成可复现实验流程。
- 实现矩阵结构、求解器入口和 validation 脚本，适合作为 C 工程基础证据。

### 数值计算 / 科研计算方向
- 从一维稳态热方程出发，用二阶中心差分构造三对角 Poisson 系统，并用解析解验证误差。
- 实现直接法和迭代法两类求解路径，对比 LU、Richardson、Jacobi、Gauss-Seidel 的误差与收敛行为。
- 使用 BLAS/LAPACK band storage 处理三对角矩阵，避免 dense 存储带来的额外空间和计算开销。
- 解释 `N>=100` 时迭代法 1000 次内未达容差的原因：Poisson 矩阵条件数随 `O(N^2)` 增长。
- 扩展 CSR/CSC 稀疏格式，为二维/三维或非结构化问题迁移做接口准备。

## 9. Interview Pitch
- 30 秒讲法：这个项目是我用 C 做的一维 Poisson/热方程数值求解器。核心是把 PDE 用二阶有限差分离散成三对角系统，然后分别用 LAPACK band solver、手写三对角 LU 和 Richardson/Jacobi/Gauss-Seidel 迭代法求解。验证上我用了 `g=0` 的解析解、前向误差、残差和 benchmark 图；直接法在 `N=10000` 的报告计时约 `0.56-0.57 ms`。
- 2 分钟讲法：我会先从模型讲起：一维稳态热方程在 Dirichlet 边界下离散后得到 `2/-1/-1` 的三对角矩阵。因为矩阵是 banded，我没有把重点放在 dense solve，而是用 LAPACK General Band 格式和 `dgbtrf/dgbtrs/dgbsv`，同时实现了一个简化的三对角 LU。迭代部分实现 Richardson、Jacobi 和 Gauss-Seidel，用相对残差控制收敛。验证中，直接法前向误差达到 `<1e-14`；迭代法在小规模下能收敛，但 `N>=100` 时 1000 次内达不到容差，报告中解释为条件数随 `N^2` 增长。最后我扩展了 CSR/CSC 和 SpMV，使 Richardson 可以走稀疏矩阵接口。这个项目我会把它定位为数值计算和 C 科学计算证据，而不是大规模 HPC 项目。

可能被追问的 8 个问题：
1. GB 存储中三对角矩阵如何映射到数组？回答要点：`kl=ku=1`，报告给出 `AB(ku+1+i-j,j)`，主对角、上下对角分行存储。
2. 手写三对角 LU 为什么可以不 pivot？回答要点：Poisson 1D 矩阵对称正定、严格结构稳定；但一般 band matrix 仍应使用 pivoting。
3. Richardson 的收敛参数怎么选？回答要点：报告引用课程推导，最优 Richardson 在该问题上与 Jacobi 曲线重合；需要回到谱半径解释。
4. 为什么 `N=100` 迭代法 1000 次仍不够？回答要点：条件数随 `O(N^2)` 增长，低频误差消除慢。
5. 误差 `<1e-14` 和 `3.8e-3` 分别代表什么？回答要点：直接法接近浮点精度；迭代法小规模误差主要来自离散误差。
6. CSR 和 CSC 的 SpMV 区别？回答要点：CSR 按行聚合输出，CSC 按列向输出累加。
7. 计时是否可作为严格 benchmark？回答要点：不能过度声称，报告有 Docker/Fedora/CPU/GCC 信息，但缺少重复次数、频率锁定等完整协议。
8. 如果扩展到 2D 怎么做？回答要点：矩阵变为更宽带或稀疏结构，CSR/CSC 更合适，迭代法可能需要 CG/预条件。

## 10. What Not To Overclaim
- 不要说这是通用高性能稀疏求解器；证据主要是一维三对角问题。
- 不要把 `0.56 ms` 写成严格可复现性能结论；需补充实验条件。
- 不要说 CSR/CSC 已在大规模 2D/3D 上验证；报告只展示 `N=10` 正确性。
- 不要说“完全从空仓库独立完成所有代码”；git 支撑当前仓库贡献归属，但课程模板边界仍需说明。
- 不要说迭代法性能优秀；报告明确显示 `N>=100` 1000 次内未达容差。

## 11. Keywords for Internship Search
数值计算, 科学计算, 计算物理, 有限差分, Poisson 方程, 线性系统求解, 稀疏矩阵, C 语言, BLAS, LAPACK, General Band, CSR, CSC, SpMV, Richardson, Jacobi, Gauss-Seidel, Docker, Numerical Computing, Scientific Computing, Finite Difference, Linear Solver, Sparse Matrix, Banded Matrix, HPC fundamentals
