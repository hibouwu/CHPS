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
#pragma omp master
        {
            printf("Thread %d est le master et attend 5 secondes\n", trank); fflush(stdout);
            sleep(5);
        }

        printf("Thread %d avant single\n", trank); fflush(stdout);
#pragma omp single
        {
            printf("Un seul thread (ici %d) entre dans le single et attend 10s, les autres threads attendent en fin de single\n", trank); fflush(stdout);
            sleep(10);
            printf("\n"); fflush(stdout);
        }

        printf("Thread %d après single\n", trank); fflush(stdout);
    }
    printf("Autre section séquentielle\n");

    return 0;
}
