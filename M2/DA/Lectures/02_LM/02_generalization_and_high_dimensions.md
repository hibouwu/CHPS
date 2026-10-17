# 2. 泛化与高维问题

[本课目录](../02_LM_zh.md) · [上一篇：线性模型与最小二乘](01_linear_models_and_least_squares.md) · [下一篇：稀疏性与模型选择](03_sparsity_and_model_selection.md)

<a id="section-07"></a>

<a id="regression-risk"></a>

## What all student (should) know The bias-variance trade-off in regression

**所有学生都（应该）知道的内容：回归中的偏差—方差权衡**

<a id="reading-fixed-design-risk"></a>

First fix the input matrix $\mathbf X$ and imagine repeatedly observing new responses with independent noise at these inputs, refitting each time. $\mathbf h^*$ contains the true means at those locations, while $\widehat{\mathbf h}_n$ varies with noise and training data. The expectation measures the average error across these repeated fits.

下面先固定输入矩阵 $\mathbf X$，想象在这些输入位置反复观测带有独立噪声的新响应，每次重新拟合。$\mathbf h^*$ 是这些位置上的真实均值，$\widehat{\mathbf h}_n$ 随噪声和训练数据变化；期望衡量的是这种重复拟合的平均误差。

The comparison is between estimated and true means, not directly against training labels. Predicting another independent set of labels with the same noise variance at the same inputs adds irreducible noise $\sigma^2$ to mean squared prediction error. Arbitrary new inputs also require accounting for their distribution; this section's $d/n$ is not a universal formula for test error.

这里比较的是“估计出的均值”和“真实均值”，不是直接比较训练标签。若要预测相同输入位置上另一组独立、同方差的新标签，平均平方预测误差还会多出不可约噪声 $\sigma^2$。预测任意新输入时，也要结合新输入的分布，不能把本节的 $d/n$ 直接当成所有测试误差的公式。


- Model: $\pmb { \mathsf { Y } } = \pmb { \mathsf { h } } ^ { * } + \varepsilon \in \mathbb { R } ^ { n }$

  模型：$\pmb { \mathsf { Y } } = \pmb { \mathsf { h } } ^ { * } + \varepsilon \in \mathbb { R } ^ { n }$。

- Computation of LSE: $\widehat { \mathbf { h } } _ { \mathbf { n } } = \widehat { \Pi } \mathbf { Y }$ where $\widehat { \Pi } = \pmb { \mathsf { X } } ( \pmb { \mathsf { X } } ^ { T } \pmb { \mathsf { X } } ) ^ { - 1 } \pmb { \mathsf { X } } ^ { T }$

  最小二乘估计的计算：$\widehat { \mathbf { h } } _ { \mathbf { n } } = \widehat { \Pi } \mathbf { Y }$，其中 $\widehat { \Pi } = \pmb { \mathsf { X } } ( \pmb { \mathsf { X } } ^ { T } \pmb { \mathsf { X } } ) ^ { - 1 } \pmb { \mathsf { X } } ^ { T }$。

- A notion of risk:

  一种风险的定义：

$$
L (\widehat {\mathbf {h}} _ {\mathbf {n}}) = \frac {1}{n} \mathbb {E} \big (\| \mathbf {h} ^ {*} - \widehat {\mathbf {h}} _ {\mathbf {n}} \| ^ {2} \big)
$$

### Bias-variance decomposition (1/2) Derivation

**偏差—方差分解（1/2）：推导**


- First note that: $\widehat { \mathbf { h } } _ { \mathbf { n } } = \widehat { \Pi } \mathbf { Y } = \widehat { \Pi } ( \mathbf { h } ^ { * } + \varepsilon )$ and then

  首先注意到 $\widehat { \mathbf { h } } _ { \mathbf { n } } = \widehat { \Pi } \mathbf { Y } = \widehat { \Pi } ( \mathbf { h } ^ { * } + \varepsilon )$，于是

$$
\mathbf {h} ^ {*} - \widehat {\mathbf {h}} _ {\mathfrak {n}} = (I _ {n} - \widehat {\Pi}) \mathbf {h} ^ {*} - \widehat {\Pi} \varepsilon
$$


- Note that $\widehat { \Pi } : \mathbb { R } ^ { n } \to \mathbb { R } ^ { n }$ the orthogonal projection onto $\mathcal { H } ( X )$

  注意，$\widehat { \Pi } : \mathbb { R } ^ { n } \to \mathbb { R } ^ { n }$ 是到 $\mathcal { H } ( X )$ 上的正交投影。

$$
\widehat {\Pi} \circ \widehat {\Pi} = \widehat {\Pi}
$$


- By orthogonality of the images of $I _ { n } - { \widehat { \Pi } }$ and $\widehat { \Pi } .$ :

  由于 $I _ { n } - { \widehat { \Pi } }$ 和 $\widehat { \Pi } .$ 的像空间正交：

$$
\begin{array}{r} L (\widehat {h} _ {n}) = \frac {1}{n} \mathbb {E} \big (\| \mathbf {h} ^ {*} - \widehat {\mathbf {h}} _ {\mathbf {n}} \| ^ {2} \big) \\ = \frac {1}{n} \mathbb {E} \big (\| (I _ {n} - \widehat {\Pi}) \mathbf {h} ^ {*} \| ^ {2} + \| \widehat {\Pi} \varepsilon \| ^ {2} \big) \end{array}
$$

### Bias-variance decomposition (2/2) Result

**偏差—方差分解（2/2）：结果**


- Using an additional technical result (next slide):

  利用一个额外的技术结果（见下一页）：

$$
\begin{array}{r l} & L (\widehat {h} _ {n}) = \frac {1}{n} \mathbb {E} \big (\| \mathbf {h} ^ {*} - \widehat {\mathbf {h}} _ {\mathbf {n}} \| ^ {2} \big) \\ & \quad = \frac {1}{n} \mathbb {E} \big (\| (I _ {n} - \widehat {\Pi}) \mathbf {h} ^ {*} \| ^ {2} + \| \widehat {\Pi} \varepsilon \| ^ {2} \big) \\ & \quad = \underbrace {\frac {1}{n} \mathbb {E} \big (\| (I _ {n} - \widehat {\Pi}) \mathbf {h} ^ {*} \| ^ {2} \big)} _ {\text{偏差}} + \underbrace {\sigma^ {2} \frac {d}{n}} _ {\text{方差}} \end{array}
$$


- Used in model selection (e.g. AIC = Akaike Information Criterion)

  用于模型选择，例如 AIC，即 Akaike Information Criterion（赤池信息准则）。

### Explanation of the d/n term

**d/n 项的解释**

Property on the norm of projections of gaussian random vectors:

高斯随机向量投影的范数性质：


- Assume $\mathbf { Z }$ is a gaussian random vector $ { \mathcal { N } _ { n } } ( 0 ,  { I _ { n } } )$ in $\mathbb { R } ^ { n }$ , H is a linear subspace of $\mathbb { R } ^ { n }$ and $\Pi : \mathbb { R } ^ { n }  \mathbb { R } ^ { n }$ a linear projection onto $\mathcal { H }$

  假设 $\mathbf { Z }$ 是 $\mathbb { R } ^ { n }$ 中服从 $ { \mathcal { N } _ { n } } ( 0 ,  { I _ { n } } )$ 的高斯随机向量，H 是 $\mathbb { R } ^ { n }$ 的线性子空间，$\Pi : \mathbb { R } ^ { n }  \mathbb { R } ^ { n }$ 是到 $\mathcal { H }$ 的线性投影。

- Then: the random vector $\Pi _ { \mathcal { H } } \mathbf { Z }$ has gaussian distribution $\mathcal { N } _ { n } ( 0 , \Pi )$ on $\mathbb { R } ^ { n }$ (linear transformation of a gaussian is a gaussian)

  则随机向量 $\Pi _ { \mathcal { H } } \mathbf { Z }$ 在 $\mathbb { R } ^ { n }$ 上服从高斯分布 $\mathcal { N } _ { n } ( 0 , \Pi )$（高斯随机向量的线性变换仍为高斯随机向量）。

- Furthermore: $\|\Pi Z\|^2$ follows a chi-square distribution with

  此外，$\|\Pi Z\|^2$ 服从卡方分布，并且

$$
\mathbb {E} (\| \Pi \mathbf {Z} \| ^ {2}) = \dim (\mathcal {H})
$$

> **Note:** These properties require orthogonal projection. If the projected subspace has dimension r, the squared norm has a chi-square distribution with r degrees of freedom.

> **译注：** 上述性质要求正交投影。若投影子空间维度为 r，则平方范数服从自由度为 r 的卡方分布。

<a id="reading-variance-directions"></a>

### Each additional fitted direction admits another contribution from noise

**每多拟合一个方向，就多接纳一份噪声**

Once $\mathbf X$ is fixed, projection separates $\mathbf h^*$ into a component representable by the model and one it cannot represent. The latter produces the squared bias above. At the same time, $\widehat\Pi\varepsilon$ retains noise components aligned with the model directions, producing variance.

固定 $\mathbf X$ 后，投影把 $\mathbf h^*$ 分成能被模型表示的部分和无法表示的部分。后者形成上式的平方偏差。与此同时，$\widehat\Pi\varepsilon$ 把噪声中恰好沿模型方向的成分也保留下来，形成方差。

For a model of rank $d$, each orthogonal direction contributes average noise energy $\sigma^2$, totaling $d\sigma^2$; division by $n$ gives $\sigma^2d/n$. The three-point line example has two free directions, an intercept and a slope, so this term is $2\sigma^2/3$. Fitting only a constant reduces it to $\sigma^2/3$, at the potential cost of missing the true trend.

对于秩为 $d$ 的模型，每个正交方向贡献平均 $\sigma^2$ 的噪声能量，合计 $d\sigma^2$，再除以 $n$ 就是 $\sigma^2d/n$。在三个点的直线例子中，有常数方向和斜率方向两个自由方向，因此这一项为 $2\sigma^2/3$。若只拟合一个常数，则变成 $\sigma^2/3$，代价是可能无法表示真正的变化趋势。

<details>
<summary>Derivation: obtaining d/n without expanding a chi-square density<br>推导：不用展开卡方密度也能得到 d/n</summary>

Let the $d$ columns of $\mathbf Q$ form an orthonormal basis for the model space, so $\widehat\Pi=\mathbf Q\mathbf Q^T$. Noise projected onto each unit direction has variance $\sigma^2$, hence

设 $\mathbf Q$ 的 $d$ 个列向量构成模型空间的一组标准正交基，则 $\widehat\Pi=\mathbf Q\mathbf Q^T$。噪声沿每个单位方向的投影方差都是 $\sigma^2$，所以

$$
\mathbb E\|\widehat\Pi\varepsilon\|^2
=\mathbb E\|\mathbf Q^T\varepsilon\|^2
=\sum_{j=1}^{d}\mathbb E(q_j^T\varepsilon)^2
=d\sigma^2.
$$

This expectation requires only mean-zero noise with covariance $\sigma^2I_n$. Gaussianity additionally gives $\|\widehat\Pi\varepsilon\|^2/\sigma^2\sim\chi_d^2$. If the model matrix has actual rank $r<d$, the number of free directions is $r$.

这个期望计算只需要零均值和协方差 $\sigma^2I_n$。高斯假设进一步给出 $\|\widehat\Pi\varepsilon\|^2/\sigma^2\sim\chi_d^2$。若模型矩阵的实际秩是 $r<d$，对应的自由方向数就是 $r$。

</details>

<a id="section-08"></a>

## How Machine Learning takes over linear regression

**机器学习如何接续线性回归**


1. What if non-additive noise? Other tasks than regression?

   如果噪声不是加性的，会怎样？回归以外的任务呢？

2. From linear to nonlinear models

   从线性模型到非线性模型。

3. What replaces the dimension d as a measure of complexity in nonlinear models?

   在非线性模型中，什么量替代维度 d 来衡量复杂度？

4. Is the d/n rate also typical for larger hypothesis classes? What if d larger than n ?

   d/n 的速率对更大的假设类是否也具有代表性？如果 d 大于 n 呢？

<a id="section-09"></a>

## From classical statistics to Machine Learning

**从经典统计到机器学习**


- Handling models in high dimensions:

  处理高维模型：

$$
d \gg 1, d \gg n
$$


- Questioning dimensionality:

  重新审视维度：

number of parameters vs. complexity of set of functions

参数个数与函数集合复杂度的比较。

<a id="reading-high-dimensional-regimes"></a>

There are two distinct meanings of large here. A large absolute $d$ increases storage and computation; a large $d$ relative to $n$ means estimating many quantities from few observational constraints. For example, 3,000 variables with 100,000 observations is very different from 3,000 variables with 100 observations.

这里有两种不同的“大”。$d$ 本身大，会增加存储和计算量；$d$ 相对 $n$ 大，则意味着需要估计的量很多、观测提供的约束很少。例如，同样是 3,000 个变量，配 100,000 条观测和配 100 条观测，是很不一样的问题。

For linear models, matrix rank directly counts independent feature directions. With redundant columns, the parameter count already differs from this count. For more general function families, complexity also depends on parameter constraints and function structure, so simply counting parameters is insufficient.

在线性模型中，独立的特征方向数可以直接用矩阵的秩表达；若列之间冗余，参数个数就已经不等于独立方向数。推广到更一般的函数族后，复杂度还受参数约束、函数结构等因素影响，不能只数有多少个参数。

<a id="section-10"></a>

## High Dimensional Interlude Some surprising fact

**高维插曲：一个令人意外的事实**

![image](<../Images/02_LM/image_003.jpg>)

99%

99%


- Ratio shell/volume:

  外壳与总体积之比：

$$
\frac {v o l (B _ {d} (0 , 1) - B _ {d} (0 , 1 - \varepsilon))}{v o l (B _ {d} (0 , 1))} = 1 - (1 - \varepsilon) ^ {d} \rightarrow 1 \text{当} d \rightarrow \infty
$$

### High level position paper:

**综述性观点文章**

”High Dimensional Data Analysis : The Curses and Blessings of Dimensionality” by D. Donoho (2000)

D. Donoho（2000），High Dimensional Data Analysis: The Curses and Blessings of Dimensionality（高维数据分析：维度的诅咒与馈赠）。

### Maths book:

**数学著作**

”High-Dimensional Probability” by Roman Vershynin (2018)

Roman Vershynin（2018），High-Dimensional Probability（高维概率）。

<a id="reading-orange-shell"></a>

### How much volume does an equally thin orange peel occupy in high dimensions?

**同样厚度的“橘子皮”，在高维里占多少体积**

Set the radius to $1$ and shell thickness to $\varepsilon=0.005$, leaving inner radius $0.995$. Scaling a radius by $0.995$ scales $d$-dimensional volume by $0.995^d$. The following calculation therefore needs no explicit constant for the unit ball's volume:

把半径设为 $1$，外壳厚度设为 $\varepsilon=0.005$，内球半径就是 $0.995$。半径缩小到原来的 $0.995$ 倍，$d$ 维体积会缩小到原来的 $0.995^d$ 倍。因此不必知道单位球体积的具体常数，也能算出：

| Dimension<br>维度 | Shell fraction $1-0.995^d$<br>外壳所占比例 $1-0.995^d$ |
|---|---:|
| $d=2$ | Approximately $1.00\%$<br>约 $1.00\%$ |
| $d=3$ | Approximately $1.49\%$<br>约 $1.49\%$ |
| $d=1000$ | Approximately $99.33\%$<br>约 $99.33\%$ |

Under sampling uniform by volume within the ball, the probability of falling in the shell equals this ratio. A thin high-dimensional shell can contain most samples, so intuition from two- and three-dimensional pictures needs reassessment. This calculation describes ball volume and uniform sampling. Real data can instead concentrate near lower-dimensional structures; their distribution must be determined by the problem.

若从球内按体积均匀采样，落进外壳的概率就等于这个比例。高维中的薄外壳可以容纳绝大多数样本，二维、三维画图形成的直觉因此需要重新检查。这个计算描述的是球的体积和相应均匀采样；真实数据也可能集中在低维结构上，其分布仍要由具体问题决定。

<a id="section-11"></a>

## From classical statistics to Machine Learning: Handling high dimensions

**从经典统计到机器学习：处理高维问题**

A. Sparsity and linear models

A. 稀疏性与线性模型。

B. Estimating nonlinear functions

B. 估计非线性函数。

C. Generalizations

C. 推广。

<a id="section-12"></a>

## What ’high’ means for linear regression

**对线性回归而言，“高维”意味着什么**


- So far, we assumed: $n \geq d$ and $( \pmb { \mathsf { X } } ) = d$

  到目前为止，假设 $n \geq d$ 且 $( \pmb { \mathsf { X } } ) = d$。

- If d gets large, two things may/will happen:

  当 d 增大时，可能或将会出现两种情况：

- Instability in computing the inverse $( { \pmb X } ^ { T } { \pmb X } ) ^ { - 1 }$

  计算逆矩阵 $( { \pmb X } ^ { T } { \pmb X } ) ^ { - 1 }$ 时不稳定。

- Rank-deficiency of data matrix X

  数据矩阵 X 秩亏。

- Rank-defficient case (but still $n \geq d )$

  秩亏情形（但仍有 $n \geq d )$）：

- There are many solutions to the LS problem...

  最小二乘问题存在多个解……

- Get one LSE by using Moore-Penrose pseudo-inverse instead of $( { \pmb X } ^ { T } { \pmb X } ) ^ { - 1 }$ in the projection matrix

  在投影矩阵中使用 Moore–Penrose 伪逆来代替 $( { \pmb X } ^ { T } { \pmb X } ) ^ { - 1 }$，可得到一个最小二乘估计。

- The LSE is the solution with minimal $\ell _ { 2 } { \mathrm { - } } \mathsf { n o r m }$

  这个最小二乘估计是使 $\ell _ { 2 } { \mathrm { - } } \mathsf { n o r m }$ 最小的解。

- Cure to instability: (ridge) regularization...

  对不稳定性的补救：使用（岭）正则化……

<a id="reading-rank-and-stability"></a>

### Nonunique solutions and sensitivity to perturbations

**解不唯一，与解对扰动敏感**

First consider two identical columns:

先看两列完全重复的例子：

$$
\mathbf X=\begin{pmatrix}1&1\\2&2\end{pmatrix},
\qquad
\mathbf Y=\begin{pmatrix}2\\4\end{pmatrix}.
$$

Any coefficients satisfying $\beta_1+\beta_2=2$ fit perfectly: $(2,0)$, $(1,1)$, and $(0,2)$ are all solutions. Observations identify only their sum, not their separate contributions. The pseudoinverse selects the minimum-norm solution $(1,1)$, providing a definite choice without recovering information absent from the data. Although coefficients are nonunique, the optimal prediction vector at training inputs is still the unique orthogonal projection.

任何满足 $\beta_1+\beta_2=2$ 的系数都能完全拟合数据，$(2,0)$、$(1,1)$、$(0,2)$ 都是解。观测只能识别两个系数的和，无法区分各自的贡献。伪逆选出的最小范数解是 $(1,1)$；它给出一种确定的选择，却不会凭空恢复数据中没有的信息。虽然系数不唯一，训练点上的最优预测向量仍是唯一的正交投影。

Now consider an invertible but sensitive example:

再看一个仍然可逆、但很敏感的例子：

$$
\mathbf X=\begin{pmatrix}1&1\\1&1.01\end{pmatrix}.
$$

Responses $(2,2.01)^T$ yield $(1,1)^T$. Increasing only the second response by $0.01$, to $(2,2.02)^T$, changes the solution to $(0,2)^T$. The columns are so similar that their contributions are difficult to distinguish reliably, allowing a small observational change to produce a large coefficient change.

响应 $(2,2.01)^T$ 对应解 $(1,1)^T$；只把第二个响应增加 $0.01$，改成 $(2,2.02)^T$，解就变成 $(0,2)^T$。两列非常接近，数据很难可靠地区分它们，于是很小的观测变化就能引起很大的系数变化。

When $d>n$, $\operatorname{rank}(\mathbf X)\leq n<d$, so full column rank is impossible. Even when $d\leq n$, duplicate or nearly duplicate columns can cause these problems. Practical least-squares calculations generally solve the relevant linear system using factorizations such as QR or SVD; the explicit inverse mainly supports derivation.

当 $d>n$ 时，$\operatorname{rank}(\mathbf X)\leq n<d$，列满秩必然不成立；当 $d\leq n$ 时，也可能因为重复或近似重复的列出现上述问题。实际计算最小二乘通常求解相应线性系统，采用 QR 或 SVD 等分解；显式写出的逆矩阵主要帮助推导。

---

[本课目录](../02_LM_zh.md) · [上一篇：线性模型与最小二乘](01_linear_models_and_least_squares.md) · [下一篇：稀疏性与模型选择](03_sparsity_and_model_selection.md)
