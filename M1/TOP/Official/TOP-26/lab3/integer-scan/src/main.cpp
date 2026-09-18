#include <vector>

#include <fmt/core.h>

#include "cycle.h"

// Sequential inclusive scan (prefix sum)
auto inclusive_scan_sequential(std::vector<int> const& input, std::vector<int>& output) -> void {
  if (input.empty())
    return;

  size_t const n = input.size();
  output.resize(n);

  output[0] = 0 // ??;
    for (size_t i = 1; i < n; ++i) {
    // ??
  }
}

auto main(int argc, char* argv[]) -> int {
  size_t n = 10'000'000;
  if (argc == 2) {
    n = std::stoll(argv[1]);
  }

  std::vector<int> input(n, 1);
  std::vector<int> output(n);

  // Measure inclusive scan performance
  auto t0 = getticks();
  inclusive_scan_sequential(input, output);
  auto t1 = getticks();

  // Verify result (should be [1, 2, 3, ..., n])
  bool correct = true;
  for (size_t i = 0; i < n; ++i) {
    if (output[i] != static_cast<int>(i + 1)) {
      correct = false;
      fmt::print(stderr, "error: at position {}: expected {}, got {}\n", i, i + 1, output[i]);
      break;
    }
  }
  if (!correct) {
    fmt::print(stderr, "error: implementation is incorrect\n");
    return -1;
  }

  double cycles_per_element = double(t1 - t0) / double(n);
  fmt::print("Array size:     {}\n", n);
  fmt::print("Elapsed cycles: {}\n", t1 - t0);
  fmt::print("Cycles/element: {}\n", cycles_per_element);

  return 0;
}
