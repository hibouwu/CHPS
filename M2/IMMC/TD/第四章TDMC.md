# 练习 1 ------ 受拉梁

设一根梁承受自重并放置在地面上（见图 1.1）。梁的高度为 $h$，截面为正方形 $S$。材料均匀，密度为 $\rho$。

工作坐标系为 $(O, \bm{e}_1, \bm{e}_2, \bm{e}_3)$，其中 $O$ 是梁与地面接触轴上的一点。竖直方向定义为 $\bm{e}_3$。梁上任意一点 $M$ 的位置向量为： 

$$
\overrightarrow{OM} = x_1 \bm{e}_1 + x_2 \bm{e}_2 + x_3 \bm{e}_3 \tag{1.1}
$$

梁的自重由体力密度 $\bm{f} = -\rho g \bm{e}_3$ 表示，其中 $g$ 为重力加速度。假设任意点 $M$ 处的应力张量为：

$$
\bm{\sigma} =
\begin{bmatrix}
0 & 0 & 0 \\
0 & 0 & 0 \\
0 & 0 & a + bx_3
\end{bmatrix}_{(\bm{e}_1,\bm{e}_2,\bm{e}_3)}
\tag{1.2}
$$

 其中 $a$ 与 $b$ 为常数。

## 问题 1.1

利用局部平衡方程，确定常数 $b$ 的条件，使得固体处于静力平衡。并使用静力学基本原理 (PFS) 重新得到该结果。

### 解答 1.1

局部平衡方程（或内部平衡）写作： 

$$
\text{div}\,\bm{\sigma} + \bm{f}_v = \bm{0} \quad (\text{静态})
$$

 即 

$$
\begin{pmatrix}
\sigma_{11,1} + \sigma_{12,2} + \sigma_{13,3} \\
\sigma_{21,1} + \sigma_{22,2} + \sigma_{23,3} \\
\sigma_{31,1} + \sigma_{32,2} + \sigma_{33,3}
\end{pmatrix}
+
\begin{pmatrix}
0 \\ 0 \\ -\rho g
\end{pmatrix}
= \bm{0}
\quad \forall M \in \Omega
\tag{*1.1}
$$

代入应力张量得： 

$$
\begin{pmatrix}
0 \\ 0 \\ b
\end{pmatrix}
+
\begin{pmatrix}
0 \\ 0 \\ -\rho g
\end{pmatrix}
=
\begin{pmatrix}
0 \\ 0 \\ 0
\end{pmatrix}
\Rightarrow
\begin{cases}
0 = 0\\
0 = 0\\
b - \rho g = 0
\end{cases}
\Rightarrow b = \rho g
\tag{*1.2}
$$

现在使用静力学基本原理（PFS）验证： 对体积 $\Omega$，体力与表面力平衡条件为： 

$$
\int_{\Omega} \bm{f}_v(M)\, dV
+
\int_{\partial \Omega} \bm{T}(M, \bm{n}(M))\, dS
= \bm{0}
\tag{*1.3}
$$

 其中 $\bm{T}(M,\bm{n}(M)) = \bm{\sigma}(M)\cdot\bm{n}(M)$。

代入具体形式： 

$$
\int_{\Omega} (-\rho g \bm{e}_3) \, dV
+
\int_{S_3^+} \bm{\sigma}(M)\cdot\bm{e}_3\, dS
+
\int_{S_3^-} \bm{\sigma}(M)\cdot(-\bm{e}_3)\, dS
= \bm{0}
\tag{*1.5}
$$

即： 

$$
-\rho g S h \bm{e}_3 + (a + bh)S\bm{e}_3 - aS\bm{e}_3 = \bm{0}
\Rightarrow -\rho g h + bh = 0 \Rightarrow b = \rho g
\tag{*1.6}
$$

## 问题 1.2

写出梁各表面的边界条件。

### 解答 1.2

各面的边界条件如下（设地面接触压强为 $p$）：

$$
\begin{aligned}
&\bm{T}(M) = \bm{\sigma}(M)\cdot\bm{e}_1 = \bm{0} \quad \forall M \in S_1^+ \text{（自由表面）} \tag{*1.7}\\
&\bm{T}(M) = \bm{\sigma}(M)\cdot(-\bm{e}_1) = \bm{0} \quad \forall M \in S_1^- \text{（自由表面）} \tag{*1.8}\\
&\bm{T}(M) = \bm{\sigma}(M)\cdot\bm{e}_2 = \bm{0} \quad \forall M \in S_2^+ \text{（自由表面）} \tag{*1.9}\\
&\bm{T}(M) = \bm{\sigma}(M)\cdot(-\bm{e}_2) = \bm{0} \quad \forall M \in S_2^- \text{（自由表面）} \tag{*1.10}\\
&\bm{T}(M) = \bm{\sigma}(M)\cdot\bm{e}_3 = \bm{0} \quad \forall M \in S_3^+ \text{（自由表面）} \tag{*1.11}\\
&\bm{T}(M) = \bm{\sigma}(M)\cdot(-\bm{e}_3) = -p(-\bm{e}_3) \quad \forall M \in S_3^- \text{（地面接触压力）} \tag{*1.12}
\end{aligned}
$$

## 问题 1.3

由此推导出 $a$ 与接触压力 $p$ 的表达式。

### 解答 1.3

在上表面 $S_3^+$（$x_3 = h$）处： 

$$
\bm{\sigma}(x_3 = h)\cdot\bm{e}_3 = \bm{0}
\Rightarrow a + bh = 0
$$

 代入 $b = \rho g$： 

$$
a = -\rho g h
$$

在下表面 $S_3^-$（$x_3 = 0$）处： 

$$
\bm{\sigma}(x_3 = 0)\cdot(-\bm{e}_3) = -p(-\bm{e}_3)
\Rightarrow -a = p
$$

 代入上式： 

$$
p = \rho g h
$$

# 练习 2 ------ 边界条件

设一个空心球体，内半径为 $r_1$，外半径为 $r_2$。球体内侧承受内压 $p_1$，外侧承受外压 $p_2$。

在以球坐标 $(r, \theta, \varphi)$ 为基础的局部坐标系中，应力张量 $\bm{\sigma}$ 已知形式如下： 

$$
\bm{\sigma} =
\begin{pmatrix}
\sigma_r & 0 & 0 \\
0 & \sigma_\theta & 0 \\
0 & 0 & \sigma_\varphi
\end{pmatrix}
\quad \text{其中}\quad
\sigma_r = A - \frac{2B}{r^3}, \quad
\sigma_\theta = \sigma_\varphi = A + \frac{B}{r^3},
$$

 其中 $A$ 和 $B$ 为常数。

## 问题 2.1

确定满足边界条件的常数 $A$ 和 $B$ 的数值。

### 解答 2.1

回顾：若在连续介质边界 $\partial \Omega_T$ 上（法向为 $\bm{n}$）给定一个表面力（面力）分布 $\bm{T}_d$，则边界条件写作： 

$$
\bm{\sigma}(M) \cdot \bm{n}(M) = \bm{T}_d(M), \quad \forall M \in \partial \Omega_T
$$

 或简写为： 

$$
\bm{\sigma} \cdot \bm{n} = \bm{T}_d
$$

若该分布为压力 $p$，则条件为： 

$$
\bm{\sigma}(M) \cdot \bm{n}(M) = \bm{T}_d(M) = -p(M)\bm{n}(M), \quad \forall M \in \partial \Omega_T
$$

 或简写为： 

$$
\bm{\sigma} \cdot \bm{n} = \bm{T}_d = -p\bm{n}
$$

在此，我们有两个未知常数（标量）$A$ 和 $B$，因此需要两条独立的标量方程来求解。 该区域有两个边界面（内壁与外壁），且在每个边界面上给出了力边界条件。因此可以求出 $A$ 与 $B$。

### 边界条件表达

#### (1) 内壁 $r = r_1$：

内侧压力为 $p_1$，法向外指（相对于介质）为 $\bm{n}(r_1) = -\bm{e}_r$， 因此： 

$$
\bm{\sigma}(r_1) \cdot \bm{n}(r_1) = -p_1 \bm{n}(r_1)
\Rightarrow
\bm{\sigma}(r_1) \cdot (-\bm{e}_r) = p_1 \bm{e}_r
$$

从径向分量得到： 

$$
- \sigma_r(r_1) = p_1
\Rightarrow -\left(A - \frac{2B}{r_1^3}\right) = p_1
\Rightarrow A - \frac{2B}{r_1^3} = -p_1
\tag{*2.1}
$$

#### (2) 外壁 $r = r_2$：

外侧压力为 $p_2$，法向外指 $\bm{n}(r_2) = \bm{e}_r$， 因此： 

$$
\bm{\sigma}(r_2) \cdot \bm{n}(r_2) = -p_2 \bm{n}(r_2)
\Rightarrow
\bm{\sigma}(r_2)\cdot \bm{e}_r = -p_2 \bm{e}_r
$$

径向分量为： 

$$
A - \frac{2B}{r_2^3} = -p_2
\tag{*2.2}
$$

### 联立求解常数 $A$ 与 $B$

由式（\*2.1）与（\*2.2）相减： 

$$
-\frac{2B}{r_1^3} + \frac{2B}{r_2^3} = -p_1 + p_2
\Rightarrow
B = \frac{p_1 - p_2}{2} \,
\frac{(r_1r_2)^3}{r_2^3 - r_1^3}
\tag{*2.3}
$$

将（\*2.3）代入（\*2.1）： 

$$
A - \frac{2B}{r_1^3} = -p_1
\Rightarrow
A = \frac{p_1 r_1^3 - p_2 r_2^3}{r_2^3 - r_1^3}
\tag{*2.4}
$$

### 结论与符号分析

由以上结果可知：

- 常数 $B$ 的符号与 $p_1 - p_2$ 相同；

- 若 $r_1$ 与 $r_2$ 大小相近且 $p_2 > p_1$，则 $A$、$B$ 都为正；

- 若 $r_1$ 与 $r_2$ 大小相近且 $p_2 \ll p_1$，则 $A$、$B$ 都为负。
