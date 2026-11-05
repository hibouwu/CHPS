/* ============================================================================
 * cuda_utils.h : aides CUDA minimales pour le TP (erreurs, chronometrage)
 * ============================================================================
 * Ce header est mis a la disposition des etudiants. Il n'est utilise ni
 * par fw.c ni par le Makefile : incluez-le dans votre fw_gpu.cu.
 *
 * Il ne contient ni allocation, ni copie, ni lancement de kernel : la
 * gestion memoire et les lancements restent a ecrire et doivent
 * apparaitre dans votre code. Sont fournis :
 *   - CUDA_CHECK(...) : verification d'un code de retour CUDA ;
 *   - gpu_timer_t     : chronometrage par evenements CUDA, en ms.
 * ==========================================================================*/

#ifndef CUDA_UTILS_H
#define CUDA_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

/* --------------------------------------------------------------------------
 * Verification d'erreur
 * ------------------------------------------------------------------------ */

/* Verifie un appel CUDA : en cas d'erreur, affiche le fichier, la ligne
 * et le message, puis arrete le programme.
 * Exemple : CUDA_CHECK(cudaMalloc(&d, octets)); */
#define CUDA_CHECK(call)                                                   \
    do {                                                                   \
        cudaError_t err_ = (call);                                         \
        if (err_ != cudaSuccess) {                                         \
            fprintf(stderr, "%s:%d : erreur CUDA : %s\n",                  \
                    __FILE__, __LINE__, cudaGetErrorString(err_));         \
            exit(EXIT_FAILURE);                                            \
        }                                                                  \
    } while (0)

/* --------------------------------------------------------------------------
 * Chronometrage
 * ------------------------------------------------------------------------ */

/* Chronometre GPU par evenements. Les lancements sont asynchrones : une
 * horloge cote hote (now_ms) ne mesure pas le travail GPU, car elle peut
 * revenir avant la fin des kernels. Les evenements, eux, sont enregistres
 * dans le flux CUDA et datent le travail reel.
 *
 *   gpu_timer_t t;
 *   gpu_timer_start(&t);
 *   ... lancements et copies ...
 *   float ms = gpu_timer_stop(&t);        duree en millisecondes */
typedef struct {
    cudaEvent_t beg, end;
} gpu_timer_t;

static void gpu_timer_start(gpu_timer_t *t)
{
    CUDA_CHECK(cudaEventCreate(&t->beg));
    CUDA_CHECK(cudaEventCreate(&t->end));
    CUDA_CHECK(cudaEventRecord(t->beg));
}

static float gpu_timer_stop(gpu_timer_t *t)
{
    float ms = 0.f;
    CUDA_CHECK(cudaEventRecord(t->end));
    CUDA_CHECK(cudaEventSynchronize(t->end));
    CUDA_CHECK(cudaEventElapsedTime(&ms, t->beg, t->end));
    CUDA_CHECK(cudaEventDestroy(t->beg));
    CUDA_CHECK(cudaEventDestroy(t->end));
    return ms;
}

#endif /* CUDA_UTILS_H */
