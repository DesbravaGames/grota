#ifndef NK_OPENGL_SHADERS_H
#define NK_OPENGL_SHADERS_H

#define SHADER_VERTEX_ATTRIBUTE 0
#define SHADER_NORMAL_ATTRIBUTE 1
#define SHADER_TEXTCOORD_ATTRIBUTE 2
#define SHADER_VERTEX_COLOR_ATTRIBUTE 4

int shader_compile_vertex(const char *shadersource);
int shader_compile_fragment(const char *shadersource);
int shader_link_program(int vertex_shader,int fragment_shader);
int shader_create_program(const char *vertex_shader,const char * fragment_shader);

void shader_uniform_int(int id_program,const char *name, int value);
void shader_uniform_bool(int id_program,const char *name, bool value);
void shader_uniform_float(int id_program,const char *name, float value);
void shader_uniform_color(int id_program,const char *name, Color4f color);


#endif