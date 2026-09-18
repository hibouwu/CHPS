#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <random>
#include <span>
#include <vector>

#include <nanobench.h>

namespace nb = ankerl::nanobench;
using namespace std::chrono_literals;

constexpr size_t N = 100'000;

/// Initialize array with random 64-bit floating-point values between 0 and 1.
auto array_init(std::span<double> array) -> void {
  std::mt19937_64 rng(std::random_device{}());
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  std::ranges::generate(array, [&] { return dist(rng); });
}

auto array_shuffle(std::span<double> array) -> void {
  std::mt19937 rng(std::random_device{}());
  // Sattolo's algorithm: swap i with random j in [0, i-1)
  for (int i = array.size() - 1; i > 0; --i) {
    std::uniform_int_distribution<int> dist(0, i - 1);
    std::swap(array[i], array[dist(rng)]);
  }
}

static int __attribute__((noinline, noclone)) returns_one() {
  return 1;
}
static int __attribute__((noinline, noclone)) returns_zero() {
  return 0;
}

/// Compare array values to 0.5 and set the result array accordingly.
auto array_test(std::span<double const> array, std::span<int> result) -> void {
  assert(array.size() == result.size());
  using fn_t             = int (*)();
  fn_t volatile table[2] = {returns_zero, returns_one};
  for (size_t i = 0; i < array.size(); ++i) {
    bool cond = array[i] < 0.5;
    asm volatile("" : "+r"(cond)); // opaque to optimizer
    int idx   = cond ? 1 : 0;
    result[i] = table[idx]();
  }
}

auto main(void) -> int {
  // Allocate memory for 3 arrays
  std::vector<double> a_sorted(N);
  std::vector<double> a_unsorted(N);
  std::vector<int> res(N);

  // Initialize arrays
  array_init(a_unsorted);
  array_shuffle(a_unsorted);
  array_init(a_sorted);
  std::sort(a_sorted.begin(), a_sorted.end());

  nb::Bench bs;
  bs.title("branch prediction").timeUnit(1s, "s").relative(true);
  bs.run("unsorted", [&]() {
    array_test(a_unsorted, res);
    nb::doNotOptimizeAway(res);
  });
  bs.run("sorted", [&]() {
    array_test(a_sorted, res);
    nb::doNotOptimizeAway(res);
  });

  // // Print results
  // std::printf("Unsorted array: %3lf s\n", elapsed_unsorted.count());
  // std::printf("Sorted array:   %3lf s\n", elapsed_sorted.count());
  // std::printf("Speedup:        %3lfx faster with sorted array\n", elapsed_unsorted / elapsed_sorted);

  return 0;
}
