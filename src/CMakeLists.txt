include_directories(${CMAKE_BINARY_DIR})

message(STATUS ${CMAKE_BINARY_DIR})

set(appMain
	main.cpp)

add_executable(mybookdb ${appMain})

find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIR})
target_link_libraries(mybookdb ${JPEG_LIBRARY})

install(TARGETS mybookdb DESTINATION bin)
