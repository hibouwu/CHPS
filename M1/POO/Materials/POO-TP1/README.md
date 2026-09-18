# TD1 Introduction à CMake

# 1.1 Compiler un programme et une bibliothèque

## 1.1.1 Manuellement (pour intuiter le fonctionnement)

```bash
Compile with:
g++ -o mylib_dir/libmylib.so -fpic -shared mylib_dir/MyClass.cpp
```

Methods naive compilation and execution:

Compile with:
```bash
g++ -Lmylib_dir -Imylib_dir src/main.cpp -lmylib
```
Run with:
```bash
LD_LIBRARY_PATH=mylib_dir ./a.out
```

Compile with:
```bash
g++ -Lmylib_dir -Imylib_dir src/main.cpp -lmylib -o main
```

Run with:
```bash
LD_LIBRARY_PATH=mylib_dir ./main
```

g++顺序：
1. -L指定库文件路径
2. -I指定头文件路径
3. 源文件
4. -l指定库文件
5. -o指定输出文件名

注意：-l后面紧跟库名，不加前缀lib和后缀.so

## 1.1.2 Avec CMake

创建构建目录：
```bash
mkdir -p build
cd build
```

配置项目：
```bash
cmake ..
```

编译项目：
```bash
make
# 或者使用
cmake --build .
```

运行程序：
```bash
./Main.exe
```

运行测试：
```bash
ctest
```

# 1.2 Ajouter des tests

## 1.2.1 Compiler et installer GTest

```shell
#Ubuntu
sudo apt-get install libgtest-dev
#Fedora
sudo dnf install gtest-devel
```

## 1.2.2 Trouver et utiliser GTest via CMake

- La doc CMake est là :
  - <https://cmake.org/cmake/help/v3.18/module/FindGTest.html?highlight=gtest#module:FindGTest>
- utilisez la commande `find_package` de CMake pour chercher GTest. Indiquez l'option `REQUIRED`.

## 1.2.3 Ajouter des tests via GTest
.
├── build
├── CMakeLists.txt
├── my_libConfig.cmake.in
├── mylib_dir
│   ├── CMakeLists.txt
│   ├── MyClass.cpp
│   └── MyClass.h
├── src
│   └── main.cpp
├── Sujet-TP1.md
└── tests
    └── test.cpp