
cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_STANDARD 99)
project(Grota3D)
add_executable(grota 
	main.c
	shaders.c
	camera.c
	window.c
	core/event_register.c
	core/mathematics.c
	core/colors.c
	core/time.c
	libs/glad/glad.c
)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(
	${OPENGL_INCLUDE_DIRS} 
	${GLUT_INCLUDE_DIRS} 
	${PROJECT_SOURCE_DIR}
)

target_link_libraries(grota ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} m dl )
