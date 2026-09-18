# 练习 1 (Exercice 1)

## 题目描述

> Le code source ci-dessous permet de calculer une approximation de la valeur de π.
> 下面的源代码用于计算 π 值的近似值。
>
> Il y a deux fonctions de calcul pi_reference et pi_kernel.
> 有两个计算函数 pi_reference 和 pi_kernel。
>
> Étudiez le code source et parallélisez le calcul dans la fonction pi_kernel à l'aide des directives et des clauses OpenMP que vous jugerez adaptées à ce cas de figure.
> 研究源代码并使用您认为适合这种情况的 OpenMP 指令和子句在 pi_kernel 函数中并行化计算。

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#omp-1)

## 解析与纠正 (Éléments de correction)

为了并行化 `pi_kernel` 函数中的计算，我们使用了 OpenMP 指令 `parallel for`，该指令自动在多个执行线程之间分配我们循环的迭代。

但是，`pi_kernel` 函数在每一步迭代中：

1. 更新 `sum` 变量，
2. 使用 `term` 变量。

因此，所有执行线程都要访问 `sum` 变量。由于我们希望迭代顺序和分配给不同执行线程的方式不会影响最终结果，因此我们通过 `reduction(+:sum)` 子句指定 `sum` 是一个归约变量。

至于 `term` 变量，每个执行线程都必须有自己的私有副本才能正确执行计算。因此，我们添加 `private(term)` 子句。

**注意**: 我们没有在 `private` 子句的参数列表中包括循环索引 `i`，因为 C/C++ 的 OpenMP 标准规定循环索引会自动变为私有变量。

```c
double pi_kernel(size_t n) {
    double sum = 0.0;
    double term;
    #pragma omp parallel for reduction(+:sum) private(term)
    for(size_t i = 0; i < n; i++) {
        term = 1.0 / (2.0 * (double) i + 1.0);
        if(i % 2) {
            sum -= term;
        } else {
            sum += term;
        }
    }
    return 4.0 * sum;
}
```

## 代码详解

本练习展示了 OpenMP 的基本用法：并行循环和归约。

1. **并行循环**:
    `#pragma omp parallel for` 将 `for` 循环的迭代分配给多个线程。

2. **归约 (Reduction)**:
    `reduction(+:sum)` 告诉 OpenMP `sum` 是一个归约变量。这意味着每个线程都有自己的 `sum` 副本，循环结束时，这些副本将被相加（`+`）到全局 `sum` 中。

3. **私有变量 (Private)**:
    `private(term)` 声明 `term` 为私有变量。每个线程需要自己的 `term` 副本，因为它的值取决于迭代索引 `i`。如果 `term` 是共享的（默认），线程间会发生数据竞争。
