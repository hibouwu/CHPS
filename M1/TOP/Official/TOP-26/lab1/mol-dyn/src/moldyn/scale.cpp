#include <moldyn/scale.hpp>

#include <cstdint>
#include <vector>

namespace md {

auto scale_velocities(int64_t n, double sa, std::vector<double>& sx) -> void {
  for (int64_t i = 0; i < n; ++i) {
    sx[i] *= sa;
  }
}

} // namespace md
