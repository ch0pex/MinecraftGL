cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(CraftGL)

link_directories(${PROJECT_SOURCE_DIR}/lib)

file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

add_executable(CraftGL ${SOURCE_FILES} ${HEADER_FILES})


set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(CraftGL glew32 glfw3 ${OPENGL_LIBRARY})



add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${PROJECT_SOURCE_DIR}/dlls"
	$<TARGET_FILE_DIR:${PROJECT_NAME}>)