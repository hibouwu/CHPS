target_sources(top.lbm-exe PRIVATE main.cpp)
target_link_libraries(top.lbm-exe PRIVATE top::lbm-lib MPI::MPI_CXX OpenMP::OpenMP_CXX)
set_target_properties(top.lbm-exe PROPERTIES BUILD_RPATH ${CMAKE_BINARY_DIR}/lib)

target_sources(top.display PRIVATE display.cpp)
target_link_libraries(top.display PRIVATE top::lbm-lib)
set_target_properties(top.display PROPERTIES BUILD_RPATH ${CMAKE_BINARY_DIR}/lib)
