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
	src
	/usr/include/cppunit
)


file(
	GLOB
	source_files
	include/*
	src/*
)

add_library(
	cosmoloj-cpp
	SHARED
	${source_files}
)

add_executable(
  cosmoloj-cpp-test
  src/cosmoloj-cpp-test.cc
)

target_link_libraries(
  cosmoloj-cpp-test
  cosmoloj-cpp
)

add_executable(
  test
  test/unit-test.cc
  test/test.cc
)

target_link_libraries(
  test
  cosmoloj-cpp
  cppunit
)




