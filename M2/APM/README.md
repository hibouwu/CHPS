# APM — 硬件加速器体系结构与编程

S3 · 公共课 · [M2 课程目录](../README.md) · [仓库首页](../../README.md)

加速器架构、CUDA 编程与多 GPU。本年材料在 `TD1  APM/`、`TD2/`、`TP1/`、`tp3/`、`uvsq-tp-note-2026/`，往年材料在 `TDTP2025/`。

**本节计分实验：Floyd–Warshall sur GPU**（`uvsq-tp-note-2026`）· [中文题目](uvsq-tp-note-2026/SUJET/tpnote_zh.md) · [法语题目](uvsq-tp-note-2026/SUJET/tpnote.md) · [原题 PDF](uvsq-tp-note-2026/SUJET/tpnote.pdf)。时长 3 小时，Q1–Q10；两份 Markdown 保持题号、公式及命令对应，未填写答案。

TP3 资料：[GPU Occupancy 与 Block Tiling](tp3/README.md)，含 [ROMEO GH200 的 Q1–Q17 中法实测解答](tp3/TP3/SUJET/tp3_romeo.md)、完整 CUDA 程序及本机对照；ROMEO 作业 817906 已完成。

补充实测：[5 与 6 blocks/SM 的编译配置对照](tp3/TP3/RESULTS/romeo-818095/README.md)，作业 818095 已完成；限制到 40 寄存器后可达到 6 blocks/SM、75% 理论 occupancy。

[按课堂讲解复测](tp3/TP3/RESULTS/romeo-818143/README.md)：原始 1024 线程 kernel 在一维和二维布局下均为 **2 blocks/SM、100% 理论 occupancy**，作业 818143 已完成。

## 2026 年 10 月 22 日期中笔试复习

[复习资料入口](Revision_Partiel/README.md) · [法语讲义](Revision_Partiel/APM_Revision_fr.md) · [中文讲义](Revision_Partiel/APM_Revision_zh.md) · [法语 PDF](Revision_Partiel/output/pdf/APM_Revision_fr.pdf) · [中文 PDF](Revision_Partiel/output/pdf/APM_Revision_zh.pdf)

整理 CM1–CM3、本年 TD1/TD2/TP1、OpenMP Target 示例及往年拓展题，并附自测。两种语言章节、公式与题号相同。

**2025-2026 年真题：**[法中逐段对照：题目与解析](Examen/APM_CC1_2025.md) · [双语 PDF](Examen/output/pdf/APM_CC1_2025.pdf)

## 教师课件

| 顺序 | 教师课件 | 中英/法对照稿 | 原文提取稿 | 主要内容 |
|---|---|---|---|---|
| 1 | [APM_Cours1_en.pdf](CM/APM_Cours1_en.pdf) | [第 1 讲对照](CM/APM_Cours1_zh_part1.md) | [原文](CM/APM_Cours1.md)（93 页旧版） | 加速器架构与编程模型 |
| 2 | [APM_Cours2.pdf](CM/APM_Cours2.pdf) | [第 2 讲对照 · part1](CM/APM_Cours2_zh_part1.md) / [part2](CM/APM_Cours2_zh_part2.md) | [原文](CM/APM_Cours2.md) | 进阶 CUDA、内存管理与异步执行 |
| 3 | [APM_Cours3.pdf](CM/APM_Cours3.pdf) | [第 3 讲对照 · part1](CM/APM_Cours3_zh_part1.md) / [part2](CM/APM_Cours3_zh_part2.md) | [原文](CM/APM_Cours3.md) | CUDA API、上下文与多 GPU 编程 |

对照稿逐页先列课件原文（英文或法文，引用块排版），再给中文翻译和课堂讲解；逐步展示的重复页已合并，代码只保留一份。三份 PDF 分别为 96、98、101 页。第 1 讲的原文提取稿对应 [93 页旧版](CM/Archive/APM_Cours1_2025.pdf)，新版新增的几页在对照稿里只有中文。课件代码以 PDF 为准。

架构拓展资料见 [NVIDIA GPU 参数与微架构](NVIDIA/README.md)。

## TD 与 TP

| 材料 | 内容与学年 |
|---|---|
| [计分 TP 原题](uvsq-tp-note-2026/SUJET/tpnote.pdf) · [中文题目](uvsq-tp-note-2026/SUJET/tpnote_zh.md) · [法语题目](uvsq-tp-note-2026/SUJET/tpnote.md) · [原始答题文件](uvsq-tp-note-2026/CODE/REPONSES.md) | 2026–2027；Floyd–Warshall、CPU/GPU 验证与计时、合并访存及共享内存分块；Q1–Q10，3 小时 |
| [TD1 原题](TD1%20%20APM/td1.pdf) · [中法对照解答](TD1%20%20APM/td1.md) | 2026–2027；索引、代码理解与 CPU 模拟，Q1–Q9 |
| [TD2 原题](TD2/TD2/SUJET/td2.pdf) · [中法对照解答](TD2/TD2/SUJET/td2.md) · [CPU 代码](TD2/TD2/CODE/pi.c) | 2026–2027；Monte Carlo 求 π，Q1–Q6 |
| [TP1 原题](TP1/SUJET/tp1.pdf) · [中法对照解答](TP1/SUJET/tp1_zh.md) · [法语版](TP1/SUJET/tp1.md) | 2026–2027；编译链与全局内存 DGEMM，Q1–Q12；实测记录在 TP1/RESULTS |
| [TP3 入口](tp3/README.md) · [原题](tp3/TP3/SUJET/tp3.pdf) · [ROMEO 实测解答](tp3/TP3/SUJET/tp3_romeo.md) · [原理与本机对照](tp3/TP3/SUJET/tp3.md) · [ROMEO 验证记录](tp3/TP3/RESULTS/romeo-817906/README.md) | 2026–2027；occupancy、SASS 静态分析与线程内复用，Q1–Q17；GH200 作业 817906 完成 |
| [OpenMP Target 向量加法](cmexos/ompgpuecAdd.c) | 课堂示例：数据映射与执行设备检查 |
| [旧 TD：CUDA 与 3D 距离函数](TDTP2025/TD/td2.pdf) · [中法对照解答](TDTP2025/TD/td2.md) | 2025–2026 计分 TD，Q1–Q7；与本年 Monte Carlo TD2 不同 |
| [旧 TP1 教师解答：矩阵乘法与共享内存](TDTP2025/TP/tp1_correction.pdf) · [中法对照](TDTP2025/TP/tp1_correction.md) | 2024–2025，Q1–Q21；题号与本年不同，Q13–Q21 对应 TP2 的优化内容 |
| [旧 TP2 题目：Streams](TDTP2025/TP/tp2_sujet_2025-2026.pdf) · [教师解答](TDTP2025/TP/tp2_correction.pdf) · [中法对照](TDTP2025/TP/tp2.md) | 题目 2025–2026、解答 2024–2025，题目逐字相同，Q1–Q15 |
