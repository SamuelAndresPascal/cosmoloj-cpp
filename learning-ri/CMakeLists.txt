cmake_minimum_required(VERSION 2.8)
project(learning-ri)

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
    ../learning/include
)


file(
    GLOB
    source_files
    src/*
)

add_library(
    learning-ri
    SHARED
    ${source_files}
)

add_executable(
    learning-ri-demo
    demo/unit-simple-ri-demo.cc
)

target_link_libraries(
    learning-ri-demo
    learning-ri
)

add_executable(
    polymorphysm-demo
    demo/polymorphysm-demo.cc
)

target_link_libraries(
    polymorphysm-demo
    learning-ri
)

add_executable(
    test
    test/unit-test.cc
    test/unit-operators-test.cc
    test/test.cc
)

target_link_libraries(
    test
    learning-ri
    cppunit
)




