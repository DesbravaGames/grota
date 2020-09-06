#include <math.h>
#include "mathematics.h"
#include "require.h"

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