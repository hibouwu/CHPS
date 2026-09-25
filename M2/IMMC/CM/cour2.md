Typiquement , un mousse, ça, comme ça, ou un fluide. Quand vous générez un écoulement, le milieu se déforme, ok, et on va caractériser ça avec des outils différents pour les fluides
et les solides, ok. Alors, je n'ai pas fait la pomme, hein, je m'en plains pas plus tard. Donc, on va s'intéresser à la caractérisation, à la mesure , à la modélisation
mathématique des déformations au sein des milieux continus. Alors, bon, c'est écrit comme ça, mais bon, en gros, il faut le voir : vision Lagrangienne, la notion de déformation, ok, et la vision
— pardon, la vision Lagrangienne— et la vision eulérienne, le taux de déformation. Donc c'est une déformation dérivée par rapport au temps, au taux de déformation, ok.
Donc on va voir les deux aspects, et puis chacun des deux aspects, ça va se séparer en différentes parties. Je n'ai pas réussi à faire— à faire passer tous les slides, je ne sais pas si
on ira jusqu'au bout, je ne sais pas. Donc on va commencer par la notion de déformation en Lagrangien, avec, première notion à introduire : le gradient de la transformation. Donc si je vous dis
« transformation », vous devez, euh, a priori penser. Alors, peut-être pas encore de manière très automatique, je ne vais pas par là, mais, euh, typiquement , ce n'était peut-être pas
logique pour vous, mais ces trois équations scalaires, là, tout le monde voit,
ces trois équations scalaires, là, elles vous définissent les équations de trajectoire, mais ça vous définit aussi la fonction phi, la fonction de transformation, ok.
Donc, en gros, pour caractériser— enfin, pour faire une première étape vers la caractérisation des déformations, il va falloir qu'on calcule justement le gradient de cette fonction.
En calculant le gradient de cette fonction, on va— on va avoir une première étape vers quelque chose qui n'est pas une variation des positions, mais plus une variation des distances
et des angles entre les biparticules. Donc vous prenez une biparticule, c'est deux particules. Donc si vous les regardez, ben, elles peuvent se déplacer les deux dans l'espace, mais a priori,
elles peuvent se déplacer les deux dans l'espace si la distance entre les deux reste constante. Vous ne pouvez pas montrer qu'il y a une déformation, ok.
Potentiellement, ça veut dire qu'il n'y a pas de déformation. Autre vision des choses : vous pouvez considérer triparticules, trois particules,
ok, elles se déplacent dans l'espace, potentiellement avec un mouvement de corps rigide, mais sans changer de— alors, si vous — bon, il y a une variation de distance entre deux— entre deux
des— des tri— des trois particules qui font le— les trois particules, mais vous pouvez avoir une variation de l'angle qui est formé par ces trois particules.
Typiquement, une variation de l'angle, c'est une distorsion de— une distorsion de l'image, par exemple. Ça, vous voyez bien. Vous prenez une image qui est bien cartésienne, là, et puis
vous la— vous l'écrasez comme ça, là, ça vous fait plutôt un losange. Ben voilà, vous avez distordu l'image, ok. Et c'est une— en fait, c'est une déformation de glissement. Bon, bref.
Il va falloir qu'on dérive cette fonction par rapport à l'espace pour avoir un premier pas vers une information qui se rapproche d'une déformation, mais ce n'est pas encore une déformation.
Ensuite, je vais vous proposer une mesure de la déformation, parce qu'en fait, il y a plein de manières de mesurer ça. On précisera un peu le cadre de l'hypothèse des petites perturbations, qui
constituera notre — notre pré-carré dans lequel on arrivera à faire des choses de manière analytique.
Si on sort de l'hypothèse des petites perturbations de manière analytique, les calculs, ça devient — c'est tout de suite le bazar. C'est beaucoup plus complexe, alors que
si on reste dans le cadre des petites perturbations, on reste sur des équations très linéaires, c'est bien, on sait faire, ça marche bien.
Et on verra quelques petits aspects pratiques sur les déformations, histoire de vous donner quelques— quelques repères, ok.
Donc voilà pour le menu de cette première partie, donc la partie plutôt vision Lagrangienne des déformations, ok. Alors, première façon de caractériser les déformations d'un milieu continu. On
est en description Lagrangienne, et donc l'objectif de cette première section, là, ça va être de se donner les outils qui permettent de— de caractériser cette déformation,
et voire de la mesurer. Par « caractériser », on pourrait donner une approche très qualitative des choses : c'est— ça se déforme plutôt de— sous tel mode, c'est une dilatation,
c'est une distorsion, etc. Mais il y a un moment où il faut être capable de quantifier les choses, donc il faut arriver à une mesure avec une échelle, si vous voulez, ok. Donc, dans le—
dans le meilleur des cas, on va essayer de mesurer cette déformation. Et donc ça, c'est valable pour un milieu continu au cours de son mouvement. Donc, caractériser la déformation.
J'ai commencé à vous dire, hein : les biparticules, si on regarde l'évolution de la distance entre deux particules, ben, on va avoir une variation des distances. C'est typiquement une déformation
suivant une direction. On peut avoir une variation des angles si on considère un triplet de particules, ok. Alors, là, moi, je vais—
je vais me cantonner à un tout petit aspect de la mécanique des milieux continus. On peut aller beaucoup plus loin avec des représentations
des— des choses de plus en plus complexes, qui n'ont pas forcément un intérêt, parce qu'avec la représen— enfin, avec les outils que je vais vous donner dans ce cours,
on va rester dans un cadre des équations très linéaires. On arrive à traiter plus de 95 % des situ ations de manière assez fidèle. Ça marche bien, c'est— c'est efficace,
c'est manipulable par un ingénieur, et pas que par des chercheurs, donc c'est très bien. Mais il y a certains matériaux, certaines situ ations, où on est obligé de passer sur
des— des modèles beaucoup plus avancés. Bon, nous, on va rester dans le cadre où c'est abordable, où c'est simple. L'idée, c'est que vous ayez les— les principes de base, ok.
Et puis, si ça vous intéresse, ben, vous prendrez un polygone, vous irez suivre des cours de— à l'école doctorale, ou quoi, ou enfin, ou vous ferez un autre M2 après, enfin, je n'en sais rien.
Mais vous avez plein de ressources sur le— sur le web pour vous auto-former, si ça vous intéresse d'aller vers des problèmes plus — plus complexes. Donc là, je vais vous donner des outils
basiques, mais qui fonctionnent très, très bien pour la majeure partie des situ ations. Alors, la notion de déformation. On repart de ce principe-là, enfin, de cette application-là, qui traduit
les coordonnées actualisées des particules via une applic ation vectorielle qui, à partir du temps et des coordonnées initiales, nous donne des coordonnées réactualisées, ok. Donc,
en réalité, on pourrait réécrire, sous forme différentielle, cette équation-là, là. Le vecteur OM, donc la position actualisée, c'est la transformée de la position initiale.
On fait une différence , tout simplement, une différentielle. Donc d de OM, ben, c'est du coup égal au gradient de phi fois le vecteur d OM0. Je ne sais pas pourquoi ça —
ce n'est pas joli, c'est d là, droit. Voilà. Alors, ça veut dire que, en gros, je vais définir— je vais définir un nouvel outil, enfin, un nouvel outil — un nouvel outil et une notation.
Et là, je vais commencer à raisonner non plus avec que des vecteurs. Alors, bon, je vais commencer à introduire quelques matrices, des tenseurs, et tout, mais
là, c'est— ça va être le premier tenseur que je vais introduire. Je vais dire que je vais noter le tenseur du second ordre, grand F, donc double barre pour
noter que c'est un tenseur du second ordre, comme étant égal au gradient de ma fonction de transformation. Alors, en réalité, hein,
c'est une fonction qui est vectorielle, elle a— elle a trois composantes, vous êtes d'accord avec ça, ok. Si j'applique le gradient sur une fonction scalaire, par exemple la température,
c'est censé me donner le vecteur qui donne la direction de la plus grosse variation de température, ok. Ça me donne un vecteur. Si j'applique le gradient sur une quantité qui est vectorielle,
du coup, je monte d'un ordre, je passe au tenseur du second ordre, ok. Si j'applique un gradient sur un tenseur du second ordre, ça me donne un tenseur du troisième ordre, et ainsi de suite, ok.
C'est bon pour ça ? Donc, éventuellement, je peux rajouter deux barres pour préciser que ça va me donner une quantité qui va être tenseur du second ordre, ok.
C'est une manière de— de représenter les choses. Et donc, alors, c'est bien beau de dire « c'est le gradient de phi », mais bon, peut-être que vous n'êtes pas encore bien — bien habitués
à ce type d'opérateur. En réalité, ça veut dire que c'est la dérivée partielle de phi de — on va le faire comme ça— de OM 0 , et on dérive par rapport au vecteur OM0. Alors, pourquoi
quand on fait le gradient, c'est qu'on dérive par rapport à l'espace, ok. Mais là, on est en description Lagrangienne, donc on va dériver par rapport à notre— à nos
variables qui permettent de définir le— enfin, de paramétrer l'espace. Et quand on est en description Lagrangienne, c'est la position initiale, donc M0, ok.
On aurait à calculer un gradient alors qu'on est en description eulérienne, on aurait dérivé par rapport aux coordonnées actuelles, les coordonnées eulériennes, ok.
Donc c'est un petit peu implicite quand on applique un gradient, le— les coordonnées par rapport auxquelles on va— on va dériver, ok. Donc, voilà.
Donc, en réalité, hein, on est— on est passé par une différentielle. Don c de d de OM, ça fait apparaître le gradient de la transformation, et donc on choisit de le noter F. Et donc, on va le
nommer, on va dire que ce tenseur F , c'est l'opérateur gradient de transformation. Voilà, la définition est dans son nom, ok. On peut appliquer le gradient sur la fonction de transformation, ok.
Ne retenez pas juste F, retenez « opérateur gradient de transformation ». Opérateur ou tenseur, c'est pareil. Voilà. Un tenseur, hein, généralement, c'est un opérateur.
Alors, retenez qu'il est sans unité, ben, oui, parce que cette quantité-là , c'est une position . C'est quelle unité ? Une longueur. Une longueur, donc typiquement des mètres,
hein, dans le système international. Et vous dérivez par rapport à des mètres, vous tombez sur une grandeur qui est à dimensionner, ok.
Donc typiquement, ça va être des pourcents, en fait, globalement, sans unité. Ok. Alors, en l'absence de déformation, ben, du coup, ce tenseur, il revient à l'identité. Ça veut dire que
vous, si vous regardez l'évolution par rapport à l'espace de la transform ation, elle se comporte — alors, oui, pardon, si c'est— c'est l'identité en l'absence de déformation,
et sans rotation de type corps rigide. Donc potentiellement , vous prenez — vous essayez de retrouver les équations de trajectoire que vous pourriez avoir pour cette— pour ce mouvement-là,
ok, le mouvement de corps rigide avec seulement une translation. Alors, vous avez juste rajouté un terme, typiquement, qui pourrait dépendre du temps, à la position suivant la direction 1, ok.
Si vous calculez le gradient, ben, il ne reste plus que la— la position initiale. Vous avez rajouté au grand X1 quelque chose qui dépend du temps, ok. Du coup, vous êtes retombé sur l'identité.
Si jamais vous mettez une rotation, ben, vous l'avez vu, hein, vous recouplez un petit peu les— les différentes composantes. Donc ça — ça peut rester en présence de mouvement de corps rigide,
ça peut rester une isométrie vectorielle directe, une matr— une matrice de rotation, typiquement, ok. Donc si vous avez un mouvement qui intègre à la fois potentiellement
une— une translation de corps rigide, mais en plus de ça une translation, cet opérateur-là va devenir une matrice de rotation, ok. Alors, en l'absence de rotation, votre— ce tenseur-là sera
symétrique, parce qu'il n'y aura pas de composition avec une rotation qui est — qui a plutôt tendance à être — à avoir un aspect pas antisymétrique, mais pas long, ok.
Donc ça, c'est quelques petites observations qui vous permettront , à partir de la forme de F, une fois que vous l'aurez calculée, parce que c'est un calcul assez fréquent,
ben, vous arriverez à tout de suite repérer : « Ah oui, a priori, là, il y a une rotation ». Donc il n'y en a pas, typiquement. Alors, une fois que vous avez caractérisé
donc le gradient de la transformation, ben, on pourrait justement se baser sur cette inform ation pour essayer de relier ça à la comparaison des longueurs— des longueurs, mais pas des longueurs
toutes bêtes, hein, on va prendre les longueurs au carré. On prend la longueur au carré initiale et la longueur au carré actuelle entre deux particules, par exemple. Donc
une particule M, une particule — enfin, M0 et N0, qu'on va voir évoluer au fur— au fur et à mesure du temps dans le mouvement, ok. Alors, calculer la longueur au carré de deux vecteurs qui
vont gérer l'expression, enfin, ce n'est pas si compliqué que ça, hein. Mais là, on va— on va d'abord le faire en cons idérant que ces deux particules, elles sont extrêmement proches, ok.
Donc on va — on va raisonner au voisinage de— du point initialement en M0, ok. Donc ces deux particules qui sont infiniment proches. Alors, on a, par exemple,
en termes de calcul préliminaire, on a la position du point M, qui peut être recalculée à partir de N0 qu'on fait passer dans la fonction de transformation. Et pareil, N, ben, c'est le point N0
qu'on a fait passer dans la fonction de transformation. Donc au voisinage autour de N0 , on peut écrire que on a N qui est égal à la transformée, donc de N0, très bien.
Et donc c'est comme si on avait U_N qui est égal à la transformée de M0 qui est très proch e, ok, et on rajoute une contribution qui revient au gradient de la transform ation,
notre fameux opérateur gradient de transformation, notre tenseur F, fois le vecteur M0 vers N0. Donc, en gros, c'est une approche au premier gradient. On pourrait rajouter
des termes qui font appel au second gradient, au deuxième gradient, etc. C'est comme un développement limité, si vous voulez, ok, si ça vous parle aussi. Bon, on va faire une approche simple.
On va négliger les— les termes qui sont au-delà du premier gradient. Et donc, ça veut dire qu'on peut écrire que le vecteur qui va de l'origine à la—
à la particule N à sa position actuelle, c'est égal au vecteur qui va jusqu'à la position M, plus le tenseur gradient de transformation exprimé pour le point M0, pour la particule N,
fois le vecteur M0 vers N0. Si on passe par la relation de Shal, pour aller de M jusqu'à N, donc de la position de la particule M réactualisée à la particule N dans sa position réactualisée,
ben, on peut passer par l'origine, et on est capable d'écrire OM, on est capable d'écrire OM, on est capable d'écrire MO et plus ON, ok. Donc MO plus ON, ben, si ON
, ça contient OM, ben, ça, ça va s'annuler. Il ne reste plus que la contribution de— liée au tenseur de gradient de transformation appliquée sur M0 vers N0.
Ce qu'on peut retenir, du coup, c'est qu'on a , pour N et M qui sont infiniment proches, on a pu montrer qu'on a cette expression. Donc si on connaît
ce vecteur-là initialement, on connaît les positions initiales des deux particules, en considérant qu'elles sont infiniment proches, et qu'on a l'expression de
ce tenseur gradient de transformation, parce qu'on connaît la transformation, on est capable d'obtenir la réactualisation du vecteur qui va d'une particule vers l'autre, ok. Très bien.
Bon, alors, vous allez me dire : « Je n'ai pas encore vu le lien avec les longueurs initiales, les longueurs au carré pour la configuration initiale actuelle. »
Ben, il suffit que j'élève ça au carré, je vais avoir la longueur au carré, ça va me donner la norme au carré, ok. Si je fais le produit scalaire de ça avec ça, ok, et puis, ben,
je vais pouvoir le mettre en regard du produit — enfin, de la longueur au carré de ce vecteur-là, en réalité, assez facilement. C'est ce que je vais faire.
Donc les longueurs au carré initiales et actuelles, pour ce vecteur-là, ce vecteur-là, je peux les écrire. C'est la transposée du vecteur M_N fois lui-même, ok.
Et pour M0 vers N0, ben, c'est la transposée de M0 vers N0 fois M0 vers N0. Du coup, je remplace mon vecteur M_N par cette expression-là .
Je vais faire apparaître, du coup, le tenseur gradient de la transformation. Et du coup, j'ai réussi à réexprimer cette longueur au carré en fonction . Ah, j'ai oublié de sourire.
Pourquoi je ne suis pas parti de ma place ? Merci. On ne va pas faire trop de gentils. Donc ce vecteur-là, donc c'est F fois M0 vers N0, pardon, je commence à me fatiguer, transposée fois
F fois M0 vers N0. Quand j'applique la transposée sur un produit de deux— de plusieurs tenseurs ou de tenseurs-vecteurs, je change l'ordre. Donc si je développe,
ça me donne la transposée de M0 vers N0 fois F transposée fois F fois M0 vers N0, d'accord. Donc j'ai juste développé l'opérateur transposée. Pour ça, j'ai dû changer l'ordre des—
des différents termes. Bon, ben, du coup, là, j'ai M0 vers N0 transposée fois F transposée F , et M0 vers N0. Et si j'avais fait exactement la même chose avec M0 vers N0 au carré,
ben, en fait, j'aurais pu intercaler l'opérateur identité entre les deux, ça— ça ne change rien. Résultat : si je veux calculer l'écart entre
cette longueur au carré, qui est la longueur actuelle , la longueur au carré entre la position actuelle des deux particules et la position initiale, ben, je calcule ça,
et je vois qu'en factorisant, je fais apparaître F transposée F moins l'identité. Du coup, cette quantité-là , elle me permet de traduire l'évolution, la variation des longueurs au carré
entre mes deux particules, ok, entre la configuration actuelle et la configuration initiale. Donc je vais me baser là-dessus, en fait. Alors, je vais d'abord caractériser ceci,
puis ensuite je verrai comment je peux utiliser ça. Alors, cette partie-là, je vais la— je vais la noter comme étant l'opérateur des dilatations de Cauchy-Green droit.
À 4 heures de l'après-midi, après près de 5 heures de cours, c'est difficile à retenir, mais bon, retenez que c'est un opérateur qui caractérise des dilatations, ok. Donc
c'est un opérateur qui est symétrique, c'est un tenseur symétrique, et les composantes C et J. Alors, c'est-à-dire que vous avez votre tenseur C, là, avec les composantes C11 , C22
et C33, qui sont sur la diagonale. Elles représentent, à chaque fois, les dilatations au carré selon l'orientation 1, 2 ou 3. Et une dilatation, typiquement , si j'étais capable
, avec cette mousse, de faire une extension pour que je double la longueur de cette grille en mousse, là, que vaudrait la dilatation suivant cette direction ? Si j'arrivais à doub— mais
mettons que je le fais avec un outil de transformation des images, je double la longueur comme si j'avais tiré très fort dessus, dans cette direction, quelle serait la valeur de la dilatation
dans cette direction ? Est-ce que c'est 100 % ? Donc 1. Est-ce que c'est 2 ? C'est 1 ou c'est 2 ? C'est 2. C'est le rapport de la longueur initiale sur la longueur— de la longueur
actuelle sur la longueur initiale, ok. Donc ce qui veut dire qu'on garde l'identité, on garde les 100 % de la configuration initiale. On a rajouté 100 % à la longueur, ok.
Donc le— si vous raisonnez en termes de prix, en général, ça nous parle toujours beaucoup plus comparé à un scalaire. Le prix, le prix initial, c'est 100 % du prix, vous êtes d'accord.
Si le prix se dilate de 100 % — pas de 100 %. Si vous rajoutez 100 % au prix initial, ben, il s'est dilaté de— la dilatation vaut 2 ou 200 %. Par contre, vous avez ajouté 100 %, et les 100 %,
c'est la déformation, c 'est l'augmentation, ok. Donc c'est toujours positif ? Non. Ben, les prix, des fois, on est content, c'est nég— il y a une réduction du prix.
On peut avoir une diminution du prix, une réduction de 20 %, des fois ça arrive. Mais pour la déformation, on peut très bien contracter la matière, c'est possible. Alors, la dilatation sera
inférieure à 1. Par contre, la déformation, on va enlever l'identité, on va enlever 1, ok. Et vous allez voir, là, on caractérise une dilatation. Donc, en gros, on garde l'identité
, on garde les 100 % initiaux de la configuration initiale. Donc les composantes, là, ça nous donne les dilatations dans les différentes directions de l'espace.
Les composantes hors plan, bon, enfin, hors diagonale, pardon, on peut relier ça aux variations d'angle entre les fibres qui étaient initialement alignées avec
les directions des vecteurs de la base, ok. Bon, ça, c'est pas forcément à retenir. Ça, par contre, ça va être un peu plus simple. Si jamais ce tenseur de dilatation, il vaut l'identité,
ben, ça veut dire qu'il n'y a pas de déformation, ok. Votre milieu continu, il suit un mouvement de corps rigide. Vu que les dilatations dans les différentes directions de l'espace
sont bien égales à 1, donc il n'y a pas de variation de longueur pour les fibres qui sont alignées avec la base.
Et vu que c'est l'identité, il n'y a pas de variation d'angle, donc il n'y a pas de déformation, ok. Si ce — si F transposée fois F vaut l'identité,
ben, vous n'êtes pas loin d'avoir quelque chose qui est soit juste une matrice de rotation pour F, ok, soit c'est que F vaut l'identité. Et donc, si on revient sur
les petites astuces que je vous ai données sur F, enfin, les petits repères, ben, on a quelque chose de complètement cohérent.
On rappelle que, du coup, c'est une dilatation, c'est sans unité, hein. On est parti de F qui n'est— qui n'a pas d'unité. On fait juste le produit de F par F, enfin, de F transposée par F.
On ne change pas le système d'unité pour les deux tenseurs. Donc ça, c'est un peu un— c'est un tenseur qu'on n'utilise pas trop, en réalité, mais bon, ça permet de comprendre qu'est-ce qui est
lié à une transformation, qu'est-ce qui est lié à une dilatation, qu'est-ce qui est lié, du coup, à une déformation. Et pour caractériser la déformation, donc on a dit
que la configuration initiale, c'était l'identité, c'était les 100 % initiaux. Ben, on va reprendre notre F transposée F, et on va lui enlever l'identité. Et là, maintenant, on a vraiment
la partie déformation, la variation relative des longueurs au carré. Sauf que, petit détail, on rajoute un facteur 1/2, qui est très facile à oublier.
Donc résultat : on va définir un opérateur de déformation, qu'on appelle l'opérateur de déformation de Green-Lagrange, qu'on note E , et ça, c'est une notation qu'on retrouve de manière assez
large, même dans la littérature anglo-saxonne, donc il n'y a pas de problème avec ça. Et en fait, on va retirer à la dilatation les 100 % de la configuration initiale.
Donc on enlève l'identité. Ce qui nous permet de caractériser une déformation en termes de pourcents : 10 % de déformation, 10 % d'augmentation du prix, ou 10 % de réduction du prix si
on a une dilatation qui est inférieure à 1. Bon, par contre, la dilatation, elle ne peut pas être négative, ok, ça, ça ne va pas. Donc on garde l'aspect symétrique, hein. On est parti
d'un tenseur C , dont les propriétés sont la symétrie. On enlève juste l'identité, et on fait fois 1/2 , ça ne va pas changer l'aspect symétrique. Et là, cette fois, les composantes
qui sont sur la diagonale, donc non pas de C, mais de E, elles représentent les écarts relatifs des longueurs au carré selon les directions 1, 2 et 3, les trois directions de l'espace, ok.
Donc typiquement , si je reprends— cette fois, je prends un autre chiffre, je prends cette mousse-là, et mettons que j'étends jusqu'à peu près cette longueur-là
, que vaut la déformation dans cette direction, à peu près ? Ce n'est peut-être pas très clair. Ouais, c'est plutôt 50 %, à peu près. J'ai — si je prends la longueur
— puis alors après, c'est vrai que c'est une longueur au carré, donc bon. Mais globalement, oui, c'est à peu près 50 %, à peu près.
C'est vrai qu'on n'est pas en petite inflation, à chaque fois, c'est un peu — c'est un peu risqué. Mais oui, oui, du coup, c'est une longueur au carré. Donc
écart relatif des longueurs au carré. Et pour les composantes qui sont hors de la diagonale, ben, ça correspond aux variations d'angle entre les fibres qui étaient initialement alignées avec
les vecteurs de notre base. Cette fois, pour avoir un mouvement de corps rigide, il faut que ce tenseur ne soit pas égal à l'identité , mais il faut qu'il soit nul. Parce que là, on a retiré
l'identité, on a retiré la configuration initiale. Si en enlevant la configuration initiale, il reste quelque chose, c'est qu'on a bougé quelque chose, à la fois sur les longueurs,
enfin les distances entre les particules, ou sur les angles, ok. Donc là, cette fois, il faut qu'on ait un tenseur totalement nul pour que ça caractérise un mouvement de corps rigide. Donc
je reprends un peu, hein. Alors, de F , si on fait F transposée F , ça nous donne les dilatations. Et ensuite, si — on verra plus tard pourquoi il y a un facteur 1/2. Donc là, on retrouve C
, et ben, ça, ça permet de caractériser justement la déformation. C'est du jargon, hein, mais ça— derrière, il y a un sens qui permet de savoir ce qu'on manipule, et ça permet de mieux
— de mieux formaliser les choses. Alors, justement, je viens juste de parler de petites perturbations, hein. On va préciser un peu ce que c'est que les petites perturbations.
On va introduire une nouvelle grandeur qu'on n'a pas encore discutée pour l'instant, c'est le déplacement. Donc le déplacement , votre particule
dans la configuration initiale— bon, depuis tout à l'heure, je parlais de la particule qui était là— il y a eu un mouvement , elle est arrivée ici, à l'instant T. Le déplacement, c'est
tout simplement l'écart entre la position actuelle et l'initiale, ok. Mais bon, le déplacement, vous voyez que
ça ne tient pas compte de toute l'histoire, hein, le fait que, ben, la trajectoire, elle a pu être hyper courbée, on ne le voit pas apparaître dans le déplacement.
Vous pouvez très bien avoir fait une trajectoire complètement circulaire et être revenu ici, à un instant T. Pour vous, le déplacement est nul, mais pourtant, vous
avez parcouru des kilomètres, enfin, des kilomètres, des centimètres, ok. Donc c'est une grandeur qui a du sens, justement, quand on est sur des petites perturbations,
qu'on ne se déplace pas beaucoup par rapport à la position initiale, en réalité, ok. Donc c'est tout simple, ça permet de traduire avec le vecteur U qui traduit le déplacement en tout point.
Pour tout point M0, ben, c'est tout simplement l'écart à la position initiale, ok, qui nous permet d'arriver sur la position finale. Bon, ben, du coup, on peut dire qu' on peut relier
le gradient de la transformation. Donc ça, je vous rappelle que ça revient à OM, hein. Je vais oublier de le réécrire comme ça. Donc OM , je peux le séparer en deux contributions
: relation de Chal, OM plus M0 M. Et ça, c'est le déplacement. C'est le vecteur entre la position initiale et la position actuelle, ok. Si je dérive OM0 par rapport à OM0, enfin,
vu que je suis censé avoir un tenseur d'ordre 2, ça me donne plutôt l'identité . Et si je dérive cette partie-là, qui est le déplacement , par rapport aux coordonnées initiales, j'obtiens
le gradient du champ de déplacement. C'est exactement ça que j'ai ici. Je peux décomposer mon tenseur gradient de transformation en l'identité plus le gradient du champ de déplacement, d'accord.
Alors là, il est noté de trois manières différentes : avec la vision dérivée partielle du champ de déplacement par rapport à la coordonnée, enfin, par rapport à la position M0.
Ouais, j'aurais dû rajouter un petit — un vecteur, mais ça, ça ne va pas. Du coup, c'est l'identité plus le gradient de U, mais de manière implicite, c'est la dérivée par rapport à M0.
Et pour ceux qui sont familiers avec la notation labla, le gradient, c'est labla appliqué à U. Ben, du coup, je peux reprendre les mêmes notations, mais appliquer cette fois
à ce que j'utilise pour caractériser la déformation, le tenseur de déformation de Green-Lagrange : 1/2 de F transposée F moins l'identité. Ben, en réalité,
je vois que je peux le réécrire sous cette forme-là. Alors, peut-être que je vous le remonte, mais bon, c'est assez simple. On va faire le calcul rapidement. Ok, F, j'ai vu que c'était
l'identité plus le gradient de U. Donc c'est comme si je calculais identité plus le gradient de U, que je vais noter avec cette notation-là, transposée fois I plus le gradient de U.
Et à ça, je vais enlever l'identité. Jusque-là, hein, je vais juste développer la forme de F. Il n'y a pas de magie noire, ok. Du coup, je vais faire les produits croisés. Donc I
identité fois l'identité ident ité. Ensuite, identité fois le gradient de U gr adient de U. Gradient de U transposée fois l'identité gr adient de U transpos ée.
Et gradient de U transposée fois gradient de U gr adient de U transposée fois gradient de U. Et il reste encore moins l'identité. L'identité, qui s'annule. Qu'est-ce qui me reste ?
Le gradient de U, son transposé, et un joli petit terme quadratique qui fait apparaître le gradient de U fois son transposé, enfin, le transposé du gradient de U fois le gradient de U.
Le fait d'avoir — d'être en petites perturbations, ça veut dire qu'on va avoir des, a priori, des petits déplacements globalement, des petites déformations, mais surtout des
— on va avoir petits déplacements, petites déformations, petites rotations. Et tout ça, enfin, tout ça, petites déformations et petites rotations, ça veut dire qu'on va avoir des petites
transformations. Et des petites transformations, ça veut dire que F, finalement, il va être très proche de I, de l'identité
, et donc que le gradient du champ de déplacement, il va être très petit. Si ça, c'est très petit, ben, ça, ça va être encore plus petit.
Et donc, par une approche de type développement limité, on va facilement pouvoir négliger ce terme. C'est le principe
de l'hypothèse des petites perturbations : on va se débarrasser de ce terme qui, au final, est non linéaire, et qui va surtout nous casser les pieds très rapidement
dès qu'on va vouloir mettre ça en équation et résoudre les équations, ok. Donc, dans l'absolu, la forme pour le champ, enfin, de déformation,
ça peut être mis sous cette forme, celle-là, ou celle-là, c'est juste des notations différentes, ok, c'est la même chose. Mais par contre, on peut avoir sa version linéarisée
lorsque l'on considère que les transformations sont infinitésimales, c'est-à-dire que la norme du gradient de U est petite. Donc, sous l'hypothèse des petites perturbations, qui se regroupe
sous deux sous-hypothèses, les déplacements sont petits, ça veut dire qu'on va avoir la norme du champ de déplacement qui va être petite par rapport au diamètre apparent de notre structure.
Donc, en gros, ça veut dire que les configurations initiales et actuelles, courantes, elles peuvent être plus ou moins confondues, et que les transformations sont petites.
Infinitésimales, c'est un mot un peu plus savant, mais ça veut dire petit, quoi. Et mathématiquement, comment ça se traduit ? Ça veut dire que la norme du tenseur gradient du déplacement
est très petite. Et dans ces cas-là, pour la norme, on prend la norme infinie, c'est-à-dire la valeur absolue de la— enfin, le max des valeurs absolues de chaque composante du tenseur. C'est ça.
La norme du tenseur A, quel qu'il soit, du second ordre, c'est le max sur I et J de la valeur absolue de la composante IJ. On regarde quel est le max des valeurs absolues des composantes.
Et ça, ça permet de caractériser, s'assurer qu'on est très petit devant l'unité, devant, ok. Ça, c'est une manière de vérifier qu'on est — qu'on est
sous— soit qu'on est dans le domaine des petites perturbations, soit ça va nous permettre de poser une limite pour dire : ben, là, notre modèle, il marche bien tant que l'on est dans —
on ne dépasse pas telle valeur pour tel paramètre, pour le temps, pour le temps d'observation du mouvement, etc., etc. Donc ça, c'est des vérifications que vous aurez à faire par la suite. Alors,
l'hypothèse de petites transformations, donc le fait d'avoir ce gradient du champ de déplacement qui est petit, ça implique en fait que les déformations sont petites. Donc, mécaniquement
, ce tenseur-là, il va être très petit. Donc il va être très petit devant. Donc pareil, avec le même principe pour la norme. Et également que les rotations sont petites.
Alors ça, on verra par la suite. Mais ce tenseur-là, là, le tenseur ω, vous voyez qu'il y a une petite barre verticale, là, ça correspond à la partie antisymétrique du gradient de U. Alors,
il s'agit d'une implication et non d'une équivalence, hein, encore une fois. Vo us allez être habitués à ça, hein.
Ce n'est pas parce que vous avez petites déformations que vous avez petites transformations. Et ça, c'est un mauvais réflexe qu'on a assez régulièrement : « Ah oui,
on a une petite déformation, donc c'est une petite transformation. » Non, non, non. Vous pouvez avoir des grandes rotations qui peuvent venir mettre le bazar là-dedans. Et on va le voir
dans un exercice qu'on fera peut-être tout à l'heure, hein, je ne sais pas si on aura le temps pour ça. Donc, du coup, donc là, j'ai différentes formes. Enfin, j'ai la forme pour mon tenseur
de déformation de Green-Lagrange, donc j'ai dit que je pouvais l'avoir sous cette forme : le gradient de U plus son transposé plus — on va le transposer comme ça— fois le gradient de U. Et
si je suis en HPP, ça, ça va être très petit devant le gradient de U ou son transposé. Et donc, du coup, dans ce cas-là, si j'ai l'hypothèse des petites perturbations,
ben, je vais plutôt avoir tendance à utiliser la forme linéarisée, c'est-à-dire le tenseur qu'on note ε, tenseur de déformation. ε, en mécanique, c'est la déformation,
qui va tout simplement avoir cette forme-là , la somme du gradient de déplacement et de son transposé. Ce qui revient quand on fait ce type d'opération, c'est la partie symétrique
du gradient de U, ok. Quand vous faites ce type d'opération, vous prenez la moitié de la somme d'un tenseur et de son transposé, vous avez symétrisé votre tenseur. Et faire exactement
l'opération inverse, justement, pour obtenir la partie antisymétrique. Et n'importe quel tenseur, du second ordre ou autre, peut se décomposer en une partie symétrique et antisymétrique.
Des fois, il y a l'une ou l'autre qui peut être nulle. Ben, quand votre tenseur est symétrique, la partie antisymétrique
est nulle, et quand votre tenseur est antisymétrique, la partie symétrique est nulle. Dans l'hypothèse des petites perturbations, en fait, on —
l'hypothèse qu'on fait par-dessus, hein, c'est de se dire que, ben, la partie symétrique du gradient de déplacement, en fait, correspond aux déformations, de manière pleine et entière.
Et par contre, la partie antisymétrique du gradient de déplacement représentera les petites rotations de votre milieu, ok. Donc ε, là, on appelle ça le tenseur de déformation
linéarisé, ou le tenseur de déformation infinitésimal, parce que — euh , alors, ah oui, il y avait ces aspects-là. Ça, ça ne rapporte pas grand-chose. C'est juste si vous êtes dans la base
orthonormée cartésienne, vous pouvez le noter comme ceci, et là, de manière indicielle, vous pouvez représenter les différentes coordonnées : actuelle, initiale, et le déplacement . Le tenseur
gradient de transformation, donc la notation ΔIJ, hein, c'est l'indice de Cronecker. Ça vaut 1 quand I = AJ, ça vaut 0 dans tous les autres cas. Vous retrouverez ça dans les annexes des
bases mathématiques, il y en a de— donc je ne vais pas revenir là-dessus. Là, vous retrouvez la forme du tenseur de déformation de Green-Lagrange, et la forme linéarisée.
Donc, dans la forme linéarisée, hein, vous oubliez ce terme— les termes quadratiques qui, a priori, sont négligeables, ok. Alors, attention, justement, mais on va le voir dans un exercice, hein.
Quand vous utilisez cette forme-là pour caractériser les déformations alors que vous avez potentiellement des grandes rotations, vous allez potentiellement trouver une déformation non nulle,
alors qu'avec la forme complète, là, du tenseur de déformation, vous auriez bien trouvé une déformation de manière — de manière exacte, qui devrait être nulle. Donc c'est un petit
— un petit warning à garder en tête, hein. On va utiliser essentiellement cette forme-là, mais pour l'utiliser, il faudra s'assurer qu'on respecte bien l'hypothèse des petites perturbations.
Sinon, on pourrait prendre une forme pour mesurer les déformations qui est plus simple, mais qui, en réalité, est fausse au regard de la situ ation, ok. 3, 4 .
Alors, pour ceux qui ont peut-être déjà fait un peu de résistance des matériaux, peut-être qu'ils sont passés par des — comment, des cursus un peu plus ingénieurs.
Ce fameux ε, là, on appelle ça, en manière un peu simpliste, la déformation de l'ingénieur. Parce que les ingénieurs, généralement, ils raisonnent essentiellement en petites perturbations.
Alors, c'est un peu caricatural, hein, mais on essaie d'utiliser des modèles qui sont faciles à manipuler et qui conduisent à des calculs linéaires, enfin, entre guillemets. Donc,
cette déformation, elle correspond aux différentes valeurs de la diagonale du tenseur de déformation linéarisée, et en réalité, de manière assez simple, c'est la variation longueur
divisée par la longueur initiale, ok. Déformation de l'ingénieur, ça se manipule assez facilement. Donc L moins L0 divisé par L0. Est-ce que ça va pour ça ?
Pardon, je n'ai pas laissé la place à des question s. Peut-être qu'il y a besoin de repréciser quelque chose. Alors, on avance. Ça, c'est un point qui est un petit peu
— un petit peu hors programme, on va dire, hein, ça va peut-être un peu trop loin, mais . Le fait que les déformations, elles dérivent d'un champ de déplacement.
Mettons, vous connaissez le champ de déplacement, vous avez juste à dériver par rapport à l'espace, calculer son gradient, et puis
de calculer la partie symétrique pour avoir accès aux déformations. Mettons, on est dans— on reste dans le cadre des petites perturbations. Donc je peux utiliser cette formule-là. Ça,
c'est pas mal. C'est direct : vous avez un champ à 3 composantes, vous voulez aller sur un champ à 6 composantes, parce que ce tenseur-là, il a la bonne idée d'être symétrique.
Un tenseur symétrique en 3D, c'est 6 composantes, ok. Bon, ben, ça, ça se fait. Des fois, on a besoin de retrouver le champ de déplacement à partir du champ de déformation.
C'est-à-dire de remonter à un champ qui est un déplacement, un vecteur à 3 composantes, à partir d'un champ de déformation qui, lui, a 6 composantes.
On ne peut pas utiliser n'importe quelle forme pour un champ de déformation. Donc vous ne pouvez pas— enfin, comment, si vous avez supposé une certaine forme pour le champ de déformation,
en vous disant : « Ben, je fais l'hypothèse qu' en regardant ce mouvement, par exemple, la déformation évolue de manière cubique, donc en x1
puissance 3, selon la direction, selon cette direction. » Ça, c'est une hypothèse que vous faites, ok. Ben, peut-être que vous n'allez pas trouver de champ de déplacement qui
va être compatible avec ce champ de déformation. Et tout ça, c'est régi, justement, par des équations de compatibilité. Le champ de déplacement, il doit être continu, donc
sa forme doit être cadrée. Et donc, justement, la continuité du champ de déformation, elle, elle est assurée du champ de— du champ de dép lacement, hein, petite erreur.
Elle est assurée, justement, par les jeux d'équations de compatibilité. Alors,
on peut les résumer en disant que le rotationnel du rotationnel du transposé du champ de déplacement de déformation est égal à 0. Bon, le rotationnel
d'un tenseur, bon, ce n'est pas évident, mais bon, ça se calcule. Et en réalité, vous avez un lien avec le théorème de Schwartz qui dit que pour les dérivées doubles
du tenseur de rotation, donc le ω, hein, vous pouvez intervertir l'ordre des dérivées par rapport à la direction k et l, et vous avez un lien entre la— enfin, entre le tenseur de rotation,
les petites rotations, et le tenseur de déformation avec les duels des li. Avec ça, en fait, vous arrivez à ce type d'équation.
Quand vous tenez compte de toutes les symétries et de tous les aspects liés au théorème de Schwartz, à la fin, vous n'avez que 6 possibilités pour ces équations-là, et il faut les respecter.
Alors, peut-être la seule chose à retenir avec cette histoire de compatibilité des déformations : est-ce que vous êtes capables, à peu près, de me donner
une caractéristique pour les champs de déformation pour lesquels on est sûrs que ça marche tout le temps ? C'est-à-dire qu'on a forcément la compatibilité qui est assurée.
Alors, le plus facile, c'est la déformation nulle. Si le tenseur de déformation est nul en tout point, ben, c'est facile, hein : je dérive 0 par rapport à n'importe quoi, plus ou moins 0,
c'est forcément égal à 0 plus 0 ou 0 moins 0. Il n'y a pas de mystère là-dessus, ok. Donc la première solution, c'est un champ de déformation nul, mais bon, un fairet très limité, ok.
Est-ce que vous êtes capables de me donner une autre forme de champ de déformation, avec une évolution dans l'espace, hein ? C'est surtout ça qui nous intéresse, parce que
là, les dérivées, je ne les ai peut-être pas reprécisées, mais ce sont des dérivées par rapport à l'espace, par rapport aux coordonnées de l'espace.
Est-ce que vous êtes capables de me donner quelque chose qui n'est pas nul, comme champ de déformation, mais qui a une forme simple et qui sera toujours compatible ? Avec cette forme-là, les formes
— ces formes-là d'équations de compatibilité, ça veut dire que vous prenez certaines composantes du champ de déformation, et vous dérivez
une première fois par rapport à une composante de l'espace, et une seconde fois par rapport à une autre composante de l'espace. A priori, pour quel type de champ ça marche toujours ?
Un truc un peu plus complexe que nul. Je pense qu'il est trop tard. Pardon ? O ui, même avant linéaire, constant. Mais je suis d'accord avec linéaire.
Si c'est constant, vous dérivez une première fois par rapport à n'importe quelle composante, ben, vous obtenez 0 pour chacun des termes, et du coup ça marche.
Vous vérifiez bien que 0 est égal à 0, ok. Et bonne remarque, alors même plus que linéaire, du coup, une combinaison de constant et linéaire affine. Bon, bref. Si vous avez des polynômes
de degré inférieur à 2 en fonction des différ ents paramètres de l'espace, ça marche toujours. Donc si vous tombez sur un champ de déformation qui a la bonne idée d'avoir cette forme-là,
vous pouvez tout de suite le dire . Pas besoin de vérifier les équations de compatibilité, c'est forcément compatible, ok. Et donc vous n'avez pas à vous fader toutes les équations à vérifier,
ce qui est pratique. Touj ours plus pratique de s'éviter des calculs. On gagne du temps et on évite de faire des erreurs. Bon. Mais ces équations de compatibilité , c'est plutôt
ces équations-là , ici, qui vont nous permettre, justement , de voir comment est-ce qu'on intègre le champ de déformation pour arriver au gradient du champ de déplacement, puis ensuite
au champ de déplacement lui-même. Bon, on va finir avec quelques aspects pratiques sur les déformations. Alors, là, vous avez un exemple de comment se comporte un matériau,
dans le cadre général. Alors, en très continu, là, vous avez l'exemple d'un acier plutôt « doux », entre guillemets, et donc plutôt ductile. Alors, la ductilité, hein, c'est la capacité
que peut avoir un matériau à se déformer au-delà de sa limite d'élasticité, lorsqu'il commence à générer des déformations irréversibles de la plasticité. Donc plus vous pouvez continuer
d'étirer, si vous voulez, votre barre d'acier au-delà de la limite d'élasticité, plus c'est ductile, ok. Donc là, selon cet axe-là, on a la déformation.
Là, on a la contrainte, une force divisée par une surface, ok. Si vous avez un matériau plutôt fragile,
ben, globalement, dès que vous allez atteindre la limite d'élasticité, très vite, vous allez atteindre la rupture. Vous déformez du verre un peu au-delà de la limite, c'est cassé, c'est fini.
Quelque chose qui est fragile, exemple parfait, la craie, ok, que vous fassiez en traction ou en flexion, dès que vous
franchissez la limite, il n'y a pas de déformation irréversible, il y a rupture directe. C'est ça, un matériau fragile.
Quelque chose qui est fragile, ce n'est pas quelque chose qui casse très vite, c'est quelque chose qui n'est pas capable d'accumuler de la déformation plastique. C'est tout de suite la rupture, ok.
Dès que vous tapez un peu trop fort dans un verre, hein, si ça tombe par terre, c'est cassé. Si c'est ductile, ça encaisse un peu la déformation. Typiquement, l'aluminium,
hein, c'est souvent un peu ductile. Vous voyez que ça encaisse un peu de déformation. Ok. Bon, peu importe.
Là, tout ce qui se passe après, hein, vous pouvez avoir de la plasticité, des tressages, de la striation, peu importe. Ce qui est important, c'est : nous,
on va dire, on va modéliser ce qui se passe dans la phase d'élasticité qui est essentiellement linéaire, la relation entre déformation et contrainte est linéaire, jusqu'à ce qu'on at
teigne la limite d'élasticité. Au-delà, c'est non linéaire, on n'ira pas plus loin. Par contre, on se donnera les moyens de définir au bout de quel chargement
on atteint cette limite-là, et il vaut mieux pas aller au-delà, ok.
Donc c'est le début de la déformation irréversible, que ce soit de la plasticité, donc l'accumulation de déformation, qui pourra pas être — qui pourra être — qui ne sera pas réversible,
ou tout simplement de la rupture si on est dans le cas d'un matériau qui est fragile. Donc ça, c'est pour vous donner une idée de comment peut se comporter un matériau. Alors,
les polymères, c'est— même l'élasticité, c'est un peu non linéaire, mais on ne va pas aborder ça, parce qu'
on n'a pas les modèles pour— enfin, on ne va pas vous présenter les modèles pour étudier ça. Bon, voilà. Alors, avec cette courbe de traction, là, que je vous ai présentée, donc
pour avoir des ordres de grandeur, si vous travaillez sur un matériau de type acier, la partie élasticité , en termes de gamme de déformation, ça va à peu près jusqu'à 1 %, de
0, à peu près 0,1 jusqu'à 1 %. Si vous allez au-delà, c'est que vous passez en plasticité, vous générez des déformations qui sont irréversibles. Et donc là, ben, vous pouvez aller
de 1 jusqu'à 10 %, c'est plutôt de la plasticité. Par contre, quand vous faites vraiment de la mise en forme, hein, quand vous emboutissez, par exemple, des plaques d'acier pour faire
des moules, par exemple, donc ça, c'est sur les presses industrielles, là, vous générez des déformations qui sont vraiment très, très importantes, et là, ce n'est même plus de la plasticité,
c'est de la mise en forme. Là, vous êtes à plus de 10 % de déformation, c'est énorme. Ou ce que vous pouvez faire avec de la forme, typiquement. Si vous prenez l'exemple
d'un béton qui est soumis à une compression et qui va jusqu'à rupture, ben, c'est à peu près 0 ,1 %. Vous voyez que le béton, il n'encaisse pas beaucoup de déformation, en réalité, avant
de rentrer. Et je ne vous dis pas ce que ça peut encaisser en déformation en traction, mais c'est proche de 0, en réalité. Vous devez savoir, peut-être, que le béton, c'est un matériau qui
est fragile. Si vous exercez de la traction dessus, tout se désagrège de manière presque immédiate. C'est pour ça qu'on fait quoi avec le béton ? Pardon ? On met de l'acier, on l'arme, ok.
Première étape : on met des câbles d'acier dedans, ce qui fait que quand il y a un chargement de traction, c'est les câbles en acier qui prennent la traction, et du coup, ça
ne fait pas rompre le béton. Ça, c'est la première étape. Deuxième étape : qu'est-ce qu'on peut faire avec les câbles en acier quand on fait couler le béton ? On les tend.
On fait couler le béton, et ensuite on relâche. Ce qui fait que les câbles sont précontraints, et en plus de prendre les efforts de traction, ben, ils vont déjà appliquer une précontrainte
sur le béton, ce qui fait qu'on a un peu plus de marge avant d'arriver en traction. Le béton est précontraint, ok. Bon, voilà, quelques petits principes pour vous familiariser avec ce concept-là.
Alors, quelques exemples de méthodes expérimentales pour avoir accès à la mesure des déformations, parce que c'est presque un— c'est avec les déplacements.
Les déplacements, on peut les mesurer typiquement avec des lasers, avec des comparateurs, hein. C'est tout simplement une tige avec un ressort
qui appuie sur une surface, et puis, ben, dès que ça bouge, ben, vous êtes capables de mesurer de combien ça s'est déplacé. Voilà.
Vous avez des extensomètres aussi, qui permettent d'être plaqués, par exemple, sur la surface d'une éprouvette. Si
l'éprouvette se déforme, ben, l'extenso, il mesure le fait que, ben, vous avez une variation de longueur dans une direction, ok, le facteur de déplacement. La méthode des grilles, c'est
tout simplement : vo us mettez une— vous imprimez une grille sur votre matériau, comme ça, et là, ben,
c'est un peu le principe de la corrélation d'image, mais là, vous le faites avec une grille. Vous tirez, vous
observez, vous êtes capables de mesurer le fait qu'il y a une variation de longueur entre les intersections des lignes, mais aussi, vous pouvez voir qu'il peut y avoir aussi une variation des angles,
ok. Donc c'est les deux caractérisations de la déformation : la variation des longueurs entre les particules et la variation des angles. Capteurs de déplacement, donc
par méthode laser ou comparateur par contact. Les jauges de déformation : typiquement, vous allez mettre à la surface d'une éprouvette un fil
de cuivre, typiquement, qui va faire un serpentin, comme ça, et ça va vous permettre de mesurer la déformation dans cette direction-là. Parce que quand vous allez
mettre une tension, là, entre les deux, si vous tirez, ça va changer la mesure de la tension, ok. Il y a une loi — en gros, ça va changer la résistivité de votre dispositif. Et donc, par
un mécanisme d'étalonnage, vous allez être capables de remonter à la déformation qui est appliquée sur la surface. Alors, ça ne marche que pour un point, ok, et ça vous donne
la déformation que dans une seule direction. Donc il faut combiner ça avec plusieurs jauges pour avoir accès au tenseur complet. Corrélation d'image, en 2D, par exemple. Donc Mouchti sur
une surface, donc c'est un peu le principe de la méthode des grilles, mais vous pouvez avoir des taches, des grosses taches blanches, des grosses taches noires, des petites taches blanches, des petites taches noires,
et en fait, ça va vous permettre de capter les différ entes échelles de déformation au sein de votre mesure.
Vous allez essayer de retrouver le champ de déplacement qu'il faut appliquer à l'image déformée pour retourner sur l'image de départ, ok, ou l' inverse, comme vous voulez, mais
c'est un peu le principe. Vous pouvez utiliser la diffraction des rayons X. Bon, ça, c'est que pour les matériaux métalliques, hein. Vous envoyez des rayons X , conditions de Brague—
ça va être un peu plus compliqué— mais ça peut vous donner une information sur la distance entre les plans atomiques, et vous pouvez remonter à la déformation. Je vais m'arrêter là pour
ces aspects-là. Typiquement, la méthode des grilles, hein, là vous voyez comment peut se déformer une grille, et donc, du coup, ben, en procédant par carré de grille par carré de grille,
vous pouvez remonter à la variation d'angle et à la variation de longueur. Quelques mouvements de base : ben, là, vous avez un domaine initial qui vous est donné en trait plein, et ça déformait.
Bon, ben, vous voyez qu'il n'y a pas de variation de longueur dans les deux directions de l'espace, il n'y a pas de rotation, c'est une translation uniforme, avec un vecteur B qui est donné ici.
Ici, vous avez une rotation uniforme de centre C, ok, avec un angle alpha, ok, pas très compliqué. Déformation de glissement simple. Donc là, à votre avis,
avec ce que je vous ai dit tout à l'heure, est-ce qu'il y a une différence entre la surface ou le volume, si vous voulez, du domaine initial et final ? On garde le même volume. Donc
c'est un mouvement incompressible, sans changement de volume. Mais il y a une déformation, parce qu'il y a une variation des angles entre les fibres orientées suivant les directions initiales, ok.
Vous avez changé l'angle entre — ben, vous prenez une triparticule, là , avec celle qui était là, là et là, ben, votre angle, il a varié, ok. Ça, c'est du glissement simple.
Ça veut dire, c'est vraiment le— vous avez pris un jeu de cartes, et vous avez juste poussé sur le côté, vous avez juste un glissement dans une direction.
Là, vous avez ce qu'on appelle le glissement pur. Là, la petite différence , c'est que là, vous n'avez pas de rotation globale, ok, vous avez juste contracté dans une direction
et tiré dans l'autre. Là, vous avez fait— vous avez généré une légère rotation de vos fibres, ok. Bon, on verra ça par la suite. Si vo
us calculez les directions principales de déformation, là, elles évoluent au cours de la déformation, là, elles sont tout le temps alignées de la même manière.
Un glissement pur, ça peut être résumé en deux glissements simples ? D'une direction puis dans l'autre ? Ou c'est différent ? Oui, on peut recomposer ça.
Mais alors, en élasticité, le trajet de chargement importe peu. Ce n'est pas forcément le cas quand on se retrouve dans des aspects non linéaires. Mais oui, par combinaison
d'un glissement simple et d'un glissement pur— et d'un— de deux glissements simples, on va pouvoir retrouver le glissement pur, oui, en effet.
Je vérifie qu'on ne dise pas de bêtises, mais a priori, c'est bon. Glissement simple, glissement pur, donc ça, on voit. Là, par exemple, vous avez une dilatation isotrope,
donc ça se dilate de la même manière sur toutes les directions de l'espace, enfin, en tout cas dans le plan. Je ne voulais pas faire en 3D, je prendrai la question juste après.
Et là, vous avez un exemple de dilatation qui est anisotrope. Ça se dilate davantage suivant l'axe horizontal que suivant l'axe vertical.
Donc vous n'avez pas le même rapport, enfin, la même valeur pour les dilatations, donc lambda 1 dans la direction E1 et dans la direction E2. Quand on parle de glissement, est
-ce qu'il y a— est-ce qu'il y a des angles qui peuvent être — ? C'est— on parle de glissement, c'est du jargon. En anglais, on peut parler de soit « gliding
», soit on peut parler de « shear strain », mais de « simple shear » ou « pure shear ». C'est un choix qui n'est pas forcément tout le temps bienvenu.
À un moment, on a choisi un terme, et puis on l'a gardé. On peut parler de — on pourrait dire « distorsion » aussi. Ça, c'est — vous voyez que l'image initiale et l'image finale sont
— enfin, il y a une distorsion entre l'image initiale et l'image finale. Enfin, l'image— le domaine initial et le domaine final. Bon, c'est— il faut— voilà, il faut —
qu'est-ce qu'on retrouve des fois comme terme ? Non, mais c'est glissement. Alors, il y a un lien, parce que les mécanismes de déformation plastique, typiquement dans les alliages, dans les aciers,
c'est — pour la déformation plastique, on dit que c'est du glissement entre les plans cristallins. Vous avez — vous imaginez, vous avez des atomes qui sont à chaque intersection de lignes, là.
Quand vous générez de la déformation plastique dans un alliage, dans un — dans du fer, par exemple, ou dans de l'acier, en gros, vous allez aller au-delà de la limite d'élasticité, et pot
entiellement, l'atome qui était là, ben, au bout d'un moment, pouf, il va se décaler ici. Et vous allez générer un glissement plus ou moins global de toute la couche d'atome,
et vous allez générer des défauts qu'on appelle des dislocations. Et ça, c'est des mécanismes qui se font sans variation de volum e, et donc on parle de glissement. Alors,
je ne sais pas si, de manière historique, on s'est basé sur justement cette approche de glissement des plans atomiques les uns par rapport aux autres. Je ne sais pas.
Mais voilà, on utilise ce terme. Bon. Normalement, il nous reste 10 minutes, mais j'ai l'impression que ça fait peut-être déjà un peu trop pour une première journée.
Est-ce que ça paraît raisonnable , en termes de planning, de s'arrêter là ? Ça ne me paraît pas idiot. Peut-être, avant de vous libérer, vous avez peut-être des questions, hein. Peut-être
une redoutable envie de faire un QCM. Je n'ai pas l'impression. Ok. Alors, je — ah, je crois que j'ai oublié de mettre les slides sur Ecampus. De toute façon, ils ne sont
pas— ils ne sont pas complets pour l'instant. On peut essayer de faire ça dans la soirée. Mais de toute façon, je pense que j'ai encore des petites corrections à apporter par-ci par-là.
Donc bon, je vais incrémenter avec la V0, la V1, etc. La dernière fois, j'ai regardé, il y avait les slides de ce matin. Ça s'arrêtait à peu près à— Voilà, mais j'ai
— en fait, j'ai régénéré le truc . Tout à l'heure, j'ai fait— je finis de faire mes slides très rapidement avant de commencer, et j'ai oublié de les déposer. Donc
vous n'avez pas pu les suivre en même temps, mais bon. Je vais essayer de vous déposer ça dans la soirée. Ok ?