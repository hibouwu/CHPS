## 1. Architectures et premiers programmes CUDA

Ce chapitre rassemble les notions du CM1 nécessaires pour expliquer un accélérateur, lire une architecture NVIDIA et écrire un premier kernel. La référence principale est le [CM1 de 96 pages](../CM/APM_Cours1_en.pdf). Les chiffres d'architecture ci-dessous sont les exemples du cours, pas une fiche des GPU actuellement disponibles.

### 1.1. Pourquoi utiliser un accélérateur ?

Un **accélérateur** est une ressource de calcul conçue pour une classe de travaux particulière. Il peut être séparé du processeur principal ou intégré avec lui. Son intérêt vient du compromis matériel choisi : consacrer davantage de ressources au calcul adapté à son domaine, au prix d'une moindre généralité.

Le CPU convient à la conduite générale du programme, au contrôle complexe et aux tâches peu parallèles. Un GPU recherche surtout un débit élevé en faisant progresser de nombreux threads. Une boucle contenant beaucoup d'opérations indépendantes sur des tableaux est donc un bon point de départ pour comprendre le calcul GPU.

Cela ne suffit pas à garantir une accélération. Pour un appel isolé avec des transferts explicites, on peut décomposer le temps ainsi :

$$
T_{GPU}=T_{init}+T_{H\to D}+T_{kernel}+T_{D\to H}.
$$

Ici, le temps d'initialisation regroupe les préparations retenues dans la mesure, par exemple les allocations. Cette égalité est un modèle pédagogique sans recouvrement entre les phases. Elle montre pourquoi un kernel rapide peut donner un programme complet lent. Réutiliser des données déjà présentes sur le GPU peut éviter des transferts répétés.

**Question type.** Une boucle est parallélisable : faut-il nécessairement l'envoyer au GPU ? **Réponse.** Il faut aussi considérer la taille du travail, le coût des transferts, les dépendances, la régularité des accès et le temps total de l'application.

### 1.2. Familles d'accélérateurs et interconnexions

| Ressource | Idée essentielle | Point à retenir |
| --- | --- | --- |
| CPU | Traitement général et contrôle du programme | Le programme hôte organise le travail |
| GPU | Nombreux threads et calcul sur des données régulières | Exposer assez de parallélisme et organiser les accès mémoire |
| MIC / Xeon Phi | De nombreux cœurs x86, avec multithreading et cohérence des caches | Exemple historique d'une autre approche du calcul fortement parallèle |
| Cell | Un processeur maître et des unités spécialisées SPE | Exemple historique de répartition explicite du travail |
| FPGA | Logique reconfigurable | La structure matérielle peut être adaptée à un traitement ; le CM1 le cite sans détailler sa programmation |

Le cours oppose deux tendances de connexion. Une carte raccordée au bus système, par exemple PCIe, est relativement facile à intégrer mais les communications ont un coût. Une intégration plus étroite avec le processeur permet des liens et des partages de ressources adaptés, au prix d'une intégration plus complexe.

**Ne pas confondre proximité et coût nul.** Un CPU et un GPU proches physiquement peuvent encore accéder à des régions mémoire différentes. Une interface cohérente ne supprime ni les effets de localisation des données ni le besoin d'attendre la fin d'un calcul avant d'en utiliser les résultats.

### 1.3. Du GPU au thread : les niveaux à distinguer

Un GPU NVIDIA contient plusieurs **SM** (*Streaming Multiprocessors*). Un SM possède des unités de calcul, des ordonnanceurs et des ressources mémoire. Les threads d'un bloc exécutent leur travail sur un même SM dans le modèle de base étudié ici ; un SM peut accueillir plusieurs blocs si ses ressources le permettent.

Un **thread** est une instance logique du kernel. Un **cœur CUDA** est une unité matérielle de calcul. Il n'existe donc pas une correspondance permanente « un thread = un cœur ». Le nombre de threads lancés peut largement dépasser le nombre d'unités de calcul, et les blocs peuvent être exécutés en plusieurs vagues.

Un **warp** regroupe 32 threads d'un même bloc. Pour un bloc multidimensionnel, les threads sont regroupés selon leur numéro local linéaire, avec `x` variant le plus vite. Le modèle **SIMT** présente des threads distincts au programmeur, tout en exécutant leurs instructions par groupes.

Si des threads d'un même warp suivent des branches différentes, les chemins concernés peuvent devoir progresser séparément avec des ensembles de threads actifs différents. Il faut donc distinguer la correction d'un `if` de son coût : `if (i < N)` reste nécessaire pour protéger les accès aux limites.

**À éviter :** affirmer que le GPU ne peut pas exécuter de branchement, que tous les threads de la grille travaillent simultanément, ou que les threads d'un warp peuvent communiquer sans respecter les règles de synchronisation.

### 1.4. Kepler : lire l'exemple du cours

Les pages 35-39 présentent un exemple Kepler : 15 SMX, avec 192 unités FP32, 64 unités FP64, 32 SFU et 32 unités de chargement/stockage par SMX. Ces nombres décrivent la figure du cours et ne sont pas des constantes du modèle CUDA.

Le point ajouté dans la version de 96 pages concerne l'ordonnancement :

- 4 ordonnanceurs de warps par SMX ;
- 8 unités de dispatch, soit 2 par ordonnanceur ;
- chaque ordonnanceur choisit un warp ;
- deux instructions indépendantes de ce warp **peuvent** être dispatchées dans un cycle si les conditions le permettent.

![Ordonnanceur de warps Kepler](../CM/Images/cours1_2026_kepler_warp_scheduler.png)

*Figure 1. Extrait de la page 38 : un ordonnanceur et ses deux unités de dispatch. Une paire d'instructions peut provenir du même warp ; les couleurs distinguent les warps sélectionnés au fil du temps.*

« Deux instructions possibles » ne signifie pas « deux instructions toujours exécutées ». Une dépendance entre instructions ou une ressource indisponible peut empêcher ce débit. Le nombre d'ordonnanceurs ne donne pas non plus le nombre maximal de warps résidents.

La hiérarchie mémoire distingue les caches, gérés par le matériel, et la mémoire partagée, explicitement utilisée par le programme. Même lorsqu'ils partagent des ressources physiques, L1 et mémoire partagée n'ont pas la même fonction logicielle. Une lecture de mémoire globale ne cherche pas automatiquement ses données dans une variable `__shared__`.

### 1.5. Volta, Ampere, Hopper et intégration CPU-GPU

Les schémas suivants du CM1 illustrent une organisation hiérarchique : **GPC → TPC → SM**. On peut calculer un nombre de SM à partir d'un schéma, à condition de préciser que l'on décrit ce schéma.

| Figure du cours | Calcul des SM représentés | Idée à apprendre |
| --- | --- | --- |
| Volta, page 40 | `6 × 7 × 2 = 84` | Plusieurs niveaux de regroupement et apparition des Tensor Cores dans la présentation |
| Ampere, pages 42-43 | `8 × 8 × 2 = 128` | Un SM comporte plusieurs sous-ensembles de traitement |
| Hopper, pages 44-45 | `8 × 9 × 2 = 144` | Des unités distinctes réalisent différents types d'opérations |

Ces valeurs ne donnent pas automatiquement le nombre de SM actifs d'une carte commercialisée. De même, les performances maximales affichées page 46 dépendent du type d'opération et de la précision. On ne peut pas additionner des pics FP32, FP64 et Tensor Core pour obtenir la performance d'un programme.

La page 46 compare aussi les formats : FP32 possède 8 bits d'exposant et 23 bits de fraction ; TF32 conserve 8 bits d'exposant avec 10 bits de fraction ; FP16 utilise 5 bits d'exposant et 10 bits de fraction. Il faut distinguer l'étendue des valeurs représentables de leur précision. Les valeurs en bits ici n'incluent pas le bit de signe.

Pour Grace-Hopper, retenir surtout l'association d'un CPU et d'un GPU par une interconnexion cohérente. Le support chinois contient une mise au point : proximité dans un assemblage, même puce de silicium et partage d'une même région mémoire sont des notions différentes. La localisation mémoire et les effets NUMA restent pertinents ; ne pas apprendre littéralement la formule « même die » de la page 47.

### 1.6. Choisir un modèle de programmation

| Approche | Exemples du CM1 | Travail exprimé par le programmeur |
| --- | --- | --- |
| Programmation explicite du GPU | CUDA, HIP | Kernels, organisation des threads et gestion des données |
| Interface portable de bas niveau | OpenCL | Calcul et ressources selon une interface commune |
| Directives | OpenMP Target, OpenACC | Régions à déporter, boucles parallèles et transferts |
| Abstractions de plus haut niveau | Kokkos, RAJA, SYCL | Calcul exprimé via une bibliothèque ou une abstraction et traduit vers une cible |

Avec CUDA, le programmeur écrit le travail d'un thread puis choisit la grille et les blocs. Avec une approche à directives, il annote des régions ou des boucles ; le compilateur prend en charge une partie de leur mise en œuvre sur la cible. Le CM3 développe OpenMP Target séparément.

**Trois objectifs distincts :** compiler sur une nouvelle machine, obtenir un résultat correct et y atteindre de bonnes performances. Une interface portable aide au premier objectif ; elle ne garantit pas à elle seule les deux autres. Les dépendances entre itérations et les déplacements de données doivent rester compris.

### 1.7. Le rôle du host et du device

Le **host** est la partie exécutée sur le CPU. Le **device** est l'accélérateur. Dans les premiers exemples du cours, le host prépare les entrées, alloue la mémoire du device, transfère les données, lance le kernel puis récupère les résultats.

| Étape | Ressource / opération | Pourquoi ? |
| --- | --- | --- |
| 1 | Tableaux hôtes initialisés | Fournir les entrées et recevoir la sortie |
| 2 | `cudaMalloc` | Créer les tableaux dans la mémoire du device |
| 3 | `cudaMemcpyHostToDevice` | Transférer les entrées nécessaires au calcul |
| 4 | `kernel<<<grid, block>>>(...)` | Demander l'exécution du kernel |
| 5 | Attente appropriée puis copie vers le host | Ne lire qu'un résultat terminé |
| 6 | `cudaFree` puis libération côté host | Fermer le cycle de vie des ressources |

Un pointeur `d_a` est une variable du programme hôte contenant l'adresse d'une allocation du device dans cet exemple. Copier la valeur du pointeur n'est pas copier les éléments du tableau. Un paramètre scalaire, comme `N`, est transmis avec les arguments du kernel ; un tableau nécessite que ses éléments soient accessibles au device.

Dans `c[i] = a[i] + b[i]`, l'ancienne valeur de `c[i]` n'est pas lue : il faut allouer `d_c`, mais il est inutile de copier le tableau `c` vers le GPU avant le calcul. Cette conclusion changerait pour `c[i] += a[i]`.

### 1.8. Grille, blocs et coordonnées

La grille contient des blocs, et chaque bloc contient des threads. Les dimensions `x`, `y`, `z` sont une organisation logique choisie au lancement ; elles ne représentent pas une direction physique imposée dans le GPU.

| Nom | Signification | Exemple |
| --- | --- | --- |
| `gridDim` | Nombre de blocs selon chaque dimension | `(3, 2, 1)` |
| `blockIdx` | Coordonnées du bloc courant | `(1, 0, 0)` |
| `blockDim` | Nombre de threads du bloc selon chaque dimension | `(4, 3, 1)` |
| `threadIdx` | Coordonnées du thread dans son bloc | `(1, 2, 0)` |

Les coordonnées commencent à zéro. Ainsi, `0 <= threadIdx.x < blockDim.x`. Le programme hôte utilise couramment `dim3` pour construire les dimensions de lancement ; les composantes non indiquées à sa construction valent 1.

```cpp
dim3 grid(3, 2);
dim3 block(4, 3);
my_kernel<<<grid, block>>>(/* arguments */);
```

Ce lancement crée `3 × 2 = 6` blocs, `4 × 3 = 12` threads par bloc et `6 × 12 = 72` threads au total. Il ne promet pas que les 72 threads exécutent la même instruction au même instant.

### 1.9. Une dimension : couvrir exactement le domaine utile

Avec une grille et des blocs à une dimension, le numéro global usuel est :

$$
i=\texttt{blockIdx.x}\times\texttt{blockDim.x}+\texttt{threadIdx.x}.
$$

Pour un tableau de `N` éléments et `B` threads par bloc, on lance suffisamment de blocs pour couvrir le tableau :

$$
G=\left\lceil\frac{N}{B}\right\rceil,
\qquad G=(N+B-1)/B\quad(N>0,\ B>0).
$$

La seconde expression utilise une division entière. Exemple : `N = 1000`, `B = 256`, donc `G = 4`. Le lancement crée 1024 threads ; 1000 traitent une valeur, et les 24 derniers ne doivent pas accéder au tableau. Le test est **`i < N`**, pas `i <= N`. Pour `N = 0`, on évite le lancement dans l'exemple donné plus bas.

Le contrôle des bornes empêche un accès en trop ; il ne répare pas un nombre insuffisant de threads. Avec seulement 3 blocs de 256 threads, les éléments 768 à 999 ne seraient pas calculés.

### 1.10. Deux dimensions : deux numérotations différentes

Le CM1 déroule l'exemple `grid = (3, 2)`, `block = (4, 3)`, `blockIdx = (1, 0)`, `threadIdx = (1, 2)`. Pour numéroter les threads **bloc par bloc**, avec `x` variant le plus vite :

$$
b=\texttt{blockIdx.y}\times\texttt{gridDim.x}+\texttt{blockIdx.x}=1,
$$
$$
t=\texttt{threadIdx.y}\times\texttt{blockDim.x}+\texttt{threadIdx.x}=9,
$$
$$
T=\texttt{blockDim.x}\times\texttt{blockDim.y}=12,
\qquad g=bT+t=21.
$$

![Coordonnées du thread choisi](../CM/Images/cours1_img_060.jpg)

*Figure 2. Exemple du CM1, pages 77-84 : combiner le numéro du bloc et celui du thread. Le titre de l’agrandissement indique « Block (1,1) », mais la grille sélectionne (1,0) : les calculs suivent le bloc (1,0).*

Pour traiter une matrice en associant `x` aux colonnes et `y` aux lignes, on calcule plutôt les coordonnées des données :

$$
\begin{aligned}
x&=\texttt{blockIdx.x}\times\texttt{blockDim.x}+\texttt{threadIdx.x}=5,\\
y&=\texttt{blockIdx.y}\times\texttt{blockDim.y}+\texttt{threadIdx.y}=2.
\end{aligned}
$$

Dans une matrice stockée par lignes de largeur `W = 12`, l'élément correspondant est `p = y × W + x = 29`. **21 et 29 ne répondent pas à la même question** : le premier est une numérotation par blocs, le second est une adresse linéaire selon l'organisation de la matrice. Il faut annoncer la convention avant de calculer.

### 1.11. Généralisation à trois dimensions

Pour une numérotation par blocs avec `x` le plus rapide, puis `y`, puis `z` :

```cpp
int block_id = (blockIdx.z * gridDim.y + blockIdx.y)
               * gridDim.x + blockIdx.x;
int thread_id = (threadIdx.z * blockDim.y + threadIdx.y)
                * blockDim.x + threadIdx.x;
int threads_per_block = blockDim.x * blockDim.y * blockDim.z;
int global_id = block_id * threads_per_block + thread_id;
```

La multiplication par une dimension signifie : sauter tous les éléments déjà parcourus dans les dimensions plus rapides. Ces expressions supposent de petites dimensions permettant de rester dans la capacité d'un `int` ; pour de grands domaines, il faut aussi choisir un type entier suffisamment large.

Vérification rapide : `grid = (2, 3, 2)`, `block = (4, 2, 2)`, `blockIdx = (1, 2, 1)`, `threadIdx = (3, 1, 1)`. On obtient `block_id = 11`, `thread_id = 15`, `threads_per_block = 16`, `global_id = 191`. Il y a 192 threads au total : le dernier numéro est donc bien 191.

### 1.12. Addition de vecteurs : suivre tout le trajet des données

Le fragment ci-dessous exprime le cycle complet d'une opération, avec `a`, `b`, `c` déjà alloués côté host. Il adapte le CM1 en calculant la taille de grille et en conservant un nom unique pour le kernel. Pour garder le trajet des données visible, la gestion détaillée des erreurs CUDA est omise ; ce fragment ne constitue pas un compte rendu d'exécution GPU.

```cpp
#include <cuda_runtime.h>
#include <cstddef>

__global__ void vecAddKernel(const double *a, const double *b,
                             double *c, int N)
{
    std::size_t i = std::size_t(blockIdx.x) * blockDim.x + threadIdx.x;
    if (i < std::size_t(N)) {
        c[i] = a[i] + b[i];
    }
}

void vector_add(const double *a, const double *b, double *c, int N)
{
    if (N <= 0) {
        return;
    }
    std::size_t bytes = std::size_t(N) * sizeof(double);
    double *d_a = nullptr;
    double *d_b = nullptr;
    double *d_c = nullptr;

    cudaMalloc((void **)&d_a, bytes);
    cudaMalloc((void **)&d_b, bytes);
    cudaMalloc((void **)&d_c, bytes);
    cudaMemcpy(d_a, a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, bytes, cudaMemcpyHostToDevice);

    int B = 256;
    int G = N / B + (N % B != 0);
    vecAddKernel<<<G, B>>>(d_a, d_b, d_c, N);
    cudaMemcpy(c, d_c, bytes, cudaMemcpyDeviceToHost);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
}
```

Le calcul de `G` évite ici l'addition `N + B - 1` et son éventuel dépassement de capacité. La copie bloquante vers le host, placée après le kernel dans le même flux par défaut, permet d'utiliser les résultats après son retour réussi. Dans un programme réel, vérifier chaque appel CUDA et les erreurs de lancement et d'exécution avant de conclure que le résultat est valide.

`__global__` déclare le kernel exécuté sur le device. Les chevrons `<<<G, B>>>` indiquent la configuration de lancement ; un appel ordinaire `vecAddKernel(...)` ne remplace pas cette syntaxe. Un fichier CUDA est normalement confié à `nvcc`, qui organise la compilation des parties host et device.

### 1.13. Questions de contrôle et erreurs fréquentes

1. **Pourquoi chaque thread ne contient-il pas la boucle complète sur `N` ?** Dans cette décomposition, chaque thread traite son propre indice ; répéter toute la boucle dans tous les threads reproduirait le travail et provoquerait des écritures concurrentes.
2. **Un thread peut-il traiter plusieurs éléments ?** Oui. « Un thread par élément » est la décomposition de l'exemple, pas une obligation du langage ; un kernel peut contenir des boucles.
3. **`<<<32, 64>>>` suffit-il pour n'importe quel `N` ?** Non : ce lancement couvre 2048 indices avec la formule à un élément par thread. Il faut vérifier la couverture et les bornes.
4. **Un bloc de 48 threads contient combien de warps ?** Deux : un warp de 32 threads et un second dont 16 positions correspondent à des threads du bloc. Des threads de deux blocs différents ne sont pas réunis pour compléter ce warp.
5. **Pourquoi le tableau `c` n'est-il pas copié vers le GPU ?** Le kernel écrit tous les éléments utiles sans lire leur ancienne valeur. L'allocation reste indispensable.
6. **Les dimensions 2D imposent-elles un tableau 2D ?** Non. Le programmeur définit le lien entre coordonnées CUDA et données, puis vérifie que chaque donnée utile est traitée correctement.
7. **La grille garantit-elle l'ordre des blocs ?** Non. Ne pas faire dépendre la correction d'un ordre implicite d'exécution des blocs dans le modèle de base.

### 1.14. Repères dans les sources

| Notion | Pages du CM1 actuel |
| --- | --- |
| Accélérateurs, connexions, host/device | 8-19 ; exemples d'intégration 24-30 |
| Architecture NVIDIA et Kepler | 34-39, dont l'ajout de la page 38 |
| Volta, Ampere, Hopper, Grace-Hopper | 40-47 |
| Modèles de programmation | 49-52 |
| Cycle de vie des données et compilation | 55-70 |
| Threads, indices, lancement et programme | 71-96 |

La page 87 présente également le **thread block cluster**, un regroupement entre grille et blocs, avec des mécanismes de lancement supplémentaires. Le présent chapitre garde ce repère sans reprendre son attribution historique à Blackwell comme un fait vérifié. Les graphiques Top500 et les tableaux de pics servent de contexte historique et ne sont pas développés en données actuelles.

Pour reprendre les explications en détail : [CM1 actuel](../CM/APM_Cours1_en.pdf), [support chinois enrichi](../CM/APM_Cours1_zh.md), [ancienne extraction](../CM/APM_Cours1.md). L'ancienne extraction repose sur 93 pages et ne remplace pas le PDF actuel. Les exemples de calcul et les mises en garde de ce chapitre sont des reformulations pédagogiques ; ils ne constituent pas une liste officielle de questions d'examen.
