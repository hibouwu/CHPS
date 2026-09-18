#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

void mpi_bcast(char *buf, int n)
{
    MPI_Bcast(buf, n, MPI_BYTE, 0, MPI_COMM_WORLD);
}

void fill_buf(char *buf, int n)
{
  for(int i = 0 ; i < n ; i++) {
    buf[i] = (char)i;
  }
}

int check_buf(char *buf, int n)
{
  for(int i = 0 ; i < n ; i++) {
    if (buf[i] != (char)i)
      return 0;
  }
  return 1;
}

#define NITER 100

int main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    int rank, iter;
    char *buf;
    double tend, tbeg;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    buf = (char*)malloc(n*sizeof(char));

    if (rank == /*root=*/0)
    {
        printf("%d bytes\n", n);
        fflush(stdout);
        fill_buf(buf, n);
    }

    tbeg = MPI_Wtime();

    for(iter = 0 ; iter < NITER ; iter++)
    {
        mpi_bcast(buf, n);
    }

    tend = MPI_Wtime();

    if (rank == 0)
    {
        printf("Telaps for %d bcast = %.3e s\n", NITER, tend - tbeg);
    }
    if (!check_buf(buf, n)) {
        printf("Erreur contenu buffer pour processus %d\n", rank);
    }

    free(buf);

    MPI_Finalize();
    return 0;
}

