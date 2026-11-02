# Untitled_Realtime_261002T0737：课堂原始转写与页面译文

来源：EasyNote 的 Transcript 面板，归档于 2026-10-19。法语为平台语音识别原文，保留识别错误与重复；中文为平台自动译文，未按音频逐句校对。时间戳相对该录音开头。

## 00:45

L'L'ététude des des fluidese. Donc, étant donné qu'on va s'intéresser à la danse-cadre, à un mouvement de fluide, on va s'intéresser à un écoululement. Donc, quand on caractérise un écoulement, c'est plutôt avec une vision aériérienne. Et on travaille plutôt avec le champ de vitesse, on ne travaille pas avec la position des particules. On considère qu'on a une grille d'observation qui est fixe, et le le milieuu, s'écoule autour de cette cette grille fixe. On peut mesurer la température, la vitesse, ce qu'on veut, mais pour arriver à la déformation, on a bes besoin de la vitesse. Donc on va d'abord s'intéresser à au calcul du gradient du champ de vitesse, justement, qui va nous permettre d'extraire des informations liées à la déformation du milieu.u.

**页面中文译文**

流体的研究。因此，既然我们将关注流体的运动，即流动，我们就会关注流动的特性。当描述流动时，通常采用俯视视角。我们主要研究速度场，而不是粒子的位置。我们假设有一个固定的观测网格，流体在这个固定网格周围流动。我们可以测量温度、速度等各种参数，但为了得到变形信息，我们需要速度。因此，我们首先关注速度场梯度的计算，这将帮助我们提取与流体变形相关的信息。

## 01:10

On verra comment ça se passe dans le cadre d'un corps rigide, et on pour pourra en extraire, justement, les informations si on retire toute la partie corps rigide, il restera. Tout ce qui est taux de déformation et taux de rotation également, parce que la déformation. Dans tout ce qui concerne la déformation du milieu, il y a une partie rotation. Et puis on verra quelques propriétés d'écoulement particulier.

**页面中文译文**

我们将观察在刚体框架内的情况，并且正是通过去除刚体部分后，能够提取出相关信息。剩下的部分包括变形率和旋转率，因为在介质的变形过程中，存在一部分旋转。接着，我们还将探讨一些特殊的流动性质。

## 01:40

Les slides sont sur iCampus, donc si vous voulez suivre en même temps avec les slides, vous pouvez aller récupérer le tout sur iCampus. Alors, donc, pour bien enfoncer le clou, là on va essayer d'extraire une quantité qui est qui décrit la déformation d'un milieu, mais cette fois en représentation aérienne.

**页面中文译文**

幻灯片已上传至iCampus，因此如果您想同步查看幻灯片，可以前往iCampus下载全部内容。现在，为了更好地强调这一点，我们将尝试提取一个描述介质变形的量，但这次是以俯视图的形式呈现。

## 02:15

Donc on n'a pas de configuration particulière sur laquelle se référer. Alors que pour le cas d'un solide, on prenait la la configuration initiale comme la configuration de référence, et on allait tout exprimer justement en fonction de cette configuration de référence. Là, c'est un écoulement, le milieu est en mouvement perpétuel, enfin perpétuel, il est en mouvement, et on voit les particules s'écouler, on ne sait pas d'où elles viennent, on on ne sait pas ce qui nous intéresse. Nous, ce qui nous intéresse juste, dans cette représentation, c'est à quelle vitesse elles passent en différents points de l'espace. À chaque instant.

**页面中文译文**

因此，我们没有特定的参考构型。对于固体的情况，我们通常将初始构型作为参考构型，并且所有表达式都是基于这个参考构型。而这里是流动，介质处于持续运动中，粒子在流动，我们不知道它们来自哪里，也不清楚具体关注什么。我们关心的只是，在这种描述中，粒子在空间不同点的速度是多少，以及每一时刻的速度情况。

## 03:10

Alors, si on reprend une approche un peu développement limité, on prend deux points fixes de l'espace : un point M et un point N. N, On cons consididèreère que ces deux points, ils sont très, très proches. Si on a le vecteur vitesse ici, pour ce premier point, et puis un vecteur vitesse qui peut être légèrement différent au point N, on peut essayer d'exprimer justement la vitesse à chaque instant et au point N ici, en fonction de la vitesse qui est supposée, on va dire, connue en ce point, en utilisant justement la dérivée du champ de vitesse par rapportport à l'espace.

**页面中文译文**

那么，如果我们采用有限增量的方法，我们取空间中的两个固定点：点M和点N。我们假设这两个点非常非常接近。如果在第一个点处有一个速度矢量，而在点N处的速度矢量可能略有不同，我们可以尝试用点N处的速度来表示每一时刻的速度，这个速度假设在点M处是已知的，利用速度场关于空间的导数来实现。

## 03:39

Par rapport au point N. Fois le vecteur mn. Là, on pourrait rajouter la dérivée double par rapport à l'espace, etc., mais bon. Dans le cadre d'un développement limité, en général, on aime bien utiliser juste le premier terme, enfin le développement à l'ordre 1, ça suffit. Tous les autres termes, on va les négliger.

**页面中文译文**

关于点N，乘以向量mn。在这里，我们可以加入关于空间的二阶导数等等，但算了。在有限展开的框架下，通常我们喜欢只使用第一个项，也就是一阶展开，这就足够了。其他所有项我们都会忽略。

## 04:02

Et donc, ce terme-là, la dérivée du champ de vitesse par rapport à l'espace, c'est tout simplement le gradient du champ de vitesse.e. Donc on retrouve un petit peu l'esprit développement limité. Et ça va nous permettre d'exprimer le champ de vitesse de voir comment le champ de vitesse varie juste en se basant sur le gradient du champ de vitesse.

**页面中文译文**

因此，这个术语，即速度场对空间的导数，实际上就是速度场的梯度。我们可以稍微联想到泰勒展开的思想。这将使我们能够表达速度场，并仅基于速度场的梯度来观察速度场的变化。

## 04:52

Alors, ce gradient, on va, comme on est en représentation aérienne, on. Le coordonnées de l'espace, les. Paramètres spatiaux, c'est justement les coordonnées x1, petit x2, petit x3, qui sont les coordonnées aériennes. Pas les coordonnées initiales des particules, mais les coordonnénées du point M au auquel elles passent au moment où on a la mesure. Donc quand on va faire le gradient, on va le faire justement par rapport à ces coordonnées.

**页面中文译文**

那么，这个梯度，因为我们是在航拍表示中，我们……空间坐标，空间参数，正是指 x₁、小 x₂、小 x₃ 这些航拍坐标。不是粒子的初始坐标，而是它们经过测量时所在点 M 的坐标。所以当我们计算梯度时，正是相对于这些坐标来进行的。

## 05:59

Alors, pour tout ch. Quand il est sous forme d'un gradient, un champ de vitesse quandand on prend le gradient, on était parti d'un champ de de vitesse sans unamp de vecteur, si vous dérivez par rapport à l'espace, vous arrivez à un p transfert du second ordre. Vous avez une matrice. N'importe quel transfert du second ordre, que ce soit un gradient ou peu importe, vous pouvez toujours le décomposer en une partie symétrique et une partie antisymétrique. La La partie symétrique, vous prenez tout simplement la moitié de la, enfin du tenseur initial, ici le gradient du champ de vitesse, plus sa transposée, ça vous extrait la partie symétrique, pour en extraire la partie antisymétrique, vous faites la moitié de la différence entre le tenseur et son transposée. Ça, c'est une opération que vous pouvez faire sur tout tenseur.

**页面中文译文**

那么，对于任何场。当它以梯度的形式存在时，一个速度场，当我们取梯度时，我们是从一个速度场出发的，它是一个向量场，如果你对空间求导，就会得到一个二阶张量。你会得到一个矩阵。任何二阶张量，无论是梯度还是其他，都可以分解为对称部分和反对称部分。对称部分就是取初始张量（这里是速度场的梯度）与其转置的和的一半，这样就提取出了对称部分；要提取反对称部分，则取张量与其转置差的一半。这是一个可以对任何张量进行的操作。

## 06:28

En gros, c'est tout simplement une décomposition sur une base de tenseur, en fait. Une partie symétrique, une partie antisymétrique. Là, ici, ce qui va être intéressant, c'est qu'on va donner un sens à chacune de ces parties. On va considérer que la partie symétrique, on va déjà lui donner un nom, enfin une notation, d, et ce d, ça va être ce qu'on appelle le tenseur taux de déformation.ation.

**页面中文译文**

基本上，这只是基于张量的一种分解。一个对称部分，一个反对称部分。在这里，有趣的是我们将赋予每个部分一个意义。我们将把对称部分命名为 d，或者用符号 d 表示，这个 d 就是所谓的应变率张量。

## 08:02

Alors, si vous vous souvenez, on avait pu— Ok. Donc ce tenseur taux de déformation, c'est la partie symétrique du gradient de vitesse, qui. Et d'autre part, on va avoir ce qu'on appelle le taux de rotation du. Pour la partie antque. Donc le fait est que en réalité, on va pouvoir attribuer à la partie symétrique la partie déformation du milieu, ce qui représente plutôt le fait que le milieu s'étire ou soit cisaillé comme si vous utilisiez des ciseaux ou une cisaille, c'est tout simplement ça.

**页面中文译文**

那么，如果你还记得的话，我们之前已经讲过——好的。这个变形率张量是速度梯度的对称部分。另一方面，我们还有所谓的旋转率部分。对于反对称部分，实际上我们可以将对称部分归因于介质的变形部分，这主要表示介质被拉伸或剪切，就像你使用剪刀或剪切机一样，情况就是这样。

## 08:26

Vous avez un glissement, en fait, des fibres, les unes par rapport aux aut. Et ici, plutôt la partie rotation. Donc typiquement, le taux de rotation, vous allez retrouver ça dès que vous allez avoir un mouvement qui va ressembler. À une rotation, à un tourbillon par exemple, ça vous donne l'aspect rotation locale du.

**页面中文译文**

实际上，纤维之间存在滑移。这里主要是旋转部分。通常，当你遇到类似旋转或涡流的运动时，就会观察到旋转率，这反映了局部的旋转特性。

## 08:53

Milieu, et donc là, vu qu'on est plutôt sur une représentation aérienne, plutôt pour les fluides. Alors, ce tenseur taux de rotation, comme il correspond à à une une partie antisymétrique, en fait, il. Ça veut dire que sa diagonale est forcément nulle, et que les termes hors diagonaux sont forcément opposés.

**页面中文译文**

环境，因此这里，由于我们主要是在讨论流体的空气动力学表示。这个旋转率张量对应于一个反对称部分，实际上这意味着它的对角线元素必然为零，且非对角线元素必然互为相反数。

## 09:28

Et un tenseur du second ordre, on peut voir ça comme un opérateur, quand vous— si vous appliquez ce tenseur taux de déformation à un vecteur, par exemple mn, comme on a pu voir tout à l'heure,. Là, c'est l'annexe des bases mathématiques, qui doit être dans. Lesus. Copiés de l'année dernière, que je n'ai pas eu aujourd'hui.

**页面中文译文**

作为一个二阶张量，我们可以将其视为一个算子，当你——例如，将这个变形率张量作用于一个向量，比如 mn，就像我们刚才看到的那样。这部分内容在数学基础的附录中，应该是在 Lesus 里。是去年复制过来的，我今天没有拿到。

## 10:00

En fait, vous pouvez le mettre sous une autre forme, le fait de faire ce produit matrice-vecteur, ça revient exactement à la même chose que faire un produit vectoriel entre un vecteur et un autre vecteur,. Et ça, c'est valable que si— Si ce tenseur-là est antisymétrique. Alors, vu que nous, par.

**页面中文译文**

实际上，你可以用另一种形式来表示，进行这个矩阵-向量乘积，实际上和对两个向量做叉积是完全一样的。而且，这只有在这个张量是反对称的情况下才成立。既然我们，按照…

## 10:35

On a dit qu'il était antisymétrique,. On peut écrire un vecteur qui peut s'écrire sous cette forme-là, donc avec le symbole de Lévititchi-Vital, c'est un tenseur du troisième ordre. En gros, pour ce tenseur-là, epsilon i j k,. Très rapidement, c'est égal à 1 si i j et k, ça vous fait une permutation cir.

**页面中文译文**

有人说它是反对称的。我们可以写出一个可以用这种形式表示的向量，也就是用Levi-Civita符号表示的，这是一个三阶张量。大致来说，对于这个张量ε_ijk，如果i、j和k构成一个循环排列，那么它的值就是1。

## 11:43

Directe, donc. En gros, 1, 2, 3, 2, 3, 1, 2, 3, 1, 2, c'est égal à à -1 si. C'est indirect,. Et c'est égal à 0 si i = j,, i = k, ou j = k. Don Donc si vous avez un indice qui est répété,. Et donc, en fait, c'est ce qui nous permet de retrouver. L'esprit du produit vectoriel,. Et donc le fait de le retrouver sous la forme d'un produit vectoriel, vous allez voir qu'on va retrouver la loi de composition des vitesses, en réalité.

**页面中文译文**

直接的，所以基本上，1，2，3，2，3，1，2，3，1，2，如果满足条件则等于 -1。如果是间接的，则等于 1。如果 i = j，i = k，或 j = k，则等于 0。所以如果有重复的指标，实际上这正是让我们能够找回向量积的本质。而且，通过将其重新表达为向量积的形式，你会看到我们实际上会重新发现速度合成定律。

## 12:16

Donc, si on se place cette fois dans le cas d'un corps rigide, justement, on va retrouver cette loi de composition des vitesses, classique, la vitesitesse au point m, au point m, pardon, on peut l'exprimer si on considère que— Ces points-là. Font partie d'un solide sigma qui se comporte comme un solide, pardon.

**页面中文译文**

因此，如果这次我们考虑刚体的情况，我们将重新得到经典的速度合成定律。点m处的速度，如果我们认为这些点属于一个表现为刚体的固体σ，那么可以这样表达。

## 12:55

Un milieu qui n'est pas forcément un solide, un milieu qui se déplace sous forme comme un corps rigide, c'est exactement la même chose de se dire que vous avez mis de l'eau dans un verre, et vous transportez tr très délicatement votre verre d'eau, le milieu, il peut se déformer, c'est un fluide, mais a priori, si vous le déplacez très lentement, il a un m mouvement de corps rigide. Vous êtes capable de le tourner pour le présenter différemment si par exemple c'était un œil avec une nuance pour le donner à quelqu'un, vous pouvez très bien l'animer d'un mouvement de corps rigide sans que ça déforme le milieu, ok.

**页面中文译文**

环境不一定是固体，环境可以像刚体一样移动。就好比你往杯子里倒水，然后非常小心地搬动这杯水。这个环境是可以变形的，因为它是流体，但原则上，如果你移动得非常慢，它会表现出刚体运动的特性。你可以旋转它以不同的方式展示，比如如果这是一个带有色调的眼睛，想要递给别人，你完全可以让它做刚体运动，而不会使环境变形。

## 13:37

Donc, mettons, on a— on veut exprimer la vitesse de ce point en fonction de ce point, on connaît avec ce vecteur-là qu'on a pu exprimer à partir de notre tenseur de. Oméga qui représente la partie antisymétrique du rayon de vitesse. Du coup, vous pouvez très bien transporter le champ de vitesse du point m au point m, en utilisant justement le produit vectoriel entre ce vecteur omégaga qui est lié à votre tenseur antisymétrique oméga, et le vecteur mn.

**页面中文译文**

所以，假设我们想用这个点来表示该点的速度，我们可以利用这个向量来表达，它是从我们的张量中得到的。欧米伽张量表示速度半径的反对称部分。因此，你完全可以利用与反对称张量欧米伽相关的欧米伽向量，与向量mn的叉乘，将点m的速度场传递到点m。

## 14:14

Éventuellement, il il peut peut dépendre du temps,. Vu qu'ils vont se déplacer, ok. Au cours du mouvement.. Donc maintenant, on si on considère que ces deux points sont assez proches, on va pouvoir représenter ce petit vecteur mn comme étant un petit vecteur infinitésimal de l'espace, et donc la dérivée temporelle, justement, de ce vecteur mn, ici, que je peux vous matérialiser en rouge,.

**页面中文译文**

最终，它可能取决于时间。因为他们会移动，好吧。在运动过程中……所以现在，如果我们认为这两个点足够接近，我们就可以将这个小向量mn表示为空间中的一个无穷小向量，因此这个向量mn的时间导数，在这里，我可以用红色标示出来。

## 14:51

Ce vecteur mn, si je calcule sa dérivée temporelle par rapport au temps, c'est la dérivée du coût temporel de dm, et en utilisant ce qu'on appelle le théorème de Schwarz, qui permet d'inter. De changer l'ordre des dérivées en fonction des paramètres de l'espace, pour avoir certaines conditions de régularité, au lieu de dire que c'est la dérivée temporelle de dm, on peut dire que c'est égal à une petite variation du champ de vitesse, ok.

**页面中文译文**

这个向量mn，如果我计算它关于时间的导数，就是dm的时间导数的导数。利用所谓的施瓦茨定理，该定理允许在满足一定正则条件的情况下交换空间参数的导数顺序。与其说这是dm的时间导数，不如说它等于速度场的一个微小变化。

## 15:40

On a fait rentrer la dérivée temporelle dans la position, ok. Je reprends donc cette quantité-là, ici, par la relation de Challe, je peux faire intervenir le vecteur origine O entre deux, et la dérivée du vecteurteur, donc— j'ai mon mon origine ici,. Faire ce trajet-là, c'est en fait la même chose que de le faire comme ceci, hop, donc c'est exactement la même chose que de partir au point O et de revenir au point n, leses.

**页面中文译文**

我们将时间导数引入位置中，好的。所以我在这里重新考虑这个量，通过查勒关系，我可以在两者之间引入原点向量O，以及向量的导数，所以——我的原点在这里。走这条路径，实际上和这样走是一样的，嗯，所以这完全等同于从点O出发再回到点n。

## 16:13

Temporelles de ces deux vecteurs, en fait, c'est l'opposé de la la vitesse du point m qui est ici, et la vitesse du point n ici.i, Donc en réalité, Donc en réalité, la dérivée temporelle de mn de t, je vois que je peux la réécrire comme étant égale à ce produit vectoriel en me basant sur cette équation-là, parce que j'ai fait les— j'ai calculé la différence entre ces deux vecteurs de vitesse,.

**页面中文译文**

这两个向量的时间导数，实际上是点m在这里的速度和点n在这里的速度的相反方向。因此，实际上，向量mn关于时间t的导数，我看到我可以根据这个方程将其重写为这个叉积，因为我已经计算了这两个速度向量的差值。

## 17:34

Donc du coup, ma différentielle du champ de vitesse, elle peut s'écrire sous cette forme,. Mm g j'ai montré que je pouvais le réécrire comme étant dm, et donc du coup, je vais pouvoir recalculer mon champ de vitesse en intégrant cette quantité, finalement. Donc dans ce cas-là,. Le gradient du champ de vitesse, ici, il correspond essentientiellement à cette partie-là de l'opération, qui finalement ne représente qu'une partie rotation, donc dans ce cas— dans le cas d'un corps rigide, le gradient de vitesse,— si je le décompose en parties symétriques et antisymétriques, je vois directement que la partie symétrique est forcément nulle, et par contre la partie antisymétrique— première chose, elle ne va pas dépendre de l'espace, quand je suis sur un corps rigide, et elle va représenter justement, en fait, le vecteur rotation de mon solide— enfin, de mon solide, pardon, de mon corps, qui suit un mouvement de corps rigide.e. Oi.ui, Là,

**页面中文译文**

因此，我的速度场的微分可以写成这种形式。嗯，我已经证明我可以将其重写为 dm，因此我最终可以通过积分这个量来重新计算我的速度场。在这种情况下，速度场的梯度主要对应于操作中的这一部分，它实际上只表示旋转部分。因此，在刚体的情况下，如果我将速度梯度分解为对称部分和反对称部分，我可以直接看到对称部分必然为零，而反对称部分——首先，它不会依赖于空间，因为我处于刚体上，并且它实际上代表了我的固体——不，抱歉，是我的物体的旋转矢量，该物体遵循刚体运动。

## 18:03

Là, c'est un dm qui manque, le vectorieliel dm. Là, Là, il n n'y aen. Parce qu'en fait, cet opérateur-là, ce tenseur, on peut l'écrire comme tout simplement. C. La même chose.e, Ok. C'est une autre manière de l'écrire, si vous voul. C'est un peu bizarre, mais ce tenseur, c'est une matrice qui effectue une opération, c'est un un opérateur.

**页面中文译文**

这里缺少一个微分算子，向量微分算子。这里，那里，没有。因为实际上，这个算子，这个张量，我们可以简单地写成C。同样的东西。好的。这是另一种写法，如果你愿意的话。有点奇怪，但这个张量是一个执行操作的矩阵，是一个算子。

## 18:37

Et cette opération, c'est exactement la même chose si vous préférez, vous pouvez le réécrire comme ça. Sauf que là, j'ai juste montré que mon gradient, du champ de vitesse, en fait, il n'est composé que de la partie antisymétrique, doncc si vous préférez, si je réécris ça, c'est comme si j'avais écrit la dérivée spatiale de mon champ de vitesse, donc ça correspond bien au gradient du champ de vitesse, ok.

**页面中文译文**

这一步操作其实完全一样，如果你愿意的话，你也可以这样重写。只是我刚才展示了我的速度场的梯度实际上只包含反对称部分，所以如果你愿意，我重新写的话，就好像我写的是速度场的空间导数，因此这确实对应于速度场的梯度，明白了吗。

## 19:23

Pardon. Et c. Comme j'ai la partie symétrique qui est nulle, c'est comme si c'était égal à. Ça, ok. Et donc je peux dire que— oui. J'auraisit dû mettretre dès le début, mais. Dans ces cas-là, j'ai le gradient du champ de vitesse fo. Vecteur mn, je peux l'écrire comme si'était la même chose que ça,.

**页面中文译文**

抱歉。等等。由于我有一个对称部分为零，就好像它等于那个。好的。所以我可以说——是的。我本应该一开始就写出来，但在这种情况下，我有速度场的梯度 \( \mathbf{f}_0 \)。向量 \( \mathbf{m}_n \)，我可以把它写成好像和那个是一样的。

## 20:06

Ce qui est également égal à ça. Donc je peux complètement intervertir cette. Opérateur par celui-là. Ok. Bon, là, c'est une des rares démonstrations que je vais vous faire, mais c'est pour— c'est pour vous sensibiliser, je prends la question, juste après, sur le fait que vos opérateurs sous forme de t tenseurs du sol contorque, ça correspond à des— ça peut correspondre à des opérations qui qui sont faites entre— par des vecteurs sur deux vecteurs.

**页面中文译文**

这也等同于这个。所以我可以完全互换这个运算符和那个运算符。好的。嗯，这是我给你们做的为数不多的演示之一，但这是为了——是为了让你们意识到，我稍后会接着讲一个问题，关于你们的算符以张量形式存在于余切空间，这对应于——可能对应于由两个向量之间进行的运算。

## 20:24

O Donc ça, c'est où la— et on peut le régénérer des corps dans Enfin, ce c'était— enfin, je ne comprendsends pas pas si vous voul. Là, en fait, ce qu'on montre, c'est que dans le cas d'un corps rigide, ce qu'il faut retenir, c'est que vous avez le taux de déformation qui est nul. Mais voilà.

**页面中文译文**

哦，所以这是在哪里——而且我们可以在这里再生身体。嗯，这个是——嗯，我不太明白你想表达什么。实际上，我们展示的是，在刚体的情况下，需要记住的是变形率为零。就是这样。

## 20:56

Et Et dans un cas— dans le cas d'un corps rigide, il il n'y a pas de déformation, en fait. Un corps rigidide ou un— enfin, un mou— un milieu qui suit un mouvement de corps rigide, ça se fait sans déformation. En gros, ce qu'on montre là, c'est que en considérant que le. Milieu suit un mouvement de corps rigide, ce qui est caractérisé par ce type d'équation, ok,.

**页面中文译文**

在一种情况下——刚体的情况下，实际上没有变形。刚体或者说遵循刚体运动的介质，是在没有变形的情况下运动的。基本上，我们这里展示的是，考虑介质遵循刚体运动，这种运动由这种类型的方程来描述。

## 21:20

Ça amène au fait que le gradient du champ de vitesse est uniquement composé d'une opérération qui est— enfin, qui peut se mettre— qui peut se mettre sous la forme d'un tenseur du second ordre antisymétrique. Et dans ces cas-là, ça veut dire que ça ne correspond qu'à une rotation, et donc que la— qu'il n'y a qu'une partie antisymétrique, et donc la partie symétrique est nulle, cette partie symétrique, on l'attribue à la déformation.

**页面中文译文**

这意味着速度场的梯度仅由一个操作组成——或者说可以表示为一个二阶反对称张量。在这种情况下，这表示它仅对应于旋转，因此只有反对称部分，而对称部分为零。对称部分则归因于变形。

## 22:05

Ok. Donc par ce raisonnement-là, on a réussi à donner— à attribuer le sens qu'on a à la partie symétrique et à la partie antisymétrique de notre gradient du champ de vitesse. Si vous voul. Donc en conclusion, l'opérateur qu'on note grand D, donc avec une double barre pour signifier que c'est bien un tenseur du second ordre, c'est la partie du symétrique du gradient du champ de vitesse, et on l'appelle taux de déformation— il peut dépendre du temps et du point de la grille où on a mesuré le champ de vitesse.

**页面中文译文**

好的。通过这个推理，我们成功地赋予了速度场梯度的对称部分和反对称部分以意义。如果您愿意。总之，我们用双杠表示的算子大D，是速度场梯度的对称部分，我们称之为变形率——它可能依赖于时间和我们测量速度场的网格点。

## 22:43

Alors, éventuellement, bon, ça, c'est plus pour. Voir qu'on peut toujours rebasculer dans une autre description, vous pouvez reer. Par exemple en description eulérienne, là on a— on a le tenseur de déformation de Green-Lagrange, donc en— qui est plutôt en représentation Lagrangienne, là vous voyez qu'il est lié à ce tenseur taux de déformation par l'intermédiaire de f, qui, je le rappelle, est le gradient de la transformation.

**页面中文译文**

那么，实际上，这更多是为了说明我们总是可以切换到另一种描述方式。比如说，在欧拉描述中，我们有格林-拉格朗日应变张量，它更倾向于拉格朗日表示。你可以看到它通过变换梯度f与速率应变张量相关联，f是变换的梯度，我在这里提醒一下。

## 23:14

Donc vous pouvez rebasculer en description Lagrangienne. Parcece que votre gradient du champ de vitesse, vous pouvez l'exprimer en fonction de la dérivée temporelle du gradient de transformation son inverse, et vous pouvez aussi vous amuser à, du coup, vu que vous avez le. Gradient du champ de vitesse D, c'est la partie symétrique du gradient du champ de vitesse, donc du coup la partie symétrique de.

**页面中文译文**

因此，您可以切换回拉格朗日描述。因为速度场的梯度可以用变换梯度的时间导数及其逆来表示，您也可以利用这一点。速度场梯度的对称部分D，就是速度场梯度的对称部分。

## 23:39

Cette expression. Donc là, vous retrouvez un demi de cette quantité, plus son transposée, donc qui se met sous cette forme. Si vous appliquez la transposée à cette expression, vous obtenez ça. Donc ça, c'est l'inverse de la transposée, et là. Vous avez la transposée de la dérivée temporelle du gradient de transformation.

**页面中文译文**

这个表达式。所以这里，你得到这个量的一半，加上它的转置，因此它呈现出这种形式。如果你对这个表达式应用转置，你会得到这个。因此，这就是转置的逆操作。这里，你有变换梯度的时间导数的转置。

## 24:39

Bon, je vous rassure tout de suite, c'est des équations qui vous sont données plutôt pour notes, mais que vous n'allez pas manipuler. Donc avec la démonstration qu'on vient de faire, le lien avec les mouvements de corps rigides, c'est que si à un instant t vous avez le tenseur taux de déformation qui est nul en tout, en tout point point de votre solide, de votre solide, de votre milieu, je peux l'appeler oméga pour que ce soit cohérent avec le slide, là, ça veut dire que le champ de vitesse est un tenseur, ça veut dire que vous pouvez mettre le champ de vitesse sous cette forme, donc le champ de vitesse à tout instant t est en tout point de l'espace, ça peut être composé d'un vecteur qui ne dépend que du temps, qui va être la translation, par exemple, de votrere mil milieu,.

**页面中文译文**

好的，我马上给您解释清楚，这些方程主要是作为笔记给出的，您不需要去操作它们。通过我们刚才的演示，与刚体运动的联系在于：如果在某一时刻 t，变形率张量在您固体的每一个点上都为零，我可以称它为 ω，以便与幻灯片保持一致，这意味着速度场是一个张量，也就是说，您可以将速度场表示成这种形式。因此，在任意时刻 t，空间中每一点的速度场可以由一个仅随时间变化的向量组成，比如说，您的介质的平移运动。

## 25:08

Et d'une partie qui est liée à la rotation avec le vecteur rotation qui représente, par exemple, le. La rotation de votre milieu, ok, vous voyez que ça dépend du temps, vous avez juste besoin d'un vecteur qui peut potentiellement dépendre du temps pour exprimer la rotation de votre corps, vectorielle OM, donc O, l'origine de votre domaine, et puis M, le point auquel vous voulez exprimer la vitesse.

**页面中文译文**

以及与旋转相关的部分，其中旋转向量表示例如您的介质的旋转。好的，您可以看到它随时间变化，您只需要一个可能随时间变化的向量来表达物体的旋转，向量OM，其中O是您区域的原点，M是您想要表达速度的点。

## 25:32

Plus— Plus votre— le point M auquel vous voulez exprimer la vitesse s'éloigne de l'origine, là vous allez exprimer votre vecteur rotation, et plus la vitesse de ce point va être importante pour une même rotation. Je suis prêt. Oi. Du coupup, toutes l'équations de la page précédente, c'était pour démontrer celle-là, la—

**页面中文译文**

此外——点M越远离原点，你想表达的速度点越远离原点，你表达的旋转矢量就越明显，对于相同的旋转，该点的速度也会越大。我准备好了。好的。总之，上一页的所有方程都是为了证明这个方程，那个——

## 25:53

C'était pour— tout ça, c'était une démonstration, pour justement montrer que dans un mouvement de corps rigide, vousus avez d qui est nul, et donc vous avez une équivalence., Si vous arrivez à mettre le champ de vitesse— par pardon— sous cette forme, c'est que c'est un mouvement de corps rigide, si c'est un mouvement de de corps rigide, vous avez d qui est égal à 0.

**页面中文译文**

这完全是一个演示，目的是为了说明在刚体运动中，变形率张量 d 为零，因此存在等价关系。如果你能够将速度场表示成这种形式，那说明这是刚体运动；如果是刚体运动，那么 d 就等于零。

## 26:19

Et donc typiquement, ce n'est pas parce que c'est valable pour un court intervalle de temps que vous avez un mouvement de corps rigide que ça va tout le temps être le cas, vous pouvez très bien au début commencer à vous mettre en mouvement sans que ça génère de déformation, et au bout d'un moment, il y a— vous franchissez un seuil et ça génère de la déformation, par exemple.

**页面中文译文**

因此，通常情况下，仅仅因为在短时间内适用刚体运动，并不意味着这种情况会一直持续。你完全可以一开始运动时没有产生变形，但过了一段时间后，你会达到一个临界点，开始产生变形。

## 27:00

Je Il me souviens qu'avant, il y avait une équivalence dans. Démonstration, parce qu'il y a eu l'implication— Oui, alors c'est— ce n'est pas forcément très propre,. Là où il y a le— Ici, là? Oi. Oui, je je crois, on devrait pouvoir mettre une équivalenceence. Non, mais parce que c'est vrai que là, je pars de la.

**页面中文译文**

我记得以前在演示中有一个等价关系，因为存在蕴含——是的，所以这不一定非常严谨。这里有——这里，对吧？是的，我相信我们应该能够建立一个等价关系。不，不过因为我现在是从这个出发的。

## 28:05

Description d'un mouvement de corps rigidee,— Oui, bon, ce serait à reprendre.re en En tout cas, enfin, ce que vous pouvez retenir, c'est que on part du gradient du champ de vitesse, ce qui est de se mettre sous cette forme-l. Vous en prenez la partie symétrique, ça vous donne ce qu'on appelle le taux de déformation, si ce t ce taux de déformation est nul, c'est que vous avez un mouvement de corps rigide, et que donc vous pouvez mettre le champ de vitesse sous cette forme, avec une translation qui peut dépendre du temps, et une rotation qui peut dépendre du temps, donc c'est. Translation du corps rigideide, la rotation du corps rigide, et de manière équivalente, si vous arrivez à mettre le champ de vitesse sous cette forme, ça veut dire que votre— vous n'avez pas de déformation dans votre milieu, que le tenseur taux de déformation est nul, et que du coup vous avez un mouvement de corps rigide.

**页面中文译文**

刚体运动的描述——好的，这部分需要重新整理。无论如何，您需要记住的是，我们从速度场的梯度出发，将其表示为这种形式。取其对称部分，这就是所谓的变形率。如果变形率为零，说明您有一个刚体运动，因此速度场可以表示为由时间决定的平移和旋转的形式。这就是刚体的平移和刚体的旋转。等价地，如果您能够将速度场表示为这种形式，说明您的介质中没有变形，变形率张量为零，因此您拥有一个刚体运动。

## 28:35

Vous avez vraiment une équivalivalence entre les deux. Donc en gros, si. Votre milieu se. Déforme réellement, c'est que soit vous avez d qui est non nul, en une partie de votre milieu et sur un intervalle de temps, soit que vous avez— alors bon, ça c'est encore autre chose— que vous avez la partie antisymétrique, là, qui est dépendante du temps.

**页面中文译文**

你们之间确实存在等价关系。基本上，如果你的介质确实发生变形，那要么是你的介质中某部分的d不为零，并且在一段时间内如此，要么是——这又是另外一回事——你有一个时间相关的反对称部分。

## 29:05

Ça veut dire que potentiellement vous avez juste des petits tourbillons un peu partout. Alors bon, ça c'est— première remarque, ce. Vecteur-là, vous pouvez l'écrire, vous pouvez le déterminer en utilisant l'opérateur rotationnel, qui va vous permettre d'extraire du champ de vitesse la partie rotation, directement.

**页面中文译文**

这意味着你可能只是到处都有一些小涡旋。那么，好吧，这是——第一点，这个向量你可以写出来，也可以用旋度算子来确定，它可以直接从速度场中提取旋转部分。

## 29:36

Donc l'opérateur rotationnel, il porte bien son nom, il extrait la partie rotation, la partie courbure d'un champ. Et la courbure d'un champ de vitesse, on attribue ça à la rotation. Et donc la définition sur le même principe que l'opérateur précédent, l'opérateur oméga, c'est la partie antisymétrique, et ça représente le taux de rotation, donc c'est— ça représente une vitesse de rotation.

**页面中文译文**

旋转算子名副其实，它提取场的旋转部分，即曲率部分。速度场的曲率归因于旋转。因此，其定义与前一个算子欧米伽算子基于相同的原理，是反对称部分，代表旋转速率，也就是说，它表示旋转速度。

## 30:16

Qu'on peut extraire, du du coupup, soit en passant par la partie antisymétrique du gradient de vitesse, mais on a vu qu'on avait une équivalence avec un vecteur de rotation oméga, qui peut ou pas dépendre de l'espace, qui s'extrait à partir du. Rotationnel du champ de vitesse. Alors typiquement, si on applique cette opération avec le rottationnel, on obtient quelque chose qui ne dépend pas de l'espace, on a montré que le mouvement était un mouvement de corps rigide.

**页面中文译文**

可以从切变中提取出来，要么通过速度梯度的反对称部分，但我们已经看到这与一个旋转矢量ω等价，ω可能依赖于空间，也可能不依赖，它是从速度场的旋度中提取的。通常，如果我们用旋度进行这个操作，我们得到的结果不依赖于空间，我们已经证明这种运动是刚体运动。

## 31:05

Ok, donc on va pouvoir décrire les différents types d'écoulement particuliers,. Première propriété d'un écoulement, ou d'un mouvement, l'aspect incompressible. Donc on dit qu'un mouvement— qu'un écoulement, ou qu'un mouvement est incompressible, si la divergence du champ de vitesse eulérien, donc avec le petit indice e, exposant, donc ça revient à cal calculer la trace du gradient du champ de vitesse, en réalité, la divergence, donc—

**页面中文译文**

好的，那么我们将能够描述不同类型的特殊流动。流动或运动的第一个性质是不可压缩性。也就是说，如果欧拉速度场（带有小标记e的速度场）的散度为零，也就是计算速度场梯度的迹，实际上就是散度，那么这个流动或运动被称为不可压缩的。

## 31:36

Si je le prends pour n'importe quel champ de vitesse, c'est tout simplement ceci. Avec laann nototation de d' laassommation d'Einstein, ça correspond à faire la somme sur i de v_i dérivé par rapport à i, qui est la notation compacte, de la dérivée de la composante i par rapport à x.i. Vu qu'on est en représentation eulérienne.

**页面中文译文**

如果我将其应用于任意速度场，实际上就是这样。使用爱因斯坦求和约定，这相当于对 i 求和 v_i 关于 x_i 的导数，这是对分量 i 关于 x_i 导数的简洁表示。因为我们采用的是欧拉描述。

## 32:11

Alors vu que l'on fait la— on calcule la trace du gradient du champ de vitesse, ça veut dire qu'on fait la somme des éléments diagonaux, que ce soit le gradient du champ de vitesse ou sa partie symétrique, ça revient exactement au même. Donc ça là. Divergence du champ de vitesse eulérien, c'est exactement la même chose que la trace du tenseur d, qui représente la partie symétrique du gradient du champ de vitesse.

**页面中文译文**

既然我们计算的是速度场梯度的迹，也就是对角元素的和，无论是速度场梯度还是其对称部分，结果都是完全相同的。因此，欧拉速度场的散度，实际上与表示速度场梯度对称部分的张量d的迹是完全一样的。

## 32:36

Voilà, ça c'est pour vous familiariser un peu avec les équivalences et les identités en calcul en. Analyse vectorielle et tensorielle. Deuxième caractéristique d'un écoulement, il peut ou non être stationnaire. Alors, stationnaire, c'est tout simplement la dépendance au temps du champ de vitesse eulérien.

**页面中文译文**

这就是为了让你们稍微熟悉一下向量和张量分析中的等价关系和恒等式。流动的第二个特征是它是否为稳态。所谓稳态，就是欧拉速度场是否随时间变化。

## 33:00

Vous pouvez très bien avoir un champ de vitesse en représentation Lagrangienne qui va dépendre du temps, parce que vous. Prenez par exemple un simple mouvement de rotation, si vous regardez la vitesse d'une particule, elle change, elle ne change pas forcément en termes de norme, mais au moins en termes de direction.

**页面中文译文**

您完全可以拥有一个随时间变化的拉格朗日速度场。举例来说，考虑一个简单的旋转运动，如果观察一个粒子的速度，它会发生变化，速度的大小不一定变化，但至少方向会变化。

## 33:22

Par contre, le mouvement de rotation, il est perpétuel, vous avez une hor horloge qui tourne, c'est tout le temps le même mouvement que vous allez voir, donc dans ces cas-là, on a bien le champ de vitesse eulérienne qui est indépendant du temps, par contre si on avait regardé sa représentation Lagrangienne, on aurait pas pu arriver à la traéce stationn.

**页面中文译文**

另一方面，旋转运动是永恒的，你有一个不停转动的钟表，运动始终如一，因此在这种情况下，我们确实得到了与时间无关的欧拉速度场；但如果我们观察其拉格朗日表示，就无法达到稳态轨迹。

## 34:05

Autre propriété, l'aspect rotationnel. Est-ce qu'un écoulement est irrotationnel? Cette fois, c'est si la partie rotation du champ de vitesse extraite par l'opérateur rotationnel est nulle. Il manque un petit vecteur ici,. Je corrige ça. C'est ici à l'intérieur. Je corrigerai tout à l'heure.

**页面中文译文**

另一个性质是旋转性。流动是否为无旋流？这次是指通过旋转算子提取的速度场的旋转部分是否为零。这里缺少一个小向量，我来修正一下。就在这里面，我稍后会全部修正。

## 34:40

Là, après, on arrive sur des considérations plutôt sur des des aspects mécaniques des fluides, on va dire, on parle d'aspect laminaire, donc un écoulement qui se fait de manière laminaire, c'est en l'absence de turbulence, lorsque vous avez le fluide qui s'écoule vraiment coucheche par couche, vous n'avez pas de turbulence, vous n'avez pas de remous, si vous voulez, de tourbillons, qui sont générés par les turbulences typiquement quand vous avez un écoulement qui se passe à une vitesse beaucoup trop élevée par rapport à la viscosité du milieu.

**页面中文译文**

接下来，我们将讨论流体力学的机械方面，具体来说是层流现象。层流指的是流体以层层叠叠的方式流动，没有湍流。当流体以这种方式流动时，不会产生湍流，也不会有漩涡，这些漩涡通常是在流速远高于介质粘度时产生的。

## 35:14

Donc en gros, les couches, se glissent les unes par rapport aux autres sans que ça génère de gros tourbillons. Alors, il y a une simplification abusive qui se fait assez régulièrement, c'est de dire que si l'écoulement est laminaire, le gradient du champ de vitesse fois v, donc le terme convectif qu'on a pu voir dans la dérivée particulière, est négligeable. En réalité, c'est plutôt pour les écoulements rampants qu'on peut faire cette simplification. Bon, c'est une petite note, mais ce n'est pas central.

**页面中文译文**

所以基本上，流体层彼此滑动时不会产生大的涡流。这里有一个常见的过度简化，就是说如果流动是层流，那么速度场的梯度乘以速度，即我们在物质导数中看到的对流项，可以忽略不计。实际上，这种简化更适用于缓慢流动的情况。嗯，这只是一个小提示，但并不是核心内容。

## 35:45

C'est'est plus pour vous familiariser un peu avec les termes li liés avec l' l'étude des fluides. Don Donc ça clôt ce chapitre sur le. Description des déformations plutôt dans les milieux fluides. Et donc on va pouvoir mettre ça en application sur des petits exercices. Il faut que je je lire ça.

**页面中文译文**

这主要是让您熟悉一些与流体研究相关的术语。这样就结束了关于流体介质中变形描述的这一章。接下来我们将通过一些小练习来应用这些内容。我需要读一下这些内容。

## 36:14

Alors, il faut que je fasse attention, parce que tout à l'heure,. Est--ce que ça va— Ça ne devraitit pas gêner. Alors,. Donc on passe sur du TD, normalement je crois que j'ai interverti l'ordre des exercices, je me su suis dit que c'était mieux de commencer par celui-là. Et donc on va s'intéresser—

**页面中文译文**

那么，我得注意，因为刚才……这应该不会有问题。那么……所以我们开始做习题课，正常来说，我想我把练习的顺序弄反了，我觉得先从这个开始会更好。接下来我们将关注——

## 37:11

Aux m mouvements du glissement simple. Alors, on vous pose un milieu— Dans le repère cartésien, donc matérialisé par le repère E1, E2, E3, on va le faire dans cette direction, avec votre origine, pour un point M de coordonnées x1, x2, x3,. On va exprimer le champ de vitesse— De chacun de ces points M, sous cette forme.

**页面中文译文**

对于简单滑动运动。现在，我们设定一个介质——在笛卡尔坐标系中，用基向量E1、E2、E3表示，我们将在这个方向上进行，以原点为参考，对于坐标为x1、x2、x3的点M。我们将以这种形式表达每个点M的速度场。

## 37:49

Donc la vitesse au point M, elle peut s'écrire sous cette forme, donc α fois le vecteur unitaire E1, fois— C'est Le produit scalaire entre E2 et et E1. Alors, c'est une manière un petit peu déguisée de faire apparaître ici— Si vous prenez ce vecteur OM et que vous en—— que vous allez extraire, que vous faites le produit scalaire avec.

**页面中文译文**

因此，点M处的速度可以写成这种形式，即α乘以单位向量E1，再乘以——这是E2和E1之间的点积。这是一种稍微隐晦的方式来表达这里的内容——如果你取这个向量OM，然后对它进行——对它做点积的话。

## 38:27

Ce vecteur unitaire E2, c'est tout simplement— La coordonnée x2. En réalité, c'est une manière un petit peu sournoise de vous écrire le champ de de vitesse sous cette forme. Alors, si on regarde ça comme ça, on se dit, on peut déjà essayer de se représenter le champ de vitesse, ok, c'est un champ de vitesse qui est uniquement orienté dans cette direction, dans la direction 1, horizontale, et il dépend de l'espace, mais ça ne dépend que de la coordonnée x2, qui est plutôt verticale.

**页面中文译文**

这个单位向量E2，实际上就是——坐标x2。实际上，这是一种稍微有点隐晦的方式来表示速度场。这样看的话，我们可以尝试去想象速度场，好吧，这是一个仅沿着第1方向（水平方向）定向的速度场，并且它依赖于空间，但只依赖于垂直方向的坐标x2。

## 38:52

Et donc ça représente bien un mouvement de glissement simple, parce que plus les particules vont être éloignées de l'axe des abscisses, plus elles vont se déplalacer rapidement dans cette direction, et si elles sont sous l'origine, elles se déplacent dans celle-là. Et donc vous retrouvez bien ce qu'on appelle le mouvement de glissement simple, où vous avez des couches de particules qui glissent les les unes par rapport aux autres.

**页面中文译文**

这确实代表了一种简单的滑动运动，因为粒子离横轴越远，它们在该方向上的移动速度就越快；如果它们位于原点以下，则向相反方向移动。因此，这正是我们所说的简单滑动运动，即粒子层相互滑动。

## 39:25

De manière relative. À chaque fois que vous allez sur une couche qui est un peu plus haute, les particules se déplacent plus vite dans une seule direction. Et donc on note que α est une constante positive. Alors, bon, c'est une question un peu classique, c'est de retrouver les trajectoires et les lignes de courant de ce mouvement.

**页面中文译文**

相对而言，每当你进入一个稍高的层次时，粒子会以更快的速度沿单一方向移动。因此，我们注意到α是一个正常数。那么，这就是一个比较经典的问题，即找出该运动的轨迹和流线。

## 40:22

Donc ça permet de réviser— Ce que c'est qu'une trajectoire et une ligne de courant. Mais dans ces cas-là, la première chose à vérifier, vous voyez qu'on est dans une description eulérienne,. Sur— Est-ce que çaa passera mieux? Dans la description, elle est eulérienne, parce qu'on vous a donné la forme du champ de vitesse en fonction des coordonnées actualisées du mouvement.

**页面中文译文**

所以这有助于复习——什么是轨迹和流线。但在这些情况下，首先要检查的是，你们看到我们是在欧拉描述中。这个会不会更清楚一些？在这种描述中，它是欧拉描述，因为给出了速度场的形式，作为运动的更新坐标的函数。

## 40:54

Quels caractéristiques on vient de voir les caractéristiques des écoulements? Quelles caractéristiques on voit apparaître très rapidement sur ce type d'écoulement? On On a un mouvement ou un écoulement, on parle plutôt d'écoulement quand on. En représentation eulérienne, on voit qu'il est stationnaire.re,

**页面中文译文**

我们刚刚看到了流动的哪些特征？这种类型的流动中很快出现了哪些特征？当我们谈论运动或流动时，更倾向于称之为流动。在欧拉描述中，我们看到它是稳定的。

## 41:25

Ok, parce que le champ de vitesse qui est sous forme e. Il est— Là, on voit qu'il est indépendant du temps, mais il est exprimé en fonction des coordonnées eulériennes, si je calcule sa dérivée par rapport au temps, elle est nulle. Et dans ces cas-là,. Vous avez une équivalence entre les lignes de courant et les trajectoires.

**页面中文译文**

好的，因为速度场是以欧拉坐标的形式表示的。这里我们看到它与时间无关，但它是以欧拉坐标表示的，如果我对它关于时间求导，导数为零。在这种情况下，流线和轨迹是等价的。

## 41:43

Ça représente exactement les mêmesmes les. Doncc en réalité, soit vous cherchez les lignes de courant, soit vous cherchez les trajectoires, et vous avez tout ce qu'il faut. En gros, nous, on va plutôt s'intéresser à récupérer les trajectoires, c'est souvent ce qui est le plus simple. Donc—

**页面中文译文**

这实际上完全相同。实际上，要么你寻找流线，要么你寻找轨迹，而你拥有一切所需。基本上，我们更倾向于获取轨迹，因为这通常是最简单的。所以——

## 42:27

Retrouver les trajectoires— Ça équivaut à passer— En représentation Lagrangienne. En Lagrang Donc on se souvient, ça ve vout dire que j'ai le champ de vitesse— Ça veut dire que j'ai les dx—— Ça veut dire que j'ai le— Qui dépend de M, en fait, c'est comme si j'avais x1, x2, et x3, sous forme d'un vecteur.ur, ok

**页面中文译文**

找回轨迹——这相当于采用拉格朗日表示法。用拉格朗日方法，所以我们记得，这意味着我有速度场——这意味着我有dx——这意味着我有一个依赖于M的量，实际上，就好像我有x1、x2和x3，以向量的形式存在。好的。

## 43:09

Et je vois que c'est égal à cette quantité-là. Donc c'est α fois x2, 0 et 0, dans ma base— E1, E2, E3. E1, E2, E3. Dès qu'on pose ça sous cette forme, ça me me fait fait un système déc quoisif,. Avec comme condition initiale, donc CI comme condition initiale,. X1 de t est égal de t = 0 sous cette forme.

**页面中文译文**

我看到它等于那个量。所以这是α乘以x2，0和0，在我的基底——E1，E2，E3中。E1，E2，E3。一旦我们以这种形式表示，它就给我构建了一个微分方程系统，初始条件是，作为初始条件，t=0时的x1满足这个形式。

## 43:48

C'est égal à X1, les coordonnées initiales, pareil pour x2,. X3. Je résous— Et là, la résolution, elle est assez rapide, vous voyez que vous avez trois équations,: x1 qui est égal à αx2, x2 qui est égal égal à 0, et x3 qui est égal à 0. On va commencer par intégrer les plus simples.ples, ok

**页面中文译文**

这等于X1，即初始坐标，x2和x3也是一样。我来解这个方程——这里的求解相当快，你们可以看到有三个方程：x1等于αx2，x2等于0，x3等于0。我们先从最简单的开始积分，好吗？

## 44:47

Qui ont plutôt tendance à nous dire que x3 et x2 sont des constantes.es. Je vais mettre c3. Et une fois que j'ai ça,. Sans connaître— Bon, Je peux déjjà utiliser mes conditions initiales, si x2 et x3 sont égaux à des constantes, forcément c'est égal aux coordonnées initiales x2 et x3. Là, j'utilise mes CI, ça veut dire que c'est égal à x2 de t égal à 0, pareil et.

**页面中文译文**

他们更倾向于告诉我们，x3 和 x2 是常数。我将设为 c3。一旦确定了这个，虽然不知道——好，我已经可以使用我的初始条件了，如果 x2 和 x3 等于常数，那么它们必然等于初始坐标 x2 和 x3。在这里，我使用我的初始条件，这意味着它们等于 t=0 时的 x2，情况也是一样。

## 45:49

Donc c'est égal à x2, c'est égal à x3. Maintenant que j'ai ça, je vais pouvoir remplacer mon petit x2 ici parce qu'il est déjà connu. Ce qui veut dire que— Je peux dire que x1, c c'était égal à αx2, soit α. Et donc là, je vais pouvoir encore une fois intégrer— Ce qui veut dire que du coup, je vais avoir x1, en fait ça veut dire que la dérivée,e, elle dépend de la coordonnée initiale, x2, et donc ça va être égal à α fois x2 fois le temps, plus une constante c1.

**页面中文译文**

所以它等于 x2，也等于 x3。现在我有了这个，我就可以用已知的 x2 来替换这里的小 x2。这意味着——我可以说 x1 等于 α 乘以 x2，也就是 α。所以这里我可以再次积分——这意味着，实际上 x1 的导数依赖于初始坐标 x2，因此它等于 α 乘以 x2 乘以时间，加上一个常数 c1。

## 46:27

Je vais peut-être— Ça, ça, ça, c'est des constantes. Les constantes d'intégration. J'utilise mon autre condition initiale, qui est que x1 de t égal à 0, c'est égal à x1, et donc ça veut dire que si je remplace là-dedans, ça veut dire que c'est égal à αx2 fois 0, plus c1. Ce qui est égal à c1.

**页面中文译文**

我可能会——这些，这些，这些，都是常数。积分常数。我用另一个初始条件，即当 t 等于 0 时，x1 等于 x1，所以这意味着如果我把它代进去，就等于 αx2 乘以 0，加上 c1，也就是等于 c1。

## 47:02

Et donc je viens égaliter entre c1 et x1. Du coup, j'ai bien x1 de t qui est égal à αx2 fois le temps, plus x1, x2 de t c'est égal à x2, et x3 de t qui est égal à x1. J'ai ma description Lagrangienne du mouvement, j'ai exprimé les coordonnées actualisées de mes particules, en fonction du temps et des coordonnées initiales de cette même particule.

**页面中文译文**

所以我得到了 c1 和 x1 之间的等式。于是，我得出 x1 关于时间 t 的导数等于 α 乘以 x2 再乘以时间，加上 x1；x2 关于时间 t 的导数等于 x2；x3 关于时间 t 的导数等于 x1。我得到了运动的拉格朗日描述，表达了粒子的更新坐标，作为时间和该粒子初始坐标的函数。

## 47:53

Ça, c'était la première étape, c'est une manière de réviser ce qu'on avait vu— La première fois, et donc ce qu'on peut faire maintenant, c'est s'intéresser— À quoi ressemble la transformée— D'un carré de côté— État. Ensuite, avec Avec, par exemple, not. Que c'est le carré O à 0, B0, C0, avec du coup O à 0 qui est égal à état E1, et OB0 qui est égal à état E2.

**页面中文译文**

这是第一步，这是一种复习我们第一次看到内容的方法——所以我们现在可以关注的是——一个边长为——某状态的正方形的变换是什么样的。接着，例如，考虑点O在坐标0，B0，C0，其中O在坐标0对应状态E1，OB0对应状态E2。

## 49:13

Ce qui veut dire que— O à 0, B0, et C0. Avec des angles bien droits part partout,. Alors,. Ça, l'application qui permet de passer du coup de x2 des xi à xi de t, c'est mon application φ, la transformée. Ce qui me permet de transformer mon milieu. De mettre à jour à l'instant. Don Donc, si je veux voir comment ce carré, dans Dans sa configurationation initiale, va être transformé, j'ai tout simplement besoin de faire le calcul de OA en appliliququant la fonction φ,. Alors là, on voit que ici, elle est ind indépendante du temps, paron.

**页面中文译文**

这意味着——点O在0点，B0和C0。各个角度都是直角。那么，这个应用程序可以将xi的两倍转换为t时刻的xi，这就是我的变换函数φ。它使我能够转换我的空间，并实时更新。因此，如果我想看到这个正方形在初始配置下如何被变换，我只需要计算OA并应用函数φ。这里可以看到，它与时间无关。

## 49:43

Pas indépendante du temps, c'est le tenseur de vitesse qui est indépendant du temps. Donc, à l'instant t, je vais donc l'appliquer sur, à l'instant t, pour le vecteur OA0. Donc, si j'injecte ça dans cette application-là, en réalité, qu'est-ce que j'obtiens?? Pour la coordonnée x1, j'injecte du coup.

**页面中文译文**

速度张量是不随时间变化的。因此，在时刻 t，我将其应用于时刻 t 的向量 OA0。那么，如果我将其代入这个映射，实际上我得到的是什么呢？对于坐标 x1，我就代入了。

## 50:11

Ce vecteur-là, c'est égal à état 0 et 0, j'injecte ces trois coordonnées à la place de x1, x2 et x3. Ce qui va me donner toujours ici— je vais avoir toujours état 0, et encore 0. Je vois que— C'est la La transformée, quand je l'applique sur ce point-là, ça ne change pas la position de ce point.

**页面中文译文**

这个向量等于状态0和0，我将这三个坐标代入x1、x2和x3的位置。这样我这里得到的仍然是状态0，还是0。我看到——这是变换，当我把它应用到这个点上时，点的位置没有改变。

## 50:43

Elle ne varie pas. De toute façon, je l'aurais très bien pu le voir, parce que pour un point M pour lequel la coordonnée x2 est nulle, la vitesse est nulle. Si le champ de vitesse est nul, les particules ne bougent pas. En gros, on pour pourrait conclure que toutes les particules qui sont sur l'axe des abscisses, sur le plan avec x2 est égal à 0, toutesutes ces particules ne bougent pas.

**页面中文译文**

它不变化。无论如何，我完全可以看到这一点，因为对于一个点M，其坐标x₂为零时，速度也为零。如果速度场为零，粒子就不会移动。基本上，我们可以得出结论，所有位于横轴上、即x₂等于0的平面上的粒子，所有这些粒子都不会移动。

## 51:09

Bon, je peux le faire maintenant pour mon point B, alors le point B, c'est différent cette fois, c'est la deuxième coordonnée qui est égale à état, donc si j'applique cette même fonction sur ce nouveau vecteur, là ça va changer les choses. Parce que là, je vais avoir 0, mais là, je vais avoir état et 0.

**页面中文译文**

好，我现在可以为我的点B做这件事，点B这次不同，第二个坐标等于“état”，所以如果我对这个新向量应用同样的函数，情况就会改变。因为这里我会得到0，但这里我会得到“état”和0。

## 52:13

Donc, en réalité, je vais avoir αt fois état, et. État et 0. Donc là, je peux bien noter que— Le point B, je. Vais faire pareil petit à petit. Là, j'ai aussi mon point A, par contre mon point B— Il va bouger. Il était en B0, il a bougé, du coup de αt. Fois état. Et en faisant pareil avec le point C, donc φ de t égale C0, alors OC0, je vais le noter là, c'était tout simplement état et 0, comme coordonnées, il était là., Bon,

**页面中文译文**

所以，实际上，我将有 αt 乘以状态，和状态为 0。所以这里，我可以很好地记下——点 B，我会一点一点地做同样的事情。这里，我也有我的点 A，但我的点 B 会移动。它原本在 B0，移动了 αt 乘以状态。对点 C 做同样的操作，所以 φ(t) 等于 C0，那么 OC0，我会记在那里，它的坐标就是状态和 0，就在那里。好了，

## 53:03

Bon, si j'injecte ça, à la fin, je vais obtenir état. Facteur de αt plus— pardon, αt plus 1, état et puis 0. Donc, en réalité, la se positionner un peu plus par là, avec le même déplacement en réalité. Donc là, j'ai mon point B, et là, j'ai mon point C. Et donc, en partant de ce carré, du coup, pour le point O, on savait qu'il n'allait pas bouger, mais du coup, dans la transformée,.

**页面中文译文**

好，如果我注入这个，最后我会得到状态。因子是αt加——抱歉，αt加1，状态，然后是0。所以，实际上，这里稍微往那边定位一点，实际上是相同的位移。这里是我的点B，那里是我的点C。因此，从这个正方形出发，对于点O，我们知道它不会移动，但在变换中，...

## 53:35

Avec ce type de cinématique, vous voyez que j'ai fait glisser mon milieu d'une configuration qui correspondait à un carré, à un espèce de trapèze, de. Parallélogramammme même, carrément. Avec les différentes couches de particules qui ont glissé les unes par rapport aux autres. Si vous matérialisez les différentes couches de particules comme ça, vous allez retrouver, elles sont juste légèrement décalées comme ça.

**页面中文译文**

通过这种类型的运动学，你可以看到我将中间部分从一个正方形的配置滑动到了一个类似梯形，甚至是平行四边形的形状。不同的粒子层相互滑动。如果你把这些不同的粒子层这样具体化，你会发现它们只是稍微错开了一点。

## 54:04

Voilà ce que c'est que le mouvement de glissement simple. Alors après, une fois qu'on— Qu'on a pu établir la représentation de la grangène, maintenant on va pouvoir essayer d'en extraire des informations. Là, on était plus dans l'étude, du mouvement. Alors, on peut le refaire en 3D, bon, ça ne change pas grand-chose,.

**页面中文译文**

这就是简单滑移运动的含义。接下来，一旦我们建立了晶格的表示，现在我们就可以尝试从中提取信息。这里我们更多地是在研究运动。我们也可以用三维方式重新做一遍，嗯，这并不会有太大变化。

## 54:43

Vous pourrez voir ça dans dans le corrigé. À la suite, on vous demande de rappeler la définition du tenseur de transformation.ation, alorsors oui, c'est plutôt le tenseur gradient de transformation,ation, il faut que je rectifie ça. Donc, le tenseur grent. De transformation, ou l'opérateur gradient de transformation,.

**页面中文译文**

您可以在答案解析中看到这一点。接下来，我们要求您回顾变换张量的定义。是的，应该是变换梯度张量，我需要更正这一点。所以，是变换梯度张量，或者变换梯度算子。

## 55:14

Donc, on peut le noter avec un F double barre, comme ça. Et donc, ça correspond en fait à la dérivée spatiale de la fonctionnel φ,. Donc, on dérive par rapport à l'espace, et vu qu'on est passé en représentation de la grangène, on va dériver par rapport aux coordonnées actualisées. Donc, on dérive par rapport à. Au vecteur OM0.

**页面中文译文**

因此，我们可以用双杠F来表示它，就像这样。实际上，这对应于泛函φ的空间导数。因此，我们对空间变量求导，由于我们已经转换到了格点表示，所以我们将对更新后的坐标求导。也就是说，我们对向量OM0求导。

## 55:51

Donc, on peut le remettre sous la forme gradient effectué par rapport à, aux coordonnées M0,. De la fonctionnel φ. Une autre manière de l'écrire, c'est. L'er. Des coordonnées actualisées par rapport aux coordonnées initiales, qui sont portées par le produit tensoriel, donc la base E une_ g.

**页面中文译文**

因此，可以将其重新表示为关于坐标 M0 的梯度，即泛函 φ 的梯度。另一种表达方式是，将更新后的坐标相对于初始坐标表示，这通过张量积实现，因此基底为 E 一_ g。

## 56:53

Là, dans ces cas-là, vous voyez ça, ça représente unee. Ligne, et là, colonne. Et donc là, si on l'applique ici, ça veut dire qu'ici on devrait calculer pour la première coordonnée c'est la. Dérivée partielle de la coordonnée actualisée x1 par rapport à x1, toujours sur la même ligne, je vais toujours réutiliser la même composante, donc d petit x1 par rapport à x2, troisième colonne de la même ligne, je dérive par les différentes composantes.

**页面中文译文**

在这种情况下，你看到这里表示一行，这里表示一列。因此，如果我们将其应用到这里，这意味着我们应该计算第一坐标，即更新后的坐标x1关于x1的偏导数，仍然在同一行，我将继续使用相同的分量，所以是x1关于x2的偏导数，在同一行的第三列，我对不同的分量进行求导。

## 57:22

Le j là, c'est les colonnes, c'est les composantes par rapport auxquelles je vais dériver. Deuxième ligne de ma matrice qui représente mon tenseur du second ordre, je dérive cette fois une autrere composante de mon application vectorielle φ. Donc dx2 par rapport à x1, d petit x2 par rapport à x2, dx2 par rapport à x3, et ainsi de sue.

**页面中文译文**

这里的 j 是列，表示我将要对其求导的分量。矩阵的第二行代表我的二阶张量，这次我对向量函数 φ 的另一个分量求导。因此是对 x1 求导的 dx2，对 x2 求导的 dx2，对 x3 求导的 dx2，依此类推。

## 58:10

Troisième ligne, je dérive cette composante-là par rapport à la composante 11,, par rapportport à la composante 2, par rapport à la composante 3. En notation compacte, j'aurais très bien pu mettre x1 1, x1, 2, x1, 3. Et ainsi de suite. Et donc, si on procède au calcul,. Il n'y a rien de très compliqué, ça, si je dérive par rapport à x1, il n'y a que ce terme-là qui va persister.

**页面中文译文**

第三行，我对该分量分别关于分量1、分量2和分量3求导。用简洁的符号表示，我完全可以写成x1,1，x1,2，x1,3，依此类推。因此，如果进行计算，其实并不复杂。如果我对x1求导，只有这一项会保留下来。

## 58:47

Dans l'équation.ation, Donc, je vais garder un 1 pour cette composante-là., Ensuite, ici, je dérive cette même expression, mais par rapport à x2, il va me rester αt, et si je reprends cette même expression que je dérive par rapport à x3, c'est 0. Ensuite, si je passe à ces deux composantes, je vois qu'elles sont à chaque fois uniquement fonction, pardon, d'une seule composante,.

**页面中文译文**

在方程中，所以我会为这一分量保留1。接着，在这里，我对同一个表达式关于x2求导，结果是αt；如果我对同一个表达式关于x3求导，结果是0。然后，如果我看这两个分量，我发现它们每次仅仅是单一分量的函数。

## 59:40

Et donc, si je complète le calcul, ça me donne cette forme-là. Don Donc, vous voyez que vous avez l'identité plus une. Non nul ici, qui caractérise en fait la définition, enfin, le mouvement de glissement. Je vais vous passer à la suite. Donc, on vous demande ensuite la définition. Du tenseur de déformation de Greenrim-Lagrange,.

**页面中文译文**

所以，如果我完成计算，就会得到这个形式。你们看到这里有一个非零的单位矩阵，它实际上表征了滑移运动的定义。接下来我将继续讲解。然后，接下来会要求你们给出格林-拉格朗日应变张量的定义。

## 60:09

Alors, on peut maintenant qu'on est là, pet petiteite question, est-ce que que vous vous souvenez quelle doit être la dimension de ce type de, la grandeur physique? Elle s'exprime en quelle unité, cette quantité? Reprenez la définition. Vous voyez que vous dérivez. Par rapport à l'espace, une quantité qui est.

**页面中文译文**

那么，现在我们既然在这里，可以问一个小问题：你们还记得这种物理量的量纲应该是什么吗？它用什么单位来表示？请回顾一下定义。你们会发现它是相对于空间导出的一个量。

## 60:42

C'est une distance, une longueur. Donc, des mètres que vous dérivez par rapport à des mètres où vous avez quelque chose qui est sans unitéité, c'est la dimensionnelle, ok? Alors, du coup, quelle unité pour α? α, c'est en second moins 1, du coup. Pour retomber sur cette. Donc là, cette fois,is, on veut définir un tenseur de déformation de Green-Lagrange, c.

**页面中文译文**

这是一段距离，一段长度。因此，你用米作为基准，而你所得到的东西是无量纲的，这是量纲的，对吧？那么，α的单位是什么？α的单位是秒的负一次方。为了回到这个问题上。这一次，我们想定义一个格林-拉格朗日应变张量，c。

## 61:52

Qu'on note... E, c. Et il représente l'écart quadratique,. Relatif dess. Et il représente également les variations d'angle... Des fibibres, enfin, ou des lignes qui étaient dans dans une une position, enin. Dans une configuration initiale, elles étaient orientées sel selon une cer certataine manière, et donc son expression, c'est un demi2 de f transposé fois f, auquel on retire l'identité.,

**页面中文译文**

记作……E，c。它表示相对的均方差。同时，它也表示纤维的角度变化，或者说是那些在初始配置中处于某种特定位置的线条的角度变化。它们最初以某种确定的方式定向，因此其表达式是f的转置乘以f再乘以二分之一，然后减去单位矩阵。

## 62:41

Et pour note, on peut retrouver que ici, là, vous avez le t tenseur de dilatation de Cauchy-Green. Bon, si on calcule son expression, alors on peut commencer par calculer c, de manière... Donc ça veut dire qu'on fait le produit... De f transposé fois f. Ça veut dire qu'on fait fj. I... Fo Fois f.

**页面中文译文**

作为备注，我们可以看到这里，你们有考希-格林的膨胀张量。好，如果我们计算它的表达式，那么我们可以先计算c，以这种方式……这意味着我们做乘积……f的转置乘以f。这意味着我们做fj。I……乘以f。

## 63:18

Ji, en réalité. Quand vous faites un produit de deux matrices, si je les no note a et b, c'est a i j fois b ji i, ok ok? Bon, bah là, en gros, si on considère, on va mettre plutôt f ici, ok? Si a c'est égal à f transposé, ç ça veut dire que ça, vous pouvez le remplacer directement par f ji i.,

**页面中文译文**

实际上，当你计算两个矩阵的乘积时，如果我们把它们分别记为a和b，那么就是a的第i行第j列元素乘以b的第j行第i列元素，对吧？好，那么这里，基本上，如果我们考虑一下，我们这里用f来表示，好吗？如果a等于f的转置，这意味着你可以直接用f的第j行第i列元素来替代它。

## 63:53

Donc, en réalité, c'est le produit colonne par colonne de f avec lui-me. Au lieu de faire ligne colonne, vous faites colonne colonne. Donc, on reprend f, là, donc pour la composante 1, 1 de c, je vais prendre la colonne 1 fois la colonne 1. Et ainsi de suite. Bon, bah, colonne 1 fois colonne 1, ça va me faire 1 fois 1 plus 0 fois 0 plus 0 fois 0, eh bien, obtenir 1.

**页面中文译文**

所以，实际上，这是函数f与自身按列逐列相乘的结果。不是按行列相乘，而是按列列相乘。我们重新来看f，对于矩阵c的第1行第1列元素，我将取第1列乘以第1列。依此类推。好，第1列乘以第1列，就是1乘以1加0乘以0加0乘以0，结果是1。

## 64:29

Ens Ensuite, pour la composante 1 2, c'est la colonne 1 fois la colonne 2. Donc ça me fait 1 fois αt, plus 0 fois 1, plus 0 fois 0. Ok? Ensuite, pour la composante 1 3, je vais faire colonne 1 fois colonne 3, j'obtiens bien 0. Ok? Ens Ensuituite, colonne 1 fois colonne 2, je vais encore obtenir αt. De toute façon,

**页面中文译文**

然后，对于分量12，是第1列乘以第2列。所以是1乘以αt，加上0乘以1，再加上0乘以0。明白吗？接着，对于分量13，我将第1列乘以第3列，结果确实是0。明白吗？然后，第1列乘以第2列，我还会得到αt。无论如何，

## 64:56

on sait que c'est... pardon, que ces deux tenseurs qui sont symétriques, donc à partir du moment où j'ai la diagonale sup supérieure, j'ai pas besoin de m'embêter pour le reste. Alors, composante 2 2, je prends la colonne 2 fois la colonne 2. Voilà, cette fois, ça va me faire αt au carré plus 1.

**页面中文译文**

我们知道这是……抱歉，这两个张量是对称的，所以从我有了上三角对角线元素开始，我就不需要为其余部分费心了。那么，分量2 2，我取第2列乘以第2列。这样，这次会得到αt的平方加1。

## 65:29

Ensuite, 0 ici, et puis petit à petit, on arrive assez facilement à obtenir cette formule. Donc on voit qu'on a... Encore l'identité qui était là là, là, dans le tenseenseur c qui représente les dilatations, on a encore l'identité qui est présente. On a encore les 100 % de la configuration initiale qui sont là.

**页面中文译文**

然后，从这里开始，逐渐地，我们相当容易地得出这个公式。于是我们看到……张量c中表示膨胀的部分仍然包含单位矩阵。初始构型的100%依然存在。

## 65:57

Mais pour obtenir la déformation, je vois qu'il faut que j'enlève l'identité et que je divise par 2. Bon,on, bah du coup, j'obtiens bien... Je Je vais même pouvoir facer. Par αt, parce que si j'enlève l'identité, j'enlève les 3 1, là, je vois que j''ai tout qui est facteur de αt, et donc je peux mettretre ça sous cette forme, avec αt 0 0 0.

**页面中文译文**

但是为了得到变形，我发现必须去掉单位矩阵并除以2。好吧，那么，我确实得到了……我甚至可以用αt来表示，因为如果我去掉单位矩阵，也就是去掉三个1，我看到所有项都是αt的因子，所以我可以把它写成这种形式，带有αt 0 0 0。

## 66:26

Et là, d'une certaine manière, j'ai pas besoin d'indiquer le reste, parce que c'est symétrique. Donc éventuellement, vous pouvez préciser comme c'est symétrique, il n'y a pas besoin d'indiquer la diagonale inférieure. Donc une fois que vous avez ce tenseur de déformation, on peut rappeler que c.

**页面中文译文**

在这里，从某种意义上说，我不需要指出其余部分，因为它是对称的。因此，您可以说明由于它是对称的，不需要指出下三角部分。一旦你有了这个应变张量，我们可以回顾一下。

## 67:08

Là, ces trois composantes qui. C'est l'écart quadratique relatif. Des longueurs de. Selon le i, donc dans dans la direction 1, je vois que j'ai pas de déformation. Dans la direction 2, je vois que j'ai une une légère déformation. Et pour les composantes là, c'est pareil, donc c'est symétrique.

**页面中文译文**

这里，这三个分量。它是相对长度的均方根误差。根据i的不同，在方向1上，我看到没有变形。在方向2上，我看到有轻微的变形。对于这些分量也是一样的，因此是对称的。

## 68:10

Là, ça représente les variations d'angle. Orienté initialement. Le i est. Le ji. Donc pour vo vous le. R. Spécifié, je garde mon petit schéma là,. Au départ, typiquement, vous aviez... Les fibres, qui étaient orientées suivant cette direction e1, et une fibre orientée suivant cette direction. Dans la configuration déformée là, ça reste selon cette direction.,

**页面中文译文**

这里表示角度的变化。最初的方向。i 是。ji 是。所以对于 vo 你有。R。指定的，我保留我的小示意图。起初，通常你有……纤维沿着这个 e1 方向排列，还有一根纤维沿着这个方向排列。在变形后的配置中，它仍然保持这个方向。

## 68:42

Lorsque vous avez déformé, par contre, celle-là, elle se retrouve orientée comme ça. Donc vous êtes passé d'un angle droit... À un angle qui n'est plus droit, ok? Ces deux fibres, elles sont plus orthogonales, et donc vous avez eu un glissement, justement, vous avez eu une variation d'angle. C'est ce que représente cette coordonnée-là. Vous voyez qu'entre les directions 2 1 et 2 3, il n'y a pas de variation, en réalité.

**页面中文译文**

当你变形时，这个方向就会变成这样。所以你从一个直角变成了一个不再是直角的角度，好吗？这两根纤维不再是正交的，因此发生了滑移，确切地说，就是角度发生了变化。这就是那个坐标所表示的。你会看到，在方向21和23之间，实际上没有变化。

## 69:31

Et pareil, entre e2 et e3, il n'y a que dans le plan e1 e2 que vous avez une variation de l'angle des fibres, ok? Alors, par la suite, on vous demande de déterminer les déformations de. Principales, pardon,. Et leurs directions. Est-ce que vous voyez... est-ce que vous arrivez à anticiper savoir ce que ça représente,it et puis on fera notre première pause.

**页面中文译文**

同样地，在e2和e3之间，只有在e1 e2平面内，纤维的角度才会发生变化，好吗？接下来，我们会要求你们确定主应变及其方向。你们能理解……能预见这代表什么吗？然后我们将进行第一次休息。

## 69:56

D'après vous, qu'est-ce que c'est qu'une déformation principale? Qu'est-ce que c'est qu'uneune dire direction principale de déformation? C'est Ouais, les déformations principales, c'est les valeurs propres de. Votrere tenseur qui représente la déformation. Et les directions, c'est les vecteurs propres.

**页面中文译文**

在您看来，什么是主应变？什么是主应变的主方向？是的，主应变是表示变形的张量的特征值，而主方向则是特征向量。

## 70:31

Donc en gros, ce qu'on vous demande de faire là, c'est de diagonaliser. Et diagonaliser, c'est résoudre l'équation déterminant de epsilon moins lambda fois l'identité, égale à 0. Et Et vous déterminez les trois valeurs lambda. Qui correspondent. Donc ça, c'est ce qui va vous donner les. Déformations principales.

**页面中文译文**

所以，基本上，我们要求你们做的是对角化。对角化就是解方程：行列式（ε 减 λ 乘以单位矩阵）等于零。然后你们确定对应的三个 λ 值。这些 λ 值就是主变形。

## 71:25

Et pour les directions, il faut résoudre les équations qui correspondent, en fait,. À epsilon appliqué sur. Un vecteur ni,. Égale à l lambambda fois ni. Ce qui équivaut à epsilon moins lambda i. Appliqué sur ni, égale le vecteur ni. C la même chose. Et ça, ça va vous donner les directions principales.

**页面中文译文**

对于方向，需要解相应的方程。实际上，就是将应变作用于向量 \( \mathbf{n}_i \)，等于 \( \lambda \) 乘以 \( \mathbf{n}_i \)。这相当于 \( (\epsilon - \lambda_i) \) 作用于 \( \mathbf{n}_i \) 等于零向量。这是同一个问题，这将给出主方向。

## 72:01

Bon, là, si vous l'appliquez, vous allez tomber sur, très rapidement, sur un. Sur la résolution d'un trinôme. Ça, c'est assez simple à faire. Là, dans ces cas-là, en gros, il va falloir déterminer les trois composantes des vecteurs ni. Donc ça veut dire qu'a priori, voz. Trois vecteurs à déterminer, avec chacun trois composantes,.

**页面中文译文**

好，如果你应用它，很快就会遇到一个问题。关于二次三项式的求解。这其实相当简单。在这种情况下，基本上需要确定向量ni的三个分量。也就是说，原则上需要确定三个向量，每个向量有三个分量。

## 72:47

Donc a priori, 9 inconnues à déterminer. Mais comment vous pouvez réduire le problème?? Normalement, cette base de vecteurs principaux, des vecteurs propres, elle est censée être orthonormée. Donc vous êtes censé avoir n. 3 Qui est égal à n1 vectoriel n2. Donc à partir du moment où vous avez déterminé les deux premiers vecteurs, n1 et n2, c'est bon. En plus, le vecteururs stabes,le, alors i3, il est bien équivalent... On On peut peut voir directement.

**页面中文译文**

所以，原则上，有9个未知数需要确定。但你们怎么能简化这个问题呢？通常，这组主向量，也就是特征向量，应该是正交归一的。因此，你应该有n3等于n1与n2的叉积。所以，一旦你确定了前两个向量n1和n2，就可以了。此外，稳定向量i3也是等价的……我们可以直接看到。

## 75:11

On a une valeur propre qui est nulle, et associée à la... au vecteur propre e3. Ett. on va pouvoir faire une une petite pause dès maintenant. Et on on va faire un petit quiz à la retrouver. Sur votre ch Au bout du。 那问题是你那边多少个人呢? 我那边6个人。 我说6个人? 算你吗?

**页面中文译文**

我们有一个特征值为零，并且与特征向量e3相关联。好了，我们现在可以稍作休息。接下来我们将进行一个小测验来回顾一下。你的那边有多少人？我这边有6个人。我说6个人？算上你吗？

## 75:47

算上我。 那我们怎么办? 强浩宇有分? 然后你再加4个人。 就10个人。 就10个人。 不是啊，就是抱团。 抱团? 哦，你们抱团。 你们已经抱了吗? 没抱呢。 没抱?  O当天的小团。La longueur au carré dans la configuration actu InInitial.itiiti Alors, ça, je peux le ré réécrire comme étant « la transformée à l'instant T de DM0 ».

**页面中文译文**

算上我，那我们怎么办？强浩宇有分吗？然后你再加四个人，就是十个人。不是啊，就是抱团。抱团？哦，你们抱团。你们已经抱团了吗？还没抱呢。还没抱？当天的小团体。当前配置中的平方长度。在初始状态。那么，这个我可以重新写成“DM0在时刻T的变换”。

## 76:36

OK. Bon, ça, ça ne change pas. Si je veux cette quantité-là, alors, euh, je. La nor normeme de D DM0 ou de DM, peu importe, je peux l'écrire comme étant le produit de la transposée de DM0 fois DM0, et. OK, et donc pour DM, ben en fait ça va être. Voilà, je Je vais l'écrire comme je peux l'écrirere comme comme ça.

**页面中文译文**

好的，这个是不变的。如果我想要这个数量，那么，呃，我。D DM0 或 DM 的范数，无论哪一个，我都可以写成 DM0 的转置乘以 DM0 的乘积。好的，那么对于 DM，实际上也是这样。就是这样，我会把它写成这样。

## 77:24

Si tu veuxux, Tu mets l'autre manière de l'écrire, ce sera plus commode. On peut également écrire que DM, c'est égal à F fois DM0., Souvenez--vous, hein, de. Mon tenseur gradient de la transformation, c'est égal à D2M sur D2M0, et donc si j'intègre ça, j'ai bien F fois TM0, qui est égal à Fis.

**页面中文译文**

如果你愿意，可以用另一种写法，这样会更方便。我们也可以写成 DM 等于 F 乘以 DM0。记住，我的变换梯度张量等于 D²M 除以 D²M0，因此如果我对它积分，就得到 F 乘以 TM0，也就是 Fis。

## 78:28

D2M0, qui qui est égal à D2M.M Donc, appliqué comme ça, ben ça veut dire que j'ai F fois transposée de DM0. F fois DM0. Le tout transposé, fois F. DM0. Bon, ça, je vais le gardarder comme ça. Cette partie-là, qu'est-ce que je vais en faire ? Ben je vais développer, quand je fais la transposée d'un produit matrice-vecteur ou matrice fois matrice, ben j'intervertis le distribué de la transposée en changeant l'ordre en intervertissant l'ordre. Donc ça veut dire que j'ai DM0 transposée fois F transposée. Et là, je prends la même chose ici, vo.

**页面中文译文**

D2M0，即等于D2M乘以M。因此，应用到这里，意味着我有F乘以DM0的转置，F乘以DM0，整体转置，再乘以F。DM0。好，这部分我先保留这样。那这部分我该怎么处理呢？当我对矩阵-向量乘积或矩阵乘矩阵做转置时，我会交换转置的分配顺序，也就是颠倒顺序。所以这意味着我有DM0的转置乘以F的转置。这里我取相同的东西，就是这样。

## 79:05

Donc si je développe complètement, ça me fait DM0 transposée fois F transposée fois F, ici en réalité c. La même chose ici, et donc je rassemble ces deux termes ici.i. Ça résultete, qu'est-ce que je retrouve ? Je retrouve mon vecteur... mon vecteur, mon tenseur de dilatation de Cauchy-Gréneau. O

**页面中文译文**

所以如果我完全展开，它变成了DM0的转置乘以F的转置再乘以F，这里实际上是C。同样的情况也出现在这里，因此我将这两个项合并在这里。结果是什么呢？我得到了我的向量……我的张量，考希-格雷诺的膨胀张量。

## 79:48

Donc je peux relier la longueur au carré, actuelle, à ma longueur au carré initiale, au travers de ce tenseur de dilatation. Très bien. Mais ce que je veux, moi, c'est l'écart entre les deux, donc c'est la longueur au carré, donc mon accroissement lambda de DM0, ben du coup c'est l'écart entre les deux.

**页面中文译文**

所以我可以通过这个伸长张量，将当前的长度平方与初始的长度平方联系起来。很好。但我想要的是两者之间的差异，也就是长度的平方，因此我的增量λ的DM0，实际上就是两者之间的差值。

## 80:24

Donc je peux l'écrire comme étant DM0 fois C moins l'identité, fois DM0. Je fais l'écart entre les deux, j'ai ça moins ça, j'aurais très bien pu glisser le. Entre les deux une une matriceice ident identité. Donc si je fais l'écart entre les deux, je peux factoriser, ça me donne cette forme-là, et donc du coup je vais pouvoir faire apparaître so soit mon t tenseur de dilatation...

**页面中文译文**

所以我可以把它写成 DM0 乘以 C 减去单位矩阵，再乘以 DM0。我计算两者之间的差值，就是这个减那个，我本来也可以在两者之间插入一个单位矩阵。所以如果我计算两者之间的差值，我可以进行因式分解，得到这样的形式，因此我就能够显现出我的张量 t 的膨胀部分……

## 81:32

Que j'utilise assez peu, hein, finalement, en réalité,. Mais je vais plutôt le mettre sous cette forme-là, avec un petit facteur 2 ici,. Si je fais apparaître çaa ici,. De manière un petit peu artificielle, je fais apparaître mon tenseur de déformation. Donc j'arrive bien à faire le lien entre l'accroissement du carré de la longueur du vecteur ici, et.

**页面中文译文**

实际上我用得不多，不过我会把它写成这样，加上这里的一个小因子2。如果我在这里稍微人为地引入它，我就能引出我的应变张量。因此，我能够很好地将这里向量长度平方的增量联系起来。

## 82:07

Mon tenseur de déformation de Greene-Lage. Donc c'est bien ce qu'on retrouve ici. Alors, maintenant que je peux réécrire la forme de DM0, c'est égal à DL0 fois le vecteur E,. DL0 fois E, donc ça veut dire que c'est cosinus phi sinus phi 0. Ben je peux, je peux le calculer, ce que ça donne sur cette quantité-l.

**页面中文译文**

格林-拉格变形张量。因此，这正是我们在这里看到的。现在我可以重新写出 \( \Delta M_0 \) 的形式，它等于 \( \Delta L_0 \) 乘以向量 \( E \)。\( \Delta L_0 \) 乘以 \( E \)，这意味着是余弦φ、正弦φ和0。嗯，我可以计算出这在该量上的结果。

## 82:55

Donc e. Si je l'applique, ben ça va me faire. Cosinus alpha sinus phi, pardon,. 0. Facteurur, du co coup,. Doncc je dois av avoir un 2 qui apparaît là, mon tenseur de déformation de Greene-Lagrange, il a cette forme-là, donc j'avais un 2 ici que je me retrouve avec un alpha t sur 2 facteur, donc de 0 alpha t, enfin pardon, ici c'est 1, alpha t 0 0 0, sachant que c'est symétrique.

**页面中文译文**

所以e。如果我应用它，那么结果将是余弦α乘以正弦φ，抱歉，系数为0。因此，我这里应该出现一个2，我的格林-拉格朗日应变张量就是这个形式，所以我这里有一个2，结果变成了αt除以2的系数，也就是0，αt，抱歉，这里是1，αt，0，0，0，且该张量是对称的。

## 83:58

Et là j j'ai un cosinus phi sinus phi 0. Donc si je... si je développe, je vais pouvoir simplifier là le 2 avec le 1/2,. Du coup je commence par par ce calcul-là, donc là je regarde mon cosinus sinus 0, facteur du coup de...... ben on est, un peu plus de place, alors 0 fois cosinus phi, plus 1 fois sinus phi, pour garder ici le alpha t qui est un provenant ici, alors e euhuh, je l'ai dit, oui c'est sinus phi pour la première composante, deuxième composante, donc j'ai 1 fois cosinus phi, plus alpha t fois sinus phi,.

**页面中文译文**

然后这里我有一个余弦φ乘以正弦φ等于0。所以如果我……如果我展开的话，我就能把2和1/2简化掉。于是我先从这个计算开始，这里我看余弦正弦0的因子，结果是……嗯，我们有更多空间了，所以0乘以余弦φ，加上1乘以正弦φ，为了保留这里的αt，它来自这里，嗯，我说过了，第一部分是正弦φ，第二部分是1乘以余弦φ，加上αt乘以正弦φ。

## 84:49

Plus 0 fois 0. Et pour la dernière, 0 fois cosinus phi, plus 0, 0 0, ça me donne 0. Ensuite je fais mon produit... Mon produit vecteur-vecteur, mon produit scalaire, ce qui me donne alpha t fois cosinus phi sinus phi, plus du coup. Cosinus phii, sinus phi, plus alpha t sinus phi au carré. Donc je peuxux r rassembler les termes: de cosinus phi, sinus phi, plus alpha t, sinus phi au carré.

**页面中文译文**

加上0乘以0。最后，0乘以余弦φ，加上0，0 0，结果是0。接着我做我的乘积……我的向量-向量乘积，我的标量积，这给了我αt乘以余弦φ乘以正弦φ，加上余弦φ乘以正弦φ，加上αt乘以正弦φ的平方。所以我可以把余弦φ乘以正弦φ，加上αt乘以正弦φ的平方的项合并起来。

## 85:21

Voilà ce ce que c'est essentiellement donné, pet voite véri apficplication s'il n'y a pas d'erreur. Euh, Ah ouuii, j'o oubliais mes DL0, côté... j j'étaétais censéé avoiroir un un DL0 ici et un DL0 là., Pas homogène, Donc j'ai un DL0 carré ici, DL0 au carré, DL0 au carré. C'est un un accroissement de de longueur au carré, donc à la fin je dois bien avoir une longueur au carré.

**页面中文译文**

这基本上就是给出的内容，这是一个真正的应用，如果没有错误的话。嗯，啊，对了，我忘了我的DL0，方面……我本来应该这里有一个DL0，那里也有一个DL0。不是均匀的，所以我这里有一个平方的DL0，DL0的平方，DL0的平方。这是长度的平方的增长，所以最后我应该得到一个长度的平方。

## 86:04

Sachant que alphaha t c'est censé être adimensionné. Euh, çaa suffit, oui. Éventuellement, ça. On peut le remplacer par un sinus de 2 alpha, de 2 phi. Avec les formules de trigo. Bon, ça simplifie légèrement la forme. Donc... Ah oui, don donc vous voyez que vous avez un terme qui est linéaire en temps et un terme qui est.

**页面中文译文**

已知αₕₐₜ应该是无量纲的。嗯，这样就够了。或者，可以用2α、2φ的正弦函数来替代。利用三角函数公式，这样可以稍微简化表达式。所以……啊，是的，你们看到有一个项是时间的线性函数，还有一个项是。

## 86:36

Qu Quadratique. Donc plus le temps avance, plus... Vous allez avoir une partie importante. Bonon, là, celle-là, si vous êtes au tout début de la déformation, ça, ça ne joue presque pas, au final. Parce que c'est d au au carré. Des temps très petits, au tout début de la déformation, ça va très peu jouer, et donc du coup c'est surtout ce terme-là qui va porter l'essentiel de la déformation.

**页面中文译文**

二次方程。因此，随着时间的推移，您将会有一个重要的部分。嗯，这个，如果您处于变形的最初阶段，这几乎不起作用。因为这是时间的平方。在变形的最初阶段，时间非常短，对结果影响很小，所以主要是这个项承担了变形的主要部分。

## 87:15

Donc du coup, on peut se dire qu'au tout début du glissement, quand on commence à peine le mouvement, là, en fait les. Évolutions de la longueur des fibres évoluent de manière linéaire. On peut négliger ce terme-l. Par contre, si vous vous intéressez à la partie très avancée de la déformation, donc vous vous souvenez de votre domaine qui était sous cette forme, ben petit à pet petit il glisse, il glisse, il glisse, il glisse, au bout d'un moment vous vous retrouvez avec un truc qui est sous sous cette forme-là.

**页面中文译文**

所以一开始滑动刚刚开始的时候，纤维长度的变化实际上是线性的，我们可以忽略这个项l。但是，如果你关注变形的后期阶段，你还记得你的区域最初是这个形状，慢慢地它滑动、滑动、滑动，最终你会得到一个呈现这种形状的结构。

## 87:42

Vous voyez que plus vous allez avancer, plus vous alle allez étirer votre... La longueur de vosos fibres, et donc ça. Évoluer de manière non linéaire. Donc globalement, nous on va toujours se contenter aux petites perturbations, comme on avait vu la semaine derninière, donc on va essayer de rester sur les évolutions linéaires, ok.

**页面中文译文**

你会发现，随着你不断前进，你的纤维长度会不断拉伸，因此这种变化是非线性的。总体来说，我们通常只考虑小的扰动，就像我们上周看到的那样，所以我们会尽量保持在线性变化范围内，好吗？

## 88:10

Pour pouvoir manipuler des équations qui sont... Facilement. Manipulables. Euh, très bien, donc ça c'est bon, c'est fait. Et on va s'intéresser à un dernier aspect qui est le côté variation de volume, Ça c ouais c'est quoi le deuxième terme alpha t sinus carré phi, vous avez dit que qu'ilus ét étaitie négégligeable., parce que c'est Al

**页面中文译文**

为了能够轻松地操作方程。嗯，非常好，这部分完成了。接下来我们将关注最后一个方面，即体积变化这一部分。第二项是αt sin²φ，你们说它可以忽略，因为它是…

## 88:52

Alors non, quand t est petit, proche de 0, ben t est beaucoup plus important que t au carré. Si je prends t = 0, 0,01, 1% par exemple. Ok. Benen. 1% par rapport à 1% au carré, vous avez un rapport 100 entre les deux. Ok. Donc vous aurez un très petit. Et là, si vous regardez en... donc vous avez ces dépendances sinus de... de.

**页面中文译文**

不，当 t 很小，接近 0 时，t 比 t 的平方重要得多。比如我取 t = 0.01，也就是 1%。好的。那么，1% 与 1% 的平方相比，两者相差 100 倍。好的。所以你会得到一个非常小的值。如果你观察……所以你有这些正弦函数的依赖关系……

## 89:27

Phi, donc en gros vous voyez que la... comment, l' l'allongement des fibres, en fonction de comment elles sont orientées au départ, ok, elles sont plutôt orientées suivant E1 ou ou E2, ben si vous vous intéressez juste au début de la déformation, ben suivant E1, sinus de phi, égal à 0, vous n'avez pas de variation de longueur des fibres, et plus vous allez vous rapprocher des fibres qui sont orientées suivant E2, plus vous allez vous rapprocher de cette direction, ben plus le.

**页面中文译文**

Phi，所以基本上你可以看到……纤维的伸长程度取决于它们最初的方向，好吧，它们大致沿着E1或E2方向排列。如果你只关注变形的初期阶段，那么沿着E1方向，phi的正弦值等于0，纤维的长度没有变化；而当你越接近沿E2方向排列的纤维时，你就越接近这个方向，变化也就越明显。

## 90:10

L'augmentation de la longueur des fibres va être importante. Alors, dernière question, je crois que c'est la question 1 7. Du coup, sur. Ce Onon vousus demande, c'est pour un un cube et. Donc si c'est un cube, ça veut dire que que vo vous alle allez y. Définir par les vecteurs dA, 0, d, c0, enfin dA0, dB0, dc0, donc en gros vous avez votre cube dans la configuration initiale, là,.

**页面中文译文**

纤维长度的增加将会很显著。那么，最后一个问题，我相信是第17题。题目要求的是一个立方体。如果是立方体的话，这意味着你们将通过向量dA0、dB0、dC0来定义它，基本上你们有一个处于初始配置的立方体。

## 91:20

Avec... on va le mettre ici, dA0. D, d, 00, et dc0. Ce qu'on veut, c'est regarder la variation de volume entre les deux états,. Entre l'état initial et l'état actuel. Donc sous l'effet de la déformation. Ok. Alors, vo. Donc ce que vous avez quand même, vous avez d d,c0 qui est égal à dAc0 vectoriel dB0, ok, c'est des... ils sont unitaires, c'est pour.

**页面中文译文**

用……我们把它放在这里，dA0。D，d，00，和dc0。我们想要的是观察两个状态之间的体积变化，初始状态和当前状态之间的变化。因此是在变形作用下的变化。好的。那么，vo。所以你们手头有的，d d,c0 等于 dAc0 向量乘以 dB0，好吧，它们是……它们是单位向量，这是为了……

## 92:18

Ok. Si on veut avoir accès au au volume élémentaire de ce petit cube, ben du coup on fait le produit mixte. Le produit mixte de ces trois vecteurs, c'est égal à dA0, dB. 0 vectoriel dc0. Déjà en chane.îne, Alors, c'est valable dans la configuration initi initiale, mais c'est aussi valable dans la configuration actualisée.

**页面中文译文**

好的。如果我们想要获得这个小立方体的基本体积，那么我们就计算这三个向量的混合积。这个三个向量的混合积等于 dA0、dB0 和 dc0 的叉积。首先在参考配置下成立，同时在当前配置下也同样成立。

## 93:20

Avec du coup dA c'est égal à phii, de dA0, ce qui est égal aussi à f de dA0. Pareil pour dB, et pour dc. Donc pour avoir le volume initial, je fais cette opération. Pour avoir le volume actuel, je fais cette opération. Et je vois que pour chacun des vecteurs dans la configuration actualisée, je peux les mettre en lien avec les vecteurs dans la configuration initiale.

**页面中文译文**

因此，dA 等于 φi，等于 dA0，也等于 f(dA0)。对于 dB 和 dC 也是一样的。为了得到初始体积，我进行这个操作。为了得到当前体积，我进行这个操作。我发现，在更新后的配置中，每个向量都可以与初始配置中的向量对应起来。

## 94:21

Alors,. Je peux aussi dire que le produit mixte des vecteurs dA, dB et dc c'est la même chose que de faire de calculer le déterminant de la matrice avec dA... DB et dc qui sont en colonne. Donc je peux écrire que d dB0 c'est égal au déterminant, alors on. Va se faciliter la vie avec une notation plus...

**页面中文译文**

那么，我也可以说，向量 dA、dB 和 dC 的混合积与计算以 dA、dB 和 dC 作为列的矩阵的行列式是相同的。因此，我可以写成 d dB0 等于该行列式，然后我们用一种更简便的符号来表示。

## 95:00

Plus facile, hein. Le déterminant de ces trois vecteur Le déterminant de ces trois vecteurs, c'est le déterminant de la matrice avec les vecteurs qui sont mis sous forme de colonne. Doncc dB0, ben c'est ce déterminant-là., Voilà. Et donc c'est vu que je peux utiliser ces équations-là, je peux remplacer par f fois dA0.

**页面中文译文**

更简单，对吧。这三个向量的行列式，就是将这三个向量作为列组成的矩阵的行列式。所以dB0，就是这个行列式。就是这样。因此，因为我可以使用这些方程，我可以用f乘以dA0来替代。

## 95:52

F appliqué à dB0, et f appliqué à dc0. Alorors, les propriétés du déterminant,. Les propriétés de Morphisme, en fait c'est'est comme si du coup j'avais le déterminant de f fois le déterminant de dA0 dB0 dc0. Et là je ret retrouve bien... Avec cette quantité, je retrouve bien la valeur du volume initial.

**页面中文译文**

函数f作用于向量B0，函数f作用于向量C0。那么，行列式的性质，态射的性质，实际上就像是我得到了f的行列式乘以由向量A0、B0、C0组成的行列式。这样，我就能很好地通过这个量恢复初始体积的值。

## 96:30

Ce qui me permet de dire que dB sur dB0, c'est égal au déterminant de f. Je peux relier le déterminant de f, en gros hein, c'est égal au jacobien de la... au déterminant de la matrice jacobienne, çaa me retranscrit l'évolution temporelle, au fur et à mesure du temps, du volume actuel sur l'initial.

**页面中文译文**

这使我能够说，dB 关于 dB0 的变化等于函数 f 的行列式。我可以将函数 f 的行列式联系起来，基本上它等于雅可比矩阵的行列式，这反映了随着时间的推移，当前体积相对于初始体积的变化。

## 97:33

Et donc si je l'applique à mon problème, là,. Je vais garder ça sous la main, tac tac tac, ça j'en ai plus besin. Je garde mon schéma ici. Ici, du coup, le dé déterminant de f,. J'ai plus la forme de f. f C'est dans la forme de ça. Attends, Alors, 1, 0, 1, 1, 0, tac. Donc là j'ai un tracé, j'ai un 0.

**页面中文译文**

所以如果我把它应用到我的问题上，嗯，我会把它放在手边，咔咔咔，这个我不需要了。我把我的图表保留在这里。这里，所以，f的决定因子，我不再有f的形式。f的形式是这样的。等等，1，0，1，1，0，咔。所以这里我有一个图形，我有一个0。

## 98:50

Bon ben du coup, je. 1 fois ce produit-là, ça me fait 1 fois 1 fois 1, moins alpha t fois 0, moins alpha t. Soit 1 moins plus alpha t au carré. Attendes,z, Euh, 4. Jeis censé av avoir... j'ai pas de variation de volume normalement. Ah non, pardon, j j'ai un 0 ici, je suis bte. Il est pas symététrique mon tenseur à f, que j'ai pasid bien l'ar recopé.

**页面中文译文**

好吧，那么，我用这个产品一次，得到的是一次一次一次，减去αt乘以0，减去αt。也就是1减去加上αt的平方。等等，z，呃，4。我应该有……我正常情况下没有体积变化。啊不，对不起，我这里有个0，我犯傻了。我的张量f不是对称的，我没把它抄好。

## 99:30

Donc ça me donne 1 moins 0 fois alpha t. Moins 0, moins 0 fo fois... je m'en fous, de toute façon c'est égal à 0. Donc du coup c'est égal à 1. Et donc si. De f est égale à 1, ben ça veut dire que les volumes actuels sur l'initial sont les mêmes, donc. Directement. Et donc il s'agit d'une transformation à.

**页面中文译文**

所以这给了我1减去0乘以αt。减去0，减去0乘以……我不在乎，反正等于0。所以结果等于1。因此，如果f等于1，那就意味着当前的体积和初始体积是相同的，直接如此。因此，这是一种变换。

## 100:11

Volume constant, autrement dit isochore,. Et donc... Pas de changement de volume. Et on peut même préciseriser que ça correspond à un mouvement. Du coup qui est incompressible. Quand vous faites un mouvement de glissement, que ce soit un glissement simp simple ou un glissement pur, ça se fait sans changement de volume.

**页面中文译文**

体积保持不变，换句话说，即等容过程。因此……体积没有变化。我们甚至可以进一步明确，这对应于一种运动。因此，这种运动是不可压缩的。当你进行滑动运动时，无论是简单滑动还是纯滑动，都是在体积不变的情况下进行的。

## 100:39

Et c'est typiquement le type de propriété qu'on a pour la déformation plastique dans les aciers, on considère que c'est des défauts qui se... qui se propagent dans les arrangements cristallins de la matière, et donc c'est juste un déplacement d'un défaut dans ce réseau-là, ça change pas du tout le volume de votre... de votre matière.

**页面中文译文**

这正是我们在钢材塑性变形中所具有的典型性质，我们认为这是在物质的晶体结构中传播的缺陷，因此这只是该晶格中缺陷的位置移动，完全不会改变材料的体积。

## 101:16

Par contre, vous accumulez des défauts, ce qui... ce qui représente la déformation plastique. Et donc dernière question avant de passer à un autre exercice : c'est la question... Elle a aucun intérêt cette question, on va pas la... on va la laisser comme entraînement. Donc ça clôt cet exercice, j'en ai un autre où on peut réutiliser des résultats d'un exercice précédent, où là on va s'intéresser à.

**页面中文译文**

另一方面，你们积累了缺陷，这就代表了塑性变形。最后一个问题，在换到另一个练习之前：这是个问题……这个问题没有任何意义，我们不会……我们就当作练习保留它。好了，这个练习就到这里，我还有另一个练习，可以重复利用前一个练习的结果，接下来我们将关注那个。

## 102:11

L'aspect petite déformation. Petite perturbation. Qu'est-ce que que ça donne ça ? ? Euh, mouvement LBVTT de rotation... Mais là cette fois on va s'intéresser à la partie déformation. Donc en gros, he hein, c'est la suite du TD11 exice. 2. On avait... on s'était intéressé... Au mouvement de rotation...

**页面中文译文**

小的形变。小的扰动。这会产生什么效果呢？嗯，LBVTT的旋转运动……但这次我们将关注形变部分。总的来说，嗯，这是TD11练习2的后续。我们之前关注的是旋转运动……

## 103:38

Ça ou non ? ça, c'est ? On s'intéressait au mouvement de rotation d'un cylindre. On avait pu traduire... On avait le mouvement en description, Lagrangangienne, qu.. On était partis du commun pour cet exercice-l. On a pris un truc Ouais, on était partis de la description Lagne. Ç C'est comme comme ça. ç ça,

**页面中文译文**

这个还是不行吗？这是……我们关注的是一个圆柱体的旋转运动。我们已经能够表达……我们有运动的描述，拉格朗日函数，那个……我们是从常见的情况出发做这个练习的。我们选了一个东西，是的，我们是从拉格朗日描述出发的。就是这样的，就这样。

## 104:15

Et ils sont ca. Donc là on avait la description Lagrangienne du mouvement, on avait déterminé la description Eulérienne, donc pas de... pas tellement... D'intérêt, mais on était arrivés à cette description-l., Pour la description du mouvement. Des Description Lagrangienne et description Eulérienne, qui sont équivalentes, c'est juste selon le contexte, c'est plus pratique d'utiliser l'une ou l're.

**页面中文译文**

它们就是这样。所以我们有了运动的拉格朗日描述，也确定了欧拉描述，虽然不是特别重要，但我们已经得到了这种描述。运动的拉格朗日描述和欧拉描述是等价的，只是根据具体情况，使用其中一种会更方便。

## 105:08

Alors, ce qu'on peut faire dans ce... dans le cadre de cet exercice,. On peut calculer le tenseur de déformation,. Le On va commencencer, on va le faire par éta étapes. Gradient de transformation f. Puis... De dé. Formation E. Tenseur de déformation, vous avez prévu une Lagre. Alors, le. Tenseur gradient de transformation, on peut le calculer comme étant le gradient de la fonction fi, c'est ça.

**页面中文译文**

那么，在这个练习的框架内，我们可以做的是计算变形张量。我们将分步骤进行。首先是变换梯度f，然后是变形张量E。变形张量你已经预见到了。那么，变换梯度张量可以计算为函数fi的梯度，对吧。

## 105:48

Ça correspond à dériver les positions actuelles par rapport aux positions initiales. Et donc de manière. Mathématique, hein, ça revient à ça. Donc je prends cette fonction fi, je la dérive par rapport aux différentes composantes de l'espace, donc d'abord je dérive cette expression-là par rapport à X1, ce qui me donne cosinus θ.

**页面中文译文**

这相当于对当前位置相对于初始位置求导。从数学角度来看，确实是这样。所以我取这个函数fi，分别对空间的各个分量求导，首先我对这个表达式关于X1求导，得到的是余弦θ。

## 106:30

Puis par rapport à X2, ça va me donner -sinus θ. Puis par rapport à X3, ça me donne 0. Deuxième ligne de ma matrice f, je dérive la composante 2 des. Coordonnées actualisées par rapport à. X1 dans la... dans un premier temps. Ce qui me donne sinus θ, parce que ça, ça dépend que de x2. Ensuite, je dérive par rapport à X2, ça me me donne cosinus θ., Par rapport à X3, ç

**页面中文译文**

然后关于X2，这将给我 -sinθ。然后关于X3，结果是0。矩阵f的第二行，我首先对更新后的坐标的第二个分量关于X1求导，这给了我sinθ，因为它只依赖于X2。接着，我对X2求导，得到cosθ。关于X3，结果是…

## 107:09

Par rapport à X3, ça me donne 0. Puis je dérive ça par rapport à X1, ça me donne 0. Par rapport à X2, 0. Et par rapport à X3, j'obtiens bien A. 1 Première remarque : cela ressemble beaucoup à une matrice de rotation. Ok. Ça tombe bien, parce que c'est un mouvement de rotation ce qu'on est en train d'étudier.

**页面中文译文**

相对于X3，结果是0。然后我对X1求导，结果仍是0。对X2求导，还是0。对X3求导，我确实得到了A。第一点评论：这很像一个旋转矩阵。很好，因为我们正在研究的正是一个旋转运动。

## 107:53

Alors, la suite logique, c'est'est de calculer le tenseur de déformation... E, qui est égal à 1//2 de f transposé fois f moins l'identité. Donc je refais ma petite tambouilleille de tout à l'heure, ça, ça correspond au tenseur c, et le tenseur c. Je sais que c i j, c'est égal à f j j fois f j j.

**页面中文译文**

那么，接下来的逻辑步骤是计算变形张量E，它等于½乘以F的转置与F的乘积减去单位矩阵。于是我重新进行刚才的小计算，这部分对应的是张量C。对于张量C，我知道C_ij等于F_ji乘以F_jj。

## 108:18

Donc pareil que tout à l'heure, je peuxux faire le produit colonne-colonne. Ok. Je sais en réalalité, bah ça va être cosus. Carré θ fois... plus, pardon, sinus carré θ. J'ai fait cette colonneonne-là, je prends cette colonne-là. Cosinus θ fois cosinus θ, puis sinus θ fois sinus θ,, puis 0 fois 0.

**页面中文译文**

所以和刚才一样，我可以做列与列的乘积。好的。我实际上知道，这将是余弦平方θ加上正弦平方θ。我取这一列，乘以这一列。余弦θ乘以余弦θ，加上正弦θ乘以正弦θ，再加上0乘以0。

## 108:56

Ce qui me donne ça, ensuite, là je vais faire colonne 1 fois colonne 2, donc moins cosinus θ, sinus θ, plus cosinus θ, sinus θ. Clac clac, plus clac clac. Ok.k, Et ensuit Et ensuite, ligne... colonne 1 fois colonne 3, à chaque fois que j'ai que des 0. C'est symétrique à. Ce tenseur, donc j'ai pas besoin de calculer ni ça ni ça.

**页面中文译文**

这给了我这个，接下来，我将做第一列乘以第二列，所以是负余弦θ，正弦θ，加上余弦θ，正弦θ。啪嗒啪嗒，加上啪嗒啪嗒。好的。然后，接着，行……第一列乘以第三列，每次我只有零。这是对称的张量，所以我不需要计算这个或那个。

## 109:24

Ce qui va m'intéresser maintenant, c'est la composante 2 2, donc colonne 2 fois colonne 2, ce qui me donne encore une fois sinus carré θ plus cosinus carré θ, pour cette composante c'est colonne 2 fois colonne 3, sinus θ fois 0 plus cosinus θ fois 0 plus 0 fois 1, ça me donne 0. Et dernière composante, 3 3, colonne 3 fois colonne 3, ce qui va me donner 1.

**页面中文译文**

我现在感兴趣的是第2行第2列的分量，也就是第2列乘以第2列，这又给了我正弦平方θ加余弦平方θ。对于这个分量，是第2列乘以第3列，正弦θ乘以0加余弦θ乘以0加0乘以1，结果是0。最后一个分量，第3行第3列，第3列乘以第3列，结果是1。

## 110:16

Ok. Et vu que je me souviens des formules de base de trigo, ça c'est égal à 1, et ça c'est égal à 1. Conclusion : ma matrice c est égale à ma matrice identité. Si la matrice c c est égale à à l'identité, bah du coup, j'ai 1/2 de c - i qui est égal du coup à 0. Le tenseur 0. Ok. Conclusion : si le tenseur de déformation de Green-Lagrange est nul, ç.

**页面中文译文**

好的。既然我记得基本的三角函数公式，这个等于1，那个也等于1。结论：我的矩阵c等于单位矩阵。如果矩阵c等于单位矩阵，那么1/2乘以(c - i)就等于0，也就是零张量。好的。结论是：如果Green-Lagrange变形张量为零，…

## 110:48

Que par définition, il n'yy a pas de déformation du milieu. Ça tombe bien, parce que le mouvement, là, bon, j'ai pas... j'ai j'ai pas de cylindre, mon gobelet, hein, mais une simple rotation de corps rigide, ça n'entraîne pas de déformation du milieu. Là, c'est avec la définition très propre des dé déformations. qu' Onon a pris le tenseur des déformformations de Green-Lagre.

**页面中文译文**

根据定义，介质没有变形。正好如此，因为这个运动嘛，我没有……我没有圆柱体，我的杯子，嗯，只是刚体的简单旋转，不会导致介质变形。这里是利用非常严格的变形定义，我们采用了格林-拉格朗日变形张量。

## 111:43

Maintenant, on va se dire : ok,. Nous, on aime bien avoir des équations simples, on aime bien linéariser, on a aime... on va essayer d'appliquer la linéarisation. Ok. Alors, e. Dans le cadre des petites perturbations,. Ce qu'on appelle communément HTP, hypothèse H, des petites perturbations,. On peut utiliser une.

**页面中文译文**

现在，我们来说：好吧，我们喜欢简单的方程，我们喜欢线性化，我们喜欢……我们将尝试应用线性化。好的。那么，在小扰动的范围内，也就是通常所说的小扰动假设（HTP，假设H），我们可以使用一种方法。

## 113:02

La forme linéarisée de ce tenseur. Donc,. On peut dire que quand on est en HTP,. Le tenseur de déformation de Green-Lagrange, on peut dire qu'il est à à peu près égal à sa forme linéarisée, qui est égale à 1/2 du. Gradient de U plus son transposé. U, c'est le déplacement. Or,. On sait que le gradient... que le gradient du champ de déplacement, c'est égal à f, euh, pardon,.

**页面中文译文**

该张量的线性化形式。因此，可以说当处于小变形假设（HTP）时，格林-拉格朗日应变张量大致等于其线性化形式，即位移梯度与其转置矩阵之和的1/2。这里，U表示位移。我们知道，位移场的梯度等于F，呃，抱歉，…

## 114:14

C'est égal à f moins... Pardon, f moins l'identité. On va recalculer. Donc, on peut déterminer la forme de notre gradient de déplacement, et on va aboutir au calcul. Et on va pouvoir voir si ça marche. On On va voir ce que ça nous donne, déjà. Donc, le gradient du champ de déplacement, si on retire l'identité à f, bah du coup,.

**页面中文译文**

这等于f减去……抱歉，f减去恒等映射。我们将重新计算。因此，我们可以确定位移梯度的形式，并最终完成计算。然后我们可以看看效果如何。我们先看看结果如何。所以，如果我们从f中减去恒等映射，就得到了位移场的梯度。

## 115:00

Ça nous donne cosinus de θ - 1, euh, là je crois que c'était moins sinus θ, 0. Sinus θ, sinus θ - 1, 0, et là on avait 1, ça nous donne 0. Ok. Donc, du coup, si on prend la partie symétrique, bah en gros, ça ne change pas. De comme ça. Ça ch change rien pour les quantités qui sont sur la diagonale, on les... on garde toujours les mêmes, vu qu'on extrait la partie symétrique.

**页面中文译文**

这给了我们余弦θ减1，嗯，我记得这里是负正弦θ，0。正弦θ，正弦θ减1，0，然后这里是1，结果是0。好的。所以，如果我们取对称部分，基本上不会改变。就是这样。对角线上那些量没有变化，我们还是保持不变，因为我们提取的是对称部分。

## 115:50

Ok. Donc, sinus θ - 1, et puis 0, ok. Par contre, pour. Pour ces parties-là, bah on va... on va faire la somme des deux, bah sinus θ plus moins sinus θ, pardon, sinus θ moins sinus θ, ça nous donne 0, et puis ici on va voir 0 et 0. Qu'est-ce qui se passe ? Si on regarde la forme linéarisée du tenseur de déformation,.

**页面中文译文**

好的。所以，sin θ 减 1，然后是 0，好的。另一方面，对于这些部分，我们将……我们将两者相加，即 sin θ 加减 sin θ，不好意思，是 sin θ 减 sin θ，结果是 0，然后这里我们看到 0 和 0。发生了什么？如果我们观察应变张量的线性化形式，…

## 116:14

On n'a pas 0. Par définition, vous êtes sur sur un mouvement qui n'entraîne pas de déformation, mais si vous prenez la forme approchée, donc une forme linéarisée pour vous... pour vous focaliser sur les petites perturbations, vous voyez qu'il y a... il y a a des déformations. Par définition.

**页面中文译文**

根据定义，我们没有零。您处于一个不会引起变形的运动中，但如果您采用近似形式，也就是线性化的形式，专注于小的扰动，您会看到确实存在变形。这是定义所决定的。

## 117:07

C'est cocasse. Alors, la question c'est :. Hypothèse sur l'angle θ, qui— je le rappelle— est égale à ω fois t,. Euh,. Liée à l'hypothèse des petites perturbations. Alors, l'hypothèse des petites perturbations, c. Ça veut dire que les transformations sont infinitésimales,. C. Petites,.

**页面中文译文**

这很滑稽。那么，问题是：关于角度θ的假设，我提醒一下，θ等于ω乘以t。嗯，这与小扰动假设有关。小扰动假设意味着变换是无穷小的，也就是说，非常小。

## 118:04

Et par pareil pour les déplacements. L'ordre de grandeur... Sont petits. Alors là, ça, on va pas avoir trop le mûou, les lesens. De caractériser l'aspect infinitésimal des déplacements.s, O ? Oui, oui, s' s'il vous plaît, r rendez-le luminéères. Est-ce que la lumière... Merci. Désolé. Euh, alors, la seule chose qu'on voit... sur laquelle on va pouvoir s'intéresser, enfin à laquelle on va pouvoir s'intéresser, c'est l'aspect infinitésimal...

**页面中文译文**

对于位移也是类似的情况。数量级……很小。那么，在这里，我们不会过多地讨论位移的无穷小性质。哦？是的，是的，请把灯打开。光线……谢谢。抱歉。那么，我们唯一能关注的，或者说我们将要关注的，就是无穷小的方面……

## 118:52

L'aspect infinitésimal des transformations, c'est caractérisé.... Équivalent, pardon, à dire que le— il fa faut que je regarde le gradient du ch champ de déplacement, donc qui est censé être un tenseur, il doit vérifier que sa norme est très petite devant 1. Pour ça, on prend la norme infinie, et donc la norme infinie, ça veut dire que pour un tenseur que je noterai comme grandamp A, je.

**页面中文译文**

变换的无穷小性质可以这样描述……等价于说——抱歉，我需要查看位移场的梯度，它应该是一个张量，并且必须满足其范数远小于1。为此，我们取无穷范数，无穷范数意味着对于一个我记作大写字母A的张量，……

## 119:33

Prends le max sur l'ensemble des composantes i_j, de la valeur absolue de a__ij. Donc si je l'applique, là, à à mon mon problème,. Ça veut dire que je dois avoir le max de cosinus de θ - 1, ou de sinus θ - 1, en valeur absolue, et de 0. Ça va vite passer à la trae. Il doit être très petit devant 1.

**页面中文译文**

取所有分量 \(i_j\) 中 \(|a_{ij}|\) 的最大值。所以如果我把它应用到我的问题上，这意味着我必须取 \(|\cos \theta - 1|\)、\(|\sin \theta - 1|\) 和 0 中的最大值。这个值很快就会趋近于零，必须远小于1。

## 120:26

Donc, dans le corrigé, vous avez une étude bien carrée qui est faite,. Mais en réalité, il faut regarder— attendez, je vais sinus... Pardon, j'ai pas un sinus θ, j'ai un... c'est un cosinus ici. Oi. C'est pareil. Un cos Désolé pour la petite erreur. J'ai pas de sinus... c'est juste... c'est juste comme ça, en fait.

**页面中文译文**

所以，在答案中，你会看到一个非常规范的分析。但实际上，我们需要看——等等，我要用正弦……抱歉，我这里没有正弦θ，我有一个……这里是余弦。哦。其实是一样的。余弦。抱歉刚才的小错误。我没有正弦……其实就是这样。

## 121:09

Avec ça, h.op, ça c'est Oui, pardon. Bien sinus θ., Parce que c'est pas... c'est pas là-dessus, c'est là-dus. Je dois faire mes... je dois regarder. C'est bien ça. Très petit devant 1. Très bien. Donc là, en fait, il faut regarder l'évolution des... la forme des fonctions cosinus θ - 1, alors si vous regardez cosinus...

**页面中文译文**

好的，对不起。是正弦θ，因为不是……不是那个，是那个。我得看一看。就是这样。非常小于1。很好。所以这里，实际上需要观察函数cosθ - 1的变化形态，如果你看cos……

## 122:05

θ - 1 en fonction de θ, si vous tracez... Ça a un peu de sens. Donc, vous allez avoir une cloche comme ça, voilà, donc ça c'est vot votre cosinus θ - 1., Et votre sinus θ, Et votre sinus θ, c'est censé vousus don donnerner ça. À peu près. C'est un peu comme ça. Donc, si vous faites passer que ces deux fonctions dans une valeur absolue, c'est-à-dire que vous prenez que la valeur positive, ça veut dire que pour sinus θ, çaa vous donne ça,.

**页面中文译文**

θ - 1 关于 θ 的函数，如果你画出来……这有点道理。所以，你会得到一个这样的钟形曲线，这就是你的 cosθ - 1。还有你的 sinθ，sinθ 应该给你大致这样的图形。大致就是这样。所以，如果你对这两个函数取绝对值，也就是说只取正值，那么对于 sinθ，它会给你这样的图形。

## 122:55

Ça c'est pour sinus θ,. Et pour votre cosinus θ - 1, ben ça vous donne quelque chose comme ça. Donc à chaque fois, il faut prendre le max. Sachant que ça, c'est égal à ω t, donc. Plus besoin, je peux calculer. Et donc la conclusion, en fait,. C'est que globalement vous allez tout le temps prendre, en fait, le cosin... vous allez tout le temps prendre, en fait, le sinus... pas tout le temps,

**页面中文译文**

这是关于正弦θ的。至于余弦θ减1，它会给你类似这样的结果。所以每次都要取最大值。知道这个等于ωt后，就不需要再计算了。结论实际上是，总的来说，你实际上会一直取余弦……不完全是，一直取正弦……也不是一直，

## 123:42

en gros. Si vous avez θ. Qui appartitient à mos. Qui est dans moins π/2, π/2 ça revient à prendre le sinus θ, est très petit devant 1, et si θ, du coup, n'appartient pas à moins π/2, π/2, sachant que ce sera perérimise. Votre condition, c'est cosinus θ - 1, très petit devant 1. Sachant que je l'ai couvert.

**页面中文译文**

大致来说。如果你有θ，属于区间(-π/2, π/2)，这相当于取sinθ，其值远小于1；如果θ不属于区间(-π/2, π/2)，且已知这是被限制的情况。你的条件是cosθ - 1远小于1。以上内容我已经涵盖。

## 124:23

Ben ça, au final, ça veut dire que vous avez. Dans tous les cas, je souhaite avoiroir des r se faire un peu dans les dé détails,. Ça vous dit que θ doit être très petit devant π/2, et ça, pareil, ça vous dit que θ doit être très petit devant π/2. En valeur absolue. Donc en fait, ça veut dire dire que vousus pou pouvez uniquement vo vousus intéresser aux petits angles.

**页面中文译文**

嗯，归根结底，这意味着你们有。无论如何，我希望能够在细节上稍作了解。这告诉你θ必须远小于π/2，同样，这也告诉你θ在绝对值上必须远小于π/2。实际上，这意味着你们只能关注小角度。

## 125:10

Aux très petits angles. Et comme θ est égal à ω t, ben ça revient au tout dé débutbut. Si on considère que,e... on on ne s'intéresse qu'aux temps positifs, au tout début de la déformation. En fait, quand vous commencez à avoir des rotations,. Ça peut complètement mettre en défaut l'utilisation de cette forme-l.

**页面中文译文**

在非常小的角度下。由于θ等于ωt，这就回到了最开始的情况。如果我们只考虑正时间，也就是变形刚开始的时候。实际上，当你开始出现旋转时，这可能会完全使这种形式的使用失效。

## 125:44

Donc là, vu qu'on est au tout début de la déformation, ben du coup,. Ça marche que quand vous êteses. qu quand vous avez des toutes petites rotations de. Corps rigide. Donc c'est une manianière de de bien se rentrer en tête que l'on veut éviter quand on... quand on va faire de de la simulation de déformation de solide, on veut à tout prix éviter d'avoir des mouvements de corps rigide.

**页面中文译文**

所以这里，由于我们处在变形的最初阶段，所以这个方法只适用于你们进行非常小的刚体旋转时。这是一种帮助大家牢记的方式：在进行固体变形模拟时，我们必须尽一切努力避免出现刚体运动。

## 126:12

Parce que ça va venir nous perturber nos formes linéarisées, ça veut dire qu'on va introduire de l'erreur. Mais par contre, là on est sur un un m mouvement de rotation de corps rigide,. On va on— on ne devrait pas mesurerer de la déformation en réalité. Par définition, il n'y en a pas du tout. Mais avec une forme linéarisée, on en mesure un un petit peu.

**页面中文译文**

因为这会干扰我们线性化的形状，这意味着我们会引入误差。但另一方面，这里我们讨论的是刚体的旋转运动，实际上我们不应该测量到任何变形。按定义，根本不存在变形。但使用线性化的形状时，我们会测量到一点点变形。

## 126:49

Alors, elle va être négligeable si on reste pour les toutes, toutes petites valeurs de θ, mais elles vont venir perturber la qualité de notre solution. Donc, en gros, hein,. Attention, l'ation. De la forme linéarisarisée,. Elle est liée à l'HPP, et donc il y a un domaine de validité bien précis.is.

**页面中文译文**

那么，如果我们只考虑非常非常小的θ值，它将是可以忽略的，但它们会干扰我们解的质量。总的来说，注意线性化形式的作用，它与HPP有关，因此有一个非常明确的适用范围。

## 127:21

L'hypothèse de petite perturbation dès qu'on travaille sur les solides, généralement on la fait. Mais à la faire, de manière. On va dire automatique, reptililienienne, au bout d'un d'un moment on oublie de savoir qu'il faut quand même bien s'assurer qu'on est dans un cadre où cette hypothèse est bien valide.

**页面中文译文**

在处理固体时，通常会假设只有小的扰动。但如果我们以一种自动化、机械化的方式去做，久而久之就会忘记必须确保所处的环境确实符合这一假设的前提。

## 128:13

Monsieur? Oui. Oui? Oui. Plus transposer des vari Oi. Par rapport avec le petit déformation de Oui, alors, comment? Le tenseur de déformation binal angle, on peut l'écrire comme étant cette forme-là plus le prod produit croisé de ces deux termes. Et du coup, est-ce qu'on pourrait définir l' l'hypothèse à vérifier à partir de ce produit croisé des de derni laères unités?

**页面中文译文**

先生？是的。是吗？是的。更多地转置一些变量。关于小变形，是的，那么，如何做呢？二阶角变形张量，我们可以将其写成这种形式，加上这两个项的叉乘积。那么，我们是否可以基于这两个最后单位的叉乘积来定义需要验证的假设？

## 128:36

Ben en fait, ça revient un peu au même que de vérifier ça. Parce que c'est un terme croisé entre le grade de U et son transposé, si la norme de grade de U est très petite, ben le transposé de grade de U fois grade de U, ça va être très petit devant ces deux termes-l. Parce que le résuitult Uat,, c'est'est une une hypothèse de?

**页面中文译文**

其实，这和验证它差不多。因为这是一个关于U的范数和它的转置范数的交叉项，如果U的范数非常小，那么转置范数乘以U的范数在这两个项面前会非常小。因为结果Uat……这是一个假设吗？

## 129:11

Alors oui, on peut le faire de différentes façs. En effet, on peut le faire de différentes façons, vérifier l'hypothèse des petites perturbations. Là, on va dire, c'est la méthode la plus rigoureuse, on va dire. C'est vraiment comme ça. On peut aussi vérifier dans quel cadre grade de U transposé fois grade de U est négligeable devant grade de U, mais ça, c'est pas hyper propre. Généralement, quand on vérifie un DL, on s'assure que les termes sont très petits, les termes qui qui ar arrivent à l'ordre 2, 3, ils sont très petits dev devant 1.

**页面中文译文**

是的，我们可以用不同的方式来做。事实上，我们可以用不同的方法来验证小扰动的假设。这里，我们可以说这是最严谨的方法，确实就是这样。我们也可以验证在什么情况下转置的梯度U乘以梯度U相比梯度U本身可以忽略不计，但这并不是特别严谨。通常，当我们验证一个泰勒展开时，我们会确保那些达到二阶、三阶的项非常小，远小于1。

## 130:06

Alors que là, c'est comme si on vérifiait que les termes d'ordre 2 sont petits devant les termes d'ordre 1. C'est pas tr très... C'est pas très rigoureux d'un point de vue mathématique. Euh, als. Ça clôt— La partie déation. On va pouvoir faire un un petit test, voir si vous avez un petit peu assimilé...

**页面中文译文**

这里就好像是在验证二阶项相对于一阶项是否很小。从数学角度来看，这并不是非常严谨。嗯，好吧。这就结束了——推导部分。我们可以做一个小测试，看看你们是否稍微掌握了一些内容……

## 130:59

Tout ça. Donc vous pouvez aller sur Socrative, je vais virer l.. Je v Je vais vous laisser le temps de noter, et puis on va passer à l'activité juste après. On va lancer un questionnaire.. Questionnaire Déformation... Donc vous allez sur Socrativive,e,. Et dans la salle, correspond. À E2. Je vais devoir effacer, j'ai pas anticipé le fait que il n'y a pas d'écran. Alors,.

**页面中文译文**

所有这些。所以你们可以登录Socrative，我会把它关闭……我会给你们时间记笔记，然后我们马上开始活动。我们将启动一个问卷调查……变形问卷……所以你们登录Socrative，进入教室，教室号是E2。我得清除一下，我没预料到这里没有屏幕。

## 131:40

Donc vousus allez avoir différentes questions qui sont en lien avec ce problème, deuxième chapitre. On va attendre.re Comme Comme ça je pourrai éteindre... Alors que vousus y voyez quelque chose, mais vous pouvez vous connecter depuis votre smartphone ou votre ordinateur. Donc,. Ce qui est important, en fait, c'est l'équation à laquelle ça mène.ne, Aprè

**页面中文译文**

所以你们将会有一些与这个问题相关的不同问题，这是第二章。我们会等待。这样我就可以关闭……虽然你们能看到一些内容，但你们可以通过智能手机或电脑连接。实际上，重要的是它所导出的方程式。之后，…

## 132:02

Après, la résolution, l'implication derrière, bon, c'est des développements mathématiques. Qui nous permettent à la fin d'arriver à cette conclusion-là, mais bon, le plus important c'est d'arriver à traduire ça sous forme mathématiatique. Du coup, je vais effacer ça, de toute façon vous avez le le corrigé qui est en ligne.

**页面中文译文**

之后，解析和背后的推理其实是一些数学推导，这些推导最终使我们得出这个结论。但最重要的是能够将其转化为数学形式。好了，我要把这些擦掉，反正你们网上有答案解析。

## 132:29

Je vais effacer ça et puis on va va passer au quiz. Avant de passer au chapitre suivant, on va pouvoir s'intéresser à la partie effort. Effort interne. Alors,. J'ai lancé l'activité, donc... je Ça a l'air à peu près lisible. Donc, le tenseur taux de déformation qui est le TD, alors là il il rend grave.e,

**页面中文译文**

我将删除这个内容，然后我们将进行测验。在进入下一章之前，我们先关注一下应变部分——内部应变。好了，我已经开始活动了，所以……看起来还算清晰。应变率张量，也就是TD，这里它表现得非常严重。

## 132:52

D'un milieu continu, est-ce qu'il est lié à la partie symétrie du gradient de vitesse? À la partie antisymétrique? Est-ce que c'est une grandeur Lagrangienne? Est-ce que c'est une grandeur Eulérienne? Est-ce qu'il dépend ou pas du temps? Et Et ça, c'est dans l'absolu. Ok. Alors, attentention, qu.

**页面中文译文**

在连续介质中，它是否与速度梯度的对称部分有关？与反对称部分有关吗？它是拉格朗日量吗？它是欧拉量吗？它是否随时间变化？这是绝对的。好的，那么，请注意，那个。

## 133:34

C'est pas en temps réel, cette affaire. Ou Il pourrait y avoir quelquesun bonnes bonnes réponses qu'onon a faites. Qui ont été faites. Oui, C C'est'est pas... C'est de de moins en moins efficace, cette cette plateforme. Je crois que je passe la Bon,. Une question pl plutôtt simple. On peut passer à la suivante.

**页面中文译文**

这件事不是实时的。或者可能有一些我们给出的正确答案。是的，这个平台变得越来越没效率了。我想我就说到这里吧。一个比较简单的问题。我们可以进入下一个问题了。

## 134:58

Tchak. Alors,. Quel type de mouvement se fait forcément à volume constant? Une rotation,? sous So--entendu de corps rigide, un glissement, une dilatation, une translation. Sous-entendu de corps rigide. Rotation, sous-entendu de... homogène, de corps rigide. Un glissement, une dilatation, une translation.

**页面中文译文**

那么，哪种运动必然是在体积不变的情况下进行的？旋转吗？在刚体的前提下，滑动、膨胀、平移。前提是刚体。旋转，前提是均匀的刚体。滑动、膨胀、平移。

## 135:40

Je comprends pas pour pourquoi c'est pas mis à jour cette affaire. C'est pas... On passe à la question suivante. L'intérêt, c'est surtout de vous mettre en situation. Alors,. Quand je parle de déformation, on parle de déformation de l'ingénieur, une déformation linéarisée, si vous voul. Donc si une barre de métal de 1 mètre, si avec les bras musclés j'arrive à l'allonger d'un centimètre, que veut sa déformation dans cette direction?

**页面中文译文**

我不明白为什么这件事没有更新。算了……我们进入下一个问题。重点主要是让你们身临其境。那么，当我说变形时，我们指的是工程师所说的变形，一种线性化的变形，如果你愿意的话。比如一根一米长的金属棒，如果我用力气把它拉长了一厘米，那么它在这个方向上的变形是多少？

## 136:23

Et est-ce que je suis un humain ou que. La force d'un poussin, ou que je je suis aussi fort que Superman si j'arrive à faire ça? Ça, c'est la question des deux. Donc,. Est-ce que la déformation, elle vaut 1 centimètre, 101%, 1%, 10%, ou 1 centim? Barre de métal d'un mètre, elle. Allongée d'un centimètre dans l'axe de la barre.

**页面中文译文**

我是人类吗？还是说，我像小鸡一样弱，或者如果我能做到这个，我就像超人一样强？这就是两个问题。所以，变形是1厘米，还是101%、1%、10%，或者是1厘米？一根一米长的金属棒，在棒的轴线上被拉长了1厘米。

## 137:08

Ah, c'est une question hyper pragmatique, hein, c'est pas... C'est juste voir si vous avez compris le concept de déformation. Et a priori, On va passer à la question suivante. Cette partie, le tenseur de déformation de Green-Lagrange, je peux rajouter que c'est deux, là, comme ça? Alors, est-ce qu'il est adapté à la description lagrangienne du mouvement?

**页面中文译文**

啊，这是一个非常务实的问题，不是……只是想看看你是否理解了变形的概念。原则上，我们将进入下一个问题。这部分，格林-拉格朗日应变张量，我可以这样加上这两个吗？那么，它适合用来描述拉格朗日运动吗？

## 137:32

À la description Eulérienne du mouvement? Est-ce qu'il contient uniquement la déformation pure du mouvement? Donc la partie déformation. Est-ce qu'il contient uniquement les parties rotation et déformation pure du mouvement? Est-ce qu'il contient les parties translation, rotation et déformation pure du mouvement?

**页面中文译文**

欧拉描述的运动包含的内容是什么？它是否仅包含运动的纯变形部分？还是仅包含运动的旋转部分和纯变形部分？或者它包含运动的平移、旋转和纯变形部分？

## 138:58

Ok. Allez, on passe à la dernière question. On précisera de toute façon, après on va faire la correction. Et donc, quelle est la caractéristique d'un mouvement qui est décrit par un tenseur de déformation D, dont la trace est nulle? Est-ce que c'est stationnaire, est-ce que c'est un mouvement circulaire, un mouvement incompressible, un mouvement qui est forcément rectiligne, est-ce que c'est un mouvement qui est irrotationnel?

**页面中文译文**

好的，我们来回答最后一个问题。无论如何，之后我们会进行讲解。那么，由一个迹为零的应变张量D描述的运动有什么特征？是静止的运动，还是圆周运动，不可压缩运动，必定是直线运动，还是无旋运动？

## 139:36

Donc... Rappel à Les l'émotion de de stationnarité, d'incompressibilité. Et les aspects irrotationnels des mouvementsements, qu' on les a vus, on a. Fait l'étude d'un mouvement circulaire dans le premier chapitre de... de cette thémati Par contre, on n'a pas trop vu les aspectsects rectilignes. Mais bon,.

**页面中文译文**

所以……回顾一下静止性和不可压缩性的概念，以及运动的无旋性方面，我们已经看过并研究过。在本主题的第一章中，我们研究了圆周运动。然而，我们并没有详细讨论直线运动的方面。不过，没关系。

## 140:29

Je peux vous mettre sur la voix. On se laisse un petit temps de réflexion. Aspect stationnaire, aspect circulaire, aspect incompressible, aspect rectiligne, aspect rotationnel ou irrotationnel. Allez, on se laisse croire 5 secondes. Terminalo. Alors, on va regarder question par question. On le met comme Coma.

**页面中文译文**

我可以帮你接通电话。我们先留一点时间思考。静止状态、循环状态、不可压缩状态、直线状态、旋转或非旋转状态。来，我们给自己五秒钟时间相信一下。结束。接下来，我们逐题来看。我们把它当作昏迷状态处理。

## 140:55

Alors, c'est lié à la partie symétrique du gradient de vitesse. C'est par définition la partie symétrique du gradient de vitesse. Donc c'était pas ça. C'est une grandeur Eulérienne, parce que c'est calculée... sur la base du gradient de vitesse Eulérienne.ne, Et potentiellement, ça peut dépendre du temps, parfois çaa peut ne pas dépendre du temps, mais par définition, il n'y a pas de raison que ça ne dépende pas du temps.

**页面中文译文**

那么，这与速度梯度的对称部分有关。它本质上就是速度梯度的对称部分。所以并不是那个。它是一个欧拉量，因为它是基于欧拉速度梯度计算的。并且它可能随时间变化，有时也可能不随时间变化，但从定义上讲，没有理由它不随时间变化。

## 141:23

Ok? Ça va pour ça? Ça se soulève pas de question? Très bien. Alors, quel type de mouvement se fait forcément à volume constant? Alors, une rotation de corps rigide? Oui,i, a priori. Alors, vous pouvez avoir des micro-rotations, justement, mais qui qui n'ont pas forcément généré des changements de volume.

**页面中文译文**

好的？这样可以吗？没有引起疑问吗？很好。那么，哪种类型的运动一定是在体积不变的情况下进行的？刚体的旋转吗？是的，原则上是这样。你们可以有微小的旋转，但这些旋转不一定会引起体积的变化。

## 141:49

Un glissement, on vient de le voir, par définition, un glissement qu'il soit simple ou pur, ça pour le côté glissement pur, on verra peut-être plus tard. Ça se fait à volume constant, une dilatation, les seules dilatations qui conduisent à. Une. Constant, c'est des dilatations avec un facteur 1, tout simplement.

**页面中文译文**

滑移，正如我们刚才所见，按照定义，无论是简单滑移还是纯滑移——关于纯滑移的部分，我们可能稍后再讨论——都是在体积不变的情况下进行的。膨胀，唯一导致体积不变的膨胀，就是膨胀因子为1的膨胀，简单来说就是这样。

## 142:14

Donc ça fait rien en réalité. Et une translation de corps rigide, ça ne change pas le volume. Très bien. Question suivante. Si une barre de métal est allongée d'un centimètre dans sa direction, alors qu'elle faisait un m mètre, la déformation vautut bien 1%. Alors, un centimètre, c'est pas la bonne unité, tout simplement.

**页面中文译文**

所以实际上这没什么影响。刚体的平移并不改变体积。很好。下一个问题。如果一根金属棒在其长度方向上被拉长了一厘米，而它原本的长度是1米，那么变形率确实是1%。不过，一厘米不是合适的单位，根本不合适。

## 142:34

101%, c'est plutôt la dilatation dans cette direction qui vaudrait 101%. Vous avez encore les 100% de la configuration initiale, vous avez encore l'identité. Quand vous cherchez à avoir la déformation, vous enlevez l'identité. Et 10%, c'est juste pas le bon ordre de grandeur. Mais au moins, c'était le bon type de quantité.

**页面中文译文**

101%，更准确地说，是指该方向上的膨胀率为101%。你仍然保留初始配置的100%，仍然是单位矩阵。当你想要得到变形时，需要去掉单位矩阵。而10%根本不是正确的数量级。但至少，这是正确的量的类型。

## 143:03

Alors, si au lieu de l'allonger, vous l'avez comp comprimé, contracté plutôt, ça aurait été moins 1%. Ok, ça aurait été une déformation négative. Et donc du co coup, en termes d'ordre de grandeur, on n'a pas encore vu ces notions-là, mais juste pour voir si est-ce que pour déformer une barre de métal, de 1 1%, est-ce que un humain très musclé y arrive?

**页面中文译文**

那么，如果不是拉长它，而是压缩它，收缩它的话，变形会少1%。好，这将是负变形。因此，从数量级上来说，我们还没有看到这些概念，但只是想看看，要使一根金属棒变形1%，一个非常强壮的人能做到吗？

## 143:34

Est-ce que un. Poussin y arrive? Est-ce qu'une machine industrielle y arrive? Non, vous n'avez pas du tout les ordres de grandeur. Une déformation de 1%, si vous vous souvenez, je vous ai donné quand même quelques ordres de grandeur, c'est de la déformation plastique. On n'est pas loin, on n'est pas encore au niveau de la mise en forme, mais arriver à faire plastifier une barre de de métal, une barre d'acier, c.

**页面中文译文**

一只小鸡能做到吗？一台工业机器能做到吗？不，你们根本不了解数量级。如果变形达到1%，如果你还记得，我之前给过你们一些数量级的概念，那就是塑性变形。我们还不远，还没有达到成形的程度，但能够使一根金属棒、一根钢棒发生塑性变形，已经是很了不起的了。

## 144:01

Faudrait vraiment, enfin Faudrait vraimentiment qu'elle ait... Ça dépend du... ça peut dépendre du rayon, on est d'accord. Mais bon, en général, quand on on parle d'une barre de métal, c'est quand même très compliqué de f faire ça avec ses mains. En tout cas, en traction, comme ça. Si vous faites de la flexion, des fois, si vous avez une barre de métal qui est très fine, en flexion, vous allez... avec un bras de levier, vous pouvez réussir à faire quelque chose. Ok?

**页面中文译文**

真的应该，嗯，真的应该让她……这取决于……这可能取决于区域，我们同意这一点。不过，一般来说，当我们谈论一根金属棒时，用手做到这一点还是非常困难的。至少，在拉伸的情况下是这样。如果你做弯曲，有时候，如果你有一根非常细的金属棒，通过杠杆作用，你可以做到一些事情。明白吗？

## 144:23

Mais là, en traction, comme ça, compliqué. Bon, ça c'était le petit côté bonus, mais vous inquiétez pas, c'est des notions que vous n'avez pas enc encore mes. Alors, le tenseur de déformation de Green-Lagrange, bon, c'est description Lagrangienne. Du coup, c'est pas vraiment la description Eulérienne.

**页面中文译文**

但是这样拉伸的话，就比较复杂了。好吧，这只是一个小的额外内容，不过别担心，这些概念你们还没学过。好了，Green-Lagrange应变张量，这是拉格朗日描述，所以它并不是真正的欧拉描述。

## 144:54

Et ça contient uniquement la partie de déformation pure du mouvement. Alors, la petite nuance, c'est quand même qu'on vous... on arrive à voir qu'il y a une petite rotation des fibres en. Étant capable de caractériser qu'il y a une variation d'angle des des fibres. Et donc, ça induit une légère partie rotation mais on a enlevé la partie rotation de corps rigide. Et on a retiré la partie translation de corps rigide également, qui n''apparaît pas.

**页面中文译文**

这只包含了运动中纯变形的部分。需要稍微说明的是，我们能够观察到纤维有轻微的旋转，能够确定纤维角度存在变化。因此，这引起了一部分轻微的旋转，但我们已经去除了刚体的旋转部分，同时也去除了刚体的平移部分，这些部分并未出现。

## 145:20

Je vais basculer là. Caractéristiques d'un mouvement décrit par un tenseur de déformation D dont la trace est nulle, c'est incompressible, la trace d'un taux de déformation qui est égal à la partie symétrique du gradient de champange de vitesse, c'est comme si c'était la trace du gradient de de vitesse en réalité, et donc c'est la divergence du champ de vitesse.

**页面中文译文**

我将切换到这里。一个由变形张量D描述的运动特征，其迹为零，表示不可压缩。变形率的迹等于速度场梯度的对称部分的迹，实际上就像是速度梯度的迹，因此它就是速度场的散度。

## 145:51

Donc c'est la définition de l'incompressibilité. Le fait que cette trace soit n. Par contre, ça n'a aucun lien avec l'aspect stationnaire, qui est.. j'ai justeuste lié à l'évolution temporelle du champ de vitesse, ça n'a aucun aspect avec l'aspect circulaire, ça donne aucune information sur le fait que le mouvement soit rectiligne ou non, et ça donne pas d'information sur l'aspect rotation qui, lui, va être lié plutôt à.

**页面中文译文**

这就是不可压缩性的定义，即迹为n。然而，这与稳态性质无关，稳态仅仅与速度场的时间演化有关，与循环性质无关，也无法提供运动是否为直线运动的信息，也无法提供与旋转性质相关的信息，旋转性质则另有联系。

## 146:14

Au tenseur oméga. Qui, lui, contientent la partie antisymétrique qui est liée à la partie rotation, c'est le tenseur taux de rotation. Ok? Donc voilà,. on va essayer de débunkkeré un peu les pignons, pour voir que finalement, vousus êtes une majeure partie à avoir trouvé les bonnes réponses, donc c'est pas trop mal.

**页面中文译文**

关于张量Ω。它包含与旋转部分相关的反对称部分，这就是旋转率张量。明白了吗？好了，我们来稍微澄清一下这些概念，看看你们大多数人其实都找到了正确答案，所以表现还不错。

## 146:46

Ça veut dire que vous avez compris l'essentiel, a priori. Bon, on va pouvoir avancer un petit peu sur la partie plutôt schématisation des efforts intérieurs. Alors, des efforts, dans l'absolu, mais pour pouvoir parler des efforts qui sont à l'intérieur de la matière, c'est-à-dire la notion de contraininte, on va revenir un petit peu à la base, les efforts qui s'appliquent à l'extérieur d'un milieu.

**页面中文译文**

这意味着你们大致上已经理解了要点。好，我们现在可以稍微推进一下关于内部应力部分的内容。首先，谈论应力这个概念本身，但为了能够讨论作用于物质内部的应力，也就是应力的概念，我们先回到基础，看看作用于介质外部的应力。

## 147:23

Ok? Donc, on va commencer par voir comment est-ce qu'on peut schématiser ça, comment on peut représenter ça d'un point de vue mathématique. Par la suite, on verra que ces efforts, quand on a un équilibre mécanique quis suitent des lois, des principes de la mécanique, des principes de la physique, donc les principes fondamentaux de la mécanique des mouvements aussi, et ce qui arrivera par la suite, dans les chapitres qui suivent, par que j'ai pas encore fait apparaître ici, on verra comment est-ce qu'on peut faire le lien entre les déformations et les contraintes.

**页面中文译文**

好的？那么，我们先来看一下如何对其进行简化表示，如何从数学角度来表达它。接下来，我们将看到这些力，当系统处于机械平衡时，会遵循机械学的定律和物理学的原理，也就是运动力学的基本原理。在后续的章节中，我还没有提到的内容，我们将探讨如何将变形与应力联系起来。

## 148:05

Ce qui traduit le comportement des matériaux, est-ce qu'ils sont plutôt rigides, soupuples, ou. Ce genre de considération. Ok? Donc, als. Je repasse en en mode comme ça. Tac, tac. Voilà. Alors, au programme de ce chapitre, donc, on va d'abord revenir sur la notion d'effort extérieur à un domaine, à un milieu, ensuite on verra comment est-ce qu'on schématise les efforts qui transitent à l'intérieur de ce domaine-là, à l'intérieur du milieu qui est déformable, on.

**页面中文译文**

材料的行为表现为它们是较为刚性的、柔软的，还是其他类型的。这类考虑。好的？那么，我切换回这种模式。好了。这个章节的内容安排是，首先我们将回顾作用于一个区域或介质外部的外力的概念，接着我们将探讨如何示意图示那些在该区域内部、在可变形介质内部传递的力。

## 148:31

Fera une petite étude justement des contraintes, parce que les efforts intérieururs, c'est des contraintes dans la matière, on ver verra comment est-ce qu'on peut décomposer les. Tenseurs des contraintes ou le vecteur contrainte, c'est des choses qu'on va introduire et qu'on va étudier ici, on va se donner les différents moyens d'étudier.

**页面中文译文**

将对应力进行一个小的研究，因为内部应力就是材料中的应力，我们将看看如何分解应力张量或应力向量，这些内容将在这里介绍和学习，我们将提供不同的研究方法。

## 148:55

L'état de contrainte dans la matière, donc pour ça on verra des opérateurs, des tenseurs de contrainte qui représentent des états de chargement bien spécifiques, et on introduira quelelques critères justement pour être capable de définir si un milieu subit des efforts qui vont au-delà de sa limite élastique, comment est-ce qu'on arrive à caractériser ça.

**页面中文译文**

材料中的应力状态，因此我们将看到一些算子和应力张量，它们表示特定的载荷状态。我们还将引入一些准则，以便能够判断材料是否承受了超过其弹性极限的力，以及我们如何对其进行表征。

## 149:25

Alors, première chose, quand on s'intéresse à des systèmes de solides qui sont rigides, il n'y a pas d'effort intérieur, à l'intérieur des corps qui sont rigides, qui ne se déforment pas. Ok? Donc les seuls types d'efforts qu'on peut modéliser, quand on travaille sur les solides rigides, ce qui nous intéresse pas plus que ça, c'est les efforts extérieurs.

**页面中文译文**

那么，第一点，当我们关注刚体系统时，刚体内部没有内部应力，因为刚体不会变形。明白吗？所以，当我们研究刚体时，唯一可以建模的应力类型，也就是我们主要关注的，是外部作用力。

## 149:50

Les efforts qui qui peuvent transiter dans la matière, dans les milieux qui se déforment, les milieux continus, on a des efforts intérieurs, on parle aussi d'efforts de cohésion, c'est les efforts qui permettent de maintenir la matière en cohérence, en cohésion. Ok? Donc quand vous tirez sur votrere barre de métal, là, il y a des efforts qui permettent de.

**页面中文译文**

在物质中传递的应力，在变形的连续介质中，我们称之为内部应力，也称为内聚应力，这些应力使物质保持连贯和内聚。明白了吗？所以当你拉伸你的金属棒时，就会产生这些应力。

## 150:18

Maintenir les particules à à une certaine distance, encore en cohésion. Pour ceux qu'on fait un peu de physique, on peut relier ça aux forces d'interaction entre les atomes. Ok? Donc, à partir du moment où on veut s'intéresser aux milieux continus qui se déforment, aux milieux continus déformables, on est obligé de rajouter ces efforts intérieurs.s.

**页面中文译文**

保持颗粒在一定距离内，仍然保持内聚力。对于学过一些物理的人来说，可以将其与原子之间的相互作用力联系起来。明白了吗？因此，从我们开始关注可变形的连续介质时，就必须考虑这些内部应力。

## 151:11

Donc ça, c'est pour bien faire la séparation entre les efforts intérieurs et extérieurs, et donc on va faire des petits rappels sur la manière de schématiser les efforts qui sont extérieurs. Donc pour ça, on va rappeler ce que c'est qu'un torseur, et on va prendre les différents cas, bien caractéristiques, des efforts extérieurs qui s'appliquent sur un point matériel, donc ça c'est vraiment la base de la mécanique, la physique du point matériel, on considère même pas la forme et l'occupation de l'espace par notre point matériel, c'est typiquement quand on fait de l'étude des astres, on considère que c'est des points matériels dans l'espace, avec une masse et basta, on s'en fout de leur volume, de de toute façon le volume qui est occupé par le vide dans l'espace est prend.

**页面中文译文**

所以，这是为了清楚地区分内力和外力，因此我们将简要回顾如何示意外力的表示方法。为此，我们将回顾什么是力矩阵，并且会举出几个典型的外力作用于质点的例子。这实际上是力学的基础，质点物理学，我们甚至不考虑质点的形状和空间占据情况，这通常用于天体研究，我们将天体视为空间中的质点，具有质量，仅此而已，我们不关心它们的体积，毕竟空间中被占据的体积主要是空的。

## 151:33

Le plus gros de la place. Ensuite, le cas d'un solide rigide, donc d'un corps rigide, là on va prendre en compte son volume, sa répartition de masse dans l'espace, et puis le cas d'un milieu continu, là on va voir qu'il y a des choses qu'on peut faire avec les points matériels ou les corps rigides qu'on va pas trop s'autoriser avec les milieux continus.

**页面中文译文**

最大的部分。接下来是刚体的情况，也就是刚性物体，这时我们会考虑它的体积以及质量在空间中的分布；然后是连续介质的情况，我们会发现，有些针对质点或刚体可以做的事情，在连续介质中是不太允许的。

## 152:22

Donc, c'est parti, on commence par la notion de torseur. Un torseur, par définition, c'est un champ de vecteurs, ça veut dire que on a un vecteur qui va dépendre de l'espace. Ok? En plus de ça, ce champ de vecteurs, il est équiprojectif, ce qui veut dire que quel que soit d'autres points de l'espace M et N, si on prend le champ de vecteurs, donc H exprimé au point M, scalaire le vecteur MN, donc qui relie ces deux points, ça va être égal au même champ de vecteurs, mais exprimé au point M, qu'on va projeter sur le même vecteur MN.

**页面中文译文**

那么，开始吧，我们先从扭矩的概念讲起。扭矩，按定义，是一个向量场，这意味着我们有一个向量，它会依赖于空间的位置。好的？除此之外，这个向量场是等投影的，这意味着无论空间中的任意两点M和N，如果我们取在点M处表达的向量场H，与连接这两点的向量MN做点积，那么这个结果将等于在点N处表达的同一向量场投影到向量MN上的值。

## 153:14

C'est équiprojectif, ça veut dire que la projection de H de M sur MN, c'est égal à la projection de H de N sur MN. Une fois qu'on a défini ça, on peut démontrer, on va pas faire la démonstration, qu'il existe un unique vecteur, donc qui lui ne dépend pas de là où on exprime le torseur, enfin le champ de vecteurs, maisailleurs il en en est est indépendant, on va app appeler R, c'est ce qu'on appelle la résultante du torseur, telle que quel que soit ses points M et N, on peut exprimer le champ de vecteurs H de N à partir de sa valeur au point M, en rajoutant une contribution qui li estée à l'arrêt au produit vec vectoriel de la résultante et du vecteur MN.

**页面中文译文**

这是等投影的，这意味着点M关于线段MN的H投影等于点N关于线段MN的H投影。一旦定义了这一点，我们可以证明（这里不做证明）存在一个唯一的向量，这个向量不依赖于我们在哪表达扭矩器，或者说向量场的位置，而是独立的，我们称之为R，这就是所谓的扭矩器的合力。对于任意点M和N，我们可以通过点M处的向量场H的值，加上一个与合力和向量MN的叉积相关的贡献，来表达点N处的向量场H。

## 153:42

Et donc, par les propriétés du produit vectoriel, si on intervertit le rôle, on change le signe, et si on intervertit l'ordre de, enfin le sens du vecteur, on peut l'écrire sous ces deux formes, ça revient exactement au même. Et donc, le vecteur H de N, donc le champ de vecteurs qui définit notre torseur, c'est ce qu'on appelle le moment en M du torseur.

**页面中文译文**

因此，根据叉积的性质，如果交换两个向量的位置，结果会改变符号；如果改变向量的顺序，最终向量的方向也会改变。我们可以用这两种形式来表示，结果是完全相同的。因此，点N处的向量H，也就是定义我们力矩的向量场，被称为力矩在点M处的力矩。

## 154:18

Donc, en réalité, quand on définit un torseur, on peut le définir par ses éléments de réduction, jea. Par la suite, c'est complètement déterminé si on donne la valeur de la résultante, donc qui ne dépend pas de l'espace, vous voyez, et de son moment en un point N. Et donc ça, c'est ce qu'on appelle les éléments de réduction d'un torseur.

**页面中文译文**

因此，实际上，当我们定义一个力矩时，可以通过它的简化元素来定义。随后，如果给定合力的数值（即不依赖于空间的位置）以及它在某一点N的力矩，那么力矩就完全确定了。这就是所谓的力矩的简化元素。

## 155:11

Donc, c'est souvent noté sous cette forme, la résultante en haut, et le moment en bas. Le moment dépend du point M, auquel sont exprimés les éléments de réduction du torseur. Donc, très bien, R et H de M,. Là, j'ai défini un torseur, très bien, si je veux faire des opérations entre ce torseur-là et un autre, que ce soit une addition, une soustraction, ou même ah non, c'est là où je me rends compte que j'ai peut-être pas mis à jour, ou ce qu'on appelle le co-moment, donc.

**页面中文译文**

因此，通常以这种形式表示，上面是合力，下面是力矩。力矩取决于点M，即力矩的简化元素所表达的点。很好，R和H在点M处。这里我定义了一个力矩螺旋，如果我想对这个力矩螺旋和另一个进行运算，无论是加法、减法，或者……不对，我意识到我可能没有更新，或者说没有考虑共力矩。

## 155:36

Avec un autre torseur, il faut que que je m'assure de bien les exprimer au point M. Je vais faire en fait les opérations, que je vais pouvoir les faire entre la résultante et le moment pour l'addition et la soustraction, à partir du moment où je les ai bien exprimés au même point. Ça n'a aucun sens d'additionner les éléments de réduction de deux torseurs s'ils sont pas exprimés au même point.

**页面中文译文**

对于另一个力矩，我必须确保它们都在点M正确表达。实际上，我将进行运算，只要我能将合力和力矩都表达在同一点上，就可以进行加法和减法。如果两个力矩的简化元素没有在同一点表达，进行相加是没有意义的。

## 156:04

Ok? Donc, si j'ai un torseur T1, T2, du coup, vu que que la résultante ne dépend pas de là où exprimer le torseur, ça change rien, mais par contre ça va jouer sur la partie moment, il faut que je fe. La somme entre les deux moments qui sont liés aux deux torseurs, bien exprimés au même point.

**页面中文译文**

好的？所以，如果我有两个力矩组T1和T2，由于合力不依赖于力矩组的表达点，这不会改变结果，但这会影响力矩部分，我必须做的是将与这两个力矩组相关的两个力矩在同一点正确表达后相加。

## 156:46

Et donc, si je l'avais si on m'avait donné par exemple le torseur T2 exprimé au point B, par l'intermédiaire de cette formule-là, je peux déplacer je peux expririmer mon champ de vecteurs en un autre point. Et donc, une fois que j'ai fait ça, je peux ensuite procéder à la some. Bon, ça c'est pas forcément très important, mais c'est du jargon, un glisseur, c'est un torseur pour lequel il existe au moins un point dans l'espace où le moment il obtient une valeur nulle.

**页面中文译文**

所以，如果我有，比如说给我在点B处表示的扭矩T2，通过这个公式，我可以将我的矢量场表达在另一个点上。一旦我完成了这一步，我就可以进行求和。嗯，这不一定非常重要，但这是术语，“滑移器”是指存在空间中至少一个点使得力矩为零的扭矩。

## 157:14

Ok? Typiquement, un glisseur, quand le torseur one. Pour travailler sur les efforts, ça veut dire que vous avez juste un effort qui est appliqué en un point. Si vous vous éloignez par le bras de levier, ça génère un un moment, ok, par rapport à ce point-là, mais il y a bien un endroit où le moment est nul et il y a que la résultante qui s'applique.

**页面中文译文**

好的？通常情况下，一个滑动体，当力矩为零时。为了研究力的作用，这意味着你只有一个力作用在一个点上。如果你远离这个点的力臂，会产生一个力矩，相对于该点，但确实存在一个力矩为零的位置，只有合力作用在那里。

## 158:29

Par contre, si en un point vous av avez le moment qui est nul, pardon, sur une une droite, vous avez le moment qui est nul, si la la résultante est non nulle en tout point de l'espace, dans ce cas-là, le torseur est nul. Petit raisonnement là-dessus, mais c'est pas quelque chose de central. On revient sur, enfin, on va s'intéresser maintenant à la schématisation des efforts extérieurs, mais on va s'intéresser au cas d'un point matériel, donc vous considéérez par exemple un point matériel de l'espace, par exemple cette télécommande, vous modélisez ça juste par un point géométrique qui a la masse de votre télécommande, les effets de l'extérieur sur M, par exemple si je tape dessus comme ça, c'est j'exerce des efforts dessus, si je le tiens comme ça, vous voyez, il y a le poids de votre télécommande qui s'applique, ça j'ai besoin de rien pour l'appliquer, par contre moi j'exerce un effort dessus parce que par le pr principe d'action réaction, ma main exerce une force sur la télécommande.

**页面中文译文**

但是，如果在某一点上，力矩为零，抱歉，在一条直线上，力矩为零，而合力在空间的任意一点都不为零，那么在这种情况下，力矩系为零。这里有一个小推理，但这不是核心内容。我们回过头来，现在将关注外力的示意图，但我们将关注质点的情况，比如你可以考虑空间中的一个质点，比如这个遥控器，你可以将它建模为一个具有遥控器质量的几何点。外界对质点M的作用，比如我这样敲击它，就是对它施加了力，如果我这样拿着它，你看，遥控器的重力作用于它，这个我不需要做任何操作就存在，但我对它施加了一个力，因为根据作用力与反作用力原理，我的手对遥控器施加了一个力。

## 159:01

Je peux les schématiser par des des forces appliquées en M, des forces ponctuelles, donc vu que je vais réduire ça à juste un point matériel, les seuls efforts que je vais pouvoir appliquer dessus, c'est des torseurs dont la résultante est non nulle, mais le moment va être nul. Sur un point, vous pouvez difficilement appliquer un moment, sauf avec des forces électromagnétiques, mais bon, ça on va laisser ça de de côté pour l'instant.

**页面中文译文**

我可以用作用在点M的力来简化它们，也就是集中力。既然我要把它简化为一个质点，那么我能施加的唯一作用就是力矩的力偶，其合力不为零，但力矩为零。在一个点上，很难施加力矩，除非是电磁力，不过这些暂且先不考虑。

## 159:38

Donc, vous pouvez avoir que des efforts, le moment est forccément nul, donc si vous vous placez dans un repère R qui est galiléen, vous pouvez appeler ce qu'on appelle le principe fondamental de la dynamique, et donc ce principe fondamental de la dynamique, c'est somme des forces est égale à MA, enfin donc somme des forces est égale à M fois l'accélération, l'accélération c'est la dérivée double de la position du point OM, et donc si l'ensemble des forces qui s'appliquent dessus, c'est simplement une résultante, ça s'écrit sous cette forme.

**页面中文译文**

因此，你只能有力的作用，力矩必然为零，所以如果你选择一个伽利略参考系R，你可以使用所谓的动力学基本原理，这个动力学基本原理是力的总和等于质量乘以加速度，也就是说，力的总和等于质量乘以加速度，加速度是点OM位置的二阶导数，如果作用在物体上的所有力的合力就是这个形式。

## 160:04

Ultra simpliste. Maintenant, on passe à un corps rigide. Je vais changer d'objet. Maintenant, je vais considérer cet objet-là, je vais considérer sa forme, son volume, la répartition de la masse dans son volume. Donc, les effets d'environnement extérieur, ils peuvent être schématisés par trois types d'efforts, première chose, les efforts volumiques.

**页面中文译文**

非常简化。现在，我们转向刚体。我将更换对象。现在，我将考虑这个对象，考虑它的形状、体积以及质量在体积中的分布。因此，外部环境的影响可以通过三种类型的力来简化表示，第一种是体积力。

## 160:48

Exemple, la pesanteur, le poids, la force de gravité, c'est un effort volumique. On parle des fois d'efforts à distance, parce que pas besoin de contact entre la Terre et ce stylo pour que la Terre exerce une force de gravitation, une force d'attraction. Ok? Donc, en réalité, vous avez l'habitude de juste prendre le le poids de votre objet et de le multiplier par G, la constante de de gravité, qui est à la 9,80 là, mais en réalité, ça s'applique sur l'ensemble du volume, et donc on a une densité d'effort volumique.

**页面中文译文**

例如，重力、重量、引力是一种体积力。有时我们称之为远距离作用力，因为地球和这支笔之间不需要接触，地球就能施加引力，一种吸引力。明白吗？实际上，你通常只是取物体的重量乘以重力加速度常数G，约为9.80，但实际上，这个力作用于整个体积，因此我们有一个体积力密度。

## 161:15

Si vous voulez représenter ça sous forme d'un torseur résultant qui s'applique au solide, il faut calculer la résultante, ce qui consiste à intégrer ce champ de force volumique qui s'applique à ce solide, et pareil pour le moment, cette fois vous n'allez pas intégrer juste la force volumique, vous allez calculer le moment local qui est appliqué par cet effort au au point A. A

**页面中文译文**

如果您想将其表示为作用于固体的合力矩张量，则需要计算合力，这包括对作用于该固体的体积力场进行积分，转矩也是同理，这次您不仅仅积分体积力，还需要计算该力在点A处产生的局部力矩。

## 161:42

Donc, vous allez transporter sius. Avez typiquement. Cette partie-là qui est beaucoup plus lourde, ok, si vous la tenez comme ça, ça va, vous voyez que ça génère ça va générer un moment qui va être de plus en plus important à partir du moment où vous éloignez du point A, mettons si je positionne mon point A ici, vous avez un effet de bras de levier qui va être de plus en plus important si votre stylo est grand.

**页面中文译文**

所以，你们要搬运sius。通常情况下，这部分会更重，好吧，如果你这样拿着它，你会看到这会产生一个力矩，从你远离点A的那一刻起，这个力矩会越来越大。假设我把点A放在这里，如果你的笔很长，杠杆效应会变得越来越明显。

## 162:13

Donc, vous intégrez AM, vectoriel, le champ de force volumique exprimé au point M. Et donc, ça vous donnera donc les éléments de réduction du torseur au point A, et donc du coup pour le cas d'un torseur d'effort,c. Qui représente les actions mécaniques, la résultante s'exprime en newtons, et le moment en newtons mètres.

**页面中文译文**

因此，您将对点M处表示的体力场进行积分，得到在点A处的力矩简化元件。对于力矩扭矩的情况，它表示机械作用力，合力以牛顿为单位，力矩以牛顿·米为单位。

## 162:35

Donc, l'exemple le plus classique, c'est la pesanteur, mais vous pouvez typiquement avoir les forces d'aimantation, elles peuvent se faire à distance, c'est très certainement déjà joué avec des aimants, vous n'avez pas besoin d'avoir contact entre un aimant et un élément ferromagnétique pour qu'il y ait une force d'attraction qui s'exerce à distance.

**页面中文译文**

最经典的例子是重力，但你通常也会遇到磁力，这些力可以远距离作用。你很可能已经玩过磁铁了，你不需要让磁铁和铁磁性物体接触，磁力就能在远处产生吸引力。

## 163:11

Donc, ça marche ai. Et donc, du coup, vu que si vous intégrez ça sur votre volume complet, vous obtenez des newtons, ça veut dire que cette force volumique, elle est bien exprimée en newtons par mètre cube. Efforts volumiques, on verra que dans la grande majorité des cas, on a plutôt tendance à négliger l'effet de ces efforts, parce que quand vous calculez la.

**页面中文译文**

所以，这确实有效。因此，如果你将其应用于整个体积，你会得到牛顿，这意味着这种体积力确实以牛顿每立方米为单位表示。体积力，我们会看到在大多数情况下，人们倾向于忽略这些力的影响，因为当你计算时。

## 163:31

Résistance d'une caisse mécanique, une caisse d'avion par exemple, généralement les efforts les plus importants sont des efforts qui viennent vraiment de l'extérieur, de la tenue mécanique, de la fonction mécanique de la pièce, et son poids va les déformations qui sont liées aux propres poids de la pièce sont négligeables par rapport aux efforts qui transitent dessus.

**页面中文译文**

机械箱体的强度，例如飞机的机身箱体，通常最重要的应力来自外部，来自机械结构的承载和零件的机械功能，而由于零件自身重量引起的变形相比作用在其上的应力可以忽略不计。

## 163:53

Ça, c'est un exemple, il y a quelques cas où ça peut valoir le coup de prendre en compte l'effet du po poids. Qu Quand vous dimensionnez un pylône pour une. Éolienne, typiquement, il vaut mieux prendre en compte le poids de votre pylône que. Pour éviter qu'il s'effondre par sous l'effet de son propre pos.

**页面中文译文**

这是一个例子，有些情况下考虑自重的影响是值得的。当你为风力发电机设计塔架时，通常最好考虑塔架的重量，以避免它因自身重量而倒塌。

## 164:28

Très bien, alors on a fait les efforts volumiques, maintenant les efforts surfaciques. Donc, on par parle le aussi d'efforts de contact., ok Les efforts surfaciques, souvent c'est par l'effet d'une pression qui est exercée par un fluide sur un solide, ou par un autre solide sur le solide.ide. Donc, là cette fois, on va schématiser ça non plus sur l'ensemble du domaine oméga, mais sur.

**页面中文译文**

很好，那么我们已经讨论了体积力，现在讨论表面力。所以，我们这里也谈到了接触力。表面力通常是由流体对固体施加的压力，或者一个固体对另一个固体施加的压力产生的。这一次，我们将不再在整个域Ω上进行示意，而是在...

## 165:06

Sa frontière. Des ronds oméga, c'est la frontière du domaine oméga. Et donc là, je vais considérer que sur l'ensemble de. Frontière, je vais avoir une répartition d' d'efforts qui peut être variable, elle peut être plus ou moins importante en certains points, ok, et donc cette quantité T, qu'on verra par la suite, et le vecteur contraint, c'est une densité surfacique de force.

**页面中文译文**

它的边界。欧米茄圆圈表示欧米茄区域的边界。因此，我将考虑在整个边界上，受力的分布可能是变化的，在某些点上可能更大或更小。好的，所以这个量T，我们稍后会看到，它是约束向量，是一种表面力密度。

## 165:33

Donc, pour chaque point M qui appartient à des ronds oméga, je vais avoir une valeur différente de cet effort surfacique, et si je veux modéliser l'ensemble des. Des efforts qui sont appliqués sur mon domaine oméga, je vais intégrer cette répartition d'efforts sur l'ensemble de la frontière, ah oui pardon, j'ai mis oméga mais c'est un sigma.ma, ex

**页面中文译文**

因此，对于属于区域Ω的每个点M，我将得到不同的表面力值。如果我想对作用在我的区域Ω上的所有力进行建模，我将对整个边界上的力分布进行积分。哦，对不起，我写成了Ω，实际上应该是Σ。比如说，...

## 166:12

Donc, je vais intégrer cette densité d'efforts surfacique sur la frontière, et pareil, pour avoir le moment résultant au point A, je vais calculer l'effet du bras de levier du point A vers le point M, où s'applique mon eff effort surfacique. Et en intégrant tout ça sur la surface, à la fin, j'obtiens encore une fois un torseur d'action mécanique, donc exprimé en newtons pour la résultante et en newtons mètres pour le même r.

**页面中文译文**

因此，我将对边界上的表面力密度进行积分，同样地，为了得到作用于点A的合力矩，我将计算从点A到力作用点M的力臂效应。通过对整个表面进行积分，最终我再次得到一个机械作用力矩阵，其合力以牛顿为单位，力矩以牛顿·米为单位表示。

## 166:53

Du coup, ma densité surfacique d'effort, c'est bien exprimée en newtons par mètre carré. Ou autrement dit, je dois noter directement, quel est le type de l'unité que je peux utiliser pour une force surfacique? Pascal. Newtons par mètre. Ou aut? Oi. Gigapascal. Kilopascal. Quand on parle de pression, on peut aussi avoir des barres, vous pouvez avoir des PSI, enfin on a toute une zoologie de.

**页面中文译文**

所以，我的表面应力密度确实用牛顿每平方米来表示。换句话说，我应该直接标注，我可以用哪种单位来表示表面力？帕斯卡。牛顿每米。还是其他？哦，对。千兆帕。千帕。当我们谈论压力时，也可以用巴（bar）、磅力每平方英寸（PSI），总之，我们有各种各样的单位。

## 167:29

Très bien, bon ça, ça résume les efforts surfaciques, les efforts de contact, on peut également avoir des efforts concentrés, donc juste une force, ou on a juste un point qui est sollicité. Donc, en un point C, d'un solide par exemple, ou d'un corps genre actuel, on se donne une force CF et le moment qui est relié, bien évidemment, si je tiens mon stylo comme ça et que j'appuie là, ça génère un moment ça peut potentiellement le faire tourner.

**页面中文译文**

很好，这总结了表面力和接触力，我们也可以有集中力，也就是只有一个力，或者只有一个点受到作用。例如，在一个固体的某个点C，或者一个类似流体的物体上，我们施加一个力CF以及相关的力矩。当然，如果我这样拿着笔并在那里施加压力，就会产生一个力矩，可能会使它旋转。

## 167:56

Donc, une force, un moment, le tout exprimé en C, et toujours exprimé dans les mêmes unités. Ça, c'est vraiment le cas ça. Alors, maintenant qu'on a défini pour le cas d'un solide rigide qui ne subit pas de déformation, on peut rappeler le PFD qui, si je reviens un peu en arrière, le PFD pour pour un point matériel, c'était une seule équation.

**页面中文译文**

因此，一个力，一个力矩，全部用C表示，并且始终使用相同的单位。这确实是这样。现在我们已经为不发生变形的刚体情况进行了定义，我们可以回顾一下动力学基本方程（PFD），如果我稍微回顾一下，对于质点来说，动力学基本方程只有一个方程。

## 168:20

Parce qu'on n'a pas de moment généré. Si maintenant je considère le domaine qui reste bien rigide mais qui occupe un volume, là je vais devoir prendre en compte à la fois l'équilibre en résultant et l'équilibre en moment. Donc, en gros, il faut que je calcule le torseur dynamique de sigma.

**页面中文译文**

因为我们没有产生力矩。如果现在我考虑仍然相当刚性的区域，但它占据一定的体积，那么我就必须同时考虑由此产生的平衡和力矩平衡。总的来说，我需要计算σ的动力学力矩。

## 168:52

Et dire que le torseur dynamique, c'est égal au torseur des efforts extérieurs appliqués à sigma. Le torseur dynamique, c'est l'intégrale sur le domaine de la masse volumique fois l'accélération locale du point M par rapport à mon repère, et. Pour la partie moment, c'est la même quantité mais je vais calculer le moment avec le bras de levier qui va du point A au point M.

**页面中文译文**

动态力矩等于作用于区域σ上的外力矩。动态力矩是对质量密度域内的积分，乘以点M相对于我的参考系的局部加速度。对于力矩部分，计算方法相同，但我将用从点A到点M的力臂来计算力矩。

## 169:29

Tout est exprimé l'accélération. Donc ça, c'est pour la partie torseur dynamique, et le torseur des efforts extérieurs, je viens de le préciser, il y a la contribution des efforts volumiques, avec avec mon champ de for force FV, pour force volumique, la contribution des efforts surfaciques, avec la résultante là et le moment, et puis la contribution ici de l'effort ponctuel, avec le.

**页面中文译文**

所有内容都表示加速度。这部分是关于动力扭矩的，而外力扭矩，我刚才已经说明了，包括体积力的贡献，用我的体积力场FV表示，表面力的贡献，包括合力和力矩，还有这里点力的贡献。

## 170:05

La contribution du moment ici sur. Donc, ici là c'est l'équilibre en résultant, si vous voulez, enfin quand je dis équilibre, c'est le PFD en résultant, et là c'est le PFD en en moment. Et là, le PFD il est fait au point A. Bien évidemment, quand j'ai les égalités, je les fais au même point, ok.

**页面中文译文**

这里的力矩贡献。因此，这里是由此产生的平衡，如果你愿意的话，或者说这是由此产生的自由体图（PFD）。这里是力矩的自由体图。而且，自由体图是在点A处绘制的。当然，当我写等式时，我是在同一点进行的。

## 170:33

Donc, bon, j n'ai pas de données sa la définition, mais ici en gros représente bien la masse volumique, qui le plus souvent est exprimée en kilogrammes par mètre cube. Donc là,us avez le PFD qui est donné pour un solide rigide, on va voir que quand on va l'appliquer à un solide un. Corps déformable, ça va nous donner d'autres équations.

**页面中文译文**

所以，我没有关于定义的数据，但这里大致表示的是密度，通常以千克每立方米为单位表示。这里给出了刚体的PFD，我们将看到当它应用于可变形体时，会得到其他的方程。

## 171:03

Alors, on va pouvoir maintenant s'intéresser au milieu qu'on considère comme continu, qui peuvent cette fois se déformer. Donc là, je. Change, maintenant, je mets un oméga pour dire que c'est déformable. Maintenant, pour décrire les efforts les effets de l'environnement extérieur, donc les efforts extérieurs sur ce type de milieu, on va se restreindre à deux types de schématisation.

**页面中文译文**

那么，现在我们可以关注被视为连续且这次可以变形的介质。这里，我改用希腊字母欧米伽（Ω）来表示它是可变形的。现在，为了描述外部环境的作用力，即作用在这种介质上的外力，我们将限制为两种类型的简化模型。

## 171:28

Les efforts surfaciques, et les efforts volumiques. De la même manière, et ça s'applique toujours pour les efforts surfaciques sur la frontière, ou sur une sous-partie de la frontière, et. Donc on est noté et dans le cas où ce serait une donnée, on va rajouter un petit indice d, parce qu'on va considérer que c'est une donnée du problème, donc dans ces cas-là c'est connu.

**页面中文译文**

表面力和体积力。同样地，这也适用于边界上的表面力，或边界的某个子部分。因此，我们用符号表示，在这种情况下，如果它是一个已知数据，我们会加上一个小的下标d，因为我们将其视为问题的已知数据，所以在这些情况下它是已知的。

## 172:09

Pareil, on peut avoir un champ de force volumique, ok, qu'on peut noter FV, et si jamais c'est une donnée, ona. Noter FD comme ça. Donc, ça ce ce s sera presque às. 99 % des cas ce sera une donnée du problème, des fois on vous demandera avec la recalculer, par contre les effortorts surfaciques, il y aura toujours une partie où ils seront inconnus, en général, dans les problèmes, on verra ça plus tard.

**页面中文译文**

同样，我们可以有一个体积力场，记作FV，如果这是一个已知量，就记作FD。几乎在99%的情况下，这将是问题中给定的数据，有时会要求你重新计算它。另一方面，表面力通常会有一部分是未知的，通常在问题中我们稍后会看到这一点。

## 172:37

Donc ce sera pas toujours une donnée du problèème, ou alors ce sera donné que sur une sous-partie de la frontière. Donc, alors au moins dans un premier temps, en fait ça va être tout le temps, dans le cadre de de ce ce mod module, on va pas cons considérer les efforts concentrés appliqués sur un milieu continu, parce que ça va générer des difficultés d'ordre mathématique, parce qu'on va avoir des singularités au niveau du point d'application de ces efforts.

**页面中文译文**

所以这并不总是问题中的一个已知条件，或者说只会给出边界的一部分条件。至少在初期阶段，实际上在本模块的范围内，我们不会考虑作用于连续介质上的集中力，因为这会带来数学上的困难，因为在这些力的作用点会出现奇异性。

## 173:11

Donc, on va oublier les efforts ponctuels, on va se limiter aux efforts surfaciques, aux efforts volumies. Et donc, petite note, là dans le cadre de ce module, on essaye de rester dans un cadre on va dire accessible d'un point de vue analytique, et on va se restreindre au milieu de Cauchy, pour lesquels il n'y a pas de on va pas modéliser les moments locaux qui pourraient apparaître sous l'effet de.

**页面中文译文**

所以，我们将忽略点力，只考虑面力和体力。顺便提一下，在本模块中，我们力求保持分析上的简便，因此将限制在柯西介质范围内，不对可能因某些作用而出现的局部力矩进行建模。

## 173:36

Phénomènes complexes, on va dire, et donc on n'a pas de moment local. Il est possible de formuler des enfin de reprendre les grands principes de la mécanique des milieux continus pour des milieux qui justement permettent des moments locaux, et et donc on peut avoir des milieux représentés de manière plus complexe.

**页面中文译文**

复杂的现象，可以这么说，因此我们没有局部力矩。可以重新阐述连续介质力学的基本原理，针对那些恰好允许局部力矩的介质，因此我们可以用更复杂的方式来描述这些介质。

## 174:11

Parmi ces milieux-là, on peut voir les milieux micromorphes, par exemple, vous pouvez avoir les m matatières enfin les milieux à seconde gradient, et. Donc vous avez vu que qu'à chaque fois là quand je parle je démontrais la cinématique que je dérivais par rapport à l'espace, à chaque fois je faisais un développement limité en prenant le premier gradient, et en négligeant à chaque fois le reste.

**页面中文译文**

在这些介质中，可以看到微形态介质，例如，您可以拥有材料，或者说二阶梯度介质。因此，您看到每次我讲解时，我都是通过对空间求导来推导运动学，每次我都进行有限展开，取第一个梯度，并且每次都忽略其余部分。

## 174:35

C'est une hypothèse enfin c'est une hypothèse, dans les milieux à seconde gradient, on va tenir compte du seconde gradient, voir si on fera on veutut vraiment se faire du mal, on peut aller chercher le troisième gradient, etc.c., mais b Là on est on est vraiment sur dans le cas où on cherche à modéliser des phénomènes assez complexes qu'on qui permettent pas de faire grand-chose quand on veut être à l'échelle de l'ingénur.

**页面中文译文**

这只是一个假设，毕竟是一个假设。在二阶梯度介质中，我们会考虑二阶梯度。如果我们真的想自找麻烦，还可以考虑三阶梯度，等等。但这里我们真正讨论的是在试图模拟相当复杂的现象时的情况，这些现象在工程尺度上几乎无能为力。

## 175:18

Donc c'est pour c'est des modèles fins et complexes, mais assez difficiles à manipuler. Donc c'est pas du tout l'objectif dans le cadre de ce module. Bon, je pense qu'on peut faire la pause maintenant,. J'ai dû penser que enant. Une heure, on va peut-être le le temps de. Et on pourra schématiser les efforts intérieurss, à la reprise.
