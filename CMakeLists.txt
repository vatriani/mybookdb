project(mybookdb)
cmake_minimum_required(VERSION 2.8.9)

# Configure section
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(FindGit)
if(GIT_FOUND)
	GIT_WC_INFO(${PROJECT_SOURCE_DIR} mybookdb)
	execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags
	OUTPUT_VARIABLE VERSION
	OUTPUT_STRIP_TRAILING_WHITESPACE)
	message("-- git project version: " ${VERSION})
endif()

configure_file(version.h.in ${CMAKE_BINARY_DIR}/version.h)

# add qt5 stuff
find_package(Qt5Core REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)

find_package(Qt5Widgets REQUIRED)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(${Qt5Widget_INCLUDES})
add_definitions(${Qt5Widget_DEFINITIONS})

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")
# end qt5 stuff

# adding subdirs for CMake

# Build our copy of QSqlLiteDriver.
# We do this because we can't guarantee that the driver shipped with Qt exposes the
# raw sqlite3_ functions required for FTS support. This way we know that those symbols
# exist at compile-time and that our code links to the same sqlite library as the
# Qt driver.
#add_subdirectory(lib/sqlite3)
#include_directories("lib/sqlite3")

add_subdirectory(lib/aws)
include_directories("lib/aws")

add_subdirectory(src)


find_package(Doxygen)
if(DOXYGEN_FOUND)
	add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} ../Doxyfile)
endif()
