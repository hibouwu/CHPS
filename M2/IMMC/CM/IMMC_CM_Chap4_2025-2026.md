## Chapitre 4

# Principes fondamentaux de la Mécanique des Milieux Continus

Dans les chapitres précédents, nous avons introduit la description cinématique du mouvement d’un milieu continu et la schématisation des efforts intérieurs et extérieurs. Lorsque des sollicitations extérieures sont données, l’objectif est de déterminer le champ de contrainte en tout point et à tout instant ainsi que le champ de déplacement (en description lagrangienne) ou le champ de vitesse (en description eulérienne). Dans ce chapitre, nous allons introduire, ou rappeler, les grands principes de la Mécanique et établir les équations fondamentales qui en résultent. On parle aussi de « Lois de conservation » ou de « Lois bilan ».

## Lemme Fondamental

Soit Σ une partie du domaine complet étudié Ω et • une quantité physique quelconque (scalaire, vectorielle ou tensorielle). On a :

$$
\int_ {\Sigma} \bullet (M) \mathrm{d} V = 0 \forall \Sigma \in \Omega \quad \Longleftrightarrow \quad \bullet (M) = 0 \forall M \in \Omega\tag{4.1}
$$

Cela correspond au Lemme Fondamental de la Physique des Milieux Continus (LFPMC).

## 4.1 Conservation de la masse

## 4.1.1 Densité volumique de masse

On admet que dans un milieu continu Ω la répartition des masses est décrite par la donnée d’une densité volumique de masse <sup><a href="#note-1">1</a></sup> définie en tout point M et à tout instant t :

$$
(t, M) \mapsto \rho (t, M)\tag{4.2}
$$

Dans la configuration initiale $\Omega _ { 0 }$ , on note : $\rho ( 0 , M _ { 0 } ) = \rho _ { 0 } ( M _ { 0 } )$ . Soit $\Sigma _ { 0 }$ une partie de $\Omega _ { 0 }$ et $\Sigma ( t )$ la position de $\Sigma_0$ à l’instant t :

$$
\Sigma (t) = \{M = \phi (t, M _ {0}), M _ {0} \in \Sigma_ {0} \}\tag{4.3}
$$

La masse de $\Sigma$ à $t$ est définie par :

$$
m (t, \Sigma) = \int_ {\Sigma (t)} \rho (t, M) \mathrm{d} V\tag{4.4}
$$


## 4.1.2 Principe de conservation de la masse

Toute partie d’un milieu continu, que l’on suit dans son mouvement, a une masse constante.

$$
\frac {\mathrm{d} m}{\mathrm{d} t} = 0 \quad \Longleftrightarrow \quad \frac {\mathrm{d}}{\mathrm{d} t} \int_{\Sigma(t)}\rho\,\mathrm dV=0\qquad\text{pour toute partie matérielle }\Sigma(t)\tag{4.5}
$$

> **Précision théorique (PDF, p. 2, formule 4.5).** La phrase précédente dit « toute partie » matérielle ; pour en déduire la conservation locale, le bilan doit valoir pour chaque $\Sigma(t)$, et pas seulement pour le corps entier $\Omega(t)$.\n\nIl s’agit d’un bilan global sur toute partie matérielle $\Sigma(t)$. On a alors, sous forme locale :

$$
\begin{array}{c c} \rho \det (\mathbb {F}) = \rho_ {0} & \text {en description lagrangienne} \\ \frac {\mathrm{d} \rho}{\mathrm{d} t} + \rho \operatorname{div} (\vec {V}) = \frac {\partial \rho}{\partial t} + \operatorname{div} (\rho \vec {V}) = 0 & \text {en description eulérienne} \end{array}\tag{4.6}
$$

Cette équation (ou jeu d’équations), est également appelée « équation locale de conservation de la masse » ou « équation de continuité sous forme locale ».

Dans le cas d’un milieu composé de deux parties fluides $\Omega _ { 1 }$ et $\Omega _ { 2 }$ , séparées par une interface $\Sigma ( t )$ se déplaçant à la vitesse locale $\vec { W } ( M , t )$ , la conservation de la masse peut s’écrire sous forme d’une équation de saut :

$$
\llbracket \rho (\vec {V} - \vec {W}) \cdot \vec {n} \rrbracket _ {\Sigma (t)} = 0\tag{4.7}
$$

où $\llbracket\bullet\rrbracket = \bullet | _ { \partial \Omega _ { 2 } \cap \Sigma ( t ) } - \bullet | _ { \partial \Omega _ { 1 } \cap \Sigma ( t ) }$ et $\vec{n}$ la normale sortante locale sur $\Sigma ( t )$ , allant de $\Omega _ { 1 }$ vers $\Omega _ { 2 }$

Remarque 4.1 Pour toute fonction f, on a :

$$
\frac {\mathrm{d}}{\mathrm{d} t} \int_ {\Sigma} \rho f \mathrm{d} V = \int_ {\Sigma} \rho \frac {\mathrm{d} f}{\mathrm{d} t} \mathrm{d} V\tag{4.8}
$$

que l’on écrit souvent, en posant $\rho \mathrm { d } V = \mathrm { d } m$

$$
\frac {\mathrm{d}}{\mathrm{d} t} \int_ {\Sigma} f \mathrm{d} m = \int_ {\Sigma} \frac {\mathrm{d} f}{\mathrm{d} t} \mathrm{d} m\tag{4.9}
$$

Remarque 4.2 Soit $\mathcal { V } ( \Sigma )$ le volume d’une partie du milieu continu que l’on suit dans son mouvement. On obtient :

$$
\frac {\mathrm{d}}{\mathrm{d} t} \mathcal {V} (\Sigma) = \frac {\mathrm{d}}{\mathrm{d} t} \int_ {\Sigma} \mathrm{d} V = \int_ {\Sigma} \left(\frac {\mathrm{d}}{\mathrm{d} t} (1) + 1 \operatorname{div} (\vec {V})\right) \mathrm{d} V \quad \begin{array}{l} \text { par   la } 2 ^ {\mathrm{e}} \text { forme   du   théorème } \\ \text { de   transport   de   Reynolds } \end{array}\tag{4.10}
$$

soit :

$$
\frac {\mathrm{d}}{\mathrm{d} t} \mathcal {V} (\Sigma) = \int_ {\Sigma} \operatorname{div} (\vec {V}) \mathrm{d} V\tag{4.11}
$$

On en déduit donc que si $\mathrm { d i v } ( \vec { V } )$ est nul, le volume de chaque particule est constant au cours du mouvement.

Remarque 4.3 On peut qualifier d’incompressible un milieu (matériau ou fluide) ou un mouvement. Il faut cependant apporter de la précaution à l’utilisation des ces hypothèses.

Milieu, matériau ou fluide incompressible : $\rho = c s t e \quad \Longrightarrow \quad \mathrm { d i v } \vec { V } = 0$

Mouvement incompressible : $\begin{array} { r l r } { \frac { \mathrm { d } \rho } { \mathrm { d } t } = 0 } & { { } \Longleftrightarrow } & { \mathrm { d i v } { \vec { V } } = 0 } \end{array}$

Pour un milieu continu incompressible, on a $\rho ( t , M ) = \rho _ { 0 } ( M _ { 0 } )$ . Généralement, on suppose en plus que le milieu est homogène ce qui conduit à $\rho ( t , M ) = \rho _ { 0 }$

## 4.2 Équations d’équilibre d’un milieu continu

On considère que les actions extérieures sont schématisées par une densité volumique de forces (donnée ou non) $\vec { f } _ { v }$ définie dans Ω et des efforts surfaciques (donnés ou non) $\vec { T }$ définis sur ∂Ω.

## 4.2.1 Équation d’équilibre local

Théorème 4.1 En tout point et à tout instant, on a <sup><a href="#note-2">2</a></sup> :

$$
\overrightarrow {\mathrm{div}} \sigma + \vec {f _ {v}} = \rho \vec {\Gamma}\tag{4.12}
$$

On appelle aussi cette équation « équilibre intérieur » ou « conservation de la quantité de mouvement » sous sa forme locale. À la base, elle porte sur des quantités uniquement eulériennes.

Si la densité volumique de force est donnée, on la note $\vec { f } _ { d }$ , soit $: \overrightarrow { \mathrm { d i v } } \sigma + \overrightarrow { f _ { d } } = \rho \overrightarrow { \Gamma } .$

## 4.2.2 Conditions aux limites

Par un raisonnement simple de continuité à la frontière ∂Ω (physique ou virtuelle), on a :

$$
\sigma (M) \vec {n} (M) = \sigma (M) \cdot \vec {n} (M) = \vec {T} (M) \quad \forall M \in \partial \Omega\tag{4.13}
$$

Ce cas général peut se décliner en certains cas particuliers :

Densité surfacique d’effort $\vec { T _ { d } }$ donnée sur une partie de la frontière $\partial \Omega _ { T }$

$$
\sigma (M) \cdot \vec {n} (M) = \vec {T _ {d}} (M) \quad \forall M \in \partial \Omega_ {T}\tag{4.14}
$$

Condition aux limites en pression p sur une partie de la frontière $\partial \Omega _ { p }$

$$
\sigma (M) \cdot \vec {n} (M) = - p (M) \vec {n} (M) \quad \forall M \in \partial \Omega_ {p}\tag{4.15}
$$

Condition de surface libre (de contrainte) sur une partie de la frontière $\partial \Omega _ { 0 }$

$$
\sigma (M) \cdot \vec {n} (M) = \vec {0} \quad \forall M \in \partial \Omega_ {0}\tag{4.16}
$$

Condition de type torseur d’effort résultant en A sur une partie de la frontière $\partial \Omega _ { T }$

$$
\left\{ \begin{array}{c} \int_ {\partial \Omega_ {T}} \boldsymbol {\sigma} (M) \cdot \vec {n} (M) \mathrm{d} S = \vec {R} \\ \int_ {\partial \Omega_ {T}} \overrightarrow {A M} \wedge \boldsymbol {\sigma} (M) \cdot \vec {n} (M) \mathrm{d} S = \vec {M} _ {A} \end{array} \right.\tag{4.17}
$$

Dans certains cas, ce type de condition peut ne porter que sur certaines composantes du torseur d’effort résultant.

Condition d’adhésion parfaite (ou contact collant) → continuité d’efforts et déplacements

• entre deux milieux déformables $\Omega _ { 1 }$ et $\Omega _ { 2 }$ à la frontière $\Sigma ( t )$

$$
\llbracket \sigma \rrbracket_ {\Sigma (t)} \cdot \vec {n} = (\sigma_ {2} - \sigma_ {1}) \cdot \vec {n} = \vec {0} \quad \text {et} \quad \llbracket \vec {u} \rrbracket_ {\Sigma (t)} = \vec {u} _ {2} - \vec {u} _ {1} = \vec {0} \quad \forall M \in \Sigma (t)\tag{4.18}
$$

• entre un milieu déformable Ω et un corps rigide (encastrement) à la frontière $\partial \Omega _ { T }$

aucune CL en effort mais plutôt en déplacement :

$$
\vec{u}(M)=\vec{0}\qquad\forall M\in\partial\Omega_u\tag{4.19}
$$


> **Erratum de frontière (PDF, p. 4, formule 4.19).** Le PDF utilise $\partial\Omega_T$ pour un encastrement, alors que la condition $\vec u=0$ est une condition de déplacement et relève de $\partial\Omega_u$ dans la convention du cours.\n\nCondition de contact sans frottement (ou contact glissant, glissement libre)

• entre deux milieux déformables $\Omega _ { 1 }$ et $\Omega _ { 2 }$ à la frontière Σ(t)

$$
\vec {n} \cdot \llbracket\sigma\rrbracket _ {\Sigma (t)} \cdot \vec {n} = \vec {n} \cdot (\sigma_ {2} - \sigma_ {1}) \cdot \vec {n} = 0 \quad \text { et } \quad \llbracket\vec{u}\rrbracket _ {\Sigma (t)} \cdot \vec {n} = 0 \qquad \forall M \in \Sigma (t)\tag{4.20}
$$

$$
\vec {t} \cdot \sigma_ {1} \cdot \vec {n} = 0 \quad \text {et} \quad \vec {t} \cdot \sigma_ {2} \cdot \vec {n} = 0 \qquad \forall M \in \Sigma (t) \qquad \text {avec} \quad \vec {t} \cdot \vec {n} = 0\tag{4.21}
$$

• entre un milieu déformable Ω et un corps rigide à la frontière $\partial \Omega _ { T }$

$$
\vec {t} \cdot \boldsymbol {\sigma} \cdot \vec {n} = 0 \qquad \mathrm{et} \qquad \vec {u} \cdot \vec {n} = 0 \qquad \forall M \in \partial \Omega_ {T}\tag{4.22}
$$

Si $\partial \Omega _ { T }$ est une frontière plane, cela correspond à ce qu’on appelle une « condition de symétrie ».

Remarque 4.4 La notation $\llbracket\bullet\rrbracket _ { \Sigma }$ correspond au saut de la quantité • à travers la frontière Σ.

## 4.3 Les principes de la thermodynamique

Ces principes sont uniquement mentionnés ici pour mémoire mais nous ne les utiliserons que très peu dans ce cours.

## 4.3.1 Le premier principe

Ce principe introduit la notion d’énergie interne et il fournit un bilan d’énergie : la variation d’énergie (énergie interne + énergie cinétique) entre deux états est égale à la somme du travail reçu et de la quantité de chaleur reçue.

On peut traduire ce principe sous forme locale en l’exprimant en fonction de la température, ce qui correspond à l’équation de la la chaleur.

## 4.3.2 Le second principe

Ce principe introduit la notion d’entropie. C’est une inégalité qui fixe un sens à l’évolution d’un système et peut donner la notion d’irréversibilité.

## 4.4 Le théorème de l’énergie cinétique

Définition 4.1 La puissance des efforts intérieurs est définie par :

$$
P _ {i n t} = - \int_ {\Omega} \operatorname{Tr} (\sigma \mathbb {D}) \mathrm{d} V = - \int_ {\Omega} \sigma : \mathbb {D} \mathrm{d} V\tag{4.23}
$$


Remarque 4.5 En représentation lagrangienne, la puissance des efforts intérieurs s’écrit :

$$
P _ {i n t} = - \int_ {\Omega_ {0}} \mathrm{Tr} (\mathbb {S} \dot {\mathbb {E}}) \mathrm{d} V _ {0}\tag{4.24}
$$

où l’opérateur $\mathbb { S } = \operatorname* { d e t } ( \mathbb { F } ) \mathbb { F } ^ { - 1 } \sigma \mathbb { F } ^ { - T }$ est appelé (seconde) contrainte de Piola-Kirchhoff (PK2).

Théorème 4.2 Dans un repère galiléen, la dérivée de l’énergie cinétique d’un milieu continu, équivalente à la puissance des quantités d’accélération $\ P _ { a c c }$ , est égale à la somme de la puissance des efforts extérieurs $P _ { e x t }$ et de la puissance des efforts intérieurs $P _ { i n t }$

$$
\frac {\mathrm{d}}{\mathrm{d} t} E _ {c i n} (\Omega) = P _ {e x t} + P _ {i n t} = \int_ {\Omega} \vec {f _ {v}} \cdot \vec {V} \mathrm{d} V + \int_ {\partial \Omega} \vec {T} \cdot \vec {V} \mathrm{d} S - \int_ {\Omega} \underbrace {\mathrm{Tr} (\sigma \mathbb {D})} _ {\sigma : \mathbb {D}} \mathrm{d} V\tag{4.25}
$$

C’est une conséquence directe des équations d’équilibre.

## Notes

<a id="note-1"></a>

**1.** La dimension physique de $\rho$ est $\mathsf{M}\mathsf{L}^{-3}$, soit l’unité $\mathsf{kg}\cdot\mathsf{m}^{-3}$.

<a id="note-2"></a>

**2.** La divergence $\overrightarrow{\operatorname{div}}\mathbb{A}$ d’un opérateur linéaire $\mathbb{A}$ est définie, pour tout champ de vecteur constant $\vec{W}$, par $\operatorname{div}(\mathbb{A}\vec{W})=\overrightarrow{\operatorname{div}}\mathbb{A}\cdot\vec{W}$. Dans un repère orthonormé, on a $(\overrightarrow{\operatorname{div}}\mathbb{A})_i=\sum_{k=1}^{3}A_{ik,k}$. Pour un champ de vecteur $\vec{Z}$ dépendant du point $M$, on a $\operatorname{div}(\mathbb{A}\vec{Z})=\overrightarrow{\operatorname{div}}\mathbb{A}\cdot\vec{Z}+\operatorname{Tr}\!\left[\mathbb{A}\frac{\partial\vec{Z}}{\partial M}\right]$.
