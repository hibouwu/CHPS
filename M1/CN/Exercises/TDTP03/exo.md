# Exercice : Factorisation LU et Résolution (Forme Compacte) 练习：LU 分解与求解（紧凑形式）

**Données du problème :** 问题数据：
On considère la matrice $A \in \mathbb{R}^{3\times 3}$ et le vecteur $b \in \mathbb{R}^3$ suivants :
考虑如下矩阵 $A \in \mathbb{R}^{3\times 3}$ 和向量 $b \in \mathbb{R}^3$：

$$
A = \begin{pmatrix}
1 & 1 & 1 \\
2 & 4 & 5 \\
-1 & 1 & 3
\end{pmatrix}, \quad
b = \begin{pmatrix}
6 \\
25 \\
14
\end{pmatrix}
$$

**Questions :** 问题：

1. **Factorisation LU (Algorithme 12 & 13)** : appliquez la méthode d'élimination de Gauss (sans pivotage) pour factoriser $A$ sous la forme $A = LU$.
   **LU 分解（算法 12 和 13）**：应用高斯消元法（无主元选取）将 $A$ 分解为 $A = LU$。
   * Donnez explicitement les matrices $L$ (triangulaire inférieure à diagonale unité) et $U$ (triangulaire supérieure).
     明确给出矩阵 $L$（单位对角的下三角）和 $U$（上三角）。
   * Précisez les multiplicateurs $m_{ik}$ calculés à chaque étape.
     说明每一步计算的乘子 $m_{ik}$。
2. **Stockage compact (Algorithme 13)** : donnez la matrice sous sa forme compacte, telle qu'elle serait stockée en mémoire à la fin de l'algorithme. *(Référence : Slide 30, Algorithme 13)*
   **紧凑存储（算法 13）**：给出矩阵的紧凑形式，即算法结束后在内存中的存储方式。（参考：幻灯片 30，算法 13）
3. **Résolution du système (Algorithme 10 & 11)** : en utilisant la factorisation obtenue, résolvez $Ax = b$ en deux étapes :
   **求解线性系统（算法 10 和 11）**：利用得到的分解，分两步求解 $Ax = b$：
   * Descente (résolution de $Ly = b$).
     前代（求解 $Ly = b$）。
   * Remontée (résolution de $Ux = y$).
     回代（求解 $Ux = y$）。
4. **Complexité** : rappelez le coût en flops de la factorisation LU (étape 1) et de la résolution du système (étape 3). *(Référence : Slide 27 et analyse précédente)*
   **复杂度**：给出 LU 分解（步骤 1）和求解系统（步骤 3）的浮点运算次数。（参考：幻灯片 27 及先前分析）

-----

## 💡 Correction détaillée 详细解答

Prenez un stylo et essayez de le faire avant de regarder la solution ci-dessous !
在查看下方解答前，先拿起笔尝试自行完成！

### 1. Factorisation LU (Élimination de Gauss) 1. LU 分解（高斯消元）

L'objectif est d'annuler les coefficients sous la diagonale (colonne par colonne).
目标是按列依次将对角线下方的系数消为零。

- **Étape $k=1$ (colonne 1)**
  第 $k=1$ 步（第 1 列）
  - Pivot : $a_{11} = 1$.
    主元：$a_{11} = 1$。
  - Multiplicateur $m_{21} = A_{21}/A_{11} = 2/1 = \mathbf{2}$.
    乘子 $m_{21} = A_{21}/A_{11} = 2/1 = \mathbf{2}$。
  - Multiplicateur $m_{31} = A_{31}/A_{11} = -1/1 = \mathbf{-1}$.
    乘子 $m_{31} = A_{31}/A_{11} = -1/1 = \mathbf{-1}$。
  - Opérations sur les lignes :
    行操作：
    - $L_2 \leftarrow L_2 - 2 L_1 \Rightarrow (0, 4-2, 5-2) = (0, 2, 3)$.
      $L_2 \leftarrow L_2 - 2 L_1 \Rightarrow (0, 4-2, 5-2) = (0, 2, 3)$。
    - $L_3 \leftarrow L_3 - (-1) L_1 \Rightarrow (0, 1+1, 3+1) = (0, 2, 4)$.
      $L_3 \leftarrow L_3 - (-1) L_1 \Rightarrow (0, 1+1, 3+1) = (0, 2, 4)$。
  - Matrice intermédiaire : $\begin{pmatrix} 1 & 1 & 1 \\ 0 & 2 & 3 \\ 0 & 2 & 4 \end{pmatrix}$.
    中间矩阵：$\begin{pmatrix} 1 & 1 & 1 \\ 0 & 2 & 3 \\ 0 & 2 & 4 \end{pmatrix}$。

- **Étape $k=2$ (colonne 2)**
  第 $k=2$ 步（第 2 列）
  - Pivot : $a_{22}^{(2)} = 2$.
    主元：$a_{22}^{(2)} = 2$。
  - Multiplicateur $m_{32} = A_{32}^{(2)}/A_{22}^{(2)} = 2/2 = \mathbf{1}$.
    乘子 $m_{32} = A_{32}^{(2)}/A_{22}^{(2)} = 2/2 = \mathbf{1}$。
  - Opération sur la ligne : $L_3 \leftarrow L_3 - 1 L_2 \Rightarrow (0, 0, 4-3) = (0, 0, 1)$.
    行操作：$L_3 \leftarrow L_3 - 1 L_2 \Rightarrow (0, 0, 4-3) = (0, 0, 1)$。

- **Résultat** : les éléments de $U$ sont ceux de la matrice finale. Les éléments de $L$ (hors diagonale) sont les multiplicateurs $m_{ik}$.
  结果：$U$ 的元素来自最终矩阵，$L$ 的非对角元素即为各步乘子 $m_{ik}$。

$$
L = \begin{pmatrix}
1 & 0 & 0 \\
\mathbf{2} & 1 & 0 \\
\mathbf{-1} & \mathbf{1} & 1
\end{pmatrix}, \quad
U = \begin{pmatrix}
1 & 1 & 1 \\
0 & 2 & 3 \\
0 & 0 & 1
\end{pmatrix}
$$

### 2. Forme compacte (stockage mémoire) 2. 紧凑形式（内存存储）

On stocke $L$ (sans sa diagonale unitaire) dans la partie triangulaire inférieure de $A$, et $U$ dans la partie supérieure.
将 $L$（去掉单位对角线）存放在 $A$ 的下三角部分，$U$ 存放在上三角部分。

$$
\text{Forme compacte} = \begin{pmatrix}
1 & 1 & 1 \\
\mathbf{2} & 2 & 3 \\
\mathbf{-1} & \mathbf{1} & 1
\end{pmatrix}
$$
*(Notez que la diagonale contient les pivots de $U$.)*
（注意：主对角线包含 $U$ 的主元。）

### 3. Résolution du système 3. 求解线性系统

On résout $Ax=b \iff LUx=b$. On pose $Ux=y$, donc on résout d'abord $Ly=b$.
解 $Ax=b \iff LUx=b$。设 $Ux=y$，先求解 $Ly=b$。

- **A. Descente (forward substitution) : $Ly = b$**
  A. 前代（求解 $Ly = b$）

$$
\begin{cases}
y_1 = 6 \\
2y_1 + y_2 = 25 \Rightarrow 12 + y_2 = 25 \Rightarrow y_2 = 13 \\
-y_1 + y_2 + y_3 = 14 \Rightarrow -6 + 13 + y_3 = 14 \Rightarrow 7 + y_3 = 14 \Rightarrow y_3 = 7
\end{cases}
$$

$\Rightarrow y = (6, 13, 7)^T$.
因此 $y = (6, 13, 7)^T$。

- **B. Remontée (backward substitution) : $Ux = y$**
  B. 回代（求解 $Ux = y$）

$$
\begin{cases}
x_3 = 7 / 1 \Rightarrow x_3 = 7 \\
2x_2 + 3x_3 = 13 \Rightarrow 2x_2 + 21 = 13 \Rightarrow 2x_2 = -8 \Rightarrow x_2 = -4 \\
x_1 + x_2 + x_3 = 6 \Rightarrow x_1 - 4 + 7 = 6 \Rightarrow x_1 + 3 = 6 \Rightarrow x_1 = 3
\end{cases}
$$

**Solution finale :** $x = (3, -4, 7)^T$.
最终解：$x = (3, -4, 7)^T$。

### 4. Complexité 4. 复杂度

- **Factorisation LU :** $\approx \frac{2}{3}n^3$ flops.
  LU 分解：约 $\frac{2}{3}n^3$ 次浮点运算。
- **Résolution (descente + remontée) :** $\approx 2n^2$ flops (soit $n^2$ pour la descente et $n^2$ pour la remontée).
  求解（前代 + 回代）：约 $2n^2$ 次浮点运算（前代 $n^2$，回代 $n^2$）。
  