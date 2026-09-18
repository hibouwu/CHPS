#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_VAL 1000

int max_seq(int *tab, int nelt)
{
    int i, maxv;

    maxv = 0;
    for( i = 0 ; i < nelt ; i++ )
    {
        if (tab[i] > maxv)
        {
            maxv = tab[i];
        }
    }

    return maxv;
}

struct max_args_t
{
    int *tab_loc;
    int nloc;
    sem_t *p_sem;
    int *p_max_glob;
};


void *max_tab_mt(void *ptr_args)
{
    struct max_args_t *args = (struct max_args_t *)ptr_args;
    int i, max_loc;

    /* On recherche le max sur les donnees locales => max_loc */
    max_loc = max_seq(args->tab_loc, args->nloc);

    /* A present on met a jour la variable globale : un seul thread a la fois peut le faire */
    sem_wait(args->p_sem);

    if (max_loc > *(args->p_max_glob))
    {
        *(args->p_max_glob) = max_loc;
    }

    sem_post(args->p_sem);

    return NULL;
}

int main(int argc, char **argv)
{
    int nthreads, nelt, i, t, maxv_seq, maxv_mt, ideb, ifin, nloc, Q, R;
    int *tab;
    pthread_t *tid;
    struct max_args_t *all_args;
    sem_t sem;
    int max_glob;

    sem_init(&sem, /*pshared=*/0, /*value=*/1);

    nelt     = atoi(argv[1]); /* Taille du tableau */
    nthreads = atoi(argv[2]); /* Nombre de threads a creer */

    tid = (pthread_t*)malloc(nthreads*sizeof(pthread_t));
    all_args = (struct max_args_t*)malloc(nthreads*sizeof(struct max_args_t));

    /* Creation du tableau et remplissage aleatoire */
    tab = (int*)malloc(nelt*sizeof(int));

    srand(nelt);
    for( i = 0 ; i < nelt ; i++)
    {
        tab[i] = 1 + (rand() % MAX_VAL);
    }

    /* Recherche du max de tab en contexte multithread => maxv_mt, max_glob */
    Q = nelt / nthreads;
    R = nelt % nthreads;

    max_glob = 0;
    ideb = 0;

    for( t = 0 ; t < nthreads ; t++ )
    {
        nloc = (t < R ? Q+1 : Q);
        ifin = ideb + nloc;

        all_args[t].tab_loc    = tab+ideb;
        all_args[t].nloc       = nloc;
        all_args[t].p_sem      = &sem;
        all_args[t].p_max_glob = &max_glob;

        pthread_create(tid+t, NULL, max_tab_mt, all_args+t);

        ideb = ifin;
    }

    /* Recherche du max en sequentiel pour verification => maxv_seq */
    maxv_seq = max_seq(tab, nelt);

    for( t = 0 ; t < nthreads ; t++ )
    {
        pthread_join(tid[t], NULL);
    }

    /* Un fois que tous les threads ont termines, max_glob est a jour */
    maxv_mt = max_glob;

    if (maxv_seq == maxv_mt)
    {
        printf("PASSED\n");
    }
    else
    {
        printf("FAILED\n");
        printf("Valeur correcte : %d\n", maxv_seq);
        printf("Votre valeur    : %d\n", maxv_mt);
    }

    sem_destroy(&sem);

    free(tab);
    free(tid);
    free(all_args);

    return 0;
}

