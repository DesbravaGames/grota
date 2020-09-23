#include "core/mathematics.h"
#include "core/colors.h"
#include "camera.h"
#include "renderer.h"

VertexData quad_vertices[] = {
	// positions      // texture coords
	{{ 0.5f,  0.5f,0.0f  },{ 1.0f, 1.0f}}, // top right
	{{ 0.5f, -0.5f,0.0f  },{ 1.0f, 0.0f}}, // bottom right
	{{-0.5f, -0.5f,0.0f  },{ 0.0f, 0.0f}}, // bottom left
	{{-0.5f,  0.5f,0.0f  },{ 0.0f, 1.0f}}  // top left 
};
GLuint quad_indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

bool renderer_init_quad(Renderer *quad) {
    RendererData rend_data;
    rend_data.vertices=quad_vertices;
    rend_data.vertices_count=sizeof(quad_vertices)/sizeof(VertexData);
    rend_data.indices=quad_indices;
    rend_data.indices_count=sizeof(quad_indices)/sizeof(GLuint);
    return renderer_init(quad,rend_data);
}



VertexData skybox_vertices[] = {
/*	{1.000000 -1.000000 -1.000000},
	{1.000000 -1.000000 1.000000},
	{-1.000000 -1.000000 1.000000},
	{-1.000000 -1.000000 -1.000000},
	{1.000000 1.000000 -1.000000}
	{0.999999 1.000000 1.000001},
	{-1.000000 1.000000 1.000000},
	{-1.000000 1.000000 -1.000000},*/
};
GLuint skybox_indices[] = {
};

bool renderer_init_skybox(Renderer *quad) {
    RendererData rend_data;
    rend_data.vertices=skybox_vertices;
    rend_data.vertices_count=sizeof(skybox_vertices)/sizeof(VertexData);
    rend_data.indices=skybox_indices;
    rend_data.indices_count=sizeof(skybox_indices)/sizeof(GLuint);
    return renderer_init(quad,rend_data);
}
void skybox_draw(Renderer *skybox,Camera *camera) {
	glDisable(GL_DEPTH_TEST);
	renderer_draw(skybox,camera);
	glEnable(GL_DEPTH_TEST);
}