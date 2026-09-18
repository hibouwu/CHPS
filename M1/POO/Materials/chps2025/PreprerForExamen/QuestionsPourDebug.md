# 🎯 C++ 考试重点：找错题分析 (Questions Pour Debug / Correction)

本文档依据课件（TooL / Mem / OO / Static）总结了“找错题”的高频考点。只有两类错误：**编译期错误 (Compile-time Error)** 和 **运行期错误 (Runtime Error)**。

---

# 🛑 第一部分：编译期错误 (Compile-time Errors)

**核心特征**：违反语法规则、类型系统、访问权限，代码无法生成可执行文件。

## 1. 访问权限错误 (Access Rights) [Item 7, 8]
**考点**：`class` 默认 `private`，对象在外部无法访问 `private` 或 `protected` 成员。

```cpp
class A {
    int x; // 默认为 private
public:
    int y;
};

int main() {
    A a;
    a.y = 1; // OK
    a.x = 2; // ❌ 编译错误：'int A::x' is private
}
```

## 2. 继承导致的可见性改变 (Inheritance Visibility) [Item 8]
**考点**：`private` 继承会将基类的 `public/protected` 成员在子类中变为 `private`。

```cpp
class Base {
public:
    int x;
};

class Derived : private Base {
    // x 在这里变成了 private
};

int main() {
    Derived d;
    d.x = 10; // ❌ 编译错误：'int Base::x' is inaccessible
}
```

## 3. Const 方法修改成员 (Const Correctness) [Item 7]
**考点**：`const` 成员函数承诺不修改任何成员变量（除非成员是 `mutable`）。

```cpp
class A {
    int x = 0;
public:
    void f() const {
        x = 2;  // ❌ 编译错误：assignment of member 'A::x' in read-only object
    }
};
```

## 4. 引用绑定错误 (Reference Binding) [Item 9]
**考点**：非常量左值引用 (`T&`) 不能绑定到右值（如临时对象、字面量）。

```cpp
void f(int& x) {}

int main() {
    int a = 1;
    f(a); // OK
    f(1); // ❌ 编译错误：cannot bind non-const lvalue reference to an rvalue
}
```

*修正*：改为 `void f(const int& x)` 或 `void f(int&& x)`。

## 5. Unique_ptr 的复制 (Unique_ptr Copy) [Item 17]

**考点**：`std::unique_ptr` 是独占所有权的，删除了拷贝构造函数，只能移动。

```cpp
#include <memory>
void func() {
    std::unique_ptr<int> p1 = std::make_unique<int>(10);
    std::unique_ptr<int> p2 = p1; // ❌ 编译错误：use of deleted function (copy constructor)
}
```

*修正*：`std::unique_ptr<int> p2 = std::move(p1);`

## 6. 纯虚函数与抽象类 (Abstract Classes) [Item 19]
**考点**：包含纯虚函数的类是抽象类，不能实例化。

```cpp
class Shape {
public:
    virtual void draw() = 0; // 纯虚函数
};

class Circle : public Shape {}; // 未重写 draw，仍为抽象类

int main() {
    Shape s;   // ❌ 编译错误：cannot instantiate abstract class 'Shape'
    Circle c;  // ❌ 编译错误：cannot instantiate abstract class 'Circle'
}
```

## 7. 模板链接错误 (Template Linking) [Item 12]
**考点**：模板的声明和定义通常不能分离在 `.h` 和 `.cpp` 中（除非显式实例化），否则链接时找不到定义。

```cpp
// A.h
template<typename T> void f(T);

// A.cpp
template<typename T> void f(T) {}

// main.cpp
#include "A.h"
int main() {
    f(10); // ❌ 链接错误 (Linker Error)：undefined reference to validation
}
```

---

# 💣 第二部分：运行期错误 (Runtime Errors)

**核心特征**：编译通过，但程序运行时崩溃 (Crash/Segfault)、行为未定义 (UB) 或非正常终止。

## 8. 指针错误 (Pointers: Segfault) [Item 9]
**考点**：解引用空指针 (`nullptr`) 或未初始化的指针。

```cpp
void func() {
    int* p = nullptr;
    *p = 10; // ❌ 运行期错误：Segmentation Fault (访问非法内存)
    
    int* q;  // 未初始化，指向随机地址
    *q = 5;  // ❌ 运行期错误：Undefined Behavior / Segfault
}
```

## 9. 内存双重释放 (Double Free) [Item 9, 10]
**考点**：手动管理 `new/delete` 时，如果未遵守 Rule of 3（未自定义拷贝构造），默认的浅拷贝会导致两个对象指向同一块内存，析构时重复释放。

```cpp
class A {
    int* ptr;
public:
    A() { ptr = new int(1); }
    ~A() { delete ptr; }
    // 缺少拷贝构造函数，使用编译器默认版本（浅拷贝）
};

int main() {
    {
        A a;
        A b = a; // b.ptr 和 a.ptr 指向同一个地址
    } // b 析构，delete ptr; a 析构，delete ptr;
    // ❌ 运行期错误：Double free detected
}
```

## 10. Vector 越界访问 (Vector Out of Range) [Item 13]
**考点**：`operator[]` 不检查边界（UB），`.at()` 检查边界（抛异常）。

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3};
    
    // 情况 A: operator[]
    int val = v[100]; // ❌ 运行期错误：Undefined Behavior (可能读脏数据，也可能崩溃)
    
    // 情况 B: .at()
    try {
        v.at(100); // ❌ 运行期异常：std::out_of_range
    } catch(...) {}
}
```

## 11. Noexcept 抛出异常 (Throw in Noexcept) [Item 18]
**考点**：声明为 `noexcept` 的函数如果抛出异常，程序会直接调用 `std::terminate` 终止。

```cpp
void safe() noexcept {
    throw std::runtime_error("Oops"); // ❌ 运行期错误：std::terminate called
}

int main() {
    try {
        safe();
    } catch(...) {
        // 无法捕获，程序已终止
    }
}
```

## 12. 悬空引用 (Dangling Reference) [Item 9]
**考点**：返回了局部变量的引用，函数结束后局部变量销毁，引用指向无效内存。

```cpp
int& getInt() {
    int x = 10;
    return x; // ⚠️ 编译警告，但可能通过
}

int main() {
    int& ref = getInt();
    std::cout << ref; // ❌ 运行期错误：Undefined Behavior (访问已销毁的栈内存)
}
```
