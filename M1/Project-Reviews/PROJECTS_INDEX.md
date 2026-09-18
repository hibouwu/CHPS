# Projects Index

## 总览表

| Project | Time Range | Main Direction | Strongest Claim | Biggest Risk |
|---|---|---|---|---|
| `PROJECT_PPN_TRAINING_SYSTEMS.md` | 2025-10-23 至 2026-05-05 (git) | 训练系统 / AI Infrastructure / HPC / C++ | C++ from-scratch autodiff/MLP，MNIST 约 `98.2%`；gprof 定位 matmul 96.4%，BLAS 后端到端 `7.6x`；git 支撑 GEMM/Tiny-ImageNet/Conv2D/部分 MPI runtime 的 Jianye 贡献 | Trainer、IST、compression 是多人模块；Tiny-ImageNet 和 IST 不能过度声称 |
| `PROJECT_TOP_D2Q9_LBM_KARMAN.md` | 2026-04-07 至 2026-04-28 (git) | HPC / 并行计算 / 科学计算 | MPI+OpenMP LBM 经 SoA/AVX-512/halo 优化，最终统一协议最好 `2047.32 MLUPS`；git 显示 Jianye 是核心代码/bench/report 主要贡献者 | Wei 也是共同作者且有关键提交；物理验证缺少 lift/drag/Strouhal；仅 mono-node |
| `PROJECT_CN1_POISSON_C.md` | 2025-12-03 至 2026-01-02 (git) | 数值计算 / C 科学计算 | C/LAPACK band solver + 迭代法验证，直接法 `N=10000` 约 `0.56-0.57 ms`；git 显示当前核心代码/报告均归 Jianye | 性能协议简单；CSR/CSC 验证规模小；课程模板边界需说明 |
| `PROJECT_POO_TPPROJET.md` | 2025-11-13 至 2025-12-21 (mtime, Low) | C++ 工程基础 / 并行 API 入门 | C++ 模板/多态粒子模拟器，支持 steady/unsteady、Parallel STL、thread/async 入口 | 缺少 git/报告和性能输出；个人贡献无法确认 |

## 每个项目适合投递的岗位方向

| Direction | Primary Projects | How to Position |
|---|---|---|
| 训练系统 / AI Infrastructure | PPN | 强调 autodiff、training loop、GEMM backend、MPI gradient sync、profiling |
| HPC / 性能优化 | TOP, PPN | TOP 主打 MPI+OpenMP/AVX-512；PPN 主打 GEMM/OpenBLAS/OpenMP profiling |
| C++ 后端 / 系统开发 | PPN, TOP, POO | PPN 模块化 runtime；TOP 性能工程；POO 作为基础补充 |
| 数值计算 / 科研计算 | TOP, CN1 | TOP 是科学计算性能优化；CN1 是数值方法基础 |

## 哪些项目适合放在一页简历
- 首选：PPN Training Systems。适合训练系统、AI Infra、C++、HPC 多方向裁剪，且第一阶段个人贡献有报告证据，第二阶段部分模块有 git 支撑。
- 首选：TOP D2Q9 LBM Karman。适合 HPC/并行计算岗位，claim 强，git 支撑 Jianye 为主要贡献者；表述为主导/主要参与，不写独立完成。
- 备选：CN1 Poisson C。适合数值计算或科学计算岗位的第二项目，作为数值方法基础证明。
- 不建议主放：POO TPProjet。除非投 C++ 初级后端或需要展示课程 C++ 基础，否则更适合作为面试补充。

## 哪些项目适合作为面试补充
- CN1：用于解释有限差分、LAPACK band storage、迭代法收敛和稀疏矩阵格式。
- POO：用于解释 C++ 模板、多态、Parallel STL、`std::thread/std::async`，但不讲性能数字。
- PPN 第二阶段：用于面试展开 GEMM/MPI/IST，但简历中只写证据最稳的部分。
- TOP 优化记录：用于 HPC 面试深入讲 profiling-driven optimization，不建议在简历塞入过多阶段数字。

## 推荐的简历项目排序
1. 训练系统 / AI Infrastructure：PPN -> TOP -> CN1
2. HPC / 性能优化：TOP -> PPN -> CN1
3. C++ 后端：PPN -> TOP -> POO
4. 数值计算 / 科研计算：TOP -> CN1 -> PPN

## 四类岗位分别应该突出哪些项目

### 训练系统
- 主项目：PPN。
- 突出：C++ autodiff、Trainer、CrossEntropyLoss、GEMM backend、MPI gradient bucketing/overlap。
- 谨慎：Tiny-ImageNet、IST 和 compression 都是阶段性工程验证。

### HPC
- 主项目：TOP。
- 突出：MPI halo batching、OpenMP、SoA、AVX-512、phase profiling、MLUPS benchmark。
- 第二项目：PPN GEMM。
- 谨慎：TOP 不覆盖多节点；PPN 自研 GEMM 不全面超过 OpenBLAS。

### C++ 后端
- 主项目：PPN。
- 突出：模块化 runtime、autodiff object model、distributed runtime 封装、测试覆盖。
- 第二项目：TOP 或 POO。
- 谨慎：POO 缺少性能和分工证据。

### AI Infrastructure
- 主项目：PPN。
- 突出：训练 loop、计算 kernel、profiling、distributed sync、bucket/overlap。
- 补充：TOP 的通信/计算 overlap 经验可类比分布式训练 runtime。

## 每个项目最强 claim 和最大风险

- PPN 最强 claim：第一阶段个人贡献有报告依据，MNIST MLP 约 `98.2%`，matmul profiling 到 BLAS 端到端 `7.6x`。
- PPN 最大风险：Trainer、IST、compression 等多人模块不能写成个人独立完成；Tiny-ImageNet 精度和 IST 性能不能夸大。
- TOP 最强 claim：完整 26 轮 HPC 优化证据链，最终统一协议最高 `2047.32 MLUPS`。
- TOP 最大风险：虽然 git 支撑 Jianye 主要贡献，但 Wei 是共同作者；最终物理验证和多节点验证不足。
- CN1 最强 claim：C/LAPACK/有限差分/迭代法闭环清晰，数值计算基础扎实。
- CN1 最大风险：benchmark 协议不够严谨，CSR/CSC 仅小规模验证。
- POO 最强 claim：C++ 模板、多态、Parallel STL 和 concurrency API 的小型可运行项目。
- POO 最大风险：缺少报告、分工和性能输出，不建议写性能 claim。

## 待补充材料清单
- PPN 第二阶段仍建议补充分工记录，用于解释 Trainer、IST、compression 等多人模块边界。
- TOP 每轮优化对应 commit 或分工记录，用于确认 Jianye 具体负责模块。
- POO benchmark 输出和个人贡献说明。
- CN1 运行脚本输出原始日志、重复次数和 benchmark 协议。
- TOP `scripts/bench_runs/*/status.txt` 为 FAILED 的原因说明。
