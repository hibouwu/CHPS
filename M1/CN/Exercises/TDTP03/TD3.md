# TD/TP 3 DE CALCUL NUMÉRIQUE Résolution de système linéaire 数值计算 TD/TP 3 线性系统求解

## T. Dufaud ([thomas.dufaud@uvsq.fr](mailto:thomas.dufaud@uvsq.fr)) T. Dufaud（[thomas.dufaud@uvsq.fr](mailto:thomas.dufaud@uvsq.fr)）

—M1 CHPS—
—M1 CHPS— CHPS 硕士一年级

Cette fiche de TD/TP est associée au cours de calcul numérique sur l'algèbre linéaire. Elle a pour objectifs :
这份 TD/TP 讲义对应线性代数的数值计算课程，目标如下：

- Découvrir un langage haut niveau, type DSL, pour le calcul scientifique.  
了解用于科学计算的高级语言（DSL 类型）。  
- Savoir implémenter un algorithme pour le calcul numérique.  
掌握数值计算算法的实现。  
- Comprétre les performances et les limites d'un algorithmes.
理解算法的性能与局限。  
- Comparator les performances.  
比较性能表现。  
- Résoudre des systèmes linéaires.
求解线性系统。

L'exercice 1 (TD) est à réaliser sur feuille. Les exercices 2, 3 et 4 (TP) sont à réaliser sur machine avec Scilab. Un compte rendu doit être réalisé. Ce compte rendu doit comprendre l'analyse des algorithmes implémentés, vos observations et analyses d'algorithmme, ainsi que des mesures de performance. Il complete le compte rendu du TD/TP 2.
练习 1（TD）需在纸上完成；练习 2、3、4（TP）需在 Scilab 上机完成。必须撰写一份报告，其中包括对实现算法的分析、对算法的观察与分析，以及性能测试；该报告补充 TD/TP 2 的内容。

## Exercice 1. [TD - Matrice triangulaire et méthode directe] 练习 1. [TD - 三角矩阵与直接法]

On souhaite résoudre le système  $Ax = b$ , où  $A$  est une matrice triangulaire inférieure de taille  $n \times n$  à coefficients réels,  $x, b \in \mathbb{R}^n$ .
考虑求解系统 $Ax = b$，其中 $A$ 是一个 $n \times n$ 的实下三角矩阵，$x, b \in \mathbb{R}^n$。

- Ecrivez la procEDURE de résolution directe par la méthode de descente.  
写出使用前代法直接求解的过程。  
- Quelle est la complexité de cet algorithme?  
该算法的复杂度是多少？  
- Quelle est l'occupation mémoire de votre procédure?
你的过程占用多少内存？

```matlab
function [x] = lsolve(L, b)
    n = size(L, 1);
    x = zeros(n, 1);
    for i = 1:n
        sum = 0;
        for j = 1:i-1
            sum = sum + L(i, j) * x(j);
        end
        x(i) = (b(i) - sum) / L(i, i);
    end
end
```

## Exercise 2. TP - Systeme triangulaire 练习 2. TP - 三角系统

1. Ecrivez les algorithmes 10 et 11 (diapo 22) de résolution par remontée et descente. On cree 2 fichiers usolve.sci et lsolve.sci avec les en-têtes :
编写幻灯片 22 中算法 10 与 11 的回代和前代求解器，创建函数文件 usolve.sci 与 lsolve.sci，文件头如下：

    $$
    function[x] = usolve(U, b)
    $$
    et
    $$
    function[x] = lsolve(L, b)
    $$

    Voir le fichier cn-tdtp3/lsolve.m et cn-tdtp3/usolve.m.

2. Tester et valider vos algorithmes (cf TD/TP 1). On peut s'aider des fonctions tril() et triu() qui permettent d'extraire une matrice triangulaire inférieure ou supérieur.
测试并验证你的算法（参见 TD/TP 1），可借助 tril() 和 triu() 函数提取下/上三角矩阵。

## Exercise 3. TP - Gauss 练习 3. TP - 高斯法

1. Ecrivez l'algorithmme 12 (diapo 27) de résolution par élimination de Gauss sans pivotage. On create 1 fichier gausskij3b.sci
编写幻灯片 27 中算法 12 的无主元高斯消元求解器，并创建 gausskij3b.sci 文件。

    $$
    function  [x] =  gausskij3b(A,b)
    $$

2. Testez et validez votre algorithme sur de petites matrices.
在小型矩阵上测试并验证你的算法。

## Exercise 4. TP - LU 练习 4. TP - LU

1. Ecrire l'algorithmme 13 (diapo 30) de factorisation LU
编写幻灯片 30 中算法 13 的 LU 分解。
    $$
    function [\mathrm{L},\mathrm{U}] = \mathrm{mylu3b(A)}
    $$

2. Testez et validez votre algorithme sur de petites matrices. On calculera l'erreur commise sur la factorisation  $LU: A - LU$ .  
在小型矩阵上测试并验证算法，并计算 LU 分解的误差 $A - LU$。  
3. Améliorez l'algorithmé 13 (diapo 30) de factorisation LU de sorte à n'obtenir qu'une boucle.  
改进幻灯片 30 的算法 13，使其只用一个循环完成 LU 分解。  
4. Ajoutez la méthode de pivot partiel.
加入部分主元策略。

    $$
    function [\mathrm{L},\mathrm{U},\mathrm{P}] = \mathrm{mylu}(\mathrm{A})
    $$

5. Comparez avec la fonction  $lu()$  de Scilab.  
将结果与 Scilab 的 $lu()$ 函数比较。  
6. Appliquees mylu et lu aux matrices de T. Davis. On effectue la lecture avec la fonction mmread. (OPTIONNEL)
对 T. Davis 的矩阵应用 mylu 与 lu，并使用 mmread 函数读取数据。（可选）

## Exercise 5. Poisson 1D (OPTIONNEL) 练习 5. 一维泊松问题（可选）

1. Écrire une matrice  $A$  du problème de poisson 1D de taille  $n$  (Equation de la chaleur 1D stationnaire).  
写出尺寸为 $n$ 的一维泊松问题（即稳态一维热方程）矩阵 $A$。  
2. Écrire le second membre et la solution analytique.  
写出右端项与解析解。  
3. Résoudre le système pour différentes tailles de  $A$  avec  $LU$ . Critiquez les résultats en tenant compte du conditionnement de  $A$ .  
对不同尺寸的 $A$ 使用 LU 分解求解系统，并结合 $A$ 的条件数分析结果。  
4. Tracer la solution avec plot()  
使用 plot() 绘制解。  
5. Résoudre le système pour différentes tailles de  $A$  en utilisant une factorisation de Cholesky. On utilisera la fonction chol().  
对不同尺寸的 $A$ 使用 Cholesky 分解（chol()）求解系统。  
6. Ecrire un algorithme LU pour une matrice tridiagonale. Comparez vos performances avec les algorithmes précédents.
编写适用于三对角矩阵的 LU 算法，并与前述算法比较性能。
