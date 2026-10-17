# 3. 稀疏性与模型选择

[本课目录](../02_LM_zh.md) · [上一篇：泛化与高维问题](02_generalization_and_high_dimensions.md) · [下一篇：Lasso 与结构化稀疏性](04_lasso_and_structured_sparsity.md)

<a id="section-13"></a>

## A. Sparsity and linear models Tuning the dimension of the model

**A. 稀疏性与线性模型：调整模型维度**


- Vector notations:

  向量记号：

Response vector $\mathbf { Y } \in \mathbb { R } ^ { n }$ , input data matrix $\textsf { X } ( { \mathsf { s i z e } } \ n \times d )$

响应向量 $\mathbf { Y } \in \mathbb { R } ^ { n }$，输入数据矩阵 $\textsf { X } ( { \mathsf { s i z e } } \ n \times d )$。


- Linear model with vector notations:

  以向量形式表示的线性模型：

$$
\mathbf {Y} = \mathbf {X} \boldsymbol {\beta} ^ {*} + \varepsilon
$$

where ε random noise vector (centered, independent of X)

其中 ε 是均值为零、与 X 独立的随机噪声向量。

<a id="section-14"></a>

## The sparse linear regression model

**稀疏线性回归模型**


- Intuition: what if there are uninformative variables in the model but we do not know which they are?

  直觉：如果模型中的某些变量不提供信息，但我们不知道具体是哪些变量，会怎样？

- Sparsity assumption: Let $\beta ^ { * }$ the true parameter which only a subset of variables (called support)

  稀疏性假设：设真实参数 $\beta ^ { * }$ 仅涉及一部分变量，这个变量子集称为支撑集。

$$
m ^ {*} = \{j: \beta_ {j} ^ {*} \neq 0 \} \subset \{1, \dots , d \}
$$

$\ell _ { 0 }$ norm of any β: $\| \beta \| _ { 0 } = \sum _ { j = 1 } ^ { d } \mathbb { I } \{ \beta _ { i } \neq 0 \}$

任意 β 的 $\ell _ { 0 }$“范数”：$\| \beta \| _ { 0 } = \sum _ { j = 1 } ^ { d } \mathbb { I } \{ \beta _ { i } \neq 0 \}$。

<a id="reading-sparse-support"></a>

### The challenge of sparsity is not knowing which variables to keep

**稀疏性难在“不知道该留下哪些变量”**

For example, $\beta=(2,0,-1,0)^T$ has support $\{1,3\}$, so only the first and third features enter prediction. Here

例如 $\beta=(2,0,-1,0)^T$ 的支撑集为 $\{1,3\}$，只有第一、第三个特征进入预测。此时

$$
\|\beta\|_0=2,\qquad \|\beta\|_1=3,\qquad \|\beta\|_2^2=5.
$$

$\ell_0$ counts nonzero coefficients; the summation index above should consistently be understood as $\sum_{j=1}^d\mathbb I\{\beta_j\neq0\}$. Although commonly called the zero norm, it lacks norm homogeneity: doubling all nonzero coefficients still leaves a count of $2$.

$\ell_0$ 统计非零系数的个数；上方求和中的指标应一致地理解为 $\sum_{j=1}^d\mathbb I\{\beta_j\neq0\}$。它通常被称为“零范数”，但不满足范数的齐次性：把所有非零系数放大两倍，计数仍然是 $2$。

If the 20 useful variables among 100 were known beforehand, their columns could be selected and the smaller model fitted. Sparse learning typically assumes only that relatively few variables matter, while their locations remain unknown. It must therefore address support selection and coefficient estimation together. Even known support does not eliminate finite-sample estimation error.

如果事先知道 100 个变量中哪 20 个有用，就可以取出相应的 20 列，再拟合这个较小的模型。稀疏学习通常只假设有用变量较少，具体位置仍未知，因此需要同时处理“选择支撑集”和“估计系数”两个问题。即使支撑集已知，有限样本下的估计误差仍然存在。

<a id="section-15"></a>

## Two possible formulations Constrained vs. Penalized optimization

**两种表述：约束优化与惩罚优化**


1. Ivanov formulation: take k between $0$ and min $\{ n , d \}$

   Ivanov 表述：在 $0$ 与 min $\{ n , d \}$ 之间选取 k。

$$
\min _ {\beta \in \mathbb {R} ^ {d}} \| \mathbf {Y} - \mathbf {X} \beta \| _ {2} ^ {2} \quad \text{满足} \| \beta \| _ {0} \leq k
$$


2. Tikhonov formulation: take $\lambda > 0$

   Tikhonov 表述：取 $\lambda > 0$。

$$
\min _ {\beta \in \mathbb {R} ^ {d}} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| _ {2} ^ {2} + \lambda \| \beta \| _ {0} \right\}
$$


- Tikhonov looks as a Lagrange formulation of Ivanov

  Tikhonov 表述看起来是 Ivanov 表述的拉格朗日形式。

- But here the two formulations are NOT equivalent due to the lack of smoothness of the $\ell _ { 0 }$ norm

  但由于 $\ell _ { 0 }$ 范数缺乏光滑性，这里的两种表述并不等价。

> **Note:** Attributing nonequivalence solely to nonsmoothness is insufficient. Nonconvexity and discrete support selection are crucial here. Under suitable conditions, nonsmooth convex problems can still relate constrained and penalized formulations.

> **译注：** 原文将不等价归因于“不光滑”，这个归因不充分。这里的关键是非凸性及离散的支撑选择；非光滑的凸问题在适当条件下仍可以建立约束形式与惩罚形式的对应。


- Ivanov with $\ell _ { 0 }$ constraint is known as the Best Subset Selection problem for which there are algorithms based on heuristics (e.g. Forward Stagewise Regression) which work ok up to $k \simeq 3 5$ . Recent advances: check Mixed Integer Optimization (MIO) formulation by Bertsimas et al. (2016).

  带 $\ell _ { 0 }$ 约束的 Ivanov 表述称为最佳子集选择问题。已有基于启发式的算法，例如前向逐步回归，在 $k \simeq 3 5$ 以内效果尚可。近期进展：参见 Bertsimas 等（2016）的混合整数优化（MIO）表述。

- Focus on Tikhonov regularization from now on

  从现在起重点讨论 Tikhonov 正则化。

<a id="reading-budget-and-price"></a>

### One formulation limits the count; the other prices each variable

**一个限制数量，一个给每个变量定价**

The constrained formulation permits at most $k$ variables and fits as well as possible under that limit. The penalized formulation charges $\lambda$ for each nonzero coefficient: adding a variable is worthwhile only if refitting reduces the residual sum of squares by more than $\lambda$.

约束形式规定“最多使用 $k$ 个变量”，然后在这个限制内尽量拟合。惩罚形式则为每个非零系数收取 $\lambda$ 的代价：若增加一个变量、重新拟合后减少的残差平方和超过 $\lambda$，它才值得被加入。

<details>
<summary>Example: varying λ need not recover every optimal model size<br>例子：为什么调整 λ 不一定能得到每一种最优模型大小</summary>

Suppose using $0,1,2$ variables gives best residual sums of squares $10,9,0$, respectively. A limit of at most one variable selects the one-variable model with residual sum of squares $9$.

假设分别使用 $0,1,2$ 个变量时，能达到的最小残差平方和是 $10,9,0$。约束“最多一个变量”会选残差为 $9$ 的单变量模型。

In the penalized formulation, the three objective values are $10$, $9+\lambda$, and $2\lambda$. Making the middle one optimal requires both

惩罚形式中，这三个候选的目标值为 $10$、$9+\lambda$ 和 $2\lambda$。要让中间那个最优，必须同时满足

$$
9+\lambda\leq10\quad\text{和}\quad9+\lambda\leq2\lambda,
$$

That is, $\lambda\leq1$ and $\lambda\geq9$, which cannot hold simultaneously. A model selected by a cardinality limit need not be selectable by any uniform per-variable price. This explicitly illustrates why constrained and penalized formulations can differ in discrete, nonconvex model selection.

也就是 $\lambda\leq1$ 且 $\lambda\geq9$，不可能同时成立。因此，给定数量上限能够选出的模型，未必能通过某个统一的变量价格选出来。这是离散、非凸模型选择中两种表述未必等价的具体表现。

</details>

<a id="section-16"></a>

## Sparsity and linear models Model selection

**稀疏性与线性模型：模型选择**

### Connecting the dots Tikhonov penalty and variance

**建立联系：Tikhonov 惩罚与方差**

Recall:

回顾：


- Tikhonov formulation with $\ell _ { 0 }$ penalty: take $\lambda > 0$

  带 $\ell _ { 0 }$ 惩罚的 Tikhonov 表述：取 $\lambda > 0$。

$$
\min _ {\beta \in \mathbb {R} ^ {d}} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| _ {2} ^ {2} + \lambda \| \beta \| _ {0} \right\}\tag{1}
$$


- Bias-variance decomposition of the error for the LSE ${ \widehat { \beta } } \mathbf { : }$ :

  最小二乘估计 ${ \widehat { \beta } } \mathbf { : }$ 的误差偏差—方差分解：

$$
\frac {1}{n} \mathbb {E} \big (\| \mathbf {X} \beta^ {*} - \mathbf {X} \widehat {\beta_ {\mathbf {n}}} \| ^ {2} \big) \simeq \text{偏差} + \sigma^ {2} \frac {d}{n}\tag{2}
$$

where d is the dimension of the data and $\sigma ^ { 2 }$ is the variance of the Gaussian noise

其中 d 是数据维度，$\sigma ^ { 2 }$ 是高斯噪声的方差。

Questions for now: does the bias-variance decomposition (2) explains (1)? Is the penalty correct?

现在的问题：偏差—方差分解（2）能否解释（1）？这个惩罚项是否正确？

<a id="section-17"></a>

## Model selection in linear models

**线性模型中的模型选择**


- Model: $\mathbf Y=\mathbf X\beta^*+\varepsilon$

  模型：$\mathbf Y=\mathbf X\beta^*+\varepsilon$。

- Consider a model for $\beta ^ { * }$ that is a subset m of indices of $\{ 1 , \ldots , d \}$

  考虑 $\beta ^ { * }$ 的一个模型：它由 $\{ 1 , \ldots , d \}$ 的索引子集 m 给出。

- Example: In dimension $d = 3$ , we have:

  例子：在维度 $d = 3$ 下，有：

- 1 model of size $| m | = 0 ;$ : constant model

  1 个大小为 $| m | = 0 ;$ 的模型：常数模型。

- 3 models of size $| m | = 1 ; \{ 1 \} , \{ 2 \} , \{ 3 \}$

  3 个大小为 $| m | = 1 ; \{ 1 \} , \{ 2 \} , \{ 3 \}$ 的模型。

- 3 models of size $| m | = 2 \colon \{ 1 , 2 \} , \{ 2 , 3 \} , \{ 1 , 3 \}$

  3 个大小为 $| m | = 2 \colon \{ 1 , 2 \} , \{ 2 , 3 \} , \{ 1 , 3 \}$ 的模型。

- 1 model of size $| m | = 3 \colon \{ 1 , 2 , 3 \}$

  1 个大小为 $| m | = 3 \colon \{ 1 , 2 , 3 \}$ 的模型。

We potentially have 8 versions of Least Square Estimator (LSE), we call call constrained LSE (except for the case $| m | = 3$ which is unconstrained).

可能有 8 个版本的最小二乘估计，称为约束最小二乘估计（$| m | = 3$ 的情形除外，它没有约束）。

<a id="section-18"></a>

## Model selection in linear models

**线性模型中的模型选择**


- Consider the set $\mathcal { M }$ of subsets m of the variables among indices $\{ 1 , \ldots , d \}$ . There are $2 ^ { d }$ such sets m.

  考虑索引 $\{ 1 , \ldots , d \}$ 中变量子集 m 的集合 $\mathcal { M }$，这样的集合 m 共有 $2 ^ { d }$ 个。

- For every $m \in { \mathcal { M } }$ , there is a standard linear regression model with dimension $| m |$ . In other words, for those $j \notin m _ { \cdot }$ , we have $\theta _ { j } ^ { * } = 0$

  对每个 $m \in { \mathcal { M } }$，有一个维度为 $| m |$ 的标准线性回归模型。换言之，对那些 $j \notin m _ { \cdot }$，有 $\theta _ { j } ^ { * } = 0$。

- Denote by $\mathsf { X } _ { m }$ the submatrix of X of size $n \times | m |$ which contains only the columns whose index belongs to m

  用 $\mathsf { X } _ { m }$ 表示 X 的一个大小为 $n \times | m |$ 的子矩阵，它只包含索引属于 m 的列。

- For each model $m \in { \mathcal { M } }$ , compute the constrained Least Square Estimator $\widehat { \theta } _ { n } ^ { ( m ) } = ( \mathsf { X } _ { m } ^ { T } \mathsf { X } _ { m } ) ^ { - 1 } \mathsf { X } _ { m } ^ { T } \mathsf { Y } \in \mathbb { R } ^ { | m | }$

  对每个模型 $m \in { \mathcal { M } }$，计算约束最小二乘估计 $\widehat { \theta } _ { n } ^ { ( m ) } = ( \mathsf { X } _ { m } ^ { T } \mathsf { X } _ { m } ) ^ { - 1 } \mathsf { X } _ { m } ^ { T } \mathsf { Y } \in \mathbb { R } ^ { | m | }$。

- The final estimator is the ”best” among ${ \widehat { \theta } } _ { n } ^ { ( m ) }$ over all $m \in { \mathcal { M } }$

  最终估计量是在所有 $m \in { \mathcal { M } }$ 上的 ${ \widehat { \theta } } _ { n } ^ { ( m ) }$ 中选出的“最佳”估计量。

- Denote by $\mathsf { X } _ { m }$ the data matrix of size $n \times | m |$

  用 $\mathsf { X } _ { m }$ 表示大小为 $n \times | m |$ 的数据矩阵。

- Risk of the predictor: $r _ { m } = \frac { 1 } { n } \mathbb { E } \big ( \| \mathbf { X } \theta ^ { * } - \mathbf { X } _ { m } \widehat { \theta } _ { n } ^ { ( m ) } \| ^ { 2 } \big )$

  预测器的风险：$r _ { m } = \frac { 1 } { n } \mathbb { E } \big ( \| \mathbf { X } \theta ^ { * } - \mathbf { X } _ { m } \widehat { \theta } _ { n } ^ { ( m ) } \| ^ { 2 } \big )$。

- Best theoretical estimator (called oracle):

  理论上的最佳估计量（称为预言机）：

$$
\widehat {\theta} _ {n} ^ {(\overline {{m}})} \quad \text{其中} \quad \overline {{m}} = \underset {m \in \mathcal {M}} {\arg \min} r _ {m}
$$


- Penalized LS with Akaike Information Criterion (AIC)

  使用赤池信息准则（AIC）的惩罚最小二乘：

$$
\widehat {m} = \underset {m \in \mathcal {M}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} \| ^ {2} + 2 | m | \sigma^ {2} \right\}
$$

(can be computed from data assuming $\sigma ^ { 2 }$ is known)

（假设 $\sigma ^ { 2 }$ 已知，则可由数据计算。）

<a id="reading-aic-example"></a>

### Comparing models through a computable score

**用一个可计算的分数近似比较模型**

An oracle knows true prediction risks and therefore the best submodel. In practice only samples are available, so this answer cannot be used directly. Comparing training residuals alone always favors a larger nested model at least as much as a smaller one, since extra coefficients can be set to zero. Additional degrees of freedom therefore need a cost.

“预言机”知道真实预测风险，因而知道哪个子模型最好；实际拿到的只有样本，无法直接使用这个答案。若只比较训练残差，较大的嵌套模型总能做到不差于较小模型，因为新增系数至少可以取零。于是需要为增加自由度付出代价。

For the Gaussian linear model with known $\sigma^2$ used in the slides, take $\sigma^2=1$ and suppose the candidate models have these residual sums of squares:

以课件中已知 $\sigma^2$ 的高斯线性模型为例，令 $\sigma^2=1$，并假设几个候选模型得到以下残差平方和：

| Model size $\lvert m\rvert$<br>模型大小 $\lvert m\rvert$ | Residual sum of squares<br>残差平方和 | Penalty $2\lvert m\rvert\sigma^2$<br>惩罚 $2\lvert m\rvert\sigma^2$ | Total score<br>总分 |
|---:|---:|---:|---:|
| 0 | 40 | 0 | 40 |
| 1 | 24 | 2 | 26 |
| 2 | 21 | 4 | 25 |
| 3 | 20 | 6 | 26 |

The selected model has size $2$. The third variable only reduces the residual from $21$ to $20$, insufficient to offset penalty increase $2$. Better training fit and selection by a model-selection criterion are thus different outcomes. The derivation below explains the factor $2\sigma^2$.

这里会选择大小为 $2$ 的模型。第三个变量只把残差从 $21$ 降到 $20$，不足以抵消增加的惩罚 $2$。这解释了为什么“训练拟合更好”和“被模型选择准则选中”是两回事。下文推导说明这个系数 $2\sigma^2$ 从哪里来。

Calling $|m|=0$ a constant model usually means retaining an intercept separately, outside variable selection. Without a separate intercept, setting every coefficient to zero gives the zero function. Model comparisons must use a consistent intercept convention.

原例把 $|m|=0$ 称为常数模型，通常是把截距单独保留，不纳入待选变量。如果连截距也不单独设置，所有系数为零对应的就是零函数。比较模型时应始终使用同一种截距约定。

<a id="section-19"></a>

## Optional material Derivation of Akaike Information Criterion

**选读材料：赤池信息准则的推导**

<details>
<summary>Full derivation: from projection error to a model-selection criterion<br>展开完整推导：从投影误差到模型选择准则</summary>

### LSE in linear regression

**线性回归中的最小二乘估计**


- Denote by $\mathsf { X } _ { m }$ the data matrix $( n \times | m | )$ and ${ \widehat { \theta } } _ { n } ^ { ( m ) }$ the LSE

  用 $\mathsf { X } _ { m }$ 表示数据矩阵 $( n \times | m | )$，用 ${ \widehat { \theta } } _ { n } ^ { ( m ) }$ 表示最小二乘估计。

- Prediction vector: $\mathsf { X } _ { m } \widehat { \theta } _ { n } ^ { ( m ) } = \mathsf { X } _ { m } ( \mathsf { X } _ { m } ^ { T } \mathsf { X } _ { m } ) ^ { - 1 } \mathsf { X } _ { m } ^ { T } \mathsf { Y } = \widehat { \Pi } _ { m } \mathsf { Y }$

  预测向量：$\mathsf { X } _ { m } \widehat { \theta } _ { n } ^ { ( m ) } = \mathsf { X } _ { m } ( \mathsf { X } _ { m } ^ { T } \mathsf { X } _ { m } ) ^ { - 1 } \mathsf { X } _ { m } ^ { T } \mathsf { Y } = \widehat { \Pi } _ { m } \mathsf { Y }$。

![image](<../Images/02_LM/image_004.jpg>)

### Bias-variance decomposition (1/2) Derivation

**偏差—方差分解（1/2）：推导**


- Note that $\widehat { \Pi } _ { m } : \mathbb { R } ^ { n }  \mathbb { R } ^ { n }$ is the orthogonal projection onto the space generated by the directions in m:

  注意，$\widehat { \Pi } _ { m } : \mathbb { R } ^ { n }  \mathbb { R } ^ { n }$ 是到 m 中各方向所张成空间的正交投影：

$$
\widehat {\Pi} _ {m} \circ \widehat {\Pi} _ {m} = \widehat {\Pi} _ {m}
$$


- We have: $\mathbf X_m\widehat\theta_n^{(m)}=\widehat\Pi_m\mathbf Y=\widehat\Pi_m(\mathbf X\theta^*+\varepsilon)$ and then

  有 $\mathbf X_m\widehat\theta_n^{(m)}=\widehat\Pi_m\mathbf Y=\widehat\Pi_m(\mathbf X\theta^*+\varepsilon)$，于是

$$
\mathbf {X} \theta^ {*} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} = (I _ {n} - \widehat {\Pi} _ {m}) \mathbf {X} \theta^ {*} - \widehat {\Pi} _ {m} \varepsilon
$$


- Property of the projector: images of $I _ { n } - \widehat { \Pi }$ and $\widehat { \Pi }$ are orthogonal

  投影算子的性质：$I _ { n } - \widehat { \Pi }$ 和 $\widehat { \Pi }$ 的像空间正交。

- Therefore:

  因此：

$$
\begin{array}{r l} {r _ {m}} & {= \frac {1}{n} \mathbb {E} \left(\| (I _ {n} - \widehat {\Pi} _ {m}) \mathbf {X} \theta^ {*} \| ^ {2} + \| \widehat {\Pi} _ {m} \varepsilon \| ^ {2}\right)} \\ & {= \frac {1}{n} \mathbb {E} \left(\| (I _ {n} - \widehat {\Pi} _ {m}) \mathbf {X} \theta^ {*} \| ^ {2}\right) + \sigma^ {2} \frac {| m |}{n}} \end{array}
$$

since $\| \widehat { \Pi } _ { m } \varepsilon \| ^ { 2 }$ follows a chi-square distribution with $| m |$ degrees of freedom (property of projections of multivariate gaussian vectors).

因为 $\| \widehat { \Pi } _ { m } \varepsilon \| ^ { 2 }$ 服从自由度为 $| m |$ 的卡方分布（多元高斯向量投影的性质）。

### Akaike Information Criterion (1/2) Derivation

**赤池信息准则（1/2）：推导**


- Similarly, we can derive:

  类似地，可以推导出：

$$
\frac {1}{n} \mathbb {E} \big (\| \mathbf {Y} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} \| ^ {2} \big) = \frac {1}{n} \mathbb {E} \big (\| (I _ {n} - \widehat {\Pi} _ {m}) \mathbf {X} \theta^ {*} \| ^ {2} \big) + \sigma^ {2} \frac {(n - | m |)}{n}
$$

Indeed: $\begin{array} { r } { \mathsf { \pmb { Y } } - \mathsf { \pmb { X } } _ { m } \widehat { \theta } _ { n } ^ { ( m ) } = \big ( I _ { n } - \widehat { \Pi } _ { m } \big ) ( \mathsf { \pmb { X } } \theta ^ { * } + \varepsilon ) } \end{array}$ and $\| I _ { n } - \widehat { \Pi } _ { m } \varepsilon \| ^ { 2 }$ follows a chi-square distribution with $n - | m |$ degrees of freedom

事实上，$\begin{array} { r } { \mathsf { \pmb { Y } } - \mathsf { \pmb { X } } _ { m } \widehat { \theta } _ { n } ^ { ( m ) } = \big ( I _ { n } - \widehat { \Pi } _ { m } \big ) ( \mathsf { \pmb { X } } \theta ^ { * } + \varepsilon ) } \end{array}$，且 $\| I _ { n } - \widehat { \Pi } _ { m } \varepsilon \| ^ { 2 }$ 服从自由度为 $n - | m |$ 的卡方分布。


- Combining the two identities, prediction error can be related to risk:

  联合这两个恒等式，可将预测误差与风险联系起来：

$$
\frac {1}{n} \mathbb {E} \big (\| \mathbf {Y} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} \| ^ {2} \big) = r _ {m} + \sigma^ {2} \frac {(n - 2 | m |)}{n}
$$

### Akaike Information Criterion (2/2) Empirical estimator of the error

**赤池信息准则（2/2）：误差的经验估计量**


- We have obtained that:

  已经得到：

$$
r _ {m} = \frac {1}{n} \mathbb {E} \big (\| \mathbf {Y} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} \| ^ {2} \big) + \sigma^ {2} \frac {(2 | m | - n)}{n}
$$


- Unbiased estimator of the error (assuming known variance):

  误差的无偏估计量（假设方差已知）：

$$
\widehat {r} _ {m} = \frac {1}{n} \| \mathbf {Y} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} \| ^ {2} + \sigma^ {2} \frac {(2 | m | - n)}{n}
$$


- Akaike Information Criterion

  赤池信息准则：

$$
\widehat {m} = \underset {m \in \mathcal {M}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} _ {m} \widehat {\theta} _ {n} ^ {(m)} \| ^ {2} + 2 | m | \sigma^ {2} \right\}
$$

End of optional material

选读材料结束。

The chi-square variables should be $\|\widehat\Pi_m\varepsilon\|^2/\sigma^2$ and $\|(I_n-\widehat\Pi_m)\varepsilon\|^2/\sigma^2$. The slide omits variance normalization in both and projection parentheses in the second. The corresponding expectations remain $|m|\sigma^2$ and $(n-|m|)\sigma^2$. Starting from the unbiased risk estimate for a fixed model, dropping the constant shared by all candidates and multiplying by $n$ gives the criterion used in the main text: residual sum of squares plus $2|m|\sigma^2$.

这里的卡方变量应写成 $\|\widehat\Pi_m\varepsilon\|^2/\sigma^2$ 和 $\|(I_n-\widehat\Pi_m)\varepsilon\|^2/\sigma^2$；原页分别省略了方差归一化，并在第二处漏写投影括号。相应期望仍是 $|m|\sigma^2$ 与 $(n-|m|)\sigma^2$。上述固定模型的无偏风险估计，去掉对所有候选都相同的常数、再乘以 $n$，便得到正文采用的残差平方和加 $2|m|\sigma^2$ 的选择准则。

</details>

<a id="section-20"></a>

## AIC in large dimensions

**高维情况下的 AIC**


- When d is large, is this practical ?

  当 d 很大时，这样做是否实用？

- There are about $e ^ { d / 2 }$ models to scan in the worst case where $| m | \simeq d / 2 .$

  最坏情况下，需要遍历大约 $e ^ { d / 2 }$ 个模型，其中 $| m | \simeq d / 2 .$。

<a id="reading-subset-complexity"></a>

What grows is the number of variable combinations to compare. There are $2^d$ subsets of $d$ variables, and $\binom dk$ ways to choose exactly $k$. Choosing just 20 of 100 variables already gives approximately $5.36\times10^{20}$ combinations.

真正增长的是需要比较的变量组合数。总共 $d$ 个变量有 $2^d$ 个子集，固定选择 $k$ 个时则有 $\binom dk$ 种。仅从 100 个变量中选 20 个，就约有 $5.36\times10^{20}$ 种组合。

The expression $e^{d/2}$ conveys exponential scale. More precisely, the largest binomial coefficient occurs for $k$ near $d/2$, with order $2^d/\sqrt{\pi d/2}$. Searching more candidates also increases the chance of finding a model that happens to fit noise. A fixed-model degrees-of-freedom penalty does not automatically account for every selection effect of a large search.

上方 $e^{d/2}$ 表达的是指数规模的直觉；更准确地说，最大的二项式系数出现在 $k$ 接近 $d/2$ 的位置，其量级为 $2^d/\sqrt{\pi d/2}$。此外，遍历更多候选也更容易偶然找到迎合噪声的模型，固定模型的自由度惩罚并没有自动解决所有大规模搜索带来的选择偏差。

---

[本课目录](../02_LM_zh.md) · [上一篇：泛化与高维问题](02_generalization_and_high_dimensions.md) · [下一篇：Lasso 与结构化稀疏性](04_lasso_and_structured_sparsity.md)
