cmake_minimum_required(VERSION 3.25)

project(top.branch-predict)

include(FetchContent)
FetchContent_Declare(nanobench GIT_REPOSITORY https://github.com/martinus/nanobench.git GIT_TAG master GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(nanobench)

add_executable(top.branch-predict)
target_sources(top.branch-predict PRIVATE branch_predict.cpp)
target_compile_features(top.branch-predict PRIVATE cxx_std_20)
target_compile_options(top.branch-predict PRIVATE -O2 -fno-if-conversion -fno-tree-dominator-opts)
target_link_libraries(top.branch-predict PRIVATE nanobench)
