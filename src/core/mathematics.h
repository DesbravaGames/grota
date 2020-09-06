#ifndef GROTA_MATH_H
#define GROTA_MATH_H

#define VEC2_ZERO {0.0f, 0.0f}
#define VEC2_FILL_ONE {1.0f, 1.0f}
/* two dimensional vector */
typedef struct {
    float x, y;
} Vec2;

Vec2 vec2_normalize(Vec2 vector);
Vec2 vec2_create(float x,float y);
Vec2 vec2_add(Vec2 a,Vec2 b);
Vec2 vec2_sub(Vec2 a, Vec2 b);
float vec2_dot(Vec2 a, Vec2 b);
Vec2 vec2_scalar_mult(Vec2 v,float s);
Vec2 vec2_invert(Vec2 v);


/* three dimensional vector */

#define VEC3_ZERO {0.0f, 0.0f,0.0f}
#define VEC3_FILL_ONE {1.0f, 1.0f,1.0f}

typedef struct {
    float x, y, z;
} Vec3;

Vec3 vec3_normalize(Vec3 vector);
Vec3 vec3_create(float x,float y,float z);
Vec3 vec3_add(Vec3 a,Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 x,Vec3 y);
float vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_scalar_mult(Vec3 v,float s);
Vec3 vec3_invert(Vec3 v);


/*     MATRICES     */

#define MAT_EMPTY_ROW { 0.0f, 0.0f, 0.0f, 0.0f }
#define MAT_EMPTY { MAT_EMPTY_ROW, MAT_EMPTY_ROW, MAT_EMPTY_ROW, MAT_EMPTY_ROW}

/**
 * @brief represent a 4x4 matrix.
 *
 */
typedef struct {
    float data[4][4];
} Mat4;



/**
 * @brief create a 4x4 matrix
 * @return Mat4
 */
Mat4 mat4(float num);


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
Mat4 mat4_perspective(float fovy,float aspect,float zNear,float zFar);

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
        float left,
        float right,
        float bottom,
        float top,
        float zNear,
        float zFar);

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
        float left,
        float right,
        float bottom,
        float top,
        float zNear,
        float zFar);

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



/**
 * @brief multiply matrice by a scalar
 * 
 */
void mat4_scalar_mult(Mat4 *m, float s);


/**
 * @brief multiply matrix m1 by matrix M2
 * 
 */
Mat4 mat4_mult(Mat4 m1, Mat4 m2);
void mat4_rotation(Mat4 *matrix,float angle, float x, float y, float z);
void mat4_rotationxyz(Mat4 *matrix,float angleX, float angleY, float angleZ);
void mat4_rotation_vec3(Mat4 *matrix,Vec3 angles);
void mat4_rotate(Mat4 *matrix,float angle, float x, float y, float z);
void mat4_rotatexyz(Mat4 *matrix,float angleX, float angleY, float angleZ);
void mat4_rotate_vec3(Mat4 *matrix,Vec3 angles);
void mat4_translation(Mat4 *matrix,float x, float y, float z);
void mat4_translation_vec3(Mat4 *matrix,Vec3 translation);
void mat4_translate(Mat4 *matrix,float x, float y, float z);
void mat4_translate_vec3(Mat4 *matrix,Vec3 translation);
void mat4_scaling(Mat4 *matrix,float x, float y, float z);
void mat4_scaling_vec3(Mat4 *matrix,Vec3 scale);
void mat4_scale(Mat4 *matrix,float x, float y, float z);
void mat4_scale_all(Mat4 *matrix,float v);
void mat4_scale_vec3(Mat4 *matrix,Vec3 scale);


#endif