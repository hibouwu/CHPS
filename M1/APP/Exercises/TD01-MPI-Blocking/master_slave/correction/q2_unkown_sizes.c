#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mpi.h>

#define TAG_DATA    3000

int main(int argc, char **argv)
{
  int rank, nproc, nint;
  int *data = NULL;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);

  if (rank == 0)
  {
    MPI_Status sta;

    for(int islv = 0 ; islv < nproc-1 ; islv++)
    {
      /* 等待来自任意进程的消息。
         由于事先不知道消息大小，因此先使用 MPI_Probe 探测。
         */
      MPI_Probe(MPI_ANY_SOURCE, TAG_DATA, MPI_COMM_WORLD, &sta);

      /* 先把消息大小按“整型个数”取出来保存到 nint，
         然后再正式调用 MPI_Recv 接收消息。
         */
      MPI_Get_count(&sta, MPI_INT, &nint);

      /* 在真正接收之前，先按消息大小分配或调整接收缓冲区。 */
      data = (int*)realloc(data, nint*sizeof(int));

      MPI_Recv(data, nint, MPI_INT, sta.MPI_SOURCE, sta.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      /* 收到消息后，计算数组元素之和并输出。 */
      int sum=0;
      for(int i=0 ; i<nint ; i++) {
        sum += data[i];
      }
      printf("Rank 0 : message reçu de %d (size, sum) = (%d, %d)\n", sta.MPI_SOURCE, nint, sum);
    }
  }
  else
  {
    // 随机生成要发送的消息长度
    srand((rank+1)*time(NULL));
    nint = (rand() % 100)+1;

    data = (int*)malloc(nint*sizeof(int));
    int sum=0;
    for(int i=0 ; i<nint ; i++) {
      data[i] = (rank+1);
      sum += data[i];
    }

    MPI_Send(data, nint, MPI_INT, 0, TAG_DATA, MPI_COMM_WORLD);
    printf("Rank %d : message envoyé à 0 (size, sum) = (%d, %d)\n", rank, nint, sum);
  }

  free(data);

  MPI_Finalize();

  return 0;
}
