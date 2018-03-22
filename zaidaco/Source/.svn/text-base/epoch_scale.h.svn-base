#ifndef EPOCH_SCALE_H_INCLUDED
#define EPOCH_SCALE_H_INCLUDED
/*
 *  epoch_scale.h
 *
 *	Purpose: This this draws the epoch scale.
 * 
 *  Created by Sarah Block on 4/23/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */
 
#include <string>
#include <vector>
#include "gvutils.h"
#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "dataset.h"

using std::string;

 
class epoch_scale{

	public:
	/** 
	 * The constructor hold a pointer to the data for the 
	 * the epoch scale
	 *
	 */	
	epoch_scale(data *dt):
	_dt(0)
	{
		if(dt)
		{
			_dt = dt;
		}
	}
	
	/**
	 * Default destructor
	 */
	~epoch_scale(){}
		
	
	/**
	 * This method draws the epoch scale and takes three arguments.
	 * w and h are the window width and height.
	 * percent_complete is the scaled position of the frame and is a value between
	 * 0.0 and 1.0
	 * 
	 * 
	 */
	void draw_scale(int w, int h, double percent_complete);	

	
	private:
	/**
	 * Set to false when the user elects not to show the epoch scale
	 */
	bool _show;
	
	data *_dt;
	

};


#endif //EPOCH_SCALE_H_INCLUDED