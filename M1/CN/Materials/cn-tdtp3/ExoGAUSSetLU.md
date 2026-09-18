# Exercice : Factorisation LU et Résolution (Forme Compacte)

**Données du problème :**
On considère la matrice $A \in \mathbb{R}^{3\times 3}$ et le vecteur $b \in \mathbb{R}^3$ suivants :

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

**Questions :**

1. **Factorisation LU (Algorithme 12 & 13)** : appliquez la méthode d'élimination de Gauss (sans pivotage) pour factoriser $A$ sous la forme $A = LU$.
   * Donnez explicitement les matrices $L$ (triangulaire inférieure à diagonale unité) et $U$ (triangulaire supérieure).
   * Précisez les multiplicateurs $m_{ik}$ calculés à chaque étape.
2. **Stockage compact (Algorithme 13)** : donnez la matrice sous sa forme normale et compacte, telle qu'elle serait stockée en mémoire à la fin de l'algorithme. *(Référence : Slide 30, Algorithme 13)*
3. **Résolution du système (Algorithme 10 & 11)** : en utilisant la factorisation obtenue, résolvez $Ax = b$ en deux étapes :
   * Descente (résolution de $Ly = b$).
   * Remontée (résolution de $Ux = y$).
4. **Complexité** : rappelez le coût en flops de la factorisation LU (étape 1) et de la résolution du système (étape 3). *(Référence : Slide 27 et analyse précédente)*

-----

## 💡 Correction détaillée

Prenez un stylo et essayez de le faire avant de regarder la solution ci-dessous !

### 1. Factorisation LU (Élimination de Gauss)

L'objectif est d'annuler les coefficients sous la diagonale (colonne par colonne).

- **Étape $k=1$ (colonne 1)**
  - Pivot : $a_{11} = 1$.
  - Multiplicateur $m_{21} = A_{21}/A_{11} = 2/1 = \mathbf{2}$.
  - Multiplicateur $m_{31} = A_{31}/A_{11} = -1/1 = \mathbf{-1}$.
  - Opérations sur les lignes :
    - $L_2 \leftarrow L_2 - 2 L_1 \Rightarrow (0, 4-2, 5-2) = (0, 2, 3)$.
    - $L_3 \leftarrow L_3 - (-1) L_1 \Rightarrow (0, 1+1, 3+1) = (0, 2, 4)$.
  - Matrice intermédiaire : $\begin{pmatrix} 1 & 1 & 1 \\ 0 & 2 & 3 \\ 0 & 2 & 4 \end{pmatrix}$.

- **Étape $k=2$ (colonne 2)**
  - Pivot : $a_{22}^{(2)} = 2$.
  - Multiplicateur $m_{32} = A_{32}^{(2)}/A_{22}^{(2)} = 2/2 = \mathbf{1}$.
  - Opération sur la ligne : $L_3 \leftarrow L_3 - 1 L_2 \Rightarrow (0, 0, 4-3) = (0, 0, 1)$.

- **Résultat** : les éléments de $U$ sont ceux de la matrice finale. Les éléments de $L$ (hors diagonale) sont les multiplicateurs $m_{ik}$.

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

### 2. Forme compacte (stockage mémoire)

On stocke $L$ (sans sa diagonale unitaire) dans la partie triangulaire inférieure de $A$, et $U$ dans la partie supérieure.

$$
\text{Forme compacte} = \begin{pmatrix}
1 & 1 & 1 \\
\mathbf{2} & 2 & 3 \\
\mathbf{-1} & \mathbf{1} & 1
\end{pmatrix}
$$
*(Notez que la diagonale contient les pivots de $U$.)*

### 3. Résolution du système

On résout $Ax=b \iff LUx=b$. On pose $Ux=y$, donc on résout d'abord $Ly=b$.

- **A. Descente (forward substitution) : $Ly = b$**

$$
\begin{cases}
y_1 = 6 \\
2y_1 + y_2 = 25 \Rightarrow 12 + y_2 = 25 \Rightarrow y_2 = 13 \\
-y_1 + y_2 + y_3 = 14 \Rightarrow -6 + 13 + y_3 = 14 \Rightarrow 7 + y_3 = 14 \Rightarrow y_3 = 7
\end{cases}
$$

$\Rightarrow y = (6, 13, 7)^T$.

- **B. Remontée (backward substitution) : $Ux = y$**

$$
\begin{cases}
x_3 = 7 / 1 \Rightarrow x_3 = 7 \\
2x_2 + 3x_3 = 13 \Rightarrow 2x_2 + 21 = 13 \Rightarrow 2x_2 = -8 \Rightarrow x_2 = -4 \\
x_1 + x_2 + x_3 = 6 \Rightarrow x_1 - 4 + 7 = 6 \Rightarrow x_1 + 3 = 6 \Rightarrow x_1 = 3
\end{cases}
$$

**Solution finale :** $x = (3, -4, 7)^T$.

### 4. Complexité

- **Factorisation LU :** $\approx \frac{2}{3}n^3$ flops.
- **Résolution (descente + remontée) :** $\approx 2n^2$ flops (soit $n^2$ pour la descente et $n^2$ pour la remontée).
