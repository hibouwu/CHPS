#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

struct complex_s
{
    double real;
    double imag;
};
typedef struct complex_s complex_t;

struct complex_loc_s
{
    double real;
    double imag;
    int rank;
};
typedef struct complex_loc_s complex_loc_t;

/* Permet de tester notre programme
   Affecte des valeurs différentes en fonction du rang
 */
void init_tab_compl(complex_t *tab, int n)
{
    int rang, i, deb;

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    deb = rang+10;
    for(i = 0 ; i < n ; i++)
    {
        tab[i].real = cos(deb   + ((double)(i+1))/(double)n);
        tab[i].imag = sin(deb+1 + ((double)(i+1))/(double)n);
    }
}

/* Calcule la norme d'un nombre complexe
 */
double norm_compl_ri(double real, double imag)
{
    return sqrt(real*real + imag*imag);
}

double norm_compl(complex_t *cpl)
{
    return norm_compl_ri(cpl->real, cpl->imag);
}

void output_tab(complex_t *tab, int n)
{
    int rang, i;

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    char nom_pts[64];
    sprintf(nom_pts, "pts_P%05d", rang);
    FILE *fd = fopen(nom_pts, "w");

    for(i = 0 ; i < n ; i++)
    {
        fprintf(fd, "%.6e %.6e\n", tab[i].real, tab[i].imag);
    }

    fclose(fd);
}


/* Calcule la norme max parmis les nombres complexes du tableau distribuée
   et récupère le rank du processus sur lequel se trouve le max
 */
void calc_norm_max_loc(
        complex_t *tab, int n, 
        MPI_Op op_norm_max_loc,
        MPI_Datatype mpi_cpl_max_loc,
        complex_loc_t *cpl_max_loc)
{
    /* Chaque processus recherche l'indice imax dans [0:n[ tel que tab[imax] 
       soit le nombre complexe de plus grande norme dans le tableau local tab[0:n[
     */
    int rang, i, imax = -1;
    double norm, norm_max = 0;
    complex_loc_t cpl_max_loc_local;

    for(i = 0 ; i < n ; i++)
    {
        norm = norm_compl(tab+i);

        if (norm > norm_max)
        {
            norm_max = norm;
            imax = i;
        }
    }

    /*
       A ECRIRE
       Recuperer dans *cpl_max_loc le nombre complexe de plus grande norme ainsi 
       que le rang sur lequel se trouve ce nombre complexe sur l'ensemble du tableau distribué
     */
}


int main(int argc, char **argv)
{
    int rang;
    int n; /* nb d'éléments par processus */

    complex_t *tab;

    MPI_Op op_norm_max_loc;
    complex_loc_t cpl_max_loc;
    MPI_Datatype mpi_cpl_max_loc;

    int blocklens[3] = {1, 1, 1};
    MPI_Aint indices[3], base;
    MPI_Datatype old_types[3] = {MPI_DOUBLE, MPI_DOUBLE, MPI_INT};

    FILE *fd;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    if (argc == 2)
    {
        n = atoi(argv[1]);
    }
    else
    {
        printf("Il faut exactement 1 argument : le nb d'éléments par processus\n");
        abort();
    }

    /* Allocation + remplissage tableau
       */
    tab = (complex_t*)malloc(n*sizeof(complex_t));

    init_tab_compl(tab, n);

    output_tab(tab, n);


    /*  => creer mpi_cpl_max_loc */
    MPI_Get_address(&cpl_max_loc     , &base);
    MPI_Get_address(&cpl_max_loc.real, indices+0);
    MPI_Get_address(&cpl_max_loc.imag, indices+1);
    MPI_Get_address(&cpl_max_loc.rank, indices+2);

    indices[0] -= base;
    indices[1] -= base;
    indices[2] -= base;

    MPI_Type_create_struct(3, blocklens, indices, old_types, &mpi_cpl_max_loc);
    MPI_Type_commit(&mpi_cpl_max_loc);

    /* A COMPLETER => creer op_norm_max_loc */

    calc_norm_max_loc(tab, n, op_norm_max_loc, mpi_cpl_max_loc, &cpl_max_loc);
    printf("P%d, norm = %.6e, rang = %d\n", rang, norm_compl_ri(cpl_max_loc.real, cpl_max_loc.imag), cpl_max_loc.rank);

    fd = fopen("pts_max", "w");
    fprintf(fd, "%.6e %.6e\n", 0., 0.);
    fprintf(fd, "%.6e %.6e\n", cpl_max_loc.real, cpl_max_loc.imag);
    fclose(fd);

    /* A COMPLETER => liberation operateur */
    MPI_Type_free(&mpi_cpl_max_loc);

    free(tab);

    MPI_Finalize();

    return 0;
}

