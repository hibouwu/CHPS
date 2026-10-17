# 5. 线性模型：从拟合到预测误差

[本课目录](../01_intro_zh.md) · [上一篇：学习对象与偏差—方差分解](04_hypotheses_and_bias_variance.md) · [下一篇：经验风险、真实风险与损失](06_empirical_and_true_risk.md)

<a id="linear-models"></a>

### The case of linear models

**线性模型的情形**

<a id="classroom-linear-roadmap"></a>

**How to read the following linear-model calculations**

**怎样读接下来的线性模型计算**

Linear regression is a useful next subject because parameters, predictions, and errors can all be expressed as explicit vector and matrix operations, making the earlier abstract tradeoff easier to inspect. First distinguish n, the sample count, from d, the number of features per input. The design matrix collects inputs, the response vector collects labels, training estimates parameters, and substituting a new input into those parameters produces a prediction.

线性回归适合作为下一步研究的对象，因为参数、预测和误差都能写成明确的向量与矩阵运算，便于检查前面抽象的权衡。读这部分时先分清：n 是样本数，d 是每个输入的特征数；设计矩阵收集输入，响应向量收集标签，训练估计参数，再把参数代入一个新输入产生预测。

Convenient linear algebra does not remove assumptions. A matrix inverse requires the appropriate rank condition, for example, and fixed-design and random-design expectations average over different objects.

不必把“线性代数容易计算”理解为条件可以省略：例如逆矩阵要求相应的秩条件，固定设计与随机设计的期望对象也不同。

*来源：[转录 3](../01_part3.md) 第 452–458 行。*

<a id="reading-linear-example"></a>

**Fitting a line to three samples**

**从三个样本算出一条直线**

Begin with a regression problem having one numerical feature t. We observe three samples and want a line $h(t)=\theta_0+\theta_1t$ to predict the response:

先看只有一个数值特征 t 的回归问题。我们测得三个样本，希望用直线 $h(t)=\theta_0+\theta_1t$ 预测响应：

| Sample i<br>样本 i | Feature $t_i$<br>特征 $t_i$ | Observed response $y_i$<br>观测响应 $y_i$ |
|---|---:|---:|
| 1 | −1 | 1 |
| 2 | 0 | 1 |
| 3 | 1 | 4 |

Include the intercept in the parameter vector by setting $x_i=(1,t_i)^T$ and $\theta=(\theta_0,\theta_1)^T$; one prediction then becomes $x_i^T\theta$. Stack the three inputs as rows to obtain

把截距也放进参数向量，令 $x_i=(1,t_i)^T$、$\theta=(\theta_0,\theta_1)^T$，单个预测就能写成 $x_i^T\theta$。将三个输入逐行排好，得到

$$
\mathbf X=\begin{pmatrix}1&-1\\1&0\\1&1\end{pmatrix},\qquad
\mathbf y=\begin{pmatrix}1\\1\\4\end{pmatrix},\qquad
\mathbf X\theta=\begin{pmatrix}\theta_0-\theta_1\\\theta_0\\\theta_0+\theta_1\end{pmatrix}.
$$

Here n=3 and d=2: three samples and two input columns, one constantly equal to 1 to represent the intercept. **Matrix multiplication simply computes all sample predictions at once.** Observed values minus predictions form the residual vector $\mathbf y-\mathbf X\theta$. Least squares chooses parameters minimizing its sum of squares.

这里 n=3、d=2：三个样本，两列输入，其中一列恒为 1，用于表示截距。**矩阵乘法只是一次算出所有样本的预测值。** 观测与预测的差组成残差向量 $\mathbf y-\mathbf X\theta$，最小二乘选择使其平方和最小的参数。

The calculation gives $\widehat\theta=(2,1.5)^T$, so the prediction rule is $\widehat h(t)=2+1.5t$. Predictions at the three training points are 0.5, 2, and 3.5, with residuals 0.5, −1, and 0.5. Substituting the new input t=2 into the learned parameters gives a prediction of 5.

计算得到 $\widehat\theta=(2,1.5)^T$，所以预测规则是 $\widehat h(t)=2+1.5t$。三个训练点的预测分别为 0.5、2、3.5，与观测值之间的残差为 0.5、−1、0.5。对于新的输入 t=2，代入已学到的参数就得到预测值 5。

<details>
<summary>Calculation: where the parameters 2 and 1.5 come from<br>计算：参数 2 和 1.5 是怎样得到的</summary>

Differentiate the residual sum of squares with respect to the parameters. The first-order condition gives the normal equations

将残差平方和对参数求导，一阶条件给出正规方程

$$
\mathbf X^T\mathbf X\widehat\theta=\mathbf X^T\mathbf y.
$$

In this example,

在这个例子中，

$$
\mathbf X^T\mathbf X=\begin{pmatrix}3&0\\0&2\end{pmatrix},\qquad
\mathbf X^T\mathbf y=\begin{pmatrix}6\\3\end{pmatrix}.
$$

The two equations are therefore $3\widehat\theta_0=6$ and $2\widehat\theta_1=3$, giving 2 and 1.5. This is the inverse-matrix formula below: the two input columns are linearly independent, so $\mathbf X^T\mathbf X$ is invertible. The residual sum of squares is $0.5^2+(-1)^2+0.5^2=1.5$; dividing by the sample count gives training MSE 0.5.

所以两个方程分别是 $3\widehat\theta_0=6$ 与 $2\widehat\theta_1=3$，解为 2 和 1.5。这也就是下面的逆矩阵公式；两列输入线性独立，因而 $\mathbf X^T\mathbf X$ 可逆。残差平方和为 $0.5^2+(-1)^2+0.5^2=1.5$，除以样本数得到训练均方误差 0.5。

</details>

Next express this process for general n samples and d input components. To discuss errors, distinguish the true parameter, the parameter estimated from data, and observation noise.

下面把这一过程写成一般的 n 个样本、d 个输入分量的形式。为了讨论误差，还要进一步区分真实参数、由数据估计的参数，以及观测中的噪声。


- True model : $h ^ { \ast } ( x ) = x ^ { T } \theta ^ { \ast }$ ,for some $\theta ^ { * } \in \mathbb { R } ^ { d }$

  真实模型：$h ^ { \ast } ( x ) = x ^ { T } \theta ^ { \ast }$，其中 $\theta ^ { * } \in \mathbb { R } ^ { d }$。

- Linear models : $h ( x ) = x ^ { T } \theta$ , where $\boldsymbol { \theta } \in \mathbb { R } ^ { d }$

  线性模型：$h ( x ) = x ^ { T } \theta$，其中 $\boldsymbol { \theta } \in \mathbb { R } ^ { d }$。

- Matrix/vector notations : $\mathsf { X } \in \mathbb { R } ^ { n \times d } , \mathsf { Y } \in \mathbb { R } ^ { d } , \varepsilon \in \mathbb { R } ^ { n }$

  矩阵／向量记号：$\mathsf { X } \in \mathbb { R } ^ { n \times d } , \mathsf { Y } \in \mathbb { R } ^ { d } , \varepsilon \in \mathbb { R } ^ { n }$。

> **Note:** The slide places $\mathbf Y$ in $\mathbb R^d$. A response vector consistent with $\mathbf X\in\mathbb R^{n\times d}$ must instead belong to $\mathbb R^n$.

> **译注：** 原页把 $\mathbf Y$ 写为 $\mathbb R^d$ 中的向量；与 $\mathbf X\in\mathbb R^{n\times d}$ 一致的响应向量应属于 $\mathbb R^n$。


- Assumption : X is of full rank

  假设：X 满秩。

- MLE : $\widehat { \theta } _ { n } ^ { \mathrm { M L E } } = ( \mathsf { X } ^ { T } \mathsf { X } ) ^ { - 1 } \mathsf { X } ^ { T } \mathsf { Y }$

  最大似然估计：$\widehat { \theta } _ { n } ^ { \mathrm { M L E } } = ( \mathsf { X } ^ { T } \mathsf { X } ) ^ { - 1 } \mathsf { X } ^ { T } \mathsf { Y }$。

- Plugin predictor : $\widehat { h } _ { n } ( x ) = x ^ { T } \widehat { \theta } _ { n } ^ { \mathrm { M L E } }$

  代入式预测器：$\widehat { h } _ { n } ( x ) = x ^ { T } \widehat { \theta } _ { n } ^ { \mathrm { M L E } }$。

- Computations : for fixed (x, y)

  计算：对固定的 (x,y)。

- Bias term : $x ^ { T } \mathbb { E } _ { n } ( \widehat { \theta } _ { n } ^ { \mathrm { M L E } } - \theta ^ { * } ) = 0$

  偏差项：$x ^ { T } \mathbb { E } _ { n } ( \widehat { \theta } _ { n } ^ { \mathrm { M L E } } - \theta ^ { * } ) = 0$。

- Variance term : $\mathbb { E } _ { n } \left( ( x ^ { T } ( \mathsf { X } ^ { T } \mathsf { X } ) ^ { - 1 } \mathsf { X } ^ { T } \varepsilon ) ^ { 2 } \right)$

  方差项：$\mathbb { E } _ { n } \left( ( x ^ { T } ( \mathsf { X } ^ { T } \mathsf { X } ) ^ { - 1 } \mathsf { X } ^ { T } \varepsilon ) ^ { 2 } \right)$。

What theory says : By Gauss-Markov theorem, MLE is the lowest variance unbiased estimator... but not necessarily the one with minimal MSE.

理论结论：根据 Gauss–Markov 定理，最大似然估计是方差最小的无偏估计量……但未必是均方误差最小的估计量。

> **Note:** The Gauss–Markov minimum-variance conclusion applies within the class of linear unbiased estimators. Identifying least squares with maximum likelihood additionally requires conditions such as Gaussian errors.

> **译注：** Gauss–Markov 定理的最小方差结论限定在线性无偏估计量中；最小二乘与最大似然的对应还需要高斯误差等条件。

<a id="reading-noise-propagation"></a>

**How changes in observations reach parameters and predictions**

**观测中的变化怎样传到参数和预测中**

Use the same three inputs. If the second response changes from 1 to $1+\Delta$ while the other observations stay fixed, the first component of $\mathbf X^T\mathbf y$ increases by $\Delta$ and the second remains unchanged. The intercept therefore increases by $\Delta/3$, the slope stays fixed, and the entire prediction line shifts upward by $\Delta/3$. Parameters and predictions depend on observed values; data carrying different noise produce a different fit.

仍用上面的三个输入。如果第二个响应由 1 变成 $1+\Delta$，而其余观测不变，则 $\mathbf X^T\mathbf y$ 的第一个分量增加 $\Delta$，第二个分量保持不变。因此截距增加 $\Delta/3$，斜率不变，整条预测直线上移 $\Delta/3$。这说明参数和预测都依赖观测值，换一组带有不同噪声的数据就会得到不同的拟合结果。

In the general model $\mathbf Y=\mathbf X\theta^*+\varepsilon$, separate the true linear relation from noise and substitute into the least-squares formula to obtain

在一般模型 $\mathbf Y=\mathbf X\theta^*+\varepsilon$ 中，把观测分成真实线性关系与噪声，再代入最小二乘公式，便得到

$$
\widehat\theta-\theta^*=(\mathbf X^T\mathbf X)^{-1}\mathbf X^T\varepsilon,\qquad
x^T\widehat\theta-x^T\theta^*
=x^T(\mathbf X^T\mathbf X)^{-1}\mathbf X^T\varepsilon.
$$

The first identity describes parameter error; the second describes prediction error at a fixed input x. The variance calculation below measures how much fluctuation remains after the noise passes through these matrix operations.

第一式描述参数误差，第二式描述固定输入 x 处的预测误差。接下来的方差计算，就是衡量右边的噪声经过这些矩阵运算后还剩多少波动。

<details>
<summary>Derivation: why fixed-input prediction variance involves an inverse matrix<br>推导：固定输入时，预测方差为什么含有逆矩阵</summary>

Fix a full-column-rank design matrix $\mathbf X$ and assume mean-zero noise with covariance $\sigma^2I$. Set $A=(\mathbf X^T\mathbf X)^{-1}\mathbf X^T$; the parameter error is $A\varepsilon$, with covariance

固定满列秩的设计矩阵 $\mathbf X$，假设噪声均值为零、协方差为 $\sigma^2I$。令 $A=(\mathbf X^T\mathbf X)^{-1}\mathbf X^T$，则参数误差为 $A\varepsilon$，其协方差为

$$
\operatorname{Cov}(\widehat\theta\mid\mathbf X)
=A(\sigma^2I)A^T
=\sigma^2(\mathbf X^T\mathbf X)^{-1}.
$$

Consequently, the variance of the estimated mean response at fixed x is

因此，固定 x 处估计出的平均响应的方差为

$$
\operatorname{Var}(x^T\widehat\theta\mid\mathbf X)
=\sigma^2x^T(\mathbf X^T\mathbf X)^{-1}x.
$$

For the three samples above, $x=(1,t)^T$, which gives $\sigma^2(1/3+t^2/2)$. At t=0 the variance is $\sigma^2/3$, and at t=2 it is $7\sigma^2/3$. Predictions based on the same parameter estimates need not be equally stable at different inputs. This is the variance of the estimated mean response. Predicting an independent new observation also requires adding that observation's noise variance.

对上面的三个样本，$x=(1,t)^T$，代入得到 $\sigma^2(1/3+t^2/2)$。在 t=0 处是 $\sigma^2/3$，在 t=2 处是 $7\sigma^2/3$；同一组参数在不同输入位置上的预测稳定性并不相同。这里计算的是估计平均响应的方差，若预测独立的新观测，还需加上新观测本身的噪声方差。

</details>

<a id="variance-computation"></a>


- Assumption : $\varepsilon \sim \mathcal { N } _ { n } ( 0 , \sigma ^ { 2 } I _ { n } )$ n-dimensional multivariate gaussian

  假设：$\varepsilon \sim \mathcal { N } _ { n } ( 0 , \sigma ^ { 2 } I _ { n } )$，即 n 维多元高斯分布。

- Variance term : for any x

  方差项：对任意 x，

$$
\begin{array}{r l} \mathbb {E} _ {y | x} \mathbb {V} _ {n} (x ^ {T} \widehat {\theta} _ {n}) & = \mathbb {E} _ {y | x} \mathbb {E} _ {n} ((x ^ {T} (\mathsf {X} ^ {T} \mathsf {X}) ^ {- 1} \mathsf {X} ^ {T} \boldsymbol {\varepsilon}) ^ {2}) \\ & = x ^ {T} \mathbb {E} _ {n} ((\mathsf {X} ^ {T} \mathsf {X}) ^ {- 1} \mathsf {X} ^ {T} \mathbb {E} _ {y | x} (\boldsymbol {\varepsilon} \boldsymbol {\varepsilon} ^ {T}) \mathsf {X} ((\mathsf {X} ^ {T} \mathsf {X}) ^ {- 1}) ^ {T} x) \\ & = \sigma^ {2} x ^ {T} \mathbb {E} _ {n} ((\mathsf {X} ^ {T} \mathsf {X}) ^ {- 1}) x \end{array}
$$


- Assumption : random design $x , x _ { i } \sim \mathcal { N } ( 0 , 1 )$ IID

  假设：随机设计 $x , x _ { i } \sim \mathcal { N } ( 0 , 1 )$，独立同分布。

$$
\mathbb E_x\mathbb E_{y\mid x}\mathbb V_n(x^T\widehat\theta_n)=\sigma^2\frac dn.
$$

> **Note:** The slide mixes different prediction risks here. For estimating mean responses at fixed training inputs, the variance contribution is $\sigma^2d/n$. If training rows and an independent new input both follow $\mathcal N_d(0,I_d)$, no separate intercept is added, and $n>d+1$, the expected OLS variance at the new input is $\sigma^2d/(n-d-1)$.

> **译注：** 原页此处把不同预测风险混在一起。固定设计的训练点均值预测风险中，方差项为 $\sigma^2d/n$；若训练行与独立新输入均服从 $\mathcal N_d(0,I_d)$、不另加截距且 $n>d+1$，新输入上的 OLS 方差期望为 $\sigma^2d/(n-d-1)$。

General argument relies on Cochran’s theorem (gaussian case).

一般论证依赖 Cochran 定理（高斯情形）。

<a id="projection"></a>

### Explanation of the $d / n$ term

**$d / n$ 项的解释**

Property on the norm of projections of gaussian random vectors :

高斯随机向量投影的范数性质：


- Assume $\textsf { Z }$ is a gaussian random vector $ { \mathcal { N } } _ { n } ( 0 , I _ { n } )$ in $\mathbb { R } ^ { n }$ , $\mathcal { H }$ is a linear subspace of $\mathbb { R } ^ { n }$ and $\Pi : \mathbb { R } ^ { n }  \mathbb { R } ^ { n }$ a linear projection onto $\mathcal { H }$

  假设 $\textsf { Z }$ 是 $\mathbb { R } ^ { n }$ 中服从 $ { \mathcal { N } } _ { n } ( 0 , I _ { n } )$ 的高斯随机向量，$\mathcal { H }$ 是 $\mathbb { R } ^ { n }$ 的线性子空间，$\Pi : \mathbb { R } ^ { n }  \mathbb { R } ^ { n }$ 是到 $\mathcal { H }$ 的线性投影。

- Then : the random vector $\Pi _ { \mathcal { H } } Z$ has gaussian distribution $\mathcal { N } _ { n } ( 0 , \Pi )$ on $\mathbb { R } ^ { n }$ (linear transformation of a gaussian is a gaussian)

  则随机向量 $\Pi _ { \mathcal { H } } Z$ 在 $\mathbb { R } ^ { n }$ 上服从高斯分布 $\mathcal { N } _ { n } ( 0 , \Pi )$（高斯随机向量的线性变换仍为高斯随机向量）。

- Furthermore : $\| \Pi Z \| ^ { 2 }$ follows a chi-square distribution with

  此外，$\| \Pi Z \| ^ { 2 }$ 服从卡方分布，并且

$$
\mathbb {E} (\| \Pi Z \| ^ {2}) = \dim (\mathcal {H})
$$

> **Note:** These distributional and expectation results require an orthogonal projection, not just an arbitrary linear projection.

> **译注：** 这组分布与期望结论要求正交投影，不能仅假设任意线性投影。

<a id="reading-projection"></a>

**Why projection produces d/n**

**投影为什么会带来 d/n**

With a fixed design matrix, all fitted vectors of the form $\mathbf X\theta$ lie in a subspace of $\mathbb R^n$, of dimension d under full column rank. Least squares projects the observation vector into this subspace, projecting its noise as well. If noise has variance $\sigma^2$ in each orthogonal direction, the d retained directions contribute expected squared error $d\sigma^2$. Averaging over n training locations gives $\sigma^2d/n$.

固定设计矩阵时，所有形如 $\mathbf X\theta$ 的拟合值都位于 $\mathbb R^n$ 中的一个子空间，其维数在满列秩条件下为 d。最小二乘把观测向量投影到这个子空间；其中的噪声也被一同投影。若噪声在每个正交方向上的方差都是 $\sigma^2$，保留下来的 d 个方向合计贡献 $d\sigma^2$ 的期望平方误差，再按 n 个训练位置平均，就得到 $\sigma^2d/n$。

This makes the earlier tradeoff concrete: more fitted directions permit richer variation but also retain more noise fluctuations. The comparison concerns estimated mean responses at the training inputs. Risk at new inputs must additionally account for their positions and distribution.

这把前面的抽象权衡变成了一个具体量：可拟合的方向越多，能够表示的变化越丰富，也会保留更多噪声波动。这里比较的是训练输入位置处的平均响应估计误差，计算新输入上的风险时还要考虑新输入的位置与分布。

<a id="beyond-linear"></a>

### From gaussian linear regression to ML

**从高斯线性回归到机器学习**


- What if d larger than n ?

  如果 d 大于 n，会怎样？

- What replaces the dimension d in nonlinear models ?

  在线性以外的模型中，什么量替代维度 d？

- Other tasks than regression ?

  回归以外的其他任务呢？

---

[本课目录](../01_intro_zh.md) · [上一篇：学习对象与偏差—方差分解](04_hypotheses_and_bias_variance.md) · [下一篇：经验风险、真实风险与损失](06_empirical_and_true_risk.md)
