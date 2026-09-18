#include <stdio.h>
#include <mpi.h>

/* piegeA piegeA piegeA piegeA */

void piegeA(int rang)
{
    int i, n = 10;

    if (rang == 0)
    {
        int tab[n];

        for(i = 0 ; i < n ; i++)
        {
            tab[i] = i;
        }

        MPI_Send(tab, n, MPI_INT, /*dest=*/1, /*tag=*/1000, MPI_COMM_WORLD);
    }
    else if (rang == 1)
    {
        int recue;

        /* ERREUR : LA RECEPTION D'UN ENVOI NE PEUT PAS SE FAIRE EN PLUSIEURS RECEPTIONS
           MEME SI LA SOMME DES TAILLES DES DONNEES A RECEVOIR EST EGALE A CELLE DES DONNEES ENVOYEES */
        for(i = 0 ; i < n ; i++)
        {
            MPI_Recv(&recue, 1, MPI_INT, /*src=*/0,  /*tag=*/1000, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%d\n", recue);
        }
    }
}

void correctionA(int rang)
{
    int i, n = 10;
    int tab[n];

    if (rang == 0)
    {
        for(i = 0 ; i < n ; i++)
        {
            tab[i] = i;
        }

        MPI_Send(tab, n, MPI_INT, /*dest=*/1, /*tag=*/1000, MPI_COMM_WORLD);
    }
    else if (rang == 1)
    {
        /* CORRECTION : UNE SEULE INSTRUCTION DE RECEPTION POUR UN SEUL ENVOI */
        MPI_Recv(tab, n, MPI_INT, /*src =*/0, /*tag=*/1000, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for(i = 0 ; i < n ; i++)
        {
            printf("%d\n", tab[i]);
        }
    }
}

int main(int argc, char **argv)
{
    int rang;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    correctionA(rang);

    MPI_Finalize();

    return 0;
}

