cmake_minimum_required(VERSION 3.20.0)

add_library(toy_utilities toy_utilities.cpp)
target_include_directories(toy_utilities PUBLIC .)
