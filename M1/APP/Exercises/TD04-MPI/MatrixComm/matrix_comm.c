#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int P, rank;
    int Nib, Njb, ib, jb;

    MPI_Comm comm_row, comm_col;

    MPI_Init(&argc, &argv);

    Nib = atoi(argv[1]);
    Njb = atoi(argv[2]);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &P);

    if (P != Nib*Njb)
    {
        if (rank == 0)
        {
            printf("Nib x Njb = %d x %d != %d processus MPI\n", Nib, Njb, P);
            abort();
        }
    }

    /*
       A ECRIRE : creation communicateurs comm_row et comm_col
     */


    MPI_Finalize();

    return 0;
}

