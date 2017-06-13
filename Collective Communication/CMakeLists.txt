cmake_minimum_required(VERSION 3.7)
project(Collective_Communication)

set(CMAKE_CXX_STANDARD 11)



set(SOURCE_FILES
        allgather.c
        allreduce.c
        bcast.c
        gather.c
        reduce.c
        scatter.c)

add_executable(Collective_Communication ${SOURCE_FILES})