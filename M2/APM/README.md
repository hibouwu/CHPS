# APM — 硬件加速器体系结构与编程

S3 · 公共课 · [M2 课程目录](../README.md) · [仓库首页](../../README.md)

教师课件讲解加速器架构、CUDA 编程与多 GPU；本年材料在 `TD1  APM/`、`TD2/`、`TP1/`，往年材料在 `TDTP2025/`。建议按三讲顺序阅读，做实验时核对材料标注的学年。

## 2026 年 10 月 22 日期中笔试复习

[复习资料入口与来源说明](Revision_Partiel/README.md) · [法语整理版](Revision_Partiel/APM_Revision_fr.md) · [中文整理版](Revision_Partiel/APM_Revision_zh.md)

[法语 PDF](Revision_Partiel/output/pdf/APM_Revision_fr.pdf) · [中文 PDF](Revision_Partiel/output/pdf/APM_Revision_zh.pdf)

两种语言采用相同章节、公式与题号，整理 CM1–CM3、本年 TD1/TD2/TP1、OpenMP Target 示例及往年拓展题，并附自测。课堂课表将 DST 安排在 10 月 22 日上午，优化 DGEMM 的 TP2 在当天下午；复习材料据此区分主线和拓展，但不把授课顺序当成老师明确公布的考点排除表。

## 教师课件

| 顺序 | 教师课件 | 原文提取稿 | 中文译稿 | 主要内容 |
|---|---|---|---|---|
| 1 | [APM_Cours1_en.pdf](CM/APM_Cours1_en.pdf) | [旧版原文](CM/APM_Cours1.md) | [第 1 讲中文](CM/APM_Cours1_zh.md) | 加速器架构与编程模型 |
| 2 | [APM_Cours2.pdf](CM/APM_Cours2.pdf) | [原文](CM/APM_Cours2.md) | [第 2 讲中文](CM/APM_Cours2_zh.md) | 进阶 CUDA、内存管理与异步执行 |
| 3 | [APM_Cours3.pdf](CM/APM_Cours3.pdf) | [原文](CM/APM_Cours3.md) | [第 3 讲中文](CM/APM_Cours3_zh.md) | CUDA API、上下文与多 GPU 编程 |

当前三份 PDF 分别为 96、98、101 页（2026-10-15 核对）。第 1 讲中文稿已于 2026-09-25 按新版增量同步，补入 Kepler warp 调度器说明；其原文提取稿仍对应 [93 页旧版归档](CM/Archive/APM_Cours1_2025.pdf)。第 2 讲提取稿和中文稿已注明 2026 年版本增量。

原文 Markdown 由 MinerU 提取，图片已下载到 `CM/Images/` 并改为本地链接。已修正部分明确的识别错误和误判的代码语言；由于课件含图、公式和逐步展示的代码，Markdown 尚不能代替逐页核对 PDF。

中文译稿翻译了原文中的英文、法文正文，并按阅读需要合并重复展示：去除独立的页角装饰图，保留完整架构图、对照图和关键步骤，为保留的图片添加中文图注。图片内文字与保留的代码块仍沿用原文，新增调度器图的标签在相邻正文中解释。原文提取稿正文和原有图片均保留；第 1 讲旧版 PDF 单独归档，新版用独立文件名保存。提取残缺和部分存疑表述在对应位置注明。译稿不代表对课件全部技术结论的独立核验。各讲开头保留其版本和整理说明。

架构拓展资料见 [NVIDIA GPU 参数与微架构](NVIDIA/README.md)：包含建议研究的代表型号、官方资料入口和型号记录模板。

## TD 与 TP

| 材料 | 内容与学年 |
|---|---|
| [TD1 原题](TD1%20%20APM/td1.pdf) · [解答](TD1%20%20APM/td1.md) | 2026–2027；索引、代码理解与 CPU 模拟，Q1–Q9。 |
| [TD2 原题](TD2/TD2/SUJET/td2.pdf) · [CPU 代码](TD2/TD2/CODE/pi.c) | 2026–2027；Monte Carlo 求 π，Q1–Q6。 |
| [TP1 原题](TP1/SUJET/tp1.pdf) · [法语解答](TP1/SUJET/tp1.md) · [中文解答](TP1/SUJET/tp1_zh.md) | 2026–2027；编译链与全局内存 DGEMM，Q1–Q12。历史 GPU 验证记录位于 TP1/RESULTS。 |
| [OpenMP Target 向量加法](cmexos/ompgpuecAdd.c) | 课堂示例，包含数据映射与执行设备检查。 |
| [旧 TD：CUDA 与 3D 距离函数](TDTP2025/TD/td2.pdf) | 2025–2026；与本年 Monte Carlo TD2 区别阅读。 |
| [旧 TP1 解答：矩阵乘法与共享内存](TDTP2025/TP/tp1_correction.pdf) | 2024–2025；不能直接套用本年题号。 |
| [旧 TP2 题目：Streams](TDTP2025/TP/tp2_sujet_2025-2026.pdf) | 2025–2026；从独立的 `s3/tp2/SUJET/tp2.pdf` 归档。 |
| [旧 TP2 解答：Streams](TDTP2025/TP/tp2_correction.pdf) | 2024–2025；与上面的题目学年不同。 |

第 1 讲新版主封面署名 Adrien Roussel，部分共用介绍页署名 Julien Jaeger、Patrick Carribault；第 2、3 讲保留原有版本。最初归档材料复制自本地 `待整理课件_IMMC_EDP_APM/APM/`，第 1 讲新版由用户后续提供；PDF 内容未改写。独立 TP2 题目归档时命名为 `tp2_sujet_2025-2026.pdf`，避免和解答混淆。现有材料不能证明覆盖 2026–2027 学年的全部课次。
