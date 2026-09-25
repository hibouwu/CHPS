# 练习 1 --- 直接与逆本构关系

研究一个在**小扰动假设（HPP）**下的**各向同性线性弹性固体**。 该材料由以下参数描述：

- $\lambda$：第一 Lamé 常数（单位 Pa, MPa 或 GPa）

- $\mu$：剪切模量（第二 Lamé 常数，有时记为 $G$），单位 Pa, MPa 或 GPa

- $E$：杨氏模量（或弹性模量），单位 Pa, MPa 或 GPa

- $\nu$：泊松比（无量纲）

- $K$：体积弹性模量（或压缩模量），单位 Pa, MPa 或 GPa

## 问题 1.1

回忆直接与逆本构关系的两种表达式，分别为 $\sigma = f_1(\varepsilon)$ 与 $\varepsilon = f_2(\sigma)$， 并用材料参数 $\lambda, \mu, E, \nu$ 表示。推导这些材料参数之间的关系。

#### 解答：

直接与逆的线性本构关系写作： 

$$
\sigma = K : \varepsilon = 2\mu \varepsilon + \lambda\, \mathrm{Tr}(\varepsilon) I,
\quad
\varepsilon = K^{-1} : \sigma = \frac{1+\nu}{E}\sigma - \frac{\nu}{E}\mathrm{Tr}(\sigma)I
\tag{*1.1}
$$

首先求 $\mathrm{Tr}(\sigma)$ 与 $\mathrm{Tr}(\varepsilon)$、$E$、$\nu$ 之间的关系。

由逆关系： 

$$
\mathrm{Tr}(\varepsilon) =
\mathrm{Tr}\left(\frac{1+\nu}{E}\sigma\right)
- \mathrm{Tr}\left(\frac{\nu}{E}\mathrm{Tr}(\sigma)I\right)
$$

 因为 $\mathrm{Tr}(I)=3$，得： 

$$
\mathrm{Tr}(\varepsilon) = \frac{1+\nu}{E}\mathrm{Tr}(\sigma) - \frac{3\nu}{E}\mathrm{Tr}(\sigma)
= \frac{1-2\nu}{E}\mathrm{Tr}(\sigma)
\tag{*1.2}
$$

 因此： 

$$
\mathrm{Tr}(\sigma) = \frac{E}{1-2\nu}\mathrm{Tr}(\varepsilon)
\tag{*1.3}
$$

代回逆关系： 

$$
\varepsilon = \frac{1+\nu}{E}\sigma
- \frac{\nu}{E}\frac{E}{1-2\nu}\mathrm{Tr}(\varepsilon)I
\Rightarrow
\frac{1+\nu}{E}\sigma = \varepsilon + \frac{\nu}{1-2\nu}\mathrm{Tr}(\varepsilon)I
\tag{*1.4}
$$

整理得： 

$$
\sigma = \frac{E}{1+\nu}\varepsilon
+ \frac{\nu E}{(1+\nu)(1-2\nu)}\mathrm{Tr}(\varepsilon)I
\tag{*1.5}
$$

由此识别出： 

$$
\mu = \frac{E}{2(1+\nu)}, \quad
\lambda = \frac{\nu E}{(1+\nu)(1-2\nu)}
\tag{*1.6}
$$

等价形式： 

$$
E = \mu \frac{3\lambda + 2\mu}{\lambda + \mu},
\quad
\nu = \frac{\lambda}{2(\lambda + \mu)}
\tag{*1.7}
$$

## 问题 1.2

回忆固体材料的**不可压缩性条件**，并说明该条件对模量 $K$ 的影响。

#### 解答：

不可压缩材料在任意载荷下都只能产生**不可压缩运动**，即： 

$$
\mathrm{div}_E \vec{V} = 0
\tag{*1.8}
$$

在 HPP 假设下，欧拉与拉格朗日表示重合，因此： 

$$
\mathrm{div}\,\vec{V} = 0 \Rightarrow
\mathrm{div}\,\vec{u} = 0
\Rightarrow
\mathrm{Tr}(\nabla \vec{u}) = \mathrm{Tr}(\varepsilon) = 0
\tag{*1.9}
$$

压缩模量 $K$ 出现在本构关系： 

$$
\mathrm{Tr}(\sigma) = K\,\mathrm{Tr}(\varepsilon)
\quad\Longleftrightarrow\quad
\mathrm{Tr}(\varepsilon) = \frac{1}{K}\mathrm{Tr}(\sigma)
\tag{*1.10a}
$$

若 $\mathrm{Tr}(\varepsilon)=0$ 对任意 $\sigma$ 成立，则必有： 

$$
K \to \infty
\tag{*1.10b}
$$

当材料受载超过屈服极限时，会产生**塑性变形**，其叠加在弹性变形之上。 对于金属和合金，塑性变形通常被视为**等体积变形（isochore）**，即不可压缩。

## 问题 1.3

在此情况下（3D），求塑性应变张量的独立分量数。

#### 解答：

在 HPP 假设下，应变张量 $\varepsilon$ 为对称张量，因此在三维空间中具有 6 个独立分量 （二维时为 3 个）。由于塑性变形为**等体积变形**，有： 

$$
\mathrm{Tr}(\varepsilon) = 0
\quad \Rightarrow \quad
\varepsilon_{11} + \varepsilon_{22} + \varepsilon_{33} = 0
\tag{*1.11}
$$

 这提供了一条约束关系，使独立分量减少 1 个。 因此塑性应变张量有： 

$$
6 - 1 = 5
$$

 个独立分量。

------------------------------------------------------------------------

::: center
*校对版 TD5 习题 1 解答 --- ENS Paris-Saclay, 2024年10月19日*
:::
