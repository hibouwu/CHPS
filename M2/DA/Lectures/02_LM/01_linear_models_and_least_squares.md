# 1. 线性模型与最小二乘

[本课目录](../02_LM_zh.md) · [下一篇：泛化与高维问题](02_generalization_and_high_dimensions.md)

[Data & Apprentissage] Introduction à la science des données et à l’apprentissage

**数据科学与机器学习导论**

Nicolas Vayatis

<a id="section-01"></a>

## Modèles linéaires et parcimonie

**线性模型与稀疏性**

<a id="reading-model-and-learning"></a>

### Learning a predictor from a family of functions

**从一族函数中学出一个预测器**

Given labeled data, a learning algorithm selects a function to predict new samples. Model has two common meanings here. During modeling, it denotes an allowed family, such as all functions $h(t)=a+bt$; after training, it often denotes the particular function with estimated parameters, such as $\widehat h(t)=2+1.5t$. The former specifies how patterns may be represented; the latter is the particular result supplied by these data.

给定一组带标签的数据，学习算法要选出一个能预测新样本的函数。这里“模型”有两个常见含义：建模时，它指允许选择的函数族，例如所有 $h(t)=a+bt$；训练完成后，它也常指已经选定参数的那个函数，例如 $\widehat h(t)=2+1.5t$。前者规定可以怎样表达规律，后者是这次数据给出的具体结果。

This lecture follows three questions: how to fit data within a chosen function family, how to limit solution complexity when there are many variables, and how to retain linear-model solution methods while expressing nonlinear relationships. Loss measures prediction–target discrepancies, penalties express desired solution properties, and training combines both to optimize parameters.

本讲沿着三个问题展开：怎样在选定的函数族中拟合数据；变量很多时，怎样限制解的复杂度；怎样保留线性模型的求解方法，同时表达非线性关系。损失函数衡量预测与目标的差异，惩罚项表达希望解具有的性质，训练则把这两方面合在一起求最优参数。

<details>
<summary>Further detail: how data contribute when labels arrive gradually<br>延伸：标签逐渐到来时，数据怎样参与学习</summary>

Historical data may initially contain only inputs, with labels arriving later. Customer information can be recorded at application time while actual repayment outcomes emerge later; images can likewise be collected before receiving annotations. Available labels guide prediction and unlabeled data provide input-distribution information, together forming a semi-supervised setting.

一批历史数据可能只有输入，后来收集的数据则逐渐有了标签。例如，申请时能记录客户资料，实际还款结果要过一段时间才出现；图像也可以先收集，再陆续获得人工标注。已有标签帮助确定预测方向，无标签数据提供输入分布的信息，两者结合便形成半监督学习的情形。

Unlabeled points reveal regions where data concentrate and regions with few samples. Whether this improves classification also depends on the relation between that structure and labels. New feedback can update a predictor after deployment. If interests or the environment change, old and new data may differ in relevance, motivating time windows or reduced weight on older data.

无标签点能帮助看出数据集中在哪些区域、哪些区域几乎没有样本；能否据此改进分类，还取决于这些分布结构与标签之间的关系。系统运行一段时间后，可以用新增反馈更新预测器。若用户兴趣或环境发生变化，旧数据和新数据的参考价值也可能不同，此时还需要考虑时间窗口或对旧数据降低权重。

Similarity methods find historical samples close to a new one. The linear methods emphasized here fit parameters through an overall objective. Both must specify what close or good prediction means. Describing people using a few categories versus predicting from richer individual histories likewise reflects different representation choices.

相似性方法会寻找与新样本接近的历史样本；本讲主要讨论的线性方法，则通过一个整体目标函数拟合参数。它们都需要说明什么叫“接近”或“预测得好”。把人群只用少数类别描述，与利用较丰富的个人历史进行预测，也对应不同的表示选择。

</details>

<details>
<summary>Further detail: statistical models and prediction models<br>延伸：统计模型与预测模型的关系</summary>

A statistical model is often a family of probability distributions, such as Gaussians with unknown means and variances. Estimating parameters describes the data distribution. A prediction task can instead select a decision function without first estimating the complete joint distribution. Squared-loss regression needs the conditional mean, for example, while binary decisions can compare class probabilities.

统计模型常写成一族概率分布，例如均值和方差未知的高斯分布族；估计参数以后，就得到关于数据分布的描述。预测任务也可以直接选择决策函数，而不先估计完整的联合分布。例如，平方损失回归需要条件均值，二分类决策可以围绕类别概率的比较展开。

A full distribution often requires more information. An unrestricted $d$-dimensional Gaussian has $d+d(d+1)/2$ free parameters in its mean and symmetric covariance alone. Direct prediction permits more task-specific assumptions; it does not guarantee that every prediction model has fewer parameters than a probability model.

完整分布往往需要更多信息：一个不加结构限制的 $d$ 维高斯分布，仅均值和对称协方差就包含 $d+d(d+1)/2$ 个自由参数。直接预测允许围绕任务选择较具体的假设；它并不保证所有预测模型都比概率模型参数更少。

Optimization objectives can also be defined without human labels. Given a density family $p_\theta$, for example, one can minimize $-\sum_i\log p_\theta(X_i)$. Whether labels are available and whether learning uses optimization are separate questions.

没有人工标签也可以定义优化目标。例如，给定密度族 $p_\theta$，可以最小化 $-\sum_i\log p_\theta(X_i)$。因此，“是否有标签”和“是否通过优化学习”是两个不同的问题。

</details>

<a id="section-02"></a>

## Supervised Machine Learning The bias-variance decomposition in Machine Learning

**监督机器学习：机器学习中的偏差—方差分解**

### General setup Notations

**一般设定与记号**


- Goal of learning: an optimal decision function $h^*:\mathcal X\to\mathcal Y$. $\mathcal X$: domain set, $\mathcal Y$: label set.

  学习目标：最优决策函数 $h^*:\mathcal X\to\mathcal Y$。$\mathcal X$ 是输入定义域，$\mathcal Y$ 是标签集合。

- Input of learning:

  学习的输入：

- Training data: a set of labeled data

  训练数据：一组带标签的数据

$$
D _ {n} = \{(X _ {1}, Y _ {1}), \dots , (X _ {n}, Y _ {n}) \}
$$

of size n, where the $(X,Y)$ pairs are in $\mathcal X\times\mathcal Y$

其大小为 n，其中各观测对 $(X,Y)$ 属于 $\mathcal X\times\mathcal Y$。


- Hypothesis space: a collection $\mathcal H$ of candidate decision functions $h:\mathcal X\to\mathcal Y$

  假设空间：候选决策函数 $h:\mathcal X\to\mathcal Y$ 的集合 $\mathcal H$。

- Output of learning: an empirical decision function $\widehat { h }$ in the hypothesis space $\mathcal { H }$ estimated from training data $D _ { n }$

  学习的输出：利用训练数据 $D _ { n }$ 估计得到、位于假设空间 $\mathcal { H }$ 中的经验决策函数 $\widehat { h }$。

- Reference in $\mathcal { H } \mathrm { : }$ : the best decision function $\bar { h }$ in the class (the more data, the closer $\widehat { h }$ to $\bar { h } )$

  $\mathcal { H } \mathrm { : }$ 中的参照：该类中的最佳决策函数 $\bar { h }$（数据越多，$\widehat { h }$ 越接近 $\bar { h } )$）。

### The key trade-off in Machine Learning

**机器学习中的关键权衡**

<a id="reading-three-functions"></a>

$h^*$ is the population-optimal function under the chosen loss; $\bar h$ is the best achievable after restriction to $\mathcal H$; and $\widehat h$ is obtained from this training dataset. Here $L(h)$ averages loss on future samples. Even when training error is computable, the true $L(h)$ is generally unknown because the future-data distribution is unknown.

$h^*$ 是按选定损失衡量的总体最优函数，$\bar h$ 是限制在 $\mathcal H$ 后能达到的最佳函数，$\widehat h$ 是用这一次训练数据得到的函数。这里的 $L(h)$ 对未来样本的损失取平均；即使能算出训练误差，也通常不知道真实的 $L(h)$，因为未来数据的分布未知。

All lines $a+bt$ form an infinite set, but they can still represent only straight lines. If the target relationship is a parabola, more data cannot make that family itself become parabolic: this is approximation error. Finite data can make the fitted result differ from the best line in the class: this is estimation error. The following identity separates these gaps. Optimality is relative to the loss and candidate set; unpredictable noise can leave even the optimal function with nonzero error. Existence of the relevant optimal functions is assumed here.

所有直线 $a+bt$ 构成一个无限集合，却仍然只能画出直线。如果目标关系是一条抛物线，再多数据也不能让这个函数族本身变成抛物线。这对应近似误差；有限样本使拟合结果偏离类内最佳直线，则对应估计误差。下面的等式把这两种差距分开。“最优”以损失和候选范围为准；目标中存在不可预测的噪声时，最优函数也有非零误差。此处假定相应最优函数存在。


- Denote by $L ( h )$ the error measure for any decision function h

  对任意决策函数 h，用 $L ( h )$ 表示其误差度量。

- We have: $L ( \bar { h } ) = \operatorname* { i n f } _ { \mathcal { H } } L$ , and $L ( h ^ { * } ) = \mathsf { i n f } L$

  有 $L ( \bar { h } ) = \operatorname* { i n f } _ { \mathcal { H } } L$，以及 $L ( h ^ { * } ) = \mathsf { i n f } L$。

- Bias-Variance type decomposition of error for any output $\widehat { h }$ :

  对任意输出 $\widehat { h }$，误差具有如下偏差—方差类型的分解：

$$
L (\widehat {h}) - L (h ^ {*}) = \underbrace {L (\widehat {h}) - L (\bar {h})} _ {\text{估计误差（随机）}} + \underbrace {L (\bar {h}) - L (h ^ {*})} _ {\text{近似误差（确定性）}}
$$

Hypothesis class H

假设类 H

![image](<../Images/02_LM/image_001.jpg>)

### About approximation error

**关于近似误差**

Cybenko (1989) - Denseness result in the spirit of Stone-Weierstrass showing that any linear combination of compositions of sigmoid with linear functions is dense wrt the supremum norm in the space of continuous functions over the d-dimensional unit cube.

Cybenko（1989）：一个具有 Stone–Weierstrass 风格的稠密性结果，表明 sigmoid 与线性函数复合后所得函数的线性组合，在 d 维单位立方体上的连续函数空间中，关于上确界范数稠密。


- Barron (1994) - Approximation error bound involves a parameter quantifying the smoothness of the target function.

  Barron（1994）：近似误差界包含一个刻画目标函数光滑程度的参数。

- Status of this question in the regression setup:

  回归设定下这一问题的研究状况：

  - For kernel machines: a full theory is available thanks to Smale (2003), Steinwart (2008).

    对核方法：Smale（2003）、Steinwart（2008）的工作提供了完整理论。

  - For deep learning: recent work by Grohs, Perekrestenko, Elbrächter, and Bölcskei (2019) .

    对深度学习：Grohs、Perekrestenko、Elbrächter 和 Bölcskei（2019）的近期工作。

- In the classification setup, tough problem, still open issue...

  在分类设定下，这是一个困难的问题，仍有待解决……

<a id="section-03"></a>

## Reminder on linear models in statistics The regression case

**统计学线性模型回顾：回归情形**


- Goal of learning: $h^*:\mathbb R^d\to\mathbb R$

  学习目标：$h^*:\mathbb R^d\to\mathbb R$。

- Observations: IID random pairs $( X _ { i } , Y _ { i } ) \in \mathbb { R } ^ { d } \times \mathbb { R }$

  观测：独立同分布的随机变量对 $( X _ { i } , Y _ { i } ) \in \mathbb { R } ^ { d } \times \mathbb { R }$。

$$
Y _ {i} = h ^ {*} (X _ {i}) + \varepsilon_ {i}, \quad i = 1, \dots , n
$$

where $\varepsilon _ { i }$ is a random noise variable independent of $X$

其中 $\varepsilon _ { i }$ 是与 $X$ 独立的随机噪声变量。


- We shall use a vector notation as follows:

  下面使用如下向量记法：

$$
\mathbf {Y} = \mathbf {h} ^ {*} + \varepsilon
$$

where the three terms are all in $\mathbb { R } ^ { n }$

其中三项都属于 $\mathbb { R } ^ { n }$。


- Elements in $\mathbb { R } ^ { n }$ :

  $\mathbb { R } ^ { n }$ 中的元素：

$$
\mathbf {Y} = \left(Y _ {1}, \dots , Y _ {n}\right) ^ {T},
$$

$$
\varepsilon = \left(\varepsilon_ {1}, \dots , \varepsilon_ {n}\right) ^ {T}
$$


- Image vectors: for any $h \in \mathcal H$ , we use the bold characters as

  像向量：对任意 $h \in \mathcal H$，用粗体表示

$$
\mathbf {h} = \left(h (X _ {1}), \dots , h (X _ {n})\right) ^ {T}
$$


- The image of data points through elements of $\mathcal { H }$ by

  数据点经 $\mathcal { H }$ 中的函数映射后得到的像集合为

$$
\mathcal {H} (X) = \left\{\mathbf {h} = \left(h \left(X _ {1}\right), \dots , h \left(X _ {n}\right)\right) ^ {T},: h \in \mathcal {H} \right\}
$$


- Norm in $\mathbb { R } ^ { n }$ :

  $\mathbb { R } ^ { n }$ 中的范数：

$$
\forall u = \left(u _ {1}, \ldots , u _ {n}\right) ^ {T} \in \mathbb {R} ^ {n}, \| u \| ^ {2} = \sum_ {i = 1} ^ {n} u _ {i} ^ {2}
$$


- Definition of the LSE :

  最小二乘估计（LSE）的定义：

$$
\widehat {\mathbf {h}} _ {\mathbf {n}} = \underset {\mathbf {h} \in \mathcal {H} (X)} {\arg \min} \frac {1}{n} \| \mathbf {Y} - \mathbf {h} \| ^ {2}
$$

where ${ \mathcal { H } } ( X ) = \{ \boldsymbol { \mathsf { h } } = ( h ( X _ { 1 } ) , \ldots , h ( X _ { n } ) ) ^ { T } , : h \in { \mathcal { H } } \}$

其中 ${ \mathcal { H } } ( X ) = \{ \boldsymbol { \mathsf { h } } = ( h ( X _ { 1 } ) , \ldots , h ( X _ { n } ) ) ^ { T } , : h \in { \mathcal { H } } \}$。


- Assuming that the linear model is gaussian (i.e. the noise variables are IID and follow a centered gaussian distribution with fixed and known variance), then the LSE also corresponds to the Maximum Likelihood estimator.

  假设线性模型为高斯模型，即噪声变量独立同分布、服从均值为零且方差固定并已知的高斯分布，则最小二乘估计也对应最大似然估计。

- The hypothesis space $\mathcal { H }$ is the class of linear functions of rank $d$

  假设空间 $\mathcal { H }$ 是秩为 $d$ 的线性函数类。

- The noise vector $\boldsymbol { \varepsilon } = ( \varepsilon _ { 1 } , \ldots , \varepsilon _ { n } ) ^ { T }$ is a gaussian random vector in $\mathbb { R } ^ { n }$ with distribution ${ \mathcal { N } } _ { n } ( 0 , \sigma ^ { 2 } I _ { n } )$

  噪声向量 $\boldsymbol { \varepsilon } = ( \varepsilon _ { 1 } , \ldots , \varepsilon _ { n } ) ^ { T }$ 是 $\mathbb { R } ^ { n }$ 中服从分布 ${ \mathcal { N } } _ { n } ( 0 , \sigma ^ { 2 } I _ { n } )$ 的高斯随机向量。

Notations: $\boldsymbol { x } = ( \boldsymbol { x } ^ { ( 1 ) } , \ldots , \boldsymbol { x } ^ { ( d ) } ) ^ { T } \in \mathbb { R } ^ { d }$

记号：$\boldsymbol { x } = ( \boldsymbol { x } ^ { ( 1 ) } , \ldots , \boldsymbol { x } ^ { ( d ) } ) ^ { T } \in \mathbb { R } ^ { d }$。


- Linear regression: $\begin{array} { r } { h ( x ) = \sum _ { k = 1 } ^ { d } \beta _ { k } x ^ { ( k ) } } \end{array}$

  线性回归：$\begin{array} { r } { h ( x ) = \sum _ { k = 1 } ^ { d } \beta _ { k } x ^ { ( k ) } } \end{array}$。

- Basis/frame expansion (Fourier, splines, wavelets, etc.)

  基／框架展开（Fourier、样条、小波等）。

- Additive models: $h ( x ) = \sum _ { k = 1 } ^ { d } f _ { k } ( x ^ { ( k ) } )$

  加性模型：$h ( x ) = \sum _ { k = 1 } ^ { d } f _ { k } ( x ^ { ( k ) } )$。

- Piecewise constant regression (taking into account breakpoints)

  分段常数回归（考虑分段点）。



<a id="reading-linear-in-parameters"></a>

### Linear means linear in the parameters being estimated

**“线性”指对待估计参数线性**

The polynomial $h(t)=\beta_0+\beta_1t+\beta_2t^2$ is nonlinear in its input $t$, but the coefficients $\beta_0,\beta_1,\beta_2$ to be estimated appear only in a linear combination. Representing the input as $(1,t,t^2)$ therefore permits linear-regression methods. Fourier, spline, and wavelet expansions have the same form:

多项式 $h(t)=\beta_0+\beta_1t+\beta_2t^2$ 对输入 $t$ 不是线性的，但待估计系数 $\beta_0,\beta_1,\beta_2$ 都只以一次线性组合出现。把输入表示为 $(1,t,t^2)$ 后，仍然可以使用线性回归的方法。Fourier、样条和小波展开也有同样的形式：

$$
h(x)=\sum_{j=1}^{d}\beta_j\phi_j(x),
$$

The basis functions $\phi_j$ are chosen beforehand and training estimates their coefficients. If parameters inside the basis functions are learned too, one must reassess whether the model remains linear in all estimated parameters.

其中基函数 $\phi_j$ 预先选定，训练负责估计系数。若连基函数内部的参数也要一起学习，就要重新判断模型是否仍对全部待估计参数线性。

Also distinguish a function from its values at the training inputs. $h$ accepts any new input, whereas the bold vector $\mathbf h=(h(X_1),\ldots,h(X_n))^T$ records predictions only at these $n$ locations. $\mathcal H(X)$ is the set of all such prediction vectors as the parameters vary. Least squares finds the point in this set nearest to the observation vector $\mathbf Y$.

还要区分一个函数和它在训练点上的取值。$h$ 接受任意新输入，而粗体 $\mathbf h=(h(X_1),\ldots,h(X_n))^T$ 只记录这 $n$ 个位置上的预测。$\mathcal H(X)$ 就是改变模型参数后，所有这些预测向量组成的集合。最小二乘在这个集合里寻找离观测向量 $\mathbf Y$ 最近的点。

With Gaussian noise, the negative log-likelihood is a parameter-independent constant plus $\|\mathbf Y-\mathbf X\beta\|^2/(2\sigma^2)$, so least squares and maximum likelihood produce the same regression coefficients. The least-squares optimization problem itself can nevertheless be defined and solved without a Gaussian-noise assumption.

在高斯噪声假设下，负对数似然等于一个与参数无关的常数，加上 $\|\mathbf Y-\mathbf X\beta\|^2/(2\sigma^2)$，所以最小二乘与最大似然给出同一组回归系数。最小二乘这个优化问题本身则可以在不假设高斯噪声时定义和求解。

<a id="section-04"></a>

<a id="least-squares"></a>

## LSE in linear regression

**线性回归中的最小二乘估计**


- Denote by $\pmb { \mathsf { X } } \in \mathbb { R } ^ { n \times d }$ the data matrix and $\boldsymbol { \beta } \in \mathbb { R } ^ { d }$ the parameter to estimate

  用 $\pmb { \mathsf { X } } \in \mathbb { R } ^ { n \times d }$ 表示数据矩阵，$\boldsymbol { \beta } \in \mathbb { R } ^ { d }$ 表示待估计参数。

- Assumption: X is of full rank equal to d and assume $d \leq n$

  假设：X 满秩，其秩等于 d，并假设 $d \leq n$。

- Definition of LSE: $\begin{array} { r } { \widehat { \beta } _ { \mathfrak { n } } = \arg \operatorname* { m i n } _ { \beta \in \mathbb { R } ^ { d } } \frac { 1 } { n } \| \pmb { \mathsf { Y } } - \pmb { \mathsf { X } } \beta \| ^ { 2 } } \end{array}$

  最小二乘估计的定义：$\begin{array} { r } { \widehat { \beta } _ { \mathfrak { n } } = \arg \min _ { \beta \in \mathbb { R } ^ { d } } \frac { 1 } { n } \| \pmb { \mathsf { Y } } - \pmb { \mathsf { X } } \beta \| ^ { 2 } } \end{array}$。

- Least square estimate: $\widehat { \mathbf { h } } _ { \mathbf { n } } = \mathbf { X } \widehat { \beta } _ { \mathbf { n } } = \mathbf { X } ( \mathbf { X } ^ { T } \mathbf { X } ) ^ { - 1 } \mathbf { X } ^ { T } \mathbf { Y } = \widehat { \Pi } \mathbf { Y }$

  最小二乘估计：$\widehat { \mathbf { h } } _ { \mathbf { n } } = \mathbf { X } \widehat { \beta } _ { \mathbf { n } } = \mathbf { X } ( \mathbf { X } ^ { T } \mathbf { X } ) ^ { - 1 } \mathbf { X } ^ { T } \mathbf { Y } = \widehat { \Pi } \mathbf { Y }$。

![image](<../Images/02_LM/image_002.jpg>)

<a id="reading-ls-example"></a>

### Understanding matrices and projections through three data points

**用三个数据点看清矩阵与投影**

Reuse the first lecture's data: inputs $t=(-1,0,1)$, observations $Y=(1,1,4)$, and the fitted line $h(t)=\beta_0+\beta_1t$. With the constant term as the first feature column,

沿用第一讲的数据：输入 $t=(-1,0,1)$，观测 $Y=(1,1,4)$，拟合直线 $h(t)=\beta_0+\beta_1t$。把常数项作为第一列特征，得到

$$
\mathbf X=
\begin{pmatrix}
1&-1\\
1&0\\
1&1
\end{pmatrix},\qquad
\mathbf Y=\begin{pmatrix}1\\1\\4\end{pmatrix},\qquad
\beta=\begin{pmatrix}\beta_0\\\beta_1\end{pmatrix}.
$$

Each row is an observation and each column a feature. Here $n=3$ and $d=2$; $\mathbf X\beta$ is the vector of three predictions. Calculation gives

每一行是一条观测，每一列是一种特征。这里 $n=3$、$d=2$；$\mathbf X\beta$ 是三个预测值组成的向量。计算得到

$$
\mathbf X^T\mathbf X=\begin{pmatrix}3&0\\0&2\end{pmatrix},
\qquad
\mathbf X^T\mathbf Y=\begin{pmatrix}6\\3\end{pmatrix},
\qquad
\widehat\beta=\begin{pmatrix}2\\1.5\end{pmatrix}.
$$

Thus $\widehat{\mathbf h}=(0.5,2,3.5)^T$, with residuals $\mathbf r=\mathbf Y-\widehat{\mathbf h}=(0.5,-1,0.5)^T$, residual sum of squares $1.5$, and mean squared error $0.5$.

于是 $\widehat{\mathbf h}=(0.5,2,3.5)^T$，残差 $\mathbf r=\mathbf Y-\widehat{\mathbf h}=(0.5,-1,0.5)^T$，残差平方和为 $1.5$，平均平方误差为 $0.5$。

As the two coefficients vary, $\mathbf X\beta$ can move only in the plane spanned by $(1,1,1)^T$ and $(-1,0,1)^T$. The optimal prediction is the orthogonal projection of $\mathbf Y$ onto that plane. Direct verification gives

改变两个系数，$\mathbf X\beta$ 只能在两列向量 $(1,1,1)^T$ 和 $(-1,0,1)^T$ 张成的平面内移动。最优预测就是 $\mathbf Y$ 到这个平面的正交投影。直接验算：

$$
(1,1,1)\mathbf r=0.5-1+0.5=0,\qquad
(-1,0,1)\mathbf r=-0.5+0.5=0.
$$

The residual is perpendicular to both columns, so adjusting the prediction along any allowed model direction cannot further reduce its distance to $\mathbf Y$. This is the geometry of the normal equations $\mathbf X^T(\mathbf Y-\mathbf X\widehat\beta)=0$. The plane lies in $\mathbb R^3$, with one coordinate per observation, and differs from the original $(t,Y)$ scatterplot plane. [Geometry of least squares](https://www.seas.ucla.edu/~vandenbe/133A/lectures/ls.pdf)

残差与两列都垂直，说明沿任何允许的模型方向调整预测，都不能再缩短到 $\mathbf Y$ 的距离。这正是正规方程 $\mathbf X^T(\mathbf Y-\mathbf X\widehat\beta)=0$ 的几何含义。这里的平面位于“每个坐标对应一条观测”的 $\mathbb R^3$，与原来画散点的 $(t,Y)$ 平面是两种表示。[最小二乘的几何解释](https://www.seas.ucla.edu/~vandenbe/133A/lectures/ls.pdf)

<details>
<summary>Derivation: why orthogonality guarantees a minimum<br>推导：正交条件为什么保证得到最小值</summary>

Any other coefficient vector can be written $\widehat\beta+\Delta$, with residual $\mathbf r-\mathbf X\Delta$. Since $\mathbf r$ is orthogonal to the column space of $\mathbf X$,

任何另一组系数可以写成 $\widehat\beta+\Delta$。相应残差为 $\mathbf r-\mathbf X\Delta$。由于 $\mathbf r$ 与 $\mathbf X$ 的列空间正交，

$$
\|\mathbf Y-\mathbf X(\widehat\beta+\Delta)\|^2
=\|\mathbf r\|^2+\|\mathbf X\Delta\|^2
\geq\|\mathbf r\|^2.
$$

If $\mathbf X$ has full column rank, equality holds only for $\Delta=0$, making the coefficient solution unique. The orthogonal projector also satisfies $\widehat\Pi^T=\widehat\Pi$ and $\widehat\Pi^2=\widehat\Pi$: projecting a vector already in the model plane leaves it unchanged.

若 $\mathbf X$ 列满秩，只有 $\Delta=0$ 才能取等号，因此系数解唯一。正交投影矩阵还满足 $\widehat\Pi^T=\widehat\Pi$ 和 $\widehat\Pi^2=\widehat\Pi$：已经落在模型平面内的向量，再投影一次仍停留在原处。

</details>

<a id="section-05"></a>

## Proof of the LSE computation in linear models

**线性模型中最小二乘计算的证明**

$$
\widehat {\beta} _ {\mathbf {n}} = \underset {\beta \in \mathbb {R} ^ {d}} {\arg \min} R (\beta) \text{其中} R (\beta) = \frac {1}{n} \| \mathbf {Y} - \mathbf {X} \beta \| ^ {2}
$$


- Gradient computation:

  计算梯度：

$$
\frac {d}{d \beta} \left((\mathbf {Y} - \mathbf {X} \beta) ^ {T} (\mathbf {Y} - \mathbf {X} \beta)\right) = - 2 \mathbf {Y} ^ {T} \mathbf {X} + 2 \beta^ {T} \mathbf {X} ^ {T} \mathbf {X} \in \mathbb {R} ^ {1 \times d}
$$


- First-order condition for the minimizer of a convex function:

  凸函数极小点的一阶条件：

$$
-\mathbf {Y} ^ {T} + \beta^ {T} \mathbf {X} ^ {T} \mathbf {X} = 0
$$

> **Note:** This line of the slides omits $\mathbf X$ after $\mathbf Y^T$. The first-order condition should be $-\mathbf Y^T\mathbf X+\beta^T\mathbf X^T\mathbf X=0$.

> **译注：** 原课件该行漏了 $\mathbf Y^T$ 后的 $\mathbf X$。一阶条件应为 $-\mathbf Y^T\mathbf X+\beta^T\mathbf X^T\mathbf X=0$。


- Final result: $\widehat { \beta } _ { \mathfrak { n } } = ( \mathsf { X } ^ { T } \mathsf { X } ) ^ { - 1 } \mathsf { X } ^ { T } \mathsf { Y }$

  最终结果：$\widehat { \beta } _ { \mathfrak { n } } = ( \mathsf { X } ^ { T } \mathsf { X } ) ^ { - 1 } \mathsf { X } ^ { T } \mathsf { Y }$。

<a id="reading-normal-equation"></a>

Writing the gradient as a column vector, the least-squares first-order condition is

把梯度写成列向量，最小二乘的一阶条件就是

$$
\nabla R(\beta)=\frac{2}{n}\mathbf X^T(\mathbf X\beta-\mathbf Y)=0
\quad\Longleftrightarrow\quad
\mathbf X^T\mathbf X\beta=\mathbf X^T\mathbf Y.
$$

The factor $1/n$ does not change this objective's minimizer; keeping it interprets training error as an average per sample across different sample sizes. Once a penalty is added, however, the relative scale of fit and penalty matters. Removing $1/n$ only from the fitting term while keeping the same $\lambda$ no longer represents the same regularization strength.

因子 $1/n$ 不改变这一个目标函数的最小点；保留它的好处，是让不同样本量下的训练误差都按“每个样本平均”来理解。加入惩罚项之后，拟合项与惩罚项的相对比例就有意义了，届时不能只删去拟合项的 $1/n$ 而仍把同一个 $\lambda$ 当成相同的正则化强度。

Here a linear system yields an explicit matrix formula, usually called a closed-form solution. More general nonlinear learning problems often require iterative numerical methods. The task determines the appropriate loss.

这里可以通过线性方程得到显式的矩阵公式，通常称为闭式解。较一般的非线性学习问题往往需要迭代数值求解；具体采用什么损失，则由任务决定。

<a id="section-06"></a>

## Alternate proof based on chain rule

**基于链式法则的另一种证明**


- Let: $R ( \beta ) = \ell ( e ( \beta ) )$ where $\ell ( e ) = \| e \| ^ { 2 }$ and $\boldsymbol { e } ( \beta ) = \boldsymbol { \mathsf { Y } } - \boldsymbol { \mathsf { X } } \beta$

  设 $R ( \beta ) = \ell ( e ( \beta ) )$，其中 $\ell ( e ) = \| e \| ^ { 2 }$，且 $\boldsymbol { e } ( \beta ) = \boldsymbol { \mathsf { Y } } - \boldsymbol { \mathsf { X } } \beta$。

- Chain rule: $\frac { d R } { d \beta } = \frac { \partial \ell } { \partial e } \frac { \partial e } { \partial \beta }$ where the $j \mathrm { - t h }$ element is given by:

  链式法则：$\frac { d R } { d \beta } = \frac { \partial \ell } { \partial e } \frac { \partial e } { \partial \beta }$，其中第 $j \mathrm { - t h }$ 个元素为：

$$
\frac {d R}{d \beta} [ j ] = \sum_ {k = 1} ^ {n} \frac {\partial \ell}{\partial e} [ k ] \frac {\partial e}{\partial \beta} [ k, j ]
$$


- Note that: $\frac { \partial \ell } { \partial e } = 2 e ^ { T } \in \mathbb { R } ^ { 1 \times n }$ and $\frac { \partial e } { \partial \beta } = - { \pmb X } \in \mathbb { R } ^ { n \times d }$

  注意：$\frac { \partial \ell } { \partial e } = 2 e ^ { T } \in \mathbb { R } ^ { 1 \times n }$，且 $\frac { \partial e } { \partial \beta } = - { \pmb X } \in \mathbb { R } ^ { n \times d }$。

- Finally: $\frac{dR}{d\beta}=-2e^T\mathbf X=-2(\mathbf Y-\mathbf X\beta)^T\mathbf X$

  最后得到：$\frac{dR}{d\beta}=-2e^T\mathbf X=-2(\mathbf Y-\mathbf X\beta)^T\mathbf X$。

---

[本课目录](../02_LM_zh.md) · [下一篇：泛化与高维问题](02_generalization_and_high_dimensions.md)
