#include <mpi.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void handle_sigterm(int signum) {
    printf("Received SIGTERM (%d).\n", signum);
    exit(EXIT_SUCCESS);
}

void handle_sigint(int signum) {
    printf("Received SIGINT (%d).\n", signum);
    exit(EXIT_SUCCESS); 
}

int main() {
    if (signal(SIGTERM, handle_sigterm) == SIG_ERR) {
        perror("Erreur lors de l'installation du gestionnaire de signal");
        return EXIT_FAILURE;
    }
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
       perror("Erreur lors de l'installation du gestionnaire de signal pour SIGINT");
       return EXIT_FAILURE;
    }
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size); 
    printf("Program is running. PID: %d\n", getpid());

    // Simulation d'une tâche en cours d'exécution
    while (1) {
        // Votre code ici...

        // Ajoutez une pause pour éviter une utilisation intensive du processeur
        sleep(1);
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}

