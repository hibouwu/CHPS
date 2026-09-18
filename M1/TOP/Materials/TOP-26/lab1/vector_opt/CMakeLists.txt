# Exo 1.2
cmake_minimum_required(VERSION 3.25...4.2)

project(top-lab1-vector-opt LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 12.1.0
)
FetchContent_MakeAvailable(fmt)

add_subdirectory(src)

# cmake -G Ninja -B build
# cmake --build build

# Exo 2.1