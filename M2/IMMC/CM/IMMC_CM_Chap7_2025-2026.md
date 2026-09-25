## Chapitre 7

## Problèmes de mécanique des fluides

À la différence des problèmes d’élasticité linéaire sur les solides :

— On se place cette fois en description eulérienne, les termes d’accélération feront cette fois appel à la dérivée particulaire.

— L’inconnue cinématique est cette fois la champ de vecteur vitesse eulérienne ${}^{E}\vec{V}$ alors que l’inconnue duale est cette fois le champ de pression, qui intervient dans le tenseur de contraintes $\sigma$.

— La résolution fera cette fois appel à la loi de conservation de la masse, en plus des autres équations.

## 7.1 Équations de Navier-Stokes

A partir d’hypothèses similaires à celles nécessaires à l’écriture des équations de Navier, c’est-à-dire ici :

— fluide homogène ;

— fluide visqueux newtonien.

De manière analogue à la construction des équations de Navier pour les milieux solides, on peut aboutir aux équations de Navier-Stokes en partant de l’équation d’équilibre dynamique (en description eulérienne), dans laquelle on injecte la loi de comportement du milieu fluide ainsi que la forme du tenseur des taux de déformation D. Il reste enfin à manipuler l’équation obtenue avec le théorème de Schwarz.

Si on développe de la relation de comportement du milieu fluide (ici visqueux Newtonien) :

$$
\sigma = - p \mathbb {I} + \lambda_ {v} \operatorname{Tr} (\mathbb {D}) \mathbb {I} + 2 \mu_ {v} \mathbb {D} \quad \text { soit   en   indiciel } \quad \sigma_ {i j} = - p \delta_ {i j} + \lambda_ {v} D _ {k k} \delta_ {i j} + 2 \mu_ {v} D _ {i j}\tag{7.1}
$$

Or on connait la forme du tenseur taux de déformation D :

$$
\mathbb {D} = \frac {1}{2} \left(\overline {{\overline {{\operatorname{grad}}}}} \vec {V} + \overline {{\overline {{\operatorname{grad}}}}} ^ {\mathsf {T}} \vec {V}\right) \quad \text { soit   en   indiciel } \quad D _ {i j} = \frac {1}{2} \left(V _ {i, j} + V _ {j, i}\right)\tag{7.2}
$$

Ce qui donne, une fois injecté dans la relation de comportement :

$$
\sigma_ {i j} = - p \delta_ {i j} + \lambda_ {v} V _ {k, k} \delta_ {i j} + \mu_ {v} (V _ {i, j} + V _ {j, i}) = \lambda_ {v} V _ {k, k} \delta_ {i j} + \mu_ {v} (V _ {i, j} + V _ {j, i}) - p \delta_ {i j}\tag{7.3}
$$

On repart de l’équilibre dynamique en description eulérienne :

$$
\overrightarrow {\operatorname{div}} \sigma + \vec {f} _ {d} = \rho \vec {\Gamma} \quad \xrightarrow {\text {soit en indiciel}} \quad \sigma_ {i j, j} + f _ {i} = \rho \Gamma_ {i}\tag{7.4}
$$

On injecte la relation de comportement développée précédemment pour le milieu fluide :

$$
\lambda_ {v} \left(V _ {k, k} \delta_ {i j}\right) _ {, j} + \mu_ {v} \left(V _ {i, j} + V _ {j, i}\right) _ {, j} - (p \delta_ {i j}) _ {, j} + f _ {i} = \rho \Gamma_ {i}\tag{7.5}
$$

$$
\lambda_ {v} V _ {k, k j} \delta_ {i j} + \mu_ {v} V _ {i, j j} + \mu_ {v} V _ {j, i j} - p _ {, j} \delta_ {i j} + f _ {i} = \rho \Gamma_ {i}\tag{7.6}
$$

Les termes en $\delta _ { i j }$ seront non nuls SSI $i = j$

$$
\lambda_ {v} V _ {k, k i} + \mu_ {v} V _ {i, j j} + \mu_ {v} V _ {j, i j} - p _ {, i} + f _ {i} = \rho \Gamma_ {i}\tag{7.7}
$$

Par le théorème de Schwartz :

$$
\lambda_ {v} V _ {k, k i} + \mu_ {v} V _ {i, j j} + \mu_ {v} V _ {j, j i} - p _ {, i} + f _ {i} = \rho \Gamma_ {i}\tag{7.8}
$$

On voit apparaître le gradient de pression, le Laplacien et le gradient de la divergence de la vitesse.

$$
\lambda_ {v} \overrightarrow {\operatorname{grad}} (\operatorname{div} \vec {V}) + \mu_ {v} \Delta \vec {V} + \mu_ {v} \overrightarrow {\operatorname{grad}} (\operatorname{div} \vec {V}) - \overrightarrow {\operatorname{grad}} p + \vec {f} _ {d} = \rho \vec {\Gamma}\tag{7.9}
$$

Soit, en définitive :

$$
\boxed {\mu_ {v} \Delta \vec {V} + (\lambda_ {v} + \mu_ {v}) \overrightarrow {\operatorname{grad}} (\operatorname{div} \vec {V}) - \overrightarrow {\operatorname{grad}} p + \vec {f} _ {d} = \rho \vec {\Gamma} = \rho \left(\frac {\partial \vec {V}}{\partial t} + \overline {{\overline {{\operatorname{grad}}}}} \vec {V} \cdot \vec {V}\right)}\tag{7.10}
$$

Encore une fois, en passant par la formule du double rotationnel, on peut construire trois formes différentes de ces équations. En fonction des hypothèses et caractéristiques du problème, certains termes s’annuleront ou se simplifieront. Il sera donc utile de choisir judicieusement la forme la plus adaptée au problème étudié (incompressibilité, aspect irrotationnel, forme du champ de vitesse, etc).

$$
\boxed{\left(\lambda_ {v} + 2 \mu_ {v}\right) \Delta \vec {V} + \left(\lambda_ {v} + \mu_ {v}\right) \overrightarrow {\operatorname{rot}} \overrightarrow {\operatorname{rot}} \vec {V} - \overrightarrow {\operatorname{grad}} p + \vec {f} _ {d} = \rho \vec {\Gamma} }\tag{7.11}
$$

$$
\boxed{\left(\lambda_ {v} + 2 \mu_ {v}\right) \overrightarrow {\operatorname{grad}} (\operatorname{div} \vec {V}) - \mu_ {v} \overrightarrow {\operatorname{rot}} \overrightarrow {\operatorname{rot}} \vec {V} - \overrightarrow {\operatorname{grad}} p + \vec {f} _ {d} = \rho \vec {\Gamma} }\tag{7.12}
$$

Remarque 7.1 L’équation de Navier-Stokes traduit un équilibre dynamique, qui fait intervenir différents termes et différentes natures de forces impliquées dans l’équilibre dynamique, qui sont explicitées ci-dessous :

$$
\underbrace {\overbrace {\mu_ {v} \Delta \vec {V}} ^ {\text {terme diffusif}} + (\lambda_ {v} + \mu_ {v}) \overrightarrow {\operatorname{grad}} (\operatorname{div} \vec {V})} _ {\text {forces de viscosité}} - \overbrace {\overrightarrow {\operatorname{grad} p}} ^ {\text {forces de pression}} + \underbrace {\vec {f} _ {d}} _ {\text {forces de volume}} = \overbrace {\rho \vec {\Gamma}} ^ {\text {forces d'inertie}} = \rho \left(\underbrace {\frac {\partial \vec {V}}{\partial t}} _ {\text {terme instationnaire}} + \overbrace {\overline {{\operatorname{grad}}} \vec {V} \cdot \vec {V}} ^ {\text {terme convectif}}\right)
$$

## 7.2 Conditions aux limites

## 7.2.1 Vitesse lors de l’écoulement autour d’un solide

## Paroi imperméable

On a dans ce cas, continuité des vitesses normales. Les composantes normales à la paroi Σ, de normale ${ \vec { n } } ,$ de la vitesse du fluide $\vec { V _ { f } }$ et du solide $\vec { V _ { s } }$ , sont égales.

$$
\vec {V} _ {f} (M) \cdot \vec {n} (M) = \vec {V} _ {s} (M) \cdot \vec {n} (M) \quad \forall M \in \Sigma\tag{7.13}
$$

## Fluide parfait s’écoulant le long d’une paroi imperméable

Dans ce cas, on ne considère que la continuité des vitesses normales uniquement. Il n’y a pas de condition sur les composantes tangentielles à la paroi Σ (ou interface avec un autre fluide) de la vitesse du fluide $\vec { V } _ { f }$ et du solide $\vec { V _ { s } }$ (ou de l’autre fluide $\vec { V } _ { f 2 }$

## Fluide visqueux s’écoulant le long d’une paroi

Dans ce cas, il y a adhérence du fluide à la paroi, ce qui se traduit par :

— Continuité des vitesses tangentielles : les composantes tangentielles à la paroi $\Sigma$ de la vitesse du fluide $\vec { V } _ { f }$ et du solide $\vec { V } _ { s } ,$ , sont égales.

$$
\vec {V} _ {f} ^ {t} (M) = \vec {V} _ {s} ^ {t} (M) \quad \forall M \in \Sigma \quad \xrightarrow {\text { +imperméabilité   de   la   paroi }} \quad \vec {V} _ {f} (M) = \vec {V} _ {s} (M) \quad \forall M \in \Sigma\tag{7.14}
$$

## 7.2.2 Pression sur une frontière Σ de normale $\vec { n }$

On retrouve la même condition que dans le cas d’un milieu solide soumis à une pression $p$ :

$$
\sigma \cdot \vec {n} = - p \vec {n} \quad \text { soit } \quad \sigma (M) \cdot \vec {n} (M) = - p (M) \vec {n} (M) \qquad \forall M \in \Sigma\tag{7.15}
$$

## 7.2.3 Condition mixte : interface entre fluides visqueux non miscibles

Dans le cas d’une interface Σ, de normale ${ \vec { n } } ,$ , entre 2 fluides visqueux non miscibles A et B, on peut écrire des conditions de continuité portant à la fois sur les vitesses et les contraintes.

— Interface imperméable (car fluides non miscibles) → continuité des vitesses normales :

$$
\vec {V} _ {A} (M) \cdot \vec {n} = \vec {V} _ {B} (M) \cdot \vec {n} \quad \forall M \in \Sigma
$$

— Fluides visqueux donc adhérence → continuité des vitesses tangentielles :

$$
\vec {V} _ {A} ^ {t} (M) = \vec {V} _ {B} ^ {t} (M) \quad \forall M \in \Sigma \quad \xrightarrow {\text { +interface   impermeable }} \quad \vec {V} _ {A} (M) = \vec {V} _ {B} (M) \quad \forall M \in \Sigma
$$

— Équilibre de l’interface → continuité du vecteur contrainte :

$$
\llbracket \sigma (M) \rrbracket_ {\Sigma} \cdot \vec {n} (M) = \vec {0} \quad \forall M \in \Sigma \quad \Longleftrightarrow \quad \sigma_ {A} (M) \cdot \vec {n} (M) = \sigma_ {B} (M) \cdot \vec {n} (M) \quad \forall M \in \Sigma
$$

## 7.3 Méthodologie

Nous allons donner ici les étapes de résolution d’un problème de mécanique des fluides :

A. Décrire la géométrie du problème (domaine, chargement)

B. Lister les hypothèses du problèmes (stationnarité, incompressibilité, invariances, etc)

C. Lister les équations portant sur le milieux

D. Lister les conditions aux limites du problème

E. Vérifier le nombre d’inconnues vis-a-vis du nombre d’équations

F. Résoudre

## 7.4 Exemple : écoulement de Poiseuille

Voir TD7, exercice 1
