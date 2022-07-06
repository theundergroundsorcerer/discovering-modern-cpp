cmake_minimum_required(VERSION 3.20.0)

add_library(toy_file_io toy_file_io.cpp)
target_include_directories(toy_file_io PUBLIC .)