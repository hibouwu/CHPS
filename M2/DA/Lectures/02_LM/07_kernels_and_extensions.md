# 7. 非线性扩展与核方法

[本课目录](../02_LM_zh.md) · [上一篇：正则化比较与参数选择](06_regularization_and_validation.md)

<a id="section-36"></a>

<a id="kernels"></a>

## B. Estimating nonlinear functions

**B. 估计非线性函数**

### From nonlinear to linear Polynomial regression example

**从非线性到线性：多项式回归例子**


- Consider a polynomial regression in dimension $d = 2$ : this corresponds to a linear model of dimension $d ^ { \prime } = 7$ with feature vector:

  考虑维度为 $d = 2$ 的多项式回归：它对应一个维度为 $d ^ { \prime } = 7$ 的线性模型，特征向量为：

$$
\Phi (x _ {1}, x _ {2}) = \left(1, \sqrt {2} x _ {1}, \sqrt {2} x _ {2}, \sqrt {2} x _ {1} x _ {2}, x _ {1} ^ {2}, x _ {2} ^ {2}\right) ^ {T}
$$

> **Note:** The slide says seven dimensions, but its feature vector has only six components. The dimension consistent with that vector is six.

> **译注：** 原页写作 7 维，但所列特征向量只有 6 个分量；与该向量一致的维度应为 6。


- Note that:

  注意：

$$
\Phi (x) ^ {T} \Phi (x ^ {\prime}) = (x ^ {T} x ^ {\prime} + 1) ^ {2}
$$


- We call $K ( x , x ^ { \prime } ) = ( x ^ { T } x ^ { \prime } + 1 ) ^ { 2 }$ a polynomial kernel. A kernel has the property to be represented as a scalar product in a high dimensional feature space. The feature space is the image of the original input space of dimension d through Φ. The feature space can be of huge dimension.

  称 $K ( x , x ^ { \prime } ) = ( x ^ { T } x ^ { \prime } + 1 ) ^ { 2 }$ 为多项式核。核具有这样一个性质：可以表示为高维特征空间中的内积。特征空间是原始 d 维输入空间经 Φ 映射得到的像空间，其维度可能非常大。

<a id="reading-feature-map"></a>

### Expanding features versus computing the inner product directly

**展开特征，与直接计算内积**

The six features above represent a constant, two linear terms, a cross term, and two squared terms. The function can curve with respect to $(x_1,x_2)$ while remaining linear in the coefficients of these six features.

上面的六个特征允许模型表达常数项、两个一次项、交叉项和两个平方项。函数对 $(x_1,x_2)$ 可以弯曲，但对这六个特征的系数仍然线性。

Take $x=(1,2)^T$ and $z=(2,0)^T$. In the order used by the slides,

取 $x=(1,2)^T$、$z=(2,0)^T$。按照课件给出的顺序，

$$
\Phi(x)=(1,\sqrt2,2\sqrt2,2\sqrt2,1,4)^T,\qquad
\Phi(z)=(1,2\sqrt2,0,0,4,0)^T.
$$

Expanding and taking the inner product gives $1+4+4=9$; directly evaluating the kernel gives $(x^Tz+1)^2=(2+1)^2=9$. Both routes produce the same value. The $\sqrt2$ factors ensure that cross-term coefficients agree with the square expansion.

展开后计算内积，得到 $1+4+4=9$；直接计算核函数，得到 $(x^Tz+1)^2=(2+1)^2=9$。两条路径给出同一个数。特征中的 $\sqrt2$ 正是为了让交叉项的系数与平方展开一致。

If an algorithm only needs these inner products, the kernel can compute the result directly without explicitly listing every feature. This is especially useful for high polynomial degrees or high-dimensional original inputs. [Understanding kernels through feature maps](https://cs229.stanford.edu/notes2021fall/cs229-notes3.pdf)

如果算法只需要这样的内积，就可以用核函数一次算出结果，不必显式列出全部特征。多项式次数或原始输入维度很大时，这种表示尤其有用。[从特征映射理解核方法](https://cs229.stanford.edu/notes2021fall/cs229-notes3.pdf)

<a id="section-37"></a>

## The magic of kernels Kernel ridge regression

**核的魔力：核岭回归**


- In the linear case of ridge regression, we have seen that the only data-dependent quantities that matter in both problem formulation and evaluation of predictions are the pairwise scalar products of $X _ { i } ^ { T } X _ { j }$ and $x ^ { T } X _ { i }$

  在线性岭回归中已经看到，无论问题表述还是预测求值，真正用到的依赖数据的量，只有 $X _ { i } ^ { T } X _ { j }$ 与 $x ^ { T } X _ { i }$ 的两两内积。

- We can basically replace any scalar product by the kernel evaluation of the considered pair without changing at all the algorithmic complexity of resolution. We are then able to estimate the parameters $\alpha _ { i }$ of nonlinear functions of the form:

  基本上，可以将任意一个内积替换为相应点对的核函数值，而完全不改变求解的算法复杂度。于是能够估计下列非线性函数中的参数 $\alpha _ { i }$：

> **Note:** The original algorithmic-complexity statement is retained here. Replacing inner products preserves the Gram-matrix solution framework, but kernel-evaluation and storage costs must still be considered separately.

> **译注：** 这里保留原文的算法复杂度说法。替换内积不改变基于 Gram 矩阵求解的框架，但具体核函数的求值代价与存储成本仍需另外考虑。

$$
f (x) = \sum_ {i = 1} ^ {n} \alpha_ {i} K (x, X _ {i})
$$

<a id="reading-kernel-ridge-example"></a>

### From a kernel matrix to an actual prediction

**从核矩阵到一个实际预测**

Define the $n\times n$ kernel matrix $\mathbf K$ by $K_{ij}=K(X_i,X_j)$. Keeping the earlier notation $c=\widehat\alpha/\lambda$, kernel Ridge regression becomes

定义 $n\times n$ 的核矩阵 $\mathbf K$，其中 $K_{ij}=K(X_i,X_j)$。沿用前面 $c=\widehat\alpha/\lambda$ 的记号，核岭回归可以写成

$$
(\mathbf K+\lambda I_n)c=\mathbf Y,\qquad
\widehat f(x)=\sum_{i=1}^{n}c_iK(x,X_i).
$$

The slides above call the weights directly multiplying the kernels $\alpha_i$. They correspond to $c_i$ here and already absorb the earlier dual multiplier's factor $1/\lambda$.

上方课件把直接乘在核函数前的权重记作 $\alpha_i$，相当于这里的 $c_i$；它已吸收前面对偶乘子中的 $1/\lambda$。

Take two one-dimensional training inputs $X_1=0,X_2=1$, responses $\mathbf Y=(0,1)^T$, kernel $K(x,z)=(1+xz)^2$, and $\lambda=1$. Then

只取两个一维训练输入 $X_1=0,X_2=1$，响应 $\mathbf Y=(0,1)^T$，使用 $K(x,z)=(1+xz)^2$ 和 $\lambda=1$。则

$$
\mathbf K=\begin{pmatrix}1&1\\1&4\end{pmatrix},\qquad
\begin{pmatrix}2&1\\1&5\end{pmatrix}c
=\begin{pmatrix}0\\1\end{pmatrix},
\qquad
c=\begin{pmatrix}-1/9\\2/9\end{pmatrix}.
$$

The prediction function is

预测函数为

$$
\widehat f(x)=-\frac19+\frac29(1+x)^2.
$$

At new input $x=2$, the prediction is $-1/9+2\times9/9=17/9$. Solving only a two-variable linear system has produced a function quadratic in the original input. Positive regularization permits nonzero training residuals, so the curve is not required to pass through both observations. [Kernel Ridge regression](https://scikit-learn.org/stable/modules/kernel_ridge.html)

在新输入 $x=2$ 处，预测值是 $-1/9+2\times9/9=17/9$。求解过程只是一个两元线性系统，得到的函数却对原始输入呈二次关系。正的正则化强度允许训练点上保留残差，因此这里没有要求曲线穿过两个观测。[核岭回归](https://scikit-learn.org/stable/modules/kernel_ridge.html)

<details>
<summary>Derivation: the kernel-space penalty and conditions for a valid kernel<br>推导：核空间里的惩罚是什么，怎样判断核是否合适</summary>

Let the explicit feature matrix be $\mathbf\Phi$ and perform Ridge in that space:

设显式特征矩阵为 $\mathbf\Phi$，在这个空间做 Ridge：

$$
\min_w\|\mathbf Y-\mathbf\Phi w\|^2+\lambda\|w\|^2.
$$

The optimal $w$ lies in the span of the training feature vectors: an orthogonal component would not affect training predictions but would increase the squared-norm penalty, so the optimum removes it. Thus $w=\mathbf\Phi^Tc$. Here $\mathbf K=\mathbf\Phi\mathbf\Phi^T$, the prediction vector is $\mathbf Kc$, and the penalty is

最优 $w$ 位于训练特征向量张成的空间内：与这个空间正交的分量不改变训练预测，却会增加平方范数惩罚，因此最优解会去掉它。于是可以写成 $w=\mathbf\Phi^Tc$。此时 $\mathbf K=\mathbf\Phi\mathbf\Phi^T$，预测向量为 $\mathbf Kc$，惩罚项为

$$
\lambda\|w\|^2=\lambda c^T\mathbf Kc.
$$

Kernel Ridge therefore retains the Ridge penalty in feature space. Directly penalizing $c$ by $\lambda\|c\|^2$ generally defines a different problem.

因此核岭回归保留的是特征空间中的 Ridge 惩罚，直接对 $c$ 使用 $\lambda\|c\|^2$ 一般会得到另一个问题。

A real-valued inner-product kernel must be symmetric and produce a positive semidefinite Gram matrix for every finite sample set. If $K(x,z)=\langle\Phi(x),\Phi(z)\rangle$, then for any weight vector $a$,

一个函数要充当实值内积核，需要对称，并且对任意有限样本组产生半正定的 Gram 矩阵。若 $K(x,z)=\langle\Phi(x),\Phi(z)\rangle$，则对任意权重向量 $a$，

$$
a^T\mathbf Ka=\left\|\sum_i a_i\Phi(X_i)\right\|^2\geq0.
$$

This condition makes $\mathbf K+\lambda I_n$ invertible for $\lambda>0$. An arbitrarily designed similarity need not satisfy it. Similarity in a kernel method must respect this inner-product structure.

这个条件让 $\mathbf K+\lambda I_n$ 在 $\lambda>0$ 时可逆。任意人为设计的“相似度”不一定满足它；核方法所用的相似关系需要符合这种内积结构。

</details>

<a id="section-38"></a>

## Examples of basic kernels

**基本核的例子**


- Linear: $\operatorname { K } ( \mathbf { x } , \mathbf { z } ) = \mathbf { x } \cdot z$

  线性核：$\operatorname { K } ( \mathbf { x } , \mathbf { z } ) = \mathbf { x } \cdot z$。

- Polynomial: $\operatorname { K } ( \mathbf { x } , z ) = ( \mathbf { x } \cdot z ) ^ { \mathrm { d } } \circ r \operatorname { K } ( \mathbf { x } , z ) = ( 1 + \mathbf { x } \cdot z ) ^ { \mathrm { d } }$

  多项式核：$\operatorname { K } ( \mathbf { x } , z ) = ( \mathbf { x } \cdot z ) ^ { \mathrm { d } } \circ r \operatorname { K } ( \mathbf { x } , z ) = ( 1 + \mathbf { x } \cdot z ) ^ { \mathrm { d } }$。

- Gaussian: $\begin{array} { r } { \mathrm { K } ( \mathrm { x } , z ) = \exp \left[ - \frac { \left| \left| x - z \right| \right| ^ { 2 } } { 2 \sigma ^ { 2 } } \right] } \end{array}$

  高斯核：$\begin{array} { r } { \mathrm { K } ( \mathrm { x } , z ) = \exp \left[ - \frac { \left| \left| x - z \right| \right| ^ { 2 } } { 2 \sigma ^ { 2 } } \right] } \end{array}$。

- Laplace Kernel: $\begin{array} { r } { \mathrm { K } ( \mathrm { x } , z ) = \exp \left[ - \frac { | | x - z | | } { 2 \sigma ^ { 2 } } \right] } \end{array}$

  Laplace 核：$\begin{array} { r } { \mathrm { K } ( \mathrm { x } , z ) = \exp \left[ - \frac { | | x - z | | } { 2 \sigma ^ { 2 } } \right] } \end{array}$。

![image](<../Images/02_LM/image_010.jpg>)

<a id="reading-kernel-shape"></a>

### The kernel determines how two inputs are compared

**核函数决定怎样看待两个输入**

The linear kernel preserves the original feature inner product. Polynomial kernels introduce combinations of features of different degrees. The exponent $d$ in the polynomial formula denotes degree; it can instead be called $p$ to avoid confusion with input dimension.

线性核保留原特征的内积；多项式核引入特征间不同次数的组合。这里多项式公式里的指数 $d$ 表示次数，为避免与输入维度混淆，也可以把次数记成 $p$。

The Gaussian kernel decreases with distance. For points separated by $1$, setting $\sigma=0.1$ gives $e^{-50}$, almost zero, whereas setting $\sigma=1$ gives $e^{-1/2}\approx0.607$. A smaller width restricts interactions to closer neighborhoods; a larger width connects more distant samples. Width and regularization strength both affect fitting and should be selected together.

高斯核则随距离增大而减小。若两个点相距 $1$，取 $\sigma=0.1$ 时，核值为 $e^{-50}$，几乎为零；取 $\sigma=1$ 时，核值为 $e^{-1/2}\approx0.607$。较小的宽度把相互作用限制在更近的区域，较大的宽度把更远的样本也联系起来。宽度与正则化强度一起影响拟合，需要共同选择。

A kernel specifies not only a similarity value but also a feature-space distance. Expanding the squared difference between two feature vectors gives the following expression involving only kernel values.

核确定的不只是一个相似度数值，也确定了特征空间里的距离。把两个特征向量之差的平方展开，就得到下面只含核值的公式。

$$
\begin{array}{l} d _ {K} \left(\mathbf {x} _ {1}, \mathbf {x} _ {2}\right) ^ {2} = \| \Phi \left(\mathbf {x} _ {1}\right) - \Phi \left(\mathbf {x} _ {2}\right) \| _ {\mathcal {H}} ^ {2} \\ \qquad = \langle \Phi \left(\mathbf {x} _ {1}\right) - \Phi \left(\mathbf {x} _ {2}\right), \Phi \left(\mathbf {x} _ {1}\right) - \Phi \left(\mathbf {x} _ {2}\right) \rangle_ {\mathcal {H}} \\ \qquad = \langle \Phi \left(\mathbf {x} _ {1}\right), \Phi \left(\mathbf {x} _ {1}\right) \rangle_ {\mathcal {H}} + \langle \Phi \left(\mathbf {x} _ {2}\right), \Phi \left(\mathbf {x} _ {2}\right) \rangle_ {\mathcal {H}} - 2 \langle \Phi \left(\mathbf {x} _ {1}\right), \Phi \left(\mathbf {x} _ {2}\right) \rangle_ {\mathcal {H}} \\ d _ {K} (\mathbf {x} _ {1}, \mathbf {x} _ {2}) ^ {2} = K (\mathbf {x} _ {1}, \mathbf {x} _ {1}) + K (\mathbf {x} _ {2}, \mathbf {x} _ {2}) - 2 K (\mathbf {x} _ {1}, \mathbf {x} _ {2}) \end{array}
$$


- Specific kernels have been design to process structured data such as strings (text, DNA sequence...)

  为处理字符串（文本、DNA 序列等）这样的结构化数据，人们设计了专门的核。

- Example of spectrum kernel used for DNA sequences:

  用于 DNA 序列的谱核示例：

Kernel definition

核的定义


- The 3-spectrum of $\mathbf{x} = \text{CGGSLIAMMWFGV}$ is: (CGG, GGS, GSL, SLI, LIA, IAM, AMM, MMW, MWF, WFG, FGV) .

  $\mathbf{x} = \text{CGGSLIAMMWFGV}$ 的 3-spectrum（长度为 3 的子串谱）是：(CGG, GGS, GSL, SLI, LIA, IAM, AMM, MMW, MWF, WFG, FGV)。


- Let $\Phi_u(\mathbf{x})$ denote the number of occurrences of $u$ in $\mathbf{x}$ . The $k$ -spectrum kernel is: $K(\mathbf{x}, \mathbf{x}') := \sum_{u \in A^k} \Phi_u(\mathbf{x}) \Phi_u(\mathbf{x}')$ .

  令 $\Phi_u(\mathbf{x})$ 表示 $u$ 在 $\mathbf{x}$ 中的出现次数。$k$-spectrum 核定义为 $K(\mathbf{x}, \mathbf{x}') := \sum_{u \in A^k} \Phi_u(\mathbf{x}) \Phi_u(\mathbf{x}')$。




> **Note:** The slide calls this a DNA example, but the string includes characters outside the four-letter DNA alphabet. The original example is retained without changing the kernel's counting definition.

> **译注：** 原页称这是 DNA 序列示例，但字符串含有 DNA 四种碱基字母以外的字符；这里保留原例，不改变核的计数定义。

<a id="reading-string-kernel"></a>

### Comparing strings through shared fragments

**字符串也能通过“共同出现的片段”比较**

Use fragments of length two. ABABA contains AB twice and BA twice; ABBA contains AB, BB, and BA once each. Listing just the potentially contributing coordinates AB, BA, and BB gives the count vectors

取长度为 2 的片段。字符串 ABABA 中，AB 出现 2 次、BA 出现 2 次；字符串 ABBA 中，AB、BB、BA 各出现 1 次。只列出可能有贡献的坐标 AB、BA、BB，两者的计数向量为

$$
\Phi(\mathrm{ABABA})=(2,2,0),\qquad
\Phi(\mathrm{ABBA})=(1,1,1),
$$

Their spectrum-kernel value is therefore $2\times1+2\times1+0\times1=4$. Each fragment type is a feature, and shared fragments contribute similarity through an inner product. Original inputs can be symbol strings, while the algorithm receives pairwise kernel values.

所以二者的谱核值为 $2\times1+2\times1+0\times1=4$。每种片段是一种特征，共同片段通过内积产生相似性。原始输入可以是符号串，进入算法的则是两两核值。

This representation retains local order within fragments of the chosen length, but different strings with identical counts can map to the same feature vector. The induced distance can consequently be zero between distinct inputs and is generally a pseudometric. It becomes a genuine metric when the feature map distinguishes all inputs.

这种表示保留所选长度片段的局部顺序，但计数相同的字符串可能映射到同一特征向量。相应地，核诱导的距离可能让不同输入之间的距离为零，严格说一般是伪距离；如果特征映射能够区分所有输入，才得到真正的距离。

<a id="section-39"></a>

## Kernel machine learning estimation Is it doable?

**核机器学习估计：可行吗？**


- Nice modeling properties of kernel functions

  核函数具有良好的建模性质。

- The question is whether the penalized optimization in the sense of least squares is feasible?

  问题是：最小二乘意义下的惩罚优化是否可行？

<a id="reading-kernel-computation"></a>

### Where the computation moves when explicit feature expansion is avoided

**省去特征展开以后，计算量转移到了哪里**

Kernels can avoid constructing very high-dimensional or even infinite-dimensional features explicitly, but still require handling relationships among samples. Standard dense kernel Ridge stores a $n\times n$ matrix, requiring $O(n^2)$ storage. Conventional direct factorization takes about $O(n^3)$ operations, in addition to kernel evaluations needed to construct the matrix.

核方法可以避免显式构造很高维甚至无限维的特征，却仍然需要处理样本之间的关系。标准的稠密核岭回归需要存储 $n\times n$ 的矩阵，存储量为 $O(n^2)$；常规直接分解求解约需 $O(n^3)$ 运算，构建核矩阵还要加上核函数的求值成本。

For example, with $n=10,000$, the matrix has one hundred million entries. Storing this matrix alone in double precision takes about $0.8$ GB, before factorization workspace and other overhead. Predicting a new input usually also requires its kernel values against training samples. Kernels avoid the difficulty of explicit feature expansion, but large sample counts still carry costs.

例如 $n=10,000$ 时，矩阵有一亿个元素，仅用双精度存储这一张矩阵就约需 $0.8$ GB，尚未计入分解等额外空间。对一个新输入的预测，通常还要计算与各训练样本的核值。因此，核方法绕开的是显式特征展开的困难，大样本量带来的成本仍要处理。

Returning to the two representations, linear Ridge can choose a solution method based on $d$ and $n$, whereas general kernel methods mainly work with a sample Gram matrix. This distinction shows both where the kernel trick saves work and where computational costs remain.

回到前面的两种表示：线性 Ridge 可以根据 $d$ 和 $n$ 选择较合适的求解方式；一般核方法主要围绕样本 Gram 矩阵展开。理解这一区别，也就能看出核技巧在哪个环节节省了工作、又在哪个环节留下了成本。

<a id="section-40"></a>

## C. Generalizations Application to other estimation problems

**C. 推广：应用于其他估计问题**

### Penalized optimization What about other variations?

**惩罚优化：还有哪些变体？**


- Until now: hypothesis class with linear functions $h \in \mathcal H$ and variations on the penalties

  到目前为止：由线性函数 $h \in \mathcal H$ 构成的假设类，以及不同的惩罚项。

$$
\text{准则} (h) = \text{训练误差} (h) + \lambda \text{惩罚项} (h)
$$


- From now on: play with other losses affects the Training error

  从现在起：使用其他损失函数来改变训练误差。

$$
\text{准则} (h) = \text{训练误差} (h) + \lambda \text{惩罚项} (h)
$$

A few examples:

几个例子：

Ridge regression:

岭回归：

$$
\min _ {\boldsymbol {\beta} \in \mathbb {R} ^ {p}} \frac {1}{n} \sum_ {i = 1} ^ {n} \frac {1}{2} (y _ {i} - \boldsymbol {\beta} ^ {\top} \mathbf {x} _ {i}) ^ {2} + \lambda \| \boldsymbol {\beta} \| _ {2} ^ {2}.
$$

Linear SVM:

线性 SVM：

$$
\min _ {\boldsymbol {\beta} \in \mathbb {R} ^ {p}} \frac {1}{n} \sum_ {i = 1} ^ {n} \max (0, 1 - y _ {i} \boldsymbol {\beta} ^ {\top} \mathbf {x} _ {i}) + \lambda \| \boldsymbol {\beta} \| _ {2} ^ {2}.
$$

Logistic regression: $\min_{\beta\in\mathbb R^p}\frac1n\sum_{i=1}^n\log\left(1+e^{-y_i\beta^T\mathbf x_i}\right)+\lambda\|\beta\|_2^2$

逻辑回归：$\min_{\beta\in\mathbb R^p}\frac1n\sum_{i=1}^n\log\left(1+e^{-y_i\beta^T\mathbf x_i}\right)+\lambda\|\beta\|_2^2$。

![image](<../Images/02_LM/image_011.jpg>)

<a id="reading-changing-the-loss"></a>

### Keep the modeling framework while changing what a wrong prediction means

**保留建模框架，改变“预测错了”的含义**

Squared loss directly compares numerical predictions with numerical targets. In binary classification with labels $y\in\{-1,1\}$, a model can output score $s=\beta^Tx$ and use its sign to choose a class. The product $ys$, called the margin, is positive for the correct direction and negative for the wrong one.

平方损失适合直接比较数值预测与数值目标。二分类中，若标签 $y\in\{-1,1\}$，可以让模型输出分数 $s=\beta^Tx$，再用符号决定类别；乘积 $ys$ 称为间隔，它为正说明方向正确，为负说明方向错误。

The linear SVM hinge loss is $\max(0,1-ys)$: even the correct direction incurs a cost if the margin is too small, and this sample's loss becomes zero once the margin reaches $1$. Logistic loss $\log(1+e^{-ys})$ decreases smoothly as the margin increases. In the plot, red squared loss rises again after the prediction exceeds its numerical target, green hinge loss becomes zero at its threshold, and blue logistic loss approaches zero gradually.

线性 SVM 的 hinge 损失是 $\max(0,1-ys)$：方向正确但间隔不足时仍付出代价，间隔达到 $1$ 后该样本的损失为零。逻辑损失 $\log(1+e^{-ys})$ 则随间隔增加平滑下降。图中红色平方损失在预测超过目标数值以后又上升，绿色 hinge 损失达到阈值后变为零，蓝色逻辑损失逐渐趋近零。

All these methods can still use regularization, feature transformations, and validation. Changing the loss changes how predictions are evaluated for the task; changing the penalty changes the desired structure and complexity of the solution.

这些方法都可以继续配合正则化、特征变换和验证流程。改变损失，是在改变任务中如何评价预测；改变惩罚，是在改变对解的结构与复杂度的要求。


- Other tasks: linear models for classification

  其他任务：用于分类的线性模型。

- The issue of representation: feature engineering, variable selection , representation learning

  表示问题：特征工程、变量选择、表示学习。

- From linear to nonlinear models: what can be saved?

  从线性模型到非线性模型：哪些部分可以保留？

<a id="reading-sources"></a>

<details>
<summary>来源与阅读说明</summary>

正文以原课件的完整中文译文为骨架，例子、练习、重复正文、公式、图表及文献均保留；图中文字保留原图语言。原课件错误与必要辨析在相应位置说明。课堂解释已融入概念所在段落，手算例子用于把定义与运算联系起来。

原始课堂记录：[转录 1](../02_part1.md)、[转录 2](../02_part2.md)、[转录 3](../02_part3.md)。重复口头表达、课间安排、个人经历和未采用的旁支讨论仍可在原始记录中查阅，具体去向见[本讲整合与核对记录](../Translation-audit/02_LM_classroom_integration.md)。

外部材料按问题选用：


- [UCLA：Least squares](https://www.seas.ucla.edu/~vandenbe/133A/lectures/ls.pdf)：投影与最小二乘。

- [UCLA：Multi-objective least squares](https://www.seas.ucla.edu/~vandenbe/133A/lectures/mols.pdf)：二次惩罚与正则化。

- [Stanford CS229：LASSO](https://cs229.stanford.edu/notes2021fall/lecture10-lasso-regression.pdf)：变量选择与系数路径。

- [scikit-learn：交叉验证](https://scikit-learn.org/stable/modules/cross_validation.html)：训练、验证及预处理的配合。

- [Stanford CS229：核方法](https://cs229.stanford.edu/notes2021fall/cs229-notes3.pdf)：特征映射、内积与核的条件。

- [scikit-learn：Elastic Net](https://scikit-learn.org/stable/modules/linear_model.html#elastic-net) 与[核岭回归](https://scikit-learn.org/stable/modules/kernel_ridge.html)：目标函数及方法之间的联系。

- [Friedman、Hastie、Tibshirani：Group LASSO 与 Sparse Group LASSO](https://arxiv.org/abs/1001.0736)：组稀疏与组内稀疏的区别。

- [Raissi、Perdikaris、Karniadakis：物理信息学习](https://arxiv.org/abs/1711.10561)：把方程信息加入学习目标的延伸阅读。

</details>

---

[本课目录](../02_LM_zh.md) · [上一篇：正则化比较与参数选择](06_regularization_and_validation.md)
