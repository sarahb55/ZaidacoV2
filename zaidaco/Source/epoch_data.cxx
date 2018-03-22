/*
 *  epoch_data.cxx
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


#include "epoch_data.h"

epoch_data::epoch_data(int year, int month, int day, int hour, int min, float sec)
{
	init(year, month, day, hour, min, sec);
}

epoch_data::epoch_data(double kyear)
{
	init(kyear);
}

void epoch_data::reset_epoch(int year, int month, int day, int hour, int min, float sec)
{
	init(year, month, day, hour, min, sec);
}

void epoch_data::set_strings()
{
		char str[128];
		sprintf(str, "%d", _year);
		_year_str = str;
		sprintf(str, "%d/%02d", _month, _day);
		_month_day_str = str;
		sprintf(str, "%d/%02d/%d", _month, _day, _year);
		_mon_day_yr_str = str;
		sprintf(str, "%02d:%02d:%02d", _hour,_minute,_second);
		_hr_min_sec_str = str;
		sprintf (str, "%.6f", _julian_date);
		_julian_date_str = str;
}


bool epoch_data::operator>(epoch_data &rhs)
{
	return _julian_date > rhs.julian_date();
}

bool epoch_data::operator>=(epoch_data &rhs)
{
	return _julian_date >= rhs.julian_date();
}

bool epoch_data::operator<=(epoch_data &rhs)
{
	return _julian_date <= rhs.julian_date();
}

bool epoch_data::operator< (epoch_data &rhs)
{
	return _julian_date < rhs.julian_date();
}

bool epoch_data::operator==(epoch_data &rhs)
{
	return _julian_date == rhs.julian_date();
}

bool epoch_data::operator!=(epoch_data &rhs)
{
	return _julian_date != rhs.julian_date();
}

epoch_data & epoch_data::operator=(epoch_data &rhs)
{
	if(this != &rhs)
	{
		reset_epoch(rhs.year(), rhs.month(), rhs.day(), rhs.hour(), rhs.minute(), rhs.second());
	}
	return *this;
}

/**
 * For looking at longer events using kyears not yet implemented
 */
void epoch_data::init(double year)
{


}

void epoch_data::init(int year, int month, int day, int hour, int min, float sec)
{
	_year = year;
	
	/**
	 * Check to see if values are in bounds.
	 */
	if(month > 0 && month <= MAX_MONTH)
	{
		_month = month;
	}
	
	/**
	 * If it's February and a lep year day can go up to 29
	 */
	if(month == FEB && is_leap_year(year) && _day <= 29 && day > 0)
	{
		_day = day;
	}
	else if(month == FEB && day <= 28 && day > 0)
	{
		day = _day;
	}
	
	/**
	 * These are the months that have 30 days
	 */
	else if((month == APR || month == SEP || month == JUN || month == NOV) && day <= 30 && day > 0)
	{
		_day = day;
	}
	/**
	 * These have 31 days
	 */
	else if((month == JAN || month == MAR || month == MAY || month == JUL || month == AUG || month == OCT || month == DEC) && day > 0 && day <= 31)
	{
		_day = day;
	}
	
			
	if(hour > 0 && hour < MAX_HOUR)
	{
		_hour = hour;
	}
	else
	{
		_hour = 0;
	}
	
	if(min >= 0 && min <= MAX_MINUTE)
	{
		_minute = min;
	}
	else
	{
		_minute = 0;
	}
	
	if(sec > 0 && sec < MAX_SECOND)
	{
		_second = sec;
	}
	else
	{
		_second = 0.0f;
	}

	if(_year >= MIN_INTEGER_YEAR)
	{
		_julian_date = ymdhms_to_jd(_year, _month, _day, _hour, _minute, _second);
		_modified_julian_date = jd_to_mjd(_julian_date);
	}
	else
	{
		_julian_date  = _modified_julian_date  = NO_EPOCH;
	}
	
	set_strings();

}

/**
 * checks to see if a year is a leap year
 */
bool epoch_data::is_leap_year(int year)
{
	bool bret = false;
	
	if((year % 100 == 0) && (year % 400 ) == 0)
	{
		bret = true;			
	}
	else if(year % 4 == 0)
	{
		bret = true;
	}

	return bret;

}

/**
 *
 *	This method is modified from code code written by JL Davis
 *  Returns the Julian date at the epoch spcified.
 * 
 *  Based on ymdhms_to_jd in gen_util library. This routine is only valid for dates after 1600 Jan 1.
 */
double epoch_data::ymdhms_to_jd(int year, int month, int day, int hour, int minute, float sec)
{

	
	int MONTH_DAYS[12] = {0, 31, 59, 90, 120, 151, 181, 222, 253, 283, 314, 344 };
	int years_from_1600, leap_days, leap_year;
	int days_from_1600;
		
	double frac_day, mjd, jd;
			
	/* Make sure year is within range */
	if (year < MIN_INTEGER_YEAR) return (NO_EPOCH);
	
	/* Compute number of years from 1600 */
	years_from_1600 = year - MIN_INTEGER_YEAR;

	/*	
	 *  Now compute number of leap days up to the start of the year
	 *	we are in (i.e., if the year we are in is a leap year do not
	 *  add the leap day yet) 
	 */
	leap_days = 0;
	leap_days += (int) ((years_from_1600 - 1) / 4);
	leap_days -= (int) ((years_from_1600 + 99) / 100);
	leap_days += (int) ((years_from_1600 + 399) / 400);
	leap_days += 1;
	leap_days -= (years_from_1600 == 0);
	
	/* Now see if we are in leap year */
	leap_year = ((years_from_1600 % 4) == 0) && (((years_from_1600 % 100) != 0) | ((years_from_1600 % 400) == 0));
	
	/* Now compute number of days since 1600 */
	days_from_1600 = years_from_1600 * 365  + leap_days + MONTH_DAYS[month - 1] + day;
	
	/* Add extra day if we are after Februrary and this is a leap year */
	days_from_1600 += ((month > 2) && leap_year);

	/* Compute the mjd and add in the fraction of a day part. The MJD of 1600 Jan 0 is -94554 */
	frac_day  = (double) sec / 86400.0  + (double) minute / 1440.0 + (double) hour / 24.0;
	
	mjd = -94554.0 + (double) days_from_1600 + frac_day;
	
	/* Julian date */
	jd = 2400000.5 + mjd;
	
	/* Return full Julian date */
	return (jd);

}

float epoch_data::jd_to_mjd(float jd)
{
	return jd - 2400000.5;

}


