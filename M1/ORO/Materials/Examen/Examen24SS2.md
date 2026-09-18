# Examen de recherche opérationnelle SS2 运筹学考试 SS2

20 Juin 2024

## Exercice 1 : Ordonnancement 练习 1：排程

Dans le tableau ci-dessous sont récapitulées les 10 principales tâches d'un projet, avec la durée probable de chacune et ses contraintes d'antériorité. 下表汇总了一个项目中的 10 个主要任务，以及每个任务的预计工期和前置约束。

| Nom de la tâche 任务名称 | Durée 工期 | Antériorités 前置关系 |
| --- | ---: | --- |
| A | 10 | - |
| B | 7 | - |
| C | 6 | A |
| D | 6 | A, B |
| E | 3 | C |
| F | 5 | C |
| G | 8 | C, D |
| H | 6 | D |
| I | 4 | G |
| J | 3 | E, H |

Résoudre ce problème par la méthode des potentiels. Indiquer clairement la durée totale minimale et le calendrier prévisionnel d'exécution des tâches, avec les tâches critiques, les marges totales et les marges libres. 用势方法求解这个问题，并清楚给出最短总工期、任务的预计执行日程、关键任务、总时差和自由时差。

## Exercice 2 : Modélisation 练习 2：建模

On cherche à produire un bronze, alliage de cuivre, d'étain, et de plomb. Cet alliage devra contenir au moins deux fois plus de cuivre que d'étain, et trois fois plus que de plomb. Il devra contenir moins de plomb que d'étain, et au moins un quart d'étain. 我们希望生产一种青铜合金，由铜、锡和铅组成。该合金中铜至少应是锡的两倍、铅的三倍；铅应少于锡，并且锡至少占总量的四分之一。

Le plomb coûte 10€ la tonne, l'étain 15, et le cuivre 12. 铅每吨 10 欧元，锡每吨 15 欧元，铜每吨 12 欧元。

On cherche la proportion (en pourcentage) de chacun des composants qui minimise le coût de production. 我们希望求出各成分的百分比，使生产成本最小。

1. Modélisez ce problème sous forme de programme linéaire en précisant ce que représente chacune des variables que vous utiliserez. 将该问题建模成线性规划，并说明每个变量的含义。
2. Exprimez une variable en fonction des autres et simplifiez le programme linéaire de la question précédente. 用其他变量表示其中一个变量，并化简上一问得到的线性规划。

## Exercice 3 : Programmation linéaire en nombres entiers 练习 3：整数线性规划

On cherche à résoudre le programme linéaire en nombres entiers suivant : 我们希望求解下面这个整数线性规划：

\[
(P_0) : \max \{10x_1 + 12x_2\}
\]

s.c.

\[
\begin{cases}
4x_1 - 4x_2 \leq 6 \\
4x_1 + 5x_2 \leq 15 \\
-2x_1 + 2x_2 \leq 3 \\
x_1, x_2 \in \mathbb{N}
\end{cases}
\]

Complétez au fur et à mesure l'arbre binaire des sous-problèmes rencontrés. 请随着解题过程逐步补全遇到的子问题二叉树。

1. Résolvez la relaxation continue de \((P_0)\). 求解 \((P_0)\) 的连续松弛。

2. On effectue la séparation selon la variable \(x_1\). \((P_1)\) désigne le sous-problème obtenu en ajoutant une contrainte \(x_1 \leq 2\). Écrivez le premier tableau de simplex de la relaxation continue de \((P_1)\) (on ne demande pas de résoudre ce problème !) 我们按变量 \(x_1\) 进行分支。\((P_1)\) 表示在原问题基础上加入约束 \(x_1 \leq 2\) 得到的子问题。写出 \((P_1)\) 的连续松弛对应的第一个单纯形表（不要求求解）。

3. \((P_2)\) désigne le sous-problème obtenu en ajoutant à \((P_0)\) la contrainte \(x_1 \geq 3\). Réécrivez \((P_2)\) pour remplacer cette contrainte par la contrainte \(x'_1 \geq 0\). Expliquez, sans utiliser la méthode du grand \(M\), pourquoi ce problème n'a pas de solution réalisable. \((P_2)\) 表示在 \((P_0)\) 中加入约束 \(x_1 \geq 3\) 得到的子问题。请把 \((P_2)\) 重写成用约束 \(x'_1 \geq 0\) 表示的形式，并且在不使用大 \(M\) 法的情况下说明为什么该问题没有可行解。

4. Le dernier tableau de simplex obtenu pour \((P_1)\) est le suivant :

    | Base | \(x_1\) | \(x_2\) | \(y_1\) | \(y_2\) | \(y_3\) | \(y_4\) | Second membre |
    | --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
    | \(y_1\) | 0 | 0 | 1 | \( \frac{4}{5} \) | 0 | \( -\frac{36}{5} \) | \( \frac{18}{5} \) |
    | \(x_1\) | 1 | 0 | 0 | 1 | 0 | 1 | 2 |
    | \(x_2\) | 0 | 1 | 0 | \( \frac{1}{5} \) | 0 | \( \frac{4}{5} \) | \( \frac{7}{5} \) |
    | \(y_3\) | 0 | 0 | 0 | \( -\frac{2}{5} \) | 0 | \( \frac{18}{5} \) | \( \frac{21}{5} \) |
    | | 0 | 0 | 0 | \( -\frac{12}{5} \) | 0 | \( -\frac{2}{5} \) | \( -\frac{184}{5} \) |

    Donnez la solution optimale du problème \((P'_1)\), et décrivez la manière dont \(P_1\) va être séparé. Donnez, sans utiliser l'algorithme du simplexe, la solution optimale de \((P_3)\). 给出问题 \((P'_1)\) 的最优解，并说明 \(P_1\) 将如何继续分支。不要使用单纯形算法，直接给出 \((P_3)\) 的最优解。

5. Le problème \((P_4)\) équivaut à (la contrainte \(x_1 \leq 1\) devient redondante avec les autres contraintes ; on pose \(x'_2 = x_2 - 2\)) :

    \[
    (P'_4) : 24 + \max \{10x_1 + 12x'_2\}
    \]

    s.c.

    \[
    \begin{cases}
    4x_1 - 4x'_2 \leq 14 \\
    4x_1 + 5x'_2 \leq 5 \\
    -2x_1 + 2x'_2 \leq -1 \\
    x_1, x'_2 \in \mathbb{N}
    \end{cases}
    \]

    Résolvez sa relaxation continue en utilisant la méthode du grand \(M\). 用大 \(M\) 法求解它的连续松弛。

6. Le problème \((P_6)\) consiste à ajouter à \((P_4)\) la contrainte \(x_1 \geq 2\). justifiez qu'il n'admet aucune solution réalisable. Le problème \((P_5)\) revient à ajouter à \((P_0)\) les contraintes \(x_1 \leq 1\) et \(x_2 \geq 2\). sa relaxation continue a pour solution optimale \((1, \frac{11}{5})\) de valeur \( \frac{182}{5} \). Déduisez en \((P_7)\) et \((P_8)\), donnez leur solution sans calcul, et concluez. 问题 \((P_6)\) 是在 \((P_4)\) 中加入约束 \(x_1 \geq 2\) 得到的。说明为什么它没有可行解。问题 \((P_5)\) 则是在 \((P_0)\) 中加入约束 \(x_1 \leq 1\) 和 \(x_2 \geq 2\) 得到的，它的连续松弛最优解为 \((1, \frac{11}{5})\)，目标值为 \( \frac{182}{5} \)。由此推出 \((P_7)\) 和 \((P_8)\)，不给计算过程直接写出它们的解，并作出结论。
