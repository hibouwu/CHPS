## Chapitre 2

# Déformations des milieux continus

## 2.1 La notion de déformation

On va introduire ici une première façon de caractériser la déformation d’un milieu continu, en se plaçant en représentation lagrangienne.

L’objectif est de définir des outils mathématiques permettant de caractériser (et si possible de mesurer) la « déformation » d’un milieu continu au cours de son mouvement : variation des distances, des angles, etc. Il s’agit d’un problème difficile auquel nous n’apporterons ici que des réponses partielles mais qui seront suffisantes dans de très nombreuses situations.

## 2.1.1 Gradient de transformation

On a vu qu’il existe une application vectorielle, appelée transformation et notée $\vec { \phi , }$ telle que $\overrightarrow { O M } = \overrightarrow { \phi } ( \overrightarrow { O M _ { 0 } } )$ ). En différenciant cette relation, on obtient :

$$
\mathrm{d} \overrightarrow {O M} = (\overline {{\text { grad }}} \vec {\phi}) \cdot \mathrm{d} \overrightarrow {O M _ {0}} = \mathbb {F} \cdot \mathrm{d} \overrightarrow {O M _ {0}}\tag{2.1}
$$

$$
\text { avec } \quad \mathbb {F} = \frac {\partial \left[ \vec {\phi} (\overrightarrow {O M _ {0}}) \right]}{\partial \overrightarrow {O M _ {0}}} = \frac {\partial \overrightarrow {O M}}{\partial \overrightarrow {O M _ {0}}} = \overline {\overline {{\text { grad }}}}   \vec {\phi}\tag{2.2}
$$

où $\mathbb { F }$ est l’opérateur gradient <sup><a href="#note-1">1</a></sup> de transformation (sans unité). Il est égal à :

— l’identité I en l’absence de déformation ; sans rotation de type corps rigide, mais avec potentiellement une translation de type corps rigide ;

— une isométrie vectorielle directe <sup><a href="#note-2">2</a></sup> en l’absence de déformation mais avec potentiellement une rotation de type corps rigide et/ou une translation de type corps rigide ;

— un opérateur (ou tenseur) symétrique $( \mathbb { F } ^ { \mathsf { T } } = \mathbb { F } )$ en l’absence de rotation.

## 2.1.2 Une mesure de déformation

## Comparaison des longueurs au carré initiale et actuelle

On se place en représentation lagrangienne. On considère deux particules $M$ et $N$ d’un milieu continu et l’on cherche à comparer $\lVert\overrightarrow{MN}\rVert$ à $\lVert\overrightarrow{M_0N_0}\rVert$.


On va se placer uniquement d’un point de vue local, c’est-à-dire que l’on supposera que $N _ { 0 }$ est infiniment proche de $M _ { 0 }$

Calcul préliminaire : On a $\vec { M } = \vec { \phi } ( t , M _ { 0 } )$ et $\vec { N } = \vec { \phi } ( t , N _ { 0 } )$ . Au voisinage de $M _ { 0 }$ , on a donc <sup><a href="#note-3">3</a></sup> :

$$
\vec {N} = \vec {\phi} (t, N _ {0}) = \vec {\phi} (t, M _ {0}) + \underbrace {\frac {\partial \vec {\phi}}{\partial \vec {M} _ {0}} (t , M _ {0})} _ {\text { opérateur   gradient   } \mathbb {F} (t, M _ {0})} \overrightarrow {M _ {0} N _ {0}} + \underbrace {\ldots} _ {\text { termes   négligés }}\tag{2.3}
$$

On en déduit facilement que, au premier ordre :

$$
\overrightarrow {O N} = \overrightarrow {O M} + \mathbb {F} (t, M _ {0}) \overrightarrow {M _ {0} N _ {0}}\tag{2.4}
$$

ce qui donne :

$$
\overrightarrow {M N} = \overrightarrow {M O} + \overrightarrow {O N} = \mathbb {F} (t, M _ {0}) \overrightarrow {M _ {0} N _ {0}}\tag{2.5}
$$

Les longueurs au carré, initiale et actuelle, valent donc :

$$
\left\| \overrightarrow {M N} \right\| ^ {2} = \overrightarrow {M N} ^ {\mathsf {T}} \overrightarrow {M N} = (\mathbb {F} \overrightarrow {M _ {0} N _ {0}}) ^ {\mathsf {T}} \mathbb {F} \overrightarrow {M _ {0} N _ {0}} = \overrightarrow {M _ {0} N _ {0}} ^ {\mathsf {T}} \mathbb {F} ^ {\mathsf {T}} \mathbb {F} \overrightarrow {M _ {0} N _ {0}}\tag{2.6}
$$

$$
\left\| \overrightarrow {M _ {0} N _ {0}} \right\| ^ {2} = \overrightarrow {M _ {0} N _ {0}} ^ {\mathsf {T}} \overrightarrow {M _ {0} N _ {0}} = \overrightarrow {M _ {0} N _ {0}} ^ {\mathsf {T}} \mathbb {I} \overrightarrow {M _ {0} N _ {0}}\tag{2.7}
$$

et donc :

$$
\overrightarrow {M N} ^ {\mathsf {T}} \overrightarrow {M N} - \overrightarrow {M _ {0} N _ {0}} ^ {\mathsf {T}} \overrightarrow {M _ {0} N _ {0}} = \overrightarrow {M _ {0} N _ {0}} ^ {\mathsf {T}} \left[ \mathbb {F} ^ {\mathsf {T}} \mathbb {F} - \mathbb {I} \right] \overrightarrow {M _ {0} N _ {0}}\tag{2.8}
$$

## Opérateur des dilatations de Cauchy-Green droit

Définition 2.1 L’opérateur :

$$
\mathbb {C} (t, M _ {0}) = \mathbb {F} ^ {\mathsf {T}} \mathbb {F}\tag{2.9}
$$

est appelé opérateur (ou tenseur) des dilatations de Cauchy-Green droit (sans unité).

Il possède les propriétés suivantes :

— C est un opérateur symétrique <sup><a href="#note-4">4</a></sup> ;

— les composantes $C _ { i j } \ \forall i = j$ correspondent aux dilatations au carré selon la direction initialement orientée selon $\vec { e _ { i } }$ (c’est-à-dire dans la configuration initiale) ;

— les composantes ${ C _ { i j } } \ \forall i \neq j$ correspondent aux variations d’angles entre les fibres initialement alignées avec les directions des vecteurs $\vec { e _ { i } }$ et $\vec { e } _ { j }$ (initialement orthogonales) ;

$- \ \mathbb { C } = \mathbb { I } \ \forall t , M _ { 0 } \ \Longleftrightarrow$ le milieu continu suit un mouvement de corps rigide.

## Opérateur de déformations Green-Lagrange

Définition 2.2 L’opérateur :

$$
\mathbb {E} (t, M _ {0}) = \frac {1}{2} \left[ \mathbb {F} ^ {\intercal} \mathbb {F} - \mathbb {I} \right] = \frac {1}{2} \left[ \mathbb {C} - \mathbb {I} \right]\tag{2.10}
$$

est appelé opérateur (ou tenseur) des déformations de Green-Lagrange (sans unité).

Il possède les propriétés suivantes :

— E est un opérateur symétrique ;

— les composantes $E _ { i j } \forall i = j$ correspondent aux écarts relatifs des longueurs au carré selon la direction initialement orientée selon $\vec{e}_i$ (c’est-à-dire dans la configuration initiale) ;

— les composantes $E _ { i j } \ \forall i \neq j$ correspondent aux variations d’angles entre les fibres initialement alignées avec les directions des vecteurs $\vec { e _ { i } }$ et $\vec { e } _ { j }$ (initialement orthogonales) ;

$- \ \mathbb { E } = \mathbb { O } \ \forall t , M _ { 0 } \ \Longleftrightarrow$ le milieu continu suit un mouvement de corps rigide.

## 2.1.3 Hypothèse des Petites Perturbations (HPP)

Introduisons comme nouvelle grandeur le déplacement $\vec { u } ( t , M _ { 0 } ) = \overrightarrow { M _ { 0 } M } ( t )$ . Ce champ vectoriel est continu à tout instant t et pour tout point $M _ { 0 } \in \Omega _ { 0 }$ . On a donc :

$$
\begin{array}{c} \vec {M} (t) = \vec {M} _ {0} + \vec {u} (t, M _ {0}) \\ \mathbb {F} (t, M _ {0}) = \mathbb {I} + \frac {\partial \vec {u}}{\partial M _ {0}} (t, M _ {0}) = \mathbb {I} + \overline {{\overline {{\operatorname{grad}}}}} \vec {u} = \mathbb {I} + \nabla \vec {u} \\ \mathbb {E} (t, M _ {0}) = \frac {1}{2} \left[ \frac {\partial \vec {u}}{\partial M _ {0}} + \left(\frac {\partial \vec {u}}{\partial M _ {0}}\right) ^ {\mathsf {T}} + \left(\frac {\partial \vec {u}}{\partial M _ {0}}\right) ^ {\mathsf {T}} \frac {\partial \vec {u}}{\partial M _ {0}} \right] \\ \mathbb {E} (t, M _ {0}) = \frac {1}{2} \left[ \overline {{\overline {{\operatorname{grad}}}}} \vec {u} + (\overline {{\overline {{\operatorname{grad}}}}} \vec {u}) ^ {\mathsf {T}} + (\overline {{\overline {{\operatorname{grad}}}}} \vec {u}) ^ {\mathsf {T}} \overline {{\overline {{\operatorname{grad}}}}} \vec {u} \right] \\ \mathbb {E} (t, M _ {0}) = \frac {1}{2} \left[ \nabla \vec {u} + (\nabla \vec {u}) ^ {\mathsf {T}} + (\nabla \vec {u}) ^ {\mathsf {T}} \nabla \vec {u} \right] \end{array}\tag{2.11}
$$

On peut linéariser $\mathbb { E }$ en négligeant le dernier terme sous l’Hypothèse des Petites Perturbations (HPP), qui regroupe deux sous-hypothèses :

— les déplacements sont « petits » (ou infinitésimaux) par rapport aux dimensions du domaine $\Omega _ { 0 }$ , soit $\| { \vec { u } } \| \ll \mathsf { d i a m e t r e } ( \Omega _ { 0 } )$ , ce qui indique que les configurations initiale $\Omega _ { 0 }$ et courante $\Omega ( t )$ peuvent être confondues ;

— les transformations sont « petites » (ou infinitésimales), soit $\left\| { \overline { { \overline { { \mathrm { g r a d } } } } } } \vec { u } \right\| \ll 1$ où $\| \mathbb { A } \|$ s’interprète ici comme la norme « infini » $\left. \mathbb { A } \right. = \operatorname* { m a x } _ { i , j } \left| A _ { i j } \right|$

Remarque 2.1 L’hypothèse de petites transformations (ou transformations infinitésimales) elle-même implique que :

— les déformations sont petites (ou infinitésimales) : $\| \mathbb { E } \| \ll 1$

— les rotations sont petites (ou infinitésimales) $: \ \| \omega \| \ \ll 1$ (ω correspond à la partie antisymétrique de grad $\vec{u}$).

Néanmoins, comme il s’agit d’une implication, et non d’une équivalence, la réciproque est donc fausse. C’est-à-dire que « petites déformations » n’implique pas forcément « petites transformations ».

On obtient ainsi la déformation linéarisée, exprimée par son tenseur $\varepsilon$ (sans unité) :

$$
\varepsilon (t, M _ {0}) = \frac {1}{2} \left[ \frac {\partial \vec {u}}{\partial M _ {0}} + \left(\frac {\partial \vec {u}}{\partial M _ {0}}\right) ^ {\mathsf {T}} \right] = \frac {1}{2} \left[ \overline {{\overline {{\mathrm{grad}}}}}   \vec {u} + \left(\overline {{\overline {{\mathrm{grad}}}}}   \vec {u}\right) ^ {\mathsf {T}} \right] = \frac {1}{2} \left[ \nabla   \vec {u} + (\nabla   \vec {u}) ^ {\mathsf {T}} \right]\tag{2.12}
$$

## Expression en coordonnées cartésiennes

On se place dans une base orthonormée $\boldsymbol { B } = \left( \vec { e } _ { 1 } , \vec { e } _ { 2 } , \vec { e } _ { 3 } \right)$ . On pose :

$$
\vec {u} (t, M _ {0}) = u _ {1} (t, M _ {0}) \vec {e} _ {1} + u _ {2} (t, M _ {0}) \vec {e} _ {2} + u _ {3} (t, M _ {0}) \vec {e} _ {3}\tag{2.13}
$$

ou encore en notation matricielle :

$$
\vec {u} = \left[ \begin{array}{c} u _ {1} \\ u _ {2} \\ u _ {3} \end{array} \right] _ {(\vec {e} _ {1}, \vec {e} _ {2}, \vec {e} _ {3})}\tag{2.14}
$$

On utilisera aussi la notation $\frac { \partial \bullet } { \partial X _ { i } } = \bullet _ { , i }$ pour désigner la dérivation partielle par rapport à la i<sup>e</sup> coordonnée de $M _ { 0 }$ . On a (avec des notations évidentes <sup><a href="#note-5">5</a></sup>) :

$$
\begin{array}{c} {x _ {i} = X _ {i} + u _ {i} (t, X _ {1}, X _ {2}, X _ {3})} \\ {F _ {i j} = \delta_ {i j} + u _ {i, j}} \\ {E _ {i j} = \frac {1}{2} \left[ u _ {i, j} + u _ {j, i} + \sum_ {k = 1} ^ {3} u _ {k, i} u _ {k, j} \right]} \end{array}\tag{2.15}
$$

Quant à la déformation linéarisée, on l’obtient en négligeant le dernier terme :

$$
\varepsilon_ {i j} = \frac {1}{2} [ u _ {i, j} + u _ {j, i} ]\tag{2.16}
$$

Lorsqu’on est dans le cadre HPP, on parle souvent de « déformation de l’ingénieur », il s’agit d’une vision simplifiée. Cette déformation correspond aux valeurs diagonales du tenseur de déformation linéarisé $\varepsilon$, correspondant aux différentes directions. Cela s’interprète comme la variation relative de longueur.

$$
\varepsilon = \frac {\Delta L}{L _ {0}} = \frac {L - L _ {0}}{L _ {0}}
$$

## Compatibilité des déformations

Le champ de déformation linéarisé $\varepsilon$ dérivant du champ de déplacement ${ \vec { u } } ,$ lui-même continu, sa forme est cadrée. La continuité du champ de déformation est assurée par un jeu d’équations appelées « équations de compatibilité » (des déformations) :

$$
\operatorname{rot} \left(\operatorname{rot} \varepsilon^ {\mathsf {T}}\right) = \mathbb {O} \qquad \Longleftrightarrow \qquad \omega_ {i j, k l} = \omega_ {i j, l k} \qquad \qquad \text {avec} \quad \omega_ {i j, k} = \varepsilon_ {i k, j} - \varepsilon_ {j k, i}\tag{2.17}
$$

$$
\text { soit } \quad \boxed {\varepsilon_ {i k, j l} - \varepsilon_ {j k, i l} = \varepsilon_ {i l, j k} - \varepsilon_ {j l, i k}}\tag{2.18}
$$

$$
\text { ou   encore } \quad \varepsilon_ {i k, j l} + \varepsilon_ {j l, i k} = \varepsilon_ {i l, j k} + \varepsilon_ {j k, i l}\tag{2.19}
$$

$$
\text { ou   encore } \quad \varepsilon_ {i j, k l} + \varepsilon_ {k l, i j} = \varepsilon_ {i k, j l} + \varepsilon_ {j l, i k}\tag{2.20}
$$

## 2.1.4 Aspects pratiques sur les déformations

## Ordre de grandeur des déformations

Une courbe de traction classique est présentée en figure 2.1, avec les domaines de déformation élastique et irréversible (plastique). À cela s’ajoute quelques ordres de grandeurs :

![image](Images/IMMC_CM_Chap2_2025-2026_01.jpg)


Figure 2.1 – Courbe de traction classique pour un matériau de type acier ductile (en trait plein) et de type fragile (pointillé).


— élasticité pour les aciers : $10^{-4}$ à $10^{-2}$ (soit 0,01 % à 1 %) ;

— plasticité pour les aciers : $10^{-2}$ à $10^{-1}$ (soit 1 % à 10 %) ;

— mise en forme des aciers : $1 0 ^ { - 1 }$ ou plus (soit 10 % ou plus) ;

— béton en compression à la rupture : $1 0 ^ { - 3 }$ (soit 0,1 %).

## Méthodes expérimentales de mesure des déformations

— méthode des grilles (cf. figure 2.2) : on a $E _ { 1 1 } = \frac { 1 } { 2 } \left[ \frac { \delta a ^ { 2 } } { \delta a _ { 0 } ^ { 2 } } - 1 \right]$ et $E _ { 1 2 } = \frac { 1 } { 2 } \frac { \delta a \cdot \delta b } { \delta a _ { 0 } \cdot \delta b _ { 0 } } \cos \alpha$

— capteur de déplacement ;

— jauges de déformation ;

— corrélation d’images 2D (mesure du champ de déplacement (discret) puis calcul du gradient) ;

— diffraction des rayons X ;

— etc

![image](Images/IMMC_CM_Chap2_2025-2026_02.jpg)


Figure 2.2 – Principe de la méthode des grilles


## Quelques mouvements de base

![image](Images/IMMC_CM_Chap2_2025-2026_03.jpg)


(a) Translation uniforme, ici d’un vecteur $\vec { d } .$


![image](Images/IMMC_CM_Chap2_2025-2026_04.jpg)


(b) Rotation uniforme, ici de centre C et d’angle α.


![image](Images/IMMC_CM_Chap2_2025-2026_05.jpg)


(c) Glissement simple, ici d’angle γ.


![image](Images/IMMC_CM_Chap2_2025-2026_06.jpg)

(d) Glissement pur, ici d’angle $\gamma$.

![image](Images/IMMC_CM_Chap2_2025-2026_07.jpg)

(e) Dilatation isotrope $(\lambda_1=\lambda_2)$.

![image](Images/IMMC_CM_Chap2_2025-2026_08.jpg)


(f) Dilatation anisotrope $( \lambda _ { 1 } = 1 , 5 \lambda _ { 2 } )$


Figure 2.3 – Description schématique de mouvements particuliers.


## 2.2 Le taux de déformation

On va introduire ici une autre façon de caractériser la « déformation » d’un milieu continu en se plaçant en représentation eulérienne, c’est-à-dire sans configuration de référence particulière.

## 2.2.1 Gradient du champ de vitesse

On se place toujours d’un point de vue local au voisinage d’un point M et à un instant t donné. Pour un point N voisin de M, en développant au premier ordre, on a :

$$
\vec {V} (t, N) = \vec {V} (t, M) + \underbrace {\frac {\partial \vec {V}}{\partial \vec {M}} (t , M)} _ {\text { gradient   de   la   vitesse }} \overrightarrow {M N} + \underbrace {\ldots} _ {\text { termes   négligés }}\tag{2.21}
$$

L’opérateur $\textstyle { \frac { \partial { \vec { V } } } { \partial M } } ( t , M )$ est le gradient eulérien <sup><a href="#note-6">6</a></sup> du champ de vitesse en M et à l’instant t.

Usuellement, on décompose le gradient en la somme de sa partie symétrique et de sa partie antisymétrique :

$$
\frac {\partial \vec {V}}{\partial \vec {M}} (t, M) = \mathbb {D} (t, M) + \boldsymbol{\Omega} (t, M)\tag{2.22}
$$

$$
\mathbb {D} (t, M) = \frac {1}{2} \left[ \frac {\partial \vec {V}}{\partial M} (t, M) + \left(\frac {\partial \vec {V}}{\partial M} (t, M)\right) ^ {\mathsf {T}} \right]\tag{2.23}
$$

matrice symétrique


$$
\boldsymbol{\Omega} (t, M) = \frac {1}{2} \left[ \frac {\partial \vec {V}}{\partial M} (t, M) - \left(\frac {\partial \vec {V}}{\partial M} (t, M)\right) ^ {\mathsf {T}} \right] \begin{array}{l} \text {matrice antisymétrique} \\ \text {(diagonale nulle, termes hors-} \\ \text {diagonale opposés)} \end{array}\tag{2.24}
$$

avec, par exemple :

$$
\boldsymbol{\Omega} = \left[ \begin{array}{c c c} 0 & - \omega_ {3} & \omega_ {2} \\ \omega_ {3} & 0 & - \omega_ {1} \\ - \omega_ {2} & \omega_ {1} & 0 \end{array} \right] \qquad \text { avec } \qquad \left\{ \begin{array}{l} \omega_ {k} = \omega_ {k} (t, M) = - \frac {1}{2} \varepsilon_ {i j k} \Omega_ {i j} \\ \Omega_ {i j} = - \varepsilon_ {i j k} \omega_ {k} \end{array} \right.\tag{2.25}
$$

où $\vec { \omega }$ est le vecteur taux de rotation et $\varepsilon _ { i j k }$ est le symbole de Levi-Civita (cf. annexe B).

## 2.2.2 Cas d’un corps rigide

Si le voisinage de M a, par rapport au repère $\mathcal { R }$ , un mouvement de corps rigide, on a :

$$
\vec {V} (t, N) = \vec {V} (t, M) + \vec {\omega} (t) \wedge \overrightarrow {M (t) N (t)}\tag{2.26}
$$

Si M et N sont suffisamment proches :

$$
\overrightarrow {M N} = \mathrm{d} \vec {M} \quad \Rightarrow \quad \frac {\mathrm{d} \overrightarrow {M N}}{\mathrm{d} t} = \frac {\mathrm{d}}{\mathrm{d} t} (\mathrm{d} \vec {M}) \stackrel {{\text { Th. de Schwarz }}} {{=}} \mathrm{d} \vec {V} (t, M)\tag{2.27}
$$

Or :

$$
\frac {\mathrm{d} \overrightarrow {M N}}{\mathrm{d} t} = \frac {\mathrm{d} \overrightarrow {M O}}{\mathrm{d} t} + \frac {\mathrm{d} \overrightarrow {O N}}{\mathrm{d} t} = - \vec {V} (t, M) + \vec {V} (t, N) \quad \stackrel {(2. 2 6)} {\Longrightarrow} \quad \frac {\mathrm{d} \overrightarrow {M N}}{\mathrm{d} t} = \vec {\omega} (t) \wedge \overrightarrow {M (t) N (t)}\tag{2.28}
$$

Soit :

$$
\mathrm{d} \vec {V} (t, M) = \vec {\omega} (t) \wedge \overrightarrow {M (t) N (t)} = \vec {\omega} (t) \wedge \mathrm{d} \vec {M}\tag{2.29}
$$

Et donc :

$$
\mathrm{d} \vec {V} (t, M) = \vec {\omega} (t) \wedge \mathrm{d} \vec {M} \qquad \text {soit} \qquad \frac {\partial \vec {V}}{\partial M} (t, M) = \overline {{\overline {{\operatorname{grad}}} _ {M}}}   \vec {V} (t, M) = \vec {\omega} (t) \wedge\tag{2.30}
$$

Le gradient de vitesse se décomposant en partie symétrique D et anti-symétrique Ω, on en déduit :

$$
\mathbb {D} (t, M) = 0 \quad \text { et } \quad \boldsymbol{\Omega} (t, M) = \vec {\omega} (t) \wedge\tag{2.31}
$$

## 2.2.3 Définition du taux de déformation et taux de rotation

Définition 2.3 L’opérateur D, partie symétrique du gradient des vitesses, est appelé opérateur taux de déformation en M à l’instant t, exprimé en s<sup>−1</sup>.

$$
\mathbb {D} (t, M) = \frac {1}{2} \left[ \frac {\partial \vec {V}}{\partial M} (t, M) + \left(\frac {\partial \vec {V}}{\partial M} (t, M)\right) ^ {\mathsf {T}} \right] = \frac {1}{2} \left[ \overline {{\overline {{\operatorname{grad}}}}} \vec {V} + \left(\overline {{\overline {{\operatorname{grad}}}}} \vec {V}\right) ^ {\mathsf {T}} \right]\tag{2.32}
$$

Lien avec le gradient de la transformation

$$
\frac {\partial \vec {V}}{\partial M} = \dot {\mathbb {F}} \mathbb {F} ^ {- 1}; \mathbb {D} = \frac {1}{2} \left[ \dot {\mathbb {F}} \mathbb {F} ^ {- 1} + \mathbb {F} ^ {- T} \dot {\mathbb {F}} ^ {\intercal} \right]; \dot {\mathbb {E}} = \mathbb {F} ^ {\intercal} \mathbb {D} \mathbb {F}\tag{2.33}
$$

Lien avec les mouvements de corps rigide

Si, à un instant t, on a $\mathbb { D } = 0$ en tout point M de $\Omega ( t )$ , alors le champ des vitesses est un torseur, c’est-à-dire un champ de la forme :

$$
\vec {V} (t, M) = \vec {A} (t) + \vec {\omega} (t) \wedge \overrightarrow {O M}\tag{2.34}
$$

Si cette propriété est vraie pour tout t (ou seulement sur un intervalle de temps $[ t _ { 1 } , t _ { 2 } ] )$ , alors le milieu continu a un mouvement de corps rigide (éventuellement seulement sur cet intervalle de temps $[ t _ { 1 } , t _ { 2 } ] )$

Remarque 2.2 On peut montrer que :

$$
\vec {\omega} = \frac {1}{2} \overrightarrow {\mathrm{rot}} \vec {V} (M)\tag{2.35}
$$

Définition 2.4 L’opérateur Ω, partie anti-symétrique du gradient des vitesses, est appelé opérateur taux de rotation en M à l’instant t.

$$
\boldsymbol{\Omega} (t, M) = \frac {1}{2} \left[ \frac {\partial \vec {V}}{\partial M} (t, M) - \left(\frac {\partial \vec {V}}{\partial M} (t, M)\right) ^ {\mathsf {T}} \right] = \frac {1}{2} \left[ \overline {{\overline {{\mathrm{grad}}}}} \vec {V} - \left(\overline {{\overline {{\mathrm{grad}}}}} \vec {V}\right) ^ {\mathsf {T}} \right]\tag{2.36}
$$

## 2.2.4 Écoulements particuliers

Incompressible un écoulement est dit incompressible SSI :

$$
\operatorname{div} ^ {E} \vec {V} = \operatorname{Tr} \left(\overline {{\overline {{\operatorname{grad}}}}} ^ {E} \vec {V}\right) = \operatorname{Tr} \mathbb {D} = 0
$$

Stationnaire un écoulement est dit stationnaire (ou permanent) SSI son champ de vitesse eulérien est indépendant du temps t :

$$
\frac {\partial^ {E} \vec {V}}{\partial t} = \vec {0}
$$

Irrotationnel un écoulement est dit irrotationnel SSI :

$$
\overrightarrow {\mathrm{rot}} ^ {E} \vec {V} = 0
$$

Laminaire un écoulement est dit laminaire en l’absence de turbulence, lorsque le fluide l’écoule par couches qui glissent les unes par rapport aux autres (sans se croiser) et épouse les formes des solides autour desquels il s’écoule. On fait très souvent la simplification abusive selon laquelle : écoulement laminaire $\implies \overline { { \overrightarrow { \mathrm { g r a d } } } } \overrightarrow { V } \cdot \overrightarrow { V }$ négligeable

Rampant un écoulement est dit rampant lorsqu’il est pénible, difficile à mettre en mouvement et facile à arrêter, si bien qu’on peut complètement négliger les effets des forces d’inertie, notamment ceux générés par le terme convectif grad $\vec { V } \cdot \vec { V }$

## Notes

<a id="note-1"></a>

**1.** En coordonnées cartésiennes orthonormées, l’opérateur gradient lagrangien est représenté par une matrice $3 \times 3$ dont les éléments sont les dérivées partielles : $\partial\bullet/\partial X_j$.

<a id="note-2"></a>

**2.** Une isométrie vectorielle directe (ou positive) correspond à un opérateur orthogonal ou autrement dit, une matrice de rotation. Si tel est le cas pour $\mathbb{F}$, on a $\mathbb{F}^{\mathsf{T}}\mathbb{F}=\mathbb{I}$ et $\det\mathbb{F}=1$.

<a id="note-3"></a>

**3.** Cette formule est analogue à la formule des accroissements finis.

<a id="note-4"></a>

**4.** Dans une base orthonormée, la matrice d’un opérateur symétrique est une matrice symétrique (i.e. égale à sa transposée).

<a id="note-5"></a>

**5.** $\delta_{ij}$ est l’élément $(i,j)$ de la matrice identité : $\delta_{ij}=0$ si $i\ne j$ et $\delta_{ij}=1$ si $i=j$.

<a id="note-6"></a>

**6.** En coordonnées cartésiennes orthonormées l’opérateur gradient est représenté par une matrice $3 \times 3$ dont les éléments sont les dérivées partielles : $\partial\bullet/\partial x_j$.
