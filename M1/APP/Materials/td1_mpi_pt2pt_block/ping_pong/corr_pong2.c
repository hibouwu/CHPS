#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rk, tag2, i;
    double tabr[10];
    MPI_Status sta;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rk);

    tag2 = 1001;
    if (rk == 0)
    {
        MPI_Recv(tabr, 10, MPI_DOUBLE, 1, tag2, MPI_COMM_WORLD, &sta);

        for(i = 0 ; i < 10 ; i++)
        {
            printf("P%d, tabr[%i] = %.6e\n", rk, i, tabr[i]);
        }
    }
    else if (rk == 1)
    {
        for(i = 0 ; i < 10 ; i++)
        {
            tabr[i] = 1./(1. + (double)i);
        }

        MPI_Send(tabr, 10, MPI_DOUBLE, 0, tag2, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}

