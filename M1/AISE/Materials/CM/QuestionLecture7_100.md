
# 100 Questions de révision - Lecture 7 : Environnement Logiciel et Virtualisation / 100 道复习题 - 第七讲：软件环境与虚拟化

## I. Rappel Débogage / 调试回顾 (1-10)

1. **Qu'est-ce qu'une "Segmentation Fault" ? / 什么是“段错误”？**
    * Erreur d'accès mémoire illégal (hors de la zone allouée). (非法内存访问（超出分配区域）。)
2. **Quel est le principe de GDB ? / GDB 的原理是什么？**
    * Exécuter le programme sous contrôle pour s'arrêter en cas de crash et inspecter l'état. (受控执行程序，在崩溃时停止并检查状态。)
3. **Comment Valgrind détecte-t-il les erreurs mémoire ? / Valgrind 如何检测内存错误？**
    * Il instrumente le code (émule l'exécution CPU) pour surveiller chaque accès mémoire. (它对代码进行插装（模拟 CPU 执行）以监控每次内存访问。)
4. **Quel est l'inconvénient principal de Valgrind ? / Valgrind 的主要缺点是什么？**
    * Il ralentit considérablement l'exécution (x10 - x50). (显著降低执行速度。)
5. **Que trace l'outil `strace` ? / 工具 `strace` 跟踪什么？**
    * Les appels système (System Calls) et les signaux. (系统调用和信号。)
6. **Si un programme plante sans message, quel outil lancer en premier ? / 如果程序崩溃且无消息，首先运行哪个工具？**
    * `strace` (pour voir la dernière interaction système) ou `gdb`.
7. **Quel outil est le mieux adapté pour trouver une fuite de mémoire ? / 哪个工具最适合查找内存泄漏？**
    * Valgrind (Memcheck).
8. **Comment voir les arguments passés à `open()` par un programme ? / 如何查看程序传递给 `open()` 的参数？**
    * Avec `strace`.
9. **GDB permet-il de modifier la valeur d'une variable en cours d'exécution ? / GDB 允许在运行时修改变量值吗？**
    * Oui (`set variable x = 10`).
10. **Quelle commande GDB affiche la pile d'appels ? / 哪个 GDB 命令显示调用栈？**
    * `backtrace` (ou `bt`).

## II. Environnement Logiciel & Reproductibilité / 软件环境与复现性 (11-30)

1. **Qu'est-ce qu'un environnement logiciel ? / 什么是软件环境？**
    * L'ensemble des logiciels et bibliothèques nécessaires pour exécuter une application. (运行应用程序所需的软件和库的集合。)
2. **Qu'est-ce qu'une dépendance ? / 什么是依赖？**
    * Un logiciel (ou bibliothèque) requis par un autre pour fonctionner. (另一个软件运行所需的软件（或库）。)
3. **Qu'est-ce qu'un "Dependency Hell" ? / 什么是 "Dependency Hell"？**
    * Conflits de versions insolubles entre différentes dépendances. (不同依赖之间无法解决的版本冲突。)
4. **Qu'est-ce que la reproductibilité en HPC ? / HPC 中的复现性是指什么？**
    * Capacité à obtenir les mêmes résultats scientifiques sur des machines ou temps différents. (在不同机器或时间获得相同科学结果的能力。)
5. **Pourquoi l'environnement global (`/usr`) pose-t-il problème pour la reproductibilité ? / 为什么全局环境 (`/usr`) 会导致复现性问题？**
    * Il change avec les mises à jour système (apt upgrade), incontrôlable par l'utilisateur. (随系统更新而变化，用户无法控制。)
6. **Quels sont les 4 types de portée d'environnement cités ? / 提到的 4 种环境范围是什么？**
    * Global, Local (User), Isolé, Temporaire. (全局，本地（用户），隔离，临时。)
7. **Où sont installés les logiciels dans un environnement local (souvent) ? / 本地环境中的软件通常安装在哪里？**
    * `~/.local` ou `~/bin`.
8. **Quel est le problème principal du déploiement manuel (compilation) ? / 手动部署（编译）的主要问题是什么？**
    * Difficile à reproduire, chronophage, pas de gestion automatique des dépendances. (难以复现，耗时，无自动依赖管理。)
9. **Qu'est-ce qu'un gestionnaire de paquets système (ex: `apt`) ? / 什么是系统包管理器（如 `apt`）？**
    * Outil qui installe des binaires pré-compilés validés par la distribution. (安装发行版验证的预编译二进制文件的工具。)
10. **Quelle est la limite de `apt` pour un développeur ? / `apt` 对开发者的限制是什么？**
    * Versions souvent anciennes, impossible d'installer plusieurs versions de la même lib. (版本通常较旧，无法安装同一库的多个版本。)
11. **Citez des gestionnaires de paquets "avancés" ou fonctionnels. / 列举“高级”或功能性包管理器。**
    * Guix, Spack, Nix.
12. **Quel est l'avantage de Guix/Nix pour la reproductibilité ? / Guix/Nix 对复现性的优势是什么？**
    * Chaque paquet est stocké dans un chemin unique basé sur le hash de tous ses inputs. (每个包存储在基于其所有输入哈希的唯一路径中。)
13. **Qu'est-ce que Spack ? / 什么是 Spack？**
    * Un gestionnaire de paquets dédié au HPC (flexible sur les compilateurs/MPI). (专用于 HPC 的包管理器（对编译器/MPI 灵活）。)
14. **Pourquoi documenter l'environnement ne suffit pas ? / 为什么仅仅记录环境是不够的？**
    * Car les liens de téléchargement meurent et les instructions manuelles sont ambiguës. (因为下载链接会失效，手动说明有歧义。)
15. **Qu'est-ce qu'un environnement "Isolé" ? / 什么是“隔离”环境？**
    * Un environnement qui ne voit pas (ou peu) le système hôte pour éviter les interférences. (看不到（或很少看到）宿主系统以避免干扰的环境。)

## III. Conteneurs et Docker / 容器与 Docker (31-70)

1. **Qu'est-ce qu'un conteneur ? / 什么是容器？**
    * Une instance d'espace utilisateur isolée partageant le noyau de l'hôte. (共享宿主内核的隔离用户空间实例。)
2. **Quelle est la différence fondamentale entre Conteneur et VM ? / 容器和 VM 的根本区别是什么？**
    * La VM virtualise le matériel (a son propre noyau), le conteneur virtualise l'OS (partage le noyau). (VM 虚拟化硬件（有自己的内核），容器虚拟化 OS（共享内核）。)
3. **Docker est-il un système de virtualisation matériel ? / Docker 是硬件虚拟化系统吗？**
    * Non, c'est de la virtualisation au niveau de l'OS. (不，是 OS 级虚拟化。)
4. **Qu'est-ce qu'une Image Docker ? / 什么是 Docker 镜像？**
    * Un modèle statique et immuable contenant tout le système de fichiers pour le conteneur. (包含容器所需所有文件系统的静态不可变模板。)
5. **Qu'est-ce qu'un Dockerfile ? / 什么是 Dockerfile？**
    * Script texte décrivant les étapes pour construire une image. (描述构建镜像步骤的文本脚本。)
6. **Quelle commande construit une image ? / 哪个命令构建镜像？**
    * `docker build`.
7. **Quelle commande lance un conteneur ? / 哪个命令启动容器？**
    * `docker run`.
8. **Quelle instruction Dockerfile définit l'image de base ? / 哪个 Dockerfile 指令定义基础镜像？**
    * `FROM` (ex: `FROM ubuntu:20.04`).
9. **Quelle instruction Dockerfile exécute une commande shell lors de la construction ? / 哪个 Dockerfile 指令在构建时执行 shell 命令？**
    * `RUN` (ex: `RUN apt-get install gcc`).
10. **Quelle instruction copie des fichiers locaux dans l'image ? / 哪个指令将本地文件复制到镜像中？**
    * `COPY` (ou `ADD`).
11. **Les modifications dans un conteneur persistent-elles dans l'image ? / 容器中的修改会持久保存到镜像中吗？**
    * Non, elles sont perdues à la suppression du conteneur (sauf si commit). (不，容器删除时丢失（除非 commit）。)
12. **Comment partager des fichiers entre l'hôte et le conteneur ? / 如何在主机和容器间共享文件？**
    * Avec des volumes (`-v /hote:/conteneur`).
13. **Qu'est-ce que le Docker Hub ? / 什么是 Docker Hub？**
    * Un registre public pour stocker et partager des images. (用于存储和共享镜像的公共注册表。)
14. **Quelle commande télécharge une image depuis le registre ? / 哪个命令从注册表下载镜像？**
    * `docker pull`.
15. **Qu'est-ce que Apptainer (Singularity) ? / 什么是 Apptainer (Singularity)？**
    * Un système de conteneurs sécurisé conçu pour le HPC (pas de démon root). (专为 HPC 设计的安全容器系统（无 root 守护进程）。)
16. **Pourquoi Docker est-il souvent interdit sur les clusters HPC ? / 为什么 HPC 集群通常禁止 Docker？**
    * Pour des raisons de sécurité (le démon Docker tourne en root). (出于安全原因（Docker 守护进程以 root 运行）。)
17. **Une image Docker Linux tourne-t-elle nativement sur Windows ? / Linux Docker 镜像能在 Windows 上原生运行吗？**
    * Non, elle nécessite une couche de compatibilité (WSL2 ou VM Linux cachée). (不，需要兼容层（WSL2 或隐藏的 Linux VM）。)
18. **Quels sont les "Namespaces" Linux ? / 什么是 Linux "Namespaces"？**
    * Fonctionnalité du noyau pour isoler les ressources (PID, Réseau, Mount...). (用于隔离资源（PID，网络，挂载...）的内核功能。)
19. **Qu'est-ce que les "Cgroups" ? / 什么是 "Cgroups"？**
    * Control Groups : limiter l'usage ressources (CPU, RAM) d'un groupe de processus. (限制进程组的资源使用（CPU，RAM）。)
20. **Peut-on changer le noyau dans un conteneur Docker ? / 可以在 Docker 容器中更改内核吗？**
    * Non, le conteneur utilise le noyau de l'hôte. (不，容器使用宿主内核。)
21. **Si l'hôte est Linux 5.4, quelle version du noyau voit le conteneur ubuntu:latest ? / 如果宿主是 Linux 5.4，ubuntu:latest 容器看到哪个内核版本？**
    * Linux 5.4.
22. **Le système de fichiers d'un conteneur est-il persistant ? / 容器的文件系统是持久的吗？**
    * Non, éphemère par défaut. (不，默认是临时的。)
23. **Quelle commande liste les conteneurs en cours d'exécution ? / 哪个命令列出正在运行的容器？**
    * `docker ps`.
24. **Quelle commande liste toutes les images locales ? / 哪个命令列出所有本地镜像？**
    * `docker images`.
25. **Comment supprimer un conteneur ? / 如何删除容器？**
    * `docker rm`.
26. **Comment supprimer une image ? / 如何删除镜像？**
    * `docker rmi`.
27. **Qu'est-ce que `docker build -t nom:tag .` ? / `docker build -t nom:tag .` 是什么？**
    * Construire une image nommée `nom` avec le tag `tag` à partir du Dockerfile dans le répertoire courant (`.`). (从当前目录的 Dockerfile 构建名为 `nom` 标签为 `tag` 的镜像。)
28. **Quelle est la "couche" (layer) dans Docker ? / Docker 中的“层” (layer) 是什么？**
    * Chaque instruction du Dockerfile crée une couche de différence système de fichiers (cacheable). (Dockerfile 的每条指令创建一个文件系统差异层（可缓存）。)
29. **Pourquoi nettoyer le cache apt dans la même instruction RUN ? / 为什么要在同一个 RUN 指令中清理 apt 缓存？**
    * Pour réduire la taille de la couche et donc de l'image finale. (为了减小层的大小，从而减小最终镜像。)
30. **Peut-on exécuter un conteneur en mode interactif ? / 可以交互式运行容器吗？**
    * Oui, avec `-it` (ex: `docker run -it ubuntu bash`).
31. **Qu'est-ce qu'une image "Alpine" ? / 什么是 "Alpine" 镜像？**
    * Une distribution Linux minimaliste (~5 Mo) très utilisée pour les conteneurs légers. (用于轻量级容器的极简 Linux 发行版。)
32. **Docker garantit-il la performance native ? / Docker 保证原生性能吗？**
    * Presque (overhead négligeable pour le CPU/RAM, faible overhead pour I/O réseau). (几乎（CPU/RAM 开销可忽略，网络 I/O 开销小）。)
33. **Comment un conteneur accède-t-il au réseau ? / 容器如何访问网络？**
    * Via un pont (bridge) virtuel par défaut (NAT). (默认通过虚拟网桥 (NAT)。)
34. **Comment exposer un port du conteneur vers l'hôte ? / 如何将容器端口暴露给主机？**
    * `-p hote_port:container_port`.
35. **Qu'est-ce que Docker Compose ? / 什么是 Docker Compose？**
    * Outil pour définir et lancer des applications multi-conteneurs (via YAML). (用于定义和启动多容器应用的工具。)
36. **Peut-on utiliser une GUI depuis un conteneur ? / 可以在容器中使用 GUI 吗？**
    * Oui, mais complexe (mapper le socket X11). (可以，但复杂（映射 X11 套接字）。)
37. **Si je supprime tout, puis-je reconstruire l'image identique ? / 如果删除所有内容，能否重建相同的镜像？**
    * Pas forcément, si `apt-get install` télécharge des versions plus récentes (sauf si versions épinglées). (不一定，如果 `apt` 下载了新版本（除非锁定版本）。)
38. **Comment garantir la reproductibilité absolue de la construction ? / 如何保证构建的绝对复现性？**
    * Utiliser des digests d'image (sha256) et des gestionnaires purement fonctionnels (Guix/Nix). (使用镜像摘要和纯函数式管理器。)
39. **Qu'est-ce que le "Layer Caching" ? / 什么是 "Layer Caching"？**
    * Docker réutilise les couches déjà construites si l'instruction n'a pas changé. (如果指令未变，Docker 重用已构建的层。)
40. **Quel est l'impact de l'ordre des instructions dans le Dockerfile ? / Dockerfile 中指令顺序的影响是什么？**
    * Mettre les choses qui changent peu (install libs) au début pour maximiser le cache. (将变化少的内容放在前面以最大化缓存。)

## IV. Virtualisation (VM) / 虚拟化 (VM) (71-80)

1. **Quel logiciel permet de créer des VM ? / 哪个软件可以创建 VM？**
    * Un Hyperviseur (VirtualBox, VMware, KVM).
2. **La VM voit-elle le matériel réel ? / VM 能看到真实硬件吗？**
    * Généralement non, elle voit du matériel émulé/virtuel. (通常不能，它看到的是模拟/虚拟硬件。)
3. **Une VM nécessite-t-elle un OS complet ? / VM 需要完整的 OS 吗？**
    * Oui (Noyau + User space).
4. **Quel est l'avantage de la VM sur le conteneur pour la sécurité ? / VM 在安全方面相比容器的优势是什么？**
    * Isolation plus forte (noyau distinct, surface d'attaque réduite). (隔离更强（内核不同，攻击面减小）。)
5. **Quel est l'avantage de la VM pour la compatibilité ? / VM 在兼容性方面的优势是什么？**
    * Peut tourner un OS totalement différent (Windows sur Linux). (可以运行完全不同的 OS。)
6. **La performance disque est-elle meilleure en VM ou Conteneur ? / 磁盘性能是 VM 好还是容器好？**
    * Conteneur (accès direct FS hôte vs disque virtuel image). (容器（直接访问主机 FS vs 虚拟磁盘镜像）。)
7. **Qu'est-ce que le "Overhead" de la virtualisation ? / 虚拟化的 "Overhead" 是什么？**
    * Ressources consommées par l'émulation elle-même (CPU, RAM). (模拟本身消耗的资源。)
8. **Le démarrage d'une VM est-il instantané ? / VM 启动是瞬间的吗？**
    * Non, il faut booter tout l'OS invité (secondes/minutes). (不，需要启动整个客户 OS。)
9. **Peut-on faire tourner Docker dans une VM ? / 可以在 VM 中运行 Docker 吗？**
    * Oui.
10. **Peut-on faire tourner une VM dans un conteneur ? / 可以在容器中运行 VM 吗？**
    * Techniquement oui (KVM dans docker), mais rare. (技术上可以，但罕见。)

## V. Divers / 其他 (81-100)

1. **Qu'est-ce qu'une "Image Registry" locale ? / 什么是本地 "Image Registry"？**
    * Serveur privé pour stocker des images (ex: GitLab Container Registry). (存储镜像的私有服务器。)
2. **Qu'est-ce que l'utilisateur `root` dans un conteneur ? / 容器中的 `root` 用户是什么？**
    * C'est root à l'intérieur du namespace, mais il peut être mappé à un utilisateur normal sur l'hôte (User Namespaces). (它是命名空间内的 root，但可以映射为主机上的普通用户。)
3. **Singularity utilise-t-il des images Docker ? / Singularity 使用 Docker 镜像吗？**
    * Il peut les importer et les convertir (format SIF). (它可以导入并转换它们。)
4. **Que signifie "Immuable" pour un conteneur ? / 容器的“不可变”意味着什么？**
    * On ne met pas à jour un conteneur vivant, on en recrée un nouveau depuis une nouvelle image. (不更新运行中的容器，而是从新镜像重新创建一个。)
5. **Pourquoi utiliser `-v` (volumes) en HPC ? / 为什么在 HPC 中使用 `-v` (volumes)？**
    * Pour accéder aux données de calcul (souvent sur disque partagé type Lustre/GPFS). (为了访问计算数据（通常在 Lustre/GPFS 等共享磁盘上）。)
6. **Qu'est-ce que CI/CD ? / 什么是 CI/CD？**
    * Continuous Integration / Continuous Deployment.
7. **Quel est le lien entre CI/CD et Docker ? / CI/CD 和 Docker 有什么联系？**
    * Les jobs CI tournent souvent dans des conteneurs isolés pour garantir un environnement propre. (CI 任务通常在隔离容器中运行以保证环境清洁。)
8. **Dans quel fichier liste-t-on les dépendances Python ? / 在哪个文件中列出 Python 依赖？**
    * `requirements.txt` (ou `pyproject.toml`).
9. **Dans quel fichier liste-t-on les paquets système d'un projet Debian ? / 在哪个文件中列出 Debian 项目的系统包？**
    * `debian/control` (ou simplement une liste `apt.txt` pour scripts perso).
10. **Qu'est-ce que `LD_PRELOAD` ? / 什么是 `LD_PRELOAD`？**
    * Variable d'environnement pour forcer le chargement d'une bibliothèque avant les autres (hooking/debugging). (强制在其他库之前加载某库的环境变量。)
11. **Comment connaître la version du noyau Linux ? / 如何知道 Linux 内核版本？**
    * `uname -r`.
12. **Comment connaître la distribution Linux ? / 如何知道 Linux 发行版？**
    * `cat /etc/os-release`.
13. **Guix est-il aussi un système d'exploitation complet ? / Guix 也是一个完整的操作系统吗？**
    * Oui (Guix System), mais s'utilise aussi comme gestionnaire de paquets sur une autre distro. (是的，但也可用作其他发行版上的包管理器。)
14. **Citez un avantage de l'isolation pour le développement. / 列举隔离对开发的一个好处。**
    * Pouvoir travailler sur plusieurs projets utilisant des versions différentes de Python/GCC sans conflit. (可以在使用不同 Python/GCC 版本的多个项目上工作而不冲突。)
15. **Qu'est-ce que Open Container Initiative (OCI) ? / 什么是 Open Container Initiative (OCI)？**
    * Standardisation des formats de conteneurs et d'images (Docker, Podman, etc. sont compatibles). (容器和镜像格式的标准化。)
16. **Podman vs Docker ? / Podman vs Docker？**
    * Podman est sans-démon (daemonless) et rootless par défaut, compatible CLI Docker. (Podman 默认无守护进程且无 root，CLI 兼容 Docker。)
17. **Qu'est-ce qu'un environnement virtuel Python (`venv`) ? / 什么是 Python 虚拟环境 (`venv`)？**
    * Isolation légère pour les paquets Python (dossier local avec ses propres libs). (Python 包的轻量级隔离。)
18. **Conda est-il un gestionnaire de paquets système ou langage ? / Conda 是系统还是语言包管理器？**
    * Les deux (gère binaires, python, R, dépendances système...). (两者都是（管理二进制，Python，R，系统依赖...）。)
19. **Pourquoi utiliser un Dockerfile Multi-stage ? / 为什么使用多阶段 Dockerfile？**
    * Pour compiler dans une étape lourde, et ne copier que l'exécutable dans une image finale légère. (在重型阶段编译，仅将可执行文件复制到最终轻量镜像。)
20. **Comment réduire la surface d'attaque d'une image ? / 如何减少镜像的攻击面？**
    * Utiliser des images minimales (distroless, alpine), ne pas installer d'outils inutiles. (使用最小镜像，不安装无用工具。)
21. **Qu'est-ce que l'orchestration de conteneurs ? / 什么是容器编排？**
    * Gérer le déploiement de milliers de conteneurs sur plusieurs machines (Kubernetes). (管理多台机器上数千个容器的部署。)
22. **Un conteneur a-t-il une adresse IP ? / 容器有 IP 地址吗？**
    * Oui, sur son réseau virtuel interne. (是的，在其内部虚拟网络上。)
23. **Peut-on limiter la RAM d'un conteneur ? / 可以限制容器 RAM 吗？**
    * Oui (`--memory="1g"`).
24. **Qu'est-ce qu'un "Bind Mount" ? / 什么是 "Bind Mount"？**
    * Monter un fichier/dossier spécifique de l'hôte dans le conteneur (type de volume). (将主机的特定文件/文件夹挂载到容器中。)
25. **Comment voir les logs d'un conteneur détaché ? / 如何查看分离容器的日志？**
     * `docker logs <container_id>`.
