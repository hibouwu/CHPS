add_executable(top.stream_main)

target_sources(top.stream_main PRIVATE main.cpp)
target_compile_options(
  top.stream
  INTERFACE -Wall -Wextra -Wconversion -march=native -O3 -g3
)
target_include_directories(top.stream_main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(top.stream_main PRIVATE top::stream fmt::fmt)
