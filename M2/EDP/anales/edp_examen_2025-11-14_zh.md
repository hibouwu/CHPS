# Contrôle en évaluation de performances — 14 novembre 2025 性能评估考试 — 2025 年 11 月 14 日

M2 CHPS · Durée : **2 h 30** 考试时长：**2 小时 30 分钟**

[Index des annales 历年试题索引](README.md) · [Sujet en français 法语原题](edp_examen_2025-11-14.md) · [Photographie, page 1 原图第 1 页](Images/edp_examen_2025-11-14_p01.png) · [Photographie, page 2 原图第 2 页](Images/edp_examen_2025-11-14_p02.png)

> Transcription du sujet photographié et traduction chinoise, sans corrigé. La présentation et les notations ont été harmonisées sans modifier les données ni les questions. Les consignes concernent uniquement cette épreuve historique. 根据试卷照片整理的法中对照版，不含解答。排版和符号已统一，数据与题目要求保持原意。考试规则仅对应这份历史试卷。法语在前、中文在后，同一行用空格隔开，撇号统一为 '。

## Consignes 考试规则

- Les calculatrices, les notes de cours et de TD sont autorisées mais sont strictement personnelles. 允许使用计算器、课程笔记和 TD 笔记，但必须为本人专用。
- Les ordinateurs et les téléphones sont interdits. 禁止使用电脑和手机。

## Exercice 1 — Réseau de files d'attente à quatre ressources 练习 1 — 四资源排队网络

*Questions 1 à 5 : page 1 ; questions 6 à 9 : page 2. 第 1–5 问对应原卷第 1 页，第 6–9 问对应原卷第 2 页。*

On considère un système en charge de traiter un flux de tâches arrivant à une fréquence $\lambda$ exprimée en $\mathrm{instr/s}$. Ce système contient quatre ressources numérotées de $R_1$ à $R_4$, avec des taux de service de $\mu_{R_1}$ à $\mu_{R_4}$ respectivement. On sait que : 考虑一个处理任务流的系统，任务以到达率 $\lambda$ 进入，单位为 $\mathrm{instr/s}$。系统包含 4 个资源，编号为 $R_1$ 至 $R_4$，对应的服务率分别为 $\mu_{R_1}$ 至 $\mu_{R_4}$。已知：

$$
\mu_{R_1}=400\ \mathrm{instr/s},\qquad
\mu_{R_2}=180\ \mathrm{instr/s},\qquad
\mu_{R_3}=550\ \mathrm{instr/s},\qquad
\mu_{R_4}=125\ \mathrm{instr/s}.
$$

Chacune de ces ressources est associée à une file d'attente. 每个资源都关联一个等待队列。

À l'entrée de ce système, la ressource $R_1$ reçoit les tâches à une fréquence $\lambda$ et les dirige vers les ressources de calcul $R_2$ et $R_3$ à hauteur de 30 % et 70 % respectivement. 在系统入口处，资源 $R_1$ 以到达率 $\lambda$ 接收任务，然后按 30% 和 70% 的比例，分别将任务送往计算资源 $R_2$ 和 $R_3$。

À la sortie de la ressource $R_2$, 80 % des instructions sont dirigées vers la ressource $R_4$ et les 20 % qui restent quittent le système. La ressource $R_3$ reçoit également en entrée toutes les instructions issues de la file associée à la ressource $R_4$. Après le passage par la file associée à $R_3$, toutes les instructions quittent le système. 从资源 $R_2$ 离开的指令中，80% 被送往资源 $R_4$，其余 20% 离开系统。资源 $R_3$ 还接收所有来自资源 $R_4$ 所关联队列的指令。指令经过 $R_3$ 所关联的队列后，全部离开系统。

### Questions 问题

1. Donnez le schéma en réseau de files d'attente correspondant au système décrit ci-dessus. Il faut mentionner sur votre schéma l'ensemble des ressources ainsi que la valeur de la fréquence des flux sur toutes les transitions (entrée, sortie, intermédiaires). 画出上述系统对应的排队网络图。图中必须标明所有资源，以及每一条转移路径上的流率，包括入口、出口和中间路径。

2. Quelle condition pose-t-on sur la fréquence d'arrivée externe $\lambda$ pour que le système global soit stable ? 为使整个系统稳定，外部到达率 $\lambda$ 需要满足什么条件？

3. Pour le reste des questions, on suppose que $\lambda$ est de $320\ \mathrm{instr/s}$. Le système est-il stable ? 后续各问均假设 $\lambda=320\ \mathrm{instr/s}$。系统是否稳定？

4. Quel est le temps d'attente moyen du système ? Identifiez la ressource qui est majoritairement à l'origine de cette attente. 系统的平均等待时间是多少？指出造成等待时间的主要资源。

5. Pour réduire l'attente dans cette ressource identifiée, on propose de la remplacer par une ressource ayant le même mode de fonctionnement mais avec un taux de service doublé. 为减少在上述资源处的等待时间，拟将其替换为工作方式相同、但服务率加倍的资源。

   (a) Le système reste-t-il stable ? 系统是否仍然稳定？

   (b) Quel est le nouveau temps moyen d'attente au niveau de cette ressource, et celui du système global ? 该资源处新的平均等待时间是多少？整个系统新的平均等待时间是多少？

6. Quel est le temps de service moyen (après changement de la ressource identifiée dans la question précédente) ? Identifiez la ressource qui est majoritairement à l'origine de ce temps. 更换上一问确定的资源后，平均服务时间是多少？指出对这一时间贡献最大的资源。

7. Pour réduire le temps de service de cette ressource identifiée, on la remplace par une autre qui effectue le même service mais trois fois plus vite. 为减少上述资源的服务时间，将其替换为执行相同服务、但速度提高到原来 3 倍的另一资源。

   (a) Quel est le nouveau taux de service de cette nouvelle ressource ? 新资源的服务率是多少？

   (b) Quel est le nouveau temps de service moyen du système global ? 整个系统新的平均服务时间是多少？

8. Après ces deux remplacements, quel est le temps de réponse moyen du système global ? Quelle est l'accélération obtenue par rapport à la version initiale (avant les deux changements) ? 完成这两次替换后，整个系统的平均响应时间是多少？与初始版本（两次更换之前）相比，加速比是多少？

9. Sachant que les deux changements ont augmenté le coût du système global de 0,75 fois sa valeur initiale, est-ce que vous pensez que cet investissement est efficace ? Justifiez votre réponse. 已知这两次更换使整个系统的成本增加了初始成本的 0.75 倍。你认为这项投资是否有效？请说明理由。

## Exercice 2 — Gustafson–Barsis 练习 2 — Gustafson–Barsis 定律

*Page 2 du sujet. 对应原卷第 2 页。*

La métrique de Gustafson–Barsis sert à calculer la capacité d'exécuter un code plus grand dans la même durée d'exécution que le problème initial en utilisant plus de processeurs. Ici, c'est le cas d'un passage du séquentiel (un processeur) à $P$ processeurs ($P>1$) d'un code dont la fraction séquentielle est $seq$. Ce passage s'accompagne d'une accélération de mise à l'échelle (*scaled speedup*), telle que : Gustafson–Barsis 指标用于衡量：使用更多处理器，在与初始问题相同的执行时间内，能够运行多大规模的程序。这里考虑将一个顺序部分比例为 $seq$ 的程序，从顺序执行（1 个处理器）扩展到 $P$ 个处理器（$P>1$）。这一扩展对应的规模扩展加速比为：

$$
Acc(\mathrm{scaled})\leq P+(1-P)\times seq.
$$

> **Note de transcription :** la photographie utilise $P$ dans le paragraphe et $p$ dans la formule. La transcription uniformise cette notation en $P$ et conserve le signe $\leq$ de l'original. **转录校注：**原图正文用大写 $P$ 表示处理器数，公式中改用小写 $p$；此处统一为大写 $P$，保留原图中的 $\leq$。

### Questions 问题

1. Quelle est l'accélération selon Gustafson–Barsis (*scaled speedup*) pour une application s'exécutant sur huit processeurs et qui passe 14 % de son temps à exécuter sa partie séquentielle ? 某应用在 8 个处理器上运行，执行顺序部分的时间占总执行时间的 14%。根据 Gustafson–Barsis 定律，其规模扩展加速比是多少？

2. Quelle est la fraction séquentielle maximale que l'on puisse tolérer pour garder au moins la même accélération (*scaled speedup*) quand le nombre de processeurs passe à dix ? 当处理器数量增加到 10 时，为使规模扩展加速比至少保持与上一问相同的水平，顺序部分的比例最大可以是多少？

## Exercice 3 — Uniformité d'un générateur aléatoire 练习 3 — 随机数生成器的均匀性

*Page 2 du sujet. 对应原卷第 2 页。*

On utilise un générateur de nombres aléatoires uniformément distribués entre 0 et 1 pour générer des traces synthétiques et on souhaite vérifier son uniformité à travers l'échantillon ci-dessous, de taille 20, au seuil de risque de 5 %. 使用一个在 0 到 1 之间生成均匀分布随机数的生成器来生成合成轨迹。现希望利用以下容量为 20 的样本，在 5% 的显著性水平下检验其均匀性。

```text
0.12, 0.45, 0.67, 0.23, 0.89, 0.34, 0.56, 0.78, 0.01, 0.99,
0.41, 0.62, 0.15, 0.73, 0.27, 0.51, 0.84, 0.39, 0.60, 0.95
```

### Questions 问题

1. Poser les hypothèses à tester. 提出待检验的统计假设。

2. Effectuer la comparaison de la distribution observée à celle théorique en utilisant le test de Kolmogorov–Smirnov au seuil de risque $\alpha=0.05$. Que déduisez-vous ? 在显著性水平 $\alpha=0.05$ 下，使用 Kolmogorov–Smirnov 检验比较观测分布与理论分布。可以得出什么结论？

3. En découpant l'intervalle $[0,1]$ en cinq classes $[0,0.2[$, $[0.2,0.4[$, $[0.4,0.6[$, $[0.6,0.8[$ et $[0.8,1]$, effectuer la comparaison de la distribution observée à celle théorique en utilisant le test du Khi-deux au seuil de risque $\alpha=0.05$. Que déduisez-vous ? 将区间 $[0,1]$ 划分为 5 组：$[0,0.2)$、$[0.2,0.4)$、$[0.4,0.6)$、$[0.6,0.8)$ 和 $[0.8,1]$。在显著性水平 $\alpha=0.05$ 下，使用 χ²（卡方）检验比较观测分布与理论分布。可以得出什么结论？

4. Peut-on confirmer l'uniformité du générateur ? Au seuil de risque de 5 %, justifiez votre réponse. 能否确认该生成器具有均匀性？请在 5% 的显著性水平下说明理由。
