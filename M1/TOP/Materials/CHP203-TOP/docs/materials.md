# Materials repository & Software stack 材料仓库与软件栈

The lab material for this course is available on the following [GitHub repository](https://github.com/dssgabriel/TOP-26). 本课程的实验材料可在以下 [GitHub 仓库](https://github.com/dssgabriel/TOP-26)中获取。

This course expects students to use a Linux machine. If you are running another operating systems, please borrow a _Cartable Numerique_ by the administration. 本课程要求学生使用 Linux 机器。如果你使用的是其他操作系统，请向行政部门借用一台 _Cartable Numerique_。

Most of the software used throught in this course can be easily installed via your Linux distribution package manager (e.g. `apt` on Ubuntu/Debian, `dnf` on RedHat-like, `pacman`/`paru` on Arch-like, etc.), or using the [Spack Package Manager](https://spack.readthedocs.io/en/latest/index.html). 本课程中使用的大多数软件都可以通过你的 Linux 发行版包管理器轻松安装（例如 Ubuntu/Debian 上的 `apt`、类 RedHat 系统上的 `dnf`、类 Arch 系统上的 `pacman`/`paru` 等），或者使用 [Spack Package Manager](https://spack.readthedocs.io/en/latest/index.html) 安装。

To load Spack-installed software, use the `spack load <PACKAGE>` command. 要加载通过 Spack 安装的软件，请使用 `spack load <PACKAGE>` 命令。


## Required software 所需软件

### CMake

Most of this course material relies on CMake for building the code provided in each exercise. 本课程的大部分材料都依赖 CMake 来构建每个练习中提供的代码。

You can get CMake from [here](https://cmake.org/download/). The prefered version for this course is 你可以从[这里](https://cmake.org/download/)获取 CMake。本课程推荐使用的版本是
[3.31](https://cmake.org/cmake/help/v3.31/release/3.31.html), the minimum required version is [3.31](https://cmake.org/cmake/help/v3.31/release/3.31.html)，最低要求版本是
[3.25](https://cmake.org/cmake/help/v3.25/release/3.25.html). [3.25](https://cmake.org/cmake/help/v3.25/release/3.25.html)。

1. Download the binary distribution for Linux: 1. 下载适用于 Linux 的二进制发行包：
```sh
wget https://github.com/Kitware/CMake/releases/download/v3.31.11/cmake-3.31.11-linux-x86_64.tar.gz
```

2. Install the tarball (in a userspace directory): 2. 安装该压缩包（安装到用户目录中）：
```sh
tar -C $HOME/.local/ --strip-components=1 -xf cmake-3.31.11-linux-x86_64.tar.gz
```

3. Ensure it works: 3. 确认其可正常工作：
```sh
cmake --version
```

### C/C++ Compilers C/C++ 编译器

Compiler 编译器 | Version 版本 | Spack command Spack 命令
--- | --- | ---
GNU Compiler Collection (gcc) | 15.x | `spack install gcc@15`
LLVM Clang (clang) | 22.x | `spack install llvm@22`
Intel oneAPI (icx) | 2025.x | `spack install intel-oneapi-compilers@2025`

### MPI

Implementation 实现 | Version 版本 | Spack command Spack 命令
--- | --- | ---
Open MPI | 5.x | `spack install openmpi@5`
MPICH | 4.x | `spack install mpich@4`


## Formatting and style 格式与风格

We expect students to format their code according to a `clang-format` spec (one is provided at the root of the lab repo). Similarly, CMake files should be formatted using tools such as `gersemi`. 我们希望学生按照 `clang-format` 规范来格式化代码（实验仓库根目录已提供一份配置）。类似地，CMake 文件也应当使用 `gersemi` 之类的工具进行格式化。

To improve your C/C++ code, we suggest you to regularly run tools such as `clang-tidy`, `sonar-lint` or other code linters that help detect anti-patterns, weird or inefficient coding styles, and suggest ways of writing more idiomatic C/C++. 为了改进你的 C/C++ 代码，我们建议你定期运行 `clang-tidy`、`sonar-lint` 或其他代码检查工具，以帮助发现反模式、奇怪或低效的编码风格，并给出更符合惯用法的 C/C++ 写法建议。

You should also look into popular and battle-tested code style guidelines: 你还应该参考一些流行且经过实践检验的代码风格指南：

- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) - C++ 核心指南
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) - Google C++ 风格指南
- [Carbon C++ Style Guide](https://docs.carbon-lang.dev/docs/project/cpp_style_guide.html) - Carbon C++ 风格指南
- [MISRA C++](https://misra.org.uk/misra-c-plus-plus/) - MISRA C++
- [ANSSI C Rules for C language software development](https://cyber.gouv.fr/en/publications/rules-secure-c-language-software-development) - ANSSI C 语言软件开发规则
