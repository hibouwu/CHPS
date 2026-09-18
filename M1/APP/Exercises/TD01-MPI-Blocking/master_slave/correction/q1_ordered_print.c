#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mpi.h>

#define TAG_READY   1000

int main(int argc, char **argv)
{
  int rank, nproc;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);

  if (rank == 0)
  {
    MPI_Status sta;

    for(int islv = 0 ; islv < nproc-1 ; islv++)
    {
      // Se mettre en attente du premier processus qui a terminé
      MPI_Recv(NULL, 0, MPI_BYTE, MPI_ANY_SOURCE, TAG_READY, MPI_COMM_WORLD, &sta);

      int slave_rank = sta.MPI_SOURCE;
      printf("Rank 0 : terminaison du processus %d\n", slave_rank);
    }
  }
  else
  {
    // Tout processus autre que 0 attend un temps tiré au hasard
    // int duration = 1000000; /* 1 s */
    int duration =  100000; /* 0.1 s */
    // int duration =   10000; /* 0.01 s */
    srand((rank+1)*time(NULL));
    int ndur = (rand() % 100)+1;
    usleep(ndur*duration);
    printf("Rank %d a attendu %.1f s\n", rank, (ndur*duration)/1e6);

    /* On envoit un message à 0 pour indiquer que je suis dispo
       Le message est vide mais il existe bel et bien (entête du message).
       Ce qui compte c'est la présence d'un message avec l'étiquette TAG_READY et non le contenu du message
       */
    MPI_Send(NULL, 0, MPI_BYTE, 0, TAG_READY, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}

