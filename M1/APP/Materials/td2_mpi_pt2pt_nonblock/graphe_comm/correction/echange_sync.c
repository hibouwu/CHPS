#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <mpi.h>

struct graphe_t
{
    int nb_noeuds ;

    /* tableau dimensionné à nb_noeuds
       nb_voisins[p] : retourne le nombre de noeuds directement connectés au noeud p
       */    
    int *nb_voisins ;

    /* tableau à 2 dimensions
       voisins[p] : tableau dimensionné à nb_voisins[p]
       contient les numéros des noeuds directement connectés au noeud p
       */
    int **voisins ;
};

void lire_graphe(const char *nom, struct graphe_t *graphe) {

    int nd, iv;
    FILE *fd = fopen(nom, "r");

    fscanf(fd, "%d", &(graphe->nb_noeuds));
    graphe->nb_voisins = (int*)malloc(graphe->nb_noeuds*sizeof(int));
    graphe->voisins = (int**)malloc(graphe->nb_noeuds*sizeof(int*));

    for( nd = 0 ; nd < graphe->nb_noeuds ; nd++ ) {
	fscanf(fd, "%d", &(graphe->nb_voisins[nd]));
	graphe->voisins[nd] = (int*)malloc(graphe->nb_voisins[nd]*sizeof(int));
    }

    for( nd = 0 ; nd < graphe->nb_noeuds ; nd++ ) {
	for( iv = 0 ; iv < graphe->nb_voisins[nd] ; iv++ ) {
	    fscanf(fd, "%d", &(graphe->voisins[nd][iv]));
	}
    }

    fclose(fd);
}

void afficher_graphe(struct graphe_t *graphe) {
    int nd, iv;
    printf("nb_noeuds : %2d\n", graphe->nb_noeuds);
    for( nd = 0 ; nd < graphe->nb_noeuds ; nd++ ) {
	printf("noeud %2d a %2d voisins : [ ", nd, graphe->nb_voisins[nd]);
	for( iv = 0 ; iv < graphe->nb_voisins[nd] ; iv++ ) {
	    printf("%2d ", graphe->voisins[nd][iv]);
	}
	printf("]\n");
    }
}

void tri_voisins(struct graphe_t * graphe, int *tri_list, int *ptr_nbv_inf)
{
    int rang, vois, vois_min;
    int nbv, nbv_inf;
    int iv, tmp;
    int iiv, iiv1, iiv_min;
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    nbv = graphe->nb_voisins[rang];

    nbv_inf = 0;

    for( iv = 0 ; iv < nbv ; iv++ )
    {
	vois = graphe->voisins[rang][iv];

	if (vois < rang)
	    nbv_inf++;

	tri_list[iv] = iv;
    }

    *ptr_nbv_inf = nbv_inf;

    for( iiv = 0 ; iiv < nbv ; iiv++ )
    {
	/* Recherche du min sur l'intervalle [iv, nbv[ */
	iiv_min = iiv;
	vois_min = graphe->voisins[rang][ tri_list[iiv_min] ];

	for( iiv1 = iiv ; iiv1 < nbv ; iiv1++)
	{
	    vois = graphe->voisins[rang][ tri_list[iiv1] ];

	    if (vois < vois_min)
	    {
		iiv_min = iiv1;
		vois_min = vois;
	    }
	}

	tmp               = tri_list[iiv];
	tri_list[iiv]     = iiv_min;
	tri_list[iiv_min] = tmp;
    }

    nbv_inf = 0;

    for( iiv = 0 ; iiv < nbv ; iiv++ )
    {
	vois = graphe->voisins[rang][ tri_list[iiv] ];

	if (vois < rang)
	    nbv_inf++;
    }

    assert(nbv_inf == *ptr_nbv_inf);

    printf("noeud %2d a %2d voisins : [ ", rang, graphe->nb_voisins[rang]);
    for( iiv = 0 ; iiv < graphe->nb_voisins[rang] ; iiv++ ) {
	printf("%2d ", graphe->voisins[rang][ tri_list[iiv] ]);
    }
    printf("]\n");
}

void echange_synchrone(struct graphe_t * graphe,
	char **msg_snd, int *taille_msg_snd,
	char **msg_rcv, int *taille_msg_rcv) 
{
    int rang, nbv, nbv_inf, iiv, iv, vois, tag;
    int *tri_list;
    MPI_Status sta;

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    tag = 1000;
    nbv = graphe->nb_voisins[rang];

    tri_list = (int*)malloc(nbv*sizeof(int));
    tri_voisins(graphe, tri_list, &nbv_inf);

    for( iiv = 0 ; iiv < nbv_inf ; iiv++ ) {
	iv = tri_list[iiv];
	vois = graphe->voisins[rang][iv];
	MPI_Recv(msg_rcv[iv], taille_msg_rcv[iv], MPI_CHAR, vois, tag, MPI_COMM_WORLD, &sta);
    }

    for( iiv = 0 ; iiv < nbv ; iiv++ ) {
	iv = tri_list[iiv];
	vois = graphe->voisins[rang][iv];
	MPI_Ssend(msg_snd[iv], taille_msg_snd[iv], MPI_CHAR, vois, tag, MPI_COMM_WORLD);
    }

    for( iiv = nbv_inf ; iiv < nbv ; iiv++ ) {
	iv = tri_list[iiv];
	vois = graphe->voisins[rang][iv];
	MPI_Recv(msg_rcv[iv], taille_msg_rcv[iv], MPI_CHAR, vois, tag, MPI_COMM_WORLD, &sta);
    }
    
    free(tri_list);
}

int main(int argc, char **argv) {

    char tmp[7];
    int n, rang, P, nbv, iv, test_msg;
    struct graphe_t graphe;
    char **msg_snd, **msg_rcv;
    int *taille_msg_snd, *taille_msg_rcv;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    MPI_Comm_size(MPI_COMM_WORLD, &P);

    lire_graphe("graphe.txt", &graphe);

    if (rang == 0)
	afficher_graphe(&graphe);

    if (P != graphe.nb_noeuds && rang == 0) {
	printf("Le nb de noeuds doit etre egal au nb de processus MPI. Nb de noeuds lus : %d\n", graphe.nb_noeuds);
	abort();
    }

    nbv = graphe.nb_voisins[rang];

    taille_msg_snd = (int*)malloc(nbv*sizeof(int));
    taille_msg_rcv = (int*)malloc(nbv*sizeof(int));
    msg_snd = (char**)malloc(nbv*sizeof(char*));
    msg_rcv = (char**)malloc(nbv*sizeof(char*));

    for( iv = 0 ; iv < nbv ; iv++ ) {
	taille_msg_snd[iv] = 7;
	taille_msg_rcv[iv] = 7;
	msg_snd[iv] = (char*)malloc(taille_msg_snd[iv]*sizeof(char));
	msg_rcv[iv] = (char*)malloc(taille_msg_rcv[iv]*sizeof(char));
	sprintf(msg_snd[iv], "S%02dD%02d", rang, graphe.voisins[rang][iv]);
    }

    echange_synchrone(&graphe, msg_snd, taille_msg_snd, msg_rcv, taille_msg_rcv);

    for( iv = 0 ; iv < nbv ; iv++ ) {
	sprintf(tmp, "S%02dD%02d", graphe.voisins[rang][iv], rang);
	test_msg = (strcmp(msg_rcv[iv], tmp) == 0);
	printf("P%02d : %s : %s\n", rang, msg_rcv[iv], (test_msg ? "PASSED" : "FAILED"));
    }

    MPI_Finalize();
    return 0;
}

