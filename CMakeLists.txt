cmake_minimum_required(VERSION 2.6)
project(schemese)

find_package(FLEX)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11 -stdlib=libc++")
add_subdirectory(vendor/googletest)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

flex_target(scanner_definitions
    lib/scanner_definitions.l
    ${CMAKE_BINARY_DIR}/scanner.l.cc)

add_executable(token_test
  test/token_test.cc
  lib/token.cc)

target_link_libraries(token_test ${CORELIBS} gtest gtest_main)
add_test(token_test ${CMAKE_BINARY_DIR}/token_test)

add_executable(scanner_test
  ${FLEX_scanner_definitions_OUTPUTS}
  lib/scanner.cc
  lib/token.cc
  test/scanner_test.cc)

target_link_libraries(scanner_test ${CORELIBS} gtest gtest_main)
add_test(scanner_test ${CMAKE_BINARY_DIR}/scanner_test)
