/*
 *  initialize.cxx
 *  COLOR
 *
 *  Created by Sarah Block on 5/18/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "initialize.h"

init_params::init_params()
{
	cout << "Initializing parameters" << endl;
	get_params_from_file();
}


void init_params::get_params_from_file()
{
	
	char *path = getenv("HOME");
	cout << "Initializing parameters get_params_from_file()" << path << endl;
	
	if(path != NULL)
	{
		gvhome = path;
		cout << path << "Not Null" << endl;
	}
	else
	{
		cout << "Path = NULL" << endl;

		return;
	}
	
	
	std::ifstream file;	
	string filename = gvhome + "/" + CONFIG;
	cout << filename << endl;
	file.open(filename.c_str(), ios::in);

	file.close();

}

