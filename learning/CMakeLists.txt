cmake_minimum_required(VERSION 3.22)
project(learning)

cmake_policy(VERSION 3.22)

set(CMAKE_CXX_STANDARD CACHE STRING "cxx standard")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED LIBRARY_OUTPUT_PATH)
    set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})
endif()

add_library(
    learning
    SHARED
    include/unitSimple.hh
    include/polymorphism.hh
    include/stats.hh
)

set_target_properties(
    learning
    PROPERTIES LINKER_LANGUAGE
    CXX
)

