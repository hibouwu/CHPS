#include <stdio.h>
#include <mpi.h>

/* piegeD piegeD piegeD piegeD */

void piegeD(int rang)
{
    if (rang == 0)
    {
        int i = 1;
        printf("L'autre processus devra afficher la valeur %d\n", i);
        MPI_Send(&i, 1, MPI_INT, 1, 1000, MPI_COMM_WORLD);
    }
    else if (rang == 1)
    {
        double r;
        MPI_Recv(&r, 1, MPI_DOUBLE, 0, 1000, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("r = %g\n", r);
    }
}

int main(int argc, char **argv)
{
    int rang;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    piegeD(rang);

    MPI_Finalize();

    return 0;
}

