#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>

#define MASTER_RANK 0

void process_data(int slave_rank, int cptr, double *data, int nreal)
{
    double sum = 0.;

    for(int i = 0 ; i < nreal ; i++)
    {
        sum += data[i];
    }

    int duration = 1000000; /* 1 s */
//    int duration =  100000; /* 0.1 s */
//    int duration =   10000; /* 0.01 s */
    usleep(nreal*duration);
    printf("cptr %5d : Slave %d receives nreal = %d from Master ; sum = %.6e\n", cptr, slave_rank, nreal, sum);
}

void run_slave(int slave_rank)
{
    int over = 0;
    int nreal;
    double *data = NULL;

    do
    {
        /* TRAVAIL A FAIRE  */
        /* Attendre un message pour savoir 
              s'il faut traiter le tableau de reels (c-a-d appeler process_data)
              ou bien si le travail de l'esclave est terminé
           */

        /*
           Si il faut traiter un tableau de reels
              Allouer le tableau de reels data a nreals reels double precision
              Recevoir le tableau de reels data
              Appeler process_data(slave_rank, cptr_from_master, data, nreal)

            Sinon 
              Le traitement est termine
              over = 1;
              printf("Slave %d : END\n", slave_rank);
           */
        /* FIN TRAVAIL A FAIRE  */
    }
    while(!over);

    if (data)
    {
        free(data);
    }
}

void read_data(int *p_cptr, double **p_data, int *p_nreal)
{
    if (*p_cptr < 100)
    {
        *p_nreal = 5 + (int)(3*sin(*p_cptr));

        *p_data = (double*)realloc(*p_data, *p_nreal * sizeof(double));

        for(int i = 0 ; i < *p_nreal ; i++)
        {
            (*p_data)[i] = 1. / (1 + *p_cptr + i);
        }

        (*p_cptr)++;
    }
    else
    {
        *p_nreal = 0;
    }
}

void run_master(int nslaves)
{
    int slave_rank = -1;
    double *data = NULL;
    int nreal;
    int cptr = 0;

    /* On lit les premieres donnees
       */
    read_data(&cptr, &data, &nreal);

    while(nreal > 0)
    {
        /* TRAVAIL A FAIRE  */

        /* Le maitre attend qu'un esclave soit disponible et recupere son rang
           */

        /* Le maitre envoit les donnees a traiter (tableau data de nreal reels) a l'esclave 
           Utiliser l'etiquette du message pour transmettre le compteur de traitement cptr
           */
        printf("cptr %5d : Master send nreal %d to slave %d\n", cptr, nreal, slave_rank);

        /* FIN TRAVAIL A FAIRE  */


        /* On prepare les prochaines donnees
           Si nreal == 0 c'est qu'on a rien lu (et qu'il n'y a plus rien a lire)
           */
        read_data(&cptr, &data, &nreal);
    }

    if (data)
    {
        free(data);
    }

    /* TRAVAIL A FAIRE  */

    /* Maintenant que toutes les donnees sont traitees
       il faut attendre tous les esclaves
       et leur signaler que les traitements sont termines
       */
    printf("Master : END\n");

    /* FIN TRAVAIL A FAIRE  */
}

int main(int argc, char **argv)
{
    int rank, nproc;

    /* TRAVAIL A FAIRE  */
    /* Initialiser rank et nproc
       */

    if (rank == MASTER_RANK)
    {
        run_master(nproc-1);
    }
    else
    {
        run_slave(rank);
    }

    /* FIN TRAVAIL A FAIRE  */

    return 0;
}

