project(mybookdb)
cmake_minimum_required(VERSION 2.8)

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

# adding subdirs for CMake

#add_subdirectory(lib)
add_subdirectory(src)


find_package(Doxygen)
if(DOXYGEN_FOUND)
	add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} ../Doxyfile)
endif()

