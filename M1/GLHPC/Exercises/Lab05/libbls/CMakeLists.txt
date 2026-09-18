cmake_minimum_required(VERSION 3.10)
project(bls C)

set(CMAKE_C_STANDARD 11)
set(COMMON_COMPILE_FLAGS
    $<$<CONFIG:Debug>:-Wall -Wextra -g3 -fno-omit-frame-pointer>
    $<$<CONFIG:Release>:-Wall -Wextra -O3 -march=native -funroll-loops -g3 -fno-omit-frame-pointer>
)

find_package(OpenMP REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter)
find_package(Python3 COMPONENTS Development)

if (NOT Python3_Development_FOUND)
    message(FATAL_ERROR "Python3 development package not found\n"
        "Ubuntu/Debian: sudo apt install python3-dev\n"
        "Fedora: sudo dnf install python3-devel\n")
endif()

# Find the numpy install and include directories
execute_process(
    COMMAND "${Python3_EXECUTABLE}" -c
            "import numpy; print(numpy.get_include())"
    OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_library(bls SHARED src/pybls.c src/bls.c include/bls.h)
target_compile_options(bls PRIVATE ${COMMON_COMPILE_FLAGS})
set_target_properties(bls PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(bls PRIVATE OpenMP::OpenMP_C Python3::Python)

target_include_directories(bls PRIVATE include 
    ${NUMPY_INCLUDE_DIR} ${Python3_INCLUDE_DIRS}
)

set_target_properties(bls PROPERTIES
    PREFIX ""
    SUFFIX ".so"
)

# We directly install at the root of the install folder
# Quite messy, but it will simplify the lab instructions
install(TARGETS bls
    LIBRARY DESTINATION .
)