/* ============================================================================
 * fw.c : Floyd-Warshall sur CPU                     TP GPU, code de base
 * ============================================================================
 * Compilation : make        (gcc -O3, produit ./fw)
 * Execution   : ./fw                exemple deterministe du sujet (n = 4)
 *               ./fw -n taille      graphe aleatoire a <taille> sommets
 *               ./fw -n taille -s graine    (graine par defaut : 42)
 *               ./fw -h | --help    aide : options et cas d'usage
 *
 * Ce fichier est le point de depart du TP : la version GPU sera
 * ecrite a partir de lui. Il ne contient que l'algorithme et le
 * programme principal ; les utilitaires (construction du graphe,
 * affichage, chronometrage) sont dans fw_utils.h.
 * ==========================================================================*/

#include "fw_utils.h"
#include <stdbool.h>
#include <unistd.h>                           /* getopt                  */
#include <getopt.h>                           /* getopt_long, --help     */

/* --------------------------------------------------------------------------
 * Floyd-Warshall. En sortie, d[i * n + j] contient la longueur du plus
 * court chemin de i a j (INF s'il n'en existe pas). La matrice est
 * mise a jour sur place.
 * ------------------------------------------------------------------------ */
static void floyd_warshall(int *d, int n)
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++) {
            int dik = d[i * n + k];
            for (int j = 0; j < n; j++) {
                int alt = dik + d[k * n + j];
                if (alt < d[i * n + j])
                    d[i * n + j] = alt;
            }
        }
}

/* Options et cas d'usage du programme : sur stdout pour -h / --help
 * (sortie 0), sur stderr en cas d'erreur (sortie 1). */
static void usage(FILE *out, const char *prog)
{
    fprintf(out,
            "usage : %s [-n taille] [-s graine] [-h | --help]\n"
            "  -n taille : graphe aleatoire a <taille> sommets, chronometre\n"
            "  -s graine : graine du generateur (42 par defaut)\n"
            "  -h, --help : cette aide\n"
            "  sans option : exemple deterministe du sujet (4 sommets)\n"
            "cas d'usage :\n"
            "  %s                  l'exemple du sujet, affiche et chronometre\n"
            "  %s -n 512           un graphe aleatoire de 512 sommets\n"
            "  %s -n 512 -s 7      meme taille, autre graine\n",
            prog, prog, prog, prog);
}

int main(int argc, char **argv)
{
    bool alea = false;
    int n = 0;
    unsigned seed = 42;
    int *d;
    int opt;

    static const struct option longopts[] = {
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };

    while ((opt = getopt_long(argc, argv, "n:s:h", longopts, NULL)) != -1) {
        switch (opt) {
        case 'n': alea = true; n = atoi(optarg); break;
        case 's': seed = (unsigned)atoi(optarg); break;
        case 'h': usage(stdout, argv[0]); return 0;
        default:  usage(stderr, argv[0]); return 1;
        }
    }
    if (alea && n <= 0) {                     /* taille invalide         */
        usage(stderr, argv[0]);
        return 1;
    }
    if (optind < argc) {                      /* operande inattendu      */
        usage(stderr, argv[0]);
        return 1;
    }

    if (alea) {
        d = graph_random(n, seed);
    } else {                                  /* exemple deterministe    */
        n = 4;
        d = graph_example();
    }

    if (n <= 16) {                            /* n'affiche que les petits cas */
        printf("Graphe de base :\n");
        print_graph(d, n);
    }

    double t0 = now_ms();
    floyd_warshall(d, n);
    double t1 = now_ms();

    if (n <= 16) {
        printf("Graphe final (plus courts chemins) :\n");
        print_graph(d, n);
    }
    printf("Floyd-Warshall, n = %d : %.1f ms\n", n, t1 - t0);

    free(d);
    return 0;
}
