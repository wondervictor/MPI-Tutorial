cmake_minimum_required(VERSION 3.7)
project(MatrixAlgorithms)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        MatConv.c
        MatMultiply.c GenMat.c GenMat.h)

add_executable(MatrixAlgorithms ${SOURCE_FILES})