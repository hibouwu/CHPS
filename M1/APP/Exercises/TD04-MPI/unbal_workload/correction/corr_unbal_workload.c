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
  int rank, is_completed; 
  int niter, local_wl, local_wlr, global_wl, goal_wl, is_over;
  MPI_Request req;

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

//  srand(time(NULL)+rank);
  srand(1+rank);

  niter = 0;
  local_wl = 0;
  global_wl = 0;

  is_over = /*false*/0;
  req = MPI_REQUEST_NULL;

  double tbeg = MPI_Wtime();

  while(!is_over)
  {
    niter++;

    // Pendant que la réduction se déroule, on peut travailler
    int wl = work();
    local_wl += wl;

    // La requete de réduction est-elle terminée ?
    MPI_Test(&req, &is_completed, MPI_STATUS_IGNORE);

    if (is_completed)
    {
        // Si on est ICI, c'est que tous les procesus ont contribué 
        // à la somme globale global_wl, on peut donc lire cette variable

        if (global_wl<goal_wl)
        {
            printf("P%d, !is_over: global_wl(=%d)<goal_wl(=%d) (local_wl=%d) in %d iterations\n",
                    rank, global_wl, goal_wl, local_wl, niter);
            // ICI, le critère d'arrêt n'est pas satisfait
            is_over = /*false*/0;

            // Depuis la précédente réduction, local_wl a augmenté,
            // il faut remettre à jour la nouvelle somme global_wl
            // la variable local_wlr ne sera pas modifiée entre cet
            // appel à MPI_Iallreduce et le MPI_Test à true
            local_wlr = local_wl; 
            MPI_Iallreduce(&local_wlr, &global_wl, 1, MPI_INT,
                    MPI_SUM, MPI_COMM_WORLD, &req);
        }
        else
        {
            is_over = /*true*/1;
        }
    }
  }

  double telaps = MPI_Wtime() - tbeg;

  printf("P%d, global_wl(=%d)>=goal_wl(=%d) (local_wl=%d) in %d iterations Telaps=%g s\n",
      rank, global_wl, goal_wl, local_wl, niter, telaps);

  MPI_Finalize();
  return 0;
}

