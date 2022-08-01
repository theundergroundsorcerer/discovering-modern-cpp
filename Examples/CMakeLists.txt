cmake_minimum_required(VERSION 3.20.0)
if(NOT WITH_PRINT_FUNCTION_MESSAGES)
add_subdirectory(Chapter01)
else()
    message("Not adding Chapter01")
endif()

add_subdirectory(Chapter02Update)
add_subdirectory(Chapter02)