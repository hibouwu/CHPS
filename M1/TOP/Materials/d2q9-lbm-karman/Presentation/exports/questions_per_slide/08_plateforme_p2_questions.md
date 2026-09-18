# Slide 8 — Transition Partie 2 : plateforme AMD + protocole

## 可能问题

1. **[HIGH]** 为什么换到 AMD x86-64，而不是继续在 macOS 上完成 AVX-512 工作？
2. **[HIGH]** `CPU lock`、`drop_caches`、`1 warm-up + 20 reps + médiane` 各自解决什么测量偏差？
3. **[HIGH]** 你如何证明这台机器确实支持并使用了 AVX-512？
4. **[MEDIUM]** `Référence P2 dev : 216 MLUPS` 为什么标成 dev？它是在什么条件下测的？
5. **[MEDIUM]** 为什么这一页同时出现平台信息和 protocol，而不是分成两页？
6. **[LOW]** 跨平台比较是否公平？你如何给出谨慎但不回避的回答？

## 已覆盖情况

- **PPT 是/否**：是 — slide 8 写出了 AMD Ryzen 9 8940HX, Zen4, x86-64 + AVX-512；benchmark protocol (CPU lock, drop_caches, warm-up, 20 reps, médiane)；"Référence P2 dev : 216 MLUPS"
- **Script 是/否**：是 — `soutenance_partie2_fr.md` §1 解释了换平台原因和 dev vs official 区别
- **Gaps**：没有准备 CPU lock 和 drop_caches 各自针对什么偏差的详细说明

## 建议回答（法语）

**Pourquoi changer de plateforme ?**

> Apple Silicon ne supporte pas AVX-512 — c'est une contrainte architecturale, pas un choix. Les optimisations de Partie 2 ciblent explicitement les registres zmm (512 bits) de Zen4. On aurait pu continuer sur macOS avec NEON, mais l'objectif de cette partie était précisément d'exploiter un ISA vectoriel plus large sur x86-64.

Apple Silicon 不支持 AVX-512——这是架构限制，不是选择。第二部分的优化明确针对 Zen4 的 zmm 寄存器（512 位）。我们可以继续在 macOS 上用 NEON，但这一部分的目标正是在 x86-64 上利用更宽的向量 ISA。

**À quoi sert chaque élément du protocole ?**

> Le CPU lock (fréquence fixée) élimine le bruit du DVFS — sans lui, le boost automatique fausse les comparaisons. Le `drop_caches` garantit que le warm-up ne lit pas depuis un cache chaud qui ne représente pas les conditions réelles. Le warm-up charge les données en cache pour que les 20 répétitions mesurent le régime permanent. La médiane sur 20 répétitions rejette les outliers dus aux interruptions OS.

CPU lock（固定频率）消除 DVFS 噪声——没有它，自动 boost 会扭曲比较。`drop_caches` 确保 warm-up 不从不代表真实条件的热缓存读取。warm-up 将数据加载到缓存，使 20 次重复测量稳定状态下的性能。20 次重复取中位数可以排除因 OS 中断产生的异常值。

**Comment prouvez-vous qu'AVX-512 est utilisé ?**

> On a vérifié à l'`objdump` que GCC génère des instructions `zmm` — notamment `vmovupd (%r10,%rax,1),%zmm23`, `vaddpd` et `vdivpd` sur registres zmm. La présence de ces instructions dans le code de la boucle interne confirme que le compilateur émet bien des opérations 512 bits. Le cpuinfo confirme que la machine supporte AVX-512F.

我们用 `objdump` 验证了 GCC 生成了 `zmm` 指令——包括 `vmovupd (%r10,%rax,1),%zmm23`、以及在 zmm 寄存器上的 `vaddpd` 和 `vdivpd`。这些指令出现在内层循环代码中，确认编译器确实生成了 512 位操作。cpuinfo 确认了该机器支持 AVX-512F。

**Pourquoi 216 MLUPS est-il "dev" ?**
**为什么 216 MLUPS 标为「开发数据」？**


> 216 MLUPS a été mesuré après opt18–19 (passage SoA), sans CPU lock ni protocole formel — c'est une mesure de développement pour calibrer l'effet de la restructuration des données. Elle n'est pas comparable aux résultats officiels. Le seul résultat officiel de Partie 2 est mesuré sous protocole complet.

216 MLUPS 是在 opt18–19（SoA 转换）之后测得的，未使用 CPU lock 或正式协议——这是用于评估数据重组效果的开发期测量，不能与正式结果比较。第二部分唯一的官方结果是在完整协议下测量的。

## 证据

- CPU info AMD Ryzen 9 8940HX, Zen4, AVX-512 : `工作记录/优化18.md` (à vérifier)
- objdump zmm evidence : `工作记录/优化22.md`
- Protocole benchmark (CPU lock, drop_caches, médiane) : `工作记录/优化22.md` ou fichier de protocole dédié (à vérifier)
- soutenance script §1 : `exports/soutenance_partie2_fr.md`

## Phrases à éviter

- ❌ "notre machine est plus performante que le Mac" — c'est non iso-plateforme ; les deux ont des architectures et ISA différents.
- ❌ "sans CPU lock les résultats sont faux" — ils sont bruités, pas faux ; dire "moins reproductibles".
- ❌ "216 MLUPS est notre point de départ officiel de Partie 2" — c'est une référence dev, pas un résultat officiel.
