# 第二讲讲解整合与核对

2026-10-16：正文已迁入[第二课双语分篇](../02_LM_zh.md)，下方概念链接已更新。本文保留先前讲解整合阶段的记录与验证结果；分篇后的对应关系和验证见[双语分篇记录](2026-10-16-bilingual-split.md)。

日期：2026-10-16。主文件：[线性模型与稀疏性](../02_LM_zh.md)。

## 阅读方式与内容保留

- 以整合前的完整中文译文为基线，保留原课件的 40 个一级课程段落及其顺序，新增 34 处概念解释或例子。必要解释直接显示，AIC 原有长推导及较长补充推导、旁支材料置于折叠区。
- 原有 11 张图、完整练习、重复课件正文和已有译注保留；新增一张根据一维目标函数计算的惩罚比较图。
- 通过反向移除本轮增补、还原标题和排版、还原逐项登记的 PDF 转换修复，可以逐字恢复整合前文件。此项检查用于确认没有未登记的正文删除。
- 原 PDF、英文转换稿、三份课堂转录、其余五篇中文讲义的 SHA-256 与编辑前一致。源文件作为完整原始记录保留。
- 新增解释采用直接论述的文章文风。来源对应关系放在本记录，正文保留少量外部阅读链接。

## 课堂内容去向

三份转录合计 770 行，以下范围连续覆盖全部行。范围包括口头重复、空行、个人经历和课堂安排；它用于查找内容去向，不把每一行都当成独立知识点。

### 02_part1.md

来源：[02_part1.md](../02_part1.md)。

| 行范围 | 内容与处理 | 正文位置 |
|---|---|---|
| 1–18 | 监督标签、决策函数；课次安排保留原始记录 | [对应位置](../02_LM/01_linear_models_and_least_squares.md#reading-model-and-learning) |
| 19–65 | 新标签逐渐到来、半监督分布信息、更新与时间权重；公司和人物旁例不写成事实结论 | [对应位置](../02_LM/01_linear_models_and_least_squares.md#reading-model-and-learning) |
| 66–75 | 模型一词与个人教学经历；个人经历留在原文 | [对应位置](../02_LM/01_linear_models_and_least_squares.md#reading-model-and-learning) |
| 76–111 | 概率分布族、参数规模、函数族与已训练预测器 | [对应位置](../02_LM/01_linear_models_and_least_squares.md#reading-model-and-learning) |
| 112–123 | 无监督问题也可通过似然目标进行优化 | [对应位置](../02_LM/01_linear_models_and_least_squares.md#reading-model-and-learning) |
| 124–138 | 生成式模型问答；叙述混合了对抗训练与语言模型，保留原文供查阅，不移植为第二课技术结论 | [对应位置](../02_LM/07_kernels_and_extensions.md#reading-sources) |
| 139–147 | 线性依赖参数、监督框架及总体最优参照 | [对应位置](../02_LM/01_linear_models_and_least_squares.md#reading-linear-in-parameters) |
| 148–168 | 相似性推断、个体表示与个性化；营销史和人物刻板案例留在原文 | [对应位置](../02_LM/01_linear_models_and_least_squares.md#reading-model-and-learning) |
| 169–185 | 无限函数族不等于全部函数、最优依赖准则、不可约误差 | [对应位置](../02_LM/01_linear_models_and_least_squares.md#reading-three-functions) |

### 02_part2.md

来源：[02_part2.md](../02_part2.md)。

| 行范围 | 内容与处理 | 正文位置 |
|---|---|---|
| 1–13 | 多项式及基展开对参数线性 | [对应位置](../02_LM/01_linear_models_and_least_squares.md#reading-linear-in-parameters) |
| 14–20 | 闭式解与数值求解；未沿用所有深度学习均使用平方损失的概括 | [对应位置](../02_LM/01_linear_models_and_least_squares.md#reading-normal-equation) |
| 21–39 | 矩阵形状、最小二乘、正交投影及幂等性 | [对应位置](../02_LM/01_linear_models_and_least_squares.md#reading-ls-example) |
| 40–58 | 梯度、常数比例与正规方程；对照 PDF 保留和解释原页笔误 | [对应位置](../02_LM/01_linear_models_and_least_squares.md#reading-normal-equation) |
| 59–64 | 期望与经验量的区别，固定设计下的风险定义 | [对应位置](../02_LM/02_generalization_and_high_dimensions.md#reading-fixed-design-risk) |
| 65–91 | 正交分解、噪声投影和 d/n；用期望而非卡方方差解释 d/n | [对应位置](../02_LM/02_generalization_and_high_dimensions.md#reading-variance-directions) |
| 92–110 | 变量数、样本数与高维情形；历史概括留在原文 | [对应位置](../02_LM/02_generalization_and_high_dimensions.md#reading-high-dimensional-regimes) |
| 111–136 | 求解规模、秩亏、病态与参数个数的区别 | [对应位置](../02_LM/02_generalization_and_high_dimensions.md#reading-rank-and-stability) |
| 137–158 | 高维橘子皮计算；明确均匀体积采样条件 | [对应位置](../02_LM/02_generalization_and_high_dimensions.md#reading-orange-shell) |
| 159–170 | 高维表示与个性化旁例；基本表示含义融入开篇，社会与医疗引申留在原文 | [对应位置](../02_LM/01_linear_models_and_least_squares.md#reading-model-and-learning) |
| 171–176 | 学习要求、休息时间等当时安排，保留原始记录 | [对应位置](../02_LM/07_kernels_and_extensions.md#reading-sources) |

### 02_part3.md

来源：[02_part3.md](../02_part3.md)。

| 行范围 | 内容与处理 | 正文位置 |
|---|---|---|
| 1–34 | 伪逆、最小范数、对角加载与 Ridge 的统计含义 | [对应位置](../02_LM/05_ridge_and_duality.md#reading-ridge-eigenvalues) |
| 35–61 | 支撑未知、零范数、选择变量与估计系数 | [对应位置](../02_LM/03_sparsity_and_model_selection.md#reading-sparse-support) |
| 62–83 | 数量约束与惩罚定价，非凸选择使两种表述不完全等价 | [对应位置](../02_LM/03_sparsity_and_model_selection.md#reading-budget-and-price) |
| 84–95 | 逐步选择、组合搜索与计算规模；未将随口规模当成通用算法上限 | [对应位置](../02_LM/04_lasso_and_structured_sparsity.md#reading-greedy-and-convexity) |
| 96–122 | 子矩阵、预言机、AIC 与残差惩罚 | [对应位置](../02_LM/03_sparsity_and_model_selection.md#reading-aic-example) |
| 123–128 | 模型组合数及大规模选择的偏差 | [对应位置](../02_LM/03_sparsity_and_model_selection.md#reading-subset-complexity) |
| 129–142 | 同时选择结构与参数、Dropout 的旁支直觉 | [对应位置](../02_LM/04_lasso_and_structured_sparsity.md#reading-regularization-purpose) |
| 143–165 | 凸松弛、LASSO 与 log d 依赖；未沿用年代或全局最小凸上界的口头说法 | [对应位置](../02_LM/04_lasso_and_structured_sparsity.md#reading-lasso-threshold) |
| 166–180 | 路径图及系数随强度变化；未把路径说成每种模型大小的最佳子集解 | [对应位置](../02_LM/06_regularization_and_validation.md#reading-regularization-paths) |
| 181–201 | 过拟合、噪声与扰动、训练表现和预测表现 | [对应位置](../02_LM/04_lasso_and_structured_sparsity.md#reading-regularization-purpose) |
| 202–212 | λ、参数与超参数、网格搜索 | [对应位置](../02_LM/06_regularization_and_validation.md#reading-cross-validation) |
| 213–228 | 建模选择与外层搜索成本；AI 产品拟人化和社会议论保留原文 | [对应位置](../02_LM/06_regularization_and_validation.md#reading-cross-validation) |
| 229–255 | 变量分组、资料与行为两类信息；个人信贷和道德评价旁例保留原文 | [对应位置](../02_LM/04_lasso_and_structured_sparsity.md#reading-group-lasso) |
| 256–280 | 组惩罚、组权重、组内稀疏；纠正 L1/L1 自动带来双层稀疏的说法 | [对应位置](../02_LM/04_lasso_and_structured_sparsity.md#reading-group-lasso) |
| 281–304 | 顺序信息、差分惩罚与 fused LASSO | [对应位置](../02_LM/04_lasso_and_structured_sparsity.md#reading-fused-lasso) |
| 305–325 | 建模与求解的区别、物理关系作为约束；未沿用领域争议的笼统判断 | [对应位置](../02_LM/04_lasso_and_structured_sparsity.md#reading-fused-lasso) |
| 326–350 | Ridge、样本内积、对偶与核化；澄清样本 Gram 矩阵为 XXᵀ | [对应位置](../02_LM/05_ridge_and_duality.md#reading-dual-to-kernel) |
| 351–377 | Elastic Net、相关特征与路径；负系数和路径交叉不被当成错误 | [对应位置](../02_LM/06_regularization_and_validation.md#reading-elastic-net-example) |
| 378–386 | 核类型、宽度、次数及多超参数选择 | [对应位置](../02_LM/07_kernels_and_extensions.md#reading-kernel-shape) |
| 387–403 | 核计算规模、结构化字符串与片段计数；成本主要按样本数讨论 | [对应位置](../02_LM/07_kernels_and_extensions.md#reading-string-kernel) |
| 404–409 | 改变任务与损失、模型方法之间的迁移 | [对应位置](../02_LM/07_kernels_and_extensions.md#reading-changing-the-loss) |

## 对课堂简化与原页问题的处理

- 高维部分分别解释绝对规模、相对样本量、秩亏与病态；橘子皮比例只用于相应均匀体积采样，不推断所有真实高维数据都均匀分布或两两远离。
- 已知支撑集仍有有限样本估计误差；LASSO 的预测风险界与精确支撑恢复不同，正则化路径也不被解释成逐一解决全部最佳子集选择问题。
- 对约束形式与惩罚形式的不完全等价，使用离散模型选择例子说明非凸性；没有沿用“非光滑必然不等价”的概括。
- Group LASSO 鼓励组间稀疏，并不强制被选组内所有系数非零。将组内 L2 直接换成 L1 会退化为普通或加权 LASSO；组间及组内稀疏采用组合惩罚，并引用原研究。
- Elastic Net 不保证非负系数或路径不交叉。相同变量上的均匀分配与一维组合惩罚例子用于说明其实际作用。
- 超参数多时主要是完整网格代价高，不把它改写成交叉验证不可能使用。参数、正则化强度、学习率和特征标准化分别解释。
- 核化时的样本 Gram 矩阵是 XXᵀ，核系数 c 与前面对偶乘子 α 的比例明确；核岭回归在 c 表示下的惩罚是 cᵀKc。
- PDF 第 64 页的练习第一项确实是常数 λ。正文保留原式并给出字面解 Y；与硬阈值对应的 λI{β≠0} 单独解释，边界处两个最优解均保留。比较图以此修订版本的 L0 问题为第一栏。
- 原课件的卡方缩放和投影括号遗漏、AIC 组合数、L0 求和指标等，保留原文后给出正确解释。原课件的 7 维/6 分量、对偶项漏平方及字符串类型问题继续保留既有译注。

## 按原 PDF 恢复的转换错误

| PDF 页 | 修复内容 |
|---:|---|
| 3 | 恢复输入域到标签集的箭头和标签符号 |
| 3 | 恢复观测对所属的输入与标签笛卡尔积 |
| 3 | 恢复候选决策函数的映射箭头 |
| 7 | 恢复回归函数定义域到实数值域的映射箭头 |
| 13 | 恢复 PDF 一阶条件中原有的负号；缺少 X 的原页笔误仍由译注解释 |
| 33 | 恢复被转换成无意义符号的线性模型 Y=Xβ*+ε |
| 38 | 恢复子模型预测与投影的矩阵等式 |
| 55 | 恢复 XᵀX 的矩阵记号 |
| 57 | 恢复 Ridge 正则化矩阵 XᵀX+λI 的记号 |
| 74 | 恢复逻辑损失中的 log 运算及平方范数 |

另按 PDF 第 74 页把“线性 SVM”标签放回对应公式前。第一项一阶条件中缺少 X 等原课件自身的错误没有伪装成转换错误，仍在对应译注解释。

## 外部材料与自编例子

外部来源采用 UCLA 讲义、Stanford CS229 讲义、scikit-learn 官方文档以及 Group LASSO、物理信息学习的作者论文；具体链接见主文[来源与阅读说明](../02_LM/07_kernels_and_extensions.md#reading-sources)。使用这些材料核对概念后，按本讲符号重新组织解释，没有整段移植外部教材。

自编或承接第一讲的计算例子包括：三个点的最小二乘及扰动、重复列与近似重复列、稀疏向量的三种量、约束与惩罚的候选分数、AIC 分数表、正交设计下三种正则化、相邻差分比较、交叉验证示意分数、硬软阈值与收缩、显式特征内积、两样本核岭回归以及字符串片段计数。交叉验证表是示意计算，不是声称完成了某个真实数据实验。

## 验证

- 原文恢复、源文件哈希、原有章节顺序和图像引用均已核对。
- 手算例子已用 Python 独立重算；还检查了阈值边界、不同输入的多项式核恒等式，以及欠定/超定两种形状下的 Ridge 原始与对偶解一致性。
- 682 个数学表达式通过 KaTeX 解析，Chrome 临时 HTML 预览中 12 张图片全部加载，6 个表格列数一致；核心例子不在折叠区内，AIC 折叠区可以展开和收起。检查了最小二乘、惩罚练习、核岭回归和新增图的截图。
- 101 个本地链接及其显式锚点通过检查，18 个折叠块闭合正确，无 source-block 注释，修改范围的 git diff --check 通过。
- 本讲 339 个原文块的目标行号已随新增内容更新；同时修正第 0 块原先指向导航行的记录，使其指向课程标题。

机器可读的来源哈希、分段去向、公式修复及数值验证结果见[覆盖与验证记录](02_LM_classroom_coverage.json)。
