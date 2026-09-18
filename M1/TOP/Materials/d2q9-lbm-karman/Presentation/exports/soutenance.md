# Soutenance de projet — Partie 2

## Part 2

### Transition — New platform and unified protocol / 平台切换与统一测量协议

Maintenant, on passe à la deuxième partie du travail.  
现在我们进入工作的第二部分。  

Jusqu'ici, la première partie se passait surtout sur macOS. Ici, on passe sur un AMD Ryzen 9, donc sur une plateforme x86-64 avec AVX-512. Cela nous permet de mesurer le programme sur du matériel AMD et de mieux l'adapter à d'autres architectures, surtout pour les optimisations mémoire et vectorisation côté x86.  
到这里为止，第一部分主要还是在 macOS 上进行的。这里我们切换到 AMD Ryzen 9，也就是一个带 AVX-512 的 x86-64 平台。这样做既让我们能够在 AMD 硬件上测量程序性能，也让程序更容易适配到更多架构，尤其是这一部分里和 x86 相关的内存与向量化优化。  

Il faut aussi garder une distinction. Certains chiffres viennent de mesures prises pendant la phase de développement, souvent quand on analysait les hotspots du programme. Ils servent à comprendre ce que fait une optimisation. Les chiffres finaux, eux, viennent du protocole de benchmark officiel.  
还要记住一个区分：有些数字来自开发阶段的测量，通常是在分析程序热点时得到的，它们是用来帮助理解某个优化做了什么；而最终数字则来自正式 benchmark 协议。  

### P2-A — AoS to SoA / 从 AoS 到 SoA

Ici, on passe d'abord à l'organisation des données.  
这里第一个重要变化，就是数据组织方式。  

Au départ, les données sont en AoS. C'est pratique à écrire, mais ce n'est pas très bon pour vectoriser. Pour une direction donnée, les accès aux cellules voisines n'ont pas une bonne localité spatiale.  
一开始，数据是 AoS 布局。这样写代码比较自然，但并不适合向量化。对于某一个固定方向，相邻格点的访问没有很好的空间局部性。

Donc on passe en SoA. Avec SoA, à k fixé, les cellules voisines en j deviennent contiguës en mémoire. Concrètement, ça facilite beaucoup le chargement de plusieurs valeurs en même temps avec SIMD.  
所以我们改成 SoA。改成 SoA 之后，在 k 固定时，j 方向上的相邻格点在内存中变成连续。具体来说，这会让我们更容易一次性用 SIMD 加载多个值。  

Ce qu'on observe, c'est que SoA ne donne pas forcément un gain immédiat. Chez nous, il y a même une régression au début, parce que les accès ne sont pas encore adaptés au nouveau layout.  
我们观察到的是，SoA 不一定会立刻带来性能提升。在我们的实验里，一开始甚至出现了回退，因为访问方式还没有适配新的布局。  

### P2-B — AVX-512 vectorization / AVX-512 向量化

Ensuite, on arrive à l'étape AVX-512.  
接下来就是 AVX-512 这一步。  

D'abord, on veut vérifier que le compilateur génère vraiment du code AVX-512 utile ou pas.  
这里我们首先想验证的是，编译器到底会不会真正生成有用的 AVX-512 代码。  

Le blocage venait surtout de l'analyse d'alias. Si le compilateur soupçonne un recouvrement entre pointeurs, il vectorise peu.  
真正的阻碍主要来自 alias analysis。如果编译器怀疑指针之间可能重叠，它就不太会做向量化。  

Dans le code, nous n'avons pas écrit d'intrinsics AVX-512 à la main. Nous avons gardé du C++ classique, avec `__restrict__` et `#pragma GCC ivdep`, puis nous avons vérifié à l'objdump que GCC générait bien des instructions zmm.  
在代码里，我们没有手写 AVX-512 intrinsic。我们保留了比较经典的 C++ 写法，用 `__restrict__` 和 `#pragma GCC ivdep` 去引导编译器，然后再用 objdump 验证 GCC 确实生成了 zmm 指令。  

À partir de là, on voit bien des registres zmm dans l'assembleur. Donc AVX-512 est réellement utilisé. Dans la chaîne de développement, cette étape monte à 832 MLUPS. Donc, sur cette partie, ce qui compte, c'est l'ensemble : le layout mémoire, la boucle, et le compilateur.  
到这里之后，我们可以在汇编里看到 zmm 寄存器，说明 AVX-512 的确被用上了。在这条开发链里，这一步达到了 832 MLUPS。这里最重要的信息是，收益不是来自某一个关键词，而是来自内存布局、循环结构和编译器三者的配合。  

### P2-C and P2-D — Halo packing and unified OpenMP region / Halo 打包与统一 OpenMP 区域

Après ça, on a travaillé sur des optimisations moins spectaculaires, mais utiles.  
在这之后，我们又做了一些没有那么惊艳、但仍然有价值的优化。  

Pour le halo, on passe à un packing en k-major. C'est plus cohérent avec la SoA, et ce qu'on observe surtout, c'est une amélioration du comportement mémoire, surtout sur l'unpack.  
对于 halo，我们把 packing 改成了 k-major。这样做更符合 SoA 的结构，而我们最主要观察到的，是内存访问行为的改善，尤其是在 unpack 这一侧。  

Sur notre test intra-nœud, on a aussi regardé `MPI_Waitall`. En pratique, ce qu'on voit surtout, c'est un déséquilibre d'arrivée entre ranks. Certains arrivent plus tôt, puis attendent les autres.  
在我们的节点内测试里，我们还分析了 `MPI_Waitall`。实际更明显的问题，是 ranks 到达时间的不平衡。有些 rank 会更早到达，然后等待其他 rank。  

Enfin, on regroupe plusieurs phases d'un même timestep dans une seule région OpenMP. Le gain n'est pas énorme, mais le code devient plus propre, avec moins de création répétée d'équipes de threads.  
最后，我们把同一个 timestep 里的几个阶段放进同一个 OpenMP 区域。这样收益虽然不大，但代码结构更清楚，也减少了反复创建线程团队的成本。  

### Final results / 最终结果

Pour les résultats finaux, on ne garde que le protocole officiel.  
到了最终结果，我们只看正式协议下的 benchmark。  

Le meilleur résultat mesuré est 2047 MLUPS avec `np=1` et `OMP=16`.  
测得的最佳绝对结果是 `np=1`、`OMP=16` 下的 2047 MLUPS。  

Le meilleur résultat multi-processus est 1071 MLUPS avec `np=2` et `OMP=4`.  
最佳多进程结果是 `np=2`、`OMP=4` 下的 1071 MLUPS。  

Ces résultats sont comparables entre eux, parce qu'ils viennent de la même machine et du même protocole. Pour la comparaison avec la partie macOS, il faut rester prudent : c'est un gain global indicatif, non iso-plateforme.  
这些结果之所以可以直接比较，是因为它们来自同一台机器、同一套协议。但如果和 macOS 部分相比，就必须保持谨慎：那只是一个整体上的指示性收益，而不是严格的同平台比较。  

### Conclusion / 结论

Pour conclure cette partie, il y a une idée simple.  
最后总结这一部分，有一个很简单的想法。  

On réorganise d'abord les données avec SoA. Ensuite, on aide le compilateur avec `__restrict__` et `ivdep`. Puis on réduit ce qui reste côté halo et OpenMP.  
我们先用 SoA 重组数据，然后用 `__restrict__` 和 `ivdep` 帮助编译器，最后再去清理 halo 和 OpenMP 相关的剩余成本。  

Merci.  
谢谢。  
