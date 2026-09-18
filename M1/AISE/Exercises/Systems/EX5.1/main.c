#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#define PI "3.141592653589793238462"
#define PRECISION 1.e-10
#define MAX 5
#define N 51200000

// Implémentation séquentielle de référence (ne pas modifier)
void pi_reference(size_t nb_steps, double * pi) {
  double term;
  double sum = 0.;
  double step = 1. / (double) nb_steps;

  for(size_t i = 0; i < nb_steps; i++) {
    term = (i + 0.5) * step;
    sum += 4. / (1. + term * term);
  }

  (*pi) = step * sum;
}

// Implémentation à paralléliser
/*
 * Éléments de correction / 解析与纠正
 *
 * Pour paralléliser le calcul dans la fonction pi_kernel, nous avons utilisé la directive OpenMP parallel for
 * qui répartit automatiquement les itérations de notre boucle entre plusieurs fils d'exécution.
 *
 * 为了并行化 pi_kernel 函数中的计算，我们使用了 OpenMP 指令 parallel for，该指令自动在多个执行线程之间分配我们循环的迭代。
 *
 * Cependant, la fonction pi_kernel modifie la variable sum à chaque étape d'itération et utilise la variable term.
 * Par conséquent, tous les fils d'exécution accèdent à la variable sum.
 * Comme nous souhaitons que l'ordre des itérations et de leur répartition aux différents fils d'exécution
 * n'impacte pas le résultat final, nous spécifions via la clause reduction(+:sum) que sum est une variable de réduction.
 *
 * 但是，pi_kernel 函数在每一步迭代中更新 sum 变量，并使用 term 变量。
 * 因此，所有执行线程都要访问 sum 变量。由于我们希望迭代顺序和分配给不同执行线程的方式不会影响最终结果，
 * 因此我们通过 reduction(+:sum) 子句指定 sum 是一个归约变量。
 *
 * Quant à la variable term, chacun des fils d'exécution doit en avoir sa propre copie privée pour
 * effectuer correctement ses calculs. Nous avons donc ajouté la clause private(term).
 *
 * 至于 term 变量，每个执行线程都必须有自己的私有副本才能正确执行计算。因此，我们添加 private(term) 子句。
 *
 * Note : Nous n'avons pas inclus l'index de la boucle i à la liste des paramètres de la clause private
 * puisque le standard OpenMP pour C/C++ spécifie que l'index de la boucle devient une variable privée automatiquement.
 *
 * 注意: 我们没有在 private 子句的参数列表中包括循环索引 i，因为 C/C++ 的 OpenMP 标准规定循环索引会自动变为私有变量。
 */

void pi_kernel(size_t nb_steps, double * pi) {
  double term;
  double sum = 0.;
  double step = 1. / (double) nb_steps;

  #pragma omp parallel for reduction(+:sum) private(term)
  for(size_t i = 0; i < nb_steps; i++) {
    term = (i + 0.5) * step;
    sum += 4. / (1. + term * term);
  }

  (*pi) = step * sum;
}

int main(void) {
  double pi, pi_ref;
  double time_reference, time_kernel;

  // Exécution de l'implémentation séquentielle de référence.
  time_reference = omp_get_wtime();
  pi_reference(N, &pi_ref);
  time_reference = omp_get_wtime() - time_reference;
  printf("Calcul séquentiel : %3.5lf s\n", time_reference);
  // Exécution de l'implémentation parallélisée.
  time_kernel = omp_get_wtime();
  pi_kernel(N, &pi);
  time_kernel = omp_get_wtime() - time_kernel;
  printf("Calcul parallèle : %3.5lf s\n", time_kernel);

  printf("Pi : %s\n", PI);
  printf("Pi (résultat du calcul de référence) : %.22g\n", pi_ref);
  printf("Pi (résultat du calcul parallèle) : %.22g\n", pi);

  // Comparaison des résultats.
  if (fabs(pi_ref - pi) > PRECISION) {
    printf("Mauvais résultats !\n");
    exit(1);
  }

  printf("Ça roule !\n");

  return 0;
}