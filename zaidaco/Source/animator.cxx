/*
 *  animator.cxx
 *  
 *  Implementation of animator.h
 *
 *  Created by Sarah Block on 3/9/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */

#include "animator.h"

animator::animator():
_dataset(0),
_frames_between_sets(DEFAULT_INTERPOLATION_STEPS),
_interval_count(0),
_pause(false),
_percent_complete(0.0)
{
	

}

animator::~animator()
{
	if(_dataset)
		delete _dataset;
}


void animator::on_stop(data *ds)
{
	_frame_index = 0;
	_interval_count = 0;
	_percent_complete = 0.0f;
	
	if(ds)
	{
		ds->index(0);
	}
}

void animator::on_play(data *ds)
{
	_pause = false;

}

bool animator::calculate_next_frame(data *ds)
{
	if(_pause || !ds || ds->size() < 2 || ds->index() > ds->size() - 1)
	{
		return false;
		
	}
	
	bool retval = true;
	
	if(!_dataset)
	{
		printf("Init dataset \n");
		_dataset = new dataset(ds->get_current());
	}
	
	/**
	 * No interpolation at this point so just set the next value in the data
	 */
	
	if(_frames_between_sets == 0)
	{
		dataset *dt = ds->get_next();
		
		for(uint i = 0; i < _dataset->size(); i++)
		{
			_dataset->set_value_at(i,  dt->get_value(i));
		}
		
		_percent_complete = dt->epoch_internal();
	
	}
	else
	{	
		/*
		 * If we are done interpolating between the two data sets
		 * reset the interval count and grab the next two
		 */
		
		if(_interval_count >= _frames_between_sets)
		{
			_interval_count = 0;
			dataset *ds1 = ds->get_next();
			
			if(!ds || ds->index() >= ds->size())
			{
				retval = false;
			}
			else
			{
				for(uint i = 0; i < _dataset->size(); i++)
				{
					_dataset->set_value_at(i,  ds1->get_value(i));
				}
				
				if(ds1->epoch_internal() > 0)
				{
					_percent_complete = ds1->epoch_internal();
				}
				else
				{
					_percent_complete = (float)ds->index()/((float)ds->size());
				}
			}
			
		}
		else
		{
			
			
			_interval_count++;
			dataset *ds1, *ds2;
			ds1 = ds->get_element_at(ds->index());
			ds2 = ds->get_element_at(ds->index() + 1);
			if(!ds1 || !ds2)
			{
				retval = false;
				_percent_complete = 1.0;
			}
			else
			{
				double v1, v2 = 0.0f;
				
				v1 = ((double)_frames_between_sets - (double)_interval_count)/(double)_frames_between_sets;
				v2 = ((double)_interval_count/(double)_frames_between_sets);	
				
				double interp = 0.0f;
				//loop through and inerpolate
				for(uint i = 0; i < _dataset->size(); i++)
				{
					
					interp = v1*ds1->get_value(i) + v2*ds2->get_value(i);	
					_dataset->set_value_at(i,  interp);
					
				}
				
				if(ds2->epoch_internal() > 0 && ds1->epoch_internal() > 0)
				{
					_percent_complete =(ds2->epoch_internal() - ds1->epoch_internal() ) *(float) _interval_count /(float) _frames_between_sets  + ds1->epoch_internal() ;
				}
				else
				{
					_percent_complete = (float)ds->index()/(float)ds->size()  + (float) _interval_count /( (float) _frames_between_sets*ds->size() );
				}
			}
			
		}
		
		
		
		
	
	}


	
	return retval;
}



