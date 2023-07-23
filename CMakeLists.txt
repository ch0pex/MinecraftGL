cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(CraftGL)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(src/helpers/root_dir.h.in src/helpers/root_dir.h)

link_directories(${PROJECT_SOURCE_DIR}/lib)

file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.cc)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h)


include_directories("${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/include" "${CMAKE_BINARY_DIR}/src/helpers")

add_executable(CraftGL ${SOURCE_FILES} ${HEADER_FILES})

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

target_link_libraries(CraftGL glew32 glfw3 ${OPENGL_LIBRARY})


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${PROJECT_SOURCE_DIR}/dlls"
	$<TARGET_FILE_DIR:${PROJECT_NAME}>)