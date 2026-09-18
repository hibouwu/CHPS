# Quiz

## Ch.02 Memory layout and cache blocking

### *Q.1 Qu'est ce que la localité spatiale ? Qu'est ce que la localité temporelle ? 什么是空间局部性？什么是时间局部性？

### *Q.2 Quelle est la difference entre le cache L1i et L1d ? `L1i` 和 `L1d` cache 有什么区别？

### *Q.3 Expliquer qu'est ce que le TLB ? 解释什么是 TLB

### Q.4 Qu'est-ce qu'une cache line ? Pourquoi l'accès contigu est-il plus efficace ? 什么是 cache line？为什么连续访问更高效？

### Q.5 Quelle est la différence entre `row-major` et `column-major` ? Pourquoi cela change-t-il la bonne façon de parcourir un tableau ? `row-major` 和 `column-major` 有什么区别？为什么这会改变遍历数组的最佳方式？

### *Q.6 Qu'est ce qu'un tableau de structure (Struct of Array, SoA) ? 什么是 SoA（结构分量分数组）？

### *Q.7 Qu'est ce qu'une structure de tableau (Array of Struct, AoS) ? 什么是 AoS（数组元素为结构体）？

### *Q.8 Expliquez dans quelles cas il est plus judicieux d'utiliser l'une ou l'autre. 解释在什么情况下更适合使用 SoA 或 AoS

### Q.9 Pourquoi l'ordre des champs d'une structure peut-il changer sa taille mémoire ? 为什么结构体字段顺序会改变其内存大小？

### Q.10 Qu'est-ce que le cache blocking ? Pourquoi améliore-t-il les performances ? 什么是 cache blocking？为什么它能提高性能？

## Ch.03 NUMA

### *Q.1 Qu'est ce qu'une architecture NUMA ? Expliquer qu'est ce que l'“effet NUMA” ? 什么是 NUMA 架构？解释什么是“NUMA 效应”

### *Q.2 Expliquer ce qu'est la politique de “first touch”. 解释什么是“first touch”策略

### *Q.3 Est ce que le first touch permet toujours de bien gérer les effets NUMA ? Expliquez la réponse. first touch 是否总能很好地处理 NUMA 效应？请解释

### *Q.4 Qu'est ce que le false-sharing ou faux-partage ? Comment peut-on l'éviter ? 什么是伪共享？如何避免？

### Q.5 Qu'est-ce que la cache coherency ? Pourquoi peut-elle coûter cher ? 什么是 cache coherency？为什么它会带来开销？

### Q.6 Pourquoi l'accès à un cache distant sur le même socket, puis sur un autre socket, est-il plus lent ? Comment peut-on limiter ce problème ? 为什么访问同 socket 的远端 cache、以及跨 socket 的远端 cache 更慢？如何缓解这个问题？

### Q.7 Pourquoi une initialisation parallèle est-elle souvent meilleure qu'une initialisation séquentielle sur une machine NUMA ? 为什么在 NUMA 机器上，并行初始化通常比顺序初始化更好？

### Q.8 Quel est le lien entre data locality et NUMA locality ? 数据局部性和 NUMA 局部性之间是什么关系？

### Q.9 Quelle est la différence entre true sharing et false sharing ? 真共享和伪共享有什么区别？

### Q.10 Pourquoi NUMA affecte-t-il aussi la bande passante et les périphériques d'I/O ? 为什么 NUMA 也会影响带宽和 I/O 设备？

## Ch.04 The Roofline model

### Q.1 Qu'est-ce que le modèle Roofline ? 什么是 Roofline 模型？

### Q.2 Qu'est-ce que l'arithmetic intensity ? 什么是 arithmetic intensity（算术强度）？

### Q.3 Quelle est la différence entre une application memory-bound et compute-bound ? 什么是 memory-bound 和 compute-bound，它们有什么区别？

## Ch.05 Tools

### *Q.1 Citez 4 outils d'analyse et d'optimisation des performances et expliquez leurs usages. 列举 4 种性能分析与优化工具并说明其用途

## Ch.06 Compilers

### Q.1 Quel est le rôle du préprocesseur ? 预处理器的作用是什么？

### Q.2 Qu'est-ce que GIMPLE ? Pourquoi est-il utile ? 什么是 GIMPLE？为什么它有用？

### Q.3 Quel est le rôle du middle-end ? 中端（middle-end）的作用是什么？

## Ch.07 ILP

### *Q.1 Qu'est ce que l'Instruction Level Parallelism (ILP) ? En quoi cela est important pour les performances d'un code ? 什么是指令级并行（ILP）？为什么它对程序性能很重要？

## Ch.08 Vectorization

### *Q.1 Comment fonctionne la vectorisation ? 向量化是如何工作的？

## Ch.09 MPI

### *Q.1 Qu'est ce que la bande passante (bandwidth) lors de l'envoi d'un message MPI ? MPI 消息发送中的带宽是什么？

### *Q.2 Qu'est ce que la latence (latency) lors de l'envoi d'un message MPI ? MPI 消息发送中的延迟是什么？

### Q.3 Qu'est-ce que le domain decomposition ? Pourquoi est-il nécessaire ? 什么是 domain decomposition（域分解）？为什么它是必要的？

### Q.4 Quelle est la différence entre une décomposition verticale et une décomposition horizontale d'un stencil 2D ? 二维 stencil 的垂直分解和水平分解有什么区别？

### *Q.5 Qu'appelle-t-on des mailles “fantômes” (ou ghost cells) ? Quelle est leur utilité ? 什么叫“幽灵单元”或“鬼单元”？它们有什么作用？

### Q.6 Qu'est-ce que l'asynchronous progression ? 什么是 asynchronous progression（异步推进）？

### Q.7 Pourquoi une communication MPI non bloquante ne progresse-t-elle pas toujours toute seule ? 为什么 MPI 非阻塞通信并不一定会自己自动推进？

### *Q.8 Quelle est la différence entre `MPI_Barrier` et `MPI_Ibarrier` ? `MPI_Barrier` 和 `MPI_Ibarrier` 有什么区别？

### *Q.9 Citez 2 topologies réseaux différentes. Expliquez leurs avantages et inconvénients. 列举两种不同的网络拓扑，并说明其优缺点

### *Q.10 Schématiser les échanges de messages entre 8 rangs MPI pour une implémentation efficace de `MPI_Gather`. Expliquer pourquoi un tel choix. 画出 8 个 MPI rank 之间实现高效 `MPI_Gather` 时的消息交换示意，并解释为什么这样设计

## Ch.10 Placement

### Q.1 Pourquoi le placement est-il important ? 为什么 placement 很重要？

### Q.2 Qu'est-ce que `OMP_PLACES` et `OMP_PROC_BIND` ? `OMP_PLACES` 和 `OMP_PROC_BIND` 是什么？

### Q.3 Quelle est la différence entre `close` et `spread` ? `close` 和 `spread` 有什么区别？

## Ch.11 Scalability

### Q.1 Qu'est-ce que la loi d'Amdahl ? 什么是 Amdahl 定律？

### Q.2 Pourquoi la loi d'Amdahl limite-t-elle le speedup ? 为什么 Amdahl 定律会限制 speedup？

### *Q.3 Quelle est la différence entre scalabilité forte (strong scaling) et scalabilité faible (weak scaling) ? 强可扩展性和弱可扩展性有什么区别？

### Q.4 Pourquoi un petit changement dans un schéma de communication peut-il changer fortement la scalabilité ? 为什么通信模式中一个小改动也会显著改变可扩展性？

## Ch.12 Threads-Synchronisation

### *Q.1 Donner les différences (avantages, inconvénients) entre attente active et attente passive. 给出主动等待和被动等待的区别（优点、缺点）

### *Q.2 Quelle est la différence entre `#pragma omp critical` et `#pragma omp atomic` ? `#pragma omp critical` 和 `#pragma omp atomic` 有什么区别？
