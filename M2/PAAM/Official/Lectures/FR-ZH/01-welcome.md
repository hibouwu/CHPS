# Programmation avancée des architectures multicœurs · 多核体系结构高级编程

[目录](README.md) · [教师英文讲义（4 页）](../../GitLab/cours/01-welcome.pdf) · [本学年课表](../../GitLab/Readme.md)

## Pourquoi étudier les architectures multicœurs · 为什么学习多核体系结构

[原讲义第 1–2 页](../../GitLab/cours/01-welcome.pdf#page=1)

**FR** Les architectures multicœurs sont présentes dans les téléphones, les postes de travail et les centres de données. Dans l'exemple du cours, la machine Arya possède quatre sockets de douze cœurs, soit 48 cœurs. Un socket correspond ici à un processeur physique et contient plusieurs cœurs. Pour tirer parti du matériel, le programme doit fournir du travail parallèle, coordonner les accès aux données partagées et limiter les coûts de communication et de synchronisation.

**中文** 手机、工作站和数据中心都有多核处理器。课件以 Arya 为例，机器有 4 个插槽（socket），每个插槽对应一颗有 12 个核心的物理处理器，共 48 核。要利用这些核心，程序需要提供可并行的工作，协调对共享数据的访问，并控制通信与同步开销。

## Organisation et progression · 课程组织和学习顺序

[原讲义第 3 页](../../GitLab/cours/01-welcome.pdf#page=3) · [本学年课程安排](../../README.md)

**FR** La diapositive décrit une organisation type sur six semaines, avec une à deux heures de théorie, quatre à cinq heures de TP et environ une heure de travail personnel par semaine. Le dépôt 2026–2027 indique 30 h et présente l'ordre suivant. Le parcours commence par les threads, les mutex et les variables de condition, puis étudie les verrous, les algorithmes non bloquants et la mémoire transactionnelle. La mémoire persistante est la cinquième séance et NUMA figure en complément. Consulter le dépôt pour les dates et les salles de cette année.

**中文** 第 3 页给出的典型组织方式是六周，每周 1–2 小时理论课、4–5 小时实验和约 1 小时课外练习。2026–2027 年 GitLab 首页写明课程共 30 小时，并列出了本学年的顺序。先学线程、互斥锁与条件变量，再学习锁的实现、非阻塞算法和事务内存。第 5 课是持久内存，NUMA 列为补充。具体上课与考试的时间、地点见今年的课程课表。

## Prérequis · 先修知识

[原讲义第 4 页](../../GitLab/cours/01-welcome.pdf#page=4)

**FR** Il faut savoir programmer en C, manipuler les pointeurs et gérer la mémoire. Côté système, les notions de processus et de communication interprocessus sont utiles. Pour lire les exemples, repérer où une donnée est allouée, qui peut y accéder et à quel moment sa durée de vie se termine.

**中文** 先掌握 C 指针和内存管理，以及操作系统中的进程和进程间通信。读代码时先定位数据在哪里分配、哪些执行者能访问它、它的生命周期何时结束。后面的线程与同步题经常从这三个问题开始。

## Vérification rapide · 自检

**Question / 问题** Un processeur à 48 cœurs suffit-il à accélérer 48 fois un programme ? 有 48 个核心，程序就能加速 48 倍吗？

**Réponse / 答案** Le gain dépend du travail parallélisable et du coût des accès partagés. Une partie séquentielle ou un verrou très disputé peut limiter le gain. 加速取决于可并行的工作比例以及共享访问的代价。串行部分或竞争激烈的锁都可能限制加速。
