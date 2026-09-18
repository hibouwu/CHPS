# Conception Détaillée — CNN LeNet-5 (version minimale)

## Architecture Logicielle

Le projet étend le moteur MLP existant avec un réseau **LeNet-5** pour MNIST, en ajoutant le minimum de nouveaux composants :

```text
┌─────────────────────────────────────────────────────────┐
│                    main.cpp (CLI)                       │
│                  --model mlp | cnn                      │
├─────────────────────────────────────────────────────────┤
│     Trainer  ←──── NeuralNetwork (interface)            │
│                     ├── MLPNetwork (existant)            │
│                     └── LeNetNetwork (nouveau)           │
├──────────────────┬──────────────────────────────────────┤
│  Loss + Optimizer│  Conv2D + MaxPool2D + LinearLayer    │
├──────────────────┴──────────────────────────────────────┤
│              Node + MathOps (Autodiff, inchangé)        │
├─────────────────────────────────────────────────────────┤
│                  Matrix (inchangé)                      │
└─────────────────────────────────────────────────────────┘
```

## Diagramme de Classes UML

![CNN LeNet-5 — Diagramme de classes](Images/CD_CNN.png)

## Architecture LeNet-5 pour MNIST

| #  | Couche                     | Entrée           | Sortie           | Paramètres |
|----|----------------------------|------------------|------------------|------------|
| 1  | Conv2D (5×5, s=1, p=2)     | (N, 1, 28, 28)   | (N, 6, 28, 28)   | 156        |
| 2  | ReLU                       | (N, 6, 28, 28)   | (N, 6, 28, 28)   | 0          |
| 3  | MaxPool2D (2×2, s=2)       | (N, 6, 28, 28)   | (N, 6, 14, 14)   | 0          |
| 4  | Conv2D (5×5, s=1, p=0)     | (N, 6, 14, 14)   | (N, 16, 10, 10)  | 2 416      |
| 5  | ReLU                       | (N, 16, 10, 10)  | (N, 16, 10, 10)  | 0          |
| 6  | MaxPool2D (2×2, s=2)       | (N, 16, 10, 10)  | (N, 16, 5, 5)    | 0          |
| 7  | Flatten (inline)           | (N, 16, 5, 5)    | (N, 400)          | 0          |
| 8  | Fully Connected layer 400→120 + ReLU | (N, 400) | (N, 120) | 48 120     |
| 9  | Fully Connected layer 120→84 + ReLU  | (N, 120) | (N, 84)  | 10 164     |
| 10 | Fully Connected layer 84→10 (logits) | (N, 84)  | (N, 10)  | 850        |

**Total : ~61 706 paramètres entraînables**

### Flux de données (Forward Pass)

```text
                        MNIST 28×28 (1 canal)
                        Matrix(N, 784) en entrée
                              │
                    ┌─────────▼──────────────────┐
                    │  Conv2D 5×5, 6 ch (p=2)     │  28×28 → 28×28
                    │  + ReLU                     │
                    └─────────┬──────────────────┘
                    ┌─────────▼──────────────────┐
                    │  MaxPool 2×2                │  28×28 → 14×14
                    └─────────┬──────────────────┘
                    ┌─────────▼──────────────────┐
                    │  Conv2D 5×5, 16 ch (p=0)    │  14×14 → 10×10
                    │  + ReLU                     │
                    └─────────┬──────────────────┘
                    ┌─────────▼──────────────────┐
                    │  MaxPool 2×2                │  10×10 → 5×5
                    └─────────┬──────────────────┘
                    ┌─────────▼──────────────────┐
                    │  Flatten layer              │  (N,16,5,5) → (N,400)
                    └─────────┬──────────────────┘
                    ┌─────────▼──────────────────┐
                    │  Fully Connected layer      │
                    │  400→120 + ReLU             │
                    └─────────┬──────────────────┘
                    ┌─────────▼──────────────────┐
                    │  Fully Connected layer      │
                    │  120→84 + ReLU              │
                    └─────────┬──────────────────┘
                    ┌─────────▼──────────────────┐
                    │  Fully Connected layer      │
                    │  84→10 (logits)             │
                    └─────────┬──────────────────┘
                              │
                        CrossEntropyLoss
```

## Composants Nouveaux

### 1. NeuralNetwork — Interface minimale

Interface avec seulement 2 méthodes virtuelles pures :

```cpp
class NeuralNetwork {
public:
    virtual ~NeuralNetwork() = default;
    virtual Node::Ptr forward(const Node::Ptr& input) const = 0;
    virtual std::vector<Node::Ptr> getParameters() const = 0;
};
```

`MLPNetwork` et `LeNetNetwork` héritent de cette interface. C'est le seul changement structurel sur le code existant.

### 2. Conv2DLayer — Couche de convolution

Utilise la technique **im2col** pour réduire la convolution à un `matmul` :

- **Pas de Tensor4D** : la forme `(N, C, H, W)` est passée en paramètres de `forward()`
- Les données restent dans un `Matrix(N, C*H*W)` standard
- `im2col` est une méthode privée, réutilise `MathOps::matmul` et `MathOps::add`

```text
im2col:    (N, C_in, H, W) → Matrix(N*H_out*W_out, C_in*kH*kW)
kernels:   Matrix(C_out, C_in*kH*kW)

out = im2col(input) @ kernels^T + bias
```

### 3. MaxPool2DLayer — Sous-échantillonnage

- Sélectionne le maximum dans chaque fenêtre `(pool_h, pool_w)`
- Mémorise les positions des maxima pour le backward
- Aucun paramètre entraînable

### 4. LeNetNetwork — Réseau complet

Structure **fixe** (pas de vecteur de couches dynamique) :

```cpp
class LeNetNetwork : public NeuralNetwork {
    Conv2DLayer conv1_{1, 6, 5, 5, 1, 2};    // (1→6, 5×5, p=2)
    Conv2DLayer conv2_{6, 16, 5, 5, 1, 0};   // (6→16, 5×5, p=0)
    MaxPool2DLayer pool_{2, 2, 2};            // 2×2, stride=2
    LinearLayer fc1_{400, 120};
    LinearLayer fc2_{120, 84};
    LinearLayer fc3_{84, 10};
    ReLU relu_;
};
```

Le `Flatten` est un simple reshape inline dans `forward()` — pas besoin de classe.

## Intégration avec le Système Existant

### Composants inchangés

| Composant           | Rôle                                 |
|---------------------|--------------------------------------|
| `Node`              | Graphe de calcul et rétropropagation |
| `MathOps`           | Opérations `matmul`, `add`, `relu`   |
| `Matrix`            | Stockage et calcul matriciel         |
| `LinearLayer`       | Couches FC réutilisées par LeNet     |
| `ReLU`              | Activation réutilisée                |
| `CrossEntropyLoss`  | Fonction de perte                    |
| `SGDOptimizer`      | Mise à jour des paramètres           |
| `DataLoader`        | Chargement par mini-batchs           |
| `MNISTDataset`      | Lecture des données MNIST            |

### Modifications minimales sur l'existant

| Fichier        | Modification                          | Lignes |
|----------------|---------------------------------------|--------|
| `network.hpp`  | Ajouter `: public NeuralNetwork`      | 3      |
| `trainer.hpp`  | `MLPNetwork&` → `NeuralNetwork&`      | 2      |
| `trainer.cpp`  | Mise à jour du type                   | 0      |
| `main.cpp`     | Ajout `--model cnn` + construction    | ~15    |

**Total modifications : ~20 lignes sur les fichiers existants.**

## Représentation 4D sans Tensor4D

Au lieu d'introduire une classe `Tensor4D`, les données 4D sont stockées dans une `Matrix(N, C*H*W)` standard avec un accès indexé :

```cpp
// Accès logique (n, c, h, w) dans Matrix(N, C*H*W)
size_t idx = c * H * W + h * W + w;
double val = matrix(n, idx);
```

L'information de forme `(N, C, H, W)` est propagée comme paramètres entre couches. `LeNetNetwork::forward()` gère cette propagation en interne.

## Choix de Conception

| Aspect                  | Choix                         | Justification                              |
|-------------------------|-------------------------------|--------------------------------------------|
| Représentation 4D       | `Matrix` + paramètres forme   | Aucune nouvelle classe de données          |
| Interface réseau        | `NeuralNetwork` (2 méthodes)  | Minimum pour supporter MLP et CNN          |
| Structure réseau        | Membres fixes, pas de vector  | LeNet-5 est fixe, évite la complexité      |
| Convolution             | im2col + `MathOps::matmul`    | Réutilise BLAS existant                    |
| Flatten                 | Inline dans `forward()`       | Pas de classe supplémentaire               |
| Données d'entrée        | `(N, 784)` inchangé           | CNN reshape en interne                     |

## Hiérarchie des Fichiers

```text
include/
├── neural_network.hpp    [NEW]   Interface (15 lignes)
├── conv2d_layer.hpp      [NEW]   Conv2DLayer
├── maxpool2d_layer.hpp   [NEW]   MaxPool2DLayer
├── lenet_network.hpp     [NEW]   LeNetNetwork
├── network.hpp           [MOD]   + héritage NeuralNetwork
└── trainer.hpp           [MOD]   MLPNetwork& → NeuralNetwork&

src/
├── conv2d_layer.cpp      [NEW]
├── maxpool2d_layer.cpp   [NEW]
├── lenet_network.cpp     [NEW]
└── main.cpp              [MOD]   + --model cnn
```
