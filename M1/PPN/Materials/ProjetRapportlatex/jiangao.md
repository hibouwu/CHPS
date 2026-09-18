# Jiangao's Notes

## 1. Introduction 30-40s

Bonjour, je commence par le contexte général.

Le projet partait d'un prototype MNIST avec un MLP, de l'autodiff en mode reverse et une boucle d'entraînement.

Ce semestre, nous l'avons élargi vers trois directions : GEMM et convolution pour le calcul bas niveau, CNN et Tiny-ImageNet pour des modèles et données plus exigeants, puis MPI pour l'entraînement distribué.

大家好，我先介绍一下整体背景。

该项目基于一个采用多层神经网络（MLP）的 MNIST 原型，采用了反向自学习（autodiff）模式和一个训练循环。

本学期，我们将其扩展到了三个方向：用于低级计算的 GEMM 和卷积；用于更复杂模型和数据的 CNN 和 Tiny-ImageNet；以及用于分布式训练的 MPI。

## 2. GEMM 3min20s-3min40s

### 2.1 méthodologie et environnement 40-45s
Je commence par GEMM, parce qu'il sert à la fois au MLP et au chemin convolutif actuel via im2col. Donc, le comprendre aide déjà à lire une partie importante des performances du système.
Ici, je ne détaille pas encore les implémentations ; je fixe surtout le protocole : plateforme contrôlée, affinité CPU fixée, mesures sur les seuls cœurs physiques, avec à la fois des workloads issus des formes réelles du projet et des matrices carrées de référence.
Ensuite, je comparerai la baseline, puis le blocking, le packing, et enfin les variantes GotoBLAS.
这里我先从 GEMM 讲起，因为它既影响 MLP，也影响当前通过 im2col 实现的卷积路径。所以如果先把 GEMM 讲清楚，后面很多性能现象就更容易理解。
这一页我先不展开具体实现，主要是先交代比较方法：受控平台、固定 CPU 亲和度、只看物理核心，同时既看项目里的真实 workload，也看补充的方阵 benchmark。
接下来我会按顺序比较 baseline、blocking、packing，以及 GotoBLAS 风格的实现。

### 2.2 45s

Cette diapositive définit les chemins comparés. blas et omp servent de points de départ.

Le blocking améliore la réutilisation cache en découpant le calcul en sous-blocs. Le packing réorganise certains panneaux dans des buffers contigus pour rendre les accès mémoire plus réguliers. La parallélisation, elle, répartit ensuite ces blocs entre les threads.

Enfin, les versions GotoBLAS AVX2 et AVX-512 ajoutent une organisation plus hiérarchique : blocking à plusieurs niveaux, packing, puis micro-kernel SIMD.

本幻灯片给出了所比较路径的定义。

blas 和 omp 是上一学期实现的版本。

分块技术会先把计算切成子块，以提高缓存中的数据复用。packing 则是在此基础上，把某些面板重新整理到连续缓冲区里，让内存访问更规则。至于并行化，可以再把这些块分配给不同线程去处理。

最后，GotoBLAS AVX2 和 AVX-512 版本采用了更具层次性的组织结构：多级分块、紧凑排列，然后是微内核 SIMD。

### 2.3 45-55s

Ici, on résume l'idée GotoBLAS.

D'abord, on découpe \(B\) pour obtenir un grand panneau \(B_c\), qu'on peut relier au niveau L3. Ensuite, on découpe \(A\) pour obtenir un bloc \(A_c\), qu'on peut plutôt relier au niveau L2.

En pratique, la parallélisation se fait surtout en découpant \(A\) le long de la dimension \(M\), donc chaque thread travaille sur son propre bloc \(A_c\). Ensuite, \(A_c\) et \(B_c\) sont redécoupés en micro-panneaux \(A_r\) et \(B_r\), qu'on peut relier au niveau L1 et au micro-kernel. Puis, tout à la fin, le micro-kernel met à jour un tout petit bloc \(C_r\) directement dans les registres.

Après cela, on garde simplement la configuration qui donne les meilleurs résultats après tuning ; le détail du réglage figure en annexe.

这里将对 GotoBLAS 类型的组织结构进行更详细的说明。

首先，我们先切分 \(B\)，得到一个比较大的面板 \(B_c\)，这一层可以大致对应到 L3。然后，我们再切分 \(A\)，得到一块 \(A_c\)，这一层可以更接近 L2。

在并行化这一步里，主要是沿着 \(M\) 维去切 \(A\)，所以不同线程会各自处理自己的那一块 \(A_c\)。再往里走一步，\(A_c\) 和 \(B_c\) 还会继续切成更小的微面板，也就是 \(A_r\) 和 \(B_r\)，这一层可以理解成更接近 L1，也更接近 micro-kernel 真正读取的数据。最后，micro-kernel 更新的是最里面那个很小的 \(C_r\)，这一块是直接放在寄存器里的。

再往后，我们就固定采用调参后表现最好的那一组配置；具体调参和筛选过程可以看论文的 annex。

### 2.4 35-45s

Ici, on regarde simplement un cas \(256 \times 256\), avec 1 à 8 threads.

Sur ce cas précis, le blocking seul n'améliore pas encore la base \texttt{omp}, et reste même légèrement en dessous. Le gain visible commence surtout avec le packing. Ensuite, les variantes GotoBLAS vont plus loin : l'AVX2 fait mieux que les chemins OpenMP simples, et l'AVX-512 se rapproche encore davantage d'OpenBLAS.

À 8 threads, OpenBLAS reste le plus rapide, mais l'écart devient bien plus faible.

这张图看的是一个很简单的 case：固定 \(256 \times 256\)，线程数从 1 增加到 8。

首先，在这个 case 上，blocking 单独并没有把最基础的 \texttt{omp} 路径做得更好，甚至还略差一点；真正明显的提升是从 packing 开始出现的。再往后，GotoBLAS 风格的两条路径又进一步提升了表现：AVX2 更好，AVX-512 也更接近 OpenBLAS。

在 8 线程这个点上，OpenBLAS 仍然最快，但差距已经小了很多。

## 8. Entraînement distribué 2min30s-3min

### 8.1 organisation 1min10s-1min20s

Ici, on reste sur l'idée classique du data parallel synchrone : chaque rank garde une copie complète du modèle, mais ne traite que sa propre partie des données. Ensuite, chaque rank fait son forward et son backward en local, puis on synchronise les gradients avant la mise à jour des paramètres.

La différence porte surtout sur la manière d'organiser cette synchronisation. Le chemin le plus simple est le mode paramètre par paramètre, donc un très grand nombre de petites communications. Ensuite, le bucketed regroupe plusieurs gradients dans un même buffer ; l'overlap essaie de lancer une partie de la communication pendant le backward ; et la compression essaie de réduire le volume transmis avant le AllReduce.

这里其实还是最经典的同步数据并行：每个 rank 上都有一份完整的模型，但数据是分开的，各自只处理自己的那一部分。然后每个 rank 先在本地完成 forward 和 backward，再在参数更新之前做梯度同步。

真正变化的主要是同步的组织方式。最简单的是逐参数同步，也就是很多次很小的通信；bucketed 是把多个梯度先合并到一个 buffer 里；overlap 是尽量在 backward 还没结束时就提前发起一部分通信；compression 则是希望在 AllReduce 之前先减少传输的数据量。

### 8.2 résultats 1min10s-1min30s

Sur la page suivante, la figure de gauche montre le cas de strong scaling avec global\_batch fixé. Quand on passe de 1 à 4 processus, le temps par epoch baisse nettement, et on atteint ici un speedup de \(3.90\times\), donc assez proche de l'idéal dans cette configuration.

La figure de droite montre un profile. Elle sert surtout à localiser le coût de synchronisation. Ici, le \texttt{sync\_wait} par step reste très proche entre \texttt{bucketed} et \texttt{overlap\_bucketed}, donc, dans cette configuration, l'overlap ne masque pas encore un gain important.

Autrement dit, la partie MPI fonctionne déjà bien pour la mise à l'échelle de base, mais pour overlap et compression, on est encore dans une phase de validation et d'analyse plus que dans un résultat final stabilisé.

下一页左边这张图，对应的是固定 \texttt{global\_batch} 的 strong scaling。可以看到，从 1 个进程增加到 4 个进程以后，epoch 时间明显下降，这里得到的加速比大约是 \(3.90\times\)，已经比较接近理想情况。

右边这张图是一个 profile，用来定位同步等待的成本。这里可以看到，overlap 机制本身已经激活了，也就是有些 bucket 会在 backward 期间提前发出；只是单机共享内存 MPI 下，AllReduce 延迟本来就很低，所以 \texttt{sync\_wait} 按 step 来看没有明显下降。换到多节点网络场景，这种机制的效果理论上会更明显。

换句话说，MPI 这部分最基本的扩展路径已经能工作了；但 overlap 和 compression 这两条路径，目前更像是在做机制验证和成本分析，还不能讲成已经完全稳定的性能结论。
