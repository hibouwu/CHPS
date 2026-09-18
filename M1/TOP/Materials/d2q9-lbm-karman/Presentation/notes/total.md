# 13-slide canonical notes

## 01_cover

Ce projet présente l'optimisation d'un solveur D2Q9 LBM pour la simulation du sillage de Kármán, avec une stratégie parallèle hybride MPI + OpenMP. Nous avons réalisé 26 optimisations sur deux plateformes, avec un meilleur résultat mesuré de 2047 MLUPS.

## 02_contexte

Le solveur implémente la méthode de Boltzmann sur réseau D2Q9 pour simuler le sillage de Kármán à Re=96. La figure de mérite (FOM) est définie en MLUPS : millions de mises à jour de mailles par seconde. Le domaine est 800×160 mailles, simulé sur 20 000 pas. Chaque pas comporte trois phases : traitement des cellules spéciales, collision BGK, et propagation avec échange de halo.

## 03_feuille_de_route

Les quatre phases de la Partie 1 adressent successivement les corrections de validité, la refactorisation MPI, la localité cache et OpenMP, puis les diagnostics avancés. La Partie 2, sur AMD x86-64, refactorise la disposition mémoire et réécrit le cœur de calcul avec vectorisation AVX-512.

## 04_p1a_corrections

Le bug le plus spectaculaire : un appel nanosleep(1s) encodé en hexadécimal dans un header cmake, déclenché à chaque échange de halo. Sur 20 000 pas, la perte cumulée atteignait 5,5 heures par exécution. La correction consiste à supprimer entièrement la chaîne d'appel dynamique. Deux autres bugs corrigeaient la formule MLUPS — surestimée d'un facteur égal au nombre de rangs — et une incohérence dans les tailles MPI.

## 05_p1b_mpi

Le profiling montrait que le coût MPI venait du nombre de messages, non du volume de données. 12 MPI_Barrier redondants ont été supprimés — 9 dans halo_exchange et 3 dans la boucle principale. L'optimisation principale est le regroupement des messages halo : 7 182 petits envois remplacés par 1 seul message de toute la ligne. Résultat : np=2 OMP=1, 68.7 → 102.75 MLUPS, +50%.

## 06_p1c_openmp

L'inversion de boucle réduit le pas d'accès mémoire de 180 lignes de cache à 8 octets (stride-1). Le mode Pull élimine les conflits d'écriture entre threads, permettant une parallélisation OpenMP directe et sûre. Ces deux changements combinés amènent np=1 OMP=4 à 194 MLUPS, soit +220% par rapport à la référence.

## 07_p1d_simd

Certaines pistes testées n'ont pas été retenues, mais elles ont clarifié les choix techniques. Sur macOS AArch64 (Apple M3), -march=native + #pragma omp simd dégrade de 13% (OMP=1) et 10% (OMP=4). Diagnostic probable : lectures non contiguës + ordonnanceur P/E cores. Décision : conserver -O3 seul, qui génère déjà fmla.2d (NEON 2×double). Les autres diagnostics incluent overlap MPI asynchrone, fusion de boucles de collision, et optimisation I/O 9.2×.

## 08_plateforme_p2

La Partie 2 est menée sur AMD Ryzen 9 8940HX, 16 cœurs physiques, Zen4, avec AVX-512 confirmé par objdump. Le protocole de mesure unifié impose le verrouillage de fréquence CPU, la purge du cache de pages, 1 échauffement et 20 répétitions formelles avec médiane.

## 09_p2a_soa

La refactorisation de disposition mémoire, de AoS vers SoA, est intentionnellement préparatoire : mesurée seule, elle introduit une régression. Avec AoS, deux mailles adjacentes pour une même direction sont séparées de 72 octets ; avec SoA, à k fixé, les cellules voisines en j deviennent contiguës en mémoire. Cette contiguïté est la condition nécessaire pour la vectorisation AVX-512 qui suit.

## 10_avx512_resultat

Dans la chaîne de développement, cette étape atteint 832 MLUPS pour np=2 OMP=4. Nous n'écrivons pas d'intrinsics AVX-512 à la main : le compilateur émet bien des registres zmm, et le point clé reste l'ensemble layout mémoire + boucle + __restrict__ + #pragma GCC ivdep.

## 11_p2cd_halo_omp

opt24 réorganise le halo vertical en k-major et porte la chaîne de développement à 905 MLUPS pour np=2 OMP=4. Sur notre test intra-nœud, opt25 indique que le coût de waitall reflète surtout un déséquilibre d'arrivée entre ranks. opt26 regroupe plusieurs phases d’un même timestep dans une même région OpenMP, avec un gain limité mais une structure plus propre.

## 12_resultats_finaux

Le benchmark officiel donne 2047 MLUPS pour np=1 OMP=16 — meilleur résultat absolu — et 1071 MLUPS pour np=2 OMP=4, meilleure configuration multi-rang. Pour la comparaison avec macOS, il faut rester prudent : gain global indicatif, non iso-plateforme.

## 13_conclusion

Le parcours illustre l'importance de corriger d'abord les bugs de validité avant toute optimisation. La progression logique suit : communication → localité mémoire → parallélisme → refactorisation → SIMD. Les perspectives incluent la mesure inter-nœuds, la validation physique (Cl, Cd, Strouhal) et l'adaptation à d'autres architectures.
