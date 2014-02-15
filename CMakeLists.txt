project(mybookdb)
cmake_minimum_required(VERSION 2.8.9)

# Configure section
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(GetGitRevisionDescription)
git_describe(VERSION --tags --dirty=-dirty)

#parse the version information into pieces.
string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" VERSION_SHA1 "${VERSION}")
set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

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
# end qt5 stuff

# adding subdirs for CMake

# Build our copy of QSqlLiteDriver.
# We do this because we can't guarantee that the driver shipped with Qt exposes the
# raw sqlite3_ functions required for FTS support. This way we know that those symbols
# exist at compile-time and that our code links to the same sqlite library as the
# Qt driver.
#add_subdirectory(lib/qsqlite)
#include_directories("lib/qsqlite")

add_subdirectory(src)


find_package(Doxygen)
if(DOXYGEN_FOUND)
	add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} ../Doxyfile)
endif()

