#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "core/time.h"
#include "camera.h"
#include "window.h"
#include "shaders.h"
#include "renderer.h"
#include <GL/glut.h>
/*
 * REQUIRE OPENGL 2.1 WITH ARB_VERTEX_ARRAY_OBJECT EXTENSION
 * 
 */

bool graphics_init() {
	if(!window_init()) return false;
 	time_init();
    return true;
}

void graphics_update() {	
	time_update();
	window_update();
}
void graphics_destroy() {
	window_destroy();
}
