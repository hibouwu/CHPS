# EDP 实践作业

[返回课程入口](../README.md)

## 工作负载分析（v2）

当前材料集中在 [edp_workload_26_v2](edp_workload_26_v2/)：

- [法语题目](edp_workload_26_v2/tp_workload.html) · [中文题目](edp_workload_26_v2/tp_workload_zh.html)
- [分析脚本](edp_workload_26_v2/analyze.py) · [轨迹生成脚本](edp_workload_26_v2/generate.py)
- [保存的答案](edp_workload_26_v2/answers.txt) · [请求大小分布图](edp_workload_26_v2/q11_size_distribution.png)
- 原始数据：该目录中的 `trace_0.csv` 至 `trace_4.csv`，全部保留。

从本目录运行：

```sh
python3 edp_workload_26_v2/analyze.py
python3 edp_workload_26_v2/generate.py
```

脚本会覆盖同目录中的输出文件。保存的 `answers.txt` 与归档答案存在表述差异，本次整理不修改作业答案、不重新生成结果；脚本和数据均保持原始字节。目录内 `SUBMISSION_README.txt` 是先前提交材料的说明，描述的是不含教师 trace 的交付包；当前学习目录包含这些 trace。

## 旧材料归档

- [edp 原提交材料](Archives/edp/)：包含另一份答案表述，以及当时配套的脚本、图片与生成数据。部分文件与 v2 相同，为保留旧材料组合一并归档。
- [2025–2026 fio 题目](Archives/TP25/TP_Evaluation_de_performances_2.pdf)：历史学年的要求，以当前教师通知为准。

原顶层 `edp.zip` 的五个文件与 `Archives/edp/` 完全相同，已删除重复压缩包。
