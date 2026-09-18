# Ex02（2年考1次）

## CorrEx.1 1

### Hypothèses

- $A = A^{T}$, $(a_{ij}) = (a_{ji})$.
- Factorisations possibles :
  - $A = LU$, où $L \in \mathbb{R}^{n \times n}$ est triangulaire inférieure unitaire, $U \in \mathbb{R}^{n \times n}$ triangulaire supérieure.
  - On peut obtenir une factorisation $A = LDL^{T}$, avec $D \in \mathbb{R}^{n \times n}$ diagonale.
- Montrer l'existence et l'unicité de $A = LU$ sous cette hypothèse (L : unit lower triangular, u.l.t).

### Remarque 1 : Matrice triangulaire inférieure unitaire (u.l.t.)

$$
L =
\begin{bmatrix}
1 & & & & \\
X & \ddots & & & \\
X & X & \ddots & & \\
X & X & X & \ddots & \\
X & X & X & X & 1
\end{bmatrix}
$$

### Remarque 2 : La factorisation $LU$ (ULD) peut ne pas exister

Exemple :

$$
A \in \mathbb{R}^{3 \times 3},
\quad
A =
\begin{bmatrix}
1 & 2 & 3 \\
2 & 4 & 7 \\
3 & 5 & 3
\end{bmatrix}
$$

On cherche un $LU$ tel que

$$
A =
\begin{bmatrix}
1 & 0 & 0 \\
l_{21} & 1 & 0 \\
l_{31} & l_{32} & 1
\end{bmatrix}
\begin{bmatrix}
u_{11} & u_{12} & u_{13} \\
0      & u_{22} & u_{23} \\
0      & 0      & u_{33}
\end{bmatrix}.
$$

Les relations obtenues :

$$
a_{11} = 1 = u_{11}
$$
$$
a_{21} = 2 = l_{21} u_{11} = l_{21} \Rightarrow l_{21} = 2
$$
$$
a_{12} = 2 = u_{12}
$$
$$
a_{22} = 4 = l_{21} u_{12} + u_{22} = 4 + u_{22} \Rightarrow u_{22} = 0
$$
$$
a_{13} = 3 = u_{13}
$$
$$
a_{23} = 7 = l_{21} u_{13} + u_{23} = 6 + u_{23} \Rightarrow u_{23} = 1
$$
$$
a_{31} = 3 = l_{31} u_{11} = l_{31} \Rightarrow l_{31} = 3
$$
$$
\begin{aligned}
a_{32} &= 5 \neq l_{31} u_{12} + l_{32} u_{22} \\
       &= 6 + l_{32} \cdot 0 = 6
\end{aligned}
$$
$$
a_{33} = 3 = l_{31} u_{13} + l_{32} u_{23} + u_{33}
$$

Le déterminant de sous-matrice est nul, donc ça implique le $k$-ième pivot est nul : $u_{22} = 0$.

Alors le 2-ième pivot $\big(a_{22}^{(1)} = 0\big)$ est nul.

On peut généraliser et voir que si $\det\big(A(1:k,1:k)\big) = 0$, alors le $k$-ième pivot $a_{kk}^{(k-1)}$ est nul.

Notation du cour !!

### Théorème (LU)

Si $A \in \mathbb{R}^{n \times n}$ et $\det\big(A(1:k,1:k)\big) \neq 0$ pour $k = 1 : n-1$, alors il existe :

- une matrice "unit lower triangular"(u.l.t.) $L \in \mathbb{R}^{n \times n}$
- une matrice triangulaire supérieure $U \in \mathbb{R}^{n \times n}$

telles que $A = LU$.  
Si $A$ est inversible, la factorisation est unique et

$$
\det(A) = \prod_{i=1}^{n} u_{ii} = u_{11} \times u_{22} \times \dots \times u_{nn}.
$$

(Remarque: $\det(A \times B) = \det(A) \times \det(B)$.)

### a) Existence de la factorisation $A = LU$

Prouve (Démostration constructiviste) : on applique $k-1$ éliminations de Gauss. À l'étape k, on a

$$
M_{k-1} M_{k-2} \dots M_{2} M_{1} A = A,
$$

les matrices d'élimination u.l.t. d'où
$$
A(1:k,1:k) =
\begin{bmatrix}
1 & & & & \\
X & \ddots & & & \\
X & X & \ddots & & \\
X & X & X & \ddots & \\
X & X & X & X & 1
\end{bmatrix}
\begin{bmatrix}
a_{11}^{(k-1)}& X & X & X & X \\
              & \ddots & X & X & X \\
              &        & \ddots & X & X \\
              &        &        & \ddots & X \\
              &        &        &        & a_{kk}^{(k-1)}
\end{bmatrix}
$$

(Remarque: les matrices a droites ne sont pas complètes.)

Si $A(1:k,1:k)$ est inversible, alors

$$
\det\big(A(1:k,1:k)\big) = \prod_{i=1}^{k} a_{ii}^{(k-1)} \neq 0
$$

Donc le pivot $a_{kk}^{(k-1)}$ à l'étape $k$ est donc non nul. donc la factorisation existe.

#### b) Unicité

Supposons par l'absurde $A = L_{1} U_{1} = L_{2} U_{2}$ avec $L_i$ u.l.t., $U_i$ triangulaire sup., $\det(L_i) \neq 0$, $\det(U_i) \neq 0$, alors

$$
\begin{aligned}
L_{1} U_{1} = L_{2} U_{2}
&\iff L_{2}^{-1} L_{1} U_{1} = L_{2}^{-1} L_{2} U_{2} \quad (L_{2}^{-1} L_{2}\text{ est Identité}) \\
&\iff L_{2}^{-1} L_{1} U_{1} = U_{2} \\
&\iff L_{2}^{-1} L_{1} U_{1} U_{1}^{-1} = U_{2} U_{1}^{-1} \quad (U_{1} U_{1}^{-1}\text{ est Identité}) \\
&\iff L_{2}^{-1} L_{1} = U_{2} U_{1}^{-1}.
\end{aligned}
$$

(Remarques : inverses de matrices triangulaires inférieures sont aussi triangulaires inférieures. De même pour les triangulaires supérieures.)

Quelles sont les propriétés de $L_{2}^{-1} L_{1}$ et de $U_{2} U_{1}^{-1}$ ?

- $L_{2}^{-1}$ et $L_{1}$ sont u.l.t., le produit de 2 matrices u.l.t. est matrice u.l.t.
- $U_{2} U_{1}^{-1}$ est triangulaire supérieure.

Donc $L_{2}^{-1} L_{1} = U_{2} U_{1}^{-1} = I$ (Une matrice sup. equale a Une matrice inf. $\Rightarrow$ identité).

Donc $L_{1} = L_{2}$ et $U_{1} = U_{2}$.

Il suit de là que $A = LU$ est unique et

$$
\det(A) = \det(L) \times \det(U) = \prod_{i=1}^{n} u_{ii}.
$$

## ② Existence et unicité de $A = L D L^{T}$

Remarque : Soit l'exemple suivant $A \in \mathbb{R}^{2 \times 2}$, $A = A^{T}$,

$$
A =
\begin{bmatrix}
a & c \\
c & d
\end{bmatrix}=\begin{bmatrix}
1 & 0 \\
\tfrac{c}{a} & 1
\end{bmatrix}
\begin{bmatrix}
a & 0 \\
0 & d - \tfrac{c}{a} c
\end{bmatrix}
\begin{bmatrix}
1 & \tfrac{c}{a} \\
0 & 1
\end{bmatrix}.
$$

$$
L = \begin{bmatrix}
1 & 0 \\
\tfrac{c}{a} & 1
\end{bmatrix}, \quad D = \begin{bmatrix}
a & 0 \\
0 & d - \tfrac{c^{2}}{a}
\end{bmatrix}.
$$

### Théorème 2 (LDLᵀ)

Si $A \in \mathbb{R}^{n \times n}$ est symétrique et $A(1:k,1:k)$ est inversible pour $k = 1 : n-1$, alors il existe une matrice u.l.t. $L$ et une matrice diagonale $D = \operatorname{diag}(d_{1}, \dots, d_{n})$ telles que $A = L D L^{T}$, la factorisation est unique.

### Démonstration de Théorème 2

a) Existence

Soit $A = A^{T}$ et $A(1:k,1:k)$ est inversible pour $k = 1 : n-1$, alors il suit du théorème 1 qu'il existe une unique factorisation telle que $A = L U$, et comme $A = A^{T}$ on a $A = LU = (LU)^{T} = U^{T} L^{T} = A^{T}$.

On veut $A = L D L^{T}$ :
$$
\begin{aligned}
A = L D L^{T} &\iff L^{-1} A (L^{T})^{-1} = L^{-1} L D L^{T} (L^{T})^{-1} \\
&\iff L^{-1} A (L^{T})^{-1} = D \\
&\iff L^{-1} L U (L^{T})^{-1} = D
\end{aligned}
$$

Donc
$$
L^{-1} A (L^{T})^{-1} = U (L^{T})^{-1} \quad \text{(est-ce que $U (L^{T})^{-1}$ est diagonale ?)}
$$
avec $L^{-1}$ triangulaire inférieure, $U$ et $(L^{T})^{-1}$ triangulaires supérieures, donc $U (L^{T})^{-1}$ est triangulaire supérieure.

$$
\bigl(L^{-1} A (L^{T})^{-1}\bigr)^{T} = \bigl((L^{T})^{-1}\bigr)^{T} A^{T} (L^{-1})^{T} = L^{-1} A (L^{T})^{-1}.
$$

Donc $L^{-1} A (L^{T})^{-1}$ est matrice symétrique et $U (L^{T})^{-1}$ est triangulaire supérieure et symétrique.  
Ainsi $L^{-1} A (L^{T})^{-1}$ et $U (L^{T})^{-1}$ sont diagonaux.  
On pose $U (L^{T})^{-1} = D$.

b) Unicité

Par unicité de la factorisation $LU$, on obtient $A = L(U(L^{T})^{-1})L^{T} = L D L^{T}$ unique.

## ③ Algorithme LDLᵀ

- Factoriser $A = L D L^{T}$.
- Résoudre $Ax = b$ via :

$$
\begin{cases}
L z = b,\\
D y = z,\\
L^{T} x = y.
\end{cases}
$$

On effectue $n-1$ éliminations de Gauss. Pour $j = 1 : n-1$, on calcule $L(j+1:n, j)$ et $d_{j}$ à l'étape $j$. Écriture bloc :
$$
A =
\begin{bmatrix}
a_{11} & \cdots & a_{1j} & \cdots & a_{1n} \\
\vdots & & \vdots & & \vdots \\
a_{j1} & \cdots & a_{jj} & \cdots & a_{jn} \\
\vdots & & \vdots & & \vdots \\
a_{n1} & \cdots & a_{nj} & \cdots & a_{nn}
\end{bmatrix}
=
\underbrace{\begin{bmatrix}
1 & & & & \\
\ell_{21} & 1 & & & \\
\vdots & \ddots & \ddots & & \\
\ell_{j1} & \cdots & \ell_{j\,j-1} & 1 & \\
\vdots & & \vdots & & \ddots & \\
\ell_{n1} & \cdots & \ell_{n\,j-1} & \cdots & \cdots & 1
\end{bmatrix}}_{L}
\underbrace{\begin{bmatrix}
d_{1} & d_{1}\ell_{21} & \cdots & d_{1}\ell_{j1} & \cdots & d_{1}\ell_{n1} \\
& d_{2} & \cdots & d_{2}\ell_{j2} & \cdots & d_{2}\ell_{n2} \\
& & \ddots & \vdots & & \vdots \\
& & & d_{j} & \cdots & d_{j}\ell_{n\,j} \\
& & & & \ddots & \vdots \\
& & & & & d_{n}
\end{bmatrix}}_{U = D L^{T}}
$$

Pour $a_{jj}$ on écrit
$$
a_{jj} = L(j, 1:j-1)
\begin{bmatrix}
d_{1} l_{j1} \\
\vdots \\
d_{j-1} l_{j\,j-1}
\end{bmatrix}
 + d_{j}
 = d_{j} + \sum_{k=1}^{j-1} d_{k} l_{jk}^{2},
$$

d'où (étape [2])
$$
d_{j} = a_{jj} - \sum_{k=1}^{j-1} d_{k} l_{jk}^{2}.
$$

On considère ensuite $A(j+1:n, j)$ (étape [1]) :
$$
\begin{aligned}
A(j+1:n, j) &= L(j+1:n, 1:j)
\begin{bmatrix}
d_{1} l_{j1} \\
\vdots \\
d_{j-1} l_{j\,j-1} \\
d_{j}
\end{bmatrix} \\
&=
L(j+1:n, 1:j-1)
\begin{bmatrix}
d_{1} l_{j1} \\
\vdots \\
d_{j-1} l_{j\,j-1}
\end{bmatrix}
 + d_{j} \, L(j+1:n, j).
\end{aligned}
$$

On note $v(1:j) = [d_{1} l_{j1}, \dots, d_{j-1} l_{j\,j-1}, d_{j}]^{T}$ (étape [1]) et on écrit $A(j+1:n, j) = L(j+1:n, 1:j) v(1:j)$. Avec l'expression de $d_{j}$ ci-dessus (étape [2]), il suit la règle (étape [3]) pour $L(j+1:n, j)$ :
$$
L(j+1:n, j) = \frac{1}{d_{j}}
\Big[A(j+1:n, j) - L(j+1:n, 1:j-1)
\begin{bmatrix}
d_{1} l_{j1} \\
\vdots \\
d_{j-1} l_{j\,j-1}
\end{bmatrix}\Big].
$$

Boucle explicite (étapes [1] → [2] → [3] →(j+1)→ [1] ...) :

```matlab
% Version de boucle jik
for j = 1:n
    % [1]
    for i = 1:j-1
        v(i) = L(j, i) * d(i);
    end
    % [2]
    d(j) = A(j, j) - L(j, 1:j-1) * v(1:j-1)';
    % [3]
    L(j+1:n, j) = (A(j+1:n, j) - L(j+1:n, 1:j-1) * v(1:j-1)') / d(j);
end
```

Algorithme avec forme compacte (écrasement de $a_{ij}$ par $\ell_{ij}$ si $i \ge j$ et $d_{i}$ si $i=j$) :

```matlab
for j = 1:n
    % [1]
    for i = 1:j-1
        v(i) = A(j, i) * A(i, i);
    end
    % [2]
    A(j, j) = A(j, j) - A(j, 1:j-1) * v(1:j-1)';
    % [3]
    A(j+1:n, j) = (A(j+1:n, j) - A(j+1:n, 1:j-1) * v(1:j-1)') / A(j, j);
end
```

Remarque 3 : Complexité de l'algorithme LDLᵀ

- Étape [1] : j-1 multiplications
- Étape [2] : j-1 multiplications + 1 soustraction = j fois flops
- Étape [3] :
    - Produit matrice-vecteur : (n-j) × (j-1) multiplications + (n-j) × (j-2) additions = (n-j)(2j-3) fois flops
    - 1 division par A(j, j)

On calecule le total des opérations arithmétiques :
$$
\begin{aligned}
\text{Total} &= \sum_{j=1}^{n} \big[ (j-1) + j + (n-j)(2j-3) + 1 \big] \\
&= \sum_{j=1}^{n} \big[ 2nj - 2j^{2} + 2j + n - 2 \big] \\
&= 2n \sum_{j=1}^{n} j - 2 \sum_{j=1}^{n} j^{2} + 2 \sum_{j=1}^{n} j + \sum_{j=1}^{n} (n - 2) \\
&= 2n \cdot \frac{n(n+1)}{2} - 2 \cdot \frac{n(n+1)(2n+1)}{6} + 2 \cdot \frac{n(n+1)}{2} + n(n - 2) \\
&= n^{3} - \frac{2}{3} n^{3} + O(n^{2}) \\
&= \frac{1}{3} n^{3} + O(n^{2}).
\end{aligned}
$$

## ④ Test de validation de l'algorithme LDLᵀ

Soient les matrices $L, D \in \mathbb{R}^{3 \times 3}$ telles que

$$
L = \begin{pmatrix}
1 & 0 & 0 \\
2 & 1 & 0 \\
3 & 4 & 1
\end{pmatrix},
\quad
D = \begin{pmatrix}
2 & 0 & 0 \\
0 & 3 & 0 \\
0 & 0 & 4
\end{pmatrix}.
$$

Proposez une procédure pour un test de validation de votre algorithme. Vous préciserez quelle matrice passer en entrée de l'algorithme et quelle métrique utiliser pour savoir si le résultat est valide.

Procédure de validation :

- Construction de la matrice de test : former $A_{\text{test}} = L D L^{T}$ à partir des $L, D$ fournis (on peut développer en 3×3 si besoin, mais ce n'est pas requis). $A_{\text{test}}$ est par construction factorisable.
- Exemple développé (optionnel) : pour ces $L, D$, on obtient
  $$
  A_{\text{test}} = L D L^{T} =
  \begin{pmatrix}
  2 & 6 & 8 \\
  6 & 35 & 46 \\
  8 & 46 & 77
  \end{pmatrix}.
  $$
- Application de l'algorithme : appliquer l'algorithme $LDL^{T}$ à $A_{\text{test}}$ pour obtenir $(\hat{L}, \hat{D})$.
- Calcul de l'erreur (métrique) : mesurer l'erreur relative
  $$
  \varepsilon = \frac{\big\|A_{\text{test}} - \hat{L} \hat{D} \hat{L}^{T}\big\|_{F}}{\big\|A_{\text{test}}\big\|_{F}},
  $$
  la norme de Frobenius quantifiant l'écart global. Si $\varepsilon$ est proche de la précision machine (par exemple $< 10^{-12}$), le résultat est validé.
