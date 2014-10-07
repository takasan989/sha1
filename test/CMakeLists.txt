cmake_minimum_required (VERSION 2.6)
project (sha1-test)

include_directories (~/usr/include)
link_directories (~/usr/lib)

add_executable (run_alltest test.cc)

target_link_libraries (run_alltest
  pthread
  gtest
  gtest_main

  sha1)
