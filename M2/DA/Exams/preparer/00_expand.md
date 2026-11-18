# 笔记关键词 → 完整答案 → 中文翻译（74 题）

每题三段：**笔记上写的关键词**、**扩展成的完整英文答案**（考场照这个写）、**中文翻译**。题号顺序和背诵版一致。

## 1. 泛化、误差分解与偏差—方差

### 1.1 What is the bias–variance trade-off? 偏差—方差权衡是什么？ ★★★★

**📝 笔记关键词：** bias²+var+Bayes err；simple→underfit，complex→overfit；CV 选复杂度，test once

**✍️ 完整答案：**

Expected squared error = **bias²** + **variance** + **Bayes error** (noise); for least squares with $d$ parameters, the variance averaged over the training inputs is $\sigma^2 d/n$.
A too **simple** model has high bias: it **underfits**.
A too **complex** model has high variance: it learns the noise and **overfits**.
We choose the complexity (degree, depth, $\lambda$) by **cross-validation**, then test once on a test set.

**🇨🇳 中文翻译：**

期望平方误差 = **偏差²** + **方差** + **贝叶斯误差**（噪声）；对有 $d$ 个参数的最小二乘，在训练输入上平均的方差为 $\sigma^2 d/n$。
模型太**简单**时偏差大：**欠拟合**。
模型太**复杂**时方差大：学到了噪声，**过拟合**。
用**交叉验证**选择复杂度（次数、深度、$\lambda$），最后在测试集上只测一次。

---

### 1.2 What are the approximation and estimation errors, and how is the trade-off between them solved? 近似误差和估计误差是什么？二者的权衡如何处理？ ★★

**📝 笔记关键词：** L(ĥ)−L(h*)=[L(ĥ)−L(h̄)] estim（finite n ~var，data↑→↓）+[L(h̄)−L(h*)] approx（𝓗 too small ~bias）；𝓗↑：approx↓ estim↑；reg/CV

**✍️ 完整答案：**

$L(\hat h)-L(h^*)=\underbrace{L(\hat h)-L(\bar h)}_{\textbf{estimation (stochastic)}}+\underbrace{L(\bar h)-L(h^*)}_{\textbf{approximation (deterministic)}}$, with $\bar h$ the best function in $\mathcal H$.
**Approximation error**: the class $\mathcal H$ is too poor (like bias). **Estimation error**: $\hat h$ is learned from finite data (like variance).
A bigger $\mathcal H$ does not increase the approximation error, but the estimation error **tends to increase**.
Learning = choose $\mathcal H$ (design), then estimate the best function in it (training); balance by **regularization / model selection by CV**, and more data.

**🇨🇳 中文翻译：**

$L(\hat h)-L(h^*)$ = 估计误差（随机的）+ 近似误差（确定的），$\bar h$ 是 $\mathcal H$ 中最好的函数。
**近似误差**：函数类 $\mathcal H$ 太贫乏（类似偏差）。**估计误差**：$\hat h$ 是从有限数据学来的（类似方差）。
$\mathcal H$ 变大不会增加近似误差，但估计误差**往往会增大**。
学习 = 先选 $\mathcal H$（设计），再在其中估计最好的函数（训练）；靠**正则化 / 用 CV 做模型选择**和更多数据来平衡。

---

### 1.3 What is the generalization error and how is it related to overfitting? 什么是泛化误差？它和过拟合有什么关系？ ★

**📝 笔记关键词：** gen err=expected loss on new data E ℓ(h(X),Y)；train err optimistic；overfit=low train，high gen；estimate on test/CV

**✍️ 完整答案：**

The generalization error (true error) is the expected loss on **new data**: $L(h)=\mathbb E[\ell(h(X),Y)]$.
The training error is too optimistic.
**Overfitting**: the training error is very low but the generalization error is high, because the model learned the noise.
We estimate it on a **test set** or by **cross-validation**.

**🇨🇳 中文翻译：**

泛化误差（真实误差）是在**新数据**上的期望损失：$L(h)=\mathbb E[\ell(h(X),Y)]$。
训练误差过于乐观。
**过拟合**：训练误差很低但泛化误差很高，因为模型学到了噪声。
用**测试集**或**交叉验证**来估计它。

---

### 1.4 What is the role of penalization in machine learning? 惩罚项（正则化）在机器学习中起什么作用？ ★

**📝 笔记关键词：** min L̂+λΩ：①控制复杂度 bias↑var↓ ②ill-posed（XᵀX+λI 可逆）③structure（ℓ1 sparsity）；λ CV

**✍️ 完整答案：**

We minimize training error + $\lambda$ penalty: $\hat L_n(\theta)+\lambda\,\Omega(\theta)$. The penalty:
(1) **controls complexity** (Occam's razor): more bias but less variance, so less overfitting ($\lambda$ sets the balance);
(2) **regularizes ill-posed** problems (Tikhonov; Ridge: $X^TX+\lambda I$ is invertible);
(3) adds **structure**, e.g. $\ell_1$ gives **sparsity**. $\lambda$ is a hyperparameter chosen by CV.

**🇨🇳 中文翻译：**

最小化 训练误差 + $\lambda$·惩罚项：$\hat L_n(\theta)+\lambda\,\Omega(\theta)$。惩罚项的作用：
(1) **控制复杂度**（奥卡姆剃刀）：偏差增大、方差减小，过拟合减少（$\lambda$ 决定平衡）；
(2) **正则化病态问题**（Tikhonov；Ridge 中 $X^TX+\lambda I$ 可逆）；
(3) 引入**结构**，例如 $\ell_1$ 带来**稀疏性**。$\lambda$ 是超参数，用 CV 选。

---

### 1.5 Are generalization error and overfitting relevant for clustering? 泛化误差和过拟合的概念适用于聚类吗？ ★

**📝 笔记关键词：** yes：inertia 随 k 不增（k=N→0）→ large k overfits，unstable；stability under resampling，held-out likelihood，BIC

**✍️ 完整答案：**

**Yes.** The optimal inertia never increases when $k$ grows (it is 0 when $k=N$ distinct points).
So a too large $k$ **overfits** the sample and gives unstable clusters.
Without labels, we check generalization by **stability under resampling**, held-out likelihood, or **BIC**.

**🇨🇳 中文翻译：**

**适用。** $k$ 增大时最优惯性不会增加（$k=N$ 个不同点时为 0）。
所以 $k$ 太大会对样本**过拟合**，得到不稳定的簇。
没有标签时，用**重采样下的稳定性**、留出数据上的似然或 **BIC** 检验泛化。

---

### 1.6 What is the impact of computation time (fixed resources) when the sample size grows? 计算资源固定时，样本量增大对计算时间有什么影响？ ★

**📝 笔记关键词：** more data↓estim err but O(n)/pass → fixed time ⇒ accept optim err；SGD/mini-batch/subsample；rough optimum on big data > exact on small

**✍️ 完整答案：**

More data reduces the **estimation error**, but each exact pass over the data costs $O(n)$.
With fixed time, we must accept a larger **optimization error**.
So we use cheap methods: **SGD / mini-batches**, or a subsample.
A rough optimum on much data is often better than an exact optimum on little data.

**🇨🇳 中文翻译：**

更多数据会降低**估计误差**，但每次精确遍历数据要 $O(n)$。
时间固定时，必须接受更大的**优化误差**。
所以用便宜的方法：**SGD / 小批量**，或子采样。
在大量数据上的粗略最优，往往好于在少量数据上的精确最优。

---

## 2. 三大算法家族与 SVM

### 2.1 What is the principle of local methods? Give an example and its hyperparameters. 局部方法的原理是什么？举一个例子并说明超参数。 ★★★

**📝 笔记关键词：** local：x 邻近点 vote/avg，no global optim；kNN；k + distance by CV；small k overfit

**✍️ 完整答案：**

Local methods predict at $x$ with the training points **near $x$**: **majority vote** (classification) or **average** (regression). No global optimization.
Example: **k-nearest neighbors**. Hyperparameters: **$k$** and the **distance**, chosen by cross-validation.
Small $k$: overfitting; large $k$: underfitting. (Decision trees are also local.)

**🇨🇳 中文翻译：**

局部方法用 **$x$ 附近**的训练点在 $x$ 处预测：**多数投票**（分类）或**平均**（回归），不做全局优化。
例子：**k 近邻**。超参数：**$k$** 和**距离**，用交叉验证选。
$k$ 小：过拟合；$k$ 大：欠拟合。（决策树也是局部方法。）

---

### 2.2 What is the principle of global methods? Give an example. 全局方法的原理是什么？举一个例子。 ★★★

**📝 笔记关键词：** global：functional optim，min train err+λ pen on all data；Ridge/Lasso，SVM，boosting，NN

**✍️ 完整答案：**

Global methods are based on **functional optimization**: choose one function $h_\theta$ by **minimizing a criterion on all the data**:
$\min_\theta\frac1n\sum_i\ell(h_\theta(x_i),y_i)+\lambda\Omega(\theta)$ (training error + $\lambda$ penalty). The same parameters are used everywhere.
Examples: **regularized regression (Ridge / Lasso)**, **SVM**, **boosting**, **feedforward neural networks**. Complexity is controlled by the class and by $\lambda$.

**🇨🇳 中文翻译：**

全局方法基于**泛函优化**：通过**在全部数据上最小化一个准则**来选出一个函数 $h_\theta$：
（训练误差 + $\lambda$ 惩罚）。同一组参数在所有地方使用。
例子：**正则化回归（Ridge / Lasso）**、**SVM**、**boosting**、**前馈神经网络**。复杂度由函数类和 $\lambda$ 控制。

---

### 2.3 What are the two main ingredients of ensemble methods? Give an example. 集成方法的两个主要要素是什么？举一个例子。 ★★★

**📝 笔记关键词：** resampling（bootstrap+rand feat / reweight=boosting）+ aggregation（avg/vote）；RF；bag↓var，boost↓bias

**✍️ 完整答案：**

(1) **Resampling**: build many (weak) predictors from the **same data** and the same class $\mathcal H$: **bootstrap** samples (+ random features), or **reweighted** data (**boosting**).
(2) **Aggregation**: **average** (regression) or **majority vote** (classification); boosting uses a weighted vote.
Bagging / random forests mainly reduce **variance**; boosting mainly reduces **bias**.
Example: **random forest** = many unpruned trees + bootstrap + random features.

**🇨🇳 中文翻译：**

(1) **重采样**：从**同一份数据**、同一函数类 $\mathcal H$ 构造许多（弱）预测器：**bootstrap** 样本（+ 随机特征），或**重新加权**的数据（**boosting**）。
(2) **聚合**：**平均**（回归）或**多数投票**（分类）；boosting 用加权投票。
Bagging / 随机森林主要降低**方差**；boosting 主要降低**偏差**。
例子：**随机森林** = 许多不剪枝的树 + bootstrap + 随机特征。

---

### 2.4 What are the two key principles of SVM? SVM 的两个核心原理是什么？ ★★

**📝 笔记关键词：** ① max margin 1/‖w‖，convex QP，support vectors，slack C（hinge）② kernel trick → non-linear

**✍️ 完整答案：**

(1) **Maximum margin**: the separating hyperplane with the largest margin $M=1/\|w\|$ (distance to each class): a **convex quadratic** problem. Only the **support vectors** ($\alpha_i\neq0$) matter.
With slack variables: $\min\frac12\|w\|^2+C\sum_i\xi_i$ s.t. $y_i(w^Tx_i+b)\ge1-\xi_i$, $\xi_i\ge0$ (**hinge loss**).
(2) **Kernel trick**: the dual only uses the Gram matrix $x_i^Tx_j$; replace it by a kernel $k(x_i,x_j)$ (e.g. Gaussian RBF), i.e. map the data to a space where they are (almost) **linearly separable** → **non-linear** boundaries.
Hyperparameters: $C$ and the kernel (chosen on validation data).

**🇨🇳 中文翻译：**

(1) **最大间隔**：选间隔 $M=1/\|w\|$（到每一类的距离）最大的分离超平面：一个**凸二次**问题。只有**支持向量**（$\alpha_i\neq0$）起作用。
加松弛变量后是上面的软间隔问题（**hinge 损失**）。
(2) **核技巧**：对偶问题只用到 Gram 矩阵 $x_i^Tx_j$；把它换成核 $k(x_i,x_j)$（如高斯 RBF），相当于把数据映射到一个（几乎）**线性可分**的空间 → **非线性**边界。
超参数：$C$ 和核（在验证数据上选）。

---

### 2.5 Why are convex losses sometimes used in learning? 为什么学习中有时使用凸损失？ ★

**📝 笔记关键词：** 0–1 loss non-convex，NP-hard → convex surrogate φ≥0–1（hinge，exp）；local=global；sgn(f*)=Bayes；L−L* ≤ ctrl by A−A*

**✍️ 完整答案：**

The **0–1 loss** is not convex and not continuous: minimizing the empirical 0–1 loss is **NP-hard** in general.
We use a **convex surrogate** $\varphi\ge$ 0–1 loss (**hinge** for SVM, **exponential** for boosting), so $L(f)\le A(f)=\mathbb E\,\varphi(-Yf(X))$; with a linear model (or a linear span) the problem is **convex**.
Then every local minimum is **global**, and it is solved efficiently.
Moreover $\text{sgn}(f^*)$ is the **Bayes classifier**, and $L(f)-L^*$ is controlled by $A(f)-A^*$.

**🇨🇳 中文翻译：**

**0–1 损失**不凸也不连续：一般情况下最小化经验 0–1 损失是 **NP 难**的。
用**凸替代损失** $\varphi\ge$ 0–1 损失（SVM 用 **hinge**，boosting 用**指数**），于是 $L(f)\le A(f)$；配合线性模型，问题是**凸**的。
这时每个局部最小都是**全局**最小，可以高效求解。
而且 $\text{sgn}(f^*)$ 就是**贝叶斯分类器**，$L(f)-L^*$ 被 $A(f)-A^*$ 控制。

---

### 2.6 What other choices of loss lead to practical methods? 还有哪些损失选择能得到实用的方法？ ★

**📝 笔记关键词：** change loss：squared（Ridge），hinge（SVM），logistic，exp（boost）；absolute/Huber（robust），ε-insens（SVR），quantile；non-convex+SGD（DL）

**✍️ 完整答案：**

Keep **Criterion = training error + λ penalty** and **change the loss**: **squared** (Ridge), **hinge** (SVM), **logistic** (logistic regression), **exponential** (boosting).
Other choices: **absolute / Huber** (robust to outliers), **ε-insensitive** (SVR), **quantile** loss.
Even **non-convex** losses work with **SGD** (deep learning), but with no global guarantee. The loss should match the real cost of errors.

**🇨🇳 中文翻译：**

保持 **准则 = 训练误差 + λ 惩罚**，**更换损失**：**平方**（Ridge）、**hinge**（SVM）、**logistic**（逻辑回归）、**指数**（boosting）。
其他选择：**绝对值 / Huber**（对离群点稳健）、**ε-不敏感**（SVR）、**分位数**损失。
即使是**非凸**损失，用 **SGD** 也能用（深度学习），但没有全局保证。损失应当符合错误的真实代价。

---

### 2.7 Can SVM be used for regression? SVM 能用于回归吗？ ★

**📝 笔记关键词：** SVR：ε-tube，ε-insensitive loss，min ½‖w‖²+CΣmax(0,|y−f|−ε)；inside tube not SV；kernels

**✍️ 完整答案：**

**Yes: SVR.** We fit $f(x)=w^Tx+b$ with a **tube $f(x)\pm\varepsilon$**: errors smaller than ε cost nothing (**ε-insensitive loss**).
We minimize $\frac12\|w\|^2+C\sum_i\max(0,|y_i-f(x_i)|-\varepsilon)$.
Points strictly inside the tube are **not support vectors** (sparse solution). Kernels give non-linear regression.

**🇨🇳 中文翻译：**

**能：SVR。** 用一个**管道 $f(x)\pm\varepsilon$** 拟合 $f(x)=w^Tx+b$：小于 ε 的误差不计代价（**ε-不敏感损失**）。
最小化上面的目标函数。
严格在管道内的点**不是支持向量**（稀疏解）。用核可以做非线性回归。

---

## 3. 模型评估与超参数校准

### 3.1 Give an example of a hyperparameter and explain how to calibrate it. 举一个超参数的例子并说明如何校准。 ★★★

**📝 笔记关键词：** 例 max depth（train err 不能选）；grid×K-fold CV → min val err → retrain all → test ONCE

**✍️ 完整答案：**

Example: the **maximum depth** of a tree. The training error cannot choose it (a deeper tree never has a higher training error).
**K-fold cross-validation**: for each value in a grid, train on K−1 folds, validate on the held-out fold, rotate over the K folds and average.
Choose the value with the **lowest validation error**, retrain on all training data, and test **once** on the test set.

**🇨🇳 中文翻译：**

例子：树的**最大深度**。训练误差选不了它（树越深，训练误差不会更高）。
**K 折交叉验证**：对网格中的每个取值，在 K−1 折上训练，在留出的一折上验证，K 折轮换后取平均。
选**验证误差最小**的取值，用全部训练数据重新训练，最后在测试集上**只测一次**。

---

### 3.2 What are the stakes and difficulties of hyperparameter calibration? 超参数校准的意义和难点是什么？ ★★

**📝 笔记关键词：** 控制复杂度→under/overfit；不能用 train err；每次重训 costly；noisy；tune on test=optimistic

**✍️ 完整答案：**

Hyperparameters set the **complexity**, so they decide **underfitting vs overfitting**.
Difficulties: we **cannot use the training error**, so we need validation data or CV;
each try needs a **new training** (costly); the score is **noisy**;
tuning on the test set gives an **optimistic** result.

**🇨🇳 中文翻译：**

超参数决定**复杂度**，因此决定**欠拟合还是过拟合**。
难点：**不能用训练误差**，需要验证数据或 CV；
每次尝试都要**重新训练**（代价高）；评分有**噪声**；
在测试集上调参会得到**过于乐观**的结果。

---

### 3.5 Define the ROC curve. 给出 ROC 曲线的定义。 ★★

**📝 笔记关键词：** ROC (0,0)→(1,1)，random=diagonal；all thresholds：compare models，choose t（costs）；rare pos → PR curve

**✍️ 完整答案：**

For a score $s(x)$ and a threshold $t$: $\text{TPR}(t)=P(s(X)\ge t\mid Y=1)$, $\text{FPR}(t)=P(s(X)\ge t\mid Y=0)$.
The **ROC curve** plots TPR against FPR when $t$ varies, from $(0,0)$ to $(1,1)$.
A random score gives the **diagonal**; a perfect score goes through $(0,1)$.

**🇨🇳 中文翻译：**

对打分 $s(x)$ 和阈值 $t$：TPR 和 FPR 如上定义。
**ROC 曲线**是 $t$ 变化时 TPR 对 FPR 的曲线，从 $(0,0)$ 到 $(1,1)$。
随机打分是**对角线**；完美打分经过 $(0,1)$。

---

### 3.6 What is the interest of the ROC curve and the AUC? ROC 曲线和 AUC 有什么用？ ★★

**📝 笔记关键词：** ROC (0,0)→(1,1)，random=diagonal；all thresholds：compare models，choose t（costs）；rare pos → PR curve

**✍️ 完整答案：**

ROC evaluates a score **for all thresholds**.
We use it to **compare** models and to **choose a threshold** (costs, max false alarms).
**AUC** = area under the curve = $P(s(X^+)>s(X^-))+\tfrac12P(s(X^+)=s(X^-))$: 0.5 = random, 1 = perfect ranking.
With rare positives, also use the **precision–recall** curve.

**🇨🇳 中文翻译：**

ROC **在所有阈值下**评估一个打分。
用它来**比较**模型、**选择阈值**（按代价、最大误报数）。
**AUC** = 曲线下面积 = 随机取一正一负，正样本得分更高的概率：0.5 = 随机，1 = 完美排序。
正类很少时，还要看**精确率–召回率**曲线。

---

### 3.3 Can hyperparameter calibration be solved by an optimization technique? 超参数校准能用优化方法解决吗？ ★

**📝 笔记关键词：** bi-level min_λ L̂val(θ̂(λ))；black box（no grad，costly，noisy，non-convex）→ grid（nᵈ）/ random / Bayesian opt

**✍️ 完整答案：**

**Yes**, it is a **bi-level problem**: $\min_\lambda\hat L_{\text{val}}(\hat\theta(\lambda))$.
But the objective is usually a **black box**: no gradient available, **expensive**, **noisy**, often **non-convex**, mixed discrete / continuous variables.
So we use **grid search**, **random search** or **Bayesian optimization**. No guarantee of the global optimum.

**🇨🇳 中文翻译：**

**可以**，这是一个**双层问题**：$\min_\lambda\hat L_{\text{val}}(\hat\theta(\lambda))$。
但目标通常是**黑箱**：没有梯度、**代价高**、**有噪声**、往往**非凸**、离散和连续变量混合。
所以用**网格搜索**、**随机搜索**或**贝叶斯优化**。不保证找到全局最优。

---

### 3.4 Which parameters are chosen by the data scientist and which are learned by the algorithm? 哪些参数由数据科学家选择，哪些由算法学得？ ★

**📝 笔记关键词：** Ridge：learned w,b；chosen：features+scaling，penalty type，λ（CV），protocol；树：split learned，depth chosen

**✍️ 完整答案：**

Example: **Ridge**, $\min\sum_i(y_i-w^Tx_i-b)^2+\lambda\|w\|^2$.
**Learned** by the algorithm: the weights **$w$ and $b$**.
**Chosen** by the data scientist: the features and their scaling, the type of penalty, the value of **$\lambda$** (by CV), the validation protocol.
For a tree: splits are learned, the depth is chosen.

**🇨🇳 中文翻译：**

例子：**Ridge**。
由算法**学习**：权重 **$w$ 和 $b$**。
由数据科学家**选择**：特征及其缩放、惩罚类型、**$\lambda$** 的值（用 CV）、验证方案。
对树来说：切分是学出来的，深度是人选的。

---

### 3.7 Which evaluation criteria can be used for classification data? 分类数据可以用哪些评价准则？ ★

**📝 笔记关键词：** on test：error/accuracy，cost；imbalanced：precision，recall，F1；ranking：ROC/AUC；prob：log-loss

**✍️ 完整答案：**

It depends on the task, always measured on **test data**.
Class decision: **error rate / accuracy**, cost-weighted error; with imbalanced classes: **precision, recall, F1**.
Ranking: **ROC / AUC**, PR curve. Probabilities: **log-loss**, Brier score.

**🇨🇳 中文翻译：**

取决于任务，并且总在**测试数据**上衡量。
类别决策：**错误率 / 准确率**、按代价加权的错误；类别不平衡时：**精确率、召回率、F1**。
排序：**ROC / AUC**、PR 曲线。概率：**log-loss**、Brier 分数。

---

### 3.8 How do you measure classification performance with a train–test split (N = 700 + 300)? 如何用训练／测试划分评估分类性能（700＋300）？ ★

**📝 笔记关键词：** 700/300 imbalanced → stratified 80/20：train 800（560+240），test 200（140+60）；scaling on train；test once：confusion，recall，F1，AUC

**✍️ 完整答案：**

Classes are **imbalanced (70/30)**, so use a **stratified** split, e.g. 80/20:
**train 800 (560 + 240)**, **test 200 (140 + 60)**.
Fit the model (and the scaling) on the train set only.
Evaluate **once** on the test set: **confusion matrix**, recall, F1 or AUC, not only accuracy.

**🇨🇳 中文翻译：**

类别**不平衡（70/30）**，所以用**分层**划分，例如 80/20：
**训练 800（560 + 240）**，**测试 200（140 + 60）**。
只在训练集上拟合模型（和缩放）。
在测试集上**只评估一次**：**混淆矩阵**、召回率、F1 或 AUC，不只看准确率。

---

### 3.9 How do you measure classification performance with k-fold cross-validation? 如何用 k 折交叉验证评估分类性能？ ★

**📝 笔记关键词：** 5 stratified folds of 200（140+60）；train 4 folds（800），test 1；mean ± std；nested CV if tuning

**✍️ 完整答案：**

$k=5$: split into **5 stratified folds of 200 (140 + 60)**.
Each time, train on **4 folds (800)** and test on the remaining fold.
Report the **mean and standard deviation** of the 5 scores; each point is tested exactly once.
If the same CV is used for tuning, use **nested CV**.

**🇨🇳 中文翻译：**

$k=5$：分成 **5 个分层折，每折 200（140 + 60）**。
每次在 **4 折（800）**上训练，在剩下一折上测试。
报告 5 个分数的**均值和标准差**；每个点恰好被测试一次。
如果同一个 CV 还用来调参，就用**嵌套 CV**。

---

## 4. 决策树

### 4.1 What are the hyperparameters of decision trees? 决策树有哪些超参数？ ★★★★

**📝 笔记关键词：** max depth，max leaves，min samples leaf/split，min impurity dec，criterion Gini/entropy/MSE，pruning λ；learned：split var，threshold，leaf value；CV

**✍️ 完整答案：**

**Hyperparameters**: **max depth**, max number of leaves, **min samples per leaf / per split**, min impurity decrease, split **criterion** (Gini, entropy, MSE), **pruning** parameter $\lambda$ (often called α).
**Learned parameters**: split variables, thresholds, leaf values.
Hyperparameters are chosen by **cross-validation**.

**🇨🇳 中文翻译：**

**超参数**：**最大深度**、最大叶子数、**每个叶子 / 每次切分的最少样本数**、最小不纯度下降、切分**准则**（Gini、熵、MSE）、**剪枝**参数 $\lambda$（常记作 α）。
**学到的参数**：切分变量、阈值、叶子值。
超参数用**交叉验证**选。

---

### 4.2 What is a decision tree (representation), e.g. for binary classification? 什么是决策树（表示方式），例如在二分类中？ ★★

**📝 笔记关键词：** recursive partition；node xⱼ≤s；leaf=axis-parallel rectangle → majority class；piecewise const，local

**✍️ 完整答案：**

A tree is a **recursive partition** of the input space.
Each internal node has a test $x_j\le s$; each **leaf** is an **axis-parallel rectangle** with a prediction.
In binary classification, the leaf gives the **majority class** (0 or 1).
It is a **piecewise-constant**, local model.

**🇨🇳 中文翻译：**

树是输入空间的**递归划分**。
每个内部节点有一个测试 $x_j\le s$；每个**叶子**是一个**与坐标轴平行的矩形**，带一个预测值。
二分类中，叶子给出**多数类**（0 或 1）。
它是一个**分段常数**的局部模型。

---

### 4.3 How is a decision tree built / trained (pseudocode)? 决策树如何构建／训练（伪代码）？ ★★

**📝 笔记关键词：** 见笔记「RANSAC · 树」一栏的 Grow(S) 伪代码

**✍️ 完整答案：**

```text
Grow(S):
  if stop (pure, max depth, too few points, no valid split): return Leaf(majority class of S)
  choose (j, s) that maximizes the impurity decrease (Gini / entropy)
  S_L = {x in S : x_j <= s},  S_R = S \ S_L
  return Node(x_j <= s, Grow(S_L), Grow(S_R))
```
Splits are chosen **greedily** (locally optimal). Optionally **prune** with $\hat L_n(T)+\lambda|T|$.

**🇨🇳 中文翻译：**

伪代码：Grow(S)：若满足停止条件（纯、达到最大深度、点太少、没有有效切分）→ 返回叶子（S 的多数类）；否则选使不纯度下降最大的 $(j,s)$（Gini / 熵），按 $x_j\le s$ 把 S 分成左右两部分，返回节点并递归生长左右子树。
切分是**贪心**选择的（局部最优）。可以再用 $\hat L_n(T)+\lambda|T|$ **剪枝**。

---

### 4.4 What label does a decision tree assign to a new point x? 决策树给新点 x 赋什么标签？ ★★

**📝 笔记关键词：** root→leaf by tests；class：majority in leaf（freq=score）；regr：mean y

**✍️ 完整答案：**

Send $x$ down from the root, following the tests, until it reaches a **leaf**.
Classification: the **majority class** of the training points in that leaf (the class frequency can be a score).
Regression: the **mean** of their $y$.

**🇨🇳 中文翻译：**

把 $x$ 从根节点往下送，按各节点的测试走，直到到达一个**叶子**。
分类：该叶子中训练点的**多数类**（类别频率可以当作打分）。
回归：这些点 $y$ 的**均值**。

---

### 4.5 What are the advantages of decision trees over most other algorithms? 与大多数其他算法相比，决策树有哪些优点？ ★★

**📝 笔记关键词：** interpretable if–then，auto var selection，nonlinear+interactions，scale-invariant，missing/categorical，fast；base of RF/boost

**✍️ 完整答案：**

**Easy to interpret**: logical if–then rules (**explainable ML**). **Automatic variable selection**.
Handles **non-linearity and interactions**. **Scale changes** do not matter (invariant to monotone transforms).
Handles **missing and categorical data**, for classification and regression. Fast.
It is the base of **random forests and boosting**.

**🇨🇳 中文翻译：**

**易于解释**：逻辑 if–then 规则（**可解释 ML**）。**自动选择变量**。
能处理**非线性和交互作用**。**尺度变化**没有影响（对单调变换不变）。
能处理**缺失值和类别数据**，可做分类和回归。速度快。
它是**随机森林和 boosting** 的基础。

---

### 4.6 A tree was trained for f. Can it be reused for f₁(5x)=f(x), f₂(x)=5f(x), f₃(x)=f(x)⁵, without retraining? 为 f 训练好的树，能否不重新训练就用于这些变换后的函数？ ★★

**📝 笔记关键词：** no retrain：f(5x)→thresholds×5；5f→leaves×5；f⁵→leaves^5；ensemble f⁵：先 avg 再 ^5

**✍️ 完整答案：**

**No retraining** (if the rescaled inputs stay inside the training range). $f_1(5x)=f(x)$: **multiply the thresholds by 5**.
$f_2=5f$: **multiply the leaf values by 5**.
$f_3=f^5$: raise each **leaf value to the power 5**.
For an **ensemble**: the same for linear changes, but for $f^5$ **average first, then take the power**.

**🇨🇳 中文翻译：**

**不用重新训练**（前提是缩放后的输入还在训练范围内）。$f_1(5x)=f(x)$：**阈值乘以 5**。
$f_2=5f$：**叶子值乘以 5**。
$f_3=f^5$：每个**叶子值取 5 次方**。
对**集成**：线性变换同理，但 $f^5$ 要**先平均，再取 5 次方**。

---

### 4.7 What are the drawbacks of decision trees? 决策树有哪些缺点？ ★

**📝 笔记关键词：** unstable（high var），overfit，greedy，axis-parallel（staircase），no extrapolation，< SOTA

**✍️ 完整答案：**

**Extremely unstable** (high variance). **Overfits** when deep. **Greedy** training.
**Axis-parallel** boundaries only (a staircase for oblique lines).
**Piecewise-constant**: no extrapolation. Accuracy **below state-of-the-art** methods; large trees are **not interpretable**.

**🇨🇳 中文翻译：**

**极不稳定**（方差高）。深了会**过拟合**。**贪心**训练。
只有**与坐标轴平行**的边界（斜线会变成阶梯）。
**分段常数**：不能外推。精度**低于最先进**方法；大树**不可解释**。

---

### 4.8 Is it possible to solve the drawbacks of decision trees? 能否克服决策树的缺点？ ★

**📝 笔记关键词：** partly：depth/min leaf/pruning；var→bagging/RF；bias→boosting；cost：lose interpretability

**✍️ 完整答案：**

**Partly.** Overfitting: limit the depth, min leaf size, **pruning** ($\lambda$ by CV).
Variance: **bagging / random forests**. Bias: **boosting**.
Cost: we **lose interpretability** and need more computation.

**🇨🇳 中文翻译：**

**部分可以。** 过拟合：限制深度、最小叶子大小、**剪枝**（$\lambda$ 用 CV）。
方差：**bagging / 随机森林**。偏差：**boosting**。
代价：**失去可解释性**，需要更多计算。

---

### 4.9 Give at least two stopping rules for training a decision tree. 至少给出两条决策树训练的停止规则。 ★

**📝 笔记关键词：** stop：pure；max depth；too few samples；impurity dec too small；max leaves

**✍️ 完整答案：**

Stop when: (1) the node is **pure**; (2) the **max depth** is reached;
(3) there are too **few samples** to split; (4) no split gives enough **impurity decrease**;
(5) the **max number of leaves** is reached.

**🇨🇳 中文翻译：**

以下情况停止：(1) 节点**纯**；(2) 达到**最大深度**；
(3) **样本太少**，无法切分；(4) 没有切分能带来足够的**不纯度下降**；
(5) 达到**最大叶子数**。

---

### 4.10 Is it possible to monitor the number of cells of the tree using the training data? 能否用训练数据控制树的单元（叶）数量？ ★

**📝 笔记关键词：** yes：max leaves，max depth（≤2ᴰ），min leaf，prune L̂(h_c)+λ|c|；train err can't choose → CV

**✍️ 完整答案：**

**Yes**: set a **max number of leaves**, a max depth ($\le2^D$ leaves) or a min leaf size, or **prune** with the penalized criterion $\hat L_n(h_c)+\lambda|c|$ ($|c|$ = number of cells).
But the **training error alone cannot choose** the number of leaves (more leaves never increase it).
So choose it by **validation / CV**.

**🇨🇳 中文翻译：**

**能**：设**最大叶子数**、最大深度（最多 $2^D$ 个叶子）或最小叶子大小，或用带惩罚的准则 $\hat L_n(h_c)+\lambda|c|$ **剪枝**（$|c|$ = 单元数）。
但**只靠训练误差选不出**叶子数（叶子越多，训练误差不会增加）。
所以用**验证 / CV** 来选。

---

### 4.11 Give a 2D example where the classes are separable but a tree is not efficient. 给出一个二维例子：类别可分，但决策树效率不高。 ★

**📝 笔记关键词：** diagonal x₂=x₁ separable，tree needs staircase of axis-parallel splits → deep，overfit；linear model / feature x₂−x₁

**✍️ 完整答案：**

Two classes separated by the **diagonal** $x_2=x_1$: they are linearly separable.
But a tree only makes **axis-parallel splits**, so it needs a **staircase** of many splits.
The tree becomes deep and **overfits**. A linear model, or the feature $x_2-x_1$, solves it.

**🇨🇳 中文翻译：**

两类被**对角线** $x_2=x_1$ 分开：它们是线性可分的。
但树只能做**与坐标轴平行的切分**，所以需要很多次切分拼成的**阶梯**。
树会变深并**过拟合**。用线性模型，或者加特征 $x_2-x_1$ 就能解决。

---

## 5. 线性模型、OLS 与逻辑回归

### 5.1 Describe the logistic regression model. 描述逻辑回归模型。 ★★★

**📝 笔记关键词：** p=σ(wᵀx+b)，log-odds linear；MLE；discriminative；penalty possible

**✍️ 完整答案：**

For $Y\in\{0,1\}$: $P(Y=1\mid x)=\sigma(w^Tx+b)=\frac1{1+e^{-(w^Tx+b)}}$, i.e. the **log-odds is linear**.
$(w,b)$ are estimated by **maximum likelihood**: minimize the **cross-entropy** (convex; Newton or gradient descent).
A penalty can be added. It is a **discriminative** model.

**🇨🇳 中文翻译：**

对 $Y\in\{0,1\}$：$P(Y=1\mid x)=\sigma(w^Tx+b)$，即**对数几率是线性的**。
$(w,b)$ 用**最大似然**估计：最小化**交叉熵**（凸；牛顿法或梯度下降）。
可以加惩罚项。它是**判别式**模型。

---

### 5.2 What decisions / uses does logistic regression allow (classification, scoring, other problems)? 逻辑回归能支持哪些决策／用途？ ★★★

**📝 笔记关键词：** ① classification p≥t（0.5 / costs）② scoring/ranking（credit）ROC/AUC ③ prob estimation → expert

**✍️ 完整答案：**

It gives a probability $p(x)$, so it allows:
(1) **classification**: $\hat y=1$ if $p(x)\ge t$ ($t=0.5$, or chosen from the costs);
(2) **scoring / ranking**: sort individuals by risk (credit, medicine), evaluated by **ROC / AUC**;
(3) **probability estimation**, e.g. send uncertain cases to an expert.

**🇨🇳 中文翻译：**

它给出概率 $p(x)$，所以可以用于：
(1) **分类**：若 $p(x)\ge t$ 则 $\hat y=1$（$t=0.5$，或按代价选）；
(2) **打分 / 排序**：按风险给个体排序（信贷、医疗），用 **ROC / AUC** 评估；
(3) **概率估计**，例如把不确定的情况交给专家。

---

### 5.3 Explain how Ordinary Least Squares (OLS) fits a line / a linear model. 说明 OLS 如何拟合直线／线性模型。 ★★★

**📝 笔记关键词：** min RSS；∂=0 → β₁，β₀；matrix (full rank)；sensitive to outliers

**✍️ 完整答案：**

Line $\hat y=\beta_0+\beta_1x$. OLS minimizes $\text{RSS}=\sum_i(y_i-\beta_0-\beta_1x_i)^2$.
Setting the derivatives to 0: $\hat\beta_1=\frac{\sum(x_i-\bar x)(y_i-\bar y)}{\sum(x_i-\bar x)^2}$, $\hat\beta_0=\bar y-\hat\beta_1\bar x$.
Matrix form (if $X$ has full column rank): $\hat\beta=(X^TX)^{-1}X^Ty$. Error: $\text{RMSE}=\sqrt{\text{RSS}/N}$.
OLS is **sensitive to outliers**.

**🇨🇳 中文翻译：**

直线 $\hat y=\beta_0+\beta_1x$。OLS 最小化 RSS。
令导数为 0，得到 $\hat\beta_1$ 和 $\hat\beta_0$ 的公式（见上）。
矩阵形式（$X$ 列满秩时）：$\hat\beta=(X^TX)^{-1}X^Ty$。误差：$\text{RMSE}=\sqrt{\text{RSS}/N}$。
OLS **对离群点敏感**。

---

### 5.4 How do you use logistic regression for a classification problem? 如何把逻辑回归用于分类问题？ ★★

**📝 笔记关键词：** fit MLE → p(x) → 1 if p≥t；t=0.5：linear boundary；evaluate on test（confusion，AUC）

**✍️ 完整答案：**

(1) **Fit** $(w,b)$ on the training data by maximum likelihood.
(2) For a new $x$, compute $p(x)=\sigma(w^Tx+b)$.
(3) Predict 1 if $p(x)\ge t$. With $t=0.5$ this is $w^Tx+b\ge0$: a **linear boundary**.
(4) **Evaluate** on test data (confusion matrix, AUC).

**🇨🇳 中文翻译：**

(1) 在训练数据上用最大似然**拟合** $(w,b)$。
(2) 对新的 $x$，计算 $p(x)=\sigma(w^Tx+b)$。
(3) 若 $p(x)\ge t$ 就预测为 1。$t=0.5$ 时等价于 $w^Tx+b\ge0$：**线性边界**。
(4) 在测试数据上**评估**（混淆矩阵、AUC）。

---

### 5.5 Explain the principle of Ridge regression. 解释岭回归的原理。 ★

**📝 笔记关键词：** Ridge ℓ2：总可逆，shrink，bias↑var↓；Lasso ℓ1：β=0 exactly → selection，convex relax ℓ0（NP-hard），LARS/CD/ISTA；λ CV

**✍️ 完整答案：**

Ridge adds an **$\ell_2$ penalty**: $\min_\beta\|y-X\beta\|^2+\lambda\|\beta\|^2$, so $\hat\beta=(X^TX+\lambda I)^{-1}X^Ty$.
$X^TX+\lambda I$ is **always invertible** (even if $d>N$).
The coefficients **shrink towards 0**: more bias, less **variance** (a good $\lambda$ lowers the test error).
$\lambda$ is chosen by CV, on standardized features.

**🇨🇳 中文翻译：**

Ridge 加一个 **$\ell_2$ 惩罚**，解为 $\hat\beta=(X^TX+\lambda I)^{-1}X^Ty$。
$X^TX+\lambda I$ **总是可逆**（即使 $d>N$）。
系数**向 0 收缩**：偏差增大、**方差**减小（合适的 $\lambda$ 能降低测试误差）。
$\lambda$ 用 CV 选，特征要先标准化。

---

### 5.6 How do you estimate a sparse linear model? 如何估计稀疏线性模型？ ★

**📝 笔记关键词：** Ridge ℓ2：总可逆，shrink，bias↑var↓；Lasso ℓ1：β=0 exactly → selection，convex relax ℓ0（NP-hard），LARS/CD/ISTA；λ CV

**✍️ 完整答案：**

Use the **Lasso**: $\min_\beta\|Y-X\beta\|^2+\lambda\|\beta\|_1$.
The **$\ell_1$ penalty** sets many coefficients **exactly to 0**, so it selects variables.
It is the **convex relaxation** of the $\ell_0$ problem (best subset selection, NP-hard).
$\lambda$ by **cross-validation**; solved by **LARS** (whole regularization path), **coordinate descent** or **proximal methods** (ISTA / FISTA, soft thresholding).

**🇨🇳 中文翻译：**

用 **Lasso**：最小化 RSS + $\lambda\|\beta\|_1$。
**$\ell_1$ 惩罚**把许多系数**精确地变成 0**，所以能选择变量。
它是 $\ell_0$ 问题（最优子集选择，NP 难）的**凸松弛**。
$\lambda$ 用**交叉验证**；用 **LARS**（整条正则化路径）、**坐标下降**或**近端方法**（ISTA / FISTA，软阈值）求解。

---

### 5.7 With N = 50 data points and d = 200 features, which regression method would you prefer? How could you still use OLS? N=50、d=200 时选哪种回归方法？如果必须用 OLS 怎么办？ ★

**📝 笔记关键词：** d=200>N=50：XᵀX singular，not unique，overfit → Lasso/Ridge（CV）；OLS after selection/PCA to <50，or X⁺y

**✍️ 完整答案：**

$d=200>N=50$: $X^TX$ is **not invertible**; the OLS solution is **not unique** and unstable, with a high risk of **overfitting**.
I prefer **Lasso** (selects variables) or **Ridge**, with $\lambda$ by CV.
To use OLS anyway: first **reduce the dimension below 50** (variable selection, or **PCA then OLS**), or take the **pseudo-inverse** solution $X^+y$.

**🇨🇳 中文翻译：**

$d=200>N=50$：$X^TX$ **不可逆**；OLS 解**不唯一**且不稳定，**过拟合**风险高。
我更倾向 **Lasso**（能选变量）或 **Ridge**，$\lambda$ 用 CV。
一定要用 OLS 的话：先把**维度降到 50 以下**（变量选择，或**先 PCA 再 OLS**），或者取**伪逆**解 $X^+y$。

---

### 5.8 Which polynomial models would you try on 4 data points, and what is the most complex meaningful one? 4 个数据点上可以尝试哪些多项式模型？最复杂且有意义的是哪个？ ★

**📝 笔记关键词：** polynomial linear in params；4 pts：deg 1,2,3；deg 3（4 params）interpolates，train err 0；higher underdetermined；validation

**✍️ 完整答案：**

Polynomial regression is still **linear in the parameters** (OLS on $1,x,x^2,\dots$).
With 4 points (distinct $x_i$), try degrees **1**, **2** and **3** (at most 4 parameters).
Degree **3** (4 parameters) is the most complex: it **interpolates** the 4 points (zero training error); higher degrees are underdetermined.
In practice, choose a low degree by validation.

**🇨🇳 中文翻译：**

多项式回归对参数仍然是**线性的**（在 $1,x,x^2,\dots$ 上做 OLS）。
4 个点（$x_i$ 互不相同）时，试 **1**、**2**、**3** 次（最多 4 个参数）。
**3** 次（4 个参数）最复杂：它**插值**这 4 个点（训练误差为 0）；更高次是欠定的。
实际中用验证选一个低次数。

---

## 6. 深度学习与数值优化

### 6.1 What optimization strategy is used to train / calibrate deep learning architectures? 深度学习采用什么优化策略？ ★★

**📝 笔记关键词：** mini-batch SGD/Adam；backprop（chain rule）；non-convex；lr，batch，init，early stopping

**✍️ 完整答案：**

We minimize the empirical risk with **mini-batch SGD** (or **Adam**):
$\theta_{t+1}=\theta_t-\eta_t\nabla_\theta\frac1{|B_t|}\sum_{i\in B_t}\ell(f_\theta(x_i),y_i)$.
The gradient is computed by **backpropagation** (chain rule).
The problem is **non-convex**: no global guarantee. Learning rate, batch size, initialization and **early stopping** matter.

**🇨🇳 中文翻译：**

用**小批量 SGD**（或 **Adam**）最小化经验风险（更新公式见上）。
梯度用**反向传播**（链式法则）计算。
问题**非凸**：没有全局保证。学习率、批大小、初始化和**提前停止**都很重要。

---

### 6.2 How is numerical optimization achieved in machine learning methods? Give an example. 机器学习方法如何做数值优化？举一个例子。 ★

**📝 笔记关键词：** closed form（OLS/Ridge），gradient/Newton（logistic），CD/proximal（Lasso），SGD（NN）；ℓ2 logistic convex → global

**✍️ 完整答案：**

Write the objective (loss + penalty), then pick a solver:
**closed form** (OLS, Ridge: QR / SVD), **gradient / Newton** (logistic regression), **coordinate descent / proximal** (Lasso), **SGD** (neural networks).
Example: $\ell_2$-regularized logistic regression, $w_{t+1}=w_t-\eta\nabla L(w_t)$ until the gradient is small; it is strictly **convex**, so with a suitable step size it converges to the **global minimum**.

**🇨🇳 中文翻译：**

写出目标函数（损失 + 惩罚），再选求解器：
**闭式解**（OLS、Ridge：QR / SVD）、**梯度 / 牛顿法**（逻辑回归）、**坐标下降 / 近端方法**（Lasso）、**SGD**（神经网络）。
例子：$\ell_2$ 正则化逻辑回归，$w_{t+1}=w_t-\eta\nabla L(w_t)$，直到梯度很小；它严格**凸**，步长合适时收敛到**全局最小**。

---

### 6.3 What is the mathematical space of functions of deep feedforward neural networks? 深度前馈神经网络对应怎样的函数空间？ ★

**📝 笔记关键词：** 𝓗={A∘σ∘…∘σ∘A}，nonlinear in θ，not vector space，universal approx；hp：depth，width，activation，dropout，weight decay，lr，batch，epochs

**✍️ 完整答案：**

For a fixed architecture: $\mathcal H=\{x\mapsto A_{L+1}\circ\sigma_L\circ A_L\circ\dots\circ\sigma_1\circ A_1(x)\}$, with $A_\ell(u)=W_\ell u+b_\ell$ and $\sigma$ = ReLU, tanh…
It is a **parametric family of compositions**, **non-linear** in $\theta$ and **not a vector space**.
**Universal approximation**: with enough neurons, it can approximate any continuous function on a compact set.

**🇨🇳 中文翻译：**

固定结构时，$\mathcal H$ 是"仿射层 $A_\ell(u)=W_\ell u+b_\ell$ 与激活函数 $\sigma$（ReLU、tanh……）交替复合"得到的函数集合。
它是一个**参数化的复合函数族**，对 $\theta$ **非线性**，**不是向量空间**。
**万能逼近**：神经元足够多时，可以逼近紧集上的任意连续函数。

---

### 6.4 What are the hyperparameters of deep neural networks? 深度神经网络有哪些超参数？ ★

**📝 笔记关键词：** 𝓗={A∘σ∘…∘σ∘A}，nonlinear in θ，not vector space，universal approx；hp：depth，width，activation，dropout，weight decay，lr，batch，epochs

**✍️ 完整答案：**

Weights and biases are **learned**. Hyperparameters:
**architecture** (depth, width, activations, layer types);
**regularization** (weight decay, dropout, early stopping);
**optimization** (optimizer, **learning rate**, **batch size**, epochs, initialization). Tuned on a **validation set**.

**🇨🇳 中文翻译：**

权重和偏置是**学出来的**。超参数：
**结构**（深度、宽度、激活函数、层的类型）；
**正则化**（权重衰减、dropout、提前停止）；
**优化**（优化器、**学习率**、**批大小**、轮数、初始化）。在**验证集**上调。

---

### 6.5 What is the fundamental difference between deep and shallow learning? 深度学习与浅层学习的根本区别是什么？ ★

**📝 笔记关键词：** shallow：hand-made features/kernel + explicit penalty，convex；deep：many layers learn features end-to-end，implicit reg，non-convex，much data

**✍️ 完整答案：**

**Shallow** learning: **hand-made features** (or a fixed kernel) + **explicit (Tikhonov) regularization** $\min\hat L_n(h)+\lambda\,\text{pen}(h)$; the penalty controls the variance; often convex.
**Deep** learning stacks **many non-linear layers** and **learns the features itself**, end to end; it is a **universal approximator** (almost zero bias).
**No penalty term**: non-convex (SGD), **implicit regularization** (weight decay, dropout, early stopping…), needs **much data and computation**.

**🇨🇳 中文翻译：**

**浅层**学习：**人工设计的特征**（或固定的核）+ **显式（Tikhonov）正则化**；惩罚项控制方差；往往是凸的。
**深度**学习堆叠**许多非线性层**，**自己学习特征**，端到端；它是**万能逼近器**（偏差几乎为零）。
**没有惩罚项**：非凸（SGD），**隐式正则化**（权重衰减、dropout、提前停止……），需要**大量数据和计算**。

---

## 7. 聚类（k-means、软 k-means、层次聚类）

### 7.1 Give the k-means objective function and the pseudocode of the algorithm. 给出 k-means 的目标函数和算法伪代码。 ★★★★

**📝 笔记关键词：** 见笔记「C2 k-means」一栏的伪代码和 J

**✍️ 完整答案：**

Objective: $J=\sum_{i=1}^N\|x_i-c_{z_i}\|^2$ (within-cluster sum of squares).
```text
initialize k centers (random data points, or k-means++)
repeat
  assign: z_i = argmin_j ||x_i - c_j||^2
  update: c_j = mean of the points with z_i = j
until the assignments do not change
```

**🇨🇳 中文翻译：**

目标：$J$ = 簇内平方和。
伪代码：初始化 k 个中心（随机数据点，或 k-means++）；重复：**分配**（每个点分给最近的中心）、**更新**（每个中心取它那一簇点的均值）；直到分配不再变化。

---

### 7.2 Why does the k-means procedure converge? k-means 为什么会收敛？ ★★★

**📝 笔记关键词：** assign↓J（z），mean↓J（c）；partitions finite ≤kᴺ → stops finite，local min

**✍️ 完整答案：**

Each step **cannot increase** $J$: the nearest center minimizes $J$ in $z$; the **mean** minimizes $J$ in $c$.
$J$ strictly decreases whenever the partition changes (ties broken consistently), and there are only **finitely many partitions** ($\le k^N$), so no partition repeats.
So it **stops in finite time**, at a **fixed point** (a local minimum in practice), not always the global one.

**🇨🇳 中文翻译：**

每一步都**不会增大** $J$：分给最近中心是在 $z$ 上最小化 $J$；取**均值**是在 $c$ 上最小化 $J$。
只要划分改变，$J$ 就严格下降（平局按一致规则处理），而划分只有**有限多个**（$\le k^N$），所以同一划分不会重复出现。
因此它**在有限步内停止**，停在一个**不动点**（实际上是局部最小），不一定是全局最小。

---

### 7.3 Why are multiple (re)runs suggested? How can k-means approximate the globally optimal solution? 为什么建议多次运行？如何用 k-means 逼近全局最优？ ★★★

**📝 笔记关键词：** non-convex，init-dependent → many runs keep lowest J；k-means++；no guarantee

**✍️ 完整答案：**

$J$ is **non-convex**: the result **depends on the initialization**.
So we run k-means **many times** with random starts and **keep the lowest $J$**.
**k-means++** spreads the initial centers and helps.
This often finds a good (near-global) solution, but with **no guarantee**.

**🇨🇳 中文翻译：**

$J$ **非凸**：结果**依赖初始化**。
所以用随机起点**多次运行** k-means，**保留 $J$ 最小**的那次。
**k-means++** 让初始中心分散开，有帮助。
这样往往能找到好的（接近全局的）解，但**没有保证**。

---

### 7.4 How do you validate the choice of the number of clusters? 如何验证聚类数目的选择？ ★★

**📝 笔记关键词：** J 随 k 不增（k=N→0）→ elbow，silhouette max，BIC，stability

**✍️ 完整答案：**

The optimal $J$ never increases with $k$ (it is 0 when $k=N$), so we cannot just minimize it.
Use the **elbow method**, the **silhouette score** (choose the max), **BIC / AIC** for mixtures,
**stability** under resampling, and domain knowledge.

**🇨🇳 中文翻译：**

最优 $J$ 随 $k$ 增大不会增加（$k=N$ 时为 0），所以不能直接最小化它。
用**肘部法**、**轮廓系数**（取最大）、混合模型的 **BIC / AIC**，
重采样下的**稳定性**，以及领域知识。

---

### 7.5 Propose a soft k-means with probabilistic assignments: definition, pseudocode, convergence. 设计一种概率分配的软 k-means：定义、伪代码、是否收敛。 ★★

**📝 笔记关键词：** E：r_ij；M：weighted mean；F 不增 → converges；= EM GMM，shared spherical cov，τ=2σ²

**✍️ 完整答案：**

Soft assignment with temperature $\tau$: $r_{ij}=\frac{\exp(-\|x_i-c_j\|^2/\tau)}{\sum_l\exp(-\|x_i-c_l\|^2/\tau)}$.
Repeat: **E-step** compute all $r_{ij}$; **M-step** $c_j=\sum_ir_{ij}x_i/\sum_ir_{ij}$.
Both steps do not increase $F=\sum r_{ij}\|x_i-c_j\|^2+\tau\sum r_{ij}\log r_{ij}$, which is bounded below, so the objective **converges** (not necessarily to a global, or even local, minimum).
It is **EM for a GMM** with equal weights and a fixed shared spherical covariance ($\tau=2\sigma^2$).

**🇨🇳 中文翻译：**

带温度 $\tau$ 的软分配 $r_{ij}$（公式见上）。
重复：**E 步**计算所有 $r_{ij}$；**M 步** $c_j$ = 以 $r_{ij}$ 为权重的加权平均。
两步都不会增大 $F$，而 $F$ 有下界，所以目标**收敛**（不一定到全局最小，甚至不一定是局部最小）。
它就是**GMM 的 EM**：权重相等、协方差为固定的共享球形协方差（$\tau=2\sigma^2$）。

---

### 7.6 If k-means is initialized with the soft k-means solution, will the clusters change? Is it a local minimum of hard k-means? 用软 k-means 的解初始化 k-means，簇会变吗？它是硬 k-means 的局部极小吗？ ★★

**📝 笔记关键词：** not necessarily：soft center=weighted mean ≠ hard mean → centers move，pts switch

**✍️ 完整答案：**

**Not necessarily.** Soft centers are **weighted means** (every point counts a bit).
With hard assignments, each cluster mean is different, so k-means **moves the centers** and some points can change cluster.
It stays the same only if each soft center already **equals the mean of its hard cluster** (almost 0/1 weights make this approximately true).

**🇨🇳 中文翻译：**

**不一定。** 软中心是**加权平均**（每个点都占一点权重）。
换成硬分配后，每个簇的均值不一样，所以 k-means 会**移动中心**，有些点可能换簇。
只有当每个软中心已经**等于它那个硬簇的均值**时才不变（权重接近 0/1 时近似成立）。

---

### 7.7 Compare hard and soft k-means. When is soft k-means preferable? 比较硬 k-means 和软 k-means。什么时候软 k-means 更合适？ ★★

**📝 笔记关键词：** hard：simple fast，forced；soft：probabilities，uncertainty，costlier，need τ；用 soft 当 overlap

**✍️ 完整答案：**

**Hard**: one cluster per point, **simple and fast**, but boundary points are forced into one cluster.
**Soft**: gives **membership probabilities** and shows **uncertainty**; a GMM can model elliptical clusters.
But it costs more and needs $\tau$ or a model.
Use soft when clusters **overlap** or when probabilities are needed.

**🇨🇳 中文翻译：**

**硬**：每个点只属于一个簇，**简单快速**，但边界上的点被强行分到一个簇。
**软**：给出**隶属概率**，体现**不确定性**；GMM 能建模椭圆形的簇。
但代价更高，需要 $\tau$ 或一个模型。
簇**互相重叠**或需要概率时，用软的。

---

### 7.8 Summarize the dataset by two "typical" examples (the centers): how well does each center represent its cluster? 用两个"典型"样本（中心）概括数据：每个中心代表其簇的效果如何？ ★★

**📝 笔记关键词：** centers（or medoid）；compact → well（small MSE）；spread/outliers → bad，mean 落在无数据处；fixed center worse

**✍️ 完整答案：**

The two typical examples are the **centers** (means); if a real point is needed, the **medoid**.
A **compact** cluster is well represented (small MSE).
A **spread** cluster, or one with sub-groups or outliers, is badly represented: its mean can lie where there is no data.
A **fixed** center (not the mean) is worse.

**🇨🇳 中文翻译：**

两个典型样本就是**中心**（均值）；如果必须是真实的点，用 **medoid**。
**紧凑**的簇被代表得好（MSE 小）。
**分散**的簇，或者有子群、离群点的簇，被代表得差：均值可能落在没有数据的地方。
**固定**的中心（不是均值）更差。

---

### 7.9 During k-means, how can a cluster become empty? Give heuristics to continue without reducing k. k-means 中簇为什么会变空？给出不减少 k 的处理办法。 ★

**📝 笔记关键词：** empty：no pt closest to center；move to worst pt / split biggest / reseed k-means++

**✍️ 完整答案：**

A cluster is empty when **no point is closest to its center** (bad initialization, or other centers took its points).
Fixes: move the center to the **point with the largest error**, or **split the biggest cluster**, or **re-seed** it (uniformly at random, or by the **k-means++** rule: probability ∝ squared distance to the nearest center).

**🇨🇳 中文翻译：**

当**没有点离某个中心最近**时，这个簇就空了（初始化不好，或者其他中心抢走了它的点）。
办法：把中心移到**误差最大的点**，或**拆分最大的簇**，或**重新播种**（均匀随机，或按 **k-means++** 规则：概率正比于到最近中心距离的平方）。

---

### 7.10 What if the initial clusters are formed by assigning each point uniformly at random? Will it converge, faster or slower? 如果初始化时把每个点等概率随机分到某个簇，会收敛吗？更快还是更慢？ ★

**📝 笔记关键词：** random assign → centers ≈ global mean（LLN）；still converges，slower，maybe worse local opt

**✍️ 完整答案：**

Each random cluster is a sample of the whole data, so all initial centers are **near the global mean** (law of large numbers).
It **still converges** (same argument as 7.2), but it can be **slower**, because the centers must first separate.
It may also end more often in a **bad local optimum** (this depends on the data).

**🇨🇳 中文翻译：**

每个随机簇都是整份数据的一个样本，所以所有初始中心都**靠近全局均值**（大数定律）。
它**仍然收敛**（论证同 7.2），但可能**更慢**，因为中心要先分开。
也可能更常落到**差的局部最优**（取决于数据）。

---

### 7.11 Give three linkage criteria for hierarchical agglomerative clustering, with formulas. 给出层次凝聚聚类的三种连接准则及公式。 ★

**📝 笔记关键词：** 见笔记「C4 回归树 · C5 linkage」一栏的 Linkage

**✍️ 完整答案：**

Start from single points and **merge the two closest clusters** (this gives a dendrogram).
**Single**: $\min_{a,b}\|a-b\|$ (chaining). **Complete**: $\max_{a,b}\|a-b\|$ (compact clusters).
**Average**: $\frac1{|A||B|}\sum_{a,b}\|a-b\|$. **Ward**: merge with the smallest increase of inertia.

**🇨🇳 中文翻译：**

从单个点开始，每次**合并最近的两个簇**（得到树状图）。
**单连接**：最小距离（链式效应）。**全连接**：最大距离（簇更紧凑）。
**平均连接**：所有点对距离的平均。**Ward**：合并后惯性增加最小的两个簇。

---

### 7.12 Use bootstrapped k-means solutions to compute an outlier score; compare with Isolation Forest. 用多次 bootstrap 的 k-means 解计算离群分数，并与 Isolation Forest 比较。 ★

**📝 笔记关键词：** B bootstrap k-means，score=dist to nearest center，avg；not robust；iForest：random splits，isolated fast，no k

**✍️ 完整答案：**

For $b=1..B$: take a **bootstrap sample**, run k-means, and score each point by its **(normalized) distance to the nearest center**. The outlier score is the **mean / median** over the runs.
It is more stable than one run, but k-means is **not robust** and assumes round clusters.
**Isolation Forest** uses random splits: outliers are **isolated quickly**; no centers, no $k$.

**🇨🇳 中文翻译：**

对 $b=1..B$：取一个 **bootstrap 样本**，跑 k-means，用每个点**到最近中心的（归一化）距离**打分。离群分数是多次运行的**均值 / 中位数**。
它比单次运行稳定，但 k-means **不稳健**，而且假设簇是圆的。
**Isolation Forest** 用随机切分：离群点**很快被孤立**；不需要中心，也不需要 $k$。

---

## 8. 稳健估计（RANSAC）与概率图模型

### 8.1 Describe the standard RANSAC method and algorithm for linear regression. 详细描述用于线性回归的标准 RANSAC 方法和算法。 ★★★

**📝 笔记关键词：** 见笔记「RANSAC · 树」一栏的 RANSAC 伪代码和 T 公式

**✍️ 完整答案：**

```text
repeat T times:
  pick 2 random points -> line y = a x + b
  inliers I = { i : |y_i - a x_i - b| <= tau }
  keep the line with the largest I
refit the line by OLS on the best inlier set
```
Choose $T\ge\frac{\log(1-p)}{\log(1-w^2)}$ ($w$ = inlier ratio). It is robust to many **outliers**.

**🇨🇳 中文翻译：**

伪代码：重复 T 次：随机取 2 个点 → 一条直线；内点集 = 残差 ≤ τ 的点；保留内点最多的直线。最后在最好的内点集上用 OLS 重新拟合。
$T$ 按上面的公式选（$w$ = 内点比例）。它对大量**离群点**稳健。

---

### 8.7 Give the graphical model of the battery–sensor–alarm system and write the joint distribution. 给出电池—传感器—报警系统的概率图模型并写出联合分布。 ★★

**📝 笔记关键词：** 见笔记「C3 报警」a)

**✍️ 完整答案：**

Chain **$b\to c\to a$**: $p(a,b,c)=p(b)\,p(c\mid b)\,p(a\mid c)$, so $a\perp b\mid c$.
Data: $P(b=0)=0.1$, $P(c=0\mid b=1)=0.01$, $P(c=0\mid b=0)=0.3$, $P(a=0\mid c=1)=0.99$.
$P(a=0\mid c=0)=q$ is **not given**.

**🇨🇳 中文翻译：**

链 **$b\to c\to a$**：$p(a,b,c)=p(b)\,p(c\mid b)\,p(a\mid c)$，所以 $a\perp b\mid c$。
已知数据如上。
$P(a=0\mid c=0)=q$ **没有给出**。

---

### 8.8 Are a and b independent? (conditional vs marginal independence) a 和 b 独立吗？（条件独立与边际独立） ★★

**📝 笔记关键词：** 见笔记「C3 报警」b)

**✍️ 完整答案：**

Given $c$, **$a$ and $b$ are independent**: both rows of the table $p(a=1\mid b,c)$ are equal ($1-q$ and $0.01$).
But they are **not marginally independent**: $P(a=1\mid b)=\sum_cP(a=1\mid c)P(c\mid b)$ differs for $b=0$ and $b=1$ (except if $q=0.99$).

**🇨🇳 中文翻译：**

给定 $c$ 时，**$a$ 和 $b$ 独立**：表 $p(a=1\mid b,c)$ 的两行相等（$1-q$ 和 $0.01$）。
但它们**边际上不独立**：$P(a=1\mid b)$ 在 $b=0$ 和 $b=1$ 时不同（除非 $q=0.99$）。

---

### 8.9 How do you compute P(battery fails | no alarm) from the model? 如何用模型计算"没听到报警时电池失效"的概率？ ★★

**📝 笔记关键词：** 见笔记「C3 报警」c)–d)

**✍️ 完整答案：**

**Sum out** the unknown variables, then use **Bayes**:
$P(c=0)=0.039$, $P(a=0)=0.95139+0.039q$, $P(a=0,b=0)=0.0693+0.03q$,
so $P(b=0\mid a=0)=\frac{0.0693+0.03q}{0.95139+0.039q}$ (between 0.073 and 0.100).

**🇨🇳 中文翻译：**

先**对未知变量求和**（全概率公式），再用**贝叶斯公式**：
数值见上，
所以 $P(b=0\mid a=0)$ 在 0.073 到 0.100 之间（取决于 $q$）。

---

### 8.2 How sensitive is RANSAC to its parameters? RANSAC 对参数的敏感性如何？ ★

**📝 笔记关键词：** τ：too small rejects good，too large accepts outliers（noise level）；T：more outliers → T↑；random

**✍️ 完整答案：**

**τ**: too small rejects good points; too large accepts outliers. Choose it from the **noise level**.
**T**: too small may miss a clean sample; too large only costs time. $T$ grows fast when there are more outliers.
The results are **random**.

**🇨🇳 中文翻译：**

**τ**：太小会拒绝好点；太大会接受离群点。按**噪声水平**选。
**T**：太小可能抽不到干净的样本；太大只是费时间。离群点越多，$T$ 增长得越快。
结果是**随机的**。

---

### 8.3 What is the difference between RANSAC and a typical bootstrap estimation procedure? RANSAC 与典型的 bootstrap 估计有什么区别？ ★

**📝 笔记关键词：** bootstrap：size N w/ replacement，variance/avg，not robust；RANSAC：minimal sample，best consensus，robust

**✍️ 完整答案：**

**Bootstrap**: samples of **size N with replacement**, to estimate the **variance** of an estimator or to **average** models. Outliers stay inside, so it does **not make a non-robust estimator** (e.g. OLS) robust.
**RANSAC**: **minimal samples** (2 points), and it keeps the **best consensus**, not the average.
Its goal is **robustness** and finding outliers.

**🇨🇳 中文翻译：**

**Bootstrap**：**大小为 N、有放回**的样本，用来估计估计量的**方差**或对模型**取平均**。离群点还在样本里，所以它**不能让不稳健的估计量**（如 OLS）变稳健。
**RANSAC**：**最小样本**（2 个点），保留**最好的一致集**，而不是取平均。
它的目标是**稳健性**和找出离群点。

---

### 8.4 How can the internal RANSAC models "grade" datapoints as outliers, and the datapoints "grade" each model? RANSAC 内部的模型如何给数据点"打分"（是否离群），数据点又如何给模型打分？ ★

**📝 笔记关键词：** models grade pts：r≤τ inlier，rejected by most good models=outlier；pts grade models：#inliers / Σmin(r²,τ²)

**✍️ 完整答案：**

**Models grade points**: each model says inlier ($r\le\tau$) or outlier; a point rejected by most **good** models is an outlier.
**Points grade models**: the score of a model is its **number of inliers** (or a truncated loss $\sum_i\min(r_i^2,\tau^2)$).

**🇨🇳 中文翻译：**

**模型给点打分**：每个模型判断一个点是内点（$r\le\tau$）还是离群点；被大多数**好**模型拒绝的点就是离群点。
**点给模型打分**：模型的得分是它的**内点数**（或截断损失 $\sum_i\min(r_i^2,\tau^2)$）。

---

### 8.5 Develop a generalized RANSAC to fit a circle C(c, r). 用广义 RANSAC 拟合圆 C(c, r)。 ★

**📝 笔记关键词：** 3 pts → circle；residual |‖p−c‖−r|；refit LS；T with w³

**✍️ 完整答案：**

Same algorithm, with three changes:
(1) sample **3 points** (one circle passes through 3 non-collinear points);
(2) residual = **radial distance** $\big|\|p_i-c\|-r\big|$;
(3) refit $(c,r)$ on the inliers by least squares. Use $T\ge\log(1-p)/\log(1-w^3)$.

**🇨🇳 中文翻译：**

算法相同，改三处：
(1) 取 **3 个点**（不共线的 3 个点确定一个圆）；
(2) 残差 = **径向距离** $\big|\|p_i-c\|-r\big|$；
(3) 在内点上用最小二乘重新拟合 $(c,r)$。$T$ 公式中用 $w^3$。

---

### 8.6 Robustly estimate δ = ‖μ − m‖ (mean vs medoid) with RANSAC when each instance has a quality indicator qᵢ. 每个样本带质量指标 qᵢ 时，用 RANSAC 稳健估计 δ = ‖μ − m‖（均值与 medoid 之差）。 ★

**📝 笔记关键词：** δ mean vs medoid（large→outliers）；sample ∝ qᵢ，inliers within τ，score Σqᵢ；δ̂ on best I

**✍️ 完整答案：**

$\delta$ compares the **mean** (sensitive to outliers) with the **medoid** (the most central real point); a large $\delta$ means skew or outliers.
RANSAC: sample points with probability $\propto q_i$, compute a candidate center, inliers = points within τ, score = $\sum_{i\in I}q_i$.
On the best inlier set compute $\hat\mu$, $\hat m$ and $\hat\delta=\|\hat\mu-\hat m\|$. Do not use $q_i$ as a coordinate.

**🇨🇳 中文翻译：**

$\delta$ 比较**均值**（对离群点敏感）和 **medoid**（最中心的真实点）；$\delta$ 大说明有偏斜或离群点。
RANSAC：按正比于 $q_i$ 的概率抽点，算一个候选中心，内点 = τ 以内的点，得分 = $\sum_{i\in I}q_i$。
在最好的内点集上算 $\hat\mu$、$\hat m$ 和 $\hat\delta=\|\hat\mu-\hat m\|$。不要把 $q_i$ 当成一个坐标。

---

## 9. 学习问题的基本概念与实际应用

### 9.1 What are the links between machine learning and numerical simulation / HPC? Give two examples. 机器学习与数值模拟（高性能计算）有哪些联系？举两个例子。 ★★★

**📝 笔记关键词：** surrogate models（simulations → fast predictor，new params）；reduced-order PCA/POD；tune solvers，HPC anomaly

**✍️ 完整答案：**

(1) **Surrogate models**: run some expensive simulations (CFD, finite elements), then train a fast model (regression, neural network) to predict the output for **new parameters** without running the solver. Useful for optimization and uncertainty studies.
(2) **Reduced-order models**: use **PCA / POD** or autoencoders to compress huge simulated fields into a few modes, then learn or solve in this small space.
Also: tuning solvers, detecting anomalies on HPC nodes.

**🇨🇳 中文翻译：**

(1) **代理模型**：先跑一些昂贵的仿真（CFD、有限元），再训练一个快速模型（回归、神经网络），对**新参数**直接预测输出，不用再跑求解器。可用于优化和不确定性研究。
(2) **降阶模型**：用 **PCA / POD** 或自编码器把巨大的仿真场压缩成少数几个模态，然后在这个小空间里学习或求解。
另外：调优求解器、检测 HPC 节点上的异常。

---

### 9.2 What is the difference between classification data and a classification problem? 分类数据与分类问题有什么区别？ ★★

**📝 笔记关键词：** data：pairs (x,y)，y category；problem：learn h:X→{0,1}；same data → scoring/ranking，P(Y=1|x)

**✍️ 完整答案：**

**Classification data** describes the **data**: pairs $(x_i,y_i)$ where $y_i$ is a **category** (e.g. 0/1).
A **classification problem** describes the **task**: learn a rule $h:\mathcal X\to\{0,1\}$ that gives a class to new points, with a small error rate.
The same data can also be used for **other problems**: **scoring / ranking** ($s(x)$, evaluated by ROC/AUC) or **probability estimation** $P(Y=1\mid x)$.

**🇨🇳 中文翻译：**

**分类数据**描述的是**数据**：$(x_i,y_i)$ 对，其中 $y_i$ 是一个**类别**（如 0/1）。
**分类问题**描述的是**任务**：学一个规则 $h:\mathcal X\to\{0,1\}$，给新的点分类，错误率要小。
同样的数据也可以用于**其他问题**：**打分 / 排序**（$s(x)$，用 ROC/AUC 评估）或**概率估计** $P(Y=1\mid x)$。

---

### 9.3 What is the difference between supervised and unsupervised learning? Give two examples of each. 监督学习与无监督学习有什么区别？各举两个例子。 ★

**📝 笔记关键词：** supervised：labels y（spam，energy regression）；unsupervised：no labels，structure（segmentation，PCA）

**✍️ 完整答案：**

**Supervised**: each training point $x_i$ has a known **label $y_i$**; we learn to predict $y$ from $x$. Examples: **spam detection** (classification), **predicting energy consumption** (regression).
**Unsupervised**: **no labels**; we look for **structure** in the $x_i$. Examples: **customer segmentation** (clustering), **dimension reduction** with PCA.
Supervised learning is evaluated by prediction error; unsupervised learning is harder to evaluate.

**🇨🇳 中文翻译：**

**监督**：每个训练点 $x_i$ 有已知的**标签 $y_i$**；学习从 $x$ 预测 $y$。例子：**垃圾邮件检测**（分类）、**预测能耗**（回归）。
**无监督**：**没有标签**；在 $x_i$ 中寻找**结构**。例子：**客户分群**（聚类）、用 PCA **降维**。
监督学习用预测误差评估；无监督学习更难评估。

---

### 9.4 What is the difference between classification data and regression data? 分类型数据与回归型数据有什么区别？ ★

**📝 笔记关键词：** target Y：classification qualitative/discrete；regression quantitative ∈ℝ；loss 0–1/logistic vs squared

**✍️ 完整答案：**

The difference is the **type of the target $Y$**.
**Classification**: $Y$ is **qualitative / discrete**, a finite set of classes (e.g. $\{0,1\}$, disease type).
**Regression**: $Y$ is **quantitative / continuous**, $Y\in\mathbb R$ (e.g. price, temperature).
The inputs $X$ can be numerical or categorical in both cases. The losses differ: 0–1 / logistic vs squared error.

**🇨🇳 中文翻译：**

区别在于**目标 $Y$ 的类型**。
**分类**：$Y$ 是**定性 / 离散**的，取有限个类别（如 $\{0,1\}$、疾病类型）。
**回归**：$Y$ 是**定量 / 连续**的，$Y\in\mathbb R$（如价格、温度）。
两种情况下输入 $X$ 都可以是数值或类别。损失不同：0–1 / logistic vs 平方误差。

---

### 9.5 Give two concrete implementation issues in real applications (supervised anomaly detection on an instrumented production line). 实际应用中的两个具体实施问题（以生产线上的监督式异常检测为例）。 ★

**📝 笔记关键词：** ① data/labels：sensor drift，missing，rare defects（imbalance），costly labels ② eval：split by time，cost FA vs miss，concept drift

**✍️ 完整答案：**

(1) **Data quality and labels**: sensors have different rates, scales, drifts and missing values; real defects are **rare** (strong **class imbalance**) and labels are expensive; a sensor failure must be distinguished from a real anomaly.
(2) **Realistic evaluation and drift**: split by **time** to avoid leakage; false alarms (stopping the line) and missed defects have **different costs**, so choose the threshold accordingly; the machines change over time (**concept drift**), so monitor and retrain.

**🇨🇳 中文翻译：**

(1) **数据质量和标签**：传感器的采样率、尺度、漂移和缺失值各不相同；真实缺陷**很少**（严重的**类别不平衡**），标签代价高；要区分传感器故障和真实异常。
(2) **真实的评估和漂移**：按**时间**划分，避免泄漏；误报（停线）和漏检的**代价不同**，阈值要据此选；机器会随时间变化（**概念漂移**），要监控并重新训练。

---

### 9.6 Describe a data science pipeline to deploy a predictive model (e.g. energy consumption peaks). 描述部署预测模型的数据科学流程（如能耗峰值预测）。 ★

**📝 笔记关键词：** collect/join → clean+features（calendar，lags，temp）→ target（peak>95% quantile）→ train/tune，time split，vs baseline → deploy，monitor drift，retrain

**✍️ 完整答案：**

(1) **Collect and join** the data (sites + measures), parse dates and numbers.
(2) **Clean and build features**: missing values, sensor errors, normalization per site, calendar features (hour, day), lagged consumption, temperature.
(3) **Define the target**: e.g. "peak" = consumption above the site's 95% quantile at $t+h$ (classification) or the consumption itself (regression).
(4) **Train and tune** models (logistic regression, random forest, boosting) with a **time-ordered** split, and **evaluate** on later data against a naive baseline.
(5) **Deploy and monitor** (drift), **retrain**, and **capitalize** (document, reuse data and models).

**🇨🇳 中文翻译：**

(1) **收集并合并**数据（站点 + 测量），解析日期和数字。
(2) **清洗并构造特征**：缺失值、传感器错误、按站点归一化、日历特征（小时、星期几）、滞后的能耗、温度。
(3) **定义目标**：例如"峰值" = $t+h$ 时能耗超过该站点的 95% 分位数（分类），或直接预测能耗（回归）。
(4) 用**按时间顺序**的划分**训练和调参**（逻辑回归、随机森林、boosting），在之后的数据上和朴素基线对比**评估**。
(5) **部署并监控**（漂移）、**重新训练**，并**沉淀经验**（文档、复用数据和模型）。

---

### 9.7 Which points need attention because of the time dimension in the data? 由于数据带有时间维度，需要注意哪些问题？ ★

**📝 笔记关键词：** no future leakage（time split，features on past）；seasonality；autocorrelation（random CV optimistic）；drift；P/R/F1 rare peaks，naive baseline

**✍️ 完整答案：**

(1) **No leakage from the future**: split by time (rolling / expanding window), and compute features, scaling and thresholds on the past only; in production, future temperature is a forecast.
(2) **Seasonality**: daily, weekly and yearly cycles, holidays.
(3) **Autocorrelation**: points 10 minutes apart are not independent, so random CV is too optimistic.
(4) **Drift**: monitor and retrain. **Evaluate** with precision / recall / F1 for the rare peaks (RMSE for consumption), against a naive baseline (same hour yesterday).

**🇨🇳 中文翻译：**

(1) **不能用未来的信息**：按时间划分（滚动 / 扩展窗口），特征、缩放和阈值只用过去的数据计算；生产环境中未来温度只是预报值。
(2) **季节性**：日、周、年周期，节假日。
(3) **自相关**：相隔 10 分钟的点不独立，所以随机 CV 过于乐观。
(4) **漂移**：监控并重新训练。对稀有峰值用精确率 / 召回率 / F1 **评估**（能耗用 RMSE），并和朴素基线（昨天同一小时）比较。

---
