#include "fw_utils.h"
#include <stdbool.h>
#include <unistd.h>                           /* getopt                  */
#include <getopt.h>                           /* getopt_long, --help     */
#include "cuda_utils.h"
#include <string.h>

__global__ void fw_step(int *d, int n, int k)
{
    int j = blockIdx.x * blockDim.x + threadIdx.x;
    int i = blockIdx.y * blockDim.y + threadIdx.y;

    if (i >= n || j >= n)
        return;

    if (i == k || j == k)
        return;

    int idx = i * n + j;
    int via_k = d[i * n + k] + d[k * n + j];

    if (via_k < d[idx])
        d[idx] = via_k;
}

void fw_gpu(int *d, int n)
{
    size_t bytes = (size_t)n * n * sizeof(int);
    int *d_device = nullptr;
    CUDA_CHECK(cudaMalloc(&d_device, bytes));
    CUDA_CHECK(cudaMemcpy(d_device, d, bytes, cudaMemcpyHostToDevice));
    dim3 block(32, 8);
    dim3 grid((n + block.x - 1) / block.x, (n + block.y - 1) / block.y);

    //Q3
    for (int k = 0; k < n; ++k) {
        fw_step<<<grid, block>>>(d_device, n, k);
        CUDA_CHECK(cudaGetLastError());
    }
    CUDA_CHECK(cudaMemcpy(d, d_device, bytes, cudaMemcpyDeviceToHost));

    CUDA_CHECK(cudaFree(d_device));
}

/* --------------------------------------------------------------------------
 * Floyd-Warshall. En sortie, d[i * n + j] contient la longueur du plus
 * court chemin de i a j (INF s'il n'en existe pas). La matrice est
 * mise a jour sur place.
 * (copie par le fichier cpu)
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

    // Q4
    int count = n * n;
    int *d_cpu_ref = (int *)malloc(count * sizeof(int));
    memcpy(d_cpu_ref, d, count * sizeof(int));
    double cpu_t0 = now_ms();
    floyd_warshall(d_cpu_ref, n);
    double cpu_t1 = now_ms();

    double t0 = now_ms();
    fw_gpu(d, n);
    double t1 = now_ms();

    bool ok = true;
    for (int i = 0; i < count; ++i) {
        if (d[i] != d_cpu_ref[i]) {
            ok = false;
            break;
        }
    }
    printf("Validation CPU/GPU : %s\n", ok ? "PASS" : "FAIL");
    free(d_cpu_ref);
    if (!ok) {
        free(d);
        return EXIT_FAILURE;
    }

    if (n <= 16) {
        printf("Graphe final (plus courts chemins) :\n");
        print_graph(d, n);
    }
    printf("n = %d\n", n);
    printf("CPU : %.3f ms\n", cpu_t1 - cpu_t0);
    printf("GPU (transferts compris) : %.3f ms\n", t1 - t0);
    free(d);
    return 0;
}
