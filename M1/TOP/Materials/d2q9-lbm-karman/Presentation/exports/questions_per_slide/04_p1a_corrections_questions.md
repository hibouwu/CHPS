# Slide 4 — P1-A : Corrections de validité (opt01–03)

## 可能问题

1. **[HIGH]** 你是怎么定位 `nanosleep` 的？它在代码里是怎么隐藏的？
2. **[HIGH]** 5.5 小时这个数字是怎么算出来的？
3. **[HIGH]** `MLUPS` 公式原来为什么会按 rank 数被高估？错误口径会误导哪些结论？
4. **[HIGH]** 这些修复算不算优化？为什么放在性能答辩里讲？
5. **[MEDIUM]** `MPI sizes` 不一致具体会带来什么风险：错误结果、死锁，还是只是性能问题？
6. **[MEDIUM]** 60 MLUPS 这个参考值是在什么配置下测得的？

## 已覆盖情况

- **PPT 是/否**：是 — slide 4 列出三个 opt，说明了每个 bug 的影响和来源
- **Script 是/否**：否 — soutenance.md 从 Part 2 开始，Part 1 脚本未提供
- **Gaps**：没有口头准备 nanosleep 的定位方法（hex decode → dlsym → inline asm）；5.5h 计算没有说明过程

## 建议回答（法语）

**Comment avez-vous localisé le nanosleep ?**

> Le `nanosleep` était encodé en hexadécimal dans un template CMake, appelé via `dlsym` avec un symbole forgé dynamiquement, lui-même injecté par de l'inline assembly. Ce n'est pas un appel direct dans le code source. On l'a trouvé en combinant `strace` sur une exécution courte et une lecture du binaire compilé — la signature de l'appel système `nanosleep` était visible dans la trace. Les détails complets sont dans le journal `优化01.md`.

`nanosleep` 被十六进制编码在一个 CMake 模板里，通过 `dlsym` 以动态伪造的符号调用，该符号本身由内联汇编注入。这不是源码里的直接调用。我们通过对一次短时运行做 `strace`，再结合读取编译后的二进制文件，找到了它——`nanosleep` 系统调用的签名在 trace 中可见。完整细节见 `优化01.md`。

**Comment calculez-vous 5,5 heures ?**

> Chaque `halo_exchange` appelle `nanosleep(1s)`. Avec np=2, il y a deux échanges par timestep (gauche et droite). Sur 20 000 pas : 20 000 × 2 × 1 s = 40 000 s ≈ 11 h par rank. À vérifier : le journal `优化01.md` précise le calcul exact ; le chiffre cité dans le PPT est 5,5 h.

每次 `halo_exchange` 都会调用 `nanosleep(1s)`。以 np=2 为例，每个时间步有两次交换（左和右）。20 000 步下：20 000 × 2 × 1 s = 40 000 s ≈ 11 小时每个 rank。待确认：`优化01.md` 中有精确计算；PPT 中引用的数字是 5.5 小时。

**Pourquoi la formule MLUPS surestimait-elle par np ?**

> La formule multipliait W×H×steps par `comm_size` (le nombre de rangs MPI). Avec np=2, le résultat était donc doublé. En réalité, chaque rang traite une fraction du domaine — la somme est bien W×H, pas W×H×np. Cela faisait croire que multi-rank était plus rapide qu'il n'était réellement.

原公式把 W×H×steps 乘以了 `comm_size`（MPI 进程数）。np=2 时结果因此被翻倍。实际上每个 rank 只处理域的一部分——总和仍是 W×H，而不是 W×H×np。这让多 rank 的性能看起来比实际更高。

**Ces corrections sont-elles des optimisations ?**

> Ce sont des corrections de validité, pas des optimisations de performance au sens strict. Mais sans elles, toutes les mesures suivantes sont non comparables. On les inclut dans la soutenance parce qu'elles sont une précondition à tout résultat fiable, et parce qu'elles illustrent un problème réel de reproductibilité dans les benchmarks HPC.

这些是有效性修正，不是严格意义上的性能优化。但没有它们，后续所有测量都无法相互比较。我们把它们纳入答辩，是因为它们是所有可靠结果的前提条件，同时也说明了 HPC benchmark 中真实存在的可重现性问题。

**Risque de l'incohérence MPI sizes (opt03) ?**

> Un `MPI_Recv` avec un count inférieur au count envoyé peut déclencher un `MPI_ERR_TRUNCATE` sur les implémentations strictes, ou silencieusement corrompre les données de halo sur les implémentations permissives. Dans notre cas, le comportement était indéfini et dépendant de l'implémentation MPI.

`MPI_Recv` 的 count 小于发送端时，在严格实现上会触发 `MPI_ERR_TRUNCATE`，在宽松实现上则会悄无声息地损坏 halo 数据。在我们的情况中，行为是未定义的，取决于具体的 MPI 实现。

## 证据

- nanosleep 完整技术细节：`工作记录/优化01.md`
- MLUPS 公式 comm_size bug：`工作记录/优化02.md`
- MPI sizes 不一致：`工作记录/优化03.md`
- 参考值 60 MLUPS (np=1, OMP=1)：slide 4 底部 bar

## Phrases à éviter

- ❌ "le nanosleep était intentionnellement caché pour nous piéger" — on ne peut pas affirmer l'intention ; dire "encodé de manière obfusquée".
- ❌ "ça nous a coûté 5,5 heures de calcul" — préciser que c'est par run de 20 000 pas en mode Linux, et que macOS échouait silencieusement.
- ❌ "opt03 pouvait causer un deadlock" — sauf si le journal le confirme explicitement ; dire "comportement indéfini / truncation possible".
