#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {

    int rang, P, len, ma_var;
    pid_t pid;
    char str_host[MPI_MAX_PROCESSOR_NAME];

    /*
     * 并行从程序第一条指令就开始，每个进程都会执行到这里，
     * 所以 "Avant MPI init" 的打印次数=进程数，不是 1 次。
     */
    printf("Avant MPI init addr(ma_var)=%p\n", &ma_var);
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    MPI_Comm_size(MPI_COMM_WORLD, &P);

    MPI_Get_processor_name(str_host, &len);
    pid = getpid();

    /*
     * 每个进程是独立的 OS 进程（pid 不同），各自拥有独立地址空间，
     * 因此 ma_var 的地址在不同进程中不同；重新运行程序地址也可能变化。
     * 变量同名不意味着共享，进程间必须通过 MPI 消息传递交换数据。
     */
    printf("[%d], %d, %s, pid=%d addr(ma_var)=%p\n", rang, P, str_host, pid, &ma_var);

    MPI_Finalize();

    return 0;
}

