## 3. API CUDA, contextes et programmation multi-GPU

Source principale : [CM3, PDF de 101 pages](../CM/APM_Cours3.pdf). Les diapositives mélangent explications historiques et exemples schématiques ; les précisions identifiées ci-dessous servent à éviter d'apprendre un comportement incorrect. La dernière diapositive décrit NCCL 2.19.3, sans constituer un inventaire de toutes les versions ultérieures.

### 3.1 Runtime API et Driver API

Source : CM3, p. 4-10.

| Point | Runtime API | Driver API |
|---|---|---|
| Niveau | Plus haut niveau, utilisé dans les premiers exemples | Contrôle plus explicite, utile pour certaines bibliothèques |
| Préfixe | `cuda` | `cu` |
| Allocation | `cudaMalloc` | `cuMemAlloc` |
| Copie | `cudaMemcpy` et sa direction | Par exemple `cuMemcpyHtoD`, `cuMemcpyDtoH` |
| Contexte | Gestion habituelle par le runtime | Gestion explicite possible |
| Type de retour | `cudaError_t` | `CUresult` |

Les deux API donnent accès au même GPU. Le Driver API n'est pas une promesse d'accélération : son intérêt est le contrôle des ressources et de leur contexte. Mélanger les deux demande de vérifier quel contexte est courant et à quel contexte appartiennent les objets utilisés.

### 3.2 Ce que représente un contexte

Source : CM3, p. 13-25.

Un contexte organise l'état CUDA associé à un GPU : allocations usuelles, espace d'adressage, streams, événements et autres ressources. Pour raisonner sur un pointeur, il faut connaître son allocation et les droits d'accès, pas seulement le numéro du GPU.

| Situation | Partage à retenir dans le modèle du cours |
|---|---|
| Plusieurs threads CPU, même processus, même contexte primaire | Les allocations du contexte sont partageables entre ces threads |
| Un processus, plusieurs GPU | Un contexte primaire par GPU utilisé |
| Plusieurs processus MPI, même GPU | Les processus n'obtiennent pas automatiquement le même espace d'adressage |
| Deux contextes explicites sur un même GPU | Le même GPU physique ne rend pas leurs allocations automatiquement interchangeables |

Le contexte primaire, présenté comme disponible depuis CUDA 4.0, est partagé par les threads d'un même processus ciblant ce GPU. Le contexte courant est une notion liée au thread hôte ; deux threads peuvent avoir des GPU courants différents.

**Précision sur la p. 22 :** l'affirmation selon laquelle seuls les contextes primaires resteraient disponibles ne doit pas être mémorisée comme règle actuelle. Le Driver API fournit toujours `cuCtxCreate`. Un contexte explicite n'est pas non plus intrinsèquement « privé pour toujours » à un thread : son association peut être manipulée. Voir la [gestion des contextes NVIDIA](https://docs.nvidia.com/cuda/cuda-driver-api/group__CUDA__CTX.html).

### 3.3 Choisir le GPU et vérifier les erreurs

Source : CM3, p. 28-38.

`cudaGetDeviceCount(&count)` renseigne le nombre de GPU visibles au processus. `cudaSetDevice(device)` sélectionne le GPU pour le thread hôte appelant ; les allocations, streams, événements et lancements suivants doivent être associés au GPU voulu.

```cpp
int count = 0;
cudaError_t status = cudaGetDeviceCount(&count);
if (status != cudaSuccess || count == 0) {
    return 1;
}
int device = local_rank % count;
status = cudaSetDevice(device);
if (status != cudaSuccess) {
    return 1;
}
```

Ce fragment suppose `local_rank` déjà défini. Le modulo n'est valide que si `count > 0`. L'affectation doit respecter les GPU réellement attribués et visibles, pas une numérotation physique supposée.

**Correction de la p. 36 :** un numéro invalide peut produire `cudaErrorInvalidDevice` ; il ne faut pas attendre un retour silencieux vers le GPU 0. Les p. 31-35 décrivent aussi une recherche de contextes historiques qui ne doit pas servir de contrat général : la documentation décrit `cudaSetDevice` comme liant le contexte primaire choisi au thread appelant. Voir [NVIDIA, gestion des devices](https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__DEVICE.html).

Changer de GPU courant ne déplace pas une allocation existante et ne termine pas automatiquement les travaux déjà soumis à l'autre GPU.

### 3.4 Manipuler les contextes avec le Driver API

Source : CM3, p. 39-49.

| Fonction | Effet à comprendre |
|---|---|
| `cuCtxCreate` | Crée un nouveau contexte et le rend courant ; ne cherche pas à réutiliser une allocation existante |
| `cuCtxGetCurrent` | Consulte le contexte courant sans le retirer |
| `cuCtxGetDevice` | Obtient le GPU du contexte courant |
| `cuCtxPushCurrent` | Rend un contexte courant en l'empilant sur le thread appelant |
| `cuCtxPopCurrent` | Retire le contexte courant et renvoie le contexte retiré |
| `cuCtxSetCurrent` | Associe explicitement un contexte au thread appelant |
| `cuCtxDestroy` | Détruit un contexte explicitement créé lorsque ses ressources ne sont plus utilisées |

Exemple de raisonnement : le thread utilise A ; il empile B ; les opérations qui utilisent le contexte courant visent B ; il dépile B et retrouve A. Le pointeur renvoyé par `cuCtxPopCurrent` désigne B, pas A. Deux appels de création visant le même GPU peuvent créer deux contextes distincts.

La signature de création à trois paramètres des diapositives dépend de la version de l'API ; il faut utiliser la signature du toolkit compilant le programme. Pour l'examen, maîtriser les effets des opérations et la propriété des ressources est plus utile que recopier un fragment incomplet. Les précisions de ce paragraphe et du tableau sont cohérentes avec la [documentation Driver API](https://docs.nvidia.com/cuda/cuda-driver-api/group__CUDA__CTX.html).

### 3.5 UVA et mémoire unifiée : deux notions différentes

Source : CM3, p. 51-62 ; mémoire unifiée dans CM2, p. 41-50.

UVA, présenté comme introduit avec CUDA 4.0, organise les adresses de l'hôte et des GPU dans un espace virtuel unifié sur les systèmes compatibles. Une adresse peut ainsi être associée à son allocation et à son emplacement, même si le GPU courant change.

| Notion | Ce qu'elle apporte | Ce qu'elle n'implique pas |
|---|---|---|
| UVA | Reconnaissance unifiée des adresses | Toutes les mémoires physiquement fusionnées |
| `cudaMemcpyDefault` | Déduction de la direction à partir des pointeurs dans un environnement UVA | Suppression de la copie |
| Mémoire unifiée, `cudaMallocManaged` | Gestion des accès et déplacements pour une allocation partagée CPU/GPU | Absence de migrations, de concurrence ou de synchronisation |
| Accès pair-à-pair | Accès à la mémoire d'un autre GPU lorsque supporté et autorisé | Garantie universelle donnée par UVA seule |

Un pointeur reconnaissable n'est pas nécessairement directement déréférençable par n'importe quel processeur. Conserver séparément les questions « où est l'allocation ? », « qui peut y accéder ? » et « quand ses données sont-elles prêtes ? ».

Les fragments des p. 51-59 utilisent une écriture abrégée de `cudaMemcpy`. Dans un vrai appel, passer le pointeur de données `d_a`, pas l'adresse de la variable `&d_a`.

### 3.6 Accès P2P et transferts entre GPU

Complément de clarification lié à UVA ; cette procédure n'est pas développée comme telle dans CM3. Elle distingue l'identification d'une adresse et l'autorisation d'y accéder.

```cpp
int canAccess = 0;
cudaDeviceCanAccessPeer(&canAccess, 0, 1);
if (canAccess) {
    cudaSetDevice(0);
    cudaDeviceEnablePeerAccess(1, 0);
}
```

Ce fragment demande si GPU 0 peut accéder à GPU 1, puis active ce sens depuis GPU 0 ; il n'active pas automatiquement le sens inverse. Il suppose des identifiants valides et omet les contrôles d'erreurs pour montrer le mécanisme.

`cudaMemcpyPeer` ou `cudaMemcpyPeerAsync` expriment un transfert entre allocations de deux GPU. Le trajet efficace dépend de la topologie et des capacités disponibles. P2P ne signifie ni « la donnée est déjà arrivée » ni « tous les accès distants ont le coût d'un accès local ». Il faut encore ordonner production, copie et consommation. Référence : [NVIDIA, accès à la mémoire d'un device pair](https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__PEER.html).

### 3.7 MPI et affectation des GPU

Source : CM3, p. 64-69.

Si tous les processus utilisent le GPU par défaut, ils peuvent tous charger GPU 0. Faire le même `cudaSetDevice(1)` dans tous les processus ne répartit pas davantage le travail. Le cours propose une distribution cyclique :

$$
\operatorname{device}(r)=r\bmod N_{\mathrm{GPU}}.
$$

Sur un seul nœud, ce choix répartit les rangs entre les GPU visibles. En multi-nœud, raisonner avec le rang local au nœud et la visibilité des GPU attribués : le rang MPI global ne décrit pas à lui seul le placement local. Si chaque processus ne voit qu'un GPU qui lui a été réservé, ce GPU peut avoir l'indice local 0 dans chaque processus.

La distribution cyclique n'équilibre pas nécessairement le coût : les rangs peuvent avoir des volumes de calcul différents. Elle ne garantit pas non plus le meilleur placement NUMA entre CPU, mémoire hôte, GPU et interface réseau.

Les processus MPI ont des espaces d'adressage distincts. Envoyer la valeur brute d'un pointeur ou d'un handle de contexte ne partage pas l'allocation. Les échanges demandent un mécanisme prévu pour cela : communications, prise en charge de buffers GPU par une implémentation MPI adaptée, ou mécanisme interprocessus explicite. Ces possibilités n'impliquent pas que tout MPI accepte directement un pointeur GPU.

### 3.8 OpenMP côté hôte et partage du contexte primaire

Source : CM3, p. 71-75. Il s'agit ici de threads CPU OpenMP qui appellent CUDA ; l'offload OpenMP `target` est un autre mécanisme.

```cpp
#pragma omp parallel
{
    int tid = omp_get_thread_num();
    int device = tid % gpuCount;
    cudaSetDevice(device);
    cudaStream_t stream;
    cudaStreamCreate(&stream);
    kernel<<<grid, block, 0, stream>>>(buffers[device]);
    cudaStreamSynchronize(stream);
    cudaStreamDestroy(stream);
}
```

Ce schéma suppose `gpuCount > 0`, un buffer correct par GPU, et des travaux compatibles entre eux. Si plusieurs threads écrivent le même buffer, il faut répartir leurs régions ou ajouter une synchronisation ; partager le contexte ne rend pas les écritures concurrentes correctes.

Chaque thread hôte doit choisir son GPU avant ses appels CUDA. Des threads d'un même processus utilisant le même contexte primaire peuvent manipuler les mêmes allocations. Créer au contraire un contexte explicite indépendant à chaque passage peut rendre un pointeur précédent inutilisable dans le contexte courant.

Les streams ordonnent le travail GPU ; les mécanismes OpenMP ordonnent aussi les échanges et accès du côté CPU. Ces deux niveaux de synchronisation ne sont pas interchangeables.

### 3.9 MPI + OpenMP + CUDA : organisation et topologie

Source : CM3, p. 76-82.

Le cours présente un processus MPI par GPU, avec plusieurs threads hôtes et des streams, comme une organisation favorable au partage des allocations et au recouvrement. C'est un modèle de départ, pas une preuve que cette configuration maximise tous les programmes.

Les p. 78-80 doivent être lues avec précaution : les nombres 16 ou 128 ne sont pas une limite universelle du nombre de streams créables, et `cudaMalloc(..., stream)` n'est pas la signature de `cudaMalloc`. Dans les exemples étudiés, le stream se fournit au lancement du noyau ou à `cudaMemcpyAsync`.

Pour évaluer un placement, suivre le trajet des données : cœur CPU → mémoire NUMA → GPU → autre GPU ou réseau. Un GPU proche de certains cœurs peut être éloigné d'autres ; le meilleur placement GPU peut concurrencer le meilleur placement CPU. Une bibliothèque externe peut aussi modifier le device ou le contexte courant : ne pas supposer que cet état reste inchangé après tout appel.

### 3.10 NCCL : communicateurs, rangs et initialisation

Source : CM3, p. 84-92.

NCCL fournit des communications entre GPU. Une « clique » désigne ici les GPU participant à un communicateur ; elle peut ne couvrir qu'un sous-ensemble. Il faut distinguer trois numéros : rang MPI, identifiant CUDA local du device et rang dans le communicateur NCCL.

| Fonction | Organisation |
|---|---|
| `ncclGetUniqueId` | Crée l'identifiant commun à distribuer aux participants |
| `ncclCommInitRank` | Chaque participant initialise son rang, après avoir choisi son GPU |
| `ncclCommInitAll` | Un seul processus initialise un ensemble de GPU locaux à partir de `devList` |

Avec `devList = {0, 3, 1, 5}`, les rangs NCCL 0, 1, 2, 3 correspondent respectivement aux GPU locaux 0, 3, 1, 5. Le dernier argument de `ncclCommInitRank` est le rang NCCL unique dans `0..nranks-1`, pas nécessairement le numéro du GPU ; cela corrige l'ambiguïté de la p. 90.

Les participants utilisent le même identifiant. En MPI, un processus le crée puis le diffuse, par exemple avec `MPI_Bcast`. L'initialisation peut attendre les autres participants : les appels doivent être coordonnés, sur plusieurs threads/processus ou avec des appels groupés si un thread gère plusieurs GPU.

Dans le modèle étudié, un GPU ne doit pas représenter plusieurs rangs du même communicateur. Plusieurs threads associés au même GPU doivent donc désigner le participant qui réalise l'initialisation, conformément à la p. 90. Voir aussi [NCCL, création d'un communicateur](https://docs.nvidia.com/deeplearning/nccl/user-guide/docs/usage/communicators.html).

Ces distinctions, notamment la portée mono-processus de `ncclCommInitAll`, sont vérifiées dans la [documentation officielle des communicateurs NCCL](https://docs.nvidia.com/deeplearning/nccl/user-guide/docs/api/comms.html). Un handle créé dans un processus ne devient pas utilisable dans les autres en diffusant seulement sa valeur.

### 3.11 Collectives, AllReduce et exécution asynchrone

Source : CM3, p. 93-100.

| Opération | Résultat attendu |
|---|---|
| Broadcast | Une donnée du rang racine est envoyée à tous |
| Reduce | Les contributions sont combinées et le résultat est placé à la racine |
| AllReduce | Les contributions sont combinées et chaque participant reçoit le résultat |
| AllGather | Chaque participant reçoit les contributions de tous |
| ReduceScatter | Les contributions sont combinées puis le résultat est réparti par morceaux |

Pour une somme sur `P` participants, le résultat reçu par chacun est :

$$
y_j=\sum_{r=0}^{P-1}x_{r,j}.
$$

`ncclAllReduce(sendbuff, recvbuff, count, datatype, op, comm, stream)` utilise des buffers GPU ; `count` compte les éléments, pas les octets. Les participants doivent appeler des opérations compatibles, dans le même ordre collectif. Les pointeurs locaux peuvent être différents : « mêmes paramètres » ne veut pas dire « mêmes adresses numériques dans tous les processus ».

L'opération est soumise dans un stream. La fin de l'appel hôte ne suffit pas à autoriser la lecture immédiate du résultat par le CPU. Les dépendances du stream ou une attente appropriée doivent protéger le consommateur.

Quand un seul thread gère plusieurs GPU, le simple `for` des diapositives doit être complété par la sémantique de groupe :

```cpp
ncclGroupStart();
for (int i = 0; i < nLocalGPUs; ++i) {
    ncclAllReduce(send[i], recv[i], count, ncclFloat,
                  ncclSum, comms[i], streams[i]);
}
ncclGroupEnd();
```

Les communicateurs, buffers et streams sont supposés déjà initialisés. Attendre les streams après `ncclGroupEnd`, pas au milieu du groupe. Cette précision évite qu'un premier appel attende un autre participant encore non soumis ; voir [NCCL, appels groupés](https://docs.nvidia.com/deeplearning/nccl/user-guide/docs/usage/groups.html).

### 3.12 Points de vigilance pour le partiel

Source : CM3, notamment p. 22, 36, 78-80, 84, 90 et 101.

1. **Même GPU ne veut pas dire même contexte.** Vérifier processus, contexte courant et allocation.
2. **UVA ne veut pas dire mémoire unifiée.** Identifier séparément adressage, accès autorisé et mouvement des données.
3. **Même contexte ne veut pas dire absence de concurrence.** Les lectures/écritures ont encore besoin d'un ordre correct.
4. **Changer de device ne déplace pas les données.** Conserver les informations d'appartenance des buffers, streams et événements.
5. **Rang NCCL, rang MPI et device CUDA peuvent différer.** Faire un tableau explicite avant de corriger un programme.
6. **Asynchrone ne veut pas dire terminé.** Relier production, communication et consommation avec streams/événements/attentes.

La p. 84 présente InfiniBand pour le multi-nœud, tandis que la p. 101, explicitement consacrée à NCCL 2.19.3, mentionne aussi RoCE et les sockets IP. Il ne faut donc pas apprendre « NCCL multi-nœud nécessite obligatoirement InfiniBand ». Cette dernière page répertorie les collectives, les échanges point-à-point et des motifs pouvant être construits avec ces échanges ; elle ne signifie pas que chaque motif est une API collective distincte.

Les exemples du chapitre sont des supports de raisonnement, pas des programmes exécutés ni des mesures de scalabilité. Pour une question de performance, il faut aussi examiner quantité de données, fréquence des communications, déséquilibre du calcul et topologie.
