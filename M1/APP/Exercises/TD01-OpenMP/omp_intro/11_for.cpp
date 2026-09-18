#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
    int N = 1000000;
    double *arr = new double[N];

    printf("Section séquentielle\n");
    double tbeg = omp_get_wtime();
#pragma omp parallel shared(N)
    {
        printf("Dans la région parallèle\n");
        for(int k = 0 ; k < 100 ; k++)
        {
#pragma omp for
            for(int i = 0 ; i < N ; i++)
            {
                arr[i] = i/2.;
            }
        }
    }
    double tend = omp_get_wtime();
    printf("Telaps = %g s\n", tend - tbeg);

    delete[] arr;

    return 0;
}
