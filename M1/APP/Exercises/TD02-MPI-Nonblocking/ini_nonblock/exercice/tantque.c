#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

void work(int iter)
{
    sleep(iter);
}

int main(int argc, char **argv)
{
    int rank, nsecs, niter;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        nsecs = 10;
        sleep(nsecs);

        /* TRAVAIL A FAIRE
           Envoyer nsecs au processus 1
         */
    }
    else if (rank == 1)
    {
        niter = 0;
        /* TRAVAIL A FAIRE

           Tant qu'on n'a pas recu nsecs de P0 :
               
               niter++;
               work(niter);
           */

        printf("Nsecs = %d s  / Nb iter = %d\n", nsecs, niter);
    }

    MPI_Finalize();
    return 0;
}

