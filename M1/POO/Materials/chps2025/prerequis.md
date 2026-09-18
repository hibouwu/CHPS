<header>
S. de Chaisemartin
</header>

# Prérequis cours CHPS/POOCS

Au cours de cet enseignement vous réaliserez deux types d'actions

- pendant les cours, de nombreux exercices d'application directe seront proposés.
- pendant les séances de TD, vous travaillerez sur un petit projet de code C++.

Au niveau du matériel, il est donc **nécessaire d'avoir un PC individuel**, de préférence sous Linux, pour chaque séance que ce soit un cours ou un TD.

## Concernant les outils **informatiques nécessaires**

### Pour les **exercices**

- pour la plupart des exercices, nous utiliserons un compilateur en ligne, au choix par exemple parmi :
  - <https://wandbox.org/>,
  - <http://coliru.stacked-crooked.com/>,
  - <https://cppinsights.io/>,
  - <https://techiedelight.com/compiler/>,
- certains exercices nécessiteront de compiler à la main dans un terminal. Il faut sur votre machine un compilateur C/C++ récent :
  - gcc >= 11.2
  - clang >= 11
  - Visual Studio 2022 (préférer Linux...)
  
### Pour les **TDs**

- pour les TDs, il nous faut un environnement de développement intégré (IDE). Je vous propose de travailler avec CLion de Jetbrains (<https://www.jetbrains.com/fr-fr/clion/>) qui est utilisable gratuitement pour les étudiants (<https://www.jetbrains.com/fr-fr/clion/buy/#discounts?billing=yearly>). Installer ce logiciel ne nécessite pas de droits administrateurs sur votre machine.
- Si possible, il serait bien d'installer la bibliothèque Google Test (gtest) sur vos machines. Cette installation doit pouvoir se faire via le gestionnaire de paquet de votre distribution Linux (`apt-get`, `rpm`, `dpkg`)* ou via `vcpkg` sur Windows. Cette installation peut nécessiter d'avoir des droits `sudo` sous Linux et administrateurs sous Windows.
- Finalement également pour les TDs nous pourrions avoir besoin de Paraview, pour de la visualisation de résultat : https://www.paraview.org/

---
\* Pour trouver si `gtest` est installée sur votre poste linux

- Ubuntu : `dpkg -s googletest`
- Debian : `apt-cache search googletest`
- RedHat/CentOS : `rpm -qa gtest`