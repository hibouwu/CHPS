#include <chrono>
#include <ratio>
#include <thread>
#include <vector>

#include <fmt/core.h>

constexpr int NUM_THREADS = 8;
constexpr int ITERATIONS  = 100'000'000;

// Array of counters - one per thread
int counters[NUM_THREADS];

auto increment_counter(int thread_id) -> void {
  for (int i = 0; i < ITERATIONS; ++i) {
    counters[thread_id]++;
  }
}

auto main() -> int {
  std::vector<std::thread> threads;

  auto t0 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < NUM_THREADS; ++i) {
    threads.push_back(std::thread(increment_counter, i));
  }
  for (auto& t : threads) {
    t.join();
  }
  auto t1      = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration<double, std::micro>(t1 - t0);

  // Verify results
  int total = 0;
  for (int i = 0; i < NUM_THREADS; ++i) {
    total += counters[i];
  }

  fmt::print("Execution time: {:9.3} us\n", elapsed.count());
  fmt::print("Total count:    {} (expected: {})\n", total, NUM_THREADS * ITERATIONS);

  return 0;
}
