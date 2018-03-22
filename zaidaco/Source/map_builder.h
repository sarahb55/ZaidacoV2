#ifndef MAP_BUILDER_H_INCLUDED
#define MAP_BUILDER_H_INCLUDED

   /**
	 *  map_builder.h
	 *  
	 *  Purpose: This class takes a dataset and draws an image on the screen. 
	 *  It has member variables to save the user settings that are changed via 
	 *  the user interface and then draw a map onto the screen when draw_map is called
	 *  by the glut callback display in earthviewui.
	 *
	 *  Created by Sarah Block on 2/6/07.
	 *  Copyright 2007 Sarah Block. All rights reserved.
	 *
	 */

#define TWOPI           6.283185307179
#define PI              3.141592653589
#define PI_OVER_TWO		1.570796326795

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <FL/gl.h>
#include <FL/glut.h>
#include <FL/glut.H>	// changed for fltk


#ifdef __APPLE__
# include <OpenGL/glu.h>
#else
# include <GL/glu.h> // added for fltk
#endif

#include "colorbartext.h"
#include "gvutils.h"
#include "colorbar.h"
#include "animator.h"
#include "epoch_scale.h"
#include "fileloader/data.h"
#include "fileloader/dataset.h"
#include "user_messages.h"

using std::string;

typedef struct{

   GLfloat x,y,z;

} xyz_position;


enum {

	kSphere,
	kPlane
};


class map_builder{


public:

   /**
	 * Constructor 
	 */
	map_builder(double rad, data *dt, colorbar *cb, animator *anim);	
   /**
	 * Destructor deletes memory allocated and cleans up.
	 */
	~map_builder();
	 
	/**
	  * This is the main public method called by the UI when the map is redrawn.
	  * It sets up all of the map features.
	  *
	  */
	 void draw_map(int w, int h);
	
	 
	/**
	  * Set and get methods for member variables.
	  */
	 void set_data(data *data){ if(_data){_data = data;} }
	 data *get_data(){return _data;}
	 
	 void set_colorbar(colorbar *cbar){if(_cbar){_cbar = cbar;} }
	 colorbar *get_colorbar(){return _cbar;}
	 
	 double radius(){return _radius;}
	 void radius(double rad){if(rad > 0.0) _radius = rad;}
	 
	 void scale(double scale){ _scale = scale;}
	 double scale(){return _scale;}
	
	/**
	  * The figure may be rotated either by latitude or longitude.
	  * This method is called when the UI rollers are activated to 
	  * change the rotation.
	  */
	 void rotateXY(double XYrot){ _XYrot = XYrot;}
	 void rotateZ(double Zrot){  _Zrot = Zrot;}	
	
   /**
	 * These methods set allocate memory and create initial values for the arrays
	 * used in displying the figure
	 */
	void initialize_arrays(){initialize_arrays(0);}
	void initialize_arrays(uint index);
	
   /**
	 * This method is called by the UI to let the map_builder know whether
	 * to display a frame from the animator or the current frame.
	 * _animate is a boolean value.
	 */
	void animate(bool animate){_animate = animate;}
   /**
     * This method is called by the UI when the color is reset. It is 
	 * uses the colorbar object member variable to obtain the new colors and
	 * resets the color array.
	 *
	 */
	void reset_color();
   /**
     * This method is called by the UI when the scale is reset. It is 
	 * resets the vertices in the vertex array.	
	 */
	void reset_vertices();
	
  /**
    * This method is called when setting up the lighting and when the window
    * is reshaped.
    * For now, it is not possible to adjust the lighting but it is possible
    * to create an interface to change the properties of the lighting.
    *
    */	
	void set_lighting(unsigned int mode, int w, int h);	
	
  /**
    * These methods are called by the UI and enable or 
    * disable these features.
    *
    */	
	void toggle_lighting(){_light = !_light; }
	void toggle_wireframe(){_solid = !_solid; }
	void toggle_axes(){_axes = !_axes;}
	void toggle_coastlines(){_coastlines = !_coastlines;} 
	void toggle_epoch(){_epoch = !_epoch; }

	
private:
	
	data *_data;
	colorbar *_cbar;
	animator *_anim;
	epoch_scale *_es;
	
   /**
	 * These values are set in the UI 
	 * and change the appearance of the map.
	 */		
	double _radius;
	double _scale;
	int _XYrot;
	double _Zrot;
	unsigned int _data_index;
	bool _animate;
	bool _light;
	bool _solid;
	bool _axes;
	bool _coastlines;
	bool _epoch;
		
   /**
	 * Arrays displayed in map.
	 */		
	GLfloat * _xyz_array;
	GLfloat * _normal_array;
	GLfloat * _texcoord_array;
	GLfloat * _color_array;
	GLuint  * _indices_array;
	GLfloat * _xyz_position_array;
	
   /**
	 * Takes a sing xyz_position and normalizes by dividing it by its length.
	 */
	xyz_position*	normalize(xyz_position *p);
	
   /**
	 * Calculates the normal of two vectors using their cross product and normalizes the normal.
	 */
	xyz_position	normal(xyz_position p,xyz_position p1,xyz_position p2);
	
   /**
	 * Calculates the xyz position from latitude, longitude after they 
	 * have been converted to radians.
	 */
	xyz_position	evaluate(double u, double v, int type, int index);
	
   /**
	 * This method checks to see whether animation is turned on and returns a pointer
	 * to the dataset to be drawn. NULL if none are loaded into the program.
	 *
	 */
	dataset*		data_set();
	
	/**
	  * Dynamically allocates memory for the six display arrays. Sends 
	  * an fl_alert message on error and
	  * exits the program as program will not run without these.
	  *
	  */
	void			set_up_arrays();
   
   /**
	 * Called when user requests map axes.
	 */
	void	        draw_axes();
	
   /**
	 * Private method that enable the arrays and draws them. Called by public version.
	 */
	void			draw_map();
	
   /** 
	 * Used by reset vertices when vertex positions change so that lighting
	 * adjust according to the new shape.
	 */
	void			reset_normals();
	
	
};

#endif //MAP_BUILDER_H_INCLUDED