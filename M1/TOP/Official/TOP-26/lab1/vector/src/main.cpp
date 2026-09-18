#include <chrono>
#include <cstdint>
#include <locale>

#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/format.h>

#include <vector/vector.hpp>

constexpr int64_t VECTOR_SIZE = 32;
constexpr int64_t REPETITIONS = 30'000'000;

using std::chrono::high_resolution_clock;

auto print_info(void) -> void {
  fmt::print(
    "┌{0:─^77}┐\n"
    "│{1: ^77}│\n"
    "│{2: ^77}│\n"
    "└{0:─^77}┘\n",
    "",
    "M1 CHPS TOP - LAB 1: TOOLCHAINS & HPC ENVIRONMENT",
    "VECTOR ADDITION"
  );
  fmt::println(fmt::format(std::locale("en_US.UTF-8"), "VECTOR SIZE:  {:L}", VECTOR_SIZE));
  fmt::println(fmt::format(std::locale("en_US.UTF-8"), "REPETITIONS:  {:L}", REPETITIONS));
}

template <typename T>
auto print_results(Vector<T> const& a, Vector<T> const& b, Vector<T> const& c) -> void {
  fmt::print(
    "{1: ^3} = {2: ^3} + {3: ^3}\n"
    "{0:─^79}\n",
    "",
    "c",
    "a",
    "b"
  );
  for (int64_t i = 0; i < VECTOR_SIZE; ++i) {
    fmt::println("{: ^3} = {: ^3} + {: ^3}", c[i], a[i], b[i]);
  }
  fmt::println("{:─^79}", "");
}

auto benchmark(int64_t size, int64_t reps) -> void {
  Vector<double> a(size, 1.0);
  Vector<double> b(size, 2.0);
  Vector<double> c(size, 0.0);

  auto t0 = high_resolution_clock::now();
  for (int64_t r = 0; r < reps; ++r) {
    Vector<double>::add(c, a, b);
  }
  auto t1      = high_resolution_clock::now();
  auto elapsed = t1 - t0;

  fmt::print(
    "{0:─^79}\n"
    "Elapsed time: {1}, average: {2}\n"
    "{0:─^79}\n",
    "",
    elapsed,
    elapsed / reps
  );
  print_results(a, b, c);
}

auto main(int argc, char* argv[]) -> int {
  print_info();
  int useless = 42;
  benchmark(VECTOR_SIZE, REPETITIONS);
  return 0;
}
