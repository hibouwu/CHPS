#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char **argv)
{
    int nthreads, nelt, i, t, maxv_seq, maxv_mt;
    int *tab;

    nelt     = atoi(argv[1]); /* Taille du tableau */
    nthreads = atoi(argv[2]); /* Nombre de threads a creer */

    /* Creation du tableau et remplissage aleatoire */
    tab = (int*)malloc(nelt*sizeof(int));

    srand(nelt);
    for( i = 0 ; i < nelt ; i++)
    {
	tab[i] = 1 + (rand() % MAX_VAL);
    }

    /* Recherche du max de tab en contexte multithread => maxv_mt*/
    maxv_mt = 0;
    /* A ECRIRE */

    /* Recherche du max en sequentiel pour verification => maxv_seq */
    maxv_seq = max_seq(tab, nelt);

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

    return 0;
}

