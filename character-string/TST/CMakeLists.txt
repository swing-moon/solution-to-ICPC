cmake_minimum_required(VERSION 3.12)
project(TST)

set(CMAKE_CXX_STANDARD 14)

add_executable(TST main.cpp cmake-build-debug/TST.h)