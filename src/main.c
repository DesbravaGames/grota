#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "core/time.h"
#include "graphics/graphics.h"
#include "graphics/camera.h"
#include "graphics/renderer.h"
#include "graphics/window.h"
#include <GL/glut.h>
/*
 * REQUIRE OPENGL 2.1 WITH ARB_VERTEX_ARRAY_OBJECT EXTENSION
 * 
 */


Camera main_camera={0};
Renderer quad=RENDERER_NEW;

Transform tr_camera=TRANSFORM_IDENTITY;

bool engine_init() {
	if(!graphics_init()) return false;
	if(!renderer_init_quad(&quad)) return false;
 	camera_init(&main_camera);
	quad.color=color_create(0,1,0,0);
	if(!renderer_texturize(&quad,"/home/tocatoca/Pictures/5.jpg")) {
		 printf("Failed to load texture");
	}
 	return true;
}

void engine_update() {	
	graphics_update();
	camera_draw_viewport(&main_camera);
	camera_update_matrix(&main_camera);
	// update projection
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
	
	
	quad.color.r=sin(time_elapsed());
	quad.color.g=1-sin(time_elapsed());
	quad.color.b=cos(time_elapsed());
	
    renderer_draw(&quad,&main_camera);
}
void engine_destroy() {
	renderer_destroy(&quad);
	graphics_destroy();
}

int main(int argc, char **argv) {
	if(!engine_init()) return -1;

	glutIdleFunc(engine_update);	
	glutMainLoop();


	engine_destroy(); 
	return 0;
}
