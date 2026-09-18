# Calcul Numérique - Algèbre linéaire dense 数值计算 - 稠密线性代数

T.DUFAUD
T.DUFAUD

UVSQ
凡尔赛-圣康坦大学（UVSQ）

UNIVERSITE DE VERSAILLES
凡尔赛大学

ST-QUENTIN-EN-YVELINES
圣康坦昂伊夫林

M1 CHPS - 5 / 11 / 2025
M1 CHPS - 2025 年 11 月 5 日

## Plan

Rappel: Le calcul numérique et la simulation numérique  
回顾：数值计算与数值仿真
Algèbre linéaire : bases d'implémentation  
线性代数：实现基础
3 Résolution de système linéaire
三、线性系统求解

- Systeme triangulaire  
- 三角系统
- Methode de Gauss  
- 高斯法

- Factorisation LU  
- LU 分解
- Pivot
- 枢轴

## Rappel: Le calcul numérique et la simulation numérique 回顾：数值计算与数值仿真

En quelques mots 简而言之

- Réaliser des expériences sur des machines de calcul  
- 在计算机上开展实验

- Experiences dangereuses ou impossible à produit (Nucléaire, Chimie, Astro-physique)  
  处理危险或无法实际开展的试验（核工业、化学、天体物理）
Utilisée dans l'industrie pour réduire les temps et les coûts de conception (exemple : industrié automobile)  
用于工业领域以降低设计时间和成本（例如汽车工业）
- De plus en plus utilisée (Nouveaux domaines d'applications, élargissement de la communauté scientifique (ex : Maison de la Simulation))  
  应用愈发广泛（新的应用领域，科研社区扩大，例如 Maison de la Simulation）
- Activité pluridisciplinaire (Domaine d'application, Modélisation, Schéma numérique, Algorithme de résolution (parallèle), Programmation (parallele), Post-traitement)
  一项跨学科活动（应用领域、建模、数值格式、求解算法（并行）、编程（并行）、后处理）

### Au coeur de la simulation 仿真的核心

- Intervient après la modélisation du problème  
- 在问题建模之后发挥作用

- Choix d'une méthode de résolution adaptée : comprendre le problème, la manière dont le problème est posée contraint le choix de méthode (Propriétés des objets mathématiques à manipuler)  
  选择合适的求解方法：理解问题本身，问题的表述方式限制了方法的选择（需操作对象的数学性质）
- Étude des complexités et de la stabilité numérique : Avoir un résultat juste pour un coût minimum (mémoire + temps CPU)  
  研究复杂度与数值稳定性：以最小代价（内存 + CPU 时间）获得正确结果
- Évolution des architectures des machines de calcul : les machines évoluant, les algorithmes doivent être adaptés ou bien inventés.
  计算架构持续演进：机器变化促使算法需要调整甚至重新设计。

### Plusieurs types de problèmes 多类问题

- Probleme stationnaire (ex: recherche de zéro par bissection)  
  稳态问题（如二分法求零点）
- Probleme dynamique (ex: chute d'un corps par Euler (EDO))  
  动态问题（如用欧拉法求解物体下落的常微分方程）
- Probleme discret lineaire (ex : Écoulement stationnaire dans un milieu poreux, équation de Darcy : résolution par méthodes directes ou itératives)
  线性离散问题（如多孔介质中的稳态流动，Darcy 方程：可用直接或迭代方法求解）

### Objectifs 目标

- Comprétre les contraintes du calcul en précision finie  
  理解有限精度计算的限制
- Implementer un algorithme de calcul et l'analyser  
  实现并分析计算算法
- Améliorer un algorithme : en termes de temps d'exécution, d'occupation mémoire et de stabilité numérique.  
  改进算法：提升执行时间、内存占用和数值稳定性。
- Utiliser l'algebre linéaire pour la compréhension des problématiques du calcul numérique.
  运用线性代数理解数值计算中的问题。

## Algèbre linéaire : bases d'implémentation 线性代数：实现基础

### Opérations vectorielles 向量运算

Soient  $a\in \mathbb{R},x,y,z\in \mathbb{R}^n$ 设 $a\in \mathbb{R}, x,y,z\in \mathbb{R}^n$

- Multiplication d'un vecteur par un scalaire
  向量与标量相乘

$$
z = a x \Rightarrow z _ {i} = a x _ {i}
$$

- Addition de deux vecteurs
  两个向量相加

$$
z = x + y \Rightarrow z _ {i} = x _ {i} + y _ {i}
$$

- Produkt scalaire
  点积

$$
a = x ^ {T} y \Rightarrow a = \sum_ {i = 1} ^ {n} x _ {i} y _ {i}
$$

- Produkt d'Hadamard (Terme à terme)
  Hadamard 逐项乘积

$$
z = x. * y \Rightarrow z _ {i} = x _ {i} y _ {i}
$$

- SAXPY

$$
y := a x + y \Rightarrow y _ {i} = a x _ {i} + y _ {i}
$$

### Opérations matricielles 矩阵运算

Soient  $\alpha \in \mathbb{R}$ .  $A, B$  et  $C$  des matrices réelles dont la taille est définie pour chaque opération.
设 $\alpha \in \mathbb{R}$，$A,B,C$ 为满足相应维度的实矩阵。

- Transpose:  $\mathbb{R}^{m\times n}\to \mathbb{R}^{n\times m}$
  转置：$\mathbb{R}^{m\times n}\to \mathbb{R}^{n\times m}$

$$
C = A ^ {T} \Rightarrow c _ {i j} = a _ {j i}
$$

- Addition:  $\mathbb{R}^{m\times n}\times \mathbb{R}^{m\times n}\to \mathbb{R}^{m\times n}$
  加法：$\mathbb{R}^{m\times n}\times \mathbb{R}^{m\times n}\to \mathbb{R}^{m\times n}$

$$
C = A + B \Rightarrow c _ {i j} = a _ {i j} + b _ {i j}
$$

- Multiplication par un scalaire:  $\mathbb{R} \times \mathbb{R}^{m \times n} \to \mathbb{R}^{m \times n}$
  标量乘矩阵：$\mathbb{R} \times \mathbb{R}^{m \times n} \to \mathbb{R}^{m \times n}$

$$
C = \alpha A \Rightarrow c _ {i j} = \alpha a _ {i j}
$$

Multiplication Matrice-Matrice  $\mathbb{R}^{m\times p}\times \mathbb{R}^{p\times n}\to \mathbb{R}^{m\times n}$
矩阵乘矩阵 $\mathbb{R}^{m\times p}\times \mathbb{R}^{p\times n}\to \mathbb{R}^{m\times n}$

$$
C = A B \Rightarrow c _ {i j} = \sum_ {k = 1} ^ {p} a _ {i k} b _ {k j}
$$

### Opérations Matrice-Vecteur 矩阵-向量运算

GAXPY

$$
y := A x + y
$$

### Complexité et performances 复杂度与性能

- On identifie 3 ordres de complexité : linéaire, quadratique et cubique  
- On identifie 3 ordres de complexité : linéaire, quadratique et cubique  
  常见三种复杂度：线性、平方、立方
- Chaque ordre correspond à un niveau : 1, 2 ou 3  
  每个层次对应一级、二级或三级操作
- On essaye de replacer les bocles par des algorithmes de niveau 1 2 ou 3.  
  尝试将循环替换为 1/2/3 级算法。
- On peut faire appel à des bibliothèques optimisées (ex: BLAS)
  可调用优化库（如 BLAS）。

  - DSL在某些情况下会自动调用BLAS，比如矩阵乘法 A * B。

### Algorithm 1 Produit scalaire:  $a = x^T y$

算法 1 点积：$a = x^T y$

Require:  $x, y \in \mathbb{R}^n$
要求：$x, y \in \mathbb{R}^n$

```matlab
a = 0;
for i = 1:n
    a = a + x(i) * y(i);
end
```

```matlab
% Version vectorisée
a = x(:)' * y(:);
% ou
a = x' * y;
```

### Algorithm 2 Opération SAXPY:  $y = ax + y$

算法 2 SAXPY 操作：$y = ax + y$

Require:  $a \in \mathbb{R}$,  $x, y \in \mathbb{R}^n$  
要求：$a \in \mathbb{R}$，$x, y \in \mathbb{R}^n$

```matlab
for i = 1:n
    y(i) = a * x(i) + y(i);
end
```

```matlab
% Version vectorisée
y = a * x(:) + y(:);
```

### Algorithm 3 Opération GAXPY double boucle, avec parcours prioritaire des lignes de  $A: y = Ax + y$

算法 3 GAXPY 操作的双循环形式，按 $A$ 的行优先遍历：$y = Ax + y$

Require:  $x, y \in \mathbb{R}^n$  et  $y = 0_n$  
要求：$x, y \in \mathbb{R}^n$ 且 $y = 0_n$

```matlab
for i = 1:m
    for j = 1:n
        y(i) = A(i, j) * x(j) + y(i);
    end
end
```

```matlab
% Version vectorisée
y = a * x(:) + y(:);
```

### Algorithm 4 Opération GAXPY double boucle, avec parcours prioritaire des colonnes de  $A: y = Ax + y$

算法 4 GAXPY 操作的双循环形式，按 $A$ 的列优先遍历：$y = Ax + y$

Require:  $x, y \in \mathbb{R}^n$  et  $y = 0_n$  
要求：$x, y \in \mathbb{R}^n$ 且 $y = 0_n$

```matlab
for j = 1:n
    for i = 1:m
        y(i) = A(i, j) * x(j) + y(i);
    end
end
```

### Algorithm 5 Opération GAXPY une boucle, avec parcours prioritaire des lignes de  $A: y = Ax + y$

算法 5 单循环 GAXPY 操作，按 $A$ 的行优先遍历：$y = Ax + y$

Require:  $x, y \in \mathbb{R}^n$  et  $y = 0_n$  
要求：$x, y \in \mathbb{R}^n$ 且 $y = 0_n$

```matlab
for i = 1:m
    y(i) = A(i, :) * x + y(i);
end
```

### Algorithm 6 Opération GAXPY une boucle, avec parcours prioritaire des colonnes de  $A: y = Ax + y$

算法 6 单循环 GAXPY 操作，按 $A$ 的列优先遍历：$y = Ax + y$

Require:  $x, y \in \mathbb{R}^n$  et  $y = 0_n$  
要求：$x, y \in \mathbb{R}^n$ 且 $y = 0_n$

```matlab
for j = 1:n
    y = A(:, j) * x(j) + y;
end
```

```matlab
% Version vectorisée de niveau 2
y = A * x(:) + y(:)
```

### Algorithm 7 Produit Matrice-Matrice "ijk"

算法 7 矩阵乘矩阵 “ijk” 版本

Require:  $A\in \mathbb{R}^{m\times p}$,  $B\in \mathbb{R}^{p\times n}$,  $C\in \mathbb{R}^{m\times n}$  
要求：$A\in \mathbb{R}^{m\times p}$，$B\in \mathbb{R}^{p\times n}$，$C\in \mathbb{R}^{m\times n}$

Formule générale:
$$
C = AB + C \Rightarrow c _ {i j} = \sum_ {k = 1} ^ {p} a _ {i k} b _ {k j} + c _ {i j}
$$

```matlab
% Version ijk scalaire
for i = 1:m
    for j = 1:n
        for k = 1:p
            C(i, j) = A(i, k) * B(k, j) + C(i, j);
        end
    end
end
```

Complexité:  $O(m n p)$

<!-- markdownlint-disable MD033 -->
<table>
  <tr><td>Version</td><td>Boucle intermédiaire</td><td>Boucle interieure</td><td>Accès aux données (boucle interieure)</td></tr>
  <tr><td>ijk</td><td>vector × matrice</td><td>produit scalaire</td><td>ligne de A et colonne de B</td></tr>
  <tr><td>jik</td><td>matrice × vecteur</td><td>produit scalaire</td><td>ligne de A et colonne de B</td></tr>
  <tr><td>ikj</td><td>GAXPY ligne</td><td>SAXPY</td><td>ligne de B et ligne de C</td></tr>
  <tr><td>jki</td><td>GAXPY colonne</td><td>SAXPY</td><td>colonne de A et colonne de C</td></tr>
  <tr><td>kij</td><td>produit extérieur de lignes</td><td>SAXPY</td><td>ligne de B et ligne de C</td></tr>
  <tr><td>kji</td><td>produit extérieur de colonnes</td><td>SAXPY</td><td>colonne de A et colonne de C</td></tr>
</table>
<!-- markdownlint-enable MD033 -->

表：不同乘法版本中各层循环的含义及数据访问模式

### Algorithm 8 Produit Matrice-Matrice "ijk" avec 2 boucles 算法 8 两重循环的矩阵乘矩阵 “ijk”

Require:  $A\in \mathbb{R}^{m\times p}$,  $B\in \mathbb{R}^{p\times n}$,  $C\in \mathbb{R}^{m\times n}$  
要求：$A\in \mathbb{R}^{m\times p}$，$B\in \mathbb{R}^{p\times n}$，$C\in \mathbb{R}^{m\times n}$

```matlab
for i = 1:m
    for j = 1:n
        C(i, j) = A(i, :) * B(:, j) + C(i, j);
    end
end
```

### Algorithm 9 Produit Matrice-Matrice "ijk" avec 1 boucle 算法 9 单循环的矩阵乘矩阵 “ijk”

Require:  $A\in \mathbb{R}^{m\times p}$,  $B\in \mathbb{R}^{p\times n}$,  $C\in \mathbb{R}^{m\times n}$  
要求：$A\in \mathbb{R}^{m\times p}$，$B\in \mathbb{R}^{p\times n}$，$C\in \mathbb{R}^{m\times n}$

```matlab
for i = 1:m
    C(i, :) = A(i, :) * B + C(i, :);
end
```

## Résolution de système linéaire 线性系统求解

### Système linéaire 线性系统

Soient  $A \in \mathbb{R}^{n \times n}$ ,  $x, b \in \mathbb{R}^{n \times n}$ ,  $A$  is invertible, i.e.  $\det(A) \neq 0$ . Dans la suite, on sahaité résoudre le système linéaire suivant:
设 $A \in \mathbb{R}^{n \times n}$，$x, b \in \mathbb{R}^{n \times n}$，且 $A$ 可逆，即 $\det(A) \neq 0$。我们希望求解如下线性系统：

$$
A x = b \tag {1}
$$

### Erreur avant, arrêté et conditionnement 前向误差、后向误差与条件数

- Erreur avant :
  前向误差：
$\hat {x}$是数值方法计算得到的 $x$ 的近似值。设相对前向误差 err $\in \mathbb{R}$：

$$
e r r := \frac {\left| \left| x - \hat {x} \right| \right|}{\left| \left| x \right| \right|} \tag {2}
$$

- Erreur arrêté : le résidu  $r \in  {\mathbb{R}}^{n},r = b - A\widehat{x}$  . Soit l'erreur résiduelle relative relres  $\in  \mathbb{R}$  :
  后向误差：残差 $r \in \mathbb{R}^{n}, r = b - A\widehat{x}$，设相对残差 relres $\in \mathbb{R}$：

$$
\operatorname {r e l r e s} := \frac {\left| \left| b - A \hat {x} \right| \right|}{\left| \left| A \right| \right| \left| \left| \hat {x} \right| \right|} \tag {3}
$$

- Conditionnement de  $A: \kappa(A) = ||A||||A^{-1}||$ . Le conditionnement peut être vu comme la capacité pour  $A$  à générer de l'erreur  
  $A$ 的条件数 $\kappa(A) = ||A||||A^{-1}||$，可理解为 $A$ 产生误差的能力。

- Règle générale: 通用准则

$$
\frac {\left| \left| x - \hat {x} \right| \right|}{\left| \left| x \right| \right|} \leq \kappa_ {2} (A) \frac {\left| \left| b - A \hat {x} \right| \right|}{\left| \left| A \right| \right| \left| \left| \hat {x} \right| \right|} \tag {4}
$$

### Problématique 问题意识

- Quelle méthode désir?
  想使用哪种方法？
- Dequelle précision avons-nous besoin ?  
  我们需要达到什么精度？
- Quelles sont les contraintes matérielles ? (espace mémoire, architecture)
  硬件限制是什么？（内存空间、架构）
- Quel type de matrice doit-on inverser?  
  需要求逆的矩阵类型是哪种？
- Y a-t-il des propriétés intéressante à exploiter ?
  是否存在可利用的特殊性质？

### L'idée des méthodes directes 直接法的思路

- Transformer un système en un système équivalent plus simple à résoudre.  
- Les systèmes triangulaires sont simples à résoudre!
- Transformer un système en un système équivalent plus simple à résoudre.  
  将系统转化为更易求解的等价形式。
- Les systèmes triangulaires sont simples à résoudre!
  三角系统容易求解！

## Matrice triangulaire 三角矩阵

### Definition 1. 定义 1

[Matrice triangulaire supérieure] La matrice  $U \in \mathbb{R}^{n \times n}$ , est triangulaire supérieure si  $\forall i > j$ ,  $u_{ij} = 0$ .  $U$  est donc de la forme:

$$
U = \left( \begin{array}{c c c c c} X & X & X & X & X \\ & X & X & X & X \\ & & X & X & X \\ & & & X & X \\ & & & & X \end{array} \right)
$$

### Definition 2 (Matrice triangulaire inférieure). 定义 2（下三角矩阵）

La matrice  $L \in \mathbb{R}^{n \times n}$ , est triangulaire inférieure si  $\forall i < j, l_{ij} = 0$ .  $L$  est donc de la forme:

$$
L = \left( \begin{array}{c c c c c} X & & & & \\ X & X & & & \\ X & X & X & & \\ X & X & X & X & \\ X & X & X & X & X \end{array} \right)
$$

### Algorithm 10 Méthode de remontée : résolution de  $Ux = b$  (version avec produit scalaire) 算法 10 回代法：解 $Ux = b$（点积形式）

Require:  $U\in \mathbb{R}^{n\times n}$,  $x, b\in \mathbb{R}^n$  
要求：$U\in \mathbb{R}^{n\times n}$，$x, b\in \mathbb{R}^n$

```matlab
x(n) = b(n) / U(n,n)
for i = n-1:-1:1
    s = 0
    for j = i+1:n
        s = s + U(i,j) * x(j)
    end for
    x(i) = (b(i) - s) / U(i,i)
end for
```
$$
x_{i} = \frac{ b_{i} - \sum_{j=i+1}^{n} U_{ij} x_{j} }{U_{ii}}
$$

```matlab
% Version vectorisée
x(n) = b(n) / U(n, n);
for i = n-1:-1:1
    x(i) = (b(i) - U(i, (i + 1):n) * x((i + 1):n)) / U(i, i);
end
```

### Algorithm 11 Méthode de descente : résolution de  $Lx = b$  (version avec produit scalaire) 算法 11 前代法：解 $Lx = b$（点积形式）

Require:  $L\in \mathbb{R}^{n\times n}$,  $x, b\in \mathbb{R}^n$  
要求：$L\in \mathbb{R}^{n\times n}$，$x, b\in \mathbb{R}^n$

```matlab
x(1) = b(1) / L(1, 1);
for i = 2:n
    s = 0;
    for j = 1:(i - 1)
        s = s + L(i, j) * x(j);
    end
    x(i) = (b(i) - s) / L(i, i);
end
```

$$
x_{i} = \frac{ b_{i} - \sum_{j=1}^{i-1} L_{ij} x_{j} }{d_{i}}
$$

```matlab
% Version vectorisée
x(1) = b(1) / L(1, 1);
for i = 2:n
    x(i) = (b(i) - L(i, 1:(i - 1)) * x(1:(i - 1))) / L(i, i);
end
```

## Principe général 基本原理

La méthode de Gauss s'applique en deux étapes :
高斯法包含两步：

Triangularisation du système tel que
首先对系统进行三角化

$$
A x = b \Leftrightarrow M A x = M b
$$

ou  $MA$  est une matrice triangulaire supérieure.
此时 $MA$ 为上三角矩阵。

- Résolution de  $MAx = Mb$  par "remontée". 通过回代求解 $MAx = Mb$。

La triangularisation, élimination de Gauss, s'effectue en  $n - 1$  étapes et consiste àmettre à zéro les éléments d'une colonne situés sous la diagonale principale.
三角化（高斯消元）需进行 $n-1$ 步，将主对角线下方的元素清零。

### Initialisation et Elimination 1 初始化与第 1 次消元

- Initialisation:  $A^{(1)} \coloneqq A$  et  $b^{(1)} \coloneqq b$  et pivot  $d_{1} = a_{11}^{(1)}$  
- Initialisation:  $A^{(1)} \coloneqq A$  et  $b^{(1)} \coloneqq b$  et pivot  $d_{1} = a_{11}^{(1)}$  
  初始化：$A^{(1)} \coloneqq A$，$b^{(1)} \coloneqq b$，枢轴 $d_{1} = a_{11}^{(1)}$
- Pour  $k = 1$ ,  $d_{1} = a_{11}^{(1)}$
  当 $k = 1$ 时，$d_{1} = a_{11}^{(1)}$

$$
\begin{array}{l} A ^ {(2)} = M _ {1} A ^ {(1)} \\ = \left( \begin{array}{c c c c c c} 1 & & & & & \\ - m _ {2 1} & 1 & & & & \\ - m _ {3 1} & & 1 & & & \\ \vdots & & & \ddots & & \\ - m _ {n 1} & & & & 1 \end{array} \right) A ^ {(1)}, \text {o u} m _ {(k + 1): n, 1} = A ^ {(1)} (2: n, 1) / d _ {1} \\ = \left( \begin{array}{c c c c} a _ {1 1} ^ {(1)} & a _ {1 2} ^ {(1)} & \ldots & a _ {1 n} ^ {(1)} \\ 0 & a _ {2 2} ^ {(2)} & \ldots & a _ {2 n} ^ {(2)} \\ \vdots & \vdots & & \\ 0 & a _ {n 2} ^ {(2)} & \ldots & a _ {n n} ^ {(2)} \end{array} \right) \\ \end{array}
$$

et,
且

$$
b ^ {(2)} = M _ {1} b ^ {(1)}
$$

$$
k = 2: n - 2 \text {é l i m i n a t i o n s}
$$
进行 $k = 2: n - 2$ 次消元

Pour 1 < k < n - 1, $d_k = a_{kk}^{k}$
当 $1 < k < n - 1$ 时，$d_k = a_{kk}^{k}$

$$
A ^ {(k + 1)} \quad = \quad M _ {k} A ^ {(k)}
$$

$$
= \left( \begin{array}{c c c c c c c} 1 & & & & & & \\ & \ddots & & & & \\ & & 1 & & & & \\ & & - m _ {(k + 1) k} & 1 & & \\ & & \vdots & & \ddots & \\ & & - m _ {n k} & & & 1 \end{array} \right) A ^ {(k)}, \text {ou } m _ {(k + 1): n, 1} = A ^ {(k)} ((k + 1): n, k) / d _ {k}
$$

$$
\left( \begin{array}{c c c c c c c c c} a _ {1 1} ^ {(k)} & a _ {1 2} ^ {(k)} & \dots & \dots & \dots & \dots & \dots & \dots & a _ {1 n} ^ {(k)} \\ 0 & a _ {2 2} ^ {(k)} & a _ {2 3} ^ {(k)} & \dots & \dots & \dots & \dots & \dots & a _ {2 n} ^ {(k)} \\ & & \ddots & & & & & \\ 0 & 0 & \ddots & & & & & \\ \vdots & \vdots & & a _ {k k} ^ {(k)} & a _ {(k (k + 1)} ^ {(k)} & \dots & \dots & \dots & a _ {k n} ^ {(k)} \\ \vdots & \vdots & & 0 & a _ {(k + 1) k} ^ {(k + 1)} & \dots & \dots & \dots & a _ {(k + 1) n} ^ {(k + 1)} \\ \vdots & \vdots & & \vdots & \vdots & & & & \vdots \\ 0 & 0 & & 0 & a _ {n k} ^ {(k + 1)} & \dots & \dots & \dots & a _ {n n} ^ {(k + 1)} \end{array} \right)
$$

et,
并且，

$$
b ^ {(k + 1)} = M _ {k} b ^ {(k)}
$$

### $k = 2:n - 1$  éliminations $k = 2:n - 1$ 次消元

- Pour  $k = n - 1$ , on obtient  $A^{(n)}$  triangulaire supérieure telle que:
- Pour  $k = n - 1$ , on obtient  $A^{(n)}$  triangulaire supérieure telle que:
  当 $k = n - 1$ 时，得到上三角矩阵 $A^{(n)}$，满足：

$$
A ^ {(n)} = M _ {n - 1} A ^ {(n - 1)} = M A
$$

et,
且，

$$
\boldsymbol {b} ^ {(n)} = M \boldsymbol {b}
$$

Avec,
其中，

$$
\begin{array}{l} M = M _ {n - 1} M _ {n - 2} \dots M _ {1} \\ = \left( \begin{array}{c c c c c} 1 & & & & \\ - m _ {2 1} & 1 & & & \\ \vdots & - m _ {3 2} & 1 & & \\ \vdots & \vdots & & \ddots & \\ - m _ {n 1} & - m _ {n 2} & \dots & - m _ {n (n - 1)} & 1 \end{array} \right) \tag {5} \\ \end{array}
$$

### Algorithm 12 Méthode de résolution de Gauss sans pivotage : résolution de  $Ax = b$  (version scalaire à 3 boucles "kij")

算法 12 无主元的高斯消元法：解 $Ax = b$（3 重循环 "kij" 标量形式）

Require:  $A\in \mathbb{R}^{n\times n}$,  $x, b\in \mathbb{R}^n$  
要求：$A\in \mathbb{R}^{n\times n}$，$x, b\in \mathbb{R}^n$

```matlab
for k = 1:n-1
    for i = k+1:n
        m(i, k) = A(i, k) / A(k, k);
        b(i) = b(i) - m(i, k) * b(k);
        for j = k+1:n
            A(i, j) = A(i, j) - m(i, k) * A(k, j);
        end
    end
end
```

Résoudre le nouveau système  $Ax = b$  par remontée (Algorithm 10).
再对所得系统 $Ax = b$ 进行回代（算法 10）。

La méthode est dépendante du second membre.  
该方法依赖右端项。

- Complexité de l'élimination:  $2n^{3} / 3$  flops
- 消元复杂度：$2n^{3} / 3$ 次浮点运算

## De Gauss à LU 从高斯到 LU

Posons  $U = MA$ . On peut écrire  $A = LU$  avec  $L$  triangulaire inférieur.
令 $U = MA$，则可写成 $A = LU$，其中 $L$ 为下三角矩阵。

En considérant l'écriture de  $M$  donnée par l'équation (6) on a  $M$  inversible, d'ou :
根据式 (6) 给出的 $M$，其可逆，因此：

$$
U = M A \Leftrightarrow M ^ {- 1} U = A
$$

et  $M^{-1} = M_1^{-1}M_2^{-1}\dots M_{n - 2}^{-1}M_{n - 1}^{-1}$
且 $M^{-1} = M_1^{-1}M_2^{-1}\dots M_{n - 2}^{-1}M_{n - 1}^{-1}$

On obtient alors
因此

$$
M ^ {- 1} = \left( \begin{array}{c c c c c c} 1 & & & & & \\ m _ {2 1} & 1 & & & & \\ \vdots & m _ {3 2} & 1 & & & \\ \vdots & \vdots & & \ddots & & \\ m _ {n 1} & m _ {n 2} & \dots & m _ {n (n - 1)} & 1 \end{array} \right) \tag {6}
$$

On a donc bien une matrice triangulaire  $M^{-1}$  et on pose  $L = M^{-1}$ .
从而 $M^{-1}$ 确为下三角矩阵，并令 $L = M^{-1}$。

La méthode de Gauss donne donc une factorisation  $LU$  de la matrice.
因此，高斯方法提供了矩阵的 $LU$ 分解。

### Principe général 基本流程

Factorisation  $A = LU$  
先进行 $A = LU$ 分解
Résolution de
然后求解

$$
\left\{ \begin{array}{r c l} L y & = & b \\ U x & = & y \end{array} \right. \tag {7}
$$

### LU(Forme normale et forme compacte de la matrice A) LU（矩阵 A 的紧凑形式）

Require:  $A\in \mathbb{R}^{n\times n}$  
要求：$A\in \mathbb{R}^{n\times n}$

```matlab
% 初始化
L = eye(n);      % L 对角线为 1

for k = 1:n-1
    for i = k+1:n
        % 1. 计算倍数 (使用当前的 U，而不是原始的 A)
        L(i, k) = A(i, k) / A(k, k);
    end for
        % 2. 更新第 i 行 (这是消除过程)
    for i = k+1:n
        for j = k:n 
            A(i, j) = A(i, j) - L(i, k) * A(k, j);
        end
    end
end

% 循环结束后：
% U = A 的下三角部分理论上已经是 0 了,但实际上无所谓，因为我们只关心上三角部分
% A 现在存储的是 U 矩阵
% L 记录了所有的乘数
```

$$
A = L U := \left( \begin{array}{c c c c c} u _ {1 1} & \dots & \dots & \dots & u _ {1 n} \\ I _ {2 1} & u _ {2 2} & \dots & \dots & u _ {2 n} \\ I _ {3 1} & I _ {3 2} & \ddots & \dots & \dots \\ \vdots & \vdots & \ddots & \ddots & u _ {(n - 1) n} \\ I _ {n 1} & I _ {n 2} & \dots & I _ {n (n - 1)} & u _ {n n} \end{array} \right) \tag {8}
$$

Algorithm 13 Élimination de Gauss et écriture compacte de LU (version scalaire à 3 boucles "kij")
算法 13 高斯消元及 LU 紧凑存储（3 重循环 "kij" 标量实现）

Require:  $A\in \mathbb{R}^{n\times n}$  
要求：$A\in \mathbb{R}^{n\times n}$

```matlab
for k = 1:n-1
    for i = k+1:n
        A(i, k) = A(i, k) / A(k, k);
    end
    for i = k+1:n
        for j = k+1:n
            A(i, j) = A(i, j) - A(i, k) * A(k, j);
        end
    end
end
```

Comme pour le produit Matrice-Matrice il y a 6 écrites possibles.
与矩阵乘矩阵类似，这里也有 6 种循环写法。

## Pivot 枢轴

## Problématique 问题

Soit à résoudre le système linéaire (1) par l'algorithmme 12. Deux situations critiques peuvent apparaitre :
使用算法 12 求解系统 (1) 时可能遇到速度更快：Matlab 或 Python (NumPy) 底层会调用高度优化的 BLAS Level 2/3 库来执行这些矩阵乘法，比解释器执行 for 循环要快得多。两类严重情况：

- si  $d_{k} = a_{kk}^{(k)} = 0$  alors l'opération d'élimination n'est pas définie (division par zéro).  
- 若 $d_{k} = a_{kk}^{(k)} = 0$，则无法进行消元（会除以零）。
- si  $d_{k} = a_{kk}^{(k)} = \epsilon \ll   1$
- 若 $d_{k} = a_{kk}^{(k)} = \epsilon \ll 1$

## Exemple pour le cas 2 情形 2 示例

A=（ 1 -1）avec  $0 <   \epsilon \ll   1$  
$\kappa_{\infty}(A) = 4 / (1 + \epsilon)$  
Pour la factorisation  $LU$  on peut écrire :
考虑 $0<\epsilon \ll 1$ 且 $A = \begin{pmatrix}\epsilon & -1 \\ 1 & 1\end{pmatrix}$，其 $\kappa_{\infty}(A) = 4 / (1 + \epsilon)$，LU 分解如下：

$$
\begin{array}{l} A = \left( \begin{array}{c c} \epsilon & - 1 \\ 1 & 1 \end{array} \right) \\ = \left( \begin{array}{c c} 1 & 0 \\ I _ {2 1} & 1 \end{array} \right) \left( \begin{array}{c c} u _ {1 1} & u _ {1 2} \\ 0 & u _ {2 2} \end{array} \right) \\ = \left( \begin{array}{c c} 1 & 0 \\ \epsilon^ {- 1} & 1 \end{array} \right) \left( \begin{array}{c c} \epsilon & - 1 \\ 0 & \epsilon^ {- 1} \end{array} \right) \\ \end{array}
$$

D'ou,

$$
A - \hat {L} \hat {U} = \left( \begin{array}{c c} 0 & 0 \\ 0 & 1 \end{array} \right)
$$

Le problème est dans le besoin du pivot et non dans le conditionnement de  $A$ .
问题出在需要选取枢轴，而不是矩阵 $A$ 的条件数。

## Pivot partiel 部分枢轴

Prendre pour pivot le plus grand élément de la colonne en valeur absolue. C'est-à-dire, à l' étape  $k$  on échange la ligne  $k$  avec la ligne  $r$  tel que:
选择该列绝对值最大的元素作为枢轴，即在第 $k$ 步，将第 $k$ 行与满足下式的第 $r$ 行互换：

$$
\left| a _ {i k} ^ {(k)} \right| = \max_{k \leq i \leq n} \left(a _ {i k} ^ {(k)}\right) \tag {9}
$$

Ceci assure que
这可保证

$$
\left| m _ {i k} \right| \leq 1, \text { pour } i = k + 1: n \tag {10}
$$

Cette méthode dite du pivot partiel à une complexité en  $O(n^{2})$ .
该部分枢轴策略的复杂度为 $O(n^{2})$。

## Pivot complete 完全枢轴

On pourrait, pour assurer une plus grande stabilité, échéanger à l'étape  $k$  les lignes  $r$  et les colonnes  $s$  de  $A$  tel que:
为获得更高稳定性，可以在第 $k$ 步同时交换第 $r$ 行和第 $s$ 列，使得：

$$
\left| a _ {r s} ^ {(k)} \right| = \max  _ {k \leq i \leq n, k \leq j \leq n} \left(a _ {i j} ^ {(k)}\right) \tag {11}
$$

Cette méthode dite du pivot complet à une complexité en  $O(n^3)$ .
这种完全枢轴方法的复杂度为 $O(n^3)$。

## Algorithm 14 Pivot Partiel 算法 14 部分枢轴

Require:  $A \in \mathbb{R}^{n \times n}$  à l' étape  $k$  de l'élimination de Gauss,  $row \in \mathbb{R}^{1\times n}$  
要求：$A \in \mathbb{R}^{n \times n}$（处于高斯消元第 $k$ 步），$row \in \mathbb{R}^{1\times n}$

```matlab
[piv, ind] = max(abs(A(k:n, k)));      % récupère le max piv sous A(k,k)
ind = k - 1 + ind;                    % convertit l'indice local en global
q = row(1, ind);                      % ligne à permuter à cette étape
if ind ~= k
    new = A(ind, :);                  % stockage temporaire dans new
    A(ind, :) = A(k, :);              % échange des lignes
    A(k, :) = new;
    row(1, ind) = row(1, k);          % mise à jour de row
    row(1, k) = q;
end
```

$$
P A = L U
$$

On écrit généralement la matrice des permutations,  $P \in \mathbb{R}^{n \times n}$  après les  $k$  étapes d'élimination.
通常在完成 $k$ 次消元后写出置换矩阵 $P \in \mathbb{R}^{n \times n}$。

Lorsque I'on calcule une factorisation  $LU$  avec pivot partiel on obtient :
采用部分枢轴计算 LU 分解时，有：

$$
P A = L U
$$

Cela revient a resoudre le système :
因此需要解以下系统：

$$
A x = b \Leftrightarrow L U x = P b
$$
