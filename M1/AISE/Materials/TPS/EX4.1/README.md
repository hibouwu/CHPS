# 练习 1 (Exercice 1)

## 题目描述

> Écrivez un programme qui :
> 编写一个程序，要求：
>
> - prend comme premier argument une valeur entière n strictement positive,
> - 接受一个严格正整数值 n 作为其第一个参数
>
> - crée une équipe de n fils d'exécution à l'aide de la fonction pthread_create,
> - 使用 pthread_create 函数创建一个由 n 个执行线程组成的团队
>
> - attend la terminaison des fils d'exécution à l'aide des appels à la fonction pthread_join.
> - 使用对 pthread_join 函数的调用等待执行线程的终止
>
> Dans cette équipe de n fils d'exécution, chaque fil d'exécution :
> 在这个由 n 个执行线程组成的团队中，每个执行线程：
>
> - reçoit en argument un identifiant (une valeur entre 0 et n),
> - 接收一个标识符（0 到 n 之间的值）作为参数
>
> - affiche son identifiant.
> - 显示其标识符

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#pthreads-1)

## 解析与纠正 (Éléments de correction)

在下面的实现中，`work` 函数将由团队中的每个执行线程执行。该函数只显示其参数的值，即执行它的执行线程的标识符。

在检查程序预期参数（即要创建的执行线程数 `n`）的存在和格式之后，主函数 `main` 分配两个 `n` 个元素的数组：

1. 数组 `tid`，它将保留操作系统在调用 `pthread_create` 时分配给每个执行线程的标识符；
2. 数组 `id`，它将保留我们对执行线程的本地标识符，即 0 到 `n` 之间的值。

接下来，一个 `for` 循环允许我们可以启动 `n` 个执行线程。一旦执行线程启动，我们将通过专用调用 `pthread_join` 等待每个执行线程的终止。为了为每个执行线程调用 `pthread_join`，我们使用第二个 `for` 循环。

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void * work(void * arg) {
    int * me = (int *) arg;
    printf("Le fil d'exécution No. %d dit bonjour.\n", *me);
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
```

## 代码详解

本练习是 POSIX 线程 (pthreads) 的入门练习。

1. **参数解析**:
    从命令行读取线程数 `n`。

2. **线程创建**:
    循环 `n` 次调用 `pthread_create`。
    每次传递一个独立的 `id`（通过数组 `id[i]`，避免竞态条件）。
    线程函数为 `work`。

3. **线程函数 (`work`)**:
    接收 `id` 指针，将其转换为 `int` 并打印。

4. **线程等待**:
    循环 `n` 次调用 `pthread_join`，确保主线程等待所有子线程执行完毕后再退出。
