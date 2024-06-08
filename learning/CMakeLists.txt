cmake_minimum_required(VERSION 2.8)
project(learning)

cmake_policy(VERSION 2.8.1)

if(NOT DEFINED LIBRARY_OUTPUT_PATH)
    set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})
endif()

add_library(
    learning
    SHARED
    include/unitSimple.hh
)

set_target_properties(
    learning
    PROPERTIES LINKER_LANGUAGE
    CXX
)

