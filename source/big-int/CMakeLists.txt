# CMakeList.txt: проект CMake для big-int; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
# Добавьте источник в исполняемый файл этого проекта.

add_subdirectory("sources")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
