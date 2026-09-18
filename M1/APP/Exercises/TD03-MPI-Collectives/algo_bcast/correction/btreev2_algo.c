#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

struct bcast_info_s
{
    int nproc;
    int log2_nproc;
    int rank;
};
typedef struct bcast_info_s bcast_info_t;

void init_bcast_info(int nproc, int rank, bcast_info_t *binfo)
{
    binfo->nproc = nproc;
    binfo->rank  = rank;

    /* Calcul de la plus petite puissance de 2 supérieure ou egale a nproc */
    int tmp = nproc >> 1;
    int p2 = 0;
    while(tmp > 0)
    {
        tmp = tmp >> 1;
        p2++;
    }
    binfo->log2_nproc = ((1 << p2) == nproc ? p2 : p2+1);
}

void btreev2_bcast(char *buf, int n, bcast_info_t *binfo)
{
    int tag, i;
    int two_pi, two_pim1, src, dest;

    tag = 0;

    for(i = binfo->log2_nproc ; i > 0 ; i--)
    {
        two_pi   = 1 << i;
        two_pim1 = 1 << i-1;

        dest = -1;
        if (binfo->rank % two_pi == 0)
        {
            dest = binfo->rank + two_pim1;
            dest = (dest < binfo->nproc ? dest : -1); /* blindage pour les cas ou nproc n'est pas une puissance de 2 */
        }

        src = -1;
        /* on verifie que la source obeit au critere d'envoi */
        if ((binfo->rank - two_pim1) >= 0 && (binfo->rank - two_pim1) % two_pi == 0)
        {
            src = binfo->rank - two_pim1;
        }

        if (dest >= 0)
        {
            MPI_Send(buf, n, MPI_BYTE, dest, tag+i, MPI_COMM_WORLD);
        }
        else if (src >= 0)
        {
            MPI_Recv(buf, n, MPI_BYTE, src, tag+i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

    }
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
    int rank, iter, nproc;
    char *buf;
    double tend, tbeg;
    bcast_info_t binfo;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    buf = (char*)malloc(n*sizeof(char));

    if (rank == /*root=*/0)
    {
        printf("%d bytes\n", n);
        fflush(stdout);
        fill_buf(buf, n);
    }

    init_bcast_info(nproc, rank, &binfo);

    tbeg = MPI_Wtime();

    for(iter = 0 ; iter < NITER ; iter++)
    {
        btreev2_bcast(buf, n, &binfo);
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

