# CC1 考场速查（开卷随身版）

> 考场上只看这一份。推导看不懂时回《CC1期中开卷小抄表》。
> 用法：读题 → 找下面第 0 节的关键词 → 跳到对应节 → 照步骤抄。

---

## 0 关键词定位

| 题目里的法语 | 去哪节 |
| :--- | :--- |
| décrire le mouvement / Lagrange / Euler | §2.1 |
| le mouvement est-il plan ? | §2.1 第 1 步 |
| stationnaire / instationnaire | §2.3 |
| isochore / conservation du volume | §2.3 |
| irrotationnel / rotationnel | §2.3 |
| corps rigide | §2.3 |
| trajectoire / ligne de courant | §2.1 第 3 步 |
| déformations principales | §2.4 |
| contraintes planes | §4.2 |
| équation d'équilibre / divergence nulle | §5 |
| surface libre / condition aux limites | §6 |
| résultante / moment / torsion | §7 |
| Tresca / von Mises / coefficient de sécurité | §8 |

---

## 1 单位（QCM 固定一题）

| 单位 | 物理量 |
| :--- | :--- |
| 无量纲 | $\mathbb{F},\ J,\ \mathbb{C},\ \mathbb{E},\ \boldsymbol{\varepsilon},\ \boldsymbol{\omega},\ \nabla\vec{u},\ \nu,\ C_s$ |
| $\text{s}^{-1}$ | $\overrightarrow{\operatorname{grad}}\vec{V},\ \mathbb{D},\ \boldsymbol{\Omega},\ \vec{\omega}=\tfrac12\overrightarrow{\operatorname{rot}}\vec{V},\ \operatorname{div}\vec{V}$ |
| $\text{Pa}$ | $\boldsymbol{\sigma},\ \boldsymbol{\sigma}^D,\ \vec{T},\ \sigma_n,\ \tau,\ p,\ E,\ \lambda,\ \mu,\ K,\ \sigma_e,\ \sigma_{\text{eq}}$ |
| $\text{N}\cdot\text{m}^{-3}$ | $\overrightarrow{\operatorname{div}}\boldsymbol{\sigma},\ \vec{f}_v=\rho\vec{g},\ \overrightarrow{\operatorname{grad}}p,\ \rho\vec{\gamma}$ |
| $\text{N}$ | 合力 $\vec{R}$ |
| $\text{N}\cdot\text{m}$ | 合力矩 $\vec{M}_O$、扭矩 |
| $\text{Pa}\cdot\text{s}$ | 动力黏度 $\mu$ |

**量纲求 $\alpha$**：$[\alpha]=[V]/[x]$ 或 $[\alpha t]=1$，统一是 $\text{s}^{-1}$（若 $V=\alpha x^2$ 则是 $\text{m}^{-1}\text{s}^{-1}$）。

---

## 2 运动学大题

### 2.1 两条流水线

**模式 A：给欧拉速度 $\vec{V}(t,x)$**

1. 量纲求 $\alpha$；写“mouvement plan”两句：$V_3=0$，且 $\partial V_{1,2}/\partial x_3=0$。
2. 算 $\operatorname{div}\vec{V}$、$\overrightarrow{\operatorname{grad}}\vec{V}$、$\mathbb{D}$、$\boldsymbol{\Omega}$。
3. 解 ODE 得轨迹：$\mathrm{d}x_i/\mathrm{d}t=V_i$，代入 $x_i(0)=X_i$。
4. 消 $t$ 得轨迹方程（两年真题都是两式相乘）。
5. 求 $\mathbb{F}=\nabla_0\vec{\phi}$、$J=\det\mathbb{F}$、$\rho J=\rho_0$。
6. $\mathbb{C}=\mathbb{F}^T\mathbb{F}$，$\mathbb{E}=\tfrac12(\mathbb{C}-\mathbb{I})$。
7. 主应变/主方向（对角阵就直接读）。
8. HPP：$|\alpha|t\ll1$，一阶展开得 $\boldsymbol{\varepsilon}$。
9. 与 glissement simple 比较（§2.5）。

**模式 B：给拉格朗日映射 $\vec{x}=\vec{\phi}(t,\vec{X})$**

1. 对 $t$ 求偏导得 ${}^L\vec{V}$。
2. 反解 $X_i=x_i$ 的表达式，代回得 ${}^E\vec{V}$（**必须全换成小写**）。
3. 看 ${}^E\vec{V}$ 是否含 $t$ → stationnaire 与否。
4. 之后同模式 A 的 5–9 步。

### 2.2 通用伸缩运动（2024、2025 两套真题都套这一个）

$$x_1=a(t)X_1,\qquad x_2=\frac{X_2}{a(t)},\qquad x_3=X_3$$

$$\mathbb{F}=\operatorname{diag}\Big(a,\frac1a,1\Big),\quad J=1,\quad \mathbb{C}=\operatorname{diag}\Big(a^2,\frac1{a^2},1\Big)$$

$$\mathbb{E}=\frac12\operatorname{diag}\Big(a^2-1,\ \frac1{a^2}-1,\ 0\Big)$$

$${}^E\vec{V}=\Big(\frac{\dot a}{a}x_1,\ -\frac{\dot a}{a}x_2,\ 0\Big),\qquad \mathbb{D}=\frac{\dot a}{a}\operatorname{diag}(1,-1,0),\qquad \boldsymbol{\Omega}=\mathbb{0}$$

轨迹：$x_1x_2=X_1X_2$，双曲线。

| | 2024 | 2025 |
| :--- | :--- | :--- |
| $a(t)$ | $e^{\alpha t}$ | $1+\alpha t$ |
| $\dot a/a$ | $\alpha$ | $\dfrac{\alpha}{1+\alpha t}$ |
| 稳态？ | 是 | 否 |
| $E_{11}$ | $\tfrac12(e^{2\alpha t}-1)$ | $\alpha t+\tfrac12\alpha^2t^2$ |
| $\rho$ | $\rho_0$ | $\rho_0$ |

两套的小应变完全相同：

$$\boldsymbol{\varepsilon}=\begin{pmatrix}\alpha t&0&0\\0&-\alpha t&0\\0&0&0\end{pmatrix},\qquad \operatorname{Tr}\boldsymbol{\varepsilon}=0,\qquad \partial_t\boldsymbol{\varepsilon}\big|_{t=0}=\mathbb{D}(0)$$

### 2.3 四个判据

- **稳态**：看 ${}^E\vec{V}$ 是否显含 $t$。**不能看 ${}^L\vec{V}$。**
- **等体积**：$\operatorname{div}\vec{V}=0$ 或 $J=1$。
- **无旋**：$\boldsymbol{\Omega}=\mathbb{0}$，即 $\partial_{x_j}V_i=\partial_{x_i}V_j$。
- **刚体**：$\mathbb{D}=\mathbb{0}$。只要有一个 $\partial V_i/\partial x_i\neq0$ 就不是。

**始终等体积的运动**：平移、旋转、简单剪切。
**不等体积**：单轴拉伸/压缩（$J=\lambda$）、各向同性膨胀（$J=\lambda^3$）。

### 2.4 主应变

$\mathbb{E}$ 已对角 → 主方向就是 $\vec{e}_1,\vec{e}_2,\vec{e}_3$，主应变就是三个对角元。

有 $E_{12}\neq0$ 时：

$$E_{\text{I,II}}=\frac{E_{11}+E_{22}}2\pm\sqrt{\Big(\frac{E_{11}-E_{22}}2\Big)^2+E_{12}^2}$$

纯剪切 $\begin{pmatrix}0&\gamma/2\\\gamma/2&0\end{pmatrix}$ → 主应变 $\pm\gamma/2$，主方向 $\frac1{\sqrt2}(\vec{e}_1\pm\vec{e}_2)$。

### 2.5 与简单剪切的比较（压轴问答，背三条）

**同**：都平面；都等体积（$\det\mathbb{F}=1$，$\operatorname{Tr}\mathbb{D}=\operatorname{Tr}\boldsymbol{\varepsilon}=0$）；转过 45° 后本运动的纯伸缩等价于纯剪切。

**异**：本运动无旋（$\boldsymbol{\Omega}=\mathbb{0}$），主方向固定；简单剪切有旋（$\boldsymbol{\Omega}\neq\mathbb{0}$）= 纯剪切 + 刚体旋转。轨迹：双曲线 vs 平行直线。

### 2.6 基本运动结果表

| 运动 | $\mathbb{F}$ | $J$ | $\mathbb{E}$ | $\mathbb{D}$ / $\boldsymbol{\Omega}$ |
| :--- | :--- | :--- | :--- | :--- |
| 平移 | $\mathbb{I}$ | 1 | $\mathbb{0}$ | $0$ / $0$ |
| 旋转 | $\mathbb{R}$ | 1 | $\mathbb{0}$ | $0$ / $\neq0$ |
| 单轴拉伸 $\lambda$ | $\operatorname{diag}(\lambda,1,1)$ | $\lambda$ | $E_{11}=\tfrac12(\lambda^2-1)$ | $\dot\lambda/\lambda$ / $0$ |
| 简单剪切 $\gamma$ | $\begin{pmatrix}1&\gamma&0\\0&1&0\\0&0&1\end{pmatrix}$ | 1 | $\begin{pmatrix}0&\gamma/2&0\\\gamma/2&\gamma^2/2&0\\0&0&0\end{pmatrix}$ | $D_{12}=\dot\gamma/2$ / $\Omega_{12}=\dot\gamma/2$ |

**杆拉长 2 倍**：$\varepsilon_{11}=1$，$E_{11}=1.5$。

---

## 3 应力 QCM

**斜截面五个量**，顺序不能乱：

$$\vec{T}=\boldsymbol{\sigma}\cdot\vec{n}\ \to\ \sigma_n=\vec{T}\cdot\vec{n}\ \to\ \vec{T}_n=\sigma_n\vec{n}\ \to\ \vec{T}_t=\vec{T}-\vec{T}_n\ \to\ \tau=\|\vec{T}_t\|$$

- 先确认 $\|\vec{n}\|=1$，没归一就先除模。
- $\vec{n}=\vec{e}_j$ → $\vec{T}$ 就是第 $j$ 列，$\sigma_n=\sigma_{jj}$，$\tau=\sqrt{\sum_{i\neq j}\sigma_{ij}^2}$。

**判类型五步**：算迹（$=0$ → déviatorique）→ 元素是否常数（是 → divergence nulle）→ 有没有整行整列为 0（有且 $2\times2$ 子块行列式 $\neq0$ → biaxial）→ 迹和行列式同时为 0（→ cisaillement pur）→ 是不是 $c\mathbb{I}$（是 → sphérique）。

---

## 4 应力大题

### 4.1 补矩阵
对称：$\sigma_{ji}=\sigma_{ij}$，沿对角线镜像。

### 4.2 论证 contraintes planes（背这三句）
$\sigma_{zz}=\sigma_{rz}=\sigma_{\theta z}=0$；上下表面 $z=\pm e/2$ 是自由面（$\boldsymbol{\sigma}\cdot\vec{e}_z=\vec{0}$），故表面上严格为零；板很薄（$e\ll R$），连续性使其在整层厚度内近似为零。

---

## 5 局部平衡方程

**直角 $(x,y,z)$**

$$\partial_x\sigma_{xx}+\partial_y\sigma_{xy}+\partial_z\sigma_{xz}=0$$
$$\partial_x\sigma_{yx}+\partial_y\sigma_{yy}+\partial_z\sigma_{yz}=0$$
$$\partial_x\sigma_{zx}+\partial_y\sigma_{zy}+\partial_z\sigma_{zz}=0$$

**柱 $(r,\theta,z)$**

$$\frac{\partial\sigma_{rr}}{\partial r}+\frac1r\frac{\partial\sigma_{r\theta}}{\partial\theta}+\frac{\partial\sigma_{rz}}{\partial z}+\frac{\sigma_{rr}-\sigma_{\theta\theta}}{r}=0$$
$$\frac{\partial\sigma_{\theta r}}{\partial r}+\frac1r\frac{\partial\sigma_{\theta\theta}}{\partial\theta}+\frac{\partial\sigma_{\theta z}}{\partial z}+\frac{2\sigma_{r\theta}}{r}=0$$
$$\frac{\partial\sigma_{zr}}{\partial r}+\frac1r\frac{\partial\sigma_{z\theta}}{\partial\theta}+\frac{\partial\sigma_{zz}}{\partial z}+\frac{\sigma_{zr}}{r}=0$$

**轴对称 $\boldsymbol{\sigma}=\operatorname{diag}(\sigma_{rr}(r),\sigma_{\theta\theta}(r),0)$** 只剩径向：

$$\sigma_{\theta\theta}=\sigma_{rr}+r\frac{\mathrm{d}\sigma_{rr}}{\mathrm{d}r}$$

2025 真题：$\sigma_{rr}=6\alpha(r/R_e)^2+\beta(R_i/r)^2+\gamma$

$$\frac{\mathrm{d}\sigma_{rr}}{\mathrm{d}r}=\frac{12\alpha r}{R_e^2}-\frac{2\beta R_i^2}{r^3}\ \Longrightarrow\ \sigma_{\theta\theta}=18\alpha\Big(\frac r{R_e}\Big)^2-\beta\Big(\frac{R_i}r\Big)^2+\gamma$$

---

## 6 边界条件

外法向（从材料指向外部）：

| 面 | $\vec{n}$ |
| :--- | :--- |
| 外侧面 $r=R_e$ | $+\vec{e}_r$ |
| 内孔 $r=R_i$ | $-\vec{e}_r$（**注意负号**） |
| 上表面 | $+\vec{e}_z$ |
| 下表面 | $-\vec{e}_z$ |

- 自由面：$\boldsymbol{\sigma}\cdot\vec{n}=\vec{0}$
- 压强 $p$：$\boldsymbol{\sigma}\cdot\vec{n}=-p\vec{n}$
- 2025 求 $\beta,\gamma$：$\sigma_{rr}(R_e)=\sigma_{rr}(R_i)=0$，两式相减 → $\beta=6\alpha$，$\gamma=-6\alpha\big[1+(R_i/R_e)^2\big]$。
- 验算：边界上 $\sigma_{\theta\theta}=\pm12\alpha\big[1-(R_i/R_e)^2\big]$。

---

## 7 合力与合力矩

$$\vec{R}=\iint_S\boldsymbol{\sigma}\cdot\vec{n}\,\mathrm{d}S,\qquad \vec{M}_{O'}=\iint_S\overrightarrow{O'M}\wedge(\boldsymbol{\sigma}\cdot\vec{n})\,\mathrm{d}S$$

极坐标：$\mathrm{d}S=r\,\mathrm{d}r\,\mathrm{d}\theta$；圆域上 $\iint x\,\mathrm{d}S=\iint y\,\mathrm{d}S=0$。

**2024 扭转**（$\sigma_{xz}=-\alpha y,\ \sigma_{yz}=\alpha x$）：$\vec{R}=\vec{0}$，

$$\vec{M}=\iint\alpha r^2\,\mathrm{d}S\,\vec{e}_z=\frac{\pi\alpha R^4}{2}\vec{e}_z$$

即纯扭转，扭矩 $\mathcal{C}=\pi\alpha R^4/2$。

---

## 8 屈服准则

$$C_s=\frac{\sigma_e}{\max\sigma_{\text{eq}}}\ \ge1$$

**Tresca**：先写三个主应力（平面应力**必须补 $\sigma_3=0$**），

$$\sigma_{\text{eq}}^T=\max\big(|\sigma_1-\sigma_2|,\ |\sigma_2-\sigma_3|,\ |\sigma_3-\sigma_1|\big)$$

**von Mises**：

$$\sigma_{\text{eq}}^{VM}=\sqrt{\tfrac12\big[(\sigma_1-\sigma_2)^2+(\sigma_2-\sigma_3)^2+(\sigma_3-\sigma_1)^2\big]}$$

平面应力：$\sigma_{\text{eq}}^{VM}=\sqrt{\sigma_{11}^2+\sigma_{22}^2-\sigma_{11}\sigma_{22}+3\sigma_{12}^2}$

| | Tresca | von Mises |
| :--- | :--- | :--- |
| 纯剪切 $\tau$ | $2|\tau|$，$\tau_e=0.5\sigma_e$ | $\sqrt3|\tau|$，$\tau_e=0.577\sigma_e$ |
| 静水压 | 0 | 0 |

**2024 扭转**：主应力 $(|\alpha|r,0,-|\alpha|r)$。

$$\sigma_{\text{eq}}^T=2|\alpha|r\Rightarrow|\alpha_{\max}|=\frac{\sigma_e}{2R};\qquad \sigma_{\text{eq}}^{VM}=\sqrt3|\alpha|r\Rightarrow|\alpha_{\max}|=\frac{\sigma_e}{\sqrt3R}$$

最危险点在外表面 $r=R$。

**2025 圆环**：边界上 $\sigma_{rr}=\sigma_{zz}=0$，故 $\sigma_{\text{eq}}\approx|\sigma_{\theta\theta}|$。

---

## 9 易错点（考前扫一遍）

1. 稳态只看欧拉速度。
2. 平面应力求 Tresca 漏掉 $\sigma_3=0$。
3. 内孔外法向是 $-\vec{e}_r$。
4. ${}^E\vec{V}$ 里残留大写 $X$ 就是错的。
5. 简单剪切有旋，别写成无旋。
6. 体积守恒的运动只有平移、旋转、简单剪切。
7. $\mathbb{C}$ 要写成 $\mathbb{F}^T\mathbb{F}$，不是 $\mathbb{F}\mathbb{F}^T$。
8. 应力张量对称，只有 6 个独立分量。

---

## 10 法语答题句

> Le mouvement est plan dans le plan $(\vec{e}_1,\vec{e}_2)$ car $V_3=0$ et $V_1,V_2$ ne dépendent pas de $x_3$.

> Par analyse dimensionnelle, $[\alpha]=\text{s}^{-1}$.

> Comme $\operatorname{div}\vec{V}=\operatorname{Tr}\mathbb{D}=0$, le mouvement est isochore (conserve le volume).

> Comme $\boldsymbol{\Omega}=\mathbb{0}$, le mouvement est irrotationnel.

> Le tenseur $\mathbb{E}$ étant diagonal dans la base $(\vec{e}_1,\vec{e}_2,\vec{e}_3)$, les directions principales sont $\vec{e}_1,\vec{e}_2,\vec{e}_3$ et les déformations principales sont $E_1,E_2,E_3=0$.

> Il s'agit d'un état de contraintes planes car $\sigma_{rz}=\sigma_{\theta z}=\sigma_{zz}=0$, les faces $z=\pm e/2$ étant libres.

> L'équation d'équilibre locale $\overrightarrow{\operatorname{div}}\boldsymbol{\sigma}=\vec{0}$ est vérifiée pour tout $\alpha$.

> La surface latérale est libre : $\boldsymbol{\sigma}\cdot\vec{n}=\vec{0}$.

---

## 附录 若考到（CC1 不确定，抄着备用）

**柱坐标应变**

$$\varepsilon_{rr}=\partial_r u_r,\quad \varepsilon_{\theta\theta}=\frac1r\partial_\theta u_\theta+\frac{u_r}r,\quad \varepsilon_{zz}=\partial_z u_z$$
$$\varepsilon_{r\theta}=\frac12\Big(\frac1r\partial_\theta u_r+\partial_r u_\theta-\frac{u_\theta}r\Big)$$

散度：$\operatorname{div}\vec{u}=\frac1r\partial_r(ru_r)+\frac1r\partial_\theta u_\theta+\partial_z u_z$

**球对称**：$\varepsilon_{rr}=\mathrm{d}u/\mathrm{d}r$，$\varepsilon_{\theta\theta}=\varepsilon_{\varphi\varphi}=u/r$，平衡 $\frac{\mathrm{d}\sigma_{rr}}{\mathrm{d}r}+\frac{2(\sigma_{rr}-\sigma_{\theta\theta})}{r}=0$

**应变积分求位移**：验相容性 → 积分三个正应变各加任意函数 → 代入三个剪切方程定函数 → **加刚体位移 $\vec{u}=\vec{\lambda}+\vec{\Omega}\wedge\vec{x}$** → 用边界条件定 6 个常数。

**层流四式**

| | $u(y)$ | 流量 |
| :--- | :--- | :--- |
| Couette | $Uy/h$ | $Uh/2$ |
| 平板 Poiseuille | $\frac{G}{2\mu}(h^2-y^2)$ | $\frac{2Gh^3}{3\mu}$ |
| 圆管 | $\frac{\Delta P}{4\mu L}(R^2-r^2)$ | $\frac{\pi R^4\Delta P}{8\mu L}$ |
| 斜面膜 | $\frac{\rho g\sin\alpha}{2\mu}y(2h-y)$ | $\frac{\rho g\sin\alpha\,h^3}{3\mu}$ |

自由面条件：$p=p_0$ 且 $\sigma_{xy}=0$。
