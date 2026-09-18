#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
    int max_threads = omp_get_max_threads();
    printf("Nb maximal de threads OpenMP dans la future région parallèle : %d\n", max_threads);
    printf("Section séquentielle\n");
#pragma omp parallel
    {
        int trank = omp_get_thread_num();
        int nthreads_in_parallel = omp_get_num_threads();
        printf("Dans la région parallèle, thread %d sur %d\n", trank, nthreads_in_parallel);
    }
    printf("Autre section séquentielle\n");

    return 0;
}
