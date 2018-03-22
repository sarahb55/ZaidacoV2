/*
 *  epoch_scale.cxx
 *  COLOR
 *
 *  Created by Sarah Block on 4/23/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "epoch_scale.h"


#define DAYS_ELAPSED "%d days" //Used for display of elapsed time.


/**
 * This method draws the epoch scale and takes three arguments.
 * w and h are the window width and height.
 * percent_complete is the scaled position of the frame and is a value between
 * 0.0 and 1.0
 * 
 * 
 */
void epoch_scale::draw_scale(int w, int h, double percent_complete)
{
	if(!_dt) //no data are loaded
		return;
	if(w < 0 || h < 0)
		return;
	
	float min_y = 8;
	float max_y = 10;
	
	glPushMatrix();
	
	glLoadIdentity();
	glViewport(0,0,w,h);
	glDisable (GL_DEPTH_TEST);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-0.6, 1.3, 0.0, 100.0, -1.0, 1.0); 
	if(_dt->size() > 1)
	{
		glColor3f(0.4, 0.4, 1.0);
		glRectf(0.0, min_y, percent_complete,  max_y); //Draw a blue rectangle for the first half
		
		glColor3f(1.0, 1.0, 1.0);
		glRectf(percent_complete, min_y, 1.0,  max_y); //Draw a white rectangle for the second half
		glLineWidth(2.0);
		
		glBegin(GL_LINES); //Draw vertical lines for each data set
		glColor3f(0.0, 0.0,0.0);
		for(int i = 0; i < _dt->size(); i++)
		{
			float ei = _dt->get_element_at(i)->epoch_internal();
			glVertex2f(ei, min_y);
			glVertex2f(ei, max_y);
		}
		glEnd();
	}
	glColor3f(1.0, 1.0, 1.0); //Set the color to white to write the text

	//Calculate the number of elapsed days.
	float current = _dt->get_element_at(_dt->size() - 1)->epoch_data_val().julian_date();
	float start = _dt->get_element_at(0)->epoch_data_val().julian_date();
	int days  = ceil ((current - start)*percent_complete);
	
	char blue[1024]; //Make a string to show the number of elapsed days.
	
	sprintf(blue,DAYS_ELAPSED, days);
	print_string(1.0f, max_y + 2.0f,  blue);

	print_string(0.0f, min_y - 4.0f,  _dt->get_element_at(0)->epoch_data_val().mon_day_yr_str().c_str());
	if(_dt->size() > 1)
	{
		print_string(0.0f, max_y + 2.0f,  _dt->get_current()->epoch_data_val().mon_day_yr_str().c_str());
		print_string(1.0f, min_y - 4.0f, _dt->get_element_at(_dt->size() - 1)->epoch_data_val().mon_day_yr_str().c_str());
	}
	glLineWidth(1.0);


	glPopMatrix();

}
