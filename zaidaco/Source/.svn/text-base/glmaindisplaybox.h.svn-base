#ifndef GLMAINDISPLAYBOX_H_INCLUDED
#define GLMAINDISPLAYBOX_H_INCLUDED

#include <FL/Fl.H>
#include <FL/gl.h>
#include <FL/glut.h>
#include <FL/Fl_Gl_Window.H>

#include "colorbartext.h"
#include "gvutils.h"
#include "colorbar.h"
#include "map_builder.h"
#include <stdio.h>
#include <stdlib.h>

#include <string>
using std::string;

#define LAT_DEFAULT 0
#define LON_DEFAULT 0
#define LON_DEFAULTT 0.75

class GLMainDisplayBox : public Fl_Gl_Window {
public:
		
	
	GLMainDisplayBox(int x,int y,int w,int h,const char *l=0)
		: Fl_Gl_Window(x,y,w,h,l) {
			_adjustLatitude = LAT_DEFAULT;
			_adjustLongitude = LON_DEFAULT;
			_zoom = LON_DEFAULTT;
		}
		

		
	void draw();
	int handle(int);
	
	
	void set_color_bar(colorbar *bar){_cbar = bar; }
	void set_map_builder(map_builder *map){_map = map;}
	void adjustLatitude(double rotate){_adjustLatitude = rotate;}
	void adjustLongitude(double rotate){_adjustLongitude = rotate;}
	void adjustZoom(double zoom){_zoom = zoom;}
	void adjustScale(double s){_map->scale(s);}
	
	private:
	colorbar *_cbar;
	map_builder *_map;
	
	double _adjustLatitude;
	double _adjustLongitude;
	double _zoom;
};

#endif //GLMAINDISPLAYBOX_H_INCLUDED