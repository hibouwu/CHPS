#ifndef TOP_MOLDYN_FCC_HPP
#define TOP_MOLDYN_FCC_HPP

#include <cstdint>
#include <vector>

namespace md {

/// @brief Generate FCC lattice for atoms inside the box.
auto fcc(int64_t n, double alpha, std::vector<double>& x) -> void;

} // namespace md

#endif // TOP_MOLDYN_FCC_HPP
