---
marp: true
theme: default
paginate: true


math: katex
---

# **Programmation Orientée Objet pour le Calcul Scientifique : Part II Deep Water** 面向科学计算的面向对象编程：第二部分 深水区

---

# Organisation du cours 课程安排

Sous forme d'**Item**, se raccrochant à trois catégories :
以条目形式呈现，对应三个类别：

- Outils et Langage (TooL)
工具与语言（TooL）
- **Gestion de la mémoire (Mem)**
**内存管理（Mem）**
- Orienté objet (OO)
面向对象（OO）
- Programmation statique (Static)
静态编程（Static）

Vous n'êtes pas seul : https://en.cppreference.com/w/ est votre allié...
你并不孤单：https://en.cppreference.com/w/ 是你的盟友...

# Item 16 : copier sans copier 第16项：复制而不复制

Le but de cet item est d'introduire (un peu grossièrement) les notions :
此项的目标是（相对粗略地）介绍以下概念：

- de *rvalue*
关于 *rvalue*
- de *rvalue reference* `&&` dans les signatures de fonctions/méthodes
关于函数/方法签名中的 *rvalue reference* `&&`
- de *std::move*
关于 *std::move*

Toutes ces notions vont nous aider à **déplacer la mémoire** d'un objet/variable
这些概念将帮助我们**移动对象/变量的内存**

- afin d'éviter des copies inutiles et coûteuses
以避免不必要且昂贵的复制
- ces notions ont donc leur intérêt dans une optique *Calcul Scientifique*
因此在*科学计算*的视角下这些概念具有意义

# Item 16 : copier sans copier 第16项：复制而不复制

Une ***rvalue*** 1/5
***rvalue*** 概述 1/5

- est une valeur que l'on ne peut pas nommer (temporaire, retour de fonction...)
是无法命名的值（临时量、函数返回值等）
- ne peut s'utiliser que dans le membre de droite d'une affectation (right-value)
只能用于赋值的右侧（right-value）
- n'a pas d'adresse utilisable
没有可用的地址

```c++
int a = 4, b = 2; // 4 & 2 are rvalues
int c = a+b; // a+b = rvalue
std::string s ="hello"; // "hello" = rvalue
int d = a++; // a++ = rvalue

int_ptr = &(a+b); // ERROR : cannot take rvalue address

int func() {return 42;}

auto a = func(); // func() = rvalue
```

---

# Item 16 : copier sans copier 第16项：复制而不复制

Une ***rvalue*** 2/5
***rvalue*** 概述 2/5
s'oppose à la classique **lvalue** (left value), qui elle peut :
与经典的 **lvalue**（左值）相对，后者可以：

- être nommée
被命名
- apparaître à droite ou à gauche d'une affectation
出现在赋值的左侧或右侧
- avoir une adresse
具有地址

```c++
int a = 4, b = 2; // a & b are lvalues
int c = a+b; // c is a lvalue
std::string s ="hello"; // s is a lvalue

int* int_ptr = &a; // OK can take lvalue address
```

---

# Item 16 : copier sans copier 第16项：复制而不复制

Une ***rvalue*** 3/5
***rvalue*** 概述 3/5
Petit Quiz : **rvalue** ou **lvalue** ??
小测验：**rvalue** 还是 **lvalue**？

```c++
struct A{};
A a{}; // a lvalue
A{}; // A{} rvalue
int global = 1;
int& func() {return global;} // func() lvalue
func(); //  func() rvalue

```

Comment savoir ? Impossible d'affecter dans une rvalue :
如何判断？无法向 rvalue 赋值：

```c++
int i = 1 , j = 2;
i + 2 = j; // Error
3 = j; // Error
```

---

# Item 16 : copier sans copier 第16项：复制而不复制

Une ***rvalue*** 4/5
***rvalue*** 概述 4/5
peut être utilisée pour initialiser :
可以用来初始化：

- une *lvalue*
一个 *lvalue*
- une référence **constante** de *lvalue*
一个 *lvalue* 的**常量**引用

```c++
int a = 4, b = 2; // lvalues initialized by rvalues
int c = a + b; // lvalue initialized by rvalue
std::string s = "hello"; // lvalue initialized by rvalue
int const& d = a+b; // lvalue const reference initialized by rvalue
```

- une référence de *lvalue* ne peut-être initialisée que par une *lvalue*
一个 *lvalue* 引用只能由 *lvalue* 初始化

```c++
int& d = a; // lvalue reference initialized by lvalue
int& e = 3; // ERROR
```

---

# Item 16 : copier sans copier 第16项：复制而不复制

Une ***rvalue*** 5/5
***rvalue*** 概述 5/5
Encore un quiz...
再次小测...

- une *rvalue* ne peut pas être modifiée ?
*rvalue* 不能被修改？
- on peut toujours faire une affectation dans une *lvalue* ?
我们总能在 *lvalue* 中执行赋值吗？

```c++
// Hint for rvalue
A{}.method(); 

// Hint for lvalue 
int const c = 3;
```

---

# Item 16 : copier sans copier 第16项：复制而不复制

La référence de *rvalue* `&&`
*rvalue* 引用 `&&`
Commençons par un exemple : y-a-t-il une recopie du vecteur ?
先从一个例子开始：这个向量发生了复制吗？

```c++
std::vector<int> a = std::vector<int>{1,2,3,4}; // lvalue from rvalue
```

La réponse est **non** ! ouf...Mais pourquoi ? Quel est l'opérateur appelé ?
答案是**没有**！呼……但为什么？调用的是哪个运算符？
`std::vector<T>::operator=(std::vector<T> const& rhs)`  ? Non car :
`std::vector<T>::operator=(std::vector<T> const& rhs)`？不是，因为：

- il attend une référence de *lvalue* et non de *rvalue*
它期望的是 *lvalue* 引用而不是 *rvalue*
- cet opérateur fait d'ailleurs une copie...
而且该运算符确实会执行一次复制…

La définition de la ***rvalue-reference*** **`&&`** permet de normaliser ce comportement
***rvalue-reference*** **`&&`** 的定义能够规范这种行为
`std::vector<T>::operator=(std::vector<T>&& rhs)`

- l'opérateur prend une rvalue et "vole" sa mémoire
该运算符接收一个 *rvalue* 并“窃取”其内存

---

# Item 16 : copier sans copier 第16项：复制而不复制

La fonction **`std::move`** 1/2
函数 **`std::move`** 1/2
Peut-on "voler" la mémoire d'une *lvalue* ?
我们能否“窃取”一份 *lvalue* 的内存？

```c++
struct A {
  std::vector<int> data;
};
int main() {
  std::vector<int> vec {1,2,3,4};
  // don't want to use vec anymore but want to store it in A.data
  A a{};
  a.data = vec; // copy...
}
```

Oui grâce à la méthode **`std::move`** qui "transforme" une *lvalue* en *rvalue*
可以，借助 **`std::move`** 方法，它会将 *lvalue* “转换”为 *rvalue*

---

# Item 16 : copier sans copier 第16项：复制而不复制

La fonction **`std::move`** 2/2
函数 **`std::move`** 2/2
Peut-on "voler" la mémoire d'une *lvalue* ?
我们能否“窃取”一份 *lvalue* 的内存？

- Oui grâce à la méthode **`std::move`** qui "transforme" une *lvalue* en *rvalue*
可以，借助 **`std::move`** 方法，它会将 *lvalue* “转换”为 *rvalue*

```c++
struct A {
  std::vector<int> data;
};
int main() {
  std::vector<int> vec {1,2,3,4};
  // don't want to use vec anymore but want to store it in A.data
  A a{};
  a.data = std::move(vec); // no copy...
}
```

Attention, après un `std::move(var)` `var` n'est plus **utilisable**
注意，在执行 `std::move(var)` 之后，`var` 将不再**可用**

---

# Item 16 : copier sans copier 第16项：复制而不复制

La fonction **`std::move`** 2/2
函数 **`std::move`** 2/2
Peut-on "voler" la mémoire d'une *lvalue* ?
我们能否“窃取”一份 *lvalue* 的内存？

- Oui grâce à la méthode **`std::move`** qui "transforme" une *lvalue* en *rvalue*
可以，借助 **`std::move`** 方法，它会将 *lvalue* “转换”为 *rvalue*

**Exo 16.1** construisez un tableau et "voler" sa mémoire dans un autre tableau. Vérifier que ce premier tableau n'a plus de mémoire.
**练习 16.1** 构建一个数组，并将它的内存“窃取”到另一个数组中。验证第一个数组已经没有内存。

**Exo 16.2** créez une fonction qui prend un vecteur par référence de *rvalue* et qui l'affiche à la console. Appelez-la dans un `main`, à partir d'une *rvalue* et voyez ce qui se passe lorsque vous l'appelez à partir d'une *lvalue*.
**练习 16.2** 创建一个函数，接受 *rvalue* 引用的向量并在控制台输出。在 `main` 中以 *rvalue* 调用它，然后看看当你用 *lvalue* 调用时会发生什么。

**Exo 16.3** reprenez l'exo 16.2 et construisez dans votre fonction un vecteur à partir de votre référence de *rvalue*. Attention il ne devra pas y avoir de copie.
**练习 16.3** 回到练习 16.2，在函数中利用 *rvalue* 引用构建一个向量，注意不能发生任何拷贝。

---

# Item 16 : copier sans copier 第16项：复制而不复制

Les fonctions implicites des classes sont enrichies avec des `&&`
类的隐式函数通过 `&&` 得到扩展
Rappelez-vous l'*item 10*
请回忆一下*第 10 项*

```c++
struct A{ // ce que vous ne voyez pas
   A() {}; // constructor
  ~A() {}; // destructor
   A(A const& a) {m_i = a.i;} // copy constructor
   A& operator= (A const& a) {m_i = a.i;} // copy assignment
   int m_i = 0;
}; // move operators kept under silence for the moment
```

Sont maintenant automatiquement ajouteés les opérations de *move*
现在会自动补充 *move* 操作

```c++
A(A&& a) : m_i{std::move(a.i)} {} // move constructor
A& operator= (A&& a) {m_i = std::move(a.i);} // move assignment
```

---

# Item 16 : copier sans copier 第16项：复制而不复制

Un petit exercice : **Exo 16.4** :
小练习：**练习 16.4**：

- écrivez une classe contenant explicitement les sept méthodes implicites.
编写一个类，显式包含七个隐式方法。
- utilisez toutes ces méthodes dans une fonction `main`.
在 `main` 函数中使用全部这些方法。
- vous pouvez repartir de l'**Exo 10.1** et ajouter les opérations de move
你可以在 **练习 10.1** 的基础上添加 move 操作。
- pour voir quelles sont les méthodes appelées, ajoutez un affichage de la signature
为了观察调用了哪些方法，添加签名的打印输出。

---

# Item 17 : les pointeurs intelligents 第17项：智能指针

La gestion de zones mémoires via des pointeurs n'est pas sans risque :
通过指针管理内存区域并非毫无风险：

- oubli du `delete` = fuite mémoire ; double `delete` = crash
忘记调用 `delete` 会导致内存泄漏；重复 `delete` 会引发崩溃
- manipulation d'un pointeur nul
解引用空指针
- erreur dans l'arithmétique de pointeur
指针运算出错

Le C++, à partir de la norme 11 propose donc des classes de ***smart pointer***
因此，自 C++11 起提供了多种***智能指针***类

- `std::unique_ptr<T>`
`std::unique_ptr<T>` 独占所有权指针
- `std::shared_ptr<T>`
`std::shared_ptr<T>` 共享所有权指针
- `std::weak_ptr<T>`
`std::weak_ptr<T>` 弱引用指针

Les ***smart pointers*** **désallouent automatiquement la mémoire** pour vous
***智能指针*** 会为你**自动释放内存**

---

# Item 17 : les pointeurs intelligents 第17项：智能指针 

L'unique `std::unique_ptr<T>` 1/2
独占型 `std::unique_ptr<T>` 1/2

- la donnée pointée est unique et ne peut-être copiée
被指向的数据具有唯一所有权，无法被复制
不能将地址赋值给另一个指针
- la donnée pointée est détruite quand le pointeur est détruit
当指针被销毁时，被指向的数据也会被销毁
- la donnée peut être transférée à un autre unique_ptr via un `std:move`
可以通过 `std::move` 将所有权转移给另一个 `unique_ptr`

```c++
#include <memory>

int main()
{
  {
    std::unique_ptr<int> int_ptr(new int{3});
    std::unique_ptr<int> int_ptr2 = int_ptr; // ERROR
    std::unique_ptr<int> int_ptr3 = std::move(int_ptr); // OK. int_ptr undefined
  } // pointed data *int is deleted
}
```

---

# Item 17 : les pointeurs intelligents 第17项：智能指针

L'unique `std::unique_ptr<T>` 2/2
独占型 `std::unique_ptr<T>` 2/2

- comme dans un pointeur classique, la donnée est accessible via `operator*`
与传统指针一样，可以通过 `operator*` 访问所指向的数据
- le pointeur stocké dans `std::unique_ptr<T>` est accessible par la méthode `get()`
存储的原始指针可通过 `get()` 方法获取
- un `std::unique_ptr<T>` peut être créé via la méthode `std::make_unique(ptr)`
可以使用 `std::make_unique(ptr)` 创建 `std::unique_ptr<T>`

```c++
std::unique_ptr<int> int_ptr = std::make_unique<int>(3);
std::cout << *int_ptr << std::endl;
int* ptr = int_ptr.get(); 
std::cout << *ptr << std::endl; 
```

**Exo 17.1** : Créer un `unique_ptr<std::string>` pour manipuler une chaîne de caractère. Affichez le contenu de la chaîne et l'adresse du pointeur `std::string*`. Transférez votre pointeur à un nouveau `unique_ptr` et refaites les mêmes affichages.
**练习 17.1**：创建一个 `unique_ptr<std::string>` 来处理字符串，输出字符串内容以及 `std::string*` 指针地址。将指针转移到新的 `unique_ptr` 后重复同样的输出。

---

# Item 17 : les pointeurs intelligents 第17项：智能指针 

Le partage avec `std::shared_ptr<T>` 1/3
通过 `std::shared_ptr<T>` 共享 1/3

- la donnée pointée peut-être partagée entre plusieurs `std::shared_ptr<T>`
被指向的数据可以在多个 `std::shared_ptr<T>` 之间共享
- la donnée pointée est détruite quand le 'dernier' `shared_ptr` est détruit
当“最后一个” `shared_ptr` 被销毁时，数据才会被释放

```c++
#include <memory>
int main()
{
  {
   std::shared_ptr<int> int_ptr(new int{3}); // int allocated
    {
      std::shared_ptr<int> int_ptr2 = int_ptr; // OK, no new allocation
    } // int_ptr2 released but the data is still allocated
 
  }  // pointed data *int is deleted
}
```

---

# Item 17 : les pointeurs intelligents 第17项：智能指针 

Le partage avec `std::shared_ptr<T>` 2/3
通过 `std::shared_ptr<T>` 共享 2/3

- L'accès à la donnée pointée ou au pointeur est identique au `unique_ptr`
对数据或指针的访问方式与 `unique_ptr` 相同
  - `operator*` pour la donnée et méthode `get()` pour le pointeur
  - 通过 `operator*` 访问数据，通过 `get()` 获取指针
- un shared_ptr peut être créé par la fonction `std::make_shared(ptr)`
可以使用 `std::make_shared(ptr)` 创建 shared_ptr

```c++
std::shared_ptr<int> int_ptr = std::make_shared<int>(3);
std::cout << *int_ptr << std::endl;
int* ptr = int_ptr.get();
std::cout << *ptr << std::endl; 
```

---

# Item 17 : les pointeurs intelligents 第17项：智能指针 

Le partage avec `std::shared_ptr<T>` 3/3
通过 `std::shared_ptr<T>` 共享 3/3

- le `shared_ptr` utilise un mécanisme de compteur de référence
`shared_ptr` 使用引用计数机制
- la donnée est allouée une seule fois et les `shared_ptr` se partage une référence
数据只分配一次，所有 `shared_ptr` 共享同一个引用
- si la donnée est modifiée via l'un des `shared_ptr` elle est modifiée pour tous
如果某个 `shared_ptr` 修改了数据，其他所有共享者都会看到该修改

```c++
std::shared_ptr<int> int_ptr = std::make_shared<int>(3);
std::shared_ptr<int> int_ptr2 = int_ptr;
(* int_ptr)++; // increment value
std::cout << *int_ptr2 << std::endl; // 4
```

**Exo 17.2** Créer un `shared_ptr<double>` et copiez-le dans un autre shared_ptr. Modifiez la valeur du `double` depuis l'un des `shared_ptr` et vérifiez qu'elle est bien modifiée dans le second.
**练习 17.2** 创建一个 `shared_ptr<double>` 并将其复制到另一个 shared_ptr 中。从其中一个 `shared_ptr` 修改 `double` 的值，确认另一个也同步变化。

---

# Item 17 : les pointeurs intelligents 第17项：智能指针 

l'accès si possible avec `std::weak_ptr<T>` 1/2
使用 `std::weak_ptr<T>` 的受限访问 1/2

- le `weak_ptr` permet d'accéder à une donnée contenue dans un `shared_ptr`
`weak_ptr` 允许访问由 `shared_ptr` 管理的数据
- sans pour autant contribuer au comptage de référence
同时不会增加引用计数
- la donnée pointée peut donc être désallouée
因此被指向的数据仍然可能被释放

```c++
 std::weak_ptr<int> int_weak_ptr;
{
  std::shared_ptr<int> int_ptr = std::make_shared<int>(3);
  int_weak_ptr = int_ptr;
  if ( !int_weak_ptr.expired()) {std::cout << "weak_ptr data alive."<< "\n";}
}
if (int_weak_ptr.expired()) {std::cout << "weak_ptr data deleted."<< "\n";}
```

---

# Item 17 : les pointeurs intelligents 第17项：智能指针

l'accès si possible avec `std::weak_ptr<T>` 2/2
使用 `std::weak_ptr<T>` 的受限访问 2/2

- le weak_ptr ne permet pas un accès direct à la donnée pointée
`weak_ptr` 无法直接访问指向的数据
- il faut d'abord recopier dans un `shared_ptr` avec la méthode `lock`
需要先通过 `lock` 方法将其拷贝为 `shared_ptr`，防止在访问时数据被释放

```c++
std::shared_ptr<int> int_sptr = std::make_shared<int>(3);
std::weak_ptr<int> int_wptr = int_sptr;  
// Try to access pointed value from weak_ptr
if ( !int_wptr.expired()) {
  auto shared_ptr_tmp = int_wptr.lock();
  std::cout << "weak_ptr data "<< *shared_ptr_tmp <<"\n";
}
```

---

# Item 17 : les pointeurs intelligents 第17项：智能指针

Utilisation d'un destructeur spécifique 1/2
自定义析构器的使用 1/2

- par défaut un `delete` sur l'objet pointé
默认会对指向的对象执行 `delete`
- possibilité de fournir un destructeur spécifique
可以提供自定义析构器
- sous la forme d'une fonction générique (Foncteur, $\lambda$...)
形式可以是泛型函数（函数对象、$\lambda$ 等）

```c++
// unique_ptr case
auto my_deleter = [](PointedObject* ptr) 
                  {
                    std::cout << "Delete PointedObject";
                    delete ptr;
                  };
using unique_ptr_with_del = std::unique_ptr<PointedObject, decltype(my_deleter)>;
unique_ptr_with_del u_ptr(new PointedObject{},my_deleter);
```

---

# Item 17 : les pointeurs intelligents 第17项：智能指针

Utilisation d'un destructeur spécifique 2/2
自定义析构器的使用 2/2

- par défaut un `delete` sur l'objet pointé
默认会对指向的对象执行 `delete`
- possibilité de fournir un destructeur spécifique
可以提供自定义析构器
- sous la forme d'une fonction générique (Foncteur, $\lambda$...)
形式可以是泛型函数（函数对象、$\lambda$ 等）

```c++
// shared_ptr case
auto my_deleter = [](PointedObject* ptr) 
                  {
                    std::cout << "Delete PointedObject";
                    delete ptr;
                  };

std::shared_ptr<PointedObject> s_ptr(new PointedObject{},my_deleter);
```

---

# Item 17 : les pointeurs intelligents 第17项：智能指针

- **Exo 17.3** 1/4 : Maille et face d'un maillage. On souhaite créer un use case d'une maille contenant un pointeur vers sa face. Les opérations seront les suivantes :
**练习 17.3** *1/4*：网格中的单元与面。我们希望构建一个单元包含指向其面的指针的用例。操作如下：
  - création d'une maille (classe `Cell`)
  创建一个单元（`Cell` 类）
  - affichage de l'id de sa face (champ `int` dans la classe `Face`)
  输出其面 ID（`Face` 类中的 `int` 字段）
  - destruction de la maille
  销毁该单元
  
  On souhaite réaliser trois scénarios (dans trois fonctions que vous appellerez depuis votre `main()`).
  我们希望实现三个场景（分别在 `main()` 中调用的三个函数）。

---

# Item 17 : les pointeurs intelligents 第17项：智能指针

- **Exo 17.3** 2/4 : Maille et face d'un maillage. On souhaite créer un use case d'une maille contenant un pointeur vers sa face.
**练习 17.3** *2/4*：网格中的单元与面。我们希望构建一个单元包含指向其面的指针的用例。
  - **Scénario 1** : la maille est la seule à posséder le pointeur de sa face. Elle ne le partage pas. Dans ce scénario, vous écrirez le cas où la maille transfère la propriété de sa face à une nouvelle maille avant d'être détruite.
  **场景 1**：该单元独占其面的指针，不与他人共享。在此场景中，编写单元在被销毁前将面指针的所有权转移给新单元的情况。

--- 

# Item 17 : les pointeurs intelligents 第17项：智能指针

- **Exo 17.3** 3/4 : Maille et face d'un maillage. On souhaite créer un use case d'une maille contenant un pointeur vers sa face.
**练习 17.3** *3/4*：网格中的单元与面。我们希望构建一个单元包含指向其面的指针的用例。
  - **Scénario 2** : la maille peut partager sa face et celle-ci peut rester allouée même après la suppression de la cellule. Dans l'exercice vous recopierez la face de la maille dans un pointeur extérieur à la maille qui devra 'survivre' à la destruction de la maille. Pour le vérifier on affichera l'id de la face après la destruction de la maille.
  **场景 2**：单元可以共享其面，即使单元被删除，面仍可继续分配。在练习中，将面的指针复制到单元外部的指针，使其在单元销毁后仍“存活”。为验证效果，在单元销毁后打印面的 ID。

---
# Item 17 : les pointeurs intelligents 第17项：智能指针

- **Exo 17.3** 4/4 : Maille et face d'un maillage. On souhaite créer un use case d'une maille contenant un pointeur vers sa face.
**练习 17.3** *4/4*：网格中的单元与面。我们希望构建一个单元包含指向其面的指针的用例。
  - **Scénario 3** : la maille peut toujours partager sa face que l'on va à nouveau stocker dans un pointeur. En revanche on veut que cette face soit effectivement détruite lorsque la maille est détruite. On vérifiera donc que ce pointeur a expiré après la destruction de la maille.
  **场景 3**：单元仍可以分享其面，并再次将其存入一个指针中。但我们希望当单元被销毁时，该面也确实被销毁。因此需确认该指针在单元销毁后已过期。
