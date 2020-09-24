#include "core/mathematics.h"
#include "camera.h"


void camera_init(Camera *camera) {
	camera->is_perspective=true;
	camera->fovy=70;
	camera->aspect=1;
	camera->left=50;
	camera->right=-50;
	camera->top=50;
	camera->bottom=-50;
	camera->zNear=0.1;
	camera->zFar=1000;
	camera->projection_matrix=mat4_identity;
	camera->view_matrix=mat4_identity;
    camera->render_layer=0;
    camera->viewport=rect_empty;
    camera_update_matrix(camera);
}

void camera_update_matrix(Camera *camera) {
	if(camera->is_perspective) {
		camera->projection_matrix=
			mat4_perspective(camera->fovy,camera->aspect,camera->zNear,camera->zFar);
	} else {
		camera->projection_matrix=
			mat4_ortho(camera->left,camera->right,camera->bottom,camera->top,camera->zNear,camera->zFar);
	}
}
	
void camera_perspective(Camera *camera,GLfloat fovy,GLfloat aspect,GLfloat zNear,GLfloat zFar) {
	camera->fovy=fovy;
	camera->aspect=aspect;
	camera->zNear=zNear;
	camera->zFar=zFar;
	camera_update_matrix(camera);
}

void camera_ortho(
			Camera *camera,
			GLfloat left,
			GLfloat right,
			GLfloat bottom,
			GLfloat top,
			GLfloat zNear,
			GLfloat zFar) {				
	camera->left=left;
	camera->right=right;
	camera->bottom=bottom;
	camera->top=top;
	camera->zNear=zNear;
	camera->zNear=zNear;
	camera_update_matrix(camera);
}


Mat4 camera_generate_shader_matrix(Camera *camera,Mat4 model) {
	Mat4 inverse_view_matrix=camera->view_matrix;
	return mat4_mult(
		camera->projection_matrix,
		mat4_mult(model,camera->view_matrix)
	);
}

void camera_draw_viewport(Camera *camera) {
	Rect viewport=camera->viewport;
	glViewport(
		viewport.position.x*window_width(),
		viewport.position.y*window_height(),
		viewport.size.x*window_width(),
		viewport.size.y*window_height()
	);
}

void camera_log(Camera *cam) {
/*	printf(" 
	camera->fovy=70;
	camera->aspect=1;
	camera->left=50;
	camera->right=-50;
	camera->top=50;
	camera->bottom=-50;
	camera->zNear=0.1;
	camera->zFar=1000;",
	" 
	camera->fovy,
	camera->aspect=,
	camera->left=50,
	camera->right=-50,
	camera->top=50,
	camera->bottom=-50,
	camera->zNear=0.1,
	camera->zFar=1000,
	)*/
}

