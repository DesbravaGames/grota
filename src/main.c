#include "require.h"
#include <stdbool.h>


#include "window.c"


#include "renderers/quad.c"

Quad quad=QUAD_NEW;

bool engine_init() {
	if(!window_init()) return false;
	if(!quad_init()) return false;
 	time_init();
 	return true;
}

void engine_update() {	
	window_update();
	time_update();
    quad_draw(&quad);
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