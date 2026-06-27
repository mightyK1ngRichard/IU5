cmake_minimum_required(VERSION 3.23)
project(Practice)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Practice
        data.txt
        Header.h
        pract.cpp
        Source.cpp)
