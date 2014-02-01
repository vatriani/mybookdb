include_directories(${CMAKE_BINARY_DIR})

message(STATUS ${CMAKE_BINARY_DIR})

set(appMain
	main.cpp)

add_executable(mybookdb ${appMain})

install(TARGETS mybookdb DESTINATION bin)
