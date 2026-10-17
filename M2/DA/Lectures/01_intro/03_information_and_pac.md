# 3. 信息量、样本与 PAC 学习

[本课目录](../01_intro_zh.md) · [上一篇：算法家族、正则化与处理流程](02_algorithms_and_pipeline.md) · [下一篇：学习对象与偏差—方差分解](04_hypotheses_and_bias_variance.md)

<a id="sample-size"></a>

<a id="section-12"></a>

## Supervised Machine Learning Learning and information

**监督机器学习：学习与信息**

<a id="questions-game"></a>

### Learning like the twenty-question game

**像“二十问”游戏一样学习**


- Assume Nature has picked one function among K and we want to reveal this function

  假设自然界从 K 个函数中选取了一个，我们希望找出这个函数。

- Assume we have an oracle answering YES or NO when we ask a question about this function

  假设存在一个预言机：当我们就这个函数提出问题时，它回答“是”或“否”。

- What is the optimal number n of questions to ask to find the unknown function ?

  为找到这个未知函数，最优的提问次数 n 是多少？

<a id="classroom-twenty-questions"></a>

**Understanding information through a guessing game from 1 to 100**

**用 1 到 100 的猜数游戏理解信息量**

Imagine guessing an integer from 1 to 100 using only yes/no questions. Asking whether it is 1, then 2, and so on usually eliminates just one candidate per negative answer. Asking whether it exceeds 50 eliminates about half at once, after which the remaining interval can be bisected again. The candidate count decreases roughly as $100\to50\to25\to13\to7\to4\to2\to1$, so at most seven suitable questions suffice.

设想要猜一个 1 到 100 的整数，每次提问只能得到“是／否”作为回答。逐个问“是 1 吗、是 2 吗”时，一个“不是”通常只排除一个候选；问“是否大于 50”则可一次排除约一半，随后继续对剩余区间二分。候选数约按 $100\to50\to25\to13\to7\to4\to2\to1$ 缩小，所以最多 7 个适当问题就够。

Efficiency depends on how many candidates one answer distinguishes, not merely on the question count. There are at most $2^n$ distinct sequences of $n$ binary answers. Distinguishing K objects therefore requires at least $2^n\ge K$. This explains the appearance of $\lceil\log_2 K\rceil$ below.

这里控制效率的是一次回答能区分多少候选，而不只是问题数量。$n$ 个二进制回答最多有 $2^n$ 种不同回答序列；要区分 K 个对象，至少要使 $2^n\ge K$。这是下面出现 $\lceil\log_2 K\rceil$ 的原因。

This is a worst-case guarantee when suitable bisection questions are allowed. The transcript's phrase average log 100 questions should not be treated as the expectation for any questioning strategy. Sequential enumeration can stop when only one candidate remains, without asking another question. Oral slips between 100 and 1000 do not affect the bisection idea.

这说的是允许恰当二分问题时的最坏情况保证，不应把转录中的“平均 log 100 次”照搬为任意提问策略的期望值。逐个枚举可在剩最后一个候选时停止，不必再多问；课堂中的 100／1000 等口误也不影响二分思想。

*来源：[转录 3](../01_part3.md) 第 203–220 行。*

<a id="finite-questions"></a>

### Brute force learning Finite case

**穷举学习：有限情形**


- ISSUE : How many questions with answers YES or NO one has to ask the oracle to find THE function among K functions ?

  问题：为了从 K 个函数中找到那个函数，需要向预言机提出多少个答案为“是”或“否”的问题？

- STRATEGY : Proceed recursively by splitting the set of functions in two groups and asking whether THE function is the first group and removing the group which does not contain the function. This leads to the identification of the desired function with about log K questions.

  策略：递归地把函数集合分为两组，询问目标函数是否位于第一组，并移除不包含目标函数的那一组。这样大约经过 log K 次提问，就能识别目标函数。

- ANSWER : Number of questions $n = \left\lceil { \frac { \log K } { \log 2 } } \right\rceil = \lceil \log _ { 2 } K \rceil$

  答案：提问次数为 $n = \left\lceil { \frac { \log K } { \log 2 } } \right\rceil = \lceil \log _ { 2 } K \rceil$。

- NB : this quantity represents the number of bits of information characterizing the function in the set of K functions

  注意：这个量表示在 K 个函数的集合中确定一个函数所需的信息比特数。

<a id="information-theory"></a>

### Shannon’s Information theory The origin of the log $\boldsymbol { K }$

**Shannon 信息论：log $\boldsymbol { K }$ 的由来**


- Number of bits to encode a collection of K functions where each function can occur with probability $P ( k )$

  对一个包含 K 个函数的集合进行编码所需的比特数，其中各函数出现的概率为 $P ( k )$。

![image](<../Images/01_intro/image_007.jpg>)


- Entropy of a distribution $P$ in information theory :

  信息论中，分布 $P$ 的熵为：

$$
H (P) = - \sum_ {k = 1} ^ {K} P (k) \log_ {2} P (k) \leq \log_ {2} K
$$

<a id="classroom-entropy"></a>

**What fixed-length coding and entropy measure**

**固定长度编码与熵分别在量什么**

For eight candidate objects, assign the eight three-bit codes from 000 to 111. This connects the number of binary answers needed to identify an object with the number of bits needed to label it. A fixed-length code for K objects requires $\lceil\log_2 K\rceil$ bits.

若有 8 个候选对象，可以给它们分配 000 到 111 共 8 个三位编码。这样，“确定一个对象需要几次二元回答”和“给一个对象编号需要多少比特”就联系起来了。对 K 个对象的固定长度编码，所需位数是 $\lceil\log_2 K\rceil$。

When objects have different probabilities, some outcomes are more common than others. Entropy averages their information content using those probabilities. A uniform distribution is hardest to predict in advance and has entropy $\log_2 K$; a more concentrated distribution can have lower average uncertainty.

当对象出现概率不同，有些结果比其他结果更常见，熵就把不同结果的信息量按概率平均。均匀分布时最难预先猜中，熵达到 $\log_2 K$；分布越集中，平均不确定性可以越低。

<details>
<summary>Calculation: entropy of eight equally likely objects<br>推算：8 个等可能对象的熵</summary>

For each object, $P(k)=1/8$, so one outcome carries $-\log_2(1/8)=3$ bits of information and the average remains $H(P)=-8\times(1/8)\log_2(1/8)=3$ bits.

对每个对象，$P(k)=1/8$，所以单个结果的信息量为 $-\log_2(1/8)=3$ 比特，平均仍为 $H(P)=-8\times(1/8)\log_2(1/8)=3$ 比特。

Describing entropy as the expectation of the logarithm of probability omits a minus sign. The correct expression is $-\mathbb E[\log_2 P(J)]$, where J indexes the random object and K remains the total candidate count. Entropy concerns optimal average code length, not the length of an arbitrary code. Its maximum does not require an even candidate count. When the count is a power of two, fixed-length binary coding requires no upward-rounding overhead.

转录把熵说成“概率对数的期望”时漏了负号；应读作 $-\mathbb E[\log_2 P(J)]$，其中 J 表示随机对象的索引，K 仍表示候选总数。熵与最优平均编码长度有关，不等于任意编码的长度。熵最大值的结论不要求候选数是 2 的倍数；候选数为 2 的幂时，等长二进制编码正好没有向上取整的余量。

</details>

*来源：[转录 3](../01_part3.md) 第 221–227 行。*

<a id="questions-data"></a>

<a id="section-13"></a>

## From questions to data

**从提问到数据**

a. Exhaustive search in the zero-error case

a. 零误差情形下的穷举搜索。

b. PAC learning in the zero-error case

b. 零误差情形下的 PAC 学习。

c. PAC learning in the general case

c. 一般情形下的 PAC 学习。

PAC = Probably Approximately Correct

PAC = Probably Approximately Correct，即“以高概率近似正确”。

L. Valiant (1984). A theory of the learnable. Communications of the ACM.

L. Valiant（1984）. A theory of the learnable（可学习性理论）. Communications of the ACM.

<a id="classroom-pac-meaning"></a>

**What question does a labeled sample answer?**

**一个带标签的样本，相当于回答了什么问题**

In image classification, $x_i$ is the input given to candidate functions and $y_i$ is its known correct label. A candidate predicting $f(x_i)\ne y_i$ can be eliminated in a noiseless setting where the target really belongs to the candidate class. Candidate numbers in the guessing game thus correspond to candidate functions, and a question together with its answer corresponds to a labeled sample.

在图像分类中，$x_i$ 是给候选函数的输入，$y_i$ 是这个输入的已知正确标签。若某个候选函数预测 $f(x_i)\ne y_i$，在无噪声、目标确实属于候选类的设定下，就可以把它排除。于是，猜数中的“候选数字”对应候选函数，问题及答案对应带标签的样本。

Actual learning usually need not identify a unique target exactly. Two functions may differ only on very rare inputs, and noisy data may prevent any function from always being correct. PAC therefore separates two requirements: allow the selected rule a small true error, and require a sufficiently high probability of selecting such a good rule. These are what approximately correct and probably respectively describe.

但真实学习通常不要求精确识别唯一目标：两个函数可能只在极少出现的输入上不同，而含噪数据甚至不允许任何函数总是正确。PAC 因而把目标分成两层：允许所选规则的真实误差略大，同时要求选出这种好规则的成功概率足够高。这就是“近似正确”和“以高概率”分别修饰什么。

Label flipping is an intuitive example of noise: an image containing a pedestrian is labeled as containing none. It shows why all samples need not agree with a perfect function; it does not imply that noise only comes from deliberate tampering. PAC's historical contribution was to turn what can be learned into a formal question. The Valiant reference from the slides is retained, while casual remarks about page counts or citation rankings are not treated as course concepts.

标签翻转是一种直观的噪声例子：原本有人行人的图像被标成无行人。它说明“所有样本必须与某个完美函数一致”的设定可能不成立，而不是说噪声只能来自人为篡改。PAC 的历史意义在于把“什么能够被学到”变成可以讨论的形式化问题；原课件给出的 Valiant 文献保留，课堂对页数或引用排名的随口描述不作为知识点。

*来源：[转录 3](../01_part3.md) 第 230–263 行。*

<a id="section-14"></a>

## From questions to data

**从提问到数据**

<a id="zero-error"></a>

### a. Zero error case (1/2)

**a. 零误差情形（1/2）**


- Notations : Domain space X and label space $\mathcal { V } = \{ 0 , 1 \}$

  记号：定义域空间 X，标签空间 $\mathcal { Y } = \{ 0 , 1 \}$。

- Zero-error setup : Consider a finite set of indicator functions

  零误差设定：考虑有限个指示函数

$$
f _ {k}: \mathcal {X} \to \{0, 1 \}, \quad k = 1, \dots , K
$$

and a collection of data points $\left( x _ { i } , y _ { i } \right)$ such that there always exists some k for which $y _ { i } = f _ { k } ( x _ { i } )$ , for any index i

以及一组数据点 $\left( x _ { i } , y _ { i } \right)$，使得总存在某个 k，对任意索引 i 都满足 $y _ { i } = f _ { k } ( x _ { i } )$。


- Worst case scenario : the collection of data points $x _ { i } \in { \mathcal { X } }$ is such that the cardinality of the set of vectors $\{ ( f _ { 1 } ( x _ { i } ) , \ldots , f _ { K } ( x _ { i } ) ) : i \geq 1 \}$ is maximal and equal to $2 ^ { K }$

  最坏情形：数据点集合 $x _ { i } \in { \mathcal { X } }$ 使向量集合 $\{ ( f _ { 1 } ( x _ { i } ) , \ldots , f _ { K } ( x _ { i } ) ) : i \geq 1 \}$ 的基数达到最大值，等于 $2 ^ { K }$。

- ISSUE : How many examples $( x _ { i } , y _ { i } ) \in \mathcal { X } \times \{ 0 , 1 \}$ to find the unknown indicator function among K possible indicator functions $f _ { k } : \mathcal { X } \to \{ 0 , 1 \} , k = 1 , \ldots , K \ ?$

  问题：需要多少个样本 $( x _ { i } , y _ { i } ) \in \mathcal { X } \times \{ 0 , 1 \}$，才能从 K 个可能的指示函数 $f _ { k } : \mathcal { X } \to \{ 0 , 1 \} , k = 1 , \ldots , K \ ?$ 中找到未知的那个？

- SAME ANSWER : Number of examples $n = \left\lceil { \frac { \log K } { \log 2 } } \right\rceil$

  答案相同：样本数为 $n = \left\lceil { \frac { \log K } { \log 2 } } \right\rceil$。

STRATEGY : One has to find a vector $x _ { j }$ such that half of the functions take value 1 and the other half take value 0 and ask the oracle whether the desired function takes value 1 or 0 on this vector and discard those functions taking the opposite value. Apply this n times.

策略：找到一个向量 $x _ { i }$，使一半函数在该点取值 1，另一半取值 0；询问预言机目标函数在这个向量上取值 1 还是 0，并排除取相反值的函数。将这一过程执行 n 次。

> **Note:** This strategy assumes active choice of query points. At each step, one must find an input x on which about half the remaining candidates predict 0 and half predict 1, then request its true label. A numerical interval always has a midpoint, but a general function class need not admit such an x, and finding one may be difficult even if it exists. Thus $\lceil\log_2 K\rceil$ counts ideal queries; it is not a sample size that arbitrary random observations achieve.

> **译注：** 这个策略假设可以主动选择查询点：每一步都要找到一个输入 x，使当前剩余候选中约一半预测 0、另一半预测 1，再询问它的真实标签。猜数时区间总有中点，但一般的函数集合未必存在这样的 x，即使存在，找到它本身也可能很难。因此 $\lceil\log_2 K\rceil$ 是理想查询下的次数，不是任意随机样本都能达到的样本量。

<a id="classroom-query-limit"></a>

**Why guessing numbers permits bisection but arbitrary data may not**

**为什么猜数能二分，任意数据未必能**

If two candidate functions agree on every image collected so far, those data have not distinguished them, however often their predictions are computed. An input on which they disagree is needed before its label can resolve the choice. Sample count and informational value are therefore different things.

若两个候选函数在所有已采集的图像上都预测相同，它们无论各预测了多少遍，都还没有被这些数据区分开；需要出现使二者预测不同的输入，才可能借标签判断。这解释了为什么样本数量与样本的信息价值不是同一件事。

Also note that the classification label space is the set $\{0,1\}$, not the interval $[0,1]$ containing arbitrary real values.

另外注意，分类标签空间是集合 $\{0,1\}$，不是包含任意实数的区间 $[0,1]$。

*来源：[转录 3](../01_part3.md) 第 263–281 行。*

<a id="pac-zero"></a>

### From questions to data b. PAC in the zero-error case

**b. 零误差情形下的 PAC**


- REMARK : it may be hard to find such an $x _ { j }$ which splits every subset of functions into two equal parts.

  备注：要找到一个 $x _ { j }$，使每个候选函数子集都被平分成两部分，可能很困难。

- SAMPLING : Assume $X _ { 1 } , \ldots , X _ { n }$ is an IID sample

  采样：假设 $X _ { 1 } , \ldots , X _ { n }$ 是独立同分布样本。

- QUESTION : In the zero-error setup, how many examples $( X _ { i } , Y _ { i } )$ are required to find among a finite collection of indicator functions $f : \mathcal { X }  \{ 0 , 1 \}$ the one whose error probability is ε-close to zero with probability $1 - \delta ?$

  问题：在零误差设定下，需要多少个样本 $( X _ { i } , Y _ { i } )$，才能从有限个指示函数 $f : \mathcal { X }  \{ 0 , 1 \}$ 中，以概率 $1 - \delta ?$ 找到一个错误概率与零相差不超过 ε 的函数？

- ANSWER : Number of examples

  答案：样本数为

$$
n = \left\lceil \frac {\log K + \log (1 / \delta)}{\varepsilon} \right\rceil
$$

(Proof left as an exercise)

（证明留作练习。）

<a id="classroom-epsilon-delta"></a>

**ε controls rule error; δ controls the probability of an unsuccessful training sample**

**ε 管规则的误差，δ 管训练抽样失败的概率**

Think of training as a repeatable experiment: draw n fresh samples and retrain each time, potentially obtaining a different rule.

把训练想成可以重复做的实验：每次重新抽取 n 个样本、重新训练，得到的规则可能不同。


- $\varepsilon$ bounds the true error of the rule from a successful training run. In a general setting, it usually bounds excess risk relative to an optimal reference.

  $\varepsilon$ 控制一次成功训练所得规则的真实误差上限；在一般情形中，通常控制相对某个最优参照的额外风险。

- $\delta$ controls the probability of drawing an unfavorable training set on which the guarantee fails. The outer success probability is at least $1-\delta$.

  $\delta$ 控制抽到不利训练集、使保证失败的概率。外层成功概率至少是 $1-\delta$。

For example, in a realizable setting, $\varepsilon=0.05$ and $\delta=0.01$ mean that with at least 99% probability over training samples, the selected classifier's error rate under the target distribution is at most 5%. They do not mean that every input is classified correctly with probability 99%, or that exactly 5% of each training batch is misclassified.

例如，在可实现设定下，$\varepsilon=0.05$、$\delta=0.01$ 的含义是：以至少 99% 的训练抽样概率，所选分类器在目标分布上的错误率不超过 5%。它不表示每个输入都以 99% 概率被正确分类，也不表示每批训练样本恰好错 5%。

<details>
<summary>Derivation: why the realizable case gives 1/ε, proving the exercise above<br>推导：为什么可实现情形出现 1/ε（即上面留作练习的证明）</summary>

For a fixed candidate with true error greater than $\varepsilon$, the probability of making no mistakes on n IID training examples is at most $(1-\varepsilon)^n\le e^{-n\varepsilon}$. Learning may select a bad function whenever any such candidate among K functions agrees with all training labels. The union bound bounds this event's probability by $K e^{-n\varepsilon}$.

对一个真实错误率大于 $\varepsilon$ 的固定候选函数，在 n 个独立同分布训练样本上碰巧一次也不出错的概率，不超过 $(1-\varepsilon)^n\le e^{-n\varepsilon}$。K 个候选中，只要存在一个这样的坏函数却与全部训练标签相容，学习就有选错的可能；并集界把该概率上界为 $K e^{-n\varepsilon}$。

Requiring this upper bound to be at most $\delta$ gives

令这个上界不超过 $\delta$，得到

$$
n\ge\frac{\log K+\log(1/\delta)}{\varepsilon}.
$$

The conditions are a finite candidate class fixed in advance, IID samples, a true target belonging to that class, and an algorithm choosing a function with zero training error. The conclusion is high-probability approximate correctness, not exact recovery of the target.

这里用到的条件是：候选类有限且预先固定、样本独立同分布、真实目标属于候选类，以及算法选择在训练集上零误差的函数。结论是以高概率找到近似正确的函数，而不是精确恢复目标。

</details>

*来源：[转录 3](../01_part3.md) 第 278–287 行；[转录 3](../01_part3.md) 第 335–362 行。*

<a id="reading-risk-notation"></a>

**Distinguish two averages before reading the probability bounds**

**进入概率界前，先认清两种平均**

We will use two quantities that evaluate the same rule h:

接下来会用到两个评价同一规则 h 的量：

| Notation<br>记号 | Which losses are averaged?<br>平均的是哪些损失 | Interpretation<br>怎样理解 |
|---|---|---|
| $\widehat L_n(h)$ | Losses on the current n training samples<br>当前 n 个训练样本上的损失 | Empirical risk, directly computable from the available data<br>已经拿到数据，可以直接计算的经验风险 |
| $L(h)$ | Losses on inputs and labels from the target distribution<br>目标分布产生的输入与标签上的损失 | True risk sought on future data, usually unknown<br>希望模型在未来数据上达到的真实风险，通常未知 |

The loss on each sample is $\ell(h(X_i),Y_i)$. **Empirical risk minimization (ERM)** selects the candidate minimizing $\widehat L_n(h)$; denote the selected rule by $\widehat h$. Probability bounds explain how good its true performance can be when selection uses training performance. Full definitions appear later under [empirical risk minimization](06_empirical_and_true_risk.md#empirical-risk) and [true error](06_empirical_and_true_risk.md#loss-risk); for now these two averages make the proof readable.

每个样本的损失写成 $\ell(h(X_i),Y_i)$。**ERM（经验风险最小化）**就是在候选类中选择 $\widehat L_n(h)$ 最小的规则，选出的规则记作 $\widehat h$。概率界要解释：用训练集上的表现作选择，真实表现还能有多好。完整定义在后面的[经验风险最小化](06_empirical_and_true_risk.md#empirical-risk)和[真实误差](06_empirical_and_true_risk.md#loss-risk)两节，这里先用这两个平均值读懂证明。

<a id="pac-general"></a>


- ASSUME : among K functions, NONE of them commits zero error on the sample $\{ ( X _ { i } , Y _ { i } ) : i \geq 1 \}$

  假设：K 个函数中，没有任何一个在样本 $\{ ( X _ { i } , Y _ { i } ) : i \geq 1 \}$ 上达到零误差。

- SAME ISSUE AS BEFORE

  问题与前面相同。

- ANSWER : Number of examples on average

  答案：平均而言，样本数为

$$
n = \left\lceil \frac {\log K + \log (1 / \delta)}{2 \varepsilon^ {2}} \right\rceil
$$

Same dependency on K, the only change is in the constant.

对 K 的依赖关系相同，变化仅在常数上。

> **Note:** The slide says on average, whereas PAC guarantees are usually stated with probability at least $1-\delta$. In the general case, the comparison is between the learned risk and the best risk in the candidate class, not a promise of zero true error despite noise. The slide's formula corresponds to a one-sided uniform deviation: Hoeffding's inequality and the union bound give probability at least $1-\delta$ that all K candidates satisfy $L(h)\le\widehat L_n(h)+\varepsilon$, consistent with the later [finite-class bound](07_bayes_and_learning_bounds.md#finite-class-bound). Guaranteeing the ERM within-class excess risk $L(\widehat h)-L(\bar h)\le\varepsilon$ requires controlling both sides and using the deviation twice, which changes the constant. One sufficient condition is $n\ge 2\log(2K/\delta)/\varepsilon^2$; see the [proof sketch](#classroom-probability-proof).

> **译注：** 原页写作“平均而言”，但 PAC 保证通常以概率至少 $1-\delta$ 陈述。一般情形比较的是候选类中最优风险与所学风险，不应理解为含噪时仍能把真实错误率压到零。原页公式对应的是单侧一致偏差：由 Hoeffding 不等式和并集界，以至少 $1-\delta$ 的概率，所有 K 个候选同时满足 $L(h)\le\widehat L_n(h)+\varepsilon$，这与后面的[有限类界](07_bayes_and_learning_bounds.md#finite-class-bound)一致。若要保证 ERM 的类内超额风险 $L(\widehat h)-L(\bar h)\le\varepsilon$，需要控制双侧偏差并用到两次，常数随之改变，一个充分条件是 $n\ge 2\log(2K/\delta)/\varepsilon^2$，推导见[证明概要](#classroom-probability-proof)。

<a id="classroom-sample-scaling"></a>

**Reading sample-size bounds without treating them as universal recipes**

**怎样读样本量界，而不误读成万能配方**

In a finite function class, the cost of more candidates enters through $\log K$. Smaller error or higher confidence requires more data. With general noise, the precision dependence changes from $1/\varepsilon$ to $1/\varepsilon^2$.

在有限函数类里，候选数增加的代价通过 $\log K$ 出现；要求更小误差或更高置信度，则需要更多数据。一般有噪声情形中，对精度的依赖从 $1/\varepsilon$ 变为 $1/\varepsilon^2$。

There is no theoretical prohibition on making both $\varepsilon$ and $\delta$ smaller: under these conditions, increasing the sample size permits both. The difficulty is improving precision and confidence simultaneously under a **fixed sample budget**. When $\delta\to0$, $\log(1/\delta)\to+\infty$. This says that this type of sufficient sample bound grows as confidence approaches one; it does not rule out deterministic finite-sample guarantees for every special problem.

$\varepsilon$ 和 $\delta$ 并非理论上不能同时变小：在这些条件下，可以通过增加样本量让两者都变小；困难是在**固定样本预算**下同时提高精度和置信度。$\delta\to0$ 时，$\log(1/\delta)\to+\infty$；这表示该类充分样本界在置信度趋于 1 时增大，并不是所有特殊问题都不可能在有限样本下得到确定保证。

Recruiting participants and observing patients cost resources, so how many patients are needed is a practical data-collection question. These learning bounds explain the relation between sample size and task difficulty; they should not directly serve as clinical-study sample-size formulas. Actual planning also depends on study design, effects, and other assumptions. For infinite function classes, substituting $K=\infty$ into a counting bound is invalid; an appropriate complexity measure must replace the simple count.

实验招募和观测患者都需要成本，因此“需要多少患者”也是数据采集中的现实问题。这里的学习界用于理解样本量与任务难度的关系，不应直接当作临床研究样本量公式；实际规划还取决于研究设计、效应及其他假设。对无限函数类，不能直接把 $K=\infty$ 代入计数界，需要用适当的复杂度刻画代替简单计数。

*来源：[转录 3](../01_part3.md) 第 284–332 行。*

<a id="pac-proof"></a>

<a id="section-15"></a>

## PAC bound - General case Sketch of proof

**一般情形的 PAC 界：证明概要**


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

<a id="classroom-probability-proof"></a>

**Control one function first, then all candidates**

**先控制一个函数，再控制所有候选**

For a fixed function, training error is the average sample loss and true risk is its expectation. Hoeffding's inequality bounds large deviations between them. The union bound extends a possible deviation for one candidate to whether any candidate deviates. Only a simultaneous guarantee for all candidates remains applicable after observing the data and selecting a function.

对固定函数，训练误差是样本损失的平均值，真实风险是其期望。Hoeffding 不等式控制二者偏离较大的概率；并集界则把“一个候选可能偏离”扩展到“所有候选中有没有任何一个偏离”。只有同时控制所有候选，才能在看过数据、选出函数之后继续使用这个保证。

<details>
<summary>Derivation: turning a two-sided uniform deviation into an ERM risk guarantee<br>推导：把双侧一致偏差换成 ERM 的风险保证</summary>

Assume every loss lies in $[0,1]$, samples are IID, and the candidate class is fixed in advance with size K. Controlling both deviation directions for all candidates gives

设每个损失都在 $[0,1]$ 中，样本独立同分布，候选类预先固定且大小为 K。对所有候选同时控制双侧偏差，可得

$$
\mathbb P\left(\sup_{h\in\mathcal H}|\widehat L_n(h)-L(h)|>t\right)\le 2K e^{-2nt^2}.
$$

If this uniform deviation is at most t and $\widehat h$ actually minimizes empirical risk, move from true risk to empirical risk, use empirical optimality, and then return to true risk to obtain

若这项一致偏差不超过 t，且 $\widehat h$ 确实最小化经验风险，那么先从真实风险走到经验风险，利用经验最优性，再走回真实风险，得到

$$
L(\widehat h)\le\widehat L_n(\widehat h)+t
\le\widehat L_n(\bar h)+t
\le L(\bar h)+2t.
$$

To keep within-class excess risk below $\varepsilon$, take $t=\varepsilon/2$, giving the sufficient condition $n\ge 2\log(2K/\delta)/\varepsilon^2$. Approximate optimization requires an additional optimization-error term. Nor can this bounded-loss result be applied to unbounded squared loss without further conditions.

因此要使类内超额风险不超过 $\varepsilon$，可以取 $t=\varepsilon/2$，得到一个充分条件 $n\ge 2\log(2K/\delta)/\varepsilon^2$。若优化只达到近似最优，还需要加入优化误差；无界平方损失也不能不加条件就套用上述有界损失版本。

</details>

*来源：[转录 3](../01_part3.md) 第 281–308 行。*

<a id="sampling-questions"></a>


- Proof arguments for PAC learnability (finite case)

  PAC 可学习性的证明思路（有限情形）。

- PAC : From finite to infinite collection of functions

  PAC：从有限函数集合到无限函数集合。

- From "strategies" to "learning algorithms"

  从“策略”到“学习算法”。

- What is lost through random sampling ? the sample may not contain the optimal set of "questions"....

  随机采样损失了什么？样本可能不包含最优的那组“问题”……

<a id="classroom-sampling"></a>

**Probability comes from repeated sampling; active learning changes the sampling process**

**概率来自重复采样，主动学习则改变采样方式**

The data file in front of us is fixed, but it is not the only dataset that could have been produced. For exam grades, preparation and prior knowledge are not the only influences: sleep, health, wording, and other unrecorded factors can change outcomes. A probability model describes different observations arising from the same mechanism; it does not deny that the recorded values are now fixed.

眼前的数据文件已经固定，但它并不是世界上唯一可能产生的数据集。以考试成绩为例：准备程度、既有知识以外，睡眠、健康、题目表达等未记录因素也会让结果变化。概率模型描述的是在同一机制下可能得到不同观测，而不是否认眼前记录的数值已经确定。

A training set may happen to be unrepresentative, so even carefully trained algorithms can perform poorly on other data. This is why PAC allows a probability of sampling failure. Asking only questions aimed at candidates above 70 does not effectively distinguish smaller candidates, illustrating that queries may miss the information needed. The transcript's value 344 is outside its stated 0–100 range and is not reused.

一次训练集可能恰好不具代表性，即使算法认真训练，也会在其他数据上表现不佳。这是 PAC 要容许一个抽样失败概率的原因。只问针对大于 70 的候选的问题，就无法有效区分更小的候选，这说明查询可能没有提供需要的信息；转录里出现了超出 0—100 范围的“344”，不沿用这个矛盾数字。

**Active learning** asks whether choosing which samples to label can use a budget more efficiently. This differs from passively receiving a fixed training set. Choosing queries can improve efficiency, but the benefit depends on the data, the available queries, and the learning objective.

**主动学习**进一步问：如果能选择哪些样本值得标注，能不能更有效地使用预算？这与接收一个已给定训练集的被动设定不同；选择查询有机会提高效率，但收益仍依赖数据、可查询范围和学习目标。

<details>
<summary>Application: expensive simulations, surrogate models, and sequential learning<br>应用：昂贵仿真、代理模型与序贯学习</summary>

If a physical simulation is too slow to run fully whenever a quick prediction is needed, run selected input settings first, collect input–output pairs, and train a cheaper surrogate. Since we choose experimental or simulation inputs, we can prioritize parameter locations that reduce uncertainty instead of blindly collecting more low-value samples. Active querying still requires attention to surrogate coverage and differences between the simulation and the actual target.

如果物理仿真运行很慢，无法在每次需要快速预测时完整执行，可以先运行部分输入设置，收集输入—输出对，再训练一个较便宜的代理模型。既然实验或仿真的输入由我们决定，就可以优先查询能减少不确定性的参数位置，而不是盲目堆积同样价值不高的样本。主动查询仍需注意代理模型覆盖范围，以及仿真与实际目标的差别。

Another sequential-learning setting allows an adversary to choose data to make prediction difficult, rather than assuming samples from a fixed distribution. It studies strategies that remain reliable under those conditions. Not all sequential or online learning is adversarial; this is one modeling framework. Its assumptions differ from active query selection and IID sampling, so their guarantees cannot be interchanged.

另一种序贯学习设定是：不假设样本来自固定概率分布，而是允许一个“对手”选择数据，让预测尽可能困难，从而研究在这种条件下仍可靠的策略。序贯或在线学习并不都等于对抗学习，这里举的只是其中一种建模框架。它与主动选择查询、独立同分布随机抽样的假设不同，不能混用保证。

</details>

*来源：[转录 3](../01_part3.md) 第 335–391 行。*

---

[本课目录](../01_intro_zh.md) · [上一篇：算法家族、正则化与处理流程](02_algorithms_and_pipeline.md) · [下一篇：学习对象与偏差—方差分解](04_hypotheses_and_bias_variance.md)
