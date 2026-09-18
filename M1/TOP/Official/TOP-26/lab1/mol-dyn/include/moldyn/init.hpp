#ifndef TOP_MOLDYN_INIT_HPP
#define TOP_MOLDYN_INIT_HPP

#include <vector>

namespace md {

/// @brief Initializes a range to double precision scalar value.
auto init_forces(std::vector<double>& s, double fill_val) -> void;

} // namespace md

#endif // TOP_MOLDYN_INIT_HPP
