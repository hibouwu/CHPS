# Lab 1: HPC Toolchains & Performance profiling

A reminder on compilers, build systems, developement tools and profilers for HPC.

The material for this lab is available on the following [GitHub repo](https://github.com/dssgabriel/TOP-26/tree/main/lab1).


## CMake build system

1. Write a minimal `CMakeLists.txt` file for the `vector` code.

2. Improve your build system by splitting the `CMakeLists.txt` into multiple files in the directory hierarchy. Use CMake best practices.

Relevant resources for this exercise:

- [Modern CMake guide](https://cliutils.gitlab.io/modern-cmake/README.html)
- [CMake's `target_sources` command](https://cmake.org/cmake/help/v3.31/command/target_sources.html)
- [Examplar CMake](https://github.com/bemanproject/exemplar/blob/main/CMakeLists.txt)
- [NYU's VIP CMake lab](https://nyu-processor-design.github.io/getting_started/onboarding/02_cmake.html)


## Compiler toolchains and flags

1. Using the GCC compiler, build `vector` into an executable without any optimization flags.
What do you notice on the display of the values of vector `v3`?

2. Add the compilation flags `-Wall`, `-Wextra` and `-Werror`.  
Fix all the warnings emitted by the compiler and recompile the program.

3. Run the corrected program and record the time displayed.

4. Compile different versions of the code using flags `-O1`, `-O2`, `-O3` and `-Ofast`. Run them each and record their execution time.  
What do you see? Compare the generated assembly.

5. Repeat with a different compiler (e.g. LLVM Clang, Intel ICX, etc.).  
What differences do you notice?


## Compilation passes

1. Compare the flags included with `-O2` on [GCC 11.x](https://gcc.gnu.org/onlinedocs/gcc-11.5.0/gcc/Optimize-Options.html) and on [GCC 12.x](https://gcc.gnu.org/onlinedocs/gcc-12.5.0/gcc/Optimize-Options.html).
   Which flags differ?

2. Compare the flags included with `-Ofast` on [GCC](https://gcc.gnu.org/onlinedocs/gcc-15.2.0/gcc/Optimize-Options.html) and on [LLVM Clang](https://manpages.debian.org/experimental/clang-22/clang-22.1.en.html).
   Which flags differ?

3. Study the program in the `saxpy` directory, then compile it with the `-fdump-tree-all` flag.
   Run the `ls` command.
   What do you see?

4. What does it correspond to?
   How many do you see?

5. Delete the files that have appeared, and recompile with the `-O1` flag.  
   What do you observe? Are any files missing from the previous compilation?


## Code sanitizers

Valgrind is an open-source programming tool for debugging, profiling and identifying memory leaks. (see [Wikipedia page](https://en.wikipedia.org/wiki/Valgrind))

AddressSanitizer (or `ASan`) is an open-source programming tool that detects memory corruption bugs such as buffer overflows or accesses to a dangling pointer (use-after-free). AddressSanitizer is based on compiler instrumentation and directly mapped shadow memory. AddressSanitizer is currently implemented in Clang (starting from version 3.1), GCC (starting from version 4.8), Xcode (starting from version 7.x) and MSVC (widely available starting from version 16.9). (see [Wikipedia page](https://en.wikipedia.org/wiki/Code_sanitizer))

1. Use Valgrind on the `saxpy` code. What do you see?

2. Use ASan on the `saxpy` code. What do you observe? Fix the problem(s).

3. What are `dhat`, `memcheck`, `cachegrind`, `callgrind`, `massif`?

4. What are `kcachegrind`, `massif-visualizer`?


## Debuggers

### Sequential debugging

Study the program in `bugs`, then compile it with the `-g3` flag. Run the program using the GNU Debugger (GDB):
```sh
gdb <BIN_NAME>
```

GDB features interactive help. Start by browsing the help menu, typing `help` to get a list of commands. Then, `help` followed by a command to obtain information about it.

1. To locate the source of the first bug, type `run` (or `r`) under GDB. Quit (`quit`), correct the error and recompile the program.

2. Proceed in the same way to correct the next bug. Use the `backtrace` (or `bt`) command to display the call stack and obtain more information on the source of the error.

3. Identify the next error after recompiling the program. What is the problem? Can it be corrected?

4. We're now going to solve the last bug with other basic GDB functions. Start the debugger without using the `run` command for the moment. Set a breakpoint on the `launch_fibonacci()` function using `breakpoint launch_fibonacci` (or `b launch_fibonacci`).  
Now try to print the value of `fibo_values->max`.  
What do you see? Use `up` to position yourself before the function call, then `list` to display the lines of code around the breakpoint. Now enter the command `print fibo_values`. Correct the problem and recompile the program.

The sequence is incorrect. We should obtain the following numbers:
$$
F_0 = 0, F_1 = 1, F_2 = 1, F_3 = 2, F_4 = 5, F_6 = 8, \ldots
$$
To pinpoint the source of the error, we will display the values in the sequence step by step, monitoring changes to the `fibo_values->result` variable.


### Parallel debugging

There are debuggers specifically designed for the needs of parallel programs. Examples include TotalView and Linaro DDT. Although these programs are very powerful, they are not free nor open-source.
Nevertheless, it is possible to use GDB to debug small-scale parallel programs.
For multi-threaded programs, simply use the `info threads` command in GDB. We can choose to view a particular thread with the command `thread <thread_number>`.

!!! tip

    For MPI programs, we can use the following trick:
    ```sh
    mpirun -np <NPROC> <TERM_EMULATOR> -e gdb -args <MY_BIN> [ARGS...]
    ```
    This will open one terminal per MPI process.

1. Start from the original `mol-dyn` code and parallelize the program's most expensive function using OpenMP or Pthread.

2. If necessary, use the above methods to debug your parallel code on `mol-dyn`.


## Performance profiling with GNU `gprof`, Linux `perf` and `hotspot`

Gprof is a GNU Binary Utilities program for code profiling.
When compiling and linking source code with GCC, simply add the `-pg` option, the program generates a `gmon.out` file containing the profiling information.
You can then use Gprof to read this file, specifying the options.

Perf (sometimes called `perf_events` or `perf-tools`, originally Performance Counters for Linux, PCL) is a performance analysis tool for Linux, available in the Linux kernel since version 2.6.31 in 2009.
The userspace controlling utility, named `perf`, is accessed from the command line and provides a number of subcommands; it is capable of statistical profiling of the entire system (both kernel and userspace code).

Hotspot is a GUI for the Linux Perf profiler that replaces the `perf report` command (see [its GitHub page](https://github.com/KDAB/hotspot)).

The `mol-dyn` code supplied is a model of a molecular dynamics simulation in a gas (interaction between gas molecules).  
To compile, there are three preset sizes to choose from:

| Preset | CMake command | Number of particles |
| --- | --- | --- |
| mini | `-DNPART=MINI` | 1372 |
| medium | `-DNPART=MEDIUM` | 4000 |
| maxi | `-DNPART=MAXI` | 13500 |

1. Use Gprof on the `mol-dyn` code.
   What is the most computationally-intensive function?

2. Use Perf and Hotspot on the code.
   What is the most computationally-intensive function?

3. What is a _hotspot_ in the context of performance profiling?


## STREAM benchmarks

Given the code provided in the [lab 1 repository](https://github.com/dssgabriel/TOP-26/tree/main/lab1/stream), you are
to measure the performance of a very basic OpenMP implementation of the [STREAM bandwidth benchmarks](https://cs.virginia.edu/stream/ref.html).

### Performance metrics

1. Modify the `src/bin/main.cpp` file in order to actual measure something (e.g. execution time) and extract some
   performance data about them.
   You can use standard C or C++ clocks, CPU clock cycles, or any other unit of time that you think makes sense.
   You can also swap out the minimal provided code and use a dedicated benchmarking library instead, e.g. [Google Benchmarks](https://github.com/google/benchmark), [nanobench](https://github.com/martinus/nanobench), or [Catch2](https://github.com/catchorg/Catch2).

2. Derive some meaningful metrics (e.g., memory bandwith) from your raw measurements.

3. Plot the obtained data (e.g., using a Python script).

### Scalability

1. Measure the strong scaling speedup and weak scaling efficiency of the STREAM benchmarks.
   Write a simple script to do it.

2. Plot the obtained data.


## HPC package managers

- [Spack PM](https://spack.readthedocs.io/en/latest/index.html)
- [GNU GUIX](https://guix.gnu.org/)
