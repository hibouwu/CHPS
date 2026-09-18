#include <moldyn/init.hpp>

#include <vector>

namespace md {

auto init_forces(std::vector<double>& s, double fill_val) -> void {
  for (auto& e : s) {
    e = fill_val;
  }
}

} // namespace md
