Avec autre chose que X comme variable, et ça, ça permet de généraliser très largement les modèles linéaires. Par exemple, si on prend des polynômes,
un polynôme n'est pas une fonction linéaire de X, ok ? En X carré, X carré, ce n'est pas linéaire en X, c'est plutôt sous-linéaire quand X entre 0 et 1, et plutôt sur-linéaire quand on est
au-dessus de 1. Ce n'est pas linéaire en X. Par contre, c'est linéaire par rapport à ses coefficients. Donc si on transforme les X en 1XX carré,
bah ça devient linéaire par rapport au coefficient du... c'est linéaire par rapport au coefficient du polynôme. Donc, du point de vue statistique, les polynômes sont des modèles linéaires.
Parce que ce qui nous intéresse, c'est de voir les modèles comme des fonctions des paramètres à estimer. Donc si c'est linéaire par rapport aux paramètres à estimer,
bah c'est un modèle linéaire. C'est clair, ça ? Donc si je prends, euh , tout ce qui est Fourier, Spline, Ondelette, etc., c'est linéaire par rapport aux paramètres, donc
c'est des modèles linéaires. Les modèles dits « additifs », qui vont prendre des fonctions additives avec des coefficients éventuellement alpha k ici, de... des composantes
du vecteur, sont également des modèles linéaires. Voilà. Don c il y a plein de modèles linéaires qui, en réalité, ne sont pas linéaires par rapport à la variable. Ok ?
Donc dès qu'on est linéaire par rapport aux paramètres, c'est bon pour nous, ça rentre dans les modèles linéaires. Dans...
bon, ça, je le dis une bonne fois pour toutes, pour qu'on soit un peu sensibilisés à la généralité du modèle linéaire. Il ne faut pas se dire « ouais, c'est linéaire, c'est nul ».
Bah, ce n'est pas tout à fait vrai. Ce n'est pas complètement nul. Euh, mais après, pour la présentation, on va rester plutôt sur le premier exemple, hein. On va. .. je ne vais pas parler
des cas où i... où on a la somme des bêta k de h de X, quoi. On ne va pas... ou h de X k. On ne va pas ... je ne vais pas rentrer dans c es. ..
je ne vais pas prendre la présentation la plus générale. Mais il faut juste savoir que le modèle linéaire, ça peut être plein de trucs, dont les modèles polynômes ou autres. Donc,
bonne nouvelle : il y a une solution explicite à la minimisation des moindres carrés, telle que je l'ai formulée tout à l'heure.
Si on recherche le meilleur vecteur, quand on est dans le cas linéaire, ben en fait, il y a une formule, quoi. Quand je dis « il y a une solution explicite », c'est qu'il y a une formule.
Il pourrait ne pas y en avoir. Dans la plupart des modèles d'apprentissage non linéaires, les réseaux de neurones et tout le bazar, on part du même. .. à peu près du même endroit.
C'est-à-dire qu'on cherche à minimiser les moindres carrés. Les moindres carrés, c'est ce qui est utilisé dans le deep learning, hein, c'est...
il y a génératif, ça, c'est des moindres carrés. Sauf qu' on est dans des trucs beaucoup plus compliqués, et il n'y a pas de formule. Donc il faut faire du numérique.
On essaie d'approcher la solution de manière numérique. Ici, dans le cas linéaire, le truc le plus simple : football, il y a une formule. On parle aussi de forme close en mathématiques.
Quand on dit « closed form » en anglais, forme close, ça veut dire qu'on a une solution explicite. On sait faire le calcul, symboliquement, et on a un résultat. C'est quoi ce résultat ?
Eh ben, vous l'avez là, en fait. Donc le HN chapeau, qui est le minimiseur, donc de ... du problème de la minimisation de X ou Y moins H normaux carrés. Ici, le H, comme c'est linéaire ...
en fait, oui, le H dans le cas linéai re, mon H en gras là, c'est en fait X en gras fois bêta en gras. Alors bêta, c'est mon vecteur de coefficients, donc c'est bêta 1, bêta 2, bêta d,
qui est le coefficient du modèle. Et X, c'est la matrice des données. Euh, donc en fait, on va mettre X1 transposé, Xn transposé, comme ça. Donc les Xi, ils vivent en dimension D.
On prend la transposée, ça veut dire que le vecteur colonne, on le renverse, on en fait une ligne. Et donc c'est une matrice qui est N par D.
Donc je peux la multiplier par un vecteur de dimension D. Elle a N lignes, D colonnes. Je multiplie par un vecteur de taille D, et ça me donne un vecteur de taille N, or Y est de taille N, hein,
il est dans RN. Donc c'est bien cohérent. Donc on écrit H comme le produit d'une matrice par le vecteur ... matrice X par le vecteur bêta. Euh, on suppose que X est de rang plein.
Il faut supposer ça, à ce stade. Et dans ce cas-là, on a une solution explicite. Donc H chapeau, c'est X bêta N chapeau. Et bêta N chapeau, c'est quoi ? C'est
X transposé X moins 1, on prend l'inverse de X transposé X, multiplié par X transposé Y. Je vais vous expliquer après d'où ça sort. Vous pouvez résoudre les équations à la main, hein.
Ça peut se faire à la main. Vous avez un méga système linéaire, c'est hyper chiant, mais ça se fait. Voilà.
Maintenant, si vous prenez des écritures matricielles, ça peut se faire de manière très élégante en quelques lignes. Ce qu'il faut retenir de la...
donc je donne d'abord la solution, mais ce qu'il faut retenir de la solution, en fait, c'est que si on prend une représentation géométrique de nos vecteurs, Y vit dans RN. Quand je prends, euh, un
... imaginons qu'on est en dimension 2. Euh , dimension... en dimension 3. Je prends un modèle linéaire avec juste deux variables. Donc c'est bêta 1 , X1 plus bêta 2, X2.
Qu'est-ce que c'est que la solution Y ? Euh, pardon, avec bêta chapeau, en fait, c'est la projection orthogonale de Y dans le plan qui est engendré par X1 X2.
Donc il y a une notion, en fait, dans les moindres carrés de projection. Et donc c'est ce que matérialise cette formule-là.
C'est-à-dire que si vous voyez ici, je n'ai que des matrices, des produits de matrices, Y c'est un vecteur. Donc si je prends ce produit-là , X, X transposé, X moins 1, X transposé,
en fait, on peut vérifier mathématiquement que c'est une matrice de projection. On la note π chapeau. Donc la solution H chapeau, c'est le résultat d'une projection de Y sur un certain plan,
ou sur certains hyper-plan quand on est en grande dimension, ou sur un sous-espace, pour être plus précis, plus général, plutôt. D'accord ? Donc c'est... qu'est-ce que c'est qu'une projection ?
Bah, une projection, c'est ... en gros, il y a cette idée d'orthogonalité , et puis il y a le fait que quand vous projetez un point qui a déjà été projeté, bah c'est l'identité. D'accord ?
Donc il y a deux conditions mathématiques qu'on peut vérifier avec ces. .. ces formules-là. Ça se vérifie. Donc c'est vraiment... π chapeau, c'est un projecteur au sens mathématique du terme.
Alors, comment on démontre en fait cette formule ? Euh , ben en fait, on a... quand on écrit Y moins. .. la norme de Y moins X bêta au carré, ça s'écrit comme ça.
En fait, vous l'avez là, pardon. La forme que je réécris. La norme au carré.
On oublie le 1 sur N, on s'en fout du 1 sur N, hein, quand on minimise par rapport à bêta, ça ne change rien, on a un facteur multiplicatif constant, on peut l'enlever.
Par contre, la norme au carré , en fait, pour un vecteur, la norme de U, c'est U transposé U.
Donc ici, le vecteur c'est Y moins X bêta, mais on a Y moins X bêta transposé multiplié par Y moins X bêta. On prend le vecteur ligne, on multiplie par la colonne, et ça nous fait...
on fait la somme, et ça fait la somme des carrés. Donc on dérive par rapport à bêta, mais en fait c'est le gradient qu'on calcule. Donc vous pouvez vérifier, si vous faites des...
des dérivées composante par composante, que quand vous prenez le gradient, il vous reste une fonction linéaire. Au départ, c'est quadratique,
mais il nous reste une fonction linéaire où bêta, il intervient comme ça, comme 2 bêta transposé X transposé X. Qu'est-ce qui se passe quand on minimise une fonction quadratique ?
Bah, en fait, le minimum, il satisfait la condition de gradient nul, s'il n'y a pas de contrainte. S'il y a des contraintes, ce n'est pas forcément le minimum global. Mais
sinon, c'est bien convexe, c'est gentiment convexe, et donc on annule le gradient. Donc on écrit : la solution, c'est que ce truc-là est égal à 0. En fait, si vous pouvez
inverser X transposé X, ce qui est le cas parce qu'on a supposé que la matrice des données, elle est de rang plein, de rang D. X transposé X, c'est la matrice D par D.
Donc si ça, c'est inversible, bah on trouve. .. on trouve ça. Ok ? Donc on a... il manque peut-être ici le X, hein. J'ai... une faute de frappe. Donc il y a un X ici, hein.
Donc on prend le transposé ... voilà. Donc on a la... voilà, on a la... on utilise aussi, dans ces écritures, que quand on a
deux matrices A, B, on prend la transposée, ça fait B transposé A transposé X , pareil pour les vecteurs, et puis voilà, on en tire le résultat. D'accord ? Donc c'est ...
j'espère vous convaincre par cette slide. Je ne sais pas si certains d'entre vous l'ont fait à l'ancienne.
De l'intérêt d'avoir ces notations matricielles quand on navigue dans les modèles linéaires, hein. C'est... franchement, c'est d'une simplicité .
Il faut s'entraîner un peu, comprendre ce que ça veut dire de... de dériver par rapport, de calculer un gradient, etc., sur ces écritures-là. Mais... mais
franchement, après, ça se fait très simplement. Voilà. Donc là, vous avez une preuve un peu plus classique, en utilisant la notion de composition,
qui est assez courte aussi, mais bon, je ne vais pas... je ne vais pas développer. Alors, on a calculé le minimiseur, et on peut donner un sens maintenant à une notion de critère en moyenne.
Parce qu'en fait, quand je vous avais dit tout à l'heure le L de H, on ne saurait pas le calculer, ou le L de H étoile, ou le L de H barre, on ne sait pas le calculer.
Bon, parce que H barre et H étoile, on ne connaît pas. Je vous ai dit : en réalité, on ne connaît même pas le L. Pourquoi ? Parce que le L, c'est un critère moyenné. On fait une moyenne
sur tous les échantillons possibles de taille N. Mais qu'est-ce que ça veut dire , euh, faire la moyenne sur tous les échantillons de taille N ? Ça veut dire connaître la loi de probabilité,
qu'on ne connaît pas. D'accord ? Donc quand on a une espérance, c'est qu'on fait une moyenne par rapport à la loi de probabilité. Donc c'est en ce sens que c'est un critère un peu théorique.
Donc L de HN chapeau, on va dire que finalement, le critère qu'on va retenir pour comparer H étoile à H chapeau, c'est un critère moyen de l'écart . On prend la...
la norme des différences des prédictions au carré. Ok ? Et l'espérance, c'est une espérance sur tous les échantillons, euh, de taille N possible.
Alors, maintenant qu'on a ça, on peut tout à fait illustrer le compromis biais-variance dans ce cas particulier. Euh, l'idée est la suivante. Donc on va décomposer L de HN chapeau.
L de HN chapeau, vous l'avez ici. Et on va faire apparaître le. .. un terme de... de biais, un terme de variance. Donc comment ça marche ? En fait,
HN chapeau, on a vu que c'était la projection de Y par la matrice π chapeau. On se ramène à cette écriture-là. Y est défini par le modèle.
J'avais dit : Y, c'est le point de départ, c'est H étoile plus ε. Donc on remplace ... euh, on remplace donc Y par H étoile plus ε, et on s'amuse maintenant à regarder la différence entre
H étoile et HN chapeau. H étoile, on laisse en l'état. Donc quand on fait H chapeau moins π chapeau de H... euh, pardon, H étoile moins π H... π chapeau de H étoile,
en fait, ça revient à écrire l'identité moins π chapeau appliquée à H étoile. Et il nous reste un moins π chapeau ε . Donc maintenant, on prend la norme au carré de cette différence .
Et alors, ce qui va se passer, c'est que quand on prend la norme au carré de cette différence, on va voir... on va décomposer ça. Donc ça va faire la somme des carrés plus un double produit.
Sauf qu e, du fait de l'orthogonalité, parce que π chapeau est une matrice de projection, le sous-espace... l'image du sous-espace engendré par IN moins π chapeau
et l'image du sous-espace π chapeau sont orthogonales, parce que c'est une projection orthogonale. D'accord ? Donc le double produit disparaît par orthogonalité. Ça fait...
ça fait comme une covariance qui est égale à 0. Et là, il reste la somme des carrés, donc des deux termes. Donc là, vous avez
le terme espérance de norme de IN moins π chapeau de H étoile au carré, plus π chapeau de ε, qu'on prend la norme au carré. Alors, il se trouve que le. .. vous allez me dire : le ε... bon,
on est un peu embêtés par ça. On comprend que c'est un terme de biais, d'accord ? Parce qu'il y a l'espace dans lequel on projette les estimateurs, et puis il y a le H étoile là où il est.
Donc on comprend que c'est une différence entre la meilleure fonction, enfin la fonction obtenue par l'algorithme, et ... et enfin, en plus, c'est en espérance, donc on peut dire que c'est
le meilleur résultat possible. Donc c'est un terme de biais. Euh, et là, il y a le π chapeau ε, qui est lié au bruit et qui donne un terme de variance. Alors, il se trouve que
dans l'hypothèse où ε suit une loi gaussienne avec les caractéristiques, les hypothèses qu'on a données tout à l'heure, en fait, on sait faire le calcul. Et ça fait σ2 D sur N, ce terme.
Et là, on retrouve quelque chose qui était classique en statistique, qui était de dire : bah, en fait, quand on a
le choix entre plusieurs modèles linéaires, on a des données en dimension D, mais on peut aller chercher des modèles de taille différente de D. Peut-être des modèles plus simples.
Certes, nos données sont en dimension D, mais peut-être qu'un modèle de dimension 3 , ça marche bien. Donc, pour aller sélectionner ce modèle, donc la dimension du modèle plus petit,
en fait, on a tendance à pénaliser les moindres carrés par un terme qui est proportionnel à la dimension de l'espace divisé par N. Et le facteur de proportionnalité, c'est σ2.
Ça veut dire que σ2, on ne connaît pas forcément, il faut l'estimer. Donc ça, c'est ce qu'on appelle le critère d'équalité en sélection de modèles en statistique.
Alors, vous avez une explication pour d'où vient le D sur N. C'est ce qu'on appelle... je ne vais pas développer tout ce qui est un peu technique, mathématique.
Je ne vais pas vous donner les explications. C'est juste pour que vous sachiez d'où ça vient. S'il y en a qui s'intéressent, vous allez regarder,
les calculs se font très bien, il n'y a pas de problème, mais il faut y passer un petit moment dessus. Je pense que pour la majorité d'entre vous, ce n'est pas forcément le point clé de...
pour la compréhension du cours. Mais des fois, on a besoin un peu de technique. Mais par contre, vous devez savoir cette histoire de D sur N. Le résultat, vous devez le connaître.
Euh, donc c'est ce qu'on appelle le théorème de Cochrane. En gros, l'idée, c'est que quand on projette un vecteur gaussien et qu'on prend la norme au carré, ça suit une loi dite du chi-2.
Donc c'est comme les lois gaussiennes. Les lois du chi-2 sont méditables. On... numériquement, on sait parfaitement les écrire. Et donc on sait calculer la variance d'une loi du chi-2.
Et donc c'est comme ça qu'on obtient la dimension de l'espace dans lequel on projette. Alors, ça, c'est ce qu'on...
ça, je vous ai dit, il y a une première partie, c'est la statistique dite classique. Maintenant, il y avait un grand défi dans les années 2000, notamment
du fait des données génomiques, qu'on a eu ce défi-là, c'est que les données génomiques, ça nous mettait d'emblée dans des espaces avec 3 000, 4 000 dimensions.
Donc vous prenez une séquence d'ADN. Dans chaque site de la séquence , vous avez une lettre. Donc c'est une. .. c'est une valeur, on peut dire. Euh, et
par contre, des sites comme ça, vous en avez 3 000, 4 000 dans une séquence. Ça veut dire qu'on a une variable en dimension 3 000, 4 000. Et donc se posait la question de, bah, d'utiliser ces. ..
ces séquences de génome pour faire des prédictions. C'est-à-dire : est-ce que la personne, elle va développer un cancer ? Est-ce qu'elle va développer une maladie neurodégénérative, etc.
C'était un grand sujet à l'époque. Vous le savez tous aujourd'hui. Comment, à partir de la génomique, on peut faire une prédiction sur l'état de santé de la personne,
ou sur des risques qu'elle pourrait avoir par la suite ? Donc ça nécessite, pour ces gentils modèles linéaires, on a vu qu'on pouvait les calculer, etc.
On avait des formules, hein, pour calculer le meilleur estimateur linéaire. Euh, ça nécessitait de pouvoir aller sur des problèmes de grande dimension.
Alors, je souligne que quand on dit « en grande dimension », ça ne veut pas dire grand-chose. Il y a deux régimes. Il y a un régime qui est de dire : grande dimension dans l'absolu.
Quand je vous dis 3 000, 4 000, ah ouais, c'est grande dimension. En réalité, du point de vue de la théorie statistique, si j'ai 100 000 observations, 3 000, 4 000 dimensions, ce n'est pas énorme.
D'accord ? Donc, euh, la grande dimension, c'est plutôt l'inverse. C'est le cas où j'ai beaucoup de variables et des petits échantillons. C'était le cas de la génomique.
C'est-à-dire qu'on avait 3 000, 4 000 variables, mais en réalité, on avait une centaine de patients sur chaque étude. Donc la grande dimension, c'est plutôt le cas
qui est un peu le drame du statisticien du 20e siècle. Là où il rend son tablier, c'est si j'ai plus d'inconnues que de variables. C'est comme. ..
enfin, vous, si vous faites des systèmes, vous avez fait des systèmes linéaires, sûrement vous avez dû en manger un peu, par exemple du numérique et tout ça. Pour ceux qui en ont fait.
Bon, bah, quand il y a plus d'équations que d'inconnues, on rend son tablier et on dit : bah, désolé, là, je ne sais pas faire, quoi. Le statisticien, pareil, quand il y a
moins d'observations que de paramètres, il dit : je suis désolé, là, je... moi, je ne sais pas faire. Je. .. Donc, au 20e siècle, c'est un problème qu'on ne sait pas résoudre.
Donc ce qui a été le gros ... le grand bon en avant, c'est que vous parlez à un data scientist du 21e siècle : pas de problème, je vous le fais. Ça,
la grande rupture sur les modèles linéaires. Et ça a utilisé des idées aussi. Ce n'est pas étranger au machine learning, à tout ce qu'on a fait par la suite, hein, et au raisonnement.
Ce n'est pas étranger. C'est juste qu'on est dans un cas où il y avait des choses classiques, et on peut voir comment on peut les améliorer. Alors, il faut bien être sensible à ce fait-là .
Euh, donc ce que j'avais dit aussi, c'est que la matrice X des données, elle est de remplint. Maintenant, si on a moins de données que de dimensions, elle est plus de remplint. Elle est de rang E+N.
Qu'est-ce qui se passe si elle est plus de remplint ? Enfin, là, il y a deux problèmes qui se posent dans les deux régimes de grande dimension. Est-ce que vous voyez lesquels, en fait ?
Quel problème se pose quand D est très grand par rapport à la solution que je vous ai montrée là ? Par rapport... la solution, elle est là. Qu'est-ce qui se passe quand D est très grand ?
Premier régime, hein : D largement plus grand que N. Quelle est la difficulté ? Quelle est la nature de la difficulté qui se pose avec cette solution ? Si D est largement plus
grand que N, ça veut dire qu'il doit avoir un nombre d'échantillons qui est... Alors, imaginons qu'on a ... on a la matrice de remplint. On a un très grand... beaucoup d'échantillons.
Donc, dans le premier régime, on ne met pas forcément en défaut ce côté-là. D'accord ? C'est dans la... après, j'aurais une deuxième question, c'est : qu'est-ce qui se passe si
D est plus grand que N ? Donc, euh, elle est... elle est à la moyenne de 52,9 . Hum, non, pas forcément. Si D est très grand. Vous avez fait un peu de calcul de matrices.
Qu'est-ce que vous avez fait ? Qu'est-ce qui est dur dans le calcul de matrices ? C 'est l' inversibilité de la matrice. Comment ? L'inversibilité de la matrice. L'inverse.
Calculer des inverses, numériquement, ça peut être chaud. C'est instable, souvent. Je pense que vous avez dû voir un peu les stratégies. Donc,
calculer des inverses, on n'a pas trop envie de le faire, c'est un peu chiant. Il y a des précautions à prendre. Et c'est numériquement instable. Qu'est-ce qui se passe si D est grand ?
X transposé à X, c'est une matrice D par D. On doit calculer l'inverse d'une immense matrice. Bah, en fait, ça, on ne sait pas faire, quoi. On ne sait pas faire. Au-delà d'un certain
D, on ne sait pas faire. C'est juste... numériquement, pas possible. Donc, D grand, la grande dimension,
ça ne remet pas en question la théorie, ça ne remet pas en question les formules, ça ne remet rien en question. C'est juste que, numériquement, ça devient un peu chaud. D'accord ?
Ça, c'est le premier régime. Deuxième régime de la grande dimension : si D est beaucoup plus grand que N. Qu'est-ce qui se passe ? Toujours dans cette formule.
Ça, c'est un autre problème qui se pose. Même quand D n'est pas hyper, hyper grand. Simplement, il y a plus de dimensions que de ... plus de variables que de données.
Bah, c'est mon hypothèse qui tombe, hein. C'est que X n'est plus de remplint, parce qu e. .. vous voyez, je suppose que D est plus petit que N. Donc si D est plus grand que N,
le rang de la matrice X est N, si c'est plus petit que D. Et donc, bah, l'inverse n'existe même pas. Je n'ai pas d'inverse. La matrice n'est pas inversible. D'accord ? Donc là, ça me fait même. ..
ma-mon équation, elle ne marche plus. Ce n'est pas que j'ai un problème pour la raison, c'est qu'elle ne marche plus. Donc c'est un challenge, la grande dimension.
Alors, juste un petit paramètre, c'est que, euh, la notion de dimension, il faut faire un peu attention à qu'est-ce qu'on met derrière.
C'est-à-dire que là, quand on est dans un modèle linéaire avec des c ovariables ou des variables de base qui sont indépendantes, c'est la dimension au sens classique,
quand vous regardez des espaces vectoriels, ce que vous avez appris à l'époque. Maintenant, si on est dans un monde non linéaire... et oui, dans...
pardon, dans ce monde un peu idéal, là, et simple, il y a un peu un amalgame entre nombre de paramètres et dimension de l'espace. Et ça, ça marche quand on est dans un...
dans le cas des modèles linéaires. Si les modèles ne sont pas linéaires, il faut faire très attention avec le nombre de paramètres.
Ce n'est pas forcément un bon indicateur de la complexité de la famille de fonctions. En réalité, le concept clé, c'est celui de complexité. On peut donner un sens mathématique à cette notion
en apprentissage statistique. Mais voilà, il peut y avoir une ambiguïté sur ce qui est le bon... la bonne manière de qualifier la complexité. D'accord ?
Donc là, il se trouve que la dimension, c'est le bon... la bonne notion, mais c'est juste parce qu'on est dans le modèle linéaire. Alors, juste, euh , je vous fais une petite. .. un petit
interlude, là, jingle, pour vous parler de ce que c'est que des données en grande dimension. Euh, parce qu'on peut se dire
: bon, bah, OK, on sait ce que ça veut dire en dimension 2, en dimension 3, on sait faire des petits dessins. Donc quand on est en dimension N, en gros, ce qu'on a dans la tête en dimension 2 et 3,
ça marche pareil, quoi. Un mathématicien, en gros, il se dit ça. Je ne peux pas me représenter parfaitement la géométrie du tas de dimensions D,
quand D est plus grand que 3, mais je me dis : ça va marcher de la même manière. Bon, cette... ici, c'est pour vous montrer que ce n'est pas vrai.
Donc les espaces de grande dimension ont une géométrie très spéciale. Et donc ça peut donner de très mauvaises intuitions si vous étendez vos raisonnements en dimension 2 ou 3, en dimension
supérieure. Comment on va illustrer ça ? Imaginez que j'ai une orange. Alors d'abord, l'orange, je l'écrase. On est en dimension 2. Enfin, je l'écrase. Je fais une coupe de l'orange.
Je garde une tranche de l'orange. OK ? J'ai un disque. Et je garde la pelure. Donc là, là, c'est l'orange normale en dimension 3. Et là, c'est une orange en dimension 1000. Dans ces trois cas,
je vais regarder le volum e, euh, le volume qui est dans la pelure de l'orange. Donc j'enlève. .. j'ai ... disons que mon orange, elle est de rayon 1, quelle que soit l'unité.
Ça va des centimètres, mais là, c'est 1. Ça veut dire que c'est... je normalise à 1 le rayon de l'orange. Et la pelure, euh, elle mesure, par exemple, si c'est 0,0 05 de mon unité de départ.
Donc si le rayon de l'orange avec la pelure, c'est 1, le rayon de la... de la... pardon, de l'orange avec la pelure, c'est 1, le rayon de l'orange sans la pelure, c'est 0,9 95.
Dans les trois cas, c'est ça : la notion de rayon, c'est un nombre . Même si je suis en dimension 1000, je définis des boules avec des rayons, hein, ce n'est pas un problème.
Donc dans les trois cas, le rayon de l'orange sans la pelure, c'est 0,9 95. On peut faire un calcul mathématique en calculant le. ..
pour calculer le volume de la pelure, en disant : bah, j'ai le volume de la boul e. Ça, ça vaut toujours 1, parce que je prends toujours des rayons 1.
Et maintenant, on calcule le volume d'une boule de rayon 0,9 95. Il se trouve que ce calcul-là, bon, bah, c'est... je ne sais pas, c'est peut-être un tiers de πr3 quand vous êtes en dimension 3.
Euh, quand vous êtes en dimension 2, c'est πr2, tu vois. Euh, on sait calculer les surfaces, les volumes en dimension 2, 3. On sait les calculer en dimension D aussi.
Et alors là, qu'est-ce qui se passe ? Quand je fais le calcul en dimension 2, j'ai 1 % de la surface qui est dans la pelure. Donc j'ai 99 % à l'intérieur, 1 % qui est la pelure de l'orange.
Dimension 3 , la pelure, elle prend 1,5 % du volume. C'est-à-dire que j'ai 98,5 % du volume qui est mon orange. Quand on vit en dimension 1000, ce n'est pas une idée de se nourrir avec des oranges.
Parce qu'en fait, en dimension 1000, la pelure prend 9 9 % du volume. 1 %, c'est ce qu'il y a à l'intérieur. 99 %, c'est tout le bord. Donc si vous voulez remplir cet espace avec 100 points,
vous répartissez de manière plus ou moins homogène, bah, en fait, tous les points vont être dans le bord. Il n'y aura aucun point au centre.
Alors que quand vous échantillonnez en petite dimension, tous les points sont à l'intérieur. Il n'y aura très peu de points sur le bord.
La conséquence de ça, c'est que tous les points sont très loin les uns des autres, qui sont tous sur le bord. C'est fou, hein ? Ça ne vous impressionne pas ?
C'est vraiment très contre-intuitif, quand même. On ne s'attend pas à ça. Donc c'est intéressant de faire le calcul et de voir vraiment ce que ça donne. Et
en fait, ça dit beaucoup de choses sur le monde moderne, si vous réfléchissez bien. Enfin, ça rejoint ce que je disais tout à l'heure sur mon exemple de marketing.
C'est-à-dire qu'évidemment, quand on décrit la population avec deux variables, bah, il y a plein de gens qui se ressemblent beaucoup .
Si on décrit la population avec 1000 variables, bah, il n'y a pas une personne pareille que l'autre. Et ça, dans tout ce qui est justement , enfin,
la consommation de biens culturels, pourquoi est-ce que la VOD, tous ces trucs-là ont explosé, tout ce qui passe par les plateformes a explosé ?
C'est que, bah, maintenant on peut décrire les préférences culturelles des gens avec beaucoup, beaucoup de variables. Avant, on n'avait pas accès à ces variables.
Et donc il y a une personnalisation extrême, en fait, de tout ce qui est proposé. Et il y a donc les canaux pour acheminer ces biens qui sont très personnalisés. Enfin, l'offre, elle est
très, très personnalisée. Parce que tout le monde est très différent l'un de l'autre. Il suffit de regarder suffisamment de choses, on se rend compte qu'on est...
qu'on est tous très différents. C'est un vrai challenge pour la médecine aussi, par exemple. C'est-à-dire qu'un médecin qui regardait trois variables, bah, il pouvait se dire : « J'ai...
OK, j'ai deux protocoles. » Maintenant, si on regarde 1000 variables, le médecin, il est cuit. Il n'a plus... il ne sait plus quoi faire.
Parce qu'il y a autant de protocoles qu'il n'y a de personnes. Et un protocole médical, c'est des ressources, c'est des médicaments, c'est des... des stratégies de traitement, etc.
Donc tout devient très différent. Et ça, c'est un vrai challenge, en fait. Après, c'est un challenge logistique, en fait, dans cette...
voilà, on va y faire quelques lectures si vous voulez creuser le côté grande dimension.
Alors, ce n'est peut-être pas un mauvais moment de prendre la pause, parce que maintenant on va voir la partie moderne des modèles linéaires. OK ?
Donc avant de vous poser des questions sur cette partie-là, je m'éclaire. Donc j'insiste pour que vous reteniez bien les concepts, les idé es.
La technique, il faut savoir ce qu'il y a derrière, mais je... moi, je ne veux pas vous demander de faire des méga-calculs et de me redémontrer des trucs, hein. Ce n'est pas ça l'idée.
Par contre, il faut que vous ayez bien compris les concepts. Ça peut nécessiter aussi, pour vous, de passer un peu de temps pour aller voir de près certains calculs.
Ça dépend de ce que chacun est capable d'appréhender. Il y a des versions très simples, il y a des versions très compliquées. Là, vous avez quand même
les principaux repères pour aller explorer ces concepts-là. OK, bon, bah écoutez, on va prendre une pause jusqu'à 11 h 15. 13 minutes de pause.