#include "core/mathematics.h"
#include "core/colors.h"
#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb_image.h"
#include "camera.h"
#include "shaders.h"
#include "renderer.h"
 
/// SHADERSSSSSSS

const char *renderer_vertex_shader= SHADER_INLINE(
    uniform mat4 matrix;
    in vec3 a_vertex;
    in vec2 a_textcoord;
    out vec2 texture_coordinates;
    void main() {
         gl_Position = matrix * vec4(a_vertex, 1.0f);
		texture_coordinates= vec2(a_textcoord.x, a_textcoord.y);
    }
);
   
    
const char *renderer_fragment_shader= SHADER_INLINE(
    uniform vec4 color;
    uniform sampler2D texture;
    in vec2 texture_coordinates;
    out vec4 FragColor;
    void main() {
		FragColor=color*texture2D(texture,texture_coordinates);
	}
);
   
GLuint renderer_attribute_vertex;
GLuint renderer_attribute_textcoord;
GLuint renderer_uniform_color;
GLuint renderer_uniform_texture;
GLuint renderer_uniform_matrix;
GLuint renderer_shader_program;

bool render_shader_initialized=false;

bool renderer_shader_init() {
    if(!render_shader_initialized) {
        render_shader_initialized=true;
        renderer_shader_program=shader_create_program(renderer_vertex_shader,renderer_fragment_shader);
        if(renderer_shader_program==0) return false;  
        
        renderer_uniform_color=glGetUniformLocation(renderer_shader_program, "color");
        renderer_uniform_matrix=glGetUniformLocation(renderer_shader_program, "matrix");
        renderer_uniform_texture=glGetUniformLocation(renderer_shader_program, "texture");
        renderer_attribute_vertex=glGetAttribLocation(renderer_shader_program,"a_vertex");
        renderer_attribute_textcoord=glGetAttribLocation(renderer_shader_program,"a_textcoord");

        return true;
    } else
    return false;
}

GLuint load_texture(const char *filename) {
    GLuint texture_id;
   	 // tell stb_image.h to flip loaded texture's on the y-axis.
    stbi_set_flip_vertically_on_load(true);
    int width, height, nr_channels; 
	GLubyte *data = stbi_load(filename, &width, &height, &nr_channels, 3);
	if(!data) return 0;
	
    glGenTextures(1, &texture_id);
    
    printf("texture loaded! id:%u \nfile: %s \n",texture_id,filename);
    
    printf("%d x %d - %d channels \n",width,height,nr_channels);
	
    glBindTexture(GL_TEXTURE_2D, texture_id); 
    
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
    return texture_id;
}

bool renderer_texturize(Renderer *renderer,const char *filename) {
    renderer->texture_id=load_texture(filename);
    return true;
}
bool renderer_init(Renderer *renderer,RendererMesh renderer_data) {
    // configurando shader
    if(!renderer_shader_init()) return false;

	glUniform1i(renderer_uniform_texture, 0);

    glGenVertexArrays(1, &renderer->VAO);
    glGenBuffers(1, &renderer->VBO);
    glGenBuffers(1, &renderer->EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(renderer->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, renderer->VBO);
    glBufferData(GL_ARRAY_BUFFER, renderer_data.vertices_count*sizeof(VertexData), renderer_data.vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(renderer_attribute_vertex, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
    glEnableVertexAttribArray(renderer_attribute_vertex);
    // texture coord attribute
    
    glVertexAttribPointer(renderer_attribute_textcoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(Vec3)));
    glEnableVertexAttribArray(renderer_attribute_textcoord);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, renderer_data.indices_count*sizeof(GLuint), renderer_data.indices, GL_STATIC_DRAW);
    renderer->indices_count=renderer_data.indices_count;
    printf("created a Renderer with %d indices\n",renderer->indices_count);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
     glBindVertexArray(0);
     return true;
}

	

void renderer_draw(Renderer *renderer,Camera *camera) {
  // render the renderer   
    glUseProgram(renderer_shader_program); 
    
	if(renderer->texture_id) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderer->texture_id);
	}
    
	Mat4 shader_matrix=camera_generate_shader_matrix(camera,renderer->matrix);
	glUniformMatrix4fv(renderer_uniform_matrix, 1, GL_FALSE, (GLfloat*)&shader_matrix);
	glUniform4fv(renderer_uniform_color,1, (GLfloat*) &(renderer->color));
    glBindVertexArray(renderer->VAO);
	glDrawArrays(GL_TRIANGLES,0,6);
    
	glDrawElements(GL_TRIANGLES, renderer->indices_count, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    
}

void renderer_destroy(Renderer *renderer) {
	 // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &renderer->VAO);
    glDeleteBuffers(1, &renderer->VBO);
    glDeleteBuffers(1, &renderer->EBO);
}

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
    RendererMesh rend_data;
    rend_data.vertices=quad_vertices;
    rend_data.vertices_count=sizeof(quad_vertices)/sizeof(VertexData);
    rend_data.indices=quad_indices;
    rend_data.indices_count=sizeof(quad_indices)/sizeof(GLuint);
    return renderer_init(quad,rend_data);
}
