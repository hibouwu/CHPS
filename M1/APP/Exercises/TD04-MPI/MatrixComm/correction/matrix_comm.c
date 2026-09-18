#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int P, rank;
    int Nib, Njb, ib, jb;
    int mNib, mNjb, mib, mjb;

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
    ib = rank / Njb;
    jb = rank % Njb;

    MPI_Comm_split(MPI_COMM_WORLD, /*color=*/ib, /*key=*/rank, &comm_col);
    MPI_Comm_split(MPI_COMM_WORLD, /*color=*/jb, /*key=*/rank, &comm_row);

    MPI_Comm_size(comm_row, &mNib);
    MPI_Comm_size(comm_col, &mNjb);

    MPI_Comm_rank(comm_row, &mib);
    MPI_Comm_rank(comm_col, &mjb);

    printf("P%02d : (ib=%d, jb=%d) in [0, %d[x[0, %d[ : (mib=%d, mjb=%d) in [0, %d[x[0, %d[\n",
            rank, ib, jb, Nib, Njb, mib, mjb, mNib, mNjb);
    if (
            (ib != mib)   ||
            (jb != mjb)   ||
            (Nib != mNib) ||
            (Njb != mNjb)
            )
    {
        printf("Erreur pour processus P%d\n", rank);
    }

    MPI_Finalize();

    return 0;
}

