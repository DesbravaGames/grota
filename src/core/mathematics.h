#ifndef GROTA_MATH_H
#define GROTA_MATH_H

#define VEC2_ZERO {0.0f, 0.0f}
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


#endif