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
    include/*
    src/*
)

add_library(
    learning-ri
    SHARED
    ${source_files}
)

add_executable(
    unit-simple-ri-demo
    demo/unit-simple-ri-demo.cc
)

target_link_libraries(
    unit-simple-ri-demo
    learning-ri
)

add_executable(
    polymorphism-demo
    demo/polymorphism-demo.cc
)

target_link_libraries(
    polymorphism-demo
    learning-ri
)

add_executable(
    array-demo
    demo/array-demo.cc
)

add_executable(
    su-test
    test/unit-test.cc
    test/unit-operators-test.cc
    test/test.cc
)

target_link_libraries(
    su-test
    learning-ri
    cppunit
)

enable_testing()

add_test(NAME su-test COMMAND su-test)

set_tests_properties(
    su-test
    PROPERTIES PASS_REGULAR_EXPRESSION "OK"
)




