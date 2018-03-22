#ifndef COLORBARUI_H_INCLUDED
#define COLORBARUI_H_INCLUDED
/*
 *  colorbarui.h
 *  
 *	Purpose: This is a class to store the user input related to the color scale
 * and use this to draw the scale onto the screen.
 *
 *  Created by Sarah Block on 4/26/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Return_Button.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Value_Input.H>

#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/glut.h>
#include <FL/Fl_Group.H>
#include <FL/forms.H>	// changed for fltk

#include "colorbartext.h"
#include "gvutils.h"
#include "colorbar.h"
#include "map_builder.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;


	
class colorbarui {
public:
	colorbarui(int x, int y, int w, int h, const char *label)
	{
	
	}
	int handle(int event){return event;}
	
	/**
	 * Thiis method is called to draw the color scale with the 
	 * attributes as defined below into the left lower corner of a window
	 * of any size
	 */
	void draw(){}
	
	/**
	 * This s called by a method to show the user interface for the color scale
	 * arguments, argc and argv are from main, colorbar is a pointer to the class that
	 * holds the color scale data and map_builder is a pointer back to the program that
	 * draws the main image.
	 */
	int edit_settings(int argc, char **argv, colorbar *bar, map_builder *mb);
	
	
	private:
	
	/**
	 * Below are the callbacks for the buttons and sliders
	 */
	
	/**
	 * Callback that assigns a string value to units
	 */
	void setunits(Fl_Widget *o, void*);
	static void setunits_e(Fl_Widget *o, void*);
	
	/**
	 * Callbacks that sets a maximum color scale value.
	 * This value will not reset when the maximum is less than 
	 * the minimum.
	 */
	void setmaxvalue(Fl_Widget *o, void*);
	static void setmaxvalue_e(Fl_Widget *o, void*);
	
	
	
	/**
	 * Callbacks that sets a minimum color scale value.
	 * This value will not reset when the minimum is greater than 
	 * the maximum.
	 */
	void setminvalue(Fl_Widget *o, void*);
	static void setminvalue_e(Fl_Widget *o, void*);
	
	/**
	 * Callback that assigns a string value to title
	 */
	void settitle(Fl_Widget *o, void*);
	static void settitle_e(Fl_Widget *o, void*);

	
	/**
	 * Callbacks that sets the orientation
	 * to either horizontal or verticcal
	 */
	void vert(Fl_Round_Button *o, void*);
	static void vert_e(Fl_Widget *o, void*);
	
	void hori(Fl_Widget *o, void*);
	static void hori_e(Fl_Widget *o, void*);
	
		
	/**
	 * Callbacks that set the number of
	 * tick marks on the color scale
	 */
	void setticks(Fl_Widget*o, void*);
	static void setticks_e(Fl_Widget*o, void*);
	
	/**
	 * Callbacks to hide or show scale
	 */
	
	void show(Fl_Widget*o, void*);
	static void show_e(Fl_Widget*o, void*);

	void hide(Fl_Widget*o, void*);
	static void hide_e(Fl_Widget*o, void*);
	
	void color_scale(Fl_Input_Choice *o, void*);
	static void color_scale_e(Fl_Widget*o, void*);
	
	void static hide_window_e(Fl_Widget *o, void*);

	/**
	 * Not yet implemented callbacks to 
	 * mask color values.
	 */
	
	void mask_above(Fl_Widget *o, void*);
	static void mask_above_e(Fl_Widget *o, void*);
	
	void mask_above_value(Fl_Widget *o, void*);
	static void mask_above_value_e(Fl_Widget *o, void*);
	
	void mask_above_color(Fl_Widget *o, void*);
	static void mask_above_color_e(Fl_Widget *o, void*);

	void mask_below(Fl_Widget *o, void*);
	static void mask_below_e(Fl_Widget *o, void*);
	
	void mask_below_value(Fl_Widget *o, void*);
	static void mask_below_value_e(Fl_Widget *o, void*);
	
	void mask_below_color(Fl_Widget *o, void*);
	static void mask_below_color_e(Fl_Widget *o, void*);
	
	/**
	 * Member variables that are used to draw 
	 * sliders and buttons
	 */
	
	Fl_Input_Choice *units;
	Fl_Float_Input *flfi_min_value;
	Fl_Float_Input *flfi_ticks_value;
	Fl_Float_Input *flfi_max_value;
	Fl_Input *fli_title;
	Fl_Input_Choice *flic_number_display;
	Fl_Button *flb_apply;
	
};






#endif
