#ifndef TOP_MOLDYN_SCALE_HPP
#define TOP_MOLDYN_SCALE_HPP

#include <cstdint>
#include <vector>

namespace md {

/// @brief Scales an array.
auto scale_velocities(int64_t n, double sa, std::vector<double>& sx) -> void;

} // namespace md

#endif // TOP_MOLDYN_SCALE_HPP
