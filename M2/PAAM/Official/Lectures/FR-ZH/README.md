# Notes de cours PAAM en français et en chinois · PAAM 法中对照讲义

[PAAM 课程主页](../../../README.md) · [2026–2027 官方资料与历年试题](../../README.md)

Chaque section présente l'explication en français puis en chinois. Les pages d'animation consécutives sont regroupées autour de la même idée. Les liens renvoient aux diapositives anglaises officielles pour relire les figures et le code dans leur contexte.

每节先读法语，再用中文核对同一个概念。连续的演示动画合在一起讲，每节标明新版英文原讲义的页码。要跟代码执行、读性能图或确认伪代码时，直接跳到对应页面。

| Séance / 课次 | Cours / 双语讲义 | Diapositives / 英文原讲义 | TP / 实验 |
|---|---|---|---|
| Introduction / 导读 | [Architectures multicœurs · 多核体系结构](01-welcome.md) | [4 页](../../GitLab/cours/01-welcome.pdf) | — |
| 1 | [Processus, threads et synchronisation · 进程、线程与同步](01-threads.md) | [18 页](../../GitLab/cours/01-threads.pdf) | [Threads](../../GitLab/threads/Readme.md) |
| 2 | [Implémentation des verrous · 锁的实现](02-locks.md) | [53 页](../../GitLab/cours/02-locks.pdf) | [Locks](../../GitLab/locks/Readme.md) |
| 3 | [Algorithmes non bloquants · 非阻塞算法](03-non-blocking.md) | [76 页](../../GitLab/cours/03-non-blocking.pdf) | [Non-blocking](../../GitLab/non-blocking/Readme.md) |
| 4 | [Mémoire transactionnelle · 事务内存](04-stm.md) | [54 页](../../GitLab/cours/04-stm.pdf) | [STM](../../GitLab/stm/Readme.md) |
| 5 | [Mémoire persistante · 持久内存](06-nvmm.md) | [26 页](../../GitLab/cours/06-nvmm.pdf) | [PMEM](../../GitLab/nvmm/Readme.md) |
| Complément / 补充 | [Architectures NUMA · 非均匀内存访问](05-numa.md) | [89 页](../../GitLab/cours/05-numa.pdf) | [NUMA](../../GitLab/numa/Readme.md) |

Les questions de fin de chapitre servent à reformuler une notion ou à rejouer un entrelacement. Pour les verrous et les structures non bloquantes, noter l'état partagé, l'opération atomique et l'instant où elle rend le changement visible. Pour la mémoire persistante, ajouter l'instant où ce changement devient récupérable après panne.

每讲末尾的自检题可以用来复述概念或手推一次线程交错。复习锁和非阻塞算法时，先画共享状态，找出原子操作，再说明修改何时对其他线程可见。遇到持久内存题，再说明修改何时达到崩溃后可恢复的状态。
