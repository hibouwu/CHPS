add_executable(top.mesh)
target_sources(top.mesh PRIVATE main.cpp)
target_compile_options(top.mesh PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
target_link_libraries(top.mesh OpenMP::OpenMP_CXX fmt::fmt)
