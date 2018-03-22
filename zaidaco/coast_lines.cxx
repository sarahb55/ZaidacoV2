/*
 *  coast_lines.cxx
 *  COLOR
 *
 *  Created by Sarah Block on 2/26/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "coast_lines.h"


GLuint framebuffer, texture;
void init_coastlines()
{
	
	GLint val;
	
    if (glewInit() != GLEW_OK) exit(0);
	
	if (GLEW_EXT_framebuffer_object){
		glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE_EXT, &val);	
		printf("GL_MAX_RENDERBUFFER_SIZE_EXT = %d", val);
		GLenum status;
		glGenFramebuffersEXT(1, &framebuffer);
		
		// Set up the FBO with one texture attachment
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, 
					 					 GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, 
										GL_TEXTURE_2D, texture, 0);
		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		check_GL_errors ("Bigger size:");
		if (status != GL_FRAMEBUFFER_COMPLETE_EXT){
			exit(1);
		}
		
		//Draw coastlines into offscreen buffer
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		
		glDisable(GL_DEPTH);
		glDisable(GL_TEXTURE_2D);
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glPushMatrix();
		
		glViewport(0, 0, 256, 256);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D (0.0, 360.0, 
					-90.0, 90.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		glClearColor(1.0, 1.0, 1.0, 0.0);
		char line[256];
		FILE * file;
		float lat, lon;
		
		file = fopen("/Users/sblock/COLOR/coastlines.xy", "r");
		if (file==NULL) {fputs ("File error",stderr); exit (1);}
	
		while(!feof(file)){
			fgets(line, 256, file);
			//printf("%s", line);
			glBegin(GL_LINE_STRIP);
			glColor4f (0.0, 0.0,0.0, 1.0);
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
		
		glPopMatrix();
		// Make the window the target
		
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glGenerateMipmapEXT(GL_TEXTURE_2D);
		
		glDisable (GL_LINE_SMOOTH);
		glDisable (GL_BLEND);
		
	}
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.0, 0.0, 0.0);
}

//Function to use if above doesn't work
void plot_coastlines(int w, int h)
{
	

	//glEnable (GL_LINE_SMOOTH);
	//glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH);
	glPushMatrix();
		
	
	
	glViewport(0, 0, w, w);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (0.0, 359.0, 
        -90.0, 90.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	 glLineWidth(0.5);

	char line[256];
	FILE * file;
	float lat, lon;
	  
	file = fopen("/Users/sblock/COLOR/coastlines.xy", "r");
	if (file==NULL) {fputs ("File error",stderr); exit (1);}
	
	while(!feof(file)){
		fgets(line, 256, file);
		//printf("%s", line);
		glBegin(GL_LINE_STRIP);
		glColor4f (0.0, 0.0,0.0, 1.0);
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

 glLineWidth(1.0);

   glPushMatrix();
      glBegin (GL_LINES);
	   glColor4f (0.0, 0.0,0.0, 1.0);
	for(int i = 0; i < 360; i += 15){
      glVertex2f ((float) i, -90);
      glVertex2f ((float) i, 90);
	}
   glEnd ();
   
   
   glPushMatrix();
   for(int i = -90; i <= 90; i += 15){
     glBegin (GL_LINES);
	  glColor4f (0.0, 0.0,0.0, 1.0);
      glVertex2f (0, i);
      glVertex2f (360, i);
   glEnd ();
   }
   
    glBegin (GL_LINES);
	  glColor4f (0.0, 0.0,1.0, 1.0);
      glVertex2f (0, 0);
      glVertex2f (360, 0);
   glEnd ();

   glPopMatrix();

  
	glFlush();
	
	unsigned width      =  glutGet(GLUT_WINDOW_WIDTH);
	unsigned height     =  glutGet(GLUT_WINDOW_HEIGHT);
	unsigned bits_per_pixel     =  4;
	cout << "bits_per_pixel " << bits_per_pixel  << endl;
	GLenum   format =   GL_RGBA;
	GLubyte* pdata;

	// allocate memory to store image data
	pdata = new GLubyte[width*height*bits_per_pixel];

	// read from front buffer
	glReadBuffer(GL_FRONT);

	// read pixel data
	glReadPixels(0,0,width ,height,format,GL_UNSIGNED_BYTE,pdata);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

#ifdef GL_VERSION_1_1
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);
#endif

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#ifdef GL_VERSION_1_1

   gluBuild2DMipmaps(GL_TEXTURE_2D, bits_per_pixel , width, height, format, GL_UNSIGNED_BYTE, pdata);
#else
   gluBuild2DMipmaps(GL_TEXTURE_2D, bits_per_pixel , width, height, format, GL_UNSIGNED_BYTE, pdata);
#endif

	delete [] pdata;
	
	glPopMatrix();

}



