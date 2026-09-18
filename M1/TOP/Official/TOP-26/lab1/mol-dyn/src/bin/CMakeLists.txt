add_library(top.moldyn_main.compile_flags INTERFACE)

target_compile_options(
  top.moldyn_main.compile_flags
  INTERFACE -Wall -Wextra -Wpedantic -Wconversion -Wcast-align
)
target_compile_features(top.moldyn_main.compile_flags INTERFACE cxx_std_23)
set_target_properties(top.moldyn_main.compile_flags PROPERTIES CXX_EXTENSIONS OFF)

add_executable(top.moldyn_main)

target_sources(top.moldyn_main PRIVATE main.cpp)
target_link_libraries(top.moldyn_main INTERFACE top.moldyn_main.compile_flags)
target_link_libraries(top.moldyn_main PRIVATE top::moldyn fmt::fmt)
