# Séquence de Révision : Concepts Clés C++ (Flashcards)  C++核心概念复习序列 (抽认卡)

Ce document rassemble les concepts essentiels du cours, organisés par thématiques et ordre de progression, sous forme de questions-réponses pour faciliter la mémorisation.
本文档汇集了课程的基本概念，按主题和进度顺序组织，以问答形式呈现，便于记忆。

---

## 1. Compilation & Environnement (Survival Kit - TooL)  编译与环境 (生存工具包 - 工具篇)

**Q1 : Qu'est-ce que la compilation en C++ ?**
*(Q1 : 什么是C++中的编译？)*
**R :** C'est le processus de transformation du code source (lisible par l'humain) en un fichier binaire exécutable (compréhensible par la machine).
*(R : 它是将源代码（人类可读）转换为可执行二进制文件（机器可理解）的过程。)*

**Q2 : Quelle est la commande de base pour compiler avec GCC ?**
*(Q2 : 使用GCC编译的基本命令是什么？)*
**R :** `g++ fichier.cpp -o mon_programme`
*   `-o mon_programme` : définit le nom de l'exécutable. *(定义可执行文件的名称。)*
*   Ajoutez `-Wall` pour afficher tous les avertissements (recommandé). *(添加 `-Wall` 以显示所有警告（推荐）。)*

**Q3 : Quelle est la différence entre un fichier `.h` et un fichier `.cpp` ?**
*(Q3 : `.h` 文件和 `.cpp` 文件有什么区别？)*
**R :**
*   **`.h` (Header)** : Contient les **déclarations** (prototypes de fonctions, classes, templates). Il est destiné à être inclus (`#include`). *(包含 **声明**（函数原型、类、模板）。用于被包含。)*
*   **`.cpp` (Source)** : Contient les **définitions** (l'implémentation du code). Il est destiné à être compilé. *(包含 **定义**（代码实现）。用于被编译。)*

**Q4 : Pourquoi sépare-t-on le code en fichiers `.h` (header) et `.cpp` (source) ?**
*(Q4 : 为什么要将代码分为 `.h`（头文件）和 `.cpp`（源文件）？)*
**R :**
1.  **Séparation Interface/Implémentation** : L'utilisateur n'a besoin que du `.h` pour connaître l'interface. *(接口/实现分离：用户只需要 `.h` 即可了解接口。)*
2.  **Mutualisation** : Plusieurs fichiers `.cpp` peuvent inclure le même `.h`. *(共享：多个 `.cpp` 文件可以包含同一个 `.h`。)*
3.  **Compilation incrémentale** : On ne recompile que les fichiers `.cpp` modifiés. *(增量编译：只重新编译修改过的 `.cpp` 文件。)*

**Q5 : Quelle est la règle d'ordre déclaration/définition pour une fonction ?**
*(Q5 : 函数的声明/定义顺序规则是什么？)*
**R :** Une fonction doit impérativement être **déclarée** (le compilateur doit connaître sa signature) **avant** d'être utilisée (appelée) dans le code.
*(R : 函数必须在代码中被使用（调用）**前**进行 **声明**（编译器必须知道其签名）。)*

---

## 2. Types & Variables (Survival Kit - TooL)  类型与变量 (生存工具包 - 工具篇)

**Q6 : Pourquoi faut-il toujours initialiser une variable en C++ ?**
*(Q6 : 为什么在C++中总是要初始化变量？)*
**R :** Parce qu'une variable non initialisée a une valeur indéterminée (le contenu résiduel de la mémoire), ce qui peut causer des bugs imprévisibles.
*(R : 因为未初始化的变量具有未确定的值（内存的残留内容），这可能导致不可预测的错误。)*

**Q7 : Quelles sont les différentes façons d'initialiser une variable ?**
*(Q7 : 初始化变量有哪些不同的方法？)*
**R :**
1.  `int a = 5;` (Copie) *(复制)*
2.  `int b(5);` (Constructeur) *(构造函数)*
3.  `int c{5};` (Uniforme/Accolades - **Recommandée** car plus sûre, empêche le narrowing). *(统一/大括号 - **推荐**，因为更安全，防止窄化转换)*

**Q8 : Qu'est-ce que l'inférence de type (`auto`) ?**
*(Q8 : 什么是类型推断 (`auto`)？)*
**R :** C'est la capacité du compilateur à déduire automatiquement le type d'une variable à partir de sa valeur d'initialisation.
*(R : 这是编译器根据变量的初始值自动推断其类型的能力。)*
*   Exemple : `auto x = 3.14;` (x est déduit comme `double`). *(例如：x 被推断为 `double`。)*
*   **Règle AAA** : *Almost Always Auto* (utiliser `auto` le plus possible pour la maintenabilité). *(AAA规则：几乎总是使用 Auto（为了可维护性尽可能使用 `auto`）。)*

**Q9 : À quoi sert le mot-clé `const` ?**
*(Q9 : 关键字 `const` 有什么用？)*
**R :** Il rend une variable **immuable** (constante). Elle doit être initialisée dès sa déclaration et ne peut plus être modifiée ensuite.
*(R : 它使变量**不可变**（常量）。它必须在声明时初始化，之后不能修改。)*

**Q10 : Quelle est la différence entre `auto` et `decltype` ?**
*(Q10 : `auto` 和 `decltype` 有什么区别？)*
**R :**
*   `auto` déduit le type en ignorant les références et `const` (sauf si spécifié). *(`auto` 推断类型时忽略引用和 `const`（除非指定）。)*
*   `decltype(expr)` donne le type **exact** de l'expression, en conservant les qualifieurs `const` et les références. *(`decltype(expr)` 给出表达式的 **精确** 类型，保留 `const` 限定符和引用。)*

**Q11 : Qu'est-ce que le "Shadowing" (Masquage) de variables ?**
*(Q11 : 什么是变量的 "Shadowing"（遮蔽）？)*
**R :** C'est le fait de déclarer une variable dans un bloc interne (ex: `{ int i = 2; }`) avec le même nom qu'une variable existante dans un bloc externe (ex: `int i = 1;`). La variable interne **masque** temporairement la variable externe. À éviter.
*(R : 这是指在内部块（例如：`{ int i = 2; }`）中声明一个与外部块中现有变量（例如：`int i = 1;`）同名的变量。内部变量暂时 **遮蔽** 了外部变量。应避免这种情况。)*

---

## 3. Contrôle & Fonctions (Survival Kit - TooL)  控制与函数 (生存工具包 - 工具篇)

**Q12 : Comment fonctionne une boucle `do...while` par rapport à un `while` classique ?**
*(Q12 : `do...while` 循环与经典 `while` 循环相比如何工作？)*
**R :** La boucle `do...while` garantit que le bloc d'instructions est exécuté **au moins une fois**, car la condition est vérifiée *après* l'exécution.
*(R : `do...while` 循环保证指令块 **至少执行一次**，因为条件是在执行 *后* 检查的。)*

**Q13 : Qu'est-ce qu'une fonction surchargée (overloading) ?**
*(Q13 : 什么是重载函数 (overloading)？)*
**R :** C'est la possibilité de définir plusieurs fonctions avec le **même nom** mais des **signatures différentes** (paramètres différents en nombre ou type).
*(R : 这是指可以用 **相同的名字** 但 **不同的签名**（参数数量或类型不同）定义多个函数。)*

**Q14 : Où doit-on placer les arguments par défaut d'une fonction ?**
*(Q14 : 函数的默认参数应该放在哪里？)*
**R :** Ils doivent être définis **uniquement dans la déclaration** (prototype) et placés à la **fin** de la liste des paramètres.
*(R : 它们必须 **仅在声明**（原型）中定义，并放置在参数列表的 **末尾**。)*

---

## 4. Manipulation Avancée (Survival Kit - TooL)  高级操作 (生存工具包 - 工具篇)

**Q15 : Pourquoi utiliser `enum class` plutôt qu'un `enum` classique ?**
*(Q15 : 为什么使用 `enum class` 而不是经典的 `enum`？)*
**R :**
1.  **Portée (Scope)** : Les valeurs sont dans l'espace de nom de l'enum (accès via `Enum::Valeur`). *(作用域：值在枚举的命名空间内（通过 `Enum::Valeur` 访问）。)*
2.  **Typage fort** : Pas de conversion implicite vers `int`, renforce la sécurité. *(强类型：没有向 `int` 的隐式转换，增强了安全性。)*

**Q16 : À quoi servent les `namespaces` ?**
*(Q16 : `namespaces` 有什么用？)*
**R :** À regrouper des identifiants (fonctions, classes) pour éviter les **conflits de noms** (ex: `std::cout` vs `mon_projet::cout`).
*(R : 用于组合标识符（函数、类）以避免 **命名冲突**（例如：`std::cout` vs `mon_projet::cout`）。)*

**Q17 : Quel type de `cast` (conversion) est le plus sûr pour les types de base ?**
*(Q17 : 对于基本类型，哪种 `cast`（转换）最安全？)*
**R :** `static_cast<Type>(variable)`. Il effectue des vérifications à la compilation.
*(R : `static_cast<Type>(variable)`。它在编译时执行检查。)*

---

## 5. Orienté Objet - Les Bases (Survival Kit - OO)  面向对象 - 基础 (生存工具包 - OO)

**Q18 : Quelle est la différence entre une `class` et une `struct` en C++ ?**deque
*(Q18 : C++ 中 `class` 和 `struct` 有什么区别？)*
**R :** La seule différence est la **visibilité par défaut** :
*(R : 唯一的区别是 **默认可见性**：)*
*   `class` : membres `private` par défaut. *(`class` : 默认为 `private` 成员。)*
*   `struct` : membres `public` par défaut. *(`struct` : 默认为 `public` 成员。)*

**Q19 : Quelle est la différence précise entre `public`, `protected` et `private` (Visibilité) ?**
*(Q19 : `public`、`protected` 和 `private`（可见性）之间的确切区别是什么？)*
**R :**
*   **Public** : Accessible de partout (interface externe). *(随处可见（外部接口）。)*
*   **Protected** : Accessible dans la classe elle-même et dans ses **classes dérivées** (enfants). *(仅在类本身及其 **派生类**（子类）中可见。)*
*   **Private** : Accessible **uniquement** dans la classe elle-même (masqué même pour les enfants). *(**仅** 在类本身中可见（对子类也隐藏）。)*

**Q20 : Qu'est-ce que l'encapsulation ?**
*(Q20 : 什么是封装？)*
**R :** C'est le principe de masquer les données internes (`private`) et de ne fournir l'accès que via des méthodes publiques (interface) pour protéger l'intégrité de l'objet.
*(R : 这是隐藏内部数据 (`private`) 并仅通过公共方法（接口）提供访问以保护对象完整性的原则。)*

**Q21 : À quoi sert le mot-clé `friend` ?**
*(Q21 : `friend` 关键字有什么用？)*
**R :** Il permet à une fonction ou classe externe d'accéder aux membres **privés** (et protégés) de la classe qui la déclare "amie".
*(R : 它允许外部函数或类访问声明其为“友元”的类的 **私有**（和受保护）成员。)*

**Q22 : Que signifie `void maFonction() const;` dans une classe ?**
*(Q22 : 类中的 `void maFonction() const;` 是什么意思？)*
**R :** Cela signifie que la méthode s'engage à **ne pas modifier** les données membres de l'objet appelant. Obligatoire pour appeler la méthode sur un objet `const`.
*(R : 这意味着该方法承诺 **不修改** 调用对象的成员数据。在 `const` 对象上调用该方法是必须的。)*

**Q23 : Pourquoi faut-il des "Include Guards" (`#ifndef`, `#define`, `#endif`) dans les `.h` ?**
*(Q23 : 为什么 `.h` 文件中需要 "Include Guards" (`#ifndef`, `#define`, `#endif`)？)*
**R :** Pour empêcher qu'un fichier d'en-tête soit inclus plusieurs fois dans le même fichier source (multiples définitions).
*(R : 为了防止头文件在同一个源文件中被多次包含（多重定义）。)*

---

## 6. Héritage & Polymorphisme (Survival Kit - OO)  继承与多态 (生存工具包 - OO)

**Q24 : Quelle est la différence entre l'héritage `public`, `protected` et `private` ?**
*(Q24 : `public`、`protected` 和 `private` 继承有什么区别？)*
**R :**
*   **`public`** : L'interface du parent reste publique chez l'enfant (*est-un*). *(父类的接口在子类中保持公开（*is-a*）。)*
*   **`protected`** : Le public du parent devient protégé chez l'enfant. *(父类的公开成员在子类中变为受保护。)*
*   **`private`** : Tout le parent devient privé chez l'enfant. *(父类的所有成员在子类中变为私有。)*

**Q25 : Qu'est-ce que le polymorphisme dynamique ?**
*(Q25 : 什么是动态多态？)*
**R :** C'est la capacité d'appeler une méthode sur un pointeur/référence de type `Base`, et d'exécuter la version de l'objet réel (`Derived`). Nécessite des méthodes `virtual`.
*(R : 这是在 `Base` 类型的指针/引用上调用方法，执行实际对象（`Derived`）版本的能力。需要 `virtual` 方法。)*

**Q26 : Pourquoi le destructeur d'une classe de base doit-il être `virtual` ?**
*(Q26 : 为什么基类的析构函数必须是 `virtual`？)*
**R :** Pour garantir que le destructeur de la classe dérivée soit appelé lors d'une destruction via un pointeur `Base`. Sinon : fuite de mémoire.
*(R : 为了确保通过 `Base` 指针销毁对象时，派生类的析构函数被调用。否则：内存泄漏。)*

**Q27 : À quoi sert le mot-clé `override` ?**
*(Q27 : 关键字 `override` 有什么用？)*
**R :** Il indique explicitement qu'une méthode redéfinit une méthode virtuelle du parent. Permet au compilateur de vérifier la signature.
*(R : 它显式指示方法重写了父类的虚拟方法。允许编译器检查签名。)*

---

## 7. Gestion de la Mémoire (Survival Kit - Mem)  内存管理 (生存工具包 - Mem)

**Q28 : Quelles sont les trois zones mémoire principales ?**
*(Q28 : 主要的三种内存区域是什么？)*
**R :**
1.  **Statique** : Global/Static (durée = programme). *(静态区：全局/静态（生命周期 = 程序）。)*
2.  **Pile (Stack)** : Variables locales (durée = bloc). *(栈：局部变量（生命周期 = 块）。)*
3.  **Tas (Heap)** : Allocations dynamiques `new` (durée = jusqu'au `delete`). *(堆：动态分配 `new`（生命周期 = 直到 `delete`）。)*

**Q29 : Quelle est la différence entre `new/delete` et `malloc/free` ?**
*(Q29 : `new/delete` 和 `malloc/free` 有什么区别？)*
**R :**
*   **`new` / `delete`** : Allouent/libèrent la mémoire **ET** appellent Constructeur/Destructeur. À utiliser en C++.
*   **`new` / `delete`** : 分配/释放内存 **并且** 调用构造函数/析构函数。在 C++ 中使用。
*   **`malloc` / `free`** : Allouent/libèrent juste des octets bruts sans gérer l'objet. À éviter en C++.
*   **`malloc` / `free`** : 仅分配/释放原始字节，不管理对象。在 C++ 中避免使用。

**Q30 : Quelle est la différence entre un pointeur (`int*`) et une référence (`int&`) ?**
*(Q30 : 指针 (`int*`) 和引用 (`int&`) 有什么区别？)*
**R :**
*   **Pointeur** : Adresse mémoire, peut être `nullptr`, réassignable. *(指针：内存地址，可以是 `nullptr`，可重新赋值。)*
*   **Référence** : Alias, jamais nulle, non réassignable. *(引用：别名，永不为空，不可重新赋值。)*

**Q31 : Pourquoi préférer le passage par `const&` (référence constante) ?**
*(Q31 : 为什么首选 `const&`（常量引用）传递？)*
**R :** Pour éviter la copie de l'objet (performance) tout en garantissant qu'il ne sera pas modifié (sécurité).
*(R : 为了避免对象复制（性能），同时保证它不会被修改（安全）。)*

**Q32 : Résumez les modes de passage : Valeur vs Référence vs Pointeur.**
*(Q32 : 总结传递模式：值 vs 引用 vs 指针。)*
**R :**
*   **Valeur** : Copie de l'objet (coûteux si grand). *(值：复制对象（如果很大则昂贵）。)*
*   **Référence** (`&`) : Alias vers l'original (modification possible, pas de copie). *(引用 (`&`)：原始对象的别名（可修改，无复制）。)*
*   **Pointeur** (`*`) : Adresse (peut être NULL, arithmétique possible). *(指针 (`*`)：地址（可以是NULL，可进行算术运算）。)*

**Q33 : Qu'est-ce qu'une "fuite mémoire" ?**
*(Q33 : 什么是“内存泄漏”？)*
**R :** Mémoire allouée (`new`) mais non libérée (`delete`) alors qu'on a perdu son adresse.
*(R : 分配了内存 (`new`) 但在丢失地址时未释放 (`delete`)。)*

**Q34 : Qu'est-ce que la "Règle des 5" ?**
*(Q34 : 什么是“五法则”？)*
**R :** Si une classe gère une ressource manuellement (ex: destructeur personnalisé), elle doit sans doute définir : Destructeur, Constructeur de copie, Opérateur d'affectation copie, Constructeur de déplacement, Opérateur d'affectation déplacement.
*(R : 如果一个类手动管理资源（例如：自定义析构函数），它可能必须定义：析构函数、拷贝构造函数、拷贝赋值运算符、移动构造函数、移动赋值运算符。)*

**Q35 : Qu'est-ce que la "Rule of 0" ?**
*(Q35 : 什么是“零法则”？)*
**R :** Si une classe ne gère pas de ressource manuelle, elle ne doit définir **aucun** destructeur/constructeur spécial. Le compilateur les génère correctement.
*(R : 如果一个类不管理手动资源，它不应定义 **任何** 特殊的析构/构造函数。编译器会正确生成它们。)*

---

## 8. Programmation Statique (Survival Kit - Static)  静态编程 (生存工具包 - Static)

**Q36 : Que signifie le mot-clé `static` dans une classe ?**
*(Q36 : 类中的关键字 `static` 是什么意思？)*
**R :** Le membre appartient à la **classe** et non à une instance. Partagé par tous les objets.
*(R : 成员属于 **类** 而不是实例。被所有对象共享。)*

**Q37 : À quoi sert `constexpr` ?**
*(Q37 : `constexpr` 有什么用？)*
**R :** Indique qu'une expression peut être évaluée à la **compilation**.
*(R : 指示表达式可以在 **编译时** 评估。)*

**Q38 : Qu'est-ce qu'un "Template" ?**
*(Q38 : 什么是 "Template"（模板）？)*
**R :** Un mécanisme pour définir des fonctions/classes génériques (sans type fixé à l'avance).
*(R : 一种定义通用函数/类（不预先固定类型）的机制。)*

**Q39 : Pourquoi les templates doivent-ils être définis dans les fichiers `.h` ?**
*(Q39 : 为什么模板必须在 `.h` 文件中定义？)*
**R :** L'instanciation du template se fait à la **compilation** et nécessite la **définition complète** du code source. Le compilateur doit voir le code pour générer la version spécifique (ex: `vector<int>`).
*(R : 模板实例化是在 **编译** 时完成的，需要源代码的 **完整定义**。编译器必须看到代码才能生成特定版本（例如：`vector<int>`）。)*

**Q40 : Que sont les "Concepts" (C++20) ?**
*(Q40 : 什么是 "Concepts" (C++20)？)*
**R :** Un moyen de contraindre les types acceptés par un template (ex: `requires std::integral<T>`) pour des messages d'erreur plus clairs.
*(R : 一种限制模板接受类型的方法（例如：`requires std::integral<T>`），以便获得更清晰的错误消息。)*

---

## 9. Bibliothèque Standard STL (Deep Water - TooL)  标准模板库 STL (深水区 - 工具篇)

**Q41 : Qu'est-ce que la STL ?**
*(Q41 : 什么是 STL？)*
**R :** *Standard Template Library* : Conteneurs (stockage), Algorithmes (traitement) et Outils génériques optimisés fournis avec C++.
*(R : *Standard Template Library*：C++ 提供的优化通用容器（存储）、算法（处理）和工具。)*

**Q42 : Différence `std::vector` vs `std::array` ?**
*(Q42 : `std::vector` vs `std::array` 的区别？)*
**R :**
*   **`vector`** : Dynamique (taille variable, Tas). Conteneur par défaut. *(动态（可变大小，堆）。默认容器。)*
*   **`array`** : Statique (taille fixe connue compil., Pile). *(静态（编译时已知固定大小，栈）。)*

**Q43 : Différence `std::map` vs `std::vector` ?**
*(Q43 : `std::map` vs `std::vector` 的区别？)*
**R :** `map` associe Clé/Valeur (dictionnaire). `vector` est une séquence indexée par des entiers contigus.
*(R : `map` 关联键/值（字典）。`vector` 是由连续整数索引的序列。)*

**Q44 : Pourquoi `map` et `set` n'ont pas d'accès par index `[]` (au sens position) ?**
*(Q44 : 为什么 `map` 和 `set` 没有按索引 `[]` 访问（指位置）？)*
**R :** Ce sont des structures associatives (arbres), triées par clé. L'élément n°10 n'est pas accessible directement en O(1).
*(R : 它们是关联结构（树），按键排序。第10个元素无法直接以 O(1) 访问。)*

**Q45 : Qu'est-ce qu'un itérateur ?**
*(Q45 : 什么是迭代器？)*
**R :** Objet permettant de parcourir un conteneur (`begin()`/`end()`) de façon uniforme.
*(R :允许以统一方式遍历容器 (`begin()`/`end()`) 的对象。)*

**Q46 : Que pointe `container.end()` ?**
*(Q46 : `container.end()` 指向什么？)*
**R :** L'élément **juste après** le dernier (*past-the-end*). Ne jamais le déréférencer.
*(R : 最后一个元素 **之后** 的元素 (*past-the-end*)。切勿解引用。)*

**Q47 : Différence `for(auto x : vec)` vs `for(auto& x : vec)` ?**
*(Q47 : `for(auto x : vec)` vs `for(auto& x : vec)` 的区别？)*
**R :**
*   `auto x` : Travaille sur une **copie**. *(在 **副本** 上工作。)*
*   `auto& x` : Travaille sur une **référence** (modifie l'original, plus rapide). *(在 **引用** 上工作（修改原始值，更快）。)*

**Q48 : Qu'est-ce qu'une Lambda ?**
*(Q48 : 什么是 Lambda？)*
**R :** Fonction anonyme définie en ligne `[capture](args){body}`. Utilisée avec les algorithmes STL.
*(R : 在线定义的匿名函数 `[capture](args){body}`。与 STL 算法一起使用。)*

**Q49 : Que fait `std::for_each` ?**
*(Q49 : `std::for_each` 做什么？)*
**R :** Applique une fonction à chaque élément d'une plage d'itérateurs.
*(R : 将函数应用于迭代器范围内的每个元素。)*

---

## 10. Mémoire Avancée (Deep Water - Mem)  高级内存 (深水区 - Mem)

**Q50 : Différence lvalue vs rvalue ?**
*(Q50 : lvalue vs rvalue 的区别？)*
**R :**
*   **lvalue** : A un nom et une adresse (ex: `x`). *(有名字和地址（例如：`x`）。)*
*   **rvalue** : Temporaire, pas de nom persistant (ex: `42`, `x+y`). *(临时，无持久名称（例如：`42`, `x+y`）。)*

**Q51 : À quoi sert `std::move` ?**
*(Q51 : `std::move` 有什么用？)*
**R :** Convertit une lvalue en rvalue pour permettre le **déplacement** (vol de ressources) au lieu de la copie.
*(R : 将 lvalue 转换为 rvalue，以允许 **移动**（窃取资源）而不是复制。)*

**Q52 : Qu'est-ce qu'une "rvalue reference" (`T&&`) ?**
*(Q52 : 什么是 "rvalue reference" (`T&&`)？)*
**R :** Référence acceptant les objets temporaires/déplacés. Permet le Move Constructor.
*(R : 接受临时/移动对象的引用。允许移动构造函数。)*

**Q53 : Pourquoi les Smart Pointers ?**
*(Q53 : 为什么使用智能指针？)*
**R :** Gestion automatique de la vie des objets (pas de `delete` manuel).
*(R : 自动管理对象生命周期（无需手动 `delete`）。)*

**Q54 : Différences `unique_ptr`, `shared_ptr`, `weak_ptr` ?**
*(Q54 : `unique_ptr`, `shared_ptr`, `weak_ptr` 的区别？)*
**R :**
*   **`unique_ptr`** : Propriétaire unique. *(唯一所有者。)*
*   **`shared_ptr`** : Propriété partagée (compteur). *(共享所有权（计数器）。)*
*   **`weak_ptr`** : Observateur faible (ne garde pas l'objet en vie). *(弱观察者（不保持对象存活）。)*

---

## 11. Orienté Objet Avancé (Deep Water - OO)  高级面向对象 (深水区 - OO)

**Q55 : Comment gérer les erreurs (Exceptions) ?**
*(Q55 : 如何处理错误（异常）？)*
**R :** `throw` lance l'erreur, `try/catch` la capture. Plus propre que les codes de retour.
*(R : `throw` 抛出错误，`try/catch` 捕获。比返回码更整洁。)*

**Q56 : Qu'est-ce que le "Stack Unwinding" ?**
*(Q56 : 什么是 "Stack Unwinding"（栈展开）？)*
**R :** Lors d'une exception, le programme remonte la pile et **détruit automatiquement** tous les objets locaux rencontrés.
*(R : 发生异常时，程序回溯栈并 **自动销毁** 遇到的所有局部对象。)*

**Q57 : Que signifie `noexcept` ?**
*(Q57 : `noexcept` 是什么意思？)*
**R :** La fonction ne lance jamais d'exception. Si cela arrive -> Crash.
*(R : 函数从不抛出异常。如果发生 -> 崩溃。)*

**Q58 : Comment définir une Interface en C++ ?**
*(Q58 : 如何在 C++ 中定义接口？)*
**R :** Classe abstraite avec uniquement des méthodes virtuelles pures (`=0`).
*(R : 仅包含纯虚方法 (`=0`) 的抽象类。)*

**Q59 : Qu'est-ce qu'une méthode virtuelle pure ?**
*(Q59 : 什么是纯虚方法？)*
**R :** Méthode sans implémentation (`=0`) qui rend la classe abstraite et force les enfants à l'implémenter.
*(R : 没有实现的方法 (`=0`)，使类变为抽象并强制子类实现它。)*

**Q60 : Pourquoi utiliser des interfaces ?**
*(Q60 : 为什么使用接口？)*
**R :** Pour le polymorphisme : manipuler divers objets via un contrat commun, sans connaître leur type réel.
*(R : 为了多态：通过通用契约操作各种对象，而不知道其实际类型。)*

---

## 12. Programmation Statique Avancée (Deep Water - Static)  高级静态编程 (深水区 - Static)

**Q61 : Qu'est-ce qu'une "Universal Reference" ?**
*(Q61 : 什么是 "Universal Reference"（万能引用）？)*
**R :** Paramètre template `T&&`. Accepte lvalue et rvalue. Base du Perfect Forwarding.
*(R : 模板参数 `T&&`。接受 lvalue 和 rvalue。完美转发的基础。)*

**Q62 : À quoi sert `std::forward` ?**
*(Q62 : `std::forward` 有什么用？)*
**R :** Transmet l'argument en préservant sa nature (lvalue reste lvalue, rvalue reste rvalue).
*(R : 传递参数并保留其性质（lvalue 保持 lvalue，rvalue 保持 rvalue）。)*

**Q63 : Qu'est-ce qu'un Template Variadique ?**
*(Q63 : 什么是可变参数模板？)*
**R :** Template acceptant un nombre variable d'arguments (`typename... Args`).
*(R : 接受可变数量参数的模板 (`typename... Args`)。)*

**Q64 : Que sont les "Fold Expressions" ?**
*(Q64 : 什么是 "Fold Expressions"（折叠表达式）？)*
**R :** Syntaxe pour appliquer une opération sur tout un pack de paramètres (`(args + ...)`).
*(R :对整个参数包应用操作的语法 (`(args + ...)`).)*
