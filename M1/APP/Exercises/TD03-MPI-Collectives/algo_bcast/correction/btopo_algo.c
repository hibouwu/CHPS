#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

struct hierarch_info_s
{
    int level;
    int nproc;
    int rank;
    MPI_Comm comm;
};
typedef struct hierarch_info_s hierarch_info_t;

struct bcast_info_s
{
    hierarch_info_t global;
    hierarch_info_t intra_node;
    hierarch_info_t inter_node;
};
typedef struct bcast_info_s bcast_info_t;

/* Calcul de la plus petite puissance de 2 supérieure ou egale a number */
int calc_puiss2(int number)
{
    /* Calcul de la plus petite puissance de 2 supérieure ou egale a number */
    int tmp = number >> 1;
    int p2 = 0;
    while(tmp > 0)
    {
        tmp = tmp >> 1;
        p2++;
    }
    int log2_number = ((1 << p2) == number ? p2 : p2+1);

    return log2_number;
}

void init_bcast_info(int nproc, int rank, bcast_info_t *binfo)
{
    binfo->global.level = 0;
    binfo->global.nproc = nproc;
    binfo->global.rank  = rank;
    binfo->global.comm  = MPI_COMM_WORLD;


    /* Tous les processus qui appartiendront au meme
     * communicateur binfo->intra_node.comm
     * sont sur le meme noeud de calcul */
    MPI_Comm_split_type(binfo->global.comm, MPI_COMM_TYPE_SHARED, binfo->global.rank, MPI_INFO_NULL, &(binfo->intra_node.comm));
    MPI_Comm_rank(binfo->intra_node.comm, &(binfo->intra_node.rank));
    MPI_Comm_size(binfo->intra_node.comm, &(binfo->intra_node.nproc));
    binfo->intra_node.level = 2;

    /* Par noeud on designe un "master"
     * C'est le processus de rang 0 du communicateur intra_node.comm
     */
    int is_master_in_node = (binfo->intra_node.rank == 0);

    /* On va construire binfo_>inter_node.comm :
     *    - MPI_COMM_NULL si le processus n'est pas un "master" d'un noeud
     *    - le communicateur de tous les masters si le processus est un "node master"
     */
    int master_color = (is_master_in_node ? 1 : MPI_UNDEFINED);
    MPI_Comm_split(binfo->global.comm, master_color, binfo->global.rank, &(binfo->inter_node.comm));

    binfo->inter_node.level = 1;
    if (is_master_in_node)
    {
        MPI_Comm_rank(binfo->inter_node.comm, &(binfo->inter_node.rank));
        MPI_Comm_size(binfo->inter_node.comm, &(binfo->inter_node.nproc));
    }
    else
    {
        binfo->inter_node.rank  = -1;
        binfo->inter_node.nproc =  0;
    }

    /* Par construction chaque maitre doit avoir le rang 0 a chaque niveau hierarchique 
     * (ici inter-noeud avec inter_node.comm et intra-noeud avec intra_node.comm)
     */
    if (binfo->global.rank == 0 && binfo->inter_node.rank != 0)
    {
        printf("Le processus de rang 0 n'est pas le processus de rang 0 de tous les maitres (inter_node.rank=%d)\n", binfo->inter_node.rank);
        MPI_Abort(binfo->global.comm, 1);
    }

    if (is_master_in_node && binfo->intra_node.rank != 0)
    {
        printf("Un \"node master\" doit avoir le rang 0 dans son propre noeud (intra_node.rank=%d)\n", binfo->intra_node.rank);
        MPI_Abort(binfo->global.comm, 1);
    }

    /*
    printf("Rank=%02d  intra_node.rank=%02d   inter_node.rank=%2d\n", 
            binfo->global.rank, binfo->intra_node.rank, binfo->inter_node.rank); 
            */
}

void btreev2_bcast_comm(char *buf, int n, hierarch_info_t *hinfo)
{
    int tag, i;
    int two_pi, two_pim1, src, dest;
    int log2_nproc;

    tag = 1000 * hinfo->level;

    log2_nproc = calc_puiss2(hinfo->nproc);

    for(i = log2_nproc ; i > 0 ; i--)
    {
        two_pi   = 1 << i;
        two_pim1 = 1 << i-1;

        dest = -1;
        if (hinfo->rank % two_pi == 0)
        {
            dest = hinfo->rank + two_pim1;
            dest = (dest < hinfo->nproc ? dest : -1); /* blindage pour les cas ou nproc n'est pas une puissance de 2 */
        }

        src = -1;
        /* on verifie que la source obeit au critere d'envoi */
        if ((hinfo->rank - two_pim1) >= 0 && (hinfo->rank - two_pim1) % two_pi == 0)
        {
            src = hinfo->rank - two_pim1;
        }

        if (dest >= 0)
        {
            MPI_Send(buf, n, MPI_BYTE, dest, tag+i, hinfo->comm);
        }
        else if (src >= 0)
        {
            MPI_Recv(buf, n, MPI_BYTE, src, tag+i, hinfo->comm, MPI_STATUS_IGNORE);
        }

    }
}

void btopo_bcast(char *buf, int n, bcast_info_t *binfo)
{
    if (binfo->inter_node.rank >= 0)
    {
        btreev2_bcast_comm(buf, n, &(binfo->inter_node));
    }
    btreev2_bcast_comm(buf, n, &(binfo->intra_node));
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
        btopo_bcast(buf, n, &binfo);
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

