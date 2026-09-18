[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/LTvoibQm)

# Lab4 - Échantillonnage de Monte Carlo

Implémentation parallèle de la méthode de Monte Carlo pour estimer π à l'aide d'OpenMP.

## Vue d'ensemble

Ce projet estime π en générant des points aléatoires dans un carré unitaire et en comptant combien d'entre eux tombent dans le disque unité. L'implémentation exploite OpenMP pour paralléliser la charge de travail et améliorer les performances.

## Structure du projet

```
├── src/
│   ├── main.c           # Programme principal avec banc d'essai et mesures
│   ├── compute_pi.c     # Estimation de π par Monte Carlo
│   └── compute_pi.h     # En-tête
├── scripts/
│   └── analyse.py       # Analyse et visualisation
├── build/                # Répertoire de compilation
├── results/              # Sorties et graphiques
├── CMakeLists.txt        # Configuration CMake
└── run_all.sh            # Construction + analyses automatisées
```

## Algorithme

La méthode de Monte Carlo :
1. Générant des points aléatoires (x, y) dans [-1, 1] × [-1, 1]
2. Tester l'appartenance au disque unité (x² + y² ≤ 1)
3. Estimer π par le ratio : π ≈ 4 × (points_dans_cercle / total_points)

L'implémentation parallèle dans [`compute_pi_mc`](src/compute_pi.c) utilise OpenMP et un générateur aléatoires thread-safe (drand48_r).

## Construction du projet

### Prérequis
- CMake 3.15
- GCC avec support OpenMP
- Python 3 avec les paquets requis (pandas, numpy, matplotlib, seaborn, rich, tqdm)

### Compilation
```bash
mkdir build
cd build
cmake ..
make
```

## Utilisation

### Lancement basique
```bash
./piestimator <n> [meta_repets] [fichier_sortie]
```

- `n` : Nombre d'échantillons aléatoires pour l'estimation de Monte Carlo
- `meta_repets` : Nombre de répétitions pour l'analyse statistique (défaut : 1)
- `fichier_sortie` : Chemin du fichier CSV de sortie (défaut : "results.csv")

### Exemples
```bash
# Estimation unique avec 1M d'échantillons
./piestimator 1000000

# Exécutions multiples pour analyse statistique
./piestimator 1000000 100 results.csv

# Test de mise à l'échelle des 4 threads
OMP_NUM_THREADS=4 ./piestimator 1000000
```

### Analyse complète (pipeline)
Exécuter le pipeline d'analyse complet :
```bash
./run_all.sh <run_label>
```

Cela va :
1. Construire le projet
2. Exécuter l'analyse de stabilité (2048 répétitions avec 5M d'échantillons)
3. Exécuter l'analyse de convergence (tailles d'échantillons variables)
4. Générer des graphiques de visualisation
5. Collecter les informations système

- `run_label` : nom de l'exécution. Toutes les sorties sont écrites sous `results/<run_label>/` (CSV, PNG, logs, cpuinfo, ...).

## Analyse des performances

Le script [`analyse.py`](scripts/analyse.py) propose deux analyses :

### Analyse de stabilité
- 2048 répétitions avec 5 000 000 d'échantillons
- distributions des estimations de π et des temps d'exécution
- validation de la correction et de la stabilité du système

### Analyse de convergence  
- tailles d'échantillons de 1 000 à 1 000 000
- l'erreur d'estimation diminue quand n augmente
- le temps d'exécution croît linéairement avec n

## Résultats

### Test de performance des threads

#### Test de speedup (même nombre d'échantillons)
```bash
cd build
OMP_NUM_THREADS=1 ./piestimator 1000000
OMP_NUM_THREADS=2 ./piestimator 1000000
OMP_NUM_THREADS=4 ./piestimator 1000000
OMP_NUM_THREADS=8 ./piestimator 1000000
cd ..
```

| Threads | Échantillons | Temps Moy. (s) | Accélération |
|---------|--------------|-----------------|--------------|
| 1       | 1M           | 0.0103          | 1.0x         |
| 2       | 1M           | 0.0050          | 2.06x        |
| 4       | 1M           | 0.0025          | 4.12x        |
| 8       | 1M           | 0.0014          | 7.36x        |

#### Test de mise à l'échelle (travail proportionnel aux threads)
```bash
cd build
OMP_NUM_THREADS=1 ./piestimator 1000000
OMP_NUM_THREADS=2 ./piestimator 2000000
OMP_NUM_THREADS=4 ./piestimator 4000000
OMP_NUM_THREADS=8 ./piestimator 8000000
cd ..
```

| Threads | Échantillons | Temps Moy. (s) | Efficacité |
|---------|--------------|-----------------|------------|
| 1       | 1M           | 0.0102          | 100%       |
| 2       | 2M           | 0.0102          | 100%       |
| 4       | 4M           | 0.0104          | 98%        |
| 8       | 8M           | 0.0117          | 87%        |

Ces résultats montrent une excellente efficacité et une accélération quasi linéaire.

## Détails d'implémentation

### Sécurité des threads
L'implémentation parallèle utilise :
- `#pragma omp parallel reduction(+:points_inside_circle)` pour l'accumulation sécurisée
- `drand48_r` local aux threads avec des graines uniques par thread
- Planification statique pour l'équilibrage de charge

### Mesure du temps
Le code utilise `clock_gettime(CLOCK_MONOTONIC_RAW, ...)` pour mesurer les durées :
- **Précision** : nanoseconde (résolution réelle dépend du matériel, souvent <100 ns) ;
- **Monotonicité** : garantie — pas affectée par NTP ni ajustements d'horloge ;
- **Utilisation** : mesure du temps écoulé dans `mc_harness()` avant/après chaque exécution.

### Stabilité des timings
- On observe un léger jitter dû au scheduler + pics (scheduler, CPU freq, I/O). Réduire le bruit : fixer `OMP_NUM_THREADS`, CPU governor=performance, augmenter `meta_repets`, épingler threads.

### Accélération OpenMP
- Le calcul est parallélisé via `#pragma omp for` → gain proche de linéaire selon les cœurs. `scripts/analyse.py` ajoute un coût fixe (~5s). Non-linéarités dues à overhead threads, contention mémoire, limites physiques.

### Fonctionnalités de benchmarking
La structure [`BenchResults`](src/main.c) suit :
- Les estimations π individuelles et les mesures de temps
- Les mesures statistiques (moyenne, écart-type)
- Sortie CSV pour l'analyse

### Fonctions clés
- [`compute_pi_mc(int n)`](src/compute_pi.c) : Estimation Monte-Carlo principale
- [`mc_harness()`](src/main.c) : Wrapper de benchmarking avec chronométrage
- [`save_to_csv()`](src/main.c) : Sérialisation des résultats

## Fichiers générés

- `stability.csv` / `stability.png` : distributions et stabilité
- `convergence.csv` / `convergence.png` : précision vs taille d'échantillon
- Infos système : `cpuinfo.txt`, `meminfo.txt`, `timestamp.txt`
