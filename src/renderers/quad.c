#include "core/mathematics.h"
#include "core/colors.h"
#include "libs/stb_image.h"
#include "camera.h"
 
#define QUAD_NEW {COLOR_WHITE,MAT4_IDENTITY,0}


typedef struct {
    Color4f color;
	Mat4 matrix;
    GLuint texture_id;
} Quad;


const char *quad_vertex_shader= SHADER_INLINE(
    uniform mat4 matrix;
    in vec2 a_vertex;
    in vec2 a_textcoord;
    out vec2 texture_coordinates;
    void main() {
         gl_Position = matrix * vec4(a_vertex,0.0f, 1.0f);
		texture_coordinates= vec2(a_textcoord.x, a_textcoord.y);
    }
);
   
    
const char *quad_fragment_shader= SHADER_INLINE(
    uniform vec4 color;
    uniform sampler2D texture;
    in vec2 texture_coordinates;
    out vec4 FragColor;
    void main() {
		FragColor=color*texture2D(texture,texture_coordinates);
	}
);
   
GLuint quad_attribute_vertex;
GLuint quad_attribute_textcoord;
GLuint quad_uniform_color;
GLuint quad_uniform_texture;
GLuint quad_uniform_matrix;

GLuint quad_vao,
		quad_vbo,
		quad_ebo,
		quad_shader_program;

 // set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
GLfloat quad_vbo_data[] = {
	// positions      // texture coords
	 0.5f,  0.5f,     1.0f, 1.0f, // top right
	 0.5f, -0.5f,     1.0f, 0.0f, // bottom right
	-0.5f, -0.5f,     0.0f, 0.0f, // bottom left
	-0.5f,  0.5f,     0.0f, 1.0f  // top left 
};
GLuint quad_indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};




bool quad_texturize(Quad *quad,const char *filename) {
	 // tell stb_image.h to flip loaded texture's on the y-axis.
    stbi_set_flip_vertically_on_load(true);
    GLuint width, height, nr_channels; 
	GLubyte *data = stbi_load(filename, &width, &height, &nr_channels, 3);
	if(!data) return false;
	
    glGenTextures(1, &(quad->texture_id));
    printf("texture loaded! id:%u \nfile: %s \n",quad->texture_id,filename);
    printf("%u x %u - %u channels \n",width,height,nr_channels);
	
    glBindTexture(GL_TEXTURE_2D, quad->texture_id); 
    
     // set the texture wrapping parameters
     // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load image, create texture and generate mipmaps
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //  glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
    // unbind texture to safe
    glBindTexture(GL_TEXTURE_2D, 0); 
    return true;
}
bool quad_init() {
    // configurando shader
    quad_shader_program=shader_create_program(quad_vertex_shader,quad_fragment_shader);
    if(quad_shader_program==0) return false;  
    
    quad_uniform_color=glGetUniformLocation(quad_shader_program, "color");
    quad_uniform_matrix=glGetUniformLocation(quad_shader_program, "matrix");
    quad_uniform_texture=glGetUniformLocation(quad_shader_program, "texture");
    quad_attribute_vertex=glGetAttribLocation(quad_shader_program,"a_vertex");
    quad_attribute_textcoord=glGetAttribLocation(quad_shader_program,"a_textcoord");
    
	glUniform1i(quad_uniform_texture, 0);

    glGenVertexArrays(1, &quad_vao);
    glGenBuffers(1, &quad_vbo);
    glGenBuffers(1, &quad_ebo);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(quad_vao);

    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vbo_data), quad_vbo_data, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(quad_attribute_vertex, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(quad_attribute_vertex);
    // texture coord attribute
    
    glVertexAttribPointer(quad_attribute_textcoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(quad_attribute_textcoord);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_indices), quad_indices, GL_STATIC_DRAW);
 
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
     glBindVertexArray(0);
     return true;
}

	

void quad_draw(Quad *quad,Camera *camera) {
  // render the quad   
    glUseProgram(quad_shader_program); 
    
	if(quad->texture_id) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, quad->texture_id);
	}
	Mat4 shader_matrix=camera_generate_shader_matrix(camera,quad->matrix);
	glUniformMatrix4fv(quad_uniform_matrix, 1, GL_FALSE, (GLfloat*)&shader_matrix);
	glUniform4fv(quad_uniform_color,1, (GLfloat*) &(quad->color));
    glBindVertexArray(quad_vao);
	//glDrawArrays(GL_TRIANGLES,0,6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void quad_destroy() {
	 // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &quad_vao);
    glDeleteBuffers(1, &quad_vbo);
    glDeleteBuffers(1, &quad_ebo);
}
