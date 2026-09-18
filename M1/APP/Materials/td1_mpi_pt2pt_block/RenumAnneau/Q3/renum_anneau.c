#include <stdio.h>
#include <assert.h>
#include <mpi.h>

int numerotation(int me_old, int ouest, int est)
{
    int me, tmp, tag = 1000;
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
    me = numerotation(me, ouest, est);

    // Verification
    if (me != rang)
    {
	printf("P%d : ERREUR, me = %d\n", rang, me);
    }
    else
    {
	printf("P%d/%d : SUCCES\n", rang, nproc);
    }

    MPI_Finalize();

    return 0;
}

