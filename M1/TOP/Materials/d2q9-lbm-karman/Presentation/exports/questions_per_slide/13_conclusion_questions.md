# Slide 13 — Conclusion

## 可能问题

1. **[HIGH]** 如果老师让你只保留一个结论，你最想保留哪一条？为什么？
2. **[HIGH]** 从工程方法论上看，这个项目最值得迁移到别的 HPC 代码中的经验是什么？
3. **[HIGH]** 你的工作里哪些结论只对这个 LBM 代码成立，哪些具有更一般的参考价值？
4. **[HIGH]** 数值正确性是如何验证的？你有 Strouhal 数或升/阻力系数验证吗？
5. **[MEDIUM]** 这里展示的 `+50% MPI` 和 `×10 total` 是同一口径下的数字吗？
6. **[MEDIUM]** 如果老师问"这项工作最大的局限是什么"，你会怎么回答而不削弱整体贡献？
7. **[LOW]** 如果老师问 future work，你如何回答而不越界声明没有实现的事情？

## 已覆盖情况

- **PPT 是/否**：是 — slide 13 列出了方法论主线（validity → MPI → localité → SIMD），+50% MPI，最终结果；底部列出 future work 方向
- **Script 是/否**：是 — `soutenance_partie2_fr.md` §Conclusion 有口头总结：SoA → restrict/ivdep → halo/OMP
- **Gaps**：+50% 和"×10 total"是否同口径没有明确说明；future work 的边界没有口头准备

## 建议回答（法语）

**Si vous ne gardez qu'une seule conclusion ?**
**如果只保留一个结论？**


> La leçon la plus transférable : avant d'optimiser, corriger le benchmark. Le `nanosleep` caché et la formule MLUPS erronée auraient pu invalider tout le travail si on ne les avait pas détectés en premier. Sans une base de mesure valide, les gains suivants n'auraient pas de sens. C'est vrai pour tout code HPC, pas seulement LBM.

最值得迁移的教训是：优化之前，先修正 benchmark。隐藏的 `nanosleep` 和错误的 MLUPS 公式如果没有被首先发现，可能会使整个工作失效。没有有效的测量基础，后续所有增益都没有意义。这对任何 HPC 代码都成立，不只是 LBM。

**Quelle expérience est transférable à d'autres codes HPC ?**
**哪些经验可以迁移到其他 HPC 代码？**


> La démarche en couches : d'abord la validité des mesures, puis réduire la latence de communication (pas le volume), puis améliorer la localité mémoire (layout SoA ou équivalent), puis aider le compilateur à vectoriser (restrict, ivdep, vérification objdump). Chaque couche est un prérequis pour la suivante — notamment, AVX-512 est inefficace sur des données mal organisées.

分层方法：首先确保测量有效性，然后减少通信延迟（而非数据量），再改善内存局部性（SoA 布局或等价形式），最后帮助编译器向量化（restrict, ivdep, objdump 验证）。每一层都是下一层的前提——特别是，数据布局不当时 AVX-512 是低效的。

**Quels résultats sont spécifiques à ce code LBM, et lesquels sont généraux ?**
**哪些结果是 LBM 特有的，哪些具有普遍性？**


> Spécifique à LBM : le gain exact de Pull vs Push, les 7182 messages MPI, le layout SoA pour 9 directions. Général : la domination de la latence sur le volume MPI, l'effet des alias sur l'auto-vectorisation, la nécessité de faire précéder toute vectorisation d'un layout mémoire adapté. Ces principes s'appliquent à la plupart des codes stencil.

LBM 特有的：Pull vs Push 的精确增益、7182 条 MPI 消息、针对 9 个方向的 SoA 布局。具有普遍性的：MPI 延迟比数据量更重要、alias 对自动向量化的影响、向量化之前必须先有适配的内存布局。这些原则适用于大多数 stencil 类代码。

**Le +50% MPI et le ×10 total sont-ils comparables ?**
**+50% MPI 和 ×10 整体倍数是否在同一参考系下？**


> Le +50% MPI (68.7 → 102.75 MLUPS) est mesuré sur la même plateforme macOS, même config (np=2, OMP=1) — c'est une comparaison iso-plateforme et iso-config, directement valide. Le facteur global ×~34 (60 → 2047) est non iso-plateforme — il inclut deux machines différentes. Ces deux chiffres ne sont pas dans le même référentiel et ne doivent pas être mis en regard.

+50% MPI（68.7 → 102.75 MLUPS）是在同一平台 macOS、相同配置（np=2, OMP=1）下测量的——这是同平台、同配置的对比，直接有效。×~34 的整体倍数（60 → 2047）是非同平台的——包含了两台不同的机器。这两个数字不在同一参考系中，不应被放在一起比较。

**Comment avez-vous vérifié la correction numérique ? Strouhal ? Portance/traînée ?**
**你如何验证数值正确性？Strouhal 数？升/阻力系数？**


> Pour chaque étape d'optimisation, on a effectué une comparaison max-delta maille par maille avec les sorties de l'étape précédente — les écarts observés restent au niveau des erreurs d'arrondi FP64. Pour les configurations multi-rang, certaines sorties np=1 ont été comparées à np=2/4 sans anomalie. Visuellement, le sillage de Kármán est visible à Re=96. En revanche, la thèse l'indique explicitement : ni le nombre de Strouhal, ni les coefficients de portance et de traînée, ni une validation numérique indépendante sur l'ensemble des configurations finales ne sont fournis. C'est une limitation documentée du périmètre de ce travail.

每个优化步骤都与前一步的输出做了逐格点 max-delta 比较——差异在 FP64 舍入误差级别。部分 np=1 输出与 np=2/4 输出进行了比较，未发现异常。在 Re=96 下，Kármán 涡街可视化正常。然而，论文明确指出：本报告不提供 Strouhal 数、升/阻力系数，也不进行所有最终配置的独立数值一致性验证。这是本工作范围的已记录局限性。

**Quelle est la principale limitation de ce travail ?**
**这项工作最大的局限是什么？**


> La principale limitation est l'absence de test multi-nœuds pour la Partie 2 : toutes les mesures AMD sont intra-nœud. On ne peut pas confirmer que les optimisations MPI tiennent sur un vrai réseau haute performance. Il n'y a pas non plus de validation physique quantitative (Strouhal, portance, traînée). Ces limites sont documentées et explicitées — elles ne remettent pas en cause les mesures de performance elles-mêmes, qui sont toutes faites sous protocole cohérent.

主要局限是第二部分缺少多节点测试：所有 AMD 测量都是节点内的。无法确认 MPI 优化在真正的高性能网络上同样有效。同样也没有定量物理验证（Strouhal 数、升/阻力系数）。这些局限已被记录并明确说明——它们不质疑性能测量本身的有效性，所有测量都在一致的协议下进行。

## 证据

- +50% MPI (np=2, OMP=1, same config) : `工作记录/优化08.md`, slide 5 + slide 13
- Validité des mesures (prerequisite) : `工作记录/优化01.md`, `工作记录/优化02.md`
- Méthode en couches : `exports/soutenance_partie2_fr.md` §Conclusion
- Résultats finaux officiels : slide 12

## Phrases à éviter

- ❌ "on a amélioré les performances de ×34" — non iso-plateforme ; ne jamais citer ce facteur sans caveat.
- ❌ "nos optimisations fonctionneront de la même façon sur d'autres codes" — certaines sont LBM-spécifiques (Pull/Push, 9 directions) ; generaliser prudemment.
- ❌ "le future work c'est d'implémenter GPU" — ne pas annoncer ce qu'on n'a pas fait ; dire "une piste naturelle serait..." avec conditionnel.
