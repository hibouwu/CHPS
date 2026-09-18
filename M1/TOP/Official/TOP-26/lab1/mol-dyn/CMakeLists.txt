cmake_minimum_required(VERSION 3.25)

project(mol-dyn LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt GIT_TAG 11.1.4)
FetchContent_MakeAvailable(fmt)

add_subdirectory(src/prng)
add_subdirectory(src/moldyn)
add_subdirectory(src/bin)
