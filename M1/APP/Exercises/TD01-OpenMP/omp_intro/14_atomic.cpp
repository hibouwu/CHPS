#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int count = 0;
#pragma omp parallel shared(count)
    {
#pragma omp atomic
        count++;
    }
    printf("count = %d\n", count);

    return 0;
}
