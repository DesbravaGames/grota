#ifndef GROTA_COLORS_H
#define GROTA_COLORS_H

#include "colors.h"

#define COLOR_WHITE {1.0f, 1.0f ,1.0f, 1.0f}
#define COLOR_BLACK {0.0f, 0.0f, 0.0f, 1.0f}
#define COLOR_RED  {1.0f, 0.0f, 0.0f, 1.0f}
#define COLOR_GREEN {0.0f, 1.0f, 0.0f, 1.0f}
#define COLOR_BLUE {0.0f, 0.0f, 1.0f, 1.0f}

typedef struct {
    GLfloat r, g, b, a;
} Color4f;

Color4f color_create(GLfloat r,GLfloat g,GLfloat b,GLfloat a);
#endif




