# TD/TP 2 DE CALCUL NUMÉRIQUE 数值计算的第 2 次 TD/TP

## T. Dufaud ([thomas.dufaud@uvsq.fr](mailto:thomas.dufaud@uvsq.fr)) T. Dufaud（[thomas.dufaud@uvsq.fr](mailto:thomas.dufaud@uvsq.fr)）

## Exercice 1. [TD - Suppression ligne/colonne et redimensionnement] 练习 1. [TD - 删除行/列并重新调整尺寸]

Écrire un algorithme qui accepte en entrée une matrice  $A$  d'ordre  $n$  et qui donne en sortie la matrice  $A[i,j]$  d'ordre  $n - 1$  obtenu à partir de  $A$  en supprimant sa  $i$ -ème ligne et sa  $j$ -ème colonne.
编写一个算法，输入为阶数为 $n$ 的矩阵 $A$，输出为阶数为 $n - 1$ 的矩阵 $A[i,j]$，该矩阵通过删除 $A$ 的第 $i$ 行和第 $j$ 列获得。

Quel est le nombre d'affectations dans l'algorithmme précédent (la complexité en temps)?
上述算法的赋值次数是多少（时间复杂度是多少）？

### CorrEx1Methode 1 更正练习 1 方法 1

Soit  $A$  une matrice carrée donnée d'ordre $n$ . $i , j$ deux entiers tels que  $1 \leq i, j \leq n$ .
设 $A$ 为阶数为 $n$ 的给定方阵，$i , j$ 为满足 $1 \leq i, j \leq n$ 的两个整数。

```matlab
n = size(A, 1);
% bloc de matrice de indice de 1,i-1 et 1,j-1
for k = 1:i-1
    for l = 1:j-1
        B(k, l) = A(k, l);
    end
end

% bloc de matrice de indice de 1,i-1 et j+1,n
for k = 1:i-1
    for l = j+1:n
        B(k, l-1) = A(k, l);
    end
end

% bloc de matrice de indice de i+1,n et 1,j-1
for k = i+1:n
    for l = 1:j-1
        B(k-1, l) = A(k, l);
    end
end

% bloc de matrice de indice de i+1,n et j+1,n
for k = i+1:n
    for l = j+1:n
        B(k-1, l-1) = A(k, l);
    end
end
```

Les quatre blocs effectuent respectivement $(i-1)(j-1)$, $(i-1)(n-j)$, $(n-i)(j-1)$ et $(n-i)(n-j)$ affectations, au total $(n-1)^2$ affectations, soit $(n-1)^2 = \mathcal{O}(n^2)$ opérations arithmétiques. Alors $C_{temps} = \mathcal{O}(n^2)$
这四个代码块分别执行 $(i-1)(j-1)$、$(i-1)(n-j)$、$(n-i)(j-1)$ 和 $(n-i)(n-j)$ 次赋值，总计 $(n-1)^2$ 次赋值，即 $(n-1)^2 = \mathcal{O}(n^2)$ 次算术操作，因此 $C_{temps} = \mathcal{O}(n^2)$。

En mémoire on conserve $A$ ($n^2$ mots) et $B$ ($(n-1)^2$ mots), ce qui donne $C_m = 2n^2 - 2n + 1 = \mathcal{O}(n^2)$ mots. Alors $C_{espace} = \mathcal{O}(n^2)$
在内存中保留 $A$（$n^2$ 个字）和 $B$（$(n-1)^2$ 个字），得到 $C_m = 2n^2 - 2n + 1 = \mathcal{O}(n^2)$ 个字，因此 $C_{espace} = \mathcal{O}(n^2)$。

```matlab
n = size(A, 1);
% Version vectorisée en utilisant le blas niveau 1
for k = 1:i-1
    B(k, 1:j-1) = A(k, 1:j-1);
end
for k = 1:i-1
    B(k, j:n-1) = A(k, j+1:n);
end
for k = i:n-1
    B(k, 1:j-1) = A(k+1, 1:j-1);
end
for k = i:n-1
    B(k, j:n-1) = A(k+1, j+1:n);
end
```

```matlab

% Version vectorisée en utilisant le blas niveau 2
function B = remove_row_col(A, i, j)
    n = size(A, 1);
    B(1:i-1, 1:j-1) = A(1:i-1, 1:j-1);
    B(1:i-1, j:n-1) = A(1:i-1, j+1:n);
    B(i:n-1, 1:j-1) = A(i+1:n, 1:j-1);
    B(i:n-1, j:n-1) = A(i+1:n, j+1:n);
end
```

### CorrEx1Methode 2 更正练习 1 方法 2

Soit  $A$  une matrice carrée donnée d'ordre $n$ . $i , j$ deux entiers tels que  $1 \leq i, j \leq n$ .
设 $A$ 为阶数为 $n$ 的给定方阵，$i , j$ 为满足 $1 \leq i, j \leq n$ 的两个整数。

```matlab
n = size(A, 1);
B = zeros(n-1, n-1); % Initialisation de la matrice
row_B = 1;
for row_A = 1:n
    if row_A == i % Test est 2x plus cher que une affectation
        continue; % Sauter la ligne i
    end
    col_B = 1;
    for col_A = 1:n
        if col_A == j
            continue; % Sauter la colonne j
        end
        B(row_B, col_B) = A(row_A, col_A);
        col_B = col_B + 1;
    end
    row_B = row_B + 1;
end
```

Les affectations principales restent $(n-1)^2$ (remplissage de $B$) mais il faut ajouter les $(n-1)$ affectations de `row_B` et les $(n-1)^2$ affectations de `col_B`, soit encore un total en $\mathcal{O}(n^2)$. En revanche, cette méthode effectue aussi $n$ tests pour `row_A == i` et $n^2$ tests pour `col_A == j`; donc au total $(n-1)^2 + (n-1) + (n-1)^2$ affectations et $n + n^2$ comparaisons.
主要的赋值操作仍为 $(n-1)^2$（填充 $B$），但还需加上 `row_B` 的 $(n-1)$ 次赋值和 `col_B` 的 $(n-1)^2$ 次赋值，总计依然是 $\mathcal{O}(n^2)$。然而，该方法还需要进行 `row_A == i` 的 $n$ 次测试和 `col_A == j` 的 $n^2$ 次测试；因此总共有 $(n-1)^2 + (n-1) + (n-1)^2$ 次赋值以及 $n + n^2$ 次比较。

Si l'on compte ces comparaisons (plus coûteuses qu'une simple affectation) le coût arithmétique détaillé devient $C_{temps} = (n-1)^2 + (n-1) + (n-1)^2 + n + n^2 = 3n^2 - 2n + 1 = \mathcal{O}(n^2)$, légèrement supérieur au schéma 4-blocs.
若将这些比较（比简单赋值更昂贵）也计入，详细的算术成本为 $C_{temps} = (n-1)^2 + (n-1) + (n-1)^2 + n + n^2 = 3n^2 - 2n + 1 = \mathcal{O}(n^2)$，略高于 4 个块的方案。

En mémoire on conserve $A$ ($n^2$ mots) et $B$ ($(n-1)^2$ mots) et 2 variable temporaires, ce qui donne $C_m = 2n^2 - 2n + 1 + 2 = \mathcal{O}(n^2)$ mots. Alors $C_{espace} = \mathcal{O}(n^2)$
在内存中保留 $A$（$n^2$ 个字）和 $B$（$(n-1)^2$ 个字）以及 2 个临时变量，得到 $C_m = 2n^2 - 2n + 1 + 2 = \mathcal{O}(n^2)$ 个字，因此 $C_{espace} = \mathcal{O}(n^2)$。

### CorrEx1Methode 3 (Re-utilisation la matrice A) 更正练习 1 方法 3（重复使用矩阵 A）

Soit  $A$  une matrice carrée donnée d'ordre $n$ . $i , j$ deux entiers tels que  $1 \leq i, j \leq n$ .
设 $A$ 为阶数为 $n$ 的给定方阵，$i , j$ 为满足 $1 \leq i, j \leq n$ 的两个整数。

```matlab
n = size(A, 1);
for k = 1:i-1
    A(k, j:n-1) = A(k, j+1:n);
end
for k = i:n-1
    A(k, 1:j-1) = A(k+1, 1:j-1);
end
for k = i:n-1
    A(k, j:n-1) = A(k+1, j+1:n);
end
```

Dans cette méthode, on réutilise la matrice  $A$  pour stocker le résultat. Les trois boucles effectuent respectivement les nombre d'affectations $(i-1)(n-j)$、$(n-i)(j-1)$ 和 $(n-i)(n-j)$, soit un total de $(i-1)(n-j) + (n-i)(j-1) + (n-i)(n-j) = n^2 - n - ij + i + j - 1$ affectations, ce qui est en  $O(n^2)$ . Donc le coût en temps reste  $C_{temps} = O(n^2)$. Ainsi, le coût en espace devient  $C_{espace} = O(n^2)$ , ce qui est une amélioration par rapport aux méthodes précédentes.
在这种方法中，我们重复使用矩阵 $A$ 来存储结果。三重循环分别执行 $(i-1)(n-j)$、$(n-i)(j-1)$ 和 $(n-i)(n-j)$ 次赋值，总计 $(i-1)(n-j) + (n-i)(j-1) + (n-i)(n-j) = n^2 - n - ij + i + j - 1$ 次赋值，属于 $O(n^2)$。因此时间复杂度仍为 $C_{temps} = O(n^2)$，空间复杂度变为 $C_{espace} = O(n^2)$，比前面的方法更优。

## Exercice 2. [TD - Déterminant (OPTIONNEL)] 练习 2. [TD - 行列式（可选）]

Écrire un algorithme pour le calcul du déterminant d'une matrice  $A$  d'ordre  $n$ , réalisant la formule suivante:
编写一个算法来计算阶数为 $n$ 的矩阵 $A$ 的行列式，满足以下公式：

$$
 d e t (A) = \sum_ {j = 1} ^ {n} (- 1) ^ {j + 1} a _ {1, j} d e t (A [ 1, j ])
$$

ou  $A[i,j]$  est la matrice d'ordre  $n - 1$  obtenu a partir de la matrice  $A$  en eliminating sa  $i^{\text{eme}}$  ligne et sa  $j^{\text{eme}}$  colonne.
其中 $A[i,j]$ 是由矩阵 $A$ 删除第 $i$ 行和第 $j$ 列后得到的阶数 $n-1$ 的矩阵。

### CorrEx2 更正练习 2

```matlab
% Algorithme récursif pour le calcul du déterminant
% On suppose A carrée d'ordre n
% On utilise la fonction remove_row_col définie dans l'exercice 1 pour Suppression de la 1ère ligne et de la i-ème colonne de matrice A
function d = determinant(A)
    n = size(A, 1);
    if n == 1
        d = A(1,1);
    else
        d = 0;
        for i = 1:n
            B = remove_row_col(A, 1, i);
            d = d + A(1,i) * (-1)^(1+i) * determinant(B);
        end
    end
end
```

$C_{temps} = O(n!)$
时间复杂度 $C_{temps} = O(n!)$。

## Exercice 3. [TD - Transposée] 练习 3. [TD - 转置]

Proposer un algorithme pour le calcul de la matrice transposée d'une matrice carrée  $A$  d'ordre  $n$ . Quel est le nombre d'affectations de cet algorithme.  
设计一个算法来计算阶数为 $n$ 的方阵 $A$ 的转置矩阵。这个算法的赋值次数是多少？

### CorrEx3 更正练习 3

```matlab
n = size(A, 1);
B = zeros(n, n); % Initialisation de la matrice transposée
for i = 1:n
    for j = 1:n
        B(j, i) = A(i, j);
    end
end
```

## Exercice 4. [TD - Opérations niveau 1, 2, et 3] 练习 4. [TD - 1、2、3 级操作]

- Écrire un algorithme permettant de calculer le produit scalaire de deux vecteurs de longueur  $n$ .  
- 编写一个算法来计算长度为 $n$ 的两个向量的内积。

```matlab
% Algorithme du produit scalaire de deux vecteurs
% Soit x et y deux vecteurs de taille n
n = length(x);
s = 0;
for i = 1:n
    s = s + x(i) * y(i);
end
```

- Ecrire un algorithme permettant de calculer le produit d'une matrice  $A$  possédant  $n$  lignes et  $m$  colonnes et un vecteur  $x$  de longueur  $m$ .  
- 编写一个算法来计算具有 $n$ 行 $m$ 列的矩阵 $A$ 与长度为 $m$ 的向量 $x$ 的乘积。

```matlab
% Algorithme du produit matrice-vecteur GAXPY
% Soit A une matrice de taille n x m et x un vecteur de taille m
n = size(A, 1);
m = size(A, 2);
b = zeros(n, 1);
for i = 1:n
    for j = 1:m
        b(i) = b(i) + A(i, j) * x(j);
    end
end
```

```matlab
% Variante DOT (accumulation colonne par colonne)
n = size(A, 1);
m = size(A, 2);
b = zeros(n, 1);
for j = 1:m
    b = b + A(:, j) * x(j); % équivaut à un axpy
end
```

- Écrire un algorithme permettant le calcul du produit d'une matrice  $A$  possédant  $n$  lignes et  $m$  colonnes et une matrice  $B$  possédant  $m$  lignes et  $p$  colonnes.
- 编写一个算法来计算具有 $n$ 行 $m$ 列的矩阵 $A$ 与具有 $m$ 行 $p$ 列的矩阵 $B$ 的乘积。

```matlab
% Algorithme du produit matrice-matrice
% Soit A une matrice de taille n x m et B une matrice de taille m x p
n = size(A, 1);
m = size(A, 2);
p = size(B, 2);
C = zeros(n, p);
for i = 1:n
    for j = 1:p
        for k = 1:m
            C(i, j) = C(i, j) + A(i, k) * B(k, j);
        end
    end
end
```

## Exercice 5. [TD - Borne de tableau et espace mémoire] 练习 5. [TD - 数组边界和内存空间]

Considérons les trois tableaux:  $a[0:n]$ ,  $b[-1:n,1:m]$ ,  $c[-n:0,1:2]$ . Supposons que chaque élément de ces tableaux peut être stocké sur un mot mémoire. Combien de mots mémoire sont-ils nécessaires pour le stockage de ces trois tableaux?

考虑三个数组：$a[0:n]$、$b[-1:n,1:m]$、$c[-n:0,1:2]$。假设这些数组的每个元素都可以存储在一个内存字中，存储这三个数组需要多少个内存字？

### CorrEx5 更正练习 5

Le tableau  $a[0:n]$  contient  $n + 1$  éléments, le tableau  $b[-1:n,1:m]$  contient  $(n + 2) \times m$  éléments, et le tableau  $c[-n:0,1:2]$  contient  $(n + 1) \times 2$  éléments. Donc, le nombre total de mots mémoire nécessaires pour stocker ces trois tableaux est: $ (n + 1) + (n + 2) \times m + (n + 1) \times 2 $.
数组 $a[0:n]$ 包含 $n + 1$ 个元素，数组 $b[-1:n,1:m]$ 包含 $(n + 2) \times m$ 个元素，数组 $c[-n:0,1:2]$ 包含 $(n + 1) \times 2$ 个元素。因此，存储这三个数组所需的内存字总数为：$(n + 1) + (n + 2) \times m + (n + 1) \times 2$。
