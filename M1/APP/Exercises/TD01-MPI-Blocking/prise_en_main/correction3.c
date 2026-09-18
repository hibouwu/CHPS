#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {

    int rang, P, len, ma_var;
    pid_t pid;
    char str_host[MPI_MAX_PROCESSOR_NAME];

    printf("Avant MPI_Init\n");
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    MPI_Comm_size(MPI_COMM_WORLD, &P);

    MPI_Get_processor_name(str_host, &len);
    pid = getpid();
    printf("%d, %d, %s, pid=%d addr(ma_var)=%p\n", rang, P, str_host, pid, &ma_var);

    MPI_Finalize();

    return 0;
}

