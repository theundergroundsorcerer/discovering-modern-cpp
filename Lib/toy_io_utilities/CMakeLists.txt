cmake_minimum_required(VERSION 3.20.0)

add_library(toy_io_utilities toy_io_utilities.cpp)
target_include_directories(toy_io_utilities PUBLIC .)
