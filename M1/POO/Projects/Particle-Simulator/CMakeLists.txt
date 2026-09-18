cmake_minimum_required(VERSION 3.15)
project(TP3 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(TBB REQUIRED)

enable_testing()

add_library(simulator_lib INTERFACE)
target_include_directories(simulator_lib INTERFACE include)
target_link_libraries(simulator_lib INTERFACE TBB::tbb)

add_executable(Myproject src/main.cpp)
target_link_libraries(Myproject simulator_lib Threads::Threads)

add_executable(test_runner tests/test.cpp)
target_link_libraries(test_runner simulator_lib GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_runner)
