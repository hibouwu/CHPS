# Algorithmique distribuée et parallèle 分布式与并行算法

*Durée : 2h.* 考试时长：2小时。  
*Documents non autorisés.* 不允许使用资料。  
*L'algorithme de Ricart Agrawala est fourni en annexe.* Ricart-Agrawala 算法见附录。

## Exercice 1. 练习1

1. Dans un graphe non connexe simple sans boucle, combien de valeurs différentes peuvent avoir les degrés des sommets :  
   在一个无自环的简单非连通图中，顶点的度数最多可以取多少种不同的值：

   a. $n$  
   b. $n-1$  
   c. $n-2$  
   d. $n*(n-1)/2$

2. Quel est le degré maximal et minimal d'un sommet dans un arbre quelconque ?  
   在任意一棵树中，一个顶点的最大度和最小度分别是多少？

3. Dessiner un arbre avec $n$ sommets et qui a pour hauteur $n/2$.  
   画出一棵有 $n$ 个顶点且高度为 $n/2$ 的树。

4. Soit $G$ un graphe complet. Chaque sommet se voit attribuer une couleur. Combien de couleurs faut-il pour que deux sommets voisins n'aient pas la même couleur ? Qu'en est-il pour un arbre ?  
   设 $G$ 是一个完全图。每个顶点被赋予一种颜色。为了使任意两个相邻顶点颜色不同，需要多少种颜色？对于树又是多少？

5. La plus grande clique dans un arbre (cad le plus grand sous-graphe de l'arbre qui est un graphe complet) est de taille :  
   在一棵树中，最大的团（即树中最大的完全子图）的大小是：

   a. 1  
   b. 2  
   c. 3  
   d. $n-1$

6. Un graphe $G$ n'a que des sommets de degré impair. il a :  
   一个图 $G$ 的所有顶点度数都为奇数。那么它的顶点数：

   a. 10212211148 sommets  
   b. 4112334441 sommets

7. Combien d'arêtes a un graphe clique ?  
   一个团图（完全图）有多少条边？

8. L'algorithme de Ricart Agrawala fonctionne sur un graphe quelconque ?  
   Ricart-Agrawala 算法是否能在任意图上运行？

Soit $\Delta$ le degré maximal d'un graphe.  
设 $\Delta$ 为图的最大度数。

9. La complexité de l'algorithme de Ricart Agrawala est asymptotiquement :  
   Ricart-Agrawala 算法的渐近复杂度是：

   a. $\Delta * (\text{nombre de demandes})$  
   b. $n * (\text{nombre de demandes})$  
   c. $\Delta * n$  
   d. $\Delta * m$

10. Il est possible d'écrire un algorithme d'élection de leader fonctionnant sur n'importe quel type de réseau ?  
    是否存在一种领导者选举算法，可以在任意类型的网络上运行？

11. L'algorithme de Ricart Agrawala fonctionne si les canaux de communications ne sont pas FIFO ?  
    如果通信信道不是 FIFO，Ricart-Agrawala 算法还能正常工作吗？

12. Dans notre modèle algorithmique, les variables de connaissance sont accédées par les noeuds :  
    在我们的算法模型中，知识变量被节点以何种方式访问：

    1. En écriture. 只写。  
    2. En lecture. 只读。  
    3. En lecture et en écriture. 读写。

13. Dans notre modèle algorithmique, lorsqu'un noeud effectue un STOP-GLOBAL, cela signifie :  
    在我们的算法模型中，当某个节点执行 `STOP-GLOBAL` 时，这意味着：

    1. il a terminé d'exécuter le code mais d'autres noeuds non.  
       它已经执行完代码，但其他节点还没有。

    2. tous les noeuds ont terminé d'exécuter le code mais des messages peuvent être en transit.  
       所有节点都执行完了代码，但仍可能有消息在传输途中。

    3. tous les noeuds ont terminé d'exécuter le code et il n'y a pas de messages en transit.  
       所有节点都执行完了代码，并且没有在途消息。

## Exercice 2. 练习2

On considère l'algorithme d'exclusion mutuelle de Ricart-Agrawala (cf. algorithme fourni en annexe) sur un graphe de 5 sites, numérotés 1, 2, 3, 4, 5.  
考虑在一个由 5 个站点组成的图上运行 Ricart-Agrawala 互斥算法（参见附录中的算法），站点编号为 1、2、3、4、5。

On considère la configuration $C0$ suivante :  
考虑如下配置 $C0$：

- tout site $i$ est tel que : $etat_i = S$, $attendu_i = \varnothing$ et $differe_i = \varnothing$ ;  
  对每个站点 $i$，都有：$etat_i = S$、$attendu_i = \varnothing$、$differe_i = \varnothing$；
- les valeurs des horloges sont : $h_1 = 4$ ; $h_2 = 3$ ; $h_3 = 3$ ; $h_4 = 3$ ; $h_5 = 3$ ;  
  时钟值为：$h_1 = 4$、$h_2 = 3$、$h_3 = 3$、$h_4 = 3$、$h_5 = 3$；
- aucun message n'est en transit dans les canaux de communication.  
  通信信道中没有在途消息。

À partir de cette configuration $C0$, on suppose que les sites 1 et 2 demandent simultanément à entrer en section critique. On entend par simultanément le fait que les deux sites exécutent en même temps le code de la règle "Sur demande d'entrée en SC".  
从该配置 $C0$ 出发，假设站点 1 和站点 2 同时请求进入临界区。这里“同时”指两个站点在同一时刻执行规则“请求进入临界区时”的代码。

1. Rappeler les deux propriétés fondamentales que doit vérifier un algorithme correct d'exclusion mutuelle.  
   回答一个正确的互斥算法必须满足的两个基本性质。

2. Dire qui de 1 ou de 2 entre en premier en section critique. Justifier brièvement.  
   说明 1 和 2 中谁先进入临界区，并简要说明理由。

3. Dans les deux questions suivantes, on considère la configuration $C1$ qui correspond au moment où les deux sites 1 et 2 sont sortis de section critique.  
   在接下来的两个问题中，考虑配置 $C1$，即站点 1 和站点 2 都已经离开临界区的时刻。

4. Donner la valeur des variables $h_i$ pour les sites du système, dans la configuration $C1$.  
   给出配置 $C1$ 中系统各站点变量 $h_i$ 的值。

5. Indiquer combien de messages ont été échangés dans l'exécution qui mène de $C0$ à $C1$.  
   指出从 $C0$ 到 $C1$ 的执行过程中一共交换了多少条消息。

## Exercice 3. 练习3

1. Ecrire un algorithme qui effectue l'exclusion mutuelle dans un graphe en anneau.  
   写一个在环形图中实现互斥的算法。

2. Ecrire un algorithme dans un arbre tel que la racine connaisse le nombre de noeuds à la fin de son exécution. Donnez sa complexité en message.  
   在一棵树上写一个算法，使得根节点在算法结束时知道树中的节点总数。给出它的消息复杂度。

## Annexe 附录

### Algorithme 1. Algorithme de Ricart Agrawala, local au site $i$ 算法1：Ricart-Agrawala 算法，站点 $i$ 的局部算法

#### Variables 变量

```text
etat_i     ∈ {E, SC, S}, initialisé à S
etat_i     ∈ {请求中, 临界区, 空闲}，初始化为 S

h_i        : entier initialisé à 0. C'est l'horloge logique de i
h_i        : 整数，初始化为 0。这是 i 的逻辑时钟

last_i     : entier initialisé à 0. C'est la date de la dernière demande d'entrée en SC de i
last_i     : 整数，初始化为 0。这是 i 上一次请求进入临界区的时间戳

differe_i  : ens. des sites dont l'envoi de la permission est retardé. Initialisé à ∅
differe_i  : 集合，表示被延迟发送许可的站点。初始化为 ∅

attendu_i  : ens. des sites dont i attend la permission. Initialisé à ∅
attendu_i  : 集合，表示 i 正在等待其许可的站点。初始化为 ∅

priorite_i : booléen qui est à vrai si i est prioritaire par rapport à la demande en cours
             de traitement. Initialisé à faux
priorite_i : 布尔值；若 i 相对于当前处理的请求具有优先权，则为真。
             初始化为 faux（假）
```

#### Algorithme 算法

**Sur demande d'entrée en section critique** :  
**当请求进入临界区时**：

```text
etat_i <- E
last_i <- h_i + 1
attendu_i <- tous les sites sauf i
for all j ∈ attendu_i do
    Envoyer Dem(last_i, i) à j
```

**Sur réception de** `Dem(h', j)` **de** $j$ :  
**当从** $j$ **接收到** `Dem(h', j)` **时**：

```text
h_i <- max(h_i, h')
priorite_i <- (etat_i = SC) ∨ ((etat_i = E) ∧ ((last_i, i) < (h', j)))
if priorite_i = vrai then
    differe_i <- differe_i ∪ {j}
else
    Envoyer Perm à j
```

**Sur réception de** `Perm` **de** $j$ :  
**当从** $j$ **接收到** `Perm` **时**：

```text
attendu_i <- attendu_i \ {j}
if attendu_i = ∅ then
    etat_i <- SC
```

**Sur sortie de section critique** :  
**当离开临界区时**：

```text
etat_i <- S
for all j ∈ differe_i do
    Envoyer Perm à j
differe_i <- ∅
```
