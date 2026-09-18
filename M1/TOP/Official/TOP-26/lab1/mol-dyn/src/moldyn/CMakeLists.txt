add_library(top.moldyn.compile_flags INTERFACE)

target_compile_options(
  top.moldyn.compile_flags
  INTERFACE -Wall -Wextra -Wpedantic -Wconversion -Wcast-align
)
target_compile_features(top.moldyn.compile_flags INTERFACE cxx_std_23)
set_target_properties(top.moldyn.compile_flags PROPERTIES CXX_EXTENSIONS OFF)

add_library(top.moldyn STATIC)
add_library(top::moldyn ALIAS top.moldyn)

target_sources(
  top.moldyn
  PRIVATE avgvel.cpp ekin.cpp fcc.cpp forces.cpp init.cpp maxwell.cpp scale.cpp update.cpp
  PUBLIC
    FILE_SET moldyn_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_SOURCE_DIR}/include
    FILES
      ${CMAKE_SOURCE_DIR}/include/moldyn/avgvel.hpp
      ${CMAKE_SOURCE_DIR}/include/moldyn/ekin.hpp
      ${CMAKE_SOURCE_DIR}/include/moldyn/fcc.hpp
      ${CMAKE_SOURCE_DIR}/include/moldyn/forces.hpp
      ${CMAKE_SOURCE_DIR}/include/moldyn/init.hpp
      ${CMAKE_SOURCE_DIR}/include/moldyn/maxwell.hpp
      ${CMAKE_SOURCE_DIR}/include/moldyn/scale.hpp
      ${CMAKE_SOURCE_DIR}/include/moldyn/update.hpp
)
target_include_directories(top.moldyn PRIVATE ${CMAKE_SOURCE_DIR}/include/prng)
target_link_libraries(top.moldyn INTERFACE top.moldyn.compile_flags)
target_link_libraries(top.moldyn PUBLIC top::prng)
