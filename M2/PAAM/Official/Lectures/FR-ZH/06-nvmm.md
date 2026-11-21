# Mémoire persistante · 持久内存

[目录](README.md) · [教师英文讲义（26 页）](../../GitLab/cours/06-nvmm.pdf) · [本讲实验](../../GitLab/nvmm/Readme.md)

## Mémoire adressable et persistante · 可按字节寻址的持久内存

[原讲义第 1–5 页](../../GitLab/cours/06-nvmm.pdf#page=1)

**FR** La PMEM est une mémoire persistante adressable par le processeur par des instructions de chargement et de stockage. Elle associe un mode d'accès proche de la DRAM à la conservation des données après coupure. Le tableau présente des mesures pour DDR4, Optane DC et NVMe. Dans l'exemple, une lecture séquentielle prend 80 ns en DDR4, 160 ns sur Optane DC et 250 µs sur NVMe. Sous Linux, le support peut être exposé comme périphérique, puis formaté avec un système de fichiers prenant en charge l'accès direct DAX.

**中文** PMEM 是持久内存，CPU 可用 load/store 直接访问其字节，在断电后仍能保留已经持久化的数据。课件比较了 DDR4、Optane DC 和 NVMe。当时的顺序读示例分别为 80 ns、160 ns 与 250 µs。这些数值对应表中的设备与访问模式。在 Linux 中，可将 PMEM 暴露为设备，再用支持 DAX（直接访问）的文件系统格式化。

## Accès aux fichiers et projection en mémoire · 文件访问与内存映射

[原讲义第 6–12 页](../../GitLab/cours/06-nvmm.pdf#page=6)

**FR** Dans le schéma, le fichier ordinaire `fic2` est stocké sur disque. Avec `read`, le noyau fournit les octets à un tampon du processus. Avec `mmap`, un intervalle d'adresses virtuelles est associé au fichier. Pour un fichier classique, les pages accédées sont représentées dans le cache de pages en DRAM. Pour le fichier `fic1` sur PMEM avec DAX, la projection donne accès aux pages du support, sans recopier le contenu dans ce cache. La traduction virtuelle et les caches du processeur font toujours partie du chemin d'accès.

**中文** 图中的普通文件 `fic2` 在磁盘上。用 `read` 时，内核把文件字节交给进程缓冲区；用 `mmap` 时，进程中的一段虚拟地址与文件关联，普通文件的访问靠 DRAM 中的页缓存提供数据。对 DAX 上的 PMEM 文件 `fic1`，映射可以直接指向介质上的页面，免去把文件内容复制到页缓存。虚拟地址转换和 CPU 缓存仍然参与访问。

## Modifier un fichier projeté et le remapper · 修改映射文件与重启后恢复

[原讲义第 13–16 页](../../GitLab/cours/06-nvmm.pdf#page=13)

**FR** Le cours ouvre ou crée `fic1`, fixe sa longueur à 8 Kio avec `ftruncate`, puis le projette en lecture-écriture avec `mmap` en demandant `MAP_SHARED_VALIDATE | MAP_SYNC`. Il écrit ensuite la valeur 42 dans le premier octet. Après redémarrage, un nouveau mappage permet de relire les octets effectivement persistés. La suite précise les opérations nécessaires quand la récupération dépend de l'ordre et de l'achèvement des écritures.

**中文** 课件先打开或创建 `fic1`，用 `ftruncate` 将文件长度设为 8 KiB，再通过 `mmap` 和 `MAP_SHARED_VALIDATE | MAP_SYNC` 建立可读写的共享映射，最后把首字节写成 42。重启后重新映射文件，就能读取已经持久化的字节。恢复过程如果依赖多个写入的先后和完成状态，就要用后面讲的持久化操作。

```c
int fd = open("/mnt/pmem/fic1", O_RDWR | O_CREAT, 0700);
ftruncate(fd, 8 * 1024);
char *addr = mmap(NULL, 8 * 1024, PROT_READ | PROT_WRITE,
                  MAP_SHARED_VALIDATE | MAP_SYNC, fd, 0);
addr[0] = 42;
```

## Atomicité après panne · 崩溃原子性

[原讲义第 17–20 页](../../GitLab/cours/06-nvmm.pdf#page=17)

**FR** Le cours écrit `name`, puis place `committed` à vrai. Après une panne, un marqueur validé doit garantir que le nom entier est récupérable. Si la ligne du marqueur atteint la mémoire persistante avant les lignes du nom, on peut retrouver un état partiel. Une barrière d'ordre mémoire entre cœurs ne suffit pas à imposer cet ordre de persistance. Une bibliothèque telle que PMDK peut gérer ce protocole.

**中文** 课件先写 `name`，再把 `committed` 设为真。崩溃恢复时，如果提交标志为真，整个名字就必须可恢复。若标志所在缓存行早于名字所在缓存行进入持久域，就可能恢复出部分更新。约束核间可见顺序的内存屏障不足以建立这个持久化顺序，可以用 PMDK 之类的库实现协议。

## Écriture des lignes et ordre de persistance · 缓存行写回与持久化顺序

[原讲义第 21–22 页](../../GitLab/cours/06-nvmm.pdf#page=21)

**FR** Dans le modèle du cours, `pwb(addr)` demande l'écriture de la ligne contenant `addr` et `pfence()` impose l'ordre de propagation demandé. Demander l'écriture de toutes les lignes modifiées de `name`, placer la barrière, puis publier et écrire la ligne de `committed`. Le protocole établit ainsi l'implication de récupération `committed == true ⇒ name contient la valeur complète`. Pour une chaîne couvrant plusieurs lignes, un seul `pwb` sur le premier octet ne couvre pas toute l'écriture.

**中文** 在课件抽象模型中，`pwb(addr)` 请求写回给定地址所在的缓存行，`pfence()` 约束前后持久化动作的顺序。先请求写回 `name` 涉及的所有修改行，执行屏障，再改变并请求写回 `committed` 所在行。于是恢复时满足 `committed == true ⇒ name 为完整新值`。如果字符串跨了多条缓存行，只对首地址执行一次 `pwb` 不够。

```text
write(name) → pwb(lines modified by name) → pfence()
            → write(committed = true) → pwb(line containing committed)
```

## Attendre avant l'accusé de réception · 确认前等待持久化完成

[原讲义第 23–26 页](../../GitLab/cours/06-nvmm.pdf#page=23)

**FR** La barrière `pfence()` ordonne les écritures, mais la dernière peut encore être en attente lorsque le programme voudrait envoyer un accusé de réception. `psync()` attend que les écritures précédentes aient atteint le domaine de persistance. Le producteur publie ensuite le signal inter-thread `ok` par une synchronisation adéquate. L'exemple Intel utilise `clwb` pour écrire une ligne et `sfence` pour l'ordre et l'achèvement requis, selon les garanties du domaine de persistance de la machine. En C, le drapeau partagé doit aussi avoir une vraie synchronisation, par exemple un couple release/acquire.

**中文** `pfence()` 确立顺序，但程序准备发送确认时，最后一次写回可能还没完成。`psync()` 等待前面的写入到达持久域，生产者之后才用适当的同步发布线程间标志 `ok`。课件的 Intel 例子用 `clwb` 写回缓存行，用 `sfence` 提供对应的顺序和完成保证，实际语义取决于机器的持久域。C 中的共享标志也需要真实的线程同步，例如 release/acquire。

## Vérification rapide · 自检

- **FR** Quand peut-on acquitter la requête ? Une fois le marqueur durable, puis la disponibilité de cet état publiée au thread qui répond. **中文** 什么时候可以回应用户？先等提交标志持久化完成，再向回复线程发布这一事实。
- **FR** Que vérifie-t-on si le marqueur vaut encore faux au redémarrage ? Le protocole doit permettre d'ignorer, d'annuler ou de rejouer cette mise à jour partielle. **中文** 重启后标志仍为假怎么办？协议应允许忽略、撤销或重做这次可能只写了一部分的更新。
