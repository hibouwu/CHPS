find_package(OpenMP REQUIRED)

add_library(top.stream INTERFACE)
add_library(top::stream ALIAS top.stream)

target_sources(top.stream INTERFACE FILE_SET HEADERS BASE_DIRS ${CMAKE_SOURCE_DIR}/include FILES stream.hpp)
target_compile_options(
  top.stream
  INTERFACE -Wall -Wextra -Wconversion -march=native -O3 -g3
)
target_link_libraries(top.stream INTERFACE OpenMP::OpenMP_CXX)
