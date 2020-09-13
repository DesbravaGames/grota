#include <libs/opengl.h>
#include "colors.h"

Color4f color_create(GLfloat r,GLfloat g,GLfloat b,GLfloat a) {
	Color4f result={r,g,b,a};
    return result;
}
