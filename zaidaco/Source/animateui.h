/*
 *  animateui.h
 *  COLOR
 *
 *  Created by Sarah Block on 5/7/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Adjuster.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.h>

#define MIN_VIEW_SECONDS 20
#define MAX_VIEW_SECONDS 300
#define MIN_TIMER_MS 10
#define MAX_TIMER_MS 1000
#define TIMER_INTERVAL 30
#define RUN_TIME 60

extern void window_exit(Fl_Widget *, void*);
class animateui{

	public:
	animateui(long timer_ms, long viewing_time);
	int show(int argc, char **argv, long timer_ms, long viewing_time);
	
	long viewing_time(){return _viewing_secs; }
	void viewing_time(long vs) {set_viewing_time(vs); } 
	
	void timer_ms(long tms){set_timer(tms); }
	long timer_ms(){return _timer_ms; }
	
	private:
	void set_timer(long value);
	void set_viewing_time(long value);
	long _timer_ms;
	long _viewing_secs;


};
