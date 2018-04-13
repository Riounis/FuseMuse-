cmake_minimum_required(VERSION 2.8.2)
project(FuseMusepp CXX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_BUILD_TYPE Debug)

# Enable automatic tests via CMake
# Probably will be removed - google test automatically discovers tests
enable_testing()

add_subdirectory(src)
add_subdirectory(src/libfm)
add_subdirectory(tests)

