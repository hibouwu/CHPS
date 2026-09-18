---
marp: true
theme: default
paginate: true

---

# **Programmation Orientée Objet pour le Calcul Scientifique : Part I Survival kit** 面向科学计算的面向对象编程：第一部分 生存工具包

---

# Organisation du cours 课程安排

Sous forme d'**Item**, se raccrochant à quatre catégories :
以条目形式呈现，归属于四个类别：

- **Outils et Langage (TooL)**
**工具与语言（TooL）**
- Orienté objet (OO)
面向对象（OO）
- Gestion de la mémoire (Mem)
内存管理（Mem）
- Programmation statique (Static)
静态编程（Static）

Vous n'êtes pas seul : <https://en.cppreference.com/w/> est votre allié...
你并不孤单：<https://en.cppreference.com/w/> 是你的盟友...
et les LLM ! Mais pas pour coder à votre place...!!
还有各类 LLM！但不是用来替你写代码...!!

---

# Item 1 : C++, un langage compilé C++：一种编译型语言

Un point de départ : la fonction `main`
出发点：`main` 函数

```c++
int main() {
    return 0;
} // Votre premier programme C++ prog.cpp (ou .cxx, .cc, .c++)
```

Prototype de fonction :
函数原型：

```shell
type_retour nom_ma_fonction(arguments_ou_pas){
    corps de la fonction;
}
```

---

# Item 1 : C++, un langage compilé C++：一种编译型语言

Comment compiler ? **1/3**
如何编译？**1/3**

- Pour démarrer : en ligne !
先从在线环境开始！
  - <http://coliru.stacked-crooked.com/>
  - <https://wandbox.org/>
  - <https://godbolt.org/>

**Exo 1.1** : hello C++ world compilateur en ligne
**练习 1.1**：在在线编译器中实现 hello C++ world

---

# Item 1 : C++, un langage compilé C++：一种编译型语言

Comment compiler ? **2/3**
如何编译？**2/3**

- Ensuite avec un compilateur...Quatre principaux compilateurs :
接着使用本地编译器……四个主要编译器：
  - GCC (Communauté, <https://fr.wikipedia.org/wiki/GNU_Compiler_Collection>)
GCC（社区，<https://fr.wikipedia.org/wiki/GNU_Compiler_Collection>）
  - Clang (Communauté, <https://fr.wikipedia.org/wiki/Clang>)
Clang（社区，<https://fr.wikipedia.org/wiki/Clang>）
  - MSVC (Microsoft, <https://fr.wikipedia.org/wiki/Microsoft_Visual_Studio>)
MSVC（微软，<https://fr.wikipedia.org/wiki/Microsoft_Visual_Studio>）
  - ICPC (Intel, <https://en.wikipedia.org/wiki/Intel_C%2B%2B_Compiler>)
ICPC（英特尔，<https://en.wikipedia.org/wiki/Intel_C%2B%2B_Compiler>）

---

# Item 1 : C++, un langage compilé C++：一种编译型语言

Comment compiler ? **3/3**
如何编译？**3/3**

- sous Linux, gcc et clang facilement disponibles
在 Linux 下，gcc 和 clang 可轻松获取
- sous Windows msvc et clang accessible via [Visual Studio Community](https://visualstudio.microsoft.com/fr/vs/community/)
在 Windows 上，可通过 [Visual Studio Community](https://visualstudio.microsoft.com/fr/vs/community/) 使用 MSVC 和 Clang
- sous MacOS, clang accessible via [XCode](https://apps.apple.com/fr/app/xcode/id497799835?mt=12)
在 macOS 上，可通过 [XCode](https://apps.apple.com/fr/app/xcode/id497799835?mt=12) 使用 Clang
Commande pour compiler (gcc, clang)
编译命令（gcc、clang）

```shell
> g++ hello_world.cpp -o hello_world.exe // gcc
> clang++ hello_world.cpp -o hello_world.exe // clang
> ./hello_world.exe
Hello C++ world
```

**Exo 1.2** avec votre OS et compilateur favori, refaire le hello world.
**练习 1.2**：使用你偏好的操作系统和编译器重做 hello world。

---

# Item 1 : C++, un langage compilé C++：一种编译型语言

Quelles options de compilation de base  ?
有哪些基础的编译选项？

- `-o exe_name` : positionne le nom de l'exécutable
用于指定可执行文件名称
- `-Wall` : active de nombreux warnings (obligé !) voire `-Wextra`
启用大量警告（强烈建议！），甚至可加上 `-Wextra`
- `-std=c++20`, `-std=c++17`, `-std=c++14`, `-std=c++11` : choix du standard C++
选择 C++ 标准版本
- `-g` : export des symboles pour le debug
导出调试符号
- `-02`, `-03` : option d'optimisation
优化选项
Ces options peuvent varier en fonction du compilateur (ex MSVC...)
这些选项会根据不同编译器有所差异（如 MSVC 等）。

---

# Item 1 : C++, un langage compilé C++：一种编译型语言

Deux types de fichiers existent en C++ :
在 C++ 中存在两类文件：

- les entêtes (headers) : `Filename.h`qui sont inclus
头文件（headers）：`Filename.h`，通过 include 引入
- les sources : `Filename.cpp` qui sont compilés
源文件：`Filename.cpp`，用于编译

```c++
#include <iostream> // fichier "système"
#include "Filename.h" // fichier utilisateur
```

Les fichiers *.h* permettent de mutualiser du code.
`.h` 文件用于共享代码。
Ils rendent accessibles le contrat de la fonction ou de la classe.
它们公开函数或类的契约。
A l'édition des liens, le compilateur doit trouver l'implémentation de ce contrat.
在链接阶段，编译器必须找到契约的具体实现。

- **Exo 1.3** reprendre le cas hello world : sans include iostream mais en incluant un fichier .h que vous aurez écrit.
**练习 1.3**：重新实现 hello world，去掉 `#include <iostream>`，改为引入你编写的 `.h` 文件。

---

# Item 1 : C++, un langage compilé C++：一种编译型语言

Les **IDE** ou Environnement de Développement Intégré pour gagner en productivité
通过 **IDE**（集成开发环境）来提升生产力

- gère l'édition du code (coloration syntaxique, complétion, navigation, refactoring)
管理代码编辑（语法高亮、补全、导航、重构）
- gère le système de version (git, svn,...)
管理版本控制系统（git、svn 等）
- gère la compilation du code
负责代码编译
- peut également gérer l'exécution et le debugging
还可以处理程序运行与调试
- propose un agent IA...
甚至提供 AI 助手……

---

# Item 1 : C++, un langage compilé C++：一种编译型语言

**IDE C++** les plus connues :
最知名的 **C++ IDE**：

- Visual Studio, Visual Studio Code (Microsoft)
Visual Studio、Visual Studio Code（微软）
- XCode (Apple)
XCode（苹果）
- CLion (JetBrains)
CLion（JetBrains）
- NetBeans (Communauté Apache Software Foundation)
NetBeans（Apache 软件基金会社区）
- Eclipse CDT (Communauté Eclipse Foundation)
Eclipse CDT（Eclipse 基金会社区）

---

# Item 2 : Types de bases et structure de contrôle C++ 基本类型与控制结构

Les types de bases proches du C, <https://en.cppreference.com/w/cpp/language/types>
基础类型与 C 语言相近，<https://en.cppreference.com/w/cpp/language/types>

- entier : `int`
  - `short`/`long int`, `signed`/`unsigned`
- réel : `float`, `double`, `long double`
- caractère : `char` (`char8_t`,`char16_t`,`char32_t`)
- booléen : `bool`

---

# Item 2 : Types de bases et structure de contrôle C++ 基本类型与控制结构

Tailles et plage de valeurs (architecture 64 bits) 1/2
大小与取值范围（64 位架构）1/2

|*Types*| Taille (bits) |Format |étendue |
|---|---|---|---
|`char` | 8 | signed 
 unsigned | $-128...127$ 
 $0...255$  |
|`char16_t` | 16 | signed
unsigned | $\approx$ $\pm3.10^{4}$
 $\approx$ $6.10^{4}$ |
|`int` | 32 | signed
unsigned | $\approx$ $\pm2.10^{9}$
 $\approx$ $4.10^{9}$ |

---

# Item 2 : Types de bases et structure de contrôle C++ 基本类型与控制结构

Tailles et plage de valeurs (architecture 64 bits) 2/2
大小与取值范围（64 位架构）2/2

|*Types*| Taille (bits) |Format |étendue |
|---|---|---|---
|`long long int` | 64 | signed
unsigned | $\approx$ $\pm9.10^{18}$
 $\approx$ $2.10^{19}$ |
|`float` | 32 | [IEE754](https://en.wikipedia.org/wiki/IEEE-754) | $\approx$ $\pm3.10^{38}$ |
|`double` | 64 | [IEE754](https://en.wikipedia.org/wiki/IEEE-754) | $\approx$ $\pm2.10^{308}$ |

Pour ne pas se perdre utilisez les types STL : `std::int32_t`, `std::int64_t`...
为避免混淆，请使用 STL 类型：`std::int32_t`、`std::int64_t` 等。

- <https://en.cppreference.com/w/cpp/types/integer>

---

# Item 2 : Types de bases et structures de contrôle C++ 基本类型与控制结构

Les **structures de contrôle** 1/6
**控制结构** 1/6

- boucle `for (<init>;<condition>;<increment>) {<bloc>}`, identique au **C**
  循环 `for (<init>;<condition>;<increment>) {<bloc>}`，与 **C** 语言相同

```c++
for (int i = 0 ; i < nb_iterations; i++) {
    std::cout << "iteration i =  " << i << "\n";
}
```

- structure conditionnelle `if (<condition>) {<bloc>}`
条件结构 `if (<condition>) {<bloc>}`

```c++
if (condition_is_true) {
    std::cout << "My condition is true  " << std::endl;
}
```

**Exo 2.1** Afficher les entiers de 0 à 100. Puis uniquement les nombres pairs.
**练习 2.1**：输出 0 到 100 的整数，然后只输出偶数。

- Indice : l'opérateur `%` retourne le reste de la division entière...
提示：运算符 `%` 返回整数除法的余数……

---

# Item 2 : Types de bases et structures de contrôle C++ 基本类型与控制结构

Les **structures de contrôle** 2/6
**控制结构** 2/6

- structure conditionnelle `if(<init>; <condition>){<bloc>}` avec initialisation
带初始化的条件结构 `if(<init>; <condition>){<bloc>}`

```c++
if (bool condition = (n < max); condition) {
    std::cout << "My n is inferieur a max " << std::endl;
}
```

**Démo 2.1** : utilisation de l'initialisation dans la boucle dans l'**Exo 2.1**.
**演示 2.1**：在 **练习 2.1** 的循环中使用初始化。

- structure conditionnelle `if(<condition>){<bloc>} else {<bloc>}`
条件结构 `if(<condition>){<bloc>} else {<bloc>}`

```c++
if (n < max) {
    std::cout << "n < max  " << std::endl;
} else {
    std::cout << "n >= max  " << std::endl;
}
```

---

# Item 2 : Types de bases et structures de contrôle C++ 基本类型与控制结构

Les **structures de contrôle** 3/6
**控制结构** 3/6

- structure conditionnelle `if(<condition>){<bloc>} else if(<condition>) {<bloc>}`
条件结构 `if(<condition>){<bloc>} else if(<condition>) {<bloc>}`

```c++
if (i == 0) {
    i = 101;
} else if (i == 1) {
    i = 11;
} else if (i == 2) {
    i = 1;
} else {
    i++;
}
```

**Exo 2.1 (suite)** : Afficher si un nombre est un multiple de 5 ou s'il est un multiple de 2 ou s'il n'est aucun des deux.
**练习 2.1（续）**：判断一个数是否是 5 的倍数，或是否是 2 的倍数，或都不是。

---

# Item 2 : Types de bases et structures de contrôle C++ 基本类型与控制结构

Les **structures de contrôle** 4/6
**控制结构** 4/6

- structure tant que `while`
`while` 循环结构

```c++
while (condition_is_true) {
    std::cout << "still doing an operation." << std::endl;
}
```

- structure faire tant que : `do <bloc> while <condition>`
`do <bloc> while <condition>` 形式的“先做后判”结构

```c++
int i = 0;
do {
    i++;
} while (i < 5);
```

**Exo 2.2** : écrire de deux façon différente (`while` et `do-while`) les 10 premiers entiers.
**练习 2.2**：分别使用 `while` 与 `do-while` 输出前 10 个整数。

---

# Item 2 : Types de bases et structures de contrôle C++ 基本类型与控制结构

Les **structures de contrôle** 5/6 : compléments
**控制结构** 5/6：补充

- Si une `condition` est définie comme l'union de plusieurs opérations, arrêt à la première évaluation fausse
若一个 `condition` 由多个操作组成，一旦某次求值为假即停止继续求值

```c++
int z,i = 0;
if (z > 0 && i ==3){...} // expression (i == 3 ) n'est pas évaluée
```

- Il est possible pour toutes les structures de contrôle d'omettre le scope {},
对所有控制结构，都可以省略 `{}` 作用域，
  - si **une seule ligne d'instruction**
  - 若仅有 **单行指令**

    ```c++
    if (i > 5) std::cout << i << std::endl;
    int a = 0;
    for (int i = 0 ; i < 5 ; ++i) a+=i;
    //  Attention peut être source d'erreur, à éviter...
    ```

---

# Item 2 : Types de bases et structures de contrôle C++ 基本类型与控制结构

Les **structures de contrôle** 6/6 : compléments
**控制结构** 6/6：补充

- deux instructions pour les boucles (`for`,`while`, `do while`) :
循环（`for`、`while`、`do while`）的两条指令：
  - `break` : sortie de la boucle
  - `break`：退出循环
  - `continue` : sortie de l'itération courante
  - `continue`：跳过当前迭代

    ```c++
    while (true) {
        break; // sortie d'une boucle qui serait infini
    }
    for (int i = 0; i < 10; i++) {
        if (i == 5) continue; // l'itération 5 est sautée
        ...
    }
    ```

- l'instruction de contrôle ```switch```sera vu dans l'item 5, associée aux `enum class`.
控制语句 ```switch``` 将在第 5 个单元中介绍，与 `enum class` 相关。

---

# Item 3 : Créez et manipulez vos variables 创建并操控变量

Initialisation : tous les coups sont permis `()`,`{}`,`=`
初始化：`()`、`{}`、`=` 均可使用

```c++
bool  a = true;
int   b(1); 
float c{3.14}; // initialisation uniforme recommandée ; plus robuste
```

Un seul mot d'ordre : **initialisez toujours vos variables**. Une variable non initialisée est un bug potentiel.
唯一准则：**务必初始化你的变量**。未初始化的变量是潜在的缺陷。

---

# Item 3 : Créez et manipulez vos variables 创建并操控变量

Les opérateurs en C++ du simple au double: `+=-<>&|,++==--<<>>&&||`
从单目到双目的 C++ 运算符：`+=-<>&|,++==--<<>>&&||`

```c++
int i = 1 + 2 ;
bool true_exp = i <= 3;
bool false_exp = i == 1;

i++; // j = i; i = i + 1; return j;
++i; // i = i + 1; return i;

false_exp = true && false;// ET logique, ne pas confondre avec & (bit à bit)
true_exp = true || false; // OU logique, ne pas confondre avec | (bit à bit)

#include <iostream>
std::cout << "Voici l'opérateur de flux" << std::endl;
int valeur_saisie_au_clavier;
std::cin >> valeur_saisie_au_clavier;
```

---

# Item 3 : Créez et manipulez vos variables 创建并操控变量

Les opérateurs en C++ variations autour de = : `+=,-=,*=,/=,%=,%,!=`
围绕 `=` 的 C++ 运算符变体：`+=,-=,*=,/=,%=,%,!=`

```c++
int i = 1 ;
i+=2 ; // i = i + 2
i-=1;  // i = i - 1
i*=3;  // i = i * 3
i/=2;  // i = i / 2
i%=2;  // i = i %2; => % donne le reste de la division entière

bool true_exp = 2 != 3; // NON EGAL, opérateur logique

```

---

# Item 3 : Créez et manipulez vos variables 创建并操控变量

L'**opérateur ternaire** : `(<condition>) ? true_case : false_case`
**三元运算符**：`(<condition>) ? true_case : false_case`

```c++
int i = 1 ;
(i % 2 == 0) ? std::cout << "even" : std::cout << "odd";
```

L'**opérateur virgule** : `<instruction 1> , <instruction 2>`
**逗号运算符**：`<instruction 1> , <instruction 2>`
exécute les instructions et retourne le résultat de la dernière
执行每条指令，并返回最后一条指令的结果

```c++
int n = 1;
int m = (++n, n+=2, 2 * n); // m = 8 (这三个操作依次执行，m 取最后一个操作的结果)
std::cout << "m = " << (++m, m) << '\n';
```

**Exo 3.1** : combien vaut m ?
**练习 3.1**：`m` 的值是多少？

**ans :** `m = 9`

---

# Item 3 : Créez et manipulez vos variables 创建并操控变量

Ordre des opérations, ne perdez pas le fil...
运算顺序，别跟丢了……

```c++
int i = 1 + 2 + 3 + 4; // ((1+2)+3)+4)
int j = 1 + 2 * 3 + 4; // ((1+(2*3))+4)

bool b = true && false && true; //((true && false) && true)
bool c = true || false && true; // (true || (false && true ))
int k;
i = j = k = 0; // (i = (j = (k = 0)))
```

**Exo 3.2** : prévoir l'ordre des opérations ci-dessus.
**练习 3.2**：预测上述表达式的运算顺序。

---

# Item 3 : Créez et manipulez vos variables 创建并操控变量

Ordre des opérations, ne perdez pas le fil...
运算顺序，别跟丢了……

```c++
// opérateurs arithmétiques et logiques : gauche à droite en respectant priorités
int i = 1 + 2 + 3 + 4; // ((1+2)+3)+4)
int j = 1 + 2 * 3 + 4; // ((1+(2*3))+4)

bool b = true && false && true; //((true && false) && true)
bool c = true || false && true; // (true || (false && true ))

// opérateurs d'affectation droite à gauche
int k;
i = j = k = 0; // (i = (j = (k = 0)))
```

Tous les détails : <https://en.cppreference.com/w/cpp/language/operator_precedence>
完整细节：<https://en.cppreference.com/w/cpp/language/operator_precedence>

---

# Item 4 : Premiers pas avec les fonctions 函数入门

Les **fonctions** 1/8 :
**函数** 1/8：

- prennent des arguments en entrée ou entrée/sortie, ou non
可接收输入参数、输入/输出参数，或没有参数
- produisent une sortie (mot clé `return`), ou non
可返回值（使用关键字 `return`），也可以没有返回值
- s'écrivent avec le prototype suivant :
函数原型形式如下：
`<out> fonction(<in_or_out_arguments...>) {<instruction bloc>}`

```c++
// No in nor out
void hello_world() {std::cout << "Hello function world";}
// No out, int in
void func(int i) {std::cout << "Value is " << i;}
// int out, two int in
int func2(int i, int j) { return i+j; }
```

---

# Item 4 : Premiers pas avec les fonctions 函数入门

Les **fonctions** 2/8 :
**函数** 2/8：

- sont appelées avec leurs arguments par la syntaxe : `func(<in_or_out_arguments...>);`
通过语法 `func(<in_or_out_arguments...>);` 调用并传入参数

```c++
int main() {
    hello_world();// No in nor out
    func(1);// No out, int in
    int result = func2(1,2);// int out, two int in
```

**Exo 4.1** Ecrivez une fonction retournant la somme de trois flottants et appelez la dans un programme principal.
**练习 4.1**：编写一个返回三个浮点数之和的函数，并在主程序中调用它。

---

# Item 4 : Premiers pas avec les fonctions 函数入门

Les **fonctions** 3/8 :
**函数** 3/8：

- peuvent être définies  en deux blocs distincts :函数可以分为两个独立部分：
  - la déclaration = le prototype de la fonction
  - 声明 = 函数原型

    ```c++
    void hello_world();
    ```

  - la définition = le corps de la fonction (on rappelle le prototype)

    ```c++
    void hello_world() {std::cout << "Hello function world";}
    ```

    Permet par exemple d'**exposer le prototype** de la fonction dans un fichier `.h`
    **sans exposer l'implémentation** de la fonction 'cachée' dans un fichier `cpp`
    这样可以在 `.h` 文件中**暴露函数原型**，同时让函数实现“隐藏”在 `cpp` 文件中。

---

# Item 4 : Premiers pas avec les fonctions 函数入门

Les **fonctions** 4/8 :
**函数** 4/8：

- peuvent être définies  en deux blocs distincts :
函数可以拆分为两个独立部分：
  - la déclaration = le prototype de la fonction
  - 声明 = 函数原型

    ```c++
    void hello_world();
    ```

  - la définition = le corps de la fonction (on rappelle le prototype)

    ```c++
    void hello_world() {std::cout << "Hello function world";}
    ```

**Exo 4.2** Séparer la déclaration de la définition de votre fonction de l'**Exo 4.1**. Essayez de l'appeler avec uniquement la déclaration.
**练习 4.2**：将 **练习 4.1** 的函数声明与定义分离，尝试仅凭声明进行调用。

---

# Item 4 : Premiers pas avec les fonctions 函数入门

Les **fonctions** 5/8 :
**函数** 5/8：

- peuvent avoir des valeurs par défaut
可以拥有默认值
  - doivent être placés à la fin de la liste des arguments
必须放在参数列表的末尾
  - le ou les arguments peuvent alors être omis lors de l'appel à la fonction
因此在调用时可以省略这些参数

```c++
int func2(int i, int j = 0);
int func2(int i, int j) { return i+j; }
int main() {
    int res = func2(1); // i =1, j = 0
}
```

Attention la valeur par défaut ne doit être **précisée qu'une seule fois** :
**dans la déclaration ou la définition**
注意默认值**只能指定一次**：要么在声明中，要么在定义中。

---

# Item 4 : Premiers pas avec les fonctions 函数入门

Les **fonctions** 6/8 :
**函数** 6/8：

- peuvent avoir des valeurs par défaut
可以拥有默认值
  - doivent être placés à la fin de la liste des arguments
必须安排在参数列表末尾
  - le ou les arguments peuvent alors être omis lors de l'appel à la fonction
调用函数时可以省略这些参数

```c++
int func2(int i, int j = 0);
int func2(int i, int j) { return i+j; }
int main() {
    int res = func2(1); // i =1, j = 0
}
```

**Exo 4.3** Ajouter une valeur par défaut dans votre fonction des **Exo 4.1** et **Exo 4.2**.
**练习 4.3**：为 **练习 4.1** 与 **练习 4.2** 中的函数添加默认值。

---

# Item 4 : Premiers pas avec les fonctions 函数入门

Les **fonctions** 7/8 :
**函数** 7/8：

- peuvent appeler d'autres fonctions
可以调用其他函数

```c++
void hello_world() {std::cout << "Hello function world";}

int func2(int i, int j) { 
    hello_world();
    return i+j; 
}
```

La fonction principale `main`est elle-même une fonction qui en appelle d'autres...
主函数 `main` 本身就是一个会调用其他函数的函数……

---

# Item 4 : Premiers pas avec les fonctions 函数入门

Les **fonctions** 8/8 :
**函数** 8/8：

- peuvent s'appeler elle-même **récursivement**
可以**递归地**调用自身

```c++
void recursive_function(int nb_call) { 
    if (nb_call <= 0) return; // stop recursion (otherwise infinite)
    else {
        std::cout << "Recursive call nb : " << nb_call << std::endl;
        recursive_function(--nb_call);
    }
}
```

Attention à bien mettre une **condition d'arrêt** dans la fonction récursive...
请务必在递归函数中设置**终止条件**……

---

# Item 5 : jouer avec les types 玩转类型

**Type constant** : il est possible en C++ de définir un type constant :
**常量类型**：在 C++ 中可以定义常量类型：

- `<type> const my_var;`
- `const <type> my_var;`
Une variable de ce type ne pourra alors **pas être modifiée** et doit **être initialisée**.
此类变量将**不可修改**，并且必须**已初始化**。

```c++
const int i; // ERROR 未初始化i的值
const int a = 3;
a = 2; // ERROR 尝试修改常量
float const pi = 3.1416;
pi = 0; // ERROR 尝试修改常量
```

---

# Item 5 : jouer avec les types 玩转类型

**Inférence de type** : késako ? **1/4**
**类型推断**：这是什么？**1/4**
C'est la possibilité pour le compilateur de déduire le type d'une variable.
即编译器可以推断变量类型的能力。
Les mot-clés associés sont `auto`et `decltype`
相关关键字是 `auto` 和 `decltype`

- `auto` vous permet de déclarer une variable sans préciser son type.
`auto` 允许你在声明变量时不显式指定类型。

```c++
auto i = 1; // i is deduced to be an int.
auto f = 5.5f; // F is deduced to be a float.
auto z; // ERROR !
```

Il est alors **obligatoire d'initialiser les variables**.
此时**必须初始化变量**。

---

# Item 5 : jouer avec les types 玩转类型

**Inférence de type** : késako ? **2/4**
**类型推断**：这是什么？**2/4**

- `auto` vous permet de déclarer une variable sans préciser son type.
`auto` 允许在声明变量时省略类型。

Ce mot clé apporte trois avantages substantiels
该关键字带来三大优势

- les variables sont toujours initialisées ;
变量始终被初始化；
- plus d'erreur liée à des conversions de type implicite ;
避免隐式类型转换导致的错误；
- le code est générique : un changement de type  à l'avenir aura moins d'impact.
代码更具泛化能力：未来更改类型时影响更小。

D'où la règle **AAA** : Almost Always Auto.
因此有 **AAA** 原则：Almost Always Auto（几乎总是使用 auto）。

声明时必须有初始化值；否则编译器无从推断（auto z; 报错）。
推断的是具体类型，不是“动态类型”；auto i = 1; 得到 int，后续不能再改成别的类型。
字面量会带上前缀/后缀决定精度：5.5 推 double，5.5f 推 float，1u 推 unsigned int 等。
绑定到引用/const 时规则不同：const int x = 1; auto y = x; 得到非 const；用 const auto& y = x; 才保留 const 引用。
decltype(expr) 返回表达式的精确定义类型（含引用/const），常用于模板或想匹配已有变量/返回值类型时。

---

# Item 5 : jouer avec les types 玩转类型

**Inférence de type** : késako ? **3/4**
**类型推断**：这是什么？**3/4**

- `decltype` vous permet de déterminer le type d'une expression.
`decltype` 允许确定表达式的类型。

```c++
int i = 1;
decltype(i) j; // int j;
int const k = 2;
decltype(k) l; // int const l;
decltype(2+3) n; // int n;
```

---

# Item 5 : jouer avec les types 玩转类型

**Inférence de type** : késako ? **4/4**
**类型推断**：这是什么？**4/4**

- `decltype` vous permet de déterminer le type d'une expression.
`decltype` 可以用来确定表达式的类型。

`decltype`, à la différence d'`auto` déduit exactement le type, y compris :
与 `auto` 不同，`decltype` 会精确推导类型，包括：

- son caractère `const` ;
其 `const` 属性；
- sa caractéristique mémoire le cas échéant : pointeur `*` ou référence `&`
在需要时的内存特性：指针 `*` 或引用 `&`
    (cf. Items à venir sur la gestion mémoire).
    （参见后续关于内存管理的章节。）

---

# Item 5 : jouer avec les types 玩转类型

Définition d'un **alias de type** : mot clé `using`
定义**类型别名**：关键字 `using`
On renomme un type `using <alias> = type`
我们通过 `using <alias> = type` 来重命名类型

```c++
using integer = int;
using    real = double;

integer i = 0;
   real a = 1.0;
```

Cela permet :
这样做可以：

- d'améliorer la lisibilité du code ;
提升代码可读性；
- d'augmenter la généricité :
提高泛化能力：
  - possibilité de changer un type sous-jacent sans réécrire de code.
可以在不重写代码的情况下更换底层类型。

---

# Item 5 : jouer avec les types 玩转类型

Introduction aux **espaces des nommages** : `namespace` **1/2**
**命名空间**入门：`namespace` **1/2**
Les `namespace` protègent l'accès aux types afin :  
`namespace` 用于保护类型访问，以便：

- d'éviter des conflits de noms ;
避免命名冲突；
- d'identifier la provenance des types que l'on utilise.
标识所使用类型的来源。

Syntaxe :
语法：

- **déclaration** : `namespace mon_namespace { <bloc de déclarations> }`
**声明**：`namespace mon_namespace { <bloc de déclarations> }`
- **utilisation** : `mon_namespace::ma_declaration`
**使用**：`mon_namespace::ma_declaration`

---

# Item 5 : jouer avec les types 玩转类型

Introduction aux **espaces des nommages** : `namespace` **2/2**
**命名空间**入门：`namespace` **2/2**
Syntaxe :
语法：

- déclaration : `namespace mon_namespace { <bloc de déclarations> }`
声明：`namespace mon_namespace { <bloc de déclarations> }`
- utilisation : `mon_namespace::ma_declaration`
使用：`mon_namespace::ma_declaration`

```c++
std::cout << "Hello world"; // namespace std from standard library

namespace my_namespace { // creating a namespace
    int my_int = 0; // declaring a variable inside a namespace
}
int main() {
    my_namespace::my_int +=1; // using a variable from a namespace
}
```

---

# Item 5 : jouer avec les types 玩转类型

**Conversion de types**  : `cast` **1/4**
**类型转换**：`cast` **1/4**
`cast_operator<T>(var)` = conversion dans le type `T` de la variable `var`
`cast_operator<T>(var)` 表示将变量 `var` 转换为类型 `T`
Plusieurs opérateurs :
可用的运算符：

- `static_cast<T>(var)`
- `const_cast<T>(var)`
- `reinterpret_cast<T>(var)`
- `dynamic_cast<T>(var)`

Les types `T` et `decltype(var)` doivent être compatibles...
类型 `T` 与 `decltype(var)` 必须兼容……

---

# Item 5 : jouer avec les types 玩转类型

**Conversion de types**  : `cast` **2/4**
**类型转换**：`cast` **2/4**
`cast_operator<T>(var)` = conversion dans le type `T` de la variable `var`
`cast_operator<T>(var)` 表示将变量 `var` 转换为类型 `T`
Plusieurs opérateurs :
可用的运算符：

- `static_cast<T>(var)` : conversion avec vérification à la compilation
  - `static_cast<T>(var)`：在编译期进行检查的转换

```c++
float pi = 3.14f;
double pi_dp = static_cast<double>(pi);
```

- `dynamic_cast<T>(var)`  : conversion dynamique au runtime.
  - Souvent utilisée pour des conversions entre classes (cf Items Orienté Objet)

---

# Item 5 : jouer avec les types 玩转类型

**Conversion de types**  : `cast` **3/4**
**类型转换**：`cast` **3/4**
`cast_operator<T>(var)` = conversion dans le type `T` de la variable `var`
`cast_operator<T>(var)` 表示将变量 `var` 转换为类型 `T`
Plusieurs opérateurs :
可用的运算符：

- `reinterpret_cast<T>(var)` : opérateur magique ne se soucie pas de la correspondance de type, uniquement d'un accord de tailles entre les 2 types
  - `reinterpret_cast<T>(var)`：神奇的运算符，只关心两种类型大小匹配，不管类型兼容性
- `const_cast<T>(var)` : suppression de la composante const du type
  - `const_cast<T>(var)`：移除类型的 const 成分

```c++
int i = 3;
int const& j = i;
const_cast<int&>(j) = 4; // no more const. now i = 4;
```

---

# Item 5 : jouer avec les types 玩转类型

**Conversion de types**  : `cast` **4/4**
**类型转换**：`cast` **4/4**
Remarque : l'utilisation de `cast` est **rarement bon signe...**
注意：使用 `cast` **往往不是好兆头……**

- C'est un outil qui permet de violer les règles établies...
  - 它是一种可以突破既定规则的工具……

- C'est souvent (même si pas toujours) un signe de problème de conception...
  - 它通常（即使不绝对）是设计有问题的征兆……

---

# Item 5 : jouer avec les types 玩转类型

**```enum class```** : la classe pour les enum...
**```enum class```**：枚举的现代形式……
Pourquoi utiliser des énumérations ? Essayons sans :
为什么要使用枚举？先尝试不用：

```c++
// Switch between resolution methods: wrong way
int main() {}
    std::string resolution_method{"method1"};

    if (resolution_method == "method1") std::cout << "compute with method1" << std::endl;
    else if (resolution_method == "method2") std::cout << "compute with method2" << std::endl;
    // ...
    else std::cout << "Wrong resolution method." << std::endl;
}
```

- pas robuste (faute de frappe...)
不够鲁棒（很容易拼写错误……）
- les différentes méthodes possibles ne sont pas exposées
所有可能的方法没有显式列出
- risque d'oublier le cas défaut : choix d'une méthode incorrecte.
容易遗漏默认情况：可能选择错误的方法。

---

# Item 5 : jouer avec les types 玩转类型

**```enum class```** : la classe pour les enum...
**```enum class```**：枚举的现代形式……
Pourquoi utiliser des énumérations ? Essayons avec :
为什么要使用枚举？试着用它：

```c++
// Switch between resolution methods: good way
enum class ResolutionMethod {Method1, Method2};
auto resolution_method = ResolutionMethod::Method1;
switch (resolution_method) {
    case ResolutionMethod::Method1: std::cout << "compute with method1" << std::endl;
        break;
    case ResolutionMethod::Method2: std::cout << "compute with method2" << std::endl;
        break;
}
```

- robuste (aide du compilateur, tous les cas doivent être dans le switch)
更加稳健（编译器辅助，`switch` 中必须覆盖所有情况）
- les différentes méthodes possibles exposées dans l'```enum```
所有可能的方法都在 ```enum``` 中一目了然
- le défaut est géré automatiquement
默认情况将自动得到处理

---

# Item 5 : jouer avec les types 玩转类型

**Exo 5.1** Réalisez un code permettant de choisir entre un affichage des 10 premiers entiers par une boucle for et un affichage par une boucle while. Réalisez deux versions de ce code, l'une avec `if/elseif` et l'autre avec `switch`.
**练习 5.1**：编写代码，实现选择使用 for 循环或 while 循环输出前 10 个整数的功能。完成两个版本：一个使用 `if/elseif`，另一个使用 `switch`。

# Item 5 : jouer avec les types 玩转类型

Pour aller plus loin : évolution des `enum class` dans le standard C++ :
进一步了解：C++ 标准中 `enum class` 的演进：

- <https://www.cppstories.com/2024/enum-improvements/>
