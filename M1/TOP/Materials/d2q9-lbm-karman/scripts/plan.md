# 实验重跑计划

生成日期：2026-04-28

---

## 1. 总体判断

核心问题有三个，优先级递减：

**问题 A（最严重）：** P1 和 P2 的测试平台不同。P1（opt01–17）在 macOS AArch64（Apple Silicon）完成，P2（opt18–26）在 AMD Ryzen 9 8940HX Linux x86-64 完成。`rapport/report_cn.tex` 的"全程性能演进"表把两组数字并排比较，包括声称"较基线 ×15"——这个跨机器的倍数在数值上是无意义的。这是目前报告最需要处理的问题。

**问题 B（重要）：** P2 阶段的 opt19–24 数据是在"无绑核、无锁频"条件下采集的。`bench.sh` 曾引入 `OMP_PROC_BIND=close`，但经实测验证（2026-04-28），在没有配套 MPI 进程绑定（`--map-by core:PE=N`）的情况下，该设置会导致不同 rank 的 OMP 线程竞争相同物理核，FOM 从 ~772 降至 ~659（−15%）。现已从 `bench.sh` 移除该设置。切换协议后测到的 opt26 最终 FOM（802 MLUPS）与 opt24（905 MLUPS）的差距，除 OMP 线程数不同（OMP=8 vs OMP=4）外，还混入了该绑定问题；去掉绑定后 np=2 OMP=4 实测 ~772 MLUPS，剩余差距的具体来源（PROFILING=ON 开销、频率状态、批次抖动等）尚未逐一排查，待统一协议重跑后确认。

**问题 C（可控）：** opt19–22 的中间版本代码难以精确重现，但它们的相对提升幅度（+14%, +33%, +97%）足够大，测量噪声不改变结论方向。

**总体策略：** 不追求逐版本完全重现。重跑目标是：用当前最终代码（opt26）+ 当前协议，建立一套内部一致的 P2 最终基准数据；历史版本的相对提升数据保留为"开发期定向测量"，降级措辞；P1 数据明确标注平台后保留。

---

## 2. 必须重跑项

### 必须重跑 #1：P2 阶段最终性能基准

**为什么：** 建立 P2 阶段内部一致的锚点。当前 opt24（905 MLUPS, OMP=4）和 opt26（802 MLUPS, OMP=8）无法直接比较，需在同一协议下给出同一代码的多个配置数字。

用当前代码（opt26），`LBM_ENABLE_PROFILING=OFF`：

重跑矩阵分两组，目的不同，不可混用：

**组 A：最终版本吞吐扫描**（替换 P2 汇总表里"当前协议"列）

| np | OMP | 说明 |
| -- | --- | --- |
| 2 | 4 | opt24 等效口径；同时用于 6.4 节消除"802 vs 905"误读 |
| 2 | 8 | 充分利用 CCX，当前协议主配置 |
| 1 | 16 | 单进程吞吐上限 |
| 4 | 4 | 记录 np=4 退化，支持 CCX 拓扑分析 |

**组 B：历史对比表修补**（P2 汇总表里 `np=1 OMP=4` 一列，报告第 941 行附近）

| np | OMP | 说明 |
| -- | --- | --- |
| 1 | 4 | 直接替换历史表中 opt19/20/21 的 np=1 OMP=4 数字 |

组 B 只跑一个配置，但不可省略——否则历史对比表的那列数字仍然是无绑核无锁频的口径，与 opt26 新数据不统一。

**配置要求（组 A 和 B 相同）：**

- `LBM_ENABLE_PROFILING=OFF`（FOM 测量；perf stat 不需要）
- warmup 1 次，repeats 3 次取 median
- `OMP_PROC_BIND` **不设置**：无配套 MPI 进程绑定（`--map-by core:PE=N`）时，`OMP_PROC_BIND=close` 会导致不同 rank 的线程重叠在同一物理核上，实测降低约 15%；让 OS 自由调度反而更好
- `cpupower frequency-set -g performance`：**必须执行**。若 sudo 不可用，`bench.sh` 前置检查直接 hard-fail，本次运行中止，`status.txt` 写入 `FAILED`，错误信息见 `console.log`。该组数据不得用于报告正式表格，解决 sudo 权限后重跑。不接受"警告后继续"的中间状态。

**执行方法：直接运行 `bench.sh`（唯一官方入口）**

```bash
cd /home/jianyeshi/Note/TOP/d2q9-lbm-karman
./scripts/bench.sh
```

脚本内部自动完成：
1. 6 项前置检查（MPI 工具、配置文件、cpupower、sudo 权限）
2. 两个独立编译目录：`build-bench-fom`（PROFILING=OFF）和 `build-bench-prof`（PROFILING=ON）
3. 后构建验证：libmpi 链接路径、AVX-512 zmm 指令数
4. FOM 扫描（7 个配置）+ profiling 采集（np=2 OMP=8）
5. 结果写入 `scripts/bench_runs/YYYYMMDD-HHMMSS/`

时间估算：约 35 min（含两次 cmake + 7 个 FOM 配置的 warmup/3 次重复 + 3 次 profiling）。

### 必须重跑 #2：opt26 profiling 数据

**为什么：** 报告 P2-D 节引用的 halo_finish 27.6%、waitall 10.4% 等数字来自 `工作记录/优化26.md` §5.2，需用当前协议重采集一次作为报告正式引用数据。

用当前代码（opt26），`LBM_ENABLE_PROFILING=ON`，仅 np=2 OMP=8：

- warmup 1 次，repeats 3 次，绑核锁频要求与 #1 相同（sudo 不可用则停止）
- 不需要 perf stat
- **汇总规则：** 取 3 次中 `loop_total avg` 最小的那次的 phase 明细（最稳定的一次），报告该次的各 phase avg 和 max。不对 3 次的 phase avg 再取平均——那样会把调度抖动叠进 profiling 数字。

时间估算：约 5 min。

### 必须重跑 #3（含在 #1 内）：最终代码无退化验证

opt26 代码以 np=2 OMP=4 测出的 FOM 应 ≈ opt24 的 905 MLUPS（算法完全一致，仅 OMP parallel 结构重组）。此配置已包含在 #1 组 A 中，不额外增加时间。

**措辞边界：** 这个结果只能说"opt26 最终代码在 np=2 OMP=4 下 FOM 与 opt24 记录值无显著差异，结构重构未引入退步"。它不能重新证明 opt24 的因果贡献（k-major halo +8.7%）——那个结论是由 opt23→opt24 的 A/B 对比建立的，本次无法复现。

---

## 3. 建议重跑项

### 建议重跑 #B1：opt22 vs opt21 AVX-512 相对提升验证

**为什么：** "+97% at np=2 OMP=4"是整个报告最大的单步跳跃。前提条件：能 git checkout 到 opt21 commit 编译运行。如果提取成本 > 15 分钟，跳过，改用定性措辞（见第 6 节）。

如做：np=2 OMP=4，PROFILING=OFF，repeats=3，绑核锁频。时间估算约 15 min。

---

## 3.5 已确认的诊断陷阱（执行前必读）

**陷阱 1：AVX-512 在 `.so` 里，不在 exe 里。**
物理核心代码编译进 `libtop.lbm-lib.so`；`top.lbm-exe` 只是主函数壳。
用 `objdump -d top.lbm-exe | grep -c zmm` 总是得到 0，不代表 AVX-512 缺失。
正确验证命令：`objdump -d build/lib/libtop.lbm-lib.so | grep -c zmm`（应 >200）。

**陷阱 2：cmake 不删 cache 直接重传 flag，新 flag 不生效。**
`-DCMAKE_CXX_FLAGS="-march=native"` 在有旧 CMakeCache.txt 时可能被忽略，
导致编译出无 AVX-512 的二进制，FOM 直接退回 opt21 水平（400–500 MLUPS）。
每次切换编译选项前执行 `rm -f build/CMakeCache.txt`。

**陷阱 3：`OMP_PROC_BIND=close` 无 MPI 进程绑定时有害。**
np=2 OMP=4 实测：有 `OMP_PROC_BIND=close` → 659 MLUPS；无绑定 → 772 MLUPS（−15%）。
根因是两个 rank 的线程在没有 MPI 显式进程绑定的情况下叠到相同物理核。
`bench.sh` 已移除该设置；不要在 run 命令里手动加回去。

---

## 4. 可降级为定性证据的历史结果

| 数据来源 | 当前在报告位置 | 处理方式 |
| --- | --- | --- |
| P1 全部 FOM（60/103/194 MLUPS） | 全程演进表 + P1 各表 | 保留，加注"测试平台：macOS AArch64" |
| "较基线 ×15" | 全程演进表末行、路线图 | 删除，改写（见第 6 节） |
| opt19–21 绝对 FOM（157/213/293 MLUPS） | P2-B 节表格 | 保留，加脚注"开发期测量，无绑核锁频，仅用于阶段间相对提升参考" |
| opt22 vs opt21 +97% | P2-B 节 | 保留百分比；若 B1 重跑成功则替换为新数字 |
| opt24 905 MLUPS | P2-C 节、全程演进表 | 若 #1 中 np=2 OMP=4 复现 ≈905 则替换；若偏差 ±5% 内，保留旧数字加注 |
| opt25 否定实验（约 -3%, 约 -34%） | P2-D 节 | 全部保留，把百分比改为"约"，定性描述即可 |
| "FP64 达理论峰值约 65%" | P2-B opt22 节 | **删除**，无计算依据 |
| opt26 intra-node +0.3% | P2-D 节 | 保留，已是当前协议测出的可信数字 |

---

## 5. 统一实验口径与命令模板

### 唯一入口

```bash
cd /home/jianyeshi/Note/TOP/d2q9-lbm-karman
./scripts/bench.sh
```

脚本自动管理两个编译目录，无需手动 cmake：

| 目录 | PROFILING | 用途 |
| -- | -- | -- |
| `build-bench-fom` | OFF | FOM 扫描（7 配置） |
| `build-bench-prof` | ON | profiling 采集（np=2 OMP=8） |

每次运行都会删除 CMakeCache.txt 后重新 configure，保证 `-march=native` 等 flag 生效。

### 输出目录结构

```
scripts/bench_runs/YYYYMMDD-HHMMSS/
  meta.txt               # 机器、编译器、MPI、git rev
  fom.tsv                # 7 配置 × run1/run2/run3/median (MLUPS)
  profiling_raw.txt      # 3 次 profiling 完整输出
  profiling_selected.txt # 最佳一次（max FOM = min loop_total avg 代理）
  console.log            # 所有构建 + 运行输出
  status.txt             # SUCCESS 或 FAILED
```

### FOM 扫描配置矩阵

| np | OMP | 说明 |
| -- | --- | -- |
| 1 | 4 | 历史对比表修补（组 B） |
| 1 | 16 | 单进程吞吐上限 |
| 2 | 4 | opt24 等效口径（组 A） |
| 2 | 8 | CCX 主配置（组 A） |
| 2 | 16 | 超订阅参考 |
| 4 | 4 | np=4 退化记录 |
| 4 | 8 | np=4 扩展参考 |

### AVX-512 验证（后构建自动执行，也可手动确认）

```bash
objdump -d build-bench-fom/lib/libtop.lbm-lib.so | grep -c "zmm"
# 应 > 200；物理核心代码在 .so，不在 top.lbm-exe
```

MPI 环境：`env -u MPI_HOME LD_LIBRARY_PATH=/usr/lib64/mpich/lib`（bench.sh 内部已设置）。

---

## 6. 报告改写方案

### 6.1 全程性能演进表——拆分为两张

**表 A（P1 阶段，开发平台：macOS AArch64）：** 保留 P1 的 FOM 数字，表头加注平台，作用是展示优化思路演进，而不是最终性能数字。

**表 B（P2 阶段，正式测试平台：AMD Ryzen 9 8940HX，Linux x86-64）：** 只放 P2 数字，基线是 opt19 的 279 MLUPS（np=2 OMP=4），最终是重跑 #1 的实测值。

**"较基线 ×15"** 改写为：
> P2 阶段在 AMD Ryzen 9 8940HX 上，从 SoA 基线（opt19，np=2 OMP=4，279 MLUPS）经四轮核心优化，达到最终 XXX MLUPS，提升约 3.2×。

### 6.2 opt19–24 中间版本脚注

在相关表格加：
> 各中间步骤数据采集于开发期（无 CPU 频率锁定、无 OMP 线程绑定），用于阶段间相对提升参考。最终版本（opt26）数据采集于统一测量协议下（见 §测量协议）。

### 6.3 "FP64 达理论峰值 65%"——删除

替换为：
> 通过 \texttt{objdump} 确认内层 $j$ 循环生成 AVX-512 \texttt{vmovupd}（64 字节宽）与 \texttt{vfmadd231pd} 指令，向量化有效。

### 6.4 opt26 "802 vs 905"的解释

在 P2-D 节现有文字后加：
> 注：opt24 的 905 MLUPS 采用 np=2 OMP=4，本节 opt26 的 802 MLUPS 采用 np=2 OMP=8。以相同配置（np=2 OMP=4）在 opt26 最终代码上测量，FOM 为 XXX MLUPS，与 opt24 记录值无显著差异，表明 opt25–26 的 OMP parallel 结构重组未引入性能退步。

XXX 填入重跑 #1 的实测值。

### 6.5 路线图末行

将 `最终：905 MLUPS` 改为 `最终：XXX MLUPS（np=2 OMP=4，统一协议）`，opt26 的 802 MLUPS 单独标注为 np=2 OMP=8 的数字。

---

## 7. 时间预算与执行顺序

总计约 1.5 小时（含编译和结果整理）：

| 顺序 | 任务 | 时间 |
| --- | --- | --- |
| 1 | `./scripts/bench.sh`（含两次 cmake + 7 FOM 配置 + 3 次 profiling） | 35 min |
| 2 | 根据 fom.tsv 填入 report_cn.tex（XXX 替换、表格更新、脚注补充） | 20 min |
| 3 | 删除"×15"、删除"65%峰值"、拆分全程演进表为 P1/P2 两张 | 20 min |
| 4（可选） | 检查 git log 看 opt21/opt22 commit 是否易于 checkout，如 15 min 内可编译则跑建议重跑 #B1 | 15 min |

---

## 8. 关键风险与假设

| 风险 | 可能性 | 应对 |
| --- | --- | --- |
| opt26 以 np=2 OMP=4 测出的 FOM 与 opt24 的 905 差异 >5% | **高**（实测 ~772，差距约 15%） | 已知根因：opt24 无绑定无锁频；重跑时 PROFILING=OFF + 锁频后预期缩小差距。若重跑后仍 <900，在报告写"当前协议下 XXX MLUPS，opt24 记录值 905 MLUPS 为开发期无频率锁定测量，两者不直接可比"。 |
| cpupower 需要 sudo 但不可用 | 低 | 停止本次运行；解决 sudo 权限后重跑。不接受无锁频数据进入正式表格。若确实无法获得 sudo，在报告协议节说明"频率控制不可用"，并把所有 FOM 数字标注为"无频率锁定"，不与锁频数据并排比较。 |
| opt19–24 相对提升百分比重跑后变化 | 极低 | +97% 和 +33% 远超测量噪声，结论方向不变；若不重跑，保留数字 + 降级脚注 |
| P1 数据标注 macOS AArch64 后需大幅重写叙事 | 中 | P1 叙事重心是"优化思路和方法论"而不是绝对数字，加注平台后保留原文，不需要重写 |
