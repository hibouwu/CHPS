# 🎓 Examen Blanc de POO C++ (Simulation)

本文档包含两套模拟卷 (**Sujet A** 和 **Sujet B**)，每套卷子均包含 **Code Reading (打印预测)** 和 **Code Correction (找错)** 两部分。

建议考试时间：**30 - 45 分钟 / 套**。

---

# 📝 Sujet A

## Partie 1: Prédire l'affichage (Code Reading) [10 pts]

**Question 1: Object Lifecycle & Inheritance**
给定以下代码，请写出完整的标准输出内容。

```cpp
#include <iostream>

struct Base {
    Base() { std::cout << "B_ctor "; }
    virtual ~Base() { std::cout << "B_dtor "; }
};

struct Member {
    Member(int i) { std::cout << "M" << i << " "; }
    ~Member() { std::cout << "~M "; }
};

struct Derived : Base {
    Member m;
    Derived() : m(1) { std::cout << "D_ctor "; }
    ~Derived() { std::cout << "D_dtor "; }
};

int main() {
    {
        Derived d;
        std::cout << "| ";
    }
    std::cout << "End";
}
```

<details>
<summary>点击查看答案</summary>

```txt
B_ctor M1 D_ctor | D_dtor ~M B_dtor End
```
**解析**：
1. `Derived` 构造：先 `Base` 构造 (B_ctor)，再 `Member` 成员构造 (M1)，最后 `Derived` 构造体 (D_ctor)。
2. 打印 `|`。
3. `Derived` 离开作用域析构：先 `Derived` 析构 (D_dtor)，再 `Member` 析构 (~M)，最后 `Base` 析构 (B_dtor)。
</details>

---

**Question 2: Passing Mechanics & Static**
给定以下代码，请写出输出。

```cpp
#include <iostream>

void f(int& x) { std::cout << "L "; }
void f(int&& x) { std::cout << "R "; }

struct Tracer {
    Tracer() { std::cout << "T "; }
    ~Tracer() { std::cout << "~T "; }
};

void func() {
    static Tracer t;
    int a = 0;
    f(a);
    f(1);
    f(std::move(a));
}

int main() {
    func();
    std::cout << "- ";
    func();
}
```

<details>
<summary>点击查看答案</summary>

```txt
T L R R - L R R ~T
```
**解析**：
1. 第一次调用 `func`: 构造静态 `t` (T)。`f(a)` 调 L，`f(1)` 调 R，`f(move(a))` 调 R。
2. 打印 `-`。
3. 第二次调用 `func`: `t` 已构造不再打印。`a` 重新传参打印 L R R。
4. `main` 结束，静态对象 `t` 析构 (~T)。
</details>

---

## Partie 2: Code Correction (Trouver les erreurs) [10 pts]

请指出以下代码中的错误（编译错误或运行期错误），并简述原因。

**Code 1**
```cpp
class A {
    int val;
public:
    void set(int v) const {
        val = v; 
    }
};
```
<details>
<summary>答案</summary>
❌ **编译错误**。`set` 是 `const` 成员函数，不能修改成员变量 `val`。
</details>

---

**Code 2**
```cpp
void process(int& x) {}

int main() {
    process(10);
}
```
<details>
<summary>答案</summary>
❌ **编译错误**。非常量左值引用 `int&` 不能绑定到右值（临时对象 `10`）。
</details>

---

**Code 3**
```cpp
struct A {
    int* p;
    A() { p = new int(5); }
    ~A() { delete p; }
};

int main() {
    A a;
    A b = a;
}
```
<details>
<summary>答案</summary>
💣 **运行期错误 (Double Free)**。违反 Rule of 3，使用默认拷贝构造（浅拷贝），`a` 和 `b` 的 `p` 指向同一内存，析构时重复释放。
</details>

---

**Code 4**
```cpp
#include <vector>
int main() {
    std::vector<int> v;
    int x = v[0];
}
```
<details>
<summary>答案</summary>
💣 **运行期错误 (Undefined Behavior)**。访问空 vector 的第 0 个元素越界。
</details>

---

# 📝 Sujet B

## Partie 1: Prédire l'affichage (Code Reading) [10 pts]

**Question 1: Move Semantics & Stack Unwinding**
写出输出内容。

```cpp
#include <iostream>

struct Box {
    Box() { std::cout << "def "; }
    Box(const Box&) { std::cout << "copy "; }
    Box(Box&&) { std::cout << "move "; }
    ~Box() { std::cout << "dtor "; }
};

void may_throw() {
    Box b;
    std::cout << "throw ";
    throw 1;
}

int main() {
    try {
        may_throw();
    } catch(...) {
        std::cout << "catch ";
    }
}
```

<details>
<summary>点击查看答案</summary>

```txt
def throw dtor catch
```
**解析**：构造 `b` (def) -> 打印 throw -> 抛出异常 -> 栈展开析构局部变量 `b` (dtor) -> 进入 catch 块 (catch)。
</details>

---

**Question 2: Smart Pointers & Scope**
写出输出。

```cpp
#include <iostream>
#include <memory>

struct Res {
    int id;
    Res(int i) : id(i) { std::cout << "+" << id << " "; }
    ~Res() { std::cout << "-" << id << " "; }
};

int main() {
    std::unique_ptr<Res> p1 = std::make_unique<Res>(1);
    {
        std::shared_ptr<Res> p2 = std::make_shared<Res>(2);
        std::cout << "in ";
    }
    std::unique_ptr<Res> p3 = std::move(p1);
    std::cout << "out ";
}
```

<details>
<summary>点击查看答案</summary>

```txt
+1 +2 in -2 out -1
```
**解析**：
1. `p1` 构造 `Res(1)` (+1)。
2. 进入块，`p2` 构造 `Res(2)` (+2)，打印 in。
3. 离开块，`p2` 引用计数归零，析构 `Res(2)` (-2)。
4. `p1` 移动给 `p3`，`p1` 变空，资源所有权转移。
5. 打印 out。
6. `main` 结束，`p3` 析构 `Res(1)` (-1)，`p1` 为空不操作。
</details>

---

## Partie 2: Code Correction (Trouver les erreurs) [10 pts]

**Code 1**
```cpp
class Base {
public:
    int x;
};
class Derived : private Base {};

int main() {
    Derived d;
    d.x = 5;
}
```
<details>
<summary>答案</summary>
❌ **编译错误**。`private` 继承将 `Base::x` 在 `Derived` 中变为私有，外部不可访问。
</details>

---

**Code 2**
```cpp
#include <memory>
void f() {
    std::unique_ptr<int> a = std::make_unique<int>(1);
    std::unique_ptr<int> b = a;
}
```
<details>
<summary>答案</summary>
❌ **编译错误**。`unique_ptr` 禁止拷贝，只能移动。
</details>

---

**Code 3**

```cpp
void f() noexcept {
    throw 42;
}
int main() {
    try { f(); } catch(...) {}
}
```

<details>
<summary>答案</summary>
💣 **运行期错误**。在 `noexcept` 函数中抛出异常会导致 `std::terminate`，无法被 catch。
</details>

---

**Code 4**

```cpp
int* getPtr() {
    int x = 10;
    return &x;
}
int main() {
    int* p = getPtr();
    *p = 20;
}
```

<details>

<summary>答案</summary>
💣 **运行期错误 (UB)**。返回局部变量 `x` 的地址，函数返回后 `x` 已销毁，`p` 成为悬空指针。
</details>
