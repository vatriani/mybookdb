include_directories(${CMAKE_BINARY_DIR})
message(STATUS ${CMAKE_BINARY_DIR})

# qt ui files
QT5_WRAP_UI(UIS_HDRS
	ui/mainwindow.ui
	ui/overview.ui
	ui/bookdescription.ui
)


set(appMain
	library.cpp
	isbn.cpp
	networkscanner.cpp
	amazonsearch.cpp
	imagestore.cpp
	uihelpers.cpp
	ui/groupboxcollapse.cpp
	ui/ratingbar.cpp
	ui/fieldmanager.cpp
	ui/overview.cpp
	ui/bookdescription.cpp
	ui/mainwindow.cpp
	main.cpp
)

qt5_add_resources(RES_OUT ../res/ressources.qrc)


add_executable(mybookdb ${appMain} ${UIS_HDRS} qrc_ressources.cpp)

include(CheckCXXCompilerFlag)

find_package(Threads REQUIRED)
include_directories(${THREAD_INCLUDE_DIR})
target_link_libraries(mybookdb ${THREAD_LIBRARY})

find_package(Sqlite3 REQUIRED)
include_directories(${SQLITE3_INCLUDE_DIR})
target_link_libraries(mybookdb ${SQLITE3_LIBRARIES})

target_link_libraries(mybookdb)

qt5_use_modules(mybookdb Widgets Network)

install(TARGETS mybookdb DESTINATION bin)
