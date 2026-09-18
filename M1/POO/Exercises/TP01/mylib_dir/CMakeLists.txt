# CMakeLists.txt for mylib library

# Create the mylib library
add_library(mylib SHARED MyClass.cpp)

# Add alias for namespaced use
add_library(my_lib::mylib ALIAS mylib)

# Specify the include directories for this library
target_include_directories(mylib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(mylib PRIVATE -fvisibility=hidden)
target_compile_definitions(mylib PRIVATE MYLIB_BUILD)

# Set target properties
set_target_properties(mylib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    EXPORT_NAME mylib
)

# Install the library
install(TARGETS mylib
    EXPORT my_libTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Install headers
install(FILES MyClass.h
    DESTINATION include
)
