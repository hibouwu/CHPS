# Simulateur de Particules 1D

Un simulateur de particules simple en C++ pour le projet POO.
Simule le mouvement des particules dans des champs de gaz stationnaires et instationnaires.

## Compilation

```bash
mkdir build
cd build
cmake ..
make
cd ..
```

## Exécution

Lancer la simulation stationnaire :

```bash
./build/Myproject steady
```

(Sortie : Les fichiers `particles_positions`, `particles_velocities`)

Lancer la simulation instationnaire :

```bash
./build/Myproject unsteady
```

(Sortie :  Les fichiers `particles_positions_0.000000`, `particles_velocities_0.000000`, `particles_positions_0.200000`, `particles_velocities_0.200000`, ... , `particles_positions_1.000000`, `particles_velocities_1.000000`)

## Graphiques

Ce script trace les positions et les vitesses des particules au cours du temps (pour la simulation `unsteady`).

```bash
gnuplot scripts/plot.gp
```

## Performance & Bonus

Lancer les benchmarks pour comparer Séquentiel vs Parallèle :

```bash
# Tout lancer (Séquentiel + Thread + Async)
./build/Myproject perf all

# Lancer des modes spécifiques
./build/Myproject perf thread
./build/Myproject perf async
```
