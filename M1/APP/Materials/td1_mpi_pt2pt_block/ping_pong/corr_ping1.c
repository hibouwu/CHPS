#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rk, jeton, tag1;
    MPI_Status sta;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rk);

    // 这个小程序只考虑 2 个进程：P0 -> P1 发送一个整数 10
    tag1 = 1000;
    if (rk == 0)
    {
        jeton = 10;
        // 点对点通信：发送端必须有匹配的接收端，否则通信无法完成
        MPI_Send(&jeton, 1, MPI_INT, 1, tag1, MPI_COMM_WORLD);
    }
    else if (rk == 1)
    {
        // 接收端显式接收来自 P0 的消息
        MPI_Recv(&jeton, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD, &sta);

        printf("Je suis P%d et j'ai recu la valeur %d\n", rk, jeton);
    }

    ADD();

    MPI_Finalize();

    GEMM();

    return 0;
}


