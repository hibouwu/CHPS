#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/*
 * Éléments de correction / 解析与纠正
 *
 * Pour finaliser le calcul de la somme globale, tous les fils d'exécution devront contribuer à sum qui devient une variable critique.
 * Comme les fils d'exécution s'exécutent maintenant de manière parallèle, nous devons assurer l'exclusion mutuelle de leurs accès (et surtout de leurs modifications) à la variable sum.
 * Autrement dit, lorsqu'un fil d'exécution modifie la valeur de sum aucun autre fil d'exécution ne peut le modifier simultanément.
 * Pour ce faire, nous nous servons du verrou d'exclusion mutuelle lock.
 *
 * 为了完成全局总和的计算，所有执行线程必须对 sum 做出贡献，sum 变成了一个临界变量。
 * 由于执行线程现在以并行方式执行，我们必须确保它们对变量 sum 的访问（尤其是修改）是互斥的。
 * 换句话说，当一个执行线程修改 sum 的值时，任何其他执行线程都不能同时修改它。为此，我们使用互斥锁 lock。
 *
 * Pour maximiser le parallélisme de notre programme, nous devons minimiser le nombre d'instructions dans la section critique ainsi que le nombre d'accès à la section critique elle-même.
 * C'est pourquoi (comme illustré dans l'implémentation ci-dessous) chaque fil d'exécution n'accède à la section critique qu'une seule fois
 * pour y ajouter sa somme locale après avoir d'abord calculé la somme locale de la portion du tableau values traitée par lui.
 *
 * 为了最大化程序的并行性，我们必须尽量减少临界区中的指令数量以及临界区本身的访问次数。
 * 这就是为什么（如下面的实现所示）每个执行线程只有在首先计算出数组 values 中由它处理的那部分的局部和之后，
 * 才访问一次临界区，以便将其加到全局变量 sum 上的原因。
 */

struct s_arg {
  int * begin;
  int n;
};

void * work(void * arg) {
  struct s_arg * me = (struct s_arg *) arg;
  int local = 0;
  for(int i = 0; i < me->n; i++) {
    me->begin[i] *= 2;
    local += me->begin[i];
  }
  pthread_mutex_lock(&lock);
  sum += local;
  pthread_mutex_unlock(&lock);
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

  int size = 16;
  if(argc > 2) {
    size = atoi(argv[2]);
  }

  if(size < 1) {
    fprintf(
      stderr,
      "La taille du tableau doit être supérieure à zéro !\n"
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

  printf("Résultat : [");
  for(int i = 0; i < size; i++) {
    printf(" %*d ", 2, values[i]);
  }
  printf("]\n");

  printf("Somme : %d (", sum);
  for(int i = 0; i < size - 1; i++) {
    printf("%d + ", values[i]);
  }
  printf("%d)\n", values[size - 1]);

  free(tid);
  free(values);
  free(args);

  return 0;
}
