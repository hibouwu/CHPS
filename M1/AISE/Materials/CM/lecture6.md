# Lecture 6: Compilation et Bibliothèques *编译与库*

## Table des matières *目录*

- [Lecture 6: Compilation et Bibliothèques *编译与库*](#lecture-6-compilation-et-bibliothèques-编译与库)
  - [Table des matières *目录*](#table-des-matières-目录)
  - [La Compilation *编译*](#la-compilation-编译)
    - [1. Pré-traitement (Preprocessing) *预处理*](#1-pré-traitement-preprocessing-预处理)
    - [Autres directives de préprocesseur courantes (其他常见预处理指令)](#autres-directives-de-préprocesseur-courantes-其他常见预处理指令)
    - [Macros prédéfinies (预定义宏)](#macros-prédéfinies-预定义宏)
    - [Exemple avancé : Prétraitement et Compilation conditionnelle (进阶示例：预处理与条件编译)](#exemple-avancé--prétraitement-et-compilation-conditionnelle-进阶示例预处理与条件编译)
    - [2. Compilation *编译*](#2-compilation-编译)
    - [3. Assemblage (Assembly) *汇编*](#3-assemblage-assembly-汇编)
    - [4. Édition des liens (Linking) *链接*](#4-édition-des-liens-linking-链接)
    - [5. Exécution (Execution) *执行*](#5-exécution-execution-执行)
    - [Détails de la compilation *编译详解*](#détails-de-la-compilation-编译详解)
  - [Bibliothèques *库*](#bibliothèques-库)
    - [Makefile](#makefile)
    - [Installation et construction des bibliothèques *安装与构建*](#installation-et-construction-des-bibliothèques-安装与构建)
    - [Compilation et liens avec la bibliothèque *编译与链接*](#compilation-et-liens-avec-la-bibliothèque-编译与链接)
    - [Chemins de recherche à l'exécution *运行时库路径*](#chemins-de-recherche-à-lexécution-运行时库路径)
    - [Export et runpath *导出与运行路径*](#export-et-runpath-导出与运行路径)
    - [Remplacement de bibliothèque sans recompiler *不重编译更换库*](#remplacement-de-bibliothèque-sans-recompiler-不重编译更换库)
  - [Débogage *调试*](#débogage-调试)
    - [Bogue *Bug / 错误*](#bogue-bug--错误)
    - [Méthodes de débogage *调试方法*](#méthodes-de-débogage-调试方法)

## La Compilation *编译*

Les processus de compilation transforment le code source écrit dans un langage de programmation en un code exécutable par la machine. Ce processus comprend plusieurs étapes clés. (编译的过程将用编程语言编写的源代码转换为机器可执行代码。该过程包括几个关键步骤。)

**Fichier cible de compilation (编译目标文件) : `main.c`**

### 1. Pré-traitement (Preprocessing) *预处理*

Cette étape traite les directives spéciales dans le code source, telles que les inclusions de fichiers et les macros. Elle prépare le code pour la compilation proprement dite. (此步骤处理源代码中的特殊指令，如文件包含和宏。它为实际的编译做好准备。)

```c
#ifndef MY_STDIO_H   //验证是否已包含，避免重复包含同一个头文件
#define MY_STDIO_H   //如果没有包含，则定义宏
#include <stdio.h>   //包含标准输入输出头文件
#include "myheader.h" //包含自定义头文件
#define VALUE 42
#define GET_VALUE(x) (x + 1)
int main() {
    printf("Value: %d\n", GET_VALUE(42));
#ifdef HELLO
    printf("Hello, World!\n");
#else
    printf("Goodbye, World!\n");
#endif

#ifdef HELLOOPTION
#if HELLOOPTION == 1
    /* */
    printf("HELLOOPTION is set to 1, from %s on line %d\n", __FILE__, __LINE__);
#elif HELLOOPTION == 2
    printf("HELLOOPTION is set to 2, from %s on line %d\n", __FILE__, __LINE__);
#else
    printf("HELLOOPTION is set to an unknown value\n");
#endif
#endif
    return VALUE;
}
#endif
```

### Autres directives de préprocesseur courantes (其他常见预处理指令)

- `#include`：包含头文件
- `#define`：定义宏
- `#undef`：取消宏定义
- `#ifdef` / `#ifndef`：条件编译
- `#if` / `#elif` / `#else` / `#endif`：条件编译分支
- `__FILE__`：当前文件名
- `__LINE__`：当前行号
- `__DATE__`：编译日期
- `__TIME__`：编译时间
- `__VERSION__`：编译器版本

### Macros prédéfinies (预定义宏)

- `_WIN32` / `__WIN32`：Windows 平台（依编译器不同）
- `__linux__`：Linux 系统
- `__APPLE__`：Apple 系统（包括 macOS 和 iOS）
- `C_INCLUDE_PATH`：包含路径环境变量，编译器搜索头文件的路径

```bash
gcc -E main.c -o main.i -DHELLOOPTION=2
```

```c
/* Preprocessed output */
/* Contents of stdio.h and myheader.h would be included here */
int main() {
    printf("Value: %d\n", (42 + 1));
    printf("Goodbye, World!\n");
    printf("HELLOOPTION is set to 2, from %s on line %d\n", "main.c", 18);
    return 42;
}

```

### Exemple avancé : Prétraitement et Compilation conditionnelle (进阶示例：预处理与条件编译)

**Fichier / 文件 `div.h` :**

```c
#ifndef __DIV_H
#define __DIV_H

#ifdef __linux__
    #define PROGRAM "Division on Linux"
#else
    #define PROGRAM "Division on other system"
#endif

#include <stdio.h>
#define ERROR(msg) printf("%s\n", msg)

void div(float a, float b);

#endif
```

**Fichier / 文件 `div.c` :**

```c
#include <stdio.h>
#include "div.h"

void div(float a, float b) {
    if (b > 0)
        printf("%s: %.2f / %.2f = %.2f\n", PROGRAM, a, b, a / b);
    else
        ERROR("division by zero");
}
```

**Fichier / 文件 `hello.c` :**

```c
#include <stdio.h>
#include "div.h"

#define GET_VALUE(x) (x + 1)

int main() {
#ifndef HELLO
    printf("Hello from %s\n", __FILE__);
#elif HELLO == 1
    printf("Hello from mode 1\n");
#elif HELLO == 2
    printf("Value: %d\n", GET_VALUE(5));
    div(1.0, 2.0);
#endif
    return 0;
}
```

### 2. Compilation *编译*

Le compilateur traduit le code source prétraité en code assembleur spécifique à l'architecture cible. (编译器将预处理后的源代码转换为特定于目标架构的汇编代码。)

```bash
gcc -S main.i -o main.s
```

Génération d'un fichier assembleur (生成汇编文件).

Exemple de code assembleur généré (x86_64) / 生成的汇编代码示例 (x86_64) :

```asm
.file "simple-hello.c"
.text
.section .rodata
.LC0:
    .string "Hello world!"
.text
.globl main
.type main, @function
main:
.LFB0:
    .cfi_startproc
    endbr64
    pushq %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq %rsp, %rbp
    .cfi_def_cfa_register 6
    leaq .LC0(%rip), %rax
    movq %rax, %rdi
    call puts@PLT
    movl $0, %eax
    popq %rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
```

### 3. Assemblage (Assembly) *汇编*

L'assembleur convertit le code assembleur en code machine binaire (de langage assembleur), produisant des fichiers objets (.o), format ELF. (汇编器将汇编代码转换为二进制机器代码，生成 ELF 格式的目标文件 .o。)

```bash
gcc -c main.s -o main.o
```

### 4. Édition des liens (Linking) *链接*

Le linker combine les fichiers objets et les bibliothèques nécessaires pour créer un exécutable final. (链接器将目标文件和所需的库组合在一起，创建最终的可执行文件。)

```bash
gcc main.o -o executable -lm
file executable   # 确认 ELF/平台信息
```

**ELF (Executable and Linkable Format)** est le format standard pour les fichiers objets et exécutables sous Linux. (ELF 是 Linux 下目标文件和可执行文件的标准格式。)

### 5. Exécution (Execution) *执行*

L'exécutable peut maintenant être lancé sur la machine cible. (现在可以在目标机器上运行可执行文件。)

```bash
./executable
```

### Détails de la compilation *编译详解*

1. **Analyse lexicale (Lexical Analysis) *词法分析*** :
   - Le code source est divisé en unités lexicales (tokens). (源代码被划分为词法单元/标记。)
   - `int main` -> `TYPE ESPACE IDENTIFICATEUR`

2. **Analyse syntaxique (Syntax Analysis) *语法分析*** :
   - Les unités lexicales sont organisées en arbre syntaxique abstrait (AST). (词法单元被组织成抽象语法树。)

3. **Analyse sémantique (Semantic Analysis) *语义分析*** :
   - Vérification de la cohérence du code (types, portées). (检查代码一致性，如类型、作用域。)

4. **Optimisation de l'AST *AST 优化*** :
   - Amélioration de l'arbre syntaxique. (改进语法树以优化性能。)

5. **Génération de code intermédiaire *中间代码生成*** :
   - Production d'une représentation intermédiaire (IR). (生成中间表示，如三地址代码。)

6. **Optimisation du code intermédiaire *中间代码优化*** :
   - Amélioration de l'efficacité sans changer le comportement. (提高效率而不改变行为。)

7. **Génération de code assembleur *汇编代码生成*** :
   - Traduction en code machine spécifique. (转换为特定架构的机器代码。)

---

**Comparaison des compilateurs :**

- **CLANG** :
  - Étapes 1-5 : Frontend (Clang).
  - Étapes 6-7 : Backend (LLVM).
- **GCC** :
  - Étapes 1-5 : Frontend (GCC).
  - Étapes 6-7 : Backend (GCC).

> [!NOTE]
> **LLVM** est une collection d'outils réutilisables qui peut optimiser à partir de l'IR et générer du code assembleur pour différentes architectures.
> (LLVM 是可复用的工具链集合，能够基于 IR 进行优化并生成适用于不同架构的汇编代码。)

## Bibliothèques *库*

Les bibliothèques sont des collections de fonctions et de routines précompilées qui peuvent être utilisées par les programmes pour effectuer des tâches spécifiques sans avoir à réécrire le code. Elles facilitent le développement en fournissant des fonctionnalités réutilisables. (库是预编译的函数和例程的集合，无需重写代码即可复用。)

> **API (Application Programming Interface)** : Spécification d'interface entre composants logiciels. (软件组件之间的接口规范。)

### Makefile

Makefile 是一种用于自动化构建过程的文件，通常用于管理大型项目的编译和链接。它定义了一组规则，指定如何从源代码生成可执行文件或其他目标文件。Makefile 通过使用 `make` 工具来读取这些规则并执行相应的命令，从而简化了构建过程。

Deux types de bibliothèques :
bibliothèques statiques `.a`  et
bibliothèques partagées `.so`
两种类型的库：

- bibliothèques statiques `.a` : Ces bibliothèques sont liées au moment de la compilation. Le code de la bibliothèque est copié dans l'exécutable final, ce qui peut augmenter la taille du fichier exécutable. Avantage : pas de dépendance externe lors de l'exécution. Inconvénient : mise à jour difficile, car il faut recompiler l'exécutable pour intégrer les modifications de la bibliothèque.
    静态库 `.a`：这些库在编译时链接。库的代码被复制到最终的可执行文件中，这可能会增加可执行文件的大小。优点：运行时没有外部依赖,可以将程序移动到其他计算机上运行，依然有效。缺点：更新困难，因为必须重新编译可执行文件以集成库的更改。

- bibliothèques partagées `.so` : Ces bibliothèques sont chargées dynamiquement au moment de l'exécution. L'exécutable contient des références à la bibliothèque, mais le code n'est pas copié dans l'exécutable final. Avantage : mise à jour facile, car il suffit de remplacer la bibliothèque partagée sans recompiler l'exécutable. Inconvénient : dépendance externe, car la bibliothèque doit être présente sur le système lors de l'exécution.
    共享库 `.so`：这些库在运行时动态加载。可执行文件包含对库的引用，但库的代码不会被复制到最终的可执行文件中。优点：更新方便，只需替换共享库而无需重新编译可执行文件。缺点：存在外部依赖，因为库必须在运行时存在于系统中。

### Installation et construction des bibliothèques *安装与构建*

- 静态库与动态库都可以构建；也可只构建其中一种。Les bibliothèques statiques et dynamiques peuvent être construites, ou seulement l'une des deux.

| Version | 描述 |
| --- | --- |
| Statique | 直接链接到可执行文件；binaire plus gros mais autonome. |
| Dynamique | 运行时加载；binaire plus petit, dépend du chargeur et des chemins de librairie. |

- 安装目标：将库的二进制文件和头文件放到指定位置，未用包管理器时常用前缀 `/usr/local`。Objectif d'installation : déposer binaires et headers sous un préfixe (souvent `/usr/local` hors gestionnaire de paquets).
- 典型位置 Emplacements typiques：二进制库 `/usr/local/lib`，接口/头文件 `/usr/local/include`。
- `make install` 时可用变量覆盖前缀（例如 `make install PREFIX=$HOME/bin/Fibonacci`）。On peut redéfinir le préfixe via une variable lors de `make install`.
- 构建/安装流程：编译源代码 -> 生成静态/动态库 -> 将库与头文件复制到前缀路径。一旦库安装完成，可在多个程序中反复使用。Une fois la bibliothèque construite et installée, elle peut servir à un nombre arbitraire de programmes.

### Compilation et liens avec la bibliothèque *编译与链接*

- 头文件不在标准路径时，用 `-I<chemin>` 指定查找目录；库文件不在标准路径时，用 `-L<chemin>` 指定目录。Si le header n'est pas dans un chemin standard, utiliser `-I`; pour les binaires de bibliothèque hors chemin standard, utiliser `-L`.
- 链接时用小写 `-lFibonacci` 指定库名，编译器自动补全前缀 `lib` 与后缀 `.a/.so`。`-lFibonacci` indique la bibliothèque (sans `lib`), le compilateur ajoute `lib...a/.so`.
- 大写 `-L` 告诉编译器去哪个目录找库二进制。`-L` ajoute un répertoire de recherche des bibliothèques.
- 编译共享库时加 `-shared -fPIC` 生成位置无关代码；这样库加载到不同内存位置时内部跳转使用相对地址仍能工作。Pour une bibliothèque partagée, utiliser `-shared -fPIC` afin de produire du code position-independent, compatible avec un chargement à n'importe quelle adresse.
- 示例：`gcc -I/path/to/include -L/path/to/lib -lFibonacci Fibo_test.c -o fibo_test`。
- 静态链接生成的可执行文件更大（示例 ~780 KB），动态链接的可执行文件更小（示例 ~16 KB），但运行时需要能找到共享库。Un binaire statique est plus volumineux, un binaire dynamique plus léger mais dépend des bibliothèques partagées disponibles.

### Chemins de recherche à l'exécution *运行时库路径*

- 运行时装载器默认查找 `/usr/lib`、`/usr/local/lib` 等，可通过环境变量 `LD_LIBRARY_PATH` 添加自定义路径。Le chargeur cherche par défaut dans `/usr/lib`, `/usr/local/lib`, et `LD_LIBRARY_PATH` permet d'ajouter des chemins.
- 也可在链接时设置运行路径（runpath/rpath），避免每次设置环境变量。On peut fixer un runpath/rpath à l'édition de liens pour éviter de modifier l'environnement.
- 如果不想改环境变量，可用 `sudo make install` 安装到系统前缀让加载器自动找到。Installer la bibliothèque sous `/usr/local` via `sudo make install` permet au chargeur de la trouver sans variables supplémentaires.

`LD_LIBRARY_PATH` : C'est une variable d'environnement utilisée dans les systèmes Unix/Linux pour spécifier des chemins supplémentaires où le chargeur de bibliothèques dynamiques (dynamic linker) doit rechercher les bibliothèques partagées (.so) lors de l'exécution d'un programme. En définissant cette variable, les utilisateurs peuvent indiquer au système où trouver les bibliothèques nécessaires qui ne sont pas situées dans les répertoires standard du système.  `LD_LIBRARY_PATH`：这是 Unix/Linux 系统中使用的环境变量，用于指定动态链接器在运行程序时搜索共享库（.so）的额外路径。通过设置此变量，用户可以告诉系统在哪里找到不在系统标准目录中的所需库。

- 使用 `ldd <exécutable>` 检查可执行文件依赖的共享库及其路径。Utiliser `ldd <exécutable>` pour vérifier les bibliothèques partagées utilisées par un exécutable et leurs chemins.

### Export et runpath *导出与运行路径*

- `export` 只在当前终端会话有效，关闭终端后变量会消失。L'export d'une variable ne vaut que pour la session courante.
- 设置路径时用冒号分隔（Unix PATH/LD_LIBRARY_PATH）。Séparer les chemins par deux-points `:` dans PATH/LD_LIBRARY_PATH.
- 如果二进制未编译合适的 runpath，运行时可能找不到共享库。Sans runpath approprié lors de la compilation/édition de liens, le binaire peut échouer à trouver les bibliothèques partagées.
- 现有二进制的 runpath 可后期修改（如用 `patchelf` 等工具）。On peut modifier le runpath d'un binaire existant (ex. via `patchelf`).

### Remplacement de bibliothèque sans recompiler *不重编译更换库*

- 如果保持接口不变，可以替换已安装库的二进制实现（例如把简单版 fibo 换成 clever/logic 版），无需重新编译使用它的程序。Si l'interface reste identique, on peut remplacer la bibliothèque installée par une autre implémentation sans recompiler les programmes clients.
- 只要库路径/runpath/`LD_LIBRARY_PATH` 指向新库，已有可执行文件会加载新版实现，行为与旧版相同的接口契约保持兼容。Tant que le chemin de bibliothèque (runpath ou `LD_LIBRARY_PATH`) vise la nouvelle version, l'exécutable chargera la nouvelle implémentation avec la même interface.

## Débogage *调试*

### Bogue *Bug / 错误*

- Terminaison prématurée du programme (程序过早终止)
- Production d'un résultat inattendu (产生意外结果)
- Interblocage (Wait / 死锁)

### Méthodes de débogage *调试方法*

1. **Affichage (Printing)** :
   - Injection d'appels à des fonctions d'affichage comme `printf`. (注入 `printf` 等打印函数调用)
   - Méthode naïve, parfois suffisante. (朴素的方法，有时足够有效)

2. **Débogueur (Debugger / 调试器)** :
   - Générique : **GDB** (GNU Debugger).
   - Mémoire : **Valgrind** (检测内存泄漏和非法访问).
   - Précision numérique : **CADNA** (Control of Accuracy and Debugging for Numerical Applications).

3. **Traçage (Tracing / 跟踪)** :
   - Appels système : `strace`. (跟踪系统调用)
   - Chargement de bibliothèques : `LD_DEBUG=libs ./programme`. (跟踪动态库加载)
