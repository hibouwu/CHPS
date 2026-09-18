#include <stdio.h>
#include <mpi.h>

/* piegeD piegeD piegeD piegeD */

void piegeD(int rang)
{
    if (rang == 0)
    {
        int i = 1;
        MPI_Send(&i, 1, MPI_INT, 1, 1000, MPI_COMM_WORLD);
    }
    else if (rang == 1)
    {
        /* ERREUR : UN INT EST ENVOYE (PROBABLEMENT 4 OCTETS) MAIS UNE RECEPTION 
           D'UN DOUBLE (PROBABLEMENT 8 OCTETS) EST DEMANDEE.
           LE MPI_Recv N'ECHOUE PAS CAR LA TAILLE DU BUFFER DE RECPETION EST SUPERIEURE 
           AUX DONNEES ENVOYEES (POSSIBLE MAIS DANGEREUX).
           PAS DE CASTING POSSIBLE, LE CONTENU DE LA VARIABLE r EST ERRONNE */
        double r;
        MPI_Recv(&r, 1, MPI_DOUBLE, 0, 1000, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("r = %g\n", r);
    }
}

void correctionD(int rang)
{
    if (rang == 0)
    {
        int i = 1;
        printf("L'autre processus devra afficher la valeur %d\n", i);
        MPI_Send(&i, 1, MPI_INT, 1, 1000, MPI_COMM_WORLD);
    }
    else if (rang == 1)
    {
        /* CORRECTION : LE PROCESSUS DE RANG 1 RECOIT D'ABORD UN ENTIER 
           PUIS EFFECTUE LE CASTING VERS LA VARIABLE r */
        int i;
        double r;
        MPI_Recv(&i, 1, MPI_INT, 0, 1000, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        r = i;
        printf("r = %g\n", r);
    }
}


int main(int argc, char **argv)
{
    int rang;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    correctionD(rang);

    MPI_Finalize();

    return 0;
}

