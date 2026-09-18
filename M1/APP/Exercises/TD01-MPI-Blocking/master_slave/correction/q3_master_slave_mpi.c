#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <mpi.h>

#define MASTER_RANK 0
#define TAG_READY   1000
#define TAG_END     2000
#define TAG_DATA    3000

void process_data(int slave_rank, int cptr, double *data, int nreal)
{
    double sum = 0.;

    for(int i = 0 ; i < nreal ; i++)
    {
        sum += data[i];
    }

//    int duration = 1000000; /* 1 s */
    int duration =  100000; /* 0.1 s */
//    int duration =   10000; /* 0.01 s */
    usleep(nreal*duration);
    printf("cptr %5d : Slave %d receives nreal = %d from Master ; sum = %.6e\n", cptr, slave_rank, nreal, sum);
}

void run_slave(int slave_rank)
{
    MPI_Status sta;
    int over = 0;
    int nreal;
    double *data = NULL;

    do
    {
        /* On envoit un message au "maitre" pour indiquer que moi "esclave" je suis dispo
           Le message est vide mais il existe bel et bien (entête du message).
           Ce qui compte c'est la présence d'un message avec l'étiquette TAG_READY et non le contenu du message
         */
        MPI_Send(NULL, 0, MPI_BYTE, MASTER_RANK, TAG_READY, MPI_COMM_WORLD);

        /* On attend l'arrivee d'un message de la part du maitre.
           La nature de ce message sera indiquee par l'étiquette.
           On ne connait pas la nature du message d'ou l'utilisation de MPI_ANY_TAG
           */
        MPI_Probe(MASTER_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, &sta);

        if (sta.MPI_TAG >= TAG_DATA)
        {
            /* Si l'etiquette est sup. ou egale a TAG_DATA alors les donnees envoyees 
               sont des reels double precision.
               Il faut recuperer la taille du message en nombre de reels => nreal
               Puis recevoir le message proprement dit => MPI_Recv
               */
            MPI_Get_count(&sta, MPI_DOUBLE, &nreal);

            /* Allocation du tableau avant de le recevoir
               */
            data = (double*)realloc(data, nreal*sizeof(double));

            MPI_Recv(data, nreal, MPI_DOUBLE, MASTER_RANK, sta.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            /* ET bien sur on traite les donnees recues
               */
            process_data(slave_rank, sta.MPI_TAG - TAG_DATA, data, nreal);
        }
        else
        {
            assert(sta.MPI_TAG == TAG_END);

            /* L'etiquette TAG_END indique la fin du travail de l'esclave.
               Le message envoyee par le maitre etait de taille nulle
               */
            MPI_Recv(NULL, 0, MPI_BYTE, MASTER_RANK, TAG_END, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            over = 1;
            printf("Slave %d : END\n", slave_rank);
        }
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
    MPI_Status sta;
    int slave_rank = -1;
    double *data = NULL;
    int nreal;
    int cptr = 0;

    /* On lit les premieres donnees
       */
    read_data(&cptr, &data, &nreal);

    while(nreal > 0)
    {
        /* Le maitre attend qu'un esclave soit disponible
           (n'importe lequel d'ou MPI_ANY_SOURCE)
           */
        MPI_Recv(NULL, 0, MPI_BYTE, MPI_ANY_SOURCE, TAG_READY, MPI_COMM_WORLD, &sta);

        slave_rank = sta.MPI_SOURCE;

        /* Le maitre envoit les donnees a traiter a l'esclave avec l'etiquette TAG_DATA+cptr
           */
        printf("cptr %5d : Master send nreal %d to slave %d\n", cptr, nreal, slave_rank);
        MPI_Send(data, nreal, MPI_DOUBLE, slave_rank, TAG_DATA+cptr, MPI_COMM_WORLD);

        /* On prepare les prochaines donnees
           Si nreal == 0 c'est qu'on a rien lu (et qu'il n'y a plus rien a lire)
           */
        read_data(&cptr, &data, &nreal);
    }

    if (data)
    {
        free(data);
    }

    /* Maintenant que toutes les donnees sont traitees
       il faut recevoir les messages TAG_READY en cours (autant que d'esclaves)
       */
    for(int islv = 0 ; islv < nslaves ; islv++)
    {
        MPI_Recv(NULL, 0, MPI_BYTE, MPI_ANY_SOURCE, TAG_READY, MPI_COMM_WORLD, &sta);

        slave_rank = sta.MPI_SOURCE;

        /* Le maitre envoit le message de fin du travail a l'esclave
           */
        MPI_Send(NULL, 0, MPI_BYTE, slave_rank, TAG_END, MPI_COMM_WORLD);
    }
    printf("Master : END\n");
}

int main(int argc, char **argv)
{
    int rank, nproc;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    if (rank == MASTER_RANK)
    {
        run_master(nproc-1);
    }
    else
    {
        run_slave(rank);
    }

    MPI_Finalize();

    return 0;
}

