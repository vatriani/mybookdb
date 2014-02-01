project(mybookdb)
cmake_minimum_required(VERSION 2.8)

# Configure section

set(V_MAJOR 0)
set(V_MINOR 1)
set(V_PATCH 0)

find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIR})

configure_file(config.h.in ${CMAKE_BINARY_DIR}/config.h)

# adding subdirs for CMake

#add_subdirectory(lib)
add_subdirectory(src)
