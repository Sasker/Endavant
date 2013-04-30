cmake_minimum_required (VERSION 2.6)



####################### ENGINE #####################
project (Endavant)

INCLUDE_DIRECTORIES(${${PROJECT_NAME}_SOURCE_DIR}/src/Engine)
INCLUDE_DIRECTORIES(${${PROJECT_NAME}_SOURCE_DIR}/src/Externals)

file(GLOB_RECURSE SOURCE_FILES
	${${PROJECT_NAME}_SOURCE_DIR}/src/Engine/*.cpp	
	${${PROJECT_NAME}_SOURCE_DIR}/src/Externals/*.cpp	
	)
	
if(CMAKE_BUILD_TYPE MATCHES release)
	set(EXECUTABLE_OUTPUT_PATH ${${PROJECT_NAME}_SOURCE_DIR}/bin/release)
	LINK_DIRECTORIES (${${PROJECT_NAME}_SOURCE_DIR}/build/release) 
	message("--- RELEASE BUILD ---")
endif(CMAKE_BUILD_TYPE MATCHES release)
if(CMAKE_BUILD_TYPE MATCHES debug)
	set(EXECUTABLE_OUTPUT_PATH ${${PROJECT_NAME}_SOURCE_DIR}/bin/debug)
	LINK_DIRECTORIES (${${PROJECT_NAME}_SOURCE_DIR}/build/debug) 
	message("--- DEBUG BUILD ---")
endif(CMAKE_BUILD_TYPE MATCHES debug)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -std=c++0x")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Werror -std=c++0x")

ADD_LIBRARY(${PROJECT_NAME} ${SOURCE_FILES})

if(WIN32)
	if(WIN32 AND NOT MINGW)
		TARGET_LINK_LIBRARIES(${PROJECT_NAME} sdlmain sdl sdl2_mixer sdl_image opengl32 GLEW)
	else(WIN32 AND NOT MINGW)
		TARGET_LINK_LIBRARIES(${PROJECT_NAME} mingw32 sdl2main sdl2 sdl2_mixer sdl2_image opengl32 GLEW)	
	endif()
elseif(UNIX AND NOT APPLE)
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} SDL2 SDL2_mixer SDL2_image GL GLEW)
else(UNIX AND NOT APPLE)
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} SDL2 SDL2_mixer SDL2_image GLEW)
endif()











####################### TESTS #####################
file(GLOB_RECURSE TEST1_SOURCE_FILES
	${${PROJECT_NAME}_SOURCE_DIR}/src/Tests/Test1/*.cpp	
)

ADD_EXECUTABLE(Test1 ${TEST1_SOURCE_FILES})
ADD_DEPENDENCIES(Test1 ${PROJECT_NAME})
TARGET_LINK_LIBRARIES(Test1 ${PROJECT_NAME} )

	






