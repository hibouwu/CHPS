#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    printf("Section séquentielle\n");
#pragma omp parallel
    {
        int trank = omp_get_thread_num();
        int tsec = rand() % 5;
#pragma omp critical
        {
            printf("Thread %d est dans la section critique et attend %d s\n", trank, tsec); fflush(stdout);
            sleep(tsec);
        }
    }
    printf("Autre section séquentielle\n");

    return 0;
}
