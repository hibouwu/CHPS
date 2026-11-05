# TP noté CUDA : Floyd-Warshall — feuille de réponses

APM 2026-2027, Programmation GPU. À remplir et à rendre avec `fw_gpu.cu`.
Les questions de code (Q.2 à Q.5, Q.7, Q.10) sont évaluées dans
`fw_gpu.cu` ; les autres ici.

Nom : ....SHI....  Prénom : ....Jianye....

## Q.1 — La boucle k côté hôte (1 pt)

(a) Qu'est-ce que le passage k+1 lit qui vient d'être produit par le
passage k ?

Réponse : Le passage k+1 lit les valeurs `d[i][j]`, `d[i][k+1]` et `d[k+1][j]` dans la matrice `d` qui viennent d'être mises à jour par le passage k. Ces valeurs sont nécessaires pour calculer le nouveau `d[i][j]` à l'itération k+1.

(b) À quelle échelle `__syncthreads()` synchronise-t-il ? Que manque-t-il
pour synchroniser toute la grille en CUDA standard ?

Réponse : `__syncthreads()` ne synchronise que les threads d'un même bloc. En CUDA standard, il manque une barrière globale permettant de synchroniser tous les blocs de la grille entre eux.

(c) Où reste la boucle sur k, et qu'est-ce qui joue le rôle de barrière
entre deux pas successifs ?

Réponse : La boucle sur k reste côté hôte. La barrière entre deux pas successifs est assurée par le lancement séquentiel des kernels dans le même stream CUDA : le kernel du passage k+1 ne démarre qu'une fois celui du passage k terminé.

## Q.5 — Chronométrage CPU / GPU (2 pts)

| n | CPU (ms) | GPU, transferts compris (ms) |
|------|----------|------------------------------|
| 512 | 97.148 | 210.537 |
| 1024 | 731.760 | 210.370 |
| 2048 | 5620.021 | 330.292 |

Constat (une phrase) : À n = 512 le GPU est plus lent à cause du coût d'initialisation et des transferts mémoire, mais il devient beaucoup plus rapide que le CPU dès n = 1024 et n = 2048.

## Q.6 — Nature des accès de votre kernel (2 pts)

Votre répartition : i sur threadIdx.y, j sur
threadIdx.x

Classement des accès de votre kernel (coalescé / diffusé / strided) :

Avec un bloc de taille (32, 8), les threads d'un même warp ont le même i et des j consécutifs, et la matrice est stockée ligne par ligne :

- Lecture de `d[i*n+k]` : diffusé (tous les threads du warp lisent la même adresse).
- Lecture de `d[k*n+j]` : coalescé (les threads du warp lisent des éléments consécutifs de la ligne k).
- Lecture et écriture de `d[i*n+j]` : coalescé (accès à des éléments consécutifs de la ligne i).

## Q.7 — Coalescé contre non coalescé (2 pts)

À n = 4096 : version coalescée 686.755 ms ; autre répartition (i sur x, j sur y, compilée avec -DSTRIDED) 886.239 ms ; écart : 199.484 ms (soit environ 1.29x plus lent pour la version strided).

## Q.8 — Trafic et toit mémoire (2 pts)

(a) Octets par mise à jour :

Dans le meilleur des cas, chaque mise à jour lit 3 entiers (`d[i*n+j]`, `d[i*n+k]`, `d[k*n+j]`) et écrit 1 entier (`d[i*n+j]`). Comme un int fait 4 octets, cela donne 4 * 4 = 16 octets par mise à jour (soit 16 * n^3 octets au total).

(b) Intensité arithmétique, et ce qui limite le noyau :

Une mise à jour fait 2 opérations (une addition et un min). L'intensité arithmétique est donc :
I = 2 / 16 = 0.125 op/octet.

Sur le GPU GH200 (pic FP32 de 67 TFLOP/s et bande passante HBM3 de 4000 Go/s), la balance machine est de 67000 / 4000 = 16.75 flop/octet. Comme 0.125 < 16.75, le noyau est clairement limité par la mémoire (memory-bound).

(c) Débit mesuré à n = 4096 (Go/s), pic de bande passante du GPU
(Go/s), pourcentage atteint :

Avec un trafic théorique de 16 * 4096^3 = 1099.51 Go et un temps de 686.755 ms (0.686755 s) :
- Débit atteint : 1099.51 / 0.686755 = 1601 Go/s
- Pic de bande passante du GH200 : 4000 Go/s
- Pourcentage atteint : 1601 / 4000 = 40 %

## Q.9 — Trois lancements par pas de bloc (1 pt)

Pourquoi trois lancements par pas de bloc K, et quel risque y a-t-il à
fusionner les phases 2 et 3 en un seul lancement ?

Réponse :

## Q.10 — Version par blocs (3 pts)

Accélération mesurée (par blocs / naïf coalescé) : ............ ×

D'où vient le gain, en une phrase :
