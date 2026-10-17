# 7. Bayes 最优、一致性与学习界

[本课目录](../01_intro_zh.md) · [上一篇：经验风险、真实风险与损失](06_empirical_and_true_risk.md)

<a id="consistency"></a>

<a id="section-21"></a>

## Optimal elements, consistency and bounds

**最优解、一致性与界**


- Bayes rule $h ^ { * }$ and Bayes error $L ^ { * }$

  Bayes 规则 $h ^ { * }$ 和 Bayes 误差 $L ^ { * }$。

$$
h ^ {*} = \underset {h} {\arg \min} L (h) \quad \text{且} \quad L ^ {*} = L (h ^ {*})
$$

<a id="reading-bayes-reference"></a>

**What is the comparison class for Bayes optimality?**

**Bayes 最优是在什么范围里比较**

First fix the loss and the true data distribution. The Bayes rule $h^*$ minimizes true risk over all permitted measurable decision rules, providing a reference for what could be achieved if the true mechanism were known. The within-class optimum $\bar h$ is additionally restricted by the chosen class $\mathcal H$, while the learned rule $\widehat h_n$ can use only finite data.

先固定损失函数和真实数据分布。Bayes 规则 $h^*$ 在所有允许的可测决策规则中最小化真实风险；它提供的是“知道真实规律时能够达到什么水平”的参照。类内最优规则 $\bar h$ 还受到所选函数类 $\mathcal H$ 的限制，而实际学到的 $\widehat h_n$ 只能利用有限数据。

The optimal risk $L^*$ can still be positive. For example, when the observed features do not uniquely determine a label, even correct conditional probabilities may leave unavoidable mistakes. Learning seeks to reduce the excess risk $L(\widehat h_n)-L^*$ above this optimum.

最优风险 $L^*$ 仍可能大于零。例如，同样的已观测特征并不能唯一决定标签时，即使知道正确的条件概率，也可能判断错误。学习要尽量减少的是相对这个最优水平的额外风险 $L(\widehat h_n)-L^*$。


- (Strong) Consistency of an inference principle $\widehat { h } _ { n }$

  推断原则 $\widehat { h } _ { n }$ 的（强）一致性。

$$
L (\widehat {h} _ {n}) \to L ^ {*}
$$

almost surely

几乎必然成立。


- The nonasymptotic bounds Eldorado :

  非渐近界的“黄金国”：

$$
L (\widehat {h} _ {n}) - L ^ {*} \leq U (n, \mathcal {H}) \quad \text{以高概率}
$$

<a id="reading-consistency"></a>

**Consistency concerns the eventual destination; finite-sample bounds concern the current gap**

**一致性看最终能达到哪里，有限样本界看现在离那里有多远**

Consistency studies long-run behavior as samples accumulate from the same generating mechanism. Strong consistency here means that along a growing training-sample sequence, the learned rule's true risk converges to $L^*$, except on a probability-zero set of sequences. This alone gives no sample count for a specified accuracy, and it does not require the error to decrease whenever one sample is added.

一致性研究同一数据产生机制下，样本越来越多时的长期行为。这里的强一致性表示：沿着不断增加的训练样本序列，除去一个概率为零的例外集合，所学规则的真实风险最终趋近 $L^*$。这个结论本身没有给出达到某个精度所需的样本数，也不要求每增加一个样本，误差都比上一次更小。

A finite-sample bound directly relates the current sample count, candidate-class complexity, and allowed failure probability. Under 0/1 loss, a guarantee that excess risk is at most 0.03 with training-sample probability at least 95% means that the trained classifier's true error rate exceeds the Bayes optimum by at most three percentage points on that event. Such a guarantee can inform whether the present sample size is sufficient.

有限样本界则直接把当前样本数、候选类复杂度和允许的失败概率联系起来。例如，在 0/1 损失下，如果一个界保证“以至少 95% 的训练抽样概率，超额风险不超过 0.03”，那么它说明这次训练得到的分类器，其真实错误率比 Bayes 最优错误率高出的部分至多为 3 个百分点。这种保证可以用于讨论当前样本量是否足够。

Both also depend on what the candidate class can achieve. If the approximation error $L(\bar h)-L^*$ for a fixed $\mathcal H$ is strictly positive, increasingly accurate within-class learning still leaves a gap to the Bayes level. Bayes consistency additionally requires that approximation gap to disappear.

两者还取决于候选类能达到哪里：如果固定 $\mathcal H$ 的近似误差 $L(\bar h)-L^*$ 严格大于零，那么即使类内学习越来越准确，也仍与 Bayes 水平有一段距离。要达到上面的 Bayes 一致性，还需要让这段近似差距消失。

<a id="bayes-exercise"></a>

Find optimal elements $h ^ { * }$ and $L ^ { * }$ in these two cases :

在以下两种情形中，求出最优解 $h ^ { * }$ 和 $L ^ { * }$：


- Binary classification problem : Y takes 0-1 values

  二分类问题：Y 取 0、1 两个值。

$$
\ell (y, y ^ {\prime}) = \mathbb {I} \{y \neq y ^ {\prime} \} \quad \text{且} \quad L (h) = \mathbb {P} \left\{h (X) \neq Y \right\}
$$


- Regression : Y takes values in $\mathbb { R }$

  回归：Y 在 $\mathbb { R }$ 中取值。

$$
\ell (y, y ^ {\prime}) = \left(y - y ^ {\prime}\right) ^ {2} \quad \text{且} \quad L (h) = \mathbb {E} \big ((Y - h (X)) ^ {2} \big)
$$

We shall use the notations $\eta ( x ) = \mathbb { E } ( Y \mid X = x )$ and use the fact that $\mathbb { E } ( Y ) = \mathbb { E } \big ( \mathbb { E } ( Y \mid X ) \big )$

使用记号 $\eta ( x ) = \mathbb { E } ( Y \mid X = x )$，并利用事实 $\mathbb { E } ( Y ) = \mathbb { E } \big ( \mathbb { E } ( Y \mid X ) \big )$。

<a id="reading-bayes-solutions"></a>

**Fix one input before comparing prediction losses**

**先固定一个输入，再比较不同预测的损失**

Both exercises above can begin by fixing $X=x$, finding the best prediction at that input, and then averaging over inputs.

上面两道练习都可以先固定 $X=x$，找出这个输入处最好的预测，再对不同输入取平均。

**Binary classification: choose the class with higher conditional probability.** Because labels are 0 or 1, $\eta(x)=\mathbb E[Y\mid X=x]$ equals $\mathbb P(Y=1\mid X=x)$. If a group of images has $\eta(x)=0.7$, predicting 1 has error probability 0.3 and predicting 0 has error probability 0.7, so predict 1. In general,

**二分类：选择条件概率较大的类别。** 因为标签只能是 0 或 1，$\eta(x)=\mathbb E[Y\mid X=x]$ 就等于 $\mathbb P(Y=1\mid X=x)$。例如，若某类图像的 $\eta(x)=0.7$，预测 1 的错误概率为 0.3，预测 0 的错误概率为 0.7，因此应预测 1。一般地，

$$
h^*(x)=\begin{cases}1,&\eta(x)\ge 1/2,\\0,&\eta(x)<1/2,\end{cases}
\qquad
L^*=\mathbb E\big[\min\{\eta(X),1-\eta(X)\}\big].
$$

When $\eta(x)=1/2$, both predictions have equal risk. Choosing 1 in the displayed rule is simply a tie convention. Selecting the smaller error probability at each input and averaging over the input distribution gives $L^*$.

当 $\eta(x)=1/2$ 时，两种预测的风险相同，上式选择 1 只是规定一种处理平局的方式。每个输入处选较小的错误概率，再对输入分布取平均，就得到 $L^*$。

Using the earlier pedestrian-detection costs, a miss costs 2 and a false alarm 0.5. Predicting 0 then has conditional expected loss $2\eta(x)$, while predicting 1 has loss $0.5(1-\eta(x))$. Comparing them shows that 1 should be predicted when $\eta(x)\ge0.2$. A higher missed-detection cost lowers the threshold for declaring a pedestrian present: the optimal rule changes with the loss.

如果继续使用前面行人检测的代价：漏检损失为 2，误报损失为 0.5，那么预测 0 的条件期望损失为 $2\eta(x)$，预测 1 的为 $0.5(1-\eta(x))$。比较二者可得，$\eta(x)\ge0.2$ 时就应预测 1。漏检代价较高，使判为“有行人”的门槛降低；最优规则随损失的改变而改变。

**Squared-loss regression: predict the conditional mean.** Assume Y has a finite second moment. At fixed x, moving the prediction farther from the conditional mean adds squared error, hence

**平方损失回归：预测条件均值。** 假设 Y 的二阶矩有限。在固定输入 x 处，预测值离条件均值越远，就会增加额外的平方误差，因此

$$
h^*(x)=\eta(x)=\mathbb E[Y\mid X=x],\qquad
L^*=\mathbb E\big[\operatorname{Var}(Y\mid X)\big].
$$

For example, at a fixed x let Y equal 2 or 4 with equal probability. Predicting its conditional mean 3 gives average squared loss $\tfrac12(2-3)^2+\tfrac12(4-3)^2=1$; predicting 2 gives $\tfrac12(2-2)^2+\tfrac12(4-2)^2=2$. The prediction 3 is already optimal, yet its loss is still 1. This is the variation that the current input information cannot predict.

例如，在某个固定 x 下，Y 等概率取 2 和 4。预测条件均值 3 时，平均平方损失是 $\tfrac12(2-3)^2+\tfrac12(4-3)^2=1$；若预测 2，则平均平方损失为 $\tfrac12(2-2)^2+\tfrac12(4-2)^2=2$。选择 3 已经最优，但损失仍为 1，这正是当前输入信息下无法预测的那部分波动。

<details>
<summary>Derivation: why optimal predictions at each input minimize total risk<br>推导：为什么逐个输入最优就能使总风险最小</summary>

Conditional expectation writes the total risk as

条件期望把总风险写成

$$
L(h)=\mathbb E_X\!\left[\mathbb E\big[\ell(h(X),Y)\mid X\big]\right].
$$

Bayes optimization permits any measurable decision rule, so one can select a prediction minimizing conditional risk at each input. For 0/1 classification, the two conditional risks are $\eta(x)$ and $1-\eta(x)$; selecting the smaller yields the rule and optimal risk above.

Bayes 优化允许选择任意可测决策规则，所以可在每个输入处选取条件风险最小的预测。对 0/1 分类，两个候选预测的条件风险就是 $\eta(x)$ 与 $1-\eta(x)$，选择较小者即得上面的规则与最优风险。

For squared-loss regression, fix x and denote any prediction by a. Write $Y-a$ as $(Y-\eta(x))+(\eta(x)-a)$. The first term has conditional mean zero, so the cross term vanishes after expanding the square and taking conditional expectations, giving

对平方损失回归，固定 x 并把任意预测值记为 a，将 $Y-a$ 写成 $(Y-\eta(x))+(\eta(x)-a)$。第一项的条件均值为零，展开平方后的交叉项消失，得到

$$
\mathbb E[(Y-a)^2\mid X=x]
=\operatorname{Var}(Y\mid X=x)+(a-\eta(x))^2.
$$

The variance term does not depend on a; choosing $a=\eta(x)$ makes the second term zero. Averaging over X then gives $L^*=\mathbb E[\operatorname{Var}(Y\mid X)]$. In a smaller function class, predictions at different inputs may be tied together by shared parameters, so these pointwise optima need not be attainable. The result is then a within-class optimum, not necessarily the Bayes optimum.

方差项与 a 无关，取 $a=\eta(x)$ 使第二项为零；再对 X 取期望，得到 $L^*=\mathbb E[\operatorname{Var}(Y\mid X)]$。如果把规则限制在某个较小的函数类中，不同输入处的预测可能由同一组参数联系起来，就未必能逐点取到这个最优值；那时得到的是类内最优，而不一定是 Bayes 最优。

</details>

Inputs, predictions, loss, empirical risk, and optimal risk are now connected: first specify how to evaluate one prediction, then select a rule using finite samples, and finally study how far its true risk is from the ideal optimum. The next section splits that gap back into estimation and approximation errors.

到这里，输入、预测、损失、经验风险和最优风险已经连起来了：先确定怎样评价一次预测，再用有限样本选择规则，最后研究所选规则的真实风险距离理想最优还有多远。下一节把这段差距重新分成估计误差与近似误差。

<a id="section-22"></a>

## Estimation vs. approximation error Extension of bias-variance decomposition

**估计误差与近似误差：偏差—方差分解的推广**


- Proof idea : Add and retrieve $\widehat { L } ( \widehat { h } _ { n } ) \ , \ \widehat { L } ( \overline { { h } } ) , \ L ( \overline { { h } } )$ , then use the definition of ERM to upper bound the sum. Difference between $L$ and $\widehat { L }$ appear twice.

  证明思路：加上再减去 $\widehat { L } ( \widehat { h } _ { n } ) \ , \ \widehat { L } ( \overline { { h } } ) , \ L ( \overline { { h } } )$，然后利用 ERM 的定义对总和取上界。$L$ 与 $\widehat { L }$ 的差会出现两次。

- We have :

  有：

$$
L (\widehat {h} _ {n}) - L ^ {*} \leq \underbrace {2 \sup _ {h \in \mathcal {H}} | L (h) - \widehat {L} _ {n} (h) |} _ {\text{估计误差（随机）}} + \underbrace {L (\overline {{h}}) - L ^ {*}} _ {\text{近似误差（确定性）}}
$$

<a id="finite-class-bound"></a>


- Assume that the hypothesis class $\mathcal { H }$ of decision functions is finite and $h ^ { \ast } \notin \mathcal { H }$

  假设决策函数的假设类 $\mathcal { H }$ 是有限的，并且 $h ^ { \ast } \notin \mathcal { H }$。

- Then, we have, for any $\delta ,$ , with probability at least $1 - \delta$

  则对任意 $\delta ,$，以至少 $1 - \delta$ 的概率，有：

$$
\forall h \in \mathcal {H}, L (h) \leq \widehat {L} _ {n} (h) + \sqrt {\frac {\log | \mathcal {H} | + \log \left(\frac {1}{\delta}\right)}{2 n}}
$$


- log $| \mathcal { H } | = \log K $ Statement in the introduction, see !

  log $| \mathcal { H } | = \log K $：看，这正是导论中的结论！

<a id="section-23"></a>

## Finite hypothesis class Sketch of proof

**有限假设类：证明概要**


- Hoeffding’s inequality :

  Hoeffding 不等式：

- Consider $Z _ { 1 } , \ldots , Z _ { n }$ IID over [0, 1] and $\overline { { Z } } _ { n } = \frac { 1 } { n } \sum _ { i = 1 } ^ { n } Z _ { i }$

  设 $Z _ { 1 } , \ldots , Z _ { n }$ 是取值于 [0,1] 的独立同分布随机变量，且 $\overline { { Z } } _ { n } = \frac { 1 } { n } \sum _ { i = 1 } ^ { n } Z _ { i }$。

- We have, for any $t > 0$

  对任意 $t > 0$，有：

$$
\mathbb {P} \{\overline {{Z}} _ {n} - \mathbb {E} (Z _ {1}) > \varepsilon \} \leq \exp (- 2 n \varepsilon^ {2})
$$


- Union bound : For any two measurable sets A, B, we have :

  并集界：对任意两个可测集合 A、B，有：

$$
\mathbb {P} \{A \cup B \} \leq \mathbb {P} \{A \} + \mathbb {P} \{B \}
$$

<a id="next-sessions"></a>


- Supervised Machine Learning

  监督机器学习。

- Linear models for supervised learning (2 sessions)

  用于监督学习的线性模型（2 次课）。

- From linear to for nonlinear models (2 sessions)

  从线性模型到非线性模型（2 次课）。

- Unsupervised Machine Learning

  无监督机器学习。

- Dimension reduction and clustering (1 session)

  降维与聚类（1 次课）。

---

[本课目录](../01_intro_zh.md) · [上一篇：经验风险、真实风险与损失](06_empirical_and_true_risk.md)
