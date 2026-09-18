#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Un travail qui dure aléatoirement de 1s à 10s
int work()
{
  int wl = rand()%10;
  if (wl == 0)
    wl = 1;
  sleep(wl);
  return wl;
}

int main(int argc, char **argv)
{
  int rank; 
  int niter, local_wl, global_wl, goal_wl, is_over;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (argc != 2)
  {
    if (rank == 0)
      printf("Usage %s <WorkLoadInSecondsAsInt>\n", argv[0]);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  goal_wl = atoi(argv[1]);
  if (rank == 0)
    printf("Objective workload = %d\n", goal_wl);

  srand(1+rank);

  niter = 0;
  local_wl = 0;
  global_wl = 0;

  is_over = /*false*/0;

  double tbeg = MPI_Wtime();

  while(!is_over)
  {
    // Travail local
    int wl = work();
    local_wl += wl;

    // Pour obtenir la somme de tous les local_wl
    MPI_Allreduce(&local_wl, &global_wl, 1, MPI_INT,
            MPI_SUM, MPI_COMM_WORLD);

    // Critère d'arrêt
    is_over = !(global_wl<goal_wl);

    niter++;

    if (!is_over) {
        printf("P%d, !is_over: global_wl(=%d)<goal_wl(=%d) (local_wl=%d) in %d iterations\n",
                rank, global_wl, goal_wl, local_wl, niter);
    }
  }

  double telaps = MPI_Wtime() - tbeg;

  printf("P%d, global_wl(=%d)>=goal_wl(=%d) (local_wl=%d) in %d iterations Telaps=%g s\n",
      rank, global_wl, goal_wl, local_wl, niter, telaps);

  MPI_Finalize();
  return 0;
}

