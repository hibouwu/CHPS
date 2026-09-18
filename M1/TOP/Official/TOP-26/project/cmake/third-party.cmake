# Third-party integration configuration
# This module provides platform-specific optimizations from external sources

configure_file("${CMAKE_SOURCE_DIR}/cmake/tpl.hpp.in" "${CMAKE_BINARY_DIR}/include/lbm/tpl.hpp" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/cmake/tpl_loader.hpp.in" "${CMAKE_BINARY_DIR}/include/lbm/tpl_loader.hpp" @ONLY)
