#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

/*
 * Éléments de correction / 解析与纠正
 *
 * Pour effectuer sa portion de calcul, chaque fil d'exécution a besoin de savoir :
 * 1. où dans le tableau values il commence à travailler,
 * 2. combien de cases il doit traiter.
 *
 * 为了执行其计算部分，每个执行线程需要知道：
 * 1. 它在 values 数组中的哪里开始工作，
 * 2. 它必须处理多少个单元格。
 *
 * Dans l'implémentation ci-dessous, la fonction work sera exécutée par chacun des fils d'exécution et effectuera une partie des multiplications.
 * Cependant elle n'accepte qu'un seul argument. Nous passons donc les informations nécessaires aux fils d'exécution
 * via la structure struct s_arg à deux éléments :
 * 1. begin, pointeur vers la case du tableau values où le fil d'exécution commence à travailler ;
 * 2. n, le nombre de cases que le fil d'exécution doit traiter à partir de begin.
 *
 * 在下面的实现中，work 函数将由每个执行线程执行，并执行部分乘法运算。而且通过 struct s_arg 结构传递必要信息。
 * 1. begin，指向执行线程开始工作的 values 单元格的指针；
 * 2. n，执行线程必须从 begin 开始处理的单元格数量。
 *
 * Après avoir vérifié la présence et le format des arguments passés au programme (à savoir le nombre n de fils d'exécution à créer
 * et, optionnellement, la taille size du tableau values), la fonction principale main alloue trois tableaux de n éléments.
 * 1. Le tableau tid qui stockera les identifiants attribués par le système d'exploitation à chacun des fils d'exécution...
 * 2. Le tableau values qui contient les données à traiter.
 * 3. Le tableau args qui stockera les informations nécessaires à chaque fil d'exécution pour effectuer leur portion de calcul.
 *
 * 主函数 main 分配三个数组：tid (线程ID), values (数据), args (线程参数)。
 */

struct s_arg {
  int * begin;
  int n;
};

int sum = 0;
pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER;
int sumMutex = 0;

void * work(void * arg) {
  struct s_arg * me = (struct s_arg *) arg;
  for(int i = 0; i < me->n; i++) {
    me->begin[i] *= 2;
  }

  int sumLoc = 0;
  for(int i = 0; i < me->n; i++) {
    sumLoc += me->begin[i];
  }

  atomic_fetch_add(&sum, sumLoc);

  pthread_mutex_lock(&sum_mutex);
    sumMutex += sumLoc;
  pthread_mutex_unlock(&sum_mutex);

  return NULL;
}

int main(int argc, char ** argv) {
  if(argc < 2) {
    fprintf(
      stderr, "Veuillez spécifier le nombre de fils d'exécution à lancer !\n"
    );
    return 1;
  }

  int n = atoi(argv[1]);

  if(n < 1) {
    fprintf(
      stderr, "Le nombre de fils d'exécution doit être supérieur à zéro !\n"
    );
    return 1;
  }

  int size = 16;

  if(argc > 2) {
    size = atoi(argv[2]);
  }

  if(size < 1) {
    fprintf(
      stderr, "La taille du tableau doit être supérieure à zéro !\n"
    );
    return 1;
  }

  if(size % n) {
    fprintf(
      stderr,
      "La taille du tableau doit être divisible par le nombre de fils "
      "d'exécution !\n"
    );
    return 1;
  }

  int batch = size / n;

  pthread_t * tid = (pthread_t *) malloc(n * sizeof(pthread_t));
  int * values = (int *) malloc(size * sizeof(int));
  struct s_arg * args = (struct s_arg *) malloc(n * sizeof(struct s_arg));

  for(int i = 0; i < size; i++) {
    values[i] = rand() % 11;
  }

  printf("Initialisation : [");

  for(int i = 0; i < size; i++) {
    printf(" %*d ", 2, values[i]);
  }

  printf("]\n");

  for(int i = 0; i < n; i++) {
    args[i].begin = &values[i * batch];
    args[i].n = batch;
    pthread_create(&tid[i], NULL, work, (void *) &args[i]);
  }

  for(int i = 0; i < n; i++) {
    pthread_join(tid[i], NULL);
  }

  printf("Somme partielle calculée par les fils d'exécution : %d\n", sum);
    printf("Somme partielle calculée avec un mutex : %d\n", sumMutex);

  printf("Résultat       : [");

  for(int i = 0; i < size; i++) {
    printf(" %*d ", 2, values[i]);
  }

  printf("]\n");

  free(tid);
  free(values);
  free(args);

  return 0;
}

/*
 * Compilé sous le nom pthreads-compute et lancé avec ./pthreads-compute 4 16, notre programme produit la sortie suivante.
 * 在 pthreads-compute 下编译并用 ./pthreads-compute 4 16 启动后，我们的程序产生以下输出。
 *
 * Initialisation : [  6  10   6   2   1   4   0   6   3   1   8   7   5   3   7   4 ]
 * Résultat       : [ 12  20  12   4   2   8   0  12   6   2  16  14  10   6  14   8 ]
 *
 * À noter  请注意
 * Une implémentation séquentielle du calcul consisterait à remplacer les boucles for responsables du lancement et de l'attente des fils d'exécution par une seule boucle for effectuant le calcul comme suit.
 * 计算的顺序实现方式是将负责启动和等待执行线程的循环 for 替换为单个循环 for ，该循环按以下方式执行计算：
 *
 * for(int i = 0; i < size; i++) {
 *   values[i] *= 2;
 * }
 */
