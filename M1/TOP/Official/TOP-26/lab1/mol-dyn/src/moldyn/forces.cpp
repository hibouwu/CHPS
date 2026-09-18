#include <moldyn/forces.hpp>

#include <cstdint>
#include <vector>

namespace md {

auto compute_forces(
  int64_t n, std::vector<double>& x, std::vector<double>& f, double side, double r_cutoff, double& e_pot, double& vir
) -> void {
  int64_t n3 = 3 * n;
  e_pot      = 0.0;
  vir        = 0.0;

  for (int64_t i = 0; i < n3; i += 3) {
    // Zero force components on particle i
    double fxi = 0.0;
    double fyi = 0.0;
    double fzi = 0.0;

    // Loop over all particles with index > i
    for (int64_t j = i + 3; j < n3; j += 3) {
      // Compute distance between particles i and j allowing for wrap-around
      double xx = x[i] - x[j];
      double yy = x[i + 1] - x[j + 1];
      double zz = x[i + 2] - x[j + 2];

      if (xx < (-0.5 * side)) {
        xx += side;
      }
      if (xx > (0.5 * side)) {
        xx -= side;
      }
      if (yy < (-0.5 * side)) {
        yy += side;
      }
      if (yy > (0.5 * side)) {
        yy -= side;
      }
      if (zz < (-0.5 * side)) {
        zz += side;
      }
      if (zz > (0.5 * side)) {
        zz -= side;
      }

      double rd = xx * xx + yy * yy + zz * zz;

      // If distance is inside cutoff radius, compute forces and contributions
      // to potential energy and virial
      if (rd <= r_cutoff * r_cutoff) {
        double r_rd   = 1.0 / rd;
        double r_rd3  = r_rd * r_rd * r_rd;
        double r_rd4  = r_rd3 * r_rd;
        double r_r148 = r_rd4 * (r_rd3 - 0.5);

        e_pot += r_rd3 * (r_rd3 - 1.0);
        vir -= rd * r_r148;

        fxi += xx * r_r148;
        fyi += yy * r_r148;
        fzi += zz * r_r148;

        f[j] -= xx * r_r148;
        f[j + 1] -= yy * r_r148;
        f[j + 2] -= zz * r_r148;
      }
    }

    // Update forces on particle i
    f[i] += fxi;
    f[i + 1] += fyi;
    f[i + 2] += fzi;
  }
}

} // namespace md
