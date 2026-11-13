#include <mpi.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

char buffer[100];


void elapsedTimeToString(char *output, size_t size) {
    static clock_t start_time = 0;

    if (start_time == 0) {
        // Enregistrez le temps de démarrage lors de la première invocation
        start_time = clock();
    }

    // Calculez le temps écoulé depuis le démarrage du programme
    clock_t current_time = clock();
    double elapsed_time = ((double)(current_time - start_time)) / CLOCKS_PER_SEC;

    // Écrivez le temps écoulé dans la chaîne de texte
    snprintf(output, size, "Temps écoulé : %.2f secondes", elapsed_time);
}


int writeToFile(const char* text) {
    FILE *file;

    // Ouverture du fichier en mode écriture (efface le contenu existant)
    file = fopen("/tmp/output.txt", "a");

    // Vérifier si l'ouverture du fichier a réussi
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Écriture dans le fichier
    fprintf(file, "%s", text);

    // Fermeture du fichier
    fclose(file);

    printf("Données écrites dans le fichier avec succès.\n");

    return 0;
}


void handle_sigterm(int signum) {
    printf("Received SIGTERM (%d).\n", signum);
    snprintf(buffer,sizeof(buffer), "Received SIGTERM (%d).\n",signum);
    writeToFile(buffer);
    elapsedTimeToString(buffer, sizeof(buffer));
    writeToFile(buffer);    
    // Ajoutez ici le code de nettoyage ou de gestion du signal SIGKILL

    // Exemple : Fermez les fichiers, libérez la mémoire, etc.
    // ...

    // Terminez proprement le programme
    exit(EXIT_SUCCESS);
}

void handle_sigint(int signum) {
    printf("Received SIGINT (%d).\n", signum);
    snprintf(buffer,sizeof(buffer), "Received SIGINT (%d).\n",signum);
    writeToFile(buffer);
    elapsedTimeToString(buffer, sizeof(buffer));
    writeToFile(buffer);
    exit(EXIT_SUCCESS); 
}

int main() {
    // Installez le gestionnaire de signal pour SIGKILL
    elapsedTimeToString(buffer, sizeof(buffer));
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
    printf("Le programme est en cours d'exécution. PID: %d\n", getpid());

    // Simulation d'une tâche en cours d'exécution
    while (1) {
        // Votre code ici...

        // Ajoutez une pause pour éviter une utilisation intensive du processeur
        sleep(1);
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}

