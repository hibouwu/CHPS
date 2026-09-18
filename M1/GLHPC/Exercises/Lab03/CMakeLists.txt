cmake_minimum_required(VERSION 3.15)
project(parser VERSION 1.0.0 LANGUAGES C)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

include(CodeCoverage)

add_library(parser SHARED src/parser.c)
add_executable(mytransform src/main.c src/transformation.c src/image.c)

target_link_libraries(mytransform PRIVATE parser m)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(COMMON_COMPILE_FLAGS
    $<$<CONFIG:Debug>:-Wall -Wextra -g>
    $<$<CONFIG:Release>:-Wall -Wextra -O3 -DNDEBUG>
)

target_compile_options(parser PRIVATE ${COMMON_COMPILE_FLAGS})
target_compile_options(mytransform PRIVATE ${COMMON_COMPILE_FLAGS})

target_include_directories(parser 
    PUBLIC 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_include_directories(mytransform PRIVATE ${PROJECT_SOURCE_DIR}/src)

set_target_properties(parser PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

include(GNUInstallDirs)

install(TARGETS parser
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS mytransform
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Fetch and build the Unity testing framework
include(FetchContent)
FetchContent_Declare(
    unity
    GIT_REPOSITORY  https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG         v2.6.1
    GIT_SHALLOW true)

# Use the modern API instead of deprecated FetchContent_Populate
FetchContent_MakeAvailable(unity)

# Make Unity available but don't add to ALL target by default
# This is important to avoid installing unity dependencies which are only needed for testing 
# but are not required in the release version of the project
FetchContent_GetProperties(unity)
if(NOT unity_POPULATED)
    FetchContent_Populate(unity)
    add_subdirectory(${unity_SOURCE_DIR} ${unity_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(test_runner 
    tests/test_runner.c 
    tests/test_image.c 
    tests/test_transformation.c 
    src/transformation.c 
    src/image.c
)

target_include_directories(test_runner 
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/include
)

append_coverage_compiler_flags_to_target(test_runner)

target_link_libraries(test_runner PRIVATE unity m parser)

add_custom_target(test 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running unit tests..."
)

setup_target_for_coverage_gcovr_html(
    NAME coverage
    EXECUTABLE test_runner
    DEPENDENCIES test_runner
    BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
    EXCLUDE "tests/*" "CMakeFiles/*" "build/*" "_deps/*"
)