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
    int rank, nproc, tag, nvals_per_proc;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    if (nproc == 1)
    {
        printf("Il faut au moins 2 processus MPI\n"); fflush(stdout);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    tag = 1000;
    nvals_per_proc = 100000;
    if (rank == 0)
    {
        int isnd;
        int dst_odd = 1;
        int n_odd   = nproc / 2;
        MPI_Request req;
        int tab_vals[n_odd*nvals_per_proc];

        for(isnd = 0 ; isnd < n_odd ; isnd++)
        {
            int *isnd_arr = tab_vals+isnd*nvals_per_proc;
            fill_val_array(dst_odd, isnd_arr, nvals_per_proc);

            /* ATTENTION, ceci est FAUX !!!
               Quelle est l'erreur ?
               */
            MPI_Isend(isnd_arr, nvals_per_proc, MPI_INT, dst_odd, tag, MPI_COMM_WORLD, &req);
            printf("P0 initiates send values [%d, %d] to process P%d\n", isnd_arr[0], isnd_arr[nvals_per_proc-1], dst_odd);
            dst_odd += 2;
        }
        MPI_Wait(&req, MPI_STATUS_IGNORE);
    }
    else if (rank % 2 == 1)
    {
        MPI_Request req;
        int my_val_arr[nvals_per_proc];

        MPI_Irecv(my_val_arr, nvals_per_proc, MPI_INT, 0, tag, MPI_COMM_WORLD, &req);
        MPI_Wait(&req, MPI_STATUS_IGNORE);

        check_val_array(rank, my_val_arr, nvals_per_proc);
    }

    MPI_Finalize();

    return 0;
}

