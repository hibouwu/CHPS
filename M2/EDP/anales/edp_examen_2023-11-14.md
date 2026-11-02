# Contrôle en évaluation de performances — 14 novembre 2023

M2 CHPS · S. Zertal · Durée : **2 h**

[Index des annales](README.md) · [Version chinoise](edp_examen_2023-11-14_zh.md) · [Photographie, page 1](Images/edp_examen_2023-11-14_p01.png) · [Photographie, page 2](Images/edp_examen_2023-11-14_p02.png)

> Transcription du sujet photographié, sans corrigé. La présentation et les notations ont été harmonisées sans modifier les données ni les questions.

## Consignes

- Les calculatrices, les notes de cours et de TD sont autorisées mais sont strictement personnelles.
- Les ordinateurs et les téléphones sont interdits.

## Exercice 1 — Unités de calcul et disques

*Page 1 du sujet.*

Soit un système composé de deux unités de calcul : $Cal_G$, en charge du calcul d’ordre général, et $Cal_S$, en charge d’un calcul spécifique, et de deux disques $Disk_1$ et $Disk_2$ servant au stockage des données. Les instructions des codes soumis à ce système passent d’abord par les unités de calcul et se répartissent entre elles selon les proportions de calcul général/spécifique qu’ils contiennent. Les deux unités de calcul ont accès aux données sur les disques.

Pour $Cal_G$, 85 % des instructions exécutées se terminent et quittent le système, et le reste accède à l’espace de stockage, tandis que pour $Cal_S$, 65 % des instructions exécutées se terminent et quittent le système, et le reste accède à l’espace de stockage. Les données sont uniformément distribuées sur l’espace de stockage composé par les deux disques et les accès aux disques finalisent l’exécution des instructions.

Les codes types exécutés sur ce système contiennent en moyenne 80 % de calcul spécifique. $Cal_G$ exécute $1200\ \mathrm{instr/s}$ alors que $Cal_S$ exécute $2500\ \mathrm{instr/s}$. $Disk_1$ a une capacité de 1 TB avec un temps d’accès moyen de 6 ms, alors que $Disk_2$ n’a que 500 GB avec un temps d’accès moyen de 4 ms.

### Questions

1. Donnez un schéma pour le système décrit ci-dessus. Il est impératif de détailler les différents serveurs et files associées ainsi que les connexions entre elles. L’ensemble doit être accompagné de labels précisant les fréquences en entrée, les taux de service et les probabilités de répartition.

2. Quelle est la limite supérieure de la fréquence en entrée supportée par ce système pour assurer sa stabilité ?

3. On considère une fréquence d’arrivée initiale de $1000\ \mathrm{instr/s}$ et on change les serveurs pour lesquels le temps moyen d’attente est supérieur au temps moyen de service. Quels sont les serveurs concernés ? Justifiez votre réponse numériquement, étape par étape.

## Exercice 2 — Benchmarks et performances moyennes

*Page 2 du sujet.*

Le tableau suivant regroupe les temps d’exécution (en secondes) et le nombre d’instructions exécutées de cinq benchmarks du même domaine applicatif, sur trois systèmes différents.

| Benchmark | $Syst_1$ : temps (s) | $Syst_2$ : temps (s) | $Syst_3$ : temps (s) | Nombre d’instructions |
|---|---|---|---|---|
| 1 | 33.4 | 28.8 | 28.3 | $1.45\times10^{10}$ |
| 2 | 19.9 | 22.1 | 25.3 | $7.97\times10^9$ |
| 3 | 6.5 | 5.3 | 4.7 | $3.11\times10^9$ |
| 4 | 84.3 | 75.8 | 80.1 | $3.77\times10^{10}$ |
| 5 | 101.1 | 99.4 | 70.2 | $4.56\times10^{10}$ |

On considère que ces benchmarks ont des poids équivalents.

### Questions

1. Calculez le temps d’exécution moyen et le MIPS moyen par système.

2. Calculez l’accélération moyenne par système avec le système 3 comme référence. Ces valeurs d’accélérations moyennes reflètent-elles les vraies performances ? Justifiez votre réponse.

## Exercice 3 — Placement des données sur disque

*Page 2 du sujet.*

Un module de placement intelligent des données sur disque s’occupe de stocker les données sur les cylindres internes (numéros faibles), puis, selon les disponibilités, vers les cylindres externes (numéros forts). On aimerait savoir si ce module remplit bien sa fonction et on procède à un ensemble de tests (accès) avec vérification du numéro de cylindre accédé.

On a observé les accès aux huit cylindres centraux $[cyl_0,\ldots,cyl_7]$ et on a comptabilisé les accès suivants :

| Numéro de cylindre | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|---|
| Nombre d’accès | 29 | 19 | 18 | 25 | 17 | 10 | 15 | 11 |

### Questions

1. Poser les hypothèses pour tester l’utilité de ce module de placement.

2. Vérifier l’utilité de ce module à 5 % de risque et en utilisant le test de Kolmogorov–Smirnov (voir table jointe). Détailler les différentes étapes.

> **Note de transcription :** la table jointe mentionnée dans la question 2 n’est pas visible sur les photographies fournies.
