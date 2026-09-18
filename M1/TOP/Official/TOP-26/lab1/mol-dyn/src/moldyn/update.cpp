#include <moldyn/update.hpp>

#include <cstdint>
#include <vector>

namespace md {

auto update_particles(int64_t n, std::vector<double>& x, std::vector<double>& vh, std::vector<double>& f, double side)
  -> void {
  int64_t n3 = 3 * n;
  for (int64_t i = 0; i < n3; ++i) {
    x[i] += vh[i] + f[i];

    // Periodic boundary conditions
    if (x[i] < 0.0) {
      x[i] += side;
    }
    if (x[i] > side) {
      x[i] -= side;
    }

    // Partial velocity updates
    vh[i] += f[i];
    // Initialise forces for the next iteration
    f[i] = 0.0;
  }
}

} // namespace md
