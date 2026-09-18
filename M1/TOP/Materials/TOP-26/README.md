# MYCHP203 — Parallel Optimization Techniques, Spring 2026

### Lab sessions

Tuesdays, 9:30 - 12:45 CET, CN2, Rabelais building, Guyancourt campus

Lab sessions are not graded, though they remain mandatory. Any absence shall be justified to the administration and the TA.
Exercises are corrected during class, and corrections will _not_ be given.

### Resources

> [!TIP]
> Valuable resources for this course will be added here. Check back often!

Build systems:
- A guide on [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- The [Meson build system](https://mesonbuild.com/index.html)
- [Ninja](https://ninja-build.org/): a small & fast build system

C Programming language:
- [Modern C](https://inria.hal.science/hal-02383654) by Jens Gustedt (researcher at INRIA Strasbourg and ISO C standards committee member)
- Semantics of [the `restrict` keyword](https://open-std.org/jtc1/sc22/wg14/www/docs/n3234.htm)
- Latest draft of the [ISO C standard](https://open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf) (as of 2024-03-26)

C++ Programming language:
- WG21 - ISO C++23 [P0009](https://open-std.org/jtc1/sc22/wg21/docs/papers/2022/p0009r18.html): A standard C++ multidimensional container abstraction, [`std::mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)

Computer Architecture:
- [Computer Architecture: A quantitative approach](https://dl.acm.org/doi/book/10.5555/1999263)
- [What every programmer should know about memory](https://people.freebsd.org/~lstewart/articles/cpumemory.pdf)

Memory:
- [Kokkos tutorial](https://github.com/kokkos/kokkos-tutorials/blob/main/Intro-Full/Slides/KokkosTutorial_ORNL20.pdf) slides (specifically slides on memory layout, slides 74-84)
- [C++ on sea 2023, a talk by JF Bastien - \*(char\*)0 = 0;](https://youtu.be/dFIqNZ8VbRY) (treats about memory hierarchy: caches, TLB, virtual/physical memory)
- [Cache coherency protocols](https://en.wikipedia.org/wiki/Cache_coherency_protocols_(examples))

Performance profiling:
- Scalability benchmarking: [strong & weak scaling](https://hpc-wiki.info/hpc/Scaling)
- [Linux perf](https://perf.wiki.kernel.org/index.php/Main_Page) (nice tutorial in french: [here](https://grasland.pages.in2p3.fr/tp-perf/introduction/index.html))
- Modular Assembly Quality Analyzer & Optimizer: [MAQAO](https://www.maqao.org/)
- Tuning and Analysis Utilities: [TAU](https://www.cs.uoregon.edu/research/tau/home.php)
- [Scalasca](https://www.scalasca.org/)
- [µops.info's uiCA](https://uops.info/uiCA.html): Accurate Throughput Prediction of Basic Blocks on Recent Intel Microarchitectures
