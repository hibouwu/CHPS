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
