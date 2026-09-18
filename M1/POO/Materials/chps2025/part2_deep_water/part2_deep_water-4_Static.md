---
marp: true
theme: default
paginate: true


---

# **Programmation Orientée Objet pour le Calcul Scientifique : Part II Deep Water**  科学计算的面向对象编程：第二部分 深水

---

# Organisation du cours  课程组织

Sous forme d'**Item**, se raccrochant à trois catégories :  
以**条目**形式，分属三类：

- Outils et Langage (TooL)
- 工具与语言 (TooL)
- Gestion de la mémoire (Mem)
- 内存管理 (Mem)
- Orienté objet (OO)
- 面向对象 (OO)
- **Programmation statique (Static)**
- **静态编程 (Static)**

Vous n'êtes pas seul : https://en.cppreference.com/w/ est votre allié...  
你并不孤单： https://en.cppreference.com/w/ 是你的盟友...

---

# Item 20 Encore une référence...  第20条 再谈引用

Nous avons vu précédemment `&&`, référence d'une *rvalue* (ou objet temporaire)  
之前我们看到过 `&&` 作为*rvalue*（或临时对象）的引用

- En programmation statique `&&` peut prendre un autre sens, un peu plus général
- 在静态编程中 `&&` 可以有另一种更普遍的含义
- Lorsqu'il apparaît dans la signature d'une fonction/méthode template
- 当它出现在函数/方法模板的签名中时

```c++
template <typename T>
void func(T&& param) {} // universal reference
```

- Dans ce cas il signifie que l'objet passé peut-être soit :
- 在这种情况下，传入的对象可以是：
  - de type `T&`
  - 类型为 `T&`
  - de type `T&&`
  - 类型为 `T&&`

On les appelle **forwarding reference** (*référence de transfert*) car elles permettent le **perfect forwarding**  
它们被称为**转发引用**，因为它们允许**完美转发**

---

# Item 20 Encore une référence...  第20条 再谈引用

Les *forwarding reference* peuvent aussi permettre une déclaration : `auto &&`  
转发引用也可以用于声明：`auto &&`
Comme dans le cas template, Le type déduit pour l'objet peut être  
与模板情况类似，推导出的对象类型可以是

- une référence de *lvalue* `type&`
- 一个*lvalue*引用 `type&`
- une référence de *rvalue* `type&&`
- 一个*rvalue*引用 `type&&`

```c++
auto && value = 1; // value is deduced to be of type int&&
int i = 0;
auto && value2 = i; // value2 is deduced to be of type int&
```

Le type déduit est au plus près du type en originel. Pour rappel :  
推导出的类型尽可能贴近原始类型。回顾一下：

```c++
auto value = 1; // value is deduced to be of type int
auto value2 = i; // value2 is deduced to be of type int
```

---

# Item 20 Encore une référence...  第20条 再谈引用

Quel(s) intérêt(s) ?  
有什么好处？

- une signature unique pour traiter à la fois des références de *rvalue* ou de *lvalue*
- 一个签名同时处理*rvalue*或*lvalue*引用
- une déclaration unique pour stocker à la fois des références de *rvalue* ou de *lvalue*
- 一个声明同时保存*rvalue*或*lvalue*引用

---

# Item 20 Encore une référence...  第20条 再谈引用

Une signature unique pour traiter à la fois des références de *rvalue* ou de *lvalue*  
用一个签名同时处理*rvalue*或*lvalue*引用

```c++
template <typename T>
void func(T&& param) {
  std::cout << param << std::endl;
} // forwarding reference

int main(){
  int i = 0;
  func(i); // Call with lvalue. T is deduced to be int&.
  func(5); // Call with rvalue. T is deduced to be int&&
}
```

Remarque : dans l'exemple ci dessus, dans la signature de `func` :  
注意：在上面的示例中，`func` 的签名里：

- si `T&&` était remplacé par `T&` l'appel avec une ***rvalue*** ne serait pas possible.
- 如果把 `T&&` 换成 `T&`，就无法用***rvalue*** 调用了。
- Si `T&&` était remplacé par `int&&` l'appel avec une ***lvalue*** ne serait pas possible .
- 如果把 `T&&` 换成 `int&&`，就无法用***lvalue*** 调用了。

---

# Item 20 Encore une référence...  第20条 再谈引用

Une déclaration unique pour stocker à la fois des références de *rvalue* ou de *lvalue*  
用一个声明同时存储*rvalue*或*lvalue*引用

```c++
template <typename T>
void func(T&& param) {
  auto && copy = param; // not yet correct. missing forward
} // universal reference

int main(){
  int i = 0;
  func(i); // Call with lvalue. T is deduced to be int&.
  func(5); // Call with rvalue. T is deduced to be int&&
}
```

---

# Item 20 Encore une référence...  第20条 再谈引用

Comment gérer un move conditionnel ?  
如何处理条件移动？

- Si `T&&` = une référence de *rvalue* on souhaite un déplacement des données `move`
- 如果 `T&&` 是*rvalue*引用，希望移动数据（`move`）
- Si `T&&` = une référence de *lvalue* on souhaite une copie des données
- 如果 `T&&` 是*lvalue*引用，希望复制数据
- Pour cela on utilise `std::forward<T>` (header `<utility>`)
- 为此使用 `std::forward<T>`（`<utility>` 头文件）

```c++
template <typename T>
void func(T&& param) {
  auto && copy = std::forward<T>(param); } // universal reference

int main(){
  int i = 0;
  func(i); // Call with lvalue. T is deduced to be int&.
  func(5); // Call with rvalue. T is deduced to be int&&
}
```

---

# Item 20 Encore une référence...  第20条 再谈引用

Comment gérer un move conditionnel ? Un exemple 1/2  
如何处理条件移动？示例 1/2

```c++
void f(int&) {
    std::cout << "f(int&)" << std::endl;
}
void f(int&&) {
    std::cout << "f(int&& )" << std::endl;
}
int main() { // code not yet working, type is to be explicited
  auto && rvalue_ref = 5;
  f(std::forward<type>(rvalue_ref)); // type to be explicited in next slide
  int i = 42;
  auto&& lvalue_ref = i;
  f(std::forward<type>(lvalue_ref));// type to be explicited in next slide
}
```

---

# Item 20 Encore une référence...  第20条 再谈引用

Comment gérer un move conditionnel ? Un exemple 2/2  
如何处理条件移动？示例 2/2

```c++
void f(int&) {
    std::cout << "f(int&)" << std::endl;
}
void f(int&&) {
    std::cout << "f(int&& )" << std::endl;
}
int main() { // type is now explicited
  auto && rvalue_ref = 5;
  f(std::forward<decltype(rvalue_ref)>(rvalue_ref)); 
  int i = 42;
  auto&& lvalue_ref = i;
  f(std::forward<decltype(lvalue_ref)>(lvalue_ref));
}
```

# Item 20 Encore une référence...  第20条 再谈引用

Quel intérêt ? Un exemple 1/2 ; **sans : deux écritures** de `copy`  
有何用处？示例 1/2；**没有转发时需要两种写法**的 `copy`

```c++
struct MyVector{
  MyVector& operator= (MyVector &) {std::cout << "copy data " << std::endl; return *this;}
  MyVector& operator= (MyVector&&) {std::cout << "move data" << std::endl; return *this;}
  void copy(MyVector& vec) {std::cout << "Copy data " << std::endl; *this = vec;}
  void copy(MyVector&&) {std::cout << "Move data " << std::endl; *this = std::move(vec);}
};

int main(){
  MyVector a{},b{};
  a.copy(b);
  a.copy(MyVector{});
}
```

---

# Item 20 Encore une référence...  第20条 再谈引用

Quel intérêt ? Un exemple 2/2 ; **avec : une unique écriture** de `copy`  
有何用处？示例 2/2；**使用转发时只需一种写法**的 `copy`

```c++
struct MyVector{
private:
  MyVector& operator= (MyVector const&) {std::cout << "copy data " << std::endl; return *this;}
  MyVector& operator= (MyVector&&) {std::cout << "move data" << std::endl; return *this;}
public:
  template <typename T>
 void copy(T&& vec) {std::cout << "copy or move" << std::endl; *this = std::forward<T>(vec);}
};

int main(){
  MyVector a{},b{};
  a.copy(b);
  a.copy(MyVector{});
}
```

---

# Item 20 Encore une référence...  第20条 再谈引用

Quel intérêt ? Un deuxième exemple 1/2 ; **sans : deux écritures** de `addData`  
有何用处？第二个示例 1/2；**没有转发时需要两种写法**的 `addData`

```c++
struct HeavyData{
  HeavyData& operator=(HeavyData const&) {std::cout << "copy data" << std::endl;return *this;}
  HeavyData& operator=(HeavyData &&) {std::cout << "move data" << std::endl;return *this;}
};
struct Container {
  HeavyData m_data;
  void addData(HeavyData const& heavy_data) {m_data = heavy_data;}
  void addData(HeavyData && heavy_data) {m_data = std::move(heavy_data);}
};

int main() {
  HeavyData a{};
  Container c{};
  c.addData(a); // add lvalue reference by copy
  c.addData(HeavyData{}); // add rvalue reference by move
}
```

---

# Item 20 Encore une référence...  第20条 再谈引用

Quel intérêt ? Un deuxième exemple 2/2 ; **avec : une unique écriture** de `addData`  
有何用处？第二个示例 2/2；**使用转发时只需一种写法**的 `addData`

```c++
struct HeavyData{
  HeavyData& operator=(HeavyData const&) {std::cout << "copy data" << std::endl;return *this;}
  HeavyData& operator=(HeavyData &&) {std::cout << "move data" << std::endl;return *this;}
};
struct Container {
  HeavyData m_data;
  template <typename T>
  void addData(T&& heavy_data) { m_data = std::forward<T>(heavy_data);}
};

int main() {
  HeavyData a{};
  Container c{};
  c.addData(a);// add lvalue reference by copy
  c.addData(HeavyData{}); // add rvalue reference by move
}
```

---

# Item 20 Encore une référence...  第20条 再谈引用

Quel intérêt ?  *pour aller plus loin* : vérifier les types avec `if constepxr`  
有何用处？*深入一点*：用 `if constexpr` 检查类型

```c++
struct HeavyData{
  HeavyData& operator=(HeavyData const&) {std::cout << "copy data" << std::endl;return *this;}
  HeavyData& operator=(HeavyData &&) {std::cout << "move data" << std::endl;return *this;}
};
template <typename Data>
struct Container {
  Data m_data;
  template <typename T>
  void addData(T&& data) { 
    if constexpr (std::is_same_v<Data, std::remove_reference_t<T>>) m_data = std::forward<T>(data);
    else std::cout << "Bad type added";
    }
};
int main() {
  HeavyData a{};
  Container<HeavyData> c{};
  c.addData(a);
  c.addData(HeavyData{});
  c.addData(42); // "Bad type added"
}
```

---

# Item 20 Encore une référence...  第20条 再谈引用

**Exo 20.1**  : Créez une classe `B` contenant un objet d'une classe `A` comme donnée membre. La classe `B` sera construite à partir d'une *forwarding reference* vers A pour pouvoir faire un déplacement mémoire lorsque c'est possible ; une copie sinon. Faites fonctionner le code suivant :  
**练习 20.1**：创建一个类 `B`，其成员数据是类 `A` 的对象。类 `B` 使用指向 A 的转发引用来构造，能移动时移动，否则复制。让下面的代码能运行：

```c++
int main() {
  A a{};
  B b(A{}); // A(A&&)
  B b2(a); // A(A const&)
}
```

de sorte qu'il affiche :  
使其输出：

```shell
A(A&&)
A(A const&)
```

---

# Item 21 Template : mettez le pack  模板：打包

En C++11 a été ajouté la possibilité d'avoir un nombre variable de paramètres template  
C++11 增加了可变数量模板参数的能力

```c++
template<typename... T>
void func(T&&... t){}

int main() {
  func(1);
  func(1,'c',3.f);
}
```

---

# Item 21 Template : mettez le pack  模板：打包

En C++11 a été ajouté la possibilité d'avoir un nombre variable de paramètre template  
C++11 增加了可变数量的模板参数

- il est tout d'abord possible de connaître le **nombre d'arguments** passés
- 首先可以获取传入的**参数数量**

```c++
template<typename... T>
void func(T&&...){
  std::cout << " nb parameter : " << sizeof...(T) << std::endl;
}

int main() {
  func(1);
  func(1,'c',3.f);
}
```

---

# Item 21 Template : mettez le pack  模板：打包
Un premier cas d'usage pour les fonctions : **l'appel pour tous les paramètres**  
在函数中的第一个用例：**对所有参数进行调用**

```c++
void print() {
  std::cout << std::endl;
}

template<typename U,typename... T>
void print(U&& u, T&&... t){
  std::cout << u << " ";
  print(t...);
}

int main() {
  print(1);
  print(1,'c');
  print(1,"Hello World",3.f);
}
```

---

# Item 21 Template : mettez le pack  模板：打包

Un deuxième cas d'usage dans les fonctions : **avec un opérateur** (*fold expresssions*)  
函数中的第二个用例：**配合运算符**（折叠表达式）

- dans une opération "unaire" : pour un parameter pack `args`
- 对于参数包 `args` 的“一元”操作：
  - `(args op ...)` : unary right folding 一元右折叠
    `(arg1 op (arg2 op (...( arg_n-1 op arg_n))))`

```c++
 template<typename... T>
 int func(T&&... args) {
   return ( args - ...); 
 }

 int main(){
   func(3,2,1); // (3 - (2 - 1 )) = 2
}
```

---

# Item 21 Template : mettez le pack  模板：打包

Un deuxième cas d'usage dans les fonctions : **avec un opérateur** (*fold expresssions*)  
函数中的第二个用例：**配合运算符**（折叠表达式）

- dans une opération "unaire" : pour un parameter pack `args`
- 对于参数包 `args` 的“一元”操作：
  - `(... op args)` : unary left folding 一元左折叠
    `(((arg1 op arg2)  op ...) op arg_n)`

```c++
 template<typename... T>
 int func(T&&... args) {
   return (... - args); 
 }
 
 int main(){
   func(3,2,1); // (3 - 2) - 1 = 0
 }
 ```

---

# Item 21 Template : mettez le pack  模板：打包

Un deuxième cas d'usage dans les fonctions : **avec un opérateur** (*fold expresssions*)  
函数中的第二个用例：**配合运算符**（折叠表达式）

- dans une opération "unaire" : pour un parameter pack `args`
- 对于参数包 `args` 的“一元”操作：
  - `(args op ...)` : unary right folding 一元右折叠
  - `(arg1 op (arg2 op (...( arg_n-1 op arg_n))))`
  - `(... op args)` : unary left folding 一元左折叠
  `(((arg1 op arg2)  op ...) op arg_n)`
  `(((arg1 op arg2)  op ...) op arg_n)`

**Exo 21.1** : Réalisez une fonction qui additionne les n arguments passés en entrée :  
**练习 21.1**：实现一个函数，对传入的 n 个参数求和：

```c++
int main(){
  auto result = 0;
  result = sum(1,2,3);
  result = sum(1,2,4,5,6);
}
```

---

# Item 21 Template : mettez le pack  模板：打包

Un deuxième cas d'usage dans les fonctions : **avec un opérateur** (*fold expresssions*)  
函数中的第二个用例：**配合运算符**（折叠表达式）

- dans une opération "binaire" : pour un parameter pack `args`
- 对于参数包 `args` 的“二元”操作：
  - `(args op ... op init)` : binary right folding 二元右折叠
  - `(arg1 op (... op (arg_n-1 op(arg_n op init))))`

```c++
template <typename U, typename... T>
void init(U value, T&... args) {
    (args = ... = value); // arg1 = arg2 = ... = value
}
 
 int main(){
   int a, b,c;
   init(42,a,b,c);
   std::cout << " a " << a << " b " << b << " c "  << c << std::endl;
 }
 ```

---

# Item 21 Template : mettez le pack  模板：打包

Un deuxième cas d'usage dans les fonctions : **avec un opérateur** (*fold expresssions*)  
函数中的第二个用例：**配合运算符**（折叠表达式）

- dans une opération "binaire" : pour un parameter pack `args`
- 对于参数包 `args` 的“二元”操作：
  - `(init op ... op args)` : binary left folding 二元左折叠
    `((((init op arg1) op arg2)  op ...) op arg_n)`

```c++
template <typename U, typename... T>
U cumul(U value, T... args) {
    return (value += ... += args);// ((value += val1) += val2) += val3)
}

 int main(){
   std::cout << " cumul " << cumul(1,a,b,c);
 }

 ```

---

# Item 21 Template : mettez le pack  模板：打包

Un deuxième cas d'usage dans les fonctions : **avec un opérateur** (*fold expresssions*)  
函数中的第二个用例：**配合运算符**（折叠表达式）

- dans une opération "binaire" : pour un parameter pack `args`
- 对于参数包 `args` 的“二元”操作：
  - `(init op ... op args)` : binary left folding 二元左折叠
    `((((init op arg1) op arg2)  op ...) op arg_n)`

```c++
// With a type check through a requires clause (using folding !)
template <typename U, typename... T>
U cumul(U value, T... args) requires (std::is_same_v<U,T> && ...) {
    return (value += ... += args);// ((value += val1) += val2) += val3)
}

 int main(){
   std::cout << " cumul " << cumul(1,a,b,c);
 }

 ```

---

# Item 21 Template : mettez le pack  模板：打包

Un deuxième cas d'usage dans les fonctions : **avec un opérateur** (*fold expresssions*)  
函数中的第二个用例：**配合运算符**（折叠表达式）

- dans une opération "binaire" : pour un parameter pack `args` et un opérateur `op`
- 对于参数包 `args` 与运算符 `op` 的“二元”操作：
  - `(args op ... op init)` : binary right folding 二元右折叠
    `(arg1 op (... op (arg_n-1 op (arg_n op init))))`
  - `(init op ... op args)` : binary left folding 二元左折叠
    `((((init op arg1) op arg2)  op ...) op arg_n)`

**Exo 21.2** : refaites une fonction d'affichage de ses n arguments d'entrée sans utiliser de récursion. Vous utiliserez un "binary left folding" avec l'opérateur `<<`  
**练习 21.2**：重写一个输出 n 个输入参数的函数，不使用递归，使用运算符 `<<` 的“二元左折叠”。

---

# Item 21 Template : mettez le pack  模板：打包

Un deuxième cas d'usage dans les fonctions : **avec un opérateur** (*fold expresssions*)  
函数中的第二个用例：**配合运算符**（折叠表达式）
Pour aller plus loin : dans une expression de type `(args operator ...)`  
进一步：在 `(args operator ...)` 形式的表达式中

- `args` peut-être une expression contenant un parameter pack non développé
- `args` 可以是包含未展开参数包的表达式
  - par exemple un appel de fonction
  - 例如一个函数调用
- `(func(pack),...)` va donc donner  par exemple pour trois arguments :  
- 因此 `(func(pack),...)` 对三个参数会得到：
  - `(func(arg1),(func(arg2),func(arg3)))`
  - `(func(arg1),(func(arg2),func(arg3)))`
  - permets d'appeler une fonction pour tous les arguments sans récursion
  - 允许在不使用递归的情况下对所有参数调用一个函数

---

# Item 21 Template : mettez le pack  模板：打包

Un deuxième cas d'usage dans les fonctions : **avec un opérateur** (*fold expresssions*)  
函数中的第二个用例：**配合运算符**（折叠表达式）
Pour aller plus loin : **`(func(pack),...)`**  
进一步：**`(func(pack),...)`**

- permets d'appeler une fonction pour tous les arguments sans récursion
- 允许在不使用递归的情况下对所有参数调用一个函数

```c++
template <typename T, typename...Args>
addToVector(std::vector<T>& vec, Args... args) {
  (vec.push_back(args),...); // check on type compatibility is omitted
}

int main(){
 std::vector<int> my_vector;
 addToVector(my_vector,1,2,3);
}
```

---

# Item 21 Template : mettez le pack  模板：打包

Un deuxième cas d'usage dans les fonctions : **avec un opérateur** (*fold expresssions*)  
函数中的第二个用例：**配合运算符**（折叠表达式）
Pour aller plus loin : **`(func(pack),...)`**  
进一步：**`(func(pack),...)`**

- permets d'appeler une fonction pour tous les arguments sans récursion
- 允许在不使用递归的情况下对所有参数调用一个函数

```c++
// version 'universal reference'
template <typename T, typename...Args> 
void addToVector(std::vector<T>& vec, Args&&... args) {
  (vec.push_back(std::forward<Args>(args)),...);
}

int main(){
 std::vector<int> my_vector;
 int a = 2;
 addToVector(my_vector,1,a,3); // (std::vector<int>&,int&&,int&,int&&)
}

```

---

# Item 21 Template : mettez le pack  模板：打包

Un deuxième cas d'usage dans les fonctions : **avec un opérateur** (*fold expresssions*)  
函数中的第二个用例：**配合运算符**（折叠表达式）
Pour aller plus loin : **`(func(pack),...)`**  
进一步：**`(func(pack),...)`**

- Remarque : `(func(pack),...)` n'est pas nécessairement un appel de fonction
- 注意：`(func(pack),...)` 不一定是函数调用
  - peut-être une expression contenant un pack (écrite entre parenthèses)
  - 它可以是包含参数包的表达式（放在括号中）
  - permets alors d'exécuter une expression pour tous les arguments
  - 因此可以对所有参数执行一段表达式

**Exo 21.3** Modifiez votre fonction d'affichage afin qu'elle insère des espaces entre chaque valeur. Vous n'utiliserez pas de récursion.  
**练习 21.3** 修改打印函数，使其在每个值之间插入空格，不使用递归。

```c++
int main() {
  print(1);
  print(1,'c'); // output: 1 c 
  print(1,"Hello World",3.f);//output: 1 Hello World 3 
}
```

---

# Item 21 Template : mettez le pack  模板：打包

Un troisième cas d'usage dans les fonctions : peut-on faire un **pack d'entier** ?  
函数中的第三个用例：能否创建一个**整数包**？

- oui :  `template <int..ints>`
- 可以：`template <int..ints>`

```c++
template <int...Ns>
void func() {
  std::cout << "int sequence size " << sizeof...(Ns) << std::endl;
  ((std::cout << Ns << ' '),...)  << std::endl;
}

int main(){
  func<-1,0,2>();
  func<1,2,3>();
}
```

---

# Item 21 Template : mettez le pack  模板：打包

Un troisième cas d'usage dans les fonctions : peut-on faire un **pack d'entier** ?  
函数中的第三个用例：能否创建一个**整数包**？

- oui :  `template <int...ints>`
- 可以：`template <int...ints>`
- on peut générer la séquence avec `std::integer_sequence<T,ints...>` 
- 可以用 `std::integer_sequence<T,ints...>` 生成序列
  - où `T` est le type d'entier
  - 其中 `T` 是整数类型

```c++
template <typename T, T...Ns>
void func(std::integer_sequence<T,Ns...> int_seq) {
  std::cout << "sequence size " << int_seq.size() << std::endl;
  ((std::cout << Ns << ' '),...)  << std::endl;
}

int main(){
  func(std::integer_sequence<unsigned,0,1,2>{});
  func(std::make_integer_sequence<unsigned,3>{}); // <0,1,2>
}
```

---

# Item 21 Template : mettez le pack

Un troisième cas d'usage dans les fonctions : peut-on faire un **pack d'entier** ?

- oui :  `template <int...ints>`
- on peut générer la séquence avec `std::integer_sequence<T,ints...>` 
- 可以用 `std::integer_sequence<T,ints...>` 生成序列
  - où `T` est le type d'entier
  - 其中 `T` 是整数类型

Si le type d'entier = `size_t` on utilise `std::index_sequence<size_t...ints>`  
如果整数类型是 `size_t`，使用 `std::index_sequence<size_t...ints>`

```c++
  template<typename Tuple, size_t...indexes>
  void print_tuple(Tuple& tuple, std::index_sequence<indexes...>){
      ((std::cout << std::get<indexes>(tuple) << ' '), ...);
  }
  int main() {
    std::tuple<int, char,std::string> tuple {42,'c',"hello"};
    print_tuple(tuple,std::make_index_sequence<3>{});
  }
```

---

# Item 21 Template : mettez le pack  模板：打包

Un troisième cas d'usage dans les fonctions : peut-on faire un **pack d'entier** ?  
函数中的第三个用例：能否创建一个**整数包**？

- oui :  `template <int...ints>`
- 可以：`template <int...ints>`
- mais :  on ne peut pas les utiliser directement comme argument
- 但不能直接把它们作为参数使用
  - il faut passer par une `std::integer_sequence<T,N...>`,   où `T` un type d'entier
  - 需要通过 `std::integer_sequence<T,N...>`，其中 `T` 是整数类型

si le type d'entier = `size_t` on utilise `std::index_sequence<size_t...ints>`  
如果整数类型是 `size_t`，使用 `std::index_sequence<size_t...ints>`

**Exo 21.4** (Avancé) Réalisez une méthode d'impression d'un tuple ne prenant en argument que le tuple (pas l'`index_sequence`) :  
**练习 21.4**（进阶）实现一个打印 tuple 的方法，只接受 tuple 本身（不传 `index_sequence`）：

```c++
int main() {
  std::tuple<int, char,std::string> tuple {42,'c',"hello"};
  print_tuple(tuple);
}
```

---

# Item 21 Template : mettez le pack  模板：打包

Cas d'usage pour les **classes** : une classe peut également prendre un pack  
在**类**中的用例：类同样可以接收一个参数包

- ex d'un tuple pouvant contenir un nombre variable d'éléments de types différents
- 例子：一个 tuple 可以包含数量可变、类型各异的元素

```c++
template <typename...Args>
class Tuple {
public:
  Tuple(Args...) {}
};

int main() {
  Tuple my_tuple{2,3.5,'c',"hello"};
}
```

---

# Item 21 Template : mettez le pack  模板：打包

Cas d'usage pour les **classes** : une classe peut hériter d'un pack  
在**类**中的用例：类可以继承一个参数包

- ex d'une classe héritant des classes données à la construction
- 例子：一个类继承构造时传入的若干类

```c++
template <typename...Args>
class Holder : public Args... {
public:
  Holder(const Args&...args): Args(args)... {}
};

struct Solver{};
struct Scheme {};

int main() {
  Holder<Solver,Scheme> holder(Solver{},Scheme{});
}
```
