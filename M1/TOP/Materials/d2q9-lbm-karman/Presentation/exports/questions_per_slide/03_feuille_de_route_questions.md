# Slide 3 — Feuille de route (26 optimisations)

## 可能问题

1. **[HIGH]** 为什么整个工作要拆成 Partie 1 和 Partie 2？两个平台的结果能直接比较吗？
2. **[HIGH]** Part 1 先做 validity corrections，这个顺序为什么是必要的？
3. **[MEDIUM]** 路线图里，MPI refactor 和 cache locality 为什么分成两段，而不是合并？
4. **[MEDIUM]** 为什么 Part 2 要换到 AMD x86-64 再讲内存布局和 AVX-512？
5. **[LOW]** 如果老师问"有没有回头修改前一部分的结论"，你怎么说明路线图不是事后拼接的？
6. **[LOW]** 路线图上写的三个 Part 1 jalons（60 → 103 → 194）和两个 Part 2 jalons（216 → 832 → 2047），哪个是最终官方结果？

## 已覆盖情况

- **PPT 是/否**：是 — slide 3 明确写出 4 行 Partie 1 步骤 + 3 行 Partie 2 步骤，附里程碑数字；底部注明"non iso-plateforme"
- **Script 是/否**：是（部分）— `soutenance_partie2_fr.md` §1 解释了为什么换平台，并说明了 dev vs official 的区别
- **Gaps**：没有口头解释"validity corrections 必须先做"的理由；缺乏"两平台结果不可直接比较"的主动说明

## 建议回答（法语）

**Pourquoi deux parties / deux plateformes ?**

> La Partie 1 est réalisée sur macOS AArch64, où on a d'abord corrigé les erreurs de mesure, puis optimisé MPI et la localité mémoire. La Partie 2 passe sur un AMD Ryzen 9 x86-64 parce que AVX-512 n'est pas disponible sur Apple Silicon — c'est une contrainte matérielle, pas un choix arbitraire. Les jalons des deux parties ne sont pas directement comparables : plateformes différentes, configurations différentes.

第一部分在 macOS AArch64 上完成，先修正测量误差，再优化 MPI 和内存局部性。第二部分切换到 AMD Ryzen 9 x86-64，因为 Apple Silicon 不支持 AVX-512——这是硬件限制，不是任意选择。两个部分的里程碑数字不可直接比较：平台不同，配置也不同。

**Pourquoi commencer par les corrections de validité ?**

> Si le benchmark est faussé dès le départ — par exemple un `nanosleep` caché ou une formule MLUPS erronée — toutes les mesures suivantes sont invalides. On ne peut pas comparer un avant/après sur une base biaisée. La correction de validité est donc un prérequis, pas une optimisation optionnelle.

如果 benchmark 从一开始就有误——比如隐藏的 `nanosleep` 或错误的 MLUPS 公式——那么后续所有测量都是无效的。无法在有偏差的基础上做前/后对比。因此，有效性修正是前提条件，不是可选的优化步骤。

**216 MLUPS est-il le point de départ de Partie 2 ou un résultat final ?**

> 216 MLUPS est la référence de développement en début de Partie 2, mesurée après le passage en SoA sur AMD (opt18–19), sans protocole officiel. Ce n'est pas un résultat final. Le seul résultat officiel Partie 2 est 2047 MLUPS (np=1, OMP=16) mesuré sous protocole avec CPU lock.

216 MLUPS 是第二部分开始时的开发参考值，在 AMD 上完成 SoA 转换（opt18–19）后测得，未使用正式协议。它不是最终结果。第二部分唯一的官方结果是在带 CPU lock 的正式协议下测得的 2047 MLUPS（np=1, OMP=16）。

## 证据

- 路线图内容：`svg_output/03_feuille_de_route.svg`
- dev vs official 区别：`exports/soutenance_partie2_fr.md` §1
- nanosleep 必须先修：`工作记录/优化01.md`
- 平台说明：`exports/soutenance_partie2_fr.md` §1

## Phrases à éviter

- ❌ "on a progressé de 60 à 2047 MLUPS" — c'est non iso-plateforme ; formulation risquée sans caveat immédiat.
- ❌ "la Partie 2 améliore la Partie 1" — les deux parties tournent sur des machines différentes ; ce n'est pas une amélioration directe.
