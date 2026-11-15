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
Expected squared error = **bias²** + **variance** + **Bayes error** (noise); for least squares with $d$ parameters, the variance averaged over the training inputs is $\sigma^2 d/n$.
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

- "Expected squared error = bias² + variance + Bayes error (noise); for least squares with $d$ parameters, the variance averaged over the training inputs is $\sigma^2 d/n$." → 总期望平方误差＝偏差平方＋方差＋Bayes 误差（不可消噪声）；用 $d$ 个参数的最小二乘时，方差项在训练输入上取平均后等于 $\sigma^2 d/n$（课件：高斯噪声线性模型）：参数越多方差越大，样本越多方差越小。
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
(1) **controls complexity** (Occam's razor): more bias but less variance, so less overfitting ($\lambda$ sets the balance);
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
- "The penalty: (1) controls complexity (Occam's razor): more bias but less variance, so less overfitting ($\lambda$ sets the balance);" → 作用一：控制复杂度（奥卡姆剃刀）：偏差变大、方差变小，从而减轻过拟合；划不划算取决于 $\lambda$（$\lambda$ 太大会欠拟合）。
- "(2) regularizes ill-posed problems (Tikhonov; Ridge: $X^TX+\lambda I$ is invertible);" → 作用二：让病态问题变得规则可解（Tikhonov 正则化；Ridge 里加 $\lambda I$ 保证矩阵可逆）。
- "(3) adds structure, e.g. $\ell_1$ gives sparsity. $\lambda$ is a hyperparameter chosen by CV." → 作用三：加入结构偏置（如 $\ell_1$ 带来稀疏），其中 $\lambda$ 是靠交叉验证选的超参数。

### 1.5 Are generalization error and overfitting relevant for clustering? 泛化误差和过拟合的概念适用于聚类吗？ ★

考过：[2019 Q8](../Exam_2019_zh.md)

**先懂这些：** ① k-means 目标（簇内平方和）随 $k$ 单调下降——[Lab4](../../Exercises/Lab4/Lab4_zh.ipynb) 簇数选择部分；② 与 7.4（如何选簇数）一起复习。

**最终版答案（背诵版 EN，≤5 行）：**
**Yes.** The optimal inertia never increases when $k$ grows (it is 0 when $k=N$ distinct points).
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

- "Yes. The optimal inertia never increases when $k$ grows (it is 0 when $k=N$ distinct points)." → 适用；**最优**惯性随 $k$ 增大单调不增（$k=N$ 且点互不相同时为 0）。注意说的是最优解：k-means 实际跑出的局部解不一定随 $k$ 单调。
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
The **0–1 loss** is not convex and not continuous: minimizing the empirical 0–1 loss is **NP-hard** in general.
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

- "The 0–1 loss is not convex and not continuous: minimizing the empirical 0–1 loss is NP-hard in general." → 0–1 损失不凸也不连续，一般情况下直接最小化训练集上的 0–1 损失是 NP 难的（数据线性可分时例外，可以高效求解）。
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
Example: the **maximum depth** of a tree. The training error cannot choose it (a deeper tree never has a higher training error).
**K-fold cross-validation**: for each value in a grid, train on K−1 folds, validate on the held-out fold, rotate over the K folds and average.
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

- "Example: the maximum depth of a tree. The training error cannot choose it (a deeper tree never has a higher training error)." → 例子是决策树最大深度；训练误差没法用来选它（树越深，训练误差只会不变或变小）。
- "K-fold cross-validation: for each value in a grid, train on K−1 folds, validate on the held-out fold, rotate over the K folds and average." → K 折交叉验证做法：对网格里每个候选值，在 $K-1$ 折上训练、在留出的那一折上验证，轮换 $K$ 次让每一折都当一次验证集，再求平均。
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
**Yes**, it is a **bi-level problem**: $\min_\lambda\hat L_{\text{val}}(\hat\theta(\lambda))$.
But the objective is usually a **black box**: no gradient available, **expensive**, **noisy**, often **non-convex**, mixed discrete / continuous variables.
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

- "Yes, it is a bi-level problem: $\min_\lambda\hat L_{\text{val}}(\hat\theta(\lambda))$." → 可以，它是一个双层优化问题（外层调 $\lambda$ 最小化验证误差，内层学 $\hat\theta(\lambda)$）。
- "But the objective is usually a black box: no gradient available, expensive, noisy, often non-convex, mixed discrete / continuous variables." → 外层目标通常是个黑盒：一般拿不到梯度、评估昂贵、有噪声、往往非凸、离散与连续变量混杂。
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
**Hyperparameters**: **max depth**, max number of leaves, **min samples per leaf / per split**, min impurity decrease, split **criterion** (Gini, entropy, MSE), **pruning** parameter $\lambda$ (often called α).
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

- "Hyperparameters: max depth, max number of leaves, min samples per leaf / per split, min impurity decrease, split criterion (Gini, entropy, MSE), pruning parameter $\lambda$ (often called α)." → 决策树的六大超参数清单。
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
**Partly.** Overfitting: limit the depth, min leaf size, **pruning** ($\lambda$ by CV).
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

- "Partly. Overfitting: limit the depth, min leaf size, pruning ($\lambda$ by CV)." → 部分可以克服：防过拟合靠限深度、设最小叶子样本数和剪枝。
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
But the **training error alone cannot choose** the number of leaves (more leaves never increase it).
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
- "But the training error alone cannot choose the number of leaves (more leaves never increase it)." → 但光靠训练误差选不出最佳叶子数（它永远偏爱更多叶子）。
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
Matrix form (if $X$ has full column rank): $\hat\beta=(X^TX)^{-1}X^Ty$. Error: $\text{RMSE}=\sqrt{\text{RSS}/N}$.
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
- "Matrix form (if $X$ has full column rank): $\hat\beta=(X^TX)^{-1}X^Ty$. Error: $\text{RMSE}=\sqrt{\text{RSS}/N}$." → 多维矩阵解与 RMSE 误差公式。
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
The coefficients **shrink towards 0**: more bias, less **variance** (a good $\lambda$ lowers the test error).
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
- "The coefficients shrink towards 0: more bias, less variance (a good $\lambda$ lowers the test error)." → 系数向 0 收缩：偏差变大、方差变小；$\lambda$ 选得好时总误差下降，$\lambda$ 太大则欠拟合。
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
With 4 points (distinct $x_i$), try degrees **1**, **2** and **3** (at most 4 parameters).
Degree **3** (4 parameters) is the most complex: it **interpolates** the 4 points (zero training error); higher degrees are underdetermined.
In practice, choose a low degree by validation.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

刚用 4 个点算完一条直线（见 2021 Ex2 前一问），题目接着问：如果觉得直线太简单，在这 **4 个数据点**上还能试哪些更复杂的**多项式模型**？其中**最复杂但仍然有意义**的是几次多项式？

**② 需要的工具**

- **为什么抛物线／三次曲线依然叫“线性模型”？** 机器学习里说“线性模型”，指的是对**待学参数 $\beta$ 是线性的**（$\beta$ 只做加权乘法，不互相相乘也不套非线性函数），并不要求画出来的图像是直的！只要把 $x, x^2, x^3$ 当成几个现成特征塞进矩阵 $X$，多项式回归依然直接用 **OLS 正规方程**求解。
- **参数个数规律**：$p$ 次多项式 $\beta_0 + \beta_1 x + \dots + \beta_p x^p$ 一共有 **$p+1$ 个参数**（别忘了常数项 $\beta_0$！）。
- **两点定直线、三点定抛物线、四点定三次曲线（插值）**：当 $p+1 = N$（参数个数刚好等于样本点数，且 $x_i$ 互不相同）时，存在**唯一一条**曲线严格穿过全部 $N$ 个点——这叫**插值（interpolation）**，训练误差恰好等于 0。
- **自由度 $= N - (p+1)$**：样本数减掉参数个数，代表“还剩多少多余的样本用来检验你到底学对没有、没白拟合噪声”。

**③ 一步一步**

1. **先把多项式放回 OLS 框架**：对特征 $(1, x, x^2, \dots, x^p)$ 做线性回归即可。
2. **在 $N=4$ 个点上能试哪些比直线更复杂的模型？** 可以尝试 **2 次多项式（抛物线，3 个参数）** 和 **3 次多项式（4 个参数）**。（当然如果有明显弯曲趋势，2 次很常用。）
3. **最复杂且有唯一确定解的是几次？—— 3 次多项式！**
   - 3 次多项式有 $3+1 = 4$ 个参数，正好等于 4 个数据点；
   - 只要 4 个点的横坐标 $x_i$ 互不相同，它就能严丝合缝穿过每一个点（**精确插值**，训练误差 $\text{RMSE}=0$）。
4. **为什么 4 次及以上没有意义？** 4 次多项式有 5 个参数、5 次有 6 个参数……未知数比 4 个点方程还多，属于**欠定方程组**（$d>N$，$X^TX$ 不可逆），有无穷多条不同曲线都能完美穿过这 4 个点，数据根本决定不了选哪条！
5. **注意“有唯一解”不代表“适合用来预测”**：3 次多项式把 4 个自由度全花光了（自由度 $=4-4=0$），训练误差为 0 只是把这 4 个点连同噪声一并背了下来，点与点之间会剧烈扭曲。实际使用时应在验证数据上优先选更简单的模型（比如 1 次或 2 次）。

**④ 小例子（数清参数与自由度）**

对比 $N=4$ 个点上各次多项式的命运：

| 多项式次数 $p$ | 参数个数 $p+1$ | 自由度 $4-(p+1)$ | 能否继续往里加？ |
|---|---|---|---|
| 1 次（直线） | 2 | 2 | 常用基线 |
| **2 次（抛物线）** | **3** | **1** | **可尝试（有余地检验趋势）** |
| **3 次（三次曲线）** | **4** | **0** | **最复杂上限：唯一插值，训练误差=0** |
| $\ge 4$ 次 | $\ge 5$ | 欠定 | **无意义（无穷多解，模型选不定）** |

**⑤ 常见误区**

- **误区 1：看到 $x^2, x^3$ 就说多项式回归是非线性回归、不能用 OLS**。它对**参数 $\beta$ 是线性的**，依然是正宗 OLS。
- **误区 2：以为 3 次多项式能让训练误差变成 0，所以就是最佳模型**。训练误差为 0 往往意味着严重过拟合了噪声。
- **误区 3：数错次数和参数个数的关系**——记住 **$p$ 次多项式有 $p+1$ 个参数**，4 个点对应最高 **3 次**（不是 4 次！）。

**⑥ 对照最终版**

- "Polynomial regression is still linear in the parameters (OLS on $1,x,x^2,\dots$)." → 多项式回归对参数仍是线性的（在 $1,x,x^2,\dots$ 上做 OLS）。
- "With 4 points (distinct $x_i$), try degrees 1, 2 and 3 (at most 4 parameters)." → 4 个点（$x_i$ 互不相同）上可以尝试 1、2、3 次：参数个数不能超过 4。
- "Degree 3 (4 parameters) is the most complex: it interpolates the 4 points (zero training error); higher degrees are underdetermined." → 3 次（4 个参数）是最复杂上限：它精确插值这 4 个点（训练误差为 0）；更高次就欠定了。
- "In practice, choose a low degree by validation." → 实践中要用验证选低次模型。

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

深度神经网络有成千上万甚至上亿个参数，而且整个优化地形弯弯曲曲、不是简单的碗状。到底采用什么优化策略，才能把这套参数有效地训（课程里也叫“校准 calibrate”）出来？

**② 需要的工具**

- **经验风险**：训练集上的平均损失（加正则化惩罚），训练的目标就是尽量把它压低（见 2.2）。
- **梯度下降（Gradient Descent）**：把损失函数想成一座高低起伏的山谷，**梯度**指向“上坡最陡的方向”，于是每次朝**负梯度（下坡最陡）**挪一小步：$\theta_{t+1} = \theta_t - \eta\nabla L(\theta_t)$，其中 $\eta$ 叫**学习率（步长）**。
- **小批量随机梯度下降（mini-batch SGD）**：数据集动辄百万条，每走一步都把百万条全算一遍太慢了；于是每步只随机抓一小把样本 $B_t$（比如 64 或 128 条）估个大概下坡方向就立刻迈步——单步计算量和总样本数 $n$ 无关，非常快！
- **Adam 等自适应优化器**：给 SGD 加上“惯性动量”并按每个参数各自调步长，通常比原生 SGD 收敛更快更稳。
- **反向传播（Backpropagation）**：不是更新参数的算法，而是**高效算梯度的工具**！从输出层的误差出发，利用微积分里的**链式法则**，从后往前一层层把“损失对每个权重的影响（偏导数）”传回来算清。
- **非凸地形与早停（Early Stopping）**：深度学习的损失地形有无数大大小小的山谷和鞍点（**非凸**），谁也不能保证找到全球最低的谷底；因此工程上常靠监控验证集误差，一旦发现验证误差不再下降甚至开始反弹（过拟合信号）就立刻刹车停训（**早停**）。

**③ 一步一步（标准训练循环）**

1. **随机初始化权重**：先给所有权重撒一组合适的初始随机数（不能全设为 0）。
2. **前向传播（算预测与损失）**：从训练集抽一小批样本 $B_t$，输入网络从第一层一路算到输出层，得出预测和平均损失。
3. **反向传播（用链式法则算梯度）**：从最后一层损失倒着往回乘偏导数，一次性算出当前小批量上损失对每一个参数 $\theta$ 的梯度。
4. **优化器迈出一步（更新权重）**：按 mini-batch SGD（或 Adam）公式更新所有参数：
   $$\theta_{t+1}=\theta_t-\eta_t\nabla_\theta\frac1{|B_t|}\sum_{i\in B_t}\ell(f_\theta(x_i),y_i)$$
5. **一轮轮循环＋早停**：换下一小批重复第 2–4 步，把全体样本过一遍叫一个 **epoch（轮）**；借助调好的**学习率（及其衰减调度）、批大小、初始化**和**早停**，往往能稳定走到泛化很好的解（虽无全球最优保证，但随机噪声反而帮助跳出不好的平坦鞍点）。

**④ 小例子（手算一步前向＋反向传播＋更新）**

考虑一个极简的两层网络 $\hat y = w_2\cdot\text{ReLU}(w_1 x)$，其中激活函数 $\text{ReLU}(z)=\max(0,z)$（正数原样通过、负数变 0）。已知 $x=1,\ y=5$，当前权重 $w_1=2,\ w_2=3$，用平方损失 $L=(\hat y-y)^2$：

1. **前向传播**：隐藏层 $h=\text{ReLU}(2\times 1)=2$；输出 $\hat y=3\times 2=6$；损失 $L=(6-5)^2=\mathbf{1}$。
2. **反向传播（链式法则逐层乘）**：
   - 先算输出对损失的影响：$\frac{\partial L}{\partial\hat y} = 2(\hat y-y) = 2(6-5) = 2$；
   - 传给外层权重：$\frac{\partial L}{\partial w_2} = \frac{\partial L}{\partial\hat y}\cdot h = 2\times 2 = \mathbf{4}$；
   - 传到隐藏层：$\frac{\partial L}{\partial h} = \frac{\partial L}{\partial\hat y}\cdot w_2 = 2\times 3 = 6$；
   - 再穿过 ReLU（$2>0$ 导数为 1）传给里层权重：$\frac{\partial L}{\partial w_1} = 6\times 1\times x = \mathbf{6}$。
3. **SGD 更新一步**（取学习率 $\eta=0.05$）：
   $w_2 \leftarrow 3 - 0.05\times 4 = \mathbf{2.8}$，$w_1 \leftarrow 2 - 0.05\times 6 = \mathbf{1.7}$。
4. **验算成果**：新预测 $\hat y = 2.8\times 1.7 = 4.76$，新损失 $(4.76-5)^2 = \mathbf{0.0576}$——走一步损失直接从 1 暴降到 0.0576！

**⑤ 常见误区**

- **误区 1：把“反向传播”当成优化器**。反向传播只负责**算梯度**，真正决定怎么改权重的是优化器（SGD、Adam 等）。
- **误区 2：忽视步长与随机设置**。学习率 $\eta$ 太大时一步跨过山谷导致损失震荡爆炸；太小时半天走不动。

**⑥ 对照最终版**

- "We minimize the empirical risk with mini-batch SGD (or Adam): [更新公式]" → 用小批量 SGD 或 Adam 最小化经验风险，并写出参数更新公式。
- "The gradient is computed by backpropagation (chain rule)." → 梯度通过反向传播（链式法则）高效算出。
- "The problem is non-convex: no global guarantee. Learning rate, batch size, initialization and early stopping matter." → 问题是**非凸**的（不保证全局最优），因此学习率、批大小、初始化和早停都很关键。

### 6.2 How is numerical optimization achieved in machine learning methods? Give an example. 机器学习方法如何做数值优化？举一个例子。 ★

考过：[2023.11 Ex1 Q8](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① OLS 闭式解与 QR／SVD——[第二课 · 线性模型与最小二乘](../../Lectures/02_LM/01_linear_models_and_least_squares.md)；② Lasso 的三种求解算法——[第四课 · LASSO 估计的优化方法](../../Lectures/04_UL_zh.md)；③ SVM 的对偶二次规划——[第五课 · 对偶表述](../../Lectures/05_NLM_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
Write the objective (loss + penalty), then pick a solver:
**closed form** (OLS, Ridge: QR / SVD), **gradient / Newton** (logistic regression), **coordinate descent / proximal** (Lasso), **SGD** (neural networks).
Example: $\ell_2$-regularized logistic regression, $w_{t+1}=w_t-\eta\nabla L(w_t)$ until the gradient is small; it is strictly **convex**, so with a suitable step size it converges to the **global minimum**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

机器学习训练模型时，写完“损失＋惩罚”的公式只是第一步——到底怎么靠计算机真把最优参数算出来（**数值优化**）？不同问题怎么选求解器？请举一个具体例子。

**② 需要的工具**

- **目标函数**：写出来的“经验损失＋惩罚项”，我们要让它尽量小（见 2.2）。
- **“四象限”挑求解器看两个性质**：
  - **凸 vs 非凸**（见 2.5）：凸函数是一整口大碗，局部极小就是全局极小；非凸函数凹凸不平，到处是假谷底和**鞍点**（像马鞍正中心：左右看是谷底，前后看是山顶，斜率为 0 却不是极小值）。
  - **光滑 vs 非光滑**：光滑函数处处圆润可导；非光滑函数（比如带绝对值的 $\ell_1$ 惩罚）有尖角，在尖角处求不了导。
- **闭式解与 QR / SVD**：有现成公式直接一步算出答案（如 OLS / Ridge）。实际数值计算时一般**不硬算矩阵逆** $(X^TX)^{-1}$（容易因精度舍入炸掉），而是用 **QR 分解或 SVD（奇异值分解）** 稳稳地解线性方程。
- **梯度下降**：$w_{t+1}=w_t-\eta\nabla L(w_t)$，沿着下坡最陡方向走一小步，$\eta$ 是步长（学习率）。
- **牛顿法**：不仅看一阶斜率，还看二阶弯曲程度（曲率），一步迈得更准，往往迭代十来次就收敛。

**③ 一步一步（挑求解器的“看菜吃饭”法则）**

1. **先写好优化目标**：明确要最小化的 `损失 + 惩罚`。
2. **按目标长相选最合适的求解器**：
   - **有线性闭式解**（OLS、Ridge）：直接用 **QR 或 SVD** 求解，精确又不用迭代；
   - **光滑＋凸**（逻辑回归）：用**梯度下降**、**牛顿法**或拟牛顿法（如 L-BFGS）；
   - **非光滑＋凸**（Lasso、SVM）：Lasso 用**坐标下降**、**LARS** 或**近端梯度法（软阈值）**（见 5.6）；SVM 把带约束问题转成对偶后做**二次规划（QP）**；
   - **大规模非凸**（深度神经网络）：用**小批量 SGD / Adam** 配反向传播算梯度（见 6.1）。
3. **迭代方法要注意“步长”和“何时停”**：步长 $\eta$ 选太大容易跨过头震荡甚至发散（光滑凸函数理论要求 $\eta \le 1/L$，即不超过局部弯曲度允许的上限）；当梯度小到接近 0（$\|\nabla L(w_t)\|<\varepsilon$）或目标几乎不再下降时停止。
4. **知道凸优化的“额外前提”**：光有凸性只说明“局部极小＝全局极小”，要让梯度下降真的收敛到全局极小，还必须满足**最小值确实存在**＋**步长合适**（例如加上 $\ell_2$ 正则让函数**严格凸**，保证唯一极小值存在）。非凸问题没有全局保证，可能停在局部极小或鞍点附近。

**④ 小例子（手算一步步滑向碗底的梯度下降）**

想最小化简单凸函数 $L(w)=(w-3)^2$，导数是 $\nabla L(w) = 2(w-3)$。从 $w_0=0$ 出发，取步长 $\eta=0.25$：

- **第 1 步**：$w_0=0$ 处斜率 $= -6$ → $w_1 = 0 - 0.25\times(-6) = \mathbf{1.5}$；
- **第 2 步**：$w_1=1.5$ 处斜率 $= -3$ → $w_2 = 1.5 - 0.25\times(-3) = \mathbf{2.25}$；
- **第 3、4 步**：$w_3 = \mathbf{2.625}$，$w_4 = \mathbf{2.8125}$……

每走一步，离真碗底 $3$ 的距离都精确砍半！实际考场举**带 $\ell_2$ 正则的逻辑回归**做例子最稳：目标严格凸且存在唯一最小值，只要步长合适、迭代到梯度足够小，就保证收敛到全局最优。

**⑤ 常见误区**

- **误区 1：以为“所有机器学习都在跑梯度下降”**。OLS / Ridge 有闭式解（QR/SVD），Lasso 有专门的坐标下降／软阈值，乱用普通梯度下降反而又慢又卡尖角。
- **误区 2：以为“只要函数是凸的，梯度下降就一定能收敛到一个有限最优解”**。反例：当两类数据**线性可分**时，**不加正则的逻辑回归**虽然也是凸函数，但压根没有有限最小值（权重 $\|w\|$ 会一路冲向正无穷、损失只是逼近 0）；加上 $\ell_2$ 正则变成严格凸之后，才保证有限唯一极小值存在！
- **误区 3：以为非凸问题至少一定会停在局部极小**。也可能卡在平缓的**鞍点**附近。

**⑥ 对照最终版**

- "Write the objective (loss + penalty), then pick a solver:" → 先写出“损失＋惩罚”目标，再挑选求解器。
- "closed form (OLS, Ridge: QR / SVD), gradient / Newton (logistic regression), coordinate descent / proximal (Lasso), SGD (neural networks)." → 四大类代表方法与对应求解器。
- "Example: $\ell_2$-regularized logistic regression, $w_{t+1}=w_t-\eta\nabla L(w_t)$ until the gradient is small; it is strictly convex, so with a suitable step size it converges to the global minimum." → 具体例子（$\ell_2$ 正则化逻辑回归）：严格凸保证唯一最小解，步长合适即收敛到全局最优。

### 6.3 What is the mathematical space of functions of deep feedforward neural networks? 深度前馈神经网络对应怎样的函数空间？ ★

考过：[2023.11 Ex1 Q6](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** ① 深度前馈网络的定义——[第六课 · 深度学习：主要概念介绍（深度前馈网络）](../../Lectures/06_DL_zh.md)；② 单层网络是通用逼近器——[第六课 · 1. 通用逼近器的存在性定理](../../Lectures/06_DL_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
For a fixed architecture: $\mathcal H=\{x\mapsto A_{L+1}\circ\sigma_L\circ A_L\circ\dots\circ\sigma_1\circ A_1(x)\}$, with $A_\ell(u)=W_\ell u+b_\ell$ and $\sigma$ = ReLU, tanh…
It is a **parametric family of compositions**, **non-linear** in $\theta$ and **not a vector space**.
**Universal approximation**: with enough neurons, it can approximate any continuous function on a compact set.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

前几章我们学过线性模型（所有直线/超平面的集合）和决策树（所有方格子分区的集合）。那深度前馈神经网络所有可能学出来的函数，凑在一起是一个什么样的"函数集合（假设空间 $\mathcal H$）"？它有什么数学性质？

**② 需要的工具**

- **仿射映射（Affine map）$A_\ell(u)=W_\ell u+b_\ell$**：把上一层的输出做"加权求和 + 偏置"的线性变化（矩阵乘法 $W_\ell u$ 再加偏移向量 $b_\ell$）。
- **激活函数 $\sigma_\ell$**：逐个数字单独施加一个**非线性**函数，比如 ReLU（$\max(0,z)$，把负数砍成 0）或 $\tanh$。没有它，多层线性叠加还是线性，等于白搭。
- **函数复合 $\circ$**：$f\circ g(x)=f(g(x))$，意思是像工厂流水线一样，先经过 $g$ 加工，再把加工结果喂给 $f$。
- **向量空间（Vector space）**：集合里任意两个函数相加、或者乘以一个常数，结果必须**仍然在原来的集合里**（比如线性函数空间就是向量空间）。
- **有界闭集（Compact set）**：可以理解成"范围有限、带边界、不跑到无穷远的一块区域"（比如 $[0,1]^d$）。

**③ 一步一步**

1. **先把网络结构固定下来**：比如一共有 $L$ 个隐藏层，第 $\ell$ 层有几个神经元、用什么激活函数 $\sigma_\ell$ 都提前定死。
2. **写出它能表示的所有函数 $\mathcal H$**：数据 $x$ 像过流水线一样，先过一层仿射变换 $A_1$，再过一次激活 $\sigma_1$，再过 $A_2$、$\sigma_2$……最后过输出层 $A_{L+1}$：
   $$\mathcal H=\{x\mapsto A_{L+1}\circ\sigma_L\circ A_L\circ\dots\circ\sigma_1\circ A_1(x)\}$$
   所有权重矩阵和偏置凑成参数 $\theta=\{(W_\ell,b_\ell)\}_{\ell=1}^{L+1}$。每换一组参数 $\theta$，就得到 $\mathcal H$ 里的一个具体函数。
3. **两大结构性质**：
   - **对参数 $\theta$ 是非线性的**：因为一层的输出被下一层矩阵乘过再过非线性 $\sigma$，参数之间互相乘在一起、套在激活函数里。所以训练损失对 $\theta$ 不是凸碗（非凸），必须靠梯度下降慢慢找局部极小值。
   - **它一般不是向量空间**：假设规定一个隐藏层只有 $K=1$ 个 ReLU 神经元，能表示一个折角函数 $f_1(x)=\max(0,x)$（折点在 0）和另一个 $f_2(x)=\max(0,x-1)$（折点在 1）。把两个加起来 $f_1(x)+f_2(x)$ 有两个折点，通常需要 $2$ 个神经元才能拼出来，塞不回"只有 1 个神经元"的结构里！所以两个同结构网络相加，往往跑出 $\mathcal H$ 之外。
4. **但表达能力极强（通用逼近定理，Universal approximation）**：只要允许增加神经元个数（哪怕只有 1 个隐藏层，只要足够宽），在任意有界闭集上，神经网络就能以任意小的误差逼近任何连续函数（就像用足够多的小折线段可以贴合任何光滑曲线）。而"深度"的好处是，很多复杂函数用深层结构只需少得多的参数就能拼出来（见 6.5）。

**④ 小例子**

输入一张 $28\times28=784$ 像素的手写数字图，经 1 个 100 神经元的隐藏层（ReLU），输出 10 个分类得分：
- 第 1 层 $A_1$：权重 $W_1$ 有 $784\times 100$ 个数，偏置 $b_1$ 有 $100$ 个数；
- 输出层 $A_2$：权重 $W_2$ 有 $100\times 10$ 个数，偏置 $b_2$ 有 $10$ 个数；
- 总参数共 $784\times 100+100+100\times 10+10=79\,510$ 个。
这 $79\,510$ 个实数每取一组值，就唯一确定 $\mathcal H$ 里的一个映射函数；而无论你怎么调这 $79\,510$ 个数，这个函数集合对参数都不是线性的，两个这种 100 神经元的网络直接相加也通常不再能用 100 个神经元表示。

**⑤ 常见误区**

- 误以为神经网络的函数空间是"所有函数"，或者像多项式空间那样是向量空间：一旦固定网络结构 $\mathcal H$，它只是有限个参数张成的非线性参数族，相加并不封闭。
- 误以为通用逼近定理保证了"随便训练就能学到完美函数"：定理只保证**存在**这样一组参数（近似误差可小），但有限样本会不会过拟合（估计误差）、梯度下降能不能找到那组参数（优化误差），它并不保证。

**⑥ 对照最终版**

- `"For a fixed architecture: \mathcal H=\{x\mapsto A_{L+1}\circ\sigma_L\circ A_L\circ\dots\circ\sigma_1\circ A_1(x)\}, with A_\ell(u)=W_\ell u+b_\ell and \sigma = ReLU, tanh…"` → 固定结构下，函数空间就是仿射映射和激活函数交替复合。
- `"It is a parametric family of compositions, non-linear in \theta and not a vector space."` → 两大数学性质：参数化复合族、对 $\theta$ 非线性、不是向量空间。
- `"Universal approximation: with enough neurons, it can approximate any continuous function on a compact set."` → 通用逼近性质：神经元够多时在有界闭集上可逼近任意连续函数。

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

训练神经网络时，哪些数字是电脑自己学出来的，哪些必须人类在开练前拍板定好（也就是**超参数**）？

**② 需要的工具**

- **参数 vs 超参数**（见 3.4）：网络里面的权重 $W$ 和偏置 $b$ 是靠训练数据算出来的，叫**参数**；在点击"开始训练"之前由人指定、用来控制网络长什么样以及怎么练的设置，叫**超参数**。
- **权值衰减（Weight decay）**：训练时给太大的权重 $W$ 罚款（就像 $\ell_2$ 正则，见 1.4），逼着权重保持温和，别走极端。
- **Dropout（随机失活）**：每次喂数据时随机把一部分神经元临时"捂住嘴"，不让网络死抱少数几个特征偷懒。
- **早停（Early stopping）**：一边练一边偷看验证集分数，一旦发现"训练集还在变好、验证集开始变差（开始死记硬背了）"，立刻喊停。
- **批大小（Batch size）与轮数（Epochs）**：每次抓多少张图算一回梯度叫 `batch size`；把整套训练集从头到尾刷完一遍叫 1 个 `epoch`。

**③ 一步一步（分成三大类记，绝对不漏）**

1. **先分清谁不是超参数**：权重 $W$ 和偏置 $b$ 是训练自动学出来的，**不是**超参数。
2. **第一类：决定"网络长什么样"——结构超参数（Architecture）**：
   - **深度（depth）**：有多少层；**宽度（width）**：每层有多少个神经元；
   - **激活函数（activations）**：用 ReLU 还是 $\tanh$ 等；
   - **层的类型（layer types）**：用普通全连接层、看图像用的卷积层（还有卷积核大小、步长），还是处理序列用的循环层等。
3. **第二类：决定"怎么防死记硬背"——正则化超参数（Regularization）**：
   - 权值衰减系数 $\lambda$、Dropout 关掉神经元的比例（比如 $0.2$ 或 $0.5$）、早停的耐心等待轮数（以及图像旋转/裁剪等数据增强）。
4. **第三类：决定"怎么学得快又稳"——优化超参数（Optimization）**：
   - 优化器（用普通 SGD 还是 Adam）、**学习率（learning rate）**和学习率衰减方式、**批大小（batch size）**、总训练轮数（epochs）、权重最初怎么随机初始化（initialization）。
5. **去哪儿调这些超参数**：绝对不能在测试集上挑（见 3.1/3.2），必须在**验证集**上对比筛选（常用随机搜索或贝叶斯优化，见 3.3）。代价通常很高，因为每换一组超参数，几乎都要从头完整训练一遍网络。

**④ 小例子**

哪怕只挑 3 个超参数试试：
- 隐藏层数选 `{2, 3, 4}`（3 种）
- 学习率选 `{0.1, 0.01, 0.001}`（3 种）
- Dropout 比例选 `{0, 0.5}`（2 种）

光是网格组合就有 $3\times3\times2=18$ 种方案——如果练一次网络要 1 小时，找出哪组在验证集上最好就得跑 18 小时。

**⑤ 常见误区**

- 把网络里的权重 $W$ 和偏置 $b$ 也当成超参数（错，它们是**学出来的参数**）。
- 只记得"层数、神经元数"是超参数，忘了优化器、学习率、批大小和训练轮数这些**训练过程设置**也是超参数——实际调参时学习率往往是最关键的那个。

**⑥ 对照最终版**

- `"Weights and biases are learned. Hyperparameters:"` → 先把学出来的参数和人工超参数划清界限。
- `"architecture (depth, width, activations, layer types);"` → 第一组：网络结构。
- `"regularization (weight decay, dropout, early stopping);"` → 第二组：正则化。
- `"optimization (optimizer, learning rate, batch size, epochs, initialization). Tuned on a validation set."` → 第三组：优化设置；最后说明在验证集上调节。

### 6.5 What is the fundamental difference between deep and shallow learning? 深度学习与浅层学习的根本区别是什么？ ★

考过：[2020 A6](../Exam_2020_zh.md)

**先懂这些：** ① [第六课 · 浅层与深度学习：Vapnik 与 LeCun；从浅层到深层网络](../../Lectures/06_DL_zh.md)；② 浅层方法如何用显式惩罚控制复杂度——[第一课 · 算法家族、正则化与处理流程](../../Lectures/01_intro/02_algorithms_and_pipeline.md)。

**最终版答案（背诵版 EN，≤5 行）：**
**Shallow** learning: **hand-made features** (or a fixed kernel) + **explicit (Tikhonov) regularization** $\min\hat L_n(h)+\lambda\,\text{pen}(h)$; the penalty controls the variance; often convex.
**Deep** learning stacks **many non-linear layers** and **learns the features itself**, end to end; it is a **universal approximator** (almost zero bias).
**No penalty term**: non-convex (SGD), **implicit regularization** (weight decay, dropout, early stopping…), needs **much data and computation**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

同样是机器学习，为什么以前叫"浅层学习（Shallow learning）"，现在叫"深度学习（Deep learning）"？它们的区别绝不只是"层数变多了"，究竟**根本区别**在哪？

**② 需要的工具**

- **浅层学习**：只有 1～2 层简单变换的模型，比如线性模型、逻辑回归、SVM（核方法）、决策树、随机森林。
- **人工特征（Hand-made features）**：算法不懂原始像素或文字，必须由人类专家先写规则提取特征（比如从照片里先算出边缘数量、平均亮度），再喂给模型。
- **端到端表示学习（End-to-end feature learning）**：直接把原始像素/声音/文本扔进模型，前面几层自己学会提取特征，最后一层直接输出答案，一条龙全靠数据学出来。
- **显式正则化（Explicit regularization）**：直接在优化目标函数后面明明白白加上一条罚款项 $\min_h \hat L_n(h)+\lambda\,\text{pen}(h)$（也叫 Tikhonov 正则化，见 1.4），靠调节 $\lambda$ 压住方差、防过拟合。
- **隐式正则化（Implicit regularization）**：目标函数里往往没有专门的复杂惩罚项（或即使不用），但训练过程和技巧本身就像"无形的手"在限制复杂度——比如 SGD 自带的噪声、提前喊停（早停）、随机关掉神经元（Dropout）、权值衰减，以及网络结构本身的限制。

**③ 一步一步（从 3 个核心维度对比）**

| 对比维度 | 浅层学习（Shallow） | 深度学习（Deep） |
|---|---|---|
| **特征谁来做** | 人手工设计特征，或选一个固定核函数 | 堆叠很多非线性层，**端到端自动学出层次特征** |
| **怎么防过拟合** | **显式正则化**：$\min_h \hat L_n(h)+\lambda\,\text{pen}(h)$，惩罚项直接管住方差 | **无复杂显式惩罚**（或主要靠**隐式正则化**：早停、Dropout、SGD 噪声、权值衰减等） |
| **函数空间与优化** | 函数空间较简单，近似误差可能较大；**经常是凸问题**（唯一最低谷，理论好分析） | **通用逼近器**（几乎零偏差/近似误差）；但**非凸**（用 SGD 找局部极小值），极度依赖**海量数据和强算力** |

用两句话总结根本转变：
1. **从"人造特征 + 浅层分类器"变成"自动学多层特征 + 端到端优化"**；
2. **从"凸优化 + 显式 Tikhonov 惩罚控方差"变成"非凸高容量网络 + 隐式正则化技巧与大数据控方差"**。

**④ 小例子**

做"猫狗照片识别"：
- **浅层做法**：工程师自己先设计程序从照片里算出一堆固定数字（颜色直方图、边角方向统计），再交给带 $\ell_2$ 惩罚的线性 SVM 去分。哪怕图片再多，前面算特征的规则也是死板的。
- **深度做法**：直接把原始 RGB 像素矩阵喂给多层卷积网络——第 1 层自己学会看斜线和色块，中间层自己拼出耳朵、胡须，深层自己认出猫脸，最后直接判断是猫还是狗。如果网络参数有几百万个，就靠大数据、SGD、Dropout 和早停来防止它把训练集背下来。

**⑤ 常见误区**

- 只答"浅层只有 1 层，深度有很多层"：这只是表面现象，核心得分点是**特征是否自动学（hand-made features vs learns features end to end）**、**函数逼近能力（universal approximator / almost zero bias）**和**正则化机制（explicit Tikhonov vs implicit regularization）**。
- 误以为深度学习不需要防过拟合：它参数多、方差风险其实极大，只是把防过拟合的手段从公式里的显式惩罚转移到了训练技巧（隐式正则化）和大数据上。

**⑥ 对照最终版**

- `"Shallow learning: hand-made features (or a fixed kernel) + explicit (Tikhonov) regularization \min\hat L_n(h)+\lambda\,\text{pen}(h); the penalty controls the variance; often convex."` → 浅层三大特征：手工特征/固定核、显式惩罚控方差、常为凸优化。
- `"Deep learning stacks many non-linear layers and learns the features itself, end to end; it is a universal approximator (almost zero bias)."` → 深度核心优势：多层非线性复合、端到端自学习特征、通用逼近（几乎零偏差）。
- `"No penalty term: non-convex (SGD), implicit regularization (weight decay, dropout, early stopping…), needs much data and computation."` → 深度的代价与机制：非凸需 SGD、靠隐式正则化控方差、吃数据与算力。

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

聚类的典型代表 **k-means 算法**到底想最小化一个什么目标函数？它的每一步是怎么循环跑起来的？请把公式和伪代码写出来。

**② 需要的工具**

- **聚类（Clustering）**：数据**没有标签**（没人告诉你谁属于哪一类），我们要把长得像、离得近的点自动聚成 $k$ 堆。
- **簇中心（Center / Centroid）$c_j$**：第 $j$ 堆点的"代表点"（一共选出 $k$ 个代表 $c_1,\dots,c_k$）。
- **分组标签（Assignment）$z_i$**：记号 $z_i \in \{1,\dots,k\}$ 表示"第 $i$ 个点 $x_i$ 被分到了第几堆"。
- **目标函数——簇内平方和 $J$（Inertia）**：
  $$J=\sum_{i=1}^N\|x_i-c_{z_i}\|^2$$
  每个点先算出"自己到自己所属代表点 $c_{z_i}$ 的距离的平方"，再把所有 $N$ 个点的账加在一起。$J$ 越小，说明每堆点都紧紧抱在自己的代表身边。
- **为什么每堆的最佳代表是平均值（Mean）**：如果分组已经固定，问一个点 $c$ 到这堆点距离平方和什么时候最小？对 $c$ 求导令它为 $0$：$\sum_{i} 2(c-x_i)=0 \implies c=\text{这堆点的平均值}$。这就是它叫 **k-means（k 个均值）** 的原因。

**③ 一步一步（先把问题拆成两半轮流做）**

同时找最佳分组 $z_i$ 和最佳中心 $c_j$ 很难，k-means 的聪明之处是**"轮流固定一边，优化另一边"**：

1. **先选组数 $k$ 并初始化中心**：k-means 不会自己猜有几类，必须人先指定 $k$；然后随机挑 $k$ 个点（或用 **k-means++**，尽量把初始中心挑得彼此分散些）作为最初的 $c_1,\dots,c_k$。
2. **分配步（Assign，固定中心找最近归属）**：对每个点 $x_i$，看它离哪个中心最近，就把它分给谁：
   $$z_i = \arg\min_{j\in\{1,\dots,k\}} \|x_i - c_j\|^2$$
   （中心固定时，每人都挑离自己最近的那个，总平方和 $J$ 一定最省。）
3. **更新步（Update，固定分组算新均值）**：对每一堆 $j=1,\dots,k$，把分到这一堆里的所有点求平均值，作为新的中心 $c_j$（如果某堆不幸空了，处理见 7.9）。
   （分组固定时，平均值能让这一堆内部平方和最小。）
4. **重复直到停止**：不断交替执行第 2、3 步，直到所有点的归属 $z_i$ 不再变化（这时中心也不会再动了，算法停下来）。

**④ 小例子**

有一维数据 $X=\{1,2,3,10,11,12\}$，设 $k=2$，故意挑一个很差的初始中心 $(c_1,c_2)=(1,2)$：

| 步骤 | 当前中心 $(c_1,c_2)$ | 怎么分（看离谁近，中点为界） | 算总平方和 $J$ |
|---|---|---|---|
| 第 1 轮分配 | $(1, 2)$ | 中点 $1.5 \implies \{1\}$ 和 $\{2,3,10,11,12\}$ | $0^2 + (0^2+1^2+8^2+9^2+10^2) = 246$ |
| 第 2 轮更新+分配 | $(1,\; 7.6)$ | 中点 $4.3 \implies \{1,2,3\}$ 和 $\{10,11,12\}$ | $(0^2+1^2+2^2)+(2.4^2+3.4^2+4.4^2)=41.68$ |
| 第 3 轮更新+分配 | $(2,\; 11)$ | 中点 $6.5 \implies \{1,2,3\}$ 和 $\{10,11,12\}$ | $((-1)^2+0^2+1^2)+((-1)^2+0^2+1^2)=4$ |

第 2 轮的中心 $7.6 = (2+3+10+11+12)/5$；第 3 轮重新分配后分组跟第 2 轮完全一样，所以算法立刻停止，输出最终两堆 $\{1,2,3\}$ 和 $\{10,11,12\}$！

**⑤ 常见误区**

- 忘了写目标函数中的**平方** $\|x_i-c_{z_i}\|^2$：不加平方（直接距离之和）最优中心是中位数而不是均值，那就不是 k-means 了。
- 误以为 k-means 能自己决定 $k$，或者一定能找到全局最优：事实上 $k$ 必须人工预设，且结果高度依赖初始中心（见 7.3）。

**⑥ 对照最终版**

- `"Objective: J=\sum_{i=1}^N\|x_i-c_{z_i}\|^2 (within-cluster sum of squares)."` → 必须写出完整带平方和下标的目标函数（簇内平方和）。
- 伪代码四部分：`initialize k centers` → `repeat` 循环里的 `assign`（求最近中心）与 `update`（求组内均值） → `until the assignments do not change`（终止条件）。

### 7.2 Why does the k-means procedure converge? k-means 为什么会收敛？ ★★★

考过：[2023.3 Ex3 a](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex2 a](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 a](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 7.1 的两步分别是在固定一组变量时对另一组变量**精确最小化** $J$（坐标下降）。

**最终版答案（背诵版 EN，≤5 行）：**
Each step **cannot increase** $J$: the nearest center minimizes $J$ in $z$; the **mean** minimizes $J$ in $c$.
$J$ strictly decreases whenever the partition changes (ties broken consistently), and there are only **finitely many partitions** ($\le k^N$), so no partition repeats.
So it **stops in finite time**, at a **fixed point** (a local minimum in practice), not always the global one.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

写循环的时候最怕死循环跑不完。k-means 靠 `until the assignments do not change` 来停，那怎么保证它**一定会越来越稳并最终停下来**，不会永远左右横跳？

**② 需要的工具**

- **坐标下降（Alternating minimization）**：一次同时调好"分法 $z$"和"中心 $c$"太难，于是轮流固定一边、把另一边调到最好。
- **有限个划分（$\le k^N$ 种）**：总共有 $N$ 个点、要放进 $k$ 个篮子里，每个点有 $k$ 种去处，全部分法加起来最多只有 $k^N$ 种（虽然很大，但**个数是有限的**）。
- **下界 $J\ge 0$**：$J$ 是距离平方加总，不可能变成负数，最低只能是 $0$。

**③ 一步一步（像"只能下楼、且台阶总数有限"）**

1. **先看分配步（Assign）——只跌不涨**：中心 $c$ 临时固定。原本点 $x_i$ 在旧中心名下，现在它主动改投**离自己最近**的中心，平方距离 $\|x_i-c_{z_i}\|^2$ 要么不变、要么变小，所以总账 $J$ **绝不会增加**。
2. **再看更新步（Update）——同样只跌不涨**：分法 $z$ 临时固定。把每组中心从"旧中心"移到这组点的**平均值（Mean）**，而均值恰恰是使该组距离平方和最小的点（见 7.1），所以总账 $J$ **也绝不会增加**。
3. **两步都不涨 + 不能为负（$J\ge 0$）**：说明每轮走下来 $J$ 只能往下走或持平，绝不会反弹。
4. **为什么不仅收敛，还能在有限步停下？**：如果某个状态（某一种划分）能让 $J$ 严格变小，那你就**永远不可能再回到比它更高 $J$ 的旧划分里去**（平局时用固定规则不乱切）。既然总分法最多只有 $k^N$ 种且不回头，用不完这有限种分法，就必然走到某一步：分法完全不变、中心完全不变，**有限步内停止**。
5. **停在哪？**：它只保证停在一个"怎么单步微调都降不下去了"的**局部极小值（local minimum）**，不保证是全局最好的那一种分法（原因见 7.3）。

**④ 小例子**

拿 7.1 里的 6 个点 $\{1,2,3,10,11,12\}$ 分成 $k=2$ 组来看：
- 6 个点每人选 1 组还是 2 组，最多总共只有 $2^6 = 64$ 种分法；
- 目标函数 $J$ 依次经历了 `246 → 41.68 → 4 → 4`（第 4 步分配不变，停下），严格单调下降且 $\ge 0$，只走了 3 轮就一定收工，绝不会死循环。

**⑤ 常见误区**

- 以为"算法收敛 = 找到全世界最好的聚类结果"：错！收敛只代表"停在了一个稳定谷底（局部最优）"，好不好还要看起点选得好不好（见 7.3）。
- 只背"每步减小"却忘了写 **$J\ge 0$** 和 **划分总数有限（$\le k^N$）**：光单调下降不代表有限步必停（比如无限逼近极限值但永远走不完），靠"划分只有有限种"才能证明它**一定会在有限步停下来**。

**⑥ 对照最终版**

- `"Each step cannot increase J: the nearest center minimizes J in z; the mean minimizes J in c."` → 两步都不增大 $J$ 的精确原因（分别对 $z$ 和 $c$ 最小化）。
- `"J strictly decreases whenever the partition changes (ties broken consistently), and there are only finitely many partitions (\le k^N), so no partition repeats."` → 只要划分变了 $J$ 就严格下降（距离相等时固定规则，不来回换），而划分方案有限，所以不会重复出现同一个划分。
- `"So it stops in finite time, at a fixed point (a local minimum in practice), not always the global one."` → 结论：有限步内停止，停在不动点（实践中通常是局部最优），不一定是全局最优。

### 7.3 Why are multiple (re)runs suggested? How can k-means approximate the globally optimal solution? 为什么建议多次运行？如何用 k-means 逼近全局最优？ ★★★

考过：[2023.3 Ex3 a](../DataML-CHPS-2022-examen_zh.md) · [2023.11 Ex2 a](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 a](../DataML-CHPS-2024-examen_zh.md)（原问法：how it can be used to approximate the globally optimal solution）

**先懂这些：** 先理解 7.2 的"只保证局部最优"；在 [Lab4](../../Exercises/Lab4/Lab4_zh.ipynb) 用不同随机种子跑同一数据，比较 $J$。

**最终版答案（背诵版 EN，≤5 行）：**
$J$ is **non-convex**: the result **depends on the initialization**.
So we run k-means **many times** with random starts and **keep the lowest $J$**.
**k-means++** spreads the initial centers and helps.
This often finds a good (near-global) solution, but with **no guarantee**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

既然 7.2 刚说过 k-means 停下来时只是**局部最优**，那工程上为什么要把 k-means 连续重启跑好几遍（比如 `n_init=10`）？又要怎么用这个办法尽量逼近**真正的全局最优**？

**② 需要的工具**

- **非凸目标与"多谷底"地形**：把所有可能分法的 $J$ 想成一片连绵起伏、有很多山谷的地形。k-means 就像一个只会"往脚下低处滑"的小球——放进哪个山谷，就只能滑到那个山谷的谷底，**爬不出山坡去隔壁更深的山谷**。起点不同，滑到的谷底就不同。
- **多次重启（Multiple reruns）**：既然一个小球会卡在小水坑里，那我就在这片地形上空**不同位置多撒几个小球**，各自滑到谷底后，比一比谁的海拔（$J$）最低！
- **k-means++ 初始化**：比纯瞎蒙更聪明的放起点方法。先随机选第 1 个中心；选第 2 个、第 3 个中心时，故意给**"离已有中心越远的点"越高的被选中概率**（概率正比于到最近已有中心的距离平方）。这样初始中心天然散开，极少挤在同一个角落里，能帮算法一开局就站对山谷（在理论期望上有 $O(\log k)$ 的近似保证）。

**③ 一步一步**

1. **为什么必须多次运行**：因为 $J$ 是非凸的，单次运行的结果**严重依赖初始中心位置**，一次随机起点很可能掉进很差的局部极小值。
2. **具体怎么逼近全局最优**：
   - 在**同一个数据集、同一个 $k$** 下，用不同的随机起点（或配合 **k-means++**）独立把 k-means 跑很多次（每次都跑到收敛为止）；
   - 算一算每次跑完最终的簇内平方和 $J$；
   - **选出并保留 $J$ 最小的那一次运行结果**（注意：直接比 $J$ 挑最好的，而不是把几次的结果"平均"）。
3. **有没有保证一定拿到全局最优**：**没有理论保证（no guarantee）**——这就像猜一个多山谷地形的最低点，多试几次＋用 k-means++ 能非常接近全局最优，但在有限次尝试下，理论上仍不能保证百分百撞中全局最小（找聚类精确全局最优本身是 NP-hard 问题）。

**④ 小例子**

一维数据 $X=\{1,2,10,11,20,21\}$，明显应该分成 3 堆，设 $k=3$：
- **倒霉的起点** $(1, 2, 15)$（前两个中心挤在左边 $\{1,2\}$ 里了）：
  第 1 轮就收敛成 $\{1\}$、$\{2\}$、$\{10,11,20,21\}$（第 3 组中心 $15.5$），算出来 $J = 0+0+(5.5^2+4.5^2+4.5^2+5.5^2) = 101$，然后就**卡死不动了**！
- **分散的起点** $(1, 10, 20)$（或者用 k-means++ 很容易挑出这种分散起点）：
  收敛到 $\{1,2\}$、$\{10,11\}$、$\{20,21\}$，算出来 $J = 1.5$。

算法一模一样，仅仅因为初始中心放的位置不同，最终误差 $J$ 竟相差 **67 倍**！多跑几遍并留最小的 $J=1.5$，就能轻松躲开 $J=101$ 的坏结果。

**⑤ 常见误区**

- 以为"多次运行 = 像随机森林一样把几次结果取平均"：错！聚类的组号没有固定顺序（这次的第 1 组可能是下次的第 2 组），中心不能直接平均，必须**挑 $J$ 最小的那一次**作为最终结果。
- 误以为用了多次重启或 k-means++ 就**一定保证**找到全局最优：它只是大大提高逼近全局最优的概率，依然 `with no guarantee`。
- 拿 $J$ 去比较**不同 $k$** 的结果（比如 $k=2$ 和 $k=5$ 比谁的 $J$ 小）：$k$ 越大中心越多，$J$ 几乎必然越小（$k=N$ 时 $J=0$），所以只有**同一 $k$** 之间才能直接比 $J$（选 $k$ 见 7.4）。

**⑥ 对照最终版**

- `"J is non-convex: the result depends on the initialization."` → 解释为什么不能只跑一次：目标非凸、强依赖初始化。
- `"So we run k-means many times with random starts and keep the lowest J."` → 具体做法：多次随机重启，保留 $J$ 最小的解。
- `"k-means++ spreads the initial centers and helps."` → 加分技巧：k-means++ 把初始中心铺开。
- `"This often finds a good (near-global) solution, but with no guarantee."` → 实事求是的结论：往往能找到接近全局最优的解，但没有保证。

### 7.4 How do you validate the choice of the number of clusters? 如何验证聚类数目的选择？ ★★

考过：[2019 Q7](../Exam_2019_zh.md) · [2020 A5](../Exam_2020_zh.md)

**先懂这些：** [Lab4](../../Exercises/Lab4/Lab4_zh.ipynb) 簇数选择部分；[Lab5](../../Exercises/Lab5/Lab5_zh.ipynb) GMM（BIC）；与 1.5 一起复习。

**最终版答案（背诵版 EN，≤5 行）：**
The optimal $J$ never increases with $k$ (it is 0 when $k=N$), so we cannot just minimize it.
Use the **elbow method**, the **silhouette score** (choose the max), **BIC / AIC** for mixtures,
**stability** under resampling, and domain knowledge.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

无监督聚类没有正确答案可以核对准确率，那你怎么证明自己选的"分成 $k$ 堆"是合理的，而不是瞎猜了一个 $k$？

**② 需要的工具（先搞懂为什么不能直接比 $J$，再记 5 招验证）**

- **为什么不能选使 $J$ 最小的 $k$**：簇内平方和 $J$ 会随着 $k$ 增大**一路单调下降**。极端情况让每个样本自己占一个山头（$k=N$），$J$ 直接等于 $0$，但等于没分！所以选 $k$ 必须找"既紧凑、组数又别太多"的平衡点（参见 1.5）。
- **第 1 招——肘部法（Elbow method）**：把不同 $k$ 算出的 $J(k)$ 画成折线图，寻找像人胳膊弯曲的"手肘拐点"——拐点之前每多加一组，$J$ 猛跌（抓住了真结构）；拐点之后再加组，$J$ 只慢悠悠降一点点（只是把同一堆硬切两半）。
- **第 2 招——轮廓系数（Silhouette score）**：衡量每个点分得舒不舒服：
  $$s(i)=\frac{b(i)-a(i)}{\max(a(i),b(i))}$$
  - $a(i)$：点 $i$ 到**自己这一堆**其他成员的平均距离（"和本班同学有多熟"，越小越抱团）；
  - $b(i)$：点 $i$ 到**最近的隔壁堆**所有点的平均距离（"离最近邻班有多远"，越大越分明）。
  - $s(i)\in[-1,1]$：接近 $+1$ 说明内紧外疏、分得极好；接近 $0$ 说明骑在两堆边界上；$<0$ 说明可能分错了堆！对全数据求平均后，**选平均轮廓系数最大的 $k$**（注意轮廓系数只在 $k\ge 2$ 时有意义）。
- **第 3 招——BIC / AIC 准则**：专门配合概率聚类模型（如高斯混合模型 GMM）使用。它们等于"拟合得分 − 组数/参数太复杂的惩罚项"，自动在"解释数据好"与"别搞太复杂"之间找最优 $k$。
- **第 4 招——重采样稳定性（Stability）**：反复随机抽比如 80% 的数据重跑聚类。如果某个 $k$ 确实代表真实结构，每次分出的群组应该大同小异；若每抽一回分组就大洗牌，说明这个 $k$ 在强行切分噪声。
- **第 5 招——领域知识（Domain knowledge）**：结合实际业务意义看看分出来的 $k$ 堆能不能解释得通（比如把客户分成"高/中/低消费"3 群很有用，分成 47 群就没法运营）。

**③ 一步一步**

1. 先试一串候选组数（例如 $k=1,2,\dots,10$），对每个 $k$ 多跑几次取最小 $J$。
2. 先点明前提：**不能直接最小化 $J$**，因为 $J$ 随 $k$ 严格变小。
3. 再上验证组合拳：画肘部图看拐点、算平均轮廓系数取最大值（如适用 GMM 再算 BIC/AIC）、做重采样看结果稳不稳，最后用业务/领域知识把关确认（如果有少量参考标签，也可用 ARI、NMI 等外部指标辅助检验）。

**④ 小例子**

拿 1 维数据 $\{1,2,3,10,11,12\}$（肉眼一看就是左、右两堆）试不同 $k$，对应的最优 $J$ 为：

| 组数 $k$ | 1 | 2 | 3 | 4 |
|---|---|---|---|---|
| 簇内平方和 $J$ | 125.5 | **4** | 2.5 | 1 |

- **看肘部**：从 $k=1\to 2$，$J$ 暴跌了 $121.5$（125.5 跌到 4）；从 $k=2\to 3$ 只跌了 $1.5$，拐点明明白白就在 **$k=2$**！
- **看轮廓系数**：取 $k=2$ 时，$1$ 到同组 $\{2,3\}$ 平均距离 $a=(1+2)/2=1.5$，到另一组 $\{10,11,12\}$ 平均距离 $b=(9+10+11)/3=10$，于是 $s=(10-1.5)/10=0.85$，非常接近 1，同样支持 $k=2$。

**⑤ 常见误区**

- 以为谁的 $J$ 最小就选哪个 $k$（记住：**同一 $k$ 比初始化才比谁的 $J$ 小**，**跨不同 $k$ 选组数绝对不能比谁的 $J$ 小**）。
- 忘了轮廓系数是**越高越好**（要选 `max`），而 BIC（常见定义为负对数似然加惩罚时）通常是越小越好——答题时记清楚 `silhouette score (choose the max)`。

**⑥ 对照最终版**

- `"J always decreases with k, so we cannot just minimize it."` → 先讲清楚为何不能靠最小化 $J$ 选 $k$。
- `"Use the elbow method, the silhouette score (choose the max), BIC / AIC for mixtures,"` → 三大定量验证工具（肘部法、轮廓系数选最大、混合模型用 BIC/AIC）。
- `"stability under resampling, and domain knowledge."` → 两大实践验证标准（重采样稳定性、领域知识）。

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

硬 k-means 里每个点只能"非此即彼"地归属唯一一个簇；考官让你**自己设计**一个"软（概率）版本"的 k-means：每个点改用**概率**属于各簇，而且要求同时答出三件事：**怎么定义、伪代码怎么写、收敛性如何（能到最优吗）**。

**② 需要的工具**

- **责任度（Responsibility / 软分配）$r_{ij}$**：点 $i$ 属于第 $j$ 簇的概率，满足 $r_{ij}\ge 0$ 且 $\sum_{j=1}^k r_{ij}=1$。硬 k-means 里 $r_{ij}$ 只能取 $0$ 或 $1$；软 k-means 里可以取小数，比如 $(0.8, 0.2)$。
- **Softmin / Softmax 转换**：怎样把"到各中心的距离"变成和为 1 的概率？规则很简单：**距离越小，概率越大，而且按指数级放大差距**：
  $$r_{ij}=\frac{\exp(-\|x_i-c_j\|^2/\tau)}{\sum_{l=1}^k\exp(-\|x_i-c_l\|^2/\tau)}$$
- **温度参数 $\tau > 0$（Temperature）**：控制"软硬程度"的旋钮。$\tau$ 越小（越冷），差距被放得越大，接近硬分配 $(1,0)$；$\tau$ 越大（越热），各簇概率越平均、越模糊。
- **自由能目标函数 $F(r,c)$（软 k-means 真正最小化的目标）**：
  $$F(r,c)=\sum_{i,j}r_{ij}\|x_i-c_j\|^2+\tau\sum_{i,j}r_{ij}\log r_{ij}$$
  第一项是"按概率加权的平方距离"，第二项是"$\tau \times$ 负熵"——因为负熵鼓励概率分散不要太死板，$\tau$ 越大，第二项话语权就越大。
- **与 GMM + EM 的对应**：这在数学上等价于一个**高斯混合模型（GMM）的 EM 算法**——假设各高斯簇权重相等、协方差矩阵相同且固定为球形 $\sigma^2 I$，其中温度对应 $\tau = 2\sigma^2$。

**③ 一步一步（定义 → 伪代码 → 收敛分析 → 与 GMM 联系）**

1. **定义**：给出上面的软分配公式 $r_{ij}$（带温度 $\tau$）与加权平方距离目标 $F(r,c)$。
2. **伪代码（就是 EM 交替两步）**：
   - 初始化 $k$ 个中心 $c_1,\dots,c_k$；
   - 循环直到中心或 $F$ 变化极小：
     - **E 步（算软归属）**：固定中心 $c$，按公式算出每个点对每个簇的责任度 $r_{ij}$；
     - **M 步（加权更新中心）**：固定 $r$，用"所有人按责任度加权平均"更新中心：
       $$c_j=\frac{\sum_{i=1}^N r_{ij}x_i}{\sum_{i=1}^N r_{ij}}$$
       （谁属于第 $j$ 簇的概率高，第 $j$ 簇的新中心就多听谁的话。）
3. **是否收敛？收敛到哪里？**：
   - **目标值会收敛**：可以证明 E 步是在 $c$ 固定时把 $F$ 在 $r$ 上降到最低，M 步是在 $r$ 固定时把 $F$ 在 $c$ 上降到最低，所以每一步都不会让 $F$ 变大；又因为熵有界，可以算出 $F \ge -N\tau\log k$（有下界），因此目标函数值 $F$ 必定**收敛**。
   - **但不仅不保证全局最优，甚至不保证一定是局部极小值！** 比如数据是 $\{-1, 1\}$、取 $\tau=1$，把两个中心故意初始化成完全重合 $c_1=c_2=0$：E 步算出所有 $r_{ij}=1/2$，M 步算均值又是 $( -1\cdot 0.5 + 1\cdot 0.5 )/1 = 0$，于是卡死在 $(0,0)$ 不动了，此时 $F\approx 0.614$；可只要稍微把两个中心拨开一点到 $(-0.1, 0.1)$，$F$ 立刻降到 $\approx 0.594$！说明 $(0,0)$ 只是个**鞍点/不动点**，连局部最优都不是。
4. **补充加分项**：指出它就是固定等球协方差（$\tau=2\sigma^2$）的 **GMM 的 EM**，且当 $\tau\to 0$ 时就退化成标准硬 k-means。

**④ 小例子**

一维点 $x=4$，两个中心分别在 $c_1=2$ 和 $c_2=7$，距离平方是 $(4-2)^2=4$ 和 $(4-7)^2=9$：
- **低温 $\tau=2$**（更"硬"）：权重比例 $e^{-4/2}:e^{-9/2}=e^{-2}:e^{-4.5}$，归一化得 $r\approx(0.924,\ 0.076)$ —— 92.4% 归第一簇；
- **高温 $\tau=20$**（更"软"）：权重比例 $e^{-4/20}:e^{-9/20}=e^{-0.2}:e^{-0.45}$，归一化得 $r\approx(0.562,\ 0.438)$ —— 两边几乎五五开；
- **极限 $\tau\to 0$**：$r\to(1,\ 0)$ —— 变回硬 k-means。

**⑤ 常见误区**

- 开放设计题只答"给每个点算概率"而**不写公式、不写伪代码、不写收敛分析**：考官明确要看 definition、pseudocode、convergence 三部分。
- 把收敛说成"一定收敛到局部极小甚至全局最优"：一定要写清**目标 $F$ 有下界且单调不增所以目标值收敛，但不保证全局最优，甚至可能卡在不是局部极小的不动点上**。

**⑥ 对照最终版**

- `"Soft assignment with temperature \tau: r_{ij}=\frac{\exp(-\|x_i-c_j\|^2/\tau)}{\sum_l\exp(-\|x_i-c_l\|^2/\tau)}."` → 给出带温度 $\tau$ 的明确概率定义。
- `"Repeat: E-step compute all r_{ij}; M-step c_j=\sum_ir_{ij}x_i/\sum_ir_{ij}."` → 简洁两步伪代码。
- `"Both steps do not increase F=\sum r_{ij}\|x_i-c_j\|^2+\tau\sum r_{ij}\log r_{ij}, which is bounded below, so the objective converges (not necessarily to a global, or even local, minimum)."` → 严格写出自由能目标及有下界的收敛结论（并点破未必是局部极小）。
- `"It is EM for a GMM with equal weights and a fixed shared spherical covariance (\tau=2\sigma^2)."` → 与 GMM+EM 的精准对应。

### 7.6 If k-means is initialized with the soft k-means solution, will the clusters change? Is it a local minimum of hard k-means? 用软 k-means 的解初始化 k-means，簇会变吗？它是硬 k-means 的局部极小吗？ ★★

考过：[2023.11 Ex2 c](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex5 c](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 软中心是**加权均值**，硬中心是**普通均值**（7.1 与 7.5 对比）。

**最终版答案（背诵版 EN，≤5 行）：**
**Not necessarily.** Soft centers are **weighted means** (every point counts a bit).
With hard assignments, each cluster mean is different, so k-means **moves the centers** and some points can change cluster.
It stays the same only if each soft center already **equals the mean of its hard cluster** (almost 0/1 weights make this approximately true).

**解析版（小白也能看懂）：**

**① 这道题在问什么**

这是一道很有深度的小连环问：假设我们先用 **软 k-means** 跑到了收敛，把得到的中心拿去当 **硬 k-means** 的初始中心再跑：
1. 聚类结果（中心和分组）会发生变化吗？
2. 软 k-means 的解，算是硬 k-means 的**局部极小值**吗？

**② 需要的工具**

- **软中心 = 所有点加权平均**（见 7.5）：哪怕主要属于隔壁簇的点，对你的中心也有那么一点"拉扯力"（因为概率 $r_{ij}>0$，永远不是绝对的 0）。
- **硬中心 = 本簇自己人纯平均**（见 7.1）：只看分到本簇的点，隔壁簇的点一票都没有。
- **不动点与局部最优**：硬 k-means 停下的前提是"按最近中心硬分完之后，每堆的新均值刚好就等于旧中心"。

**③ 一步一步**

1. **先给结论：不一定不变（通常会变）！** 因此软 k-means 的解一般**不是**硬 k-means 的局部极小值。
2. **原因在于两者优化的公式根本不同**：软 k-means 停下来时，满足的是自由能 $F$ 的平衡（中心是**加权均值**）；硬 k-means 要求满足簇内平方和 $J$ 的平衡（中心是**普通均值**）。
3. **跑一步硬 k-means 会发生什么**：
   - 把软中心放进来，每个点按"离谁最近"硬选一个归属；
   - 再把每个中心更新为本簇内点的**普通均值**——由于删掉了隔壁簇点原本的微弱拉力，**中心往往会立刻向外移动**；
   - 中心一移动，簇之间的分界线也跟着平移，那些**刚好卡在边界附近**的点就可能跳槽换到另一簇！
4. **什么时候才会一步都不动？**：只有当"按软中心做完硬分配后，每一簇的普通均值**恰好已经等于**原来的软中心"时，硬 k-means 才不会动。如果簇彼此隔得极远或温度 $\tau$ 极小，责任度几乎全是 $0$ 或 $1$，这时两种中心会**非常接近**，结果大概率近似不变——但这只是近似，严格条件还是"软中心 $=$ 对应硬簇的均值"。

**④ 小例子**

一维数据 $\{0,1,2,6,7,8\}$，设 $k=2$，温度 $\tau=8$：
- **先跑软 k-means 收敛**：因为右边的 $\{6,7,8\}$ 对左边中心还有约 5% 的拉力，左中心停在 $1.103$（略微被向右拉偏），右中心停在 $6.897$（略微被向左拉偏）。
- **接手跑硬 k-means**：
  1. 按 $(1.103, 6.897)$ 硬分配：中点在 $4$，左边分到 $\{0,1,2\}$，右边分到 $\{6,7,8\}$；
  2. 更新为中心均值：左边变成 $(0+1+2)/3 = 1$，右边变成 $(6+7+8)/3 = 7$ —— **中心立刻向外移开了**！如果两堆中间还恰好站着边界附近的点（比如非对称分布时分界线一挪），这些点就会跟着改变所属的簇。

**⑤ 常见误区**

- 误以为软、硬 k-means 是"同一座山谷的两种写法"，答案一样：其实目标函数 $F$ 和 $J$ 不同，平衡点也不同。
- 把"责任度接近 0/1"说成"绝对不变"的充要条件：其实只要有一个边界点带了一点小权重，普通均值就会和加权均值差一点点；不变的严格判据必须是**"每个软中心恰好等于其硬簇样本的普通平均"**。

**⑥ 对照最终版**

- `"Not necessarily. Soft centers are weighted means (every point counts a bit)."` → 直接回答不一定（会变），核心原因就是软中心受每个点加权拉扯。
- `"With hard assignments, each cluster mean is different, so k-means moves the centers and some points can change cluster."` → 说明硬平均不同导致中心移动，进而可能让边界点换簇（故不是硬 k-means 局部最优）。
- `"It stays the same only if each soft center already equals the mean of its hard cluster (almost 0/1 weights make this approximately true)."` → 严谨写出唯一不变的条件，并顺带点出权重接近 0/1 时近似成立。

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

硬 k-means 和软 k-means（包括它的好兄弟 GMM）各有啥优缺点？到底什么情况下应该放弃简单快速的硬 k-means，改用软 k-means？

**② 需要的工具**

- **硬分配（Hard assignment）**（见 7.1）：非此即彼，每个点只能被死死按进唯一一个簇，拿不到"把握有多大"。
- **软分配（Soft assignment）**（见 7.5）：给出属于每个簇的**概率**（比如 0.65 归 A 簇、0.35 归 B 簇），把"模棱两可"诚实地留下来。
- **球形 vs 椭圆形簇（GMM 协方差）**：硬 k-means（和固定等协方差的软 k-means）只按普通欧氏距离比远近，画出来的簇范围像一个个**等大的正圆球**；如果升级成完整协方差的高斯混合模型（GMM），每个簇还能自由拉扁、旋转、变大小，变成**各种形状的椭圆**。

**③ 一步一步（对比表 + 适用场景）**

| 对比维度 | 硬 k-means | 软 k-means / GMM |
|---|---|---|
| **输出结果** | 每人一个唯一簇号（简单干脆） | **概率向量**，诚实反映**边界不确定性** |
| **速度与开销** | **快、省内存**（每轮只需记最近的那个中心） | 更慢更占内存（每轮要算并存 $N\times k$ 个概率） |
| **簇的形状** | 默认圆形、等大小（对椭圆、大小悬殊很吃力） | 完整 GMM 可拟合**斜着、拉长的椭圆和不同大小** |
| **额外旋钮** | 只需定簇数 $k$ | 除了 $k$，还要选温度 $\tau$ 或协方差假设 |

**什么时候软 k-means 更合适？记住 3 个场景**：
1. **几堆数据彼此混在一起、边界互相重叠**（Hard 方法会被迫把骑墙点硬塞给一边，丢失信息）；
2. **下游任务需要知道"确定度/概率"**（例如风控、医疗或用户画像，80% 属于 A 且 20% 属于 B 比一句生硬的"属于 A"更有用）；
3. **需要概率密度模型或处理细长椭圆簇**（改用完整的 GMM）。

**④ 小例子**

电商做客户分群：有个买家买便宜日用品也买高端数码，算出来的隶属概率是 `60% 价格敏感型 + 40% 品质优先型`。
- **硬 k-means**：一刀切贴标签叫"价格敏感型"，从此只给他推 9.9 包邮，白白错失高端消费能力；
- **软 k-means**：保留 `0.6 / 0.4` 的概率，系统就能按比例混推商品，还知道这个人是跨界客户。

**⑤ 常见误区**

- 以为软 k-means 永远全方位吊打硬 k-means：如果各堆分得非常开、数据量又极大、你只想要个快速粗略分组，硬 k-means **更快更省、不必操心选 $\tau$**，反而更实用。
- 忘了顺手提一句**离群点**：两种标准 k-means 对极端离群点都同样敏感（都会拉偏中心），这是均值自身的毛病。

**⑥ 对照最终版**

- `"Hard: one cluster per point, simple and fast, but boundary points are forced into one cluster."` → 硬 k-means 的优（简单快）与缺（边界点被迫硬站队）。
- `"Soft: gives membership probabilities and shows uncertainty; a GMM can model elliptical clusters."` → 软 k-means 的优（给概率、保留不确定性，且 GMM 能建椭圆簇）。
- `"But it costs more and needs \tau or a model."` → 软 k-means 的代价（计算贵、需定 $\tau$ 或概率模型）。
- `"Use soft when clusters overlap or when probabilities are needed."` → 核心适用结论（簇重叠、需要概率时选用）。

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

这是典型结合计算题的追问（比如算完 $k=2$ 的两轮迭代后）：现在让你只用**两个"典型代表"（簇中心）**去概括整套数据集，请问：
1. 这两个典型代表是谁？
2. 它们各自代表本簇的效果好不好？怎么量化说明？

**② 需要的工具**

- **合成中心（Mean / Centroid）**：本簇所有点的平均值。它是一个**算出来的虚拟原型**（不一定是数据集里真实存在过的样本），它能让簇内均方误差最小。
- **中心样本（Medoid）**：如果业务硬性要求代表必须是"数据集里真实存在的某一个人/样本"（比如展示两张真实代表图片），就要找离全组其他人总距离最小的真实点，即 **medoid**。
- **簇内 MSE（Mean Squared Error）**：把簇里所有点到代表的距离平方求平均（$\frac{1}{|C_j|}\sum_{x\in C_j}\|x-c_j\|^2$）。你可以把它理解成**"用代表代替所有人说话时，平均造成的失真有多大"**——MSE 越小，代表得越贴切。

**③ 一步一步（考场标准回答套路）**

1. **先指明典型代表是谁**：通常就是两个簇中心 $c_1,c_2$（均值）；顺手补一句"若必须取真实样本，则用 **medoid**"。
2. **用数据量评估代表性（算 MSE / 看紧散程度）**：
   - 如果一个簇**很紧凑（compact）**、点都抱团在中心周围，**簇内 MSE 很小**，中心就能很好地代表大家；
   - 如果一个簇**很分散（spread）**、**里面还暗藏多个小团体（sub-groups）**、或者**被离群点拉扯**，那**簇内 MSE 就会很大**，代表效果很差——算出来的均值甚至可能落在一块**根本没有任何数据的"真空地带"**（就像 $\{1, 99\}$ 的平均是 $50$，既不代表 1 也不代表 99！）。
3. **如果是固定中心（Fixed center）更糟糕**：像 2021 年真题那样，第二个中心被题目强行钉死在 $80$ 不让更新为均值，那它连自己簇的平方误差最小值都达不到，代表性比均值还要差。

**④ 小例子（2021 年真题完整演示）**

数据集分为两簇：簇 1 是 `{10, 15, 20, 25}`（中心为均值 `17.5`），簇 2 是 `{55, 60, 90, 100}`（中心被题目**固定**为 `80`）：
- **簇 1（紧凑）**：偏差只有 $\pm2.5,\pm7.5$，簇内 MSE $=\frac{7.5^2+2.5^2+2.5^2+7.5^2}{4}=\mathbf{31.25}$。`17.5` 站在四个点正中间，代表得非常好！
- **簇 2（分散 + 有两个子群 + 中心被固定）**：不仅松散，内部还明显裂成 `{55, 60}` 和 `{90, 100}` 两小伙人；再加上中心被死死钉在 `80`（甚至不等于本簇真正的均值 `76.25`），结果簇内 MSE 高达 $\frac{(-25)^2+(-20)^2+10^2+20^2}{4}=\mathbf{381.25}$（误差是簇 1 的 12 倍！），而且 `80` 附近其实空无一人！

完整一步步计算过程见 [计算题 C2](00_calculations.md)。

**⑤ 常见误区**

- 只把两个中心数值抄一遍，不比较两者 MSE 大小、不分析"紧凑 vs 分散/双峰/固定中心"，会丢掉大部分解释分。
- 以为均值中心一定在数据集里找得到：其实均值是算出来的虚拟点，要真实数据点必须提 **medoid**。

**⑥ 对照最终版**

- `"The two typical examples are the centers (means); if a real point is needed, the medoid."` → 先定义代表是谁（均值，若需真点则 medoid）。
- `"A compact cluster is well represented (small MSE)."` → 紧凑簇（低 MSE）代表得好。
- `"A spread cluster, or one with sub-groups or outliers, is badly represented: its mean can lie where there is no data."` → 分散/多子群/含离群点的簇代表得差，均值可能落在无数据区。
- `"A fixed center (not the mean) is worse."` → 被固定而不是均值的中心更差。

### 7.9 During k-means, how can a cluster become empty? Give heuristics to continue without reducing k. k-means 中簇为什么会变空？给出不减少 k 的处理办法。 ★

考过：[2021 Ex4 e](../DataML-CHPS-2021-examen_zh.md)

**先懂这些：** 7.1 的分配步：一个中心如果不是任何点的"最近中心"，它的簇就是空的。

**最终版答案（背诵版 EN，≤5 行）：**
A cluster is empty when **no point is closest to its center** (bad initialization, or other centers took its points).
Fixes: move the center to the **point with the largest error**, or **split the biggest cluster**, or **re-seed** it (uniformly at random, or by the **k-means++** rule: probability ∝ squared distance to the nearest center).

**解析版（小白也能看懂）：**

**① 这道题在问什么**

运行 k-means 时，明明有 $k$ 个簇中心，为什么半路上某个簇可能会变成 **"0 个成员"（空簇）**？一旦空了该怎么办，才能**保住 $k$ 不缩水**继续往下算？

**② 需要的工具**

- **分配步决定生死**（见 7.1）：每个点只投靠"离自己最近的那个中心"。如果一个中心一个粉丝都没抢到，它名下的簇就是空的。
- **空集没法算均值**：更新步要求 `c_j = 本簇所有点的均值`。0 个点怎么求平均？分子分母都是 $0/0$，算法就卡住了！
- **误差最大的点（Point with largest error）**：整个数据集里，离自己当前老大距离最远（$\|x_i-c_{z_i}\|^2$ 最大）的那个点——它是当前分得最委屈、失真最严重的一个点。

**③ 一步一步**

1. **为什么会变空？**
   - 在某轮分配步中，**没有任何一个数据点离 $c_j$ 最近**。
   - 典型诱因：一开局就把某初始中心随机放到远离所有数据的荒郊野外；两个中心几乎贴在一起；或者某个中心在移动过程中被"邻居中心"移动过来把仅剩的几个点全部抢走了。
2. **不缩减 $k$ 的三种急救启发式（Heuristics）**：
   - **招式 1（最推荐）：把空中心搬到当前"误差最大的点"上**。因为那个点目前最孤单、拉高了总平方和 $J$；新中心落到它身上，它立刻归顺这个新中心，而且还能顺便大幅降低 $J$！
   - **招式 2：拆掉最大的簇（Split the biggest cluster）**。找一个目前内部误差（或成员数）最大的臃肿簇，把空中心放到它里面的某个远点或随机点上，把大簇一分为二。
   - **招式 3：重新撒种（Re-seed）**。要么从现有数据点里均匀随机重抽一个点当中心；要么按 **k-means++ 规则**抽——到现有最近中心的**距离平方越大，被抽中的概率越高**（专挑离现有老大最远的地盘落地，避免再次撞车）。
3. 补救完空中心后，接着正常往下跑分配和更新循环即可。

**④ 小例子**

一维数据 $\{1,2,3,10,11,12\}$，设 $k=3$，倒霉初始化为 $(c_1,c_2,c_3)=(1, 2, 50)$：
- **分配**：所有点都离 1 或 2 很近，没有任何点离 50 最近！于是 $c_3$ 名下为空簇；
- **急救**：检查当前每人的误差——12 归给了中心 2，平方误差高达 $(12-2)^2=100$，全班最大！于是直接把原本在 50 的 $c_3$ 搬到 **12** 上，三中心变成 $(1, 2, 12)$，成功复活并继续迭代。

**⑤ 常见误区**

- 直接把空簇删掉变成 $k-1$ 簇：题目明确要求 **`without reducing k`**（不能减少 $k$），直接删簇会丢分！
- 把 k-means++ 重置说成"随机选一个点"：一定要点出它是按**与最近中心距离平方成正比的概率**去抽样（`probability ∝ squared distance to the nearest center`）。

**⑥ 对照最终版**

- `"A cluster is empty when no point is closest to its center (bad initialization, or other centers took its points)."` → 清晰说明空簇成因（没有任何点离它最近 + 两个典型原因）。
- `"Fixes: move the center to the point with the largest error, or split the biggest cluster, or re-seed it (uniformly at random, or by the k-means++ rule: probability ∝ squared distance to the nearest center)."` → 给出三种不用减 $k$ 的修复启发式，并点清 k-means++ 的加权规则。

### 7.10 What if the initial clusters are formed by assigning each point uniformly at random? Will it converge, faster or slower? 如果初始化时把每个点等概率随机分到某个簇，会收敛吗？更快还是更慢？ ★

考过：[2023.3 Ex3 b](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** 大数定律：随机子集的均值≈全体均值；对比 7.3 的 k-means++。

**最终版答案（背诵版 EN，≤5 行）：**
Each random cluster is a sample of the whole data, so all initial centers are **near the global mean** (law of large numbers).
It **still converges** (same argument as 7.2), but it can be **slower**, because the centers must first separate.
It may also end more often in a **bad local optimum** (this depends on the data).

**解析版（小白也能看懂）：**

**① 这道题在问什么**

常规 k-means 是先挑 $k$ 个点当初始中心。现在题目换了个初始化办法：不选中心，而是**先把每个点扔骰子等概率随机分进第 $1\dots k$ 组**，再算各组均值当初始中心。这样做：
1. 算法还会收敛吗？
2. 比常规（如随机挑点 / k-means++）更快还是更慢？结果好还是差？

**② 需要的工具**

- **大数定律（Law of large numbers）**：从一大群人里**完全随机**抽一个子集出来，这个子集的平均值会很接近全体总平均。如果把全班同学随机分成 3 组，每组的平均身高都会几乎一样（都在全班平均身高附近）。
- **7.2 的收敛论证**：无论起点长什么样，只要进到 k-means 的"分配—更新"主循环，$J\ge 0$ 单调不增且划分只有有限种，所以一定在有限步停下。

**③ 一步一步**

1. **初始中心长什么样（大数定律发威）**：随机分出来的每组，都是全数据集的均匀随机样本。因此算出每组的均值后，**所有 $k$ 个初始中心会全都挤在全局平均值附近**（彼此挨得很近），而不是像 k-means++ 那样事先分散开。（如果样本很少，甚至开局就可能某组随机到 0 个点变成空簇。）
2. **还会收敛吗？——会！**：因为进入循环之后，每一步依然是不增加 $J$ 且划分数有限（见 7.2），所以**照样一定收敛**。
3. **更快还是更慢？——往往更慢（can be slower）**：既然 $k$ 个中心一开局全挤在数据正中间，它们在头几轮得先花额外的力气"互相排斥、慢慢拆散挪到各自的地盘"，然后才慢慢稳定下来；相比之下，k-means++ 一开局中心就已经站好大概位置了。
4. **结果质量如何？——可能更容易卡进较差的局部最优**：挤成一团的中心很容易在移动时相互干扰、把某几个大簇抢成奇怪的切法。当然，以上两点都是**"倾向"而不是铁律**，实际快慢和好坏还要看具体数据的形状（在极端简单的数据上它也可能一步分对）。

**④ 小例子**

- **为什么在极简一维数据上看不出差异**：数据 $\{1,2,3,10,11,12\}$（全局均值 $6.5$），随机分成 $\{1,3,10\}$ 和 $\{2,11,12\}$，算出的初始中心是 $4.67$ 和 $8.33$——果然都向全局均值 $6.5$ 靠拢了！但因为一维 $k=2$ 的分界中点恰好还是 $(4.67+8.33)/2=6.5$，第一轮分配就立刻分对了 $\{1,2,3\}$ 和 $\{10,11,12\}$。
- **在二维或 $k \ge 3$ 时就明显了**：想象在平面四个角各有一团点，$k=4$。随机划分会把 **4 个中心全都生成在正方形正中央 $(0,0)$ 附近紧挨着**——此时 k-means++ 第 1 轮就已经稳稳各占一角，而随机划分出来的 4 个中心像粘在一起的麻团，经常要慢吞吞挪很多轮才能各自散开，有时甚至两个中心挤去抢同一个角、留另一个角空着没人管（掉进差局部最优）。

**⑤ 常见误区**

- 以为"中心位置也算随机了"所以效果差不多：其实随机**划分点**再求均值，会让初始中心全部向**全局均值塌缩**；而随机**抽 $k$ 个点**本身就分散在数据云各处，两者完全不同！
- 把"更慢、更差"写成绝对必然：记得加定语 **"can be slower / may end more often ... (depends on the data)"**，最严谨。

**⑥ 对照最终版**

- `"Each random cluster is a sample of the whole data, so all initial centers are near the global mean (law of large numbers)."` → 先用大数定律解释初始中心全都挤在全局均值附近。
- `"It still converges (same argument as 7.2), but it can be slower, because the centers must first separate."` → 回答收敛性（7.2 同理必收敛）和速度（可能更慢，因中心需先散开）。
- `"It may also end more often in a bad local optimum (this depends on the data)."` → 回答解的质量（可能更常陷入坏局部最优，视数据而定）。

### 7.11 Give three linkage criteria for hierarchical agglomerative clustering, with formulas. 给出层次凝聚聚类的三种连接准则及公式。 ★

考过：[2023.3 Ex3 e](../DataML-CHPS-2022-examen_zh.md)（树状图：[2022_linkage.png](../Answers/2022_linkage.png)）

**先懂这些：** 凝聚聚类流程：从单点簇开始，每次合并距离最近的两个簇；[Lab4](../../Exercises/Lab4/Lab4_zh.ipynb)。

**最终版答案（背诵版 EN，≤5 行）：**
Start from single points and **merge the two closest clusters** (this gives a dendrogram).
**Single**: $\min_{a,b}\|a-b\|$ (chaining). **Complete**: $\max_{a,b}\|a-b\|$ (compact clusters).
**Average**: $\frac1{|A||B|}\sum_{a,b}\|a-b\|$. **Ward**: merge with the smallest increase of inertia.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

k-means 是一开始定好 $k$ 个中心直接抓堆；**层次凝聚聚类（Hierarchical agglomerative clustering）**则是反着来："最开始每人孤身一簇，一步步把最近的两簇合并"，最后画成一棵像家谱一样的合并树。
关键问题来了：**两个"一堆点"之间，距离到底怎么算？** 题目要你写出至少 **3 种连接准则（Linkage criteria）及公式**。（真题里还常配合手画树状图，见 [计算题 C5](00_calculations.md)。）

**② 需要的工具**

- **层次凝聚（Agglomerative = 自底向上合并）**：开局 $N$ 个点各自为战（$N$ 簇），每次找当前距离最近的两个簇合二为一，直到所有点变成 1 大簇。
- **树状图（Dendrogram）**：把每次谁和谁在多大距离上合并画成一棵倒立的树。树画好后，想分几组就拿尺子在某个高度横切一刀，不用提前定死 $k$！
- **连接准则（Linkage）**：两个单独的点之间可以用欧氏距离 $\|a-b\|$，但两个各含好几个点的集合 $A$ 和 $B$ 之间，**以哪对点代表两个集合的距离**，不同规定就是不同连接准则。

**③ 一步一步（4 种准则，考题要 3 种，全背下来还能顺手挑最好记的）**

设两个簇分别是点集 $A$ 和 $B$：

1. **单连接（Single linkage / 最近邻）**：取两簇之间**距离最近**的那一对朋友的距离：
   $$d_{\text{single}}(A,B)=\min_{a\in A,\ b\in B}\|a-b\|$$
   - **特点**：只要两团边上恰好有一两个点靠近就能牵上线合并，所以擅长找长条形/月牙形簇，但容易出现**"链式效应（chaining）"**——几个零星中间点会把原本不相干的大团串成一条长蛇。
2. **全连接（Complete linkage / 最远邻）**：取两簇之间**距离最远**的那一对冤家的距离：
   $$d_{\text{complete}}(A,B)=\max_{a\in A,\ b\in B}\|a-b\|$$
   - **特点**：只有两簇里**所有成员**彼此都不算太远时才肯合并，所以往往做出大小相近、**紧密圆润（compact）**的簇；缺点是受离群点影响大。
3. **平均连接（Average linkage）**：把两簇之间**所有跨簇点对**的距离全部算出来求平均值：
   $$d_{\text{avg}}(A,B)=\frac{1}{|A|\cdot|B|}\sum_{a\in A}\sum_{b\in B}\|a-b\|$$
   - **特点**：既不像单连接那么容易粘成一串，也不像全连接那么怕个别远点，是两者的稳健折中。
4. **Ward 准则（最小方差增量，补充备选）**：合并能使**总簇内平方和 $J$ 增加最少**的那一对簇：
   $$\Delta(A,B)=\frac{|A||B|}{|A|+|B|}\|\mu_A-\mu_B\|^2$$
   - **特点**：思路和 k-means 一脉相承，最喜欢产出球形、分布均匀的簇（注意看合并后的 $\Delta$ 公式就能当连接公式背）。

**④ 小例子**

有两个一维簇 $A=\{10, 15\}$（均值 $\mu_A=12.5$）和 $B=\{20, 25\}$（均值 $\mu_B=22.5$）。跨簇点对一共有 $2\times 2 = 4$ 对，距离分别是：
$|10-20|=10,\ |10-25|=15,\ |15-20|=5,\ |15-25|=10$。

四种连接准则给出完全不同的数值：
- **Single（取最小）**：$\min(10,15,5,10) = \mathbf{5}$；
- **Complete（取最大）**：$\max(10,15,5,10) = \mathbf{15}$；
- **Average（取平均）**：$(10+15+5+10)/4 = \mathbf{10}$；
- **Ward（合并惯性增量）**：$\frac{2\times 2}{2+2}(22.5-12.5)^2 = \mathbf{100}$（合并前 $A$ 和 $B$ 各自平方和共 $25$，合并成 $\{10,15,20,25\}$ 后平方和 $125$，恰好增加了 $100$）。

**⑤ 常见误区**

- 题目问 **`with formulas`**，千万不能只写英文名字（Single / Complete / Average）而漏掉 $\min$、$\max$、$\frac{1}{|A||B|}\sum$ 这些公式。
- 把 Single 和 Complete 的 $\min$ / $\max$ 记反：记住 "Single = 只要牵上一**单**根线就行（看**最接近**的 $\min$）；Complete = 必须**全部**最远的人都够近才行（看**最远**的 $\max$）"。

**⑥ 对照最终版**

- `"Start from single points and merge the two closest clusters (this gives a dendrogram)."` → 概括层次凝聚聚类的自底向上合并流程与树状图输出。
- `"Single: \min_{a,b}\|a-b\| (chaining). Complete: \max_{a,b}\|a-b\| (compact clusters)."` → 写出单连接、全连接公式及各自特点（链式效应 vs 紧凑簇）。
- `"Average: \frac1{|A||B|}\sum_{a,b}\|a-b\|. Ward: merge with the smallest increase of inertia."` → 写出平均连接公式，再补上 Ward 准则（可按需任选其中三种）。

### 7.12 Use bootstrapped k-means solutions to compute an outlier score; compare with Isolation Forest. 用多次 bootstrap 的 k-means 解计算离群分数，并与 Isolation Forest 比较。 ★

考过：[2024 Ex5 d](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① bootstrap（有放回重采样）——[第五课 · 一般而言，bootstrap 是什么？](../../Lectures/05_NLM_zh.md)；② Isolation Forest 原理——[Lab3](../../Exercises/Lab3/Lab3_zh.ipynb) 异常检测部分。

**最终版答案（背诵版 EN，≤5 行）：**
For $b=1..B$: take a **bootstrap sample**, run k-means, and score each point by its **(normalized) distance to the nearest center**. The outlier score is the **mean / median** over the runs.
It is more stable than one run, but k-means is **not robust** and assumes round clusters.
**Isolation Forest** uses random splits: outliers are **isolated quickly**; no centers, no $k$.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

这是一道设计＋对比题：
1. 怎么利用**多次 bootstrap 重采样 + k-means** 的结果，给每个数据点算一个"有多像离群点（Outlier score）"的分数？
2. 把这个自制方法，和经典的 **Isolation Forest（孤立森林）** 对比一下各自有什么优缺点？

**② 需要的工具**

- **Bootstrap 重采样**（见 2.3）：从 $N$ 个点中有放回地随机抽 $N$ 次（抽完放回去再抽，同一个点可能被抽中多次，也会有约 $37\%$ 的点某轮一次都没抽到）。
- **离群分数（Outlier score）**：给每个点打分，分数越高越怀疑它是异常值。如果离所有聚类中心都特别远，就很可能是离群点。
- **为什么距离要按簇的尺度归一化（Normalized distance）**：假设 A 簇非常紧实（大家离中心距离都在 $0.1$ 左右），B 簇非常松散（大家离中心距离都在 $10$ 左右）。那么同样距离中心 $3$ 的点，在 A 簇里已经是极大异类（$3/0.1=30$ 倍），在 B 簇里却平平无奇（$3/10=0.3$ 倍）！所以距离最好除以该簇的尺度（如标准差或方差 $v_{bj}+\varepsilon$）。
- **Isolation Forest（孤立森林）**：用许多棵"完全随机乱切"的树来找异常值——孤零零偏在角落的离群点，随便切一两刀就跟大部队隔开了（树上路径极短）；挤在人群中心的正常点，得反复切很多刀才能单独框出来（路径很长）。

**③ 一步一步（流程 + 自身局限 + 与 IF 对比）**

**第一步：设计算法流程（$b=1,\dots,B$ 轮）**
1. 对每一轮 $b=1,\dots,B$：
   - 从原数据集有放回地抽出一份 **bootstrap 样本**，在这个样本上跑 k-means 得到 $k$ 个中心 $\{c_{b1},\dots,c_{bk}\}$ 和各自簇的尺度 $v_{bj}$；
   - 对数据集里的**每一个点 $x_i$**，计算它到这轮**最近中心**的（归一化）距离：
     $$s_b(x_i)=\min_j\frac{\|x_i-c_{bj}\|^2}{v_{bj}+\varepsilon}$$
     （$\varepsilon>0$ 是个小常数，防止某个簇缩成一个点导致分母为 0。）
2. 跑完 $B$ 轮后，把每个点收到的 $B$ 个分数取**平均值（mean）或中位数（median）**（中位数更不怕某几轮偶然被离群点带偏），作为 $x_i$ 最终的离群分数（也可以更讲究地只拿"$x_i$ 自己没被抽进样本的那些轮"——即 OOB 轮——来算它的分数）。

**第二步：分析优缺点**
- **优点**：比起只跑一次 k-means，多次重采样把局部最优和初始化随机性平均掉了，分数更稳定。
- **缺点（k-means 本身的毛病没消失）**：k-means 依然**对离群点不稳健**（真把极远点抽进样本时，它要么把中心拉歪，要么干脆自己独占一个中心让距离变 0），而且**必须事先定死 $k$**，还默认簇都是**球形/圆形**（把非圆形数据或稀疏小簇判成异常）。

**第三步：与 Isolation Forest 对比**
- **Isolation Forest**：不靠聚类、不靠中心、**不用选 $k$、甚至不用算距离**——靠随机切分，异常点平均几刀就被孤立（路径短）；速度极快（线性复杂度）、对不规则形状和高维数据适应性强。但具体谁效果更好仍取决于数据结构，应在相同数据集和指标下实测对比。

**④ 小例子**

假设大部分点聚在两团（$2$ 附近和 $11$ 附近，都在 $0\sim 13$ 之间），另外夹杂一个极端离群点在 $x=40$，设 $k=2$：
- **当 $40$ 没被抽进某轮 bootstrap 样本时**（约有 $36.8\%$ 的轮次会发生！）：两个中心一定安稳地落在 $2$ 和 $11$ 附近，这时算 $40$ 到最近中心的距离平方至少 $(40-13)^2=729$，分数爆表！
- **当 $40$ 运气好被抽中（甚至抽中好几次）时**：k-means 可能会狠心把 $40$ 单独当成一个簇中心，让原来那两团挤成一簇——这一轮里 $40$ 离自己中心距离居然是 $0$！
这就是为什么**不能只跑一次**，而且汇总时往往选**中位数**（或只算没抽到它的轮次），这样就能稳稳把 $40$ 揪出来。

**⑤ 常见误区**

- 只算原始距离不做按簇尺度归一化：结果紧实簇周围的小偏移全被放过，松散大簇边缘的正常点全被误报。
- 以为用了 bootstrap 就让 k-means 对离群点完全免疫：它只是**比单次更稳**，但底层还是依赖球形簇假设和预设的 $k$（记住 `k-means is not robust and assumes round clusters`）。

**⑥ 对照最终版**

- `"For b=1..B: take a bootstrap sample, run k-means, and score each point by its (normalized) distance to the nearest center. The outlier score is the mean / median over the runs."` → 完整给出 $B$ 轮 bootstrap + 算最近归一化距离 + 取均值/中位数的流程。
- `"It is more stable than one run, but k-means is not robust and assumes round clusters."` → 评价优缺点：更稳，但 k-means 不稳健且假设球形簇。
- `"Isolation Forest uses random splits: outliers are isolated quickly; no centers, no k."` → 一针见血对比 Isolation Forest（随机切分、迅速孤立、无中心也无需 $k$）。

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

如果训练数据里混进了一堆严重错误的坏点（离群点），普通最小二乘法 OLS 会被拽得面目全非。**RANSAC（RANdom SAmple Consensus，随机抽样一致）** 就是来救场的——怎么用它稳健地把真正的直线拟合出来？考试常考它的**核心思想 + 完整伪代码 + 迭代次数 $T$ 的公式**。

**② 需要的工具（先把名字拆开就能懂一半）**

- **内点（Inlier） vs 离群点（Outlier）**：符合真实规律的正常点叫**内点**（带一点正常小噪声）；传感器故障或标错的极端坏点叫**离群点**。
- **为什么 OLS 会崩掉**（见 5.3）：OLS 把误差**平方**了，一个离真实直线远了 20 的坏点贡献 $20^2=400$ 的惩罚，等于 400 个正常小误差的拉力，能把整条直线硬生生拖歪。
- **名字由来 = 随机抽最小样本（RANdom SAmple） + 全体投票看一致性（Consensus）**：
  - 既然坏点拉偏 OLS，那就**别一开始就把所有点全拿来拟合**！确定一条直线最少只需 **2 个点**（叫**最小样本**，圆则是 3 个点，见 8.5），每次只随机抓 2 个点连成一条试探直线，赌这两个点恰好都是好人（内点）！
  - 直线画出来后，让数据集里所有点站出来表决：只要残差 $|y_i - (ax_i+b)| \le \tau$ 就算支持这条直线（构成**共识集 Consensus set**）。只要其中有一个点挑了坏点，画出的歪斜直线就几乎骗不到其他好人的票；只有两个都抽中好人，画出的真直线才能一呼百应、收获最多内点！
- **阈值 $\tau$**：判断点算不算内点的及格线，大小应当大致匹配正常噪声幅度（选太小、太大的后果见 8.2）。

**③ 一步一步（伪代码 + 重拟合 + $T$ 的推导）**

1. **核心循环（重复 $T$ 次）**：
   - 随机抽取 **2 个不同横坐标的点**，直接过这两点算一条候选直线 $y=ax+b$；
   - 把**全部 $N$ 个点**带进去算竖直残差，找出满足 $|y_i - ax_i - b|\le \tau$ 的内点集合 $I$（共识集）；
   - 记录并保留目前为止**内点个数 $|I|$ 最多**（如平局则选内点误差更小）的那条直线与内点集合。
2. **最后一步极其重要——用全部内点做 OLS 重拟合（Refit）**：
   - 只靠最初那 2 个内点画出的线受局部微噪声抖动影响大，不够准；一旦靠 RANSAC 把坏点全剔除、拿到了干干净净的**最佳内点集**，立刻在这个纯净集合上用普通 OLS 重新拟合一次，得到最精准的直线！
3. **迭代次数 $T$ 的公式怎么背又怎么推？**：
   - 假设数据里真实内点的比例是 $w$（例如 $80\%$ 正常点，$w=0.8$）。
   - 随机抽 2 个点**全都是内点**的概率 $\approx w^2$（有放回/大样本独立近似）；抽**失败**（至少中了一个坏点）的概率 $\approx 1-w^2$；
   - 连续抽 $T$ 次**全部失败**的概率 $\approx (1-w^2)^T$。
   - 我们要求"至少成功一次"的概率 $\ge p$（比如 $p=0.99$），等价于"全部失败"的概率 $\le 1-p$，即 $(1-w^2)^T \le 1-p$。两边取对数（注意 $\log(1-w^2)<0$ 要变号！）：
     $$T \ge \frac{\log(1-p)}{\log(1-w^2)}$$
   - （一般若模型需要 $s$ 个点，就把 $w^2$ 换成 $w^s$；注意样本很小时不放回抽 2 个不同点的精确概率是 $\binom{n_{\text{in}}}{2}/\binom{n}{2}$，大样本下与 $w^2$ 几乎一致。）

**④ 小例子**

数据共 5 个点：$(0,0),\,(1,1),\,(2,2),\,(3,3),\,(4,20)$——前 4 个都在 $y=x$ 上，只有 $(4,20)$ 是离群坏点。取 $\tau=0.5$：
- **普通 OLS**：被 $(4,20)$ 拖偏成 $y=4.2x-3.2$，完全认不出 $y=x$！
- **RANSAC**：
  - 如果倒霉抽到 $(3,3)$ 和 $(4,20)$，连成陡线 $y=17x-48$，结果只有这两个点自己离得近，共识集大小仅 `2`；
  - 如果幸运抽到 $(1,1)$ 和 $(3,3)$，连成 $y=x$，前 4 个点残差全为 $0\le 0.5$，共识集大小高达 `4`！
  - 用这 4 个内点做一次 OLS 重拟合，稳稳拿回完美直线 $y=x$。
- **算算 $T$**：这里 $w=0.8$，想有 $p=0.99$ 把握成功，常用近似公式给出 $T\ge \frac{\log(0.01)}{\log(1-0.8^2)}=\frac{\log(0.01)}{\log(0.36)}\approx 4.51$，即跑 **5 次**。（由于一共才 5 个点且每次抽 2 个不同的点，精确成功率是 $\binom42/\binom52=0.6$，精确下界为 $\frac{\log(0.01)}{\log(0.4)}\approx 5.03$，即 **6 次**；样本量大时两者几乎一样。）

**⑤ 常见误区**

- 写伪代码漏掉最后一步 **`refit by OLS on the best inlier set`**：没有最后全内点重拟合，RANSAC 的参数估计精度会变差。
- 推 $T$ 的不等式时忘记两边都是负数，除以 $\log(1-w^2)$ 没把 $\le$ 翻成 $\ge$；或者以为 $T$ 保证 100% 找到真模型（$p<1$ 只能保证以高概率 $p$ 找到好样本）。
- 只对 $\tau$ 乱填：$\tau$ 必须和正常噪声幅度匹配（细节见 8.2）。

**⑥ 对照最终版**

- 5 行伪代码：`repeat T times` → 每次抽 2 点连直线 → 找残差 $\le \tau$ 的内点集 $I$ → 留 $|I|$ 最大的直线 → 最后用最佳内点集 **OLS 重拟合**。
- `"Choose T\ge\frac{\log(1-p)}{\log(1-w^2)} (w = inlier ratio). It is robust to many outliers."` → 给出轮数 $T$ 的计算公式，并总结其对大量离群点稳健的核心性质。

### 8.7 Give the graphical model of the battery–sensor–alarm system and write the joint distribution. 给出电池—传感器—报警系统的概率图模型并写出联合分布。 ★★

考过：[2023.11 Ex3 a](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex3 a](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 有向图模型（贝叶斯网络）：联合分布＝各节点在给定父节点下的条件分布之积；② [Lab5](../../Exercises/Lab5/Lab5_zh.ipynb) 图模型部分。

**最终版答案（背诵版 EN，≤5 行）：**
Chain **$b\to c\to a$**: $p(a,b,c)=p(b)\,p(c\mid b)\,p(a\mid c)$, so $a\perp b\mid c$.
Data: $P(b=0)=0.1$, $P(c=0\mid b=1)=0.01$, $P(c=0\mid b=0)=0.3$, $P(a=0\mid c=1)=0.99$.
$P(a=0\mid c=0)=q$ is **not given**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

考卷给了一段英文故障说明书（电池坏的概率、电池好/坏时传感器坏的概率、传感器正常时报警的概率）。题目让你：
1. 把"电池 $b$ — 传感器 $c$ — 报警器 $a$"画成一个**概率图模型（有向链）**；
2. 写出三者的**联合概率分布分解公式**；
3. 把题干数字全翻译成条件概率表，并挑出**题目漏给的那个关键条件**！

**② 需要的工具**

- **三个变量约定**（考试里通常 $1$ 表示正常/响，$0$ 表示失效/不响）：
  - $b \in \{0,1\}$：电池（Battery，$1$ 正常 / $0$ 失效）；
  - $c \in \{0,1\}$：传感器（Sensor/Capteur，$1$ 正常 / $0$ 失效）；
  - $a \in \{0,1\}$：报警器（Alarm，$1$ 响起 / $0$ 静默）。
- **概率图（贝叶斯网络）怎么画**：用箭头表示"**谁直接影响谁**"。先有原因后有结果，不能画反。
- **按图分解联合概率**：任何贝叶斯网络的联合分布，都等于"每个节点在给定它箭头上游父节点时的条件概率之积"：
  $$p(a,b,c)=\text{根因概率} \times \text{中间条件概率} \times \text{末端条件概率}$$
- **条件独立符号 $a\perp b\mid c$**：意思是"一旦**已知**中间的传感器 $c$ 是好是坏，$a$ 和 $b$ 就互不相干（条件独立）"。

**③ 一步一步**

1. **画出因果链：$b \to c \to a$**：
   - 电池供电给传感器，所以 $b \to c$；
   - 传感器把监测状态传给报警器，所以 $c \to a$。
   - **为什么没有 $b \to a$ 的直接箭头？** 因为报警器只看得见传感器发来的信号，它并不直接去测电池电压——这就对应假设 $a\perp b\mid c$（给定 $c$ 时，$a$ 与 $b$ 条件独立）。
2. **写出联合分布分解**：
   $$p(a,b,c)=p(b)\,p(c\mid b)\,p(a\mid c)$$
   （口诀：先挑出没有父节点的源头 $b$，再乘上 $c$ 看 $b$ 的脸色，最后乘上 $a$ 只看 $c$ 的脸色！）
3. **把题目给的数据逐条翻成概率（再用 $1-p$ 算出另一半）**：
   - 电池失效概率 $0.1$ $\implies P(b=0)=0.1$（从而正常概率 $P(b=1)=0.9$）；
   - 电池正常时传感器失效 $0.01$ $\implies P(c=0\mid b=1)=0.01$（从而 $P(c=1\mid b=1)=0.99$）；
   - 电池失效时传感器失效 $0.3$ $\implies P(c=0\mid b=0)=0.3$（从而 $P(c=1\mid b=0)=0.7$）；
   - 传感器正常时报警静默 $0.99$（误报率 $0.01$）$\implies P(a=0\mid c=1)=0.99$（从而 $P(a=1\mid c=1)=0.01$）。
4. **抓出考卷里最大的坑——漏给了一个概率**：
   - 手册**根本没说**"传感器失效（$c=0$）时报警器会怎么样"！
   - 必须把 $q = P(a=0\mid c=0)$（传感器坏了但报警却静默的概率）**显式设为未知参数 $q$**（从而响铃概率 $P(a=1\mid c=0)=1-q$），千万不能擅自脑补成 $q=0$ 或 $q=1$。

**④ 小例子**

用刚写好的公式算算最风平浪静的一天——"电池正常、传感器正常、报警不响"的概率：
$$P(b=1,c=1,a=0) = P(b=1)\cdot P(c=1\mid b=1)\cdot P(a=0\mid c=1) = 0.9 \times 0.99 \times 0.99 = \mathbf{0.88209}$$
（大约 88.2% 的时间里三样东西都安安静静正常工作。）

**⑤ 常见误区**

- 把箭头画反成 $a\to c\to b$：因果关系必须是电池先影响传感器、传感器再影响报警。
- 没发现 $P(a=0\mid c=0)$ 缺失而自己瞎假设"传感器坏了报警一定响（$q=0$）"：实际考试 2023 和 2024 原卷都漏掉了这个条件，正确做法是设为参数 $q$ 保留在后面所有推导里！

**⑥ 对照最终版**

- `"Chain b\to c\to a: p(a,b,c)=p(b)\,p(c\mid b)\,p(a\mid c), so a\perp b\mid c."` → 给出链式图模型、联合分解和条件独立结论。
- `"Data: P(b=0)=0.1, P(c=0\mid b=1)=0.01, P(c=0\mid b=0)=0.3, P(a=0\mid c=1)=0.99."` → 精准列出题干已给的 4 条参数。
- `"P(a=0\mid c=0)=q is not given."` → 明确点出未知参数 $q$ 未给出。

### 8.8 Are a and b independent? (conditional vs marginal independence) a 和 b 独立吗？（条件独立与边际独立） ★★

考过：[2023.11 Ex3 b](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex3 b](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** ① 链 $b\to c\to a$ 中，观测到 $c$ 会"阻断"路径；② 边际独立要用全概率公式真正算出来比较。

**最终版答案（背诵版 EN，≤5 行）：**
Given $c$, **$a$ and $b$ are independent**: both rows of the table $p(a=1\mid b,c)$ are equal ($1-q$ and $0.01$).
But they are **not marginally independent**: $P(a=1\mid b)=\sum_cP(a=1\mid c)P(c\mid b)$ differs for $b=0$ and $b=1$ (except if $q=0.99$).

**解析版（小白也能看懂）：**

**① 这道题在问什么**

考题经常先让你填出 $p(a=1\mid b,c)$ 的 $2\times 2$ 表格，再连环拷问：**报警器 $a$ 和电池 $b$ 到底独不独立？**
这里故意设了一个"条件独立 vs 边际独立"的思维区分题：**已知传感器 $c$ 时独立吗？不知道传感器 $c$ 时还独立吗？**

**② 需要的工具**

- **独立（边际独立 Marginal independence）**：哪怕其它一概不知，单看 $b$ 变不变，不会改变 $a$ 响铃的概率，即 $P(a=1\mid b=0) = P(a=1\mid b=1)$。
- **条件独立（Conditional independence, $a\perp b\mid c$）**：**在已经确定传感器 $c$ 状态的前提下**，再告诉你电池 $b$ 好不好，对预测报警 $a$ 没有任何新帮助，即 $P(a\mid b,c)=P(a\mid c)$。
- **路径"被阻断"的直觉**：在链 $b\to c\to a$ 里，电池 $b$ 想影响报警器 $a$，必须**借道传感器 $c$**。
  - 你要是已经盯死了中间站 $c$ 的状态，这条传话通道就被**堵住（阻断）**了，$b$ 和 $a$ 就条件独立；
  - 你要是不知道中间站 $c$ 啥样（只能对 $c$ 做**全概率求和**跨过去），电池状态就会顺着通道漏过去影响报警！

**③ 一步一步**

1. **先写出题干要的 $2\times 2$ 表 $p(a=1\mid b,c)$**（因为链结构下 $a$ 只看 $c$ 的脸色，跟 $b$ 没关系）：

   | $p(a=1\mid b,c)$ | 传感器坏 ($c=0$) | 传感器好 ($c=1$) |
   |---|---|---|
   | **电池坏 ($b=0$)** | $1-q$ | $0.01$ |
   | **电池好 ($b=1$)** | $1-q$ | $0.01$ |

2. **第一问：条件独立吗（给定 $c$）？—— 独立！**
   看上面表格的第一行（$b=0$）和第二行（$b=1$）**完全一模一样**！这用最硬核的表格直接证明了：只要已知 $c$，$b$ 取 $0$ 还是 $1$ 根本改变不了 $a$ 响的概率，所以**给定 $c$ 时，$a$ 和 $b$ 条件独立（$a\perp b\mid c$）**。
3. **第二问：边际独立吗（不给定 $c$）？—— 一般不独立！**
   不知道 $c$ 时，必须用全概率公式 $P(a=1\mid b)=\sum_{c\in\{0,1\}} P(a=1\mid c)P(c\mid b)$ 把传感器好坏两种情况加起来：
   - **电池正常（$b=1$）**：$P(a=1\mid b=1)=0.99\times 0.01 + 0.01\times(1-q) = \mathbf{0.0199 - 0.01q}$；
   - **电池失效（$b=0$）**：$P(a=1\mid b=0)=0.70\times 0.01 + 0.30\times(1-q) = \mathbf{0.307 - 0.30q}$。
   对比两式：令 $0.0199-0.01q = 0.307-0.30q \implies 0.29q = 0.2871 \implies \mathbf{q=0.99}$。
   - **只要 $q\ne 0.99$**：两个概率不等，所以 **$a$ 和 $b$ 不边际独立**；
   - **特例 $q=0.99$**：意味着不管传感器坏没坏，报警器不响的概率永远是 0.99（报警器压根不看传感器脸色），这时才退化成边际独立。

**④ 小例子**

假设传感器坏了有一半概率会触发报警（取 $q=0.5$）：
- 电池正常时，$P(a=1\mid b=1)=0.0199-0.005=\mathbf{0.0149}$（大约 1.5% 响铃）；
- 电池坏了时，$P(a=1\mid b=0)=0.307-0.15=\mathbf{0.157}$（约 15.7% 响铃，高了 **10 倍**！）。
不知道传感器状态时，电池坏不坏明显牵动报警率——二者边际不独立！但一旦你走近一看"确认传感器此刻是正常的（$c=1$）"，不管电池好不好，报警率立刻统一锁定在 `0.01`（条件独立）。

**⑤ 常见误区**

- 把"条件独立"和"边际独立"混为一谈，答成"有箭头连着所以一定也不条件独立"，或者"条件独立所以就独立了"：在 $b\to c\to a$ 链上，**条件独立成立，但边际一般不独立**！
- 忘记提 `$q=0.99$` 的例外：光看图有连线其实不能百分之百断定边际一定相关，必须算出全概率式子发现仅当 $q=0.99$ 时例外相等。

**⑥ 对照最终版**

- `"Given c, a and b are independent: both rows of the table p(a=1\mid b,c) are equal (1-q and 0.01)."` → 先答条件独立，直接用表格两行相等 ($1-q$ 和 $0.01$) 说明。
- `"But they are not marginally independent: P(a=1\mid b)=\sum_c P(a=1\mid c)P(c\mid b) differs for b=0 and b=1 (except if q=0.99)."` → 再答边际不独立，给出全概率公式说明 $b=0,1$ 结果不同（同时严谨标出 $q=0.99$ 特例）。

### 8.9 How do you compute P(battery fails | no alarm) from the model? 如何用模型计算"没听到报警时电池失效"的概率？ ★★

考过：[2023.11 Ex3 c–d](../DataML-CHPS-2023-examen_zh.md) · [2024 Ex3 c–d](../DataML-CHPS-2024-examen_zh.md)

**先懂这些：** 全概率公式（对未观测变量求和＝边缘化）与 Bayes 公式；数值答案见两卷参考答案。

**最终版答案（背诵版 EN，≤5 行）：**
**Sum out** the unknown variables, then use **Bayes**:
$P(c=0)=0.039$, $P(a=0)=0.95139+0.039q$, $P(a=0,b=0)=0.0693+0.03q$,
so $P(b=0\mid a=0)=\frac{0.0693+0.03q}{0.95139+0.039q}$ (between 0.073 and 0.100).

**解析版（小白也能看懂）：**

**① 这道题在问什么**

这是 8.7、8.8 的紧接计算追问：
- 先算 **报警保持静默** 的总概率 $P(a=0)$；
- 再算 **在没听到报警的前提下，电池其实失效了** 的后验概率 $P(b=0\mid a=0)$（注意不知道传感器 $c$ 的状态）。

**② 需要的工具（三步打通贝叶斯推理）**

- **全概率公式 / 边缘化（Sum out / Marginalization）**：中间有不知道状态的变量（比如算 $a$ 时不知道 $c$ 和 $b$），把所有可能路径的概率全部加起来就行。
- **乘法法则**：一条完整分支的概率 $=$ 源头概率 $\times$ 下一级条件概率 $\times \dots$
- **Bayes 公式（倒果推因）**：
  $$P(b=0\mid a=0)=\frac{P(a=0,\,b=0)}{P(a=0)}$$
  平时给你的参数都是"因为电池坏，所以……"（由因到果）；现在看见了结果"报警没响（$a=0$）"，用贝叶斯公式就能反推源头"电池坏了（$b=0$）"的可能性！
- **先验 vs 后验**：还没听见任何消息前，电池坏的**先验概率**是 $0.1$；听见"报警没响"这个证据后，更新得到的就是**后验概率**。

**③ 一步一步（像剥洋葱一样从 $b \to c \to a$ 算下来）**

1. **第 1 步：先把不知道的 $b$ 加掉，算出传感器坏的概率 $P(c=0)$**
   传感器坏有两种途径（电池正常却自己坏、或者电池坏了连累它坏）：
   $$P(c=0)=P(b=1)P(c=0\mid b=1)+P(b=0)P(c=0\mid b=0)=0.9\times 0.01 + 0.1\times 0.3 = \mathbf{0.039}$$
   从而传感器正常的概率是 $P(c=1)=1-0.039=\mathbf{0.961}$。
2. **第 2 步：再把不知道的 $c$ 加掉，算出静默的概率 $P(a=0)$**
   静默也有两条路（传感器好且没误报、传感器坏且静默）：
   $$P(a=0)=P(c=1)P(a=0\mid c=1)+P(c=0)P(a=0\mid c=0)=0.961\times 0.99 + 0.039\times q = \mathbf{0.95139+0.039q}$$
   这就是真题 (c) 问的最终式子（保留未知数 $q$）。
3. **第 3 步：算分子——"既电池坏、又没报警"的联合概率 $P(a=0, b=0)$**
   固定 $b=0$，把传感器正常和坏的两条分支相加（即对 $c$ 求和）：
   $$P(a=0,b=0)=P(b=0)\Big[P(c=1\mid b=0)P(a=0\mid c=1)+P(c=0\mid b=0)P(a=0\mid c=0)\Big]=0.1\times(0.7\times 0.99+0.3q)=\mathbf{0.0693+0.03q}$$
4. **第 4 步：代进 Bayes 公式，算条件概率 $P(b=0\mid a=0)$**
   $$P(b=0\mid a=0)=\frac{P(a=0,b=0)}{P(a=0)}=\frac{\mathbf{0.0693+0.03q}}{\mathbf{0.95139+0.039q}}$$
   这就是真题 (d) 问的答案！
5. **检查数值范围与直觉解释**：
   - 由于 $q\in[0,1]$，代入算得结果落在 **`0.0728`（当 $q=0$）到 `0.1003`（当 $q=1$）**之间。
   - **为什么大多数时候低于 0.1，接近 $q=1$ 时反而略高于 0.1？** 如果传感器坏了报警大概率会响（$q<0.99$），那"没听见响"算个好消息，电池坏的后验概率就比先验 $0.1$ 低；但若传感器坏了以后几乎哑火（$q>0.99$，比正常时的 $0.99$ 还更容易保持沉默），没听见响反而微微增加了一丝电池/传感器出毛病的嫌疑（临界点恰好是 8.8 里让 $a,b$ 独立的 $q=0.99$）。

**④ 小例子**

假如题干补一句"传感器坏了一半概率沉默"，即取 $q=0.5$：
- 没报警概率 $P(a=0)=0.95139+0.039\times 0.5 = 0.97089$；
- 联合概率 $P(a=0,b=0)=0.0693+0.03\times 0.5 = 0.0843$；
- 后验概率 $P(b=0\mid a=0)=0.0843/0.97089\approx \mathbf{0.0868}$（约 8.7%，比原来的先验 10% 安心了一点点）。

完整分支计算表见 [计算题 C3](00_calculations.md)。

**⑤ 常见误区**

- 没注意到 $q=P(a=0\mid c=0)$ 题干未给，在第二步随便塞了一个数值算死（考试必须保留含 $q$ 的表达式）。
- 把 $P(b=0\mid a=0)$（**已知没报警**，问电池坏没坏）和 $P(a=0\mid b=0)$（**已知电池坏**，问报不报警）弄反——一个是"由果推因"（需用 Bayes），一个是"由因推果"（只需全概率公式）。

**⑥ 对照最终版**

- `"Sum out the unknown variables, then use Bayes:"` → 整个推理的两大核心动作：先把未知中间变量加掉（边缘化），再用贝叶斯公式倒推。
- `"P(c=0)=0.039, P(a=0)=0.95139+0.039q, P(a=0,b=0)=0.0693+0.03q,"` → 背熟这三个关键中间结果，考场上一路验算不出错。
- `"so P(b=0\mid a=0)=\frac{0.0693+0.03q}{0.95139+0.039q} (between 0.073 and 0.100)."` → 含参数 $q$ 的最终答案及上下界范围。

### 8.2 How sensitive is RANSAC to its parameters? RANSAC 对参数的敏感性如何？ ★

考过：[2023.3 Ex2 c](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** 8.1 的三个参数；在作业一中改变 $\tau$ 看内点集的变化。

**最终版答案（背诵版 EN，≤5 行）：**
**τ**: too small rejects good points; too large accepts outliers. Choose it from the **noise level**.
**T**: too small may miss a clean sample; too large only costs time. $T$ grows fast when there are more outliers.
The results are **random**.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

RANSAC 用起来要自己调几个超参数（主要是内点阈值 $\tau$ 和迭代次数 $T$）。这些参数选偏了会出什么事？RANSAC 整体对参数敏感吗？

**② 需要的工具**

- **内点阈值 $\tau$**（见 8.1）：点到直线的残差 $\le \tau$ 才被当成好人（内点）。**它是最敏感、最关键的参数**。
- **噪声尺度（Noise level）**：正常好点围绕真实直线上下正常抖动的幅度（比如传感器本身有 $\pm 0.2$ 的测量误差）。
- **MAD（中位数绝对偏差，Median Absolute Deviation）**：一种抗离群点的"稳健标准差"，用中位数去估计正常数据的抖动有多大，不会被几个极端坏点带偏。
- **迭代次数 $T$**：抽多少轮最小样本（直线 $s=2$，圆 $s=3$）。

**③ 一步一步（逐个拆解敏感性）**

1. **对阈值 $\tau$ 很敏感（选不好两头挨打）**：
   - **$\tau$ 太小**（门槛卡太死）：很多正常但稍微带点测量噪声的好点被错杀赶出共识集 $\implies$ 剩的点太少，拟合不稳、方差变大；
   - **$\tau$ 太大**（门槛放太宽）：连离群坏点也被大水漫灌放进共识集，最后重拟合 OLS 时直接把直线拉歪，稳健性全没了；
   - **该怎么选**：必须贴合数据本身的**正常噪声水平**（例如噪声标准差的 2～3 倍，或借助 MAD 等稳健尺度估算，也可以用验证集微调）。
2. **对迭代次数 $T$ 是"单边敏感"**：
   - **$T$ 太小**：可能整个 $T$ 轮运气不好**一轮干净的全内点样本都没抽到**，于是直接错失真实模型；
   - **$T$ 太大**：不会把模型变差，只是**白白多花计算时间**；
   - **坏点一多，$T$ 暴增**：记住公式 $T \ge \frac{\log(1-p)}{\log(1-w^s)}$，当内点比例 $w$ 变低（离群点多）或模型需要的点数 $s$ 变大（高维/复杂形状），$w^s$ 会迅速缩小，$T$ 会急剧飙升！
3. **可选的最小共识集大小 & 固有随机性**：
   - 如果设了"共识集至少要有多少人才算通过"，门槛太高可能谁都选不上，太低可能把假直线当真；
   - 此外因为每轮都是随机抽点，哪怕参数固定，不同次跑出来的结果也带有**随机性（random）**（需设固定种子，或用全部内点 OLS 重拟合、平局时比内点总误差来减稳）。

**④ 小例子**

1. **先看 $\tau$ 的敏感**：真实直线是 $y=x$，好点带有 $\pm 0.1$ 噪声，离群点偏离 $1.5$。若 $\tau=0.02$（太小），连 $(1, 1.05)$ 这种好点也被踢出去；若 $\tau=2.0$（太大），把偏离 $1.5$ 的坏点也拉进来做 OLS，线又歪了；选 $\tau \approx 0.3$ 刚好把好点全留下、坏点全挡在门外。
2. **再看 $T$ 如何随坏点比例暴涨**（要求成功率 $p=0.99$）：

   | 模型所需最少点数 | 50% 内点 ($w=0.5$) | 70% 内点 ($w=0.7$) |
   |---|---|---|
   | **直线 ($s=2$)** | 17 次 | 7 次 |
   | **圆 ($s=3$)** | **35 次** | 11 次 |

   内点比例从 70% 降到 50%，圆模型所需迭代次数直接从 11 次跳涨到 **35 次**；如果 $w$ 跌到 $0.1$（90% 坏点），拟合圆甚至要约 $4603$ 次！

**⑤ 常见误区**

- 以为"$T$ 越大模型就越准"：其实一旦大概率已经覆盖到干净样本，继续把 $T$ 翻 10 倍只会多花 10 倍时间，真正决定好不好的是 $\tau$ 是否贴近真实噪声。
- 忘了最后回答一句 **`The results are random`**（因为抽样随机，每次结果可能轻微波动）。

**⑥ 对照最终版**

- `"τ: too small rejects good points; too large accepts outliers. Choose it from the noise level."` → 点出 $\tau$ 太小/太大的双向风险与设定依据（噪声尺度）。
- `"T: too small may miss a clean sample; too large only costs time. T grows fast when there are more outliers."` → 点出 $T$ 的非对称敏感性与随离群点增多急剧增长的规律。
- `"The results are random."` → 总结随机抽样带来的结果随机性。

### 8.3 What is the difference between RANSAC and a typical bootstrap estimation procedure? RANSAC 与典型的 bootstrap 估计有什么区别？ ★

考过：[2023.3 Ex2 c](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** [第五课 · 一般而言，bootstrap 是什么？](../../Lectures/05_NLM_zh.md)；Bagging（2.3）。

**最终版答案（背诵版 EN，≤5 行）：**
**Bootstrap**: samples of **size N with replacement**, to estimate the **variance** of an estimator or to **average** models. Outliers stay inside, so it does **not make a non-robust estimator** (e.g. OLS) robust.
**RANSAC**: **minimal samples** (2 points), and it keeps the **best consensus**, not the average.
Its goal is **robustness** and finding outliers.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

**RANSAC** 和 **Bootstrap**（见 2.3 / 第五课）表面上看起来很像——都是从原数据里一遍遍地"随机抽样本 → 跑一次拟合 → 循环很多轮"。那它俩到底有什么本质区别？能不能用 Bootstrap 代替 RANSAC 来抗离群点？

**② 需要的工具**

- **Bootstrap（自助法 / 重采样）**：从 $N$ 个样本中**有放回**地抽满同样大小 **$N$ 个**样本，重复 $B$ 轮，把每轮算出来的模型/统计量收集起来，用来**估计方差（不确定性）**或者像 Bagging 那样**做平均**。
- **RANSAC**：每轮只**不放回**地抽取能定出模型的**最小样本**（如直线 $2$ 个点、圆 $3$ 个点），算出候选模型后用全部数据投票，**只保留得票（内点）最多的那一个赢家**。

**③ 一步一步（一张表彻底对比清楚）**

| 对比维度 | Bootstrap 估计 | RANSAC |
|---|---|---|
| **每轮抽几个点** | 和原数据集一样大（**$N$ 个**） | **最小样本**（极小，直线只要 **2 个**） |
| **抽样方式** | **有放回**（同一点可被抽多次） | 同一轮内**不放回**（需选不同的点来定模型） |
| **多轮结果怎么合** | **全留下来汇总**：求标准差/置信区间，或把所有模型**取平均**（Bagging） | **只要第一名**：按共识集大小打分，**只选最好那一个模型**（丢掉其余） |
| **离群点去哪了** | **一直留在样本里**（比例和原数据差不多），无法自动把坏 estimator 变稳健 | 赌在某轮**抽不到离群点**，借共识票把离群点全部揪出来踢掉 |
| **核心目的** | 评估**方差/不确定性**，或平均降低方差 | **稳健估计**（抗海量离群点）+ **找离群点** |

**重点补一刀**：如果原来的估计方法本身不稳健（比如 **OLS**），套一层 Bootstrap 依然**不会**让它变稳健——每轮重采样样本里照样混着坏点，算出的每条直线依然是歪的，平均之后还是歪的！（Bootstrap 的稳健性完全取决于里面包的那个估计量自身稳不稳健，比如对中位数做 Bootstrap 才稳健。）

**④ 小例子**

假设有 100 个点，其中 **20% 是极端坏点**，想拟合直线：
- **用 Bootstrap + OLS**：每轮有放回抽 100 个点，里面大概率还是含约 20 个坏点。每轮 OLS 都被这 20 个坏点拽偏，跑 500 轮求平均，得到的还是一条被拽歪的线！
- **用 RANSAC**：每轮只抽 2 个点，单轮两个点全抽到正常好点的概率高达 $0.8^2 = \mathbf{64\%}$！只要任何一轮抽对（跑 5 轮没抽对的概率不到 $0.36^5 \approx 0.6\%$），这条线就能拿到 80 个内点投票，轻松淘汰那 20 个坏点，再重拟合就还原出完美直线。

**⑤ 常见误区**

- 以为"都是重采样"，所以 Bootstrap + OLS 也能抗离群点（大错特错！坏点依然每次都被抽进这 $N$ 个点里）。
- 忘了强调 RANSAC **不是求平均**，而是 **选出共识最好的那个**（`keeps the best consensus, not the average`）。

**⑥ 对照最终版**

- `"Bootstrap: samples of size N with replacement, to estimate the variance of an estimator or to average models. Outliers stay inside, so it does not make a non-robust estimator (e.g. OLS) robust."` → 概括 Bootstrap 的抽样规模/方式、目的（算方差或平均），并点明坏点仍在样本中、救不了不稳健估计量。
- `"RANSAC: minimal samples (2 points), and it keeps the best consensus, not the average."` → 概括 RANSAC 的最小样本与"只选最佳共识、不平均"。
- `"Its goal is robustness and finding outliers."` → 总结 RANSAC 的目标（稳健性与找离群点）。

### 8.4 How can the internal RANSAC models "grade" datapoints as outliers, and the datapoints "grade" each model? RANSAC 内部的模型如何给数据点"打分"（是否离群），数据点又如何给模型打分？ ★

考过：[2023.11 Ex4 c](../DataML-CHPS-2023-examen_zh.md)

**先懂这些：** 8.1 中的残差 $r_i$ 和共识集 $I$；把 $T$ 个候选模型看成一张"模型×点"的残差表。

**最终版答案（背诵版 EN，≤5 行）：**
**Models grade points**: each model says inlier ($r\le\tau$) or outlier; a point rejected by most **good** models is an outlier.
**Points grade models**: the score of a model is its **number of inliers** (or a truncated loss $\sum_i\min(r_i^2,\tau^2)$).

**解析版（小白也能看懂）：**

**① 这道题在问什么**

RANSAC 跑 $T$ 轮时会造出 $T$ 条候选模型（老师）和 $N$ 个数据点（学生）。题目用了一个特别形象的比喻——**"双向互评打分"**：
1. 里面的模型怎么给每个数据点"打分"（谁像离群点）？
2. 数据点又怎么反过来给每个候选模型"打分"（哪条模型最好）？

**② 需要的工具（想象一张"模型 $\times$ 点"的双向评分表）**

- **残差表 $r_{it}$**：行是第 $t$ 个候选模型，列是第 $i$ 个数据点，格子里记着点 $i$ 离模型 $t$ 的距离（残差）$r_{it}$。
- **二值判别（内点 / 离群）**：只要 $r_{it} \le \tau$，模型 $t$ 就认点 $i$ 是内点（打 1 分好评 / 0 分离群嫌疑）；若 $r_{it} > \tau$ 就拒绝它（标为离群点，或给软距离分 $r_{it}/\tau$）。
- **截断损失（Truncated loss, 如 MSAC）**：$\sum_{i=1}^N \min(r_{it}^2,\,\tau^2)$。对好点照常算平方误差，对超过 $\tau$ 的坏点一律封顶按 $\tau^2$ 惩罚——这样既防坏点拖垮总分，又能在同样内点数时挑出贴得更近的模型。

**③ 一步一步（横着看 vs 竖着看）**

每轮生成模型 $m_t$ 后，算出它对所有点的残差 $r_{it}$，就能做双向打分：

1. **模型给数据点打分（Models grade points —— 竖着汇总好模型的评价）**：
   - 每个模型判断点 $i$ 算不算自己的内点（$r_{it}\le \tau$）还是离群点（$r_{it}>\tau$）；
   - **关键规则：只听好模型（或按模型好坏加权）的话！** 把那些内点多、质量高的**好模型**对点 $i$ 的评价汇总（算平均拒绝率或加权平均残差）：**被大多数好模型拒绝的点，就是离群点**！（抽到坏点造出来的歪模型本身就瞎，不能让它和好模型一人一票平起平坐。）
2. **数据点给模型打分（Points grade models —— 横着加总所有点的投票）**：
   - 站在模型 $m_t$ 这一行，让 $N$ 个点投票：谁觉得 $r_{it}\le\tau$，就给这个模型投 1 票——模型的得分就是它收获的**内点总数 $|I_t|$**（标准 RANSAC）；
   - 进阶打法是改算**截断损失** $\sum_i \min(r_{it}^2,\tau^2)$（越小越好）：内点数一样时，内点误差越小的模型得分更高。

**④ 小例子**

拿 8.1 的 5 个点 $\{p_1=(0,0),\ p_2=(1,1),\ p_3=(2,2),\ p_4=(3,3),\ p_5=(4,20)\}$，取 $\tau=0.5$，看表里两行模型：

| 候选模型 \ 点 | $p_1(0,0)$ | $p_2(1,1)$ | $p_3(2,2)$ | $p_4(3,3)$ | $p_5(4,20)$ | **点给模型打分（内点数）** |
|---|---|---|---|---|---|---|
| **$m_1: y=x$**（好模型） | 内点 (0) | 内点 (0) | 内点 (0) | 内点 (0) | **离群 (16)** | **4 票（胜出）** |
| **$m_2: y=17x-48$**（烂模型） | 离群 (48) | 离群 (32) | 离群 (16) | 内点 (0) | 内点 (0) | 2 票（淘汰） |

- **横向（点给模型打分）**：$m_1$ 得 **4 票**完胜 $m_2$ 的 **2 票**！
- **纵向（模型给点打分）**：只要忽略淘汰的烂模型 $m_2$，只看选出来的好模型（们）对 $p_5$ 的评价——$p_5$ 被好模型一致判为离群点（残差 16 远大于 $\tau=0.5$），于是稳稳抓出离群点 $p_5$。

**⑤ 常见误区**

- 让所有 $T$ 个模型（包括大量抽中坏点产生的垃圾模型）平等投票来判断点是不是离群点：如果好模型比例不多时这样平均，结果会被垃圾模型带偏；必须强调看 **`good models`**。
- 只写"内点数"，忘了多写一句进阶版截断损失 $\sum_i\min(r_i^2,\tau^2)$ 很容易加分。

**⑥ 对照最终版**

- `"Models grade points: each model says inlier (r\le\tau) or outlier; a point rejected by most good models is an outlier."` → 清晰写出模型如何给点打分（阈值判定 + 好模型多数拒绝即离群）。
- `"Points grade models: the score of a model is its number of inliers (or a truncated loss \sum_i\min(r_i^2,\tau^2))."` → 清晰写出点如何给模型打分（内点计数或截断损失）。

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

前面学的 RANSAC 用来拟合直线，但真实数据里有一群点其实沿着一个**圆**分布（周围还混着一堆坏点）。怎样把标准 RANSAC "改造成"**拟合圆 $C(c,r)$** 的版本？

**② 需要的工具**

- **RANSAC 通用骨架**（见 8.1）：不管拟合直线、圆还是抛物线，主循环都一样——**抽最小样本 → 算模型 → 全员投票找内点 → 保留最多内点 → 全内点重拟合**。要变的只有 3 个零件 + $T$ 的幂次。
- **三点定圆**：平面上只要 3 个**不共线**的点，就能唯一画出一个圆（2 个点能画出无数个圆）。
- **径向距离（Radial distance）$\big|\|p_i-c\|-r\big|$**：点 $p_i$ 到圆心 $c$ 的距离 $\|p_i-c\|$，再减去半径 $r$ 的绝对值——它就是点到**圆周边界的真实几何距离**（在圆外多出多少、或在圆内缩进多少）。

**③ 一步一步（骨架不动，只改这 3 处）**

1. **改动①——最小样本改成 3 个点（不共线）**：
   - 每次循环随机抽 3 个点 $p_1,p_2,p_3$。如果三点几乎连成一条直线（共线），根本定不出圆，直接跳过重抽。
   - 怎么算圆心 $c=(x_c,y_c)$ 和半径 $r$？因为三点到圆心等距（$\|p_j-c\|^2=\|p_1-c\|^2$），展开后 $x_c^2+y_c^2$ 两边正好消掉，只剩两个线性方程：
     $$2(p_j-p_1)^Tc=\|p_j\|^2-\|p_1\|^2 \quad (j=2,3)$$
     解出圆心 $c$ 后，半径就是 $r=\|p_1-c\|$。
2. **改动②——残差改成径向几何距离**：
   - 对全部点算到圆周的真实距离 $e_i=\big|\|p_i-c\|-r\big|$；凡是 $e_i\le\tau$ 的点算进内点共识集（$\tau$ 依然按正常噪声水平定）。
   - **千万别用代数差 $|\|p_i-c\|^2-r^2|$**：它和半径大小纠缠在一起，会歪曲真实几何距离。
3. **改动③——最后用全部内点做最小二乘重拟合**：
   - 循环 $T$ 次留出内点数最多的一批内点 $I$ 后，在 $I$ 上用最小二乘重新优化 $\min_{c,r}\sum_{i\in I}(\|p_i-c\|-r)^2$（可用代数最小二乘解当初值再迭代几步），得到比 3 个点更精准的圆。
4. **别忘了改迭代次数 $T$**：一次抽 3 个点全是内点的概率降为 $\approx w^3$，所以次数要加到：
   $$T\ge \frac{\log(1-p)}{\log(1-w^3)}$$

**④ 小例子**

1. **手算三点定圆**：抽到 $p_1=(1,0),\ p_2=(0,1),\ p_3=(-1,0)$：
   - $j=2$: $2\big((0,1)-(1,0)\big)\cdot(x_c,y_c) = 1-1 \implies -2x_c+2y_c=0 \implies y_c=x_c$；
   - $j=3$: $2\big((-1,0)-(1,0)\big)\cdot(x_c,y_c) = 1-1 \implies -4x_c=0 \implies x_c=0$。
   立刻解出圆心 $c=(0,0)$，半径 $r=\|(1,0)-(0,0)\|=1$（单位圆），接下来拿 $\big|\|p_i-(0,0)\|-1\big|\le\tau$ 去扫所有点即可！
2. **为什么不能用代数差**：半径 $r=100$ 时，某个点只离圆周 $1$ 单位（在 $r=101$ 处），真实径向距离就是 $1$；但代数差却是 $101^2-100^2=201$，直接会被误杀成离群点！

**⑤ 常见误区**

- 还习惯性写"抽 2 个点"或公式里还写 $w^2$：拟合圆必须 **3 个不共线的点**、公式必须是 **$w^3$**。
- 用 $\|p_i-c\|^2-r^2$ 当作内点判定残差。

**⑥ 对照最终版**

- `"Same algorithm, with three changes:"` → 框架不变，直奔三大改动。
- `"(1) sample 3 points (one circle passes through 3 non-collinear points);"` → 改动一：3 个不共线点。
- `"(2) residual = radial distance \big|\|p_i-c\|-r\big|;"` → 改动二：径向几何距离。
- `"(3) refit (c,r) on the inliers by least squares. Use T\ge\log(1-p)/\log(1-w^3)."` → 改动三：内点最小二乘重拟合 + $w^3$ 轮数公式。

### 8.6 Robustly estimate δ = ‖μ − m‖ (mean vs medoid) with RANSAC when each instance has a quality indicator qᵢ. 每个样本带质量指标 qᵢ 时，用 RANSAC 稳健估计 δ = ‖μ − m‖（均值与 medoid 之差）。 ★

考过：[2023.3 Ex2 d](../DataML-CHPS-2022-examen_zh.md)（开放设计题）

**先懂这些：** ① 均值对离群点敏感，medoid 是真实样本中最"居中"的；② 8.1 的"候选—共识—重拟合"框架。

**最终版答案（背诵版 EN，≤5 行）：**
$\delta$ compares the **mean** (sensitive to outliers) with the **medoid** (the most central real point); a large $\delta$ means skew or outliers.
RANSAC: sample points with probability $\propto q_i$, compute a candidate center, inliers = points within τ, score = $\sum_{i\in I}q_i$.
On the best inlier set compute $\hat\mu$, $\hat m$ and $\hat\delta=\|\hat\mu-\hat m\|$. Do not use $q_i$ as a coordinate.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

这是一道开放设计题，里面藏了两个小概念：
1. 为什么我们要研究 $\delta=\|\mu - m\|$（均值 $\mu$ 和中心样本 medoid $m$ 之间的距离）？
2. 现在每个样本 $x_i$ 还自带一个"靠谱度/质量分" $q_i\ge 0$（越大越可信）。怎么改造 **RANSAC**，在有离群点时稳健地估计这个 $\delta$？（还要小心别把 $q_i$ 用错地方！）

**② 需要的工具**

- **均值 $\mu$（Mean） vs 中心样本 $m$（Medoid）**：
  - $\mu$ 是所有点平均出来的虚拟中心——只要有几个离群点，$ \mu$ 立刻会被拽偏；
  - $m$ 是数据集里真实存在的、离其他人总距离最小的那个"最居中的人"（一维近似中位数）——只要大多数点是正常的，$m$ 稳如泰山、不会被一两个坏点带跑。
- **差值 $\delta = \|\mu - m\|$ 的物理直觉**：
  - 如果数据长得对称、抱成一团，均值和最居中点几乎重合，$\delta$ 很小；
  - 一旦 $\delta$ 很大，就暴露了数据**长歪了（偏斜 skew）、分了好几团，或者混入了离群点**！
- **质量指标 $q_i$ 的正确用法 vs 错误用法**：$q_i$ 表示第 $i$ 个点有多可靠，但它**不是空间坐标**，绝不能拼进距离公式 $\|x_i-c\|$ 里去，而应该用来指导"**谁更有资格抽中、谁投的一票更重**"！

**③ 一步一步（先把 $\delta$ 讲清，再设计 4 步 RANSAC 流程）**

1. **先点出 $\delta$ 在干嘛**：$\delta=\|\mu-m\|$ 对比容易受离群点影响的均值和稳健的 medoid，用来衡量数据主体的偏斜或离群点干扰程度。
2. **用加权 RANSAC 找到"干净又靠谱"的内点集 $I^*$**：
   - **抽样**：每次按与质量指标 $q_i$ 成正比的概率抽样（如只抽 1 个或少量点）来生成一个候选中心 $c$（质量高的点更有机会代表大家；若全为 0 则退回均匀抽样）；
   - **划圈定内点**：只看原本 $\mathbb R^d$ 特征空间里的距离 $\|x_i-c\|\le\tau$ 来判定谁是内点集合 $I$（**绝对不要把 $q_i$ 放进距离里！**）；
   - **给候选打分**：算这批内点的**质量总和 $\sum_{i\in I} q_i$**（比简单数人头更聪明——集齐一堆高质量内点才得高分！）；
   - 重复 $T$ 轮，挑出质量总分最高的最佳共识集 $I^*$。
3. **最终估计 $\hat\delta$**：就在脱敏后的纯净内点集 $I^*$ 里，分别算出普通均值 $\hat\mu$ 和 medoid $\hat m$，最终输出 $\hat\delta = \|\hat\mu - \hat m\|$（还可以外层多跑几次看 $\hat\delta$ 的波动范围，衡量不确定性）。

**④ 小例子**

一维数据 $\{1, 2, 3, 4, 100\}$，其中前 4 个点质量很高（$q_i=1$），$100$ 是坏点（比如 $q_5=0.1$ 或哪怕也混在里面）：
- **直接算全数据**：均值 $\mu=22$，medoid $m=3$（$3$ 到其余点距离和最小 $=101$），于是 $\delta = |22-3| = \mathbf{19}$ —— 完全是被坏点 $100$ 炸出来的虚高！
- **加权 RANSAC 筛选后**：靠更高的 $q_i$ 抽到中心 $2$ 或 $3$，取 $\tau=2$，共识集干净锁定 $I^*=\{1,2,3,4\}$（质量总和 $4$），踢掉 $100$。再在这个主体里算：$\hat\mu = 2.5$，$\hat m = 2$ 或 $3$，得到真实主体的 $\hat\delta = \mathbf{0.5}$（非常对称紧凑！）。

**⑤ 常见误区**

- 把 $q_i$ 当成第 $d+1$ 维特征拼进去算欧氏距离：就像用"身高+信用分"混算地理距离一样荒谬，答案要求明确声明 **`Do not use q_i as a coordinate`**。
- 开放设计题只空泛地背概念（只解释均值与 medoid），不写出抽样 $\to$ 内点判定 $\to$ 加权打分 $\to$ 在最佳内点集重算的完整流程。

**⑥ 对照最终版**

- `"\delta compares the mean (sensitive to outliers) with the medoid (the most central real point); a large \delta means skew or outliers."` → 先解释清楚 $\delta$ 的含义（对比敏感均值与稳健真实中心，过大反映偏斜/离群点）。
- `"RANSAC: sample points with probability \propto q_i, compute a candidate center, inliers = points within \tau, score = \sum_{i\in I}q_i."` → 精准写出加权 RANSAC 的每一步（按 $q_i$ 抽样、距离 $\le\tau$ 定内点、用内点 $q_i$ 之和打分）。
- `"On the best inlier set compute \hat\mu, \hat m and \hat\delta=\|\hat\mu-\hat m\|. Do not use q_i as a coordinate."` → 最终估计步骤 + 千万别把 $q_i$ 当坐标的红线提示。

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

我们专业的全称叫高性能计算与仿真（CHPS）。这门课的机器学习（ML）和传统工程里的数值模拟（如流体力学 CFD、结构力学有限元 FEM）及高性能计算（HPC）之间能擦出什么火花？请讲清楚联系，并给出至少两个具体例子。

**② 需要的工具**

- **数值模拟（Numerical simulation）**：用计算机一步步离散求解物理偏微分方程（PDE），精度很高但**极其烧算力**，算一次飞机绕流或地震波可能要超算跑几小时甚至几天。
- **代理模型（Surrogate model / 替身模型）**：既然真仿真太慢，那就先算几百个样本点，练一个快速的机器学习模型记住"物理参数 $\to$ 仿真结果"的规律。之后面对新参数，毫秒级直接猜出结果！
- **降阶模型（Reduced-Order Model, ROM）与 PCA/POD**：一个三维流体模拟一帧就有上百万个网格数字。PCA（在力学里通常叫 **POD，本征正交分解**）能提取出变化最剧烈的少数几个主模式（Modes），把百万维巨兽压缩到几十维空间里计算。
- **优化与不确定性量化（Optimization / UQ）**：设计机翼或评估材料误差影响，往往需要尝试上万组不同参数——真仿真根本算不动，正是代理模型的用武之地。

**③ 一步一步（记住两大核心例子 + 补充扩展）**

1. **例子 1：代理模型（Surrogate models —— 用 ML 给贵得要命的求解器当替身）**：
   - 先有针对性地挑几百组输入参数（材料硬度、来流速度、几何角度等），咬牙用真实数值求解器（CFD / FEM）跑完得到输出结果；
   - 把这些 `(参数, 输出)` 配对当成训练集，训练一个快速回归模型或神经网络；
   - 在留出的验证/测试参数点上检验误差，确保在安全范围精度达标；
   - 此后做形状优化、反问题或蒙特卡洛不确定性量化（UQ）时，只需向代理模型提问，秒级出答案！
2. **例子 2：降阶模型（Reduced-order models —— 用 PCA/POD 压缩庞大模拟场）**：
   - 把真实求解器算出来的许多时刻网格快照（Snapshots，比如每帧 100 万维向量）收集起来；
   - 用 **PCA / POD**（或自编码器）找出几十个最核心的基底模态；
   - 原本 100 万个网格数字现在只需存这几十个模态系数，直接在几十维极小空间里就能做机器学习预测或降阶求解。
3. **其他联系（双向赋能，答出来很加分）**：
   - **ML 辅助 HPC 运维与求解**：自动调优数值求解器参数（如预条件子、网格自适应加密）、监测超算 HPC 节点的日志和传感器做故障预警/异常检测、物理引导学习（PINN，把 PDE 方程塞进损失函数）；
   - **反过来，HPC 赋能 ML**：超算的多 GPU 并行与高效矩阵计算，也正是训练大模型和深度学习的基础设施。

**④ 小例子**

- **算力账（代理模型）**：跑 1 次三维流体仿真要 **10 小时**，做设计优化需要评估 **10,000 次**不同参数，硬跑要 **10 万小时（十几年）**！如果改先花 2000 小时跑 200 个精选参数造出训练集，练一个代理模型，之后评估 10,000 次每次只需要 **几毫秒**！
- **内存账（ROM）**：一个流场快照有 100 万个网格速度值，经 POD 发现前 20 个模态已保留 99.9% 能量，每个快照瞬间瘦身成 **20 个数字**。

**⑤ 常见误区**

- 吹嘘"代理模型完全可以替代数值求解器"：错！代理模型**只在训练采样的参数区间（内插）内靠谱**，一旦问到训练范围之外（外推）的新物理工况就可能胡说八道；而且别忘了先期造数据跑真实模拟的成本也是总代价的一部分。
- 只讲空泛关系（"两者都用数学/超算"），没写出 **Surrogate models** 和 **Reduced-order models (PCA/POD)** 这两个标准核心实例。

**⑥ 对照最终版**

- `"(1) Surrogate models: run some expensive simulations (CFD, finite elements), then train a fast model (regression, neural network) to predict the output for new parameters without running the solver. Useful for optimization and uncertainty studies."` → 例子 1：代理模型的完整工作流及核心用途（优化、不确定性分析）。
- `"(2) Reduced-order models: use PCA / POD or autoencoders to compress huge simulated fields into a few modes, then learn or solve in this small space."` → 例子 2：降阶模型如何压缩场并降维求解。
- `"Also: tuning solvers, detecting anomalies on HPC nodes."` → 补齐 HPC 方向的联系（调优求解器、超算节点异常检测）。

### 9.2 What is the difference between classification data and a classification problem? 分类数据与分类问题有什么区别？ ★★

考过：[2021 Ex1 Q1](../DataML-CHPS-2021-examen_zh.md) · [2023.3 Ex1 Q2](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** [第三课 · 分类数据：例子；这些数据可以支持哪些决策？](../../Lectures/03_LMC_zh.md)——同一份数据可以对应分类、评分两种问题；与 5.2 一起复习。

**最终版答案（背诵版 EN，≤5 行）：**
**Classification data** describes the **data**: pairs $(x_i,y_i)$ where $y_i$ is a **category** (e.g. 0/1).
A **classification problem** describes the **task**: learn a rule $h:\mathcal X\to\{0,1\}$ that gives a class to new points, with a small error rate.
The same data can also be used for **other problems**: **scoring / ranking** ($s(x)$, evaluated by ROC/AUC) or **probability estimation** $P(Y=1\mid x)$.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

"分类数据（Classification data）"和"分类问题（Classification problem）"只差两个字，不就是一回事吗？错！第三课专门考的就是：**数据自带的形式 $\neq$ 你要解决的业务任务**。

**② 需要的工具（食材 vs 菜品）**

- **数据（食材长什么样）**：原始样本长什么格式——如果每条数据都配了一个离散的类别标签（比如 0/1、猫/狗），这就叫**分类数据**。
- **问题 / 任务（想做什么菜）**：模型拿到手后到底要输出什么结果、用什么指标打分：
  - **分类任务（Classification）**：输出干脆的类别 $0$ 或 $1$，看错分率低不低；
  - **评分 / 排序任务（Scoring / Ranking）**：输出一个连续的风险打分 $s(x)$，用来把人排个高低队（见 5.2），用 ROC / AUC 评价（见 3.5、3.6）；
  - **概率估计任务（Probability estimation）**：精确估计后验概率 $P(Y=1\mid x)$，用 Brier score / 对数损失 / 校准度评价（见 3.7）。

**③ 一步一步**

1. **分类数据（Describes the data）**：说的是**输入的数据集本身**长什么样——是一对对样本 $(x_i, y_i)$，其中标签 $y_i$ 只能取有限个离散类别（比如 $\{0, 1\}$）。
2. **分类问题（Describes the task）**：说的是**要学一个什么样的决策规则**——找一个映射 $h:\mathcal X\to\{0,1\}$，能给新来的样本贴上正确的类别标签，让**分类错误率**尽可能小。
3. **关键区分——同一份分类数据能用来解三种不同的问题！**：
   - 拿 $(x_i, y_i)$ 训练硬分类器 $\implies$ 解**分类问题**；
   - 拿 $(x_i, y_i)$ 训练打分器 $s(x)$ 按危险程度排序 $\implies$ 解**评分/排序问题**；
   - 拿 $(x_i, y_i)$ 估计真实发生概率 $P(Y=1\mid x)$ $\implies$ 解**概率估计问题**。
   问题换了，连模型的评价指标和阈值选择策略都要跟着换（见 3.7）。

**④ 小例子**

银行手里只有同一张历史账本（**分类数据**：每个老客户的特征 $x_i$ + 是否违约标签 $y_i\in\{0,1\}$），但三个部门要用它解决三个**不同的问题**：
- **风控审批岗（分类问题）**：新来一个人申请信用卡，直接回答"批（0）还是拒（1）"，考核指标是错判率；
- **放贷排序岗（评分/排序问题）**：本月资金只够借给前 100 个人，不需要绝对概率，只要按分数 $s(x)$ 从稳到险排队挑最稳的前 100 名就行，考核指标是 **ROC/AUC**；
- **利率定价岗（概率估计问题）**：必须知道某人违约的**真实概率**是 $2\%$ 还是 $20\%$ 才能算出不赔钱的利息，考核概率是否校准。

**⑤ 常见误区**

- 以为只要标签 $y\in\{0,1\}$ 就"只能用来做分类"：其实在工业界和第三课中，**打分排序**和**概率估计**同样是从同一份 $(x_i,y_i)$ 分类数据出发的重要问题。
- 忘了分别用一句清晰的定义句界定 "Classification data describes the **data**" 和 "A classification problem describes the **task**"。

**⑥ 对照最终版**

- `"Classification data describes the data: pairs (x_i,y_i) where y_i is a category (e.g. 0/1)."` → 明确界定分类数据指代数据集的形式（带类别标签）。
- `"A classification problem describes the task: learn a rule h:\mathcal X\to\{0,1\} that gives a class to new points, with a small error rate."` → 明确界定分类问题指代任务目标（学分类规则、降错误率）。
- `"The same data can also be used for other problems: scoring / ranking (s(x), evaluated by ROC/AUC) or probability estimation P(Y=1\mid x)."` → 举例说明同一份数据还可以支撑评分排序与概率估计等不同任务。

### 9.3 What is the difference between supervised and unsupervised learning? Give two examples of each. 监督学习与无监督学习有什么区别？各举两个例子。 ★

考过：[2019 Q1](../Exam_2019_zh.md)

**先懂这些：** [第一课 · 数据、任务与学习函数（Types of Machine Learning problems）](../../Lectures/01_intro/01_data_and_learning.md)；[第四课 · 无监督学习与降维](../../Lectures/04_UL_zh.md)。

**最终版答案（背诵版 EN，≤5 行）：**
**Supervised**: each training point $x_i$ has a known **label $y_i$**; we learn to predict $y$ from $x$. Examples: **spam detection** (classification), **predicting energy consumption** (regression).
**Unsupervised**: **no labels**; we look for **structure** in the $x_i$. Examples: **customer segmentation** (clustering), **dimension reduction** with PCA.
Supervised learning is evaluated by prediction error; unsupervised learning is harder to evaluate.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

机器学习最常被劈成两大阵营：**监督学习（Supervised learning）**和**无监督学习（Unsupervised learning）**。它们的根本区别是什么？请各举两个例子。

**② 需要的工具**

- **标签 $y_i$**：每条样本配备的"正确答案"（比如这封邮件是不是垃圾邮件、明天用电量是多少）。
- **监督（有老师）**：训练时每个样本 $x_i$ 都写好了答案 $y_i$，模型对照着标准答案学从 $x\to y$ 的预测本领。
- **无监督（没老师）**：手头只有光秃秃的样本特征 $x_i$，**没有任何答案标签 $y_i$**，模型只能自己观察这堆数据里面藏着什么规律、团块或压缩结构。

**③ 一步一步（对比表 + 例子）**

| 对比维度 | 监督学习（Supervised） | 无监督学习（Unsupervised） |
|---|---|---|
| **训练数据长啥样** | 成对出现 $(x_i, y_i)$，**有明确标签 $y_i$** | 只有 $x_i$，**没有标签** |
| **学习目标** | 学出预测函数 $x \mapsto y$，去猜新数据的 $y$ | 发现 $x$ 内部的**隐藏结构（structure）** |
| **两个经典例子** | ① **垃圾邮件识别**（分类）<br>② **能源/电力消耗预测**（回归） | ① **客户自动分群**（聚类，如 k-means）<br>② **PCA 降维**（压缩数据提取主成分） |
| **好不好怎么评价** | 直接把预测值和真实答案 $y$ 比对算预测误差（清晰好算） | **没有标准答案**，往往靠启发式指标或下游检查，评价更难（见 1.5、7.4） |

**④ 小例子**

同一张超市会员表（记录了年龄、每月消费额、逛店次数等特征 $x_i$）：
- 如果表里最后一列写了"明年有没有续费（是/否）"或"明年消费了多少钱"作为答案 $y_i$，让你预测新客户的情况 $\implies$ **监督学习**（有目标答案可抄）；
- 如果根本没有那一列目标答案，只让你把这 10 万个客户自动归纳成 4 类人群（聚类），或者把 50 列指标压缩成 2 个综合打分图（PCA）$\implies$ **无监督学习**。

**⑤ 常见误区**

- 把"聚类（Clustering）"和"分类（Classification）"混着说：记住**分类是监督学习**（先有人标好猫狗再学着认），**聚类是无监督学习**（没人给标签，自己把长得像的堆一块儿）。
- 忘了顺便答一句**评价难度的区别**：`Supervised learning is evaluated by prediction error; unsupervised learning is harder to evaluate`（因为无监督没有现成的真值对照）。

**⑥ 对照最终版**

- `"Supervised: each training point x_i has a known label y_i; we learn to predict y from x. Examples: spam detection (classification), predicting energy consumption (regression)."` → 监督学习定义 + 一分类一回归两个典型例子。
- `"Unsupervised: no labels; we look for structure in the x_i. Examples: customer segmentation (clustering), dimension reduction with PCA."` → 无监督学习定义 + 一聚类一降维两个典型例子。
- `"Supervised learning is evaluated by prediction error; unsupervised learning is harder to evaluate."` → 评价方式对比。

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

同样是带标签 $(X, Y)$ 的监督学习数据，什么时候叫**分类数据（Classification data）**，什么时候叫**回归型数据（Regression data）**？新手最容易盯着输入特征 $X$ 看，其实看错了地方！

**② 需要的工具**

- **目标变量 $Y$（Target / Output）**：表格里你想预测的那一列答案（$X$ 是已知线索，$Y$ 是最终谜底）。
- **定性 / 离散变量（Qualitative / Discrete）**：取值是有限几个互不连贯的"种类名称"（如 `{0, 1}`、`{猫, 狗, 鸟}`、`{故障A, 故障B, 正常}`），说白了是**贴标签**，不能随便插一个 `0.73` 在中间。
- **定量 / 连续变量（Quantitative / Continuous）**：取值是实数轴上的数字 $Y\in\mathbb R$（如房价 352.4 万、明日气温 $23.6^\circ\text{C}$），可以比大小、做加减。

**③ 一步一步**

1. **唯一的判断标准：看目标变量 $Y$ 的类型，不看输入特征 $X$！**
   - **分类数据**：$Y$ 是**定性 / 离散**的有限个类别（例如 `{0, 1}` 或疾病种类）。
   - **回归数据**：$Y$ 是**定量 / 连续**的实数值 $Y\in\mathbb R$（例如价格、温度）。
2. **输入特征 $X$ 决定不了类型**：无论是分类还是回归，输入 $X$ 本身都可以既包含数值（身高、年龄）又包含类别（城市、性别）。
3. **目标 $Y$ 一旦不同，后面整套武器库跟着变**：
   - 分类看 0–1 损失 / 对数损失（交叉熵）、评价用错误率 / $F_1$ / AUC；
   - 回归看平方误差 $(y-\hat y)^2$ / 绝对误差、评价用 RMSE / MAE。

**④ 小例子**

房产中介手里有完全同一批房子信息 $X$（面积 `90㎡`、地段 `市中心`、房龄 `5年`——有数字也有文字类别）：
- 如果要预测的 $Y$ 是 **"半年内能不能卖掉（能 / 不能）"** $\implies$ **分类数据**（$Y\in\{0,1\}$）；
- 如果要预测的 $Y$ 是 **"最终成交价是多少万元（实数）"** $\implies$ **回归数据**（$Y\in\mathbb R$）。
输入线索 $X$ 一模一样，全凭预测目标 $Y$ 决定它是分类还是回归！

**⑤ 常见误区**

- 看到输入特征 $X$ 里全是字母类别（比如性别、颜色），就脱口而出"这是分类数据"；或者看到输入全是数字，就以为"这是回归数据"——牢记判断权 100% 在 **target $Y$**！
- 有时分类标签也被编码成数字 `0, 1, 2`（例如三种机器型号），但它本质依然是**离散类别**（模型绝不能把预测输出当成 `1.5` 号型号），切勿被数字假象骗成回归。

**⑥ 对照最终版**

- `"The difference is the type of the target Y."` → 第一句点出核心：区别在目标变量 $Y$ 的类型。
- `"Classification: Y is qualitative / discrete, a finite set of classes (e.g. \{0,1\}, disease type)."` → 分类数据定义与举例。
- `"Regression: Y is quantitative / continuous, Y\in\mathbb R (e.g. price, temperature)."` → 回归数据定义与举例。
- `"The inputs X can be numerical or categorical in both cases. The losses differ: 0–1 / logistic vs squared error."` → 强调输入 $X$ 均可混杂，以及随之而变的损失函数。

### 9.5 Give two concrete implementation issues in real applications (supervised anomaly detection on an instrumented production line). 实际应用中的两个具体实施问题（以生产线上的监督式异常检测为例）。 ★

考过：[2023.3 Ex1 Q10](../DataML-CHPS-2022-examen_zh.md)

**先懂这些：** ① 真实世界中的完整数据处理流程——[第一课 · 算法家族、正则化与处理流程](../../Lectures/01_intro/02_algorithms_and_pipeline.md)；② 类别不平衡下的评价指标（3.7）；③ [Lab3](../../Exercises/Lab3/Lab3_zh.ipynb) 异常检测部分。

**最终版答案（背诵版 EN，≤5 行）：**
(1) **Data quality and labels**: sensors have different rates, scales, drifts and missing values; real defects are **rare** (strong **class imbalance**) and labels are expensive; a sensor failure must be distinguished from a real anomaly.
(2) **Realistic evaluation and drift**: split by **time** to avoid leakage; false alarms (stopping the line) and missed defects have **different costs**, so choose the threshold accordingly; the machines change over time (**concept drift**), so monitor and retrain.

**解析版（小白也能看懂）：**

**① 这道题在问什么**

作业里拿一个干净整齐的 `.csv` 文件直接调 `fit()` 很简单；可一旦把模型搬进真实工厂（比如在装满传感器的生产线上抓异常故障），**落地实施时到底会撞上哪两个具体棘手的大坑？**

**② 需要的工具**

- **严重类别不平衡（Class imbalance）**：工厂正常运转 99.99% 的时间都是好的，真缺陷凤毛麟角（见 3.7），模型哪怕全猜"正常"准确率也有 99.99%。
- **时间泄漏（Temporal leakage）**：相邻几秒钟的传感器读数几乎长得一模一样，如果像普通数据那样随机打乱切分，等于拿"10点02分的数据预测10点01分"，虚高假成绩毫无用处（见 9.7）。
- **概念漂移（Concept drift）**：机器用久了会磨损老化、换了原材料或季节温度变了，以前代表"正常"的振动幅度，现在可能已经算隐患了。
- **误报 vs 漏报的不对称代价（Asymmetric costs）**：误报一次就得紧急停掉整条昂贵的生产线；漏报一次则可能让残次品流入市场甚至炸坏设备。

**③ 一步一步（紧扣场景，写出两大实打实的工程痛点）**

1. **问题一：传感器数据质量乱 + 故障标签难拿（Data quality and labels）**：
   - **信号对不上、脏数据多**：温度计一分钟报一次、震动仪一毫秒报一次，采样率与量纲全不同，时钟可能还错位，外加零点漂移和掉线缺失值；
   - **极端缺正样本 + 标注巨贵**：真的坏件/事故很少（严重**类别不平衡**），而且必须停机由资深工程师拆检才敢打标签，标注成本极高；
   - **真假异常难分**：必须把"**传感器自己坏掉乱报数**"和"**生产线真出了故障**"区分开（同时不同负载工况下正常基线也不一样）。
2. **问题二：评估必须贴合时间与代价 + 上线后会老化漂移（Realistic evaluation and drift）**：
   - **必须按时间顺序切分验证**：不能随机乱洗划分，要用过去练、未来测，才能杜绝时间泄漏；
   - **不能用默认 0.5 阈值和准确率**：结合误报（无故停线损失）和漏报（放走真缺陷后果）的**不同业务代价**，在 PR/F-beta 或成本曲线上挑决策阈值；
   - **上线不是终点（Concept drift）**：机器磨损、维护或工艺变动都会改变数据分布，必须持续监控告警并定期用新数据重训模型。

**④ 小例子**

某生产线一天产生 100 万条传感器记录，里面其实只有 **50 条真缺陷**（0.005%）：
- 如果按准确率考核，一个啥都不干的傻瓜模型"永远预测正常"就能拿 **99.995%** 满分，却会放跑全部 50 个次品；
- 而就算模型抓到了 45 个真缺陷，但如果同时误报了 500 次导致生产线每天白白停机重检，厂长一样会关掉这个系统！所以必须靠 PR 曲线、按真实停线/返修成本定阈值，并做好传感器断线排查与按时间滚动重训。

**⑤ 常见误区**

- 只背万能套话（如"硬件算力不够""数据量太大不好存"），完全没有结合 **"supervised anomaly detection on an instrumented production line"**（传感器、罕见故障标签、传感器自身故障、停线成本、按时间切分、设备漂移）这些接地气的具体痛点。

**⑥ 对照最终版**

- `"(1) Data quality and labels: sensors have different rates, scales, drifts and missing values; real defects are rare (strong class imbalance) and labels are expensive; a sensor failure must be distinguished from a real anomaly."` → 问题一（紧扣传感器数据脏 + 强不平衡高标注成本 + 区分传感器故障与真实异常）。
- `"(2) Realistic evaluation and drift: split by time to avoid leakage; false alarms (stopping the line) and missed defects have different costs, so choose the threshold accordingly; the machines change over time (concept drift), so monitor and retrain."` → 问题二（紧扣按时间切分防泄漏 + 按代价定阈值 + 概念漂移持续监控重训）。

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

面试或大题让你**从 0 到 1 描述一个真实数据科学项目是怎么落地的**（例如 2020 年真题 B 部分：给你 40 个城市建筑的传感器流水账，怎么搭一套上线能用的"能耗峰值预测"系统）？千万不能只答 "`fit()` + `predict()`"，要讲出完整生命周期！

**② 需要的工具（把 5 步拆成听得懂的人话）**

- **多表关联（Join）**：现实里信息常拆在两张表里（比如一张写"建筑 ID、类型、面积"，另一张写"每 10 分钟电表读数"），得先按建筑 ID 对接起来。
- **特征工程（Feature engineering）**：原始时间戳 `2020-01-15 18:30` 模型看不懂，要拆成"几点钟、周几、是不是节假日"；再加上**滞后消耗（Lagged consumption）**（比如 1 小时前、昨天同一时刻的用电量）和温度等线索。
- **按场所标准化（Normalization per site）**：大工厂一小时用 4000 度电，小图书馆只用 40 度电，不按各自平时水平归一化，小场所的特征就会被完全淹没。
- **什么是傻瓜基线（Naive baseline）**：比如直接猜"1 小时后的电量和现在一样（或等于昨天同一时间）"。如果花了大功夫练的神经网络还没赢过傻瓜基线，说明流程里肯定出问题了！
- **沉淀复用（Capitalize）**：把清洗代码、特征定义和文档记下来做成通用资产，下次换个城市或楼宇直接复用。

**③ 一步一步（5 步闭环，覆盖第一课全流程）**

1. **收集与拼表（Collect and join）**：把场所属性表和传感器读数表按 ID 对接，解析日期格式，顺手把欧洲常见的逗号小数（如 `"-2,5"`）修成数字 `-2.5`。
2. **清洗与造特征（Clean and build features）**：修补缺失值和传感器掉零故障；**按每个场所各自做标准化**；构造日历特征（几点、周几）、滞后耗电量（如 $t-1, t-24\text{h}$）以及天气温度特征（天太冷取暖、天太热空调，耗电呈 U 形）。
3. **给预测目标下操作性定义（Define the target）**：客户只说"预测峰值"，算法听不懂！必须转成数学题——例如"未来 $t+h$ 时刻的耗电是否冲破该场所历史 **95% 分位数**"（这就变成**分类**题），或者直接预测 $t+h$ 时刻的具体耗电量数值（变成**回归**题）。
4. **按时间切分训练、调参并对照基线验收（Train, tune, evaluate）**：从简单的逻辑回归练到随机森林、Boosting；**必须严格按时间顺序切分训练/验证/测试集**（不能随机乱抽，见 9.7）；最后在后面的未来时间段上，和**傻瓜基线（Naive baseline）**正面 PK，确认真的大幅胜出。
5. **上线监控、重训与经验沉淀（Deploy, monitor, retrain, capitalize）**：部署上线后持续监控数据漂移，效果下滑时定期重训；最后写清楚文档，沉淀可复用的数据与模型流水线。

**④ 小例子**

系统里同时接入了一座**化工厂**（每 10 分钟耗电约 4000 单位）和一家**小旅馆**（每 10 分钟耗电约 40 单位）：
- 不做第 2 步的"按场所标准化"，模型为了少犯错只会死盯着 4000 的化工厂波动，对小旅馆飙到 100（平时 2.5 倍的大峰值！）视而不见；
- 按各场所历史分布标准化，再配上"周几+滞后用电+温度"特征、以各自 95% 分位数定义峰值，模型就能同时精准抓住两家的异常高峰；并靠与"直接抄昨天同时刻电量"这个傻瓜基线对比来验真效果。

**⑤ 常见误区**

- 一上来直接建模，漏了第 3 步 **"定义目标"**（没有给"峰值"下量化定义就无从标标签、也分不清分类还是回归）。
- 忘了提 **按时间切分**、**对比傻瓜基线**，以及上线后的 **监控重训 + 经验沉淀（capitalize）**——这几词往往就是阅卷点。

**⑥ 对照最终版**

- `"(1) Collect and join the data (sites + measures), parse dates and numbers."` → 第 1 步：数据收集、关联与格式解析。
- `"(2) Clean and build features: missing values, sensor errors, normalization per site, calendar features (hour, day), lagged consumption, temperature."` → 第 2 步：清洗、按场所归一化与四类典型时序特征。
- `"(3) Define the target: e.g. 'peak' = consumption above the site's 95% quantile at t+h (classification) or the consumption itself (regression)."` → 第 3 步：可操作的分类/回归目标定义。
- `"(4) Train and tune models (logistic regression, random forest, boosting) with a time-ordered split, and evaluate on later data against a naive baseline."` → 第 4 步：多模型对比、按时间切分、与基线模型对比评估。
- `"(5) Deploy and monitor (drift), retrain, and capitalize (document, reuse data and models)."` → 第 5 步：上线监控漂移、重训与文档复用沉淀（完整呼应课件工程流程）。

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

普通表格里的样本互相独立（张三的数据和李四的数据打乱顺序不影响什么），但**时间序列数据**（比如每 10 分钟抄一次电表）带着**"时间先后"**这根轴。正因为多了时间维度，建预测模型、画分验证集和上线部署时有哪些必须特别小心的坑？

**② 需要的工具**

- **未来信息泄漏（Leakage from the future）**：你在预测 10:00 的时候，模型特征或切分方式里悄悄混进了 10:10 之后才知道的信息（等于考试偷看标准答案）。
- **滚动 / 扩展窗口划分（Rolling / Expanding window split）**：老老实实只用"过去"训练、用"紧随其后的未来"验证（例如 1–5 月练 $\to$ 6 月测；再推进到 1–6 月练 $\to$ 7 月测），绝不能把时间顺序打乱！
- **自相关（Autocorrelation）**：10:00 和 10:10 只隔十分钟，大楼里的空调、灯全没怎么动，数值几乎一模一样。它们**不是**相互独立的样本。
- **季节性（Seasonality）**：人类作息和天气带来的固定规律循环（一天早晚、一周工作/周末、一年冬夏、节假日）。
- **漂移（Drift）**：时间长了，大楼入驻率变了、设备老化了，过去的规律慢慢失效。

**③ 一步一步（围绕 4 个核心注意项 + 评估收尾）**

1. **第一大忌：绝对不能偷看未来信息（No leakage from the future）**
   - **切分按时间**：只能用**滚动/扩展时间窗口**，严禁 `train_test_split(..., shuffle=True)`；
   - **预处理和阈值也只能看过去**：比如计算某建筑的标准化均值方差、界定"峰值"的 95% 分位数，通通只能在**历史训练窗**里算；
   - **真实上线时的隐蔽泄漏**：如果你想拿"未来 1 小时温度"作特征，做历史回测时千万别直接把当时气象站**事后实测**的真温度喂给模型——真正部署上线时你手里只有**天气预报**（带误差的预报值），测试也要模拟用预报值才公平！
2. **第二要点：抓住多重季节性（Seasonality）**
   - 要通过特征工程或模型考虑日周期（早晚高峰）、周周期（工作日 vs 周末）、年周期（冬夏取暖制冷），以及节假日和夏令时跳变。
3. **第三要点：认清自相关，别被随机交叉验证骗了（Autocorrelation）**
   - 每 10 分钟的数据彼此高度相似（强自相关），远不是独立样本。如果用普通的随机 k-折交叉验证，测试点紧挨着训练点前后夹击，得分会**虚假地偏高（too optimistic）**。
4. **第四要点：持续对抗漂移 + 用对评估方案（Drift & Evaluation）**
   - 上线后分布和规律会慢慢漂移，必须监控性能并定期**重训（retrain）**；
   - **评价指标与基线**：稀少的峰值用**精确率 / 召回率 / $F_1$**（别被准确率骗）；预测具体耗电量用 **RMSE**；而且一定要和最朴素的**基线模型（比如"猜明天此时等于昨天此时"）**比一比，看看复杂模型是不是真的学到了东西。

**④ 小例子**

假设电表每 10 分钟记一次数：
- **作弊式随机打乱划分**：训练集分到了 `10:00` 和 `10:20` 的耗电量，测试集考你 `10:10` 是多少。由于自相关，模型根本不用懂天气和规律，光看左右邻居就稳稳猜出中间值，验证成绩 99 分！一上线要它真去预测"明天 10:10"，前后都没有邻居可抄，瞬间崩盘！
- **正确的按时间划分**：用 `1–10 月` 训练并统计均值和 95% 分位阈值，只在 `11 月` 上按滚动窗口测试，再用 $F_1$ 或 RMSE 对比"昨天同一小时"基线，这才是最真实的成绩。

**⑤ 常见误区**

- 对时间序列直接做随机 k-折交叉验证（最致命错误，必然造成信息泄漏与分数虚高）。
- 回测时误用了未来实测天气、未来全年的标准化均值/分位数（隐蔽的数据泄漏）。
- 忘了写明怎么**评估**（针对罕见峰值用 P/R/$F_1$，针对连续值用 RMSE，且要与 `naive baseline` 比较）。

**⑥ 对照最终版**

- `"(1) No leakage from the future: split by time (rolling / expanding window), and compute features, scaling and thresholds on the past only; in production, future temperature is a forecast."` → 严防未来泄漏的三大要求（时间窗口切分、特征/缩放/阈值只用过去、上线温度用预报）。
- `"(2) Seasonality: daily, weekly and yearly cycles, holidays."` → 多重季节性周期与节假日。
- `"(3) Autocorrelation: points 10 minutes apart are not independent, so random CV is too optimistic."` → 自相关导致样本不独立，随机 CV 过于乐观。
- `"(4) Drift: monitor and retrain. Evaluate with precision / recall / F1 for the rare peaks (RMSE for consumption), against a naive baseline (same hour yesterday)."` → 监控漂移重训 + 按任务选对指标并对标昨天同一时刻朴素基线。

