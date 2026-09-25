# 练习 1 -- 刚体旋转运动与变形

我们考虑欧几里得空间 $E$，其正交基为 $(\vec{e}_1, \vec{e}_2, \vec{e}_3)$。 以下关系定义了一个**绕轴 $(O, \vec{e}_3)$ 以角速度 $\omega$ 旋转的刚体**（见图 1.1）的运动。 $\vec{X}$ 和 $\vec{x}$ 分别表示质点在初始时刻 ($t=0$) 与当前时刻的空间位置：

$$
\begin{cases}
x_1 = X_1\cos\theta - X_2\sin\theta \\[4pt]
x_2 = X_1\sin\theta + X_2\cos\theta \\[4pt]
x_3 = X_3
\end{cases}
\quad (1.1)
$$

其中 $\theta = \omega t$ 为时刻 $t$ 的转角。

---

## 问题 1.1：给出该运动的拉格朗日描述与欧拉描述（参照 TD1）。

#### 解答：

此运动由轨迹方程定义，即质点的当前坐标 $(x_1, x_2, x_3)$ 由其初始坐标 $(X_1, X_2, X_3)$ 给出。 因此，方程 (1.1) 直接就是**拉格朗日描述**：

$$
\begin{cases}
x_1 = X_1\cos(\omega t) - X_2\sin(\omega t) & (∗1.1) \\[4pt]
x_2 = X_1\sin(\omega t) + X_2\cos(\omega t) & (∗1.2) \\[4pt]
x_3 = X_3 & (∗1.3)
\end{cases}
$$

要得到**欧拉描述**，我们需要：

- 对轨迹方程关于时间求导，以得到拉格朗日速度场；

- 将结果用当前坐标 $x_i$ 表示，从而得到欧拉速度场。

---

求导可得： 

$$
\begin{aligned}
\dot{x}_1 &= \omega[-X_1\sin(\omega t) - X_2\cos(\omega t)] 
\quad \text{由 (∗1.2) 可得 } \dot{x}_1 = -\omega x_2 \\[4pt]
\dot{x}_2 &= \omega[X_1\cos(\omega t) - X_2\sin(\omega t)]
\quad \text{由 (∗1.1) 可得 } \dot{x}_2 = \omega x_1 \\[4pt]
\dot{x}_3 &= 0
\end{aligned}
$$

因此对应的欧拉速度分量为： 

$$
\boxed{
\begin{cases}
V_1 = -\omega x_2 \\[4pt]
V_2 = \omega x_1 \\[4pt]
V_3 = 0
\end{cases}
\quad (∗1.4)
}
$$

这表明该运动为绕 $\vec{e}_3$ 轴的纯旋转。

---

## 问题 1.2：计算变换梯度张量 $F$ 与 Green-Lagrange 变形张量 $E$，并对结果进行评论。

#### 解答：

根据轨迹方程 $\varphi$ 对初始坐标求导，可以得到**变换梯度张量**： 

$$
F = \nabla_{\!X}\varphi = \dfrac{\partial \overrightarrow{OM}}{\partial \overrightarrow{OM_0}} =
\begin{pmatrix}
\cos\theta & -\sin\theta & 0\\[4pt]
\sin\theta & \cos\theta & 0\\[4pt]
0 & 0 & 1
\end{pmatrix}
\quad (∗1.5)
$$

---

Green--Lagrange 变形张量由 Green--Cauchy 右延伸张量 

$$
C = F^T F
$$

 定义为：

$$
E = \dfrac{1}{2}(C - I)
= \dfrac{1}{2}(F^T F - I)
\quad (∗1.6)
$$

计算：

$$
C = F^T F
=
\begin{pmatrix}
\cos^2\theta + \sin^2\theta & -\cos\theta\sin\theta + \sin\theta\cos\theta & 0\\[4pt]
-\cos\theta\sin\theta + \sin\theta\cos\theta & \sin^2\theta + \cos^2\theta & 0\\[4pt]
0 & 0 & 1
\end{pmatrix}
=
\begin{pmatrix}
1 & 0 & 0\\[4pt]
0 & 1 & 0\\[4pt]
0 & 0 & 1
\end{pmatrix}
\quad (∗1.7)
$$

因此：

$$
E = \dfrac{1}{2}(C - I)
= \dfrac{1}{2}(I - I)
= \mathbf{O}
\quad (∗1.8)
$$

---

**结论：** Green--Lagrange 变形张量为零，即变形测度为零。 说明该运动中介质未产生任何变形，这是**纯刚体运动（pure rigid-body motion）**。

事实上，这一点也可以直接从 $F$ 的形式看出------它本身就是一个**旋转矩阵**，代表刚体转动而非变形。

## 问题 1.3：在小扰动假设下，给出线性化变形张量 $\boldsymbol{\varepsilon}$。

#### 解答：

**回顾：** 在线性小变形假设（*Hypothèse des Petites Perturbations, HPP*）下，线性化变形张量 $\boldsymbol{\varepsilon}$ 定义为：

$$
\boldsymbol{\varepsilon} = \dfrac{1}{2} \left[ \nabla \vec{u} + (\nabla \vec{u})^T \right]
\quad (∗1.9)
$$

其中，位移场 $\vec{u}$ 为拉格朗日描述下的量，定义为：

$$
\vec{u}(t) = \overrightarrow{OM}(t) - \overrightarrow{OM_0}
\quad (∗1.10)
$$

---

根据已知轨迹方程，可写出位移场：

$$
\vec{u}(t) = 
\overrightarrow{OM}(t) - \overrightarrow{OM_0}
=
\begin{pmatrix}
X_1\cos\theta - X_2\sin\theta - X_1 \\[4pt]
X_1\sin\theta + X_2\cos\theta - X_2 \\[4pt]
X_3 - X_3
\end{pmatrix}
=
\begin{pmatrix}
X_1(\cos\theta - 1) - X_2\sin\theta \\[4pt]
X_1\sin\theta + X_2(\cos\theta - 1) \\[4pt]
0
\end{pmatrix}
\quad (∗1.11)
$$

---

由此可求出其梯度及转置：

$$
\nabla \vec{u}
= \dfrac{\partial \vec{u}}{\partial \overrightarrow{OM_0}}
=
\begin{pmatrix}
\cos\theta - 1 & -\sin\theta & 0\\[4pt]
\sin\theta & \cos\theta - 1 & 0\\[4pt]
0 & 0 & 0
\end{pmatrix}
\Rightarrow
(\nabla \vec{u})^T
=
\begin{pmatrix}
\cos\theta - 1 & \sin\theta & 0\\[4pt]
-\sin\theta & \cos\theta - 1 & 0\\[4pt]
0 & 0 & 0
\end{pmatrix}
\quad (∗1.12)
$$

---

于是线性化变形张量为：

$$
\boldsymbol{\varepsilon}
= \dfrac{1}{2}\left[\nabla \vec{u} + (\nabla \vec{u})^T\right]
=
\begin{pmatrix}
\cos\theta - 1 & 0 & 0\\[4pt]
0 & \cos\theta - 1 & 0\\[4pt]
0 & 0 & 0
\end{pmatrix}
\quad (∗1.13)
$$

---

## 问题 1.4：应满足怎样的条件才能使小扰动假设（HPP）有效？

#### 解答：

为了使小扰动假设成立，必须满足：

$$
\|\nabla \vec{u}\| \ll 1
\quad \Leftrightarrow \quad
\max_{i,j} |u_{i,j}| \ll 1
\quad \Leftrightarrow \quad
\max(|\cos\theta - 1|, |\sin\theta|) \ll 1
\quad (∗1.14)
$$

---

考察函数 $\cos\theta - 1$ 与 $\sin\theta$ 及其绝对值在区间 $[-\pi, \pi]$ 上的变化：

$$
\begin{array}{cc}
\text{左图：} & 
\text{右图：}\\[6pt]
f(\theta) = \cos\theta - 1,\; \sin\theta
&
f(\theta) = |\cos\theta - 1|,\; |\sin\theta|
\end{array}
$$

（此处原文对应图像：显示 $\sin$ 与 $\cos - 1$ 的曲线以及其绝对值在 $[-\pi, \pi]$ 区间的变化趋势。）

---

可以区分以下情况：

#### 情况 1：$\theta \in [-\pi/2, \pi/2]$

若 $|\sin\theta| \ll 1$，则： 

$$
\begin{cases}
\sin\theta \ll 1, & \text{若 } \theta \in [0, \pi/2]\\[4pt]
-\sin\theta \ll 1 \Rightarrow \sin(-\theta) \ll 1, & \text{若 } \theta \in [-\pi/2, 0]
\end{cases}
\quad (∗1.15)
$$

由于 $\arcsin$ 在 $[-\pi, \pi]$ 上为单调递增函数，因此：

$$
\begin{cases}
\theta \ll \arcsin(1) = \pi/2, & \text{若 } \theta \in [0, \pi/2]\\[4pt]
-\theta \ll \arcsin(1) = \pi/2, & \text{若 } \theta \in [-\pi/2, 0]
\end{cases}
\quad (∗1.16)
$$

综合可得： 

$$
\theta \in [-\pi/2, \pi/2] \Rightarrow |\theta| \ll \pi/2
\quad (∗1.17)
$$

---

#### 情况 2：$\theta \in [-\pi, -\pi/2) \cup (\pi/2, \pi]$

在此区间，$\cos\theta - 1 < 0$，因此： 

$$
|\cos\theta - 1| \ll 1 \Leftrightarrow 1 - \cos\theta \ll 1 \Leftrightarrow \cos\theta \gg 0
\quad (∗1.18)
$$

 由于 $\arccos$ 在 $[-\pi, \pi]$ 上为单调递减函数，可得： 

$$
|\theta| \ll \arccos(0) = \dfrac{\pi}{2}
\quad (∗1.19)
$$

---

**最终结论：** 

$$
\boxed{|\,\theta\,| \ll \dfrac{\pi}{2}}
$$

 这就是小扰动假设成立的条件。

---

**备注：**

- 注意，这里的"无变形"在几何上是严格成立的（$E = 0$），但线性化近似 $\boldsymbol{\varepsilon}$ 中仍保留了旋转的分量，使其在数学上呈现微小的"伪变形"。

- 因此，即使真实变形为零，线性化形式在 $\theta$ 不够小时仍可能产生非零项。

- 下图给出了 $\arcsin(x)$ 与 $\arccos(x)$ 的曲线，表明两函数在 $[-1,1]$ 上的单调性：

$$
\text{左图： } y = \arcsin(x) \text{ （单调递增）} \quad
\text{右图： } y = \arccos(x) \text{ （单调递减）}
$$

# 练习 2 -- 简单剪切运动

设 $(O, \vec{e}_1, \vec{e}_2, \vec{e}_3)$ 为一正交坐标系，其中点 $O$ 固定。 一个连续介质的运动由如下速度场定义：

$$
\vec{V}(M) = \alpha\,\vec{e}_1\,(\vec{e}_2 \cdot \overrightarrow{OM})
$$

 其中 $\alpha$ 为一给定的正常数。

---

## 问题 2.1：求该运动的轨迹与流线。

#### 解答：

**回顾：**

- **轨迹**：由方程 $x_i(t) = f_i(X_i, t)$ 定义，这些曲线连接了同一质点从初始时刻 $t_0$ 到任意时刻 $t$ 所经过的所有位置。

- **流线**：在某固定时刻 $t$，为与欧拉速度场 $\vec{V}(M,t)$ 相切（或共线）的曲线。 它是"瞬时图像"，但可随时间演化。 流线由条件 $d\vec{M} \wedge \vec{V}(M,t) = \vec{0}$ 给出， 即 $d\vec{M}$ 与速度场共线。该条件涉及空间积分（非时间积分）。

- 若运动为**非定常（instationnaire）**，轨迹与流线不同；若为**定常（stationnaire）**，两者重合。

- 但注意，轨迹与流线重合并不一定意味着运动定常，例如振动平移的情况。

---

在本题中，速度场与时间无关，因此运动为**定常**。 于是轨迹与流线重合，我们只需计算轨迹方程 $\vec{M}(t) = \varphi(\vec{M}_0, t)$。

由速度场可得： 

$$
E\vec{V}(M,t) =
\begin{pmatrix}
\dot{x}_1 \\[4pt]
\dot{x}_2 \\[4pt]
\dot{x}_3
\end{pmatrix}
=
\begin{pmatrix}
\alpha x_2 \\[4pt]
0 \\[4pt]
0
\end{pmatrix}
\Rightarrow
\begin{cases}
\dfrac{dx_1}{dt} = \alpha x_2 \\[4pt]
\dfrac{dx_2}{dt} = 0 \\[4pt]
\dfrac{dx_3}{dt} = 0
\end{cases}
$$

初始条件： 

$$
\begin{cases}
x_1(0) = X_1 \\[4pt]
x_2(0) = X_2 \\[4pt]
x_3(0) = X_3
\end{cases}
$$

解得： 

$$
\begin{cases}
x_1(t) = \displaystyle\int_0^t \alpha x_2\,dt + X_1 = \alpha X_2 t + X_1 \\[6pt]
x_2(t) = X_2 \\[4pt]
x_3(t) = X_3
\end{cases}
$$

即： 

$$
\boxed{
x_1(t) = X_1 + \alpha X_2 t, \quad
x_2(t) = X_2, \quad
x_3(t) = X_3
}
$$

---

## 问题 2.2：在时刻 $t=0$，考虑边长为 $\eta$ 的正方形 $OA_0B_0C_0$，其中

$$
\overrightarrow{OA_0} = \eta \vec{e}_1, \qquad
\overrightarrow{OB_0} = \eta \vec{e}_2
$$

 求其在时刻 $t$ 的变换后图形。

#### 解答：

回顾： 变换映射 $\vec{\varphi}$ 将参考构型 $\Omega_0$ 的点 $\overrightarrow{OM_0}$ 映射到当前构型 $\Omega(t)$ 中的 $\overrightarrow{OM}(t)$：

$$
\overrightarrow{OM}(t) = \vec{\varphi}(\overrightarrow{OM_0}, t)
$$

将其应用于定义正方形的点：

$$
\overrightarrow{OA_0} =
\begin{pmatrix}\eta\\0\\0\end{pmatrix},\quad
\overrightarrow{OB_0} =
\begin{pmatrix}0\\\eta\\0\end{pmatrix},\quad
\overrightarrow{OC_0} = 
\begin{pmatrix}\eta\\\eta\\0\end{pmatrix}
$$

利用 $\varphi$ 的定义： 

$$
x_1 = X_1 + \alpha X_2 t, \quad x_2 = X_2, \quad x_3 = X_3
$$

计算各点变换：

$$
\begin{aligned}
\overrightarrow{OA} &= \eta
\begin{pmatrix}1\\0\\0\end{pmatrix},\\[4pt]
\overrightarrow{OB} &= \eta
\begin{pmatrix}\alpha t\\1\\0\end{pmatrix},\\[4pt]
\overrightarrow{OC} &= \eta
\begin{pmatrix}\alpha t + 1\\1\\0\end{pmatrix}.
\end{aligned}
$$

即该方形被剪切成平行四边形。

---

## 问题 2.3：若在 $t=0$ 时取一个立方体，其一面为上述方形 $OA_0B_0C_0$，求其在时刻 $t$ 的变换。

#### 解答：

在初始状态中： 

$$
\overrightarrow{OD_0} = \eta
\begin{pmatrix}0\\0\\1\end{pmatrix},\quad
\overrightarrow{OE_0} = \eta
\begin{pmatrix}1\\0\\1\end{pmatrix},\quad
\overrightarrow{OF_0} = \eta
\begin{pmatrix}0\\1\\1\end{pmatrix},\quad
\overrightarrow{OG_0} = \eta
\begin{pmatrix}1\\1\\1\end{pmatrix}.
$$

应用变换：

$$
\begin{aligned}
\overrightarrow{OD} &= \eta
\begin{pmatrix}0\\0\\1\end{pmatrix},\\[4pt]
\overrightarrow{OE} &= \eta
\begin{pmatrix}1\\0\\1\end{pmatrix},\\[4pt]
\overrightarrow{OF} &= \eta
\begin{pmatrix}\alpha t\\1\\1\end{pmatrix},\\[4pt]
\overrightarrow{OG} &= \eta
\begin{pmatrix}\alpha t + 1\\1\\1\end{pmatrix}.
\end{aligned}
$$

因此整个立方体被沿 $\vec{e}_1$ 方向剪切。

---

## 问题 2.4：回顾变换梯度张量的定义并给出其表达式。

#### 解答：

变换梯度张量（或称变换张量）$F$ 定义为： 

$$
F = \dfrac{\partial \overrightarrow{OM}}{\partial \overrightarrow{OM_0}} = \nabla_X \vec{\varphi}
$$

它描述了从参考构型 $\Omega_0$ 到当前构型 $\Omega(t)$ 的映射。 对本题而言：

$$
F =
\begin{pmatrix}
\dfrac{\partial x_1}{\partial X_1} & \dfrac{\partial x_1}{\partial X_2} & \dfrac{\partial x_1}{\partial X_3}\\[4pt]
\dfrac{\partial x_2}{\partial X_1} & \dfrac{\partial x_2}{\partial X_2} & \dfrac{\partial x_2}{\partial X_3}\\[4pt]
\dfrac{\partial x_3}{\partial X_1} & \dfrac{\partial x_3}{\partial X_2} & \dfrac{\partial x_3}{\partial X_3}
\end{pmatrix}
=
\begin{pmatrix}
1 & \alpha t & 0\\[4pt]
0 & 1 & 0\\[4pt]
0 & 0 & 1
\end{pmatrix}
\quad (∗2.1)
$$

---

## 问题 2.5：计算 Green--Lagrange 变形张量 $E$，并求其主应变及主方向。

#### 解答：

Green--Lagrange 变形张量定义为： 

$$
E = \dfrac{1}{2}(F^T F - I)
$$

 其中 $C = F^T F$ 为右 Cauchy--Green 张量。

计算： 

$$
C = F^T F =
\begin{pmatrix}
1 & 0 & 0\\[4pt]
\alpha t & 1 & 0\\[4pt]
0 & 0 & 1
\end{pmatrix}
\begin{pmatrix}
1 & \alpha t & 0\\[4pt]
0 & 1 & 0\\[4pt]
0 & 0 & 1
\end{pmatrix}
=
\begin{pmatrix}
1 & \alpha t & 0\\[4pt]
\alpha t & (\alpha t)^2 + 1 & 0\\[4pt]
0 & 0 & 1
\end{pmatrix}
$$

于是： 

$$
E = \dfrac{1}{2}(C - I) = \dfrac{\alpha t}{2}
\begin{pmatrix}
0 & 1 & 0\\[4pt]
1 & \alpha t & 0\\[4pt]
0 & 0 & 0
\end{pmatrix}
$$

---

为了得到主应变与主方向，求解特征方程： 

$$
\det(E - \lambda I) = 0
$$

即： 

$$
\det
\begin{pmatrix}
-2\lambda & \alpha t & 0\\[4pt]
\alpha t & (\alpha t)^2 - 2\lambda & 0\\[4pt]
0 & 0 & -2\lambda
\end{pmatrix} = 0
$$

可得一特征值 $\lambda_1 = 0$，其余两个为： 

$$
\lambda_{2,3} = \dfrac{\alpha t}{4}\left[\alpha t \mp \sqrt{(\alpha t)^2 + 4}\right]
$$

主方向向量为：

$$
\vec{N}_1 = \vec{e}_3,\quad
\vec{N}_2 \propto
\begin{pmatrix}
2\\[2pt]
\alpha t + \sqrt{(\alpha t)^2 + 4}\\[2pt]
0
\end{pmatrix},
\quad
\vec{N}_3 = \vec{N}_1 \wedge \vec{N}_2 \propto
\begin{pmatrix}
-\alpha t - \sqrt{(\alpha t)^2 + 4}\\[2pt]
2\\[2pt]
0
\end{pmatrix}
$$

---

## 问题 2.6：求沿方向 $\tau$（角度 $\phi = (\vec{e}_1, \tau)$）的小向量 $d\vec{M}_0$ 的长度平方增量。

#### 解答：

定义： 

$$
\Lambda(d\vec{M}_0) = \|d\vec{M}\|^2 - \|d\vec{M}_0\|^2
$$

代入 $d\vec{M} = F d\vec{M}_0$，得： 

$$
\Lambda(d\vec{M}_0) = (d\vec{M}_0)^T (F^T F - I) d\vec{M}_0 = (d\vec{M}_0)^T (2E) d\vec{M}_0
$$

设 $d\vec{M}_0 = dl_0\,\tau$，其中 

$$
\tau =
\begin{pmatrix}
\cos\phi\\[2pt]
\sin\phi\\[2pt]
0
\end{pmatrix}
$$

则： 

$$
\Lambda(d\vec{M}_0) = dl_0^2 \alpha t (\sin 2\phi + \alpha t \sin^2\phi)
$$

---

## 问题 2.7：求边矢量为 $d\vec{a}_0, d\vec{b}_0, d\vec{c}_0$ 的微小立方体在变形前后体积的变化。

#### 解答：

体积定义为三重积： 

$$
dV = \det(d\vec{a}, d\vec{b}, d\vec{c}) = \det(F)\det(d\vec{a}_0, d\vec{b}_0, d\vec{c}_0)
$$

因此： 

$$
\dfrac{dV}{dV_0} = \det F = J
\Rightarrow
\dfrac{dV - dV_0}{dV_0} = J - 1
$$

计算： 

$$
J = \det F =
\begin{vmatrix}
1 & \alpha t & 0\\
0 & 1 & 0\\
0 & 0 & 1
\end{vmatrix} = 1
$$

因此： 

$$
\boxed{\text{该变换为等体变换（isochore）}}
$$

---

## 问题 2.8：若速度场为

$$
\vec{V} = \alpha \vec{e}_1(\vec{e}_2 \cdot \overrightarrow{OM}) - \alpha \vec{e}_2(\vec{e}_1 \cdot \overrightarrow{OM})
$$

 描述的是哪种运动？

#### 解答：

这等价于 TD1 中研究的旋涡运动，取 $\omega = \alpha$ 且 $a = 0$。 因此：

- 该运动是**定常的（stationnaire）**；

- **纯旋转的（rotationnel）**；

- **不可压的（incompressible）**。

因此，该运动为**以原点为中心的静态圆周旋转（稳态涡旋）**。

# 练习 3 -- 通过应变计测量变形

# 题目背景说明

**应变计法（Extensométrie）** 是一种通过在固体表面某点测量来确定变形张量各分量的技术。 该测量通常使用电阻丝应变计（其电阻与长度成比例）。 之后，通过材料本构关系可以从测得的应变得到应力分量。

现有三个应变计（记作 I、II、III）构成一组"应变花"（rosette），围绕固体表面上一点 $O$ 布置。 它们分别测量沿三条相隔 $120^\circ$ 方向上的线性应变（即单位伸长率）：

$$
\alpha = 0^\circ, \quad \beta = 120^\circ, \quad \gamma = 120^\circ.
$$

测得的数据如下： 

$$
\varepsilon_I = 0.5 \times 10^{-4}, \quad
\varepsilon_{II} = 2 \times 10^{-4}, \quad
\varepsilon_{III} = 2 \times 10^{-4}.
$$

（图 3.1 示意：(a) 单个应变计；(b) 120° rosette 三向布置）

---

## 问题 3.1：计算点 $O$ 处的线性化变形张量分量，并确定最大单位伸长率的方向与数值。

#### 解答：

**回顾：** 沿任意方向 $\vec{n}$ 的**单位伸长率**（或称"工程应变"、"相对伸长"）定义为： 

$$
\delta(\vec{n}) = \dfrac{dl - dl_0}{dl_0} = \dfrac{\|F \cdot \vec{n}\| - \|\vec{n}\|}{\|\vec{n}\|}
$$

 其中 $F$ 为变换梯度张量。 设 $\vec{n}$ 为单位向量，则： 

$$
\delta(\vec{n}) = \sqrt{\vec{n} \cdot C \cdot \vec{n}} - 1
= \sqrt{1 + 2\,\vec{n} \cdot E \cdot \vec{n}} - 1
$$

 在小扰动假设（HPP）下，有： 

$$
\boxed{\delta(\vec{n}) = \vec{n} \cdot \varepsilon \cdot \vec{n}}
\quad (∗3.0)
$$

 其中 $\varepsilon$ 即线性化应变张量。

---

因此，对三条应变计方向，有： 

$$
\begin{cases}
\varepsilon_I = \vec{e}_I \cdot \varepsilon(O) \cdot \vec{e}_I \\[4pt]
\varepsilon_{II} = \vec{e}_{II} \cdot \varepsilon(O) \cdot \vec{e}_{II} \\[4pt]
\varepsilon_{III} = \vec{e}_{III} \cdot \varepsilon(O) \cdot \vec{e}_{III}
\end{cases}
\quad (∗3.1)
$$

应变张量在 $(\vec{e}_x, \vec{e}_y)$ 平面内为对称形式： 

$$
\varepsilon =
\begin{pmatrix}
\varepsilon_{xx} & \varepsilon_{xy}\\[4pt]
\varepsilon_{xy} & \varepsilon_{yy}
\end{pmatrix}_{(\vec{e}_x, \vec{e}_y)}
\quad (∗3.2)
$$

 因此有 3 个独立分量待定，恰好对应三条测量方向。

---

#### 建立方程：

三条测向单位向量分别为： 

$$
\begin{cases}
\vec{e}_I = \cos\alpha\,\vec{e}_x + \sin\alpha\,\vec{e}_y\\[4pt]
\vec{e}_{II} = \cos(\alpha + \beta)\vec{e}_x + \sin(\alpha + \beta)\vec{e}_y\\[4pt]
\vec{e}_{III} = \cos(\alpha + \beta + \gamma)\vec{e}_x + \sin(\alpha + \beta + \gamma)\vec{e}_y
\end{cases}
$$

 代入 $\alpha=0^\circ, \beta=120^\circ, \gamma=120^\circ$：

$$
\boxed{
\begin{cases}
\vec{e}_I = \vec{e}_x \\[4pt]
\vec{e}_{II} = -\dfrac{1}{2}\vec{e}_x + \dfrac{\sqrt{3}}{2}\vec{e}_y \\[6pt]
\vec{e}_{III} = -\dfrac{1}{2}\vec{e}_x - \dfrac{\sqrt{3}}{2}\vec{e}_y
\end{cases}
}
\quad (∗3.3)
$$

---

#### 写出测量方程：

$$
\begin{aligned}
\varepsilon_I &= \vec{e}_I \cdot \varepsilon(O) \cdot \vec{e}_I
= 
\begin{pmatrix}1 & 0\end{pmatrix}
\begin{pmatrix}
\varepsilon_{xx} & \varepsilon_{xy}\\[4pt]
\varepsilon_{xy} & \varepsilon_{yy}
\end{pmatrix}
\begin{pmatrix}1\\0\end{pmatrix}
= \varepsilon_{xx} \quad (∗3.4)\\[8pt]
\varepsilon_{II} &= 
\vec{e}_{II} \cdot \varepsilon(O) \cdot \vec{e}_{II}
= \dfrac{1}{4}\Big[
\varepsilon_{xx} - 2\sqrt{3}\,\varepsilon_{xy} + 3\varepsilon_{yy}
\Big] \quad (∗3.5)\\[8pt]
\varepsilon_{III} &= 
\vec{e}_{III} \cdot \varepsilon(O) \cdot \vec{e}_{III}
= \dfrac{1}{4}\Big[
\varepsilon_{xx} + 2\sqrt{3}\,\varepsilon_{xy} + 3\varepsilon_{yy}
\Big] \quad (∗3.6)
\end{aligned}
$$

---

#### 解方程组：

由 (∗3.4)： 

$$
\varepsilon_{xx} = \varepsilon_I
$$

由 (∗3.5)+(∗3.6)： 

$$
\varepsilon_{II} + \varepsilon_{III}
= \dfrac{1}{2}(\varepsilon_{xx} + 3\varepsilon_{yy})
\Rightarrow
\varepsilon_{yy} = \dfrac{2(\varepsilon_{II} + \varepsilon_{III}) - \varepsilon_I}{3}
$$

由 (∗3.5)-(∗3.6)： 

$$
\varepsilon_{II} - \varepsilon_{III}
= -\dfrac{\sqrt{3}}{2}\,\varepsilon_{xy}
\Rightarrow
\varepsilon_{xy} = \dfrac{\varepsilon_{III} - \varepsilon_{II}}{\sqrt{3}}
$$

---

#### 代入数值：

$$
\varepsilon_I = 0.5\times10^{-4}, \quad
\varepsilon_{II} = 2\times10^{-4}, \quad
\varepsilon_{III} = 2\times10^{-4}
$$

于是： 

$$
\boxed{
\varepsilon_{xx} = 0.5\times10^{-4}, \quad
\varepsilon_{yy} = 2.5\times10^{-4}, \quad
\varepsilon_{xy} = 0
}
$$

即： 

$$
\varepsilon = 10^{-4}
\begin{pmatrix}
0.5 & 0\\[4pt]
0 & 2.5
\end{pmatrix}_{(\vec{e}_x,\vec{e}_y)}
$$

---

**结论：**

该应变张量在基底 $(\vec{e}_x, \vec{e}_y, \vec{e}_z)$ 下为对角形式， 因此 $(\vec{e}_x, \vec{e}_y)$ 即为主方向基底。 其主应变分别为： 

$$
\varepsilon_1 = 0.5\times10^{-4}, \quad
\varepsilon_2 = 2.5\times10^{-4}
$$

 最大伸长方向沿 $\vec{e}_y$，其值为 $2.5\times10^{-4}$。

---

## 问题 3.2：若三根应变计以 45° 间隔布置（$\alpha=0^\circ,\ \beta=45^\circ,\ \gamma=45^\circ$），测量结果为何？

#### 解答：

角度给出： 

$$
\begin{cases}
\vec{e}_I = \cos\alpha\,\vec{e}_x + \sin\alpha\,\vec{e}_y = \vec{e}_x\\[4pt]
\vec{e}_{II} = \cos(\alpha+\beta)\vec{e}_x + \sin(\alpha+\beta)\vec{e}_y
= \dfrac{\sqrt{2}}{2}(\vec{e}_x + \vec{e}_y)\\[6pt]
\vec{e}_{III} = \cos(\alpha+\beta+\gamma)\vec{e}_x + \sin(\alpha+\beta+\gamma)\vec{e}_y
= \vec{e}_y
\end{cases}
\quad (∗3.7)
$$

---

#### 将已知应变张量投影到各方向：

$$
\varepsilon =
10^{-4}
\begin{pmatrix}
0.5 & 0\\[4pt]
0 & 2.5
\end{pmatrix}
$$

计算：

$$
\begin{aligned}
\varepsilon_I &= \vec{e}_I \cdot \varepsilon \cdot \vec{e}_I
= (1,0)
\begin{pmatrix}
0.5 & 0\\[4pt]
0 & 2.5
\end{pmatrix}
\begin{pmatrix}1\\0\end{pmatrix}
= 0.5\times10^{-4}\\[8pt]
\varepsilon_{II} &= 
\vec{e}_{II} \cdot \varepsilon \cdot \vec{e}_{II}
= \dfrac{1}{2}(0.5 + 2.5)\times10^{-4}
= 1.5\times10^{-4}\\[8pt]
\varepsilon_{III} &=
\vec{e}_{III} \cdot \varepsilon \cdot \vec{e}_{III}
= (0,1)
\begin{pmatrix}
0.5 & 0\\[4pt]
0 & 2.5
\end{pmatrix}
\begin{pmatrix}0\\1\end{pmatrix}
= 2.5\times10^{-4}
\end{aligned}
$$

---

**结果：** 

$$
\boxed{
\varepsilon_I = 0.5\times10^{-4}, \quad
\varepsilon_{II} = 1.5\times10^{-4}, \quad
\varepsilon_{III} = 2.5\times10^{-4}
}
$$

这些数值与应变张量主方向一致：

- $\varepsilon_I$ 对应 $\vec{e}_x$ 方向最小应变；

- $\varepsilon_{III}$ 对应 $\vec{e}_y$ 方向最大应变；

- $\varepsilon_{II}$ 对应 45° 方向的中间应变值。
