cmake_minimum_required(VERSION 3.26)
project(teset)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(teset
        include/CImg.h
        src/main.cpp)
