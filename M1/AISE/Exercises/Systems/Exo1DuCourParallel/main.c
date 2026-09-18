// gcc -o main main.c -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_func(void *arg) {
    int *val = (int *)arg;
    (*val)++;
    printf("Numéro de fils d'excution: %d\n", *val - 1);
    return NULL;
}

int main(int argc, char **argv) {
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    pthread_t tids[N];
    int val = 0;

    for (int i = 0; i <= N; i++) {
        pthread_create(&tids[i], NULL, thread_func, &val);
    }
    
    for (int i = 0; i <= N; i++) {
        pthread_join(tids[i], NULL);
    }

    return 0;
}