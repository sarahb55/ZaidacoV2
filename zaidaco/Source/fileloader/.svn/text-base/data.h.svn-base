#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

/**
 * 
 *  data.h
 *  
 * Purpose: This class holds an array of dataset objects. This
 * It is used by the rest of the program to access the datasets
 * sequentially. It has an index member variable that saves its 
 * plae. The key methods are get_current returns the current
 * dataset, get_next get the next and increments index and
 * get_previous returns the previous dataset. Both get_next and 
 * get_previous loop. You may add a dataset to the data either
 * with puch_back that accepts a pointer to a dataset or with 
 * load_file that take the name of a file and creates a dataset
 * and adds it to the list. 
 * 
 *
 *  Created by Sarah Block on 1/29/07.
 *  Copyright 2007 Sarah Block. All rights reserved.
 *
 */
 
 #include "dataset.h"
 #include "filereader.h"

 #include <vector>
 #include <algorithm> 
 
 using namespace std;

 class data{
 
	public:
	/**
	 * Constructor initializes index to 0
	 */
	data(): _index(0){}
	/**
	 * Destructor
	 *
	 */
	~data(){}
	
	/**
	 * @returns a pointer at a given index if i is in bounds
	 * NULL on failure
	 */	 
	dataset * get_dataset(uint i);
	
	dataset * operator[](uint i);
	
	/**
	 * @return a pointer at a the next index if index + 1 is in bounds
	 * NULL on failure
	 */	 
	dataset * get_next();
	
	/**
	 * @return a pointer at a the previous index if index - 1 is in bounds
	 * NULL on failure
	 */	 
	dataset * get_previous();

	/**
	 * @return a pointer the current element
	 * NULL if no datasets are in the stack
	 */	
	dataset * get_current();
	
	/**
	 * @returns a pointer at a given index if i is in bounds
	 * NULL on failure
	 */	 
	dataset * get_element_at(uint i)
	{	
		if(i >= 0 && i < datasets.size())
		{
			return datasets[i];
		}
		else
		{
			return NULL;
		}
		
	}
	
	/** 
	 * Clears all files from the stach and deallocates memory
	 */
	void clear();	
	
	/**
	 * Removes the dataset at the current _index
	 */ 
	void remove_current_element();
	
	/**
	 * @return the total number of datasets in the data object.
	 */
	int size() { return datasets.size();}
	
	/**
	 * Sends back the index of the current element. 
	 */
	int index(){ return _index; }
	
	/**
	 * Sets the index of the current element to i unless
	 * i is out of bounds in which case it does nothing.
	 */
	void index(uint i)
	{
		if(i >= 0 && i < datasets.size())
		{
			_index = i;
		}
	}
	
	/**
	 * Use this method to add a dataset to the current stack.
	 */
	void push_back(dataset *ds);
	
	/**
	 * This methode will create a dataset object when you send it a file name.
	 * @return true if successful false otherwise
	 *	
	 */
	bool load_file(char *filename);
	
	private:
	vector<dataset *> datasets;
	uint _index;
	
	/**
	 * This method recalculates the internal epochs of all the datasets loaded
	 * each time a dataset o=is added to the stack.
	 */
	void reset_epochs();
	
 
 
 };

#endif //DATA_H_INCLUDED