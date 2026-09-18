#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Éléments de correction / 解析与纠正
 *
 * Dans l'implémentation ci-dessous, la fonction work sera exécutée par chacun des fils d'exécution de l'équipe.
 * Celle-ci se contente d'afficher la valeur de son argument, c'est-à-dire l'identifiant du fils d'exécution l'exécutant.
 *
 * 在下面的实现中，work 函数将由团队中的每个执行线程执行。该函数只显示其参数的值，即执行它的执行线程的标识符。
 *
 * Après avoir vérifié la présence et le format de l'argument attendu par le programme, à savoir le nombre n de fils d'exécution à créer,
 * la fonction principale main alloue deux tableaux de n éléments.
 * 1. Le tableau tid qui stockera les identifiants attribués par le système d'exploitation à chacun des fils d'exécution lors de l'appel à pthread_create.
 * 2. Le tableau id qui stockera nos identifiants locaux aux fils d'exécution, c'est-à-dire une valeur entre 0 et n.
 *
 * 在检查程序预期参数（即要创建的执行线程数 n）的存在和格式之后，主函数 main 分配两个 n 个元素的数组：
 * 1. 数组 tid，它将保留操作系统在调用 pthread_create 时分配给每个执行线程的标识符；
 * 2. 数组 id，它将保留我们对执行线程的本地标识符，即 0 到 n 之间的值。
 *
 * Ensuite, une boucle for nous permet de lancer les n fils d'exécution.
 * Une fois les fils d'exécution lancés, nous allons attendre la terminaison de chacun d'entre eux via un appel dédié à pthread_join.
 * Pour appeler pthread_join pour chaque fils d'exécution, nous utilisons une deuxième boucle for.
 *
 * 接下来，一个 for 循环允许我们可以启动 n 个执行线程。一旦执行线程启动，我们将通过专用调用 pthread_join 等待每个执行线程的终止。
 * 为了为每个执行线程调用 pthread_join，我们使用第二个 for 循环。
 */

void * work(void * arg) {
  int * me = (int *) arg;
  printf("Le fil d'exécution No. %d dit bonjour.\n", *me);
  return NULL;
}

int main(int argc, char ** argv) {
  if(argc < 2) {
    fprintf(
      stderr,
      "Veuillez spécifier le nombre de fils d'exécution à lancer !\n"
    );
    return 1;
  }

  int n = atoi(argv[1]);

  if(n < 1) {
    fprintf(
      stderr,
      "Le nombre de fils d'exécution doit être supérieur à zéro !\n"
    );
    return 1;
  }

  pthread_t * tid = (pthread_t *) malloc(n * sizeof(pthread_t));
  int * id = (int *) malloc(n * sizeof(int));

  for(int i = 0; i < n; i++) {
    id[i] = i;
    pthread_create(&tid[i], NULL, work, (void *) &id[i]);
  }

  for(int i = 0; i < n; i++) {
    pthread_join(tid[i], NULL);
  }

  free(id);
  free(tid);

  return 0;
}

/**
Compilé sous le nom pthreads-hello et lancé avec ./pthreads-hello 4, notre programme produit la sortie suivante.
在 pthreads-hello 下编译并用 ./pthreads-hello 4 启动后，我们的程序产生以下输出。

Le fil d'exécution No. 0 dit bonjour.
Le fil d'exécution No. 1 dit bonjour.
Le fil d'exécution No. 2 dit bonjour.
Le fil d'exécution No. 3 dit bonjour.
*/