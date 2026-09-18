#ifndef TOP_MOLDYN_EKIN_HPP
#define TOP_MOLDYN_EKIN_HPP

#include <cstdint>
#include <vector>

namespace md {

/// @brief Scale forces, update velocities and compute kinetic energy.
auto compute_kinetic_energy(int64_t n, std::vector<double>& f, std::vector<double>& vh, double half_hsq, double hsq)
  -> double;

} // namespace md

#endif // TOP_MOLDYN_EKIN_HPP
