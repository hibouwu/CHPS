---
marp: true
theme: default
paginate: true


math: katex
---

# **Programmation Orientée Objet pour le Calcul Scientifique : Part II Deep Water** 科学计算的面向对象编程：第二部分 深水区

---

# Organisation du cours 课程组织

Sous forme d'**Item**, se raccrochant à trois catégories :
以**条目**形式组织，归入三大类：

- Outils et Langage (TooL)
- Gestion de la mémoire (Mem)
- **Orienté objet (OO)**
- Programmation statique (Static)
- 工具与语言（TooL）
- 内存管理（Mem）
- **面向对象（OO）**
- 静态编程（Static）

Vous n'êtes pas seul : https://en.cppreference.com/w/ est votre allié...
你并不孤单： https://en.cppreference.com/w/ 是你的盟友……

---

# Item 18 : la règle des exceptions 异常规则

- Quelle approche utiliser pour gérer un comportement non souhaité/d'erreur ?
- 对不期望的行为/错误，应采用什么处理方式？

- Un code de retour ?
- 返回码？

```c++
int func(int size) {
  auto max_element = 1e3;
  if (size > max_element) return 1;
  else {
    // do treatment
    return 0;
  }
}

int main() {
  func(10000); // error code not tested...
}
```

---

# Item 18 : la règle des exceptions 异常规则

- Problèmes des codes de retour :
  - ne sont (souvent) pas testés à l'appel de la fonction
  - polluent la signature de votre méthode (retour ou argument)
  - ne sont pas normalisés, votre convention devra être explicitée...
- En C++ et dans de nombreux langages objets, les **exceptions** viennent à la rescousse.
  - Elles offrent un mécanisme d'interruption en cas d'erreur par l'envoi/réception d'objet, par exemple de type `std::exception` ou dérivés en C++.
- 返回码的问题：
  - 调用函数时（往往）不会去测试
  - 污染方法签名（返回值或参数）
  - 没有标准化，需要明确约定
- 在 C++ 和许多面向对象语言中，**异常**可以救场。
  - 通过发送/接收对象（如 `std::exception` 或其派生）提供错误时的中断机制。

---

# Item 18 : la règle des exceptions 异常规则

- Un premier exemple
- 第一个例子

```c++
#include <iostream>
#include <exception>

void func(int size) {
  auto max_element = 1e3;
  if (size > max_element) throw std::exception();
  else {} // do treatment 
}
int main() {
  try {
    func(10000); // error code not tested...
  }
  catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
```

---

# Item 18 : la règle des exceptions 异常规则

- Une fonction/méthode pouvant lever une erreur est mise dans un bloc `try`
- L'exception est levée grâce à la méthode `throw`
- L'exception levée peut-être une classe du standard mais aussi une classe utilisateur
- le standard propose et utilise de nombreux types d'exceptions dérivés de la classe de base `std::exception`
- si l'exception est levée, l'exécution s'arrête et reprend dans le bloc `catch`
- l'absence de levée d'exception dans une méthode peut s'indiquer avec `noexcept`
- la libération propre de la mémoire dans le bloc try est gérée automatiquement (*stack unwinding*).
- 可能抛出错误的函数/方法要放在 `try` 块里
- 使用 `throw` 来抛出异常
- 抛出的异常可以是标准库类，也可以是自定义类
- 标准库提供了许多派生自 `std::exception` 的异常类型
- 如果异常被抛出，执行会停止并在 `catch` 块继续
- 可用 `noexcept` 标识方法不会抛异常
- try 块中的资源会自动释放（*栈展开*）

---

# Item 18 : la règle des exceptions 异常规则

- L'exception levée peut-être une classe du standard mais aussi une classe utilisateur.
- 抛出的异常可以是标准库类，也可以是自定义类。

```c++
struct exception {
  std::string message;
};

int main(){
  try {
    throw exception{"an error occured"};
  }
  catch (exception& e) {
    std::cout << e.message << std::endl;
  }
}
```

---

# Item 18 : la règle des exceptions 异常规则

- le standard propose et utilise de nombreux types d'exceptions dérivées de la classe de base `std::exception`, par exemple :标准库提供并使用许多派生自 `std::exception` 的异常类型，例如：
  - `std::bad_alloc` : levée lors d'un échec de `new` `new` 失败时抛出
  - `std::bad_cast` : levée lors d'un échec de `dynamic_cast` `dynamic_cast` 失败时抛出
  - `std::bad_typeid` : levée lors d'un échec de typeid `typeid` 失败时抛出
  - `std::io_base::failure` : levée lors d'un échec des fonctions de iostream iostream 函数失败时抛出
  - `std::bad_weak_ptr` : levée lorsqu'un `weak_ptr` pointe sur un objet détruit `weak_ptr` 指向已销毁对象时抛出

le catalogue est disponible : <https://en.cppreference.com/w/cpp/error/exception>完整列表。
le type de l'exception donne des informations sur la nature de l'erreur. 异常类型传达了错误的性质。
Il faut inclure le header : `#include <exception>`

---

# Item 18 : la règle des exceptions 异常规则

- Toutes ces exceptions sont à votre disposition pour votre code. Ainsi vous pourrez utiliser :
  - `std::runtime_error` pour une erreur à l'exécution
  - `std::range_error` pour un problème de taille de tableau
  - `std::invalid_argument` pour un argument incorrect dans une fonction
- la méthode `what()`de ces exceptions vous retournera une chaîne de caractère indiquant son type.
- Ces exceptions peuvent prendre en argument une chaîne `char*`
- 这些异常都可直接在代码中使用。例如：
  - `std::runtime_error`：运行时错误
  - `std::range_error`：数组大小问题
  - `std::invalid_argument`：非法参数
- 这些异常的 `what()` 方法会返回描述类型的字符串。
- 构造函数可以接收 `char*` 字符串。

```c++
throw std::runtime_error{"My error message"};
```

---
# Item 18 : la règle des exceptions 异常规则

- Toutes ces exceptions sont à votre disposition pour votre code.
- la méthode `what()`de ces exceptions vous retournera une chaîne de caractère indiquant son type.

- Ces exceptions peuvent prendre en argument une chaîne `char*`
- 以上这些异常都可在代码中直接使用。
- 它们的 `what()` 方法会返回描述类型的字符串。
- 构造函数可接受 `char*` 字符串。

```c++
throw std::runtime_error{"My error message"};
```

**Exo 18.1** : écrivez une fonction qui affiche l'entier qui lui est passé en argument s'il est positif et qui lève une exception de type `std::invalid_argument` s'il est négatif. Un message explicatif sera passé à l'exception. Appelez cette fonction depuis un `main` avec un entier positif et un entier négatif.
**练习 18.1**：编写一个函数，若传入整数为正则打印它，若为负则抛出 `std::invalid_argument` 并附带解释消息。在 `main` 中用一个正数和一个负数调用它。

---

# Item 18 : la règle des exceptions 异常规则

- si l'exception est levée, l'exécution s'arrête et reprend dans le bloc `catch` 1/3
  - il faut préciser le type de l'exception en argument
- 若异常被抛出，执行停止并在 `catch` 块继续 1/3
  - 需要在参数中指明异常类型
  
  ```c++
  catch(std::runtime_exception& e ) { ...}
  ```

  - un bloc de `catch` peut donc être écrit pour chaque type d'exception
    - cela permet de segmenter le traitement en fonction de l'exception levée
  - l'appel de `catch(...)` capturera tous les types d'exception.
    - Cela perd de l'intérêt puisque l'on ne sait pas quelle est l'exception concernée
    - Peut se mettre en dernier rempart, si on veut à tout prix que le code n'échoue pas...
  - 可以为每种异常写一个 `catch` 块
    - 便于按抛出的异常类型分开处理
  - `catch(...)` 会捕获所有异常
    - 但无法得知具体异常类型
    - 可作为避免程序失败的最后屏障

---

# Item 18 : la règle des exceptions 异常规则

- si l'exception est levée, l'exécution s'arrête et reprend dans le bloc `catch` 2/3
- 若异常被抛出，执行停止并在 `catch` 块继续 2/3

```c++
struct exception {std::string message;};
void func(int size) {
  auto max_element = 1e3;
  if (size > max_element) throw std::invalid_argument("i must be < 1000");
  else { throw exception{"an error occured"}; } // error in treatment 
}
int main(){
  try {
    func(5e2); // first catch
    func(5e3); // second catch
  }
  catch (exception& e) { std::cout << e.message << std::endl; }
  catch (std::invalid_argument& e) { 
    std::cout << " invalid argument : " << e.what() << std::endl; }
}
```

---

# Item 18 : la règle des exceptions 异常规则

- l'appel de `catch(...)` capturera tous les types d'exception. 3/3
- `catch(...)` 会捕获所有类型的异常 3/3

```c++
struct exception {std::string message;};
void func(int size) {
  auto max_element = 1e3;
  if (size > max_element) throw std::invalid_argument("i must be < 1000");
  else { throw exception{"an error occured"}; } // error in treatment 
}
int main(){
  try {
    func(5e2);
    func(5e3); // both catched in the same block
  }
  catch (...) {
    std::cout << "An exception occured" << std::endl;
  }
}
```

---

# Item 18 : la règle des exceptions 异常规则

- si l'exception est levée, l'exécution s'arrête et reprend dans le bloc `catch`
  - il faut préciser le type de l'exception en argument
- 若异常被抛出，执行停止并在 `catch` 块继续
  - 需要在参数中指明异常类型

  ```c++
  catch(std::runtime_exception& e ) { ...}
  ```

  - un bloc de `catch` peut donc être écrit pour chaque type d'exception
  - l'appel de `catch(...)` capturera tous les types d'exception.
  - 可以为每种异常写一个 `catch` 块
  - `catch(...)` 会捕获所有异常

**Exo 18.2** : reprenez votre exercice **18.1** et ajoutez un bloc `try/catch` pour capturer votre exception et en afficher le message.
**练习 18.2**：在练习 **18.1** 基础上加入 `try/catch` 捕获异常并输出消息。

---

# Item 18 : la règle des exception 异常规则

- la libération propre de la mémoire dans le bloc `try` est gérée automatiquement
  - *stack unwinding*
- `try` 块中的内存会自动释放
  - *栈展开*

```c++
struct A {
     ~A() {std::cout << "~A()" << std::endl;}
};
int main() {
 try { 
   A a{}; 
   throw std::exception{};
}
 catch(...) {}
} // ~A() is called. Ressource properly destroyed.
```

---

# Item 18 : la règle des exception 异常规则

- la libération propre de la mémoire dans le bloc try est gérée automatiquement
  - *stack unwinding*
- cette gestion de la mémoire a un coût :
  - peut empêcher des optimisations du compilateur
- en raison de cette gestion mémoire liée à l'exception : 
  - il n'est pas possible de lever une exception dans des destructeurs
- try 块中的内存会自动释放
  - *栈展开*
- 这种内存管理有代价：
  - 可能阻止编译器优化
- 因为与异常相关的内存管理：
  - 析构函数中不能再抛异常

```c++
struct A { ~A() {throw std::runtime_error("failed");} };

int main() {
 try { A a{}; }
 catch(...) {}
} // crash: terminate called after throwing an instance of 'std::runtime_error'
```

---

# Item 18 : la règle des exception 异常规则

- l'absence de levée d'exception dans une méthode peut s'indiquer avec `noexcept`
- 方法不抛出异常可以用 `noexcept` 标注

```c++
void no_exception_function noexcept {
  // function not throwing any exception
  // and calling only functions not throwing any exception
}
```

- Cette qualification n'est **pas vérifiée** à la **compilation** mais à l'**exécution**
- L'exécution d'une fonction `noexcept` provoque un plantage
- 这一属性在**运行时**而非**编译时**检查
- `noexcept` 函数抛异常会导致崩溃

```c++
void function() noexcept {throw std::runtime_error("failed");}
int main() {
  try { function(); }
  catch(...) {}
} // crash: terminate called after throwing an instance of 'std::runtime_error'
```

---

# Item 18 : la règle des exception 异常规则

- les **destructeurs** sont par défaut `noexcept`
- pour aller plus loin : noexcept peut être conditionnel
  - pour expimer `noexcept` si et seulement si une autre fonction l'est...
- **析构函数** 默认 `noexcept`
- 进一步：`noexcept` 可以是有条件的
  - 仅当另一函数也 `noexcept` 时才标注

**Exo 18.3** : reprenez votre exercice **18.2** et créez maintenant votre propre classe `exception`, qui vous permettra par exemple de stocker la valeur de l'argument d'entrée de votre fonction qui a provoqué son déclenchement. Ecrivez le bloc `catch` pour la capturer. Au sein du bloc `catch` vous afficherez la valeur de l'entier stocké. Finalement constatez ce qui se passe lorsque vous mettez votre fonction d'affichage en `noexcept`.
**练习 18.3**：在练习 **18.2** 基础上创建自己的 `exception` 类，例如用来存储触发异常的函数输入参数值。编写 `catch` 块捕获它，并在其中打印存储的整数。最后将打印函数标记为 `noexcept`，观察会发生什么。

---

# Item 19 : Interfacer sans interface 没有 interface 的接口化
Qu'est-ce qu'une ***interface*** en programmation objet ?
在面向对象编程中，***接口*** 是什么？

- La définition d'un contrat
- un unique code pour manipuler différente implémentation de ce contrat
- 定义一种契约
- 用统一的代码操作该契约的不同实现

En **java** par exemple
例如在 **Java** 中

```java
public interface Solver {
  public void solve();
}
public class DirectSolver : implements Solver {
  public void solve() { System.out.println("Direct Solver")}
}
public class IterativeSolver : implements Solver {
  public void solve() { System.out.println("Iterative Solver")}
}
```

---
# Item 19 : Interfacer sans interface 没有 interface 的接口化

Qu'est-ce qu'une ***interface*** en programmation objet ?
在面向对象编程中，***接口*** 是什么？

- Une interface est une classe mère qui oblige ses enfants à implémenter ses méthodes.
- Les méthodes d'une interface sont la plupart du temps vide.
- 接口是一个基类，强制子类实现其方法。
- 接口的方法大多为空实现。

En **C++** ?
- 那么在 **C++** 呢？

- C++ ne contient pas de type `interface`....
- Il faut utiliser la notion de ***méthode virtuelle pure***
- C++ 没有 `interface` 类型……
- 要用***纯虚函数***的概念来实现。

---

# Item 19 : Interfacer sans interface 没有 interface 的接口化

**Méthode virtuelle pure** 1/5
**纯虚函数** 1/5

- la syntaxe est :
- 语法如下：

```c++
class MyInterface {
public:
  virtual void my_pure_virtual_method() = 0; // pure virtual method
  virtual ~MyInterface() = default; // virtual destructor
}
```

- une méthode virtuelle pure n'est habituellement **pas définie** (juste déclarée)
- une classe contenant une méthode virtuelle pure **ne peut pas s'instancier**
- une méthode virtuelle pure doit être **surchargée** dans **toutes les classes enfant**
- 纯虚函数通常**不定义**（只声明）
- 含纯虚函数的类**不能实例化**
- 纯虚函数必须在**所有子类**中**重写**

---

# Item 19 : Interfacer sans interface 没有 interface 的接口化

**Méthode virtuelle pure** 2/5
**纯虚函数** 2/5

- une méthode virtuelle pure n'est habituellement **pas définie** (juste déclarée)
  - une méthode pure n'a pas en soi de comportement
  - néanmoins les compilateurs le permettent,
    - il faut alors séparer définition et déclaration
  - peut servir pour un comportement par défaut commun à tous les enfants
- 纯虚函数通常**不定义**（只声明）
  - 纯函数本身没有行为
  - 编译器允许定义，但要分开声明与定义
  - 可用于提供所有子类共享的默认行为

```c++
class MyInterface {
public:
  virtual void function() = 0; // 声明虚拟纯函数
  virtual ~MyInterface() = default; //
};

void MyInterface::function() {std::cout << "Interface::function";}
int main() {
  MyInterface i{}; 
  // ERROR: cannot declare variable 'i' to be of abstract type 'MyInterface'
}
```

---

# Item 19 : Interfacer sans interface 没有 interface 的接口化

**Méthode virtuelle pure** 3/5
**纯虚函数** 3/5

- une classe contenant une méthode virtuelle pure **ne peut pas s'instancier**
  - elle ne fait aucune action ;
  - elle ne sert qu'à manipuler génériquement ses enfants.
- 含纯虚函数的类**不能实例化**
  - 自身不执行任何操作；
  - 仅用于泛化地操作子类。

```c++
class MyInterface {
public :
  virtual void function() = 0;
  virtual ~MyInterface() = default;
};
int main() {
  MyInterface i{}; 
  // ERROR: cannot declare variable 'i' to be of abstract type 'MyInterface'
}
```

---
# Item 19 : Interfacer sans interface 没有 interface 的接口化

**Méthode virtuelle pure** 4/5
**纯虚函数** 4/5

- une méthode virtuelle pure doit être **surchargée** dans **toutes les classes enfant**
  - un enfant ne surchargeant pas la(les) méthode(s) virtuelle(s) pure(s) de son parent ne peut s'instancier
- 纯虚函数必须在**所有子类**中**重写**
  - 未重写父类纯虚函数的子类无法实例化

```c++
class MyInterface {
public :
  virtual void function() = 0;
  virtual ~MyInterface() = default;
};
class MyImplementation : public MyInterface { // 继承 MyInterface
public:
  void function() override {std::cout << "MyImplementation::function()" << std::endl;}
};

int main() {
  MyImplementation mip{}; 
  // ERROR: cannot declare variable 'mip' to be of abstract type 'MyImplementation'
}
```

---

# Item 19 : Interfacer sans interface 没有 interface 的接口化

**Méthode virtuelle pure** 5/5
**纯虚函数** 5/5

- L'intérêt est donc d'avoir de l'héritage et une **manipulation polymorphique**
- 目的是实现继承与**多态式操作**

```c++
class ISolver {
public : 
  virtual void solve() = 0; // pure virtual method
  virtual ~ISolver() = default; // virtual destructor
};
class MySolver : public ISolver {
public:
 void solve() override {std::cout << "MySolver::solve()" << std::endl;}
};
class MyOtherSolver : public ISolver {
public:
 void solve() override {std::cout << "MyOtherSolver::solve()" << std::endl;}
};
```

---
# Item 19 : Interfacer sans interface 没有 interface 的接口化

Création d'une interface 1/2
创建接口 1/2

- On crée un **pointeur d'interface** pour manipuler l'**implémentation**
  - à l'ancienne (raw pointer)
- 创建**接口指针**来操作**实现**
  - 传统方式（裸指针）

```c++
int main() {
ISolver* solver = new MySolver{};
solver->solve();
delete solver; // MySolver is destroyed

solver = new MyOtherSolver{};
solver->solve();
delete solver; // MyOtherSolver is destroyed
}
```

---

# Item 19 : Interfacer sans interface 没有 interface 的接口化

Création d'une interface 2/2
创建接口 2/2

- On crée un **pointeur d'interface** pour manipuler l'**implémentation**
  - avec du C++ moderne (smart pointer)
- 创建**接口指针**来操作**实现**
  - 使用现代 C++（智能指针）

```c++
int main() {
using ISolverPtr = std::unique_ptr<ISolver>;
ISolverPtr solver = std::make_unique<MySolver>();
solver->solve();

solver = std::make_unique<MyOtherSolver>(); // MySolver is destroyed
solver->solve();
}// MyOtherSolver is destroyed
```

---

# Item 19 : Interfacer sans interface 没有 interface 的接口化

- L'interface est donc du polymorphisme sous contrainte :
  - il est obligatoire de surcharger dans les enfants
- Cela permet d'imposer un contrat, par exemple le contrat `ISolver`
- 接口是一种受约束的多态：
  - 子类必须重写接口方法
- 这样可以强制执行契约，例如 `ISolver` 契约

**Exo 19.1** : créez une classe `Interface` avec une méthode `compute` et créez deux classes dérivées `Implem1` et `Implem2` qui héritent d'`Interface`. `Interface` doit obliger ses classes dérivées à définir la méthode `compute`. Dans votre `main`, créez deux pointeurs d'`Interface` (avec les deux implémentations) et passez-les dans une fonction `apply(Interface*)` qui appelelera la méthode `compute`.
Recommencez l'exercice avec des smart pointeurs (`shared_ptr` ou `unique_ptr`).
**练习 19.1**：创建一个带 `compute` 方法的 `Interface` 类和两个继承它的类 `Implem1`、`Implem2`。`Interface` 应强制派生类定义 `compute`。在 `main` 中创建两个指向两种实现的 `Interface*`，传给函数 `apply(Interface*)` 调用 `compute`。再用智能指针（`shared_ptr` 或 `unique_ptr`）重复练习。

---
# Item 19 : Interfacer sans interface 没有 interface 的接口化

- **Exo 19.2** Créez une classe `Solvers` qui contient un tableau `std::vector` de solveurs sous la forme de pointeur (`std::unique_ptr`) d'interface `ISolver`, et deux classe filles `MySolver` et `MyOtherSolver`.
  - Cette classe `Solvers` contiendra :
    - une méthode addSolver qui prendra en argument le nom du solveur et comme argument template son type.
    - une méthode `solve` qui parcourera le tableau de solveur et appellera la méthode solve de chaque solveur au moyen d'un algorithme std::for_each et d'une $\lambda$-function.
  - Dans un programme principal :
    - ajoutez plusieurs solveurs dans cette classe
    - appelez la méthode `solve`
- **练习 19.2** 创建一个 `Solvers` 类，内部有一个 `std::vector` 保存接口 `ISolver` 的智能指针（`std::unique_ptr`），并有两个子类 `MySolver` 与 `MyOtherSolver`。
  - 该 `Solvers` 类包含：
    - `addSolver` 方法：参数为求解器名称，模板参数为其类型。
    - `solve` 方法：遍历求解器数组，用 `std::for_each` 和 λ 函数调用每个求解器的 `solve`。
  - 在主程序中：
    - 向此类添加多个求解器
    - 调用 `solve` 方法
