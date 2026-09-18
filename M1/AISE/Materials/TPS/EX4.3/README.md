# 练习 3 (Exercice 3)

## 题目描述

> Reprenez le programme de l'exercice précédent en effectuant la somme de tous les éléments du tableau values après leur multiplication par 2.
> 基于上一个练习的程序，在将数组 values 的所有元素乘以 2 之后，计算它们的总和。
>
> La somme devra être réalisée en parallèle.
> 总和必须并行计算。
>
> Pendant qu'un fil d'exécution multiplie par 2 les éléments du tableau values qui lui ont été attribués, il calcule également une somme locale de ces éléments.
> 当一个执行线程将分配给它的 values 数组元素乘以 2 时，它也会计算这些元素的局部和。
>
> Ainsi, chaque fil d'exécution effectue, en parallèle avec les autres fils d'exéctution, une partie de la somme des éléments de values représentée par la variable globale sum.
> 因此，每个执行线程都与其他执行线程并行地对由全局变量 sum 表示的 values 元素总和的一部分进行计算。
>
> Pour finaliser le calcul de la somme globale, tous les fils d'exécution devront contribuer à sum qui devient une variable critique.
> 为了完成全局总和的计算，所有执行线程必须对 sum 做出贡献，sum 变成了一个临界变量。

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#pthreads-3)

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#pthreads-3)

## 解析与纠正 (Éléments de correction)

为了完成全局总和的计算，所有执行线程必须对 `sum` 做出贡献，`sum` 变成了一个临界变量。

由于执行线程现在以并行方式执行，我们必须确保它们对变量 `sum` 的访问（尤其是修改）是互斥的。换句话说，当一个执行线程修改 `sum` 的值时，任何其他执行线程都不能同时修改它。为此，我们使用互斥锁 `lock`。

为了最大化程序的并行性，我们必须尽量减少临界区中的指令数量以及临界区本身的访问次数。这就是为什么（如下面的实现所示）每个执行线程只有在首先计算出数组 `values` 中由它处理的那部分的局部和之后，才访问一次临界区，以便将其加到全局变量 `sum` 上的原因。

我们必须确保它们对变量 `sum` 的访问（尤其是修改）是互斥的。换句话说，当一个执行线程修改 `sum` 的值时，任何其他执行线程都不能同时修改它。为此，我们使用互斥锁 `lock`。

为了最大化程序的并行性，我们必须尽量减少临界区中的指令数量以及临界区本身的访问次数。这就是为什么（如下面的实现所示）每个执行线程只有在首先计算出数组 `values` 中由它处理的那部分的局部和之后，才访问一次临界区，以便将其加到全局变量 `sum` 上的原因。

我们首先选择了第一种解决方案，即实现 POSIX 锁（参见变量 `lock`）。

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int sum = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
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
}
int main(int argc, char ** argv) {
    // ... (参数解析与初始化代码与 EX4.2 类似，略)
    // 完整逻辑请参考 main.c
    // 下面是创建线程和等待线程的关键部分
    
    // ... initialization of values ...
    
    // ... creation of threads ...
    // pthread_create(&tid[i], NULL, work, (void *) &args[i]);
    
    // ... waiting for threads ...
    // pthread_join(tid[i], NULL);
    
    // ... printing result ...
    return 0;
}
```

> [!NOTE]
> 基于使用变量原子更新例程 `atomic_fetch_add` 的解决方案更简单，但需要 C11 支持 (`stdatomic.h`)。

### 第二部分：由特定线程显示结果 (Barrier Synchronization)

在练习的第二部分，要求由 **2号线程** 在所有计算完成但线程销毁之前显示总和。

显示 `sum` 值的操作现在成为 `work` 例程的一部分，但必须仅在以下情况下执行：

1. 由 2 号线程执行，
2. 一旦所有执行线程都对 `sum` 做出了贡献。

为了满足第一个条件，我们将 0 到 `n-1` 之间的逻辑标识符分配给每个执行线程，并通过 `s_args` 结构的新元素 `id` 将其传递给它。然后，在 `work` 例程中，我们在显示 `sum` 之前检查它是否是 2 号执行线程。

为了满足第二个条件，我们使用 **同步屏障 (Barrier Synchronization)**（参见变量 `barrier`）。在初始化屏障时（参见主函数 `main` 中对 `pthread_barrier_init` 的调用），我们指定必须遇到此屏障的执行线程数，即 `n`。

> [!WARNING]
> 不要将屏障放置在确定是否为 2 号线程的条件内！其他执行线程将永远无法到达它，程序将被阻塞。

(完整代码将在下一节提供)

## 代码详解

本练习引入了**临界区 (Critical Section)** 和**互斥锁 (Mutex)** 的概念。

1. **全局变量与锁**:
    `int sum = 0;` 是全局共享变量。
    `pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;` 初始化一个静态互斥锁。

2. **局部计算**:
    每个线程先计算自己负责部分的局部和 `local` (为了减少锁的竞争)。

3. **临界区保护**:
    在更新全局变量 `sum` 时，必须加锁：

    ```c
    pthread_mutex_lock(&lock);
    sum += local;
    pthread_mutex_unlock(&lock);
    ```

    这保证了同一时刻只有一个线程修改 `sum`，避免数据竞争。

4. **主线程输出**:
    所有线程 join 后，主线程打印最终的 `sum`。
