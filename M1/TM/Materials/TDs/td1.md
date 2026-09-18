# Techniques de modélisation | 建模技术

**Année** : 2025-2026 | **学年**：2025-2026  
**TD** : 1 | **习题课**：1

---

## Exercice 1 | 练习 1

Considérons les équations différentielles suivantes : | 考虑下面这些微分方程：

1. $u'(t)=e^t u(t)$
2. $u_{xx}(x,t)=u(x,t)\sqrt{x+t}$
3. $u_{xx}(x,y)+u_{yy}(x,y)e^{\sin(x)}=1$
4. $u_t(x,t)+u_x(x,t)=u_{xx}(x,t)+u^2(x,t)$
5. $u''(t)+u(t)=e^t$

Pour chacune de ces équations dites s'il s'agit d'EDO ou d'EDP, si elles sont linéaires ou non linéaires et enfin si elles sont homogènes ou non homogènes. | 对每一个方程，说明它是常微分方程还是偏微分方程，线性还是非线性，以及齐次还是非齐次。

**Éléments de réponse** | **答案要点**

1. EDO d'ordre 1, linéaire, à coefficients variables, homogène. | 一阶常微分方程，线性，变系数，齐次。
2. EDP d'ordre 2, linéaire, à coefficients variables, homogène. | 二阶偏微分方程，线性，变系数，齐次。
3. EDP d'ordre 2, linéaire, à coefficients variables, non homogène. | 二阶偏微分方程，线性，变系数，非齐次。
4. EDP d'ordre 2, non linéaire, à coefficients constants, homogène au sens où il n'y a pas de terme source indépendant de $u$. | 二阶偏微分方程，非线性，常系数，并且在没有独立于 $u$ 的源项这个意义下是齐次的。
5. EDO d'ordre 2, linéaire, à coefficients constants, non homogène. | 二阶常微分方程，线性，常系数，非齐次。

## Exercice 2 | 练习 2

Considérons l'équation différentielle ordinaire suivante : | 考虑下面这个常微分方程：

$$u'(t)=-\alpha u(t) \qquad \text{avec } u(0)=u_0 \qquad \text{et} \qquad \alpha>0$$

1. Montrer que ce problème est stable si l'on perturbe $u_0$ uniquement. | 证明如果只扰动 $u_0$，那么这个问题是稳定的。
2. Que se passe-t-il si l'on perturbe $\alpha$ uniquement ? | 如果只扰动 $\alpha$，会发生什么？
3. Que se passe-t-il si l'on perturbe les deux ? | 如果两者都扰动，会发生什么？

**Éléments de réponse** | **答案要点**

Ici, on étudie la stabilité en utilisant l'erreur absolue $|u(t)-\tilde{u}(t)|$. | 这里我们利用绝对误差 $|u(t)-\tilde{u}(t)|$ 来研究稳定性。

On note $u$ la solution du problème non perturbé et $\tilde{u}$ la solution du problème perturbé. | 记 $u$ 为未扰动问题的解，$\tilde{u}$ 为扰动后问题的解。

1. On résout d'abord le problème non perturbé $u'(t)+\alpha u(t)=0$, $u(0)=u_0$, donc $u(t)=u_0e^{-\alpha t}$. | 首先求解未扰动问题 $u'(t)+\alpha u(t)=0$，$u(0)=u_0$，因此 $u(t)=u_0e^{-\alpha t}$。

   Si on perturbe uniquement la donnée initiale, on résout $\tilde{u}'(t)+\alpha\tilde{u}(t)=0$, $\tilde{u}(0)=u_0+\delta u_0$, donc $\tilde{u}(t)=(u_0+\delta u_0)e^{-\alpha t}$. | 如果只扰动初始值，则需要求解 $\tilde{u}'(t)+\alpha\tilde{u}(t)=0$，$\tilde{u}(0)=u_0+\delta u_0$，因此 $\tilde{u}(t)=(u_0+\delta u_0)e^{-\alpha t}$。

   L'erreur absolue vaut $|u(t)-\tilde{u}(t)|=|\delta u_0|e^{-\alpha t}$. Comme $e^{-\alpha t}\in]0,1]$ pour $t\ge 0$ et $\alpha>0$, on a $|u(t)-\tilde{u}(t)|\to 0$ quand $\delta u_0\to 0$. Donc le problème est stable par rapport à $u_0$. | 绝对误差为 $|u(t)-\tilde{u}(t)|=|\delta u_0|e^{-\alpha t}$。由于当 $t\ge 0$ 且 $\alpha>0$ 时有 $e^{-\alpha t}\in]0,1]$，所以当 $\delta u_0\to 0$ 时，$|u(t)-\tilde{u}(t)|\to 0$。因此该问题对 $u_0$ 是稳定的。

2. Si on perturbe uniquement $\alpha$, on pose $\tilde{\alpha}=\alpha+\delta\alpha$. On résout alors $\tilde{u}'(t)+\tilde{\alpha}\tilde{u}(t)=0$, $\tilde{u}(0)=u_0$, donc $\tilde{u}(t)=u_0e^{-\tilde{\alpha}t}=u_0e^{-\alpha t}e^{-\delta\alpha t}$. | 如果只扰动 $\alpha$，令 $\tilde{\alpha}=\alpha+\delta\alpha$。于是求解 $\tilde{u}'(t)+\tilde{\alpha}\tilde{u}(t)=0$，$\tilde{u}(0)=u_0$，从而 $\tilde{u}(t)=u_0e^{-\tilde{\alpha}t}=u_0e^{-\alpha t}e^{-\delta\alpha t}$。

   L'erreur absolue vaut $|u(t)-\tilde{u}(t)|=|u_0|e^{-\alpha t}|1-e^{-\delta\alpha t}|$. Pour tout $t\ge 0$ fixé, lorsque $\delta\alpha\to 0$, on a $e^{-\delta\alpha t}\to 1$, donc $|u(t)-\tilde{u}(t)|\to 0$. Le problème est stable par rapport à $\alpha$. | 绝对误差为 $|u(t)-\tilde{u}(t)|=|u_0|e^{-\alpha t}|1-e^{-\delta\alpha t}|$。对任意固定的 $t\ge 0$，当 $\delta\alpha\to 0$ 时，$e^{-\delta\alpha t}\to 1$，因此 $|u(t)-\tilde{u}(t)|\to 0$。该问题对 $\alpha$ 是稳定的。

3. Si on perturbe à la fois $u_0$ et $\alpha$, on pose $\tilde{u}(0)=u_0+\delta u_0$ et $\tilde{\alpha}=\alpha+\delta\alpha$. On résout $\tilde{u}'(t)+\tilde{\alpha}\tilde{u}(t)=0$, donc $\tilde{u}(t)=(u_0+\delta u_0)e^{-(\alpha+\delta\alpha)t}$. | 如果同时扰动 $u_0$ 和 $\alpha$，令 $\tilde{u}(0)=u_0+\delta u_0$ 且 $\tilde{\alpha}=\alpha+\delta\alpha$。于是求解 $\tilde{u}'(t)+\tilde{\alpha}\tilde{u}(t)=0$，因此 $\tilde{u}(t)=(u_0+\delta u_0)e^{-(\alpha+\delta\alpha)t}$。

   L'erreur absolue vaut $|u(t)-\tilde{u}(t)|=e^{-\alpha t}\left|u_0-(u_0+\delta u_0)e^{-\delta\alpha t}\right|$. Pour tout $t\ge 0$ fixé, si $\delta u_0\to 0$ et $\delta\alpha\to 0$, alors $|u(t)-\tilde{u}(t)|\to 0$. Donc le problème est stable par rapport à $u_0$ et à $\alpha$. | 绝对误差为 $|u(t)-\tilde{u}(t)|=e^{-\alpha t}\left|u_0-(u_0+\delta u_0)e^{-\delta\alpha t}\right|$。对任意固定的 $t\ge 0$，如果 $\delta u_0\to 0$ 且 $\delta\alpha\to 0$，那么 $|u(t)-\tilde{u}(t)|\to 0$。因此该问题对 $u_0$ 和 $\alpha$ 都是稳定的。

## Exercice 3 | 练习 3

Considérons le problème de Cauchy suivant : | 考虑下面这个 Cauchy 问题：

$$u'(t)=t\,u(t)(u(t)-2) \qquad \text{avec } u(0)=u_0$$

1. Montrer que la solution de ce problème est : | 证明该问题的解为：

$$u(t)=\frac{2u_0}{u_0+(2-u_0)e^{t^2}}$$

2. Étudiez le comportement de cette solution en fonction de $u_0$ ? | 研究该解随 $u_0$ 变化时的行为。
3. Que peut-on conclure ? | 可以得出什么结论？

**Éléments de réponse** | **答案要点**

1. On vérifie d'abord la condition initiale : $u(0)=\dfrac{2u_0}{u_0+2-u_0}=u_0$. | 首先验证初始条件：$u(0)=\dfrac{2u_0}{u_0+2-u_0}=u_0$。

   Pour résoudre l'équation, on sépare les variables : | 为了求解这个方程，我们分离变量：

   $$\frac{du}{dt}=t\,u(u-2) \qquad \Longleftrightarrow \qquad \frac{du}{u(u-2)}=t\,dt$$

   Or | 而

   $$\frac{1}{u(u-2)}=\frac{1}{2}\left(\frac{1}{u-2}-\frac{1}{u}\right)$$

   donc | 因此

   $$\frac{1}{2}\ln\left|\frac{u-2}{u}\right|=\frac{t^2}{2}+C$$

   Ainsi, $\dfrac{u-2}{u}=K e^{t^2}$. En utilisant $u(0)=u_0$, on obtient $K=\dfrac{u_0-2}{u_0}$, puis | 因而有 $\dfrac{u-2}{u}=K e^{t^2}$。利用 $u(0)=u_0$，得到 $K=\dfrac{u_0-2}{u_0}$，进而

   $$u(t)=\frac{2u_0}{u_0+(2-u_0)e^{t^2}}$$

2. Posons $D(t)=u_0+(2-u_0)e^{t^2}$ le dénominateur de la solution. | 令 $D(t)=u_0+(2-u_0)e^{t^2}$ 为该解的分母。

   Les cas constants sont $u_0=0$, qui donne $u(t)=0$, et $u_0=2$, qui donne $u(t)=2$. | 常值解的情形为 $u_0=0$，此时 $u(t)=0$；以及 $u_0=2$，此时 $u(t)=2$。

   Le dénominateur s'annule lorsque | 当满足下式时，分母为零：

   $$e^{t^2}=-\frac{u_0}{2-u_0}$$

   Comme $e^{t^2}\ge 1$, il faut $-\dfrac{u_0}{2-u_0}\ge 1$. Cela arrive pour $u_0>2$. Dans ce cas, il existe un temps $t^\ast$ tel que $D(t^\ast)=0$, et la solution explose quand $t\to t^\ast$. | 由于 $e^{t^2}\ge 1$，必须有 $-\dfrac{u_0}{2-u_0}\ge 1$。这在 $u_0>2$ 时成立。在这种情况下，存在某个时刻 $t^\ast$ 使得 $D(t^\ast)=0$，于是当 $t\to t^\ast$ 时解会爆破。

   Si $u_0<2$, le dénominateur ne s'annule pas et la solution est définie pour tout $t$. | 如果 $u_0<2$，则分母不会为零，解对所有 $t$ 都有定义。

3. On conclut que la solution dépend fortement de la donnée initiale $u_0$. Les comportements sont différents selon que $u_0<2$, $u_0=2$, ou $u_0>2$. Sur un intervalle de temps fixé qui ne contient pas de temps d'explosion, la dépendance continue est conservée ; en revanche, on ne peut pas avoir de stabilité globale uniforme au voisinage des données qui mènent à une explosion. | 我们由此得到：解强烈依赖于初始值 $u_0$。当 $u_0<2$、$u_0=2$ 或 $u_0>2$ 时，解的行为不同。在一个不包含爆破时刻的固定时间区间上，连续依赖性仍然成立；但在会导致爆破的初值附近，不能得到整体一致稳定性。

## Exercice 4 | 练习 4

Trouver les solutions exactes aux problèmes de Cauchy suivants : | 求解下列 Cauchy 问题的精确解：

1.

$$\begin{cases} u_t + 2x u_x = 0 & x \in \mathbb{R},\, t>0 \\ u(x,0)=e^{-x^2} \end{cases}$$

**Éléments de réponse** | **答案要点**

On utilise la méthode des caractéristiques. Pour une courbe $x=x(t)$, on a | 我们使用特征线方法。对一条曲线 $x=x(t)$，有

$$\frac{d}{dt}u(x(t),t)=u_t(x(t),t)+x'(t)u_x(x(t),t)$$

Pour la première équation, on choisit $x'(t)=2x(t)$, ce qui donne | 对第一个方程，取 $x'(t)=2x(t)$，于是得到

$$\frac{d}{dt}u(x(t),t)=u_t+2xu_x=0$$

Donc $u$ est constante le long des caractéristiques. De plus, $x'(t)=2x(t)$ donne $x(t)=x_0e^{2t}$, donc $x_0=xe^{-2t}$. | 因此 $u$ 沿特征线保持常数。另外，$x'(t)=2x(t)$ 给出 $x(t)=x_0e^{2t}$，从而 $x_0=xe^{-2t}$。

Ainsi, | 因而

$$u(x,t)=u(x_0,0)=e^{-x_0^2}=e^{-(xe^{-2t})^2}=e^{-x^2e^{-4t}}$$

2.

$$\begin{cases} u_t - x u_x = 0 & x \in \mathbb{R},\, t>0 \\ u(x,0)=\sin(87x) \end{cases}$$

On choisit $x'(t)=-x(t)$, donc | 取 $x'(t)=-x(t)$，因此

$$\frac{d}{dt}u(x(t),t)=u_t-xu_x=0$$

Ainsi $u$ est constante le long des caractéristiques. Or $x'(t)=-x(t)$ donne $x(t)=x_0e^{-t}$, donc $x_0=xe^t$. Par conséquent, | 因此 $u$ 沿特征线保持常数。又因为 $x'(t)=-x(t)$ 给出 $x(t)=x_0e^{-t}$，所以 $x_0=xe^t$。从而

$$u(x,t)=u(x_0,0)=\sin(87x_0)=\sin(87xe^t)$$

3.

$$\begin{cases} u_t + x u_x = x & x \in \mathbb{R},\, t>0 \\ u(x,0)=\cos(90x) \end{cases}$$

On choisit $x'(t)=x(t)$. Alors | 取 $x'(t)=x(t)$。于是

$$\frac{d}{dt}u(x(t),t)=u_t+xu_x=x(t)$$

Or $x'(t)=x(t)$ donne $x(t)=x_0e^t$, donc $x_0=xe^{-t}$. En intégrant le long de la caractéristique, | 而 $x'(t)=x(t)$ 给出 $x(t)=x_0e^t$，因此 $x_0=xe^{-t}$。沿着特征线积分，

$$u(x,t)=u(x_0,0)+\int_0^t x(s)\,ds$$

donc, comme $x(s)=x_0e^s$, | 因此，由于 $x(s)=x_0e^s$，

$$u(x,t)=\cos(90x_0)+\int_0^t x_0e^s\,ds=\cos(90xe^{-t})+x(1-e^{-t})$$

4.

$$\begin{cases} u_t + x u_x = x^2 & x \in \mathbb{R},\, t>0 \\ u(x,0)=\sin(87x)\cos(90x) \end{cases}$$

On choisit encore $x'(t)=x(t)$, donc $x(t)=x_0e^t$ et $x_0=xe^{-t}$. | 仍然取 $x'(t)=x(t)$，于是 $x(t)=x_0e^t$ 且 $x_0=xe^{-t}$。

Le long d'une caractéristique, on obtient | 沿着一条特征线，有

$$\frac{d}{dt}u(x(t),t)=u_t+xu_x=x(t)^2=x_0^2e^{2t}$$

En intégrant, | 对其积分，

$$u(x,t)=\sin(87x_0)\cos(90x_0)+\int_0^t x_0^2e^{2s}\,ds$$

Ainsi, | 因而

$$u(x,t)=\sin(87xe^{-t})\cos(90xe^{-t})+\frac{x^2}{2}(1-e^{-2t})$$

## Exercice 5 | 练习 5

Calculer la solution exacte du problème de Cauchy suivant : | 求解下列 Cauchy 问题的精确解：

$$\begin{cases} u_t + u_x = u & x \in \mathbb{R},\, t>0 \\ u(x,0)=\phi(x) & x \in \mathbb{R} \end{cases}$$

où $\phi$ est une fonction régulière donnée. | 其中 $\phi$ 是给定的光滑函数。

**Éléments de réponse** | **答案要点**

On pose $x=x(t)$ une caractéristique. Comme | 令 $x=x(t)$ 为一条特征线。由于

$$\frac{d}{dt}u(x(t),t)=u_t+x'(t)u_x$$

on choisit $x'(t)=1$, ce qui donne | 取 $x'(t)=1$，于是得到

$$\frac{d}{dt}u(x(t),t)=u_t+u_x=u$$

La caractéristique vérifie $x(t)=x_0+t$, donc $x_0=x-t$. Le long de cette caractéristique, on résout $\dfrac{du}{dt}=u$, d'où $u(x(t),t)=Ke^t$. | 特征线满足 $x(t)=x_0+t$，因此 $x_0=x-t$。沿该特征线求解 $\dfrac{du}{dt}=u$，可得 $u(x(t),t)=Ke^t$。

Avec la condition initiale, $u(x_0,0)=K=\phi(x_0)$. Ainsi, | 结合初始条件 $u(x_0,0)=K=\phi(x_0)$。因此

$$u(x,t)=e^t\phi(x_0)=e^t\phi(x-t)$$

## Exercice 6 | 练习 6

Considérons le problème de Cauchy suivant : | 考虑下列 Cauchy 问题：

$$\begin{cases} u_t + a u_x = b(x,t) & x \in \mathbb{R},\, t>0 \\ u(x,0)=\phi(x) & x \in \mathbb{R} \end{cases}$$

où $a$ est une constante et $\phi$ et $b$ sont des fonctions régulières données. | 其中 $a$ 是常数，$\phi$ 和 $b$ 是给定的光滑函数。

Considérons également le problème de Cauchy suivant : | 再考虑下面这个 Cauchy 问题：

$$\begin{cases} v_t + a v_x = b(x,t) & x \in \mathbb{R},\, t>0 \\ v(x,0)=\phi(x)+\epsilon(x) & x \in \mathbb{R} \end{cases}$$

où $\epsilon$ est une fonction régulière. | 其中 $\epsilon$ 是一个光滑函数。

1. Montrer que : | 证明：

$$\sup_{x \in \mathbb{R},\, t \geq 0}|u(x,t)-v(x,t)|=\sup_{x \in \mathbb{R}}|\epsilon(x)|$$

2. Conclure. | 并作出结论。

**Éléments de réponse** | **答案要点**

Comme $a$ est constante, les caractéristiques vérifient $x'(s)=a$. La caractéristique passant par $(x,t)$ est $x(s)=x-a(t-s)$, et son point initial est $x(0)=x-at$. | 由于 $a$ 是常数，特征线满足 $x'(s)=a$。经过点 $(x,t)$ 的特征线为 $x(s)=x-a(t-s)$，其初始点为 $x(0)=x-at$。

Pour le premier problème, | 对第一个问题，

$$u(x,t)=\phi(x-at)+\int_0^t b(x-a(t-s),s)\,ds$$

et pour le second, | 而对第二个问题，

$$v(x,t)=\phi(x-at)+\epsilon(x-at)+\int_0^t b(x-a(t-s),s)\,ds$$

Donc, en supposant $\epsilon$ bornée, | 因此，在假设 $\epsilon$ 有界的情况下，

$$u(x,t)-v(x,t)=-\epsilon(x-at)$$

et | 并且

$$\sup_{x\in\mathbb{R},\,t\ge 0}|u(x,t)-v(x,t)|=\sup_{x\in\mathbb{R},\,t\ge 0}|\epsilon(x-at)|=\sup_{y\in\mathbb{R}}|\epsilon(y)|$$

On conclut que le problème est stable par rapport à une perturbation de la condition initiale. | 由此可见，这个问题对于初始条件的扰动是稳定的。

## Exercice 7 | 练习 7

Considérons l'équation des ondes : | 考虑波动方程：

$$\begin{cases} u_{tt}=c^2u_{xx} & x \in \mathbb{R},\, t>0 \\ u(x,0)=\phi(x) & x \in \mathbb{R} \\ u_t(x,0)=\psi(x) & x \in \mathbb{R} \end{cases}$$

pour un $c>0$. | 其中 $c>0$。

1. Montrer que la solution de ce problème s'écrit : | 证明该问题的解可以写成：

$$u(x,t)=\frac{1}{2}\left(\phi(x+ct)+\phi(x-ct)\right)+\frac{1}{2c}\int_{x-ct}^{x+ct}\psi(\theta)\,d\theta$$

2. En utilisant le résultat précédent trouver la solution du problème suivant : | 利用前面的结果，求解下列问题：

$$\begin{cases} u_{tt}=16u_{xx} & x \in \mathbb{R},\, t>0 \\ u(x,0)=6\sin^2(x) & x \in \mathbb{R} \\ u_t(x,0)=\cos(6x) & x \in \mathbb{R} \end{cases}$$

3. Posons $v=u_t+cu_x$ où $u$ est la solution de l'équation des ondes initiales. | 令 $v=u_t+cu_x$，其中 $u$ 是原始波动方程的解。

(a) Montrer que : | (a) 证明：

$$v_t-cv_x=0$$

(b) Exprimer $v$ en fonction de $\phi$ et $\psi$. | (b) 用 $\phi$ 和 $\psi$ 表示 $v$。

(c) Montrer que : | (c) 证明：

$$u(x,t)=\phi(x-ct)+\int_0^t v[x-c(t-\tau),\tau]\,d\tau$$

(d) En déduire la forme de $u$ donnée à la question 1. | (d) 由此推出第 1 问中给出的 $u$ 的表达式。

**Éléments de réponse** | **答案要点**

1. La formule de d'Alembert, vue dans le cours par changement de variables, donne directement : | 课程中通过变量变换得到的 d'Alembert 公式直接给出：

$$u(x,t)=\frac{1}{2}\left(\phi(x+ct)+\phi(x-ct)\right)+\frac{1}{2c}\int_{x-ct}^{x+ct}\psi(\theta)\,d\theta$$

2. Ici $c=4$, $\phi(x)=6\sin^2(x)$ et $\psi(x)=\cos(6x)$. Donc | 这里 $c=4$，$\phi(x)=6\sin^2(x)$，且 $\psi(x)=\cos(6x)$。因此

$$u(x,t)=3\sin^2(x+4t)+3\sin^2(x-4t)+\frac{1}{8}\int_{x-4t}^{x+4t}\cos(6\theta)\,d\theta$$

Ainsi, | 从而

$$u(x,t)=3\sin^2(x+4t)+3\sin^2(x-4t)+\frac{\sin(6x+24t)-\sin(6x-24t)}{48}$$

3. On pose $v=u_t+cu_x$. | 令 $v=u_t+cu_x$。

(a) On calcule : | (a) 计算：

$$v_t-cv_x=(u_{tt}+cu_{xt})-c(u_{tx}+cu_{xx})=u_{tt}-c^2u_{xx}=0$$

(b) On a $v(x,0)=u_t(x,0)+cu_x(x,0)=\psi(x)+c\phi'(x)$. Comme $v_t-cv_x=0$, les caractéristiques donnent | 有 $v(x,0)=u_t(x,0)+cu_x(x,0)=\psi(x)+c\phi'(x)$。由于 $v_t-cv_x=0$，特征线方法给出

$$v(x,t)=v(x+ct,0)=\psi(x+ct)+c\phi'(x+ct)$$

(c) Pour la courbe $y(\tau)=x-c(t-\tau)$, on a $y'(\tau)=c$, donc | 对曲线 $y(\tau)=x-c(t-\tau)$，有 $y'(\tau)=c$，因此

$$\frac{d}{d\tau}u(y(\tau),\tau)=u_t(y(\tau),\tau)+cu_x(y(\tau),\tau)=v(y(\tau),\tau)$$

En intégrant entre $0$ et $t$ : | 在 $0$ 到 $t$ 之间积分：

$$u(x,t)=\phi(x-ct)+\int_0^t v[x-c(t-\tau),\tau]\,d\tau$$

(d) En utilisant l'expression de $v$ : | (d) 利用 $v$ 的表达式：

$$u(x,t)=\phi(x-ct)+\int_0^t \left(\psi(x-ct+2c\tau)+c\phi'(x-ct+2c\tau)\right)\,d\tau$$

Avec le changement de variable $s=x-ct+2c\tau$, on retrouve | 作变量代换 $s=x-ct+2c\tau$，可重新得到

$$u(x,t)=\frac{\phi(x+ct)+\phi(x-ct)}{2}+\frac{1}{2c}\int_{x-ct}^{x+ct}\psi(s)\,ds$$

## Exercice 8 | 练习 8

Résoudre les EDP suivantes en faisant le changement de variable proposé : | 按照给定的变量变换求解下列偏微分方程：

1.

$$\partial_x f-\partial_y f=a$$

en posant $u=x+y$ et $v=x-y$ où $a$ est une constante réelle. | 令 $u=x+y$，$v=x-y$，其中 $a$ 为实常数。

2.

$$x\partial_x f=y\partial_y f$$

en posant $u=xy$ et $v=x/y$. | 令 $u=xy$，$v=x/y$。

3.

$$x\partial_x f=-y\partial_y f$$

en posant $x=\rho\cos(\theta)$ et $y=\rho\sin(\theta)$. | 令 $x=\rho\cos(\theta)$，$y=\rho\sin(\theta)$。

4.

$$y\partial_x f-x\partial_y f=2f$$

en posant $x=\rho\cos(\theta)$ et $y=\rho\sin(\theta)$. | 令 $x=\rho\cos(\theta)$，$y=\rho\sin(\theta)$。

5.

$$2xy\partial_x f+(1+y^2)\partial_y f=0$$

en posant $x=(u^2+v^2)/2$ et $y=u/v$. | 令 $x=(u^2+v^2)/2$ 且 $y=u/v$。

**Éléments de réponse** | **答案要点**

1. On pose $f(x,y)=F(u,v)$ avec $u=x+y$ et $v=x-y$. Alors $\partial_x f=F_u+F_v$ et $\partial_y f=F_u-F_v$. Donc | 令 $f(x,y)=F(u,v)$，其中 $u=x+y$ 且 $v=x-y$。于是 $\partial_x f=F_u+F_v$，$\partial_y f=F_u-F_v$。因此

$$\partial_x f-\partial_y f=2F_v=a$$

Ainsi $F(u,v)=\dfrac{a}{2}v+\varphi(u)$, donc | 因而 $F(u,v)=\dfrac{a}{2}v+\varphi(u)$，所以

$$f(x,y)=\frac{a}{2}(x-y)+\varphi(x+y)$$

2. On pose $f(x,y)=F(u,v)$ avec $u=xy$ et $v=x/y$. Alors | 令 $f(x,y)=F(u,v)$，其中 $u=xy$ 且 $v=x/y$。于是

$$\partial_x f=yF_u+\frac{1}{y}F_v,\qquad \partial_y f=xF_u-\frac{x}{y^2}F_v$$

L'équation $x\partial_x f=y\partial_y f$ donne $2\dfrac{x}{y}F_v=0$, donc $F_v=0$. Ainsi, | 方程 $x\partial_x f=y\partial_y f$ 给出 $2\dfrac{x}{y}F_v=0$，因此 $F_v=0$。于是

$$f(x,y)=\varphi(xy)$$

3. En coordonnées polaires $f(x,y)=F(\rho,\theta)$, on a | 在极坐标下令 $f(x,y)=F(\rho,\theta)$，则有

$$x\partial_x f+y\partial_y f=\rho F_\rho$$

L'équation $x\partial_x f=-y\partial_y f$ équivaut donc à $x\partial_x f+y\partial_y f=0$, c'est-à-dire $\rho F_\rho=0$. Donc $F$ ne dépend que de $\theta$ : | 所以方程 $x\partial_x f=-y\partial_y f$ 等价于 $x\partial_x f+y\partial_y f=0$，也就是 $\rho F_\rho=0$。因此 $F$ 只依赖于 $\theta$：

$$f(x,y)=\varphi(\theta)$$

4. En coordonnées polaires, on a | 在极坐标下，有

$$F_\theta=-y\partial_x f+x\partial_y f$$

Donc $y\partial_x f-x\partial_y f=-F_\theta$. L'équation devient $-F_\theta=2F$, donc | 因此 $y\partial_x f-x\partial_y f=-F_\theta$。方程化为 $-F_\theta=2F$，从而

$$F(\rho,\theta)=e^{-2\theta}\varphi(\rho)$$

Ainsi, | 因而

$$f(x,y)=e^{-2\theta}\varphi(\rho)$$

5. On pose $f(x,y)=F(u,v)$ avec $x=(u^2+v^2)/2$ et $y=u/v$. En notant | 令 $f(x,y)=F(u,v)$，其中 $x=(u^2+v^2)/2$ 且 $y=u/v$。记

$$L=2xy\partial_x+(1+y^2)\partial_y$$

on obtient $L(v)=0$ et $L(u)=\dfrac{u^2+v^2}{v}$. L'équation $L(f)=0$ devient donc | 可以得到 $L(v)=0$ 且 $L(u)=\dfrac{u^2+v^2}{v}$。因此方程 $L(f)=0$ 变为

$$\frac{u^2+v^2}{v}F_u=0$$

Ainsi $F_u=0$, donc | 因而 $F_u=0$，所以

$$f(x,y)=\varphi(v)$$

avec $v^2=\dfrac{2x}{1+y^2}$. Selon le domaine considéré, on peut écrire par exemple $f(x,y)=\varphi\left(\sqrt{\dfrac{2x}{1+y^2}}\right)$, à un choix de signe près pour $v$. | 其中 $v^2=\dfrac{2x}{1+y^2}$。根据所考虑的定义域，例如可以写成 $f(x,y)=\varphi\left(\sqrt{\dfrac{2x}{1+y^2}}\right)$，这里只差一个关于 $v$ 的符号选择。

## Exercice 9 | 练习 9

Considérons l'EDP suivante (équation des ondes unidimensionnelle) : | 考虑下列偏微分方程（一维波动方程）：

$$\begin{cases} \dfrac{\partial^2 u}{\partial t^2}=c_0^2\dfrac{\partial^2 u}{\partial x^2} & \text{pour } x \in ]0,L[ \text{ et } t>0 \\ u(0,t)=u(L,t)=0 & \text{pour } t>0 \\ u(x,0)=f(x) \\ \dfrac{\partial u}{\partial t}(x,0)=g(x) \end{cases}$$

1. Résoudre cette EDP en utilisant la méthode de séparation de variables. | 用变量分离法求解这个偏微分方程。
2. Donner la solution pour les conditions suivantes : | 在下列条件下写出解：

   - $L=\pi$
   - $f(x)=\sin(3x)-4\sin(10x)$
   - $g(x)=2\sin(4x)+\sin(6x)$

**Éléments de réponse** | **答案要点**

On cherche $u(x,t)=X(x)T(t)$. En injectant dans $u_{tt}=c_0^2u_{xx}$, on obtient | 设 $u(x,t)=X(x)T(t)$。代入 $u_{tt}=c_0^2u_{xx}$，得到

$$\frac{T''}{c_0^2T}=\frac{X''}{X}=-\lambda$$

donc | 因此

$$X''+\lambda X=0,\qquad T''+c_0^2\lambda T=0$$

Les conditions $u(0,t)=u(L,t)=0$ donnent $X(0)=X(L)=0$. Comme dans le cours, | 边界条件 $u(0,t)=u(L,t)=0$ 给出 $X(0)=X(L)=0$。与课程中相同，

$$\lambda_n=\left(\frac{n\pi}{L}\right)^2,\qquad X_n(x)=\sin\left(\frac{n\pi}{L}x\right),\qquad n\in\mathbb{N}^*$$

et | 并且

$$T_n(t)=A_n\cos\left(\frac{c_0n\pi}{L}t\right)+B_n\sin\left(\frac{c_0n\pi}{L}t\right)$$

La solution générale est donc | 因此通解为

$$u(x,t)=\sum_{n=1}^{+\infty}\left[A_n\cos\left(\frac{c_0n\pi}{L}t\right)+B_n\sin\left(\frac{c_0n\pi}{L}t\right)\right]\sin\left(\frac{n\pi}{L}x\right)$$

Avec $u(x,0)=f(x)$, | 由 $u(x,0)=f(x)$，

$$A_n=\frac{2}{L}\int_0^L f(x)\sin\left(\frac{n\pi}{L}x\right)\,dx$$

et avec $u_t(x,0)=g(x)$, | 而由 $u_t(x,0)=g(x)$，

$$B_n=\frac{2}{c_0n\pi}\int_0^L g(x)\sin\left(\frac{n\pi}{L}x\right)\,dx$$

Pour $L=\pi$, $f(x)=\sin(3x)-4\sin(10x)$ et $g(x)=2\sin(4x)+\sin(6x)$, on obtient | 当 $L=\pi$，$f(x)=\sin(3x)-4\sin(10x)$，且 $g(x)=2\sin(4x)+\sin(6x)$ 时，得到

$$u(x,t)=\cos(3c_0t)\sin(3x)-4\cos(10c_0t)\sin(10x)+\frac{1}{2c_0}\sin(4c_0t)\sin(4x)+\frac{1}{6c_0}\sin(6c_0t)\sin(6x)$$

## Exercice 10 | 练习 10

Considérons le problème suivant : | 考虑下列问题：

$$\begin{cases} u'(t)=-u(t) \\ u(0)=1 \end{cases}$$

1. Quelle est la solution exacte de ce problème ? | 这个问题的精确解是什么？
2. Montrer que la méthode d'Euler explicite mène à la solution numérique suivante : | 证明显式 Euler 方法得到下面这个数值解：

$$u_m=(1-\Delta t)^m, \qquad m=0,1,\ldots$$

3. Montrer que la solution converge en $t=1$ quand $\Delta t$ tend vers $0$. | 证明当 $\Delta t$ 趋于 $0$ 时，解在 $t=1$ 处收敛。
4. Montrer que : | 证明：

$$\frac{u(t_{m+1})-u(t_m)}{\Delta t} \approx u'(t_{m+1})=f(u(t_{m+1}))$$

5. Donner le schéma d'Euler implicite qui se base sur la formulation précédente. | 给出基于上式的隐式 Euler 格式。
6. En déduire que : | 由此推出：

$$u_m=\frac{1}{(1+\Delta t)^m}, \qquad m=0,1,\ldots$$

7. Montrer que : | 证明：

$$\frac{u(t_{m+1})-u(t_m)}{\Delta t} \approx \frac{f(u(t_{m+1}))+f(u(t_m))}{2}$$

8. En déduire le schéma numérique suivant : | 由此推出下面这个数值格式：

$$u_{m+1}-\frac{1}{2}\Delta t\,f(u_{m+1})=u_m+\frac{1}{2}\Delta t\,f(u_m), \qquad m=0,1,\ldots$$

9. Montrer alors que la solution numérique vaut : | 证明这时数值解为：

$$u_m=\left(\frac{2-\Delta t}{2+\Delta t}\right)^m, \qquad m=0,1,\ldots$$

10. Comparer la précision des trois méthodes en calculant par exemple la solution à $t=1$. Montrer que les erreurs respectives sont de l'ordre de $k\Delta t$ pour les 2 premières et de l'ordre de $k\Delta t^2$ pour le dernier schéma. | 例如通过计算 $t=1$ 时的解来比较这三种方法的精度。说明前两种方法的误差分别是 $k\Delta t$ 阶，而最后一种格式的误差是 $k\Delta t^2$ 阶。
11. Refaire l'étude avec le problème suivant : | 对下列问题重新做同样的研究：

$$\begin{cases} u'(t)=-u^2(t) \\ u(0)=1 \end{cases}$$

**Éléments de réponse** | **答案要点**

1. La solution exacte est $u(t)=e^{-t}$. | 精确解是 $u(t)=e^{-t}$。

2. La méthode d'Euler explicite donne $u_{m+1}=u_m+\Delta t f(u_m)=(1-\Delta t)u_m$. Comme $u_0=1$, | 显式 Euler 方法给出 $u_{m+1}=u_m+\Delta t f(u_m)=(1-\Delta t)u_m$。由于 $u_0=1$，

$$u_m=(1-\Delta t)^m$$

3. À $t=1$, on prend $m=N$ et $\Delta t=1/N$. Alors | 在 $t=1$ 时，取 $m=N$ 且 $\Delta t=1/N$。于是

$$u_N=\left(1-\frac{1}{N}\right)^N\longrightarrow e^{-1}$$

4. L'approximation arrière s'écrit | 后向近似写成

$$\frac{u(t_{m+1})-u(t_m)}{\Delta t}\approx u'(t_{m+1})=f(u(t_{m+1}))$$

5. Le schéma d'Euler implicite est donc | 因此隐式 Euler 格式为

$$\frac{u_{m+1}-u_m}{\Delta t}=f(u_{m+1})=-u_{m+1}$$

6. On en déduit $(1+\Delta t)u_{m+1}=u_m$, donc | 由此得到 $(1+\Delta t)u_{m+1}=u_m$，因此

$$u_m=\frac{1}{(1+\Delta t)^m}$$

7. Le schéma centré en temps donne | 时间中心格式给出

$$\frac{u(t_{m+1})-u(t_m)}{\Delta t}\approx\frac{f(u(t_{m+1}))+f(u(t_m))}{2}$$

8. Donc | 因此

$$u_{m+1}-\frac{1}{2}\Delta t\,f(u_{m+1})=u_m+\frac{1}{2}\Delta t\,f(u_m)$$

9. Pour $f(u)=-u$, cela donne | 对于 $f(u)=-u$，这变为

$$u_{m+1}+\frac{\Delta t}{2}u_{m+1}=u_m-\frac{\Delta t}{2}u_m$$

donc | 因此

$$u_m=\left(\frac{2-\Delta t}{2+\Delta t}\right)^m$$

10. À $t=1$, avec $\Delta t=1/N$ : | 在 $t=1$ 时，取 $\Delta t=1/N$：

$$\left(1-\Delta t\right)^{1/\Delta t}=e^{-1}+O(\Delta t),\qquad \left(1+\Delta t\right)^{-1/\Delta t}=e^{-1}+O(\Delta t)$$

et | 并且

$$\left(\frac{2-\Delta t}{2+\Delta t}\right)^{1/\Delta t}=e^{-1}+O(\Delta t^2)$$

Les deux méthodes d'Euler sont donc d'ordre 1, tandis que le dernier schéma est d'ordre 2. | 因此前两种 Euler 方法都是一阶的，而最后一个格式是二阶的。

11. Pour $u'(t)=-u^2(t)$, la solution exacte est | 对于 $u'(t)=-u^2(t)$，精确解是

$$u(t)=\frac{1}{1+t}$$

Les trois schémas deviennent : | 三个格式变为：

$$\text{Euler explicite :}\qquad u_{m+1}=u_m-\Delta t\,u_m^2$$

$$\text{Euler implicite :}\qquad u_{m+1}=u_m-\Delta t\,u_{m+1}^2$$

donc on prend la racine positive | 因此取正根

$$u_{m+1}=\frac{-1+\sqrt{1+4\Delta t\,u_m}}{2\Delta t}$$

$$\text{Schéma centré :}\qquad u_{m+1}+\frac{\Delta t}{2}u_{m+1}^2=u_m-\frac{\Delta t}{2}u_m^2$$

donc on prend également la racine positive | 因此同样取正根

$$u_{m+1}=\frac{-1+\sqrt{1+2\Delta t\,u_m-\Delta t^2u_m^2}}{\Delta t}$$

Sous les hypothèses régulières usuelles, les deux schémas d'Euler restent d'ordre 1 et le schéma centré reste d'ordre 2. | 在通常的正则性假设下，两种 Euler 格式仍然是一阶，而中心格式仍然是二阶。
