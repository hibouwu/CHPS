# 4. Lasso 与结构化稀疏性

[本课目录](../02_LM_zh.md) · [上一篇：稀疏性与模型选择](03_sparsity_and_model_selection.md) · [下一篇：岭回归与对偶](05_ridge_and_duality.md)

<a id="section-21"></a>

## A. Sparsity and linear models From (mathematical) statistics to optimization

**A. 稀疏性与线性模型：从数理统计到优化**

### Solving the computation burden The power of convexity

**解决计算负担：凸性的力量**

Practical methods for model selection are essentially greedy heuristics consisting in adding and/or retrieving one variable at the time to explore part of the whole model space which is exponential in the dimension. Examples are: Forward Stagewise Regression, Forward-Backward algorithm...

实用的模型选择方法主要是贪心启发式方法，每次增加和／或移除一个变量，以探索整个模型空间的一部分；整个模型空间的规模随维度呈指数增长。例子包括前向逐步回归、前向—后向算法等。


- Question: would it be possible to solve the optimization wrt the unknown parameter $\beta$ AND wrt to its support subset of indices jointly?

  问题：是否能够同时针对未知参数 $\beta$ 及其支撑索引子集进行优化？

- Answer is yes at the cost of the so-called relaxation of the non-convex formulation with the $\ell _ { 0 }$ penalty to a convexified problem with an $\ell _ { 1 }$ penalty.

  答案是肯定的，代价是进行所谓的松弛：把带 $\ell _ { 0 }$ 惩罚的非凸表述替换为带 $\ell _ { 1 }$ 惩罚的凸化问题。



<a id="reading-greedy-and-convexity"></a>

Forward stepwise selection tries adding one variable at a time and refits the current candidates. Following one path saves enumeration cost but can miss combinations whose usefulness appears only when two variables are considered together.

前向逐步选择每次尝试加入一个变量，并对当前候选重新拟合。它沿着一条路径探索，能节省枚举成本，却可能错过必须把两个变量一起考虑才显现出来的组合。

Replacing $\ell_0$ by $\ell_1$ changes the optimization problem itself. Squared residuals and the sum of absolute values are convex in $\beta$, so their sum remains convex. This penalty allows coefficients to vary continuously while still setting some exactly to zero. It is a different computational approach to sparse modeling, not a guarantee of the same answer as exhaustive best-subset selection.

把 $\ell_0$ 换成 $\ell_1$，则改变了优化问题本身：平方残差和绝对值之和都对 $\beta$ 凸，因此整体仍是凸问题。得到的惩罚允许系数连续变化，同时保留把部分系数推到零的能力。它是另一种可计算的稀疏建模办法，并不保证给出与逐个枚举最佳子集完全相同的答案。

<a id="section-22"></a>

<a id="lasso"></a>

## The LASSO for linear models From $\ell _ { 0 }$ to $\ell _ { 1 }$

**线性模型的 LASSO：从 $\ell _ { 0 }$ 到 $\ell _ { 1 }$**


- Consider the relaxation of the previous problem replacing the $\ell _ { 0 } - \mathsf { n o r m }$ by the $\ell _ { 1 } { \mathrm { - } } \mathsf { n o r m }$

  考虑对前述问题作松弛，用 $\ell _ { 1 } { \mathrm { - } } \mathsf { n o r m }$ 替代 $\ell _ { 0 } - \mathsf { n o r m }$。

$$
\| \beta \| _ {1} = \sum_ {j = 1} ^ {d} | \beta_ {j} |
$$


- The new estimator is called the ${ \mathsf { L } } { \mathsf { A } } { \mathsf { S } } { \mathsf { S } } { \mathsf { O } }$ : for any $\lambda > 0$

  新估计量称为 ${ \mathsf { L } } { \mathsf { A } } { \mathsf { S } } { \mathsf { S } } { \mathsf { O } }$：对任意 $\lambda > 0$，

$$
\widehat {\beta} _ {\lambda} \in \underset {\beta \in \mathbb {R} ^ {d}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| ^ {2} + \lambda \| \beta \| _ {1} \right\}
$$


- Approximate solutions via efficient algorithms building the so-called regularization paths $\lambda  \widehat { \beta } _ { \lambda }$

  通过构建所谓正则化路径 $\lambda  \widehat { \beta } _ { \lambda }$ 的高效算法求近似解。

![image](<../Images/02_LM/image_005.jpg>)


- Theoretical soundness: it can be shown that: as $n , d \to \infty$

  理论依据：可以证明，当 $n , d \to \infty$ 时，

$$
\frac {1}{n} \mathbb {E} \big (\| \mathbf {X} \beta^ {*} - \mathbf {X} \widehat {\beta} \| ^ {2} \big) \leq C \| \beta^ {*} \| _ {1} \sqrt {\frac {\log d}{n}}
$$

<a id="reading-lasso-threshold"></a>

### How an absolute-value penalty sets coefficients to zero

**绝对值惩罚怎样把系数压到零**

Reduce the problem to one coefficient, retaining this section's squared-loss convention without $1/2$:

先把问题缩小到一个系数，并沿用本节没有 $1/2$ 的平方损失：

$$
\min_b (z-b)^2+\lambda|b|.
$$

For $b>0$, setting the derivative $2(b-z)+\lambda=0$ gives $b=z-\lambda/2$; for $b<0$, it gives $b=z+\lambda/2$. If the absolute value of $z$ is at most $\lambda/2$, the optimum stays at $b=0$. Together,

当 $b>0$ 时，令导数 $2(b-z)+\lambda=0$，得到 $b=z-\lambda/2$；当 $b<0$ 时，得到 $b=z+\lambda/2$。如果 $z$ 的绝对值不超过 $\lambda/2$，最优值就停在 $b=0$。合起来是

$$
\widehat b_{\mathrm{LASSO}}
=\operatorname{sign}(z)\bigl(|z|-\lambda/2\bigr)_+,
\qquad (u)_+=\max(u,0).
$$

Small signals become exactly zero, and larger ones are shortened toward zero by $\lambda/2$: this is soft thresholding. The absolute-value function's corner at zero lets an entire interval of $z$ map to the same zero solution. The one-dimensional exercise below plots this alongside two other penalties.

较小的信号直接归零，较大的信号也会向零缩短 $\lambda/2$，这叫软阈值。绝对值函数在零点有尖角，使一整段 $z$ 都可以对应同一个零解；下面的一维练习还会把它与另外两种惩罚画在一起比较。

Take $\mathbf X=I_3$, $\mathbf Y=(3,0.4,-2)^T$, and $\lambda=2$. Solving each coordinate separately gives

取 $\mathbf X=I_3$、$\mathbf Y=(3,0.4,-2)^T$、$\lambda=2$，三个坐标可以分别求解，得到

$$
\widehat\beta_{\mathrm{LASSO}}=(2,0,-1)^T.
$$

The second feature is removed and the other two remain, but their coefficient magnitudes also decrease. This coordinatewise formula applies to the orthogonal design here. Generally, correlated features interact and must be optimized jointly.

第二个特征被剔除，另外两个仍保留，但系数绝对值也减小了。这个逐坐标公式适用于这里的正交设计；一般的相关特征会相互影响，需要联合求解。

Geometrically, the two-dimensional $\ell_1$ constraint set is a diamond with corners on the coordinate axes. A loss contour can meet it at such a corner, where one coefficient is zero. Coefficient paths show how coordinates enter or leave the solution as $\lambda$ changes. [LASSO and coefficient paths](https://cs229.stanford.edu/notes2021fall/lecture10-lasso-regression.pdf)

从几何上看，二维 $\ell_1$ 约束集是带尖角的菱形，角点落在坐标轴上，优化时容易在这样的地方接触到损失等高线；坐标落在轴上，就意味着一个系数为零。系数路径则展示了改变 $\lambda$ 时，这些坐标怎样进入或离开解。[LASSO 与系数路径](https://cs229.stanford.edu/notes2021fall/lecture10-lasso-regression.pdf)

<details>
<summary>Derivation: optimality at zero and log d in the theoretical bound<br>推导：零点的最优条件，以及理论界中的 log d</summary>

$|b|$ is not differentiable at zero, but its subgradient there is the interval $[-1,1]$. Zero is optimal when

$|b|$ 在零点不可微，但其子梯度是区间 $[-1,1]$。零点成为最优解的条件是

$$
0\in-2z+\lambda[-1,1],
$$

That is, $|z|\leq\lambda/2$. For column $\mathbf X_j$, indexed by $j$, in general LASSO, the corresponding zero-coefficient condition is

即 $|z|\leq\lambda/2$。一般 LASSO 中，对第 $j$ 列 $\mathbf X_j$，零系数的条件相应为

$$
|2\mathbf X_j^T(\mathbf Y-\mathbf X\widehat\beta)|\leq\lambda.
$$

This compares the feature's correlation with the remaining residual and explains why relationships among features affect which coefficients are selected.

它比较该特征与剩余残差的相关程度，解释了为什么特征之间的关系会改变哪些系数被选中。

The prediction-error bound in the main text expresses dimension dependence through $\sqrt{\log d/n}$. For example, when $d=n^3$, $\log d/n=3\log n/n\to0$, so this factor can vanish even if there are more variables than samples. Making the whole bound small also requires controlling $\|\beta^*\|_1$ and satisfying the relevant design normalization, noise, and $\lambda$ selection conditions. The constant $C$ also reflects model assumptions. Small prediction error and exact recovery of the nonzero-coefficient support are different conclusions.

正文所列预测误差界，把维度依赖写成 $\sqrt{\log d/n}$。例如 $d=n^3$ 时，$\log d/n=3\log n/n\to0$，即使变量数超过样本数，这一因子仍可能趋于零。要让整项误差界变小，还要控制 $\|\beta^*\|_1$，并满足相应设计矩阵归一化、噪声及 $\lambda$ 选择条件；常数 $C$ 也包含模型假设的信息。预测误差小与准确恢复每个非零系数的支撑集，是不同的结论。

</details>

<a id="section-23"></a>

## The ”mother” of ML algorithms Penalized optimization

**机器学习算法之“母”：惩罚优化**


- Learning process as the optimization of a data-dependent criterion:

  将学习过程写成对依赖于数据的准则的优化：

Criterion(h) = Training error(h) + λ Penalty(h)

准则(h) = 训练误差(h) + λ 惩罚(h)。


- Training error: data-fitting term related to a loss function

  训练误差：与损失函数相关的数据拟合项。

- Penalty: complexity of the decision function

  惩罚项：决策函数的复杂度。

- Constant λ: smoothing parameter tuned through cross-validation procedure

  常数 λ：通过交叉验证过程调整的平滑参数。

<a id="reading-regularization-purpose"></a>

### Why sacrifice some training fit?

**为什么愿意牺牲一点训练拟合**

Finite data contain both patterns and chance fluctuations. A flexible model can fit both, so small training error need not mean accurate prediction on new data. Regularization compares good fit with simpler or more stable solutions within one objective.

有限数据里既有规律，也有偶然波动。一个很灵活的模型可以把两者一起拟合，因此训练误差很小，并不意味着对新数据也准确。正则化把“拟合好”与“采用较简单或较稳定的解”放在同一个目标里比较。

$\lambda$ controls the penalty's contribution to the objective; the learning rate controls how the numerical algorithm updates parameters at each step. Changing $\lambda$ changes the problem being solved, while changing the learning rate mainly changes how its solution is approached. Standardization changes feature scales before fitting. These are three distinct roles.

$\lambda$ 控制惩罚在目标中的分量；学习率控制数值算法每一步怎样更新参数。改变 $\lambda$ 会改变要求解的问题，改变学习率主要影响怎样到达这个问题的解。标准化则是在拟合前调整特征的尺度，三者各有作用。

<details>
<summary>Example: how a zero-training-error curve changes for the same three points<br>例子：同样三个点，训练误差为零的曲线怎样变化</summary>

For the three points above, the line $\widehat h(t)=2+1.5t$ has residual sum of squares $1.5$. The quadratic $q(t)=1+1.5t+1.5t^2$ passes through all three, with zero training residual. Yet at $t=2$ their predictions are $5$ and $10$, respectively. Those three observations alone do not establish which extrapolates better.

对前面的三个点，直线 $\widehat h(t)=2+1.5t$ 的残差平方和为 $1.5$。二次曲线 $q(t)=1+1.5t+1.5t^2$ 能穿过全部三个点，训练残差为零；但在 $t=2$ 处，二者分别预测 $5$ 和 $10$。仅凭这三个观测，不能确认哪一个外推更好。

Now change the middle response from $1$ to $1+\Delta$. After refitting, the line predicts $5+\Delta/3$ at $t=2$, while the interpolating quadratic predicts $10-3\Delta$. At this location, the latter amplifies the same observational perturbation more strongly. This shows how flexibility lets finite-sample fluctuations enter predictions. Deciding whether overfitting occurs still requires data not used in fitting.

现在把中间的响应从 $1$ 改成 $1+\Delta$。重新拟合后，直线在 $t=2$ 处的预测变为 $5+\Delta/3$，插值二次曲线的预测变为 $10-3\Delta$。在这个位置，后者把同一个观测扰动放大得更多。这个计算说明模型灵活性怎样让有限样本中的波动进入预测；是否发生过拟合，还要通过未参与拟合的数据来判断。

</details>

<details>
<summary>Further detail: regularization beyond explicit penalties<br>延伸：显式惩罚以外的正则化思路</summary>

Applying suitable small input perturbations while requiring reasonable predictions is another way to limit excessive dependence on details. Dropout randomly masks units during training so that the model cannot always rely on one fixed cooperation path. Like this lecture's methods, these approaches restrict how training samples are used. Their effects depend on the task, perturbations, and training procedure; adding arbitrary noise does not automatically improve learning.

对输入施加适当的小扰动，并要求预测仍保持合理，是另一种限制模型过度依赖细节的办法。Dropout 则在训练时随机屏蔽部分单元，使模型不能总依赖某一条固定的协作路径。它们与本讲的共同点，是限制模型怎样利用训练样本；具体效果取决于任务、扰动方式和训练过程，不能把“增加任何噪声”都理解成改进学习。

Structure selection and parameter estimation can also interact, for example by exploring submodels during training. Linear models and explicit penalties first make this relation an optimization problem that can be analyzed directly.

结构选择和参数估计也可以相互影响，例如在训练中探索不同的子模型。这里先用线性模型和明确的惩罚项，把这种关系写成可以直接分析的优化问题。

</details>

<a id="section-24"></a>

## A. Sparsity and linear models Structured sparsity

**A. 稀疏性与线性模型：结构化稀疏性**

### Putting human priors in penalties Sparsity patterns

**将人的先验放进惩罚项：稀疏模式**

![image](<../Images/02_LM/image_006.jpg>)

### The simplest structured penalty Group LASSO

**最简单的结构化惩罚：Group LASSO**


- Group structure on the parameter $\beta ^ { * }$ : let G the number of groups of subsets of indices in $\{ 1 , \ldots , d \}$ and, for $g = 1 , \ldots , G$ , we denote by $\mathbf { \boldsymbol { x } } ( \bar { g } )$ the submatrix of X with variables in group $\boldsymbol { g }$ and by $\beta ^ { ( g ) }$ the coefficient vector applied to variables in group $\boldsymbol { g }$ and $d _ { g }$ is the size of group g.

  参数 $\beta ^ { * }$ 的分组结构：设 G 是 $\{ 1 , \ldots , d \}$ 中索引子集的分组数。对 $g = 1 , \ldots , G$，用 $\mathbf { \boldsymbol { x } } ( \bar { g } )$ 表示 X 中由第 $\boldsymbol { g }$ 组变量组成的子矩阵，用 $\beta ^ { ( g ) }$ 表示施加于第 $\boldsymbol { g }$ 组变量的系数向量；$d _ { g }$ 是第 g 组的大小。

- Group LASSO formulation:

  Group LASSO 表述：

$$
\widehat {\beta} _ {\lambda} \in \underset {\beta \in \mathbb {R} ^ {d}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| ^ {2} + \lambda \sum_ {g = 1} ^ {G} \sqrt {d _ {g}} \| \beta^ {(g)} \| \right\}
$$

![image](<../Images/02_LM/image_007.jpg>)

<a id="reading-group-lasso"></a>

### Selecting a group rather than a single coordinate

**选择一个组，而不只选择一个坐标**

Variables often have known groups: customer attributes and transaction histories are different kinds of information, while channels from a sensor group or related genes can also form a unit. Ordinary LASSO sees only coordinates; a penalty must communicate the grouping to the model.

变量往往有事先已知的分组：客户资料与交易历史是两类信息，一组传感器的多个通道或一组相关基因也可以作为一个整体。普通 LASSO 只看到一串坐标，分组信息需要通过惩罚项告诉模型。

Group LASSO first computes each group's Euclidean length $\|\beta^{(g)}\|_2$ and then sums the group lengths. A whole group vector becoming zero removes that group's features together. For coefficient groups $(3,4)$ and $(0,0)$, for example, the unweighted group penalty is $5+0$. Directions within a nonzero group can still vary continuously.

Group LASSO 先计算每组的欧氏长度 $\|\beta^{(g)}\|_2$，再把各组长度加起来。整个组向量变成零，就意味着这组特征一起退出预测。例如两组系数为 $(3,4)$ 和 $(0,0)$ 时，未加权的组惩罚是 $5+0$；非零组内的方向仍可以连续调整。

It therefore encourages sparsity between groups, without specifically encouraging sparsity inside every retained group. Retaining a group also does not force every coefficient in it to be nonzero. The slide's $\sqrt{d_g}$ adjusts weights for group size, while the within-group norm is $\ell_2$, including its outer square root.

因此，它鼓励“组间稀疏”，不会专门鼓励每个非零组内部也很稀疏；一个组被保留，也不意味着其中每个系数都被强制设为非零。课件中的 $\sqrt{d_g}$ 用来调整不同组大小的惩罚权重，而组内采用的是 $\ell_2$ 范数，保留外面的平方根。

<details>
<summary>Further detail: selecting both groups and variables within groups<br>延伸：怎样同时选择组和组内变量</summary>

For disjoint groups covering all variables, directly replacing the within-group $\ell_2$ norm with $\ell_1$ gives

对于互不重叠、覆盖全部变量的分组，如果直接把组内 $\ell_2$ 改成 $\ell_1$，则

$$
\sum_g\|\beta^{(g)}\|_1=\|\beta\|_1.
$$

This reduces to ordinary LASSO, or weighted LASSO if different group weights are retained; it does not automatically create a separate group-selection mechanism. To encourage both entire groups and within-group coordinates to become zero, combine two penalties:

这会退回普通 LASSO；若保留不同组权重，则是加权 LASSO，并不会自动产生独立的组选择机制。要同时鼓励整组归零和组内坐标归零，可以叠加两种惩罚：

$$
\lambda_1\sum_g\sqrt{d_g}\|\beta^{(g)}\|_2
+\lambda_2\|\beta\|_1.
$$

This combination is called Sparse Group LASSO. [Original discussion by Friedman, Hastie, and Tibshirani](https://arxiv.org/abs/1001.0736)

这种组合称为 Sparse Group LASSO。[Friedman、Hastie 与 Tibshirani 的原文说明](https://arxiv.org/abs/1001.0736)

</details>


- Enforcing temporal coherence leads to adding a penalty term:

  强制时间上的一致性，会引入如下惩罚项：

$$
\widehat {\beta} _ {\lambda} \in \underset {\beta \in \mathbb {R} ^ {d}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| ^ {2} + \lambda \| \beta \| _ {1} + \mu \sum_ {j = 2} ^ {d} | \beta_ {j} - \beta_ {j - 1} | \right\}
$$



<a id="reading-fused-lasso"></a>

### Adjacency can also be part of the model

**相邻位置也可以成为模型的一部分**

Ordinary LASSO penalizes columns separately. Reordering data columns and their corresponding coefficients together leaves its objective unchanged, so it has no inherent knowledge of adjacency. Time series, spatial positions, or adjacent sequence sites may require preserving order information.

普通 LASSO 对各列的惩罚相互独立。如果把数据列和对应系数一起重新排序，目标值不变，因此它本身不知道哪些变量相邻。时间序列、空间位置或序列中的相邻位点，则可能需要保留这种顺序信息。

The added penalty $\sum_{j=2}^d|\beta_j-\beta_{j-1}|$ above is the adjacent-difference penalty of fused LASSO. Compare these two vectors:

上式额外惩罚 $\sum_{j=2}^d|\beta_j-\beta_{j-1}|$，称为 fused LASSO 的相邻差分惩罚。比较两个向量：

$$
\beta^{(A)}=(0,0,3,3,3,0),\qquad
\beta^{(B)}=(0,3,0,3,0,3).
$$

Both have three nonzero coefficients and $\ell_1$ norm $9$, but their sums of absolute adjacent differences are $6$ and $15$. With equal fitting terms, the new penalty favors the contiguous segments in A. $\lambda$ controls coefficient shrinkage toward zero, while $\mu$ controls the cost of adjacent jumps, encouraging piecewise constant coefficients.

两者都有三个非零系数，$\ell_1$ 范数也都是 $9$，但相邻差分绝对值之和分别为 $6$ 和 $15$。在拟合项相同的情况下，新的惩罚更偏好连续成段的 A。$\lambda$ 调节系数本身向零收缩的程度，$\mu$ 调节相邻跳变的代价，从而鼓励一段一段保持相同系数。

<details>
<summary>Further detail: expressing prior knowledge in the optimization objective<br>延伸：把已有知识写进优化目标</summary>

Groups and adjacency are modeling knowledge. Similarly, if a candidate function should satisfy a physical equation, substitute it into that equation, compute the equation residual, and minimize that residual together with data-fitting error. Physics-informed neural networks use this kind of approach. [Related research](https://arxiv.org/abs/1711.10561)

分组和邻接关系都是建模知识。类似地，如果候选函数应满足某个物理方程，可以把它代入方程，计算方程残差，再把该残差与数据拟合误差一起最小化；物理信息神经网络采用的就是这类思路。[相关研究](https://arxiv.org/abs/1711.10561)

First decide which relationships a solution should obey, then consider how to solve the resulting optimization problem. Penalizing violations with a finite weight usually defines a soft constraint. Exact satisfaction requires appropriate constraints or structural design. Data noise, equation approximations, and their relative weights all affect the resulting solution.

建模时首先要决定希望解遵守什么关系，再考虑如何求解相应优化问题。用有限权重惩罚违反关系的程度，通常表达的是软约束；若要求某种关系严格成立，还需要合适的约束或结构设计。数据噪声、方程近似和两者的权重都会影响最后得到的解。

</details>

---

[本课目录](../02_LM_zh.md) · [上一篇：稀疏性与模型选择](03_sparsity_and_model_selection.md) · [下一篇：岭回归与对偶](05_ridge_and_duality.md)
