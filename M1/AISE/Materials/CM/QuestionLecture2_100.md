
# 100 Questions de révision - Lecture 2 : Système de Fichiers et I/O / 100 道复习题 - 第二讲：文件系统与 I/O

## I. Arborescence et Répertoires / 目录树与主要目录 (1-15)

1. **Quel est le point de départ de toute l'arborescence Unix ? / Unix 目录树的起点是什么？**
    * La racine `/` (The root). (根目录 `/`。)
2. **Que contient le répertoire `/bin` ? / `/bin` 目录包含什么？**
    * Les binaires de base essentiels (ex: `ls`, `cp`, `mv`). (基础二进制命令。)
3. **Quelle est la différence entre `/bin` et `/sbin` ? / `/bin` 和 `/sbin` 有什么区别？**
    * `/sbin` contient les binaires destinés au superutilisateur (administration), `/bin` pour tous. (`/sbin` 包含面向超级用户的二进制文件，`/bin` 面向所有用户。)
4. **Que contient `/boot` ? / `/boot` 包含什么？**
    * Les fichiers de démarrage (noyau, chargeurs comme GRUB). (启动文件，如内核、引导程序。)
5. **À quoi sert `/dev` ? / `/dev` 有什么用？**
    * Contient les fichiers représentant les périphériques (Device files). (包含代表设备的特殊文件。)
6. **Où se trouvent les fichiers de configuration du système (ex: `passwd`) ? / 系统配置文件（如 `passwd`）在哪里？**
    * Dans `/etc`.
7. **Que contient `/home` ? / `/home` 包含什么？**
    * Les répertoires personnels des utilisateurs. (用户的家目录。)
8. **À quoi sert `/lib` ? / `/lib` 有什么用？**
    * Contient les bibliothèques partagées essentielles (ex: `libc`). (包含基础共享库。)
9. **Quelle est la différence entre `/media` et `/mnt` ? / `/media` 和 `/mnt` 有什么区别？**
    * `/media` pour les montages automatiques/amovibles (USB), `/mnt` pour les montages temporaires manuels. (`/media` 用于自动/可移动挂载，`/mnt` 用于手动临时挂载。)
10. **Où installe-t-on généralement des logiciels additionnels optionnels ? / 通常在哪里安装可选的附加软件？**
    * Dans `/opt`.
11. **Qu'est-ce que `/proc` ? / 什么是 `/proc`？**
    * Un système de fichiers virtuel décrivant les processus et l'état du système. (描述进程和系统状态的虚拟文件系统。)
12. **Quel est le répertoire personnel du superutilisateur (root) ? / 超级用户 (root) 的家目录在哪里？**
    * `/root` (et non `/home/root`).
13. **Que contient `/tmp` ? / `/tmp` 包含什么？**
    * Des fichiers temporaires (souvent effacés au redémarrage). (临时文件。)
14. **À quoi sert `/usr` ? / `/usr` 有什么用？**
    * Contient les applications et bibliothèques utilisateurs (User System Resources). (包含用户级应用程序和库。)
15. **Que contient `/usr/local/bin` par rapport à `/usr/bin` ? / `/usr/local/bin` 与 `/usr/bin` 有什么不同？**
    * `/usr/local/bin` est pour les programmes installés manuellement (depuis les sources), `/usr/bin` pour ceux gérés par les paquets. (`/usr/local/bin` 用于手动安装的程序，`/usr/bin` 用于包管理器管理的程序。)

## II. Environnement et Bibliothèques / 环境与库 (16-25)

1. **À quoi sert la variable d'environnement `PATH` ? / 环境变量 `PATH` 有什么用？**
    * Elle liste les répertoires où le shell cherche les commandes exécutables. (它列出了 Shell 搜索可执行命令的目录。)
2. **Quelle variable indique où chercher les bibliothèques dynamiques ? / 哪个变量指示在哪里搜索动态库？**
    * `LD_LIBRARY_PATH` (ou `LIBRARY_PATH` pour la compilation).
3. **Quelle variable est utilisée pour les en-têtes C ? / 哪个变量用于 C 头文件？**
    * `C_INCLUDE_PATH`.
4. **Quelle commande affiche toutes les variables d'environnement ? / 哪个命令显示所有环境变量？**
    * `env`.
5. **Que fait `which ls` ? / `which ls` 做什么？**
    * Affiche le chemin complet de l'exécutable `ls` trouvé dans le `PATH`. (显示在 `PATH` 中找到的可执行文件 `ls` 的完整路径。)
6. **À quoi sert la commande `ldd` ? / 命令 `ldd` 有什么用？**
    * Lister les bibliothèques partagées (.so) nécessaires à un binaire. (列出二进制文件所需的共享库。)
7. **Que signifie "vdso" dans la sortie de `ldd` ? / `ldd` 输出中的 "vdso" 是什么意思？**
    * Virtual Dynamic Shared Object (interface noyau virtuelle). (虚拟动态共享对象。)
8. **Si un programme ne trouve pas sa bibliothèque, quelle variable faut-il vérifier ? / 如果程序找不到库，应该检查哪个变量？**
    * `LD_LIBRARY_PATH`.
9. **Où sont installées les sources manuellement ? / 手动安装的源代码放在哪里？**
    * `/usr/local/src`.
10. **Où sont les en-têtes (headers) installés par le système ? / 系统安装的头文件在哪里？**
    * `/usr/include`.

## III. Stockage et Montage / 存储与挂载 (26-40)

1. **Qu'est-ce qu'un point de montage ? / 什么是挂载点？**
    * Un répertoire où est attaché un système de fichiers. (附加文件系统的目录。)
2. **Quelle commande affiche la topologie des disques ? / 哪个命令显示磁盘拓扑结构？**
    * `lsblk`.
3. **Dans `lsblk`, que signifie "part" ? / 在 `lsblk` 中，"part" 是什么意思？**
    * Partition. (分区。)
4. **Dans `lsblk`, que signifie "lvm" ? / 在 `lsblk` 中，"lvm" 是什么意思？**
    * Logical Volume Manager (volume logique). (逻辑卷管理器。)
5. **Qu'est-ce que le répertoire `/boot/efi` ? / `/boot/efi` 目录是什么？**
    * La partition système EFI (pour le démarrage UEFI). (EFI 系统分区。)
6. **Qu'est-ce que le "swap" ? / 什么是 "swap"（交换空间）？**
    * Espace disque utilisé comme extension de la mémoire RAM (mémoire virtuelle). (用作 RAM 扩展/虚拟内存的磁盘空间。)
7. **Quelle est la commande pour monter une partition manuellement ? / 手动挂载分区的命令是什么？**
    * `sudo mount -t <type> <device> <mount_point>`.
8. **Comment démonter un système de fichiers ? / 如何卸载文件系统？**
    * `sudo umount <mount_point>`.
9. **Quel fichier configure les montages persistants (au démarrage) ? / 哪个文件配置持久挂载（启动时）？**
    * `/etc/fstab`.
10. **Dans `/etc/fstab`, que signifie la 4ème colonne (ex: `defaults`) ? / 在 `/etc/fstab` 中，第 4 列（如 `defaults`）代表什么？**
    * Les options de montage. (挂载选项。)
11. **Dans `/etc/fstab`, que signifie la dernière colonne ? / 在 `/etc/fstab` 中，最后一列代表什么？**
    * L'ordre de vérification par `fsck` (0 = pas de vérification). (`fsck` 的检查顺序。)
12. **Peut-on monter un fichier ISO ? / 可以挂载 ISO 文件吗？**
    * Oui (loopback mount). (可以。)
13. **Qu'est-ce que UUID dans `/etc/fstab` ? / `/etc/fstab` 中的 UUID 是什么？**
    * Universally Unique Identifier, identifie un système de fichiers de manière unique. (通用唯一标识符。)
14. **Quelle commande permet de voir l'espace disque utilisé ? / 哪个命令用于查看已用磁盘空间？**
    * `df -h`.
15. **Qu'est-ce que `nvme0n1` ? / `nvme0n1` 是什么？**
    * Un disque SSD NVMe. (NVMe 固态硬盘。)

## IV. Commandes de Base / 基本命令 (41-50)

1. **Que fait `touch file` si `file` existe déjà ? / 如果 `file` 已存在，`touch file` 做什么？**
    * Met à jour ses horodatages (accès/modification). (更新其时间戳。)
2. **Quelle est la différence entre `cat` et `tac` ? / `cat` 和 `tac` 有什么区别？**
    * `tac` affiche les lignes dans l'ordre inverse (de la dernière à la première). (`tac`以此相反的顺序显示行。)
3. **Que fait `rm -r` ? / `rm -r` 做什么？**
    * Supprime un répertoire et son contenu récursivement. (递归删除目录及其内容。)
4. **Que fait `rmdir` ? / `rmdir` 做什么？**
    * Supprime un répertoire **vide** uniquement. (仅删除**空**目录。)
5. **Quelle commande donne des métadonnées détaillées (inode, dates) sur un fichier ? / 哪个命令提供文件的详细元数据（inode，日期）？**
    * `stat`.
6. **Comment concaténer deux fichiers `f1` et `f2` dans `f3` ? / 如何将文件 `f1` 和 `f2` 串联到 `f3`？**
    * `cat f1 f2 > f3`.
7. **Comment créer un répertoire et ses parents s'ils manquent ? / 如何创建目录及其缺失的父目录？**
    * `mkdir -p`.
8. **Quelle commande change le répertoire courant ? / 哪个命令更改当前目录？**
    * `cd`.
9. **Comment lister les fichiers cachés ? / 如何列出隐藏文件？**
    * `ls -a`.
10. **Comment afficher le contenu d'un répertoire avec les détails (permissions, taille) ? / 如何显示目录内容的详细信息（权限、大小）？**
    * `ls -l`.

## V. Utilisateurs et Droits / 用户与权限 (51-70)

1. **Par quoi est identifié un utilisateur unique ? / 用户由什么唯一标识？**
    * UID (User Identifier).
2. **Quel est l'UID habituel du superutilisateur (root) ? / 超级用户 (root) 的通常 UID 是多少？**
    * 0.
3. **Par quoi est identifié un groupe ? / 用户组由什么唯一标识？**
    * GID (Group Identifier).
4. **Un utilisateur peut-il appartenir à plusieurs groupes ? / 一个用户可以属于多个组吗？**
    * Oui. (可以。)
5. **Quelle commande crée un nouvel utilisateur ? / 哪个命令创建新用户？**
    * `useradd` ou `adduser`.
6. **Quelle commande supprime un utilisateur ? / 哪个命令删除用户？**
    * `userdel` ou `deluser`.
7. **Quelle commande change le propriétaire d'un fichier ? / 哪个命令更改文件所有者？**
    * `chown`.
8. **Quelle commande change le groupe d'un fichier ? / 哪个命令更改文件的组？**
    * `chgrp`.
9. **Comment changer à la fois le propriétaire et le groupe (ex: user `bob`, group `dev`) ? / 如何同时更改所有者和组（如用户 `bob`，组 `dev`）？**
    * `chown bob:dev file`.
10. **Que signifie la permission `r` pour un répertoire ? / 对于目录，权限 `r` 意味着什么？**
    * Capacité de lister son contenu (`ls`). (列出其内容的能力。)
11. **Que signifie la permission `x` pour un répertoire ? / 对于目录，权限 `x` 意味着什么？**
    * Capacité de le traverser (`cd`) ou d'accéder aux fichiers dedans. (进入目录或访问其中文件的能力。)
12. **Si un fichier a les droits `rw-r--r--`, quelle est sa valeur octale ? / 如果文件权限是 `rw-r--r--`，它的八进制值是多少？**
    * 644 (`rw-`=6, `r--`=4, `r--`=4).
13. **Que fait `chmod +x script.sh` ? / `chmod +x script.sh` 做什么？**
    * Ajoute le droit d'exécution pour tout le monde (u,g,o). (为所有人添加执行权限。)
14. **Que signifie `chmod 777` ? / `chmod 777` 是什么意思？**
    * Lecture, écriture et exécution pour tout le monde (dangereux). (所有人都有读、写、执行权限（危险）。)
15. **Qui sont les "others" (`o`) ? / "others" (`o`) 是指谁？**
    * Tous les utilisateurs qui ne sont ni le propriétaire, ni dans le groupe du fichier. (既不是所有者也不是文件所属组成员的所有用户。)
16. **Que fait la commande `groups` ? / 命令 `groups` 做什么？**
    * Affiche les groupes auxquels l'utilisateur appartient. (显示用户所属的组。)
17. **Où sont stockés les mots de passe (hashés) ? / 密码（哈希后）存储在哪里？**
    * `/etc/shadow` (lisible uniquement par root).
18. **Où sont définis les utilisateurs (infos publiques) ? / 用户定义（公共信息）在哪里？**
    * `/etc/passwd`.
19. **Que fait `sudo` ? / `sudo` 做什么？**
    * Exécute une commande avec les privilèges d'un autre utilisateur (souvent root). (以另一个用户（通常是 root）的权限执行命令。)
20. **Comment ajouter un utilisateur à un groupe ? / 如何将用户添加到组？**
    * `adduser <user> <group>` (ou `usermod -aG`).

## VI. Types de Fichiers et Structure / 文件类型与结构 (71-80)

1. **Que signifie le type `-` dans `ls -l` ? / `ls -l` 中的类型 `-` 是什么意思？**
    * Fichier régulier. (普通文件。)
2. **Que signifie le type `d` ? / 类型 `d` 是什么意思？**
    * Répertoire. (目录。)
3. **Que signifie le type `l` ? / 类型 `l` 是什么意思？**
    * Lien symbolique. (符号链接。)
4. **Que signifie le type `c` et `b` ? / 类型 `c` 和 `b` 是什么意思？**
    * Périphérique Caractère (Character device) et Bloc (Block device). (字符设备和块设备。)
5. **Un fichier a-t-il une structure imposée par l'OS sous Unix ? / Unix 下操作系统是否强制文件具有特定结构？**
    * Non, c'est juste une suite d'octets. (不，它只是字节序列。)
6. **Comment identifier le type réel d'un fichier (image, texte...) pas seulement par son extension ? / 如何识别文件的真实类型（图像、文本...），而不仅仅是通过扩展名？**
    * Commande `file`.
7. **Qu'est-ce qu'un lien symbolique ? / 什么是符号链接？**
    * Un fichier qui pointe vers le chemin d'un autre fichier. (指向另一个文件路径的文件。)
8. **Sur un `ls -l`, que représente le nombre juste après les droits (ex: `1`) ? / 在 `ls -l` 中，权限后面的数字（如 `1`）代表什么？**
    * Le nombre de liens durs (Hard links). (硬链接数。)
9. **Que se passe-t-il si on supprime la cible d'un lien symbolique ? / 如果删除符号链接的目标会发生什么？**
    * Le lien devient "cassé" (dangling pointer). (链接变“断”/无效。)
10. **Quelle commande permet de voir les premiers octets d'un fichier en hexadécimal ? / 哪个命令可以用十六进制查看文件的前几个字节？**
    * `hexdump` (ou `xxd`, `od`).

## VII. E/S Bas Niveau (File Descriptors) / 低级 I/O (81-90)

1. **Qu'est-ce qu'un descripteur de fichier (fd) ? / 什么是文件描述符 (fd)？**
    * Un entier non-négatif représentant un fichier ouvert. (表示打开文件的非负整数。)
2. **A quoi correspond le fd 0 ? / fd 0 对应什么？**
    * Entrée standard (STDIN). (标准输入。)
3. **A quoi correspond le fd 1 ? / fd 1 对应什么？**
    * Sortie standard (STDOUT). (标准输出。)
4. **A quoi correspond le fd 2 ? / fd 2 对应什么？**
    * Erreur standard (STDERR). (标准错误。)
5. **Quelle fonction système ouvre un fichier ? / 哪个系统函数打开文件？**
    * `open()`.
6. **Quels sont les flags d'ouverture courants pour `open` ? / `open` 的常见打开标志有哪些？**
    * `O_RDONLY`, `O_WRONLY`, `O_RDWR`, `O_CREAT`.
7. **Que retourne `read()` ? / `read()` 返回什么？**
    * Le nombre d'octets lus (ou 0 si EOF, -1 si erreur). (读取的字节数（EOF 为 0，出错为 -1）。)
8. **Quelle fonction permet de se déplacer dans un fichier ouvert ? / 哪个函数允许在打开的文件中移动？**
    * `lseek()`.
9. **Que signifie `SEEK_END` dans `lseek` ? / `lseek` 中的 `SEEK_END` 是什么意思？**
    * Se placer par rapport à la fin du fichier. (相对于文件末尾进行定位。)
10. **Pourquoi faut-il fermer un fichier avec `close()` ? / 为什么要用 `close()` 关闭文件？**
    * Pour libérer le descripteur et les ressources système. (为了释放描述符和系统资源。)

## VIII. E/S Haut Niveau (Streams - stdio) / 高级 I/O (91-100)

1. **Quel type opaque représente un flux en C (`stdio.h`) ? / C 语言 (`stdio.h`) 中哪个不透明类型表示流？**
    * `FILE *`.
2. **Quelle fonction ouvre un fichier en haut niveau ? / 哪个函数用于高级文件打开？**
    * `fopen()`.
3. **Que retourne `fopen` en cas d'erreur ? / `fopen` 出错时返回什么？**
    * `NULL`.
4. **Quelle est la différence entre `open` et `fopen` ? / `open` 和 `fopen` 有什么区别？**
    * `open` est un appel système (renvoie un int), `fopen` est une fonction de bibliothèque (renvoie `FILE*` avec buffering). (`open` 是系统调用（返回 int），`fopen` 是库函数（返回带缓冲的 `FILE*`）。)
5. **Comment lire des blocs de données binaires avec stdio ? / 如何使用 stdio 读取二进制数据块？**
    * `fread()`.
6. **Que fait `fwrite` ? / `fwrite` 做什么？**
    * Écrit des éléments binaires dans un flux. (将二进制元素写入流。)
7. **Comment détecter la fin de fichier avec stdio ? / 如何使用 stdio 检测文件末尾？**
    * `feof()`.
8. **Quel mode utiliser dans `fopen` pour lire ? / `fopen` 中读取应使用什么模式？**
    * `"r"`.
9. **Quel mode utiliser dans `fopen` pour écrire (en écrasant) ? / `fopen` 中写入（覆盖）应使用什么模式？**
    * `"w"`.
10. **Quelle fonction vide le buffer d'un flux vers le disque ? / 哪个函数将流的缓冲区刷新到磁盘？**
    * `fflush()`.

## IX. Approfondissement et details (101-125)

1. **Quel repertoire decrit le materiel et le noyau via un FS virtuel ? / 哪个目录以虚拟文件系统描述内核与硬件？**
    * `/sys`.
2. **A quoi sert `/var` ? / `/var` 有什么用？**
    * Donnees variables (logs, files d'attente, cache). (可变数据，如日志、队列、缓存。)
3. **Quelle difference entre `/usr/share` et `/usr/bin` ? / `/usr/share` 与 `/usr/bin` 有何区别？**
    * `/usr/share` contient des ressources independantes de l'architecture, `/usr/bin` des executables. (`/usr/share` 放通用资源，`/usr/bin` 放可执行文件。)
4. **A quoi sert `/usr/local/include` ? / `/usr/local/include` 有什么用？**
    * En-tetes installes manuellement depuis les sources. (源码手动安装的头文件。)

5. **Quelle variable influence la recherche des bibliotheques statiques a la compilation ? / 编译时影响静态库搜索的变量是哪个？**
    * `LIBRARY_PATH`.
6. **Quelle variable est destinee aux en-tetes C++ ? / C++ 头文件使用的变量是哪个？**
    * `CPLUS_INCLUDE_PATH`.
7. **Que signifie `linux-vdso.so.1` dans `ldd` ? / `ldd` 中的 `linux-vdso.so.1` 代表什么？**
    * Une interface noyau virtuelle exposee aux processus. (内核提供的虚拟共享对象接口。)

8. **Quelle difference entre disque, partition et systeme de fichiers ? / 磁盘、分区、文件系统有何区别？**
    * Disque = materiel, partition = decoupage logique, systeme de fichiers = format/organisation des donnees. (磁盘是硬件，分区是逻辑划分，文件系统是数据组织格式。)
9. **Que signifie le champ "type" dans `/etc/fstab` ? / `/etc/fstab` 中的 "type" 字段表示什么？**
    * Le type de systeme de fichiers (ext4, vfat, nfs, ...). (文件系统类型。)
10. **A quoi servent les champs `dump` et `pass` de `/etc/fstab` ? / `/etc/fstab` 的 `dump` 与 `pass` 有什么用？**
    * `dump` controle la sauvegarde, `pass` l'ordre de `fsck`. (`dump` 控制备份，`pass` 控制 `fsck` 检查顺序。)
11. **Quelle difference entre swap partition et swap fichier ? / 交换分区与交换文件有何区别？**
    * Meme role; l'un est une partition dediee, l'autre un fichier regulier. (同样用途，一个是专用分区，一个是普通文件。)
12. **Que signifie un montage "loop" ? / "loop" 挂载是什么意思？**
    * Monter un fichier (ex: ISO) comme un systeme de fichiers. (将文件如 ISO 作为文件系统挂载。)

13. **Quelle information fournit `stat` qu'un simple `ls` ne donne pas toujours ? / `stat` 提供 `ls` 不一定显示的信息？**
    * L'inode, les timestamps detailes, et les liens. (inode、详细时间戳与链接数。)
14. **Que se passe-t-il si `rmdir` vise un repertoire non vide ? / `rmdir` 作用于非空目录会怎样？**
    * Echec avec erreur. (失败并报错。)
15. **Que signifie le droit `w` sur un repertoire ? / 目录的 `w` 权限意味着什么？**
    * Creer/supprimer des fichiers dans ce repertoire (si `x` est aussi present). (在目录中创建/删除文件（通常需配合 `x`）。)

16. **Quelle est la difference entre lien dur et lien symbolique ? / 硬链接与符号链接有何区别？**
    * Lien dur partage le meme inode; lien symbolique pointe vers un chemin. (硬链接共享 inode；符号链接指向路径。)
17. **Pourquoi `ln -s` reste valide meme si l'inode change ? / 为什么 `ln -s` 在 inode 变化后仍可能有效？**
    * Il reference un chemin, pas un inode. (符号链接引用路径而非 inode。)
18. **Que represente le type `s` dans `ls -l` ? / `ls -l` 中的类型 `s` 表示什么？**
    * Socket local. (本地套接字。)
19. **Que represente le type `p` dans `ls -l` ? / `ls -l` 中的类型 `p` 表示什么？**
    * Tube nomme (FIFO). (命名管道。)

20. **Pourquoi `open` avec `O_CREAT` necessite un `mode` ? / `open` 与 `O_CREAT` 一起使用时为何需要 `mode`？**
    * Pour definir les permissions initiales du nouveau fichier. (指定新文件的初始权限。)
21. **Que signifie un retour `0` de `read()` ? / `read()` 返回 `0` 表示什么？**
    * Fin de fichier (EOF). (到达文件末尾。)
22. **Pourquoi `write()` peut ecrire moins d'octets que demande ? / 为什么 `write()` 可能写入少于请求的字节数？**
    * Interruptions/saturation; il faut boucler pour terminer. (被中断或资源限制，需要循环写完。)
23. **Quelle difference entre `fseek` et `lseek` ? / `fseek` 与 `lseek` 有何区别？**
    * `fseek` agit sur un `FILE*` (stdio, bufferise), `lseek` sur un fd (bas niveau). (`fseek` 操作 `FILE*` 缓冲流，`lseek` 操作 fd。)
24. **Comment distinguer EOF d'une erreur avec stdio ? / 用 stdio 如何区分 EOF 与错误？**
    * Utiliser `feof()` et `ferror()`. (使用 `feof()` 与 `ferror()`。)
25. **Pourquoi `fflush(stdout)` est parfois necessaire ? / 为什么有时需要 `fflush(stdout)`？**
    * Pour forcer l'ecriture des donnees bufferisees. (强制写出缓冲数据。)
