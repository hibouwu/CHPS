[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/-YJ44HPN)

# Lab3 - Transformateur d'Images

Un programme C pour appliquer diverses transformations sur des images BMP à l'aide d'un système de graphe de traitement.

## Fonctionnalités

- **Chargement et sauvegarde** d'images BMP
- **Transformations d'images** :
  - Conversion en niveaux de gris
  - Inversion des couleurs
  - Quantification des couleurs
  - Rotation de 90° dans le sens horaire
- **Traitement par pipeline** via des fichiers de configuration

## Construction du projet

### Prérequis
- CMake 3.15 ou plus récent
- Compilateur C (GCC ou Clang)
- Makefile

### Compilation

```bash
# Configuration du projet
cmake -B build -DCMAKE_BUILD_TYPE=Debug .

# Compilation
cmake --build build
# ou
make -C build
```

### Utilisation

```bash
./build/mytransform <fichier_pipeline>

```

Exemple de fichier pipeline:
Voir `pipelines/rotate.pipeline` pour un exemple de configuration.

## Tests

```bash
# Exécuter les tests unitaires
make -C build test

# Générer un rapport de couverture de code
make -C build coverage
```

Le rapport de couverture sera généré dans build/coverage/index.html.

## Structure du projet

- src - Code source principal
- include - Fichiers d'en-tête
- tests - Tests unitaires
- pipelines - Exemples de fichiers de pipeline
- images - Images d'exemple

## Bibliothèques utilisées

- stb_image - Chargement d'images
- stb_image_write - Écriture d'images
- Unity - Framework de tests unitaires

## 输入数据

大型 BMP 输入以无损 gzip 文件提供。运行实验前执行 `python3 prepare_data.py`，恢复原文件名与字节内容；解压后的文件不纳入 Git。
