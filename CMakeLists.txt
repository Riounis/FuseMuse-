cmake_minimum_required(VERSION 2.8.2)
project(FuseMusepp CXX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

# Enable automatic tests via CMake
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

