#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, P, root;
    int val_to_recv;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &P);

    root = 0;

    /* Le processus root cree autant d'entiers qu'il y a
       de processus et distribue une valeur differente a chaque processus
       */
    if (rank == root)
    {
        int vals_to_distrib[P];
        int i;

        for(i = 0 ; i < P ; i++)
        {
            vals_to_distrib[i] = i;
        }

        /* Il ne faut pas mettre la taille du tableau a distribuer
           mais le nb d'elements à envoyer à chaque processus (ici 1 entier)
         */
        MPI_Scatter(
                vals_to_distrib, 1, MPI_INT,
                &val_to_recv, 1, MPI_INT,
                root, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Scatter(
                NULL, 0, MPI_INT,
                &val_to_recv, 1, MPI_INT,
                root, MPI_COMM_WORLD);
    }

    printf("P%d, val_to_recv = %d\n", rank, val_to_recv);

    MPI_Finalize();

    return 0;
}

