#include <stdio.h>
#include <mpi.h>

/* piegeC piegeC piegeC piegeC */

void piegeC(int rang)
{
    char c;

    if (rang == 0)
    {
        c = 'A';
        MPI_Send(&c, 1, MPI_CHAR, 1, 1000, MPI_COMM_WORLD);
    }
    else if (rang == 1)
    {
        /* ERREUR : LE PROCESSUS DE RANG 0 ENVOIE UN MESSAGE AU PROCESSUS DE RANG 1 
           ET CE DERNIER SE PREPARE A LE RECEVOIR.
           MAIS LES TAGS DU MESSAGE ENVOYE (1000) NE CORRESPOND PAS A CELUI A RECEVOIR (2000) */
        MPI_Recv(&c, 1, MPI_CHAR, 0, 2000, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%c\n", c);
    }
}

void correctionC(int rang)
{
    char c;

    if (rang == 0)
    {
        c = 'A';
        MPI_Send(&c, 1, MPI_CHAR, 1, 1000, MPI_COMM_WORLD);
    }
    else if (rang == 1)
    {
        /* CORRECTION : LES MESSAGES ENVOYE/RECU ONT LE MEME TAG (1000) */
        MPI_Recv(&c, 1, MPI_CHAR, 0, 1000, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%c\n", c);
    }
}

int main(int argc, char **argv)
{
    int rang;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    correctionC(rang);

    MPI_Finalize();

    return 0;
}

