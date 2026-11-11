# Contrôle en évaluation de performances — 14 novembre 2023 性能评估考试 — 2023 年 11 月 14 日

M2 CHPS · S. Zertal · Durée : **2 h** 考试时长：**2 小时**

[Index des annales 历年试题索引](README.md) · [Sujet en français 法语原题](edp_examen_2023-11-14.md) · [Photographie, page 1 原图第 1 页](Images/edp_examen_2023-11-14_p01.png) · [Photographie, page 2 原图第 2 页](Images/edp_examen_2023-11-14_p02.png)

> Transcription du sujet photographié et traduction chinoise, sans corrigé. La présentation et les notations ont été harmonisées sans modifier les données ni les questions. Les consignes concernent uniquement cette épreuve historique. 根据试卷照片整理的法中对照版，不含解答。排版和符号已统一，数据与题目要求保持原意。考试规则仅对应这份历史试卷。法语在前、中文在后，同一行用空格隔开，撇号统一为 '。

## Consignes 考试规则

- Les calculatrices, les notes de cours et de TD sont autorisées mais sont strictement personnelles. 允许使用计算器、课程笔记和 TD 笔记，但必须为本人专用。
- Les ordinateurs et les téléphones sont interdits. 禁止使用电脑和手机。

## Exercice 1 — Unités de calcul et disques 练习 1 — 计算单元与磁盘

*Page 1 du sujet. 对应原卷第 1 页。*

Soit un système composé de deux unités de calcul : $Cal_G$, en charge du calcul d'ordre général, et $Cal_S$, en charge d'un calcul spécifique, et de deux disques $Disk_1$ et $Disk_2$ servant au stockage des données. Les instructions des codes soumis à ce système passent d'abord par les unités de calcul et se répartissent entre elles selon les proportions de calcul général/spécifique qu'ils contiennent. Les deux unités de calcul ont accès aux données sur les disques. 考虑一个由两个计算单元和两个磁盘组成的系统。$Cal_G$ 负责通用计算，$Cal_S$ 负责专用计算；$Disk_1$ 和 $Disk_2$ 用于存储数据。提交到该系统的程序指令首先经过计算单元，并按照程序中通用计算与专用计算的比例，分配到相应单元。两个计算单元都可以访问磁盘中的数据。

Pour $Cal_G$, 85 % des instructions exécutées se terminent et quittent le système, et le reste accède à l'espace de stockage, tandis que pour $Cal_S$, 65 % des instructions exécutées se terminent et quittent le système, et le reste accède à l'espace de stockage. Les données sont uniformément distribuées sur l'espace de stockage composé par les deux disques et les accès aux disques finalisent l'exécution des instructions. 在 $Cal_G$ 上执行的指令中，85% 执行完毕后直接离开系统，其余指令需要访问存储空间；在 $Cal_S$ 上执行的指令中，65% 执行完毕后直接离开系统，其余指令需要访问存储空间。数据均匀分布在两个磁盘共同组成的存储空间中，指令访问磁盘后即完成执行。

Les codes types exécutés sur ce système contiennent en moyenne 80 % de calcul spécifique. $Cal_G$ exécute $1200\ \mathrm{instr/s}$ alors que $Cal_S$ exécute $2500\ \mathrm{instr/s}$. $Disk_1$ a une capacité de 1 TB avec un temps d'accès moyen de 6 ms, alors que $Disk_2$ n'a que 500 GB avec un temps d'accès moyen de 4 ms. 该系统执行的典型程序平均包含 80% 的专用计算。$Cal_G$ 每秒执行 1200 条指令，$Cal_S$ 每秒执行 2500 条指令。$Disk_1$ 的容量为 1 TB，平均访问时间为 6 ms；$Disk_2$ 的容量只有 500 GB，平均访问时间为 4 ms。

### Questions 问题

1. Donnez un schéma pour le système décrit ci-dessus. Il est impératif de détailler les différents serveurs et files associées ainsi que les connexions entre elles. L'ensemble doit être accompagné de labels précisant les fréquences en entrée, les taux de service et les probabilités de répartition. 画出上述系统的模型图。必须详细标出各服务节点及对应队列，以及它们之间的连接关系。图中应标注输入流率、服务率和分流概率。

2. Quelle est la limite supérieure de la fréquence en entrée supportée par ce système pour assurer sa stabilité ? 为保证系统稳定，系统所能承受的输入流率上限是多少？

3. On considère une fréquence d'arrivée initiale de $1000\ \mathrm{instr/s}$ et on change les serveurs pour lesquels le temps moyen d'attente est supérieur au temps moyen de service. Quels sont les serveurs concernés ? Justifiez votre réponse numériquement, étape par étape. 设初始到达率为 $1000\ \mathrm{instr/s}$。如果某个服务节点的平均等待时间大于平均服务时间，就更换该节点。哪些节点需要更换？请逐步给出数值计算并说明理由。

## Exercice 2 — Benchmarks et performances moyennes 练习 2 — 基准程序与平均性能

*Page 2 du sujet. 对应原卷第 2 页。*

Le tableau suivant regroupe les temps d'exécution (en secondes) et le nombre d'instructions exécutées de cinq benchmarks du même domaine applicatif, sur trois systèmes différents. 下表列出了同一应用领域中的 5 个基准程序在 3 个不同系统上的执行时间（单位：秒），以及各基准程序执行的指令数。

| Benchmark 基准程序 | $Syst_1$ : temps (s) 系统 1 执行时间（s） | $Syst_2$ : temps (s) 系统 2 执行时间（s） | $Syst_3$ : temps (s) 系统 3 执行时间（s） | Nombre d'instructions 指令数 |
|---|---|---|---|---|
| 1 | 33.4 | 28.8 | 28.3 | $1.45\times10^{10}$ |
| 2 | 19.9 | 22.1 | 25.3 | $7.97\times10^9$ |
| 3 | 6.5 | 5.3 | 4.7 | $3.11\times10^9$ |
| 4 | 84.3 | 75.8 | 80.1 | $3.77\times10^{10}$ |
| 5 | 101.1 | 99.4 | 70.2 | $4.56\times10^{10}$ |

On considère que ces benchmarks ont des poids équivalents. 假设这 5 个基准程序的权重相同。

### Questions 问题

1. Calculez le temps d'exécution moyen et le MIPS moyen par système. 分别计算每个系统的平均执行时间和平均 MIPS（每秒执行的百万条指令数）。

2. Calculez l'accélération moyenne par système avec le système 3 comme référence. Ces valeurs d'accélérations moyennes reflètent-elles les vraies performances ? Justifiez votre réponse. 以系统 3 为参照，分别计算每个系统的平均加速比。这些平均加速比能否反映真实性能？请说明理由。

## Exercice 3 — Placement des données sur disque 练习 3 — 磁盘数据放置

*Page 2 du sujet. 对应原卷第 2 页。*

Un module de placement intelligent des données sur disque s'occupe de stocker les données sur les cylindres internes (numéros faibles), puis, selon les disponibilités, vers les cylindres externes (numéros forts). On aimerait savoir si ce module remplit bien sa fonction et on procède à un ensemble de tests (accès) avec vérification du numéro de cylindre accédé. 一个智能磁盘数据放置模块优先将数据存储在内部柱面（编号较小），然后根据可用空间，逐步放置到外部柱面（编号较大）。现在希望判断该模块是否正常发挥作用，因此进行了一系列访问测试，并检查每次访问的柱面编号。

On a observé les accès aux huit cylindres centraux $[cyl_0,\ldots,cyl_7]$ et on a comptabilisé les accès suivants : 观测中央的 8 个柱面 $[cyl_0,\ldots,cyl_7]$，得到以下访问次数：

| Numéro de cylindre 柱面编号 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|---|
| Nombre d'accès 访问次数 | 29 | 19 | 18 | 25 | 17 | 10 | 15 | 11 |

### Questions 问题

1. Poser les hypothèses pour tester l'utilité de ce module de placement. 为检验该数据放置模块是否有效，提出相应的统计假设。

2. Vérifier l'utilité de ce module à 5 % de risque et en utilisant le test de Kolmogorov–Smirnov (voir table jointe). Détailler les différentes étapes. 在 5% 的显著性水平下，使用 Kolmogorov–Smirnov 检验判断该模块是否有效（参见附表）。详细说明各个步骤。

> **Note de transcription :** la table jointe mentionnée dans la question 2 n'est pas visible sur les photographies fournies. **整理说明：**题目第 2 问提到的附带统计表未出现在所提供的照片中。
