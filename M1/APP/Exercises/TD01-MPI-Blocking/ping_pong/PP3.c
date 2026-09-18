#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rk, jeton, tag1, tag2, i, j, nsec;
    double tabr[10];
    MPI_Status sta;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rk);

    tag1 = 1000;
    tag2 = 1001;
    if (rk == 0)
    {
        jeton = 10;
        MPI_Send(&jeton, 1, MPI_INT, 1, tag1, MPI_COMM_WORLD);
        MPI_Recv(tabr, 10, MPI_DOUBLE, 1, tag2, MPI_COMM_WORLD, &sta);

        printf("\n");
        for(i = 0 ; i < 10 ; i++)
        {
            printf("P%d, tabr[%i] = %.6e\n", rk, i, tabr[i]);
        }
    }
    else if (rk == 1)
    {
        MPI_Recv(&jeton, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD, &sta);

        printf("Je suis P%d et j'ai recu la valeur %d\n", rk, jeton);

        nsec = 5; // on veut attendre 5 secondes en tout
        for(j = 0 ; j < nsec ; j++)
        {
            printf("."); fflush(stdout);
            sleep(1); // attente de 1 seconde
        }
        printf("\n");

        for(i = 0 ; i < 10 ; i++)
        {
            tabr[i] = 1./(1. + (double)i);
        }

        MPI_Send(tabr, 10, MPI_DOUBLE, 0, tag2, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}

