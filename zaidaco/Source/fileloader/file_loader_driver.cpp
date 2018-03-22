/*
 *  file_loader_driver.cpp
 *  COLOR
 *
 *  Created by Sarah Block on 1/29/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
 
 #include "dataset.h"
 #include "data.h"
 #include "filereader.h"
 
 #include <iostream>
 
 using namespace std;

int main(int argv, char *argc[])
{
	cout << "Hello" << endl;


	dataset *ds = new dataset(10);
	data dvs; 
	dataset p;
	
	for(int i = 0; i < 10; i++)
	{
		ds->push_back((double) i);
	}
	
	dvs.push_back(ds);
	
	double * v = dvs[0]->get_values();
	
	for(int i = 0; i < 10; i++)
	{
		cout << v[i] << endl;
	}
	
	p = *ds;
	
	p.compute_standard_of_deviation();
	
	for(int i = 0; i < 10; i++)
	{
		cout << p[i] << "mean = " << p.mean() << " and std = " << p.standard_of_deviation() << endl;
	}
	
	dataset *ds2 = new dataset(180*360);
	filereader fr;
	fr.read_file("/Users/sblock/COLOR/ylm33.xyz", ds2,0);
		
	for(int i =0; i < 720; i++)
	{
		cout << ds2->get_value(i) << endl;
	}

	
	return 0;
}

