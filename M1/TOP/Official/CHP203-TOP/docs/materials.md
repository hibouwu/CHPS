# Materials repository & Software stack

The lab material for this course is available on the following [GitHub repository](https://github.com/dssgabriel/TOP-26).

This course expects students to use a Linux machine. If you are running another operating systems, please borrow a _Cartable Numerique_ by the administration.

Most of the software used throught in this course can be easily installed via your Linux distribution package manager (e.g. `apt` on Ubuntu/Debian, `dnf` on RedHat-like, `pacman`/`paru` on Arch-like, etc.), or using the [Spack Package Manager](https://spack.readthedocs.io/en/latest/index.html).

To load Spack-installed software, use the `spack load <PACKAGE>` command.


## Required software

### CMake

Most of this course material relies on CMake for building the code provided in each exercise.

You can get CMake from [here](https://cmake.org/download/). The prefered version for this course is
[3.31](https://cmake.org/cmake/help/v3.31/release/3.31.html), the minimum required version is
[3.25](https://cmake.org/cmake/help/v3.25/release/3.25.html).

1. Download the binary distribution for Linux:
```sh
wget https://github.com/Kitware/CMake/releases/download/v3.31.11/cmake-3.31.11-linux-x86_64.tar.gz
```

2. Install the tarball (in a userspace directory):
```sh
tar -C $HOME/.local/ --strip-components=1 -xf cmake-3.31.11-linux-x86_64.tar.gz
```

3. Ensure it works:
```sh
cmake --version
```

### C/C++ Compilers

Compiler | Version | Spack command
--- | --- | ---
GNU Compiler Collection (gcc) | 15.x | `spack install gcc@15`
LLVM Clang (clang) | 22.x | `spack install llvm@22`
Intel oneAPI (icx) | 2025.x | `spack install intel-oneapi-compilers@2025`

### MPI

Implementation | Version | Spack command
--- | --- | ---
Open MPI | 5.x | `spack install openmpi@5`
MPICH | 4.x | `spack install mpich@4`


## Formatting and style

We expect students to format their code according to a `clang-format` spec (one is provided at the root of the lab repo). Similarly, CMake files should be formatted using tools such as `gersemi`.

To improve your C/C++ code, we suggest you to regularly run tools such as `clang-tidy`, `sonar-lint` or other code linters that help detect anti-patterns, weird or inefficient coding styles, and suggest ways of writing more idiomatic C/C++.

You should also look into popular and battle-tested code style guidelines:

- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [Carbon C++ Style Guide](https://docs.carbon-lang.dev/docs/project/cpp_style_guide.html)
- [MISRA C++](https://misra.org.uk/misra-c-plus-plus/)
- [ANSSI C Rules for C language software development](https://cyber.gouv.fr/en/publications/rules-secure-c-language-software-development)
