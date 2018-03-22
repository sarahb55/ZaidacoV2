
#ifndef EARTH_VIEW_UI_H
#define EARTH_VIEW_UI_H

/**
 *
 * earthviewui.h
 * 
 * Purpose: This implements the callbacks, widgets, 
 * other features of the main window of the user interface.
 *
 *  
 *  Created by Sarah Block on 1/6/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */
#include "coast_lines.h"
#include "colorbarui.h"
#include "colorbar.h"
#include "map_builder.h"
#include "animator.h"
#include "animateui.h"
#include "fileloader/filereader.h"
#include "fileloader/data.h"
#include "fileloader/dataset.h"
#include "initialize.h"
#include "user_messages.h"


#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Roller.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Output.H>
#include <FL/fl_ask.H>

#include <sys/param.h>
#include <unistd.h>




#define TIMER_CB 1
/**
 * These are the callbacks for when the 
 * user adjust features in the user interface.
 * They in turn call methods in either the 
 * animator, colorbar, or map_builder and 
 * if necessary redraw the screen to show changes.
 *

/**
 * Resets the zoom in the map_builder
 */
extern void on_zoom_cb(Fl_Value_Slider*, void*);

/**
 * Resets the zoom in the map_builder
 */
extern void on_scale_cb(Fl_Value_Slider*, void*);

/**
 * Callback for the latitude roller.
 */
extern void adjust_latitude_cb(Fl_Roller*, void*);

/**
 * Callback for the longitude roller.
 */
extern void adjust_longitude_cb(Fl_Roller*, void*);


/**
 * Callback for the edit color menu item. 
 * Opens up the colorbarui interface.
 */
extern void edit_color_cb(Fl_Menu_*, void*);


/**
 * Callback for when the user clicks stop.
 * 
 */
extern void on_stop_cb(Fl_Widget *o, void*v);

/**
 * Callback for when the user clicks play.
 * It starts the glutTimer and sets the animator
 * to play.
 * 
 */
extern void on_play_cb(Fl_Widget *o, void*v);

/**
 * Callback for when the user clicks pause.
 * It stops the glutTimer
 * 
 */
extern void on_pause_cb(Fl_Widget *o, void*v);

/**
 * Callback for when the user clicks next.
 * Displays the next frame if there are more
 * than one.
 */
extern void on_next_cb(Fl_Widget *o, void*v);


/**
 * Callback for when the user clicks previous.
 * Displays the previous frame if there are more
 * than one.
 */

extern void on_previous_cb(Fl_Widget *o, void * v);
/**
 * Callback for when the user clicks the
 * menu item load data set.
 * Opens a file loader and diaplys the
 * data set opened. On error displays 
 * error messages.
 */
extern void load_data_set_cb(Fl_Widget *o, void * v);

/*
 * Opens a file loader and oens multiple datasets for
 * when the user selects the menu item.
 */
extern void load_data_sets_cb(Fl_Widget *o, void*v);

/*
 * Clears the data set currently shown on the screen
 * callback for when the user selects it from the 
 * Data menu
 */
extern void clear_data_set_cb(Fl_Widget *o, void*v);

/*
 * Clears all of the data sets
 * callback for when the user selects it from the 
 * Data menu
 */
extern void clear_all_data_sets_cb(Fl_Widget *o, void*v);

/**
 * Sets the variable lighting to false in the mapbuilder
 */
extern void toggle_lighting_cb(Fl_Widget *o, void*v);

/**
 * Sets the variable solid to false in the mapbuilder
 */
extern void toggle_wireframe_cb(Fl_Widget *o, void*v);

/**
 * Will display x-y-z axes
 */
extern void toggle_axes_cb(Fl_Widget *o, void*v);

/**
 * Will hide or show coastlines.
 */
extern void toggle_coastlines_cb(Fl_Widget *o, void*v);

/**
 * Will hide or show epoch.
 */
extern void toggle_epoch_cb(Fl_Widget *o, void*v);
//extern void adjust_interp_cb(Fl_Value_Slider*o, void*v);
extern void adjust_timer_cb(Fl_Value_Slider*o, void*v);
extern void next(void);

/**
 * This sets the number on the UI to show which rame is 
 * currently loaded.
 */
extern void set_frame(int i);

/**
 * This is called when the user slides the interpolation
 * slider. It resets the number of interpolated steps
 * in the animator.
 * 
 */
extern void adjust_interp_cb(Fl_Value_Slider*o, void*v);


/**
 * This is called when the user slides the timer
 * slider. It resets the number of timer speed.
 * 
 * 
 */
extern void adjust_timer_cb(Fl_Value_Slider *o, void*v);


/**
 * These are the glut callbacks
 *
 */

/**
 * this initializes variables, loads the coastline texture
 *
 */
void init();

/**
 * this function is empty but it prevents
 * a system bug from taking all the CPU while the
 * program is idling.
 */
void idle();

/**
 * This callback is used whenever the screen is refreshed.
 */
void display(void);

/**
 *  this is the callback for when the window is resized.
 */
void reshape(int w, int h);

/**
 * This is used to enter keyboard commands.
 */
void keyboard (unsigned char key, int x, int y);

/**
 * The system crashes without the mouse and motion callbacks.
 * They both are empty at the moment but may be programmed to 
 * spin the globe at a later date
 */
void mouse(int b, int s, int x, int y);
void motion(int x, int y);

/**
 * When the animation is running this callback is
 * called whenever the timer ticks.
 * It calls the animator method to calculate the next frame
 * when the animation is runnning.
 */
void timer(int value);

#ifdef __APPLE__
#include <unistd.h>
#endif



class earthviewui {
public:
  earthviewui(){}
  
  /**
   *
   * This is the method that builds the main window and displays it.
   * it requires argc and argv from main to work.
   * The pointers are the ones created in MapBuilder.cpp and
   * are used throughout the program
   */
  
  int show(int argc, char **argv, colorbar *cb, map_builder *mb, data *d, animator *anim);  
  
  private:
  
  /**
   * Called by show to create al of the parts of the main window.
   */
  
  Fl_Double_Window* make_window();
  /**
   * These are all of the menu items
   */
  Fl_Menu_Bar *main_menu;
  static Fl_Menu_Item menu_main_menu[];
  static Fl_Menu_Item *file_menu;
  static Fl_Menu_Item *map_features;


  
};
#endif //EARTH_VIEW_UI_H
