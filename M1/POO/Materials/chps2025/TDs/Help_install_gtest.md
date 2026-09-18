# Installation Gtest

Cette section est nécessaire uniquement si vous n'avez pas les droits suffisants pour installer gtest via le gestionnaire de paquet de votre distribution. Il faut alors compiler/installer/ajouter dans le Path, la bibliothèque.

## Récupérer les sources

Sur la page https://github.com/google/googletest/releases/tag/release-1.10.0 vous pouvez télécharger le fichier .tar.gz (lien `Source Code`: https://github.com/google/googletest/archive/release-1.10.0.tar.gz). Créez-vous un répertoire gtest à l'emplacement de votre choix.

```shell
mkdir gtest
```

Créez ensuite un répertoire pour les sources (src) un répertoire pour compiler (build) et un répertoire pour installer (install)

```shell
cd gtest
mkdir src
mkdir build
mkdir install
```

Vous pouvez copier le .tar.gz dans gtest/src et l'extraire :

```shell
tar xvfz  googletest-release-1.10.0.tar.gz
```

## Compiler Gtest

La compilation utilise CMake et se fait en deux phases : configuration (appel de cmake) et compilation (appel de make).

- Configuration : pour configurer vous devez indiquer le chemin d'installation (répertoire gtest/install) en absolu.

```shell
cd build
cmake ../src/googletest-release-1.10.0/ -DCMAKE_INSTALL_PREFIX=/absolute_path_before_gtest/gtest/install -DBUILD_SHARED_LIBS=ON
```

- compilation :

```shell
make -j 6
```

## Installer Gtest

Rien de plus simple, Make va le faire pour vous (vous lui avez indiqué où installer...)

```shell
make install
```

## Ajout dans *LD_LIBRARY_PATH*

Afin que la bibliothèque soit détectable lorsqu'elle sera utilisée, il faut l'ajouter dans la variable d'environnement *LD_LIBRARY_PATH* :

```shell
% csh ou tcsh
setenv LD_LIBRARY_PATH $LD_LIBRARY_PATH\:absolute_path_before_gtest/gtest/install/lib 
% bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:absolute_path_before_gtest/gtest/install/lib
```

## Utiliser Gtest dans un projet CMake

Pour pouvoir être trouvé dans un projet CMake (via un `find_package`) il faut positionner la variable d'environnement `$GTEST_ROOT` :

```shell
% csh ou tcsh
setenv GTEST_ROOT absolute_path_before_gtest/gtest/install
% bash
export GTEST_ROOT=absolute_path_before_gtest/gtest/install
```
