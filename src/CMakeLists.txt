# src/CMakeLists.txt

# collect source and header files inside the current directory
# a bit lazy to do this via 'globbing expressions' but hey...
file(GLOB_RECURSE src 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

# instruct CMake to build the binary
# oops, we need to add the sidelined main.cpp source file.
add_executable(speciome "${CMAKE_SOURCE_DIR}/main.cpp" ${src})

# place the binary into ./bin
set_target_properties(speciome PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<0:>)
