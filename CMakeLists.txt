cmake_minimum_required(VERSION 3.25)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

set(optimizations "-Ofast")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${optimizations}")

add_executable(Lab1 main.cpp task1.h task2.h
        task4.h
        task3.h
        task6.h)
