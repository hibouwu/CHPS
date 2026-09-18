---
marp: true
theme: default
paginate: true


---

# **Programmation Orientée Objet pour le Calcul Scientifique : Part I Survival kit** 面向科学计算的面向对象编程：第一部分 生存工具包

---

# Organisation du cours 课程安排

Sous forme d'**Item**, se raccrochant à trois catégories :
以条目形式呈现，关联到三类：

- Outils et Langage (TooL)
工具与语言（TooL）
- Orienté objet (OO)
面向对象（OO）
- Gestion de la mémoire (Mem)
内存管理（Mem）
- **Programmation statique (Static)**
**静态编程（Static）**

Vous n'êtes pas seul : https://en.cppreference.com/w/ est votre allié...
你并不孤单：https://en.cppreference.com/w/ 是你的盟友……

---

# Item 11 premier flirt avec la programmation statique 第11项 首次邂逅静态编程

Programmation statique qu'est-ce que c'est ? Les lignes de codes écrites sont "exécutées" :
什么是静态编程？所写代码行的“执行”方式如下：

有些代码不是等程序运行起来（双击打开或命令行运行）之后才干活的，而是在编译器生成可执行文件的过程中就已经计算出结果了。

Le plus simple : les variables statiques
最简单的情况：静态变量

```c++
int i = 3; // assignment done at compile time

int main() {
    std::cout << " i =" << i << std::endl;
}

```

---

# Item 11 premier flirt avec la programmation statique 第11项 首次邂逅静态编程

Mot clé **static** : membre de classe et non d'objet **1/2**
关键字 **static**：属于类而非对象 **1/2**

```c++
struct A{
    static int i;
};
int A::i = 1;

int main(){
    std::cout << A::i << std::endl; // no need to have an object to access i
    A a;
    A a2;
    std::cout << a.i << std::endl;  // = 1
    std::cout << a2.i << std::endl; // = 1
    // i is the same in all object of class 
    a.i += 2;
    std::cout << a2.i << std::endl;// = 3 !
}
```

---

# Item 11 premier flirt avec la programmation statique 第11项 首次邂逅静态编程

Mot clé **static** : membre de classe et non d'objet **2/2**
关键字 **static**：属于类而非对象 **2/2**

```c++
// Since C++17 inline authorises in-class initialization
struct A{
    inline static int i = 1;
};

int main(){
    std::cout << A::i << std::endl; // no need to have an object to access i
    A a;
    A a2;
    std::cout << a.i << std::endl;  // = 1
    std::cout << a2.i << std::endl; // = 1
    // i is the same in all object of class 
    a.i += 2;
    std::cout << a2.i << std::endl;// = 3 !
}
```

---

# Item 11 premier flirt avec la programmation statique 第11项 首次邂逅静态编程

Mot clé **constexpr** : indique qu'une expression peut être évaluée à la compilation
关键字 **constexpr**：表明某个表达式可以在编译阶段求值

- cette expression se comporterta comme une expression constante
该表达式的行为与常量表达式相同
- ``constexpr`` peut porter sur une variable ou une fonction, voir :
``constexpr`` 可以用于变量或函数，参见：
  - <https://en.cppreference.com/w/cpp/language/constexpr>
  参阅：<https://en.cppreference.com/w/cpp/language/constexpr>
  - <https://en.cppreference.com/w/cpp/language/constant_expression.html>
  参阅：<https://en.cppreference.com/w/cpp/language/constant_expression.html>

```c++
constexpr int i = 5;

constexpr int f()  {
    return i+2;
}
```

---

# Item 11 premier flirt avec la programmation statique 第11项 首次邂逅静态编程

Les expressions constantes sont nécessaires dans les deux cas de figures suivants :
常量表达式在以下两种情况下是必需的：

- les paramètres des template (voir item suivant)
模板参数（见下一项）
- les tailles de tableaux statiques
静态数组的大小

```c++
int static_array[constant_expression];
```

---

# Item 11 premier flirt avec la programmation statique 第11项 首次邂逅静态编程

les tableaux statiques : sont des tableaux `à la C`
静态数组：是 C 风格的数组

```c++
int array0 [3]; // uninitialized array
int array[3] = {0,1,2};
std::cout << array[0] << std::endl; // array starts at index 0
for (int i = 0; i < 3 ; ++i){
    std::cout << "array["<< i << "] = " << array[i]<< std::endl;
}
```

- La taille est connue statiquement, ie. à la compilation et ne peut pas changer.
数组大小在编译时静态确定，无法更改。
- Un dépassement de tableau est une erreur silencieuse (=danger)
数组越界是一种静默错误（=危险）。

```c++
int array[3] = {0,1,2};
array[3] = 0; //ERROR, memory corruption
```

---

# Item 11 premier flirt avec la programmation statique 第11项 首次邂逅静态编程

les tableaux statiques : sont des tableaux `à la C`
静态数组：是 C 风格的数组

- leur taille peut être une expression constante (fonction ou variable `constexpr`)
其大小可以是一个常量表达式（`constexpr` 函数或变量）。

```c++
constexpr int i = 5;

constexpr int f()  {
    return i+2;
}
int main(){
    int array[f()];
    for (int i = 0; i < f() ; ++i){
        array[i] = i;
    }
}
```

---

# Item 11 premier flirt avec la programmation statique 第11项 首次邂逅静态编程

les tableaux statiques : sont des tableaux `à la C`
静态数组：是 C 风格的数组

- ces tableaux peuvent être multi-dimensionnels :
这些数组可以是多维的：
`<type> name [slow-index]...[fast-index]`

```c++
int multi_array[2][3] = {   {0,1,2},
                            {3,4,5}
                        };
for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
        std::cout << multi_array[i][j] << std ::endl;
    }
}
```

L'ordre de stockage est la transposée de celui utilisé en Fortran.
存储顺序是 Fortran 所使用顺序的转置。
**Exo 11.1** Construire, remplir et afficher un tableau de taille [2][2][3].
**练习 11.1** 构建、填充并显示一个大小为 [2][2][3] 的数组。

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Paramètres template** : la face immergée de l'iceberg...
**模板参数**：冰山隐藏的一面……

- **Fonctions Template**
**函数模板**
  - abstraction du type des arguments
  对参数类型进行抽象
- **Classes Template**
**类模板**
  - un modèle de classe
  一个类模型

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Fonctions Template** **1/4**
**函数模板** **1/4**

- commençons par un exemple
先从一个示例开始

```c++
void f_int(int a) { std::cout << a << std::endl;}
void f_double(double a) { std::cout << a << std::endl;}
void f_char(char a) {std::cout << a << std::endl;}
```

Un paramètre template permet de mutualiser du code pour différent type de données
模板参数可以在不同数据类型之间复用代码

```c++
template <typename T>
void f(T a) { std::cout << a << std::endl;}
int main(){
    f(3);
    f(3.14);
    f('a');
}
```

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Fonctions Template** **2/4**
**函数模板** **2/4**

- Syntaxe  : on peut écrire indifféremment `typename` ou `class`
语法：可以任选书写 `typename` 或 `class`

```c++
template <class T> // or template <typename T>
void f(T a) { std::cout << a << std::endl;}
```

**Exo 12.1** écrire une fonction template qui incrémente son paramètre (passé en entrée/sortie). L'appeler pour différents types numériques (entiers ou flottants).
**练习 12.1** 编写一个模板函数，使其对传入（入参/出参）的参数执行自增，并针对不同数值类型（整数或浮点数）调用它。

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Fonctions Template** **3/4** : danger des templates
**函数模板** **3/4**：模板的风险

- une fonction template ne peux pas fonctionner pour n'importe quel type
模板函数并不能适用于任意类型
  - impossible de spécifier les types requis (avant les concepts de C++20)
  在 C++20 的 concepts 引入之前无法指定所需的类型

```c++
template <typename T>
void f(T& a) { ++a; }

int main(){
    int i = 0;
    f(i); // OK
    bool b = true;
    f(b); // KO, ++ operator not available for bool type
 }
```

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Fonctions Template** **3/4** : introduction des concepts
**函数模板** **3/4**：引入 concepts

- ``#include <concepts>`` introduits en C++20
``#include <concepts>`` 在 C++20 中被引入
- permettent d'apporter des restrictions sur le type passé en argument du template
允许对传入模板参数的类型施加约束
  
```c++
#include <concepts>
template <typename T>
requires std::incrementable<T> //作用：限制 T 只能是可递增类型
void f(T& a) { ++a; }

int main(){
    int i = 0;
    f(i); // OK
    bool b = true;
    f(b); // KO, ++ operator not available for bool type
 }
```

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Classes Template**  1/13
**类模板** 1/13

- commençons par un exemple
先从一个示例开始

```c++
class IntData {
    int m_i;
public:
    void print();
    void add(int a);
};
class FloatData {
    float m_f;
public:
    void print();
    void add(float a);
};
```

- Peut-on mutualiser ?
我们能否实现代码复用？

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Classes Template** 2/13
**类模板** 2/13

- commençons par un exemple : réécriture template
先从一个示例开始：使用模板改写

```c++
template <typename T>
class DataT {
    T m_i = T{}; // default value of type T
public:
    void print() {}
    void add(T a) {}
};
int main(){
    DataT<int> int_data;
    DataT<float> float_data;
}
```

- Attention la classe `DataT` n'est compilée que lorsqu'elle est déclarée.
注意：类 `DataT` 只有在被实例化声明时才会被编译。

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Classes Template** 3/13
**类模板** 3/13
un modèle de classe qui devient une classe à sa déclaration
类模板在实例化声明时就成为一个具体的类

- les classe template peuvent contenir plusieurs paramètres template
类模板可以包含多个模板参数
- les paramètres templates peuvent être des types ou des `int` ou des `bool`
模板参数可以是类型、`int` 或 `bool`
- les paramètres templates peuvent être (partiellement) spécialisés
模板参数可以被（部分）特化
- la déclaration et la définition doivent être accessibles à l'instanciation de la classe
类的声明与定义在实例化时必须可见

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Classes Template** 4/13
**类模板** 4/13

- les classe template peuvent contenir plusieurs paramètres template
类模板可以包含多个模板参数

```c++
template <typename T, typename U>
class Pair {
    T m_a = T{}; // default value of type T
    U m_b = U{}; // default value of type U
public:
    void print() {}
    void add(T a, U b) {}
};
int main(){
    Pair<int,float> int_data;
    Pair<float, double> float_data;
}
```

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Classes Template** 5/13
**类模板** 5/13

- les paramètres templates peuvent être des types ou des `int` ou des `bool`
模板参数可以是类型、`int` 或 `bool`

```c++
template <typename T, int N>
class ArrayT {
    T m_i [N] = {}; // empty array
public:
    void print() {}
    void add(T* a) {}
};
int main(){
    ArrayT<int,2> int_data;
    ArrayT<float,3> float_data;
}
```

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Classes Template** 6/13
**类模板** 6/13

- les paramètres templates de la classe peuvent être (partiellement) spécialisés
类模板的模板参数可以被（部分）特化

```c++
template <typename T>
class DataT {
    T m_data = T{}; // default value of type T
public:
    void print();
    void add(T a, U b);
};
template <> // specialization: no add method
class DataT<bool>{
    T m_data = T{}; // default value of type T
public:
    void print();
}; 
```

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Classes Template** 7/13
**类模板** 7/13

- les paramètres templates de la classe peuvent être (partiellement) spécialisés
类模板的模板参数可以被（部分）特化

```c++
template <typename T, typename U>
class Pair {
    T m_a = T{}; // default value of type T
    U m_b = U{}; // default value of type U
public:
    void print() {}
    void add(T a, U b) {}
};
// specialization 
template <typename U>
class Pair<int,U>{
    // specific behavior for a pair which first arg is an int...
}; 
```

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Classes Template** 8/13
**类模板** 8/13

- les méthodes de la classe peuvent être spécialisées (pas partiellement)
类的成员函数可以被特化（不能部分特化）

```c++
template <typename T, typename U>
struct Pair {
    void print() {std::cout << "Pair<T,U>"<< std::endl;}
};
template <> // specialization 
void Pair<int,int>::print() {std::cout << "Pair<int,int>"<< std::endl;}

int main(){
    Pair<int,double> p1;
    Pair<int,int> p2;
    p1.print();
    p2.print();
} 
```

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Classes Template** 9/13
**类模板** 9/13

- la déclaration et la définition doivent être accessibles à l'instanciation de la classe
类的声明与定义在实例化时必须可见

```c++
template <typename T> // -- A.h --
struct A {
    T m_ = T{};
    void print(); }; // declaration only
#include "A.h" // -- A.cpp --
template <typename T>
void A<T>::print() {} // definition (here empty for concision)
// -- main .cpp --
#include "A.h"
int main(){
    A<int> a;
    a.print(); //  ERROR: undefined reference to 'A<int>::print()
}
```

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Classes Template** 10/13
**类模板** 10/13

- la déclaration et la définition doivent être accessibles à l'instanciation de la classe
类的声明与定义在实例化时必须可见
  - lorsque l'objet `a` est créé, la **définition** et la **déclaration** de l'ensemble de la classe doivent être **visibles** : dans un `.h` inclus ou dans le même fichier
  当对象 `a` 被创建时，整个类的**定义**与**声明**必须是**可见**的：要么在已包含的 `.h` 中，要么在同一文件中
  - les template sont **déclarés et définis dans des fichiers `.h`**
  模板通常**在 `.h` 文件中同时声明与定义**
  - Les template peuvent être définis dans un `.cpp` s'ils ne sont utilisés qu'**à l'intérieur de ce `.cpp`**.
  若模板仅在该 `.cpp` 内部使用，也可以在 `.cpp` 中定义
  - si l'on souhaite séparer définition et déclaration dans deux fichiers : faire deux `.h` et include la déclaration dans la définition
  如果想在两个文件中拆分定义与声明：可以使用两个 `.h` 文件，并在定义文件中包含声明文件

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Classes Template** 11/13
**类模板** 11/13

- la déclaration et la définition doivent être accessibles à l'instanciation de la classe
类的声明与定义在实例化时必须可见

```c++
/*
Project/
├── A.h          <-- 包含 struct A 的声明 AND 函数 print() 的完整代码
└── main.cpp     <-- #include "A.h"
*/
/*A.h*/
template <typename T> 
struct A {
    T m_ = T{};
    void print(); // declaration only
};
template <typename T>
void A<T>::print() {} // definition within the A.h file
/*main.cpp*/
#include "A.h"
int main(){
    A<int> a;
    a.print(); //  OK
}
```

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Classes Template** 12/13
**类模板** 12/13

- la déclaration et la définition doivent être accessibles à l'instanciation de la classe
类的声明与定义在实例化时必须可见

```c++
/*
Project/
├── A.h          <-- 包含 struct A 的声明 + 在末尾 #include "A_impl.h"
├── A_impl.h     <-- 只包含 void A<T>::print() 的函数体代码
└── main.cpp     <-- #include "A.h"
*/
/*A_impl.h*/
template <typename T> 
void A<T>::print() {} // definition within the another.h file
/*A.h*/
template <typename T>
struct A {
    T m_ = T{};
    void print();}; // declaration only
#include "A_impl.h"
/*main.cpp*/
#include "A.h"
int main(){
    A<int> a;
    a.print(); //  OK
}
```

---

# Item 12 : entrée dans l'univers des template 第12项 走进模板的世界

**Classes Template** 13/13
**类模板** 13/13

- **Exo 12.2** faites fonctionner ce programme qui affiche le contenu du tuple
**练习 12.2** 让该程序运行并输出元组的内容

```c++
#include "Tuple.h"

int main(){
    Tuple<int,int,int> my_tuple {1,2,3};
    my_tuple.print();
    Tuple<int,double,int> my_tuple2 {1,1.2,3};
    my_tuple2.print();
    return 0;
}
```

- le `Tuple<int,int,int>` affiche "Made of int"
`Tuple<int,int,int>` 会输出 "Made of int"
- séparer la déclaration et la définition de votre tuple dans deux fichiers.
将元组的声明与定义拆分到两个文件中。
