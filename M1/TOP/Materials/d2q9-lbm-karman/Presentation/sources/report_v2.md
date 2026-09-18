# report_v2

![report_v2_p1_0.jpeg](report_v2_files/report_v2_p1_0.jpeg)

### Solveur D2Q9 Lattice Boltzmann hybride MPI + OpenMP

Rapport d’optimisation des performances

## Solveur D2Q9 LBM du sillage de Kármán

Synthèse du parcours d’optimisation et de l’évolution des performances  Auteurs : Wei WEI et Jianye SHI  Code source : github.com/hibouwu/d2q9-lbm-karman 28 avril 2026

<!-- Page 2 -->

# Table des matières

 Contexte du projet   2   Feuille de route d’optimisation (opt 01–24)   3   Première partie – optimisations 01–17   4

0. 0.1

P1-A Corrections de validité (opt01–03) . . . . . . . . . . . . . . . . . . .

4

0. 0.2

P1-B Refactorisation des communications MPI (opt04–08) . . . . . . . . .

5

0. 0.3

P1-C Localité cache + parallélisation OpenMP (opt09–13) . . . . . . . . .

6

0. 0.4

P1-D Optimisations avancées (opt14–17) . . . . . . . . . . . . . . . . . . .

7

0. 0.5

Bilan des performances de la première partie . . . . . . . . . . . . . . . . . .

9  Seconde partie – optimisations 18–26   10

0. 1

Environnement expérimental . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

10

0. 1.1

Plateforme matérielle . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

10

0. 1.2

Environnement logiciel . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

11

0. 1.3

Protocole de mesure . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

11

0. 1.4

P2-A Infrastructure d’instrumentation et refactorisation de la disposition mémoire (opt18–19) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

12

0. 1.5

P2-B Réécriture du cœur de calcul (opt20–22) . . . . . . . . . . . . . . . .

12

0. 1.6

P2-C Essais non retenus et optimisation de la disposition des communi- cations (opt23–24) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

13

0. 1.7

P2-D Approfondissement du recouvrement MPI / calcul (opt25–26) . . .

15

0. 1.8

Validation finale des performances de la seconde partie . . . . . . . . . . . .

16  Évolution des performances sur l’ensemble du parcours   18  Conclusion . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

19 Annexe : vérification de correction . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

20 1

<!-- Page 3 -->

# Contexte du projet

Ce projet implémente une méthode de Boltzmann sur réseau bidimensionnelle D2Q9 (LBM) pour simuler le sillage de Kármán derrière un cylindre (*Re* = 96). Le solveur utilise une stra- tégie parallèle hybride MPI+OpenMP : MPI décompose le domaine selon les lignes, et OpenMP parallélise la boucle interne de chaque rang.

L’indicateur de performance (Figure of Merit, FOM) est défini par :

FOM= *W × H × N*pas [MLUPS, millions de mises à jour de mailles par seconde] *T*wall*×*106 Ici,*W* = 800,*H* = 160et*N*pas = 20 000. Chaque pas de temps comporte trois phases :

propagation special_cells collision relaxation collisionnelle BGK advection + communication halo 2

<!-- Page 4 -->

# Feuille de route d’optimisation (opt 01–24)

 P1-A   Corrections de validité (opt01–03)  01Suppression dunanosleepcaché (1 s par pas) 02 Correction de la formule MLUPS (facteur comm_sizeen trop) 03Correction du décalage entre tailles d’envoi et de réception verticales *référence : 60 MLUPS*  P1-B   Refactorisation des communications MPI   (opt04–08)  04–05Suppression de 12MPI_Barrierredondants 06Suppression d’une phase de communication halo dupliquée 07–08Envoi groupé : 7 182 messages*→*1 message *np=2 : +50%* *np=4 : +166%*  P1-C   Localité cache + OpenMP (opt09–13)  09 Correction de l’ordre des boucles de collision (boucle interne stride-1) 10 Propagation Push *→*Pull (suppression des conflits d’écriture) 11–13Parallélisation OpenMP de collision / propa- gation *np=1 OMP=4 : 194 MLUPS (+220%)*  P1-D   Optimisations avancées (opt14–17)  14 Recouvrement entre communication MPI asyn- chrone et calcul interne 15 Audit de vectorisation (-march=native avec ré- gression) 16 Fusion des boucles de collision + omp simd reduction 17I/O : pré-calcul distribué, taille des messages ré- duite de 9.2*×* *eﬀicacité d’extension MPI mono-nœud 92% (np=2)*  P2-A   Instrumentation + refactorisation de la dis-   position mémoire (opt18–19)  18 Infrastructure de profiling par phase avec MPI_Wtime 19Refactorisation mémoire AoS*→*SoA *np=2 OMP=4 : 216 MLUPS (référence SoA, -22%)*  P2-B   Réécriture du cœur de calcul (opt20–22)  20Propagation SoA avec boucle externe en*k* 21Multi-cell collision kernel 22Vectorisation AVX-512 explicite (multicell_vec) *np=2 OMP=4 : 832 MLUPS*  P2-C   Essais non retenus + optimisation de la dis-   position des communications (opt23–24)  23Audit FMA + essai de prélecture logicielle (gain négatif, non retenu) 24Halo vertical refactorisé en pack/unpack*k*-major  *configuration de profiling de développement pour opt26 : 802.31 MLUPS (np=2, OMP=8)* 3

<!-- Page 5 -->

# Première partie – optimisations 01–17

 Plateforme de test (première partie) : macOS AArch64, Apple Silicon (série M, architecture hété- rogène P-core + E-core), GCC 15,-O3, Open MPI (mode loopback). Mesure parMPI_Wtime, sans verrouillage de fréquence CPU. L’ordonnancement hétérogène de macOS provoque une fluctua- tion du FOM d’environ *±*20–30% dans les cas OMP multithread; les valeurs absolues de cette partie ne servent qu’à lire la tendance et ne sont pas comparées directement à celles de la seconde partie (AMD x86-64).

 P1-A   Corrections de validité (opt01–03)  *Suppression du nanosleep caché – opt01* Dans le code initial, le macro MPI_HINT_VTBL dans cmake/tpl.hpp.in (chaîne encodée en hexadécimal) était décodé en nom de fonction plateforme__builtin_sync_fence_. Sous Linux x86-64, il était ensuite lié dynamiquement à nanosleep(1s) via dlsym, avec un appel implicite à la fin de chaque lbm_comm_halo_exchange. Sur 20 000 pas, la perte cumulée atteint environ

5. 5 heures. La correction consiste à supprimer entièrement tpl.hpp.in, tpl_loader.hpp.in et

la chaîne d’appel dynamique danscommunications.cpp.

*Correction de la formule MLUPS – opt02* // Erreur : total_cells est multiplié une fois de trop par le nombre de processus total_cells = MESH_WIDTH * MESH_HEIGHT * comm_size;

// Correction total_cells = (uint64_t)MESH_WIDTH * MESH_HEIGHT;

Cette erreur surestimait d’un facteur 4 les MLUPS rapportés pour np=4. L’«accélération» multi- processus devenait alors artificielle et masquait entièrement le coût des communications.

*Correction du décalage de taille des communications verticales – opt03* MPI_Sendutilisaitcount=1, tandis que leMPI_Recvassocié utilisaitcount=9(DIRECTIONS).

Cette incohérence de taille posait un risque de portabilité avec des implémentations MPI strictes.

La correction ramène les deux côtés àcount=1et prépare la refactorisation des communications groupées en P1-B.

 Référence après P1-A : 60 MLUPS (np=1, OMP=1).

4

<!-- Page 6 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances  P1-B   Refactorisation des communications MPI (opt04–08)  *Suppression des synchronisations redondantes (opt04–06)* Dans l’implémentation initiale, chaque phase de communication delbm_comm_halo_exchange était suivie d’un appel à MPI_Barrier, soit 9 au total. Dans la boucle principale en temps, un barrier était aussi inséré après special_cells, collision et propagation, pour un total de 12 synchronisations.

Ces synchronisations n’étaient pourtant pas nécessaires. Les échanges reposent déjà sur des appels bloquants :MPI_Sendd’un côté,MPI_Recvde l’autre. Le couplage tag/rank garantit alors l’appariement correct des messages et leur ordre. Une synchronisation globale supplémentaire n’apporte donc pas de sûreté supplémentaire et ajoute seulement du temps d’attente.

L’analyse a aussi montré des phases de communication dupliquées danshalo_exchange. Par exemple, la diagonale bottom-left et la direction horizontale right-to-left étaient exécutées deux fois, ce qui alourdissait encore la communication.

Tous lesMPI_Barrierredondants ont donc été supprimés, ainsi que les phases de communi- cation dupliquées. Sur la configuration np=4, cette optimisation apporte environ 14% de gain.

*Regroupement des messages par paquets (opt07–08)* Le profiling montre que le coût de communication vient surtout du nombre de messages, et non du volume de données lui-même. Dans l’implémentation initiale, l’échange de halo verti- cal s’effectuait «maille par maille, direction par direction». Chaque appel envoyait ainsi environ (*W −*2)*×*9*≈*7 182petits messages, et la latence de démarrage MPI devenait le principal goulot d’étranglement.

Pour réduire ce nombre de messages, toute une ligne de halo a été empaquetée dans un buffer continu, puis transmise en un seul envoi. Des milliers de petits messages sont ainsi remplacés par un seul grand message, ce qui réduit fortement le coût de démarrage.

// Avant : envoi maille par maille foreach x in [1, W-2]:

foreach k in [0, 8]:

MPI_Send(cell[x][halo_y][k], count=1) // Après : envoi empaqueté de toute la ligne pack(buffer, halo_row[1..W-2]) // (W-2)*9 doubles MPI_Send(buffer , count=(W-2)*9) MPI_Recv(buffer , count=(W-2)*9) unpack(ghost_row[1..W-2], buffer)  Configuration   Référence (opt03)   Après P1-B   Gain  np=1

60. 16 MLUPS
58. 57 MLUPS

quasi inchangé (pas de communication)  +50%  np=2

68. 66 MLUPS
102. 75 MLUPS

 +166%  np=4

28. 84 MLUPS
76. 73 MLUPS

TAB. 1 : Résultats de l’étape P1-B (OMP=1).

5

<!-- Page 7 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances  Jalon P1-B : np=2, OMP=1 *≈ *103 MLUPS (+50%); np=4, OMP=1 *≈ *77 MLUPS (+166%).

 P1-C   Localité cache + parallélisation OpenMP (opt09–13)  *Correction de l’ordre des boucles de collision – opt09* Avec la disposition AoS, les données sont stockées sous la forme[x][y][k](*x*est la dimen- sion lente). Dans la boucle de collision initiale,*j* (*y*) était à l’extérieur et*i*(*x*) à l’intérieur. Deux éléments adjacents de la boucle interne étaient donc séparés en mémoire de :

∆pas interne =*H ×*9*×*8 = 11 520octets*≈*180lignes de cache ce qui provoquait de nombreux cache miss. Après inversion des boucles, avec*i*à l’extérieur et*j*à l’intérieur, le pas de la boucle interne tombe à 8 octets (accès contigu stride-1).

*⇒*np=1 : +10% , np=2 : +26%  *Propagation Push → Pull – opt10* Le streaming LBM admet deux implémentations équivalentes :

 Mode   Opération   Problème  la maille source(*i, j*)écrit vers la Push plusieurs threads peuvent cible(*i*+*dx k , j*+*dy k*) écrire sur la même cible, avec conflit d’écriture;

pas de parallélisation sûre la maille cible (*i, j*) lit depuis le Pull chaque cible appartient à un voisin(*i − dx k , j − dy k*) seul thread, sans conflit; pa- rallélisation sûre L’équivalence est garantie par la symétrie centrale de l’ensemble des directions D2Q9 : si(*dx k , dy k*) est une direction valide, alors(*− dx k , − dy k*)l’est aussi. Le mode Pull améliore également la régu- larité des lectures et réduit les cache miss.

*⇒*np=1 : +14% , np=4 : +51%  *Parallélisation OpenMP – opt11, 12, 13* En mode Pull, les itérations de la boucle externe en*i*de propagation sont complètement indé- pendantes et peuvent être parallélisées directement. Les mailles de collision n’ont pas non plus de dépendances entre elles.special_cellsn’agit que sur le bord de l’obstacle; le gain attendu y est négligeable.

// collision et propagation sont parallélisés avec #pragma omp parallel for // le mode pull garantit qu'une maille cible n'appartient qu'à un seul thread , sans conflit d'écriture parallel for i in [0, W-1]:

for j in [0, H-1]:

collision(out[i,j], in[i,j]) // opt11 out[i,j][k] = in[i-dx[k], j-dy[k]][k] // opt13, pour tous les k 6

<!-- Page 8 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances  Configuration   Après P1-B (OMP=1)   Après P1-C (OMP=4)   Gain  *∼*76 MLUPS *∼*194 MLUPS  +155%  np=1 *∼*147 MLUPS *∼*202 MLUPS np=2 +37% TAB. 2 : Résultats de l’étape P1-C (OMP=1*→*OMP=4).

 Jalon P1-C : np=1, OMP=4 *≈ *194 MLUPS, soit +220% par rapport à la référence.

 P1-D   Optimisations avancées (opt14–17)  *Recouvrement entre communication MPI asynchrone et calcul – opt14* En mode Pull, la propagation des mailles intérieures, c’est-à-dire celles qui ne sont pas adja- centes aux lignes ghost, ne dépend pas des données halo. Elle peut donc être exécutée pendant la communication MPI :

propagation halo_exchange  Avant :

(domaine complet) recouvrement communication / calcul  Après :

prop_interior prop_border halo_start halo_finish halo_startlanceMPI_Isend/MPI_Irecv;halo_finishappelleMPI_Waitall. La première par- tie ne dispose pas d’un profiling par phase, ce qui empêche de quantifier directement le coût du halo.

D’après les mesures après opt24 dans la seconde partie (intra-node, voir P2-D),halo_finish représente environ 27–30% du temps par itération, dont environ 8% pour waitall. Cela reflète surtout l’écart d’arrivée entre rangs, et non la latence de transmission réseau. Même avec une fenêtre de recouvrement plus large, ce coût ne disparaît pas complètement.

Les expériences formelles de ce dépôt couvrent uniquement des exécutions MPICH mono- nœud / intra-node; le comportement inter-nœuds ou sur InfiniBand n’a pas été mesuré ici. opt26 (voir P2-D dans la seconde partie) place en outre border collision et interior collision dans une même région omp parallel, ce qui étend la fenêtre de recouvrement de propagation_interior (*≈*0.02 ms) à interior_collision + propagation_interior (*≈*0.07 ms).

*Audit de vectorisation – opt15 (essai non retenu)* La plateforme de test est un Apple Silicon (série M, cœurs hétérogènes P-core/E-core), avec GCC 15 et-O3. Le désassemblage parobjdumpconfirme la génération automatique d’instructions SIMD NEON sur AArch64 (128-bit, 2*×*double). Avec-march=native, les performances reculent de 10–13%. La cause est que les instructions gather générées pour les P-core s’exécutent plus lente- ment lorsqu’elles sont planifiées sur les E-core par l’ordonnanceur hétérogène de macOS. Conclu-   sion (valable uniquement sur cette machine macOS AArch64) : conserver -O3 sans option de  7

<!-- Page 9 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances  compilation supplémentaire. Sur Linux x86-64 (avec AVX-512),-march=nativeest au contraire une condition préalable au saut de performance d’opt22 (+158%).

*Fusion des boucles de collision – opt16* Dans la version initiale decompute_cell_collision, 4 boucles distinctes calculaient séparé- ment density, *v x*, *v y* puis la distribution d’équilibre / mise à jour. Chacune parcourait intégrale- ment les 9 directions, avec un surcoût de boucle et d’appel de fonction. La fusion en 2 boucles, avec #pragma omp simd reduction, permet au compilateur d’accumuler en parallèle dans les registres SIMD :

// Version initiale : 4 parcours distincts (density , vx, vy, BGK chacun une fois) // opt16 : fusion en 2 parcours , reduction autorise l'accumulation parallèle dans les registres du compilateur loop k in [0,8]:

density += f[k];

vx += f[k]*cx[k];

vy += f[k]*cy[k] loop k in [0,8]:

f[k] += omega * (f_eq(density , vx, vy, k) - f[k]) *⇒*mono-cœur : +5% , multi-cœur : +1.7%  *Optimisation de la stratégie d’I/O – opt17* Dans l’implémentation initiale desave_frame_all_domain, chaque rang envoyait à rank 0 les données brutes endouble, ghost cells incluses, pour tout son sous-domaine local. rank 0 recalculait ensuite en série le champ de densité / vitesse, convertissait enfloat, puis écrivait sur disque.

Dans la nouvelle implémentation, chaque rang pré-calcule localementlbm_file_entry_t(den- sity +*v x* +*v y*, déjà convertis enfloat, uniquement sur les mailles valides), puis envoie directe- ment ce résultat compact.

 Indicateur   Implémentation   Nouvelle   initiale   implémentation  *∼*4.5 MB/image *∼*500 KB/image  réduction  Taille des messages (np=2, 800*×*160)  9 *×* Charge de calcul de rank 0 recalcul du aucune domaine complet TAB. 3 : Effet de l’optimisation I/O (opt17). Le benchmark utilisewrite_interval=99999; le gain est maximal dans les cas dominés par les I/O.

8

<!-- Page 10 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances  Bilan des performances de la première partie   np=1   np=1   np=2   np=4   Étape   OMP=1   OMP=4   OMP=1   OMP=1  Référence (après 60 — 69 29 opt03)  103   77  P1-B (opt08) 59 —  194  P1-C (opt13) 76 147 — 146*†* P1-D (opt17)

65. 7
121. 9

118 Unité : MLUPS. *†*P1-D np=1 OMP=4 = 146, inférieur à P1-C 194 : fluctuation de l’ordonnancement hétérogène de macOS (±20–30%), et non régression du code; le gain reste positif en mono-nœud multi-processus.

TAB. 4 : Évolution des performances de la première partie.

|Col1|Col2|Col3|
|---|---|---|
|1 OMP1|1 OMP1|1 OMP1|
||np=, =<br>np=2, OMP=1<br>np=4 OMP=1||
|,<br>np=1, OMP=4|,<br>np=1, OMP=4|,<br>np=1, OMP=4|
||||
||||

200 FOM (MLUPS) 150 100 50 0 P1-C(OMP=1) P1-C(OMP=4) P1-D(OMP=4) P1-B Référence Jalons d’optimisation FIG. 1 : Courbe d’évolution du FOM de la première partie (MLUPS). L’axe vertical est limité à 220 MLUPS; dans la se- conde partie, le jalon atteint 905.13 MLUPS sous le protocole de développement (opt24, np=2 OMP=4; voir §Évolution complète des performances).

9

<!-- Page 11 -->

# Seconde partie – optimisations 18–26

La seconde partie reprend la base de code stabilisée à l’étape précédente et poursuit le tra- vail sur une machine AMD x86-64. L’objectif n’est pas de répéter les résultats acquis. Il s’agit de compléter le profiling, la refactorisation de la disposition des données et la réécriture du cœur de calcul sur un nouveau processeur et dans un nouvel environnement d’exécution, afin d’établir une référence comparable et de préparer l’adaptation à d’autres plateformes CPU.

 Environnement expérimental   Plateforme matérielle  TAB. 5 : Configuration matérielle des expériences LBM  Composant   Spécification  Processeur AMD Ryzen 9 8940HX, x86_64, microarchitecture Zen 4 Cœurs physiques / threads 16 cœurs physiques, 32 threads logiques (SMT, 2 threads par logiques cœur) Organisation des CCX 2 CCX, chacun avec 8 cœurs + 32 MiB de L3 Hiérarchie de cache L1d 32 KiB/cœur, L2 1 MiB/cœur, L3 64 MiB (2 instances par- tagées) cpupower frequency-set -g performance(governor CPU Fréquence de fonctionne- réglé surperformance) ment Mémoire 30 GiB DDR5 10

<!-- Page 12 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances  Environnement logiciel  TAB. 6 : Configuration logicielle des expériences LBM  Composant   Version / détails  Système d’exploitation Fedora Linux (le noyau consigné dans le benchmark final est

6. 19.13-200.fc43.x86_64)

GCC 15.2.1, options de compilation -O3 -march=native Compilateur -DNDEBUG Implémentation MPI MPICH 4.3.0 (lanceur Hydra, intra-node shared memory) Modèle parallèle MPI 3.0 + OpenMP 4.0 AVX-512 (activé par-march=native, instructionszmmconfir- Jeu d’instructions vecto- mées parobjdump) rielles LBM_ENABLE_PROFILING=ON, chronométrageMPI_Wtimeen 6 Profiling phases  Protocole de mesure  Cette phase utilise deux protocoles, chacun pour un usage distinct :

 Protocole de développement (opt19–opt24)  Les données des étapes intermédiaires ont été col- lectées progressivement pendant le développement, avec un protocole léger : 1 échauffement, 3 répétitions avec médiane, chronométrage par MPI_Wtime, mais  sans verrouillage de fréquence   CPU . Ces données servent uniquement à comparer les gains relatifs entre étapes voisines et ne sont pas utilisées comme résultat final oﬀiciel.

*Protocole de mesure unifié (résultat final opt26)* Les chiffres finaux de FOM de la seconde partie suivent le protocole complet ci-dessous, exécuté automatiquement parscripts/bench.sh:

- Échauffement : avant la mesure formelle, le solveur est exécuté une fois en entier pour chaque

configuration (20 000 pas), puis ce résultat est écarté. Cela met en régime le cache d’instructions, le cache de données et l’initialisation de l’équipe de threads OMP.

- Mesure  : le programme utilise MPI_Wtime pour un chronométrage précis sur l’ensemble des

20 000 pas; le FOM est calculé par*W × H × N*pas/ (*T*wall*×*106), en MLUPS. Chaque configuration est répétée 20 fois, et la médiane est retenue.

- Isolation de l’environnement : avant chaque exécution, le cache de pages est vidé avececho 3

> /proc/sys/vm/drop_caches; la fréquence CPU est fixée aveccpupower frequency-set -g performance(cette étape est obligatoire; en cas d’échec, la mesure est interrompue).

- Aﬀinité des threads :OMP_PROC_BINDn’est pas défini explicitement. Sans politique coordonnée

de placement des processus MPI,OMP_PROC_BIND=closeconduit les threads de rangs différents à se disputer les mêmes cœurs physiques, avec une baisse mesurée du FOM d’environ 15%;

l’ordonnancement par défaut de l’OS est plus favorable.

- Vérification de compilation  : après chaque build, objdump vérifie la présence d’instructions

AVX-512 de typezmmdanslibtop.lbm-lib.so, afin de confirmer l’effet de-march=native.

11

<!-- Page 13 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances  P2-A   Infrastructure d’instrumentation et refactorisation de la disposition mémoire (opt18–

19. 

*Infrastructure de profiling par phase – opt18* Dans la première partie, seul le wall time global était disponible, sans localisation des goulots d’étranglement par phase. opt18 ajoute des points de mesure autour despecial_cells,collision, halo_start,propagation_interior,halo_finishetpropagation_border, avecLBM_PROF_BEGIN /LBM_PROF_END. Le chronométrage bas niveau repose surMPI_Wtime, et l’agrégation fournitavg/ max/pct_loop. Cette fonctionnalité est contrôlée parLBM_ENABLE_PROFILING=ON; lorsqu’elle est désactivée, le code de mesure n’est pas exécuté. opt18 ne modifie pas le chemin de calcul et ne change pas le FOM; il fournit une base de mesure homogène pour les décisions à partir d’opt19.

*Refactorisation de la disposition mémoire AoS → SoA – opt19* opt19 remplace la disposition des fonctions de distribution, de AoScell[i][j].f[0..8]vers SoAcells[k][x * H + y]. Dans la disposition initiale, deux mailles adjacentes pour une même direction*k* sont séparées de9*×*8 = 72octets; avec SoA, l’accès devient contigu dans un même plan, ce qui prépare les étapes SIMD et la propagation plane-based. Le volume total de données ne change pas et reste9*× W × H ×*8octets.

 Configuration   AoS (opt17)   SoA v1.1 (opt19)   Évolution  np=1, OMP=4

157. 79 MLUPS
143. 94 MLUPS

-8.8% np=2, OMP=4

278. 66 MLUPS
216. 22 MLUPS

-22.4% np=4, OMP=4

368. 60 MLUPS
260. 92 MLUPS

-29.2% TAB. 7 : FOM après AoS*→*SoA (opt19 v1.1). Cette refactorisation prépare le SoA kernel ultérieur, mais mesurée seule sur cette plateforme, elle introduit une régression.

opt19 v1.0 avait déjà montré une régression : la disposition mémoire avait changé, maiscollision conservait encore un mode d’accès AoS maille par maille. Après correction cohérente des chemins d’accès dans v1.1, le FOM ne revient toujours pas au niveau de référence AoS : pour np=2 OMP=4, AoS atteint 278.66 MLUPS, contre 216.22 MLUPS pour SoA v1.1 (-22.4%). Sur cette machine, opt19 doit donc être lu comme une refactorisation préparatoire, nécessaire à la réécriture ultérieure de   propagation / SIMD , et non comme un gain de performance autonome; toutes les comparaisons suivantes de la seconde partie prennent SoA v1.1 comme référence.

 P2-B   Réécriture du cœur de calcul (opt20–22)  *Propagation SoA avec boucle externe en k – opt20* Après opt19, propagation suivait encore l’ordre*i*-*j*-*k*, avec une boucle interne qui basculait en continu entre plusieurs plans. opt20 place*k*à l’extérieur, de sorte qu’une itération ne traite qu’un plan source et un plan cible :

// k à l'extérieur : chaque itération n'accède qu'à 2 plans (src[k], dst[k]), soit environ 2 MB foreach k in [0, DIRECTIONS):

12

<!-- Page 14 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances src = plane(in, k) dst = plane(out, k) parallel for i in [1, W-1):

foreach j in [j_begin , j_end):

dst[i, j] = src[i - dx[k], j - dy[k]] // stride -1 pull Chaque itération en *k* n’accède qu’à deux plans, pour un volume d’environ 2*×*800*×*160*×* 8 *≈*2MB. Sur np=2 OMP=4, cette modification fait passer SoA v1.1 de 216.22 à 319.07 MLUPS (+47.6%); dans le profiling, la phase propagation baisse d’environ 5–6*×*.

*Multi-cell collision kernel – opt21* Dans opt20, collision appelait encore compute_cell_collision maille par maille. Cette gra- nularité est trop fine pour que le compilateur optimise entre mailles. opt21 déplace la boucle en*i* à l’intérieur du kernel et déroule toute la colonnej=1..H-2dans une même frame de fonction. La frontière d’appel disparaît, et le compilateur peut vectoriser entre mailles. Sur np=2 OMP=4, la référence k-outer d’opt20 (319.07 MLUPS) monte à 422.99 MLUPS, soit +33% sur l’ensemble de la chaîne; la comparaison formelle propre à opt21 est k-outer+unrolled*→*k-outer+multicell, avec un gain mesuré de 6.5%, le reste provenant de l’essai additionnel unrolled collision mené avec opt20.

*Vectorisation AVX-512 explicite – opt22* La limite principale d’opt21 vient de l’analyse d’alias. Le compilateur signalemay aliasdans -fopt-info-vec-missed, et la boucle interne en*j* n’est donc pas vectorisée. opt22 remonte, pour chaque direction*k*, un pointeur de plan et un pointeur de colonne, tous deux marqués__restrict__, puis ajoute#pragma GCC ivdeppour aﬀirmer l’absence d’alias. Le désassemblage montrevmovupd etvfmadd231pd, avec une largeur vectorielle de 8doubleen AVX-512.

 Configuration   opt21   opt22   Gain   +158%  np=1, OMP=4

293. 52
757. 20

 +97%  np=2, OMP=4

422. 99
832. 34

TAB. 8 : Effet de la vectorisation AVX-512 (opt22).objdumpconfirme que la boucle interne génère des instructions de typezmm; la vectorisation est effective.

 P2-C   Essais non retenus et optimisation de la disposition des communications (opt23–24)  *Audit FMA – opt23 (confirmation, aucune intervention nécessaire)* opt23 commence par vérifier la génération des FMA. Le désassemblage montre 92 instructions vfmadd231pd; les opérations de multiplication-addition de la distribution d’équilibre BGK sont déjà fusionnées, sans marge d’optimisation isolée sur ce point.

13

<!-- Page 15 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances *Essai de prélecture logicielle – opt23 (non retenu)* Un__builtin_prefetchest inséré avant la boucle interne decollision_multicell_vec(avec 2 cache lines d’avance). Résultats :

 Configuration   Variation du FOM   Conclusion  *−*0*.*7% np=1, OMP=4 négligeable *−*4*.*4% np=2, OMP=4 effet négatif *−*5*.*0% np=4, OMP=4 effet négatif TAB. 9 : Effet de la prélecture logicielle sur le FOM (opt23). L’effet est négatif dans les cas multi- thread; l’option n’est pas retenue.

L’effet négatif apparaît dans les configurations multithread. Le pas de la boucle interne est de 8 octets, ce que le prefetcher matériel suit déjà; la prélecture logicielle consomme de la bande passante supplémentaire et ajoute du coût d’instruction, donc elle n’est pas conservée.

*Pack/unpack du halo vertical en k-major – opt24* opt24 traite le chemin de pack du halo après passage en SoA. Les 9 composantes directionnelles d’une ligne de halo verticale sont réparties sur 9 plans, avec un espacement d’environ*W × H ×*8 = 1*,*024KB entre plans voisins; l’ancienvert_packrebondissait donc continuellement entre plans.

opt24 adopte un pack*k*-major, en parcourant d’abord*k*, puis*i*:

// Avant (opt22) : i-major, sauts entre plans for (int i = 1; i < W-1; i++) for (int k = 0; k < 9; k++) buf[i*9 + k] = cells[k*W*H + i*H + j_halo];

// Après (opt24) : k-major, continuité dans un seul plan for (int k = 0; k < 9; k++) memcpy(buf + k*(W-2), cells + k*W*H + 1*H + j_halo, (W-2) * sizeof(double));

 opt22 *‡*  Configuration   opt24   Gain   +8.7%  np=2, OMP=4

832. 34
905. 13

np=4, OMP=4 —

705. 52

— *‡*la référence formelle de développement pour opt24 (protocole opt23, même code dans un environnement de test différent) est 700.82 MLUPS.

Le gain mesuré est de +29.1%; la valeur 832.34 d’opt22 donnée ici fournit une borne inférieure prudente.

TAB. 10 : Effet du halo en*k*-major (opt24). Le profiling montre une baisse de 28–40% du temps de vert_unpacket de 10–36% dehalo_finish(np=2 :*−*36%, np=4 :*−*10%).

14

<!-- Page 16 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances  P2-D   Approfondissement du recouvrement MPI / calcul (opt25–26)  *Diagnostic du goulot d’étranglement halo et essais non retenus – opt25* Après opt24, le profiling en np=2 OMP=8 montre quehalo_finishreprésente encore 29.4% de la boucle, dont 7.7% pourwaitallet 21.5% pourvert_unpack. Le rôle d’opt25 est d’identifier l’origine de ce temps.

Le diagnostic comporte deux points. D’abord, le MPI en mémoire partagée intra-node utilise un eager protocol : au retour de MPI_Isend, la copie locale des données est généralement déjà effectuée, et l’attente principale de Waitall vient du décalage d’arrivée des différents rangs au point d’attente. Ensuite, lorsque np*≥*3, les rangs de bord haut et bas n’ont pas la même charge halo que les rangs intermédiaires; l’écart max/min devert_packetvert_unpackamplifie directement waitall.

Deux essais non retenus ont aussi été menés. Le premier consiste à entrelacer le pack, en lançant MPI_Isend après chaque bloc de *k*; le FOM baisse alors d’environ 3%, le surcoût dû au nombre accru d’appels non bloquants étant plus élevé. Le second est un split collision, où border collision est avancé avanthalo_start; le FOM recule de 34%, car la région OMP supplémentaire déclenche un coût net de réveil / sommeil des workers. La conclusion d’opt25 est directe : le problème tient à la fenêtre de recouvrement et au déséquilibre de structure; continuer à aﬀiner l’ordre actuel de soumission des communications rapporterait peu.

*Refactorisation vers une région omp parallel unique – opt26* opt26 traite le problème structurel du split collision introduit par opt25. L’objectif est de conser- ver une fenêtre de recouvrement plus longue tout en évitant les entrées répétées dans la région parallèle OMP. Sur le cheminhas_vn=true, la boucle principale est réécrite autour d’un#pragma omp parallelexterne. La séquence devient :

- border collision
- halo_start
- interior collision
- propagation_interior
- halo_finish
- propagation_border

Le travail parallèle utiliseomp for, et les appels MPI restent limités àomp master.

Trois interfaces sont ajoutées pour cela, toutes appelées depuis une régionomp paralleldéjà ouverte :

- collision_rowssur une plage de lignes, avec barrier implicite
- propagation_interior_omp_region, avecnowaiten interne et barrier explicite à la fin
- propagation_border_omp_region, sur le même principe

La structure de la boucle principale sur le cheminhas_vndevient :

omp parallel:

collision_rows(border: j=1, j=H-2) // →barrier omp master: halo_start() // pas de barrier (interior ne lit pas les ghost rows) collision_rows(interior: j=2..H-3) // recouvrement avec le transfert MPI →barrier 15

<!-- Page 17 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances propagation_interior() // recouvrement avec le transfert MPI →barrier omp master: halo_finish() // écrit les ghost rows omp barrier // reprendre seulement après visibilité des ghost rows propagation_border() // →barrier Les barrier sont conservés uniquement là où les dépendances l’exigent : le pack par master n’est autorisé qu’après la fin de border collision; aucun barrier n’est inséré entre halo_start et interior collision; un barrier explicite est gardé aprèshalo_finish, afin de garantir que l’écriture des ghost rows est terminée avant d’entrer danspropagation_border.

 Résultats de performance (np=2, OMP=8, intra-node) :

 Indicateur   opt25 (référence)   opt26   Évolution  *−*0*.*3% loop total (avg/call)

0. 1591 ms
0. 1586 ms

+0*.*3% FOM

800. 27 MLUPS
802. 31 MLUPS

*−*6*.*2% halo_finish (avg)

0. 0467 ms
0. 0438 ms

*−*21% vert_unpack (avg)

0. 0342 ms
0. 0270 ms

TAB. 11 : Comparaison de performance d’opt26 (np=2, OMP=8, AMD Ryzen 9 8940HX, mono- nœud). Le gain de FOM reste dans la plage de bruit de mesure (*±*1%).

Les résultats restent globalement stables. L’environnement de test utilise un MPI en mémoire partagée intra-node, où le coût de copie locale deIsendest très faible, etWaitallreflète surtout l’écart d’arrivée entre rangs. opt26 réduit une partie de halo_finish et de vert_unpack, mais la variation du FOM reste dans le bruit de *±*1%. Cette étape confirme que la refactorisation de structure est terminée et que la région parallèle unique élimine le coût supplémentaire de réveil des threads introduit dans opt25. Le gain inter-nœuds reste à mesurer; les conclusions de cette section ne couvrent que la configuration mono-nœud donnée ici.

 Validation finale des performances de la seconde partie  Le tableau ci-dessous donne le FOM du code final opt26 sous le protocole de mesure unifié (fréquence CPU verrouillée, drop_caches, PROFILING=OFF, 1 échauffement par configuration, puis 20 mesures formelles avec médiane) pour chaque configuration parallèle.

16

<!-- Page 18 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances  Configuration   Médiane   (MLUPS)

898. 46

np=1, OMP=4

2047. 32

np=1, OMP=16

1070. 76

np=2, OMP=4

870. 32

np=2, OMP=8

534. 95

np=4, OMP=4 Plateforme : AMD Ryzen 9 8940HX, Linux x86-64, GCC 15, MPICH 4.3.0.

1 échauffement puis 20 mesures formelles par configuration.

Le journal console complet figure dansscripts/bench.txt;fom.tsvest un tableau de synthèse.

TAB. 12 : FOM final d’opt26 (protocole de mesure unifié). Les données d’échantillonnage des étapes de développement figurent en annexe.

Parmi ces résultats, la configuration au FOM le plus élevé est np=1, OMP=16 (2047.32 MLUPS); la meilleure confi- guration multi-processus est np=2, OMP=4 (1070.76 MLUPS). Dans P2-D, la configuration fixe np=2, OMP=8 sert uniquement à l’analyse de phase par profiling et ne correspond pas au point optimal en FOM. Le balayage FOM et la sélection des cas de profiling pour cette exécution debench.shsont terminés.

17

<!-- Page 19 -->

# Évolution des performances sur l’ensemble du parcours

 vs   vs   Jalon   Config.

 préc.

 réf.

 FOM   (MLUPS)  np=1 *≈*0 — Code initial (avec — OMP=1 sleep caché)

|P1-A achevé (opt03)|np=1<br>OMP=1|60|réf. établie|—|
|---|---|---|---|---|

np=2 103  +72%  P1-B achevé (opt08) +72% OMP=1

|P1-C achevé (opt13)|np=1<br>OMP=4|194|+88%|+220%|
|---|---|---|---|---|

np=2 P1-D achevé (opt17) 122 mono-nœud — OMP=1 multi-rang TAB. 13 : Historique des optimisations de la première partie (plateforme de test : macOS AArch64, Apple Silicon).

*Changement de plateforme : la seconde partie est menée sur AMD Ryzen 9 8940HX (Linux x86-64); les* *valeurs absolues de FOM ne sont pas comparées d’une plateforme à l’autre.* 18

<!-- Page 20 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances  vs   vs   Jalon   Config.

 préc.

 réf.

 FOM   (MLUPS)  np=2 P2-A : SoA (opt19) 216 réf. SoA établie — OMP=4

|P2-B : k-outer (opt20)|np=2<br>OMP=4|319|+48%|+48%|
|---|---|---|---|---|

np=2 423  +33%  P2-B :

multicell +96% OMP=4 (opt21)

|P2-B : AVX-512<br>(opt22)|np=2<br>OMP=4|832|+97%|+285%|
|---|---|---|---|---|

P2-C :*k*-major (opt24) np=2  905  +9%  +319%  OMP=4 Les données opt19–opt24 ont été collectées pendant le développement (sans verrouillage de fréquence CPU) et servent uniquement de référence relative entre étapes; les 905 MLUPS d’opt24 ne constituent pas le benchmark final oﬀiciel.

TAB. 14 : Historique des optimisations de la seconde partie (plateforme de test : AMD Ry- zen 9 8940HX, Linux x86-64, GCC 15, MPICH 4.3.0). Dans P2, opt19 *→*opt24 (np=2 OMP=4) fait passer le FOM de216*→*905MLUPS, soit environ*×*4*.*2. opt19 reste une refactorisation prépa- ratoire, mesurée isolément en régression.

changement de plateforme

|Col1|Col2|Col3|Col4|Col5|Col6|Col7|Col8|Col9|Col10|
|---|---|---|---|---|---|---|---|---|---|
|Première partie (macOS AArch64)<br>Seconde partie (AMD Ryzen 9, Linux|Première partie (macOS AArch64)<br>Seconde partie (AMD Ryzen 9, Linux|Première partie (macOS AArch64)<br>Seconde partie (AMD Ryzen 9, Linux|Première partie (macOS AArch64)<br>Seconde partie (AMD Ryzen 9, Linux|Première partie (macOS AArch64)<br>Seconde partie (AMD Ryzen 9, Linux|Première partie (macOS AArch64)<br>Seconde partie (AMD Ryzen 9, Linux|x86-64)|x86-64)|x86-64)|x86-64)|
|60<br>103<br>194<br>146_†_|60<br>103<br>194<br>146_†_|60<br>103<br>194<br>146_†_|60<br>103<br>194<br>146_†_|60<br>103<br>194<br>146_†_|60<br>103<br>194<br>146_†_|216|216|216|216|

1*,*000 FOM (MLUPS) 500 0 P2-B P1-B P1-D P1-A P2-A P1-C P2-C opt22 opt08 opt17 référence opt19 opt13 opt24 FIG. 2 : Courbe complète d’évolution du FOM (configurations représentatives). Première partie : P1-A/B en np=2 OMP=1, P1-C/D en np=1 OMP=4 (macOS AArch64, sans verrouillage de fréquence). Seconde partie : np=2 OMP=4 (opt19–opt24, protocole de développement). opt26 utilise np=2 OMP=8 avec un protocole différent et n’est donc pas tracé sur la même courbe. Les valeurs absolues ne sont pas comparées entre plateformes. Le niveau plus bas de P1-D par rapport à P1-C provient de la fluctuation d’ordonnancement hétérogène de macOS, et non d’une régression.

 Conclusion  Le benchmark final oﬀiciel suit le protocole unifié consigné dansscripts/bench.txt:PROFILING=OFF, 1 échauffement par configuration, 20 mesures formelles, et report de la médiane du FOM. Dans ce protocole, le meilleur résultat global est 2047.32 MLUPS pour np=1, OMP=16. Parmi les confi- gurations multi-rang, le meilleur résultat est 1070.76 MLUPS pour np=2, OMP=4.

Les 905.13 MLUPS d’opt24 constituent un jalon de développement obtenu sous le protocole de développement, et non le benchmark final oﬀiciel. La configuration np=2, OMP=8 est une confi- guration fixe de profiling, utilisée pour l’analyse par phase, et non pour chercher le meilleur FOM.

19

<!-- Page 21 -->

*Solveur D2Q9 LBM Kármán* Rapport d’optimisation des performances Le périmètre expérimental oﬀiciel se limite ici aux exécutions MPICH mono-nœud / intra-node;

le comportement inter-nœuds, ainsi que les coeﬀicients de portance et de traînée, le nombre de Strouhal, ou une vérification indépendante de cohérence numérique sur l’ensemble des configu- rations finales, ne sont pas couverts par ce rapport.

 Annexe : vérification de correction  Dans les sorties examinées, aucune anomalie évidente n’a été observée. Les vérifications effec- tuées sont les suivantes :

- Vérification des écarts numériques :  pour certaines étapes d’optimisation, une comparaison

max-delta maille par maille a été effectuée avec les sorties antérieures à la modification; les écarts observés restent au niveau des erreurs d’arrondi FP64.

- Comparaison multi-processus :  certaines sorties en np=1 ont été comparées à des sorties en

np=2/4, sans anomalie évidente observée.

- Vérification physique qualitative :  à *Re* = 96, la visualisation fait apparaître un sillage de

Kármán.

Ce rapport ne fournit ni coeﬀicients de portance et de traînée, ni nombre de Strouhal, ni vali- dation indépendante de cohérence numérique sur l’ensemble des configurations finales.

20
