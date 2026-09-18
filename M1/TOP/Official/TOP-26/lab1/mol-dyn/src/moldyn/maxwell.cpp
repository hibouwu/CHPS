#include <moldyn/maxwell.hpp>

#include <cmath>
#include <cstdint>
#include <vector>

extern "C" {
#include <prng/prng.h>
}

namespace md {

auto maxwell(int64_t n, std::vector<double>& vh, double h, double t_ref, double t_scale) -> void {
  int64_t n3 = 3 * n;

  // Set a seed and pick the range of numbers to generate
  prng_seed(0.0, 1.0);
  for (int64_t i = 0; i < n3; i += 2) {
    double s = 2.0;
    double v1, v2;
    while (s >= 1.0) {
      v1 = 2.0 * prng_random() - 1.0;
      v2 = 2.0 * prng_random() - 1.0;
      s  = v1 * v1 + v2 * v2;
    }
    double r  = std::sqrt(-2.0 * std::log(s) / s);
    vh[i]     = v1 * r;
    vh[i + 1] = v2 * r;
  }

  double sp    = 0.0;
  double e_kin = 0.0;
  for (int64_t i = 0; i < n3; i += 3) {
    sp += vh[i];
  }
  sp /= double(n);
  for (int64_t i = 0; i < n3; i += 3) {
    vh[i] -= sp;
    e_kin += vh[i] * vh[i];
  }

  sp = 0.0;
  for (int64_t i = 1; i < n3; i += 3) {
    sp += vh[i];
  }
  sp /= double(n);
  for (int64_t i = 1; i < n3; i += 3) {
    vh[i] -= sp;
    e_kin += vh[i] * vh[i];
  }

  sp = 0.0;
  for (int64_t i = 2; i < n3; i += 3) {
    sp += vh[i];
  }
  sp /= double(n);
  for (int64_t i = 2; i < n3; i += 3) {
    vh[i] -= sp;
    e_kin += vh[i] * vh[i];
  }

  double sc = h * std::sqrt(t_ref / (t_scale * e_kin));
  for (int64_t i = 0; i < n3; ++i) {
    vh[i] *= sc;
  }
}

} // namespace md
