#include <moldyn/ekin.hpp>

#include <cstdint>
#include <vector>

namespace md {

auto compute_kinetic_energy(int64_t n, std::vector<double>& f, std::vector<double>& vh, double half_hsq, double hsq)
  -> double {
  int64_t n3 = 3 * n;
  double sum = 0.0;
  for (int64_t i = 0; i < n3; ++i) {
    f[i] *= half_hsq;
    vh[i] += f[i];
    sum += vh[i] * vh[i];
  }
  return sum / hsq;
}

} // namespace md
