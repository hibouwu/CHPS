#include <stdio.h>

int main(int argc, char **argv)
{
    printf("Section séquentielle\n");
#pragma omp parallel
    {
        printf("Dans la région parallèle\n");
    }
    printf("Autre section séquentielle\n");

    return 0;
}
