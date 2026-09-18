# Algorithmique et Programmation Parallele / 并行算法与程序设计

Évaluation du 03/04/2025 - Ce document contient 6 pages  2025/04/03 测验 - 本文档共 6 页  
2h - Tout document autorisé  2 小时 - 允许查阅所有资料

## Exercice I : Quel est le danger ? / 练习 I：危险是什么？

Soit la section de code suivante exécutée par tous les processus d'un programme MPI (il y a au moins 3 processus) :  设下面这段代码由一个 MPI 程序中的所有进程执行（至少有 3 个进程）：

```c
int rang, val;
MPI_Status sta;

MPI_Comm_rank(MPI_COMM_WORLD, &rang);

if (rang == 0) {
    MPI_Recv(&val, 1, MPI_INT, MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &sta);
} else if (rang == 1) {
    val = rang;
    MPI_Send(&val, 1, MPI_INT, 0, 1111, MPI_COMM_WORLD);
} else if (rang == 2) {
    val = rang;
    MPI_Send(&val, 1, MPI_INT, 0, 1000, MPI_COMM_WORLD);
}
```

a) Suite à l'exécution de ces lignes, quelle est la valeur de la variable `val` sur les 3 premiers processus ? Justifiez.  a) 执行完这些语句后，前 3 个进程上的变量 `val` 的值分别是多少？请说明理由。  
b) Expliquez brièvement en quoi cette section de code pose un problème.  b) 请简要说明这段代码为什么会有问题。  
c) Apportez une correction au problème identifié en b).  c) 针对 b) 中指出的问题给出一个修正方案。

**Réponse** / 答案

- a) `rang 0 : val = 2`, `rang 1 : val = 1`, `rang 2 : val = 2`.
  Justification : le processus 0 exécute `MPI_Recv(..., MPI_ANY_SOURCE, 1000, ...)`, donc il ne peut recevoir qu'un message de tag `1000`. Le processus 1 envoie avec le tag `1111`, tandis que le processus 2 envoie avec le tag `1000`. Ainsi, seul le message du processus 2 peut être reçu par le processus 0.
- b) Cette section de code pose un problème de correspondance des communications : le processus 1 envoie un message avec le tag `1111`, alors que le processus 0 ne reçoit qu'un message de tag `1000`. Le message du processus 1 n'est donc pas reçu par cette instruction. Selon l'implémentation MPI et le mode effectif de l'envoi, cela peut conduire à un blocage.
- c) Il faut rendre cohérents les tags et faire correspondre le nombre d'envois et de réceptions. Par exemple, si le processus 0 doit recevoir les deux messages :

```c
if (rang == 0) {
    int v1, v2;
    MPI_Recv(&v1, 1, MPI_INT, 1, 1000, MPI_COMM_WORLD, &sta);
    MPI_Recv(&v2, 1, MPI_INT, 2, 1000, MPI_COMM_WORLD, &sta);
} else if (rang == 1) {
    val = rang;
    MPI_Send(&val, 1, MPI_INT, 0, 1000, MPI_COMM_WORLD);
} else if (rang == 2) {
    val = rang;
    MPI_Send(&val, 1, MPI_INT, 0, 1000, MPI_COMM_WORLD);
}
```

## Exercice II : Boucles `for` / 练习 II：`for` 循环

Soit le programme OpenMP suivant :  设有如下 OpenMP 程序：

```c
void main() {
    // (A)
    #pragma omp parallel num_threads(2)
    for (int i = 0; i < 10; i++) {
        printf("thr=%d, i=%d\n", omp_get_thread_num(), i);
    }

    // (B)
    #pragma omp for schedule(static)
    for (int j = 0; j < 10; j++) {
        printf("thr=%d, j=%d\n", omp_get_thread_num(), j);
    }

    // (C)
    #pragma omp parallel for schedule(static) num_threads(2)
    for (int k = 0; k < 10; k++) {
        printf("thr=%d, k=%d\n", omp_get_thread_num(), k);
    }
}
```

### Question 1 / 问题 1

Donnez, pour chacune des boucles (A), (B) et (C), le nombre maximal de threads les exécutant. Justifiez brièvement.  对于循环 (A)、(B) 和 (C)，分别给出执行它们的最大线程数。请简要说明理由。

**Réponse** / 答案

- (A) `2` threads. La directive `parallel num_threads(2)` crée 2 threads, et chacun exécute toute la boucle `for`.
- (B) `1` thread. La directive `omp for` répartit les itérations entre les threads de l'équipe courante ; ici, hors de toute région `parallel`, seul le thread initial (`thread 0`) exécute la boucle.
- (C) `2` threads. La directive `parallel for num_threads(2)` crée directement 2 threads et répartit les itérations entre eux.

### Question 2 / 问题 2

On fait l'hypothèse suivante : chacune des boucles est exécutée par son nombre maximal possible de threads (déterminé à la question 1).  作如下假设：每个循环都由其可能的最大线程数执行（该值由问题 1 决定）。

Pour chacune des sections (A), (B) et (C), donnez les intervalles des valeurs de `i` (respectivement `j` et `k`) en fonction des numéros des threads.  对于 (A)、(B) 和 (C) 三部分，分别给出 `i`（对应地还有 `j` 和 `k`）在不同线程编号下的取值区间。

**Réponse** / 答案

- (A) `thread 0 : i = 0..9`, `thread 1 : i = 0..9`, car chaque thread exécute toute la boucle.
- (B) `thread 0 : j = 0..9`, car hors de toute région `parallel`, seul le thread initial exécute la boucle.
- (C) Avec `schedule(static)`, 10 itérations et 2 threads, les itérations sont réparties en deux blocs contigus de 5 : `thread 0 : k = 0..4`, `thread 1 : k = 5..9`.

## Exercice III : Calcul d'une série / 练习 III：级数计算

Soit $S_N$ une série où $N$ est un entier strictement positif :  设 $S_N$ 为一个级数，其中 $N$ 是一个严格正整数：

$$
S_N = \frac{1}{N} \sum_{i=1}^{N} \frac{u_i}{1 + u_i^2}
$$

La suite $u_i$ se définit comme suit :  数列 $u_i$ 定义如下：

$$
\beta = 1.4,\quad u_0 = -\frac{\beta}{2}
$$

$$
i \geq 1,\quad u_i = u_{i-1} + \beta
$$

Ce qui peut encore se réécrire :  它还可以改写为：

$$
i \geq 1,\quad u_i = u_0 + \beta i
$$

Soit le programme séquentiel suivant, qui calcule dans `S` la valeur $S_N$ :  设有如下顺序程序，它在变量 `S` 中计算 $S_N$ 的值：

```c
1  void main()
2  {
3      double u, S, beta, sum = 0.0;
4      int i, N = 100000;
5
6      beta = 1.4;
7      u = -0.5 * beta;
8
9      for (i = 1; i <= N; i++) {
10         u += beta;
11         sum = sum + u / (1.0 + u * u);
12     }
13
14     S = sum / (double)N;
15     printf("\nS = %lf\n", S);
16 }
```

Travail à faire : paralléliser le calcul de `S` avec OpenMP.  要求：使用 OpenMP 并行化 `S` 的计算。

**Réponse** / 答案

La variable `u` crée une dépendance entre les itérations (`u += beta`), donc la boucle ne peut pas être parallélisée directement.
On remplace cette récurrence par l'expression explicite `u_i = u0 + beta * i`, ce qui rend les itérations indépendantes.
La variable `sum` est alors traitée avec une réduction.

```c
#include <stdio.h>
#include <omp.h>

int main(void) {
    double S, beta, u0, sum = 0.0;
    int i, N = 100000;

    beta = 1.4;
    u0 = -0.5 * beta;

    #pragma omp parallel for reduction(+:sum)
    for (i = 1; i <= N; i++) {
        double u = u0 + beta * i;
        sum += u / (1.0 + u * u);
    }

    S = sum / (double)N;
    printf("\nS = %lf\n", S);

    return 0;
}
```

## Exercice IV : Implémentation d'un `gather` / 练习 IV：实现一个 `gather`

Soit la fonction :  设有如下函数：

```c
void allgather(int in, int *out);
```

appelée en même temps par tous les processus MPI.  它由所有 MPI 进程同时调用。

Elle collecte dans le tableau `out` le contenu de toutes les variables `in` de tous les processus MPI. Tous les processus doivent récupérer les résultats. Le tableau `out` est préalablement alloué au nombre total de processus.  它把所有 MPI 进程中的变量 `in` 收集到数组 `out` 中。所有进程都必须拿到结果。数组 `out` 已经按总进程数预先分配好。

La fonction `allgather` est implémentée dans le listing suivant, ainsi qu'un programme principal qui utilise cette fonction. Cependant, le listing n'est pas complet.  函数 `allgather` 及其使用该函数的主程序如下所示。不过，这段代码并不完整。

Travail à faire : compléter les lignes `/* A COMPLETER */` pour que la fonction `allgather` et le programme principal soient corrects.  要求：补全 `/* A COMPLETER */` 所在各行，使函数 `allgather` 和主程序都正确。

Listing de la fonction `allgather` et de son programme principal : complétez-le.  `allgather` 函数及其主程序代码如下：请将其补全。

**Réponse** / 答案

Une solution correcte est la suivante :

```c
void allgather(int in, int *out) {
    int rang, P;

    MPI_Comm_size(MPI_COMM_WORLD, &P);
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    if (rang == 0) {
        MPI_Status sta;
        out[0] = in;
        for (int p = 1; p < P; p++) {
            int val;
            MPI_Recv(&val, 1, MPI_INT, p, 1000, MPI_COMM_WORLD, &sta);
            out[p] = val;
        }
    } else {
        MPI_Send(&in, 1, MPI_INT, 0, 1000, MPI_COMM_WORLD);
    }

    MPI_Bcast(out, P, MPI_INT, 0, MPI_COMM_WORLD);
}

int main(int argc, char *argv[]) {
    int rang, P, *out;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &P);
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    out = (int *)malloc(P * sizeof(int));
    allgather(rang, out);
    for (int p = 0; p < P; p++)
        printf("P%d, out[%d] = %d\n", rang, p, out[p]);
    free(out);

    MPI_Finalize();
    return 0;
}
```

```c
1.  void allgather(int in, int *out) {
2.      int rang, P;
3.
4.      /* A COMPLETER : il faut affecter le nombre de processus dans P */
5.      /* A COMPLETER : il faut affecter la variable rang */
6.
7.      if (rang == 0) {
8.          MPI_Status sta;
9.          out[0] = in;
10.         for (int p = 1; p < P; p++) {
11.             int val;
12.             /* A COMPLETER : réception dans val de la valeur envoyée par le processus de rang p */
13.             /* A COMPLETER : mise à jour du tableau out */
14.         }
15.     } else {
16.         /* A COMPLETER : envoi de in au processus 0 */
17.     }
18.     /* A COMPLETER : le processus 0 diffuse out aux autres processus */
19. }
20.
21. int main(int argc, char *argv[]) {
22.     int rang, P, *out;
23.
24.     /* A COMPLETER */
25.     /* A COMPLETER : il faut affecter le nombre de processus dans P */
26.     /* A COMPLETER : il faut affecter la variable rang */
27.
28.     out = (int *)malloc(P * sizeof(int));
29.     allgather(rang, out);
30.     for (int p = 0; p < P; p++)
31.         printf("P%d, out[%d] = %d\n", rang, p, out[p]);
32.     free(out);
33.
34.     /* A COMPLETER */
35.     return 0;
36. }
```

## Exercice V : Single / 练习 V：Single

Soit le programme OpenMP suivant :  设有如下 OpenMP 程序：

```c
#include <stdio.h>
#include <omp.h>

#define N 10

void main() {
    #pragma omp parallel
    {
        int nt = omp_get_num_threads();
        int myrank = omp_get_thread_num();

        for (int k = 0; k < N; k++) {
            #pragma omp critical
            {
                printf("critical=%d\n", myrank);
            }

            #pragma omp master
            {
                printf("master=%d\n", myrank);
            }

            #pragma omp single
            {
                printf("single=%d\n", myrank);
            }
        }
    }
}
```

### Question 1 / 问题 1

1-a) La variable `nt` est-elle locale à chaque thread de la région parallèle ou bien partagée entre ces threads ?  1-a) 变量 `nt` 是并行区中每个线程私有的，还是在线程之间共享的？  
1-b) La valeur de `nt` est-elle identique à tous les threads ou bien différente par thread ? Justifiez.  1-b) `nt` 的值对所有线程都相同，还是会因线程不同而不同？请说明理由。  
1-c) Combien va-t-il y avoir d'affichages `printf("critical=%d\n", myrank)` ? Justifiez.  1-c) `printf("critical=%d\n", myrank)` 会输出多少次？请说明理由。  
1-d) Combien va-t-il y avoir d'affichages `printf("master=%d\n", myrank)` ? Justifiez.  1-d) `printf("master=%d\n", myrank)` 会输出多少次？请说明理由。  
1-e) Combien va-t-il y avoir d'affichages `printf("single=%d\n", myrank)` ? Justifiez.  1-e) `printf("single=%d\n", myrank)` 会输出多少次？请说明理由。  
1-f) Les valeurs affichées par `printf("master=%d\n", myrank)` sont-elles identiques au cours de l'exécution ? Justifiez.  1-f) 在程序执行过程中，`printf("master=%d\n", myrank)` 输出的值是否始终相同？请说明理由。  
1-g) Les valeurs affichées par `printf("single=%d\n", myrank)` sont-elles identiques au cours de l'exécution ? Justifiez.  1-g) 在程序执行过程中，`printf("single=%d\n", myrank)` 输出的值是否始终相同？请说明理由。

**Réponse** / 答案

- 1-a) `nt` est une variable locale, donc privée à chaque thread.
- 1-b) La valeur de `nt` est identique pour tous les threads : elle vaut le nombre total de threads de la région parallèle.
- 1-c) `critical` est exécuté une fois par thread et par itération, donc s'il y a `nt` threads, il y a `10 * nt` affichages.
- 1-d) `master` n'est exécuté que par le thread maître, une fois par itération, donc il y a `10` affichages.
- 1-e) `single` n'est exécuté qu'une seule fois par itération, donc il y a aussi `10` affichages.
- 1-f) Oui. La valeur affichée est toujours `master=0`, car le thread maître a toujours le rang 0.
- 1-g) Non, pas nécessairement. Le thread qui exécute `single` peut changer d'une itération à l'autre.

### Question 2 / 问题 2

Quelle est l'affirmation correcte ?  哪个说法是正确的？

- [A] Il y a une barrière avant l'accolade ouvrante de `omp single`.  [A] 在 `omp single` 的左花括号之前有一个屏障。
- [B] Il y a une barrière après l'accolade fermante de `omp single`.  [B] 在 `omp single` 的右花括号之后有一个屏障。
- [C] Il y a une barrière avant l'accolade ouvrante et une barrière après l'accolade fermante de `omp single`.  [C] 在 `omp single` 的左花括号之前和右花括号之后各有一个屏障。
- [D] Il n'y a aucune barrière avec la construction `omp single`.  [D] `omp single` 结构中没有任何屏障。

**Réponse** / 答案

- Réponse correcte : `[B]`.
- La construction `omp single` comporte une barrière implicite à la fin, mais pas au début. Cette barrière disparaît seulement si l'on ajoute `nowait`.

### Question 3 / 问题 3

On fait l'hypothèse que les threads OpenMP de la région parallèle sont compatibles POSIX. Par conséquent, il est possible de faire appel à la bibliothèque `pthread` dans la région parallèle OpenMP.  假设并行区域中的 OpenMP 线程与 POSIX 兼容。因此，可以在 OpenMP 并行区中调用 `pthread` 库。

On désire remplacer la construction OpenMP `single` par des appels `pthread`.  我们希望用 `pthread` 调用来替代 OpenMP 的 `single` 结构。
Travail à faire : complétez les sections de code A, B, C et D du programme suivant pour reproduire le même comportement que `single` dans le programme d'origine. Indication : vous pouvez utiliser des variables globales.  要求：补全下面程序中的 A、B、C、D 四段代码，使其重现原程序中 `single` 的相同行为。提示：你可以使用全局变量。

**Réponse** / 答案

Le comportement de `omp single` est le suivant : un seul thread exécute l'instruction, puis tous les threads attendent à une barrière implicite à la fin.
On peut reproduire cette sémantique avec un mutex, une variable globale `single_done` et une barrière `pthread`.

```c
#include <stdio.h>
#include <omp.h>

/* DEBUT SECTION DE CODE A */
#include <pthread.h>
/* FIN SECTION DE CODE A */

/* DEBUT SECTION DE CODE B */
pthread_mutex_t single_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t single_barrier;
int single_done = 0;
/* FIN SECTION DE CODE B */

#define N 10

int main(int argc, char **argv) {
    /* 为了让 omp_get_max_threads() 对应这次 parallel 的实际线程数 */
    omp_set_dynamic(0);

    /* 初始化 pthread barrier */
    pthread_barrier_init(&single_barrier, NULL, omp_get_max_threads());

    #pragma omp parallel
    {
        int nt = omp_get_num_threads();
        int myrank = omp_get_thread_num();

        for (int k = 0; k < N; k++) {
            #pragma omp critical
            {
                printf("critical=%d\n", myrank);
            }
        }

        #pragma omp master
        {
            printf("master=%d\n", myrank);
        }

        /* DEBUT SECTION DE CODE C */
        int do_single = 0;

        pthread_mutex_lock(&single_mutex);
        if (single_done == 0) {
            single_done = 1;
            do_single = 1;
        }
        pthread_mutex_unlock(&single_mutex);

        if (!do_single) goto fin_single;
        /* FIN SECTION DE CODE C */

        printf("single=%d\n", myrank);

        /* DEBUT SECTION DE CODE D */
fin_single:
        pthread_barrier_wait(&single_barrier);
        /* FIN SECTION DE CODE D */
    }

    pthread_barrier_destroy(&single_barrier);
    pthread_mutex_destroy(&single_mutex);

    return 0;
}
```

```c
#include <stdio.h>
#include <omp.h>
/* DEBUT SECTION DE CODE A */
/* includes a completer */
/* FIN SECTION DE CODE A */

/* DEBUT SECTION DE CODE B */
/* declarations a completer */
/* FIN SECTION DE CODE B */

#define N 10

int main(int argc, char **argv) {
    #pragma omp parallel
    {
        int nt = omp_get_num_threads();
        int myrank = omp_get_thread_num();

        for (int k = 0; k < N; k++) {
            #pragma omp critical
            printf("critical=%d\n", myrank);
        }

        #pragma omp master
        printf("master=%d\n", myrank);

        /* DEBUT SECTION DE CODE C */
        /* a completer */
        /* FIN SECTION DE CODE C */

        printf("single=%d\n", myrank);

        /* DEBUT SECTION DE CODE D */
        /* a completer */
        /* FIN SECTION DE CODE D */
    }

    return 0;
}
```

## Exercice VI : Recouvrement / 练习 VI：重叠

Dans la section de code MPI suivante, la fonction `collect_trait` est utilisée dans les conditions suivantes :  在下面这段 MPI 代码中，函数 `collect_trait` 的使用条件如下：

1. cette fonction est appelée par tous les processus MPI (comme une opération collective) ;  1. 该函数由所有 MPI 进程调用（相当于一个集合操作）；  
2. chaque processus a pré-alloué et a rempli son propre tableau `tab` de `N` entiers ;  2. 每个进程都已经预先分配并填好了自己的 `tab` 数组，其中包含 `N` 个整数；  
3. la valeur de `N` est identique pour tous les processus MPI ;  3. 对所有 MPI 进程来说，`N` 的值相同；  
4. la fonction `trait(int *tab, int N)` (appelée par le processus 0) effectue un traitement coûteux à partir des données du tableau `tab` passé en argument, sans modifier le contenu de ces données.  4. 函数 `trait(int *tab, int N)`（由 0 号进程调用）会基于参数数组 `tab` 中的数据执行一个开销较大的处理，但不会修改这些数据的内容。

```c
void collect_trait(int *tab, int N)
{
    int rank, P, k;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &P);

    if (rank == 0)
    {
        MPI_Status sta;
        int *buf2 = (int *)malloc(N * sizeof(int));

        trait(tab, N);
        for (k = 1; k < P; k++)
        {
            MPI_Recv(buf2, N, MPI_INT, k, 1000, MPI_COMM_WORLD, &sta);
            trait(buf2, N);
        }
        free(buf2);
    }
    else
    {
        MPI_Send(tab, N, MPI_INT, 0, 1000, MPI_COMM_WORLD);
    }
}
```

### Question 1 / 问题 1

Quelle est la modification à apporter à la réception pour que le processus 0 reçoive les messages dans n'importe quel ordre ?  应当如何修改接收操作，才能让 0 号进程以任意顺序接收消息？

**Réponse** / 答案

Il faut utiliser MPI_ANY_SOURCE dans la réception :

```c
MPI_Recv(buf2, N, MPI_INT, MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &sta);
```

### Question 2 / 问题 2

Expliquez brièvement pourquoi la réception, par le processus 0, n'est pas recouverte par le traitement `trait`.  请简要说明为什么 0 号进程的接收过程没有和 `trait` 处理过程重叠。

**Réponse** / 答案

La réception n'est pas recouverte par le traitement, car `MPI_Recv` est bloquant : le processus 0 attend la fin complète de la réception avant d'appeler `trait`. Communication et calcul sont donc exécutés successivement.

### Question 3 / 问题 3

Modifiez la section de code exécutée par le processus 0 pour recouvrir la réception par le traitement `trait`, tout en recevant les messages dans n'importe quel ordre.  修改 0 号进程执行的代码段，使接收过程能够与 `trait` 处理过程重叠，同时仍能以任意顺序接收消息。

Indication : utilisez deux buffers de `N` entiers, un pour recevoir des données, l'autre pour traiter des données déjà reçues.  提示：使用两个大小为 `N` 的整数缓冲区，一个用于接收数据，另一个用于处理已经接收到的数据。

**Réponse** / 答案

On utilise deux buffers : pendant que `trait` travaille sur un buffer déjà reçu, la réception du message suivant est lancée dans l'autre buffer avec `MPI_Irecv`. Les messages sont reçus dans n'importe quel ordre grâce à `MPI_ANY_SOURCE`.

```c
if (rank == 0) {
    MPI_Status sta;
    MPI_Request req;
    int *buf[2];
    int cur = 0, next = 1;

    buf[0] = (int *)malloc(N * sizeof(int));
    buf[1] = (int *)malloc(N * sizeof(int));

    trait(tab, N);

    MPI_Irecv(buf[cur], N, MPI_INT, MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &req);

    for (k = 1; k < P; k++) {
        MPI_Wait(&req, &sta);

        if (k < P - 1) {
            MPI_Irecv(buf[next], N, MPI_INT, MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &req);
        }

        trait(buf[cur], N);

        int tmp = cur;
        cur = next;
        next = tmp;
    }

    free(buf[0]);
    free(buf[1]);
}
```
