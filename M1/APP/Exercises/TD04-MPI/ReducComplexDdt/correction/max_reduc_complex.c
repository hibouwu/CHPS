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
 */
void calc_norm_max(
        complex_t *tab, int n, 
        MPI_Op op_norm_max,
        MPI_Datatype mpi_cpl,        
        complex_t *cpl_max)
{
    /* Chaque processus recherche l'indice imax dans [0:n[ tel que tab[imax] 
       soit le nombre complexe de plus grande norme dans le tableau local tab[0:n[
     */
    int i, imax = -1;
    double norm, norm_max = 0;

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
       Recuperer dans *cpl_max le nombre complexe de plus grande norme sur l'ensemble du tableau distribué
     */
    MPI_Allreduce(tab+imax, cpl_max, 1, mpi_cpl, op_norm_max, MPI_COMM_WORLD);
}

void func_op_norm_max(void *ptr_a, void *ptr_b, int *len, MPI_Datatype *ddt)
{
    complex_t *a = (complex_t*)ptr_a;
    complex_t *b = (complex_t*)ptr_b;
    double norm_ai, norm_bi;
    int i;

    for(i = 0 ; i < *len ; i++)
    {
        norm_ai = norm_compl(a+i);
        norm_bi = norm_compl(b+i);

        if (norm_ai > norm_bi)
        {
            b[i].real = a[i].real;
            b[i].imag = a[i].imag;
        }
        /* else b[i] reste inchange */
    }
}

int main(int argc, char **argv)
{
    int rang;
    int n; /* nb d'éléments par processus */

    MPI_Op op_norm_max;
    MPI_Datatype mpi_cpl;
    complex_t cpl_max;
    complex_t *tab;

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


    /* A COMPLETER => creer mpi_cpl */
    MPI_Type_contiguous(2, MPI_DOUBLE, &mpi_cpl);
    MPI_Type_commit(&mpi_cpl);

    /* A COMPLETER => creer op_norm_max */
    MPI_Op_create(func_op_norm_max, /*commute*/1, &op_norm_max);


    calc_norm_max(tab, n, op_norm_max, mpi_cpl, &cpl_max);
    printf("P%d, norm = %.6e\n", rang, norm_compl(&cpl_max));

    fd = fopen("pts_max", "w");
    fprintf(fd, "%.6e %.6e\n", 0., 0.);
    fprintf(fd, "%.6e %.6e\n", cpl_max.real, cpl_max.imag);
    fclose(fd);

    /* A COMPLETER => liberation operateur, type dérivé */
    MPI_Op_free(&op_norm_max);
    MPI_Type_free(&mpi_cpl);

    free(tab);

    MPI_Finalize();

    return 0;
}

