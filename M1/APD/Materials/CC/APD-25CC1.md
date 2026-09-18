# Évaluation en Système Distribué 分布式系统考核

*Durée : 2h30.* 考试时长：2小时30分。
*Aucun document autorisé.* 不允许使用任何资料。
*Le barème est donné à titre indicatif.* 分值仅供参考。

## Exercice 1. Causalité (5 points) 练习1：因果关系（5分）

Soient les événements suivants constituant l'exécution \((S)\) d'un système distribué : 设以下事件构成一个分布式系统的执行 \((S)\)：

$$
\begin{array}{lll}
e_1 = Envoi(1,2) & e_2 = Interne(3) & e_3 = Reception(2,1) \\
e_4 = Envoi(4,1) & e_5 = Envoi(4,3) & e_6 = Envoi(3,1) \\
e_7 = Interne(1) & e_8 = Envoi(3,2) & e_9 = Reception(1,3) \\
e_{10} = Interne(4) & e_{11} = Reception(1,4) & e_{12} = Reception(3,4) \\
e_{13} = Reception(2,3) & e_{14} = Interne(2) & e_{15} = Envoi(2,4) \\
e_{16} = Interne(4) & e_{17} = Reception(4,2) &
\end{array}
$$

avec \(Envoi(i,j)\) un envoi de \(i\) vers \(j\) et \(Reception(i,j)\) une réception sur \(i\) d'un message de \(j\). 其中，\(Envoi(i,j)\) 表示从 \(i\) 向 \(j\) 发送消息，\(Reception(i,j)\) 表示在 \(i\) 处接收来自 \(j\) 的消息。

1. Tracer le diagramme espace temps correspondant à l'exécution. 画出与该执行对应的时空图。
   Dans le diagramme, vous positionnerez \(P_1\) en haut et \(P_4\) en bas (1pt). 在图中，将 \(P_1\) 放在最上方，\(P_4\) 放在最下方（1分）。
2. Donner l'horloge vectorielle et l'horloge de Lamport des événements \(e_2\), \(e_{11}\), \(e_{12}\) et \(e_{17}\) (2pt). 给出事件 \(e_2\)、\(e_{11}\)、\(e_{12}\) 和 \(e_{17}\) 的向量时钟与 Lamport 时钟（2分）。
3. On rappelle qu'une exécution équivalente est une exécution qui : 回顾定义：等价执行是指满足以下条件的执行：
   (a) contient les mêmes événements que ceux présents dans l'exécution initiale et (a) 包含与初始执行相同的事件；
   (b) ces événements apparaissent dans un ordre global différent, mais tel que ce nouvel ordre global respecte toutes les relations de précédence induites par l'exécution initiale. (b) 这些事件在全局上按不同顺序出现，但该新全局顺序仍满足初始执行所诱导的所有先后关系。

   Donner une exécution équivalente à \(S\) dans laquelle il n'y a pas deux messages en transit au même instant. 给出一个与 \(S\) 等价的执行，使得任意时刻都不存在两个消息同时在传输中。
   Si c'est possible, donner une telle exécution, sinon expliquez pourquoi cela est impossible (1pt). 如果可以，请给出该执行；如果不可以，请解释为什么不可能（1分）。
4. Les événements \(e_1\) et \(e_{17}\) sont-ils liés causalement ? 事件 \(e_1\) 和 \(e_{17}\) 是否具有因果关系？
   Et si oui, comment ? 如果有，它们是如何因果关联的？
   Justifiez en utilisant les valeurs des horloges (1pt). 请用时钟值进行论证（1分）。

## Exercice 2. Algorithme de Ricart-Agrawala (4 points) 练习2：Ricart-Agrawala 算法（4分）

On considère l'algorithme d'exclusion mutuelle de Ricart-Agrawala (cf. algorithme 1 fourni en annexe) sur un graphe complet de 5 sites, numérotés 1, 2, 3, 4, 5. 考虑在一个由 5 个站点（编号 1、2、3、4、5）构成的完全图上运行 Ricart-Agrawala 互斥算法（见附件算法1）。

On considère la configuration \(C_0\) suivante : 考虑如下初始配置 \(C_0\)：

- tout site \(i\) est tel que : \(etat_i = S\), \(attendu_i = \emptyset\) et \(differe_i = \emptyset\) ; 每个站点 \(i\) 都满足：\(etat_i = S\)、\(attendu_i = \emptyset\)、\(differe_i = \emptyset\)；
- les valeurs des horloges sont : \(h_1 = 4\) ; \(h_2 = 3\) ; \(h_3 = 3\) ; \(h_4 = 3\) ; \(h_5 = 3\). 时钟值为：\(h_1 = 4\)、\(h_2 = 3\)、\(h_3 = 3\)、\(h_4 = 3\)、\(h_5 = 3\)。
- aucun message n'est en transit dans les canaux de communication. 通信信道中没有在途消息。

À partir de cette configuration \(C_0\), on suppose que les sites 1 et 2 demandent simultanément à entrer en section critique. 从该配置 \(C_0\) 出发，假设站点 1 和站点 2 同时请求进入临界区。
On entend par simultanément le fait que les deux sites exécutent en même temps le code de la règle "Sur demande d'entrée en SC". 这里“同时”指两个站点在同一时刻执行规则“请求进入临界区时”的代码。

1. Dire qui de 1 ou de 2 entre en premier en section critique. 说明 1 和 2 中谁先进入临界区。
   Justifier brièvement (1pt). 请简要说明理由（1分）。

    Dans les deux questions suivantes, on considère la configuration \(C_1\) qui correspond au moment où les deux sites 1 et 2 sont sortis de section critique. 在接下来的两个问题中，考虑配置 \(C_1\)，即站点 1 和站点 2 都已经离开临界区的时刻。

2. Donner la valeur des variables \(h_i\) pour tous les sites du système, dans la configuration \(C_1\) (1pt). 给出配置 \(C_1\) 中系统所有站点的变量 \(h_i\) 的值（1分）。
3. Indiquer combien de messages ont été échangés dans l'exécution qui mène de \(C_0\) à \(C_1\) (1pt). 指出从 \(C_0\) 到 \(C_1\) 的执行过程中交换了多少条消息（1分）。

## Exercice 3. Algorithme de diffusion (3 points) 练习3：扩散算法（3分）

Écrire un algorithme qui trouve le noeud d'identifiant maximal dans un anneau orienté. 写一个算法，在有向环中找到标识符最大的节点。
À la fin de l'algorithme, tous les noeuds doivent connaître cet identifiant. 算法结束时，所有节点都必须知道这个标识符。

## Exercice 4. Algorithme d'exclusion mutuelle (3 points) 练习4：互斥算法（3分）

Écrire un algorithme qui effectue une exclusion mutuelle dans un graphe anneau. 写一个在环形图中实现互斥的算法。

## Exercice 5. Compter dans un arbre (BONUS) 练习5：在树中计数（附加题）

On considère un arbre orienté (un site distingue son père de ses fils). 考虑一棵有向树（每个站点能够区分其父节点和子节点）。
On suppose un système asynchrone dans lequel les initiateurs sont les feuilles de l'arbre. 假设系统是异步的，并且发起者是树的叶子节点。
On souhaite calculer des informations relatives à cet arbre. 我们希望计算与这棵树相关的信息。

1. Écrire un algorithme distribué tel que, à la fin de l'exécution, la racine de l'arbre connaît le nombre de noeuds bizarres dans l'arbre. 写一个分布式算法，使得在执行结束时，树根知道树中“奇怪节点”的数量。
   Un noeud est bizarre s'il a exactement un nombre pair de fils. 当且仅当一个节点的子节点数恰好为偶数时，该节点称为“奇怪节点”。
   Vous indiquerez le mode de terminaison en indiquant la (ou les) action(s) `STOP_LOCAL` et/ou `STOP_GLOBAL` (5pts). 请说明终止方式，并给出 `STOP_LOCAL` 和/或 `STOP_GLOBAL` 动作（5分）。
2. Donner la complexité en messages et en temps (synchrone). 给出消息复杂度和时间复杂度（同步时间模型）。
   Justifier (2pts). 并进行说明（2分）。

## Exercice 6. QCM (5 points. Attention une réponse fausse entraîne une perte d'un demi point.) 练习6：选择题（5分。注意：答错一题扣0.5分。）

On suppose que les graphes dans les questions ont \(n\) noeuds et \(m\) arêtes. 假设题目中的图都有 \(n\) 个节点和 \(m\) 条边。

1. Un graphe arbre peut avoir au plus : 一棵树图最多可以有：

   (a) 0 cycles. (a) 0 个环。
   (b) 1 cycle. (b) 1 个环。
   (c) \(n-1\) cycles. (c) \(n-1\) 个环。
   (d) \(n\) cycles. (d) \(n\) 个环。

2. Un graphe clique a : 一个团图（完全图）有：

   (a) \(n\) arêtes. (a) \(n\) 条边。
   (b) \(n-1\) arêtes. (b) \(n-1\) 条边。
   (c) \(n*n\) arêtes. (c) \(n*n\) 条边。
   (d) \(n*(n-1)/2\) arêtes. (d) \(n*(n-1)/2\) 条边。

    Soit \(\Delta\) le degré maximal d'un graphe. 设 \(\Delta\) 为图的最大度数。

3. La complexité de l'algorithme de Ricart-Agrawala est asymptotiquement : Ricart-Agrawala 算法的渐近复杂度是：

   (a) \(\Delta*(\text{nombre de demandes})\). (a) \(\Delta*(\text{请求次数})\)。
   (b) \(n*(\text{nombre de demandes})\). (b) \(n*(\text{请求次数})\)。
   (c) \(\Delta*n\). (c) \(\Delta*n\)。
   (d) \(\Delta*m\). (d) \(\Delta*m\)。

4. Il est possible d'écrire un algorithme d'élection de leader fonctionnant sur n'importe quel type de réseau. 可以写出一个在任意类型网络上都能工作的领导者选举算法。

   (a) Vrai. (a) 对。
   (b) Faux. (b) 错。

5. L'algorithme de Ricart-Agrawala fonctionne si les canaux de communications ne sont pas FIFO : 如果通信信道不是 FIFO，Ricart-Agrawala 算法仍然可以工作：

   (a) Vrai. (a) 对。
   (b) Faux. (b) 错。

6. Dans notre modèle algorithmique, les variables de connaissance sont accédées par les noeuds : 在我们的算法模型中，知识变量被节点以如下方式访问：

   (a) En écriture. (a) 只写。
   (b) En lecture. (b) 只读。
   (c) En lecture et en écriture. (c) 读写。

7. Dans notre modèle algorithmique, lorsqu'un noeud effectue un STOP-GLOBAL, cela signifie : 在我们的算法模型中，当某个节点执行 STOP-GLOBAL 时，意味着：

   (a) il a terminé d'exécuter le code mais d'autres noeuds non. (a) 它已执行完代码，但其他节点还没有。
   (b) tous les noeuds ont terminé d'exécuter le code mais des messages peuvent être en transit. (b) 所有节点都已执行完代码，但仍可能有在途消息。
   (c) tous les noeuds ont terminé d'exécuter le code et il n'y a pas de messages en transit. (c) 所有节点都已执行完代码，且没有在途消息。
