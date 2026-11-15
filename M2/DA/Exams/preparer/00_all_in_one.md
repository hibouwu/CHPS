# 高频概念题合集（按主题）

[← 清单首页](README.md) · [计算题](00_calculations.md)

共 74 题，分 9 个主题；每个主题内按出现次数（★）从多到少排列，★ 相同时按题号。★ = 考过这道题的试卷份数。文中"见 7.4"之类的引用按题号查找。

每道题的读法：先读**解析版**（从零讲起：这道题在问什么 → 用到的工具是干什么的 → 一步一步推 → 小例子 → 常见误区 → 最终版每句话的意思），读懂后再背**最终版答案**（英文，≤5 行）。基础概念在文件里第一次出现时讲得最详细，后面的题会写"见 x.y"。

## 目录

1. 泛化、误差分解与偏差—方差（6 题，其中 ★★★ 以上 1 题）
2. 三大算法家族与 SVM（7 题，其中 ★★★ 以上 3 题）
3. 模型评估与超参数校准（9 题，其中 ★★★ 以上 1 题）
4. 决策树（11 题，其中 ★★★ 以上 1 题）
5. 线性模型、OLS 与逻辑回归（8 题，其中 ★★★ 以上 3 题）
6. 深度学习与数值优化（5 题，其中 ★★★ 以上 0 题）
7. 聚类（k-means、软 k-means、层次聚类）（12 题，其中 ★★★ 以上 3 题）
8. 稳健估计（RANSAC）与概率图模型（9 题，其中 ★★★ 以上 1 题）
9. 学习问题的基本概念与实际应用（7 题，其中 ★★★ 以上 1 题）

---

## 1. 泛化、误差分解与偏差—方差

### 1.1 What is the bias–variance trade-off? 偏差—方差权衡是什么？ ★★★★

考过：[2020 A1](../Exam_2020_zh.md) · [2023.3 Ex1 Q5](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex1 Q1](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex1 Q2](../DataML-CHPS-2024-examen_zh.md)（原问法：estimation error vs approximation error，见 1.2）

**先懂这些：** ① 期望预测误差是对"换一份训练集重新训练"取平均——[第一课 · 偏差—方差分解](../../Lectures/01_intro/04_hypotheses_and_bias_variance.md)；② 模型复杂度＝假设空间 $\mathcal H$ 的大小，正则化 $\lambda$ 等价于缩小 $\mathcal H$——[第二课 · 正则化与验证](../../Lectures/02_LM/06_regularization_and_validation.md)；③ 在 [Lab1](../../Exercises/Lab1/Lab1_zh.ipynb) 多项式／Ridge 实验里看训练误差和验证误差随复杂度的变化。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

为什么模型既不能太简单、也不能太复杂？"偏差—方差权衡"就是解释这件事的理论。这是全文第一题，下面先把后面所有题都会用到的基础词讲清楚。

**② 需要的工具**

- **数据 $(x,y)$**：$x$ 是输入（也叫**特征**），$y$ 是想预测的答案（也叫**标签**）。例：$x$＝房子面积，$y$＝房价。训练数据就是很多对 $(x_i,y_i)$。
- **模型 $h$（预测函数）**：给它一个 $x$，它输出预测值 $\hat y=h(x)$。"训练"就是根据数据找出一个好的 $h$。
- **假设空间 $\mathcal H$**：允许挑选的所有模型的集合，比如"所有直线"或"所有 9 次多项式"。$\mathcal H$ 越大，模型越灵活，也就越**复杂**。
- **损失函数 $\ell$**：衡量一次预测错了多少。回归里最常用**平方损失** $(y-\hat y)^2$：差 1 罚 1，差 3 罚 9。
- **训练误差 vs 测试误差**：训练误差是在训练用过的数据上的平均损失；测试误差是在**没见过的新数据**上的平均损失。我们真正关心的是后者（详见 1.3）。
- **欠拟合／过拟合**：欠拟合＝模型太简单，连训练数据都拟合不好；过拟合＝模型太复杂，把训练数据里的**随机噪声**也背了下来，换到新数据上反而变差。
- **偏差（bias）**：假设能换很多份不同的训练集反复训练，把所有预测取平均，这个平均值离真实值有多远。它表示模型**系统性地**偏到哪里去了。
- **方差（variance）**：换一份训练集，预测会抖动多少。它表示模型有多**不稳定**。
- **噪声 $\sigma^2$**：数据本身的随机性（如测量误差），任何模型都消除不了，是误差的下限。
- **交叉验证（cross-validation）**：把训练数据轮流分出一部分当"模拟考试"，用来估计测试误差（详见 3.1）。
- **正则化强度 $\lambda$**：给复杂度加惩罚的旋钮（详见 1.4）。

**射箭类比**：偏差＝箭的平均落点离靶心多远；方差＝箭散得有多开。好的射手两者都要小。

**③ 一步一步（推导看懂即可，不用背）**

设真实关系是 $Y=f^*(X)+\varepsilon$，噪声 $\varepsilon$ 均值为 0、方差为 $\sigma^2$。模型 $\hat f$ 是从一份随机的训练集学出来的，所以 $\hat f(x)$ 本身也是随机的，记它的平均为 $\bar f(x)=\mathbb E[\hat f(x)]$。

1. 把误差拆成三段：$Y-\hat f=(Y-f^*)+(f^*-\bar f)+(\bar f-\hat f)$。为什么：每一段正好对应一个误差来源（噪声、偏差、方差）。
2. 两边平方再取期望。交叉项都等于 0，因为噪声和训练集无关且均值为 0，而 $\bar f-\hat f$ 的均值也是 0。
3. 得到 $\mathbb E[(Y-\hat f)^2]=\underbrace{\sigma^2}_{\text{噪声}}+\underbrace{(f^*-\bar f)^2}_{\text{偏差}^2}+\underbrace{\mathbb E[(\hat f-\bar f)^2]}_{\text{方差}}$。
4. 复杂度上升时：偏差下降（模型能贴近真实函数），方差上升（对训练集的偶然性更敏感）。两者相加，测试误差随复杂度呈 **U 形**。
5. 实际怎么做：准备几个复杂度候选（多项式次数、树深、$k$、$\lambda$ 等），用**验证集或交叉验证**选出验证误差最小的那个，最后只在独立测试集上评估一次。为什么只能一次：测试集一旦参与了挑选，它就不再是"没见过的数据"，分数会偏乐观。

**④ 小例子（脚本模拟）**

真实函数 $y=\sin(2\pi x)$ 加噪声（$\sigma=0.3$，即 $\sigma^2=0.09$）。每次只给 10 个训练点，分别用 1、3、6 次多项式拟合，重复 200 次取中位数：

| 多项式次数 | 训练误差 | 测试误差 | 诊断 |
|---|---|---|---|
| 1（直线） | 0.223 | 0.333 | 太简单：偏差大，欠拟合 |
| 3 | 0.052 | 0.158 | 刚好 |
| 6 | 0.022 | 3.685 | 太复杂：方差大，过拟合 |

训练误差一路下降，测试误差先降后升，这就是 U 形。3 次多项式的测试误差 0.158 已经接近噪声下限 0.09。

**⑤ 常见误区**

- "训练误差越小越好"是错的，6 次多项式就是反例。
- 这个三项分解只对**平方损失**成立；分类问题有类似的思想，但公式不同。
- 偏差—方差与"近似误差—估计误差"相关，但不完全是同一个东西（见 1.2）。
- 不能用测试集挑模型。

**⑥ 对照最终版**

- "Expected squared error = bias² + variance + noise." → 平方损失下的期望误差＝偏差平方＋方差＋噪声。
- "A too simple model has high bias: it underfits." → 太简单 → 偏差大 → 欠拟合。
- "A too complex model has high variance: it learns the noise and overfits." → 太复杂 → 方差大 → 把噪声背下来 → 过拟合。
- "We choose the complexity … by cross-validation, then test once on a test set." → 用交叉验证选复杂度，测试集只用一次。

**最终版答案（背诵版 EN，≤5 行）：**
Expected squared error = **bias²** + **variance** + noise.
A too **simple** model has high bias: it **underfits**.
A too **complex** model has high variance: it learns the noise and **overfits**.
We choose the complexity (degree, depth, $\lambda$) by **cross-validation**, then test once on a test set.

### 1.2 What are the approximation and estimation errors, and how is the trade-off between them solved? 近似误差和估计误差是什么？二者的权衡如何处理？ ★★

考过：[2021 Ex1 Q6](../DataML-CHPS-2021-examen_zh.md)（原问法：哪些误差项能解释过拟合）· [2024 Ex1 Q2](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 三个"最优"的区别：Bayes 最优 $f^*$、类内最优 $f^*_{\mathcal H}$、学到的 $\hat f$——[第一课 · Bayes 最优与学习界](../../Lectures/01_intro/07_bayes_and_learning_bounds.md)；② 真实风险 $R$ 与经验风险 $\hat R_n$——[第一课 · 经验风险与真实风险](../../Lectures/01_intro/06_empirical_and_true_risk.md)；③ 第三项优化误差——[第六课 · 机器学习中的新权衡：三个项](../../Lectures/06_DL_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

模型的误差可以拆成"近似误差"和"估计误差"两部分。题目问：它们分别是什么？为什么此消彼长？怎么平衡？（2021 年的问法是"哪些误差项能解释过拟合"。）

**② 需要的工具**

- **三个"最优"**：
  - $f^*$：理论上最好的预测函数（**Bayes 最优**），知道真实分布才能算出来。
  - $f^*_{\mathcal H}$：在我们选定的模型族 $\mathcal H$ 里最好的那个函数（比如"最好的那条直线"）。
  - $\hat f$：我们用有限的训练数据实际学到的函数。
- **真实风险 $R$**：在全部可能数据上的平均损失，即测试误差的理论值（见 1.3）。
- **超额风险** $R(\hat f)-R(f^*)$：我们比理论最优差了多少。

**③ 一步一步**

1. 把超额风险拆成两段：$R(\hat f)-R(f^*)=\underbrace{R(\hat f)-R(f^*_{\mathcal H})}_{\text{估计误差}}+\underbrace{R(f^*_{\mathcal H})-R(f^*)}_{\text{近似误差}}$。为什么：中间插入 $f^*_{\mathcal H}$，把"模型族不够好"和"数据不够多"两个原因分开。
2. **近似误差**：即使数据无限多，模型族里最好的函数也只能做到这样。它来自 $\mathcal H$ 的表达能力不足，类似偏差。
3. **估计误差**：因为只有有限样本，学到的 $\hat f$ 比 $\mathcal H$ 里最好的差多少。它类似方差。
4. **权衡**：对嵌套的模型类，扩大 $\mathcal H$ → 近似误差**不增**（通常下降）；但在样本数 $n$ 固定时，选择变多、更容易被噪声误导 → 估计误差**往往**上升（不是必然，要看数据和学习算法）。估计误差主导时就是过拟合。
5. 若优化算法没有精确找到最小值，还要再加第三项**优化误差**（Bottou–Bousquet 三项分解，见 1.6）。
6. 怎么平衡：用正则化或模型选择**控制复杂度**，$\lambda$ 或 $\mathcal H$ 的大小由**交叉验证**确定；**增加数据**能直接降低估计误差。

**④ 小例子**

回到 1.1 的模拟（噪声下限 0.09）：

- 用直线（$\mathcal H$＝所有直线）：测试误差 0.333。直线永远画不出正弦曲线，多出来的误差主要是**近似误差**。
- 用 6 次多项式：模型族足够表达正弦曲线，近似误差很小，但只有 10 个点，测试误差 3.685，主要是**估计误差**。
- 3 次多项式两者都不大，测试误差 0.158，最好。

**⑤ 常见误区**

- 这个分解和平方损失下的偏差—方差分解**相关但不完全相同**：这里比较的是风险，适用于任何损失函数。
- 增加数据只能降低估计误差，不能降低近似误差。

**⑥ 对照最终版**

- 公式那一行 → 超额风险＝估计误差＋近似误差。
- "Approximation error: the class $\mathcal H$ is too poor (like bias). Estimation error: we learn from finite data (like variance)." → 两项各自的来源。
- "A bigger $\mathcal H$ does not increase the approximation error, but the estimation error tends to increase." → 此消彼长：近似误差不增，估计误差往往变大（不是必然）。
- "Solution: regularization / model selection by cross-validation, and more data." → 怎么平衡。

**最终版答案（背诵版 EN，≤5 行）：**
$R(\hat f)-R(f^*)=\underbrace{R(\hat f)-R(f^*_{\mathcal H})}_{\textbf{estimation}}+\underbrace{R(f^*_{\mathcal H})-R(f^*)}_{\textbf{approximation}}$.
**Approximation error**: the class $\mathcal H$ is too poor (like bias). **Estimation error**: we learn from finite data (like variance).
A bigger $\mathcal H$ does not increase the approximation error, but the estimation error **tends to increase**.
Solution: **regularization / model selection by cross-validation**, and more data.

### 1.3 What is the generalization error and how is it related to overfitting? 什么是泛化误差？它和过拟合有什么关系？ ★

考过：[2019 Q8](../Exam_2019_zh.md)

**先懂这些：** ① 损失函数 $\ell$ 与"真实风险＝期望损失"——[第一课 · 经验风险与真实风险](../../Lectures/01_intro/06_empirical_and_true_risk.md)；② 训练误差为什么是乐观估计——[第二课 · 泛化与高维（$d/n$ 项）](../../Lectures/02_LM/02_generalization_and_high_dimensions.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

什么是泛化误差？它和过拟合有什么关系？

**② 需要的工具**

- **泛化误差（真实风险）** $R(h)=\mathbb E[\ell(h(X),Y)]$：模型在**同一分布的新数据**上的平均损失。"泛化"就是"在没见过的数据上也表现好"。
- **经验误差（训练误差）** $\hat R_n(h)=\frac1n\sum_i\ell(h(x_i),y_i)$：在训练数据上的平均损失，能直接算出来。
- **期望 $\mathbb E$**：对所有可能出现的数据取平均。真实分布未知，所以 $R(h)$ 不能精确计算，只能估计。
- **留出数据**：没参与训练的数据（测试集、交叉验证的验证折）。

**③ 一步一步**

1. 我们真正想要的是泛化误差小，但它无法直接计算。
2. 能算的只有训练误差。它对**刚训练好的模型**偏乐观，因为模型就是按这些数据调出来的，相当于"拿做过的题考自己"。
3. **过拟合**：模型太复杂，把训练数据里的噪声也记住了。表现为训练误差很小，泛化误差却很大（方差高）。
4. 两者之差通常随模型复杂度增大而变大，随样本量 $n$ 增大而缩小。
5. 所以泛化误差必须在**留出数据**上估计：测试集或交叉验证（见 3.1）。

**④ 小例子**

1.1 的模拟里，6 次多项式的训练误差是 0.022，几乎为 0；测试误差却是 3.685，差了 160 多倍。这个巨大的差距就是过拟合的信号。

**⑤ 常见误区**

- 把训练误差当作泛化误差的估计。
- 以为泛化误差可以精确算出来；它只能在新数据上估计。

**⑥ 对照最终版**

- "The generalization error is the expected loss on new data: $R(h)=\mathbb E[\ell(h(X),Y)]$." → 定义。
- "The training error is too optimistic." → 训练误差偏乐观。
- "Overfitting: the training error is very low but the generalization error is high, because the model learned the noise." → 过拟合的表现和原因。
- "We estimate it on a test set or by cross-validation." → 怎么估计。

**最终版答案（背诵版 EN，≤5 行）：**
The generalization error is the expected loss on **new data**: $R(h)=\mathbb E[\ell(h(X),Y)]$.
The training error is too optimistic.
**Overfitting**: the training error is very low but the generalization error is high, because the model learned the noise.
We estimate it on a **test set** or by **cross-validation**.

### 1.4 What is the role of penalization in machine learning? 惩罚项（正则化）在机器学习中起什么作用？ ★

考过：[2023.11 Ex1 Q7](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① 带惩罚优化是"机器学习算法之母"——[第二课 · Lasso 与结构化稀疏（Penalized optimization）](../../Lectures/02_LM/04_lasso_and_structured_sparsity.md)；② Ridge 为什么让方程可解——[第二课 · 岭回归与对偶](../../Lectures/02_LM/05_ridge_and_duality.md)；③ $\ell_1$／$\ell_2$／Elastic Net 的对比——[第二课 · 正则化与验证](../../Lectures/02_LM/06_regularization_and_validation.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

在训练目标里加惩罚项（正则化）起什么作用？

**② 需要的工具**

- **惩罚项 $\Omega(\theta)$**：衡量模型"有多复杂"的量，例如系数的平方和 $\|\theta\|_2^2$（$\ell_2$）或绝对值和 $\|\theta\|_1$（$\ell_1$）。
- **正则化强度 $\lambda$**：惩罚的权重，是一个**超参数**，用交叉验证选（见 3.1）。
- **病态问题**：解不唯一或对数据的微小变化极其敏感的问题，例如特征数多于样本数时的最小二乘（见 5.7）。
- **稀疏**：大部分系数恰好为 0，相当于自动挑选变量（见 5.6）。

**③ 一步一步**

1. 目标从"只让训练误差小"改成 $\hat R_n(\theta)+\lambda\,\Omega(\theta)$：既要拟合好，又不能太复杂。
2. **作用一：控制复杂度、防止过拟合**。接受一点偏差，换来方差大幅下降，提升泛化（见 1.1）。
3. **作用二：稳定病态问题**。例如 Ridge 的 $\ell_2^2$ 惩罚，在 $d>n$ 或特征共线时让 $X^TX+\lambda I$ 可逆，解变得唯一且稳定（见 5.5）。
4. **作用三：注入结构先验**。$\ell_1$（Lasso）让很多系数恰好为 0，实现变量选择；分组惩罚可以整组选择变量。
5. $\lambda$ 太大 → 模型被压得太简单 → 欠拟合；$\lambda=0$ → 没有正则化。
6. 区分：$\theta$ 是学出来的参数，$\lambda$ 是人定的超参数。

**④ 小例子**

5.3 的三个点，一维 Ridge 的斜率是 $\frac{S_{xy}}{S_{xx}+\lambda}=\frac{3}{2+\lambda}$：

- $\lambda=0$：1.5（就是 OLS）；
- $\lambda=1$：1.0；
- $\lambda=4$：0.5。

$\lambda$ 越大，斜率被压得越接近 0，模型越"保守"。

**⑤ 常见误区**

- 以为正则化总是越强越好；过强会欠拟合。
- 截距通常不惩罚。

**⑥ 对照最终版**

- "We minimize $\hat R_n(\theta)+\lambda\Omega(\theta)$." → 带惩罚的目标。
- "(1) controls complexity …; (2) stabilizes ill-posed problems …; (3) adds structure, e.g. $\ell_1$ gives sparsity." → 三个作用。
- "$\lambda$ is a hyperparameter chosen by CV." → $\lambda$ 是超参数。

**最终版答案（背诵版 EN，≤5 行）：**
We minimize $\hat R_n(\theta)+\lambda\,\Omega(\theta)$. The penalty:
(1) **controls complexity**: a little more bias, much less variance, less overfitting;
(2) **stabilizes** ill-posed problems (Ridge: $X^TX+\lambda I$ is invertible);
(3) adds **structure**, e.g. $\ell_1$ gives **sparsity**. $\lambda$ is a hyperparameter chosen by CV.

### 1.5 Are generalization error and overfitting relevant for clustering? 泛化误差和过拟合的概念适用于聚类吗？ ★

考过：[2019 Q8](../Exam_2019_zh.md)

**先懂这些：** ① k-means 目标（簇内平方和）随 $k$ 单调下降——[Lab4](../../Exercises/Lab4/Lab4_zh.ipynb) 簇数选择部分；② 与 7.4（如何选簇数）一起复习。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

泛化误差、过拟合这些概念，对没有标签的聚类也适用吗？

**② 需要的工具**

- **聚类的"模型"**：比如 k-means 的 $k$ 个中心（见 7.1）。
- **惯性 $J$**：簇内平方和，$k$ 越大越小。
- **稳定性**：换一份样本（重采样）后，聚类结果是否基本一样。
- **BIC**：概率模型的选择准则，拟合好加分、参数多扣分（见 7.4）。

**③ 一步一步**

1. **适用**。聚类同样是在有限样本上拟合一个模型，我们希望学到的结构对**同一分布的新样本**也成立。
2. 惯性 $J$ 随 $k$ 单调下降，$k=N$ 时为 0（每个点自成一簇）。这时模型完全"背下"了样本。
3. $k$ 太大就是对当前样本**过拟合**：得到的簇不稳定，换一批数据就变样。
4. 没有标签，只能**间接**评估泛化：重采样下的稳定性；在**留出数据**上算惯性或对数似然（如 GMM）；用 BIC 等带惩罚的准则。

**④ 小例子**

7.4 的数据 $\{1,2,3,10,11,12\}$：$k=2$ 时 $J=4$，$k=6$ 时 $J=0$。$k=6$ 的"完美"结果毫无意义，换一批新点它就完全对不上了。

**⑤ 常见误区**

- 认为聚类没有标签，就不存在过拟合。

**⑥ 对照最终版**

- "Yes. The inertia always decreases when $k$ grows (0 when $k=N$)." → 适用；惯性随 $k$ 单调下降。
- "So a too large $k$ overfits the sample and gives unstable clusters." → $k$ 太大会过拟合。
- "Without labels, we check generalization by stability under resampling, held-out likelihood, or BIC." → 间接评估的方法。

**最终版答案（背诵版 EN，≤5 行）：**
**Yes.** The inertia always decreases when $k$ grows (0 when $k=N$).
So a too large $k$ **overfits** the sample and gives unstable clusters.
Without labels, we check generalization by **stability under resampling**, held-out likelihood, or **BIC**.

### 1.6 What is the impact of computation time (fixed resources) when the sample size grows? 计算资源固定时，样本量增大对计算时间有什么影响？ ★

考过：[2021 Ex1 Q6](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** ① 三项误差分解中的优化误差——[第六课 · 机器学习中的新权衡：三个项](../../Lectures/06_DL_zh.md)；② SGD 每步代价与 $n$ 无关——[第六课 · 反向传播与梯度下降](../../Lectures/06_DL_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

计算资源固定时，样本量越来越大，计算时间会带来什么影响？

**② 需要的工具**

- **三项误差**：近似误差、估计误差、**优化误差**（优化没算到底而多出来的误差），见 1.2。
- **一次完整遍历的代价**：精确地算一次梯度或损失，要把所有样本都过一遍，代价至少是 $O(n)$。
- **SGD／小批量**：每步只用少量样本，代价与 $n$ 无关（见 6.1）。

**③ 一步一步**

1. 样本越多，**估计误差**越小，这是好事。
2. 但精确求解（把经验风险最小化到底）的计算量随 $n$ 增长。时间预算固定时，已经算不完了。
3. 于是问题从"数据受限"变成"**时间受限**"（**大规模学习**），必须接受更大的**优化误差**。权衡变成近似、估计、优化三项之间的平衡。
4. 实际做法：改用每步代价与 $n$ 无关的算法，如 **SGD** 或小批量；或者只用一部分数据训练。
5. 结论：在海量数据上做粗略的优化，往往比在少量数据上做精确的优化泛化得更好。

**④ 小例子**

1 亿个样本，每个样本算一次梯度要 1 微秒：

- 完整梯度一次要 100 秒，1 小时只能走 36 步；
- 批大小 100 的 SGD 一步只要 100 微秒，1 小时能走 3600 万步。

**⑤ 常见误区**

- 以为数据越多越好、不用考虑计算时间。

**⑥ 对照最终版**

- "More data reduces the estimation error, but each exact pass over the data costs $O(n)$." → 数据多的好处和代价。
- "With fixed time, we must accept a larger optimization error." → 时间固定，接受优化误差。
- "So we use cheap methods: SGD / mini-batches, or a subsample." → 用便宜的方法。
- "A rough optimum on much data is often better than an exact optimum on little data." → 结论。

**最终版答案（背诵版 EN，≤5 行）：**
More data reduces the **estimation error**, but each exact pass over the data costs $O(n)$.
With fixed time, we must accept a larger **optimization error**.
So we use cheap methods: **SGD / mini-batches**, or a subsample.
A rough optimum on much data is often better than an exact optimum on little data.

---

## 2. 三大算法家族与 SVM

> 2023.3 和 2024 年把"三大家族各举例"合成一道题，2021 年把局部方法和全局方法分成两道题。这里拆成局部、全局、集成三道题，每道都要求**原理＋例子**。

### 2.1 What is the principle of local methods? Give an example and its hyperparameters. 局部方法的原理是什么？举一个例子并说明超参数。 ★★★

考过：[2021 Ex1 Q4](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex1 Q4](../DataML-CHPS-2022-examen_zh.md) · [2024 Ex1 Q1](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 三大家族的定义——[第一课 · 算法家族（1 Local methods）](../../Lectures/01_intro/02_algorithms_and_pipeline.md)；② "无需优化的正则化：直方图"和 k-NN——[第五课 · 基于局部性的非线性模型、k 近邻](../../Lectures/05_NLM_zh.md)；③ [Lab2](../../Exercises/Lab2/Lab2_zh.ipynb) 的 k-NN 与决策树实验。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

什么叫"局部方法"？举一个例子，并说出它的超参数（训练前要人来定的设置）。

**② 需要的工具**

- **距离**：用来衡量两个样本"像不像"。最常用欧氏距离 $\sqrt{\sum_j(x_j-x'_j)^2}$，也可以用曼哈顿距离 $\sum_j|x_j-x'_j|$。距离越小越相似。
- **多数投票／局部平均**：分类时看邻居里哪个类最多；回归时把邻居的 $y$ 取平均。
- **超参数**：训练之前由人设定、算法不会自己学的量（详见 3.4），用交叉验证来选（见 3.1）。
- **维度灾难**：特征维数很高时，所有点彼此都离得很远，"最近的邻居"其实也不像，局部方法就失效了。

**③ 一步一步（以 $k$ 近邻为例）**

1. 选定 $k$ 和距离。为什么：这两项决定"谁算邻居"。
2. 来了新点 $x$，计算它到所有训练点的距离。
3. 取最近的 $k$ 个训练点。为什么：假设相似的输入有相似的输出。
4. 分类取多数类，回归取平均值。
5. 没有真正的"训练"过程（只是把数据存起来），计算量都在预测时。

**$k$ 的意义**："正则化"就是邻域的大小。$k=1$：边界跟着每个点弯曲，连噪声点也照抄，偏差低、方差高，**过拟合**；$k$ 很大（极端 $k=N$）：永远输出全体的多数类，偏差高、方差低，**欠拟合**。

决策树也是局部方法：它把空间切成一个个格子，格子里的点投票（见 4.2），超参数是最大深度、叶节点最少样本数等。

**④ 小例子**

训练点（一维）：1(A)、2(A)、3.5(B)、6(B)、8(B)。新点 $x=3$，到各点的距离依次是 2、1、0.5、3、5。

- $k=1$：最近的是 3.5(B) → 预测 **B**。
- $k=3$：最近三个是 3.5(B)、2(A)、1(A) → A 占 2 票 → 预测 **A**。

换一个 $k$ 答案就变了，所以 $k$ 是关键超参数，要用交叉验证选。

**⑤ 常见误区**

- 特征量纲不同（如"米"和"毫米"）会让距离被大数字主导，要先**标准化**。
- 二分类时 $k$ 取偶数可能平票，通常取奇数。
- 高维数据上效果差（维度灾难）。

**⑥ 对照最终版**

- "Local methods predict at $x$ with the training points near $x$ … No global optimization." → 只看 $x$ 附近的训练点投票或平均，没有全局目标函数要优化。
- "Example: k-nearest neighbors. Hyperparameters: $k$ and the distance, chosen by cross-validation." → 例子是 k-NN，超参数是 $k$ 和距离，用交叉验证选。
- "Small $k$: overfitting; large $k$: underfitting." → $k$ 小过拟合，$k$ 大欠拟合。

**最终版答案（背诵版 EN，≤5 行）：**
Local methods predict at $x$ with the training points **near $x$**: **majority vote** (classification) or **average** (regression). No global optimization.
Example: **k-nearest neighbors**. Hyperparameters: **$k$** and the **distance**, chosen by cross-validation.
Small $k$: overfitting; large $k$: underfitting. (Decision trees are also local.)

### 2.2 What is the principle of global methods? Give an example. 全局方法的原理是什么？举一个例子。 ★★★

考过：[2021 Ex1 Q5](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex1 Q4](../DataML-CHPS-2022-examen_zh.md) · [2024 Ex1 Q1](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① [第一课 · 算法家族（2 Global methods: functional optimization）](../../Lectures/01_intro/02_algorithms_and_pipeline.md)；② 经验风险最小化（ERM）——[第一课 · 经验风险与真实风险](../../Lectures/01_intro/06_empirical_and_true_risk.md)；③ 第五课"在庞大的函数空间中最小化带惩罚的凸风险"——[第五课 · 推断原则、高效算法](../../Lectures/05_NLM_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

什么叫"全局方法"？它和局部方法的根本区别是什么？举一个例子。

**② 需要的工具**

- **参数 $\theta$**：模型里等着被学出来的数字。例如直线 $\hat y=ax+b$ 的参数是 $\theta=(a,b)$。
- **经验风险最小化（ERM）**：在训练集上找平均损失最小的参数，即 $\min_\theta\frac1n\sum_i\ell(h_\theta(x_i),y_i)$。"经验风险"就是训练集上的平均损失。
- **惩罚项 $\lambda\Omega(\theta)$**：防止模型太复杂的附加项（详见 1.4）。
- **优化算法**：真正把最小值找出来的方法，有闭式解或梯度下降（见 6.2）。

**③ 一步一步**

1. 选一个模型族 $h_\theta$（例如所有直线）。为什么：先限定"在哪里找"。
2. 选损失函数：回归用平方损失，分类用对数损失或 hinge 损失。为什么：定义什么叫"错"。
3. 可以加惩罚项 $\lambda\Omega(\theta)$。为什么：控制复杂度。
4. 用优化算法在**全部训练样本**上求 $\hat\theta=\arg\min_\theta\frac1n\sum_i\ell(h_\theta(x_i),y_i)+\lambda\Omega(\theta)$。
5. 之后对任何新 $x$ 都用**同一个** $\hat\theta$ 预测，训练数据可以丢掉。

和局部方法对比：k-NN 每次预测都要回去找邻居；全局方法把所有数据"浓缩"成一组参数，在整个输入空间统一使用。

**④ 小例子**

用直线拟合房价：$\theta=(a,b)$，最小化 $\sum_i(y_i-ax_i-b)^2$（就是 OLS，见 5.3）。在 5.3 的小例子里会算出 $a=1.5$、$b\approx0.83$，之后任何新面积 $x$ 直接代入 $1.5x+0.83$ 即可。

常见的全局方法：**Ridge／Lasso 回归**（平方损失＋$\ell_2$／$\ell_1$ 惩罚）、**逻辑回归**（对数损失）、**SVM**（hinge 损失＋$\|w\|^2$）、神经网络；课件也把 Boosting 列入。复杂度由 $\mathcal H$ 的选择和 $\lambda$ 控制。

**⑤ 常见误区**

- "全局"指的是优化**一个覆盖全部数据的整体目标**，不是"一定能找到全局最优"。目标非凸时（如神经网络），只能保证局部最优。

**⑥ 对照最终版**

- "Global methods choose one function $h_\theta$ by minimizing a criterion on all the data." → 在全部训练数据上最小化一个准则，选出一个函数。
- 公式那一行 → 带惩罚的经验风险最小化；"The same parameters are used everywhere" → 训练完后到处都用同一组参数。
- "Examples: Ridge / Lasso, logistic regression, SVM." → 三个例子。"Complexity is controlled by the class and by $\lambda$." → 复杂度由模型族和 $\lambda$ 控制。

**最终版答案（背诵版 EN，≤5 行）：**
Global methods choose one function $h_\theta$ by **minimizing a criterion on all the data**:
$\min_\theta\frac1n\sum_i\ell(h_\theta(x_i),y_i)+\lambda\Omega(\theta)$. The same parameters are used everywhere.
Examples: **Ridge / Lasso**, **logistic regression**, **SVM**. Complexity is controlled by the class and by $\lambda$.

### 2.3 What are the two main ingredients of ensemble methods? Give an example. 集成方法的两个主要要素是什么？举一个例子。 ★★★

考过：[2023.3 Ex1 Q4](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex1 Q5](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex1 Q1](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① [第一课 · 算法家族（3 Ensemble methods: resampling and aggregation）](../../Lectures/01_intro/02_algorithms_and_pipeline.md)；② Bagging、随机森林、Boosting、bootstrap——[第五课 · 集成方法](../../Lectures/05_NLM_zh.md)；③ [Lab3](../../Exercises/Lab3/Lab3_zh.ipynb) 的集成学习部分。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

集成方法（把很多模型组合起来）靠哪两件事起作用？举一个例子。

**② 需要的工具**

- **基学习器**：被组合的单个模型，最常用决策树（见 4.2）。
- **bootstrap（自助采样）**：从 $n$ 个训练点里**有放回地**抽 $n$ 个，同一个点可能被抽到多次，有些点一次也抽不到。平均每份只包含约 63.2% 的不同点。作用：用同一份数据造出很多份"略有不同"的训练集。
- **方差与相关系数 $\rho$**：$\rho$ 衡量两个模型的错误有多同步，$\rho=1$ 表示总是一起错。
- **多数投票／平均**：把多个预测合成一个。

**③ 一步一步**

**Bagging／随机森林**（并行）：

1. 抽 $B$ 份 bootstrap 样本。为什么：制造差异。
2. 每份训练一棵深树。随机森林在**每次分裂时只随机看一部分特征**。为什么：让树之间更不一样，降低 $\rho$。
3. 预测时回归取平均、分类多数投票。为什么：各棵树的随机错误互相抵消。

**Boosting**（串行）：依次训练很多浅树，每一棵专门修正前面模型的错误（加大分错样本的权重，或直接拟合残差），最后加权求和。

为什么平均能变好：$B$ 个方差为 $\sigma^2$、相关系数为 $\rho$ 的预测器取平均后，方差是 $\rho\sigma^2+\frac{1-\rho}{B}\sigma^2$。$B$ 越大第二项越小，$\rho$ 越小第一项越小。所以 **Bagging／随机森林主要降方差**，**Boosting 主要降偏差**。

**④ 小例子**

- 方差：$\sigma^2=1$、$\rho=0.3$、$B=100$ → $0.3+0.7/100=0.307$，比单棵树的 1 小很多；若 $\rho=0$ → 只剩 $0.01$；若 $\rho=1$ → 还是 1，平均毫无作用。
- 投票：3 个**互相独立**的分类器各有 70% 正确率，多数投票的正确率是 $0.7^3+3\times0.7^2\times0.3=0.784$，比任何单个都高。

**⑤ 常见误区**

- 如果所有基学习器一模一样（误差完全相关），集成没有任何好处，所以"差异性"是必要条件。
- 不要把降方差和降偏差说反：Bagging 降方差，Boosting 降偏差。

**⑥ 对照最终版**

- "(1) Diversity: train many base models on random versions of the data (bootstrap, random features), or one after another on the errors (boosting)." → 要素一：用随机化或串行纠错制造差异。
- "(2) Aggregation: average (regression) or majority vote (classification)." → 要素二：聚合。
- "Bagging / random forests reduce variance; boosting reduces bias." → 各自降什么。
- "Example: random forest = many deep trees + bootstrap + random features." → 例子：随机森林。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **Diversity**: train many base models on random versions of the data (**bootstrap**, random features), or one after another on the errors (**boosting**).
(2) **Aggregation**: **average** (regression) or **majority vote** (classification).
Bagging / random forests reduce **variance**; boosting reduces **bias**.
Example: **random forest** = many deep trees + bootstrap + random features.

### 2.4 What are the two key principles of SVM? SVM 的两个核心原理是什么？ ★★

考过：[2019 Q6](../Exam_2019_zh.md) · [2020 A4](../Exam_2020_zh.md)

**先懂这些：** ① 线性可分、感知机与间隔——[第五课 · 感知机、Novikoff 定理](../../Lectures/05_NLM_zh.md)；② 最大间隔的优化问题与对偶、支持向量——[第五课 · 场景 1：具有良好泛化能力的超平面、KKT 条件](../../Lectures/05_NLM_zh.md)；③ 核的思想——[第二课 · 非线性扩展与核方法](../../Lectures/02_LM/07_kernels_and_extensions.md)；④ [Lab2](../../Exercises/Lab2/Lab2_zh.ipynb) SVM 部分。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

支持向量机（SVM）有两个核心思想，分别是什么？

**② 需要的工具**

- **分离超平面**：二维时是一条直线，三维时是一个平面，把两类点分开。写作 $w^Tx+b=0$，$w$ 决定方向，$b$ 决定位置。
- **间隔（margin）**：分界线到两边最近样本的距离之和，等于 $2/\|w\|$。间隔越大，分界线离两类都越远，对新数据越不容易分错。
- **hinge 损失** $\max(0,1-y\,f(x))$，其中 $y\in\{-1,+1\}$：点分对而且离分界线足够远（$y f(x)\ge1$）时损失为 0；越界越多，罚得越多。
- **支持向量**：落在间隔边界上或间隔内的那些点。只有它们决定最终的分界线。
- **核函数** $K(x,x')=\langle\phi(x),\phi(x')\rangle$：直接算出两个点映射到高维空间后的内积，而不用真正去做这个映射。

**③ 一步一步**

1. **最大间隔**：在所有能把两类分开的直线中，选间隔最大的那条，即 $\min\frac12\|w\|^2$，约束是每个点都在正确一侧且离边界至少 1：$y_i(w^Tx_i+b)\ge1$。为什么：间隔大＝留有余地＝泛化好。
2. **软间隔**：数据不能完全分开时，允许少数点越界，并按 hinge 损失罚：$\min\frac12\|w\|^2+C\sum_i\max(0,1-y_i(w^Tx_i+b))$。$C$ 大：几乎不容忍错误（容易过拟合）；$C$ 小：允许更多错误、间隔更宽。这是一个**凸**问题，能找到全局最优。
3. **核技巧**：求解过程和最终的预测只用到样本之间的内积 $x_i^Tx_j$。把内积换成核函数 $K(x_i,x_j)$（多项式核、高斯 RBF 核），就等于在高维空间里找线性分界线，回到原空间看就是**弯曲的边界**。
4. 超参数：$C$、核的种类及参数（如 RBF 的 $\gamma$），用交叉验证选。

**④ 小例子**

- 间隔：$w=(1,1)$ 时，间隔 $=2/\sqrt2\approx1.414$。
- hinge 损失：$y f(x)=2$（分对且远）→ 0；$y f(x)=0.5$（分对但太近）→ 0.5；$y f(x)=-1$（分错）→ 2。
- 核的直觉：一维上 A 类在 $x=-2$ 和 $x=2$，B 类在 $x=0$，一条竖线分不开。映射成 $\phi(x)=(x,x^2)$ 后，A 类的 $x^2=4$，B 类的 $x^2=0$，用 $x^2=2$ 就能分开。

**⑤ 常见误区**

- 不是所有训练点都影响结果，只有支持向量才影响。
- $C$ 和正则化强度的方向相反：$C$ 越大，正则化越弱。

**⑥ 对照最终版**

- "(1) Maximum margin: … the largest margin $2/\|w\|$. With errors: … (hinge loss, convex). Only the support vectors matter." → 原理一：最大间隔、软间隔、支持向量。
- "(2) Kernel trick: replace $x_i^Tx_j$ by $K(x_i,x_j)$ (e.g. RBF) to get non-linear boundaries." → 原理二：核技巧。
- "Hyperparameters: $C$ and the kernel." → 超参数。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **Maximum margin**: choose the hyperplane with the largest margin $2/\|w\|$. With errors: $\min\frac12\|w\|^2+C\sum_i\max(0,1-y_i(w^Tx_i+b))$ (**hinge loss**, convex). Only the **support vectors** matter.
(2) **Kernel trick**: replace $x_i^Tx_j$ by $K(x_i,x_j)$ (e.g. RBF) to get **non-linear** boundaries.
Hyperparameters: $C$ and the kernel.

### 2.5 Why are convex losses sometimes used in learning? 为什么学习中有时使用凸损失？ ★

考过：[2021 Ex1 Q5](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** ① 0–1 损失与分类风险——[第三课 · 评价准则：分类器的误差](../../Lectures/03_LMC_zh.md)；② ERM 的缺点与凸替代——[第五课 · 经验风险最小化（ERM）、高效算法](../../Lectures/05_NLM_zh.md)；③ 凸性带来的计算优势——[第二课 · Lasso（The power of convexity）](../../Lectures/02_LM/04_lasso_and_structured_sparsity.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

为什么机器学习里经常用"凸"的损失函数？

**② 需要的工具**

- **0–1 损失** $\mathbf 1\{y\,h(x)\le0\}$：分错记 1，分对记 0。这是分类最自然的损失。（这里 $y\in\{-1,+1\}$，$y\,h(x)>0$ 表示分对。）
- **凸函数**：形状像一个碗（碗底可能是一个点，也可能是一片平地），没有"假谷底"。凸问题里，任何局部最低点都是全局最低点。
- **NP 难**：目前没有已知的高效算法，规模一大就算不动。
- **替代损失（surrogate）**：用来代替 0–1 损失、更容易优化的函数，这里关心的是**凸**替代损失。它**不一定**是 0–1 损失的上界：hinge 和指数损失恰好处处 $\ge$ 0–1 损失，但自然对数的 logistic 损失 $\log(1+e^{-m})$ 在 $m=0$ 时只有 0.693 $<1$（见下表）；改用以 2 为底的 $\log_2(1+e^{-m})$ 才是上界。"替代损失"和"凸上界"是两个不同的概念。

**③ 一步一步**

1. 0–1 损失不连续也不凸（在 0 处突然跳变），直接最小化训练集上的 0–1 损失一般是 **NP 难**的。
2. 于是换成**凸替代损失**：hinge $\max(0,1-yh(x))$（SVM）、logistic $\log(1+e^{-yh(x)})$（逻辑回归）、指数损失 $e^{-yh(x)}$（AdaBoost）或平方损失。
3. 配合线性模型（或对参数线性的模型），整个训练问题就是**凸优化问题**：局部最优即全局最优。
4. 可以用梯度法、牛顿法或二次规划**高效、可靠**地求解，不会卡在坏的局部最优。
5. 在温和条件下，这些替代损失是**分类校准**的：最小化它们，最终仍会趋向理论最优的 Bayes 分类器。

**④ 小例子**

令 $m=y\,h(x)$（$m>0$ 表示分对，越大越"有把握"）：

| $m$ | 0–1 损失 | hinge | logistic |
|---|---|---|---|
| −1（分错） | 1 | 2 | 1.313 |
| 0（在边界上） | 1 | 1 | 0.693 |
| 0.5（分对但不够远） | 0 | 0.5 | 0.474 |
| 2（分对且有把握） | 0 | 0 | 0.127 |

替代损失是平滑变化的，能告诉优化算法"往哪个方向改进"；0–1 损失只有 0 和 1 两个值，没有这样的信息。

**⑤ 常见误区**

- 凸性要"损失凸"加上"模型对参数线性"才能保证；深度网络即使用凸损失，整体也不是凸问题。
- 以为替代损失都必须是 0–1 损失的上界：上表里自然对数的 logistic 损失在 $m=0$、$m=-1$ 附近就小于 0–1 损失（如 $m=0$：0.693 < 1）。

**⑥ 对照最终版**

- "The 0–1 loss is not convex and not continuous: minimizing it is NP-hard." → 为什么不直接用 0–1 损失。
- "A convex surrogate (hinge, logistic, squared) with a linear model gives a convex problem." → 换成凸替代。
- "Then every local minimum is global, and gradient methods solve it fast and reliably." → 凸的好处。

**最终版答案（背诵版 EN，≤5 行）：**
The **0–1 loss** is not convex and not continuous: minimizing it is **NP-hard**.
A **convex surrogate** (hinge, logistic, squared) with a linear model gives a **convex problem**.
Then every local minimum is **global**, and gradient methods solve it fast and reliably.

### 2.6 What other choices of loss lead to practical methods? 还有哪些损失选择能得到实用的方法？ ★

考过：[2021 Ex1 Q5](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** ① 保持建模框架、只换损失——[第二课 · 非线性扩展（Generalizations: changing what a wrong prediction means）](../../Lectures/02_LM/07_kernels_and_extensions.md)；② 深度学习的非凸损失与 SGD——[第六课 · 深度学习](../../Lectures/06_DL_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

除了上面的凸替代损失，还有哪些损失函数能得到实用的方法？

**② 需要的工具**

- **残差** $r=y-h(x)$：预测差了多少。
- **离群点**：远离大多数数据的点。平方损失会把它的影响放大很多倍。
- **分位数**：例如 90% 分位数，表示有 90% 的数据低于这个值。

**③ 一步一步（每种损失解决什么问题）**

1. **绝对值损失** $|y-h(x)|$：对应预测中位数，**对离群点稳健**，因为大误差只按线性增长。
2. **Huber 损失**：残差小时用平方（光滑、好优化），残差大时改用线性（稳健），兼顾两者。
3. **$\varepsilon$-不敏感损失** $\max(0,|y-h(x)|-\varepsilon)$：用于 SVR（见 2.7），误差小于 $\varepsilon$ 不计，解是稀疏的。
4. **分位数（pinball）损失**：用来预测分位数，例如"九成概率不会超过多少"。
5. **交叉熵**：用于多分类的概率输出。
6. **非凸损失**也可以用：配合随机梯度下降，深度神经网络就是这样训练的，只是不保证全局最优。
7. 总原则：损失应当反映实际应用中**错误预测的代价**。

**④ 小例子**

残差 $r=3$ 时，不同损失的惩罚（Huber 取 $\delta=1$，小残差时用 $\frac12r^2$）：

- 平方损失 $\frac12r^2=4.5$；
- 绝对值损失 3；
- Huber $=\delta(|r|-\frac12\delta)=2.5$。

而残差 $r=0.5$ 时，Huber 等于 $\frac12r^2=0.125$，和平方损失一样光滑。

**⑤ 常见误区**

- 以为只有平方损失和 0–1 损失两种选择。

**⑥ 对照最终版**

- "Absolute and Huber losses (robust to outliers), ε-insensitive loss (SVR), quantile loss, cross-entropy (multi-class)." → 几种实用的损失。
- "Even non-convex losses work with SGD (deep learning), but with no global guarantee." → 非凸损失也可用。
- "The loss should match the real cost of errors." → 选择原则。

**最终版答案（背诵版 EN，≤5 行）：**
**Absolute** and **Huber** losses (robust to outliers), **ε-insensitive** loss (SVR), **quantile** loss, **cross-entropy** (multi-class).
Even **non-convex** losses work with **SGD** (deep learning), but with no global guarantee.
The loss should match the real cost of errors.

### 2.7 Can SVM be used for regression? SVM 能用于回归吗？ ★

考过：[2019 Q6](../Exam_2019_zh.md)

**先懂这些：** 先掌握 2.4 的最大间隔和 2.6 的 $\varepsilon$-不敏感损失；[Lab3](../../Exercises/Lab3/Lab3_zh.ipynb) 里有回归方法对比。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

SVM 能用来做回归（预测数字）吗？

**② 需要的工具**

- **SVM 的最大间隔思想**（见 2.4）。
- **$\varepsilon$-管道**：围绕预测曲线上下各宽 $\varepsilon$ 的一条带子。
- **$\varepsilon$-不敏感损失** $\max(0,|y-f(x)|-\varepsilon)$：点落在带子里不罚，越出带子才按超出的部分罚（见 2.6）。

**③ 一步一步**

1. **可以，就是支持向量回归（SVR）**。
2. 不再在两类之间找间隔，而是拟合 $f(x)=w^Tx+b$，希望尽量多的点落在管道 $f(x)\pm\varepsilon$ 里（上下各 $\varepsilon$，总宽 $2\varepsilon$）。
3. 目标：$\min\frac12\|w\|^2+C\sum_i\max(0,|y_i-f(x_i)|-\varepsilon)$。$\|w\|^2$ 让函数尽量"平坦"，起到分类中间隔的作用。
4. **严格落在管道内部**的点系数为 0，不是支持向量；支持向量只能在管道**边界上或管道外**（边界上的点损失为 0，但系数可以非零）。所以解是稀疏的。
5. **核技巧**照样可以用，于是能做非线性回归。超参数是 $C$、$\varepsilon$ 和核参数。

**④ 小例子**

取 $\varepsilon=0.5$：某点残差 0.3（在管道内）→ 损失 0；残差 0.8 → 损失 $0.8-0.5=0.3$。

**⑤ 常见误区**

- 以为 SVM 只能做分类。

**⑥ 对照最终版**

- "Yes: SVR. We fit $f(x)=w^Tx+b$ with a tube $f(x)\pm\varepsilon$: errors smaller than ε cost nothing (ε-insensitive loss)." → SVR 和 ε-管道（上下各 ε）。
- "We minimize $\frac12\|w\|^2+C\sum_i\max(0,|y_i-f(x_i)|-\varepsilon)$." → 目标函数。
- "Points strictly inside the tube are not support vectors (sparse solution). Kernels give non-linear regression." → 管道内部的点不是支持向量（边界上和管道外的点才可能是）；核技巧。

**最终版答案（背诵版 EN，≤5 行）：**
**Yes: SVR.** We fit $f(x)=w^Tx+b$ with a **tube $f(x)\pm\varepsilon$**: errors smaller than ε cost nothing (**ε-insensitive loss**).
We minimize $\frac12\|w\|^2+C\sum_i\max(0,|y_i-f(x_i)|-\varepsilon)$.
Points strictly inside the tube are **not support vectors** (sparse solution). Kernels give non-linear regression.

---

## 3. 模型评估与超参数校准

### 3.1 Give an example of a hyperparameter and explain how to calibrate it. 举一个超参数的例子并说明如何校准。 ★★★

考过：[2020 A3](../Exam_2020_zh.md)（决策树超参数如何校准）· [2021 Ex1 Q7](../DataML-CHPS-2021-examen_zh.md) · [2024 Ex1 Q4](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 交叉验证具体做什么、为什么先标准化——[第二课 · 正则化与验证（Tuning the hyperparameters: Cross-validation）](../../Lectures/02_LM/06_regularization_and_validation.md)；② 训练／验证／测试三分——[作业一第 4 题：数据划分](../../Exercises/Assignment1/guide/04_data_splitting.md)；③ [Lab1](../../Exercises/Lab1/Lab1_zh.ipynb) 的验证部分。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

举一个超参数的例子，并说明怎样确定它取什么值（"校准" calibration）。

**② 需要的工具**

- **参数 vs 超参数**：参数由算法从数据里学（如直线的斜率）；超参数由人在训练前设定（如树的最大深度），算法不会自己改（详见 3.4）。
- **训练集／验证集／测试集**：训练集用来学参数；验证集用来比较不同的超参数；测试集只在最后评估一次。类比：课本习题、模拟考、正式考试。
- **K 折交叉验证**：数据不多时，单独留一个验证集太浪费、结果也不稳。于是把数据分成 $K$ 份，让每份轮流当一次验证集，最后取平均。
- **网格（grid）**：要尝试的候选值列表，如深度 $\in\{2,4,8\}$。

**③ 一步一步**

1. 先留出**测试集**，调参全程不碰。为什么：保证最终评估是公正的。
2. 把剩下的数据分成 $K$ 份（常用 $K=5$ 或 10）。
3. 对每个候选值：做 $K$ 轮"用 $K-1$ 份训练、剩下 1 份验证"，把 $K$ 个验证误差取平均。为什么：平均能减少"某一次划分运气好坏"的影响。
4. 选**平均验证误差最小**的值（或在一个标准差以内选最简单的值）。
5. 用选中的值在**全部训练数据**上重新训练。为什么：数据越多模型越好。
6. 在测试集上评估**一次**并报告。
7. 类别不平衡时用**分层**划分（每折保持类别比例）；时间序列要**按时间顺序**划分（不能用未来预测过去）。

**④ 小例子**

5 折交叉验证选决策树深度，每格是一折的验证误差：

| 深度 | 第 1 折 | 第 2 折 | 第 3 折 | 第 4 折 | 第 5 折 | 平均 |
|---|---|---|---|---|---|---|
| 2 | 0.30 | 0.28 | 0.32 | 0.29 | 0.31 | 0.30 |
| 4 | 0.20 | 0.22 | 0.19 | 0.23 | 0.21 | **0.21** |
| 8 | 0.25 | 0.27 | 0.24 | 0.28 | 0.26 | 0.26 |

选深度 4。解读：深度 2 太浅（欠拟合），深度 8 太深（过拟合）。

**⑤ 常见误区**

- 用训练误差选：永远会选最深的树。
- 用测试集选：测试分数会偏乐观。
- 标准化等预处理要在每一折的训练部分上拟合，否则验证集的信息会"泄漏"进训练。

**⑥ 对照最终版**

- "Example: the maximum depth of a tree. The training error cannot choose it." → 例子是最大深度；不能用训练误差选。
- "K-fold cross-validation: for each value in a grid, train on K−1 folds, validate on the last one, and average." → K 折交叉验证的做法。
- "Choose the value with the lowest validation error, retrain on all training data, and test once on the test set." → 选最小、重训、测试一次。

**最终版答案（背诵版 EN，≤5 行）：**
Example: the **maximum depth** of a tree. The training error cannot choose it (deeper is always better there).
**K-fold cross-validation**: for each value in a grid, train on K−1 folds, validate on the last one, and average.
Choose the value with the **lowest validation error**, retrain on all training data, and test **once** on the test set.

### 3.2 What are the stakes and difficulties of hyperparameter calibration? 超参数校准的意义和难点是什么？ ★★

考过：[2021 Ex1 Q7](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex1 Q9](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** ① 超参数控制偏差—方差（见 1.1）；② 交叉验证与 Lasso／Elastic Net 的正则化路径——[第二课 · 正则化与验证](../../Lectures/02_LM/06_regularization_and_validation.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

超参数校准（调参）为什么重要？难在哪里？

**② 需要的工具**

- **超参数决定复杂度**：深度、$k$、$\lambda$、学习率、网络结构……这些旋钮决定了模型会欠拟合还是过拟合（见 1.1）。
- **验证数据／交叉验证**：调参必须用的"模拟考试"（见 3.1）。
- **信息泄漏**：测试数据的信息不知不觉进入了训练或选择过程，导致评估结果偏乐观。

**③ 一步一步**

1. **为什么重要**：选错超参数，同一个算法可能从"完全没用"变成"很好"，反之亦然。
2. **难点一：不能用训练误差**。训练误差总是偏爱最复杂的模型，所以必须留出验证数据或做交叉验证。代价是训练用的数据变少，或者计算量成倍增加。
3. **难点二：每试一个值都要重新训练**，计算很贵。
4. **难点三：验证分数有噪声**，换一种数据划分，最优值可能就变了。
5. **难点四：超参数往往有好几个，而且连续值、整数、类别混在一起**，组合数量爆炸。
6. **难点五：测试集绝对不能参与调参**，否则会信息泄漏、成绩虚高。

**④ 小例子**

- 只调一个 $\lambda$，试 10 个值、做 5 折交叉验证，就要训练 $10\times5=50$ 次。
- 同时调 3 个超参数、每个试 10 个值：$10^3=1000$ 种组合，乘 5 折就是 5000 次训练。这就是为什么要用随机搜索或贝叶斯优化（见 3.3）。

**⑤ 常见误区**

- 在测试集上反复调参，等于"偷看考题"。
- 交叉验证给出的最好分数本身也偏乐观（因为是挑出来的最好值），需要嵌套交叉验证或另留测试集来得到公正的估计。

**⑥ 对照最终版**

- "Hyperparameters set the complexity, so they decide underfitting vs overfitting." → 为什么重要。
- "Difficulties: we cannot use the training error, so we need validation data or CV;" → 难点一。
- "each try needs a new training (costly); the score is noisy;" → 难点二、三。
- "tuning on the test set gives an optimistic result." → 难点五。

**最终版答案（背诵版 EN，≤5 行）：**
Hyperparameters set the **complexity**, so they decide **underfitting vs overfitting**.
Difficulties: we **cannot use the training error**, so we need validation data or CV;
each try needs a **new training** (costly); the score is **noisy**;
tuning on the test set gives an **optimistic** result.

### 3.5 Define the ROC curve. 给出 ROC 曲线的定义。 ★★

考过：[2021 Ex1 Q2](../DataML-CHPS-2021-examen_zh.md) · [2023.11 Ex1 Q2](../DataML-CHPS-2023-examen_zh.md)（原问法：评分算法的理论评价准则）

**先懂这些：** ① 分类与评分（scoring）的区别——[第三课 · 这些数据可以支持哪些决策？](../../Lectures/03_LMC_zh.md)；② α–β 图、Neyman–Pearson、理想 ROC 曲线——[第三课 · 从分类到评分：ROC 曲线与 AUC](../../Lectures/03_LMC_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

给出 ROC 曲线的定义。（2023.11 的问法是"给出一个评价评分算法的理论准则"，答 ROC／AUC。）

**② 需要的工具**

- **评分函数 $s(x)$**：给每个样本打一个分，分越高越可能是正类（例如逻辑回归输出的概率）。
- **阈值 $t$**：分数 $\ge t$ 就判为正类。阈值不同，判断结果就不同。
- **混淆矩阵**：把预测结果和真实情况交叉统计成四格：
  - **TP**（真阳性）：真的是正类，也判成正类；
  - **FN**（假阴性）：真的是正类，却判成负类（漏报）；
  - **FP**（假阳性）：真的是负类，却判成正类（误报）；
  - **TN**（真阴性）：真的是负类，也判成负类。
- **TPR（真阳性率、召回率、灵敏度）** $=\frac{TP}{TP+FN}$：所有正类中被找出来的比例。
- **FPR（假阳性率）** $=\frac{FP}{FP+TN}$：所有负类中被误报的比例，等于 1 − 特异度。

**③ 一步一步**

1. 用评分函数给所有测试样本打分。
2. 把阈值 $t$ 从很高降到很低。为什么：$t$ 很高时谁都不判正（点 $(0,0)$）；$t$ 很低时所有人都判正（点 $(1,1)$）。
3. 每取一个阈值，算出一对 $(\text{FPR},\text{TPR})$，画成平面上的一个点。
4. 把这些点连起来，就是 **ROC 曲线**：$t\mapsto(\text{FPR}(t),\text{TPR}(t))$，其中 $\text{TPR}(t)=P(s(X)\ge t\mid Y=1)$，$\text{FPR}(t)=P(s(X)\ge t\mid Y=0)$。
5. 解读：随机打分的 ROC 是**对角线**；完美打分的 ROC 经过左上角 $(0,1)$。曲线越靠近左上角越好。

**④ 小例子**

5 个样本，分数和真实类别：0.9(+)、0.8(−)、0.7(+)、0.4(+)、0.2(−)，共 3 个正类、2 个负类。

| 阈值 $t$ | 判为正的样本 | TP | FP | TPR | FPR |
|---|---|---|---|---|---|
| 0.9 | 0.9 | 1 | 0 | 0.333 | 0 |
| 0.8 | 0.9、0.8 | 1 | 1 | 0.333 | 0.5 |
| 0.7 | 前 3 个 | 2 | 1 | 0.667 | 0.5 |
| 0.4 | 前 4 个 | 3 | 1 | 1 | 0.5 |
| 0.2 | 全部 | 3 | 2 | 1 | 1 |

把 (0,0) → (0,0.333) → (0.5,0.333) → (0.5,0.667) → (0.5,1) → (1,1) 连起来就是 ROC 曲线。

**⑤ 常见误区**

- ROC 评价的是"排序能力"，与某个具体阈值无关。
- 横轴是 FPR，纵轴是 TPR，不要画反。

**⑥ 对照最终版**

- "For a score $s(x)$ and a threshold $t$: TPR(t)=…, FPR(t)=…" → 两个比率的定义。
- "The ROC curve plots TPR against FPR when $t$ varies, from $(0,0)$ to $(1,1)$." → 阈值变化时画出的曲线。
- "A random score gives the diagonal; a perfect score goes through $(0,1)$." → 两个参照情况。

**最终版答案（背诵版 EN，≤5 行）：**
For a score $s(x)$ and a threshold $t$: $\text{TPR}(t)=P(s(X)\ge t\mid Y=1)$, $\text{FPR}(t)=P(s(X)\ge t\mid Y=0)$.
The **ROC curve** plots TPR against FPR when $t$ varies, from $(0,0)$ to $(1,1)$.
A random score gives the **diagonal**; a perfect score goes through $(0,1)$.

### 3.6 What is the interest of the ROC curve and the AUC? ROC 曲线和 AUC 有什么用？ ★★

考过：[2021 Ex1 Q2](../DataML-CHPS-2021-examen_zh.md) · [2023.11 Ex1 Q2](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① 评分的最优解、实用准则 AUC——[第三课 · 评分的最优解、实用准则：ROC 曲线下面积（AUC）](../../Lectures/03_LMC_zh.md)；② 先理解 3.5。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

ROC 曲线和曲线下面积 AUC 有什么用？

**② 需要的工具**

- **ROC 曲线**（见 3.5）。
- **AUC** $=P(s(X^+)>s(X^-))+\tfrac12P(s(X^+)=s(X^-))$：随机抽一个正样本和一个负样本，正样本分数更高的概率，分数相同时算一半（第二项）。只有分数不会相同时（如连续分数）才能省掉第二项；反例：所有样本分数都相同时 AUC＝0.5，只写第一项会得到 0。它恰好等于 ROC 曲线下的面积。
- **代价与工作阈值**：实际使用时要选一个具体阈值，取决于误报和漏报各自的代价。
- **Neyman–Pearson 思路**：先规定可以容忍的最大误报率，再在这个限制下让检出率尽量高。

**③ 一步一步**

1. **不依赖阈值的评价**：ROC 同时展示所有阈值下"检出率 vs 误报率"的权衡，不用事先决定阈值或代价。
2. **比较模型**：一条 ROC 曲线处处在另一条上方，就说明它在任何误报率下都检出得更多。
3. **选择工作阈值**：按业务要求在曲线上挑一个点。例如"误报率不能超过 5%"，就选 FPR ≤ 0.05 中 TPR 最高的那个阈值。
4. **用 AUC 概括成一个数**：0.5＝随机猜，1＝完美排序。因为它衡量的是**排序质量**，所以是评分问题的理论准则。
5. **局限**：正类非常稀少时，ROC 可能看起来很好，此时还应看**精确率—召回率曲线**；AUC 高也不代表输出的概率校准良好。

**④ 小例子**

接 3.5 的 5 个样本：正类分数 0.9、0.7、0.4，负类分数 0.8、0.2，共 $3\times2=6$ 个正负对：

- 0.9 > 0.8 ✓，0.9 > 0.2 ✓，0.7 > 0.8 ✗，0.7 > 0.2 ✓，0.4 > 0.8 ✗，0.4 > 0.2 ✓
- 排对 4 对 → AUC $=4/6\approx0.667$。
- 用梯形算 3.5 那条曲线下的面积：$0.5\times0.333+0.5\times1=0.667$，两种算法结果一致。
- 选阈值：若要求 FPR = 0（一个误报都不能有），只能取 $t=0.9$，TPR 仅为 0.333；若允许 FPR = 0.5，取 $t=0.4$ 就能找出全部正类。

**⑤ 常见误区**

- AUC 衡量排序，不衡量概率准不准。
- 类别极不平衡时只看 AUC 可能过于乐观。

**⑥ 对照最终版**

- "ROC evaluates a score for all thresholds." → 不依赖阈值。
- "We use it to compare models and to choose a threshold (costs, max false alarms)." → 两个用途。
- "AUC = area under the curve = $P(s(X^+)>s(X^-))+\tfrac12P(s(X^+)=s(X^-))$: 0.5 = random, 1 = perfect ranking." → AUC 的定义和含义（同分算一半）。
- "With rare positives, also use the precision–recall curve." → 局限。

**最终版答案（背诵版 EN，≤5 行）：**
ROC evaluates a score **for all thresholds**.
We use it to **compare** models and to **choose a threshold** (costs, max false alarms).
**AUC** = area under the curve = $P(s(X^+)>s(X^-))+\tfrac12P(s(X^+)=s(X^-))$: 0.5 = random, 1 = perfect ranking.
With rare positives, also use the **precision–recall** curve.

### 3.3 Can hyperparameter calibration be solved by an optimization technique? 超参数校准能用优化方法解决吗？ ★

考过：[2023.3 Ex1 Q9](../DataML-CHPS-2022-examen_zh.md)（2024 Ex1 Q4 的参考答案也涉及）

**先懂这些：** 先掌握 3.1 的交叉验证流程；再对比 6.2 中"普通"的数值优化（有梯度、可多次廉价评估）。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

能不能把"找最好的超参数"当成一个优化问题来解？这个问题在数值上有什么特点？可以用什么方法？

**② 需要的工具**

- **双层优化**：优化问题里面还嵌套着另一个优化问题。外层选超参数 $\lambda$，内层对每个 $\lambda$ 训练模型得到参数 $\hat\theta(\lambda)$。
- **黑盒函数**：只能"输入 → 输出"地去试，看不到内部结构，也拿不到梯度。
- **网格搜索、随机搜索、贝叶斯优化**：三种常用的不需要梯度的搜索方法。

**③ 一步一步**

1. **可以**，写成 $\min_\lambda\hat R_{\text{val}}(\hat\theta(\lambda))$：外层最小化验证误差，内层 $\hat\theta(\lambda)$ 是在训练数据上训练出的参数。
2. 外层目标的数值特点：
   - **没有显式梯度**，常常不可微；
   - **评估很贵**：每试一个 $\lambda$ 都要完整训练 1 次或 $K$ 次；
   - **有噪声**：结果受数据划分和随机性影响；
   - **非凸**：可能有多个局部最优；
   - **混合空间**：超参数有连续的、整数的、类别的。
3. 所以用**不需要梯度**的方法：
   - **网格搜索**：每个超参数取几个值，全部组合试一遍，只适合很少几个超参数；
   - **随机搜索**：随机抽组合来试，维数较高时比网格更有效；
   - **贝叶斯优化**：用一个代理模型猜"哪里可能更好"，有针对性地选下一个试验点；
   - 多保真方法（逐次减半、Hyperband）：先用少量资源淘汰差的候选。
4. 这些方法都不保证全局最优；测试集始终不参与这个过程。

**④ 小例子**

两个超参数，其中只有一个真正重要，各试 9 次：

- 网格 3×3：重要的那个超参数只试了 3 个不同的值；
- 随机搜索：9 次试验给重要的超参数试了 9 个不同的值，更可能碰到好的值。

**⑤ 常见误区**

- 以为可以像训练参数那样直接用梯度下降调超参数（一般拿不到梯度）。

**⑥ 对照最终版**

- "Yes, it is a bi-level problem: $\min_\lambda\hat R_{\text{val}}(\hat\theta(\lambda))$." → 可以，是双层问题。
- "But the objective is a black box: no gradient, expensive, noisy, non-convex, mixed discrete / continuous variables." → 数值特点。
- "So we use grid search, random search or Bayesian optimization. No guarantee of the global optimum." → 求解方法和局限。

**最终版答案（背诵版 EN，≤5 行）：**
**Yes**, it is a **bi-level problem**: $\min_\lambda\hat R_{\text{val}}(\hat\theta(\lambda))$.
But the objective is a **black box**: no gradient, **expensive**, **noisy**, **non-convex**, mixed discrete / continuous variables.
So we use **grid search**, **random search** or **Bayesian optimization**. No guarantee of the global optimum.

### 3.4 Which parameters are chosen by the data scientist and which are learned by the algorithm? 哪些参数由数据科学家选择，哪些由算法学得？ ★

考过：[2023.3 Ex1 Q6](../DataML-CHPS-2022-examen_zh.md)（原问法：任选一种监督算法描述其特征）；[2019 Q5](../Exam_2019_zh.md) 问的决策树"参数"也要区分这两类

**先懂这些：** 在任一具体算法上区分：优化变量（$\theta$）与固定它们的外部设置（$\lambda$、结构）——[第二课 · 最小二乘](../../Lectures/02_LM/01_linear_models_and_least_squares.md) 与 [正则化与验证](../../Lectures/02_LM/06_regularization_and_validation.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

任选一种监督学习算法：哪些量是数据科学家（人）定的，哪些是算法从数据里学出来的？

**② 需要的工具**

- **参数**：算法在训练中通过优化自动得到的量。
- **超参数**：训练开始前由人设定、算法不会改的量。
- **建模决策**：选哪些特征、怎么预处理、用什么惩罚、怎么验证，这些也是人做的选择。
- **标准化**：把每个特征调成均值 0、方差 1。带惩罚的模型必须做，因为惩罚对尺度敏感。

**③ 一步一步（以 Ridge 回归为例）**

1. 模型：$\min_{w,b}\sum_i(y_i-w^Tx_i-b)^2+\lambda\|w\|_2^2$。它拟合一个线性预测器，并把系数往 0 收缩，在特征多或相关时更稳定（见 5.5）。
2. **算法学出来的**：权重 $w$ 和截距 $b$，通过解这个优化问题得到。
3. **人选的**：
   - 用哪些特征、怎么预处理（必须标准化）；
   - 惩罚的形式（这里是 $\ell_2$）；
   - $\lambda$ 的值（用交叉验证选）；
   - 验证方案；如果拿来分类，还有决策阈值。
4. 决策树同理：分裂变量、阈值、叶值是学出来的；最大深度、叶节点最少样本数是人选的（见 4.1）。

**④ 小例子**

5 折交叉验证在 $\lambda\in\{0.1,1,10\}$ 中选出 $\lambda=1$（人通过验证做的决定）；然后算法在全部训练数据上解出 $w=(0.8,-0.3)$、$b=2.1$（学出来的）。

**⑤ 常见误区**

- 把 $\lambda$ 当成学出来的参数。
- 忘了特征选择和预处理也是人的决策。

**⑥ 对照最终版**

- "Example: Ridge, $\min\sum_i(y_i-w^Tx_i-b)^2+\lambda\|w\|^2$." → 例子。
- "Learned by the algorithm: the weights $w$ and $b$." → 学出来的。
- "Chosen by the data scientist: the features and their scaling, the type of penalty, the value of $\lambda$ (by CV), the validation protocol." → 人选的。
- "For a tree: splits are learned, the depth is chosen." → 决策树的对应情况。

**最终版答案（背诵版 EN，≤5 行）：**
Example: **Ridge**, $\min\sum_i(y_i-w^Tx_i-b)^2+\lambda\|w\|^2$.
**Learned** by the algorithm: the weights **$w$ and $b$**.
**Chosen** by the data scientist: the features and their scaling, the type of penalty, the value of **$\lambda$** (by CV), the validation protocol.
For a tree: splits are learned, the depth is chosen.

### 3.7 Which evaluation criteria can be used for classification data? 分类数据可以用哪些评价准则？ ★

考过：[2023.3 Ex1 Q3](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** ① 分类、评分、概率估计是三种不同的任务——[第三课 · 这些数据可以支持哪些决策？](../../Lectures/03_LMC_zh.md)；② 混淆矩阵与留出法——[第三课 · 评价准则、实践中的留出法](../../Lectures/03_LMC_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

对分类数据，评价一个学习方法可以用哪些准则？各自适合什么情况？

**② 需要的工具**

- **混淆矩阵**（TP、FP、FN、TN，见 3.5）。
- **准确率** $=\frac{TP+TN}{\text{总数}}$；**错误率**＝1−准确率。
- **精确率（precision）** $=\frac{TP}{TP+FP}$：判为正的里面，真正为正的比例（"报警可不可信"）。
- **召回率（recall）** $=\frac{TP}{TP+FN}$：真正为正的里面，被找出来的比例（"漏了多少"）。
- **特异度** $=\frac{TN}{TN+FP}$：真正为负的里面，被正确判为负的比例。
- **$F_1$** $=\frac{2PR}{P+R}$：精确率和召回率的调和平均。
- **平衡准确率**：召回率和特异度的平均。
- **对数损失、Brier 分数**：评价输出的概率准不准。

**③ 一步一步**

1. 先问清楚任务是什么，所有指标都要在**独立的测试／验证数据**上算。
2. **要给出类别**：用错误率／准确率；误判代价不同时，用按混淆矩阵加权的代价；**类别不平衡**时，改看精确率、召回率、特异度、$F_1$、平衡准确率。
3. **要排序／打分**：用 ROC 曲线和 AUC（见 3.5、3.6）；正类很稀少时用精确率—召回率曲线。
4. **要输出概率**：用对数损失（交叉熵）、Brier 分数、校准曲线。
5. 同时报告结果的波动（例如交叉验证的标准差）。

**④ 小例子（欺诈检测：1000 笔交易，其中 30 笔欺诈）**

- 模型 A 把所有交易都判为"正常"：准确率 97%，但召回率为 0，一笔欺诈都没抓到。
- 模型 B：TP=24、FN=6、FP=40、TN=930。准确率 95.4%（反而比 A 低），但召回率 0.8、精确率 0.375、$F_1\approx0.51$、平衡准确率约 0.88。

显然 B 更有用。这说明类别不平衡时**准确率会误导**。

**⑤ 常见误区**

- 只报告准确率。
- 混淆精确率和召回率。

**⑥ 对照最终版**

- "It depends on the task, always measured on test data." → 先看任务，在测试数据上算。
- "Class decision: error rate / accuracy, cost-weighted error; with imbalanced classes: precision, recall, F1." → 给出类别时的指标。
- "Ranking: ROC / AUC, PR curve. Probabilities: log-loss, Brier score." → 排序和概率的指标。

**最终版答案（背诵版 EN，≤5 行）：**
It depends on the task, always measured on **test data**.
Class decision: **error rate / accuracy**, cost-weighted error; with imbalanced classes: **precision, recall, F1**.
Ranking: **ROC / AUC**, PR curve. Probabilities: **log-loss**, Brier score.

### 3.8 How do you measure classification performance with a train–test split (N = 700 + 300)? 如何用训练／测试划分评估分类性能（700＋300）？ ★

考过：[2019 Q9a](../Exam_2019_zh.md)

**先懂这些：** [作业一第 4 题：数据划分](../../Exercises/Assignment1/guide/04_data_splitting.md)；[第三课 · 实践中的留出法](../../Lectures/03_LMC_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

有 1000 个带标签的样本（700 个类 1，300 个类 2），怎样用"训练集／测试集划分"来评估一个分类方法？

**② 需要的工具**

- **训练／测试划分**（见 3.1）。
- **分层抽样**：划分时让每一部分都保持原来的类别比例（这里是 70%／30%）。为什么：否则测试集可能偶然缺少少数类，评估就不准了。
- **混淆矩阵与各种指标**（见 3.7）。

**③ 一步一步**

1. 注意类别**不平衡**（7:3），所以要**分层**划分。
2. 例如按 80/20 划分：随机打乱后，训练集 **800 个（类 1 取 560、类 2 取 240）**，测试集 **200 个（类 1 取 140、类 2 取 60）**。
3. 如果还要调超参数，就在训练集里再分出验证集，或在训练集内部做交叉验证。
4. 模型和标准化等预处理**只在训练集上拟合**。为什么：测试集的信息不能泄漏进训练。
5. 在测试集上**只评估一次**：看混淆矩阵、召回率／精确率／$F_1$ 或 AUC，不只看准确率。
6. 缺点：结果依赖一次随机划分，而且测试集只有 200 个点，波动较大。可以重复划分，或改用交叉验证（见 3.9）。

**④ 小例子**

数字核对：$800\times0.7=560$，$800\times0.3=240$；$200\times0.7=140$，$200\times0.3=60$。两部分的类别比例都还是 7:3。

**⑤ 常见误区**

- 不分层，导致测试集类别比例失真。
- 在全部数据上先做标准化再划分，造成信息泄漏。

**⑥ 对照最终版**

- "Classes are imbalanced (70/30), so use a stratified split, e.g. 80/20:" → 分层划分。
- "train 800 (560 + 240), test 200 (140 + 60)." → 具体数字。
- "Fit the model (and the scaling) on the train set only." → 只在训练集上拟合。
- "Evaluate once on the test set: confusion matrix, recall, F1 or AUC, not only accuracy." → 测试一次，用合适的指标。

**最终版答案（背诵版 EN，≤5 行）：**
Classes are **imbalanced (70/30)**, so use a **stratified** split, e.g. 80/20:
**train 800 (560 + 240)**, **test 200 (140 + 60)**.
Fit the model (and the scaling) on the train set only.
Evaluate **once** on the test set: **confusion matrix**, recall, F1 or AUC, not only accuracy.

### 3.9 How do you measure classification performance with k-fold cross-validation? 如何用 k 折交叉验证评估分类性能？ ★

考过：[2019 Q9b](../Exam_2019_zh.md)

**先懂这些：** [第二课 · 交叉验证具体做什么](../../Lectures/02_LM/06_regularization_and_validation.md)；[作业一第 4 题：数据划分](../../Exercises/Assignment1/guide/04_data_splitting.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

同样的 1000 个样本，怎样用 $k$ 折交叉验证来评估分类性能？

**② 需要的工具**

- **K 折交叉验证**（见 3.1）。
- **分层**（见 3.8）。
- **嵌套交叉验证**：外层交叉验证用来评估，内层交叉验证用来调超参数，两者分开，避免"既当运动员又当裁判"。

**③ 一步一步（$k=5$）**

1. 把 1000 个样本**分层**分成 5 折，每折 200 个（类 1 140 个、类 2 60 个）。
2. 第 $j$ 轮（$j=1,\dots,5$）：用其余 4 折（800 个）训练，预处理也在这一步重新拟合；在第 $j$ 折上算指标。
3. 5 轮之后得到 5 个分数，报告它们的**均值和标准差**。
4. 每个样本恰好被测试一次，所以结果比单次划分更不受运气影响，代价是要训练 5 次。
5. 如果同时用这个交叉验证来调超参数，分数会偏乐观，应改用**嵌套交叉验证**，或另留一个最终测试集。

**④ 小例子**

5 折的准确率分别是 0.86、0.88、0.85、0.87、0.89，报告"平均 0.87，标准差约 0.016"，比单次划分只给一个数更可靠。

**⑤ 常见误区**

- 用同一组交叉验证既调参又报告最终成绩。

**⑥ 对照最终版**

- "$k=5$: split into 5 stratified folds of 200 (140 + 60)." → 分折。
- "Each time, train on 4 folds (800) and test on the remaining fold." → 每一轮怎么做。
- "Report the mean and standard deviation of the 5 scores; each point is tested exactly once." → 报告方式。
- "If the same CV is used for tuning, use nested CV." → 调参时用嵌套交叉验证。

**最终版答案（背诵版 EN，≤5 行）：**
$k=5$: split into **5 stratified folds of 200 (140 + 60)**.
Each time, train on **4 folds (800)** and test on the remaining fold.
Report the **mean and standard deviation** of the 5 scores; each point is tested exactly once.
If the same CV is used for tuning, use **nested CV**.

---

## 4. 决策树

> 出现最稳定的主题：2019、2020、2023.3、2023.11、2024 都有概念题。画回归树的计算题见[计算题文件](00_calculations.md)。

### 4.1 What are the hyperparameters of decision trees? 决策树有哪些超参数？ ★★★★

考过：[2019 Q5](../Exam_2019_zh.md) · [2020 A3](../Exam_2020_zh.md) · [2023.11 Ex1 Q4](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex2 Q5](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① [第五课 · 基于划分的分类器（3/4）：超参数](../../Lectures/05_NLM_zh.md)；② 参数和超参数的区别（见 3.4）；③ [Lab2](../../Exercises/Lab2/Lab2_zh.ipynb) 决策树部分，试着改 `max_depth` 看边界变化。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

决策树有哪些超参数？顺便要能分清哪些是超参数、哪些是树自己学出来的参数。

**② 需要的工具**

- **决策树是什么**（详见 4.2）：一连串"是／否"问题。例：贷款审批，先问"月收入 ≤ 3000？"，是 → 拒绝；否 → 再问"负债率 ≤ 40%？"……最后走到的那个格子（叶节点）给出答案。
- **每个超参数的意义**：
  - **最大深度 max depth**：最多连续问几层问题。
  - **最大叶节点数**：最多分成几个最终格子。
  - **分裂所需最少样本数／叶节点最少样本数**：一个格子里至少要有多少样本才允许再分，或者才算一个合法的叶子。
  - **最小不纯度下降**：一次分裂至少要让格子"变纯"多少才值得分（纯度的含义见 4.3）。
  - **分裂准则**：用什么衡量"纯"，分类用 Gini 或熵，回归用 MSE。
  - **剪枝参数 $\alpha$**：先长一棵大树，再按 $R(T)+\alpha|T|$ 剪掉不划算的分支（$|T|$ 是叶子数）。
  - 随机森林还有：树的棵数、每次分裂尝试的特征数。
- **学出来的参数**：每个节点问哪个变量、阈值是多少，以及每个叶子输出什么。

**③ 一步一步**

1. 认识到：上面所有超参数都在控制同一件事，就是**树能长多复杂**。
2. 树太深 → 叶子太多 → 每个叶子只有一两个样本 → 背答案（过拟合）；树太浅 → 欠拟合。
3. 用交叉验证在候选值里选（见 3.1），测试集保持独立。

**④ 小例子**

100 个训练点：

- 最大深度 7 → 最多 $2^7=128$ 个叶子，比样本还多 → 树有足够的**容量**把训练集切得非常细，训练误差往往接近 0，等于把训练集背了下来。注意 128 只是叶子数的上界，不保证每个点都能真的被单独分开：例如两个样本特征完全相同、标签不同，任何划分都分不开它们。
- 叶节点最少 10 个样本 → 最多 10 个叶子，每个叶子的预测由至少 10 个点投票决定 → 更稳定。

**⑤ 常见误区**

- 分裂变量和阈值是**学出来的参数**，不是超参数。
- 最大深度只给出叶子数的上界（$\le2^D$），不等于精确规定叶子数。

**⑥ 对照最终版**

- "Hyperparameters: max depth, max number of leaves, min samples per leaf / per split, min impurity decrease, split criterion (Gini, entropy, MSE), pruning parameter α." → 超参数清单。
- "Learned parameters: split variables, thresholds, leaf values." → 学出来的参数。
- "Hyperparameters are chosen by cross-validation." → 用交叉验证选。

**最终版答案（背诵版 EN，≤5 行）：**
**Hyperparameters**: **max depth**, max number of leaves, **min samples per leaf / per split**, min impurity decrease, split **criterion** (Gini, entropy, MSE), **pruning** parameter α.
**Learned parameters**: split variables, thresholds, leaf values.
Hyperparameters are chosen by **cross-validation**.

### 4.2 What is a decision tree (representation), e.g. for binary classification? 什么是决策树（表示方式），例如在二分类中？ ★★

考过：[2020 A3](../Exam_2020_zh.md) · [2024 Ex2 Q1](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** [第五课 · 局部方法 2：基于划分的方法（决策树）、基于划分的分类器（1/4）](../../Lectures/05_NLM_zh.md)；与 2.1 的"局部方法"联系起来。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

决策树是什么？它怎样表示一个分类器（以二分类为例）？

**② 需要的工具**

- **递归划分**：先把空间切成两块，再把每一块继续切，一层层切下去。
- **内部节点**：一个"是／否"问题，通常只看一个变量，如 $x^{(j)}\le s$（"第 $j$ 个特征是否不超过阈值 $s$"）。
- **叶节点**：不再继续切的格子，里面存放预测结果。
- **轴对齐**：每次只按一个变量切，所以切出来的格子都是边与坐标轴平行的矩形。

**③ 一步一步**

1. 从根节点开始，每个内部节点问一个问题，把数据分到左、右两个子节点。
2. 一直分下去，直到叶节点。每个叶节点对应输入空间里的一个**矩形格子**。
3. 二分类时，每个叶节点给出一个 0／1 标签，就是落在这个格子里的训练点的**多数类**；也可以附上类别比例作为分数。
4. 整棵树就是一个**分段常数**函数：同一格子里所有点的预测都相同。
5. 它是**局部方法**：预测只取决于同一格子里的训练点（见 2.1）。

**④ 小例子**

二维数据：$x_1$＝年龄，$x_2$＝收入。一棵深度为 2 的树：

- 根节点："收入 ≤ 3000？"
  - 是 → 节点："年龄 ≤ 25？" 是 → 叶子"拒绝"；否 → 叶子"批准"。
  - 否 → 叶子"批准"。

它把平面切成 3 个矩形：{收入 ≤ 3000，年龄 ≤ 25}、{收入 ≤ 3000，年龄 > 25}、{收入 > 3000}。

**⑤ 常见误区**

- "二分类"指目标只有两个类别；CART 每个节点分成两支，这是另一回事。
- 叶子的预测来自训练数据，不是人为规定的。

**⑥ 对照最终版**

- "A tree is a recursive partition of the input space." → 递归划分。
- "Each internal node has a test $x_j\le s$; each leaf is an axis-parallel rectangle with a prediction." → 节点和叶子的含义。
- "In binary classification, the leaf gives the majority class (0 or 1)." → 二分类时叶子输出多数类。
- "It is a piecewise-constant, local model." → 分段常数的局部模型。

**最终版答案（背诵版 EN，≤5 行）：**
A tree is a **recursive partition** of the input space.
Each internal node has a test $x_j\le s$; each **leaf** is an **axis-parallel rectangle** with a prediction.
In binary classification, the leaf gives the **majority class** (0 or 1).
It is a **piecewise-constant**, local model.

### 4.3 How is a decision tree built / trained (pseudocode)? 决策树如何构建／训练（伪代码）？ ★★

考过：[2020 A3](../Exam_2020_zh.md) · [2024 Ex2 Q3](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① [第五课 · 基于划分的分类器（2/4）：构建数据驱动的划分](../../Lectures/05_NLM_zh.md)；② 不纯度：Gini $1-\sum_c p_c^2$、熵 $-\sum_c p_c\log p_c$；③ [Lab2](../../Exercises/Lab2/Lab2_zh.ipynb)／[Lab3](../../Exercises/Lab3/Lab3_zh.ipynb)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

怎样从数据训练出一棵决策树？要能写出伪代码。

**② 需要的工具**

- **不纯度**：衡量一个格子里的类别有多"混"。全是同一类＝纯（不纯度 0）；两类各占一半＝最混。
  - **Gini 指数** $1-\sum_cp_c^2$（$p_c$ 是第 $c$ 类的比例）；
  - **熵** $-\sum_cp_c\log p_c$；
  - 回归树用 **MSE**（格子内 $y$ 的方差）。
- **不纯度下降（增益）**：分裂前的不纯度减去分裂后左右两边按样本数加权的不纯度。下降越多，这次分裂越有用。
- **贪心**：每一步只选当前看起来最好的分裂，不回头修改。
- **剪枝**：先长一棵大树，再剪掉不划算的分支（见 4.10）。

**③ 一步一步**

1. 如果满足停止规则（节点已纯、到达最大深度、样本太少、没有有效增益，见 4.9），就把它设为叶子：分类取多数类，回归取均值。
2. 否则，枚举每个变量 $j$ 和每个候选阈值 $s$（排序后相邻两个值的中点）。
3. 对每个 $(j,s)$，把数据分成左右两部分，计算不纯度下降 $\Delta=I(S)-\frac{|S_L|}{|S|}I(S_L)-\frac{|S_R|}{|S|}I(S_R)$。为什么加权：大的子集影响更大。
4. 选 $\Delta$ 最大的 $(j^*,s^*)$ 作为这个节点的问题。
5. 对左右两个子集**递归**地重复上述步骤。
6. （可选）长完后用代价复杂度准则 $R(T)+\alpha|T|$ 剪枝，$\alpha$ 用验证集选。

这是贪心算法：每一步局部最优，但整棵树不一定全局最优（找最优树是 NP 难的）。

**④ 小例子（Gini）**

一个节点有 10 个样本：5 个 A、5 个 B，Gini $=1-(0.5^2+0.5^2)=0.5$。比较两个候选分裂：

- 分裂 1：左边 (4A, 1B)，右边 (1A, 4B)。每边 Gini $=1-(0.8^2+0.2^2)=0.32$，加权后 0.32，下降 **0.18**。
- 分裂 2：左边 (5A, 3B)，右边 (0A, 2B)。左边 Gini $=0.469$，右边 0（纯），加权 $0.8\times0.469=0.375$，下降 **0.125**。

选分裂 1，因为它让两边都更纯。

**⑤ 常见误区**

- 只看右边一个格子很纯（分裂 2）不够，要看**加权**后的整体不纯度。
- 不剪枝、不限制深度的树会一直长到叶子纯了或再也分不开为止（通常每个叶子只剩很少几个样本）；特征相同、标签不同的样本永远分不开，所以要有"没有合法分裂就停"的停止条件。

**⑥ 对照最终版**

- 伪代码五行：满足停止条件就返回叶子（多数类）→ 选不纯度下降最大的 $(j,s)$ → 分成左右两部分 → 对两边递归。
- "Splits are chosen greedily (locally optimal). Optionally prune with $R(T)+\alpha|T|$." → 贪心选择；可以剪枝。

**最终版答案（背诵版 EN，≤5 行）：**
```text
Grow(S):
  if stop (pure, max depth, too few points, no valid split): return Leaf(majority class of S)
  choose (j, s) that maximizes the impurity decrease (Gini / entropy)
  S_L = {x in S : x_j <= s},  S_R = S \ S_L
  return Node(x_j <= s, Grow(S_L), Grow(S_R))
```
Splits are chosen **greedily** (locally optimal). Optionally **prune** with $R(T)+\alpha|T|$.

### 4.4 What label does a decision tree assign to a new point x? 决策树给新点 x 赋什么标签？ ★★

考过：[2020 A3](../Exam_2020_zh.md)（分类或回归时如何决策）· [2024 Ex2 Q2](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 先理解 4.2 的表示方式；对比 2.1 中 k-NN 的"局部投票"。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

一棵训练好的决策树，怎样给一个新点 $x$ 预测标签？（2020 年还问回归时怎么预测。）

**② 需要的工具**

- **决策树的结构**（见 4.2）：内部节点是问题，叶子是答案。
- **多数类**：叶子里训练样本最多的那个类。
- **类别频率作为分数**：叶子里正类所占的比例，可以当作"有多像正类"的分数。

**③ 一步一步**

1. 从根节点开始，按节点上的问题 $x^{(j)}\le s$ 向左或向右走。
2. 一直走到某个叶节点 $L(x)$。每个点只会落进唯一的一个叶子。
3. **分类**：输出这个叶子里训练样本的多数类 $\hat y=\arg\max_cn_{L,c}$（$n_{L,c}$ 是叶子里第 $c$ 类的样本数）。也可以输出正类频率 $n_{L,1}/n_L$ 作为分数，再按代价选阈值。平局规则要事先固定。
4. **回归**：输出这个叶子里训练样本 $y$ 值的**平均数**。
5. 预测只需要比较"树的深度"那么多次，非常快。

**④ 小例子**

- 分类：新点落进的叶子里有 7 个 A、3 个 B → 预测 **A**；B 的分数是 0.3。如果漏掉 B 的代价很高，可以把阈值设为 0.25，此时就判为 B。
- 回归：新房子落进的叶子里有 3 套训练房子，价格分别是 200、220、240 → 预测 **220**。

**⑤ 常见误区**

- 叶子里的频率不一定是校准良好的真实概率，尤其是叶子样本很少时。

**⑥ 对照最终版**

- "Send $x$ down from the root, following the tests, until it reaches a leaf." → 从根走到叶。
- "Classification: the majority class of the training points in that leaf (the class frequency can be a score)." → 分类取多数类。
- "Regression: the mean of their $y$." → 回归取均值。

**最终版答案（背诵版 EN，≤5 行）：**
Send $x$ down from the root, following the tests, until it reaches a **leaf**.
Classification: the **majority class** of the training points in that leaf (the class frequency can be a score).
Regression: the **mean** of their $y$.

### 4.5 What are the advantages of decision trees over most other algorithms? 与大多数其他算法相比，决策树有哪些优点？ ★★

考过：[2023.3 Ex1 Q7](../DataML-CHPS-2022-examen_zh.md) · [2024 Ex2 Q7](../DataML-CHPS-2024-examen_zh.md)（pros）

**先懂这些：** [第五课 · 关于局部方法的要点：决策树的优点](../../Lectures/05_NLM_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

和大多数其他算法相比，决策树有哪些优点？

**② 需要的工具**

- **可解释性**：人能看懂模型是怎么做决定的。
- **特征交互**：一个变量的作用取决于另一个变量（如"年轻且收入低"才拒绝）。
- **单调变换**：保持大小顺序不变的变换，如换单位、取对数。
- **标准化**：把各特征调到相近的尺度，许多算法（k-NN、SVM、带惩罚的回归）都需要。

**③ 一步一步（逐条理解每个优点）**

1. **可解释**：小树就是一组"如果……那么……"的规则，可以直接解释给医生或银行职员听。
2. **自动选变量**：只有对分类有帮助的变量才会被选来分裂，无用变量自然不出现。
3. **自动处理非线性和交互**：树一层层切分，天然能表达"先看 A，再看 B"的组合规则，不用手工构造交叉项或多项式。
4. **不需要标准化**：分裂只看"$x_j$ 是否 ≤ 阈值"，只和样本的大小顺序有关。把收入从欧元换成美元，或者取对数，树的结构完全一样。
5. **适用面广**：数值和类别变量都能处理，分类和回归都能做，部分实现还能处理缺失值。
6. **快**：预测只需走一条路径。
7. **是强大集成方法的积木**：随机森林、Boosting 都由树组成。

**④ 小例子**

按 1 欧元＝1.1 美元换算，问题"收入 ≤ 3000 欧元？"和"收入 ≤ 3300 美元？"把样本分成完全相同的两组。所以树不在乎单位，而 k-NN 的距离会因为单位不同而完全改变。

**⑤ 常见误区**

- "可解释"只对小树成立，几百个叶子的大树或森林就看不懂了。
- 优点题常和缺点题一起考（见 4.7）。

**⑥ 对照最终版**

- "Easy to interpret (if–then rules). Automatic variable selection." → 优点 1、2。
- "Handles non-linearity and interactions. No scaling needed (invariant to monotone transforms)." → 优点 3、4。
- "Works with mixed data, for classification and regression. Fast." → 优点 5、6。
- "It is the base of random forests and boosting." → 优点 7。

**最终版答案（背诵版 EN，≤5 行）：**
**Easy to interpret** (if–then rules). **Automatic variable selection**.
Handles **non-linearity and interactions**. **No scaling needed** (invariant to monotone transforms).
Works with **mixed data**, for classification and regression. Fast.
It is the base of **random forests and boosting**.

### 4.6 A tree was trained for f. Can it be reused for f₁(5x)=f(x), f₂(x)=5f(x), f₃(x)=f(x)⁵, without retraining? 为 f 训练好的树，能否不重新训练就用于这些变换后的函数？ ★★

考过：[2021 Ex3 d–e](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex4 c](../DataML-CHPS-2022-examen_zh.md)（原问法：$3f(x)$、$f_2(3x)=f(x)$、$[f_1(x)+f_2(3x)]^2$）

**先懂这些：** ① 树是分段常数函数：阈值作用在**输入轴**，叶值作用在**输出轴**（4.2）；② 集成＝多棵树的平均（2.3）；③ 原卷参考答案中的回归树图：[2021](../DataML-CHPS-2021-examen_zh.md)、[2023.3](../DataML-CHPS-2022-examen_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

已经用数据训练好一棵回归树 $T\approx f$。现在新数据和原来"本质相同、只是做了已知的变换"，例如 $f_1(5x)=f(x)$、$f_2(x)=5f(x)$、$f_3(x)=f(x)^5$。要不要重新训练？如果不用，该怎么做？

**② 需要的工具**

- **回归树是分段常数函数**：阈值决定**在横轴（输入）哪里切**，叶值决定**每一段的高度（输出）**。
- **输入变换 vs 输出变换**：变换作用在 $x$ 上，就改阈值；作用在 $y$ 上，就改叶值。
- **集成＝多棵树取平均**（见 2.3）。
- **外推**：在训练数据范围之外做预测。树在范围外只能沿用边界叶子的常数，所以不可靠。

**③ 一步一步**

1. **输入缩放** $f_1(5x)=f(x)$，即 $f_1(u)=f(u/5)$：预测 $T(u/5)$。"$u/5\le s$"等价于"$u\le5s$"，所以把**所有阈值乘以 5**，叶值不变。
2. **输出缩放** $f_2=5f$：**所有叶值乘以 5**，阈值不变。
3. **输出非线性变换** $f_3=f^5$：单棵树在每个叶子里是常数，所以只要**把每个叶值取 5 次方**。代价是误差也被放大：叶值误差为 $\delta$ 时，五次方后误差约为 $5\hat f^4\delta$。
4. **集成模型**：前两种是线性变换，"先变换每棵树再平均"和"先平均再变换"结果相同；但 $f^5$ 是非线性的，必须**先对所有树的预测取平均，再取 5 次方**，因为 $(\frac1B\sum T_b)^5\ne\frac1B\sum T_b^5$。
5. **前提**：换算后的输入（如 $u/5$、$u/3$）必须落在原训练区间内，否则树只能常值外推，结果不可靠。
6. 2023.3 的版本：c1 $=3f$ → 叶值乘 3；c2 $f_2(3x)=f(x)$ → 阈值乘 3；c3 $=[f_1(x)+f_2(3x)]^2=[3f(x)+f(x)]^2=(4f(x))^2$ → 先乘 4 再对叶值平方。

**④ 小例子**

一棵树：$x\le2$ 时输出 1，否则输出 3。

- $f_1(5x)=f(x)$：阈值变成 10（$u\le10$ 输出 1，否则 3）。
- $f_2=5f$：叶值变成 5 和 15。
- $f_3=f^5$：叶值变成 1 和 243。
- 集成：某点上两棵树分别预测 1 和 3。正确做法是先平均得 2，再取 5 次方得 **32**；错误做法是先各自取 5 次方再平均，得 $(1+243)/2=$ **122**。

**⑤ 常见误区**

- 以为任何变换都要重新训练，其实已知变换只需改阈值或叶值。
- 集成模型里对非线性变换搞错了先后顺序。
- 忘记检查换算后的输入是否还在训练范围内。

**⑥ 对照最终版**

- "No retraining (if the rescaled inputs stay inside the training range). $f_1(5x)=f(x)$: multiply the thresholds by 5." → 不用重训；输入缩放改阈值。
- "$f_2=5f$: multiply the leaf values by 5." → 输出缩放改叶值。
- "$f_3=f^5$: raise each leaf value to the power 5." → 非线性变换作用在叶值上。
- "For an ensemble: the same for linear changes, but for $f^5$ average first, then take the power." → 集成时注意顺序。

**最终版答案（背诵版 EN，≤5 行）：**
**No retraining** (if the rescaled inputs stay inside the training range). $f_1(5x)=f(x)$: **multiply the thresholds by 5**.
$f_2=5f$: **multiply the leaf values by 5**.
$f_3=f^5$: raise each **leaf value to the power 5**.
For an **ensemble**: the same for linear changes, but for $f^5$ **average first, then take the power**.

### 4.7 What are the drawbacks of decision trees? 决策树有哪些缺点？ ★

考过：[2024 Ex2 Q7](../DataML-CHPS-2024-examen_zh.md)（cons）

**先懂这些：** [第五课 · 关于局部方法的要点：主要局限](../../Lectures/05_NLM_zh.md)；配合 4.11 的二维例子。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

决策树有哪些缺点？

**② 需要的工具**

- **方差高**（见 1.1）：训练数据稍有变化，模型就大变。
- **贪心**（见 4.3）：每一步只选当前最好的分裂，不回头。
- **轴对齐边界**（见 4.2）：每次只按一个变量切。
- **外推**：在训练数据范围之外预测。
- **XOR 问题**：两个变量单独看都没有信息，组合起来才有，例如"$x_1$ 和 $x_2$ 相同则为 A，不同则为 B"。

**③ 一步一步（逐条理解每个缺点）**

1. **方差高、不稳定**：数据稍有变化，根节点的问题就可能换掉，整棵树随之全变。
2. **容易过拟合**：不加限制的树会一直长到叶子纯了为止，训练误差为 0（除非有特征完全相同、标签不同的样本，那样的点无论怎么切都分不开）。
3. **贪心训练**：只看一步，像 XOR 那样"单看一个变量没用、组合起来才有用"的结构可能被错过。
4. **轴对齐边界**：斜线或曲线边界需要很多次分裂才能近似，形成"阶梯"（见 4.11）。
5. **分段常数**：回归树的预测不光滑，而且**不能外推**到训练范围以外。
6. **大树难解释**：叶子一多，可解释性的优势就没了。
7. 和其他局部方法一样，**高维**小样本时效果差。

**④ 小例子（XOR）**

4 个点：(0,0) A、(1,1) A、(0,1) B、(1,0) B。无论按 $x_1$ 还是按 $x_2$ 切一刀，两边都是 1 个 A、1 个 B，不纯度一点没降，贪心算法会认为"没必要分"。但连切两刀（先 $x_1$ 再 $x_2$）就能完全分对。

**⑤ 常见误区**

- 优缺点常一起考，要能对应着说（见 4.5）。

**⑥ 对照最终版**

- "High variance / unstable. Overfits when deep. Greedy training." → 缺点 1–3。
- "Axis-parallel boundaries only (a staircase for oblique lines)." → 缺点 4。
- "Piecewise-constant: no extrapolation. Large trees are not interpretable." → 缺点 5、6。

**最终版答案（背诵版 EN，≤5 行）：**
**High variance / unstable**. **Overfits** when deep. **Greedy** training.
**Axis-parallel** boundaries only (a staircase for oblique lines).
**Piecewise-constant**: no extrapolation. Large trees are **not interpretable**.

### 4.8 Is it possible to solve the drawbacks of decision trees? 能否克服决策树的缺点？ ★

考过：[2024 Ex2 Q8](../DataML-CHPS-2024-examen_zh.md)；相关：[2021 Ex3 c、e](../DataML-CHPS-2021-examen_zh.md)（树集成如何逼近数据）

**先懂这些：** [第五课 · 集成方法 1：Bagging 与随机森林；集成方法 2：Boosting](../../Lectures/05_NLM_zh.md)；[Lab3](../../Exercises/Lab3/Lab3_zh.ipynb) 集成部分。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

决策树的那些缺点能不能克服？怎么克服？

**② 需要的工具**

- **剪枝**（见 4.10）。
- **Bagging、随机森林、Boosting**（见 2.3）。
- **斜决策树**：每个节点可以按几个变量的线性组合来切，而不只是一个变量。

**③ 一步一步（逐个缺点对应补救）**

1. **过拟合** → 限制深度、设叶节点最少样本数、用交叉验证选 $\alpha$ 来**剪枝**。
2. **方差高** → **Bagging**（对多棵在 bootstrap 样本上训练的树取平均）和**随机森林**（再在每次分裂随机选特征，让树之间更不相似）。平均后的预测更平滑、更稳定。
3. **偏差／单棵浅树太弱** → **Boosting**：依次在残差或被加权的错误样本上训练浅树，配合收缩和早停。
4. **斜边界** → 斜决策树，或换用 SVM、逻辑回归等模型。
5. **代价**：集成**失去了单棵小树的可解释性**，计算量更大；而常数叶值的平均仍然**不能外推**。所以是"部分"克服。

**④ 小例子**

2.3 的公式：100 棵相关系数为 0.3 的树取平均，方差从 1 降到 0.307。这就是随机森林比单棵树稳定得多的原因。

**⑤ 常见误区**

- 说"所有缺点都能消除"，其实可解释性和外推问题仍然存在。

**⑥ 对照最终版**

- "Partly. Overfitting: limit the depth, min leaf size, pruning (α by CV)." → 部分可以；过拟合的对策。
- "Variance: bagging / random forests. Bias: boosting." → 方差和偏差的对策。
- "Cost: we lose interpretability and need more computation." → 代价。

**最终版答案（背诵版 EN，≤5 行）：**
**Partly.** Overfitting: limit the depth, min leaf size, **pruning** (α by CV).
Variance: **bagging / random forests**. Bias: **boosting**.
Cost: we **lose interpretability** and need more computation.

### 4.9 Give at least two stopping rules for training a decision tree. 至少给出两条决策树训练的停止规则。 ★

考过：[2024 Ex2 Q4](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 4.3 的伪代码中"stopping rule"那一行。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

训练决策树时，什么时候停止继续分裂？至少说出两条规则。

**② 需要的工具**

- **4.3 的伪代码**：每个节点先检查"要不要停"。
- **超参数**（见 4.1）：很多停止规则直接对应超参数。

**③ 一步一步**

满足下列任一条件，就把节点设为叶子：

1. 节点**已纯**（所有样本同一类）。为什么：再分也没意义。
2. 达到**最大深度**。
3. 节点样本数**少于分裂所需最少样本数**，或者任何分裂都会产生样本太少的叶子。为什么：样本太少时的分裂往往只是在拟合噪声。
4. **最佳的不纯度下降低于阈值**，即没有有用的分裂。
5. 达到**最大叶节点数**。

补充：用正增益阈值提前停止可能"短视"，例如 XOR（见 4.7）第一刀的增益是 0，却能为下一刀铺路。所以另一种做法是先长一棵大树，再**剪枝**（见 4.10）。

**④ 小例子**

叶节点最少样本数设为 5，某节点有 8 个样本：任何分裂都会让一边少于 5 个，所以停止，把它设为叶子。

**⑤ 常见误区**

- 只答"树长完为止"，没有给出具体规则。

**⑥ 对照最终版**

- "Stop when: (1) the node is pure; (2) the max depth is reached;" → 规则 1、2。
- "(3) there are too few samples to split; (4) no split gives enough impurity decrease;" → 规则 3、4。
- "(5) the max number of leaves is reached." → 规则 5。

**最终版答案（背诵版 EN，≤5 行）：**
Stop when: (1) the node is **pure**; (2) the **max depth** is reached;
(3) there are too **few samples** to split; (4) no split gives enough **impurity decrease**;
(5) the **max number of leaves** is reached.

### 4.10 Is it possible to monitor the number of cells of the tree using the training data? 能否用训练数据控制树的单元（叶）数量？ ★

考过：[2024 Ex2 Q6](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 代价复杂度剪枝 $R(T)+\alpha|T|$；② 训练误差为什么偏好大树（1.3）。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

能不能用训练数据来控制树的格子（叶子）数量？

**② 需要的工具**

- **叶子数＝格子数**：每个叶子对应输入空间里的一个格子。
- **代价复杂度剪枝** $R_{\text{train}}(T)+\alpha|T|$：$|T|$ 是叶子数，$\alpha$ 是每多一个叶子的"罚款"。
- **验证数据**（见 3.1）。

**③ 一步一步**

1. **可以直接控制**：设最大叶节点数、最大深度（叶子数至多 $2^D$）或叶节点最少样本数。
2. **也可以剪枝**：对每个 $\alpha$，找使 $R_{\text{train}}(T)+\alpha|T|$ 最小的子树。$\alpha$ 越大，留下的叶子越少。
3. 训练数据用来**构建**划分和计算拟合项 $R_{\text{train}}$。
4. 但**只看训练误差选不出**合适的叶子数，因为叶子越多训练误差越小，直到 0。
5. 所以叶子数（或 $\alpha$）必须在**验证数据／交叉验证**上选。

**④ 小例子**

大树 8 个叶子、训练误差 0.05；剪过的树 3 个叶子、训练误差 0.10：

- $\alpha=0.02$：大树 $0.05+8\times0.02=0.21$，小树 $0.10+3\times0.02=0.16$ → 选**小树**。
- $\alpha=0.005$：大树 $0.05+0.04=0.09$，小树 $0.10+0.015=0.115$ → 选**大树**。

$\alpha$ 取多少，最终要看哪棵树在验证集上更好。

**⑤ 常见误区**

- 以为最大深度能精确规定叶子数（它只给上界）。
- 用训练误差选叶子数。

**⑥ 对照最终版**

- "Yes: set a max number of leaves, a max depth ($\le2^D$ leaves) or a min leaf size, or use cost-complexity pruning $R_{\text{train}}(T)+\alpha|T|$." → 可以，几种控制方式。
- "But the training error alone cannot choose the number of leaves (it always prefers more)." → 训练误差选不出。
- "So choose it by validation / CV." → 用验证选。

**最终版答案（背诵版 EN，≤5 行）：**
**Yes**: set a **max number of leaves**, a max depth ($\le2^D$ leaves) or a min leaf size, or use **cost-complexity pruning** $R_{\text{train}}(T)+\alpha|T|$.
But the **training error alone cannot choose** the number of leaves (it always prefers more).
So choose it by **validation / CV**.

### 4.11 Give a 2D example where the classes are separable but a tree is not efficient. 给出一个二维例子：类别可分，但决策树效率不高。 ★

考过：[2019 Q5](../Exam_2019_zh.md)（示意图：[2019_diagonal_tree.png](../Answers/2019_diagonal_tree.png)）

**先懂这些：** 树的每次分裂只能平行于坐标轴（4.2）。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

画一个二维例子：两类本来可以分开，但用决策树来分却很低效。

**② 需要的工具**

- **线性可分**：一条直线就能把两类完全分开。
- **轴对齐分裂**（见 4.2）：树每次只能画一条横线或竖线。

**③ 一步一步**

1. 构造两类数据，用**对角线** $x_2=x_1$ 分开：$x_2>x_1$ 是类 1，$x_2<x_1$ 是类 2。
2. 它们**线性可分**，逻辑回归或线性 SVM 用一条斜线就能完全分开。
3. 但树只能画横线和竖线，只能用**阶梯**去逼近这条斜线。
4. 想更精确，就要更多台阶 → 树变深、难解释，而且台阶是跟着样本走的，容易**过拟合**。
5. 解决办法：加一个新特征 $x_2-x_1$（树只要一刀就能分开），或用斜决策树，或直接用线性模型。

其他例子：同心圆、任何"转了一个角度"的边界。示意图见 [2019_diagonal_tree.png](../Answers/2019_diagonal_tree.png)。

**④ 小例子**

在 $[0,1]^2$ 上沿对角线分开的两类，深度为 2 的树最多只有 4 个叶子，只能做出很粗的几级台阶，靠近对角线的点很多会被分错；要误差足够小，就需要非常多的叶子。而一个线性分类器用两个参数就完全解决了。

**⑤ 常见误区**

- 选了一个"类别本身就分不开"的例子，那就不符合题目"可分但树低效"的要求了。

**⑥ 对照最终版**

- "Two classes separated by the diagonal $x_2=x_1$: they are linearly separable." → 例子。
- "But a tree only makes axis-parallel splits, so it needs a staircase of many splits." → 为什么树低效。
- "The tree becomes deep and overfits. A linear model, or the feature $x_2-x_1$, solves it." → 后果与解决方法。

**最终版答案（背诵版 EN，≤5 行）：**
Two classes separated by the **diagonal** $x_2=x_1$: they are linearly separable.
But a tree only makes **axis-parallel splits**, so it needs a **staircase** of many splits.
The tree becomes deep and **overfits**. A linear model, or the feature $x_2-x_1$, solves it.

---

## 5. 线性模型、OLS 与逻辑回归

> OLS 的数值计算（4 个点求直线和 RMSE）每年都考，见[计算题文件](00_calculations.md)。

### 5.1 Describe the logistic regression model. 描述逻辑回归模型。 ★★★

考过：[2019 Q4](../Exam_2019_zh.md) · [2020 A2](../Exam_2020_zh.md) · [2021 Ex1 Q3](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** ① 分类数据的概率模型、后验概率 $P(Y=1\mid X=x)$——[第三课 · 分类数据的概率模型](../../Lectures/03_LMC_zh.md)；② 线性逻辑回归及其拟合——[第三课 · 方法 3：线性逻辑回归](../../Lectures/03_LMC_zh.md)；③ [Lab1](../../Exercises/Lab1/Lab1_zh.ipynb) 逻辑回归部分。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

描述逻辑回归模型：它输出什么、参数怎么学。注意它虽然叫"回归"，其实是做**分类**的。

**② 需要的工具**

- **后验概率 $P(Y=1\mid x)$**：看到输入 $x$ 之后，它属于类 1 的概率。例：看到一封邮件的内容后，它是垃圾邮件的概率。
- **几率（odds）与对数几率（log-odds）**：几率＝$p/(1-p)$。$p=0.8$ 时几率是 4（"四比一"），对数几率是 $\log 4\approx1.386$。对数几率可以取任意实数，适合用线性函数来表示。
- **sigmoid 函数** $\sigma(z)=\frac{1}{1+e^{-z}}$：把任意实数压到 0 和 1 之间，正好可以当概率用。它是 log-odds 的反函数。
- **极大似然**：选参数，使"实际观测到的这些标签"出现的概率最大。
- **交叉熵（对数损失）** $-[y\log p+(1-y)\log(1-p)]$：极大似然等价于最小化它。预测越**自信地错**，惩罚越大。
- **凸函数**：只有一个谷底的函数，局部最低点就是全局最低点（见 2.5）。
- **判别式模型**：直接建模 $P(Y\mid X)$，不关心 $X$ 本身怎样分布。

**③ 一步一步**

1. 先算线性分数 $z=w^Tx+b$。为什么：用最简单的方式把各个特征加权组合起来。
2. 用 sigmoid 把分数变成概率：$p(x)=\sigma(w^Tx+b)$，等价于假设"对数几率是 $x$ 的线性函数"。
3. 训练：用极大似然估计 $(w,b)$，也就是最小化交叉熵。
4. 交叉熵对 $(w,b)$ 是**凸**的，但没有闭式解，所以用**牛顿法（IRLS）**或梯度下降迭代求解。
5. 数据完全可分或维数很高时，必须加 $\ell_2$ 或 $\ell_1$ 惩罚。为什么：否则权重会越变越大、趋向无穷。
6. 解读系数：$e^{w_j}$ 是 $x_j$ 增加 1 个单位时几率乘上的倍数（几率比）。

**④ 小例子**

- sigmoid 取值：$\sigma(-2)=0.119$，$\sigma(0)=0.5$，$\sigma(2)=0.881$，$\sigma(4)=0.982$。
- 设 $w=1.5$、$b=-3$：$x=2$ 时 $z=0$，$p=0.5$；$x=3$ 时 $z=1.5$，$p=0.818$。
- 几率比：$w=1.5$ 表示 $x$ 每多 1，几率乘以 $e^{1.5}\approx4.48$。
- 交叉熵：真实 $y=1$，预测 $p=0.9$ 时损失 $-\ln0.9=0.105$；预测 $p=0.1$ 时损失 $-\ln0.1=2.303$，自信地错了，罚得重得多。

**⑤ 常见误区**

- 输出的 $p(x)$ **不保证**是校准良好的真实概率。
- 决策边界 $w^Tx+b=0$ 是线性的（一个超平面）；想要曲线边界要加多项式特征。
- 名字里的"回归"指的是回归 log-odds，它解决的是分类问题。

**⑥ 对照最终版**

- "For $Y\in\{0,1\}$: $P(Y=1\mid x)=\sigma(w^Tx+b)$, i.e. the log-odds is linear." → 模型形式：sigmoid 输出概率，对数几率线性。
- "$(w,b)$ are estimated by maximum likelihood: minimize the cross-entropy (convex; Newton or gradient descent)." → 参数学法。
- "A penalty can be added. It is a discriminative model." → 可加惩罚；判别式模型。

**最终版答案（背诵版 EN，≤5 行）：**
For $Y\in\{0,1\}$: $P(Y=1\mid x)=\sigma(w^Tx+b)=\frac1{1+e^{-(w^Tx+b)}}$, i.e. the **log-odds is linear**.
$(w,b)$ are estimated by **maximum likelihood**: minimize the **cross-entropy** (convex; Newton or gradient descent).
A penalty can be added. It is a **discriminative** model.

### 5.2 What decisions / uses does logistic regression allow (classification, scoring, other problems)? 逻辑回归能支持哪些决策／用途？ ★★★

考过：[2019 Q3](../Exam_2019_zh.md) · [2020 A2](../Exam_2020_zh.md)（两种用途）· [2021 Ex1 Q3](../DataML-CHPS-2021-examen_zh.md)（还能用于哪类学习问题）

**先懂这些：** [第三课 · 这些数据可以支持哪些决策？（1. 分类 2. 评分 4. 从分类到评分）](../../Lectures/03_LMC_zh.md)；与 9.2（分类数据 vs 分类问题）一起复习。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

逻辑回归输出一个概率 $p(x)$，拿这个数可以做哪几种决策？（2019 问"能做哪些决策"，2020 问"两种用途"，2021 问"还能用于哪类学习问题"。）

**② 需要的工具**

- **阈值 $t$**：把连续的概率变成"是／否"的分界线。
- **评分／排序（scoring）**：不急着下结论，只按风险高低排个序。
- **ROC／AUC**：评价排序好坏的工具（详见 3.5、3.6）。
- **代价不对称**：漏诊一个病人和误报一个健康人，代价往往不一样。

**③ 一步一步**

1. **分类**：$p(x)\ge t$ 判为 1，否则判为 0。概率校准良好时，$t=0.5$ 使错误率最小；漏报代价高（如癌症筛查）时降低 $t$，宁可多误报。
2. **评分／排序**：直接按 $p(x)$ 从高到低排，资源有限时先处理排在前面的（信用审核、精准营销、医疗分诊）。用 ROC／AUC 评价排得好不好。
3. **概率估计**：直接报告风险大小，支持不确定情况下的决策。例如 $p(x)$ 落在中间区间 $[t_1,t_2]$ 时不自动判断，交给人工专家。

所以同一个模型，既能解决**分类问题**，也能解决**评分问题**（见 9.2）。

**④ 小例子**

4 个病人，模型给出的患病概率分别是 0.9、0.6、0.3、0.05：

- $t=0.5$：前两人判阳性。
- $t=0.2$（筛查场景，宁可误报也不漏诊）：前三人判阳性。
- 排序：医生按 0.9 > 0.6 > 0.3 > 0.05 的顺序依次复查。
- 拒判区间 $[0.4,0.7]$：第二个人（0.6）不自动下结论，交给专家判断。

**⑤ 常见误区**

- 0.5 不是万能阈值，要看代价和概率是否校准。
- 分类和评分是两个不同的问题，评价指标也不同：分类看错误率、召回率；评分看 AUC。

**⑥ 对照最终版**

- "It gives a probability $p(x)$, so it allows:" → 因为输出概率，所以能做三件事。
- "(1) classification: $\hat y=1$ if $p(x)\ge t$ ($t=0.5$, or chosen from the costs)" → 分类，阈值按代价选。
- "(2) scoring / ranking: sort individuals by risk (credit, medicine), evaluated by ROC / AUC" → 排序，用 ROC／AUC 评价。
- "(3) probability estimation, e.g. send uncertain cases to an expert." → 概率估计，不确定的交给专家。

**最终版答案（背诵版 EN，≤5 行）：**
It gives a probability $p(x)$, so it allows:
(1) **classification**: $\hat y=1$ if $p(x)\ge t$ ($t=0.5$, or chosen from the costs);
(2) **scoring / ranking**: sort individuals by risk (credit, medicine), evaluated by **ROC / AUC**;
(3) **probability estimation**, e.g. send uncertain cases to an expert.

### 5.3 Explain how Ordinary Least Squares (OLS) fits a line / a linear model. 说明 OLS 如何拟合直线／线性模型。 ★★★

考过：[2021 Ex2 a](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex2 a](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex4 a](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① 最小二乘估计与投影的几何意义、两种证明——[第二课 · 线性模型与最小二乘](../../Lectures/02_LM/01_linear_models_and_least_squares.md)；② [Lab1](../../Exercises/Lab1/Lab1_zh.ipynb) 线性回归部分；③ 务必自己手算一遍某年的 4 点例子。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

普通最小二乘法（OLS）怎样用数据点拟合出一条最好的直线？要说出准则和求解公式。

**② 需要的工具**

- **残差** $e_i=y_i-\hat y_i$：真实值减去预测值，是**竖直方向**上的误差。
- **残差平方和 RSS** $=\sum_ie_i^2$。为什么要平方：① 正负误差不会互相抵消；② 大误差罚得更重；③ 可以求导，有闭式解；④ 噪声服从高斯分布时，最小化 RSS 就是极大似然。
- **偏导数＝0**：光滑函数的最低点处斜率为 0，所以令偏导等于 0 就能找到最小值。
- **均值、$S_{xx}$、$S_{xy}$**：$S_{xx}=\sum(x_i-\bar x)^2$ 衡量 $x$ 的分散程度；$S_{xy}=\sum(x_i-\bar x)(y_i-\bar y)$ 衡量 $x$ 和 $y$ 是否一起变大。斜率 $S_{xy}/S_{xx}$ 就是"协方差／方差"。
- **RMSE** $=\sqrt{\text{RSS}/N}$：平均每个点大约错多少，单位和 $y$ 相同。

**③ 一步一步（推导）**

1. 写出目标：$\text{RSS}(\beta_0,\beta_1)=\sum_i(y_i-\beta_0-\beta_1x_i)^2$，要让它最小。
2. 对 $\beta_0$ 求偏导令其为 0：$-2\sum_i(y_i-\beta_0-\beta_1x_i)=0$，得 $\hat\beta_0=\bar y-\hat\beta_1\bar x$。意义：最优直线一定经过均值点 $(\bar x,\bar y)$。
3. 代入后对 $\beta_1$ 求偏导令其为 0，得 $\hat\beta_1=\frac{\sum(x_i-\bar x)(y_i-\bar y)}{\sum(x_i-\bar x)^2}=\frac{S_{xy}}{S_{xx}}$。
4. 多个特征时写成矩阵（$X$ 加一列 1 对应截距）：最小化 $\|y-X\beta\|^2$，令梯度为 0 得**正规方程** $X^TX\hat\beta=X^Ty$；$X$ 列满秩时 $\hat\beta=(X^TX)^{-1}X^Ty$。几何意义：$X\hat\beta$ 是 $y$ 在 $X$ 列空间上的**正交投影**。
5. 用 RMSE 报告拟合质量。

**④ 小例子**

三个点 (0,1)、(1,2)、(2,4)：

1. $\bar x=1$，$\bar y=7/3\approx2.333$。
2. $S_{xx}=(-1)^2+0^2+1^2=2$；$S_{xy}=(-1)(-1.333)+0+(1)(1.667)=3$。
3. $\hat\beta_1=3/2=1.5$，$\hat\beta_0=2.333-1.5\times1=0.833$。
4. 预测 0.833、2.333、3.833；残差 0.167、−0.333、0.167，和为 0（这是一个很好的自查方法）。
5. RSS ≈ 0.1667，RMSE $=\sqrt{0.1667/3}\approx0.2357$。

考试真题的完整计算表见[计算题 C1](00_calculations.md)。

**⑤ 常见误区**

- OLS 最小化的是**竖直**误差，不是点到直线的垂直距离。
- 平方会放大离群点的影响，OLS **对离群点很敏感**（这正是 RANSAC 的动机，见 8.1）。
- 这里的 RMSE 是训练误差，不是测试误差。
- 特征数 $d$ 大于样本数 $N$ 时 $X^TX$ 不可逆（见 5.7）。

**⑥ 对照最终版**

- "Line $\hat y=\beta_0+\beta_1x$. OLS minimizes RSS." → 模型和准则。
- "Setting the derivatives to 0: $\hat\beta_1=\dots$, $\hat\beta_0=\bar y-\hat\beta_1\bar x$." → 求导得到的两个公式。
- "Matrix form: $\hat\beta=(X^TX)^{-1}X^Ty$. Error: RMSE." → 矩阵形式和误差指标。
- "OLS is sensitive to outliers." → 对离群点敏感。

**最终版答案（背诵版 EN，≤5 行）：**
Line $\hat y=\beta_0+\beta_1x$. OLS minimizes $\text{RSS}=\sum_i(y_i-\beta_0-\beta_1x_i)^2$.
Setting the derivatives to 0: $\hat\beta_1=\frac{\sum(x_i-\bar x)(y_i-\bar y)}{\sum(x_i-\bar x)^2}$, $\hat\beta_0=\bar y-\hat\beta_1\bar x$.
Matrix form: $\hat\beta=(X^TX)^{-1}X^Ty$. Error: $\text{RMSE}=\sqrt{\text{RSS}/N}$.
OLS is **sensitive to outliers**.

### 5.4 How do you use logistic regression for a classification problem? 如何把逻辑回归用于分类问题？ ★★

考过：[2019 Q4](../Exam_2019_zh.md) · [2021 Ex1 Q3](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** 先理解 5.1；[第三课 · 二分类问题的理论框架、Bayes 分类器](../../Lectures/03_LMC_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

怎样把逻辑回归用于一个分类问题？要说出从训练到预测、评估的完整流程。

**② 需要的工具**

- **逻辑回归模型**（见 5.1）：$p(x)=\sigma(w^Tx+b)$。
- **阈值 $t$**（见 5.2）。
- **线性分类器**：决策边界是超平面（二维是直线）的分类器。
- **softmax**：逻辑回归的多分类版本，把 $K$ 个分数变成 $K$ 个和为 1 的概率。

**③ 一步一步**

1. **训练**：在训练集上用极大似然拟合 $(w,b)$；需要时加惩罚，惩罚强度用交叉验证选。
2. **算概率**：对新点 $x$ 计算 $p(x)=\sigma(w^Tx+b)$。
3. **设阈值判类**：$p(x)\ge t$ 判为 1，否则为 0。$t=0.5$ 时，等价于 $w^Tx+b\ge0$，所以决策边界是一个**超平面**，逻辑回归是**线性分类器**。$t$ 可以按代价选，或者在验证集上按目标召回率／误报率选。
4. **评估**：在测试集上看混淆矩阵、错误率、召回率／精确率、ROC-AUC。
5. **扩展**：多分类用一对多或 softmax；需要弯曲边界时加多项式特征或用核。

**④ 小例子**

接 5.1 的参数 $w=1.5$、$b=-3$（一维）：

- $t=0.5$ 时边界是 $1.5x-3=0$，即 $x=2$：$x>2$ 判为 1，$x<2$ 判为 0。
- 若改用 $t=0.818$，边界移到 $x=3$（因为 $\sigma(1.5)=0.818$），判为 1 的样本变少，误报减少，但漏报增多。

**⑤ 常见误区**

- 阈值不是模型参数，是使用时的决策选择。
- 逻辑回归本身只能画直的边界。

**⑥ 对照最终版**

- "(1) Fit $(w,b)$ on the training data by maximum likelihood." → 训练。
- "(2) For a new $x$, compute $p(x)=\sigma(w^Tx+b)$." → 算概率。
- "(3) Predict 1 if $p(x)\ge t$. With $t=0.5$ this is $w^Tx+b\ge0$: a linear boundary." → 设阈值；线性边界。
- "(4) Evaluate on test data (confusion matrix, AUC)." → 评估。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **Fit** $(w,b)$ on the training data by maximum likelihood.
(2) For a new $x$, compute $p(x)=\sigma(w^Tx+b)$.
(3) Predict 1 if $p(x)\ge t$. With $t=0.5$ this is $w^Tx+b\ge0$: a **linear boundary**.
(4) **Evaluate** on test data (confusion matrix, AUC).

### 5.5 Explain the principle of Ridge regression. 解释岭回归的原理。 ★

考过：[2021 Ex2 d](../DataML-CHPS-2021-examen_zh.md)；[2023.3 Ex1 Q6](../DataML-CHPS-2022-examen_zh.md) 的参考答案也以 Ridge 为例

**先懂这些：** ① [第二课 · 岭回归与对偶（Why adding λI makes the system solvable）](../../Lectures/02_LM/05_ridge_and_duality.md)；② 高维最小二乘为什么病态——[第二课 · 泛化与高维](../../Lectures/02_LM/02_generalization_and_high_dimensions.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

解释岭回归（Ridge）的原理。

**② 需要的工具**

- **OLS**（见 5.3）。
- **$\ell_2$ 惩罚** $\|\beta\|_2^2=\sum_j\beta_j^2$：系数平方和。
- **可逆矩阵**：$X^TX$ 可逆，OLS 才有唯一解。特征数多于样本数或特征高度相关时，它不可逆或接近不可逆。
- **单位矩阵 $I$**：对角线为 1、其他为 0 的矩阵。加上 $\lambda I$ 相当于给对角线每个数都加 $\lambda$。
- **对偶形式与核**：解也可以写成只用样本之间内积的形式，于是能换成核函数（核岭回归）。

**③ 一步一步**

1. 在 OLS 目标上加系数大小的惩罚：$\min_\beta\|y-X\beta\|_2^2+\lambda\|\beta\|_2^2$，$\lambda>0$，截距通常不惩罚。
2. 求导令其为 0，得闭式解 $\hat\beta=(X^TX+\lambda I)^{-1}X^Ty$。
3. 加上 $\lambda I$ 后，矩阵**一定可逆**：即使 $d>N$ 或特征共线，问题也变得**适定**（解唯一且稳定）。
4. 系数被**往 0 收缩**，但很少恰好变成 0（与 Lasso 不同，见 5.6）。代价是多了一点偏差，换来方差大幅下降。
5. $\lambda$ 用交叉验证在**标准化**后的特征上选。为什么要标准化：惩罚对系数的大小一视同仁，而系数大小取决于特征的单位。
6. 对偶形式：预测只需要内积，$\hat y(x)=x^TX^T(XX^T+\lambda I)^{-1}y$，由此引出**核岭回归**。

**④ 小例子**

5.3 的三个点，一维时斜率 $=\frac{S_{xy}}{S_{xx}+\lambda}=\frac{3}{2+\lambda}$：$\lambda=0$ 时 1.5，$\lambda=1$ 时 1.0，$\lambda=4$ 时 0.5，越来越接近 0，但永远不会恰好等于 0。

**⑤ 常见误区**

- 以为 Ridge 能做变量选择（它不会把系数压成恰好 0）。
- 忘了先标准化。

**⑥ 对照最终版**

- "Ridge adds an $\ell_2$ penalty: …, so $\hat\beta=(X^TX+\lambda I)^{-1}X^Ty$." → 目标和闭式解。
- "$X^TX+\lambda I$ is always invertible (even if $d>N$)." → 一定可逆。
- "The coefficients shrink towards 0: a little bias, much less variance." → 收缩；偏差换方差。
- "$\lambda$ is chosen by CV, on standardized features." → 怎么选 $\lambda$。

**最终版答案（背诵版 EN，≤5 行）：**
Ridge adds an **$\ell_2$ penalty**: $\min_\beta\|y-X\beta\|^2+\lambda\|\beta\|^2$, so $\hat\beta=(X^TX+\lambda I)^{-1}X^Ty$.
$X^TX+\lambda I$ is **always invertible** (even if $d>N$).
The coefficients **shrink towards 0**: a little bias, much less **variance**.
$\lambda$ is chosen by CV, on standardized features.

### 5.6 How do you estimate a sparse linear model? 如何估计稀疏线性模型？ ★

考过：[2023.11 Ex1 Q3](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① 稀疏回归模型、约束式与惩罚式两种表述——[第二课 · 稀疏性与模型选择](../../Lectures/02_LM/03_sparsity_and_model_selection.md)；② 从 $\ell_0$ 到 $\ell_1$、绝对值惩罚为什么能把系数压到 0——[第二课 · Lasso 与结构化稀疏性](../../Lectures/02_LM/04_lasso_and_structured_sparsity.md)；③ 求解算法（坐标下降、LARS、近端方法）——[第四课 · LASSO 估计的优化方法](../../Lectures/04_UL_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

怎样估计一个**稀疏**的线性模型（大部分系数为 0，只用少数变量）？

**② 需要的工具**

- **稀疏**：只有少数系数非零，相当于自动挑出真正有用的变量。
- **$\ell_0$ "范数"** $\|\beta\|_0$：非零系数的个数。直接惩罚它就是"最优子集选择"，但要尝试所有变量组合，是 NP 难的。
- **$\ell_1$ 范数** $\|\beta\|_1=\sum_j|\beta_j|$：$\ell_0$ 的凸替代。
- **软阈值** $S_\lambda(z)=\text{sign}(z)\max(|z|-\lambda,0)$：比 $\lambda$ 小的直接变成 0，其余向 0 缩 $\lambda$。这就是 Lasso 产生 0 的机制。
- **坐标下降、LARS、近端方法**：求解 Lasso 的算法（课件第四课）。

**③ 一步一步**

1. 理想目标是惩罚变量个数 $\|\beta\|_0$（最优子集、AIC／BIC），但这是组合问题，算不动。
2. 改用它的凸松弛 **Lasso**：$\min_\beta\frac1N\|y-X\beta\|_2^2+\lambda\|\beta\|_1$。
3. 为什么 $\ell_1$ 能产生 0：绝对值函数在 0 处有"尖角"，优化时很多系数会正好停在 0 上，从而同时完成估计和变量选择。
4. 先**标准化**特征，沿正则化路径用**交叉验证**选 $\lambda$。
5. 用**坐标下降、LARS 或近端梯度**（软阈值）求解。
6. 注意：特征高度相关时，Lasso 往往随便挑一个，选择**不稳定**，可以用 Elastic Net；要找回"真正的"变量集合还需要额外的条件。

**④ 小例子（软阈值）**

在特征**标准正交**（$X^TX=I$：列两两正交且每列长度为 1）、目标写成 $\frac12\|y-X\beta\|^2+\lambda\|\beta\|_1$ 的简化情形下，Lasso 系数就是对 OLS 系数做软阈值 $S_\lambda$。（若只是列正交、长度不为 1，第 $j$ 个系数的阈值是 $\lambda/\|X_j\|_2^2$，不能统一减 $\lambda$。）设 OLS 系数为 3、0.8、−2，取 $\lambda=1$：

- $3\to2$（缩小 1）；
- $0.8\to0$（小于 1，直接变 0，这个变量被"删掉"了）；
- $-2\to-1$。

**⑤ 常见误区**

- 把 Ridge 当成稀疏方法。
- 以为 Lasso 选出的变量一定就是"真正的"变量。

**⑥ 对照最终版**

- "Use the Lasso: $\min_\beta\frac1N\|y-X\beta\|^2+\lambda\|\beta\|_1$." → 用 Lasso。
- "The $\ell_1$ penalty sets many coefficients exactly to 0, so it selects variables." → 为什么稀疏。
- "It is the convex version of the $\ell_0$ problem (NP-hard)." → 与 $\ell_0$ 的关系。
- "$\lambda$ by cross-validation; solved by coordinate descent or LARS." → 怎么选 $\lambda$、怎么求解。

**最终版答案（背诵版 EN，≤5 行）：**
Use the **Lasso**: $\min_\beta\frac1N\|y-X\beta\|^2+\lambda\|\beta\|_1$.
The **$\ell_1$ penalty** sets many coefficients **exactly to 0**, so it selects variables.
It is the convex version of the $\ell_0$ problem (NP-hard).
$\lambda$ by **cross-validation**; solved by **coordinate descent** or LARS.

### 5.7 With N = 50 data points and d = 200 features, which regression method would you prefer? How could you still use OLS? N=50、d=200 时选哪种回归方法？如果必须用 OLS 怎么办？ ★

考过：[2021 Ex2 e](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** ① "高"维对线性回归意味着什么——[第二课 · 泛化与高维（What 'high' means for linear regression）](../../Lectures/02_LM/02_generalization_and_high_dimensions.md)；② 5.5 和 5.6。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

只有 $N=50$ 个样本，却有 $d=200$ 个特征。你会选哪种回归方法？如果规定必须用 OLS，该怎么办？

**② 需要的工具**

- **秩**：矩阵里"真正独立"的行（或列）的个数。$X$ 是 $50\times200$ 的，秩最多是 50。
- **方程组的解**：未知数（200 个系数）比方程（50 个样本）多，解有无穷多个。
- **正则化方法** Ridge、Lasso、Elastic Net（见 5.5、5.6）。
- **PCA（主成分分析）**：把很多特征压缩成少数几个"综合特征"（主成分）。
- **伪逆 $X^+$**：在无穷多个解中挑出系数长度最小的那个（用 SVD 计算）。

**③ 一步一步**

1. 问题出在哪：$X^TX$ 是 $200\times200$ 的，但秩最多 50，**不可逆**。OLS 的系数解不唯一（有无穷多个），估计极不稳定。在常见情形下（$X$ 的 50 行线性无关，即行满秩），这些解都能把训练数据拟合到训练误差为 0；但这需要 $y$ 落在 $X$ 的列空间里，并不是 $d>N$ 自动保证的（反例：两个样本特征完全相同、标签一个 0 一个 1，任何系数都无法同时拟合）。训练误差为 0 意味着**过拟合风险很高**，是否真的过拟合要看在新数据上的表现。
2. **首选正则化**：预计只有少数变量重要 → **Lasso**（最多选出 $N$ 个变量，结果好解释）；预计很多变量都有小作用 → **Ridge**；也可以用 **Elastic Net**。$\lambda$ 用交叉验证选。
3. **必须用 OLS 时**，先把维数降到 $N$ 以下：
   - **变量选择**：用相关性筛选或前向逐步选择，保留 $k<50$ 个特征再做 OLS；
   - **主成分回归**：先用 PCA 降到 $k<50$ 个成分，再在这些成分上做 OLS；
   - 或直接取**最小范数解** $\hat\beta=X^+y$。
4. $k$ 用交叉验证确定。

**④ 小例子**

50 个方程、200 个未知数，就像只用 1 个方程 $x+y=2$ 去解两个未知数：$(1,1)$、$(0,2)$、$(3,-1)$……都满足，解不唯一，数据没法告诉你哪个是对的。

**⑤ 常见误区**

- 硬算 $(X^TX)^{-1}$（根本不存在）。
- 把"$d>N$"直接等同于"训练误差一定为 0、一定过拟合"：零训练误差还需要 $X$ 行满秩之类的条件，过拟合要看泛化表现。
- 只说"用 Ridge"，没有回答"必须用 OLS 时怎么办"这一半。

**⑥ 对照最终版**

- "$d=200>N=50$: $X^TX$ is not invertible; the OLS solution is not unique and unstable, with a high risk of overfitting." → 问题在哪：解不唯一、不稳定、过拟合风险高。
- "I prefer Lasso (selects variables) or Ridge, with $\lambda$ by CV." → 首选正则化。
- "To use OLS anyway: first reduce the dimension below 50 (variable selection, or PCA then OLS), or take the pseudo-inverse solution $X^+y$." → 必须用 OLS 时的办法。

**最终版答案（背诵版 EN，≤5 行）：**
$d=200>N=50$: $X^TX$ is **not invertible**; the OLS solution is **not unique** and unstable, with a high risk of **overfitting**.
I prefer **Lasso** (selects variables) or **Ridge**, with $\lambda$ by CV.
To use OLS anyway: first **reduce the dimension below 50** (variable selection, or **PCA then OLS**), or take the **pseudo-inverse** solution $X^+y$.

### 5.8 Which polynomial models would you try on 4 data points, and what is the most complex meaningful one? 4 个数据点上可以尝试哪些多项式模型？最复杂且有意义的是哪个？ ★

考过：[2021 Ex2 c](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** ① "线性模型"指对参数线性，多项式回归仍是 OLS——[第二课 · 线性模型与最小二乘](../../Lectures/02_LM/01_linear_models_and_least_squares.md)；② 每多拟合一个方向就多吸收一份噪声（$d/n$ 项）——[第二课 · 泛化与高维](../../Lectures/02_LM/02_generalization_and_high_dimensions.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

对只有 4 个点的数据，可以尝试哪些更复杂的多项式模型？最复杂且仍有意义的是哪个？

**② 需要的工具**

- **"线性模型"的含义**：对**参数**线性，不要求对 $x$ 线性。$\hat y=\beta_0+\beta_1x+\beta_2x^2$ 仍然是线性模型，可以用 OLS 解，只要把 $x,x^2$ 当作两个特征。
- **参数个数**：$p$ 次多项式有 $p+1$ 个系数。
- **插值**：曲线恰好穿过所有数据点，训练误差为 0。
- **自由度**：样本数减去参数个数，表示还剩多少信息能用来检验模型。

**③ 一步一步**

1. 多项式回归 $\hat y=\sum_{k=0}^p\beta_kx^k$ 在特征 $(1,x,\dots,x^p)$ 上做 OLS 即可。
2. 4 个点（横坐标互不相同）时，可以尝试 **2 次**（贴合散点的弯曲趋势）和 **3 次**。
3. 3 次多项式有 4 个参数，正好**插值**通过 4 个点，训练误差为 0，是仍然**有唯一解**的最复杂模型。
4. $p\ge4$ 时参数多于点数，方程组欠定，解有无穷多个，没有意义。
5. 但 3 次已经没有剩余自由度了：训练误差为 0 说明不了泛化能力。实际上应该用验证或留一法，在 1–2 次中选。

**④ 小例子**

4 个点各次多项式的参数个数：1 次 2 个、2 次 3 个、3 次 4 个（＝点数，恰好插值）、4 次 5 个（多于点数，欠定）。

**⑤ 常见误区**

- 以为多项式回归不是线性模型。
- 以为训练误差为 0 的 3 次多项式就是最好的模型。

**⑥ 对照最终版**

- "Polynomial regression is still linear in the parameters (OLS on $1,x,x^2,\dots$)." → 仍是线性模型。
- "With 4 points, try degree 2 and 3." → 尝试哪些。
- "Degree 3 (4 parameters) is the most complex: it interpolates the 4 points (zero training error); higher degrees are underdetermined." → 最复杂的是 3 次。
- "In practice, choose a low degree by validation." → 实际上用验证选低次。

**最终版答案（背诵版 EN，≤5 行）：**
Polynomial regression is still **linear in the parameters** (OLS on $1,x,x^2,\dots$).
With 4 points, try degree **2** and **3**.
Degree **3** (4 parameters) is the most complex: it **interpolates** the 4 points (zero training error); higher degrees are underdetermined.
In practice, choose a low degree by validation.

---

## 6. 深度学习与数值优化

### 6.1 What optimization strategy is used to train / calibrate deep learning architectures? 深度学习采用什么优化策略？ ★★

考过：[2023.3 Ex1 Q8](../DataML-CHPS-2022-examen_zh.md) · [2024 Ex1 Q3](../DataML-CHPS-2024-examen_zh.md)；相关：6.2（2023.11 问一般机器学习的数值优化）

**先懂这些：** ① 反向传播：链式法则、激活函数——[第六课 · 2. 反向传播算法、选读：通过反向传播计算梯度](../../Lectures/06_DL_zh.md)；② 梯度下降会收敛到最优解吗、SGD 避开不良临界点——[第六课 · 反向传播：讨论；深度学习优化中的结果](../../Lectures/06_DL_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

深度学习用什么方法训练（课程里叫"校准"）网络的参数？

**② 需要的工具**（你已经熟悉神经网络，这里主要把它对应到课程用语）

- **经验风险**：训练集上的平均损失，训练就是最小化它（见 2.2）。
- **梯度下降**：沿着损失下降最快的方向（负梯度）走一小步：$\theta\leftarrow\theta-\eta\nabla L(\theta)$，$\eta$ 是学习率。
- **小批量随机梯度下降（mini-batch SGD）**：每一步只用随机抽的一小批样本 $B_t$ 估计梯度，而不是用全部数据。
- **Adam、RMSprop、动量**：在 SGD 基础上自动调整步长的变体。
- **反向传播**：用链式法则从输出层往输入层逐层计算所有权重的梯度。它负责**算梯度**，更新参数的是优化器。
- **非凸**：损失地形有很多山谷，不能保证找到最低的那个。

**③ 一步一步**

1. **前向传播**：用当前参数，在一小批样本上算出预测和损失。
2. **反向传播**：用链式法则算出损失对每个权重的梯度。
3. **更新**：$\theta_{t+1}=\theta_t-\eta_t\nabla_\theta\Big[\frac1{|B_t|}\sum_{i\in B_t}\ell(f_\theta(x_i),y_i)+\lambda\Omega(\theta)\Big]$。
4. 换一小批，重复。把所有数据过一遍叫一个 epoch（轮）。
5. 为什么用小批量：每步的计算量和总样本数 $n$ 无关，适合大数据；梯度带一点噪声，还有助于跳出不好的平坦区域。
6. 目标非凸，不保证全局最优，所以初始化、**学习率**（及其调度）、批大小、训练轮数和**早停**都很重要。

**④ 小例子**

- 100 万个样本、批大小 100 → 每个 epoch 更新 10000 次。
- 一个最小的网络 $\hat y=w_2\cdot\text{ReLU}(w_1x)$，取 $x=1$、$y=5$、$w_1=2$、$w_2=3$：
  1. 前向：$h=\text{ReLU}(2)=2$，$\hat y=6$，损失 $(\hat y-y)^2=1$。
  2. 反向：$\partial L/\partial\hat y=2(\hat y-y)=2$；$\partial L/\partial w_2=2\times h=4$；$\partial L/\partial h=2\times w_2=6$；$\partial L/\partial w_1=6\times1\times x=6$（ReLU 在正区间导数为 1）。
  3. 更新（$\eta=0.05$）：$w_2=3-0.05\times4=2.8$，$w_1=2-0.05\times6=1.7$。
  4. 新的预测 $\hat y=2.8\times1.7=4.76$，损失 0.0576，比原来的 1 小很多。

**⑤ 常见误区**

- 反向传播是算梯度的方法，不是优化器本身。
- 学习率太大，损失会震荡甚至发散；太小，训练很慢。

**⑥ 对照最终版**

- "We minimize the empirical risk with mini-batch SGD (or Adam):" → 用小批量 SGD 或 Adam 最小化经验风险。
- 更新公式 → 沿小批量梯度的反方向走一步。
- "The gradient is computed by backpropagation (chain rule)." → 梯度由反向传播计算。
- "The problem is non-convex: no global guarantee. Learning rate, batch size, initialization and early stopping matter." → 非凸；这些设置很重要。

**最终版答案（背诵版 EN，≤5 行）：**
We minimize the empirical risk with **mini-batch SGD** (or **Adam**):
$\theta_{t+1}=\theta_t-\eta_t\nabla_\theta\frac1{|B_t|}\sum_{i\in B_t}\ell(f_\theta(x_i),y_i)$.
The gradient is computed by **backpropagation** (chain rule).
The problem is **non-convex**: no global guarantee. Learning rate, batch size, initialization and **early stopping** matter.

### 6.2 How is numerical optimization achieved in machine learning methods? Give an example. 机器学习方法如何做数值优化？举一个例子。 ★

考过：[2023.11 Ex1 Q8](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① OLS 闭式解与 QR／SVD——[第二课 · 线性模型与最小二乘](../../Lectures/02_LM/01_linear_models_and_least_squares.md)；② Lasso 的三种求解算法——[第四课 · LASSO 估计的优化方法](../../Lectures/04_UL_zh.md)；③ SVM 的对偶二次规划——[第五课 · 对偶表述](../../Lectures/05_NLM_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

机器学习方法是怎样做数值优化（求出最优参数）的？至少举一个具体例子。

**② 需要的工具**

- **目标函数**：经验损失＋惩罚项，要让它最小（见 2.2）。
- **凸／非凸**：凸函数的任何局部极小点都是全局极小点（谷底可能是一整片，但没有"假谷底"）；非凸函数可能有很多局部极小点和鞍点（见 2.5）。
- **光滑／非光滑**：光滑函数处处可导；$\ell_1$ 惩罚在 0 处有尖角，不可导。
- **闭式解**：用一个公式直接算出答案，不用迭代（如 OLS）。
- **梯度下降**：$w\leftarrow w-\eta\nabla L(w)$，沿最陡的下坡方向走一小步，$\eta$ 是步长（学习率）。
- **牛顿法**：同时利用二阶导数（曲率），步子更聪明，迭代次数更少。
- **QR／SVD 分解**：数值上更稳定地求解线性方程组的方法。

**③ 一步一步**

1. 先把学习问题写成目标函数：损失＋惩罚。
2. 看目标的**凸性和光滑性**，选合适的求解器：
   - **有闭式解**：OLS、Ridge 用 QR 或 SVD 解正规方程；
   - **光滑凸**：梯度下降、牛顿法、拟牛顿法（L-BFGS），如带 $\ell_2$ 正则的逻辑回归；
   - **非光滑凸**：Lasso 用坐标下降或近端梯度（软阈值）；SVM 在对偶问题上做二次规划；
   - **大规模非凸**：神经网络用小批量 SGD／Adam，配合反向传播算梯度（见 6.1）。
3. 迭代方法要选合适的步长（或用线搜索），并设停止条件，如梯度范数 $\|\nabla L(w_t)\|<\varepsilon$。
4. 凸性本身只保证"局部极小＝全局极小"，**不自动保证某个算法收敛**：梯度下降还需要最小值存在、步长合适（如光滑凸函数取 $\eta\le 1/L$，$L$ 是梯度的 Lipschitz 常数）等条件。非凸问题一般没有全局保证，梯度下降可能停在局部极小点，也可能停在鞍点附近。

**④ 小例子（梯度下降）**

最小化 $L(w)=(w-3)^2$，导数是 $2(w-3)$，从 $w_0=0$ 出发，步长 $\eta=0.25$：

- $w_1=0-0.25\times(-6)=1.5$
- $w_2=1.5-0.25\times(-3)=2.25$
- $w_3=2.625$，$w_4=2.8125$……

每步都离最优点 3 近一半。因为 $L$ 是凸的，一定会收敛到全局最小点 3。

**⑤ 常见误区**

- 以为所有问题都用梯度下降：有闭式解时直接算更好，不可导时要用专门的方法。
- 步长太大会震荡甚至发散。
- 以为"凸＝一定收敛到全局最小"：凸性不保证最小值存在。例如线性可分数据上的**无正则**逻辑回归，没有有限的最优参数，$\|w\|$ 会一直增大、损失只是趋近下确界 0；加上 $\ell_2$ 正则后目标严格凸、最小值存在且唯一。
- 以为非凸问题至少能到局部极小：也可能停在鞍点。

**⑥ 对照最终版**

- "Write the objective (loss + penalty), then pick a solver:" → 先写目标，再选求解器。
- "closed form (OLS, Ridge: QR / SVD), gradient / Newton (logistic regression), coordinate descent / proximal (Lasso), SGD (neural networks)." → 四类求解器。
- "Example: $\ell_2$-regularized logistic regression, $w_{t+1}=w_t-\eta\nabla L(w_t)$ until the gradient is small; it is strictly convex, so with a suitable step size it converges to the global minimum." → 例子：带正则保证最小值存在且唯一，步长合适才保证收敛。

**最终版答案（背诵版 EN，≤5 行）：**
Write the objective (loss + penalty), then pick a solver:
**closed form** (OLS, Ridge: QR / SVD), **gradient / Newton** (logistic regression), **coordinate descent / proximal** (Lasso), **SGD** (neural networks).
Example: $\ell_2$-regularized logistic regression, $w_{t+1}=w_t-\eta\nabla L(w_t)$ until the gradient is small; it is strictly **convex**, so with a suitable step size it converges to the **global minimum**.

### 6.3 What is the mathematical space of functions of deep feedforward neural networks? 深度前馈神经网络对应怎样的函数空间？ ★

考过：[2023.11 Ex1 Q6](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① 深度前馈网络的定义——[第六课 · 深度学习：主要概念介绍（深度前馈网络）](../../Lectures/06_DL_zh.md)；② 单层网络是通用逼近器——[第六课 · 1. 通用逼近器的存在性定理](../../Lectures/06_DL_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

深度前馈神经网络对应的"函数空间"（假设空间）在数学上是什么样的？

**② 需要的工具**（你已熟悉神经网络，这里主要是课程的数学写法）

- **仿射映射** $A_\ell(u)=W_\ell u+b_\ell$：矩阵乘法加偏置，就是一层全连接。
- **激活函数 $\sigma$**：逐个分量作用的非线性函数，如 ReLU、sigmoid、tanh。
- **复合 $\circ$**：$f\circ g$ 表示先做 $g$ 再做 $f$，网络就是一层层的复合。
- **向量空间**：任意两个元素相加、乘以常数后仍在这个集合里。
- **通用逼近定理**：只要神经元足够多，网络可以在有界区域上以任意精度逼近任意连续函数。

**③ 一步一步**

1. 固定网络结构（$L$ 个隐藏层，每层宽度固定）。
2. 函数空间是**仿射映射和激活函数交替复合**得到的所有函数：$\mathcal H=\{x\mapsto A_{L+1}\circ\sigma_L\circ A_L\circ\dots\circ\sigma_1\circ A_1(x)\}$，参数是 $\theta=\{(W_\ell,b_\ell)\}$。
3. 它是一个**参数化的函数族**，对参数是**非线性**的。
4. 它一般**不是向量空间**：两个同结构网络之和，一般不能用一个同结构的网络表示。
5. 由**通用逼近定理**，单隐藏层只要够宽就能逼近任意连续函数（近似误差可以很小）；**深度**让某些函数可以用少得多的参数表示（层次化表示，见 6.5）。

**④ 小例子**

输入 784 维（28×28 图像）、一个 100 个神经元的隐藏层、10 个输出的网络：参数个数 $=784\times100+100+100\times10+10=79510$。这 79510 个数的每一组取值，对应 $\mathcal H$ 里的一个函数。

**⑤ 常见误区**

- 把函数空间说成"所有函数"：结构固定时它只是一个有限维参数化的子集。

**⑥ 对照最终版**

- "For a fixed architecture: $\mathcal H=\{\dots\}$, with $A_\ell(u)=W_\ell u+b_\ell$ and σ = ReLU, tanh…" → 函数空间的写法。
- "It is a parametric family of compositions, non-linear in θ and not a vector space." → 性质。
- "Universal approximation: with enough neurons, it can approximate any continuous function on a compact set." → 通用逼近。

**最终版答案（背诵版 EN，≤5 行）：**
For a fixed architecture: $\mathcal H=\{x\mapsto A_{L+1}\circ\sigma_L\circ A_L\circ\dots\circ\sigma_1\circ A_1(x)\}$, with $A_\ell(u)=W_\ell u+b_\ell$ and $\sigma$ = ReLU, tanh…
It is a **parametric family of compositions**, **non-linear** in $\theta$ and **not a vector space**.
**Universal approximation**: with enough neurons, it can approximate any continuous function on a compact set.

### 6.4 What are the hyperparameters of deep neural networks? 深度神经网络有哪些超参数？ ★

考过：[2023.11 Ex1 Q6](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** [第六课 · 设计问题（1/2）设定、（2/2）选择结构；深度学习中的正则化](../../Lectures/06_DL_zh.md)；超参数与参数的区别见 3.4。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

深度神经网络有哪些超参数？

**② 需要的工具**

- **参数 vs 超参数**（见 3.4）：权重和偏置是学出来的，其余设置是人定的。
- **权值衰减**：在损失里加 $\ell_2$ 惩罚，让权重不要太大（见 1.4）。
- **Dropout**：训练时随机"关掉"一部分神经元，防止网络过度依赖少数神经元。
- **早停**：验证误差开始上升时就停止训练，防止过拟合。
- **数据增强**：对训练图像做旋转、裁剪等变换，人为增加训练数据。

**③ 一步一步（分三组记）**

1. **结构**（决定函数空间）：深度（层数）、宽度（每层神经元数）、激活函数、层的类型（全连接、卷积及其核大小／步长、循环层等）。
2. **正则化**：权值衰减系数、Dropout 比例、数据增强、早停。
3. **优化**：优化器（SGD、Adam）、学习率及其调度、动量、批大小、训练轮数、初始化方式。
4. 这些都在验证集上调（常用随机搜索或贝叶斯优化，见 3.3）。代价很高，因为每试一组都要完整训练一次网络。

**④ 小例子**

一次调参的候选：层数 {2, 3, 4}、学习率 {0.1, 0.01, 0.001}、Dropout {0, 0.5}，组合起来就有 $3\times3\times2=18$ 次完整训练。

**⑤ 常见误区**

- 把权重当成超参数。
- 忘了优化相关的设置（学习率、批大小）也是超参数。

**⑥ 对照最终版**

- "Weights and biases are learned. Hyperparameters:" → 区分参数和超参数。
- "architecture (depth, width, activations, layer types);" → 结构类。
- "regularization (weight decay, dropout, early stopping);" → 正则化类。
- "optimization (optimizer, learning rate, batch size, epochs, initialization). Tuned on a validation set." → 优化类；在验证集上调。

**最终版答案（背诵版 EN，≤5 行）：**
Weights and biases are **learned**. Hyperparameters:
**architecture** (depth, width, activations, layer types);
**regularization** (weight decay, dropout, early stopping);
**optimization** (optimizer, **learning rate**, **batch size**, epochs, initialization). Tuned on a **validation set**.

### 6.5 What is the fundamental difference between deep and shallow learning? 深度学习与浅层学习的根本区别是什么？ ★

考过：[2020 A6](../Exam_2020_zh.md)

**先懂这些：** ① [第六课 · 浅层与深度学习：Vapnik 与 LeCun；从浅层到深层网络](../../Lectures/06_DL_zh.md)；② 浅层方法如何用显式惩罚控制复杂度——[第一课 · 算法家族、正则化与处理流程](../../Lectures/01_intro/02_algorithms_and_pipeline.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

深度学习和浅层学习的根本区别是什么？

**② 需要的工具**

- **浅层学习**：只有一两层变换的方法，如线性模型、SVM、核方法、决策树、Boosting。
- **人工特征**：人根据领域知识设计的输入，比如从图像里手工提取的边缘、纹理。
- **表示学习**：模型自己从原始数据里学出有用的特征。
- **显式正则化**：在目标里写明惩罚项，如 $\lambda\,\text{pen}(h)$。
- **隐式正则化**：没有写进目标，但训练方式本身限制了模型复杂度，如 SGD 的噪声、早停、Dropout、网络结构。

**③ 一步一步**

1. **浅层学习**：在**人工设计的特征**（或固定的核）上做一两层变换；通过带惩罚的风险最小化 $\min_h\hat R_n(h)+\lambda\,\text{pen}(h)$ **显式地**控制偏差—方差；通常是凸问题，有理论保证。
2. **深度学习**：把**许多非线性层**复合起来，从原始数据**端到端地自己学习表示**，而且是层次化的（低层学边缘，高层学物体部件）。
3. 深度学习的函数空间极大（通用逼近，近似误差小），优化**非凸**（用 SGD）。
4. 它的方差主要靠**隐式正则化**控制：网络结构、SGD、早停、Dropout，再加上超大的数据集。
5. 结果：在图像、语音、文本上表现突出，但需要大量数据和算力，可解释性较差。

**④ 小例子**

做人脸识别：浅层方法先由专家手工提取特征（眼距、肤色直方图等），再用 SVM 分类；深度网络直接输入像素，自己学出"边缘 → 眼睛、鼻子 → 整张脸"的层次特征。

**⑤ 常见误区**

- 说"区别只是层数多少"，没有讲到"自动学习表示"和"正则化方式不同"这两个关键点。

**⑥ 对照最终版**

- "Shallow learning uses hand-made features (or a fixed kernel) and explicit regularization …, often convex." → 浅层的特点。
- "Deep learning stacks many non-linear layers and learns the features itself, end to end." → 深度的特点。
- "It is non-convex (SGD), uses implicit regularization, and needs much data and computation." → 深度学习的优化、正则化和代价。

**最终版答案（背诵版 EN，≤5 行）：**
**Shallow** learning uses **hand-made features** (or a fixed kernel) and **explicit regularization** $\min\hat R_n(h)+\lambda\,\text{pen}(h)$, often convex.
**Deep** learning stacks **many non-linear layers** and **learns the features itself**, end to end.
It is non-convex (SGD), uses **implicit regularization**, and needs **much data and computation**.

---

## 7. 聚类（k-means、软 k-means、层次聚类）

> 六篇讲义没有完整讲 k-means 及其变体，主要靠 [Lab4](../../Exercises/Lab4/Lab4_zh.ipynb)（聚类、簇数选择）和 [Lab5](../../Exercises/Lab5/Lab5_zh.ipynb)（GMM、EM）学懂原理。一维 k-means 填表见[计算题文件](00_calculations.md)。

### 7.1 Give the k-means objective function and the pseudocode of the algorithm. 给出 k-means 的目标函数和算法伪代码。 ★★★★

考过：[2021 Ex4 a](../DataML-CHPS-2021-examen_zh.md)（只更新一个中心的变体）· [2023.3 Ex3 a](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex2 a](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 a](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 为什么均值是使组内平方和最小的点（对 $c$ 求导＝0）；② [Lab4](../../Exercises/Lab4/Lab4_zh.ipynb) k-means 部分，手动跟踪几轮迭代。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

写出 k-means 的目标函数和算法步骤（伪代码）。

**② 需要的工具**

- **聚类**：数据**没有标签**，想把相似的样本自动分成几组（见 9.3）。
- **中心 $c_j$**：每一组的"代表点"。
- **分配 $z_i$**：第 $i$ 个点属于哪一组。
- **簇内平方和 $J$（惯性）**：$J=\sum_i\|x_i-c_{z_i}\|^2$，即每个点到自己所属中心的距离平方之和。$J$ 越小，各组越紧凑。
- **为什么中心取均值**：一组点里，使"到它的距离平方和"最小的点就是这组点的平均值（对 $c$ 求导：$\sum_i2(c-x_i)=0\Rightarrow c=\text{平均}$）。

**③ 一步一步**

1. 选定组数 $k$。为什么：k-means 不会自己决定分几组（怎么选见 7.4）。
2. 初始化 $k$ 个中心：随机选 $k$ 个数据点，或用 k-means++。
3. **分配步**：每个点归到离它最近的中心（平局用固定规则）。为什么：在中心固定时，这样能让 $J$ 最小。
4. **更新步**：每个中心移到自己组的均值（空簇的处理见 7.9）。为什么：在分组固定时，均值能让 $J$ 最小。
5. 重复第 3、4 步，直到分配不再变化（或 $J$ 几乎不再下降）。

**④ 小例子**

数据 $X=\{1,2,3,10,11,12\}$，$k=2$，初始中心 $(1,2)$：

| 轮 | 中心 | 分组 | $J$ |
|---|---|---|---|
| 1 | (1, 2) | {1}、{2,3,10,11,12} | 246 |
| 2 | (1, 7.6) | {1,2,3}、{10,11,12} | 41.68 |
| 3 | (2, 11) | {1,2,3}、{10,11,12} | 4 |

第 3 轮分组不变，停止。第 2 轮的 7.6 是 $\{2,3,10,11,12\}$ 的平均值；一维时，"离谁近"只需要和两中心的中点比较（如 $(1+7.6)/2=4.3$）。

**⑤ 常见误区**

- $k$ 必须事先给定。
- 目标是**平方**距离之和，不是距离之和。
- 结果依赖初始化（见 7.3）。

**⑥ 对照最终版**

- "Objective: $J=\sum_{i=1}^N\|x_i-c_{z_i}\|^2$ (within-cluster sum of squares)." → 目标函数。
- 伪代码四行：初始化 → 分配到最近中心 → 中心更新为均值 → 直到分配不变。

**最终版答案（背诵版 EN，≤5 行）：**
Objective: $J=\sum_{i=1}^N\|x_i-c_{z_i}\|^2$ (within-cluster sum of squares).
```text
initialize k centers (random data points, or k-means++)
repeat
  assign: z_i = argmin_j ||x_i - c_j||^2
  update: c_j = mean of the points with z_i = j
until the assignments do not change
```

### 7.2 Why does the k-means procedure converge? k-means 为什么会收敛？ ★★★

考过：[2023.3 Ex3 a](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex2 a](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 a](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 7.1 的两步分别是在固定一组变量时对另一组变量**精确最小化** $J$（坐标下降）。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

为什么 k-means 一定会停下来（收敛）？用简单的论证说明。

**② 需要的工具**

- **坐标下降**：参数分成两组，轮流"固定一组、优化另一组"。k-means 的分配步和更新步正是这样轮流进行的。
- **单调有界**：一个数列如果每步都不增加，又不会低于 0，它就一定会稳定下来。
- **有限个划分**：$N$ 个点分进 $k$ 组，分法最多 $k^N$ 种，是有限的。

**③ 一步一步**

1. **分配步不会让 $J$ 变大**：中心不动时，每个点改归最近的中心，它的距离只会变小或不变。
2. **更新步不会让 $J$ 变大**：分组不动时，均值是使组内平方和最小的点（见 7.1），换成均值只会更好或不变。
3. 所以 $J\ge0$ 而且每一步都不增加，取值一定收敛。
4. 再加上划分只有有限种，固定平局规则后不会在同一组划分之间来回循环，所以算法在**有限步内停止**。
5. 停下的地方是一个稳定点（**局部**最优），不一定是全局最优（见 7.3）。

**④ 小例子**

7.1 的例子里，$J$ 依次是 246 → 41.68 → 4 → 4（不变，停止）。6 个点分 2 组，最多只有 $2^6=64$ 种分法。

**⑤ 常见误区**

- "收敛"不等于"找到全局最优"。
- 严格说，收敛的是 $J$ 的值，算法停在一个稳定的划分上。

**⑥ 对照最终版**

- "Each step cannot increase $J$: the nearest center minimizes $J$ in $z$; the mean minimizes $J$ in $c$." → 两步都不增加 $J$ 的理由。
- "$J\ge0$ keeps decreasing, and there is a finite number of partitions ($\le k^N$)." → 有下界、单调、划分有限。
- "So it stops in finite time, at a local minimum, not always the global one." → 有限步停止，但只是局部最优。

**最终版答案（背诵版 EN，≤5 行）：**
Each step **cannot increase** $J$: the nearest center minimizes $J$ in $z$; the **mean** minimizes $J$ in $c$.
$J\ge0$ keeps decreasing, and there is a **finite number of partitions** ($\le k^N$).
So it **stops in finite time**, at a **local** minimum, not always the global one.

### 7.3 Why are multiple (re)runs suggested? How can k-means approximate the globally optimal solution? 为什么建议多次运行？如何用 k-means 逼近全局最优？ ★★★

考过：[2023.3 Ex3 a](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex2 a](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 a](../DataML-CHPS-2024-examen_zh.md)（原问法：how it can be used to approximate the globally optimal solution）

**先懂这些：** 先理解 7.2 的"只保证局部最优"；在 [Lab4](../../Exercises/Lab4/Lab4_zh.ipynb) 用不同随机种子跑同一数据，比较 $J$。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

为什么建议多次运行 k-means？怎样借此逼近最好的解（全局最优）？

**② 需要的工具**

- **非凸与局部最优**：想象一片有很多山谷的地形。往下走一定会停在某个谷底，但不一定是最深的那个。k-means 的 $J$ 就是这样的地形。
- **k-means++**：一种聪明的初始化方法。第一个中心随机选，之后每个新中心按"离已选中心越远越容易被选中"（概率与距离平方成正比）来抽，让初始中心尽量分散。理论上期望意义下是 $O(\log k)$ 近似。

**③ 一步一步**

1. 用**不同的随机初始化**运行 k-means 很多次。为什么：每次可能落进不同的谷底。
2. 每次都运行到收敛。
3. 比较各次最终的 $J$，**保留最小的那次**。为什么：所有运行优化的是同一个目标、同一个 $k$，$J$ 就是唯一合理的比较标准。
4. 用 k-means++ 代替纯随机初始化，减少落入坏谷底的机会。

**④ 小例子**

数据 $X=\{1,2,10,11,20,21\}$，$k=3$：

- 坏的初始中心 $(1,2,15)$ → 收敛到 {1}、{2}、{10,11,20,21}，$J=101$。
- 好的初始中心 $(1,10,20)$ → 收敛到 {1,2}、{10,11}、{20,21}，$J=1.5$。

算法完全一样，只因起点不同，$J$ 差了 60 多倍。

**⑤ 常见误区**

- 有限次重启**不能保证**找到全局最优，只是大大降低落入坏解的概率。
- 不能用 $J$ 比较不同 $k$ 的结果，因为 $k$ 越大 $J$ 一定越小（选 $k$ 见 7.4）。

**⑥ 对照最终版**

- "$J$ is non-convex: the result depends on the initialization." → 非凸，结果取决于初始化。
- "So we run k-means many times with random starts and keep the lowest $J$." → 多次运行，取 $J$ 最小。
- "k-means++ spreads the initial centers and helps." → k-means++ 让初始中心分散。
- "This approximates the global optimum well, but with no guarantee." → 能较好地逼近，但不保证。

**最终版答案（背诵版 EN，≤5 行）：**
$J$ is **non-convex**: the result **depends on the initialization**.
So we run k-means **many times** with random starts and **keep the lowest $J$**.
**k-means++** spreads the initial centers and helps.
This approximates the global optimum well, but with **no guarantee**.

### 7.4 How do you validate the choice of the number of clusters? 如何验证聚类数目的选择？ ★★

考过：[2019 Q7](../Exam_2019_zh.md) · [2020 A5](../Exam_2020_zh.md)

**先懂这些：** [Lab4](../../Exercises/Lab4/Lab4_zh.ipynb) 簇数选择部分；[Lab5](../../Exercises/Lab5/Lab5_zh.ipynb) GMM（BIC）；与 1.5 一起复习。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

聚类时，怎样判断（验证）分几组 $k$ 才合适？

**② 需要的工具**

- **惯性 $J$**（见 7.1）：簇内平方和。$k$ 越大 $J$ 一定越小，$k=N$ 时为 0，所以不能直接选使 $J$ 最小的 $k$。
- **肘部法**：画出 $J$ 随 $k$ 变化的曲线，找"拐弯"的地方。
- **轮廓系数（silhouette）** $s(i)=\frac{b(i)-a(i)}{\max(a(i),b(i))}$：
  - $a(i)$＝点 $i$ 到**本簇**其他点的平均距离（越小说明本簇越紧）；
  - $b(i)$＝点 $i$ 到**最近的另一个簇**的平均距离（越大说明离别的簇越远）；
  - $s(i)$ 接近 1 表示分得好，接近 0 表示在边界上，负数表示可能分错了。取所有点的平均。
- **BIC／AIC**：用于 GMM 等概率模型，拟合得好会加分，参数多会扣分，自动平衡复杂度。
- **稳定性**：数据稍有变化（重采样）时，聚类结果是否基本不变。

**③ 一步一步**

1. 对一系列候选 $k$（如 1 到 10）分别跑聚类。
2. **肘部法**：画 $J(k)$，选下降明显变缓的那个 $k$。为什么：再增加组数，收益已经很小了。
3. **轮廓系数**：选平均轮廓系数最大的 $k$。也可以参考 Davies–Bouldin、Calinski–Harabasz、gap statistic 等指标。
4. 概率模型（GMM）用 **BIC／AIC** 或留出数据上的似然。
5. 检查**稳定性**：重采样后结果是否一致。
6. 结合**业务可解释性**；如果有参考标签，可以用 ARI、NMI 等外部指标。

**④ 小例子**

数据 $\{1,2,3,10,11,12\}$ 在不同 $k$ 下的最优 $J$：

| $k$ | 1 | 2 | 3 | 4 |
|---|---|---|---|---|
| $J$ | 125.5 | 4 | 2.5 | 1 |

从 $k=1$ 到 $k=2$，$J$ 从 125.5 骤降到 4；之后只是小幅下降。"肘部"在 $k=2$，与数据明显的两团一致。

轮廓系数：某个点 $a=1$、$b=4$，则 $s=(4-1)/4=0.75$，说明这个点分得很好。

**⑤ 常见误区**

- 不能直接最小化 $J$ 来选 $k$。
- 肘部有时并不明显，要结合多个指标判断。

**⑥ 对照最终版**

- "$J$ always decreases with $k$, so we cannot just minimize it." → 为什么不能直接最小化 $J$。
- "Use the elbow method, the silhouette score (choose the max), BIC / AIC for mixtures," → 三种指标。
- "stability under resampling, and domain knowledge." → 稳定性和业务知识。

**最终版答案（背诵版 EN，≤5 行）：**
$J$ always decreases with $k$, so we cannot just minimize it.
Use the **elbow method**, the **silhouette score** (choose the max), **BIC / AIC** for mixtures,
**stability** under resampling, and domain knowledge.

### 7.5 Propose a soft k-means with probabilistic assignments: definition, pseudocode, convergence. 设计一种概率分配的软 k-means：定义、伪代码、是否收敛。 ★★

考过：[2023.11 Ex2 b](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 b](../DataML-CHPS-2024-examen_zh.md)（"similar to Gaussian Mixture Modeling"）

**先懂这些：** ① [Lab5](../../Exercises/Lab5/Lab5_zh.ipynb) GMM 与 EM：E 步算责任度、M 步加权更新；② softmax 函数。这是开放设计题，必须同时写出**目标、更新规则、收敛论证**。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

设计一种"软" k-means：不再把每个点硬性分给一个簇，而是给出属于各簇的**概率**。要写出定义、伪代码，并论证是否收敛。这是开放设计题，必须同时写清**目标、更新规则和收敛理由**。

**② 需要的工具**

- **责任度（软分配）** $r_{ij}\ge0$、$\sum_jr_{ij}=1$：点 $i$ 属于簇 $j$ 的程度。硬 k-means 里它只能是 0 或 1。
- **softmax／softmin**：把一组数变成和为 1 的概率。距离越小，概率越大。
- **温度 $\tau$**：控制"软"的程度。$\tau$ 大 → 分配很平均；$\tau\to0$ → 退化成硬分配。
- **加权平均**：每个点按责任度贡献给每个中心。
- **熵**：$-\sum r\log r$，衡量分配有多分散。
- **GMM 与 EM**：高斯混合模型用 EM 算法估计。E 步算每个点属于各高斯分量的概率，M 步按这些概率加权更新参数。

**③ 一步一步**

1. **定义软分配**：$r_{ij}=\frac{\exp(-\|x_i-c_j\|^2/\tau)}{\sum_l\exp(-\|x_i-c_l\|^2/\tau)}$。为什么：离中心越近，权重按指数增大，而且对每个点归一化。
2. **E 步**：中心固定，算出所有 $r_{ij}$。
3. **M 步**：责任度固定，把中心更新为加权平均 $c_j=\sum_ir_{ij}x_i/\sum_ir_{ij}$。
4. 重复第 2、3 步，直到目标 $F$ 或中心的变化小于阈值。
5. **收敛理由**：这两步都在精确地最小化同一个目标 $F(r,c)=\sum_{ij}r_{ij}\|x_i-c_j\|^2+\tau\sum_{ij}r_{ij}\log r_{ij}$（惯性＋熵项），而 $F$ 有下界 $-N\tau\log k$。所以 $F$ 单调不增、**目标值收敛**。这个论证只保证目标值收敛，**不保证**停在局部最小点，更不保证全局最优。反例：数据 $\{-1,1\}$、两个中心都初始化为 0、$\tau=1$，责任度一直各为 $1/2$，中心不动（是不动点）；但把中心稍微分开到 $(-0.1,0.1)$，$F$ 从约 0.614 降到约 0.594，所以这个不动点不是局部最小。
6. **与 GMM 的关系**：这正是等权重、共享固定球形协方差 $\sigma^2I$ 的高斯混合模型的 EM 算法，其中 $\tau=2\sigma^2$；$\tau\to0$ 时退化为硬 k-means。

**④ 小例子**

点 $x=4$，两个中心在 2 和 7，距离平方分别是 4 和 9：

- $\tau=2$：$r=\big(e^{-2},e^{-4.5}\big)$ 归一化 $\approx(0.924,\ 0.076)$，几乎全归第一簇。
- $\tau=20$：$r=\big(e^{-0.2},e^{-0.45}\big)$ 归一化 $\approx(0.562,\ 0.438)$，两簇差不多。
- $\tau\to0$：$r=(1,0)$，就是硬 k-means。

**⑤ 常见误区**

- 只写"用概率分配"不够，必须给出具体公式、更新规则和收敛论证。
- 说"一定收敛到全局最优"是错的；说"一定收敛到局部最优"也不对，论证只能保证目标值收敛（对称初始化会卡在不是局部最小的不动点上）。

**⑥ 对照最终版**

- "Soft assignment with temperature $\tau$: $r_{ij}=\dots$" → 软分配的定义。
- "Repeat: E-step compute all $r_{ij}$; M-step $c_j=\dots$" → 伪代码。
- "Both steps do not increase $F=\dots$, which is bounded below, so the objective converges (not necessarily to a global, or even local, minimum)." → 收敛理由：只保证目标值收敛。
- "It is EM for a GMM with equal weights and a fixed shared spherical covariance." → 与 GMM 的关系。

**最终版答案（背诵版 EN，≤5 行）：**
Soft assignment with temperature $\tau$: $r_{ij}=\frac{\exp(-\|x_i-c_j\|^2/\tau)}{\sum_l\exp(-\|x_i-c_l\|^2/\tau)}$.
Repeat: **E-step** compute all $r_{ij}$; **M-step** $c_j=\sum_ir_{ij}x_i/\sum_ir_{ij}$.
Both steps do not increase $F=\sum r_{ij}\|x_i-c_j\|^2+\tau\sum r_{ij}\log r_{ij}$, which is bounded below, so the objective **converges** (not necessarily to a global, or even local, minimum).
It is **EM for a GMM** with equal weights and a fixed shared spherical covariance ($\tau=2\sigma^2$).

### 7.6 If k-means is initialized with the soft k-means solution, will the clusters change? Is it a local minimum of hard k-means? 用软 k-means 的解初始化 k-means，簇会变吗？它是硬 k-means 的局部极小吗？ ★★

考过：[2023.11 Ex2 c](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 c](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 软中心是**加权均值**，硬中心是**普通均值**（7.1 与 7.5 对比）。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

先跑软 k-means 得到一个解，再用它去初始化普通（硬）k-means，簇会不会变？换句话说，软 k-means 的解是不是硬 k-means 的局部最优？

**② 需要的工具**

- **软中心是加权平均**（见 7.5）：每个点都按责任度对每个中心有一点贡献，包括边界附近属于另一簇的点。
- **硬中心是普通平均**（见 7.1）：只用本簇的点。
- **不动点**：算法再走一步也不会改变的状态。硬 k-means 停下的地方就是它的不动点。

**③ 一步一步**

1. 软解满足的是**另一个目标** $F$ 的平衡条件，而不是硬 k-means 目标 $J$ 的平衡条件。
2. 用软中心做硬 k-means 的初始化：每个点分给最近的中心。
3. 再把每个中心更新为本簇的**普通平均**。这个平均一般和软中心不同，因为软中心里混有其他簇的点的贡献。
4. 中心一动，部分点的分配就可能改变，直到到达硬 k-means 的不动点。
5. 通常硬中心会稍微**分开**一些，因为软中心被对方簇的点"拉近"了。
6. 严格的判据是：按最近软中心做硬分配后，**每个软中心是否恰好等于它所属硬簇的普通平均**。是，则硬 k-means 一步都不会动（软解就是硬 k-means 的不动点）；否，中心就会移动。责任度接近 0／1（簇分得很开或 $\tau$ 很小）只是让两者**近似**相等，不是严格判据。

**④ 小例子（脚本计算）**

数据 $\{0,1,2,6,7,8\}$，$\tau=8$。软 k-means 收敛到中心 $(1.103,\ 6.897)$：左簇中心被右边的点拉高了一点，右簇中心被拉低了一点。

改用硬 k-means：分组为 {0,1,2} 和 {6,7,8}，普通平均是 $(1,\ 7)$，中心向外移动了约 0.1。

**⑤ 常见误区**

- 以为"软解和硬解是同一个目标的最优"，其实它们优化的目标不同。
- 把"责任度接近 0／1"当成不变的严格条件：要检查的是硬分配后中心是否等于所属样本的均值。

**⑥ 对照最终版**

- "Not necessarily. Soft centers are weighted means (every point counts a bit)." → 不一定；软中心是加权平均。
- "With hard assignments, each cluster mean is different, so k-means moves the centers and some points can change cluster." → 硬平均不同，中心会移动，分配可能改变。
- "It stays the same only if each soft center already equals the mean of its hard cluster (almost 0/1 weights make this approximately true)." → 不变的严格条件：软中心＝硬簇均值。

**最终版答案（背诵版 EN，≤5 行）：**
**Not necessarily.** Soft centers are **weighted means** (every point counts a bit).
With hard assignments, each cluster mean is different, so k-means **moves the centers** and some points can change cluster.
It stays the same only if each soft center already **equals the mean of its hard cluster** (almost 0/1 weights make this approximately true).

### 7.7 Compare hard and soft k-means. When is soft k-means preferable? 比较硬 k-means 和软 k-means。什么时候软 k-means 更合适？ ★★

考过：[2023.11 Ex2 d](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 c](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 7.5、7.6；[Lab5](../../Exercises/Lab5/Lab5_zh.ipynb) 中 GMM 与 k-means 的对比。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

比较硬 k-means 和软 k-means（或 GMM）。什么情况下更适合用软的？

**② 需要的工具**

- **硬分配**：每个点只属于一个簇（见 7.1）。
- **软分配**：每个点属于各簇的概率（见 7.5）。
- **GMM 的协方差**：允许每个簇有自己的形状和大小（椭圆形），而不只是圆形。
- **退火**：先用大的 $\tau$（很软），再逐渐减小，可以帮助避开不好的局部最优。

**③ 一步一步（逐项比较）**

1. **输出**：硬的只给出"属于哪一组"；软的给出"属于各组的概率"，能**表达边界点的不确定性**。
2. **计算**：硬的简单、快，每轮 $O(Nkd)$，不用存储责任度；软的要算并存储 $N\times k$ 个概率，代价更大。
3. **收敛**：硬的在有限步内停止；软的目标值收敛，但通常要设阈值才停。
4. **形状**：硬 k-means 和固定球形协方差的软 k-means 都偏好圆形簇；完整协方差的 GMM 能表示**大小不同的椭圆簇**。
5. **额外选择**：软方法需要选 $\tau$ 或概率模型的设定。
6. **鲁棒性**：两者都不会自动对离群点稳健。
7. **什么时候用软的**：簇**互相重叠**时；后续决策需要**隶属概率**时（如风险评估、客户同时具有多种特征）；需要一个密度模型时。

**④ 小例子**

客户分群中，一个客户 60% 像"价格敏感型"、40% 像"品质优先型"。硬 k-means 只会说他是"价格敏感型"；软方法会保留 60%／40% 的信息，营销时可以针对两种偏好都做推荐。

**⑤ 常见误区**

- 软的不一定"更好"，只在需要概率或簇有重叠时才更有价值。

**⑥ 对照最终版**

- "Hard: one cluster per point, simple and fast, but boundary points are forced into one cluster." → 硬的优缺点。
- "Soft: gives membership probabilities and shows uncertainty; a GMM can model elliptical clusters." → 软的优点。
- "But it costs more and needs $\tau$ or a model." → 软的代价。
- "Use soft when clusters overlap or when probabilities are needed." → 适用场景。

**最终版答案（背诵版 EN，≤5 行）：**
**Hard**: one cluster per point, **simple and fast**, but boundary points are forced into one cluster.
**Soft**: gives **membership probabilities** and shows **uncertainty**; a GMM can model elliptical clusters.
But it costs more and needs $\tau$ or a model.
Use soft when clusters **overlap** or when probabilities are needed.

### 7.8 Summarize the dataset by two "typical" examples (the centers): how well does each center represent its cluster? 用两个"典型"样本（中心）概括数据：每个中心代表其簇的效果如何？ ★★

考过：[2021 Ex4 c](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex3 d](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** 中心（均值，合成原型）与 medoid（真实样本）的区别；簇内 MSE 作为"代表性"的度量。具体数值见两卷参考答案。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

聚类完成后，用两个"典型"样本概括整个数据集，并比较每个代表对自己所在簇代表得好不好、为什么。

**② 需要的工具**

- **中心（均值）**：使簇内平方距离最小的点，是一个"合成"的原型，不一定是真实数据。
- **medoid（中心样本）**：簇里到其他成员平均距离最小的那个**真实样本**。一维时就是中位数。
- **簇内 MSE**：簇内各点到代表点距离平方的平均，越小代表得越好。

**③ 一步一步**

1. 两个典型样本就是两个**簇中心**。如果题目要求必须是真实数据点，就取 **medoid** 或离中心最近的点。
2. 对每个簇算簇内 MSE（或看分散程度）。
3. **紧凑**的簇代表得好；**分散**、内部还有子群或含离群点的簇代表得差，它的均值可能落在一个根本没有数据的空白处。
4. 如果中心不是本簇的均值（如 2021 年那题里人为**固定**的中心），它天然就不是最优代表。
5. 用 MSE 的数值对比支撑你的结论。

**④ 小例子（2021 年真题）**

两个簇 {10,15,20,25} 和 {55,60,90,100}，中心是 17.5 和 80（80 是固定的）：

- 簇 1 很紧凑，簇内 MSE 为 31.25，代表得好。
- 簇 2 内部有 {55,60} 和 {90,100} 两小群，而且 80 不是它的均值（均值是 76.25），簇内 MSE 高达 381.25；80 附近也根本没有数据。
- 结论：簇 1 被代表得好得多。

完整计算见[计算题 C2](00_calculations.md)。

**⑤ 常见误区**

- 只写出两个数，不做比较、不给理由，会丢分。
- 中心不一定是真实数据点，题目要求"真实样本"时要用 medoid。

**⑥ 对照最终版**

- "The two typical examples are the centers (means); if a real point is needed, the medoid." → 代表是谁。
- "A compact cluster is well represented (small MSE)." → 紧凑的簇代表得好。
- "A spread cluster, or one with sub-groups or outliers, is badly represented: its mean can lie where there is no data." → 分散的簇代表得差。
- "A fixed center (not the mean) is worse." → 固定中心更差。

**最终版答案（背诵版 EN，≤5 行）：**
The two typical examples are the **centers** (means); if a real point is needed, the **medoid**.
A **compact** cluster is well represented (small MSE).
A **spread** cluster, or one with sub-groups or outliers, is badly represented: its mean can lie where there is no data.
A **fixed** center (not the mean) is worse.

### 7.9 During k-means, how can a cluster become empty? Give heuristics to continue without reducing k. k-means 中簇为什么会变空？给出不减少 k 的处理办法。 ★

考过：[2021 Ex4 e](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** 7.1 的分配步：一个中心如果不是任何点的"最近中心"，它的簇就是空的。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

k-means 运行过程中，为什么会出现某个簇一个点也没有（空簇）？怎样处理，才能不减少簇数 $k$ 继续运行？

**② 需要的工具**

- **分配步**（见 7.1）：每个点只归最近的中心。
- **均值**：空集没有均值，更新步就没法算了。
- **误差最大的点**：离自己当前中心最远的点，它是"被代表得最差"的点。

**③ 一步一步**

1. **原因**：分配步中，如果**没有任何点把 $c_j$ 当作最近的中心**，簇 $j$ 就空了。
2. 常见情形：初始中心离数据太远，或两个中心几乎重合；也可能是其他中心在更新中移动过来，把它的点全部"抢走"了。
3. **处理办法**（保持 $k$ 不变）：
   - 把空中心移到**误差最大的点**上（这样还会降低 $J$）；
   - **拆分惯性最大的簇**：把空中心放到该簇的随机点或最远点上；
   - 均匀随机选一个数据点重新初始化；或按 **k-means++ 的规则**选：以到最近已有中心的**距离平方为权重**抽一个点（离现有中心越远越容易被选中），这不是普通的均匀随机抽点。
4. 然后继续迭代。

**④ 小例子**

数据 $\{1,2,3,10,11,12\}$，$k=3$，初始中心 $(1,2,50)$：每个点都离 1 或 2 更近，中心 50 一个点也分不到，成了空簇。各点到当前中心的距离平方中，12 最大（到中心 2 的距离平方是 100），于是把空中心移到 12，继续迭代。

**⑤ 常见误区**

- 直接删掉空簇（这样 $k$ 就变小了，不符合题目要求）。

**⑥ 对照最终版**

- "A cluster is empty when no point is closest to its center (bad initialization, or other centers took its points)." → 原因。
- "Fixes: move the center to the point with the largest error, or split the biggest cluster, or re-seed it (uniformly at random, or by the k-means++ rule: sampling with probability ∝ squared distance to the nearest center)." → 三种处理办法；k-means++ 是按距离平方加权抽样。

**最终版答案（背诵版 EN，≤5 行）：**
A cluster is empty when **no point is closest to its center** (bad initialization, or other centers took its points).
Fixes: move the center to the **point with the largest error**, or **split the biggest cluster**, or **re-seed** it (uniformly at random, or by the **k-means++** rule: probability ∝ squared distance to the nearest center).

### 7.10 What if the initial clusters are formed by assigning each point uniformly at random? Will it converge, faster or slower? 如果初始化时把每个点等概率随机分到某个簇，会收敛吗？更快还是更慢？ ★

考过：[2023.3 Ex3 b](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** 大数定律：随机子集的均值≈全体均值；对比 7.3 的 k-means++。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

如果初始化时把每个点**等概率随机**分到某个簇（而不是随机挑 $k$ 个点当中心），效果和常规方法比怎样？还会收敛吗？更快还是更慢？

**② 需要的工具**

- **大数定律**：随机抽的样本越多，样本平均值越接近总体平均值。
- **常规初始化**：随机选 $k$ 个不同的数据点当中心，或 k-means++、k-最远点初始化，中心一开始就分散在数据各处。
- **7.2 的收敛论证**：$J$ 单调不增，划分有限。

**③ 一步一步**

1. 随机划分时，每个初始簇都是整个数据集的一个随机样本。
2. 由大数定律，各簇的均值（初始中心）都**挤在全局均值附近**，空间覆盖很差；$N$ 小时还可能出现空簇。
3. 常规策略一开始就把中心**分散**到不同区域。
4. **仍然收敛**：理由和 7.2 一样（$J$ 单调不增、划分有限）。
5. 和把中心分散开的初始化（如 k-means++）相比，**可能更慢**：几乎重合的中心常要先花几轮才分开。
6. 也**可能**更容易落入较差的局部最优。注意 5、6 都只是**倾向**，不能从"中心靠近全局均值"必然推出：速度和解的质量取决于数据、具体初始化和拿来比较的方法（下面的小例子里它一步就分对了）。

**④ 小例子**

数据 $\{1,2,3,10,11,12\}$（全局均值 6.5），随机分成 {1,10,3} 和 {2,11,12}，初始中心是 4.667 和 8.333，都离 6.5 不远；而真正的两团在 2 和 11 附近。如果随机挑两个点当中心，比如挑到 2 和 11，第一步就已经是正确答案了。不过这个例子里随机划分也不差：两个中心的中点是 6.5，第一次分配就得到 {1,2,3} 和 {10,11,12}，同样一步到位。数据分得这么开时差别不大；簇多、簇间距小时，挤在一起的初始中心才更容易出问题。

**⑤ 常见误区**

- 以为随机划分"更随机所以更好"。
- 把"更慢、更差"说成必然结果：它们只是常见倾向，取决于数据和比较对象。

**⑥ 对照最终版**

- "Each random cluster is a sample of the whole data, so all initial centers are near the global mean (law of large numbers)." → 初始中心挤在一起。
- "It still converges (same argument as 7.2), but it can be slower, because the centers must first separate." → 仍收敛，但可能更慢。
- "It may also end more often in a bad local optimum (this depends on the data)." → 可能更容易得到差的解，取决于数据。

**最终版答案（背诵版 EN，≤5 行）：**
Each random cluster is a sample of the whole data, so all initial centers are **near the global mean** (law of large numbers).
It **still converges** (same argument as 7.2), but it can be **slower**, because the centers must first separate.
It may also end more often in a **bad local optimum** (this depends on the data).

### 7.11 Give three linkage criteria for hierarchical agglomerative clustering, with formulas. 给出层次凝聚聚类的三种连接准则及公式。 ★

考过：[2023.3 Ex3 e](../DataML-CHPS-2022-examen_zh.md)（树状图：[2022_linkage.png](../Answers/2022_linkage.png)）

**先懂这些：** 凝聚聚类流程：从单点簇开始，每次合并距离最近的两个簇；[Lab4](../../Exercises/Lab4/Lab4_zh.ipynb)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

层次凝聚聚类常用的簇间"连接准则"有哪些？写出公式。（2023.3 还要求在给定的点上画出树状图，见[计算题 C5](00_calculations.md)。）

**② 需要的工具**

- **层次凝聚聚类**：一开始每个点自成一簇，每次把**最近的两个簇**合并，直到只剩一个簇。
- **树状图（dendrogram）**：记录合并顺序和合并时的距离（高度）的树。在某个高度横着切一刀，就得到相应数目的簇。
- **连接准则**：定义"两个簇之间的距离"。点和点的距离好定义，簇和簇的距离有多种定义方式。

**③ 一步一步**

1. 每个点自成一簇。
2. 用连接准则算出所有簇对之间的距离，合并最近的一对，记下合并高度。
3. 重复，直到只剩一个簇，画出树状图。
4. 四种常用的连接准则（$A$、$B$ 是两个簇）：
   - **单连接** $\min_{a\in A,b\in B}\|a-b\|$：两簇**最近**的两个点之间的距离。能找出细长形状，但有**链式效应**（一串点会被一个个连成一长条）。
   - **全连接** $\max_{a\in A,b\in B}\|a-b\|$：两簇**最远**的两个点之间的距离。倾向于形成直径相近的**紧凑**簇，对离群点敏感。
   - **平均连接** $\frac1{|A||B|}\sum_{a\in A}\sum_{b\in B}\|a-b\|$：所有点对距离的平均，是前两者的折中。
   - **Ward**：合并使**簇内惯性增加最少**的一对，$\Delta=\frac{|A||B|}{|A|+|B|}\|\mu_A-\mu_B\|^2$，思路接近 k-means。

**④ 小例子**

簇 $A=\{10,15\}$，$B=\{20,25\}$：

- 单连接 $=20-15=5$；
- 全连接 $=25-10=15$；
- 平均连接 $=(10+15+5+10)/4=10$。

同样两个簇，三种准则给出三个不同的距离，所以合并顺序和树状图也会不同。

**⑤ 常见误区**

- 只写名字不写公式。
- 把单连接和全连接的 min、max 写反。

**⑥ 对照最终版**

- "Start from single points and merge the two closest clusters (this gives a dendrogram)." → 算法流程。
- "Single: min (chaining). Complete: max (compact clusters)." → 单连接、全连接。
- "Average: … Ward: merge with the smallest increase of inertia." → 平均连接、Ward。

**最终版答案（背诵版 EN，≤5 行）：**
Start from single points and **merge the two closest clusters** (this gives a dendrogram).
**Single**: $\min_{a,b}\|a-b\|$ (chaining). **Complete**: $\max_{a,b}\|a-b\|$ (compact clusters).
**Average**: $\frac1{|A||B|}\sum_{a,b}\|a-b\|$. **Ward**: merge with the smallest increase of inertia.

### 7.12 Use bootstrapped k-means solutions to compute an outlier score; compare with Isolation Forest. 用多次 bootstrap 的 k-means 解计算离群分数，并与 Isolation Forest 比较。 ★

考过：[2024 Ex5 d](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① bootstrap（有放回重采样）——[第五课 · 一般而言，bootstrap 是什么？](../../Lectures/05_NLM_zh.md)；② Isolation Forest 原理——[Lab3](../../Exercises/Lab3/Lab3_zh.ipynb) 异常检测部分。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

设计一个流程：多次在 bootstrap 样本上跑 k-means，为每个数据点算一个"离群分数"。再和 Isolation Forest 比较各自的性质。

**② 需要的工具**

- **bootstrap**：有放回重采样（见 2.3）。
- **离群分数**：衡量一个点有多"异常"的数，越大越可疑。
- **按簇尺度归一化**：一个点离中心 5，在很分散的簇里正常，在很紧凑的簇里就异常，所以要除以簇的分散程度 $v$。
- **Isolation Forest（孤立森林）**：用很多棵随机切分的树。异常点和别人离得远，随机切几刀就会被单独"隔离"出来；正常点则要切很多刀。

**③ 一步一步**

1. 对 $b=1,\dots,B$：抽一份 bootstrap 样本，在上面跑 k-means（多次初始化）。
2. 对每个点 $x_i$ 算分数，例如到最近中心的距离平方，再除以该簇的尺度：$s_b(x_i)=\min_j\|x_i-c_{bj}\|^2/(v_{bj}+\varepsilon)$。$\varepsilon$ 是一个很小的正数，防止除以 0。
3. 把 $B$ 次的分数取**均值或中位数**，作为最终离群分数（也可以只用 $x_i$ 不在其 bootstrap 样本里的那些轮）。
4. 在验证数据上定一个阈值，分数超过阈值就报为异常。
5. **性质**：多次重采样平均掉了单次 k-means 的随机性，分数更稳定；但 k-means **本身不稳健**：离群点会把中心拉偏甚至自成一簇，小而正常的簇可能被误报，结果还依赖 $k$、尺度和距离，并假设簇大致是圆形的。
6. **和 Isolation Forest 比较**：IF 用随机切分，异常点的平均路径更短；不需要距离、中心或 $k$，速度快，能处理不规则形状。两者没有绝对优劣，应在相同数据和准则下比较。

**④ 小例子**

数据大部分在两团（一维，都落在 0 到 13 之间：2 附近一团、11 附近一团），另有一个点在 40，取 $k=2$。这是示意，不是实际运行结果：

- **40 不在这份 bootstrap 样本里的轮次**：每个中心都是样本点的平均，所以都在 0 到 13 之间，40 到最近中心的距离平方至少 $(40-13)^2=729$，远大于其他点的个位数。这种轮次里它的分数**一定**很高。
- **40 被抽到（甚至抽到好几次）的轮次**：k-means 可能把 11 那团和 40 合成一簇，也可能干脆给 40 单独一个中心，这时它的距离甚至是 0、分数最低——这正是"离群点会自成一簇"的问题。

所以单轮结果不可靠：取**中位数**，或者只用 40 不在样本里的轮次（第 ③ 步括号里的做法），40 的分数才会稳定地排在最前面。

**⑤ 常见误区**

- 不按簇的尺度归一化，导致分散的簇里的正常点也被报为异常。
- 以为 bootstrap 能让 k-means 变得对离群点稳健。

**⑥ 对照最终版**

- "For $b=1..B$: take a bootstrap sample, run k-means, and score each point by its (normalized) distance to the nearest center. The outlier score is the mean / median over the runs." → 流程。
- "It is more stable than one run, but k-means is not robust and assumes round clusters." → 性质。
- "Isolation Forest uses random splits: outliers are isolated quickly; no centers, no $k$." → 与 IF 的比较。

**最终版答案（背诵版 EN，≤5 行）：**
For $b=1..B$: take a **bootstrap sample**, run k-means, and score each point by its **(normalized) distance to the nearest center**. The outlier score is the **mean / median** over the runs.
It is more stable than one run, but k-means is **not robust** and assumes round clusters.
**Isolation Forest** uses random splits: outliers are **isolated quickly**; no centers, no $k$.

---

## 8. 稳健估计（RANSAC）与概率图模型

> RANSAC 主要靠[作业一第 1 题讲解](../../Exercises/Assignment1/guide/01_ransac.md)和 [Lab1](../../Exercises/Lab1/Lab1_zh.ipynb)，图模型靠 [Lab5](../../Exercises/Lab5/Lab5_zh.ipynb)。2023.11 和 2024 的报警题完全相同，且**题面缺一个条件概率** $q=P(a=0\mid c=0)$；数值计算见[计算题文件](00_calculations.md)。

### 8.1 Describe the standard RANSAC method and algorithm for linear regression. 详细描述用于线性回归的标准 RANSAC 方法和算法。 ★★★

考过：[2023.3 Ex2 c](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex4 c](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex4 b](../DataML-CHPS-2024-examen_zh.md)（推广到圆，见 8.5）

**先懂这些：** ① OLS 对离群点敏感（5.3）；② [作业一第 1 题：RANSAC](../../Exercises/Assignment1/guide/01_ransac.md)，把算法亲手实现一遍；③ "最小样本"＝确定模型所需的最少点数（直线 2 个、圆 3 个）。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

详细描述 RANSAC：一种在数据里混有很多"坏点"时，仍能稳健地拟合直线的方法。

**② 需要的工具**

- **离群点（outlier）与内点（inlier）**：离群点是远离大多数数据的坏点（如传感器故障造成的读数）；内点是符合模型的正常点。
- **为什么 OLS 不行**：OLS 平方了误差，一个离群点就能把直线拉歪（见下面的例子）。
- **最小样本**：确定一个模型所需的最少点数。直线 2 个，圆 3 个（见 8.5）。
- **阈值 $\tau$**：残差小于 $\tau$ 的点才算内点，$\tau$ 应与正常噪声的大小相当（见 8.2）。
- **共识集（consensus set）**：某个候选模型的全部内点，越大说明支持这个模型的点越多。

**③ 一步一步**

1. 随机抽**最小样本**：2 个横坐标不同的点。为什么：点越少，越有可能抽到的全是内点。
2. 过这 2 个点画一条候选直线。
3. 计算**所有**点到这条直线的残差。
4. 残差 $\le\tau$ 的点构成**共识集**。
5. 如果这个共识集比目前最好的还大（平局时比内点误差），就保存它。
6. 重复第 1–5 步共 $T$ 次。
7. 最后用最佳共识集里的**全部内点**重新做一次 OLS。为什么：只用 2 个点确定的直线受噪声影响大，用所有内点重拟合更准。

**$T$ 的公式怎么来**：设内点比例为 $w$。一次抽 2 个点全是内点的概率是 $w^2$，失败概率是 $1-w^2$；$T$ 次全部失败的概率是 $(1-w^2)^T$。要求"至少成功一次"的概率不低于 $p$，即 $(1-w^2)^T\le1-p$，解得 $T\ge\frac{\log(1-p)}{\log(1-w^2)}$。一般地，最小样本有 $s$ 个点时把 $w^2$ 换成 $w^s$。注意 $w^s$ 是**近似**：它假设每次抽点相互独立（相当于放回抽样），点很多时与"抽 $s$ 个不同的点"几乎一样；点很少时要用精确概率 $\binom{n_\text{in}}{s}/\binom{n}{s}$。

**④ 小例子**

5 个点：(0,0)、(1,1)、(2,2)、(3,3)、(4,20)，最后一个是离群点。

- OLS 结果是 $y=4.2x-3.2$，被一个坏点拉得面目全非（真实规律是 $y=x$）。
- RANSAC 若抽到 (1,1) 和 (3,3)，得到 $y=x$；取 $\tau=0.5$，前 4 个点都是内点，共识集大小为 4。
- 若抽到 (3,3) 和 (4,20)，得到斜率 17 的直线，只有这 2 个点自己是内点，共识集大小为 2，被淘汰。
- 用 4 个内点重拟合，得到 $y=x$。
- 迭代次数：用常见近似公式，$w=0.8$、$p=0.99$ 时 $T\ge\log(0.01)/\log(1-0.8^2)=\log(0.01)/\log(0.36)\approx4.5$，取 5 次。但这个例子只有 5 个点，每轮抽 2 个**不同**的点，抽到 2 个内点的精确概率是 $\binom42/\binom52=6/10=0.6$（不是 $0.8^2=0.64$），精确要求是 $T\ge\log(0.01)/\log(0.4)\approx5.03$，即 **6 次**。点很多时两者几乎没有差别。

**⑤ 常见误区**

- $\tau$ 太小会丢掉正常点，太大会混进坏点（见 8.2）。
- 结果有随机性；最后一定要用全部内点重拟合。

**⑥ 对照最终版**

- 伪代码五行：重复 $T$ 次 → 随机取 2 点得直线 → 残差 $\le\tau$ 的是内点 → 保留内点最多的直线 → 最后在最佳内点集上做 OLS。
- "Choose $T\ge\frac{\log(1-p)}{\log(1-w^2)}$ ($w$ = inlier ratio). It is robust to many outliers." → 迭代次数公式；能容忍大量离群点。

**最终版答案（背诵版 EN，≤5 行）：**
```text
repeat T times:
  pick 2 random points -> line y = a x + b
  inliers I = { i : |y_i - a x_i - b| <= tau }
  keep the line with the largest I
refit the line by OLS on the best inlier set
```
Choose $T\ge\frac{\log(1-p)}{\log(1-w^2)}$ ($w$ = inlier ratio). It is robust to many **outliers**.

### 8.7 Give the graphical model of the battery–sensor–alarm system and write the joint distribution. 给出电池—传感器—报警系统的概率图模型并写出联合分布。 ★★

考过：[2023.11 Ex3 a](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex3 a](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 有向图模型（贝叶斯网络）：联合分布＝各节点在给定父节点下的条件分布之积；② [Lab5](../../Exercises/Lab5/Lab5_zh.ipynb) 图模型部分。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

为"电池 → 传感器 → 报警器"系统画出概率图模型，写出联合分布，并把手册给的信息翻译成概率表达式。

**② 需要的工具**

- **随机变量**：$b$＝电池（1 正常／0 失效），$c$＝传感器（1 正常／0 失效），$a$＝报警（1 响／0 不响）。
- **条件概率** $P(A\mid B)$：已知 $B$ 发生时 $A$ 发生的概率。例：$P(c=0\mid b=0)$＝电池坏了的情况下传感器也坏的概率。
- **有向图模型（贝叶斯网络）**：用箭头表示"谁直接影响谁"的有向无环图。
- **分解规则**：联合分布＝每个变量在给定它的"父节点"（箭头指向它的变量）下的条件概率之积，即 $p(x_1,\dots,x_n)=\prod_ip(x_i\mid\text{父节点})$。
- **互补概率**：$P(\text{不发生})=1-P(\text{发生})$。

**③ 一步一步**

1. **画图**：电池给传感器供电（$b\to c$），传感器把信息送给报警器（$c\to a$），得到链 $b\to c\to a$。
2. **写分解**：$p(a,b,c)=p(b)\,p(c\mid b)\,p(a\mid c)$。为什么 $a$ 只依赖 $c$：报警器只"看得见"传感器，看不见电池。这等价于假设 $a\perp b\mid c$。
3. **翻译手册**：
   - 电池失效概率 0.1 → $P(b=0)=0.1$，$P(b=1)=0.9$；
   - 电池正常时传感器失效 0.01 → $P(c=0\mid b=1)=0.01$；
   - 电池失效时传感器失效 0.3 → $P(c=0\mid b=0)=0.3$；
   - 传感器正常时报警静默 0.99 → $P(a=0\mid c=1)=0.99$。
4. **指出缺失**：手册**没有给出**传感器失效时报警静默的概率，记为 $q=P(a=0\mid c=0)$，保留为参数，不要自己编一个值。

**④ 小例子**

用分解算一个联合概率："电池正常、传感器正常、报警不响"：$P(b=1,c=1,a=0)=0.9\times0.99\times0.99=0.88209$。这是最常见的情形。

**⑤ 常见误区**

- 箭头方向画反（应按因果方向：电池 → 传感器 → 报警）。
- 自己假设 $q=0$ 或 $q=1$ 而不说明。

**⑥ 对照最终版**

- "Chain $b\to c\to a$: $p(a,b,c)=p(b)p(c\mid b)p(a\mid c)$, so $a\perp b\mid c$." → 图和分解。
- "Data: $P(b=0)=0.1$, $P(c=0\mid b=1)=0.01$, $P(c=0\mid b=0)=0.3$, $P(a=0\mid c=1)=0.99$." → 手册翻译。
- "$P(a=0\mid c=0)=q$ is not given." → 缺失的条件。

**最终版答案（背诵版 EN，≤5 行）：**
Chain **$b\to c\to a$**: $p(a,b,c)=p(b)\,p(c\mid b)\,p(a\mid c)$, so $a\perp b\mid c$.
Data: $P(b=0)=0.1$, $P(c=0\mid b=1)=0.01$, $P(c=0\mid b=0)=0.3$, $P(a=0\mid c=1)=0.99$.
$P(a=0\mid c=0)=q$ is **not given**.

### 8.8 Are a and b independent? (conditional vs marginal independence) a 和 b 独立吗？（条件独立与边际独立） ★★

考过：[2023.11 Ex3 b](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex3 b](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 链 $b\to c\to a$ 中，观测到 $c$ 会"阻断"路径；② 边际独立要用全概率公式真正算出来比较。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

报警 $a$ 和电池 $b$ 独立吗？要先给出 $p(a=1\mid b,c)$ 的 2×2 表，再分别讨论**条件独立**和**边际独立**。

**② 需要的工具**

- **独立**：知道一个变量的取值，对另一个变量的概率没有任何影响，即 $P(a\mid b)=P(a)$。
- **条件独立** $a\perp b\mid c$：**已知 $c$ 的情况下**，再知道 $b$ 对 $a$ 没有额外帮助，即 $P(a\mid b,c)=P(a\mid c)$。
- **全概率公式**：$P(a\mid b)=\sum_cP(a\mid c)P(c\mid b)$，把中间变量 $c$ 的所有可能情况加起来。
- **"阻断"直觉**：在链 $b\to c\to a$ 里，信息必须经过 $c$ 才能从 $b$ 传到 $a$。一旦知道了 $c$，这条路就被"堵住"了。

**③ 一步一步**

1. **填表**：链结构下 $p(a=1\mid b,c)=p(a=1\mid c)$，与 $b$ 无关，所以两行相同：$c=0$ 列为 $1-q$，$c=1$ 列为 $1-0.99=0.01$。
2. **条件独立**：两行相同，正说明给定 $c$ 时 $a\perp b$。
3. **边际独立**：$c$ 未知时，用全概率公式分别算 $b=1$ 和 $b=0$ 时的报警概率：
   - $P(a=1\mid b=1)=0.99\times0.01+0.01\times(1-q)=0.0199-0.01q$；
   - $P(a=1\mid b=0)=0.7\times0.01+0.3\times(1-q)=0.307-0.3q$。
4. 两者只在 $q=0.99$ 时相等。$q=0.99$ 意味着报警根本不看传感器状态，是退化情况。其他情况下 $a$ 和 $b$ **不边际独立**。
5. 结论：**条件独立推不出边际独立**，要通过计算判断，不能只看图下结论。

**④ 小例子**

取 $q=0.5$：电池正常时报警概率 $0.0149$，电池失效时 $0.157$，差了 10 倍。可见电池状态会影响报警，即二者不独立。

**⑤ 常见误区**

- 看到图上有一条路径，就无条件断言"一定相关"（$q=0.99$ 是反例）。
- 把条件独立和边际独立混为一谈。

**⑥ 对照最终版**

- "Given $c$, $a$ and $b$ are independent: both rows of the table $p(a=1\mid b,c)$ are equal ($1-q$ and $0.01$)." → 条件独立，表两行相同。
- "But they are not marginally independent: $P(a=1\mid b)=\sum_cP(a=1\mid c)P(c\mid b)$ differs for $b=0$ and $b=1$ (except if $q=0.99$)." → 边际上不独立，除了 $q=0.99$ 这个特例。

**最终版答案（背诵版 EN，≤5 行）：**
Given $c$, **$a$ and $b$ are independent**: both rows of the table $p(a=1\mid b,c)$ are equal ($1-q$ and $0.01$).
But they are **not marginally independent**: $P(a=1\mid b)=\sum_cP(a=1\mid c)P(c\mid b)$ differs for $b=0$ and $b=1$ (except if $q=0.99$).

### 8.9 How do you compute P(battery fails | no alarm) from the model? 如何用模型计算"没听到报警时电池失效"的概率？ ★★

考过：[2023.11 Ex3 c–d](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex3 c–d](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 全概率公式（对未观测变量求和＝边缘化）与 Bayes 公式；数值答案见两卷参考答案。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

（c）报警器保持静默的概率是多少？（d）没听到报警、也不知道传感器好不好时，电池坏了的概率是多少？

**② 需要的工具**

- **全概率公式（边缘化）**：不知道某个中间变量时，把它的所有可能取值都加起来，例如 $P(c=0)=\sum_bP(c=0\mid b)P(b)$。用途：从条件概率算出单个变量的概率。
- **乘法法则**：$P(A,B)=P(A\mid B)P(B)$。用途：算两个事件同时发生的概率。
- **Bayes 公式**：$P(B\mid A)=\frac{P(A,B)}{P(A)}$。用途：从"原因 → 结果"的概率反推"看到结果后，原因的概率"。
- **先验与后验**：先验＝观察之前的概率（电池坏的概率 0.1）；后验＝观察到证据（没报警）之后更新的概率。

**③ 一步一步**

1. 对 $b$ 求和，得到传感器失效的概率：$P(c=0)=0.9\times0.01+0.1\times0.3=0.039$，所以 $P(c=1)=0.961$。
2. 对 $c$ 求和，得到静默的概率：$P(a=0)=0.99\times0.961+q\times0.039=$ **$0.95139+0.039q$**。这是第 (c) 问的答案。
3. 算"电池坏且静默"的联合概率：$P(a=0,b=0)=0.1\times(0.7\times0.99+0.3q)=0.0693+0.03q$。
4. 代入 Bayes 公式：$P(b=0\mid a=0)=\frac{0.0693+0.03q}{0.95139+0.039q}$。这是第 (d) 问的答案。
5. 因为题目没给 $q$，结果必须保留 $q$。$q$ 从 0 取到 1 时，结果约在 0.0728 到 0.1003 之间。
6. 直观解释：一般情况下，没听到报警会让"电池坏了"的可能性略低于先验的 0.1；但如果传感器坏时报警必定静默（$q$ 接近 1），后验会略高于 0.1。临界点正好是 $q=0.99$。

**④ 小例子**

取 $q=0.5$：$P(a=0)=0.97089$，$P(a=0,b=0)=0.0843$，后验 $=0.0843/0.97089\approx0.087$，比先验 0.1 略低。完整计算表见[计算题 C3](00_calculations.md)。

**⑤ 常见误区**

- 忘记题目缺 $q$，自己随便填一个数。
- 把 $P(a=0\mid b=0)$ 和 $P(b=0\mid a=0)$ 搞混，前者是"电池坏时静默的概率"，后者才是题目问的。

**⑥ 对照最终版**

- "Sum out the unknown variables, then use Bayes:" → 先边缘化，再用 Bayes。
- "$P(c=0)=0.039$, $P(a=0)=0.95139+0.039q$, $P(a=0,b=0)=0.0693+0.03q$," → 三个中间结果。
- "so $P(b=0\mid a=0)=\frac{0.0693+0.03q}{0.95139+0.039q}$ (between 0.073 and 0.100)." → 最终答案及范围。

**最终版答案（背诵版 EN，≤5 行）：**
**Sum out** the unknown variables, then use **Bayes**:
$P(c=0)=0.039$, $P(a=0)=0.95139+0.039q$, $P(a=0,b=0)=0.0693+0.03q$,
so $P(b=0\mid a=0)=\frac{0.0693+0.03q}{0.95139+0.039q}$ (between 0.073 and 0.100).

### 8.2 How sensitive is RANSAC to its parameters? RANSAC 对参数的敏感性如何？ ★

考过：[2023.3 Ex2 c](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** 8.1 的三个参数；在作业一中改变 $\tau$ 看内点集的变化。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

RANSAC 的结果对它的参数有多敏感？

**② 需要的工具**

- **RANSAC 的参数**（见 8.1）：内点阈值 $\tau$、迭代次数 $T$、（可选）最小共识集大小。
- **噪声尺度**：正常数据围绕真实模型的波动大小，例如标准差。
- **MAD（中位数绝对偏差）**：一种不受离群点影响的波动估计。

**③ 一步一步（逐个参数）**

1. **阈值 $\tau$**（最关键）：
   - 太**小**：正常但带噪声的点被当成离群点，共识集很小，拟合不稳定；
   - 太**大**：离群点也被当成内点，失去稳健性；
   - 应与噪声尺度匹配，比如内点噪声标准差的几倍，或用 MAD 估计。
2. **迭代次数 $T$**：
   - 太小：可能一次也没抽到全是内点的样本，从而错过真实模型；
   - 太大：只是多花计算时间；
   - 内点比例 $w$ 越低、最小样本点数 $s$ 越多，所需 $T$ 增长越快（公式见 8.1）。
3. **最小共识集大小**：太高则什么模型都不被接受；太低则可能接受虚假模型。
4. **随机性**：每次运行结果可能不同，应固定随机种子或多次运行。用内点误差打破平局、最后用全部内点重拟合，都能降低敏感性。

**④ 小例子**

成功概率要求 0.99 时所需的迭代次数：

| | $w=0.5$ | $w=0.7$ |
|---|---|---|
| 直线 $s=2$ | 17 | 7 |
| 圆 $s=3$ | 35 | 11 |

离群点越多（$w$ 越小）、模型越复杂（$s$ 越大），需要的迭代就越多。

**⑤ 常见误区**

- 以为 $T$ 越大结果越好、可以无限加（超过一定次数后只是浪费时间）。

**⑥ 对照最终版**

- "τ: too small rejects good points; too large accepts outliers. Choose it from the noise level." → 阈值的影响。
- "T: too small may miss a clean sample; too large only costs time. $T$ grows fast when there are more outliers." → 迭代次数的影响。
- "The results are random." → 随机性。

**最终版答案（背诵版 EN，≤5 行）：**
**τ**: too small rejects good points; too large accepts outliers. Choose it from the **noise level**.
**T**: too small may miss a clean sample; too large only costs time. $T$ grows fast when there are more outliers.
The results are **random**.

### 8.3 What is the difference between RANSAC and a typical bootstrap estimation procedure? RANSAC 与典型的 bootstrap 估计有什么区别？ ★

考过：[2023.3 Ex2 c](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** [第五课 · 一般而言，bootstrap 是什么？](../../Lectures/05_NLM_zh.md)；Bagging（2.3）。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

RANSAC 和常见的 bootstrap 估计有什么区别？两者都是随机重采样。

**② 需要的工具**

- **bootstrap**：有放回地抽 $N$ 个点，重复很多次，用来估计一个统计量的波动（标准误、置信区间），或用来做 Bagging（见 2.3）。
- **有放回 vs 不放回**：有放回时同一个点可能被抽到多次。
- **最小样本**（见 8.1）。

**③ 一步一步（逐项对比）**

1. **抽多少**：bootstrap 每次抽**和原数据一样多**（$N$ 个）；RANSAC 每次只抽**最小样本**（直线 2 个）。
2. **怎么抽**：bootstrap **有放回**；RANSAC 在一次抽样内**不放回**（2 个不同的点）。
3. **结果怎么用**：bootstrap 把所有结果合在一起，用来估计波动或取平均；RANSAC 按共识打分，**只保留最好的一个**。
4. **对离群点**：bootstrap 的每份样本里离群点的比例和原数据差不多，它**不会自动让一个不稳健的估计量变稳健**：对 OLS 做 bootstrap，每份样本的 OLS 照样被离群点污染。（稳健与否取决于被重采样的估计量本身：对中位数做 bootstrap，结果就继承了中位数的稳健性。）RANSAC 则专门寻找一个全是内点的小样本，从而排除离群点。
5. **目的**：bootstrap 是量化不确定性；RANSAC 是**稳健估计**和**离群点检测**。

**④ 小例子**

数据里有 20% 的离群点：每份 bootstrap 样本里大约也有 20% 离群点，算出的每条 OLS 直线都被拉歪，取平均仍然是歪的。RANSAC 只要抽到一次"两个点都是内点"（概率 $0.8^2=0.64$），就能找到正确的直线。

**⑤ 常见误区**

- 以为两者都是"重采样"，所以作用一样。

**⑥ 对照最终版**

- "Bootstrap: samples of size N with replacement, to estimate the variance of an estimator or to average models. Outliers stay inside, so it does not make a non-robust estimator (e.g. OLS) robust." → bootstrap 的做法和问题：稳健性取决于被重采样的估计量。
- "RANSAC: minimal samples (2 points), and it keeps the best consensus, not the average." → RANSAC 的做法。
- "Its goal is robustness and finding outliers." → 目的不同。

**最终版答案（背诵版 EN，≤5 行）：**
**Bootstrap**: samples of **size N with replacement**, to estimate the **variance** of an estimator or to **average** models. Outliers stay inside, so it does **not make a non-robust estimator** (e.g. OLS) robust.
**RANSAC**: **minimal samples** (2 points), and it keeps the **best consensus**, not the average.
Its goal is **robustness** and finding outliers.

### 8.4 How can the internal RANSAC models "grade" datapoints as outliers, and the datapoints "grade" each model? RANSAC 内部的模型如何给数据点"打分"（是否离群），数据点又如何给模型打分？ ★

考过：[2023.11 Ex4 c](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** 8.1 中的残差 $r_i$ 和共识集 $I$；把 $T$ 个候选模型看成一张"模型×点"的残差表。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

RANSAC 内部会产生很多候选直线。这些模型怎样给数据点"打分"（判断是否离群）？反过来，数据点又怎样给模型"打分"（判断模型好不好）？

**② 需要的工具**

- **残差表**：把 $T$ 个候选模型和 $N$ 个点排成一张表，第 $t$ 行第 $i$ 列是残差 $r_{it}$。
- **投票**：每个模型对每个点说"你是内点"或"你是离群点"。
- **截断损失** $\min(r^2,\tau^2)$：残差小时按平方算，超过 $\tau$ 后一律按 $\tau^2$ 算，这样离群点的影响有上限（MSAC 方法）。

**③ 一步一步**

1. 每一轮得到一个候选模型 $m_t$，算出所有点的残差 $r_{it}$。
2. **模型给点打分**：每个模型给每个点投一票，内点（$r_{it}\le\tau$）或离群点；也可以给软分数如 $r_{it}/\tau$。在**好模型**上汇总（例如只用共识大的模型，或按共识大小加权），得到每个点的离群分数：被多数好模型拒绝的点很可能是离群点。差的随机模型不应和好模型同等计票。
3. **点给模型打分**：模型的质量就是**内点个数** $|I_t|$，即每个点为"能解释它的模型"投一票；改进版用截断损失 $\sum_i\min(r_{it}^2,\tau^2)$，在内点数相同时偏好残差更小的模型。
4. 要说明残差用的是竖直距离还是几何（垂直）距离，二者对应不同的噪声假设。

**④ 小例子**

接 8.1 的 5 个点。模型 $y=x$ 有 4 个内点，模型"斜率 17"只有 2 个内点 → 点给模型打分，前者胜出。在 $y=x$ 这个好模型看来，点 (4,20) 是离群点；只要有足够多的好模型都拒绝它，它就被判为离群点。

**⑤ 常见误区**

- 让所有候选模型（包括明显很差的）平等投票。

**⑥ 对照最终版**

- "Models grade points: each model says inlier ($r\le\tau$) or outlier; a point rejected by most good models is an outlier." → 模型给点打分。
- "Points grade models: the score of a model is its number of inliers (or a truncated loss)." → 点给模型打分。

**最终版答案（背诵版 EN，≤5 行）：**
**Models grade points**: each model says inlier ($r\le\tau$) or outlier; a point rejected by most **good** models is an outlier.
**Points grade models**: the score of a model is its **number of inliers** (or a truncated loss $\sum_i\min(r_i^2,\tau^2)$).

### 8.5 Develop a generalized RANSAC to fit a circle C(c, r). 用广义 RANSAC 拟合圆 C(c, r)。 ★

考过：[2024 Ex4 b](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 8.1 的通用框架：最小样本大小 $s$、残差定义、重拟合，这三处要随模型改变。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

数据大致沿一个圆分布，怎样用"广义 RANSAC"拟合一个圆 $C(c,r)$？

**② 需要的工具**

- **RANSAC 框架**（见 8.1）：抽最小样本 → 得候选模型 → 算残差、数内点 → 保留最好的 → 用全部内点重拟合。
- **圆的方程** $(x-x_c)^2+(y-y_c)^2=r^2$，圆心 $c=(x_c,y_c)$，半径 $r$。
- **三点定圆**：不在一条直线上的 3 个点唯一确定一个圆。
- **径向距离** $\big|\|p_i-c\|-r\big|$：点到圆周的真实距离。

**③ 一步一步（框架不变，改三处）**

1. **最小样本改为 3 个点**（不共线）。圆心由两个线性方程解出：$2(p_j-p_1)^Tc=\|p_j\|^2-\|p_1\|^2$（$j=2,3$），半径 $r=\|p_1-c\|$。为什么是线性方程：把"$p_j$ 和 $p_1$ 到圆心距离相等"展开，平方项会消掉。三个点近乎共线、或半径不合理时，丢弃这个候选。
2. **残差改为径向距离** $e_i=\big|\|p_i-c\|-r\big|$，内点是 $e_i\le\tau$ 的点。不要把代数值 $(x-x_c)^2+(y-y_c)^2-r^2$ 直接当作距离。
3. **重拟合**：保留最大共识集后，在它的全部内点上最小化 $\sum_{i\in I}(\|p_i-c\|-r)^2$（几何拟合，需要迭代），可以用代数最小二乘的结果作初值。
4. 迭代次数 $T\ge\log(1-p)/\log(1-w^3)$，比直线多；$\tau$ 按噪声尺度选。

**④ 小例子（三点定圆）**

三个点 $p_1=(1,0)$、$p_2=(0,1)$、$p_3=(-1,0)$：

- $j=2$：$2\big((0,1)-(1,0)\big)\cdot c=1-1$，即 $-2x_c+2y_c=0$；
- $j=3$：$2\big((-1,0)-(1,0)\big)\cdot c=1-1$，即 $-4x_c=0$；
- 解得 $c=(0,0)$，$r=\|p_1-c\|=1$，就是单位圆。

**⑤ 常见误区**

- 仍然只抽 2 个点（2 个点确定不了一个圆）。
- 用代数残差代替几何距离来判断内点。

**⑥ 对照最终版**

- "Same algorithm, with three changes:" → 框架不变，改三处。
- "(1) sample 3 points (one circle passes through 3 non-collinear points);" → 最小样本 3 个点。
- "(2) residual = radial distance;" → 残差用径向距离。
- "(3) refit $(c,r)$ on the inliers by least squares. Use $T\ge\log(1-p)/\log(1-w^3)$." → 重拟合；迭代次数。

**最终版答案（背诵版 EN，≤5 行）：**
Same algorithm, with three changes:
(1) sample **3 points** (one circle passes through 3 non-collinear points);
(2) residual = **radial distance** $\big|\|p_i-c\|-r\big|$;
(3) refit $(c,r)$ on the inliers by least squares. Use $T\ge\log(1-p)/\log(1-w^3)$.

### 8.6 Robustly estimate δ = ‖μ − m‖ (mean vs medoid) with RANSAC when each instance has a quality indicator qᵢ. 每个样本带质量指标 qᵢ 时，用 RANSAC 稳健估计 δ = ‖μ − m‖（均值与 medoid 之差）。 ★

考过：[2023.3 Ex2 d](../DataML-CHPS-2022-examen_zh.md)（开放设计题）

**先懂这些：** ① 均值对离群点敏感，medoid 是真实样本中最"居中"的；② 8.1 的"候选—共识—重拟合"框架。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

每个样本都附带一个质量指标 $q_i\ge0$（越大越可靠）。设计一个 RANSAC 流程，稳健地估计 $\delta=\|\mu-m\|$，即均值中心 $\mu$ 和中心样本 medoid $m$ 之间的距离。这是开放设计题。

**② 需要的工具**

- **均值 $\mu$**：所有样本的平均，对离群点和偏斜很敏感。
- **medoid $m$**：到其他样本平均距离最小的那个**真实样本**，不容易被离群点拉走（见 7.8）。
- **$\delta$ 的意义**：数据对称、紧凑时，均值和 medoid 很接近，$\delta$ 小；$\delta$ 大说明数据**不对称、有多个峰，或者被离群点污染**。
- **RANSAC 框架**（见 8.1）。

**③ 一步一步**

1. **按质量抽样**：每轮按与 $q_i$ 成正比的概率抽少量样本（$q_i$ 全为 0 时退化为均匀抽样），算出一个候选中心 $c$。为什么：高质量的样本更值得信任，应该更常被选中。
2. **定共识**：只在原特征空间 $\mathbb R^d$ 里按距离判断内点，$I=\{i:\|x_i-c\|\le\tau\}$；用内点的**质量总和** $\sum_{i\in I}q_i$ 给候选打分，保留最好的集合 $I^*$。
3. **估计 $\delta$**：在 $I^*$ 上算均值 $\hat\mu$ 和 medoid $\hat m$，得到 $\hat\delta=\|\hat\mu-\hat m\|$。
4. 重复整个过程，可以得到 $\hat\delta$ 的分布，用来描述它的不确定性。
5. **关键**：$q_i$ 只用于抽样和打分，**不能当作第 $d+1$ 维坐标**参与距离计算，因为它和特征不是同一种量。
6. 这样刻画的是"可靠数据主体"的性质，前提是主体大致是单峰的。

**④ 小例子**

一维数据 $\{1,2,3,4,100\}$：均值是 22，medoid 是 3（到其他点的距离和最小），$\delta=19$，被离群点 100 严重拉大。去掉 100 后，均值 2.5，medoid 是 2 或 3，$\delta=0.5$。RANSAC 的共识集正是为了排除 100 这类点。

**⑤ 常见误区**

- 把 $q_i$ 当作一个坐标放进距离公式。
- 只给概念不给流程（开放题要写出具体步骤）。

**⑥ 对照最终版**

- "$\delta$ compares the mean (sensitive to outliers) with the medoid (the most central real point); a large $\delta$ means skew or outliers." → $\delta$ 的含义。
- "RANSAC: sample points with probability $\propto q_i$, compute a candidate center, inliers = points within τ, score = $\sum_{i\in I}q_i$." → 流程。
- "On the best inlier set compute $\hat\mu$, $\hat m$ and $\hat\delta$. Do not use $q_i$ as a coordinate." → 估计；注意事项。

**最终版答案（背诵版 EN，≤5 行）：**
$\delta$ compares the **mean** (sensitive to outliers) with the **medoid** (the most central real point); a large $\delta$ means skew or outliers.
RANSAC: sample points with probability $\propto q_i$, compute a candidate center, inliers = points within τ, score = $\sum_{i\in I}q_i$.
On the best inlier set compute $\hat\mu$, $\hat m$ and $\hat\delta=\|\hat\mu-\hat m\|$. Do not use $q_i$ as a coordinate.

---

## 9. 学习问题的基本概念与实际应用

### 9.1 What are the links between machine learning and numerical simulation / HPC? Give two examples. 机器学习与数值模拟（高性能计算）有哪些联系？举两个例子。 ★★★

考过：[2019 Q10](../Exam_2019_zh.md)（calcul intensif）· [2021 Ex1 Q8](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex1 Q1](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** ① 数据科学的三大支柱与机器学习的目标——[第一课 · 数据、任务与学习函数](../../Lectures/01_intro/01_data_and_learning.md)；② PCA 降维——[第四课 · PCA 及其变体](../../Lectures/04_UL_zh.md)、[Lab5](../../Exercises/Lab5/Lab5_zh.ipynb)；③ 这是 CHPS 专业的"本专业题"，几乎必考。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

机器学习和数值模拟（以及高性能计算 HPC）有什么联系？举两个例子。这是 CHPS 专业几乎必考的一题。

**② 需要的工具**

- **数值模拟**：用计算机求解物理方程来预测现象，例如流体力学（CFD）、有限元结构分析。精确但很贵，跑一次可能要几小时到几天。
- **代理模型（surrogate model）**：一个快速的机器学习模型，学会"输入参数 → 模拟结果"的对应关系，用来代替昂贵的模拟器。
- **降阶模型（ROM）与 PCA／POD**：PCA 找出数据变化最大的少数几个方向（"模态"），只用这几个方向的坐标就能近似表示整个数据。在流体力学里，同样的方法叫 POD。
- **不确定性量化（UQ）**：输入参数不确定时，评估输出会在什么范围内变化，需要成千上万次模拟。

**③ 一步一步**

**代理模型**：

1. 挑选一批参数组合。
2. 对每组参数跑真实模拟，得到输出。
3. 用这些（参数，输出）对训练回归模型或神经网络。
4. 在**没参与训练**的参数点上检验精度。为什么：确认代理在适用范围内可靠。
5. 之后做优化或不确定性量化时，用代理代替模拟器，每次几乎瞬间出结果。

**降阶模型（ROM）**：

1. 收集模拟场的"快照"（每一时刻整个网格上的数值）。
2. 用 PCA／POD 求出少数几个主模态。
3. 每个快照只用这几个模态的系数表示，在低维空间里学习或求解它的演化。

**④ 小例子（示意数字）**

- 一次 CFD 模拟要 10 小时，优化需要评估 1 万次，直接算要 10 万小时。先跑 200 次（2000 小时）训练代理模型，之后每次评估只要毫秒级。
- 一个快照有 100 万个网格值，如果用 20 个模态就能表示大部分信息，每个快照只需要存 20 个数。

**⑤ 常见误区**

- 代理模型只在训练参数范围内可靠，超出范围不能信。
- 要把造数据（跑模拟）的成本算进总收益。
- 其他联系也可以提：求解器参数自动调优、超算节点的异常检测与故障预测、把物理方程作为约束融入训练（物理引导学习，如 PINN）；反过来，HPC 也让大规模深度学习训练成为可能。

**⑥ 对照最终版**

- "(1) Surrogate models: … predict the output for new parameters without running the solver. Useful for optimization and uncertainty studies." → 例子一：代理模型。
- "(2) Reduced-order models: use PCA / POD or autoencoders to compress huge simulated fields into a few modes …" → 例子二：降阶模型。
- "Also: tuning solvers, detecting anomalies on HPC nodes." → 其他联系。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **Surrogate models**: run some expensive simulations (CFD, finite elements), then train a fast model (regression, neural network) to predict the output for **new parameters** without running the solver. Useful for optimization and uncertainty studies.
(2) **Reduced-order models**: use **PCA / POD** or autoencoders to compress huge simulated fields into a few modes, then learn or solve in this small space.
Also: tuning solvers, detecting anomalies on HPC nodes.

### 9.2 What is the difference between classification data and a classification problem? 分类数据与分类问题有什么区别？ ★★

考过：[2021 Ex1 Q1](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex1 Q2](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** [第三课 · 分类数据：例子；这些数据可以支持哪些决策？](../../Lectures/03_LMC_zh.md)——同一份数据可以对应分类、评分两种问题；与 5.2 一起复习。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

"分类数据"和"分类问题"有什么区别？听起来像一回事，题目考的正是你能不能把二者分开。

**② 需要的工具**

- **数据的形式**：数据长什么样，比如标签 $y$ 是类别还是数字（见 9.4）。
- **学习任务（问题）**：我们想用数据做成什么事，比如输出类别、给出排序、估计概率。
- **评分／排序问题**：输出连续分数 $s(x)$，按风险高低排序，用 ROC／AUC 评价（见 3.5、3.6）。
- **概率估计问题**：输出 $P(Y=1\mid x)$，之后再根据代价做决策。

**③ 一步一步**

1. **分类数据**说的是数据的形式：样本对 $(x_i,y_i)$，其中 $y_i$ 是离散类别（如 0／1）。
2. **分类问题**说的是任务：学一个规则 $h:\mathcal X\to\{0,1\}$，给新样本分配类别，使误分类风险尽量小。
3. 关键点：**同一份分类数据可以用来解决不同的问题**：
   - 分类问题：直接给出类别；
   - 评分／排序问题：给出连续分数，用于排序（信用风险排序、精准营销）；
   - 概率估计问题：给出后验概率，再按代价决策。
4. 所以"数据是什么类型"不等于"要解决什么任务"，评价准则也随任务而变（见 3.7）。

**④ 小例子**

同一份"客户是否违约"的历史数据（标签 0／1）：

- 分类问题：新客户批不批贷款？输出"批／不批"，看错误率。
- 评分问题：额度有限，先给哪 100 个客户放贷？按违约风险排序，看 AUC。
- 概率估计：给每个客户定利率，需要违约概率本身，看概率校准得好不好。

**⑤ 常见误区**

- 认为有了分类数据就只能做分类。

**⑥ 对照最终版**

- "Classification data describes the data: pairs $(x_i,y_i)$ where $y_i$ is a category." → 分类数据指数据的形式。
- "A classification problem describes the task: learn a rule $h$ … with a small error rate." → 分类问题指任务。
- "The same data can also be used for other problems: scoring / ranking … or probability estimation." → 同一份数据可以服务于其他问题。

**最终版答案（背诵版 EN，≤5 行）：**
**Classification data** describes the **data**: pairs $(x_i,y_i)$ where $y_i$ is a **category** (e.g. 0/1).
A **classification problem** describes the **task**: learn a rule $h:\mathcal X\to\{0,1\}$ that gives a class to new points, with a small error rate.
The same data can also be used for **other problems**: **scoring / ranking** ($s(x)$, evaluated by ROC/AUC) or **probability estimation** $P(Y=1\mid x)$.

### 9.3 What is the difference between supervised and unsupervised learning? Give two examples of each. 监督学习与无监督学习有什么区别？各举两个例子。 ★

考过：[2019 Q1](../Exam_2019_zh.md)

**先懂这些：** [第一课 · 数据、任务与学习函数（Types of Machine Learning problems）](../../Lectures/01_intro/01_data_and_learning.md)；[第四课 · 无监督学习与降维](../../Lectures/04_UL_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

监督学习和无监督学习有什么区别？各举两个例子。

**② 需要的工具**

- **标签 $y$**：我们想预测的"正确答案"（见 1.1）。
- **分类／回归**：$y$ 是类别还是数字（见 9.4）。
- **聚类、降维**：两种最常见的无监督任务（见 7.1；PCA 在课件第四课）。

**③ 一步一步**

1. **监督学习**：每个训练样本 $x_i$ 都带有已知的标签 $y_i$，目标是学会从 $x$ 预测 $y$。好比有老师批改答案。
   - 例子：垃圾邮件识别（分类）、电力消耗预测（回归）、医学诊断。
2. **无监督学习**：**没有标签**，目标是发现数据本身的**结构**。好比没有答案，只能自己找规律。
   - 例子：客户分群（聚类）、用 PCA 降维、异常检测、推荐系统中的矩阵补全。
3. **评价方式不同**：监督学习可以直接用预测误差评价；无监督学习没有"标准答案"，评价更难（见 1.5、7.4）。

**④ 小例子**

同一批客户数据：如果有"是否流失"这一列，预测新客户会不会流失就是监督学习；如果没有任何标签，只是想把客户自动分成几类，就是无监督学习（聚类）。

**⑤ 常见误区**

- 例子给错类别，比如把聚类当成分类。

**⑥ 对照最终版**

- "Supervised: each training point $x_i$ has a known label $y_i$; we learn to predict $y$ from $x$. Examples: spam detection, predicting energy consumption." → 监督学习及例子。
- "Unsupervised: no labels; we look for structure in the $x_i$. Examples: customer segmentation, dimension reduction with PCA." → 无监督学习及例子。
- "Supervised learning is evaluated by prediction error; unsupervised learning is harder to evaluate." → 评价上的区别。

**最终版答案（背诵版 EN，≤5 行）：**
**Supervised**: each training point $x_i$ has a known **label $y_i$**; we learn to predict $y$ from $x$. Examples: **spam detection** (classification), **predicting energy consumption** (regression).
**Unsupervised**: **no labels**; we look for **structure** in the $x_i$. Examples: **customer segmentation** (clustering), **dimension reduction** with PCA.
Supervised learning is evaluated by prediction error; unsupervised learning is harder to evaluate.

### 9.4 What is the difference between classification data and regression data? 分类型数据与回归型数据有什么区别？ ★

考过：[2019 Q2](../Exam_2019_zh.md)

**先懂这些：** [第一课 · 数据、任务与学习函数](../../Lectures/01_intro/01_data_and_learning.md)；[第三课 · 分类数据：例子](../../Lectures/03_LMC_zh.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

分类型数据和回归型数据有什么区别？

**② 需要的工具**

- **目标变量 $Y$**：要预测的那一列。
- **定性（离散）**：取有限个类别，如"是／否"、病的种类。
- **定量（连续）**：取实数值，如价格、温度。
- **损失与评价指标**：0–1 损失、对数损失、准确率、AUC（分类）；平方损失、RMSE、MAE（回归）。

**③ 一步一步**

1. 区别在于**目标变量 $Y$ 的类型**。
2. **分类数据**：$Y$ 是定性的，取有限个类别，如 $\{0,1\}$ 或故障类型。
3. **回归数据**：$Y$ 是定量的，取实数，如房价、温度。
4. 两种情况下，输入 $X$ 都可以是数值型或类别型，所以区别**不在输入**。
5. 由此带来的不同：损失函数（0–1／对数损失 vs 平方损失）、评价指标（准确率、AUC vs RMSE、MAE）、模型输出（类别或概率 vs 实数）。

**④ 小例子**

同样是房屋数据：预测"三个月内能不能卖掉"（是／否）是分类；预测"能卖多少钱"是回归。

**⑤ 常见误区**

- 以为看输入就能判断是分类还是回归。

**⑥ 对照最终版**

- "The difference is the type of the target $Y$." → 区别在目标变量。
- "Classification: $Y$ is qualitative / discrete … Regression: $Y$ is quantitative / continuous …" → 两种类型。
- "The inputs $X$ can be numerical or categorical in both cases. The losses differ: 0–1 / logistic vs squared error." → 输入不决定类型；损失不同。

**最终版答案（背诵版 EN，≤5 行）：**
The difference is the **type of the target $Y$**.
**Classification**: $Y$ is **qualitative / discrete**, a finite set of classes (e.g. $\{0,1\}$, disease type).
**Regression**: $Y$ is **quantitative / continuous**, $Y\in\mathbb R$ (e.g. price, temperature).
The inputs $X$ can be numerical or categorical in both cases. The losses differ: 0–1 / logistic vs squared error.

### 9.5 Give two concrete implementation issues in real applications (supervised anomaly detection on an instrumented production line). 实际应用中的两个具体实施问题（以生产线上的监督式异常检测为例）。 ★

考过：[2023.3 Ex1 Q10](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** ① 真实世界中的完整数据处理流程——[第一课 · 算法家族、正则化与处理流程](../../Lectures/01_intro/02_algorithms_and_pipeline.md)；② 类别不平衡下的评价指标（3.7）；③ [Lab3](../../Exercises/Lab3/Lab3_zh.ipynb) 异常检测部分。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

以"在装满传感器的生产线上做监督式异常检测"为例，说出实际部署中的两个具体问题。

**② 需要的工具**

- **类别不平衡**：真正的故障极少，正常数据极多（见 3.7）。
- **信息泄漏**：评估时用到了"未来"或测试数据的信息，导致成绩虚高。
- **概念漂移**：数据背后的规律随时间改变，比如设备老化。
- **代价不对称**：误报（无谓停机）和漏报（放过真故障）的损失不同。

**③ 一步一步（两个问题）**

1. **问题一：数据质量与标签获取**
   - 多个传感器的采样频率、量纲不同，时钟可能不同步，还有信号漂移和缺失值；
   - 真实故障极少（严重**类别不平衡**），人工标注成本高；
   - 要区分"传感器自己坏了"和"生产线真的出了问题"。
2. **问题二：评估、误报代价与工况漂移**
   - 必须按时间段或生产批次划分训练／测试数据，防止信息泄漏；
   - 漏检和误报的代价不对称，要按代价设定阈值，用召回率、精确率而不是准确率评价；
   - 负载等运行工况会影响"正常"的样子（满负荷时振动大是正常的）；
   - 设备老化或工艺变化会造成**概念漂移**，上线后要持续监控、定期重训。

**④ 小例子**

100 万条传感器记录里只有 50 条故障：一个"永远报正常"的模型准确率高达 99.995%，却一次故障都抓不到。所以要看召回率，并通过重采样、代价加权等方法处理不平衡。

**⑤ 常见误区**

- 只说"数据量大""模型要准"这类泛泛的话，没有结合传感器、生产线的具体场景。

**⑥ 对照最终版**

- "(1) Data quality and labels: … real defects are rare (strong class imbalance) and labels are expensive; a sensor failure must be distinguished from a real anomaly." → 问题一。
- "(2) Realistic evaluation and drift: split by time to avoid leakage; false alarms and missed defects have different costs …; concept drift, so monitor and retrain." → 问题二。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **Data quality and labels**: sensors have different rates, scales, drifts and missing values; real defects are **rare** (strong **class imbalance**) and labels are expensive; a sensor failure must be distinguished from a real anomaly.
(2) **Realistic evaluation and drift**: split by **time** to avoid leakage; false alarms (stopping the line) and missed defects have **different costs**, so choose the threshold accordingly; the machines change over time (**concept drift**), so monitor and retrain.

### 9.6 Describe a data science pipeline to deploy a predictive model (e.g. energy consumption peaks). 描述部署预测模型的数据科学流程（如能耗峰值预测）。 ★

考过：[2020 B1–B3](../Exam_2020_zh.md)（智慧城市案例）

**先懂这些：** [第一课 · Machine Learning in the real world: A full pipeline for data processing](../../Lectures/01_intro/02_algorithms_and_pipeline.md)；[作业一第 4 题：数据划分](../../Exercises/Assignment1/guide/04_data_splitting.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

描述部署一个预测模型的完整数据科学流程（2020 年的案例：预测 40 个场所的能耗峰值）。

**② 需要的工具**

- **数据关联（join）**：把两张表按共同的键（如场所 ID）合在一起。
- **特征工程**：从原始数据中构造对预测有用的输入，如小时、星期几、过去一小时的平均能耗。
- **标准化**：让不同场所的数值可比（化工厂和酒店的能耗差上百倍）。
- **按时间划分**（见 9.7）。
- **数据漂移**：上线后数据的分布慢慢改变。

**③ 一步一步**

1. **收集与关联**：按场所 ID 关联场所表和测量表；解析日期，把逗号小数（如 "-2,5"）转成数字。
2. **清洗与特征工程**：处理缺失值和传感器异常（如突然掉到接近 0）；**按场所标准化**；构造日历特征（小时、星期、节假日）、历史滞后特征和温度特征（取暖和制冷带来的 U 形关系）。
3. **定义目标**：例如"$t+h$ 时刻的能耗超过该场所 95% 分位数"记为峰值（分类），或直接预测能耗（回归）。
4. **训练与调参**：先用逻辑回归做基线，再试随机森林、梯度提升、SVM 等；**按时间顺序**划分训练／验证／测试。
5. **部署、监控、重训**：上线后监控数据漂移，定期重新训练。

**④ 小例子**

化工厂每 10 分钟约耗 4000 单位，酒店约 40 单位。如果不按场所标准化，一个统一的模型几乎只会学化工厂的规律；按场所标准化后，"高于自身平时水平"才是真正有意义的峰值信号。

**⑤ 常见误区**

- 流程里漏掉"定义目标"这一步（"峰值"必须先有可操作的定义）。
- 随机打乱划分时间序列数据。

**⑥ 对照最终版**

- "(1) Collect and join the data (sites + measures), parse dates and numbers." → 收集与关联。
- "(2) Clean and build features: missing values, sensor errors, normalization per site, calendar features, lagged consumption, temperature." → 清洗与特征工程。
- "(3) Define the target: e.g. "peak" = consumption above the site's 95% quantile at $t+h$ (classification) or the consumption itself (regression)." → 定义目标。
- "(4) Train and tune models … with a time-ordered split. (5) Deploy, monitor drift, retrain." → 训练、部署、监控。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **Collect and join** the data (sites + measures), parse dates and numbers.
(2) **Clean and build features**: missing values, sensor errors, normalization per site, calendar features (hour, day), lagged consumption, temperature.
(3) **Define the target**: e.g. "peak" = consumption above the site's 95% quantile at $t+h$ (classification) or the consumption itself (regression).
(4) **Train and tune** models (logistic regression, random forest, boosting) with a **time-ordered** split. (5) **Deploy, monitor drift, retrain**.

### 9.7 Which points need attention because of the time dimension in the data? 由于数据带有时间维度，需要注意哪些问题？ ★

考过：[2020 B4–B5](../Exam_2020_zh.md)

**先懂这些：** 随机打乱划分为什么会泄漏未来信息——[作业一第 4 题：数据划分](../../Exercises/Assignment1/guide/04_data_splitting.md)。

**解析版（小白也能看懂）：**

**① 这道题在问什么**

数据带有时间维度（每 10 分钟一条），建预测模型时要特别注意哪些问题？（对应 2020 年的 B4 评估方案和 B5 注意事项。）

**② 需要的工具**

- **信息泄漏**：训练或特征里用到了预测时刻之后才知道的信息。
- **滚动／扩展窗口验证**：始终用过去的数据训练、用紧随其后的数据验证，窗口沿时间向前移动。
- **季节性**：按固定周期重复的模式（每天、每周、每年）。
- **自相关**：相邻时刻的值高度相关，样本不是独立的。
- **非平稳与概念漂移**：数据规律随时间改变。
- **朴素基线**：最简单的预测方法，比如"预测值＝昨天同一时刻的值"，用来检验模型有没有真正的价值。

**③ 一步一步**

1. **防止未来信息泄漏**：
   - 不能随机打乱划分，要**按时间**划分（滚动或扩展窗口）；
   - 滑动平均、标准化参数、峰值阈值都只能用过去的数据计算；
   - 实际部署时，未来的温度只能用天气预报值，不能用事后测到的值。
2. **多重季节性**：日周期（早晚高峰）、周周期（工作日／周末）、年周期（冬夏），还有节假日和夏令时切换。
3. **自相关**：相隔 10 分钟的样本几乎一样，不是独立同分布，随机交叉验证会给出虚高的分数。
4. **非平稳与概念漂移**：设备、业务的变化会改变用能规律，需要持续监控、定期重训。
5. **数据缺口**：各场所的采集时段不同，还有缺测。
6. **评价指标**：峰值是少数类，用精确率、召回率、$F_1$、PR-AUC；预测能耗本身时用 RMSE／MAE；一定要和朴素基线比较，并分场所报告结果。

**④ 小例子**

如果随机打乱，训练集里有 10:00 和 10:20 的数据，测试集里有 10:10 的数据。模型几乎可以"抄"相邻时刻的值，测试成绩会非常好，上线后却远远达不到。按时间划分（用 1–10 月训练、11 月测试）才接近真实情况。

**⑤ 常见误区**

- 把时间序列当作普通的独立样本随机划分。
- 不和朴素基线比较，看不出模型是否真的有用。

**⑥ 对照最终版**

- "(1) No leakage from the future: split by time …; in production, future temperature is a forecast." → 防止泄漏。
- "(2) Seasonality: daily, weekly and yearly cycles, holidays." → 季节性。
- "(3) Autocorrelation: points 10 minutes apart are not independent, so random CV is too optimistic." → 自相关。
- "(4) Drift: monitor and retrain. Evaluate with precision / recall / F1 for the rare peaks (RMSE for consumption), against a naive baseline." → 漂移；评价方式。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **No leakage from the future**: split by time (rolling / expanding window), and compute features, scaling and thresholds on the past only; in production, future temperature is a forecast.
(2) **Seasonality**: daily, weekly and yearly cycles, holidays.
(3) **Autocorrelation**: points 10 minutes apart are not independent, so random CV is too optimistic.
(4) **Drift**: monitor and retrain. **Evaluate** with precision / recall / F1 for the rare peaks (RMSE for consumption), against a naive baseline (same hour yesterday).

