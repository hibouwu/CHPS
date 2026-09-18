# Méthode itérative de base. Krylov

Soient $A \in \mathbb{R}^{n \times n}$, $x$, $b \in \mathbb{R}^n$. 假设$A \in \mathbb{R}^{n \times n}$, $x$，$b \in \mathbb{R}^n$。

Soit le système linéaire $Ax = b$ (RHS: Right Hand Side, LHS: Left Hand Side). 线性系统 $Ax = b$（RHS：右端项，LHS：左端项）。

On note $r = b - Ax$ (r: Résidu) 残差$r = b - Ax$（r：残差）。

## I Méthodes et idées -> L Méthode de Jacobi, Gauss-Seidel 方法和思想 -> L Jacobi，Gauss-Seidel 方法

### I.1 Idée générale 基本思想

En partant d'une solution initiale arbitraire, on se rapproche de la solution du problème pas à pas. 从任意初始解开始，通过逐步迭代接近问题的解。

À chaque pas, on modifie une ou plusieurs composantes d'un vecteur solution approché pour "améliorer" l'itéré $k$, c'est-à-dire réduire $||b - Ax^k||$ en annihilant (mettant à jour) des composantes du résidu $r^k$. 在每一步中，我们修改近似解向量的一个或多个分量以“改进”迭代 $k$，即通过消除（更新）残差 $r^k$ 的分量来减少 $||b - Ax^k||$。

La convergence est rarement garantie. Un cadre théorique existe dans le cas des schémas différence finie pour les EDP elliptiques. 收敛性很少有保证。对于椭圆型偏微分方程的有限差分格式，存在理论框架。

Une généralisation de ce type de méthode est la méthode de Richardson (processus itératif de Richardson). 这种方法的推广是 Richardson 方法（Richardson 迭代过程）。

#### Algorithme Méthode de Richardson 里查森方法算法

Pour $x^0$, $r^0 = b - Ax^0$

while $||r^{k+1}|| > \epsilon$ do :

$$x^{k+1} = x^k + M^{-1}(b - Ax^k)$$

Où $M$ est une matrice inversible. 其中 $M$ 是一个可逆矩阵。

**Remarque 1:** Les différents $M^{-1}$ choisis correspondent chacun à une méthode. Par exemple: 注意 1：选择的不同 $M^{-1}$ 对应于不同的方法。例如：

On verra par la suite que Jacobi est une méthode de Richardson avec $M^{-1} = D^{-1}$ où $D$ est la matrice des éléments diagonaux de $A$. 随后我们将看到，Jacobi 是一种 Richardson 方法，其中 $M^{-1} = D^{-1}$，$D$ 是 $A$ 的对角元素矩阵。

Gauss-Seidel est une méthode de Richardson avec $M^{-1} = (D - E)^{-1}$ où $E$ est la matrice triangulaire inférieure de $A$. Gauss-Seidel 是一种 Richardson 方法，其中 $M^{-1} = (D - E)^{-1}$，$E$ 是 $A$ 的下三角矩阵。

#### I.21 Définition des méthodes de Jacobi et Gauss-Seidel 雅可比和高斯-赛德尔方法的定义

Soit une décomposition de $A$ telle que 假如$A$的分解为

$$
\begin{aligned}
A &= D - E - F \\
&= \text{diag}(A) - \text{tril}(A, -1) - \text{triu}(A, 1)
\end{aligned}
$$

tel que $D, E, F$ sont respectivement la matrice diagonale, la matrice triangulaire inférieure et la matrice triangulaire supérieure de $A$ et $D, E, F \in \mathbb{R}^{n \times n}$. 即 $D, E, F$ 分别是 $A$ 的对角矩阵、下三角矩阵和上三角矩阵。

$$
A = \begin{pmatrix}
 d & -f & -f & -f & -f \\
 -e & d & -f & -f & -f \\
 -e & -e & d & -f & -f \\
 -e & -e & -e & d & -f \\
 -e & -e & -e & -e & d
\end{pmatrix}
$$

##### Jacobi 雅可比方法

On annihile/met à jour la $i$-ème composante du résidu à l'itération $i$, c'est-à-dire: 我们消除/更新迭代 $i$ 中残差的第 $i$ 个分量，即：

Soit $\xi_{i}^{(k)}$ la $i$-ème composante de $x^k$ et $\beta_i$ la $i$-ème composante de $b$. 设 $\xi_{i}^{(k)}$ 为 $x^k$ 的第 $i$ 个分量，$\beta_i$ 为 $b$ 的第 $i$ 个分量。

Soit $i = 1:n$, $ (b-Ax^{k+1})_i =0$

Donc pour tous les éléments

$$
\begin{bmatrix}
\beta_1\\
\vdots\\
\beta_i\\
\vdots\\
\beta_n
\end{bmatrix}
-
\begin{bmatrix}
\sum_{j=1}^n a_{1j}\,\xi^{k+1}_j\\
\vdots\\
\sum_{j=1}^n a_{ij}\,\xi^{k+1}_j\\
\vdots\\
\sum_{j=1}^n a_{nj}\,\xi^{k+1}_j
\end{bmatrix}
= 0.
$$

pour la $i$-ème composante:

$$
\beta_i = \sum_{j=1,i\neq j}^n a_{ij}\,\xi^{k+1}_j + a_{ii}\,\xi^{k+1}_i
$$
avec on prend $\xi^{k+1}_j$ valeur à l'itération:
D'où 由此得出

$$\beta_i - a_{ii}\xi_i^{k+1} -\sum_{j=1, j \neq i}^n a_{ij}\xi_j^k = 0$$

$$a_{ii}\xi_i^{k+1} = -\sum_{j=1, j \neq i}^n a_{ij}\xi_j^k + \beta_i$$

$$\xi_i^{k+1} = \frac{1}{a_{ii}}\left(\beta_i - \sum_{j=1, j \neq i}^n a_{ij}\xi_j^k\right)$$

**Remarque2 :** On identifie que $\frac{1}{a_{ii}}$ correspond aux éléments de $D^{-1}$ et $-\sum_{j=1, j \neq i}^n a_{ij}$ correspond à $(E + F)$, avec A = D - E - F

D'où l'itération de Jacobi

$$
\boxed{(1)\; x^{k+1} = D^{-1}(E + F)x^k + D^{-1}b}
$$

ou这样

$$
\boxed{(2)\; Dx^{k+1} = (D - A)x^k + b}
\qquad
(1)\text{ et }(2)\text{ sont équivalents.}
$$
ou

$$
\boxed{(3)\; x^{k+1} = x^k + D^{-1}(b - Ax^k)}
$$

**Remarque :** $(2)$ est sous la forme $Mx^{k+1} = Mx^k + b$ (Richardson avec $M^{-1} = D^{-1}$)

##### Gauss-Seidel 高斯-赛德尔方法

On corrige la $i$-ème composante de la solution à l'itération $i$ pour annihiler la $i$-ème composante du résidu en mettant à jour immédiatement la solution après qu'une nouvelle composante soit déterminée. 我们在迭代 $i$ 中修正解的第 $i$ 个分量，以消除残差的第 $i$ 个分量，在确定新分量后立即更新解。

$\xi_{i}$ i=1:n est modifié dans un vecteur chaque pas de la relaxation (modification d'une composante i) au pas i.

$$
\beta_i - \sum_{j=1}^{i-1} a_{ij}\,\xi^{k+1}_j + a_{ii}\,\xi^{k+1}_i + \sum_{j=i+1}^n a_{ij}\,\xi^k_j = 0
$$

avec $E = \sum_{j=1}^{i-1} a_{ij}$, $F = \sum_{j=i+1}^n a_{ij}$, $D = a_{ii}$

$$\xi_i^{k+1} = \frac{1}{a_{ii}}\left(- \sum_{j=1}^{i-1} a_{ij}\xi_j^{k+1} - \sum_{j=i+1}^n a_{ij}\xi_j^k + \beta_i \right)$$

Sous forme vectorielle:

$$b + Ex^{k+1} - Dx^{k+1} + Fx^k = 0$$

**Itération de Gauss-Seidel :**

$$
\boxed{(4)\; x^{k+1} = (D - E)^{-1}F x^k + (D - E)^{-1}b}
$$

ou Forward GS:

$$
\boxed{(5)\; (D - E)x^{k+1} = Fx^k + b}
$$

Backward GS:

$$
\boxed{(6)\; (D - F)x^{k+1} = E x^k + b}
$$

**Richardson :**

$$
\boxed{(7)\; x^{k+1} = x^k + (D - E)^{-1}(b - Ax^k)}
$$

Gauss-Seidel $\Leftrightarrow$ Richardson avec $M^{-1} = (D - E)^{-1}$.

**Autres formes et découpage :**

$$
A = D - E - F
$$
$$
A = M - N
$$

**Remarque:** Gauss-Seidel $\Leftrightarrow$ Richardson avec $M^{-1} = (D - E)^{-1}$

## II Convergence 收敛性

### II.1 Matrice d'itération (Matrice de transfert d'erreur) 矩阵迭代（误差传递矩阵）

Soit une itération de Richardson  

$$
\boxed{(8)\; x^{k+1} = x^k + M^{-1}(b - Ax^k)}
$$  

d'où  

$$
\begin{aligned}
x^{k+1} &= x^k + M^{-1}b - M^{-1}Ax^k \\
&= \underbrace{(I - M^{-1}A)}_{G}x^k + M^{-1}b
\end{aligned}
$$  

On pose $G = I - M^{-1}A$.

$$
\boxed{(9)\; x^{k+1} = G x^k + M^{-1}b}
$$  

$G$ est appelée "matrice d'itération" ou "matrice de transfert d'erreur".  

La convergence d'un tel processus est donnée par (Axelsson 1976, Siaïret 1994).

$$\boxed{(10)\; e^k = G^k e^{0}}$$

où $e^0 = x^0 - x^*$ et $e^k = x^k - x^*$, avec $x^*$ la solution à convergence ($\lim_{k\to\infty} x^k = x^*$).  

$$
G \cdots G\,e^0 = G^k e^0 \quad \Rightarrow \quad e^{(k)} = G^k e^0
$$
car $Ge^0 = e^{(1)}$, $Ge^{(1)} = e^{(2)}$, ..., $Ge^{(k-1)} = e^{(k)}$.

$G = I - M^{-1}A$ est une opération de transfert d'erreur.

### II.2 Convergence - résultats généraux 一般收敛结果

On considère $A$ inversible.On cherche à résoudre $Ax = b$.On note $x^*$ la solution de ce système à convergence d'une méthode itérative qui s'écrit sous la forme d'un processus de Richardson. 我们考虑可逆矩阵 $A$。我们要解 $Ax = b$。设 $x^*$ 为该线性系统的解，且该解通过迭代方法以 Richardson 过程形式收敛得到。

a) Si le processus de Richardson converge, a-t-on la solution du système original ? 如果 Richardson 过程收敛，是否得到原始系统的解？

Si $x^{k+1} = G x^k + M^{-1}b$ converge, alors

$$\boxed{(11)\; x^* = G x^* + M^{-1}b}$$

Remarque : $G = I - M^{-1}(M - N) = I - I + M^{-1}N = M^{-1}N$.

Si $A = M - N$, la solution de (11) est identique à celle de $Ax^* = b$ et on écrit $x^{k+1} = M^{-1}N x^k + M^{-1}b$.

La limite satisfait $M x^* = N x^* + b \Leftrightarrow (M - N) x^* = b \Leftrightarrow A x^* = b$.

b) Sous quelle condition le processus itératif de Richardson converge ? Richardson 迭代过程在什么条件下收敛？

Si $(I - G)$ est inversible, 如果 $(I - G)$ 可逆，

**Remarque :** $I - G = I - (I - M^{-1} A ) = M^{-1} A$  注意：$I - G = M^{-1} A$。

alors il existe une solution $x^*$ à l'équation (11). 因此方程 (11) 存在解 $x^*$。

Soit $e^{(k)} = G^k e^0$ (10). 记 $e^{(k)} = G^k e^0$。

Le rayon spectral de $G$ doit être strictement inférieur à 1 pour que $e^k$ converge vers 0. 要使 $e^k \to 0$，必须有谱半径 $\rho(G) < 1$。

De plus, on peut écrire chaque itération sous la forme 此外，每次迭代可写为：

$$
x^{k+1} - x^k = G\,(x^k - x^{k-1}) = G^k(M^{-1}b - (I - G)x^0)
$$

Si l'itération converge pour tout $x^0$ et $M^{-1}b$, alors pour tout $v \in \mathbb{R}^n$, $G^k v$ converge vers 0. 如果对任意初值和右端都收敛，则 $G^k v \to 0$ 对任意 $v$ 成立。  

Donc $\rho(G) < 1$ ( $\rho(G)$ rayon spectral de $G$). 因此必须有 $\rho(G) < 1$。

**Théorème :** 定理  
Soit $G$ une matrice carrée telle que $\rho(G) < 1$, alors $(I - G)$ est inversible et l'itération $x^{k+1} = G x^k + f, f \in \mathbb{R}^n$ converge pour tout $f$ et tout $x^0$.  
Réciproquement, si $x^{k+1} = G x^k + f$ converge pour tout $f$ et $x^0$, alors $\rho(G) < 1$. 如果 $\rho(G)<1$，迭代对任意 $f,x^0$ 收敛；反之若对任意 $f,x^0$ 收敛，则 $\rho(G)<1$。

**Rappel :** définition du rayon spectral. 提醒：谱半径定义  

$$\rho(G) = \max\{|\lambda|,\, \lambda \in \operatorname{spec}(G)\}$$

$\operatorname{spec}(G)$ est l'ensemble des valeurs propres de $G$.  $\operatorname{spec}(G)$ 为 $G$ 的特征值集合。

$Rq:$ $\rho(G)$ est cher à calculer. En pratique, on utilise $\rho(G) \leq \|G\|$. 备注：直接算谱半径昂贵，常用估计 $\rho(G) \le \|G\|$。

### II.3 Convergence pour les matrices tridiagonales et cas poisson 1D 三对角矩阵和一维泊松问题的收敛性

#### II.3.0 Résultats généraux pour le calcul aux valeurs propres des matrices tridiagonales du type des schéma FD 3 points 三点有限差分格式类型的三对角矩阵特征值计算的一般结果

**Matrice de Toeplitz**  
$A \in \mathbb{R}^{n \times n}$,
$$
\begin{aligned}
A &= \operatorname{Trid}(a,b,c)\\
&= \begin{pmatrix}
b & c &  &  &  \\
a & b & c &  &  \\
 & a & b & \ddots &  \\
 &  & \ddots & \ddots & c \\
 &  &  & a & b
\end{pmatrix}
\end{aligned}
$$

(cas $ac > 0$, $\operatorname{sign}(a) = \operatorname{sign}(c)$).

Soit les vecteurs $\{ X_{jk} \},\ k = 1\!:\!n$ dont les composantes sont  
$$X_{j,k} = \sqrt{\frac{2}{n+1}}\left(\sqrt{\frac{a}{c}}\right)^j \sin(j\,\theta_k), \quad \theta_k = \frac{k\pi}{n+1}$$

D'où  
$$
\begin{aligned}
(A X_k)_l &= \sum_{j=1}^n A_{lj} X_{j,k} \\
&= a\,X_{l-1,k} + b\,X_{l,k} + c\,X_{l+1,k} \\
&= \Bigl[b + \sqrt{ac}\; \frac{\operatorname{sign}(a)\sin((l-1)\theta_k)+\operatorname{sign}(c)\sin((l+1)\theta_k)}{\sin(l\,\theta_k)}\Bigr] X_{l,k}
\end{aligned}
$$

$$
(A X_k)_l = \lambda_k\,X_{l,k}
$$

Donc  
$$
\boxed{(12)\; \lambda_k = b + 2\,\operatorname{sign}(c)\,\sqrt{ac}\,\cos(\theta_k)}
$$

#### II.3.1 Rayon spectral de $G_J$ (G de Méthode Jacobi) pour Poisson 1D 一维泊松问题的 $G_J$ 的谱半径

Soit $G_J = I - M^{-1}_J A = I - D^{-1}A$ avec $A = D - E - F$. On a $G_J = D^{-1}(E - F)$. 设 $G_J = I - D^{-1}A$，其中 $A = D - E - F$，故 $G_J = D^{-1}(E - F)$。

Soit $\delta \in \mathbb{C}$ valeur propre de $G_J$ et $v$ son vecteur propre associé ($v \ne 0$) : 设 $\delta$ 为 $G_J$ 特征值，$v$ 为对应非零特征向量：

$$
G_J v = \delta v \iff D^{-1}(E + F)v = \delta v \iff (E + F)v = \delta D v \iff (\delta D - E - F)v = 0.
$$

Considérons Poisson 1D. Il existe une valeur propre $\lambda_k$ nulle pour la matrice $\operatorname{Trid}(-1, 2\delta, -1)$. Le spectre de cette matrice est (12) : 对一维泊松，矩阵 $\operatorname{Trid}(-1, 2\delta, -1)$ 的谱由 (12) 给出，并存在 $\lambda_k=0$。

$$\lambda_k = 2\delta - 2\cos \theta_k,$$

La condition $\lambda_k = 0$ donne les valeurs propres $\delta_k$ telles que  由 $\lambda_k = 0$ 得到
$$\delta_k = \cos \theta_k, \quad k = 1\!:\!n, \quad \theta_k = \frac{k\pi}{n+1}.$$

Donc  因此
$$
\rho(G_J) = \cos\left(\frac{\pi}{n+1}\right) = \cos(\pi h) = 1 - \frac{\pi^2}{2}h^2 + o(h^2) < 1,
$$

avec $h = \tfrac{1}{n+1}$ le pas de discrétisation. 其中 $h = \tfrac{1}{n+1}$ 为步长。

Vitesse de convergence = rayon spectral.  收敛速率即谱半径。  
$$
e^k = C\,\delta_k^k e^0, \qquad \|e^k\| \le \rho(G_J)^k \|e^0\|.
$$

#### II.3.2 Rayon spectral de $G_{GS}$ pour Poisson 1D 一维泊松问题的 $G_{GS}$ 的谱半径

Soit

$$
G_{GS} = (D - E)^{-1}F = I - (D - E)^{-1}A.
$$

On procède comme pour II.3.1 appliqué à $G_J$. 处理方式与 II.3.1 对 $G_J$ 相同。

Soit $\delta'$ valeur propre de $G_{GS}$ avec vecteur propre $v' \neq 0$ : 设 $\delta'$ 为 $G_{GS}$ 特征值，$v' \ne 0$ 为特征向量：

$$
G_{GS} v' = \delta' v' \iff (D - E)^{-1} F v' = \delta' v' \iff F v' = \delta'(D - E) v'
$$

$$
\iff (\delta'(D - E) - F) v' = 0 \iff (\delta' D - \delta' E - F) v' = 0.
$$

Considérons Poisson 1D. Il existe une valeur propre $\lambda_k'$ nulle pour la matrice $\operatorname{Trid}(-\delta', 2\delta', -1)$. Le spectre de cette matrice, en appliquant (12), est 对一维泊松，$\operatorname{Trid}(-\delta', 2\delta', -1)$ 的谱由 (12) 给出，存在 $\lambda_k'=0$。

$$
\lambda_k' = 2\delta' - 2\sqrt{\delta'} \cos \theta_k.
$$

La condition $\lambda_k' = 0$ donne les valeurs propres $\delta_k'$ telles que 由 $\lambda_k'=0$ 得

$$
\delta_k' = \cos^2 \theta_k, \quad k = 1\!:\!n, \quad \theta_k = \frac{k\pi}{n+1}, \quad h = \frac{1}{n+1}.
$$

Donc 因此

$$
\rho(G_{GS}) = \cos^2\left(\frac{\pi}{n+1}\right) = \cos^2(\pi h) = [\rho(G_J)]^2.
$$

Remarque : $\rho(G_J) = \cos \tfrac{\pi}{n+1}$ et $\rho(G_{GS}) = [\rho(G_J)]^2$, autrement dit deux transferts d’erreur de Jacobi sont équivalents à un transfert d’erreur de Gauss-Seidel. 注：$\rho(G_{GS}) = [\rho(G_J)]^2$，即两次 Jacobi 误差传递等效于一次 Gauss-Seidel。
