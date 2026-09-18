#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
    int N = 1000000;
    double *arr = new double[N];

    double tbeg = omp_get_wtime();
    double sum = 0;
#pragma omp parallel for shared(N) reduction(+:sum)
    for(int i = 0 ; i < N ; i++)
    {
        arr[i] = i/2.;
        sum += arr[i];
    }
    double tend = omp_get_wtime();
    printf("Telaps = %g s, sum = %f\n", tend - tbeg, sum);

    delete[] arr;

    return 0;
}
