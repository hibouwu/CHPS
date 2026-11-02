### 3.13 OpenMP Target et addition vectorielle

Le calendrier du 9 octobre associe OpenMP Target au CM3. L'[exemple local](../cmexos/ompgpuecAdd.c) calcule `c[i] = a[i] + b[i]`. Le programmeur décrit une boucle et ses données ; le compilateur réalise le placement sur le dispositif et la distribution du travail.

```c
#pragma omp target teams distribute parallel for \
    map(to: a[0:N], b[0:N]) map(from: c[0:N])
for (int i = 0; i < N; ++i) {
    c[i] = a[i] + b[i];
}
```

`target` définit la région destinée au dispositif, `teams` crée des équipes, `distribute` répartit les itérations entre équipes et `parallel for` les répartit entre threads de chaque équipe. Cette composition ne fixe pas une correspondance portable exacte entre une équipe OpenMP et un bloc CUDA.

Dans cet exemple sans mapping préexistant, `map(to: ...)` rend les entrées disponibles sur le dispositif, et `map(from: ...)` rapatrie la sortie à la fin. `a[0:N]` désigne **N éléments à partir de l'indice 0**, pas une taille en octets. Pour `y[i] = alpha*x[i] + y[i]`, `y` est à la fois entrée et sortie : utiliser `map(tofrom: y[0:N])`.

Sans `nowait`, l'exécution poursuit après l'achèvement de cette région target. Une clause de mapping exprime les données à rendre disponibles ; dans un programme plus général, un mapping existant ou une mémoire partagée entre dispositifs peut éviter une copie physique supplémentaire.

Références : [modèle d'exécution OpenMP 5.2](https://www.openmp.org/spec-html/5.2/openmpse3.html), [construct distribute](https://www.openmp.org/spec-html/5.2/openmpse67.html), [carte de référence officielle](https://www.openmp.org/wp-content/uploads/OpenMPRefCard-5-2-web.pdf).

### 3.14 Compilation, repli sur CPU et pièges de lecture

Une compilation réussie et un résultat juste ne prouvent pas une exécution GPU. L'implémentation OpenMP peut exécuter une région target sur l'hôte lorsque le dispositif n'est pas disponible. Le code local interroge le lieu d'exécution à l'intérieur de la région :

```c
int on_host = 1;
#pragma omp target map(from: on_host)
{
    on_host = omp_is_initial_device();
}
```

`on_host != 0` indique le dispositif initial, donc l'hôte dans ce programme. Une valeur nulle indique un dispositif cible ; le type de ce dispositif dépend de l'environnement. Les options de compilation doivent configurer une cible offload disponible : ajouter seulement `-fopenmp` ne garantit pas la génération et l'utilisation de code GPU.

Pour plusieurs boucles successives utilisant les mêmes tableaux, un environnement `target data` peut maintenir les mappings entre les régions et éviter des transferts répétés. Il faut toujours identifier quelle région produit chaque donnée avant son utilisation.

**Question type.** Pourquoi `map(from: y[0:N])` est-il insuffisant pour une mise à jour AXPY ? Parce que le calcul utilise la valeur initiale de `y` ; sans mapping préexistant, il faut aussi la rendre disponible sur le dispositif. Pourquoi `#pragma omp parallel for` ne suffit-il pas pour exprimer un offload ? Parce qu'il répartit le travail entre threads dans l'environnement courant, sans créer à lui seul une région target.

Référence : [omp_is_initial_device](https://www.openmp.org/spec-html/5.0/openmpsu149.html).
