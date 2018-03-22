#ifndef FILEREADER_H_INCLUDED
#define  FILEREADER_H_INCLUDED


/*
 *  filereader.h
 * 
 *  Purpose: This reads data files from the disk and converts them into the internal 
 *  dataset format used by the program. It currently only reads one type of file but could 
 *  be modified to read other file types without adjusting other parts of the program
 *  The main method is called read_file.
 *
 *  Created by Sarah Block on 1/29/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

#include "data.h"
#include "dataset.h"
#include "../user_messages.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Output.H>
#include <FL/fl_ask.H>

class data;

enum filetypes  {LAT_LON_VAL_1_DEGREE, VALUE_ONLY};
#define COMMENT_LINE '#'
#define GRACE_EPOCH "#GRACE_EPOCH"
#define EPOCH "#EPOCH"
#define KILO_YEARS "#KILO_YEARS"

using namespace std;

class filereader{
 
	public:
	 filereader(){}
	 ~filereader(){}
	 
	/**
	  * This reads in a single data file and populates the dataset
	  * argument.
	  *
	  * returns false on error.
	  */
	  bool read_file(string filename, dataset *ds, int type=LAT_LON_VAL_1_DEGREE);
	  
	/**
	  * This reads in a a list of multiple files and populates the dataset
	  * argument.
	  */	  
	 void read_file(vector<string> filenames, dataset *ds, int type=LAT_LON_VAL_1_DEGREE);
	 
	/**
	  * This opens a file that is a list of multiple files and populates the data
	  * argument with datasets. This allocates memory each data set.
	  */	
	 void read_file(string file /*file containing list of file names*/, data *d, int type=LAT_LON_VAL_1_DEGREE);
	 
	 private:
		
	 string _filename;
	 vector<string> _comments;
	 
	 /**
	  * Saves the comments from the file and adds them to the dataset
	  */
	 int save_comments(ifstream &file, dataset *ds);


	 
 
 };

#endif //FILEREADER_H_INCLUDED
