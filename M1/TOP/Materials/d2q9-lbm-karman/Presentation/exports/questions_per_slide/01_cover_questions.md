# Slide 1 — Page de couverture

## 可能问题

1. **[HIGH]** 你的题目里为什么强调 `MPI + OpenMP`，这两个并行层次各自解决什么问题？
2. **[HIGH]** 开场页提到 `26` 个优化，这个数字怎么定义？是代码提交数、实验轮次，还是明确的优化步骤？
3. **[HIGH]** 你在封面页就写出 `2047 MLUPS`，为什么这个数字有代表性？它是 single-process 还是 multi-process 结果？
4. **[MEDIUM]** 为什么选 `D2Q9 LBM` 和 Kármán 涡街这个案例，而不是别的 CFD 模型？
5. **[MEDIUM]** 如果老师问"你的工作核心贡献是什么"，你会用哪一句话概括？
6. **[LOW]** 题目中的 Kármán vortex 有无物理意义，还是只是一个计算 benchmark？

## 已覆盖情况

- **PPT 是/否**：是 — 封面写了 "MPI + OpenMP · D2Q9 LBM · Kármán · 26 optimisations · 2047 MLUPS"
- **Script 是/否**：否 — Part 1 开场脚本未单独提供（soutenance.md 从 Part 2 开始）
- **Gaps**：口头没有准备"26 的定义"和"2047 是 np=1 结论"这两点的简短说明

## 建议回答（法语）

**Q1 — MPI vs OpenMP 分层**

> MPI gère la communication entre processus distincts — ici, le découpage du domaine en colonnes. OpenMP parallélise les boucles à l'intérieur d'un processus sur les cœurs disponibles. Les deux niveaux sont complémentaires : MPI réduit la mémoire partagée requise, OpenMP réduit la surcharge de communication.

MPI 负责进程之间的通信——这里是把计算域按列划分到不同进程。OpenMP 在进程内部对循环进行多核并行。两个层次互补：MPI 减少共享内存需求，OpenMP 减少通信开销。

**Q2 — 26 optimisations**

> Les 26 optimisations correspondent à des étapes numérotées de manière séquentielle dans nos journaux de travail — chacune est un changement de code ou de configuration distinct, validé par une mesure avant/après. Ce n'est pas le nombre de commits, mais le nombre de modifications ciblées et documentées.

26 个优化对应工作日志里按顺序编号的步骤——每一条都是一个独立的代码或配置变更，并用前/后测量来验证。这不是提交次数，而是有文档记录的针对性修改数量。

**Q3 — 2047 MLUPS**

> C'est le meilleur résultat absolu mesuré sur la machine AMD, avec `np=1` et `OMP=16`, sous protocole officiel avec CPU lock. On le cite en couverture parce qu'il représente le plafond de performance atteint. Le meilleur résultat multi-processus est 1071 MLUPS avec `np=2, OMP=4`.

这是在 AMD 机器上测得的最佳绝对值，配置为 `np=1, OMP=16`，在开启 CPU lock 的正式协议下测量。放在封面是因为它代表了所达到的性能上限。最佳多进程结果是 `np=2, OMP=4` 下的 1071 MLUPS。

**Q4 — Choix D2Q9 LBM**

> D2Q9 LBM est un cas classique en HPC : la structure de grille régulière, les 9 directions par cellule, et la séparation collision/propagation en font un benchmark bien documenté. Le Kármán vortex à Re=96 assure que la simulation reste physiquement intéressante tout en étant reproductible.

D2Q9 LBM 是 HPC 领域的经典案例：规则网格结构、每格 9 个方向、碰撞/传播分离，使它成为文档完善的 benchmark。Re=96 的 Kármán 涡街确保仿真在物理上有意义，同时保持可重现性。

**Q5 — Contribution principale**

> La contribution principale est méthodologique : on a montré qu'une chaîne systématique — correction de validité, puis MPI, puis localité mémoire, puis vectorisation — permet de passer de 60 à 2047 MLUPS sur du matériel courant, sans modifier le modèle numérique lui-même.

核心贡献是方法论层面的：我们证明了一条系统化的优化链——先修正有效性，再优化 MPI，再优化内存局部性，最后向量化——可以在普通硬件上将性能从 60 提升到 2047 MLUPS，而无需修改数值模型本身。

## 证据

- 结果来源：`exports/karman_lbm_20260504_final_readable.pptx` slide 1 + slide 12
- 26 个优化的完整列表：`工作记录/优化01.md` … `工作记录/优化26.md`
- 2047 MLUPS 来源：slide 12 final results table (np=1, OMP=16, official protocol)

## Phrases à éviter

- ❌ "2047 MLUPS c'est notre résultat final" — sans préciser que c'est np=1, ça peut sembler cherry-picked.
- ❌ "on a fait 26 améliorations de code" — "amélioration" implique que toutes ont apporté un gain ; certaines (opt15) ont révélé une régression.
