---
marp: true
theme: default
paginate: true


---

# **Programmation Orientée Objet pour le Calcul Scientifique : Part I Survival kit** 面向科学计算的面向对象编程：第一部分 生存工具包

---

# Organisation du cours 课程安排

Sous forme d'**Item**, se raccrochant à trois catégories :
以条目形式呈现，归属于三个类别：

- Outils et Langage (TooL)
工具与语言（TooL）
- **Orienté objet (OO)**
- **Orienté objet (OO)**
**面向对象（OO）**
- Gestion de la mémoire (Mem)
- Gestion de la mémoire (Mem)
内存管理（Mem）
- Programmation statique (Static)
- Programmation statique (Static)
静态编程（Static）

Vous n'êtes pas seul : https://en.cppreference.com/w/ est votre allié...
你并不孤单：https://en.cppreference.com/w/ 是你的盟友...

---

# Item  6 : Une première forme de polymorphisme 多态的第一种形式

Les fonctions peuvent être **surchargées** **1/2**
函数可以被**重载** 1/2
Elles pourront changer de comportement en fonction de leurs arguments :
它们可以根据参数不同而改变行为：

```c++
void hello() {std::cout << "Hello world";}
void hello(int year) { std::cout <<"Hello year "<< year;}
```

Attention :
注意：

- le type de retour n'est pas discriminant
返回类型不是区分依据

```c++
void hello() {...}
int  hello() // ERROR : function hello already declared
```

---

# Item  6 : Une première forme de polymorphisme 多态的第一种形式

Les fonctions peuvent être **surchargées** **2/2**
函数可以被**重载** 2/2
Elles pourront changer de comportement en fonction de leurs arguments :
它们可以根据参数不同而改变行为：

```c++
void hello() {std::cout << "Hello world";}
void hello(int year) { std::cout <<"Hello year "<< year;}
```

**Exo 6.1**  Créer une fonction `multiple` qui multiplie deux entiers l'un par l'autre. Surchargez cette fonction pour qu'elle fonctionne avec un seul entier en entrée (elle le multipliera alors par 10).
**练习 6.1** 编写一个函数`multiple`用于将两个整数相乘。对该函数进行重载，使其在只有一个整数输入时使用（此时将该整数乘以 10）。

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Qu'est-ce qu'une **classe** :
什么是**类**：

- une structure qui contient des données et des traitements sur ces données
包含数据及其处理的结构

```c++
  class MyClass {}; 
```

Qu'est-ce qu'un **objet** :
什么是**对象**：

- une **instance** de classe, ie. une variable de type `MyClass`
类的一个**实例**，也就是一个类型为`MyClass`的变量。

```c++
  MyClass  my_object;
```

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Comment s'écrit une **classe** :
如何编写一个**类**：

```c++
class <MyClassName> {
 <data>;
 <methods>;
};
```

```c++
class MyClass {
  int i =0;
  void print() {std::cout << i;}
};
```

Le mot clé **`struct`** peut également s'utiliser. Voir plus loin (Visibilité).
关键字 **`struct`** 也可以使用。更多内容见后文（可见性）。

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Comment s'utilise une **classe**
如何使用一个**类**

- on accède aux données et aux méthodes par l'**operateur** `.`
通过运算符 `.` 访问数据和方法

```c++
MyClass my_object{};
my_object.i;
my_object.print();
```

**Exo 7.1** Créer votre propre classe avec une donnée et une méthode (mot clé **`class`**). Créer un objet de cette classe. Essayer d'accéder aux champs via l'opérateur `.` :  que constatez-vous ?
**练习 7.1** 使用关键字 **`class`** 创建一个包含数据和方法的自定义类。实例化一个对象，尝试通过运算符 `.` 访问这些字段：你观察到了什么？

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Notion de **visibilité** **1/3**
**可见性**概念 1/3
Comme l'**Exo 7.1** vous le montre :
正如**练习 7.1** 所展示的那样：

- les champs (données ou méthodes) d'une classe sont, par défaut, **inaccessibles**
类中的字段（数据或方法）默认是**不可访问**的

Avant de déclarer un bloc dans une classe il faut indiquer sa **visibilité**
在类中声明任何代码块前，需要先指明它的**可见性**

```c++
class <MyClassName> {
 <visibility>:
 <data>;
 <visibility>:
 <methods>;
};
```

`<visibility>` = `private`/`public` ou `protected` (vu plus tard)
`<visibility>` 可以是 `private` / `public` 或 `protected`（稍后介绍）

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Notion de **visibilité** **2/3**
**可见性**概念 2/3

- `private:` signifie que les champs ne seront accessibles qu'à l'intérieur de la classe
`private:` 表示字段仅能在类的内部访问
  - ie. dans les autres méthodes de la classe.
    即只能在该类的其他方法中访问。
- `protected` identique à `private` + accessibles à l'intérieur d'une classe dérivée
`protected` 与 `private` 类似，但在派生类内部也可以访问
- `public:` signifie que les champs seront accessibles à l'extérieur de la classe
`public:` 表示字段在类的外部也能访问

On observe en pratique que :
在实践中我们会发现：

- les **données** sont le plus souvent privées
**数据** 通常设为私有
- les **méthodes** sont le plus souvent publiques
**方法** 通常设为公有

Cela permet de proposer des **traitements sans exposer la représentation interne des données.**
这样就能在不暴露数据内部表示的情况下提供**操作**。

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Notion de **visibilité** **3/3**
**可见性**概念 3/3

```c++
class MyClass {
private:
  int i = 0;
public:
  void print() {std::cout << i;}
};
int main(){
  MyClass c{};
  c.print(); // OK
  c.i = 2; // ERROR
}
```

**Exo 7.2** Modifier votre classe de l'**Exo 7.1** pour donner accès à votre méthode, sans exposer vos données.
**练习 7.2** 修改你在**练习 7.1**中定义的类，使其提供方法访问但不暴露内部数据。

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

**Visibilité par défaut** deux mots clés `class` & `struct` pour construire une classe
**默认可见性**：使用 `class` 和 `struct` 两个关键字来构建类

- `class` : visibilité `private` par défaut ;
`class`：默认可见性为 `private`
- `struct` : visibilité `public` par défaut.
`struct`：默认可见性为 `public`

```c++
class MyClass {
  int i = 0; // private
};
struct MyStruct {
  int i = 0; //public
};
```

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Changer la **Visibilité** par amitié avec le mot clé **`friend`** **1/2**
使用关键字 **`friend`** 通过友元改变**可见性** 1/2

```c++
class MyClass {
  int i = 0; // private
  friend void my_friend_function(MyClass mc) {
    std::cout << mc.i << std::endl;
  }
};

int main() {
  MyClass mc {};
  my_friend_function(mc); // print "0"
  std::cout << mc.i << std::endl; // ERROR 'int MyClass::i' is private within this context
}
```

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Changer la **Visibilité** par amitié avec le mot clé **`friend`** **2/2**
使用关键字 **`friend`** 通过友元改变**可见性** 2/2

```c++
class MyClass {
  int i = 0; // private
  friend class MyFriendClass;
};
class MyFriendClass {
public:
  void printMyClass(MyClass mc) {
    std::cout << mc.i << std::endl;
  }
};

int main() {
  MyClass mc {};
  MyFriendClass mfc{}; // print "0"
  mfc.printMyClass(mc);
  std::cout << mc.i << std::endl; // ERROR 'int MyClass::i' is private within this context
}
```

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Membres ou méthodes **non mutables** : `const` **1/3**
不可变的成员或方法：`const` 1/3

- un membre `const` **reste constant** pendant toute la durée de vie de l'objet
`const` 成员在对象的整个生命周期内**保持不变**
  - il doit **être initialisé** !
  - il doit **être initialisé** !
  - 它必须**被初始化**！

```c++
struct MyStruct {
int const i = 10;
};

int main(){
  MyStruct a;
  a.i = 0;//ERROR 
}
```

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Membres ou méthodes **non mutables** : `const` **2/3**
不可变的成员或方法：`const` 2/3

- une méthode `const` ne peut **pas modifier des membres de l'objet**
`const` 方法**不能修改对象的成员**

```c++
struct MyClass {
int m_i = 10;
void print() const;
};

void MyClass::print() const {
m_i = 10; // ERROR
}
```

**Exo 7.3** Ajouter à votre classe une méthode const manipulant une donnée const.
**练习 7.3** 在你的类中添加一个 const 方法来操作一个 const 数据成员。

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Membres ou méthodes **non mutables** : `const` **3/3**
不可变的成员或方法：`const` 3/3

- Un objet peut être déclaré `const` :
对象可以被声明为 `const`：
  - on ne peut alors appeler que **ses méthodes const**
    此时只能调用它的 **const 方法**

```c++
  class MyClass {
  private: 
    int m_i = 0;
  public:
    void non_const_method() {}
    void const_method() const {}
  };
  int main(){
    MyClass const a{};
    a.const_method(); // OK
    a.non_const_method(); // ERROR
  }
```

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Pointeur d'instance `this`
实例指针 `this`

- Il est possible d'accéder à l'objet au sein des méthodes via le pointeur `this`
可以在方法内部通过指针 `this` 访问对象本身

```c++
class MyClass {
private: 
int m_i = 0;
public:
void increment() {
  m_i++;
  // equivalent to 
  this->m_i++; // Note operator -> equivalent to . for pointers
} 
};
```

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Classe et **fichiers** **1/6**
类与**文件** 1/6
Une bonne architecture de classe se compose :
一个良好的类架构包含：

- d'un **fichier header** `(.h)` contenant la **déclaration** de la classe, données/méthodes
一个包含类声明（数据/方法）的**头文件** `(.h)`
- d'un **fichier source** `(.cpp)` contenant les **définitions** des méthodes
- d'un **fichier source** `(.cpp)` contenant les **définitions** des méthodes
一个包含方法**定义**的**源文件** `(.cpp)`

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Classe et **fichiers** **2/6**
类与**文件** 2/6
Une bonne architecture de classe se compose :
一个良好的类架构包含：

- d'un **fichier header** `(.h)` contenant la **déclaration** de la classe, données/méthodes
一个包含类声明（数据/方法）的**头文件** `(.h)`

```c++
// MyClass.h
class MyClass {
  int m_i = 0;
public:
  void print() const;
};
```

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Classe et **fichiers** **3/6**
类与**文件** 3/6
Une bonne architecture de classe se compose :
一个良好的类架构包含：

- d'un **fichier source** `(.cpp)` contenant les **définitions** des méthodes
一个包含方法**定义**的**源文件** `(.cpp)`

```c++
// MyClass.cpp
#include "MyClass.h"
void MyClass::print() const  {
 std::cout << "i = " << m_i;
}
```

- **Exo 7.4** : créer une classe décrite dans deux fichiers `.h` et `.cpp`.
**练习 7.4**：创建一个使用 `.h` 和 `.cpp` 两个文件描述的类。

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象
Classe et **fichiers** : **Include guard** **4/6**
类与**文件**：**Include guard** 4/6

- Un fichier `.h` **ne peut pas être inclus deux fois dans le même fichier**
同一个源文件**不能两次包含**同一个 `.h` 文件

```c++
// MyOtherClass.h
#include "MyClass.h"

// main.cpp
#include "MyClass.h"
#include "MyOtherClass.h" //ERROR class MyClass already defined
```

- on protège donc un fichier `.h` par des directives de compilation 
因此，我们通过编译指令来保护 `.h` 文件，
  ```#ifndef, #endif, #define``` pour ne l'inclure qu'une seule fois
  ```#ifndef, #endif, #define``` 以确保它只被包含一次

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Classe et **fichiers** : **Include guard** **5/6**
类与**文件**：**Include guard** 5/6

- Exemple de protection du fichier `MyClass.h`
`MyClass.h` 文件保护示例

```c++
// MyClass.h
#ifndef MYCLASS_H_
#define MYCLASS_H_
class MyClass {
  int m_i = 0;
public:
  void print() const;
};
#endif // MYCLASS_H_

// main.cpp
#include "MyClass.h"
#include "MyOtherClass.h" // OK MyClass.h not included again
```

---

# Item 7 : créer une classe/un objet en C++ 在 C++ 中创建类/对象

Classe et **fichiers** : **Include guard** **6/6**
类与**文件**：**Include guard** 6/6

- **Exo 7.5** Créer un nouvel header `Tools.h`, déclarant par exemple un paramètre ou une classe,  que vous inclurez dans `Myclass.h` et dans `main.cpp`.
**练习 7.5** 新建一个头文件 `Tools.h`，例如声明一个参数或类，并在 `MyClass.h` 与 `main.cpp` 中包含它。
- Remarque : en pratique vous n'écrirez pas ces protections à la main, tous les IDE modernes l'écrivent automatiquement à la création d'un fichier `.h`.
备注：实际工作中不需要手动编写这些保护，现代 IDE 在创建 `.h` 文件时会自动生成。

---

# Item 8 : une affaire d'héritage 继承之事

Les classes peuvent hériter les unes des autres.
类之间可以相互继承。

- L'héritage s'écrit avec l'opérateur **":"** **``class Son : Parent  {};``**
继承使用运算符 **":"** 表示，即 **`class Son : Parent {};`**
- L'héritage **donne accès aux méthodes et aux données du(des) parent(s)**
继承能够**访问父类的方法和数据**

```c++
struct Parent{
  int parent_data = 1;
  void print_parent(){std::cout << "Parent class";}
};
struct Son : Parent {};

int main(){
  Son s{};
  std::cout << s.parent_data << std::endl;
  s.print_parent();
}
```

---

# Item 8 : une affaire d'héritage 继承之事

L'héritage donne accès méthodes et données du(des) parent(s)...**ou pas**
继承是否能访问父类的方法和数据取决于条件……**也可能不行**

- Cela **dépend** de la **visibilité** dans la **classe parent** : ex. **``private``**
这**取决于**父类中的**可见性**设置，例如 **`private`**

```c++
struct Parent{
private:
  int parent_data = 1;
  void print_parent(){std::cout << "Parent class";}
};

struct Son : Parent {};

int main(){
  Son s{};
  std::cout << s.parent_data << std::endl; // KO 'Parent::parent_data' is private
  s.print_parent(); // KO 'Parent::print_parent()' is private
}
```

---

# Item 8 : une affaire d'héritage 继承之事

L'héritage donne accès méthodes et données du(des) parent(s)...**ou pas**
继承是否能访问父类的方法和数据取决于条件……**也可能不行**

- Cela **dépend** de la **visibilité** dans la **classe parent** : ex. **``protected``**
这**取决于**父类中的**可见性**设置，例如 **`protected`**

```c++
class Parent{
protected :
  int parent_data = 1;
  void print_parent(){std::cout << "Parent class";}
};
struct Son : Parent {
  void print() {print_parent(); std::cout << parent_data;} // OK protected data called inside child Son::print
};
int main(){
  Son s{};
  std::cout << s.parent_data << std::endl; // KO : protected not visible outside
  s.print_parent(); // KO : idem
  s.print(); // OK protected data called inside child Son::print
}
```

---

# Item 8 : une affaire d'héritage 继承之事

L'héritage donne accès méthodes et données du(des) parent(s)...**ou pas**
继承是否能访问父类的方法和数据取决于条件……**也可能不行**

- Cela **dépend** du **type d'héritage**
这**取决于**具体的**继承类型**
- Celui-ci peut-être :
可能的情况包括：
  - `public` (le défaut pour une `struct`)
    `public`（`struct` 的默认值）
  - `private` (le défaut pour une `class`)
    `private`（`class` 的默认值）
  - `protected`
    `protected`（受保护）

**Exercice** : refaire les trois exemples ci-dessus en changeant le type d'héritage (``public``, ``protected`` ou ``private``).
**练习**：修改上述三个示例，分别将继承类型设为 `public`、`protected` 和 `private`。

---

# Item 8 : une affaire d'héritage 继承之事

L'héritage `public` ne modifie pas la visibilité des membres du parent chez l'enfant
`public` 继承不会改变父类成员在子类中的可见性

```c++
struct Parent{
private :
  int internal_data = 0;
protected :
  int parent_data = 1;
public :
  void print_parent(){std::cout << "Parent class";}
};
class Son : public Parent {// ****** Son inherits the members with the following visibility ********
// This is pseudo-code showing how Son access its Parent data and methods
private :
  int internal_data = 0;
protected :
  int parent_data = 1;
public :
  void print_parent(){std::cout << "Parent class";}
  // ******************************************************
};
```

---

# Item 8 : une affaire d'héritage 继承之事

L'héritage `protected` rend les membres **`public`** du parent **`protected`** chez l'enfant
`protected` 继承会把父类中 **`public`** 的成员在子类中变为 **`protected`**

```c++
struct Parent{
private :
  int internal_data = 0;
protected :
  int parent_data = 1;
public :
  void print_parent(){std::cout << "Parent class";}
};
class Son : protected Parent {// ****** Son inherits the members with the following visibility ********
// This is pseudo-code showing how Son access its Parent data and methods
private :
  int internal_data = 0;
protected :
  int parent_data = 1;
protected :
  void print_parent(){std::cout << "Parent class";}
  // *****************************************************

};
```

---

# Item 8 : une affaire d'héritage 继承之事

L'héritage `private` rend **tous les membres** du parent **`private`** chez l'enfant
`private` 继承会使父类的**所有成员**在子类中都变为 **`private`**

```c++
struct Parent{
private :
  int internal_data = 0;
protected :
  int parent_data = 1;
public :
  void print_parent(){std::cout << "Parent class";}
};
class Son : private Parent {// ****** Son inherits the members with the following visibility ********
// This is pseudo-code showing how Son access its Parent data and methods
private :
  int internal_data = 0;
private :
  int parent_data = 1;
private :
  void print_parent(){std::cout << "Parent class";}
  // *****************************************************
};
```

---

# Item 8 : une affaire d'héritage 继承之事

|Membres classe parent | Type d'héritage |Membres classe enfant |
|父类成员 | 继承类型 | 子类成员|
|---|---|---|
|`private`<br> `protected` <br> `public`| `: private` | `private`<br> `private` <br> `private`|
|父类成员：`private`<br> `protected` <br> `public`|继承类型：`: private`|子类成员：`private`<br> `private` <br> `private`|
|`private`<br> `protected` <br> `public`| `: protected` | `private`<br> `protected` <br> `protected`|
|父类成员：`private`<br> `protected` <br> `public`|继承类型：`: protected`|子类成员：`private`<br> `protected` <br> `protected`|
|`private`<br> `protected` <br> `public`| `: public` | `private`<br> `protected` <br> `public`|
|父类成员：`private`<br> `protected` <br> `public`|继承类型：`: public`|子类成员：`private`<br> `protected` <br> `public`|

---

# Item 8 : une affaire d'héritage 继承之事

L'héritage **donne accès aux méthodes et aux données du(des) parent(s)...ou pas**
继承**可能**让你访问父类的方法和数据，但也**可能不行**

- **Exo 8.1** Créer les classe `Parent` et `Son` pour faire fonctionner le code ci-dessous
**练习 8.1** 编写 `Parent` 与 `Son` 两个类，让下面的代码能够运行

```c++
int main(){
  Parent p{42};
  p.print_parent(); // output : "Parent ; v = 42"
  std::cout << "parent value " << p.v << std::endl; // output : "parent value 42"
  Son s{};
  s.set_value(42);
  s.print(); // output "The Child, Parent ; v =42"
  s.print_parent(); // output : "Parent ; v = 42"
  std::cout << s.v; // output : "42"
}
```
**Modifier** `Son` pour que les deux dernières lignes ne fonctionnent pas, puis pour que les "enfants" de `Son` n'accèdent pas aux données/méthodes de `Parent`.
**修改** `Son`，使最后两行代码无法执行；然后进一步修改，让 `Son` 的“子类”无法访问 `Parent` 的数据或方法。

---

# Item 8 : une affaire d'héritage 继承之事
L'héritage permet de se **faire passer pour...**
继承允许派生类**伪装成其他类型……**
```c++
struct Base{
  void print() {std::cout << "Base"<< std::endl;}
};
struct Derived : public Base{
  void print() {
    std::cout << "Derived"<< std::endl;
  }
};

int main(){
  Derived d{};
  d.print(); // "Derived"
  Base& b = d; // &意味着引用，b引用d但是b的类型是Base，b和d其实是同一个实例
               // 静态绑定：编译时确定调用哪个版本的print
  b.print(); // "Base"
}
```

C'est ce que l'on appelle le **polymorphisme**, l'objet est à la fois `Base` et `Derived`
这就是所谓的**多态**，对象既是 `Base` 也是 `Derived`

---

# Item 8 : une affaire d'héritage 继承之事

L'héritage permet de **redéfinir (surcharger) le comportement du parent** (polymorphe)
继承可以**重新定义（重载）父类的行为**（多态）

```c++
#include <iostream>

struct Base{
  // virtual permet de faire du polymorphisme
  virtual void print() {std::cout << "Base"<< std::endl;}
  void print2(){std::cout << "Base"<< std::endl;}
};
struct Derived : public Base{
  void print() override {std::cout << "Derived"<< std::endl;}
  void print2(){std::cout << "Derived"<< std::endl;}
};

int main(){
  Derived d{};
  d.print(); // "Derived"
  d.print2(); // "Derived"
  Base& b = d;
  b.print(); // "Derived"
  b.print2(); // "Base"
}
```

Attention dans ce cas le destructeur de la classe de base doit être **virtuel**.
注意，此时基类的析构函数必须是**虚函数**。

---

# Item 8 : une affaire d'héritage 继承之事

L'héritage permet de **redéfinir (surcharger) le comportement du parent**
继承可以**重新定义（重载）父类的行为**
Destructeur de classe de base virtuel **ou risque de non destruction de la classe dérivée**
基类析构函数需要设为虚函数，**否则派生类可能无法正确析构**

```c++
struct Base{
  virtual void print() {std::cout << "Base"<< std::endl;}
  virtual ~Base() = default;
};
struct Derived : public Base{
  void print() override {std::cout << "Derived"<< std::endl;}
};

int main(){
  Base* b = new Derived{};
  delete b; // delete Derived only if ~Base is virtual...
}
```

---

# Item 8 : une affaire d'héritage 继承之事

L'héritage permet de **redéfinir (surcharger) le comportement du parent**
继承可以**重新定义（重载）父类的行为**
Attention ce **n'est possible que** pour un héritage **public**
注意，这**只适用于**`public` **继承**

```c++
struct Base{
  virtual void print() {std::cout << "Base"<< std::endl;}
  virtual ~Base() = default;
};
struct Derived : private Base{
  void print() override {std::cout << "Derived"<< std::endl;}
};

int main(){
 Derived d{};
  d.print(); // "Derived"
  Base& b = d; // KO : Base is an inaccesible base of Derived
}
```

---

# Item 8 : une affaire d'héritage 继承之事

- L'héritage **donne accès aux méthodes et aux données du(des) parent(s)**
继承**可以访问父类的方法和数据**
  - à l'intérieur de la classe dérivée (tous les types d'héritages)
  - 在派生类内部（适用于所有继承类型）
  - à l'extérieur de la classe dérivée (héritage ``public``)
  - 在派生类外部（仅限 `public` 继承）
- L'héritage, s'**il est ``public``**, permet de :
当继承是 **`public`** 时，它还允许：
  - se **faire passer pour...**
  - **伪装成父类或其他类型**
  - **redéfinir (surcharger) le comportement du parent**
  - **重定义（重载）父类的行为**

**Exo 8.2** Construire une classe de base `Point` et deux classes dérivées `Point2D` et `Point3D` (ne contenant qu'une méthode print affichant le nom de la classe). Afficher les noms des classes dérivées `Point2D` et `Point3D` mais depuis une fonction manipulant un `Point&`.
**练习 8.2** 构建一个基类 `Point` 和两个派生类 `Point2D`、`Point3D`（仅包含打印类名的 `print` 方法）。通过一个接受 `Point&` 的函数打印两个派生类的名称。
