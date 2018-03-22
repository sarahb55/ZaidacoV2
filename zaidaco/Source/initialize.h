#ifndef INITIALIZE_H_INCLUDED
#define INITIALIZE_H_INCLUDED
/*
 *  initialize.h
 *  COLOR
 *
 *  Created by Sarah Block on 5/18/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
 
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
 
using namespace std;

#define CONFIG "config"
class init_params{

	public:
	init_params();
	~init_params(){}
	
	
	private:
	string gvhome;
	int tex_w;
	int tex_h;
	void get_params_from_file();

	
	


};



#endif