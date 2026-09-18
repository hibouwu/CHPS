cmake_minimum_required(VERSION 3.25...4.2)

project(
  top.lbm
  LANGUAGES CXX
  VERSION 0.1.0
  DESCRIPTION "Hybrid MPI+OpenMP parallel D2Q9 lattice Boltzmann solver for Kármán vortex street flow"
  HOMEPAGE_URL "https://dssgabriel.github.io/CHP203-TOP/project"
)

find_package(MPI 3.0 REQUIRED)
find_package(OpenMP 4.0 REQUIRED)
include(cmake/third-party.cmake)

add_library(top.lbm-lib SHARED)
add_executable(top.lbm-exe)
add_executable(top.display)

add_subdirectory(src/lbm)
add_subdirectory(src/bin)
