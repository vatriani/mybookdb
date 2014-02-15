include_directories(${CMAKE_BINARY_DIR})
message(STATUS ${CMAKE_BINARY_DIR})

# qt ui files
QT5_WRAP_UI(UIS_HDRS
	ui/mainwindow.ui
	ui/overview.ui
	ui/bookdescription.ui
	ui/toolbargroups.ui
)


set(appMain
	main.cpp
	library.cpp
	ui/mainwindow.cpp
	ui/overview.cpp
	ui/bookdescription.cpp
	ui/toolbargroups.cpp
	entry.cpp
)

qt5_add_resources(RES_OUT ../res/ressources.qrc)


add_executable(mybookdb ${appMain} ${UIS_HDRS} qrc_ressources.cpp)

include(CheckCXXCompilerFlag)

find_package(Threads REQUIRED)
include_directories(${THREAD_INCLUDE_DIR})
target_link_libraries(mybookdb ${THREAD_LIBRARY})

qt5_use_modules(mybookdb Widgets Sql)

install(TARGETS mybookdb DESTINATION bin)
