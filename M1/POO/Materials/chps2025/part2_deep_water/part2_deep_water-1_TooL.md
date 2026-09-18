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
以“条目”形式呈现，归属于三个类别：

- **Outils et Langage (TooL)**
**工具与语言（TooL）**
- Gestion de la mémoire (Mem)
内存管理（Mem）
- Orienté objet (OO)
面向对象（OO）
- Programmation statique (Static)
静态编程（Static）

Vous n'êtes pas seul : https://en.cppreference.com/w/ est votre allié...
你并不孤单：https://en.cppreference.com/w/ 是你的盟友……

# Item 13 : la bibliothèque standard STL (introduction) 第13项：标准库 STL（介绍）

Qu'est-que c'est ? Tout ce que vous trouvez sous `std::`...
这是什么？就是你在 `std::` 命名空间下找到的所有内容……
STL : Standard Template Library
STL：标准模板库

- une bibliothèque bas-niveau mise à disposition par votre compilateur
  由编译器提供的底层库
  - il existe autant de versions que de compilateurs
    各个编译器都对应有自己的版本
- un ensemble :
  一个集合：
  - de conteneurs génériques (indépendant du type contenu)
    泛型容器（与所含类型无关）
  - d'algorithmes génériques (indépendant du conteneur)
    泛型算法（与容器类型无关）
  - d'objets de base biens pratiques (io, mémoire, exceptions, parallélisme...)
    一系列实用的基础对象（I/O、内存、异常、并行等）

Le premier réflexe à avoir quand on a besoin de quelque chose : est-ce dans la STL ?
当你需要某个功能时的第一反应：它是否已经在 STL 中？
Nous focalisons dans cet item sur les **conteneurs** et les **algorithmes**
本节我们聚焦于**容器**和**算法**

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les **premiers conteneurs** : paire et n-uplet 1/2
首批容器：二元组与多元组 1/2

- Le conteneur le plus simple est la **paire d'élément** : `std::pair<T,U>`
  最简单的容器是**元素对**：`std::pair<T,U>`
  - les deux objets sont de **type quelconque**
    两个对象都可以是**任意类型**
  - on peut la construire avec la fonction `std::make_pair(a,b)`
    可以使用函数 `std::make_pair(a,b)` 来构造
  - il faut inclure le header `<utility>`
    需要包含头文件 `<utility>`
  - les éléments s'accèdent au moyen des données membres `first` et `second`
    通过成员 `first` 和 `second` 访问元素

```c++
#include <utility>
int main() {
  // C++98 / C++11 / C++14 / C++17
  std::pair<int, float> p(1, 3.14f); // 必须写 <int, float>
  // C++98 / C++11 / C++14
  std::pair<char,int> pair = std::make_pair('a',1); // auto pair更简写
  // C++17
  std::pair p(1, 3.14f); // 编译器自动推导为 std::pair<int, float>
  std::cout << pair.first << " " ;
  std::cout << pair.second;
}
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les **premiers conteneurs** : paire et n-uplet 2/2
首批容器：二元组与多元组 2/2

- Le **n-uplet** stocke un nombre quelconque d'élément : `std::tuple<T...>`
  **多元组**可存储任意数量的元素：`std::tuple<T...>`
  - les n objets sont de **type quelconque**
    这 n 个对象都可以是**任意类型**
  - on peut le construire avec la fonction `std::make_tuple(a,b,c,d)`
    可以使用函数 `std::make_tuple(a,b,c,d)` 来构造
  - il faut inclure le header `<tuple>`
    需要包含头文件 `<tuple>`
  - les éléments s'accèdent au moyen de la fonction `std::get<i>(tuple)`
    使用函数 `std::get<i>(tuple)` 来访问各个元素

```c++
#include <tuple>
int main() {
  // C++98 / C++11 / C++14
  std::tuple<int, float> t1(1, 3.14f);
  // C++98 / C++11 / C++14 / C++17
  std::tuple<char,int,float> tuple = std::make_tuple('a',1,10.f);
  // C++17
  std::tuple t2('a',1,10.f,20.f);
  std::cout << std::get<0>(tuple) << " " ;
  std::cout << std::get<1>(tuple) << " " ;
  std::cout << std::get<2>(tuple) << " " ;
}
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

La **chaîne de caractère**, un premier tableau
**字符串**，第一个数组

- la chaîne de caractère : `std::string`
  字符串容器：`std::string`

```c++
#include <string>

int main(){
  std::string str{"Hello World"};
  std:: cout << str << std::endl;
  str = {"new value"};
  std::cout << str << std::endl;
  auto size = str.size(); // = 9
  // 等于 9
  std::cout << str[size-1]; // e
  // 字符 e
}
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les tableaux de la STL 1/3
STL 中的数组 1/3

- **tableau** de taille statique `std::array<T,size>`
**静态大小**数组 `std::array<T,size>`

```c++
#include <array> 

int main() {
  std::array<int,3> int_array_of_size_3 {0,1,2};
  int_array_of_size_3[2] = 0;

  // Deduction guide
  // 推导指南
  std::array deducted_size_type_array {0,1,2,3}; // -> std::array<int,4>
  // 等价于 std::array<int,4>

  std::array<char, 2> char_array = { 'a', 'b' };
}
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）
Les tableaux de la STL 2/3
STL 中的数组 2/3

- **tableau** de taille dynamique `std::vector<T>`
  **动态大小**数组 `std::vector<T>`

```c++
#include <vector>

int main() {
  std::vector<int> vec {0,1}; // 创建并分配
  vec.push_back(2); // 添加元素

  vec.clear(); // 清空

  vec = {2,4,5}; // 重新分配
  vec[0] += 2; // 修改元素
}
```

De nombreuses fonctionnalités : https://en.cppreference.com/w/cpp/container/vector
更多功能请见：https://en.cppreference.com/w/cpp/container/vector

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les tableaux de la STL 3/3
STL 中的数组 3/3

- **tableau** de taille dynamique `std::vector<T>` : création et allocation
  **动态大小**数组 `std::vector<T>`：创建与分配

```c++
int main() { // do not forget to #include <vector>
  // 记得包含头文件 <vector>
  std::vector<int> vec{0,1}; // vector with 2 elements
  // 含有 2 个元素的向量
  std::cout << vec[0] << " " << vec[1] << std::endl;
  std::vector<int> vec2; // empty vector
  // 空向量
  vec.resize(2); //allocate 2 elements
  // 分配 2 个元素
  std::cout << vec[0] << " " << vec[1] << std::endl;
  vec.push_back(2); // add a new element : re-allocation
  // 添加新元素：触发重新分配
  std::cout << vec[2] << std::endl;
  std::vector<int> vec3; // empty vector
  // 空向量
  vec3.reserve(3); // allocate a maximum size. size = 0, capacity = 3
  // 预分配最大容量，size = 0，capacity = 3
  vec3.push_back(2); // add a new element : no re-allocation
  // 添加新元素：不触发重新分配
  vec.clear(); vec2.clear(); vec3.clear();
}
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les autres conteneurs séquences de la STL
STL 的其他序列容器
La STL contient d'autres conteneurs séquences (éléments non triés)
STL 还包含其他序列容器（元素未排序）

- un tableau à double entrée : `std::deque<T>` (`push_back()` et `push_front()`)
  双端数组：`std::deque<T>`（支持 `push_back()` 与 `push_front()`）
- des listes chaînées
  各类链表
  - coût d'insertion d'un éléments très faible (contrairement à `vector`)
    插入一个元素的成本极低（与 `vector` 相比）
  - **pas d'accès indexé à un élément** (`operator[](int)` inexistant)
    **不支持按索引访问元素**（不存在 `operator[](int)`）
    - la liste `std::list<T>`:`push_back()/push_front()`,`pop_back()/pop_front()`
      双向链表 `std::list<T>`：`push_back()/push_front()`，`pop_back()/pop_front()`
    - la file `std::queue<T>` : manipulation FIFO (First In First Out,`push()/pop()`)
      队列 `std::queue<T>`：遵循 FIFO（先进先出）操作，`push()/pop()`
    - la pile`std::stack<T>` : manipulation LIFO (Last In First Out,`push()/pop()`)
      栈 `std::stack<T>`：遵循 LIFO（后进先出）操作，`push()/pop()`

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les conteneurs séquences de la STL
STL 的序列容器

- `std::array<T,int>`
`std::array<T,int>`
- `std::vector<T>`
`std::vector<T>`
- `std::deque<T>`, `std::list<T>`, `std::queue<T>`, `std:stack<T>`
`std::deque<T>`、`std::list<T>`、`std::queue<T>`、`std:stack<T>`

**Exo 13.1** : manipulation de conteneurs séquences
**练习 13.1**：序列容器操作

- créez un conteneur `array` et `vector`,
创建一个 `array` 容器和一个 `vector` 容器，
- les remplir (à la construction ou via `resize` et `push_back` pour le vecteur)
为它们填充数据（在构造时，或对 `vector` 使用 `resize` 和 `push_back`）。
- affichez la taille (éventuellement la capacité).
输出它们的大小（以及容量，如果需要）。
- affichez leurs valeurs via une unique fonction template.
通过一个模板函数打印它们的值。

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les vues sur les conteneurs séquences (contigus)
序列容器（连续存储）的视图

- **`std::string_view`** C++17, vue constante sur un std::string
**`std::string_view`** C++17，对 `std::string` 的常量视图

```c++
#include <string_view>

int main(){
  std::string str{"Hello World"};
  std::string_view str_view = str; // No copy
  // 无拷贝
  // Can be handled like a std::string
  // 可以像 std::string 一样使用
  std::cout << str_view << std::endl;
  auto size = str_view.size(); // = 9
  // 等于 9
  std::cout << str_view[size-1]; // e
  // 字符 e
  // str_view[0] = '0'; KO, not mutable
  // str_view[0] = '0'；不可修改
}
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les vues sur les conteneurs séquences (contigus)
序列容器（连续存储）的视图

- **`std::span<T>`** C++20, vue sur un tableau
**`std::span<T>`** C++20，数组视图

```c++
#include <span>

int main(){
  int static_array[3] = {1,2,3};
  std::span<int> span1(static_array);
  std::array<int, 3> std_array = {4,5,6};
  std::span<int> span2(std_array);         
  std::vector<int> std_vector = {7,8,9};
  std::span<int> span3(std_vector);
  std::span<int,3> span4(static_array);
  std::span<int,3> span5(std_array);
}
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les vues sur les conteneurs séquences (contigus)
序列容器（连续存储）的视图

- **`std::span<T>`** C++20, vue sur un tableau
**`std::span<T>`** C++20，数组视图
- ne possède pas les données
不拥有底层数据
- permet de modifier les données
允许修改数据
- ne permet pas de redimensionner le conteneur
不允许重新调整容器大小
- est invalidée si le conteneur est redimensionné ou supprimé
当容器被重新调整大小或删除时视图失效
- peut avoir sa taille fixée statiquement
可以静态指定视图大小

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les vues sur les conteneurs séquences (contigus)
序列容器（连续存储）的视图

- permettent une sémantique de passage par copie dans des fonctions
允许在函数中实现按值语义的传参
- attention à la validité du conteneur au sein de la fonction
注意在函数内部容器的有效性

```c++
#include <vector>
#include <span>

void function(std::span<int> view) {...}

int main(){
  std::vector vec{1,2,3};
  function(vec);
}
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les **conteneurs associatifs** de la STL 1/7
STL 的**关联容器** 1/7

- Les conteneurs associatifs trient leurs éléments à l'insertion
关联容器在插入时会对元素进行排序
  - accès énuméré ou par une recherche ; pas d'accès direct par un index
    访问方式为遍历或查找；不支持通过索引直接访问
- Les deux principaux conteneurs associatifs sont
两类主要的关联容器：
  - l'ensemble ou set `std::set<T>`
    集合 `std::set<T>`
  - la dictionnaire clé-valeur ou map `std::map<Key,T>`
    键值字典 `std::map<Key,T>`

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）
Les **conteneurs associatifs** de la STL 2/7
STL 的**关联容器** 2/7

- l'ensemble ou set `std::set<T>`
集合 `std::set<T>`
  - par défaut les éléments sont triés par un `operator<`
    默认按照 `operator<` 进行排序
  - il est possible de donner une comparaison défini par l'utilisateur
    可以提供用户自定义的比较器
    - `std::set<T,Compare>`
      使用 `std::set<T,Compare>`
  - le set n'insère qu'une fois une même valeur, pas de doublon
    集合中同一个值只会插入一次，不允许重复
    - voir `std::multiset` pour un set contenant des doublons
      若需要允许重复值，请使用 `std::multiset`
  - la recherche d'une valeur retourne un itérateur (syntaxe de pointeur)
    查找操作返回一个迭代器（指针语法）
  - les éléments du set ne sont pas modifiables, stockés en `const T`
    集合中的元素不可修改，以 `const T` 存储

--- 
# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les **conteneurs associatifs** de la STL 3/7
STL 的**关联容器** 3/7

- l'**ensemble** ou set `std::set<T>`
**集合** `std::set<T>`

```c++
#include <set>

int main(){
  std::set<int> my_set {4,1,7,2}; // inserted element will be sorted
  // 插入的元素会被排序
  
  my_set.insert(0); // inserted before 1
  // 插入元素 0，位于 1 之前
  auto value_ite = my_set.find(1); // returns an iterator
  // 返回一个迭代器
  
  if (value_ite != my_set.end()) {
    std::cout << *value_ite;
  }
  my_set.clear();
}
```

---
# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les **conteneurs associatifs** de la STL 4/7
STL 的**关联容器** 4/7

- l'**ensemble** ou set `std::set<T>`
**集合** `std::set<T>`

```c++
#include <set>

int main(){
  std::set<double> my_set { 1.0,2.0 };
  using my_iterator = std::set<double>::iterator;
  std::pair<my_iterator,bool> insert_ret = my_set.insert(2.0);
  if (! insert_ret.second) std::cout << "Insertion didn't occur" << std::endl;

  // Light syntax with structured bindings
  // 使用结构化绑定的简洁语法
  auto [iterator,is_inserted] = my_set.insert(4.0);
  if (! is_inserted) std::cout << "Insertion didn't occur";
  else std::cout << (*iterator);
}    
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les **conteneurs associatifs** de la STL 5/7
STL 的**关联容器** 5/7

- le **dictionnaire** clé-valeur ou map `std::map<Key,Value>`
**键值字典** `std::map<Key,Value>`
  - stocke des couples clé/valeur sous la forme de
    以如下形式存储键/值对：
    - `std::pair<const Key,Value>`
      `std::pair<const Key,Value>`
  - l'insertion n'a lieu que si la clé n'existe pas : pas de clé en doublon
    只有当键不存在时才插入：不允许重复键
    - voir `std::multimap` pour des stockages avec clés en doublons
      如需允许重复键，请使用 `std::multimap`
  - accès aux éléments via un itérateur pointant vers : `std::pair<const Key,Value>`
    通过指向 `std::pair<const Key,Value>` 的迭代器访问元素
  - les clés ne sont pas modifiables
    键不可修改

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）
Les **conteneurs associatifs** de la STL 6/7
STL 的**关联容器** 6/7
- le **dictionnaire** clé-valeur ou map `std::map<Key,Value>`
  **键值字典** `std::map<Key,Value>`
```c++
#include <map>

int main(){
  std::map<std::string,double> my_map { {"val1",1.0},{"val2",2.0} };

  my_map.insert({"val3",3.0});
  my_map.insert(std::make_pair("val4",4.0));

  auto val_ite = my_map.find("val2");
  if (val_ite != my_map.end()) 
    std::cout << (*val_ite).second << std::endl;
}
```
---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les **conteneurs associatifs** de la STL 7/7
STL 的**关联容器** 7/7

- le **dictionnaire** clé-valeur ou map `std::map<Key,Value>`
**键值字典** `std::map<Key,Value>`

```c++
#include <map>

int main(){
  std::map<std::string,double> my_map { {"val1",1.0},{"val2",2.0} };
  using my_iterator = std::map<std::string,double>::iterator;
  std::pair<my_iterator,bool> insert_ret = my_map.insert({"val1",3.0});
  if (! insert_ret.second) std::cout << "Insertion didn't occur" << std::endl;

  // Light syntax with structured bindings
  // 使用结构化绑定的简洁语法
  auto [iterator,is_inserted] = my_map.insert({"val2",4.0});
  if (! is_inserted) std::cout << "Insertion didn't occur";
  else std::cout << (*iterator).second;
}    
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

Les **conteneurs associatifs** de la STL
STL 的**关联容器**

- Les deux principaux conteneurs associatifs sont
两类主要的关联容器：
  - l'ensemble ou set `std::set<T>`
    集合 `std::set<T>`
  - le dictionnaire clé-valeur ou map `std::map<Key,T>`
    键值字典 `std::map<Key,T>`

**Exo 13.2** : manipulation de conteneurs associatifs
**练习 13.2**：关联容器操作

- créez un conteneur `set` et `map`,
创建一个 `set` 容器和一个 `map` 容器，
- les remplir à la construction et via une méthode `insert`,
在构造时以及通过 `insert` 方法填充它们，
- recherchez une valeur et modifiez-la si possible.
查找一个值，并在可能的时候修改它。

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

**Itérer** sur un conteneur STL 1/10
**遍历** STL 容器 1/10

- Un itérateur est un concept de la STL permettant le parcours d'une collection
迭代器是 STL 中用于遍历集合的概念
- Tous les conteneurs STL donne accès à un itérateur
所有 STL 容器都能提供迭代器访问
- `container.begin()` donne accès au premier élément du tableau
`container.begin()` 返回容器的第一个元素
- `container.end()` **n'est pas le dernier élément du conteneur**
`container.end()` **并不是容器的最后一个元素**
  - il **pointe après la fin du conteneur** (past-the-end)
    它**指向容器末尾之后的位置**（past-the-end）
  - si `iterator == container.end()` on est en dehors du conteneur
    若 `iterator == container.end()`，则表示已越过容器范围
  - pour tester que l'on est encore dans un conteneur on fait donc
    因此要检查是否仍在容器内，可使用
    - `if(iterator != container.end())`
      `if(iterator != container.end())`

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

**Itérer** sur un conteneur STL 2/10
**遍历** STL 容器 2/10

- Un itérateur a une syntaxe de pointeur
迭代器具有指针语法
  - Un itérateur **passe d'un élément à un autre** par l'opérateur `++`
    迭代器通过 `++` 运算符**在元素之间移动**
  - Un itérateur **donne accès à l'élément courant** par l'opérateur `*`
    迭代器通过 `*` 运算符**访问当前元素**
- Les algorithmes de la STL utilisent les itérateurs et non directement les conteneurs
STL 算法使用迭代器而非直接操作容器
  - ils sont donc **indépendants du type de conteneurs**
    因此它们**与容器类型无关**
- Ils existe plusieurs concepts d'itérateurs :
迭代器有多种概念：
  - `InputIterator`, `OutputIterator`, `ForwardIterator`
    `InputIterator`、`OutputIterator`、`ForwardIterator`
  - `BidirectionalIterator`
    `BidirectionalIterator`
  - `RandomAccessIterator`
    `RandomAccessIterator`

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

**Itérer** sur un conteneur STL 3/10
**遍历** STL 容器 3/10

- Il faut donc utiliser l'itérateur pour parcourir le conteneur
因此需要使用迭代器遍历容器
- la syntaxe est la même quel que soit le conteneur
无论何种容器，语法都相同

```c++
std::vector<int> my_vector {1,2,3};
for (auto iter = my_vector.begin(); iter!= my_vector.end();++iter){
  std::cout << *iter << std::endl;
}

std::map<std::string,int> my_map { {"val1",1.0},{"val2",2.0} };
for (auto iter = my_map.begin(); iter!= my_map.end();++iter){
  std::cout << "key   : " << (*iter).first << std::endl;
  std::cout << "value : " << (*iter).second << std::endl;
}
```
---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

**Itérer** sur un conteneur STL 4/10
**遍历** STL 容器 4/10

- Il faut donc utiliser l'itérateur pour parcourir le conteneur
因此需要使用迭代器遍历容器
- la syntaxe est la même quelle que soit le conteneur
无论何种容器，语法都相同

**Exo 13.3** : manipulation de conteneurs :
**练习 13.3**：容器操作：

- reprenez vos conteneurs des exercices 13.1 et 13.2,
重新使用练习 13.1 与 13.2 中的容器，
- parcourez-les avec un itérateur,
使用迭代器遍历它们，
- créer une fonction template qui affiche les éléments
编写一个模板函数用于输出元素
  - Pouvez-vous utiliser le même code pour tous les conteneurs ?
    你能为所有容器复用同一段代码吗？

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

**Itérer** sur un conteneur STL 5/10
**遍历** STL 容器 5/10
Une **nouvelle boucle** sur les conteneurs : range-based for loop
一种用于容器的**新型循环**：基于范围的 for 循环

```c++
std::vector vec {0,1,2}; // deduced to be std::vector<int>
// 推导类型为 std::vector<int>
for (int val : vec) { // val is a copy of a vec element
// val 是容器元素的副本
  std::cout << val << std::endl;
}
```

**Attention** à la déclaration de `val` : si l'on souhaite modifier le conteneur : il faut un **`int&`**
**注意** `val` 的声明：如果希望修改容器，需要使用 **`int&`**

```c++
std::vector vec {0,1,2}; // deduced to be std::vector<int>
// 推导类型为 std::vector<int>
for (int& val : vec) { // val is a ref toward a vec element
// val 是指向容器元素的引用
  val += 1;
}
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

**Itérer** sur un conteneur STL 6/10
**遍历** STL 容器 6/10
Une **nouvelle boucle** sur les conteneurs : range-based for loop
一种用于容器的**新型循环**：基于范围的 for 循环

```c++
std::map<std::string,int> my_map { {"val1",1.0},{"val2",2.0} };
for (std::pair<const std::string,int> val : my_map) { // val is a copy of a map element
// val 是映射元素的副本
  std::cout << "key   : " << val.first << std::endl;
  std::cout << "value : " << val.second << std::endl;
}
```

**Attention** à la déclaration de `val` : si l'on souhaite modifier la valeur (la clé est const)  : il faut un **`std::pair<const std::string,int>&`**  
**注意** `val` 的声明：若想修改值（键是 const），需要使用 **`std::pair<const std::string,int>&`**

```c++
std::map<std::string,int> my_map { {"val1",1.0},{"val2",2.0} };
for (std::pair<const std::string,int>& val : my_map) { // val is a copy of a map element
// val 是映射元素的副本
  val.second +=2;
}
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

**Boucle** sur un conteneur STL 7/10
**循环**遍历 STL 容器 7/10
Une nouvelle boucle sur les conteneurs : range-based for loop.
一种用于容器的新循环：基于范围的 for 循环。
S'utilise souvent avec `auto`
常与 `auto` 搭配使用

```c++
std::vector vec {0,1,2}; // deduced to be std::vector<int>
// 推导类型为 std::vector<int>
for (auto val : vec) { // val is a copy of a vec element
// val 是容器元素的副本
  std::cout << val << std::endl;
}
```

**Attention** à la déclaration de `val` : si l'on souhaite modifier le tableau : il faut  **`auto&`**  
**注意** `val` 的声明：如果希望修改数组，需要使用 **`auto&`**
```c++
std::vector vec {0,1,2}; // deduced to be std::vector<int>
// 推导类型为 std::vector<int>
for (auto& val : vec) { // val is a ref toward a vec element
// val 是指向容器元素的引用
  val += 1;
}
```

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

**Boucle** sur un conteneur STL 8/10
**循环**遍历 STL 容器 8/10
Une nouvelle boucle sur les conteneurs : range-based for loop.
一种用于容器的新循环：基于范围的 for 循环。
S'utilise souvent avec `auto`
常与 `auto` 搭配使用

```c++
std::map<std::string,int> my_map { {"val1",1.0},{"val2",2.0} };
for (auto val : my_map) { // val is a copy of a map element
// val 是映射元素的副本
  std::cout << "key   : " << val.first << std::endl;
  std::cout << "value : " << val.second << std::endl;
}
```

**Attention** à la déclaration de `val` : si l'on souhaite modifier la valeur  : il faut **`auto&`**
**注意** `val` 的声明：若想修改值，需要使用 **`auto&`**

```c++
std::map<std::string,int> my_map { {"val1",1.0},{"val2",2.0} };
for (auto& val : my_map) { // val is a ref toward a map element
// val 是指向映射元素的引用
  val.second +=2;
}
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

**Boucle** sur un conteneur STL 9/10
**循环**遍历 STL 容器 9/10
Une nouvelle boucle sur les conteneurs : range-based for loop.
一种用于容器的新循环：基于范围的 for 循环。
Grâce au **structured bindings** on peut aussi mapper directement la clé et la valeur :
得益于**结构化绑定**，可以直接映射键和值：

```c++
std::map<std::string,int> my_map { {"val1",1.0},{"val2",2.0} };
for (auto [key,val] : my_map) { // key and val map key and value of the map element
// key 和 val 分别对应映射元素的键和值
  std::cout << "key   : " << key << std::endl;
  std::cout << "value : " << val << std::endl;
}
```

**Attention** à la déclaration de `val` : si l'on souhaite modifier la valeur  : il faut un **`auto&`**
**注意** `val` 的声明：若想修改值，需要使用 **`auto&`**

```c++
std::map<std::string,int> my_map { {"val1",1.0},{"val2",2.0} };
for (auto& [key,val] : my_map) { // val is a ref toward the map element value
// val 是指向映射元素值的引用
  val +=2;
}
```

---

# Item 13 : la bibliothèque standard STL (conteneurs) 第13项：标准库 STL（容器）

**Boucle** sur un conteneur STL 10/10
**循环**遍历 STL 容器 10/10
Une nouvelle boucle sur les conteneurs : range-based for loop
一种用于容器的新循环：基于范围的 for 循环

- fonctionne pour pour **tous les conteneurs de la stl**
适用于**所有 STL 容器**
- plus largement peut fonctionner pour une structure utilisateur
更一般地，它也可用于自定义结构
  - dès lors qu'elle propose des méthodes `begin()` et `end()`
    只要该结构提供 `begin()` 与 `end()` 方法
  - donc dès qu'elle possède un itérateur
    也就是一旦拥有迭代器
- **Exo 13.4** : modifiez l'exercice 13.3 avec des range-for loop
**练习 13.4**：使用 range-for 循环改写练习 13.3
- **Exo 13.5** (*Bonus*) créez votre propre conteneur
**练习 13.5**（加分）：创建你自己的容器
  - parcourez le avec une range-for loop
    使用 range-for 循环遍历它
  - pour vous aider, faites le embarquer un conteneur STL...
    可借助一个内嵌的 STL 容器来实现……

---

# Item 14 : la bibliothèque standard 2 (algorithmes) 第14项：标准库之二（算法）

Les **algorithmes** 1/3, permettent d'appliquer des traitements à des conteneurs
**算法** 1/3，可用于对容器执行各种处理

- indépendamment du type de conteneur
与容器类型无关
- en utilisant les itérateurs des conteneurs
通过使用容器的迭代器

Les algorithmes de la STL sont classés en :
STL 中的算法分类如下：

- non modifying sequence : `for_each`, `find`, `find_if`, `search`, `any`, `count`, `count_if`...
非修改序列：`for_each`、`find`、`find_if`、`search`、`any`、`count`、`count_if` 等
- modifying sequence : `fill`, `transform`, `generate`, `copy`, `copy_if`, `remove`, `remove_if`...
修改序列：`fill`、`transform`、`generate`、`copy`、`copy_if`、`remove`、`remove_if` 等
- et bien plus encore : tri, partitionnement, numérique, opérations sur les set, min/max, comparaison..
以及更多：排序、分区、数值运算、集合操作、最小/最大、比较等
cf. https://en.cppreference.com/w/cpp/header/algorithm
参见 https://en.cppreference.com/w/cpp/header/algorithm

---

# Item 14 : la bibliothèque standard 2 (algorithmes) 第14项：标准库之二（算法）

Les **algorithmes** 2/3, quelques exemples; ne pas oublier `#include <algorithm>`
**算法** 2/3，一些示例；记得包含 `#include <algorithm>`

```c++
std::vector<int> vec {0,1,1,2};
int num_ones = std::count(vec.begin(),vec.end(),1); // 计数

auto iter_max= std::max_element(vec.begin(),vec.end()); // 最大值
std::cout << *iter_max << std::endl;

std::vector<int> vec_copy;
std::copy(vec.begin(),vec.end(),std::back_inserter(vec_copy)); // 复制

std::fill(vec.begin(),vec.end(),0); // 填充

bool is_equal = std::equal(vec.begin(),vec.end(),vec_copy.begin()); // 比较

auto iter = std::find(vec.begin(),vec.end(),0); // 查找
if (iter != vec.end()) { std::cout << "vec contains " << *iter;}
```

 ---

# Item 14 : la bibliothèque standard 2 (algorithmes) 第14项：标准库之二（算法）

Les **algorithmes** 2/3, quelques exemples
**算法** 2/3，一些示例

**Exo 14.1** Manipulation d'algorithmes
**练习 14.1** 算法操作

- Construire un tableau contenant les entiers de 1 à 100 grâce à l'algorithme `iota`. Attention cet algorithme est dans le header `numeric` ;
使用算法 `iota` 构造一个包含 1 到 100 的数组。注意该算法位于 `numeric` 头文件；
- Calculer la somme des éléments de ce tableau grâce à l'algorithme `accumulate` (header `numeric` également).
使用算法 `accumulate`（同样在 `numeric` 头文件中）计算该数组元素之和。

---

# Item 14 : la bibliothèque standard 2 (algorithmes) 第14项：标准库之二（算法）

Les **algorithmes** 3/3, quelques exemples avec traitement
**算法** 3/3，带处理函数的示例

```c++
struct Function{
    void operator()(int i ) {std::cout << i << ' ';} // treatment function 处理函数
};

int main(){
  std::vector<int> vec {0,1,2,3};
  std::for_each(vec.begin(),vec.end(),Function{}); // 遍历
}   
```

- De nombreux algorithmes appellent une fonction de traitement sur les éléments
许多算法会对元素调用处理函数
- Deux méthodes pour implémenter cette fonction :
实现该函数有两种方式：
  - une classe 'fonctor' qui se comporte comme une fonction (cf. ci-dessus)
    使用类似函数的函子类（见上例）
  - une fonction anonyme ($\lambda$-function) qui peut s'écrire "en ligne"
    使用可以内联编写的匿名函数（$\lambda$ 函数）

---

# Item 14 : la bibliothèque standard 2 (algorithmes) 第14项：标准库之二（算法）

Les **algorithmes**
**算法**

**Exo 14.2** Manipulation d'algorithmes avec traitement
**练习 14.2** 带处理函数的算法操作

- Reprenez votre exercice 14.1
复用练习 14.1
- Modifier l'appel à accumulate pour calculer le double de la somme de tous les éléments. Vous utiliserez un fonctor comme dans le transparent précédent (mais attention accumulate a besoin d'une opération binaire, avec comme signature `int op(int sum, int current_element)`).
修改 `accumulate` 的调用以计算所有元素之和的两倍。使用上一页中的函子（注意 `accumulate` 需要一个二元操作，签名为 `int op(int sum, int current_element)`）。

---

# Item 15 : les fonctions anonymes ou $\lambda$-functions 第15项：匿名函数或 $\lambda$ 函数

Les $\lambda$-functions 1/9
$\lambda$ 函数 1/9
Une syntaxe assez particulière mais très employée, introduite en C++11
语法较为特殊但应用广泛，于 C++11 引入

- On définit les arguments `()` le corps `{}` et une zone de capture `[]`
定义时包含参数 `()`、函数体 `{}` 以及捕获区 `[]`

```c++
auto lambda = []() {return "Hello lambda world";};
std::cout << lambda();
```

- la zone `()` permet de prendre des arguments d'entrée/sortie'
`()` 区域用于声明输入/输出参数

```c++
auto j = 1;deque
auto lambda1 = [](int i) {return i++;};
std::cout << lambda(j); // j not modified
// j 未被修改
auto lambda2 = [](int& i) {return i++;};
lambda2(j); // j modified
// j 被修改
```

---

# Item 15 : les fonctions anonymes ou $\lambda$-functions 第15项：匿名函数或 $\lambda$ 函数

Les $\lambda$-functions 2/9
$\lambda$ 函数 2/9
Une syntaxe assez particulière mais très employée, introduite en C++11
语法较为特殊但应用广泛，于 C++11 引入

- On définit les arguments `()` le corps `{}` et une zone de capture `[]`
定义时包含参数 `()`、函数体 `{}` 以及捕获区 `[]`

```c++
auto lambda = []() {return "Hello lambda world";};
std::cout << lambda();
```

- la zone `[]`permet d'embarquer des variables de l'environnement
`[]` 区域允许捕获上下文中的变量

```c++
int i = 1;
auto lambda = [i]() {return i;};
std::cout << lambda();
```

---

# Item 15 : les fonctions anonymes ou $\lambda$-functions 第15项：匿名函数或 $\lambda$ 函数

Les $\lambda$-functions 3/9
$\lambda$ 函数 3/9
Une syntaxe assez particulière mais très employée, introduite en C++11
语法较为特殊但应用广泛，于 C++11 引入

- Le type de retour est déduit automatiquement, mais on peut le préciser
返回类型会自动推导，但也可以显式指定

```c++
auto lambda = []() -> std::string {return "Hello lambda world";};
std::cout << lambda();

```
- le type de la lambda est créé automatiquement par le compilateur
lambda 的类型由编译器自动生成
  - il contient la signature complète de la lambda (capture comprise)
    其中包含 lambda 的完整签名（包括捕获）
  - il est unique
    该类型是唯一的

---

# Item 15 : les fonctions anonymes ou $\lambda$-functions 第15项：匿名函数或 $\lambda$ 函数

Les $\lambda$-functions 4/9
$\lambda$ 函数 4/9
Une syntaxe assez particulière mais très employée, introduite en C++11
语法较为特殊但应用广泛，于 C++11 引入

- le type de la lambda est créé automatiquement par le compilateur
lambda 的类型由编译器自动生成
  - il contient la signature complète de la lambda (capture comprise)
    其中包含 lambda 的完整签名（包括捕获）
  - il est unique
    该类型是唯一的
- on ne peut donc pas copier une lambda dans une autre
因此无法将一个 lambda 赋值给另一个
  - même avec une signature identique
    即便签名相同

```c++
auto lambda = [](int i) {return i++;};
lambda = [](int i) {return 2*i;}; // Error not known conversion
// 错误：不存在已知的转换
```

---

# Item 15 : les fonctions anonymes ou $\lambda$-functions 第15项：匿名函数或 $\lambda$ 函数

Les $\lambda$-functions 5/9
$\lambda$ 函数 5/9
Une syntaxe assez particulière mais très employée, introduite en C++11
语法较为特殊但应用广泛，于 C++11 引入

- on ne peut donc pas copier une lambda dans une autre
因此无法将一个 lambda 赋值给另一个
- mais on peut copier dans un objet de type `std::function`
但可以拷贝到 `std::function` 类型的对象中
  - défini avec la même signature
    只要定义了相同的签名

```c++
auto lambda = [](int i) {return i++;};
std::function<int(int)> function = lambda; // header <functional>
// 头文件 <functional>
std::cout << function(1);
```

# Item 15 : les fonctions anonymes ou $\lambda$-functions 第15项：匿名函数或 $\lambda$ 函数

Les $\lambda$-functions 6/9 La zone de capture :

- il est possible de capturer une variable par référence `[&i]` ou par copie [i]
可以通过引用 `[&i]` 或拷贝 `[i]` 捕获变量

```c++
int i = 1;
auto lambda1 = [i](){return i + 1;};
std::cout << lambda1();
std::cout << " i = " << std::endl; // 1
// 输出 1
auto lambda2 = [&i](){return ++i;};
lambda2();
std::cout << " i = " << std::endl; // 2
// 输出 2
auto lambda3 = [i](){return ++i;}(); // ERROR, increment read-only variable
// 错误：试图递增只读变量
```

- on peut capturer toutes les variables de l'environnement (non recommandé)
也可以捕获环境中的所有变量（不推荐）
  - par copie [=]
    通过拷贝 `[=]`
  - par référence [&]
    通过引用 `[&]`

---

# Item 15 : les fonctions anonymes ou $\lambda$-functions 第15项：匿名函数或 $\lambda$ 函数

Les $\lambda$-functions 7/9
$\lambda$ 函数 7/9

- on peut capturer toutes les variables de l'environnement (non recommandé)
可以捕获环境中的所有变量（不推荐）
  - par copie [=]
    通过拷贝 `[=]`
  - par référence [&]
    通过引用 `[&]`

```c++
int a = 1;
bool b = true;
auto lambda = [=](){ auto i = 0; if (b) i += a; return i;};
lambda();
auto lambda2 = [&](){a++; b = false;};
lambda2();
```

**Exo 15.1** : Créez une $\lambda$-function qui retourne le double de l'entier pris en argument, ou pris par capture. Avec la capture, faite une version où l'argument capturé est modifié.
**练习 15.1**：创建一个 $\lambda$ 函数，返回参数（或捕获的变量）数值的两倍；在捕获版本中，让被捕获的参数发生修改。

---

# Item 15 : les fonctions anonymes ou $\lambda$-functions 第15项：匿名函数或 $\lambda$ 函数

Les $\lambda$-functions 8/9
$\lambda$ 函数 8/9
Pourquoi utiliser des $\lambda$ ? A la place de fonctors ou de pointeurs de fonction
为什么使用 $\lambda$？可替代函子或函数指针

- pour passer des fonctions en argument
用于将函数作为参数传递
- un bon exemple : les algorithmes STL
一个典型示例：STL 算法

```c++
std::vector<int> vec {0,1,2,3};

std::for_each(vec.begin(),vec.end(),[](auto& i){i++;});
```

**Exo 15.2** : reprenez l'exercice 14.2 et remplacez le fonctor par une $\lambda$ fonction. Faites deux versions : une avec une prédéclaration de la $\lambda$ et une où vous écrivez directement la $\lambda$ dans l'algorithme.
**练习 15.2**：重做练习 14.2，用 $\lambda$ 函数替换函子。写出两个版本：一个预先声明 $\lambda$，另一个直接在算法中书写 $\lambda$。

---

# Item 15 : les fonctions anonymes ou $\lambda$-functions 第15项：匿名函数或 $\lambda$ 函数

Les $\lambda$-functions 9/9
$\lambda$ 函数 9/9
Pourquoi utiliser des $\lambda$ ? A la place de fonctors ou de pointeurs de fonction
为什么使用 $\lambda$？可替代函子或函数指针

- pour passer des fonctions en argument
用于将函数作为参数传递
- un bon exemple : les algorithmes STL
一个典型示例：STL 算法

```c++
std::vector<int> vec {0,1,2,3};

std::for_each(vec.begin(),vec.end(),[](auto& i){i++;});
```

**Exo 15.3** : à l'aide d'un algorithme et d'une $\lambda$, copier les éléments pairs d'un vecteur dans un autre vecteur.
**练习 15.3**：利用算法和 $\lambda$ 将一个向量中的偶数元素复制到另一个向量中。
