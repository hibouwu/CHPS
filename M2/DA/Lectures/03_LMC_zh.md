# 分类问题与参数化方法

M2 CHPS · Nicolas Vayatis

> 对照来源：[原课件](<03_LMC.pdf>)，共 69 页；[原文转换稿](<03_LMC.md>)。按原课件顺序翻译，合并重复标题与过渡页，保留全部原图。**理解、图解、校对说明**为补充，实质性公式修正在对应位置注明。

## 分类数据与实际决策（第 1–4 页）

原课件列举三个任务：医学诊断中，$X$ 是检查结果，$Y=+1$ 表示健康，$Y=-1$ 表示不健康；信用风险中，$X$ 是个人社会经济数据，$Y=+1$ 表示借款人可靠；垃圾邮件识别中，$X$ 是邮件描述特征，$Y=+1$ 表示垃圾邮件。

同样的数据可以支持两种不同决策：

- **分类：** 预测新对象的类别，希望分类错误率低。
- **评分与排序：** 给对象打分并排序，希望正例尽可能排在前面。

**理解：** 以垃圾邮件识别为例，“这封邮件是否进入垃圾箱”要求给出类别，是分类；“把最可疑的邮件排在前面，供人优先检查”要求给出顺序，是评分与排序。前者关心每封邮件是否判对，后者关心垃圾邮件是否排在正常邮件前面。

本篇依次介绍概率模型、分类评价、LDA/QDA、Fisher 判别分析、逻辑回归、ROC/AUC、感知机和最大间隔分类。

## 分类的概率模型（第 5–8 页）

设 $(X,Y)$ 服从未知联合分布 $P$，$X\in\mathcal X$（例如 $\mathbb R^d$），暂取二元标签 $Y\in\{-1,+1\}$。

**生成式描述**先给出类别先验及类条件分布：

$$
p=\mathbb P(Y=+1),\qquad P_+=\mathcal L(X\mid Y=+1),\quad P_-=\mathcal L(X\mid Y=-1).
$$

它对应联合分布的分解 $P(dx,dy)=P_Y(dy)P_{X\mid Y}(dx\mid y)$。

**判别式描述**关注输入边际分布 $P_X$ 和给定输入后的标签概率：

$$
\eta(x)=\mathbb P(Y=+1\mid X=x).
$$

它对应 $P(dx,dy)=P_X(dx)P_{Y\mid X}(dy\mid x)$。这里是条件分布分解，不能把原文的乘积符号理解为 $X,Y$ 独立。

若类条件密度为 $f_+,f_-$，则

$$
f_X(x)=pf_+(x)+(1-p)f_-(x),
\qquad\eta(x)=\frac{pf_+(x)}{pf_+(x)+(1-p)f_-(x)}.
$$

在分母非零处，$\eta(x)>1/2$ 等价于 $pf_+(x)>(1-p)f_-(x)$。

**理解：** 生成式方法先问“各类会产生怎样的输入”，再由 Bayes 公式判断类别；判别式方法直接建模“看到这个输入后，各类别有多大可能”。

## 二分类、训练误差与泛化（第 9–15 页）

给定 $(x_i,y_i)_{i=1}^n$，希望学习 $g:\mathbb R^d\to\{-1,+1\}$，使它能预测未见数据。常先学习实值决策函数 $f$，再令 $g=\operatorname{sgn}(f)$；零点如何归类需要约定。

训练错误率为

$$
\widehat L_n(g)=\frac1n\sum_{i=1}^n\mathbf1\{g(x_i)\ne y_i\}
=\frac{\#\{i:g(x_i)\ne y_i\}}n.
$$

低训练误差只说明当前样本拟合得好，不足以说明真实风险 $L(g)=\mathbb P(g(X)\ne Y)$ 小。

![分类边界的过拟合](<Images/03_LMC/image_001.jpg>)

![欠拟合、过拟合与适中复杂度](<Images/03_LMC/image_002.jpg>)

**图解：** 过于简单的边界不能分开主要结构；为了围住每个训练样本而不断弯曲的边界，又可能把偶然点当成规律。图中的新样本提示我们，训练点上的正确性不等于新点上的正确性。

![复杂度与风险控制](<Images/03_LMC/image_003.jpg>)

**图解：** 随函数类扩大，经验风险通常下降，但控制经验误差与真实风险差距的项可能增加。图是权衡示意，不保证所有实际学习曲线都是同样的 U 形。

留出法把数据分成训练集与独立测试集。训练好 $g$ 后，用

$$
\widehat L'_m(g)=\frac1m\sum_{j=1}^m\mathbf1\{g(X_{n+j})\ne Y_{n+j}\}
$$

估计风险。在独立同分布且测试集不参与训练、选模的条件下，可对训练集条件化来理解此估计。原文进一步提出交叉验证以减少对一次划分的依赖。

**补充：** 调超参数时使用验证集或交叉验证，最终测试集保留到最后；反复按测试结果选模型会使它失去独立评价作用。

## 方法一：多元高斯与混合模型（第 16–19 页）

统一采用列向量，多元高斯密度为

$$
\mathcal N(x;\mu,\Sigma)=\frac1{(2\pi)^{d/2}|\Sigma|^{1/2}}
\exp\left[-\frac12(x-\mu)^T\Sigma^{-1}(x-\mu)\right].
$$

其中 $\mu\in\mathbb R^d$，$\Sigma\in\mathbb R^{d\times d}$ 为正定协方差矩阵，$|\Sigma|$ 是行列式。对 $m$ 个独立样本，最大似然估计为

$$
\widehat\mu=\frac1m\sum_{j=1}^m x^{(j)},\qquad
\widehat\Sigma=\frac1m\sum_{j=1}^m(x^{(j)}-\widehat\mu)(x^{(j)}-\widehat\mu)^T.
$$

这是分母为 $m$ 的最大似然估计，不是分母 $m-1$ 的无偏协方差估计。

![多元高斯的密度与等高线](<Images/03_LMC/image_004.jpg>)

![二维混合模型的数据与等高线](<Images/03_LMC/image_005.jpg>)

![二维混合模型的密度曲面](<Images/03_LMC/image_006.jpg>)

**图解：** 均值确定云团中心，协方差决定延伸方向与离散程度；多个高斯分量加权叠加后，可以形成多个峰。

多分类时设 $Y\in\{1,\ldots,K\}$，$X\mid Y=k\sim\mathcal N(m_k,\Sigma_k)$，密度为 $f_k$，先验为 $\pi_k$。后验为

$$
\eta_k(x)=\mathbb P(Y=k\mid X=x)=\frac{\pi_kf_k(x)}{\sum_{j=1}^K\pi_jf_j(x)}.
$$

**校对说明：** 原页把 $X\mid Y=k$ 称作“后验分布”，实际应为类条件分布；$Y\mid X=x$ 才是这里用于分类的后验。

## 线性判别分析 LDA（第 20–21 页）

假设所有类别共享协方差 $\Sigma_k=\Sigma$。则

$$
\begin{aligned}
\log\frac{\eta_k(x)}{\eta_j(x)}
&=\log\frac{\pi_kf_k(x)}{\pi_jf_j(x)}\\
&=x^T\Sigma^{-1}(m_k-m_j)
-\frac12(m_k^T\Sigma^{-1}m_k-m_j^T\Sigma^{-1}m_j)
+\log\frac{\pi_k}{\pi_j}.
\end{aligned}
$$

它对 $x$ 是仿射函数。因此可比较

$$
\delta_k(x)=x^T\Sigma^{-1}m_k-\frac12m_k^T\Sigma^{-1}m_k+\log\pi_k,
\qquad g(x)\in\arg\max_k\delta_k(x).
$$

![高斯类别与判别区域](<Images/03_LMC/image_007.jpg>)

**理解：** 两个类条件高斯的二次项因共享协方差而抵消，留下线性边界。“线性”是由这个抵消推出来的，不是额外硬加的直线。

**校对说明：** PDF 第 20 页第一行右侧漏了对数，常数项又误写成两个 $(m_k+m_j)$ 的乘积；正确形式如上，也可写为 $-\tfrac12(m_k+m_j)^T\Sigma^{-1}(m_k-m_j)$。

## 二次判别分析 QDA 及协方差正则化（第 22–23 页）

若各类协方差不同，判别函数变为

$$
\delta_k(x)=-\frac12(x-m_k)^T\Sigma_k^{-1}(x-m_k)
+\log\pi_k-\frac12\log\det\Sigma_k.
$$

二次项不再普遍抵消，所以边界通常是二次曲面。代价是每类都要估计协方差，高维时数据需求更大。

原文提出在共享协方差与各类协方差之间插值（Friedman，1989）：

$$
\widehat\Sigma_k(\lambda)=\lambda\widehat\Sigma_k+(1-\lambda)\widehat\Sigma,
\qquad0\le\lambda\le1.
$$

**校对说明：** 原式右边第一项也写了 $(\lambda)$，造成自引用；此处改为未经这一步收缩的类内估计。$\lambda=0$ 使用共享协方差，$\lambda=1$ 使用各类协方差；还可考虑其他正则化或稀疏结构。插值本身不保证高维秩亏完全解决。

## 方法二：Fisher 判别分析 FDA（第 24–27 页）

原课件从两类高斯出发，寻找一个投影方向，使投影后的类中心尽量远，同时每类内部尽量集中。

![投影后类别重叠较多的方向](<Images/03_LMC/image_008.jpg>)

![投影后类别分离较好的方向](<Images/03_LMC/image_009.jpg>)

**图解：** 相同二维点云，沿不同方向投影会产生不同重叠。只追求两个投影均值远还不够，还应考虑各自的分散程度。

对 $i=1,2$，均值估计为 $\widehat\mu_i$。给定方向 $u$，投影均值与类内离差平方和为

$$
m_i(u)=u^T\widehat\mu_i,\qquad
\widehat S_i^2(u)=\sum_{j:Y_j=i}(u^TX_j-m_i(u))^2.
$$

最大化 Fisher 准则

$$
J(u)=\frac{(m_1(u)-m_2(u))^2}{\widehat S_1^2(u)+\widehat S_2^2(u)}
=\frac{u^TS_Bu}{u^TS_Wu},
$$

其中

$$
S_B=(\widehat\mu_1-\widehat\mu_2)(\widehat\mu_1-\widehat\mu_2)^T,
\quad S_W=\sum_{i=1}^2\sum_{j:Y_j=i}(X_j-\widehat\mu_i)(X_j-\widehat\mu_i)^T.
$$

拉格朗日法给出广义特征值问题 $S_Bu=\lambda S_Wu$。若 $S_W$ 可逆且两类均值不同，则最佳方向满足

$$
u\propto S_W^{-1}(\widehat\mu_1-\widehat\mu_2).
$$

方向确定后仍要选择分类阈值。FDA 关注有标签的类间分离，PCA 关注无标签的总体方差，两者一般不同。这个样本准则本身不要求数据必须高斯；高斯是假设解释的一种背景。

## 方法三：逻辑回归（第 28–29 页）

对 $K$ 类，直接假设相对参考类 $K$ 的对数优势比为线性函数：

$$
\log\frac{\eta_k(x)}{\eta_K(x)}=\theta_k^Tx,\qquad k=1,\ldots,K-1.
$$

因此

$$
\eta_k(x)=\frac{\exp(\theta_k^Tx)}{1+\sum_{j=1}^{K-1}\exp(\theta_j^Tx)},\quad k<K,
\qquad\eta_K(x)=\frac1{1+\sum_{j=1}^{K-1}\exp(\theta_j^Tx)}.
$$

**校对说明：** 参考类应取 $\theta_K=0$，原文的 $\theta_K=1$ 不正确。若需要截距，可以在输入中添加常数特征。

**理解：** LDA 通过输入的类条件分布推出后验；逻辑回归直接限制后验的对数优势比。逻辑回归是判别式方法，并不要求输入服从高斯。

## 逻辑回归的拟合与数值求解（第 30–31 页）

记所有参数为 $\theta=(\theta_1,\ldots,\theta_{K-1})$，概率为 $p_k(x,\theta)$。正确的对数似然是

$$
\ell(\theta)=\sum_{i=1}^n\log p_{Y_i}(X_i,\theta).
$$

原式的固定下标 $k$ 应随样本真实类别取值。二分类推导改用 $Y_i\in\{0,1\}$，令 $p(x,\theta)=1/(1+e^{-\theta^Tx})$：

$$
\begin{aligned}
\ell(\theta)
&=\sum_i[Y_i\log p(X_i,\theta)+(1-Y_i)\log(1-p(X_i,\theta))]\\
&=\sum_i[Y_i\theta^TX_i-\log(1+e^{\theta^TX_i})].
\end{aligned}
$$

得分方程、Hessian 和 Newton 更新为

$$
\nabla\ell(\theta)=\sum_iX_i(Y_i-p(X_i,\theta)),
$$

$$
H_\ell(\theta)=-\sum_iX_iX_i^Tp(X_i,\theta)(1-p(X_i,\theta)),
$$

$$
\theta_{t+1}=\theta_t-H_\ell(\theta_t)^{-1}\nabla\ell(\theta_t).
$$

该迭代可写成迭代重加权最小二乘。它使用当前概率更新权重，再求解下一步参数。Hessian 可逆等条件需要检查；完全可分的数据在无正则化时可能不存在有限的最大似然参数。

## 参数模型的局限（第 32 页）

原课件提醒：“所有模型都有偏差，但有些模型有用。”高斯、线性等先验降低了学习难度，同时也可能限制真实关系的表达；高维还会增加估计难度，即维数灾难（Bellman）。

**校对说明：** 本页原题为“生成式方法的局限”，但前一节逻辑回归并非生成式方法。这里讨论的建模与维度限制有些适用于更广泛的参数模型，不能据标题把逻辑回归归为生成式。

## 从分类到评分：两类错误（第 33–35 页）

分类错误可分为误报与漏报：

$$
L(g)=\mathbb P(g(X)=+1,Y=-1)+\mathbb P(g(X)=-1,Y=+1).
$$

假阳性率和真阳性率分别为

$$
\alpha(g)=\mathbb P(g(X)=+1\mid Y=-1),\qquad
\beta(g)=\mathbb P(g(X)=+1\mid Y=+1).
$$

所以

$$
L(g)=(1-p)\alpha(g)+p(1-\beta(g)).
$$

在 $0<p<1$ 时，固定错误率对应 $\alpha$–$\beta$ 平面上的直线：

$$
\beta=\frac{1-p}{p}\alpha+1-\frac Lp.
$$

![假阳性率与真阳性率平面的等错误率线](<Images/03_LMC/image_010.jpg>)

**图解：** 横轴是误报率，纵轴是检出率；向左上方移动更有利。同一分类错误率对应怎样的直线，还取决于正例比例 $p$。

## Neyman–Pearson 分类（第 36–38 页）

考虑检验 $H_0:Y=-1$ 对 $H_1:Y=+1$。最优似然比统计量为

$$
T^*(x)=\frac{f_+(x)}{f_-(x)}=\frac{1-p}{p}\frac{\eta(x)}{1-\eta(x)}.
$$

此处 $\alpha$ 是第一类错误率，$\beta$ 是检验功效。固定允许的误报水平 $\alpha$ 后，在连续情形可选择

$$
R_\alpha^*=\{x:\eta(x)>Q^-(\eta,\alpha)\},
\qquad g_\alpha^*(x)=2\mathbf1\{x\in R_\alpha^*\}-1,
$$

其中 $Q^-$ 是负类中 $\eta(X)$ 分布的 $1-\alpha$ 分位数。存在离散原子时，可能需要在阈值处随机化才能精确达到指定误报率。

![固定误报率下的最优检出率](<Images/03_LMC/image_011.jpg>)

记 $\beta^*(\alpha)=\beta(g_\alpha^*)$。这种规则最优化的是“误报受限时尽量检出”，不一定最小化总体分类错误率。Bayes 分类在对称错误代价下使用 $\eta=1/2$ 的阈值。

**校对说明：** 原文说只有分位数恰为 $1/2$ 才能达到 Bayes 风险，表述过强：不同阈值若在有概率质量的区域产生同一决策，也可能达到同样风险。

## ROC 曲线与最优评分（第 39–41 页）

令评分 $s:\mathbb R^d\to\mathbb R$，超过阈值 $t$ 时报警：

$$
\beta(s,t)=\mathbb P(s(X)\ge t\mid Y=+1),\qquad
\alpha(s,t)=\mathbb P(s(X)\ge t\mid Y=-1).
$$

降低阈值最终使两者都趋于 1；提高阈值最终使两者都趋于 0。因此检出与误报必须共同评价。

![正负类评分分布的重叠](<Images/03_LMC/image_012.jpg>)

![不同分离程度的理想 ROC 曲线](<Images/03_LMC/image_013.jpg>)

ROC 是固定评分规则下，改变阈值得到的曲线：

$$
t\longmapsto(\alpha(s,t),\beta(s,t)).
$$

**图解：** 正负类评分重叠越少，越容易在较低误报下获得较高检出。对角线对应没有排序区分能力的基准，左上角是理想方向。

后验概率 $\eta(x)$ 的严格递增变换保留排序，因此具有同样的最优 ROC 表现。评分不必本身等于概率才能正确排序。

## ROC 曲线下面积 AUC（第 42 页）

对独立同分布的 $(X,Y),(X',Y')$，

$$
\begin{aligned}
\operatorname{AUC}(s)
&=\int_0^1\operatorname{ROC}(s,\alpha)\,d\alpha\\
&=\mathbb P(s(X)>s(X')\mid Y>Y')
+\frac12\mathbb P(s(X)=s(X')\mid Y>Y').
\end{aligned}
$$

**理解：** 随机取一个正例和一个负例，AUC 衡量正例得分更高的概率；打平记半分。它不是某个固定阈值的分类准确率。

当 $0<p<1$ 时，最优 AUC 为

$$
\operatorname{AUC}^*=\operatorname{AUC}(\eta)
=\frac12+\frac{\mathbb E|\eta(X)-\eta(X')|}{4p(1-p)}.
$$

最优 ROC 包络与候选 ROC 间的面积差，可以解释为相应的 $L_1$ 差距；任意两条相交 ROC 曲线拥有相近 AUC，并不意味着两曲线接近。

## 全局评价与局部评价（第 43–47 页）

原课件列出 ROC、Precision–Recall（精确率—召回率）和 Lift（提升）曲线，以及全局 AUC、部分 AUC（Dodd 与 Pepe，2003）和局部 AUC（Clémençon 与 Vayatis，2007）。

![一条 ROC 整体优于另一条](<Images/03_LMC/image_014.jpg>)

![两条 ROC 相交](<Images/03_LMC/image_015.jpg>)

**图解：** 整体占优时容易比较；曲线相交时，优劣取决于工作区间，不能只看一个全局面积。

![部分 AUC 的阴影区域](<Images/03_LMC/image_016.jpg>)

![不同评分规则与筛选比例的关系](<Images/03_LMC/image_017.jpg>)

![局部 AUC 的示意区域](<Images/03_LMC/image_018.jpg>)

**图解：** 图中下降直线表示固定筛选比例，例如 $p\,\mathrm{TPR}+(1-p)\,\mathrm{FPR}=10\%$。相同筛选预算与相同 FPR 截断不是同一个约束：不同规则与预算线的交点可能有不同的 FPR。原文用这组图提醒我们，局部指标应与实际筛选目标一致。“部分 AUC 的不一致性”是该讨论语境中的标题，不能泛化为部分 AUC 没有用途。课件未给出局部 AUC 的完整定义，图示不能替代正式定义。

## 线性分离的三个场景（第 48–53 页）

原课件区分完全线性可分、近似线性可分、不可线性分离三种情形。

![线性可分的样本](<Images/03_LMC/image_019.jpg>)

![近似线性可分的样本](<Images/03_LMC/image_020.jpg>)

线性决策函数为 $f(x)=b+\beta^Tx$，$b\in\mathbb R$、$\beta\in\mathbb R^d$。$f(x)=0$ 定义超平面 $H$，分类约定为 $f(x)>0$ 时取 $+1$，否则取 $-1$。

对 $\beta\ne0$，单位法向量为 $\beta/\|\beta\|$，对任意 $x_0\in H$ 有 $\beta^Tx_0=-b$。有符号距离为

$$
d(x,H)=\frac{\beta^T(x-x_0)}{\|\beta\|}=\frac{b+\beta^Tx}{\|\beta\|}.
$$

![超平面、法向量与距离](<Images/03_LMC/image_021.jpg>)

**图解：** 图中 $w$ 对应正文的 $\beta$。分数 $f(x)$ 会随参数整体缩放而改变，有符号几何距离消除了这个任意缩放。

**术语说明：** 原文将本部分称为“非参数线性判别”。这里主要强调不拟合类条件概率分布；固定维度的线性感知机本身仍有有限维参数，并非通常统计定义下的非参数模型。

## 感知机算法（第 54–56 页）

Rosenblatt（1958）的简化感知机取 $b=0$，初始 $\beta_0=0$。依次访问样本，若 $y_i\beta^Tx_i>0$ 则不变，否则更新 $\beta\leftarrow\beta+y_ix_i$。训练通常需要反复遍历样本。

一般形式加入学习率 $\eta>0$ 和截距。令 $R=\max_i\|x_i\|>0$，采用增广样本 $(x_i,R)$、参数 $(\beta,b/R)$，在 $y_i(b+\beta^Tx_i)\le0$ 时更新

$$
\beta\leftarrow\beta+\eta y_ix_i,\qquad b\leftarrow b+\eta y_iR^2.
$$

若增广常数取 1，则常见写法是 $b\leftarrow b+\eta y_i$。

**校对说明：** PDF 第 55 页写成 $\eta y_i^2R^2$，会让截距更新始终非负，已修正为 $\eta y_iR^2$。

Novikoff 收敛结论的准确形式需要匹配增广约定：若样本 $\widetilde x_i$ 满足 $\|\widetilde x_i\|\le\widetilde R$，存在单位向量 $\widetilde w^*$ 使 $y_i\widetilde w^{*T}\widetilde x_i\ge\gamma>0$，则感知机错误更新次数满足

$$
T\le\frac{\widetilde R^2}{\gamma^2}.
$$

对上述增广有 $\widetilde R\le\sqrt2R$，故 $T\le2R^2/\gamma^2$。

**校对说明：** 原页额外写 $T\le n$，这不是一般保证；也把分母间隔直接写成原空间到仿射超平面的距离 $M$，没有处理增广参数归一化。此处给出条件与符号一致的版本。感知机具有在线更新优势，但找到任意分隔面不等于找到具有最好泛化能力的分隔面；不能一概说它必然泛化差。

## 最大间隔与硬间隔 SVM（第 57–59 页）

![多个分隔超平面与最大间隔选择](<Images/03_LMC/image_022.jpg>)

**图解：** 能分开训练点的直线可能很多。最大间隔选择离最近训练点尽可能远的分隔面，避免只满足“刚好分开”。

几何目标是最大化 $M$，满足 $y_i d(x_i,H)\ge M$。利用参数整体缩放不改变超平面，将最小函数间隔规范为 1，得到等价问题：

$$
\min_{\beta,b}\frac12\|\beta\|^2,
\qquad y_i(b+\beta^Tx_i)\ge1,\quad i=1,\ldots,n.
$$

此时单侧间隔为 $1/\|\beta\|$。这个规范化依赖样本可分，不能对不可分数据直接要求所有约束成立。

## 软间隔与松弛变量（第 60–62 页）

![间隔内的样本与松弛变量](<Images/03_LMC/image_023.jpg>)

引入 $\xi_i\ge0$，允许 $y_if(x_i)\ge1-\xi_i$。可在总预算 $\sum_i\xi_i\le\Xi$ 下最小化 $\|\beta\|^2/2$，或采用惩罚形式

$$
\min_{\beta,b,\xi}\frac12\|\beta\|^2+C\sum_{i=1}^n\xi_i,
\qquad\xi_i\ge0,\quad\xi_i\ge1-y_i(b+\beta^Tx_i),\quad C>0.
$$

**理解：** $\xi_i=0$ 表示满足间隔；$0<\xi_i<1$ 时通常分类正确但进入间隔；$\xi_i>1$ 表示落到错误一侧。消去松弛变量后，惩罚项就是 $C\sum_i\max(0,1-y_if(x_i))$，与第 02 篇的 hinge 损失相接。

## 拉格朗日函数、对偶与 KKT（第 63–65 页）

令 $\alpha_i,\mu_i\ge0$。统一使用约束 $1-\xi_i-y_if(x_i)\le0$ 与 $-\xi_i\le0$，拉格朗日函数为

$$
\mathcal L=\frac12\|\beta\|^2+C\sum_i\xi_i
+\sum_i\alpha_i(1-\xi_i-y_i(b+\beta^Tx_i))-\sum_i\mu_i\xi_i.
$$

驻点条件是

$$
\beta=\sum_i\alpha_iy_ix_i,\qquad\sum_i\alpha_iy_i=0,
\qquad C-\alpha_i-\mu_i=0.
$$

因此 $0\le\alpha_i\le C$。代回得到对偶问题

$$
\max_\alpha\sum_i\alpha_i-\frac12\sum_{i,j}\alpha_i\alpha_jy_iy_jx_i^Tx_j,
\qquad0\le\alpha_i\le C,\quad\sum_i\alpha_iy_i=0.
$$

KKT 条件还包括原始可行性、乘子非负和互补松弛：

$$
y_if(x_i)-(1-\xi_i)\ge0,\quad\xi_i\ge0,
$$

$$
\alpha_i[y_if(x_i)-(1-\xi_i)]=0,\qquad\mu_i\xi_i=0.
$$

**校对说明：** PDF 第 63 页的 $+\sum_i\mu_i\xi_i$ 与第 64–65 页使用的非负乘子及 $\alpha_i\le C$ 不一致。此处改成负号，相应驻点条件改为 $\alpha_i+\mu_i=C$，使整个推导一致。

## 支持向量及解的表示（第 66–68 页）

由 KKT 可知：

- $\widehat\alpha_i=0$：$\mu_i=C>0$，所以 $\xi_i=0$，$y_if(x_i)\ge1$。
- $0<\widehat\alpha_i<C$：$\xi_i=0$ 且 $y_if(x_i)=1$，样本位于间隔边界。
- $\widehat\alpha_i=C$：$y_if(x_i)=1-\xi_i\le1$，可能在边界、间隔内部或错误一侧，不一定已经误分类。

令 $I=\{i:\widehat\alpha_i\ne0\}$，这些样本称为支持向量。解可以表示为

$$
\widehat\beta=\sum_{i\in I}\widehat\alpha_i y_ix_i,
\qquad\widehat f(x)=\widehat b+\sum_{i\in I}\widehat\alpha_i y_ix_i^Tx.
$$

若存在 $0<\widehat\alpha_j<C$ 的样本，则

$$
\widehat b=y_j-\sum_{i\in I}\widehat\alpha_i y_i x_i^Tx_j.
$$

**校对说明：** 原式只要求 $j\in I$，条件不够；软间隔下必须使用位于间隔边界的自由支持向量。若没有这样的点，需要用可行性条件确定截距区间。

![最优超平面与支持向量](<Images/03_LMC/image_024.jpg>)

**图解：** 两条规范间隔边界为 $f(x)=\pm1$，宽度为 $2/\|\beta\|$。许多对偶系数可能为零，因此预测可只保留支持向量。这里的稀疏性发生在样本系数上，与 LASSO 的特征系数稀疏是不同对象。

## 后续内容（第 69 页）

课程将继续讨论无标签的聚类、其他非参数与非线性分类算法，以及通过正则化调节复杂度。原文法语“classification non supervisée”在这个语境中译为“无监督聚类”，避免和有标签分类混淆。
