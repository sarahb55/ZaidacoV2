/*
 *  filereader.cxx
 *  
 *
 *  Created by Sarah Block on 1/29/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */

#include "filereader.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Output.H>

bool filereader::read_file(string filename, dataset *ds, int type)
{
	
	ifstream file;
	
	float lon, lat, value;
	double maxlon, maxlat, minlon, minlat;
	maxlon = maxlat= minlon= minlat=0.0;
	
	string line;
	bool retval = true;
	
	_filename = filename;
	_comments.push_back(filename);
	
	ds->set_source_filename(filename);
	file.open(filename.c_str(), ios::in);
	/**
	 * Send a UI message on failure.
	 */
	
	if(file.fail())
	{
		fl_alert(FILE_LOADER_FILE_NOT_FOUND, filename.c_str());
		return false;
	}		
		
		save_comments(file, ds);
						
		while(!file.eof())
		{
			
			getline(file, line);
			if(line[0] != COMMENT_LINE && line.length() > 0)
			{
				int i = sscanf(line.c_str(),"%f %f %f", &lon, &lat, &value);
			
				if(line.length() > 0 && i != 3)
				{
					retval = false;
					break;
				}
			}
		
			if(lat < minlat){
				minlat = lat;
			}
			if(lat > maxlat){
				maxlat = lat;
			}
			if(lon < minlon){
				minlon = lon;
			}
			if(lon > maxlon){
				maxlon = lon;
			}
			
			ds->push_back(value);	
			
		}
		
	ds->min_latitude(minlat);
	ds->max_latitude(maxlat);
	ds->min_longitude(minlon);
	ds->max_longitude(maxlon);

	file.close();
	return retval;
}

/**
 * Saves information from the file header
 */	 
int filereader::save_comments(ifstream &file, dataset *ds)
{
	bool epoch_set = false;
    int comments = 0;
	string line;
	string date;
	int sday, syear = 0;
	
	char epoch_type[256];
	
	file.seekg(0,ios::beg);
	
	while(!file.eof())
	{
		
		getline(file, line);
		
		if(line[0] == COMMENT_LINE && line.length() > 0)
		{
			_comments.push_back(line);
			ds->push_back(line);
			comments++;
			
			date = line.substr(0,strlen(GRACE_EPOCH));
			/**
			 * GRACE_EPOCH only works for files after 1970 since it uses ctime.
			 */
			if(date == GRACE_EPOCH)
			{
				int i = sscanf(line.c_str(),"%s %d %d", epoch_type, &syear, &sday);
				if(i == 3)
				{
					
					time_t start_time = yd_to_time_t(syear, sday);
					tm *start_tm = gmtime(&start_time);
					ds->set_epoch(1900 + start_tm->tm_year, start_tm->tm_mon + 1, start_tm->tm_mday);
					epoch_set = true;
				}
			}
			date = line.substr(0,strlen(EPOCH));
			if(date == EPOCH)
			{
				int year, month, day, hour, min;
				float sec;
				int i = sscanf(line.c_str(),"%s %d %d %d %d %d %f", epoch_type, &year, &month, &day, &hour, &min, &sec);
				if(i == 7)
				{
					ds->set_epoch(year, month, day, hour, min, sec);
					epoch_set = true;
				}
			}
			
			date = line.substr(0,strlen(KILO_YEARS));
			if(date == KILO_YEARS)
			{
				double year;
				int i = sscanf(line.c_str(),"%s %f", epoch_type, &year);
				if(i == 2)
				{
					ds->set_epoch(year);
					epoch_set = true;
				}
			}

			
		}
		else
		{
			file.seekg(0,ios::beg);
			
			for(int i = 0; i < comments; i++)
			{
				getline(file, line);
			}
			return comments;			
		}		
	
	}

	if(!epoch_set)
	{
		ds->set_epoch(NO_EPOCH);
	}
	
	return comments;
}





void filereader::read_file(string filename /*file containing list of file names*/, data *ds, int type)
{
		ifstream file;
		file.open(filename.c_str(), ios::in);
		vector<string> filenames;
		string line;
	
		if(file.fail())
		{
			return;
		}
		
		while(!file.eof())
		{
			getline(file, line);	
			if(line.size() > 0)
			{
				filenames.push_back(line);
			}
		}
		
		
		file.close();
		/**
		 * Modal progress bar to show user what is happening
		 **/
		Fl::check();                     
		Fl_Window *w = new Fl_Window(200, 120, 300, 200, FILE_LOADER_LOADING_FILES);
		w->begin();                    
		Fl_Progress *progress = new Fl_Progress(10,20,280,30);
		Fl_Output* fname = new Fl_Output(10, 80, 280, 30);
	
		fname->textsize(10);
		progress->minimum(0.0);              
		progress->maximum(1.0);
		w->set_modal();
		w->end();    
		w->show();     

		char message[1024];
		
		
		for(int i = 0; i < filenames.size(); i++)
		{
			dataset *dt = new dataset();
			if(read_file(filenames[i], dt, type))
			{
				sprintf(message, FILE_LOADER_LOADING_X_OF_Y_FILES, i, (int)filenames.size());
				fname->value(message);
				dt->compute_mean();
				dt->compute_standard_of_deviation();
				dt->adjust_data();
				ds->push_back(dt);
				progress->value((float) i/(float) filenames.size()); 
				Fl::check();  
			}
			else
			{
				w->remove(progress);  
				w->remove(fname);
				delete(fname);              
				delete(progress);  
				w->redraw(); 
				delete(w); 
				return;
			}
		}

	w->remove(progress);  
	w->remove(fname);
	delete(fname);              
    delete(progress);  
    w->redraw(); 
	delete(w); 
}


