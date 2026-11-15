# 高频概念题合集（按主题）

[← 清单首页](README.md) · [计算题](00_calculations.md)

共 74 题，分 9 个主题；每个主题内按出现次数（★）从多到少排列，★ 相同时按题号。★ = 考过这道题的试卷份数。文中"见 7.4"之类的引用按题号查找。

每道题先给**最终版答案**（英文，≤5 行，考场上直接写的版本），紧接着是**解析版**（从零讲起：这道题在问什么 → 用到的工具是干什么的 → 一步一步推 → 小例子 → 常见误区 → 最终版每句话的意思）。第一次学某道题时先读下面的解析版，读懂后再回到上面背最终版答案；复习时只看最终版答案即可。基础概念在文件里第一次出现时讲得最详细，后面的题会写"见 x.y"。

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

**最终版答案（背诵版 EN，≤5 行）：**
Expected squared error = **bias²** + **variance** + **Bayes error** (noise); for linear least squares the variance is $\sigma^2 d/n$.
A too **simple** model has high bias: it **underfits**.
A too **complex** model has high variance: it learns the noise and **overfits**.
We choose the complexity (degree, depth, $\lambda$) by **cross-validation**, then test once on a test set.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

为什么模型不能一味追求“越复杂越好”，也不能太简单？“偏差—方差权衡（bias–variance trade-off）”就是解释**模型复杂度、预测误差与稳定性之间拉锯战**的核心理论。作为全文第一题，下面先把后面各题都会用到的核心概念用大白话讲透。

**② 需要的工具**

- **数据 $(x,y)$**：$x$ 是用来预测的已知信息（叫**特征**，例如房子面积），$y$ 是想猜的答案（叫**标签**，例如房价）。训练集就是手头拿到的 $n$ 对已知样本 $(x_i,y_i)$。
- **模型（预测函数）$h$**：给它一个 $x$，它输出猜的答案 $\hat y=h(x)$。“训练”就是根据手头的训练数据，挑出一个好函数 $\hat h$。
- **假设空间 $\mathcal H$**：允许算法去挑的“候选模型菜单”，比如“所有直线”或“所有 9 次多项式”。菜单 $\mathcal H$ 越大，模型就越灵活、越**复杂**。
- **损失函数 $\ell$**：给预测错多少“打分罚款”。回归题最常用**平方损失** $(y-\hat y)^2$：猜错 1 块钱罚 1，猜错 3 块钱罚 9（错得离谱时罚得特别重）。
- **训练误差 vs 测试误差**：训练误差是在做过的“练习题”上的平均罚款；测试误差是在**从未见过的新题**上的平均罚款。考试和实际应用中，我们真正关心的是后者（详见 1.3）。
- **欠拟合 vs 过拟合**：
  - **欠拟合（underfitting）**：模型太简单（菜单里只有直线，但真实规律是弯的），连手头的训练数据都拟合不好；
  - **过拟合（overfitting）**：模型太复杂（菜单里有弯弯曲曲的高次曲线），把训练数据里偶然的**随机噪声**当成规律硬背下来，结果换一批新数据就错得一塌糊涂。
- **噪声（Bayes 误差）$\sigma^2$**：数据里自带的不可预测的随机波动（比如测量误差、同一个面积的房子因为朝向楼层不同产生的随机差价）。**这是任何完美模型都消除不了的误差下限**，课件里叫 **Bayes error**。
- **偏差（bias）与方差（variance）**：现实里我们只有一份训练集，抽到哪几条数据带有运气成分。想象一个思想实验——如果能**换很多份不同的训练集，每次重新训练出一个模型 $\hat h$**：
  - **偏差**＝所有这些模型预测结果的**平均值**，离真实规律有多远（衡量模型是不是**系统性地看偏了**）；
  - **方差**＝换一份训练集时，学出来的模型预测结果**左右摇摆有多厉害**（衡量模型对数据偶然波动有多**敏感、不稳定**）。
- **射箭类比**：把靶心想成真实答案，每次换训练集训练出的模型相当于射出一箭。**高偏差**＝箭整体射偏到靶心左上角，哪怕很集中也打不中靶心；**高方差**＝箭东一枪西一枪撒得到处都是；好模型要既瞄得准（低偏差）、手又稳（低方差）。
- **交叉验证（cross-validation）与正则化 $\lambda$**：交叉验证把训练集拆成几份轮流做“模拟考”，用来挑复杂度（详见 3.1）；正则化系数 $\lambda$ 则是限制模型别太复杂的“紧箍咒”（详见 1.4）。

**③ 一步一步（推导看懂意思即可，不用死记）**

假设世界上的真实规律是 $Y = f^*(X) + \varepsilon$，其中 $f^*(X)$ 是真实规律（即理论上最好的 **Bayes 模型**），$\varepsilon$ 是随机噪声，平均值为 0、方差为 $\sigma^2$。

1. 拿某一份训练集训练出模型 $\hat h$。因为训练集是随机抽的，所以 $\hat h(x)$ 也会随训练集变化；把无数次重抽训练集得到的预测取平均，记为平均预测 $\bar h(x) = \mathbb E[\hat h(x)]$。
2. 把单次预测的总失误 $Y - \hat h(x)$ 拆成三段：
   $$Y - \hat h(x) = \underbrace{(Y - f^*(x))}_{\text{纯噪声}} + \underbrace{(f^*(x) - \bar h(x))}_{\text{平均预测与真实规律的差距}} + \underbrace{(\bar h(x) - \hat h(x))}_{\text{单次结果相对平均的晃动}}$$
   *为什么这么拆*：正好把误差分成“天注定的噪声”、“模型平均看偏了多少”和“模型因为换数据晃了多少”三块互不重叠的部分。
3. 两边平方再取期望（平均），由于噪声均值为 0 且与训练集无关，交叉乘积项全部抵消为 0，最终得到经典的三项分解公式：
   $$\mathbb E[(Y-\hat h)^2] = \underbrace{(f^*-\bar h)^2}_{\text{偏差}^2\ (\text{bias}^2)} + \underbrace{\mathbb E[(\hat h-\bar h)^2]}_{\text{方差}\ (\text{variance})} + \underbrace{\sigma^2}_{\text{噪声 / Bayes 误差}}$$
4. **特别记住线性最小二乘的方差公式 $\sigma^2 d / n$**：如果用 $d$ 个特征做线性回归，每多一个特征维度，就相当于多一个要靠数据猜的权重旋钮。数据量 $n$ 不变时特征 $d$ 越多，每个旋钮分到的样本信息越少、猜得越抖，方差就按 $\sigma^2 d / n$ 线性变大；样本量 $n$ 越大，方差就越小。
5. **为什么必须权衡（U 形曲线）**：当模型从简单变复杂时，它越来越跟得上复杂规律，**偏差下降**；但它同时开始迁就训练集里的随机噪声，**方差上升**。一降一升加起来，测试误差随复杂度先降后升，呈一个 **U 形**——谷底就是最佳复杂度。
6. **实际怎么选谷底**：选几个候选复杂度（比如多项式次数、树的深度、正则化 $\lambda$），用**交叉验证**比较模拟考分数，选分数最低的那个；**独立测试集只用来做最后一次期末打分**。*为什么测试集只能用一次*：一旦你看着测试集分数去反复调参数，测试集就变成了变相的练习题，最后报出的成绩会虚高。

**④ 小例子（动手实验直观感受）**

真实规律是一条正弦波 $y=\sin(2\pi x)$ 加上标准差 $\sigma=0.3$ 的随机噪声（此时噪声方差 $\sigma^2=0.09$ 就是任何模型都打不破的理论下限）。每次只抽 $n=10$ 个点当训练集，分别用 1 次（直线）、3 次、6 次多项式去拟合，重复“抽样→训练→测试”200 次，看中位数误差：

| 多项式次数（复杂度） | 训练误差 | 测试误差 | 到底发生了什么 |
|---|---|---|---|
| 1（太简单，直线） | 0.223 | 0.333 | **高偏差、低方差（欠拟合）**：怎么抽样都只能画直线，弯不过来 |
| 3（刚刚好） | 0.052 | 0.158 | **平衡点**：跟上了波形，测试误差接近噪声下限 0.09 |
| 6（太复杂，6 次曲线） | 0.022 | 3.685 | **低偏差、超高方差（过拟合）**：几乎贴死这 10 个点，换新点时曲线剧烈乱飞 |

看表就能明白：**训练误差一路降到底，但测试误差走出了一条 U 形曲线**。

**⑤ 常见误区**

- **误区 1：“训练误差越低，模型就越好”**。错！6 次多项式训练误差只有 0.022，但测试误差炸到 3.685。
- **误区 2：以为只有平方损失有“越复杂越过拟合”的规律**。上面严谨的三项相加等式确实只对**平方损失**成立，但“太简单欠拟合、太复杂过拟合、测试误差呈 U 形”这个权衡思想对分类问题（比如 0–1 损失）同样成立（用 1.2 的“近似误差＋估计误差”分解就能解释所有损失函数）。
- **误区 3：把“偏差—方差”和“近似误差—估计误差”完全画等号**。两者很像但定义层级不同（详见 1.2）。
- **误区 4：反复看测试集分数来调参**。这是数据泄露，会让评估失真。

**⑥ 对照最终版**

- "Expected squared error = bias² + variance + Bayes error (noise); for linear least squares the variance is $\sigma^2 d/n$." → 总期望平方误差＝偏差平方＋方差＋Bayes 误差（不可消噪声）；线性最小二乘的方差项精确等于 $\sigma^2 d/n$。
- "A too simple model has high bias: it underfits." → 太简单的模型偏差高，造成欠拟合。
- "A too complex model has high variance: it learns the noise and overfits." → 太复杂的模型方差高，会把噪声背下来导致过拟合。
- "We choose the complexity (degree, depth, $\lambda$) by cross-validation, then test once on a test set." → 复杂度旋钮（次数、树深、$\lambda$）靠交叉验证来选，测试集只做最后一次验证。

### 1.2 What are the approximation and estimation errors, and how is the trade-off between them solved? 近似误差和估计误差是什么？二者的权衡如何处理？ ★★

考过：[2021 Ex1 Q6](../DataML-CHPS-2021-examen_zh.md)（原问法：哪些误差项能解释过拟合）· [2024 Ex1 Q2](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 三个"最优"的区别：Bayes 最优 $f^*$、类内最优 $f^*_{\mathcal H}$、学到的 $\hat f$——[第一课 · Bayes 最优与学习界](../../Lectures/01_intro/07_bayes_and_learning_bounds.md)；② 真实风险 $R$ 与经验风险 $\hat R_n$——[第一课 · 经验风险与真实风险](../../Lectures/01_intro/06_empirical_and_true_risk.md)；③ 第三项优化误差——[第六课 · 机器学习中的新权衡：三个项](../../Lectures/06_DL_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
$L(\hat h)-L(h^*)=\underbrace{L(\hat h)-L(\bar h)}_{\textbf{estimation (stochastic)}}+\underbrace{L(\bar h)-L(h^*)}_{\textbf{approximation (deterministic)}}$, with $\bar h$ the best function in $\mathcal H$.
**Approximation error**: the class $\mathcal H$ is too poor (like bias). **Estimation error**: $\hat h$ is learned from finite data (like variance).
A bigger $\mathcal H$ does not increase the approximation error, but the estimation error **tends to increase**.
Learning = choose $\mathcal H$ (design), then estimate the best function in it (training); balance by **regularization / model selection by CV**, and more data.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

模型的真实总误差可以拆成“近似误差”和“估计误差”两块。题目问：它们各代表什么原因造成的误差？为什么会此消彼长？实际中怎么平衡？（2021 年原卷问的是“哪些误差项能解释过拟合”。）

**② 需要的工具**

为了和课件及上面的**最终版答案**保持同一套符号（部分参考书把 $L$ 写作 $R$、把 $\bar h$ 写作 $f^*_{\mathcal H}$、把 $h^*$ 写作 $f^*$，意思完全一样），先认识三个“理想／现实模型”：

- **$h^*$（Bayes 最优模型）**：上帝视角下理论最优的预测函数，只有知道真实世界全部概率分布时才能达到。
- **$\bar h$（菜单 $\mathcal H$ 里的最佳模型）**：在我们人为选定的候选范围 $\mathcal H$（例如“所有直线”）里，客观上表现最好的那个函数——就算给你无限多数据，最多也就只能找到它。
- **$\hat h$（实际学出来的模型）**：用手里有限的 $n$ 个训练样本真正训练出来的函数。
- **真实风险 $L(h)$**：模型 $h$ 在未来所有新数据上的平均损失（即泛化误差，见 1.3）。
- **超额风险 $L(\hat h) - L(h^*)$**：我们学出的模型，比理论天花板 $h^*$ 多出来多少误差（注：$\hat h$ 不可能比理论最优更好，所以这个差 $\ge 0$）。

**画画类比**：要临摹一条曲线。如果规定你只能用直尺（$\mathcal H$ 太小），手艺再好也画不弯，这就是**近似误差**；如果给你几百种曲线模板，却只给你看 5 个带噪点的模糊点（样本太少），你很容易照着噪点画歪，这就是**估计误差**。

**③ 一步一步**

1. **在中间插进一个 $\bar h$，把超额风险一分为二**：
   $$L(\hat h) - L(h^*) = \underbrace{\big(L(\hat h) - L(\bar h)\big)}_{\text{估计误差（随机）}} + \underbrace{\big(L(\bar h) - L(h^*)\big)}_{\text{近似误差（确定）}}$$
   *为什么这么插*：刚好把误差切给两个责任人——“工具菜单没选好”和“训练样本不够多”。
2. **近似误差 $L(\bar h) - L(h^*)$（类似偏差）**：反映假设空间 $\mathcal H$ 的表达能力够不够。只要 $\mathcal H$ 选定、样本再多也改不了这一项，所以它是**确定的（deterministic）**。
3. **估计误差 $L(\hat h) - L(\bar h)$（类似方差）**：反映数据量有限带来的不稳定性。因为换一批样本训练，学出的 $\hat h$ 就会变，所以它是**随机的（stochastic）**。**过拟合的本质**正是这一项太大——$\mathcal H$ 太大而样本太少，$\hat h$ 迁就了训练集里的随机噪声。
4. **为什么此消彼长（权衡）**：当候选菜单 $\mathcal H$ 一层层扩大（比如从直线扩大到 3 次、9 次多项式）：
   - 原来的好函数还在新菜单里，所以最佳表现只会更好或不变 → 近似误差**不增**（通常变小）；
   - 但在样本数 $n$ 固定时，可选函数变多，模型更容易被样本里的噪声带偏 → 估计误差**往往增大**（注意不是绝对必然，还取决于具体数据分布和算法）。
5. **额外补充第三项**：现实中如果优化器没走到最小值就停了（比如深度学习里的提前停止或步长没调好），实际解比训练目标的精确解又差了一截，这就冒出第三项**优化误差**（见 1.6）。
6. **怎么解决二者的权衡**：把学习拆成两步——先**设计／挑选合适的 $\mathcal H$**，再在里面**用数据估计 $\hat h$**；具体用**正则化**（给复杂度加惩罚）和**交叉验证（CV）选模型**来平衡两边，同时**增加训练数据量 $n$** 能直接压低估计误差。

**④ 小例子**

回到 1.1 的正弦波模拟（$\sigma^2=0.09$，每次只给 10 个点）：

- **$\mathcal H$ = 所有直线**：测试误差 0.333。就算给你 100 万个点，最佳直线 $\bar h$ 依然画不出正弦波，多出来的误差主要是**近似误差**。
- **$\mathcal H$ = 所有 6 次多项式**：正弦波在它眼里不难画，近似误差几乎是 0；但 10 个点去定 7 个系数，选出来的 $\hat h$ 到处乱飞，测试误差飙到 3.685，主要是**估计误差**（严重过拟合）。
- **$\mathcal H$ = 3 次多项式**：两项都很小，测试误差 0.158，取得最佳权衡。

**⑤ 常见误区**

- **误区 1：把“近似误差 / 估计误差”和 1.1 的“偏差² / 方差”完全等同**。虽然直观上很对应，但 1.1 只适用于平方损失且对预测值做分解；这里的风险分解适用于**任何损失函数**（分类、回归都能用）。
- **误区 2：以为拼命加数据能解决所有误差**。增加数据 $n$ 只能缩小**估计误差**；如果你的模型家族 $\mathcal H$ 本身就不行（例如用直线去拟合圆），数据加到无穷大，近似误差还是降不下来。

**⑥ 对照最终版**

- 公式一行 → 把超额风险 $L(\hat h)-L(h^*)$ 拆成随机的估计误差 $L(\hat h)-L(\bar h)$ 和确定的近似误差 $L(\bar h)-L(h^*)$，其中 $\bar h$ 是 $\mathcal H$ 里最好的函数。
- "Approximation error: the class $\mathcal H$ is too poor (like bias). Estimation error: $\hat h$ is learned from finite data (like variance)." → 近似误差来自菜单 $\mathcal H$ 太穷（像偏差）；估计误差来自有限样本学习（像方差）。
- "A bigger $\mathcal H$ does not increase the approximation error, but the estimation error tends to increase." → 扩大 $\mathcal H$ 不会增大近似误差，但估计误差往往会增大。
- "Learning = choose $\mathcal H$ (design), then estimate the best function in it (training); balance by regularization / model selection by CV, and more data." → 学习的本质是先设计 $\mathcal H$、再训练估计；通过正则化、交叉验证选模型和加数据来权衡。

### 1.3 What is the generalization error and how is it related to overfitting? 什么是泛化误差？它和过拟合有什么关系？ ★

考过：[2019 Q8](../Exam_2019_zh.md)

**先懂这些：** ① 损失函数 $\ell$ 与"真实风险＝期望损失"——[第一课 · 经验风险与真实风险](../../Lectures/01_intro/06_empirical_and_true_risk.md)；② 训练误差为什么是乐观估计——[第二课 · 泛化与高维（$d/n$ 项）](../../Lectures/02_LM/02_generalization_and_high_dimensions.md)。

**最终版答案（背诵版 EN，≤5 行）：**
The generalization error (true error) is the expected loss on **new data**: $L(h)=\mathbb E[\ell(h(X),Y)]$.
The training error is too optimistic.
**Overfitting**: the training error is very low but the generalization error is high, because the model learned the noise.
We estimate it on a **test set** or by **cross-validation**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

什么是“泛化误差”（generalization error）？它和“过拟合”之间是什么关系？

**② 需要的工具**

- **泛化误差（真实风险 $L(h)$，教材常写作 $R(h)$）**：模型在**没见过、但和训练集来自同一套规律的新数据**上的平均损失——也就是它走出实验室之后真正的平均考分。“泛化（generalization）”说白了就是“举一反三的能力”。公式写作 $L(h)=\mathbb E[\ell(h(X),Y)]$。
- **训练误差（经验风险 $\hat L_n(h)$，教材常写作 $\hat R_n(h)$）**：模型在手头这 $n$ 条练习题上的平均损失 $\hat L_n(h)=\frac1n\sum_{i=1}^n\ell(h(x_i),y_i)$，可以直接用代码算出来。
- **为什么需要“期望 $\mathbb E$”**：真实世界的数据分布（比如所有未来可能出现的房子）是未知且无穷多的，所以 $L(h)$ 没法像训练误差那样精确求和算出，只能拿没见过的数据去**估计**。
- **留出数据（held-out data）**：专门藏起来、**绝对不参与训练**的数据（独立测试集，或交叉验证里的验证折）。

**③ 一步一步**

1. **我们的终极目标不是训练误差低，而是泛化误差 $L(h)$ 低**。但 $L(h)$ 看不见也算不出。
2. **为什么不能直接用训练误差 $\hat L_n(h)$ 代替泛化误差？** 因为 $\hat L_n(h)$ **系统性偏乐观（太好看）**——模型参数本身就是照着这批训练数据挑出来的，拿训练集再考它一遍，就像把**刷过的原题再考一次**，分数自然虚高。
3. **过拟合（overfitting）的本质**：模型为了迎合训练集，把训练样本里偶然夹带的**随机噪声**也当成规律记住了。结果在老题上几乎满分（**训练误差极低**），一遇新题就露馅（**泛化误差很高**）。
4. **差距什么时候最大？** 模型越复杂、训练样本 $n$ 越少，“训练误差”和“泛化误差”之间的鸿沟（泛化间隙）就越大；样本量 $n$ 越大，两者才越接近。
5. **正确评估方法**：必须把一部分数据锁在抽屉里不给模型看，在**独立测试集**或用**交叉验证**（见 3.1）去估算泛化误差。

**④ 小例子**

回到 1.1 的正弦波实验：6 次多项式在这 10 个训练点上训练误差低到 **0.022**，看起来几乎贴合得天衣无缝；可一旦拿新点来测，测试误差（对泛化误差的估计）竟高达 **3.685**——足足差了 160 多倍！“训练分极高、测试分很烂”，这就是过拟合最直观的报警信号。

**⑤ 常见误区**

- **误区 1：拿训练误差当成模型的真实水平**（只要模型够复杂，训练误差甚至能降到 0，但毫无意义）。
- **误区 2：以为泛化误差能算出精确数字**。因为未来所有新数据的完整分布是未知的，我们永远只能用有限的留出数据去**估计**它。

**⑥ 对照最终版**

- "The generalization error (true error) is the expected loss on new data: $L(h)=\mathbb E[\ell(h(X),Y)]$." → 定义：泛化误差（真实误差）是在新数据上的期望损失，课件记为 $L(h)$。
- "The training error is too optimistic." → 训练误差偏乐观（不能代表真实水平）。
- "Overfitting: the training error is very low but the generalization error is high, because the model learned the noise." → 过拟合就是训练误差很低但泛化误差很高，因为模型把噪声学进去了。
- "We estimate it on a test set or by cross-validation." → 我们只能靠测试集或交叉验证来估计泛化误差。

### 1.4 What is the role of penalization in machine learning? 惩罚项（正则化）在机器学习中起什么作用？ ★

考过：[2023.11 Ex1 Q7](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① 带惩罚优化是"机器学习算法之母"——[第二课 · Lasso 与结构化稀疏（Penalized optimization）](../../Lectures/02_LM/04_lasso_and_structured_sparsity.md)；② Ridge 为什么让方程可解——[第二课 · 岭回归与对偶](../../Lectures/02_LM/05_ridge_and_duality.md)；③ $\ell_1$／$\ell_2$／Elastic Net 的对比——[第二课 · 正则化与验证](../../Lectures/02_LM/06_regularization_and_validation.md)。

**最终版答案（背诵版 EN，≤5 行）：**
We minimize training error + $\lambda$ penalty: $\hat L_n(\theta)+\lambda\,\Omega(\theta)$. The penalty:
(1) **controls complexity** (Occam's razor): a little more bias, much less variance, less overfitting;
(2) **regularizes ill-posed** problems (Tikhonov; Ridge: $X^TX+\lambda I$ is invertible);
(3) adds **structure**, e.g. $\ell_1$ gives **sparsity**. $\lambda$ is a hyperparameter chosen by CV.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

训练模型时，为什么不直接“只让训练误差最小”，还要在后面强行加一个“惩罚项（正则化）”？它到底起什么作用？

**② 需要的工具**

- **惩罚项 $\Omega(\theta)$**：用来给模型的“复杂程度”打分，系数越大、非零系数越多，$\Omega(\theta)$ 就越大。常见两种：
  - **$\ell_2$ 惩罚（平方和）** $\sum_j \theta_j^2$：惩罚大系数，把所有系数整体往 0 拽小；
  - **$\ell_1$ 惩罚（绝对值和）** $\sum_j |\theta_j|$：能直接把不重要的系数压成**精确的 0**。
- **正则化强度 $\lambda$**（“紧箍咒力度”）：自己设定的**超参数**（不是数据学出来的），用交叉验证来挑（见 3.1）。$\lambda$ 越大，对复杂度的惩罚越狠。
- **奥卡姆剃刀原则（Occam's razor）**：“如无必要，勿增实体”——在把训练数据拟合得差不多的前提下，优先选更简单、系数更温和的模型。
- **病态问题（ill-posed problem）**：方程组解不唯一，或者数据只晃动了一丁点、算出来的系数却翻天覆地（例如特征数 $d$ 多于样本数 $n$ 时的最小二乘，见 5.7）。数学上专门用来把病态问题变稳定的方法叫 **Tikhonov 正则化**（在机器学习里就是带 $\ell_2$ 惩罚的岭回归 Ridge）。
- **稀疏（sparse）**：模型里大部分特征的系数变成了 0，只留少数真正有用的特征。

**③ 一步一步**

1. **改写训练目标**：把原来的“只最小化训练误差 $\hat L_n(\theta)$”，改成同时最小化：
   $$\hat L_n(\theta) + \lambda\,\Omega(\theta)$$
   *为什么这么改*：就像挑员工既要业绩高（$\hat L_n$ 小），又要动作简单别搞花活（$\Omega(\theta)$ 小）；$\lambda$ 决定你有多讨厌花活。
2. **作用一：控制复杂度，防止过拟合（奥卡姆剃刀）**。宁可让模型在训练集上稍微多偏一点点（多一点偏差），也要大幅压低系数对随机噪声的敏感度（方差大幅下降），从而提高泛化能力（见 1.1）。
3. **作用二：把“病态问题”救活（Tikhonov / Ridge）**。当特征太多（$d>n$）或两个特征高度重复（共线）时，普通最小二乘里 $X^TX$ 不可逆、算不出唯一解；加上 $\ell_2$ 惩罚后，矩阵变成 $X^TX+\lambda I$（只要 $\lambda>0$ 就**一定可逆**），解瞬间唯一且稳定（见 5.5）。
4. **作用三：注入结构先验（比如稀疏性）**。如果你相信只有少数特征真正有用，用 $\ell_1$ 惩罚（Lasso）可以把大量无关特征的系数压成 0，顺便完成“特征筛选”；用分组惩罚还能一整组一起选（见 5.6）。
5. **注意旋钮方向**：$\lambda=0$ 等于没开惩罚；$\lambda$ 太大则会把模型压成“几乎全是 0 的傻瓜模型”，造成**欠拟合**。

**④ 小例子**

假设有 3 个数据点 $(0,1),\,(1,2),\,(2,4)$，去中心化后算出 $S_{xx}=2,\,S_{xy}=3$。一维岭回归（Ridge，用 $\ell_2$ 惩罚斜率）算出来的直线斜率公式是 $\hat\beta_1 = \frac{S_{xy}}{S_{xx}+\lambda} = \frac{3}{2+\lambda}$：

- **$\lambda=0$（无惩罚 / OLS）**：斜率 $= 3/2 = 1.5$，完全听训练数据的；
- **$\lambda=1$（适度惩罚）**：斜率 $= 3/(2+1) = 1.0$，斜率变平缓了；
- **$\lambda=4$（强惩罚）**：斜率 $= 3/(2+4) = 0.5$，被硬生生压平了很多。

可见 $\lambda$ 越大，斜率越往 0 收缩，模型越“保守”，越不容易因为一两个噪点就剧烈摆动。

**⑤ 常见误区**

- **误区 1：以为正则化越强（$\lambda$ 越大）越好**。过强会让模型学不到真实规律，变成欠拟合。
- **误区 2：以为截距项也要惩罚**。实际通常**不惩罚截距**（截距只是整体上下平移，不代表模型变复杂）。
- **误区 3：混淆参数与超参数**。权重 $\theta$ 是优化算法学出来的参数，而 $\lambda$ 是人定（靠 CV 选）的超参数。

**⑥ 对照最终版**

- "We minimize training error + $\lambda$ penalty: $\hat L_n(\theta)+\lambda\,\Omega(\theta)$." → 最小化“训练误差＋$\lambda\times$惩罚项”，课件称它是“机器学习算法之母”。
- "The penalty: (1) controls complexity (Occam's razor): a little more bias, much less variance, less overfitting;" → 作用一：控制复杂度（奥卡姆剃刀），用一点小偏差换方差大幅下降、减轻过拟合。
- "(2) regularizes ill-posed problems (Tikhonov; Ridge: $X^TX+\lambda I$ is invertible);" → 作用二：让病态问题变得规则可解（Tikhonov 正则化；Ridge 里加 $\lambda I$ 保证矩阵可逆）。
- "(3) adds structure, e.g. $\ell_1$ gives sparsity. $\lambda$ is a hyperparameter chosen by CV." → 作用三：加入结构偏置（如 $\ell_1$ 带来稀疏），其中 $\lambda$ 是靠交叉验证选的超参数。

### 1.5 Are generalization error and overfitting relevant for clustering? 泛化误差和过拟合的概念适用于聚类吗？ ★

考过：[2019 Q8](../Exam_2019_zh.md)

**先懂这些：** ① k-means 目标（簇内平方和）随 $k$ 单调下降——[Lab4](../../Exercises/Lab4/Lab4_zh.ipynb) 簇数选择部分；② 与 7.4（如何选簇数）一起复习。

**最终版答案（背诵版 EN，≤5 行）：**
**Yes.** The inertia always decreases when $k$ grows (0 when $k=N$).
So a too large $k$ **overfits** the sample and gives unstable clusters.
Without labels, we check generalization by **stability under resampling**, held-out likelihood, or **BIC**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

像 k-means 这种**聚类算法**根本没有标准答案标签 $y$，那“泛化误差”和“过拟合”这两个概念对聚类还适用吗？

**② 需要的工具**

- **聚类与聚类的“模型”**：聚类就是把没有标签的数据自动抱团分成 $k$ 组（每组叫一个**簇**）。学出来的“模型”就是这 $k$ 个组的**中心点**（或者概率混合模型里的各团分布参数，详见 7.1）。
- **惯性（inertia）$J$**：聚类版的“训练误差”——把每个点到它所属组中心的**距离平方加起来**，衡量每堆是不是足够抱团紧凑。
- **稳定性（stability）**：从同一批总体里再抽一次样、或者从训练集里随机丢掉一点点再重跑聚类，分出来的组是不是还长得差不多。
- **BIC（贝叶斯信息准则）**：给混合高斯（GMM）等概率聚类用的打分公式，既看拟合好不好，又会对“分太细（参数太多）”自动扣分（详见 7.4）。

**③ 一步一步**

1. **结论：完全适用！** 虽然没有 $y$，但聚类依然是在**有限样本**上找数据的内在分组结构，我们同样希望学出来的这 $k$ 个中心能代表**未来新来的同类样本**（即能“泛化”到总体分布上）。
2. **为什么聚类的“训练误差”（惯性 $J$）不能直接用来选 $k$？** 因为组数 $k$ 越大，每个点离最近中心的距离只会变小不会变大；极端到 $k=N$（有 $N$ 个点就分 $N$ 组，每个点自己当中心）时，$J=0$——表面上看误差为 0，其实只是把当前这几个点硬背下来了。
3. **聚类的“过拟合”长什么样？** 当 $k$ 选得太大时，算法会顺着当前这批样本里的随机噪声强行硬拆出一些莫须有的小组。结果只要换一批新样本（或者稍微扰动数据），分组位置就完全对不上了——这就是**簇不稳定、泛化差**。
4. **没有答案标签，怎么检查聚类有没有泛化能力？** 改用三类间接方法：
   - **重采样稳定性**：多次抽样重跑，看分组结果一不一致；
   - **留出数据表现**：拿一组没参与训练的新数据，算它们到这 $k$ 个中心的惯性，或者算概率模型的**留出对数似然**；
   - **带复杂惩罚的准则**：如 **BIC** 或轮廓系数（详见 7.4）。

**④ 小例子**

假设手头有 6 个数 $\{1, 2, 3, 10, 11, 12\}$，肉眼就能看出它们本来就是两堆（$\{1,2,3\}$ 中心在 $2$，$\{10,11,12\}$ 中心在 $11$）：

- **选 $k=2$**：$J = (1-2)^2+(2-2)^2+(3-2)^2+(10-11)^2+(11-11)^2+(12-11)^2 = 4$。换一批同规律的新点 $\{1.1, 2.2, 2.9, 9.8, 11.1, 12.2\}$，两个中心依然大致在 $2$ 和 $11$，非常稳。
- **选 $k=6$**：6 个点各自成一簇，$J = 0$“完美拟合”！但其实是在生搬硬套当前这 6 个具体的数，换批新点就完全失去分组意义——这就是过拟合。

**⑤ 常见误区**

- **误区：以为“没有监督标签 $y$，就没有测试集误差，所以不存在过拟合”**。只要是在有限样本上估计总体结构，$k$ 过大就一样会拟合样本里的偶然噪声，造成过拟合。

**⑥ 对照最终版**

- "Yes. The inertia always decreases when $k$ grows (0 when $k=N$)." → 适用；因为惯性 $J$ 随 $k$ 增大一定单调下降（$k=N$ 时降为 0）。
- "So a too large $k$ overfits the sample and gives unstable clusters." → 所以 $k$ 太大会对当前样本过拟合，导致分出来的簇不稳定。
- "Without labels, we check generalization by stability under resampling, held-out likelihood, or BIC." → 没有标签时，我们通过重采样稳定性、留出数据的似然（或惯性）、以及 BIC 来检查泛化能力。

### 1.6 What is the impact of computation time (fixed resources) when the sample size grows? 计算资源固定时，样本量增大对计算时间有什么影响？ ★

考过：[2021 Ex1 Q6](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** ① 三项误差分解中的优化误差——[第六课 · 机器学习中的新权衡：三个项](../../Lectures/06_DL_zh.md)；② SGD 每步代价与 $n$ 无关——[第六课 · 反向传播与梯度下降](../../Lectures/06_DL_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
More data reduces the **estimation error**, but each exact pass over the data costs $O(n)$.
With fixed time, we must accept a larger **optimization error**.
So we use cheap methods: **SGD / mini-batches**, or a subsample.
A rough optimum on much data is often better than an exact optimum on little data.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

当电脑算力和时间预算都是**固定的**，而手里的样本量 $n$ 越来越大时，计算时间会带来什么问题，我们该如何取舍？

**② 需要的工具**

- **三项误差分解**：除了 1.2 讲的近似误差（菜单够不够好）和估计误差（样本够不够多），现实里还会多出第三项——**优化误差**（时间不够或优化器没走到训练目标的最低点，多出来的误差）。
- **每遍遍历的代价 $O(n)$**：要把 $n$ 条训练数据完整算一遍（比如算一次全量梯度），样本量翻倍，耗时至少也翻倍（记作 $O(n)$；某些矩阵算法甚至要 $O(n^2)$ 或 $O(n^3)$）。
- **SGD / 小批量（mini-batch）**：全量方法每走一步都要读完所有 $n$ 条样本；而 **SGD（随机梯度下降）／小批量**每次只随机抽一小把（比如 100 条）样本估个大概方向就更新一次参数，**走一步的时间只取决于批大小，跟总样本量 $n$ 无关**。

**③ 一步一步**

1. **好消息（数据多的红利）**：样本量 $n$ 越大，随机抽样偏差越小，**估计误差**不断下降。
2. **坏消息（算力的瓶颈）**：要精益求精地把经验风险 $\hat L_n$ 最小化到底，哪怕只把全部样本过一遍都要至少 $O(n)$ 的时间。算力／时间预算封顶时，数据太大就**算不完**了。
3. **权衡发生转变（大规模学习）**：过去是“数据太少”卡脖子，现在变成“时间不够”卡脖子——为了在规定时间内出结果，我们**必须容忍一个更大的优化误差**（优化没算到死，半路停手）。
4. **工程对策**：放弃每步都要看全量数据的昂贵算法，改用每步代价便宜、与 $n$ 无关的方法——比如 **SGD / 小批量**，或者先随机抽取一个子样本集（subsample）来训。
5. **核心结论**：在**海量数据上做粗略优化**（估计误差极低＋有一点优化误差），在测试集上的表现往往**好过在少量数据上做精确优化**（优化误差为 0＋估计误差很高）。

**④ 小例子**

假设你有 1 亿条样本，算 1 条样本的梯度要 1 微秒，你只允许程序跑 1 小时（3600 秒）：

- **全量梯度下降（精确过全数据）**：每走 1 步就要扫完 1 亿条，耗时 $10^8 \times 1\mu\text{s} = 100$ 秒。1 小时总共只能更新 **36 步**，几乎还在原地踏步。
- **小批量 SGD（每次抽 100 条）**：走 1 步只要 $100\mu\text{s}$，1 小时就能更新 **3600 万步**！虽然每步带点噪声、没法算到绝对精确的极小值（优化误差大一点），但模型早已充分消化海量数据、泛化得很好。

**⑤ 常见误区**

- **误区：以为“只要给更多数据，模型效果一定只升不降，不用管算力”**。在固定计算时间下，单步太慢会导致优化严重不足，必须换更便宜的优化算法或做子采样。

**⑥ 对照最终版**

- "More data reduces the estimation error, but each exact pass over the data costs $O(n)$." → 数据越多估计误差越小，但精确扫一遍数据至少花 $O(n)$ 时间。
- "With fixed time, we must accept a larger optimization error." → 时间固定时，只能接受更大的优化误差（没算到底）。
- "So we use cheap methods: SGD / mini-batches, or a subsample." → 所以改用每步便宜的方法：SGD / 小批量，或者抽子样本。
- "A rough optimum on much data is often better than an exact optimum on little data." → 在大数据上求个粗略解，往往胜过在小数据上求精确解。

---

## 2. 三大算法家族与 SVM

> 2023.3 和 2024 年把"三大家族各举例"合成一道题，2021 年把局部方法和全局方法分成两道题。这里拆成局部、全局、集成三道题，每道都要求**原理＋例子**。

### 2.1 What is the principle of local methods? Give an example and its hyperparameters. 局部方法的原理是什么？举一个例子并说明超参数。 ★★★

考过：[2021 Ex1 Q4](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex1 Q4](../DataML-CHPS-2022-examen_zh.md) · [2024 Ex1 Q1](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 三大家族的定义——[第一课 · 算法家族（1 Local methods）](../../Lectures/01_intro/02_algorithms_and_pipeline.md)；② "无需优化的正则化：直方图"和 k-NN——[第五课 · 基于局部性的非线性模型、k 近邻](../../Lectures/05_NLM_zh.md)；③ [Lab2](../../Exercises/Lab2/Lab2_zh.ipynb) 的 k-NN 与决策树实验。

**最终版答案（背诵版 EN，≤5 行）：**
Local methods predict at $x$ with the training points **near $x$**: **majority vote** (classification) or **average** (regression). No global optimization.
Example: **k-nearest neighbors**. Hyperparameters: **$k$** and the **distance**, chosen by cross-validation.
Small $k$: overfitting; large $k$: underfitting. (Decision trees are also local.)

**解析版（小白也能看懂）：**

**① 这道题在问什么**

机器学习里三大算法家族之一的**局部方法（local methods）**到底是怎么工作的？请举一个代表例子，并说出有哪些需要人工先调好的“超参数”。

**② 需要的工具**

- **核心直觉（“问邻居”）**：不尝试总结一条放之四海而皆准的全局公式，而是相信**“长相接近的样本，答案也接近”**。碰到新样本 $x$，只看它周围那一小块区域里的训练点就行。
- **距离（distance）**：用来量两个样本“长得多像”的尺子。最常用欧氏距离（直线距离）$\sqrt{\sum_j(x_j-x'_j)^2}$，也可用曼哈顿距离（走格子路距离）$\sum_j|x_j-x'_j|$；距离越小越像。
- **多数投票 / 局部平均**：拿来作预测的简单规则——分类看这几个邻居里哪个类别占多数；回归把这几个邻居的数值 $y$ 取平均。
- **超参数（hyperparameter）**：训练前必须由人先定好、算法不会自己学出来的设置（详见 3.4），需要用交叉验证来挑（见 3.1）。
- **维度灾难**：如果特征太多（高维空间），空间极其空旷，所有点彼此之间都隔得很远，“最近的邻居”其实一点也不近，局部方法就会失灵。

**③ 一步一步（以代表例子 $k$ 近邻 k-NN 为例）**

1. **先选好两个超参数**：邻居个数 $k$ 和距离公式（如欧氏距离）。*为什么*：这两样决定了“到底算谁是邻居”。
2. **来了一个新点 $x$，算距离**：分别计算 $x$ 到训练集里所有点的距离。
3. **找出最近的 $k$ 个点**。
4. **直接投票／平均出结果**：分类任务就少数服从多数；回归任务就取这 $k$ 个邻居标签的平均值。
5. **注意特点：没有全局优化！** 传统方法要在全体数据上列一个全局目标函数、求导优化参数（见 2.2）；局部方法根本**没有全局优化这一步**（训练时几乎只把数据存下来，计算全在预测时现做）。
6. **$k$ 怎么控制过拟合／欠拟合（“不靠优化的正则化”）**：邻域大小 $k$ 就是复杂度开关：
   - **$k$ 太小（如 $k=1$）**：只听最贴近那 1 个点的话，哪怕那个点是标错的噪点也照抄 → 偏差低、方差高，**过拟合**；
   - **$k$ 太大（如极端取 $k=n$）**：不管站在哪儿都把全场所有点拉进来平均，局部特色全被抹平 → 偏差高、方差低，**欠拟合**。

（顺带一提，**决策树**也属于局部方法：它先把空间切成一块块格子，每个格子里各自投票或取平均，超参数是最大深度、叶节点最少样本数等，见 4.1–4.2。）

**④ 小例子**

一维训练集只有 5 个点：`1(A)`、`2(A)`、`3.5(B)`、`6(B)`、`8(B)`。现在来了一个新点 $x=3$，它到这 5 个点的距离分别是 `2, 1, 0.5, 3, 5`：

- **设 $k=1$**：离 $x=3$ 最近的是 `3.5(B)`（距离 0.5）→ 预测 **B**；
- **设 $k=3$**：最近的 3 个邻居是 `3.5(B)`、`2(A)`、`1(A)` → A 占 2 票、B 占 1 票 → 预测 **A**。

只是换了一个 $k$，答案就从 B 翻成了 A，可见超参数 $k$ 必须靠交叉验证认真挑。

**⑤ 常见误区**

- **误区 1：特征单位不统一就直接算距离**。比如特征 1 是“身高（米，范围 1.5–1.9）”，特征 2 是“年薪（元，范围 50000–200000）”，年薪的零头就能把距离完全霸占，身高等于白写！用之前通常要先**标准化**（缩放到同一尺度）。
- **误区 2：二分类时 $k$ 随便取偶数**。容易出现 1:1 或 2:2 平票，通常取奇数。
- **误区 3：以为任何数据都能无脑用 k-NN**。特征维度很高时（维度灾难），效果往往急剧变差。

**⑥ 对照最终版**

- "Local methods predict at $x$ with the training points near $x$: majority vote (classification) or average (regression). No global optimization." → 局部方法用 $x$ 附近的训练点做预测（分类靠多数投票，回归靠取平均），不需要做全局优化。
- "Example: k-nearest neighbors. Hyperparameters: $k$ and the distance, chosen by cross-validation." → 代表例子是 k-NN；超参数是 $k$ 和距离度量，都靠交叉验证来选。
- "Small $k$: overfitting; large $k$: underfitting. (Decision trees are also local.)" → $k$ 小容易过拟合，$k$ 大容易欠拟合；决策树也属于局部方法。

### 2.2 What is the principle of global methods? Give an example. 全局方法的原理是什么？举一个例子。 ★★★

考过：[2021 Ex1 Q5](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex1 Q4](../DataML-CHPS-2022-examen_zh.md) · [2024 Ex1 Q1](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① [第一课 · 算法家族（2 Global methods: functional optimization）](../../Lectures/01_intro/02_algorithms_and_pipeline.md)；② 经验风险最小化（ERM）——[第一课 · 经验风险与真实风险](../../Lectures/01_intro/06_empirical_and_true_risk.md)；③ 第五课"在庞大的函数空间中最小化带惩罚的凸风险"——[第五课 · 推断原则、高效算法](../../Lectures/05_NLM_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
Global methods are based on **functional optimization**: choose one function $h_\theta$ by **minimizing a criterion on all the data**:
$\min_\theta\frac1n\sum_i\ell(h_\theta(x_i),y_i)+\lambda\Omega(\theta)$ (training error + $\lambda$ penalty). The same parameters are used everywhere.
Examples: **regularized regression (Ridge / Lasso)**, **SVM**, **boosting**, **feedforward neural networks**. Complexity is controlled by the class and by $\lambda$.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

三大算法家族的第二类——**全局方法（global methods）**的核心原理是什么？它和“问邻居”的局部方法到底差在哪里？请举一个代表例子。

**② 需要的工具**

- **核心直觉（“总结一套通吃全场的公式”）**：不再针对每个新点现找邻居，而是先把全部训练数据看完，用优化算法**一口气总结出一个全局函数 $h_\theta$**。一旦练成公式，**全空间所有新点都套同一组参数 $\theta$**。课件称这种方式为 **functional optimization（函数优化）**。
- **参数 $\theta$**：函数里待确定的数字，例如直线 $\hat y=ax+b$ 的斜率和截距 $\theta=(a,b)$。
- **经验风险最小化（ERM）**：在全部训练数据上挑参数，让平均犯错最少，即 $\min_\theta\frac1n\sum_{i=1}^n\ell(h_\theta(x_i),y_i)$。
- **惩罚项 $\lambda\Omega(\theta)$**：防止函数为了迎合训练集变得太曲折复杂（详见 1.4）。
- **优化算法**：真正动手把最低点找出来的计算手段（有直接代入的闭式解，也有一步步往下走的梯度下降，见 6.2）。

**③ 一步一步**

1. **先画圈选模型族 $h_\theta$**：决定函数长得什么样（比如所有直线、带核的 SVM、或者神经网络）。
2. **定好罚款规则（损失函数 $\ell$）**：回归常用平方损失，分类常用对数损失或合页（hinge）损失。
3. **通常加上惩罚项 $\lambda\Omega(\theta)$**：用模型族的灵活度和 $\lambda$ 共同控制复杂度，避免过拟合。
4. **在全部训练数据上做一次全局优化**：求解 $\hat\theta = \arg\min_\theta \frac1n\sum_{i=1}^n\ell(h_\theta(x_i),y_i)+\lambda\Omega(\theta)$。
5. **用同一套参数打天下**：训练一结束，不管新来的 $x$ 在哪里，都直接带入同一个 $h_{\hat\theta}(x)$ 出结果（此时训练数据甚至可以扔掉不用存）。

**对比局部方法**：k-NN 每次预测都要临时翻遍训练集找周围邻居；全局方法则是在训练时把整份数据“提炼浓缩”成一组通用参数，处处适用。

**④ 小例子**

假设有 3 套房的面积与价格数据：$(0,1),\,(1,2),\,(2,4)$，我们选直线模型 $\hat y=ax+b$，用最小二乘（OLS，不加惩罚的全局方法）在全部 3 个点上同时最小化总平方误差 $\sum_{i=1}^3(y_i-ax_i-b)^2$，算出来斜率 $a=1.5$、截距 $b=5/6\approx 0.83$。以后无论来什么面积 $x$，一律直接代入 $\hat y = 1.5x + 0.83$，全空间共用这一条线。

**考试写哪个例子最稳？** 课件第一课把全局方法归为 **functional optimization**，明确列了四个经典代表（考试优先写这几个）：
- **正则化回归（Ridge / Lasso）**：平方损失＋$\ell_2$ 或 $\ell_1$ 惩罚；
- **SVM（支持向量机）**：hinge 损失＋$\|w\|^2$ 惩罚；
- **Boosting**：指数损失，在弱分类器组合上做函数优化；
- **前馈神经网络（Feedforward NN）**：交叉熵或平方损失＋梯度下降优化。（逻辑回归也是同思路，只是课件没列在这一页的清单里。）

**⑤ 常见误区**

- **误区：“全局方法”就是一定能找到“全局最优解”**。错！“全局”是指**用一个统一的全局准则覆盖整个输入空间**，而不是指优化一定不卡在局部极小。像神经网络的全局准则是非凸的，只能保证局部最优，但它依然属于全局方法家族。

**⑥ 对照最终版**

- "Global methods are based on functional optimization: choose one function $h_\theta$ by minimizing a criterion on all the data:" → 全局方法基于“函数优化”：在全部数据上最小化一个准则，从而选出一个函数 $h_\theta$。
- "$\min_\theta\frac1n\sum_i\ell(h_\theta(x_i),y_i)+\lambda\Omega(\theta)$ (training error + $\lambda$ penalty). The same parameters are used everywhere." → 公式即“训练误差＋$\lambda$ 惩罚”；学出来的同一组参数在空间处处通用。
- "Examples: regularized regression (Ridge / Lasso), SVM, boosting, feedforward neural networks. Complexity is controlled by the class and by $\lambda$." → 课件列出的四个代表例子；模型复杂度由假设空间和 $\lambda$ 共同控制。

### 2.3 What are the two main ingredients of ensemble methods? Give an example. 集成方法的两个主要要素是什么？举一个例子。 ★★★

考过：[2023.3 Ex1 Q4](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex1 Q5](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex1 Q1](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① [第一课 · 算法家族（3 Ensemble methods: resampling and aggregation）](../../Lectures/01_intro/02_algorithms_and_pipeline.md)；② Bagging、随机森林、Boosting、bootstrap——[第五课 · 集成方法](../../Lectures/05_NLM_zh.md)；③ [Lab3](../../Exercises/Lab3/Lab3_zh.ipynb) 的集成学习部分。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **Resampling**: build many (weak) predictors from the **same data** and the same class $\mathcal H$: **bootstrap** samples (+ random features), or **reweighted** data (**boosting**).
(2) **Aggregation**: **average** (regression) or **majority vote** (classification); boosting uses a weighted vote.
Bagging / random forests mainly reduce **variance**; boosting mainly reduces **bias**.
Example: **random forest** = many unpruned trees + bootstrap + random features.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

“三个臭皮匠顶个诸葛亮”——把很多模型组合起来的**集成方法（ensemble methods）**，最核心靠哪两大要素运转？请举一个代表例子。

**② 需要的工具**

- **基学习器（弱预测器）**：拿来当组员的单个基础模型，最常用**决策树**（见 4.2）。
- **为什么不能直接把同一份数据复制 100 遍训 100 个模型？** 因为如果算法和训练集一模一样，训出来的 100 个模型也完全一模一样，合起来没有任何新信息！想让“臭皮匠”起作用，组员之间必须**各不相同（有差异性）**。
- **要素一：重采样（Resampling，造差异）**：靠同一份数据变出很多略有差异的训练版本，常用两招：
  - **bootstrap（自助采样）**：从 $n$ 条样本里**有放回地**随机抽 $n$ 次（同一条可能被抽好几次，另一些一次都没抽到；平均每份覆盖约 63.2% 的原样本），造出很多份略有区别的练习卷。
  - **重加权（reweighting，用于 Boosting）**：给上一轮做错的样本提高权重，逼下一个模型重点攻克错题。
- **要素二：聚合（Aggregation，合结果）**：把所有组员的答案合到一起——回归取**平均**，分类用**多数投票**（Boosting 则是能力越强的组员投票权重越大，即**加权投票**）。
- **两个直觉比喻**：
  - **Bagging / 随机森林**＝“**独立专家团投票**”（并行）：每个专家各自练好、互不干扰，最后投票抵消各自偶尔犯浑的错误（**主要降方差**）。
  - **Boosting**＝“**错题本接力**”（串行）：后一个老师专门盯前一个老师做错的题，把整体偏弱的地方一层层补起来（**主要降偏差**）。

**③ 一步一步**

**路线 A：Bagging 与随机森林（并行，降方差）**
1. 从原数据有放回地抽 $B$ 份 **bootstrap** 样本（这就是**重采样**）。
2. 每份样本单独训一棵**不剪枝的深树**（本身偏差低、但方差高）。**随机森林**更进一步：每棵树每次找切分特征时，只从全部特征里**随机抽一小部分**来比。*为什么*：防止所有树都挑同一个最强特征而长得一模一样，人为压低树与树之间的错误相关性 $\rho$。
3. 预测时回归取平均、分类用**多数投票**（这就是**聚合**）。*为什么有效*：假设 $B$ 个组员各自方差都是 $\sigma^2$、两两错误相关系数为 $\rho$，平均后的总方差是 $\rho\sigma^2+\frac{1-\rho}{B}\sigma^2$。树越多（$B$ 大）第二项趋近于 0，树之间越不相关（$\rho$ 小）第一项也越小，所以**大幅降低方差**。

**路线 B：Boosting（串行，降偏差）**
依次训练很多棵很浅的树，每棵新树重点拟合前面模型还错着的那部分（通过给分错样本加权重或拟合残差），最后把所有树**加权投票**。它把很多“弱小（偏差高）”的浅树叠成一个很准的强模型，所以**主要降偏差**。

**④ 小例子**

- **方差缩减直观算**：如果单棵深树方差 $\sigma^2=1$，树之间相关性 $\rho=0.3$，请 $B=100$ 棵树平均，总方差瞬间降到 $0.3 + \frac{1-0.3}{100} = 0.307$，稳了 3 倍多！反过来，如果 100 棵树完全同步（$\rho=1$），总方差还是 $1$，集成白费工夫。
- **独立投票准确率**：假设 3 个相互独立的分类器，每个准确率只有 70%。少数服从多数（至少 2 个对就算对）的准确率是 $0.7^3 + 3\times 0.7^2\times 0.3 = 0.343 + 0.441 = 0.784$（78.4%），明显超过任何单打独斗的组员。

**⑤ 常见误区**

- **误区 1：以为随便组合就行，不管组员一不一样**。只要组员错误完全同步，集成没有任何收益；“组员各有差异”是必要前提。
- **误区 2：把降方差和降偏差记反**。记住口诀：**Bagging／随机森林＝深树求平均→降方差**；**Boosting＝浅树接力补短板→降偏差**。

**⑥ 对照最终版**

- "(1) Resampling: build many (weak) predictors from the same data and the same class $\mathcal H$: bootstrap samples (+ random features), or reweighted data (boosting)." → 要素一**重采样**：用同一份数据和同一模型族造出许多不同的预测器（bootstrap＋随机特征，或重加权数据）。
- "(2) Aggregation: average (regression) or majority vote (classification); boosting uses a weighted vote." → 要素二**聚合**：取平均或多数投票；Boosting 用加权投票。
- "Bagging / random forests mainly reduce variance; boosting mainly reduces bias." → Bagging / 随机森林主要降方差；Boosting 主要降偏差。
- "Example: random forest = many unpruned trees + bootstrap + random features." → 代表例子：随机森林＝很多棵不剪枝决策树＋bootstrap 重采样＋每次分裂随机抽特征。

### 2.4 What are the two key principles of SVM? SVM 的两个核心原理是什么？ ★★

考过：[2019 Q6](../Exam_2019_zh.md) · [2020 A4](../Exam_2020_zh.md)

**先懂这些：** ① 线性可分、感知机与间隔——[第五课 · 感知机、Novikoff 定理](../../Lectures/05_NLM_zh.md)；② 最大间隔的优化问题与对偶、支持向量——[第五课 · 场景 1：具有良好泛化能力的超平面、KKT 条件](../../Lectures/05_NLM_zh.md)；③ 核的思想——[第二课 · 非线性扩展与核方法](../../Lectures/02_LM/07_kernels_and_extensions.md)；④ [Lab2](../../Exercises/Lab2/Lab2_zh.ipynb) SVM 部分。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **Maximum margin**: the separating hyperplane with the largest margin $M=1/\|w\|$ (distance to each class): a **convex quadratic** problem. Only the **support vectors** ($\alpha_i\neq0$) matter.
With slack variables: $\min\frac12\|w\|^2+C\sum_i\xi_i$ s.t. $y_i(w^Tx_i+b)\ge1-\xi_i$, $\xi_i\ge0$ (**hinge loss**).
(2) **Kernel trick**: the dual only uses the Gram matrix $x_i^Tx_j$; replace it by a kernel $k(x_i,x_j)$ (e.g. Gaussian RBF), i.e. map the data to a space where they are (almost) **linearly separable** → **non-linear** boundaries.
Hyperparameters: $C$ and the kernel (chosen on validation data).

**解析版（小白也能看懂）：**

**① 这道题在问什么**

支持向量机（SVM）最核心的两大法宝（两个基本原理）分别是什么？

**② 需要的工具**

- **直觉比喻（“铺一条最宽的马路”）**：平面上有红蓝两堆点。普通分类器只要画一条线把红蓝隔开就满足了；SVM 则追求**在红蓝之间铺一条尽可能宽的马路**（分界线是马路正中线）。这样将来新来一个带点噪声的点，也不容易一脚踩到对面去。
- **分离超平面 $w^Tx+b=0$**：二维里是一条直线，高维里是一个平直分界面；$w$ 决定朝向，$b$ 决定左右/上下平移。
- **间隔（margin）$M=1/\|w\|$**：马路中线到两边最近样本的距离。把约束写成“离中线至少 1 个单位”（$y_i(w^Tx_i+b)\ge 1$）时，单侧间隔精确等于 **$M=1/\|w\|$**（马路总宽度是 $2M=2/\|w\|$；**考试按课件写 $M=1/\|w\|$**）。所以想让马路最宽，就等价于让 $\|w\|$ 最小！
- **松弛变量 $\xi_i$ 与 hinge 损失**：现实里红蓝往往混在一起没法一刀切干净。允许第 $i$ 个点往禁区里“妥协借用” $\xi_i\ge 0$ 的距离，同时按借了多少收罚款——对应的就是 **hinge（合页）损失** $\max(0,1-y_i(w^Tx_i+b))$（分对且在马路外面，罚款为 0；踩进马路甚至站错边，借多少罚多少）。
- **对偶权重 $\alpha_i$ 与支持向量（support vectors）**：用数学里的拉格朗日对偶去解这个优化问题时，每个样本 $i$ 会分到一个重要度权重 $\alpha_i \ge 0$。解完会发现**绝大多数远离马路的点的 $\alpha_i=0$**（删掉它们对马路毫无影响），只有紧贴马路边线或踩进禁区的少数关键点有 $\alpha_i\neq 0$——这些点就叫**支持向量**。
- **核函数 $k(x,x')$ 与 Gram 矩阵**：在对偶形式里，所有样本只通过“两两内积 $x_i^T x_j$”（把所有点对的内积排成一张表，叫 **Gram 矩阵**）参与计算。把普通内积替换成核函数 $k(x_i,x_j)=\langle\phi(x_i),\phi(x_j)\rangle$，就能在不显式算出高维坐标的前提下，直接得到映射到高维空间后的内积。

**③ 一步一步**

1. **原理一：最大间隔（＋软间隔）**：
   - 先找最宽马路：最小化 $\frac12\|w\|^2$（等价于最大化 $M=1/\|w\|$），要求所有点都在马路外侧正确一边：$y_i(w^Tx_i+b)\ge 1$。
   - 若数据不能完全线性分开，加入松弛变量 $\xi_i\ge 0$：
     $$\min_{w,b,\xi}\ \frac12\|w\|^2 + C\sum_i \xi_i \quad \text{s.t.}\ y_i(w^Tx_i+b)\ge 1-\xi_i,\ \xi_i\ge 0$$
     这等价于用 hinge 损失＋$\ell_2$ 正则化。超参数 $C$ 控制“多讨厌越界”：$C$ 越大越不容忍分错（间隔变窄、容易过拟合）；$C$ 越小越宽容越界（间隔更宽、偏向欠拟合）。
   - 这是一个**凸二次规划**问题（只有一个最低谷，没有局部陷阱），能稳定求出全局最优解，最终只靠少数**支持向量**（$\alpha_i\neq 0$）决定边界。
2. **原理二：核技巧（Kernel trick）**：
   - 当原空间里红蓝只能用曲线（甚至圈）才能分开时，直线毫无办法。
   - 因为对偶求解只用到了 **Gram 矩阵**里的内积 $x_i^Tx_j$，直接把 $x_i^Tx_j$ 换成核函数 $k(x_i,x_j)$（常用**高斯 RBF 核**或多项式核）。这就悄悄把数据送进了一个更高维的 Hilbert 空间，在那里它们变得**（几乎）线性可分**；在高维空间切一刀超平面，投影回原空间就是一条弯曲的**非线性边界**。
3. **调参**：主要超参数是惩罚系数 $C$ 和核函数及其参数（如高斯核带宽 $\gamma$），都在验证集／交叉验证上选。

**④ 小例子**

- **间隔计算**：若分界线是 $x_1+x_2=0$（即 $w=(1,1)$），则 $\|w\|=\sqrt{1^2+1^2}=\sqrt2$。单侧间隔 $M=1/\|w\|=1/\sqrt2\approx 0.707$（马路总宽度 $2M=2/\sqrt2\approx 1.414$）。
- **hinge 损失打分**：对正类 $y=+1$，若 $w^Tx+b=2$（站得远远的），损失 $=\max(0, 1-2)=0$；若 $w^Tx+b=0.5$（站对了边但踩进马路），损失 $=0.5$；若 $w^Tx+b=-1$（站错边），损失 $=2$。
- **核函数的魔法**：一维数轴上，正类在 $x=-2$ 和 $x=2$，负类在 $x=0$，你一刀切不开它们。但只要把每个点升维变成二维点 $\phi(x)=(x, x^2)$，正类就在 $( -2,4),(2,4)$，负类在 $(0,0)$，用一条水平直线 $x^2=2$ 瞬间一刀切开！

**⑤ 常见误区**

- **误区 1：以为所有训练点都在撑起 SVM 的边界**。不是，只有 $\alpha_i\neq 0$ 的**支持向量**才起作用，其余点就算删掉结果也完全一样。
- **误区 2：把 $C$ 和 Ridge 里的 $\lambda$ 方向记混**。$C$ 乘在“训练误差 $\sum \xi_i$”前面，所以 **$C$ 越大＝正则化越弱**（容错少、容易过拟合）；正好和乘在惩罚项前的 $\lambda$ 相反！

**⑥ 对照最终版**

- "(1) Maximum margin: the separating hyperplane with the largest margin $M=1/\|w\|$ (distance to each class): a convex quadratic problem. Only the support vectors ($\alpha_i\neq0$) matter." → 原理一：最大间隔（$M=1/\|w\|$，是一个凸二次优化问题，只有支持向量起作用）。
- "With slack variables: $\min\frac12\|w\|^2+C\sum_i\xi_i$ s.t. $y_i(w^Tx_i+b)\ge1-\xi_i$, $\xi_i\ge0$ (hinge loss)." → 加松弛变量的软间隔公式（等价于 hinge 损失）。
- "(2) Kernel trick: the dual only uses the Gram matrix $x_i^Tx_j$; replace it by a kernel $k(x_i,x_j)$ (e.g. Gaussian RBF), i.e. map the data to a space where they are (almost) linearly separable → non-linear boundaries." → 原理二：核技巧（对偶只用 Gram 矩阵，换核等于映射到线性可分的高维空间，得到非线性边界）。
- "Hyperparameters: $C$ and the kernel (chosen on validation data)." → 超参数是 $C$ 和核（在验证集上挑）。

### 2.5 Why are convex losses sometimes used in learning? 为什么学习中有时使用凸损失？ ★

考过：[2021 Ex1 Q5](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** ① 0–1 损失与分类风险——[第三课 · 评价准则：分类器的误差](../../Lectures/03_LMC_zh.md)；② ERM 的缺点与凸替代——[第五课 · 经验风险最小化（ERM）、高效算法](../../Lectures/05_NLM_zh.md)；③ 凸性带来的计算优势——[第二课 · Lasso（The power of convexity）](../../Lectures/02_LM/04_lasso_and_structured_sparsity.md)。

**最终版答案（背诵版 EN，≤5 行）：**
The **0–1 loss** is not convex and not continuous: minimizing it is **NP-hard**.
We use a **convex surrogate** $\varphi\ge$ 0–1 loss (**hinge** for SVM, **exponential** for boosting), so $L(f)\le A(f)=\mathbb E\,\varphi(-Yf(X))$; with a linear model (or a linear span) the problem is **convex**.
Then every local minimum is **global**, and it is solved efficiently.
Moreover $\text{sgn}(f^*)$ is the **Bayes classifier**, and $L(f)-L^*$ is controlled by $A(f)-A^*$.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

二分类最关心的本来是“分错率”（0–1 损失），那为什么真实算法里大家经常改用所谓的“**凸替代损失**”？这样做到底图什么、又靠不靠谱？

**② 需要的工具**

- **0–1 损失 $\mathbf 1\{Y f(X)\le 0\}$**：把两类标签记成 $Y\in\{-1,+1\}$。预测分值 $f(x)$ 和真实 $Y$ 同号就判对（罚 0），异号或刚好踩在 0 线上就判错（罚 1）。它是“**阶梯状**”的——除了 $0$ 点那一下突然跳变，其余地方全是水平平地，**导数处处为 0**。
- **为什么 0–1 损失极难优化（NP 难）**：想象你闭着眼站在一片**由几层大平地和断崖组成的台阶**上想找最低点：脚下永远是平的，根本感觉不到往哪走能下坡；要从全部切法里穷举出分错最少的那一刀，计算量随样本数爆炸，属于 **NP 难**问题（规模一大就完全算不动）。
- **凸函数（“一口大碗”）**：形状像光滑（或折线）的碗，只有唯一一个大碗底，没有半路卡人的小坑。只要问题整体是凸的，**任何局部最低点就一定是全局最低点**。
- **凸替代损失（convex surrogate）$\varphi$ 与 $\varphi$-风险 $A(f)$**：干脆换一个**形状像大碗（凸函数）、非负、且处处踩在 0–1 损失头顶上（$\varphi \ge \text{0–1 损失}$）**的代替品，写成 $\varphi(-Yf(X))$（记 $m=Yf(X)$ 为“间隔信心值”：$m>0$ 分对，$m<0$ 分错）：
  - 课件举的两个标准代表：**hinge 损失** $\max(0, 1-m)$（用于 SVM）和**指数损失** $e^{-m}$（用于 Boosting）。它们都处处 $\ge$ 0–1 损失，把真实分类错误率 $L(f)$ 牢牢压在自己的期望 $A(f)=\mathbb E[\varphi(-Yf(X))]$ 下面，即 **$L(f)\le A(f)$**。
  - 小提醒：常用的自然对数 logistic 损失 $\ln(1+e^{-m})$ 在 $m=0$ 处等于 $0.693<1$，略低于 0–1 损失；必须换成以 2 为底的 $\log_2(1+e^{-m})$，才严格满足 $\varphi\ge$ 0–1 损失。

**③ 一步一步**

1. **原问题太难**：真实分类任务想最小化 0–1 损失，但它既不连续也不凸，直接最小化训练错误率是 **NP 难**的。
2. **偷梁换柱成凸替代**：找一个凸的、始终大于等于 0–1 损失的替代函数 $\varphi$（比如 SVM 用的 **hinge**、Boosting 用的 **exponential**），去最小化它的期望风险 $A(f)=\mathbb E[\varphi(-Yf(X))]$，于是天然保证 $L(f)\le A(f)$。
3. **配合线性结构变身凸优化**：如果模型 $f$ 对参数是线性的（例如线性函数 $w^Tx+b$，或弱分类器的线性组合），“线性模型＋凸损失”的经验风险目标整体就是**凸问题**。
4. **计算瞬间变轻松**：凸优化里**局部最优就是全局最优**，可以用梯度下降、牛顿法或二次规划高效、稳定地求到底，再也不怕卡在假谷底。
5. **理论上也没跑偏（课件第五课保证）**：人们会担心“我优化的是替代损失 $A(f)$，不是真正的错分率 $L(f)$，最后学出来的分类器会不会歪？”理论证明不会！最小化 $\varphi$-风险得到的理论最优函数 $f^*$，取符号 $\text{sgn}(f^*)$ **恰好就是理论最佳的 Bayes 分类器**；而且替代误差多出来的部分 $A(f)-A^*$，能直接锁死真实超额错分率 $L(f)-L^*$。

**④ 小例子**

令 $m=Y f(X)$（正数＝分对，越正越有把握；负数＝分错）：

| $m$（预测把握） | 0–1 损失 | hinge $\max(0,1-m)$ | 指数损失 $e^{-m}$ | $\log_2(1+e^{-m})$ | $\ln(1+e^{-m})$ |
|---|---|---|---|---|---|
| −1（分错） | 1 | 2 | 2.718 | 1.894 | 1.313 |
| 0（骑在边界上） | 1 | 1 | 1 | 1 | **0.693 (<1)** |
| 0.5（分对但不够远） | 0 | 0.5 | 0.607 | 0.684 | 0.474 |
| 2（分对且有把握） | 0 | 0 | 0.135 | 0.183 | 0.127 |

看表就能发现：0–1 损失只知道硬给 0 或 1，一旦分对一丁点（哪怕 $m=0.01$ 和 $m=2$）惩罚就全变成 0，优化器得不到任何改进指引；而 hinge 和指数损失既有坡度（告诉你往哪个方向推能更稳），又处处压在 0–1 损失上面！

**⑤ 常见误区**

- **误区 1：以为只要用了凸损失，整个训练问题就一定是凸的**。还要看模型结构！把凸损失套在多层神经网络上，因为网络本身对权重非线性，整体依然是**非凸**问题。
- **误区 2：考试随手举自然对数 $\ln(1+e^{-m})$ 当“$\ge$ 0–1 损失的替代损失”**。它在 $m=0$ 时是 $0.693 < 1$，不满足课件严格上界条件；考试举例优先写课件里的 **hinge** 和 **exponential**（或者写明 $\log_2$）。

**⑥ 对照最终版**

- "The 0–1 loss is not convex and not continuous: minimizing it is NP-hard." → 0–1 损失不凸也不连续，直接最小化是 NP 难的。
- "We use a convex surrogate $\varphi\ge$ 0–1 loss (hinge for SVM, exponential for boosting), so $L(f)\le A(f)=\mathbb E\,\varphi(-Yf(X))$; with a linear model (or a linear span) the problem is convex." → 改用 $\ge$ 0–1 损失的凸替代 $\varphi$（SVM 的 hinge、Boosting 的指数），它能上界真实错分率 $L(f)\le A(f)$；搭配线性模型（或线性张成空间）后整体变成凸问题。
- "Then every local minimum is global, and it is solved efficiently." → 于是每个局部极小都是全局极小，能高效求解。
- "Moreover $\text{sgn}(f^*)$ is the Bayes classifier, and $L(f)-L^*$ is controlled by $A(f)-A^*$." → 理论也有保障：替代风险的最优解符号就是 Bayes 分类器，真实超额误差受替代超额误差控制。

### 2.6 What other choices of loss lead to practical methods? 还有哪些损失选择能得到实用的方法？ ★

考过：[2021 Ex1 Q5](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** ① 保持建模框架、只换损失——[第二课 · 非线性扩展（Generalizations: changing what a wrong prediction means）](../../Lectures/02_LM/07_kernels_and_extensions.md)；② 深度学习的非凸损失与 SGD——[第六课 · 深度学习](../../Lectures/06_DL_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
Keep **Criterion = training error + λ penalty** and **change the loss**: **squared** (Ridge), **hinge** (SVM), **logistic** (logistic regression), **exponential** (boosting).
Other choices: **absolute / Huber** (robust to outliers), **ε-insensitive** (SVR), **quantile** loss.
Even **non-convex** losses work with **SGD** (deep learning), but with no global guarantee. The loss should match the real cost of errors.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

除了 2.5 讲的分类凸替代损失（hinge、指数损失），在机器学习里还能换用哪些不同的**损失函数**，从而变出各种好用的实用方法？

**② 需要的工具**

- **万能模板（“换汤不换药”）**：课件第二课指出，大量看似完全不同的经典算法，其实骨架都是同一条公式：
  $$\text{Criterion}(h) = \text{Training error}(h) + \lambda\,\text{Penalty}(h)$$
  **骨架不变，只换里面的损失函数（怎么定义“预测错了有多严重”），就能得到一个全新算法！**
- **残差 $r = y - h(x)$**：真实值减预测值，即猜偏了多少。
- **离群点（outlier）**：数据里混进来的极端错误点（比如正常房价 300 万，有一套多打了一个零变成 3000 万）。如果用平方损失 $r^2$，离群点会被**平方放大**，硬把整条回归线拉歪。
- **分位数（quantile）**：比如“90% 分位数”，意思是“有 90% 的情况实际值不超过这个数”（比只猜平均值更有风险把控意义）。

**③ 一步一步（把换损失能变出的实用方法理顺）**

1. **先把课件第二课／第五课的四个“标准换装”答出来（考试必写）**：
   - 换成**平方损失** $(y-h(x))^2$ → 得到**岭回归 Ridge**（$\ell_2$ 惩罚）或 **Lasso**（$\ell_1$ 惩罚）；
   - 换成 **hinge 损失** → 得到**线性 SVM**；
   - 换成 **logistic（对数）损失** $\log(1+e^{-y\beta^Tx})$ → 得到**逻辑回归**；
   - 换成**指数损失** $e^{-yh(x)}$ → 得到 **Boosting**。
2. **想要不怕极端离群点 → 换“绝对值损失”或“Huber 损失”**：
   - **绝对值损失** $|r|$：哪怕错 100 也只罚 100（线性增长，不会平方爆炸），模型学出来会去追**中位数**而不是均值，对离群点稳健；缺点是在 $r=0$ 处是个尖角，不好求导。
   - **Huber 损失**：把两者优点拼在一起——设个门槛 $\delta$，误差小时（$|r|\le \delta$）用光滑好算的 $\frac12 r^2$，误差大到像离群点时（$|r|>\delta$）改用线性增长的 $\delta(|r|-\frac12\delta)$，**既光滑好优化，又不怕离群点**。
3. **想要只用少数关键样本撑起回归线 → 换“$\varepsilon$-不敏感损失”**：
   - 写做 $\max(0, |r|-\varepsilon)$，用于支持向量回归 **SVR**（见 2.7）：误差落在 $\pm\varepsilon$ 宽的“容忍管道”内完全不罚（损失为 0），只有跑出管道的点才算支持向量。
4. **想要预测上限／下限区间 → 换“分位数损失（pinball loss）”**：
   - 给“猜高了”和“猜低了”设不同的惩罚比例（例如电网预估用电高峰，猜少了停电损失极大、猜多了浪费不多，就专罚猜低），直接预测 90% 分位数等风险边界。
5. **多分类概率预测 → 换“交叉熵损失”**；**非凸损失也照样能实用**：比如深度学习经常用非凸目标，虽然不保证找到全局最优，但配合 **SGD（随机梯度下降）** 在大数据上同样效果极佳。
6. **选损失的总原则**：损失函数应当贴合现实业务里“**猜错一次究竟会付出多大代价**”。

**④ 小例子（看数字感受“抗离群点”的差距）**

设 Huber 门槛 $\delta=1$，对比两个点的罚款：

| 残差大小 | $\frac12 r^2$（平方） | $|r|$（绝对值） | Huber（$\delta=1$） |
|---|---|---|---|
| 正常小误差 $r=0.5$ | $0.125$ | $0.5$ | $0.125$（跟平方一样光滑） |
| 极端离群点 $r=10$ | **$50$（被放大 100 倍！）** | $10$ | **$9.5$（几乎不被带偏）** |

看表一目了然：面对离群点，平方损失会疯狂尖叫（罚 50），把直线强行拽歪；Huber 在小误差时像平方一样丝滑，遇到离群点立刻冷静按直线罚款。

**⑤ 常见误区**

- **误区：以为机器学习非得用平方损失（回归）或 0–1 损失（分类）不可**。其实损失函数是可以按业务需求和稳健性需要“插拔替换”的模块。

**⑥ 对照最终版**

- "Keep Criterion = training error + λ penalty and change the loss: squared (Ridge), hinge (SVM), logistic (logistic regression), exponential (boosting)." → 保持“训练误差＋$\lambda$ 惩罚”框架不变，换四个经典损失就得到四个经典算法。
- "Other choices: absolute / Huber (robust to outliers), ε-insensitive (SVR), quantile loss." → 补充四种实用损失：绝对值／Huber（稳健）、$\varepsilon$-不敏感（SVR）、分位数损失。
- "Even non-convex losses work with SGD (deep learning), but with no global guarantee. The loss should match the real cost of errors." → 即使非凸损失配上 SGD 也能用（深度学习），只是不保证全局最优；选损失要贴合现实犯错代价。

### 2.7 Can SVM be used for regression? SVM 能用于回归吗？ ★

考过：[2019 Q6](../Exam_2019_zh.md)

**先懂这些：** 先掌握 2.4 的最大间隔和 2.6 的 $\varepsilon$-不敏感损失；[Lab3](../../Exercises/Lab3/Lab3_zh.ipynb) 里有回归方法对比。

**最终版答案（背诵版 EN，≤5 行）：**
**Yes: SVR.** We fit $f(x)=w^Tx+b$ with a **tube $f(x)\pm\varepsilon$**: errors smaller than ε cost nothing (**ε-insensitive loss**).
We minimize $\frac12\|w\|^2+C\sum_i\max(0,|y_i-f(x_i)|-\varepsilon)$.
Points strictly inside the tube are **not support vectors** (sparse solution). Kernels give non-linear regression.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

SVM（支持向量机）平时用来做分类，它能不能改成做**回归**（预测连续数值，比如房价）？

**② 需要的工具**

- **和分类 SVM 对比的直觉（“推开” vs “装进管道”）**：
  - 分类 SVM（见 2.4）是在两堆点之间铺一条宽马路，要求数据点尽量被**推到马路外面**；
  - 回归 SVR 正好相反：它以预测直线 $f(x)=w^Tx+b$ 为中心，向上下各撑开 $\varepsilon$ 宽，形成一根**容忍管道（$\varepsilon$-tube）**，要求数据点尽量**落进这根管道里面**。
- **$\varepsilon$-不敏感损失（$\varepsilon$-insensitive loss）**：写作 $\max(0,|y-f(x)|-\varepsilon)$（见 2.6）。只要预测误差没超过 $\varepsilon$（点在管内或刚好擦到管壁），**罚 0 分**；跑出管道外，才按多出来的距离罚。
- **平缓项 $\frac12\|w\|^2$**：和分类里一样，用来控制斜率不要太陡，防止曲线剧烈扭曲过拟合。

**③ 一步一步**

1. **答案：完全可以，叫支持向量回归（SVR）。**
2. **定下回归管道**：用函数 $f(x)=w^Tx+b$ 当中心线，划出上下各 $\varepsilon$ 的管道 $[f(x)-\varepsilon,\ f(x)+\varepsilon]$（总高 $2\varepsilon$）。
3. **写下优化目标**：既希望函数尽量平缓（$\|w\|^2$ 小），又希望跑出管道外的总误差尽量小：
   $$\min_{w,b}\ \frac12\|w\|^2 + C\sum_{i=1}^n \max(0, |y_i-f(x_i)|-\varepsilon)$$
4. **为什么叫“支持向量”回归？（稀疏解）** 如果一个点老老实实待在管道**正里面**（误差 $<\varepsilon$），它的损失是 0，微调直线时根本不用理它，算出来的对偶系数严格为 0；**只有落在管道壁上（$|y-f(x)|=\varepsilon$）或跑到管道外面的点**才会拽住直线，这些才是**支持向量**。所以最终预测只依赖少数几个支持向量（解是稀疏的）。
5. **照样支持核技巧**：只要把内积换成核函数 $k(x_i,x_j)$（比如高斯 RBF 核），就能弯出非线性的回归管道。主要超参数是 $C$、容忍半宽 $\varepsilon$ 和核参数。

**④ 小例子**

假设当前模型是直线 $f(x)=x$，管道半宽 $\varepsilon=0.5$（误差在 $0.5$ 以内一律免罚）：

- 点 $(2, 2.3)$：误差 $|2.3-2|=0.3 < 0.5$，在管道**严格内部** → 损失 $=0$，**不是支持向量**；
- 点 $(4, 4.5)$：误差 $|4.5-4|=0.5 = \varepsilon$，卡在**管道壁上** → 损失 $=0$，**可能是支持向量**；
- 点 $(6, 6.8)$：误差 $|6.8-6|=0.8 > 0.5$，跑出**管道外面** → 损失 $=0.8-0.5=0.3$，**是支持向量**。

**⑤ 常见误区**

- **误区 1：以为 SVM 只能用来二分类**。换上 $\varepsilon$-不敏感损失就是 SVR。
- **误区 2：以为只有管道“外面”的点才是支持向量**。刚好卡在管道**边界上**（$|y-f(x)|=\varepsilon$）的点损失虽为 0，但同样顶着管道，也可能是支持向量；真正绝对不是支持向量的，是**严格落在管道里面**的点。

**⑥ 对照最终版**

- "Yes: SVR. We fit $f(x)=w^Tx+b$ with a tube $f(x)\pm\varepsilon$: errors smaller than ε cost nothing (ε-insensitive loss)." → 可以，叫 SVR；用 $f(x)\pm\varepsilon$ 的管道拟合，小于 $\varepsilon$ 的误差不计罚（$\varepsilon$-不敏感损失）。
- "We minimize $\frac12\|w\|^2+C\sum_i\max(0,|y_i-f(x_i)|-\varepsilon)$." → 最小化平缓惩罚＋超出管道的误差之和。
- "Points strictly inside the tube are not support vectors (sparse solution). Kernels give non-linear regression." → 严格在管道内的点不是支持向量（得到稀疏解）；换上核函数就能做非线性回归。

---

## 3. 模型评估与超参数校准

### 3.1 Give an example of a hyperparameter and explain how to calibrate it. 举一个超参数的例子并说明如何校准。 ★★★

考过：[2020 A3](../Exam_2020_zh.md)（决策树超参数如何校准）· [2021 Ex1 Q7](../DataML-CHPS-2021-examen_zh.md) · [2024 Ex1 Q4](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 交叉验证具体做什么、为什么先标准化——[第二课 · 正则化与验证（Tuning the hyperparameters: Cross-validation）](../../Lectures/02_LM/06_regularization_and_validation.md)；② 训练／验证／测试三分——[作业一第 4 题：数据划分](../../Exercises/Assignment1/guide/04_data_splitting.md)；③ [Lab1](../../Exercises/Lab1/Lab1_zh.ipynb) 的验证部分。

**最终版答案（背诵版 EN，≤5 行）：**
Example: the **maximum depth** of a tree. The training error cannot choose it (deeper is always better there).
**K-fold cross-validation**: for each value in a grid, train on K−1 folds, validate on the last one, and average.
Choose the value with the **lowest validation error**, retrain on all training data, and test **once** on the test set.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

先举一个**超参数**的具体例子，再完整说明到底怎么科学地给它定一个好值（也就是“校准 / 调参” calibration）。

**② 需要的工具**

- **参数 vs 超参数**：**参数**是模型在训练时自己学出来的数字（比如直线斜率、树的切分阈值）；**超参数**是训练开始之前必须由人先拍板设定的旋钮（比如决策树的**最大深度**、k-NN 的 $k$、正则化强度 $\lambda$，详见 3.4）。
- **三份数据分工（书本比喻）**：
  - **训练集**＝平时做题的**练习册**（用来学模型参数）；
  - **验证集**＝考前选学习计划用的**模拟考**（用来对比哪个超参数最好）；
  - **测试集**＝最后检验真水平的**正式期末考**（全程封存，只在最后打分一次）。
- **K 折交叉验证（K-fold CV）**：如果手头样本本来就不多，单独切出一大块做验证集太肉痛，单次划分结果也容易受运气影响。于是把“练习册＋模拟考”合并成一份，平均切成 $K$ 份，轮流让每 1 份当一次模拟考、其余 $K-1$ 份做训练，最后把 $K$ 次模拟考分数取平均。
- **候选网格（grid）**：提前列好准备挨个试验的几个候选值，例如最大深度试 `{2, 4, 8}`。

**③ 一步一步**

1. **先把测试集锁进抽屉**：调超参数的全程绝对不看测试集。*为什么*：保证最后的成绩单公正、不虚高。
2. **把其余数据（训练＋验证池）切成 $K$ 份**（工程上常用 $K=5$ 或 $10$）。
3. **挨个试网格里的每个候选值**：例如先试“深度 $=4$”——用第 2–5 份训练、第 1 份算误差；再用第 1,3,4,5 份训练、第 2 份算误差……一共算 5 遍，把这 5 个验证误差取平均。*为什么取平均*：抹平“某一次刚好抽到简单样本或刁钻样本”的划分运气。
4. **选平均验证误差最小的候选值**（如果两个值的分数极其接近，也可以按奥卡姆剃刀挑更简单的那个）。
5. **用选好的超参数在全部训练数据上重训一遍**：*为什么*：刚才做 5 折时每次只用到了 $4/5$ 的数据，现在已经定好了“深度 $=4$”，当然要把全部训练数据合在一起喂给模型，学出最终成品。
6. **去测试集考最后一次**并汇报最终成绩。
7. **特殊数据小提示**：类别比例极度不平衡时要用**分层划分（stratified）**保证每折正负比例一致；时间序列要**按时间前后切**，绝对不能拿未来数据去训练再预测过去。

**④ 小例子**

用 **5 折交叉验证**挑决策树的最大深度（每格是对应那一折的验证错误率）：

| 最大深度 | 第 1 折 | 第 2 折 | 第 3 折 | 第 4 折 | 第 5 折 | 5 折平均误差 |
|---|---|---|---|---|---|---|
| 2（太浅） | 0.30 | 0.28 | 0.32 | 0.29 | 0.31 | 0.30 |
| 4（刚好） | 0.20 | 0.22 | 0.19 | 0.23 | 0.21 | **0.21（最低）** |
| 8（太深） | 0.25 | 0.27 | 0.24 | 0.28 | 0.26 | 0.26 |

平均验证误差在深度 4 达到最低（0.21），深度 2 欠拟合、深度 8 过拟合 → 于是选定深度 **4**，用深度 4 在全部训练池上重训一棵树，最后到测试集测一次！

**⑤ 常见误区**

- **误区 1：直接看训练误差选超参数**。只要能降低训练误差，树越深训练误差一定越低，结果永远把最过拟合的那个选出来。
- **误区 2：拿测试集来反复挑超参数**。这样测试集就悄悄变成了验证集，报出来的分数会偏乐观。
- **误区 3：先在全部数据上做标准化再切折**。标准化所需的均值和标准差必须在每一轮只用那 $K-1$ 份训练数据来算，再套到第 $K$ 份验证折上，否则验证折的分布信息就提前泄漏进训练过程了。

**⑥ 对照最终版**

- "Example: the maximum depth of a tree. The training error cannot choose it (deeper is always better there)." → 例子是决策树最大深度；训练误差没法用来选它（树越深训练误差永远越小）。
- "K-fold cross-validation: for each value in a grid, train on K−1 folds, validate on the last one, and average." → K 折交叉验证做法：对网格里每个候选值，在 $K-1$ 折上训练、在最后一折上验证，并求平均。
- "Choose the value with the lowest validation error, retrain on all training data, and test once on the test set." → 选平均验证误差最低的值，用它在全部训练数据上重训，最后在测试集上只测一次。

### 3.2 What are the stakes and difficulties of hyperparameter calibration? 超参数校准的意义和难点是什么？ ★★

考过：[2021 Ex1 Q7](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex1 Q9](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** ① 超参数控制偏差—方差（见 1.1）；② 交叉验证与 Lasso／Elastic Net 的正则化路径——[第二课 · 正则化与验证](../../Lectures/02_LM/06_regularization_and_validation.md)。

**最终版答案（背诵版 EN，≤5 行）：**
Hyperparameters set the **complexity**, so they decide **underfitting vs overfitting**.
Difficulties: we **cannot use the training error**, so we need validation data or CV;
each try needs a **new training** (costly); the score is **noisy**;
tuning on the test set gives an **optimistic** result.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

为什么要费那么大劲给超参数做“校准（调参）”？它重要在哪儿，又难在哪儿？

**② 需要的工具**

- **超参数＝复杂度总开关**：树深 $d_{\max}$、近邻数 $k$、惩罚权重 $\lambda$、学习率、神经网络层数……这些开关直接决定了模型会**欠拟合**还是**过拟合**（见 1.1）。
- **验证集 / 交叉验证**：专门留出来的“模拟考”（见 3.1）。
- **信息泄漏（data leakage）**：测试数据或验证数据的信息悄悄溜进了训练或选参流程，造成“提前透题”，成绩虚高。

**③ 一步一步**

1. **为什么生死攸关（Stakes / 意义）**：超参数直接定调模型的复杂度和偏差—方差平衡。同一套算法，超参数调对了可能拿到 95% 准确率，调砸了（比如决策树不限深度，或者 $\lambda$ 设成 $10^6$）可能比瞎猜还差。
2. **难点一：不能直接看训练误差**：因为“越复杂、训练误差就越低”，在训练集上最小化永远选出过拟合的模型。必须单独留出验证集或做 $K$ 折交叉验证——这既让用来学参数的数据变少了，又让计算量翻 $K$ 倍。
3. **难点二：每次尝试都要重新从头训练（算力贵）**：不像普通参数 $\theta$ 可以靠一次梯度下降慢慢滑到最低点，每换一组超参数往往都得**把整个模型重头训一遍**。
4. **难点三：验证分数自带“噪声”**：验证集规模有限，换一个随机种子或换一种切折方式，两个相近超参数的验证排名就可能颠倒（你看到那 0.5% 的胜出可能只是抽样运气）。
5. **难点四：多参数组合爆炸**：现实中往往有 3–5 个超参数同时要调（连续实数、整数、类别混杂），网格穷举数量指数级暴涨（所以常改用随机搜索或贝叶斯优化，见 3.3）。
6. **难点五：一不小心就“考前偷看答案”**：如果在测试集上反复调参，测试分数就会系统性**偏乐观（虚高）**，上线就翻车。

**④ 小例子**

- **只调 1 个超参数**（如 Ridge 的 $\lambda$ 试 10 个候选值）＋ 5 折交叉验证 ＝ 要训 $10\times 5 = 50$ 个模型。
- **同时调 3 个超参数**（比如树深、叶子最小样本数、特征比例，各试 10 个值）：组合数变成 $10^3=1000$ 种，乘上 5 折就要重头训 **5000 次**！

**⑤ 常见误区**

- **误区 1：用测试集分数当调参指南针**——调完再拿同一个测试集报分数，等于“拿模拟考成绩吹成真实考分”。
- **误区 2：以为把“最佳交叉验证平均分”直接当成真实泛化分就完全无偏**。既然这个分数是你从 100 组里**挑出来的最好那个**，它多少带点“选美运气”而偏乐观——所以最终还是需要一个从未参与选参的**独立测试集**（或用外层管打分、内层管调参的**嵌套交叉验证**）来给一个公正分。

**⑥ 对照最终版**

- "Hyperparameters set the complexity, so they decide underfitting vs overfitting." → 意义：超参数设定模型复杂度，直接决定是欠拟合还是过拟合。
- "Difficulties: we cannot use the training error, so we need validation data or CV;" → 难点一：不能用训练误差选，必须耗费额外数据／算力做验证集或 CV。
- "each try needs a new training (costly); the score is noisy;" → 难点二、三：每试一次都要重新训练（昂贵）；验证分数带有随机噪声。
- "tuning on the test set gives an optimistic result." → 难点五：用测试集调参会得到偏乐观（虚高）的结果。

### 3.5 Define the ROC curve. 给出 ROC 曲线的定义。 ★★

考过：[2021 Ex1 Q2](../DataML-CHPS-2021-examen_zh.md) · [2023.11 Ex1 Q2](../DataML-CHPS-2023-examen_zh.md)（原问法：评分算法的理论评价准则）

**先懂这些：** ① 分类与评分（scoring）的区别——[第三课 · 这些数据可以支持哪些决策？](../../Lectures/03_LMC_zh.md)；② α–β 图、Neyman–Pearson、理想 ROC 曲线——[第三课 · 从分类到评分：ROC 曲线与 AUC](../../Lectures/03_LMC_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
For a score $s(x)$ and a threshold $t$: $\text{TPR}(t)=P(s(X)\ge t\mid Y=1)$, $\text{FPR}(t)=P(s(X)\ge t\mid Y=0)$.
The **ROC curve** plots TPR against FPR when $t$ varies, from $(0,0)$ to $(1,1)$.
A random score gives the **diagonal**; a perfect score goes through $(0,1)$.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

给出 **ROC 曲线**的严格定义，并解释它怎么画出来、代表什么含义。（2023.11 原卷问“怎么从理论上评价一个评分算法”，答案也是 ROC／AUC。）

**② 需要的工具**

- **评分函数（score）$s(x)$**：不急着直接输出“是／否”，而是先给每个样本打一个连续的怀疑分数（比如患病概率），分数越高代表越像正类（$Y=1$）。
- **阈值（门槛）$t$**：定一条警戒线，规定 $s(x)\ge t$ 就报警判为正类。门槛 $t$ 定得高或低，报警人数和出错情况就会跟着变。
- **混淆矩阵（把猜对猜错装进四格表）**：
  - **TP（真阳性）**：真坏人（$Y=1$），也抓对了；
  - **FN（假阴性 / 漏报）**：真坏人（$Y=1$），却漏网了；
  - **FP（假阳性 / 误报）**：好人（$Y=0$），却被冤枉报警了；
  - **TN（真阴性）**：好人（$Y=0$），也放行了。
- **两个核心比率（记住大白话意思就不会混）**：
  - **TPR（真阳性率 / 抓对坏人的比例）**：所有真坏人里，成功抓到多少？
    $$\text{TPR}(t) = P(s(X)\ge t\mid Y=1) = \frac{TP}{TP+FN} \quad (\text{越高越好，理想为 }1)$$
  - **FPR（假阳性率 / 冤枉好人的比例）**：所有真好人里，错抓了多少？
    $$\text{FPR}(t) = P(s(X)\ge t\mid Y=0) = \frac{FP}{FP+TN} \quad (\text{越低越好，理想为 }0)$$

**③ 一步一步**

1. **先打分**：用评分函数 $s(x)$ 给每个样本算出分值。
2. **把阈值 $t$ 从极高一路滑到极低**：
   - 当 $t$ 高过所有分数（谁都不报警）：坏人一个没抓（TPR $=0$），好人一个没冤枉（FPR $=0$）→ 起点 **$(0,0)$**；
   - 当 $t$ 慢慢降低：越来越多人被划进报警线，FPR 和 TPR 同时上升；
   - 当 $t$ 低过所有分数（全员报警）：坏人全抓了（TPR $=1$），好人也全冤枉了（FPR $=1$）→ 终点 **$(1,1)$**。
3. **描点连线得到 ROC 曲线**：在横轴为 **FPR（误报率）**、纵轴为 **TPR（命中率）**的平面上，把 $t$ 取遍所有实数时算出的点 $(\text{FPR}(t),\,\text{TPR}(t))$ 连起来，就是 **ROC 曲线**。
4. **怎么看一条 ROC 曲线好不好？**
   - **闭着眼乱打分（随机评分）**：分数和真假毫无关系，门槛放进 30% 的人时，就会随机抓到 30% 的坏人和 30% 的好人，永远满足 $\text{TPR}=\text{FPR}$，画出来是一条从 $(0,0)$ 到 $(1,1)$ 的**对角线**；
   - **完美打分**：所有坏人的分数都严格高于所有好人。当 $t$ 刚好卡在坏人和好人中间时，**所有坏人全抓住（TPR $=1$）、好人一个没冤枉（FPR $=0$）**，曲线直角贴着左上角 **$(0,1)$** 走！
   - 总结：**曲线越鼓向左上角，打分能力越强**。

**④ 小例子**

5 个样本按分数从高到低排：`0.9(+)`、`0.8(−)`、`0.7(+)`、`0.4(+)`、`0.2(−)`（共 3 个正类 `+`、2 个负类 `−`）。把阈值 $t$ 从高往低放：

| 阈值 $t$ | 被判为正类的样本 | TP（抓对正类） | FP（冤枉负类） | TPR $=\text{TP}/3$ | FPR $=\text{FP}/2$ |
|---|---|---|---|---|---|
| 1.0（没人过线） | 无 | 0 | 0 | 0 | 0 |
| 0.9 | 0.9 | 1 | 0 | 0.333 | 0 |
| 0.8 | 0.9、0.8 | 1 | 1 | 0.333 | 0.5 |
| 0.7 | 前 3 个 | 2 | 1 | 0.667 | 0.5 |
| 0.4 | 前 4 个 | 3 | 1 | 1 | 0.5 |
| 0.2 | 全部 5 个 | 3 | 2 | 1 | 1 |

把坐标 $(0,0)\to(0,0.333)\to(0.5,0.333)\to(0.5,0.667)\to(0.5,1)\to(1,1)$ 顺次连起来，就是这条数据的 ROC 曲线。

**⑤ 常见误区**

- **误区 1：以为 ROC 是在评价某一个具体阈值 $t$ 下的分类器**。ROC 画出了**所有阈值**的权衡曲线，评价的是评分函数把正类排在负类前面的“排序本事”，和单个阈值无关。
- **误区 2：把横纵轴画反**。记住口诀：**横轴是误报 FPR（越小越好），纵轴是抓中 TPR（越大越好）**，所以理想点在**左上角 $(0,1)$**。

**⑥ 对照最终版**

- "For a score $s(x)$ and a threshold $t$: $\text{TPR}(t)=P(s(X)\ge t\mid Y=1)$, $\text{FPR}(t)=P(s(X)\ge t\mid Y=0)$." → 给出评分 $s(x)$ 和阈值 $t$ 后，写出 TPR 和 FPR 的概率定义。
- "The ROC curve plots TPR against FPR when $t$ varies, from $(0,0)$ to $(1,1)$." → ROC 曲线就是当阈值 $t$ 变化时，以 FPR 为横轴、TPR 为纵轴画出的从 $(0,0)$ 到 $(1,1)$ 的曲线。
- "A random score gives the diagonal; a perfect score goes through $(0,1)$." → 两条基准线：随机打分是对角线，完美打分经过左上角 $(0,1)$。

### 3.6 What is the interest of the ROC curve and the AUC? ROC 曲线和 AUC 有什么用？ ★★

考过：[2021 Ex1 Q2](../DataML-CHPS-2021-examen_zh.md) · [2023.11 Ex1 Q2](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① 评分的最优解、实用准则 AUC——[第三课 · 评分的最优解、实用准则：ROC 曲线下面积（AUC）](../../Lectures/03_LMC_zh.md)；② 先理解 3.5。

**最终版答案（背诵版 EN，≤5 行）：**
ROC evaluates a score **for all thresholds**.
We use it to **compare** models and to **choose a threshold** (costs, max false alarms).
**AUC** = area under the curve = $P(s(X^+)>s(X^-))+\tfrac12P(s(X^+)=s(X^-))$: 0.5 = random, 1 = perfect ranking.
With rare positives, also use the **precision–recall** curve.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

前面学会了画 ROC 曲线（见 3.5），那实际工作中 **ROC 曲线**和它下面的面积 **AUC** 到底有什么用？又有什么要注意的局限？

**② 需要的工具**

- **ROC 曲线**（见 3.5）：把所有可能阈值 $t$ 下的 `(误报率 FPR, 抓中率 TPR)` 画成的一条线。
- **AUC（Area Under Curve，曲线下面积）**：把整条 ROC 曲线下面的面积算出来，得到一个 $0$ 到 $1$ 之间的总分。
  - 它有一个非常好懂的概率含义：**随机抽一个真坏人 $X^+$ 和一个真好人 $X^-$，模型给真坏人打分比真好人高的概率**（打成平手算 0.5 分）：
    $$\text{AUC}=P(s(X^+)>s(X^-))+\tfrac12P(s(X^+)=s(X^-))$$
  - *为什么要写后面的 $\frac12 P(s(X^+)=s(X^-))$？* 如果所有人都被打同一分数（完全废模型），没有平局项会算出 0，加上平局算一半才得出正确的 0.5（等同随机瞎猜）。
- **工作阈值（operating threshold）与代价**：曲线只是展示所有可能，模型真正上线时，我们必须挑定一个具体的阈值 $t$ 来做“是／否”决定——选哪个点取决于**误报（冤枉好人）**和**漏报（放走坏人）**哪个代价更高。
- **Neyman–Pearson 准则**：先钉死一条红线——“最多只能容忍多少误报率（如 FPR $\le 5\%$）”，然后在此前提下挑抓中率（TPR）最高的阈值。

**③ 一步一步（ROC 和 AUC 的四大用处＋局限）**

1. **用途一：不依赖阈值，全面体检模型**：很多场景一开始根本没定死阈值，ROC 一张图把所有阈值下的权衡一次性摊开，不被某个拍脑袋的阈值误导。
2. **用途二：一眼对比多个模型谁更强**：如果模型 A 的 ROC 曲线**整条压在模型 B 的上方**，说明无论未来把误报率容忍线设在哪里，A 抓中的比例都比 B 高——A 全面碾压 B。
3. **用途三：按业务代价挑选最佳阈值 $t$**：在 ROC 曲线上直接按要求选落脚点——例如医疗筛查宁可多误报也不能漏诊，选偏右上（TPR 高）的点；垃圾邮件拦截不能误删正常邮件，就在 FPR $\le 1\%$ 的区间里选 TPR 最高的点。
4. **用途四：用 AUC 把一整条曲线浓缩成一个打分**：模型曲线偶尔会交叉、不好比谁大谁小，此时直接比面积 **AUC**：$0.5$＝瞎猜，$1.0$＝所有正类排在所有负类前面。因此 AUC 是**评价排序／评分模型**的标准准则。
5. **两大局限**：
   - **正类极稀少时 ROC 容易虚高**：假设 10000 人里只有 10 个病人、9990 个健康人。哪怕模型冤枉了 1% 的健康人（FPR $=0.01$，ROC 上几乎贴死左边界、AUC 看着高达 0.99），那也是冤枉了 **100 个健康人**，假警报比真病人多 10 倍！此时必须搭配看**精确率—召回率（Precision–Recall）曲线**。
   - **AUC 只看“谁排在谁前面”，不管分数准不准**：只要把所有分数同时乘 0.01 或加 100，排序完全没变，AUC 一点不变——但概率数值已经严重失真了。

**④ 小例子**

接 3.5 的 5 个样本：3 个正类分数 `0.9, 0.7, 0.4`，2 个负类分数 `0.8, 0.2`。

- **按“正负配对概率”算 AUC**：一共 $3\times 2 = 6$ 对正负组合，逐对看谁分高：
  `0.9>0.8`（对）、`0.9>0.2`（对）、`0.7>0.8`（错）、`0.7>0.2`（对）、`0.4>0.8`（错）、`0.4>0.2`（对）→ 6 对里赢了 4 对 → **AUC $=4/6 \approx 0.667$**。
- **按“ROC 曲线下面积”算 AUC**：3.5 算出的台阶在横轴 $\text{FPR}\in[0,0.5]$ 这半段高度一直是 $\text{TPR}=0.333$，在 $[0.5,1]$ 这半段高度跳成 $\text{TPR}=1$ → 两个矩形面积相加 $= 0.5\times 0.333 + 0.5\times 1 = 0.667$，**两种算法严丝合缝相等！**
- **按曲线挑阈值**：若要求绝对不冤枉好人（FPR $=0$），只能取 $t=0.9$，但只抓到 1/3 的坏人；若能容忍冤枉一半好人（FPR $=0.5$），取 $t=0.4$ 就能把坏人全抓光。

**⑤ 常见误区**

- **误区 1：以为 AUC 高就等于模型输出的“概率数字校准得很准”**。AUC 只评价“排序先后”，不管概率大小本身准不准。
- **误区 2：正负样本比例极度悬殊（如 1:1000）时只盯着 ROC-AUC 看**，容易盲目乐观，必须配合 Precision–Recall 曲线。

**⑥ 对照最终版**

- "ROC evaluates a score for all thresholds." → ROC 曲线同时在所有阈值下评估一个评分函数。
- "We use it to compare models and to choose a threshold (costs, max false alarms)." → 两个核心用途：对比不同模型，以及根据误报/漏报代价或最大误报率上限挑选阈值。
- "AUC = area under the curve = $P(s(X^+)>s(X^-))+\tfrac12P(s(X^+)=s(X^-))$: 0.5 = random, 1 = perfect ranking." → AUC 即曲线下面积，等于随机正负对排序正确的概率（同分算一半）：0.5 是瞎猜，1 是完美排序。
- "With rare positives, also use the precision–recall curve." → 正类稀少时，还要配合使用精确率—召回率曲线。

### 3.3 Can hyperparameter calibration be solved by an optimization technique? 超参数校准能用优化方法解决吗？ ★

考过：[2023.3 Ex1 Q9](../DataML-CHPS-2022-examen_zh.md)（2024 Ex1 Q4 的参考答案也涉及）

**先懂这些：** 先掌握 3.1 的交叉验证流程；再对比 6.2 中"普通"的数值优化（有梯度、可多次廉价评估）。

**最终版答案（背诵版 EN，≤5 行）：**
**Yes**, it is a **bi-level problem**: $\min_\lambda\hat R_{\text{val}}(\hat\theta(\lambda))$.
But the objective is a **black box**: no gradient, **expensive**, **noisy**, **non-convex**, mixed discrete / continuous variables.
So we use **grid search**, **random search** or **Bayesian optimization**. No guarantee of the global optimum.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

既然调超参数也是“找一组让验证误差最小的数”，那能直接拿优化算法来算吗？如果可以，它和训练普通参数（比如梯度下降）有什么不一样？

**② 需要的工具**

- **双层优化（bi-level problem）**：大优化套着小优化。打个比方，就像“总设计师定规则（外层），教练训练球员（内层）”：
  - **内层**（训练）：固定某组超参数 $\lambda$，在训练集上求出最优模型参数 $\hat\theta(\lambda)$；
  - **外层**（调参）：拿着刚才练出来的 $\hat\theta(\lambda)$ 去验证集打分 $\hat R_{\text{val}}(\hat\theta(\lambda))$，调整 $\lambda$ 让这个模拟考分数尽量低。
- **黑盒函数（black box）**：从外层看，输入一个 $\lambda$，要经过漫长训练才吐出一个验证误差，里面怎么一步步算出来的外层根本看不清、也求不了导数（就像一个黑盒子，只能试吃，没法拆开看配方）。
- **无梯度搜索三剑客**：
  - **网格搜索（grid search）**：提前排好整齐的格子，每个组合挨个全试一遍；
  - **随机搜索（random search）**：在范围内随机撒点来试；
  - **贝叶斯优化（Bayesian optimization）**：边试边总结——根据前几次结果建一个便宜的猜想地图（代理模型），专挑“最有希望破纪录”或“还没探过”的地方去试，尽量少试几次就能找到好解。

**③ 一步一步**

1. **可以写成优化问题**，而且正是一个**双层优化问题**：
   $$\min_\lambda\ \hat R_{\text{val}}\big(\hat\theta(\lambda)\big)$$
   其中 $\hat\theta(\lambda)$ 是在给定 $\lambda$ 下在训练集上优化出来的模型参数。
2. **为什么不能直接套梯度下降去解？** 因为外层目标是个难啃的**黑盒**：
   - **没有梯度（不可微）**：像“树深=3 还是 4”“用哪种核函数”这种整数、类别开关根本没法求导；
   - **评估一次极其昂贵**：外层每算 1 个点，内层就得完整训练 1 次（交叉验证时甚至要训练 $K$ 次）；
   - **目标带随机噪声**：换个样本划分或随机种子，分数就上下晃；
   - **非凸、有大量坑洼**：可能有很多局部极小值；
   - **变量混杂**：连续小数（学习率、$\lambda$）、整数（层数、$k$）、选项标签（核种类）混在一起。
3. **实际用什么优化算法来解？** 只能用**不依赖梯度的黑盒优化方法**：
   - 超参数很少（1–2 个）时用**网格搜索**；
   - 有 3 个以上超参数时优先**随机搜索**（不会把预算浪费在不重要的参数网格上）；
   - 单次训练很贵时用**贝叶斯优化**（也可以配合“先试小预算、表现差提前淘汰”的多保真方法如 Hyperband）。
4. **注意限制**：黑盒优化同样**不保证找到全局最优**；且验证误差再怎么优化，**测试集始终不准参与**。

**④ 小例子（为什么 9 次随机搜索常比 3×3 网格强）**

假设要调 2 个超参数：学习率（**特别重要**）和随机种子（**几乎没影响**），预算只够试 9 次：

- **3×3 网格搜索**：把 9 次排成整齐的 3 行 3 列，重要参数（学习率）翻来覆去其实**只试了 3 个不同的值**（每个值跟无关参数陪跑了 3 遍）；
- **9 次随机搜索**：每次两个数都重新随机抽，重要的学习率**足足试了 9 个不同取值**，撞中好值的概率高得多！

**⑤ 常见误区**

- **误区：以为“只要也是最小化误差，就能和普通训练一样跑一次梯度下降搞定”**。大多数场景拿不到验证误差对超参数的解析梯度，只能用无梯度黑盒搜索。

**⑥ 对照最终版**

- "Yes, it is a bi-level problem: $\min_\lambda\hat R_{\text{val}}(\hat\theta(\lambda))$." → 可以，它是一个双层优化问题（外层调 $\lambda$ 最小化验证误差，内层学 $\hat\theta(\lambda)$）。
- "But the objective is a black box: no gradient, expensive, noisy, non-convex, mixed discrete / continuous variables." → 外层目标是个黑盒：无梯度、评估昂贵、有噪声、非凸、离散与连续变量混杂。
- "So we use grid search, random search or Bayesian optimization. No guarantee of the global optimum." → 因此常用网格搜索、随机搜索或贝叶斯优化，都不保证全局最优。

### 3.4 Which parameters are chosen by the data scientist and which are learned by the algorithm? 哪些参数由数据科学家选择，哪些由算法学得？ ★

考过：[2023.3 Ex1 Q6](../DataML-CHPS-2022-examen_zh.md)（原问法：任选一种监督算法描述其特征）；[2019 Q5](../Exam_2019_zh.md) 问的决策树"参数"也要区分这两类

**先懂这些：** 在任一具体算法上区分：优化变量（$\theta$）与固定它们的外部设置（$\lambda$、结构）——[第二课 · 最小二乘](../../Lectures/02_LM/01_linear_models_and_least_squares.md) 与 [正则化与验证](../../Lectures/02_LM/06_regularization_and_validation.md)。

**最终版答案（背诵版 EN，≤5 行）：**
Example: **Ridge**, $\min\sum_i(y_i-w^Tx_i-b)^2+\lambda\|w\|^2$.
**Learned** by the algorithm: the weights **$w$ and $b$**.
**Chosen** by the data scientist: the features and their scaling, the type of penalty, the value of **$\lambda$** (by CV), the validation protocol.
For a tree: splits are learned, the depth is chosen.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

面对一个机器学习算法，到底哪些量是由**人（数据科学家）提前拍板**的，哪些量是由**算法自己从数据里学出来**的？（2023.3 要求任选一个监督算法来说明；2019 年则是结合决策树来问。）

**② 需要的工具**

- **做菜类比（瞬间分清两类量）**：
  - **数据科学家选的（外围设定与超参数）**：相当于厨师开火前的准备——“挑什么食材（选特征、切分/标准化）、用蒸锅还是炒锅（选模型与惩罚类型）、把灶台火力拧到第几档（超参数 $\lambda$ 或树深）、定好怎么试菜（验证方案）”。
  - **算法学出来的（模型参数）**：开火之后，程序在数据上跑优化自动算出来的具体数字，比如“盐放几克、酱油放几勺”（斜率权重 $w$、截距 $b$，或决策树具体的切分点）。
- **标准化（standardization）**：把每个特征缩放到均值 0、标准差 1。*为什么带惩罚的模型一定要做*：如果特征 1 用“毫米”记、特征 2 用“千米”记，千米特征为了抵消单位差异权重 $w_2$ 天然很大，直接拿 $\lambda\|w\|^2$ 惩罚就会偏心狠罚千米特征！

**③ 一步一步（以 Ridge 岭回归为例，顺带看决策树）**

1. **写出 Ridge 的优化目标**：$\min_{w,b}\sum_{i=1}^n(y_i-w^Tx_i-b)^2+\lambda\|w\|_2^2$。
2. **哪些是算法学出来的（Learned）？**
   - 权重向量 **$w$** 和截距 **$b$**。只要把上式求导解线性方程，算法自己会从训练数据里把它们算出来（截距一般不放进惩罚项）。
3. **哪些是数据科学家选的（Chosen）？**
   - 用哪些**特征**、怎么做预处理（例如**标准化**）；
   - 用什么**惩罚形式**（这里选的是 $\ell_2$ 平方惩罚，而不是 $\ell_1$）；
   - 正则化旋钮 **$\lambda$** 的具体数值（通过交叉验证选出来，见 3.1）；
   - **验证方案**（用几折交叉验证、怎么切分），如果是做分类还有决策阈值 $t$。
4. **换成决策树也完全同理**：
   - **算法学出来的**：每个节点到底按哪个特征切、切分阈值是多少、叶子输出的预测值（均值或多数类）；
   - **数据科学家选的**：停止规则与复杂度上限（最大深度 `max_depth`、叶节点最少样本数等）以及划分准则（Gini / 熵 / MSE）。

**④ 小例子**

你在电脑上用 `scikit-learn` 跑一次 Ridge 回归：

1. **人来定**：你选定用面积和房龄两个特征并做标准化，选定 $\ell_2$ 惩罚，设好 5 折交叉验证去试 $\lambda\in\{0.1, 1, 10\}$，最终挑出 **$\lambda = 1$**。
2. **算法学**：`fit()` 跑完，程序自己吐出 **$w = (0.8, -0.3),\ b = 2.1$**。

**⑤ 常见误区**

- **误区 1：把 $\lambda$、最大深度、$k$ 当成“学出来的参数”**。算法永远不会自己通过最小化训练误差去更新 $\lambda$（否则它会把 $\lambda$ 设成 0）。
- **误区 2：以为数据科学家只选超参数 $\lambda$**。别忘了“选特征、做标准化、定惩罚类型、选验证方法”同样是人定的。

**⑥ 对照最终版**

- "Example: Ridge, $\min\sum_i(y_i-w^Tx_i-b)^2+\lambda\|w\|^2$." → 举 Ridge 回归为例。
- "Learned by the algorithm: the weights $w$ and $b$." → 算法学出来的是权重 $w$ 和截距 $b$。
- "Chosen by the data scientist: the features and their scaling, the type of penalty, the value of $\lambda$ (by CV), the validation protocol." → 数据科学家选的是特征及缩放方式、惩罚类型、$\lambda$（用 CV 选）和验证方案。
- "For a tree: splits are learned, the depth is chosen." → 对决策树来说：分裂点是学出来的，最大深度是人选的。

### 3.7 Which evaluation criteria can be used for classification data? 分类数据可以用哪些评价准则？ ★

考过：[2023.3 Ex1 Q3](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** ① 分类、评分、概率估计是三种不同的任务——[第三课 · 这些数据可以支持哪些决策？](../../Lectures/03_LMC_zh.md)；② 混淆矩阵与留出法——[第三课 · 评价准则、实践中的留出法](../../Lectures/03_LMC_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
It depends on the task, always measured on **test data**.
Class decision: **error rate / accuracy**, cost-weighted error; with imbalanced classes: **precision, recall, F1**.
Ranking: **ROC / AUC**, PR curve. Probabilities: **log-loss**, Brier score.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

拿到一份带分类标签的数据（比如判断邮件是不是垃圾邮件、交易是不是欺诈），不能只盯着“正确率”这一个数看。到底有哪些评价准则（指标）可以用，每种指标又分别在什么时候掏出来？

**② 需要的工具**

- **混淆矩阵**（TP、FP、FN、TN 四个格子，见 3.5）。
- **准确率（Accuracy）** $=\frac{TP+TN}{\text{总人数}}$；**错误率** $=1-\text{准确率}$。
- **精确率（Precision）** $=\frac{TP}{TP+FP}$：你拉响的所有警报里，**真抓对的比例**（问的是“报一次警，可不可信？”）。
- **召回率（Recall / TPR）** $=\frac{TP}{TP+FN}$：所有真实坏人里，**被你抓出来的比例**（问的是“有没有漏网之鱼？”）。
- **特异度（Specificity）** $=\frac{TN}{TN+FP}$：所有真实好人里，**安全放行的比例**（$= 1 - \text{FPR}$）。
- **$F_1$ 分数** $=\frac{2PR}{P+R}$：精确率 $P$ 和召回率 $R$ 的**调和平均**。*为什么不用普通平均？* 如果一个模型只有 $R=1.0$ 但 $P=0.01$（全员报警），普通平均有 0.505 看着不错，调和平均却只有 0.02——专治“严重偏科”。
- **平衡准确率（Balanced Accuracy）**：正类的召回率与负类的特异度取平均 $\frac12(\text{TPR}+\text{TNR})$，用来防止大类霸榜。
- **概率评价指标**：**对数损失（log-loss / 交叉熵）** $-\sum y\log p$（自信猜错会被狠罚）和 **Brier 分数** $\frac1n\sum(y-p)^2$（把概率当成数值算均方误差）。

**③ 一步一步（按“模型输出什么”选指标，全部在测试集上算）**

所有评价指标**绝不能用训练集算**，必须在独立测试集（或交叉验证验证折）上算。具体挑哪个指标，取决于你拿模型做什么决策（见 5.2）：

1. **直接下结论（硬分类：输出 0 或 1）**：
   - 类别大致均衡、错一格代价一样 → 用**错误率 / 准确率**；
   - 误报和漏报代价不一样（如癌症漏诊比误报严重得多）→ 用**混淆矩阵＋代价加权错误率**；
   - 类别严重不平衡（如 99% 好人、1% 坏人）→ 看**精确率、召回率、$F_1$、平衡准确率**。
2. **只按风险排序（评分 / Ranking：输出谁更可疑）**：
   - 改看跟单个阈值无关的 **ROC 曲线和 AUC**（见 3.5、3.6）；正类极稀少时再搭配 **PR 曲线（精确率—召回率曲线）**。
3. **汇报真实概率（Probability estimation：输出“80% 概率患病”）**：
   - 必须检查概率本身准不准，用 **log-loss（对数损失）**、**Brier 分数**和校准曲线（reliability diagram）。

（如果用交叉验证，除了均值，最好把各折的**波动标准差**也一并报告。）

**④ 小例子（欺诈检测：1000 笔交易里只有 30 笔欺诈、970 笔正常）**

- **废模型 A（全部闭眼判“正常”）**：
  970 笔正常全蒙对，准确率高达 **97.0%**！但真欺诈一笔没抓到，召回率 $=0$，完全是个废物模型。
- **模型 B（真实干活）**：抓出 $\text{TP}=24$、漏掉 $\text{FN}=6$、误报 $\text{FP}=40$、放行 $\text{TN}=930$。
  - 准确率 $=(24+930)/1000=$ **95.4%**（表面看竟然比废模型 A 还低！）；
  - 但召回率 $R = 24/(24+6) = 0.80$（抓住了 8 成欺诈），精确率 $P = 24/(24+40) = 0.375$，$F_1 = 2\times 0.375\times 0.8/(0.375+0.8) \approx 0.51$，平衡准确率 $= \frac12(24/30 + 930/970) \approx 0.88$。

一眼看出：类别不平衡时**只看准确率会被严重误导**。

**⑤ 常见误区**

- **误区 1：不管三七二十一，全用 Accuracy（准确率）打天下**。遇到不平衡数据直接翻车。
- **误区 2：把精确率 Precision 和召回率 Recall 搞混**。记住：分母是“**我报成正的**”（$TP+FP$）叫精确率（报得准不准）；分母是“**本来真是正的**”（$TP+FN$）叫召回率（抓得全不全）。

**⑥ 对照最终版**

- "It depends on the task, always measured on test data." → 选什么准则取决于具体任务，且永远要在测试数据上计算。
- "Class decision: error rate / accuracy, cost-weighted error; with imbalanced classes: precision, recall, F1." → 类别决策：错误率／准确率、代价加权误差；不平衡时看精确率、召回率、$F_1$。
- "Ranking: ROC / AUC, PR curve. Probabilities: log-loss, Brier score." → 排序用 ROC／AUC 和 PR 曲线；概率质量用 log-loss 和 Brier 分数。

### 3.8 How do you measure classification performance with a train–test split (N = 700 + 300)? 如何用训练／测试划分评估分类性能（700＋300）？ ★

考过：[2019 Q9a](../Exam_2019_zh.md)

**先懂这些：** [作业一第 4 题：数据划分](../../Exercises/Assignment1/guide/04_data_splitting.md)；[第三课 · 实践中的留出法](../../Lectures/03_LMC_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
Classes are **imbalanced (70/30)**, so use a **stratified** split, e.g. 80/20:
**train 800 (560 + 240)**, **test 200 (140 + 60)**.
Fit the model (and the scaling) on the train set only.
Evaluate **once** on the test set: **confusion matrix**, recall, F1 or AUC, not only accuracy.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

手头有 1000 条带标签的样本（其中 700 条属于类 1，300 条属于类 2），怎样通过**训练集／测试集划分（train–test split）**，老老实实测出这个分类算法到底准不准？

**② 需要的工具**

- **训练／测试划分（留出法）**：把数据一分为二——大头拿去给模型学习，留一小头锁起来当期末考卷（见 3.1）。
- **分层抽样（stratified split）**：因为原数据不是 5:5，而是 **7:3 不平衡**的。分层抽样就像按班级男女生比例抽代表：先从 700 个类 1 里随机抽 80%，再单独从 300 个类 2 里随机抽 80%，保证切出来的训练集和测试集**永远都是 7:3**，不会因为手气不好把少数类全切到同一边去。
- **严防信息泄漏（预处理只在训练集上拟合）**：标准化所需的均值、标准差（或缺失值填补用的均值）只能用那 800 条训练数据算，再套用到 200 条测试数据上，不能让测试数据提前影响训练。
- **合适指标**（见 3.7）：不能只报一个准确率。

**③ 一步一步**

1. **看清数据比例**：700 vs 300（70% / 30%）属于类别不平衡，第一反应就要选**分层划分**。
2. **按 80/20 切分**：打乱两类各自的顺序后按比例抽：
   - **训练集（80%，共 800 条）**：类 1 取 $700\times 0.8 = 560$ 条，类 2 取 $300\times 0.8 = 240$ 条；
   - **测试集（20%，共 200 条）**：类 1 取 $700\times 0.2 = 140$ 条，类 2 取 $300\times 0.2 = 60$ 条。
3. **（如果要调超参数）**：在切好的 800 条训练集内部再做交叉验证或切出验证集，**绝对不能动用这 200 条测试集**。
4. **只在训练集上拟合**：用这 800 条数据做特征标准化、训练分类器；然后用同一套缩放规则去处理那 200 条测试集。
5. **在测试集上只考一次并选对指标**：画出混淆矩阵，汇报少数类的召回率、精确率、$F_1$ 或 AUC，而不仅仅只报准确率（否则全猜类 1 就能混到 70% 准确率）。
6. **知道这个做法的小缺憾**：单次切分评估结果全看这 200 条样本的“抽签运气”；数据量才 1000 条时，改用**分层 K 折交叉验证**更稳（见 3.9）。

**④ 小例子**

核对一下切分后的账本：

| 集合 | 总数 | 类 1（占 70%） | 类 2（占 30%） |
|---|---|---|---|
| 原数据 | 1000 | 700 | 300 |
| 训练集（80%） | **800** | **560** ($800\times 0.7$) | **240** ($800\times 0.3$) |
| 测试集（20%） | **200** | **140** ($200\times 0.7$) | **60** ($200\times 0.3$) |

两边比例严格保持 7:3。记住：哪怕一个模型什么都不学、闭着眼全猜类 1，在这 200 条测试集上也能蒙到 $140/200 = 70\%$ 的准确率——所以必须看混淆矩阵、$F_1$ 或 AUC。

**⑤ 常见误区**

- **误区 1：直接随机切 800/200 不分层**。少数类在测试集可能偏多或偏少，考题难度跟平时练习比例对不上。
- **误区 2：先把 1000 条全标准化了再切 800/200**。这叫信息泄漏（训练集偷偷用到了测试集的均值和方差）。

**⑥ 对照最终版**

- "Classes are imbalanced (70/30), so use a stratified split, e.g. 80/20:" → 类别 70/30 不平衡，所以用分层切分（例如 80/20）。
- "train 800 (560 + 240), test 200 (140 + 60)." → 训练集 800（560+240），测试集 200（140+60）。
- "Fit the model (and the scaling) on the train set only." → 模型和特征缩放只在训练集上拟合。
- "Evaluate once on the test set: confusion matrix, recall, F1 or AUC, not only accuracy." → 在测试集上只评估一次，报告混淆矩阵、召回率、$F_1$ 或 AUC，不能只看准确率。

### 3.9 How do you measure classification performance with k-fold cross-validation? 如何用 k 折交叉验证评估分类性能？ ★

考过：[2019 Q9b](../Exam_2019_zh.md)

**先懂这些：** [第二课 · 交叉验证具体做什么](../../Lectures/02_LM/06_regularization_and_validation.md)；[作业一第 4 题：数据划分](../../Exercises/Assignment1/guide/04_data_splitting.md)。

**最终版答案（背诵版 EN，≤5 行）：**
$k=5$: split into **5 stratified folds of 200 (140 + 60)**.
Each time, train on **4 folds (800)** and test on the remaining fold.
Report the **mean and standard deviation** of the 5 scores; each point is tested exactly once.
If the same CV is used for tuning, use **nested CV**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

同样还是 3.8 那 1000 个样本（类 1 有 700 个，类 2 有 300 个），如果不用单次 80/20 切分，而是改用 **$k$ 折交叉验证**，具体每一步怎么做、能解决什么痛点？

**② 需要的工具**

- **K 折交叉验证**（见 3.1）：把数据分成 $K$ 份，轮流拿 1 份当考卷、另外 $K-1$ 份做训练，重复 $K$ 次求平均。
- **分层切折（stratified folds）**（见 3.8）：切折时保证每一折里都严格保持 7:3 的类别比例。
- **嵌套交叉验证（nested CV）**：用两层套娃解决“同一个交叉验证既用来挑超参数、又拿最佳分数当最终成绩”会导致虚高（既当运动员又当裁判）的问题：
  - **外层**（负责公正评估）：留 1 折做最终测试，只在其余 $K-1$ 折里动手；
  - **内层**（负责调超参数）：只在那 $K-1$ 折内部再做一次小交叉验证挑出最佳超参数，再重新训练后去外层那一折打分。

**③ 一步一步（以经典的 $k=5$ 为例）**

1. **先分层切成 5 折**：把 700 个类 1 均分进 5 折（每折 140 个），再把 300 个类 2 均分进 5 折（每折 60 个）→ 得到 **5 折，每折正好 200 人（140＋60）**。
2. **轮流做 5 轮“训练＋考试”**：第 $j$ 轮（$j=1,\dots,5$）时，拿其余 4 折（800 人）当训练集（**标准化等预处理也只能在这 800 人上重新算**），再在留出的第 $j$ 折（200 人）上算评估指标（混淆矩阵、$F_1$、平衡准确率或 AUC，不要只看准确率）。
3. **汇总 5 个成绩**：得到 5 个测试分数后，不仅报告**平均值**，还要报告**标准差**（告诉别人模型在不同数据子集上的表现稳不稳）。
4. **为什么比单次 80/20 划分更好？** 1000 个样本里**每一个样本都恰好当过 1 次测试样本、4 次训练样本**，彻底消除了单次切分“运气好不好”的偏差，代价只是训练时间变成 5 倍。
5. **警惕常见陷阱**：如果这组 5 折已经用来挑超参数了，千万别直接把最高均值报成泛化成绩，要改用**嵌套交叉验证**（或事先另留一个完全独立的测试集）。

**④ 小例子**

假设 5 折算出来的 $F_1$ 分数分别是 `0.86, 0.88, 0.85, 0.87, 0.89`：

- 我们不仅知道平均分是 **0.87**，还能算出样本标准差约 **0.016**；
- 最终报告写成 **`0.87 ± 0.016`**——既有平均水平，又看得出模型非常稳定，比单次切分只给一个数字有说服力得多。

**⑤ 常见误区**

- **误区 1：在全部 1000 条上做一次标准化，然后再切 5 折**（依然属于信息泄漏，必须每折内部重算缩放参数）。
- **误区 2：用同一套 5 折分数既选 $\lambda$ 又充当最终测试分**，这会让成绩偏乐观。

**⑥ 对照最终版**

- "$k=5$: split into 5 stratified folds of 200 (140 + 60)." → 取 $k=5$，分层切成 5 折，每折 200（140+60）。
- "Each time, train on 4 folds (800) and test on the remaining fold." → 每轮用 4 折（800）训练，在剩下 1 折上测试。
- "Report the mean and standard deviation of the 5 scores; each point is tested exactly once." → 报告 5 个分数的均值和标准差；每个样本恰好被测试一次。
- "If the same CV is used for tuning, use nested CV." → 如果同一套 CV 还要用于调超参数，就要使用嵌套交叉验证。

---

## 4. 决策树

> 出现最稳定的主题：2019、2020、2023.3、2023.11、2024 都有概念题。画回归树的计算题见[计算题文件](00_calculations.md)。

### 4.1 What are the hyperparameters of decision trees? 决策树有哪些超参数？ ★★★★

考过：[2019 Q5](../Exam_2019_zh.md) · [2020 A3](../Exam_2020_zh.md) · [2023.11 Ex1 Q4](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex2 Q5](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① [第五课 · 基于划分的分类器（3/4）：超参数](../../Lectures/05_NLM_zh.md)；② 参数和超参数的区别（见 3.4）；③ [Lab2](../../Exercises/Lab2/Lab2_zh.ipynb) 决策树部分，试着改 `max_depth` 看边界变化。

**最终版答案（背诵版 EN，≤5 行）：**
**Hyperparameters**: **max depth**, max number of leaves, **min samples per leaf / per split**, min impurity decrease, split **criterion** (Gini, entropy, MSE), **pruning** parameter α.
**Learned parameters**: split variables, thresholds, leaf values.
Hyperparameters are chosen by **cross-validation**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

决策树有哪些需要人提前设定的**超参数**？考试时还常顺便追问（比如 2019 年）：树里哪些是人定的**超参数**，哪些是树自己从数据里**学出来的参数**？

**② 需要的工具**

- **先把决策树想成“玩 20 个问题的猜谜游戏”**（详见 4.2）：比如银行审批贷款，第一问“月收入 $\le 3000$ 吗？”，是 → 拒贷；否 → 再问第二问“负债率 $\le 40\%$ 吗？”……走到最后的末端格子（叫**叶节点**）直接读出结论。
- **人设定的规矩 ＝ 超参数（全部在控制“别把问题拆太碎”）**：
  - **最大深度 `max_depth`**：从树根到叶子最多连续问几层问题；
  - **最大叶节点数**：整棵树最多允许分成几个最终小格子；
  - **分裂最少样本数 / 叶节点最少样本数** `min_samples_split / min_samples_leaf`：一个格子里人太少（比如不到 5 个）就不准再拆，或者拆完不能出现“只有 1 个人”的孤立叶子；
  - **最小不纯度下降**：一次切分至少要让左右两边“更整齐纯洁”多少才动手，只赚芝麻就不切；
  - **分裂准则（criterion）**：用哪把尺子量“混杂程度”，分类常用 **Gini 指数**或**熵**，回归用 **MSE**（见 4.3）；
  - **剪枝参数 $\alpha$**（课件常写为 $\lambda$）：先放手长出一棵超大树，再按“训练误差 $+\,\alpha\times\text{叶子数}$”把华而不实的分枝剪掉。
  - （补充：若是随机森林，还会多出“造几棵树”和“每次随机抽几个特征来比”。）
- **树自己挑的具体数字 ＝ 学出来的参数**：每个分叉到底**挑哪个特征**来问、**分数线卡在几**（例如“月收入 $\le 3000$”里的“月收入”和“3000”），以及每个叶子最终报什么答案。

**③ 一步一步**

1. **看穿本质**：上面 6 个超参数虽然名字不同，但核心都在控制同一件事——**树的复杂度（能切多碎）**。
2. **太大 vs 太小**：
   - 限制太松（树太深、叶子太多）→ 每个叶子里只剩 1–2 个训练点，等于把练习题逐题死记硬背 → **过拟合**；
   - 限制太死（树太浅、叶子太少）→ 题目都没问明白就急着下结论 → **欠拟合**。
3. **怎么定这些超参数？** 在训练数据上用**交叉验证**挑平均验证误差最低的那组设置（见 3.1），独立测试集只在最后测一次。

**④ 小例子**

假设有 $N=100$ 个训练样本：

- **放开到 `max_depth = 7`**：一棵深度为 7 的二叉树最多可以裂出 $2^7 = 128$ 个叶子——**比总样本数还多**！树有足够容量把每个样本几乎单独切进一个小格子（除非有两个点特征一模一样但标签相反，否则训练误差几乎能降到 0），极其容易把噪声背下来。
- **改成 `min_samples_leaf = 10`**：哪怕不限深度，整棵树最多也只能分出 $100/10 = 10$ 个叶子，每个叶子的结论都要由至少 10 个样本共同投票决定，结果稳定得多。

**⑤ 常见误区**

- **误区 1：把节点上的“切分特征和切分阈值”当成超参数**。那是算法在训练中通过搜索**学出来的参数**，不是人手设的！
- **误区 2：以为 `max_depth = D` 就一定会精确生成 $2^D$ 个叶子**。$2^D$ 只是叶子个数的**上限**（如果某个分支提前全变纯了就会提前停下，而且特征完全相同的冲突点永远切不开）。

**⑥ 对照最终版**

- "Hyperparameters: max depth, max number of leaves, min samples per leaf / per split, min impurity decrease, split criterion (Gini, entropy, MSE), pruning parameter α." → 决策树的六大超参数清单。
- "Learned parameters: split variables, thresholds, leaf values." → 算法自己学出来的参数：分裂变量、阈值和叶节点预测值。
- "Hyperparameters are chosen by cross-validation." → 超参数通过交叉验证来选。

### 4.2 What is a decision tree (representation), e.g. for binary classification? 什么是决策树（表示方式），例如在二分类中？ ★★

考过：[2020 A3](../Exam_2020_zh.md) · [2024 Ex2 Q1](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** [第五课 · 局部方法 2：基于划分的方法（决策树）、基于划分的分类器（1/4）](../../Lectures/05_NLM_zh.md)；与 2.1 的"局部方法"联系起来。

**最终版答案（背诵版 EN，≤5 行）：**
A tree is a **recursive partition** of the input space.
Each internal node has a test $x_j\le s$; each **leaf** is an **axis-parallel rectangle** with a prediction.
In binary classification, the leaf gives the **majority class** (0 or 1).
It is a **piecewise-constant**, local model.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

到底什么叫“决策树”？它是怎么长成那个样子的，以及在“二分类”里它把输入空间表示成了什么形状？

**② 需要的工具**

- **切蛋糕比喻（递归划分 + 轴对齐矩形）**：把所有特征构成的输入空间想象成一块方形大蛋糕：
  - 决策树每次只选**一个特征**做“是／否”测试 $x_j\le s$（相当于只准**横平竖直地切一刀**，绝不斜着切）；
  - 切完两半后，再分别对左半块和右半块各自继续横切或竖切，层层套下去，这就叫**递归划分（recursive partition）**；
  - 这样一路切到底，最后留下的每一小块（每个**叶节点**），必然都是边与坐标轴平行的矩形（或高维超矩形，叫 **axis-parallel rectangle**）。
- **内部节点（internal node）**：树中间的分叉路口，每个节点装一个单变量测试 $x_j \le s$（“是”走左枝，“否”走右枝）。
- **叶节点（leaf）**：树最底端不再继续分的终点，对应蛋糕上切出来的一个完整矩形格子，里面记录该格子的最终预测答案。
- **分段常数（piecewise-constant）**：同一个叶节点矩形格子里，无论站在左角还是右角，输出都**一模一样**（像一片片刷了纯色油漆的地砖），这就叫分段常数函数。

**③ 一步一步（二分类树怎样表示与工作）**

1. **走流程判断**：一个新样本 $x$ 从最顶端的根节点出发，在每个内部节点回答一次 $x_j\le s$（真走左，假走右），一路掉进某个叶节点。
2. **叶节点怎么定答案（二分类）**：看在训练阶段**同时掉进这个矩形格子里的所有训练样本**，谁占多数就输出谁（**多数类** `0` 或 `1`）；也可以顺便报出正类占的比例当作风险分值。
3. **几何本质**：整棵决策树等价于把输入空间划分成互不重叠的“轴对齐矩形”地砖，每块地砖上写着一个固定的常数标签——所以它既是一个**分段常数**函数，又是一个只看本地小格子的**局部方法**（见 2.1）。

**④ 小例子**

设特征只有两个：$x_1 =$ 年龄，$x_2 =$ 月收入。一棵深度为 2 的贷款审批二分类树：

- 根节点问：**“$x_2$（收入） $\le 3000$ 吗？”**
  - **是** → 进入左节点再问：**“$x_1$（年龄） $\le 25$ 吗？”**
    - 是 → 叶子 1：格子里违约样本占多数 → 输出 **拒绝 (0)**；
    - 否 → 叶子 2：格子里按时还款样本占多数 → 输出 **批准 (1)**。
  - **否** → 直接到达叶子 3：格子里按时还款样本占多数 → 输出 **批准 (1)**。

它在二维平面上横竖两刀切出了 **3 个互不重叠的轴对齐矩形区域**：`{收入≤3000, 年龄≤25}`（0）、`{收入≤3000, 年龄>25}`（1）和 `{收入>3000}`（1）。

**⑤ 常见误区**

- **误区 1：把“二分类”和“二叉树”搞混**。“二分类”指的是标签 $y\in\{0,1\}$ 只有两类；而哪怕遇到 3 分类任务，CART 决策树依然是每个节点“分成两支（二叉树）”。
- **误区 2：以为叶子的答案是人手动填的**。叶子输出什么完全取决于“训练集中落进这个格子的点里谁占多数”。

**⑥ 对照最终版**

- "A tree is a recursive partition of the input space." → 决策树是对输入空间的递归划分。
- "Each internal node has a test $x_j\le s$; each leaf is an axis-parallel rectangle with a prediction." → 每个内部节点问一个 $x_j\le s$ 的测试；每个叶子对应一个带预测值的轴对齐矩形。
- "In binary classification, the leaf gives the majority class (0 or 1)." → 在二分类中，叶子输出多数类（0 或 1）。
- "It is a piecewise-constant, local model." → 它是一个分段常数的局部模型。

### 4.3 How is a decision tree built / trained (pseudocode)? 决策树如何构建／训练（伪代码）？ ★★

考过：[2020 A3](../Exam_2020_zh.md) · [2024 Ex2 Q3](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① [第五课 · 基于划分的分类器（2/4）：构建数据驱动的划分](../../Lectures/05_NLM_zh.md)；② 不纯度：Gini $1-\sum_c p_c^2$、熵 $-\sum_c p_c\log p_c$；③ [Lab2](../../Exercises/Lab2/Lab2_zh.ipynb)／[Lab3](../../Exercises/Lab3/Lab3_zh.ipynb)。

**最终版答案（背诵版 EN，≤5 行）：**
```text
Grow(S):
  if stop (pure, max depth, too few points, no valid split): return Leaf(majority class of S)
  choose (j, s) that maximizes the impurity decrease (Gini / entropy)
  S_L = {x in S : x_j <= s},  S_R = S \ S_L
  return Node(x_j <= s, Grow(S_L), Grow(S_R))
```
Splits are chosen **greedily** (locally optimal). Optionally **prune** with $\hat L_n(T)+\lambda|T|$.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

数据已经摆在眼前，程序到底是怎么一步步**长出一棵决策树**（训练过程）的？并且要能写出简洁的伪代码。

**② 需要的工具**

- **不纯度（impurity）$I(S)$**：用来给一个格子里“类别混杂得有多乱”打分。
  - **纯（$I=0$）**：格子里清一色全是同一类（就像一筐里全是红苹果）；
  - **最不纯（混杂度最高）**：两类五五开各占一半。
  - 常用的三把尺子：**Gini 指数** $1-\sum_c p_c^2$（$p_c$ 是第 $c$ 类在格子里的占比）、**信息熵** $-\sum_c p_c\log p_c$，以及回归树用的 **MSE**（格子里数值 $y$ 的方差）。
- **不纯度下降（信息增益 $\Delta$）**：切一刀**之前**的混杂度，减去切完后**左右两边按人数加权平均**的混杂度。下降越多，说明这一刀把两拨人分得越干净！
- **贪心（greedy）策略**：要穷举出“全球公认最好的一整棵树”属于 **NP 难**问题（树大了根本算不过来）。所以实际建树每一步只顾眼前——**先挑当前这一步让混杂度降得最多的一刀**，切完再也不回头反悔。
- **递归（recursion）**：“自己调用自己”。对整堆数据 `Grow(S)` 切出左半边 $S_L$ 和右半边 $S_R$ 后，直接对它们分别喊一声 `Grow(S_L)` 和 `Grow(S_R)`，用同一套规则接着往下切。
- **剪枝（pruning）**：先放手长出一棵过拟合大树，再按 $\hat L_n(T)+\lambda|T|$ 把不划算的分枝剪掉（见 4.10）。

**③ 一步一步（对照伪代码看建树流程）**

1. **先检查“该不该停下来”**（停止规则详见 4.9）：如果当前格子里样本全属同一类（已经纯了）、或者已经到了最大深度、或者样本太少、或者找不出任何能让两边不同的切法，就停手变成一个**叶节点**（分类输出多数类，回归输出均值）。
2. **否则，穷举所有合法的“一刀切”候选 $(j, s)$**：对每个特征 $j$，把现有样本按这个特征值从小到大排好，试试每相邻两个数中间的门槛 $s$。
3. **给每一刀打分（加权不纯度下降）**：把集合 $S$ 切成左半 $S_L=\{x_j\le s\}$ 和右半 $S_R=S\setminus S_L$，计算：
   $$\Delta = I(S) - \frac{|S_L|}{|S|}I(S_L) - \frac{|S_R|}{|S|}I(S_R)$$
   *为什么按比例加权*：防止为了分出 1 个孤立纯点而留下另一边 99 个混杂点——人多那一半的混杂度占更大权重才公平。
4. **贪心拍板**：挑出使 $\Delta$ 最大的最优切分 $(j^*, s^*)$，写进当前内部节点。
5. **左右分别递归**：把左半 $S_L$ 和右半 $S_R$ 当成两份独立的小数据集，继续分别调用 `Grow(S_L)` 和 `Grow(S_R)`，直到所有分支都停成叶子为止。
6. **（可选）后剪枝**：如果怕长过头，用代价复杂度准则 $\hat L_n(T)+\lambda|T|$（教材常记作 $R(T)+\alpha|T|$，$|T|$ 是叶子数）自底向上把收益太小的分支剪掉。

**④ 小例子（手算用 Gini 挑最好的一刀）**

某节点里有 10 个样本：**5 个 A、5 个 B**。分裂前 $\text{Gini}=1-(0.5^2+0.5^2)=0.50$。现在有两个候选切法：

- **切法 1**：切成左 `5 个 (4A, 1B)`、右 `5 个 (1A, 4B)`。
  两边占比都是 80% vs 20%，各自 $\text{Gini}=1-(0.8^2+0.2^2)=0.32$ → 加权平均 $0.5\times 0.32 + 0.5\times 0.32 = 0.32$ → 下降 $\Delta = 0.50 - 0.32 = \mathbf{0.18}$。
- **切法 2**：切成左 `8 个 (5A, 3B)`、右 `2 个 (0A, 2B)`（右边完全纯了！）。
  左边 $\text{Gini}=1-(0.625^2+0.375^2)=0.469$，右边 $\text{Gini}=0$ → 加权平均 $0.8\times 0.469 + 0.2\times 0 = 0.375$ → 下降 $\Delta = 0.50 - 0.375 = \mathbf{0.125}$。

**答案选切法 1**（0.18 > 0.125）——切法 2 虽然切出了一个全纯的小右边，但大左边依然很乱，加权算下来不如切法 1 干净。

**⑤ 常见误区**

- **误区 1：只挑“能立刻分出一个纯叶子”的切法，忘了算样本数加权**。看上面切法 2 的反例就懂了。
- **误区 2：以为贪心长出来的树一定是全局最优树**。因为每步不回头改前面的切法，只能做到局部贪心最优（求全局最优树是 NP 难的）。
- **误区 3：忘记写“没有有效分裂”的停机条件**。如果两个样本所有特征一模一样、标签却相反，不纯度永远 $>0$，没有这条停机条件就会卡住或产生空分支。

**⑥ 对照最终版**

- 伪代码 5 行 → 停机就返回多数类叶子 → 挑让不纯度下降最大的 $(j,s)$ → 按 $x_j\le s$ 分成 $S_L, S_R$ → 对左右两边递归 `Grow`。
- "Splits are chosen greedily (locally optimal). Optionally prune with $\hat L_n(T)+\lambda|T|$." → 每次切分都是贪心（局部最优）的；建好后还可以按 $\hat L_n(T)+\lambda|T|$ 剪枝防过拟合。

### 4.4 What label does a decision tree assign to a new point x? 决策树给新点 x 赋什么标签？ ★★

考过：[2020 A3](../Exam_2020_zh.md)（分类或回归时如何决策）· [2024 Ex2 Q2](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 先理解 4.2 的表示方式；对比 2.1 中 k-NN 的"局部投票"。

**最终版答案（背诵版 EN，≤5 行）：**
Send $x$ down from the root, following the tests, until it reaches a **leaf**.
Classification: the **majority class** of the training points in that leaf (the class frequency can be a score).
Regression: the **mean** of their $y$.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

决策树训练好了，现在来了一个从未见过的新样本 $x$，树到底是怎么一步步给它算出预测标签的？（2020 年原卷还顺带问了回归树怎么给新点预测。）

**② 需要的工具**

- **走迷宫直觉**：把一棵训练好的树想成一座“是／否问答关卡”——每个内部节点是一扇带判断条件 $x_j\le s$ 的岔路口，最底端是房间（**叶节点**）。任何新点 $x$ 从最顶端大门口（根节点）进来，按自己特征值一路回答“是（走左）”或“否（走右）”，最后一定会且只会掉进**唯一一个**叶子房间。
- **多数类（分类）**：看这个叶子房间里原本住着哪些训练样本，哪一类人数最多就报那一类。
- **类别频率（评分）**：算出房间里正类人数占房间总人数的比例，当作怀疑分数（score），再配合任意阈值或排序用。
- **均值（回归）**：如果预测的是连续数值 $y$，就取房间里所有训练样本 $y$ 值的**平均数**（因为从平方误差来看，一组数里使平方误差最小的常数刚好就是平均值）。

**③ 一步一步**

1. **从根节点一路往下走**：从树顶出发，在每个内部节点检查 $x_j \le s$ 是否成立，成立走左枝、不成立走右枝。
2. **落入唯一的叶节点**：走到没有分叉的末端叶节点停下（如果树深只有 5 层，哪怕训练集有 100 万条数据，预测时也最多只用做 **5 次数字比较**，速度极快！）。
3. **按任务读出叶子里的答案**：
   - **做分类**：统计落在当前叶子里的训练样本中哪个类别最多，输出该**多数类**（平局规则需提前定好）；也可以输出正类所占比例作为分数，再按误报/漏报代价调阈值；
   - **做回归**：输出落在当前叶子里的训练样本 $y$ 的**平均值**。

**④ 小例子**

- **分类例子**：新点 $x$ 一路问答掉进某个叶子，发现训练时也有 10 个点落在这个叶子里：**7 个 A 类、3 个 B 类**。
  - 直接输出分类结果：**A**（7 > 3）；
  - B 类的比例分值是 $3/10 = 0.30$。如果把 B 看成高风险病、漏诊代价极大，你完全可以把报警阈值设成 0.25，这样尽管 A 多，依然提前报警判 B。
- **回归例子**：新房子掉进某个叶子，里面有 3 套历史成交训练房，价格分别是 `200, 220, 240` 万 → 直接输出均值 **220 万**。

**⑤ 常见误区**

- **误区：以为叶子里正类占的比例 $3/10=0.3$ 一定是精准校准的真实概率**。当一个叶子只装了 3、5 个样本时，算出来的比例跳变很大（0%、33%、67%、100%），往往并不准。

**⑥ 对照最终版**

- "Send $x$ down from the root, following the tests, until it reaches a leaf." → 把 $x$ 从根节点一路按判断条件往下送，直到落入一个叶节点。
- "Classification: the majority class of the training points in that leaf (the class frequency can be a score)." → 分类：取该叶子里训练样本的多数类（类别频率也可直接当分数）。
- "Regression: the mean of their $y$." → 回归：取这些训练样本 $y$ 的平均值。

### 4.5 What are the advantages of decision trees over most other algorithms? 与大多数其他算法相比，决策树有哪些优点？ ★★

考过：[2023.3 Ex1 Q7](../DataML-CHPS-2022-examen_zh.md) · [2024 Ex2 Q7](../DataML-CHPS-2024-examen_zh.md)（pros）

**先懂这些：** [第五课 · 关于局部方法的要点：决策树的优点](../../Lectures/05_NLM_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
**Easy to interpret**: logical if–then rules (**explainable ML**). **Automatic variable selection**.
Handles **non-linearity and interactions**. **Scale changes** do not matter (invariant to monotone transforms).
Handles **missing and categorical data**, for classification and regression. Fast.
It is the base of **random forests and boosting**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

和线性回归、k-NN、SVM 这些“大多数算法”比起来，决策树凭什么特别好用、有哪些独到的优点？

**② 需要的工具**

- **可解释性（explainable ML）**：模型做完决定，人类能直接顺着它的逻辑看懂“为什么拒贷／为什么判患病”。
- **特征交互（interaction）**：一个特征的作用依赖于另一个特征（例如“只有同时满足‘年轻 **且** 收入低’才高风险”，单一特征看并不明显）。
- **单调变换不变性**：只要把某个特征按“保持大小排队顺序不变”的方式拉伸或换算（比如米换厘米、欧元换美元，甚至正数特征取对数 $\log x$），在决策树眼里谁排前面谁排后面一点没变，切法完全照旧！
- **无需标准化**：像 k-NN、SVM、带惩罚的回归对特征单位超级敏感，必须先标准化；决策树**不用**。

**③ 一步一步（记住 7 大实用优点）**

1. **天生好解释（如果……那么……规则）**：一棵不太深的树就是几条大白话逻辑规则，银行审核员或医生拿来就能用，不像神经网络是个黑盒。
2. **自动筛选变量**：每层只挑让不纯度降得最多的特征来切，完全没用的噪音特征树根本不会去问它，相当于顺手做了特征选择。
3. **自动搞定非线性和特征交互**：一层层往下分叉天然就能表达“先看年龄、再看收入”的组合逻辑，不用自己费劲构造 $x_1 x_2$、$x_1^2$ 这些二次特征。
4. **不在乎单位和单调变换（免标准化）**：切分条件 $x_j \le s$ 只关心“大小顺序”，把所有正数特征取对数或换算成任何货币单位，树的结构和预测一模一样。
5. **不挑食、全能型（分类/回归＋缺失/类别都行）**：同一套树思想既能分类也能回归；不像线性模型和 k-NN 遇到“缺失格子”或“红/绿/蓝文字类别”就得费劲编码或报错，决策树**原生就能处理缺失值和类别型数据**（课件明确强调这一点）。
6. **预测极快**：预测新样本时只需要沿着一根树枝向下走到底，做“深度”那么多次简单比较就出结果。
7. **集成学习的最强积木**：虽然单棵树有点不稳定（见 4.7），但它天生快又不挑数据，正好拿来做**随机森林**和 **Boosting** 的基础积木。

**④ 小例子**

把特征“月收入”从**欧元**全换成**美元**（假设 1 欧元＝1.1 美元）：

- 决策树：原来的分裂条件“收入 $\le 3000$ 欧元？”自动等价于“收入 $\le 3300$ 美元？”，切出来的左右两堆人**一个都不差**；
- 换成 k-NN 或 Ridge：如果不重新做标准化，收入那列数字突然整体变大 1.1 倍，距离公式或惩罚大小立刻全部失衡！

**⑤ 常见误区**

- **误区 1：以为随便哪棵树都“容易解释”**。其实只有**浅树**好读懂；长到几百个叶子的大树，或者由 500 棵树组成的随机森林，照样看不懂。
- **误区 2：背了优点忘了缺点**。考试常把“优点（pros）”和“缺点（cons）”捆在一起考，记得配合 **4.7** 一起背。

**⑥ 对照最终版**

- "Easy to interpret: logical if–then rules (explainable ML). Automatic variable selection." → 易解释（逻辑规则、可解释机器学习）；能自动挑选变量。
- "Handles non-linearity and interactions. Scale changes do not matter (invariant to monotone transforms)." → 自动处理非线性和特征交互；特征缩放／单位换算不影响（对单调变换不变）。
- "Handles missing and categorical data, for classification and regression. Fast." → 能处理缺失值和类别数据，分类回归都行，速度很快。
- "It is the base of random forests and boosting." → 它是随机森林和 Boosting 的基石。

### 4.6 A tree was trained for f. Can it be reused for f₁(5x)=f(x), f₂(x)=5f(x), f₃(x)=f(x)⁵, without retraining? 为 f 训练好的树，能否不重新训练就用于这些变换后的函数？ ★★

考过：[2021 Ex3 d–e](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex4 c](../DataML-CHPS-2022-examen_zh.md)（原问法：$3f(x)$、$f_2(3x)=f(x)$、$[f_1(x)+f_2(3x)]^2$）

**先懂这些：** ① 树是分段常数函数：阈值作用在**输入轴**，叶值作用在**输出轴**（4.2）；② 集成＝多棵树的平均（2.3）；③ 原卷参考答案中的回归树图：[2021](../DataML-CHPS-2021-examen_zh.md)、[2023.3](../DataML-CHPS-2022-examen_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
**No retraining** (if the rescaled inputs stay inside the training range). $f_1(5x)=f(x)$: **multiply the thresholds by 5**.
$f_2=5f$: **multiply the leaf values by 5**.
$f_3=f^5$: raise each **leaf value to the power 5**.
For an **ensemble**: the same for linear changes, but for $f^5$ **average first, then take the power**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

我们已经费力用数据训好了一棵近似函数 $f$ 的回归树 $T\approx f$。现在突然来了三个新函数：$f_1(5x)=f(x)$、$f_2(x)=5f(x)$、$f_3(x)=f(x)^5$，它们全是由原来的 $f$ 经过**已知变换**得到的。需要重新收集数据训练树吗？对于**树的集成（比如随机森林）**又该怎么办？

**② 需要的工具**

- **把树看成“台阶图”**：决策树是分段常数函数，每个内部节点的**阈值 $s$** 决定在**横轴（输入 $x$）**的哪里换台阶；每个叶子的**叶值**决定这一段台阶的**高度（输出 $y$）**。
- **改横轴 vs 改纵轴**：变换套在输入 $x$ 上，就只改节点里的**阈值**；变换套在输出 $f(x)$ 上，就只改叶子里的**叶值**。
- **不搞反 `multiply vs divide` 的验算秘诀**：记作新输入 $u=5x$，于是 $f_1(u)=f(u/5)$。直接代一个数验算：原来在 $x=2$ 处发生的事情，现在必须让 $u=10$ 才能让括号里 $u/5=2$，所以原来的切换点 $x=2$ 在新函数里移动到了 **$u=10$（乘以 5）**！
- **集成＝多棵树取平均**（见 2.3）：线性变换和求平均可以交换顺序；**非线性变换（如 5 次方）不能交换顺序**！
- **外推限制**：树在训练覆盖的区间外只会傻傻延续边界台阶的高度，没法自己延伸斜坡。

**③ 一步一步**

1. **先给总回答：不需要重新训练**（前提是缩放后的输入 $u/5$ 仍然落在原来训练数据的范围内，别跑到训练区间外面去“瞎外推”）。
2. **$f_1(5x)=f(x)$（输入拉伸 5 倍）**：令新自变量 $u=5x$，则 $f_1(u)=f(u/5)\approx T(u/5)$。原树节点里的条件 $u/5 \le s$ 等价于 $u \le 5s$——所以**把树里所有分裂阈值乘以 5**，叶值原封不动！
3. **$f_2(x)=5f(x)$（输出放大 5 倍）**：横轴切法不变，只把输出高度拉高 5 倍——直接**把所有叶值乘以 5**。
4. **$f_3(x)=f(x)^5$（输出取 5 次方）**：因为**单棵树**在每个叶子里都是一个单独常数，常数的 5 次方还是常数，所以只要**把每个叶子的叶值直接取 5 次方**即可。（小提醒：如果原来叶值估计有一点小误差 $\delta$，取 5 次方后误差会被放大约 $5\hat f^4\delta$ 倍。）
5. **如果换成一个“树的集成（多棵树求平均）”怎么办？**
   - 对前两种**线性变换**（阈值乘 5、叶值乘 5）：每棵树先改再平均，和先平均再改，结果完全一样（分配律成立）；
   - 对非线性变换 **$f^5$**：$(\frac1B\sum T_b)^5 \ne \frac1B\sum T_b^5$！必须**先让所有树预测再求平均，最后才把平均值取 5 次方**，绝不能对每棵树的叶子先取 5 次方再平均。
6. **2023.3 同类真题套用**：$3f(x)$ → 叶值乘 3；$f_2(3x)=f(x)$ → 阈值乘 3；$[f_1(x)+f_2(3x)]^2 = [3f(x)+f(x)]^2 = 16f(x)^2$ → 预测后先乘 4（即叶值乘 4）再平方，集成模型同样要先把各树预测加总求平均后再平方。

**④ 小例子**

假设原树 $T$ 只有两段：$x\le 2$ 时输出 $1$，$x>2$ 时输出 $3$。

- **$f_1(5x)=f(x)$**：阈值从 $2$ 乘 5 变成 **$10$**（$u\le 10$ 输出 $1$，否则输出 $3$）。代入 $u=10$ 检验：$f_1(10)=f(10/5)=f(2)=1$，完全正确！
- **$f_2=5f$**：阈值仍为 $2$，叶值从 $1,3$ 乘 5 变成 **$5, 15$**。
- **$f_3=f^5$**：阈值仍为 $2$，叶值从 $1,3$ 取 5 次方变成 **$1^5=1,\ 3^5=243$**。
- **集成模型遇到 $f^5$**：假设某点上两棵树分别预测 $1$ 和 $3$：
  - 正确做法（先平均再 5 次方）：$\big(\frac{1+3}{2}\big)^5 = 2^5 = \mathbf{32}$；
  - 错误做法（先各自 5 次方再平均）：$\frac{1^5+3^5}{2} = \frac{1+243}{2} = \mathbf{122}$（严重算错！）。

**⑤ 常见误区**

- **误区 1：看到 $f_1(5x)=f(x)$，条件反射把阈值除以 5**。切记代入一个具体数字验算（令 $5x=10\Rightarrow x=2$），立刻就知道是乘 5。
- **误区 2：对集成模型直接修改每棵树的叶值为 $y^5$ 然后求平均**。非线性的幂次必须放在“集成求平均”的**最后面**。
- **误区 3：忘了写前提条件**——只有当缩放后的输入还在原训练区间内才不用重训，出了范围树没法外推。

**⑥ 对照最终版**

- "No retraining (if the rescaled inputs stay inside the training range). $f_1(5x)=f(x)$: multiply the thresholds by 5." → 无需重训（只要缩放后输入仍在训练范围内）；$f_1(5x)=f(x)$ 把阈值乘以 5。
- "$f_2=5f$: multiply the leaf values by 5." → $f_2=5f$ 把叶值乘以 5。
- "$f_3=f^5$: raise each leaf value to the power 5." → $f_3=f^5$ 把每个叶值取 5 次方。
- "For an ensemble: the same for linear changes, but for $f^5$ average first, then take the power." → 对集成模型：线性变换做法相同，但 $f^5$ 必须先求平均再取 5 次方。

### 4.7 What are the drawbacks of decision trees? 决策树有哪些缺点？ ★

考过：[2024 Ex2 Q7](../DataML-CHPS-2024-examen_zh.md)（cons）

**先懂这些：** [第五课 · 关于局部方法的要点：主要局限](../../Lectures/05_NLM_zh.md)；配合 4.11 的二维例子。

**最终版答案（背诵版 EN，≤5 行）：**
**Extremely unstable** (high variance). **Overfits** when deep. **Greedy** training.
**Axis-parallel** boundaries only (a staircase for oblique lines).
**Piecewise-constant**: no extrapolation. Accuracy **below state-of-the-art** methods; large trees are **not interpretable**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

前面夸完决策树的优点（4.5），现在反过来问：单棵决策树有哪些明显短板（cons）？

**② 需要的工具**

- **高方差（extremely unstable）**（见 1.1）：树结构对数据极其敏感。因为后面的每一层都依赖根节点的第一刀，只要训练集中换掉一两个点导致第一刀换了特征或阈值，整棵树下面的分叉就全盘洗牌！
- **贪心训练的近视眼（greedy）**（见 4.3）：只看眼前这一刀能降多少不纯度，不会“牺牲一步换后面两步大丰收”。
- **轴对齐边界（axis-parallel）**（见 4.2）：每次只能横着切或竖着切，碰上斜线就只能拿马赛克拼出锯齿状的**阶梯（staircase）**。
- **无法外推（no extrapolation）**：只能输出训练数据范围两头叶子的常数值，出了训练范围也不会跟着趋势延长。
- **XOR（异或）陷阱**：单个特征完全看不出规律，必须两个特征一起看才行（比如“两个特征同号为 A，异号为 B”）。

**③ 一步一步（把缺点拆开看透）**

1. **极其不稳定（高方差）**：课件原话指出决策树“extremely unstable”，稍微增删几个样本，整棵树就可能面目全非。
2. **放任不管必过拟合**：不限制深度、不剪枝时，树会一路劈到几乎每个叶子里只剩 1 个点，训练误差降为 0（唯一分不开的只有特征完全一样却标签相反的冲突样本），泛化表现很差。
3. **贪心算法看不见“两步之后才有效”的结构**：碰到 XOR 这类问题时，第一步无论怎么切，不纯度都降不了，贪心算法甚至会误以为“分无可分”而提前停手。
4. **只能横平竖直切（轴对齐局限）**：面对明明一条斜线就能分开的简单问题，树却需要切无数刀拼出一道弯弯曲曲的楼梯（见 4.11 的经典反例）。
5. **分段常数导致不光滑、无法外推**：回归树画出来是一格一格的台阶，既不连续光滑，在训练区间外面也永远是一条水平死线（无法顺趋势外推）。
6. **精度不算顶尖，且大树不再可解释**：单棵决策树的预测准确率通常比不过随机森林、Boosting、SVM、神经网络等主流强算法；而一旦为了追求精度把树长深到几百个叶子，人眼根本读不过来，可解释性优点也随之消失。

**④ 小例子（两个小实验看清缺点）**

- **贪心算法的盲区（XOR 四点正方形）**：想象正方形四个角上有 4 个样本——左下 $(0,0)$ 和右上 $(1,1)$ 是 **A**，左上 $(0,1)$ 和右下 $(1,0)$ 是 **B**。无论你第一刀横切（按 $x_2$）还是竖切（按 $x_1$），切出来的左边和右边永远各是“1 个 A、1 个 B”，混杂度一丁点都没下降！贪心算法一看“下降 $=0$”，可能会直接停手；其实只要忍痛切两刀就能 100% 分对。
- **无法外推**：假如训练数据只在 $x\in[0,10]$ 之间，趋势是 $y=2x$，树在最右边那段 $[8,10]$ 的叶子输出均值 $18$。当预测 $x=50$ 时，直线会答 $100$，而树还是死板地输出 $18$。

**⑤ 常见误区**

- **误区：把“树很灵活、训练误差能到 0”误以为精度很高**。单棵树的测试精度往往明显低于集成模型（随机森林 / Boosting），通常考场要配合 **4.8（怎么克服这些缺点）** 一起复习。

**⑥ 对照最终版**

- "Extremely unstable (high variance). Overfits when deep. Greedy training." → 极其不稳定（高方差）、长深了过拟合、贪心训练。
- "Axis-parallel boundaries only (a staircase for oblique lines)." → 只有轴对齐边界（面对斜分界线只能拼成楼梯）。
- "Piecewise-constant: no extrapolation. Accuracy below state-of-the-art methods; large trees are not interpretable." → 分段常数导致不能外推；准确率低于顶尖方法；树一大就丧失可解释性。

### 4.8 Is it possible to solve the drawbacks of decision trees? 能否克服决策树的缺点？ ★

考过：[2024 Ex2 Q8](../DataML-CHPS-2024-examen_zh.md)；相关：[2021 Ex3 c、e](../DataML-CHPS-2021-examen_zh.md)（树集成如何逼近数据）

**先懂这些：** [第五课 · 集成方法 1：Bagging 与随机森林；集成方法 2：Boosting](../../Lectures/05_NLM_zh.md)；[Lab3](../../Exercises/Lab3/Lab3_zh.ipynb) 集成部分。

**最终版答案（背诵版 EN，≤5 行）：**
**Partly.** Overfitting: limit the depth, min leaf size, **pruning** (α by CV).
Variance: **bagging / random forests**. Bias: **boosting**.
Cost: we **lose interpretability** and need more computation.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

4.7 列出了一堆单棵决策树的缺点（不稳定、易过拟合、台阶锯齿、精度不够高），这些缺点有办法治好吗？治好了又会付出什么新代价？

**② 需要的工具**

- **剪枝（pruning）**（见 4.10）：限制大树别长太深、剪掉不划算的分枝。
- **集成方法：Bagging、随机森林、Boosting**（见 2.3）：把几十上百棵树绑成团队，治单棵树“又抖又偏”的毛病。
- **斜决策树（oblique trees）**：允许每个节点用多个特征的线性组合（斜线）来切，不再只死磕单个特征。

**③ 一步一步（缺点怎么治＋还剩什么尾巴）**

结论是**“部分克服（Partly）”**——精度和稳定性大幅提升，但没法做到十全十美：

1. **治“过拟合”**：设最大深度 `max_depth`、叶节点最少样本数，或者先长成大树再用交叉验证挑 $\alpha$（或 $\lambda$）做**剪枝**。
2. **治“不稳定 / 高方差”＋“大台阶锯齿”** → **Bagging 与随机森林**：
   - 用 bootstrap 重采样训很多棵深树取平均（随机森林还在每次分裂时随机抽部分特征，降低树与树之间的相似性）；
   - 每棵树的切点位置略有错开，平均之后不但**方差大降**，原本粗笨的“大台阶”也碎成密密麻麻、更贴近真实曲线的**细小平滑台阶**（2021 Ex3 考过这个现象！）。
3. **治“精度不够高 / 偏差”** → **Boosting**：让一群浅树按顺序接力，后一棵专补前面犯错样本的短板（配合调小每棵树步长、控制总棵数早停），往往能冲到表格数据的顶尖精度。
4. **治“轴对齐切斜线太笨”** → 用斜决策树（测试 $w^Tx\le s$），或者干脆换用 SVM、逻辑回归、神经网络。
5. **治完了付出的新代价（为什么只能说“部分克服”）**：
   - 原本单棵小树**“一目了然、能写成几条规则”的可解释性彻底没了**（几百棵树合在一起变成黑盒）；
   - 训练和预测的**计算量成倍暴涨**；
   - 只要底层叶子还是常数，多棵树平均出来依然**不能向训练范围外外推**。

**④ 小例子**

用 2.3 的公式感受随机森林有多稳：假设单棵深树方差 $\sigma^2=1$、树之间相关性 $\rho=0.3$，把 $B=100$ 棵树一平均，方差瞬间从 `1.0` 暴跌到 $0.3 + (1-0.3)/100 = \mathbf{0.307}$！一条本来东倒西歪的树边界，立刻变得稳健顺滑。

**⑤ 常见误区**

- **误区：答“全部缺点都能解决”**。记住考试必写 **Partly** 和 **trade-off（代价）**：你用“多棵树集成”换回了高精度和低方差，却把“可解释性”和“快”给丢掉了，而且依然不能外推。

**⑥ 对照最终版**

- "Partly. Overfitting: limit the depth, min leaf size, pruning (α by CV)." → 部分可以克服：防过拟合靠限深度、设最小叶子样本数和剪枝。
- "Variance: bagging / random forests. Bias: boosting." → 降方差用 Bagging / 随机森林；降偏差用 Boosting。
- "Cost: we lose interpretability and need more computation." → 代价是丧失可解释性，且需要更多计算量。

### 4.9 Give at least two stopping rules for training a decision tree. 至少给出两条决策树训练的停止规则。 ★

考过：[2024 Ex2 Q4](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 4.3 的伪代码中"stopping rule"那一行。

**最终版答案（背诵版 EN，≤5 行）：**
Stop when: (1) the node is **pure**; (2) the **max depth** is reached;
(3) there are too **few samples** to split; (4) no split gives enough **impurity decrease**;
(5) the **max number of leaves** is reached.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

训练（生长）一棵决策树时，总不能无限切下去吧？程序什么时候应该喊“停”、把当前节点封口变成叶节点？请至少给出两条停止规则。

**② 需要的工具**

- **为什么要设停止规则？** 如果完全不喊停，决策树会一直切到几乎每个叶子里只剩 1 个点（训练误差降成 0），彻底陷入过拟合；而且只要存在特征完全相同、标签相反的点，就可能根本找不出有效切分。
- **建树伪代码的第 1 行**（见 4.3）：每次调用 `Grow(S)` 时，**先检查是否触发停止条件**，只要满足任意一条就直接返回叶子。
- **跟超参数的对应**（见 4.1）：大部分停止规则就是你事先设定的超参数（预剪枝）。

**③ 一步一步（记住 5 条经典停止规则，考试任写 2–3 条即可）**

在当前节点，只要触发下面任意一条就停手，变成叶节点：

1. **节点已经“纯”了**（所有样本都属于同一类，不纯度 $=0$）。*为什么*：大家答案全一样，再切也不可能更纯。
2. **达到设定的最大深度 `max_depth`**。*为什么*：强行限制最多只能连问几层问题，控制树整体复杂度。
3. **当前样本太少（或切完后的新叶子人数不够）**，即样本数低于 `min_samples_split`，或任何一刀都会让某一边的样本少于 `min_samples_leaf`。*为什么*：人太少（比如 1–2 个点）时切出来的规律多半只是拟合随机噪声。
4. **找不到任何能让不纯度下降足够多的切法**（最佳增益小于阈值 `min_impurity_decrease`，包括特征全相同导致根本切不出有效左右两边）。*为什么*：切了几乎白切，不划算。
5. **叶子总数达到上限 `max_leaf_nodes`**。*为什么*：直接封顶整棵树最多划出多少个格子。

**小提醒（为什么有时不用规则 4 而改用“先长后剪”）**：规则 4 有点短视——像 4.7 讲的 XOR 问题，第一刀不纯度下降是 0，却能为第二刀彻底切开铺路。所以工程里常只留“纯了／样本太少／无合法切分”，先放手长成大树，再事后**剪枝**（见 4.10）。

**④ 小例子**

假设设定超参数 **`min_samples_leaf = 5`**（每片叶子至少 5 人）。某个节点现在还剩 **8 个训练样本**——因为 $8$ 不管怎么分成两份（比如 $4+4$、$3+5$、$2+6$），**必然有一边少于 5 个**，于是立刻触发停止规则，不再往下切，直接封成叶节点！

**⑤ 常见误区**

- **误区：答“树自己学完／分完就停”**——这没有给出任何可执行的停止规则，考试一定要写清具体指标（节点已纯、最大深度、最少样本数、最小不纯度下降、最大叶子数中的至少两条）。

**⑥ 对照最终版**

- "Stop when: (1) the node is pure; (2) the max depth is reached;" → 停止条件 1（节点已纯）与 2（达到最大深度）。
- "(3) there are too few samples to split; (4) no split gives enough impurity decrease;" → 停止条件 3（样本太少）与 4（不纯度下降不足）。
- "(5) the max number of leaves is reached." → 停止条件 5（达到最大叶节点数）。

### 4.10 Is it possible to monitor the number of cells of the tree using the training data? 能否用训练数据控制树的单元（叶）数量？ ★

考过：[2024 Ex2 Q6](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 代价复杂度剪枝 $R(T)+\alpha|T|$；② 训练误差为什么偏好大树（1.3）。

**最终版答案（背诵版 EN，≤5 行）：**
**Yes**: set a **max number of leaves**, a max depth ($\le2^D$ leaves) or a min leaf size, or **prune** with the penalized criterion $\hat L_n(h_c)+\lambda|c|$ ($|c|$ = number of cells).
But the **training error alone cannot choose** the number of leaves (it always prefers more).
So choose it by **validation / CV**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

考题专门卡在“**用训练数据**（using the training data）”这几个字上：我们能不能靠训练数据来控制／调节决策树切出来的格子（单元 / 叶子）数量？哪些事能靠训练数据办到，哪些事绝对不能全靠它？

**② 需要的工具**

- **单元 / 格子（cell）＝ 叶节点（leaf）**：树把输入空间切成的每一块矩形就是一个单元，总单元数 $|c|$ 就是叶子数。
- **代价复杂度剪枝 $\hat L_n(h_c)+\lambda|c|$**（教材也常写作 $R_{\text{train}}(T)+\alpha|T|$）：
  - $\hat L_n(h_c)$ 是某棵剪枝后的子树 $h_c$ 在**训练集上的错误率**；
  - $|c|$ 是这棵子树的叶子（格子）数；
  - $\lambda$（即 $\alpha$）是“**每多留一片叶子要交的罚款**”。这其实又回到了 1.4 讲的通用公式：训练误差＋$\lambda\times$复杂度惩罚！
- **验证集 / 交叉验证**（见 3.1）：模拟考卷，用来决定 $\lambda$ 或叶子数上限到底设多少最合适。

**③ 一步一步（把“能靠训练数据做的”和“不能靠它的”分清）**

1. **可以控制叶子数（怎么控？）**：
   - **长的时候直接拦住（预剪枝）**：设最大叶子数、设最大深度 $D$（把叶子数卡在 $\le 2^D$）、或设叶节点最少样本数；
   - **长完之后按公式剪枝（后剪枝）**：对一个给定的 $\lambda$，在**训练数据**上挑出让 $\hat L_n(h_c)+\lambda|c|$ 最小的子树。$\lambda$ 越大，每多一片叶子越心疼，留下的叶子越少。
2. **训练数据在这里起什么作用？** 负责划分格子，以及提供拟合项 $\hat L_n(h_c)$ 来参与剪枝打分。
3. **关键转折：光靠训练误差本身，绝对选不出最佳叶子数！** 如果把惩罚关掉（只看训练误差 $\hat L_n$），叶子越多、训练误差一定越小（一直降到 0 为止），训练数据永远只会鼓动你“再多切几刀”，导致严重过拟合。
4. **最终谁来拍板留几片叶子？** 必须靠**验证集或交叉验证**来选最佳叶子数（或最佳惩罚力度 $\lambda$）。

**④ 小例子**

在训练集上比较两棵树：大树有 **8** 片叶子、训练错误率 `0.05`；剪掉小枝后的小树有 **3** 片叶子、训练错误率 `0.10`。套用剪枝总分 $\hat L_n(h_c)+\lambda|c|$：

- **如果设 $\lambda = 0.02$**（每片叶子罚得较狠）：
  - 大树总分 $= 0.05 + 8\times 0.02 = 0.21$；
  - 小树总分 $= 0.10 + 3\times 0.02 = \mathbf{0.16}$（更低，**胜出！保留 3 片叶子**）。
- **如果设 $\lambda = 0.005$**（每片叶子罚得很轻）：
  - 大树总分 $= 0.05 + 8\times 0.005 = \mathbf{0.09}$（更低，**胜出！保留 8 片叶子**）；
  - 小树总分 $= 0.10 + 3\times 0.005 = 0.115$。

你看，给定 $\lambda$ 后在**训练集**上就能自动挑出对应那棵子树，但 **$\lambda$ 到底该取 `0.02` 还是 `0.005`**（也就是到底留 3 叶还是 8 叶），训练数据自己定不了，必须去**验证集**上考一考才知道！

**⑤ 常见误区**

- **误区 1：以为最大深度 $D$ 就是叶子数**。其实 $2^D$ 只是叶子数的上限，树不一定会把每条枝都劈满。
- **误区 2：以为光看训练数据就能把“最佳叶子数”自动选出来**。记住必须加“不能只靠训练误差选，还要靠验证集／CV 选”这一句！

**⑥ 对照最终版**

- "Yes: set a max number of leaves, a max depth ($\le2^D$ leaves) or a min leaf size, or prune with the penalized criterion $\hat L_n(h_c)+\lambda|c|$ ($|c|$ = number of cells)." → 可以控制：限制最大叶子数、最大深度、最小叶子样本数，或用惩罚准则 $\hat L_n(h_c)+\lambda|c|$ 剪枝（$|c|$ 即格子数）。
- "But the training error alone cannot choose the number of leaves (it always prefers more)." → 但光靠训练误差选不出最佳叶子数（它永远偏爱更多叶子）。
- "So choose it by validation / CV." → 所以最后要靠验证集／交叉验证来选。

### 4.11 Give a 2D example where the classes are separable but a tree is not efficient. 给出一个二维例子：类别可分，但决策树效率不高。 ★

考过：[2019 Q5](../Exam_2019_zh.md)（示意图：[2019_diagonal_tree.png](../Answers/2019_diagonal_tree.png)）

**先懂这些：** 树的每次分裂只能平行于坐标轴（4.2）。

**最终版答案（背诵版 EN，≤5 行）：**
Two classes separated by the **diagonal** $x_2=x_1$: they are linearly separable.
But a tree only makes **axis-parallel splits**, so it needs a **staircase** of many splits.
The tree becomes deep and **overfits**. A linear model, or the feature $x_2-x_1$, solves it.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

自己构造一个简单的二维分类例子：两类数据明明很容易分开，但换决策树来分却特别笨重、效率极低。

**② 需要的工具**

- **线性可分**：能用**一条斜直线**（比如逻辑回归或线性 SVM）一刀把两类完全切干净。
- **轴对齐分裂**（见 4.2）：标准决策树每次只能画**水平线**（$x_2\le s$）或**竖直线**（$x_1\le s$），绝不准画斜线。

**③ 一步一步**

1. **构造最简单的斜线可分例子**：在平面正方形 $[0,1]^2$ 里，沿着 45° 对角线 $x_2 = x_1$ 把数据一分为二——**对角线上方（$x_2 > x_1$）全是类 1，对角线下方（$x_2 < x_1$）全是类 2**（更直观的如示意图 [2019_diagonal_tree.png](../Answers/2019_diagonal_tree.png)）。
2. **线性模型秒杀**：逻辑回归、线性 SVM 甚至感知机，只需要一条线 $x_2 - x_1 = 0$（一两个参数、1 次判断）就能 100% 完美分开。
3. **决策树为什么卡住？** 因为树只能横平竖直地切，面对 45° 斜线，就像只能拿方形乐高积木去拼一条斜边——**必须切出密密麻麻的“锯齿状楼梯（staircase）”**才能勉强贴近这条斜线！
4. **后果**：想减少对角线附近的错分点，就得不断加深树深、堆出一大堆小叶子 → 树变得又深又臃肿、失去可解释性，还非常容易顺着采样位置**过拟合**。
5. **怎么破局？** 只要人工造一个差值特征 $z = x_2 - x_1$，树只需问一句“$z > 0$？”一刀搞定；或者用斜决策树，或者直接换线性模型。

（其他同道理的反例：同心圆、或者任何斜着旋转了一个角度的分界面。）

**④ 小例子**

看一眼深度为 2 的树在 $[0,1]^2$ 对角线数据集上有多狼狈：

- 第一刀竖切 $x_1 \le 0.5$：左半边大半在斜线上方、右半边大半在斜线下方，其实还有大量混在一起；
- 第二刀左边横切 $x_2 \le 0.25$、右边横切 $x_2 \le 0.75$：总共切了 4 个长方形，沿着斜线中间依然一大片区域分错（约 12.5% 面积分错！）；
- 想把错误降到 1% 以下，需要几十上百个小矩形拼成长长一串锯齿楼梯——而一条直线 $x_2 - x_1 = 0$ 从头到尾零错误。

**⑤ 常见误区**

- **误区：举了一个两类混在一起、任何模型都分不开的例子**（例如两团完全重叠的高斯分布）。题目明确要求“类别可分（separable）”，必须保证存在一条清晰分界线能把两类分开。

**⑥ 对照最终版**

- "Two classes separated by the diagonal $x_2=x_1$: they are linearly separable." → 例子：被对角线 $x_2=x_1$ 分开的两类，它们本身是线性可分的。
- "But a tree only makes axis-parallel splits, so it needs a staircase of many splits." → 但树只能做轴对齐切分，所以需要切很多刀拼出楼梯。
- "The tree becomes deep and overfits. A linear model, or the feature $x_2-x_1$, solves it." → 树会变深并过拟合；改用线性模型或加上特征 $x_2-x_1$ 就能轻松解决。

---

## 5. 线性模型、OLS 与逻辑回归

> OLS 的数值计算（4 个点求直线和 RMSE）每年都考，见[计算题文件](00_calculations.md)。

### 5.1 Describe the logistic regression model. 描述逻辑回归模型。 ★★★

考过：[2019 Q4](../Exam_2019_zh.md) · [2020 A2](../Exam_2020_zh.md) · [2021 Ex1 Q3](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** ① 分类数据的概率模型、后验概率 $P(Y=1\mid X=x)$——[第三课 · 分类数据的概率模型](../../Lectures/03_LMC_zh.md)；② 线性逻辑回归及其拟合——[第三课 · 方法 3：线性逻辑回归](../../Lectures/03_LMC_zh.md)；③ [Lab1](../../Exercises/Lab1/Lab1_zh.ipynb) 逻辑回归部分。

**最终版答案（背诵版 EN，≤5 行）：**
For $Y\in\{0,1\}$: $P(Y=1\mid x)=\sigma(w^Tx+b)=\frac1{1+e^{-(w^Tx+b)}}$, i.e. the **log-odds is linear**.
$(w,b)$ are estimated by **maximum likelihood**: minimize the **cross-entropy** (convex; Newton or gradient descent).
A penalty can be added. It is a **discriminative** model.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

完整描述**逻辑回归（Logistic Regression）**这个模型：它的数学公式长什么样？参数怎么从数据里学？名字里带着“回归”，为什么干的却是**分类**的活？

**② 需要的工具**

- **为什么要套一个 S 形函数（sigmoid）？** 直接拿线性得分 $z = w^Tx+b$ 当概率不行——$z$ 可能算出 `-5` 或 `+100`，根本不是 $0\sim 1$ 的合法概率。于是套上 **sigmoid 函数** $\sigma(z)=\frac{1}{1+e^{-z}}$，就像一个“压缩机”，把从 $-\infty$ 到 $+\infty$ 的任何实数平滑压进 **$(0,1)$** 之间，直接当作后验概率 $P(Y=1\mid x)$ 来读。
- **几率（odds）与对数几率（log-odds）**：几率＝“发生概率除以不发生概率” $p/(1-p)$（例如 $p=0.8$ 时几率是 $0.8/0.2 = 4$，即“4 比 1”）。取对数得到 $\log\frac{p}{1-p}$。而 $\sigma(z)$ 正好是它的反函数，所以 $p=\sigma(w^Tx+b)$ **等价于**假设**对数几率是特征的线性函数**：$\log\frac{p}{1-p}=w^Tx+b$——这也是它名字叫“（对数几率）回归”的原因！
- **极大似然估计（MLE）**：挑一组 $(w,b)$，让“训练集里真实发生过的那串 0/1 标签”在模型眼里出现的总概率**最大**。
- **交叉熵损失（log-loss）**：$-[y\ln p+(1-y)\ln(1-p)]$。把极大似然取个负对数，就完全等价于最小化全体样本的平均交叉熵——猜得越“**自信地错**”，罚款呈对数爆炸。
- **凸函数**：只有一个大碗底，用梯度下降或牛顿法都能稳稳走到全局最低点（见 2.5）。
- **判别式模型（discriminative）**：不管特征 $X$ 本身是怎么分布生成的，直接一门心思建模边界概率 $P(Y\mid X)$（对比生成式模型如 LDA / 朴素贝叶斯要先学 $P(X\mid Y)$）。

**③ 一步一步**

1. **算线性打分**：对特征加权求和 $z = w^Tx+b$。
2. **压成概率**：送进 sigmoid 函数得到预测概率 $p(x) = P(Y=1\mid x) = \sigma(w^Tx+b)$；当 $w^Tx+b = 0$ 时刚好给出 $p=0.5$（决策分界线是一个超平面）。
3. **训练学参数**：用**极大似然**估计 $(w,b)$，即最小化所有样本的**交叉熵损失**。
4. **怎么求解？** 交叉熵目标对 $(w,b)$ 是光滑**凸函数**（没有假局部极小），虽然不像 OLS 那样能直接写出闭式矩阵公式，但用**牛顿法（IRLS）**或**梯度下降**都能高效求到全局最优。
5. **什么时候要加惩罚项？** 当两类数据恰好**线性可分**或特征维数很高时，把权重 $(w,b)$ 成倍放大能让交叉熵无限逼近 0、参数会一路飙向无穷大；此时加上 $\ell_2$ 或 $\ell_1$ 正则化惩罚就能把参数稳住（变成**严格凸**，解唯一）。
6. **模型如何解读？** $x_j$ 每增加 1 个单位，事件发生的几率就乘以 $e^{w_j}$ 倍（几率比）。

**④ 小例子**

- **感受 sigmoid 压缩机**：$\sigma(-2)=0.119$，$\sigma(0)=0.500$（分界点），$\sigma(2)=0.881$，$\sigma(4)=0.982$。
- **具体代个数**：设 $w=1.5,\,b=-3$。当 $x=2$ 时，$z=1.5\times 2 - 3 = 0 \Rightarrow p=\sigma(0)=0.5$；当 $x=3$ 时，$z=1.5 \Rightarrow p=\sigma(1.5)=0.818$（并且 $x$ 多 1，几率刚好乘 $e^{1.5}\approx 4.48$ 倍）。
- **感受交叉熵的狠罚**：真实标签 $y=1$ 时，若模型给 $p=0.9$，罚 $-\ln(0.9)=0.105$；若模型自信满满只给 $p=0.1$，罚 $-\ln(0.1)=2.303$（整整罚重 22 倍！）。

**⑤ 常见误区**

- **误区 1：以为逻辑回归输出的 $p(x)$ 一定等于校准准确的真实概率**。高维、过拟合或模型设定有偏时，$p(x)$ 可以排对顺序（AUC 很高），但概率数字本身不一定校准良好！
- **误区 2：以为逻辑回归能直接画出曲线分界**。它的决策边界 $w^Tx+b=0$ 是一条**平直超平面**；想要弯边界必须先手工加多项式特征（或用核）。
- **误区 3：看到“回归”二字就以为它用来预测连续数值**。它做的是**分类**（只是内部用线性回归去拟合 log-odds）。

**⑥ 对照最终版**

- "For $Y\in\{0,1\}$: $P(Y=1\mid x)=\sigma(w^Tx+b)=\frac1{1+e^{-(w^Tx+b)}}$, i.e. the log-odds is linear." → 二分类下用 sigmoid 把 $w^Tx+b$ 变成概率，即对数几率是线性的。
- "$(w,b)$ are estimated by maximum likelihood: minimize the cross-entropy (convex; Newton or gradient descent)." → 参数由极大似然估计，等价于最小化交叉熵（凸问题，可用牛顿法或梯度下降求解）。
- "A penalty can be added. It is a discriminative model." → 可以加惩罚项防止过拟合／发散；它属于判别式模型。

### 5.2 What decisions / uses does logistic regression allow (classification, scoring, other problems)? 逻辑回归能支持哪些决策／用途？ ★★★

考过：[2019 Q3](../Exam_2019_zh.md) · [2020 A2](../Exam_2020_zh.md)（两种用途）· [2021 Ex1 Q3](../DataML-CHPS-2021-examen_zh.md)（还能用于哪类学习问题）

**先懂这些：** [第三课 · 这些数据可以支持哪些决策？（1. 分类 2. 评分 4. 从分类到评分）](../../Lectures/03_LMC_zh.md)；与 9.2（分类数据 vs 分类问题）一起复习。

**最终版答案（背诵版 EN，≤5 行）：**
It gives a probability $p(x)$, so it allows:
(1) **classification**: $\hat y=1$ if $p(x)\ge t$ ($t=0.5$, or chosen from the costs);
(2) **scoring / ranking**: sort individuals by risk (credit, medicine), evaluated by **ROC / AUC**;
(3) **probability estimation**, e.g. send uncertain cases to an expert.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

逻辑回归算出来不是直接的“0 或 1”，而是一个 $0$ 到 $1$ 之间的数 $p(x)$。手里有了这个数，在实际业务里能支撑哪几种完全不同的决策／用途？（2019 问“能做哪些决策”，2020 问“两种用途”，2021 问“除了分类，还能用于哪类学习问题”。）

**② 需要的工具**

- **硬分类决策 + 阈值 $t$**：画一条门槛线 $t$，$p(x)\ge t$ 才判 1，否则判 0。
- **评分 / 排序（scoring / ranking）**：干脆不急着“一刀切死”，直接拿 $p(x)$ 当风险分从高到低排队——排在最前面的人优先人工复查或优先投放资源（例如信用卡反欺诈、精准营销）。
- **ROC / AUC**（见 3.5、3.6）：专门用来评价“排的队准不准”的指标。
- **代价不对称与拒判区间**：漏抓一个恶性肿瘤病人 vs 多叫一个健康人复查，代价天差地别；对模棱两可的中间地带（比如 $p(x)\in[0.4, 0.7]$），机器最好别瞎猜，直接交给人类专家。

**③ 一步一步（同一模型支持的三种用途）**

1. **用途一：分类（Classification）**。设定阈值 $t$：如果 $p(x)\ge t$ 判为 1，否则判为 0。当概率校准较好且误报漏报代价相等时，默认用 $t=0.5$；如果漏报代价极大（比如重病筛查），就把 $t$ 调低（如 $0.2$），宁可多复查几个也别放过病人；如果误报代价极大（比如直接封禁账户），就把 $t$ 调高（如 $0.9$）。
2. **用途二：评分 / 排序（Scoring / Ranking）**。哪怕 $p(x)$ 绝对数值校准不够完美，只要风险高的人算出的 $p(x)$ 排在风险低的人前面，就可以直接拿 $p(x)$ 从高到低**排序**。这在资源有限时特别有用（比如医院每天只能抽查 20 个高危病人、银行优先排查前 1% 高风险交易），评价标准改用 **ROC / AUC**。
3. **用途三：概率估计与不确定性分流（Probability estimation）**。直接把风险概率交给决策者参考，或者设置**不确定拒判区间 $[t_1,t_2]$**：把握很大时（$\ge 0.7$ 或 $\le 0.4$）自动放行/拦截，卡在中间吃不准的案例转给人类专家审核。

（所以同一个逻辑回归模型，既能解决**分类问题**，也能解决**评分问题**——两类问题的区别详见 9.2。）

**④ 小例子**

4 位体检者的患病概率依次是 **`0.90`、`0.60`、`0.30`、`0.05`**：

- **按分类看（默认 $t=0.5$）**：前 2 人（0.90, 0.60）判阳性；
- **按筛查分类看（调低阈值 $t=0.2$，宁错杀不放过）**：前 3 人（0.90, 0.60, 0.30）都判阳性复查；
- **按评分排序看**：今天只有 1 个加急复查名额，直接给排第一的 `0.90`；明天有名额再按 `0.90 > 0.60 > 0.30 > 0.05` 依次叫号；
- **按概率＋专家复核看（拒判区间 $[0.4, 0.7]$）**：`0.90` 自动确诊、`0.30 / 0.05` 自动阴性，只有卡在中间模棱两可的 **`0.60`** 转给主任医师重点会诊。

**⑤ 常见误区**

- **误区 1：以为逻辑回归的分类阈值死规定就是 `0.5`**。阈值完全取决于实际错判代价和概率是否校准。
- **误区 2：把“分类”和“评分”混成同一个问题**。分类只管在特定阈值下判 0/1，看错误率、召回率、$F_1$；评分管全体排队顺序，看 ROC / AUC。

**⑥ 对照最终版**

- "It gives a probability $p(x)$, so it allows:" → 因为输出概率 $p(x)$，它支持三类用途：
- "(1) classification: $\hat y=1$ if $p(x)\ge t$ ($t=0.5$, or chosen from the costs);" → （1）分类：高于阈值 $t$ 判 1（默认 0.5 或按错判代价选）。
- "(2) scoring / ranking: sort individuals by risk (credit, medicine), evaluated by ROC / AUC;" → （2）评分／排序：按风险高低排序（信贷、医疗），用 ROC／AUC 评估。
- "(3) probability estimation, e.g. send uncertain cases to an expert." → （3）概率估计：例如把拿不准的样本送交专家处理。

### 5.3 Explain how Ordinary Least Squares (OLS) fits a line / a linear model. 说明 OLS 如何拟合直线／线性模型。 ★★★

考过：[2021 Ex2 a](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex2 a](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex4 a](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① 最小二乘估计与投影的几何意义、两种证明——[第二课 · 线性模型与最小二乘](../../Lectures/02_LM/01_linear_models_and_least_squares.md)；② [Lab1](../../Exercises/Lab1/Lab1_zh.ipynb) 线性回归部分；③ 务必自己手算一遍某年的 4 点例子。

**最终版答案（背诵版 EN，≤5 行）：**
Line $\hat y=\beta_0+\beta_1x$. OLS minimizes $\text{RSS}=\sum_i(y_i-\beta_0-\beta_1x_i)^2$.
Setting the derivatives to 0: $\hat\beta_1=\frac{\sum(x_i-\bar x)(y_i-\bar y)}{\sum(x_i-\bar x)^2}$, $\hat\beta_0=\bar y-\hat\beta_1\bar x$.
Matrix form: $\hat\beta=(X^TX)^{-1}X^Ty$. Error: $\text{RMSE}=\sqrt{\text{RSS}/N}$.
OLS is **sensitive to outliers**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

普通最小二乘法（Ordinary Least Squares，简称 **OLS**）是怎么从一群散点里，算出一条“最贴合”的直线（或多元线性模型）的？考试通常要求写出**优化准则、求导推导、最终公式（含矩阵形式）和误差评价**。

**② 需要的工具**

- **线性模型**：二维下画一条直线 $\hat y = \beta_0 + \beta_1 x$（$\beta_0$ 是截距，$\beta_1$ 是斜率）。
- **竖直残差 $e_i = y_i - \hat y_i$**：真实值减去直线预测值。注意这是点到直线**竖直方向（$y$ 轴方向）**的差距——因为我们要用 $x$ 猜 $y$，所以只关心 $y$ 猜偏了多少，而不是画垂直线！
- **残差平方和 $\text{RSS} = \sum_{i=1}^N e_i^2$**：把所有点的竖直误差平方加起来。*为什么非要“平方”？*
  1. 正误差和负误差不会互相抵消；
  2. 错得越多罚得越重；
  3. 平方函数处处光滑可导，能直接用中学求导数算出闭式公式；
  4. 如果噪声服从正态（高斯）分布，最小化 RSS 刚好等价于极大似然估计。
- **求最小值秘诀（偏导数＝0）**：碗状二次函数的最低点一定是平的（切线斜率为 0），所以分别对 $\beta_0$ 和 $\beta_1$ 求偏导并令它们等于 0，就找到唯一最优直线。
- **中心化统计量**：$S_{xx}=\sum(x_i-\bar x)^2$ 衡量 $x$ 的分散度，$S_{xy}=\sum(x_i-\bar x)(y_i-\bar y)$ 衡量 $x$ 与 $y$ 是否同向变化（协方差分子）。
- **均方根误差 $\text{RMSE} = \sqrt{\text{RSS}/N}$**：把总平方误差除以样本数再开根号，变回和 $y$ 相同的单位，直观表示“平均每个点大概预测偏了多少”。

**③ 一步一步（推导一遍，自己手算就能记住）**

1. **列目标函数**：找一组 $(\beta_0,\beta_1)$，让 $\text{RSS}(\beta_0,\beta_1) = \sum_{i=1}^N (y_i - \beta_0 - \beta_1 x_i)^2$ 最小。
2. **先对截距 $\beta_0$ 求偏导令为 0**：
   $-2\sum_{i=1}^N(y_i-\beta_0-\beta_1 x_i)=0 \implies \hat\beta_0 = \bar y - \hat\beta_1\bar x$。
   *几何意义*：算完截距后，带截距的 OLS 最优直线**必定穿过所有样本的重心 $(\bar x,\bar y)$**，且所有残差之和必然等于 0（$\sum e_i=0$，考场可拿来验算！）。
3. **代回后对斜率 $\beta_1$ 求偏导令为 0**：
   $$\hat\beta_1 = \frac{\sum_{i=1}^N (x_i-\bar x)(y_i-\bar y)}{\sum_{i=1}^N (x_i-\bar x)^2} = \frac{S_{xy}}{S_{xx}}$$
   斜率就是“协方差／方差”。
4. **推广到多个特征（矩阵形式）**：把截距用的全 1 列和所有特征拼成矩阵 $X$，目标写成最小化 $\|y - X\beta\|_2^2$。令梯度为 0 得到**正规方程** $X^TX\hat\beta = X^Ty$；当 $X$ 列满秩（$X^TX$ 可逆）时，直接解出：
   $$\hat\beta = (X^TX)^{-1}X^Ty$$
   *几何投影理解*：把所有 $y_i$ 看成 $N$ 维空间的一支箭头，OLS 就是找一个最靠近 $y$ 的影子 $X\hat\beta$——从高空垂直照下来做**正交投影**，使得残差向量 $y-X\hat\beta$ 垂直于 $X$ 的每一列。
5. **汇报拟合误差**：算出各点残差 $e_i$，给出 $\text{RMSE}=\sqrt{\text{RSS}/N}$。

**④ 小例子（手算验证每一步）**

3 个点 $(0,1),\,(1,2),\,(2,4)$：

1. **均值**：$\bar x=(0+1+2)/3=1$，$\bar y=(1+2+4)/3=7/3\approx 2.333$。
2. **$S_{xx}$ 与 $S_{xy}$**：
   $x-\bar x$ 为 $-1, 0, 1$；$y-\bar y$ 为 $-4/3, -1/3, 5/3$。
   $S_{xx}=(-1)^2+0^2+1^2=2$；$S_{xy}=(-1)(-4/3)+0+(1)(5/3)=3$。
3. **直线参数**：斜率 $\hat\beta_1 = 3/2 = \mathbf{1.5}$，截距 $\hat\beta_0 = 7/3 - 1.5\times 1 = 5/6 \approx \mathbf{0.833}$。
4. **残差与验算**：预测 $\hat y$ 为 $0.833,\ 2.333,\ 3.833$；残差 $e_i = y_i-\hat y_i$ 为 $+0.167,\ -0.333,\ +0.167$，三者相加正好 $=0$（验算通过！）。
5. **误差**：$\text{RSS}=1/6\approx 0.1667$，$\text{RMSE}=\sqrt{0.1667/3}\approx \mathbf{0.2357}$。

考试每年必考的 4 点手算大表与模板，详见 [计算题 C1](00_calculations.md)。

**⑤ 常见误区**

- **误区 1：以为 OLS 最小化的是点到直线的垂直距离**。不对，最小化的是**竖直方向**的误差平方和。
- **误区 2：以为 OLS 很稳健**。因为要平方，哪怕混进 1 个离群点（outlier），平方误差也会爆炸并把整条直线拽歪——OLS **对离群点非常敏感**（这也是后来学 RANSAC 的原因，见 8.1）。
- **误区 3：以为这里的 RMSE 就是测试误差**。这是在训练集上算的拟合 RMSE，不是泛化误差。
- **误区 4：当特征数 $d > N$ 时直接套 $(X^TX)^{-1}$**。此时 $X^TX$ 根本不可逆（见 5.7）。

**⑥ 对照最终版**

- "Line $\hat y=\beta_0+\beta_1x$. OLS minimizes $\text{RSS}=\sum_i(y_i-\beta_0-\beta_1x_i)^2$." → 直线形式与最小化残差平方和准则。
- "Setting the derivatives to 0: $\hat\beta_1=\frac{\sum(x_i-\bar x)(y_i-\bar y)}{\sum(x_i-\bar x)^2}$, $\hat\beta_0=\bar y-\hat\beta_1\bar x$." → 求偏导得出的斜率和截距闭式解。
- "Matrix form: $\hat\beta=(X^TX)^{-1}X^Ty$. Error: $\text{RMSE}=\sqrt{\text{RSS}/N}$." → 多维矩阵解与 RMSE 误差公式。
- "OLS is sensitive to outliers." → OLS 对离群点很敏感。

### 5.4 How do you use logistic regression for a classification problem? 如何把逻辑回归用于分类问题？ ★★

考过：[2019 Q4](../Exam_2019_zh.md) · [2021 Ex1 Q3](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** 先理解 5.1；[第三课 · 二分类问题的理论框架、Bayes 分类器](../../Lectures/03_LMC_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **Fit** $(w,b)$ on the training data by maximum likelihood.
(2) For a new $x$, compute $p(x)=\sigma(w^Tx+b)$.
(3) Predict 1 if $p(x)\ge t$. With $t=0.5$ this is $w^Tx+b\ge0$: a **linear boundary**.
(4) **Evaluate** on test data (confusion matrix, AUC).

**解析版（小白也能看懂）：**

**① 这道题在问什么**

已经认识了逻辑回归的模型公式（见 5.1），现在问的是**实战操作流程**：从拿到一份分类数据集开始，怎么一步步用逻辑回归做出“是／否”预测并评估好坏？

**② 需要的工具**

- **逻辑回归的概率输出**（见 5.1）：$p(x) = \sigma(w^Tx+b) = \frac{1}{1+e^{-(w^Tx+b)}}$。
- **决策阈值 $t$**（见 5.2）：拿来拍板的门槛线（常用 $0.5$，也可以按误报/漏报代价调高或调低）。
- **为什么是“线性分类器”？** 因为 $\sigma(0)=0.5$ 且 $\sigma(z)$ 单调递增，所以 **$p(x)\ge 0.5$ 完全等价于 $w^Tx+b \ge 0$**（分界线就是二维的一条直线、高维的一个平直超平面；哪怕换成别的阈值 $t$，也只是等价于把截距平移成 $w^Tx+b \ge \ln\frac{t}{1-t}$，依然是一条平直超平面！）。
- **多分类扩展（softmax / 一对多）**：超过两个类别时，用 softmax 把 $K$ 个类别各自的线性打分转成和为 1 的 $K$ 个概率。

**③ 一步一步（四步完整流程）**

1. **第一步（训练拟合）**：在**训练集**上用极大似然估计（最小化交叉熵）算出 $(w, b)$；如果特征多或担心过拟合，加上 $\ell_2$/$\ell_1$ 正则化惩罚（惩罚强度 $\lambda$ 在验证集／CV 上选）。
2. **第二步（预测打分）**：对没见过的新样本 $x$，先算线性打分再套 sigmoid，得出后验概率 $p(x) = \sigma(w^Tx+b)$。
3. **第三步（设阈值下分类结论）**：定好阈值 $t$（默认 $0.5$，或根据业务代价／ROC 曲线挑选）：若 $p(x)\ge t$ 判为 `1`，否则判为 `0`。因为 $t=0.5$ 时分界面为 $w^Tx+b=0$，所以它给出的是**线性边界**。
4. **第四步（独立评估）**：在从未参与训练和调参的**测试集**上评估分类效果（看混淆矩阵、召回率 / 精确率 / $F_1$、以及 ROC-AUC）。

（如果要做弯弯曲曲的非线性分界线，需先给输入手工构造多项式特征或使用核技巧。）

**④ 小例子**

假设一维训练集学出了参数 $w=1.5,\ b=-3$（即线性打分 $z=1.5x-3$）：

- **选默认阈值 $t=0.5$**：令 $1.5x-3 \ge 0 \implies$ 分界点在 **$x=2$**。所有 $x \ge 2$ 判为 `1`，$x < 2$ 判为 `0`；
- **把门槛抬高到 $t=0.818$**（减少误报）：因为 $\sigma(1.5)=0.818$，于是变成要求 $1.5x-3 \ge 1.5 \implies$ 分界点平移到 **$x=3$**——门槛收紧了，误报减少，但可能漏掉 $x\in[2,3)$ 的正类。

**⑤ 常见误区**

- **误区 1：把阈值 $t$ 当成算法学出来的参数**。$t$ 不是训练学出来的，是人们根据误报漏报代价和 ROC 曲线自己拍板的决策旋钮。
- **误区 2：以为逻辑回归直接能学出曲线边界**。原特征下的逻辑回归决策面永远是平直的超平面。

**⑥ 对照最终版**

- "(1) Fit $(w,b)$ on the training data by maximum likelihood." → （1）在训练数据上用极大似然拟合参数 $(w,b)$。
- "(2) For a new $x$, compute $p(x)=\sigma(w^Tx+b)$." → （2）对新样本 $x$ 计算概率 $p(x)$。
- "(3) Predict 1 if $p(x)\ge t$. With $t=0.5$ this is $w^Tx+b\ge0$: a linear boundary." → （3）$p(x)\ge t$ 判 1；取 0.5 时就是 $w^Tx+b\ge 0$，即一条线性边界。
- "(4) Evaluate on test data (confusion matrix, AUC)." → （4）在测试集上评估（混淆矩阵、AUC）。

### 5.5 Explain the principle of Ridge regression. 解释岭回归的原理。 ★

考过：[2021 Ex2 d](../DataML-CHPS-2021-examen_zh.md)；[2023.3 Ex1 Q6](../DataML-CHPS-2022-examen_zh.md) 的参考答案也以 Ridge 为例

**先懂这些：** ① [第二课 · 岭回归与对偶（Why adding λI makes the system solvable）](../../Lectures/02_LM/05_ridge_and_duality.md)；② 高维最小二乘为什么病态——[第二课 · 泛化与高维](../../Lectures/02_LM/02_generalization_and_high_dimensions.md)。

**最终版答案（背诵版 EN，≤5 行）：**
Ridge adds an **$\ell_2$ penalty**: $\min_\beta\|y-X\beta\|^2+\lambda\|\beta\|^2$, so $\hat\beta=(X^TX+\lambda I)^{-1}X^Ty$.
$X^TX+\lambda I$ is **always invertible** (even if $d>N$).
The coefficients **shrink towards 0**: a little bias, much less **variance**.
$\lambda$ is chosen by CV, on standardized features.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

解释**岭回归（Ridge regression）**的核心原理：它往普通最小二乘（OLS）里加了什么、为什么矩阵一下子就变得可逆好算、又怎么防止过拟合？

**② 需要的工具**

- **OLS 的两个老毛病**（见 5.3）：当特征很多（$d>N$）或者两个特征高度相关（比如“身高（厘米）”和“身高（米）”同时放进去）时，$X^TX$ 要么根本**不可逆**算不出解，要么算出的两个系数一个 $+1000$、一个 $-1000$，对数据的一点微小噪声抖动极大（方差爆炸）。
- **$\ell_2$ 惩罚** $\|\beta\|_2^2 = \sum_j \beta_j^2$：把所有权重系数的**平方加起来**，逼着它们别乱变大。
- **单位矩阵 $I$ 与对角加 $\lambda I$（为什么叫“岭”）**：$I$ 是对角线全为 1、其余全是 0 的矩阵。把 $X^TX$ 改成 $X^TX+\lambda I$，就是沿着矩阵斜对角线垫高一条“山脊（ridge）”$\lambda$。因为 $X^TX$ 的特征值原本 $\ge 0$（病态时有几个刚好 $=0$），集体加上 $\lambda > 0$ 后，**所有特征值统统变成 $\ge \lambda > 0$**，矩阵瞬间**绝对可逆**！
- **特征必须先标准化**（见 3.4）：因为 $\ell_2$ 惩罚平等对待所有系数的大小，不先把特征缩放到同一单位，惩罚就会偏心。

**③ 一步一步**

1. **在 OLS 目标后面加 $\ell_2$ 惩罚**：
   $$\min_\beta\ \|y - X\beta\|_2^2 + \lambda\|\beta\|_2^2 \quad (\lambda>0\text{，截距通常不放进惩罚})$$
2. **求导直接得到闭式解**：和 OLS 一样令梯度为 0，得到解析解：
   $$\hat\beta = (X^TX + \lambda I)^{-1}X^Ty$$
3. **解决病态、解唯一且稳**：不管是不是 $d>N$、也不管有没有重复特征，只要 $\lambda>0$，$X^TX+\lambda I$ 永远可逆。
4. **系数收缩（shrinkage）换低方差**：惩罚逼着所有系数整体**往 0 缩小**（但只是缩小，很少变成精确的 0——这点和 Lasso 不同，见 5.6）。代价是故意引入了一点点小偏差，换来**方差大幅下降**、泛化变好。
5. **超参数 $\lambda$ 怎么定？** 先对特征做**标准化**，再用**交叉验证（CV）**挑让验证误差最小的 $\lambda$。
6. **对偶视角（选看扩展）**：当特征维数 $d \gg N$ 时，可以写成只用到样本间内积的等价形式 $\hat y(x) = x^TX^T(XX^T+\lambda I)^{-1}y$，把内积换核函数就是**核岭回归**。

**④ 小例子**

拿 3 个点 $(0,1),\,(1,2),\,(2,4)$（去中心化算出 $S_{xx}=2,\,S_{xy}=3$），一维 Ridge 的斜率公式是 $\hat\beta_1 = \frac{S_{xy}}{S_{xx}+\lambda} = \frac{3}{2+\lambda}$：

- **$\lambda=0$（即普通 OLS）**：斜率 $= 3/2 = 1.5$；
- **$\lambda=1$**：斜率 $= 3/(2+1) = 1.0$；
- **$\lambda=4$**：斜率 $= 3/(2+4) = 0.5$。

可以看到，只要 $\lambda$ 增大，斜率就被稳稳地往 0 拉近，但只要 $\lambda$ 有限，它只会**接近 0 而不会变成精确的 0**。

**⑤ 常见误区**

- **误区 1：以为 Ridge 也能像 Lasso 一样把无关特征删掉（把系数压成 0）**。Ridge 只会把系数整体缩得很小，几乎不会压出精确的 0；要做变量筛选得用 Lasso（见 5.6）。
- **误区 2：直接拿原始不同量纲的数据跑 Ridge**。切记必须先做**标准化**！

**⑥ 对照最终版**

- "Ridge adds an $\ell_2$ penalty: $\min_\beta\|y-X\beta\|^2+\lambda\|\beta\|^2$, so $\hat\beta=(X^TX+\lambda I)^{-1}X^Ty$." → Ridge 加了 $\ell_2$ 惩罚，并给出了闭式解公式。
- "$X^TX+\lambda I$ is always invertible (even if $d>N$)." → 即使特征比样本还多（$d>N$），$X^TX+\lambda I$ 也永远可逆。
- "The coefficients shrink towards 0: a little bias, much less variance." → 系数向 0 收缩：付出一点偏差，换来方差大降。
- "$\lambda$ is chosen by CV, on standardized features." → $\lambda$ 在标准化特征上通过交叉验证选出。

### 5.6 How do you estimate a sparse linear model? 如何估计稀疏线性模型？ ★

考过：[2023.11 Ex1 Q3](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① 稀疏回归模型、约束式与惩罚式两种表述——[第二课 · 稀疏性与模型选择](../../Lectures/02_LM/03_sparsity_and_model_selection.md)；② 从 $\ell_0$ 到 $\ell_1$、绝对值惩罚为什么能把系数压到 0——[第二课 · Lasso 与结构化稀疏性](../../Lectures/02_LM/04_lasso_and_structured_sparsity.md)；③ 求解算法（坐标下降、LARS、近端方法）——[第四课 · LASSO 估计的优化方法](../../Lectures/04_UL_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
Use the **Lasso**: $\min_\beta\|Y-X\beta\|^2+\lambda\|\beta\|_1$.
The **$\ell_1$ penalty** sets many coefficients **exactly to 0**, so it selects variables.
It is the **convex relaxation** of the $\ell_0$ problem (best subset selection, NP-hard).
$\lambda$ by **cross-validation**; solved by **LARS** (whole regularization path), **coordinate descent** or **proximal methods** (ISTA / FISTA, soft thresholding).

**解析版（小白也能看懂）：**

**① 这道题在问什么**

面对一大堆特征（比如 500 个基因指标），只有少数几个真正有用。怎么从数据里估计出一个**稀疏线性模型**（大部分系数直接等于 0、只保留少部分关键特征）？

**② 需要的工具**

- **稀疏（sparse）**：向量里绝大多数系数精确等于 `0`，等于顺便自动删掉了无用特征、模型极易解释。
- **理想但算不动的 $\ell_0$ 惩罚（最优子集选择）**：$\|\beta\|_0$ 数的是“非零系数一共有几个”。要选出“最多只用 5 个特征的最佳组合”，必须穷举所有 $\binom{d}{5}$ 种组合——当 $d=100$ 时组合数比宇宙原子还多，属于 **NP 难**问题。
- **$\ell_1$ 范数与“凸松弛”**：退一步改用系数的**绝对值和** $\|\beta\|_1 = \sum_j |\beta_j|$。它既是光滑好优化的**凸函数**（大碗底），又能把大量小系数压成精确的 0——所以叫 $\ell_0$ 问题的**凸松弛（convex relaxation）**。
- **为什么 $\ell_1$ 能压成 0，而 $\ell_2$（Ridge）不能？**
  用“砍价手续费”对比一下：当系数 $\beta_j$ 变得很小（如 `0.01`）时，Ridge 惩罚 $\beta_j^2$ 已经微乎其微（$0.01^2=0.0001$），模型懒得把它再压成 0；而 Lasso 惩罚 $|\beta_j|$ 不管系数多小，斜率始终不降（每留一点都要交固定税），或者从几何看，**$\ell_1$ 约束区是个带尖角的菱形，误差等高线很容易正好撞在坐标轴的尖角上**——于是很多系数直接归 `0`！
- **软阈值（soft thresholding）** $S_\lambda(z)=\text{sign}(z)\max(|z|-\lambda,0)$：把绝对值 $\le \lambda$ 的数直接砍成 `0`，把超过 $\lambda$ 的往 0 收缩 $\lambda$。这正是 Lasso 把小系数变成 0 的算子。

**③ 一步一步（模型、选参、求解三部曲）**

1. **写出 Lasso 目标（课件写法）**：
   $$\min_\beta\ \|Y - X\beta\|_2^2 + \lambda\|\beta\|_1$$
   （有的教材在平方项前乘 $\frac1N$ 或 $\frac12$，只是把 $\lambda$ 等比例缩放。）
2. **先标准化，再用交叉验证挑 $\lambda$**：和 Ridge 一样，先给特征做**标准化**，再沿着不同的 $\lambda$（正则化路径）做**交叉验证**，选预测误差最低的 $\lambda$（或兼顾更稀疏的简单模型）。
3. **怎么求解？** 绝对值函数在 0 点有个尖角不可导，没法像 Ridge 那样直接写矩阵逆公式，所以要用第四课讲的三类专门优化算法：
   - **LARS（最小角回归）**：把 $\lambda$ 从大往小扫，一次性把整条正则化路径（特征依次进场的过程）算出来；
   - **坐标下降（Coordinate Descent）**：每次固定其他特征，只单独更新 1 个系数 $\beta_j$，每一步都能直接套软阈值公式；
   - **近端梯度法（ISTA / FISTA）**：先按误差平方项走一步常规梯度下降，紧接着套一次软阈值把太小的系数削成 0。
4. **知道它的局限**：如果两个有用特征高度相关（几乎一模一样），Lasso 往往随机挑一个留着、把另一个压成 0，导致挑出来的变量集合不够稳定（此时常改用 **Elastic Net**＝$\ell_1+\ell_2$ 混合惩罚）；要证明 Lasso 找回来的恰好就是“真实非零特征集”，需要较强的相关性条件。

**④ 小例子（亲手算一遍软阈值怎么把系数砍成 0）**

在特征互相正交且长度为 1（$X^TX=I$）、目标为 $\frac12\|Y-X\beta\|^2+\lambda\|\beta\|_1$ 的最简情况下，Lasso 解就是对普通 OLS 系数直接做一次软阈值 $S_\lambda$。假设普通 OLS 算出的 3 个系数是 `3.0, 0.8, -2.0`，设阈值 $\lambda = 1.0$：

- `3.0`：往 0 缩 1.0 → **`2.0`**（保留）；
- `0.8`：绝对值比 1.0 小 → 直接被砍成 **`0`**（这个特征被自动剔除了！）；
- `-2.0`：往 0 缩 1.0 → **`-1.0`**（保留）。

（注：一般非正交或未单位化时，不能简单各自减 $\lambda$，而是通过坐标下降／LARS 协同迭代，但“小系数直接归 0”的机制完全相同。）

**⑤ 常见误区**

- **误区 1：把 Ridge（$\ell_2$）也说成能挑选变量**。记住：**Ridge 缩小系数但不归零，Lasso（$\ell_1$）才能精确归零做变量选择**。
- **误区 2：以为 Lasso 没被压成 0 的变量就 100% 是“真正因果变量”**。存在强共线特征时，Lasso 可能二选一挑错搭档。

**⑥ 对照最终版**

- "Use the Lasso: $\min_\beta\|Y-X\beta\|^2+\lambda\|\beta\|_1$." → 使用 Lasso 回归（按课件公式写法）。
- "The $\ell_1$ penalty sets many coefficients exactly to 0, so it selects variables." → $\ell_1$ 惩罚会把很多系数精确设为 0，从而实现变量选择。
- "It is the convex relaxation of the $\ell_0$ problem (best subset selection, NP-hard)." → 它是 $\ell_0$ 问题（最优子集选择，NP 难）的凸松弛。
- "$\lambda$ by cross-validation; solved by LARS (whole regularization path), coordinate descent or proximal methods (ISTA / FISTA, soft thresholding)." → $\lambda$ 靠交叉验证选；用 LARS、坐标下降或近端方法（ISTA/FISTA、软阈值）求解。

### 5.7 With N = 50 data points and d = 200 features, which regression method would you prefer? How could you still use OLS? N=50、d=200 时选哪种回归方法？如果必须用 OLS 怎么办？ ★

考过：[2021 Ex2 e](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** ① "高"维对线性回归意味着什么——[第二课 · 泛化与高维（What 'high' means for linear regression）](../../Lectures/02_LM/02_generalization_and_high_dimensions.md)；② 5.5 和 5.6。

**最终版答案（背诵版 EN，≤5 行）：**
$d=200>N=50$: $X^TX$ is **not invertible**; the OLS solution is **not unique** and unstable, with a high risk of **overfitting**.
I prefer **Lasso** (selects variables) or **Ridge**, with $\lambda$ by CV.
To use OLS anyway: first **reduce the dimension below 50** (variable selection, or **PCA then OLS**), or take the **pseudo-inverse** solution $X^+y$.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

这是一道经典高维小样本场景题：手头只有 **$N=50$ 个样本**，特征却高达 **$d=200$ 个**（比如 50 个病人测了 200 个基因指标）。问题是两问：（1）这时候你首选什么回归方法？（2）如果老板硬规定**必须用 OLS**，还有什么办法挽救？

**② 需要的工具**

- **为什么 $d > N$ 会出大事？（未知数比方程多）**：线性回归相当于拿 $N=50$ 个样本方程去解 $d=200$ 个未知权重系数。$50$ 个方程解 $200$ 个未知数，是典型的**欠定方程组**——解有无穷多个！反映在矩阵上就是 $200\times 200$ 的矩阵 $X^TX$ 最多只有 50 个独立方向（秩 $\le 50 < 200$），根本**不可逆**，连 $(X^TX)^{-1}$ 都算不出来。
- **正则化方法（首选方案）**：**Lasso**（自动删变量）、**Ridge**（让 $X^TX+\lambda I$ 变得可逆）和 **Elastic Net**（两者结合），见 5.5、5.6。
- **PCA（主成分分析）**：先不看 $y$，把 200 个常常彼此相关的特征“浓缩打包”成少数几个（如 $k=10$ 个）最有代表性的综合指标，相当于大幅降维。
- **伪逆（pseudo-inverse）最小范数解 $X^+y$**：既然无穷多组 $\beta$ 都能同样拟合好这 50 个点，数学上通过奇异值分解（SVD）挑出其中“自身长度 $\|\beta\|_2$ 最短、最不极端”的那唯一一组解（刚好也是 Ridge 当 $\lambda\to 0^+$ 时的极限）。

**③ 一步一步（回答两小问）**

1. **先说清为什么普通 OLS 直接挂掉**：$d=200 > N=50$ 时，$X^TX$ 不可逆，OLS 解**不唯一**且极不稳定。只要那 50 条样本彼此线性无关（常见情况），就能在训练集上强行凑出误差为 0 的解（但若出现相同特征却不同标签的样本，也不可能凑到 0）。不管怎样，用 200 个旋钮去硬背 50 个点，**过拟合风险极高**。
2. **第一问：我首选哪种回归方法？** 首选**正则化线性模型**（先做特征标准化，再用交叉验证挑 $\lambda$）：
   - 如果怀疑 200 个特征里只有少数真有用 → 首选 **Lasso**（它能把无关特征直接压成 0，且最多只会挑出 $\le N=50$ 个变量，模型清爽好解释）；
   - 如果觉得很多特征都有点小贡献 → 选 **Ridge**（让 $X^TX+\lambda I$ 绝对可逆、系数稳稳收缩）；也可以折中用 **Elastic Net**。
3. **第二问：如果规定必须用 OLS 怎么救？** 核心原则是**先把维度压缩到 $N=50$ 以下**（让方程数反超未知数），再套 OLS：
   - **方法 A（先选变量再 OLS）**：用单变量相关性筛选、前向逐步选择等方法，只留下 $k < 50$ 个特征，再跑 OLS；
   - **方法 B（先 PCA 降维再 OLS）**：用主成分分析把 200 维压缩成 $k < 50$ 个主成分（主成分回归 PCR），再在这些综合成分上跑 OLS；
   - **方法 C（直接用伪逆 $X^+y$）**：在所有最小二乘解里取最小欧氏范数解（虽然仍建议控制复杂度）。
   其中降维后的维度 $k$ 一样要用交叉验证选好（别太大，否则又过拟合）。

**④ 小例子**

50 个方程解 200 个未知数，就像只给你 **1 个方程** $x+y=2$ 却要你求出 $(x,y)$ 两个数：$(1,1)$、$(0,2)$、$(100,-98)$……全都能让训练误差 $=0$！没有正则化或降维，模型根本不知道哪组才是真的规律；加上 $\min(x^2+y^2)$ 约束（最小范数伪逆），才唯一挑出最温和的 $(1,1)$。

**⑤ 常见误区**

- **误区 1：直接套公式算 $(X^TX)^{-1}$**——这里 $X^TX$ 奇异不可逆，程序会直接报错或数值炸裂。
- **误区 2：以为 $d>N$ 就“一定”能训练误差 $=0$ 且必然过拟合**——训练误差 $=0$ 还需行满秩（不存在矛盾样本）等条件，过拟合是否严重也要看具体信噪比与正则化。
- **误区 3：漏答后半句**——很多人只答了“改用 Ridge/Lasso”，忘了回答“*如果必须用 OLS 怎么办*”。

**⑥ 对照最终版**

- "$d=200>N=50$: $X^TX$ is not invertible; the OLS solution is not unique and unstable, with a high risk of overfitting." → 问题根源：$X^TX$ 不可逆、解不唯一且不稳定、过拟合风险高。
- "I prefer Lasso (selects variables) or Ridge, with $\lambda$ by CV." → 我首选 Lasso（能自动挑变量）或 Ridge，并用交叉验证选 $\lambda$。
- "To use OLS anyway: first reduce the dimension below 50 (variable selection, or PCA then OLS), or take the pseudo-inverse solution $X^+y$." → 硬要用 OLS 的三种救法：先降维到 50 以下（选变量或 PCA 后接 OLS），或者取伪逆解 $X^+y$。

### 5.8 Which polynomial models would you try on 4 data points, and what is the most complex meaningful one? 4 个数据点上可以尝试哪些多项式模型？最复杂且有意义的是哪个？ ★

考过：[2021 Ex2 c](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** ① "线性模型"指对参数线性，多项式回归仍是 OLS——[第二课 · 线性模型与最小二乘](../../Lectures/02_LM/01_linear_models_and_least_squares.md)；② 每多拟合一个方向就多吸收一份噪声（$d/n$ 项）——[第二课 · 泛化与高维](../../Lectures/02_LM/02_generalization_and_high_dimensions.md)。

**最终版答案（背诵版 EN，≤5 行）：**
Polynomial regression is still **linear in the parameters** (OLS on $1,x,x^2,\dots$).
With 4 points, try degree **2** and **3**.
Degree **3** (4 parameters) is the most complex: it **interpolates** the 4 points (zero training error); higher degrees are underdetermined.
In practice, choose a low degree by validation.

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

---

## 6. 深度学习与数值优化

### 6.1 What optimization strategy is used to train / calibrate deep learning architectures? 深度学习采用什么优化策略？ ★★

考过：[2023.3 Ex1 Q8](../DataML-CHPS-2022-examen_zh.md) · [2024 Ex1 Q3](../DataML-CHPS-2024-examen_zh.md)；相关：6.2（2023.11 问一般机器学习的数值优化）

**先懂这些：** ① 反向传播：链式法则、激活函数——[第六课 · 2. 反向传播算法、选读：通过反向传播计算梯度](../../Lectures/06_DL_zh.md)；② 梯度下降会收敛到最优解吗、SGD 避开不良临界点——[第六课 · 反向传播：讨论；深度学习优化中的结果](../../Lectures/06_DL_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
We minimize the empirical risk with **mini-batch SGD** (or **Adam**):
$\theta_{t+1}=\theta_t-\eta_t\nabla_\theta\frac1{|B_t|}\sum_{i\in B_t}\ell(f_\theta(x_i),y_i)$.
The gradient is computed by **backpropagation** (chain rule).
The problem is **non-convex**: no global guarantee. Learning rate, batch size, initialization and **early stopping** matter.

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

### 6.2 How is numerical optimization achieved in machine learning methods? Give an example. 机器学习方法如何做数值优化？举一个例子。 ★

考过：[2023.11 Ex1 Q8](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① OLS 闭式解与 QR／SVD——[第二课 · 线性模型与最小二乘](../../Lectures/02_LM/01_linear_models_and_least_squares.md)；② Lasso 的三种求解算法——[第四课 · LASSO 估计的优化方法](../../Lectures/04_UL_zh.md)；③ SVM 的对偶二次规划——[第五课 · 对偶表述](../../Lectures/05_NLM_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
Write the objective (loss + penalty), then pick a solver:
**closed form** (OLS, Ridge: QR / SVD), **gradient / Newton** (logistic regression), **coordinate descent / proximal** (Lasso), **SGD** (neural networks).
Example: $\ell_2$-regularized logistic regression, $w_{t+1}=w_t-\eta\nabla L(w_t)$ until the gradient is small; it is strictly **convex**, so with a suitable step size it converges to the **global minimum**.

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

### 6.3 What is the mathematical space of functions of deep feedforward neural networks? 深度前馈神经网络对应怎样的函数空间？ ★

考过：[2023.11 Ex1 Q6](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① 深度前馈网络的定义——[第六课 · 深度学习：主要概念介绍（深度前馈网络）](../../Lectures/06_DL_zh.md)；② 单层网络是通用逼近器——[第六课 · 1. 通用逼近器的存在性定理](../../Lectures/06_DL_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
For a fixed architecture: $\mathcal H=\{x\mapsto A_{L+1}\circ\sigma_L\circ A_L\circ\dots\circ\sigma_1\circ A_1(x)\}$, with $A_\ell(u)=W_\ell u+b_\ell$ and $\sigma$ = ReLU, tanh…
It is a **parametric family of compositions**, **non-linear** in $\theta$ and **not a vector space**.
**Universal approximation**: with enough neurons, it can approximate any continuous function on a compact set.

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

### 6.4 What are the hyperparameters of deep neural networks? 深度神经网络有哪些超参数？ ★

考过：[2023.11 Ex1 Q6](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** [第六课 · 设计问题（1/2）设定、（2/2）选择结构；深度学习中的正则化](../../Lectures/06_DL_zh.md)；超参数与参数的区别见 3.4。

**最终版答案（背诵版 EN，≤5 行）：**
Weights and biases are **learned**. Hyperparameters:
**architecture** (depth, width, activations, layer types);
**regularization** (weight decay, dropout, early stopping);
**optimization** (optimizer, **learning rate**, **batch size**, epochs, initialization). Tuned on a **validation set**.

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

### 6.5 What is the fundamental difference between deep and shallow learning? 深度学习与浅层学习的根本区别是什么？ ★

考过：[2020 A6](../Exam_2020_zh.md)

**先懂这些：** ① [第六课 · 浅层与深度学习：Vapnik 与 LeCun；从浅层到深层网络](../../Lectures/06_DL_zh.md)；② 浅层方法如何用显式惩罚控制复杂度——[第一课 · 算法家族、正则化与处理流程](../../Lectures/01_intro/02_algorithms_and_pipeline.md)。

**最终版答案（背诵版 EN，≤5 行）：**
**Shallow** learning: **hand-made features** (or a fixed kernel) + **explicit (Tikhonov) regularization** $\min\hat L_n(h)+\lambda\,\text{pen}(h)$; the penalty controls the variance; often convex.
**Deep** learning stacks **many non-linear layers** and **learns the features itself**, end to end; it is a **universal approximator** (almost zero bias).
**No penalty term**: non-convex (SGD), **implicit regularization** (weight decay, dropout, early stopping…), needs **much data and computation**.

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

- "Shallow learning: hand-made features (or a fixed kernel) + explicit (Tikhonov) regularization …; the penalty controls the variance; often convex." → 浅层的特点（课件："shallow learning often relates to Tikhonov's regularization"）。
- "Deep learning stacks many non-linear layers and learns the features itself, end to end; it is a universal approximator (almost zero bias)." → 深度的特点（课件："universal approximators (zero bias)"）。
- "No penalty term: non-convex (SGD), implicit regularization (weight decay, dropout, early stopping…), needs much data and computation." → 课件："no penalty term in the optimization but lots of tricks … which amount to implicit regularization"。

---

## 7. 聚类（k-means、软 k-means、层次聚类）

> 六篇讲义没有完整讲 k-means 及其变体，主要靠 [Lab4](../../Exercises/Lab4/Lab4_zh.ipynb)（聚类、簇数选择）和 [Lab5](../../Exercises/Lab5/Lab5_zh.ipynb)（GMM、EM）学懂原理。一维 k-means 填表见[计算题文件](00_calculations.md)。

### 7.1 Give the k-means objective function and the pseudocode of the algorithm. 给出 k-means 的目标函数和算法伪代码。 ★★★★

考过：[2021 Ex4 a](../DataML-CHPS-2021-examen_zh.md)（只更新一个中心的变体）· [2023.3 Ex3 a](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex2 a](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 a](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 为什么均值是使组内平方和最小的点（对 $c$ 求导＝0）；② [Lab4](../../Exercises/Lab4/Lab4_zh.ipynb) k-means 部分，手动跟踪几轮迭代。

**最终版答案（背诵版 EN，≤5 行）：**
Objective: $J=\sum_{i=1}^N\|x_i-c_{z_i}\|^2$ (within-cluster sum of squares).
```text
initialize k centers (random data points, or k-means++)
repeat
  assign: z_i = argmin_j ||x_i - c_j||^2
  update: c_j = mean of the points with z_i = j
until the assignments do not change
```

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

### 7.2 Why does the k-means procedure converge? k-means 为什么会收敛？ ★★★

考过：[2023.3 Ex3 a](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex2 a](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 a](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 7.1 的两步分别是在固定一组变量时对另一组变量**精确最小化** $J$（坐标下降）。

**最终版答案（背诵版 EN，≤5 行）：**
Each step **cannot increase** $J$: the nearest center minimizes $J$ in $z$; the **mean** minimizes $J$ in $c$.
$J\ge0$ keeps decreasing, and there is a **finite number of partitions** ($\le k^N$).
So it **stops in finite time**, at a **local** minimum, not always the global one.

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

### 7.3 Why are multiple (re)runs suggested? How can k-means approximate the globally optimal solution? 为什么建议多次运行？如何用 k-means 逼近全局最优？ ★★★

考过：[2023.3 Ex3 a](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex2 a](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 a](../DataML-CHPS-2024-examen_zh.md)（原问法：how it can be used to approximate the globally optimal solution）

**先懂这些：** 先理解 7.2 的"只保证局部最优"；在 [Lab4](../../Exercises/Lab4/Lab4_zh.ipynb) 用不同随机种子跑同一数据，比较 $J$。

**最终版答案（背诵版 EN，≤5 行）：**
$J$ is **non-convex**: the result **depends on the initialization**.
So we run k-means **many times** with random starts and **keep the lowest $J$**.
**k-means++** spreads the initial centers and helps.
This approximates the global optimum well, but with **no guarantee**.

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

### 7.4 How do you validate the choice of the number of clusters? 如何验证聚类数目的选择？ ★★

考过：[2019 Q7](../Exam_2019_zh.md) · [2020 A5](../Exam_2020_zh.md)

**先懂这些：** [Lab4](../../Exercises/Lab4/Lab4_zh.ipynb) 簇数选择部分；[Lab5](../../Exercises/Lab5/Lab5_zh.ipynb) GMM（BIC）；与 1.5 一起复习。

**最终版答案（背诵版 EN，≤5 行）：**
$J$ always decreases with $k$, so we cannot just minimize it.
Use the **elbow method**, the **silhouette score** (choose the max), **BIC / AIC** for mixtures,
**stability** under resampling, and domain knowledge.

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

### 7.5 Propose a soft k-means with probabilistic assignments: definition, pseudocode, convergence. 设计一种概率分配的软 k-means：定义、伪代码、是否收敛。 ★★

考过：[2023.11 Ex2 b](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 b](../DataML-CHPS-2024-examen_zh.md)（"similar to Gaussian Mixture Modeling"）

**先懂这些：** ① [Lab5](../../Exercises/Lab5/Lab5_zh.ipynb) GMM 与 EM：E 步算责任度、M 步加权更新；② softmax 函数。这是开放设计题，必须同时写出**目标、更新规则、收敛论证**。

**最终版答案（背诵版 EN，≤5 行）：**
Soft assignment with temperature $\tau$: $r_{ij}=\frac{\exp(-\|x_i-c_j\|^2/\tau)}{\sum_l\exp(-\|x_i-c_l\|^2/\tau)}$.
Repeat: **E-step** compute all $r_{ij}$; **M-step** $c_j=\sum_ir_{ij}x_i/\sum_ir_{ij}$.
Both steps do not increase $F=\sum r_{ij}\|x_i-c_j\|^2+\tau\sum r_{ij}\log r_{ij}$, which is bounded below, so the objective **converges** (not necessarily to a global, or even local, minimum).
It is **EM for a GMM** with equal weights and a fixed shared spherical covariance ($\tau=2\sigma^2$).

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

### 7.6 If k-means is initialized with the soft k-means solution, will the clusters change? Is it a local minimum of hard k-means? 用软 k-means 的解初始化 k-means，簇会变吗？它是硬 k-means 的局部极小吗？ ★★

考过：[2023.11 Ex2 c](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 c](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 软中心是**加权均值**，硬中心是**普通均值**（7.1 与 7.5 对比）。

**最终版答案（背诵版 EN，≤5 行）：**
**Not necessarily.** Soft centers are **weighted means** (every point counts a bit).
With hard assignments, each cluster mean is different, so k-means **moves the centers** and some points can change cluster.
It stays the same only if each soft center already **equals the mean of its hard cluster** (almost 0/1 weights make this approximately true).

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

### 7.7 Compare hard and soft k-means. When is soft k-means preferable? 比较硬 k-means 和软 k-means。什么时候软 k-means 更合适？ ★★

考过：[2023.11 Ex2 d](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 c](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 7.5、7.6；[Lab5](../../Exercises/Lab5/Lab5_zh.ipynb) 中 GMM 与 k-means 的对比。

**最终版答案（背诵版 EN，≤5 行）：**
**Hard**: one cluster per point, **simple and fast**, but boundary points are forced into one cluster.
**Soft**: gives **membership probabilities** and shows **uncertainty**; a GMM can model elliptical clusters.
But it costs more and needs $\tau$ or a model.
Use soft when clusters **overlap** or when probabilities are needed.

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

### 7.8 Summarize the dataset by two "typical" examples (the centers): how well does each center represent its cluster? 用两个"典型"样本（中心）概括数据：每个中心代表其簇的效果如何？ ★★

考过：[2021 Ex4 c](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex3 d](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** 中心（均值，合成原型）与 medoid（真实样本）的区别；簇内 MSE 作为"代表性"的度量。具体数值见两卷参考答案。

**最终版答案（背诵版 EN，≤5 行）：**
The two typical examples are the **centers** (means); if a real point is needed, the **medoid**.
A **compact** cluster is well represented (small MSE).
A **spread** cluster, or one with sub-groups or outliers, is badly represented: its mean can lie where there is no data.
A **fixed** center (not the mean) is worse.

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

### 7.9 During k-means, how can a cluster become empty? Give heuristics to continue without reducing k. k-means 中簇为什么会变空？给出不减少 k 的处理办法。 ★

考过：[2021 Ex4 e](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** 7.1 的分配步：一个中心如果不是任何点的"最近中心"，它的簇就是空的。

**最终版答案（背诵版 EN，≤5 行）：**
A cluster is empty when **no point is closest to its center** (bad initialization, or other centers took its points).
Fixes: move the center to the **point with the largest error**, or **split the biggest cluster**, or **re-seed** it (uniformly at random, or by the **k-means++** rule: probability ∝ squared distance to the nearest center).

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

### 7.10 What if the initial clusters are formed by assigning each point uniformly at random? Will it converge, faster or slower? 如果初始化时把每个点等概率随机分到某个簇，会收敛吗？更快还是更慢？ ★

考过：[2023.3 Ex3 b](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** 大数定律：随机子集的均值≈全体均值；对比 7.3 的 k-means++。

**最终版答案（背诵版 EN，≤5 行）：**
Each random cluster is a sample of the whole data, so all initial centers are **near the global mean** (law of large numbers).
It **still converges** (same argument as 7.2), but it can be **slower**, because the centers must first separate.
It may also end more often in a **bad local optimum** (this depends on the data).

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

### 7.11 Give three linkage criteria for hierarchical agglomerative clustering, with formulas. 给出层次凝聚聚类的三种连接准则及公式。 ★

考过：[2023.3 Ex3 e](../DataML-CHPS-2022-examen_zh.md)（树状图：[2022_linkage.png](../Answers/2022_linkage.png)）

**先懂这些：** 凝聚聚类流程：从单点簇开始，每次合并距离最近的两个簇；[Lab4](../../Exercises/Lab4/Lab4_zh.ipynb)。

**最终版答案（背诵版 EN，≤5 行）：**
Start from single points and **merge the two closest clusters** (this gives a dendrogram).
**Single**: $\min_{a,b}\|a-b\|$ (chaining). **Complete**: $\max_{a,b}\|a-b\|$ (compact clusters).
**Average**: $\frac1{|A||B|}\sum_{a,b}\|a-b\|$. **Ward**: merge with the smallest increase of inertia.

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

### 7.12 Use bootstrapped k-means solutions to compute an outlier score; compare with Isolation Forest. 用多次 bootstrap 的 k-means 解计算离群分数，并与 Isolation Forest 比较。 ★

考过：[2024 Ex5 d](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① bootstrap（有放回重采样）——[第五课 · 一般而言，bootstrap 是什么？](../../Lectures/05_NLM_zh.md)；② Isolation Forest 原理——[Lab3](../../Exercises/Lab3/Lab3_zh.ipynb) 异常检测部分。

**最终版答案（背诵版 EN，≤5 行）：**
For $b=1..B$: take a **bootstrap sample**, run k-means, and score each point by its **(normalized) distance to the nearest center**. The outlier score is the **mean / median** over the runs.
It is more stable than one run, but k-means is **not robust** and assumes round clusters.
**Isolation Forest** uses random splits: outliers are **isolated quickly**; no centers, no $k$.

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

---

## 8. 稳健估计（RANSAC）与概率图模型

> RANSAC 主要靠[作业一第 1 题讲解](../../Exercises/Assignment1/guide/01_ransac.md)和 [Lab1](../../Exercises/Lab1/Lab1_zh.ipynb)，图模型靠 [Lab5](../../Exercises/Lab5/Lab5_zh.ipynb)。2023.11 和 2024 的报警题完全相同，且**题面缺一个条件概率** $q=P(a=0\mid c=0)$；数值计算见[计算题文件](00_calculations.md)。

### 8.1 Describe the standard RANSAC method and algorithm for linear regression. 详细描述用于线性回归的标准 RANSAC 方法和算法。 ★★★

考过：[2023.3 Ex2 c](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex4 c](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex4 b](../DataML-CHPS-2024-examen_zh.md)（推广到圆，见 8.5）

**先懂这些：** ① OLS 对离群点敏感（5.3）；② [作业一第 1 题：RANSAC](../../Exercises/Assignment1/guide/01_ransac.md)，把算法亲手实现一遍；③ "最小样本"＝确定模型所需的最少点数（直线 2 个、圆 3 个）。

**最终版答案（背诵版 EN，≤5 行）：**
```text
repeat T times:
  pick 2 random points -> line y = a x + b
  inliers I = { i : |y_i - a x_i - b| <= tau }
  keep the line with the largest I
refit the line by OLS on the best inlier set
```
Choose $T\ge\frac{\log(1-p)}{\log(1-w^2)}$ ($w$ = inlier ratio). It is robust to many **outliers**.

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

### 8.7 Give the graphical model of the battery–sensor–alarm system and write the joint distribution. 给出电池—传感器—报警系统的概率图模型并写出联合分布。 ★★

考过：[2023.11 Ex3 a](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex3 a](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 有向图模型（贝叶斯网络）：联合分布＝各节点在给定父节点下的条件分布之积；② [Lab5](../../Exercises/Lab5/Lab5_zh.ipynb) 图模型部分。

**最终版答案（背诵版 EN，≤5 行）：**
Chain **$b\to c\to a$**: $p(a,b,c)=p(b)\,p(c\mid b)\,p(a\mid c)$, so $a\perp b\mid c$.
Data: $P(b=0)=0.1$, $P(c=0\mid b=1)=0.01$, $P(c=0\mid b=0)=0.3$, $P(a=0\mid c=1)=0.99$.
$P(a=0\mid c=0)=q$ is **not given**.

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

### 8.8 Are a and b independent? (conditional vs marginal independence) a 和 b 独立吗？（条件独立与边际独立） ★★

考过：[2023.11 Ex3 b](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex3 b](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 链 $b\to c\to a$ 中，观测到 $c$ 会"阻断"路径；② 边际独立要用全概率公式真正算出来比较。

**最终版答案（背诵版 EN，≤5 行）：**
Given $c$, **$a$ and $b$ are independent**: both rows of the table $p(a=1\mid b,c)$ are equal ($1-q$ and $0.01$).
But they are **not marginally independent**: $P(a=1\mid b)=\sum_cP(a=1\mid c)P(c\mid b)$ differs for $b=0$ and $b=1$ (except if $q=0.99$).

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

### 8.9 How do you compute P(battery fails | no alarm) from the model? 如何用模型计算"没听到报警时电池失效"的概率？ ★★

考过：[2023.11 Ex3 c–d](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex3 c–d](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 全概率公式（对未观测变量求和＝边缘化）与 Bayes 公式；数值答案见两卷参考答案。

**最终版答案（背诵版 EN，≤5 行）：**
**Sum out** the unknown variables, then use **Bayes**:
$P(c=0)=0.039$, $P(a=0)=0.95139+0.039q$, $P(a=0,b=0)=0.0693+0.03q$,
so $P(b=0\mid a=0)=\frac{0.0693+0.03q}{0.95139+0.039q}$ (between 0.073 and 0.100).

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

### 8.2 How sensitive is RANSAC to its parameters? RANSAC 对参数的敏感性如何？ ★

考过：[2023.3 Ex2 c](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** 8.1 的三个参数；在作业一中改变 $\tau$ 看内点集的变化。

**最终版答案（背诵版 EN，≤5 行）：**
**τ**: too small rejects good points; too large accepts outliers. Choose it from the **noise level**.
**T**: too small may miss a clean sample; too large only costs time. $T$ grows fast when there are more outliers.
The results are **random**.

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

### 8.3 What is the difference between RANSAC and a typical bootstrap estimation procedure? RANSAC 与典型的 bootstrap 估计有什么区别？ ★

考过：[2023.3 Ex2 c](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** [第五课 · 一般而言，bootstrap 是什么？](../../Lectures/05_NLM_zh.md)；Bagging（2.3）。

**最终版答案（背诵版 EN，≤5 行）：**
**Bootstrap**: samples of **size N with replacement**, to estimate the **variance** of an estimator or to **average** models. Outliers stay inside, so it does **not make a non-robust estimator** (e.g. OLS) robust.
**RANSAC**: **minimal samples** (2 points), and it keeps the **best consensus**, not the average.
Its goal is **robustness** and finding outliers.

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

### 8.4 How can the internal RANSAC models "grade" datapoints as outliers, and the datapoints "grade" each model? RANSAC 内部的模型如何给数据点"打分"（是否离群），数据点又如何给模型打分？ ★

考过：[2023.11 Ex4 c](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** 8.1 中的残差 $r_i$ 和共识集 $I$；把 $T$ 个候选模型看成一张"模型×点"的残差表。

**最终版答案（背诵版 EN，≤5 行）：**
**Models grade points**: each model says inlier ($r\le\tau$) or outlier; a point rejected by most **good** models is an outlier.
**Points grade models**: the score of a model is its **number of inliers** (or a truncated loss $\sum_i\min(r_i^2,\tau^2)$).

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

### 8.5 Develop a generalized RANSAC to fit a circle C(c, r). 用广义 RANSAC 拟合圆 C(c, r)。 ★

考过：[2024 Ex4 b](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 8.1 的通用框架：最小样本大小 $s$、残差定义、重拟合，这三处要随模型改变。

**最终版答案（背诵版 EN，≤5 行）：**
Same algorithm, with three changes:
(1) sample **3 points** (one circle passes through 3 non-collinear points);
(2) residual = **radial distance** $\big|\|p_i-c\|-r\big|$;
(3) refit $(c,r)$ on the inliers by least squares. Use $T\ge\log(1-p)/\log(1-w^3)$.

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

### 8.6 Robustly estimate δ = ‖μ − m‖ (mean vs medoid) with RANSAC when each instance has a quality indicator qᵢ. 每个样本带质量指标 qᵢ 时，用 RANSAC 稳健估计 δ = ‖μ − m‖（均值与 medoid 之差）。 ★

考过：[2023.3 Ex2 d](../DataML-CHPS-2022-examen_zh.md)（开放设计题）

**先懂这些：** ① 均值对离群点敏感，medoid 是真实样本中最"居中"的；② 8.1 的"候选—共识—重拟合"框架。

**最终版答案（背诵版 EN，≤5 行）：**
$\delta$ compares the **mean** (sensitive to outliers) with the **medoid** (the most central real point); a large $\delta$ means skew or outliers.
RANSAC: sample points with probability $\propto q_i$, compute a candidate center, inliers = points within τ, score = $\sum_{i\in I}q_i$.
On the best inlier set compute $\hat\mu$, $\hat m$ and $\hat\delta=\|\hat\mu-\hat m\|$. Do not use $q_i$ as a coordinate.

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

---

## 9. 学习问题的基本概念与实际应用

### 9.1 What are the links between machine learning and numerical simulation / HPC? Give two examples. 机器学习与数值模拟（高性能计算）有哪些联系？举两个例子。 ★★★

考过：[2019 Q10](../Exam_2019_zh.md)（calcul intensif）· [2021 Ex1 Q8](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex1 Q1](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** ① 数据科学的三大支柱与机器学习的目标——[第一课 · 数据、任务与学习函数](../../Lectures/01_intro/01_data_and_learning.md)；② PCA 降维——[第四课 · PCA 及其变体](../../Lectures/04_UL_zh.md)、[Lab5](../../Exercises/Lab5/Lab5_zh.ipynb)；③ 这是 CHPS 专业的"本专业题"，几乎必考。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **Surrogate models**: run some expensive simulations (CFD, finite elements), then train a fast model (regression, neural network) to predict the output for **new parameters** without running the solver. Useful for optimization and uncertainty studies.
(2) **Reduced-order models**: use **PCA / POD** or autoencoders to compress huge simulated fields into a few modes, then learn or solve in this small space.
Also: tuning solvers, detecting anomalies on HPC nodes.

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

### 9.2 What is the difference between classification data and a classification problem? 分类数据与分类问题有什么区别？ ★★

考过：[2021 Ex1 Q1](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex1 Q2](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** [第三课 · 分类数据：例子；这些数据可以支持哪些决策？](../../Lectures/03_LMC_zh.md)——同一份数据可以对应分类、评分两种问题；与 5.2 一起复习。

**最终版答案（背诵版 EN，≤5 行）：**
**Classification data** describes the **data**: pairs $(x_i,y_i)$ where $y_i$ is a **category** (e.g. 0/1).
A **classification problem** describes the **task**: learn a rule $h:\mathcal X\to\{0,1\}$ that gives a class to new points, with a small error rate.
The same data can also be used for **other problems**: **scoring / ranking** ($s(x)$, evaluated by ROC/AUC) or **probability estimation** $P(Y=1\mid x)$.

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

### 9.3 What is the difference between supervised and unsupervised learning? Give two examples of each. 监督学习与无监督学习有什么区别？各举两个例子。 ★

考过：[2019 Q1](../Exam_2019_zh.md)

**先懂这些：** [第一课 · 数据、任务与学习函数（Types of Machine Learning problems）](../../Lectures/01_intro/01_data_and_learning.md)；[第四课 · 无监督学习与降维](../../Lectures/04_UL_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
**Supervised**: each training point $x_i$ has a known **label $y_i$**; we learn to predict $y$ from $x$. Examples: **spam detection** (classification), **predicting energy consumption** (regression).
**Unsupervised**: **no labels**; we look for **structure** in the $x_i$. Examples: **customer segmentation** (clustering), **dimension reduction** with PCA.
Supervised learning is evaluated by prediction error; unsupervised learning is harder to evaluate.

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

### 9.4 What is the difference between classification data and regression data? 分类型数据与回归型数据有什么区别？ ★

考过：[2019 Q2](../Exam_2019_zh.md)

**先懂这些：** [第一课 · 数据、任务与学习函数](../../Lectures/01_intro/01_data_and_learning.md)；[第三课 · 分类数据：例子](../../Lectures/03_LMC_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
The difference is the **type of the target $Y$**.
**Classification**: $Y$ is **qualitative / discrete**, a finite set of classes (e.g. $\{0,1\}$, disease type).
**Regression**: $Y$ is **quantitative / continuous**, $Y\in\mathbb R$ (e.g. price, temperature).
The inputs $X$ can be numerical or categorical in both cases. The losses differ: 0–1 / logistic vs squared error.

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

### 9.5 Give two concrete implementation issues in real applications (supervised anomaly detection on an instrumented production line). 实际应用中的两个具体实施问题（以生产线上的监督式异常检测为例）。 ★

考过：[2023.3 Ex1 Q10](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** ① 真实世界中的完整数据处理流程——[第一课 · 算法家族、正则化与处理流程](../../Lectures/01_intro/02_algorithms_and_pipeline.md)；② 类别不平衡下的评价指标（3.7）；③ [Lab3](../../Exercises/Lab3/Lab3_zh.ipynb) 异常检测部分。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **Data quality and labels**: sensors have different rates, scales, drifts and missing values; real defects are **rare** (strong **class imbalance**) and labels are expensive; a sensor failure must be distinguished from a real anomaly.
(2) **Realistic evaluation and drift**: split by **time** to avoid leakage; false alarms (stopping the line) and missed defects have **different costs**, so choose the threshold accordingly; the machines change over time (**concept drift**), so monitor and retrain.

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

### 9.6 Describe a data science pipeline to deploy a predictive model (e.g. energy consumption peaks). 描述部署预测模型的数据科学流程（如能耗峰值预测）。 ★

考过：[2020 B1–B3](../Exam_2020_zh.md)（智慧城市案例）

**先懂这些：** [第一课 · Machine Learning in the real world: A full pipeline for data processing](../../Lectures/01_intro/02_algorithms_and_pipeline.md)；[作业一第 4 题：数据划分](../../Exercises/Assignment1/guide/04_data_splitting.md)。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **Collect and join** the data (sites + measures), parse dates and numbers.
(2) **Clean and build features**: missing values, sensor errors, normalization per site, calendar features (hour, day), lagged consumption, temperature.
(3) **Define the target**: e.g. "peak" = consumption above the site's 95% quantile at $t+h$ (classification) or the consumption itself (regression).
(4) **Train and tune** models (logistic regression, random forest, boosting) with a **time-ordered** split, and **evaluate** on later data against a naive baseline.
(5) **Deploy and monitor** (drift), **retrain**, and **capitalize** (document, reuse data and models).

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
- "(4) Train and tune models … with a time-ordered split, and evaluate on later data against a naive baseline." → 训练与评估。
- "(5) Deploy and monitor (drift), retrain, and capitalize (document, reuse data and models)." → 部署、监控、沉淀经验。课件的完整流程是：data collection and indexing → modeling → preprocessing（data quality, filtering, information compression）→ training → **evaluation** → **monitoring** → **capitalization** → learning-to-learn，这里五步把它们都覆盖了。

### 9.7 Which points need attention because of the time dimension in the data? 由于数据带有时间维度，需要注意哪些问题？ ★

考过：[2020 B4–B5](../Exam_2020_zh.md)

**先懂这些：** 随机打乱划分为什么会泄漏未来信息——[作业一第 4 题：数据划分](../../Exercises/Assignment1/guide/04_data_splitting.md)。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **No leakage from the future**: split by time (rolling / expanding window), and compute features, scaling and thresholds on the past only; in production, future temperature is a forecast.
(2) **Seasonality**: daily, weekly and yearly cycles, holidays.
(3) **Autocorrelation**: points 10 minutes apart are not independent, so random CV is too optimistic.
(4) **Drift**: monitor and retrain. **Evaluate** with precision / recall / F1 for the rare peaks (RMSE for consumption), against a naive baseline (same hour yesterday).

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

