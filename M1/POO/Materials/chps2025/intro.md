---
marp: true
theme: default
paginate: true

---

# **Programmation Orientée Objet pour le Calcul Scientifique : Introduction**

---

# Introduction

- Les langages du calcul scientifique
- Pourquoi de l'orienté objet en calcul ?
- Pourquoi C++ ?
- Quelles perspectives ?

---

# Les langages du calcul scientifique

- les bases : des langages 'bas-niveaux' et 'parallèles'
  - Fortran
  - C
  - C++
- les nouveaux venus
  - Python
  - Julia...
  - voir le cours :  <http://lmfa.ec-lyon.fr/IMG/pdf/langages.pdf>

---

# Fortran

- le langage du calcul scientifique (et de rien d'autre)
- langage nativement non objet ; évolution récente vers l'objet
- Pours
  - écriture adaptée au calcul
  - gestion simple de la mémoire et des tableaux
  - beaucoup de legacy code
- Contres
  - pas un langage d'informaticien
    - faible communauté, réservé à la seule communauté scientifique
    - peu d'outils (IDE, compilateur : surtout Intel)
    - Lenteur dans la mise à disposition des nouveautés de la norme

---

# C Programming Langage

- le langage de base de l'informatique
- langage impératif (non objet)
- Pours
  - très large communauté
  - de nombreux outils
  - beaucoup de legacy code
- Contres
  - pas d'orienté objet (avantage ?)
  - gestion complexe de la mémoire (à la main)
  - langage vieillissant (arrivée de Go)

---

# C++

- le langage de base de l'orienté objet
- Pours
  - très large communauté
  - nombreux outils
  - beaucoup de legacy code
  - nouvelle norme tous les 3 ans
  - langage très riche
- Contres
  - langage trop riche ?
  - gestion complexe de la mémoire (smart pointeurs)
  - de plus en plus un langage d'expert

---

# Python

- le langage (de script) le plus en vogue aujourd'hui ?
- Pours
  - simplicité et expressivité
  - gestion de la mémoire
  - langage interprété
  - outillage (NumPy, SciPy, Pandas, TensorFlow, PyTorch)
- Contres
  - langage interprété !
  - performance native
  - évolutivité et rétro-compatibilité
  - passage à l'échelle difficile

---

# Comparatif

|*Langages*   |Fortran|C   |C++   |Python   |
|---|---|---|---|---|
|Orienté objet   |Pas nativement  |Non   |Oui   |Oui   |
|Gestion mémoire|Simple   |Complexe   |Très complexe   |Simple   |
|Performance  |Oui   |Oui   |Oui   |Pas nativement   |
|Industrialisable (Grand nombre de lignes de code)|Oui|Oui|Oui|Peu adapté

---

# Pourquoi de l'orienté objet en calcul scientifique

- Pourquoi de l'orienté objet 'tout court' ?
  - architecture
  - encapsulation
  - généricité
  - évolutivité
- Pourquoi en CS ?
  - dommage de s'en priver !
  - attention à la performance

---

# Pourquoi C++

- Deux langages nativement objet dans notre liste :
  - C++
  - Python
- Ce cours focalise sur C++ :
  - Un des premiers langage orienté objet massivement utilisé
  - Beaucoup d'existants, y compris dans la communauté calcul
  - Langage complexe  méritant que l'on s'y attarde
  - Vous parlez déjà Python, non ?

---
# Quelles perspectives

- Quel avenir pour les langages du calcul scientifique ?
  - Complexité et verbosité croissante du C++

    ```c++
    [[nodiscard]] constexpr bool helloWorld() const noexcept;
    ```

  - Prolifération du Python (et dérivées) dans la communauté académique
    - Dans le contexte IA par exemple.
    - Arrivée d'un nouveau langage bas niveau (compilé) : le rust
      - offre une vraie robustesse mémoire.

---
# Quelles perspectives

- Quel avenir pour le développement logiciel
  - On ne peut pas ignorer l'aide de l'IA
  - Les agents sont directement disponibles dans les IDE
    - Copilot dans VSCode
    - Junie dans CLion...
  - Mais il ne faut pas courir avant de savoir marcher
    - Vous ne **pourrez pas profiter de l'IA sans les bases du langages**
    - C'est l'objectif de ce cours...
