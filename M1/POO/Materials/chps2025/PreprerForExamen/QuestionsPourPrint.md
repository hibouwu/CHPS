# 📝 C++ 考试重点：打印顺序与内容分析 (Questions Pour Print)

本文档汇总了 C++ 考试中常见的“代码执行顺序与打印内容”判断题，涵盖构造/析构、作用域、移动语义、异常处理等核心考点。

---

## 1. 构造 / 析构 / 拷贝 / 移动的打印顺序 (Object Lifecycle) [Item 10]

**考点**：

* 构造函数 (ctor)、析构函数 (dtor) 的调用时机。
* 拷贝构造 (copy ctor) vs 移动构造 (move ctor)。
* 对象作为参数传递时的行为。
* NRVO (Named Return Value Optimization) 的影响（考试通常假设未优化或需讨论）。

### 📝 练习 1.1: 基础生命周期与参数传递

```cpp
#include <iostream>

struct A {
    int id;
    A(int i) : id(i) { std::cout << "ctor" << id << " "; }
    A(const A& a) : id(a.id) { std::cout << "copy" << id << " "; }
    A(A&& a) : id(a.id) { std::cout << "move" << id << " "; }
    ~A() { std::cout << "dtor" << id << " "; }
};

void f_val(A a) {}
void f_ref(const A& a) {}

int main() {
    A a(1);
    f_val(a);
    f_ref(a);
    std::cout << "end ";
}
```

**分析建议**：注意 `f_val` 会触发拷贝，`f_ref` 不会。注意析构发生的时刻（函数结束时）。

```txt
ctor1 copy1 dtor1 end dtor1 
```

1. 构造 `a(1)` ：`ctor1`
2. 传值给 `f_val(a)` ：`copy1`
3. `f_val` 结束时析构参数：`dtor1`
4. 打印  `end`
5. `main` 结束时析构 `a`：`dtor1`

### 📝 练习 1.2: 返回值优化 (NRVO) 与右值

```cpp
A createA(int i) {
    A temp(i);
    return temp; // 可能触发 copy 或 move，或被 NRVO 消除
}

int main() {
    A a = createA(2);
    std::cout << "done";
}
```

**分析建议**：如果编译器开启 NRVO，可能只有一次 ctor。如果未优化（如 `-fno-elide-constructors`），则可能看到 ctor -> move -> dtor (temp) -> dtor (a)。考试中通常需说明标准行为（C++17 后强制省略部分拷贝）。

```txt
输出（默认开启 NRVO/C++17）：ctor2 done dtor2
输出（禁用省略）：ctor2 move2 done dtor2 dtor2

解析：默认省略下返回值直接在调用点构造，`a` 存在到 `main` 末尾打印 `done` 后析构；禁用省略时返回值需要移动构造，打印顺序中 `done` 在析构之前。
```

---

## 2. 作用域、变量生命周期 (Scope & Lifetime) [Item 9]

**考点**：

* 局部变量的析构顺序（栈的后进先出）。
* 块作用域 `{}` 对生命周期的限制。
* `static` 变量的初始化与析构时机。

### 📝 练习 2.1: 嵌套作用域与析构顺序

```cpp
#include <iostream>

struct Trace {
    char name;
    Trace(char n) : name(n) { std::cout << "C" << name << " "; }
    ~Trace() { std::cout << "D" << name << " "; }
};

int main() {
    Trace a('A');
    {
        Trace b('B');
        std::cout << "in ";
    }
    std::cout << "out ";
}
```

```txt
输出：CA CB in DB out DA

解析：进入内层块先构造 `b`，块结束按后进先出析构 `b`，最后 `main` 结束析构最早构造的 `a`。
```

### 📝 练习 2.2: Static 变量

```cpp
void func() {
    static Trace s('S');
    Trace l('L');
}

int main() {
    std::cout << "1 ";
    func();
    std::cout << "2 ";
    func();
    std::cout << "3 ";
}
```

```txt
输出：1 CS CL DL 2 CL DL 3 DS

解析：首次调用构造静态 `s` 与局部 `l`，返回时析构 `l`；第二次只构造/析构新的 `l`；程序结束时才析构静态 `s`。
```

---

## 3. 传值 / 传引用 / 引用折叠 (Passing Mechanics) [Item 9, 16, 20]

**考点**：

* 函数重载决议：`f(A)`, `f(A&)`, `f(const A&)`, `f(A&&)`。
* 普通变量可以传给非 const 参数，也可以传给 const 参数（按值或 const&）。
* const 变量可以传给按值参数（会拷贝），也可以传给 const& 参数；但不能绑定到非常量左值引用参数（所以不能传给 T& 形参）。
* 如果同时有 f(T&) 和 f(const T&)，const 对象只能匹配 f(const T&)，非常量对象优先匹配 f(T&)。
* 右值（临时）只能绑定到 const T& 或 T&&，不能绑定到 T&。
* 左值 (lvalue) vs 右值 (rvalue) 的匹配规则。

### 📝 练习 3.1: 重载决议

```cpp
#include <iostream>

struct A {};

void f(A& a) { std::cout << "lref "; }
void f(const A& a) { std::cout << "cref "; }
void f(A&& a) { std::cout << "rref "; }

int main() {
    A x;
    const A y;
    
    f(x);       // calls f(A&)
    f(y);       // calls f(const A&)
    f(A{});     // calls f(A&&)
    f(std::move(x)); // calls f(A&&)
}
```

```txt
输出：lref cref rref rref

解析：左值 `x` 绑定到 `A&`，const 左值 `y` 绑定 `const A&`，临时与 `std::move(x)` 都是右值匹配 `A&&`。
```

---

## 4. std::move / std::forward [Item 16, 20]

**考点**：

* `std::move` 将左值强转为右值引用。
* `std::forward` 在模板中保持值类别。
* **注意**：`std::move` 自身不移动任何东西，它只是转换类型，真正的移动发生在构造或赋值时。

### 📝 练习 4.1: 手动 Move

```cpp
#include <iostream>
#include <utility>

struct Box {
    Box() { std::cout << "def "; }
    Box(const Box&) { std::cout << "copy "; }
    Box(Box&&) { std::cout << "move "; }
};

void process(Box b) {}

int main() {
    Box a;
    Box b = std::move(a); // move ctor
    process(std::move(b)); // move ctor (parameter construction)
}
```

```txt
输出：def move move

解析：默认构造 `a` → `b` 通过移动构造获得资源 → 传参给 `process` 再次移动构造形参。未定义析构打印，因此结束时无输出。
```

---

## 5. 成员对象构造顺序 (Member Initialization) [Item 10]

**考点**：

* 成员变量的初始化顺序**仅由类定义中的声明顺序决定**，与初始化列表顺序无关。
* 类自身构造函数体在成员构造之后执行。

### 📝 练习 5.1: 声明顺序陷阱

```cpp
#include <iostream>

struct Member {
    int id;
    Member(int i) : id(i) { std::cout << "M" << id << " "; }
};

struct Container {
    Member m2;
    Member m1;
    
    // 初始化列表顺序与声明相反，考察是否受骗
    Container() : m1(1), m2(2) { std::cout << "C "; }
};

int main() {
    Container c;
}
```

```txt
输出：M2 M1 C

解析：成员按声明顺序初始化，先 `m2` 再 `m1`，最后执行构造函数体打印 `C`，与初始化列表书写顺序无关。
```

---

## 6. 继承下的构造/析构 (Inheritance) [Item 8]

**考点**：

* 构造：基类 -> 成员 -> 派生类。
* 析构：派生类 -> 成员 -> 基类。

### 📝 练习 6.1: 继承链

```cpp
struct Base {
    Base() { std::cout << "BaseC "; }
    ~Base() { std::cout << "BaseD "; }
};

struct Derived : Base {
    Derived() { std::cout << "DerivedC "; }
    ~Derived() { std::cout << "DerivedD "; }
};

int main() {
    Derived d;
}
```

```txt
输出：BaseC DerivedC DerivedD BaseD

解析：构造顺序基类在前，派生在后；析构顺序相反，先派生再基类。
```

---

## 7. 异常流程 (Exception Stack Unwinding) [Item 18]

**考点**：

* `throw` 导致当前作用域剩余代码跳过。
* **Stack Unwinding**：在寻找 `catch` 块的过程中，栈上已构造的对象会被析构。

### 📝 练习 7.1: 异常与析构

```cpp
struct Obj {
    ~Obj() { std::cout << "~O "; }
};

void risk() {
    Obj o;
    std::cout << "step1 ";
    throw std::runtime_error("err");
    std::cout << "step2 "; // 不执行
}

int main() {
    try {
        risk();
    } catch (...) {
        std::cout << "caught ";
    }
}
```

```txt
输出：step1 ~O caught

解析：抛出异常后跳过 `step2`，在栈展开中析构局部对象 `o` 打印 `~O`，被 `catch` 捕获后打印 `caught`。
```

---

## 8. 模板展开与 Fold Expression [Item 21]

**考点**：

* 可变参数模板的递归展开顺序。
* C++17 Fold Expression 的展开方向。

### 📝 练习 8.1: Fold Expression 顺序

```cpp
template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args); // Binary Left Fold: ((((cout << arg1) << arg2) << arg3)...)
}

int main() {
    print(1, 2, 3);
}
```

```txt
输出：123

解析：左折叠 `(cout << 1) << 2 << 3`，按入参顺序无分隔符串联。
```

---

## 9. 智能指针 (Smart Pointers) [Item 17]

**考点**：

* `unique_ptr` 离开作用域自动 delete。
* `shared_ptr` 引用计数归零时 delete。
* 移动 `unique_ptr` 导致旧指针变空（不析构资源），新指针接管。

### 📝 练习 9.1: Unique Ptr 转移

```cpp
#include <iostream>
#include <memory>

struct Res {
    ~Res() { std::cout << "~Res "; }
};

int main() {
    std::unique_ptr<Res> p1 = std::make_unique<Res>();
    {
        std::unique_ptr<Res> p2 = std::move(p1); // p2 接管，p1 为空
        std::cout << "inner ";
    } // p2 离开作用域，~Res 被打印
    std::cout << "outer ";
} //p1 离开作用域，无资源析构，因此不调用析构函数，因为它已经是空的
```

```txt
输出：inner ~Res outer

解析：资源由 `p2` 接管，离开内层作用域时析构 `p2` 释放资源并打印，随后外层打印 `outer`。
```
