#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define NESTED 0

// Implémentation séquentielle de référence (ne pas modifier)
long long int fibonacci_reference(int n) {
  if(n < 2) {
    return n;
  }

  long long int x, y;

  x = fibonacci_reference(n - 1);
  y = fibonacci_reference(n - 2);

  return x + y;
}

// Implémentation à paralléliser avec des sections
/*
 * Éléments de correction / 解析与纠正
 *
 * Première approche (Sections) :
 * Nous avons placé les deux appels récursifs de la fonction fibonacci_kernel_sections dans des sections OpenMP distinctes (directive section),
 * elles-mêmes englobées dans une zone parallel sections.
 *
 * 第一种方法 (Sections):
 * 我们将 fibonacci_kernel_sections 函数的两个递归调用分别放入单独的 OpenMP sections 中（指令 section），
 * 它们本身包含在 parallel sections 区域中。
 *
 * Cette approche est inefficace et risque de faire planter le programme (épuisement des ressources) car chaque entrée dans une zone
 * parallel sections crée une nouvelle équipe de fils d'exécution.
 *
 * 这种方法效率低下，并且可能会导致程序崩溃（资源耗尽），因为每次进入 parallel sections 区域都会创建一个新的执行线程组。
 */

long long int fibonacci_kernel_sections(int n) {
  if(n < 2) {
    return n;
  }

  long long int x, y;

  #pragma omp parallel sections firstprivate(n)
  {
    #pragma omp section
    x = fibonacci_kernel_sections(n - 1);
    #pragma omp section
    y = fibonacci_kernel_sections(n - 2);
  }

  return x + y;
}

// Implémentation à paralléliser avec des tâches
/*
 * Éléments de correction / 解析与纠正
 *
 * Deuxième approche (Tasks) :
 * Pour résoudre le problème de l'approche précédente, nous utilisons les tâches OpenMP (task).
 * Les tâches permettent de créer un pool de travaux à effectuer, que les fils d'exécution (créés une seule fois au début)
 * viennent piocher selon leur disponibilité.
 *
 * 第二种方法 (Tasks):
 * 为了解决前一种方法的问题，我们使用 OpenMP 任务（task）。
 * 任务允许创建一个要执行的作业池，执行线程组（一开始创建一次）根据可用性从中获取作业。
 *
 * Nous définissons une zone parallel exécutée par un seul fil d'exécution (directive single) qui générera les tâches.
 * Pour chaque appel récursif, nous créons une tâche (task) calculant le terme n-1, tandis que le fil d'exécution courant
 * s'occupe de n-2 et attend (taskwait) la fin de la tâche créée.
 *
 * 我们定义一个 parallel 区域，由单个执行线程执行（指令 single）来生成任务。
 * 对于每个递归调用，我们创建一个任务 (task) 计算 n-1 的项，而当前执行线程负责计算 n-2 的项并等待 (taskwait) 创建的任务完成。
 *
 * De plus, pour limiter le surcoût, nous ne créons des tâches que si n >= 20.
 *
 * 此外，为了限制开销，我们仅在 n >= 20 时才创建任务。
 */

long long int fibonacci_kernel_tasks(int n) {
  if(n < 2) {
    return n;
  }

  if(n < 20) return fibonacci_reference(n);

  long long int x, y;

  #pragma omp task shared(x)
  x = fibonacci_kernel_tasks(n - 1);
  #pragma omp task shared(y)
  y = fibonacci_kernel_tasks(n - 2);

  #pragma omp taskwait

  return x + y;
}

int main(int argc, char ** argv) {
  int n = 20;

  if(argc > 1) {
    int a = atoi(argv[1]);
    n = a > 0 ? a : n;
  }

  long long int f_ref, f_tasks, f_sections;
  double time_reference, time_kernel_tasks, time_kernel_sections;

  // Exécution de l'implémentation séquentielle de référence.
  time_reference = omp_get_wtime();
  f_ref = fibonacci_reference(n);
  time_reference = omp_get_wtime() - time_reference;
  printf("Calcul séquentiel : %3.5lf s\n", time_reference);
  // Exécution des implémentations parallélisées :
  //  - version à base de sections
  omp_set_nested(NESTED);
  time_kernel_sections = omp_get_wtime();
  f_sections = fibonacci_kernel_sections(n);
  time_kernel_sections = omp_get_wtime() - time_kernel_sections;
  printf(
    "Calcul parallèle (à base de sections) : %3.5lf s\n",
    time_kernel_sections
  );
  //  - version à base de tâches
  time_kernel_tasks = omp_get_wtime();
  #pragma omp parallel
  #pragma omp master
  f_tasks = fibonacci_kernel_tasks(n);
  time_kernel_tasks = omp_get_wtime() - time_kernel_tasks;
  printf("Calcul parallèle (à base de tâches) : %3.5lf s\n", time_kernel_tasks);

  // Affichage des résultats.
  printf(
    "Fibonacci de %d (référence séquentielle)             = %lld\n",
    n, f_ref
  );
  printf(
    "Fibonacci de %d (impl. parallèle à base de sections) = %lld\n",
    n, f_sections
  );
  printf(
    "Fibonacci de %d (impl. parallèle à base de tâches)   = %lld\n",
    n, f_tasks
  );

  // Comparaison des résultats.
  if(f_sections != f_ref) {
    printf("Mauvais résultat (impl. parallèle à base de sections) !\n");
    return 1;
  }
  if(f_tasks != f_ref) {
    printf("Mauvais résultat (impl. parallèle à base de tâches) !\n");
    return 1;
  }

  printf("Ça roule !\n");

  return 0;
}