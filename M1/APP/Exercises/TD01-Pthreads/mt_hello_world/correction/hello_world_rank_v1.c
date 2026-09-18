#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_hello(void *ptr_args)
{
    char *str = (char*)ptr_args;
    printf("%s\n", str);

    return NULL;
}

int main(int argc, char **argv)
{
    int nthreads, i, max_len;
    char *all_str;
    pthread_t *tid;

    /* nous sommes dans un thread, le thread maitre ... */

    /* Recuperation du nb de threads (fils) a creer */
    nthreads = atoi(argv[1]);

    tid = (pthread_t*)malloc(nthreads*sizeof(pthread_t));

    max_len = 32;
    all_str = (char*)malloc(nthreads*max_len*sizeof(char));

    /* Creation des threads fils */
    for(i = 0 ; i < nthreads ; i++)
    {
        sprintf(all_str+i*max_len, "Hello World ! %d", i+1);
        pthread_create(tid+i, NULL, print_hello, all_str+i*max_len);
    }

    /* pendant ce temps les threads crees s'executent ... */

    /* Attente des terminaisons des threads fils */
    for(i = 0 ; i < nthreads ; i++)
    {
        pthread_join(tid[i], NULL);
    }

    free(tid);
    free(all_str);

    return 0;
}

