/*
 *  dataset.cxx
 * 
 *  Purpose: Implementation of data.h
 *
 *  
 *	Created by Sarah Block on 1/29/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */

#include "dataset.h"

dataset::dataset():
_values(0)
{
	clear();
	init(MAX_SIZE);
}

dataset::dataset(uint s):
_values(0)
{
	clear();
	init(s);
}

dataset::dataset(uint s, string source_file, string date):
_values(0)
{
	clear();
	init(s);
	set_source_filename(source_file);
	
}
/**
 * This constructor creates a dataset with the same values as the datset
 * sent into the constructor
 */

dataset::dataset(dataset *rhs):
_values(0)
{
	if(this == rhs || !rhs)
	{
		return;
	}
	else
	{
		
		if(_values)
		{
			delete [] _values;
		}
		
		_values = new double[rhs->size()];
		_size = rhs->size();
		for(int i = 0; i < _size; i++){
			_values[i] = rhs->get_value(i);
			
		}
		
		
		_mean = rhs->mean();
		_variance = rhs->variance();
		_standard_of_deviation = rhs->variance();
		_maximum = rhs->maximum();
		_minimum = rhs->minimum();
		_grid_size = rhs->grid_size();
		_min_latitude = rhs->min_latitude();
		_max_latitude = rhs->max_latitude();
		_min_longitude = rhs->min_longitude();
		_max_longitude = rhs->max_longitude();
		_comments = rhs->get_comments();
		_source_file_name = rhs->source_file();
		_size = rhs->size();
		_index = rhs->index();
		_epoch_internal = rhs->epoch_internal();
		_epoch_data = rhs->epoch_data_val();
	}
	
	
	
}

/*
 * Destructor deallocates _values pointer
 */

dataset::~dataset(){
	if(_values)
	{
		delete [] _values;
	}
	
}

void dataset::set_max_and_min()
{
	_maximum = 0;
	_minimum = 0;
	
	for(int i = 0; i < _size; i++)
	{
		double v = _values[i];
		
		if(v > _maximum && !isnan(v)){
			_maximum = v;
		}
		else if(v < _minimum &  !isnan(v)){
			_minimum = v;
		}			
		
	}
	
}
/**
 * Clears out all the values
 */
void dataset::clear()
{
	if(_values)
	{
		delete [] _values;
	}
	_values = 0;
	_index = 0;
	_size = 0;		
	_mean  = 0.0;
	_variance = 0.0;
	_standard_of_deviation = 0.0;
	_maximum = 0.0;
	_minimum = 0.0;
	_comments.clear();
	_source_file_name.clear();
	_grid_size = GRID_SIZE;
	_min_latitude = MIN_LATITUDE;
	_max_latitude = MAX_LATITUDE;
	_min_longitude = MIN_LONGITUDE;
	_max_longitude = MAX_LONGITUDE;
	_epoch_internal = 0.0;	
}

void dataset::resize(uint size)
{
	clear();
	init(size);	
}

/**
 * Reallocates the _values array and size
 */
void dataset::init(uint s)
{
	if(_values)
	{
		delete [] _values;
	}
	
	if(s <= MAX_SIZE && s > 0){
		_values = new double[s];
		_size = s;		
	}
	
}
/**
 * Adds v to the next space in the _values array and updates _index.
 */
void dataset::push_back(double v)
{
				
	if(_index < _size){
		_values[_index] = v;
		
		_index++;
		
		if(v > _maximum && !isnan(v)){
			_maximum = v;
		}
		else if(v < _minimum && !isnan(v)){
			_minimum = v;
		}		
	}	
	
}

/**
 * To be used to put a data value at a specific point
 */
void dataset::push_back(int lon, int lat, double v)
{
	
	
	int index = (MAX_LATITUDE + lat)*_max_longitude + lon;
	if(index < _size){
		_values[index] = v;
		
		
		if(v > _maximum && !isnan(v) ){
			_maximum = v;
		}
		else if(v < _minimum && v != NAN){
			_minimum = v;
		}
		
	}
	
	
}

double dataset::compute_variance()
{
	
	double mean = compute_mean();
	double sum = 0.0;
	int count = 0;
	for(int i = 0; i < _size; i++)
	{
		if(!isnan(_values[i]))
		{
			sum += (_values[i] - mean)*(_values[i] - mean);	
			count++;
			
		}
	}
	
	if(count > 1){
		_variance = sum / ((double)count - 1.0f);
	}
	
	_standard_of_deviation = sqrt(_variance);
	
	return _variance;
}



double dataset::compute_mean()
{
	double sum = 0.0;
	int count = 0;
	
	for(int i = 0; i < _size; i++)
	{
		
		if(!isnan(_values[i]))
		{
			sum += _values[i];
			count++;
		}
		
	}
	
	if(count > 0){
		_mean = sum / (double) count;
	}
	
	return _mean;
}


/**
 * For special cases where latitude ranges from 0 to 359 
 * It adds a fax data value for 360 which is equivalent to 0. It helps to
 * make the indices array and drawing commands work properly.
 * 
 **/
void dataset::adjust_data()
{
	
	cout << "adjusting data " << endl;
	cout << _max_longitude << endl;
	
	if(!_values){
		cout << "!_values ";
		return;
		
	}	
	
	cout << _max_latitude << endl;
	if(_max_longitude == 359)
	{
		
		int lat_range = fabs(_min_latitude) + fabs (_max_latitude);
		int size = (_max_longitude + 1)*(lat_range + 1);
		double *temp = new double[size];
		
		if(!temp)
		{
			//handle error
		}
		
		int index = 0;
		double zero_val = -0.5;
		
		for(int lat = 0; lat <= lat_range; lat ++)
		{
			for(int lon = 0; lon <= _max_longitude; lon++)
			{
				int data_index = lat*(_max_longitude + 1) + lon;
				
				if(lon == 0)
				{
					//cout << "lon == 0 "<< endl;
					zero_val = _values[data_index];
					//cout << "zero_val ==  " << zero_val << endl;
				}
				if(index < size && data_index < _size)
				{
					temp[index] = 	_values[data_index];
				}
				index++;
				if(lon == _max_longitude && index < size)
				{
					temp[index] = zero_val;
					index++;
				}
				
				
			}
			
		}
		delete [] _values;
		_max_longitude = 360;
		_values = temp;
		
	}
	
	
	
}

