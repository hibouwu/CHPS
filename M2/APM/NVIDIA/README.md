# NVIDIA GPU 参数与微架构

[返回 APM](../README.md) · [型号记录模板](型号记录模板.md)

用于学习 CUDA、分析 kernel 性能和对照 APM 课件。先选择代表型号，沿着“硬件资源 → 指令与执行方式 → 数据搬运 → kernel 实现”的顺序整理。这里的优先级是学习建议，不是采购建议。

## 建议关注的型号

| 优先级 | 代表型号 | 架构 / 计算能力 | 建议研究的问题 |
|---|---|---|---|
| 主线 1 | A100 | Ampere / 8.0 | 从 SM、寄存器、shared memory、HBM 建立资源模型；理解异步复制、Tensor Core 与 GEMM 分块之间的联系。 |
| 主线 2 | H100 | Hopper / 9.0 | 研究 TMA、线程块集群、分布式共享内存及 WGMMA；解释流水线和生产者／消费者分工怎样变化。 |
| 主线 3 | B200 | Blackwell / 10.0 | 研究 Tensor Memory、第五代 Tensor Core 与新的矩阵运算路径；与 H100 的实现作对照。 |
| 后续扩展 | B300 | Blackwell Ultra / 10.3 | 在 B200 的记录上建立差异表，分别核对指令支持、存储配置与产品规格。 |
| 消费级对照 | RTX 4090；需要时补 RTX 5090 | Ada / 8.9；Blackwell / 12.0 | 比较消费级与数据中心产品；验证同属某代架构时，指令和资源是否仍有差别。若手边有其中一张，优先做可复现的实验。 |
| 按项目需要深入 | Jetson Thor（T5000 / T4000） | Blackwell / 11.0 | 单独记录 SoC、系统内存与功耗模式；核对 SM110 的目标指令和工具链支持，不直接套用 B200 的结论。 |
| 历史背景 | V100，以及课件中的 Kepler、Fermi | Volta 及更早架构 | 了解 Tensor Core、线程调度和内存体系的演进；按课件需要补充，不必先为每一代建立完整参数表。 |

计算能力按 [NVIDIA 官方 GPU 列表](https://developer.nvidia.com/cuda/gpus)核对。数字用于区分硬件能力，不能作为性能排名。核对日期：2026-09-25。

主线的选取依据是编程模型与数据搬运方式的变化，可先阅读 [Ampere Tuning Guide](https://docs.nvidia.com/cuda/ampere-tuning-guide/index.html)、[Hopper Tuning Guide](https://docs.nvidia.com/cuda/hopper-tuning-guide/index.html)和 [Blackwell Tuning Guide](https://docs.nvidia.com/cuda/blackwell-tuning-guide/index.html)。

## 每个型号要整理什么

1. **准确的产品版本。** 区分 PCIe、SXM、显存容量及功耗配置。GPU 芯片的设计上限和销售产品实际启用的资源分别记录。
2. **SM 内部结构。** warp 调度、执行单元、寄存器容量、驻留线程／warp／block 上限，以及这些资源对 occupancy 的约束。
3. **存储层次。** 寄存器、shared memory、L1、L2、显存容量和带宽；同时标明参数是每个 SM 还是整张 GPU 的数值。
4. **计算路径。** CUDA Core 与 Tensor Core 分开记录；列出数据类型、累加精度、指令族和适用的计算能力。
5. **搬运与同步。** global → shared 的复制机制、barrier、TMA、cluster 等能力怎样影响分块和流水线。
6. **性能口径。** 理论峰值、官方应用测试、自己测得的延迟／吞吐分开列；峰值注明稠密或稀疏、数据类型、频率和计数方式。
7. **最小实验。** 用访存、共享内存、计算吞吐或 GEMM 实验验证一个具体判断，保留硬件与工具链信息。

## GPU 与整机分开记录

H100 是 GPU 产品；GH200 是 Grace CPU 与 Hopper GPU 组合的平台；NVL72 还涉及系统规模与互联拓扑。研究单 GPU kernel 时先整理 GPU 与 SM；研究多 GPU 时，再增加 CPU、NUMA、PCIe、NVLink、NVSwitch 和节点间网络的资料。平台级背景可从 [Grace Hopper 官方介绍](https://developer.nvidia.com/blog/nvidia-grace-hopper-superchip-architecture-in-depth/)开始。

## 文件约定与来源

- 每个型号使用一个 Markdown 文件，如 `A100.md`、`H100.md`；确有数据后再创建，避免堆积空文件。
- 图片集中放在 `Images/`，使用 `a100_sm_01.png` 等带型号与主题的名称，并在图片旁标来源链接。
- 优先引用官方架构白皮书、产品数据表、CUDA 调优指南和 PTX 文档。微基准论文与自行推断另作标记。
- 同一架构不同产品的差异、未公开的信息和待实测项明确写出；不用另一型号的参数填补空白。

当前目录提供研究范围和模板，尚未填写各型号的完整规格表，也未在上述 GPU 上执行本目录的实验。
