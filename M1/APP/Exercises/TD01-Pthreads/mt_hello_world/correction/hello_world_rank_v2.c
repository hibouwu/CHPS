#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct mes_args_t
{
    char *str;
    int rank;
};

void *print_hello(void *ptr_args)
{
    struct mes_args_t *args = (struct mes_args_t*)ptr_args;
    printf("%s %d\n", args->str, args->rank);

    return NULL;
}

int main(int argc, char **argv)
{
    int nthreads, i;
    struct mes_args_t *all_args;
    pthread_t *tid;

    /* nous sommes dans un thread, le thread maitre ... */

    /* Recuperation du nb de threads (fils) a creer */
    nthreads = atoi(argv[1]);

    tid = (pthread_t*)malloc(nthreads*sizeof(pthread_t));

    all_args = (struct mes_args_t*)malloc(nthreads*sizeof(struct mes_args_t));

    /* Creation des threads fils */
    for(i = 0 ; i < nthreads ; i++)
    {
        all_args[i].str = "Hello World !";
        all_args[i].rank = i+1;

        pthread_create(tid+i, NULL, print_hello, all_args+i);
    }

    /* pendant ce temps les threads crees s'executent ... */

    /* Attente des terminaisons des threads fils */
    for(i = 0 ; i < nthreads ; i++)
    {
        pthread_join(tid[i], NULL);
    }

    free(tid);
    free(all_args);

    return 0;
}

