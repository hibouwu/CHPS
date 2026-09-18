# Slide 12 — Résultats finaux

## 可能问题

1. **[HIGH]** 为什么绝对最优是 `np=1, OMP=16`？多进程反而不如单进程，这说明了什么？
2. **[HIGH]** 为什么最佳多进程是 `np=2, OMP=4`，而不是 `np=4, OMP=4` 或其他？
3. **[HIGH]** 完整结果表里有 5 个配置（np=1/2/4 × OMP=4/8/16），为什么 np=2,OMP=8=870 反而比 np=2,OMP=4=1071 差？
4. **[HIGH]** np=4,OMP=4=535 远低于 np=2,OMP=4=1071，原因是什么？
5. **[MEDIUM]** `OMP_PROC_BIND` 没有设置会有什么影响？为什么不能用 `OMP_PROC_BIND=close`？
6. **[MEDIUM]** 这些结果和 Part 1 的数字能直接比较吗？如果不能，你如何给出结论？
7. **[LOW]** 协议里 20 次重复取中位数——如果你只取平均值会有什么影响？

## 已覆盖情况

- **PPT 是/否**：是 — slide 12 写出了 2047 MLUPS (np=1, OMP=16) 和 1071 MLUPS (np=2, OMP=4)；注明"protocole officiel"；底部注"gain global indicatif · non iso-plateforme"
- **Script 是/否**：是 — `soutenance_partie2_fr.md` §Final results 覆盖了两个结果，并说明了跨平台比较的谨慎态度
- **Gaps**：没有准备"为什么 np=4 更差"的口头解释；中位数 vs 平均值的选择没有口头说明

## 建议回答（法语）

**Pourquoi np=1, OMP=16 est-il le meilleur résultat absolu ?**
**为什么 np=1, OMP=16 是绝对最优结果？**


> Avec np=1, il n'y a aucune communication MPI — zéro échange de halo, zéro latence de message. Les 16 threads OpenMP exploitent tous les cœurs disponibles en mémoire partagée. Avec np=2 ou plus, on ajoute un coût MPI (même réduit) qui n'existe pas en np=1. Sur cette machine à un seul nœud, la communication intra-nœud via MPI est plus coûteuse que la parallélisation OpenMP seule.

np=1 时完全没有 MPI 通信——零 halo 交换，零消息延迟。16 个 OpenMP 线程在共享内存中利用所有可用核心。np=2 或更多时，会增加 MPI 开销（即使已被优化减少），而这在 np=1 时不存在。在这台单节点机器上，MPI 节点内通信比纯 OpenMP 并行化更昂贵。

**Pourquoi np=2, OMP=4 plutôt que np=4 ?**
**为什么 np=2, OMP=4 比 np=4 更好？**


> À vérifier dans les données de benchmark. L'hypothèse probable est qu'avec np=4 on a trop peu de threads OpenMP par rang (OMP=2 ou OMP=4 avec moins de cœurs disponibles), et le surcoût MPI entre 4 rangs dépasse le gain de décomposition de domaine. np=2, OMP=4 offre le meilleur compromis communication/calcul sur cette machine.

待 benchmark 数据确认。合理的假设是：np=4 时每个 rank 的 OpenMP 线程数太少（可用核心更少），4 个 rank 间的 MPI 开销超过了域分解的收益。np=2, OMP=4 在这台机器上提供了通信/计算的最佳平衡。

**Peut-on comparer 2047 MLUPS (AMD) avec 194 MLUPS (macOS) ?**
**可以将 2047 MLUPS（AMD）与 194 MLUPS（macOS）直接比较吗？**


> Non directement. Les deux nombres viennent de machines différentes (AMD Zen4 vs Apple M3), avec des jeux d'optimisations différents, et des configurations différentes. On peut dire que les techniques appliquées en Partie 2 ont conduit à un gain très significatif sur AMD, mais la différence absolue reflète à la fois les optimisations et la différence matérielle. C'est pourquoi on dit "gain global indicatif, non iso-plateforme".

不能直接比较。两个数字来自不同的机器（AMD Zen4 vs Apple M3），优化集合不同，配置也不同。可以说第二部分应用的技术在 AMD 上带来了非常显著的提升，但绝对差异同时反映了优化效果和硬件差异。这就是为什么要说"非同平台的指示性整体增益"。

**Médiane vs moyenne — pourquoi la médiane ?**
**中位数 vs 平均值——为什么选中位数？**


> Les 20 répétitions peuvent inclure des outliers dus aux interruptions OS, à des migrations de processus, ou à des pics thermiques. La médiane est robuste à ces valeurs extrêmes — un seul run anormalement lent ne fausse pas le résultat. La moyenne, elle, serait tirée vers le bas par les outliers.

20 次重复中可能包含因 OS 中断、进程迁移或热峰值产生的异常值。中位数对这些极值具有鲁棒性——一次异常慢的运行不会扭曲结果。而平均值则会被这些异常值拉低。

**Pourquoi np=2, OMP=8 (870) est-il inférieur à np=2, OMP=4 (1071) ?**
**为什么 np=2, OMP=8（870）低于 np=2, OMP=4（1071）？**


> La configuration np=2, OMP=8 a été utilisée comme configuration fixe pour l'analyse de profiling par phase (P2-D), pas pour maximiser le FOM. Avec OMP=8, il y a plus de threads par rang, mais le profiling lui-même (`LBM_ENABLE_PROFILING=ON`) ajoute un overhead de mesure sur les 6 phases. La comparaison équitable est faite avec `PROFILING=OFF` — dans ce cas np=2,OMP=4 reste optimal sur cette machine.

np=2, OMP=8 是作为固定配置用于 P2-D 的分相 profiling 分析，不是为了最大化 FOM。开启 profiling（`LBM_ENABLE_PROFILING=ON`）本身在 6 个阶段上增加了测量开销。公平比较应该在 `PROFILING=OFF` 下进行——此时 np=2,OMP=4 在这台机器上仍然最优。

**Pourquoi np=4, OMP=4 (535) est-il si bas ?**
**为什么 np=4, OMP=4（535）如此之低？**


> Avec np=4, on a 4 rangs MPI × 4 threads = 16 threads en tout — autant que np=1,OMP=16 (2047) ou np=2,OMP=4 (1071). Mais avec 4 rangs, le coût de synchronisation MPI est beaucoup plus élevé : halo\_finish représente une part plus grande du temps par itération. De plus, les 4 rangs de bord haut et bas ont une charge halo différente des rangs intermédiaires, ce qui crée un déséquilibre amplificateur pour MPI\_Waitall. Sur une seule machine, MPI à 4 rangs est contre-productif.

np=4 时有 4 个 MPI rank × 4 线程 = 总共 16 线程——与 np=1,OMP=16（2047）或 np=2,OMP=4（1071）线程数相同。但 4 个 rank 的 MPI 同步成本高得多：halo_finish 占每次迭代时间的比例更大。此外，边界 rank 和中间 rank 的 halo 负载不同，放大了 MPI_Waitall 的不平衡。在单台机器上，4 个 MPI rank 是适得其反的。

**Pourquoi ne pas utiliser OMP\_PROC\_BIND=close ?**
**为什么不使用 OMP_PROC_BIND=close？**


> La thèse le signale explicitement : sans politique coordonnée de placement MPI, `OMP_PROC_BIND=close` fait que les threads de rangs MPI différents se disputent les mêmes cœurs physiques — baisse mesurée de ~15% du FOM. Ne pas définir `OMP_PROC_BIND` laisse l'OS choisir une distribution qui évite ces conflits sur cette machine.

论文明确指出：在没有协调 MPI 进程绑核策略的情况下，`OMP_PROC_BIND=close` 会导致不同 MPI rank 的线程竞争同一物理核心——实测 FOM 下降约 15%。不设置 `OMP_PROC_BIND` 让 OS 自行选择分配，在这台机器上可以避免这种竞争。

## 证据

- 完整结果表（5 个配置）：`rapport/report_cn.tex` §Validation finale, 以及 `scripts/bench.txt`
- 2047 MLUPS (np=1, OMP=16), 1071 MLUPS (np=2, OMP=4) : source originale PDF du projet (à vérifier : pas trouvé dans les 优化.md individuels)
- Protocole officiel complet : `工作记录/优化22.md` ou fichier de protocole dédié (à vérifier)
- Script oral : `exports/soutenance_partie2_fr.md` §Final results
- Non iso-plateforme disclaimer : `svg_output/03_feuille_de_route.svg` + slide 12

## Phrases à éviter

- ❌ "on a multiplié les performances par 34 (60 → 2047)" — non iso-plateforme, configurations différentes.
- ❌ "le résultat multi-processus est décevant" — 1071 MLUPS est un bon résultat ; l'expliquer en termes de trade-off MPI/OMP, pas de déception.
- ❌ "np=1 prouve que MPI ne sert à rien" — np=1 est la config optimale sur une seule machine ; MPI est indispensable sur cluster multi-nœuds.
