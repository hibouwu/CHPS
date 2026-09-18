#ifndef TOP_MOLDYN_AVGVEL_HPP
#define TOP_MOLDYN_AVGVEL_HPP

#include <cstdint>
#include <vector>

namespace md {

/// @brief Compute average velocity.
auto compute_average_velocity(int64_t n, std::vector<double>& vh, double v_avg, double h, double& count) -> double;

} // namespace md

#endif // TOP_MOLDYN_AVGVEL_HPP
