# Techniques de modélisation | 建模技术

**Année** : 2024-2025 | **学年**：2024-2025  
**Session** : 1 | **场次**：1  
**Durée** : 2 heures | **时长**：2 小时

---

## Exercice 1 | 练习 1

On considère l'équation de Burgers avec viscosité : | 考虑带粘性的 Burgers 方程：

$$\frac{\partial u}{\partial t} + u \frac{\partial u}{\partial x} = \nu \frac{\partial^2 u}{\partial x^2}.$$

Soit $\varphi$ vérifiant | 设 $\varphi$ 满足

$$u = -2\nu \frac{\varphi_x}{\varphi},$$

alors, lorsque $u$ satisfait l'équation de Burgers, $\varphi$ vérifie : | 那么当 $u$ 满足 Burgers 方程时，$\varphi$ 满足：

$$\frac{\partial \varphi}{\partial t} = \nu \frac{\partial^2 \varphi}{\partial x^2}.$$

L'objet de cette question est de montrer ce résultat. | 本题的目标就是证明这个结果。

1. Soit $\tilde{\psi}$ telle que $u = \tilde{\psi}_x$, montrer que : | 设 $\tilde{\psi}$ 满足 $u = \tilde{\psi}_x$，证明：

$$\left(\tilde{\psi}_t + \frac{1}{2}\tilde{\psi}_x^2 - \nu \tilde{\psi}_{xx}\right)_x = 0.$$

2. En déduire qu'il existe une fonction $K$ qui ne dépend que de $t$ telle que : | 由此推出存在一个只依赖于 $t$ 的函数 $K$，使得：

$$\tilde{\psi}_t + \frac{1}{2}\tilde{\psi}_x^2 - \nu \tilde{\psi}_{xx} + K(t) = 0.$$

3. On pose | 令

$$\psi(x,t) = \tilde{\psi}(x,t) + \int_0^t K(s)\,ds,$$

montrer que : | 证明：

$$\psi_t + \frac{1}{2}\psi_x^2 = \nu \psi_{xx} \qquad \text{et} \qquad u = \psi_x.$$

4. Posons $\psi = -2\nu \log \varphi$ montrer alors que : | 令 $\psi = -2\nu \log \varphi$，证明：

$$\psi_t + \frac{1}{2}\psi_x^2 - \nu \psi_{xx} = -\frac{2\nu}{\varphi}\left(\varphi_t - \nu \varphi_{xx}\right).$$

5. Conclure. | 作出结论。

**Éléments de réponse** | **答案要点**

1. Comme $u=\tilde{\psi}_x$, on a $u_t=\tilde{\psi}_{xt}$, $u_x=\tilde{\psi}_{xx}$ et $u_{xx}=\tilde{\psi}_{xxx}$. | 由于 $u=\tilde{\psi}_x$，所以有 $u_t=\tilde{\psi}_{xt}$，$u_x=\tilde{\psi}_{xx}$，以及 $u_{xx}=\tilde{\psi}_{xxx}$。

   En remplaçant dans l'équation de Burgers, on obtient | 把这些关系代入 Burgers 方程，得到

   $$\tilde{\psi}_{xt}+\tilde{\psi}_x\tilde{\psi}_{xx}-\nu \tilde{\psi}_{xxx}=0.$$

   Or | 而

   $$\tilde{\psi}_x\tilde{\psi}_{xx}=\left(\frac{1}{2}\tilde{\psi}_x^2\right)_x \qquad \text{et} \qquad \tilde{\psi}_{xxx}=(\tilde{\psi}_{xx})_x.$$

   Donc | 因此

   $$\left(\tilde{\psi}_t+\frac{1}{2}\tilde{\psi}_x^2-\nu \tilde{\psi}_{xx}\right)_x=0.$$

2. Si la dérivée par rapport à $x$ est nulle, alors la quantité entre parenthèses ne dépend que de $t$. | 如果对 $x$ 的导数为零，那么括号中的量只依赖于 $t$。  
   Il existe donc une fonction $C(t)$ telle que | 因而存在一个函数 $C(t)$，使得

   $$\tilde{\psi}_t+\frac{1}{2}\tilde{\psi}_x^2-\nu \tilde{\psi}_{xx}=C(t).$$

   En posant $C(t)=-K(t)$, on obtient bien | 令 $C(t)=-K(t)$，就得到

   $$\tilde{\psi}_t+\frac{1}{2}\tilde{\psi}_x^2-\nu \tilde{\psi}_{xx}+K(t)=0.$$

3. On a | 我们有

   $$\psi_t=\tilde{\psi}_t+K(t), \qquad \psi_x=\tilde{\psi}_x, \qquad \psi_{xx}=\tilde{\psi}_{xx}.$$

   En remplaçant dans l'équation précédente, on trouve | 把它们代入前面的方程，可得

   $$\psi_t+\frac{1}{2}\psi_x^2-\nu \psi_{xx}=0,$$

   c'est-à-dire | 也就是

   $$\psi_t+\frac{1}{2}\psi_x^2=\nu \psi_{xx}.$$

   De plus, comme $\psi$ ne diffère de $\tilde{\psi}$ que par une fonction de $t$, on a | 另外，由于 $\psi$ 与 $\tilde{\psi}$ 只差一个关于 $t$ 的函数，所以

   $$u=\tilde{\psi}_x=\psi_x.$$

4. En posant $\psi=-2\nu \log\varphi$, on calcule | 令 $\psi=-2\nu \log\varphi$，计算得

   $$\psi_t=-2\nu \frac{\varphi_t}{\varphi}, \qquad \psi_x=-2\nu \frac{\varphi_x}{\varphi},$$

   et | 以及

   $$\psi_{xx}=-2\nu\left(\frac{\varphi_{xx}}{\varphi}-\frac{\varphi_x^2}{\varphi^2}\right).$$

   Par conséquent, | 因此，

   $$\frac{1}{2}\psi_x^2=2\nu^2\frac{\varphi_x^2}{\varphi^2}$$

   et | 并且

   $$-\nu\psi_{xx}=2\nu^2\frac{\varphi_{xx}}{\varphi}-2\nu^2\frac{\varphi_x^2}{\varphi^2}.$$

   En sommant, les termes en $\varphi_x^2/\varphi^2$ se simplifient et l'on obtient | 将这些项相加后，含有 $\varphi_x^2/\varphi^2$ 的项会消掉，于是得到

   $$\psi_t+\frac{1}{2}\psi_x^2-\nu\psi_{xx}=-2\nu\frac{\varphi_t}{\varphi}+2\nu^2\frac{\varphi_{xx}}{\varphi}=-\frac{2\nu}{\varphi}\left(\varphi_t-\nu\varphi_{xx}\right).$$

5. D'après la question 3, on a | 根据第 3 问，有

   $$\psi_t+\frac{1}{2}\psi_x^2-\nu\psi_{xx}=0.$$

   D'après la question 4, on a aussi | 根据第 4 问，又有

   $$\psi_t+\frac{1}{2}\psi_x^2-\nu\psi_{xx}
   =-\frac{2\nu}{\varphi}\left(\varphi_t-\nu\varphi_{xx}\right).$$

   En comparant les deux égalités, on obtient | 比较这两个等式，得到

   $$-\frac{2\nu}{\varphi}\left(\varphi_t-\nu\varphi_{xx}\right)=0.$$

   En supposant $\nu\neq 0$ et $\varphi\neq 0$, on en déduit | 在假设 $\nu\neq 0$ 且 $\varphi\neq 0$ 的情况下，可以推出

   $$\varphi_t-\nu\varphi_{xx}=0.$$

   Donc | 因此

   $$\varphi_t=\nu\varphi_{xx}.$$

   On a donc bien montré que, si $u$ satisfait l'équation de Burgers et si
   $u=-2\nu\dfrac{\varphi_x}{\varphi}$, alors $\varphi$ vérifie l'équation de la chaleur. | 因而我们证明了：如果 $u$ 满足 Burgers 方程，并且
   $u=-2\nu\dfrac{\varphi_x}{\varphi}$，那么 $\varphi$ 满足热方程。

## Exercice 2 | 练习 2

L'objectif de cet exercice est de résoudre les EDP proposées. | 本题的目标是求解所给的偏微分方程。

1. Soit $u$ une fonction définie sur $[0,\pi]\times \mathbb{R}^+$ vérifiant l'EDP suivante : | 设 $u$ 是定义在 $[0,\pi]\times \mathbb{R}^+$ 上的函数，并满足下列偏微分方程：

$$\begin{cases} \dfrac{\partial u}{\partial t} = 2\dfrac{\partial^2 u}{\partial x^2}, & x \in ]0,\pi[, \ t>0, \\ \dfrac{\partial u}{\partial x}(0,t) = \dfrac{\partial u}{\partial x}(\pi,t)=0, & t>0, \\ u(x,0)=\cos(3x)-2, & x\in[0,\pi]. \end{cases}$$

Résoudre cette équation en appliquant la méthode de séparation de variables. | 用变量分离法求解该方程。

2. Résoudre l'EDP suivante par la méthode des caractéristiques : | 用特征线法求解下列偏微分方程：

$$\frac{\partial u}{\partial t} + x\frac{\partial u}{\partial x} = u, \qquad u(x,0)=\phi(x).$$

**Éléments de réponse** | **答案要点**

1. On cherche une solution sous la forme $u(t,x)=T(t)X(x)$. | 设解形如 $u(t,x)=T(t)X(x)$。

   En remplaçant dans l'équation, on obtient | 代入方程后得到

   $$T'(t)X(x)=2T(t)X''(x).$$

   En divisant par $2T(t)X(x)$, on trouve | 两边除以 $2T(t)X(x)$，得到

   $$\frac{T'}{2T}=\frac{X''}{X}=-\lambda.$$

   On obtient donc le système | 因而得到如下方程组

   $$X''+\lambda X=0, \qquad T'+2\lambda T=0.$$

   Les conditions de Neumann donnent | Neumann 边界条件给出

   $$X'(0)=X'(\pi)=0.$$

   Les valeurs propres sont $\lambda_n=n^2$ et les fonctions propres sont $X_n(x)=\cos(nx)$ pour $n\ge 0$. | 特征值为 $\lambda_n=n^2$，对应特征函数为 $X_n(x)=\cos(nx)$，其中 $n\ge 0$。  
   Pour $n\ge 1$, on a $T_n(t)=e^{-2n^2t}$, tandis que pour $n=0$, le mode est constant. | 当 $n\ge 1$ 时，有 $T_n(t)=e^{-2n^2t}$；而当 $n=0$ 时，对应的是常数模态。

   Comme la donnée initiale vaut | 由于初始条件是

   $$u(x,0)=\cos(3x)-2,$$

   on lit directement les deux modes présents. | 我们可以直接读出其中只含有两个模态。  
   La solution est donc | 因此解为

   $$u(t,x)=e^{-18t}\cos(3x)-2.$$

2. On applique la méthode des caractéristiques à | 对下面这个方程应用特征线法

   $$u_t+xu_x=u.$$

   Les caractéristiques vérifient | 特征线满足

   $$\frac{dx}{dt}=x.$$

   On obtient | 于是得到

   $$x(t)=\xi e^t,$$

   où $\xi$ est le point de départ à l'instant $t=0$. | 其中 $\xi$ 是在时刻 $t=0$ 的出发点。  
   Donc | 因此

   $$\xi=xe^{-t}.$$

   Le long d'une caractéristique, on a | 沿着特征线，有

   $$\frac{d}{dt}u(x(t),t)=u_t+xu_x=u.$$

   Cette équation donne | 这个方程给出

   $$u(x(t),t)=Ce^t.$$

   En utilisant la donnée initiale $u(\xi,0)=\phi(\xi)$, on trouve $C=\phi(\xi)$. | 利用初值条件 $u(\xi,0)=\phi(\xi)$，可知 $C=\phi(\xi)$。  
   Finalement, | 最终，

   $$u(x,t)=e^t\phi(xe^{-t}).$$

# Techniques de modélisation | 建模技术

**Année** : 2023-2024 | **学年**：2023-2024  
**Session** : 1 | **场次**：1  
**Durée** : 2 heures | **时长**：2 小时

---

## Exercice 1 | 练习 1

Résoudre les équations aux dérivées partielles (EDP) suivantes en effectuant les changements de variables proposés : | 按照题目给定的变量变换，求解下面的偏微分方程：

1.

$$\frac{\partial^2 f}{\partial x^2}=\frac{\partial^2 f}{\partial y^2}$$

où $f$ est de classe $C^2$ en posant | 其中 $f$ 是 $C^2$ 类函数，并令

$$u=\frac{x+y}{2} \qquad \text{et} \qquad v=\frac{x-y}{2}.$$

2.

$$x^2\frac{\partial^2 g}{\partial x^2} + 2xy\frac{\partial^2 g}{\partial x \partial y} + y^2\frac{\partial^2 g}{\partial y^2} = 0$$

où $g$ est de classe $C^2$ en posant $x=w$ et $y=wz$. | 其中 $g$ 是 $C^2$ 类函数，并令 $x=w$，$y=wz$。

**Éléments de réponse** | **答案要点**

1. On pose $f(x,y)=F(u,v)$ avec $u=(x+y)/2$ et $v=(x-y)/2$. | 令 $f(x,y)=F(u,v)$，其中 $u=(x+y)/2$ 且 $v=(x-y)/2$。

   On calcule d'abord | 先计算

   $$f_x=\frac{1}{2}F_u+\frac{1}{2}F_v, \qquad f_y=\frac{1}{2}F_u-\frac{1}{2}F_v.$$

   En dérivant encore, on obtient | 再求一次导数，得到

   $$f_{xx}=\frac{1}{4}(F_{uu}+2F_{uv}+F_{vv}),$$

   $$f_{yy}=\frac{1}{4}(F_{uu}-2F_{uv}+F_{vv}).$$

   L'équation $f_{xx}=f_{yy}$ devient donc | 因此方程 $f_{xx}=f_{yy}$ 变为

   $$F_{uv}=0.$$

   En intégrant par rapport à $u$ puis à $v$, on obtient | 先对 $u$ 再对 $v$ 积分，可得

   $$F(u,v)=A(u)+B(v),$$

   où $A$ et $B$ sont deux fonctions arbitraires de classe $C^2$. | 其中 $A$ 和 $B$ 是两个任意的 $C^2$ 函数。  
   Finalement, | 最终，

   $$f(x,y)=A\left(\frac{x+y}{2}\right)+B\left(\frac{x-y}{2}\right).$$

2. On pose $g(x,y)=G(w,z)$ avec $w=x$ et $z=y/x$. | 令 $g(x,y)=G(w,z)$，其中 $w=x$ 且 $z=y/x$。

   Il est commode d'introduire l'opérateur | 方便起见，引入算子

   $$E=x\partial_x+y\partial_y.$$

   On vérifie que | 可以验证

   $$E^2g=x^2g_{xx}+2xyg_{xy}+y^2g_{yy}+xg_x+yg_y.$$

   Par conséquent, l'équation donnée s'écrit | 因而题目中的方程可以写成

   $$E^2g-Eg=0.$$

   Or, avec le changement de variables proposé, on a | 而在所给变量变换下，有

   $$Eg=xg_x+yg_y=wG_w.$$

   Donc | 因此

   $$E^2g=w\partial_w(wG_w)=wG_w+w^2G_{ww}.$$

   L'équation devient alors | 于是方程化为

   $$w^2G_{ww}=0.$$

   Pour $w\neq 0$, on obtient | 对于 $w\neq 0$，得到

   $$G_{ww}=0.$$

   En intégrant deux fois par rapport à $w$, on trouve | 对 $w$ 积分两次，可得

   $$G(w,z)=A(z)w+B(z),$$

   où $A$ et $B$ sont des fonctions arbitraires. | 其中 $A$ 和 $B$ 是任意函数。  
   En revenant aux variables $(x,y)$, on obtient | 回到变量 $(x,y)$ 后，得到

   $$g(x,y)=xA\left(\frac{y}{x}\right)+B\left(\frac{y}{x}\right).$$

## Exercice 2 | 练习 2

Soit l'équation aux dérivées partielles suivantes : | 设下列偏微分方程：

$$\begin{cases} \dfrac{\partial^2 u}{\partial x^2} + \dfrac{\partial^2 u}{\partial y^2} + 2\dfrac{\partial u}{\partial y} = 0 \\ u(x,0)=\cos\left(x+\dfrac{\pi}{2}\right) \\ \dfrac{\partial u}{\partial y}(x,\pi)=0 \\ u(0,y)=u(\pi,y)=0 \end{cases}$$

Cette EDP représente la distribution de température $u(x,y)$ dans une plaque carrée $[0,\pi]\times[0,\pi]$ de métal non homogène. | 这个偏微分方程描述了非均匀金属方板 $[0,\pi]\times[0,\pi]$ 中的温度分布 $u(x,y)$。

1. Caractériser cette EDP. | 对该偏微分方程进行分类。
2. En utilisant une méthode de séparation de variable $(u = F(x)G(y))$, trouver les équations différentielles vérifiées par $F$ et $G$. | 使用变量分离法 $(u=F(x)G(y))$，求出 $F$ 和 $G$ 所满足的微分方程。
3. Résoudre chacune de ces équations. | 分别求解这些方程。
4. Déterminer $u$. | 写出最终的 $u$。

**Éléments de réponse** | **答案要点**

1. L'équation est une EDP linéaire du second ordre à coefficients constants. | 这个方程是一个二阶常系数线性偏微分方程。  
   Sa partie principale est $u_{xx}+u_{yy}$, dont la matrice associée est l'identité. | 它的主部是 $u_{xx}+u_{yy}$，对应矩阵是单位矩阵。  
   Elle est donc elliptique. | 因此它是椭圆型方程。  
   Elle est aussi homogène puisqu'il n'y a pas de second membre. | 同时由于没有源项，所以它还是齐次的。

2. On cherche $u(x,y)=F(x)G(y)$. | 设 $u(x,y)=F(x)G(y)$。

   En remplaçant dans l'équation, on obtient | 代入方程可得

   $$F''(x)G(y)+F(x)G''(y)+2F(x)G'(y)=0.$$

   En divisant par $F(x)G(y)$, on trouve | 两边除以 $F(x)G(y)$，得到

   $$\frac{F''}{F}+\frac{G''+2G'}{G}=0.$$

   On pose | 令

   $$\frac{F''}{F}=-\lambda.$$

   Alors | 则

   $$F''+\lambda F=0, \qquad G''+2G'-\lambda G=0.$$

3. Les conditions $u(0,y)=u(\pi,y)=0$ donnent $F(0)=F(\pi)=0$. | 边界条件 $u(0,y)=u(\pi,y)=0$ 给出 $F(0)=F(\pi)=0$。  
   Les valeurs propres sont donc | 因而特征值为

   $$\lambda_n=n^2, \qquad n\in\mathbb{N}^*,$$

   et les fonctions propres associées sont | 对应的特征函数为

   $$F_n(x)=\sin(nx).$$

   Pour $G$, on obtient l'équation | 对于 $G$，得到方程

   $$G''+2G'-n^2G=0.$$

   Dans notre cas, la donnée $u(x,0)=\cos(x+\pi/2)=-\sin x$ montre que seul le mode $n=1$ intervient. | 在本题中，初始边界数据 $u(x,0)=\cos(x+\pi/2)=-\sin x$ 表明只有 $n=1$ 这一模态出现。

   On doit donc résoudre | 因此只需要求解

   $$G''+2G'-G=0.$$

   L'équation caractéristique est | 其特征方程为

   $$r^2+2r-1=0,$$

   d'où | 从而

   $$r=-1\pm \sqrt{2}.$$

   Ainsi | 因而

   $$G(y)=Ae^{(-1+\sqrt{2})y}+Be^{(-1-\sqrt{2})y}.$$

   Les conditions restantes sont | 剩下的条件为

   $$G(0)=-1, \qquad G'(\pi)=0.$$

   Une écriture commode satisfaisant $G'(\pi)=0$ est | 一个方便的、自动满足 $G'(\pi)=0$ 的写法是

   $$G(y)=C\,e^{-y}\left[\cosh\bigl(\sqrt{2}(y-\pi)\bigr)+\frac{1}{\sqrt{2}}\sinh\bigl(\sqrt{2}(y-\pi)\bigr)\right].$$

   En imposant $G(0)=-1$, on obtient | 再由 $G(0)=-1$，得到

   $$C=-\frac{1}{\cosh(\sqrt{2}\pi)-\frac{1}{\sqrt{2}}\sinh(\sqrt{2}\pi)}.$$

4. Finalement, la solution est | 最终解为

   $$u(x,y)= -\sin x \,
   \frac{e^{-y}\left[\cosh\bigl(\sqrt{2}(y-\pi)\bigr)+\frac{1}{\sqrt{2}}\sinh\bigl(\sqrt{2}(y-\pi)\bigr)\right]}
   {\cosh(\sqrt{2}\pi)-\frac{1}{\sqrt{2}}\sinh(\sqrt{2}\pi)}.$$

## Exercice 3 | 练习 3

On considère l'EDP suivante sur $\mathbb{R}\times[0,+\infty[ \to \mathbb{R}$ : | 考虑定义在 $\mathbb{R}\times[0,+\infty[$ 上的偏微分方程：

$$\frac{\partial u}{\partial t} - \frac{\partial^2 u}{\partial x^2} - \left(\frac{\partial u}{\partial x}\right)^2 = 0$$

1. Caractériser cette EDP. | 对这个偏微分方程进行分类。
2. Montrer qu'en posant $v=e^u$, cette équation devient : | 证明当令 $v=e^u$ 时，这个方程化为：

$$\frac{\partial v}{\partial t} - \frac{\partial^2 v}{\partial x^2} = 0$$

3. En utilisant la méthode de séparation de variables, résoudre cette équation. | 使用变量分离法求解这个方程。
4. En déduire $u$. | 由此推出 $u$。

**Éléments de réponse** | **答案要点**

1. Cette équation est une EDP du second ordre. | 这个方程是一个二阶偏微分方程。  
   Elle est non linéaire à cause du terme $(u_x)^2$. | 由于含有 $(u_x)^2$ 项，所以它是非线性的。  
   Son type est parabolique, car la partie principale est celle de l'équation de la chaleur. | 它的类型是抛物型，因为它的主部与热方程相同。

2. Posons $v=e^u$. | 令 $v=e^u$。

   Alors | 则

   $$v_t=e^u u_t, \qquad v_x=e^u u_x, \qquad v_{xx}=e^u\bigl(u_{xx}+(u_x)^2\bigr).$$

   Donc | 因此

   $$v_t-v_{xx}=e^u\left(u_t-u_{xx}-(u_x)^2\right).$$

   Comme $u$ vérifie l'équation donnée, on obtient | 由于 $u$ 满足原方程，所以得到

   $$v_t-v_{xx}=0.$$

3. On cherche des solutions séparées sous la forme $v(t,x)=T(t)X(x)$. | 设分离变量解形如 $v(t,x)=T(t)X(x)$。

   En remplaçant dans l'équation de la chaleur, on obtient | 代入热方程，得到

   $$T'(t)X(x)-T(t)X''(x)=0.$$

   En divisant par $T(t)X(x)$, on trouve | 两边除以 $T(t)X(x)$，可得

   $$\frac{T'}{T}=\frac{X''}{X}=-\lambda.$$

   On obtient ainsi | 因而得到

   $$T'+\lambda T=0, \qquad X''+\lambda X=0.$$

   Si $\lambda=k^2>0$, alors | 如果 $\lambda=k^2>0$，那么

   $$T(t)=e^{-k^2t}, \qquad X(x)=A\cos(kx)+B\sin(kx).$$

   On obtient donc une famille de solutions séparées | 因此得到一族分离变量解

   $$v(t,x)=e^{-k^2t}\bigl(A\cos(kx)+B\sin(kx)\bigr).$$

   Si $\lambda=0$, on obtient $T$ constant et $X(x)=Ax+B$. | 如果 $\lambda=0$，那么 $T$ 是常数，而 $X(x)=Ax+B$。

   Si $\lambda=-\mu^2<0$, on obtient | 如果 $\lambda=-\mu^2<0$，则得到

   $$T(t)=e^{\mu^2 t}, \qquad X(x)=Ae^{\mu x}+Be^{-\mu x}.$$

   Sans conditions supplémentaires, les constantes et les combinaisons linéaires restent libres. | 在没有附加条件的情况下，这些常数以及线性组合都保持任意。  
   Plus généralement, toute combinaison linéaire de tels modes est encore solution. | 更一般地，这些模态的任意线性组合仍然是解。

4. Comme $u=\ln v$, on en déduit | 由于 $u=\ln v$，于是得到

   $$u(t,x)=\ln v(t,x),$$

   sur tout domaine où $v(t,x)>0$. | 这个表达式在所有满足 $v(t,x)>0$ 的区域上成立。  
   Par exemple, pour une solution séparée, on a | 例如，对于一个分离变量解，有

   $$u(t,x)=\ln\!\left(e^{-k^2t}\bigl(A\cos(kx)+B\sin(kx)\bigr)\right).$$

## Exercice 4 | 练习 4

Résoudre les EDP suivantes en utilisant la méthode des caractéristiques : | 用特征线法求解下列偏微分方程：

1.

$$\begin{cases} 4\partial_t u(t,x) - 3\partial_x u(t,x) = 0 \\ u(0,x)=x^3 \end{cases}$$

2.

$$\begin{cases} 3\partial_t u(t,x) + 5\partial_x u(t,x) = 0 \\ u(t,0)=t^2 \end{cases}$$

**Éléments de réponse** | **答案要点**

1. On écrit l'équation sous la forme | 把方程写成

   $$u_t-\frac{3}{4}u_x=0.$$

   Les caractéristiques vérifient | 特征线满足

   $$\frac{dx}{dt}=-\frac{3}{4}.$$

   En intégrant, on obtient | 积分得到

   $$x+\frac{3}{4}t=C.$$

   La solution est constante le long des caractéristiques. | 解沿着特征线保持常数。  
   Si l'on note $\xi$ le point d'intersection avec $t=0$, alors | 如果记与 $t=0$ 的交点为 $\xi$，则

   $$\xi=x+\frac{3}{4}t.$$

   Comme $u(0,\xi)=\xi^3$, on obtient | 由于 $u(0,\xi)=\xi^3$，可得

   $$u(t,x)=\left(x+\frac{3}{4}t\right)^3.$$

2. On écrit l'équation sous la forme | 把方程写成

   $$u_t+\frac{5}{3}u_x=0.$$

   Les caractéristiques vérifient | 特征线满足

   $$\frac{dx}{dt}=\frac{5}{3},$$

   d'où | 从而

   $$x-\frac{5}{3}t=C.$$

   Pour un point $(t,x)$, la caractéristique rencontre la droite $x=0$ au temps | 对于点 $(t,x)$，它所在的特征线与直线 $x=0$ 的交点时刻为

   $$\tau=t-\frac{3}{5}x.$$

   La donnée au bord donne alors | 边界条件于是给出

   $$u(t,x)=u(\tau,0)=\tau^2.$$

   Ainsi, sur la région où la caractéristique rencontre bien le bord $x=0$, c'est-à-dire pour $t\ge \dfrac{3}{5}x$, on obtient | 因此，在特征线确实能与边界 $x=0$ 相交的区域，也就是 $t\ge \dfrac{3}{5}x$ 时，有

   $$u(t,x)=\left(t-\frac{3}{5}x\right)^2.$$

# Techniques de modélisation | 建模技术

**Année** : 2021-2022 | **学年**：2021-2022  
**Session** : 1 | **场次**：1  
**Durée** : 2 heures | **时长**：2 小时

---

## Exercice 1 | 练习 1

Soit $u$ une fonction régulière. | 设 $u$ 是一个光滑函数。  
Considérons le schéma aux différences finies suivant : | 考虑如下有限差分格式：

$$\frac{a u_n + b u_{n+1} + c u_{n+2}}{h}$$

où $u_n$, $u_{n+1}$ et $u_{n+2}$ sont les approximations de $u(x_n)$, $u(x_{n+1})$ et de $u(x_{n+2})$, et $h$ le pas de discrétisation. | 其中 $u_n$、$u_{n+1}$ 和 $u_{n+2}$ 分别近似 $u(x_n)$、$u(x_{n+1})$ 和 $u(x_{n+2})$，$h$ 是网格步长。

Déterminer les réels $a$, $b$ et $c$ pour que ce schéma soit une approximation d'ordre 2 de $u'(x_n)$. | 求实数 $a$、$b$ 和 $c$，使这个格式成为 $u'(x_n)$ 的二阶近似。

**Éléments de réponse** | **答案要点**

On développe $u_{n+1}$ et $u_{n+2}$ au voisinage de $x_n$. | 在 $x_n$ 附近对 $u_{n+1}$ 和 $u_{n+2}$ 作 Taylor 展开。

$$u_{n+1}=u_n+h\,u'(x_n)+\frac{h^2}{2}u''(x_n)+\frac{h^3}{6}u^{(3)}(x_n)+\mathcal{O}(h^4),$$

$$u_{n+2}=u_n+2h\,u'(x_n)+2h^2u''(x_n)+\frac{4}{3}h^3u^{(3)}(x_n)+\mathcal{O}(h^4).$$

En remplaçant dans le schéma, on obtient | 代入原格式，得到

$$\frac{a u_n+b u_{n+1}+c u_{n+2}}{h}=
\frac{a+b+c}{h}u_n+(b+2c)u'(x_n)+\left(\frac{b}{2}+2c\right)h\,u''(x_n)+\mathcal{O}(h^2).$$

Pour approcher $u'(x_n)$ à l'ordre 2, il faut imposer | 为了使它成为 $u'(x_n)$ 的二阶近似，需要满足

$$a+b+c=0, \qquad b+2c=1, \qquad \frac{b}{2}+2c=0.$$

La troisième équation donne $b=-4c$. | 第三个方程给出 $b=-4c$。  
En la remplaçant dans la deuxième, on obtient $-2c=1$, donc $c=-\dfrac{1}{2}$. | 把它代入第二个方程，得到 $-2c=1$，因此 $c=-\dfrac{1}{2}$。  
Alors $b=2$, puis $a=-\dfrac{3}{2}$. | 于是 $b=2$，接着 $a=-\dfrac{3}{2}$。

Finalement, | 最终，

$$a=-\frac{3}{2}, \qquad b=2, \qquad c=-\frac{1}{2},$$

et le schéma s'écrit | 该格式写成

$$u'(x_n)\approx \frac{-3u_n+4u_{n+1}-u_{n+2}}{2h},$$

avec une erreur d'ordre 2. | 其误差为二阶。

## Exercice 2 | 练习 2

Considérons le problème suivant : | 考虑下列问题：

$$-u''(x)=f(x), \qquad \text{pour } x \in ]0,1[, \qquad \text{avec } u'(0)=1 \text{ et } u'(1)=0.$$

1. Montrer que $\int_0^1 f(x)\,dx = 1.$ | 证明 $\int_0^1 f(x)\,dx = 1$。
2. Proposer un schéma d'ordre 2 pour l'équation principale. (Vous démontrerez qu'il est d'ordre 2.) | 为主方程提出一个二阶差分格式，并证明其是二阶的。
3. Proposer une discrétisation d'ordre 1 pour les conditions aux limites. | 为边界条件提出一个一阶离散格式。
4. Mettre sous forme matricielle ce schéma (équation principale et conditions aux limites). | 将该格式写成矩阵形式，包括主方程和边界条件。

**Éléments de réponse** | **答案要点**

1. On intègre l'équation sur $[0,1]$. | 在区间 $[0,1]$ 上对方程积分。

   $$\int_0^1 -u''(x)\,dx=\int_0^1 f(x)\,dx.$$

   Donc | 因此

   $$-u'(1)+u'(0)=\int_0^1 f(x)\,dx.$$

   En utilisant $u'(0)=1$ et $u'(1)=0$, on obtient | 利用 $u'(0)=1$ 与 $u'(1)=0$，得到

   $$\int_0^1 f(x)\,dx=1.$$

2. On introduit un maillage uniforme $x_i=ih$ avec $h=1/N$ et $U_i\approx u(x_i)$. | 引入均匀网格 $x_i=ih$，其中 $h=1/N$，并记 $U_i\approx u(x_i)$。

   Pour $1\le i\le N-1$, on utilise la différence centrée classique : | 对于 $1\le i\le N-1$，使用经典的中心差分：

   $$u''(x_i)=\frac{u(x_{i-1})-2u(x_i)+u(x_{i+1})}{h^2}+\mathcal{O}(h^2).$$

   L'équation $-u''(x_i)=f(x_i)$ devient donc | 因而方程 $-u''(x_i)=f(x_i)$ 离散为

   $$-\frac{U_{i-1}-2U_i+U_{i+1}}{h^2}=f(x_i), \qquad 1\le i\le N-1.$$

   Ce schéma est d'ordre 2 car l'erreur de troncature est $\mathcal{O}(h^2)$. | 这个格式是二阶的，因为其截断误差为 $\mathcal{O}(h^2)$。

3. Pour les conditions de Neumann, on peut utiliser des différences avant et arrière d'ordre 1 : | 对于 Neumann 边界条件，可以使用一阶前向和后向差分：

   $$u'(0)\approx \frac{U_1-U_0}{h}, \qquad u'(1)\approx \frac{U_N-U_{N-1}}{h}.$$

   On impose alors | 因而施加

   $$\frac{U_1-U_0}{h}=1, \qquad \frac{U_N-U_{N-1}}{h}=0.$$

4. En multipliant les équations intérieures par $h^2$ et les conditions aux limites par $h$, on obtient | 将内部方程乘以 $h^2$，边界条件乘以 $h$，得到

   $$-U_{i-1}+2U_i-U_{i+1}=h^2 f(x_i), \qquad 1\le i\le N-1,$$

   $$-U_0+U_1=h, \qquad -U_{N-1}+U_N=0.$$

   En posant $\mathbf{U}=(U_0,\dots,U_N)^T$, le système s'écrit | 令 $\mathbf{U}=(U_0,\dots,U_N)^T$，则系统写成

   $$A\mathbf{U}=\mathbf{b},$$

   avec | 其中

   $$A=
   \begin{pmatrix}
   -1 & 1 & 0 & \cdots & 0 & 0 \\
   -1 & 2 & -1 & \ddots & \vdots & \vdots \\
   0 & \ddots & \ddots & \ddots & 0 & 0 \\
   \vdots & \ddots & -1 & 2 & -1 & \vdots \\
   0 & \cdots & 0 & -1 & 2 & -1 \\
   0 & \cdots & 0 & 0 & -1 & 1
   \end{pmatrix},
   \qquad
   \mathbf{b}=
   \begin{pmatrix}
   h \\
   h^2f(x_1) \\
   \vdots \\
   h^2f(x_{N-1}) \\
   0
   \end{pmatrix}.$$

   Comme dans le problème continu avec conditions de Neumann pures, la solution n'est déterminée qu'à une constante additive près. | 与连续问题中的纯 Neumann 边界情形一样，这个离散问题的解也只确定到一个加法常数。  
   La condition de compatibilité obtenue à la question 1 est nécessaire pour l'existence d'une solution. | 第 1 问得到的相容条件是解存在的必要条件。

## Exercice 3 | 练习 3

Considérons le problème $(P_1)$ suivant : | 考虑下列问题 $(P_1)$：

$$\begin{cases} u_t = u_{xx} & \text{pour } x \in \mathbb{R} \text{ et } t>0 \\ u(x,0)=0 \text{ si } x \leq 0,\quad 1 \text{ sinon} \end{cases}$$

1. En faisant le changement de variable $u(x,t)=w(y)$ avec $y=x/\sqrt{t}$, montrer que $(P_1)$ est équivalent à : | 作变量代换 $u(x,t)=w(y)$，其中 $y=x/\sqrt{t}$，证明 $(P_1)$ 等价于：

$$\begin{cases} w''(y) + \dfrac{y}{2}w'(y)=0 \\ w(-\infty)=0 \quad \text{et} \quad w(+\infty)=1 \end{cases}$$

2. Quelle équation est vérifiée par | 下列函数满足什么方程：

$$v(y)=\exp\left(\frac{y^2}{4}\right)w'(y)\, ?$$

3. En admettant que : | 在承认下面恒等式成立的前提下：

$$\int_{-\infty}^{+\infty} e^{-\theta^2}\,d\theta = \sqrt{\pi}$$

montrer que : | 证明：

$$u(x,t)=\frac{1}{\sqrt{\pi}}\int_{-\infty}^{x/(2\sqrt{t})} e^{-\theta^2}\,d\theta$$

**Éléments de réponse** | **答案要点**

1. On pose $u(x,t)=w(y)$ avec $y=x/\sqrt{t}$. | 令 $u(x,t)=w(y)$，其中 $y=x/\sqrt{t}$。

   On calcule | 计算得

   $$y_x=\frac{1}{\sqrt{t}}, \qquad y_t=-\frac{x}{2t^{3/2}}=-\frac{y}{2t}.$$

   Donc | 因此

   $$u_t=w'(y)y_t=-\frac{y}{2t}w'(y), \qquad u_x=\frac{1}{\sqrt{t}}w'(y), \qquad u_{xx}=\frac{1}{t}w''(y).$$

   L'équation $u_t=u_{xx}$ devient alors | 方程 $u_t=u_{xx}$ 于是变为

   $$-\frac{y}{2t}w'(y)=\frac{1}{t}w''(y).$$

   En multipliant par $t$, on obtient | 两边乘以 $t$，得到

   $$w''(y)+\frac{y}{2}w'(y)=0.$$

   Lorsque $t\to 0^+$ avec $x<0$ fixé, on a $y\to -\infty$ et $u(x,t)\to 0$. | 当固定 $x<0$ 且 $t\to 0^+$ 时，有 $y\to -\infty$ 且 $u(x,t)\to 0$。  
   Lorsque $t\to 0^+$ avec $x>0$ fixé, on a $y\to +\infty$ et $u(x,t)\to 1$. | 当固定 $x>0$ 且 $t\to 0^+$ 时，有 $y\to +\infty$ 且 $u(x,t)\to 1$。  
   Ainsi | 因而

   $$w(-\infty)=0, \qquad w(+\infty)=1.$$

2. On pose | 令

   $$v(y)=e^{y^2/4}w'(y).$$

   En dérivant, on obtient | 对它求导，得到

   $$v'(y)=e^{y^2/4}\left(w''(y)+\frac{y}{2}w'(y)\right).$$

   Comme $w$ vérifie l'équation précédente, on a | 由于 $w$ 满足上面的方程，所以有

   $$v'(y)=0.$$

   Donc $v$ est constante. | 因此 $v$ 是常数函数。

3. Comme $v$ est constante, il existe $C$ tel que | 由于 $v$ 是常数，所以存在常数 $C$ 使得

   $$w'(y)=Ce^{-y^2/4}.$$

   En intégrant entre $-\infty$ et $y$, et en utilisant $w(-\infty)=0$, on trouve | 从 $-\infty$ 到 $y$ 积分，并利用 $w(-\infty)=0$，得到

   $$w(y)=C\int_{-\infty}^{y} e^{-s^2/4}\,ds.$$

   En imposant $w(+\infty)=1$, on obtient | 再利用 $w(+\infty)=1$，得到

   $$1=C\int_{-\infty}^{+\infty} e^{-s^2/4}\,ds.$$

   Avec le changement de variable $s=2\theta$, cette intégrale devient | 作变量代换 $s=2\theta$ 后，该积分变为

   $$\int_{-\infty}^{+\infty} e^{-s^2/4}\,ds=2\int_{-\infty}^{+\infty} e^{-\theta^2}\,d\theta=2\sqrt{\pi}.$$

   Donc $C=\dfrac{1}{2\sqrt{\pi}}$. | 因此 $C=\dfrac{1}{2\sqrt{\pi}}$。  
   Finalement, | 最终，

   $$w(y)=\frac{1}{2\sqrt{\pi}}\int_{-\infty}^{y} e^{-s^2/4}\,ds.$$

   En posant à nouveau $s=2\theta$, on obtient | 再次令 $s=2\theta$，得到

   $$w(y)=\frac{1}{\sqrt{\pi}}\int_{-\infty}^{y/2} e^{-\theta^2}\,d\theta.$$

   Comme $y=x/\sqrt{t}$, on en déduit | 由于 $y=x/\sqrt{t}$，因此

   $$u(x,t)=\frac{1}{\sqrt{\pi}}\int_{-\infty}^{x/(2\sqrt{t})} e^{-\theta^2}\,d\theta.$$

## Exercice 4 | 练习 4

Considérons le problème $(E_1)$ suivant : | 考虑下列问题 $(E_1)$：

$$\begin{cases} (1+t)\dfrac{\partial u}{\partial t}(t,x) - \dfrac{\partial^2 u}{\partial x^2}(t,x) = 0 & t \geq 0,\quad x \in [0,1] \\ u(t,0)=0,\quad u(t,1)=0 \\ u(0,x)=f(x) \end{cases}$$

1. Résoudre $(E_1)$ en utilisant la méthode de séparation de variables avec : | 用变量分离法求解 $(E_1)$，其中：

   (a) $f(x)=\sin(2\pi x)+\sin(4\pi x)$ | (a) $f(x)=\sin(2\pi x)+\sin(4\pi x)$

   (b) $f(x)=x$ | (b) $f(x)=x$

2. Considérons à présent le problème $(E_2)$ suivant : | 现在考虑下列问题 $(E_2)$：

$$\begin{cases} (1+t)\dfrac{\partial u}{\partial t}(t,x) - \dfrac{\partial^2 u}{\partial x^2}(t,x) = 0 & t \geq 0,\quad x \in [0,1] \\ u(t,0)=t,\quad u(t,1)=0 \\ u(0,x)=\sin(2\pi x)+\sin(4\pi x) \end{cases}$$

On pose $v(t,x)=-t+xt+u(t,x)$. | 定义 $v(t,x)=-t+xt+u(t,x)$。

(a) Quel est le problème $(E_3)$ vérifié par $v$. | (a) 写出 $v$ 所满足的问题 $(E_3)$。

(b) Résoudre le problème homogène associé. | (b) 求对应的齐次问题。

(c) Comme pourrait-on trouver les solutions de $(E_3)$ ? | (c) 可以如何求解 $(E_3)$？

(d) En déduire la solution de $(E_2)$. | (d) 由此推出 $(E_2)$ 的解。

**Éléments de réponse** | **答案要点**

1. On cherche une solution sous la forme $u(t,x)=T(t)X(x)$. | 设解形如 $u(t,x)=T(t)X(x)$。

   En remplaçant dans $(E_1)$, on obtient | 代入 $(E_1)$，得到

   $$(1+t)T'(t)X(x)-T(t)X''(x)=0.$$

   En divisant par $T(t)X(x)$, on trouve | 两边除以 $T(t)X(x)$，可得

   $$\frac{(1+t)T'}{T}=\frac{X''}{X}=-\lambda.$$

   Ainsi | 因而

   $$X''+\lambda X=0, \qquad (1+t)T'+\lambda T=0.$$

   Les conditions de Dirichlet donnent | Dirichlet 边界条件给出

   $$X(0)=X(1)=0.$$

   On obtient donc | 因而得到

   $$\lambda_n=n^2\pi^2, \qquad X_n(x)=\sin(n\pi x), \qquad n\in\mathbb{N}^*.$$

   Pour la partie temporelle, on a | 对于时间部分，有

   $$T_n(t)=(1+t)^{-n^2\pi^2}.$$

   La solution générale de $(E_1)$ est donc | 因此 $(E_1)$ 的通解为

   $$u(t,x)=\sum_{n=1}^{+\infty} a_n (1+t)^{-n^2\pi^2}\sin(n\pi x),$$

   où les coefficients $a_n$ proviennent du développement en série de Fourier sinusoïdale de $f$. | 其中系数 $a_n$ 由初值函数 $f$ 的正弦 Fourier 展开给出。

   (a) Si $f(x)=\sin(2\pi x)+\sin(4\pi x)$, on lit immédiatement | (a) 若 $f(x)=\sin(2\pi x)+\sin(4\pi x)$，则直接读出

   $$u(t,x)=(1+t)^{-4\pi^2}\sin(2\pi x)+(1+t)^{-16\pi^2}\sin(4\pi x).$$

   (b) Si $f(x)=x$, on développe $x$ sur la base $\sin(n\pi x)$. | (b) 若 $f(x)=x$，则需要把 $x$ 展开到基底 $\sin(n\pi x)$ 上。

   Les coefficients sont | 系数为

   $$a_n=2\int_0^1 x\sin(n\pi x)\,dx=\frac{2(-1)^{n+1}}{n\pi}.$$

   On obtient donc | 因而得到

   $$u(t,x)=\sum_{n=1}^{+\infty}\frac{2(-1)^{n+1}}{n\pi}(1+t)^{-n^2\pi^2}\sin(n\pi x).$$

2. (a) Comme $v=-t+xt+u$, on a | 由于 $v=-t+xt+u$，所以有

   $$u=v+t-xt=v+t(1-x).$$

   On en déduit | 从而得到

   $$u_t=v_t+1-x, \qquad u_{xx}=v_{xx}.$$

   En remplaçant dans $(E_2)$, on trouve | 代入 $(E_2)$，可得

   $$ (1+t)(v_t+1-x)-v_{xx}=0.$$

   Donc $v$ vérifie le problème $(E_3)$ : | 因此 $v$ 满足问题 $(E_3)$：

   $$\begin{cases}
   (1+t)v_t-v_{xx}=-(1+t)(1-x), & t\ge 0,\ x\in[0,1],\\
   v(t,0)=0,\quad v(t,1)=0,\\
   v(0,x)=\sin(2\pi x)+\sin(4\pi x).
   \end{cases}$$

   (b) Le problème homogène associé est | (b) 对应的齐次问题为

   $$\begin{cases}
   (1+t)v_t-v_{xx}=0,\\
   v(t,0)=v(t,1)=0.
   \end{cases}$$

   Sa solution générale s'écrit | 它的通解写成

   $$v_h(t,x)=\sum_{n=1}^{+\infty} b_n (1+t)^{-n^2\pi^2}\sin(n\pi x).$$

   Pour la donnée initiale $\sin(2\pi x)+\sin(4\pi x)$, on a en particulier | 对于初值 $\sin(2\pi x)+\sin(4\pi x)$，特别地有

   $$v_h(t,x)=(1+t)^{-4\pi^2}\sin(2\pi x)+(1+t)^{-16\pi^2}\sin(4\pi x).$$

   (c) Pour résoudre $(E_3)$, on développe $v$ et le second membre sur la base des sinus. | (c) 为了求解 $(E_3)$，把 $v$ 和右端项都展开到正弦基底上。

   On utilise l'identité | 用到恒等式

   $$1-x=\sum_{n=1}^{+\infty}\frac{2}{n\pi}\sin(n\pi x).$$

   On écrit donc | 因而写成

   $$v(t,x)=\sum_{n=1}^{+\infty} c_n(t)\sin(n\pi x).$$

   Chaque coefficient $c_n$ vérifie alors une équation différentielle linéaire du premier ordre. | 于是每个系数 $c_n$ 都满足一个一阶线性常微分方程。  
   On les résout par variation de la constante. | 可以用常数变易法来求解它们。

   (d) En remplaçant cette série dans $(E_3)$, on obtient pour $\lambda_n=n^2\pi^2$ | (d) 把级数代回 $(E_3)$，对 $\lambda_n=n^2\pi^2$ 有

   $$c_n'(t)+\frac{\lambda_n}{1+t}c_n(t)=-\frac{2}{n\pi},$$

   avec | 并且

   $$c_n(0)=
   \begin{cases}
   1,& n=2 \text{ ou } n=4,\\
   0,& \text{sinon}.
   \end{cases}$$

   On en déduit | 由此推出

   $$c_n(t)=(1+t)^{-\lambda_n}c_n(0)-\frac{2}{n\pi(\lambda_n+1)}\left[(1+t)-(1+t)^{-\lambda_n}\right].$$

   Ainsi | 因而

   $$v(t,x)=\sum_{n=1}^{+\infty}\left[(1+t)^{-n^2\pi^2}c_n(0)-\frac{2}{n\pi(n^2\pi^2+1)}\left((1+t)-(1+t)^{-n^2\pi^2}\right)\right]\sin(n\pi x).$$

   Enfin, comme $u=v+t(1-x)$, la solution de $(E_2)$ est | 最后，由于 $u=v+t(1-x)$，所以 $(E_2)$ 的解为

   $$u(t,x)=t(1-x)+\sum_{n=1}^{+\infty}\left[(1+t)^{-n^2\pi^2}c_n(0)-\frac{2}{n\pi(n^2\pi^2+1)}\left((1+t)-(1+t)^{-n^2\pi^2}\right)\right]\sin(n\pi x),$$

   avec $c_2(0)=c_4(0)=1$ et $c_n(0)=0$ sinon. | 其中 $c_2(0)=c_4(0)=1$，其余 $c_n(0)=0$。

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

# Techniques de modélisation | 建模技术

**Année** : 2025-2026 | **学年**：2025-2026  
**TD** : 2 | **习题课**：2

---

## Exercice 1 | 练习 1

Établir les approximations en différences finies des dérivées partielles écrites ci-dessous, en utilisant un développement en série de Taylor. | 利用 Taylor 级数展开，建立下面这些偏导数的有限差分近似。

1.

$$\left(\frac{\partial u}{\partial x}\right)_i=\frac{u_{i+1}-u_{i-1}}{2\Delta x}+\mathcal{O}(\Delta x^2)$$

2.

$$\left(\frac{\partial u}{\partial x}\right)_i=\frac{-u_{i+2}+4u_{i+1}-3u_i}{2\Delta x}+\mathcal{O}(\Delta x^2)$$

3.

$$\left(\frac{\partial u}{\partial x}\right)_i=\frac{3u_i-4u_{i-1}+u_{i-2}}{2\Delta x}+\mathcal{O}(\Delta x^2)$$

**Éléments de réponse** | **答案要点**

On note $h=\Delta x$ et $u_i=u(x_i)$. | 记 $h=\Delta x$，并且 $u_i=u(x_i)$。

1. Différence centrée d'ordre 2 | 2 阶中心差分

   Par Taylor : | 由 Taylor 展开：

   $$u_{i+1}=u_i+h\,u'(x_i)+\frac{h^2}{2}u''(x_i)+\frac{h^3}{6}u^{(3)}(x_i)+\mathcal{O}(h^4),$$

   $$u_{i-1}=u_i-h\,u'(x_i)+\frac{h^2}{2}u''(x_i)-\frac{h^3}{6}u^{(3)}(x_i)+\mathcal{O}(h^4).$$

   En soustrayant, | 两式相减，

   $$u_{i+1}-u_{i-1}=2h\,u'(x_i)+\mathcal{O}(h^3),$$

   donc | 因此

   $$u'(x_i)=\frac{u_{i+1}-u_{i-1}}{2h}+\mathcal{O}(h^2).$$

2. Différence progressive décentrée d'ordre 2 | 2 阶前向偏置差分

   On écrit : | 写出：

   $$u_{i+1}=u_i+h\,u'(x_i)+\frac{h^2}{2}u''(x_i)+\frac{h^3}{6}u^{(3)}(x_i)+\mathcal{O}(h^4),$$

   $$u_{i+2}=u_i+2h\,u'(x_i)+2h^2u''(x_i)+\frac{4}{3}h^3u^{(3)}(x_i)+\mathcal{O}(h^4).$$

   Alors | 那么

   $$-u_{i+2}+4u_{i+1}-3u_i=2h\,u'(x_i)+\mathcal{O}(h^3),$$

   d'où | 从而

   $$u'(x_i)=\frac{-u_{i+2}+4u_{i+1}-3u_i}{2h}+\mathcal{O}(h^2).$$

3. Différence régressive décentrée d'ordre 2 | 2 阶后向偏置差分

   De même : | 同理：

   $$u_{i-1}=u_i-h\,u'(x_i)+\frac{h^2}{2}u''(x_i)-\frac{h^3}{6}u^{(3)}(x_i)+\mathcal{O}(h^4),$$

   $$u_{i-2}=u_i-2h\,u'(x_i)+2h^2u''(x_i)-\frac{4}{3}h^3u^{(3)}(x_i)+\mathcal{O}(h^4).$$

   On en déduit | 由此得到

   $$3u_i-4u_{i-1}+u_{i-2}=2h\,u'(x_i)+\mathcal{O}(h^3),$$

   donc | 因此

   $$u'(x_i)=\frac{3u_i-4u_{i-1}+u_{i-2}}{2h}+\mathcal{O}(h^2).$$

## Exercice 2 | 练习 2

Considérons l'équation suivante : | 考虑下面这个方程：

$$u''(x)+1=0 \qquad \text{sur l'intervalle } \Omega=[0,10]$$

1. Résoudre cette équation : | 求解这个方程：

   (a) avec les conditions aux limites de Dirichlet : $u(0)=100$ et $u(10)=0$ | (a) 取 Dirichlet 边界条件：$u(0)=100$ 且 $u(10)=0$

   (b) avec les conditions mixtes (Dirichlet en $x=0$ et Neumann en $x=10$) : $u(0)=10$ et $\dfrac{du}{dx}(10)=0$ | (b) 取混合边界条件（$x=0$ 处为 Dirichlet，$x=10$ 处为 Neumann）：$u(0)=10$ 且 $\dfrac{du}{dx}(10)=0$

2. Proposer un schéma aux différences finies d'ordre 2 pour cette équation. | 为这个方程提出一个 2 阶有限差分格式。
3. Comment traite-t-on les conditions aux bords dans les deux cas (Dirichlet et mixte) ? | 在这两种情形下（Dirichlet 与混合边界），应如何处理边界条件？
4. Mettre ce schéma sous forme matricielle. | 将该格式写成矩阵形式。
5. Étudier la convergence de ce schéma. | 研究该格式的收敛性。

**Éléments de réponse** | **答案要点**

1. Solutions exactes | 精确解

   L'équation | 方程

   $$u''(x)+1=0$$

   s'écrit $u''(x)=-1$. En intégrant deux fois : | 可以写成 $u''(x)=-1$。对它积分两次：

   $$u'(x)=-x+C, \qquad u(x)=-\frac{x^2}{2}+Cx+D.$$

   (a) Cas de Dirichlet : $u(0)=100$, $u(10)=0$ | (a) Dirichlet 情形：$u(0)=100$，$u(10)=0$

   $$D=100, \qquad -\frac{10^2}{2}+10C+100=0,$$

   donc $C=-5$, et | 因此 $C=-5$，并且

   $$u(x)=-\frac{x^2}{2}-5x+100.$$

   (b) Cas mixte : $u(0)=10$, $u'(10)=0$ | (b) 混合边界情形：$u(0)=10$，$u'(10)=0$

   $$D=10, \qquad -10+C=0,$$

   donc $C=10$, et | 因此 $C=10$，并且

   $$u(x)=-\frac{x^2}{2}+10x+10.$$

2. Schéma aux différences finies d'ordre 2 | 2 阶有限差分格式

   On pose | 设

   $$h=\Delta x=\frac{10}{N}, \qquad x_i=ih, \qquad U_i \approx u(x_i).$$

   Pour $1 \le i \le N-1$, on approche $u''(x_i)$ par la différence centrée d'ordre 2 : | 对于 $1 \le i \le N-1$，用 2 阶中心差分近似 $u''(x_i)$：

   $$u''(x_i)=\frac{u(x_{i-1})-2u(x_i)+u(x_{i+1})}{h^2}+\mathcal{O}(h^2).$$

   On obtient donc le schéma | 因此得到格式

   $$\frac{U_{i-1}-2U_i+U_{i+1}}{h^2}+1=0, \qquad 1 \le i \le N-1,$$

   soit encore | 也就是

   $$U_{i-1}-2U_i+U_{i+1}=-h^2.$$

3. Traitement des conditions aux bords | 边界条件的处理

   Cas de Dirichlet : | Dirichlet 情形：

   $$U_0=100, \qquad U_N=0.$$

   Cas mixte : | 混合边界情形：

   $$U_0=10,$$

   et pour conserver l'ordre 2 au bord $x=10$, on utilise une différence régressive d'ordre 2 : | 为了在边界 $x=10$ 处保持 2 阶精度，使用 2 阶后向差分：

   $$u'(10)=\frac{3u(x_N)-4u(x_{N-1})+u(x_{N-2})}{2h}+\mathcal{O}(h^2).$$

   Comme $u'(10)=0$, on impose | 由于 $u'(10)=0$，于是施加条件

   $$\frac{3U_N-4U_{N-1}+U_{N-2}}{2h}=0.$$

4. Mise sous forme matricielle | 矩阵形式

   Cas de Dirichlet : on prend comme inconnues | Dirichlet 情形中，取未知向量为

   $$\mathbf{U}=(U_1,\dots,U_{N-1})^T.$$

   Le système s'écrit | 该线性系统写成

   $$A_D \mathbf{U}=\mathbf{b}_D,$$

   avec | 其中

   $$A_D=
   \begin{pmatrix}
   -2 & 1 & 0 & \cdots & 0 \\
   1 & -2 & 1 & \ddots & \vdots \\
   0 & \ddots & \ddots & \ddots & 0 \\
   \vdots & \ddots & 1 & -2 & 1 \\
   0 & \cdots & 0 & 1 & -2
   \end{pmatrix},
   \qquad
   \mathbf{b}_D=
   \begin{pmatrix}
   -h^2-100 \\
   -h^2 \\
   \vdots \\
   -h^2 \\
   -h^2
   \end{pmatrix}.$$

   Cas mixte : on prend comme inconnues | 混合边界情形中，取未知向量为

   $$\mathbf{U}=(U_1,\dots,U_N)^T.$$

   Le système s'écrit | 该线性系统写成

   $$A_M \mathbf{U}=\mathbf{b}_M,$$

   avec | 其中

   $$A_M=
   \begin{pmatrix}
   -2 & 1 & 0 & \cdots & 0 & 0 \\
   1 & -2 & 1 & \ddots & \vdots & \vdots \\
   0 & \ddots & \ddots & \ddots & 0 & 0 \\
   \vdots & \ddots & 1 & -2 & 1 & 0 \\
   0 & \cdots & 0 & 1 & -2 & 1 \\
   0 & \cdots & 0 & 1 & -4 & 3
   \end{pmatrix},
   \qquad
   \mathbf{b}_M=
   \begin{pmatrix}
   -h^2-10 \\
   -h^2 \\
   \vdots \\
   -h^2 \\
   -h^2 \\
   0
   \end{pmatrix}.$$

5. Convergence | 收敛性

   Le schéma intérieur est consistant d'ordre 2 puisque | 由于内部格式满足 2 阶一致性，

   $$u''(x_i)-\frac{u(x_{i-1})-2u(x_i)+u(x_{i+1})}{h^2}=\mathcal{O}(h^2).$$

   Dans le cas mixte, la discrétisation de la condition de Neumann est aussi d'ordre 2. | 在混合边界情形下，Neumann 条件的离散化也是 2 阶的。  
   Le système linéaire obtenu est stable : sa matrice est inversible et correspond à l'opérateur elliptique discret en dimension 1. | 所得到的线性系统是稳定的：其矩阵可逆，并对应于一维离散椭圆算子。

   En notant $e_i=u(x_i)-U_i$ l'erreur, on obtient un système discret de la forme | 记误差为 $e_i=u(x_i)-U_i$，则得到如下离散误差系统

   $$L_h e=\tau_h,$$

   où $\tau_h=\mathcal{O}(h^2)$ est l'erreur de troncature. | 其中 $\tau_h=\mathcal{O}(h^2)$ 是截断误差。  
   Par stabilité du problème discret, il existe une constante $C$ indépendante de $h$ telle que | 由离散问题的稳定性，存在与 $h$ 无关的常数 $C$，使得

   $$\|e\|_\infty \le C\|\tau_h\|_\infty,$$

   donc | 因此

   $$\|e\|_\infty=\mathcal{O}(h^2).$$

   Le schéma converge donc à l'ordre 2 en espace. | 所以该格式在空间上以 2 阶收敛。

## Exercice 3 | 练习 3

Considérons l'EDP suivante : | 考虑下面这个偏微分方程：

$$v_t+c v_x=v_{xx} \qquad \text{avec } c>0$$

Soient à présent les schémas suivants : | 现在考虑如下三个数值格式：

1.

$$\frac{v_j^{m+1}-v_j^m}{\Delta t}+c\frac{v_{j+1}^m-v_{j-1}^m}{2\Delta x}=\frac{v_{j-1}^m-2v_j^m+v_{j+1}^m}{\Delta x^2}$$

2.

$$\frac{v_j^{m+1}-v_j^m}{\Delta t}+c\frac{v_j^m-v_{j-1}^m}{\Delta x}=\frac{v_{j-1}^m-2v_j^m+v_{j+1}^m}{\Delta x^2}$$

3.

$$\frac{v_j^{m+1}-v_j^m}{\Delta t}+c\frac{v_j^{m+1}-v_{j-1}^{m+1}}{\Delta x}=\frac{v_{j-1}^{m+1}-2v_j^{m+1}+v_{j+1}^{m+1}}{\Delta x^2}$$

avec $v_j^m \approx v(m\Delta t,j\Delta x)$. | 其中 $v_j^m \approx v(m\Delta t,j\Delta x)$。

Pour chacun de ces schémas : | 对于每一个格式：

- Montrer comment on les obtient. | 说明它们是如何得到的。
- Étudier leur stabilité au sens de Von Neumann. | 用 Von Neumann 方法研究它们的稳定性。

**Éléments de réponse pour le schéma 1** | **格式 1 的答案要点**

On introduit un maillage régulier | 引入均匀网格

$$t_m=m\Delta t, \qquad x_j=j\Delta x, \qquad v_j^m \approx v(t_m,x_j).$$

On cherche à approcher les dérivées de l'équation | 我们要近似方程中的各个导数

$$v_t+c\,v_x=v_{xx}.$$

1. Approximation en temps de $v_t$ | 对 $v_t$ 的时间离散

   Par développement de Taylor en temps : | 对时间变量作 Taylor 展开：

   $$v_j^{m+1}=v(t_m+\Delta t,x_j)=v(t_m,x_j)+\Delta t\,v_t(t_m,x_j)+\frac{\Delta t^2}{2}v_{tt}(t_m,x_j)+\mathcal{O}(\Delta t^3).$$

   Donc | 因此

   $$\frac{v_j^{m+1}-v_j^m}{\Delta t}=v_t(t_m,x_j)+\mathcal{O}(\Delta t).$$

   On obtient ainsi une différence progressive d'ordre 1 en temps. | 于是得到时间上的一阶前向差分。

2. Approximation en espace de $v_x$ | 对 $v_x$ 的空间离散

   Par développement de Taylor en $x_j+\Delta x$ et $x_j-\Delta x$ : | 在 $x_j+\Delta x$ 和 $x_j-\Delta x$ 处作 Taylor 展开：

   $$v(t_m,x_j+\Delta x)=v(t_m,x_j)+\Delta x\,v_x(t_m,x_j)+\frac{\Delta x^2}{2}v_{xx}(t_m,x_j)+\frac{\Delta x^3}{6}v_{xxx}(t_m,x_j)+\mathcal{O}(\Delta x^4),$$

   $$v(t_m,x_j-\Delta x)=v(t_m,x_j)-\Delta x\,v_x(t_m,x_j)+\frac{\Delta x^2}{2}v_{xx}(t_m,x_j)-\frac{\Delta x^3}{6}v_{xxx}(t_m,x_j)+\mathcal{O}(\Delta x^4).$$

   En soustrayant ces deux relations, on obtient : | 两式相减可得：

   $$\frac{v_{j+1}^m-v_{j-1}^m}{2\Delta x}=v_x(t_m,x_j)+\mathcal{O}(\Delta x^2).$$

   Il s'agit donc d'une différence centrée d'ordre 2 en espace. | 因而这是一个空间上的二阶中心差分。

3. Approximation en espace de $v_{xx}$ | 对 $v_{xx}$ 的空间离散

   En additionnant les deux développements précédents : | 将上面两个展开式相加：

   $$v(t_m,x_j+\Delta x)+v(t_m,x_j-\Delta x)=2v(t_m,x_j)+\Delta x^2\,v_{xx}(t_m,x_j)+\mathcal{O}(\Delta x^4).$$

   D'où | 从而

   $$\frac{v_{j-1}^m-2v_j^m+v_{j+1}^m}{\Delta x^2}=v_{xx}(t_m,x_j)+\mathcal{O}(\Delta x^2).$$

   On obtient encore une différence centrée d'ordre 2 en espace. | 这同样给出一个空间上的二阶中心差分。

4. Obtention du schéma | 格式的推导

   En remplaçant ces approximations dans l'équation $v_t+c\,v_x=v_{xx}$, on trouve | 把这些近似代回方程 $v_t+c\,v_x=v_{xx}$，得到

   $$\frac{v_j^{m+1}-v_j^m}{\Delta t}+c\frac{v_{j+1}^m-v_{j-1}^m}{2\Delta x}=\frac{v_{j-1}^m-2v_j^m+v_{j+1}^m}{\Delta x^2}+\mathcal{O}(\Delta t)+\mathcal{O}(\Delta x^2).$$

   En négligeant les termes d'erreur, on obtient bien le premier schéma : | 忽略误差项后，便得到第一个格式：

   $$\frac{v_j^{m+1}-v_j^m}{\Delta t}+c\frac{v_{j+1}^m-v_{j-1}^m}{2\Delta x}=\frac{v_{j-1}^m-2v_j^m+v_{j+1}^m}{\Delta x^2}.$$

   Ce schéma est donc consistant d'ordre 1 en temps et d'ordre 2 en espace. | 因此该格式在时间上是一阶一致，在空间上是二阶一致。

5. Stabilité de Von Neumann du schéma 1 | 格式 1 的 Von Neumann 稳定性

   On pose | 记

   $$\lambda=\frac{c\Delta t}{\Delta x}, \qquad \mu=\frac{\Delta t}{\Delta x^2}.$$

   On cherche une solution sous la forme | 设 Fourier 模态解为

   $$v_j^m=G^m e^{ij\theta}, \qquad \theta \in \mathbb{R}.$$

   En remplaçant dans le schéma, on obtient | 代入格式可得

   $$G=1-\frac{\lambda}{2}(e^{i\theta}-e^{-i\theta})+\mu(e^{-i\theta}-2+e^{i\theta}),$$

   soit | 即

   $$G=1-i\lambda\sin\theta-4\mu\sin^2\left(\frac{\theta}{2}\right).$$

   Ainsi | 因而

   $$|G|^2=\left(1-4\mu\sin^2\left(\frac{\theta}{2}\right)\right)^2+\lambda^2\sin^2\theta.$$

   En posant $y=\sin^2(\theta/2) \in [0,1]$, on peut écrire | 令 $y=\sin^2(\theta/2) \in [0,1]$，则可写成

   $$|G|^2-1=4y\left[(\lambda^2-2\mu)+(4\mu^2-\lambda^2)y\right].$$

   La condition $|G| \le 1$ pour tout $\theta$ est équivalente à | 对任意 $\theta$ 都有 $|G| \le 1$ 的条件等价于

   $$\mu \le \frac{1}{2}, \qquad \lambda^2 \le 2\mu.$$

   Autrement dit, | 也就是说，

   $$\frac{\Delta t}{\Delta x^2} \le \frac{1}{2}, \qquad \left(\frac{c\Delta t}{\Delta x}\right)^2 \le 2\frac{\Delta t}{\Delta x^2}.$$

   Le schéma 1 est donc stable sous cette condition CFL. | 因此格式 1 在这个 CFL 条件下稳定。

**Éléments de réponse pour le schéma 2** | **格式 2 的答案要点**

1. Obtention du schéma | 格式的推导

   Comme $c>0$, on choisit une différence amont pour le terme de transport : | 由于 $c>0$，对输运项采用迎风差分：

   $$v_x(t_m,x_j)=\frac{v_j^m-v_{j-1}^m}{\Delta x}+\mathcal{O}(\Delta x).$$

   On garde la différence progressive en temps et la différence centrée d'ordre 2 pour $v_{xx}$ : | 时间上仍取前向差分，而 $v_{xx}$ 仍取二阶中心差分：

   $$v_t(t_m,x_j)=\frac{v_j^{m+1}-v_j^m}{\Delta t}+\mathcal{O}(\Delta t),$$

   $$v_{xx}(t_m,x_j)=\frac{v_{j-1}^m-2v_j^m+v_{j+1}^m}{\Delta x^2}+\mathcal{O}(\Delta x^2).$$

   En remplaçant dans l'équation, on obtient | 代回方程可得

   $$\frac{v_j^{m+1}-v_j^m}{\Delta t}+c\frac{v_j^m-v_{j-1}^m}{\Delta x}=\frac{v_{j-1}^m-2v_j^m+v_{j+1}^m}{\Delta x^2}+\mathcal{O}(\Delta t)+\mathcal{O}(\Delta x).$$

   En négligeant les termes d'erreur : | 忽略误差项后：

   $$\frac{v_j^{m+1}-v_j^m}{\Delta t}+c\frac{v_j^m-v_{j-1}^m}{\Delta x}=\frac{v_{j-1}^m-2v_j^m+v_{j+1}^m}{\Delta x^2}.$$

   Ce schéma est consistant d'ordre 1 en temps et d'ordre 1 en espace pour le terme convectif. | 这个格式在时间上是一阶一致，并且其对流项在空间上是一阶一致。

2. Stabilité de Von Neumann | Von Neumann 稳定性

   Avec le même ansatz $v_j^m=G^m e^{ij\theta}$, on obtient | 仍取 $v_j^m=G^m e^{ij\theta}$，则有

   $$G=1-\lambda(1-e^{-i\theta})+\mu(e^{-i\theta}-2+e^{i\theta}).$$

   On peut aussi écrire | 也可以写成

   $$G=(1-\lambda-2\mu)+(\lambda+\mu)e^{-i\theta}+\mu e^{i\theta}.$$

   Si | 如果

   $$\lambda+2\mu \le 1,$$

   alors les coefficients $(1-\lambda-2\mu)$, $(\lambda+\mu)$ et $\mu$ sont positifs et leur somme vaut 1. | 那么系数 $(1-\lambda-2\mu)$、$(\lambda+\mu)$ 和 $\mu$ 都是非负的，并且它们的和等于 1。  
   On en déduit immédiatement que $|G| \le 1$. | 于是立刻得到 $|G| \le 1$。

   Réciproquement, en prenant $\theta=\pi$, on a | 反过来，取 $\theta=\pi$，有

   $$G(\pi)=1-2\lambda-4\mu,$$

   et la condition $|G(\pi)| \le 1$ impose | 而条件 $|G(\pi)| \le 1$ 要求

   $$\lambda+2\mu \le 1.$$

   Le schéma 2 est donc stable si et seulement si | 因此格式 2 稳定当且仅当

   $$\lambda+2\mu \le 1,$$

   c'est-à-dire | 也就是

   $$\frac{c\Delta t}{\Delta x}+2\frac{\Delta t}{\Delta x^2} \le 1.$$

**Éléments de réponse pour le schéma 3** | **格式 3 的答案要点**

1. Obtention du schéma | 格式的推导

   Ici, on discrétise les termes d'espace au temps $t_{m+1}$, ce qui donne un schéma implicite. | 这里把空间项离散在时刻 $t_{m+1}$ 上，因此得到一个隐式格式。

   En temps, on peut écrire au point $(t_{m+1},x_j)$ : | 在时间上，于点 $(t_{m+1},x_j)$ 可写为：

   $$v_t(t_{m+1},x_j)=\frac{v_j^{m+1}-v_j^m}{\Delta t}+\mathcal{O}(\Delta t).$$

   Comme $c>0$, on utilise encore une différence amont en espace : | 由于 $c>0$，空间上仍采用迎风差分：

   $$v_x(t_{m+1},x_j)=\frac{v_j^{m+1}-v_{j-1}^{m+1}}{\Delta x}+\mathcal{O}(\Delta x).$$

   Pour la dérivée seconde : | 对于二阶导数：

   $$v_{xx}(t_{m+1},x_j)=\frac{v_{j-1}^{m+1}-2v_j^{m+1}+v_{j+1}^{m+1}}{\Delta x^2}+\mathcal{O}(\Delta x^2).$$

   En remplaçant dans l'équation, on obtient | 代回方程可得

   $$\frac{v_j^{m+1}-v_j^m}{\Delta t}+c\frac{v_j^{m+1}-v_{j-1}^{m+1}}{\Delta x}=\frac{v_{j-1}^{m+1}-2v_j^{m+1}+v_{j+1}^{m+1}}{\Delta x^2}+\mathcal{O}(\Delta t)+\mathcal{O}(\Delta x).$$

   En négligeant les termes d'erreur, on retrouve bien | 忽略误差项后，恰好得到

   $$\frac{v_j^{m+1}-v_j^m}{\Delta t}+c\frac{v_j^{m+1}-v_{j-1}^{m+1}}{\Delta x}=\frac{v_{j-1}^{m+1}-2v_j^{m+1}+v_{j+1}^{m+1}}{\Delta x^2}.$$

   Ce schéma est consistant d'ordre 1 en temps et d'ordre 1 en espace pour le terme de convection. | 该格式在时间上是一阶一致，并且其对流项在空间上是一阶一致。

2. Stabilité de Von Neumann | Von Neumann 稳定性

   En posant encore $v_j^m=G^m e^{ij\theta}$, on obtient | 再次令 $v_j^m=G^m e^{ij\theta}$，则得到

   $$G-1+\lambda G(1-e^{-i\theta})=\mu G(e^{-i\theta}-2+e^{i\theta}),$$

   donc | 因而

   $$G=\frac{1}{1+\lambda(1-e^{-i\theta})+4\mu\sin^2\left(\frac{\theta}{2}\right)}.$$

   Ainsi | 因此

   $$|G|^2=\frac{1}{\left(1+(\lambda+2\mu)(1-\cos\theta)\right)^2+\lambda^2\sin^2\theta}.$$

   Le dénominateur est toujours supérieur ou égal à 1 pour tout $\theta$, dès que $\lambda \ge 0$ et $\mu \ge 0$. | 只要 $\lambda \ge 0$ 且 $\mu \ge 0$，对任意 $\theta$ 分母都大于等于 1。  
   Par conséquent, | 因此，

   $$|G| \le 1 \qquad \text{pour tout } \theta.$$

   Le schéma 3 est donc inconditionnellement stable. | 所以格式 3 是无条件稳定的。
