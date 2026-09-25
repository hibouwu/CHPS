# EDP — 性能评估（Évaluation de performances）

S3 · 公共课 · [M2 课程目录](../README.md) · [仓库首页](../../README.md)

这门课讨论如何选择性能指标和工作负载，再通过数学建模、仿真与实测评估系统。建议先按下表读教师课件，遇到概念卡点时再对照中文笔记；做题时以原始 TD 为准。

## 按课程顺序阅读

| 顺序 | 教师课件 | 主要内容 | 对照材料 |
|---|---|---|---|
| 1 | [1_edpCpl.pdf（今年 62 页）](CM/1_edpCpl.pdf) · [旧版 Markdown](CM/1_edpCpl.md) | 课程介绍、性能评估的基本概念和 HPC 背景 | [中文笔记 1（已同步 HPC 部分）](Notes/edpcm1.md) · [第一课 Annex](Notes/edpcm1_annex.md) · [原笔记 PDF](Notes/edpcm1.pdf)、[TD1：性能指标与 Amdahl 定律](TD/td1_metrics.pdf)（[法文](TD/td1_metrics.md) · [中文](TD/td1_metrics_zh.md)） |
| 2 | [2_edp.pdf](CM/2_edp.pdf) · [Markdown](CM/2_edp.md) | 工作负载的选择、刻画，以及真实与合成工作负载 | [中文笔记 2](Notes/edpcm2.pdf)（[Markdown](Notes/edpcm2.md)）、[工作负载论文](<References/2020-HPC-workload-char-SNTA-Bang (1).pdf>) |
| 3 | [3_edp.pdf](CM/3_edp.pdf) · [Markdown](CM/3_edp.md) | 排队模型、建模过程和 Markov 链 | [中文笔记 3](Notes/ed充满.pdf)（[Markdown](Notes/ed充满.md)）、[TD3：数学建模](TD/TD3_new.pdf) |
| 4–5 | [45_edp.pdf](CM/45_edp.pdf) · [Markdown](CM/45_edp.md) | 离散事件与 Monte Carlo 仿真、测量及测量质量 | [中文笔记 4](Notes/edp4cm.pdf)（[Markdown](Notes/edp4cm.md)）、[TD4：仿真与测量](TD/td4.pdf) |

此外有 [TP：用 fio 测量 I/O 性能](TP/TP_Evaluation_de_performances_2.pdf) 和 [专题论文](References/README.md)。TP 文件写明适用于 **2025–2026 学年**；其中的提交日期和作业要求属于该学年，当前是否沿用须以教师的新通知为准。

## 材料说明

同名 Markdown 在 MinerU 提取结果上完成了本轮内容审校和格式整理。图片已保存在对应目录的 `Images/` 中，文档使用本地相对链接；原始 PDF 保持不变。涉及原资料错误或适用条件的修改标为“校注”，具体范围、主要修正及验证结果见[审校说明](审校说明.md)。

- 第一课中文笔记第 1–18 节保留原正文，第 19–26 节已按今年课件第 42–62 页重组；原第 19–35 节的扩展与预习材料另收于 annex。`CM/1_edpCpl.md` 仍对应先前的 41 页版，尚未同步新增页；第一课请优先对照当前教师 PDF 与中文正文。
- `CM/` 的四份 PDF 是 Soraya Zertal 的法文教师课件；`45_edp.pdf` 本身合并了第 4、5 部分，不拆成两份。
- `TD/` 现有 TD1、TD3、TD4；原始目录没有 TD2，不能据此认定课程没有 TD2。
- `Notes/` 的四份中文 PDF 来自原目录 `打印/`，作为对照笔记使用。其中 [demo.tex](Notes/demo.tex) 是中文题目与解答原稿，作者和正确性尚未核对，不作为教师标准答案。
- `References/` 收录一篇工作负载论文，以及原目录 `articles_edp_25/` 中编号 02–14 的 13 篇论文；编号 01 不在现有来源中。

资料复制自本地待整理目录 `待整理课件_IMMC_EDP_APM/EDP/s3/edp/`，保留了原文件名和原始目录；本目录按用途提供阅读入口。现有材料并不证明已覆盖 2026–2027 学年的全部课次。
