cmake_minimum_required(VERSION 3.25)
project(top.false_sharing LANGUAGES CXX)

find_package(OpenMP REQUIRED)

include(FetchContent)
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt GIT_TAG 11.1.4)
FetchContent_MakeAvailable(fmt)

add_subdirectory(src)
