# TD1 Introduction à CMake

# 1.1 Compiler un programme et une bibliothèque

**Exo** : compiler un programme utilisant une classe MyClass située dans une bibliothèque externe.
Pour cela vous devrez :

- créer un fichier main.cpp qui servira pour tester votre bibliothèque. Vous instancierez la classe MyClass de votre bibliothèque et vous appellerez sa méthode `print`, qui affichera une description de cette classe.
- créer un répertoire `mylib_dir` qui contiendra un `.h` et un `.cpp`. Ces fichiers vous permettront de définir la classe MyClass ; celle-ci devra appartenir au namespace MyLib. La classe contiendra au moins une méthode `print` que vous déclarerez dans le .h (n'oubliez pas les *include gards*) et que vous définirez dans le `.cpp`.

## 1.1.1 Manuellement (pour intuiter le fonctionnement)

- Compiler la bibliothèque en dynamique : dans le répertoire mylib_dir

`g++ -o libmylib.so -fpic -shared MyClass.cpp`

- Compiler le programme
  - naïvement `g++ main.cpp`
  - utilisez -L pour le chemin de la bibliothèque, -I pour le chemin d'include et -lnomdelalib (sans le prefix lib ni l'extension .so) pour faire fonctionner la compilation

 `g++ -Lmylib_dir -Imylib_dir main.cpp -lmylib`

 En cas d'échec, essayer `-L mylib_dir` (avec un espace).

- Exécutez le programme
  - naïvement
  - en enrichissant le LD_LIBRARY_PATH où doivent se trouver tous les chemins des bibliothèques
solution : enrichir à la volée :

- en bash : ```LD_LIBRARY_PATH=./mylib_dir ./a.out```
- en csh : ```env LD_LIBRARY_PATH=./mylib_dir ./a.out```

## 1.1.2 Avec CMake

- Un tutorial CMake est disponible sur la page : https://cmake.org/cmake/help/latest/guide/tutorial/index.html

- Créez un `CMakeLists.txt` à côté du `main.cpp`

```cmake
cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tutorial)

# enable modern C++
set(CMAKE_CXX_STANDARD 17)

# add the executable
add_executable(Main.exe main.cpp)
```

- Lancez la configuration : depuis un répertoire `build`, créé au même niveau que `main.cpp` lancez
`cmake ..` ; CMake génère alors un makefile. Essayez de compiler avec : `make` ou `cmake --build .`
  - la compilation échoue car nous n'avons pas ni
    - créé la bibliothèque `mylib` ;
    - indiqué à CMake la dépendance de `main.cpp` à `mylib`
- En suivant le tutorial CMake, réalisez ces deux étapes, en utilisant les commandes CMake :
  - `add_library` dans un nouveau `CMakeLists.txt` dans le répertoire `mylib_dir`
  - `add_subdirectory`, `target_link_libraries` et `target_include_directories` dans le `CMakeLists.txt` racine.
- Ajouter un test grâce à la commande `add_test` prenant comme arguments un nom de test et le nom de votre target `Main.exe`. Cette commande doit être précédée de la commande `enable_testing()` (sans argument). Vous pourrez alors tester votre code via la commande `ctest`.

# 1.2 Ajouter des tests

## 1.2.1 Compiler et installer GTest

- Si ce n'est pas déjà le cas, il faut installer GTest sur votre machine.
- Vous pouvre le faire via le système de paquet de votre distribution :  

```shell
sudo apt-get install libgtest-dev
```

- Si cela ne fonctionne pas suivez le *tutorial help install gtest* fourni dans le même répertoire que ce TP.

## 1.2.2 Trouver et utiliser GTest via CMake

- La doc CMake est là :
  - <https://cmake.org/cmake/help/v3.18/module/FindGTest.html?highlight=gtest#module:FindGTest>
- utilisez la commande `find_package` de CMake pour chercher GTest. Indiquez l'option `REQUIRED`.

## 1.2.3 Ajouter des tests via GTest

- Créez un nouveau fichier test.cpp.
- Créez une nouvelle target `Test.exe` de type `executable` contenant test.cpp
- utilisez la commande `target_link_libraries` pour lier votre target `Test.exe` aux deux targets de GTest : `GTest::GTest`et `GTest::Main` et à votre target `mylib`. N'oubliez pas non plus le `target_include_directories` pour pouvoir utiliser les header de mylib dans votre fichier de test.
- Créez un test de la méthode print de mylib en utilisant les macros de GTest :

```c++
#include "gtest/gtest.h"
#include "mylib.h"

// This macro creates a test case MylibTestPrintTest, of type UnitTest
TEST(UnitTest, MylibTestPrintTest){ 
  
  // Create an instance of Mylib::MyClass and test print method
}
```

- Ajoutez une méthode value dans MyClass et créez un nouveau test pour la valider. Par exemple une méthode retournant un entier que vous pourrez alors tester avec la macro gtest : `EXPECT_EQ(val1,val2)`
- Pour que ces tests soient utilisables depuis la commande ctest dans votre répertoire de build, vous pouvez ajouter la commande

```cmake
# Fichier CMakeLists.txt
gtest_discover_tests(Test.exe)
```

Ainsi votre projet sera compilable et testable avec les commandes (classiques) suivantes :

```shell
cmake ..
make 
ctest
```

# 1.3 Créer un code portable (BONUS)

## 1.3.1 Exporter les symboles

Afin de vous assurer que votre code est bien cross-compilable (ie compilable sur d'autres plateformes), il est utilise de désactiver l'export automatique de symboles, car celui-ci n'est pas actif sous Windows. Pour cela utiliser l'option de gcc `-fvisibility=hidden`.

- Essayer de compiler votre code avec cette option
  - pour passer cette option à CMake, utilisez l'option `CMAKE_CXX_FLAGS`, ou mieux la commande `target_compile_options`
- Corriger le code de votre bibliothèque pour réparer l'édition des liens.

## 1.3.2 Déployer votre code

S'il vous reste du temps mettez en place l'installation de votre bibliothèque dans le CMake, de sorte qu'un simple `find_package(my_lib)` + `target_link_libraries(mylib)` dans un code utilisateur permette d'utiliser votre bibliothèque.