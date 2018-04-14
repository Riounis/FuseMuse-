cmake_minimum_required(VERSION 2.8.2)

#Make FuseMusepp library
find_package(nlohmann_json CONFIG REQUIRED)
add_library(fmpp STATIC shell.cpp)
set_target_properties(fmpp PROPERTIES LINKER_LANGUAGE CXX)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
