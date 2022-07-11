cmake_minimum_required(VERSION 3.20.0)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed")
endif()

project(DisoveringModernCPP CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Check whether fmt library is installed - must be installed for project to work
find_package(fmt)
if(fmt_FOUND)
    link_libraries(fmt::fmt-header-only)
else()
    message(WARNING "Could not find fmt library\n"
            "Please install fmt library first or pass the appropriate flags while building the project\n"
            "Some examples may not build")
endif()

add_subdirectory(Chapter_1)