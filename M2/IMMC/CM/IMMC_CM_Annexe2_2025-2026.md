# Annexe B

## Rappels et bases de mathématiques

On se place dans un espace euclidien E à 3 dimensions. Soit $( \vec { e } _ { 1 } , \vec { e } _ { 2 } , \vec { e } _ { 3 } )$ une base orthonormée de E.

## B.1 Vecteurs et tenseurs

## B.1.1 Vecteurs

Un vecteur est représenté sous la forme :

$$
\vec {V} = V _ {1} \vec {e} _ {1} + V _ {2} \vec {e} _ {2} + V _ {3} \vec {e} _ {3} = \left( \begin{array}{c} V _ {1} \\ V _ {2} \\ V _ {3} \end{array} \right) _ {(\vec {e} _ {1}, \vec {e} _ {2}, \vec {e} _ {3})}\tag{B.1}
$$

où $V _ { 1 }$ , $V _ { 2 }$ et $V _ { 3 }$ sont les composantes de $\vec { V }$ dans la base $( \vec { e } _ { 1 } , \vec { e } _ { 2 } , \vec { e } _ { 3 } )$

En utilisant la convention de sommation (sommation sur les indices répétés), le vecteur $\vec { V }$ s’écrit aussi :

$$
\vec {V} = V _ {i} \vec {e} _ {i}\tag{B.2}
$$

## B.1.2 Tenseurs d’ordre 2

Un tenseur du second ordre A est une entité mathématique qui est une généralisation de la notion de vecteur. Il peut être représenté par une matrice $3 \times 3$ , lorsqu’on travaille en dimension 3. Il est défini à partir de ses composantes $A _ { i j }$ par :

$$
\mathbb {A} = \left[ \begin{array}{c c c} A _ {1 1} & A _ {1 2} & A _ {1 3} \\ A _ {2 1} & A _ {2 2} & A _ {2 3} \\ A _ {3 1} & A _ {3 2} & A _ {3 3} \end{array} \right] _ {(\vec {e} _ {1}, \vec {e} _ {2}, \vec {e} _ {3})} = A _ {i j} \vec {e} _ {i} \otimes \vec {e} _ {j}\tag{B.3}
$$

avec $\otimes$ représentant le produit tensoriel.

Un tenseur du second ordre A peut être vu comme la représentation d’une application linéaire dans la base $( \vec { e } _ { 1 } , \vec { e } _ { 2 } , \vec { e } _ { 3 } )$ . Si $\vec { W } = \mathbb { A } \vec { V }$ , les composantes du vecteur W sont alors données par :

$$
\begin{array}{l} W _ {1} = A _ {1 1} V _ {1} + A _ {1 2} V _ {2} + A _ {1 3} V _ {3} \\ W _ {2} = A _ {2 1} V _ {1} + A _ {2 2} V _ {2} + A _ {2 3} V _ {3} \\ W _ {3} = A _ {3 1} V _ {1} + A _ {3 2} V _ {2} + A _ {3 3} V _ {3} \end{array}\tag{B.4}
$$

ou sous forme plus synthétique via la notation indicielle et la convention de sommation d’Einstein) :

$$
W _ {i} = A _ {i j} V _ {j}\tag{B.5}
$$

## Décomposition en parties symétrique et antisymétrique

Un tenseur A est dit :

— symétrique si $\mathbb { A } = \mathbb { A } ^ { \top }$

— antisymétrique si $\mathbb { A } = - \mathbb { A } ^ { \top }$

On peut toujours décomposer un tenseur d’ordre 2 en parties symétrique sym(A) et anti symétrique asym(A) :

$$
\operatorname{sym} (\mathbb {A}) = \frac {1}{2} \left(\mathbb {A} + \mathbb {A} ^ {\mathsf {T}}\right) \quad \text { et } \quad \operatorname{asym} (\mathbb {A}) = \frac {1}{2} \left(\mathbb {A} - \mathbb {A} ^ {\mathsf {T}}\right)\tag{B.6}
$$

## Décomposition en parties sphérique et déviatorique

Un tenseur d’ordre 2 A est dit :

— sphérique si A = αI avec α scalaire

— déviatorique si Tr $\mathbb { A } = 0$

On peut toujours décomposer un tenseur d’ordre 2 en parties sphérique sphe(A) et déviatorique dev(A) :

$$
\operatorname{sphe} (\mathbb {A}) = \frac {\operatorname{Tr} \mathbb {A}}{3} \mathbb {I} \qquad \text {et} \qquad \operatorname{dev} (\mathbb {A}) = \mathbb {A} - \operatorname{sphe} (\mathbb {A}) = \mathbb {A} - \frac {\operatorname{Tr} \mathbb {A}}{3} \mathbb {I}\tag{B.7}
$$

## Tenseur d’ordre 2 symétrique

Lorsqu’un tenseur d’ordre 2 A est symétrique, on peut le représenter de manière allégée, avec uniquement la partie triangulaire supérieure.

$$
\mathbb {A} = \left[ \begin{array}{c c c} A _ {1 1} & A _ {1 2} & A _ {1 3} \\ & A _ {2 2} & A _ {2 3} \\ & & A _ {3 3} \end{array} \right] _ {(\vec {e} _ {1}, \vec {e} _ {2}, \vec {e} _ {3})}\tag{B.8}
$$

La symétrie d’un tenseur d’ordre 2 simplifie les expressions des opérateurs différentiels dans les différents systèmes de coordonnées (notamment cylindriques et sphériques), se référer au formulaire.

## B.2 Algèbre tensorielle

## B.2.1 Notation indicielle

## Convention de sommation d’Einstein

La convention d’Einstein consiste à omettre les signes de somme ($\sum$), afin d’alléger les notations notamment. On effectue, de manière implicite, les sommes sur les indices répétés. Ces indices sont considérés comme « muets », car on peut changer leur nom sans changer la valeur du résultat. On écrira donc le terme de droite, plutôt que le terme de gauche :

$$
\sum_ {j = 1} ^ {n} \sum_ {k = 1} ^ {n} a _ {i j} b _ {j k} c _ {k} = a _ {i j} b _ {j k} c _ {k}\tag{B.9}
$$

## Dérivée partielle

On note la dérivée partielle de la quantité $\bullet$ par rapport à la coordonnée spatiale $i$ ($x_i$ en description eulérienne, $X_i$ en description lagrangienne) :

$$
\bullet_ {, i} = \left\{ \begin{array}{l l} \frac {\partial \bullet}{\partial x _ {i}} & \text {   en   description   eulérienne   } \\ \frac {\partial \bullet}{\partial X _ {i}} & \text {   en   description   lagrangienne   } \end{array} \right.\tag{B.10}
$$

## Symbole de Kronecker

On définit le symbole de Kronecker $\delta$ comme suit :

$$
\delta_ {i j} = \left\{ \begin{array}{l l} 1 & \text { si } \quad i = j \\ 0 & \text { si } \quad i \neq j \end{array} \right.\tag{B.11}
$$

Ce symbole revient à la matrice identité I.

## Symbole de Levi-Civita (ou tenseur de spin)

On définit le symbole de Levi-Civita $\varepsilon ,$ correspondant au tenseur de spin (du $3 ^ { \mathsf { e } }$ ordre), comme suit :

$$
\varepsilon_ {i j k} = \left\{ \begin{array}{l l} 1 & \text { si } (i, j, k) \in \{(1, 2, 3), (2, 3, 1), (3, 1, 2) \} \to \text { permutation   directe } \\ - 1 & \text { si } (i, j, k) \in \{(1, 3, 2), (2, 1, 3), (3, 2, 1) \} \to \text { permutation   indirecte } \\ 0 & \text { si   un   indice   est   répété } \end{array} \right.\tag{B.12}
$$

Ce symbole revient au « tenseur de spin », du $3 ^ { \mathsf { e } }$ ordre. Voici plusieurs formules utiles :

$$
\varepsilon_ {i j k} \varepsilon_ {i j k} = 6\tag{B.13}
$$

$$
\varepsilon_ {i j k} \varepsilon_ {i j n} = 2 \delta_ {k n}\tag{B.14}
$$

$$
\varepsilon_ {i j k} \varepsilon_ {i l m} = \delta_ {j l} \delta_ {k m} - \delta_ {j m} \delta_ {k l}\tag{B.15}
$$

## B.2.2 Invariants d’un tenseur d’ordre 2

On appelle invariants d’un tenseur du second ordre $\mathbb { A }$ les $I _ { n } ( \mathbb { A } )$ , ou en abrégé $I _ { n } ,$ les scalaires définis comme suit :

$$
I _ {1} (\mathbb {A}) = \operatorname{Tr} (\mathbb {A}) \quad ; \quad I _ {2} (\mathbb {A}) = \operatorname{Tr} \left[ \left(\mathbb {A} ^ {2}\right) \right] = \mathbb {A}: \mathbb {A} \quad \text { et } \quad I _ {3} (\mathbb {A}) = \operatorname{Tr} \left[ \left(\mathbb {A} ^ {3}\right) \right]\tag{B.16}
$$

## B.2.3 Opérations sur les vecteurs

## Produit scalaire

Le produit scalaire entre deux vecteurs $\vec { V }$ et $\vec { W }$ , noté $\vec { V } \cdot \vec { W }$ , est défini par :

$$
\vec {V} \cdot \vec {W} = V _ {i} W _ {i}\tag{B.17}
$$

— Il correspond au produit contracté simple entre les deux vecteurs $\vec { V }$ et $\vec { W }$ .

— Il est indépendant de la base dans laquelle les vecteurs $\vec { V }$ et $\vec { W }$ sont exprimés.

## Produit vectoriel

Le produit vectoriel entre deux vecteurs $\vec { V }$ et $\vec { W }$ , noté $\vec { V } \wedge \vec { W }$ est défini en dimension 3 par :

$$
\vec {V} \wedge \vec {W} = \epsilon_ {i j k} V _ {j} W _ {k} \vec {e} _ {i} = \left( \begin{array}{c} V _ {1} \\ V _ {2} \\ V _ {3} \end{array} \right) \wedge \left( \begin{array}{c} W _ {1} \\ W _ {2} \\ W _ {3} \end{array} \right) = \left( \begin{array}{c} V _ {2} W _ {3} - V 3 W _ {2} \\ V _ {3} W _ {1} - V 3 W _ {1} \\ V _ {1} W _ {2} - V 1 W _ {2} \end{array} \right)\tag{B.18}
$$

## Produit mixte de trois vecteurs

Le produit mixte de trois vecteurs $\vec { U } , \vec { V }$ et $\vec { W }$ est noté $\vec { U } \wedge \vec { V } ) \cdot \vec { W }$ et est défini par :

$$
\left[ \vec {U}, \vec {V}, \vec {W} \right] = (\vec {U} \wedge \vec {V}) \cdot \vec {W}\tag{B.19}
$$

— Si ce produit mixte est nul, alors les trois vecteurs $\vec { U }$ , $\vec { V }$ et $\vec { W }$ sont coplanaires.

— Il est invariant par permutation circulaire :

$$
\left[ \vec {U}, \vec {V}, \vec {W} \right] = \left[ \vec {V}, \vec {W}, \vec {U} \right] = \left[ \vec {W}, \vec {U}, \vec {V} \right]\tag{B.20}
$$

$$
\left(\vec {U} \wedge \vec {V}\right) \cdot \vec {W} = \left(\vec {V} \wedge \vec {W}\right) \cdot \vec {U} = \left(\vec {W} \wedge \vec {U}\right) \cdot \vec {V}\tag{B.21}
$$

## Déterminant de deux vecteurs

Le déterminant de deux vecteurs $\vec { V }$ et $\vec { W }$ est noté $\operatorname* { d e t } ( { \vec { V } } , { \vec { W } } )$ et est défini par :

$$
\det (\vec {V}, \vec {W}) = \left| \begin{array}{c c} V _ {1} & W _ {1} \\ V _ {2} & W _ {2} \end{array} \right| = V _ {1} W _ {2} - V _ {2} W _ {1} = \left\| \vec {V} \right\| \cdot \left\| \vec {W} \right\| \cdot \sin \theta\tag{B.22}
$$

où $\theta$ représente l’angle orienté formé par les deux vecteurs $\vec { V }$ et $\vec { W }$ . La valeur absolue du déterminant de deux vecteurs correspond à l’aire du parallélogramme défini par ces deux vecteurs.

## Déterminant de trois vecteurs

Le déterminant de trois vecteurs $\vec { U } , \vec { V }$ et $\vec { W }$ est noté det $( \vec { U } , \vec { V } , \vec { W } )$ et est défini par :

$$
\det (\vec {U}, \vec {V}, \vec {W}) = \left| \begin{array}{c c c} U _ {1} & V _ {1} & W _ {1} \\ U _ {2} & V _ {2} & W _ {2} \\ U _ {3} & V _ {3} & W _ {3} \end{array} \right| = U _ {1} \left| \begin{array}{c c} V _ {2} & W _ {2} \\ V _ {3} & W _ {3} \end{array} \right| - U _ {2} \left| \begin{array}{c c} V _ {1} & W _ {1} \\ V _ {3} & W _ {3} \end{array} \right| + U _ {3} \left| \begin{array}{c c} V _ {1} & W _ {1} \\ V _ {2} & W _ {2} \end{array} \right|\tag{B.23}
$$

$$
= U _ {1} \left(V _ {2} W _ {3} - V _ {3} W _ {2}\right) - U _ {2} \left(V _ {1} W _ {3} - V _ {3} W _ {1}\right) + U _ {3} \left(V _ {1} W _ {2} - V _ {2} W _ {1}\right)\tag{B.24}
$$

$$
= U _ {1} V _ {2} W _ {3} - U _ {1} V _ {3} W _ {2} - U _ {2} V _ {1} W _ {3} + U _ {2} V _ {3} W _ {1} + U _ {3} V _ {1} W _ {2} - U _ {3} V _ {2} W _ {1}\tag{B.25}
$$

Il correspond également au produit mixte (en dimension 3) des trois vecteurs $\vec{U}$, $\vec{V}$ et $\vec{W}$, noté $[\vec{U},\vec{V},\vec{W}]=(\vec{U}\wedge\vec{V})\cdot\vec{W}$. La valeur absolue du déterminant de trois vecteurs est égale au volume du parallélépipède défini par ces trois vecteurs.

## B.2.4 Opérations sur les tenseurs

## Trace d’un tenseur d’ordre 2

La trace d’un tenseur du second ordre A est la somme des termes de la diagonale de A. Elle s’écrit :

$$
\operatorname{Tr} (\mathbb {A}) = A _ {i i} \quad \xrightarrow {\text { dimension   3 }} \quad \operatorname{Tr} (\mathbb {A}) = A _ {1 1} + A _ {2 2} + A _ {3 3}\tag{B.26}
$$

## Transposée d’un tenseur d’ordre 2

La transposée d’un tenseur du second ordre A est notée $\mathbb { A } ^ { \top }$ et est définie par :

$$
A _ {i j} ^ {\mathsf {T}} = A _ {j i}\tag{B.27}
$$

## Transposée de l’inverse d’un tenseur d’ordre 2

La transposée de l’inverse d’un tenseur d’ordre 2 est notée $\mathbb { A } ^ { - T }$ et est définie par :

$$
\mathbb {A} ^ {- T} = \left(A ^ {- 1}\right) ^ {\mathsf {T}}\tag{B.28}
$$

## Déterminant d’une matrice ou d’un tenseur d’ordre 2

Le déterminant d’une matrice carrée (ou d’un tenseur d’ordre 2) notée $\mathbb { A } ,$ dont les composantes sont notées $A _ { i j } ,$ , correspond en dimension 3, au déterminant de trois vecteurs $\vec { U } , \vec { V }$ et $\vec { W }$ , dont les composantes sont respectivement $A _ { i 1 } , A _ { i 2 }$ et $A _ { i 3 }$

$$
\det A = \det \left( \begin{array}{c c c} A _ {1 1} & A _ {1 2} & A _ {1 3} \\ A _ {2 1} & A _ {2 2} & A _ {2 3} \\ A _ {3 1} & A _ {3 2} & A _ {3 3} \end{array} \right) = \left| \begin{array}{c c c} A _ {1 1} & A _ {1 2} & A _ {1 3} \\ A _ {2 1} & A _ {2 2} & A _ {2 3} \\ A _ {3 1} & A _ {3 2} & A _ {3 3} \end{array} \right| = \det (\vec {U}, \vec {V}, \vec {W})\tag{B.29}
$$

On peut noter que det $\mathrm { ( A ) = d e t ( A ^ { T } ) }$ .

## B.2.5 Opérations entre vecteurs et/ou tenseurs d’ordre 2

## Produit contracté simple

Le produit contracté simple (matérialisé par le symbole « point central » ·) entre deux tenseurs A et B respectivement d’ordre p et q, donne un tenseur C d’ordre n avec :

$$
\mathbf {C} = \mathbf {A} \cdot \mathbf {B} \quad \Longrightarrow \quad n = p + q - 2\tag{B.30}
$$

En fonction de l’ordre des tenseurs A et B, l’opération diffère :

$$
\vec {A} \cdot \vec {B} = A _ {i} B _ {i} \quad n = 0 \implies \text { scalaire }\tag{B.31}
$$

$$
\mathbb {A} \cdot \vec {B} = \mathbb {A} \vec {B} = A _ {i j} B _ {j} \vec {e _ {i}} \quad n = 1 \implies \text { vecteur }\tag{B.32}
$$

$$
\vec {A} \cdot \mathbb {B} = \vec {A} ^ {\intercal} \mathbb {B} = A _ {i} B _ {i j} \vec {e} _ {j} \quad n = 1 \implies \text { vecteur }\tag{B.33}
$$

$$
\mathbb {A} \cdot \mathbb {B} = \mathbb {A} \mathbb {B} = A _ {i k} B _ {k j} \vec {e} _ {i} \otimes \vec {e} _ {j} \quad n = 2 \implies \text { tenseur   d'ordre } 2\tag{B.34}
$$

Le cas particulier le plus connu étant celui entre deux vecteurs qui n’est autre que le produit scalaire.

## Produit contracté double

Le produit contracté double (matérialisé par le symbole « deux points » :) entre deux tenseurs A et B respectivement d’ordre p et $q$ , donne un tenseur C d’ordre n avec :

$$
\mathbf {C} = \mathbf {A}: \mathbf {B} = \operatorname{Tr} (\mathbf {A} \cdot \mathbf {B}) \quad \Longrightarrow \quad n = p + q - 4\tag{B.35}
$$

En fonction de l’ordre des tenseurs A et B, l’opération diffère :

$$
\mathbb {A}: \mathbb {B} = \operatorname{Tr} (\mathbb {A B}) = A _ {i j} B _ {j i} \quad n = 0 \Rightarrow \text {   scalaire   }\tag{B.36}
$$

$$
\text { si } \mathbb {A} \text { ou } \mathbb {B} \text { symétrique } \quad \mathbb {A}: \mathbb {B} = \operatorname{Tr} (\mathbb {A} \mathbb {B}) = A _ {i j} B _ {i j} \quad n = 0 \implies \text { scalaire }\tag{B.37}
$$

$$
\text { si   } \mathbf {A} \text {   tenseur   d'ordre   4   } \quad \mathbf {A}: \mathbb {B} = \operatorname{Tr} (\mathbf {A B}) = A _ {i j k l} B _ {l k} \quad n = 2 \implies \text {   tenseur   d'ordre   2   }\tag{B.38}
$$

$$
\text { si } \mathbb {B} \text { symétrique } \quad \mathbf {A}: \mathbb {B} = \operatorname{Tr} (\mathbf {A} \mathbb {B}) = A _ {i j k l} B _ {k l} \quad n = 2 \implies \text { tenseur   d'ordre   2 }\tag{B.39}
$$
