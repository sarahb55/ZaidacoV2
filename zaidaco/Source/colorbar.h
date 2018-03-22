#ifndef COLOR_BAR_H_INCLUDED
#define COLOR_BAR_H_INCLUDED

/*
 *  colorbar.h
 *  
 *	Purpose: This is a class to store the user input related to the color scale
 *  and use this to draw the scale onto the screen.
 *
 *  Created by Sarah Block on 4/26/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */

#include <string>
using std::string;
#include "colorbartext.h"
#include "gvutils.h"
#include <stdio.h>
#include <stdlib.h>




#include <FL/gl.h>
#include <FL/glut.h>
/**
 * Small class to hold a set of color values.
 */


class color {
	public:
	color(){}
	~color(){}
	GLfloat r,g,b;
	color &operator=(color &rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
		return *this;
	}
	
};

class colorbar{
	public:
		/*Constructor*/
		colorbar();
		/*Destructor*/
		~colorbar(){}
					
		
		/*
		 * Set and get methods used by the colorbarui to show
		 * and edit data values.
		 */
		 
		 /**
		  * Sets and gets the number of tick marks
		  */
		int get_ticks(){return ticks;}
		void set_ticks(int n);				
		
		/**
		 * Set the color of a data point based on its value and the
		 * other settings of the program.
		 * This method is used by the map_builder to set up all of the 
		 * color arrays. It is also used by the colorbar to draw the
		 * scale. It works by calculating the color value based on
		 * the user input to the colorbarui
		 */
		color get_color(double value, double vmax, double vmin);
		color get_color(float v);
		
		/**
		 * This method is called to draw the color scale into the window
		 * w and h are the width and height of the window.
		 */
		void draw_color_scale(int w, int h);
		
		
		/**
		 * These are the get and set methods used by colorbarui
		 * to set and get the user settings realted to color.
		 */
		float get_minvalue();
		float get_maxvalue();
		
		void set_minvalue(float val);
		void set_maxvalue(float val);
		
		void set_units(const char *units){unit = units;}
		const char * get_units(){return unit.c_str();}
		void set_title(const char* t){title = t;}
		const char * get_title(){return title.c_str();}
		
		void set_color_scheme(const char *color_scheme){_color_scheme = color_scheme;}
		const char *get_color_scheme(){return _color_scheme.c_str();}
		
		void show();
		void hide();
		
		bool get_show(){return _hide;}
		void vertical(bool v){_vertical = v;}
		bool vertical(){return _vertical;}
		
		void set_above_max(char *val);
		void set_below_max(char *val);
		
		void mask_above(bool val){_mask_above = val;}
		void toggle_mask_below(bool val){_mask_below = val;}

		void mask_max(float val){_mask_max = val; }
		void mask_min(float val){_mask_min = val; }
		
		float mask_max(){return _mask_max; }
		float mask_min(){return _mask_min; }

		

	
	
	private:
		
		/**
		 * This stores the users choice of color table. 
		 * Refer to colorbartext.h for a list.
		 */
		string _color_scheme;
		
		/**
		 * width and length of the window
		 */
		int length;
		int width;
		
		/**
		 * Maximum and minimum values shown on the color scale.
		 */
		double min_value;
		double max_value;
		
		/**
		 * Maximum and minimum values of the data set.
		 */
		double data_max;
		double data_min;
		
		/**
		 * String representation of the units
		 */
		string unit;
		string label;
		//int decimal_places;
		//int n_axis_labels;
		float position_x; 
		float position_y;
		//int font;
		//float text_color[4];
		int ticks;
		string title;
		/*
		 * Varaible to store whether to show or hide scale
		 */
		bool _hide;
		
		/*
		 * Variable to store orientation of scale.
		 */
		bool _vertical;
		
		/**
		 * Variables for color masking not yet
		 * implemented.
		 */
		color _above_max;
		color _below_min;
		
		bool _mask_above;
		bool _mask_below;
		
		double _mask_max;
		double _mask_min;
		
				


};



#endif