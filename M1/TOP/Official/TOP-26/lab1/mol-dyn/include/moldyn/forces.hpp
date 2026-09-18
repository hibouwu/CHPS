#ifndef TOP_MOLDYN_FORCES_HPP
#define TOP_MOLDYN_FORCES_HPP

#include <cstdint>
#include <vector>

namespace md {

/// @brief Compute forces and accumulate the virial and the potential.
auto compute_forces(
  int64_t n, std::vector<double>& x, std::vector<double>& f, double side, double r_cutoff, double& e_pot, double& vir
) -> void;

} // namespace md

#endif // TOP_MOLDYN_FORCES_HPP
