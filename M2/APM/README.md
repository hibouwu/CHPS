# APM — 硬件加速器体系结构与编程

S3 · 公共课 · [M2 课程目录](../README.md) · [仓库首页](../../README.md)

教师课件讲解加速器架构、CUDA 编程与多 GPU；习题和实验材料按用途放在 `TD/`、`TP/`。建议按三讲顺序阅读，做实验时核对材料标注的学年。

## 教师课件

| 顺序 | 教师课件 | 原文提取稿 | 中文译稿 | 主要内容 |
|---|---|---|---|---|
| 1 | [APM_Cours1_en.pdf](CM/APM_Cours1_en.pdf) | [旧版原文](CM/APM_Cours1.md) | [第 1 讲中文](CM/APM_Cours1_zh.md) | 加速器架构与编程模型 |
| 2 | [APM_Cours2.pdf](CM/APM_Cours2.pdf) | [原文](CM/APM_Cours2.md) | [第 2 讲中文](CM/APM_Cours2_zh.md) | 进阶 CUDA、内存管理与异步执行 |
| 3 | [APM_Cours3.pdf](CM/APM_Cours3.pdf) | [原文](CM/APM_Cours3.md) | [第 3 讲中文](CM/APM_Cours3_zh.md) | CUDA API、上下文与多 GPU 编程 |

当前三份 PDF 分别为 96、97、101 页。第 1 讲中文稿已于 2026-09-25 按新版增量同步，补入 Kepler warp 调度器说明；其原文提取稿仍对应 [93 页旧版归档](CM/Archive/APM_Cours1_2025.pdf)。

原文 Markdown 由 MinerU 提取，图片已下载到 `CM/Images/` 并改为本地链接。已修正部分明确的识别错误和误判的代码语言；由于课件含图、公式和逐步展示的代码，Markdown 尚不能代替逐页核对 PDF。

中文译稿翻译了原文中的英文、法文正文，并按阅读需要合并重复展示：去除独立的页角装饰图，保留完整架构图、对照图和关键步骤，为保留的图片添加中文图注。图片内文字与保留的代码块仍沿用原文，新增调度器图的标签在相邻正文中解释。原文提取稿正文和原有图片均保留；第 1 讲旧版 PDF 单独归档，新版用独立文件名保存。提取残缺和部分存疑表述在对应位置注明。译稿不代表对课件全部技术结论的独立核验。具体取舍见[中文讲义整理说明](CM/APM_中文讲义整理说明.md)。

架构拓展资料见 [NVIDIA GPU 参数与微架构](NVIDIA/README.md)：包含建议研究的代表型号、官方资料入口和型号记录模板。

## TD 与 TP

| 材料 | 内容与学年 |
|---|---|
| [TD：CUDA 入门与 3D 距离函数可视化](TD/td2.pdf) | 标注 APM 2025–2026；来源文件名为 `td2.pdf`。 |
| [TP1 解答：矩阵乘法与共享内存](TP/tp1_correction.pdf) | 标注 APM 2024–2025；本批材料未找到对应题目。 |
| [TP2 题目：CUDA Streams 与异步传输](TP/tp2_sujet_2025-2026.pdf) | 标注 APM 2025–2026；从独立的 `s3/tp2/SUJET/tp2.pdf` 归档。 |
| [TP2 解答：CUDA Streams](TP/tp2_correction.pdf) | 标注 APM 2024–2025；与上面的题目学年不同，不视为逐题配套答案。 |

第 1 讲新版主封面署名 Adrien Roussel，部分共用介绍页署名 Julien Jaeger、Patrick Carribault；第 2、3 讲保留原有版本。最初归档材料复制自本地 `待整理课件_IMMC_EDP_APM/APM/`，第 1 讲新版由用户后续提供；PDF 内容未改写。独立 TP2 题目归档时命名为 `tp2_sujet_2025-2026.pdf`，避免和解答混淆。现有材料不能证明覆盖 2026–2027 学年的全部课次。
