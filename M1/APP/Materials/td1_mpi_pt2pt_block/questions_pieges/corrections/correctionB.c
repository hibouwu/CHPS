#include <stdio.h>
#include <mpi.h>

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
        /* ERREUR : LE PROCESSUS DE RANG 1 ATTEND UN MESSAGE DU PROCESSUS DE RANG 1
           ET NON DU PROCESSUS DE RANG 0 (UNE ERREUR DE COPIER-COLLER COMMUNE) */
        MPI_Recv(&c, 1, MPI_CHAR, 1, 1000, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%c\n", c);
    }
}

void correctionB(int rang)
{
    char c;

    if (rang == 0)
    {
        c = 'A';
        MPI_Send(&c, 1, MPI_CHAR, 1, 1000, MPI_COMM_WORLD);
    }
    else if (rang == 1)
    {
        /* CORRECTION : LE PROCESSUS DE RANG 1 ATTEND BIEN UN MESSAGE DU PROCESSUS DE RANG 0 */
        MPI_Recv(&c, 1, MPI_CHAR, 0, 1000, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%c\n", c);
    }
}

int main(int argc, char **argv)
{
    int rang;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    correctionB(rang);

    MPI_Finalize();

    return 0;
}

