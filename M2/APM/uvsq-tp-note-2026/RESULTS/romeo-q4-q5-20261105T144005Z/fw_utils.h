/* ============================================================================
 * fw_utils.h : utilitaires du TP Floyd-Warshall
 * ============================================================================
 * Un graphe a n sommets est decrit par sa matrice d'adjacence n x n,
 * stockee en row-major : d[i * n + j] est le poids de l'arete i -> j
 * (0 si i == j). INF note l'absence d'arete. INF = 10^9 est choisi
 * pour que la somme de deux INF (2 x 10^9) tienne dans un int 32
 * bits : l'algorithme peut comparer dik + dkj sans deborder, les
 * poids etant positifs ou INF.
 *
 * Ces fonctions sont des utilitaires, regroupes ici pour laisser le
 * fichier principal (fw.c) reduit a l'algorithme et au programme
 * principal. Les fonctions sont statiques : ce header ne doit etre
 * inclus que par un seul fichier .c.
 * ==========================================================================*/

#ifndef FW_UTILS_H
#define FW_UTILS_H

/* clock_gettime ; garde necessaire car nvcc definit deja cette macro */
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 1000000000

/* --------------------------------------------------------------------------
 * Construction du graphe
 * ------------------------------------------------------------------------ */

/* Graphe deterministe : l'exemple a 4 sommets du sujet. Il permet de
 * verifier a la main le resultat de Floyd-Warshall, puis plus tard de
 * le comparer a celui de la version parallele. La matrice retournee
 * est allouee par malloc (a liberer par free). */
static int *graph_example(void)
{
    static const int W[4][4] = {
        {   0,   3,  10, INF},
        {INF,   0,   4,   8},
        {INF, INF,   0,   1},
        {INF, INF, INF,   0}
    };
    int n = 4;
    int *d = (int *)malloc(sizeof(int) * (size_t)n * n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            d[i * n + j] = W[i][j];
    return d;
}

/* Graphe aleatoire a n sommets : environ 60 % des aretes presentes,
 * poids entiers dans [1, 100], 0 sur la diagonale, INF ailleurs. Une
 * meme graine produit toujours le meme graphe : mesures
 * reproductibles, comparaison CPU / GPU sur le meme graphe. */
static int *graph_random(int n, unsigned seed)
{
    unsigned rng = (seed != 0) ? seed : 1;
    int *d = (int *)malloc(sizeof(int) * (size_t)n * n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int w = INF;                      /* pas d'arete par defaut */
            if (i == j) {
                w = 0;
            } else {
                rng = rng * 1103515245u + 12345u;
                if ((rng >> 16) % 100 < 60)
                    w = 1 + (int)((rng >> 8) % 100);
            }
            d[i * n + j] = w;
        }
    return d;
}

/* --------------------------------------------------------------------------
 * Affichage
 * ------------------------------------------------------------------------ */

/* Affiche la matrice n x n, une ligne par sommet ; un point marque
 * l'absence d'arete (INF). */
static void print_graph(const int *d, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (d[i * n + j] >= INF) printf("    . ");
            else                     printf("%5d ", d[i * n + j]);
        printf("\n");
    }
}

/* --------------------------------------------------------------------------
 * Chronometrage
 * ------------------------------------------------------------------------ */

/* Horloge monotone, en millisecondes. S'utilise par difference :
 *   double t0 = now_ms();
 *   ... travail chronometre ...
 *   double duree_ms = now_ms() - t0; */
static double now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1e3 + (double)ts.tv_nsec / 1e6;
}

#endif /* FW_UTILS_H */
