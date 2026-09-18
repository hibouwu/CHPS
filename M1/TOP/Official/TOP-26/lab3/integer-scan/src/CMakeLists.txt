add_executable(top.integer_scan)
target_sources(top.integer_scan PRIVATE main.cpp)
target_compile_options(top.integer_scan PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(top.integer_scan PRIVATE fmt::fmt)
