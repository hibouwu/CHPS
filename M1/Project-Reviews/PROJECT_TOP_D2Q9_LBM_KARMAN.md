# D2Q9 LBM Karman Vortex Solver

## 1. One-line Positioning
适合投递 HPC / 并行计算 / 科学计算 / C++ 性能优化方向，重点是 MPI+OpenMP 混合并行、LBM 数值模拟、SoA/AVX-512 内核重写和 profiling-driven optimization。

## 2. Recruiter Summary
该项目实现 D2Q9 Lattice Boltzmann Method（格子 Boltzmann 方法）模拟圆柱绕流 Kármán 涡街，代码采用 MPI 行分解和 OpenMP 线程并行。工作记录和报告保存了 26 轮优化证据：修复隐藏 sleep、纠正 MLUPS 公式、批量 halo 通信、删除冗余 barrier、AoS 到 SoA 重构、k-outer propagation、multi-cell collision、AVX-512 向量化、k-major halo pack/unpack 和单一 OpenMP parallel 区域。git 历史显示 Jianye 是主要提交者，当前核心 `physics/communications/profiling/main/bench/report` 多数行归 Jianye；Wei 也有若干关键提交，因此应表述为 Jianye 主导/主要参与的团队项目。

## 3. My Work
- 项目整体内容：C++ D2Q9 LBM Kármán vortex solver，MPI+OpenMP 混合并行，Python 可视化，benchmark/profiling 脚本，优化记录 `opt01-26`。
- 时间范围：git 可确认项目时间为 2026-04-07 至 2026-04-28；Jianye 个人提交覆盖 2026-04-07 至 2026-04-28，Wei 提交集中在 2026-04-25 至 2026-04-28。
- 我实际完成或主要参与的内容：git `shortlog` 显示 Jianye 22 个提交、Wei 5 个提交。当前 blame 显示 `src/lbm/physics.cpp` 872 行 Jianye / 23 行 Wei，`src/lbm/communications.cpp` 336 行 Jianye / 76 行 Wei，`src/lbm/profiling.cpp` 131 行全部 Jianye，`src/bin/main.cpp` 256 行 Jianye / 3 行 Wei，`scripts/bench.sh` 358 行全部 Jianye，`rapport/report_cn.tex` 1020 行 Jianye / 35 行 Wei。因此可以把 profiling infra、bench 脚本、主循环/FOM、SoA/AVX-512 物理 kernel、主要通信重构和报告整理写作 Jianye 主导或主要参与。
- 需要人工确认的个人贡献：Wei 的 5 个提交包括部分 SOA/MPI 优化记录和报告修改；对于 opt14-17、部分通信思路和报告段落，应写成团队协作或与 Wei 共同完成，不写成 Jianye 独立完成。

## 4. Technical Stack
- 语言：C++，Python visualization，Shell benchmark
- 数值方法：D2Q9 LBM, BGK collision, Kármán vortex street, `Re=96`
- 并行：MPI 3.0, MPICH 4.3.0, OpenMP 4.0, nonblocking `MPI_Isend/Irecv/Waitall`
- 性能技术：MLUPS/FOM, phase profiling with `MPI_Wtime`, AoS->SoA, cache locality, pull propagation, AVX-512 `zmm`, `restrict`, `#pragma GCC ivdep`, k-major halo packing
- 构建/脚本：CMake, `scripts/bench.sh`, `scripts/bench_runs/*`, `LBM_ENABLE_PROFILING`
- 关键路径：`src/lbm/physics.cpp`, `src/lbm/communications.cpp`, `src/lbm/profiling.cpp`, `src/bin/main.cpp`, `include/lbm/structures.hpp`, `include/lbm/communications.hpp`

## 5. Work Path / 工作路径
- baseline 是什么：D2Q9 LBM solver，网格 `800x160`，`20000` steps，FOM 定义为 MLUPS；初始代码包含正确性和性能破坏问题。
- 遇到的主要问题是什么：隐藏 `nanosleep(1s)`、错误 MLUPS 公式、MPI message 粒度过细、冗余 barrier、AoS 访存不适配 SIMD、SoA 初期 regression、halo wait/unpack 成本。
- 如何定位问题：源码审查、逐轮工作记录、`MPI_Wtime` phase profiling、`objdump` AVX-512 检查、bench runs 的 `fom.tsv/profiling_selected.txt`。
- 做了哪些实现、重构或优化：opt01-03 修正确性；opt04-08 删除 barrier/重复通信并批量 halo；opt09-17 改 loop order、pull propagation、OpenMP、overlap 和 I/O；opt18-26 加 profiling、AoS->SoA、k-outer propagation、multi-cell collision、AVX-512、k-major halo、single OMP region。
- 如何验证：`python -m lbm_viz --check` 多进程输出比较、max-delta 检查、Kármán wake qualitative visualization、统一 benchmark 协议 20 次 median、profiling breakdown。
- 结果如何：统一协议下 `np=1, OMP=16` 达 `2047.32 MLUPS`；最佳多进程 `np=2, OMP=4` 达 `1070.76 MLUPS`；开发路径中 `np=2, OMP=4` 从 SoA baseline `216` 到 opt24 `905` MLUPS。
- 还有什么局限：最终报告只覆盖 mono-node/intra-node MPICH；没有 lift/drag coefficient、Strouhal number 或所有最终配置的独立数值一致性验证；Wei 参与的具体优化边界需要在面试中诚实说明。

## 6. Evidence Map

| Claim | Evidence | File / Path | Confidence | Interview Risk |
|---|---|---|---|---|
| 项目实现 D2Q9 LBM 模拟 `Re=96` 圆柱绕流 Kármán 涡街 | 报告 Contexte 和配置输出 | `TOP/d2q9-lbm-karman/rapport/report_cn.tex`; `TOP/d2q9-lbm-karman/config.txt` | High | 可能被问 BGK collision 和 D2Q9 离散速度 |
| 并行策略是 MPI 行分解 + OpenMP 内部循环 | 报告 Contexte du projet | `TOP/d2q9-lbm-karman/rapport/report_cn.tex`; `src/lbm/communications.cpp`; `src/lbm/physics.cpp` | High | 需要解释 ghost/halo 交换 |
| opt01 发现并移除隐藏 `nanosleep(1s)` | 工作记录和报告 P1-A | `TOP/d2q9-lbm-karman/工作记录/优化01.md`; `TOP/d2q9-lbm-karman/rapport/report_cn.tex` | High | 面试可能质疑是否课程注入代码，需聚焦审计方法 |
| opt02 修复 MLUPS 乘 `comm_size` 的错误 | 工作记录和报告 P1-A | `TOP/d2q9-lbm-karman/工作记录/优化02.md`; `src/bin/main.cpp` | High | 需要能推导 MLUPS 正确公式 |
| 批量 vertical halo 将约 7182 小消息变成 1 个大消息 | opt08 工作记录和报告 P1-B | `TOP/d2q9-lbm-karman/工作记录/优化08.md`; `TOP/d2q9-lbm-karman/rapport/report_cn.tex` | High | 需解释 AoS/SoA 下 pack/unpack 是否连续 |
| P1-B 在 `np=2/4, OMP=1` 分别约 +50%/+166% | 报告 P1-B 表 | `TOP/d2q9-lbm-karman/rapport/report_cn.tex` | High | 第一阶段 macOS 环境波动大，不能跨平台比较 |
| AoS->SoA 单独造成 regression，但为 SIMD 准备 | opt19 表显示 `np=2, OMP=4` 从 278.66 到 216.22 MLUPS | `TOP/d2q9-lbm-karman/rapport/report_cn.tex`; `工作记录/优化19.md` | High | 需说明为什么 SoA 初期更慢 |
| k-outer propagation 使 `np=2, OMP=4` 从 216.22 到 319.07 MLUPS | 报告 opt20 | `TOP/d2q9-lbm-karman/rapport/report_cn.tex`; `src/lbm/physics.cpp` | High | 需要解释 plane working set 和 stride-1 |
| AVX-512 opt22 使 `np=2, OMP=4` 从 422.99 到 832.34 MLUPS | 报告 opt22 表，objdump 确认 `zmm` | `TOP/d2q9-lbm-karman/rapport/report_cn.tex`; `工作记录/优化22.md` | High | 需解释 alias/root cause 和 `ivdep/restrict` |
| opt24 k-major halo pack/unpack 开发口径达到 905.13 MLUPS | 报告 opt24 和历史表 | `TOP/d2q9-lbm-karman/rapport/report_cn.tex`; `工作记录/优化24.md` | High | 这是开发协议，不是最终官方 benchmark |
| 最终统一协议最好结果 `2047.32 MLUPS`，最好多进程 `1070.76 MLUPS` | 最终性能表和 `fom.tsv` | `TOP/d2q9-lbm-karman/rapport/report_cn.tex`; `TOP/d2q9-lbm-karman/scripts/bench_runs/20260428-123114/fom.tsv` | High | `status.txt` 显示 FAILED，需人工确认是否 bench 脚本状态异常不影响 FOM |
| 最终报告不包含 lift/drag/Strouhal 等物理量验证 | Conclusion 和 Annexe | `TOP/d2q9-lbm-karman/rapport/report_cn.tex` | High | 不能把 qualitative wake 写成完整物理验证 |
| Jianye 是当前核心代码和报告的主要 git 贡献者 | `shortlog` 为 Jianye 22 / Wei 5；blame 显示 `physics.cpp`、`communications.cpp`、`profiling.cpp`、`main.cpp`、`bench.sh`、`report_cn.tex` 主要或全部为 Jianye | `TOP/d2q9-lbm-karman/.git`; `src/lbm/physics.cpp`; `src/lbm/communications.cpp`; `src/lbm/profiling.cpp`; `src/bin/main.cpp`; `scripts/bench.sh`; `rapport/report_cn.tex` | High | 仍不能说独立完成；Wei 有关键提交和共同作者身份 |
| 项目开发时间为 2026-04-07 至 2026-04-28 | git 首尾提交日期；Wei 的提交集中在 2026-04-25 至 2026-04-28 | `TOP/d2q9-lbm-karman/.git` | High | 只代表当前仓库历史，不代表课题准备时间 |

## 7. Detailed Project Experience / 详细项目经历母版
项目整体目标是优化一个 D2Q9 LBM Kármán vortex solver，在保持模拟结果基本一致的前提下提升 MLUPS。计算流程由 `special_cells -> collision -> halo exchange -> propagation` 组成，性能指标是 `W*H*steps/(wall_time*1e6)`。

根据 git 历史，可以更明确地说：Jianye 主导或主要参与了当前核心性能代码、profiling、benchmark 和报告整理。尤其是 `physics.cpp`、`profiling.cpp`、`main.cpp` 和 `bench.sh` 的当前行归属高度集中在 Jianye；`communications.cpp` 也以 Jianye 为主，但包含 Wei 的贡献。因此简历中可以写“主导 LBM solver 的 profiling、benchmark、SoA/AVX-512 kernel 和主要通信优化”，但不写“独立完成 26 轮优化”。

技术实现分阶段。第一阶段先修复隐藏 `nanosleep`、错误 MLUPS 和 MPI count mismatch，随后删除冗余 barrier 与重复通信阶段，把垂直 halo 从数千个小消息改为 pack 后单次发送。再通过 loop order、push-to-pull propagation 和 OpenMP 并行改善 cache locality 与并行安全。第二阶段加入 phase profiling，重构 AoS 到 SoA。虽然 SoA 初期 regression，但它为 k-outer propagation 和 AVX-512 multi-cell collision 做了铺垫。opt22 通过 `restrict` 指针和 `#pragma GCC ivdep` 解决 alias 阻碍，使内层 `j` 循环产生 `zmm` AVX-512 指令。

关键代码路径是 `src/lbm/communications.cpp` 的 halo exchange、`src/lbm/physics.cpp` 的 collision/propagation、`src/lbm/profiling.cpp` 的 phase aggregation、`src/bin/main.cpp` 的主循环和 FOM 计算、`include/lbm/structures.hpp` 的数据布局。

验证方式包括 correctness check、多进程输出比较、phase profiling、disassembly 检查和统一 benchmark。最终报告明确说 qualitative Kármán wake 可见，但没有 lift/drag/Strouhal 等完整物理验证。

可量化结果包括开发路径 opt19->opt24 的 `216 -> 905 MLUPS`，统一协议最终 `np=1 OMP=16` `2047.32 MLUPS` 和 `np=2 OMP=4` `1070.76 MLUPS`。这些数字必须带实验条件和协议说明。

适合写进简历的是 MPI/OpenMP 混合并行优化、message batching、SoA/AVX-512、profiling-driven optimization。只适合面试展开的是隐藏 sleep 审计细节、SoA regression 的原因、k-major halo 的内存访问分析、单节点 MPI 的局限。

## 8. Resume Bullet Candidates / 简历要点候选

### 训练系统 / AI Infrastructure 方向
弱相关，不建议作为训练系统主项目。
- 可作为 HPC runtime 背景补充：用 MPI nonblocking communication 和 OpenMP overlap 分析通信/计算重叠瓶颈。
- 可迁移表述：通过 phase profiling 定位同步等待和 pack/unpack 开销，方法可类比分布式训练通信优化。

### HPC / 性能优化方向
- 优化 D2Q9 LBM MPI+OpenMP solver，围绕 halo exchange、collision、propagation 做 26 轮 profiling-driven optimization。
- 将 vertical halo 从约 7182 个小 MPI 消息重构为 packed bulk transfer，P1-B 在 `np=4, OMP=1` 开发环境下约 +166%。
- 将 AoS refactor 为 SoA 后重写 k-outer propagation，使 `np=2, OMP=4` 从 216.22 到 319.07 MLUPS（开发协议）。
- 通过 multi-cell collision、`restrict` 和 `#pragma GCC ivdep` 触发 AVX-512 `zmm` 向量化，`np=2, OMP=4` 从 422.99 到 832.34 MLUPS。
- 在统一协议下完成 20 次 median benchmark，最终最好单进程多线程 `2047.32 MLUPS`，最好多进程 `1070.76 MLUPS`（需说明 mono-node MPICH）。

### C++ 后端 / 系统开发方向
- 重构 LBM solver 的通信、物理计算和 profiling 模块，核心路径集中在 `communications.cpp`、`physics.cpp`、`profiling.cpp`。
- 设计 `LBM_ENABLE_PROFILING` 条件编译路径，用 `MPI_Wtime` 聚合 phase avg/max/min 和 loop 占比。
- 将主循环重构为单一 OpenMP parallel region，在 `omp master/omp for/barrier` 之间显式表达 MPI 与计算依赖。
- 维护 CMake/benchmark 脚本链路，自动生成 `fom.tsv`、`profiling_selected.txt` 和环境元信息。

### 数值计算 / 科研计算方向
- 实现 D2Q9 Lattice Boltzmann Method 模拟 `Re=96` 圆柱绕流，包含 BGK collision、streaming/propagation 和 obstacle boundary 处理。
- 用 pull propagation 消除并行写冲突，使 OpenMP 并行传播路径保持数据依赖安全。
- 通过多进程输出比较和 max-delta 检查验证优化前后数值差异维持在 FP64 舍入量级。
- 局限：未提供 lift/drag coefficient、Strouhal number 或全部最终配置的独立物理一致性验证。

## 9. Interview Pitch
- 30 秒讲法：这是一个 D2Q9 LBM Kármán 涡街求解器优化项目，核心是 MPI+OpenMP 混合并行和 CPU 性能优化。我根据 profiling 和 git 历史可以重点讲自己主导/主要参与的 benchmark/profiling、SoA/k-outer propagation、AVX-512 collision kernel 和主要通信优化；项目最终统一协议下最好单进程多线程是 2047.32 MLUPS，最好多进程是 1070.76 MLUPS。Wei 也参与了部分优化和报告，所以我不会说独立完成。
- 2 分钟讲法：我会按问题驱动讲。最开始不是直接优化 kernel，而是先修正确性和 benchmark 可信度：隐藏 `nanosleep` 会让每步 halo exchange 睡 1 秒，MLUPS 公式还错误乘了 `comm_size`。然后优化 MPI 通信，把冗余 barrier 删除，把垂直 halo 从数千个小消息改成 packed bulk transfer。接着针对计算核心，先调整 AoS loop order 和 pull propagation，再进入第二阶段的 SoA。SoA 单独变慢，但它让我们能做 plane-based k-outer propagation 和 multi-cell collision。opt22 通过 restrict pointer 和 ivdep 解决 alias，让内层循环生成 AVX-512 `zmm` 指令，`np=2 OMP=4` 从 423 到 832 MLUPS。最后通过 k-major halo pack/unpack 和 unified benchmark 协议确认最终性能。这个项目我会明确说明物理验证仍有限，不能夸成完整 CFD validation。

可能被追问的 8 个问题：
1. MLUPS 公式是什么？回答要点：global cells * steps / wall time / 1e6，不应乘 `comm_size`。
2. 为什么 vertical halo 原来会有 7182 小消息？回答要点：`(W-2)*9` 个方向值逐个发送，MPI latency 主导。
3. Push 和 Pull propagation 区别？回答要点：push 多线程写冲突，pull 每个 target 单 owner，适合 OpenMP。
4. 为什么 AoS->SoA 初期变慢？回答要点：布局变了但 kernel 仍按 per-cell AoS 心智访问，跨 plane gather 破坏 locality。
5. k-outer propagation 为什么快？回答要点：每次只访问一对 direction planes，内层 stride-1，可用 cache 和 memcpy/SIMD。
6. AVX-512 为什么之前没自动生成？回答要点：alias 分析失败；restrict plane pointer + `ivdep` 后内层 j 可向量化。
7. 最终 benchmark 是否覆盖多节点？回答要点：没有，只是 mono-node/intra-node MPICH。
8. 物理正确性如何验证？回答要点：输出比较和 qualitative wake；缺少 lift/drag/Strouhal，不能过度声称。

## 10. What Not To Overclaim
- 不要说个人独立完成 26 轮优化；git 支撑 Jianye 是主要贡献者，但 Wei 是共同作者且有关键提交。
- 不要跨平台比较 P1 macOS 和 P2 AMD 的绝对 MLUPS。
- 不要把 opt24 的 905 MLUPS 当最终官方 benchmark；它是开发协议。
- 不要说最终已经完成严格 CFD 物理验证；缺少 lift/drag/Strouhal。
- 不要说 MPI 多节点性能已验证；报告仅覆盖 mono-node/intra-node。
- 注意 `scripts/bench_runs/20260428-123114/status.txt` 显示 FAILED，需要人工确认 bench 脚本状态与 FOM 采用关系。

## 11. Keywords for Internship Search
HPC, 高性能计算, MPI, OpenMP, Hybrid Parallelism, D2Q9, Lattice Boltzmann Method, LBM, Karman Vortex, CFD, Scientific Computing, AVX-512, SIMD, SoA, AoS, Cache Locality, Halo Exchange, Nonblocking MPI, MPI_Wtime, MLUPS, Profiling, C++ Performance, Numerical Simulation, BGK Collision, Vectorization
