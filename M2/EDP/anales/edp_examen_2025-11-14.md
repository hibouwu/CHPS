# Contrôle en évaluation de performances — 14 novembre 2025

M2 CHPS · Durée : **2 h 30**

[Index des annales](README.md) · [Version chinoise](edp_examen_2025-11-14_zh.md) · [Photographie, page 1](Images/edp_examen_2025-11-14_p01.png) · [Photographie, page 2](Images/edp_examen_2025-11-14_p02.png)

> Transcription du sujet photographié, sans corrigé. La présentation et les notations ont été harmonisées sans modifier les données ni les questions.

## Consignes

- Les calculatrices, les notes de cours et de TD sont autorisées mais sont strictement personnelles.
- Les ordinateurs et les téléphones sont interdits.

## Exercice 1 — Réseau de files d’attente à quatre ressources

*Questions 1 à 5 : page 1 ; questions 6 à 9 : page 2.*

On considère un système en charge de traiter un flux de tâches arrivant à une fréquence $\lambda$ exprimée en $\mathrm{instr/s}$. Ce système contient quatre ressources numérotées de $R_1$ à $R_4$, avec des taux de service de $\mu_{R_1}$ à $\mu_{R_4}$ respectivement. On sait que :

$$
\mu_{R_1}=400\ \mathrm{instr/s},\qquad
\mu_{R_2}=180\ \mathrm{instr/s},\qquad
\mu_{R_3}=550\ \mathrm{instr/s},\qquad
\mu_{R_4}=125\ \mathrm{instr/s}.
$$

Chacune de ces ressources est associée à une file d’attente.

À l’entrée de ce système, la ressource $R_1$ reçoit les tâches à une fréquence $\lambda$ et les dirige vers les ressources de calcul $R_2$ et $R_3$ à hauteur de 30 % et 70 % respectivement.

À la sortie de la ressource $R_2$, 80 % des instructions sont dirigées vers la ressource $R_4$ et les 20 % qui restent quittent le système. La ressource $R_3$ reçoit également en entrée toutes les instructions issues de la file associée à la ressource $R_4$. Après le passage par la file associée à $R_3$, toutes les instructions quittent le système.

### Questions

1. Donnez le schéma en réseau de files d’attente correspondant au système décrit ci-dessus. Il faut mentionner sur votre schéma l’ensemble des ressources ainsi que la valeur de la fréquence des flux sur toutes les transitions (entrée, sortie, intermédiaires).

2. Quelle condition pose-t-on sur la fréquence d’arrivée externe $\lambda$ pour que le système global soit stable ?

3. Pour le reste des questions, on suppose que $\lambda$ est de $320\ \mathrm{instr/s}$. Le système est-il stable ?

4. Quel est le temps d’attente moyen du système ? Identifiez la ressource qui est majoritairement à l’origine de cette attente.

5. Pour réduire l’attente dans cette ressource identifiée, on propose de la remplacer par une ressource ayant le même mode de fonctionnement mais avec un taux de service doublé.

   (a) Le système reste-t-il stable ?

   (b) Quel est le nouveau temps moyen d’attente au niveau de cette ressource, et celui du système global ?

6. Quel est le temps de service moyen (après changement de la ressource identifiée dans la question précédente) ? Identifiez la ressource qui est majoritairement à l’origine de ce temps.

7. Pour réduire le temps de service de cette ressource identifiée, on la remplace par une autre qui effectue le même service mais trois fois plus vite.

   (a) Quel est le nouveau taux de service de cette nouvelle ressource ?

   (b) Quel est le nouveau temps de service moyen du système global ?

8. Après ces deux remplacements, quel est le temps de réponse moyen du système global ? Quelle est l’accélération obtenue par rapport à la version initiale (avant les deux changements) ?

9. Sachant que les deux changements ont augmenté le coût du système global de 0,75 fois sa valeur initiale, est-ce que vous pensez que cet investissement est efficace ? Justifiez votre réponse.

## Exercice 2 — Gustafson–Barsis

*Page 2 du sujet.*

La métrique de Gustafson–Barsis sert à calculer la capacité d’exécuter un code plus grand dans la même durée d’exécution que le problème initial en utilisant plus de processeurs. Ici, c’est le cas d’un passage du séquentiel (un processeur) à $P$ processeurs ($P>1$) d’un code dont la fraction séquentielle est $seq$. Ce passage s’accompagne d’une accélération de mise à l’échelle (*scaled speedup*), telle que :

$$
Acc(\mathrm{scaled})\leq P+(1-P)\times seq.
$$

> **Note de transcription :** la photographie utilise $P$ dans le paragraphe et $p$ dans la formule. La transcription uniformise cette notation en $P$ et conserve le signe $\leq$ de l’original.

### Questions

1. Quelle est l’accélération selon Gustafson–Barsis (*scaled speedup*) pour une application s’exécutant sur huit processeurs et qui passe 14 % de son temps à exécuter sa partie séquentielle ?

2. Quelle est la fraction séquentielle maximale que l’on puisse tolérer pour garder au moins la même accélération (*scaled speedup*) quand le nombre de processeurs passe à dix ?

## Exercice 3 — Uniformité d’un générateur aléatoire

*Page 2 du sujet.*

On utilise un générateur de nombres aléatoires uniformément distribués entre 0 et 1 pour générer des traces synthétiques et on souhaite vérifier son uniformité à travers l’échantillon ci-dessous, de taille 20, au seuil de risque de 5 %.

```text
0.12, 0.45, 0.67, 0.23, 0.89, 0.34, 0.56, 0.78, 0.01, 0.99,
0.41, 0.62, 0.15, 0.73, 0.27, 0.51, 0.84, 0.39, 0.60, 0.95
```

### Questions

1. Poser les hypothèses à tester.

2. Effectuer la comparaison de la distribution observée à celle théorique en utilisant le test de Kolmogorov–Smirnov au seuil de risque $\alpha=0.05$. Que déduisez-vous ?

3. En découpant l’intervalle $[0,1]$ en cinq classes $[0,0.2[$, $[0.2,0.4[$, $[0.4,0.6[$, $[0.6,0.8[$ et $[0.8,1]$, effectuer la comparaison de la distribution observée à celle théorique en utilisant le test du Khi-deux au seuil de risque $\alpha=0.05$. Que déduisez-vous ?

4. Peut-on confirmer l’uniformité du générateur ? Au seuil de risque de 5 %, justifiez votre réponse.
