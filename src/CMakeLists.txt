cmake_minimum_required(VERSION 2.8.2)

#Make FuseMusepp library
add_library(fmpp STATIC Chord.h CompositionMetrics.h Constants.h Note.h TimeSignature.h Utilities.h)
set_target_properties(fmpp PROPERTIES LINKER_LANGUAGE CXX)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
