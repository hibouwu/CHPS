cmake_minimum_required(VERSION 3.15)
project(TP2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(GTest REQUIRED)

enable_testing()

add_library(simulator_lib src/simulator.cpp)

add_executable(Myproject src/main.cpp)
target_link_libraries(Myproject simulator_lib)

add_executable(test_runner tests/test.cpp)
target_link_libraries(test_runner simulator_lib GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_runner)
