cmake_minimum_required(VERSION 3.22)
project(simple-unit)

cmake_policy(VERSION 3.22)

set(CMAKE_CXX_STANDARD CACHE STRING "cxx standard")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED LIBRARY_OUTPUT_PATH)
    set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})
endif()

add_library(
    simple-unit
    SHARED
    include/unitSimple.hh
)

set_target_properties(
    simple-unit
    PROPERTIES LINKER_LANGUAGE
    CXX
)
