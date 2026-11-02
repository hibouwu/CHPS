**IMMC · TD3：内力与应力（详细推导）**

# 练习 1 ------ 简单的应力计算

题面与练习 2 见 [TD3](中文版/TD3_应力_2026-2027.md)；这里展开练习 1 与 3。

**Calculs simples sur les contraintes.** Dans la base orthonormée $(\mathbf e_1,\mathbf e_2,\mathbf e_3)$, les composantes supérieures du tenseur des contraintes au point $A$ sont données ci-dessous, en MPa. Le tenseur de Cauchy est symétrique dans le modèle considéré.

设 $(\vec{e}_1, \vec{e}_2, \vec{e}_3)$ 为正交基，在此基下，某可变形体在点 $A$ 的应力张量为：

$$
\boldsymbol{\sigma}(A) =
\begin{pmatrix}
2 & 0 & 3 \\
\cdot & 1 & 0 \\
3 & 0 & 0
\end{pmatrix}_{(\vec{e}_1, \vec{e}_2, \vec{e}_3)}
$$

 单位为 MPa。

### 问题 1.1：补全应力张量的表达式

Compléter l’expression du tenseur des contraintes.

由于应力张量是对称的，因此：

$$
\boldsymbol{\sigma}(A) =
\begin{pmatrix}
2 & 0 & 3 \\
0 & 1 & 0 \\
3 & 0 & 0
\end{pmatrix}_{(\vec{e}_1, \vec{e}_2, \vec{e}_3)}
\tag{1.1}
$$

---

### 问题 1.2：计算在不同法向下的应力向量

Calculer le vecteur contrainte $\mathbf T$ dans la base ($\mathbf e_1$ , $\mathbf e_2$ , $\mathbf e_3$ ) pour les facettes centrées en A de normales $\mathbf e_1$ , −$\mathbf e_1$ , et $\mathbf e_2$ .

在法向分别为 $\vec{e}_1$, $-\vec{e}_1$, $\vec{e}_2$ 的三个面上，求应力向量 $\vec{T}$。

根据定义：

$$
\vec{T}(A, \vec{n}) = \boldsymbol{\sigma}(A) \cdot \vec{n}
\tag{1.2}
$$

于是：

$$
\vec{T}(A, \vec{e}_1)
=
\begin{pmatrix}
2 & 0 & 3 \\
0 & 1 & 0 \\
3 & 0 & 0
\end{pmatrix}
\begin{pmatrix}
1 \\ 0 \\ 0
\end{pmatrix}
=
\begin{pmatrix}
2 \\ 0 \\ 3
\end{pmatrix}
\tag{1.3}
$$

$$
\vec{T}(A, -\vec{e}_1)
=
\begin{pmatrix}
2 & 0 & 3 \\
0 & 1 & 0 \\
3 & 0 & 0
\end{pmatrix}
\begin{pmatrix}
-1 \\ 0 \\ 0
\end{pmatrix}
=
\begin{pmatrix}
-2 \\ 0 \\ -3
\end{pmatrix}
\tag{1.4}
$$

$$
\vec{T}(A, \vec{e}_2)
=
\begin{pmatrix}
2 & 0 & 3 \\
0 & 1 & 0 \\
3 & 0 & 0
\end{pmatrix}
\begin{pmatrix}
0 \\ 1 \\ 0
\end{pmatrix}
=
\begin{pmatrix}
0 \\ 1 \\ 0
\end{pmatrix}
= \vec{e}_2
\tag{1.5}
$$

---

### 问题 1.3：法向和切向分量的方向

Représenter graphiquement les composantes du vecteur contrainte pour la facette de normale $\mathbf e_1$ et celle de normale $\mathbf e_2$ .

法向为 $\vec e_1$ 的面上，从作用点分别沿 $+\vec e_1$ 画法向分量 2 MPa、沿 $+\vec e_3$ 画切向分量 3 MPa；合成向量为 $(2,0,3)$ MPa。法向为 $\vec e_2$ 的面上，仅沿 $+\vec e_2$ 画 1 MPa 的法向分量，切向分量为零。

---

### 问题 1.4：求主应力及主基下的张量表达式

Calculer les contraintes principales de $\boldsymbol\sigma$ en $A$ et donner le tenseur des contraintes dans la base principale.

主应力是应力算子的特征值，主方向是对应的特征向量。 求解特征方程：

$$
\begin{aligned}
\det(\boldsymbol{\sigma} - \lambda \mathbf{I}) &= 0 \\
\Rightarrow
\begin{vmatrix}
2 - \lambda & 0 & 3 \\
0 & 1 - \lambda & 0 \\
3 & 0 & -\lambda
\end{vmatrix} &= 0
\end{aligned}
$$

得到：

$$
(1 - \lambda) [ (2 - \lambda)(-\lambda) - 9 ] = 0
\Rightarrow
(1 - \lambda)(\lambda^2 - 2\lambda - 9) = 0
\tag{1.6}
$$

因此：

$$
\lambda_1 = 1
\quad\text{且}\quad
\Delta = (-2)^2 - 4(1)(-9) = 40
\Rightarrow
\lambda_{2,3} = 1 \pm \sqrt{10}
\tag{1.7}
$$

按升序排列主应力：

$$
\sigma_1 = 1 - \sqrt{10}, \quad
\sigma_2 = 1, \quad
\sigma_3 = 1 + \sqrt{10}
$$

主基下的应力张量为：

$$
\boldsymbol{\sigma} =
\begin{pmatrix}
1 - \sqrt{10} & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1 + \sqrt{10}
\end{pmatrix}_{(\vec{N}_1,\vec{N}_2,\vec{N}_3)}
\tag{1.8}
$$

应力张量的迹在任意基下保持不变，此处为 3 MPa。

---

### 问题 1.5：求 von Mises 等效应力

Déterminer au point $A$ la contrainte équivalente de von Mises $\sigma_{VM}=\sqrt{\frac32\operatorname{tr}(\boldsymbol\sigma^D\boldsymbol\sigma^D)}$.

定义：

$$
\sigma_{VM} =
\sqrt{\frac{3}{2} \, \text{Tr}(\boldsymbol{\sigma}_D \boldsymbol{\sigma}_D)}
= \sqrt{\frac{3}{2} \, \boldsymbol{\sigma}_D : \boldsymbol{\sigma}_D}
\tag{1.9}
$$

以下计算在**主方向基底** 中进行；偏张量在原基底中一般不是对角矩阵。主基中的偏张量为：

$$
\boldsymbol{\sigma}_D
= \boldsymbol{\sigma} - \frac{\text{Tr}(\boldsymbol{\sigma})}{3} \mathbf{I}
=
\begin{pmatrix}
1 - \sqrt{10} & 0 & 0 \\
0 & 1 & 0 \\
0 & 0 & 1 + \sqrt{10}
\end{pmatrix}
- \mathbf{I}
=
\begin{pmatrix}
-\sqrt{10} & 0 & 0 \\
0 & 0 & 0 \\
0 & 0 & \sqrt{10}
\end{pmatrix}
\tag{1.10}
$$

于是：

$$
\sigma_{VM} =
\sqrt{\frac{3}{2}(10 + 10)} = \sqrt{30}\ \text{MPa}
\tag{1.11}
$$

---

# 练习 3 ------ 双轴拉伸试样

**Traction biaxiale.** La zone utile présente un état de contrainte plan diagonal, de composantes principales $\sigma_1,\sigma_2,0$. La normale de la facette tourne dans le plan $(\mathbf e_1,\mathbf e_2)$ ; on représente la contrainte tangentielle en fonction de la contrainte normale.

设双轴拉伸试样，其有效区域的平面应力状态为：

$$
\boldsymbol{\sigma} =
\begin{pmatrix}
\sigma_1 & 0 & 0 \\
0 & \sigma_2 & 0 \\
0 & 0 & 0
\end{pmatrix}_{(\vec{e}_1, \vec{e}_2, \vec{e}_3)}
$$

### 问题 3.1：求任意法向的应力向量

Soit une facette de normale n du plan ($\mathbf e_1$ , $\mathbf e_2$ ) et M un point de cette facette, exprimer le vecteur contrainte $\mathbf T$ (M, n).

应力向量定义为：

$$
\vec{T}(M, \vec{n}) = \boldsymbol{\sigma}(M) \cdot \vec{n}
\tag{3.1}
$$

若

$$
\vec{n} = n_1 \vec{e}_1 + n_2 \vec{e}_2
\tag{3.2}
$$

 则：

$$
\vec{T}(M, \vec{n}) =
\begin{pmatrix}
\sigma_1 n_1 \\
\sigma_2 n_2 \\
0
\end{pmatrix}
\tag{3.3}
$$

---

### 问题 3.2：求应力轨迹（Mohr 圆）

Soit α l’angle ($\mathbf e_1$ , n). Tracer le lieu des contraintes T (M, n) lorsque la facette réalise un tour complet autour de M (soit α allant de 0 à 2π), dans un repère où les axes horizontal et vertical représentent respectivement l’amplitude de la contrainte normale et l’amplitude de la contrainte tangentielle.

设 $\alpha$ 为 $(\vec{e}_1, \vec{n})$ 的夹角。

应力向量分解为法向与切向两部分：

$$
\vec{T} = \vec{T}_n + \vec{T}_t = T_n \vec{n} + T_t \vec{t}
\tag{3.4}
$$

法向应力：

$$
T_n = \vec{T} \cdot \vec{n}
\tag{3.5}
$$

切向应力：

$$
\vec{T}_t = \vec{T} - T_n \vec{n}
= \boldsymbol{\sigma}\vec{n} - (\vec{n}^T \boldsymbol{\sigma} \vec{n})\vec{n}
\tag{3.6}
$$

在平面 $(\vec{e}_1, \vec{e}_2)$ 中：

$$
\vec{n} =
\begin{pmatrix}
\cos\alpha \\ \sin\alpha \\ 0
\end{pmatrix},
\quad
\vec{t} =
\begin{pmatrix}
-\sin\alpha \\ \cos\alpha \\ 0
\end{pmatrix}
\tag{3.7}
$$

于是：

$$
\begin{aligned}
\vec{T}(M, \vec{n}) &=
\begin{pmatrix}
\sigma_1 \cos\alpha \\ \sigma_2 \sin\alpha \\ 0
\end{pmatrix}
\tag{3.8}
\end{aligned}
$$

$$
\begin{aligned}
T_n &= \vec{T}\cdot\vec{n}
= \sigma_1 \cos^2\alpha + \sigma_2 \sin^2\alpha
\tag{3.9}
\end{aligned}
$$

$$
\begin{aligned}
T_t &= \vec{T}\cdot\vec{t}
= -\sigma_1 \cos\alpha \sin\alpha + \sigma_2 \cos\alpha \sin\alpha
= (\sigma_2 - \sigma_1)\cos\alpha\sin\alpha
\tag{3.10}
\end{aligned}
$$

利用三角恒等式：

$$
\cos^2\alpha = \frac{1+\cos2\alpha}{2}, \quad
\sin^2\alpha = \frac{1-\cos2\alpha}{2}, \quad
\cos\alpha\sin\alpha = \frac{\sin2\alpha}{2}
$$

得：

$$
\begin{aligned}
T_n &= \frac{\sigma_1+\sigma_2}{2} + \frac{\sigma_1 - \sigma_2}{2}\cos2\alpha
\tag{3.11}
\end{aligned}
$$

$$
\begin{aligned}
T_t &= -\frac{\sigma_1 - \sigma_2}{2}\sin2\alpha
\tag{3.12}
\end{aligned}
$$

由此可写为圆的参数方程：

$$
(T_n - \frac{\sigma_1+\sigma_2}{2})^2 + T_t^2 =
\left(\frac{\sigma_1 - \sigma_2}{2}\right)^2
\tag{3.13}
$$

即在 $(T_n, T_t)$ 平面上，为一个半径

$$
R = \frac{|\sigma_1 - \sigma_2|}{2}
$$

 、圆心

$$
C = \left(\frac{\sigma_1+\sigma_2}{2}, 0\right)
$$

 的圆（即 Mohr 圆）。
