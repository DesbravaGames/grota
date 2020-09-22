
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

Transform tr_camera=TRANSFORM_IDENTITY;
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
	// update projection
	camera_update_matrix(&main_camera);
	float velocidade=time_delta()*0.5; //meio metro por segundo
	Mat4 *cmat=&(main_camera.view_matrix);
 
	transform_to_view_matrix(tr_camera,cmat);
	if(input_pressing('w')) tr_camera.position.z+=velocidade;
	if(input_pressing('s')) tr_camera.position.z-=velocidade;

	if(input_pressing('d')) tr_camera.position.x+=velocidade;
	if(input_pressing('a')) tr_camera.position.x-=velocidade;

	if(input_pressing('e')) tr_camera.position.y+=velocidade;
	if(input_pressing('q')) tr_camera.position.y-=velocidade;


	 
	if(input_pressing(355)) tr_camera.angles.y+=velocidade;
	if(input_pressing(357)) tr_camera.angles.y-=velocidade;
	if(input_pressing(356)) tr_camera.angles.x+=velocidade;
	if(input_pressing(358)) tr_camera.angles.x-=velocidade;
	
	
	
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
