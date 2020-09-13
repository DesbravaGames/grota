
#define STB_IMAGE_IMPLEMENTATION
#include <stdbool.h>
#include "camera.h"
#include "window.h"
#include "shaders.h"
#include "renderers/quad.c"

#include <GL/glut.h>
#include "core/time.h"
/*
 * REQUIRE OPENGL 2.1 WITH ARB_VERTEX_ARRAY_OBJECT EXTENSION
 * */


Camera main_camera={0};
Quad quad=QUAD_NEW;

bool engine_init() {
	if(!window_init()) return false;
	if(!quad_init()) return false;
	quad.color=color_create(0,1,0,0);
	if(!quad_texturize(&quad,"/home/tocatoca/Pictures/5.jpg")) {
		 printf("Failed to load texture");
	}
 	time_init();
 	camera_init(&main_camera);
 	return true;
}

void engine_update() {	
	window_update();
	time_update();
	camera_update_matrices(&main_camera);
	
	glViewport(
		main_camera.viewport.position.x*window_width(),
		main_camera.viewport.position.y*window_height(),
		main_camera.viewport.size.x*window_width(),
		main_camera.viewport.size.y*window_height()
	);
	quad.color.r=sin(time_elapsed());
	quad.color.g=1-sin(time_elapsed());
	quad.color.b=cos(time_elapsed());
    quad_draw(&quad,&main_camera);
}
void engine_destroy() {
	quad_destroy();
	window_destroy();
}

int main(int argc, char **argv) {
	if(!engine_init()) return -1;
	
	glutIdleFunc(engine_update);	
	glutMainLoop();

	engine_destroy(); 
	return 0;
}
