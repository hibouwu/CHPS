# APM — TP3：GPU Occupancy 与 Block Tiling

2026–2027 学年 · [返回 APM](../README.md)

本实验从共享内存 DGEMM 出发，计算驻留资源与理论 occupancy，再通过线程内复用减少共享内存读取。

| 材料 | 用途 |
|---|---|
| [ROMEO GH200 逐题中法实测解答](TP3/SUJET/tp3_romeo.md) | 推荐从这里阅读；Q1–Q17 对应 ROMEO 作业 817906 的真实数据 |
| [详细原理与本机对照](TP3/SUJET/tp3.md) | 较完整的概念说明及 RTX 5070 Laptop GPU 实测 |
| [教师原题 PDF](TP3/SUJET/tp3.pdf) | 4 页原始题目 |
| [完整解答程序](TP3/SOLUTION/dgemm_tp3.cu) | 资源查询、手算与 API 对照、原始 kernel、边界安全基线、每线程 4 个结果的优化 |
| [本机验证记录](TP3/RESULTS/local-2026-11-05/README.md) | 环境、正确性、sanitizer、性能与 SASS 证据 |
| [ROMEO 验证记录](TP3/RESULTS/romeo-817906/README.md) | GH200，`COMPLETED / 0:0`；含 2048/4096 阶三批计时、源快照、二进制与哈希核对 |
| [5 与 6 blocks/SM 对照实测](TP3/RESULTS/romeo-818095/README.md) | 作业 818095 完成；默认 42 寄存器为 5 块/62.5%，限制到 40 后为 6 块/75%，附正确性与计时 |
| [按课堂讲解复测 2 blocks/SM、100%](TP3/RESULTS/romeo-818143/README.md) | 作业 818143 完成；原始 1024 线程 kernel 的一维、二维布局均为 2 块/100%，区别于 256 线程优化版 |
| [复现脚本](TP3/SOLUTION/validate.py) | 编译、9 组尺寸检查、3 批计时、sanitizer、按 kernel 提取 SASS |
| [教师代码](TP3/CODE/dgemm-shared.cu) · [教师分析脚本](TP3/CODE/parse_sass.sh) | 原样保留；代码中的边界、动态共享内存和释放问题见解答 |

建议先读 Q1–Q13，弄清“资源允许多少 warp 驻留”，再读 Q14–Q17，分析数据复用怎样影响计算。这里计算的是理论 occupancy；它与 GPU 利用率、实际测得的平均 occupancy、运行时间是不同指标。

追加的作业 **818095** 在 `romeo-a043` 核对了“6 个 block”的条件：相同优化源码增加 `--maxrregcount=40` 后，实际使用 40 寄存器/thread，CUDA API 返回 **6 blocks/SM、75%**。默认版仍为 **5 blocks/SM、62.5%**。40 寄存器版在 2048 阶更快，在 4096 阶稍慢，因此保留默认编译方式，详见[对照记录](TP3/RESULTS/romeo-818095/README.md)。

在 CUDA 与宿主编译器匹配的机器上，可在 `TP3/SOLUTION/` 中执行：

```bash
make ARCH=sm_90   # 例：GH200；换成实际设备支持的架构
./dgemm_tp3.exe 256
./dgemm_tp3.exe 63 65 37 7
```

本机 RTX 5070 Laptop GPU 使用 `sm_120`。CUDA 13.0 的 `nvcc` 拒绝本机 GCC 16，已用 Clang 完成验证；完整命令和编译警告保存在本机记录中。

ROMEO 已使用 nvcc 12.9.41、`sm_90` 在 `romeo-a052` 完成验证，作业 **817906**。教师 kernel 的理论 occupancy 为 **100%**；安全基线为 **50%**，每线程 4 个结果的优化版为 **62.5%**。4096 阶三批中，优化版相对安全基线快 **2.337–2.352 倍**，相对教师 kernel（去掉多余动态申请）快 **1.705–1.721 倍**。这些是不同编译版本的指标，不应把本机的 66.67% 套用于 ROMEO。提交方式见 [ROMEO 记录](TP3/RESULTS/romeo-817906/README.md)，脚本为 [run_romeo.sh](TP3/SOLUTION/run_romeo.sh)。尚未执行 Ruche 测试。
