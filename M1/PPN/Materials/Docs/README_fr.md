# MLP & Moteur d'Autodifférentiation pour MNIST

[English](../README.md) | **[Français](README_fr.md)** | [中文](README_zh.md) | [العربية](README_ar.md) 

Ce dépôt contient l'implémentation complète d'un réseau de neurones multicouche (MLP) écrit "from scratch" en C++.

Ce projet a été développé dans le cadre de l'Unité d'Enseignement **Projet de Programmation Numérique (PPN)** du Master 1 CHPS (Calcul Haute Performance & Simulation) de l'**Université Paris-Saclay (UVSQ)**.

L'objectif principal est de comprendre les mécanismes internes des frameworks de Deep Learning en implémentant un moteur d'autodifférentiation (mode inverse) et des opérations matricielles optimisées, sans dépendre de bibliothèques tierces telles que PyTorch ou TensorFlow.

## Fonctionnalités

* **Moteur d'Autodifférentiation** : Implémentation d'un graphe de calcul dynamique (DAG) supportant la différenciation automatique en mode inverse.
* **Opérations Tensorielles Optimisées** : Multiplication matricielle optimisée utilisant le "cache blocking", le multithreading OpenMP et l'intégration optionnelle de BLAS.
* **Réseau de Neurones Configurable** : Prise en charge de configurations arbitraires de couches, de fonctions d'activation (ReLU, LeakyReLU, GELU, Sigmoid, Tanh) et de stratégies d'initialisation (He, Xavier).
* **Pipeline d'Entraînement** : Boucle d'apprentissage complète avec SGD / MomentumSGD / AdamW, perte CrossEntropy et traitement par mini-batch.

## Prérequis

Le projet requiert un compilateur compatible C++17 et CMake. **OpenBLAS est requis** pour les opérations matricielles.

* CMake 3.10 ou supérieur
* GCC ou Clang avec support C++17
* **OpenBLAS** (Requis)
* `wget` et `gzip` (pour le téléchargement du dataset)

### Installation des Dépendances

* Fedora / RHEL
  
```bash
sudo dnf install cmake gcc-c++ openblas-devel wget gzip
```

* Ubuntu / Debian
  
```bash
sudo apt install cmake g++ libopenblas-dev wget gzip
```

## Compilation et Utilisation

### 1. Compilation

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
```

### 2. Téléchargement des Données

Un script est fourni pour télécharger le dataset MNIST :

```bash
./scripts/MnistDDataDownload/get_mnist.sh
```

### 3. Exécution

Pour lancer l'entraînement avec la configuration par défaut :

```bash
./build/ppn_train --epochs 20 --learning_rate 0.01 --batch_size 64 --hidden_size 128
```

### Options de la Ligne de Commande

L'application supporte les arguments suivants :

| Option | Défaut | Description |
| -------- | -------- | ------------- |
| `--epochs` | 1 | Nombre d'époques d'entraînement |
| `--learning_rate` | 0.01 | Taux d'apprentissage |
| `--batch_size` | 64 | Taille des mini-lots (batch size) |
| `--hidden_size` | 128 | Taille d'une couche cachée unique |
| `--hidden_sizes` | "" | Tailles pour plusieurs couches cachées (séparées par virgules, ex: "128,64"). Ecrase `--hidden_size` |
| `--data_dir` | "mnist" | Répertoire contenant les fichiers MNIST |
| `--activation` | relu | Fonction d'activation (relu/leaky_relu/gelu/sigmoid/tanh) |
| `--optimizer` | sgd | Optimiseur (sgd/momentum_sgd/momentum/adamw) |
| `--momentum` | 0.9 | Coefficient de momentum (momentum_sgd) |
| `--nesterov` | 0 | Active Nesterov (0/1, momentum_sgd) |
| `--weight_decay` | 0.0 | Weight decay (momentum_sgd/adamw) |
| `--beta1` | 0.9 | AdamW beta1 |
| `--beta2` | 0.999 | AdamW beta2 |
| `--eps` | 1e-8 | AdamW epsilon |
| `--init` | he | Stratégie d'initialisation des poids (he/xavier/manual) |
| `--seed` | 0 | Graine aléatoire (0 = aléatoire) |

## Scripts Utilitaires

Le répertoire `scripts/` contient divers outils pour les benchmarks et les expériences :

* **Benchmarks** :
  * `benchmark_matmul.sh` : Compare la multiplication matricielle naïve vs optimisée.
  * `benchmark_e2e.sh` : Test de performance d'entraînement complet.
* **Expériences** :
  * `exp_learning_rate.sh`, `exp_batch_size.sh`, `exp_hidden_size.sh` : Tests d'hyperparamètres.
  * `exp_init_comparison.sh` : Comparaison des stratégies d'initialisation.
* **Visualisation** :
  * Des scripts Python (ex: `scripts/Utils/plot_metrics.py`) sont utilisés pour générer les courbes de performance.

## Architecture

L'architecture du réseau repose sur un graphe dynamique d'opérations.

```text
Entrée (784) -> Linéaire -> ReLU -> Linéaire -> Softmax -> Sortie (10)
```

[Voir le diagramme d'architecture détaillé (UML)](Images/phase4-6.png)

## Performance

Les tests de performance ont été réalisés sur un processeur **AMD Ryzen**. La version optimisée avec BLAS montre une accélération significative par rapport à l'implémentation naïve.

| Implémentation | Temps d'entraînement (par époque) | Speedup |
| ---------------- | ----------------------------------- | --------- |
| C++ Naïf | ~60s | 1x |
| **Optimisé (BLAS)** | **~0.3s** | **~200x** |

## Documentation

* [**Rapport Technique Complet (PDF)**](../ProjetRapportlatex/rapport.pdf)
* [Spécification des besoins](requirements_fr.md)
* [Conception détaillée](conception_detaillee_fr.md)

## Auteurs

* **Abdennour Boulmis**

**Encadrant** : Aurélien Delval

## Licence

Aucun fichier de licence n'est fourni. Ce projet est destiné à un usage académique et éducatif uniquement.
