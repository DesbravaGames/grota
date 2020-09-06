
Color4f window_bgcolor={0.2f, 0.3f, 0.3f, 1.0f};
Vec2 window_size={800,600};
bool window_show_fps=false;

bool window_init() {
	int glut_argc;char **glut_argv=NULL;
	glutInit(&glut_argc,glut_argv);

	 if(gladLoadGL()) {
        // you need an OpenGL context before loading glad
        printf("I did load GL with no context!\n");
        return false;
    }

	glutInitWindowSize(window_size.x, window_size.y);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutCreateWindow("Grota 3D");
    
 	if(!gladLoadGL()) {
        printf("Error Loading OpenGL With GLAD!\n");
        return false;
    }
    return true;
}
void window_update() {
	glutSwapBuffers();
	glClearColor(window_bgcolor.r,window_bgcolor.g,window_bgcolor.b,window_bgcolor.a);
    glClear(GL_COLOR_BUFFER_BIT);

	if(window_show_fps) {
		char window_title[100];
		snprintf(window_title,100," FPS: %d",time_fps());
		glutSetWindowTitle(window_title);
	}
	
}

void window_destroy() {
	// nenhum codigo ate agora
}
