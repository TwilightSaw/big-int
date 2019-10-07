# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)

project ("big-int")

# Включите подпроекты.
add_subdirectory ("big-int")
add_executable (big-int "big-int.cpp")