#include "colorbar.h"

/*
 *  colorbar.cxx
 *  
 *	Purpose: This is a class to store the user input related to the color scale
 *  and use this to draw the scale onto the screen.
 *
 *  Created by Sarah Block on 1/26/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */

colorbar::colorbar()
{
	ticks = 4;
	min_value = 0.32;
	max_value = 1.9;
	//color_choice = RAINBOW;
	_color_scheme = COLOR_RAINBOW;
	title = "";
	_hide = false;
	_vertical = true;

}
void colorbar::show()
{
	_hide = false;

}
void colorbar::hide()
{
	_hide = true;
}
void colorbar::set_ticks(int t)
{
	if(t >= 0 && t < MAX_TICKS)
		ticks = t;		
}

float colorbar::get_minvalue()
{
	return min_value;
}

float colorbar::get_maxvalue()
{
	return max_value;
}

void colorbar::set_minvalue(float val)
{
	if(val < max_value)
		min_value = val;
}


void colorbar::set_maxvalue(float val)
{
	if(val > min_value)
		max_value = val;

}

color colorbar::get_color(float v)
{
	return get_color(v, max_value, min_value);

}

/**

Color table adapted from code in SurfaceGeometry.c as part of GLUT Basics Apple example -- credit given to 
*/

color colorbar::get_color(double v, double vmax, double vmin)
{		
	color c;
	if(isnan(v))
	{
		c.r = 0.0;
		c.g = 0.0; 
		c.g = 0.0;
		return c;
	}
		
	double  dv = vmax - vmin;
		
	if(_color_scheme == COLOR_RAINBOW){
		if (v < (vmin + 0.25 * dv)) {
			c.r = 0;
			c.g = 4 * (v - vmin) / dv;
			c.b = 1;
		} else if (v < (vmin + 0.5 * dv)) {
			c.r = 0;
			c.g = 1;
			c.b = 1 + 4 * (vmin + 0.25 * dv - v) / dv;
		} else if (v < (vmin + 0.75 * dv)) {
			c.r = 4 * (v - vmin - 0.5 * dv) / dv;
			c.g = 1;
			c.b = 0;
		} else {
			c.r = 1;
			c.g = 1 + 4 * (vmin + 0.75 * dv - v) / dv;
			c.b = 0;
		}
		
	}
	else if (_color_scheme == COLOR_RAINBOW_2){
	  if (v < (vmin + dv / 6.0)) {
         c.r = 1; 
         c.g = 6 * (v - vmin) / dv;
         c.b = 0;
      } else if (v < (vmin + 2.0 * dv / 6.0)) {
         c.r = 1 + 6 * (vmin + dv / 6.0 - v) / dv;
         c.g = 1;
         c.b = 0;
      } else if (v < (vmin + 3.0 * dv / 6.0)) {
         c.r = 0;
         c.g = 1;
         c.b = 6 * (v - vmin - 2.0 * dv / 6.0) / dv;
      } else if (v < (vmin + 4.0 * dv / 6.0)) {
         c.r = 0;
         c.g = 1 + 6 * (vmin + 3.0 * dv / 6.0 - v) / dv;
         c.b = 1;
      } else if (v < (vmin + 5.0 * dv / 6.0)) {
         c.r = 6 * (v - vmin - 4.0 * dv / 6.0) / dv;
         c.g = 0;
         c.b = 1;
      } else {
         c.r = 1;
         c.g = 0;
         c.b = 1 + 6 * (vmin + 5.0 * dv / 6.0 - v) / dv;
      }

	
	}
	else if (_color_scheme == COLOR_RAINBOW_3){
		 if (v < (vmin + 0.25 * dv)) {
         c.r = 0;
         c.g = 4 * (v - vmin) / dv;
         c.b = 1 - c.g;
      } else if (v < (vmin + 0.5 * dv)) {
			c.r = 4 * (v - vmin - 0.25 * dv) / dv;
         c.g = 1 - c.r;
         c.b = 0;
      } else if (v < (vmin + 0.75 * dv)) {
         c.g = 4 * (v - vmin - 0.5 * dv) / dv;
			c.r = 1 - c.g;
         c.b = 0;
      } else {
         c.r = 0;
         c.b = 4 * (v - vmin - 0.75 * dv) / dv;
			c.g = 1 - c.b;
      }

	}
	else if (_color_scheme == COLOR_RAINBOW_4){
		      if (v < (vmin + dv / 3)) {
         c.b = 3 * (v - vmin) / dv;
			c.g = 0;
         c.r = 1 - c.b;
      } else if (v < (vmin + 2 * dv / 3)) {
         c.r = 0;
         c.g = 3 * (v - vmin - dv / 3) / dv;
         c.b = 1;
      } else {
         c.r = 3 * (v - vmin - 2 * dv / 3) / dv;
         c.g = 1 - c.r;
		 c.b = 1;
      }
	}
	else if (_color_scheme == COLOR_RAINBOW_5){
		 if (v < (vmin + 0.2 * dv)) {
         c.r = 0;
         c.g = 5 * (v - vmin) / dv;
         c.b = 1;
      } else if (v < (vmin + 0.4 * dv)) {
         c.r = 0;
         c.g = 1;
         c.b = 1 + 5 * (vmin + 0.2 * dv - v) / dv;
      } else if (v < (vmin + 0.6 * dv)) {
         c.r = 5 * (v - vmin - 0.4 * dv) / dv;
         c.g = 1;
         c.b = 0;
      } else if (v < (vmin + 0.8 * dv)) {
         c.r = 1;
         c.g = 1 - 5 * (v - vmin - 0.6 * dv) / dv;
         c.b = 0;
      } else {
         c.r = 1;
         c.g = 5 * (v - vmin - 0.8 * dv) / dv;
         c.b = 5 * (v - vmin - 0.8 * dv) / dv;
      }

	}
	else if (_color_scheme == COLOR_RAINBOW_6)
	{
		      if (v < (vmin + 0.25 * dv)) {
         c.r = 0;
         c.g = 4 * (v - vmin) / dv;
         c.b = 1;
      } else if (v < (vmin + 0.5 * dv)) {
         c.r = 0;
         c.g = 1;
         c.b = 1 - 4 * (v - vmin - 0.25 * dv) / dv;
      } else if (v < (vmin + 0.75 * dv)) {
			c.r = 4 * (v - vmin - 0.5 * dv) / dv;
         c.g = 1;
         c.b = 0;
      } else {
         c.r = 1;
			c.g = 1;
         c.b = 4 * (v - vmin - 0.75 * dv) / dv;
      }
	}
	else if (_color_scheme == COLOR_RAINBOW_7)
	{
		 if (v < (vmin + 0.5 * dv)) {
         c.r = 0.0;
         c.g = 2 * (v - vmin) / dv;
         c.b = 1 - 2 * (v - vmin) / dv;
      } else {
         c.r = 2 * (v - vmin - 0.5 * dv) / dv;
         c.g = 1 - 2 * (v - vmin - 0.5 * dv) / dv;
         c.b = 0.0;
      }

	}
	else if (_color_scheme == COLOR_RAINBOW_8)
	{
		 if (v < (vmin + 0.5 * dv)) {
         c.r = 1.0;
         c.g = 1 - 2 * (v - vmin) / dv;
         c.b = 2 * (v - vmin) / dv;
      } else {
         c.r = 1 - 2 * (v - vmin - 0.5 * dv) / dv;
         c.g = 2 * (v - vmin - 0.5 * dv) / dv;
         c.b = 1.0;
      }

	}
	else if (_color_scheme == COLOR_BLUE_TO_RED){
	
		c.r = (v - vmin) / dv;
		c.g = 0;
		c.b = (vmax - v) / dv;
	
	}
	else if(_color_scheme == TANGERINE)
	{
		color c1, c2;
		c1.r = 200 / 255.0; c1.g =  60 / 255.0; c1.b =   0 / 255.0;
		c2.r = 250 / 255.0; c2.g = 160 / 255.0; c2.b = 110 / 255.0;
      c.r = (c2.r - c1.r) * (v - vmin) / dv + c1.r;
      c.g = (c2.g - c1.g) * (v - vmin) / dv + c1.g;
      c.b = (c2.b - c1.b) * (v - vmin) / dv + c1.b;
	}
	else if(_color_scheme == ORANGE)
	{
		color c1, c2, c3;
		c1.r =  55 / 255.0; c1.g =  55 / 255.0; c1.b =  45 / 255.0;
		c2.r = 200 / 255.0; c2.g =  60 / 255.0; c2.b =   0 / 255.0; 
//		c2.r = 235 / 255.0; c2.g =  90 / 255.0; c2.b =  30 / 255.0;
		c3.r = 250 / 255.0; c3.g = 160 / 255.0; c3.b = 110 / 255.0;
		float ratio = 0.4;
		float vmid = vmin + ratio * dv;
		if (v < vmid) {
      	c.r = (c2.r - c1.r) * (v - vmin) / (ratio*dv) + c1.r;
      	c.g = (c2.g - c1.g) * (v - vmin) / (ratio*dv) + c1.g;
      	c.b = (c2.b - c1.b) * (v - vmin) / (ratio*dv) + c1.b;
		} else {
         c.r = (c3.r - c2.r) * (v - vmid) / ((1-ratio)*dv) + c2.r;
         c.g = (c3.g - c2.g) * (v - vmid) / ((1-ratio)*dv) + c2.g;
         c.b = (c3.b - c2.b) * (v - vmid) / ((1-ratio)*dv) + c2.b;
		}

	
	}
	else if(_color_scheme == YELLOW_RED)
	{
		   c.r = 1;
		   c.g = 1 - (v - vmin) / dv;
           c.b = 0;
	}
	else if(_color_scheme == COLOR_GRAYSCALE){
		c.r = (v - vmin) / dv;
		c.b = c.r;
		c.g = c.r;
	
	}
	else if(_color_scheme == COLOR_GRAY){
		c.r = 0.5;
		c.b = 0.5;
		c.g = 0.5;
	
	}
	else if(_color_scheme == COLOR_BLUE)
	{
		c.r = 0.53;
		c.b = 0.81;
		c.g = 0.95;
	}
	else if(_color_scheme == THE_BLUES)
	{
		c.r = (v - vmin) / (vmax - vmin);
      c.g = c.r;
      c.b = 1;
	
	}
	else if(_color_scheme == YELLOW_GREEN)
	{
	  c.r = (v - vmin) / (vmax - vmin);
      c.g = 1;
      c.b = 0;
	
	}
	else if (_color_scheme == GREEN_PINK)
	{
	  c.r = (v - vmin) / (vmax - vmin);
      c.g = (vmax - v) / (vmax - vmin);
      c.b = c.r;
	}
				

	return c;
}


void colorbar::draw_color_scale(int w, int h)
{
	
	glPushMatrix();
	if(_hide)
		return;
	glLoadIdentity();
	glViewport(0,0,w,h);
	glDisable (GL_DEPTH_TEST);
	
		
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	float xv = (float)w/300.0;
	float yv = (float)h/200.0;
	if(_vertical){
		
		glTranslatef(-1.6,0.1,0.0);
		glRotatef(90, 0.0,0.0,1.0);	
		
	}
	else{
		glTranslatef(0.0,0.3,0.0);
	}
		
	glOrtho(-1.0, 4*xv - 1.0,-1.5, 4*yv - 1.0, -1.0, 1.0);
	
	glColor3f (1.0, 0.0, 1.0);
	//glRectf(-0.9,-0.9, 0.8, -0.7);
	float deltar = 1.7/1024.0;
	float xpos = -0.9;
	float vmax = 0.8;
	float  vmin = -0.9;
		
	
	for(int i=0; i < 1024; i++)
	{
		
		color c = get_color(xpos, vmax, vmin);
		glColor3f(c.r, c.g, c.b);
		glRectf(xpos,-0.9, xpos+deltar, -0.7);
		xpos += deltar;
	
	}
	
	glColor3f (1.0, 1.0, 1.0);

	glBegin(GL_LINES);
		glVertex2f(-0.9,-0.9);
		glVertex2f(-0.9,-0.70);
		glVertex2f(0.8,-0.9);
		glVertex2f(0.8,-0.7);
		glVertex2f(-0.9,-0.7);
		glVertex2f(0.8,-0.7);
		glVertex2f(-0.9,-0.9);
		glVertex2f(0.8,-0.9);		
	glEnd();
	
	char min[256];
	char max[256];	
	//float offset =0.0;
	
	if(fabs(max_value) < 0.01){
		sprintf(max, "%1.2E",max_value); 
		sprintf(min, "%1.2E %s",min_value, unit.c_str()); 
	}
	else{
		   
		   sprintf(max, "%1.2f",max_value); 
		   sprintf(min, "%1.2f %s",min_value, unit.c_str()); 
	}
	
	if(_vertical){
	
		float offset = -0.2;
		float delta = 1.7/((float)ticks + 1.0f);
		float start = -0.9;
		for(int i = 0; i <= ticks + 1; i++){

		glBegin(GL_LINES);
			glVertex2f(start,-0.9);
			glVertex2f(start,-0.95);
			start += delta;
		glEnd();
		
		}

		print_string(-0.92, -1.0,min);
		print_string(.75, -1.0, max);
		print_string(-1.05 + offset, -0.7, title.c_str());
	
	}
	else
	{
		float offset = 0.0;
		float delta = 1.7/((float)ticks + 1.0f);
		float start = -0.9;
		for(int i = 0; i <= ticks+ 1; i++){

		glBegin(GL_LINES);
			glVertex2f(start,-0.7);
			glVertex2f(start,-0.65);
			start += delta;
		glEnd();

		print_string(-0.95 + offset, -0.55,min);
		print_string(.6 + offset, -0.55,max);
	}
		
	print_string(-.9 + offset, -1.15, title.c_str());
	
	}

	glPopMatrix();
	

}










