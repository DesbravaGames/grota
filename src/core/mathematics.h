#ifndef GROTA_MATH_H
#define GROTA_MATH_H

#include <libs/opengl.h>

#define VEC2_ZERO {0.0f, 0.0f}
#define VEC2_FILL_ONE {1.0f, 1.0f}
/* two dimensional vector */
typedef struct {
    GLfloat x, y;
} Vec2;

Vec2 vec2_normalize(Vec2 vector);
Vec2 vec2_create(GLfloat x,GLfloat y);
Vec2 vec2_add(Vec2 a,Vec2 b);
Vec2 vec2_sub(Vec2 a, Vec2 b);
GLfloat vec2_dot(Vec2 a, Vec2 b);
Vec2 vec2_scalar_mult(Vec2 v,GLfloat s);
Vec2 vec2_invert(Vec2 v);

typedef struct {
	Vec2 size;
	Vec2 position;
} Rect;

static Rect rect_empty={
	{1.0f,1.0f},
	{0.0f,0.0f}
};

/* three dimensional vector */

#define VEC3_ZERO {0.0f, 0.0f,0.0f}
#define VEC3_FILL_ONE {1.0f, 1.0f,1.0f}

typedef struct {
    GLfloat x, y, z;
} Vec3;

Vec3 vec3_normalize(Vec3 vector);
Vec3 vec3_create(GLfloat x,GLfloat y,GLfloat z);
Vec3 vec3_add(Vec3 a,Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 x,Vec3 y);
GLfloat vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_scalar_mult(Vec3 v,GLfloat s);
Vec3 vec3_invert(Vec3 v);

/*     MATRICES     */

#define MAT4_EMPTY {0}
#define MAT4_IDENTITY {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}

/**
 * @brief represent a 4x4 matrix.
 *
 */
typedef struct {
    GLfloat data[4][4];
} Mat4;


static const Mat4 mat4_identity= {
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
};
/**
 * @brief create a 4x4 matrix
 * @return Mat4
 */
Mat4 mat4_create(GLfloat num);


/**
 * @brief multiply matrix m1 by matrix M2
 * 
 */
Mat4 mat4_mult(Mat4 m1, Mat4 m2);

void mat4_rotate_vec3(Mat4 *matrix,Vec3 angles);
void mat4_translate_vec3(Mat4 *matrix,Vec3 translation);
void mat4_scale_vec3(Mat4 *matrix,Vec3 scale);


/**
 * @brief Creates a matrix for a symetric perspective-view frustum based on
 *        the default handedness.
 * @param fovy Specifies the field of view angle in the y direction.
 *             Expressed in radians.
 * @param aspect Specifies the aspect ratio that determines the field of view
 *               in the x direction. The aspect ratio is the ratio of
 *               x (width) to y (height).
 * @param near Specifies the distance from the viewer to the near clipping
 *             plane (always positive).
 * @param far Specifies the distance from the viewer to the far clipping
 *            plane (always positive).
 */
Mat4 mat4_perspective(GLfloat fovy,GLfloat aspect,GLfloat zNear,GLfloat zFar);

/**
 * @brief Creates a matrix for an orthographic parallel viewing volume.
 * @param left
 * @param right
 * @param bottom
 * @param top
 * @param zNear
 * @param zFar
 */
Mat4 mat4_ortho(
        GLfloat left,
        GLfloat right,
        GLfloat bottom,
        GLfloat top,
        GLfloat zNear,
        GLfloat zFar);

/**
 * @brief Creates a frustum matrix.
 * @param left
 * @param right
 * @param bottom
 * @param top
 * @param near
 * @param far
 */
Mat4 mat4_frustum(
        GLfloat left,
        GLfloat right,
        GLfloat bottom,
        GLfloat top,
        GLfloat zNear,
        GLfloat zFar);

/**
 * @brief Build a look at view matrix based on the default handedness.
 * @param eye Position of the camera
 * @param center Position where the camera is looking at
 * @param up Normalized up vector, how the camera is oriented.
 *           Typically (0, 0, 1)
 */
Mat4 mat4_look_at(
        Vec3 eye,
        Vec3 center,
        Vec3 up);


/*   TRANSFORMATIONS  */
typedef struct {
	Vec3 position;
	Vec3 angles;
	Vec3 size;
} Transform;

#define TRANSFORM_EMPTY {VEC3_ZERO, VEC3_ZERO,VEC3_FILL_ONE };
#define TRANSFORM_IDENTITY {VEC3_ZERO, VEC3_ZERO,VEC3_FILL_ONE };

static Transform transform_identity= {
	{0.0f,0.0f,0.0f}, //pos
	{0.0f,0.0f,0.0f}, //euler
	{1.0f,1.0f,1.0f} //size
};
void transform_to_matrix(Transform transform,Mat4 *matrix);

/*
 * view matrix is the relationship between world and camera
 * then, is the inverse process of model matrix
 *  */
void transform_to_view_matrix(Transform transform,Mat4 *matrix);


#endif
