# Lecture 7: Environnement logiciel et Virtualisation *软件环境与虚拟化*

## Table des matières *目录*

- [Lecture 7: Environnement logiciel et Virtualisation *软件环境与虚拟化*](#lecture-7-environnement-logiciel-et-virtualisation-软件环境与虚拟化)
  - [Table des matières *目录*](#table-des-matières-目录)
  - [Rappel : Débogage *回顾：调试*](#rappel--débogage-回顾调试)
    - [Segfaults](#segfaults)
    - [GDB (GNU Debugger)](#gdb-gnu-debugger)
    - [Valgrind](#valgrind)
    - [Strace](#strace)
  - [Environnement logiciel *软件环境*](#environnement-logiciel-软件环境)
    - [Portée des environnements *环境范围*](#portée-des-environnements-环境范围)
  - [Problème de reproductibilité *复现性问题*](#problème-de-reproductibilité-复现性问题)
  - [Solutions de déploiement *部署方案*](#solutions-de-déploiement-部署方案)
    - [1. Déploiement manuel *手动部署*](#1-déploiement-manuel-手动部署)
    - [2. Gestionnaires de paquets *包管理器*](#2-gestionnaires-de-paquets-包管理器)
    - [3. Conteneurs *容器*](#3-conteneurs-容器)
  - [Docker / Conteneurs *Docker 与容器*](#docker--conteneurs-docker-与容器)
    - [Concepts clés *核心概念*](#concepts-clés-核心概念)
    - [Workflow *工作流程*](#workflow-工作流程)
    - [Avantages vs Inconvénients *优缺点*](#avantages-vs-inconvénients-优缺点)
  - [Virtualisation *虚拟化*](#virtualisation-虚拟化)
    - [Conteneur vs Machine Virtuelle (VM)](#conteneur-vs-machine-virtuelle-vm)
  - [Ressources et Pratique *资源与实践*](#ressources-et-pratique-资源与实践)
    - [Tutoriel Guix et Org-mode (ComPAS 2025)](#tutoriel-guix-et-org-mode-compas-2025)

## Rappel : Débogage *回顾：调试*

### Segfaults

- **Segmentation violation fault** : Erreur d'accès mémoire (访问非法内存地址).

### GDB (GNU Debugger)

Le principe est de lancer le programme à l'intérieur du débogueur. En cas de crash, le débogueur arrête l'exécution à l'endroit exact du problème, permettant d'inspecter les variables et la pile d'appels (call stack). (GDB 的原理是在调试器中启动程序。当出现问题时，调试器会在发生处暂停，允许查看变量内容和函数调用栈。)

### Valgrind

Valgrind fonctionne différemment : il instrumente le programme (ajoute du code de surveillance) pour détecter les erreurs mémoire (fuites, accès illégaux). Cela ralentit considérablement l'exécution. (Valgrind 通过插装程序来工作，插入代码以监控内存访问。这会显著降低程序运行速度。)

### Strace

Outil pour tracer les appels système (system calls) et les signaux. Il affiche chaque appel système effectué, ses arguments et sa valeur de retour. (用于跟踪系统调用和信号，显示程序执行过程中的每一个系统调用及其参数和返回值。)

## Environnement logiciel *软件环境*

**Définition** : Configuration mettant à disposition un ou plusieurs logiciels avec leurs dépendances. (提供一个或多个软件及其依赖项的配置。)
*Exemple : Ubuntu Linux 24.04 avec Mozilla Firefox 126.0.1 et GCC 13.3.*

**Dépendance (Dependency)** : Logiciel dont dépend un autre logiciel pour fonctionner. (一个软件运行所依赖的其他软件。)
*Exemple : La bibliothèque `fiboclever` est une dépendance de `fibotest`.*

### Portée des environnements *环境范围*

1. **Environnement Global** : Logiciels disponibles pour tous les utilisateurs (e.g., `/usr/bin`, `/usr/lib`).
2. **Environnement Local** : Logiciels spécifiques à un utilisateur (e.g., dossier personnel `~/.local`).
3. **Environnement Isolé** : Configuration séparée pour éviter les conflits (e.g., besoin de GCC 9 alors que le système a GCC 13).
4. **Environnement Temporaire** : Configuration éphémère pour une tâche spécifique (e.g., test unitaire).

## Problème de reproductibilité *复现性问题*

Dans le calcul haute performance (HPC), les environnements sont complexes (nombreuses dépendances) et déployés sur plusieurs machines ou à des moments différents (années d'intervalle). (在 HPC 中，环境复杂且需跨机器或跨时间部署。)

**Motivation** : Éviter les incohérences de résultats dues aux changements logiciels (versions de bibliothèques, noyau OS).

## Solutions de déploiement *部署方案*

### 1. Déploiement manuel *手动部署*

Compilation manuelle des sources ou installation de binaires. (手动编译源码或安装二进制文件。)

- **Avantages** : Contrôle total (versions, options de compilation). (完全控制权。)
- **Inconvénients** : Chronophage, sujet aux erreurs humaines, documentation difficile. (耗时、易错。)

### 2. Gestionnaires de paquets *包管理器*

Outils comme `apt`, `yum`, `brew`, `guix`, `spack`. Délègue l'installation et la gestion des dépendances. (委托给专门软件管理。)

- **Avantages** : Simplification, gestion automatique des erreurs, standardisation. (简化流程，自动依赖管理。)
- **Inconvénients** :
  - *Gestionnaires de base (`apt`)* : Versions fixées par la distribution, manque de flexibilité, reproductibilité limitée dans le temps. (版本受限，复现性差。)
  - *Gestionnaires avancés (`Guix`, `Spack`)* : Meilleure reproductibilité et isolation, mais complexité élevée. (更好的复现性和隔离，但复杂度高。)

### 3. Conteneurs *容器*

Docker, Singularity, Apptainer. Empaquetage de l'environnement entier (sauf le noyau) dans une image. (将除内核外的整个环境打包成镜像。)

## Docker / Conteneurs *Docker 与容器*

Docker est une plateforme simplifiant le développement, le déploiement et l'exécution d'applications via la conteneurisation. (Docker 通过容器化简化应用生命周期。)

### Concepts clés *核心概念*

- **Image** : Fichier statique contenant tout le nécessaire (OS, bibliothèques, code). Une fois construite, elle est immuable. (包含运行所需一切的静态文件，构建后不可变。)
- **Dockerfile** : "Recette" textuelle décrivant comment construire l'image (FROM, RUN, COPY). (描述构建步骤的配方。)
- **Conteneur** : Instance en exécution d'une image, isolée par des *namespaces* Linux mais partageant le noyau. (镜像的运行实例，用户态隔离但共享内核。)

### Workflow *工作流程*

1. **Construction (`docker build`)** : Créer l'image à partir du Dockerfile.
2. **Distribution (`docker push/pull`)** : Partager l'image via un registre (Docker Hub, GitLab Registry).
3. **Exécution (`docker run`)** : Lancer un conteneur isolé. Utiliser `-v` pour monter des volumes (partager des fichiers avec l'hôte).

### Avantages vs Inconvénients *优缺点*

- **Pour** : Reproductibilité garantie (si l'image est conservée), déploiement rapide, isolation légère. (复现性强，部署快，轻量隔离。)
- **Contre** : Taille des images (GBs), nécessite un moteur de conteneur, isolation moins forte que les VM. (镜像大，需运行时引擎，隔离性弱于 VM。)

## Virtualisation *虚拟化*

Émulation logicielle d'une machine complète (Hardware + OS). (通过软件模拟整台机器。)

### Conteneur vs Machine Virtuelle (VM)

- **Conteneur** : Isolation de l'espace utilisateur (User space), partage le noyau de l'hôte. Léger, démarrage rapide. (隔离用户态，共享内核。轻量，启动快。)
- **VM (Virtual Machine)** : Isolation complète (y compris le noyau), émule le matériel. Lourd, démarrage lent. (完全隔离，模拟硬件。沉重，启动慢。)

**Choix** :

- Utiliser **Conteneurs** pour la distribution logicielle et la reproductibilité des calculs.
- Utiliser **VM** pour des besoins de sécurité forte, de noyaux spécifiques ou d'émulation matérielle.

## Ressources et Pratique *资源与实践*

### Tutoriel Guix et Org-mode (ComPAS 2025)

Atelier pratique sur le déploiement logiciel reproductible en HPC.

- [Lien vers le tutoriel](https://guix-org-tutorial-compass-2025.gitlab.io/tutorial/)
- [Étude de référence (GitLab)](https://gitlab.com/guix-org-tutorial-compas-2025/studies/reference-study)

> **Exercice** : Suivez le `README.md` de l'étude de référence pour reproduire l'environnement logiciel avec Docker.
