#include "core/array.h"
#include "core/mathematics.h"
#include "core/colors.h"
#include "core/time.h"
#include "window.h"
#include <stdlib.h>
#include <string.h>

/*
#ifdef __APPLE_
	#include <GLUT/glut.h>
#else
#endif
*/

#define MAX_EVENTS_KEYS 16

int pressed_keys[MAX_EVENTS_KEYS];
int pressed_keys_buffer[MAX_EVENTS_KEYS];

int pressing_keys[MAX_EVENTS_KEYS];
int released_keys[MAX_EVENTS_KEYS];
int released_keys_buffer[MAX_EVENTS_KEYS];

static void register_specialdown(int key,int mouse_x,int mouse_y) {
	array_add_once(pressed_keys_buffer,MAX_EVENTS_KEYS,key+255);
	array_add_once(pressing_keys,MAX_EVENTS_KEYS,key+255);
}
static void register_specialup(int key,int mouse_x,int mouse_y) {
	array_remove(pressing_keys,MAX_EVENTS_KEYS,key+255);
	array_add_once(released_keys_buffer,MAX_EVENTS_KEYS,key+255);
}

static void register_keydown(unsigned char key,int mouse_x,int mouse_y) {
	array_add_once(pressed_keys_buffer,MAX_EVENTS_KEYS,(int)key);
	array_add_once(pressing_keys,MAX_EVENTS_KEYS,(int)key);
}
static void register_keyup(unsigned char key,int mouse_x,int mouse_y) {
	array_remove(pressing_keys,MAX_EVENTS_KEYS,(int)key);
	array_add_once(released_keys_buffer,MAX_EVENTS_KEYS,(int)key);
}


int input_pressing(int key) {
	return array_contains(pressing_keys,MAX_EVENTS_KEYS,key);
}
int input_pressed(int key) {
	return array_contains(pressed_keys,MAX_EVENTS_KEYS,key);
};
int input_released(int key) {
	return array_contains(released_keys,MAX_EVENTS_KEYS,key);
};


#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>	
Color4f window_bgcolor={0.2f, 0.3f, 0.3f, 1.0f};
Vec2 window_size={800,600};
bool window_show_fps=true;


int window_width(){ return (int)window_size.x;}
int window_height() { return (int)window_size.y;};

bool window_init() {
	int glut_argc;char **glut_argv=NULL;
	glutInit(&glut_argc,glut_argv);

	if(gladLoadGL()) {
        // you need an OpenGL context before loading glad
        printf("I did load GL with no context!\n");
        return false;
    }

	glutInitWindowSize(window_size.x, window_size.y);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Grota 3D");
    
 	if(!gladLoadGL()) {
        printf("Error Loading OpenGL With GLAD!\n");
        return false;
    }
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(register_keydown);
	glutKeyboardUpFunc(register_keyup);
	glutSpecialFunc(register_specialdown);
	glutSpecialUpFunc(register_specialup);
    return true;
}

void window_update() {
	glutSwapBuffers();
	glClearColor(window_bgcolor.r,window_bgcolor.g,window_bgcolor.b,window_bgcolor.a);
    glClear(GL_COLOR_BUFFER_BIT);

	if(window_show_fps) {
		char window_title[100];
		snprintf(window_title,100," FPS: %d",time_fps());
		glutSetWindowTitle(window_title);
	}

	memcpy(pressed_keys,pressed_keys_buffer,MAX_EVENTS_KEYS*sizeof(int));
	array_clear(pressed_keys_buffer,MAX_EVENTS_KEYS);
	memcpy(released_keys,released_keys_buffer,MAX_EVENTS_KEYS*sizeof(int));
	array_clear(released_keys_buffer,MAX_EVENTS_KEYS);

	bool found_key=false;
	for(int c=0;c<MAX_EVENTS_KEYS;c++) {
		if(pressed_keys[c]==0) break;
		else {
			found_key=true;
			if(pressed_keys[c]<255) {
				printf("%c ",pressed_keys[c]);
			} else {
				printf("%d ",pressed_keys[c]);
			}
		}
	}
	if(found_key) printf(" foram pressionado(s)\n");

	found_key=false;
	for(int c=0;c<MAX_EVENTS_KEYS;c++) {
		if(released_keys[c]==0) break;
		else {
			found_key=true;
			if(released_keys[c]<255) {
				printf("%c ",released_keys[c]);
			} else {
				printf("%d ",released_keys[c]);
			}
		}
	}
	if(found_key) printf(" solta(s)\n");
}

void window_destroy() {
	// nenhum codigo ate agora
}



