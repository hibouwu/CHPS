# TP Poisson 1D - Équation de la Chaleur

Ce dépôt contient l'implémentation en C de résolveurs numériques pour l'équation de la chaleur 1D stationnaire par différences finies. Le projet inclut des méthodes directes et itératives, ainsi que des supports pour les formats de matrices creuses CSR/CSC.

## Fonctionnalités

* **Méthodes Directes** :
  * `dgbtrf` + `dgbtrs` (LAPACK General Band)
  * `dgbtrftridiag` (Factorisation LU optimisée pour tridiagonale)
  * `dgbsv` (LAPACK Driver)
* **Méthodes Itératives** :
  * Richardson (avec $\alpha_{opt}$)
  * Jacobi
  * Gauss-Seidel
* **Formats Creux (Sparse)** :
  * CSR (Compressed Sparse Row)
  * CSC (Compressed Sparse Column)
  * Adaptation de Richardson pour CSR/CSC

## Environnement & Compilation (Docker)

L'environnement de développement recommandé est Docker, assurant la disponibilité des librairies BLAS/LAPACK.

### 1. Construire l'image

```bash
docker build -f docker/Dockerfile -t tp-cn:latest .
```

### 2. Démarrer le conteneur

```bash
# Monter le répertoire courant dans /workspace
docker run --rm -it -v "$(pwd)":/workspace -w /workspace tp-cn:latest bash
```

### 3. Compiler le projet

Dans le conteneur :

```bash
make
```

Cela générera les exécutables dans le dossier `bin/`.

## Exécution et Benchmarks

### Méthodes Directes

Pour lancer un benchmark complet (temps d'exécution vs taille de matrice) :

```bash
./scripts/benchmark_direct.sh
```

Cela générera `benchmark_results.txt`.

Pour visualiser les résultats (nécessite Python sur l'hôte ou dans le conteneur) :

```bash
python3 scripts/plot_benchmark.py
```

Cela générera `benchmark_plot.png`.

### Méthodes Itératives

Pour lancer les solveurs itératifs et analyser la convergence :

**Exemple manuel :**

```bash
# Gauss-Seidel sur N=100
./bin/tpPoisson1D_iter 2 100
# Le fichier RESVEC.dat contiendra l'historique du résidu
```

Paramètres de `tpPoisson1D_iter` : `0=Richardson (GB)`, `1=Jacobi (GB)`, `2=Gauss-Seidel (GB)`, `3=Richardson (CSR)`, `4=Richardson (CSC)`.

**Comparaison de convergence :**
Vous pouvez utiliser les scripts pour générer les données de convergence et tracer les courbes :

```bash
# Générer les données (ex: N=100)
./bin/tpPoisson1D_iter 0 100 && mv RESVEC.dat RESVEC_RICH.dat
./bin/tpPoisson1D_iter 1 100 && mv RESVEC.dat RESVEC_JAC.dat
./bin/tpPoisson1D_iter 2 100 && mv RESVEC.dat RESVEC_GS.dat

# Tracer la comparaison
python3 scripts/plot_convergence.py RESVEC_RICH.dat Richardson RESVEC_JAC.dat Jacobi RESVEC_GS.dat Gauss-Seidel
```

Cela générera `convergence_comparison.png`.

## Structure du Projet

* `src/` : Code source C (`tp_poisson1D_direct.c`, `tp_poisson1D_iter.c`, bibliothèque `lib_poisson1D.c`).
* `include/` : Fichiers d'en-tête.
* `scripts/` : Scripts Shell et Python pour les benchmarks et graphiques.
* `RapportBuild/` : Fichiers sources LaTeX du rapport.
