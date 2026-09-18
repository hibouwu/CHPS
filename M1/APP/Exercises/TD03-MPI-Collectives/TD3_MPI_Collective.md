# Algorithmique et Programmation Parallèles TD 3 - Communications collectives bloquantes MPI / 并行算法与编程 TD 3 - 阻塞式 MPI 集体通信

## Exercice I : Produit scalaire / 练习 I：点积

Soit la fonction :
给定函数：

```c
double produit_scalaire(int N, double *a, double *b)
{
    double res = 0;
    for (int i = 0; i < N; i++)
        res += a[i] * b[i];
    return res;
}
```

qui calcule le produit scalaire de deux vecteurs `a` et `b` de dimension `N` en séquentiel.
该函数按顺序方式计算两个维度为 `N` 的向量 `a` 和 `b` 的点积。

**Question :** En complétant le fichier `prod_scal/exo_prod_scal.c`, paralléliser la fonction `produit_scalaire` dans le cas où `a` et `b` sont des vecteurs distribués sur tous les processus MPI (`N` devient alors le nombre d'éléments associés au processus MPI appelant `produit_scalaire`).
**问题：** 补全文件 `prod_scal/exo_prod_scal.c`，在 `a` 和 `b` 被分布到所有 MPI 进程上的情况下并行化函数 `produit_scalaire`（此时 `N` 表示调用 `produit_scalaire` 的当前 MPI 进程所持有的元素个数）。

## Exercice II : Réduction / 练习 II：归约

**Question :** Écrire la fonction :
**问题：** 编写函数：

```c
double reduction_somme(double in);
```

qui retourne la somme de tous les `in` de tous les processus MPI :
该函数返回所有 MPI 进程中 `in` 的总和：

- en utilisant des communications point à point bloquantes ;
  使用阻塞式点对点通信；
- en utilisant des communications collectives autres que `MPI_Reduce` et `MPI_Allreduce`.
  使用 `MPI_Reduce` 和 `MPI_Allreduce` 之外的集体通信。

Tester cette fonction en reprenant l'exercice I.
通过复用练习 I 的场景测试这个函数。

## Exercice III : Pièges sur les collectives / 练习 III：集体通信陷阱

Dans le répertoire `pieges_coll/pieges/`, les fichiers suivants comportent des erreurs :
在目录 `pieges_coll/pieges/` 中，下面这些文件包含错误：

a) `piege_barriere.c`  
b) `piege_scatter.c`  
c) `piege_coll.c`

Expliquez les erreurs, apportez les corrections.
解释这些错误，并给出修正。

## Exercice IV : Implémentation d'un broadcast / 练习 IV：实现一个广播

Le programme `algo_bcast/exercice/mpi_bcast.c` prend en argument un entier `n` qui représente la taille en octets d'un tableau.
程序 `algo_bcast/exercice/mpi_bcast.c` 接收一个整数参数 `n`，表示某个数组的字节大小。

Seul le processus de rang 0 remplit ce tableau et le diffuse 100 fois aux autres processus en utilisant la fonction `MPI_Bcast`.
只有 0 号进程会填充这个数组，并使用函数 `MPI_Bcast` 将其向其他进程广播 100 次。

**Question 1 :** Mesurer le temps pris par ce programme initial avec `n = 1000` pour des nombres respectifs de processus de 2, 4, 8, 16, 32 et 48.
**问题 1：** 在 `n = 1000` 的情况下，分别测量该初始程序在 2、4、8、16、32 和 48 个进程下的耗时。

À présent, on désire implémenter nous-même notre propre communication collective mais en utilisant uniquement les communications point-à-point `MPI_Send` et `MPI_Recv`.
现在，我们希望自己实现这个集体通信，但只能使用点对点通信 `MPI_Send` 和 `MPI_Recv`。

**Question 2 :** Implémenter l'algorithme linéaire (voir figure 1). Remplacer l'appel à `MPI_Bcast` par une fonction `linear_bcast`. Faire les mesures de temps et les comparer au programme initial.
**问题 2：** 实现线性算法（见图 1）。用函数 `linear_bcast` 替换对 `MPI_Bcast` 的调用。测量耗时，并与原始程序进行比较。

**Question 3 :** Implémenter le premier algorithme en arbre binaire (voir figure 2). Remplacer l'appel à `MPI_Bcast` par une fonction `btreev1_bcast`. Faire les mesures de temps et les comparer au programme initial.
**问题 3：** 实现第一个二叉树算法（见图 2）。用函数 `btreev1_bcast` 替换对 `MPI_Bcast` 的调用。测量耗时，并与原始程序进行比较。

**Question 4 :** Implémenter le deuxième algorithme en arbre binaire (voir figure 3). Remplacer l'appel à `MPI_Bcast` par une fonction `btreev2_bcast`. Faire les mesures de temps et les comparer au programme initial.
**问题 4：** 实现第二个二叉树算法（见图 3）。用函数 `btreev2_bcast` 替换对 `MPI_Bcast` 的调用。测量耗时，并与原始程序进行比较。

**Question 5 :** Implémenter un algorithme qui prenne en compte la topologie du cluster. Faire les mesures de temps et les comparer aux programmes précédents. Pour ce faire :
**问题 5：** 实现一个考虑集群拓扑结构的算法。测量耗时，并与前面的程序进行比较。为此：

a) Créer des communicateurs pour les processus qui appartiennent aux mêmes nœuds (utiliser la fonction `MPI_Comm_split_type` et la constante `MPI_COMM_TYPE_SHARED`).  
   为属于同一节点的进程创建通信器（使用函数 `MPI_Comm_split_type` 和常量 `MPI_COMM_TYPE_SHARED`）。  
b) Désigner un processus maître par nœud et créer le communicateur de tous les processus maîtres.  
   为每个节点指定一个主进程，并创建由所有主进程组成的通信器。  
c) En s'appuyant sur le deuxième algorithme en arbre binaire, implémenter le broadcast en diffusant d'abord le tableau entre les nœuds puis en le diffusant à l'intérieur des nœuds.  
   基于第二个二叉树算法，实现一个广播：先在节点之间传播数组，再在各节点内部传播。

![Figure 1 / 图 1](<Images/td3_fig1_algorithme_lineaire.jpg>)

Fig. 1 - Algorithme linéaire / 图 1 - 线性算法

```text
for (i = 1; i < p; i++)
    if (rank == 0)
        send(data, i)
```

![Figure 2 / 图 2](<Images/td3_fig2_binary_tree_v1.jpg>)

Fig. 2 - Binary tree V1 / 图 2 - 二叉树 V1

```text
for (i = 0; i < log(p); i++)
    if (rank < 2^i)
        send(data, rank + 2^i)
```

![Figure 3 / 图 3](<Images/td3_fig3_binary_tree_v2.jpg>)

Fig. 3 - Binary tree V2 / 图 3 - 二叉树 V2

```text
for (i = log(p); i > 0; i--)
    if (rank % 2^i == 0)
        send(data, rank + 2^(i - 1))
```
