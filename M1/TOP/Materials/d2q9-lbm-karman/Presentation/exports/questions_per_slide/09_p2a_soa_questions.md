# Slide 9 — P2-A : AoS → SoA (opt18–19)

## 可能问题

1. **[HIGH]** 为什么 AoS 对这类向量化不友好？关键在于哪种访问模式？
2. **[HIGH]** 你说"à k fixé, en j contiguous"——为什么是 j 方向连续，而不是其他方向？
3. **[HIGH]** SoA 之后反而先出现性能回退（-22%），这是为什么？
4. **[MEDIUM]** `72 octets` 这个数字是怎么来的？
5. **[MEDIUM]** 216 MLUPS 是什么配置下测的？是官方结果吗？
6. **[LOW]** 如果不做 SoA，后面的 AVX-512 还能工作吗？

## 已覆盖情况

- **PPT 是/否**：是 — slide 9 写出了 AoS→SoA, "à k fixé les cellules en j sont contiguës", 72 oct AoS cell size, régression initiale, préparation pour AVX-512
- **Script 是/否**：是 — `soutenance_partie2_fr.md` §P2-A 说明了 SoA 的动机、j 方向连续、以及初始回退
- **Gaps**：回退原因（访问方式未适配）需要能口头解释；216 MLUPS 的配置未在 PPT 上显示

## 建议回答（法语）

**Pourquoi AoS est-il mal adapté à la vectorisation ici ?**

> En AoS, la structure est `cell[i][j].f[k]` : pour accéder à la direction k=2 de toutes les cellules consécutives en j, on saute de 72 octets en 72 octets (la taille d'une cellule complète). SIMD charge un vecteur de valeurs contiguës en mémoire — avec AoS, on charge 9 valeurs de directions différentes pour une seule cellule, pas 8 valeurs de la même direction pour 8 cellules. Le gather résultant est inefficace.

在 AoS 布局中，结构是 `cell[i][j].f[k]`：要访问 j 方向所有相邻格点的 k=2 方向值，需要每次跳跃 72 字节（一个完整格点的大小）。SIMD 要加载内存中连续的一组值——在 AoS 下，加载的是一个格点的 9 个不同方向值，而不是 8 个格点的同一方向值。由此产生的 gather 操作效率很低。

**Pourquoi "à k fixé, j contigu" ?**

> En SoA, le layout est `cells[k][x*H + y]` — pour un k fixé, les indices `x*H + y` croissent de 1 quand y (= j) croît de 1. Donc les valeurs de la même direction k pour des cellules voisines en j sont bien consécutives en mémoire. C'est exactement ce que SIMD attend : 8 doubles côte à côte pour charger un registre zmm d'une seule instruction.

在 SoA 布局中，结构是 `cells[k][x*H + y]`——对于固定的 k，当 y（即 j）增大 1 时，索引 `x*H + y` 也增大 1。因此，j 方向相邻格点的同一方向 k 的值在内存中是连续的。这正是 SIMD 所需要的：8 个相邻的 double，可以用一条指令加载一个 zmm 寄存器。

**Pourquoi une régression de -22% au départ ?**

> Passer en SoA change l'organisation des données mais pas les patterns d'accès des boucles existantes. Les boucles étaient écrites pour AoS : elles accèdent toujours aux 9 directions d'une cellule ensemble, ce qui est maintenant non contigu en SoA. La régression vient du fait que le code n'a pas encore été adapté pour exploiter la nouvelle contiguïté. C'est opt20 (boucle k-outer) qui corrige cela.

切换到 SoA 改变了数据的组织方式，但没有改变现有循环的访问模式。循环是为 AoS 编写的：仍然同时访问一个格点的 9 个方向，而这在 SoA 中不再连续。回退是因为代码还没有适配新的连续性。opt20（k-outer 循环）才解决了这个问题。

**D'où vient 72 octets ?**

> Une cellule D2Q9 contient 9 directions × 1 double (8 octets) = 72 octets en AoS. C'est la taille d'une struct `cell_t` avec un tableau `double f[9]`.

D2Q9 的一个格点包含 9 个方向 × 1 个 double（8 字节）= 72 字节（AoS 格式）。这对应一个带有 `double f[9]` 数组的 `cell_t` 结构体大小。

**216 MLUPS — config et nature ?**

> 216 MLUPS est mesuré en développement après opt18–19 (AoS→SoA + premières adaptations), sur la configuration np=2, OMP=4 (à vérifier dans `优化19.md`), sans protocole officiel. Ce n'est pas un résultat final — c'est un jalon de la chaîne de développement.

216 MLUPS 是在 opt18–19（AoS→SoA + 初步适配）之后的开发期测量，配置为 np=2, OMP=4（待 `优化19.md` 确认），未使用正式协议。这不是最终结果——它是开发链上的一个里程碑。

## 证据

- SoA layout `cells[k][x*H+y]`, régression -22% : `工作记录/优化19.md`
- 72 octets cell AoS : dérivé de 9 × sizeof(double)
- Contiguïté en j à k fixé : `工作记录/优化19.md` + `工作记录/优化20.md`
- Script oral : `exports/soutenance_partie2_fr.md` §P2-A

## Phrases à éviter

- ❌ "SoA améliore les performances" — SoA seul dégrade d'abord ; le gain vient de SoA + boucle adaptée + restrict/ivdep.
- ❌ "sans SoA, AVX-512 est impossible" — on pourrait faire de l'AVX-512 avec AoS via gather intrinsics, mais c'est beaucoup moins efficace ; dire "SoA est la condition pour un AVX-512 efficace par auto-vectorisation".
