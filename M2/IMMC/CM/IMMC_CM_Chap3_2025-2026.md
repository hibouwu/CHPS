## Chapitre 3

# Schématisation des efforts intérieurs – Notion de contrainte

Dans le cadre de la mécanique des systèmes de solides rigides, il n’est pas utile de sché- matiser les efforts intérieurs à chaque solide (appelés aussi efforts de cohésion). En Mécanique des Milieux Continus déformables, cette impasse n’est plus possible. L’objet de ce chapitre est d’introduire une schématisation précise de ces efforts intérieurs.

## 3.1 Rappels sur la schématisation des efforts extérieurs

## 3.1.1 Notion de torseur

Définition 3.1 Un torseur est par définition un champ de vecteur $M \mapsto { \vec { H } } ( M )$ équiprojectif, c’est-à-dire tel que :

$$
\forall M, \forall N: \vec {H} (M) \cdot \overrightarrow {M N} = \vec {H} (N) \cdot \overrightarrow {M N}\tag{3.1}
$$

On démontre alors qu’il existe un unique vecteur ${ \vec { R } } ,$ appelé résultante du torseur, tel que :

$$
\forall M, \forall N: \vec {H} (N) = \vec {H} (M) + \vec {R} \wedge \overrightarrow {M N}\tag{3.2}
$$

Le vecteur $\vec { H } ( M )$ est aussi appelé moment en M du torseur.

Un torseur est entièrement déterminé par la donnée de sa résultante et de son moment en un point M : ces deux vecteurs constituent les éléments de réduction en M du torseur.

$$
\left\{ \begin{array}{c} \vec {R} \\ \vec {H} (M) \end{array} \right\} _ {M}
$$

Les opérations classiques (c’est-à-dire addition, soustraction, égalité, etc) portant sur deux torseurs $\mathcal { T } _ { 1 }$ et $\mathcal { T } _ { 2 }$ consistent à effectuer ces mêmes opérations sur leurs éléments de réduction, exprimés au même point. Par exemple :

$$
\mathcal {T} _ {1} + \mathcal {T} _ {2} = \left\{ \begin{array}{c} \vec {R} _ {1} + \vec {R} _ {2} \\ \vec {H} _ {1} (A) + \vec {H} _ {2} (A) \end{array} \right\} _ {A} = \left\{ \begin{array}{c} \vec {R} _ {1} + \vec {R} _ {2} \\ \vec {H} _ {1} (A) + \vec {H} _ {2} (B) + \vec {R} _ {2} \wedge \overrightarrow {B A} \end{array} \right\} _ {A}\tag{3.3}
$$

Définition 3.2 Un glisseur est un torseur pour lequel il existe au moins un point A où le moment est nul. Le moment est alors nul en tout point de la droite $( A , { \vec { R } } )$ si la résultante est non nulle et en tout point de l’espace si elle est nulle (dans ce cas, le torseur est le torseur nul).

## 3.1.2 Cas d’un point matériel

Soit M un point matériel de masse m. Les effets de l’environnement extérieur sur M peuvent très souvent être schématisés par une unique « force appliquée en M » c’est-à-dire de façon précise par un torseur (glisseur) dont les éléments de réduction en M sont :

— résultante $\vec { F }$ ;

— moment nul ${ \vec { 0 } } .$

Si le repère $\mathcal { R }$ est galiléen <sup><a href="#note-1">1</a></sup>, le principe fondamental de la dynamique (PFD) donne :

$$
m \frac {\mathrm{d} ^ {2} \overrightarrow {O M}}{\mathrm{d} t ^ {2}} = \vec {F}\tag{3.4}
$$

## 3.1.3 Cas d’un corps rigide Σ

Sur un corps rigide, les effets de l’environnement extérieur sont généralement schématisés par les trois types d’efforts décrits ci-dessous.

## Efforts volumiques

Certains efforts peuvent être schématisés par la donnée dans Σ (ou sur une partie volumique de Σ) d’une densité volumique d’effort $M \mapsto { \vec { f _ { v } } } ( M )$ . Le torseur associé à ce type d’effort a pour éléments de réduction en un point quelconque A :

$$
\left\{ \begin{array}{c} \vec {R} = \int_ {\Sigma} \vec {f _ {v}} (M) \mathrm{d} V \\ \vec {H} (A) = \int_ {\Sigma} \overrightarrow {A M} \wedge \vec {f _ {v}} (M) \mathrm{d} V \end{array} \right\} _ {A} \quad \text { exprimés   en } \quad \left\{ \begin{array}{c} N \\ N \cdot m \end{array} \right\}\tag{3.5}
$$

Par exemple, les efforts de pesanteur sont de ce type. La densité volumique d’effort $\vec { f } _ { v }$ s’exprime en $\mathsf { N } \cdot \mathsf { m } ^ { - 3 }$

## Efforts surfaciques

Certains efforts peuvent être schématisés par la donnée, sur la frontière ∂Σ (ou sur une partie de la frontière) d’une densité surfacique de force $M \mapsto { \vec { T } } ( M )$ . Le torseur associé à ce type d’effort a pour éléments de réduction en un point quelconque A :

$$
\left\{ \begin{array}{c} \vec {R} = \int_ {\partial \Sigma} \vec {T} (M) \mathrm{d} S \\ \vec {H} (A) = \int_ {\partial \Sigma} \overrightarrow {A M} \wedge \vec {T} (M) \mathrm{d} S \end{array} \right\} _ {A} \qquad \text {exprimés en} \qquad \left\{ \begin{array}{c} N \\ N \cdot m \end{array} \right\}\tag{3.6}
$$

Par exemple, les efforts (de type pression) exercés par un fluide sur un solide sont de ce type. La densité surfacique d’effort $\vec { T }$ s’exprime en $\mathsf { N } \cdot \mathsf { m } ^ { - 2 }$

## Efforts concentrés

En un point C d’un solide, on se donne une force $\vec { F }$ et un moment $\vec { H } ( C )$ . Le torseur associé a alors pour éléments de réduction en C :

$$
\left\{ \begin{array}{c} \vec {F} \\ \vec {H} (C) \end{array} \right\} _ {C} \qquad \text { exprimés   en } \qquad \left\{ \begin{array}{c} N \\ N \cdot m \end{array} \right\}\tag{3.7}
$$

## Rappel du PFD pour un solide

Si le repère R est galiléen, le principe fondamental de la dynamique appliqué à Σ donne :

Torseur dynamique de Σ = Torseur des efforts extérieurs appliqués à Σ

c’est-à-dire, pour les types d’efforts considérés ici :

$$
\int_\Sigma \rho\vec{\Gamma}(M/\mathcal{R})\,\mathrm{d}V
=\int_\Sigma\vec{f}_v(M)\,\mathrm{d}V+\int_{\partial\Sigma}\vec{T}(M)\,\mathrm{d}S+\vec{F}\tag{3.8}
$$

$$
\begin{aligned}
\int_\Sigma\overrightarrow{AM}\wedge\rho\vec{\Gamma}(M/\mathcal{R})\,\mathrm{d}V
&=\int_\Sigma\overrightarrow{AM}\wedge\vec{f}_v(M)\,\mathrm{d}V\\
&\quad+\int_{\partial\Sigma}\overrightarrow{AM}\wedge\vec{T}(M)\,\mathrm{d}S
+\bigl(\vec{H}(C)+\overrightarrow{AC}\wedge\vec{F}\bigr)
\end{aligned}\tag{3.9}
$$


où $\rho$ désigne la masse volumique <sup><a href="#note-2">2</a></sup>, le plus souvent exprimée en kg · m<sup>−3</sup>.

## 3.1.4 Cas d’un milieu continu

Pour décrire les effets de l’environnement extérieur sur un milieu continu Ω, nous utiliserons principalement deux types de schématisations :

— des efforts surfaciques schématisés par la donnée, sur la frontière ∂Ω (ou sur une partie de la frontière), d’une densité surfacique de force $M \mapsto { \vec { T } } ( M )$ . Ces efforts sont, selon les cas, donnés ou inconnus. Lorsqu’ils sont donnés, on les notera $\vec { T _ { d } }$

— des efforts volumiques schématisés par la donnée dans Ω (ou sur une partie volumique de Ω) d’une densité volumique d’effort $M \mapsto { \vec { f _ { v } } } ( M )$ . En général, ces efforts sont des données du problème. On les notera alors $\vec { f } _ { d }$

Remarque 3.1 Au moins dans un premier temps, nous exclurons la possibilité des efforts concentrés appliqués sur un milieu continu. La prise en compte de tels efforts conduit le plus souvent à des difficultés mathématiques hors du programme. Néanmoins, dans le cas particulier des milieux de type « poutre », ce type d’effort peut être pris en compte.

Remarque 3.2 On se limitera ici à l’étude des milieux classiques dits « de Cauchy » pour lesquels aucune densité volumique de moments n’est introduite. Des modèles plus fins, et plus complexes, sont aussi disponibles, mais hors du cadre de ce cours.

## 3.2 Schématisation des efforts intérieurs

## 3.2.1 Hypothèses de base

Considérons une partie Σ de Ω de frontière ∂Σ intérieur à Ω (cf. figure 3.1). On va schématiser les efforts intérieurs à Ω en schématisant les efforts de la partie $\Omega - \Sigma$ sur la partie Σ. On fait les deux hypothèses suivantes :

— les efforts de $\Omega - \Sigma$ sur Σ sont uniquement des efforts surfaciques définis sur $\partial \Sigma$ par une densité surfacique d’efforts $\vec { T }$

— on suppose que, en un point M donné de $\partial \Sigma$ , la densité $\vec { T }$ ne dépend que de l’orientation de l’élément de surface de ∂Σ en M et donc que $\vec { T }$ ne dépend que du vecteur normal extérieur unité $\vec { n } ( M )$ en M à ∂Σ :

$$
\vec {T} = \vec {T} (M, \vec {n} (M))\tag{3.10}
$$

![image](Images/IMMC_CM_Chap3_2025-2026_01.jpg)


Figure 3.1 – Schématisation des efforts intérieurs


## 3.2.2 Opérateur des contraintes

## Théorème fondamental (Cauchy)

Théorème 3.1 Il existe un opérateur linéaire $\sigma$ aussi appelé tenseur des contraintes de Cauchy, défini en tout point M de Ω, tel que :

$$
\vec {T} (M, \vec {n}) = \sigma (M) \vec {n} = \sigma (M) \cdot \vec {n}\tag{3.11}
$$

Définition 3.3 L’opérateur $\sigma ( M )$ est appelé opérateur des contraintes au point M.

Définition 3.4 Le vecteur $\vec { T } ( M , \vec { n } )$ est appelé vecteur contrainte en M dans la direction ${ \vec { n } } .$

## Symétrie de l’opérateur des contraintes

L’opérateur $\sigma ( M )$ est symétrique : $\boldsymbol { \sigma } ( M ) = [ \sigma ( M ) ] ^ { \boldsymbol { \mathsf { T } } }$

## 3.2.3 Étude de l’opérateur des contraintes en un point

## Dimension physique

Les composantes de $\sigma$ ont la dimension d’une pression : force par unité de surface. L’unité de mesure est donc le Pascal $( \mathsf { P a } )$ ou les unités dérivées : MPa, GPa. Cela correspond à des $\mathsf { N } \cdot \mathsf { m } ^ { - 2 }$ . Physiquement, la force élémentaire exercée par Ω−Σ sur $\Sigma$ sur un élément de surface dS est :

$$
\mathrm{d} \vec {f} = \sigma \vec {n} \mathrm{d} S = \sigma \cdot \vec {n} \mathrm{d} S\tag{3.12}
$$

A titre d’exemples, voici quelques ordres de grandeurs :

— la pression atmosphérique : $p _ { a } = 1 { \sf a t m } = 1 , 0 1 3 2 5 { \sf b a r } = 1 0 1 3 2 5 { \sf P a } \approx 0 ,$ 1 MPa

— pneu de vélo de course : $p \approx 6$ bar à 10 bar

— limite élastique d’un acier doux : 200 MPa à 250 MPa

## Contrainte normale – Contrainte tangentielle

Définition 3.5 On appelle contrainte normale dans la direction $\vec { n }$ la projection du vecteur contrainte sur $\vec{n}$ (figure 3.2) :

$$
\vec {T} _ {n} = T _ {n} \vec {n} = (\vec {n} ^ {\mathsf {T}} \sigma \vec {n}) \vec {n} = (\vec {n} \cdot \sigma \cdot \vec {n}) \vec {n}\tag{3.13}
$$

Définition 3.6 On appelle contrainte tangentielle dans la direction $\vec{n}$ la projection du vecteur contrainte sur le plan orthogonal à $\vec{n}$ (figure 3.2) :

$$
\vec {T} _ {t} = \sigma \vec {n} - \vec {T} _ {n} = \sigma \cdot \vec {n} - \vec {T} _ {n}\tag{3.14}
$$

![image](Images/IMMC_CM_Chap3_2025-2026_02.jpg)


Figure 3.2 – Contrainte normale et contrainte tangentielle


Remarque 3.3 On utilise aussi pour le couple contraintes normale et tangentielle $( T _ { n } , T _ { t } )$ parfois les notations $\left( \sigma _ { n } , \sigma _ { t } \right)$ ou $( \sigma , \tau )$

Remarque 3.4 On utilise aussi parfois le terme « contrainte de cisaillement » ou « cisaillement » à la place de contrainte tangentielle.

## Réciprocité des contraintes

On a, pour toutes directions $\vec { n } _ { 1 }$ et $\vec { n } _ { 2 }$ :

$$
\vec {n} _ {2} ^ {\mathsf {T}} \sigma \vec {n} _ {1} = \vec {n} _ {1} ^ {\mathsf {T}} \sigma \vec {n} _ {2} \quad \Longleftrightarrow \quad \vec {n} _ {2} \cdot \sigma \cdot \vec {n} _ {1} = \vec {n} _ {1} \cdot \sigma \cdot \vec {n} _ {2}\tag{3.15}
$$

## Partie sphérique et déviateur des contraintes

On peut décomposer le tenseur des contraintes (comme tout autre tenseur) en parties sphérique et déviatorique, ce qui constitue une base tensorielle.

La partie sphérique des contraintes $\sigma ^ { S }$ , correspondant au $3 ^ { \mathsf { e } }$ invariant de ce tenseur, reliée à la pression hydrostatique $p ,$ est définie par :

$$
\sigma^ {S} = \operatorname{sphe} (\sigma) = \frac {1}{3} \operatorname{Tr} (\sigma) \mathbb {I} = - p \mathbb {I} \quad \Longrightarrow \quad p = - \frac {\operatorname{Tr} (\sigma)}{3}\tag{3.16}
$$

La partie déviatorique, ou plus communément le déviateur des contraintes, noté $\sigma ^ { D }$ , est défini par :

$$
\sigma^ {D} = \mathrm{dev} (\sigma) = \sigma - \frac {1}{3} \mathrm{Tr} (\sigma) \mathbb {I}\tag{3.17}
$$

Il vérifie $\mathrm { T r } ( \sigma ^ { D } ) = 0$

## Directions principales – Contraintes principales

Définition 3.7 On appelle direction principale <sup><a href="#note-3">3</a></sup> de contrainte tout vecteur unitaire $\vec { n }$ tel que :

$$
\sigma \vec {n} = \sigma \vec {n} \quad \Longleftrightarrow \quad \sigma \cdot \vec {n} = \sigma \vec {n}\tag{3.18}
$$

Étant donné qu’en 3D, il existe, pour tout tenseur de contraintes $\sigma$, 3 contraintes principales, on a :

$$
\sigma \vec {n} _ {i} = \sigma_ {i} \vec {n} _ {i} \quad \Longleftrightarrow \quad \sigma \cdot \vec {n} _ {i} = \sigma_ {i} \vec {n} _ {i} \quad \forall i = 1, 2, 3\tag{3.19}
$$

Définition 3.8 Le réel $\sigma _ { i }$ est appelé contrainte principale <sup><a href="#note-4">4</a></sup> dans la direction $\vec { n } _ { i }$

Il existe toujours au moins une base orthonormée $( \vec { n } _ { 1 } , \vec { n } _ { 2 } , \vec { n } _ { 3 } )$ de directions principales. Dans cette base, la matrice de $\sigma$ est diagonale et les éléments diagonaux sont les contraintes principales.

## 3.2.4 Opérateurs des contraintes particuliers

Pour chacun des états des contraintes particuliers listés ici, les composantes peuvent être dépendantes du temps et de l’espace.

## Opérateur sphérique

Définition 3.9 Un opérateur de contrainte est sphérique s’il est de la forme :

$$
\sigma = \sigma \mathbb {I} = \left[ \begin{array}{c c c} \sigma & 0 & 0 \\ 0 & \sigma & 0 \\ 0 & 0 & \sigma \end{array} \right] _ {(\vec {e} _ {1}, \vec {e} _ {2}, \vec {e} _ {3})}\tag{3.20}
$$

## Opérateur uniaxial

Définition 3.10 Un opérateur de contrainte est uniaxial dans la direction $\vec { e } _ { 1 }$ , s’il est de la forme :

$$
\boldsymbol {\sigma} = \left[ \begin{array}{c c c} \sigma_ {1 1} & 0 & 0 \\ 0 & 0 & 0 \\ 0 & 0 & 0 \end{array} \right] _ {(\vec {e} _ {1}, \vec {e} _ {2}, \vec {e} _ {3})}\tag{3.21}
$$

On parle aussi traction (ou compression selon le signe de $\sigma _ { 1 1 } )$ uniaxiale ou traction pure.

## Opérateur de type plan

Définition 3.11 Un opérateur de contrainte est de type plan dans le plan orthogonal $\dot { \partial } \stackrel {  } { \boldsymbol { e } _ { 1 } } \ s ^ { \prime } \boldsymbol { i } I$ est de la forme : 1

$$
\boldsymbol {\sigma} = \left[ \begin{array}{c c c} 0 & 0 & 0 \\ 0 & \sigma_ {2 2} & \sigma_ {2 3} \\ 0 & \sigma_ {2 3} & \sigma_ {3 3} \end{array} \right] _ {(\vec {e} _ {1}, \vec {e} _ {2}, \vec {e} _ {3})}\tag{3.22}
$$

## Opérateur de type antiplan

Définition 3.12 Un opérateur de contrainte est de type antiplan dans la direction $\vec { e } _ { 1 }$ s’il est de la forme :

$$
\sigma = \left[ \begin{array}{c c c} \sigma_ {1 1} & \sigma_ {1 2} & \sigma_ {1 3} \\ \sigma_ {1 2} & 0 & 0 \\ \sigma_ {1 3} & 0 & 0 \end{array} \right] _ {(\vec {e} _ {1}, \vec {e} _ {2}, \vec {e} _ {3})}\tag{3.23}
$$

## Opérateur de type cisaillement pur

Définition 3.13 Un opérateur de contrainte est de cisaillement pur dans le plan $( \vec { e } _ { 1 } , \vec { e } _ { 2 } ) \ s ^ { \prime } i I$ est de la forme :

$$
\boldsymbol {\sigma} = \left[ \begin{array}{c c c} 0 & \tau & 0 \\ \tau & 0 & 0 \\ 0 & 0 & 0 \end{array} \right] _ {(\vec {e} _ {1}, \vec {e} _ {2}, \vec {e} _ {3})}\tag{3.24}
$$

Remarque 3.5 Exprimé dans sa base principale, en effectuant une simple rotation de $4 5 ^ { \circ }$ , il peut être exprimé comme suit (avec $\vec { n } _ { 3 } = \vec { e } _ { 3 } )$

$$
\boldsymbol {\sigma} = \left[ \begin{array}{c c c} \tau & 0 & 0 \\ 0 & - \tau & 0 \\ 0 & 0 & 0 \end{array} \right] _ {(\vec {n} _ {1}, \vec {n} _ {2}, \vec {n} _ {3})}\tag{3.25}
$$

Définition 3.14 Un opérateur de contrainte est de torsion pure selon l’axe $\vec { e } _ { z }$ si, dans le repère cylindrique, il est de la forme :

$$
\sigma = \left[ \begin{array}{c c c} 0 & \tau & 0 \\ \tau & 0 & 0 \\ 0 & 0 & 0 \end{array} \right] _ {(\vec {e} _ {r}, \vec {e} _ {\theta}, \vec {e} _ {z})} \left[ \begin{array}{c c c} 0 & 0 & 0 \\ 0 & 0 & \tau \\ 0 & \tau & 0 \end{array} \right] _ {(\vec {e} _ {r}, \vec {e} _ {\theta}, \vec {e} _ {z})}\tag{3.26}
$$

## 3.2.5 Convention

Nous suivrons la convention la plus répandue stipulant qu’une contrainte de traction est positive alors qu’une contrainte de compression est négative.

## 3.3 Critères élémentaires de dimensionnement

## 3.3.1 Contraintes équivalentes

Les propriétés des matériaux en termes de limite élastique, sont données sous forme de scalaire (homogène à une contrainte ou pression). Afin de pouvoir comparer un état de contrainte en un point particulier avec cette limite en traction, souvent notée $\sigma _ { e }$ (ou $\sigma _ { y }$ pour les anglosaxons), il est nécessaire de définir des contraintes équivalentes. Il s’agit de fonctions transformant un état de contraintes, sous forme tensorielle, en une valeur de contrainte scalaire.

## 3.3.2 Critère de von Mises

Il s’agit d’un critère énergétique construit à partir de l’expression de l’énergie élastique déviatorique. Il est assez adapté aux métaux et alliages ductiles.

Définition 3.15 La contrainte équivalente de von Mises, notée σ , s’exprime à partir du déviateur des contraintes, plus précisément comme son second invariant :

$$
\sigma_ {V M} = \sqrt {\frac {3}{2} \mathrm{Tr} (\sigma^ {D} \sigma^ {D})} = \sqrt {\frac {3}{2} \sigma^ {D} : \sigma^ {D}} = \sqrt {\frac {3}{2} \sigma_ {i j} ^ {D} \sigma_ {i j} ^ {D}} = \sqrt {\frac {3}{2} \sigma : \sigma - \frac {(\mathrm{Tr} \sigma) ^ {2}}{2}}\tag{3.27}
$$

Cette contrainte équivalente peut également être formulée à partir des contraintes principales :

$$
\sigma_ {V M} = \sqrt {\frac {(\sigma_ {1} - \sigma_ {2}) ^ {2} + (\sigma_ {2} - \sigma_ {3}) ^ {2} + (\sigma_ {1} - \sigma_ {3}) ^ {2}}{2}}\tag{3.28}
$$

Le critère de von Mises est défini par :

$$
\sigma_ {V M} \leqslant \sigma_ {e}\tag{3.29}
$$

où $\sigma _ { e }$ est la limite élastique du matériau en traction.

Remarque 3.6 La partie sphérique (ou hydrostatique) des contraintes n’intervient donc pas dans l’expression de $\sigma _ { V M }$ . Cela implique qu’avec ce critère, un chargement hydrostatique, même de forte intensité, ne provoque pas de déformation irréversible, comme la plasticité ou rupture).

## 3.3.3 Critère de Tresca

Il s’agit d’un critère basé sur la contrainte de cisaillement maximale $\tau _ { m a x }$ , obtenue en un point de l’espace, en explorant l’ensemble des facettes et directions de sollicitation. À l’aide d’une analyse graphique avec le tri-cercle de Mohr (non abordé ici), on montre que cela correspond à la moitié du plus grand écart entre les contraintes principales.

$$
\tau_{max} = \max_{\substack{\| \vec{t}\| = 1,\\ \| \vec{n}\| = 1,\\ \vec{n}\cdot \vec{t} = 0}}\left|\vec{t}\cdot \boldsymbol {\sigma}\cdot \vec{n}\right| = \max_{i,j}\left|\frac{\sigma_{i} - \sigma_{j}}{2}\right|\tag{3.30}
$$

Définition 3.16 On appelle contrainte équivalente de Tresca le scalaire $\sigma _ { T r }$ défini $p a r$ :

$$
\sigma_ {T r} = \max _ {i, j} | \sigma_ {i} - \sigma_ {j} |\tag{3.31}
$$

où les $\sigma _ { i }$ sont les valeurs propres de $\sigma _ { \cdot }$ , $c$ est-à-dire les contraintes principales de $\sigma$ .

Le critère de Tresca est défini indifféremment par :

$$
\sigma_ {T r} \leqslant \sigma_ {e} \quad \mathrm{ou} \quad \tau_ {m a x} \leqslant \tau_ {e}\tag{3.32}
$$

où $\tau _ { e }$ est la limite élastique du matériau en cisaillement, qui correspond généralement à $\sigma _ { e } / 2$

## 3.3.4 Critère de Rankine

Pour les matériaux fragiles ou quasi-fragiles (comme le béton, le verre, la fonte, etc), on peut se baser sur le critère de Rankine qui suppose que le seuil de limite d’élasticité est atteint lorsque l’une des valeurs propres est égale à la contrainte à la rupture : $\ : \ : \sigma _ { R } \ :$ . LA contrainte équivalente et le critère associé sont définis comme suit :

$$
\sigma_ {R a} = \max _ {i} (\sigma_ {i}) \qquad \mathsf {e t} \qquad \sigma_ {R a} \leqslant \sigma_ {R}\tag{3.33}
$$

## 3.3.5 Dimensionnement

On dimensionne vis-à-vis d’un critère et donc d’une contrainte équivalente $\sigma _ { e q }$ (par exemple von Mises $\sigma _ { V M }$ ou Tresca $\sigma _ { T r } )$ , en imposant :

$$
\sigma_ {V M} \leqslant \frac {\sigma_ {e}}{C _ {s}} \mathrm{ou} \sigma_ {T r} \leqslant \frac {\sigma_ {e}}{C _ {s}} = \frac {2 \tau_ {e}}{C _ {s}}\tag{3.34}
$$

où $\sigma _ { e }$ est la limite élastique du matériau en traction (aussi appelée résistance élastique), $\tau _ { e }$ la limite élastique du matériau cisaillement et $C _ { s } \geqslant 1$ est le coefficient de sécurité.

## 3.3.6 Comparaison des deux critères en contrainte plane

Supposons que $\sigma$ est un opérateur plan qui, dans une base principale, s’écrit :

en traction biaxiale $\sigma = { \left[ \begin{array} { l l l } { \sigma _ { 1 } } & { 0 } & { 0 } \\ { 0 } & { \sigma _ { 2 } } & { 0 } \\ { 0 } & { 0 } & { 0 } \end{array} \right] } _ { ( { \vec { e } } _ { 1 } , { \vec { e } } _ { 2 } , { \vec { e } } _ { 3 } ) }$

et, en traction-cisaillement $\boldsymbol { \sigma } = \left[ \begin{array} { l l l } { \boldsymbol { \sigma } } & { \boldsymbol { \tau } } & { \boldsymbol { 0 } } \\ { \boldsymbol { \tau } } & { \boldsymbol { 0 } } & { \boldsymbol { 0 } } \\ { \boldsymbol { 0 } } & { \boldsymbol { 0 } } & { \boldsymbol { 0 } } \end{array} \right] _ { ( \vec { e } _ { 1 } , \vec { e } _ { 2 } , \vec { e } _ { 3 } ) }$

En traction biaxiale, le critère de Tresca donne max $( | \sigma _ { 1 } | , | \sigma _ { 2 } | , | \sigma _ { 1 } - \sigma _ { 2 } | ) \leqslant \sigma _ { e }$ et le critère de von Mises $\sigma _ { 1 } ^ { 2 } + \sigma _ { 2 } ^ { 2 } - \sigma _ { 1 } \sigma _ { 2 } \leqslant \sigma _ { e }$ . La figure 3.3a permet, dans le plan $( \sigma _ { 1 } , \sigma _ { 2 } )$ , de comparer les deux critères.

En traction-cisaillement, le critère de Tresca donne $\sqrt { \sigma ^ { 2 } + 4 \tau ^ { 2 } } \leqslant \sigma _ { e }$ et le critère de von Mises donne $\sqrt { \sigma ^ { 2 } + 3 \tau ^ { 2 } } \leqslant \sigma _ { e }$ . La figure 3.3b permet, dans le plan $( \sigma , \tau )$ , de comparer les deux critères.

![image](Images/IMMC_CM_Chap3_2025-2026_03.jpg)


Figure 3.3 – Comparaisons des deux critères en (a) traction biaxiale et (b) tractioncisaillement .


Remarque 3.7 On peut alors observer que pour une même limite élastique $\sigma _ { e } ,$ le domaine élastique défini par le critère de Tresca est plus restreint que celui de von Mises. On dit alors que le critère Tresca est davantage conservatif. En revanche von Mises permet de gommer les discontinuités (coins) que peut produire Tresca.

## Notes

<a id="note-1"></a>

**1.** En mécanique, on postule l’existence d’au moins un repère galiléen $\mathcal{R}$ (tous les autres repères galiléens sont alors en translation rectiligne uniforme par rapport à $\mathcal{R}$). Du point de vue pratique, les repères utilisés comme « galiléens » sont des approximations et dépendent des applications envisagées. Par exemple, pour de nombreuses expériences simples de laboratoire, un repère lié à la terre peut être considéré comme « galiléen ». Par contre, pour interpréter la célèbre expérience du pendule de Foucault, ce repère ne peut plus être considéré comme galiléen !

<a id="note-2"></a>

**2.** $\int_\Sigma\rho\vec{\Gamma}(M/\mathcal{R})\,\mathrm{d}V$ est la résultante dynamique ; $\int_\Sigma\overrightarrow{AM}\wedge\rho\vec{\Gamma}(M/\mathcal{R})\,\mathrm{d}V$ est le moment dynamique en $A$. Les deux égalités précédentes sont souvent appelées « théorèmes généraux de la dynamique » ; en fait, il s’agit simplement d’une autre écriture du PFD !

<a id="note-3"></a>

**3.** Les directions principales sont donc les directions propres (vecteurs propres) de l’opérateur linéaire $\sigma$.

<a id="note-4"></a>

**4.** Les contraintes principales sont donc les valeurs propres de l’opérateur linéaire $\sigma$.
