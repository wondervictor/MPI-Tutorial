cmake_minimum_required(VERSION 3.7)
project(Comm)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/local/include/)


set(SOURCE_FILES main.c main.c CommGroup.c)
add_executable(Comm ${SOURCE_FILES})