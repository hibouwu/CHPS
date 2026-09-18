#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
    printf("Section séquentielle\n");
#pragma omp parallel
    {
        int trank = omp_get_thread_num();
        printf("Dans la région parallèle, thread %d\n", trank);
    }
    printf("Autre section séquentielle\n");

    return 0;
}
