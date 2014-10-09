
include_directories (~/usr/include)
link_directories (~/usr/lib)

set (TEST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/test.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/test.h")
  
include_directories ("${CMAKE_CURRENT_BINARY_DIR}")

add_executable (run_alltest test.cc)

target_link_libraries (run_alltest
  pthread
  gtest
  gtest_main

  sha1)
