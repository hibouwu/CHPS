## 2. CUDA avancé : mémoire, exécution et synchronisation

Ce chapitre correspond au [CM2](../CM/APM_Cours2.pdf).

### 2.1 Attributs de fonctions et structure d'un noyau (CM2, p. 3-7)

| Déclaration | Lieu d'exécution | Usage dans le cours |
|---|---|---|
| `__host__` ou aucun attribut | CPU | Fonction appelée par le programme hôte |
| `__device__` | GPU | Fonction auxiliaire appelée par du code GPU |
| `__global__` | GPU | Noyau lancé depuis l'hôte avec `<<<...>>>` |
| `__host__ __device__` | CPU ou GPU | Deux versions compilées selon le lieu d'appel |

Un appel ordinaire à une fonction `__device__` ne lance pas une nouvelle grille. Un noyau `__global__` retourne `void` ; il produit ses résultats en écrivant dans les buffers transmis. Son lancement est asynchrone par rapport au CPU. Les restrictions historiques de la p. 7 doivent être lues dans le modèle de programmation utilisé en cours, sans en faire une liste universelle pour toutes les versions de CUDA.

```cpp
__global__ void vecAdd(const double *a, const double *b,
                       double *c, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        c[i] = a[i] + b[i];
    }
}
```

Le test `i < n` protège le dernier bloc lorsque la taille du problème n'est pas un multiple de la taille du bloc. Il ne doit pas être supprimé simplement pour éviter un branchement.

### 2.2 Indices, types vectoriels et numérotation des warps (CM2, p. 8-9 et 53)

| Objet | Signification |
|---|---|
| `threadIdx.x/y/z` | Coordonnées du thread dans son bloc |
| `blockIdx.x/y/z` | Coordonnées du bloc dans la grille |
| `blockDim.x/y/z` | Dimensions d'un bloc |
| `gridDim.x/y/z` | Dimensions de la grille |
| `dim3` | Type de dimensions dont les composantes omises valent 1 |
| `int2`, `float4`, `make_int2(x, y)` | Types vectoriels et fonction de construction |

L'ordre linéaire des threads d'un bloc fait varier `x` en premier, puis `y`, puis `z`. Un warp regroupe 32 indices linéaires consécutifs.

$$
t=x+D_x(y+D_y z),\qquad w=\lfloor t/32\rfloor,\qquad \ell=t\bmod32.
$$

Pour `blockDim = (4, 4, 2)`, on obtient `t = x + 4y + 16z` : `(3,1,0)` donne 7 et `(0,0,1)` donne 16. Le bloc comporte 32 threads, soit un warp. La mention « tid (global) » du schéma de la p. 53 représente ici un indice dans le bloc, sans terme `blockIdx` ; la formule permet de lever les ambiguïtés de ses coordonnées dessinées.

Les types vectoriels imposent des règles d'alignement. Écrire `float4` ne garantit ni une instruction arithmétique vectorielle ni un gain de temps ; il faut que l'accès, l'alignement et le code produit s'y prêtent. La p. 8 ajoute un exemple de lecture vectorisée.

### 2.3 Hiérarchie mémoire : portée et durée de vie (CM2, p. 11-19 et 55-58)

| Espace | Visible par | Durée/usage à retenir |
|---|---|---|
| Registres | Un thread | Variables privées ; ressource limitée sur le SM |
| Mémoire locale | Un thread | Tableaux privés ou débordements de registres ; « locale » ne signifie pas mémoire rapide sur puce |
| Mémoire partagée, `__shared__` | Threads d'un même bloc | Une instance par bloc, jusqu'à la fin du bloc |
| Mémoire globale | Threads ayant accès à l'allocation | Grands tableaux ; allocation et libération explicites |
| Mémoire constante, `__constant__` | Lecture par le GPU | Données mises à jour depuis l'hôte ; lecture commune favorable |
| Texture / cache de lecture seule | Lectures selon le mécanisme utilisé | Chemin de lecture et règles spécifiques ; ne remplace pas la synchronisation |

Deux blocs résidant sur le même SM ne partagent pas automatiquement leur tableau `__shared__`. La grille et les blocs sont des objets logiciels ; un SM est une ressource matérielle. Une variable locale simple peut être placée dans un registre, mais cette localisation n'est pas garantie pour toutes les variables.

La mémoire constante est intéressante quand les threads d'un warp lisent la même adresse ; des adresses différentes peuvent réduire cet avantage. Les tailles de caches et leurs relations physiques avec la mémoire partagée dépendent de l'architecture.

### 2.4 Allocation et copies : taille en octets et propriété du pointeur (CM2, p. 20-24 et 30-33)

```cpp
double *d_a = nullptr;
size_t bytes = n * sizeof(double);
cudaMalloc((void **)&d_a, bytes);
cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice);
cudaMemcpy(h_a, d_a, bytes, cudaMemcpyDeviceToHost);
cudaFree(d_a);
```

`cudaMalloc` reçoit l'adresse de la variable pointeur pour y écrire l'adresse de l'allocation. `cudaMemcpy` reçoit les adresses des données : `d_a`, et non `&d_a`. `count` est un nombre d'octets. Les quatre directions présentées sont `cudaMemcpyHostToDevice`, `cudaMemcpyDeviceToHost`, `cudaMemcpyHostToHost` et `cudaMemcpyDeviceToDevice`.

Dans le modèle de mémoire séparée du cours, un pointeur obtenu par `cudaMalloc` ne peut pas être déréférencé par une boucle CPU ordinaire. Conserver les données sur le GPU entre plusieurs calculs réduit les transferts inutiles.

### 2.5 Allocation 2D/3D et pitch (CM2, p. 25-40)

`cudaMallocPitch(&ptr, &pitch, width, height)` alloue des lignes alignées. `width` est la largeur utile en octets ; `pitch` est la distance réelle en octets entre deux débuts de ligne, padding inclus. `height` compte les lignes. Le pitch n'est ni le nombre d'éléments ni la seule taille du padding.

```cpp
float *d_a = nullptr;
size_t pitch = 0;
size_t widthBytes = width * sizeof(float);
cudaMallocPitch((void **)&d_a, &pitch, widthBytes, height);
cudaMemcpy2D(d_a, pitch, h_a, widthBytes,
             widthBytes, height, cudaMemcpyHostToDevice);
```

Dans un noyau, l'adresse de la ligne `row` s'obtient en effectuant d'abord le décalage en octets :

```cpp
float *line = (float *)((char *)d_a + row * pitch);
float value = line[col];
```

Exemple : 100 `float` occupent 400 octets utiles. Si le pitch retourné vaut 512 octets, la ligne suivante commence à `base + 512`, et non `base + 400`. La valeur 512 est un exemple, pas une règle matérielle.

`cudaMemcpy2D` accepte un pitch source et un pitch destination distincts ; il copie seulement la largeur utile sur le nombre de lignes demandé. Pour la copie retour, le buffer hôte compact conserve son propre pitch de 400 octets dans cet exemple.

En 3D, `cudaMalloc3D` utilise `cudaExtent` et retourne un `cudaPitchedPtr` ; pour une allocation linéaire, la largeur est en octets. Le pas d'une tranche se déduit du pitch de ligne et de la hauteur stockée. `cudaMemcpy3D` regroupe positions, pointeurs ou tableaux CUDA, étendue et direction dans `cudaMemcpy3DParms`. Les `cudaArray` sont des objets spécialisés ; ils ne se manipulent pas comme un simple tableau C.

### 2.6 Mémoire unifiée et coût des migrations (CM2, p. 41-50)

La mémoire unifiée, introduite dans le cours avec CUDA 6.0, permet d'utiliser un même pointeur avec l'hôte et le GPU via `cudaMallocManaged` ou une variable `__managed__`. Le système gère l'accès et, selon la plateforme, les déplacements des données. Cela réduit la gestion manuelle, pas nécessairement le coût des transferts.

```cpp
int *a = nullptr;
cudaMallocManaged((void **)&a, n * sizeof(int));
kernel<<<grid, block>>>(a);
cudaDeviceSynchronize();
consume_on_cpu(a);
cudaFree(a);
```

`cudaMemAttachGlobal` et `cudaMemAttachHost` expriment des règles d'association et d'accès ; ils ne signifient pas simplement « allouer physiquement sur GPU » ou « allouer physiquement sur CPU ». Le CPU doit attendre la fin du calcul avant de lire son résultat.

Les p. 46-50 comparent une alternance répétée GPU → CPU sur le même tableau à des phases regroupées. Le ping-pong peut provoquer des migrations répétées. Regrouper les accès est intéressant uniquement si les dépendances du programme autorisent ce changement d'ordre ; si chaque étape CPU prépare l'entrée GPU suivante, on ne peut pas déplacer toutes les étapes CPU à la fin.

### 2.7 Coalescence des accès globaux (CM2, p. 51-54)

Pour analyser un chargement, écrire l'adresse lue par chaque thread d'un même warp lors de la même instruction. Des adresses proches et bien alignées demandent généralement moins de transactions que des adresses dispersées. La contiguïté entre les accès successifs d'un seul thread ne suffit pas.

Pour une matrice en ordre des lignes :

$$
\operatorname{addr}(r,c)=\operatorname{base}+(rN+c)\,s.
$$

`N` est le nombre de colonnes et `s` la taille d'un élément. Si les threads voisins font varier `c`, l'écart vaut `s`. S'ils font varier `r`, l'écart vaut `Ns`. Le premier cas favorise la coalescence ; le second peut disperser les transactions.

Les p. 52-53 citent 128 octets, des paquets de 32 octets et jusqu'à deux instructions par ordonnanceur. Ce sont les indications de la diapositive, pas des constantes universelles pour tous les GPU. Le nombre exact de transactions dépend notamment de l'architecture, de la largeur d'accès et de l'alignement.

La mémoire partagée permet de charger une tuile avec des accès globaux coalescés, puis de réutiliser ou réorganiser les données dans le bloc. Charger des éléments supplémentaires peut être utile, mais doit se justifier par une réduction du coût total.

### 2.8 Mémoire partagée et conflits de banques (CM2, p. 54-58 et 98)

Un conflit se produit lorsque plusieurs accès d'une même opération doivent utiliser une même banque pour des adresses distinctes, ce qui peut sérialiser le service. Il faut distinguer ce problème de la coalescence en mémoire globale.

Sous l'hypothèse simplifiée de 32 banques et de mots de 4 octets :

$$
\operatorname{bank}(a)=\left\lfloor a/4\right\rfloor\bmod32.
$$

Pour `float tile[32][32]`, lire une colonne avec `tile[threadIdx.x][col]` donne un pas de 32 mots : toutes les adresses tombent sur la même banque dans ce modèle. Un padding `float tile[32][33]` change le pas et répartit ces accès. Les accès au même mot peuvent bénéficier d'une diffusion ; il ne faut pas les confondre avec des accès à des mots différents d'une banque.

La mémoire partagée dynamique se déclare avec `extern __shared__`. Sa taille est le troisième paramètre du lancement. Si plusieurs tableaux utilisent la même zone, leurs offsets doivent éviter tout chevauchement et respecter l'alignement de chaque type.

### 2.9 Registres, occupation et divergence (CM2, p. 59-60 et 98)

Les registres d'un SM sont répartis entre ses threads résidents. Plus un thread consomme de registres, moins il peut rester de place pour d'autres blocs. La mémoire partagée par bloc, le nombre de threads et les limites matérielles de blocs/warps peuvent également limiter la résidence.

$$
\mathrm{occupancy}=W_{\mathrm{resident}}/W_{\max}.
$$

`W_resident` compte les warps résidents et `W_max` le maximum de warps résidents du SM. Un modèle simplifié donne une borne, avant prise en compte des granularités d'allocation :

$$
B_{\mathrm{resident}}\leq\min\left(B_{\max},\left\lfloor T_{\max}/T_b\right\rfloor,\left\lfloor R_{\mathrm{SM}}/(rT_b)\right\rfloor,\left\lfloor S_{\mathrm{SM}}/S_b\right\rfloor\right).
$$

`T_b` est le nombre de threads par bloc, `r` les registres par thread, `S_b` la mémoire partagée par bloc ; le terme partagé est omis si `S_b = 0`. Cette borne n'est pas un prédicteur complet du temps d'exécution.

`--maxrregcount=N` limite les registres ; `__launch_bounds__(maxThreadsPerBlock, minBlocksPerMultiprocessor)` informe le compilateur sur la configuration visée. Réduire excessivement les registres peut provoquer des débordements en mémoire locale. Une occupation supérieure ne garantit pas un noyau plus rapide.

La divergence concerne les chemins suivis par les threads d'un même warp. Des chemins différents peuvent diminuer l'utilisation des unités. Des warps différents peuvent suivre des branches différentes sans créer ce même phénomène. Le but est de réduire la divergence coûteuse, pas d'interdire tous les `if`.

### 2.10 Barrières, visibilité, `volatile` et opérations atomiques (CM2, p. 57, 90 et 93)

| Outil | Garantie/usage | Ce qu'il ne remplace pas |
|---|---|---|
| `__syncthreads()` | Rendez-vous du bloc et visibilité des écritures globales/partagées précédentes concernées | Barrière de toute la grille |
| `__syncthreads_count/and/or` | Barrière avec résultat collectif sur un prédicat | Synchronisation entre blocs |
| `atomicAdd`, `atomicExch`, `atomicCAS`, etc. | Mise à jour atomique de la cible selon le type et la portée supportés | Ordre général de toutes les opérations mémoire |
| `volatile` | Contraintes sur les accès du compilateur | Atomicité, rendez-vous ou protocole de synchronisation |

Les threads d'un bloc doivent rencontrer les barrières selon un contrôle cohérent. Dans un traitement par tuiles, les threads hors limites peuvent charger zéro, puis participer à la même barrière que les autres. Une barrière placée uniquement dans `if (i < n)` devient incorrecte si ce test varie entre les threads du bloc.

**Précision sur la p. 57 :** qualifier un tableau de `volatile` ne répare pas une lecture/écriture concurrente sans synchronisation. Une fence ordonne certains accès mais n'attend pas à elle seule que tous les threads arrivent. Cette distinction est confirmée dans la [documentation NVIDIA sur `volatile`](https://docs.nvidia.com/cuda/cuda-programming-guide/05-appendices/cpp-language-support.html).

`a[i]++` comprend une lecture, une addition et une écriture ; plusieurs threads peuvent perdre des incréments. `atomicAdd(&a[i], 1)` protège cette mise à jour, mais une forte contention sur une adresse peut coûter cher. Réduire localement puis combiner moins de résultats atomiques est une piste, sous réserve de l'ordre d'arrondi acceptable en flottant. Les types et largeurs supportés dépendent de la compute capability.

### 2.11 Asynchronisme, streams et mémoire hôte verrouillée (CM2, p. 62-89)

Un lancement asynchrone rend la main au CPU avant la fin du travail GPU. Dans un même stream, les opérations restent ordonnées : copie d'entrée → noyau A → noyau B → copie de sortie. Cette propriété vient de l'ordre du stream ; CUDA n'analyse pas les pointeurs pour découvrir arbitrairement les dépendances entre streams.

| API | Usage |
|---|---|
| `cudaStreamCreate/Destroy` | Créer/libérer un stream |
| `cudaMemcpyAsync(..., stream)` | Soumettre une copie dans ce stream |
| `kernel<<<grid, block, sharedBytes, stream>>>(...)` | Soumettre un noyau dans ce stream |
| `cudaStreamSynchronize(stream)` | Attendre ce stream depuis le CPU |
| `cudaDeviceSynchronize()` | Attendre les travaux précédents du contexte courant sur ce GPU |
| `cudaStreamWaitEvent(stream, event, 0)` | Établir une dépendance dans un stream sans attente active du CPU |

Les streams distincts permettent le recouvrement de travaux indépendants si le matériel et les ressources le permettent. Deux streams ne garantissent pas deux noyaux simultanés. Le stream par défaut peut imposer des dépendances suivant son mode ; pour raisonner clairement, utiliser des streams explicites et nommer les dépendances.

```cpp
cudaMemcpyAsync(d_a, h_a, bytes, cudaMemcpyHostToDevice, copyStream);
cudaEventRecord(ready, copyStream);
cudaStreamWaitEvent(computeStream, ready, 0);
kernel<<<grid, block, 0, computeStream>>>(d_a);
```

Ce fragment suppose les streams, l'événement et les buffers déjà créés. Il corrige l'ambiguïté des p. 87-88 si le noyau consomme le buffer copié. L'API correcte est `cudaMemcpyAsync`, et l'équivalent 2D est `cudaMemcpy2DAsync` ; `cudaMemCpy` et `cudaMemcpyPitchAsync` ne sont pas les noms à recopier.

Pour les transferts hôte-GPU réellement asynchrones et leur recouvrement, utiliser une mémoire hôte page-locked, par exemple `cudaMallocHost` puis `cudaFreeHost`. La mémoire pageable peut entraîner une étape intermédiaire ou un blocage. Ne pas modifier/libérer la source H→D avant la fin de la copie ; ne pas lire/réutiliser la destination D→H avant sa fin. Le verrouillage des pages et l'attente de fin répondent à deux besoins différents.

### 2.12 Événements et mesure du temps (CM2, p. 95)

```cpp
cudaEvent_t start, stop;
cudaEventCreate(&start);
cudaEventCreate(&stop);
cudaEventRecord(start, stream);
kernel<<<grid, block, 0, stream>>>(d_a);
cudaEventRecord(stop, stream);
cudaEventSynchronize(stop);
float milliseconds = 0.0f;
cudaEventElapsedTime(&milliseconds, start, stop);
cudaEventDestroy(start);
cudaEventDestroy(stop);
```

Les événements encadrent un intervalle dans le stream ; `cudaEventElapsedTime` écrit une durée en millisecondes. Attendre `stop` garantit que cet intervalle est terminé avant la lecture. Les appels ci-dessus constituent un schéma pédagogique, avec vérification des erreurs omise pour la lisibilité.

Un chronomètre CPU placé seulement autour de `<<<...>>>` mesure surtout la soumission. Pour mesurer tout le calcul depuis le CPU, attendre sa fin avant le second relevé. Toujours préciser le périmètre : noyau seul ou application, transferts inclus ou exclus, première initialisation et préchauffage inclus ou exclus. Aucun résultat de performance n'est produit par ce dossier.

### 2.13 Erreurs, fonctions mathématiques et débogage (CM2, p. 92-97)

Vérifier le `cudaError_t` des fonctions CUDA et utiliser `cudaGetErrorString` pour le message. Après un lancement, `cudaGetLastError()` permet de détecter une erreur de lancement ; vérifier aussi la synchronisation suivante pour une erreur d'exécution asynchrone. Un lancement accepté ne prouve ni l'absence d'accès hors limites ni la justesse numérique.

`printf` sur GPU est exécuté par les threads qui atteignent l'instruction. Il peut produire beaucoup de sorties et perturber le temps mesuré. Une synchronisation ajoutée pour localiser une erreur doit être réévaluée avant le chronométrage final.

Les fonctions mathématiques optimisées et `--use_fast_math` peuvent améliorer certains calculs en simple précision, au prix de changements numériques. Ce drapeau ne signifie pas « toutes les opérations en double précision sont accélérées sans modification du résultat ».

### 2.14 Méthode de réponse et ordre des optimisations (CM2, p. 98)

Application aux exercices : section 4.

1. Identifier le travail d'un thread et vérifier les limites des indices.
2. Réduire les transferts CPU-GPU et conserver les données réutilisées sur le GPU.
3. Fournir assez de blocs pour occuper les SM, sans transformer « au moins un bloc par SM » en formule d'optimalité.
4. Examiner les adresses d'un warp : coalescence globale puis éventuels conflits de banques.
5. Réutiliser les données avec la mémoire partagée si cela réduit le coût total ; placer les barrières nécessaires.
6. Examiner les registres, la mémoire partagée, l'occupation et les branches ; comparer ensuite des temps sur un périmètre identique.

Des blocs multiples de 32 constituent un point de départ fréquent. Leur taille ne se choisit pas uniquement à partir du nombre de cœurs. Le détail des optimisations DGEMM, du déroulage de boucles et du tiling reste dans les exercices concernés ; leur place dans le calendrier est précisée dans la section 4.

Pour expliquer une accélération, relier une modification à sa cause : moins d'octets transférés, moins de transactions, plus de réutilisation ou un meilleur recouvrement. Ne pas déduire un gain mesuré de la seule présence de `__shared__`, d'un stream supplémentaire ou d'une occupation plus élevée.
