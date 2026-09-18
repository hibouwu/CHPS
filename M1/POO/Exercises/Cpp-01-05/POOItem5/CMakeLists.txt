cmake_minimum_required(VERSION 3.15)
project(reviser VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(reviser src/toutReviser.cpp)
