#include <moldyn/fcc.hpp>

#include <cstdint>
#include <vector>

namespace md {

auto fcc(int64_t n, double alpha, std::vector<double>& x) -> void {
  int64_t ijk = 0;
  for (int64_t lg = 0; lg < 2; ++lg) {
    for (int64_t i = 0; i < n; ++i) {
      for (int64_t j = 0; j < n; ++j) {
        for (int64_t k = 0; k < n; ++k) {
          x[ijk]     = double(i) * alpha + double(lg) * alpha * 0.5;
          x[ijk + 1] = double(j) * alpha + double(lg) * alpha * 0.5;
          x[ijk + 2] = double(k) * alpha;
          ijk += 3;
        }
      }
    }
  }

  for (int64_t lg = 1; lg < 3; ++lg) {
    for (int64_t i = 0; i < n; ++i) {
      for (int64_t j = 0; j < n; ++j) {
        for (int64_t k = 0; k < n; ++k) {
          x[ijk]     = double(i) * alpha + double(2 - lg) * alpha * 0.5;
          x[ijk + 1] = double(j) * alpha + double(lg - 1) * alpha * 0.5;
          x[ijk + 2] = double(k) * alpha + alpha * 0.5;
          ijk += 3;
        }
      }
    }
  }
}

} // namespace md
