#include <moldyn/avgvel.hpp>

#include <cmath>
#include <cstdint>
#include <vector>

namespace md {

auto compute_average_velocity(int64_t n, std::vector<double>& vh, double v_avg, double h, double& count) -> double {
  int64_t n3     = 3 * n;
  double v_avg_h = v_avg * h;
  double vel     = 0.0;

  count = 0.0;
  for (int64_t i = 0; i < n3; i += 3) {
    double sq = std::sqrt(vh[i] * vh[i] + vh[i + 1] * vh[i + 1] + vh[i + 2] * vh[i + 2]);
    if (sq > v_avg_h)
      count++;
    vel += sq;
  }

  return vel / h;
}

} // namespace md
