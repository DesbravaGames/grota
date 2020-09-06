#include <math.h>
#include "mathematics.h"
#include "require.h"


/*-------------------------VEC2----------------------------*/

Vec2 vec2_create(float x,float y) {
    Vec2 result={x,y};
    return result;
}

Vec2 vec2_normalize(Vec2 vector) {
    float x = vector.x * vector.x;
    float y = vector.y * vector.y;
    float all = (float) sqrt(x + y);

    Vec2 result;
    result.x = vector.x / all;
    result.y = vector.y / all;

    return result;
}

Vec2 vec2_add(Vec2 a,Vec2 b) {
    Vec2 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

Vec2 vec2_sub(Vec2 a, Vec2 b) {
    Vec2 result;
    result.x = a.x - b.x;
    result.y = a.y + b.y;

    return result;
}

float vec2_dot(Vec2 a, Vec2 b) {
    return (a.x * b.x) + (a.y * b.y);
}

Vec2 vec2_scalar_mult(Vec2 v,float s) {
    Vec2 result;
    result.x = v.x * s;
    result.y = v.y * s;

    return result;
}

Vec2 vec2_invert(Vec2 v) {
    Vec2 result;
    result.x=v.x;
    result.y=v.y;
    return result;
};

/*-------------------------VEC3----------------------------*/


Vec3 vec3_normalize(Vec3 vector) {
    float x = vector.x * vector.x;
    float y = vector.y * vector.y;
    float z = vector.z * vector.z;
    float all = (float) sqrt(x + y + z);

    Vec3 result;
    result.x = vector.x / all;
    result.y = vector.y / all;
    result.z = vector.z / all;

    return result;
}

Vec3 vec3_create(float x,float y,float z) {
    Vec3 result={x,y,z};
    return result;
}

Vec3 vec3_add(Vec3 a,Vec3 b) {
    Vec3 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
    Vec3 result;
    result.x = a.x - b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

Vec3 vec3_cross(Vec3 x,Vec3 y) {
    Vec3 result;
    result.x = x.y * y.z - y.y * x.z;
    result.y = x.z * y.x - y.z * x.x;
    result.z = x.x * y.y - y.x * x.y;

    return result;
}

float vec3_dot(Vec3 a, Vec3 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}


Vec3 vec3_scalar_mult(Vec3 v,float s) {
    Vec3 result;
    result.x = v.x * s;
    result.y = v.y * s;
    result.z = v.z * s;

    return result;
}


Vec3 vec3_invert(Vec3 v) {
    Vec3 result;
    result.x=v.x;
    result.y=v.y;
    result.z=v.z;
    return result;
};


/*             MATRICES               */





Mat4 mat4(float num) {
    Mat4 result = MAT_EMPTY;
    result.data[0][0] = num;
    result.data[1][1] = num;
    result.data[2][2] = num;
    result.data[3][3] = num;
    return result;
}


Mat4 mat4_perspective(
        float fovy,
        float aspect,
        float zNear,
        float zFar) {

    float tanHalfFovy = (float) tan(fovy / (float) 2);

    Mat4 result = mat4(0.0f);
    result.data[0][0] = (float) 1 / (aspect * tanHalfFovy);
    result.data[1][1] = (float) 1 / (tanHalfFovy);
    result.data[2][2] = -(zFar + zNear) / (zFar - zNear);
    result.data[2][3] = -(float) 1;
    result.data[3][2] = -((float) 2 * zFar * zNear) / (zFar - zNear);

    return result;
}

Mat4 mat4_ortho(
        float left,
        float right,
        float bottom,
        float top,
        float zNear,
        float zFar) {
    Mat4 result = mat4(1.0f);
    result.data[0][0] = (float) 2 / (right - left);
    result.data[1][1] = (float) 2 / (top - bottom);
    result.data[2][2] = -(float) 2 / (zFar - zNear);
    result.data[3][0] = -(right + left) / (right - left);
    result.data[3][1] = -(top + bottom) / (top - bottom);
    result.data[3][2] = -(zFar + zNear) / (zFar - zNear);

    return result;
}

Mat4 mat4_frustum(
        float left,
        float right,
        float bottom,
        float top,
        float zNear,
        float zFar) {

    Mat4 result = mat4(0.0f);
    result.data[0][0] = ((float) 2 * zNear) / (right - left);
    result.data[1][1] = ((float) 2 * zNear) / (top - bottom);
    result.data[2][0] = (right + left) / (right - left);
    result.data[2][1] = (top + bottom) / (top - bottom);
    result.data[2][2] = -(zFar + zNear) / (zFar - zNear);
    result.data[2][3] = -(float) 1;
    result.data[3][2] = -((float) 2 * zFar * zNear) / (zFar - zNear);

    return result;
}

Mat4 mat4_look_at(
        Vec3 eye,
        Vec3 center,
        Vec3 up) {
    const Vec3 f = vec3_normalize(vec3_sub(center, eye));
    const Vec3 s = vec3_normalize(vec3_cross(f, up));
    const Vec3 u = vec3_cross(s, f);

    Mat4 result = mat4(1.0f);
    result.data[0][0] = s.x;
    result.data[1][0] = s.y;
    result.data[2][0] = s.z;
    result.data[0][1] = u.x;
    result.data[1][1] = u.y;
    result.data[2][1] = u.z;
    result.data[0][2] = -f.x;
    result.data[1][2] = -f.y;
    result.data[2][2] = -f.z;
    result.data[3][0] = -vec3_dot(s, eye);
    result.data[3][1] = -vec3_dot(u, eye);
    result.data[3][2] = vec3_dot(f, eye);

    return result;
}


void mat4_scalar_mult(Mat4 *m, float s) {
    for(int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            m->data[y][x] *= s;
        }
    }
}

Mat4 mat4_mult(Mat4 m1, Mat4 m2) {
    Mat4 result = 
    {
        {
           {
                m2.data[0][0] * m1.data[0][0] + m2.data[0][1] * m1.data[1][0] + m2.data[0][2] * m1.data[2][0] + m2.data[0][3] * m1.data[3][0] , 
                m2.data[0][0] * m1.data[0][1] + m2.data[0][1] * m1.data[1][1] + m2.data[0][2] * m1.data[2][1] + m2.data[0][3] * m1.data[3][1] , 
                m2.data[0][0] * m1.data[0][2] + m2.data[0][1] * m1.data[1][2] + m2.data[0][2] * m1.data[2][2] + m2.data[0][3] * m1.data[3][2] , 
                m2.data[0][0] * m1.data[0][3] + m2.data[0][1] * m1.data[1][3] + m2.data[0][2] * m1.data[2][3] + m2.data[0][3] * m1.data[3][3] 
            }, 
           {
                m2.data[1][0] * m1.data[0][0] + m2.data[1][1] * m1.data[1][0] + m2.data[1][2] * m1.data[2][0] + m2.data[1][3] * m1.data[3][0] , 
                m2.data[1][0] * m1.data[0][1] + m2.data[1][1] * m1.data[1][1] + m2.data[1][2] * m1.data[2][1] + m2.data[1][3] * m1.data[3][1] , 
                m2.data[1][0] * m1.data[0][2] + m2.data[1][1] * m1.data[1][2] + m2.data[1][2] * m1.data[2][2] + m2.data[1][3] * m1.data[3][2] , 
                m2.data[1][0] * m1.data[0][3] + m2.data[1][1] * m1.data[1][3] + m2.data[1][2] * m1.data[2][3] + m2.data[1][3] * m1.data[3][3] 
            },
           {
            m2.data[2][0] * m1.data[0][0] + m2.data[2][1] * m1.data[1][0] + m2.data[2][2] * m1.data[2][0] + m2.data[2][3] * m1.data[3][0],
            m2.data[2][0] * m1.data[0][1] + m2.data[2][1] * m1.data[1][1] + m2.data[2][2] * m1.data[2][1] + m2.data[2][3] * m1.data[3][1] , 
            m2.data[2][0] * m1.data[0][2] + m2.data[2][1] * m1.data[1][2] + m2.data[2][2] * m1.data[2][2] + m2.data[2][3] * m1.data[3][2] , 
            m2.data[2][0] * m1.data[0][3] + m2.data[2][1] * m1.data[1][3] + m2.data[2][2] * m1.data[2][3] + m2.data[2][3] * m1.data[3][3] 
            }, 

           {
            m2.data[3][0] * m1.data[0][0] + m2.data[3][1] * m1.data[1][0] + m2.data[3][2] * m1.data[2][0] + m2.data[3][3] * m1.data[3][0], 
            m2.data[3][0] * m1.data[0][1] + m2.data[3][1] * m1.data[1][1] + m2.data[3][2] * m1.data[2][1] + m2.data[3][3] * m1.data[3][1] , 
            m2.data[3][0] * m1.data[0][2] + m2.data[3][1] * m1.data[1][2] + m2.data[3][2] * m1.data[2][2] + m2.data[3][3] * m1.data[3][2] , 
            m2.data[3][0] * m1.data[0][3] + m2.data[3][1] * m1.data[1][3] + m2.data[3][2] * m1.data[2][3] + m2.data[3][3] * m1.data[3][3] 
          } 
        }
    };

    return result;
}


const double pi=M_PI;
const double half_pi=M_PI/2;
const double double_pi=M_PI*2;

static double cos_from_sin(double _sin, double angle) {
    double cos = sqrt(1.0 - _sin * _sin);
    double a = angle + half_pi;
    double b = a - (int)(a / double_pi) * double_pi;
    if (b < 0.0) 
        b = double_pi + b;
    if (b >= pi)
        return -cos;
    return cos;
}

void mat4_rotation(Mat4 *matrix,float angle, float x, float y, float z) {
    float _sin = (float) sin(angle);
    float cos = (float) cos_from_sin(_sin, angle);
    float C = 1.0f - cos;

    float xy = x * y, xz = x * z, yz = y * z;

    matrix->data[0][0] = cos + x * x * C;
    matrix->data[0][1] = xy * C - z * _sin;
    matrix->data[0][2] = xz * C + y * _sin;

    matrix->data[1][0] = xy * C + z * _sin;
    matrix->data[1][1] = cos + y * y * C;
    matrix->data[1][2] = yz * C - x * _sin;

    matrix->data[2][0] =xz * C - y * _sin;

    matrix->data[2][1] = yz * C + x * _sin;
    matrix->data[2][2] = cos + z * z * C;

}

void mat4_rotation_vec3(Mat4 *matrix,Vec3 angles){
    mat4_rotationxyz(matrix,angles.x,angles.y,angles.z);
}
void mat4_rotationxyz(Mat4 *matrix,float angleX, float angleY, float angleZ) {
    float sinX = (float) sin(angleX);
    float cosX = (float) cos_from_sin(sinX, angleX);
    float sinY = (float) sin(angleY);
    float cosY = (float) cos_from_sin(sinY, angleY);
    float sinZ = (float) sin(angleZ);
    float cosZ = (float) cos_from_sin(sinZ, angleZ);
    float m_sinX = -sinX;
    float m_sinY = -sinY;
    float m_sinZ = -sinZ;

    // rotateX
    float nm11 = cosX;
    float nm12 = sinX;
    float nm21 = m_sinX;
    float nm22 = cosX;
    // rotateY
    float nm00 = cosY;
    float nm01 = nm21 * m_sinY;
    float nm02 = nm22 * m_sinY;
    matrix->data[0][2] = sinY;
    matrix->data[1][2] = (nm21 * cosY);
    matrix->data[2][2] = (nm22 * cosY);
    // rotateZ
    matrix->data[0][0] = (nm00 * cosZ);
    matrix->data[1][0] = (nm01 * cosZ + nm11 * sinZ);
    matrix->data[2][0] = (nm02 * cosZ + nm12 * sinZ);
    matrix->data[0][1] = (nm00 * m_sinZ);
    matrix->data[1][1] = (nm01 * m_sinZ + nm11 * cosZ);
    matrix->data[2][1] = (nm02 * m_sinZ + nm12 * cosZ);
}

void mat4_rotate(Mat4 *matrix,float angle, float x, float y, float z) {
  Mat4 rotation_matrix=mat4(1.0);
  mat4_rotation(&rotation_matrix,angle,x,y,z);
  *matrix=mat4_mult(rotation_matrix,*matrix);
}

void mat4_rotate_vec3(Mat4 *matrix,Vec3 angles){
    Mat4 rotation_matrix=mat4(1.0);
    mat4_rotationxyz(&rotation_matrix,angles.x,angles.y,angles.z);
    *matrix=mat4_mult(rotation_matrix,*matrix);
}
void mat4_rotatexyz(Mat4 *matrix,float angleX, float angleY, float angleZ) {
     Mat4 rotation_matrix=mat4(1.0);
    mat4_rotationxyz(&rotation_matrix,angleX,angleY,angleZ);
    *matrix=mat4_mult(rotation_matrix,*matrix);
}


void mat4_translation(Mat4 *matrix,float x, float y, float z) {
    matrix->data[3][0]=x;
    matrix->data[3][1]=y;
    matrix->data[3][2]=z;
}
void mat4_translation_vec3(Mat4 *matrix,Vec3 translation) {
    matrix->data[3][0]=translation.x;
    matrix->data[3][1]=translation.y;
    matrix->data[3][2]=translation.z;
}    

void mat4_translate(Mat4 *matrix,float x, float y, float z) {
    matrix->data[3][0]+=x;
    matrix->data[3][1]+=y;
    matrix->data[3][2]+=z;
}

void mat4_translate_vec3(Mat4 *matrix,Vec3 translation) {
    matrix->data[3][0]+=translation.x;
    matrix->data[3][1]+=translation.y;
    matrix->data[3][2]+=translation.z;
}    
void mat4_scaling(Mat4 *matrix,float x, float y, float z) {
    matrix->data[0][0]=x;
    matrix->data[1][1]=y;
    matrix->data[2][2]=z;
}
void mat4_scaling_vec3(Mat4 *matrix,Vec3 scale) {
    mat4_scaling(matrix,scale.x,scale.y,scale.z);
}
void mat4_scale_all(Mat4 *matrix,float v) {
    matrix->data[0][0]*=v;
    matrix->data[1][1]*=v;
    matrix->data[2][2]*=v;
}
void mat4_scale(Mat4 *matrix,float x, float y, float z) {
    matrix->data[0][0]*=x;
    matrix->data[1][1]*=y;
    matrix->data[2][2]*=z;
}
void mat4_scale_vec3(Mat4 *matrix,Vec3 scale) {
    matrix->data[0][0]*=scale.x;
    matrix->data[1][1]*=scale.y;
    matrix->data[2][2]*=scale.z;
}