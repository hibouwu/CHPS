#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {

    int rang, P, len;
    pid_t pid;
    char str_host[MPI_MAX_PROCESSOR_NAME]; // 预分配主机名缓冲区，MPI 会写入名字

    /*
     * MPI_Init 需要传入命令行参数地址（argc/argv），用于解析 mpiexec 传来的 MPI 选项。
     * 初始化 MPI 运行时，建立通信基础设施，并创建初始通信器 MPI_COMM_WORLD。
     */
    MPI_Init(&argc, &argv); // 初始化 MPI 环境

    // MPI_COMM_WORLD：初始通信器，包含同时启动的所有进程
    MPI_Comm_rank(MPI_COMM_WORLD, &rang); // rank 是进程编号（0..P-1）
    MPI_Comm_size(MPI_COMM_WORLD, &P);    // size 是通信器内进程总数

    MPI_Get_processor_name(str_host, &len); // 获取主机名并返回字符串长度
    pid = getpid();                         // OS 进程 pid（与 MPI rank 不同）
    printf("[%d], %d, %s, pid=%d\n", rang, P, str_host, pid);
    printf("[%d], %d, %s, pid=%d\n", rang, P, str_host, pid);
    printf("[%d], %d, %s, pid=%d\n", rang, P, str_host, pid);
    /*
     * MPI_Finalize 负责收尾：完成可能未结束的通信并释放资源。
     * 大型程序必须干净退出，不可省略。
     */
    MPI_Finalize(); // 结束 MPI 环境

    return 0;
}
