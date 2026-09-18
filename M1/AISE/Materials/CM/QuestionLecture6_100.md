
# 100 Questions de révision - Lecture 6 : Compilation, Bibliothèques et Débogage / 100 道复习题 - 第六讲：编译、库与调试

## I. Étapes de la Compilation / 编译步骤 (1-20)

1. **Quel est le but de la compilation ? / 编译的目的是什么？**
    * Transformer un code source lisible par l'humain en code exécutable par la machine. (将人类可读的源代码转换为机器可执行的代码。)
2. **Quelles sont les 4 grandes étapes de la chaîne de compilation (Toolchain) ? / 编译工具链的 4 个主要步骤是什么？**
    * Pré-traitement, Compilation, Assemblage, Édition de liens (Preprocessing, Compilation, Assembly, Linking). (预处理，编译，汇编，链接。)
3. **Quelle commande gcc exécute seulement le pré-traitement ? / 哪个 gcc 命令只执行预处理？**
    * `gcc -E`.
4. **Que fait le préprocesseur avec les directives `#include` ? / 预处理器如何处理 `#include` 指令？**
    * Il remplace la ligne par le contenu entier du fichier inclus. (它用被包含文件的全部内容替换该行。)
5. **Que fait le préprocesseur avec les `#define` ? / 预处理器如何处理 `#define`？**
    * Il remplace textuellement toutes les occurrences de la macro par sa valeur. (它将宏的所有出现文本替换为其值。)
6. **Qu'est-ce que la compilation conditionnelle (`#ifdef`...) ? / 什么是条件编译 (`#ifdef`...)？**
    * Inclure ou exclure des parties du code source selon des conditions (ex: OS, Debug). (根据条件（如 OS，调试）包含或排除源代码的某些部分。)
7. **Quelle commande gcc génère le code assembleur (`.s`) ? / 哪个 gcc 命令生成汇编代码 (`.s`)？**
    * `gcc -S`.
8. **En quoi consiste l'étape de Compilation (proprement dite) ? / 编译（狭义）步骤包含什么？**
    * Traduction du code pré-traité en instructions assembleur spécifiques à l'architecture. (将预处理后的代码翻译成特定架构的汇编指令。)
9. **Quelle commande gcc génère le fichier objet (`.o`) ? / 哪个 gcc 命令生成目标文件 (`.o`)？**
    * `gcc -c`.
10. **Que contient un fichier objet (`.o`) ? / 目标文件 (`.o`) 包含什么？**
    * Du code machine binaire, mais non exécutable (adresses non résolues). (二进制机器代码，但不可执行（地址未解析）。)
11. **Que fait l'étape d'Édition de liens (Linking) ? / 链接步骤做什么？**
    * Combine les fichiers objets et les bibliothèques pour produire l'exécutable final. (组合目标文件和库以生成最终的可执行文件。)
12. **Quel est le format standard des exécutables sous Linux ? / Linux 下可执行文件的标准格式是什么？**
    * ELF (Executable and Linkable Format).
13. **Que signifie AST ? / AST 是什么意思？**
    * Abstract Syntax Tree (Arbre Syntaxique Abstrait).
14. **Qu'est-ce que l'analyse lexicale ? / 什么是词法分析？**
    * Découper le code en mots/tokens (Identificateurs, mots-clés...). (将代码切割成单词/标记（标识符，关键字...）。)
15. **Qu'est-ce que l'analyse syntaxique ? / 什么是语法分析？**
    * Vérifier que la structure grammaticale respecte les règles du langage (construit l'AST). (检查语法结构是否符合语言规则（构建 AST）。)
16. **Qu'est-ce que l'analyse sémantique ? / 什么是语义分析？**
    * Vérifier le sens (types cohérents, variables déclarées...). (检查意义（类型一致性，变量声明...）。)
17. **Qu'est-ce que l'optimisation de code intermédiaire ? / 什么是中间代码优化？**
    * Améliorer l'efficacité (supprimer code mort, simplifier calculs) sur une représentation indépendante de la machine. (在与机器无关的表示上提高效率（删除死代码，简化计算）。)
18. **Citez deux compilateurs C majeurs. / 列举两个主要的 C 编译器。**
    * GCC (GNU Compiler Collection) et Clang (LLVM).
19. **Quelle option de gcc active les avertissements courants ? / 哪个 gcc 选项启用常见警告？**
    * `-Wall`.
20. **Quelle option de gcc active les informations de débogage ? / 哪个 gcc 选项启用调试信息？**
    * `-g`.

## II. Bibliothèques Statiques et Dynamiques / 静态库与动态库 (21-45)

1. **Qu'est-ce qu'une bibliothèque ? / 什么是库？**
    * Une collection de fonctions précompilées réutilisables. (预编译的可重用函数集合。)
2. **Quelle est l'extension d'une bibliothèque statique sous Linux ? / Linux 下静态库的扩展名是什么？**
    * `.a` (archive).
3. **Quelle est l'extension d'une bibliothèque partagée (dynamique) ? / 共享库（动态）的扩展名是什么？**
    * `.so` (shared object).
4. **Quand le code d'une bibliothèque statique est-il intégré ? / 静态库的代码何时被集成？**
    * Au moment de la compilation (Link time). (编译（链接）时。)
5. **Quel est l'avantage principal d'une bibliothèque statique ? / 静态库的主要优点是什么？**
    * Exécutable autonome (pas de dépendance à l'exécution). (可执行文件独立（运行时无依赖）。)
6. **Quel est l'inconvénient principal d'une bibliothèque statique ? / 静态库的主要缺点是什么？**
    * Taille de l'exécutable plus grande, mise à jour difficile (recompilation nécessaire). (可执行文件较大，更新困难（需重新编译）。)
7. **Quand une bibliothèque dynamique est-elle chargée ? / 动态库何时被加载？**
    * Au moment de l'exécution (Runtime). (运行时。)
8. **Quel est l'avantage principal d'une bibliothèque dynamique ? / 动态库的主要优点是什么？**
    * Taille exécutable réduite, mise à jour facile (remplacement du fichier .so). (可执行文件较小，更新容易（替换 .so 文件）。)
9. **Quel est l'inconvénient principal d'une bibliothèque dynamique ? / 动态库的主要缺点是什么？**
    * Dépendance (DLL Hell), l'exécutable ne marche pas si la lib est absente. (依赖问题，如果库缺失则无法运行。)
10. **Quelle option gcc permet de lier avec une bibliothèque nommée `libMath.so` ? / 哪个 gcc 选项链接名为 `libMath.so` 的库？**
    * `-lMath` (on enlève `lib` et `.so`). (去掉 `lib` 和 `.so`。)
11. **Quelle option gcc ajoute un répertoire de recherche de bibliothèques ? / 哪个 gcc 选项添加库搜索目录？**
    * `-L/chemin/vers/lib`.
12. **Quelle option gcc ajoute un répertoire de recherche de fichiers d'en-tête (.h) ? / 哪个 gcc 选项添加头文件 (.h) 搜索目录？**
    * `-I/chemin/vers/include`.
13. **Que signifie `-fPIC` ? / `-fPIC` 是什么意思？**
    * Position Independent Code (Code Indépendant de la Position).
14. **Pourquoi `-fPIC` est nécessaire pour les bibliothèques partagées ? / 为什么共享库需要 `-fPIC`？**
    * Pour que le code puisse être chargé à n'importe quelle adresse mémoire virtuelle. (以便代码可以加载到任何虚拟内存地址。)
15. **Quelle commande crée une bibliothèque partagée avec gcc ? / 用 gcc 创建共享库的命令是什么？**
    * `gcc -shared -o libFoo.so foo.o`.
16. **Quelle commande liste les dépendances dynamiques d'un exécutable ? / 哪个命令列出可执行文件的动态依赖？**
    * `ldd`.
17. **Quelle variable d'environnement ajoute des chemins de recherche dynamiques ? / 哪个环境变量添加动态搜索路径？**
    * `LD_LIBRARY_PATH`.
18. **Qu'est-ce que le `rpath` (Runpath) ? / 什么是 `rpath` (Runpath)？**
    * Un chemin de recherche de bibliothèques incrusté dans l'exécutable lui-même. (在可执行文件内部嵌入的库搜索路径。)
19. **Où le système cherche-t-il les bibliothèques par défaut ? / 系统默认在哪里搜索库？**
    * `/lib`, `/usr/lib`, `/usr/local/lib`.
20. **Que fait `sudo make install` généralement ? / `sudo make install` 通常做什么？**
    * Copie les fichiers (binaires, headers) dans les répertoires système (ex: `/usr/local`). (将文件（二进制，头文件）复制到系统目录。)
21. **Comment changer le répertoire d'installation avec make ? / 如何用 make 更改安装目录？**
    * Souvent via une variable `PREFIX` (ex: `make install PREFIX=~/mylibs`).
22. **Si je mets à jour `libFoo.so` sans changer son interface, dois-je recompiler le programme ? / 如果我更新 `libFoo.so` 而不改变接口，需要重新编译程序吗？**
    * Non (Liaison dynamique). (不需要（动态链接）。)
23. **Une bibliothèque statique est-elle une archive ? / 静态库是归档文件吗？**
    * Oui (créée avec `ar`). (是的（用 `ar` 创建）。)
24. **Quelle est la convention de nommage des bibliothèques sous Linux ? / Linux 下库的命名约定是什么？**
    * `lib` + Nom + Extension (`libToto.a`, `libToto.so`).
25. **Pourquoi l'ordre des bibliothèques est-il important à l'édition de liens statique ? / 为什么静态链接时库的顺序很重要？**
    * Les symboles sont résolus séquentiellement (mettre les dépendants avant les dépendances). (符号是顺序解析的（将被依赖者放在后面）。)

## III. Préprocesseur et Macros / 预处理器与宏 (46-60)

1. **À quoi servent les "Include Guards" (`#ifndef HEADER_H`...) ? / "Include Guards" 有什么用？**
    * Empêcher l'inclusion multiple d'un même fichier d'en-tête (erreurs de redéfinition). (防止同一头文件的多次包含（重定义错误）。)
2. **Quelle macro prédéfinie donne le nom du fichier courant ? / 哪个预定义宏给出当前文件名？**
    * `__FILE__`.
3. **Quelle macro prédéfinie donne le numéro de ligne courant ? / 哪个预定义宏给出当前行号？**
    * `__LINE__`.
4. **Comment définir une constante symbolique ? / 如何定义符号常量？**
    * `#define PI 3.14`.
5. **Comment définir une macro avec arguments ? / 如何定义带参数的宏？**
    * `#define CARRE(x) ((x)*(x))`.
6. **Pourquoi faut-il parenthéser les arguments de macro ? / 为什么宏参数要加括号？**
    * Pour éviter les problèmes de priorité des opérateurs lors de l'expansion. (为了避免展开时的运算符优先级问题。)
7. **`#include <file.h>` cherche où ? / `#include <file.h>` 在哪里查找？**
    * Dans les répertoires systèmes (Standard Include Paths). (在系统目录中。)
8. **`#include "file.h"` cherche où ? / `#include "file.h"` 在哪里查找？**
    * D'abord dans le répertoire courant, puis dans les chemins systèmes. (首先在当前目录，然后是系统路径。)
9. **Comment passer une définition de macro à gcc sans modifier le code ? / 如何在不修改代码的情况下向 gcc 传递宏定义？**
    * `gcc -DNAME=VALUE`.
10. **Que fait `#undef` ? / `#undef` 做什么？**
    * Supprime une définition de macro existante. (删除现有的宏定义。)
11. **Comment détecter si on est sous Linux via préprocesseur ? / 如何通过预处理器检测是否在 Linux 下？**
    * `#ifdef __linux__`.
12. **Qu'est-ce que `C_INCLUDE_PATH` ? / 什么是 `C_INCLUDE_PATH`？**
    * Variable d'environnement pour ajouter des chemins de recherche d'includes. (添加 include 搜索路径的环境变量。)
13. **Le préprocesseur vérifie-t-il la syntaxe C ? / 预处理器检查 C 语法吗？**
    * Non, il fait juste du remplacement de texte. (不，它只做文本替换。)
14. **Peut-on utiliser `if ... else` du C dans le préprocesseur ? / 可以在预处理器中使用 C 的 `if ... else` 吗？**
    * Non, utiliser `#if ... #else`.
15. **Quelle commande permet de voir la sortie du préprocesseur ? / 哪个命令可以查看预处理器输出？**
    * `gcc -E`.

## IV. Débogage / 调试 (61-80)

1. **Quels sont les 3 types de bugs mentionnés ? / 提到的 3 种 Bug 类型是什么？**
    * Crash (Segfault), Résultat incorrect, Interblocage (Wait/Deadlock). (崩溃，结果错误，死锁。)
2. **Quelle est la méthode de débogage la plus basique ? / 最基本的调试方法是什么？**
    * Affichage (printf debugging). (打印调试。)
3. **Qu'est-ce que GDB ? / 什么是 GDB？**
    * GNU Debugger (Un débogueur interactif puissant).
4. **Comment compiler pour utiliser GDB ? / 如何编译以使用 GDB？**
    * Ajouter l'option `-g`.
5. **Que permet de faire GDB ? / GDB 允许做什么？**
    * Arrêter le programme (breakpoint), inspecter la mémoire/variables, exécuter pas-à-pas. (停止程序（断点），检查内存/变量，单步执行。)
6. **Qu'est-ce que Valgrind ? / 什么是 Valgrind？**
    * Un outil d'analyse dynamique (surtout pour la mémoire). (动态分析工具（主要是内存）。)
7. **Quelle est l'erreur détectée par Valgrind pour un accès hors tableau ? / Valgrind 检测到的数组越界错误叫什么？**
    * Invalid read / Invalid write.
8. **Quelle est l'erreur détectée par Valgrind pour un malloc non libéré ? / Valgrind 检测到的未释放 malloc 错误叫什么？**
    * Memory Leak (Fuite de mémoire).
9. **Qu'est-ce que `strace` ? / 什么是 `strace`？**
    * Un outil pour tracer les appels système (System Calls). (跟踪系统调用的工具。)
10. **Si mon programme échoue à ouvrir un fichier, quel outil utiliser ? / 如果程序打开文件失败，用什么工具？**
    * `strace` (on verra `open` retourner -1 et l'erreur). (strace（会看到 open 返回 -1 和错误）。)
11. **Comment tracer le chargement des bibliothèques ? / 如何跟踪库加载？**
    * `LD_DEBUG=libs ./programme`.
12. **Qu'est-ce que l'erreur "Undefined Reference" ? / 什么是 "Undefined Reference" 错误？**
    * Erreur de l'éditeur de liens : une fonction est appelée mais son code est introuvable (librairie manquante ou mauvais ordre). (链接器错误：调用了函数但找不到代码（缺少库或顺序错误）。)
13. **Qu'est-ce que l'erreur "Segmentation Fault" ? / 什么是 "Segmentation Fault"？**
    * Erreur d'exécution : accès mémoire illégal. (运行时错误：非法内存访问。)
14. **Peut-on déboguer un programme optimisé (`-O3`) ? / 可以调试优化过的程序 (`-O3`) 吗？**
    * Difficilement (le code machine ne correspond plus ligne à ligne au source). (很难（机器码不再与源码逐行对应）。)
15. **Qu'est-ce que CADNA ? / 什么是 CADNA？**
    * Outil pour déboguer la précision numérique (virgule flottante). (浮点数值精度调试工具。)
16. **Comment relancer la dernière commande dans GDB ? / 如何在 GDB 中重新运行上一条命令？**
    * Appuyer sur `Entrée`. (按回车。)
17. **Comment voir la pile d'appels (Traceback) dans GDB ? / 如何在 GDB 中查看调用栈？**
    * Commande `bt` (backtrace).
18. **À quoi sert `make` ? / `make` 有什么用？**
    * Automatiser la compilation (recompile seulement ce qui a changé). (自动化编译（只重编译改变的部分）。)
19. **Que contient un `Makefile` ? / `Makefile` 包含什么？**
    * Des règles (Cibles : Dépendances -> Commandes). (规则（目标：依赖 -> 命令）。)
20. **Pourquoi `make` est-il plus efficace qu'un script shell ? / 为什么 `make` 比 shell 脚本更高效？**
    * Il gère les dépendances temporelles (ne refait pas le travail inutile). (它管理时间依赖关系（不做无用功）。)

## V. Divers / 其他 (81-100)

1. **Qu'est-ce que le Backend d'un compilateur ? / 编译器的 Backend 是什么？**
    * La partie qui génère le code machine spécifique à partir de la représentation intermédiaire. (从中间表示生成特定机器码的部分。)
2. **Qu'est-ce que le Frontend d'un compilateur ? / 编译器的 Frontend 是什么？**
    * La partie qui analyse le code source (Lexing/Parsing). (分析源代码的部分。)
3. **LLVM est-il un compilateur ? / LLVM 是编译器吗？**
    * C'est une infrastructure de compilation (Clang est le compilateur C qui l'utilise). (它是一个编译基础设施（Clang 是使用它的 C 编译器）。)
4. **Qu'est-ce que "cross-compilation" ? / 什么是“交叉编译”？**
    * Compiler sur une architecture (ex: x86) pour une autre (ex: ARM). (在一个架构上为另一个架构编译。)
5. **Comment voir les sections d'un fichier ELF ? / 如何查看 ELF 文件的段？**
    * `readelf -S fichier`.
6. **À quoi sert la commande `nm` ? / `nm` 命令有什么用？**
    * Lister les symboles (fonctions, variables) d'un fichier objet/exécutable. (列出目标/可执行文件的符号。)
7. **Que signifie le symbole `U` dans `nm` ? / `nm` 中的符号 `U` 是什么意思？**
    * Undefined (Symbole utilisé mais non défini, doit être lié). (未定义（使用但未定义，需链接）。)
8. **Que signifie le symbole `T` dans `nm` ? / `nm` 中的符号 `T` 是什么意思？**
    * Text (Fonction définie dans la section code). (Text（代码段中定义的函数）。)
9. **Comment supprimer les symboles de débogage pour réduire la taille ? / 如何删除调试符号以减小大小？**
    * Commande `strip`.
10. **Qu'est-ce que `.rodata` ? / 什么是 `.rodata`？**
    * Section Read-Only Data (Constantes, chaînes littérales). (只读数据段。)
11. **Qu'est-ce que `.bss` ? / 什么是 `.bss`？**
    * Section pour les variables globales non initialisées (initialisées à 0). (未初始化全局变量段（初始化为 0）。)
12. **Qu'est-ce que `.data` ? / 什么是 `.data`？**
    * Section pour les variables globales initialisées. (已初始化全局变量段。)
13. **Comment forcer une erreur si une macro n'est pas définie ? / 如果宏未定义，如何强制报错？**
    * `#error "Message"`.
14. **Quelle est la différence entre `#include <...>` et `#include "..."` ? / `#include <...>` 和 `#include "..."` 有什么区别？**
    * `< >` pour les headers systèmes, `" "` pour les locaux. (系统头文件用 `< >`，本地用 `" "`。)
15. **Peut-on lier du code C et C++ ? / 可以链接 C 和 C++ 代码吗？**
    * Oui, mais attention au "Name Mangling" C++ (utiliser `extern "C"`). (可以，但注意 C++ 的名称修饰。)
16. **Qu'est-ce que le "Name Mangling" ? / 什么是 "Name Mangling"？**
    * Codage des noms de fonctions C++ pour inclure les types des arguments (surcharge). (编码 C++ 函数名以包含参数类型（重载）。)
17. **Pourquoi `ld` est-il rarement appelé directement ? / 为什么很少直接调用 `ld`？**
    * Car `gcc` sait comment l'appeler avec tous les bons arguments (crt0, libc...). (因为 `gcc` 知道如何带正确参数调用它。)
18. **Qu'est-ce que `pkg-config` ? / 什么是 `pkg-config`？**
    * Outil pour obtenir les flags de compilation/lien d'une bibliothèque installée. (获取已安装库的编译/链接标志的工具。)
    * `gcc main.c $(pkg-config --cflags --libs gtk+-3.0)`.
19. **Comment spécifier une bibliothèque statique explicitement à gcc ? / 如何向 gcc 显式指定静态库？**
    * Lui passer le chemin complet du `.a` ou utiliser `-Wl,-Bstatic`. (传递 `.a` 全路径或使用 `-Wl,-Bstatic`。)
20. **Quelle variable d'environnement contient les chemins des binaires (`ls`, `gcc`...) ? / 哪个环境变量包含二进制文件（`ls`, `gcc`...）的路径？**
    * `PATH`.
