//-----------------------------------------------------------------------------------
//  Filename: main.cpp
//  E234 Homework 1 Part 3 Starter Code
//  Eric Chan (chan@merl.com)
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
//  Required C/C++ headers
//-----------------------------------------------------------------------------------
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <cmath>
#include <ctime>


//-----------------------------------------------------------------------------------
//  Required OpenGL, GLEW, and GLUT headers
//-----------------------------------------------------------------------------------
#define GLEW_STATIC
#include "GL/glew.h"
#include <GLUT/glut.h>


//-----------------------------------------------------------------------------------
//  Default font
//-----------------------------------------------------------------------------------
#define FONT GLUT_BITMAP_8_BY_13


//-----------------------------------------------------------------------------------
//  Default window dimensions
//-----------------------------------------------------------------------------------
static int g_windowWidth = 1024;
static int g_windowHeight = 1024;


//-----------------------------------------------------------------------------------
//  Display text <str> in a GL window of size <w,h> at location <x,y>
//-----------------------------------------------------------------------------------
static void DisplayString (int x, int y, int w, int h, char *str)
{
    float xx = ((float) x / (float) w) * 2.0f - 1.0f;
    float yy = ((float) y / (float) h) * 2.0f - 1.0f;
    glPushAttrib(GL_ENABLE_BIT);
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_1D);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glRasterPos2f(xx, yy);
        for ( ; *str; str++) glutBitmapCharacter(FONT, *str);
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
    glPopAttrib();
}


//-----------------------------------------------------------------------------------
//  Display formatted text string whose lower-left corner is at window-space position
//  <x,y> in a GL window of dimensions <w,h>. The text will have color <r,g,b>. The
//  <fmt> rules are identical to printf's rules.
//-----------------------------------------------------------------------------------
static void DisplayStringLeft (int x, int y, int w, int h, float r, float g, float b,
char *fmt, ...)
{
    va_list arglist;
    char buf[1024];
    va_start(arglist, fmt);
    vsprintf(buf, fmt, arglist);
    va_end(arglist);
    glPushAttrib(GL_CURRENT_BIT);
    {
        glColor3f(r, g, b);
        DisplayString(x, y, w, h, buf);
    }
    glPopAttrib();
}


//-----------------------------------------------------------------------------------
//  List of OpenGL extensions to test for
//-----------------------------------------------------------------------------------
#define EXTENSION_NAMES                         \
    FUNC(GLEW_ARB_depth_texture),               \
    FUNC(GLEW_ARB_fragment_program),            \
    FUNC(GLEW_ARB_fragment_shader),             \
    FUNC(GLEW_ARB_multisample),                 \
    FUNC(GLEW_ARB_occlusion_query),             \
    FUNC(GLEW_ARB_shader_objects),              \
    FUNC(GLEW_ARB_shading_language_100),        \
    FUNC(GLEW_ARB_shadow),                      \
    FUNC(GLEW_ARB_texture_cube_map),            \
    FUNC(GLEW_ARB_vertex_buffer_object),        \
    FUNC(GLEW_ARB_vertex_program),              \
    FUNC(GLEW_ARB_vertex_shader),               \
    FUNC(GLEW_ARB_draw_buffers),                \
    FUNC(GLEW_ATI_texture_float),               \
    FUNC(GLEW_EXT_blend_minmax),                \
    FUNC(GLEW_EXT_framebuffer_object),          \
    FUNC(GLEW_EXT_texture_rectangle),           \
    FUNC(GLEW_NV_occlusion_query),				\
	FUNC(GLEW_EXT_framebuffer_object)


//-----------------------------------------------------------------------------------
//  GLUT display callback function
//-----------------------------------------------------------------------------------
static void display (void)
{
    //----List of extensions supported by the GL driver
    #define FUNC(x) x
    static int extensionsPresent[] = {
        EXTENSION_NAMES,
    };
    #undef FUNC


    //----List of extension names
    #define FUNC(x) #x
    static const char *extensionNames[] = {
        EXTENSION_NAMES,
    };
    #undef FUNC


    //----Number of extensions
    const int k_numExtensions = sizeof(extensionNames) / sizeof(*extensionNames);


    //----Clear the color back buffer
    glClear(GL_COLOR_BUFFER_BIT);


    //----Report information about the available GL system
    DisplayStringLeft(10, g_windowHeight - 20, g_windowWidth, g_windowHeight, 1.0f,
    1.0f, 0.0f, "GL Version:   %s", glGetString(GL_VERSION));
    DisplayStringLeft(10, g_windowHeight - 40, g_windowWidth, g_windowHeight, 1.0f,
    1.0f, 0.0f, "GL Vendor:    %s", glGetString(GL_VENDOR));
    DisplayStringLeft(10, g_windowHeight - 60, g_windowWidth, g_windowHeight, 1.0f,
    1.0f, 0.0f, "GL Renderer:  %s", glGetString(GL_RENDERER));


    //----Test for supported OpenGL extensions
    int lineNum = g_windowHeight - 100;
    for (int i = 0; i < k_numExtensions; ++i, lineNum -= 20) {
        DisplayStringLeft(10, lineNum, g_windowWidth, g_windowHeight, 0.8f, 0.8f,
        0.8f, "%s:  %s", extensionNames[i] + 5, extensionsPresent[i] ? "yes" : "no");
    }
	
GLuint val;
	
     DisplayStringLeft(10, lineNum - 40, g_windowWidth, g_windowHeight, 1.0f,
    1.0f, 0.0f, "GL_MAX_TEXTURE_SIZE:  %d", val);





//Your code to use the contents of the FBO

			
glClear(GL_COLOR_BUFFER_BIT);
glClearColor(1.0, 1.0, 1.0, 0.0);
	glPushMatrix();
		
	
	
	glViewport(0, 0, g_windowWidth,g_windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-0.2, 1.2, 
        -0.2, 1.2, -1.2, 1.2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBegin(GL_QUADS);
		glColor4f(1.0, 0.0, 1.0, 1.0);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(0.0, 0.0);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(1.0, 0.0);
		glTexCoord2f(1.0, 1.0); 
		glVertex2f(1.0, 1.0);
		glTexCoord2f(0.0, 1.0);
		 glVertex2f(0.0, 1.0);

     glEnd();
	 glFlush();
	glDisable(GL_TEXTURE_2D);


//Tear down the FBO and texture attachment


    //----Swap the front and back buffers
    glutSwapBuffers();
}


//-----------------------------------------------------------------------------------
//  GLUT reshape callback function
//-----------------------------------------------------------------------------------
static void reshape (int w, int h)
{
    //----Update the window dimensions
    g_windowWidth = w;
    g_windowHeight = h;


    //----Set the GL viewport transformation (see Chapter 3 of the Red Book)
    glViewport(0, 0, w, h);
}


//-----------------------------------------------------------------------------------
//  GLUT keyboard callback function
//-----------------------------------------------------------------------------------
static void keyboard (unsigned char key, int x, int y)
{
    //----Exit the program if the user presses 'q' or Escape
    if (key == 'q' || key == 'Q' || key == 27) exit(0);
}
GLuint framebuffer, texture;

void init()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.0, 0.0, 0.0);
	GLint val;
	if (GLEW_EXT_framebuffer_object){
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &val);	
			
		GLenum status;
		glGenFramebuffersEXT(1, &framebuffer);
		
		// Set up the FBO with one texture attachment
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1024, 512, 0, 
					 					 GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, 
										GL_TEXTURE_2D, texture, 0);
		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		
		if (status != GL_FRAMEBUFFER_COMPLETE_EXT){
			exit(1);
		}
		
		
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glEnable (GL_LINE_SMOOTH);
		//glEnable (GL_BLEND);
		//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		
		//glDisable(GL_DEPTH);
		//glDisable(GL_TEXTURE_2D);
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glPushMatrix();
		
		
		
		glViewport(0, 0, 1024,512);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D (0.0, 359.0, 
					-90.0, 90.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLineWidth(1.0);
		glClearColor(1.0, 1.0, 1.0, 0.0);
		char line[256];
		FILE * file;
		float lat, lon;
		
		file = fopen("/Users/sblock/COLOR/coastlines.xy", "r");
		if (file==NULL) {fputs ("File error",stderr); exit (1);}
		
		while(!feof(file)){
			fgets(line, 256, file);
			printf("%s", line);
			glBegin(GL_LINE_STRIP);
			glColor4f (1.0, 1.0,1.0, 1.0);
			if(line[0] == '#'){
				//comment do nothing
			}
			else if(line[0] == '>'){
				glEnd();
				glBegin(GL_LINE_STRIP);
			}
			else{
				sscanf(line, "%f %f", &lon, &lat);
				//printf("READING: %f %f", lon, lat);
				glVertex2f(lon, lat);		
			}
		}
		
		glEnd();
		
		
		fclose(file);
		
		// Make the window the target
		
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glGenerateMipmapEXT(GL_TEXTURE_2D);
		
		glDisable (GL_LINE_SMOOTH);
		glDisable (GL_BLEND);
		
	}
	

}

//-----------------------------------------------------------------------------------
//  Starter code entry point
//-----------------------------------------------------------------------------------
int main (int argc, char **argv)
{
    //----Initialize GLUT
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(g_windowWidth, g_windowHeight);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("HW1 Part 3");


    //----Initialize GLEW and exit immediately if the initialization fails
    if (glewInit() != GLEW_OK) exit(0);

    
    //----Register GLUT callback functions
	
	init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
	if (GLEW_EXT_framebuffer_object){
		glDeleteTextures(1, &texture);
		glDeleteFramebuffersEXT(1, &framebuffer);
	}
    //----Return success
    return(0);
}
