D'abord la partie vraiment de base, le concept de base, c'est celui de Parsimony, ça s'appelle Sparsity en anglais,
des fois on traduit par « sparsité », c'est un anglicisme, mais le mot français c'est Parsimony. Ensuite, on va voir comment on peut, dans certains cas,
se servir de ce qu'on a fait là pour estimer des fonctions non linéaires. Il y a des fois où le passage du linéaire au non linéaire, il est assez différent.
Et puis on va voir des formes de généralisation après de ce qu'on aura raconté avant . Alors, j'ai déjà expliqué ce que ça veut dire « grand », et il faut bien distinguer les deux régimes.
Donc les problèmes d'inversibilité de la matrice carrée dépardée, mais aussi les problèmes d'instabilité numérique, les deux volets. Alors, qu'est-ce qui se passe quand la matrice
est de rang n'est plus de rang plein ? On a toujours plus d'échantillons que de variables. Alors, à ce moment-là, le problème des moindres carrés, il a plusieurs solutions. Et on peut avoir
une estim ation de l'estimateur des moindres carrés en calculant la pseudoinverse. Ça, c'est des choses que peut-être vous avez vues dans vos cours de ... non, ça ne
vous parle pas, la pseudoinverse ? Donc si vous regardez des livres de méthodes d'algèbre linéaire, enfin de méthodes numériques pour l'algèbre linéaire,
vous allez tomber dessus, c'est quand même un truc hyper standard. Voilà, donc il y a une stratégie pour dire : « Voilà ce que ça donne ». Il y a plein de solutions, mais on peut avoir
typiquement la solution de norme minimale, par exemple. On a une notion de... ça fait intervenir la matrice de projection, et puis ... enfin, sur le sous-espace qui est de rang plein, et
voilà, on arrive à écrire quelque chose. Alors, ce qui est marrant, c'est que l'instabilité numérique, il y a une stratégie pour ça, qu'on voit justement
quand on fait un cours sur les méthodes numériques en algèbre linéaire. Et c'est typiquement de dire qu e, pour inverser la matrice, ça ne fait pas de mal de rajouter un terme sur la diagonale.
On rajoute une perturbation sur la diagonale, et on calcule l'inverse, qui est l'inverse d'une approximation de la matrice de départ, avec cette perturbation.
Mais ça permet le calcul de l'inverse de manière beaucoup plus robuste, donc on n'a plus ces instabilités. E t, de manière ... je ne sais pas si c'est étonnant, mais en tout cas
on peut l'affirmer, c'est qu'il y a une version statistique, en fa it. Ça, c'est fait pour des raisons numériques. Mais en fait, il y a une interprétation statistique de ça, qui revient à
dire qu'on va régulariser les moindres carrés en rajoutant une pénalité qui fait intervenir la norme de ... la norme au carré, pardon, du vecteur des coefficients.
Donc si je prends mes moindres carrés, je pense que je l'ai... pas loin après. .. je vais juste ... c'est assez loin, en fait. En gros, on a vu qu' on avait...
les moindres carrés, c'est y moins x bêta au carré. Ça, c'est x sur n. Et donc ça, c'est les moindres carrés, qu'on appelle les least squares en anglais. Eh bien, au lieu de minimiser ça,
on va minimiser un critère où on va rajouter un terme additif. Donc lambda, c'est positif, c'est un nombre positif. Et ça, c'est la norme du vecteur bêta au carré.
Donc c'est la somme des carrés des coefficients de bêta. Donc ça, c'est ce qu'on appelle la régular isation ridge, quand il y a cette norme. Là, c'est la norme de ...
alors je précise, la norme de, c'est celle que je vous ai définie tout à l'heure. Et comme on va avoir d'autres normes, je la réécris ici. Donc c'est la somme des carrés, la norme de.
On va jouer avec le concept de norme, justement, pour avoir l'espace. Donc ce critère statistique, qui consiste à dire
: « Je minimise les moindres carrés, mais je vais pénaliser les bêtas qui ont une norme très importante ». C'est-à-dire que là
, pour bien minimiser ça, je vais plutôt avoir tendance à prendre des bêtas qui ont des grandes normes. Et donc ici, ce terme, il va dire : « Ah bah, vous voulez une grande norme ?
Vous payez un prix », parce que ça vient se rajouter dans le critère, les grandes normes. D'accord ? Donc ça nous force à chercher des bêtas qui ont des plus petites normes que
si on faisait des moindres carrés sans la pénalisation. Il se trouve que ça, c'est ... on a une forme, rappelez-vous, cause-forme pour ça. On a une forme, une solution exacte par une formule.
Quand on rajoute ce terme, on a toujours une solution exacte avec une formul e. Et la seule différence
, c'est que le x transposé x qui intervient dans la formule, il est remplacé par x transposé x plus lambda l'identité de rd. Donc là, on avait l'inverse de ça, on a l'inverse de ça.
C'est la seule différence. Vous pouvez vérifier. Et ça, ça revient à rajouter un lambda sur la diagonale. C'est exactement la stratégie qu'on avait pour
répondre au problème de l'instabilité numérique. Donc là, c'est un endroit... enfin, c'est assez exceptionnel, hein, que vous ayez ... souvent c'est des mondes un peu
séparés, les considérations statistiques et les considérations numériques. On essaie de les faire converger, mais souvent les motivations, elles sont différentes.
Il se trouve que là, on a une lecture par les deux prismes qui conduit à la même équation. Donc ça mérite d'être souligné, quand même. Ce n'est pas commun. Ok ? Donc
ça explique pourquoi ces modèles-là, finalement, à un moment donné, ils ont été populaires. Ce sont des modèles de référence, etc., et ça parle à deux communautés différentes.
La communauté des numériciens et la communauté des statisticiens. Mais maintenant, on va jouer justement avec cette notion de régularisation. Alors, je rappelle les notations. On a toujours y = x
bêta étoile + ε. X est la matrice des données n par D. On a bien des données de dimension D, un vecteur de paramètres de dimension D. On va s'intéresser à des modèles
qu'on va appeler creux, ou sparse, ou parsimonieux. Mais je trouve que c'est bien de parler de modèle creux, ça peut être plus facile de retenir ce qu'on entend par là.
Ce sont des modèles linéaires. Le modèle linéaire, au départ, il a des coefficients. Un modèle creux, c'est quoi ? C'est un modèle où on va éteindre certains coefficients.
On va les éteindre, on va les mettre à 0. Donc il y a certaines coordonnées du vecteur qui ne vont pas apparaître dans le modèle prédictif. Alors on peut se dire : « Mais pourquoi faire ça ?
» En fait, ça a une certaine logique. C'est-à-dire qu e, pour reprendre notre histoire du client qui demande un prêt, on va lui faire remplir, je ne sais pas, 200 questions, 100 ou 200 questions.
Peut-être qu'il y en a qui ne servent à rien, en fait.
Souvent, on a des données, elles sont là, on les a enregistrées, on les a numérisées, on ne sait pas pourquoi on les a collectées au début.
Au final, on s'aperçoit qu'il y a plein de données qui ne sont pas pertinentes pour faire la prédiction.
Donc l'idée, c'est de se dire : « Au lieu de m'épuiser à calculer tous les paramètres pour toutes les dimensions, je vais me concentrer sur ceux qui comptent, sur ceux qui
vont vraiment avoir un effet sur la prédiction. » D'accord ? Donc il y a cette idée sous-jacente qu'il y a trop de variables par rapport à ce qu'on veut faire.
Donc on va considérer des modèles plus petits. Et l'hypothèse centrale, ici, c'est de se dire que le bêta étoile,
qui correspond au meilleur modèle, au h*, le h* c'est x bêta étoile, rappelez-vous. Donc ce meilleur modèle, en fin de compte, bêta étoile, a plein de coefficients qui sont égaux à 0.
Le point clé ici, c'est pour ça que la méthode, elle est quand même intéressante, c'est que la seule hypothèse qu'on va faire, c'est sur
la taille de ce modèle, c'est-à-dire le nombre de coefficients non nuls. Imaginons, on a 100 variables, d = 100. J'ai 100 variables.
Et il y a une petite voix qui me dit : « Non, mais en fait, tu n'as pas besoin des 100 variables, tu n'as besoin que de 20 variables. » Ce que ne me dit pas la petite voix,
c'est : « Quelles sont les 20 variables ? » D'accord ? Ça, c'est une grosse différence. Parce que si je savais quelles étaient les 20 variables, je me ferais fâcher, et je prendrais
le modèle avec les 20 variables, j'estimerais ... j'ai la formule explicite, et bam, je n'ai pas besoin de régulariser quoi que ce soit. Enfin, je peux régulariser si j'ai des problèmes
liés au numérique, mais je n'ai pas de problème d'ivariance, quoi. Je connais la solution. Je connais l'espace de la bonne solution. Je connais l'espace précisément.
Je n'ai pas dit que je connaissais la dimension de l'espace. Là, ce que je vous dis, c'est qu'on connaît la dimension de l'espace, mais on ne connaît pas l'espace.
Donc là, ce n'est pas la même histoire, parce que je cherche un espace de dimension 20 au milieu d'un espace de dimension 100. Combien il y en a, des comme ça ? Un peu de combinatoire ? 2 0
parmi 100. 20 parmi. .. nombre de combinaisons de 20 parmi 100, ça fait combien, ça ? C'est beaucoup, oui. C'est 100 puissance 1. Ça fait beaucoup. D'accord ? Ça fait beaucoup.
Donc la petite voix, elle est sympa de me dire la dimension, mais elle n'est pas très sympa de ne pas me dire les variables. Parce que là, ça me laisse avec un problème qui est quand même un
problème combinatoire difficile. Malgré tout, c'est ce problème qu'on va craquer maintenant. Alors, on introduit ce qu'on appelle la norme 0 du vecteur. C'est quoi la norme 0 du vecteur ?
On a vu la norme de, c'est : on fait la somme des carrés des coefficients. La norme 0, c'est qu'on fait la norme des puissances 0 du vecte ur, des coefficients du vecteur.
Sauf que 0 puissance 0, on prend comme convention que c'est égal à 0. Donc en fait, qu'est-ce que ça fait ? C'est en train de nous compter combien il y a de coefficients qui ne sont pas 0.
La norme 0. Donc c'est le 20 de tout à l'heure. D'accord ? Je suis en dimension 100, mais la petite voix me dit : « Il y en a 20, donc la norme 0 de mon bêta étoile est égale à 20. » Ok ?
Comment on fait, maintenant, pour trouver ce fameux sous-espace avec les 20 variables qui sont allumées ?
Première stratégie, on appelle ça la formulation d'Ivanov, c'est de dire : « On va résoudre les moindres carrés, et on va résoudre les moindres carrés pour tous les modèles de taille 20. »
20 ou plus. Donc ça veut dire minimiser y moins x bêta, la norme de au carré de ce vecteur, c'est les moindres carrés. Le 1 sur n, on s'en fout, on peut l'oublier, sous la contrainte
que la norme 0 est plus petite que 20. Sauf que ça fait combien de problèmes à résoudre ? Là, c'est un mix, en fait. C'est ce qu'on appelle l'optimisation mixte.
Parce qu'en fait, j'ai un problème continu, qui est le problème des moindres carrés, mixé avec un problème combinatoire, parce que je dois me balader dans un espace de dimension ... enfin,
je dois me balader dans un espace... enfin, dans un nombre de possibilités qui est le nombre de combinaisons de 20 parmi 100. Donc soit de l'ordre de 100 puissance 20.
Enfin, c'est un ordre de grandeur, hein, 100 puissance 20, c'est juste pour vous dire que c'est grand. Donc je dois résoudre autant de moindres carrés qu'il y a d'espaces possibles. Voilà. Donc
c'est une stratégie possible. Il y a des heuristiques pour se balader, mais c'est un peu stratégie Pac-Man. On va être un peu gloutons, et on ne va pas être très optimaux.
Il y a une autre stratégie, qui est de dire : « On va poser un problème intégré qui va juste être un problème d'optimisation. »
Le problème d'optimisation intégré, c'est de dire : « En fait, au lieu de régulariser par la norme de, ça on connaît bien, enfin on reviendra plus tard sur le ridge,
c'est de rajouter une pénalité qui est lambda fois la norme 0 de bêta. » Comme ça, j'ai juste ce problème d'optimisation à résoudre. Alors il reste mixte, parce qu'il y a du continu et
du discret. C'est un mixte discret-continu. C'est ça, la difficulté ici. Donc ça, c'est la formulation régularisée qu'on appelle la formulation Tichonov.
Alors Tichonov, il y a toute une littérature dans les problèmes mal posés, dans les années 60-70, ces approches. Il y a beaucoup de littérature là-dessus. Notamment pour
pas mal de problèmes d'ingénierie physique, c'était ce genre d'approche qui était retenue. Alors si vous avez fait... je ne sais pas si vous avez fait des cours d'optimisation.
Est-ce que la méthode des multiplicateurs de Lagrange, ça parle à certains d'entre vous ? Oui ? Il y en a qui hochent la tête. Bon.
Si vous avez fait les multiplicateurs de Lagrange, vous pourriez dire : « Non mais là, vous êtes en train de nous mener en bourrique, parce que c'est la même chose. »
C'est-à-dire qu'on peut voir la deuxième formulation comme une formulation du premier problème. Donc optimiser sous contrainte, on passe les contraintes dans
la formulation du problème, avec des multiplicateurs. Donc le lambda, ce serait le multiplicateur. Bon.
En réalité, dans ce cas précis, donc en général, c'est vrai, c'est équivalent en général, mais il y a des hypothèses. C'est que les contraintes, elles sont différentiables.
Or là, il n'y a pas la différentiabilité, donc il n'y a pas l'équivalence. Donc ces deux problèmes sont différents. Ce sont deux approches différentes
qui ne sont pas équivalentes pour répondre un peu au même objectif. Mais numériquement, ça peut donner des résultats différents. Alors,
donc c'est ce que j'explique là dans les commentaires, c'est que ça ressemble à une formulation lagrangienne. Le deuxième
ressemble à une formulation lagrangienne du premier, mais en réalité, ce n'est pas équivalent, parce que la norme 0, elle n'est pas dérivable.
On est juste en train de compter des coefficients non nuls, donc ce n'est pas dérivé, ça. Les stratégies qu'on a pour répondre au premier problème sont des stratégies itératives.
C'est en fait une heuristique. On se dit, par exemple : « On va commencer avec le plus petit modèle où il y a une seule variable. On va calculer son coefficient, ok ? Et puis après,
on va garder ce coefficient, et on va chercher le meilleur modèle où il y a une deuxième variable, on ne sait pas laquelle c'est, on va aller chercher la meilleure.
On va avoir un deuxième coefficient. On va garder ces deux premiers coefficients. On va chercher le modèle à trois variables avec le meilleur troisième coefficient.
On va estimer, et ainsi de suite. » Le problème dans cette stratégie, c'est qu'on est optimal à chaque étape. D'accord ? Donc passant d'un modèle avec
deux coefficients qui ont été estimés, avec deux variables qui sont fixées, on sait chercher le meilleur où il y a une troisième variable. Mais en fait, ce n'est pas le meilleur
parmi tous les modèles à trois variables. On n'a pas exploré cet espace. On a juste pris un chemin dans cet espace. Ok ? Donc ça, c'est les stratégies itératives. Et bon, elles marchent bien
quand on a des trucs un peu améliorés. Et ce sont des domaines de recherche assez récents, enfin de l'ordre de 10 ans. Et puis
je crois que les équipes continuent à travailler là-dessus, ce qu'on appelle les problèmes mixtes en optimisation.
Alors il y a d'autres applications, ce n'est pas que pour ce que je vous ai présenté là. Mais là, c'est un peu. ..
je veux dire, ce sont des stars de l'optimisation, MIT, qui travaillent là-dessus. Ce n'est pas un truc marginal, c'est quand même. .. enfin. Mais c'est très limité. On peut gérer jusqu'à 35 ...
des modèles avec 35 dimensions. Donc ça, c'est pour liquider un peu la première approche Ivanov avec le problème sous contrainte.
On va plutôt regarder les stratégies avec une régularisation qui est intégrée dans le critère qu'on optimise. Alors rappelons-nous de ce qu'on a vu tout à l'heure. Tout à l'heure, on a vu ça.
La question, c'est : est-ce qu'il y a un lien entre cette décomposition de bivariance et le problème d'optimisation des moindres carrés avec un critère 0 ? Ça, c'est un point qui est
détaillé ici. Alors pour bien comprendre le lien, en fait, il faut rentrer un peu dans le détail. Et pour rentrer dans le détail, il n'y a rien de mieux que de regarder un exemple.
Ce n'est pas le cas où c'est le plus intéressant d'utiliser une méthode un peu automatique, mais ça a l'avantage de... on peut représenter un peu les choses. Prenons des données en dimension 3.
Donc un modèle linéaire complet de dimension 3. Il y a trois variables. Donc ça s'écrit y = x bêta étoile + ε . Il y a combien de sous-modèles quand bêta étoile est de dimension 3 ?
En fait, il y en a 8. C'est 2 puissance 3. Le nombre de manières d'allumer/éteindre des coefficients quand on en a 3, il y en a 8. Soit il y a le modèle
qui est un modèle constant, il y a 0 variable dedans. Ça, c'est un premier modèle. Il y a le modèle complet avec 3 variables allumées, ça il y en a 1 aussi.
Et puis après, si on regarde les modèles de taille 1 , il y en a 3 possibles : soit on allume la première variable, soit la deuxième, soit la troisième. Et les modèles avec 2 variables,
il suffit de choisir laquelle on éteint. Donc il y en a 3 aussi. Donc au total, il y a 8 modèles qui sont en compétition dans ce cas avec 3 dimensions. Ok ? Alors comment on peut s'y prendre ?
Il faut faire la sélection de modèles. Imaginons qu'on fasse là, il y en a 8, on peut faire les calculs, on peut calculer les 8 estimateurs des moindres carrés. Comment on calcule ça ?
Bon, là, il y a des notations peut-être un peu. .. qui peuvent refroidir un peu, mais en réalité, si vous regardez de près, ce n'est pas si compliqué que ça. C'est que
X, c'est notre grande matrice de données n par 3 . Si on regarde des sous-modèles, ça revient à enlever certaines colonnes. Ok ? Donc on va noter Xm,
la sous-matrice de données, qui correspond au modèle où on a enlevé les colonnes qu'on ne voulait pas. Et à partir de là, on utilise la formul e. On
suppose qu'on a plus de variables que de dimensions, donc on peut calculer l'inverse, tout ça. On fait le calcul, et on a à chaque fois un estimateur des moindres carrés.
La question maintenant, c'est : lequel est le meilleur parmi tous ceux-là ? Là, on a 8 estimateurs des moindres carrés. Lequel est le meilleur ? On va s'appuyer sur la qualité de la prédiction.
Donc on a cette mesure d'erreur ici, Rm, qui regarde, en espérance, l'écart entre la prédiction avec un des estimateurs moindres carrés sur des modèles qui sont potentiellement plus petits.
Enfin, il y a le modèle complet, mais il y a aussi les plus petits, par rapport aux prédictions qui sont faites avec le thêta étoile idéal. Donc le meilleur
modèle, c'est celui qui minimise ce critère en espérance. Sauf que l'espérance, on ne la connaît pas. On ne sait pas calculer la moyenne, parce qu'on ne connaît pas la probabilité.
Puis on ne connaît pas non plus le thêta étoile, en fait. Donc ce qu'on fait, la stratégie statistique ancienne, c'est de dire : «
En fait, il faut minimiser le critère des moindres carrés sur les prédictions des étiquettes, des y, avec une pénalisation qui fait intervenir la dimension du modèle. »
Quand je mets valeur absolue de M, M c'est un ensemble de sous-indices. Les indices, ils vont de 1 à D. M, dans les notations que j'ai utilisées, c'est un sous-ensemble d'indices.
Donc par exemple, si mon D c'est 3 , et que j'allume les coefficients des variables 2 et 3, le modèle M, c'est la collection d'indices de 3.
Quand je mets une valeur absolue, c'est le cardinal de cet ensemble. Donc le cardinal ici, c'est 2, parce que j'ai 2 coefficients actifs. Ok ? Donc c'est la dim ension du modèle,
du petit modèle que je suis en train de considérer. Donc M, c'est l'estimateur des moindres carrés pour ce modèle,
et je pénalise par la taille du modèle, en comptant combien il y a de variables non nulles. Et tout ça avec un facteur multiplicatif qui est 2 sigma carré. Ça, c'est ce que me dit la théorie.
Ok ? Et ça, vous voyez que je peux calculer le M empiriquement. Je calcule le meilleur modèle empiriquement en minimisant ce critère. Donc là, j'ai une stratégie numérique plausible.
Ce n'est pas ... enfin, sauf qu'il faut aller stapper tous les estimateurs. Là, on explique comment sort le sigma carré. Bon, c'est toujours le théorème de Cockrade sur un sous-espace, en fait.
Alors le problème, c'est que quand D est grand... ça, c'est la stratégie ancienne. Le problème, c'est que quand D est grand, comment on fait, quoi ? Parce que déjà, il faut calculer tous
les modèles. Il y en a de l'ordre de l'exponentielle D sur 2. Le pire des cas, c'est le maximum du coefficient binomial, donc c'est au niveau de D sur 2, que vous avez le plus de modèles à scanner.
Et il y a un autre problèm e, qui n'est pas mentionné ici, c'est qu' en gros, Akaike a tendance à surestimer la complexité du vrai modèle. Et en fait, vous voyez qu'
en fait, il ne compte pas bien, quoi. Parce que quand je suis là ... quand je suis là, vous voyez que je vais compter une complexité de 2, alors que j'ai 3 modèles différents.
Et là, j'ai une complexité de 1, alors que j'ai 3 modèles différents aussi. Donc il n'y a pas de lien entre la complexité et le nombre de modèles à scanner.
Donc là, il y a un petit truc qui ne va pas avec le critère AIC. Donc tout ça pour dire que quel est l'avenir ? L'avenir, il est là. Voilà. C'est de passer
d'arguments statistiques tels que ceux qui ont été évoqués tout à l'heure. Alors je n'ai pas détaillé comment on trouve le critère de Akaike, tout ça. On a parlé de bivariance, tout ça.
Donc dans l'idée, ça reste valide, l'histoire de bivariance. Mais on va plonger vraiment dans ce qui est l'optimisation. Le machine learning, c'est de l'optimisation.
Les statistiques, ça va vous expliquer, mais ce n'est pas le driver de comment on formule les algorithmes. Donc on a vu que dans
ce qui a été évoqué précédemment, pour faire la sélection de modèles, il y avait toute cette dimension combinatoire, discrète, et toutes ces heuristiques qui ne sont pas optimales.
Et la question à laquelle on voudrait répondre, c'est ce que j'ai dit en introduction de cette partie, c'est de dire : « Certes, on veut estimer dans un petit modèle,
mais aussi en même temps, on voudrait trouver quel est ce petit modèle. » On voudrait faire les deux en même temps.
Si on ne fait pas les deux en même temps, on est obligé de scanner toutes les possibilités. C'est exactement la même situation avec les réseaux de neurones. À la place
de nombre de variables, vous pourriez par exemple penser nombre de couches, ou nombre d'unités dans une couche d'un réseau de neurones, nombre d'unités de calcul.
Et là, il y a aussi ce paradoxe où, en fait, on se fixe l'architecture, on fixe le nombre d'unités, on fixe le nombre de couches, et après on estime.
Et ce qu'on aimerait, c'est trouver l'architecture optimale et estimer en même temps. Alors il y a des artifices dans la manière d'utiliser les réseaux de neurones qui permettent,
dans une certaine manière, d'aller explorer des sous-modèles. Je pense par exemple au dropout. Le dropout, c'est une option dans les réseaux de neurones. Ça revient un peu à faire ça.
Ça revient à aller chercher des sous-modèles. Parce qu'on va éteindre des connexions. D'ailleurs, même de manière aléatoire. Il n'y a pas vraiment de critère pour faire ça.
Mais ça a un effet de régular isation qui est un peu similaire à ce qu'on va voir là. Donc on voudrait faire les deux en même temps. Et en fait,
ce qu'on aimerait faire, c'est quand même avoir un problème convexe. Parce que quand c'est convexe, on sait qu'on peut optimiser plus facilement.
Quand on prend une normale 0, ce n'est pas du tout convexe. Donc l'idée simple qui a été introduite autour de 2006, à peu près, c'était de dire : « Remplaçons L0 .
» Donc là, vous voyez, on avait dans la formulation que je donnais tout à l'heure une norme 0 ici. Alors la norme 2, elle est convexe, elle est sympathique.
Mais elle n'est pas tellement adaptée quand on a une grande dimension. Et donc l'idée, c'est d'aller chercher une pénalité qui laisse le problème convexe, mais qui est entre 0 et 2.
Qu'est-ce qui est entre 0 et 2 ? 1. Prenons une norme 1. C'est ça l'idée, toute bête, qu'ont eue les gens. Vous voyez, entre les années 60, 19 60 et 2006, donc presque 50 ans,
en gros, on est passé du 2 à 1. Voilà, on peut voir ça comme ça. Donc qu'est-ce que c'est que la norme 1 ? On met un 1 ici. La norme 1 , il n'y a plus de carrés d'ailleurs.
C'est juste la norme 1. Ça, c'est ce qu'on appelle la pénalité massive. Tout à l'heure, c'était Ridge avec les deux , et là, c'est la pénalité dite massive.
La norme 1, c'est la somme des valeurs absolues des coefficients. La valeur absolu e, c'est convexe. Donc on a... ça, c'est quadratique, donc c'est convexe aussi.
C'est par rapport à bêta que ça nous intéresse. Donc ça, c'est comme un polynôme de degré 2 en bêta, donc c'est convexe. Polynôme de degré 2. Et on
ajoute une autre fonction convexe, qui est la fonction des valeurs absolues des bêta x, qui est convexe aussi. Quand on prend la somme de deux fonctions convexes, ça reste convexe. Ok ? Donc
ça, c'est quelque part la plus petite fonction convexe qui domine le problème précédent avec la norme 0. C'est une approximation du modèle précédent. La question maintenant, c'est
: déjà, est-ce qu'on peut le résoudre numériquement, et est-ce que ça fait bien ce qu'on veut ? À savoir aller chercher un modèle creux. Parce qu'ici, il n'y a pas de restriction sur le bêta.
On a le bêta dans Rd. D'accord ? Donc là, le problème, c'est de chercher tous les coefficients possibles. Et alors là, c'est assez magique. Là, vous avez la formulation du lasso.
On passe de la normale 0 à la norme L1. Et le lasso, en fait, c'est génial. En fait, c'est génial parce que déjà, il y a des garanties ici théoriques. Quelque part, comme on...
je ne vais pas commenter, mais tout à l'heure, quand on pénalisait par du D sur N, en fait, pour que ça tende vers 0, il fallait que D soit fixé, que N tende vers l'infini.
Donc il y a un moment donné où N doit être plus grand que D. Or, dans les régimes de grande dimension que j'ai évoqués en motivation,
j'avais dit : « Nous, ce qu'on aimerait, c'est avoir D plus grand que N. » Et si D reste plus grand que N, dans le régime asymptotique, ça veut dire qu'il
n'y a aucune chance pour que D sur N tende vers 0. Et donc ça posait une grosse question sur la validité de tout ce qui a été écrit avant, sur le plan théorique.
Ici, quand on fait les calculs, on s'aperçoit que l'erreur de prédiction par rapport à l'optimum,
en fait, elle est majorée par un terme dont la dépendance en N, elle est en racine de log de D sur N. Donc le fait qu'on ait du log de D au lieu d'avoir du D, ça change tout.
C'est-à-dire que vous pourriez avoir quelque chose qui est entre N et N puissance D, par exemple. Non, pas N puissance D, plus petit que D, justement. N3, par exemple. Ça serait plus grand...
vous voyez que D serait plus grand que N, en N cube. Et quand on prend le log de N3, ça fait du 3 log de N sur N, ça tend bien vers 0. Ok ? Donc même quand D est plus grand que N,
tant qu'on est dans un régime qui est strictement plus petit, qui a un petit taux de N puissance D, en fait, ça marche, ça va tendre vers 0. Ok ? Donc voilà.
Donc ça, déjà théoriquement, ça a été démontré comme ça. Et l'autre truc génial, c'est que numériquement auss i, ça se passe très bien. Alors il y a eu,
pendant quelques années, en fait, les gens proposaient plusieurs algorithmes pour résoudre le lasso. J'en dirai peut-être un mot un peu plus tard. Mais en gros, ce qu'on peut obtenir
par cette résolution numérique, c'est ce qu'on appelle des chemins de régularisation. Parce que quand on régularise ici par une norme 1,
à vrai dire, je ne sais pas quelle va être la taille du modèle. La petite voix, elle m'a dit : « Ton modèle, il est de taille 20. » Mais si ça se trouve,
en optimisant comme ça, je vais trouver un modèle de taille 25, peut-être 40, qui sera le meilleur. L'avantage donc de la résolution numérique, c'est que ça nous donne des chemins de régular
isation qui vont permettre de tracer la valeur des coefficients pour chaque variable qui est dans le modèle, en fonction , en gros, de... en fonction du lambda. C'est-à-dire qu'ici, l'ordonnée. ..
pardon, l'abscisse, c'est un peu le lambda, sauf que lambda égale 0 ici, lambda égale infini ici. Ça revient à ça, en fait. Donc qu'est-ce qui se passe quand lambda égale 0 ?
Vous avez la solution des moindres carrés sans pénalité. D'accord ? J'enlève la pénalité, donc j'ai juste les moindres carrés.
Donc là, je suis à lambda égale 0, donc toutes les valeurs, là, chaque couleur, en fait, correspond à une variable. Donc j'ai les valeurs des moindres carrés, ici.
Quand j'augmente le lambda, je commence à régulariser. Donc je paie un prix pour utiliser des normes 1 élevées. Et qu'est-ce qui se passe quand j'augmente le lambda ?
En fait, ce que vous voyez, c'est qu'il y a des coefficients qui s'éteignent au fur et à mesure. Quand lambda égale infini, je n'ai plus aucun coefficient dans ma combinaison.
Donc c'est que la solution, c'est juste bêta égale 0, quand lambda égale infini. Parce qu'on privilégie la pénalité par rapport au moindre carré. Et donc
la solution, si on ne minimise que la norme, c'est 0. Mais ce qui est intéressant de voir, c'est que. .. donc si on veut 20 variables, on compte une, deux, trois... enfin, il
y en a moins que 20, donc ça ne va pas. Mais imaginons qu'on veut 3 variables. Si on veut 3 variables, on regarde les 3 premières qui s'annulent l'une l'autre.
Les 3 variables que je vais garder si j'ai un modèle de taille 3. Si j'ai un modèle de taille 4, il faut que je rajoute la rose. Si j'ai un modèle de taille 5, je rajoute la orange. Ok ?
Donc ça donne une lecture très intuitive et interprétable des différents modèles. Et ça me donne, d'une certaine manière, le meilleur modèle pour différentes tailles de modèles.
J'ai des valeurs de coefficients par rapport à ça. Donc qu'est-ce qu'il faut retenir de cette stratégie ? On va aussi prendre un peu de recul. Ces
idées-là, elles sont fondamentales en machine learning. C'est qu'en gros, si on regarde bien qu'est-ce qu'on optimise, il y a un critère qui est optimisé par rapport à une fonction de décision
H. Et on a ce qu'on appelle une erreur d'apprentissage. On parle aussi, dans certaines communautés, de terme d'attache aux données. C'est le terme qui
rend compte du fait que la fonction H, elle colle bien à mes données. Donc ce qu'on veut, c'est qu'un modèle prédictif, il colle bien aux données d'apprentissage. Mais
on ne veut pas qu'il colle trop. C'est pour ça qu'il y a un terme de pénalité. Une pénalité de H pour pénaliser les H qui collent trop aux données.
Parce que ce qu'on soupçonne, c'est qu'un H qui colle trop aux données, il risque de faire du surapprentissage. Et donc ça veut dire que sa variance explose.
Même si son biais diminue, parce qu'on sait que plus il est complexe, plus le biais va diminuer, mais le risque, c'est que ça fasse exploser le terme de variance.
Donc on cherche des H simples qui collent bien aux données. Et ça, c'est bien résumé par ce genre de formulation. Avec ce genre de formulation, déjà, vous pouvez appréhender
beaucoup, beaucoup, beaucoup de méthodes de machine learning. C'est super ? Ouais. Le surapprentissage, ça veut dire que le programme est meilleur ? Enfin, c'est le truc fort ou. .. Non.
Ça veut dire que le modèle est trop complexe par rapport aux données, donc il estime le bruit. Donc il ne voit pas le bruit, il a l'impression que le bruit, c'est de l'information.
Il va interpréter le bruit, et au final, il va être vachement oscillant. Sur le problème de régression, ça fait des fonctions vachement oscillantes.
Et donc ça, en prédiction, c'est la catastrophe. Ça fait l'impression que ton modèle, il est parfait sur tes données d'apprentissage. Et dès que tu vas l'utiliser en pratique, tu vas avoir
des prédictions qui vont être vraiment n'importe quoi. Donc on a l'impression de prendre un modèle plus puissant, et en réalité, il a trop interprété les données historiques.
C'est pour ça que la notion de bruit, elle est importante . D'ailleurs, il y a des... parfois, même c'est documenté dans certains articles, il y a des gens qui
vont prendre des données et qui vont rajouter du bruit artificiellement dans les données pour rendre plus robustes les procédures d'apprentissage.
C'est aussi un peu ce que fait l'IA générative, enfin les gens qui mettent en place ce genre de solutions. C'est une stratégie qui est utilisée de bruiter des données.
Donc le bruit a un rôle très vertueux dans les données. Après, s'il n'y a que du bruit et il n'y a pas d'information, tu ne peux rien découvrir non plus.
Tu n'as pas de structure, et donc tous les modèles... dans ce cas-là, tous les modèles sont mauvais. Mais voilà, le risque d'overfitting, c'est un risque principal, j'ai envie de dire.
Donc quelque part, vous avez une bonne maîtrise d'un algorithme de machine learning. Si vous êtes capable de mettre en évidence le régime d'overfitting, et de le contrôler après. Mais en fait,
un modèle puissant, il doit overfitter. Donc ça peut être intéressant de montrer l'overfitting, et de montrer comment on arrive dans une zone où il n'y a pas d'overfitting.
Ça, je le dis pour les TP que vous aurez, dès que vous allez avoir entre les mains des méthodes de machine learning, quelles qu'elles soient. Même avec le modèle linéaire, vous pouvez le voir.
Voilà. Donc cette formulation, elle est hyper générale. Il y a une question, c'est : « Ouais, mais le lambda, qu'est-ce qu'il fout là ? Et qu'est-ce qu'on en fait, du lambda ? »
Alors le lambda, c'est ce qu'on appelle un paramètre de régularisation. Il faut voir ça comme un paramètre d'échelle. C'est l'échelle
qui vous donne l'ordre de grandeur que vous attribuez à la pénalité. Il y a des manières de le calibrer à partir des données. C'est ce qu'on appelle la validation croisée.
Vous verrez ça aussi en TP, comment vous calculez, par validation croisée, le paramètre de régularisation. D'accord ? Il y a une manière de le calculer. Petit problème. Quand on fait
notamment des réseaux de neurones, mais dans pas mal de méthodes d'apprentissage un peu sophistiquées, il y a plein de paramètr es. Il y a plein de paramètres. Il n'y en a pas qu'un seul.
Quand il y en a un seul, pas de problème. Vous prenez une grille de lambda. Vous dites : « Le lambda, il est entre, je ne sais pas, 0 et 100. » Et puis après, on peut zoomer.
On prend lambda égale 0,01, 0,002, etc. On calcule les résultats pour tous ces lambdas, on choisit le meilleur. Le problème, c'est : qu'est-ce qui se passe s'il y a 10 paramètres ?
100 paramètres. Ce qui est le cas des réseaux de neurones. Donc la validation croisée, on oublie. On ne va pas pouvoir le faire.
Il va falloir prendre des hypothèses très fortes sur certains paramètres. Ce qu'on appelle des... en fait, ce n'est pas des paramètres, on appelle ça des hyperparamètres.
Les paramètres, ils sont réglés par l'apprentissage. C'est l'optim isation qui va les trouver toute seule. Les hyperparamètres, c'est tout ce qu'on doit régler à l'avant.
Et quoi qu'on en dise, quelle que soit l'IA, machin, il y a toujours des trucs à régler à l'avant. Il y a toujours un savoir-faire d'un humain qui va choisir des paramètres. D'accord ?
Quand on vous dit : « Les algorithmes vont prendre le contrôle, etc. », il y a des gens qui disent : « Mais c'est de la foutaise.
» C'est juste, voilà, il y a quelqu'un qui les aura programmés et qui aura fait des choix à la main où, effectivement, ça peut aboutir à la fin de l'humanité. C'est possible. Mais
c'est parce que quelqu'un aura réglé les paramètres d'une certaine manière, aura réglé les critères aussi d'optimisation d'une certaine manière. Pourquoi Claude est gentil ?
Pourquoi Claude est gentil ? Pourquoi il vous répond poliment ? Parce qu'il y a quelqu'un qui a mis dans les critères qu'il doit répondre poliment. Mais on pourrait très bien avoir
un Claude qui est agressif, quoi. C'est possible. Qui n'est pas poli, qui insulte. C'est tout à fait possible. C'est des choix de modélisation. C'est des choix humains de modélisation.
Ce n'est pas la machine qui se dit toute seule : « Je vais être sympa. » Ce n'est pas du tout ça. Ok ? Voilà. Donc ça, c'est les hyperparamètres.
Les hyperparamètres, c'est le problème le plus difficile, parce que c'est des choix humains. Et en général, il y en a beaucoup, beaucoup, beaucoup à régler.
Et donc là, ce n'est pas optimisé, là. C'est rarement optimisé. C'est pas l'optim isation de multifonction s. Ouais, mais il faut beaucoup de... enfin, si tu veux, je sais que
tu retombes sur le même problème de l'estimation en grande dimension. C'est-à-dire que le nombre d'hyperparamètres devient la dimension du problème.
C'est un espèce de méta-problème d'apprentissage. C'est-à-dire que la dimension, ça devient le nombre d'hyperparamètres, et le nombre de données,
c'est le nombre de runs d'apprentissage que tu peux faire avec différents hyperparamètres. Or l'apprentissage, c'est ce qui est le plus coûteux. Donc tu es typiquement dans des situ ations
où tu as un problème d'estimation en très grande dimension, avec des tout petits échantillons. Enfin, là aussi, tout est relatif, mais a priori, tu as des petits échantillons
par rapport à la taille de ton problème. Donc statistiquement, là aussi, c'est un problème qui est beaucoup plus dur que le problème d'apprentissage, tu vois, qui a été formulé.
Alors, c'est là où on arrive sur ce qui va être le plus intéressant, je pense, pour vous, parce que là, il y a de la ... c'est des choix de modélisation, c'est des choix humains, et où on pe
ut, je pense, innover encore, à mon avis, sur certains des problèmes, notamment
sur les problèmes qui ne sont pas des problèmes de l'IA générative, qui sont des problèmes plus ciblés dans l'ingénierie, dans la santé, dans l'industrie, enfin voilà.
Et là, il y a quelques exemples sur les modèles linéaires où ça a été fait. Donc l'idée est la suivante : si je fais du lasso, donc le lasso, il va aller spontanément chercher
des modèles creux . Il va éteindre des coefficients, et il va me dire : « Voilà ce qui est un bon compromis entre ta prédiction et le nombre de coefficients non nuls. »
Ça, c'est ce que fait le lasso par construction. Donc ça, c'est top. Et donc là, si vous imaginez ces cases-là comme
les indices des coefficients, donc c'est noir quand ils sont allumés et gris quand ils sont éteints. Donc lasso va aller m'allumer des coefficients. D'accord ? J'en ai peut-être
100 au départ, il va aller m'en allumer 20. Donc ça fait 20 cases noires. Ok ? Mais peut-être que ce n'est pas tout à fait ce que je veux, en fait.
C'est bien d'avoir un modèle creux, mais peut-être pour des raisons d'interprétabilité , et pour, oui, peut-être expliquer la décision
, ou peut-être aussi parce que j'ai une connaissance a priori de certains mécanismes qui sont derrière la prédiction. J'ai en fait des informations que je n'ai pas données au modèle.
Par exemple, dans ma problématique d'allocation de crédit, j'ai mes clients. J'ai un peu évoqué ça dans la première séance. En fait, j'ai des catégories de variables. Parce que je vais avoir
des variables qui sont des caractéristiques socio-démographiques, c'est-à-dire que ça, elles sont ce qu'elles sont, votre âge, votre sexe, où est-ce que vous habitez, etc.,
votre profession, au moins pendant une périod e, ça ne bouge pas trop, comme votre situation familiale. Donc on peut dire que sur une période, ce sont des choses qui restent relativement fixées.
Ça, c'est des informations socio-démographiques. Donc ça, ça ne bouge pas. Après, vous avez des données qui sont liées à votre comportement .
Donc la banque, elle a un historique de ce que vous avez fait, et donc il y a des données comportementales qui sont corrélées ou non à votre état socio-démographique.
C'est-à-dire que deux personnes, elles peuvent venir du même milieu, avoir le même âge, les mêmes caractéristiques, tout pareil.
Et puis, il y a des gens qui sont honnêtes, et des gens malhonnêtes. Enfin, je veux dire, ça, c'est une question de valeur morale, de comment on est éduqué, etc. Ce n'est pas forcément...
ce n'est pas quelque chose qu'on va lire dans les informations socio-démographiques. Donc le comportement va nous donner d'autres inform ations. Mais
socio-démographique, ce n'est pas qu'il ne faut pas le prendre en compte, parce que ça peut aussi influencer une décision d'allocation de crédit. Par exemple, je ne sais pas, mais si on a
la zone géographique où vous habitez, et dans cette zone démographique. .. dans cette zone géographique, il y a eu, je ne sais pas, des catastrophes naturelles, des inondations.
Il y a plein d'entreprises qui ont, je ne sais pas, leurs entrepôts inondés, etc.,
et que vous, vous êtes a priori actif dans cette région-là, on se dit : « Là, le crédit, ça va être compliqué, parce que les boîtes vont être
en difficulté, parce qu'il y a tous ces dégâts matériels. Et donc avoir un crédit, ça va devenir plus compliqué.
» Là, c'est souvent des interventions de l'État, d'ailleurs, pour dédommager des victimes, qui vont apporter des fonds.
Mais une banque, elle ne va pas prêter si elle voit qu'il y a un risque important qui est lié à des éléments de contexte, et qui ne sont pas du tout liés à votre comportement bancaire. Ok ?
Ou ça peut être... mais ce qui arrive auss i, enfin, je veux dire, moi j'y suis confronté, par exemple, c'est-à-dire, vu mon âge, avoir un crédit aujourd'hui immobilier,
c'est plus dur que pour vous, même si j'ai peut-être un meilleur niveau de rémunération, parce que je travaille depuis longtemps, j'ai un métier qui n'est plutôt pas trop mal rémunéré,
voilà. Mais mon âge fait que j'ai plus de risques de mourir demain que vous, quelque part. C'est vrai. Donc la banque, elle va regarder ça aussi. Donc l'âge devient éventuellement un critère.
Enfin, c'est l'assurance qui va dire : « Pour des personnes âgées, la prime, elle va être 100 fois plus grande, par exemple. »
Vous voyez que ces caractéristiques socio-démographiques, indépendamment du comportement bancaire, vont influer aussi sur la décision. Et il y a plein de situations comme ça.
Et pour la génomique, ça a été introduit pour la génomique, d'ailleurs, ce truc-là, c'est de dire : « En fait, il y a des groupes de gènes. » Et donc ce qu'on aimerait, c'est ...
en fait, pour les décisions qu'on veut prendre après, on a envie d'avoir des informations qui prennent en compte cette information de groupe. Si je donne juste des indices,
je n'ai pas cette information de groupe. Donc l'estimateur, il va aller voir où il y a de l'information, et il va juste allumer les variables. Maintenant, si je lui donne cette information de groupe,
je peux introduire de la sparcité dans les solutions au niveau des groupes. Ok ? Donc je peux avoir envie de contraindre
: quand il y a une variable qui s'allume dans un groupe, je voudrais que toutes les variables s'allument dans le groupe.
Et ça, ça va me permettre de dire, finalement, c'est quoi les groupes de variables qui influent le plus sur la prédiction. Donc là, c'est ce qu'on a avec ce qu'on appelle le groupe lasso.
Vous voyez, là, il va allumer. .. il m'a éteint le groupe 1 , il m'a allumé le groupe 2, il m'a éteint le groupe 3, et il m'a allumé le groupe 4.
Alors que le lasso, lui, il aurait distribué un peu sur tous les groupes. Comment on fait cet effet de groupe lasso ? C'est par ... en modifiant la pénalité. C'est-à-dire qu'au lieu de prendre
une pénalité L1, je vais faire un mi x. Elle est là. Je fais un peu un mix de L1 à L2. C'est-à-dire que j'ai du L1 , parce que j'ai la norme. .. en fait,
si vous voulez, c'est comme si je remplaçais les coefficients dans un groupe par un seul coefficient, en faisant la somme de la norme L1 des coefficients.
Je prends la somme des normes des coefficients. Donc au niveau des groupes, c'est comme si j'avais du lasso. Sauf qu'à l'intérieur des groupes, je prends une norme 2 .
Donc c'est un peu comme si je faisais du ridge à l'intérieur. Le ridge me met des poids partout. Lui, ce n'est pas discriminé. Donc là, c'est un peu un mélange de L1 à L2.
C'est comme si j'avais du L1 au niveau du groupe, et du L2 à l'intérieur du groupe. Ce qui fait qu'il va aller me chercher le groupe d'abord, et après il va mettre des coefficients sur to
utes les variables du groupe. Vous voyez qu' en changeant la pénalité , je vais changer. .. j'ai perdu mon... je ne sais pas pourquoi il va dans tous les sens là. Voilà.
En changeant la pénalité, je change la structure de la solution.
Je change le modèle linéaire qu'il va aller chercher, parce que là, il a tenu compte de l'information de groupe, mais je l'ai mise dans la pénalité, cette information de groupe.
Parce que j'ai fait des blocs de variables dans le calcul de la norme. Et j'ai fait une norme un peu exotique. Ce n'est pas une norme mathématique qui existait avant. C'est des gens qui ont bricolé.
Ils se sont dit intuitivement : « Voilà ce qu'on aimerait avoir. Voilà comment on va bidouiller la norme pour avoir ça. »
Qu'est-ce qui se passerait si on faisait du L1 à L1 au lieu de faire du L1 à L2 ? On pourrait faire du L1 au niveau du group
e, et au lieu de prendre la norme 2 dans le groupe, on pourrait prendre la norme 1. Là, on aurait aussi de la sparcité dans le groupe en plus. Donc il irait
chercher de manière sparse les groupes de variables, et dans chaque group e, il mettrait de la sparcité aussi. Donc là, il suffit de remplacer la norme 2 ici par une norme 1, et j'ai ça.
Ça, c'est un facteur qui normalise, c'est le nombre de variables dans chaque groupe. Parce que les groupes n'ont pas forcément le même nombre de variables, donc il faut quand même
normaliser pour qu'on puisse faire des comparaisons avec le même lambda. Ça revient... ou alors il faudrait dire : « On prend des lambdas différents et on laisse la validation croisée.
» Mais bon, je préfère cross-valider un paramètre que j'ai paramètres. C'est surtout ça, l'idée. Donc vous voyez comment, avec la pénalité , la pénalité
peut agir sur la structure de la solution dans un modèle linéaire. Vous voyez, on ne va pas prendre les coefficients n'importe comment.
On cherche la parcimonie, on cherche des modèles creux, mais on peut dire : « Il y a une structure . Il y a une structure derrière ça. » Un autre exemple, ça, c'est bien de la génomique.
En fait, les gens disaient : « En fait, ce qu'on aimerait, c'est... en fait, on a des expressions de gènes, et là, c'est la position dans la séquence. » Donc là, en fait, la position , c'est...
il y a une structure d'ordre. Si on prend juste des positions comme des indices dans une régression,
en fait, dans la régression, on peut changer l'ordre, normalement ça ne doit pas changer le résultat. Mais s'il y a un ordre, comment on fait ?
Parce que ces méthodes, elles sont quand même sympas. Plutôt que de faire du traitement du signal, on peut se dire : « On pourrait faire du modèle linéaire sur des séquences temporelles.
» Ça revient à ça. Mais il faut que cette contrainte de l'ordre des variables, elle soit injectée quelque part.
Si on regarde juste les moindres carrés, les moindres carrés, et la norme L1, elle ne voit pas ça. Elle ne voit pas l'ordre sur les indices.
Je change l'ordre des indices, je dois avoir la même réponse. Je n'ai pas changé le problème. Ok ? Donc il y a des gens très malins qui ont dit : « En fait,
on pourrait utiliser exactement le même algo, donc l'algo du lasso, moindres carrés plus L1, pour des données temporelles. Qu'est-ce qu'on veut préserver comme structure ? »
En fait, l'idée, c'est de se dire que quand il y a un groupe de gènes qui est actif, ils sont actifs ensemble. Tous les voisins, ils se ressemblent, ils vont s'activer en même temps.
Donc c'est cette notion de voisinage qu'on voulait préserver. Et donc ils se sont dit : « Rien n'empêche de rajouter des pénalités. » Plutôt que de triturer avec le groupe lasso, on a changé
la pénalité. Mais en fait, on pourrait aussi se dire : « Là, je veux de la sparcité, donc je veux quand même peu de coefficients, non nuls. Ça, je veux garder ça.
Donc je garde la pénalité L1, mais j'ai une contrainte en pl us. Je rajoute une contrainte, qui est le fait que je veux des blocs de coefficients qui évoluent ensemble.
Qu'est-ce que je vais pénaliser ? C'est donc les sauts dans la valeur des coefficients. C'est quoi un saut ? C'est βj - βj - 1. C'est deux coefficients successifs.
Je ne veux pas qu'ils changent de... je ne veux pas qu'ils changent de valeur comme ça, facilement.
Il faut qu'ils puissent changer de valeur, mais s'ils changent de valeur, je vais pénaliser le fait qu'ils changent à nouveau de valeur. Résultat : en rouge, vous avez l'estimation.
Donc on part à zéro . Hop, là, il y a un petit groupe qui a sauté. Après, ça fait un petit segment.
Après, hop, ça repasse quand même à zéro, ça reste sur zéro un petit moment, et hop, ça ressaute, etc. Le lambda va régir le nombre de sauts. Le mu, pardon.
Lambda, c'est la sparcité, nombre de coefficients non nuls. Et le mu, ça va régir le nombre de sauts.
Donc si je bouge le mu, peut-être que ce saut-là va disparaître, peut-être que ce saut-là va disparaître aussi, si je régularise plus, si j'augmente le mu. Après, peut-être que ça a du sens.
Là, vous voyez, il y a des petits groupes d'observation qui sont quand même loin des axes. Mais là, c'est vraiment l'estimation du support qui m'intéresse plus que l'estimation des coefficients.
C'est savoir vraiment quels groupes de gènes évoluent ensemble. Ok ? Mais ça donne une lectu re, une interprétation des données. C'est pour ça que c'était intéressant.
Ça, ça s'appelle le fuse lasso. C'est un mélange de L1 et de L1 sur des incréments des coefficients. Des incréments des coefficients successifs. Vous voyez qu'avec les modèles, on peut
jouer avec des algos différents sur des structures où il y a plus de ... enfin, pardon, sur des données où il y a plus de structures, en modifiant un tout petit peu la formulation du problème.
Après, il y a toujours la question de comment on résout numériquement, est-ce qu'on sait optimiser, etc. Mais aujourd'hui, il y a quand même des panoplies pour faire de l'optimisation
qui sont assez sophistiquées. Il y a pas mal de librairies aujourd'hui pour faire ça. Et on peut se dire que ce n'est pas forcément le problème de l'ingénieur ou du modélisateur.
Après, il faut aller voir un expert en optimisation, un expert en résolution de méthodes numériques, pour faire le job. Après, ça peut être votre travail aussi,
si vous voulez vous spécialiser là-dedans. Mais voilà. Mais en tout cas, je veux souligner les deux aspects.
C'est-à-dire que la première question, c'est de dire : « Mais qu'est-ce qu'on cherche ? Quels sont les éléments dont la physique nous dit que ça doit être dans les solutions ? »
Et ensuite, il y a une autre question qui est techniquement : comment on résout et qu'on trouve cette solution en résolvant un problème d'optimisation.
Il y a deux trucs différents, c'est pareil les sujets. Alors, il y a pas mal aussi. .. ça me fait penser
à tout un domaine de recherche qui s'appelle les PNINs, les Physically Informed Neural Networks. C'est les réseaux de neurones physiquement informés.
Et ça, ça s'est développé pas mal les dernières années dans des domaines, justement, où il y a pas mal de physique.
Parce qu'en fait, on s'aperçoit que les réseaux de neurones, ils n'ont aucune raison de respecter les lois de la physique. Il s vont suivre des données, se caler sur des données,
mais parfois ça peut tourner le dos aux lois de la physique. Donc quelque part, il y a ces initiatives pour essayer de réconcilier un peu les deux types de connaissances : la connaissance basée sur
des mécanismes des lois, des lois scientifiques, et après ce que disent les données. Alors, les lois scientifiques ne sont pas parfaites. Elles font des simplifications, elles font des hypothèses.
Et des fois, dans les données, on s'écarte des lois de la physique parce que les lois de la physique ne sont pas parfaites. Mais il y a aussi le cas où les données, elles sont bruitées,
et donc elles vont aller mettre de l'information là où il y a que du bruit, en fait. Et donc elles s'écartent beaucoup de la physique. Alors, les PNINs, c'est très controversé. Il y
a plein de gens qui disent que ça ne marche pas, et que c'est joli comme ça sur le papier, mais qu'en vérité, on n'arrive pas à les faire marcher.
Après, il y a des gens qui réussissent à les faire marcher, mais ils travaillent un peu plus que ceux qui essaient de les utiliser sur étagère. Donc ça aussi, ça a un message : c'est qu'il
n'y a pas de modèle parfait, il n'y a pas d'algorithme parfait, et que dès qu'on va aller sur des usages
où il y a des enjeux, où justement tout ce qu'on sait faire ne marche pas très bien, il faut quand même se plonger dans la technique,
dans la partie scientifique aussi, éventuellement dans la physique, pour faire des choses qui finissent par être performantes.
Et j'ai envie de dire que, pour la faire courte, la solution, c'est toujours de résoudre le compromis biais. Quelque part, si on arrive à
mettre suffisamment de données dans de la physique et suffisamment de physique dans les données, c'est qu'on arrive à bien régulariser le problème.
Alors, je vais dire quelques mots de la régression ridge. Donc là, c'est comme si on revenait un peu dans le temps. Mais c'est pour faire une petite généralisation pour aller vers
des approches non linéaires, justement. Alors, je passe sur ça, c'est des choses que j'ai déjà recommandées. Donc l'estimateur ridge, c'est celui avec la pénalité L2 au lieu de...
donc L2 au carré. Donc c'est norme 2 au carré. Donc c'est la somme des βi carrés, finalement. Parce que la norme 2, elle est définie avec une racine carrée.
Donc on élève au carré pour avoir que la somme des carrés. Et c'est l'approche la plus classique, parce qu'il y avait ce lien avec la stratégie numérique pour répondre à l'instabilité
du calcul de l'inverse dans la résolution des moindres carrés classiques. Donc ça, on l'a déjà vu. Alors voilà. Donc il y a... dans la résolution de ridge,
je vous ai dit, ça revient juste à rajouter un lambda sur la diagonale du x transposé x, avant de calculer l'inverse. Alors, il y a une remarque très importante ici.
C'est que maintenant, si on veut utiliser ce truc-là en prédiction , si on veut prédire sur un nouveau x, il suffit de multiplier à droite par un petit x. La
matrice x, c'est la matrice des données. Donc c'est tous les xi transposés qu'on a mis une ligne après l'autre. Ce qu'il y a de remarquable ici, c'est que pour les évaluations de la fonction,
mais c'est vrai en réalité ... je ne sais pas si je vous détaille ça, parce que c'est quand même. .. là, on rentre dans les multiplicateurs de Lagrange.
Je veux vous dire juste le message, en fait. Le message, il est là. C'est qu'à la fois la formulation du problème d'optim isation et l'évaluation de la fonction point par point ne fait intervenir
les données qu'à travers des produits scalaires. Donc les xi, qui sont les vecteurs d'entrée dans votre base d'apprentissage, n'interviennent qu' à travers de xi transposé xj.
C'est des produits scalaires 2 à 2 des données. Conséquence de ça, et ça, c'est quelqu'un qu i. .. alors je vais faire plutôt à l'envers. Voilà. Conséquence de ça,
on peut remplacer la notion de produit scalaire par un opérateur de deux variables, xi, xj. Donc on remplace xi transposé xj par une fonction k, ce qu'on appelle un opérateur à noyau, de xi et xj.
Alors après, quand on va calculer la réponse, xi, xj, les produits scalaires 2 à 2, ça, ça intervient dans la formulation du problème d'optimisation, qui nous permet de calculer les αi.
Et on avait des solutions qui étaient αi x i transposé x .
Maintenant, si le problème d'optimisation ne repose que sur les produits scalaires, qu'on remplace par des k de xi, xj, la solution, ça devient somme des αi k de x, xi.
Donc on remplace le produit scalaire par cette évaluation à travers l'opérateur k. Et donc là, on a maintenant des solutions qui ne sont plus linéaires en x.
Ça reste linéaire par rapport à α, mais ce n'est plus linéaire par rapport à x. Et en réalité, ce qui est assez incroyable, c'est qu' on résout exactement le même problème d'optimisation
qui se trouve ici. Voilà. Ça, c'est la formulation du problème d'optimisation en α. Et là, vous avez la norme.
Alors, c'est la norme au carré de x transposé α, mais quand on écrit la norme, rappelez-vous, il faut... la norme, c'est le vecteur transposé fois le vecteur lui-même.
Et donc quand on va calculer la transposée de ça, on va avoir α transposé x, x transposé α, enfin α transposé x, x transposé α. Et donc
on va voir x transposé x, qui est une matrice qui est formée des produits scalaires 2 à 2 de xi, xj. Et là, c'est pareil, on n'a que les produits scalaires.
Donc on peut remplacer tous ces produits scalaires par les évaluations de k de xi, xj. Donc c'est exactement le même calcul de α, il suffit de changer la matrice des données. La matrice des
x transposé x est remplacée par la matrice des k de xi, xj. Donc numériquement, on a exactement le même problème, et on a gratuitement, du coup, des modèles non linéaires. Donc ça, c'est...
voilà, si on reste sur ridge, on a cette propriété-là qui est assez incroyable. Et ça, c'est la...
si vous voulez, c'est le développement des support vector machine, qui est un des algorithmes d'apprentissage qui a été très populaire dans les années 2000, enfin 90-2000 ,
et qui est encore pas mal utilisé aujourd'hui. Ça, vous aurez l'occasion de le manipuler. Une autre généralisation que je voulais donner autour de ridge, c'est ce qu'on appelle Elastic Net.
Alors, la motivation pour ça, Elastic Net, c'est juste une idée toute bête qui est de dire : « On fait un mix entre L2 et L1.
» On rajoute juste une deuxième pénalité, on avait le lasso, et on rajoute une pénalité ridge au lasso. Alors, vous allez me dire : « Pourquoi on fait ça ?
» Parce que justement, on avait fait du lasso pour ne pas faire du ridge. Donc pourquoi faire les deux, en fait ? Et il y a une motivation ici qui est donnée dans un article de 2005 .
Donc c'est vraiment les. .. beaucoup des statisticiens de Stanford qui avaient développé ces techniques-là dans cette période. Et donc ça fait plein de papiers autour.
Et toutes les variantes, il y a pas mal de variantes qui viennent de là-bas. En fait, ce qu'ils ont dit, c'est qu'il y a un enjeu de régularisation des résultats du lasso.
Alors ça, on peut le voir peut-être si on revient sur le. .. en fait, on le voit directement ici.
Et si vous vous rappelez, là, quand j'avais montré les chemins de régularisation, donc rappelez-vous, c'est les valeurs des coefficients en fonction du lambda qui est décroissant ici. Si
on zoome un peu sur ces chemins de régularisation avec le lasso, donc là, c'est juste L1. Qu'est-ce qui se passe ? On a deux effets qui ne sont pas souhaités dans la manière de
calibrer un modèle de régression linéaire. Donc là, on a un problèm e, ça vient de... c'est une application en santé, si je me rappelle bien, où les variables sont des variables...
bon, il y a l'âge, mais après c'est des variables qui sont liées à des mesures, il y a le poids, il y a des mesures biologiques. Il y a un truc qui n'est pas très naturel dans cette courbe.
Est-ce que vous voyez des choses qui vous paraissent un peu gênantes ? Il y a deux choses un peu gênantes, en fait, dans le diagramme de gauche.
Enfin, comme vous savez que le diagramme de droite, ça va être la réponse, je pense que vous pouvez deviner quels sont les deux problèmes. Il y a des coefficients négatifs.
Ah, il y a des coefficients négatifs, tout à fait. Et c'est un peu bizarre quand on essaie d'expliquer un phénomène, de se dire qu'il y a des variables qui contribuent négativement.
À la limite, elles peuvent faiblement contribuer. On peut se dire : « L'âge contribue faiblement, mais pourquoi il serait négatif ? » Ça paraît un peu bizarre.
Donc il y a des effets de corrélation statistique comme ça, si on ne met pas de contraintes, qui sont un peu contre nature. Ça, c'est un premier élément. Le deuxième élément
, si vous vous rappelez, je vous ai dit : « Si on veut un modèle plus petit, il suffit de regarder quelles sont les premières variables qui apparaissent, et puis
on garde, par exemple, là, si je prends le modèle avec 4 variables, je vais retenir la première, c'est bio, LkVolt, je vais retenir la deuxième qui est Lweight , SVI, et Lbph. S auf qu'il
y a une variable qui apparaît après et qui finit plus haut que Lbph. Et puis oui, et puis même âge, ICP, là, en valeur absolue, c'est peut-être supérieur à celle-là.
Donc il y a des variables qui se croisent. Et ça, c'est pareil, ce n'est pas intuitif. Quelque part, on se dit : « Il y a un petit problème dans le chemin du lasso. » Donc le fait de mettre...
alors ça, je ne saurais pas trop vous l'expliquer pourquoi, mais le fait de rajouter une L2, ça permet quand même de garder de la sparcité, puisqu'
on voit qu'il y a des coefficients qui s'allument les uns après les autres. Il n'y a pas spontanément des coefficients partout, ce qui est le cas avec ridge.
Il y a de la positivité, et ils ne se croisent pas. Donc quand on regarde les chemins de régularisation,
ça nous montre qu'on a une estimation qui se passe bien, quel que soit le lambda et le mu, quoi. Quel que soit les. .. alors il faut voir ce que ça veut dire, lambda et mu, d'ailleurs,
dans ce cas précis. Mais voilà, vous voyez comment on peut essayer de corriger aussi avec les pénalités des effets qui ne sont pas souhaités dans
la manière dont les solutions sont estimées par notre stratégie. Voilà. Donc... je vois que vous avez les modèles non linéaires. Alors oui, juste pour revenir sur
le cas des modèles non linéaires, on peut se poser la question de : c'est quoi le noyau k ? En fait, il y en a certains qui sont utilisés communément, c'est les noyaux polynomiaux.
Alors il y a plusieurs formules possibles. En gros, c'est le produit scalaire à la puissance d.
Et puis vous en avez d'autres, c'est des noyaux, ce qu'on appelle fonction à base radiale, mais qui correspondent un peu à des gaussiennes. Il y a un effet un peu chapeau mexicain.
Donc c'est exponentiel de moins la norme de x moins z au carré divisé par 2 sigma carré. Donc là, dans ces techniques, vous avez des nouveaux hyperparamètres, quand on va sur
du non linéaire, qui sont le choix du k. C'est quoi la fonction ? C'est un hyperparamètre, c'est une fonction, mais c'est le modélisateur qui doit choisir.
Et chaque fonction a elle-même un hyperparamètre. Si c'est un polynôme, il y a le degré du polynôme qu'il faut choisir. Si vous prenez le noyau gaussien, il faut choisir le sigma carré.
Donc vous avez des hyperparamètres qui viennent se rajouter au lambda. Donc il y a à nouveau de la validation croisée pour ces hyperparamètres.
Mais dites-vous que si j'ai deux hyperparamètres, il faut que je prenne une grille très fine et que j'aille évaluer, que je fasse des apprentissages pour tous les points de cette grille,
pour trouver le meilleur point. Voilà. Mais en tout cas, on arrive à avoir ici du non linéaire relativement gratuitement .
Alors sauf que quand on est en grande dimension, ridge, ce n'est pas adapté. Si vous voulez, c'est là où ça a un peu bloqué le développement des SVM,
dans les années 2000 et quelques, alors que ça avait commencé à être transféré pour des applications, notamment en biotech. Et en fait, ça a coincé sur les dimensions.
C'est-à-dire qu'on n'arrivait pas vraiment à traiter des problèmes de très grande échelle. C'est pour ça que sur Internet, on n'a pas du tout fait de SVM. Donc ça reste quand même utilisé,
notamment parce que. .. ce qui est pas mal aussi pour k. Donc k, ça vous donne des mesures de similarité. On peut montrer le lien qu'il y a entre k et
une espèce de distance, une notion de distance entre deux points . Là, vous avez l'équation, pour montrer comment ça passe de l'un à l'autre. Mais là où ça a été pas mal
utilisé, j'ai parlé des biotech, c'est qu'on peut fabriquer des noyaux pour des données structurées. Et donc il y a eu toute une littérature qu'on appelle un peu. ..
enfin, je ne sais pas si c'était un terme consacré ou si c'est moi qui l'avais posé comme ça, mais un peu de kernel engineering.
C'est-à-dire que c'est l'ingénierie de kernel, on se fabrique son kernel. De la même manière qu'on se fabrique sa pénalité, comme je vous l'ai montré là. Avant la venue du deep learning,
la recherche en machine learning, c'était beaucoup ça. C'était soit de l'ingénierie de normes, soit de l'ingénierie de noyaux, de métriques, en fait. Ça revient un peu au même, d'ailleurs.
Ce n'est pas tout à fait le même. .. sur le même plan, mais... Et donc, par exemple, on peut se dire : « Voilà, si j'ai deux séquences de caractères, mais ça pourrait être du texte,
comment je compare deux séquences entre elles ? » Et ça, c'est un peu l'ancêtre des embeddings qu'il y a aujourd'hui dans les réseaux de neurones profonds.
De se dire : « Il y a des petits éléments, je voudrais savoir si ces petits éléments, ces petits motifs, on les retrouve entre deux séquences. »
Et si je prends plein de petits motifs comme ça, je peux dire que deux séquences se ressemblent si elles ont beaucoup de motifs en commun.
Ça me permet de mettre de la structure, parce qu'il y a la séquentialité dans l'occurrence des caractères, des symboles dans la chaîne de caractères.
C'est pareil avec du texte, c'est exactement pareil. Bon, ça pourrait être des tokens, si vous voulez, pour parler du jargon IA moderne.
Donc vous voyez qu'il y a plein d'idées qui étaient déjà là à l'époque et qui se sont développées à ce moment-là. Voilà, donc ça, c'est aussi
des morceaux de littérature qui peuvent vous intéresser si vous vous intéressez à des données symboliques, par exemple. Voilà. Donc
écoutez, je pense que je vais m'arrêter là, parce qu'on est déjà ... on a dépassé un peu le temps. Donc ce qu'il me restera à voir avant d'aller sur d'autres problèmes de ...
d'autres modèles linéaires, pour d'autres problèmes que la régression, c'est de voir un peu les généralisations qu'on peut dériver à partir de ce qu'on a vu là.
Vous voyez, on parlait d'un modèle de régression, un modèle linéaire, et puis dès qu'on a un formalisme, on le fait glisser pour couvrir d'autres problématiques.
Et ça, c'est une gymnastique que j'aimerais bien que vous soyez un peu. .. voilà, que vous la compreniez, cette gymnastique, et que vous puissiez éventuellement la développer vous-même.
Vous voyez comme quoi ce n'est pas nécessaire d'être super expert en régression linéaire pour pouvoir appliquer des techniques dans d'autres domaines.
Les gens qui ont fait ça, ce n'est pas des gens forcément hyper pointus sur chacun des modèles. Il faut comprendre un peu comment les idées elles naviguent d'un sujet à l'autre.