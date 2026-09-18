cmake_minimum_required(VERSION 3.10)
project(my_lib VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_subdirectory(mylib_dir)
# create main executable
add_executable(main src/main.cpp)
target_link_libraries(main mylib)

# create test executable
add_executable(test_runner tests/test.cpp)

target_link_libraries(test_runner GTest::GTest GTest::Main mylib)

# include directories for the executable
target_include_directories(main PRIVATE mylib_dir)
target_include_directories(test_runner PRIVATE mylib_dir)

# enable testing
enable_testing()

add_test(NAME RunMain COMMAND main)
gtest_discover_tests(test_runner)

target_compile_options(main PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
        -fvisibility=hidden
)

# Install configuration
include(CMakePackageConfigHelpers)

# Install the targets export
install(EXPORT my_libTargets
    FILE my_libTargets.cmake
    NAMESPACE my_lib::
    DESTINATION lib/cmake/my_lib
)

# Configure package config file
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/my_libConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/my_libConfig.cmake
    INSTALL_DESTINATION lib/cmake/my_lib
)

# Write version file
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/my_libConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install config files
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/my_libConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/my_libConfigVersion.cmake
    DESTINATION lib/cmake/my_lib
)
