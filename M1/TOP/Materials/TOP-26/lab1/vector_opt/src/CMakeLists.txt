# Exo 1.2
add_library(vector INTERFACE)

target_sources(
  vector
  INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ../include
    FILES ../include/vector/vector.hpp
)

add_executable(main)

# Exo 2. ----------------------------------
target_compile_options(main PRIVATE -Wall -Wextra -Werror)
# ----------------------------------

set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_sources(main PRIVATE main.cpp)
target_link_libraries(main PRIVATE vector fmt::fmt)
