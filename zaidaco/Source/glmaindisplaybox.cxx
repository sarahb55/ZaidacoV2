#include "GLMainDisplayBox.h"

int GLMainDisplayBox::handle(int e) {
	switch (e) {
		case FL_ENTER: cursor(FL_CURSOR_CROSS); break;
		case FL_LEAVE: cursor(FL_CURSOR_DEFAULT); break;
		printf("handle");
	}
	
	return Fl_Gl_Window::handle(e);
	
}


void GLMainDisplayBox::draw()
{ 
		
	cout << "Draw" << endl;
	
	//_map->draw_map(w(), h(), _zoom, _adjustLatitude, _adjustLongitude);
	//_cbar->draw_color_scale(w(), h());	
	
	

	
}

