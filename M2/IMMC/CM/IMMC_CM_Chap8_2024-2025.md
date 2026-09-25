## Chapitre 8

# Les théorèmes de l’énergie en élasticité

## Objectifs

Mettre en place de nouvelles formulations pour un problème d’élasticité bien adaptées à la recherche de solutions approchées.

## Hypothèses

On se place en statique, sous les hypothèses HPP. Le comportement est élastique linéaire (non nécessairement homogène ou isotrope) :

$$
\sigma = \mathbf {K}: \varepsilon (\vec {u}) \quad \text { avec   } \mathbf {K} \text {   opérateur   de   Hooke }\tag{8.1}
$$

## Domaines d’application

On va étudier dans un premier temps l’élasticité 3D, mais ces méthodes s’appliquent à bien d’autres problèmes :

— calculs de poutres élastiques droites ou courbes ;

— calculs de plaques ou de coques ;

— calculs en élasticité bidimensionnelle (DP ou CP) ;

— conduction thermique stationnaire ;

— etc

## Rappel de la formulation du problème

Trouver $( \vec { u } , \sigma )$ tels que :

— Équations de liaison

$$
\vec {u} = \vec {u} _ {d} \quad \forall M \in \partial \Omega_ {u} (+ \text { régularité })\tag{8.2}
$$

— Équations d’équilibre

$$
\overrightarrow {\mathrm{div}} \sigma + \vec {f} _ {d} = \vec {0} \quad \forall M \in \Omega\tag{8.3}
$$

$$
\sigma \vec {n} = \vec {T _ {d}} \quad \forall M \in \partial \Omega_ {T}
$$

— Relation de comportement

$$
\sigma = \mathbf {K}: \varepsilon (\vec {u})\tag{8.4}
$$

On notera $( \vec { u } _ { e x } , \sigma _ { e x } )$ la solution de ce problème (solution unique en contrainte et unique en déplacement si la frontière $\partial \Omega _ { u }$ est de mesure non nulle).

## 8.1 Champs admissibles (rappels)

## 8.1.1 Champs de déplacement cinématiquement admissibles

Définition 8.1 Un champ de déplacement $\vec{u}$ est dit Cinématiquement Admissible (en abrégé CA) si et seulement si il vérifie les équations de liaisons cinématiques (8.2).

Définition 8.2 Un champ de déplacement $\vec { u } ^ { \star }$ est dit Cinématiquement Admissible à Zéro (en abrégé CAZ) si et seulement si il vérifie les équations de liaisons pour des données nulles :

$$
\vec {u}^{\star} = \vec {0} \quad \forall M \in \partial \Omega_ {u} \quad (+\text{ régularité})\tag{8.5}
$$

> **Erratum de notation (PDF, p. 2, formule 8.5).** Le PDF imprime $\vec u$ alors que la définition porte sur le champ CAZ $\vec u^\star$ ; l’astérisque est rétabli ci-dessus.

Proposition 8.1 Si deux champs de déplacement $\vec { u } _ { 1 }$ et $\vec { u } _ { 2 }$ sont CA, leur différence $\vec { u } _ { 1 } - \vec { u } _ { 2 }$ est CAZ.

Proposition 8.2 Si $\vec { u } _ { 0 }$ est un champ CA particulier, tous les autres sont de la forme $\vec { u } =$ $\vec { u } _ { 0 } + \vec { u } ^ { \star }$ avec $\vec { u } ^ { \star }$ CAZ.

— L’espace affine (de dimension infinie) des champs CA est noté $\mathcal { U } _ { a d }$

— L’espace vectoriel (de dimension infinie) des champs $\mathsf { C A Z }$ est noté $\mathcal { U } _ { 0 }$

## 8.1.2 Champs de contrainte statiquement admissibles

Définition 8.3 Un champ de contrainte $\sigma$ est dit Statiquement Admissible (en abrégé SA) si et seulement si il vérifie les équations d’équilibre (8.3).

Définition 8.4 Un champ de contrainte $\boldsymbol { \sigma } ^ { \star }$ est dit Statiquement Admissible à Zéro (en abrégé SAZ) si et seulement si il vérifie les équations d’équilibre pour des données nulles :

$$
\overrightarrow {\operatorname{div}} \sigma^ {\star} = \vec {0} \quad \forall M \in \Omega \qquad e t \qquad \sigma^ {\star} \vec {n} = \vec {0} \quad \forall M \in \partial \Omega_ {T}\tag{8.6}
$$

Proposition 8.3 Si deux champs de contrainte $\sigma _ { 1 }$ et $\sigma _ { 2 }$ sont SA , leur différence $\sigma _ { 1 } - \sigma _ { 2 }$ est SAZ.

Proposition 8.4 Si $\sigma _ { 0 }$ est un champ SA particulier, tous les autres sont de la forme $\sigma =$ $\sigma _ { 0 } + \sigma ^ { \star }$ avec $\sigma ^ { \star } \ S A Z .$

— L’espace affine (de dimension infinie) des champs $\mathsf { S A }$ est noté $S _ { a d }$

— L’espace vectoriel (de dimension infinie) des champs $\mathsf { S A Z }$ est noté $\mathcal{S}_0$

## 8.1.3 Une propriété d’orthogonalité

Soit S l’espace des champs de contrainte.

Proposition 8.5 $\langle\sigma_1,\sigma_2\rangle_{\mathcal{S}}$ est un produit scalaire sur $\mathcal{S}$ avec :

$$
\left<   \sigma_ {1}, \sigma_ {2} \right> _ {\mathcal {S}} = \int_ {\Omega} \mathrm{Tr} \left[ \sigma_ {1} \mathbf {K} ^ {- 1}: \sigma_ {2} \right] \mathrm{d} V = \int_ {\Omega} \sigma_ {1}: \mathbf {K} ^ {- 1}: \sigma_ {2} \mathrm{d} V
$$

Proposition 8.6 $\| \sigma \| _ { \mathcal { S } }$ est une norme sur $\mathcal{S}$ avec :

$$
\left\| \sigma \right\| _ {\mathcal {S}} = \left[ \int_ {\Omega} \operatorname{Tr} \left(\sigma \mathbf {K} ^ {- 1}: \sigma\right) \mathrm{d} V \right] ^ {1 / 2} = \left[ \int_ {\Omega} \sigma : \mathbf {K} ^ {- 1}: \sigma \mathrm{d} V \right] ^ {1 / 2}
$$

Théorème 8.7 Si $\vec { u } ^ { \star }$ est $C A Z$ et si $\sigma ^ { \star }$ est $S A Z ,$ on a :

$$
\int_ {\Omega} \mathrm{Tr} [ \sigma^ {\star} \varepsilon (\vec {u} ^ {\star}) ] \mathrm{d} V = \int_ {\Omega} \sigma^ {\star}: \varepsilon (\vec {u} ^ {\star}) \mathrm{d} V = 0\tag{8.7}
$$

Les champs de contrainte $\boldsymbol { \sigma } ^ { \star }$ et $\mathbf { K } : \varepsilon ( \vec { u } ^ { \star } )$ sont donc orthogonaux.

## 8.2 Nouvelle formulation du problème

## 8.2.1 Formulation globale de la relation de comportement

Proposition 8.8 La relation de comportement (8.4) est vérifiée presque partout dans $\Omega$ si et seulement si $\|\sigma-\mathbf K:\varepsilon(\vec u)\|_{\mathcal S}=0$. Sous une hypothèse de continuité des champs, elle vaut alors partout.

> **Précision théorique (PDF, p. 3, proposition 8.8).** Une norme intégrale nulle donne en général une égalité presque partout ; l’égalité en chaque point demande une régularité supplémentaire.\n\n## 8.2.2 Erreur en relation de comportement

Un couple $( \vec { u } , \sigma )$ est appelé solution approchée admissible du problème d’élasticité si $\vec { u }$ est CA et si $\sigma$ est $\mathsf { S A }$

Pour un tel couple, seule la relation de comportement (8.4) n’est pas vérifiée.

Définition 8.5 On appelle erreur en relation de comportement associée au couple admissible $( \vec { u } , \sigma )$ la grandeur (de type contrainte) $\boldsymbol { \sigma } - \mathbf { K } : \boldsymbol { \varepsilon } ( \vec { u } )$

La norme $e = \| \boldsymbol { \sigma } - \mathbf { K } : \boldsymbol { \varepsilon } ( \vec { u } ) \| _ { \mathcal { S } }$ permet d’évaluer la qualité de la solution approchée admissible. $( \vec { u } , \sigma )$ est donc solution du problème d’élasticité si et seulement si $\vec{u}$ est CA, $\sigma$ est SA , et $e = 0$

## 8.2.3 Un premier problème de minimisation

Posons :

$$
\begin{array}{l} \Psi (\vec {u}, \sigma) = \frac {1}{2} \| \sigma - \mathbf {K}: \varepsilon (\vec {u}) \| _ {\mathcal {S}} ^ {2} = \frac {1}{2} \langle \sigma - \mathbf {K}: \varepsilon (\vec {u}), \sigma - \mathbf {K}: \varepsilon (\vec {u}) \rangle_ {\mathcal {S}} \\ = \frac {1}{2} \int_ {\Omega} [ \sigma - \mathbf {K}: \varepsilon (\vec {u}) ]: \mathbf {K} ^ {- 1}: [ \sigma - \mathbf {K}: \varepsilon (\vec {u}) ]   \mathrm{d} V \end{array}
$$

et considérons le problème de minimisation :

$$
\min_{\substack{\vec{u}\in \mathcal{U}_{ad},\\ \sigma \in \mathcal{S}_{ad}}}\Psi (\vec{u},\sigma)\quad \text{soit}\quad (\vec{u}_{ex},\sigma_{ex}) = \operatorname *{arg  min}_{\substack{\vec{u}\in \mathcal{U}_{ad},\\ \sigma \in \mathcal{S}_{ad}}}\Psi (\vec{u},\sigma)\tag{8.8}
$$

Proposition 8.9 La solution $( \vec { u } _ { e x } , \sigma _ { e x } )$ d’un problème d’élasticité est solution du problème de minimisation (8.8).

Réciproquement si la solution du problème (8.8) correspond à un minimum nul, c’est la solution du problème d’élasticité.

## 8.3 Les théorèmes de l’énergie

## 8.3.1 Propriété de découplage

Proposition 8.10 Pour $\vec{u}$ CA et pour $\sigma$ SA on $\textit { a } \Psi ( \vec { u } , \sigma ) = E _ { p } ( \vec { u } ) + E _ { c } ( \sigma )$ avec

$$
E _ {p} (\vec {u}) = \frac {1}{2} \int_ {\Omega} \varepsilon (\vec {u}): \mathbf {K}: \varepsilon (\vec {u}) \mathrm{d} V - \left[ \int_ {\Omega} \vec {f} _ {d} \cdot \vec {u} \mathrm{d} V + \int_ {\partial \Omega_ {T}} \vec {T} _ {d} \cdot \vec {u} \mathrm{d} S \right]\tag{8.9}
$$

$$
E _ {c} (\boldsymbol {\sigma}) = \frac {1}{2} \int_ {\Omega} \boldsymbol {\sigma}: \mathbf {K} ^ {- 1}: \boldsymbol {\sigma} \mathrm{d} V - \int_ {\partial \Omega_ {u}} \boldsymbol {\sigma} \vec {n} \cdot \vec {u} _ {d} \mathrm{d} S
$$

On a donc :

$$
\min_{\substack{\vec{u}\in \mathcal{U}_{ad},\\ \sigma \in \mathcal{S}_{ad}}}\Psi (\vec{u},\sigma) = \min_{\vec{u}\in \mathcal{U}_{ad}}E_{p}(\vec{u}) + \min_{\sigma \in \mathcal{S}_{ad}}E_{c}(\sigma)\tag{8.10}
$$

## 8.3.2 Théorème de l’énergie potentielle

Théorème 8.11 La solution exacte en déplacement $\vec { u } _ { e x }$ est solution du problème de minimisation :

$$
\min _ {\vec {u} \in \mathcal {U} _ {a d}} E _ {p} (\vec {u}) \qquad s o i t \qquad \vec {u} _ {e x} = \underset {\vec {u} \in \mathcal {U} _ {a d}} {\arg \min} E _ {p} (\vec {u})\tag{8.11}
$$

Interprétation des termes de l’énergie potentielle $E _ { p }$

— Le terme

$$
\frac {1}{2} \int_ {\Omega} \varepsilon (\vec {u}): \mathbf {K}: \varepsilon (\vec {u}) \mathrm{d} V
$$

correspond à l’énergie de déformation (élastique) exprimée en déplacement.

— Le terme

$$
\int_ {\Omega} \vec {f} _ {d} \cdot \vec {u} \mathrm{d} V + \int_ {\partial \Omega_ {T}} \vec {T} _ {d} \cdot \vec {u} \mathrm{d} S
$$

correspond au travail des efforts extérieurs donnés dans un déplacement CA.

Remarque 8.1 Une fois résolu le problème précédent, la solution en contrainte $\sigma _ { e x }$ se calcule par la relation de comportement.

## 8.3.3 Exploitation du théorème de l’énergie potentielle

Posons $\vec { u } = \vec { u } _ { e x } + \lambda \vec { u } ^ { \star }$ avec λ réel arbitraire et $\vec { u } ^ { \star } \in \mathcal { U } _ { 0 }$ . Les conditions de minimisation de l’énergie potentielle s’obtiennent en écrivant que :

$$
\left[ \frac {\mathrm{d}}{\mathrm{d} \lambda} E _ {p} (\vec {u} _ {e x} + \lambda \vec {u} ^ {\star}) \right] _ {| \lambda = 0} = 0 \qquad \forall \vec {u} ^ {\star} \in \mathcal {U} _ {0}\tag{8.12}
$$

On a donc pour tout $\vec { u } ^ { \star } \in \mathcal { U } _ { 0 }$

$$
\int_ {\Omega} \varepsilon (\vec {u} _ {e x}): \mathbf {K}: \varepsilon (\vec {u} ^ {\star}) \mathrm{d} V = \int_ {\Omega} \vec {f} _ {d} \cdot \vec {u} ^ {\star} \mathrm{d} V + \int_ {\partial \Omega_ {T}} \vec {T} _ {d} \cdot \vec {u} ^ {\star} \mathrm{d} S\tag{8.13}
$$

Si on remplace $\mathbf { K } : \varepsilon ( \vec { u } _ { e x } )$ par $\sigma _ { e x } ,$ on retrouve la formulation globale de l’équilibre.

## 8.3.4 Théorème de l’énergie complémentaire

Théorème 8.12 La solution exacte en contrainte $\sigma _ { e x }$ est solution du problème de minimisation :

$$
\min _ {\sigma \in \mathcal {S} _ {a d}} E _ {c} (\sigma) \qquad s o i t \qquad \sigma_ {e x} = \underset {\sigma \in \mathcal {S} _ {a d}} {\arg \min} E _ {c} (\sigma)\tag{8.14}
$$

Interprétation des termes de l’énergie complémentaire $E _ { c }$

— Le terme

$$
\frac {1}{2} \int_ {\Omega} \boldsymbol {\sigma}: \mathbf {K} ^ {- 1}: \boldsymbol {\sigma} \mathrm{d} V
$$

correspond à l’énergie de déformation (élastique) exprimée en contrainte.

— Le terme

$$
\int_ {\partial \Omega_ {u}} \sigma \vec {n} \cdot \vec {u} _ {d} \mathrm{d} S
$$

correspond au travail des efforts de liaison SA dans le déplacement imposé.

Remarque 8.2 Une fois résolu le problème précédent, la déformation $\varepsilon _ { e x }$ se calcule par la relation de comportement inverse et le champ de déplacement $\vec { u } _ { e x }$ par intégration.

## 8.4 Propriétés complémentaires

## 8.4.1 Encadrement de l’énergie exacte

Soit $\left( \vec { u } _ { C A } , \sigma _ { S A } \right)$ un couple de solutions admissibles et $( \vec { u } _ { e x } , \sigma _ { e x } )$ le couple de solutions exactes. On a :

$$
- E _ {c} (\sigma_ {S A}) \leqslant - E _ {c} (\sigma_ {e x}) = E _ {p} (\vec {u} _ {e x}) \leqslant E _ {p} (\vec {u} _ {C A})\tag{8.15}
$$

## 8.4.2 Théorème de Pythagore dans l’espace des contraintes $\boldsymbol { S }$

Soit $\left( \vec { u } _ { C A } , \sigma _ { S A } \right)$ un couple de solutions admissibles et $( \vec { u } _ { e x } , \sigma _ { e x } )$ le couple de solutions exactes.

Proposition 8.13 Théorème de Prager-Synge (équivalent de Pythagore) :

$$
\| \sigma_ {S A} - \mathbf {K}: \varepsilon (\vec {u} _ {C A}) \| _ {\mathcal {S}} ^ {2} = \| \sigma_ {e x} - \sigma_ {S A} \| _ {\mathcal {S}} ^ {2} + \| \sigma_ {e x} - \mathbf {K}: \varepsilon (\vec {u} _ {C A}) \| _ {\mathcal {S}} ^ {2}\tag{8.16}
$$

![image](Images/IMMC_CM_Chap8_2024-2025_01.jpg)


Figure 8.1 – Théorème de Pythagore dans l’espace des contraintes.


Par conséquent, on a les majorations :

$$
\begin{array}{r} \left\| \sigma_ {e x} - \sigma_ {S A} \right\| _ {\mathcal {S}} \leqslant \left\| \sigma_ {S A} - \mathbf {K}: \varepsilon (\vec {u} _ {C A}) \right\| _ {\mathcal {S}} \\ \left\| \sigma_ {e x} - \mathbf {K}: \varepsilon (\vec {u} _ {C A}) \right\| _ {\mathcal {S}} \leqslant \left\| \sigma_ {S A} - \mathbf {K}: \varepsilon (\vec {u} _ {C A}) \right\| _ {\mathcal {S}} \end{array}\tag{8.17}
$$

Si on pose $\widetilde { \boldsymbol { \sigma } } = \frac { \boldsymbol { \sigma } _ { S A } + \mathbf { K } : \varepsilon ( \vec { u } _ { C A } ) } { 2 }$ , on a aussi :

$$
\| \sigma_ {e x} - \widetilde {\sigma} \| _ {\mathcal {S}} = \frac {\| \sigma_ {S A} - \mathbf {K} : \varepsilon (\vec {u} _ {C A}) \| _ {\mathcal {S}}}{2}\tag{8.18}
$$
