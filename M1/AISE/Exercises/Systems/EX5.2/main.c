#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define PRECISION 1.e-20
#define MAX 5
#define N 5120

// Implémentation séquentielle de référence (ne pas modifier)
void matvec_reference(double c[N], double A[N][N], double b[N]) {
  size_t i, j;

  for(i = 0; i < N; i++) {
    c[i] = 0.;
    for(j = 0; j < N; j++) {
      c[i] += A[i][j] * b[j];
    }
  }
}
// Implémentation à paralléliser
/*
 * Éléments de correction / 解析与纠正
 *
 * Pour paralléliser le calcul dans la fonction matvec_kernel, nous avons de nouveau utilisé la directive OpenMP parallel for.
 *
 * 为了并行化 matvec_kernel 函数中的计算，我们再次使用了 OpenMP 指令 parallel for。
 *
 * Contrairement à l'exercice précédent, nous n'avons pas de réduction ici.
 * En effet, pour chaque itération de la boucle externe (itérateur i), un seul fil d'exécution accède à l'élément res[i] pour l'écrire.
 * Tant que plusieurs fils d'exécution ne traitent pas la même itération i, il n'y a pas de risque de conflit (data race).
 * La directive parallel for nous assure cela.
 *
 * 与前面的练习相反，我们在这里没有归约。实际上，对于外循环（迭代器 i）的每次迭代，只有一个执行线程会访问 res[i] 元素进行写入。
 * 只要多个执行线程不处理相同的迭代 i，就没有数据竞争的风险。 parallel for 指令向我们保证了这一点。
 *
 * Par contre, nous avons dû faire particulièrement attention à la boucle interne (itérateur j).
 * Tout comme dans l'exercice précédent, la variable d'itération j doit être privée.
 *
 * 另一方面，我们必须特别注意内循环（迭代器 j）。就像前面的练习一样，迭代变量 j 必须是私有的。
 */

void matvec_kernel(double c[N], double A[N][N], double b[N]) {
  size_t i, j;
  #pragma omp parallel for private(j)
  for(i = 0; i < N; i++) {
    for(j = 0; j < N; j++) {
      c[i] += A[i][j] * b[j];
    }
  }
}

int main(int argc, char ** argv) {
  double * A   = malloc(N * N * sizeof(double));
  double * b   = malloc(N * sizeof(double));
  double * c   = malloc(N * sizeof(double));
  double * ref = malloc(N * sizeof(double));
  double time_reference, time_kernel;

  // Initialisation des tableaux 'b' et 'A' avec des valeurs aléatoires.
  srand((unsigned int) time(NULL));
  for(size_t i = 0; i < N; i++)
    b[i] = (float) rand() / (float) (RAND_MAX / MAX);
  for(size_t i = 0; i < N * N; i++)
    A[i] = (float) rand() / (float) (RAND_MAX / MAX);

  // Exécution de l'implémentation séquentielle de référence.
  time_reference = omp_get_wtime();
  matvec_reference(ref, (double (*)[N])A, b);
  time_reference = omp_get_wtime() - time_reference;
  printf("Calcul séquentiel : %3.5lf s\n", time_reference);
  // Exécution de l'implémentation parallélisée.
  time_kernel = omp_get_wtime();
  matvec_kernel(c, (double (*)[N])A, b);
  time_kernel = omp_get_wtime() - time_kernel;
  printf("Calcul parallèle : %3.5lf s\n", time_kernel);

  // Affichage et comparaison des résultats.
  for (size_t i = 0; i < N; i++) {
    //printf("ref[%2d] = %f, c[%d] = %f\n", i, ref[i], i, c[i]);
    if (abs(ref[i] - c[i]) > PRECISION) {
      printf("Mauvais résultats !\n");
      exit(1);
    }
  }
  printf("Ça roule !\n");

  free(A);
  free(b);
  free(c);
  free(ref);
  return 0;
}