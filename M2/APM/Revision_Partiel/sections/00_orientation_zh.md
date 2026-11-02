## 0 复习范围与材料导航

### 0.1 先明确考试前已经安排了什么

课表写明：**2026 年 10 月 22 日上午为 DST 笔试**。考试前的课程与练习如下。课表没有说明考试范围、时长、题型和能否携带资料。

| 日期 | 上午 | 下午 |
|---|---|---|
| 2026-09-25 | CM1：GPU 架构与第一个 CUDA 程序 | TD1：网格与 CUDA 代码理解 |
| 2026-09-29 | CM2：内存层次与 CUDA API | TD2：多线程 Monte Carlo 求 π |
| 2026-10-09 | CM3：Driver API、多 GPU、OpenMP Target | TP1：DGEMM |
| 2026-10-22 | DST 笔试 | TP2：优化 DGEMM，合并访存与共享内存 |
| 2026-11-05 | TP3：GPU 占用率计算与 1D Tiling；计分 TP | 课表未进一步细分 |

**复习主线：**先掌握 CM1-CM3 的概念和程序执行过程，再独立完成本年 TD1 Q1-Q9、TD2 Q1-Q6、TP1 Q1-Q12。CM3 的 OpenMP Target 以课表示意和现有课堂示例补充。

**拓展练习：**往年共享内存 DGEMM、Streams 和 3D 距离函数题，适合训练相同的 CUDA 方法。优化 DGEMM 与占用率专项 TP 排在笔试之后，因此不应优先背诵旧题中的完整优化实现。但 CM2 已涉及的共享内存、合并访存、warp 和占用率概念仍属于已安排的课程内容。

课表照片见[课堂安排原图](Images/calendrier_cours_2026.jpg)。第 1-3 章整理课程，第 4 章按原题号整理练习，第 5 章用于闭卷自测。法语与中文版本使用相同编号；代码、变量名、公式和数值保持对应。

### 0.2 有用资料与本书对应位置

| 材料 | 版本与用途 | 对应位置 |
|---|---|---|
| [CM1 原课件](../CM/APM_Cours1_en.pdf) | 96 页新版，含 Kepler 调度器补充 | 第 1 章 |
| [CM1 中文讲义](../CM/APM_Cours1_zh_part1.md) | 含课堂讲解；原文提取稿对应 93 页旧版 | 第 1 章 |
| [CM2 原课件](../CM/APM_Cours2.pdf)及[中文讲义 · part1](../CM/APM_Cours2_zh_part1.md) / [part2](../CM/APM_Cours2_zh_part2.md) | 当前 PDF 为 98 页，含 warp 编号与事件计时内容 | 第 2 章 |
| [CM3 原课件](../CM/APM_Cours3.pdf)及[中文讲义 · part1](../CM/APM_Cours3_zh_part1.md) / [part2](../CM/APM_Cours3_zh_part2.md) | 101 页；部分 API 叙述有历史限定 | 第 3 章 |
| [TD1 原题](../TD1%20%20APM/td1.pdf)及[中法对照解答](../TD1%20%20APM/td1.md) | 2026-2027，Q1-Q9 | 第 4 章现年练习 |
| [TD2 原题](../TD2/TD2/SUJET/td2.pdf)、[中法对照解答](../TD2/TD2/SUJET/td2.md)及[CPU 代码](../TD2/TD2/CODE/pi.c) | 2026-2027，Monte Carlo，Q1-Q6 | 第 4 章现年练习 |
| [TP1 原题](../TP1/SUJET/tp1.pdf)、[中法对照解答](../TP1/SUJET/tp1_zh.md)、[法语版](../TP1/SUJET/tp1.md) | 2026-2027，编译与全局内存 DGEMM，Q1-Q12 | 第 4 章现年练习 |
| [OpenMP Target 示例](../cmexos/ompgpuecAdd.c) | 向量加法、map、设备执行位置检查 | 第 3 章 OpenMP Target |
| [旧 TP1 解答](../TDTP2025/TP/tp1_correction.pdf)及[中法对照](../TDTP2025/TP/tp1_correction.md) | 页眉为 2024-2025，含共享内存优化 | 第 4 章拓展练习 |
| [旧 TP2 题目](../TDTP2025/TP/tp2_sujet_2025-2026.pdf)、[旧解答](../TDTP2025/TP/tp2_correction.pdf)及[中法对照](../TDTP2025/TP/tp2.md) | 题目为 2025-2026，解答为 2024-2025，题目文字相同 | 第 4 章 Streams 拓展 |
| [旧 TD 题目](../TDTP2025/TD/td2.pdf)及[中法对照](../TDTP2025/TD/td2.md) | 2025-2026，3D 距离函数，区别于本年的 Monte Carlo TD2 | 第 4 章 SDF 拓展 |

### 0.3 怎样使用两种语言的版本

第一遍用中文理解执行过程，遇到术语再对照法语。第二遍直接读法语题意，在纸上写出公式、索引与数据流，然后检查题后答案。最后用第 5 章的自测检查能否说明“为什么”，而不只是记住函数名。

写 CUDA 答案时，依次回答五件事：每个线程负责什么；如何由块和线程坐标得到数据索引；哪些数据放在 CPU/GPU；哪些操作之间必须先后完成；怎样判断结果正确与时间测量范围。题目给出矩阵存储方式、线程数或硬件参数时，先采用题目条件，不能把某代 GPU 的示例数值当成通用常数。
