#ifndef DATASET_H_INCLUDED
#define DATASET_H_INCLUDED
/**
 *  dataset.h
 * 
 *  Purpose: This contains the values and other related information 
 *           for  a single data set. It is currently configured for 
 *			 a one by one grid of longitude and latitude values.
 *			 This class also has minimal support for summary information 
 *			 about the data such as mean, variance, standard of deviation, 
 *           maximum, and minimimum value. Store comments in data file
 *			 and epoch information.
 *
 *  
 *	Created by Sarah Block on 1/29/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>

#include "gvutils.h"
#include "epoch_data.h"

/**
  * Data Set Defaults
  */
#define MIN_LATITUDE  -90.0
#define MAX_LATITUDE  90.0
#define MIN_LONGITUDE  0.0
#define MAX_LONGITUDE  360.0
#define GRID_SIZE  1.0
#define MAX_SIZE 65341

using namespace std;

class dataset{
	
	public:
	/**
	  * Default constructor uses dataset defaults.
	  */
	dataset();
	dataset(uint size);
	/**
	 * Constructs a new data with the matching values of the old set.
	 */
	dataset(dataset *rhs);
	dataset(const char * source_file);
	dataset(uint s, string source_file, string date);
	
	/**
	 * Destructor deletes allocated space for data values stored in the _values array.
	 */
	~dataset();
	
	/**
	  * Push methods for adding data to the array. 
	  **/
	void push_back(double v);
	void push_back(int lon, int lat, double v);
	void push_back(float v){push_back((double)v);}
	void push_back(int v){push_back((double)v);}
	void push_back(uint v){push_back((double)v);}
	void push_back(string comment){_comments.push_back(comment);}
	
	double operator[](uint i)	 {  return get_value(i);}
	
	/**
	 * Comparison operators compare data sets by epoch only.The purpose of this is to 
	 * allow the datasets to be sorted by epoch each time a new one is added.
	 *
	 **/
	bool operator<(dataset &rhs) {	return _epoch_data.julian_date() <  rhs.epoch_data_val().julian_date(); }
	bool operator<=(dataset &rhs){	return _epoch_data.julian_date() <= rhs.epoch_data_val().julian_date(); }
	bool operator>=(dataset &rhs){	return _epoch_data.julian_date() >= rhs.epoch_data_val().julian_date(); }
	bool operator>(dataset &rhs) {	return _epoch_data.julian_date() >  rhs.epoch_data_val().julian_date(); }
	bool operator==(dataset &rhs) {	return _epoch_data.julian_date() ==  rhs.epoch_data_val().julian_date(); }

	double *get_values(){return _values;}	

	/**
	  * Set and get methods
	  **/
	void set_source_filename(string file){_source_file_name = file;}
	string get_source_filename(){return _source_file_name;}
	
	vector<string> get_comments(){return _comments;}
	void set_comments(vector<string> comments){_comments = comments;}
	
	/**
	 * Purpose for data files that run from longitude 0 to 359 sets 360 to the same as 0. 
	 **/
	void adjust_data();
	
	/**
	 * Compute statistics
	 **/
	double compute_variance();
	double compute_standard_of_deviation(){compute_variance(); return _standard_of_deviation; }
	double compute_mean();
	
	/**
	 * Get the value of the statistics
	 **/
	double standard_of_deviation(){return _standard_of_deviation;}
	double variance(){return _variance;}
	double mean(){return _mean;}

	/**
	 * Set and get for private member variables
	 **/
	double maximum(){return _maximum;}
	double minimum(){return _minimum;}
	double grid_size(){return _grid_size;}	
	double min_latitude(){return _min_latitude;}
	double max_latitude(){return _max_latitude;}
	double min_longitude(){return _min_longitude;}
	double max_longitude(){return _max_longitude;}
	void min_latitude(double v){_min_latitude = v;}
	void max_latitude(double v){_max_latitude = v;}
	void min_longitude(double v){_min_longitude = v;}
	void max_longitude(double v){_max_longitude = v;}
	void grid_size(double size){_grid_size = size; }
	
	/**
	 * Sets the value of a data point at a given index.
	 * Does nothing if value is out of bounds.
	 */
	void set_value_at(uint index, double value)
	{
		if(index >= 0 && index < _size)
		{
			_values[index] = value;
		}
	
	}
	
	/**
	 * Gets the value of a data point at a given index.
	 * Does nothing if value is out of bounds.
	 */
	double get_value(uint i)
	{
		if(i < _size && i >= 0)
		{ 
			return _values[i]; 
		}
		return NULL;
	}
	
	/**
	 * Gets the value of a data point by position.
	 * Does nothing if value is out of bounds.
	 */	
	double get_value(int lat, int lon)
	{
		uint index = (lat + _max_latitude)*_max_longitude + lon;
		return get_value(index);
	}	
	
	/**
	 * Call to reset maximimum and minimum value after adding data points.
	 * 
	 */
	void set_max_and_min();

		
	string source_file(){return _source_file_name;}
	uint size(){return _size;}
	uint index(){return _index;}
	
	void clear();
	void resize(uint size);
	
	/**
	 * Methods for setting and getting the epoch data
	 */
	epoch_data & epoch_data_val() { return _epoch_data; }
	
	void set_epoch(int year, int month= 1, int day=1, int hour=0, int minute=0, int second=0)
	{_epoch_data.reset_epoch(year, month, day, hour, minute, second); }
	
	double epoch_internal(){ return _epoch_internal; }
	void epoch_internal(double v) {_epoch_internal = v; }
	

	private:
	/**
	  * This contains the epoch data and related conversions 
	  */
	epoch_data _epoch_data;
	/**
	  * The internal epoch is a value from 0 to 1.0 used to create the epoch scale. 
	  * This is computed
	  * in the data class that contains all the data sets.
	  */
	double _epoch_internal;
	
	/**
	  * Statistical measures and other properties of the data set.
	  */
	double _mean;
	double _variance;
	double _standard_of_deviation;
	
	double _maximum;
	double _minimum;
	
	float  _grid_size;
	double _min_latitude;
	double _max_latitude;
	double _min_longitude;
	double _max_longitude;
	
	uint _size;
	double *_values;
	
	vector<string> _comments;
	string _source_file_name;	
	/**
	  * Make the copy constructor private to disallow copying
	  */
	dataset(dataset &rhs){}
	
	/**
	 * Keeps track of the position for the push_back methods.
	 */
	uint _index;
	
	/**
	 * Called by constructors to initialize data arrays
	 */
	void init(uint s);
		

};


#endif