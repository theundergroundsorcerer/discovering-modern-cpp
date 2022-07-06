cmake_minimum_required(VERSION 3.20.0)

add_subdirectory(toy_file_io)

add_executable(file_io_demo file_io_demo.cpp)
target_link_libraries(file_io_demo PRIVATE toy_file_io)

add_executable(generic_stream_demo generic_stream_demo.cpp)
target_link_libraries(generic_stream_demo toy_file_io)
