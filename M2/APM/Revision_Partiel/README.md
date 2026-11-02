# APM 期中笔试复习资料

2026 年 10 月 22 日上午 DST。先复习考试前的 CM1-CM3、TD1、TD2 和 TP1；往年优化练习用于拓展。课表没有说明考试范围、时长、题型和能否携带资料。

| 用途 | 法语 | 中文 |
|---|---|---|
| 阅读与搜索 | [法语复习讲义](APM_Revision_fr.md) | [中文复习讲义](APM_Revision_zh.md) |
| 打印（含目录与页码） | [法语 PDF](output/pdf/APM_Revision_fr.pdf) | [中文 PDF](output/pdf/APM_Revision_zh.pdf) |

两版章节编号、原题号、代码和公式相同；小节标题后标有对应的课件页码。

**法中对照练习：**[100 道 QCM 与解析](APM_QCM_100_fr_zh.md) · [100 道课程问答与参考答案](APM_Questions_Cours_100_fr_zh.md)。每套标出 60 道核心题，优先覆盖执行模型、内存、同步和本学期 TD/TP 基础。QCM 每题四选一，答案与法中解析紧跟在本题选项下方；问答题按法语问题、中文译文、法语答案、中文答案逐段排列。均为自编复习题，不是官方试卷或押题保证；本套未纳入尚未讲授的 NCCL，也不要求编写完整程序。

**2025-2026 年真题：**[法中逐段对照：题目与解析](../Examen/APM_CC1_2025.md)。建议读完第 2 章后，用真题练习 stream/event 依赖（Q6）、指针偏移与异步安全判断（Q7-Q10）和共享内存两阶段归约（Q11）。

## 内容

| 章节 | 内容 |
|---|---|
| 0 | 课表、复习主线、资料对照与阅读顺序 |
| 1 | 加速器、GPU 架构、编程模型、CUDA 执行层次、索引与程序生命周期 |
| 2 | CUDA 内存、pitch、warp、合并访存、共享内存、同步、streams 与 events |
| 3 | Runtime/Driver API、context、多 GPU、P2P、统一内存、NCCL/MPI、OpenMP Target |
| 4 | TD1 Q1-Q9、TD2 Q1-Q6、TP1 Q1-Q12；往年 DGEMM、SDF、Streams 拓展 |
| 5 | 10 道自测、答案、公式速查、法语作答句式 |

10 月 22 日下午的 TP2 才开始 DGEMM 优化，11 月 5 日的 TP3 涉及占用率与 1D Tiling，所以旧题里的完整优化实现放在拓展部分；CM2 讲过的内存层次、合并访存和共享内存概念仍在主线。

章节源文件在 `sections/`，修改后执行 `python3 tools/build_documents.py` 重新生成两份讲义和 PDF（加 `--markdown-only` 只生成 Markdown）。

[返回 APM 课程目录](../README.md)
