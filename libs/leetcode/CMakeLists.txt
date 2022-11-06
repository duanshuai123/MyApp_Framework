cmake_minimum_required(VERSION 3.0)

project( LeetCode_LIB  VERSION 1.0 )

#添加头文件

file( GLOB header_list
    *.h *.hpp
    ./LeetCode101/leetcode_101/chapter_5/*.h
    ./LeetCode101/leetcode_101/chapter_4/*.h
    )

file( GLOB source_list *.cpp *.cc
    ./LeetCode101/leetcode_101/chapter_5/*.cpp
    ./LeetCode101/leetcode_101/chapter_4/*.cpp
    )

add_library( ${PROJECT_NAME} SHARED ${header_list} ${source_list})


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
