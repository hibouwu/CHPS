#include <stdio.h>
#include <mpi.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    int rank;
    FILE *fd;
    char file_name[64];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* Le processus de rang 0 cree le repertoire REP_COMMUN
       et les autres processus doivent attendre sa creation pour creer 
       chacun un fichier REP_COMMUN/trace.P<rank>
     */
    if (rank == 0)
    {
        int res;
        res = mkdir("REP_COMMUN", 0700);
    }

    /* Tous les processus attendent, y compris le rang 0,
       une operation collective doit etre appelee par TOUS
       les processus du communicateur
     */
    MPI_Barrier(MPI_COMM_WORLD);

    sprintf(file_name, "REP_COMMUN/trace.P%d", rank);
    fd = fopen(file_name, "w");

    fprintf(fd, "Processus %d\n", rank);

    fclose(fd);

    MPI_Finalize();

    return 0;
}

