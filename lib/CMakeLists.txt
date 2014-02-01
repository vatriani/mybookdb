set(libSrc
	libsettings.h)

add_library(libary SHARED ${libSrc})
install(TARGETS libary DESTINATION lib)
