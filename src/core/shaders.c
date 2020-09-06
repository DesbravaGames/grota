
#include "require.h"

int success;
char infoLog[512];



int shader_compile_vertex(const char *shadersource) {
    printf("compiling vertex shader\n");

	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &shadersource, NULL);
    glCompileShader(vertex_shader);
    // check for shader compile errors
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        printf("%s,\n",infoLog);
    }
    return vertex_shader;
}

int shader_compile_fragment(const char *shadersource) {
    printf("compiling vertex shader");
	int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &shadersource, NULL);
    glCompileShader(fragment_shader);
    // check for shader compile errors
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        printf("%s,\n",infoLog);
        return 0;
    }
    return fragment_shader;
}

int shader_link_program(int vertex_shader,int fragment_shader) {
    printf("linking shader program");
	int shader_program=glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    // check for linking errors
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        printf("%s,\n",infoLog);
        return 0;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return shader_program;
}


int shader_create_program(const char *vertex_shader,const char * fragment_shader) {
    int vs=shader_compile_vertex(vertex_shader);
    if(!vs) return 0;
    int fs=shader_compile_fragment(fragment_shader);
    if(!fs) return 0;
    return shader_link_program(vs,fs);
}

void shader_uniform_int(int id_program,const char *name, int value){         
    glUniform1i(glGetUniformLocation(id_program, name), value); 
}
void shader_uniform_bool(int id_program,const char *name, bool value){         
    shader_uniform_int(id_program,name,value);
}
void shader_uniform_float(int id_program,const char *name, float value) {   
    glUniform1f(glGetUniformLocation(id_program, name), value); 
}
void shader_uniform_color(int id_program,const char *name, Color4f color) {   
    glUniform4f(glGetUniformLocation(id_program, name), color.r,color.g,color.b,color.a); 
}