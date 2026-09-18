#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, P, val_to_send, i;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &P);

    /* Chaque processus a une valeur propre qu'il doit 
       envoyer à tous les autres processus
       La valeur du processus i va dans la case all_vals[i]
     */
    int all_vals[P];

    val_to_send = rank;

    /* Pour une meme sequence d'appel à MPI_Bcast les racines n'etaient pas les memes
       En outre, des appels successifs à MPI_Bcast n'etaient pas la solution 
       la plus efficace.
       Un appel a MPI_Allgather est approprie ici.
     */
    MPI_Allgather(
            &val_to_send, 1, MPI_INT,
            all_vals, 1, MPI_INT,
            MPI_COMM_WORLD);

    printf("P%02d = ", rank);
    for(i = 0 ; i < P ; i++)
    {
        printf("%d ", all_vals[i]);
    }
    printf("\n"); fflush(stdout);

    MPI_Finalize();

    return 0;
}

