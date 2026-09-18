# Examen de recherche opérationnelle SS2 运筹学考试 SS2

10 mai 2023

## Exercice 1 : Ordonnancement 练习 1：排程

La mise en exploitation d'un nouveau gisement minier demande la réalisation d'un certain nombre de tâches. Le tableau suivant représente ces différentes tâches avec leurs relations d'antériorité. 一个新的矿床投入开采需要完成若干任务。下表给出了这些任务及其前置关系。

| Nom 名称 | Description de la tâche 任务描述 | Durée (en jours) 工期（天） | Antériorités 前置关系 |
| --- | --- | ---: | --- |
| A | obtention d'un permis d'exploitation | 120 | - |
| B | établissement d'une piste de 6 km | 180 | A |
| C | transport et installation à pied d'œuvre de 2 sondeuses | 3 | B |
| D | création de bâtiments provisoires | 30 | B |
| E | goudronnage de la piste | 60 | B |
| F | adduction d'eau | 90 | D |
| G | campagne de sondage | 240 | C, D |
| H | forage et équipement de trois puits | 180 | E, F, G |
| I | transport et installation au fond du matériel d'exploitation | 30 | J, H |
| J | construction de bureaux et logements, ouvriers et ingénieurs | 240 | E, F, G |
| K | traçage et aménagement du fond | 360 | J, H |
| L | construction d'une laverie | 240 | J, H |

### Questions 问题

1. Résoudre ce problème par la méthode de votre choix. Indiquer clairement la durée totale minimum et le calendrier prévisionnel d'exécution des tâches. 用你选择的方法求解该问题，并明确给出最短总工期和任务的预计执行日程。
2. Quelles sont les tâches critiques ? Pour les autres tâches, donner les marges totales et libres. 哪些是关键任务？对于其他任务，给出总时差和自由时差。

## Exercice 2 : Modélisation 练习 2：建模

Un atelier peut fabriquer trois types de jouets : 一个工坊可以生产三种玩具：

- des avions à la cadence de 35 objets à l'heure ; 飞机，每小时 35 件；
- des bateaux à la cadence de 45 objets à l'heure ; 船，每小时 45 件；
- des camions à la cadence de 20 objets à l'heure. 卡车，每小时 20 件。

Cette fabrication utilise une machine-outil unique, disponible 240 heures par mois. 生产只使用一台机床，每月可用 240 小时。

Le bénéfice unitaire pour chaque avion produit est de 60 euros, pour chaque bateau de 40 euros, et pour chaque camion de 80 euros. Ces objets sont vendus en totalité à des grossistes ; on a observé qu'on ne pouvait écouler, par mois, plus de 4000 avions, ni plus de 6000 bateaux, ni plus de 3000 camions. 每生产一架飞机的单位利润是 60 欧元，每条船 40 欧元，每辆卡车 80 欧元。这些产品全部卖给批发商；经观察，每月最多只能销售 4000 架飞机、6000 条船和 3000 辆卡车。

D'autre part, chaque objet doit être vérifié avant sa commercialisation ; une équipe de trois techniciens est chargée de cette mission ; chaque technicien travaille 160 heures par mois. La vérification d'un avion prend cinq minutes, d'un bateau, trois minutes, d'un camion, deux minutes. 此外，每件产品在销售前都必须经过检验；这项工作由 3 名技术员负责，每名技术员每月工作 160 小时。检验一架飞机需要 5 分钟，一条船 3 分钟，一辆卡车 2 分钟。

Modélisez cette situation par un programme linéaire. 请把这一情形建模成一个线性规划。

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

1. Résolvez la relaxation continue de \((P_0)\). 求 \((P_0)\) 的连续松弛。
2. On effectue la séparation selon la variable \(x_1\). \((P_1)\) désigne le sous-problème obtenu en ajoutant une contrainte \(x_1 \leq 2\). Écrivez le premier tableau de simplex de la relaxation continue de \((P_1)\) (on ne demande pas de résoudre ce problème). 我们按变量 \(x_1\) 分支。\((P_1)\) 表示加入约束 \(x_1 \leq 2\) 后得到的子问题。请写出 \((P_1)\) 的连续松弛对应的第一个单纯形表（不要求求解）。
3. \((P_2)\) désigne le sous-problème obtenu en ajoutant à \((P_0)\) la contrainte \(x_1 \geq 3\). Réécrivez \((P_2)\) pour remplacer cette contrainte par la contrainte \(x'_1 \geq 0\). Expliquez sans utiliser la méthode du grand \(M\), pourquoi ce problème n'a pas de solution réalisable. \((P_2)\) 表示在 \((P_0)\) 中加入约束 \(x_1 \geq 3\) 得到的子问题。请将其改写成使用约束 \(x'_1 \geq 0\) 的形式，并在不使用大 \(M\) 法的情况下说明为什么这个问题没有可行解。
4. Le dernier tableau de simplex obtenu pour \((P_1)\) est le suivant :

    | Base | \(x_1\) | \(x_2\) | \(y_1\) | \(y_2\) | \(y_3\) | \(y_4\) | Second membre |
    | --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
    | \(y_1\) | 0 | 0 | 1 | \( \frac{4}{5} \) | 0 | \( -\frac{36}{5} \) | \( \frac{18}{5} \) |
    | \(x_1\) | 1 | 0 | 0 | 1 | 0 | 1 | 2 |
    | \(x_2\) | 0 | 1 | 0 | \( \frac{1}{5} \) | 0 | \( \frac{4}{5} \) | \( \frac{7}{5} \) |
    | \(y_3\) | 0 | 0 | 0 | \( -\frac{2}{5} \) | 1 | \( \frac{18}{5} \) | \( \frac{21}{5} \) |
    | | 0 | 0 | 0 | \( -\frac{12}{5} \) | 0 | \( -\frac{2}{5} \) | \( -\frac{184}{5} \) |

    Donnez la solution optimale du problème \((P'_1)\), et décrivez la manière dont \(P_1\) va être séparé. Donnez, sans utiliser l'algorithme du simplexe, la solution optimale de \((P_3)\). 给出问题 \((P'_1)\) 的最优解，并说明 \(P_1\) 将如何继续分支。不使用单纯形算法，直接给出 \((P_3)\) 的最优解。

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

6. Le problème \((P_6)\) consiste à ajouter à \((P_4)\) la contrainte \(x_1 \geq 2\). justifiez qu'il n'admet aucune solution réalisable. Le problème \((P_5)\) revient à ajouter à \((P_0)\) les contraintes \(x_1 \leq 1\) et \(x_2 \geq 2\). sa relaxation continue a pour solution optimale \((1, \frac{11}{5})\) de valeur \( \frac{182}{5} \). Déduisez en \((P_7)\) et \((P_8)\), donnez leur solution sans calcul, et concluez. 问题 \((P_6)\) 是在 \((P_4)\) 中加入约束 \(x_1 \geq 2\) 得到的，说明它为什么没有可行解。问题 \((P_5)\) 则是在 \((P_0)\) 中加入约束 \(x_1 \leq 1\) 和 \(x_2 \geq 2\) 得到的，它的连续松弛最优解是 \((1, \frac{11}{5})\)，目标值为 \( \frac{182}{5} \)。据此推出 \((P_7)\) 和 \((P_8)\)，不给计算过程直接写出它们的解，并作出结论。
