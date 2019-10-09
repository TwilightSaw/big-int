cmake_minimum_required (VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)

project ("big-int")

add_subdirectory ("big-int")
add_executable (big-int "big-int.cpp")