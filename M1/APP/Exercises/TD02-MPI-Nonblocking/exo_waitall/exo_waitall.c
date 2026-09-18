#include <stdio.h>
#include <mpi.h>

/* Fonction a utiliser pour remplir un tableau qui correspond
   au processus impair odd_rank
   */
void fill_val_array(int odd_rank, int *arr, int nvals)
{
    int i;
    int idx_pos = odd_rank/2;
    int first_val = idx_pos*nvals;

    for(i = 0 ; i < nvals ; i++)
    {
        arr[i] = first_val + i;
    }
}

/* Fonction pour verifier que le tableau recu par 
   le processus impair odd_rank est correct
   */
void check_val_array(int odd_rank, int *arr, int nvals)
{
    int i;
    int idx_pos = odd_rank/2;
    int idx_error = -1;
    int first_val = idx_pos*nvals;

    for(i = 0 ; i < nvals ; i++)
    {
        int correct_value = first_val+i;
        if (arr[i] != correct_value)
        {
            idx_error = i;
            break;
        }
    }

    if (idx_error == -1)
    {
        printf("P%d receives values [%d, %d] from P0\n", odd_rank, arr[0], arr[nvals-1]);
    }
    else
    {
        printf("P%d : incorrect received value at index = %d, incorrect value = %d (correct value = %d)\n", 
                odd_rank, idx_error, arr[idx_error], first_val+idx_error);
    }
}


int main(int argc, char **argv)
{
    int rank, nproc, nvals_per_proc;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    if (nproc == 1)
    {
        printf("Il faut au moins 2 processus MPI\n"); fflush(stdout);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    nvals_per_proc = 100000;

    /* TRAVAIL A FAIRE

       Si je suis le processus de rang 0
           Pour tous les processus impairs rang_impair
               remplir un tableau d'entiers tab_snd de taille nvals_per_proc en appelant la fonction : fill_val_array(rang_impair, tab_snd, nvals_per_proc)
               Envoyer de facon non-bloquante ce tableau au processus rang_impair

       Si je suis un processus de rang impair
           Recevoir de facon non-bloquante mon tableau de taille nvals_per_proc
           Verifier le resultat en appelant la fonction check_val_array(rang_impair, tab_rcv, nvals_per_proc)
       */


    MPI_Finalize();

    return 0;
}

