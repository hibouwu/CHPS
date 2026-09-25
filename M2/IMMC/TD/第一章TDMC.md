# 练习 1 -- 运动学

我们研究一个由下述速度场定义的大气涡旋的运动。 在笛卡尔坐标系 $(O, \vec{e}_1, \vec{e}_2)$ 中，对于某点 $M(x_1, x_2)$ 在时刻 $t$：

$$
\begin{cases}
V_1 = \omega x_2 \\
V_2 = -\omega x_1 + a\omega^2 t
\end{cases}
$$

 其中 $a$ 与 $\omega$ 为常数（$\omega \neq 0$）。

注意：我们用上标 $E\bullet$ 表示欧拉量，用 $\dfrac{d\bullet}{dt}$ 表示质点导数（拉格朗日导数）。

## 问题 1.1：回忆欧拉描述与拉格朗日描述的定义，并说明如何从一种描述转化为另一种。

#### 解答：

这两种描述（或称"视角"）都用于研究同一个运动系统：

**欧拉描述：** 在这种描述中，我们关注的是*空间中固定点处流过的所有质点*，而不是追踪单个质点的运动。 也就是说，我们固定一个空间点，观察该点处随时间变化的速度、加速度、温度等量。

- 它相当于"速度场在时刻 $t$ 的一张快照"；

- 适合研究流体流动，如流体力学；

- 类比地，可将其与利用固定测速雷达测量汽车速度的方式相对应。

数学上： 

$$
E\vec{V} = \dfrac{d\vec{M}(t)}{dt} = \vec{V}(\vec{M}, t) = \vec{V}(x_1, x_2, x_3, t)
$$

**拉格朗日描述：** 以一个参考构型（即在 $t = t_0 = 0$ 的初始时刻）为基础，描述后续各时刻 $t > t_0$ 的配置。 即以每个质点的初始位置 $\vec{M}_0$ 和时间 $t$ 为自变量，给出其在时刻 $t$ 的位置 $\vec{M}$： 

$$
\vec{M} = \vec{M}(\vec{M}_0, t)
$$

- 这对应于质点轨迹方程；

- 更适合研究固体运动；

- 类比地，可视为用 GPS 芯片追踪汽车随时间变化的轨迹与速度。

数学上： 

$$
L\vec{V} = \dfrac{\partial \vec{M}}{\partial t}
= \dfrac{\partial}{\partial t}[\vec{M}(\vec{M}_0, t)]
= \vec{V}(\vec{M}_0, t) = \vec{V}(X_1, X_2, X_3, t)
$$

**备注：** 由 $\vec{M} = \vec{M}(\vec{M}_0, t)$ 可得： 

$$
d\vec{M} = \dfrac{\partial \vec{M}}{\partial t}dt + \dfrac{\partial \vec{M}}{\partial \vec{M}_0}d\vec{M}_0
$$

因为 $\dfrac{\partial \vec{M}_0}{\partial t} = \vec{0}$，故： 

$$
\dfrac{d\vec{M}}{dt} = \dfrac{\partial \vec{M}}{\partial t}
\quad\Rightarrow\quad
E\vec{V} = \dfrac{d\vec{M}(t)}{dt} = \dfrac{\partial \vec{M}(t)}{\partial t} = L\vec{V}(\vec{M}_0, t)
$$

对于加速度，同理有： 

$$
E\vec{V} = E\vec{V}(\vec{M}, t)
\Rightarrow
dE\vec{V} = \dfrac{\partial E\vec{V}}{\partial t}dt + \dfrac{\partial E\vec{V}}{\partial \vec{M}}d\vec{M}
$$

 因此： 

$$
\dfrac{dE\vec{V}}{dt} = \dfrac{\partial E\vec{V}}{\partial t} + \dfrac{\partial E\vec{V}}{\partial \vec{M}}\cdot\dfrac{d\vec{M}}{dt}
= \dfrac{\partial E\vec{V}}{\partial t} + (\nabla E\vec{V})\cdot E\vec{V}
$$

 即： 

$$
E\vec{\Gamma} = \dfrac{dE\vec{V}}{dt}
= \dfrac{\partial E\vec{V}}{\partial t} + (\nabla E\vec{V})\cdot E\vec{V}
$$

**从欧拉描述到拉格朗日描述：** 根据欧拉速度场建立常微分方程系统 $E V_i = \dfrac{dx_i}{dt}$，并结合初始条件求解。

**从拉格朗日描述到欧拉描述：** 对轨迹方程关于时间求导：$E V_i = \dfrac{dx_i(t)}{dt} = \dot{x}_i(X_i, t)$， 再通过代入轨迹表达式 $x_i(t)$，得到速度场 $E V_i = E f(x_i, t)$。

## 问题 1.2：给出该运动的欧拉描述。

#### 解答：

欧拉描述在题目中已经直接给出。 在每个点 $M$、时刻 $t$，速度场为：

$$
E\vec{V}(t) =
\begin{pmatrix}
V_1(t) \\[4pt]
V_2(t)
\end{pmatrix}_{(\vec{e}_1,\vec{e}_2)} =
\begin{pmatrix}
\dot{x}_1(t) \\[4pt]
\dot{x}_2(t)
\end{pmatrix}_{(\vec{e}_1,\vec{e}_2)} =
\begin{pmatrix}
\omega x_2 \\[4pt]
-\omega x_1 + a\omega^2 t
\end{pmatrix}_{(\vec{e}_1,\vec{e}_2)}
$$

---

## 问题 1.3：给出该运动的拉格朗日描述。

#### 解答：

我们希望根据初始位置 $\vec{M}_0$ 描述每个质点或点 $M$ 的轨迹：

$$
\vec{M}(t) =
\begin{pmatrix}
x_1(t) \\[4pt]
x_2(t)
\end{pmatrix}_{(\vec{e}_1,\vec{e}_2)}, \quad
\vec{M}_0 =
\begin{pmatrix}
X_1 \\[4pt]
X_2
\end{pmatrix}_{(\vec{e}_1,\vec{e}_2)} =
\begin{pmatrix}
x_1(0) \\[4pt]
x_2(0)
\end{pmatrix}_{(\vec{e}_1,\vec{e}_2)}
$$

于是： 

$$
\begin{pmatrix}
E V_1(t) \\[4pt]
E V_2(t)
\end{pmatrix} =
\begin{pmatrix}
\dfrac{dx_1(t)}{dt} \\[6pt]
\dfrac{dx_2(t)}{dt}
\end{pmatrix} =
\begin{pmatrix}
\dot{x}_1(t) \\[4pt]
\dot{x}_2(t)
\end{pmatrix} =
\begin{pmatrix}
\omega x_2 \\[4pt]
-\omega x_1 + a\omega^2 t
\end{pmatrix}
\Rightarrow
\begin{cases}
\dot{x}_1(t) = \omega x_2 \quad &(∗1.1) \\[4pt]
\dot{x}_2(t) = -\omega x_1 + a\omega^2 t \quad &(∗1.2)
\end{cases}
$$

**备注：** $x_1$ 与 $x_2$ 实际上都是 $x_1(t)$、$x_2(t)$ 的简写，均依赖于时间。

---

方程 $(∗1.1)$ 表示 $x_1$ 的时间导数与 $x_2(t)$ 有简单关系，可代入另一方程。 方程 $(∗1.2)$ 含有 $x_1(t)$，而我们已知其导数形式，因此对 $(∗1.2)$ 求导并代入 $(∗1.1)$，得到只含 $x_2(t)$ 与 $\ddot{x}_2(t)$ 的方程：

$$
\dfrac{\partial}{\partial t}(∗1.2)
\Rightarrow
\ddot{x}_2 = -\omega \dot{x}_1 + a\omega^2 = -\omega^2 x_2 + a\omega^2
\Rightarrow
\boxed{\ddot{x}_2 + \omega^2 x_2 = a\omega^2 \quad (∗1.3)}
$$

我们得到一个二阶常微分方程，描述**无阻尼振动运动**。 首先求解对应的齐次方程（即无右端项）：

$$
\ddot{x}_2 + \omega^2 x_2 = 0
$$

其一般形式为： 

$$
y'' + 2\lambda y' + \omega_0^2 y = 0
$$

 其中： 

$$
\begin{cases}
y = x_2(t) \\
\lambda = 0 \quad \text{（阻尼系数）}\\
\omega_0 = \omega \quad \text{（固有角频率）}
\end{cases}
$$

其特征方程： 

$$
r^2 + 2\lambda r + \omega_0^2 = 0
$$

 判别式 $\Delta = 4(\lambda^2 - \omega_0^2)$，因此可区分多种情况：

- **周期性（非阻尼）**：$\Delta = -4\omega_0^2 \Leftrightarrow \lambda = 0$ 解为： 

$$
y(t) = A\cos(\omega_0 t) + B\sin(\omega_0 t)
$$

 或等价写为： 

$$
y(t) = C e^{\omega_0 t} + D e^{-\omega_0 t}
$$

 其中 $A,B,C,D$ 为常数。

- **临界阻尼**：$\Delta = 0 \Leftrightarrow \lambda = \omega_0$ 解为： 

$$
y(t) = e^{-\lambda t}(A t + B)
$$

- **过阻尼（非周期）**：$\Delta > 0 \Leftrightarrow \lambda > \omega_0$ 解为： 

$$
y(t) = e^{-\lambda t}\left[A e^{\sqrt{\Delta}t} + B e^{-\sqrt{\Delta}t}\right]
$$

- **欠阻尼（伪周期）**：$\Delta < 0 \Leftrightarrow \lambda < \omega_0$，此时 

$$
\tilde{\omega}_0 = \sqrt{\omega_0^2 - \lambda^2}
$$

 解为： 

$$
y(t) = e^{-\lambda t}[A\cos(\tilde{\omega}_0 t) + B\sin(\tilde{\omega}_0 t)]
$$

在此，$\lambda = 0$，因此我们处于**周期性情形**。齐次方程的解为： 

$$
y_0(t) = A\cos(\omega t) + B\sin(\omega t)
$$

方程右端为常数 $a\omega^2$，其特解 $y_p(t)$ 亦为常数： 

$$
y_p = K
$$

 故通解为： 

$$
y(t) = y_0(t) + y_p(t) = A\cos(\omega t) + B\sin(\omega t) + K \quad (∗1.4)
$$

将其代入方程 $(∗1.3)$： 

$$
\ddot{x}_2 + \omega^2 x_2 = a\omega^2
\Rightarrow
-\omega^2(A\cos(\omega t) + B\sin(\omega t)) + \omega^2 x_2 = a\omega^2
$$

 得： 

$$
x_2(t) = A\cos(\omega t) + B\sin(\omega t) + a
$$

对其求导并代入 $(∗1.2)$： 

$$
\dot{x}_2(t) = \omega[-A\sin(\omega t) + B\cos(\omega t)]
\Rightarrow
\omega[-A\sin(\omega t) + B\cos(\omega t)] = -\omega x_1 + a\omega^2 t
$$

 从而： 

$$
x_1(t) = A\sin(\omega t) - B\cos(\omega t) + a\omega t
$$

利用初始条件求常数： 

$$
\begin{cases}
x_1(0) = X_1 \Rightarrow B = -X_1 \\[4pt]
x_2(0) = X_2 \Rightarrow A = X_2 - a
\end{cases}
$$

最终得到： 

$$
\boxed{
\begin{aligned}
x_1(t) &= (X_2 - a)\sin(\omega t) + X_1\cos(\omega t) + a\omega t \quad &(∗1.5)\\[4pt]
x_2(t) &= (X_2 - a)\cos(\omega t) - X_1\sin(\omega t) + a \quad &(∗1.6)
\end{aligned}
}
$$

## 问题 1.4：给出并绘制流线与轨迹。

#### 解答：

**回顾：**

1.  **轨迹（Trajectoires）** 由方程 $x_i(t) = f_i(X_i, t)$ 给出。 这些曲线连接了同一质点从初始时刻 $t_0$ 到任意时刻 $t$ 所占据的所有位置。

2.  **流线（Lignes de courant）** 是在某固定时刻 $t$，与欧拉速度场 $\vec{V}(M, t)$ 相切（或共线）的空间曲线。 它们表示"时刻 $t$ 的瞬时速度分布图像"。 尽管在固定时刻分析，但由于速度场可能随时间变化，流线也可能随 $t$ 改变。

要确定流线方程，可令位置矢量为： 

$$
\overrightarrow{OM} = x_1\vec{e}_1 + x_2\vec{e}_2
$$

 要求微小位移 $d\vec{M}$ 与速度 $\vec{V}(M,t)$ 共线，即两者叉积为零： 

$$
d\vec{M} \wedge E\vec{V}(t, M) = \vec{0}
$$

 该条件导致空间积分（非时间积分，因为 $t$ 固定），计算上有时不太直观。

3.  若运动**非定常（instationnaire）**，则轨迹与流线不同； 若**定常（stationnaire）**，两者重合。

4.  然而，即使轨迹与流线重合，也不一定说明运动是定常的。 例如，一个质点沿固定方向作往复振动的运动，其轨迹与流线重合，但运动仍是随时间变化的。

---

首先，验证该运动是否定常。 若定常，则轨迹与流线重合，可免去流线计算。 但本题中速度场含时项 $a\omega^2 t$，故运动**非定常（instationnaire）**。 因此需分别计算轨迹与流线。

---

**1. 轨迹：** 由前一问得轨迹方程： 

$$
\begin{cases}
x_1(t) = (X_2 - a)\sin(\omega t) + X_1\cos(\omega t) + a\omega t \quad &(∗1.5)\\[4pt]
x_2(t) = (X_2 - a)\cos(\omega t) - X_1\sin(\omega t) + a \quad &(∗1.6)
\end{cases}
$$

---

**2. 流线：**

令 $\overrightarrow{OM} = x_1\vec{e}_1 + x_2\vec{e}_2$，求解：

$$
d\vec{M} \wedge E\vec{V}(t, M) = \vec{0}
\Rightarrow
\begin{pmatrix}
dx_1 \\[2pt]
dx_2
\end{pmatrix}
\wedge
\begin{pmatrix}
\dot{x}_1(t) \\[2pt]
\dot{x}_2(t)
\end{pmatrix} =
\begin{pmatrix}
0 \\ 0
\end{pmatrix}
$$

将欧拉速度分量代入： 

$$
\begin{pmatrix}
dx_1 \\[2pt]
dx_2
\end{pmatrix}
\wedge
\begin{pmatrix}
\omega x_2 \\[2pt]
-\omega x_1 + a\omega^2 t
\end{pmatrix} = \vec{0}
$$

展开得： 

$$
(-\omega x_1 + a\omega^2 t)\,dx_1 - \omega x_2\,dx_2 = 0
\Rightarrow
(-x_1 + a\omega t)\,dx_1 - x_2\,dx_2 = 0
\Rightarrow
(x_1 - a\omega t)\,dx_1 + x_2\,dx_2 = 0
$$

为积分方便，分离变量并积分（积分在空间上进行，$t$ 固定）：

$$
\frac{1}{2}(x_1 - a\omega t)^2 + \frac{1}{2}x_2^2 = C(t) \ge 0
\Rightarrow
(x_1 - a\omega t)^2 + x_2^2 = 2C(t) = [D(t)]^2
$$

**备注：** 由于积分是在空间中进行，积分常数 $C(t)$ 可能依赖于时间。 因为 $(x_1 - a\omega t)^2 + x_2^2 \ge 0$，因此可写为平方形式 $[D(t)]^2$。

---

由此可见，流线是**圆**，其圆心为 $(a\omega t, 0)$，半径任意。 半径的具体数值由该流线经过的点 $(x_1, x_2)$ 在时刻 $t$ 决定。

从几何上看，也可以根据速度场图像（各时刻 $t$ 下的速度矢量切线）绘制流线。 无论从方程还是从直观图像都可看出： 这是一个绕中心 $(a\omega t, 0)$ 的**圆周运动（涡旋）**。 中心随时间沿 $\vec{e}_1$ 方向移动，其速度为： 

$$
\vec{V}_{\text{centre}} = a\omega \vec{e}_1
$$

---

**补充说明：**

- 从直觉上看，初始位于原点的质点似乎沿涡旋中心方向直线运动，但这其实是错误的。 它很快离开中心并被卷入旋涡运动。

- 只有在初始位置 $(0, a)$ 的质点沿直线运动。 这一点可由 $V_2 = \dot{x}_2(t) = 0$ 推出。

# IMMC 连续介质运动学习题 1（TD1）

## 练习 2 ------ 转动运动（Mouvement de rotation）------ 运动学（Cinématique）

在欧几里得空间 $E$ 中，考虑配有正交归一基 $(\vec{e}_1, \vec{e}_2, \vec{e}_3)$。 以下关系定义了刚体绕 $(O, \vec{e}_3)$ 轴以角速度 $\omega$ 旋转的运动，对应一个圆柱体 $\Omega$（见图 2.1）。 $\vec{X}$ 与 $\vec{x}$ 分别表示初始时刻 $(t = 0)$ 与当前时刻的空间位置：

$$
\begin{aligned}
x_1 &= X_1 \cos(\theta) - X_2 \sin(\theta) \\
x_2 &= X_1 \sin(\theta) + X_2 \cos(\theta) \\
x_3 &= X_3 \tag{2.1}
\end{aligned}
$$

其中 $\theta = \omega t$ 表示时刻 $t$ 的转角。

#### 问题 2.1：

给出此运动的拉格朗日（Lagrangienne）和欧拉（Eulérienne）描述。

### 问题 2.1：解答

此运动由轨迹方程给出，即质点当前位置 $(x_1, x_2, x_3)$ 关于其初始坐标 $(X_1, X_2, X_3)$ 的函数关系。 因此，拉格朗日描述已由式 (2.1) 给出：

$$
x_1 = X_1 \cos(\omega t) - X_2 \sin(\omega t) \tag{∗2.1}
$$

$$
x_2 = X_1 \sin(\omega t) + X_2 \cos(\omega t) \tag{∗2.2}
$$

$$
x_3 = X_3 \tag{∗2.3}
$$

对于欧拉描述，需要：

- 对轨迹方程关于时间求导，以得到拉格朗日速度场；

- 在速度表达式中识别轨迹 $(x_i(t, X_i))$，并将其改写为当前坐标 $x_i$ 的函数。

对时间求导可得：

$$
\begin{cases}
\dot{x}_1 = \omega[-X_1 \sin(\omega t) - X_2 \cos(\omega t)] \\
\dot{x}_2 = \omega[X_1 \cos(\omega t) - X_2 \sin(\omega t)] \\
\dot{x}_3 = 0
\end{cases}
$$

利用式 (∗2.1) 与 (∗2.2)，可化简为：

$$
\begin{cases}
\dot{x}_1 = -\omega x_2 \\
\dot{x}_2 = \omega x_1 \\
\dot{x}_3 = 0
\end{cases}
\tag{∗2.4}
$$

因此，欧拉速度场可表示为：

$$
\boxed{
\vec{V} = 
\begin{pmatrix}
V_1 \\ V_2 \\ V_3
\end{pmatrix} =
\begin{pmatrix}
-\omega x_2 \\ \omega x_1 \\ 0
\end{pmatrix}
}
\tag{∗2.5}
$$

该速度场对应刚体绕 $z$ 轴的匀角速度转动运动。

#### 附注：

这种形式满足刚体速度场的一般关系： 

$$
\vec{V}(M) = \vec{\omega} \wedge \overrightarrow{OM}
$$

 其中 $\vec{\omega} = (0, 0, \omega)$。
