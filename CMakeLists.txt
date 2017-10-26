# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (opgl_learning)

find_package(OpenGL REQUIRED)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

# Compile external dependencies 
add_subdirectory (ThirdParty)

include_directories(
	ThirdParty/glfw/include/GLFW/
	ThirdParty/glm/
	ThirdParty/glew/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	glew
)

# GL_learn 1
add_executable(01_first_window
	src/01_first_window/01_first_window.cpp
)
target_link_libraries(01_first_window
	${ALL_LIBS}
)
# Xcode working directories
set_target_properties(01_first_window PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/01_first_window/")

# SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
# SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )

if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
   TARGET 01_first_window POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/01_first_window${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/src/01_first_window/"
)
elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )