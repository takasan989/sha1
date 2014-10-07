cmake_minimum_required (VERSION 2.6)
project (sha1-test)

include_directories (~/usr/include)
link_directories (~/usr/lib)

add_executable (alltest test.cc)

target_link_libraries (alltest
  pthread
  gtest
  gtest_main

  sha1)
