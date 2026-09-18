## 1. Transition vers la partie 2
Maintenant, on passe à la deuxième partie du travail.

Jusqu'ici, la première partie se passait surtout sur macOS. Ici, on passe sur un AMD Ryzen 9, donc sur une plateforme x86-64 avec AVX-512. Cela nous permet de mesurer le programme sur du matériel AMD et de mieux l'adapter à d'autres architectures, surtout pour les optimisations mémoire et vectorisation côté x86.

Il faut aussi garder une distinction simple en tête. Certains chiffres viennent de mesures prises pendant la phase de développement, souvent quand on analysait les hotspots du programme. Ils servent à comprendre ce que fait une optimisation. Les chiffres finaux, eux, viennent du protocole de benchmark officiel.

## 2. P2-A — AoS vers SoA
Ici, on passe d'abord à l'organisation des données. Au départ, les données sont en AoS. C'est pratique à écrire, mais pour vectoriser, ce n'est pas très bon. Pour une direction donnée, les accès aux cellules voisines n'ont pas une bonne localité spatiale.

Donc on passe en SoA. Avec SoA, à k fixé, les cellules voisines en j deviennent contiguës en mémoire. Concrètement, ça facilite beaucoup le chargement de plusieurs valeurs en même temps avec SIMD.

Ce qu'on observe, c'est que SoA ne donne pas forcément un gain immédiat. Chez nous, il y a même une régression au début, parce que les accès ne sont pas encore adaptés au nouveau layout.

## 3. P2-B — Vectorisation AVX-512
Ensuite, on arrive à l'étape AVX-512. Là, ce qu'on voulait vérifier, c'était que le compilateur génère vraiment du code AVX-512 utile.

Le blocage venait surtout de l'analyse d'alias. Si le compilateur soupçonne un recouvrement entre pointeurs, il vectorise peu.

Dans le code, nous n'avons pas écrit d'intrinsics AVX-512 à la main. Nous avons gardé du C++ classique, avec `__restrict__` et `#pragma GCC ivdep`, puis nous avons vérifié à l'objdump que GCC générait bien des instructions zmm.

À partir de là, on voit bien des registres zmm dans l'assembleur. Donc AVX-512 est réellement utilisé. Dans la chaîne de développement, cette étape monte à 832 MLUPS. Donc, sur cette partie, ce qui compte, c'est l'ensemble : le layout mémoire, la boucle, et le compilateur.

## 4. P2-C / P2-D — Halo et région OpenMP
Après ça, on a travaillé sur des optimisations moins spectaculaires, mais utiles.

Pour le halo, on passe à un packing en k-major. C'est plus cohérent avec la SoA, et ce qu'on observe surtout, c'est une amélioration du comportement mémoire, surtout sur l'unpack.

Sur notre test intra-nœud, on a aussi regardé `MPI_Waitall`. En pratique, ce qu'on voit surtout, c'est un déséquilibre d'arrivée entre ranks. Certains arrivent plus tôt, puis attendent les autres.

Enfin, on regroupe plusieurs phases d'un même timestep dans une seule région OpenMP. Le gain n'est pas énorme, mais le code devient plus propre, avec moins de création répétée d'équipes de threads.

## 5. Résultats finaux
Pour les résultats finaux, on ne garde que le protocole officiel.

Le meilleur résultat mesuré est 2047 MLUPS avec `np=1` et `OMP=16`. Le meilleur résultat multi-processus est 1071 MLUPS avec `np=2` et `OMP=4`.

Ces résultats sont comparables entre eux, parce qu'ils viennent de la même machine et du même protocole. Pour la comparaison avec la partie macOS, il faut rester prudent : c'est un gain global indicatif, non iso-plateforme.

## 6. Conclusion
Pour conclure cette partie, il y a une idée simple.

On réorganise d'abord les données avec SoA. Ensuite, on aide le compilateur avec `__restrict__` et `ivdep`. Puis on réduit ce qui reste côté halo et OpenMP.

Merci.
