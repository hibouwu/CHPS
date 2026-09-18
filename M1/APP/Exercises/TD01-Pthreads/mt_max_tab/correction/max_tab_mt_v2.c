#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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
    int *tab;
    int nelt;
    pthread_mutex_t *p_mut_max;
    int *p_max_mt; // adresse vers une variable partagée à mettre à jour
};

void *max_tab_mt(void *ptr_args)
{
    struct max_args_t *args = (struct max_args_t *)ptr_args;
    int max_loc;

    /* On recherche le max sur les donnees locales => max_loc */
    max_loc = max_seq(args->tab, args->nelt);

    /* A present on met a jour la variable partagee : un seul thread a la fois peut le faire */
    pthread_mutex_lock(args->p_mut_max);

    if (max_loc > *(args->p_max_mt))
    {
        *(args->p_max_mt) = max_loc;
    }

    pthread_mutex_unlock(args->p_mut_max);

    return NULL;
}

int main(int argc, char **argv)
{
    int nthreads, nelt, i, t, maxv_seq, maxv_mt, ideb, nloc, Q, R;
    int *tab;
    pthread_t *tid;
    struct max_args_t *all_args;
    pthread_mutex_t mut_max = PTHREAD_MUTEX_INITIALIZER;

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

    /* Recherche du max de tab en contexte multithread => maxv_mt */
    Q = nelt / nthreads;
    R = nelt % nthreads;

    maxv_mt = 0;
    ideb = 0;

    for( t = 0 ; t < nthreads ; t++ )
    {
        nloc = (t < R ? Q+1 : Q);

        all_args[t].tab       = tab + ideb;
        all_args[t].nelt      = nloc;
        all_args[t].p_mut_max = &mut_max;
        all_args[t].p_max_mt  = &maxv_mt;

        pthread_create(tid+t, NULL, max_tab_mt, all_args+t);

        ideb += nloc;
    }

    /* Recherche du max en sequentiel pour verification => maxv_seq */
    maxv_seq = max_seq(tab, nelt);

    for( t = 0 ; t < nthreads ; t++ )
    {
        pthread_join(tid[t], NULL);
    }

    /* Un fois que tous les threads ont termines, maxv_mt est a jour */

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

    free(tab);
    free(tid);
    free(all_args);

    return 0;
}

