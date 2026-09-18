cmake_minimum_required(VERSION 3.15)
project(piestimator VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find OpenMP
find_package(OpenMP REQUIRED)

# Add executable
add_executable(piestimator
    src/main.c
    src/compute_pi.c
)

# Include directories
target_include_directories(piestimator PRIVATE src)

# Link libraries
target_link_libraries(piestimator 
    m 
    rt
    OpenMP::OpenMP_C
)

# Set compiler flags
target_compile_options(piestimator PRIVATE 
    -Wall 
    -Wextra 
    -O3
    -fopenmp
)



