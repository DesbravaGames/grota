#ifndef GROTA_CAMERA_H
#define GROTA_CAMERA_H

#include "core/mathematics.h"
#include <stdbool.h>
// the object camera can be perspective or orthogonal,
// if is_perspective are true then the camera is perspective
// otherwise orthogonal
typedef struct {
	bool is_perspective;
	// only for perspective configuration
	GLfloat fovy, aspect;
	// only for orthogonal configuration
	GLfloat left,right,top,bottom;
	// for any type
	GLfloat zNear,zFar;
	Mat4 projection_matrix;
	Mat4 view_matrix;
	GLint render_layer;
	Rect viewport;
} Camera;

void camera_init(Camera *camera);
void camera_perspective(Camera *camera,GLfloat fovy,GLfloat aspect,GLfloat zNear,GLfloat zFar);

void camera_ortho(
			Camera *camera,
			GLfloat left,
			GLfloat right,
			GLfloat bottom,
			GLfloat top,
			GLfloat zNear,
			GLfloat zFar);
			
void camera_update_matrix(Camera *camera);

void camera_log(Camera *cam);
Mat4 camera_generate_shader_matrix(Camera *camera,Mat4 model);

#endif
