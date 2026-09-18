#include <array>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <functional>
#include <numeric>
#include <vector>

#include <fmt/core.h>
#include <stream/stream.hpp>

constexpr size_t ONE_MIB   = 134'217'728;
constexpr size_t N_SAMPLES = 11;

namespace utils {

auto mean(std::array<double, N_SAMPLES> const& samples) -> double {
  return std::accumulate(samples.begin(), samples.end(), 0.0) / double(N_SAMPLES);
}

auto standard_deviation(std::array<double, N_SAMPLES> const& samples, double mean) {
  double tmp = 0.0;
  std::for_each(samples.begin(), samples.end(), [&](auto e) { tmp += (e - mean) * (e - mean); });
  tmp /= double(N_SAMPLES - 1);
  return std::sqrt(tmp) * 100.0 / mean;
}

} // namespace utils

template <typename Fn, typename... Args>
auto benchmark(std::string const& name, Fn fn, Args&&... args) -> void {
  std::array<double, N_SAMPLES> epochs;

  for (size_t it = 0; it < N_SAMPLES; ++it) {
    // auto t0 = ...?;
    for (size_t rep = 0; rep < 100; ++rep) {
      std::invoke(fn, std::forward<Args>(args)...);
    }
    // auto t1 = ...?;
    // epochs[it] = ...?;
  }

  double mean = utils::mean(epochs);
  double sdev = utils::standard_deviation(epochs, mean);
  fmt::print("{:>16} {:9.3} {:<10} +/- {:4.2}%\n", name, mean, "...?", sdev);
}

auto main(int argc, char* argv[]) -> int {
  size_t size = ONE_MIB / sizeof(double);
  if (argc == 2) {
    size = size_t(std::atoi(argv[1]));
  }

  std::vector<double> a(size);
  std::vector<double> b(size);
  std::vector<double> c(size);

  stream::init(a, 1.0);
  stream::init(b, 1.0);
  stream::init(c, 0.0);

  stream::copy(c, a);
  benchmark("stream::mul", [&]() { stream::mul(b, 2.0, c); });
  stream::add(a, b, c);
  benchmark("stream::triad", [&]() { stream::triad(c, 0.5, a, b); });
  [[maybe_unused]] auto _ = stream::dot(a, b);

  return 0;
}
