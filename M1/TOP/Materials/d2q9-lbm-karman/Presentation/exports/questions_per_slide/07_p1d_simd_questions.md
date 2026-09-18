# Slide 7 — P1-D : Diagnostics et décisions (opt14–17, ex. SIMD macOS)

## 可能问题

1. **[HIGH]** 在 Apple M3 上，为什么 `-march=native + #pragma omp simd` 反而退化（-13%/-10%）？
2. **[HIGH]** 你把原因写成 "diagnostic probable"，这和"已经证明"有什么区别？这样说安全吗？
3. **[HIGH]** 如果 `-O3` 已经能生成 `fmla.2d`，再加 SIMD 指示为什么没有收益反而更差？
4. **[MEDIUM]** 为什么专门保留一页讲"没采用"的优化，而不是只汇报成功项？
5. **[MEDIUM]** 这一页的"诊断"对后续 Part 2 的 AVX-512 有什么帮助？
6. **[HIGH]** P1-D 之后，np=1,OMP=4 的数字从 194 降到了 146 MLUPS。这是代码回退吗？
7. **[MEDIUM]** opt16 循环融合（4 路 → 2 路 + `omp simd reduction`）收益是多少？为什么在多核下几乎没有增益？
8. **[LOW]** P1-D 里 overlap MPI、fusion collision、I/O distribué 这几条，最终是否采用了？

## 已覆盖情况

- **PPT 是/否**：是 — slide 7 展示了 SIMD 测试（-13%/-10%），三列（测试/结果/决策），底部注明"Autres travaux P1-D"；用了"diagnostic probable"措辞；无 ✓ 符号；无来源引用
- **Script 是/否**：否 — Part 1 脚本不在提供文件中
- **Gaps**：没有准备"为什么 fmla.2d 已经存在，加 omp simd 反而更慢"的口头解释；没有准备 P1-D 其他工作的最终状态

## 建议回答（法语）

**Pourquoi -march=native + omp simd dégrade sur Apple M3 ?**
**为什么 -march=native + omp simd 在 Apple M3 上反而退化？**


> Le diagnostic probable — et on insiste sur "probable" — est double. D'abord, les accès mémoire ne sont pas encore contigus en AoS : forcer une vectorisation plus large sur des données non contiguës génère plus de gather/scatter que de SIMD efficace. Ensuite, le scheduler P/E cores d'Apple M3 peut répartir les threads entre Performance et Efficiency cores, ce qui déséquilibre les temps d'exécution des sections SIMD. Mais ces deux causes n'ont pas été isolées par des mesures séparées — c'est pourquoi on dit "probable".

我们强调是"可能的"诊断——原因有两个。首先，数据在 AoS 布局下尚未连续：在不连续的数据上强制更宽的向量化，产生的 gather/scatter 比有效的 SIMD 更多。其次，Apple M3 的 P/E core 调度器可能将线程分配到性能核和效率核上，导致 SIMD 各段执行时间不平衡。但这两个原因没有被独立测量隔离——这就是为什么我们说"可能"。

**Pourquoi dire "diagnostic probable" est-il correct ?**
**为什么说「可能的诊断」是正确的？**


> Parce qu'on a observé la régression (-13%, -10%) et qu'on a deux hypothèses cohérentes, mais on n'a pas de mesure qui isole l'une de l'autre. Affirmer "la cause est X" sans preuve déductive serait une sur-interprétation. "Diagnostic probable" indique qu'on a une explication plausible documentée, sans prétendre à une causalité prouvée.

因为我们观察到了退化（-13%，-10%），并有两个合理的假设，但没有能够相互隔离的测量。在没有演绎证明的情况下断言"原因是 X"会是过度解读。"可能的诊断"表明我们有有据可查的合理解释，但不声称已证明因果关系。

**Si -O3 génère déjà fmla.2d, pourquoi ajouter des hints SIMD empire les choses ?**
**如果 -O3 已经生成 fmla.2d，为什么加 SIMD 提示反而更差？**


> Précisément parce que -O3 a déjà choisi le meilleur vecteur possible pour le layout mémoire existant. Ajouter `#pragma omp simd` peut forcer le compilateur à ignorer ses propres analyses de dépendances et à émettre du code vectorisé moins adapté à la disposition mémoire réelle — notamment des loads non contigus qui annulent le bénéfice de la vectorisation.

正是因为 -O3 已经为现有内存布局选择了最合适的向量化方式。加上 `#pragma omp simd` 可能迫使编译器忽略自身的依赖分析，生成对实际内存布局适应性更差的向量化代码——尤其是不连续的 load，会抵消向量化的收益。

**Pourquoi inclure une page sur les pistes non retenues ?**
**为什么要单独列出未采用的优化路线？**


> En HPC, documenter les pistes écartées est aussi important que les gains obtenus. Cela montre que les décisions sont fondées sur des mesures, pas sur des suppositions. Cette page justifie aussi pourquoi AVX-512 est traité séparément en Partie 2 après avoir restructuré les données — ce n'est pas un oubli, c'est une décision explicite.

在 HPC 中，记录被放弃的路线与记录已取得的收益同样重要。这表明决策基于测量，而非假设。这一页也说明了为什么 AVX-512 在第二部分数据重组之后才单独处理——这不是遗漏，而是明确的决策。

**Lien avec la Partie 2 ?**
**与第二部分的联系是什么？**


> Le résultat négatif sur macOS confirme que la vectorisation efficace nécessite d'abord un layout mémoire adapté. C'est exactement la leçon appliquée en Partie 2 : on fait d'abord AoS→SoA (opt18–19), puis on active AVX-512 avec `__restrict__` et `ivdep` (opt20–22). L'ordre n'est pas arbitraire.

macOS 上的负面结果证实了高效向量化首先需要适配的内存布局。这正是第二部分所应用的经验：先做 AoS→SoA（opt18–19），再用 `__restrict__` 和 `ivdep` 激活 AVX-512（opt20–22）。这个顺序不是任意的。

**P1-D a-t-il causé une régression (194 → 146 MLUPS, np=1 OMP=4) ?**
**P1-D 导致了回退吗（194 → 146 MLUPS，np=1 OMP=4）？**


> Non, ce n'est pas une régression du code. La thèse l'explique explicitement : la plateforme macOS avec un ordonnanceur P/E-core hétérogène génère une fluctuation de FOM de ±20–30% pour les configurations multi-thread. 146 MLUPS vs 194 MLUPS est dans cette plage de bruit. Le gain reste positif en mono-nœud multi-processus (np=2,OMP=1 : 122 MLUPS). Les optimisations P1-D n'ont pas dégradé le code — la mesure est simplement moins stable sur cette plateforme.

不是代码回退。论文明确解释：macOS 的异构 P/E-core 调度器对多线程配置会产生 ±20–30% 的 FOM 波动。146 vs 194 MLUPS 在这个噪声范围内。单节点多进程的增益仍然是正的（np=2,OMP=1：122 MLUPS）。P1-D 的优化没有降低代码性能——只是这个平台上的测量不够稳定。

**opt16 — fusion des boucles de collision, quel gain ?**
**opt16 碰撞循环融合——增益是多少？**


> opt16 fusionne les 4 boucles distinctes (density, vx, vy, BGK) en 2, avec `#pragma omp simd reduction` permettant l'accumulation dans les registres SIMD. Résultat : mono-cœur +5%, multi-cœur +1.7%. Le gain multi-cœur est faible parce que les cœurs OpenMP sont déjà occupés à calculer — la fusion réduit les passes sur les 9 directions mais ne change pas la charge globale par thread.

opt16 将 4 个独立循环（density、vx、vy、BGK）合并为 2 个，用 `#pragma omp simd reduction` 允许在 SIMD 寄存器中累积。结果：单核 +5%，多核 +1.7%。多核增益小，是因为 OpenMP 各核已经在满负载计算——融合减少了对 9 个方向的遍历次数，但不改变每个线程的总体计算量。

## 证据

- SIMD régression (-13%, -10%) et fmla.2d objdump : `工作记录/优化15.md`
- Décision de conserver -O3 sur macOS : `工作记录/优化15.md`
- Autres travaux P1-D (overlap, fusion, I/O) : `工作记录/优化14.md`, `工作记录/优化16.md`, `工作记录/优化17.md`
- Slide : `svg_output/07_p1d_simd.svg`

## Phrases à éviter

- ❌ "le P/E core scheduler cause la régression" — c'est l'hypothèse B, pas la cause prouvée ; toujours dire "diagnostic probable".
- ❌ "on a décidé de ne pas faire de SIMD sur macOS" — on a décidé de ne pas ajouter de hints SIMD manuels ; -O3 fait déjà du NEON.
- ❌ "fmla.2d prouve qu'on est déjà optimal sur macOS" — non, cela prouve que le compilateur vectorise ; le gap vs AVX-512 est une différence d'ISA, pas d'optimisation.
