# 6. 经验风险、真实风险与损失

[本课目录](../01_intro_zh.md) · [上一篇：线性模型：从拟合到预测误差](05_linear_models.md) · [下一篇：Bayes 最优、一致性与学习界](07_bayes_and_learning_bounds.md)

<a id="empirical-risk"></a>

<a id="section-18"></a>

## Supervised Machine Learning Empirical Risk Minimization (ERM)

**监督机器学习：经验风险最小化（ERM）**


- Loss function : $\ell : \mathcal { V } \times \mathcal { V }  [ 0 , + \infty ]$

  损失函数：$\ell : \mathcal { V } \times \mathcal { V }  [ 0 , + \infty ]$。

- Empirical risk of a decision rule h : this is a data-dependent functional

  决策规则 h 的经验风险：这是一个依赖于数据的泛函。

$$
\widehat {L} _ {n} (h) = \frac {1}{n} \sum_ {i = 1} ^ {n} \ell (h (X _ {i}), Y _ {i})
$$


- ERM = Empirical Risk Minimization

  ERM = Empirical Risk Minimization，即经验风险最小化。

Learning from training data amounts to solving the following optimization problem

从训练数据中学习，相当于求解下面的优化问题：

$$
\widehat {h} _ {n} = \underset {h \in \mathcal {H}} {\arg \min} \widehat {L} _ {n} (h)
$$

where the minimization is restricted to the hypothesis space.

其中最小化限制在假设空间之内。

<a id="classroom-erm"></a>

**From the cost of each prediction to selecting a rule**

**从每次预测付出的代价，到选出一条规则**

Interpret 0/1 loss as paying 0 for a correct prediction and 1 for an incorrect one. For a fixed candidate rule, add these costs over the training set and divide by n to obtain empirical risk. Two mistakes among ten samples give empirical risk $2/10=0.2$.

0/1 损失可以理解为：预测正确付 0，预测错误付 1。对同一个候选规则，把训练集上这些代价加起来再除以 n，就得到经验风险。若 10 个样本中错 2 个，经验风险为 $2/10=0.2$。

The optimization variable is the rule h, not an individual sample's label. Training compares candidates' average losses within $\mathcal H$ and chooses the smallest empirical risk. The original formula includes only fitting error; adding the earlier penalty instead compares fitting error plus complexity cost.

注意优化变量是规则 h，而不是某一个样本的标签。训练在 $\mathcal H$ 中比较候选规则各自的平均损失，选择经验风险最小者。原公式只写拟合项；若加上前面介绍的惩罚，比较的就变成拟合误差与复杂度代价之和。

This first establishes suitability for the current training set, not optimality on unseen data. Function classes, regularization, and independent evaluation jointly address that gap. Equal training losses require a selection rule, and an optimizer that has not reached the minimum cannot simply be described as exact ERM.

这个结果首先说明它适合当前训练集，并未证明它在未见数据上最好。函数类、正则化以及独立评价共同处理这个差距。若两个候选的训练损失相同，还需要明确如何选择；若数值优化没达到最小值，也不能不加说明就把输出等同于精确 ERM。

*来源：[转录 3](../01_part3.md) 第 44–71 行；[转录 3](../01_part3.md) 第 179–188 行。*

<a id="erm-questions"></a>


1. The question of consistency : convergence of $\widehat { h } _ { n }$ wrt the sample size n ?

   一致性问题：随着样本量 n 增加，$\widehat { h } _ { n }$ 是否收敛？

2. What is the cost incurred for using training data instead of the actual data ?

   使用训练数据来代替真实数据会付出怎样的代价？

3. What is the nature of the trade-off to calibrate the complexity of the hypothesis space H ?

   为调整假设空间 H 的复杂度，需要作出怎样的权衡？

<a id="over-under-fitting"></a>

![image](<../Images/01_intro/image_009.jpg>)

![image](<../Images/01_intro/image_010.jpg>)

![image](<../Images/01_intro/image_011.jpg>)

Less is more :

少即是多：


- It turns out that considering all measurable functions leads to overfitting $\Rightarrow \mathcal { H }$ has to be a restricted class !

  考虑所有可测函数会导致过拟合，因此 $\Rightarrow \mathcal { H }$ 必须是一个受限制的函数类！

But greed is good :

但“贪心”也有好处：


- Algorithms which have the capacity to overfit means they have high representation power (arbitrary small approximation error)

  一个算法具有过拟合能力，意味着它有很强的表示能力（近似误差可以任意小）。

<a id="loss-risk"></a>

<a id="section-19"></a>

## The notion of true error

**真实误差的概念**


- Assumption :

  假设：

$( X , Y )$ is a pair of random variables with joint distribution P

$( X , Y )$ 是一对联合分布为 P 的随机变量。


- True error of a decision rule h : this is a distribution-dependent functional

  决策规则 h 的真实误差：这是一个依赖于分布的泛函。

$$
L (h) = \mathbb {E} (\ell (h (X), Y)) = \int \ell (h (x), y) d P (x, y)
$$

<a id="classroom-population-risk"></a>

**The difference between an empirical average and a true expectation**

**经验平均与真实期望的区别**

Empirical risk averages the n collected samples. True risk averages all input–label pairs the target distribution may generate, weighted by their probabilities. The former is directly computable; the latter is usually unknown and must be investigated through independent evaluation data or theoretical bounds.

经验风险平均的是已收集的 n 个样本；真实风险平均的是目标分布可能产生的所有输入—标签对，并按它们出现的概率加权。前者能直接算，后者通常未知，因而要用独立评价数据或理论界研究它。

True does not mean that training records are unreal. It means extending evaluation from this finite dataset to its generating mechanism. If the deployment distribution changes, the P defining risk changes too, so yesterday's low risk does not automatically guarantee tomorrow's. This is the mathematical version of the earlier discussion of [monitoring after deployment](02_algorithms_and_pipeline.md#classroom-pipeline).

“真实”不是说训练记录不真实，而是说评价对象从这一份有限数据扩展到数据产生机制。若部署环境的分布改变了，风险所依据的 P 也变了，昨天的低风险不自动保证明天的低风险。这与前面[上线后的监控](02_algorithms_and_pipeline.md#classroom-pipeline)是同一个问题的数学表达。

*来源：[转录 3](../01_part3.md) 第 179–194 行；[转录 3](../01_part3.md) 第 335–362 行；[转录 3](../01_part3.md) 第 401–407 行。*

<a id="loss-examples"></a>

<a id="section-20"></a>

## Examples of tasks/problems

**任务／问题示例**


- Binary classification problem : Y takes 0-1 values

  二分类问题：Y 取 0、1 两个值。

$$
\ell (y, y ^ {\prime}) = \mathbb {I} \{y \neq y ^ {\prime} \} \quad \text{且} \quad L (h) = \mathbb {P} \left\{h (X) \neq Y \right\}
$$


- Regression : Y takes values in R

  回归：Y 在实数集 R 中取值。

$$
\ell (y, y ^ {\prime}) = \left(y - y ^ {\prime}\right) ^ {2} \quad \text{且} \quad L (h) = \mathbb {E} \big ((Y - h (X)) ^ {2} \big)
$$

<a id="classroom-loss-cost"></a>

**With unequal error costs, minimizing mistake counts can select the wrong objective**

**两种错误代价不同时，最小化错误次数可能选错目标**

A pedestrian-detection cost model might charge 2 euros for a missed detection, 0.5 euros for a false alarm, and 0 for a correct decision. Loss then distinguishes the combination of actual and predicted labels instead of assigning 1 to every mistake.

在行人检测的代价模型中，可以设定：漏检付 2 欧元，误报付 0.5 欧元，正确判断付 0。此时损失不再是“错一次都记 1”，而要区分实际标签与预测的组合。

| Reality<br>真实情况 | Prediction<br>模型预测 | Example loss<br>示例损失 |
|---|---|---:|
| Pedestrian present<br>有行人 | Pedestrian present<br>有行人 | 0 |
| Pedestrian present<br>有行人 | Pedestrian absent<br>无行人 | 2 |
| Pedestrian absent<br>无行人 | Pedestrian present<br>有行人 | 0.5 |
| Pedestrian absent<br>无行人 | Pedestrian absent<br>无行人 | 0 |

On the same 100 samples, suppose model A misses one pedestrian and raises four false alarms: five errors with total cost $1\times2+4\times0.5=4$. Model B misses three and raises one false alarm: four errors with total cost $3\times2+1\times0.5=6.5$. B makes fewer mistakes, but A is preferable under this loss. Their average losses are 0.04 and 0.065 respectively.

例如，在同一批 100 个样本上，模型 A 漏检 1 次、误报 4 次，共错 5 次，总代价为 $1\times2+4\times0.5=4$；模型 B 漏检 3 次、误报 1 次，共错 4 次，总代价为 $3\times2+1\times0.5=6.5$。B 的错误次数更少，但按上述损失，A 更合适。平均损失分别为 0.04 和 0.065。

Defining loss is therefore not an arbitrary preparation before mathematical derivation; it specifies what better performance means. Optimality of the Bayes rule below must likewise be understood relative to a specified loss and distribution. Changing the loss can change the optimal decision.

所以，定义损失不是公式推导之前的随意准备步骤，而是在明确“什么叫表现更好”。下方 Bayes 规则的最优性也必须相对于指定的损失和分布理解，换损失可能就换了最优决策。

*来源：[转录 1](../01_part1.md) 第 74–92 行；[转录 3](../01_part3.md) 第 47–62 行。*

---

[本课目录](../01_intro_zh.md) · [上一篇：线性模型：从拟合到预测误差](05_linear_models.md) · [下一篇：Bayes 最优、一致性与学习界](07_bayes_and_learning_bounds.md)
