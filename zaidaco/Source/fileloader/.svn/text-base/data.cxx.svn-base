/*
 *  data.cxx
 *  
 *  Implementation files of data.h
 *
 *  Created by Sarah Block on 1/29/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */

#include "data.h"

bool data::load_file(char *filename)
{
	bool retval = true;
	
	filereader *fr = new filereader();
	dataset *dt = new dataset(MAX_SIZE);
	
	if(!fr)
	{
		return false;
	}

	if(fr->read_file(filename, dt,0))
	{
		dt->compute_mean();
		dt->compute_standard_of_deviation();
		dt->adjust_data();
		dt->set_source_filename(filename);
		push_back(dt);
	}
	else
	{
		delete dt;
		retval = false;
	}
	
	
	delete fr;
	reset_epochs();
	
	return retval;
}

void data::remove_current_element()
{
		
		/**
		 * Check to see if there is a current element
		 */
		if(_index > datasets.size() || _index <  0)
		{
			return;
		}
		else if(datasets.size() == 1)
		{
			clear();
		}
		else
		{
			vector<dataset *> temp;
			
			/**
			 * Build a new vector without the current dataset
			 */
			for(int i = 0; i < datasets.size(); i++)
			{
				if(i != _index)
				{
					temp.push_back(datasets[i]);
				}			
							
			}
			
			/**
			 * Clear the old one
			 */
			datasets.clear();
			
			/**
			 * Fill datasets back up with all the other items
			 */
			for(int i = 0; i < temp.size(); i++)
			{
				datasets.push_back(temp[i]);
			}
			
			/**
			 * Set the index to the previous element.
			 */
			 if(_index >= 1)
			 {
				_index = datasets.size() - 1;
			}
			else
			{
				_index = 0;
			}
		}
		reset_epochs();
	
	}
	
	void data::clear()
	{
		/**
		 * deallaocate the memory 
		 */
		for(int i= 0; i < datasets.size(); i++)
		{
			dataset *d = datasets[i];
			if(d)
			{
				delete d;
			}
		}
		
		/**
		 * then clear the vector
		 */
		datasets.clear();
		_index = -1;
	}

	dataset * data::get_current()
	{
		if(datasets.size() > 0)
		{
			return get_dataset(_index);
		}
		else
		{
			return NULL;
		}
	}
	
	dataset * data::get_previous()
	{
		/**
		 * check bounds
		 */
		if(datasets.size() == 0 || _index < 0)
		{
			return NULL; //Error
		}
		if(_index > 0){
			_index -= 1;
		}
		else
		{
			_index = 0;

		}
		//Loop
		_index %=  datasets.size();		
		
		return get_dataset(_index);
	}
	
	dataset * data::get_next()
	{
		
		
		/**
		 * check bounds
		 */
		if(datasets.size() == 0 || _index < 0)
		{
			return NULL; //Error
		}
		
		_index++;
		
		//Loop
		if(_index >= datasets.size())
		{			
			_index =  0;	
		}	
		return get_dataset(_index);
	}
	
	dataset * data::operator[](uint i)
	{
		i %=  datasets.size();
		_index = i;
		return get_dataset(i);
	}
	
	dataset * data::get_dataset(uint i)
	{
		if(datasets.size() == 0 || i < 0)
		{
			return NULL;
		}
		if(i < datasets.size())
		{
			_index = i;
			return datasets[i];
			
		}
		else
		{
			_index = 0;
			return datasets[0];
		}
		
	}
	
	void data::push_back(dataset *ds)
	{
		if(ds)
		{
			datasets.push_back(ds);
			_index++;
		}
		
		reset_epochs();
	}
	
	
	void data::reset_epochs()
	{
		bool epochs_set = true;
		
		//Nothing loaded nothing to do
		if(datasets.size() == 0)
		{
			return;
		}
		//Only one loaded set it to 0.
		else if(datasets.size() == 1)
		{
			datasets[0]->epoch_internal(0.0);
		}
		
		/**
		 * Loop through the files to make sure each has an epoch assigned
		 */
		for(int i = 0; i < datasets.size(); i ++)
		{
			if(datasets[i]->epoch_data_val().julian_date() < 0)
			{
				epochs_set = false;
			}
			//reset everything to -1.0 when some files are missing epochs
			datasets[i]->epoch_internal(-1.0);
		}
		
		
		if(epochs_set)
		{
			
			int s = datasets.size() - 1;
			//Calculate the total time interval of all the datasets loaded.
			
			float ti = datasets[s]->epoch_data_val().julian_date() - datasets[0]->epoch_data_val().julian_date();
			
			for(int i = 1; i < datasets.size() - 1; i ++)
			{
				float ei = datasets[i]->epoch_data_val().julian_date() - datasets[0]->epoch_data_val().julian_date();
				
				if(ti > 0 && ei > 0 && epochs_set)
				{
					float pc = ei/ti;
					datasets[i]->epoch_internal(pc);
				}
				
			}
			
			datasets[0]->epoch_internal(0.0);
			datasets[s]->epoch_internal(1.0);
		}
		
	
	}




