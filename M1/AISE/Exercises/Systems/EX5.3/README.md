# 练习 3 (Exercice 3)

## 题目描述

> Le code source ci-dessous permet de calculer le nème terme de la suite de Fibonacci.Il y a trois fonctions de calcul fibonacci_reference, fibonacci_kernel_sections et fibonacci_kernel_tasks. La première représente une implémentation séquentielle de référence de la suite de Fibonacci. Les deux dernières représentent des implémentations séquentielles à paralléliser.
> 下面的源代码用于计算斐波那契数列的第 n 项。其中包含三个计算函数： fibonacci_reference 、 fibonacci_kernel_sections 和 fibonacci_kernel_tasks 。第一个函数实现的是斐波那契数列的顺序参考实现，后两个函数则实现了可并行化的顺序实现方案。
>
> 1. Étudiez le code source et parallélisez le calcul dans la fonction fibonacci_kernel_sections à l'aide des sections OpenMP.
>    研究源代码并使用 OpenMP sections 在函数 fibonacci_kernel_sections 中并行化计算。
> 2. Changez la valeur de la macro NESTED à 1. Quelles sont les implications de ce changement sur le comportement du programme et sur son temps d'exécution ?
> 3. À présent, paralléliser le calcul dans la fonction fibonacci_kernel_tasks à l'aide des tâches OpenMP.
>    现在，使用 OpenMP tasks 在函数 fibonacci_kernel_tasks 中并行化计算。

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#omp-3)

## 解析与纠正 (Éléments de correction)

### 1. 使用 Sections

首先，我们将 `fibonacci_kernel_sections` 函数的两个递归调用分别放入 OpenMP 部分 (`section`) 中，它们本身包含在 `parallel sections` 区域中。

```c
size_t fibonacci_kernel_sections(size_t n) {
    size_t x, y;
    if(n < 2) return n;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            x = fibonacci_kernel_sections(n - 1);
        }
        #pragma omp section
        {
            y = fibonacci_kernel_sections(n - 2);
        }
    }
    return x + y;
}
```

可以很容易地验证，这种方法不仅效率低下，而且如果不限制嵌套并行区域的数量，还会导致程序崩溃。
实际上，每次进入 `parallel sections` 区域时，OpenMP 都会创建一个新的执行线程组，这会通过使操作系统过载而很快耗尽可用资源。

### 2. 使用 Tasks

为了解决此问题，我们使用 OpenMP 任务（`task`）。

OpenMP 任务允许创建一个要执行的作业池，执行线程组（在此练习中我们在主函数 `main` 中创建一次）根据可用性从中获取作业。

我们定义一个 `parallel` 区域，由单个执行线程执行（指令 `single`），它将通过递归调用 `fibonacci_kernel_tasks` 函数来生成任务。

对于每个递归调用，我们创建一个任务计算 `n-1` 的项，而当前执行线程负责计算 `n-2` 的项并在将结果相加之前等待创建的任务完成。

此外，为了避免创建过多任务，我们仅并在 `n` 大于或等于 20 时才创建任务。否则，我们按顺序进行计算。

```c
size_t fibonacci_kernel_tasks(size_t n) {
    size_t x, y;
    if(n < 20) return fibonacci_reference(n);
    #pragma omp task shared(x)
    {
        x = fibonacci_kernel_tasks(n - 1);
    }
    y = fibonacci_kernel_tasks(n - 2);
    #pragma omp taskwait
    return x + y;
}
```

注意：在 `main` 函数中，我们需要用 `#pragma omp parallel` 和 `#pragma omp single` 包裹初始调用，或者直接在 kernel 外部做。但根据题目，我们主要关注 kernel 内部。网站上的完整代码展示了如何在 `main` 或 wrapper 中启动。

## 代码详解

本练习比较了 OpenMP 的 **Sections** 和 **Tasks** 两种并行模式。

### 1. Sections (`fibonacci_kernel_sections`)

- 使用 `#pragma omp parallel sections` 创建并行区域。
- 使用 `#pragma omp section` 定义两个独立的任务块（递归调用）。
- **缺点**: `parallel sections` 每次递归都会创建新的线程组（除非被优化或受限于最大线程数），开销巨大且不灵活。

### 2. Tasks (`fibonacci_kernel_tasks`)

- 这... (Wait, line 26 is "这是递归算法...")
- `#pragma omp task shared(x)` 创建一个任务来计算 `x`，该任务被放入池中由空闲线程执行。
- `#pragma omp taskwait` 等待所有子任务完成，确保 `x` 和 `y` 已计算完毕后再相加。
- **优化**: 代码中包含 `if(n < 20) return fibonacci_reference(n);` 这类截止条件，避免为太小的任务创建 task，显著减少开销。
