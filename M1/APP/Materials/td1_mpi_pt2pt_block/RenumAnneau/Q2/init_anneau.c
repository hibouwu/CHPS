#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rang, nproc, est, ouest, me;

    MPI_Init(&argc, &argv);

    /* Initialisation des données du problème
       */
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    est   = (rang+1) % nproc; // 左右环形通信中，东边的进程编号是当前进程编号加1，模上总进程数
    ouest = (rang+nproc-1) % nproc; // 左右环形通信中，西边的进程编号是当前进程编号减1，模上总进程数
    me    = (rang == 0 ? 0 : -1); // 进程0的初始值为0，其他进程的初始值为-1

    printf("P%d : me = %d, ouest = %d, est = %d\n", rang, me, ouest, est);

    MPI_Finalize();

    return 0;
}

