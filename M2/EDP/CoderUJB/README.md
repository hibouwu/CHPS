# CoderUJB 复现工作区

[返回 EDP 课程目录](../README.md)

[四模型实验设计与热力图协议](Reproduction/实验设计.md)

**进行中：CodeLlama 全量多候选复现。** 已开启独立目标，对全部 2,239 题执行生成任务每题 20 次、DD 每题 10 次，共 35,380 个正式候选。旧 A/B 结果保持原样；新结果单独保存，尚无最终全量分数。[全量协议与运行入口](Reproduction/full20/README.md) · [实时生成进度](Reproduction/evidence/cl13-full20-20261105/generation-progress.json) · [全量评分汇总（含未完成分母）](Reproduction/evidence/cl13-full20-20261105/summary.json)

**最新入口：[复现交接与答辩观察（reviewed-v2）](Reproduction/复现交接.md)** · [审阅后热力图](Reproduction/evidence/final-review/heatmap-reviewed.png)。800 份 A/B 正式回答已从原始证据复算：273 通过、525 失败、2 未决，398 对可直接配对。修复覆盖统计遗漏内部类的问题后，CodeLlama B 的 CTG 从 4/20 改为 5/20；该新增通过来自空测试触发枚举初始化，不能解释为测试质量提升。旧报告与结果原样保留；当前数字以 reviewed-v2 为准。交接中包含离线重建命令、环境版本、恢复规则与未决范围。

状态更新于 2026-11-05。四个模型已分别在同一份冻结 100 题上完成 A 列单次生成，每类 20 题。Sol 使用官方 Responses API；三个公开权重模型使用 ROMEO。A 列及五道独立试跑题的付费 API 用量估算为 $0.561186；加上 B 列后，本窗口累计估算 **$1.1202265**（非账户最终账单），两个阶段的预留均已释放。下表展示通过或答对的数量，未决行保留原始分母。[四模型同题对照及逐行证据](Reproduction/evidence/sol-a100/四模型对照.md)

| 任务 | CodeLlama-13B | gpt-oss-120b | Qwen2.5-Coder-32B-Instruct | GPT-6.1 Sol |
|---|---:|---:|---:|---:|
| FCG | 2/20，1 未决 | 3/20 | 2/20 | 14/20 |
| CTG | 3/20 | 5/20 | 6/20 | 16/20 |
| ITG | 0/20 | 1/20 | 1/20 | 10/20 |
| APR | 0/20 | 6/20 | 2/20，1 未决 | 14/20 |
| DD | 10/20 | 12/20 | 9/20 | 16/20 |

模型的提示方式、精度、解码与预算均记录在对应协议中。这些是固定子集上的单次观测，差值不能全部归因于模型能力。2,239 题全量、多次采样与 C–E 工程对照尚未执行；B 列见下方入口。[Sol 协议](Reproduction/evidence/sol-a100/protocol.json) · [费用与用量](Reproduction/evidence/sol-a100/cost.json)

B 列的四模型 400 次生成与评分也已完成：只增加任务级固定输出约束，复用 A 列结果。[A/B 历史报告（v1，修正前）](Reproduction/evidence/b100/A-B对照报告.md) · [提示变化与规则](Reproduction/evidence/b100/freeze.json)。这是看过 A 结果后的探索性比较；当前 reviewed-v2 的修正与可重建结果见上方交接入口。

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

副本校验信息见 [sources.json](sources.json)。2026-11-05 已克隆官方代码至 `Reproduction/ujb/`，固定提交 `e7b69a0b4f79d0d1896046079f6926d955f31452`。已读取官方 FCG 数据集，准备了三个教学示例，详见 [题目清单](Reproduction/sample_pack/manifest.json)；原始提示位于 `Reproduction/sample_pack/prompts/`，参考答案单独保存在 `references/`。已使用 ROMEO 上既有的 PyTorch/Transformers 环境完成一次模型生成，并在本地独立 Java 8 / Defects4J 2.0.1 环境中验证第一题。

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
3. 选定一个模型、固定题目 ID 和生成参数，先跑少量样本。已选 CodeLlama-13B 基础版及 ROMEO GH200，完成 task_idx 4 的一次补全及编译、测试；另外两题与正式多次采样仍待执行。
4. 保存原始回答、编译日志、测试日志和逐题判定，区分环境失败、输出解析失败、编译失败和测试不通过。
5. 跑通后再选择论文中的目标表格或研究问题，锁定模型版本、提示、样本数与指标，扩大实验。

验收第一轮：选定题目的输入、原始输出、测试日志和最终判定齐全，能在相同环境下重跑。此时只说明流程已跑通，不表述为论文结果已复现。

若采用其他模型或修改评测设置，应标注为新实验；若要复现论文数值，还需逐项核对论文和代码中的模型版本、题目集合、采样次数、温度、提示和指标定义。当前接口对 `gpt-4` 返回 `model_not_found`；这只说明该接口或账号无法访问此模型。

## ROMEO 模型运行探测（2026-11-05）

Slurm 作业 **817583** 在 `romeo-a058` 上正常结束（`COMPLETED`，退出码 `0:0`）。本次仅验证下载、加载和生成链路：

- 模型：`codellama/CodeLlama-13b-hf`，固定 revision `8da65ff4ee20f74ecd107ca9d54f9f121b279860`；使用 BF16，未量化。三个权重分片的 SHA-256 与 Meta 官方相应版本的 LFS 元数据一致，配置和分词器文件的 Git blob 标识也已核对；不能据此断言与论文实验的 checkpoint revision 完全相同。
- 资源：1 张 GH200，实际可见显存约 95.6GiB；申请主机内存 128GiB。生成时 CUDA allocated 峰值约 27.2GiB，reserved 峰值约 27.7GiB；主机内存申请额不是实测使用峰值。
- 输入：task_idx 4，Lang 项目的 `StrBuilder.deleteFirst`，采用原始 completion prompt（1,876 tokens），seed 4、temperature 0.2、最多生成 256 tokens。
- 结果：成功生成 256 tokens，用时约 13.0 秒。原始输出包含目标方法的补全，随后继续生成相邻方法，达到 token 上限；本探测阶段只生成代码，后续提取、编译和测试结果见下节。
- 存储：约 26.0GB 权重暂存于作业专用 `/dev/shm`，脚本通过 EXIT trap 清理临时目录。本次未建立持久模型缓存，下次作业需要重新暂存。个人 home、scratch 及项目目录的持久配额仍不足以保存这些权重；长期使用需要另行解决存储配额。

[实测结果](Reproduction/evidence/romeo-model-probe-result.json) · [原始生成输出](Reproduction/evidence/romeo-model-probe-generation.txt) · [校验与作业回执](Reproduction/evidence/romeo-model-probe-receipt.json) · [Slurm 最终状态](Reproduction/evidence/romeo-model-probe-slurm.txt)。取回的结果与输出已与远程 SHA-256 核对。首次作业 817582 因权重下载网络超时失败，失败记录保留在 `Reproduction/evidence/romeo-model-probe-attempt1-*`；增加续传后重试成功。

本次探测脚本：[Python](Reproduction/romeo_model_probe.py)、[Slurm 作业入口](Reproduction/romeo_model_probe.sh)。它们是有界的可行性探测。生成后已完成第一题的编译和测试，详见下节；正式多样本评测仍需对齐论文设置。

## 第一题编译与测试结果（2026-11-05）

已对 task_idx 4（Lang `StrBuilder.deleteFirst`）的这一次 CodeLlama-13B 生成完成验证。沿用官方补全模式的函数提取和源码替换规则，分别在两份 Lang `1f` 项目中测试原始函数与模型函数；模型答案没有手工修改。两份项目都使用数据集自带的类源码；它与 Defects4J checkout 的行内容完全一致，仅文件结尾换行不同。

| 检查 | 原始函数对照 | 模型本次生成 |
|---|---|---|
| Java 语法解析 | 通过 | 通过 |
| 项目编译 | 通过 | 通过 |
| `testDeleteFirst_String` | 通过，0 失败 | 通过，0 失败 |
| `testIndexOfLang294` | 通过，0 失败 | 通过，0 失败 |
| `testLang295` | 通过，0 失败 | 通过，0 失败 |
| Defects4J 全项目测试集 | 通过，0 失败 | 通过，0 失败 |

环境为本地 Temurin Java 8u504-b01、Defects4J 2.0.1（提交 `a83e47921152721569cb95d6d7b91c4be277d940`）和 javalang 0.13.0。大型依赖和工作副本位于 `/data/jianyeshi/coderujb-reproduction/`；系统默认 Java 未切换。此环境仅初始化 Lang 的 checkout、编译和开发者测试所需组件，未安装 Gradle、自动测试生成、覆盖率或变异测试的完整工具链；细节记录在 [环境清单](Reproduction/evidence/test-environment.json)。这不是对论文原运行环境全部版本的完整复原。

[逐步结果](Reproduction/evidence/lang004-evaluation-20261105T002947Z/result.json) · [提取的模型函数](Reproduction/evidence/lang004-evaluation-20261105T002947Z/generated-function.java) · [与原始函数的差异](Reproduction/evidence/lang004-evaluation-20261105T002947Z/model-vs-baseline.diff) · [全项目测试输出](Reproduction/evidence/lang004-evaluation-20261105T002947Z/model-all-tests.stdout.log)。对应目录保留所有命令的 stdout、stderr、退出码和 SHA-256 清单。

重跑这一题的现有输出（不重新调用模型）：

```bash
/data/jianyeshi/coderujb-reproduction/runtime/eval-venv/bin/python /home/jianyeshi/Note/SiteCHPS/CHPS/M2/EDP/CoderUJB/Reproduction/evaluate_lang004.py
```

脚本每次新建工作目录和证据目录，先跑原始函数对照，再跑模型函数。每个指定测试超时 120 秒，全项目测试超时 180 秒；失败和超时会单独记录。

当前结论仅为“一题、一次生成通过既有测试”，没有计算整体 pass@k。任务 5、6 尚未生成或测试。下一步可完成另外两题，再考虑与汇报相关的上下文对照。

[gpt-oss-120b 的同题实测结果](Reproduction/evidence/oss120-lang004/receipt.json)：已在 ROMEO 单张 GH200 生成独立答案，通过本机 Lang 1f 的三个指定测试及全项目测试。

## gpt-oss-120b 与五类评分器（2026-11-05）

五类评分器的 11 个通过、失败及不可解析对照均符合预期。CTG/ITG 已实际运行 Cobertura。ITG 正例在修复版通过、在缺陷版触发指定测试的断言；一个对两版本都通过的测试被判为失败。包装器修正了覆盖率行首空格的解析，为每次执行隔离日志，验证了超时后子进程终止，以及重新提交同一候选时新增执行次数为零。历史环境清单记录的是首次 Lang 演示时的安装状态。[评分器对照](Reproduction/evidence/scoring/controls.json) · [超时](Reproduction/evidence/scoring/timeout-control.json) · [断点恢复](Reproduction/evidence/scoring/resume-control.json)

gpt-oss-120b 的 2,048-token 试跑每类一题。FCG 通过；CTG 生成的方法缺少原测试类可用的静态导入，javac 报找不到断言方法，保留原回答和编译诊断；ITG 通过双版本判定；APR 达到输出上限（`finish_reason=length`），函数未写完并触发语法失败；DD 正确。全部评分基于原始交付物。五个样例用于答辩展示。[逐题记录](Reproduction/evidence/oss120-task-pilot/results.json) · [评分细节与实验设计](Reproduction/实验设计.md)

正式的现代模型 A 列另行冻结 4,096-token 协议。只使用冻结的 100 个行键，一题至多一个答案。每个 Java 项目版本先验证原始对照能执行；缺依赖或对照不通过的行登记为环境未决。两套 token 上限分别报告。80 道 Java 题的原始对照均通过，覆盖 17 个项目，另有 20 道 DD 题直接评分。四次 ROMEO 单卡作业累计 20 分 9 秒，正式 A 列的 100 个独立请求均已核验，APR 有 2 次截断。 [分任务报告](Reproduction/evidence/oss120-a100/报告.md) · [实际输入审计](Reproduction/evidence/oss120-a100/input-audit.json) · [A 列协议](Reproduction/evidence/oss120-a100/protocol.json)

## 当前状态

- [x] 确认论文身份并复制 PDF。
- [x] 核对官方仓库、安装说明和评测入口。
- [x] 在实验设计中列出表 3、表 4 的复现问题和现代模型扩展。
- [x] 固定官方代码提交并记录 FCG 数据版本，准备三道示例题。
- [x] ROMEO 上完成 CodeLlama-13B BF16 加载及一次代码生成。
- [x] 建立独立的 Java 8 / Defects4J 2.0.1 环境，完成 Lang 第一题测试。
- [x] 第一题完成“生成 → 编译 → 指定测试 → 全项目测试”，保留日志。
- [ ] 完成另外两道固定题目并审查逐题结果。
- [x] gpt-oss-120b 完成冻结 100 题的 A 列单次基线并核验全部原始输入。
- [x] CodeLlama-13B 在相同 100 题完成一次生成，保留官方判分、逐题配对与不确定性。
- [x] Qwen2.5-Coder-32B-Instruct BF16 完成同题 100 次生成及三模型配对，99 题确定判定、1 题测试类初始化未决。
- [x] GPT-6.1 Sol 完成同题 100 次生成与评分，100 题均有确定判定；五道独立试跑与正式请求合计估算 $0.561186。
- [x] 四模型完成固定 100 题的 B 列单次生成与 A/B 配对，产出五类任务热力图和格式/测试效果诊断。
- [ ] CodeLlama-13B 完成 2,239 题，并按论文协议对照历史结果。

目前可展示四模型在相同 100 题上的观测；最新结果见顶部四模型表格。CodeLlama 在 FCG 有 2 题通过及 1 题超时未决，CTG 通过 3 题，ITG 和 APR 各 0 题，DD 按官方规则答对 10 题。每类 20 道。15 道 DD 题的首选项与官方整段解析的类别不同，详见 [逐行解析核对](Reproduction/evidence/cl13-a100/dd-first-choice.json)。
