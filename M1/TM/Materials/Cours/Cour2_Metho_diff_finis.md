# Partie II : Méthode des différences finies | 第二部分：有限差分方法

## 0. Classification des EDP d'ordre 2 | 0. 二阶偏微分方程的分类

Considérons l'EDP d'ordre 2 suivante : | 考虑如下二阶偏微分方程：

$$\sum_{i,j} a_{ij}(x)\frac{\partial^2 \phi(x)}{\partial x_i \partial x_j} + \sum_i b_i(x)\frac{\partial \phi(x)}{\partial x_i} + c(x)\phi(x) = f(x)$$

où $\phi : \Omega \to \mathbb{R}$, $\Omega \subset \mathbb{R}^N$. | 其中 $\phi : \Omega \to \mathbb{R}$，$\Omega \subset \mathbb{R}^N$。

On suppose que $a_{ij} = a_{ji}$ (c'est le cas si $\phi$ est $C^2$). | 假设 $a_{ij}=a_{ji}$（若 $\phi$ 为 $C^2$，这是成立的）。

$A(x) = (a_{ij}(x))_{1 \le i,j \le N}$ matrice symétrique de coefficients d'ordre 2. | $A(x)=(a_{ij}(x))_{1 \le i,j \le N}$ 是二阶项系数组成的对称矩阵。  
$B(x) = (b_i(x))_{1 \le i \le N}$ valeur des coefficients d'ordre 1. | $B(x)=(b_i(x))_{1 \le i \le N}$ 是一阶项系数向量。  
$H\phi(x)$ : matrice hessienne de $\phi$. | $H\phi(x)$：$\phi$ 的 Hessian 矩阵。  
$\nabla \phi(x)$ : gradient de $\phi$. | $\nabla \phi(x)$：$\phi$ 的梯度。

Produit scalaire de Frobenius : $U:V = \sum_{i,j=1}^N U_{ij}V_{ij}$. | Frobenius 内积：$U:V = \sum_{i,j=1}^N U_{ij}V_{ij}$。

Notre EDP peut se mettre sous la forme : | 该偏微分方程可以写成：

$$A(x):H\phi(x) + B(x)\cdot \nabla \phi(x) + c(x)\phi(x) = f(x)$$

### Classification | 分类

Notre EDP est dite : | 该偏微分方程称为：

- elliptique en $x \in \Omega$ ssi les valeurs propres de $A(x)$ sont non nulles et de même signe | 在 $x \in \Omega$ 处若 $A(x)$ 的特征值都非零且同号，则称为椭圆型
- hyperbolique en $x \in \Omega$ ssi les valeurs propres de $A(x)$ sont non nulles et toutes de même signe sauf une | 在 $x \in \Omega$ 处若 $A(x)$ 的特征值都非零，且除一个外其余同号，则称为双曲型
- parabolique en $x \in \Omega$ ssi les valeurs propres de $A(x)$ sont non nulles et de même signe sauf une qui est nulle, avec vecteur propre $v_0(x)$ tel que $v_0(x)\cdot B(x) \neq 0$ | 在 $x \in \Omega$ 处若 $A(x)$ 的特征值除一个为零外其余同号，并且对应特征向量 $v_0(x)$ 满足 $v_0(x)\cdot B(x)\neq 0$，则称为抛物型

Si $v_0(x)\cdot B(x) = 0$, alors l'EDP est dégénérée en $x$. | 如果 $v_0(x)\cdot B(x)=0$，则该方程在 $x$ 处是退化的。

Exemples : | 例子：

1. $\Delta \phi(x) = f(x)$ | 1. $\Delta \phi(x)=f(x)$
2. $\dfrac{\partial^2 \phi}{\partial t^2}(t,x) - c^2\Delta \phi(t,x) = g(t,x)$ | 2. 波动方程
3. $\dfrac{\partial \phi}{\partial t}(t,x) - k\Delta \phi(t,x) = f(t,x)$ | 3. 热方程

Pour $\Delta \phi = f$, on a $A = I$, donc l'équation est elliptique. | 对于 $\Delta \phi=f$，有 $A=I$，所以方程是椭圆型。  
Pour l'équation des ondes, $A = \mathrm{diag}(1,-c^2,\dots,-c^2)$, donc elle est hyperbolique. | 对于波动方程，$A=\mathrm{diag}(1,-c^2,\dots,-c^2)$，因此它是双曲型。  
Pour l'équation de la chaleur, une valeur propre est nulle et les autres valent $-k$, donc elle est parabolique. | 对于热方程，一个特征值为零，其余特征值为 $-k$，因此它是抛物型。

## 1. Quelques exemples | 1. 一些例子

On s'intéresse dans ce qui suit à l'équation de la chaleur : | 接下来我们关注热方程：

$$\begin{cases} u_t(t,x) = u_{xx}(t,x), & t>0,\ x \in ]0,L[ \\ u(t,0)=u(t,L)=0, & t>0 \\ u(x,0)=f(x) \end{cases}$$

## 2. Approximations des dérivées successives | 2. 各阶导数的近似

Considérons une subdivision régulière de $[a,b]$. | 考虑区间 $[a,b]$ 的一个均匀剖分。

### Différence divisée progressive d'ordre 1 | 一阶前向差分

$$u'(x_i) = \frac{u(x_i+h)-u(x_i)}{h} + O(h)$$

Développement de Taylor à l'ordre 1 : | 一阶 Taylor 展开：

$$u(x_i+h) = u(x_i) + hu'(x_i) + O(h^2)$$

donc | 因此

$$u'(x_i) \simeq \frac{u(x_i+h)-u(x_i)}{h}$$

### Différence divisée régressive d'ordre 1 | 一阶后向差分

$$u'(x_i) = \frac{u(x_i)-u(x_i-h)}{h} + O(h)$$

donc | 因此

$$u'(x_i) \simeq \frac{u(x_i)-u(x_i-h)}{h}$$

### Différences centrées d'ordre 2 | 二阶中心差分

$$u'(x_i) = \frac{u(x_i+h)-u(x_i-h)}{2h} + O(h^2)$$

donc | 因此

$$u'(x_i) \simeq \frac{u(x_i+h)-u(x_i-h)}{2h}$$

Pour la dérivée seconde : | 对于二阶导数：

$$u''(x_i) \simeq \frac{u(x_i+h)-2u(x_i)+u(x_i-h)}{h^2}$$

## 3. Schéma explicite | 3. 显式格式

Appliquons ce qui précède à l'équation de la chaleur. | 将上述近似应用到热方程。

$$u_t(t,x) = \frac{u(t+\Delta t,x)-u(t,x)}{\Delta t} + O(\Delta t)$$

$$u_{xx}(t,x) = \frac{u(t,x+\Delta x)-2u(t,x)+u(t,x-\Delta x)}{\Delta x^2} + O(\Delta x^2)$$

On introduit la discrétisation : | 引入离散化：

$$t_i = i\Delta t,\qquad x_j = j\Delta x,\qquad u(t_i,x_j) \simeq U_{i,j}$$

avec | 其中

$$\Delta t = \frac{T}{N_t},\qquad \Delta x = \frac{L}{N_x}$$

Alors, au point $(t_i,x_j)$ : | 那么在点 $(t_i,x_j)$ 处：

$$\frac{U_{i+1,j}-U_{i,j}}{\Delta t} = \frac{U_{i,j+1}-2U_{i,j}+U_{i,j-1}}{\Delta x^2} + O(\Delta t) + O(\Delta x^2)$$

En posant $r=\dfrac{\Delta t}{\Delta x^2}$, on obtient le schéma explicite : | 令 $r=\dfrac{\Delta t}{\Delta x^2}$，得到显式格式：

$$U_{i+1,j} = rU_{i,j+1} + (1-2r)U_{i,j} + rU_{i,j-1}$$

Ce schéma est dit explicite car chaque pas de temps $i+1$ ne dépend que du pas précédent $i$. | 这个格式称为显式格式，因为每个新时间层 $i+1$ 只依赖前一层 $i$。

Remarque : | 注：

Par développement de Taylor : | 由 Taylor 展开：

$$f(x+h)=f(x)+hf'(x)+\frac{h^2}{2}f''(x)+O(h^3)$$

$$f(x-h)=f(x)-hf'(x)+\frac{h^2}{2}f''(x)+O(h^3)$$

En additionnant : | 两式相加：

$$f''(x) = \frac{f(x+h)-2f(x)+f(x-h)}{h^2} + O(h)$$

Une écriture plus précise donne la consistance usuelle d'ordre 2 en espace. | 更精确的写法会给出空间上的二阶一致性。

## 4. Schéma implicite | 4. 隐式格式

Pour les schémas explicites, il existe souvent une condition de stabilité liant les pas de discrétisation. | 对于显式格式，通常存在将离散步长联系起来的稳定性条件。  
Les schémas implicites peuvent lever cette contrainte. | 隐式格式可以缓解这类约束。

On approche alors à l'instant $t_{i+1}$ : | 这时在时刻 $t_{i+1}$ 上进行近似：

$$u_t(t+\Delta t,x) = \frac{u(t+\Delta t,x)-u(t,x)}{\Delta t} + O(\Delta t)$$

$$u_{xx}(t+\Delta t,x) = \frac{u(t+\Delta t,x+\Delta x)-2u(t+\Delta t,x)+u(t+\Delta t,x-\Delta x)}{\Delta x^2} + O(\Delta x^2)$$

On propose le schéma implicite : | 我们得到隐式格式：

$$\frac{U_{i+1,j}-U_{i,j}}{\Delta t} = \frac{U_{i+1,j+1}-2U_{i+1,j}+U_{i+1,j-1}}{\Delta x^2}$$

ou encore | 也就是

$$-rU_{i+1,j+1} + (1+2r)U_{i+1,j} - rU_{i+1,j-1} = U_{i,j}$$

## 5. Étude de la convergence de la méthode des différences finies | 5. 有限差分法的收敛性研究

Soient $U_h=(U(x_i))_i$ et $V_h=(V_i)_i$. | 设 $U_h=(U(x_i))_i$，$V_h=(V_i)_i$。  
Ce sont les vecteurs de la solution exacte et de la solution approchée aux points de discrétisation. | 它们分别是离散点上精确解和近似解组成的向量。

On note $E_h$ le vecteur erreur défini par $E_h = U_h - V_h$. | 记误差向量 $E_h = U_h - V_h$。

On dit qu'une méthode est convergente si $\lim_{h\to 0}\|E_h\| = 0$. | 若 $\lim_{h\to 0}\|E_h\|=0$，则称该方法收敛。  
On dit que la méthode est d'ordre $p$ si $\|E_h\| = O(h^p)$. | 若 $\|E_h\|=O(h^p)$，则称该方法是 $p$ 阶的。

On appelle erreur de troncature $T_h$ l'erreur obtenue quand on applique le schéma numérique à la solution exacte. | 将数值格式作用到精确解上得到的误差称为截断误差 $T_h$。  
Une méthode est dite consistante si $\|T_h\|\to 0$ lorsque $h\to 0$. | 若 $\|T_h\|\to 0$（当 $h\to 0$ 时），则称该方法是一致的。  
Une méthode est consistante d'ordre $q$ si $\|T_h\|=O(h^q)$. | 若 $\|T_h\|=O(h^q)$，则称其为 $q$ 阶一致。

Une méthode est dite stable si toute perturbation est contrôlée. | 如果任意扰动都能被控制，则称该方法稳定。  
S'il existe $K>0$ tel que $\|W_h - V_h\|\le K\|\varepsilon_h\|$, alors la méthode est stable. | 若存在 $K>0$ 使得 $\|W_h-V_h\|\le K\|\varepsilon_h\|$，则该方法稳定。

### Théorème de Lax | Lax 定理

Une méthode est convergente si et seulement si elle est consistante et stable. | 一个方法收敛，当且仅当它是一致且稳定的。

## 6. Stabilité au sens de Von Neumann | 6. Von Neumann 意义下的稳定性

Cadre d'application : EDP linéaire d'évolution. | 适用范围：线性演化型偏微分方程。

La méthode de Von Neumann consiste à décomposer la solution en modes de Fourier et à analyser l'évolution de chaque mode. | Von Neumann 方法的思想是把解分解成 Fourier 模态，并分析每个模态的演化。  
Pour que le schéma soit stable, aucun mode ne doit diverger. | 为了使数值格式稳定，任何模态都不应发散。

On introduit un mode de Fourier : | 引入 Fourier 模态：

$$\hat U_j^n = \hat U_n e^{ikj\Delta x - in\Delta t}$$

Le rapport | 比值

$$\frac{\hat U_j^{n+1}}{\hat U_j^n} = G(k)$$

est appelé facteur d'amplification. | 称为放大因子。

Si $|G(k)| \le 1$, alors le schéma est stable. | 如果 $|G(k)|\le 1$，则该格式稳定。

Exemple : considérons l'EDP $\dfrac{\partial u}{\partial t} + a\dfrac{\partial u}{\partial x}=0$. | 例子：考虑输运方程 $\dfrac{\partial u}{\partial t} + a\dfrac{\partial u}{\partial x}=0$。

On pose le schéma décentré en temps et en espace : | 取时间和空间上都偏置的格式：

$$\frac{U_j^{n+1}-U_j^n}{\Delta t} + a\frac{U_{j+1}^n-U_j^n}{\Delta x}=0$$

On obtient alors | 于是得到

$$G(k) = 1 - a\frac{\Delta t}{\Delta x}\left(e^{ik\Delta x}-1\right)$$

En posant $\lambda = a\dfrac{\Delta t}{\Delta x}$ et $\theta = k\Delta x$, on peut écrire : | 令 $\lambda = a\dfrac{\Delta t}{\Delta x}$，$\theta=k\Delta x$，则有：

$$G(k) = 1 + \lambda - \lambda e^{i\theta}$$

et | 并且

$$|G(k)|^2 = 1 + 2\lambda(1+\lambda)(1-\cos\theta)$$

La condition $|G(k)|\le 1$ conduit à $\lambda(1+\lambda)\le 0$, soit $-1\le \lambda \le 0$. | 条件 $|G(k)|\le 1$ 导出 $\lambda(1+\lambda)\le 0$，即 $-1\le \lambda \le 0$。

Ainsi : | 因此：

- si $a>0$, alors $\lambda>0$ et le schéma est instable | 如果 $a>0$，则 $\lambda>0$，格式不稳定
- si $a<0$, alors $0\le -\dfrac{a\Delta t}{\Delta x}\le 1$, soit $\dfrac{\Delta t}{\Delta x}\le -\dfrac{1}{a}$, et le schéma est stable | 如果 $a<0$，则 $0\le -\dfrac{a\Delta t}{\Delta x}\le 1$，也就是 $\dfrac{\Delta t}{\Delta x}\le -\dfrac{1}{a}$，格式稳定
