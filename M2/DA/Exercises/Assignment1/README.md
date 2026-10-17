# 作业一（Assignments 1）

[DA 课程首页](../../README.md) · [Lab1](../Lab1/Lab1.ipynb)

Kalogeratos 布置的第一次作业，共六题：RANSAC 与鲁棒估计、鲁棒代表点比较、维数灾难、数据划分与模型选择、在线最近质心分类、分类器局部规律性。当前版本截止 2026-10-18 午夜，提交一个包含全部解答的 Jupyter notebook。

## 阅读顺序

| 步骤 | 文件 | 说明 |
|---|---|---|
| 1. 题目 | [英文原题](Assignments1.ipynb) · [中文译本](Assignments1_zh.ipynb) | 第1题配套[点云数据](cloud-of-points-data.mat)与[示意图](cloud-of-points-outliers.png) |
| 2. 解答 | [Assignments1_solution.ipynb](Assignments1_solution.ipynb) | 中英对照解答，含代码与运行输出；即提交用的 notebook |
| 3. 讲解 | [阅读版](Assignments1_deepdive_zh.html) · [Markdown](Assignments1_deepdive_zh.md) | 逐题解释思路、推导与实验结论；HTML 已内嵌图片和公式，可单独打开 |

## 其他文件

- `outputs/`：解答 notebook 运行时写出的文件，重新运行会覆盖。
  - [Assignments1_ex6_results.csv](outputs/Assignments1_ex6_results.csv)：第6题全部实验记录，38,400 行。
  - [Assignments1_ex6_selected.csv](outputs/Assignments1_ex6_selected.csv)：第6题内部交叉验证选 k 后的外层结果，960 行。
  - [Assignments1_model.joblib](outputs/Assignments1_model.joblib)：第4题交付的最终模型。
- `Assignments1_deepdive_assets/`：讲解 Markdown 引用的图片。修改 Markdown 后，HTML 阅读版需同步更新。

## 来源

英文原题与 2026-10-16 收到的压缩包逐字节一致。包内只有英文原题、点云数据和示意图三个文件，均已放在本目录，压缩包不再保留。

第1、2题的点云实验使用自行生成的样本，这是题目允许的做法；其数值不能当作老师所给数据的实验结果。
