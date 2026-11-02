## 5 Autoévaluation et rédaction pour le contrôle

### 5.1 Dix questions à faire sans regarder les réponses

Ces questions d’autotest suivent le cours ; ce ne sont pas d’anciens sujets. Écrire les réponses avant de consulter la section suivante.

1. Expliquer les relations entre grille, bloc, warp et SM. Un warp peut-il contenir des threads de deux blocs ?
2. Pour `N=1000` et `64` threads par bloc, combien faut-il de blocs ? Combien de threads sont lancés et combien ne modifient aucune donnée ?
3. Avec `gridDim=(2,2,2)`, `blockDim=(4,2,2)`, `blockIdx=(1,0,1)` et `threadIdx=(2,1,0)`, calculer l'indice unique en numérotant d'abord les blocs, puis leurs threads avec x le plus rapide.
4. Pour des matrices par lignes `A[M,K] * B[K,N] = C[M,N]`, un thread calcule `(row,col)`. Quels éléments des tableaux doit-il lire et écrire ?
5. Pourquoi faut-il synchroniser après le chargement d'une tuile en mémoire partagée ? Pourquoi faut-il généralement aussi synchroniser avant de la remplacer ?
6. Pourquoi `if (i < N) { __syncthreads(); }` peut-il être incorrect ?
7. Quel accès favorise généralement la coalescence : `a[base + tid]` ou `a[base + tid * stride]`, pour un grand `stride` ? Préciser les limites de la réponse.
8. Distinguer la soumission d'un kernel asynchrone par le CPU, sa fin sur le GPU et la disponibilité du résultat pour le CPU. `cudaStreamDestroy` remplace-t-il une attente explicite ?
9. Avec `512` blocs de `256` threads pour Monte Carlo, combien de résultats partiels faut-il ? Quel problème pose une séquence aléatoire identique pour tous les threads ?
10. Écrire les mappings OpenMP Target de `y[i] += alpha*x[i]` et expliquer comment vérifier le lieu d'exécution.

### 5.2 Réponses et raisonnement

1. Une grille contient des blocs, composés de threads ; les indices linéaires des threads d'un bloc définissent les warps. Un SM est une unité matérielle d'exécution des blocs. Un warp ne traverse pas deux blocs ; les indices de blocs n'imposent pas leur ordre d'exécution.
2. `ceil(1000/64)=16` blocs, soit `16*64=1024` threads lancés. Le test de bornes empêche `24` threads de modifier les données.
3. L'indice du bloc vaut `5`, le bloc contient `16` threads et l'indice local vaut `6`, donc `5*16+6=86`. Ce numéro n'est pas l'adresse obtenue en linéarisant les coordonnées spatiales globales.
4. Utiliser les indices ci-dessous. `k` parcourt le produit scalaire et le test de sortie est `row<M && col<N`.

```cpp
sum += A[row * K + k] * B[k * N + col];
C[row * N + col] = sum;
```

5. La première synchronisation rend disponibles les données chargées par les autres threads ; la seconde empêche un thread rapide de remplacer une tuile encore lue par un thread plus lent. Supprimer une barrière exige de prouver l'absence de la dépendance correspondante.
6. Dans un bloc de bord, certains threads peuvent entrer dans la condition et d'autres non. Une barrière de bloc impose une arrivée cohérente des participants ; charger zéro pour les éléments hors limites et faire passer ces threads par les barrières est une solution courante.
7. Le premier motif rapproche les adresses accédées par les lanes voisines et réduit généralement les transactions nécessaires. Leur nombre exact dépend aussi de la taille des éléments, de l'alignement, des lanes actives et du matériel.
8. Le retour du lancement permet à l'hôte de continuer les soumissions ; le résultat n'est utilisable qu'après la fin des calculs et transferts dont il dépend. Une attente sur le bon stream/événement ou une copie synchronisante appropriée établit cet ordre. Détruire un stream ne remplace pas l'attente du résultat par l'hôte.
9. `512*256=131072` résultats. Avec des `double`, il faut `131072*8=1048576` octets, soit `1 MiB`. Des séquences identiques répètent les échantillons et n'apportent pas le gain attendu de tirages indépendants ; des numéros de sequence distincts constituent le traitement de base dans le code du cours.
10. Utiliser `map(to: x[0:N]) map(tofrom: y[0:N])`. Appeler `omp_is_initial_device()` dans la région target pour vérifier le lieu d'exécution ; un résultat correct ne prouve pas à lui seul le succès de l'offload GPU.

### 5.3 Formules et unités

| Quantité | Formule et condition |
|---|---|
| Nombre de blocs 1D, `N>0` | $G=\lceil N/B\rceil$ ; code entier positif `(N+B-1)/B`, attention au débordement des très grands entiers |
| Threads par bloc | $B_x B_y B_z$ |
| Indice linéaire dans un bloc | $t=t_x+B_x(t_y+B_y t_z)$ |
| Indice linéaire d'un bloc | $b=b_x+G_x(b_y+G_y b_z)$ |
| Numéro global par blocs | $g=b(B_xB_yB_z)+t$ |
| Tableau 2D par lignes | $\mathrm{index}=row\cdot N+col$, avec $N$ colonnes |
| Terme principal d'un GEMM carré | $F\simeq 2N^3$ FLOP ; les termes d'ordre inférieur de $\alpha AB+\beta C$ sont distincts |
| Débit du kernel en GFLOP/s | $F/(t_{ms}\cdot10^6)$ |
| Accélération | $S=T_{CPU}/T_{GPU}$, pour des travaux et périmètres comparables |
| Monte Carlo | $\widehat\pi=4H/T$, avec $H$ succès pour $T$ échantillons |

La taille en octets est le nombre d'éléments multiplié par `sizeof(type)`. `cudaEventElapsedTime` renvoie des millisecondes. Distinguer GB et GiB, ainsi que GFLOP/s et TFLOP/s. Avec des échantillons uniformes indépendants, l'erreur statistique typique de Monte Carlo diminue comme l'inverse de la racine du nombre total d'échantillons ; chaque augmentation de ce nombre ne garantit pas une estimation plus proche de la valeur réelle.

### 5.4 Formulations utiles à l'écrit

| But de la phrase | Formulation possible |
|---|---|
| Annoncer la convention de stockage | On suppose que les matrices sont stockées par lignes. |
| Définir le travail d'un thread | Chaque thread calcule un élément de la matrice résultat. |
| Justifier le test de bornes | Le test de bornes empêche les threads excédentaires d'accéder hors du tableau. |
| Expliquer une barrière de bloc | La barrière garantit que les données chargées par le bloc sont disponibles avant leur utilisation. |
| Délimiter un chronométrage | Le temps mesuré couvre uniquement le kernel ; il exclut les transferts et les allocations. |
| Qualifier un résultat de performance | Ce gain dépend de la taille du problème et de la configuration mesurée. |
| Expliquer la coalescence | Des threads voisins accèdent à des adresses voisines, ce qui favorise la coalescence. |
| Indiquer la disponibilité du résultat | L'hôte attend la fin du transfert avant de lire le résultat. |

Avant de rendre la copie : vérifier les bornes, les divisions entières, la cohérence entre lignes, colonnes et leading dimensions, l'arrivée des participants aux barrières, l'attente effective dans le chronométrage et la conservation de la valeur initiale d'une sortie lue puis modifiée.
