# CodeLlama 全量多候选实验（运行中）

目标：全部 2,239 题；FCG 238×20、CTG 140×20、ITG 451×20、APR 470×20、DD 940×10，共 **35,380 个正式候选**。不调用付费 API。每题保留全部候选，不挑最好答案代替 pass@1。

本轮结果独立位于 `../evidence/cl13-full20-20261105/`，其物理路径是 `/data/jianyeshi/coderujb-reproduction/full20-20261105/`。旧 A/B 及 reviewed-v2 结果保留原位，并以 `prior-results-sha256.json` 冻结校验。本轮不复用旧候选充当新增采样。

## 固定协议

- 官方仓库：`e7b69a0b4f79d0d1896046079f6926d955f31452`；五个数据集 revision 和文件 SHA-256 继承已核验的 dataset audit。权威键为 task + revision + task_idx，不能按 DD 的 task_id 去重。
- 模型：`codellama/CodeLlama-13b-hf`，revision `8da65ff4ee20f74ecd107ca9d54f9f121b279860`，BF16。权重每次暂存后按原 LFS 哈希核验。
- 官方 `prompt_complete.strip()`；输入上限 4096，保留右侧；输出上限 256；temperature=0.2；每题 `torch.manual_seed(task_idx)`；一次 `generate` 返回 20 个候选，DD 返回 10 个。其余默认值保存在每个作业 runtime 文件中。
- 7 道题超过输入上限，保持官方截断策略并记录，不据此删除题目。
- 运行后端为 Transformers 4.53.3 / torch 2.7.1+cu128 / SDPA。4096×20 容量探测在默认分配器和 expandable segments 下均 OOM；加入 `prefill_chunk_size=512` 后通过，峰值约 91.5 GiB。它改变计算执行方式，不改变输入长度、候选数、温度或生成预算；仍须披露与历史后端的差异，不能声称逐 token 完全相同。三个探测作业为 817727、817734、817737，全部独立于正式统计。
- 官方生成脚本累积追加历史答案的行为不沿用；每个题目/候选索引只接纳一次完成记录。保留自然生成的重复答案，不能对相同代码去重后缩小候选分母。相同提取代码可以复用执行结果，但每个真实采样候选仍各计一次。

## 评分

`scorer.py` 是独立的新版本，不修改旧评分器。形式化成功条件保留官方提取与覆盖门槛；实际 stdout、failing_tests 和 XML 留存。

| 任务 | 目标测试时限 | 完整套件/覆盖时限 |
|---|---:|---:|
| FCG | 120 秒 | 套件 180 秒 |
| CTG | 120 秒 | 覆盖 180 秒 |
| ITG | 10 秒 | 覆盖 10 秒 |
| APR | 180 秒 | 套件 240 秒 |

正式主结果统一在 ROMEO x64cpu 平台评分，使用相同 Java/Defects4J 源码与独立 Perl 依赖；`JAVA_TOOL_OPTIONS=-XX:ActiveProcessorCount=2`，每 CPU 作业 16 核/48 GiB、6 个评分线程。主结果位于 `remote-primary/`。早期本机评分只验证流水线，原记录保留在根目录 `scores/`、`scoring/`，不混入主结果；同一保存答案在主平台重新评分，不重新生成。

正式 `defects4j test` 的隐式编译计入测试时限，避免先编译后另计时而改变原配方。参考实现以单独的宽松环境控制运行，编译/目标测试 180 秒、套件 240 秒；控制结果不计模型分数。参考控制不通过时，模型结果标为基础设施未决，不自动删除该题。

参考控制通过后，正式候选超过公开时限记为预算内失败，原始超时记录仍保留。这是新实验事先声明的口径；旧 A 列的超时未决仍不改动。真实编译失败、目标或套件断言失败计模型失败；checkout/缺少日志等基础设施异常不当作模型失败。ITG 还要求失败来自插入的目标测试，不能把编译失败或超时当作成功复现缺陷。与公开脚本宽松错误处理的差异明确保留。

覆盖率同时报告两项：论文定义的 `(类、文件、行号)` 覆盖并集；公开代码把命中布尔值放入元组再取并集的历史实现值。后者会把同一行的 true/false 当作不同元素，不能静默混用。内部类计入实际插桩输出，保留之前的修正。

## 运行与恢复

- `generation_controller.py`：29 个固定输入批次，最多 4 个 GPU 作业；每作业 1 GPU / 8 CPU / 192 GiB / 4 小时。自动收回输出并核验每份 raw SHA-256，之后写 `ready/`。逐批记录 remote、submission、sacct。观察失败只重查原作业，不自动重复提交。
- `score_rows.py`：仅评分已验证的保存答案。每个候选独立落盘；相同代码缓存有锁；生成与评分文件分开。未完成的派发不能删除 marker 重跑；须先确认旧进程/作业状态，保留失败尝试。
- `cpu_controller.py`：仅将哈希已验证的保存答案送往统一 CPU 评分平台，最多 4 个 CPU 作业；每题候选及执行日志收回到 `remote-primary/`。
- `summarize.py`：只统计 `remote-primary/` 的正式评分，离线生成 `summary.json`，给出 pass-all@1/@10、count-all@20、coverage@20，以及 DD 全候选/首候选的两种准确率和 error-count。缺失/未决候选保留计划分母并给上下界；上下界不是置信区间。
- 新运行中的时间/后端/样本数量差异需随原论文及旧 100 题比较一同披露。旧单次 A 与本轮每题 20 次的均值不能直接套二元 McNemar 比较。

本机入口（生成控制器和本地评分器已启动时，不重复启动）：

```bash
cd /home/jianyeshi/Note/SiteCHPS/CHPS/M2/EDP/CoderUJB/Reproduction
export CODERUJB_RUN="$PWD/evidence/cl13-full20-20261105"
export PYTHONPATH=/data/jianyeshi/coderujb-reproduction/runtime/eval-venv/lib/python3.14/site-packages
export PYTHONDONTWRITEBYTECODE=1
python full20/summarize.py
```

当前权威状态文件为 `generation-progress.json`、`scoring-progress-*.json`、各作业 sacct 与 `summary.json`；准备文件或 PID 文件本身不证明进程仍在运行。目标在全部生成、实际评分、未决诊断和对照报告完成前保持 active。
