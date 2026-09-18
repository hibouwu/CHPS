#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, vois, to_send, to_recv;
    MPI_Request req[2];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank <=1 )
    {
        vois = (rank + 1) % 2;

        to_send = rank;

        MPI_Issend(&to_send, 1, MPI_INT, vois, 1000, MPI_COMM_WORLD, req+0);
        MPI_Irecv (&to_recv, 1, MPI_INT, vois, 1000, MPI_COMM_WORLD, req+1);
        MPI_Waitall(2, req, MPI_STATUSES_IGNORE);

        printf("P%d : received value from P%d = %d\n", rank, vois, to_recv);
    }

    MPI_Finalize();
    return 0;
}

