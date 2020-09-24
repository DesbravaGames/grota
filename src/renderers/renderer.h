#ifndef GROTA_RENDERER_H
#define GROTA_RENDERER_H

#include "core/mathematics.h"
#include "core/colors.h"
#include "camera.h"
 
#define RENDERER_NEW {COLOR_WHITE,MAT4_IDENTITY,0,0,0,0}



typedef struct {
    Vec3 vertex;
    Vec2 texture_coordinates;
} VertexData;

typedef struct {
    GLuint vertices_count;
    VertexData *vertices;
    GLuint indices_count;
    GLuint *indices;
} RendererMesh;

typedef struct {
    Color4f color;
	Mat4 matrix;
    GLuint texture_id;
    // i need EBO and VBO to clear
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLuint indices_count;
} Renderer;



GLuint load_texture(const char *filename);

bool renderer_texturize(Renderer *renderer,const char *filename);

bool renderer_init(Renderer *renderer,RendererMesh data);

void renderer_draw(Renderer *renderer,Camera *camera);

void renderer_destroy(Renderer *renderer);

#endif