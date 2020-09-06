#include "require.h"

#define QUAD_NEW {COLOR_WHITE,{1.0,1.0}}

typedef struct {
    Color4f color;
    Vec2 size;
} Quad;


const char *quad_vertex_shader= 
    "#version 300 es \n"
    "in lowp vec2 position;"
    "void main() {"
    "     gl_Position = vec4(position,0.0f, 1.0f);"
    "}";

const char *quad_fragment_shader= 
    "#version 300 es \n"
    "out lowp vec4 FragColor;"
    "void main() {FragColor = vec4(1.0);}";


unsigned int quad_vao,quad_vbo,quad_shader_program;


bool quad_init() {
    quad_shader_program=shader_create_program(quad_vertex_shader,quad_fragment_shader);
    if(quad_shader_program==0) return false;
    glBindAttribLocation(quad_shader_program, SHADER_VERTEX_ATTRIBUTE,"position");
  // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5, -0.5,  // left top 
        -0.5,  0.5,  // left bottom 
        0.5, 0.5, // right bottom 
        0.5, 0.5,  // right bottom 
        0.5, -0.5,  // right top 
        -0.5, -0.5, // left top 
    };

    glGenVertexArrays(1, &quad_vao);
    glGenBuffers(1, &quad_vbo);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(quad_vao);

    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute

    glVertexAttribPointer(SHADER_VERTEX_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(SHADER_VERTEX_ATTRIBUTE);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
     glBindVertexArray(0);
     return true;
}


void quad_draw(Quad *quad) {
  // render the quad
    glUseProgram(quad_shader_program); 

    glBindVertexArray(quad_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void quad_destroy() {
	 // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &quad_vao);
    glDeleteBuffers(1, &quad_vbo);
}