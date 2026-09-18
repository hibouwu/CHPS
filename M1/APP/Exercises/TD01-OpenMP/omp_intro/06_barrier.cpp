#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    printf("Section séquentielle\n");
#pragma omp parallel
    {
        int tsec = rand() % 5;
        int trank = omp_get_thread_num();
        printf("Thread %d : on va attendre %d seconde(s)\n", trank, tsec); fflush(stdout);
        sleep(tsec);

        printf("Thread %d avant barrière\n", trank); fflush(stdout);
#pragma omp barrier

        printf("Thread %d après barrière\n", trank); fflush(stdout);
    }
    printf("Autre section séquentielle\n");

    return 0;
}
