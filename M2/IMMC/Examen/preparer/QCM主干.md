# QCM 主干

## 主干 1 · 欧拉与拉格朗日描述

- **(A)** $\vec V(t,\vec M_0)=AtX_1\vec e_2$　拉格朗日
- **(B)** $\vec\gamma(t,\vec M)=A(x_1\vec e_1+x_2\vec e_2)$　欧拉
- **(C)** $\vec u(t,\vec M_0)=BX_2\vec e_1$　拉格朗日
- **(D)** $\rho(t,x_1,x_2)=C(x_1^2+x_2^2)$　欧拉

## 主干 2 · Taux de déformation $\mathbb D$ et taux de rotation $\boldsymbol\Omega$ · 变形率 D 与旋转率 Ω

### 1. L'idée en une phrase · 一句话

Le gradient des vitesses se coupe en deux : $\overrightarrow{\operatorname{grad}}\vec V=\mathbb D+\boldsymbol\Omega$, avec **$\mathbb D$ (partie symétrique) = vitesse de déformation** et **$\boldsymbol\Omega$ (partie antisymétrique) = vitesse de rotation locale**, tous deux en $\mathrm s^{-1}$. 速度梯度拆成两块：**对称部分 $\mathbb D$ 管"变形有多快"**，**反对称部分 $\boldsymbol\Omega$ 管"局部转得多快"**，单位都是 $\mathrm s^{-1}$。

直觉：在流动的水面上放一小块方形的软泡沫。它在一瞬间可能做三件事：整体漂走（平移）、原地打转（转动）、被拉长或被压歪（变形）。平移不进速度梯度；$\boldsymbol\Omega$ 只记"打转"；$\mathbb D$ 只记"拉长、压扁、方角变歪"。所以判断"有没有变形"只看 $\mathbb D$，判断"有没有旋转"只看 $\boldsymbol\Omega$。泡沫转得再快，只要形状不变，$\mathbb D$ 就是零。

### 2. Formules · 公式

**速度梯度**　给定欧拉速度 $\vec V=(V_1,V_2,V_3)$，固定时间 $t$，记 $v_{ij}=\dfrac{\partial V_i}{\partial x_j}$。第 $i$ 行取速度分量 $V_i$，第 $j$ 列对当前位置 $x_j$ 求导。只含 $t$ 的项对空间求导得零。

$$
L=\overrightarrow{\operatorname{grad}}\vec V=
\begin{pmatrix}
v_{11} & v_{12} & v_{13}\\
v_{21} & v_{22} & v_{23}\\
v_{31} & v_{32} & v_{33}
\end{pmatrix}.
$$

- 把速度梯度拆成两部分，$L=\mathbb D+\boldsymbol\Omega$。把 $L$ 的行列互换，就得到下面用的转置 $L^{\mathsf T}$。
    - **变形率** $\mathbb D=\tfrac12(L+L^{\mathsf T})$。对角线两侧对应的数**相加再除以 2**，得到对称矩阵。看 $\mathbb D$ 就能判断这一瞬间有没有变形。
    - **旋转率** $\boldsymbol\Omega=\tfrac12(L-L^{\mathsf T})$。同样两个数**相减再除以 2**，得到反对称矩阵，对角线全是零。看 $\boldsymbol\Omega$ 就能判断这一瞬间有没有局部转动。
- **散度** $\operatorname{div}\vec V=v_{11}+v_{22}+v_{33}=\operatorname{tr}\mathbb D$。从矩阵左上到右下，把主对角线上的三个数相加。散度处处为零，对应不可压缩运动。
- **旋度** $\overrightarrow{\operatorname{rot}}\vec V=(v_{32}-v_{23},\,v_{13}-v_{31},\,v_{21}-v_{12})$。对于 $x_1x_2$ 平面内的二维速度场，前两个分量为零；第三分量看左上角的 $2\times2$ 方块，用**左下 $v_{21}$ 减右上 $v_{12}$**。
    - **角速度向量** $\vec\omega=\tfrac12\overrightarrow{\operatorname{rot}}\vec V$。旋度为零和旋转率矩阵 $\boldsymbol\Omega$ 为零都表示无旋。
- **单位**　以上各量都是速度除以长度，单位为 $\mathrm{s}^{-1}$。$\mathbb F$、$J$、$\mathbb C$、$\mathbb E$、$\boldsymbol\varepsilon$ 都无量纲。

和前面主干的联系：$J$ 沿轨迹满足 $\dfrac{\mathrm dJ}{\mathrm dt}=J\operatorname{div}\vec V$，所以"任何时刻 $\operatorname{div}\vec V=0$"与"$J=1$"（前提概念 D）是同一件事。$\boldsymbol\varepsilon$（前提概念 F）是累计的变形、无量纲；$\mathbb D$ 是这一瞬间的变形速度、单位 $\mathrm s^{-1}$。

四个性质：

| 性质 | 判断 | 结论 |比如
|---|---|---|
| stationnaire · 稳态 | 欧拉场不含 $t$ | 是 |
| incompressible · 不可压缩 | $\operatorname{div}\vec V=\operatorname{tr}\mathbb D=0$ | 是 |
| irrotationnel · 无旋 | $\boldsymbol\Omega\ne\mathbb O$（$\overrightarrow{\operatorname{rot}}\vec V=-k\vec e_3$） | 否，有旋 |
| corps rigide · 刚体 | $\mathbb D\ne\mathbb O$ | 否，有变形 |

对照一下刚体转动 $\vec V=\omega(-x_2\vec e_1+x_1\vec e_2)$：梯度 $\begin{pmatrix}0&-\omega&0\\\omega&0&0\\0&0&0\end{pmatrix}$ 本身就反对称，所以 $\mathbb D=\mathbb O$、$\boldsymbol\Omega$ 就是梯度本身。它有旋，却没有任何变形。

### 3. Règle de reconnaissance · 判别规则（表 QA 在本节末尾）

**先算 $\overrightarrow{\operatorname{grad}}\vec V$，再按下表逐项判断，每项都只看一个量。**

| 性质 | 判据 | 例：简单剪切 | 例：刚体转动 |
|---|---|---|---|
| stationnaire · 稳态 | 欧拉场不显含 $t$（前提概念 A 详讲） | 是 | 是 |
| incompressible · 不可压缩 | $\operatorname{div}\vec V=\operatorname{tr}\mathbb D=0$ ⇔ $J=\det\mathbb F=1$ | 是 | 是 |
| irrotationnel · 无旋 | $\boldsymbol\Omega=\mathbb O$ ⇔ $\overrightarrow{\operatorname{rot}}\vec V=\vec0$ ⇔ 梯度对称 | 否 | 否 |
| corps rigide · 刚体 | 任何时刻 $\mathbb D=\mathbb O$（⇔ $\mathbb E=\mathbb O$） | 否 | 是 |

**"必然有变形"：拿本节末尾表 QA 的刚体转动（或平移）去试，凡是刚体运动也能满足的条件都不选。**

| 必然有变形 | 不一定有变形（刚体转动或平移就满足） |
|---|---|
| $\mathbb C\ne\mathbb I$、$\mathbb E\ne\mathbb O$、$\mathbb E=\mathbb I$、$\boldsymbol\varepsilon\ne\mathbb O$（HPP） | $\mathbb F\ne\mathbb I$、$\vec u\ne\vec0$、$\vec V\ne\vec0$ |
| $\mathbb D\ne\mathbb O$、$\operatorname{div}\vec V\ne0$、$J\ne1$ | $\boldsymbol\Omega\ne\mathbb O$、$\overrightarrow{\operatorname{rot}}\vec V\ne\vec0$、梯度不对称、$\mathbb E\ne\mathbb I$ |

Pièges · 陷阱：

1. **有旋不等于刚体。** 简单剪切 $\boldsymbol\Omega\ne\mathbb O$，但 $\mathbb D\ne\mathbb O$，有变形；反过来，刚体转动也是有旋的。"有没有旋"和"是不是刚体"是两个独立的问题，分别看 $\boldsymbol\Omega$ 和 $\mathbb D$。
2. **$\boldsymbol\Omega\ne\mathbb O$ 不意味着有变形。** 刚体转动 $\boldsymbol\Omega\ne\mathbb O$、$\mathbb D=\mathbb O$。"$\overrightarrow{\operatorname{rot}}\vec V\ne\vec0$""梯度不对称"说的都是 $\boldsymbol\Omega\ne\mathbb O$，同样不保证有变形。
3. **$\mathbb F\ne\mathbb I$、$\vec u\ne\vec0$ 不意味着有变形。** 刚体转动 $\mathbb F=\mathbb Q\ne\mathbb I$，平移 $\vec u=\vec c\ne\vec0$，都没有变形；$\vec V\ne\vec0$ 也一样。
4. **$\mathbb E\ne\mathbb I$ 不保证有变形，$\mathbb E=\mathbb I$ 保证有变形。** 不变形时 $\mathbb E=\mathbb O$，照样满足 $\mathbb E\ne\mathbb I$；而 $\mathbb E=\mathbb I$ 说明 $\mathbb E\ne\mathbb O$。比较的对象是 $\mathbb O$，不是 $\mathbb I$；$\mathbb C$、$\mathbb F$ 才和 $\mathbb I$ 比。
5. **$\operatorname{div}$ 只对同编号坐标求导。** $V_2=\gamma t\,x_1$ 含 $x_1$，但 $\partial V_2/\partial x_2=0$，散度仍是 0。别把所有偏导都加起来。
6. **不可压缩的特例不能当作定义。** $\overrightarrow{\operatorname{grad}}\vec V=\mathbb O$、$\vec V=\vec0$ 只是特例；$\det\mathbb F=0$ 根本不可能（$\det\mathbb F>0$）。
7. **不可压缩不要求密度处处相等。** 它只要求每个粒子沿轨迹密度不变（$\mathrm d\rho/\mathrm dt=0$）；初始密度不均匀，就一直不均匀。
8. **$\mathbb D$ 只在某一时刻为零，不是刚体运动。** 刚体要求任何时刻 $\mathbb D=\mathbb O$。
9. **对称化后非对角元要除以 2。** 简单剪切的 $D_{12}=k/2$，不是 $k$。
10. **单位：$\mathbb D$、$\boldsymbol\Omega$、$\overrightarrow{\operatorname{grad}}\vec V$、$\operatorname{div}\vec V$ 是 $\mathrm s^{-1}$。** 名字里带 taux（率）的就多一个时间倒数；$\mathbb F$、$\mathbb E$、$\mathbb C$、$J$、$\boldsymbol\varepsilon$ 无量纲。
11. **刚体运动必定不可压缩，但不一定稳态。** 刚体（不可变形介质）= 平移 + 转动，任何时刻 $\mathbb D=\mathbb O$，所以 $\operatorname{tr}\mathbb D=0$，必定保体积；平移、转动都只是"可能有"，纯平移、纯转动各是一个反例；变速平移 $\vec V=\dot{\vec c}(t)$ 含 $t$，不是稳态。可变形介质 = 平移 + 转动 + 变形（前提概念 C）。

**表 QA · 标准运动（反例表）**

$k$, $\omega$ constantes ; $\Omega$ = taux de rotation, $\vec\gamma$ = accélération. $k$、$\omega$ 为常数；$\Omega$ 为旋转率，$\vec\gamma$ 为加速度。

| Mouvement · 运动 | Lagrange · 拉格朗日 $\vec M=\phi(t,\vec M_0)$ | Euler · 欧拉 $\vec V$ | $\mathbb E$ | $J$ | $\operatorname{div}\vec V$ | $\mathbb D$ | $\boldsymbol\Omega$ | $\vec\gamma$ |
|---|---|---|---|---|---|---|---|---|
| Translation · 平移 | $\vec M=\vec M_0+\vec c(t)$ | $\dot{\vec c}(t)$ | $\mathbb O$ | 1 | 0 | $\mathbb O$ | $\mathbb O$ | $\ddot{\vec c}$ |
| Rotation rigide · 刚体转动 | $\vec M=\mathbb Q(t)\vec M_0$ | $\omega\vec e_3\wedge\overrightarrow{OM}$ | $\mathbb O$ | 1 | 0 | $\mathbb O$ | $\ne\mathbb O$ | $-\omega^2(x_1\vec e_1+x_2\vec e_2)$ |
| Glissement simple · 简单剪切 | $x_1=X_1+ktX_2$ | $kx_2\vec e_1$ | $\ne\mathbb O$ | 1 | 0 | $\ne\mathbb O$ | $\ne\mathbb O$ | $\vec0$ |
| Extension uniaxiale · 单轴伸长 | $x_1=X_1e^{kt}$ | $kx_1\vec e_1$ | $\ne\mathbb O$ | $e^{kt}$ | $k$ | $\ne\mathbb O$ | $\mathbb O$ | $k^2x_1\vec e_1$ |
| Cisaillement pur · 纯剪切 | $x_1=X_1e^{kt}$, $x_2=X_2e^{-kt}$ | $k(x_1\vec e_1-x_2\vec e_2)$ | $\ne\mathbb O$ | 1 | 0 | $\ne\mathbb O$ | $\mathbb O$ | $k^2(x_1\vec e_1+x_2\vec e_2)$ |
| Dilatation uniforme · 均匀膨胀 | $\vec M=e^{kt}\vec M_0$ | $k\,\overrightarrow{OM}$ | $\ne\mathbb O$ | $e^{3kt}$ | $3k$ | $k\,\mathbb I$ | $\mathbb O$ | $k^2\overrightarrow{OM}$ |

Ce que la table réfute · 这张表能推翻的说法：

- Translation / rotation : $\mathbb F\ne\mathbb I$, $\vec u\ne\vec0$, $\boldsymbol\Omega\ne\mathbb O$ **sans** déformation. 平移、转动：$\mathbb F\ne\mathbb I$、$\vec u\ne\vec0$、$\boldsymbol\Omega\ne\mathbb O$ 都可以没有变形。
- Rotation à $\omega$ constant : champ eulérien **stationnaire** mais $\vec\gamma\ne\vec0$. Glissement simple : rotationnel mais **pas** rigide. 匀速转动：欧拉场稳态，但加速度不为零。简单剪切：有旋，但不是刚体运动。
- Isochores ($J=1$) : translation, rotation, glissement simple, cisaillement pur ; **non** : extension, dilatation. 保体积：平移、转动、简单剪切、纯剪切；单轴伸长、膨胀不保体积。
- Sauf la translation à vitesse variable, chaque champ eulérien ci-dessus est stationnaire (pas de $t$) alors que le lagrangien contient $t$. 除变速平移外，上表欧拉场都不含 $t$（稳态），拉格朗日描述却含 $t$。

### 4. QCM

#### Question 2.1

*Par quelle(s) équation(s) se traduit un mouvement incompressible ?* 不可压缩运动可以用哪个（些）方程来表示？

- **(A)** $\overrightarrow{\operatorname{grad}}\vec V=\mathbb O$ (tenseur nul) $\overrightarrow{\operatorname{grad}}\vec V=\mathbb O$（零张量）
- **(B)** $\vec V=\vec0$
- **(C)** $\operatorname{div}\vec V=0$
- **(D)** $\operatorname{tr}\mathbb D=0$
- **(E)** $\det\mathbb F=1$
- **(F)** $\det\mathbb F=0$

**答案与解析**

**C, D, E.** Équivalents : $\operatorname{div}\vec V=\operatorname{tr}\mathbb D=0$ et $J=\det\mathbb F=1$. A et B ne sont que des cas particuliers ; $\det\mathbb F=0$ est impossible. **C、D、E。** 三者等价：$\operatorname{div}\vec V=\operatorname{tr}\mathbb D=0$ 与 $J=\det\mathbb F=1$。A 和 B 只是特例；$\det\mathbb F=0$ 不可能出现。

用到陷阱 6：题问"用什么方程表示"，A、B 只是不可压缩的特例，不能代表全部不可压缩运动。$\det\mathbb F>0$ 是运动映射可逆的要求（前提概念 D）。

#### Question 2.2

*Un milieu est en mouvement incompressible. Quelles affirmations sont vraies ?* 一个介质做不可压缩运动。哪些说法是正确的？

- **(A)** $\rho$ est uniforme dans le milieu. $\rho$ 在介质中处处相等。
- **(B)** $\frac{\mathrm d\rho}{\mathrm dt}=0$.
- **(C)** $\operatorname{div}\vec V=0$.
- **(D)** Le volume de toute partie suivie dans son mouvement est constant. 任何一部分介质，跟着它运动时，体积保持不变。
- **(E)** $\mathbb F=\mathbb I$.

**答案与解析**

**B, C, D.** $\frac{\mathrm d\rho}{\mathrm dt}+\rho\operatorname{div}\vec V=0$ : $\operatorname{div}\vec V=0\Leftrightarrow\frac{\mathrm d\rho}{\mathrm dt}=0$ ; $\frac{\mathrm d}{\mathrm dt}\mathcal V=\int\operatorname{div}\vec V\,\mathrm dV=0$. $\rho$ peut varier d'une particule à l'autre (A faux) ; un glissement simple a $\mathbb F\ne\mathbb I$ (E faux). **B、C、D。** 由 $\frac{\mathrm d\rho}{\mathrm dt}+\rho\operatorname{div}\vec V=0$：$\operatorname{div}\vec V=0\Leftrightarrow\frac{\mathrm d\rho}{\mathrm dt}=0$；$\frac{\mathrm d}{\mathrm dt}\mathcal V=\int\operatorname{div}\vec V\,\mathrm dV=0$。$\rho$ 可以随粒子不同而不同（A 错）；简单剪切的 $\mathbb F\ne\mathbb I$（E 错）。

用到陷阱 7 和陷阱 3：不可压缩运动只要求每个粒子沿轨迹密度不变；初始密度不均匀时，各处密度仍不同。E 错：简单剪切保体积，但 $\mathbb F\ne\mathbb I$。B 用的是质量守恒的欧拉写法（前提概念 B）。

#### Question 2.3

*Quelles équations impliquent forcément une déformation du milieu ?* 哪些方程必然意味着介质发生了变形？

- **(A)** $\mathbb F\ne\mathbb I$
- **(B)** $\mathbb C\ne\mathbb I$
- **(C)** $\mathbb E\ne\mathbb O$
- **(D)** $\mathbb E=\mathbb I$
- **(E)** $\vec u\ne\vec0$
- **(F)** $\operatorname{div}\vec V\ne0$
- **(G)** $\mathbb D\ne\mathbb O$
- **(H)** $\boldsymbol\Omega\ne\mathbb O$

**答案与解析**

**B, C, D, F, G.** $\mathbb E=\mathbb I$ entraîne $\mathbb E\ne\mathbb O$, donc une déformation. **B、C、D、F、G。** $\mathbb E=\mathbb I$ 推出 $\mathbb E\ne\mathbb O$，所以有变形。

用到陷阱 4：$\mathbb E\ne\mathbb I$ 不能保证有变形，$\mathbb E=\mathbb I$ 却能。做这类题时，把"$=$"和"$\ne$"读清楚。

**同一题的另一版：** 选项完全相同，只有 D 写成 $\mathbb E\ne\mathbb I$。这时 D **不选**：不变形时 $\mathbb E=\mathbb O$，照样满足 $\mathbb E\ne\mathbb I$。答案变成 **B, C, F, G**。

#### Question 2.4

*Quelles conditions impliquent forcément une déformation ?* 哪些条件必然意味着有变形？

- **(A)** $J\ne1$
- **(B)** $\overrightarrow{\operatorname{rot}}\vec V\ne\vec0$
- **(C)** $\overrightarrow{\operatorname{grad}}\vec V$ non symétrique $\overrightarrow{\operatorname{grad}}\vec V$ 不对称
- **(D)** $\boldsymbol\varepsilon\ne\mathbb O$ (HPP) $\boldsymbol\varepsilon\ne\mathbb O$（小变形假设 HPP）
- **(E)** $\vec V\ne\vec0$

**答案与解析**

**A, D.** $J\ne1$ : changement de volume ; $\boldsymbol\varepsilon\ne\mathbb O$ : déformation (HPP). B et C signifient $\boldsymbol\Omega\ne\mathbb O$ (vrai en rotation rigide) ; E est vrai en translation. **A、D。** $J\ne1$：体积变了；$\boldsymbol\varepsilon\ne\mathbb O$：有变形（小变形）。B 和 C 的意思都是 $\boldsymbol\Omega\ne\mathbb O$（刚体转动也成立）；E 在平移时也成立。

用到陷阱 2 和 3：$\overrightarrow{\operatorname{grad}}\vec V$ 不对称等价于旋转率不为零，和 $\overrightarrow{\operatorname{rot}}\vec V\ne\vec0$ 是同一件事，刚体转动就满足。E 在平移时成立，也不保证有变形。

## 主干 3 · Vecteur contrainte sur une facette · 应力向量与某个面上的应力

### 1. L'idée en une phrase · 一句话

Le **vecteur contrainte** $\vec T(M,\vec n)$ est la force par unité de surface exercée sur une facette de normale $\vec n$ ; il s'obtient par $\vec T=\boldsymbol\sigma\vec n$, et pour $\vec n=\vec e_j$ c'est la **colonne $j$** de $\boldsymbol\sigma$. **应力向量** $\vec T(M,\vec n)$ 是法向为 $\vec n$ 的小面上、单位面积受到的力；用 $\vec T=\boldsymbol\sigma\vec n$ 计算，法向是 $\vec e_j$ 时就是 $\boldsymbol\sigma$ 的**第 $j$ 列**。

直觉：想象用一把刀把物体在某点切开，切口是一个小平面。切口两边原来互相拉着或推着，切开后要用一个力才能把它们维持原样，这个力除以切口面积就是 $\vec T$。换一个方向切，切口朝向 $\vec n$ 变了，受的力也就变了。应力张量 $\boldsymbol\sigma$ 是一张"查询表"：告诉它切口朝哪（$\vec n$），它就告诉你这个切口上的力（$\vec T=\boldsymbol\sigma\vec n$）。这个力一般是斜的，可以拆成两部分：垂直于切口的部分（法向应力，把切口拉开或压紧）和贴着切口的部分（切向应力，让切口两边互相错动）。

### 2. Formules · 公式

对法向为单位向量 $\vec n$ 的面，先求该面单位面积上的力，再分出垂直于面和平行于面的两部分。以下应力的单位都是 Pa。

- **应力向量** $\vec T=\boldsymbol\sigma\vec n$。题里若写 *facette de normale* $\vec e_j$，直接取应力矩阵的第 $j$ 列。比如问 $\vec e_2$ 面，读出的整列是 $(\sigma_{12},\sigma_{22},\sigma_{32})^{\mathsf T}$。
- **法向应力** $\sigma_n=\vec n\cdot\vec T$。在 $\vec e_2$ 面取对角元 $\sigma_{22}$。正值表示拉，负值表示压。
- **切向应力**　先减去法向部分，$\vec T_t=\vec T-\sigma_n\vec n$，再取大小 $\tau=\lVert\vec T_t\rVert$。在 $\vec e_2$ 面，$\tau=\sqrt{\sigma_{12}^2+\sigma_{32}^2}$。
- **球形应力**　若 $\boldsymbol\sigma=p\mathbb I$，则每个面都有 $\vec T=p\vec n$、$\sigma_n=p$、$\tau=0$。

### 3. Règle de reconnaissance · 判别规则

**法向 $\vec e_j$ 的面：$\vec T$ 就是第 $j$ 列；对角元 $\sigma_{jj}$ 是法向应力，同一列其余分量合起来（取模长）是切向应力。法向不是坐标轴时，先归一化 $\vec n$，再算 $\boldsymbol\sigma\vec n$，再点乘 $\vec n$。**

Pièges · 陷阱：

1. **看列，不要看错列。** 问 $\vec e_3$ 面就看第 3 列，不是第 2 列；题目常常跳着问 $\vec e_1$ 和 $\vec e_3$。
2. **对角元是法向应力，不是切向应力。** $\vec e_1$ 面的切向应力来自 $\sigma_{21}$、$\sigma_{31}$，和 $\sigma_{11}$ 无关。
3. **别漏掉非对角元。** 列里只要还有一个非零的非对角元，切向应力就不为零。
4. **切向应力模长 $\tau=\lVert\vec T_t\rVert$ vs 带符号的切向分量 $\vec T\cdot\vec t$。** 问大小时，$\vec e_1$ 面上有 $\sigma_{21}$ 和 $\sigma_{31}$ 两个分量就用 $\tau=\sqrt{\sigma_{21}^2+\sigma_{31}^2}$，只有一个时严格说 $\tau=\lvert\sigma_{21}\rvert$（不带正负号）；若题目已指定切向正方向 $\vec t$（如流体里求壁面剪应力 $\tau_p=(\boldsymbol\sigma\vec n)\cdot\vec t$），则按投影计算，结果可以为负。
5. **球形张量 $p\,\mathbb I$：任何面上法向 $p$、切向 0。** 因为 $\boldsymbol\sigma\vec n=p\vec n$ 总是和 $\vec n$ 同向，所以任何方向都是主方向。

### 4. QCM

#### Question 3.1

*Quelles affirmations sont vraies pour cet état de contrainte ?* $\boldsymbol\sigma=\begin{pmatrix}\alpha&\gamma&0\\\gamma&\beta&0\\0&0&0\end{pmatrix}$ 对这个应力状态，哪些说法正确？

- **(A)** Dans la facette de normale $\vec e_1$, la contrainte normale vaut $\alpha$. 在法向为 $\vec e_1$ 的面上，法向应力为 $\alpha$。
- **(B)** Dans la facette de normale $\vec e_1$, la contrainte tangentielle vaut $\alpha$. 在法向为 $\vec e_1$ 的面上，切向应力为 $\alpha$。
- **(C)** Dans la facette de normale $\vec e_1$, la contrainte tangentielle vaut $\gamma$. 在法向为 $\vec e_1$ 的面上，切向应力为 $\gamma$。
- **(D)** Dans la facette de normale $\vec e_2$, la contrainte normale vaut $\beta$. 在法向为 $\vec e_2$ 的面上，法向应力为 $\beta$。
- **(E)** Dans la facette de normale $\vec e_2$, la contrainte normale vaut $\gamma$. 在法向为 $\vec e_2$ 的面上，法向应力为 $\gamma$。
- **(F)** Dans la facette de normale $\vec e_2$, la contrainte tangentielle vaut $\beta$. 在法向为 $\vec e_2$ 的面上，切向应力为 $\beta$。

**答案与解析**

**A, C, D.** $\vec T(\vec e_1)=\alpha\vec e_1+\gamma\vec e_2$, $\vec T(\vec e_2)=\gamma\vec e_1+\beta\vec e_2$.

用到陷阱 2 和 4：B、F 把对角元当成切向应力；本题在法向 $\vec e_1$（或 $\vec e_2$）的面上只有沿另一坐标轴的单一分量 $\gamma$，题干沿用习惯按分量读值，严格说模长大小为 $\lvert\gamma\rvert$。

#### Question 3.2

*Quelles affirmations sont vraies avec le champ de contraintes suivant ?* $\boldsymbol\sigma=p\,\mathbb I$ 对 $\boldsymbol\sigma=p\mathbb I$，哪些说法正确？

- **(A)** Facette de normale $\vec e_1$ : contrainte normale $p$. 法向为 $\vec e_1$ 的面：法向应力为 $p$。
- **(B)** Même facette : contrainte tangentielle $p$. 同一面：切向应力为 $p$。
- **(C)** Même facette : contrainte tangentielle nulle. 同一面：切向应力为零。
- **(D)** Facette de normale $\vec e_2$ : contrainte normale nulle. 法向为 $\vec e_2$ 的面：法向应力为零。
- **(E)** Même facette : contrainte normale $p$. 同一面：法向应力为 $p$。
- **(F)** Même facette : contrainte tangentielle nulle. 同一面：切向应力为零。

**答案与解析**

**A, C, E, F.** Tenseur sphérique : $\boldsymbol\sigma\vec n=p\,\vec n$ pour tout $\vec n$, normale $p$ et tangentielle nulle sur toute facette. **A、C、E、F。** 球形张量对任意法向都满足 $\boldsymbol\sigma\vec n=p\,\vec n$，所以任何面上的法向应力均为 $p$，切向应力均为零。

用到陷阱 5：球形张量下任何方向都是主方向，所以任何面上都没有切应力。

## 主干 4 · Contraintes principales, états de contrainte, critères · 主应力、应力状态与屈服准则

### 1. L'idée en une phrase · 一句话

Les **contraintes principales** sont les valeurs propres de $\boldsymbol\sigma$ : sur les facettes de normale principale, le vecteur contrainte est **purement normal** (pas de cisaillement). On décompose $\boldsymbol\sigma=\frac13\operatorname{tr}\boldsymbol\sigma\,\mathbb I+\boldsymbol\sigma^D$ (partie **sphérique** + **déviateur**), et les critères de **Tresca** et de **von Mises** ne dépendent que du déviateur. **主应力** 就是 $\boldsymbol\sigma$ 的特征值：法向沿主方向的面上，应力向量**只有法向分量**、没有切向分量。把 $\boldsymbol\sigma$ 拆成**球量** （平均压力）加**偏量**，**Tresca** 和 **von Mises** 屈服准则只看偏量。

直觉：主干 3 里，刀口换个方向，切口上的力就变。主应力问的是：能不能把刀口转到某个方向，让切口上只有"拉开或压紧"，完全没有"错动"？对称的 $\boldsymbol\sigma$ 总能找到三个互相垂直的这样的方向，这三个方向上的拉压大小就是主应力。再打个比方：把一块金属沉到深海里，四面八方均匀受压（球量），它会被压小一点，但不会"变形走样"；真正让金属屈服、发生永久变形的，是各个方向受力**不一样** 的那部分（偏量）。屈服准则就是把偏量浓缩成一个数（等效应力），和材料的屈服极限 $\sigma_e$ 比大小。

### 2. Formules · 公式

- **主应力**是应力矩阵的特征值。对角矩阵直接读对角元，平面应力要把第三个主应力 $0$ 一起算进去。一般矩阵解 $\det(\boldsymbol\sigma-s\mathbb I)=0$。
- **主方向**满足 $\boldsymbol\sigma\vec n=\sigma_i\vec n$。若某一列只在对角线上有非零元，该坐标轴就是主方向。对于对称块 $\begin{pmatrix}a&b\\b&c\end{pmatrix}$，两个主应力是 $\frac{a+c}{2}\pm\sqrt{(\frac{a-c}{2})^2+b^2}$。
- **平面、单轴、双轴**　若 $\boldsymbol\sigma\vec e_3=\vec0$，则是 $x_1x_2$ 平面应力。恰有一个主应力非零叫单轴，恰有两个非零叫双轴。
- **球形、偏量、纯剪切**　三个主应力相等时是球形。迹为零时，应力等于它的偏量 $\boldsymbol\sigma^D=\boldsymbol\sigma-\frac13\operatorname{tr}(\boldsymbol\sigma)\mathbb I$。主应力为 $\tau,-\tau,0$（$\tau\ne0$）时是纯剪切，既是双轴，迹也为零。
- **散度为零**　应力分量在空间中全是常数时，各分量的空间导数为零，所以 $\overrightarrow{\operatorname{div}}\boldsymbol\sigma=\vec0$。
- **Tresca**　最大主应力减最小主应力，$\sigma_{Tr}=\sigma_{\max}-\sigma_{\min}$。纯剪切时得到 $2|\tau|$。
- **von Mises**　$\sigma_{VM}=\sqrt{\tfrac12[(\sigma_1-\sigma_2)^2+(\sigma_2-\sigma_3)^2+(\sigma_3-\sigma_1)^2]}$。纯剪切时得到 $\sqrt3|\tau|$。在相同单轴屈服限下，Tresca 算出的值更大，先达到屈服限。

### 3. Règle de reconnaissance · 判别规则（表 QB 在本节末尾）

**先求主应力（对角阵直接读，平面状态补一个 0），再逐个对照第 2 节的应力类型；准则只看偏量：Tresca = 最大减最小，von Mises = 三个差的平方和除以 2 再开方。**

Pièges · 陷阱：

1. **偏量不是"把对角元换成 0"。** 偏量是每个对角元减去平均值 $\frac13\operatorname{tr}\boldsymbol\sigma$，非对角元不变；偏量的对角元一般不为零。
2. **平面状态别忘了第三个主应力 0。** $\operatorname{diag}(6,3,0)$ 的 Tresca 是 $6-0=6$，不是 $6-3=3$。
3. **双轴 = 恰好两个主应力非零，不要求同号。** 单轴（traction pure）只有一个非零；双轴不等于纯剪切。
4. **纯剪切要求主应力是 $\tau,-\tau,0$，即迹为 0 且行列式为 0。** $\operatorname{diag}(\sigma_1,\sigma_2,0)$ 只有在 $\sigma_2=-\sigma_1$ 时才是纯剪切；$\operatorname{diag}(2s,-s,-s)$ 迹为 0 但没有零主应力，不是纯剪切。
5. **纯剪切不一定写成非对角形式。** $\tau(\vec e_1\otimes\vec e_2+\vec e_2\otimes\vec e_1)$ 转 $45^\circ$ 就是 $\operatorname{diag}(\tau,-\tau,0)$，两种写法是同一个状态。
6. **静水压力不会屈服。** $-p\,\mathbb I$ 的偏量为零，Tresca 和 von Mises 都等于 0，和 $p$ 多大无关。
7. **Tresca 总是 $\ge$ von Mises，所以 Tresca 更保守。** 纯剪切下两者之比恒为 $2/\sqrt3$，与 $\tau$ 无关；单轴拉伸时两者相等。
8. **"必定"只认题目给的条件。** 只说 $\sigma_1\ne\sigma_2$ 时，不能说它是偏量或纯剪切；分量是常数就能说散度为零。

**表 QB · 标准应力状态（反例表）**

做"必然 / 可能"题时拿来当反例：

| État · 状态 | $\boldsymbol\sigma$ | Principales · 主应力 | $\operatorname{tr}\boldsymbol\sigma$ | $\sigma_{Tr}$ | $\sigma_{VM}$ | Type · 类型 |
|---|---|---|---|---|---|---|
| Pression hydrostatique · 静水压 | $-p\,\mathbb I$ | $-p,-p,-p$ | $-3p$ | 0 | 0 | sphérique, déviateur nul · 球形，偏量为零 |
| Traction simple · 单轴拉伸 | $\sigma\,\vec e_1\otimes\vec e_1$ | $\sigma,0,0$ | $\sigma$ | $\lvert\sigma\rvert$ | $\lvert\sigma\rvert$ | uniaxial, plan · 单轴、平面 |
| Cisaillement pur · 纯剪切 | $\tau(\vec e_1\otimes\vec e_2+\vec e_2\otimes\vec e_1)$ | $\tau,-\tau,0$ | 0 | $2\lvert\tau\rvert$ | $\sqrt3\lvert\tau\rvert$ | plan, biaxial, déviatorique · 平面、双轴、偏量 |
| Biaxial · 双轴 | $\operatorname{diag}(\sigma_1,\sigma_2,0)$ | $\sigma_1,\sigma_2,0$ | $\sigma_1+\sigma_2$ | $\max(\lvert\sigma_1\rvert,\lvert\sigma_2\rvert,\lvert\sigma_1-\sigma_2\rvert)$ | $\sqrt{\sigma_1^2-\sigma_1\sigma_2+\sigma_2^2}$ | plan, biaxial · 平面、双轴 |

### 4. QCM

#### Question 4.1

*Quelles affirmations sont vraies concernant l'état de contrainte suivant dans la base $(\vec e_1,\vec e_2,\vec e_3)$ ?* $\boldsymbol\sigma=\operatorname{diag}(A,B,0)$ *avec $A$, $B$ des constantes positives.* 关于这个应力状态，哪些说法正确？

- **(A)** Il est plan 它是平面应力状态。
- **(B)** Il est sphérique 它是球形张量。
- **(C)** Il est diagonal 它是对角张量。
- **(D)** Il est biaxial 它是双轴应力状态。
- **(E)** Il est déviatorique 它是偏量。
- **(F)** Il est à divergence nulle 它的散度为零。

**答案与解析**

**A, C, D, F.** Plan, diagonal, biaxial, uniforme donc à divergence nulle ; $\operatorname{tr}\boldsymbol\sigma=A+B>0$ : pas déviatorique. **A、C、D、F。** 这是平面、对角、双轴应力状态；应力均匀，所以散度为零。$\operatorname{tr}\boldsymbol\sigma=A+B>0$，因此不是偏量。

球形要求三个主应力相等，这里第三个是 0。

#### Question 4.2

*Que peut-on dire de ce tenseur de contraintes, où $\tau$ est constant ?* $\boldsymbol\sigma=\operatorname{diag}(\tau,-\tau,0)$ $\tau$ 为常数，这个张量有什么性质？

- **(A)** Traction pure 单轴拉伸
- **(B)** Sphérique 球形
- **(C)** Cisaillement pur 纯剪切
- **(D)** Biaxial 双轴
- **(E)** À divergence nulle 散度为零
- **(F)** Déviatorique 偏量

**答案与解析**

**C, D, E, F.** Principales $\tau,-\tau,0$ : cisaillement pur (vu à 45°), deux principales non nulles (biaxial), trace nulle (déviatorique), constant. **C、D、E、F。** 主应力为 $\tau,-\tau,0$：对应转过 45° 的纯剪切；两个主应力非零，所以是双轴；迹为零，所以是偏量；各分量恒定，所以散度为零。

用到陷阱 5：纯剪切不一定写成非对角形式，在主轴下就是 $\operatorname{diag}(\tau,-\tau,0)$。它同时也是双轴：两个主应力非零，不要求同号（陷阱 3）。在原坐标轴下也可以写成只有 $\sigma_{12}=\sigma_{21}=\tau$ 非零的矩阵，转到主轴后即得上面的对角形式。

#### Question 4.3

*Quel critère est le plus conservatif pour un cisaillement pur ?* 纯剪切下哪个准则更保守？

- **(A)** Tresca
- **(B)** von Mises
- **(C)** Aucun 都不是
- **(D)** Cela dépend de $\tau$ 取决于 $\tau$

**答案与解析**

**A.** $\sigma_{Tr}=2\tau>\sigma_{VM}=\sqrt3\,\tau$ quel que soit $\tau$. **A。** 在 $\tau>0$ 时，Tresca 等效应力为 $2\tau$，大于 von Mises 的 $\sqrt3\,\tau$。

用到陷阱 7："更保守"= 算出的等效应力更大，更早判定屈服。两者之比是常数 $2/\sqrt3$，与 $\tau$ 无关。

## 主干 5 · Équilibre, résultante et conditions aux limites en effort · 平衡方程、合力与力边界条件

### 1. L'idée en une phrase · 一句话

**À l'intérieur**, chaque petit élément de matière vérifie $\overrightarrow{\operatorname{div}}\boldsymbol\sigma+\vec f=\rho\vec\gamma$ ; **sur le bord**, le vecteur contrainte $\boldsymbol\sigma\vec n$ est égal à l'effort imposé $\vec T_d$ ; en intégrant $\boldsymbol\sigma\vec n$ sur une face, on obtient la **résultante** et le **moment**. **体内** 每一小块物质都满足 $\overrightarrow{\operatorname{div}}\boldsymbol\sigma+\vec f=\rho\vec\gamma$；**边界上** 应力向量 $\boldsymbol\sigma\vec n$ 等于外界给的面力 $\vec T_d$；把 $\boldsymbol\sigma\vec n$ 在一个面上积分，得到这个面上的**合力** 和**合力矩**。

直觉：把物体切成很多小方块。每一块受到两种力：六个面上邻居的推拉（应力），和重力这类直接作用在体积上的力（体力 $\vec f$）。牛顿第二定律说合力 = 质量 × 加速度。相对两个面上的应力一减、除以边长，就是导数；三个方向加起来就是 $\overrightarrow{\operatorname{div}}\boldsymbol\sigma$。贴着表面的小块，一边是邻居，另一边是外界，所以外界给的力必须正好等于 $\boldsymbol\sigma\vec n$，这就是力边界条件。

### 2. Formules · 公式

- **体内平衡** $\overrightarrow{\operatorname{div}}\boldsymbol\sigma+\vec f=\rho\vec\gamma$。$\vec f$ 是单位体积上的力，$\vec\gamma$ 是加速度。题干写 *statique* 就取 $\vec\gamma=\vec0$；若同时给出 $\vec f=\vec0$，便有 $\overrightarrow{\operatorname{div}}\boldsymbol\sigma=\vec0$。
- **应力散度**按行算。第 $i$ 个分量是 $\dfrac{\partial\sigma_{i1}}{\partial x_1}+\dfrac{\partial\sigma_{i2}}{\partial x_2}+\dfrac{\partial\sigma_{i3}}{\partial x_3}$，单位为 $\mathrm{N/m^3}$。
- **边界上的力** $\boldsymbol\sigma\vec n=\vec T_d$。$\vec n$ 是单位外法向，$\vec T_d$ 是给定面力，单位为 Pa。受压力 $p$ 时取 $\vec T_d=-p\vec n$，自由面取 $\vec T_d=\vec0$。
- **静力平衡选哪两条**　题目问 *équations d’équilibre (statique)*，选体内的 $\overrightarrow{\operatorname{div}}\boldsymbol\sigma+\vec f=\vec0$ 和受力边界上的 $\boldsymbol\sigma\vec n=\vec T_d$。位移条件归到运动学，Hooke 公式归到本构。

### 3. Règle de reconnaissance · 判别规则

**体内写 $\overrightarrow{\operatorname{div}}\boldsymbol\sigma+\vec f=\rho\vec\gamma$，边界上写 $\boldsymbol\sigma\vec n=$ 外界给的面力；这两条合起来才叫"平衡方程"。**

Pièges · 陷阱：

1. **散度按行求导，体力带负号。** 静力时 $\vec f=-\overrightarrow{\operatorname{div}}\boldsymbol\sigma$，不是 $+\overrightarrow{\operatorname{div}}\boldsymbol\sigma$。
2. **$\vec n$ 永远是外法向。** $x=0$、$z=0$ 这类"负侧"的面，外法向是 $-\vec e_x$、$-\vec e_z$，符号错了整个面的力都反向。
3. **"静力 + 无体力"只能推出 $\vec\gamma=\vec0$ 和 $\overrightarrow{\operatorname{div}}\boldsymbol\sigma=\vec0$。** 推不出应力、应变或体积变化为零：受拉的杆就是反例，力从表面来。
4. **压力条件是 $\boldsymbol\sigma\vec n=-p\,\vec n$，有负号。** 压力把表面往里推，而 $\vec n$ 朝外。$\boldsymbol\sigma=-p\,\mathbb I$ 能满足这个条件，但它要求体内处处是静水应力，条件太强，不是边界条件本身。
5. **自由面是 $\boldsymbol\sigma\vec n=\vec0$（整个向量为零）。** 不是 $\boldsymbol\sigma=\mathbb O$（太强），也不是只有法向分量为零（漏了切向）。
6. **力边界条件也算平衡方程。** 弹性问题的平衡方程 = 体内平衡 + $\boldsymbol\sigma\vec n=\vec T_d$；$\vec u=\vec u_d$ 是运动学条件，Hooke 是本构（主干 6；完整的弹性问题见主干 7）。

### 4. QCM

#### Question 5.1

*Si un milieu solide est soumis à un chargement en statique dont la densité de force volumique est nulle, que peut-on dire ?* 如果一个固体受静力加载，而且体力密度为零，可以得出什么结论？

- **(A)** La variation relative de volume est nulle. 体积相对变化为零。
- **(B)** L'accélération est nulle. 加速度为零。
- **(C)** Le champ de déformation est nul. 应变场为零。
- **(D)** La divergence du champ de contrainte est nulle. 应力场的散度为零。

**答案与解析**

**B, D.** Statique : $\vec\gamma=\vec0$ ; $\overrightarrow{\operatorname{div}}\boldsymbol\sigma+\vec f_v=\rho\vec\gamma$ donne $\overrightarrow{\operatorname{div}}\boldsymbol\sigma=\vec0$. Les efforts de surface peuvent déformer le solide (barre en traction). **B、D。** 静力：$\vec\gamma=\vec0$；由 $\overrightarrow{\operatorname{div}}\boldsymbol\sigma+\vec f_v=\rho\vec\gamma$ 得 $\overrightarrow{\operatorname{div}}\boldsymbol\sigma=\vec0$。表面力仍然可以让固体变形（例如受拉的杆）。

用到陷阱 3：A、C 的反例：受拉杆是静力、无体力，但有应变和体积变化。

#### Question 5.2

*Quelles sont les équations d'équilibre (statique) d'un problème d'élasticité ?* 一个弹性问题的（静力）平衡方程是哪些？

- **(A)** $\boldsymbol\sigma(M)\cdot\vec n(M)=\vec T_d(M)\quad\forall M\in\partial\Omega_T$
- **(B)** $\vec u(M)=\vec u_d(M)\quad\forall M\in\partial\Omega_u$
- **(C)** $\boldsymbol\sigma=\lambda(\operatorname{tr}\boldsymbol\varepsilon)\,\mathbb I+2\mu\boldsymbol\varepsilon\quad\forall M\in\Omega$
- **(D)** $\overrightarrow{\operatorname{div}}\boldsymbol\sigma(M)+\vec f_d(M)=\vec0\quad\forall M\in\Omega$

**答案与解析**

**A, D.** Équilibre local dans $\Omega$ et condition en effort sur $\partial\Omega_T$ (SA). B est cinématique (CA), C est la loi de comportement. **A、D。** $\Omega$ 内的局部平衡，加上 $\partial\Omega_T$ 上的力边界条件（静力容许 SA）。B 是运动学条件（运动容许 CA），C 是本构关系。

用到陷阱 6：力边界条件也属于平衡方程，这是最容易漏选的一项。CA、SA 的完整定义见主干 7。

## 主干 6 · Lois de comportement · 本构关系

### 1. L'idée en une phrase · 一句话

La loi de comportement relie les contraintes au mouvement : un **solide élastique** répond à la **déformation** $\boldsymbol\varepsilon$ (loi de Hooke), un **fluide** répond au **taux de déformation** $\mathbb D$ (fluide newtonien) ou seulement à la pression (fluide parfait). 本构关系把应力和运动联系起来：**弹性固体** 看**变形了多少** $\boldsymbol\varepsilon$（Hooke 定律）；**流体** 看**变形得多快** $\mathbb D$（牛顿流体），或者只有压力（理想流体）。

直觉：固体像弹簧，拉长多少就产生多大的力，松手会回到原来的形状，所以它看的是 $\boldsymbol\varepsilon$。流体像蜂蜜，搅得越快阻力越大，一停下来就没有剪切力，它不在乎已经流了多远，只在乎流得多快，所以看的是 $\mathbb D$。理想流体连这点阻力都没有，只剩压力。平衡方程（主干 5）只说"力要平衡"，不知道材料是什么；本构就是告诉你"这种材料怎么受力"的那条方程。

### 2. Formules · 公式

先圈题干里的 **fluide newtonien**（牛顿流体）或 **milieux fluides**（流体）。后者也包括理想流体，因此即使两题给出相同的公式，勾选范围也不同。

- **理想流体**　$\boldsymbol\sigma=-p\mathbb I$。只有压力 $p$，没有黏性应力。
- **不可压缩牛顿流体**　$\boldsymbol\sigma=-p\mathbb I+2\mu_v\mathbb D$。$\mu_v$ 是黏度，$\mathbb D$ 是主干二的变形率，题目里的黏性应力由它决定。
- **可压缩牛顿流体**　一般式多一项 $\lambda_v\operatorname{tr}(\mathbb D)\mathbb I$。不可压缩时 $\operatorname{tr}\mathbb D=0$，就回到上一式。
- **各向同性线弹性固体（小变形）**　正关系 $\boldsymbol\sigma=2\mu\boldsymbol\varepsilon+\lambda\operatorname{tr}(\boldsymbol\varepsilon)\mathbb I$。逆关系 $\boldsymbol\varepsilon=\frac{1+\nu}{E}\boldsymbol\sigma-\frac{\nu}{E}\operatorname{tr}(\boldsymbol\sigma)\mathbb I$。两式里的 $\boldsymbol\varepsilon$ 都是应变。

### 3. Règle de reconnaissance · 判别规则（表 QB′ 在本节末尾）

**看式子里的变量：含 $\boldsymbol\varepsilon$、$E$、$\nu$、$\lambda$、$\mu$ 的是固体；含 $p$、$\mathbb D$、$\mu_v$ 的是流体。**

Pièges · 陷阱：

1. **Hooke 的正关系和逆关系是同一条固体本构。** 一个用 $\lambda,\mu$ 从 $\boldsymbol\varepsilon$ 求 $\boldsymbol\sigma$，一个用 $E,\nu$ 从 $\boldsymbol\sigma$ 求 $\boldsymbol\varepsilon$，都不是流体。
2. **问"流体"选两条，问"牛顿流体"只选一条。** $-p\,\mathbb I$ 是理想流体，也是流体，但没有黏性，不是牛顿流体；牛顿流体必须有 $2\mu_v\mathbb D$。
3. **逆关系的两个系数别颠倒。** $\frac{1+\nu}E$ 在 $\boldsymbol\sigma$ 前，$\frac\nu E$ 在迹前；剪应变 $\varepsilon_{12}=\frac{\sigma_{12}}{2\mu}$，不是 $\frac{\sigma_{12}}E$。
4. **正关系对角元别漏 $\lambda\operatorname{tr}\boldsymbol\varepsilon$。** 非对角元才只有 $2\mu\varepsilon_{ij}$。
5. **固体的 $\mu$（剪切模量，Pa）不是流体的 $\mu_v$（黏度，Pa·s）。** 同一个字母，量纲差一个时间；$\nu$ 无量纲。

**表 QB′ · 没有外力时的应力和应变（反例表）**

| Situation · 情形 | $\boldsymbol\varepsilon$ | $\boldsymbol\sigma$ | Réfute · 推翻 |
|---|---|---|---|
| Échauffement uniforme $\delta T$, corps libre · 均匀升温、自由 | $\alpha\,\delta T\,\mathbb I$ | $\mathbb O$ | « $\boldsymbol\varepsilon\ne\mathbb O\Rightarrow\boldsymbol\sigma\ne\mathbb O$ » |
| Échauffement uniforme, $\vec u=\vec0$ sur tout le bord · 均匀升温、全约束 | $\mathbb O$ ($\vec u=\vec0$) | $-3K\alpha\,\delta T\,\mathbb I$ | « $\boldsymbol\varepsilon=\mathbb O\Rightarrow\boldsymbol\sigma=\mathbb O$ », « pas d'effort ⇒ pas de contrainte » |
| Température non uniforme, corps libre · 温度不均匀、自由 | $\ne\alpha\,\delta T\,\mathbb I$ en général | $\ne\mathbb O$ en général | « pas d'effort ⇒ pas de contrainte » |
| Autocontraintes (contraintes résiduelles) · 自应力 | — | $\ne\mathbb O$, $\overrightarrow{\operatorname{div}}\boldsymbol\sigma=\vec0$, bord libre | idem |
| Fluide visqueux en rotation d'ensemble · 黏性流体整体转动 | $\mathbb D=\mathbb O$ | $-p\,\mathbb I$ | « fluide visqueux en mouvement ⇒ contrainte visqueuse » |

### 4. QCM

#### Question 6.1

*Quelle(s) relation(s) de comportement correspondent à un fluide newtonien ?* 哪些本构对应牛顿流体？

- **(A)** $\boldsymbol\varepsilon=\frac{1+\nu}E\boldsymbol\sigma-\frac\nu E\operatorname{tr}(\boldsymbol\sigma)\,\mathbb I$
- **(B)** $\boldsymbol\sigma=2\mu\boldsymbol\varepsilon+\lambda\operatorname{tr}(\boldsymbol\varepsilon)\,\mathbb I$
- **(C)** $\boldsymbol\sigma=-p\,\mathbb I$
- **(D)** $\boldsymbol\sigma=2\mu_v\mathbb D-p\,\mathbb I$

**答案与解析**

**D.** C est un fluide parfait (non visqueux) ; A et B sont la loi de Hooke (solide). **D。** C 是理想流体（无黏性）；A 和 B 是固体的 Hooke 定律。

用到陷阱 1、陷阱 2：问的是"牛顿流体"，只有含 $\mathbb D$ 的那条；理想流体也是流体，但不是牛顿流体。

#### Question 6.2

*Quelle(s) relation(s) de comportement correspondent à des milieux fluides ?* 哪些本构对应流体？

- **(A)** $\boldsymbol\sigma=2\mu\boldsymbol\varepsilon+\lambda\operatorname{tr}(\boldsymbol\varepsilon)\,\mathbb I$
- **(B)** $\boldsymbol\sigma=-p\,\mathbb I$
- **(C)** $\boldsymbol\sigma=2\mu_v\mathbb D-p\,\mathbb I$
- **(D)** $\boldsymbol\varepsilon=\frac{1+\nu}E\boldsymbol\sigma-\frac\nu E\operatorname{tr}(\boldsymbol\sigma)\,\mathbb I$

**答案与解析**

**B, C.** Fluide parfait et fluide newtonien incompressible. **B、C。** 分别是理想流体和不可压缩牛顿流体。

用到陷阱 2：与 6.1 同一组选项，问法从"牛顿流体"放宽到"流体"，答案多了理想流体。

## 主干 7 · Problème d'élasticité · 弹性问题

### 1. L'idée en une phrase · 一句话

**Résoudre un problème d'élasticité**, c'est trouver un champ de déplacement $\vec u$ **cinématiquement admissible (CA)** et un champ de contrainte $\boldsymbol\sigma$ **statiquement admissible (SA)**, reliés par la **loi de comportement** ; l'équation de **Navier** est ce qui reste quand on écrit tout en fonction de $\vec u$. 解弹性问题，就是找一个**满足位移条件的位移场** $\vec u$（CA）和一个**满足平衡与力条件的应力场** $\boldsymbol\sigma$（SA），两者由**本构关系** 连起来；**Navier 方程** 是把一切都写成 $\vec u$ 之后剩下的那条方程。

直觉：一根弹簧上端挂在天花板上，下端吊一个重物。"上端不动"是位移方面的条件；"弹簧里的力和重物的重量平衡"是力方面的条件；$F=kx$ 把力和伸长连起来。弹性问题就是这件事的三维版本：位移那一半叫 CA，力那一半叫 SA，$F=kx$ 换成 Hooke 定律。Navier 方程相当于把 $F=kx$ 代进平衡方程，只剩伸长 $x$ 一个未知量。

### 2. Formules · 公式

- **位移场** $\vec u$。在题设的完整线弹性体内，位移连续、单值，具有题目要求的正则性，并满足给定的位移条件。小变形下由位移求应变，$\boldsymbol\varepsilon=\tfrac12(\nabla\vec u+(\nabla\vec u)^{\mathsf T})$。
- **运动学容许（CA）**　给定位移的边界上 $\vec u=\vec u_d$。**静力学容许（SA）**　体内满足 $\overrightarrow{\operatorname{div}}\boldsymbol\sigma+\vec f=\vec0$，给定面力的边界上满足 $\boldsymbol\sigma\vec n=\vec T_d$。
- **Navier 方程**把三步合在一起：由位移求应变，用 Hooke 本构由应变求应力，再把应力代入局部平衡。均质、各向同性、小变形静力问题得到 $(\lambda+\mu)\operatorname{grad}(\operatorname{div}\vec u)+\mu\Delta\vec u+\vec f=\vec0$。边界条件另写。
- **光滑接触（contact glissant）**　遇到固定、刚性、无摩擦的接触面，分别看两个方向。
    - **法向位移** $\vec u\cdot\vec n=0$。物体贴着固定面，不能穿透。法向接触反力待求。
    - **切向面力** $(\boldsymbol\sigma\vec n)\cdot\vec t=0$，对任一切向 $\vec t$ 成立。物体可以沿面滑动。

### 3. Règle de reconnaissance · 判别规则（表 QC 在本节末尾）

**先给每个条件贴标签：关于位移的是 CA，关于力的是 SA，把两者连起来的是本构。Navier 只把体内的三样（平衡、本构、HPP）合成一条方程，边界条件永远要另外写。**

Pièges · 陷阱：

1. **位移场连续、正则，不是"零"，也不能间断。** 间断意味着材料开裂或互相重叠；它可以在某些点为零，但整体不是零场。
2. **Navier 只包含平衡、本构、HPP 三样。** 不包含边界条件、初始条件，也不包含质量守恒。
3. **$\vec f_d$、$\vec T_d$、$\vec u_d$、$\mathbb K$ 是已知量。** 主要未知量是 $\vec u$ 和 $\boldsymbol\sigma$；$\partial\Omega_u$ 上的约束反力是次要未知量，解出 $\boldsymbol\sigma$ 后用 $\boldsymbol\sigma\vec n$ 算。
4. **CA 场的集合不是向量空间。** 两个 CA 场之差是 CAZ；只有系数之和为 1 的组合（如平均值）仍是 CA，和、两倍一般不是。SA 场同理：两个 SA 场之差是 SAZ。
5. **滑动接触 = 法向位移为零（CA）+ 切向面力为零（SA）。** 法向应力是未知的接触反力，不为零；切向位移是自由的。对称面的条件和它相同。
6. **固定只给位移 $\vec u=\vec0$，不给力。** 同一点同一方向不能既给位移又给力，固定端的面力就是反力，是未知量。

**表 QC · 方程和问题包含什么**

✓ = contient · 包含 ; — = ne contient pas · 不包含.

| Équation / problème · 方程或问题 | Équilibre (quantité de mouvement) · 平衡 | Loi de comportement · 本构 | Cinématique $\boldsymbol\varepsilon(\vec u)$ ou $\mathbb D(\vec V)$ · 运动学 | Conservation de la masse · 质量守恒 | Conditions aux limites · 边界条件 | Inconnues · 未知量 |
|---|---|---|---|---|---|---|
| $\overrightarrow{\operatorname{div}}\boldsymbol\sigma+\vec f=\rho\vec\gamma$ | ✓ | — | — | — | — | $\boldsymbol\sigma$ |
| Hooke $\boldsymbol\sigma=\lambda\operatorname{tr}\boldsymbol\varepsilon\,\mathbb I+2\mu\boldsymbol\varepsilon$ | — | ✓ | — | — | — | — |
| Navier $(\lambda+2\mu)\overrightarrow{\operatorname{grad}}\operatorname{div}\vec u-\mu\overrightarrow{\operatorname{rot}}\,\overrightarrow{\operatorname{rot}}\vec u+\vec f=\rho\vec\gamma$ | ✓ | ✓ (élastique, isotrope, homogène) | ✓ (HPP) | — | — | $\vec u$ |
| Beltrami | ✓ | ✓ (inverse) | ✓ (compatibilité) | — | — | $\boldsymbol\sigma$ |
| Navier–Stokes $\rho\vec\gamma=-\overrightarrow{\operatorname{grad}}p+\mu_v\Delta\vec V+(\lambda_v+\mu_v)\overrightarrow{\operatorname{grad}}\operatorname{div}\vec V+\vec f$ | ✓ (dynamique) | ✓ (newtonien) | ✓ | — | — | $\vec V$, $p$ |
| Problème d'élasticité (statique, HPP) · 弹性问题 | ✓ | ✓ | ✓ | — (inutile) | $\vec u=\vec u_d$ sur $\partial\Omega_u$, $\boldsymbol\sigma\vec n=\vec T_d$ sur $\partial\Omega_T$ | $\vec u$, $\boldsymbol\sigma$ (+ réactions sur $\partial\Omega_u$) |
| Problème de fluide newtonien · 牛顿流体问题 | ✓ (NS) | ✓ | ✓ | ✓ ($\operatorname{div}\vec V=0$ si incompressible) | en vitesse (adhérence) et en effort (pression, surface libre) | $\vec V$, $p$ |

### 4. QCM

#### Question 7.1

*Quels adjectifs caractérisent le champ de déplacement en élasticité linéaire ?* 线弹性中位移场的特征是什么？

- **(A)** Continu 连续
- **(B)** Nul 为零
- **(C)** Discontinu 不连续
- **(D)** Régulier 正则

**答案与解析**

**A, D.** Un champ CA est continu et régulier (et fini) ; il peut s'annuler par endroits mais n'est pas nul. **A、D。** CA 场连续、正则且有限；它可以局部为零，但不要求整个场为零。

用到陷阱 1：不连续意味着材料开裂或重叠。

#### Question 7.2

*Quelles équations sont intégrées dans l'équation de Navier ?* Navier 方程里包含了哪些方程？

- **(A)** Équation d'équilibre local 局部平衡方程
- **(B)** Conservation de la masse 质量守恒
- **(C)** Relation de comportement 本构关系
- **(D)** Équation HPP 小扰动假设下的应变与位移关系
- **(E)** Conditions aux limites 边界条件
- **(F)** Conditions initiales 初始条件

**答案与解析**

**A, C, D.** On injecte $\boldsymbol\varepsilon(\vec u)$ (HPP) dans la loi de Hooke, puis dans l'équilibre local. **A、C、D。** 先把 HPP 下的应变与位移关系代入 Hooke 定律，再代入局部平衡方程。

用到陷阱 2 和表 QC 的 Navier 行：边界条件要另外写。

#### Question 7.3

*Quelle(s) équation(s) tradui(sen)t une condition de type contact glissant en tout point $M$ de la frontière $\partial\Omega$ (immobile) d'un domaine solide $\Omega$ avec un milieu extérieur indéformable, où $\vec n$ est la normale sortante au domaine $\Omega$ et $\vec t$ tout vecteur tangent à la frontière $\partial\Omega$ ?* 滑动接触条件用哪些方程表示？

- **(A)** $\boldsymbol\sigma(M)\cdot\vec n(M)=\vec0$
- **(B)** $\boldsymbol\sigma(M)\cdot\vec t(M)=\vec0$
- **(C)** $[\boldsymbol\sigma(M)\cdot\vec n(M)]\cdot\vec n(M)=0$
- **(D)** $[\boldsymbol\sigma(M)\cdot\vec n(M)]\cdot\vec t(M)=0$
- **(E)** $\sigma_{ij}(M)=0\ \forall i,j$
- **(F)** $\vec u(M)=\vec0$
- **(G)** $\vec u(M)\cdot\vec n(M)=0$
- **(H)** $\vec u(M)\cdot\vec t(M)=0$

**答案与解析**

**D, G.** Contact maintenu : déplacement normal nul ; sans frottement : contrainte tangentielle nulle. La contrainte normale (réaction) et le déplacement tangentiel restent libres. **D、G。** 保持接触要求法向位移为零；无摩擦要求切向应力为零。法向接触反力和切向位移不由这些条件直接指定。

用到陷阱 5：一条运动学条件加一条切向静力学条件。C 错：法向接触反力由平衡决定，可以非零。H 错：能滑动，切向位移是自由的。

## 主干 8 · Fluide newtonien et équation de Navier–Stokes · 流体与 NS 方程

### 1. L'idée en une phrase · 一句话

Un problème de fluide est **un problème d'élasticité écrit en vitesse** : inconnues $\vec V$ et $p$ (description eulérienne), loi de comportement **newtonienne** ; en l'injectant dans l'équation du mouvement on obtient **Navier–Stokes**, à compléter par la **conservation de la masse** et les **conditions aux limites en vitesse et en effort**. 流体问题就是**换成速度的弹性问题**：未知量是 $\vec V$ 和 $p$（欧拉描述），本构是**牛顿流体**；把本构代进动量方程得到 **NS 方程**，再加上**质量守恒** 和**速度、力两类边界条件**。

直觉：固体问题里，我们找"每个点挪了多少"（位移 $\vec u$），应力跟应变 $\boldsymbol\varepsilon$ 成正比。流体没有"原来的形状"，问"挪了多少"没意义，只能问"此刻每个点流多快"（速度 $\vec V$），而黏性应力跟"变形的快慢" $\mathbb D$ 成正比。所以整套做法照搬固体：动量方程 + 本构 + 运动学 → 一个只含未知场的方程（固体叫 Navier，流体叫 Navier–Stokes），再配边界条件。多出来的一样东西是质量守恒，因为流体会流进流出，要单独写。

### 2. Formules · 公式

- **动量方程（Navier–Stokes）**　不可压缩、黏度恒定的牛顿流体满足 $\rho[\partial_t\vec V+(\vec V\cdot\nabla)\vec V]=-\operatorname{grad}p+\mu_v\Delta\vec V+\vec f$。右侧依次是压力、黏性和体力，未知量是速度 $\vec V$ 和压力 $p$。
- **质量守恒**　另写 $\partial_t\rho+\operatorname{div}(\rho\vec V)=0$。不可压缩时为 $\operatorname{div}\vec V=0$。三维不可压缩问题共有三个动量分量和一个质量方程。
- **速度边界条件**　例如黏性流体在无滑移壁面满足 $\vec V=\vec V_{\rm paroi}$。**力边界条件**规定面力 $\boldsymbol\sigma\vec n$，例如静止空气作用于自由表面的压力。
- **两种黏性流体的界面**　题设的无滑移、无额外界面力条件下，$\vec V_A=\vec V_B$，用同一法向又有 $\boldsymbol\sigma_A\vec n=\boldsymbol\sigma_B\vec n$。选项中速度的法向、切向分量和面力的法向、切向分量都连续。密度可以不同。

### 3. Règle de reconnaissance · 判别规则

**流体问题 = NS（动量 + 牛顿本构 + $\mathbb D(\vec V)$）+ 质量守恒 + 速度边界条件 + 力边界条件；欧拉描述，未知量 $\vec V$、$p$。**

Pièges · 陷阱：

1. **质量守恒不在 NS 里。** NS 只由动量、本构、运动学组成，质量守恒是单独的一个方程，必须另外写。
2. **流体不用 Navier 方程，也不用位移边界条件。** Navier 和位移 $\vec u$ 是固体的东西；流体的未知量是速度。
3. **界面上连续的是应力向量 $\boldsymbol\sigma\vec n$，不是整个张量。** 作用力与反作用力只管界面那个面上的力；密度、单独的压力、整个应力张量都可以跳。速度的法向（不渗透）和切向（不滑移）都连续。
4. **黏性流体贴壁不滑，理想流体只管法向。** 黏性：$\vec V=\vec V_{\text{paroi}}$；理想：只有 $\vec V\cdot\vec n=\vec V_{\text{paroi}}\cdot\vec n$，可以沿壁面滑动。
5. **自由面是应力条件，不是速度条件。** 切应力为零（$\mu_vv'=0$）、压力等于大气压；自由面上的流体照样在流动，$v\ne0$。
6. **NS 里黏性项是 $\mu_v\Delta\vec V$，本构里是 $2\mu_v\mathbb D$。** 系数不一样，别抄混。理想流体（$\boldsymbol\sigma=-p\,\mathbb I$）没有黏性项，NS 退化为 Euler 方程。
7. **不可压缩时 $p$ 是未知量。** 它由方程和边界条件解出来；没有边界条件固定时只能确定到一个常数。

### 4. QCM

#### Question 8.1

*Quelles équations sont nécessaires à la résolution d'un problème de fluide newtonien ?* 求解牛顿流体问题需要哪些方程？

- **(A)** Équation de Navier–Stokes Navier–Stokes 方程
- **(B)** Équation de Navier Navier 方程
- **(C)** Conservation de la masse 质量守恒
- **(D)** Conditions aux limites en déplacement 位移边界条件
- **(E)** Conditions aux limites en vitesse 速度边界条件
- **(F)** Conditions aux limites en effort 力边界条件

**答案与解析**

**A, C, E, F.** NS + conservation de la masse ; CL en vitesse (adhérence) et en effort (pression, surface libre). Navier et les déplacements concernent les solides. **A、C、E、F。** NS 加质量守恒，再加速度边界条件（贴壁）与力边界条件（压力、自由面）。Navier 方程和位移条件用于固体。

用到陷阱 1、陷阱 2，主干 7 的表 QC 最后一行：质量守恒不包含在 NS 里，要单独写。B 是固体的方程，D 是固体的边界条件。

#### Question 8.2

*Deux fluides visqueux différents en contact s'écoulent côte à côte, sans se mélanger. Pour quelle(s) quantité(s) a-t-on continuité à l'interface $\Sigma$ entre les deux fluides ?* 两种互不相溶的黏性流体，界面上哪些量连续？

- **(A)** Vitesse normale 法向速度
- **(B)** Vitesse tangentielle 切向速度
- **(C)** Masse volumique 密度
- **(D)** Tenseur de contrainte 应力张量
- **(E)** Contrainte tangentielle 切向应力
- **(F)** Contrainte normale 法向应力

**答案与解析**

**A, B, E, F.** Vitesse continue (imperméabilité + adhérence) ; vecteur contrainte $\boldsymbol\sigma\vec n$ continu (action–réaction) ; $\rho$ et le tenseur complet peuvent être discontinus. **A、B、E、F。** 速度连续来自不渗透与不滑移；应力向量连续来自作用与反作用。密度和整个应力张量可以不连续。

用到陷阱 3："应力连续"指的是界面上的应力向量，不是整个张量。E、F 是应力向量的切向和法向分量，所以都连续。

## 主干 9 · Théorèmes de l'énergie · 能量定理

### 1. L'idée en une phrase · 一句话

Parmi tous les champs **cinématiquement admissibles**, la solution exacte est celui qui **minimise l'énergie potentielle** $E_p$ (énergie de déformation − travail des efforts donnés) ; parmi tous les champs **statiquement admissibles**, elle **minimise l'énergie complémentaire** $E_c$ ; d'où l'**encadrement** $-E_c(\boldsymbol\sigma_{SA})\le E_p(\vec u_{ex})\le E_p(\vec u_{CA})$. 在所有**运动许可（CA）** 的位移场里，精确解让**势能** $E_p$（应变能 − 给定外力功）**最小**；在所有**静力许可（SA）** 的应力场里，精确解让**余能** $E_c$ **最小**；于是有**夹逼不等式** $-E_c(\boldsymbol\sigma_{SA})\le E_p(\vec u_{ex})\le E_p(\vec u_{CA})$。

直觉：弹性体"很懒"，在所有允许的变形方式里，它挑能量最省的那一个。一颗球放进碗里，会滚到最低点停下；挂上重物的弹簧，会停在"弹簧储存的能量减去重物下降做的功"最小的位置。所以随便猜一个允许的位移场（CA），算出来的势能一定不比真解低，给出上界；随便猜一个满足平衡的应力场（SA），算出来的 $-E_c$ 一定不比真解高，给出下界。真解夹在中间。

### 2. Formules · 公式

- **应变能** $W_{def}=\tfrac12\int_\Omega\boldsymbol\varepsilon:\mathbb K:\boldsymbol\varepsilon\,\mathrm dV\ge0$。$\mathbb K$ 是弹性张量，$\boldsymbol\varepsilon$ 由位移 $\vec u$ 求得。
- **外力功** $W_{ext}=\int_\Omega\vec f_d\cdot\vec u\,\mathrm dV+\int_{\partial\Omega_T}\vec T_d\cdot\vec u\,\mathrm dS$。两项分别来自体力和给定面力。
- **势能** $E_p(\vec u)=W_{def}(\vec u)-W_{ext}(\vec u)$。题目给某个运动学容许位移（CA）且 $E_p=0$，可推出这个位移上的应变能等于外力功。判断它是否为精确解，要看势能是否达到最小值。
- **无给定外力**　此时 $W_{ext}=0$，所以 $E_p=W_{def}\ge0$。精确解使势能在全部 CA 位移中取最小值。若零位移也满足边界条件，最小值就是零。
- **余能** $E_c$ 用静力学容许应力（SA）计算。精确解满足 $E_p(\vec u_{ex})=-E_c(\boldsymbol\sigma_{ex})$，且 $-E_c(\boldsymbol\sigma_{SA})\le E_p(\vec u_{ex})\le E_p(\vec u_{CA})$。

### 3. Règle de reconnaissance · 判别规则

**精确解在 CA 场里让 $E_p$ 最小、在 SA 场里让 $E_c$ 最小，并且 $E_p(\vec u_{ex})=-E_c(\boldsymbol\sigma_{ex})$；所以任何 CA 场给上界，任何 SA 场的 $-E_c$ 给下界。**

Pièges · 陷阱：

1. **$E_p$ 用位移写、只对 CA 场；$E_c$ 用应力写、只对 SA 场。** 题目说"énergie de déformation écrite en déplacement"就是 $E_p$ 里的应变能，"écrite en effort"是 $E_c$ 里的。
2. **精确解是最小值，不是最大值。** CA 场的势能 $\ge$ 真解的势能；方向别写反。
3. **$E_p(\vec u_{CA})=0$ 只说明应变能和外力功相互抵消。** 它不说明这个场是精确解，也不说明是"能量意义下最好的"；要知道是不是最小，得跟别的 CA 场比。
4. **没有外力时，$E_p=W_{def}\ge0$。** 这时精确解处 $E_p$ 最小且"为正"（考试的"positive"按非负理解：没有给定位移时真解是零场，$E_p=0$）。绝不是最大，也不是负。

### 4. QCM

#### Question 9.1

*Si l'énergie potentielle associée à un champ cinématiquement admissible est nulle, quelles en sont les implications ?* 若某个 CA 场的势能为零，能推出什么？

- **(A)** Le champ est la solution exacte. 该场是精确解。
- **(B)** Le champ est la meilleure solution au sens énergétique. 该场是能量意义下的最优解。
- **(C)** L'énergie de déformation écrite en déplacement est nulle. 用位移表示的应变能为零。
- **(D)** L'énergie de déformation écrite en effort est nulle. 用应力表示的应变能为零。
- **(E)** L'énergie de déformation écrite en déplacement est compensée par le travail des efforts donnés dans ce champ. 用位移表示的应变能，被给定外力在该场中做的功抵消。
- **(F)** L'énergie de déformation écrite en effort est compensée par le travail des efforts donnés dans ce champ. 用应力表示的应变能，被给定外力在该场中做的功抵消。

**答案与解析**

**E.** $E_p(\vec u)=W_{def}(\vec u)-W_{ext}(\vec u)=0$ : les deux termes se compensent. Rien n'indique que ce soit le minimum. **E。** 势能等于应变能减外力功；势能为零仅说明两者抵消，不能据此认定已达到最小值。

用到陷阱 1、陷阱 3：$E_p$ 是用位移写的，所以 D、F（用应力写的余能）无关。A、B 都要求"最小"，单凭 $E_p=0$ 推不出来；C 也不对，是两项相等，不是应变能为零。

#### Question 9.2

*Si un solide élastique n'est soumis à aucun effort surfacique ou volumique, son énergie potentielle à la solution exacte $E_p(\vec u_{ex})$ est :* 无面力、无体力的弹性体，精确解处的势能是？

- **(A)** maximale 最大
- **(B)** minimale 最小
- **(C)** négative 为负
- **(D)** nulle 为零
- **(E)** positive 非负（本题按此义）
- **(F)** peu importe 无关紧要

**答案与解析**

**B, E.** $E_p$ est minimale à la solution exacte ; sans effort extérieur, $E_p=\frac12\int\boldsymbol\varepsilon:\mathbb K:\boldsymbol\varepsilon\,\mathrm dV\ge0$. **B、E。** 精确解使势能最小；没有外力时，势能等于应变能，因此非负。

用到陷阱 2、陷阱 4：教师答案是 B、E。若也没有给定位移，精确解是零场，$E_p=0$，"正"按"非负"理解（陷阱 4）。
