cmake_minimum_required(VERSION 3.0)

project( FORM_LIB  VERSION 1.0 )

#添加头文件
include_directories( ${GEOENGINE_LIB_SOURCE_DIR})

file( GLOB header_list *.h)
file( GLOB source_list *.cpp)

file( GLOB ui_list *.ui )
file( GLOB qrc_list  *.qrc )
file( GLOB rc_list  *.rc )

qt5_wrap_ui( generated_ui_list ${ui_list} )
add_library( ${PROJECT_NAME} SHARED ${header_list} ${source_list} ${generated_ui_list} )

#添加依赖库 添加protobufMap
target_link_libraries( ${PROJECT_NAME} GEOENGINE_LIB)

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
