cmake_minimum_required (VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

project(ng)

set(NG_LIB_SRC
)

set(NG_TEST_SRC
test/ropto_test.cpp
)

include_directories(include)

add_executable(ngtest test/TestSuite.cpp ${NG_LIB_SRC} ${NG_TEST_SRC})

enable_testing()

add_test(NAME TEST COMMAND ngtest)