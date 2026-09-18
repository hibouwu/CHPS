---
marp: true
theme: default
paginate: true


math: katex
---

# **Programmation Orientée Objet pour le Calcul Scientifique : Part I Survival kit** 面向科学计算的面向对象编程：第一部分 生存工具包

---

# Organisation du cours 课程安排

Sous forme d'**Item**, se raccrochant à trois catégories :
以条目形式呈现，归属于三个类别：

- Outils et Langage (TooL)
工具与语言（TooL）
- Orienté objet (OO)
面向对象（OO）
- **Gestion de la mémoire (Mem)**
内存管理（Mem）
- Programmation statique (Static)
静态编程（Static）

Vous n'êtes pas seul : https://en.cppreference.com/w/ est votre allié...
你并不孤单：https://en.cppreference.com/w/ 是你的盟友……

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

En préambule : notion de **bloc de portée** ou **scope** 1/3
前言：理解**作用域块**（**scope**）的概念 1/3

- un bloc de portée est défini entre **deux accolades**
一个作用域块由一对**花括号**限定
- un bloc de portée permet de déclarer des **variables locales** :
一个作用域块允许声明**局部变量**：
  - toutes les variables déclarées dans le bloc sont **détruites en sortie de bloc**
  在块中声明的所有变量会在离开块时**被销毁**
  - le bloc définit donc une **durée de vie** pour des variables
  因此，块为变量定义了**生命周期**
- un bloc **hérite** de toutes les **variables précédemment définies**
一个块会**继承**之前定义的所有**变量**
- des blocs peuvent être **imbriqués** les uns dans les autres
多个块可以**相互嵌套**

**Attention : un namespace n'est pas un bloc de portée**
**注意：namespace 不是作用域块**

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

En préambule : notion de **bloc de portée** ou **scope** 2/3
前言：理解**作用域块**（**scope**）的概念 2/3

- Exemple de deux blocs **imbriqués**
两个**嵌套**块的示例

```c++
int main() { // open main function scope
  { 
    int i = 0;
    { 
      int j = i; // parent scope available
    } 
    j = 2; // ERROR j undefined : out of scope
  } 
i = 0; // ERROR i undefined : out of scope
} // close main function scope
```

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

En préambule : notion de **bloc de portée** ou **scope** 3/3
前言：理解**作用域块**（**scope**）的概念 3/3

- Attention au *shadowing*
注意*变量遮蔽（shadowing）*

```c++
int main() {
  {
    auto i = 0;
    {
      auto i = 2; // first variable i unavailable
    }
    std::cout << i << "\n"; // i = 0 !
    {
      i += 2; // we refer to the first variable i
    }
    std::cout << i << "\n"; // i = 2 !
  }
}
```

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

Sur la *pile* ou dans le *tas* ?  1/5
在*栈*上还是在*堆*中？1/5

- On distingue trois zones mémoires différentes pour les variables
根据变量可以区分三块不同的内存区域
  - une zone **'statique'** (segments *data* ou *BSS* si variables non initialisées)
  一块**“静态”**区域（若变量未初始化则位于 *data* 或 *BSS* 段）
  - une zone **'automatique'** : **la pile** ou **stack**
  一块**“自动”**区域：即**栈**（stack）
  - une zone **'dynamique'** : le **tas** ou **heap**
  一块**“动态”**区域：即**堆**（heap）
- La zone mémoire où réside une variable est fonction de sa création
变量所处的内存区域取决于它的创建方式
  - variable créé **en dehors de tout bloc de portée** => **statique**
  变量在所有作用域块之外创建 => **静态区**
  - variable créé **dans un bloc de portée** => **pile**
  变量在某个作用域块内创建 => **栈区**
  - variable **alloué dynamiquement** => **tas**
  变量通过**动态分配**获得 => **堆区**

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

Sur la *pile* ou dans le *tas* ?  2/5
在*栈*上还是在*堆*中？2/5

- variable créé **en dehors de tout bloc de portée** => **statique**
  在所有作用域块之外创建的变量 => **静态区**

```c++
auto i = 3; // static zone (data segment)
  // 静态区（数据段）
int j; // static zone (BSS segment)
// 静态区（BSS 段）

int main(){
  j = 10;
  std::cout << "i = " << i <<std::endl;
  std::cout << "j = " << j <<std::endl;
  return 0;
}
```
  
---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

Sur la *pile* ou dans le *tas* ?  3/5
在*栈*上还是在*堆*中？3/5

- variable créé **dans un bloc de portée** => **pile**
  在某个作用域块内创建的变量 => **栈区**

```c++
void print() {
  auto i = 1; // stack variable
  // 栈变量
  std::cout << "i = " << i << std::endl;
}

int main(){
  int j = 10; // stack variable
  // 栈变量
  std::cout << "j = " << j <<std::endl;
  return 0;
}
```

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

Sur la *pile* ou dans le *tas* ?  4/5
在*栈*上还是在*堆*中？4/5

- variable **alloué dynamiquement** => **tas**
  通过**动态分配**获得的变量 => **堆区**

Qu'est-ce qu'une allocation dynamique ?
什么是动态分配？

- une réservation explicite d'un bloc mémoire de taille fixée
  显式保留一个固定大小的内存块
- utilisation des mots clés `malloc` (**C**) ou `new` (**C++** legacy)
- utilisation des mots clés `malloc` (**C**) ou `new` (**C++** legacy)
  使用关键字 `malloc`（**C**）或 `new`（**C++** 传统方式）
- l'intérêt sera de piloter la durée de vie de la variables
- l'intérêt sera de piloter la durée de vie de la variables
  目的在于掌控变量的生命周期
  - elle sera détruite manuellement par la commande `delete`
  - 需通过 `delete` 指令手动销毁
  - on manipule alors un **pointeur de variable** et non une variable : `*`
  - 此时操作的是**变量指针**而非变量本体：`*`

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

Sur la *pile* ou dans le *tas* ?  5/5
在*栈*上还是在*堆*中？5/5

- variable **alloué dynamiquement** => **tas**
  通过**动态分配**获得的变量 => **堆区**

Qu'est-ce qu'une allocation dynamique ?
什么是动态分配？

```c++
int* int_ptr = new int{0}; // new returns an int address
// new 返回一个 int 地址

*(int_ptr) = 5; // use * operator to get the pointer value
// 使用 * 运算符获取指针指向的值

std::cout << "int_ptr = " << int_ptr; // pointer address (hexadecimal)
// 指针地址（十六进制）
std::cout << "int value = "<< *int_ptr; // pointed int value
// 指向的整数值

delete int_ptr; // use delete to release memory
// 使用 delete 释放内存
```

**Exo 9.1** Créez et manipulez votre pointeur de réel (`float`).
**练习 9.1** 创建并操作一个指向实数（`float`）的指针。

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

**Pointeur et référence** : tu références ou tu pointes ?  **1/6**
**指针与引用**：你在引用还是在指向？**1/6**

- un pointeur est **l'adresse en mémoire d'une variable**
  指针是**变量在内存中的地址**
  - son type s'écrit `<type_pointé>*` ex `int* int_ptr;`,`float* float_ptr;`
  - 其类型写作 `<type_pointé>*`，例如 `int* int_ptr;`、`float* float_ptr;`
  - on accède à la valeur pointée par l'opérateur `*` ex `*int_ptr = 1;`
  - 通过 `*` 运算符访问指向的值，例如 `*int_ptr = 1;`
  - on obtient l'adresse d'un objet par l'opérateur `&` ex `int* int_ptr = &int_var`
  - 通过 `&` 运算符获取对象地址，例如 `int* int_ptr = &int_var`
- une référence est **une vue sur une variable existante**
  引用是对现有变量的**另一个别名**
  - son type s'écrit `<type_référencé>&` ex `int& ref = existing_int_var;`
  - 其类型写作 `<type_référencé>&`，例如 `int& ref = existing_int_var;`
  - on la manipule comme la variable référencée ex `ref = 3`;
  - 操作方式与被引用的变量相同，例如 `ref = 3`；
    - lorsque l'on **modifie** la **référence** d'une variable, on **modifie** la **variable**
    - 当我们**修改**变量的**引用**时，也就**修改**了该**变量**

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

**Pointeur et référence** : tu références ou tu pointes ?  **2/6**
**指针与引用**：你在引用还是在指向？**2/6**

```c++
int        i =  1;
int* int_ptr = &i; // int_ptr points on i
// int_ptr 指向 i
int& int_ref =  i; // int_ref references i
// int_ref 引用 i

*int_ptr += 2; // i = 3
// 此时 i = 3
 int_ref += 2; // i = 5
// 此时 i = 5

std::cout << "       i = " << i; 
std::cout << " int_ptr = " << int_ptr; // pointer address (hexadecimal)
// 指针地址（十六进制）
std::cout << "*int_ptr = "<< *int_ptr; //    pointed variable value
// 指针指向的变量值
std::cout << " int_ref = " << int_ref; // referenced variable value 
// 引用的变量值
```

**Exo 9.2** Créer une variable réelle (float) et manipulez la via un pointeur et via une référence.
**练习 9.2** 创建一个实数（float）变量，并分别通过指针和引用来操作它。

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

**Pointeur et référence** : tu références ou tu pointes ?  **3/6**
**指针与引用**：你在引用还是在指向？**3/6**
ces types pointeurs et références se combinent avec le mot clé `const`
这些指针与引用类型可以与关键字 `const` 结合使用

```c++
int        i =  1;
int const* const_int_ptr  = &i; // int_ptr points on i
// int_ptr 指向 i
int const& const_int_ref =  i; // int_ref references i
// int_ref 引用 i

*const_int_ptr += 2; // Error, points to a const int
// 错误：指向 const int
 const_int_ref += 2; // Error referenced a const int
// 错误：引用的是 const int
```

**Exo 9.3** Transformez vos pointeur/référence de l'**Exo 9.2** pour qu'ils adressent un `const float`.
**练习 9.3** 将你在**练习 9.2**中的指针/引用改为指向 `const float`。

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

**Pointeur et référence** : tu références ou tu pointes ?  **4/6**
**指针与引用**：你在引用还是在指向？**4/6**
ces types pointeurs et références se combinent avec le mot clé `const` :
这些指针与引用类型可以结合 `const` 关键字：

- attention à ne pas confondre pointeur constant et pointeur de constant
  注意不要混淆常量指针与指向常量的指针

```c++
int        i =  1;
int const* const_int_ptr  = &i; // pointer of const
// 指向常量的指针
*const_int_ptr += 2; // ERROR, points to a const int
// 错误：指向 const int
 
 int j = 2;
 const_int_ptr = &j; // Ok, the pointer is not const
// 可以：指针本身不是 const
 
 int* const int_ptr_const = &i; // const pointer
// 常量指针
 int_ptr_const = &j; // ERROR pointer is constant
// 错误：指针本身是常量
 *int_ptr_const += 1; // ok, the pointed value is not const
// 可以：被指向的值不是常量
 
 int const * const const_int_const_ptr = &i; // Const pointer of const int !
// 指向 const int 的 const 指针！
```

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

**Pointeur et référence** : tu références ou tu pointes ?  **5/6**
**指针与引用**：你在引用还是在指向？**5/6**
Du coup quelle(s) différence(s) ?
那么到底有哪些差异？

- La principale différence est qu'un pointeur peut être nul et pas une référence, qui pointe forcément vers une variable ;
  主要区别是指针可以为空，而引用不能，为引用必须指向某个变量；

```c++
int* ptr = nullptr;
int& ref; // ERROR
// 错误
```

- un pointeur doit donc être manipulé avec précaution : déréférencer un pointeur null ou non initialisé = crash
  因此必须谨慎操作指针：解引用空指针或未初始化指针会导致崩溃

```c++
int* ptr = nullptr;
int i = *ptr;// COMPILES BUT CRASHES (segmentation fault)
// 能编译但会崩溃（段错误）
```

- La seconde différence est qu'un pointeur peut, dans sa durée de vie, pointer successivement vers plusieurs variables, une référence non.
  第二个区别是：在其生命周期内，指针可以先后指向多个变量，而引用不行。

```c++
int* ptr = nullptr; //左边表示声明一个指向int的指针
int i = 10;
int j = 20;
ptr = &i; // &i实际上是i的地址
std::cout << "*ptr = " << *ptr << std::endl;
ptr = &j; // &j实际上是j的地址
std::cout << "*ptr = " << *ptr << std::endl;

int& ref = i; // 左边表示声明一个int变量的别名
std::cout << "ref = " << ref << std::endl;
ref = j; // i被修改（等于j）
std::cout << "i = " << i << std::endl;
std::cout << "j = " << j << std::endl;
std::cout << "ref = " << ref << std::endl;
i++; // ref也随之改变
std::cout << "i = " << i << std::endl;
std::cout << "j = " << j << std::endl;
std::cout << "ref = " << ref << std::endl;
```

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

Ne perdez pas la **mémoire** dans les **signatures de fonction**... **1/6**
别在**函数签名**里丢了你的**内存**……**1/6**
**Deux comportements possibles** pour passer un argument à une fonction :
向函数传递参数有**两种可能的行为**：

- passage par **copie** appelé aussi par **valeur**;
  通过**拷贝**传递，也称为按**值**传递；

```c++
void function( int i) {}
```

- passage par **référence**.
  通过**引用**传递。

```c++
void function( int& i) {}
```

Pour les types de base du langage, **passage par référence** = argument en **entrée/sortie**
对于语言的基础类型，**引用传递**意味着参数既是**输入**又是**输出**

- **Exo 9.4** Créez une fonction qui modifie un argument passé en paramètre.
  **练习 9.4** 编写一个函数，修改通过参数传入的值。

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

Ne perdez pas la **mémoire** dans les **signatures de fonction**... **2/6**
别在**函数签名**里丢了你的**内存**……**2/6**
**Deux comportements possibles** pour passer un argument à une fonction :
向函数传递参数有**两种可能的行为**：

- passage par **copie** appelé aussi par **valeur** :
  通过**拷贝**（按**值**）传递：
dans la fonction, la variable est **une copie** de la variable passée à la fonction
在函数内部，该变量是传入变量的**副本**

```c++
void function(int i) {
  i++; // local modification
  // 局部修改
}
int main() {
  int i = 3;
  function(i);
  std::cout<< "i = " << i << std::endl; // i = 3 ! and not 4
  // i = 3！而不是 4
}
```

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

Ne perdez pas la **mémoire** dans les **signatures de fonction**... **3/6**
别在**函数签名**里丢了你的**内存**……**3/6**
**Deux comportements possibles** pour passer un argument à une fonction :
向函数传递参数有**两种可能的行为**：

- passage par **référence** :
  通过**引用**传递：
dans la fonction, la variable est **une référence** de la variable passée à la fonction
在函数内部，该变量是传入变量的**引用**

```c++
void function(int& i) {
  i++;
  // 自增，作用于原变量
}
int main() {
  int i = 3; // 'global' modification
  // “全局”修改
  function(i);
  std::cout<< "i = " << i << std::endl; // i = 4 
  // i = 4
}
```

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

Ne perdez pas la **mémoire** dans les **signatures de fonction**... **4/6**
别在**函数签名**里丢了你的**内存**……**4/6**
**Deux comportements possibles** pour passer un argument à une fonction :
向函数传递参数有**两种可能的行为**：

- passage par **référence** :
  通过**引用**传递：
dans la fonction, la variable est **une référence** de la variable passée à la fonction
在函数内部，该变量是传入变量的**引用**
  - Attention **on ne peut pas passer un temporaire par référence non constante**
  - 注意：**不能将临时量绑定到非常量引用**

```c++
void function1(int& i) { i++;}
// 非 const 引用，递增实参
void function2(int const& i) { std::cout <<i;}
// const 引用，仅打印

int main() {
    function1(5); // ERROR
    // 错误
    function2(5); //  OK
    // 正确
}
```

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

Ne perdez pas la **mémoire** dans les **signatures de fonction**... **5/6**
别在**函数签名**里丢了你的**内存**……**5/6**
Passage d'un **pointeur** = **un troisième comportement ?**
通过传递**指针** = **第三种方式？**

- passage par **pointeur**
  通过**指针**传递

```c++
void function(int* i_ptr) {
  if (i_ptr) (*i_ptr)++;
  // 若指针有效则递增目标
}
int main() {
  int i = 3; // 'global' modification
  // “全局”修改
  function(&i);
  std::cout<< "i = " << i << std::endl; // i = 4 
  // i = 4
}
```

Nous l'appellerons le **passage par adresse** = l'argument est aussi en **entrée/sortie**
我们称之为**按地址传递** = 参数同样作为**输入/输出**

---

# Item 9 : Vie et mort d'une variable en C++ C++ 中变量的生与死

Ne perdez pas la **mémoire** dans les **signatures de fonction**... **6/6**
别在**函数签名**里丢了你的**内存**……**6/6**
Passage d'un **pointeur** = **un troisième comportement ?** Pas vraiment...
通过传递**指针** = **第三种方式？** 其实并不算……

- passage par **pointeur** = passage par **copie** d'une **adresse** ;
  指针传递 = 其实是**地址**的**拷贝传递**；

```c++
void function(int* i) {
  std:: cout << &i << "\n";
  // 打印指针变量自身的地址
}

int main() {
  int i = 10;
  std::cout << &i << "\n"; // an address
  // 一个地址
  function(&i); // another address
  // 另一个地址
}
```

La plupart du temps (sauf cas avec héritage) **lui préférer un passage par référence**.
大多数情况下（除继承等特殊场景外）应当优先使用**引用传递**。

---

# Item 10 : Vie et mort d'un objet en C++ C++ 中对象的生与死

Comme les variables : toutes les règles vues à l'**item 9** s'appliquent pour un objet
与变量相同：**条目 9** 中的所有规则同样适用于对象

```c++
struct A{};
A a{}; // static variable
// 静态变量

int main() {
  A a2{}; // stack variable
  // 栈变量
  A* a_ptr = new A{}; // heap variable
  // 堆变量
  delete a_ptr;
}
```
Focus sur trois points :
重点关注三个方面：
- **construction/desctruction** d'un objet,
对象的**构造/析构**，
- syntaxe avec les **pointeurs**,
使用**指针**的语法，
- passage par **copie/référence** d'un objet
对象的**拷贝/引用**传递

---

# Item 10 : Vie et mort d'un objet en C++ C++ 中对象的生与死

**Construction/destruction d'un objet** : ce que vous ne voyez pas... **1/6**
**对象的构造/析构**：那些你看不见的……**1/6**

```c++
struct A{
  int m_i = 0;
}; // ce que vous voyez
// 你能看到的部分

struct A{ // ce que vous ne voyez pas
// 你看不到的部分
   A() {}; // constructor
   // 构造函数
   A(int i) : m_i(i) {} // constructor
  // 构造函数
  ~A() {}; // destructor
  // 析构函数
   A(A const& a) {m_i = a.i;} // copy operator
  // 拷贝运算符
   A& operator= (A const& a) {m_i = a.i;return *this;} // copy assignment
  // 拷贝赋值
   int m_i = 0;
}; // move operators kept under silence for the moment
// 目前先不讨论移动语义
```

---

# Item 10 : Vie et mort d'un objet en C++ C++ 中对象的生与死

**Construction/destruction d'un objet** : ce que vous ne voyez pas... **2/6**
**对象的构造/析构**：那些你看不见的……**2/6**

```c++
struct A{ // ce que vous ne voyez pas
// 你看不到的部分
   A() {}; // constructor
   // 构造函数
   A(int i) : m_i(i) {} // constructor
  // 构造函数
  ~A() {}; // destructor
  // 析构函数
   A(A const& a) {m_i = a.m_i;} // copy constructor
  // 拷贝构造函数
   A& operator= (A const& a) {m_i = a.m_i;return *this;} // copy assignment
  // 拷贝赋值运算符
   int m_i = 0;
}; // move operators kept under silence for the moment
// 目前先不讨论移动语义
int main(){
  A a; // A()
  // 调用 A()
  A a{42}; // A(int)
  // 调用 A(int)
  A a2(a); // A (A const& a)
  // 调用 A(A const& a)
  A a3; // A()
  // 调用 A()
  a3 = a2; // A& operator= (A const& a)
  // 调用拷贝赋值运算符
} //~A()
// 离开作用域调用 ~A()
```

---

# Item 10 : Vie et mort d'un objet en C++ C++ 中对象的生与死

**Construction/destruction d'un objet** : ce que vous ne voyez pas... **3/6**
**对象的构造/析构**：那些你看不见的……**3/6**
Le C++ génère automatiquement ces méthodes pour vous !
C++ 会自动为你生成这些方法！

- Le constructeur : construit un objet;
  构造函数：用于构建对象；
- le destructeur libère les ressources de l'objet,
  析构函数释放对象资源；
- le constructeur par copie et l'opérateur d'affectation :
  拷贝构造函数和赋值运算符：
  - recopient les données membre à membre
    将成员数据逐一拷贝

---

# Item 10 : Vie et mort d'un objet en C++ C++ 中对象的生与死

**Construction/destruction d'un objet** : ce que vous ne voyez pas... **4/6**
**对象的构造/析构**：那些你看不见的……**4/6**
Parfois il peut être nécessaire d'implémenter une de ces méthodes
有时你需要自己实现其中某些方法

- initialisation d'un membre (privé) dans le constructeur
  - 在构造函数中初始化（私有）成员

```c++
class B {
  int m_i;
public:
  B(int i) : m_i(i) // member initialisation zone
  // 成员初始化区域
  {}
}
```

---

# Item 10 : Vie et mort d'un objet en C++ C++ 中对象的生与死

**Construction/destruction d'un objet** : ce que vous ne voyez pas... **5/6**
**对象的构造/析构**：那些你看不见的……**5/6**
Parfois il peut être nécessaire d'implémenter une de ces méthodes
有时你需要自己实现其中某些方法

- initialisation d'un membre dans le constructeur
  - 在构造函数中初始化成员
- destruction d'une ressource particulière (ex pointeur)
  - 释放特定资源（例如指针）

```c++
class B {
  int* m_ptr;
public:
  ~B() {delete m_ptr;}
}
```

**Plus aucune méthode n'est alors définie implicitement**
**此时将不再隐式生成任何方法**

- si une est explicitée ; il faut toutes les écrire...
  - 一旦显式定义其中一个，就需要全部自行实现……
- si on ne souhaite pas écrire de définition on peut utiliser ```= default```
  - 如果不想写出实现，可以使用 ```= default```
- pour supprimer une de ces méthodes on peut utiliser ```= delete```
  - 若要禁用某个方法，可以使用 ```= delete```

**Exo 10.1** écrire une classe contenant explicitement les cinq méthodes implicites. Utilisez ces méthodes dans une fonction `main`. Bonus : empêchez la copie et l'affectation.
**练习 10.1** 编写一个类，显式实现五个隐式方法；在 `main` 函数中调用这些方法。附加任务：禁止拷贝与赋值。

```c++
#include <iostream>
struct A{
  int m_i = 0;
  A() {std::cout << "A()" << std::endl;}; // constructor
  A(int const i) : m_i (i) { std::cout << "A(int)" << std::endl;}; // constructor
  ~A() {std::cout << "~A()" << std::endl;}; // destructor
  A(A const& a) { // copy constructor
    m_i = a.m_i;
    std::cout << "A(A const& a)" << std::endl;
  } 
  A& operator= (A const& a) { // copy assignment
    m_i = a.m_i;
    std::cout << "A& operator= (A const& a)" << std::endl;
    return *this;
  }
}; 

int main(){
  A a(1); // A(int)
  A a2(a); // A (A const& a)
  A a3; // A()
  a3 = a2; // A& operator= (A const& a)
  std::cout << "a3.m_i = " << a.m_i << "\n";
} //~A()
```
---

# Item 10 : Vie et mort d'un objet en C++ C++ 中对象的生与死

**Syntaxe** avec les **pointeurs**
使用**指针**时的**语法**

- La syntaxe change pour accéder aux données et aux méthodes d'un objet lorsque l'on le manipule via un pointeur :
  操作对象指针时，访问数据和方法的语法会发生变化：
  - on utilise l'opérateur `->` et non plus `.`
  - 需要使用 `->` 运算符，而不是 `.`

```c++
struct A {
  int i = 0;
  void print() const {std::cout << i << std::endl;};
};
int main(){
  A* a_ptr = new A{};
  a_ptr->i = 10;
  a_ptr->print();
  delete a_ptr;
}
```

---

# Item 10 : Vie et mort d'un objet en C++ C++ 中对象的生与死

Passage par **copie/référence** **1/3**
通过**拷贝/引用**传递 **1/3**
Choix du type de **passage** d'un argument **objet** dans une **fonction** très important
为函数选择对象参数的**传递方式**十分重要

- si on souhaite **modifier** l'objet, on passe par **référence** `&`
  若希望**修改**对象，应使用**引用** `&`
  - l'objet doit resté "alloué" tout le scope de la fonction (pas de temporaire !)
  对象必须在整个函数作用域内保持“已分配”（不能是临时量！）
- si on ne souhaite **pas le modifier**, un passage par copie est souvent contre-indiqué
  如果**不打算修改**对象，通常不建议按拷贝传递
  - un objet peut être très lourd en mémoire (contenir un tableau)
    对象可能占用大量内存（例如包含数组）
    - la copie sera donc très coûteuse
    因此拷贝代价高昂
  - on passe alors par **référence constante** `const&`
    因此改用**常量引用** `const&`
    - il n'y a alors pas de copie
      不会产生拷贝
    - l'objet est verrouillé en modification
      对象会被禁止修改

---

# Item 10 : Vie et mort d'un objet en C++ C++ 中对象的生与死

Passage par **copie/référence** **2/3**
通过**拷贝/引用**传递 **2/3**
Choix du type de passage d'un argument objet dans une fonction très important
在函数中选择对象参数的传递方式同样关键

```c++
struct A {
  int i[100000];
};

void modify_object (A& a) {
  a.i[0] = 1;
}

void do_not_modify_object(A const& a) {
  int val = a.i[0];
}

```

---

# Item 10 : Vie et mort d'un objet en C++ C++ 中对象的生与死

Passage par **copie/référence** **3/3**
通过**拷贝/引用**传递 **3/3**
Choix du type de passage d'un argument objet dans une fonction très important
为函数选择对象参数的传递方式依旧非常重要

- si on **souhaite modifier** l'objet, on passe par **référence** `&`
  如果**希望修改**对象，就通过**引用** `&`
- si on ne **souhaite pas le modifier**, on passe par **référence constante** `const&`
  如果**不想修改**对象，就通过**常量引用** `const&`

**Exo 10.2** Construisez et appelez deux fonction, l'une prenant en argument une référence d'objet et l'autre une référence constante.
**练习 10.2** 构造并调用两个函数：一个接收对象引用，另一个接收常量引用。

Si c'est **nécessaire** (souvent pour une programmation par interface) on peut passer
如有**必要**（接口编程中常见），也可以传递

- un pointeur d'objet (paramètre en entrée/sortie) `void object_in_out(A*)`
  对象指针（输入/输出参数）`void object_in_out(A*)`
- un pointeur d'objet constant (paramètre en entrée) `void object_in(A const*)`
  常量对象指针（输入参数）`void object_in(A const*)`

---

# Item 10 : Vie et mort d'un objet en C++ C++ 中对象的生与死

**Exo 10.3** Créez une classe `A` ayant :
**练习 10.3** 创建一个 `A` 类，要求：

- un membre privé de type `int*` initialisé dans le constructeur.
  在构造函数中初始化一个私有成员 `int*`
- une méthode de modification (`set`)
  提供一个修改方法（`set`）
- une méthode d'affichage (`print`) de l'entier contenu dans ce pointeur.
  提供一个显示该指针所指整数的 `print` 方法

Dans un programme principal, construisez cet objet et passez-le dans deux fonctions :
在主程序中构造此对象，并传入两个函数：

- une fonction `print_object` qui appellera la méthode print de l'objet 
  函数 `print_object`，调用对象的 `print` 方法 
- une fonction `modify_object`, qui prendra en paramètre un entier et appellera la méthode `set` de l'objet.
  函数 `modify_object`，接收一个整数参数并调用对象的 `set` 方法

Attention aux fuites mémoires à la destruction de l'objet, ou lors de sa copie...
注意对象析构或拷贝时可能出现的内存泄漏……
