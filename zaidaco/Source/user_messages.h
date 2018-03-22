#ifndef USER_MESSAGES_INLCUDED_H
#define USER_MESSAGES_INLCUDED_H
/*
 *  user_messages.h
 * 
 *  Purpose: Header file to store messages that appear on pop-up windows and errors.  
 *
 *  Created by Sarah Block on 9/6/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */


// File Loader Messages
#define FILE_LOADER_FILE_NOT_FOUND	"Unable to open %s, try using full path name to file."
#define FILE_LOADER_LOADING_FILES	"Please Wait Loading Data Sets..."
#define FILE_LOADER_LOADING_X_OF_Y_FILES "Loading %d of %d files to load."


// Map Builder Messages
#define MAP_BUILDER_MEMORY_ALLOCATION_ERROR "Unable to allocate memory, Exiting!"
#define MAP_BUILDER_Z_NORTH "z-axis 90 N"
#define MAP_BUILDER_X_0 "x-axis, 0"
#define MAP_BUILDER_Y_90_EAST "y-axis, 90 East"

//Main Menu Text
#define UI_FONT_SIZE 14
#define UI_FILE_MENU_FILE "File"
#define UI_FILE_MENU_QUIT "Quit"
#define UI_DISPLAY_MENU_COLOR "Adjust Color Scale..."
#define UI_DISPLAY_MENU_LIGHTING "Toggle Lighting"
#define UI_DISPLAY_MENU_COASTLINES "Toggle Coastlines"
#define UI_DISPLAY_MENU_AXES "Toggle Axes"
#define UI_DISPLAY_MENU_EPOCH "Toggle Epoch"
#define UI_DISPLAY_MENU_WIRE_FRAME	"Toggle Wireframe"
#define UI_DISPLAY_MENU_DISPLAY "Display"

#define UI_DATA_MENU_DATA "Data"
#define UI_DATA_MENU_OPEN_SINGLE "Open Data Set..."
#define UI_DATA_MENU_OPEN_MULTIPLE "Open Multiple Data Sets..."
#define UI_DATA_MENU_CLEAR_CURRENT "Clear Data Set Shown"
#define UI_DATA_MENU_CLEAR_ALL "Clear All Data Sets Loaded"

#define MAIN_UI_WINDOW_TITLE "Zaidaco"
#define COLOR_SCALE_MAIN_WINDOW_TITLE "Color Scale"

#define MAIN_UI_HELP_LAT "Adjust the latitude by rotating along the z-axis. Hold down the mouse button and "
#define MAIN_UI_HELP_LON "Adjust the longitude by rotating along the x-axis"
#define MAIN_UI_HELP_TIMER "Increase or decrease timer speed."
#define MAIN_UI_HELP_INTERPOLATION "Set the number of frames for interpolation -- Slows the animation"
#define MAIN_UI_HELP_ZOOM "Increase the radius of the sphere."
#define MAIN_UI_HELP_SCALE "Increase the relative scale of the heightmap to the radius of the sphere."
#define MAIN_UI_HELP_PREVIOUS "Go to the previous data set."
#define MAIN_UI_HELP_STOP "Stop animation"
#define MAIN_UI_HELP_NEXT "Go to the next data set."
#define MAIN_UI_HELP_PLAY "Play"
#define MAIN_UI_HELP_PAUSE "Pause"
#define MAIN_UI_HELP_FRAME "Shows index of current frame"

#define MAIN_UI_FILE_CHOOSER_SINGLE "Open File?"
#define MAIN_UI_FILE_CHOOSER_SINGLE_TYPE "*.xyz"
#define MAIN_UI_FILE_TYPE_ERROR "Unable to load %s. Please check the file format."
#define MAIN_UI_FILE_CHOOSER_MULTIPLE "Are you loading a file with the names of multiple data sets?"
#define MAIN_UI_FILE_CHOOSER_MULTIPLE_YES "Yes"
#define MAIN_UI_FILE_CHOOSER_MULTIPLE_NO "No"
#define MAIN_UI_FILE_CHOOSER_MULTIPLE_CANCEL "Cancel"
#define MAIN_UI_FILE_CHOOSER_MULTIPLE_CLEAR_ALL "Do you want to clear all of the data sets that are already loaded first?"
#define MAIN_UI_FILE_CHOOSER_MULTIPLE_TYPE "*.txt"

#define MAIN_UI_FILE_REMOVE_SINGLE_CHECK "Are you sure you want to remove this data set?"
#define MAIN_UI_FILE_REMOVE_SINGLE_NO "No, keep it."
#define MAIN_UI_FILE_REMOVE_SINGLE_YES "Remove."
#define MAIN_UI_FILE_REMOVE_CANCEL "Cancel"

#define MAIN_UI_FILE_REMOVE_MULTIPLE_CHECK "Do you want to clear all of the data sets?"
#define MAIN_UI_FILE_REMOVE_MULTIPLE_NO "No, keep them."
#define MAIN_UI_FILE_REMOVE_MULTIPLE_YES "Clear All."
#define MAIN_UI_FILE_REMOVE_MULTIPLE_CANCEL "Cancel"

#define MAIN_UI_SYMBOL_PLAY "@>"
#define MAIN_UI_SYMBOL_STOP "@square"
#define MAIN_UI_SYMBOL_PREVIOUS "@<|"
#define MAIN_UI_SYMBOL_NEXT "@|>"
#define MAIN_UI_SYMBOL_PAUSE "@||"

#define COASTLINE_FILE "/coastlines.xy"
#define DEFAULT_TEXTURE_WIDTH 1024
#define DEFAULT_TEXTURE_HEIGHT 1024

//Scale constants
#define SCALE_MAX 2.0
#define SCALE_MIN -2.0
#define SCALE_STEP 0.01
#define SCALE_INIT_VAL 0.0

//LAT and LON roller constants
#define MAX_ROLLER  3600
#define MIN_ROLLER -3600

 
#endif //USER_MESSAGES_INLCUDED_H