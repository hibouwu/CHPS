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
