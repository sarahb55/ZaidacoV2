#include "earthviewui.h"

/*Global variables for the User Interface**/

/**
 * FLTK needs these to work properly 
 */
int argce;
char** argve;

Fl_Window *earth_window;
colorbar *bar;
data *ds;
animator *anima;
map_builder *map;
colorbarui *color_bar_editor = NULL;
Fl_Double_Window* w;
static int interval = TIMER_INTERVAL;

#define FL_CHOICE_YES 1
int W = 435;
int H = 372;
int X = 45;
int Y = 53;

double zoom = 1.0;
double lat = 0.0;
double lon = 0.0;


bool animate = false; 

/**
 * Textbox to show the frame number
 */
Fl_Output* frame;

extern void adjust_interp_cb(Fl_Value_Slider*o, void*v)
{
	anima->interpolation_steps(o->value());
}

extern void adjust_timer_cb(Fl_Value_Slider *o, void*v)
{
	interval = o->value();

}

void next(void)
{
	//Check to see if there is a next frame
	if(ds->index()  < ds->size() && ds->size() > 1 )
	{
		ds->get_next(); //if there is grab it and rebuild the map.
		map->reset_vertices();
	//	map->reset_normals();
		map->reset_color();
		set_frame(ds->index()); //update the frame in the index
		glutPostRedisplay(); 
	}

}
void init(void)
{    
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);
   glEnable (GL_BLEND);
   glEnable (GL_POLYGON_SMOOTH);
   
	//init_params *params = new init_params();
	
	#ifdef __APPLE__
	string file_name = get_apple_resource_path();
	file_name += COASTLINE_FILE;
	cout << file_name  << endl;
	if(!init_coastlines(file_name.c_str(), DEFAULT_TEXTURE_WIDTH, DEFAULT_TEXTURE_HEIGHT))
	{
		map->toggle_coastlines();
	}
	release_apple_resource();
	#endif
	
	
	glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (0.0, 10.0, 
        0.0, 10.0, -100.0, 100.0);

  
	glLoadIdentity();
		glViewport(0,0,W,H);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode (GL_PROJECTION);
		glEnable (GL_DEPTH_TEST);
		//glEnable (GL_BLEND);
		//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor (0.0, 0.0, 0.0, 0.0);
	map->initialize_arrays();
	map->set_lighting(4, W, H);


   glClearColor(0.0, 0.0, 0.0, 0.0);
   glClearAccum(0.0, 0.0, 0.0, 0.0);
 
   
}

void idle()
{
	// The programs requires this even empty otherwise it uses all of the CPU on idle
	// maybe an fltk bug?
}

void display(void)
{
		
		glLoadIdentity();
		glViewport(0,0,W,H);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode (GL_PROJECTION);
		glEnable (GL_DEPTH_TEST);
		
		glClearColor (0.0, 0.0, 0.0, 0.0);
		map->animate(animate); //Sends the animate variable to the map to let it
							   //knowth UI setting
		map->draw_map(W, H);   //draws the vertex arrays as they are
		bar->draw_color_scale(W, H); //and the color scale
		glutSwapBuffers();
}

extern void toggle_epoch_cb(Fl_Widget *o, void*v)
{

	map->toggle_epoch(); //toggles a boolean variable in the map_builder
	glutPostRedisplay();

}

void reshape(int w, int h)
{
   animate = false; //If you try to resize the screen during an animation 
					// it can freeze or crash the system. This stops it
					// The window may be resized once it is a stable size.
					//
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   
   W = w;
   H = h;
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
  
   map->set_lighting(3, W, H); // Reset up the lighting for the new window size
   glutSwapBuffers();
   
}



void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 27: //This currently is just 'q' for quit.
         exit(0);
         break;
		default:
         break;
   }
}

void mouse(int b, int s, int x, int y)
{
	//This needs to be here otherwise the system sometimes crashes 
	// looking for it.
}

void motion(int x, int y)
{
	//This needs to be here otherwise the system sometimes crashes 
	//looking for it.
}

void timer(int value)
{

	//Check to see if we are animating now.
	//and is there is more than one data set 
	//loaded.
	if(animate && ds->size() > 1)
	{
		
		if(anima->calculate_next_frame(ds)) //call the animator to calculate the next frame
		{
			glutTimerFunc (interval, timer, TIMER_CB);
			map->reset_vertices(); 
			map->reset_color();
			//map->reset_normals();
			set_frame(ds->index()); //update the index
			//cout << interval << endl;
		}
		else
		{
			//anima->on_stop(ds);
			animate = false;
			map->animate(false);	
			Fl::check();  
			//cout << "stopping" << endl;
		}
		
		glutPostRedisplay();
	}
	
}

void edit_color_cb(Fl_Widget *o, void *v)
{
	animate = false;

	//If we don't have a color bar editor, make one
	if(color_bar_editor == NULL)
	{
		color_bar_editor = new colorbarui(10, 10, 20, 30, COLOR_SCALE_MAIN_WINDOW_TITLE);
	}
	
	//if we have one open it up.
	if(color_bar_editor)
	{
		color_bar_editor->edit_settings(argce, argve, bar, map);
		
	}
	
}

void toggle_lighting_cb(Fl_Widget *, void *v)
{
	map->toggle_lighting(); 
	glutPostRedisplay();
}

void toggle_wireframe_cb(Fl_Widget *o, void*v)
{
	map->toggle_wireframe();
	glutPostRedisplay();

}


void quit_cb(Fl_Widget *, void *v)
{
	exit(0);
}


/**
 * these are all of the menu items
 */

Fl_Menu_Item earthviewui::menu_main_menu[] = {

 {UI_FILE_MENU_FILE, 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 { UI_FILE_MENU_QUIT , 0,  (Fl_Callback*) quit_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {UI_DISPLAY_MENU_DISPLAY , 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {UI_DISPLAY_MENU_COLOR, 0,  (Fl_Callback*) edit_color_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 /*{"Map Features...", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},*/
 /*{"Animate...", 0,  (Fl_Callback*) adjust_animate_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},*/
 {UI_DISPLAY_MENU_LIGHTING, 0,  (Fl_Callback*) toggle_lighting_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {UI_DISPLAY_MENU_WIRE_FRAME, 0,  (Fl_Callback*)  toggle_wireframe_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {UI_DISPLAY_MENU_AXES, 0,  (Fl_Callback*)  toggle_axes_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {UI_DISPLAY_MENU_COASTLINES, 0,  (Fl_Callback*)  toggle_coastlines_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {UI_DISPLAY_MENU_EPOCH, 0,  (Fl_Callback*)  toggle_epoch_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {UI_DATA_MENU_DATA, 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {UI_DATA_MENU_OPEN_SINGLE, 0,  (Fl_Callback*) load_data_set_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {UI_DATA_MENU_OPEN_MULTIPLE, 0,  (Fl_Callback*) load_data_sets_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {UI_DATA_MENU_CLEAR_CURRENT, 0,  (Fl_Callback*) clear_data_set_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {UI_DATA_MENU_CLEAR_ALL, 0,  (Fl_Callback*) clear_all_data_sets_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0}
};


Fl_Menu_Item* earthviewui::file_menu = earthviewui::menu_main_menu + 0;
Fl_Menu_Item* earthviewui::map_features = earthviewui::menu_main_menu + 5;

void toggle_coastlines_cb(Fl_Widget *o, void*v)
{
	map->toggle_coastlines();
	glutPostRedisplay();

}

int earthviewui::show(int argc, char **argv, colorbar *cb, map_builder *mb, data *d, animator *anim){
	argce = argc;
	argve = argv;
	if(cb && mb && d && anim)
	{	
		bar = mb->get_colorbar();
		map = mb;	
		ds = d;
		anima = anim;
	}
	else
	{
		exit(0);
	}
	make_window();
	return Fl::run();
}

void toggle_axes_cb(Fl_Widget *o, void*v)
{
	map->toggle_axes();
	glutPostRedisplay();
}



Fl_Double_Window* earthviewui::make_window()
{
	
	Fl::scheme(FL_SCHEME);
	
	Fl_Double_Window* w;
	int width = 640;
	int height = 480;
	int border = 30;
	{ Fl_Double_Window* o = new Fl_Double_Window(width + 4*border, height + 4*border, MAIN_UI_WINDOW_TITLE);
		w = o;
		o->resizable(o);
		o->show();
		o->begin();
		o->user_data((void*)(this));
		{ Fl_Menu_Bar* o = main_menu = new Fl_Menu_Bar(0, 0, width, 20);
			o->menu(menu_main_menu);
		}
		{ Fl_Group* o = new Fl_Group(10, 8,width + 4*border, height + 4*border);
			o->align(229|FL_ALIGN_INSIDE);
			o->when(FL_WHEN_CHANGED);
			{ Fl_Roller* o = new Fl_Roller(13, 58, 25, 270);
				o->box(FL_PLASTIC_UP_BOX);
				o->minimum(MIN_ROLLER);
				o->maximum(MAX_ROLLER);
				o->step(1);
				o->callback((Fl_Callback*)adjust_latitude_cb);
				o->tooltip(MAIN_UI_HELP_LAT);
			}
			{ Fl_Roller* o = new Fl_Roller(border, height + 2*border, 350, 23);
				o->type(1);
				o->box(FL_PLASTIC_UP_BOX);
				o->minimum(MIN_ROLLER);
				o->maximum(MAX_ROLLER);
				o->step(1);
				o->callback((Fl_Callback*)adjust_longitude_cb);
				o->tooltip(MAIN_UI_HELP_LON);
			}
			
			{ Fl_Value_Slider* o = new Fl_Value_Slider(5*width/6 + border, height + 2*border, 100, 19);
				o->type(1);
				o->maximum(1000);
				o->minimum(20);
				o->step(10);
				o->value(100);
				o->textsize(14);
				o->callback((Fl_Callback*)adjust_timer_cb); 
				o->tooltip(MAIN_UI_HELP_TIMER);
			}
			{ Fl_Value_Slider* o = new Fl_Value_Slider(4*width/6, height + 2*border, 100, 19);
			
				o->type(1);
				o->maximum(100);
				o->step(1);
				o->value(20);
				o->textsize(14);
				o->callback((Fl_Callback*)adjust_interp_cb); 
				o->tooltip( MAIN_UI_HELP_INTERPOLATION);

			}
			{ Fl_Value_Slider* o = new Fl_Value_Slider(46, 28, 100, 19);
								
				o->type(1);
				o->maximum(10);
				o->step(0.1);
				o->value(1);
				o->textsize(14);
				o->callback((Fl_Callback*)on_zoom_cb); 
				o->tooltip(MAIN_UI_HELP_ZOOM);				
			}
			
			{ Fl_Value_Slider* o = new Fl_Value_Slider(160, 28, 100, 19);
				o->type(1);
				o->maximum( SCALE_MAX);
				o->minimum(SCALE_MIN);
				o->step(SCALE_STEP);
				o->value(SCALE_INIT_VAL);
				o->textsize(UI_FONT_SIZE );
				o->callback((Fl_Callback*)on_scale_cb);   
				o->tooltip( MAIN_UI_HELP_SCALE);  
			}
			
			{ Fl_Group* o = new Fl_Group(275, 16, 475, 38);
				{ Fl_Button* o = new Fl_Button(275, 24, 25, 25, MAIN_UI_SYMBOL_STOP);
					o->tooltip(MAIN_UI_HELP_STOP);
					o->down_box(FL_DOWN_BOX);
					o->shortcut(0x50073);
					o->align(224);
					o->callback(on_stop_cb);
				}
				{ Fl_Button* o = new Fl_Button(305, 24, 25, 25, MAIN_UI_SYMBOL_PREVIOUS); 
					o->tooltip(MAIN_UI_HELP_PREVIOUS);
					o->callback(on_previous_cb);
				}
				{ Fl_Button* o = new Fl_Button(336, 24, 25, 25, MAIN_UI_SYMBOL_PLAY);
					o->tooltip(MAIN_UI_HELP_PLAY);
					o->callback(on_play_cb);
				}
				{ Fl_Button* o = new Fl_Button(367, 24, 25, 25, MAIN_UI_SYMBOL_NEXT);
					o->tooltip(MAIN_UI_HELP_NEXT );
					o->callback(on_next_cb);
				}
				{ Fl_Button* o = new Fl_Button(398, 24, 25, 25,  MAIN_UI_SYMBOL_PAUSE);
					o->tooltip(MAIN_UI_HELP_PAUSE );
					o->callback(on_pause_cb);
				}

				{ frame = new Fl_Output(430, 24, 25, 25);
					frame->tooltip(MAIN_UI_HELP_FRAME);
					frame->value("0");
				}
				o->end();
			}   
			o->end();
		}
		
		
		glutInitWindowSize(640,480);
		glutInitWindowPosition(43,53);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA| GLUT_DEPTH |  GLUT_ALPHA);
		glutInit(&argce, argve);
		glutCreateWindow(argve[0]);
		o->end();
		
		//Now put in the Glut callbacks
		
		glutDisplayFunc(display);
		glutMouseFunc(mouse);
		glutMotionFunc(motion);
		glutReshapeFunc(reshape);
		glutKeyboardFunc(keyboard);
		glutIdleFunc(NULL);
		glutTimerFunc (interval, timer, TIMER_CB);
		
		init();
	}
	
	return w;
}

void set_frame(int i)
{
	char str[16];
	sprintf(str,"%d", ds->index());
	frame->value(str);


}

extern void on_pause_cb(Fl_Widget *o, void*v)
{
	animate = !animate;	
	anima->on_pause();
	if(animate)
	{
		glutTimerFunc (interval, timer, TIMER_CB);
	}
	
}

extern void on_previous_cb(Fl_Widget *o, void*v)
{
	animate = false;
	
	if(ds->index() - 1 >= 0)
	{
		ds->get_previous();
		map->reset_vertices();
		map->reset_color();
		set_frame(ds->index());
		glutPostRedisplay();
	}
	else if(ds->index() == 0)
	{
		ds->index(ds->size() - 1);
		map->reset_vertices();
		//map->reset_normals();
		map->reset_color();
		set_frame(ds->index());
		glutPostRedisplay();
	}
}

extern void on_stop_cb(Fl_Widget *o, void*v)
{
	anima->on_stop(ds);
	animate = false;
}


extern void on_play_cb(Fl_Widget *o, void*v)
{
	if(!animate) //don't do anything if it is already playing.
	{		
		animate = true;	
		if(ds->index() >= ds->size() - 1)
		{
			anima->on_stop(ds);	
		}
	}
	
	anima->on_play(ds);
	glutTimerFunc (interval, timer, TIMER_CB);
}

extern void on_next_cb(Fl_Widget *o, void*v)
{
	animate = false;
	next();
}



extern void on_scale_cb(Fl_Value_Slider*o, void*v)
{
	
	map->scale( o->value());
	map->reset_vertices();
	
	glutPostRedisplay();
}

extern void on_zoom_cb(Fl_Value_Slider*o, void*v)
{
	map->radius(o->value());
	map->reset_vertices();
	glutPostRedisplay();
}

extern void adjust_latitude_cb(Fl_Roller*o, void*v)
{		
	map->rotateXY( o->value());
	glutPostRedisplay();
}

extern void adjust_longitude_cb(Fl_Roller*o, void*v)
{
	map->rotateZ( o->value());
	glutPostRedisplay();
	
}


extern void load_data_set_cb(Fl_Widget *o, void * v)
{
	
	

	char dir[512];
	
	//This sets it up so the file chooser goes to the last directory location
	//each time you open it so you don't have to renavigate to the same directory 
	//each time you choose a file
	#ifdef __APPLE__
		static char *newfile = getcwd(dir, 512);
	#else
		static char *newfile;
	#endif
	
	//Don't want the animation running when the file is added.
	animate = false;
	
	//Open a file chooser
	newfile = fl_file_chooser(MAIN_UI_FILE_CHOOSER_SINGLE, MAIN_UI_FILE_CHOOSER_SINGLE_TYPE, newfile);
	
	if (newfile != NULL)
	{
		//Try to load the file	and then reset the map to show it.	
		
		if(ds->load_file(newfile))
		{
			map->initialize_arrays(ds->index());
			set_frame(ds->index());
			if(ds->size() == 1)
			{
				double 	mean = 	ds->get_current()->mean();
				double std = ds->get_current()->standard_of_deviation();
				bar->set_maxvalue((float) mean + 3.5*std);
				bar->set_minvalue((float) mean - 3.5*std);
				map->reset_color();
				map->reset_vertices();
				//map->reset_normals();
			}
		}
		else
		{
			//Didn't work show an error message
			
			fl_alert(MAIN_UI_FILE_TYPE_ERROR, newfile);
		}
		
		glutPostRedisplay();
	}


}


 
extern void load_data_sets_cb(Fl_Widget *o, void*v)
{
	
	
	/*Fl_File_Chooser chooser(".",                        // directory
                            "*",                        // filter
                            Fl_File_Chooser::MULTI,     // chooser type
                            "Title Of Chooser");        // title
    /*chooser.show();
	
    // Block until user picks something.
    //     (The other way to do this is to use a callback())
    //
    while(chooser.shown())
	{ Fl::wait(); }
	
    // User hit cancel?
    if ( chooser.value() == NULL )
	{ fprintf(stderr, "(User hit 'Cancel')\n"); return; }
	
    // Print what the user picked
    fprintf(stderr, "--------------------\n");
    fprintf(stderr, "DIRECTORY: '%s'\n", chooser.directory());
    fprintf(stderr, "    VALUE: '%s'\n", chooser.value());
    fprintf(stderr, "    COUNT: %d files selected\n", chooser.count());
	
    // Multiple files? Show all of them
    if ( chooser.count() > 1 ) {
        for ( int t=1; t<=chooser.count(); t++ ) {
            fprintf(stderr, " VALUE[%d]: '%s'\n", t, chooser.value(t));
        }
    }
	
	
	//Double-check that they are loading the right type of file.
	/*
	
	int i = fl_choice(MAIN_UI_FILE_CHOOSER_MULTIPLE,  MAIN_UI_FILE_CHOOSER_MULTIPLE_NO, \
		MAIN_UI_FILE_CHOOSER_MULTIPLE_YES,  MAIN_UI_FILE_CHOOSER_MULTIPLE_CANCEL);
	
	
	bool reload_color = false;
	
	//Make sure you aren't animating while you are adding files
	animate = false;
	
	if(i == FL_CHOICE_YES) //1 means yes from the f
	{
		if(ds->size() > 0)
		{
			//Check to see if we should clear the old data first...
			int j = fl_choice( MAIN_UI_FILE_CHOOSER_MULTIPLE_CLEAR_ALL, MAIN_UI_FILE_CHOOSER_MULTIPLE_NO, \
				MAIN_UI_FILE_CHOOSER_MULTIPLE_YES, MAIN_UI_FILE_CHOOSER_MULTIPLE_CANCEL);
			
			if(j == FL_CHOICE_YES)
			{
				ds->clear();
				set_frame(ds->index());
			}
		}
		char dir[512];

//Save the directory so the next file chooser opens in the same location
#ifdef __APPLE__
			static char *file = getcwd(dir, 512);
#else
			static char *file;
#endif
			//We want to reset the color if there are no loaded items
			//
			if(ds->size() == 0)
			{
				reload_color = true;
			}
			
			//Get the file name
			file = fl_file_chooser(MAIN_UI_FILE_CHOOSER_SINGLE, MAIN_UI_FILE_CHOOSER_MULTIPLE_TYPE, file);
			
			if (file != NULL)
			{								
				filereader *fr = new filereader();
				//printf("%s", file);
				fr->read_file(file, ds); //read them all in
				
				// This will display the last item loaded.
				
				if(ds->get_current() && reload_color)
				{
					double 	mean = 	ds->get_current()->mean();
					double std = ds->get_current()->standard_of_deviation();
					bar->set_maxvalue((float) mean + 3*std);
					bar->set_minvalue((float) mean - 3*std);
					map->reset_color();

				}
				
				map->initialize_arrays(ds->index());
				set_frame(ds->index());
				
			
		}
			
		glutPostRedisplay();
			
			
	}
	 */
}

extern void clear_data_set_cb(Fl_Widget *o, void*v)
{
	int i = fl_choice(MAIN_UI_FILE_REMOVE_SINGLE_CHECK,MAIN_UI_FILE_REMOVE_SINGLE_NO , \
		MAIN_UI_FILE_REMOVE_SINGLE_YES , MAIN_UI_FILE_REMOVE_CANCEL);
	animate = false;
	
	if(i == FL_CHOICE_YES && ds)
	{
		ds->remove_current_element();
		map->initialize_arrays(ds->index());
		set_frame(ds->index());
	}
	
	glutPostRedisplay();
}

extern void clear_all_data_sets_cb(Fl_Widget *o, void*v)
{
	animate = false;
	
	int i = fl_choice(MAIN_UI_FILE_REMOVE_MULTIPLE_CHECK, MAIN_UI_FILE_REMOVE_MULTIPLE_NO , \
					MAIN_UI_FILE_REMOVE_MULTIPLE_YES, MAIN_UI_FILE_REMOVE_MULTIPLE_CANCEL);

	if(i == FL_CHOICE_YES && ds)
	{
		ds->clear();
		set_frame(ds->index());
	}
	
	glutPostRedisplay();

}