#ifndef EPOCH_DATA_H_INCLUDED
#define EPOCH_DATA_H_INCLUDED
/*
 *  epoch_data.h
 *  
 *	Purpose: This is a class to store the epoch and related information from a data file.
 *	In addition to storing the epoch in the format that it is specified in the header
 *	file it also stores it in Julian Date, Modified Julian Date, and 
 *  a ew different types of string for display on the image.
 *
 *  Created by Sarah Block on 4/26/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */
#include <string>
#include <iostream>

#define MAX_MONTH 12 
#define MAX_DAY 31
#define MAX_HOUR 23
#define MAX_MINUTE 59
#define MAX_SECOND 59
#define DEFAUTL_STR "NA"
#define NO_EPOCH -1.0
#define MIN_INTEGER_YEAR 1600 /*For use in converting the to JD. May be modified later*/

enum MONTHS  {NONE, JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

using std::string;
using std::cout;
using std::endl;

class epoch_data{
	
public:
	/**
	 * This constructor is for days before the year 1600. This cn later be modified to 
	 * accept earlier dates if there is a series of data that require it.
	 */
	
	epoch_data(int year=2007, int month = 1, int day = 1, int hour = 0, int min = 0, float sec = 0.0);
	/**
	 * Not yet implemented for models that run over thousands of year
	 */	
	epoch_data(double kyear);
	
	/**
	 * Copy constructor
	 */
	epoch_data & operator=(epoch_data &rhs);

	/**
	 * Default destructor
	 */
	~epoch_data(){}
	
	/**
	 * Tests to see if a year is a leap year
	 */
	bool is_leap_year(int year);
	
	/**
	 * Converts a date into Julian Date -- 
	 * The modified Julian date is 2,400,000.5 less the Julian date (JD)
	 *  and the JD is the number of mean solar days that have elapsed since 4713 BC.
	 */
	double ymdhms_to_jd(int year, int month, int day, int hour, int minute, float sec);
	
	/**
	 * Converts a Julian Date to a modified Julian Date.
	 */
	float jd_to_mjd(float jd);
	
	/**
	 * Use to reset the epoch. Reinitializes all the values to the date entered
	 */	
	void reset_epoch(int year, int month = 1, int day = 1, int hour = 0, int min = 0, float sec = 0.0);
	
	/**
	 * Comparison Operators. Compares epochs.
	 */
	bool operator>(epoch_data &rhs);
	bool operator>=(epoch_data &rhs);
	bool operator<=(epoch_data &rhs);
	bool operator<(epoch_data &rhs);
	bool operator==(epoch_data &rhs);
	bool operator!=(epoch_data &rhs);
	
	string year_str(){return _year_str;}
	string month_day_str(){return _month_day_str;}
	string hour_min_sec_str(){return _hr_min_sec_str; }
	string julian_date_str(){return _julian_date_str; }
	string mon_day_yr_str() {return _mon_day_yr_str; }
	
	/**
	 * Get methods for private variables.
	 */
	int year() {return _year; }
	int month() {return _month; }
	int day() {return _day; }
	int hour() {return _hour; }
	int minute() {return _minute; }
	float second() {return _second; }
	
	double julian_date() { return _julian_date; }
	double modified_julian_date(){ return _modified_julian_date; }
	
private:
	
	void init(int year, int month = 1, int day = 1, int hour = 0, int min = 0, float sec = 0.0);
	void init(double year);
	
	/** 
	 * Converts the numerical epoch to string values.
	 */
	void set_strings();
	
	int _year; 
	int _month;
	int _day;
	int _hour;
	int _minute; 
	int _second;
	
	double _julian_date;
	double _modified_julian_date;
	
	/**
	 * Keeps the representation of the epoch as a string for
	 * display 
	 */
	string _year_str;
	string _month_day_str;
	string _hr_min_sec_str;
	string _julian_date_str;
	string _mon_day_yr_str;
	
};

#endif
