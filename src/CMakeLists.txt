cmake_minimum_required(VERSION 2.8.2)

#Make FuseMusepp library
add_library(fmpp STATIC chord.h composition_metrics.h constants.h note.h utilities.h dynamics.h)
set_target_properties(fmpp PROPERTIES LINKER_LANGUAGE CXX)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
