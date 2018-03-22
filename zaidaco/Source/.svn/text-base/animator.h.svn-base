#ifndef ANIMATOR_H_INCLUDED
#define ANIMATOR_H_INCLUDED
/*
 *  animator.h
 *  
 *	Purpose: This class is designed to handle the animation in the program. It is used by 
 *  map_build and earthviewui and holds the user settings and calculates and stores the dataset
 *  used in display. The UI methods call the matching animator methods when the user clicks
 *  buttons to reset the state.
 *
 *  Created by Sarah Block on 3/9/07.
 *  Copyright 2007 Sarah Block All rights reserved.
 *
 */
#include <time.h>
#include <math.h>
#include <stdio.h>

#include "fileloader/data.h"
#include "fileloader/dataset.h"

#define DEFAULT_INTERPOLATION_STEPS 20

class animator{

	public:
	animator();
	~animator();
	
	/**
	 * This method returns a pointer to the last calculated dataset
	 */
	dataset *get_frame() { return _dataset; }
	
	/**
	 * This method is called each time the frame is updated. This usually 
	 * happens via a timer but could be modified to be called by the user
	 * via the UI to control the frame rate
	 * It uses linear interpolation to calculate and intermediate frame
	 */
	bool calculate_next_frame(data *ds);
	
	void reset_count()			{_count = 0;		}
	
	time_t count()				{return _count;		}
	/**
	 * This is called by the UI when the user clicks stops and 
	 * it resets all the variables used in the animation.
	 *
	 */
	void on_stop(data *ds);
	/**
	 * This is called by the UI when the user clicks pause and 
	 * it resets the boolean _pause.
	 *
	 */
	void on_pause(){_pause = !_pause; }
	/**
	 * This is the method called when the user clicks play in the UI
	 * If the animation is running it does nothing. Otherwise it sets up
	 * the animation
	 **/
	void on_play(data *ds);
	
	/**
	 * Get methods for display by the UI
	 */
	float percent_complete(){return _percent_complete; }
	void interpolation_steps(int steps){_frames_between_sets = steps;  }
	
	
	private:
	/** 
	 * This variable is set in the UI via a slider. It is the 
	 * number of intermediate frames that are calculated for
	 * displaying between datasets.
	 */
	int  _frames_between_sets;
	
	/**
	 * This is the dataset that the program returns to the map_builder to 
	 * create a map from.
	 */
	dataset * _dataset;		
	
	/**
	 * Pointer to all the data in the system.
	 */
	data *_data;
	
	/**
	 * _count is used to keep track of how many frames were calculated.
	 */
	time_t _count;		
	
	/**
	 * _interval_count is used to keep track of how many frames were calculated between two
	 * particular frames.
	 */							    
	time_t _interval_count;
	
	/**
	 * Variable used in the UI to show which dataset is displayed.
	 */
	uint _frame_index;
	
	/**
	 * Set to true when the user clicks pause
	 */
	bool _pause;

	/**
	 * Keeps track of where the animation is.
	 * This variable is used in drawing the epoch_scale.
	 */
	float _percent_complete;


};

#endif //ANIMATOR_H_INCLUDED