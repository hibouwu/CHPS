# 5. 岭回归与对偶

[本课目录](../02_LM_zh.md) · [上一篇：Lasso 与结构化稀疏性](04_lasso_and_structured_sparsity.md) · [下一篇：正则化比较与参数选择](06_regularization_and_validation.md)

<a id="section-25"></a>

<a id="ridge"></a>

## A. Sparsity and linear models Ridge regression

**A. 稀疏性与线性模型：岭回归**

### Penalized optimization Other penalties?

**惩罚优化：其他惩罚项？**


- Until now: hypothesis class with linear functions $h \in \mathcal H$ and variations on sparsity-inducing penalties

  到目前为止：由线性函数 $h \in \mathcal H$ 构成的假设类，以及诱导稀疏性的各种惩罚项。

$$
\text{准则} (h) = \text{训练误差} (h) + \lambda \text{惩罚项} (h)
$$


- This idea goes back to the 60s (Ivanov, John, Lavrent’ev, Tikhonov) where the penalty operated as a regularizer of solutions for ill-posed problems.

  这个思想可追溯到 20 世纪 60 年代（Ivanov、John、Lavrent’ev、Tikhonov），当时惩罚项被用作不适定问题解的正则化器。

<a id="section-26"></a>

## Ill-posed problem in statistics High dimensional least square regression

**统计中的不适定问题：高维最小二乘回归**


- Assume d larger than n

  假设 d 大于 n。

- Then when solving the least square optimization problem, we observe that we have less equations than variables: this is the case of an underdetermined linear system.

  求解最小二乘优化问题时，可以看到方程数少于变量数：这就是欠定线性系统的情形。

- Another way to put this is to observe that $\mathbf X^T\mathbf X$ is not full rank, hence it is not invertible and there is an infinity of solutions.

  另一种说法是，$\mathbf X^T\mathbf X$ 不满秩，因而不可逆，并且有无穷多个解。

<a id="reading-underdetermined"></a>

When $d>n$, at least $d-n$ independent parameter directions cannot be distinguished by $\mathbf X$. If $\mathbf v\neq0$ and $\mathbf X\mathbf v=0$, then $\beta$ and $\beta+\mathbf v$ give identical predictions at every training point.

当 $d>n$ 时，至少有 $d-n$ 个独立的参数方向无法被 $\mathbf X$ 区分。若 $\mathbf v\neq0$ 且 $\mathbf X\mathbf v=0$，那么 $\beta$ 与 $\beta+\mathbf v$ 在所有训练点上的预测完全相同。

Infinitely many least-squares coefficient solutions always exist in this non-full-column-rank case. Whether training residuals can reach zero additionally depends on whether $\mathbf Y$ belongs to the column space of $\mathbf X$. In particular, if $\mathbf X$ has full row rank, its column space is $\mathbb R^n$, and any response vector can be fitted exactly. Regularization adds a criterion for selecting among solutions the data cannot distinguish.

无穷多个最小二乘解总是存在于这种非满列秩情形；至于能否把训练残差降到零，还要看 $\mathbf Y$ 是否属于 $\mathbf X$ 的列空间。特别地，若 $\mathbf X$ 满行秩，则列空间等于 $\mathbb R^n$，任意响应都可以被完全拟合。正则化给这些数据无法区分的解增加了选择依据。

<a id="section-27"></a>

## The oldest regularizer in statistics Ridge regression

**统计中最早的正则化方法：岭回归**


- The Ridge estimator is the solution of the following penalized optimization problem: for any $\lambda > 0$

  Ridge 估计量是下列惩罚优化问题的解：对任意 $\lambda > 0$，

$$
\widehat {\beta} _ {\lambda} \in \underset {\beta \in \mathbb {R} ^ {d}} {\arg \min} \left\{\| \mathbf {Y} - \mathbf {X} \beta \| ^ {2} + \lambda \| \beta \| _ {2} ^ {2} \right\}
$$

<a id="reading-ridge-shrinkage"></a>

### How Ridge produces smaller, more stable coefficients

**Ridge 如何得到更小、更稳定的系数**

Continue with $\mathbf X=I_3$ and $\mathbf Y=(3,0.4,-2)^T$. Each coordinate minimizes

继续使用 $\mathbf X=I_3$、$\mathbf Y=(3,0.4,-2)^T$。每个坐标需要最小化

$$
(z-b)^2+\lambda b^2.
$$

Setting the derivative to zero gives $\widehat b=z/(1+\lambda)$. With $\lambda=2$,

令导数为零，得到 $\widehat b=z/(1+\lambda)$。在 $\lambda=2$ 时，

$$
\widehat\beta_{\mathrm{Ridge}}=(1,\;0.4/3,\;-2/3)^T.
$$

Compared with LASSO above, all three coefficients shrink toward zero, but initially nonzero coordinates do not become zero through this shrinkage formula. LASSO's absolute value has a corner at zero, whereas Ridge's quadratic penalty is smooth there, producing different selection effects.

与前面的 LASSO 相比，三个系数都向零缩小，原本非零的坐标没有因这个收缩公式而归零。LASSO 的绝对值在零点保留一个尖角；Ridge 的二次惩罚在零点是平滑的，因此这两种惩罚产生了不同的选择效果。

With two identical columns and fixed total contribution $\beta_1+\beta_2=s$, the quantity $\beta_1^2+\beta_2^2$ is minimized at $\beta_1=\beta_2=s/2$. Ridge therefore tends to share contributions between identical or similar features, reducing unstable representations in which large positive and negative coefficients cancel.

在两列相同的例子中，给定总贡献 $\beta_1+\beta_2=s$ 后，$\beta_1^2+\beta_2^2$ 在 $\beta_1=\beta_2=s/2$ 时最小。Ridge 因而倾向于把贡献分给相同或相近的特征，减少“大正系数和大负系数相互抵消”这一类不稳定表达。

The slide's formula penalizes every coefficient included in $\beta$. Practical regression often treats the intercept separately without penalizing it, or centers data before estimating other coefficients. In that case, shrinking those coefficients to zero returns to a constant prediction, not necessarily numerical zero.

这里的课件公式对写进 $\beta$ 的全部系数施加惩罚。实际回归常将截距单独处理，不惩罚截距，或先中心化再估计其他系数；那时系数收缩到零表示回到一个常数预测，而不一定回到数值零。

<a id="section-28"></a>

## Derivation of ridge regression estimator

**岭回归估计量的推导**


- We denote the objective function:

  记目标函数为：

$$
F (\beta) = \left(\mathbf {Y} - \mathbf {X} \beta\right) ^ {T} \left(\mathbf {Y} - \mathbf {X} \beta\right) + \lambda \beta^ {T} \beta
$$


- Thanks to convexity and differentiability of F, we obtain the solution by solving

  利用 F 的凸性和可微性，通过求解下式得到解：

$$
\nabla F (\beta) = 2 \mathbf {X} ^ {T} (\mathbf {X} \beta - \mathbf {Y}) + 2 \lambda \beta = 0
$$


- Solution:

  解为：

$$
\widehat {\beta} _ {\lambda} = \left(\mathbf {X} ^ {T} \mathbf {X} + \lambda I _ {d}\right) ^ {- 1} \mathbf {X} ^ {T} \mathbf {Y}
$$

because $\mathbf X^T\mathbf X+\lambda I_d$ always invertible.

因为 $\mathbf X^T\mathbf X+\lambda I_d$ 总是可逆的。


- Computation still painful for d very large...

  当 d 很大时，计算仍然困难……

<a id="reading-ridge-eigenvalues"></a>

### Why adding λI makes the system solvable

**为什么加上 λI 就能求解**

For any nonzero vector $v$, whenever $\lambda>0$,

对任意非零向量 $v$，只要 $\lambda>0$，

$$
v^T(\mathbf X^T\mathbf X+\lambda I_d)v
=\|\mathbf Xv\|^2+\lambda\|v\|^2>0.
$$

The matrix is therefore positive definite and invertible. Zero eigenvalues are raised to $\lambda$, and very small eigenvalues are raised as well. Numerically, this limits amplification by small denominators; statistically, it restricts coefficient magnitudes. Both interpretations lead to the same Ridge formula. [Regularized least squares](https://www.seas.ucla.edu/~vandenbe/133A/lectures/mols.pdf)

因此这个矩阵正定、可逆。原本为零的特征值被提高到 $\lambda$，很小的特征值也被抬高：数值上减弱了小分母造成的放大，统计上对应限制系数的幅度。这两种解释导向同一个 Ridge 公式。[正则化最小二乘](https://www.seas.ucla.edu/~vandenbe/133A/lectures/mols.pdf)

<details>
<summary>Derivation: shrinkage along singular-vector directions<br>推导：在奇异向量方向上看收缩</summary>

Let $\mathbf X=U\Sigma V^T$, with nonzero singular values $s_j$. In direction $j$, least squares uses the factor $1/s_j$, while Ridge uses

设 $\mathbf X=U\Sigma V^T$，非零奇异值为 $s_j$。最小二乘在第 $j$ 个方向使用因子 $1/s_j$，Ridge 使用

$$
\frac{s_j}{s_j^2+\lambda}
=\frac{s_j^2}{s_j^2+\lambda}\frac1{s_j}.
$$

Relative to the least-squares coefficient in that direction, Ridge thus applies a shrinkage factor between $0$ and $1$. A small $s_j$ means weak data constraints in that direction and stronger shrinkage. If $s_j=0$, Ridge sets this data-invisible direction to zero.

也就是说，相对于该方向上的最小二乘系数，Ridge 乘了一个介于 $0$ 与 $1$ 之间的收缩因子。$s_j$ 很小时，数据在这个方向上提供的约束很弱，收缩就更强。若 $s_j=0$，Ridge 把这个数据不可见的方向设为零。

Along nonzero directions, least squares is recovered as $\lambda\to0$. With rank deficiency, the overall limit is the minimum-norm least-squares solution. Increasing $\lambda$ strengthens shrinkage and also changes bias, so its strength still needs to be selected appropriately.

在非零方向上，$\lambda\to0$ 时逐渐恢复最小二乘；有秩亏时，整体极限对应最小范数的最小二乘解。增加 $\lambda$ 会增加收缩，也会改变偏差，因而仍需要选择合适的强度。

</details>

<a id="section-29"></a>

## Dual optimization problem Formulation and KKT conditions

**对偶优化问题：表述与 KKT 条件**

<a id="reading-dual-dimensions"></a>

The preceding formula estimates a $d$-dimensional coefficient vector by handling a $d\times d$ matrix. An alternative assigns weights to the $n$ training samples and handles a $n\times n$ matrix:

前面的公式求一个 $d$ 维系数向量，需要处理 $d\times d$ 的矩阵。另一种表示改为给 $n$ 个训练样本分配权重，处理 $n\times n$ 的矩阵：

| Representation<br>表示 | Main matrix<br>主要矩阵 | Meaning of one matrix entry<br>矩阵中的一项表示什么 |
|---|---|---|
| Parameter representation<br>参数表示 | $\mathbf X^T\mathbf X$, size $d\times d$<br>$\mathbf X^T\mathbf X$，大小 $d\times d$ | Inner product of two feature columns across all samples<br>两个特征列在所有样本上的内积 |
| Sample representation<br>样本表示 | $\mathbf X\mathbf X^T$, size $n\times n$<br>$\mathbf X\mathbf X^T$，大小 $n\times n$ | Inner product of two sample feature vectors<br>两个样本特征向量的内积 |

When $n$ is much smaller than $d$, the latter can be cheaper. Both describe the same Ridge problem. Introducing residual variable $r$ temporarily separates squared error from the parameter penalty; Lagrange multipliers return the relation $r=\mathbf X\beta-\mathbf Y$ to the objective. There are only equality constraints here, and the stationarity relations below must hold together with this constraint.

当 $n$ 比 $d$ 小很多时，后一种表示可能更省计算。两者描述同一个 Ridge 问题。引入残差变量 $r$，是为了把平方误差与参数惩罚暂时分开；拉格朗日乘子把关系 $r=\mathbf X\beta-\mathbf Y$ 放回目标函数。此处只有等式约束，下面的驻点关系还必须与这条约束一起成立。


- Equivalent formulation of ridge regression optimization:

  岭回归优化的等价表述：

$$
\min _ {\beta \in \mathbb {R} ^ {d}, r \in \mathbb {R} ^ {n}} \left\{\frac {1}{2} \| r \| ^ {2} + \frac {\lambda}{2} \| \beta \| ^ {2} \right\} \quad \text{满足} r = \mathbf {X} \beta - \mathbf {Y}
$$


- Lagrange formulation with multiplier vector $\alpha$

  乘子向量为 $\alpha$ 的拉格朗日表述：

$$
\mathcal {L} (\beta , r, \alpha) = \frac {1}{2} \| r \| ^ {2} + \frac {\lambda}{2} \| \beta \| ^ {2} + \alpha^ {T} (r - \mathbf {X} \beta + \mathbf {Y})
$$


- Karush-Kuhn-Tucker conditions: zeroing gradient wrt primal variables $\beta , r ,$ , leads to:

  Karush–Kuhn–Tucker 条件：令关于原变量 $\beta , r ,$ 的梯度为零，得到：

$$
\beta (\alpha) = \frac {1}{\lambda} \mathbf {X} ^ {T} \alpha \quad \text{且} \quad r (\alpha) = - \alpha
$$

<a id="section-30"></a>

## Dual optimization problem Resolution

**对偶优化问题：求解**


- Then, an equivalent formulation of ridge regression optimization is given by:

  于是，岭回归优化的一种等价表述为：

$$
\mathcal {L} (\beta (\alpha), r (\alpha), \alpha) = \frac {1}{2} \| \alpha \| ^ {2} + \frac {1}{2 \lambda} \| \mathbf {X} ^ {T} \alpha \| + \alpha^ {T} \left(- \alpha - \frac {1}{\lambda} \mathbf {X X} ^ {T} \alpha + \mathbf {Y}\right)
$$

> **Note:** The slides omit a square on $\|\mathbf X^T\alpha\|$. Restoring it, substituting, and simplifying gives the dual function $g(\alpha)=\alpha^T\mathbf Y-\tfrac12\|\alpha\|^2-\tfrac1{2\lambda}\|\mathbf X^T\alpha\|^2$, which the dual problem maximizes. The original intermediate substitution expression remains above in full.

> **译注：** 原课件的 $\|\mathbf X^T\alpha\|$ 漏了平方。补上平方后，代回并整理得到对偶函数 $g(\alpha)=\alpha^T\mathbf Y-\tfrac12\|\alpha\|^2-\tfrac1{2\lambda}\|\mathbf X^T\alpha\|^2$，对偶问题是最大化该函数。原文的代入中间式完整保留在上方。


- Solution:

  解为：

$$
\widehat {\alpha} = \lambda \left(\mathbf {X X} ^ {T} + \lambda I _ {n}\right) ^ {- 1} \mathbf {Y} \quad \text{且} \quad \widehat {\beta} = \frac {1}{\lambda} \mathbf {X} ^ {T} \widehat {\alpha}
$$

<a id="section-31"></a>

## Dual optimization problem Interpretation of the result

**对偶优化问题：结果的解释**


- The prediction on $x \in \mathbb { R } ^ { d }$ can be expressed in terms of α

  对 $x \in \mathbb { R } ^ { d }$ 的预测可用 α 表示。

$$
x ^ {T} \widehat {\beta} = \frac {1}{\lambda} x ^ {T} \mathbf {X} ^ {T} \widehat {\alpha} = \frac {1}{\lambda} \sum_ {i = 1} ^ {n} \widehat {\alpha} _ {i} x ^ {T} X _ {i}
$$


- We can use the identity:

  可以利用恒等式：

$\pmb { \mathsf { X } } ^ { T } \left( \pmb { \mathsf { X } } \pmb { \mathsf { X } } ^ { T } + \lambda \pmb { I } _ { n } \right) ^ { - 1 } = \left( \pmb { \mathsf { X } } ^ { T } \pmb { \mathsf { X } } + \lambda \pmb { I } _ { d } \right) ^ { - 1 } \pmb { \mathsf { X } } ^ { T }$ to check the solutions are the same.

$\pmb { \mathsf { X } } ^ { T } \left( \pmb { \mathsf { X } } \pmb { \mathsf { X } } ^ { T } + \lambda \pmb { I } _ { n } \right) ^ { - 1 } = \left( \pmb { \mathsf { X } } ^ { T } \pmb { \mathsf { X } } + \lambda \pmb { I } _ { d } \right) ^ { - 1 } \pmb { \mathsf { X } } ^ { T }$ 来验证两个解相同。


- Important observation! Optimization and function evaluation only require the pairwise scalar product between $x ^ { \prime } s$ and data points $X _ { i } ^ { \prime } s$

  重要观察：优化与函数求值只需要 $x ^ { \prime } s$ 与数据点 $X _ { i } ^ { \prime } s$ 之间的两两内积。

<a id="reading-dual-to-kernel"></a>

### A prediction can be built from inner products with training samples

**一次预测可以由与训练样本的内积组成**

To simplify notation, set $c=\widehat\alpha/\lambda$. Substituting the earlier results gives

为简化下面的记号，令 $c=\widehat\alpha/\lambda$。代入前面的结果，有

$$
c=(\mathbf X\mathbf X^T+\lambda I_n)^{-1}\mathbf Y,\qquad
\widehat\beta=\mathbf X^Tc,\qquad
\widehat h(x)=\sum_{i=1}^{n}c_i\,x^TX_i.
$$

These $c_i$ are signed linear-combination weights, not probabilities. Training only requires all $X_i^TX_j$; prediction only requires $x^TX_i$ between the new input and each training point. This is where kernel methods can enter later.

这些 $c_i$ 是可正可负的线性组合权重，不是概率。训练时只需要所有 $X_i^TX_j$，预测时只需要新输入与各训练点的 $x^TX_i$。这就是后面核方法可以接入的位置。

<details>
<summary>Derivation: combining the KKT conditions into a linear system<br>推导：把 KKT 条件连成一个线性系统</summary>

Using $\beta=\mathbf X^T\alpha/\lambda$, $r=-\alpha$, and $r=\mathbf X\beta-\mathbf Y$,

由 $\beta=\mathbf X^T\alpha/\lambda$、$r=-\alpha$ 和 $r=\mathbf X\beta-\mathbf Y$，

$$
-\alpha=\frac1\lambda\mathbf X\mathbf X^T\alpha-\mathbf Y,
\qquad
(\mathbf X\mathbf X^T+\lambda I_n)\alpha=\lambda\mathbf Y.
$$

Solving for $\alpha$ and substituting back into $\beta$ gives the same Ridge solution. The computation only needs to solve this linear system, without explicitly constructing a matrix inverse.

解出 $\alpha$ 后再代回 $\beta$，便得到同一个 Ridge 解。优化时只需解这个线性系统，无须先构造矩阵的显式逆。

</details>

---

[本课目录](../02_LM_zh.md) · [上一篇：Lasso 与结构化稀疏性](04_lasso_and_structured_sparsity.md) · [下一篇：正则化比较与参数选择](06_regularization_and_validation.md)
