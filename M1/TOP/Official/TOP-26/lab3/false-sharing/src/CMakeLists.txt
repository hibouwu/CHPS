add_executable(top.false_sharing)
target_sources(top.false_sharing PRIVATE main.cpp)
target_compile_options(top.false_sharing PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(top.false_sharing PRIVATE fmt::fmt)
