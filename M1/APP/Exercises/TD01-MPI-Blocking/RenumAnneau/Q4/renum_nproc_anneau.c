#include <stdio.h>
#include <assert.h>
#include <mpi.h>

int numerotation(int me_old, int ouest, int est)
{
    int tmp, me, tag = 1000;
    MPI_Status sta;

    if (me_old == 0)
    {
	me = me_old;
	MPI_Send(&me_old, 1, MPI_INT, est, tag, MPI_COMM_WORLD); // amorce l'anneau

	// Attend le message du dernier de l'anneau 
	// (le dernier lui envoie forcement un message puisqu'il ne sait pas qu'il est le dernier)

	// On utilise tmp pour ne pas utiliser me pour eviter d'ecraser la valeur initiale
	MPI_Recv(&tmp, 1, MPI_INT, ouest, tag, MPI_COMM_WORLD, &sta);
    }
    else
    {
	MPI_Recv(&me, 1, MPI_INT, ouest, tag, MPI_COMM_WORLD, &sta);
	me++;
	MPI_Send(&me, 1, MPI_INT, est, tag, MPI_COMM_WORLD);
    }

    return me;
}

void numerotation_nproc(int me_old, int ouest, int est, int *me, int *P)
{
    int tag_num = 1000, tag_npro = 2000;
    MPI_Status sta;

    if (me_old == 0)
    {
	*me = me_old;
	MPI_Send(&me_old, 1, MPI_INT, est, tag_num, MPI_COMM_WORLD); // amorce l'anneau

	// Attend le message du dernier de l'anneau 
	// (le dernier lui envoie forcement un message puisqu'il ne sait pas qu'il est le dernier)

	// le dernier de l'anneau nous envoie son rang c-a-d P-1 
	MPI_Recv(P, 1, MPI_INT, ouest, tag_num, MPI_COMM_WORLD, &sta);
	(*P)++;

	// On amorce la diffusion du nb total de processus dans l'anneau
	MPI_Send(P, 1, MPI_INT, est, tag_npro, MPI_COMM_WORLD);
    }
    else
    {
	MPI_Recv(me, 1, MPI_INT, ouest, tag_num, MPI_COMM_WORLD, &sta);
	(*me)++;
	MPI_Send(me, 1, MPI_INT, est, tag_num, MPI_COMM_WORLD);

	// On recupere le nb total de processus
	MPI_Recv(P, 1, MPI_INT, ouest, tag_npro, MPI_COMM_WORLD, &sta);

	// Si je ne suis pas le dernier, je transmet P a est
	if (*P != *me+1)
	{
	    MPI_Send(P, 1, MPI_INT, est, tag_npro, MPI_COMM_WORLD);
	}
    }
}

int main(int argc, char **argv)
{
    int rang, nproc, est, ouest, me, P;

    MPI_Init(&argc, &argv);

    /* Initialisation des données du problème
       */
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    est   = (rang+1) % nproc;
    ouest = (rang+nproc-1) % nproc;
    me = (rang == 0 ? 0 : -1);

    /* On retrouve a partir d'ici l'algorithme de renumerotation de l'anneau
       Rappel : on dispose de est et de ouest, on cherche a recalculer son rang me
     */
//    me = numerotation(me, ouest, est);
    numerotation_nproc(me, ouest, est, &me, &P);

    // Verification
    if (me != rang || P != nproc)
    {
	printf("P%d : ERREUR, me = %d, P = %d\n", rang, me, P);
    }
    else
    {
	printf("P%d/%d : SUCCES\n", rang, P);
    }

    MPI_Finalize();

    return 0;
}

