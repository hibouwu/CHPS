add_library(top.prng.compile_flags INTERFACE)

target_compile_options(
  top.prng.compile_flags
  INTERFACE -Wall -Wextra -Wpedantic -Wconversion -Wcast-align
)
target_compile_features(top.prng.compile_flags INTERFACE c_std_23)
set_target_properties(top.prng.compile_flags PROPERTIES C_EXTENSIONS OFF)

add_library(top.prng STATIC)
add_library(top::prng ALIAS top.prng)

target_sources(
  top.prng
  PRIVATE prng.c
  PUBLIC
    FILE_SET prng_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_SOURCE_DIR}/include
    FILES ${CMAKE_SOURCE_DIR}/include/prng/prng.h
)
target_link_libraries(top.prng INTERFACE top.prng.compile_flags)
