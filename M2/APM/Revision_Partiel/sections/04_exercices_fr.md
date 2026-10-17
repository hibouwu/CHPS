## 4. Exercices corrigés et lecture de code

### 4.1. Parcours et correspondance avec les documents

Le planning fourni place le DST le **22 octobre au matin**, après CM1-CM3, TD1, TD2 et TP1. Les sections 4.2-4.8 constituent donc le parcours principal. Les sections 4.9-4.14 rassemblent les anciens exercices utiles pour approfondir ; elles ne sont pas présentées comme des questions obligatoires du DST. Le TP2 d’optimisation de GEMM est prévu après le DST, le 22 octobre après-midi.

| Document | Année portée par la source | Couverture dans cette section |
|---|---|---|
| [TD1 et réponses existantes](../TD1%20%20APM/td1.md) | 2026-2027 | Q.1-Q.9 : indexation, AXPY, émulation CPU |
| [TD2 Monte Carlo](../TD2/TD2/SUJET/td2.pdf) | 2026-2027 | Q.1-Q.6 : C, OpenMP, CUDA, cuRAND |
| [TP1 en français](../TP1/SUJET/tp1.md) | 2026-2027 | Q.1-Q.12 : compilation, GEMM, validation, mesure |
| [Ancien TP1 corrigé](../TDTP2025/TP/tp1_correction.pdf) | **2024-2025** | Compléments Q.13-Q.21 : modèle mémoire, coalescence, tuiles |
| [Ancien TD noté SDF](../TDTP2025/TD/td2.pdf) | 2025-2026 | Q.1-Q.7 : volume 3D, échantillonnage, projection |
| [TP2 streams : sujet](../TDTP2025/TP/tp2_sujet_2025-2026.pdf) / [corrigé](../TDTP2025/TP/tp2_correction.pdf) | Sujet 2025-2026, corrigé **2024-2025** | Q.1-Q.15 : transferts, dépendances, chronométrage |

Les réponses théoriques ci-dessous ont été recomposées à partir des fichiers. Les extraits de TD2, SDF, tuilage et streams sont des solutions pédagogiques, **sans nouvelle exécution GPU**. Les seuls temps repris sont ceux du TP1 déjà mesuré, identifiés en 4.8. Les extraits CUDA supposent les en-têtes adaptés et un contrôle des erreurs ; `CUDA_CHECK` est disponible dans le code du TP1.

### 4.2. TD1 Q.1-Q.5 : aplatir des indices

**Question.** Numéroter les blocs d’une grille 2D puis 3D, compter les threads d’un bloc 3D et construire un identifiant unique de thread.

**Réponse.** On choisit explicitement l’ordre **x le plus rapide, puis y, puis z**. Chaque dimension ajoute le nombre d’éléments contenus dans les lignes ou plans précédents.

```cpp
// Q.1: block in a 2D grid
unsigned int block2 = blockIdx.y * gridDim.x + blockIdx.x;
// Q.2: block in a 3D grid
unsigned int block3 = (blockIdx.z * gridDim.y + blockIdx.y)
                    * gridDim.x + blockIdx.x;
// Q.3: number of threads in a 3D block
unsigned int block_size = blockDim.x * blockDim.y * blockDim.z;
// Q.4: thread index within one block
unsigned int local = (threadIdx.z * blockDim.y + threadIdx.y)
                   * blockDim.x + threadIdx.x;
// Q.5: unique thread index, blocks stored consecutively
unsigned int global = block3 * block_size + local;
```

Pour `gridDim=(2,2,2)`, `blockDim=(4,2,2)`, `blockIdx=(1,0,1)` et `threadIdx=(2,1,0)`, on obtient `block3=5`, `block_size=16`, `local=6`, puis **`global=86`**.

Q.4 donne un indice **dans le bloc**, malgré l’expression « indice global » du sujet. Q.5 ne donne pas nécessairement l’adresse d’un tableau spatial 3D. Pour celui-ci, calculer d’abord `gx=blockIdx.x*blockDim.x+threadIdx.x`, et de même pour `gy,gz`, puis `gx + Nx*(gy + Ny*gz)`. Ne pas mélanger ces deux ordres.

**Contrôle sur papier.** Le premier indice vaut 0, le dernier vaut « nombre total − 1 ». Deux coordonnées différentes ne doivent pas produire le même indice. Pour de très grands volumes, passer en `size_t` avant les multiplications.

### 4.3. TD1 Q.6-Q.9 : lire le programme AXPY

Source effective : [tp1.cu](../TD1%20%20APM/tp1.cu). Le sujet mentionne `td2.cu`, absent du dossier ; les réponses portent sur le fichier réellement fourni.

**Q.6 - Où s’exécute chaque partie ?** `main`, les allocations, l’initialisation, les copies et l’instruction de lancement s’exécutent sur le CPU. Le corps de la fonction `__global__ kernel` s’exécute sur le GPU. Un appel à `cudaMalloc` est du code hôte qui alloue de la mémoire device.

**Q.7 - Que calcule le programme ?** Il effectue une opération AXPY :

$$
y_i\leftarrow 3.14x_i+y_i,
\qquad x_i=\frac1{i+1},\quad y_i^{(0)}=\frac{i-1}{i+1},
\qquad y_i=\frac{i+2.14}{i+1}.
$$

Ainsi `y[0]=2.14`. Le programme recopie le résultat puis libère les tableaux, sans l’afficher.

**Q.8 - Combien de blocs et de threads ?** Avec `N=1000` et 64 threads par bloc, il faut `ceil(1000/64)=16` blocs. Les **1024 threads lancés** comprennent **1000 threads utiles** et **24 threads hors limites**, éliminés par `if (i < N)`.

**Q.9 - Émuler sans CUDA.** Conserver deux ensembles de tableaux, les copies, une fonction kernel et les deux boucles bloc/thread. Voici le cœur de la solution ; le [programme CPU complet](../TD1%20%20APM/tp1_cpu.cpp) existe déjà.

```cpp
void kernel_cpu(const double *x, double *y, double alpha,
                int N, int block, int thread, int block_size) {
    int i = block * block_size + thread;
    if (i < N) y[i] = alpha * x[i] + y[i];
}
// d_x and d_y are separate CPU arrays; copy inputs into them first.
for (int block = 0; block < 16; ++block)
    for (int thread = 0; thread < 64; ++thread)
        kernel_cpu(d_x, d_y, 3.14, 1000, block, thread, 64);
// Copy d_y back into h_y, then release all four arrays.
```

Il s’agit d’une émulation **sémantique et séquentielle** de l’indexation et du flux des données ; elle ne reproduit ni les warps ni l’ordonnancement réel du GPU.

### 4.4. TD2 Q.1-Q.2 : Monte Carlo sur CPU

**Principe corrigé.** Tirer des points uniformes dans `[0,1] × [0,1]` et compter ceux pour lesquels `x*x+y*y<=1`. Le quart de disque a une aire `π/4`, le carré a une aire 1. La phrase initiale du sujet parlant d’un carré de côté 1 et d’un cercle centré de rayon 1 est géométriquement ambiguë ; l’algorithme utilise bien ce carré et ce quart de disque.

$$
\widehat\pi=4\frac{H}{T},\qquad
\operatorname{SE}(\widehat\pi)=4\sqrt{\frac{p(1-p)}T},\quad p=\frac\pi4.
$$

L’erreur statistique typique décroît comme `1/sqrt(T)` sous l’hypothèse de tirages indépendants. Multiplier le nombre de tirs par 100 réduit cette échelle d’erreur d’un facteur 10, pas 100.

**Q.1 - Version C séquentielle.** Le fichier [pi.c](../TD2/TD2/CODE/pi.c) contient déjà cette boucle. `10E7` signifie **100 000 000** tirs, pas dix millions.

```c
uint64_t hits = 0;
srand(2026);
for (uint64_t trial = 0; trial < trials; ++trial) {
    double x = rand() / (double)RAND_MAX;
    double y = rand() / (double)RAND_MAX;
    if (x * x + y * y <= 1.0) ++hits;
}
double pi = 4.0 * (double)hits / (double)trials;
```

**Q.2 - Version OpenMP demandée.** Chaque thread effectue `trials_per_thread` tirs, écrit une estimation dans sa case, puis le thread principal prend la moyenne. Il faut un état aléatoire **privé**, pas des appels concurrents à un générateur global partagé. Exemple pédagogique C/POSIX pour Linux (`stdlib.h`, `stdint.h`, `omp.h`) :

```c
int capacity = omp_get_max_threads(), used = 0;
double *partial = malloc((size_t)capacity * sizeof(*partial));
#pragma omp parallel shared(partial, used)
{
    int tid = omp_get_thread_num();
    unsigned int state = 2026u + 104729u * (unsigned int)tid;
    uint64_t hits = 0;
    #pragma omp single
    used = omp_get_num_threads();
    for (uint64_t trial = 0; trial < trials_per_thread; ++trial) {
        double x = rand_r(&state) / (double)RAND_MAX;
        double y = rand_r(&state) / (double)RAND_MAX;
        if (x*x + y*y <= 1.0) ++hits;
    }
    partial[tid] = 4.0 * hits / trials_per_thread;
}
double pi = 0.0;
for (int tid = 0; tid < used; ++tid) pi += partial[tid];
pi /= used;
free(partial);
```

`rand_r` est une solution pédagogique POSIX, pas une preuve de qualité ou d’indépendance statistique des flux. La fin de la région parallèle garantit que le tableau est rempli. La moyenne simple est correcte parce que tous les threads font le même nombre de tirs ; sinon, additionner les nombres de succès et de tirs, puis calculer `4*sum(hits)/sum(trials)`.

### 4.5. TD2 Q.3-Q.6 : Monte Carlo sur GPU

**Q.3 - Configuration.** `512` blocs de `256` threads donnent **131 072 threads**. Avec `R=TRIALS_PER_THREAD`, le nombre total de tirs est `131072*R`.

**Q.4 - Allocation.** Un `double` par thread nécessite `131072*8=1048576` octets, soit **1 MiB**. **Q.5 - Rapatriement.** La copie D2H se place après le lancement ; dans le même stream, elle permet ensuite le calcul CPU de la moyenne.

```cpp
const int blocks = 512, threads = 256;
const int count = blocks * threads;
size_t bytes = (size_t)count * sizeof(double);
double *d_partial;
double *h_partial = (double *)malloc(bytes);
CUDA_CHECK(cudaMalloc((void **)&d_partial, bytes));
monte_carlo<<<blocks, threads>>>(d_partial, trials_per_thread, 2026ULL);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaMemcpy(h_partial, d_partial, bytes, cudaMemcpyDeviceToHost));
double pi = 0.0;
for (int i = 0; i < count; ++i) pi += h_partial[i];
pi /= count;
CUDA_CHECK(cudaFree(d_partial));
free(h_partial);
```

**Q.6 - Kernel.** Un état cuRAND local par thread et une séquence identifiée par `tid` évitent de donner exactement les mêmes tirs à tous les threads. Définir le kernel avant le code de lancement :

```cpp
#include <curand_kernel.h>
__global__ void monte_carlo(double *partial, unsigned long long trials,
                            unsigned long long seed) {
    unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;
    curandStatePhilox4_32_10_t state;
    curand_init(seed, (unsigned long long)tid, 0ULL, &state);
    unsigned long long hits = 0;
    for (unsigned long long trial = 0; trial < trials; ++trial) {
        double x = curand_uniform_double(&state);
        double y = curand_uniform_double(&state);
        if (x*x + y*y <= 1.0) ++hits;
    }
    partial[tid] = 4.0 * (double)hits / (double)trials;
}
```

Exiger `trials>0`. Les API prennent un **pointeur d’état** ; le prototype donné dans le sujet est incomplet. `curand_init` retourne `void`, et les fonctions uniformes de cuRAND produisent des valeurs dans `(0,1]`. Cette convention discrète n’invalide pas le modèle du quart de disque. Avec des générateurs CPU et GPU différents, on ne demande pas l’égalité bit à bit des estimations de π : vérifier le compte total, la plage `[0,4]`, la reproductibilité à configuration fixée et le comportement statistique.

### 4.6. TP1 Q.1-Q.3 : chaîne de compilation

**Q.1 - Quels fichiers ?** `.ptx` : représentation intermédiaire textuelle du code GPU ; `.cubin` : code machine pour une cible GPU ; `.fatbin` : conteneur de PTX et/ou de cubins ; `.o` : objet côté hôte, avec le code GPU embarqué. `-c` arrête avant l’édition de liens.

```bash
mkdir -p CUDAIMG
nvcc --keep --keep-dir CUDAIMG -c tp1_check.cu
```

**Q.2 - Quelle partie devient PTX ?** Dans [tp1_check.cu](../TP1/CODE/Partie1/tp1_check.cu), le kernel `__global__ void kernel(int *v) { *v=1; }` devient un point d’entrée GPU. `main`, `printf`, allocations, copies et vérification restent côté hôte. Le lancement est traduit en code hôte qui demande l’exécution du kernel.

**Q.3 - Que signifie `_30` ?** Une cible `sm_30` ou `compute_30` signifie la compute capability **3.0**, pas CUDA 3.0 et pas 30 threads. `compute_*` désigne une cible virtuelle, `sm_*` une cible machine. Les noms réels dépendent du compilateur et des options. L’ancienne mesure GH200 a produit `sm_90`, donc une capacité 9.0 ; elle ne doit pas être décrite avec le suffixe historique `_30`.

### 4.7. TP1 Q.4-Q.10 : construire un GEMM correct

Le [code séquentiel](../TP1/CODE/Partie2/dgemm.c) calcule `C ← αAB + βC` avec des matrices `double` stockées par lignes : `(row,col)` correspond à `row*N+col`.

**Q.4-Q.5 - Allouer et copier.** Allouer trois tableaux contigus de `N*N` éléments. Copier aussi le **C initial**, car `βC` est lu : `cudaMalloc` n’initialise pas le contenu.

```cpp
size_t bytes = (size_t)N * N * sizeof(double);
double *d_A, *d_B, *d_C;
CUDA_CHECK(cudaMalloc((void **)&d_A, bytes));
CUDA_CHECK(cudaMalloc((void **)&d_B, bytes));
CUDA_CHECK(cudaMalloc((void **)&d_C, bytes));
CUDA_CHECK(cudaMemcpy(d_A, A, bytes, cudaMemcpyHostToDevice));
CUDA_CHECK(cudaMemcpy(d_B, B, bytes, cudaMemcpyHostToDevice));
CUDA_CHECK(cudaMemcpy(d_C, C, bytes, cudaMemcpyHostToDevice));
```

**Q.6 - Configuration.** Le sujet impose `block(32,32)` : 1024 threads, donc 32 warps par bloc. La grille arrondie vers le haut couvre également les tailles non multiples de 32 ; vérifier les limites matérielles et conserver le test de bornes.

```cpp
dim3 block(32, 32);
dim3 grid((N + 31) / 32, (N + 31) / 32);
```

**Q.7 - Kernel vide.** Définir une fonction qui ne modifie pas les matrices, puis la lancer depuis `main` :

```cpp
__global__ void empty_kernel() {}
// In main(), after grid and block have been defined:
empty_kernel<<<grid, block>>>();
```

**Q.8 - Résultat.** Après le kernel, effectuer la copie ci-dessous. Dans ce stream, elle attend le calcul précédent.

```cpp
CUDA_CHECK(cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost));
```

**Q.9-Q.10 - Indices et calcul.** `x` parcourt les colonnes, `y` les lignes. Chaque thread calcule un unique élément ; la somme reste locale et utilise `double`.

```cpp
__global__ void dgemm_kernel(int N, double alpha, const double *A,
                             const double *B, double beta, double *C) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row >= N || col >= N) return;
    double sum = 0.0;
    for (int k = 0; k < N; ++k)
        sum += A[row*N+k] * B[k*N+col];
    C[row*N+col] = alpha * sum + beta * C[row*N+col];
}
// In main(), after allocations and copies:
dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost));
CUDA_CHECK(cudaFree(d_A));
CUDA_CHECK(cudaFree(d_B));
CUDA_CHECK(cudaFree(d_C));
```

Aucun `__syncthreads()` n’est nécessaire ici : aucune donnée intermédiaire n’est partagée entre threads. Avec l’initialisation fournie (`A[i,k]=i`, `B[k,j]=k`, `C=0`, `α=β=1`), le résultat attendu est `C[i,j]=i*N*(N-1)/2`. Cette formule permet une vérification indépendante de la boucle CPU.

### 4.8. TP1 Q.11-Q.12 : validation et performance

**Q.11 - Mesurer quoi ?** Distinguer le temps du kernel, le temps kernel + retour D2H et le temps complet incluant allocation et H2D. Le temps du simple appel de lancement ne mesure pas le calcul asynchrone. Pour le kernel, placer deux événements dans son stream :

```cpp
cudaEvent_t start, stop;
CUDA_CHECK(cudaEventCreate(&start));
CUDA_CHECK(cudaEventCreate(&stop));
CUDA_CHECK(cudaEventRecord(start));
dgemm_kernel<<<grid, block>>>(N, alpha, d_A, d_B, beta, d_C);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaEventRecord(stop));
CUDA_CHECK(cudaEventSynchronize(stop));
float kernel_ms;
CUDA_CHECK(cudaEventElapsedTime(&kernel_ms, start, stop));
CUDA_CHECK(cudaEventDestroy(start));
CUDA_CHECK(cudaEventDestroy(stop));
```

Pour kernel + D2H, mesurer sur l’hôte de juste avant le lancement à après la copie bloquante. Échauffer, répéter, prendre une statistique annoncée et restaurer C avant chaque essai : avec `β=1`, relancer sans restauration accumule le résultat. Vérifier les résultats avant d’interpréter les temps.

**Q.12 - Complexité et débit.** Il y a `N²` sorties et `N` itérations par sortie : travail total `Θ(N³)`, travail par thread `Θ(N)`. Une FMA compte pour deux FLOP. La convention dominante est :

$$
F\simeq2N^3,\qquad P_{\mathrm{GFLOP/s}}=\frac{2N^3}{t_{\mathrm{ms}}10^6},
\qquad S=\frac{t_{\mathrm{CPU}}}{t_{\mathrm{GPU}}}.
$$

Si l’on compte littéralement le code avec `αsum+βC`, on ajoute `3N²` opérations, avant simplifications du compilateur. Les copies ne sont pas des FLOP.

**Exemple historique vérifiable, pas une nouvelle mesure.** Le [journal](../TP1/RESULTS/romeo-738578/run.log) et les [mesures JSON](../TP1/RESULTS/romeo-738578/measurements.json) du **9 octobre 2026**, job ROMEO `738578`, décrivent un GH200, CUDA 12.9, FP64, `32×32` threads, une mise en chauffe puis cinq mesures. Le CPU de référence est une boucle naïve sur un seul cœur Grace. Le tableau donne les médianes de cinq essais ; la colonne kernel + D2H exclut allocations, initialisation et H2D initial. La restauration de C, la mise en chauffe et les vérifications restent hors mesure.

| N | CPU / ms | Kernel / ms | Kernel + D2H / ms | Kernel / GFLOP/s |
|---:|---:|---:|---:|---:|
| 256 | 11.966112 | 0.036736 | 0.055616 | 913.394 |
| 512 | 205.259776 | 0.093152 | 0.121568 | 2881.693 |
| 1024 | 1846.268896 | 0.577568 | 0.644448 | 3718.149 |

Ces chiffres ne mesurent ni un CPU BLAS optimisé ni les bénéfices de la mémoire partagée. À `N=1024`, l’accélération kernel par rapport à cette boucle est environ `3196.63`, et celle avec D2H `2864.89`. Les tests généraux à `N=1,31,32,33,65` avec C non nul figurent aussi dans les données ; ils complètent le cas d’initialisation très régulier du sujet. Voir le [programme complet](../TP1/CODE/Partie2/dgemm.cu).

### 4.9. Approfondissement - ancien TP1 Q.13-Q.16 : trafic et coalescence

Ces questions viennent du corrigé **2024-2025**. Sa numérotation diffère du TP1 actuel : son Q.12 porte sur le chronométrage, son Q.13 commence le modèle de performance. Les Q.1-Q.12 anciens reprennent les étapes de 4.6-4.8 ; un même numéro ne désigne pas forcément la même question.

**Q.13 - Borne idéale pour `C=AB`, FP32, N=4096.** Supposer chaque élément de A et B lu une fois et C écrit une fois. Cette version du problème ne lit pas de C initial.

$$
F=2N^3=137.438953472\times10^9\ \mathrm{FLOP},\qquad
V_r=8N^2=128\ \mathrm{MiB},\quad V_w=4N^2=64\ \mathrm{MiB}.
$$

$$
\begin{aligned}
V&=12N^2=192\ \mathrm{MiB}=201.326592\ \mathrm{MB},\\
t_{\mathrm{data}}&=V/BW,\qquad t_{\mathrm{compute}}=F/P_{\mathrm{peak}},\\
t&\ge\max(t_{\mathrm{data}},t_{\mathrm{compute}}).
\end{aligned}
$$

Le travail s’exprime en FLOP, pas en FLOP/s. $1\,\mathrm{MiB}=2^{20}$ octets, $1\,\mathrm{MB}=10^6$ octets. Le rapport `ρ=t_compute/t_data` compare deux bornes : `ρ>1` signifie que la borne calcul domine **dans ce modèle idéal**, pas que le kernel naïf mesuré est forcément limité par le calcul. Pour `β≠0`, ajouter la lecture du C initial au volume minimal.

**Q.14 - Comparaison au pic.** Calculer `P_mesuré=F/t`, puis `P_mesuré/P_crête`. La précision et les instructions doivent correspondre : un kernel FP64 scalaire ne se compare pas à un pic FP32 ou Tensor Core. Le rapport FP64/FP32 dépend du GPU ; il ne vaut pas systématiquement 1/2. Aucun nouveau débit n’est mesuré ici.

**Q.15 - Modèle de lignes de 128 B.** Pour `C=AB`, sans lecture du C initial, un thread lit N éléments de A, N de B et écrit un C. En FP64, le volume logique vaut `8(2N+1)` octets, soit **65544 octets** pour N=4096. Pour expliciter l’exercice, ignorer le partage de lignes entre threads et compter une écriture comme un transfert de ligne, sans allocation en écriture supplémentaire.

$$
V_{\mathrm{tout\ manque}}=N^2(2N+1)128\ \mathrm{B},\qquad
V_{\mathrm{localite\ ligne}}=N^2\left(\left\lceil\frac{N}{16}\right\rceil+N+1\right)128\ \mathrm{B}.
$$

Le second modèle exploite 16 doubles par ligne de A, mais suppose un manque par élément de la colonne de B. À N=4096, ces modèles donnent environ **16.002 TiB** et **8.502 TiB** ; une matrice occupe **128 MiB**. Ce sont des comptes pédagogiques, **pas un trafic DRAM observé** : coalescence, caches et réutilisation entre threads changent le résultat réel. Les chiffres de trafic du corrigé ancien ne sont pas cohérents avec son comptage ; le calcul est donc refait ici.

**Q.16 - Affectation coalescée.** Pour un warp à `row` fixe et `col` consécutif, à k fixé les threads lisent le même A et des B contigus, puis écrivent des C contigus. Prendre `col=blockIdx.x*T+threadIdx.x` et `row=blockIdx.y*T+threadIdx.y`. C’est déjà le choix du TP1 actuel. Avec un bloc 1D de `T*T` threads :

```cpp
int row = blockIdx.y * T + threadIdx.x / T;
int col = blockIdx.x * T + threadIdx.x % T;
```

Le `% T` porte sur `threadIdx.x`. La variante ancienne avec `threadIdx.y % T` est incorrecte pour un bloc 1D, où `threadIdx.y` vaut 0.

### 4.10. Approfondissement - ancien TP1 Q.17-Q.21 : tuiles partagées

**Q.17-Q.19 - Déclarer, charger, calculer.** Deux tuiles `T×T` de doubles occupent `2*T*T*8` octets partagés, soit **16 KiB pour T=32**. Un bloc produit une tuile de C. À chaque étape sur K, chaque thread charge un A et un B, puis réutilise les données chargées par les autres threads.

Pour compléter correctement Q.17-Q.19, il faut deux barrières : la première attend tous les chargements avant les lectures partagées ; la seconde empêche la tuile suivante d’écraser la précédente avant la fin de toutes ses lectures. Ce kernel gère aussi les tailles non multiples de T :

```cpp
template<int T>
__global__ void tiled_gemm(int N, const double *A, const double *B,
                            double *C, double alpha, double beta) {
    __shared__ double tile_A[T][T], tile_B[T][T];
    int tx = threadIdx.x, ty = threadIdx.y;
    int row = blockIdx.y * T + ty, col = blockIdx.x * T + tx;
    double sum = 0.0;
    for (int base = 0; base < N; base += T) {
        tile_A[ty][tx] = (row < N && base+tx < N)
                       ? A[row*N+base+tx] : 0.0;
        tile_B[ty][tx] = (base+ty < N && col < N)
                       ? B[(base+ty)*N+col] : 0.0;
        __syncthreads();
        for (int k = 0; k < T; ++k)
            sum += tile_A[ty][k] * tile_B[k][tx];
        __syncthreads();
    }
    if (row < N && col < N)
        C[row*N+col] = alpha * sum + beta * C[row*N+col];
}
```

Lancer avec `block(T,T)`. Tous les threads participent aux deux barrières, y compris ceux dont la sortie est hors limites : ils chargent zéro et n’écrivent pas C. Ne pas placer les barrières dans un `if (row<N && col<N)` divergent. Pour `C=AB`, prendre `alpha=1,beta=0` et fournir néanmoins un C initialisé, puisque ce code lit explicitement `beta*C`.

**Q.20 - Exécuter et vérifier le résultat.** Comparer la version tuilée à la version précédente et à une référence CPU avec les mêmes données et le même C initial. Tester une taille multiple de T et des frontières, par exemple `N=1,T-1,T,T+1,2*T+1`, avec valeurs positives et négatives et C non nul. Vérifier les valeurs finies et `abs(gpu-ref) <= atol + rtol*abs(ref)`, en choisissant la tolérance selon la précision, N et l’échelle des données. Une erreur variable d’un lancement à l’autre peut signaler les barrières manquantes ; vérifier aussi indices, zéros aux frontières et restauration de C. **Ce protocole est proposé, mais le kernel tuilé n’a pas été exécuté ici.**

**Q.21 - Gain FP32/FP64.** Mesurer les variantes avec les mêmes tailles, types, coefficients et périmètres, puis calculer `t_naïf/t_tuilé`. Le gain dépend des caches, débits arithmétiques, barrières et ressources par bloc. Les chiffres du corrigé concernent d’autres GPU ; **aucun gain du kernel ci-dessus n’a été mesuré dans cette préparation**.

### 4.11. Approfondissement - SDF Q.1-Q.5 : échantillonner un volume

Le TD noté **2025-2026** utilise une distance signée : négative à l’intérieur de l’objet, positive à l’extérieur. Il demande une couleur par point 3D, puis une projection 2D. Le template `Color`, `GetColor`, `PPMSave` cité dans le PDF n’est pas présent : les interfaces ci-dessous restent à adapter, ce n’est pas un programme complet prêt à compiler.

**Q.1 - Tableau contigu.** La figure utilise x rapide, puis y, puis z. Pour un cube de côté N :

```cpp
__host__ __device__ size_t index3(int x, int y, int z, int N) {
    return (size_t)x + (size_t)N * ((size_t)y + (size_t)N * z);
}
// PPMSave: color[index3(x, slice, z, N)]
```

**Q.2 - Allocation.** `count=(size_t)N*N*N`, `bytes=count*sizeof(Color)` ; utiliser `malloc(bytes)` sur l’hôte et `cudaMalloc(...,bytes)` sur le device. N=1000 donne **un milliard de couleurs** : 3 GB si `sizeof(Color)==3`, 4 GB si elle vaut 4. Vérifier la taille réelle, les échecs d’allocation et la mémoire disponible.

**Q.3 - Grille.** Un choix est `block(8,8,8)`, 512 threads, et `grid(125,125,125)` pour N=1000. Chaque thread gère un voxel ; conserver `x<N && y<N && z<N` pour les autres tailles. Cette configuration facilite le mapping, sans prétendre être optimale.

**Q.4 - Tranche Y=0.** Choisir explicitement `position(i)=-1+2*i/N`, donc l’intervalle `[-1,1[` ; la tranche est **slice=N/2=500**. Avec les deux bornes incluses, `-1+2*i/(N-1)`, les 1000 points ne contiennent pas exactement zéro : 499 et 500 encadrent Y=0. Énoncer la convention avant de choisir la tranche.

Copier le volume device vers l’hôte après l’échantillonnage, puis faire lire `(x,500,z)` par `PPMSave`. Garder le volume device pour la projection. Une copie de la seule tranche optimiserait le transfert, mais n’est pas nécessaire à la réponse.

**Q.5 - Couleurs.** Logique sous la convention de Q.4 :

```text
x = blockIdx.x * blockDim.x + threadIdx.x
y = blockIdx.y * blockDim.y + threadIdx.y
z = blockIdx.z * blockDim.z + threadIdx.z
if x < N and y < N and z < N:
    px = -1.0 + 2.0*x/N
    py = -1.0 + 2.0*y/N
    pz = -1.0 + 2.0*z/N
    color[index3(x,y,z,N)] = GetColor(px,py,pz)
```

### 4.12. Approfondissement - SDF Q.6-Q.7 : projeter sans course

**Q.6 - Grille.** Un thread prend une colonne `(x,z)` entière. Exemple : bloc 2D `block(32,8)`, grille `((N+31)/32,(N+7)/8)`. L’axe x CUDA couvre x, l’axe y CUDA couvre **z**. On lance environ N² threads, pas N³.

**Q.7 - Projection.** L’observateur est en `(0,+∞,0)`. Parcourir y croissant, remplacer la couleur chaque fois qu’elle est non noire : on garde la couleur visible au plus grand y. La borne est **y<N**, pas `y<=1000`.

```text
x = blockIdx.x * blockDim.x + threadIdx.x
z = blockIdx.y * blockDim.y + threadIdx.y
if x < N and z < N:
    last = Color(0,0,0)
    for y = 0, ..., N-1:
        current = color[index3(x,y,z,N)]
        if current.r != 0 or current.g != 0 or current.b != 0:
            last = current
    color[index3(x,0,z,N)] = last
```

Chaque thread écrit seulement la base de **sa colonne**, après l’avoir lue : ni atomique ni barrière entre threads. Ordonner échantillonnage puis projection dans un stream, ou par événement. Copier ensuite le résultat et afficher `slice=0`. Un thread par voxel écrivant simultanément dans `(x,0,z)` créerait une course.

### 4.13. Approfondissement - streams Q.1-Q.9 : découper et ordonner

Sujet **2025-2026**, corrigé **2024-2025**. Les programmes et `graph.pdf` cités ne sont pas présents. On reconstruit les principes ; la fonction exponentielle précise `func` ne peut pas être recopiée sans son source.

**Q.1 - Portage.** Calculer `i=blockIdx.x*blockDim.x+threadIdx.x`, tester `i<N`, puis appliquer `func` à l’élément i. Le kernel est `__global__`, la grille contient `(N+threads-1)/threads` blocs.

**Q.2-Q.4 - Streams.** Créer NSTREAMS streams et donner à chacun une portion distincte. Sans quatrième paramètre de lancement, le stream par défaut est utilisé. Son mode legacy ajoute des dépendances avec les streams bloquants ; le mode par thread a d’autres règles. Un lancement de kernel n’est pas pour autant bloquant pour le CPU : ordre GPU et retour de l’appel hôte sont deux notions différentes.

```cpp
cudaStream_t streams[NSTREAMS];
for (int s = 0; s < NSTREAMS; ++s)
    CUDA_CHECK(cudaStreamCreate(&streams[s]));
for (int s = 0; s < NSTREAMS; ++s) {
    size_t begin = (size_t)s * total / NSTREAMS;
    size_t end = (size_t)(s+1) * total / NSTREAMS;
    size_t count = end - begin;
    if (count == 0) continue;
    size_t bytes = count * sizeof(double);
    CUDA_CHECK(cudaMemcpyAsync(d_in+begin, h_in+begin, bytes,
                               cudaMemcpyHostToDevice, streams[s]));
    func_kernel<<<(count+255)/256, 256, 0, streams[s]>>>(
        d_in+begin, d_out+begin, count);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaMemcpyAsync(h_out+begin, d_out+begin, bytes,
                               cudaMemcpyDeviceToHost, streams[s]));
}
for (int s = 0; s < NSTREAMS; ++s)
    CUDA_CHECK(cudaStreamSynchronize(streams[s]));
// Check results, then release buffers after all their users have finished.
for (int s = 0; s < NSTREAMS; ++s)
    CUDA_CHECK(cudaStreamDestroy(streams[s]));
```

Les buffers sont alloués avant l’extrait ; définir `func_kernel` à partir du source manquant. Les bornes par quotient traitent aussi le reste si `total` n’est pas divisible par NSTREAMS.

**Q.5 - Faible gain ?** Plusieurs kernels ne garantissent pas le recouvrement : copies bloquantes, mémoire pageable, GPU saturé, petits morceaux et coût des lancements peuvent limiter le gain. Ne pas traiter le vecteur entier NSTREAMS fois, ce qui augmenterait le travail et pourrait créer des courses.

**Q.6-Q.7 - Copies et pinned.** `cudaMemcpyAsync` place la copie dans un stream. Pour permettre le recouvrement H2D/D2H usuel, allouer les buffers hôte avec `cudaMallocHost`, puis utiliser `cudaFreeHost`. Ne pas lire un résultat ou modifier une source avant la fin du transfert. Le matériel et les ressources disponibles conditionnent aussi le recouvrement.

**Q.8 - Synchronisme.** Kernel, `cudaMemcpyAsync`, `cudaEventRecord` sont normalement des soumissions asynchrones pour le CPU. `cudaDeviceSynchronize`, `cudaStreamSynchronize`, `cudaEventSynchronize` attendent leur périmètre. `cudaMemcpy` D2H rend les données disponibles avant le retour. Les allocations/libérations classiques peuvent introduire des synchronisations : les placer hors du pipeline. `cudaStreamDestroy` peut retourner avec du travail en vol ; ce n’est pas une attente de fin. La table binaire de l’ancien corrigé simplifie excessivement ces garanties.

**Q.9 - Graphe à deux streams.** Les flèches indiquent des contraintes, pas un temps mesuré :

```text
S0 : H2D [0,N[  --> K0 [0,N[  --> D2H [0,N[  ----+
                                                 +--> wait --> CPU check
S1 : H2D [N,2N[ --> K1 [N,2N[ --> D2H [N,2N[ ----+
```

Créations et allocations précèdent les soumissions. Une requête CPU précède l’opération GPU associée. Avec la notation du sujet, D2H $\Rightarrow$ fin de synchronisation. Les morceaux distincts n’imposent pas de dépendance entre les deux lignes ; le matériel peut pourtant les sérialiser.

### 4.14. Approfondissement - streams Q.10-Q.15 : mesurer la concurrence

**Q.10 - Programme.** Prendre `gettimeofday` avant les opérations mesurées, attendre tous les travaux après leur soumission, puis prendre le temps final. Sans attente, on mesure la soumission. Convertir `Δt=(sec_fin-sec_debut)+1e-6*(usec_fin-usec_debut)` et annoncer si allocations et transferts sont inclus. Hors contrainte du sujet, une horloge monotone évite les ajustements d’heure système.

**Q.11 - Tous les kernels seuls.** Effectuer les H2D, appeler `cudaDeviceSynchronize`, prendre t0, soumettre tous les kernels, appeler `cudaDeviceSynchronize`, prendre t1, puis effectuer les D2H. `t1-t0` est la durée globale de cette phase, pas la somme des durées individuelles.

**Q.12 - Inconvénient.** L’instrumentation sépare transferts et calcul en phases, supprimant leur recouvrement. Les kernels peuvent encore se recouvrir si tous sont soumis avant la seconde barrière ; toute concurrence ne disparaît donc pas nécessairement.

**Q.13 - Chaque kernel par horloge hôte.** Avec seulement `gettimeofday` et `cudaDeviceSynchronize`, isoler chaque kernel entre deux synchronisations. Les kernels deviennent successifs : la mesure modifie alors le comportement concurrent du programme.

**Q.14 - Événements.** Placer `start[s]` et `stop[s]` autour du kernel dans chaque stream s, attendre les événements finaux, calculer les durées. Ne pas les additionner pour obtenir la durée globale en présence de recouvrement. Pour mesurer l’enveloppe de tous les kernels à partir d’un début commun, utiliser un stream de coordination :

```text
Complete H2D before this kernel-only experiment.
Record global_start in coordination stream.
For every stream s:
    wait(global_start) in s
    record start[s] in s
    launch kernel[s] in s
    record stop[s] in s
For every stream s:
    wait(stop[s]) in coordination stream
Record global_stop in coordination stream.
Wait on global_stop at the host.
Elapsed(global_start,global_stop) = total kernel-phase duration.
Elapsed(start[s],stop[s]) = duration observed for kernel s.
```

Utiliser `cudaStreamWaitEvent` pour les attentes et `cudaEventElapsedTime` pour les durées. Le début commun ajoute une contrainte : annoncer une phase « kernels seuls ». Pour mesurer le pipeline réel, conserver son ordre et mesurer son temps complet séparément. Un kernel sous concurrence peut durer plus longtemps qu’un kernel isolé.

**Q.15 - GEMM multistream.** Découper A et C en paquets de lignes. Chaque stream transfère son A et son C initial si `β≠0`, calcule ses lignes, puis rapatrie son C. Tous les paquets utilisent **B entier** : le transférer une fois avant le pipeline et rendre cette disponibilité visible dans tous les streams. Adapter l’indice de ligne global ou passer des pointeurs décalés avec un nombre local de lignes ; conserver les gardes du kernel tuilé. Avec le kernel exact de 4.10, initialiser aussi C lorsque `beta=0`, ou modifier le calcul final pour qu’une branche `beta==0` écrive `alpha*sum` sans lire C ; sans cette adaptation, supprimer la copie de C laisserait une lecture de données non initialisées.

Comparer coalescence et tuilage à données et périmètres égaux. Accélérer les transferts ne garantit pas un gain lorsque le GPU est déjà saturé. Les chiffres P5000 du corrigé ne prédisent pas un résultat GH200. Aucun gain multistream n’a été exécuté ou confirmé ici.

**À refaire au tableau.** Parcours principal : indices, nombre de threads, répartition host/device, kernel avec bornes, C initial, rapport de surfaces pour π, chronométrage attendant le calcul et conversion ms/GFLOP/s. Approfondissement : deux barrières, dépendances de streams, projection SDF. Les performances et rendus absents des sources restent à mesurer, pas à inventer.
