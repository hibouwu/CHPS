# Cours 1 — Concepts de base et performance en HPC

Soraya Zertal · Master 2 CHPS · Li-PaRAD / UVSQ

[课程入口](../README.md) · [教师课件 PDF](1_edpCpl.pdf)

保留课件正文顺序，合并连续重复的幻灯片标题；内容订正在相应位置标为“校注”，依据见[审校说明](../审校说明.md)。

## Intervenants

Soraya Zertal, Laboratoire Li-PaRAD, UPSacaly-UVSQ soraya.zertal@uvsq.fr

Sebastien Gougeaud, CEA

sebastien.gougeaud@cea.fr

## Organisation et évaluation

Organisation de l’enseignement : Cours, travaux dirigés, travaux pratiques, analyse d’article scientifique et présentation (soutenance)

### Evaluation :

Contrôle continu : TPs, présentation, évaluation écrite

## Eléments de bibliographie

0. “The art of computer systems Performance Analysis: Techniques for Experimental design, Measurement, Simulation and Modeling”, Raj Jain, Wiley Edition.

- “Handbook of Simulation: Principles, Methodology, Advances, Applications, and Practice”, Jerry Banks, Wiley Edition.
- “Queueing Systems” Leonard Kleinrock, Wiley Edition.

## Présentation générale du module

Introduction à l’Evaluation Des Performances : Motivation, problématique et concepts de base, évaluation de performances et le HPC (S. Zertal)

Méthodes et techniques d’évaluation (S. Zertal)

Workloads (+ S. Gougeaud)

Modélisation mathématique

Simulation

Mesure (+ S. Gougeaud)

## Plan : concepts de base

1. Motivation et problématique

2. Approche à suivre

3. Checklist pour éviter les erreurs

4. Métriques de base à évaluer

5. Caractéristiques d’un bon métrique

6. Evaluer les performances : méthodes à adopter

## Plan : évaluation des performances pour le HPC

1. Objectifs

2. Parallélisme et performance

3. Métriques classiques dans le HPC

4. Modèles et lacunes

5. Evaluation

## Motivation et problématique

But de tout système : fournir le meilleur rapport coût/performance

⇒ Nécessité d’évaluer cette performance à toutes les étapes du cycle de vie d’un système :

1. Conception : prédiction

2. Réalisation : choix matériel ou logiciel

3. Commercialisation : mise en valeur de métriques

4. Utilisation : tuning selon le contexte

5. Maintenance et Mise à jour : contrôle (monitoring)

## Motivations et problématique

Objectifs de l’évaluation de performances :

Mieux connaitre la faisabilité d’un système/application et l’intérêt de son développement/codage.

Détecter et mieux comprendre les limitations d’un système.

Bien cibler les améliorations possibles : ajout de ressources (exp. processeurs), réorganisation des traitements, réorganisation des charges,...etc

## Approche à suivre

Les systèmes à analyser sont multiples, de même pour les métriques, les techniques d’évaluation et les types de charge (workloads) associés.

Néanmoins, l’approche générale d’évaluation suit les étapes suivantes:

Définir le système à analyser et préciser le but à atteindre.

Etablir la liste des services à fournir par le système analysé.

Sélectionner les métriques relatifs à la vitesse, la précision et la disponibilité du système analysé.

Etablir la liste des paramètres affectant les performances du système analysé.

A distinguer les paramètres liés au système de ceux liés aux types de workloads.

Sélectionner les facteurs (parmi les paramètres) variables pendant l’évaluation ainsi que les valeurs qu’ils peuvent prendre.

Sélectionner la méthode d’évaluation appropriée parmi la modélisation mathématique, la simulation ou la mesure.

Sélectionner les charges auxquelles sera soumis le système à évaluer : synthétiques ou réelles.

Concevoir les jeux de tests pouvant fournir le maximum d’informations pour l’étude du comportement du système.

Analyser et interpréter les données collectées à l’issue des tests en utilisant des techniques statistiques.

Présenter les résultats et les communiquer sous une forme claire et compréhensible, souvent sous forme graphique, en utilisant une échelle appropriée.

## Checklist pour éviter les erreurs (R. Jain)

Is the system correctly defined and the goals clearly stated?

Are the goals stated in an unbiased manner?

Have all the steps of the analysis followed systematically?

Is the problem clearly understood before analyzing it?

Are the performance metrics relevant for this problem?

Is the workload correct for this problem?

Is the evaluation technique appropriate?

Is the list of parameters that affect performance complete?

Have all parameters that affect performance been chosen as factors to be varied?

Is the experimental design eficient in terms of time and results?

Is the level of detail proper?

Is the measured data presented with analysis and interpretation?

Is the analysis statistically correct?

Has the sensitivity analysis been done?

Would errors in the input cause an insignificant change in the results?

Have the outliers in the input/output been treated properly?

Have the future changes in the system and workload been modeled?

Has the variance of input been taken into account?

Has the variance of the results been analyzed?

Is the analysis easy to explain?

Is the presentation style suitable for its audience?

Have the results been presented graphically as much as possible?

Are the assumptions and limitations of the analysis clearly documented?

## Introduction aux métriques

Les métriques communs pour l’évaluation des performances :

Temps de réponse

Débit

Accélération

Efficacité

Taux d’utilisation

Fiabilité

Disponibilité

## Temps de réponse

### Définition :

Le temps séparant la requête de l’utilisateur de la réponse du système. Le temps de réponse augmente avec la charge du système sous l’effet de l’augmentation du temps d’attente.

Le facteur d’extension (stretch factor) est le rapport du temps de réponse pour une certaine charge à celui pour une charge minimale.

Le stretch factor quantifie l’impact de l’augmentation de la charge sur l’allongement du temps de réponse.

### Exemple :

Dans un système à temps partagé, le facteur d’extension (strech factor) est le rapport du temps de réponse avec la multiprogrammation à celui sans multiprogrammation.

## Débit

### Définition :

Taux de requêtes exécutées en une unité de temps.

| Système | Unité de débit |
| --- | --- |
| Interactif | requêtes/s |
| CPU | MIPS ou MFLOPS |
| Batch | job/s |
| Réseau | packet-bits/s (pps,bps) |
| Transactionnel | transactions/s (TPS) |

### Remarque :

Le débit augmente avec la charge jusqu’à une certaine valeur maximale, une sorte de borne supérieure (exple: bande passante en réseau).

Débit/capacité nominal est le débit maximal pouvant être délivré par le système soumis à une charge idéale.

### Exemple :

Aprés le start-up, une instruction est exécutée par le pipeline à chaque cycle s’il n y a aucune dépendance pénalisante ou branchement.

Débit/capacité d’usage est le débit maximal pouvant être obtenu tout en respectant la limite imposée au temps de réponse pour le maintenir en dèça d’une certaine valeur acceptable par l’utilisateur.

MIPS: Millions d’instructions par seconde

$$
\mathrm{MIPS} = \frac{\text{nombre d’instructions}}{10 ^{6} \times \text{temps d’exécution}}
$$

MFLOPS : millions d’opérations en virgule flottante par seconde.

> 校注：原课件将浮点运算与浮点指令混用；MFLOPS 统计运算数，一条向量或 FMA 指令可对应多次浮点运算。

Remarques : Pour les deux unités, on considère que les instructions sont en mémoire. De même, toutes les deux (surtout le MIPS) ne constituent pas de bons indicateurs de performances.

## Accélération

### Définition :

Le rapport entre le temps séquentiel et le temps parallèle (amélioré de manière générale)

$$
\mathrm{Acc} = \mathrm{Speedup} = \frac{\mathrm{Tps} \text{sequentiel}}{\mathrm{Tps} \text{parallele}}
$$

Le calcul de l’accélération par La loi d’Amdahl simple:

$$
\mathrm{Acc} = \mathrm{Speedup} = \frac{1}{(1 - F _{a}) + \frac{F _{a}}{P}}
$$

$F _{a}$ : fraction parallélisable (améliorée) du code

$P$ : nombre de processeurs utilisés

## Accélération/coût

L’Accélération n’est pas linéaire en fonction du nombre de processeurs. Il y a des coûts supplémentaires liés à la parallélisation (amélioration) tels que : les échanges de messages, la synchronisation ...etc

Le calcul de l’accélération par la loi d’amdahl enrichie :

$$
\mathrm{Acc} = \frac{1}{(1 - f _{a}) + (\frac{f _{a}}{P}) + C t (f _{a} , P)}
$$

$C t ( f _{a} , P )$ : Coût lié à la parallélisation de la fraction $f _{a}$ du code sur $P$ processeurs.

> 校注：这里的额外耗时须除以原串行运行时间，归一化后才能与分母中的时间比例相加。

## Efficacité

### Définition :

L’Eficacié d’une accélération obtenue par l’utilisation de P processeurs se calcule par:

$$
E = \frac{\mathrm{Acc}}{P}
$$

ou bien :

$$
E = \frac{\mathrm{Tps} \text{sequentiel}}{\mathrm{Tps} \text{parallele} \times P}
$$

Plus l’efficacité est proche de 1, plus l’accélération est optimale.

Une efficacité inférieure à 1 peut provenir de la partie séquentielle, du déséquilibre de charge, des communications, de la synchronisation ou d’autres surcoûts.

> 校注：$1-E$ 不能直接解释为通信／同步所占比例；效率 $E$ 与资源忙碌时间比例 $U$ 也不是同一个量。

## Taux d’utilisation

### Définition :

Fraction du temps pendant laquelle la ressource est utilisée.

### Calcul :

$$
U = \frac{\text{temps d’occupation de la ressource}}{\text{temps total écoulé}}
$$

### Buts :

Maximiser le taux d’utilisation d’une ressource.

Harmoniser au mieux les différentes ressources ⇒ l’équilibrage de charge (Load Balancing).

## Efficacité et taux d’utilisation
L’efficacité compare l’accélération obtenue au nombre de processeurs ; le taux d’utilisation mesure la fraction du temps pendant laquelle une ressource est occupée. Une ressource occupée peut notamment exécuter des communications ou une attente active.

## Passage à l’échelle : strong et weak scaling

### Strong Scaling:

Basée sur le fait que la parallélisation a pour but de réduire le temps d’éxécution: Pour une taille constante d’un problème n, on augmente le nombre de processeurs P et on observe la diminution du temps d’exécution en conséquence.

Une extensibilité forte (Strong Scaling) implique qu’on va p fois plus vite avec Pprocesseurs sur le même code de taille n, l’efficacité tend alors vers 1.

Accélération/coût

Mais la parallélisation peut avoir un autre but que celui de la réduction du temps d’exécution ...

Affiner les modèles, préciser plus les résultats, ....

Accélération/coût

### Weak Scaling:

Une extensibilité faible (Weak Scaling) consiste à faire augmenter la taille du problème n et le nombre de processeurs P ensemble, avec pour but de traiter des problèmes plus gros en maintenant le temps d’execution constant.

### Loi de Gustafson-Barsis :

La meilleure ’accélération obtenue en exécutant un code de taille n sur P processeurs, avec s la fraction de son temps temps d’exécution passé sur le code séquentiel, est :

$$
\mathrm{Acc} (n, P) \leq P + (1 - P) s
$$

Pour le modèle d’Amdahl à taille fixe, avec une fraction séquentielle $s_0$ mesurée sur l’exécution séquentielle :

$$
\mathrm{Acc}(P)=\frac{1}{s_0+(1-s_0)/P}\leq \min(P,1/s_0).
$$

> 校注：Gustafson 模型中的 $s$ 是扩大问题后在并行运行时间中测得的串行比例，不能直接与 Amdahl 中的 $s_0$ 等同；上界 $1/s_0$ 假设 $s_0>0$。

## Fiabilité (Reliability)

### Définition:

L’apptitude d’un système à effectuer ses fonctions, de fournir des résultats non erronés et de maintenir ce fonctionnement en toutes circonstances pendant un temps T.

Data Reliability : le système de stockage -moyennant une redondance intégrale ou partielle- garantit l’accès à des données non erronées.

Network Reliability : le réseau garantit que les messages sont délivrés aux destinataires

La fiabilité se mesure généralement par la probabilité d’arrivée des erreurs.

Néanmoins, il est d’usage de considérer le temps moyen séparant l’arrivée des erreurs, le Mean Time Between Errors (MTBE).

## Disponibilité (Availability)

### Définition :

C’est la période du temps pendant laquelle le système peut servir les requêtes utilisateur.

C’est la période uptime par opposition à celle downtime où le système ne répond plus.

La disponibilité est la fraction du temps pendant laquelle le système peut fournir le service :

$$
A=\frac{\text{uptime}}{\text{uptime}+\text{downtime}}.
$$

> 校注：MTTF、MTBF 是时间量，本身不是可用性比例；可修复系统还要考虑修复时间。

## Caractéristique : linéarité

Le métrique doit indiquer une performance linéairement proportionnelle à la performance actuelle.

Les utilisateurs sont assez sensibles à cette caractéristique mais pas tous les métriques peuvent l’être. Certains métriques sont logarithmiques.

## Caractéristique : fiabilité
Un métrique est considéré fiable, si les valeurs de ce métrique pour les systèmes A et B, indiquent que le système A est plus performant que le système B et le système A est effectivement toujours plus performant que le système B.

Cela parrait évident mais il ne l’est pas toujours.

Exemple : MIPS n’est pas un métrique fiable.

### Exemple de la non fiabilité du MIPS

Le benchmark whetstone est exécuté sur une machine pouvant utiliser un coprocesseur flottant. Une itération de ce benchmark dure 1.08s et génère 1.6 MIPS avec le coprocesseur mais dure 13.6s et génère 2.7 MIPS sans coprocesseur.

L’exécution en utilisant le coprocesseur est alors plus performante (12.6 fois plus rapide) pour un MIPS moindre. Ce dernier ne reflete donc pas cette performance.

## Caractéristique : déterminisme
Un métrique est déterministe SSI il donne la même valeur à chaque fois que le test est effectué.

## Caractéristique : facilité de mesure
Un métrique difficile à mesurer est par conséquent peu utilisé.

De plus, une mesure difficile à effectuer a des chances d’être erronée.

## Méthodes d’évaluation des performances

Trois méthodes pour l’évaluation des performances: la modélisation analytique, la simulation et la mesure.

La sélection de la méthode appropriée repose en premier lieu sur l’étape dans laquelle se trouve le système à analyser au moment de l’analyse.

Aussi, le coût temporel et financier de l’évaluation, les outils disponibles ainsi que le degré de précision des résultats.

Opter pour la mesure si le système existe et est disponible (ou un système s’y approchant puis extrapoler).

Autrement, opter pour la simulation ou la méthode analytique.

La simulation est plus consommatrice en temps mais nécessite moins de simplifications que la modélisation analytique.

En général, on utilise 2 méthodes et on compare leurs résultats pour validation.
