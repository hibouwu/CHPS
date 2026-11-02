# 附录 B：向量与张量的数学基础

原文：[Annexe 2 PDF](../IMMC_CM_Annexe2_2025-2026.pdf) · [法文文本](../IMMC_CM_Annexe2_2025-2026.md)

## B.1 向量与二阶张量

**B.1 Vecteurs et tenseurs**

**B.1.1 Vecteurs**

Un vecteur est représenté sous la forme :

où $V _ { 1 }$ , $V _ { 2 }$ et $V _ { 3 }$ sont les composantes de $\vec { V }$ dans la base $( \vec { e } _ { 1 } , \vec { e } _ { 2 } , \vec { e } _ { 3 } )$

En utilisant la convention de sommation (sommation sur les indices répétés), le vecteur $\vec { V }$ s’écrit aussi :

**B.1.2 Tenseurs d’ordre 2**

Un tenseur du second ordre A est une entité mathématique qui est une généralisation de la notion de vecteur. Il peut être représenté par une matrice $3 \times 3$ , lorsqu’on travaille en dimension 3. Il est défini à partir de ses composantes $A _ { i j }$ par :

avec $\otimes$ représentant le produit tensoriel.

Un tenseur du second ordre A peut être vu comme la représentation d’une application linéaire dans la base $( \vec { e } _ { 1 } , \vec { e } _ { 2 } , \vec { e } _ { 3 } )$ . Si $\vec { W } = \mathbb { A } \vec { V }$ , les composantes du vecteur W sont alors données par :

ou sous forme plus synthétique via la notation indicielle et la convention de sommation d’Einstein) :

**Décomposition en parties symétrique et antisymétrique**

Un tenseur A est dit :

— symétrique si $\mathbb { A } = \mathbb { A } ^ { \top }$

— antisymétrique si $\mathbb { A } = - \mathbb { A } ^ { \top }$

On peut toujours décomposer un tenseur d’ordre 2 en parties symétrique sym(A) et anti symétrique asym(A) :

**Décomposition en parties sphérique et déviatorique**

Un tenseur d’ordre 2 A est dit :

— sphérique si A = αI avec α scalaire

— déviatorique si Tr $\mathbb { A } = 0$

On peut toujours décomposer un tenseur d’ordre 2 en parties sphérique sphe(A) et déviatorique dev(A) :

**Tenseur d’ordre 2 symétrique**

Lorsqu’un tenseur d’ordre 2 A est symétrique, on peut le représenter de manière allégée, avec uniquement la partie triangulaire supérieure.

La symétrie d’un tenseur d’ordre 2 simplifie les expressions des opérateurs différentiels dans les différents systèmes de coordonnées (notamment cylindriques et sphériques), se référer au formulaire.

**B.2 Algèbre tensorielle**

在三维 Euclidean 空间的正交归一基 $(\mathbf e_1,\mathbf e_2,\mathbf e_3)$ 中，

$$\mathbf V=V_1\mathbf e_1+V_2\mathbf e_2+V_3\mathbf e_3=V_i\mathbf e_i.\tag{B.1–B.2}$$

重复指标默认求和。二阶张量在线性映射中推广向量概念，在指定基中以 $3\times3$ 矩阵表示：

$$\mathbf A=A_{ij}\mathbf e_i\otimes\mathbf e_j,\qquad
\mathbf W=\mathbf A\mathbf V\ \Longrightarrow\ W_i=A_{ij}V_j.\tag{B.3–B.5}$$

一个矩阵表示依赖基底，张量本身所描述的线性映射不依赖基底。

任意二阶张量可作两种分解：

$$\operatorname{sym}\mathbf A=\frac{\mathbf A+\mathbf A^{\mathsf T}}2,\quad
\operatorname{asym}\mathbf A=\frac{\mathbf A-\mathbf A^{\mathsf T}}2.\tag{B.6}$$

$$\operatorname{sphe}\mathbf A=\frac{\operatorname{tr}\mathbf A}{3}\mathbf I,\quad
\operatorname{dev}\mathbf A=\mathbf A-\frac{\operatorname{tr}\mathbf A}{3}\mathbf I.\tag{B.7}$$

对称张量只需记录六个独立分量；原讲义只写上三角时，下三角由对称性补齐，绝不是下三角为零（B.8）。

## B.2.1 指标记号

**B.2.1 Notation indicielle**

**Convention de sommation d’Einstein**

La convention d’Einstein consiste à omettre les signes de somme ($\sum$), afin d’alléger les notations notamment. On effectue, de manière implicite, les sommes sur les indices répétés. Ces indices sont considérés comme « muets », car on peut changer leur nom sans changer la valeur du résultat. On écrira donc le terme de droite, plutôt que le terme de gauche :

**Dérivée partielle**

On note la dérivée partielle de la quantité $\bullet$ par rapport à la coordonnée spatiale $i$ ($x_i$ en description eulérienne, $X_i$ en description lagrangienne) :

**Symbole de Kronecker**

On définit le symbole de Kronecker $\delta$ comme suit :

Ce symbole revient à la matrice identité I.

**Symbole de Levi-Civita (ou tenseur de spin)**

On définit le symbole de Levi-Civita $\varepsilon ,$ correspondant au tenseur de spin (du $3 ^ { \mathsf { e } }$ ordre), comme suit :

Ce symbole revient au « tenseur de spin », du $3 ^ { \mathsf { e } }$ ordre. Voici plusieurs formules utiles :

Einstein 约定：同一项中出现两次的指标求和，是可改名的哑指标；只出现一次的是自由指标。等式两边自由指标必须一致。例如

$$\sum_{j,k}a_{ij}b_{jk}c_k=a_{ij}b_{jk}c_k.\tag{B.9}$$

$$a_{,i}=\partial a/\partial x_i\quad\text{或}\quad\partial a/\partial X_i,\tag{B.10}$$

按欧拉或拉格朗日描述选择相应坐标。

Kronecker 符号 $\delta_{ij}$ 在 $i=j$ 时为 1，否则为 0（B.11）。Levi-Civita 符号在 $(1,2,3)$ 的偶置换时为 1，奇置换时为 $-1$，存在重复指标时为 0（B.12）。

$$\epsilon_{ijk}\epsilon_{ijk}=6,\quad
\epsilon_{ijk}\epsilon_{ijn}=2\delta_{kn},\quad
\epsilon_{ijk}\epsilon_{ilm}=\delta_{jl}\delta_{km}-\delta_{jm}\delta_{kl}.\tag{B.13–B.15}$$

## B.2.2 二阶张量的不变量

**B.2.2 Invariants d’un tenseur d’ordre 2**

On appelle invariants d’un tenseur du second ordre $\mathbb { A }$ les $I _ { n } ( \mathbb { A } )$ , ou en abrégé $I _ { n } ,$ les scalaires définis comme suit :

本讲义使用幂迹作为三个不变量：

$$I_1=\operatorname{tr}\mathbf A,\quad I_2=\operatorname{tr}(\mathbf A^2),\quad I_3=\operatorname{tr}(\mathbf A^3).\tag{B.16}$$

它们不是另一些教材使用的基本对称不变量 $(\operatorname{tr}\mathbf A,\frac12[(\operatorname{tr}\mathbf A)^2-\operatorname{tr}(\mathbf A^2)],\det\mathbf A)$。遇到跨教材公式时应先核对定义。

## B.2.3 向量运算

**B.2.3 Opérations sur les vecteurs**

**Produit scalaire**

Le produit scalaire entre deux vecteurs $\vec { V }$ et $\vec { W }$ , noté $\vec { V } \cdot \vec { W }$ , est défini par :

— Il correspond au produit contracté simple entre les deux vecteurs $\vec { V }$ et $\vec { W }$ .

— Il est indépendant de la base dans laquelle les vecteurs $\vec { V }$ et $\vec { W }$ sont exprimés.

**Produit vectoriel**

Le produit vectoriel entre deux vecteurs $\vec { V }$ et $\vec { W }$ , noté $\vec { V } \wedge \vec { W }$ est défini en dimension 3 par :

**Produit mixte de trois vecteurs**

Le produit mixte de trois vecteurs $\vec { U } , \vec { V }$ et $\vec { W }$ est noté $\vec { U } \wedge \vec { V } ) \cdot \vec { W }$ et est défini par :

— Si ce produit mixte est nul, alors les trois vecteurs $\vec { U }$ , $\vec { V }$ et $\vec { W }$ sont coplanaires.

— Il est invariant par permutation circulaire :

**Déterminant de deux vecteurs**

Le déterminant de deux vecteurs $\vec { V }$ et $\vec { W }$ est noté $\operatorname* { d e t } ( { \vec { V } } , { \vec { W } } )$ et est défini par :

où $\theta$ représente l’angle orienté formé par les deux vecteurs $\vec { V }$ et $\vec { W }$ . La valeur absolue du déterminant de deux vecteurs correspond à l’aire du parallélogramme défini par ces deux vecteurs.

**Déterminant de trois vecteurs**

Le déterminant de trois vecteurs $\vec { U } , \vec { V }$ et $\vec { W }$ est noté det $( \vec { U } , \vec { V } , \vec { W } )$ et est défini par :

Il correspond également au produit mixte (en dimension 3) des trois vecteurs $\vec{U}$, $\vec{V}$ et $\vec{W}$, noté $[\vec{U},\vec{V},\vec{W}]=(\vec{U}\wedge\vec{V})\cdot\vec{W}$. La valeur absolue du déterminant de trois vecteurs est égale au volume du parallélépipède défini par ces trois vecteurs.

$$\mathbf V\cdot\mathbf W=V_iW_i.\tag{B.17}$$

点积为标量，与使用的正交基无关。

$$\mathbf V\times\mathbf W=\epsilon_{ijk}V_jW_k\mathbf e_i
=(V_2W_3-V_3W_2,\ V_3W_1-V_1W_3,\ V_1W_2-V_2W_1).\tag{B.18}$$

> **译注：**原 PDF 此式的部分分量有重复项，属排印错误；上式按叉积定义写出。

$$[\mathbf U,\mathbf V,\mathbf W]=(\mathbf U\times\mathbf V)\cdot\mathbf W.\tag{B.19}$$

混合积在循环置换下不变（B.20–B.21）；为零时三向量共面。

$$\det(\mathbf V,\mathbf W)=V_1W_2-V_2W_1=\|\mathbf V\|\|\mathbf W\|\sin\theta.\tag{B.22}$$

此式为二维有向面积。原 PDF 末项的向量点积写法应理解为模长乘积。

$$\begin{aligned}
\det(\mathbf U,\mathbf V,\mathbf W)
&=U_1(V_2W_3-V_3W_2)-U_2(V_1W_3-V_3W_1)\\
&\quad+U_3(V_1W_2-V_2W_1).
\end{aligned}\tag{B.23–B.25}$$

它等于混合积，其绝对值为三向量所张平行六面体的体积。

## B.2.4 张量自身的运算

**B.2.4 Opérations sur les tenseurs**

**Trace d’un tenseur d’ordre 2**

La trace d’un tenseur du second ordre A est la somme des termes de la diagonale de A. Elle s’écrit :

**Transposée d’un tenseur d’ordre 2**

La transposée d’un tenseur du second ordre A est notée $\mathbb { A } ^ { \top }$ et est définie par :

**Transposée de l’inverse d’un tenseur d’ordre 2**

La transposée de l’inverse d’un tenseur d’ordre 2 est notée $\mathbb { A } ^ { - T }$ et est définie par :

**Déterminant d’une matrice ou d’un tenseur d’ordre 2**

Le déterminant d’une matrice carrée (ou d’un tenseur d’ordre 2) notée $\mathbb { A } ,$ dont les composantes sont notées $A _ { i j } ,$ , correspond en dimension 3, au déterminant de trois vecteurs $\vec { U } , \vec { V }$ et $\vec { W }$ , dont les composantes sont respectivement $A _ { i 1 } , A _ { i 2 }$ et $A _ { i 3 }$

On peut noter que det $\mathrm { ( A ) = d e t ( A ^ { T } ) }$ .

$$\operatorname{tr}\mathbf A=A_{ii}=A_{11}+A_{22}+A_{33},\tag{B.26}$$
$$[\mathbf A^{\mathsf T}]_{ij}=A_{ji},\qquad
\mathbf A^{-\mathsf T}=(\mathbf A^{-1})^{\mathsf T}.\tag{B.27–B.28}$$

行列式为三列向量的混合积，$\det\mathbf A=\det\mathbf A^{\mathsf T}$（B.29）。逆仅在行列式非零时存在。

## B.2.5 缩并

**B.2.5 Opérations entre vecteurs et/ou tenseurs d’ordre 2**

**Produit contracté simple**

Le produit contracté simple (matérialisé par le symbole « point central » ·) entre deux tenseurs A et B respectivement d’ordre p et q, donne un tenseur C d’ordre n avec :

En fonction de l’ordre des tenseurs A et B, l’opération diffère :

Le cas particulier le plus connu étant celui entre deux vecteurs qui n’est autre que le produit scalaire.

**Produit contracté double**

Le produit contracté double (matérialisé par le symbole « deux points » :) entre deux tenseurs A et B respectivement d’ordre p et $q$ , donne un tenseur C d’ordre n avec :

En fonction de l’ordre des tenseurs A et B, l’opération diffère :

阶数分别为 $p,q$ 的张量作一次缩并后阶数为 $p+q-2$（B.30）：

$$\mathbf a\cdot\mathbf b=a_ib_i,\qquad
\mathbf A\mathbf b=A_{ij}b_j\mathbf e_i,\qquad
\mathbf a\cdot\mathbf B=a_iB_{ij}\mathbf e_j,\tag{B.31–B.33}$$
$$\mathbf A\mathbf B=A_{ik}B_{kj}\mathbf e_i\otimes\mathbf e_j.\tag{B.34}$$

双缩并后的阶数为 $p+q-4$。本讲义约定

$$\mathbf A:\mathbf B=\operatorname{tr}(\mathbf A\mathbf B)=A_{ij}B_{ji}.\tag{B.35–B.36}$$

其中任一张量对称时等于 $A_{ij}B_{ij}$（B.37）。其他文献常直接用 $A_{ij}B_{ij}=\operatorname{tr}(\mathbf A^{\mathsf T}\mathbf B)$ 定义冒号，对非对称矩阵必须留意差别。

四阶张量作用于二阶张量时，本讲义写作 $C_{ij}=A_{ijkl}B_{lk}$；$\mathbf B$ 对称时即 $A_{ijkl}B_{kl}$（B.38–B.39）。
