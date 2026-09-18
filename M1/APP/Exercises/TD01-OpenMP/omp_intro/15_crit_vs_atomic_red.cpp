#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
    int N = 1000000;
    double *arr = new double[N];
    double tbeg, tend;
    double sum;

    tbeg = omp_get_wtime();
    sum = 0;
#pragma omp parallel for shared(N) shared(sum)
    for(int i = 0 ; i < N ; i++)
    {
        arr[i] = i/2.;
#pragma omp critical
        sum += arr[i];
    }
    tend = omp_get_wtime();
    printf("Telaps critical  = %.2e s, sum = %f\n", tend - tbeg, sum);

    tbeg = omp_get_wtime();
    sum = 0;
#pragma omp parallel for shared(N) shared(sum)
    for(int i = 0 ; i < N ; i++)
    {
        arr[i] = i/2.;
#pragma omp atomic
        sum += arr[i];
    }
    tend = omp_get_wtime();
    printf("Telaps atomic    = %.2e s, sum = %f\n", tend - tbeg, sum);

    tbeg = omp_get_wtime();
    sum = 0;
#pragma omp parallel for shared(N) reduction(+:sum)
    for(int i = 0 ; i < N ; i++)
    {
        arr[i] = i/2.;
        sum += arr[i];
    }
    tend = omp_get_wtime();
    printf("Telaps reduction = %.2e s, sum = %f\n", tend - tbeg, sum);

    delete[] arr;

    return 0;
}
