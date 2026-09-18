# Exercice 3 – Méthodes itératives et matrices tridiagonales (Correction du Examen 24-25)

On cherche à résoudre le système linéaire $T_\delta x = b$ par une méthode itérative avec $T_\delta = \operatorname{trid}(-1,\delta,-1) \in \mathbb{R}^{n \times n}$ , matrice tridiagonale inversible, $x, b \in \mathbb{R}^n$ et $\delta \in \mathbb{R}$.

## 1. *(0,5)*

Vérifiez que les valeurs propres $\lambda_j$ de $T_\delta$ sont
$$
\lambda_j = \delta - 2\cos(j\theta)
$$
$\forall j \in \{1,\dots,n\}$, avec $\theta = \frac{\pi}{n+1}$, avec pour chaque $\lambda_j$, le vecteur propre associé $v_j$ est tel que
$$
(v_j)_i = (\sin(ij\theta))_i
$$

**ans :**

1. **Analyse**

    On veut montrer que, pour la matrice tridiagonale $T_\delta = \operatorname{trid}(-1,\delta,-1)$, les valeurs propres sont données par $\lambda_j = \delta - 2\cos(j\theta)$
    avec $\theta = \frac{\pi}{n+1}$, et les vecteurs propres associés sont $(v_j)_i = (\sin(ij\theta))_i$.

    Par définition, une valeur propre $\lambda_j$ et un vecteur propre $v_j$ satisfont l'équation
    $$
    T_\delta v_j = \lambda_j v_j
    $$

    En composantes, cela s'écrit pour chaque $i$ :
    $$
    - v_{i-1} + \delta v_i - v_{i+1} = \lambda_j v_i
    $$
    avec les conditions aux bords $v_0 = 0$ et $v_{n+1} = 0$.

    On réarrange cette équation pour obtenir :
    $$
    - v_{i-1} - v_{i+1} + (\delta - \lambda_j) v_i = 0.
    $$

    On propose une solution de la forme $v_i = \sin(i j \theta)$, où $\theta = \frac{\pi}{n+1}$ et $j$ est un entier entre 1 et $n$. En substituant cette forme dans l'équation, on obtient :
    $$
    \begin{aligned}
    &- \sin((i-1) j \theta) - \sin((i+1) j \theta) + (\delta - \lambda) \sin(i j \theta) = 0. \\
    &\iff - 2 \sin(i j \theta) \cos(j \theta) + (\delta - \lambda) \sin(i j \theta) = 0. \\
    &\iff (\delta - \lambda - 2 \cos(j \theta)) \sin(i j \theta) = 0.
    \end{aligned}
    $$

    D'après la formule $\sin(a) + \sin(b) = 2 \sin\left(\frac{a+b}{2}\right) \cos\left(\frac{a-b}{2}\right)$.

    Comme $v$ est un vecteur propre non nul, il existe au moins un indice $i$ tel que $\sin(ij\theta)\neq 0$. Pour cet indice, on doit donc avoir
    $$
    \delta - \lambda - 2 \cos(j \theta) = 0,
    $$
    ce qui donne :
    $$
    \lambda = \delta - 2 \cos(j \theta).
    $$

2. **Synthèse**

    Enfin, la condition aux bords est vérifiée : $v_0 = \sin(0) = 0$ et, comme $\theta = \frac{\pi}{n+1}$, on a $v_{n+1} = \sin((n+1)j\theta) = \sin(j\pi) = 0$. Ainsi, pour $j = 1,\dots,n$, les valeurs propres de $T_\delta$ sont bien $\lambda_j = \delta - 2\cos(j\theta)$ avec les vecteurs propres associés $(v_j)_i = \sin(ij\theta)$.

**ans :** En deux lignes (analyse → synthèse) :

1. **Analyse** : poser $v_i=\sin(ij\theta)$ (respecte $v_0=v_{n+1}=0$) et le mettre dans $-v_{i-1}+\delta v_i-v_{i+1}=\lambda v_i$ donne, via $\sin a+\sin b=2\sin\frac{a+b}{2}\cos\frac{a-b}{2}$,
   $$
   (\delta-\lambda-2\cos(j\theta))\sin(ij\theta)=0 \;\Rightarrow\; \lambda=\delta-2\cos(j\theta).
   $$

2. **Synthèse** : avec cette $\lambda$, l’équation est satisfaite et les bords aussi ($\sin(0)=0$, $\sin((n+1)j\theta)=\sin(j\pi)=0$), donc pour $j=1,\dots,n$ on obtient bien les paires propres $(\lambda_j,v_j)$ annoncées.

## 2. *(0,5)*

Sous quelle condition sur $\delta$ la matrice $T_\delta$ est-elle définie positive ?

**ans :**

Pour que la matrice $T_\delta$ soit définie positive, toutes ses valeurs propres doivent être strictement positives. Les valeurs propres de $T_\delta$ sont données par :
$$
\lambda_j = \delta - 2\cos(j\theta),
$$
où $\theta = \frac{\pi}{n+1}$ et $j = 1,\dots,n$.

Comme $j\theta$ parcourt $[\theta,\pi-\theta]$ et que $\cos$ est décroissante sur $[0,\pi]$, le maximum de $\cos(j\theta)$ est atteint pour $j=1$, donc
$$
\lambda_{\min} = \delta - 2\cos\left(\tfrac{\pi}{n+1}\right).
$$
Pour que $T_\delta$ soit définie positive, il faut $\lambda_{\min} > 0$, soit
$$
\boxed{\delta > 2\cos\left(\tfrac{\pi}{n+1}\right)}.
$$

## 3. *(0,5)*

On pose $\delta = 2$.
À quel problème peut être associé l'opérateur $T_2$ ? Quelles sont les propriétés de la matrice $T_2$ ?

**ans :**

$T_2 = \operatorname{trid}(-1,2,-1)$ est la discrétisation en différences finies centrées du problème de Poisson 1D
$$
-u'' = f \ \text{sur }(0,1),\quad u(0)=u(1)=0.
$$
Sur le maillage $x_i = ih$ avec $h=\tfrac{1}{n+1}$ et $u_i \approx u(x_i)$, on obtient le schéma
$$
\frac{-u_{i-1} + 2u_i - u_{i+1}}{h^2} = f(x_i),\quad i=1,\dots,n,
$$
soit le système $T_2\,u = h^2 f$.

Propriétés :

1. **Symétrie** : $T_2^T = T_2$.
2. **Définie positive** : valeurs propres $\lambda_j = 2 - 2\cos(j\theta)$ avec $\theta = \tfrac{\pi}{n+1}$, toutes strictement positives.
3. **Tridiagonale Toeplitz** : coefficients constants sur chaque diagonale, seuls $(i,i)$, $(i,i+1)$, $(i+1,i)$ sont non nuls.

## 4. *(0,5)*

Soit le processus itératif de Richardson :
$$
x^{k+1} = x^k + M^{-1}(b - T_\delta x^k).
$$
Sous quelle condition obtient-on un processus itératif de **Jacobi** ?
Définir la matrice $M$ pour obtenir une méthode de Jacobi.

**ans :**

On choisit le préconditionneur égal à la diagonale de $T_\delta$, c'est-à-dire
$$
M = D = \operatorname{trid}(0,\delta,0) = \delta I.
$$
Le schéma devient alors l'itération de Jacobi :
$$
x^{k+1} = x^k + D^{-1}(b - T_\delta x^k).
$$

## 5. *(1)*

On pose
$$
D = \operatorname{trid}(0,\delta,0), \qquad
E = \operatorname{trid}(1,0,0), \qquad
F = \operatorname{trid}(0,0,1).
$$
Montrer que la matrice d'itération de Jacobi peut s'écrire
$$
G_J = D^{-1}(E + F).
$$

**ans :**

On décompose $T_\delta = D - E - F$. Par définition de Jacobi,
$$
G_J = I - D^{-1}T_\delta = I - D^{-1}(D - E - F) = D^{-1}(E + F).
$$
On retrouve la forme annoncée.

## 6. *(2)*

Montrer que la méthode de Jacobi converge pour $T_2$, c'est-à-dire montrer que
$$
\rho(G_J) < 1.
$$
**Remarque :** pour une méthode de Richardson où $M^{-1} = \alpha I_n$, la matrice d'itération est
$$
G_R = I - \alpha T_\delta
$$
avec $\alpha \in \mathbb{R}^+$, et les valeurs propres $\mu_i$ de $G_R$ vérifient
$$
1 - \alpha \lambda_{\max} \le \mu_i \le 1 - \alpha \lambda_{\min}.
$$

**ans :** (version compacte, avec notations explicites)

On note $\mu_j$ les valeurs propres de la matrice d'itération $G_J$.

Pour Jacobi, $G_J = I - D^{-1}T_\delta$ avec $D=\delta I$, donc $G_J = I - \tfrac{1}{\delta}T_\delta$.
Le spectre de $T_\delta$ est $\lambda_j = \delta - 2\cos(j\theta)$ avec $\theta = \tfrac{\pi}{n+1}$ et $j=1,\dots,n$, et une base propre $(v_j)$.

Appliqué à un vecteur propre $v_j$ :

$$
G_J v_j = \Bigl(I - \tfrac{1}{\delta}T_\delta\Bigr)v_j = \Bigl(1 - \tfrac{\lambda_j}{\delta}\Bigr)v_j,
$$

d'où $\mu_j = 1 - \tfrac{\lambda_j}{\delta} = \tfrac{2}{\delta}\cos(j\theta)$.

Pour $T_2$ (donc $\delta=2$), $\mu_j = \cos(j\theta)$, $\theta = \tfrac{\pi}{n+1}$, et
$$
\rho(G_J) = \max_j |\mu_j| = \cos\Bigl(\tfrac{\pi}{n+1}\Bigr) < 1
$$
car $\tfrac{\pi}{n+1}\in(0,\pi/2]$. Jacobi converge donc pour $T_2 x = b$.

## 7. *(0,5)*

Quel est le rayon de convergence de cette méthode de Jacobi ?

**ans :**

Pour $T_2$, $\rho(G_J) = \cos\left(\tfrac{\pi}{n+1}\right)$.
Plus généralement, $\rho(G_J) = \frac{2}{\delta}\cos\left(\tfrac{\pi}{n+1}\right)$

## 8. *(0,5)*

Montrer que la matrice d'itération de **Gauss–Seidel** peut s'écrire
$$
G_{GS} = (D - E)^{-1} F.
$$

**ans :**

On écrit $T_\delta = D - E - F$ et on résout à chaque pas
$$
(D - E)x^{k+1} = Fx^k + b.
$$
En isolant $x^{k+1}$, on obtient l'itération
$$
x^{k+1} = (D - E)^{-1}F x^k + (D - E)^{-1}b,
$$
d'où la matrice d'itération $G_{GS} = (D - E)^{-1}F$.

## 9. *(0,5)*

Si $\rho(G_{GS}) = \cos^2 \theta$, que dire de la vitesse de convergence de Jacobi par rapport à celle de Gauss–Seidel ?

**ans :**

Pour ces tridiagonales SPD, $\rho(G_J) = \cos\theta$ et $\rho(G_{GS}) = \cos^2\theta = [\rho(G_J)]^2 < \rho(G_J)$.
Gauss–Seidel converge plus vite : son rayon spectral est le carré de celui de Jacobi, donc il faut en gros deux fois moins d'itérations pour une réduction d'erreur comparable.

## 10. *(0,5)*

Écrire l'algorithme de résolution du système linéaire $T_2 x = b$ par la méthode itérative de Jacobi.

**ans :**

Pour $T_2 = \operatorname{trid}(-1,2,-1)$ (donc $D=2I$, $E=F=-I$), l’itération de Jacobi $x^{k+1}=D^{-1}(E+F)x^k + D^{-1}b$ donne, pour $i=1,\dots,n$,
$$
x_i^{k+1} = \tfrac{1}{2}\bigl(b_i + x_{i-1}^k + x_{i+1}^k\bigr),
$$
avec $x_0^k = x_{n+1}^k = 0$ (conditions de Dirichlet).

Pseudo-code (arrêt dès que l'écart est sous une tolérance `tol`) :

```matlab
for k = 1:kmax
    x_old = x;
    for i = 1:n
        xm = (i>1)*x_old(i-1);
        xp = (i<n)*x_old(i+1);
        x(i) = 0.5*(b(i) + xm + xp);
    end
    if norm(x - x_old) < tol, break; end
end
```
