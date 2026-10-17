# 第二课：线性模型与稀疏性

从最小二乘出发，理解高维问题、变量选择和正则化，再通过核方法表达非线性关系。

原课件正文与核心讲解均采用英文在前、中文紧随的逐段对照；概念解释、例题和技术推导保留完整细节。公式和图片共用，较长推导可折叠阅读。

[课程目录](../README.md) · [原 PDF](02_LM.pdf) · [原文转换稿](02_LM.md)

## 按顺序阅读

| 分篇 | 阅读内容 |
|---|---|
| [1. 线性模型与最小二乘](02_LM/01_linear_models_and_least_squares.md) | 从函数到预测向量，用具体数据理解最小二乘及其推导。 |
| [2. 泛化与高维问题](02_LM/02_generalization_and_high_dimensions.md) | 理解偏差与方差、高维现象、解的唯一性与稳定性。 |
| [3. 稀疏性与模型选择](02_LM/03_sparsity_and_model_selection.md) | 比较约束和惩罚，建立模型选择与 AIC 的联系。 |
| [4. Lasso 与结构化稀疏性](02_LM/04_lasso_and_structured_sparsity.md) | 从零范数到一范数，再看分组、时间结构与惩罚的作用。 |
| [5. 岭回归与对偶](02_LM/05_ridge_and_duality.md) | 理解岭回归如何选解，推导原问题和对偶问题。 |
| [6. 正则化比较与参数选择](02_LM/06_regularization_and_validation.md) | 比较 Elastic Net、正则化路径、交叉验证和三种惩罚。 |
| [7. 非线性扩展与核方法](02_LM/07_kernels_and_extensions.md) | 用特征映射和核构造非线性预测，并理解计算成本与其他损失。 |

## 例子与概念速查

- [三个点的最小二乘](02_LM/01_linear_models_and_least_squares.md#reading-ls-example)
- [解的唯一性与敏感性](02_LM/02_generalization_and_high_dimensions.md#reading-rank-and-stability)
- [三种正则化的数值比较](02_LM/06_regularization_and_validation.md#reading-elastic-net-example)
- [交叉验证](02_LM/06_regularization_and_validation.md#reading-cross-validation)
- [三种惩罚的图像](02_LM/06_regularization_and_validation.md#reading-penalty-exercise)
- [核岭回归手算](02_LM/07_kernels_and_extensions.md#reading-kernel-ridge-example)

[课堂转录与补充来源](Translation-audit/02_LM_classroom_integration.md)
