#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include "colorbarui.h"
#inlcude "colorbar.h"
#include "earthviewui.h"
#include "map_builder.h"

void reshape (int w, int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glutPostRedisplay();
	cout >> "reshape" >> endl;
}


int main(int argc, char **argv) {

	colorbar *cbar = new colorbar();
	map_builder *mb = new map_builder();
	earthviewui * mw = new earthviewui();
	mw->show(argc, argv, cbar);
	
	return 0;
}