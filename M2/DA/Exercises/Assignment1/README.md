# 作业一（Assignments 1）

[DA 课程首页](../../README.md) · [Lab1](../Lab1/Lab1.ipynb)

Kalogeratos 布置的第一次作业，共六题：RANSAC 与鲁棒估计、鲁棒代表点比较、维数灾难、数据划分与模型选择、在线最近质心分类、分类器局部规律性。当前版本截止 2026-10-18 午夜，提交一个包含全部解答的 Jupyter notebook，说明文字用英语或法语；学期末还有约 10 分钟的口试。

## 分题讲解

每题一篇，包含交付清单、逐小题讲解、动手顺序和口试自测。第 0 节的材料清单与第 1 节的前置知识供你按需回查；不必先读完全部材料才开始做题。

| 题 | 分值 | 讲解 | 先回答的核心问题 |
|---|---:|---|---|
| 1 | 25% | [RANSAC 与鲁棒估计](guide/01_ransac.md) | 少量异常点怎样把普通估计拉偏，怎样找出一致的数据？ |
| 2 | 15% | [三种鲁棒代表点的比较](guide/02_robust_representatives.md) | 距离阈值、接受区域与保留比例，分别控制什么？ |
| 3 | 15% | [维数灾难：复现 ESL 图 2.6–2.9](guide/03_curse_of_dimensionality.md) | 高维中近邻变远以后，误差为什么增加？ |
| 4 | 15% | [数据划分：训练、验证、测试与时间序列](guide/04_data_splitting.md) | 哪些数据可以用来选择模型，哪些只能用来最终评价？ |
| 5 | 15% | [只存两个均值的在线线性分类器](guide/05_online_classifier.md) | 不保存样本，能不能保留预测所需的信息？ |
| 6 | 15% | [定义并检验分类器的局部规律性](guide/06_regularity.md) | 附近的预测是否一致，与预测是否正确有什么区别？ |

每一题建议这样用：先看交付清单，明确要回答什么；再对照参考解答读对应小题，遇到不懂的概念再回查材料和前置知识。亲自运行后，合上解释，用自己的话说明一张图或一段代码为什么得到这个结果，再写进作业。最后用口试自测检查理解。

时间紧时的顺序：第5、4题最短，可以先完成；第1题分值最高，第2题要用到第1题 c1、c2 的函数，接着做；第3题按书复现；第6题完整网格运行时间长，先用小网格调通。

## 开始前的准备

**遇到困难时，优先检查这些基础：**

- 编程：Python、NumPy 向量化运算、matplotlib 画图、pandas 分组汇总、scikit-learn 的 `fit` / `predict`。不熟悉 scikit-learn 的话，先看 [Lab1](../Lab1/Lab1_zh.ipynb) 第 4 节"Python 中的线性回归"。
- 概率统计：期望和方差、正态分布及其分布函数 $\Phi$、条件概率与 Bayes 公式。
- 线性代数：向量、内积、欧氏范数、矩阵乘法。

**课上材料与各题的对应。**表中的“必读”标出理解本题的主要来源，不表示做题前必须逐篇读完。已经能解释对应概念的部分可以跳过；同一份材料在几题中出现时，读一次即可。具体范围见各篇讲解的第 0 节。

| 材料 | 第1题 | 第2题 | 第3题 | 第4题 | 第5题 | 第6题 |
|---|---|---|---|---|---|---|
| [Lab1](../Lab1/Lab1_zh.ipynb) 第 9 节 稳健线性回归 | 必读 | | | | | |
| Lab1 第 10 节 逻辑回归 | | | | 必读 | | |
| Lab1 第 12 节 偏差与方差的权衡 | | | | 选读 | | |
| Lab1 第 13 节 验证方法 | | | | 必读 | | 必读（部分） |
| [第一课第 2 篇](../../Lectures/01_intro/02_algorithms_and_pipeline.md#classroom-local) 局部方法 | | | | | | 必读 |
| [第一课第 4 篇](../../Lectures/01_intro/04_hypotheses_and_bias_variance.md#bias-variance) 偏差—方差分解 | | | 必读 | | | |
| [第一课第 5 篇](../../Lectures/01_intro/05_linear_models.md) 线性模型 | 必读（前半） | | 选读（$d/n$） | | | |
| [第一课第 7 篇](../../Lectures/01_intro/07_bayes_and_learning_bounds.md#reading-bayes-solutions) Bayes 最优 | | | | | 必读 | 选读 |
| [第二课第 2 篇](../../Lectures/02_LM/02_generalization_and_high_dimensions.md#reading-orange-shell) 高维插曲 | | | 选读 | | | |
| [第二课第 6 篇](../../Lectures/02_LM/06_regularization_and_validation.md#reading-cross-validation) 交叉验证 | | | | 必读 | | |
| [第三课](../../Lectures/03_LMC_zh.md#section-10) LDA 与 QDA | | | | | 必读 | |
| [第五课](../../Lectures/05_NLM_zh.md#kernel-svm) 核技巧 | | 必读 | | | | |
| [第五课](../../Lectures/05_NLM_zh.md#section-11) SVM 间隔与松弛变量 | | 选读 | | | | |
| [第五课](../../Lectures/05_NLM_zh.md#section-08) 感知机 | | | | | 选读 | |
| [第五课](../../Lectures/05_NLM_zh.md#local-methods) 局部方法（kNN、决策树） | | | 选读（kNN） | | | 必读 |
| ESL 2.5 节 高维中的局部方法 | | | 必读 | | | |
| ESL 7.10 节 交叉验证 | | | | 选读 | | |
| ESL 13.3 节 k 近邻分类器 | | | | | | 选读 |
| ESL 14.3.6 节 K-means | 必读 | | | | | |
| [LDA 教程](../../Tutorials/tutorial-LDA/README.md)第 3、10 节 | | | | | 选读 | |
| scikit-learn 单类 SVM 文档 | | 必读 | | | | |
| Kalogeratos 2011 论文 Algorithm 2 | | 必读 | | | | |

若需要完整补读这些主要材料，参考用时为：第1题约 30 分钟，第2题约 20 分钟，第3题约 35 分钟，第4题约 25 分钟，第5题约 17 分钟，第6题约 20 分钟。它们可以穿插在做题过程中。课程讲义没有专门讲 k-means 和单类 SVM，这两处用 ESL 和 scikit-learn 文档补上。

## 六题之间的联系

六题可以沿三条线理解：

- **数据不可靠时怎样估计**：第1题用 RANSAC 从被污染的数据中找出一致的部分，再把直线拟合推广到中心估计和聚类；第2题任务不变，换用单类 SVM 和合成原型，比较它们各自的假设。
- **怎样评价学习效果**：第3题说明高维空间中"最近"不一定"足够近"，并把预测误差拆成偏差、方差和噪声；第4题讨论怎样用有限数据训练、调参和测试，避免评价结果过于乐观。
- **受约束时怎样设计方法**：第5题不能保存历史样本，需要找可递推的统计量；第6题不能只看准确率，要自己定义局部决策的一致性，并解释这个指标什么时候会失效。

读每个小题时，先盖住代码，用自己的话说出输入、输出和评价标准；再看公式中的每个量怎样变成数组运算；最后试着解释图中一个反直觉的现象。能做到这三步，比记住某段代码更能帮你回答口试问题。

## 口试准备

每篇讲解的"口试自测"一节给出了该题的讲解主线、适合展示的证据和建议时长，六题合计约 10 分钟。三类常见追问可以这样准备：

- **"为什么用这个参数？"**先说参数的单位和作用，再说本次的选择依据。例如 RANSAC 的 25 是响应变量单位下的残差阈值，来自噪声标准差 10；Regularity 的 5 是邻居个数，是固定的评价尺度。两者不能用同一种理由解释。
- **"你的方法是不是总是更好？"**先限定任务和条件，再用实验中的反例说明边界。例如合成原型在平移距离 2 时优于 RANSAC，而 RANSAC 在 30% 污染、平移 12 时也没有完全恢复正确的聚类。
- **"这是理论证明还是实验结果？"**要明确区分：在线均值等于批量均值是代数恒等式；某次准确率 98.4% 是有限测试集上的观察；训练比例 60% 最好是这一次划分实验的结果；更多训练数据能否继续提高准确率，需要进一步实验。

## 文件

| 文件 | 说明 |
|---|---|
| [英文原题](Assignments1.ipynb) · [中文译本](Assignments1_zh.ipynb) | 题目；第1题配套[点云数据](cloud-of-points-data.mat)与[示意图](cloud-of-points-outliers.png) |
| [英文解答](Assignments1_solution.ipynb) · [中文解答](Assignments1_solution_zh.ipynb) | 完整解答（第 1–6 题），含代码与运行输出，LLM 使用范围见其末尾的 Use of LLMs 说明 |
| [提交版 v1（第 1–3 题）](SHI_Jianye_Assignment1_v1/SHI_Jianye_Assignment1_v1.ipynb) · [压缩包 v1](SHI_Jianye_Assignment1_v1.zip) | 第一版提交文件（仅含第 1–3 题） |
| [提交版 v2（第 1–6 题）](SHI_Jianye_Assignment1_v2/SHI_Jianye_Assignment1_v2.ipynb) · [压缩包 v2](SHI_Jianye_Assignment1_v2.zip) | 第二版完整提交文件（含第 1–6 题全部解答、配套数据及 `outputs/` 导出结果） |
| [guide/](guide/) | 分题讲解；`guide/assets/` 是讲解引用的图片，均来自参考解答的输出 |
| `outputs/` | 参考解答运行时写出的文件，重新运行会覆盖 |

`outputs/` 中的文件：

- [Assignments1_ex6_results.csv](outputs/Assignments1_ex6_results.csv)：第6题全部实验记录，38,400 行。
- [Assignments1_ex6_selected.csv](outputs/Assignments1_ex6_selected.csv)：第6题内部交叉验证选 $k$ 后的外层结果，960 行。
- [Assignments1_model.joblib](outputs/Assignments1_model.joblib)：第4题交付的最终模型。

## 来源

英文原题与 2026-10-16 收到的压缩包逐字节一致。包内只有英文原题、点云数据和示意图三个文件，均已放在本目录，压缩包不再保留。

第1、2题的点云实验使用自行生成的样本，这是题目允许的做法；其数值不能当作老师所给数据的实验结果。参考解答保存的运行环境为 NumPy 2.4.6、SciPy 1.16.2、scikit-learn 1.9.1，其他版本下边界判断、并列处理或随机算法的细节可能使数值略有变化。
