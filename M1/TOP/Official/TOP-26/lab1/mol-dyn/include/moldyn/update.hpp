#ifndef TOP_MOLDYN_UPDATE_HPP
#define TOP_MOLDYN_UPDATE_HPP

#include <cstdint>
#include <vector>

namespace md {

/// @brief Move particles
auto update_particles(int64_t n, std::vector<double>& x, std::vector<double>& vh, std::vector<double>& f, double side)
  -> void;

} // namespace md

#endif // TOP_MOLDYN_UPDATE_HPP
