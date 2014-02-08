include_directories(${CMAKE_BINARY_DIR})
message(STATUS ${CMAKE_BINARY_DIR})

# add qt5 stuff
find_package(Qt5Widgets REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})
# end qt5 stuff


# qt ui files
QT5_WRAP_UI(UIS_HDRS
	ui/mainwindow.ui
)


set(appMain
	main.cpp
	config.cpp

	ui/mainwindow.cpp
)


add_executable(mybookdb ${appMain} ${UIS_HDRS})

include(CheckCXXCompilerFlag)

find_package(Threads REQUIRED)
include_directories(${THREAD_INCLUDE_DIR})
target_link_libraries(mybookdb ${THREAD_LIBRARY})

find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIR})
target_link_libraries(mybookdb ${JPEG_LIBRARY})

qt5_use_modules(mybookdb Widgets)

#install(TARGETS mybookdb DESTINATION bin)
