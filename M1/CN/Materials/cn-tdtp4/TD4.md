# TD/TP 4 – Calcul numérique : exploitation des structures et calcul creux / 计算数值：矩阵结构与稀疏计算

T. Dufaud (thomas.dufaud@uvsq.fr) — M1 CHPS / T. Dufaud（thomas.dufaud@uvsq.fr）— M1 CHPS

Cette fiche de TD/TP est associée au cours de calcul numérique sur l'exploitation des structures de matrices et les matrices creuses. Les exercices sont à réaliser sur feuille puis à implémenter en Scilab. Ils seront approfondis en TP.
本次 TD/TP 配合课程内容，围绕矩阵结构利用与稀疏矩阵；练习先纸笔完成，再用 Scilab 实现，并在 TP 中深入。

## Exercice 1 — Factorisation $LDL^T$ pour $A$ symétrique / 练习 1：对称矩阵的 $LDL^T$ 分解

À partir de la factorisation LU d'une matrice symétrique, on peut obtenir une factorisation $LDL^{T}$.
对称矩阵的 LU 分解可转换为 $LDL^{T}$ 分解。

1) Montrez l'existence et l'unicité de la factorisation $A = LU$ avec $L$ unitaire inférieure.  
1）证明 $A=LU$（$L$ 为单位下三角）的存在与唯一性。
2) Montrez que si $A$ est symétrique alors il existe une factorisation $A = LDL^{T}$ unique.  
2）证明若 $A$ 对称，则存在唯一的 $A=LDL^{T}$ 分解。
3) Proposez un algorithme pour la factorisation $LDL^T$.  
3）给出 $LDL^{T}$ 分解的算法。

## Exercice 2 — LU sur une matrice tridiagonale / 练习 2：三对角矩阵的 LU

Appliquer la méthode de Gauss à la matrice tridiagonale suivante :
将高斯消元应用于下列三对角矩阵：

$$
A = \begin{pmatrix}
 a_{1} & c_{1} & 0      & \dots  & 0        & 0      \\
 b_{1} & a_{2} & c_{2}  & \dots  & 0        & 0      \\
       &       & \ddots &        &          &        \\
       &       &        & \ddots &          &        \\
 0     & 0     & 0      & \dots  & a_{n-1}  & c_{n-1}\\
 0     & 0     & 0      & \dots  & b_{n-1}  & a_{n}
\end{pmatrix}.
$$

Montrer que, sans pivot, cette méthode réduit la matrice $A$ à sa décomposition LU :
证明无需主元时，该方法将 $A$ 化为 LU 分解：

$$
A = LU =
\begin{pmatrix}
 1 & 0 & \dots & 0 & 0 \\
 e_{1} & 1 & \dots & 0 & 0 \\
       &   & \ddots &   &   \\
 0 & 0 & \dots & 1 & 0 \\
 0 & 0 & \dots & e_{n-1} & 1
\end{pmatrix}
\begin{pmatrix}
 d_{1} & c_{1} & \dots & 0 & 0 \\
 0 & d_{2} & \dots & 0 & 0 \\
   &       & \ddots &   &   \\
 0 & 0 & \dots & d_{n-1} & c_{n-1} \\
 0 & 0 & \dots & 0 & d_{n}
\end{pmatrix}.
$$

Les $e_i$ et $d_j$ (pour $2 \leq i \leq n$ et $1 \leq j \leq n - 1$) sont facilement calculables. Écrire, analyser et implanter l'algorithme de cette décomposition.
其中 $e_i$ 与 $d_j$（$2\le i\le n$，$1\le j\le n-1$）易于计算。请写出、分析并实现该分解算法。

## Exercice 3 — Cas de test pour valider LU tridiagonale / 练习 3：三对角 LU 的验证案例

On considère l'équation de la chaleur dans un milieu immobile linéaire homogène avec terme source et isotrope :
考虑静止、线性、均匀且各向同性介质中的热传导方程（含源项）：

$$
\begin{cases}
-k\, \dfrac{\partial^{2} T}{\partial x^{2}} = g, & x \in ]0,1[ \\
T(0) = T_{0} \\
T(1) = T_{1}
\end{cases}\tag{1}
$$

où $g$ est un terme source, $k > 0$ le coefficient de conductivité thermique, et $T_0 < T_1$ les températures au bord du domaine considéré.
其中 $g$ 为源项，$k>0$ 为导热系数，$T_0<T_1$ 为边界温度。

On propose de résoudre cette équation par une méthode de différences finies centrées d'ordre 2. On discrétise le domaine 1D selon $n + 2$ nœuds $x_{i}$, $i = 0,1,2,\ldots,n+1$, espacés d'un pas $h$ constant.
采用二阶中心差分离散 1D 区间，节点数为 $n+2$，记 $x_i$，$i=0,1,\dots,n+1$，步长 $h$ 恒定。

En chaque nœud l'équation discrète s'écrit :
在每个节点上，离散方程为：

$$
-k \left(\frac{\partial^{2} T}{\partial x^{2}}\right)_{i} = g_{i}.\tag{2}
$$

1) Approximer la dérivée seconde de $T$ au moyen d'un schéma centré d'ordre 2.  
1）用二阶中心差分逼近 $T$ 的二阶导。  
2) Écrire le système linéaire de dimension $n$ correspondant au problème (1).  
2）写出对应问题 (1) 的 $n$ 维线性系统。

Dans la suite du TD on considère qu'il n'y a pas de source de chaleur, i.e. $g = 0$. La solution analytique est :
在后续中设无热源，即 $g=0$。解析解为：

$$
T(x) = T_{0} + x\,(T_{1} - T_{0}).\tag{3}
$$

## Exercice 4 — Implémentation Scilab et validation / 练习 4：Scilab 实现与验证

1) Implémenter l'algorithme de l'exercice 2 pour résoudre un système linéaire tridiagonal.  
1）实现练习 2 的算法，求解三对角线性系统。  
2) Valider votre implémentation numériquement et en complexité temps.
2）从数值正确性与时间复杂度角度验证实现。
