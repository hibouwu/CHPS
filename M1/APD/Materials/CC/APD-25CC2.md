# APD-25CC2

*Durée : 2h30.* 考试时长：2小时30分。  
*Aucun document autorisé.* 不允许使用任何资料。

Il est impératif de répondre **précisément** aux questions et de **justifier** vos réponses.  
必须**准确**回答问题，并且**论证**你的答案。

## Exercice 1. (6 points) 练习1（6分）

1. Donner un algorithme distribué utilisant un parcours et qui permet à un initiateur unique de déterminer le nombre de sites ayant un nombre impair de voisins dans le système. A la fin de l'exécution, l'initiateur doit connaître ce nombre. Pour cet exercice, vous pouvez utiliser l'algorithme du parcours ci dessous, vu en cours.  
   给出一个使用遍历过程的分布式算法，使唯一的发起者能够确定系统中邻居数量为奇数的站点个数。执行结束时，发起者必须知道这个数量。对于本题，你可以使用下面课上见过的遍历算法。

   **Corr** : On reprend l'algorithme de parcours et l'on fait remonter un compteur au moment du retour vers le père. Chaque site $i$ calcule d'abord une contribution locale valant $1$ si $|vois_i|$ est impair, et $0$ sinon. Ensuite, quand tous les retours de ses fils ont été reçus, il additionne sa contribution locale et les contributions remontées par ses fils, puis renvoie le total à son père. À la fin, l'initiateur obtient le nombre total de sites de degré impair.  
   **答案。** 直接在遍历算法的回传阶段顺便统计即可。每个站点 $i$ 先计算一个本地贡献：如果 $|vois_i|$ 是奇数，则贡献为 $1$，否则为 $0$。然后当它收齐所有子节点的回传后，把这些值与自己的本地贡献相加，再把和回传给父节点。最终发起者得到的总和就是图中邻居数为奇数的节点个数。

   ```pseudo
   **Algorithm 0** Parcours par circulation de jeton avec comptage, local au site $i$

   **Connaissance**
   $vois_i$ : ensemble des voisins du site $i$.

   **Variables**
   $pere_i$ : identifiant de site, initialisé à $ndef$.
   $utilise_i[j]$ : booléen pour chaque voisin $j \in vois_i$, initialisé à $Faux$.
   $cpt_i$ : compteur local, initialisé à $1$ si $|vois_i|$ est impair, sinon à $0$.

   **Messages**
   $Jeton(v)$ : avec $v = 0$ pendant l'aller, et $v \ge 1$ pendant le retour.

   **Algorithme**
   **Initialement** ->  /* Sur un seul initiateur */
     $pere_i$ <- $i$
     Choisir $j \in vois_i$
     $utilise_i[j]$ <- $Vrai$
     Envoyer $Jeton(0)$ à $j$

   **Sur réception de** $Jeton(v)$ **de** $j_0$ ->
     **if** $pere_i = ndef$ **then**
       $pere_i$ <- $j_0$
     **else if** $v \ge 1$ **then**
       $cpt_i$ <- $cpt_i + v$

     **if** $\exists j \in vois_i \setminus \{pere_i\}$ tel que $\neg utilise_i[j]$ **then**
       Choisir $j \in vois_i \setminus \{pere_i\}$ tel que $\neg utilise_i[j]$
       $utilise_i[j]$ <- $Vrai$
       Envoyer $Jeton(0)$ à $j$
     **else**
       **if** $i = pere_i$ **then**
         **STOP_GLOBAL**
       **else**
         Envoyer $Jeton(cpt_i)$ à $pere_i$
   ```

### Algorithme 1. Algorithme de parcours, local au site $i$ 算法1：遍历算法，站点 $i$ 的局部算法

```pseudo
**Algorithm 1** Algorithme de parcours, local au site $i$

**Connaissance**
$vois_i$ : ensemble des voisins du site $i$.

**Variables**
$pere_i$ : identifiant de site, initialisé à $ndef$.
$utilise_i$ : tableau de booléens, indicé par l'identifiant des voisins, initialisé à $Faux$.

**Algorithme**
**Initialement** ->
  $pere_i$ <- $i$
  Choisir $j_0 \in vois_i$
  $utilise_i[j_0]$ <- $Vrai$
  Envoyer $Jeton()$ à $j_0$

**Sur réception de** $Jeton()$ **de** $j_0$ ->
  **if** $pere_i = ndef$ **then**
    $pere_i$ <- $j_0$

  **if** $\forall j \in vois_i, utilise_i[j] = Vrai$ **then**
    **STOP_GLOBAL**
  **else**
    **if** $\exists j \in vois_i, j \neq pere_i \land \neg utilise_i[j]$ **then**
      Choisir $j \in vois_i \setminus \{pere_i\}$ tel que $\neg utilise_i[j]$
      $utilise_i[j]$ <- $Vrai$
      Envoyer $Jeton()$ à $j$
  **else**
    $utilise_i[pere_i]$ <- $Vrai$
    Envoyer $Jeton()$ à $pere_i$
```

## Exercice 2. Élection dans un anneau (7 points) 练习2：环中的选举（7分）

On considère un anneau bidirectionnel avec $n \ge 3$ sites. Le réseau est asynchrone et chaque site a un identifiant unique. L'anneau est orienté, donc chaque site connaît parmi ses deux liens incidents, lequel va à gauche et lequel va vers la droite. On va utiliser un algorithme appelé « ALTERNER » pour résoudre le problème de l'élection : Tous les sites sont initiateurs. De plus, au départ, tous les sites sont des *candidats*. L'algorithme fonctionne en plusieurs étapes :  

考虑一个具有 $n \ge 3$ 个站点的双向环。网络是异步的，并且每个站点都有唯一标识符。该环是定向的，因此每个站点都知道它两条关联链路中哪一条通向左边、哪一条通向右边。我们使用一个名为“ALTERNER”的算法来解决选举问题：所有站点都是发起者。此外，开始时所有站点都是*候选者*。该算法分多个阶段运行：

Dans les étapes impaires (1, 3, 5, ...) chaque candidat envoie son identifiant vers la gauche. 在奇数阶段（1、3、5、……）中，每个候选者把自己的标识符发送到左边。

Dans les étapes paires (2, 4, 6, ...) chaque candidat envoie son identifiant vers la droite. 在偶数阶段（2、4、6、……）中，每个候选者把自己的标识符发送到右边。

Après chaque étape, un *candidat* compare son identifiant avec celui qu'il a reçu et, si son identifiant est plus grand, il devient *passif*. Un site passif n'est plus candidat pour la prochaine étape, ni pour les étapes suivantes. Il n'enverra donc plus son propre identifiant. Pendant le reste de l'algorithme, si un site passif reçoit un message, il le renvoie dans la direction opposée de celle par laquelle il l'a reçu. Quand un *candidat* reçoit son propre identifiant, il devient *élu*. Le pseudocode de l'algorithme est l'algorithme 2 donné ci-dessous.  
每个阶段结束后，一个*候选者*会将自己的标识符与收到的标识符进行比较；如果它自己的标识符更大，它就变成*被动者*。一个被动站点在下一阶段以及之后的所有阶段都不再是候选者，因此也不再发送自己的标识符。在算法剩余的执行过程中，如果一个被动站点收到消息，它会把该消息沿着与接收方向相反的方向转发出去。当一个*候选者*收到自己的标识符时，它就成为*当选者*。该算法的伪代码如下方算法2所示。

### Algorithme 2. Algorithme ALTERNER, local au site $i$ 算法2：ALTERNER 算法，站点 $i$ 的局部算法

```pseudo
**Algorithm 2** Algorithme ALTERNER, local au site $i$

**Connaissance**
$droite_i$, $gauche_i$ : les deux voisins de $i$.

**Variables**
$etat_i \in \{candidat, passif, elu\}$, initialisé à $candidat$.
$etape_i$ : entier initialisé à $1$.

**Algorithme**
**Initialement** ->
  Envoyer $Msg(i)$ à $gauche_i$

**Sur réception de** $Msg(id)$ **de** $j$ ->
  **if** $etat_i = passif$ **then**
    Envoyer $Msg(id)$ à $\{droite_i, gauche_i\} \setminus \{j\}$
  **else if** $etat_i = candidat$ **then**
    **if** $i > id$ **then**
      $etat_i$ <- *passif*
    **else if** $i = id$ **then**
      $etat_i$ <- *elu*
    **else**
      $etape_i$ <- $etape_i + 1$
      **if** $etape_i$ est pair **then**
        Envoyer $Msg(i)$ à $droite_i$
      **else**
        Envoyer $Msg(i)$ à $gauche_i$
```

1. Qui est élu ? Donner la complexité de l'algorithme ALTERNER en termes de nombre de messages transmis, dans le pire des cas. Expliquer votre réponse.  
   谁会当选？给出 ALTERNER 算法在最坏情况下按传输消息数衡量的复杂度，并说明理由。

   **Corr** : Le site élu est celui d'identifiant minimal. En effet, lorsqu'un candidat reçoit un identifiant plus petit que le sien, il devient passif ; ainsi, tout identifiant strictement plus grand que le minimum finit par être éliminé. Le seul identifiant qui ne peut jamais être éliminé est donc le plus petit, et lorsque son propre message lui revient, ce site devient élu.  
   **答案。** 当选的是最小标识符对应的站点。因为一个候选者一旦收到比自己更小的标识符，就会变成被动者；因此所有严格大于最小值的标识符最终都会被淘汰。唯一不可能被淘汰的就是最小标识符，对应站点在收到自己的消息时宣布当选。

   Dans le pire cas, la complexité en messages est $\Theta(n \log n)$. En effet, si l'on considère les candidats présents au début d'une étape, chacun émet exactement un message, qui traverse les sites passifs jusqu'au prochain candidat dans la direction considérée. Les trajets de ces messages forment alors une partition de l'anneau ; le nombre total de transmissions pendant une étape est donc exactement $n$. De plus, après deux étapes consécutives, le nombre de candidats restants est au plus divisé par $2$ : après une étape, les survivants sont des minima locaux dans une direction, et après l'étape suivante dans la direction opposée, deux survivants consécutifs ne peuvent pas rester tous les deux candidats. Le nombre total d'étapes est donc logarithmique, ce qui donne une borne supérieure $O(n \log n)$ sur le nombre de messages. Cette borne est atteinte pour certaines configurations ; dans le pire cas, la complexité en messages est donc bien $\Theta(n \log n)$.  
   在最坏情况下，消息复杂度是 $\Theta(n\log n)$。原因是：固定看某一阶段开始时仍为候选者的节点，每个候选者恰好发送 1 条消息；这条消息会沿该阶段规定的方向穿过一串被动节点，直到第一次到达下一位候选者。所有这些路径正好把整个环分割完，所以每个阶段的总传输次数恰好是 `n`。另外，每经过连续两阶段，剩余候选者数至多变为原来的一半：一阶段后幸存者是在该方向上的局部最小，下一阶段改向后，相邻两个幸存者不可能同时继续存活。因此总阶段数是对数量级，从而先得到消息数上界 $O(n\log n)$。而某些构造确实可以达到这个量级，所以最坏情况下消息复杂度就是 $\Theta(n\log n)$。

2. Pour cet algorithme, donner un exemple d'un anneau (avec 16 sites et leurs identifiants), dans lequel l'algorithme a la pire complexité (en termes de nombre de messages transmis).  
   对于这个算法，请给出一个环的例子（包含16个站点及其标识符），使得该算法达到最坏复杂度（按传输消息数衡量）。

   **Corr** : Un exemple classique, facile à reconstruire, qui atteint l'ordre de grandeur du pire cas pour 16 sites est le suivant :
   $$
   (1,9,5,13,3,11,7,15,2,10,6,14,4,12,8,16).
   $$
   Cet anneau est obtenu récursivement en intercalant d'abord les identifiants impairs, puis les identifiants pairs, tout en conservant à l'intérieur de chaque moitié la même structure. Cette disposition fait diminuer le nombre de candidats suffisamment lentement pour obtenir un nombre logarithmique d'étapes. Comme chaque étape transmet exactement 16 messages, on obtient un nombre total de transmissions en $\Theta(16 \log 16)$, ce qui correspond au pire ordre de grandeur.  
   **答案。** 一个经典、而且考试时可以按规律重新构造出来的 16 点坏例子是：
   $$
   (1,9,5,13,3,11,7,15,2,10,6,14,4,12,8,16).
   $$
   这个排列可以递归理解为：先放所有奇数，再放所有偶数，并且两半内部继续保持同样的交错结构。对这个环，候选者会以足够慢的速度减少，因此算法会运行对数量级的阶段数；而每个阶段都恰好传输 16 条消息，所以总消息数属于 $\Theta(16\log 16)$，这正是最坏复杂度的量级。

3. Considérons un anneau de $n$ sites qui ont les identifiants suivants :  
   考虑一个由 $n$ 个站点组成的环，这些站点的标识符按如下顺序排列：

$$
(1, 2, 3, 4, \ldots, \frac{n}{2}, n, n-1, n-2, n-3, \ldots, \frac{n}{2}+1)
$$

dans cet ordre. Quel est le nombre de messages transmis pendant l'exécution de l'algorithme ALTERNER sur cet anneau ? Expliquer votre réponse.  
按这个顺序排列时，ALTERNER 算法在该环上的执行过程中一共传输了多少条消息？请解释你的答案。

   **Corr** : Dans l'anneau
   $$
   (1,2,3,\dots,\tfrac n2,n,n-1,\dots,\tfrac n2+1),
   $$
   la première étape se fait vers la gauche. Chaque site de la première moitié reçoit un identifiant plus grand que le sien et reste candidat, tandis que chaque site de la seconde moitié reçoit un identifiant plus petit et devient passif. Après cette première étape, les seuls candidats sont donc
   $$
   1,2,3,\dots,\tfrac n2.
   $$
   À la deuxième étape, on envoie vers la droite. Le message de $1$ traverse alors toute la moitié droite, devenue passive, puis atteint $2$ ; ainsi $2$ devient passif. De même, le message de $2$ atteint $3$, etc. Finalement, tous les candidats sauf $1$ deviennent passifs. Après deux étapes, il ne reste donc plus qu'un seul candidat, celui d'identifiant minimal.  
   **答案。** 在这个排列
   $$
   (1,2,3,\dots,\tfrac n2,n,n-1,\dots,\tfrac n2+1)
   $$
   中，第 1 阶段向左发送。前半段每个站点收到的都是比自己更大的标识符，所以仍为候选者；后半段每个站点收到的都是比自己更小的标识符，因此全部变成被动者。于是第 1 阶段后，剩下的候选者正好是
   $$
   1,2,3,\dots,\tfrac n2.
   $$
   第 2 阶段向右发送。此时 `1` 的消息会穿过整个已经变成被动者的后半环，再到达 `2`，从而淘汰 `2`；同理，`2` 的消息淘汰 `3`，依次类推。于是两阶段后只剩下唯一候选者 `1`。

   Pour compter les messages, on observe que pendant chacune des deux premières étapes, les messages émis parcourent des segments disjoints qui recouvrent tout l'anneau une fois ; chacune de ces étapes transmet donc exactement $n$ messages. À la troisième étape, le seul candidat restant, d'identifiant $1$, émet son propre message, qui fait un tour complet de l'anneau à travers les sites passifs et revient à son émetteur ; cette étape transmet encore exactement $n$ messages. Le nombre total de messages transmis est donc
   $$
   n+n+n = 3n.
   $$
   Ainsi, pour cet anneau, l'algorithme transmet exactement **$3n$ messages**, donc la complexité est **$\Theta(n)$**.  
   **答案。** 计算消息数时可以注意到：前两个阶段中，所有消息所经过的路径彼此不重叠，并且各自恰好把整个环覆盖一遍，所以每个阶段都恰好传输 `n` 条消息。第 3 阶段时，只剩下候选者 `1`，它发出的消息会通过所有被动节点绕环一周并回到自己，因此这一阶段也恰好传输 `n` 条消息。故总消息数为
   $$
   n+n+n=3n.
   $$
   所以对于这个环，ALTERNER 算法一共传输 **`3n` 条消息**，复杂度为 **$\Theta(n)$**。

## Exercice 3. Election (7 points) 练习3：选举（7分）

Le réseau est un anneau unidirectionnel asynchrone, de taille inconnue. Les canaux sont FIFO. Chaque site dispose d'un identifiant unique. On vous demande de concevoir un algorithme distribué dépendant d'un paramètre $k$, qui se termine explicitement (au moins un site sait quand l'algorithme a terminé) et tel que, à la terminaison, $k$ sites soient distingués (on peut penser que l'on a élu $k$ leaders). Le paramètre $k$ est toujours plus petit que la taille de l'anneau et plus grand que 1. On suppose que l'événement *Initialement* est déclenché sur un sous-ensemble non vide de sites. On rejette la solution où l'on élit d'abord un leader, qui se chargerait de déterminer les $k-1$ autres sites. Vous devez indiquer l'instruction `STOP_GLOBAL` à l'endroit où la terminaison est détectée.  
该网络是一个大小未知的异步单向环。信道满足 FIFO。每个站点都有唯一标识符。要求你设计一个依赖参数 $k$ 的分布式算法，该算法必须显式终止（至少有一个站点知道算法何时结束），并且在终止时有 $k$ 个站点被区分出来（可以理解为选出了 $k$ 个领导者）。参数 $k$ 总是小于环的大小且大于 1。假设事件 *Initialement* 在一个非空的站点子集上触发。题目不接受那种“先选出一个领导者，再由它决定其余 $k-1$ 个站点”的方案。你必须在检测到终止的位置明确写出 `STOP_GLOBAL` 指令。

**Corr** : Une solution naturelle consiste à faire circuler tous les identifiants initiateurs autour de l'anneau, puis à ne conserver que les $k$ plus petits identifiants distincts rencontrés. Chaque site initiateur émet donc initialement un message contenant son identifiant. Chaque site maintient localement l'ensemble ordonné $Top_i$ des $k$ plus petits identifiants vus jusqu'à présent. Lorsqu'un message portant un identifiant $x$ est reçu, si $x \neq i$ alors le site met à jour $Top_i$ avec $x$ puis relaie le message ; si $x = i$, le site sait que son identifiant a fait un tour complet et l'ajoute à l'ensemble $tour_i$. Dès qu'un site constate que les $k$ identifiants de $Top_i$ ont tous effectué un tour complet, il sait que l'algorithme est terminé : ce sont ces $k$ identifiants qui désignent les $k$ leaders. On place alors `STOP_GLOBAL` à cet endroit.  
**答案。** 一个自然的办法是：让所有发起者的标识符在单向环中传播，同时每个站点只保留目前见过的 **$k$ 个最小的不同标识符**。因此每个发起者在初始时发送自己的标识符；每个站点维护一个有序集合 $Top_i$，表示目前看到的最小的 $k$ 个不同标识符。收到标识符 $x$ 时，如果 $x \neq i$，就用 $x$ 更新 $Top_i$ 并继续转发；如果 $x = i$，则说明这个标识符已经绕环一整圈，于是把它加入集合 $tour_i$。一旦某个站点确认 `Top_i` 中的这 $k$ 个标识符都已经完成了一整圈，就可以断定算法结束；这 $k$ 个标识符对应的站点就是最终区分出来的 $k$ 个领导者，此时执行 `STOP_GLOBAL`。

```pseudo
**Connaissance**
$succ_i$ : successeur de $i$ dans l'anneau.
$k$ : nombre de leaders à distinguer.

**Variables**
$Top_i$ : ensemble des $k$ plus petits identifiants vus jusqu'à présent, initialisé à $\emptyset$.
$tour_i$ : ensemble des identifiants de $Top_i$ ayant fait un tour complet, initialisé à $\emptyset$.
$init_i \in \{Vrai, Faux\}$ : indique si l'événement *Initialement* est déclenché sur $i$.

**Messages**
$Msg(id)$

**Algorithme**
**Initialement** ->
  **if** $init_i$ **then**
    $Top_i$ <- $Top_i \cup \{i\}$
    Envoyer $Msg(i)$ à $succ_i$

**Sur réception de** $Msg(id)$ ->
  **if** $id = i$ **then**
    $tour_i$ <- $tour_i \cup \{id\}$
  **else**
    $Top_i$ <- les $k$ plus petits éléments de $Top_i \cup \{id\}$
    Envoyer $Msg(id)$ à $succ_i$

  **if** $|Top_i| = k$ **and** $Top_i \subseteq tour_i$ **then**
    **STOP_GLOBAL**
```

## Exercice 4. TD révisions - Algorithmes divers 练习4：复习题 - 各类算法

1. Ecrire un algorithme sur un arbre enraciné tel que, à la fin de son exécution, la racine connaisse la hauteur de l'arbre.  
   在一棵有根树上编写一个算法，使得算法执行结束时，根节点知道该树的高度。

   **Corr** : On fait remonter l'information depuis les feuilles. Chaque feuille envoie la valeur `0` à son père. Un nœud interne attend les hauteurs envoyées par tous ses fils, prend leur maximum, ajoute `1`, puis envoie le résultat à son père. La racine calcule de la même manière et obtient alors la hauteur de l'arbre.  
   **答案。** 采用自底向上的回传。每个叶子向父节点发送 `0`。内部节点等待所有子节点返回各自子树的高度，取最大值再加 `1`，然后把结果发给父节点。根节点也做同样的计算，最终得到整棵树的高度。

   ```pseudo
   **Connaissance**
   $fils_i$ : ensemble des fils du nœud $i$.
   $pere_i$ : père de $i$.
   $init_i \in \{Vrai, Faux\}$ : indique si $i$ est la racine.

   **Variables**
   $haut_i$ : hauteur du sous-arbre enraciné en $i$.
   $nbRecu_i$ : nombre de retours reçus, initialisé à $0$.
   $max_i$ : maximum des hauteurs reçues, initialisé à $0$.

   **Algorithme**
   **Initialement** -> 
     **if** $fils_i = \emptyset$ **then** /* Sur les feuilles */
       **if** $init_i = Faux$ **then**
         Envoyer $Retour(0)$ à $pere_i$
       **else**
         $haut_i$ <- $0$
         **STOP_GLOBAL**

   **Sur réception de** $Retour(h)$ **de** $j$ ->
     $nbRecu_i$ <- $nbRecu_i + 1$
     $max_i$ <- max($max_i, h$)
     **if** $nbRecu_i = |fils_i|$ **then**
       $haut_i$ <- $max_i + 1$
       **if** $init_i$ **then**
         **STOP_GLOBAL**
       **else**
         Envoyer $Retour(haut_i)$ à $pere_i$
   ```

2. Ecrire un algorithme sur un graphe quelconque, tel que, à la fin de l'exécution, le noeud initiateur connaisse la taille du graphe.  
   在任意图上编写一个算法，使得执行结束时，发起节点知道该图的大小（顶点数）。

   **Corr** : On peut fusionner les deux phases et n'utiliser qu'un seul type de message. Le jeton de diffusion est noté $Jeton(0)$, et le même jeton sert au retour sous la forme $Jeton(v)$, où $v$ est alors la taille du sous-arbre exploré. Ainsi, une feuille renvoie $Jeton(1)$, et un nœud interne renvoie $Jeton(1 + \sum v)$ après avoir reçu tous les retours de ses fils. L'initiateur obtient donc directement la taille du graphe à la fin du PIF.  
   **答案。** 可以把两阶段融合，而且只使用一种消息。扩散时发送的是 $Jeton(0)$；回传时仍然使用同一个 Jeton，只不过写成 $Jeton(v)$，其中 $v$ 表示已经计算出的子树大小。于是叶子返回 $Jeton(1)$，内部节点在收齐所有子节点返回后，返回 $Jeton(1 + \sum v)$。这样发起者在 PIF 结束时就直接得到了整张图的大小。

   ```pseudo
   **Connaissance**
   $vois_i$ : ensemble des voisins du site $i$.
   $init_i \in \{Vrai, Faux\}$ : indique si $i$ est l'initiateur.

   **Variables**
   $pere_i$ : identifiant du père, initialisé à $ndef$.
   $nbRecu_i$ : nombre total de messages $Jeton(v)$ reçus, initialisé à $0$.
   $taille_i$ : taille de la partie explorée enracinée en $i$, initialisée à $1$.

   **Messages**
   $Jeton(v)$ : jeton avec $v = 0$ pendant la diffusion et $v \ge 1$ pendant le retour.

   **Algorithme**
   **Initialement** ->  /* Sur le site initiateur */
     **if** $init_i$ **then**
       **for all** $j \in vois_i$ **do**
         Envoyer $Jeton(0)$ à $j$

   **Sur réception de** $Jeton(v)$ **de** $j$ ->
     $nbRecu_i$ ++
     **if** $init_i$ **then**
       **if** $v \ge 1$ **then**
         $taille_i$ <- $taille_i + v$
       **if** $nbRecu_i = |vois_i|$ **then**
         **STOP_GLOBAL**
     **else**
       **if** $pere_i = ndef$ **then**
         $pere_i$ <- $j$
         **if** $vois_i \setminus \{pere_i\} = \emptyset$ **then**
           Envoyer $Jeton(1)$ à $pere_i$  /* feuille */
         **else**
           Envoyer $Jeton(0)$ à $vois_i \setminus \{pere_i\}$
       **else**
         **if** $v \ge 1$ **then**
           $taille_i$ <- $taille_i + v$
         **if** $nbRecu_i = |vois_i|$ **then**
           Envoyer $Jeton(taille_i)$ à $pere_i$
   ```

3. Etant donné un arbre, écrire un algorithme tel que, à la fin de son exécution, chaque noeud connaisse la taille (en nombre de sommets) du sous-arbre dont il est la racine.  
   给定一棵树，编写一个算法，使得在执行结束时，每个节点都知道以自己为根的子树的大小（按顶点数计）。

   **Corr** : Il suffit encore d'un calcul ascendant. Chaque feuille fixe sa taille à `1`. Un nœud interne attend les valeurs envoyées par tous ses fils, calcule `1 + somme des tailles des fils`, et mémorise ce résultat comme taille de son propre sous-arbre. Contrairement à la question précédente, ici il n'est pas nécessaire que seule la racine connaisse le résultat : chaque nœud conserve localement la valeur calculée pour lui-même.  
   **答案。** 仍然采用自底向上的计算。每个叶子把自己的子树大小设为 `1`。内部节点等待所有子节点返回各自子树大小后，计算 `1 + 所有子节点大小之和`，并把这个值保存为自己子树的大小。与上一题不同的是，这里不只是根知道结果，而是每个节点都会保留自己计算出的子树大小。

   ```pseudo
   **Connaissance**
   $fils_i$ : ensemble des fils de $i$.
   $pere_i$ : père de $i$.
   $init_i \in \{Vrai, Faux\}$ : indique si $i$ est la racine.

   **Variables**
   $taille_i$ : taille du sous-arbre enraciné en $i$, initialisée à $1$.
   $nbRecu_i$ : nombre de retours reçus, initialisé à $0$.

   **Messages**
   $Retour(v)$ : message de retour, avec $v$ la taille du sous-arbre du fils qui envoie le message.

   **Algorithme**
   **Initialement** ->  /* Sur les sites feuilles */
     **if** $fils_i = \emptyset$ **then**
       **if** $init_i = Faux$ **then**
         Envoyer $Retour(1)$ à $pere_i$
       **else**
         **STOP_GLOBAL**

   **Sur réception de** $Retour(v)$ **de** $j$ ->
     $nbRecu_i$ <- $nbRecu_i + 1$
     $taille_i$ <- $taille_i + v$
     **if** $nbRecu_i = |fils_i|$ **then**
       **if** $init_i = Faux$ **then**
         Envoyer $Retour(taille_i)$ à $pere_i$
       **else**
         **STOP_GLOBAL**
   ```
