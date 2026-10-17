## 0 Périmètre de révision et documents

### 0.1 Séances prévues avant le contrôle

Le calendrier photographié en cours indique un **DST le matin du 22 octobre 2026**. Les séances ci-dessous déterminent l'ordre de révision. Ce calendrier ne précise pas un programme exhaustif du contrôle, sa durée, la forme des questions ou les documents autorisés.

| Date | Matin | Après-midi |
|---|---|---|
| 2026-09-25 | CM1 : architecture GPU et premier code CUDA | TD1 : grille et compréhension du code CUDA |
| 2026-09-29 | CM2 : hiérarchie mémoire et API CUDA | TD2 : approximation de π par Monte Carlo multithread |
| 2026-10-09 | CM3 : Driver API, multi-GPU et OpenMP Target | TP1 : DGEMM |
| 2026-10-22 | DST | TP2 : DGEMM optimisé, accès coalescés et mémoire partagée |
| 2026-11-05 | TP3 : calcul d'occupation GPU, 1D Tiling ; TP noté | Répartition non précisée davantage |

**Parcours principal :** comprendre les notions et le déroulement d'un programme des CM1-CM3, puis refaire les questions Q1-Q9 du TD1, Q1-Q6 du TD2 et Q1-Q12 du TP1 de cette année. La partie OpenMP Target du CM3 est complétée à partir du calendrier et de l'exemple local disponible.

**Entraînement complémentaire :** les anciens exercices sur DGEMM en mémoire partagée, les streams et les fonctions de distance 3D permettent de réutiliser ces méthodes. Les TP consacrés à l'optimisation de DGEMM et au calcul d'occupation sont programmés après le DST ; leurs implémentations détaillées ne sont donc pas la première priorité. Les concepts de mémoire partagée, de coalescence, de warp et d'occupation déjà abordés au CM2 restent à réviser.

Voir la [photo du calendrier](Images/calendrier_cours_2026.jpg). Les chapitres 1-3 regroupent les cours, le chapitre 4 conserve les numéros des exercices, et le chapitre 5 sert à s'entraîner sans consulter les réponses. Les deux langues suivent la même numérotation ; le code, les variables, les formules et les valeurs se correspondent.

### 0.2 Documents utiles et correspondance

| Document | Version et utilisation | Partie du dossier |
|---|---|---|
| [Diapositives CM1](../CM/APM_Cours1_en.pdf) | Version de 96 pages, avec le complément sur les ordonnanceurs Kepler | Chapitre 1 |
| [Cours CM1 en chinois](../CM/APM_Cours1_zh.md) | Explications de séance intégrées ; l'ancienne extraction franco-anglaise correspond à 93 pages | Explications et vérification du chapitre 1 |
| [Diapositives CM2](../CM/APM_Cours2.pdf) et [cours chinois](../CM/APM_Cours2_zh.md) | PDF actuel de 98 pages, numérotation des warps et chronométrage par événements | Chapitre 2 |
| [Diapositives CM3](../CM/APM_Cours3.pdf) et [cours chinois](../CM/APM_Cours3_zh.md) | 101 pages ; certaines descriptions d'API nécessitent une qualification historique | Chapitre 3 |
| [Énoncé TD1](../TD1%20%20APM/td1.pdf) et [réponses existantes](../TD1%20%20APM/td1.md) | 2026-2027, Q1-Q9 | Exercices de l'année, chapitre 4 |
| [Énoncé TD2](../TD2/TD2/SUJET/td2.pdf) et [code CPU](../TD2/TD2/CODE/pi.c) | 2026-2027, Monte Carlo, Q1-Q6 | Exercices de l'année, chapitre 4 |
| [Énoncé TP1](../TP1/SUJET/tp1.pdf), [réponses françaises](../TP1/SUJET/tp1.md), [réponses chinoises](../TP1/SUJET/tp1_zh.md) | 2026-2027, compilation et DGEMM en mémoire globale, Q1-Q12 | Exercices de l'année, chapitre 4 |
| [Exemple OpenMP Target](../cmexos/ompgpuecAdd.c) | Addition vectorielle, map et vérification du lieu d'exécution | OpenMP Target, chapitre 3 |
| [Ancien corrigé TP1](../TDTP2025/TP/tp1_correction.pdf) | En-tête 2024-2025, optimisation avec mémoire partagée | Compléments, chapitre 4 |
| [Ancien sujet TP2](../TDTP2025/TP/tp2_sujet_2025-2026.pdf) et [ancien corrigé](../TDTP2025/TP/tp2_correction.pdf) | Sujet 2025-2026 et corrigé 2024-2025 : documents d'années différentes | Complément streams, chapitre 4 |
| [Ancien sujet TD](../TDTP2025/TD/td2.pdf) | 2025-2026, fonction de distance 3D, différent du TD2 Monte Carlo actuel | Complément SDF, chapitre 4 |

Les diapositives originales, les traductions existantes, les programmes et les archives de mesures restent à leur emplacement. Ce dossier regroupe les diapositives répétées, réorganise les thèmes pour la révision et rapproche chaque question de son explication. Les liens permettent de retrouver la formulation originale, les figures complètes ou les journaux de mesures. Les transcriptions de séance éclairent le contexte ; leurs nombres oraux ne servent pas de spécifications précises.

### 0.3 Utiliser les deux versions

Une première lecture en chinois permet de comprendre le déroulement des calculs et de retrouver les termes français. À la deuxième lecture, partir directement de l'énoncé français, écrire les indices, les formules et les déplacements de données sur papier, puis vérifier la réponse. Le chapitre 5 permet enfin de vérifier que l'on sait expliquer les raisons d'un choix.

Pour rédiger une réponse CUDA, préciser successivement le travail d'un thread, le passage des coordonnées aux indices, l'emplacement des données CPU/GPU, les dépendances entre opérations, puis la vérification du résultat et le périmètre du chronométrage. Lorsqu'un énoncé fixe un stockage matriciel, un nombre de threads ou une caractéristique matérielle, utiliser cette hypothèse. Une valeur donnée pour une génération de GPU ne constitue pas une constante universelle.

Les remarques signalées comme explications ou corrections lèvent une omission, une différence de version ou une erreur manifeste du support. Les nouveaux exemples de code ne sont pas accompagnés d'une affirmation d'exécution GPU dans cette préparation.
