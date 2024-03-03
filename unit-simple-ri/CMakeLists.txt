cmake_minimum_required(VERSION 2.8)
project(simple-unit-ri)

cmake_policy(VERSION 2.8.1)


if(NOT DEFINED EXECUTABLE_OUTPUT_PATH)
    set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
endif()

if(NOT DEFINED LIBRARY_OUTPUT_PATH)
    set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})
endif()


include_directories(
    include
    /usr/include/cppunit
    ../unit-simple/include
)


file(
    GLOB
    source_files
    src/*
)

add_library(
    unit-simple-ri
    SHARED
    ${source_files}
)

add_executable(
    unit-simple-ri-test
    src/unit-simple-ri-test.cc
)

target_link_libraries(
    unit-simple-ri-test
    unit-simple-ri
)

add_executable(
    test
    test/unit-test.cc
    test/unit-operators-test.cc
    test/test.cc
)

target_link_libraries(
    test
    unit-simple-ri
    cppunit
)




