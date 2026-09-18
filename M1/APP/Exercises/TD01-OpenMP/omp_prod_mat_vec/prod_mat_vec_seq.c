#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <libgen.h>
#include <math.h>
#include <omp.h>


/*
   Generateur de nombres aleatoires
*/
struct seed_s
{
    short xsubi[3];
};
typedef struct seed_s seed_t;

void init_rand(int seed0, seed_t *sd)
{
    sd->xsubi[0] = 0;
    sd->xsubi[1] = 0;
    sd->xsubi[2] = 0;

    int *sd0 = (int*)(sd->xsubi);
    *sd0 = seed0;
}

double drand(seed_t *sd)
{
    return erand48(sd->xsubi);
}







/*
   Vecteur
*/
struct vector_s
{
    int N;          /* Vecteur de dimension N */
    double *elt;    /* elt[i] : i-ieme element du vecteur*/
};
typedef struct vector_s vector_t;


void alloc_vector(int N, vector_t *vec)
{
    vec->N = N;
    vec->elt = (double*)malloc(N*sizeof(double));
}

void free_vector(vector_t *vec)
{
    free(vec->elt);
}

void init_vector_random(vector_t *vec, seed_t *sd)
{
    int i;

    for(i = 0 ; i < vec->N ; i++)
    {
        vec->elt[i] = drand(sd);
    }
}

int is_equal(vector_t *vec1, vector_t *vec2)
{
    int i, nb_diff;

    assert(vec1->N == vec2->N);

    nb_diff = 0;
    for(i = 0 ; i < vec1->N ; i++)
    {
        if (vec1->elt[i] != vec2->elt[i])
        {
            nb_diff++;
        }
    }
    return nb_diff == 0;
}





/*
   Matrice creuse
*/
#define NCOLMAX 10

struct sparse_matrix_s
{
    int N;          /* Matrice de dimension NxN */
    int *ncol;      /* ncol[i] : nb d'elements non nuls sur la ligne i de la matrice */
    int **col;      /* col[i][k] : colonne du k-ieme element non nul sur la ligne i de la matrice */
    double **elt;   /* elt[i][k] : k-ieme element non nul sur la ligne i de la matrice */

    int *allocated_cols;    /* pour reduire le nombre d'allocations */
    double *allocated_elts; /* pour reduire le nombre d'allocations */
};
typedef struct sparse_matrix_s sparse_matrix_t;

void alloc_sparse_matrix_random(int N, sparse_matrix_t *mat, seed_t *sd)
{
    int i, sum_ncol;
    double inv_N = 1./(double)N;

    mat->N    = N;
    mat->ncol =     (int*)malloc(N*sizeof(int));
    mat->col  =    (int**)malloc(N*sizeof(int*));
    mat->elt  = (double**)malloc(N*sizeof(double*));

    sum_ncol = 0;
    for(i = 0 ; i < N ; i++)
    {
        mat->ncol[i] = 1 + (int)( NCOLMAX*drand(sd)*exp(-i*inv_N) );
        sum_ncol += mat->ncol[i];
    }

    mat->allocated_cols =    (int*)malloc(sum_ncol*sizeof(int));
    mat->allocated_elts = (double*)malloc(sum_ncol*sizeof(double));

    sum_ncol = 0;
    for(i = 0 ; i < N ; i++)
    {
        mat->col[i] = mat->allocated_cols + sum_ncol;
        mat->elt[i] = mat->allocated_elts + sum_ncol;
        sum_ncol += mat->ncol[i];
    }
}

void free_sparse_matrix(sparse_matrix_t *mat)
{
    free(mat->ncol);
    free(mat->col);
    free(mat->elt);

    free(mat->allocated_cols);
    free(mat->allocated_elts);
}

void init_sparse_matrix_random(sparse_matrix_t *mat, seed_t *sd)
{
    int i, k, prev_col, ncol_max;

    for(i = 0 ; i < mat->N ; i++)
    {
        prev_col = 0;
        ncol_max = mat->N - prev_col;

        for(k = 0 ; k < mat->ncol[i] ; k++)
        {
            ncol_max = ncol_max - (mat->ncol[i] - k) - 1;
            mat->col[i][k] = prev_col + 1 + (int)(ncol_max*drand(sd));
            mat->elt[i][k] = 2.*drand(sd) - 1.;

            assert(prev_col < mat->col[i][k]);
            prev_col = mat->col[i][k];
            ncol_max = mat->N - prev_col;

            assert(mat->col[i][k] < mat->N);
        }
    }
}




/*
   Produit Matrice-Vecteur
*/

void prod_mat_vec(sparse_matrix_t *A, vector_t *X, vector_t *Y)
{
    assert(A->N == X->N);
    assert(Y->N == X->N);

    int i, j, k;
    double accu;

    for(i = 0 ; i < A->N ; i++)
    {
        accu = 0.;

        for(k = 0 ; k < A->ncol[i] ; k++)
        {
            j = A->col[i][k];
            accu += A->elt[i][k] * X->elt[j];
        }

        Y->elt[i] = accu;
    }
}



/*
   Main
*/

int main(int argc, char **argv)
{
    int seed0, N, iter, niter;
    double tdeb, tfin;
    seed_t sd;
    vector_t X, Y, YSEQ;
    sparse_matrix_t A;

    if (argc != 3)
    {
        printf("Usage : %s <N> <niter>\n", basename(argv[0]));
        printf("\t<N>    : dimension de la matrice\n");
        printf("\t<iter> : nb d'iterations (i.e. nb de produits)\n");
        abort();
    }
    N = atoi(argv[1]);
    niter = atoi(argv[2]);

    /* Initialisation du generateur de nombres aleatoires
     */
    seed0 = 1234;
    init_rand(seed0, &sd);

    /* Allocations + initialisations vecteurs
     */
    alloc_vector(N, &X);
    alloc_vector(N, &Y);
    alloc_vector(N, &YSEQ);

    init_vector_random(&X, &sd);

    /* Allocation + initialisation matrice creuse
     */
    alloc_sparse_matrix_random(N, &A, &sd);
    init_sparse_matrix_random(&A, &sd);



    /* Produit matrice-vecteur
     */
    prod_mat_vec(&A, &X, &YSEQ);
    
    printf("Debut des produits\n");
    tdeb = omp_get_wtime();
    for(iter = 1 ; iter <= niter ; iter++)
    {
        prod_mat_vec(&A, &X, &Y);

        if (!is_equal(&Y, &YSEQ))
        {
            printf("Difference sur l'iteration %d\n", iter);
            abort();
        }
    }
    tfin = omp_get_wtime();
    printf("Fin des produits\n");
    printf("Temps elapsed : %f s\n", tfin-tdeb);


    /* Liberations memoire
     */
    free_vector(&X);
    free_vector(&Y);

    free_sparse_matrix(&A);

    return 0;
}

