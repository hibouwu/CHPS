#ifndef TOP_MOLDYN_MAXWELL_HPP
#define TOP_MOLDYN_MAXWELL_HPP

#include <cstdint>
#include <vector>

namespace md {

/// @brief Sample Maxwell distribution at temperature `t_ref`.
auto maxwell(int64_t n, std::vector<double>& vh, double h, double t_ref, double t_scale) -> void;

} // namespace md

#endif // TOP_MOLDYN_MAXWELL_HPP
