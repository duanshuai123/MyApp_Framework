cmake_minimum_required(VERSION 3.0)
cmake_policy(PUSH)

project( Project_Framework )

add_compile_options(-std=c++11 -std=c++14 -std=c++17)

include( cmake/CMakePolicies.cmake )
include( cmake/CMakeSetCompilerOptions.cmake )
include( cmake/CMakeInclude.cmake )
# Default debug suffix for libraries.
set( CMAKE_DEBUG_POSTFIX "d" )

# One shouldn't generate the BUILD project directly in the SOURCES folder!
if ( ${CMAKE_CURRENT_BINARY_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
	if ( NOT SAME_BUILD_AND_SOURCE_FOLDER_WARNING_ALREADY_ISSUED )
		message(FATAL_ERROR "It is not advised to BUILD the binaries directly in the SOURCE folder!\n If you want to proceed with this option, just CONFIGURE the project once again" )
		set( SAME_BUILD_AND_SOURCE_FOLDER_WARNING_ALREADY_ISSUED TRUE )
	endif()
endif()

# Default install folders
# (on Windows - msvc generator - the '_debug' suffix is automatically added for debug configurations)
set( INSTALL_DESTINATIONS MyProject )
if( UNIX AND NOT APPLE )
	set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/MyProject")
endif()

# Define target folders
if(WIN32 OR APPLE) 
	set( MYPROJECT_DEST_FOLDER MyProject )
	if (OPTION_GL_QUAD_BUFFER_SUPPORT)
		set ( MYPROJECT_DEST_FOLDER ${MYPROJECT_DEST_FOLDER}Stereo )
	endif()
else()
	set( MYPROJECT_DEST_FOLDER bin )
endif()


if (APPLE)
	set( MYPROJECT_MAC_BASE_DIR ${CMAKE_INSTALL_PREFIX}/${MYPROJECT_DEST_FOLDER}/MYPROJECT.app  CACHE INTERNAL "CloudCompare bundle dir")
	set( MYPROJECT_MAC_FRAMEWORK_DIR ${MYPROJECT_MAC_BASE_DIR}/Contents/Frameworks CACHE INTERNAL "CC framework dir" )
	set( MYPROJECT_MAC_PLUGIN_DIR ${MYPROJECT_MAC_BASE_DIR}/Contents/PlugIns/ccPlugins CACHE INTERNAL "CC plugin dir" )
	
endif()

# set default install folders
if( WIN32 )
    # (on Windows - msvc generator - the '_debug' suffix is automatically added for debug configurations)
    set( INSTALL_DESTINATIONS ${MYPROJECT_DEST_FOLDER} )
elseif( APPLE )
	set( INSTALL_DESTINATIONS "${MYPROJECT_MAC_FRAMEWORK_DIR}" )
elseif( UNIX )
	set( INSTALL_DESTINATIONS ${CMAKE_INSTALL_PREFIX}/bin )
endif()

# Add external libraries
include( cmake/CMakeExternalLibs.cmake )
include( contrib/AllSupport.cmake )


# by duan这些依赖上面的子文件夹中的库，需要放到它们后面，否则可能编不过
add_subdirectory( libs/GeoEngine )
add_subdirectory( libs/Form )
add_subdirectory( libs/leetcode )
add_subdirectory( applications )

cmake_policy(POP)
