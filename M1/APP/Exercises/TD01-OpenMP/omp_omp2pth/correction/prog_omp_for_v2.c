#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int N = atoi(argv[1]);
    int sum = 0;

#pragma omp parallel shared(sum,N)
    {
        int i;

#pragma omp master
        {
            printf("Je suis le maitre !\n");
        }

#pragma omp for schedule(static) reduction(+:sum)
        for(i = 0 ; i < N ; i++)
        {
            sum += i;
        }
    }

    printf("sum = %d\n", sum);

    return 0;
}

