cmake_minimum_required (VERSION 2.6)
project (sha1)

include_directories (".")

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

add_library (sha1 sha1.cc)

add_subdirectory(test)
