# Slide 6 — P1-C : Localité mémoire + OpenMP (opt09–13)

## 可能问题

1. **[HIGH]** 为什么 `Pull` 比 `Push` 更适合 OpenMP 并行？从写冲突角度解释。
2. **[HIGH]** 你说 stride-1 vs 180 cache lines，"180 cache lines"这个说法怎么来的？
3. **[HIGH]** 这一步的收益主要来自 loop inversion 还是来自 Pull 模式还是 OpenMP？论文里有分项数据吗？
4. **[MEDIUM]** 为什么这一页展示 `np=1, OMP=4`？
5. **[MEDIUM]** OpenMP 放在 i-loop（列）上，为什么不放在 j-loop（行）上？
6. **[LOW]** 这个优化对数值结果有没有影响？

## 已覆盖情况

- **PPT 是/否**：是 — slide 6 写出了 Push→Pull, loop inversion (j inner), stride-1, 194 MLUPS, OpenMP schedule(static)
- **Script 是/否**：否 — Part 1 脚本不在提供文件中
- **Gaps**：没有准备 Push 写冲突的简短证明；"180 cache lines"需要能口头计算

## 建议回答（法语）

**Pourquoi Pull est-il thread-safe, mais pas Push ?**

> En mode Push, chaque cellule source écrit vers des cellules destination selon les 9 directions — deux threads peuvent écrire simultanément dans la même cellule destination si leurs directions se recoupent. C'est une course d'écriture. En mode Pull, chaque cellule destination lit depuis ses 9 voisins — chaque cellule est écrite par un seul thread. Il n'y a pas de conflit, et on peut paralléliser trivialement avec `#pragma omp parallel for`.

在 Push 模式下，每个源格点按 9 个方向写入目标格点——如果两个线程的方向重叠，它们可能同时写入同一个目标格点，这是写冲突。在 Pull 模式下，每个目标格点从其 9 个邻居读取——每个格点只由一个线程写入，不存在冲突，可以用 `#pragma omp parallel for` 直接并行化。

**D'où vient le "stride élevé" en mode AoS avec boucle j inner ?**

> En layout AoS, une cellule occupe 9 doubles = 72 octets. Si la boucle itère sur j (ligne), les cellules successives sont à 72 octets d'écart. Une cache line fait 64 octets — donc une cellule chevauche déjà deux lignes, et les cellules consécutives en j ne sont pas dans la même ligne de cache. En comparaison, avec la boucle i outer et j inner dans un layout colonne-major, on peut atteindre la contiguïté. À vérifier : le PPT cite "8 octets" pour le stride-1 après optimisation, ce qui correspond à un double contigu.

在 AoS 布局下，一个格点占 9 个 double = 72 字节。如果循环沿 j 方向（行）迭代，相邻格点间距 72 字节。一条 cache line 只有 64 字节——一个格点就已经横跨两条 cache line，j 方向上相邻的格点不在同一条 cache line 里。相比之下，在列主序布局且 j 在内层的情况下才能接近连续访问。待确认：PPT 引用"8 字节"作为优化后的 stride-1，对应一个连续的 double。

**Quel est le contributeur principal — Pull, loop inversion, ou OpenMP ?**

> La thèse donne des chiffres pour opt09 et opt10 séparément. opt09 (loop inversion, stride-1) : np=1 +10%, np=2 +26%. opt10 (Push→Pull) : np=1 +14%, np=4 +51% — le gain Pull est particulièrement visible sur multi-rank car Pull élimine les conflits d'écriture inter-threads. OpenMP (opt11–13) apporte ensuite la parallélisation réelle. Le gain total de la chaîne P1-C est +220% par rapport à la référence opt03 (np=1, OMP=4 : 194 MLUPS). Les trois sont cumulatifs et non substituables.

论文给出了 opt09 和 opt10 的分项数据。opt09（循环反转，stride-1）：np=1 +10%，np=2 +26%。opt10（Push→Pull）：np=1 +14%，np=4 +51%——Pull 在多 rank 下收益更明显，因为它消除了线程间写冲突。OpenMP（opt11–13）随后带来真正的并行化。P1-C 整体链增益相对于 opt03 参考值为 +220%（np=1, OMP=4：194 MLUPS）。三者是累积且不可替代的。

**Pourquoi OMP sur la boucle i (colonnes), pas j (lignes) ?**

> La décomposition MPI est déjà en colonnes (chaque rang traite un sous-ensemble de colonnes). Paralléliser en i avec OpenMP est cohérent avec ce découpage : chaque thread traite un bloc de colonnes indépendant, sans chevauchement avec les autres threads ni avec les halos MPI.

MPI 分解已经按列进行（每个 rank 处理列的子集）。将 OpenMP 放在 i 维度（列）上与这种划分一致：每个线程处理独立的列块，与其他线程和 MPI halo 没有重叠。

**L'optimisation change-t-elle les résultats numériques ?**

> Non. Pull est mathématiquement équivalent à Push — les deux implémentent la même règle de propagation LBM. La réorganisation de boucle ne modifie pas les valeurs calculées, seulement l'ordre des accès mémoire. On a vérifié que les champs de vitesse et densité sont identiques avant et après.

不影响。Pull 在数学上等价于 Push——两者实现相同的 LBM 传播规则。循环重排不改变计算结果，只改变内存访问顺序。我们验证了优化前后速度场和密度场完全相同。

## 证据

- Pull vs Push, race-free proof : `工作记录/优化10.md`
- Loop inversion (j inner, stride-1) : `工作记录/优化09.md`
- `#pragma omp parallel for schedule(static)` sur boucle i (colonnes) : `工作记录/优化11.md`, `工作记录/优化13.md`
- 194 MLUPS (np=1, OMP=4) : slide 6, `工作记录/优化13.md`

## Phrases à éviter

- ❌ "Push génère toujours des race conditions" — c'est vrai pour une parallélisation naïve, mais on pourrait utiliser des atomics ou un double buffer ; dire "Push nécessite une protection explicite que Pull rend inutile".
- ❌ "loop inversion donne un stride-1 absolu" — c'est vrai après le passage SoA en Partie 2 ; en AoS, la localité est améliorée mais pas parfaite.
- ❌ "194 MLUPS c'est le résultat final de Partie 1" — c'est un jalon de développement ; le résultat final de la plateforme macOS n'est pas isolé comme résultat officiel.
