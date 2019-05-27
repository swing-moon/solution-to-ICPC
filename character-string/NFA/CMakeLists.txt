cmake_minimum_required(VERSION 3.12)
project(NFA)

set(CMAKE_CXX_STANDARD 14)

add_executable(NFA main.cpp cmake-build-debug/Digraph.h cmake-build-debug/DirectedDFS.h cmake-build-debug/NFA.h)