# Slide 2 — Contexte physique et FOM

## 可能问题

1. **[HIGH]** 为什么用 `MLUPS` 作为 figure of merit，而不是 wall-clock time 或 speedup？
2. **[HIGH]** `800 × 160` 和 `20 000` 个时间步是怎么定的？这对性能评估有什么影响？
3. **[HIGH]** 你说每一步有三相：special cells、collision、propagation + halo。哪一部分是热点，为什么？
4. **[MEDIUM]** 为什么这里选 `Re = 96`？它对 Kármán 涡街意味着什么？
5. **[MEDIUM]** 如果老师问"你优化的是数值方法本身还是实现层面"，你怎么区分？
6. **[LOW]** 这个 benchmark 规模够大吗？能代表真实 HPC 场景吗？

## 已覆盖情况

- **PPT 是/否**：是 — slide 2 列出了 Re=96, W=800, H=160, 20 000 steps, 三阶段结构, MLUPS 公式
- **Script 是/否**：否 — Part 1 脚本不在提供文件中
- **Gaps**：MLUPS 的"为什么选这个 FOM"没有口头阐述；热点识别没有解释（collision 通常最重）

## 建议回答（法语）

**Q1 — Pourquoi MLUPS ?**

> MLUPS normalise le débit par la taille du domaine et le nombre de pas : c'est indépendant du nombre de processus et de la fréquence machine. Contrairement au speedup, il ne dépend pas d'une référence arbitraire, et contrairement au temps mur, il est comparable entre configurations. C'est la métrique standard pour les codes LBM.

MLUPS 将吞吐量按域大小和步数归一化：它与进程数和机器频率无关。不同于 speedup 依赖任意基准，也不同于 wall-clock time 跨配置不可比，MLUPS 是 LBM 代码的标准指标。

**Q2 — Pourquoi 800×160 et 20 000 pas ?**

> Ces dimensions sont issues du cas de référence Kármán à Re=96 : le rapport 5:1 permet le développement des tourbillons. 20 000 pas donnent un régime établi et un temps de mesure statistiquement stable. Le domaine de 128 000 cellules reste volontairement modeste pour que les runs de benchmark tiennent en quelques secondes — ce qui permet de répéter 20 fois sous protocole officiel.

这些参数来自 Re=96 Kármán 参考案例：5:1 的长宽比可以让涡街充分发展。20 000 步可以达到稳定状态并获得统计稳定的测量时间。128 000 个格点的域大小有意保持较小，使 benchmark 单次运行只需几秒——从而可以在正式协议下重复 20 次。

**Q3 — Quel est le hotspot ?**

> La phase collision est généralement dominante : elle implique 9 lectures, un calcul de densité et de vitesse, puis 9 écritures par cellule, avec des divisions flottantes. La propagation est plus légère en calcul mais plus lourde en accès mémoire non contigus — c'est pourquoi le layout SoA de la Partie 2 cible précisément cette phase.

碰撞阶段通常是计算主导：每个格点需要 9 次读取、密度/速度计算以及 9 次写入，其中包含浮点除法。传播阶段计算量较轻，但内存访问不连续的问题更突出——这正是第二部分 SoA 布局所针对的。

**Q4 — Re = 96**

> Re=96 est dans la plage d'instabilité de Bénard-Kármán : suffisamment élevé pour que les tourbillons alternatifs se détachent de l'obstacle, suffisamment bas pour que la simulation reste stable sans schéma de stabilisation. C'est un cas de validation classique avec des fréquences de détachement documentées.

Re=96 处于 Bénard-Kármán 不稳定区间：足够高使交替涡旋从障碍物处分离，又足够低使仿真无需稳定化方案就能保持稳定。这是一个有文献记录的经典验证案例。

**Q5 — Méthode numérique ou implémentation ?**

> On n'a modifié ni les équations BGK ni le schéma LBM — Re, les poids, et les vitesses discrètes restent identiques. Toutes les optimisations portent sur la façon dont le code traverse la mémoire et distribue le calcul. Le modèle numérique est inchangé, et les résultats physiques sont identiques avant et après chaque optimisation.

我们既没有修改 BGK 方程，也没有修改 LBM 格式——Re、权重系数和离散速度保持不变。所有优化都针对代码遍历内存和分配计算的方式。数值模型本身不变，每次优化前后的物理结果完全相同。

## 证据

- MLUPS 公式定义：`工作记录/优化02.md`（修复前的错误公式 + 修复后的单一公式）
- 热点分析：`工作记录/优化10.md`（collision/propagation 分析）
- 问题规模：slide 2 SVG `svg_output/02_contexte.svg`

## Phrases à éviter

- ❌ "le hotspot c'est la propagation" — sans mesure profilée, l'affirmation est trop directe ; dire "la collision est souvent dominante en calcul, la propagation en accès mémoire".
- ❌ "MLUPS mesure l'efficacité" — MLUPS mesure le débit, pas l'efficacité par rapport à un optimum théorique.
