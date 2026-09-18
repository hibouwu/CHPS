# Slide 10 — P2-B : AVX-512 (opt20–22)

## 可能问题

1. **[HIGH]** `opt20`, `opt21`, `opt22` 三步各自解决什么问题？为什么要拆开？
2. **[HIGH]** 你没有手写 intrinsics——那你如何证明编译器真的生成了有效 AVX-512？
3. **[HIGH]** `objdump` 里看到 `zmm` 是否足够？还有什么不能凭此断言？
4. **[HIGH]** `832 MLUPS` 为什么必须标成"chaîne de développement"？
5. **[MEDIUM]** `__restrict__` 和 `#pragma GCC ivdep` 各自告诉编译器什么？
6. **[HIGH]** opt22 之前 GCC 是否已经生成了 FMA 指令？如果已经有了，opt22 的 zmm 带来的是什么新东西？
7. **[LOW]** 如果老师问"你是在优化算法还是在迎合编译器"，你怎么回答？

## 已覆盖情况

- **PPT 是/否**：是 — slide 10 写出了 opt20 k-outer loop, opt21 multicell 4-cell unroll, opt22 `__restrict__` + ivdep；底部 bar "Chaîne de développement : 216 → 832 MLUPS"；暗色代码框显示 objdump 证据（vmovupd zmm23, vaddpd, vdivpd）
- **Script 是/否**：是 — `soutenance_partie2_fr.md` §P2-B 解释了 alias analysis 阻碍、restrict + ivdep 的作用、objdump 验证
- **Gaps**：没有准备"opt20/21/22 各自单独贡献多少"的分项数据；没有 FMA 相关的主动声明

## 建议回答（法语）

**opt20, opt21, opt22 — chacun fait quoi ?**
**opt20、opt21、opt22 各自做了什么？**


> opt20 réorganise les boucles pour mettre k en outer loop : on itère d'abord sur la direction k, puis sur les cellules en j — ce qui rend les accès contigus et permet l'auto-vectorisation. opt21 déroule la boucle sur 4 cellules simultanées pour augmenter l'ILP visible au compilateur. opt22 ajoute `__restrict__` sur les pointeurs et `#pragma GCC ivdep` pour lever l'ambiguïté d'alias — sans quoi GCC hésite à vectoriser car il suppose un éventuel recouvrement. La chaîne va de 216 à 832 MLUPS en développement.

opt20 重组循环，将 k 放在外层：先遍历方向 k，再遍历 j 方向的格点——使访问变为连续，从而允许自动向量化。opt21 将循环展开为同时处理 4 个格点，增加编译器可见的指令级并行度。opt22 在指针上添加 `__restrict__`，并加入 `#pragma GCC ivdep` 以消除 alias 歧义——没有这些，GCC 会因为怀疑潜在的指针重叠而不愿向量化。开发链从 216 提升到 832 MLUPS。

**Comment prouvez-vous qu'AVX-512 est utilisé sans intrinsics ?**
**如何在不写 intrinsics 的情况下证明 AVX-512 被使用了？**


> On a désassemblé le binaire compilé avec `objdump -d`. Dans la boucle interne, on observe `vmovupd (%r10,%rax,1),%zmm23`, `vaddpd` et `vdivpd` sur des registres zmm. Ces instructions ont une largeur de 512 bits — 8 doubles par opération. Le fait qu'elles apparaissent dans la boucle critique confirme que GCC a bien vectorisé avec AVX-512.

我们用 `objdump -d` 反汇编了编译后的二进制文件。在内层循环中，可以观察到 `vmovupd (%r10,%rax,1),%zmm23`、以及在 zmm 寄存器上的 `vaddpd` 和 `vdivpd`。这些指令宽度为 512 位——每次操作处理 8 个 double。它们出现在关键循环中，确认 GCC 确实使用了 AVX-512 进行向量化。

**Que ne peut-on pas déduire du seul fait de voir zmm ?**
**仅仅看到 zmm 不能推断出什么？**


> On peut confirmer que le compilateur émet des instructions AVX-512. On ne peut pas déduire, sans analyse plus fine (perf counters, VTune), que le pipeline AVX-512 est le seul chemin actif, ni qu'il n'y a pas de dégradation liée au throttling de fréquence AVX-512 sur certains processeurs. Sur Zen4, ce throttling est moins problématique qu'Intel, mais on ne l'a pas mesuré explicitement.

我们可以确认编译器发出了 AVX-512 指令。但在没有更细致分析（性能计数器、VTune）的情况下，无法推断 AVX-512 流水线是唯一活跃路径，也无法排除某些处理器上 AVX-512 频率降档带来的性能损失。在 Zen4 上，这种降档比 Intel 上的问题少，但我们没有显式测量。

**Pourquoi 832 MLUPS est "dev", pas officiel ?**
**为什么 832 MLUPS 是「开发数据」而非正式数据？**


> 832 MLUPS a été mesuré pendant la phase de développement, probablement sans CPU lock ni protocole formel. C'est un chiffre de chaîne pour montrer la progression relative — il n'est pas directement comparable aux 2047 MLUPS finaux qui eux sont mesurés sous protocole officiel complet.

832 MLUPS 是在开发阶段测量的，很可能没有使用 CPU lock 或正式协议。这是一个用于展示相对进展的链式数字——不能直接与在完整正式协议下测得的最终 2047 MLUPS 相比较。

**`__restrict__` vs ivdep — quelle différence ?**
**`__restrict__` 和 ivdep 有什么区别？**


> `__restrict__` dit au compilateur que deux pointeurs ne se chevauchent pas en mémoire — il peut supposer l'absence d'alias et vectoriser sans générer de code scalaire de repli. `#pragma GCC ivdep` dit au compilateur d'ignorer les dépendances supposées à l'intérieur d'une boucle : si GCC hésite sur une dépendance de boucle, ivdep l'autorise à vectoriser quand même. Les deux lèvent des blocages différents de l'analyse d'alias.

`__restrict__` 告诉编译器两个指针在内存中不重叠——它可以假设没有 alias，无需生成标量回退代码就可以向量化。`#pragma GCC ivdep` 告诉编译器忽略循环内假设的依赖关系：如果 GCC 对某个循环依赖犹豫不决，ivdep 允许它无论如何进行向量化。两者解除的是 alias 分析中不同的阻碍。

**GCC générait-il déjà des FMA avant opt22 ?**
**opt22 之前 GCC 是否已经生成 FMA 指令？**


> Oui. L'audit FMA (opt23, vérification a posteriori) montre 92 instructions `vfmadd231pd` dans le binaire après opt22 — ce qui confirme que GCC fusionnait déjà les multiplications-additions de la distribution BGK. Cela signifie que les FMA existaient probablement avant opt22 grâce à `-O3`. Ce qu'opt22 apporte n'est donc pas les FMA, mais le passage de registres xmm/ymm (128/256 bits) à zmm (512 bits), c'est-à-dire doubler la largeur SIMD de 4 à 8 doubles par opération. Le gain +97% (423→832) vient principalement de cette augmentation de largeur vectorielle, combinée à la suppression de l'ambiguïté d'alias.

是的。FMA 审计（opt23，事后验证）在 opt22 之后的二进制中发现了 92 条 `vfmadd231pd` 指令——证实 GCC 已经在融合 BGK 分布的乘加运算。这意味着 FMA 在 opt22 之前可能就已经存在（由 `-O3` 生成）。opt22 带来的不是 FMA，而是从 xmm/ymm 寄存器（128/256 位）升级到 zmm（512 位），即每次操作的向量宽度从 4 个 double 翻倍到 8 个 double。+97% 的增益（423→832）主要来自这个向量宽度的提升，加上消除了 alias 歧义。

## 证据

- objdump zmm : `vmovupd (%r10,%rax,1),%zmm23`, `vaddpd`, `vdivpd` : `工作记录/优化22.md`
- 开发链 216→319→423→832 : `工作记录/优化20.md` (216→319), `工作记录/优化21.md` (319→423), `工作记录/优化22.md` (423→832)
- 无手写 intrinsics : `工作记录/优化22.md`
- Script oral : `exports/soutenance_partie2_fr.md` §P2-B

## Phrases à éviter

- ❌ "AVX-512 multiplie les performances par 8" — le gain réel est de ×~2 (423→832), pas ×8 ; le facteur 8 est théorique.
- ❌ "on utilise des FMA AVX-512" — `vdivpd` est visible, mais des FMA (`vfmadd`) n'ont pas été explicitement listés dans le PPT ; ne pas affirmer sans vérification dans `优化22.md`.
- ❌ "sans `__restrict__` il n'y a aucune vectorisation" — il peut y avoir de la vectorisation partielle ; la restriction lève un blocage, ne crée pas la vectorisation de zéro.
