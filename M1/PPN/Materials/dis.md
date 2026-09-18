# Travail de projet ce mois

## 1 Parallélisme de données synchrone par mini-batch avec `MPI_Allreduce`

### 1.1 Baseline `non-overlap, non-bucketed`

L'entraînement distribué repose sur un schéma classique de parallélisme de données synchrone avec MPI. Chaque processus MPI, c'est-à-dire chaque `rang`, maintient une réplique complète du modèle. Côté données, chaque rang appelle `dataset->load()`, charge le jeu de données localement, puis construit une partition logique à partir de son `rang` et de `world_size` via `makeShard(...)`. Chaque rang n'entraîne donc le modèle que sur son shard local, tout en conservant une copie complète des paramètres.

Soit $B_r$ la taille du mini-batch local traité par le rang $r$ à une étape donnée, et $g_r$ la somme locale des gradients calculés à partir de ce mini-batch. Une fois la rétropropagation locale terminée, une opération `Allreduce` effectue la somme globale des gradients :
$$
g_{\mathrm{sum}}=\sum_{r=0}^{\mathrm{world\_size}-1} g_r
$$
Les tailles de mini-batch locales sont également additionnées afin d'obtenir la taille globale du batch :
$$
B_{\mathrm{global}}=\sum_{r=0}^{\mathrm{world\_size}-1} B_r
$$
Le gradient moyen global utilisé pour mettre à jour les paramètres est alors :
$$
g_{\mathrm{global}}=\frac{1}{B_{\mathrm{global}}}g_{\mathrm{sum}}
=\frac{1}{B_{\mathrm{global}}}\sum_{r=0}^{\mathrm{world\_size}-1} g_r
$$

Chaque rang applique ensuite la même mise à jour sur sa réplique du modèle :
$$
\theta \leftarrow \theta-\eta\, g_{\mathrm{global}}
$$
où $\theta$ désigne les paramètres du modèle et $\eta$ le taux d'apprentissage. Comme tous les rangs utilisent le même gradient agrégé, les paramètres restent identiques sur l'ensemble des processus. Dans la baseline actuelle, la synchronisation est bloquante et effectuée paramètre par paramètre via `MPI_Allreduce`. Dans le code, ce mode correspond à `Grad Sync Mode = per_param`.

### 1.2 Optimisation 1 — Gradient bucketing

La première optimisation consiste à remplacer la synchronisation paramètre par paramètre par une synchronisation par `bucket`. Plusieurs gradients sont regroupés dans un buffer contigu avant de lancer la collective MPI. Cela réduit le nombre d'appels à `MPI_Allreduce`, amortit le coût des petites réductions et fournit une granularité de communication plus réaliste.

Concrètement, un `BucketManager` construit une partition statique des paramètres entraînables selon leur ordre dans `trainable_params_`. Il associe ensuite à chaque paramètre un `bucket`, un offset et une longueur dans un buffer contigu. Un paramètre ne peut pas être coupé sur plusieurs `bucket`, et un très gros paramètre occupe à lui seul un `bucket`. Le même `BucketManager` est utilisé dans les modes `bucketed` et `overlap_bucketed`, ce qui garantit une représentation identique des buckets, de l'ordre des paramètres et de la logique `pack/unpack`.

Dans le mode `non-overlap, bucketed`, la communication reste déclenchée à la fin du backward, mais elle s'effectue bucket par bucket : les gradients sont copiés dans les buffers de `bucket`, chaque `bucket` est réduit via `MPI_Allreduce`, puis les résultats sont recopiés dans les gradients des paramètres. Cette optimisation conserve la même sémantique mathématique que la baseline ; seul le regroupement des gradients avant communication change. Elle permet donc d'évaluer l'effet du `bucketing` sans introduire de recouvrement entre calcul et communication.

### 1.3 Optimisation 2 — Recouvrement communication-calcul avec `MPI_Iallreduce`

Une fois le `bucketing` stabilisé, une seconde optimisation consiste à lancer certaines communications avant la fin complète du backward afin de rechercher un recouvrement partiel entre communication et calcul. Cette version repose sur le même `BucketManager`, mais remplace le lancement en fin de backward par un déclenchement événementiel. Lorsqu'un gradient de paramètre devient `final-ready`, le runtime distribué est notifié. Dès que tous les paramètres actifs d'un `bucket` sont prêts, ce `bucket` est empaqueté puis réduit de manière asynchrone via `MPI_Iallreduce`. Le backward peut ainsi continuer pendant que certaines communications sont déjà en vol.

Pour supporter ce mode `overlap, bucketed`, `DistributedContext` n'expose plus uniquement des collectives bloquantes, mais aussi un wrapper de requêtes asynchrones fondé sur `MPI_Iallreduce`, ainsi que des primitives `wait` et `waitAll`. Au-dessus, un runtime explicite `BucketedOverlapRuntime` gère le cycle de vie de chaque étape : `beginStep(...)`, réception des événements `onParameterGradReady(...)`, notification `onBackwardComplete()`, puis `finalizeAndGetGlobalBatch()`. Le mode `non-overlap, bucketed` est lui aussi encapsulé dans un objet dédié, `StepBoundaryBucketedSync`, mais reste piloté à la frontière de l'étape. Avant `optimizer_.step()`, le runtime attend la fin de toutes les requêtes, dépile les `bucket` et garantit la cohérence des gradients.

Les trois modes, `non-overlap, non-bucketed`, `non-overlap, bucketed` et `overlap, bucketed`, partagent la même sémantique mathématique : dans tous les cas, chaque rang applique une mise à jour synchrone fondée sur le gradient global moyen. La différence porte uniquement sur l'organisation de la synchronisation et sur la réduction des surcoûts de communication.

### 1.4 Résultat pratique et déplacement du goulot d'étranglement

Les mesures historiques les plus récentes sur `Tiny-ImageNet`, avec un CNN à trois étages convolutifs, `world_size = 16`, `batch_size = 64`, `Grad Sync Mode = overlap_bucketed` et `bucket_size_bytes = 4 MiB`, montrent une époque d'environ `630 s`, dont `543 s` pour `fwd_bwd` et `59 s` pour `sync_total`. Ces chiffres restent des données de profiling historiques : tant que `overlap_bucketed` n'a pas repassé une qualification multi-rang complète, ils ne doivent pas être interprétés comme une validation benchmark définitive.

Ces optimisations ont néanmoins réduit la part relative de la communication. Le goulot d'étranglement principal s'est déplacé vers le calcul CNN lui-même, en particulier les opérations de convolution et les réarrangements mémoire associés. La suite du travail doit donc porter non seulement sur le `bucketed overlap`, mais aussi sur les noyaux CPU des couches convolutionnelles.

## 2 Refonte du backward et optimisation du hot path autograd

### 2.1 Modèle initial

L'implémentation initiale de l'autodiff reposait sur un schéma direct : pendant le forward, chaque opérateur construisait son `Node` de sortie puis lui associait une lambda `backwardFn` via `setBackwardFn(...)`. Cette lambda capturait à la fois l'état du forward nécessaire au backward, par exemple les matrices d'entrée, les informations de broadcast, le cache `im2col` ou les indices du pooling, et la règle locale de dérivation. Pendant l'entraînement, l'appel à `loss_node->backward()` collectait les nœuds atteignables en sens inverse pour former une séquence d'exécution backward, puis exécutait chaque `backwardFn` selon l'ordre inverse des dépendances topologiques. Cette approche était simple et suffisante pour la première phase du projet ; elle a permis de faire fonctionner le MLP, les fonctions d'activation, les fonctions de perte et les couches CNN ajoutées ensuite.

### 2.2 Limites du modèle initial

Ce modèle, dans lequel chaque nœud porte sa propre fermeture anonyme, n'était réellement adapté qu'à un prototype. Le problème n'était pas la correction des gradients, mais l'absence de sémantique explicite sur l'état d'exécution du backward. Dans l'ancien système, chaque backward local calculait sa dérivée puis écrivait immédiatement dans le gradient du parent via `addGrad(...)`. D'un point de vue runtime, le système ne voyait alors qu'un fait grossier : un nœud venait de modifier le buffer de gradient de son parent. Il ne pouvait pas distinguer une contribution partielle de la dernière contribution attendue.

En conséquence, le processus de fusion des contributions, le moment où le gradient de sortie d'un nœud devient `final-ready`, et le moment où un gradient de paramètre peut déclencher un événement de communication ou de profilage n'étaient jamais représentés explicitement. Pour un entraînement synchrone classique, cette limite restait supportable. En revanche, pour du recouvrement communication-calcul, des hooks de paramètres `final-ready`, du bucketing, une planification CUDA par stream ou des graphes plus complexes de type Transformer, elle devenait structurelle.

### 2.3 Refonte vers un moteur d'exécution explicite

La refonte réalisée ici ne vise pas à modifier les formules de gradient, mais à transformer le backward en un processus explicite piloté par un moteur d'exécution central. Dans la nouvelle version, `Node` conserve son interface externe, mais porte désormais des métadonnées autograd plus explicites : `requires_grad`, `is_leaf`, `is_parameter`, un `grad` alloué paresseusement, la liste explicite des dépendances d'entrée `inputs`, un `GradFn` optionnel et un `BackwardContext` stocké par valeur. De plus, seuls les nœuds de sortie pour lesquels `requires_grad=true` reçoivent effectivement un `grad_fn`, un `context` et des `inputs` ; les chemins constants ne construisent donc plus d'état backward inutile. Enfin, `Node::backward()` ne lance plus directement l'ancien enchaînement reverse-topo basé sur les lambdas, mais délègue cette responsabilité à un `AutogradEngine`.

`AutogradEngine` constitue le changement structurel principal de cette étape. À partir du nœud de loss, il reconstruit le sous-graphe atteignable en backward et maintient, pour chaque nœud, le nombre de contributions de gradient provenant de l'aval qui n'ont pas encore été reçues. Un nœud n'entre dans la `ready queue` que lorsque son gradient de sortie a reçu toutes ses contributions. Le système exprime ainsi explicitement le moment où le gradient de sortie d'un nœud devient `final-ready`, ce qui est essentiel pour l'entraînement distribué.

En parallèle, la logique backward des opérateurs de base et des fonctions de perte a été déplacée vers des objets explicites `GradFn` et `BackwardContext`. `BackwardContext` conserve par valeur les caches nécessaires au backward, tandis que `GradFn` calcule uniquement les contributions de gradient à propager aux entrées, sans modifier directement `grad` des parents. Toute l'accumulation des gradients et toute la décision de passage à l'état ready sont désormais centralisées dans l'engine.

Cette migration est maintenant complète sur le chemin de production. Les opérateurs élémentaires (`add`, `mul`, `matmul`, `sum`, `mean`), les activations, les fonctions de perte, les couches linéaires, `MaxPool2D` et `Conv2D` ont tous été portés vers `GradFn + BackwardContext + AutogradEngine`. La couche de compatibilité historique basée sur `setBackwardFn(...)`, les anciennes arêtes `parents_` et la logique `reverse-topo` legacy ont été supprimées. Le backward n'utilise donc plus qu'une seule sémantique : `Node.inputs + GradFn + BackwardContext + AutogradEngine`.

Cette étape était particulièrement importante pour la suite distribuée. Le fait de disposer d'un événement `parameter-ready` explicite permet désormais au runtime de synchronisation de se brancher directement sur le moment où un gradient de paramètre devient exploitable. C'est ce point d'appui qui rend possible le mode `bucketed + overlap` décrit dans la section précédente, sans réintroduire de logique de communication ad hoc dans les couches ou dans le `Trainer`.

### 2.4 Optimisation du hot path de l'engine

Une fois la refonte structurelle terminée, un second travail a consisté à réduire le coût propre du runtime autograd. Les gradients étaient corrects, mais le moteur d'exécution restait encore coûteux sur des graphes CNN de taille réelle. L'optimisation réalisée ne modifie pas les formules de gradient ; elle vise seulement à retirer du chemin critique plusieurs surcoûts de framework.

Premièrement, l'état d'exécution du backward est maintenant indexé localement pour chaque appel à `backward()`. Au lieu de manipuler l'état des nœuds via des structures de recherche centrées sur des pointeurs et des objets `shared_ptr`, l'engine collecte le sous-graphe atteignable de cette exécution, lui assigne des indices denses locaux et accède ensuite à `states[index]`. Deuxièmement, les `GradientContribution` n'embarquent plus de `shared_ptr<Node>` comme cible ; ils transportent directement un `target_index` dense. Enfin, les petites listes de contributions sont stockées dans un conteneur inline de capacité fixe (`InlineContributionList<4>`), ce qui évite les petites allocations dynamiques dans la grande majorité des opérateurs de production.

Troisièmement, le chemin de fusion des gradients a été resserré. `Matrix` expose désormais une primitive `addInPlace(...)`, et `Node::addGrad(...)` n'effectue plus qu'une matérialisation initiale du buffer de gradient suivie d'une accumulation inplace sur buffer contigu. Le runtime distingue explicitement le coût du `first-write` (`engine_grad_merge_first_write`) et celui des accumulations ultérieures (`engine_grad_merge_accumulate`), afin de savoir si le coût résiduel provient encore du framework ou simplement du trafic mémoire inhérent aux gros tenseurs.

Les mesures historiques obtenues sur `Tiny-ImageNet` suggèrent que cette première phase d'optimisation du hot path a réduit le coût du backward. Dans une configuration `CNN + Tiny-ImageNet + 16 rangs MPI + overlap_bucketed`, le temps `fwd_bwd` est passé d'environ `753 s` à `543 s` sur une époque de référence, ce qui indique que le runtime autograd constituait probablement un goulot d'étranglement réel. Après optimisation, `engine_grad_merge_accumulate` ne représente plus qu'environ `2.5 s`, alors que `engine_grad_merge_first_write` reste autour de `45 s`. Là encore, ces valeurs restent des mesures historiques de profiling et ne suffisent pas, à elles seules, à requalifier `overlap_bucketed` comme résultat benchmark validé.

Le profilage montre cependant que le moteur autograd n'est plus le seul responsable dominant. Une fois ces surcoûts réduits, les principaux hotspots redeviennent des opérations directement liées aux convolutions : `conv2d_forward_im2col`, `conv2d_forward_gemm`, `conv2d_backward_dX_gemm`, `conv2d_backward_dW_gemm` et `conv2d_backward_col2im`. Le travail sur l'engine a donc déplacé le goulot d'étranglement vers les kernels convolutionnels eux-mêmes, ce qui était précisément l'effet recherché.

## 3 Mise à jour du jeu de données Tiny-ImageNet

Le jeu de données MNIST étant trop simple pour mettre réellement en évidence les avantages et les difficultés de l'entraînement distribué, nous avons fait évoluer l'expérimentation vers Tiny-ImageNet. Ce jeu de données contient 200 classes, avec 500 images d'entraînement et 50 images de validation par classe. Les images sont au format couleur, ce qui rend la tâche plus réaliste et plus exigeante que MNIST.

La logique de chargement des données a donc été adaptée au format de Tiny-ImageNet, et la boucle d'entraînement a également été ajustée afin que le modèle puisse traiter correctement ce nouveau jeu de données.

En pratique, l'ensemble d'entraînement contient 100 000 images (200 classes × 500 images par classe), l'ensemble de validation 10 000 images (200 classes × 50 images par classe), et l'ensemble de test 10 000 images.

À ce stade, les performances du modèle restent limitées. Sur les expériences distribuées les plus récentes en CPU, une époque peut encore prendre de l'ordre de 10 minutes selon la configuration MPI, la taille de batch locale et le mode de synchronisation. La convergence demeure également faible sur la configuration CNN actuellement utilisée : la précision de test reste basse après peu d'époques, ce qui suggère qu'il reste à la fois un travail d'optimisation système et un travail de réglage du modèle.

La suite du travail devra donc porter sur deux directions complémentaires : d'une part l'accélération plus poussée du calcul, en particulier des chemins `im2col/col2im` et du backward convolutionnel ; d'autre part l'amélioration de l'architecture ou du réglage du modèle, afin d'améliorer à la fois l'efficacité de l'entraînement et la qualité finale des résultats.
