cmake_minimum_required(VERSION 3.20.0)

add_executable(file_io_demo file_io_demo.cpp)
target_link_libraries(file_io_demo PRIVATE toy_io)

add_executable(generic_stream_demo generic_stream_demo.cpp)
target_link_libraries(generic_stream_demo toy_io)

add_executable(formatting_demo formatting_demo.cpp)
add_executable(io_error_handling_demo io_error_handling_demo.cpp)
add_executable(io_exceptions_demo io_exceptions_demo.cpp)
add_executable(filesystem_demo filesystem_demo.cpp)

# need to install fmt first
if(fmt_FOUND)
    add_executable(new_formatting_demo new_formatting_demo.cpp)
endif()