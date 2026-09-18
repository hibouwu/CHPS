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
    int max_loc;
};

void *max_tab_mt(void *ptr_args)
{
    struct max_args_t *args = (struct max_args_t *)ptr_args;

    args->max_loc = max_seq(args->tab, args->nelt);

    return NULL;
}

int main(int argc, char **argv)
{
    int nthreads, nelt, i, t, maxv_seq, maxv_mt, ideb, ifin, nloc, Q, R;
    int *tab;
    pthread_t *tid;
    struct max_args_t *all_args;

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

    /* Recherche du max de tab en contexte multithread => maxv_mt*/
    Q = nelt / nthreads;
    R = nelt % nthreads;

    ideb = 0;

    for( t = 0 ; t < nthreads ; t++ )
    {
        nloc = (t < R ? Q+1 : Q);
        ifin = ideb + nloc;

        all_args[t].tab  = tab + ideb;
        all_args[t].nelt = nloc;

        pthread_create(tid+t, NULL, max_tab_mt, all_args+t);

        ideb = ifin;
    }

    /* Recherche du max en sequentiel pour verification => maxv_seq */
    maxv_seq = max_seq(tab, nelt);

    maxv_mt = 0;
    for( t = 0 ; t < nthreads ; t++ )
    {
        pthread_join(tid[t], NULL);

        if (all_args[t].max_loc > maxv_mt)
        {
            maxv_mt = all_args[t].max_loc;
        }
    }

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

