# CoderUJB 复现工作区

[返回 EDP 课程目录](../README.md)

整理日期：2026-11-03；实验状态更新：2026-11-05。已完成论文归档、官方资源核对，以及 ROMEO 上 CodeLlama-13B 的 BF16 加载和一次代码生成探测；尚未编译生成代码或运行 Defects4J 评测。

## 中英对照阅读入口

[论文中英对照 Markdown](CoderUJB_中英对照.md)：按原章节整理英文原文与中文译文，包含 5 张表、4 幅图、3 个公式及全部 67 条参考文献。图表资源位于 `Images/`；原文差异及整理说明在文末单列。该文档为阅读材料；实验进展与证据见下方“ROMEO 模型运行探测”。

## 小组汇报材料

2026-11-04 从下载目录归档到 `Presentation/`，保留下载时的原文件名。

- [法语汇报 PPT（24 张幻灯片）](<Presentation/CoderUJB_Equipe6_FR 2.pptx>)
- [法语讲稿与逐页对照 PDF（26 页）](Presentation/CoderUJB_Equipe6_Scripts_FR.pdf)
- [LaTeX 重制演示 PDF（32 页，含目录、六个分段首页与完整正文）](Presentation/LaTeX/CoderUJB_Equipe6_FR.pdf)
- [LaTeX 源码与编译说明](Presentation/LaTeX/README.md) · [完整打包下载](Presentation/CoderUJB_Equipe6_LaTeX.zip)

## 论文与来源

- 论文：[CoderUJB: An Executable and Unified Java Benchmark for Practical Programming Scenarios](CoderUJB_ISSTA2024.pdf)。作者：Zhengran Zeng、Yidong Wang、Rui Xie、Wei Ye、Shikun Zhang；ISSTA 2024。
- [ACM DOI](https://doi.org/10.1145/3650212.3652115)
- [arXiv 页面](https://arxiv.org/abs/2403.19287)：预印本入口；本目录保留的是课程已有的 13 页会议版 PDF，不用预印本覆盖。
- 本地原件：[课程参考资料](../References/articles_edp_25/08-coderujb_an_executable_and_unified_java_benchmark.pdf)。本目录 PDF 为逐字节副本，原件保留。
- [官方代码：WisdomShell/ujb](https://github.com/WisdomShell/ujb)：论文正文给出的仓库。
- [官方安装与评测说明](https://github.com/WisdomShell/ujb/blob/main/README.md)
- [Defects4J](https://github.com/rjust/defects4j)：官方 README 指向的 Java 项目执行环境。

副本校验信息见 [sources.json](sources.json)。2026-11-05 已克隆官方代码至 `Reproduction/ujb/`，固定提交 `e7b69a0b4f79d0d1896046079f6926d955f31452`。已读取官方 FCG 数据集，准备了三个教学示例，详见 [题目清单](Reproduction/sample_pack/manifest.json)；原始提示位于 `Reproduction/sample_pack/prompts/`，参考答案单独保存在 `references/`。已使用 ROMEO 上既有的 PyTorch/Transformers 环境完成一次模型生成探测，尚未建立独立的 Java/Defects4J 评测环境。

## 复现对象

论文用来自 17 个开源 Java 项目的 2,239 道题，评估模型在五类任务上的表现。官方 README 中的任务名如下：

| 任务 | 数据集参数 `--bench-name` |
|---|---|
| 功能代码生成 | `codeujbcomplete` |
| 基于代码的测试生成 | `codeujbtestgen` |
| 基于 issue 的测试生成 | `codeujbtestgenissue` |
| 缺陷检测 | `codeujbdefectdetection` |
| 自动程序修复 | `codeujbrepair` |

论文第 4 节还研究上下文提示、不同模型、特定语言继续预训练、指令微调的影响。跑通评测流程与复现某张结果表是两个验收目标，应分别记录。

## 第一轮范围与后续步骤

先选择功能代码生成任务中的少量固定题目，用一个模型完成“读取题目 → 生成回答 → 编译和运行测试 → 保存逐题结果”的完整流程。这样可以先验证执行环境和评分链路，再投入完整评测。

1. 检查本机 Python、Java、构建工具、磁盘及可用计算资源；根据所选代码提交核对具体版本要求。官方 README 使用 Python 3.10，并要求另装 Defects4J。
2. 获取官方代码并记录提交哈希，检查数据下载路径、任务筛选方式、环境依赖与评测脚本；核对 Defects4J 版本，不能直接假定最新版与论文兼容。
3. 选定一个模型、固定题目 ID 和生成参数，先跑少量样本。已选 CodeLlama-13B 基础版及 ROMEO GH200，完成 task_idx 4 的一次补全探测；正式采样和测试仍待执行。
4. 保存原始回答、编译日志、测试日志和逐题判定，区分环境失败、输出解析失败、编译失败和测试不通过。
5. 跑通后再选择论文中的目标表格或研究问题，锁定模型版本、提示、样本数与指标，扩大实验。

验收第一轮：选定题目的输入、原始输出、测试日志和最终判定齐全，能在相同环境下重跑。此时只说明流程已跑通，不表述为论文结果已复现。

若采用其他模型或修改评测设置，应标注为新实验；若要复现论文数值，还需逐项核对论文和代码中的模型版本、题目集合、采样次数、温度、提示和指标定义。当前接口对 `gpt-4` 返回 `model_not_found`；这只说明该接口或账号无法访问此模型。

## ROMEO 模型运行探测（2026-11-05）

Slurm 作业 **817583** 在 `romeo-a058` 上正常结束（`COMPLETED`，退出码 `0:0`）。本次仅验证下载、加载和生成链路：

- 模型：`codellama/CodeLlama-13b-hf`，固定 revision `8da65ff4ee20f74ecd107ca9d54f9f121b279860`；使用 BF16，未量化。三个权重分片的 SHA-256 与 Meta 官方相应版本的 LFS 元数据一致，配置和分词器文件的 Git blob 标识也已核对；不能据此断言与论文实验的 checkpoint revision 完全相同。
- 资源：1 张 GH200，实际可见显存约 95.6GiB；申请主机内存 128GiB。生成时 CUDA allocated 峰值约 27.2GiB，reserved 峰值约 27.7GiB；主机内存申请额不是实测使用峰值。
- 输入：task_idx 4，Lang 项目的 `StrBuilder.deleteFirst`，采用原始 completion prompt（1,876 tokens），seed 4、temperature 0.2、最多生成 256 tokens。
- 结果：成功生成 256 tokens，用时约 13.0 秒。原始输出包含目标方法的补全，随后继续生成相邻方法，达到 token 上限；尚未提取并编译目标函数，也没有运行任何 Defects4J 测试。
- 存储：约 26.0GB 权重暂存于作业专用 `/dev/shm`，脚本通过 EXIT trap 清理临时目录。本次未建立持久模型缓存，下次作业需要重新暂存。个人 home、scratch 及项目目录的持久配额仍不足以保存这些权重；长期使用需要另行解决存储配额。

[实测结果](Reproduction/evidence/romeo-model-probe-result.json) · [原始生成输出](Reproduction/evidence/romeo-model-probe-generation.txt) · [校验与作业回执](Reproduction/evidence/romeo-model-probe-receipt.json) · [Slurm 最终状态](Reproduction/evidence/romeo-model-probe-slurm.txt)。取回的结果与输出已与远程 SHA-256 核对。首次作业 817582 因权重下载网络超时失败，失败记录保留在 `Reproduction/evidence/romeo-model-probe-attempt1-*`；增加续传后重试成功。

本次探测脚本：[Python](Reproduction/romeo_model_probe.py)、[Slurm 作业入口](Reproduction/romeo_model_probe.sh)。它们是有界的可行性探测，正式生成与评分仍需对齐官方流程。下一步建立 Java/Defects4J 环境，完成三道固定题目的编译、测试与逐题判定。

## 当前状态

- [x] 确认论文身份并复制 PDF。
- [x] 核对官方仓库、安装说明和评测入口。
- [ ] 明确要复现的研究问题或结果表。
- [x] 固定官方代码提交并记录 FCG 数据版本，准备三道示例题。
- [x] ROMEO 上完成 CodeLlama-13B BF16 加载及一次代码生成。
- [ ] 建立独立的 Java/Defects4J 评测环境。
- [ ] 跑通少量题目并审查评分。
- [ ] 开展目标实验并与论文对照。

已保存模型运行探测证据；尚未获得题目测试判定或任何基准总分，不能表述为论文结果已复现。
