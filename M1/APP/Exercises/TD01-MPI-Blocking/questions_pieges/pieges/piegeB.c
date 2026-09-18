#include <stdio.h>
#include <mpi.h>

/* piegeB piegeB piegeB piegeB */

void piegeB(int rang)
{
    char c;

    if (rang == 0)
    {
        c = 'A';
        MPI_Send(&c, 1, MPI_CHAR, 1, 1000, MPI_COMM_WORLD);
    }
    else if (rang == 1)
    {
        MPI_Recv(&c, 1, MPI_CHAR, 1, 1000, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%c\n", c);
    }
}

int main(int argc, char **argv)
{
    int rang;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    piegeB(rang);

    MPI_Finalize();

    return 0;
}

