# Cours 4–5 — Simulation et mesure

Soraya Zertal · Master 2 CHPS · Li-PaRAD / UVSQ

[课程入口](../README.md) · [教师课件 PDF](45_edp.pdf)

保留课件正文顺序，合并连续重复的幻灯片标题；内容订正在相应位置标为“校注”，依据见[审校说明](../审校说明.md)。

## Simulation

### But

L’opportunité d’observer le comportement d’un système

quelconque, même inexistant au moment de l’évaluation,

dans n’importe quelles conditions (configurations), représentant des contextes d’applications divers.

### Intérêts

Pas besoin de construire un système réel.

Réalisation de tests contrôlables et répétitifs.

Pas de limites pour les scénarios de tests.

Possiblitié de reproduire les résultats par les autres utilisateurs.

### Exemples d’utilisation

La simulation permet d’apporter des réponses aux questions telles que:

Quel algorithme de placement est meilleur pour telle application sur une architecture donnée ?

Quelle stratégie de cache est meilleure pour telle application ?

Quelles sont les propriétées en termes d’equité et de débit associées à certaines stratégies de gestion de ressources partagées ?

### Simulation Vs. Mesure

La mesure.... oui pour la précision et la représentativité du système réel mais....

Quelle est la part réelle des disfonctionements/surcharge du système dans les résultats ?

Les expériences et donc leurs résultats sont limités à la plateforme analysée.

Les extrapolations sont possibles mais très peu convaincantes.

Les résultats sont difficilement reproductibles par d’autres utilisateurs.

## Simulation : Définition et classification

### Définition

Tentative de prédire différents aspects du comportement d’un système quelconque en créant une imitation.

### Classification

Il existe différents types de simulation :

Emulation

Simulation statique

Simulation à événements discrets

## Emulation et simulation statique

### Emulation

Imitation du comportement physique d’un système par un logiciel s’exécutant sur un autre, de manière à ce qu’il apparait comme le système imité.

Remarque : l’émulation produit des résultats assez précis mais génère une surcharge (overhead) importante en contre partie.

### Simulation statique

Appelée surtout méthode Monte Carlo, est une simulation indépendante du temps et peut être arrêtée selon un budget de calcul ou un critère de précision. Elle ne suppose pas nécessairement d’atteindre un équilibre dynamique. Voir plus loin dans ce cours.

## Simulation à événements discrets

### La simulation à événements discrets

Une représentation d’un système par des événements, des transitions qui leurs sont associées et des fonctions spécifiques à exécuter à chaque fois qu’un de ces événement survient et qu’on effectue la transition associée. C’est donc une imitation du schéma fonctionnel, avec un changement d’état selon le temps et les évènements externes ou générés par la simulation.

### Simulation distribuée

Liée plutôt à la manière la simulation est exécutée : distribuée, exploitant les ressources de différents sites, collaborant et comuniquant tout en respectant le schéma Workflow établi et les principes de causalité.

## Simulation : Exemples

### Simulation d’un CPU

Trois simulations possibles avec un niveau d’abstraction décroissant :

Simulation mathématique : Flux macroscopique des tâches et composants (pipe) avec une simulation mathématique à gros grain.

Simulation à événements discrets : Simulation au niveau cycle (niveau microscopique) au profit de la précision.

Emulation : Virtualisation via un autre CPU, càd construction d’une machine virtuelle.

### Simulation d’un réseau de communication

Trois simulations possibles avec un niveau d’abstraction décroissant :

Simulation mathématique : Flux macroscopique des tâches et composants du réseaux (pipe) avec une simulation mathématique à gros grain.

Simulation à événements discrets : Simulation au niveau du paquet et suivi microscopique à travers les différents composants du réseau.

Emulation : de l’actuel flux à travers un réseau.

## Simulation à événements discrets

### Terminologie

Variables d’état définissant l’état du système et dont les valeurs sauvegardées permettent à une simulation arrêtée, de redémarrer ultérieurement (taille de la file d’attente, avancement dans la consommation des tâches,...).

Evénement Un changement dans l’état du système (arrivée ou fin d’un job, panne d’un composant,...)

Temps continu Vs temps discret indiquant si l’état du système est défini tout le temps ou pas.

Etat continu Vs état discret indiquant si les variables du système sont continues (temps) ou discrets (nombre d’occurrence, taille).

### Structure

Un simulateur à événements discrets doit comporter les modules suivants:

1. un ordonnanceur d’événements

2. une horloge globale et une méthode pour la mise à jour du temps

3. des procédures de traitement des événements

4. des mécanismes de génération d’événements

5. des procédures d’enregistrement/filtrage des données

### L’ordonnanceur des événements

L’ordonnanceur constitue le coeur du simulateur à événements discrets et a pour fonction de:

Maintenir la liste des événements (non traités) dans un ordre temporel global.

Procéder au traitement de l’évènement approprié de la liste par sa suppression de celle-ci et de le véhiculer à la procédure de traitement qui lui est associée.

Insérer les nouveaux événements en respectant l’ordre temporel de la liste, ainsi qu’assurer les autres tâches de l’ordonnancement ou de la suppression d’événements.

Assurer la coordination avec l’horloge globale.

### L’horloge globale

La référence temporelle de la simulation, mise à jour par l’ordonnanceur selon deux approches:

#### 1 Incrémentation par pas fixe

L’incrémentation se fait par l’ordonnanceur avec un pas fixe, qui ensuite vérifie les événements de la liste et lance ceux prêts. A la fin des exécutions, l’ordonnanceur re-incrémente l’horloge.

#### 2 Incrémentation événementielle

L’horloge change de manière non-uniforme et prend la valeur de la date de l’événement en tête de liste. C’est l’approche la plus utilisée.

### Traitement des événements

Chaque type d’événement est associé à une procédure de traitement qui simule le comportement du système lorsque ledit événement se produit.

Chaque procédure de traitement peut changer l’état du système et générer d’autres événements, qui se rajouteront à la liste tenue par l’ordonnanceur.

Le traitement implémenté dépend de la nature du système simulé.

### Génération des événements

Les générateurs d’événements se classifient par rapport à la technique de génération utilisée. Deux classes principales se distinguent:

1. Classe orientée trace : séquence d’évènements observés sur un système réel. Représentativité mais très grande Taille, point unique de validation et introduction de biais par la collecte.

2. Classe orientée loi de probabilité : Similaire dans la forme mais générée par le simulateur selon des lois de probabilité (au début ou accompagnant la simulation).

### Enregistrement des données

Maintenir les variables d’états à savoir les compteurs d’événements et les variables de mesure du temps pour effectuer des statistiques et résumer les résultats.

### Structures

Listes ordonnées ou doublement chaînées

Arbres

Se sont les structures les plus utilisées, pour accélérer les opérations (insertion, interrogation, modification) même si les accès en mémoire ne sont pas uniformes.

### Validation

La validation détermine le degré de précision du modèle fonctionnel en répondant aux questions:

Le modèle capture-il les fonctionnalités essentielles du système ?

Les suppositions sont-elles raisonnables ?

Les données en entrée sont-elles représentatives des cas réels ?

Les résultats obtenus sont-ils raisonnables ?

Ces résultats sont-ils explicables ?

### Remarques ...

...concernant la construction du simulateur :

Suivre de bonnes pratiques : programmation structurée, design modulaire, documentation, vérification d’erreurs, ...etc

Exécution étape par étape pour vérifier le passage par TOUS les états du système simulé

Vérification de la cohérence et la stabilité du simulateur

Mettre l’accent sur la vérification des cas spéciaux (corner conditions)

## Simulateurs populaires

### Simulateur de Microprocesseur

Multitude de simulateurs standards au niveau cycle : http://pages.cs.wisc.edu/ arch/www/tools.html

### SimGrid

Outils pour pour les environnements distribuées et hétérogènes (réseau de stations aux grilles de calcul), développé par l’inria. http://simgrid.gforge.inria.fr/

### Simulateur de système de stockage

Le pionnier, developpé/maintenu au Parallel Data Lab (CMU). http://www.pdl.cmu.edu/DiskSim/

Le nôtre : OGSSim. Li-PaRAD,UVSQ / CEA-DAM https://github.com/liparad-storage/ogssim

## Monte Carlo

### Historique

N. Metropolis et S. Ulam [1947-1949], utilisant un procédé aléatoire pour le calcul d’une valeur numérique. Faisant donc allusion aux jeux de hasard pratiqués à Monte Carlo.

### Définition

Méthode pour l’évaluation itérative d’un modèle déterministe en utilisant des ensembles de variables aléatoires en entrée.

Un modèle déterministe donne les mêmes résultats autant de fois qu’il est recalculé dans les mêmes conditions, avec les mêmes entrées.

### Applications

Le domaine d’applications de la méthode Monte Carlo englobe : le calcul des intégrales multidimensionnelles (surface, volume), l’évaluation du risque financier, de la rentabilité ou la solvabilité dans le secteur bancaire et d’assurance, l’étude de la dynamique des molécule ou des mouvements des populations, ...etc

### Remarque

La méthode Monte Carlo nécessite un très grand nombre d’évaluations, tâche facilitée par le calcul parallèle

### Monte Carlo en étapes :

Les différentes étapes suivies pour effectuer une simulation Monte Carlo sont :

1. Créer un modèle pour les paramètres $\left( X _{1} , X _{2} , . . . , X _{k} \right)$

2. Générer un ensemble de valeurs aléatoires $( X _{i 1} , X _{i 2} , . . . , X _{i k} )$

3. Evaluer le modèle et ranger le résultat dans $Y _{i}$

4. Répéter les étapes 2 et 3 pour i = 1..n n très grand pour utiliser la loi des grands nombres.

5. Analyser les résultats en utilisant des histogrammes, moyennes et variances, intervales de confiance...etc

## Monte Carlo : Exemple

### Calcul de π

Déterminer π en calculant la surface d’un cercle de $\mathsf{r a y o n} = 1$

1. Le modèle : $S u r f ( c e r c l e ) = \pi R ^{2} = \pi$ car $\mathsf{R} {=} 1$ La surface du cercle incluse dans le carré $= \textstyle{\frac{\pi} {4}}$ C’est l’ensemble de points $X _{i} \left( x _{i 1} , x _{i 2} \right)$ dans cet espace.

2. Générer un couple $\left( {{x} _{i 1}} , {{x} _{i 2}} \right)$ , deux v.a. uniformément distribuées sur [0..1], représentant un point sur le carré.

3. Evaluer le modèle : incrémenter le nombre de points NB du carré ET du cercle ssi: $\sqrt{\left( x _{i 1} ^{2} + x _{i 2} ^{2} \right)} < 1$

4. Refaire 2 et 3, N (très grand) fois. $\frac{\pi} {4}$ estimé par $\frac{N B} {N}$

## Mesure : Introduction

### Quoi mesurer?

Le nombre d’occurrence d’événements, la durée entre deux événements, la taille pour contenir une information, ...

### Définition

La mesure sert à suivre le fonctionnement du système par :

1. L’observation et la collecte : effectuer des prises de mesure et rassembler les informations qui en découlent.

2. L’analyse : traiter les données collectées avec des techniques statistiques

3. La présentation : afficher les résultats sous les diverses formes appropriées.

## Mesure : terminologie

### Quelques termes usuels

Evénement : tout changement de l’état du système (ex. arrivée d’une requête/un paquet, un accès mémoire ...etc)

Trace : liste ou journal d’événements

Surcharge : (overhead) mesure indiquant une consommation additionnelle du système

Résolution : niveau de détail de l’observation

Taille en entrée : nombre de bits pour coder l’évènement

Portabilité : quantité de modiffications à effectuer afin d’implémenter l’outil de mesure.

## Phase d’observation/collecte

### Méchanismes d’observation

#### 1 ”Espionnage implicite” (Implicit spying):

Observer le système sans interférer avec son fonctionnement. Pas d’impact sur sa performance mais utilisation de filtres pour garder l’information utile.

#### 2 Instrumentation explicite :

Incorporer des traceurs, des sondes en utilisant des compteurs matériels par exemple.

### Classes d’observation/collecte

On-line : résultats analysés pendant le monitoring.

batch : données collectées mais l’analyse est reportée.

### Stratégies de collecte

Event-driven : l’information est enregistrée à chaque apparition d’un événement

Trace : il y a l’enregistrement de l’état du système en plus. Donc surcharge en temps et en espace.

Echantillonnage L’enregistrement de l’information se fait de manière périodique, donc réajustement de la surcharge.

Mesure indirecte Utilisable lorsque le métrique à mesurer ne peut l’être directement. Déterminer un autre métrique mesurable et en déduire/dériver le métrique d’intérêt.

## Outils simples de collecte

### Exemples :

En plus de matériels de mesure et logiciels spécifiques, il y a des outils simples, MAIS efficaces, utilisés souvent pour la mesure.

`time`, `gettimeofday` (représentation du temps en microsecondes), `top`, `gprof`, etc.

> 校注：时间表示单位不等于实测分辨率；工具开销和时钟特性也需检查。

## Phase d’analyse

But de toute évaluation, dépend du contexte et des métriques. Plus importante pour la mesure à cause de la grande taille des données collectées, de la richesse du détail et du bruit.

### ANalysis Of Variance (ANOVA)

Lors des mesures sur un système, les données collectées présentent des écarts, pouvant être importants, liés juste aux réitérations des mesures ou présentant des réelles erreurs de mesure.

L’ANOVA décompose la variabilité en effet des alternatives et variation résiduelle ; le résidu ne se réduit pas nécessairement à une erreur de l’instrument.

### ANOVA - Calcul

On considère un échantillon de n mesures collectées pour chacune des k exécutions (alternatives) et l’ensemble compose les $y _{i j}$ pour la ième mesure de la jème exécution.

Calcul de la moyenne :

Par exécution : $\bar{y} _{j} = \frac{\sum_{i = 1} ^{n} y _{i j}} {n}$

Générale : $\bar{y} = \frac{\sum_{j = 1} ^{k} \sum_{i = 1} ^{n} y _{i j}} {k \times n}$

La mesure se réecrit $y _{i j} = \bar{y} _{j} + e _{i j}$ avec $e_{ij}$ l’erreur de mesure.

La moyenne des mesures par alternative se réecrit : $\bar{y} _{j} = \bar{y} + \alpha_{j}$ avec $\alpha_{j}$ l’effet d’execution et $\sum_{j = 1} ^{k} \alpha_{j} = 0$

### ANOVA - Application

La variation liée aux exécutions par la Sum of the Squares of Alternatives (SSA)

$$
\mathrm{SSA} = n \sum_{j = 1} ^{k} (\bar{y} _{j} - \bar{y}) ^{2}
$$

La variation liée aux erreurs de mesures par la Sum of Squares of Errors (SSE)

$$
\mathrm{SSE} = \sum_{j = 1} ^{k} \sum_{i = 1} ^{n} (y _{i j} - \bar{y} _{j}) ^{2}
$$

### ANOVA et F-test

Dans l’ANOVA à un facteur, l’hypothèse nulle est l’égalité des moyennes des $k$ alternatives. Les observations de chaque alternative sont supposées indépendantes, avec des erreurs normales de même variance dans le modèle classique.

$$
S_a^2=\frac{\mathrm{SSA}}{k-1},\qquad
S_c^2=\frac{\mathrm{SSE}}{k(n-1)},\qquad
F_{\mathrm{calculé}}=\frac{S_a^2}{S_c^2}.
$$

On rejette l’égalité des moyennes au niveau $\alpha$ si :

$$
F_{\mathrm{calculé}}>F_{1-\alpha;\,k-1,\,k(n-1)}.
$$

> 校注：原课件第 34 页将临界值与计算值的不等号方向写反。这里检验的是各组均值相等，使用组间与组内均方之比；并非把“两个方差相等”当作本节研究目标。不拒绝原假设也不等于证明均值相同。

## Phase de présentation

### Paramètres du choix de la présentation

Choix lié au système mais trois paramètres à considérer :

1. La fréquence de la présentation (on-line)

2. La résentation hiérarchique

3. Les points importants: seuils, événement anormal ...etc

### Outils simples, populaires et représentatifs

Un ensemble de techniques statistiques simples : moyenne(s), variance et écart type, quantiles ....etc (voir cours Workloads) avec les intervalles de confiance.

## Qualité de mesure

### Définition

Les erreurs ou bruit dans les mesures, doivent être quantifiés afin de déterminer la qualité de ces mesures par :

1. Justesse (Accuracy) : indique le rapprochement de la valeur mesurée de la valeur standard.

2. Précision : est relative aux mesures répétées (mêmes outils et conditions), souvent représentée par son inverse (l’imprécision).

3. Résolution est le plus petit changement détectable et “affichable”.

### Sources d’erreurs

Instruments de mesure, temps partagé entre utilisateurs, événements temps-réel (exp. interruptions avec les interfaces réseaux), synchronisation des horloges, événements non déterministes (cache misses, les exceptions système, les défauts de pages...etc)

### Quantification

1. Justesse : difficile à quantifier

2. Précision : la dispersion des mesures répétées et l’incertitude sur leur moyenne se quantifient statistiquement. La résolution correspond au plus petit changement discernable par l’instrument ; elle ne se déduit pas simplement de l’intervalle de confiance de la moyenne.

### Intervalles de confiance pour la moyenne : grands échantillons

Pour des observations indépendantes avec variance finie, lorsque l’approximation normale de la moyenne est adéquate :

$$
[c_1,c_2]=\left[\bar X-z_{1-\alpha/2}\frac{s}{\sqrt n},\quad
\bar X+z_{1-\alpha/2}\frac{s}{\sqrt n}\right].
$$

$\alpha$ est le niveau de signification ; le niveau de confiance vaut $1-\alpha$. Par exemple, une confiance de 95 % correspond à $\alpha=0.05$.

> 校注：原课件第 38 页将显著性水平 $\alpha$ 写为 0.9 或 0.95，混淆了 $\alpha$ 与 $1-\alpha$。$n\ge30$ 只是经验提示，并非保证任意分布或相关样本都可套用正态近似。

### Intervalles de confiance pour la moyenne : échantillons réduits

Pour des observations indépendantes d’une population normale de variance inconnue :

$$
[c_1,c_2]=\left[\bar X-t_{1-\alpha/2;n-1}\frac{s}{\sqrt n},\quad
\bar X+t_{1-\alpha/2;n-1}\frac{s}{\sqrt n}\right].
$$

La loi de Student a $n-1$ degrés de liberté. Cette formule n’est pas limitée à $n<30$ ; pour les grands échantillons, ses quantiles se rapprochent des quantiles normaux.

## Quantification des erreurs

### Exemple : huit mesures d’écriture

| Numéro de mesure | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Temps $X_i$ (s) | 8.0 | 7.0 | 5.0 | 9.0 | 9.5 | 11.3 | 5.2 | 8.5 |

$$
\bar X=7.9375\ \mathrm{s},\qquad
s=\sqrt{\frac{\sum_{i=1}^{8}(X_i-\bar X)^2}{7}}\approx2.14472\ \mathrm{s}.
$$

Pour $1-\alpha=90\%$, $t_{0.95;7}\approx1.89458$, donc :

$$
[c_1,c_2]\approx[6.50089,\ 9.37411]\ \mathrm{s}.
$$

> 校注：原稿代入时出现 7.95，与数据均值 7.9375 不一致，现按原始 8 个观测值重算。90% 描述重复构造区间的覆盖率，不是已有区间内“均值的概率”。

### Nombre de mesures à prévoir

Pour une demi-largeur absolue cible $\delta$, une approximation de planification est :

$$
n\ge\left(\frac{z_{1-\alpha/2}s_0}{\delta}\right)^2.
$$

Si $\delta=e_{\mathrm{rel}}|\bar X_0|$, alors :

$$
n\ge\left(\frac{z_{1-\alpha/2}s_0}{e_{\mathrm{rel}}|\bar X_0|}\right)^2.
$$

Ici $s_0$ et $\bar X_0$ proviennent d’un échantillon pilote ; $e_{\mathrm{rel}}$ est une demi-largeur relative, et non la largeur absolue $c_2-c_1$. Arrondir $n$ à l’entier supérieur.

### Exemple : précision relative de 3.5 %

Avec les valeurs pilotes arrondies du cours, $s_0=2.14\ \mathrm{s}$, $\bar X_0=7.94\ \mathrm{s}$, $e_{\mathrm{rel}}=0.035$ et $z_{0.95}\approx1.64485$ :

$$
n\ge\left(\frac{1.64485\times2.14}{0.035\times7.94}\right)^2
\approx160.44,\qquad n=161.
$$

> 校注：教师 PDF 第 41–42 页同时混用了区间全宽／半宽和正态／Student 临界值。原稿写出的 $(2.14\times1.895/(0.07\times7.94))^2$ 实际约为 53.24，而不是 212.95。若采用半宽 0.035 并固定使用先导样本的 $t_{0.95;7}\approx1.895$，才得到约 212.95，即 213 次。161 是采用正态临界值的初步规划值；使用估计标准差时仍需检查假设并可迭代采用新的 Student 临界值，不能承诺固定样本数必然达到目标精度。

## Conception d’un scénario de mesure

### But

Minimiser le nombre d’expériences en maximisant l’information collectée.

Isoler l’effet de chaque facteur en entrée

Déterminer les effets dûs aux intéractions entre les facteurs

Quantifier la part de l’erreur dans les résultats

### Plan d’expérience : définition

La répartition entre les expériences du nombre de facteurs et du nombre de niveaux (valeurs possibles) des facteurs.

### Plan d’expérience : classification

1. Plan simple : d’une configuration initiale, on varie un facteur (optimisation locale). Pas d’analyse d’intéractions.

2. Plan factoriel complet : considérer toutes les configurations (combinaisons). Impraticable car nombre Très grand.

3. Plan fractionnaire : un sous ensemble des combinaisons. Réalisable, mais comment choisir les combinaisons ?

### Plan d’expérience : Exemple

4. facteurs {A,B,C,D} avec 3 niveaux/facteur

Le plan factoriel complet donne 81 combinaisons.

Le tableau suivant est un plan orthogonal à 9 essais pour 4 facteurs à 3 niveaux, de type $L_9(3^4)$.

> 校注：原稿将下表称为“星形设计”。逐对检查因子列，每对的 9 种水平组合各出现一次，符合该正交表的结构；它不能用 9 次试验独立估计全部交互作用。

| Expérience | Fact1 | Fact2 | Fact3 | Fact4 |
| --- | --- | --- | --- | --- |
| 1 | A1 | B1 | C1 | D1 |
| 2 | A1 | B2 | C2 | D2 |
| 3 | A1 | B3 | C3 | D3 |
| 4 | A2 | B1 | C2 | D3 |
| 5 | A2 | B2 | C3 | D1 |
| 6 | A2 | B3 | C1 | D2 |
| 7 | A3 | B1 | C3 | D2 |
| 8 | A3 | B2 | C1 | D3 |
| 9 | A3 | B3 | C2 | D1 |
