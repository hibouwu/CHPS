# Ébauche de Propositions d'Optimisation (Optimization Drafts)

D'après l'analyse de la base de code, voici une analyse de faisabilité et une ébauche de mise en œuvre pour les principaux axes d'optimisation des performances et d'extension des fonctionnalités.

## Proposition 1 : Accélération par Calcul Hétérogène (GPU/CUDA)

### 1. Analyse de la Situation Actuelle (GPU)

Le projet actuel utilise une classe personnalisée `Matrix` (`src/tensor.cpp`) pour effectuer des opérations matricielles denses sur le CPU, en s'appuyant sur OpenBLAS ou OpenMP. Les données sont stockées dans la mémoire standard (`std::vector<double>`).

### 2. Évaluation de la Faisabilité (GPU)

**Faisabilité** : Moyenne (coût d'intégration élevé)

* **Avantages** : La classe `Matrix` encapsule les données et les opérations sous-jacentes, et l'espace de noms `MathOps` isole la logique opérationnelle des nœuds du graphe de calcul. Cela rend le remplacement du backend de calcul relativement facile, sans avoir à réécrire la logique du graphe de calcul de niveau supérieur.
* **Défis** : Nécessite une chaîne d'outils CUDA, la gestion explicite Host/Device, l'appel à cuBLAS/cuDNN, et une adaptation du système de build.

### 3. Ébauche de Mise en Œuvre (GPU)

1. **Restructuration des Structures de Données** :
    * Étendre la classe `Matrix` en ajoutant un pointeur `double* device_data_` pointant vers la mémoire vidéo du GPU.
    * Implémenter les méthodes `to_device()` et `to_host()` pour le transfert de données entre la mémoire vidéo et la mémoire vive.
2. **Migration des Opérateurs** :
    * **Multiplication Matricielle (GEMM)** : Ajouter une branche `MatmulImpl::Cuda` dans l'implémentation de `matmul` dans `tensor.cpp`, appelant `cublasDgemm` au niveau inférieur.
    * **Opérations Élément par Élément (Element-wise)** : Écrire des noyaux CUDA (fichiers `.cu`) pour l'addition, ReLU, Sigmoid, Tanh, etc.
3. **Optimisation du Flux de Données** :
    * Modifier `Trainer::runEpoch` pour transférer le Batch vers le GPU dès la lecture par le `DataLoader`.
    * S'assurer que les variables intermédiaires des passes Forward/Backward résident majoritairement sur le GPU, et ne rapatrier que les données nécessaires aux métriques.

## Proposition 2 : Parallélisme de Pipeline (Pipeline Parallelism)

### 1. Analyse de la Situation Actuelle (Pipeline)

Actuellement, `Trainer::runEpoch` adopte un mode d'exécution séquentiel :
`Chargement des Données (Load) -> Propagation Avant (Forward) -> Propagation Arrière (Backward) -> Mise à jour des Poids (Update)`
Ce mode entraîne une inactivité des unités de calcul lorsque le calcul CPU ou les E/S prennent du temps.

### 2. Évaluation de la Faisabilité (Pipeline)

**Faisabilité** : Élevée

* Les différentes étapes ont des frontières logiques claires et sont faciles à découpler.
* La principale difficulté réside dans le contrôle de la cohérence des poids (Staleness) et la compétition pour les ressources dans un environnement multithread.

### 3. Ébauche de Mise en Œuvre (Pipeline)

1. **Découplage des Étapes (Decoupling)** :
    * Définir quatre fonctions d'interface principales :
        * `Stage1_Load()` : Retourne `BatchData`
        * `Stage2_Forward(BatchData)` : Retourne `LossNode`
        * `Stage3_Backward(LossNode)` : Calcule les gradients
        * `Stage4_Update()` : Applique les gradients
2. **Stratégies de Parallélisme** :
    * **Stratégie A : Préchargement des Données (Data Prefetching)** (recommandée)
        * Établir une `BlockingQueue<BatchData>`.
        * Lancer un thread indépendant dédié à l'exécution du `Data Loading`, remplissant continuellement la file d'attente.
        * Le thread de calcul principal récupère les données de la file d'attente pour l'entraînement. Cette solution est la plus robuste et permet de masquer efficacement la latence des E/S.
    * **Stratégie B : Pipeline Complet (Full Pipeline)**
        * Utiliser 4 threads pour traiter respectivement les 4 étapes, en transmettant les résultats intermédiaires via des files d'attente.
        * **Attention** : Cette solution introduit des "gradients obsolètes" (Batch N+1 utilisant des poids pas encore mis à jour), ce qui correspond à un SGD asynchrone.

## Proposition 3 : Optimisation des Hyperparamètres (HPO)

### 1. Analyse de la Situation Actuelle (HPO)

`main.cpp` dispose déjà d'une fonctionnalité complète d'analyse des arguments de ligne de commande (structure `Config`), prenant en charge la configuration de paramètres tels que `--learning_rate`, `--hidden_sizes`, `--batch_size`, etc.

### 2. Évaluation de la Faisabilité (HPO)

**Faisabilité : Élevée**
Le projet est très adapté à l'adoption d'une approche "pilotée de l'extérieur" pour le HPO, sans nécessiter de modifications intrusives du code noyau C++.

### 3. Ébauche de Mise en Œuvre (HPO)

1. **Script Pilote Externe** :
    * Écrire un script Python (recommandé d'utiliser le framework `Optuna` ou `Ray Tune`).
2. **Flux de Travail** :
    * Définir l'espace de recherche des hyperparamètres (par ex. plage de LR $10^{-4} \sim 10^{-1}$, taille de Batch 32, 64, 128, etc.).
    * Le script appelle l'exécutable C++ compilé via `subprocess`, en passant une combinaison spécifique de paramètres.
    * Le programme C++ affiche la précision finale sur stdout ou dans un fichier CSV (aligné avec `metrics.csv`).
    * Le script Python analyse le résultat de sortie et le renvoie à l'algorithme d'optimisation pour décider du prochain ensemble de paramètres.

## Proposition 4 : Optimisation du Calcul Haute Performance (High Performance Computing)

Outre les changements architecturaux (GPU/Pipeline), il existe encore un énorme potentiel d'exploration côté CPU.

### 1. Réduction de la Précision (HPC - Float)

* **Analyse** : Actuellement, `tensor.hpp` définit `std::vector<double> data;`, utilisant des nombres à virgule flottante double précision 64 bits partout.
* **Bénéfice** :
  * **Doublement de la bande passante mémoire** : Pour une même bande passante de bus, le volume de transfert des Float (32 bits) est le double de celui des Double.
  * **Doublement du débit SIMD** : Le jeu d'instructions AVX2 peut traiter 4 doubles à la fois, mais peut traiter 8 floats.
  * **Suffisant pour le Deep Learning** : La grande majorité des entraînements de réseaux neuronaux peuvent converger avec seulement du Float32 voire du Float16.
* **Faisabilité** : **Élevée**. Mais un passage en `float` peut affecter la stabilité numérique ; il faut revalider les gradients et ajuster les hyperparamètres si nécessaire.

### 2. Réutilisation de la Mémoire (HPC - In-place)

* **Analyse** : Actuellement, `add` et `mul` dans `math_ops.cpp` créent de nouveaux objets `Matrix` et allouent de la mémoire : `Matrix out(val_a.rows, val_a.cols);`. Pour les réseaux profonds, cela signifie un grand nombre d'opérations malloc/free pour chaque couche à chaque Epoch.
* **Bénéfice** : Réduit la fragmentation de la mémoire et la surcharge de gestion par l'OS (appels système).
* **Mise en Œuvre** :
  * Implémenter un "Pool de Mémoire (Memory Pool)" ou un "Pool d'Objets".
  * Supporter la sémantique `a.add_(b)` (in-place), en veillant à ne pas écraser les valeurs nécessaires au backward.

### 3. Fusion d'Opérateurs (HPC - Fusion)

* **Analyse** : Actuellement, `Linear -> ReLU` sont deux étapes séparées, nécessitant deux lectures/écritures en mémoire.
* **Bénéfice** : Fusionner `MatMul + Bias + ReLU` en une seule boucle Kernel, permettant aux données de circuler directement dans les registres ou le cache L1, réduisant considérablement les accès mémoire.
* **Mise en Œuvre** : Étendre `OperationNode` ou ajouter des opérateurs fusionnés dans `MathOps`.

## Proposition 5 : Optimisation de l'Allocation Mémoire et de l'Initialisation (Memory & Initialization Optimization)

### 1. Analyse de la Situation Actuelle (Memory)

Le profilage a révélé qu'une grande partie du temps est consommée par `std::fill`, la construction de `Matrix` et la copie de données. Les principaux goulots d'étranglement sont :

* **Initialisation Répétée** : Le constructeur de `Matrix` remplit par défaut le `std::vector<double>` avec des zéros, qui est immédiatement écrasé par des données valides (entraînant une double écriture en mémoire dans `mnist_dataset.cpp` et `tensor.cpp`).
* **Copie Redondante** : `DataLoader::nextBatch` crée de nouvelles `Matrix` et copie les données élément par élément à chaque Batch, provoquant des allocations mémoire et des transferts fréquents.
* **Occupation Mémoire Inutile** : Le constructeur de `Node` alloue par défaut une matrice de gradient `grad_` de même taille et la remplit de zéros pour tous les nœuds (y compris les nœuds d'entrée/labels non dérivables).
* **Aléatoire Répété** : Il existe un risque de double initialisation si le constructeur de `LinearLayer` initialise par défaut et qu'un appel explicite suit.

### 2. Évaluation de la Faisabilité (Memory)

**Faisabilité** : Élevée (effet rapide)
Ce type d'optimisation implique principalement un "allègement" au niveau du code C++, sans nécessiter l'introduction de nouveaux frameworks, et peut réduire considérablement la charge CPU lors de l'entraînement.

### 3. Ébauche de Mise en Œuvre (Memory)

1. **Optimisation du Chargement des Données** :
    * **Initialisation sans Surcoût** : Modifier la logique de construction de `Matrix` pour permettre d'allouer la mémoire sans remplissage par défaut de zéros (n'effectuer un `fill` manuel que si nécessaire), évitant la double écriture lors du chargement dans `MNISTDataset`.
    * **Utilisation de Vues (Views)** : Restructurer `DataLoader` pour qu'il retourne une plage d'index ou une vue de référence (`Span` / `MatrixView`) des données, plutôt que de copier physiquement les données.
2. **Allègement du Graphe de Calcul** :
    * **Gradients Optionnels** : Modifier la classe `Node` pour distinguer les nœuds "dérivables" et "non dérivables" (entrées, labels). Pour les nœuds non dérivables, éviter l'allocation et l'initialisation de `grad_`.
3. **Correction de l'Initialisation des Couches** :
    * Vérifier le processus de construction de `LinearLayer` et `MLPNetwork` afin d'éviter une double initialisation (constructeur + appel explicite).
