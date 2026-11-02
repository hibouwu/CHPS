# TD4 — Simulation et mesure

S. Zertal · Master 2 CHPS

[Sommaire du module](../README.md) · [Énoncé PDF](td4.pdf) · [Version chinoise](td4_zh.md)

## Exercice 1 — Intervalles de confiance

On souhaite comparer trois systèmes pour l’exécution d’appels de fonctions, plus précisément les opérations `call` et `return`.

Le temps d’exécution de ces opérations, en microsecondes ($\mu\mathrm{s}$), est mesuré cinq fois sur chacun des trois systèmes.

| Mesure / test | Système 1 | Système 2 | Système 3 |
|---|---:|---:|---:|
| 1 | 0.0972 | 0.1382 | 0.7966 |
| 2 | 0.0971 | 0.1432 | 0.5300 |
| 3 | 0.0969 | 0.1382 | 0.5152 |
| 4 | 0.1954 | 0.1730 | 0.6675 |
| 5 | 0.0974 | 0.1383 | 0.5298 |

### Questions

1. Calculez l’intervalle de confiance à un niveau de confiance de **90 %**, puis de **99 %**, pour chacun des trois systèmes.
2. Déduisez-en le système de mesure le plus précis des trois.

### Corrigé

#### 1. Intervalles de confiance de la moyenne

La variance est inconnue et $n=5$. Sous l’hypothèse d’observations indépendantes, de même loi approximativement normale, on utilise l’intervalle de Student à $4$ degrés de liberté :

$$
\bar x=\frac1n\sum_i x_i,\qquad s^2=\frac1{n-1}\sum_i(x_i-\bar x)^2,
$$

$$
IC_{1-\alpha}=\left[\bar x-t_{1-\alpha/2,4}\frac{s}{\sqrt5},\quad
\bar x+t_{1-\alpha/2,4}\frac{s}{\sqrt5}\right].
$$

Le dénominateur de la variance corrigée est **4**, et non 5. Avec seulement cinq observations, la couverture annoncée dépend fortement de l’hypothèse de normalité.

| Système | Moyenne $\bar x$ (μs) | Écart-type corrigé $s$ (μs) | Erreur-type $s/\sqrt5$ (μs) |
|---|---:|---:|---:|
| 1 | 0.116800 | 0.043939 | 0.019650 |
| 2 | 0.146180 | 0.015146 | 0.006774 |
| 3 | 0.607820 | 0.122394 | 0.054736 |

Dans la [table de Student](<../CM + TD EDP/Table-t-Student.jpg>), ligne $\nu=4$ :

- IC bilatéral à 90 % : $\alpha/2=0.05$, donc $t_{0.95,4}\approx2.131847$.
- IC bilatéral à 99 % : $\alpha/2=0.005$, donc $t_{0.995,4}\approx4.604095$.

Par exemple, pour le système 1 à 90 % :

$$
0.1168\pm2.131847\times0.01965017=0.1168\pm0.04189114.
$$

| Système | IC à 90 % (μs) | IC à 99 % (μs) |
|---|---|---|
| 1 | $[0.074909,\ 0.158691]$ | $[0.026329,\ 0.207271]$ |
| 2 | $[0.131740,\ 0.160620]$ | $[0.114993,\ 0.177367]$ |
| 3 | $[0.491131,\ 0.724509]$ | $[0.355809,\ 0.859831]$ |

Augmenter le niveau de confiance élargit l’intervalle.

#### 2. Système le plus précis

**Le système 2** présente le plus petit écart-type, la plus petite erreur-type et les intervalles les plus étroits. Les coefficients de variation $s/\bar x$ valent respectivement $37.62\%$, $10.36\%$ et $20.14\%$ : la comparaison relative donne le même classement.

Il s’agit de la précision des mesures répétées, et non de la vitesse ou de la justesse par rapport à une valeur vraie. Le système 1 a la plus petite moyenne, mais une quatrième mesure élevée ; sans justification externe, on ne la supprime pas.

## Exercice 2 — Test du khi-deux

### Définition et hypothèses

Le test d’adéquation du khi-deux ($\chi^2$) compare des effectifs observés à des effectifs théoriques définis par une hypothèse de distribution.

- $H_0$ : les observations suivent la distribution théorique spécifiée.
- $H_1$ : les observations ne suivent pas cette distribution.

Le test est réalisé au seuil de risque $\alpha$.

### Calcul

Soient $o_i$ l’effectif observé et $c_i$ l’effectif théorique de la classe $i$, avec $1\leq i\leq k$. La statistique de test est :

$$
D=\sum_{i=1}^{k}\frac{(o_i-c_i)^2}{c_i}.
$$

Lorsque les probabilités théoriques sont entièrement spécifiées, que $c_i>0$ et que les effectifs attendus sont suffisants pour l’approximation du khi-deux, on compare $D$ à :

$$
\chi^2_{1-\alpha,\,k-1}.
$$

Si $D$ est supérieur à cette valeur critique, on rejette $H_0$ au seuil $\alpha$. Sinon, on ne rejette pas $H_0$ ; cela ne prouve pas que la distribution théorique est vraie. Le rejet d’une hypothèse d’adéquation ne constitue pas une preuve d’indépendance.

### Application — Uniformité des lancers d’un dé

On souhaite vérifier si les résultats des lancers d’un dé suivent une **loi uniforme sur les six faces**. On effectue 60 lancers et on constitue six classes correspondant aux six valeurs possibles.

Sous l’hypothèse d’équiprobabilité, l’effectif attendu est de 10 pour chaque face.

| Face du dé | Effectif observé | Effectif théorique |
|---|---:|---:|
| 1 | 9 | 10 |
| 2 | 4 | 10 |
| 3 | 18 | 10 |
| 4 | 15 | 10 |
| 5 | 6 | 10 |
| 6 | 8 | 10 |

**Question.** Au seuil de risque $\alpha=5\%$, les observations sont-elles compatibles avec une distribution uniforme ? Qu’en déduisez-vous ?

### Corrigé

En supposant les lancers indépendants, les hypothèses sont :

$$
H_0:p_1=\cdots=p_6=\frac16,\qquad
H_1:\exists i,\ p_i\ne\frac16.
$$

Chaque effectif attendu vaut $60/6=10\geq5$. Aucun paramètre n’est estimé ; le nombre de degrés de liberté est $6-1=5$.

$$
\begin{aligned}
D&=\frac{(9-10)^2+(4-10)^2+(18-10)^2+(15-10)^2+(6-10)^2+(8-10)^2}{10}\\
&=0.1+3.6+6.4+2.5+1.6+0.4=\boxed{14.6}.
\end{aligned}
$$

La [table du χ²](<../CM + TD EDP/tableCHI-DEUX.pdf>), ligne 5 et queue droite $0.05$, donne :

$$
\chi^2_{0.95,5}\approx11.0705<14.6,\qquad p\approx0.01222.
$$

**On rejette l’équiprobabilité au seuil de 5 %.** Les résultats constituent un indice de non-uniformité ; ils ne permettent ni d’en identifier la cause ni de conclure à l’indépendance des lancers.

## Exercice 3 — Test du khi-deux d’un générateur uniforme

On a généré 1000 valeurs à l’aide du générateur suivant, avec $x_0=1$ :

$$
x_n=(125x_{n-1}+1)\bmod 2^{12}.
$$

Pour les représenter dans $[0,1)$, les entiers sont normalisés par $u_n=x_n/2^{12}$. On construit un histogramme à dix classes de largeur $0.1$.

Le tableau de l’énoncé donne les effectifs suivants :

| Classe | Effectif observé | Effectif théorique |
|---|---:|---:|
| 1 | 100 | 100 |
| 2 | 96 | 100 |
| 3 | 98 | 100 |
| 4 | 85 | 100 |
| 5 | 105 | 100 |
| 6 | 93 | 100 |
| 7 | 97 | 100 |
| 8 | 125 | 100 |
| 9 | 107 | 100 |
| 10 | 94 | 100 |
| **Total** | **1000** | **1000** |

**Question.** À partir de ce tableau, vérifiez au seuil de risque $\alpha=10\%$ si les observations sont compatibles avec une distribution uniforme sur $[0,1]$.

### Corrigé

On utilise les effectifs fournis dans le tableau :

$$
H_0:p_1=\cdots=p_{10}=0.1,\qquad
H_1:\exists i,\ p_i\ne0.1.
$$

Chaque effectif attendu vaut $1000\times0.1=100$. Aucun paramètre n’est estimé, donc $\nu=10-1=9$.

$$
\begin{aligned}
D&=\sum_{i=1}^{10}\frac{(o_i-100)^2}{100}\\
&=0+0.16+0.04+2.25+0.25+0.49+0.09+6.25+0.49+0.36\\
&=\boxed{10.38}.
\end{aligned}
$$

La table, ligne 9 et queue droite $0.10$, donne :

$$
\chi^2_{0.90,9}\approx14.6837>10.38,\qquad p\approx0.32061.
$$

**On ne rejette pas l’uniformité au seuil de 10 %.** Cet histogramme est compatible avec dix classes équiprobables.

Cela ne valide pas entièrement le générateur : le test ne porte que sur les fréquences marginales de ces dix classes, pas sur toutes les variations internes aux classes, l’indépendance, la période ou les corrélations multidimensionnelles. La référence du χ² repose sur un modèle d’échantillonnage indépendant ; pour une suite pseudo-aléatoire, ce test reste un diagnostic, et non une garantie d’indépendance.

## Exercice 4 — Test de Kolmogorov–Smirnov

### Définition

Le test de Kolmogorov–Smirnov compare une distribution empirique à une distribution théorique continue spécifiée. Il existe aussi une version permettant de comparer deux échantillons.

### Calcul

Notons $F_o$ la fonction de répartition empirique d’un échantillon de taille $n$, et $F_c$ la fonction de répartition théorique. Avec la normalisation de l’énoncé :

$$
K^+=\sqrt n\,\sup_x\left[F_o(x)-F_c(x)\right],
$$

$$
K^-=\sqrt n\,\sup_x\left[F_c(x)-F_o(x)\right].
$$

- $K^+$ mesure l’écart maximal lorsque la fonction empirique est au-dessus de la fonction théorique.
- $K^-$ mesure l’écart maximal dans le sens inverse.

Pour une loi théorique continue, avec les observations ordonnées $x_{(1)}\leq\cdots\leq x_{(n)}$, cela s’écrit :

$$
K^+=\sqrt n\max_{1\leq i\leq n}\left[\frac{i}{n}-F_c(x_{(i)})\right],
$$

$$
K^-=\sqrt n\max_{1\leq i\leq n}\left[F_c(x_{(i)})-\frac{i-1}{n}\right].
$$

Pour un test bilatéral, on compare $K=\max(K^+,K^-)$ à une valeur critique $K_{1-\alpha,n}$ utilisant la même normalisation. Si $K$ ne dépasse pas le seuil, on ne rejette pas l’hypothèse d’adéquation.

### Application — Durée de vie de cinq appareils

Les durées de vie observées, en heures, sont :

$$
133,\quad169,\quad8,\quad122,\quad58.
$$

On souhaite savoir si ces durées suivent une loi exponentielle de fonction de répartition :

$$
F(x)=1-e^{-\lambda x},\qquad x\geq0,\quad\lambda>0.
$$

### Questions

1. Estimez le paramètre $\lambda$.
2. Posez la ou les hypothèses à tester.
3. Comparez la distribution observée à la distribution théorique à l’aide du test de Kolmogorov–Smirnov, au seuil de risque $\alpha=0.05$. Qu’en déduisez-vous ?

### Conditions d’utilisation du test

Les tables usuelles du test supposent une loi continue entièrement spécifiée avant l’observation des données. Ici, $\lambda$ est estimé sur le même échantillon : une conclusion au niveau annoncé nécessite un étalonnage adapté, par exemple une simulation qui réestime $\lambda$ pour chaque échantillon simulé.

### Corrigé

#### 1. Estimation du paramètre

Le paramètre $\lambda$ est un taux, avec $E[X]=1/\lambda$. Pour des durées indépendantes, de même loi et non censurées :

$$
L(\lambda)=\lambda^5e^{-\lambda\sum_i x_i},\qquad
\frac{d\log L}{d\lambda}=\frac5\lambda-\sum_i x_i.
$$

L’estimateur du maximum de vraisemblance est donc :

$$
\bar x=\frac{133+169+8+122+58}{5}=98\ \mathrm h,\qquad
\boxed{\widehat\lambda=\frac1{98}\approx0.0102041\ \mathrm h^{-1}}.
$$

#### 2. Hypothèses

$$
H_0:X_1,\ldots,X_5\overset{\mathrm{iid}}\sim\mathrm{Exp}(\lambda)
\text{ pour un certain }\lambda>0;\qquad
H_1:\text{la loi des durées n’appartient pas à cette famille}.
$$

L’hypothèse nulle est composite : la valeur estimée $1/98$ ne doit pas être traitée comme un paramètre fixé avant les observations pour calibrer le test.

#### 3. Distance de Kolmogorov–Smirnov

On trie les durées : $8,58,122,133,169$, puis on calcule $\widehat F(x)=1-e^{-x/98}$. Il faut considérer les valeurs de la fonction empirique à droite ($i/5$) et à gauche ($(i-1)/5$) de chaque saut.

| $i$ | $x_{(i)}$ (h) | $\widehat F(x_{(i)})$ | $i/5-\widehat F(x_{(i)})$ | $\widehat F(x_{(i)})-(i-1)/5$ |
|---|---:|---:|---:|---:|
| 1 | 8 | 0.078390 | 0.121610 | 0.078390 |
| 2 | 58 | 0.446690 | −0.046690 | 0.246690 |
| 3 | 122 | 0.712030 | −0.112030 | **0.312030** |
| 4 | 133 | 0.742605 | 0.057395 | 0.142605 |
| 5 | 169 | 0.821736 | **0.178264** | 0.021736 |

$$
D^+=0.178264,\qquad D^-=0.312030,\qquad
\boxed{D=\max(D^+,D^-)=0.312030}.
$$

Avec la normalisation de l’énoncé :

$$
K^+=\sqrt5D^+\approx0.3986,\qquad
K^-=\sqrt5D^-\approx0.6977,\qquad K\approx0.6977.
$$

**Lecture pédagogique de la table.** La [table K–S](<../CM + TD EDP/KolmoSmir_table.png>), ligne $n=5$, colonne $\alpha=0.05$, donne $D_{\mathrm{crit}}=0.56327$. On a $0.312030<0.56327$, ou, de manière équivalente, $K<\sqrt5\times0.56327\approx1.2595$ : la lecture conduit à ne pas rejeter. Toutefois, cette table suppose un paramètre connu à l’avance ; elle ne garantit pas ici un test de niveau 5 %.

**Calibration avec réestimation.** On simule $B=10^6$ échantillons de cinq exponentielles ; dans chaque échantillon, on réestime $\widehat\lambda_b=1/\bar X_b$ avant de recalculer $D_b$. La statistique étant invariante par changement d’échelle, on peut simuler une $\mathrm{Exp}(1)$ : la fonction ajustée aux observations simulées vaut $1-e^{-X_{b,i}/\bar X_b}$.

Le [script de calcul](td4_calculs.py), graine `20261102`, compte 384668 simulations telles que $D_b\geq D_{\mathrm{obs}}$ :

$$
\widehat p=\frac{1+384668}{10^6+1}\approx0.38467,
\qquad\mathrm{SE}_{\mathrm{MC}}\approx0.00049.
$$

Avec cette calibration adaptée à l’hypothèse composite, **on ne rejette toujours pas la famille exponentielle au seuil de 5 %**. Cinq observations ne suffisent pas à démontrer que cette famille est la vraie loi des durées.

## Exercice 5 — Accès aux cylindres d’un disque

Un module de placement intelligent stocke les données d’abord sur les cylindres internes, associés dans l’énoncé aux numéros faibles, puis, selon les disponibilités, sur les cylindres externes, associés aux numéros élevés. On souhaite vérifier si le module remplit sa fonction en observant les numéros des cylindres accédés.

Les accès aux huit cylindres $\mathrm{cyl}_0$ à $\mathrm{cyl}_7$ sont :

| Numéro de cylindre | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Nombre d’accès | 29 | 19 | 18 | 25 | 17 | 10 | 15 | 11 |

### Questions

1. Testez l’utilité du module de placement aux seuils de risque de **5 %**, puis de **1 %**, à l’aide du test de Kolmogorov–Smirnov.
2. Pouvez-vous confirmer vos résultats à l’aide d’un test du khi-deux ?

### Conditions d’utilisation du test

Il faut expliciter la distribution de référence et l’hypothèse traduisant une préférence pour les petits numéros. Les numéros de cylindres sont discrets : les valeurs critiques du test de Kolmogorov–Smirnov pour une loi continue ne s’appliquent pas directement. Un test discret ou une calibration par simulation est nécessaire pour interpréter rigoureusement les seuils demandés.

### Corrigé

#### 1. Référence et distance K–S

L’énoncé ne fournit pas de référence mesurée sans module. On adopte donc le modèle pédagogique suivant : sans préférence, les huit cylindres sont équiprobables, et les accès sont indépendants et de même loi.

- $H_0$ : $P(X=j)=1/8$, $j=0,\ldots,7$.
- Alternative orientée $H_1$ : les accès sont décalés vers les petits numéros, soit $F(j)\geq F_0(j)$ partout, avec au moins une inégalité stricte.

On utilise donc $D^+=\max_j[F_n(j)-F_0(j)]$. On donne aussi la statistique bilatérale pour comparer avec la table fournie.

$$
n=29+19+18+25+17+10+15+11=\boxed{144},\qquad F_0(j)=\frac{j+1}{8}.
$$

**Il y a 8 catégories, mais 144 observations.**

| Cylindre $j$ | Effectif | Effectif cumulé | $F_n(j)$ | $F_0(j)$ | $F_n(j)-F_0(j)$ |
|---|---:|---:|---:|---:|---:|
| 0 | 29 | 29 | 0.201389 | 0.125 | 0.076389 |
| 1 | 19 | 48 | 0.333333 | 0.250 | 0.083333 |
| 2 | 18 | 66 | 0.458333 | 0.375 | 0.083333 |
| 3 | 25 | 91 | 0.631944 | 0.500 | **0.131944** |
| 4 | 17 | 108 | 0.750000 | 0.625 | 0.125000 |
| 5 | 10 | 118 | 0.819444 | 0.750 | 0.069444 |
| 6 | 15 | 133 | 0.923611 | 0.875 | 0.048611 |
| 7 | 11 | 144 | 1.000000 | 1.000 | 0.000000 |

Les sauts des deux fonctions sont aux mêmes points : il suffit de comparer leurs valeurs aux frontières des catégories. Les formules sur observations triées destinées à une référence continue ne doivent pas être appliquées mécaniquement à ces ex æquo.

$$
D^+=\frac{19}{144}\approx0.131944,\qquad D^-=0,\qquad D=D^+,
\qquad\boxed{K=\sqrt{144}D=\frac{19}{12}\approx1.58333}.
$$

L’écart maximal se situe après le cylindre 3 : les quatre premiers cylindres concentrent $91/144\approx63.19\%$ des accès, contre 50 % sous $H_0$.

#### 2. Lecture pédagogique de la table continue bilatérale

En appliquant directement la ligne $n>50$ de la table fournie :

| Risque | $D_{\mathrm{crit}}$ continu | $K_{\mathrm{crit}}$ continu | Conclusion de cette approximation |
|---|---:|---:|---|
| 5 % | $1.35810/12=0.113175$ | 1.35810 | Rejet de l’uniformité |
| 1 % | $1.62762/12=0.135635$ | 1.62762 | Non-rejet de l’uniformité |

Cette lecture est une **approximation continue bilatérale**, et non une calibration discrète ni un test unilatéral adapté à l’alternative orientée. Ce n’est pas le résultat rigoureux du test pour ces données.

#### 3. Test discret exact

Sous $H_0$, les effectifs suivent une loi $\mathrm{Multinomial}(144;1/8,\ldots,1/8)$. Si $S_j$ compte les accès aux $j$ premiers cylindres, $j=1,\ldots,8$ :

$$
nD^+=\max_j(S_j-18j).
$$

Le seuil observé est 19. La probabilité de queue, égalité incluse, vaut :

$$
\boxed{p_+=P_{H_0}\!\left(\max_j(S_j-18j)\geq19\right)
\approx0.00223836}.
$$

Même en version discrète bilatérale :

$$
p_{\mathrm{bilat}}=P_{H_0}\!\left(\max_j|S_j-18j|\geq19\right)
\approx0.00447673.
$$

Ces probabilités sont obtenues par programmation dynamique entière dans le [script de calcul](td4_calculs.py), puis converties en décimales ; il ne s’agit pas d’une estimation Monte-Carlo. Pour l’événement complémentaire, on impose $S_j\leq18j+18$ ; en bilatéral, on impose aussi $S_j\geq18j-18$. On compte les affectations respectant ces frontières cumulées, puis on divise par les $8^{144}$ affectations possibles.

Avec la calibration discrète correcte, **on rejette donc l’uniformité à 5 % et à 1 %**. L’écart observé est dans le sens attendu d’une préférence pour les petits numéros. Sous les hypothèses de référence uniforme et d’accès indépendants, cela étaye l’utilité attendue du module ; ces seuls effectifs ne prouvent pas que le module est la cause du décalage.

#### 4. Vérification par le χ²

L’alternative du χ² est une non-uniformité quelconque, sans direction privilégiée. Chaque effectif attendu vaut $144/8=18$, et $\nu=8-1=7$ :

$$
\begin{aligned}
D_{\chi^2}
&=\frac{(29-18)^2+(19-18)^2+(18-18)^2+(25-18)^2}{18}\\
&\quad+\frac{(17-18)^2+(10-18)^2+(15-18)^2+(11-18)^2}{18}\\
&=\frac{121+1+0+49+1+64+9+49}{18}
=\boxed{\frac{49}{3}\approx16.3333}.
\end{aligned}
$$

$$
\chi^2_{0.95,7}\approx14.0671,\qquad
\chi^2_{0.99,7}\approx18.4753,\qquad p\approx0.02224.
$$

- **À 5 % :** $16.3333>14.0671$ ; rejet, comme avec K–S.
- **À 1 % :** $16.3333<18.4753$ ; non-rejet. Le χ² ne confirme donc pas le rejet du test K–S discret exact à ce niveau.

Il n’y a pas de contradiction : K–S exploite l’ordre des cylindres et les écarts cumulés, tandis que le χ² utilise les écarts quadratiques par catégorie et reste inchangé lorsqu’on permute leur ordre. Leur puissance diffère pour un décalage ordonné. Si l’on se limite à l’approximation continue bilatérale de cours, les deux méthodes donnent « rejet à 5 %, non-rejet à 1 % » ; cet accord ne rend pas la table continue applicable au cas discret.

## Résultats récapitulatifs

| Exercice | Résultat principal | Conclusion |
|---|---|---|
| 1 | $t_{0.95,4}=2.131847$ ; $t_{0.995,4}=4.604095$ | Système 2 : intervalles les plus étroits, meilleure précision |
| 2 | $\chi^2=14.6$, $\nu=5$, $p\approx0.01222$ | Rejet de l’uniformité à 5 % |
| 3 | $\chi^2=10.38$, $\nu=9$, $p\approx0.32061$ | Non-rejet de l’histogramme uniforme à 10 % |
| 4 | $\widehat\lambda=1/98$, $D=0.312030$, calibration avec réestimation : $p\approx0.38467$ | Non-rejet de la famille exponentielle à 5 % |
| 5 | $D^+=19/144$, $p$ unilatéral discret exact $\approx0.00223836$ | K–S discret : rejet à 5 % et 1 % ; χ² : rejet à 5 % seulement |

Reproduction : `python TD/td4_calculs.py` ; dépendances : NumPy et SciPy.
