# APM — TP1 : optimisation des accès mémoire

**M2 — Architecture et programmation d’accélérateurs matériels, 2026–2027**  
Université de Versailles Saint-Quentin-en-Yvelines — Université Paris-Saclay  
**Enseignant :** adrien.roussel@cea.fr  
**Sous-titre du sujet :** utilisation de la mémoire partagée

[中文版](tp1_zh.md) · [Sujet original (PDF)](tp1.pdf)

## Objectifs et conventions

L’objectif de ce TP est de comprendre les différentes mémoires d’un GPU et leur utilisation pour un calcul classique d’algèbre linéaire : le produit matriciel. Le sujet annonce la mémoire globale, la mémoire partagée, la mémoire constante et la mémoire unifiée.

Les objectifs sont :

- maîtriser la chaîne de compilation CUDA ;
- comprendre les accès mémoire sur le GPU ;
- optimiser les performances avec la mémoire partagée.

Le code principal prolonge celui de la séance précédente. Les questions Q.1 à Q.12 présentes dans ce document portent sur la compilation et une première multiplication en mémoire globale ; elles ne demandent pas encore de kernel en mémoire partagée.

> **Corrections de forme et de cohérence :** le répertoire des fichiers intermédiaires est uniformisé en `CUDAIMG` (le texte original mélange `TMP` et `CUDAIMG`). Les tirets des options sont corrigés. L’accumulateur de l’exemple est passé de `float` à `double`, conformément aux matrices et à `dgemm.c`.
>
> Les réponses ci-dessous sont complétées par les **mesures ROMEO du 9 octobre 2026**, job `738578`. Les indications Ruche du sujet sont conservées ; cette exécution utilise un GH200 sur ROMEO. Les commandes de reproduction figurent en fin de document.

## I. Chaîne de compilation

Sur Ruche, rechercher le module CUDA disponible avec `module spider cuda`, puis charger le module correspondant avec `module load cuda` si ce nom est disponible, ou avec son nom versionné. Depuis le répertoire contenant [tp1_check.cu](../CODE/Partie1/tp1_check.cu), exécuter :

```bash
mkdir -p CUDAIMG
nvcc --keep --keep-dir CUDAIMG -c tp1_check.cu
ls CUDAIMG
```

Les fichiers intermédiaires sont conservés dans `CUDAIMG`. L’option `-c` produit un fichier objet, sans édition de liens vers un exécutable.

### Q.1 — Identifier les fichiers produits

**Question.** Quel fichier correspond au PTX ? Lequel correspond au binaire CUDA ?

**Réponse.** Le fichier `.ptx` contient le code intermédiaire textuel pour le GPU. Le fichier `.cubin` contient le code machine GPU pour une architecture donnée. Un fichier `.fatbin` peut regrouper du PTX et/ou des cubins pour plusieurs cibles. Le fichier `.o` est l’objet côté hôte contenant notamment le code hôte et le code GPU embarqué ; ce n’est pas un cubin. Les noms précis dépendent de la version de `nvcc` et des options de compilation. Voir la [documentation NVIDIA de nvcc](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html).

**Observation sur ROMEO.** La commande utilisée est `nvcc -O3 -arch=sm_90 --keep --keep-dir CUDAIMG -c tp1_check.cu`. Le PTX est [tp1_check.ptx](../RESULTS/romeo-738578/CUDAIMG/tp1_check.ptx), le code machine GPU est [tp1_check.sm_90.cubin](../RESULTS/romeo-738578/CUDAIMG/tp1_check.sm_90.cubin), et le conteneur est [tp1_check.fatbin](../RESULTS/romeo-738578/CUDAIMG/tp1_check.fatbin). Le programme fourni affiche `TEST PASSED !` à l’exécution.

### Q.2 — Identifier le code compilé en PTX

**Question.** Quelles parties de `tp1_check.cu` sont conservées pour être compilées en PTX ?

**Réponse.** Dans le fichier fourni, le code de calcul destiné au GPU est :

```cpp
__global__ void kernel(int *v) {
    *v = 1;
}
```

Ce kernel devient un point d’entrée PTX, avec les déclarations nécessaires. `main`, les affichages, les requêtes sur le GPU, `malloc`, les appels `cudaMalloc`/`cudaMemcpy`/`cudaFree` et la vérification finale restent côté hôte. L’expression de lancement `kernel<<<...>>>` est transformée en code hôte qui déclenche le kernel ; le corps du kernel s’exécute sur le GPU.

**Preuve dans le PTX produit.** Le point d’entrée est `.visible .entry _Z6kernelPi`. Les instructions `mov.u32 %r1, 1` et `st.global.u32 [%rd2], %r1` réalisent l’écriture de l’entier 1 dans la mémoire globale pointée par le paramètre.

### Q.3 — Interpréter le suffixe `_30`

**Question.** À quoi correspond le suffixe `_30` des fichiers créés ?

**Réponse.** Dans les anciens noms contenant `compute_30` ou `sm_30`, `30` désigne la capacité de calcul **3.0**, associée à Kepler. `compute_30` désigne la cible virtuelle et `sm_30` la cible machine. Ce n’est ni la version de CUDA ni le nombre de threads. Ce suffixe vient d’un ancien environnement : il n’est pas garanti avec la commande actuelle. Il faut examiner les fichiers réellement produits et la ligne `.target` du PTX. Voir la [documentation historique de nvcc](https://docs.nvidia.com/cuda/archive/8.0/cuda-compiler-driver-nvcc/index.html).

**Environnement mesuré.** Le GH200 a une capacité de calcul 9.0. Le fichier produit porte le suffixe `.sm_90.cubin` et le PTX déclare `.version 8.8` et `.target sm_90`. Aucune cible `_30` n’a été produite dans cette exécution.

## II. Multiplication matricielle

La mémoire globale est accessible aux threads d’une grille. Nous utilisons `cudaMalloc` et `cudaFree` pour allouer et libérer les tableaux du GPU.

Le fichier séquentiel [dgemm.c](../CODE/Partie2/dgemm.c) calcule :

$$
C \leftarrow \alpha AB + \beta C.
$$

Compléter ce programme pour déporter le calcul sur le GPU, en utilisant l’extension `.cu`. Ici, les matrices sont carrées, de taille $N \times N$, stockées par lignes dans des tableaux contigus de $N^2$ valeurs `double`. La case $(i,j)$ se trouve à l’indice `i * N + j`.

Pour des matrices et scalaires déjà initialisés, l’algorithme séquentiel est :

```cpp
for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
        double sum = 0.0;
        for (int k = 0; k < N; k++) {
            sum += A[i * N + k] * B[k * N + j];
        }
        C[i * N + j] = alpha * sum + beta * C[i * N + j];
    }
}
```

Les extraits des réponses sont à intégrer progressivement au programme, pas à concaténer tels quels. Ils supposent `N > 0`, des allocations hôte réussies, `#include <cuda_runtime.h>` et la macro `CUDA_CHECK` fourni dans `tp1_check.cu`. Conserver les fonctions `init`, `dgemm` et `get_elapsedtime` de `dgemm.c`. Pour Q.11, ajouter `<vector>` et `<cmath>`. Définir les kernels hors de `main` ; placer allocations, copies et lancements dans `main`.

### 1. Allocation et transfert de données

### Q.4 — Allouer les matrices sur le GPU

**Question.** Avec `cudaMalloc`, allouer trois tableaux de $N^2$ éléments : deux opérandes et un résultat. Utiliser un stockage contigu et libérer les allocations avec `cudaFree` en fin de programme.

**Réponse.** Chaque tableau occupe $N^2 \times \mathrm{sizeof(double)}$ octets, soit $8N^2$ octets pour les `double` CUDA.

```cpp
size_t bytes = (size_t)N * N * sizeof(double);
double *d_A = nullptr, *d_B = nullptr, *d_C = nullptr;
CUDA_CHECK(cudaMalloc((void **)&d_A, bytes));
CUDA_CHECK(cudaMalloc((void **)&d_B, bytes));
CUDA_CHECK(cudaMalloc((void **)&d_C, bytes));
```

Après la récupération et la vérification du résultat :

```cpp
CUDA_CHECK(cudaFree(d_A));
CUDA_CHECK(cudaFree(d_B));
CUDA_CHECK(cudaFree(d_C));
```

Les tableaux hôte `A`, `B` et `C`, alloués avec `malloc`, sont libérés séparément avec `free`.

### Q.5 — Copier les données vers le GPU

**Question.** Transférer les données initialisées sur l’hôte vers le GPU avec `cudaMemcpy`.

**Réponse.** Après `init(A, B, C, N)`, copier les trois matrices :

```cpp
CUDA_CHECK(cudaMemcpy(d_A, A, bytes, cudaMemcpyHostToDevice));
CUDA_CHECK(cudaMemcpy(d_B, B, bytes, cudaMemcpyHostToDevice));
CUDA_CHECK(cudaMemcpy(d_C, C, bytes, cudaMemcpyHostToDevice));
```

Il faut aussi initialiser `d_C`, car le calcul lit l’ancienne valeur de $C$ dans $\beta C$. Dans le programme fourni, `beta = 1` et $C$ est initialement nulle ; `cudaMalloc` ne met pas la mémoire à zéro.

### 2. Configuration du kernel

### Q.6 — Définir les blocs et la grille

**Question.** Utiliser `dim3` pour définir des blocs 2D de $32 \times 32$ threads, soit 1 024 threads par bloc. Prévoir un thread par élément de $C$. Pour simplifier, choisir $N$ multiple de 32.

**Réponse.** On prend l’axe `x` pour les colonnes et l’axe `y` pour les lignes.

```cpp
dim3 block(32, 32);
dim3 grid((N + block.x - 1) / block.x,
          (N + block.y - 1) / block.y);
```

Si $N$ est multiple de 32, la grille contient $(N/32) \times (N/32)$ blocs, soit exactement $N^2$ threads. Pour $N=1024$, cela donne $32 \times 32$ blocs. L’arrondi supérieur couvre aussi les autres tailles, avec le test de limites de Q.10. Vérifier que le GPU accepte 1 024 threads par bloc et les dimensions demandées ; cette configuration imposée par le sujet n’est pas nécessairement la plus performante.

### Q.7 — Lancer un kernel vide

**Question.** Écrire puis lancer un kernel encore vide sur la grille définie précédemment.

**Réponse.** `__global__` déclare une fonction exécutée sur le GPU et appelée depuis l’hôte.

```cpp
__global__ void empty_kernel() {
}

// In main():
empty_kernel<<<grid, block>>>();
CUDA_CHECK(cudaGetLastError());
```

Le lancement est asynchrone vis-à-vis de l’hôte. `cudaGetLastError` vérifie les erreurs de lancement ; les erreurs d’exécution doivent aussi être contrôlées lors d’une synchronisation ou de la copie suivante.

### Q.8 — Récupérer le résultat

**Question.** Après l’exécution du kernel, transférer le résultat vers l’hôte.

**Réponse.** Copier `d_C` vers `C` :

```cpp
CUDA_CHECK(cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost));
```

Ici, le kernel et la copie utilisent le même flux par défaut. La copie GPU vers CPU attend les opérations précédentes de ce flux et ne retourne qu’une fois le résultat disponible sur l’hôte. À l’étape Q.7, le kernel vide laisse simplement les valeurs initiales inchangées.

### 3. Écriture du kernel

### Q.9 — Calculer les indices

**Question.** À partir des indices et dimensions de la grille, calculer la ligne et la colonne de l’élément de $C$ associé au thread.

**Réponse.**

```cpp
int row = blockIdx.y * blockDim.y + threadIdx.y;
int col = blockIdx.x * blockDim.x + threadIdx.x;
```

Le thread traite `C[row * N + col]`. Deux threads valides différents traitent deux éléments différents.

### Q.10 — Calculer un élément de C

**Question.** Pour chaque thread, calculer l’élément de $C$ correspondant.

**Réponse.** Le thread parcourt la ligne `row` de $A$ et la colonne `col` de $B$, puis applique les coefficients $\alpha$ et $\beta$.

```cpp
__global__ void dgemm_kernel(int N, double alpha,
                             const double *A, const double *B,
                             double beta, double *C) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row >= N || col >= N) return;

    double sum = 0.0;
    for (int k = 0; k < N; k++) {
        sum += A[row * N + k] * B[k * N + col];
    }
    C[row * N + col] = alpha * sum + beta * C[row * N + col];
}
```

Pour les coefficients du programme fourni, remplacer le lancement vide et la copie de Q.8 par :

```cpp
double alpha = 1.0, beta = 1.0;
dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost));
```

Aucun `__syncthreads()` n’est nécessaire : chaque thread accumule dans une variable locale et écrit un élément distinct. Cette première version utilise la mémoire globale pour les matrices.

### 4. Analyse des performances

### Q.11 — Mesurer et comparer les temps

**Question.** Utiliser `cudaEventElapsedTime` pour mesurer le temps GPU. Examiner le coût du produit matriciel et du transfert du résultat vers l’hôte, puis comparer au calcul CPU séquentiel.

**Réponse.** Mesurer séparément le kernel avec deux événements CUDA et le temps « lancement + calcul + retour de $C$ » avec l’horloge hôte `get_elapsedtime`. Le second inclut les frais de lancement et de mesure, mais exclut les allocations et les copies initiales CPU vers GPU. Pour un temps complet de l’application, il faudrait inclure ces étapes aussi. `cudaEventElapsedTime` renvoie des millisecondes ; les événements doivent être terminés avant la lecture. Voir la [documentation NVIDIA des événements CUDA](https://docs.nvidia.com/cuda/cuda-runtime-api/cuda_runtime_api/group__CUDART__EVENT.html).

Le bloc suivant **remplace** le lancement et la récupération de Q.10. Le placer après les copies de Q.5 et la configuration de Q.6, avant tout calcul modifiant `C`, avec `alpha = 1.0` et `beta = 1.0` définis. Il conserve une copie du $C$ initial pour que CPU et GPU calculent la même opération.

```cpp
// Keep the same initial C for the CPU, warm-up and measured GPU run.
std::vector<double> C_initial(C, C + (size_t)N * N);
std::vector<double> C_cpu = C_initial;

double cpu_start = get_elapsedtime();
dgemm(N, N, N, alpha, A, B, beta, C_cpu.data());
double cpu_ms = (get_elapsedtime() - cpu_start) * 1e3;

// Warm-up (excluded from timing).
dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaDeviceSynchronize());
CUDA_CHECK(cudaMemcpy(d_C, C_initial.data(), bytes,
                      cudaMemcpyHostToDevice));
CUDA_CHECK(cudaDeviceSynchronize());

cudaEvent_t start, stop;
CUDA_CHECK(cudaEventCreate(&start));
CUDA_CHECK(cudaEventCreate(&stop));

double gpu_start = get_elapsedtime();
CUDA_CHECK(cudaEventRecord(start));
dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaEventRecord(stop));
CUDA_CHECK(cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost));
double gpu_with_copy_ms = (get_elapsedtime() - gpu_start) * 1e3;

CUDA_CHECK(cudaEventSynchronize(stop));
float kernel_ms = 0.0f;
CUDA_CHECK(cudaEventElapsedTime(&kernel_ms, start, stop));
CUDA_CHECK(cudaEventDestroy(start));
CUDA_CHECK(cudaEventDestroy(stop));

printf("CPU: %.3f ms\n", cpu_ms);
printf("GPU kernel: %.3f ms\n", kernel_ms);
printf("GPU kernel + D2H (host): %.3f ms\n", gpu_with_copy_ms);
printf("Speedup (kernel): %.3f\n", cpu_ms / kernel_ms);
printf("Speedup (kernel + D2H): %.3f\n", cpu_ms / gpu_with_copy_ms);

bool correct = true;
for (size_t i = 0; i < C_initial.size(); i++) {
    double tolerance = 1e-10 + 1e-10 * std::abs(C_cpu[i]);
    if (!std::isfinite(C[i]) || !std::isfinite(C_cpu[i]) ||
        std::abs(C[i] - C_cpu[i]) > tolerance) {
        correct = false;
        break;
    }
}
printf("Validation: %s\n", correct ? "PASSED" : "FAILED");
```

La tolérance proposée est un contrôle pratique pour ce TP, à adapter à l’échelle des données et à $N$. Un échec doit être étudié avant toute comparaison de performances. Pour les données de `init`, $A_{ik}=i$, $B_{kj}=k$ et $C^{(0)}=0$ ; avec $\alpha=\beta=1$, on peut aussi vérifier $C_{ij}=iN(N-1)/2$.

Répéter les mesures après échauffement, restaurer `d_C` depuis `C_initial` avant chaque répétition, hors chronométrage, puis rapporter une médiane. Sinon, avec $\beta=1$, les lancements successifs accumulent des résultats différents. Noter le CPU, le GPU, la version CUDA, $N$ et les options de compilation. Les mesures obtenues sont présentées ci-dessous.

**Conditions ROMEO.** Mesures du 9 octobre 2026 à 14 h 27, heure de Paris, sur `romeo-a057`, job Slurm `738578`. GPU NVIDIA GH200 120GB ; un cœur ARM Neoverse-V2 du CPU Grace, fixé au CPU 280 ; CUDA 12.9.41, GCC 11.5.0, pilote 590.48.01. Compilation avec `-O3 -arch=sm_90`. Matrices en `double`, blocs `32×32`, données de la fonction `init` fournie et `alpha = beta = 1`.

Chaque implémentation est exécutée une fois pour l’échauffement, puis mesurée 5 fois. Chaque colonne de temps donne sa propre médiane. Le CPU conserve la boucle séquentielle `i → j → k`, sans BLAS ni multithreading. Les tableaux hôte sont en mémoire pageable ordinaire. Les événements encadrent uniquement le kernel ; la mesure hôte « avec retour » inclut le lancement, l’enregistrement des événements, le calcul et la copie GPU→CPU, mais exclut allocations, initialisation et copies initiales CPU→GPU. Validation, échauffement et restauration du C initial sont hors chronométrage.

| N | CPU séquentiel / ms | Kernel GPU / ms | GPU avec retour / ms | Accélération kernel | Accélération avec retour |
|---:|---:|---:|---:|---:|---:|
| 256 | 11.966112 | 0.036736 | 0.055616 | 325.73× | 215.16× |
| 512 | 205.259776 | 0.093152 | 0.121568 | 2203.49× | 1688.44× |
| 1024 | 1846.268896 | 0.577568 | 0.644448 | 3196.63× | 2864.89× |

Pour ces trois tailles, le calcul GPU reste plus rapide que le CPU fourni, même avec le retour du résultat. Les fortes accélérations sont relatives à la triple boucle naïve ; elles ne mesurent pas un gain face à une bibliothèque BLAS optimisée ou à un CPU multicœur. Le bénéfice de la mémoire partagée n’est pas mesuré ici.

**Validation.** Pour les trois tailles de performance, les résultats CPU et GPU coïncident exactement avec $C_{ij}=iN(N-1)/2$ : erreur absolue maximale nulle. Des cas supplémentaires `N = 1, 31, 32, 33, 65`, avec valeurs fractionnaires signées, C initial non nul, `alpha = 0.75` et `beta = -0.5`, passent tous la comparaison à une référence accumulée en `long double`. L’erreur absolue maximale est d’environ $2.164\times10^{-15}$. Le `memcheck` de Compute Sanitizer pour `N=33` rapporte **0 errors** ; ce temps instrumenté est exclu du tableau de performance.

[Journal complet](../RESULTS/romeo-738578/run.log) · [Mesures individuelles et médianes](../RESULTS/romeo-738578/measurements.json) · [Fin du job Slurm](../RESULTS/romeo-738578/slurm-accounting.txt)

### Q.12 — Complexité et FLOP/s

**Question.** Quelle est la complexité arithmétique ? Calculer le débit en FLOP/s de l’implémentation.

**Réponse.** Il y a $N^2$ éléments à calculer et $N$ étapes par produit scalaire : le travail total est $\Theta(N^3)$. Chaque thread effectue $\Theta(N)$ opérations ; le parallélisme ne change pas le travail arithmétique total.

Avec une multiplication et une addition par itération, on utilise conventionnellement :

$$
F \simeq 2N^3.
$$

Le comptage littéral du code ajoute deux multiplications et une addition par élément pour $\alpha\,\mathrm{sum}+\beta C$, soit $2N^3+3N^2$ opérations avant simplifications du compilateur. Une FMA compte pour deux FLOP, même si elle est exécutée comme une seule instruction.

Pour un temps $t_s$ en secondes, ou $t_{ms}$ en millisecondes :

$$
P_{\mathrm{FLOP/s}} = \frac{2N^3}{t_s},
\qquad
P_{\mathrm{GFLOP/s}} = \frac{2N^3}{t_{ms}\,10^6}.
$$

```cpp
double operations = 2.0 * N * N * N;
double kernel_gflops = operations / (kernel_ms * 1e6);
printf("GPU kernel: %.3f GFLOP/s\n", kernel_gflops);
```

Avec $N=1024$, $2N^3=2\,147\,483\,648$ FLOP. Insérer le temps réellement mesuré pour obtenir le débit. Utiliser `kernel_ms` pour le débit du kernel ; utiliser `gpu_with_copy_ms` donne un débit effectif incluant le retour du résultat, à nommer explicitement. Les copies ne sont pas comptées comme des FLOP. Les débits mesurés sur ROMEO sont présentés ci-dessous.

| N | CPU / GFLOP/s | Kernel GPU / GFLOP/s | GPU avec retour / GFLOP/s |
|---:|---:|---:|---:|
| 256 | 2.804 | 913.394 | 603.326 |
| 512 | 1.308 | 2881.693 | 2208.112 |
| 1024 | 1.163 | 3718.149 | 3332.285 |

Par exemple, pour $N=1024$ :

$$
P_{\mathrm{kernel}}=\frac{2\times1024^3}{0.577567995\times10^6}
\simeq 3718.149\ \mathrm{GFLOP/s}.
$$

Ce débit est celui de cette version en mémoire globale, dans la configuration mesurée.

## III. Programme complet et reproduction sur ROMEO

L’implémentation complète est [dgemm.cu](../CODE/Partie2/dgemm.cu). Le script [run_romeo.sh](../CODE/run_romeo.sh) compile, vérifie et mesure le programme. Les fichiers fournis `dgemm.c` et `tp1_check.cu` sont conservés.

Le répertoire distant est `/gpfs/projet/r260073/hibouwu/coursework/apm-tp1-20261009`. Les quotas home et scratch étant pleins, cette exécution utilise le répertoire personnel du projet, sans supprimer les fichiers de recherche existants. Les empreintes des sources locales et distantes concordent ; les sources mesurées sont archivées dans [source](../RESULTS/romeo-738578/source/), avec le manifeste [source.sha256](../RESULTS/romeo-738578/source.sha256).

Depuis le terminal local, se connecter puis exécuter via Slurm :

```bash
ssh romeo
cd /gpfs/projet/r260073/hibouwu/coursework/apm-tp1-20261009/CODE
srun --account=r260073 --partition=instant --constraint=armgpu \
    --nodes=1 --ntasks=1 --cpus-per-task=1 --mem=4G \
    --gpus-per-node=1 --time=00:15:00 --job-name=apm-tp1 \
    --cpu-bind=cores bash ./run_romeo.sh
```

Le script charge CUDA 12.9 sur le nœud de calcul et conserve le journal et les fichiers intermédiaires dans `RESULTS/romeo-numéro_du_job/`. Ne pas exécuter le programme GPU sur le nœud de connexion. La commande demande un nouveau job ; le job `738578` est terminé normalement, état `COMPLETED`, code de sortie `0:0`, durée d’allocation de 22 secondes, ressources libérées. Si d’autres travaux demandent aussi un GH200, utiliser le verrou GPU local commun pour sérialiser les allocations.

Dans une allocation GPU personnelle déjà active, après chargement de CUDA, on peut aussi compiler et exécuter depuis `CODE` :

```bash
nvcc -std=c++17 -O3 -arch=sm_90 -Xcompiler=-Wall,-Wextra \
    Partie2/dgemm.cu -o dgemm
./dgemm 1024 5
./dgemm 33 2 general
```

Les arguments sont la taille de matrice, le nombre de mesures et l’option `general` pour les données de validation. Sans argument, le programme utilise `N=1024`, 5 mesures et les données du sujet. Les exécutables rapatriés sont des binaires aarch64 destinés aux nœuds de calcul ROMEO correspondants.
