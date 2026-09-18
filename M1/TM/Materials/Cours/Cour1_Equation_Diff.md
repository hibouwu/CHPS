# Simulation numérique | 数值模拟

Objectif : utiliser les mathématiques et le calcul scientifique pour modéliser et simuler des phénomènes du monde réel. | 目标：使用数学与科学计算来建模并模拟现实世界中的现象。

Chaîne générale : phénomène observé -> modèle phénoménologique -> modèle mathématique -> modèle numérique -> modèle computationnel. | 总体链条：观测到的现象 -> 现象模型 -> 数学模型 -> 数值模型 -> 计算模型。

## 1. Modèle phénoménologique | 1. 现象学模型

Comment présenter le phénomène que je veux étudier. | 如何描述我想研究的现象。

Le modèle phénoménologique est une description qualitative ou empirique du processus physique. | 现象学模型是对物理过程的定性或经验性描述。  
Il est souvent proche de l'observation ou de l'intuition physique, mais il n'est pas encore directement calculable. | 它通常接近实验观察或物理直觉，但还不能直接用于计算。

- sciences du vivant -> modèle statistique | 生命科学 -> 统计模型
- mécanique des fluides -> équations | 流体力学 -> 方程
- principes de conservation de la masse, quantité de mouvement, énergie | 质量、动量、能量守恒原理
- exemple : en conduction thermique, la chaleur diffuse des zones chaudes vers les zones froides | 例子：在热传导中，热量会从高温区域扩散到低温区域
- sources : observation expérimentale, lois physiques, retour d'expérience en ingénierie | 来源：实验观察、物理定律、工程经验反馈

## 2. Modèle mathématique associé | 2. 对应的数学模型

Le modèle mathématique traduit la description physique en langage mathématique. | 数学模型把物理描述翻译成数学语言。  
On obtient en général des équations différentielles, intégrales ou stochastiques. | 通常会得到微分方程、积分方程或随机模型。

- EDP, EDO, ... | 偏微分方程、常微分方程等
- processus stochastiques | 随机过程
- exemple : pour la chaleur, on obtient typiquement $\dfrac{\partial u}{\partial t} = \alpha \dfrac{\partial^2 u}{\partial x^2}$ | 例子：对于热传导，典型模型是 $\dfrac{\partial u}{\partial t} = \alpha \dfrac{\partial^2 u}{\partial x^2}$
- cette étape fournit un cadre théorique, mais ne donne pas encore une procédure de calcul effective | 这一步给出了理论框架，但还没有直接给出可执行的计算过程

## 3. Modèle numérique | 3. 数值模型

Le modèle numérique consiste à discrétiser le modèle mathématique pour le rendre calculable. | 数值模型的作用是把数学模型离散化，使其可以被计算。  
Les dérivées, intégrales ou opérateurs continus sont remplacés par des approximations discrètes. | 导数、积分或连续算子会被离散近似所替代。

- différences finies / éléments finis / volumes finis | 有限差分 / 有限元 / 有限体积
- LBM -> méthode de Boltzmann sur réseau | LBM -> 格子玻尔兹曼方法
- méthodes spectrales | 谱方法
- méthodes à base d'IA | 基于人工智能的方法
- exemple : $\dfrac{u_j^{n+1} - u_j^n}{\Delta t} = \alpha \dfrac{u_{j+1}^n - 2u_j^n + u_{j-1}^n}{\Delta x^2}$ | 例子：把热方程离散成差分格式
- le problème continu devient alors un système algébrique ou un schéma d'évolution discret | 连续问题在这一步会变成代数方程组或离散迭代格式

## 4. Méthode computationnelle | 4. 计算方法

Le modèle computationnel est l'implémentation effective du modèle numérique sur ordinateur. | 计算模型是数值模型在计算机上的实际实现。  
Il comprend le choix des structures de données, des algorithmes, du langage et de l'architecture matérielle. | 它包括数据结构、算法、编程语言以及硬件架构的选择。

- algorithmique | 算法
- langage | 编程语言
- architecture | 计算架构
- exemples de langages : Python, C++, MATLAB | 语言示例：Python、C++、MATLAB
- aspects pratiques : complexité, mémoire, parallélisation, GPU, stabilité numérique | 实际问题：复杂度、内存、并行化、GPU、数值稳定性

## Modèle mathématique | 数学模型

- EDO : équations différentielles ordinaires | EDO：常微分方程
- EDP : équations différentielles partielles | EDP：偏微分方程

$L(u) = \rho$ où $L$ désigne un opérateur différentiel. | $L(u)=\rho$，其中 $L$ 表示一个微分算子。

Du domaine continu au domaine discrétisé : | 从连续区域到离散化区域：

- domaine continu -> analyse fonctionnelle -> théorie des EDP/EDO | 连续区域 -> 泛函分析 -> 偏微分方程 / 常微分方程理论
- domaine discrétisé : $L_h(u_h) = f_h$ -> analyse numérique | 离散化区域：$L_h(u_h)=f_h$ -> 数值分析

Approximation des opérateurs différentiels : | 微分算子的近似：

- $g(x) = b$ -> résolution d'une équation (Newton, point fixe, etc.) | $g(x)=b$ -> 求解方程（牛顿法、不动点法等）
- $Ax = w$ -> système linéaire | $Ax=w$ -> 线性系统
- méthodes directes : pivot de Gauss, LU, Cholesky | 直接方法：高斯消元、LU 分解、Cholesky 分解
- méthodes itératives : gradient, gradient conjugué, GMRES | 迭代方法：梯度法、共轭梯度法、GMRES
- $\int f\,dn$ -> méthode de quadrature | $\int f\,dn$ -> 求积方法
- maillage | 网格划分

---

## Partie I : Équations différentielles | 第一部分：微分方程

## 1. Rappel | 1. 回顾

### 1.1 Équations différentielles ordinaires (EDO) | 1.1 常微分方程（EDO）

Une EDO est une équation qui lie une fonction dépendant d'une seule variable à ses dérivées. | 常微分方程是把一个只依赖单个变量的函数与其导数联系起来的方程。  
La solution cherchée n'est donc pas un scalaire mais une fonction. | 因此，我们要求的解不是一个标量，而是一个函数。

Autrement dit, une EDO concerne une fonction d'une seule variable et ses dérivées par rapport à cette variable. | 换句话说，EDO 研究的是单变量函数以及相对于该变量的导数。

Exemple : | 例子：

$$\begin{cases} u'(t) = u(t), & \forall t > 0, \\ u(0) = u_0. \end{cases}$$

Ici, la solution générale est de la forme $u(t)=Ce^t$, avec $C \in \mathbb{R}$. | 这里的一般解形如 $u(t)=Ce^t$，其中 $C \in \mathbb{R}$。

### 1.2 Équations aux dérivées partielles (EDP) | 1.2 偏微分方程（EDP）

Les EDP sont des équations qui lient une fonction de plusieurs variables à ses dérivées partielles. | 偏微分方程是把一个多变量函数与其偏导数联系起来的方程。

Une EDP concerne donc une fonction de plusieurs variables et des dérivées partielles par rapport à ces variables. | 因此，EDP 研究的是多变量函数以及相对于这些变量的偏导数。

Exemple : | 例子：

$$\begin{cases} \dfrac{\partial^2 U}{\partial x^2} + \dfrac{\partial^2 U}{\partial y^2} = f(x,y), & \forall (x,y) \in ]0,L[^2, \\ U(x,0) = U_0(x), \\ U(x,L) = U_L(x). \end{cases}$$

Rappels utiles : | 一些有用的回顾：

- si $f(x)=e^{4x^2+3}$, alors $f'(x)=8xe^{4x^2+3}$
- si $f(x)=e^{4x^2+3}$, alors $f'(x)=8xe^{4x^2+3}$
- si $g(x,y)=xy+\cos x+\sin y$, alors $\dfrac{\partial g}{\partial x}=y-\sin x$ et $\dfrac{\partial g}{\partial y}=x+\cos y$
- on a aussi $\dfrac{\partial^2 g}{\partial x^2}=-\cos x$ et $\dfrac{\partial^2 g}{\partial y^2}=-\sin y$
- si les dérivées croisées sont continues, alors $\dfrac{\partial^2 g}{\partial x \partial y}=\dfrac{\partial^2 g}{\partial y \partial x}$ (théorème de Schwarz)
- pour une composée $f(x)=h(u(x))$, on a $f'(x)=u'(x)h'(u(x))$
- pour un produit $f(x)=f_1(x)f_2(x)$, on a $f'(x)=f_1'(x)f_2(x)+f_1(x)f_2'(x)$

### 1.3 Classification | 1.3 分类

#### Ordre d'une EDP ou d'une EDO | 偏微分方程或常微分方程的阶

On appelle ordre d'une EDP/EDO l'ordre de dérivation le plus élevé de l'équation. | 一个 EDP/EDO 的阶，指的是方程中出现的最高阶导数的阶数。

Exemples : | 例子：

Exemple (i) : | 例（i）：

$$u''(t) + 2u'(t) - u(t) = f(t), \qquad \forall t > 0$$

Exemple (ii) : | 例（ii）：

$$\dfrac{\partial^2 u}{\partial x \partial y} + \dfrac{\partial^2 u}{\partial x^2} - \dfrac{\partial^2 u}{\partial y^2} + \dfrac{\partial u}{\partial x} + \dfrac{\partial u}{\partial y} = g(x,y), \qquad \forall (x,y) \in \Omega$$

- (i) EDO d'ordre 2 | （i）二阶常微分方程
- (ii) EDP d'ordre 2 | （ii）二阶偏微分方程

Autres exemples de classification : | 其他分类例子：

- $u'(t)-u^2(t)=0$ | $u'(t)-u^2(t)=0$
  EDO d'ordre 1, à coefficients constants, homogène, non linéaire | 一阶 EDO，常系数，齐次，非线性
- $u_t-u_{xx}=0$ | $u_t-u_{xx}=0$
  EDP d'ordre 2, à coefficients constants, homogène, linéaire | 二阶 EDP，常系数，齐次，线性
- $u_{tt}-u_{xx}=\sin(t)\,u^3(t)$ | $u_{tt}-u_{xx}=\sin(t)\,u^3(t)$
  EDP d'ordre 2, à coefficients variables, non homogène, non linéaire | 二阶 EDP，变系数，非齐次，非线性
- $u''(t)-\pi u(t)+\cos(t)=0$ | $u''(t)-\pi u(t)+\cos(t)=0$
  EDO d'ordre 2, à coefficients constants, non homogène, linéaire | 二阶 EDO，常系数，非齐次，线性
- $u_t-tu_{xt}=e^{x^2+t^2}$ | $u_t-tu_{xt}=e^{x^2+t^2}$
  EDP d'ordre 2, à coefficients variables, non homogène, linéaire | 二阶 EDP，变系数，非齐次，线性

#### EDP/EDO à coefficients constants | 常系数 EDP/EDO

On dit qu'une EDP/EDO est à coefficients constants si les coefficients devant les dérivées successives de l'inconnue sont constants. | 如果未知函数各阶导数前面的系数都是常数，就称该 EDP/EDO 为常系数方程。  
Dans le cas contraire, on dit que l'EDO/EDP est à coefficients variables. | 反之，则称为变系数方程。

Exemples : | 例子：

Exemple (i) : | 例（i）：

$$2u''(t) + u(t) = \sin(t)$$

Exemple (ii) : | 例（ii）：

$$2(x^2 + y^2)\dfrac{\partial^2 u}{\partial x^2} + xy\dfrac{\partial^2 u}{\partial y^2} = xe^y$$

- (i) EDO à coefficients constants | （i）常系数常微分方程
- (ii) EDP à coefficients variables | （ii）变系数偏微分方程

#### Homogénéité | 齐次性

On dit qu'une EDO/EDP est homogène si le second membre (le terme ne dépendant pas de l'inconnue) est nul. | 如果方程右端项（即不依赖未知函数的项）为零，则称该 EDO/EDP 为齐次方程。

Exemples : | 例子：

Exemple (i) : | 例（i）：

$$2xu'(t) + u(t) = 3 + t$$

Exemple (ii) : | 例（ii）：

$$\Delta v = 0, \qquad \Delta = \dfrac{\partial^2}{\partial x^2} + \dfrac{\partial^2}{\partial y^2}$$

- (i) EDO non homogène | （i）非齐次常微分方程
- (ii) EDP homogène | （ii）齐次偏微分方程

#### Linéarité | 线性性

Soit l'opérateur différentiel associé à notre EDP/EDO d'inconnue $u$. | 设与未知函数 $u$ 对应的 EDP/EDO 的微分算子为。  
On dit que l'EDP/EDO $L(u) = f$ est linéaire si $L$ est linéaire, c'est-à-dire | 如果算子 $L$ 是线性的，那么方程 $L(u)=f$ 就称为线性方程，也就是说：

$$\forall \alpha,\beta \in \mathbb{R},\ \forall (u,v) \in E^2, \qquad L(\alpha u + \beta v) = \alpha L(u) + \beta L(v),$$

où $E$ est un espace de fonctions. | 其中 $E$ 是一个函数空间。

On peut résumer cette idée en écrivant un problème sous la forme $L(\mu)=f$ : l'inconnue $\mu$ est une fonction, $L$ est un opérateur différentiel, et $f$ est une fonction donnée. | 可以把这个思想概括为把问题写成 $L(\mu)=f$：未知量 $\mu$ 是函数，$L$ 是微分算子，$f$ 是已知函数。

Exemples : | 例子：

Exemple (i) : | 例（i）：

$$2u''(t) + u(t) = 2\sin(t)$$

Exemple (ii) : | 例（ii）：

$$\dfrac{\partial u}{\partial t} + a\dfrac{\partial u}{\partial x} = f(x,t)$$

Notation : | 记号：

$$\dfrac{\partial u}{\partial t} = \partial_t u = u_t$$

Pour (i), on peut prendre | 对于（i），我们可以取：

$$L = \dfrac{d^2}{dt^2} + \mathrm{Id}$$

qui est linéaire car $\dfrac{d^2}{dt^2}$ et $\mathrm{Id}$ sont linéaires. | 它是线性的，因为 $\dfrac{d^2}{dt^2}$ 和 $\mathrm{Id}$ 都是线性算子。

$$L : u \mapsto 2u'' + u$$

et | 并且

$$\begin{aligned} L(\alpha u + \beta v) &= 2(\alpha u + \beta v)'' + (\alpha u + \beta v) \\ &= 2\alpha u'' + 2\beta v'' + \alpha u + \beta v \\ &= \alpha(2u'' + u) + \beta(2v'' + v) \\ &= \alpha L(u) + \beta L(v). \end{aligned}$$

En revanche, si | 相反，如果

$$L : u \mapsto u_t + uu_x,$$

alors | 那么

$$\begin{aligned} L(\alpha u + \beta v) &= (\alpha u + \beta v)_t + (\alpha u + \beta v)(\alpha u + \beta v)_x \\ &= \alpha u_t + \beta v_t + \alpha^2 uu_x + \beta^2 vv_x \\ &\quad + \alpha\beta uv_x + \alpha\beta vu_x \\ &\neq \alpha L(u) + \beta L(v). \end{aligned}$$

Donc cet opérateur n'est pas linéaire. | 因此这个算子不是线性的。

Autre exemple non linéaire : si $L(u)=u'-u^2$, alors | 另一个非线性例子：如果 $L(u)=u'-u^2$，那么

$$L(\alpha u+\beta v)=(\alpha u+\beta v)'-(\alpha u+\beta v)^2=\alpha u'+\beta v'-\alpha^2u^2-\beta^2v^2-2\alpha\beta uv,$$

ce qui n'est pas égal à $\alpha L(u)+\beta L(v)$. | 这并不等于 $\alpha L(u)+\beta L(v)$。

## 2. Notion de problème bien posé | 2. 适定问题的概念

On dit qu'un problème (EDO + CI, EDP + CB) est bien posé (au sens d'Hadamard) s'il vérifie les 3 points suivants : | 如果一个问题（常微分方程 + 初始条件，偏微分方程 + 边界条件）满足下列三个条件，则称它在 Hadamard 意义下是适定的：

1. il admet une solution ; | 存在解；
2. cette solution est unique ; | 解唯一；
3. elle dépend continûment des conditions aux limites. | 解对边界条件连续依赖。

Lorsqu'un problème ne vérifie pas l'une de ces conditions, on dit qu'il est mal posé. | 如果一个问题不满足其中任意一个条件，就称它是非适定的。

Cette troisième propriété signifie qu'une petite perturbation des données doit produire une petite perturbation de la solution. | 第三个条件的意思是：如果输入数据只有小扰动，那么解也只能发生小变化。

Remarque : il existe plusieurs types de conditions aux limites. | 注：边界条件有多种类型。

- condition de Dirichlet : les conditions au bord sont données sur $u$, autrement dit on donne la valeur de $u$ au bord ; | Dirichlet 条件：边界上给出的是 $u$ 的值，也就是直接给出边界处函数值；
- condition de Neumann : les conditions sont données sur la dérivée de $u$ ; | Neumann 条件：边界上给出的是 $u$ 的导数；
- condition de Robin (mixte, Fourier) : les conditions aux limites sont données sur $u$ et sa dérivée. | Robin 条件（混合 / Fourier 条件）：边界上同时给出 $u$ 和它的导数。

Exemples : | 例子：

Condition de Dirichlet : | Dirichlet 条件：

$$\begin{cases} \Delta u = f, \\ u(0) = u_0, \\ u(L) = u_L, \end{cases}$$

Condition de Neumann : | Neumann 条件：

$$\begin{cases} \Delta u = f, \\ u_x(0) = \alpha, \\ u_y(0) = \beta, \end{cases}$$

Condition de Robin : | Robin 条件：

$$\begin{cases} \Delta u = f, \\ u_x(0) + u(0) = 0, \\ u_y(0) = \ell, \end{cases}$$

Considérons l'EDO suivante : | 考虑下面这个常微分方程：

$$(P)\quad \begin{cases} u'(t) = -u(t), \\ u(0) = u_0. \end{cases}$$

et l'EDO perturbée associée : | 以及它对应的扰动方程：

$$(P_\varepsilon)\quad \begin{cases} v'(t) = -v(t), \\ v(0) = u_0 + \varepsilon. \end{cases}$$

On obtient | 可得

$$u(t) = u_0 e^{-t}, \qquad v(t) = (u_0 + \varepsilon)e^{-t}.$$

Ainsi, | 因此，

$$\frac{\lvert u(t) - v(t) \rvert}{\lvert u(t) \rvert} = \frac{\lvert \varepsilon \rvert e^{-t}}{\lvert u_0 \rvert e^{-t}} = \frac{\lvert \varepsilon \rvert}{\lvert u_0 \rvert},$$

ce qui illustre la dépendance continue aux conditions initiales / aux conditions aux limites. | 这说明了解对初始条件 / 边界条件具有连续依赖性。

Exemple de situation plus délicate : | 一个更微妙的例子：

$$\begin{cases} u'(t)=tu(t)(u(t)-2), \\ u(0)=u_0, \end{cases}$$

dont une solution explicite est | 其一个显式解为

$$u(t)=\frac{2u_0}{u_0+(2-u_0)e^{t^2}}.$$

Si $u_0=2$, alors $u(t)=2$. | 若 $u_0=2$，则 $u(t)=2$。  
Si l'on perturbe la donnée initiale en prenant $v_0=2+\varepsilon$, on obtient une expression du même type mais dont le dénominateur peut devenir très petit ou s'annuler selon le signe de $\varepsilon$. | 如果把初值扰动为 $v_0=2+\varepsilon$，则得到同类型表达式，但其分母可能会因为 $\varepsilon$ 的符号而变得很小甚至为零。  
Cela montre qu'il faut toujours vérifier avec soin la dépendance continue sur l'intervalle de temps considéré. | 这说明在研究适定性时，必须仔细检查在所考虑时间区间上是否真的满足连续依赖。

Rappel sur la continuité : | 关于连续性的回顾：

- définition séquentielle : si $x_n \to x_0$, alors $f(x_n) \to f(x_0)$ ; | 序列定义：如果 $x_n \to x_0$，那么 $f(x_n) \to f(x_0)$；
- définition $\varepsilon$-$\delta$ : | $\varepsilon$-$\delta$ 定义：

$$\forall \varepsilon > 0,\ \exists \delta > 0, |x - x_0| < \delta \Rightarrow |f(x) - f(x_0)| < \varepsilon.$$

## 3. Quelques méthodes analytiques | 3. 一些解析方法

### a. Méthode des caractéristiques | a. 特征线方法

Considérons l'équation | 考虑方程

$$\begin{cases} u_t(x,t) + a(x,t)u_x(x,t) = 0, \\ u(x,0) = \phi(x), \end{cases}$$

où $a$ et $\phi$ sont des fonctions régulières. | 其中 $a$ 和 $\phi$ 都是光滑函数。

On considère une courbe caractéristique $x = x(t)$. Par la règle de la chaîne : | 我们考虑一条特征曲线 $x=x(t)$。由链式法则：

$$\frac{d}{dt}u(x(t),t) = \frac{\partial u}{\partial t}(x(t),t) + \frac{dx}{dt}\frac{\partial u}{\partial x}(x(t),t).$$

Si l'on choisit | 如果取

$$\frac{dx}{dt} = a(x(t),t),$$

alors | 那么

$$\frac{d}{dt}u(x(t),t) = u_t(x(t),t) + a(x(t),t)u_x(x(t),t) = 0.$$

Donc $u$ est constante le long des caractéristiques : | 因此 $u$ 沿特征线保持常数：

$$u(x(t),t) = u(x_0,0) = \phi(x_0), \qquad \text{si } x(0) = x_0.$$

Par ailleurs, | 此外，

$$x(t) - x_0 = \int_0^t a(x(s),s)\,ds.$$

En général, si $a$ dépend de $x$, cette relation est implicite : il faut résoudre l'EDO caractéristique pour retrouver $x_0$ à partir de $(x,t)$. | 一般地，如果 $a$ 依赖于 $x$，这个关系是隐式的：需要先解特征线常微分方程，才能由 $(x,t)$ 找到 $x_0$。

Si $a$ est constante, $a \neq 0$, alors | 如果 $a$ 是常数，且 $a \neq 0$，那么

$$\frac{dx}{dt} = a, \qquad x(t) = at + x_0, \qquad x_0 = x - at,$$

et donc | 因此

$$u(x,t) = \phi(x - at).$$

Avec second membre : | 如果带有右端项：

$$\begin{cases} u_t(x,t) + a(x,t)u_x(x,t) = b(x,t), \\ u(x,0) = \phi(x), \end{cases}$$

on a le long des caractéristiques | 沿着特征线有

$$\frac{d}{dt}u(x(t),t) = b(x(t),t),$$

donc | 所以

$$u(x(t),t) = \phi(x_0) + \int_0^t b(x(s),s)\,ds.$$

Ici encore, pour obtenir $u(x,t)$, on prend la caractéristique telle que $x(t)=x$ et $x(0)=x_0$. | 这里同样地，为了得到 $u(x,t)$，要取满足 $x(t)=x$ 且 $x(0)=x_0$ 的特征线。

### b. Méthode de séparation de variables | b. 分离变量法

Considérons l'équation de la chaleur avec conditions de Dirichlet homogènes : | 考虑带齐次 Dirichlet 边界条件的热方程：

$$\begin{cases} u_t(x,t)=\beta u_{xx}(x,t), & x\in]0,L[,\ t>0, \\ u(0,t)=u(L,t)=0, & t>0, \\ u(x,0)=f(x). \end{cases}$$

On cherche une solution séparée sous la forme | 我们寻找分离变量形式的解

$$u(x,t)=X(x)T(t).$$

En injectant cette forme dans l'équation, on obtient | 将该形式代入方程得到

$$X(x)T'(t)=\beta X''(x)T(t).$$

En divisant par $\beta X(x)T(t)$, on trouve | 两边除以 $\beta X(x)T(t)$，得到

$$\frac{T'(t)}{\beta T(t)}=\frac{X''(x)}{X(x)}.$$

Le membre de gauche ne dépend que de $t$ et le membre de droite ne dépend que de $x$, donc ils sont égaux à une constante, que l'on note $-\lambda$. | 左边只依赖于 $t$，右边只依赖于 $x$，所以它们等于同一个常数，记为 $-\lambda$。

On a donc | 因此

$$X'' + \lambda X = 0$$

et | 以及

$$T' + \beta\lambda T = 0$$

avec conditions aux bords | 并带有边界条件

$$X(0) = 0, \qquad X(L) = 0.$$

L'équation caractéristique associée est | 对应的特征方程为

$$r^2 + \lambda = 0 \qquad \Longleftrightarrow \qquad r^2 = -\lambda.$$

#### Cas 1 : $\lambda < 0$ | 情形 1：$\lambda < 0$

$$r_{1,2} = \pm \sqrt{-\lambda}$$

$$X(x) = \alpha e^{\sqrt{-\lambda}\,x} + \beta e^{-\sqrt{-\lambda}\,x}$$

$$X(0) = \alpha + \beta = 0 \Rightarrow \alpha = -\beta$$

$$X(L) = \alpha\left(e^{L\sqrt{-\lambda}} - e^{-L\sqrt{-\lambda}}\right) = 0$$

Comme | 因为

$$e^{L\sqrt{-\lambda}} - e^{-L\sqrt{-\lambda}} \neq 0,$$

on obtient $\alpha = \beta = 0$, donc la solution est triviale. | 可得 $\alpha=\beta=0$，因此只有平凡解。

#### Cas 2 : $\lambda = 0$ | 情形 2：$\lambda = 0$

$$r_0 = 0, \qquad X(x) = (c_0 + c_1x)e^{r_0x} = c_0 + c_1x$$

$$X(0) = 0 \Rightarrow c_0 = 0, \qquad X(L) = 0 \Rightarrow c_1 = 0$$

donc encore une fois $X = 0$. | 因此这里同样只有 $X=0$。

#### Cas 3 : $\lambda > 0$ | 情形 3：$\lambda > 0$

$$r = \pm i\sqrt{\lambda}$$

$$X(x) = A\cos(\sqrt{\lambda}\,x) + B\sin(\sqrt{\lambda}\,x)$$

$$X(0) = A = 0$$

$$X(L) = B\sin(L\sqrt{\lambda}) = 0.$$

Deux possibilités : | 有两种可能：

- si $B = 0$, alors $X = 0$ ; | 如果 $B=0$，那么 $X=0$；
- sinon $\sin(L\sqrt{\lambda}) = 0$, donc $L\sqrt{\lambda} = k\pi$, $k \in \mathbb{N}^*$. | 否则 $\sin(L\sqrt{\lambda})=0$，于是 $L\sqrt{\lambda}=k\pi$，其中 $k \in \mathbb{N}^*$。

On obtient ainsi les valeurs propres | 于是得到特征值

$$\lambda_k = \left(\frac{k\pi}{L}\right)^2$$

et les fonctions propres | 以及特征函数

$$X_k(x) = B_k \sin\left(\frac{k\pi}{L}x\right).$$

Pour la partie temporelle : | 对于时间部分：

$$T_k' + \beta \lambda_k T_k = 0$$

d'où | 因此

$$T_k(t) = \alpha_k e^{-\beta \lambda_k t} = \alpha_k e^{-\beta\left(\frac{k\pi}{L}\right)^2 t}.$$

Ainsi, | 于是

$$u_k(x,t) = \alpha_k B_k e^{-\beta\left(\frac{k\pi}{L}\right)^2 t}\sin\left(\frac{k\pi}{L}x\right)$$

est une solution. Par le principe de superposition, | 是一个解。根据叠加原理，

$$u(x,t) = \sum_{k=1}^{+\infty} C_k e^{-\beta\left(\frac{k\pi}{L}\right)^2 t}\sin\left(\frac{k\pi}{L}x\right)$$

est aussi solution. | 它也是一个解。

Pour déterminer les coefficients $C_k$, on utilise la condition initiale | 为了确定系数 $C_k$，我们使用初始条件

$$u(x,0) = f(x) = \sum_{k=1}^{+\infty} C_k \sin\left(\frac{k\pi}{L}x\right),$$

donc, par développement en série de Fourier, | 因此，通过 Fourier 正弦级数展开，

$$\forall k \in \mathbb{N}^*, \qquad C_k = \frac{2}{L}\int_0^L f(x)\sin\left(\frac{k\pi}{L}x\right)\,dx.$$

Rappel : | 回顾：

La série de Fourier en sinus sur $[0,L]$ s'écrit | 区间 $[0,L]$ 上的 Fourier 正弦级数写作

$$\sum_{k=1}^{+\infty} \alpha_k \sin\left(\frac{k\pi}{L}x\right), \qquad \alpha_k = \frac{2}{L}\int_0^L f(x)\sin\left(\frac{k\pi}{L}x\right)\,dx.$$

De même, la série de Fourier en cosinus sur $[0,L]$ s'écrit | 类似地，区间 $[0,L]$ 上的 Fourier 余弦级数写作

$$\frac{\gamma_0}{2} + \sum_{k=1}^{+\infty} \gamma_k \cos\left(\frac{k\pi}{L}x\right), \qquad \gamma_k = \frac{2}{L}\int_0^L f(x)\cos\left(\frac{k\pi}{L}x\right)\,dx.$$

### c. Méthode de changement de variable | c. 变量代换法

Équation des ondes : | 波动方程：

$$\begin{cases} u_{tt}(x,t) = u_{xx}(x,t), & \forall x \in \mathbb{R},\ t > 0, \\ u(x,0) = \phi(x), \\ u_t(x,0) = \psi(x). \end{cases}$$

On pose | 令

$$\alpha = x + t, \qquad \beta = x - t, \qquad u(x,t) = v(\alpha,\beta).$$

Par la règle de la chaîne, | 由链式法则，

$$u_x = v_\alpha\frac{\partial \alpha}{\partial x}+v_\beta\frac{\partial \beta}{\partial x}=v_\alpha+v_\beta,$$

$$u_t = v_\alpha\frac{\partial \alpha}{\partial t}+v_\beta\frac{\partial \beta}{\partial t}=v_\alpha-v_\beta.$$

On dérive une seconde fois : | 再求二阶导：

$$u_{xx}=v_{\alpha\alpha}+2v_{\alpha\beta}+v_{\beta\beta},$$

$$u_{tt}=v_{\alpha\alpha}-2v_{\alpha\beta}+v_{\beta\beta}.$$

Comme $u_{tt}=u_{xx}$, on obtient | 因为 $u_{tt}=u_{xx}$，得到

$$v_{\alpha\beta}=0.$$

Donc $v_\alpha$ ne dépend que de $\alpha$, et la solution générale s'écrit | 因此 $v_\alpha$ 只依赖于 $\alpha$，通解可写为

$$v(\alpha,\beta)=f(\alpha)+g(\beta).$$

Ainsi, en revenant aux variables $(x,t)$, | 因此回到变量 $(x,t)$，

$$u(x,t)=f(x+t)+g(x-t).$$

On utilise maintenant les conditions initiales. | 现在使用初始条件。

Pour $t=0$, | 当 $t=0$ 时，

$$u(x,0)=f(x)+g(x)=\phi(x).$$

De plus, | 另外，

$$u_t(x,t)=f'(x+t)-g'(x-t),$$

donc | 所以

$$u_t(x,0)=f'(x)-g'(x)=\psi(x).$$

En dérivant $f(x)+g(x)=\phi(x)$, on obtient | 对 $f(x)+g(x)=\phi(x)$ 求导，得到

$$f'(x)+g'(x)=\phi'(x).$$

On résout alors le système | 于是解方程组

$$\begin{cases} f'(x)+g'(x)=\phi'(x), \\ f'(x)-g'(x)=\psi(x), \end{cases}$$

ce qui donne | 得到

$$f'(x)=\frac{\phi'(x)+\psi(x)}{2}, \qquad g'(x)=\frac{\phi'(x)-\psi(x)}{2}.$$

En intégrant, | 积分可得

$$f(x)=\frac{\phi(x)}{2}+\frac{1}{2}\int_0^x \psi(s)\,ds+K_1,$$

$$g(x)=\frac{\phi(x)}{2}-\frac{1}{2}\int_0^x \psi(s)\,ds+K_2.$$

La condition $f(x)+g(x)=\phi(x)$ impose $K_1+K_2=0$. | 条件 $f(x)+g(x)=\phi(x)$ 要求 $K_1+K_2=0$。

Finalement, | 最终，

$$u(x,t)=\frac{\phi(x+t)+\phi(x-t)}{2}+\frac{1}{2}\int_{x-t}^{x+t}\psi(s)\,ds.$$

C'est la formule de d'Alembert pour l'équation des ondes avec vitesse $1$. | 这就是波速为 $1$ 的波动方程的 d'Alembert 公式。
