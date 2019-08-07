cmake_minimum_required(VERSION 3.0)

project( GEOENGINE_LIB  VERSION 1.0 )

#添加头文件

file( GLOB header_list *.h)
file( GLOB source_list *.cpp)

add_library( ${PROJECT_NAME} SHARED ${header_list} ${source_list})

# Qt
qt5_use_modules(${PROJECT_NAME} Core Gui Widgets )

# Add custom preprocessor definitions
if (WIN32)
	set_property( TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS CC_USE_AS_DLL)
endif()

# install (shared) lib to specified destinations
if( WIN32 OR APPLE )
	foreach( dest ${INSTALL_DESTINATIONS} )
		install_shared( ${PROJECT_NAME} ${dest} 1 )
	endforeach()
else()
	install_shared( ${PROJECT_NAME} lib/MyProject 0 ) #default destination: /usr/lib
endif()
