# Slide 11 — P2-C/D : Halo k-major + région OpenMP (opt23–26)

## 可能问题

1. **[HIGH]** SoA 之后，halo packing 为什么还要再改成 k-major？它改变了什么？
2. **[HIGH]** `MPI_Waitall` 里看到的是 rank 不平衡，你怎么区分它和网络延迟？
3. **[HIGH]** `832 → 905 MLUPS` 是官方数据还是开发数据？这个区别为什么重要？
4. **[HIGH]** opt25 里测试了哪些被拒绝的方案？它们为什么被放弃？
5. **[MEDIUM]** 为什么说 `diagnostic intra-nœud`？这对实际的多节点部署有什么局限？
6. **[MEDIUM]** 单一 OpenMP 区域减少的是什么成本？gain 为什么有限？
7. **[MEDIUM]** halo vertical 的 pack 为什么会在原来的 i-major 下产生大量 cache miss？具体间距是多少？
8. **[LOW]** 这一页的优化是否改变了数值结果或物理输出？

## 已覆盖情况

- **PPT 是/否**：是 — slide 11 提到了 k-major halo packing, MPI_Waitall 诊断, 单一 OMP 区域；写了"832 → 905 MLUPS (dev)"
- **Script 是/否**：是 — `soutenance_partie2_fr.md` §P2-C/D 三段分别覆盖 halo k-major、Waitall 诊断、OMP region
- **Gaps**：没有准备 intra-nœud 测试的局限性说明；905 MLUPS 的测试条件需要口头确认是 dev

## 建议回答（法语）

**Pourquoi changer le packing halo en k-major après SoA ?**
**SoA 之后为什么要将 halo packing 改为 k-major？**


> En SoA, les données sont organisées par direction k, puis par cellule. Le packing halo original copiait cellule par cellule, ce qui était contigu en AoS mais ne l'est plus en SoA. En passant au k-major, on copie d'abord toutes les valeurs d'une direction k pour les cellules halo, ce qui est maintenant contigu en mémoire. L'amélioration principale est visible sur l'unpack : les écritures dans le buffer halo sont séquentielles plutôt qu'éparpillées.

在 SoA 中，数据按方向 k 然后按格点组织。原来的 halo packing 是逐格点复制的，在 AoS 中是连续的，但在 SoA 中不再如此。改为 k-major 后，先复制 halo 格点的某一方向 k 的所有值，这在内存中现在是连续的。主要改善体现在 unpack 侧：写入 halo buffer 的操作变为顺序访问，而不是散乱的。

**Comment savez-vous que c'est un déséquilibre de ranks, pas de la latence réseau ?**
**你如何知道这是 rank 不平衡而非网络延迟？**


> Le test a été réalisé en intra-nœud (les deux rangs sur la même machine). Dans ces conditions, la latence réseau est quasi nulle — les communications passent par la mémoire partagée. Ce qu'on observe dans `MPI_Waitall`, c'est que l'un des rangs attend l'autre qui n'est pas encore prêt à recevoir. C'est un déséquilibre de charge ou de scheduling, pas de la bande passante réseau. Ce diagnostic ne se généralise pas à un vrai cluster multi-nœuds.

测试是在节点内进行的（两个 rank 在同一台机器上）。在这种情况下，网络延迟几乎为零——通信通过共享内存进行。在 `MPI_Waitall` 中观察到的是某个 rank 在等待另一个还没准备好接收的 rank，这是负载或调度不平衡，不是网络带宽问题。这个诊断不能推广到真正的多节点集群。

**832 → 905 MLUPS — dev ou officiel ?**

> C'est une mesure de développement, mesurée sans protocole officiel complet (sans CPU lock systématique, à vérifier dans `优化24.md`). On la cite pour montrer la progression de la chaîne, pas comme résultat final. Le seul résultat officiel est 2047 MLUPS mesuré sous protocole complet.

这是一个开发期测量，没有使用完整的正式协议（未系统地使用 CPU lock，待 `优化24.md` 确认）。引用它是为了展示链式进展，而非作为最终结果。唯一的官方结果是在完整协议下测得的 2047 MLUPS。

**Pourquoi dire "diagnostic intra-nœud" ?**
**为什么说「节点内诊断」？**


> Parce que le test a été fait avec np=2 sur la même machine. L'analyse de `MPI_Waitall` ne reflète que la dynamique intra-nœud — la communication passe par mémoire partagée, pas par réseau. Sur un vrai cluster, les patterns de Waitall seraient dominés par la bande passante et la latence réseau, ce qui rendrait ce diagnostic invalide.

因为测试是在同一台机器上用 np=2 进行的。`MPI_Waitall` 的分析只反映节点内的动态——通信通过共享内存而非网络进行。在真正的集群上，Waitall 的模式会被网络带宽和延迟主导，这会使该诊断失效。

**Une seule région OpenMP — pourquoi le gain est-il limité ?**
**单一 OpenMP 区域——为什么增益有限？**


> Le coût de création/destruction d'une équipe de threads OpenMP (`fork/join`) est de l'ordre de quelques microsecondes. Sur un timestep LBM avec 128 000 cellules, le calcul lui-même prend beaucoup plus de temps. La fusion des phases en une seule région réduit ce coût de fork/join, mais il était déjà petit par rapport au calcul — d'où un gain inférieur à 1%.

创建/销毁 OpenMP 线程组（`fork/join`）的成本大约是几微秒。对于包含 128 000 个格点的 LBM 时间步，计算本身要耗费更多时间。将各阶段合并到单一区域可以减少这个 fork/join 开销，但它相对于计算已经很小——因此增益不到 1%。

**opt25 — quels essais ont été rejetés et pourquoi ?**
**opt25——哪些方案被放弃了，为什么？**


> Deux essais ont été menés et rejetés. Premier essai : interleaver le pack en lançant `MPI_Isend` après chaque bloc de k — FOM −3%, le surcoût des appels non bloquants supplémentaires l'emporte. Deuxième essai : split collision, avancer la border collision avant `halo_start` — FOM −34%, car la région OMP supplémentaire déclenche un coût net de réveil/sommeil des workers. La conclusion est qu'affiner l'ordre de soumission des communications rapporterait peu ; opt26 résout le problème structurellement avec une région OMP unique.

测试了两个方案并放弃。第一：在每个 k 块之后交错发起 `MPI_Isend`——FOM −3%，额外非阻塞调用的开销超过了收益。第二：分离碰撞，将 border collision 提前到 `halo_start` 之前——FOM −34%，因为额外的 OMP 区域触发了线程唤醒/休眠的净成本。结论是进一步细化通信提交顺序收益有限；opt26 通过单一 OMP 区域从结构上解决了这个问题。

**Pourquoi l'ancien pack i-major causait-il des cache miss en SoA ?**
**为什么原来的 i-major pack 在 SoA 下会导致 cache miss？**


> En SoA, les 9 plans directionnels sont séparés de W×H×8 = 800×160×8 = 1 024 KB chacun. L'ancien pack en i-major rebondissait continuellement entre plans : pour chaque cellule i, il accédait aux 9 plans dans la boucle interne. Ces accès séparés de 1 MB dépassent largement la capacité du L2 (1 MiB/cœur), provoquant des cache misses répétés. Le pack k-major parcourt un seul plan à la fois (`memcpy` de W-2 doubles consécutifs), ce qui reste entièrement dans le L1/L2.

在 SoA 中，9 个方向平面之间相隔 W×H×8 = 800×160×8 = 1 024 KB。原来的 i-major pack 在内层循环中对每个格点 i 访问 9 个平面，每次跳跃 1 MB，远超 L2 容量（1 MiB/核），反复触发 cache miss。k-major pack 每次只遍历一个平面（连续 memcpy W-2 个 double），完全在 L1/L2 范围内。

## 证据

- k-major halo, 832→905 dev : `工作记录/优化24.md`
- MPI_Waitall diagnostic, rank imbalance, intra-nœud : `工作记录/优化25.md`
- Single OMP region, gain <1% : `工作记录/优化26.md`
- Script oral : `exports/soutenance_partie2_fr.md` §P2-C/D

## Phrases à éviter

- ❌ "on a amélioré les communications MPI de 832 à 905" — 905 est une mesure dev sans protocole ; et l'amélioration vient du halo, pas des communications elles-mêmes.
- ❌ "MPI_Waitall était le goulot d'étranglement" — c'était un déséquilibre identifié en intra-nœud ; pas de mesure cross-node pour confirmer.
- ❌ "la fusion OpenMP double les performances" — le gain est inférieur à 1% selon `优化26.md`.
