# 线性模型与稀疏性

M2 CHPS · Nicolas Vayatis

> 对照来源：[原课件](<02_LM.pdf>)，共 75 页；[原文转换稿](<02_LM.md>)。按原课件顺序翻译，合并重复标题与过渡页；各节标注 PDF 页码。正文含为自学补充的解释；图解与原文勘误单独标注。原图中的英文保留，含义在图旁用中文说明。

上一篇区分了模型能力不足与有限数据估计不准。这一篇用线性回归把这两件事算清楚，再讨论变量过多、变量相关以及关系非线性时该怎样修改模型。

先沿[最小二乘与投影](#least-squares)读到[误差分解](#regression-risk)，再比较[LASSO](#lasso)与[岭回归](#ridge)。理解两种惩罚之后，进入[核方法](#kernels)。AIC 的详细推导、结构化稀疏性与对偶推导适合随后回读；相关内容仍保留在原页顺序中。

[课程目录](README.md) · [读完后检查](#self-check)

## 从什么实际问题出发（第 1–2 页）

这一篇讨论监督学习中的误差分解，随后用线性回归推导它，再研究高维情况下的变量选择、正则化和核方法。

以房价预测为例：每条成交记录包含面积、房龄等特征和成交价格，我们希望从这些记录中学习一个函数，预测新房屋的价格。后文的线性模型、稀疏性和正则化，分别回答“怎样组合这些特征”“哪些特征需要保留”“怎样避免把有限样本中的偶然差异当成规律”。

## 一般设定与符号（第 3 页）

学习的目标是最优决策函数 $h^*:\mathcal X\to\mathcal Y$，其中 $\mathcal X$ 是输入空间，$\mathcal Y$ 是标签空间。

输入包括带标签训练集

$$
D_n=\{(X_1,Y_1),\ldots,(X_n,Y_n)\}
$$

以及候选函数组成的假设空间 $\mathcal H$。输出是根据 $D_n$ 估计的函数 $\widehat h\in\mathcal H$。类内参照是 $\bar h$：假设空间中真实风险最小的函数。在合适的采样与估计条件下，更多数据可以帮助 $\widehat h$ 接近它。

## 机器学习的核心权衡（第 4 页）

用 $L(h)$ 衡量函数在真实数据分布上的误差。若最小值存在，则

$$
L(\bar h)=\inf_{h\in\mathcal H}L(h),\qquad L(h^*)=\inf_h L(h).
$$

任意学习结果满足

$$
L(\widehat h)-L(h^*)
=\underbrace{L(\widehat h)-L(\bar h)}_{\text{估计误差}}
+\underbrace{L(\bar h)-L(h^*)}_{\text{近似误差}}.
$$

![假设空间与两类误差](<Images/02_LM/image_001.jpg>)

**图解：** $h^*$ 是理想函数，$\bar h$ 是允许的模型家族中最好的函数，$\widehat h$ 是有限数据训练出的函数。图中位置关系用来示意风险差，不能直接当作函数间的欧氏距离。

假设只根据面积预测房价，真实的平均价格随面积呈弯曲变化，而模型只允许直线 $ax+b$。即使掌握了充分的数据，最好的直线也无法完全贴合真实曲线，这是近似误差。实际只有有限成交记录时，拟合出的直线还可能偏离那条最好的直线，这是估计误差。两种原因分别指向改变模型家族和改善数据。这里的风险差分解与后面平方损失下的严格偏差—方差分解有联系，但并非同一个定义。

## 关于近似误差的研究（第 5 页）

- Cybenko（1989）：由 sigmoid 与仿射函数复合后作有限线性组合，在一定条件下可对 $d$ 维单位立方体上的连续函数作一致逼近。这是类似 Stone–Weierstrass 定理的稠密性结论。
- Barron（1994）：逼近误差上界涉及描述目标函数正则性的量。
- 对回归中的核方法，课件列出 Smale（2003）、Steinwart（2008）的理论工作。
- 对深度学习，课件列出 Grohs、Perekrestenko、Elbrächter 与 Bölcskei（2019）的工作。
- 原课件将分类情形描述为困难且仍有开放问题。

**校对说明：** 这些是课件当时的文献线索和研究判断，不作为当前研究现状的全面结论。逼近定理说明某类函数可以表达目标，不保证有限样本训练能找到它。

## 回归模型与向量记法（第 6–8 页）

目标为 $h^*:\mathbb R^d\to\mathbb R$。观测是独立同分布样本，模型写成

$$
Y_i=h^*(X_i)+\varepsilon_i,\qquad i=1,\ldots,n,
$$

其中噪声与输入独立；后续推导还假设噪声均值为零。将所有样本合起来：

$$
\mathbf Y=\mathbf h^*+\varepsilon\in\mathbb R^n,
\quad \mathbf Y=(Y_1,\ldots,Y_n)^T,
\quad \varepsilon=(\varepsilon_1,\ldots,\varepsilon_n)^T.
$$

对任意 $h\in\mathcal H$，定义它在训练输入上的预测向量

$$
\mathbf h=(h(X_1),\ldots,h(X_n))^T,
\qquad \mathcal H(X)=\{\mathbf h:h\in\mathcal H\}.
$$

向量范数为 $\|u\|^2=\sum_{i=1}^n u_i^2$。

$h$ 是能接受新输入的函数，$\mathbf h$ 只是这个函数在当前 $n$ 个输入上的输出列表。例如，房价预测函数可以接受任意新房屋的特征，而预测向量列出的是当前这批房屋各自的预测价格。后面的投影就是在这些 $n$ 维预测向量组成的空间中进行的。

## 最小二乘估计与高斯线性模型（第 9–11 页）

最小二乘估计选择最接近观测的预测向量：

$$
\widehat{\mathbf h}_n\in\arg\min_{\mathbf h\in\mathcal H(X)}\frac1n\|\mathbf Y-\mathbf h\|^2.
$$

若噪声独立且服从 $\mathcal N(0,\sigma^2)$，最小二乘估计也对应回归参数的最大似然估计。课件进一步假设函数类对应一个 $d$ 维线性空间，且

$$
\varepsilon\sim\mathcal N_n(0,\sigma^2I_n).
$$

线性模型包括普通线性回归 $h(x)=\sum_{k=1}^d\beta_kx^{(k)}$，以及固定 Fourier、样条、小波等基函数后的线性展开。加性模型 $h(x)=\sum_k f_k(x^{(k)})$ 和固定分段点的分段常数回归，也可在选择适当基之后进入这个框架。

“线性”主要指对待估计系数线性。例如，可以先把面积 $x$ 变成特征 $1,x,x^2$，再写成 $h(x)=\beta_0+\beta_1x+\beta_2x^2$。它对面积是二次函数，但对待估计的系数仍然线性。

<a id="least-squares"></a>

## 线性回归的最小二乘解（第 12–14 页）

前面已经规定预测是特征的线性组合，剩下的问题是确定组合系数。把每个样本的预测误差相加，可以得到一个关于系数的二次函数；下面通过求导找到它的最小点，再解释这个解的几何含义。

设设计矩阵 $\mathbf X\in\mathbb R^{n\times d}$，第 $i$ 行为 $X_i^T$，参数 $\beta\in\mathbb R^d$。假设 $d\le n$ 且 $\operatorname{rank}(\mathbf X)=d$。

$$
\widehat\beta_n=\arg\min_\beta R(\beta),
\qquad R(\beta)=\frac1n\|\mathbf Y-\mathbf X\beta\|^2.
$$

按列向量约定求梯度：

$$
\nabla R(\beta)=\frac2n\mathbf X^T(\mathbf X\beta-\mathbf Y).
$$

令梯度为零，得到正规方程与解：

$$
\mathbf X^T\mathbf X\widehat\beta_n=\mathbf X^T\mathbf Y,
\qquad \widehat\beta_n=(\mathbf X^T\mathbf X)^{-1}\mathbf X^T\mathbf Y.
$$

因此

$$
\widehat{\mathbf h}_n=\mathbf X\widehat\beta_n=\widehat\Pi\mathbf Y,
\qquad \widehat\Pi=\mathbf X(\mathbf X^T\mathbf X)^{-1}\mathbf X^T.
$$

![最小二乘的正交投影](<Images/02_LM/image_002.jpg>)

**图解：** 设计矩阵的列张成所有可实现的训练预测向量。最小二乘把 $\mathbf Y$ 投影到这个子空间，残差与整个子空间正交。

另一种推导使用链式法则。暂省 $1/n$，令 $e(\beta)=\mathbf Y-\mathbf X\beta$、$\ell(e)=\|e\|^2$，按原文行导数约定：

$$
\frac{dR}{d\beta}=\frac{\partial\ell}{\partial e}\frac{\partial e}{\partial\beta}
=(2e^T)(-\mathbf X)=-2(\mathbf Y-\mathbf X\beta)^T\mathbf X.
$$

第 $j$ 个分量是 $\sum_{k=1}^n(\partial\ell/\partial e_k)(\partial e_k/\partial\beta_j)$。两个因子的形状分别为 $1\times n$ 和 $n\times d$。

**校对说明：** PDF 第 13 页的一阶条件漏写了 $\mathbf Y^T$ 后的 $\mathbf X$；此处已按上一行导数修正。上式是解析表达，数值实现通常求解线性系统，不要求显式构造逆矩阵。

<a id="regression-risk"></a>

## 回归中的偏差与方差（第 15–19 页）

现在先不问怎样算出解，而问这个解为何会有预测误差。将观测分成真实均值和噪声，再分别观察投影对它们的作用，就能看出模型遗漏了什么，又把多少噪声带进了预测。

这里考察在固定设计点上对无噪声均值向量的预测风险：

$$
L(\widehat{\mathbf h}_n)=\frac1n\mathbb E\|\mathbf h^*-\widehat{\mathbf h}_n\|^2.
$$

由 $\widehat{\mathbf h}_n=\widehat\Pi(\mathbf h^*+\varepsilon)$ 得

$$
\mathbf h^*-\widehat{\mathbf h}_n
=(I_n-\widehat\Pi)\mathbf h^*-\widehat\Pi\varepsilon.
$$

正交投影满足 $\widehat\Pi^2=\widehat\Pi$，且 $I_n-\widehat\Pi$ 与 $\widehat\Pi$ 的像空间正交，所以交叉项为零：

$$
L(\widehat{\mathbf h}_n)
=\underbrace{\frac1n\|(I_n-\widehat\Pi)\mathbf h^*\|^2}_{\text{平方偏差}}
+\underbrace{\sigma^2\frac dn}_{\text{方差}}.
$$

若设计也是随机的，可再对设计取期望；不能把这个固定设计结论直接当作任意新输入上的风险公式。

$d/n$ 的来源如下：若 $Z\sim\mathcal N_n(0,I_n)$，$\Pi$ 是到 $r$ 维子空间的正交投影，则

$$
\Pi Z\sim\mathcal N_n(0,\Pi),\qquad \|\Pi Z\|^2\sim\chi_r^2,
\qquad \mathbb E\|\Pi Z\|^2=r.
$$

取 $r=d$、$\varepsilon=\sigma Z$，得到 $\mathbb E\|\widehat\Pi\varepsilon\|^2=\sigma^2d$。

每增加一个可拟合方向，也给噪声增加了一个进入预测的方向。增加特征可能减少表达上的不足，却增加噪声拟合。这正是模型选择需要惩罚复杂度的原因。此处预测目标是均值；若目标是独立的新带噪观测，还需计入相应的不可约噪声。

## 从经典统计走向高维学习（第 20–25 页）

接下来的问题是：噪声不是加性的怎么办？分类等其他任务怎么办？怎样从线性扩展到非线性？非线性函数类用什么代替维度 $d$ 衡量复杂度？$d/n$ 是否仍是合适的误差尺度？若 $d>n$ 又会怎样？

高维不仅意味着 $d\gg1$，也可能意味着 $d\gg n$。参数数量与函数集合的有效复杂度需要分别考察。

![高维球的体积集中](<Images/02_LM/image_003.jpg>)

对固定 $0<\epsilon<1$，单位球外壳占总体积的比例为

$$
\frac{\operatorname{vol}(B_d(0,1)\setminus B_d(0,1-\epsilon))}{\operatorname{vol}(B_d(0,1))}
=1-(1-\epsilon)^d\longrightarrow1.
$$

**图解：** 高维球的大部分体积集中在靠近边界的薄壳中，低维几何直觉不能直接照搬。原文列出的阅读材料是 Donoho（2000）的《高维数据分析：维度的诅咒与益处》和 Vershynin（2018）的《高维概率》。

对线性回归，高维可能导致 $\mathbf X^T\mathbf X$ 病态或秩亏。秩亏时系数解不唯一，Moore–Penrose 伪逆给出最小欧氏范数解 $\widehat\beta=\mathbf X^+\mathbf Y$；拟合向量仍是到列空间的唯一正交投影。岭正则化是改善稳定性的另一条路径。

后续分为：A. 稀疏性与线性模型；B. 非线性函数估计；C. 向其他估计任务推广。

## A. 稀疏线性模型：调节模型维度（第 26–30 页）

如果大量变量只带来噪声，保留全部变量可能不如选择其中一部分。但相关变量事先未知，所以变量选择也必须进入学习过程：一种办法直接限制使用多少个变量，另一种办法对每个被使用的变量增加代价。

仍设 $\mathbf Y=\mathbf X\beta^*+\varepsilon$，噪声零均值且独立于设计。若部分变量没有信息，希望识别真正相关的变量。非零系数的位置称为支持集：

$$
m^*=\{j:\beta_j^*\ne0\}\subseteq\{1,\ldots,d\},
\qquad \|\beta\|_0=\sum_{j=1}^d\mathbf1\{\beta_j\ne0\}.
$$

$\ell_0$ 记号表示非零项计数，严格说不是范数。两种建模方式是：

$$
\text{Ivanov：}\quad\min_\beta\|\mathbf Y-\mathbf X\beta\|^2
\quad\text{满足}\quad\|\beta\|_0\le k,
\quad 0\le k\le\min(n,d),
$$

$$
\text{Tikhonov：}\quad\min_\beta\{\|\mathbf Y-\mathbf X\beta\|^2+\lambda\|\beta\|_0\},\quad\lambda>0.
$$

第一种直接限制变量数，称为最佳子集选择；第二种给每个非零系数收取代价。

**校对说明：** 原文将两种形式不等价归因于“不光滑”。关键是 $\ell_0$ 选择的非凸、离散结构，不能保证每个约束水平都有对应的惩罚系数；不光滑本身并不足以推出不等价。原文还提到前向分阶段回归等启发式方法在约 $k\simeq35$ 的规模上的经验，以及 Bertsimas 等（2016）的混合整数优化工作；这个数字是课件背景，不能当作通用规模上限。

## 稀疏惩罚为什么与方差相关（第 31–35 页）

最小二乘风险中的方差项随所用维度增长，因此考虑用 $\lambda\|\beta\|_0$ 惩罚变量数。但惩罚系数应该取多少，需要进一步推导。

令 $m\subseteq\{1,\ldots,d\}$ 表示选择的变量，全部子集组成 $\mathcal M$，总数为 $2^d$。当 $d=3$ 时，分别有 1 个空集、3 个单变量子集、3 个双变量子集和 1 个三变量子集。空集在另外保留截距时对应常数模型；没有截距时对应零预测。

取出对应列形成 $\mathbf X_m\in\mathbb R^{n\times|m|}$，在满列秩条件下

$$
\widehat\theta_n^{(m)}=(\mathbf X_m^T\mathbf X_m)^{-1}\mathbf X_m^T\mathbf Y.
$$

每个候选子模型把未选变量的系数限制为零，这不代表真实系数在这些位置一定为零。预测风险为

$$
r_m=\frac1n\mathbb E\|\mathbf X\theta^*-\mathbf X_m\widehat\theta_n^{(m)}\|^2.
$$

理论上最佳的模型 $\bar m\in\arg\min_m r_m$ 称为 oracle 参照，因为计算它需要未知真实信号。课件提出可由数据计算的选择准则：

$$
\widehat m\in\arg\min_{m\in\mathcal M}
\{\|\mathbf Y-\mathbf X_m\widehat\theta_n^{(m)}\|^2+2|m|\sigma^2\}.
$$

此处假设 $\sigma^2$ 已知。它是高斯已知方差情形下与 AIC 选模等价的形式，也与 $C_p$ 风险估计相联系。

## 选读：AIC 形式的推导（第 36–42 页）

![子模型的最小二乘投影](<Images/02_LM/image_004.jpg>)

令 $\widehat\Pi_m=\mathbf X_m(\mathbf X_m^T\mathbf X_m)^{-1}\mathbf X_m^T$，则预测为 $\widehat\Pi_m\mathbf Y$，误差分解为

$$
\mathbf X\theta^*-\widehat\Pi_m\mathbf Y
=(I_n-\widehat\Pi_m)\mathbf X\theta^*-\widehat\Pi_m\varepsilon.
$$

两项正交，因此

$$
r_m=\frac1n\|(I_n-\widehat\Pi_m)\mathbf X\theta^*\|^2+\sigma^2\frac{|m|}{n}.
$$

训练残差则满足

$$
\mathbf Y-\widehat\Pi_m\mathbf Y=(I_n-\widehat\Pi_m)(\mathbf X\theta^*+\varepsilon),
$$

$$
\frac1n\mathbb E\|\mathbf Y-\widehat\Pi_m\mathbf Y\|^2
=\frac1n\|(I_n-\widehat\Pi_m)\mathbf X\theta^*\|^2
+\sigma^2\frac{n-|m|}{n}
=r_m+\sigma^2\frac{n-2|m|}{n}.
$$

所以对每个固定候选模型，风险的无偏估计为

$$
\widehat r_m=\frac1n\|\mathbf Y-\widehat\Pi_m\mathbf Y\|^2
+\sigma^2\frac{2|m|-n}{n}.
$$

去掉对所有模型相同的常数并乘以 $n$，便得到前面的选模准则。选读部分到此结束。

增加一个变量会让训练残差变小，即使它只拟合了噪声。修正项补偿这种乐观偏差。单个固定模型的无偏性，不意味着在许多模型中选出最小值之后仍然无偏。

**校对说明：** PDF 第 39–40 页的卡方陈述漏了尺度：应是 $\|\widehat\Pi_m\varepsilon\|^2/\sigma^2\sim\chi^2_{|m|}$，以及 $\|(I_n-\widehat\Pi_m)\varepsilon\|^2/\sigma^2\sim\chi^2_{n-|m|}$；第二式还需括号。这里采用修正后的推导。

## 高维选模的计算代价与凸松弛（第 43–45 页）

即使准则可以计算，遍历所有子集也不可行：共有 $2^d$ 个子集，大小接近 $d/2$ 的子集数量为 $\binom d{\lfloor d/2\rfloor}$，按 Stirling 近似约为 $2^d\sqrt{2/(\pi d)}$。原文的“约 $e^{d/2}$”只能表达指数增长的意图，不是这个计数的准确渐近式。

实际方法常用逐次加入或删除变量的贪心策略，例如前向分阶段回归和前向—后向算法，只探索部分子集。另一条路线是同时估计系数与非零位置：把非凸的 $\ell_0$ 惩罚替换为凸的 $\ell_1$ 惩罚。

<a id="lasso"></a>

## LASSO 与正则化路径（第 46–48 页）

定义 $\|\beta\|_1=\sum_{j=1}^d|\beta_j|$。LASSO 估计为

$$
\widehat\beta_\lambda\in\arg\min_\beta
\{\|\mathbf Y-\mathbf X\beta\|^2+\lambda\|\beta\|_1\},\qquad\lambda>0.
$$

![LASSO 正则化路径](<Images/02_LM/image_005.jpg>)

**图解：** 改变惩罚强度，会得到一系列系数向量 $\lambda\mapsto\widehat\beta_\lambda$。图中的曲线追踪各个系数如何进入、退出或缩小。$\ell_1$ 在零点的折角使部分系数可以精确为零。

课件给出如下形式的预测误差上界：

$$
\frac1n\mathbb E\|\mathbf X\beta^*-\mathbf X\widehat\beta\|^2
\le C\|\beta^*\|_1\sqrt{\frac{\log d}{n}}.
$$

**校对说明：** 原页没有列出完整条件；此类结论依赖设计归一化、噪声假设及 $\lambda$ 的选择，不能对任意数据直接套用。

由此得到通用形式：

$$
\operatorname{Criterion}(h)=\text{训练误差}(h)+\lambda\,\text{惩罚}(h).
$$

训练误差由损失函数决定，惩罚控制函数复杂度或结构，$\lambda$ 通常通过交叉验证选择。

## 结构化稀疏性：Group LASSO 与 Fused LASSO（第 49–52 页）

![不同的稀疏结构](<Images/02_LM/image_006.jpg>)

**图解：** 稀疏性可以作用于单个系数，也可以要求按组、按空间或时间结构保留系数。结构惩罚把已有的领域知识写进目标函数。

把变量划成 $G$ 组，组 $g$ 大小为 $d_g$，对应设计子矩阵 $\mathbf X^{(g)}$ 和系数 $\beta^{(g)}$。Group LASSO 为

$$
\widehat\beta_\lambda\in\arg\min_\beta
\left\{\|\mathbf Y-\mathbf X\beta\|^2
+\lambda\sum_{g=1}^G\sqrt{d_g}\|\beta^{(g)}\|_2\right\}.
$$

组内采用欧氏范数、组间求和，鼓励整组归零，而不是要求被选中组内部也稀疏。例如同一测量来源的多个特征可以作为一组；是否合理取决于任务。

若系数有时间顺序，希望相邻位置保持一致，可用 Fused LASSO：

$$
\widehat\beta\in\arg\min_\beta
\left\{\|\mathbf Y-\mathbf X\beta\|^2+\lambda\|\beta\|_1
+\mu\sum_{j=2}^d|\beta_j-\beta_{j-1}|\right\}.
$$

![Fused LASSO 的分段常数信号恢复](<Images/02_LM/image_007.jpg>)

**图解：** 灰点是带噪信号，红线是分段常数的拟合。最后一项惩罚相邻差异，鼓励分段常数结构；顺序必须有实际含义。

<a id="ridge"></a>

## 岭回归：解决不适定与不稳定（第 53–57 页）

前面的稀疏方法关注哪些变量应当保留。另一种困难是：多个变量高度相关，稍微改变数据，拟合系数就可能变化很大。岭回归通过惩罚过大的系数来稳定估计，即使不删除变量，也可能降低预测误差。

正则化思想可追溯到 20 世纪 60 年代的 Ivanov、John、Lavrent’ev、Tikhonov 等工作，用来稳定不适定问题的解。

当 $d>n$ 时，$\mathbf X^T\mathbf X$ 不可逆，最小二乘系数有无穷多个解。岭回归加入平方范数惩罚：

$$
\widehat\beta_\lambda=\arg\min_\beta
\{\|\mathbf Y-\mathbf X\beta\|^2+\lambda\|\beta\|_2^2\},\quad\lambda>0.
$$

令 $F(\beta)=(\mathbf Y-\mathbf X\beta)^T(\mathbf Y-\mathbf X\beta)+\lambda\beta^T\beta$，则

$$
\nabla F(\beta)=2\mathbf X^T(\mathbf X\beta-\mathbf Y)+2\lambda\beta=0,
$$

$$
\widehat\beta_\lambda=(\mathbf X^T\mathbf X+\lambda I_d)^{-1}\mathbf X^T\mathbf Y.
$$

由于 $\lambda>0$，矩阵正定，解唯一。但当 $d$ 很大时，求解 $d\times d$ 系统仍可能昂贵。

岭回归抑制过大的系数、稳定相关特征下的估计，通常不把系数精确变成零。公式假设全部系数受罚；若包含通常不惩罚的截距，需要相应调整。

## 岭回归的对偶问题（第 58–60 页）

同一个预测函数可以按特征系数表示，也可以借助训练样本表示。对偶推导从第一种写法走向第二种写法；这样既能比较两种线性系统的大小，也能看清哪些地方只用到了内积。后面的核方法就从这里接上。

引入残差 $r=\mathbf X\beta-\mathbf Y$：

$$
\min_{\beta,r}\frac12\|r\|^2+\frac\lambda2\|\beta\|^2,
\qquad r=\mathbf X\beta-\mathbf Y.
$$

拉格朗日函数为

$$
\mathcal L(\beta,r,\alpha)=\frac12\|r\|^2+\frac\lambda2\|\beta\|^2
+\alpha^T(r-\mathbf X\beta+\mathbf Y).
$$

对原变量求驻点得 $\beta(\alpha)=\mathbf X^T\alpha/\lambda$、$r(\alpha)=-\alpha$。代回得到要最大化的对偶函数

$$
g(\alpha)=\alpha^T\mathbf Y-\frac12\|\alpha\|^2-\frac1{2\lambda}\|\mathbf X^T\alpha\|^2.
$$

于是

$$
\widehat\alpha=\lambda(\mathbf X\mathbf X^T+\lambda I_n)^{-1}\mathbf Y,
\qquad\widehat\beta=\frac1\lambda\mathbf X^T\widehat\alpha.
$$

新输入的预测是

$$
x^T\widehat\beta=\frac1\lambda\sum_{i=1}^n\widehat\alpha_i\,x^TX_i.
$$

恒等式

$$
\mathbf X^T(\mathbf X\mathbf X^T+\lambda I_n)^{-1}
=(\mathbf X^T\mathbf X+\lambda I_d)^{-1}\mathbf X^T
$$

说明原始解和对偶解相同。

原问题围绕 $d$ 个特征系数组织，对偶围绕 $n$ 个样本系数组织。若 $n\ll d$，求解较小的 $n\times n$ 系统可能更方便。更关键的是，训练与预测只需要样本间的内积，为核方法留下了入口。

**校对说明：** PDF 第 59 页代回拉格朗日函数时漏写 $\|\mathbf X^T\alpha\|$ 的平方；上面给出补全并整理后的对偶函数。

## Elastic Net 与超参数（第 61–63 页）

Zou 与 Hastie（2005）讨论了 LASSO 的几个局限：在常见条件下，当变量数大于样本数时，其稀疏解的活跃变量数受到样本数限制；强相关变量中可能只选一个且选择不稳定；相关性强时，岭回归可能有更好的预测表现。原图引用中的“不良定义”应结合原论文条件理解，不能说 LASSO 一般不存在解或总是不唯一。

Elastic Net 组合两种惩罚：

$$
\widehat\beta\in\arg\min_\beta
\{\|\mathbf Y-\mathbf X\beta\|^2+\lambda\|\beta\|_1+\mu\|\beta\|_2^2\}.
$$

![LASSO 系数路径](<Images/02_LM/image_008.jpg>)

![Elastic Net 系数路径](<Images/02_LM/image_009.jpg>)

**图解：** 两幅路径图用于比较不同惩罚下系数的进入与变化；Elastic Net 同时保留稀疏选择和平方惩罚的稳定作用，相关变量更可能一起进入。具体路径取决于数据及横轴参数化。

$\lambda,\mu$ 是超参数，也称平滑或正则化参数，通常用交叉验证选择。它们不应通过最终测试集调节。

## 练习：三种惩罚的区别（第 64 页）

设 $Y\sim\mathcal N(\beta^*,1)$，$\beta\in\mathbb R$。分别求解

$$
\text{(i)}\ \frac12(Y-\beta)^2+\lambda\mathbf1\{\beta\ne0\},\qquad
\text{(ii)}\ \frac12(Y-\beta)^2+\lambda|\beta|,\qquad
\text{(iii)}\ \frac12(Y-\beta)^2+\lambda\beta^2.
$$

将估计量画成无约束最小二乘解 $Y$ 的函数，解释硬阈值、软阈值与收缩。

**校对说明：** 原页 (i) 只有常数 $+\lambda$，按字面最小值总在 $\beta=Y$，不会产生题目要求的硬阈值。上式根据“比较三种惩罚”的题意补上指示函数，属于明确标注的题意修复。对应关系是：硬阈值在 $|Y|>\sqrt{2\lambda}$ 时保留 $Y$，低于阈值时置零，等号时两解并存；软阈值为 $\operatorname{sgn}(Y)(|Y|-\lambda)_+$；平方惩罚给出 $Y/(1+2\lambda)$。

<a id="kernels"></a>

## B. 从非线性输入关系到线性特征模型（第 65–66 页）

线性回归允许我们先构造特征，再学习系数。因此不必立刻放弃已有求解方法：先把输入映射到能表达弯曲关系的特征，再问这些特征的内积能否直接计算。下面的二次多项式把这一步写出来。

二维输入的二次多项式可写成六维特征：

$$
\Phi(x_1,x_2)=(1,\sqrt2x_1,\sqrt2x_2,\sqrt2x_1x_2,x_1^2,x_2^2)^T.
$$

直接展开可验证

$$
\Phi(x)^T\Phi(x')=(x^Tx'+1)^2=:K(x,x').
$$

$K$ 称为多项式核。它通过原输入直接计算高维特征空间的内积，不必显式列出所有特征。

**校对说明：** 原页写 $d'=7$，但列出的特征恰好六个；应为 $d'=6$。

## 核岭回归（第 67 页）

岭回归对偶中，把 $X_i^TX_j$ 替换为 $K(X_i,X_j)$，便得到核版本。定义 Gram 矩阵 $\mathbf K_{ij}=K(X_i,X_j)$，用吸收尺度后的系数 $c$ 表示：

$$
c=(\mathbf K+\lambda I_n)^{-1}\mathbf Y,
\qquad f(x)=\sum_{i=1}^n c_iK(x,X_i).
$$

这里的 $c$ 对应前面线性对偶的 $\widehat\alpha/\lambda$，避免混淆不同页的系数约定。

算法仍求解一个 $n\times n$ 系统，预测仍是与训练样本相似度的加权和，但它可以表达原输入空间中的非线性函数。原文说算法复杂度不变，指这种求解结构没有改变；核计算成本、存储和样本数规模仍需考虑。

## 常见核、核距离与序列核（第 68–70 页）

- 线性核：$K(x,z)=x^Tz$。
- 多项式核：$K(x,z)=(x^Tz)^q$ 或 $(1+x^Tz)^q$，$q$ 为非负整数。
- 高斯核：$K(x,z)=\exp(-\|x-z\|_2^2/(2\sigma^2))$。
- 原课件的 Laplace 核参数化：$K(x,z)=\exp(-\|x-z\|_2/(2\sigma^2))$；这里分母是尺度参数，不应机械等同于高斯方差。

![特征映射与核诱导的距离](<Images/02_LM/image_010.jpg>)

核诱导的特征距离满足

$$
\begin{aligned}
d_K(x_1,x_2)^2
&=\|\Phi(x_1)-\Phi(x_2)\|_{\mathcal H}^2\\
&=\langle\Phi(x_1),\Phi(x_1)\rangle+\langle\Phi(x_2),\Phi(x_2)\rangle
-2\langle\Phi(x_1),\Phi(x_2)\rangle\\
&=K(x_1,x_1)+K(x_2,x_2)-2K(x_1,x_2).
\end{aligned}
$$

仅用核值就能计算特征空间距离。若不同输入被映到同一点，它在原输入空间只是伪度量。

文本、生物序列等结构化对象也能定义核。例如字符串 `CGGSLIAMMWFGV` 的连续长度 3 子串为 `CGG, GGS, GSL, SLI, LIA, IAM, AMM, MMW, MWF, WFG, FGV`。令 $\Phi_u(x)$ 表示子串 $u$ 在 $x$ 中出现的次数，则

$$
K(x,x')=\sum_{u\in A^k}\Phi_u(x)\Phi_u(x')
$$

是 $k$-spectrum 核，$A$ 为字母表。原文将示例称为 DNA 序列，但其字符不限于 DNA 碱基字母，故此处按一般生物序列字符串理解。

## 核估计是否可计算，以及其他损失（第 71–75 页）

核提供了灵活的建模方式，接下来仍需判断惩罚最小二乘是否可实际求解。除了改变惩罚，也可改变数据拟合项，适应不同任务：

$$
\text{岭回归：}\quad\min_\beta\frac1n\sum_{i=1}^n\frac12(y_i-\beta^Tx_i)^2+\lambda\|\beta\|_2^2,
$$

$$
\text{线性 SVM：}\quad\min_\beta\frac1n\sum_{i=1}^n\max(0,1-y_i\beta^Tx_i)+\lambda\|\beta\|_2^2,
$$

$$
\text{逻辑回归：}\quad\min_\beta\frac1n\sum_{i=1}^n\log(1+e^{-y_i\beta^Tx_i})+\lambda\|\beta\|_2^2.
$$

后两式采用 $y_i\in\{-1,+1\}$。

![不同损失函数的比较](<Images/02_LM/image_011.jpg>)

**图解：** 不同损失给同一种预测偏差赋予不同代价。平方损失适合这里的连续值回归；hinge 和 logistic 损失通过有符号间隔 $y_if(x_i)$ 评价分类。符号相同不代表任务和评价目标相同。

后续课程继续讨论线性分类、特征工程、变量选择、表示学习，以及从线性模型迁移到非线性模型时能够保留的结构。

<a id="self-check"></a>

## 读完后检查

下面的问题用于自检，不是新增的原课件考题。先尝试用自己的话作答，再回到相应推导检查。

1. 最小二乘中的设计矩阵、参数向量和预测向量，各自收集了什么？为什么“系数有多个解”不一定意味着训练点上的拟合向量也不唯一？
2. 当变量数多于样本数时，原来的求逆公式哪里失效？伪逆、岭回归和变量选择分别增加了什么约定或约束？
3. LASSO 与岭回归都能缩小系数，为什么前者还可能把部分系数精确压到零？请回看一维阈值练习。
4. 核岭回归保留了哪个求解结构，又改变了模型允许表达的函数？这里的“对参数线性”和“对原始输入线性”是否相同？

下一篇[分类问题与参数化方法](03_LMC_zh.md)把输出从连续数值改为类别，继续考察概率、决策和损失怎样对应。
