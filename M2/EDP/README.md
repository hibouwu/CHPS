# EDP — 性能评估（Évaluation de performances）

S3 · 公共课 · [M2 课程目录](../README.md) · [仓库首页](../../README.md)

这门课讨论如何选择性能指标和工作负载，再通过数学建模、仿真与实测评估系统。建议先按下表读教师课件，遇到概念卡点时再对照中文笔记；做题时以原始 TD 为准。

## 按课程顺序阅读

| 顺序 | 教师课件 | 主要内容 | 对照材料 |
|---|---|---|---|
| 1 | [1_edpCpl.pdf（今年 62 页）](CM/1_edpCpl.pdf) · [旧版 Markdown](CM/1_edpCpl.md) | 课程介绍、性能评估的基本概念和 HPC 背景 | [中文笔记 1（已同步 HPC 部分）](CM/1_edpCpl_zh.md) · [第一课 Annex](CM/1_edpCpl_zh_annex.md) · [TD1：性能指标与 Amdahl 定律](TD/td1_metrics.pdf)（[法文](TD/td1_metrics.md) · [中文](TD/td1_metrics_zh.md)） |
| 2 | [2_edp.pdf（59 页）](CM/2_edp.pdf) · [法语 Markdown](CM/2_edp.md) | 工作负载的选择、刻画，以及真实与合成工作负载 | [中文笔记 2](CM/2_edp_zh.md)、[工作负载论文](<References/2020-HPC-workload-char-SNTA-Bang (1).pdf>) |
| 3 | [3_edp.pdf（51 页）](CM/3_edp.pdf) · [法语 Markdown](CM/3_edp.md) | 排队模型、建模过程和 Markov 链 | [中文笔记 3](CM/3_edp_zh.md)、[TD3：数学建模](TD/TD3_2627.pdf)（[法语](TD/TD3_2627.md) · [中文](TD/TD3_2627_zh.md)） |
| 4–5 | [45_edp.pdf（合并校订版，45 页）](CM/45_edp.pdf) · [Markdown](CM/45_edp.md) | 离散事件与 Monte Carlo 仿真、测量及测量质量 | [中文笔记 4](CM/45_edp_zh.md)、[TD4：仿真与测量](TD/td4.pdf)（[法语](TD/td4.md) · [中文](TD/td4_zh.md)） |

此外有 TP：用 fio 测量 I/O 性能（当前目录未包含该文件） 和 [专题论文](References/README.md)。TP 文件写明适用于 **2025–2026 学年**；其中的提交日期和作业要求属于该学年，当前是否沿用须以教师的新通知为准。

## 材料说明

同名 Markdown 在 MinerU 提取结果上完成了本轮内容审校和格式整理。图片已保存在对应目录的 `Images/` 中，文档使用本地相对链接；教师原始 PDF 保留，第四课的主 PDF 另按下述规则更新为合并校订阅读版。涉及原资料错误或适用条件的修改标为“校注”，具体范围、主要修正及验证结果见[审校说明](审校说明.md)。

- 第一课中文笔记第 1–18 节保留原正文，第 19–26 节已按今年课件第 42–62 页重组；原第 19–35 节的扩展与预习材料另收于 annex。`CM/1_edpCpl.md` 仍对应先前的 41 页版，尚未同步新增页；第一课请优先对照当前教师 PDF 与中文正文。
- 第三课中法文 Markdown 已于 2026-10-08 按新版 51 页 PDF 同步，含当前课件图示、Jackson 流量推导和 M/M/C 统一记号；文末可查页码对照。
- 第二课中法文 Markdown 已于 2026-09-30 按当前 59 页 PDF 核对，包含箱线图、k-means 图例及文末页码对照。
- 第四课已于 2026-11-02 同步：[主 PDF（45 页）](CM/45_edp.pdf) 以 [2026 年教师原版（43 页）](<CM + TD EDP/45_edp.pdf>) 为基础，插回旧版第 20–21 页的模拟器介绍，并校订 F 检验文字、α／置信水平、平均时间表述与末页实验设计。它是编辑后的阅读版，不是教师原件；[2020 年旧版备份](CM/Archives/45_edp_2020.pdf) 与新版原件均保留。中法文 Markdown 已同步，文末提供页码对照。
- `CM/` 的前三份 PDF 是 Soraya Zertal 的法文教师原件；第四份主 PDF 为上述合并校订版，仍合并第 4、5 部分，不拆成两份。
- `TD/` 现有 TD1、TD3、TD4；原始目录没有 TD2，不能据此认定课程没有 TD2。
- `CM/` 中带 `_zh` 后缀的 Markdown 是中文讲义，中文原始 PDF 已从本课程目录移除，中文材料以 Markdown 为阅读入口。第一课扩展内容单列为 `1_edpCpl_zh_annex.md`。`Notes/` 中的 [demo.tex](Notes/demo.tex) 是中文题目与解答原稿，作者和正确性尚未核对，不作为教师标准答案。
- `References/` 收录一篇工作负载论文，以及原目录 `articles_edp_25/` 中编号 02–14 的 13 篇论文；编号 01 不在现有来源中。

资料复制自本地待整理目录 `待整理课件_IMMC_EDP_APM/EDP/s3/edp/`，来源目录保持原样；本目录按用途整理，中文讲义按对应法语课件的主文件名加 `_zh` 命名并放在同一目录。现有材料并不证明已覆盖 2026–2027 学年的全部课次。


## TD4 统计查表

TD4 已补全五题逐步解答：[中文题解](TD/td4_zh.md) · [法语题解](TD/td4.md) · [可复现计算脚本](TD/td4_calculs.py)（NumPy、SciPy；运行 `python TD/td4_calculs.py`）。第 4 题包含每次重新估计指数分布参数的模拟校准；第 5 题区分课堂连续双侧查表近似与离散精确检验，两者在 1% 水平的结论不同。

资料保留在 [CM + TD EDP](<CM + TD EDP/>) 中；其中 [TD4 副本](<CM + TD EDP/td4.pdf>) 与 [现有 TD4](TD/td4.pdf) 的 SHA-256 一致，无题目更新。

- [Student t 临界值表](<CM + TD EDP/Table-t-Student.jpg>)：第 1 题的小样本均值置信区间；双侧置信水平 $1-\alpha$ 应查单侧尾概率 $\alpha/2$ 一列，或表中双侧 $\alpha$ 一列。
- [χ² 临界值表](<CM + TD EDP/tableCHI-DEUX.pdf>)：第 2、3 题及第 5 题的卡方检验；表头 $p$ 为右尾概率，对应显著性水平 $\alpha$。
- [Kolmogorov–Smirnov 临界值表](<CM + TD EDP/KolmoSmir_table.png>)：供第 4、5 题查阅。该图给出未乘 $\sqrt n$ 的双侧统计量 $D_n$ 临界值；TD 的 $K^+$、$K^-$ 含 $\sqrt n$，比较 $\max(K^+,K^-)$ 时，表中临界值也须乘 $\sqrt n$，不能直接混用缩放。题中估计参数／离散样本的限制见 [TD4 校注](TD/td4_zh.md)。

## 历年试题

[历年试题索引](anales/README.md)收录 **2023-11-14** 和 **2025-11-14** 两套试卷，每套均提供法语原题转录、中文译文和两页原始照片，不含解答。图片已按考试日期与页码命名；考试规则仅对应各自历史试卷。
