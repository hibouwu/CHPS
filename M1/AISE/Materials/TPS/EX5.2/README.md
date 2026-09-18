# 练习 2 (Exercice 2)

## 题目描述

> Le code source ci-dessous permet de calculer le produit d'une matrice par un vecteur.
> 下面的源代码用于计算矩阵与向量的乘积。
>
> Étudiez le code source et parallélisez le calcul dans la fonction matvec_kernel à l'aide des directives et des clauses OpenMP que vous jugerez adaptées à ce cas de figure.
> 研究源代码并使用您认为适合这种情况的 OpenMP 指令和子句在 matvec_kernel 函数中并行化计算。

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#omp-2)

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#omp-2)

## 解析与纠正 (Éléments de correction)

为了并行化 `matvec_kernel` 函数中的计算，我们再次使用了 OpenMP 指令 `parallel for`。

与前面的练习相反，我们在这里没有归约。实际上，对于外循环（迭代器 `i`）的每次迭代，只有一个执行线程会访问 `res[i]` 元素进行写入。只要多个执行线程不处理相同的迭代 `i`，就没有数据竞争的风险。 `parallel for` 指令向我们保证了这一点。

另一方面，我们必须特别注意内循环（迭代器 `j`）。就像前面的练习一样，迭代变量 `j` 必须是私有的。

```c
void matvec_kernel(size_t n, size_t m, const double * A, const double * x, double * res) {
    size_t j;
    #pragma omp parallel for private(j)
    for(size_t i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            res[i] += A[i * m + j] * x[j];
        }
    }
}
```

## 代码详解

本练习展示了嵌套循环的并行化。

1. **外层循环并行化**:
    `#pragma omp parallel for private(j)` 应用于外层循环 `for(i...)`。
    这会将不同的行 `i` 分配给不同的线程处理。
    由于每行的计算是独立的（结果写入 `c[i]`），这是最简单的并行化策略。

2. **私有变量**:
    `private(j)` 是必须的，因为内部循环变量 `j` 对于每个线程（即每个 `i` 的迭代）必须是独立的。
    注意：在 C99 中，如果在循环头声明 (`for(int j...)`)，则自动为私有。但这里 `j` 在外部声明，所以需要显式指定。
