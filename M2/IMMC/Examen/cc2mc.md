# 练习 1 ------ 课程问题与理解（QCM）

请在 QCM 试卷首页填写学号与页码。直接勾选正确答案，无需证明。若答案错误不扣分。

## 问题 1.1

列出以拉格朗日描述给出的场（$\alpha, \beta, \gamma$ 为常数）： 

$$
\begin{cases}
\text{(A)}\; T(t, \vec{M_0}) = \alpha X_1 t + \beta X_2 \quad \checkmark\\
\text{(B)}\; \vec{\Gamma}(t, \vec{M}) = x_1\vec{e_1} - x_2\vec{e_2}\\
\text{(C)}\; \vec{V}(t, \vec{M}) = \alpha t\vec{e_1} + \beta x_1\vec{e_2}\\
\text{(D)}\; \vec{u}(t, \vec{M_0}) = \gamma X_1\vec{e_2} \quad \checkmark
\end{cases}
$$

## 问题 1.2

哪些方程必然意味着介质发生形变？ 

$$
\begin{aligned}
&\text{(A)}~ F \neq I \\
&\text{(B)}~ C \neq I \quad \checkmark\\
&\text{(C)}~ E \neq O \quad \checkmark\\
&\text{(D)}~ E = I \quad \checkmark\\
&\text{(E)}~ \vec{u} \neq \vec{0}\\
&\text{(F)}~ \mathrm{div}\,\vec{V} \neq 0 \quad \checkmark\\
&\text{(G)}~ D \neq O \quad \checkmark\\
&\text{(H)}~ \Omega \neq O
\end{aligned}
$$

## 问题 1.3

给定应力张量： 

$$
\sigma =
\begin{pmatrix}
p & 0 & 0\\
0 & p & 0\\
0 & 0 & p
\end{pmatrix}_{(\vec{e_1},\vec{e_2},\vec{e_3})}
$$

 判断下列命题： 

$$
\text{(A)}~ \text{在法向为 }\vec{e_1}\text{ 的面上，法向应力 }=p \quad \checkmark
$$

 

$$
\text{(B)}~ \text{在法向为 }\vec{e_1}\text{ 的面上，切向应力 }=p
$$

 

$$
\text{(C)}~ \text{在法向为 }\vec{e_1}\text{ 的面上，切向应力 }=0 \quad \checkmark
$$

 

$$
\text{(D)}~ \text{在法向为 }\vec{e_2}\text{ 的面上，法向应力 }=0
$$

 

$$
\text{(E)}~ \text{在法向为 }\vec{e_2}\text{ 的面上，法向应力 }=p \quad \checkmark
$$

 

$$
\text{(F)}~ \text{在法向为 }\vec{e_2}\text{ 的面上，切向应力 }=0 \quad \checkmark
$$

## 问题 1.4

应力张量： 

$$
\sigma =
\begin{pmatrix}
\tau & 0 & 0\\
0 & -\tau & 0\\
0 & 0 & 0
\end{pmatrix}_{(\vec{e_1},\vec{e_2},\vec{e_3})}
$$

 其中 $\tau$ 为常数。判断： 

$$
\begin{cases}
\text{(A)}~ \text{纯拉伸}\\
\text{(B)}~ \text{球形张量}\\
\text{(C)}~ \text{纯剪切} \quad \checkmark\\
\text{(D)}~ \text{双轴张量} \quad \checkmark\\
\text{(E)}~ \text{散度为零} \quad \checkmark\\
\text{(F)}~ \text{偏张量} \quad \checkmark
\end{cases}
$$

## 问题 1.5

在纯剪切（幅值 $\tau$）下，哪个强度判据最严格？ 

$$
\text{(A) Tresca}~\checkmark \quad
\text{(B) von Mises} \quad
\text{(C) 无} \quad
\text{(D) 依赖于 }\tau
$$

## 问题 1.6

静力平衡方程： 

$$
\begin{cases}
\text{(A)}~ \sigma(M)\cdot \vec{n}(M) = \vec{T_d}(M),~\forall M\in \partial\Omega_T \quad \checkmark\\
\text{(B)}~ \vec{u}(M)=\vec{u_d}(M),~\forall M\in \partial\Omega_u\\
\text{(C)}~ \sigma = \lambda(\text{Tr}\varepsilon)I + 2\mu\varepsilon,~\forall M\in\Omega\\
\text{(D)}~ -\text{div}\,\sigma(M) + \vec{f_d}(M)=\vec{0},~\forall M\in\Omega \quad \checkmark
\end{cases}
$$

## 问题 1.7

牛顿流体的本构关系： 

$$
\begin{cases}
\text{(A)}~ \varepsilon = \dfrac{1+\nu}{E}\sigma - \dfrac{\nu}{E}\text{Tr}(\sigma)I\\
\text{(B)}~ \sigma = 2\mu\varepsilon + \lambda\,\text{Tr}(\varepsilon)I\\
\text{(C)}~ \sigma = -pI\\
\text{(D)}~ \sigma = 2\mu_v D - pI \quad \checkmark
\end{cases}
$$

## 问题 1.8

线弹性连续介质中位移场的特征： 

$$
\text{(A) 连续}~\checkmark \quad
\text{(B) 零值} \quad
\text{(C) 不连续} \quad
\text{(D) 光滑}~\checkmark
$$

## 问题 1.9

求解牛顿流体问题所需方程： 

$$
\text{(A) Navier-Stokes 方程}~\checkmark \quad
\text{(B) Navier 方程} \quad
\text{(C) 质量守恒方程}~\checkmark
$$

 

$$
\text{(E) 速度边界条件}~\checkmark \quad
\text{(F) 应力边界条件}~\checkmark
$$

## 问题 1.10

若运动学可容位移场的势能为零，则： 

$$
\text{(E)}~ \text{以位移写出的形变能被外力所做功完全抵消。}~\checkmark
$$

# 练习 2 ------ 连续介质的运动学

设参考直角坐标系为 $(O,\vec{e_1},\vec{e_2},\vec{e_3})$。 研究一个连续介质的运动，其欧拉速度场给定如下： 

$$
\vec{V}(M,t) = -\dfrac{v t}{\tau}\vec{e_1} - \dfrac{x_1}{\tau}\vec{e_2}
$$

 其中 $v$ 与 $\tau$ 为给定正常数，$t$ 为时间变量，点 $M$ 在当前（或变形后）构型中的坐标为 $(x_1, x_2, x_3)$。

## 问题 2.1：常数 $v$ 与 $\tau$ 的单位

**解答：** $v$ 的单位为 $\mathrm{m·s^{-1}}$，$\tau$ 的单位为 $\mathrm{s}$。

## 问题 2.2：绘制速度场在 $t=0$ 与 $t=\tau$ 时的形式，并说明 $t=0$ 时的运动类型

**解答：** 在 $t=0$ 与 $t=\tau$ 时有： 

$$
\vec{V}(M,0) = -\dfrac{x_1}{\tau}\vec{e_2}, 
\qquad
\vec{V}(M,\tau) = -v\vec{e_1} - \dfrac{x_1}{\tau}\vec{e_2}
$$

 当 $t=0$ 时，观察到的运动为沿 $(\vec{e_1},\vec{e_3})$ 平面的纯滑移，方向为 $\vec{e_2}$。

## 问题 2.3：求形变率张量 $D$，并说明各分量单位

**解答：** 形变率张量 $D$ 为速度梯度的对称部分，其分量单位为 $\mathrm{s^{-1}}$： 

$$
\nabla \vec{V} = -\dfrac{1}{\tau}
\begin{pmatrix}
0 & 0 & 0\\
1 & 0 & 0\\
0 & 0 & 0
\end{pmatrix}
\quad\Rightarrow\quad
D = \dfrac{1}{2}(\nabla \vec{V} + \nabla^T \vec{V})
= -\dfrac{1}{2\tau}
\begin{pmatrix}
0 & 1 & 0\\
1 & 0 & 0\\
0 & 0 & 0
\end{pmatrix}
$$

## 问题 2.4：求运动的拉格朗日表示形式

即求函数 $f_1,f_2,f_3$，使： 

$$
\begin{cases}
x_1 = f_1(X_1, X_2, X_3, t)\\
x_2 = f_2(X_1, X_2, X_3, t)\\
x_3 = f_3(X_1, X_2, X_3, t)
\end{cases}
$$

 其中 $(X_1, X_2, X_3)$ 为 $t=0$ 时点的初始坐标。

**解答：** 由欧拉速度场可建立常微分方程组： 

$$
\begin{cases}
\dot{x}_1(t) = -\dfrac{v t}{\tau}\\
\dot{x}_2(t) = -\dfrac{x_1}{\tau}\\
\dot{x}_3(t) = 0
\end{cases}
\quad\text{且}\quad
\begin{cases}
x_1(0)=X_1\\
x_2(0)=X_2\\
x_3(0)=X_3
\end{cases}
$$

 积分得： 

$$
\begin{cases}
x_1(t) = -\dfrac{v t^2}{2\tau} + X_1\\[4pt]
x_2(t) = \dfrac{v t^3}{6\tau^2} - \dfrac{X_1 t}{\tau} + X_2\\[4pt]
x_3(t) = X_3
\end{cases}
$$

## 问题 2.5：求最初位于原点的点 $O$ 的轨迹

**解答：** 将 $\vec{M_0}=(X_1,X_2,X_3)=(0,0,0)$ 代入上式得： 

$$
\begin{cases}
x_1(O,t) = -\dfrac{v t^2}{2\tau}\\
x_2(O,t) = \dfrac{v t^3}{6\tau^2}\\
x_3(O,t) = 0
\end{cases}
$$

 故 

$$
\dfrac{x_2(O,t)}{x_1(O,t)} = -\dfrac{t}{3\tau}
\quad\Rightarrow\quad
x_2(O,t) = -\dfrac{t}{3\tau}\,x_1(O,t)
$$

 表示轨迹在 $(x_1,x_2)$ 平面上为一条立方曲线。

## 问题 2.6：求变换梯度算子 $F$ 及 Green--Lagrange 形变张量 $E$

并说明两者分量的单位。

**解答：** 变换梯度（无量纲）： 

$$
F = \nabla_X \bm{\varphi} =
\begin{pmatrix}
1 & 0 & 0\\
-\dfrac{t}{\tau} & 1 & 0\\
0 & 0 & 1
\end{pmatrix}
$$

 Green--Lagrange 形变张量（无量纲）： 

$$
E = \dfrac{1}{2}(F^T F - I)
= \dfrac{t}{2\tau}
\begin{pmatrix}
\dfrac{t}{\tau} & -1 & 0\\
-1 & 0 & 0\\
0 & 0 & 0
\end{pmatrix}
$$

## 问题 2.7：求体积相对变化率

**解答：** 体积比由变换梯度行列式给出： 

$$
\dfrac{dV}{dV_0} = \det F
= 
\begin{vmatrix}
1 & 0 & 0\\
-\dfrac{t}{\tau} & 1 & 0\\
0 & 0 & 1
\end{vmatrix}
= 1
\quad\Rightarrow\quad
\dfrac{dV - dV_0}{dV_0} = 0
$$

 因此运动为**等体积（等容）**运动。

## 问题 2.8：在小扰动假设（HPP）下，求线性化形变张量 $\varepsilon$ 并给出假设成立条件

**解答：** 位移场： 

$$
\vec{u}(M,t) = \overrightarrow{OM}(t) - \overrightarrow{OM_0}
= 
\begin{pmatrix}
x_1 - X_1\\
x_2 - X_2\\
x_3 - X_3
\end{pmatrix}
= 
-\dfrac{t}{\tau}
\begin{pmatrix}
\dfrac{v t}{2}\\
\dfrac{v t^2}{6\tau} + X_1\\
0
\end{pmatrix}
$$

 计算得： 

$$
\nabla \vec{u} = -\dfrac{t}{\tau}
\begin{pmatrix}
0 & 0 & 0\\
1 & 0 & 0\\
0 & 0 & 0
\end{pmatrix},
\quad
\varepsilon = \dfrac{1}{2}\left(\nabla \vec{u} + \nabla^T \vec{u}\right)
= -\dfrac{t}{2\tau}
\begin{pmatrix}
0 & 1 & 0\\
1 & 0 & 0\\
0 & 0 & 0
\end{pmatrix}
$$

 假设 HPP 成立当且仅当： 

$$
\|\nabla \vec{u}\| \ll 1
\quad\Rightarrow\quad
\left|\dfrac{t}{\tau}\right| \ll 1
$$

 即 $t \ll \tau$，且位移 $\|\vec{u}\|$ 在区域 $\Omega_0$ 上很小。

## 问题 2.9：此运动的特征

**解答：** 该运动： - **非定常**（$\partial_t \vec{V} \neq 0$） - **不可压缩**（$\mathrm{div}\,\vec{V} = 0$） - **有旋的**（$\mathrm{rot}\,\vec{V} \neq 0$）

# 练习 3 ------ 圆柱轴中的应力状态

考虑一个圆柱形轴，其母线与 $\vec{e_3}$ 轴平行，高度为 $h$。 其横截面为以 $O$ 为中心、半径为 $R$ 的圆。 该圆柱体两底面分别为： 

$$
\Sigma_0: x_3 = 0, \quad
\Sigma_h: x_3 = h
$$

 侧表面记为 $\Sigma_{lat}$。

轴在平衡状态下，其应力张量场如下： 

$$
\sigma(x_1,x_2,x_3) =
\begin{pmatrix}
0 & 0 & A x_2\\
0 & 0 & -A x_1\\
A x_2 & -A x_1 & 0
\end{pmatrix}_{(\vec{e_1},\vec{e_2},\vec{e_3})}
$$

 其中 $A>0$ 为常数。

## 问题 3.1：关于外加体力的推论

**解答：** 由静力平衡方程（局部形式）： 

$$
-\mathrm{div}\,\sigma + \vec{f_v} = \vec{0}
$$

 代入可得： 

$$
\mathrm{div}\,\sigma =
\begin{pmatrix}
0\\0\\0
\end{pmatrix}
\quad\Rightarrow\quad
\vec{f_v} = \vec{0}
$$

 因此，体力为零（或可忽略）。

## 问题 3.2：求侧面 $\Sigma_{lat}$ 上的表面力密度

**解答：** 表面力密度 $\vec{T}_{lat}$ 与应力场关系为： 

$$
\vec{T}_{lat}(M) = \sigma(M)\cdot \vec{n}(M)
$$

 其中外法向为： 

$$
\vec{n}(M) = \dfrac{x_1\vec{e_1} + x_2\vec{e_2}}{\sqrt{x_1^2 + x_2^2}},\quad \forall M\in\Sigma_{lat}
$$

 代入： 

$$
\vec{T}_{lat}(M) = 
A\begin{pmatrix}
0 & 0 & x_2\\
0 & 0 & -x_1\\
x_2 & -x_1 & 0
\end{pmatrix}
\cdot
\dfrac{1}{\sqrt{x_1^2+x_2^2}}
\begin{pmatrix}x_1\\x_2\\0\end{pmatrix}
= \vec{0}
$$

 因此，侧面 $\Sigma_{lat}$ 无应力（自由面）。

## 问题 3.3：计算底面 $\Sigma_0$ 与顶面 $\Sigma_h$ 上的表面力密度，并证明合力为零

**解答：** 在 $\Sigma_0$ 上，法向 $\vec{n}=-\vec{e_3}$： 

$$
\vec{T}_0(M) = \sigma(M)\cdot (-\vec{e_3})
= A\begin{pmatrix}-x_2\\x_1\\0\end{pmatrix}
$$

 在 $\Sigma_h$ 上，法向 $\vec{n}=+\vec{e_3}$： 

$$
\vec{T}_h(M) = \sigma(M)\cdot \vec{e_3}
= A\begin{pmatrix}x_2\\-x_1\\0\end{pmatrix}
$$

 可见两面力密度相反且在 $(\vec{e_1},\vec{e_2})$ 平面内。

计算每个底面合力： 

$$
\vec{R}_0 = \int_{\Sigma_0}\vec{T}_0(M)\,dS
= A\int_{\Sigma_0}(-x_2\vec{e_1}+x_1\vec{e_2})\,dS = \vec{0}
$$

 同理 $\vec{R}_h=\vec{0}$。 由于 $x_1,x_2$ 关于圆域积分为奇函数，因此结果为零。

## 问题 3.4：分别计算在 $O$ 与 $O'$ 点（两底面中心）处的力矩，并解释作用性质

**解答：** 底面 $\Sigma_0$ 上的力矩： 

$$
\vec{H}_0 = \int_{\Sigma_0} \overrightarrow{OM}\wedge \vec{T}_0(M)\,dS
= A\int_{\Sigma_0}
\begin{pmatrix}x_1\\x_2\\0\end{pmatrix}
\wedge
\begin{pmatrix}-x_2\\x_1\\0\end{pmatrix}\,dS
= A\int_{\Sigma_0}r^2\vec{e_3}\,dS
$$

 

$$
\Rightarrow \vec{H}_0 = A\pi R^4/2 \; \vec{e_3}
$$

 同理，顶面： 

$$
\vec{H}_h = -A\pi R^4/2 \; \vec{e_3}
$$

 因此： - 两面合力为零； - 力矩相等反向； - 均绕 $\vec{e_3}$ 轴作用。

**结论：** 该圆柱轴承受一纯扭矩载荷。

## 问题 3.5：求主应力与 Tresca 等效应力，并确定最大位置

**解答：** 解特征方程： 

$$
\det(\sigma - \lambda I) = 0
\quad\Rightarrow\quad
\lambda_1 = 0, \quad \lambda_{2,3} = \pm A r
$$

 按升序排列： 

$$
\sigma_1 = -A r, \quad \sigma_2 = 0, \quad \sigma_3 = A r
$$

 Tresca 等效应力： 

$$
\sigma_{Tr}(r) = \max_{i,j}|\sigma_i-\sigma_j|
= 2A r
$$

 最大值出现在 $r=R$，即外表面。

## 问题 3.6：已知材料屈服极限为 $\sigma_e$，求最大允许扭矩

**解答：** Tresca 准则： 

$$
\sigma_{Tr}^{\max} = 2AR \leq \sigma_e
\quad\Rightarrow\quad
A \leq \dfrac{\sigma_e}{2R}
$$

 扭矩： 

$$
C = \|\vec{H}_0\| = A\dfrac{\pi R^4}{2}
\quad\Rightarrow\quad
C_{\max} = \dfrac{\sigma_e\pi R^3}{4}
$$

 若采用 von Mises 准则： 

$$
\sigma_{VM}^{\max} = \sqrt{3}AR \leq \sigma_e
\quad\Rightarrow\quad
C_{\max} = \dfrac{\sigma_e\pi R^3}{2\sqrt{3}}
$$

**结论：** Tresca 判据更为保守（较小的极限扭矩）。

# 练习 4 ------ 受拉梁

考虑一根长为 $L$ 的平行六面体梁，其轴线沿直角坐标系 $(O,\vec{e_x},\vec{e_y},\vec{e_z})$ 中的 $\vec{e_z}$ 方向。 其横截面为边长为 $a$ 的正方形，该方形截面以 $\vec{e_z}$ 轴为中心对称。 坐标原点 $O$ 位于底面 $z = 0$ 的中心。

材料为各向同性、均匀的线弹性体，具有杨氏模量 $E$，泊松比 $\nu = 0.3$。 梁处于静力平衡状态，体力忽略不计。

底面 $z=0$ 与一个刚性平面接触，该平面在 $(x,y)$ 平面内可自由滑动，这意味着在该面上**无切向应力**。 各表面的表面力密度均假设为均匀分布。 侧面均为自由面（无外力）。 顶面 $z=L$ 上合力的扭转子（以该面中心 $O'$ 为参考点）为： 

$$
T_L = 
\left\{
\begin{array}{l}
\vec{R} = F\vec{e_z}\\[4pt]
\vec{M}_{O'} = \vec{0}
\end{array}
\right\}_{O'}
$$

## 问题 4.1：建立完整问题（方程、边界条件、本构关系），并分类静态/运动学可容性

**解答：**

在区域 

$$
x \in [-a/2,a/2],\quad y\in[-a/2,a/2],\quad z\in[0,L]
$$

 上建立问题。

#### （1）运动学可容性（CA）

- 小扰动假设（HPP）下的线性化应变定义： 

$$
\varepsilon(\vec{u}) = \dfrac{1}{2}\bigl(\nabla\vec{u} + \nabla^T\vec{u}\bigr)
$$

 要求：

  - 位移场 $\vec{u}$ 在 $\Omega$ 内连续且足够光滑；

  - 应变场 $\varepsilon$ 在 $\Omega$ 内兼容（可由某位移场积分得到）。

- 位移边界条件（运动学边界）一般写作：$\vec{u} = \vec{u}_d$ 于 $\partial\Omega_u$ 上。 本题中：底面 $z = 0$ 与刚性平面接触且在平面内可滑动，仅法向位移被约束： 

$$
\vec{u}(z=0)\cdot \vec{e_z} = 0
$$

#### （2）静态可容性（SA）

- 局部平衡方程（静力，无体力）： 

$$
-\mathrm{div}\,\sigma = \vec{0},\quad \forall M\in\Omega
$$

- 边界平衡（应力边界条件）一般形式：在 $\partial\Omega_T$ 上 

$$
\sigma\cdot\vec{n} = \vec{T}_d
$$

 或以扭转子形式： 

$$
\int_{\partial\Omega_T}\sigma\cdot\vec{n}\,dS = \vec{R},\quad
    \int_{\partial\Omega_T}\overrightarrow{PM}\wedge(\sigma\cdot\vec{n})\,dS = \vec{M}_P
$$

 在本题中：

  - 四个侧面均为自由面： 

$$
\sigma(x=\pm a/2)\cdot\vec{n} = \vec{0},\quad
        \sigma(y=\pm a/2)\cdot\vec{n} = \vec{0}
$$

  - 底面 $z=0$：与刚性平面接触且可滑动，意味着法向位移为零且无切向应力： 

$$
\vec{u}(z=0)\cdot\vec{n}(z=0)=0,\quad 
        \sigma(z=0)\cdot\vec{n}(z=0)\cdot\vec{e_x}=0,\quad
        \sigma(z=0)\cdot\vec{n}(z=0)\cdot\vec{e_y}=0
$$

  - 顶面 $z=L$：施加均匀拉力，对应给定合力 $\vec{R}=F\vec{e_z}$、力矩为零。 由于应力均匀： 

$$
\sigma(z=L)\cdot\vec{n}(z=L) = \dfrac{F}{S}\vec{e_z},\quad S = a^2
$$

 且 

$$
\int_{S_L}\overrightarrow{O'M}\wedge\bigl(\sigma\cdot\vec{n}\bigr)\,dS = \vec{0}
$$

#### （3）本构关系

材料为各向同性线弹性体，采用应力---应变的逆形式： 

$$
\varepsilon = \mathbb{K}^{-1}\sigma
= \dfrac{1+\nu}{E}\sigma - \dfrac{\nu}{E}\mathrm{Tr}(\sigma)\,I,\quad \forall M\in\Omega
$$

## 问题 4.2：问题是否有唯一解？为什么？

**解答：**

该问题**在应力与应变上**是适定且解唯一的（本构线性、边界条件充分）。 但在位移上，由于只在 $z=0$ 面约束法向位移，仍然允许：

- 整体沿 $\vec{e_x},\vec{e_y}$ 的刚体平移；

- 绕 $O\vec{e_x}$、$O\vec{e_y}$ 的刚体转动。

即位移解只在一个刚体运动之差内确定，因此位移**非唯一**。

现假设应力场形式为 

$$
\sigma =
\begin{pmatrix}
0 & 0 & 0\\
0 & 0 & 0\\
0 & 0 & g(z)
\end{pmatrix}_{(\vec{e_x},\vec{e_y},\vec{e_z})}
$$

## 问题 4.3：说明该应力场形式的合理性，并用静态可容性求出 $g(z)$

**解答：**

- 从几何与载荷看，问题关于 $(Oxz)$、$(Oyz)$ 平面对称，且在 $x,y$ 上无限制，故有 

$$
\dfrac{\partial}{\partial x} = 0,\quad \dfrac{\partial}{\partial y} = 0
$$

- 无 $\vec{e_x}$、$\vec{e_y}$ 方向的外载，且问题对称，预期只有 $\sigma_{zz}$ 分量。

- 上述应力形式与各边界条件（尤其是轴向拉伸）相容。

由局部平衡方程： 

$$
-\mathrm{div}\,\sigma = \vec{0}
\quad\Rightarrow\quad
g'(z)=0\quad\Rightarrow\quad g(z)=\text{常数}=A
$$

 再由顶面 $z=L$ 边界条件： 

$$
\sigma(z=L)\cdot\vec{n} = \dfrac{F}{S}\vec{e_z}
\quad\Rightarrow\quad
g(L)=\dfrac{F}{S}
$$

 因此 

$$
\sigma = \dfrac{F}{S}
\begin{pmatrix}
0 & 0 & 0\\
0 & 0 & 0\\
0 & 0 & 1
\end{pmatrix}_{(\vec{e_x},\vec{e_y},\vec{e_z})}
$$

## 问题 4.4：利用本构关系求应变场 $\varepsilon$

**解答：**

由 

$$
\varepsilon = \dfrac{1+\nu}{E}\sigma - \dfrac{\nu}{E}\mathrm{Tr}(\sigma)\,I
$$

 且 $\mathrm{Tr}(\sigma)=\sigma_{zz}=F/S$，得： 

$$
\varepsilon =
\dfrac{F}{ES}
\begin{pmatrix}
-\nu & 0 & 0\\
0 & -\nu & 0\\
0 & 0 & 1
\end{pmatrix}_{(\vec{e_x},\vec{e_y},\vec{e_z})}
$$

## 问题 4.5：位移场 $\vec{u}=(Cz+D)\vec{e_z}$ 是否为本问题的解？

**解答：**

该位移场仅有 $z$ 向分量，其应变为： 

$$
\varepsilon_{zz} = \dfrac{\partial u_z}{\partial z} = C,\quad
\varepsilon_{xx}=\varepsilon_{yy}=0
$$

 而根据泊松效应，应有 

$$
\varepsilon_{xx} = \varepsilon_{yy} = -\nu\dfrac{F}{ES}\neq 0
$$

 故该位移场不能产生正确的横向压缩，应变场与前述本构结果不符，因此**不是**该问题的解。

## 问题 4.6：在什么条件下，位移场 $\vec{u}^\star = u(x)\vec{e_x} + v(y)\vec{e_y} + w(z)\vec{e_z}$ 是解？

**解答：**

没有额外的位移边界条件，故刚体运动未完全约束。 但应变必须与第 4.4 题得到的 $\varepsilon$ 一致。 由 

$$
\varepsilon_{xx} = \dfrac{\partial u}{\partial x} = -\nu\dfrac{F}{ES},\quad
\varepsilon_{yy} = \dfrac{\partial v}{\partial y} = -\nu\dfrac{F}{ES},\quad
\varepsilon_{zz} = \dfrac{\partial w}{\partial z} = \dfrac{F}{ES}
$$

 且 

$$
\varepsilon_{xy} = \dfrac{1}{2}\left(\dfrac{\partial u}{\partial y} + \dfrac{\partial v}{\partial x}\right) = 0
$$

 因此 $\vec{u}^\star$ 是解当且仅当： 

$$
\begin{cases}
\dfrac{\partial u}{\partial x} = -\dfrac{\nu F}{ES}\\[4pt]
\dfrac{\partial v}{\partial y} = -\dfrac{\nu F}{ES}\\[4pt]
\dfrac{\partial w}{\partial z} = \dfrac{F}{ES}\\[4pt]
\dfrac{\partial u}{\partial y} + \dfrac{\partial v}{\partial x} = 0
\end{cases}
$$

 另外可以叠加任意刚体运动（整体平移或转动），而不改变应变和应力。

# 练习 5 ------ 倾斜平板上的黏性流体

考虑一刚性平面 $(\Pi)$，与水平面成角度 $\alpha$。该平面以恒定速度 

$$
\vec{U} = -U\vec{e_x}
$$

 沿自身方向匀速平移，用以输运一层黏性牛顿、不可压缩且具有自重的流体。流体密度为 $\rho$，动力黏度为 $\mu$。 考虑重力体力 $\vec{g}$。假设流动为：

- 稳态（定常）；

- 层流；

- 平面流。

流体层厚度为常数 $h$。其上表面与大气接触，大气视为理想流体，压力恒为 $p_{\mathrm{atm}}$。

## 问题 5.1：给出问题假设，并写出控制该流动的方程与边界条件

**解答：**

#### 假设：

- 流体为黏性牛顿流体，动力黏度 $\mu$；

- 不可压缩：$\rho = \text{常数}$，故 $\mathrm{div}\,\vec{V}=0$；

- 自重流体：体力 $\vec{f_d} = \rho\vec{g}$；

- 定常流动：$\partial/\partial t = 0$；

- 平面流：$\vec{V} = v(x,y)\vec{e_x} + w(x,y)\vec{e_y}$；

- 层流：流线平行于固体边界，可进一步写成 $\vec{V} = v(x,y)\vec{e_x}$；

- 平面 $(\Pi)$ 以速度 $\vec{V}_p = -U\vec{e_x}$ 运动。

由 (H5)、(H6)、(H7) 可写： 

$$
\vec{V}(M) = v(x,y)\vec{e_x}
$$

#### 控制方程：

- 质量守恒（连续性方程）： 

$$
\dfrac{\partial\rho}{\partial t} + \mathrm{div}(\rho\vec{V}) = 0
    \quad\Rightarrow\quad
    \mathrm{div}\,\vec{V} = 0
$$

- 动量守恒（动量平衡 / Navier--Stokes）： 

$$
-\mathrm{div}\,\sigma + \vec{f_d} = \rho\vec{\Gamma}
    = \rho\left(\dfrac{\partial\vec{V}}{\partial t} + \nabla\vec{V}\cdot\vec{V}\right)
$$

- 牛顿流体本构关系： 

$$
\sigma = 2\mu D + \bigl[\lambda_v\mathrm{Tr}(D) - p\bigr]I
$$

 对不可压缩流体（$\mathrm{div}\,\vec{V}=0$）有 $\mathrm{Tr}(D)=0$，故： 

$$
\sigma = 2\mu D - pI,\quad
    D = \dfrac{1}{2}\bigl(\nabla\vec{V} + \nabla^T\vec{V}\bigr)
$$

将本构关系代入动量方程，得到 Navier--Stokes 方程： 

$$
\mu\Delta\vec{V} + (\lambda_v + \mu)\nabla(\mathrm{div}\,\vec{V}) - \nabla p + \rho\vec{g}
= \rho\left(\dfrac{\partial\vec{V}}{\partial t} + \nabla\vec{V}\cdot\vec{V}\right)
$$

 利用定常与不可压缩假设，式子简化。

#### 边界条件：

- 在 $y=0$：固体壁面，不渗透，黏性流体对固体表面满足粘附条件，且固体在运动： 

$$
\vec{V}(y=0) = \vec{V}_p = -U\vec{e_x}
$$

- 在 $y=h$：与大气接触，一般采用压力与切向应力条件 

$$
p(y=h) = p_{\mathrm{atm}},\qquad
    \sigma(y=h)\cdot \vec{n}(y=h) = -p_{\mathrm{atm}}\vec{n}(y=h),\quad \vec{n}(y=h)=\vec{e_y}
$$

## 问题 5.2：说明速度场与压强场可取形式

$$
\vec{V}(x,y) = v(y)\vec{e_x},\qquad p(x,y)=p(y)
$$

**解答：**

先由连续性方程： 

$$
\mathrm{div}\,\vec{V} = 0,\quad
\vec{V} = v(x,y)\vec{e_x}
\Rightarrow
\dfrac{\partial v}{\partial x} = 0
\Rightarrow
\vec{V}(M) = v(y)\vec{e_x}
$$

 关于压强，利用问题在 $x$ 方向上的均匀性（小角度假设、几何与载荷均匀），可假设： 

$$
p(x,y) = p(y)
$$

## 问题 5.3：从方程推导速度与压强的一般形式

$$
v(y) = C_1y^2 + C_2y + C_3,\qquad p(y) = C_4y + C_5
$$

**解答：**

首先计算： 

$$
\nabla\vec{V} =
\begin{pmatrix}
0 & \dfrac{\partial v}{\partial y}\\
0 & 0
\end{pmatrix}
,\quad
\nabla\vec{V}\cdot\vec{V} =
\begin{pmatrix}
0 & v_y\\
0 & 0
\end{pmatrix}
\begin{pmatrix}
v\\[2pt] 0
\end{pmatrix}
=
\begin{pmatrix}
0\\[2pt] 0
\end{pmatrix}
$$

 于是 Navier--Stokes 化简为： 

$$
\mu\Delta\vec{V} - \nabla p + \rho\vec{g} = \vec{0}
$$

 在 $(\vec{e_x},\vec{e_y})$ 基下： 

$$
\Delta\vec{V} =
\begin{pmatrix}
\dfrac{\partial^2 v}{\partial y^2}\\[4pt]
0
\end{pmatrix}
,\quad
\nabla p =
\begin{pmatrix}
0\\[2pt]
\dfrac{\partial p}{\partial y}
\end{pmatrix}
$$

 取 $\vec{g} = g(\sin\alpha\,\vec{e_x} - \cos\alpha\,\vec{e_y})$，得： 

$$
\mu
\begin{pmatrix}
v_{yy}\\[2pt]
0
\end{pmatrix}
-
\begin{pmatrix}
0\\[2pt]
p_y
\end{pmatrix}
+
\rho g
\begin{pmatrix}
\sin\alpha\\[2pt]
-\cos\alpha
\end{pmatrix}
=
\begin{pmatrix}
0\\[2pt]
0
\end{pmatrix}
$$

 即 

$$
\begin{cases}
\mu\dfrac{\partial^2 v}{\partial y^2} = -\rho g\sin\alpha\\[6pt]
\dfrac{\partial p}{\partial y} = -\rho g\cos\alpha
\end{cases}
$$

 积分两次得： 

$$
v(y) = C_1y^2 + C_2y + C_3,\quad C_1 = -\dfrac{\rho g\sin\alpha}{2\mu}
$$

 

$$
p(y) = C_4y + C_5,\quad C_4=-\rho g\cos\alpha
$$

## 问题 5.4：用边界条件完全确定速度与压强场

**解答：**

#### 在 $y=0$：

$$
\vec{V}(0) = -U\vec{e_x}
\Rightarrow
v(0) = -U
\Rightarrow
C_3 = -U
$$

#### 在 $y=h$：

需要用上表面的应力边界条件。先计算形变率张量： 

$$
\nabla\vec{V} =
\begin{pmatrix}
0 & v_y\\
0 & 0
\end{pmatrix}
,\quad
D = \dfrac{1}{2}
\begin{pmatrix}
0 & v_y\\
v_y & 0
\end{pmatrix}
$$

 应力张量： 

$$
\sigma = 2\mu D - pI =
\begin{pmatrix}
-p(y) & \mu v_y\\
\mu v_y & -p(y)
\end{pmatrix}
$$

 在 $y=h$，上表面法向 $\vec{n}=\vec{e_y}$，边界条件： 

$$
\sigma(y=h)\cdot\vec{e_y} = -p_{\mathrm{atm}}\vec{e_y}
$$

 即 

$$
\begin{pmatrix}
-p(h) & \mu v_y(h)\\
\mu v_y(h) & -p(h)
\end{pmatrix}
\begin{pmatrix}
0\\[2pt] 1
\end{pmatrix}
=
\begin{pmatrix}
\mu v_y(h)\\[2pt]
-p(h)
\end{pmatrix}
=
\begin{pmatrix}
0\\[2pt]
-p_{\mathrm{atm}}
\end{pmatrix}
$$

 得到两条件： 

$$
\mu v_y(h)=0,\quad p(h)=p_{\mathrm{atm}}
$$

 注意 

$$
v_y(y) = 2C_1y + C_2
\Rightarrow
v_y(h) = 2C_1h + C_2
$$

 代入得： 

$$
2C_1h + C_2 = 0,\quad C_4h + C_5 = p_{\mathrm{atm}}
$$

 用前述 $C_1=-\dfrac{\rho g\sin\alpha}{2\mu}$、$C_4=-\rho g\cos\alpha$，可得： 

$$
C_2 = \dfrac{\rho g h\sin\alpha}{\mu},\quad
C_5 = p_{\mathrm{atm}} + \rho g h\cos\alpha
$$

#### 最终结果：

$$
v(y) = \dfrac{\rho g\sin\alpha}{2\mu}(2hy - y^2) - U
= \dfrac{\rho g\sin\alpha}{2\mu}(2h - y)y - U
$$

 

$$
p(y) = \rho g\cos\alpha(h - y) + p_{\mathrm{atm}}
$$

## 问题 5.5：绘制速度剖面，并计算平面所能输运的最大流层厚度 $h_{\max}$

**解答：**

速度分布： 

$$
v(y) = \dfrac{\rho g\sin\alpha}{2\mu}(2h - y)y - U
$$

 是一条开口向下的抛物线整体平移（取决于 $U$）。

当平面向上输运流体时，要求在 $0\le y\le h_{\max}$ 内速度不改变符号；取界面 $y=h_{\max}$ 为速度零点： 

$$
v(h_{\max}) = 0
\Rightarrow
\dfrac{\rho g\sin\alpha}{2\mu}(2h - h_{\max})h_{\max} - U = 0
$$

 即 

$$
h_{\max}^2 - 2hh_{\max} + \dfrac{2\mu U}{\rho g\sin\alpha} = 0
$$

 其判别式： 

$$
\Delta = 4h^2 - 8\dfrac{\mu U}{\rho g\sin\alpha}
= 4\Bigl(h^2 - \dfrac{2\mu U}{\rho g\sin\alpha}\Bigr)
$$

 有实根当且仅当： 

$$
h^2 \ge \dfrac{2\mu U}{\rho g\sin\alpha}
$$

 于是 

$$
h_{\max} = h \pm \sqrt{h^2 - \dfrac{2\mu U}{\rho g\sin\alpha}}
$$

 在 $[0,h]$ 内的物理解为： 

$$
h_{\max} = h - \sqrt{h^2 - \dfrac{2\mu U}{\rho g\sin\alpha}}
$$

## 问题 5.6：求保持平面运动所需的表面力密度，并求输运最大厚度流体时的功率

**解答：**

在下壁 $y=0$，法向 $\vec{n}=-\vec{e_y}$，故向流体的表面力密度为： 

$$
\vec{T}(y=0) = \sigma(y=0)\cdot\vec{n}(y=0)
=
\begin{pmatrix}
-p(0) & \mu v_y(0)\\
\mu v_y(0) & -p(0)
\end{pmatrix}
\begin{pmatrix}
0\\[2pt] -1
\end{pmatrix}
=
\begin{pmatrix}
-\mu v_y(0)\\[2pt]
p(0)
\end{pmatrix}
$$

 有 

$$
v_y(y) = 2C_1y + C_2,\quad
v_y(0) = C_2 = \dfrac{\rho g h\sin\alpha}{\mu}
$$

 

$$
p(0) = \rho g h\cos\alpha + p_{\mathrm{atm}}
$$

 于是 

$$
\vec{T}(y=0) =
\begin{pmatrix}
-\rho g h\sin\alpha\\[4pt]
\rho g h\cos\alpha + p_{\mathrm{atm}}
\end{pmatrix}
$$

 其中 $x$ 向分量 $T_x = -\rho g h\sin\alpha$ 表示流体对平面的阻力（沿 $-\vec{e_x}$），需要外力克服。

设 $S$ 为接触面积，则平面对流体的总功率： 

$$
P = \int_S \vec{T}(y=0)\cdot\vec{V}(y=0)\,dS
= S\,\vec{T}(0)\cdot(-U\vec{e_x})
= \rho g h\sin\alpha\,U\,S
$$

注意：此表达式与黏度 $\mu$ 无关。

若要输运**整层**流体，即 $h_{\max}=h$，则需： 

$$
h - \sqrt{h^2 - \dfrac{2\mu U}{\rho g\sin\alpha}} = h
\Rightarrow
\dfrac{2\mu U}{\rho g\sin\alpha} = h^2
\Rightarrow
U = \dfrac{\rho g h^2\sin\alpha}{2\mu}
$$

 代入功率： 

$$
P(h_{\max}=h) = (\rho g h\sin\alpha)^2\,\dfrac{Sh}{2\mu}
$$

#### 备注：

1.  一般情形下，维持给定功率的条件下，**可输运厚度**与黏度有关；

2.  若要求输运的流体厚度给定，则所需功率取决于黏度；

3.  黏度越大，达到输运整层流体所需的速度 $U$ 越小；

4.  密度越大，所需功率越大（且 $U$ 也更大）。

# 附录 ------ 笛卡尔坐标下的常用算子公式

在直角坐标系 $(O,\vec{e_x},\vec{e_y},\vec{e_z})$ 中： 

$$
\overrightarrow{OM} = x\vec{e_x} + y\vec{e_y} + z\vec{e_z}
$$

 

$$
\nabla = \vec{e_x}\dfrac{\partial}{\partial x}
+ \vec{e_y}\dfrac{\partial}{\partial y}
+ \vec{e_z}\dfrac{\partial}{\partial z}
$$

#### 标量场 $f(x,y,z)$：

$$
\nabla f = \dfrac{\partial f}{\partial x}\vec{e_x}
+ \dfrac{\partial f}{\partial y}\vec{e_y}
+ \dfrac{\partial f}{\partial z}\vec{e_z}
$$

 

$$
\Delta f = \dfrac{\partial^2 f}{\partial x^2}
+ \dfrac{\partial^2 f}{\partial y^2}
+ \dfrac{\partial^2 f}{\partial z^2}
$$

#### 向量场 $\vec{U}(x,y,z) = U_x\vec{e_x} + U_y\vec{e_y} + U_z\vec{e_z}$：

$$
\nabla\vec{U} =
\begin{pmatrix}
\dfrac{\partial U_x}{\partial x} & \dfrac{\partial U_x}{\partial y} & \dfrac{\partial U_x}{\partial z}\\[4pt]
\dfrac{\partial U_y}{\partial x} & \dfrac{\partial U_y}{\partial y} & \dfrac{\partial U_y}{\partial z}\\[4pt]
\dfrac{\partial U_z}{\partial x} & \dfrac{\partial U_z}{\partial y} & \dfrac{\partial U_z}{\partial z}
\end{pmatrix}_{(\vec{e_x},\vec{e_y},\vec{e_z})}
$$

$$
\mathrm{div}\,\vec{U} =
\dfrac{\partial U_x}{\partial x}
+ \dfrac{\partial U_y}{\partial y}
+ \dfrac{\partial U_z}{\partial z}
$$

$$
\mathrm{rot}\,\vec{U} =
\begin{pmatrix}
\dfrac{\partial U_z}{\partial y} - \dfrac{\partial U_y}{\partial z}\\[4pt]
\dfrac{\partial U_x}{\partial z} - \dfrac{\partial U_z}{\partial x}\\[4pt]
\dfrac{\partial U_y}{\partial x} - \dfrac{\partial U_x}{\partial y}
\end{pmatrix}_{(\vec{e_x},\vec{e_y},\vec{e_z})}
$$

$$
\Delta\vec{U} =
\Delta U_x\,\vec{e_x}
+ \Delta U_y\,\vec{e_y}
+ \Delta U_z\,\vec{e_z}
$$

#### 对称二阶张量场

$$
T(x,y,z) =
\begin{pmatrix}
T_{xx} & T_{xy} & T_{xz}\\
T_{xy} & T_{yy} & T_{yz}\\
T_{xz} & T_{yz} & T_{zz}
\end{pmatrix}_{(\vec{e_x},\vec{e_y},\vec{e_z})}
$$

 其散度为： 

$$
\mathrm{div}\,T =
\left(
\dfrac{\partial T_{xx}}{\partial x}
+ \dfrac{\partial T_{xy}}{\partial y}
+ \dfrac{\partial T_{xz}}{\partial z}
\right)\vec{e_x}
+
\left(
\dfrac{\partial T_{xy}}{\partial x}
+ \dfrac{\partial T_{yy}}{\partial y}
+ \dfrac{\partial T_{yz}}{\partial z}
\right)\vec{e_y}
+
\left(
\dfrac{\partial T_{xz}}{\partial x}
+ \dfrac{\partial T_{yz}}{\partial y}
+ \dfrac{\partial T_{zz}}{\partial z}
\right)\vec{e_z}
$$

