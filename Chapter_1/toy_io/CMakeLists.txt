cmake_minimum_required(VERSION 3.20.0)

add_library(toy_io toy_io.cpp)
target_include_directories(toy_io PUBLIC .)