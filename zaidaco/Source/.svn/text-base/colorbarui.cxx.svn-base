#include "colorbarui.h"

/*
 *  colorbarui.cxx
 *  
 *	Purpose: This is a class to store the user input related to the color scale
 *  and use this to draw the scale onto the screen.
 *
 *  Created by Sarah Block on 4/26/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */

colorbar *cbar;
map_builder *maps;
static Fl_Window *w;



int colorbarui::edit_settings(int argc, char *argv[], colorbar *bar, map_builder *mb)
{
	
	cbar = bar;
	maps = mb;

	
	Fl::scheme(FL_SCHEME);
	w = new Fl_Window(350,400);
	
	{
	
		Fl_Input_Choice *o = new Fl_Input_Choice(120,60,200,TEXT_HEIGHT, COLOR_SCHEME_LABEL);
		o->value(cbar->get_color_scheme());
		o->add(COLOR_RAINBOW);
		o->add(COLOR_RAINBOW_2);
		o->add(COLOR_RAINBOW_3);
		o->add(COLOR_RAINBOW_4);
		o->add(COLOR_RAINBOW_5);
		o->add(COLOR_RAINBOW_6);
		o->add(COLOR_RAINBOW_7);
		o->add(COLOR_RAINBOW_8);
		o->add(TANGERINE);
		o->add(ORANGE);
		o->add(YELLOW_RED);
		o->add(THE_BLUES);
		o->add(COLOR_BLUE_TO_RED);
		o->add(COLOR_GRAYSCALE);
		o->add(COLOR_GRAY);
		o->add(COLOR_BLUE);
		o->add(YELLOW_GREEN);
		o->add(GREEN_PINK);
		o->callback(color_scale_e);
	
	}

	//Show and Hide buttons	
	/*
	{ Fl_Group* o = new Fl_Group(0, 55, 385, 56);
      { Fl_Check_Button* o = new Fl_Check_Button(10, 69, 130, 25, MASK_QUERY_ABOVE);
        o->down_box(FL_DOWN_BOX);
		o->value(false);
		o->callback(mask_above_value_e);
      }
	
      { Fl_Input_Choice* o = new Fl_Input_Choice(247, 69, 89, 25,  WITH);
		o->add(BLACK);
		o->add(WHITE);
		o->add(GREY);
		o->add(RED);
		o->add(GREEN);
		o->add(BLUE);
		o->value(BLACK);
		o->callback(mask_above_color_e);
      }
	  {
      Fl_Value_Input *o = new Fl_Value_Input(155, 67, 60, 24);

		  o->value(cbar->get_maxvalue());
		  o->minimum(cbar->get_maxvalue());
		  o->callback(mask_above_value_e);
	  }
      o->end();
    }*/
   
	/*
	  { Fl_Group* o = new Fl_Group(5, 25, 340, 33);
      { Fl_Check_Button* o = new Fl_Check_Button(10, 33, 64, 20, MASK_QUERY_BELOW);
        o->down_box(FL_DOWN_BOX);
		
      }
	  {
		Fl_Value_Input *o = new Fl_Value_Input(155, 29, 60, 25);
		  o->value(cbar->get_minvalue());
		  o->maximum(cbar->get_minvalue());
		}

      { Fl_Input_Choice* o = new Fl_Input_Choice(247, 29, 89, 25, WITH);
		o->add("Black");
		o->add("White");
		o->add("Gray");
		o->add("Red");
		o->add("Green");
		o->add("Blue");
		o->value("Black");
      }
      o->end();
	}*/
	

	
	{ Fl_Group* o = new Fl_Group(20, 100, 300, TEXT_HEIGHT);
		o->box(FL_THIN_UP_FRAME);
		{ 
			Fl_Round_Button *o = new Fl_Round_Button(25, 100, 100, TEXT_HEIGHT, TEXT_SHOW);
			o->type(FL_RADIO_BUTTON);
			o->down_box(FL_ROUND_DOWN_BOX);
			o->value(!cbar->get_show());
			o->callback(show_e);
		}
		{	
			Fl_Round_Button *o = new Fl_Round_Button(150, 100, 100, TEXT_HEIGHT, TEXT_HIDE);
			o->type(FL_RADIO_BUTTON);
			o->value(cbar->get_show());
			o->down_box(FL_ROUND_DOWN_BOX);
			o->callback(hide_e);
		}
		
		o->end();
	}

	
		
	{ Fl_Group* o = new Fl_Group(20, 140, 300, TEXT_HEIGHT);
		o->box(FL_THIN_UP_FRAME);
		{ 
			Fl_Round_Button *o = new Fl_Round_Button(25, 140, 100, TEXT_HEIGHT, TEXT_VERTICAL);
			o->type(FL_RADIO_BUTTON);
			o->down_box(FL_ROUND_DOWN_BOX);
			o->value(cbar->vertical());
			o->callback(vert_e);
		}
		{	
			Fl_Round_Button *o = new Fl_Round_Button(150, 140, 100, TEXT_HEIGHT, TEXT_HORIZONTAL);
			o->type(FL_RADIO_BUTTON);
			o->value(!cbar->vertical());
			o->down_box(FL_ROUND_DOWN_BOX);
			o->callback(hori_e);
		}
		
		o->end();
	}
	
	char min[256];
	char max[256];	
	sprintf(max, "%f",cbar->get_maxvalue()); 
	sprintf(min, "%f",cbar->get_minvalue()); 
	flfi_min_value = new Fl_Float_Input(50, 180, 100, TEXT_HEIGHT, MINIMUM_VALUE_LABEL);
	flfi_min_value->value(min);
	flfi_min_value->callback(setminvalue_e);
    flfi_max_value = new Fl_Float_Input(220, 180, 100, TEXT_HEIGHT, MAXIMUM_VALUE_LABEL);
	flfi_max_value->value(max);
	flfi_max_value->callback(setmaxvalue_e);
	

	units =  new Fl_Input_Choice(50,220,100,TEXT_HEIGHT, UNITS_LABEL);
	units->value(cbar->get_units());
	units->add(UNITS_MGAL);
	units->callback(setunits_e);
	
	flfi_ticks_value = new Fl_Float_Input(220, 220, 100, TEXT_HEIGHT, "Ticks");
	char cticks[16];
	sprintf(cticks, "%d",cbar->get_ticks()); 
	flfi_ticks_value->value(cticks);
	flfi_ticks_value->callback(setticks_e);

	fli_title = new Fl_Input(50, 260, 280, TEXT_HEIGHT, TITLE_LABEL);
	fli_title->callback(settitle_e);
	fli_title->value(cbar->get_title());
	
	{
		Fl_Button *o = new Fl_Button(150, 300, 100, TEXT_HEIGHT, "Done");
		o->callback(hide_window_e);

	}
	
	//w->set_modal();
	w->end();
	w->show(argc, argv);	
	
	return Fl::run();
		
}

void colorbarui::hori_e(Fl_Widget *o, void* v)
{
	((colorbarui*)(v))->hori(o,v);
	glutPostRedisplay();

}


void colorbarui::hori(Fl_Widget *o, void* v)
{

	if( ((Fl_Round_Button *)(o))->value() == TRUE){
		cbar->vertical(false);
	}
	else{
		cbar->vertical(true);
	}
	
	//color_graph->redraw();
	glutPostRedisplay();;
}


void colorbarui::vert_e(Fl_Widget *o, void* v)
{
	((colorbarui*)(v))->vert((Fl_Round_Button *)o,v);
	glutPostRedisplay();

}


void colorbarui::color_scale(Fl_Input_Choice*o, void*v)
{
	

}


void colorbarui::color_scale_e(Fl_Widget*o, void*v)
{
	const char *val = ((Fl_Input_Choice *)o)->value();
	cbar->set_color_scheme(val);
	maps->reset_color();
	glutPostRedisplay();

	
}

void colorbarui::vert(Fl_Round_Button *o, void* v)
{

	if( ((Fl_Round_Button *)(o))->value() == TRUE){
		cbar->vertical(true);

	}
	else{
		cbar->vertical(false);

	}
	
	glutPostRedisplay();
	
}

void colorbarui::settitle(Fl_Widget*o, void*)
{
	cbar->set_title( ((Fl_Input *)(o))->value());
	//color_graph->redraw();
	glutPostRedisplay();
	
}

void colorbarui::settitle_e(Fl_Widget*o, void*v)
{
		 ((colorbarui*)(v))->settitle(o,v);

		
}

void colorbarui::setunits_e(Fl_Widget*o, void*v)
{
	((colorbarui*)(v))->setunits(o,v);
	
}

void colorbarui::setunits(Fl_Widget*o, void*)
{
	cbar->set_units(((Fl_Input_Choice *)(o))->value());
	glutPostRedisplay();
	
}

void colorbarui::setminvalue(Fl_Widget*o, void*)
{
	cbar->set_minvalue(atof(((Fl_Float_Input *)(o))->value()));
	maps->reset_color();
	glutPostRedisplay();
}

void colorbarui::setminvalue_e(Fl_Widget*o, void*v)
{
	((colorbarui*)(v))->setminvalue(o,v);
}


void colorbarui::setmaxvalue(Fl_Widget*o, void*)
{
	cbar->set_maxvalue(atof(((Fl_Float_Input *)(o))->value()));
	maps->reset_color();
	glutPostRedisplay();
}

void colorbarui::setmaxvalue_e(Fl_Widget*o, void*v)
{
	((colorbarui*)(v))->setmaxvalue(o,v);
}

void colorbarui::setticks_e(Fl_Widget*o, void*v)
{
	((colorbarui*)(v))->setticks(o,v);
}

void colorbarui::setticks(Fl_Widget*o, void*)
{
	cbar->set_ticks(atoi(((Fl_Float_Input *)(o))->value()));
	//color_graph->redraw();
	glutPostRedisplay();
}

void colorbarui::show(Fl_Widget*o, void*v)
{
	if( ((Fl_Round_Button *)(o))->value() == TRUE){
		cbar->show();

	}
	else{
		cbar->hide();
	}
	
	//color_graph->redraw();
	glutPostRedisplay();

	
}
void colorbarui::show_e(Fl_Widget*o, void*v)
{
	((colorbarui*)(v))->show(o,v);
}

void colorbarui::hide(Fl_Widget*o, void*)
{
	if( ((Fl_Round_Button *)(o))->value() == TRUE){
		cbar->hide();

	}
	else{
		cbar->show();
	}
	
	//color_graph->redraw();
	glutPostRedisplay();

	
}

void colorbarui::hide_e(Fl_Widget*o, void*v)
{
	((colorbarui*)(v))->hide(o,v);
}

void colorbarui::hide_window_e(Fl_Widget *o, void*)
{
	w->hide();
}

void colorbarui::mask_above(Fl_Widget *o, void*v)
{
	( (colorbarui*)(v))->mask_above(o,v);
}
void colorbarui::mask_above_e(Fl_Widget *o, void*)
{
	if( ((Fl_Check_Button* )(o) )->value() == TRUE)
	{
		cbar->mask_above( true );
	}
	else
	{
		cbar->mask_above( false );
	}	
	glutPostRedisplay();
}

void colorbarui::mask_above_value(Fl_Widget *o, void*v)
{
	if( ((Fl_Value_Input *)(o))->value() >= cbar->get_maxvalue())
	{
		cbar->mask_max(((Fl_Value_Input *)(o))->value());
	}
	glutPostRedisplay();
}

 void colorbarui::mask_above_value_e(Fl_Widget *o, void*v)
{
	 ( (colorbarui*)(v))->mask_above_value(o,v);	 

}

/** 
 * Not yet implemente
 */
void colorbarui::mask_above_color(Fl_Widget *o, void*v)
{
	
}

void colorbarui::mask_above_color_e(Fl_Widget *o, void*)
{
}


void colorbarui::mask_below(Fl_Widget *o, void*)
{
}

void colorbarui::mask_below_e(Fl_Widget *o, void*)
{
}


void colorbarui::mask_below_value(Fl_Widget *o, void*)
{
}

void colorbarui::mask_below_value_e(Fl_Widget *o, void*)
{
}


void colorbarui::mask_below_color(Fl_Widget *o, void*)
{
}

void colorbarui::mask_below_color_e(Fl_Widget *o, void*)
{
}



