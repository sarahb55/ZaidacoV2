/*
 *  map_builder.cxx
 *  
 *	Implementation of map_builder.h
 *
 *  Created by Sarah Block on 2/6/07.
 *  Copyright 2007 Sarah Block All rights reserved.
 *
 */
#define XYZ 3
#include "map_builder.h"
	
map_builder::map_builder(double rad, data *dt, colorbar *cb, animator *anim):
	_radius(1.0),
	_data_index(0),
	_scale(_radius/5.0),
	_XYrot(0), 
	_Zrot(0),  
	_xyz_array(0), 
	_color_array(0),
	_texcoord_array(0), 
	_normal_array(0), 
	_indices_array(0), 
	_xyz_position_array(0),
	_animate(false), 
	_light(true),
	_solid(true),
	_axes(false),
	_coastlines(true),
	_anim(anim),
	_data(dt),
	_cbar(cb),
	_epoch(false)
{		
	_es = new epoch_scale(_data);
	set_up_arrays();
}

map_builder::~map_builder()
{
	if(_xyz_array)
	{
		delete [] _xyz_array;
	}
	if(_color_array)
	{
		delete [] _color_array;
	}
	if(_normal_array)
	{
		delete [] _normal_array;
	}
	if(_texcoord_array)
	{
		delete [] _texcoord_array;
	}
	if(_indices_array)
	{
		delete [] _indices_array;
	}
	if(_xyz_position_array)
	{
		delete [] _xyz_position_array;
	}
	
}
	
void map_builder::initialize_arrays(uint index)
{
	dataset * ds = data_set();
	if(!ds)
		return;
	
	float grid = (float)ds->grid_size();
	int maxI = abs((int)ds->max_latitude()) + abs((int)ds->min_latitude()) + (int)ceil(grid);
	int maxJ = (int)ds->max_longitude() + (int)ceil(grid);
	int size = (int) maxI*maxJ;
	
	
	
	if(!_xyz_array || !_normal_array || !_texcoord_array || !_indices_array || !_color_array || !_xyz_position_array)
	{
		fl_alert(MAP_BUILDER_MEMORY_ALLOCATION_ERROR);
		exit(1);
		
	}
	
	
	
	for(int i = 0; i <= maxI; i++)
	{
		double theta1 = ((double) i)*PI/(180.0) - PI;
		for(int j = 0; j <= maxJ; j++)
		{
			int index = i * maxJ + j;
			double theta3  =  (double)j*PI/180.0;
			
			xyz_position vertex = {0.0, 0.0, 1.0 };
			vertex = evaluate(theta1,theta3, kSphere, index);
			color c1 = _cbar->get_color(_data->get_current()->get_value(index));
			
			if(isnan(_data->get_current()->get_value(index)))
			{
				c1.r = 1.0; c1.g = 1.0; c1.b = 1.0;
			}
			
			_normal_array[3*index] = _xyz_position_array[3*index] = _xyz_array[3*index] = (GLfloat) vertex.x;
			_normal_array[3*index + 1] = _xyz_position_array[3*index + 1] = _xyz_array[3*index + 1] = (GLfloat) vertex.y;
			_normal_array[3*index + 2] = _xyz_position_array[3*index + 2] = _xyz_array[3*index + 2] = (GLfloat) vertex.z;
			
			_color_array[4*index]	  = (GLfloat) c1.r;
			_color_array[4*index + 1] = (GLfloat) c1.g;
			_color_array[4*index + 2] = (GLfloat) c1.b;
			_color_array[4*index + 3] = (GLfloat) 1.0f;
			
			_texcoord_array[2*index]	 =  (GLfloat)  theta3/TWOPI;
			_texcoord_array[2*index + 1] =  (GLfloat) (theta1 + PI)/PI;
						
		}
	}

	//calculate normals -- they are approximated above by the normalized position vector on the sphere.
		
	//Set up index array	
	for (int i = 0; i <= maxI; i++) 
	{
		int index = 0;
		for (int j = 0; j <= maxJ; j++) 
		{
			index = i * maxJ + j;
			_indices_array[2*index] = (GLuint) (index + maxJ);
			_indices_array[2*index + 1] = (GLuint) index;			
		}	
		
	}	
	

	reset_vertices();
	reset_normals();
	
}

void map_builder::set_up_arrays()
{
	dataset * ds = data_set();
	if(!ds)
		return;
	
	float grid = (float)ds->grid_size();
	int maxI = abs((int)ds->max_latitude()) + abs((int)ds->min_latitude())  + (int)ceil(grid);
	int maxJ = (int)ds->max_longitude() + (int)ceil(grid);
	int size = (int) (maxI + 1)*(maxJ + 1);
	
	if(_xyz_array)
	{
		delete [] _xyz_array;
	}
	if(_color_array)
	{
		delete [] _color_array;
	}
	if(_normal_array)
	{
		delete [] _normal_array;
	}
	if(_texcoord_array)
	{
		delete [] _texcoord_array;
	}
	if(_indices_array)
	{
		delete [] _indices_array;
	}
	if(_xyz_position_array)
	{
		delete [] _xyz_position_array;
	}
	
	
	_xyz_array = new GLfloat[3*size];
	_xyz_position_array = new GLfloat[3*size];
	_normal_array = new GLfloat[3*size];
	_texcoord_array = new GLfloat[2*size];
	_indices_array = new GLuint[2*size];
	_color_array = new GLfloat[4*size]; //RGBA
	
	if(!_xyz_array || !_normal_array || !_texcoord_array || !_indices_array || !_color_array || !_xyz_position_array)
	{
		fl_alert(MAP_BUILDER_MEMORY_ALLOCATION_ERROR);
		exit(1);
		
	}
	


}

void  map_builder::draw_map()
{

	dataset * ds = data_set();
	if(!ds)
	{
		return;
	}
		
	float grid = (float)ds->grid_size();
	int maxI = abs((int)ds->max_latitude()) + abs((int)ds->min_latitude() + (int)ceil(grid));
	int maxJ = (int)ds->max_longitude() + (int)ceil(grid);
	int size = (int) (maxI+1)*(maxJ + 1);
	
	if(!_xyz_array || !_normal_array || !_texcoord_array || !_indices_array || !_color_array || !_xyz_position_array)
	{
		return;		
	}
	
	
	glEnableClientState (GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT,0,_normal_array);
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer (3, GL_FLOAT, 0, _xyz_array);
	glEnableClientState (GL_COLOR_ARRAY);
	glColorPointer (4, GL_FLOAT, 0, _color_array);
	glEnableClientState (GL_INDEX_ARRAY	);
	glIndexPointer(GL_UNSIGNED_INT, 0, _indices_array);
	glEnableClientState ( GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, _texcoord_array);
		
	if(_solid)
	{
		glDrawElements(GL_QUAD_STRIP, 2*size, GL_UNSIGNED_INT,_indices_array );
	
	}
	else
	{
		glDrawElements(GL_LINE_STRIP, 2*size, GL_UNSIGNED_INT,_indices_array );
	}

	glDisableClientState (GL_COLOR_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);
	glDisableClientState (GL_INDEX_ARRAY);
	glDisableClientState (GL_TEXTURE_COORD_ARRAY);
	glDisableClientState (GL_NORMAL_ARRAY);
	
}

void map_builder::reset_vertices()
{
	
	dataset * ds = data_set();
	if(!ds)
		return;
	
	float grid = (float)ds->grid_size();
	int maxI = abs((int)ds->max_latitude()) + abs((int)ds->min_latitude())  + (int)ceil(grid);;
	int maxJ = (int)ds->max_longitude() + (int)ceil(grid);
	
	
	for(int i = 0; i <= maxI; i++)
	{
		for(int j = 0; j <= maxJ; j++)
		{
			int index = i * maxJ + j;
			double r = 1.0;
			if(ds->maximum() != ds->minimum())
			{
				if(isnan(ds->get_value(index)) )
				{
					r = _radius;
				}
				else
				{
					r = _radius + _scale*(ds->get_value(index)/fabs(_cbar->get_maxvalue() -_cbar->get_minvalue()));
				}
				_xyz_array[3*index] = r*_xyz_position_array[3*index];
				_xyz_array[3*index + 1] = r*_xyz_position_array[3*index + 1];
				_xyz_array[3*index + 2] = r*_xyz_position_array[3*index + 2] ;
			}
			
		}
		
	}
	
	reset_normals();
	
		
}

void map_builder::reset_normals()
{
	dataset * ds = data_set();
	if(!ds)
		return;
	
	float grid = (float)ds->grid_size();
	int maxI = abs((int)ds->max_latitude()) + abs((int)ds->min_latitude())  + (int)ceil(grid);;
	int maxJ = (int)ds->max_longitude() + (int)ceil(grid);
	
	for(int i = 0; i <= maxI; i++)
	{
		for(int j = 0; j < maxJ; j++)
		{
			int index = 3*(i * maxJ + j);
			xyz_position point, below, next, norm;
			point.x = _xyz_array[index];
			point.y = _xyz_array[index  + 1];
			point.z = _xyz_array[index  + 2];
		
			int b = index + 3*maxJ;
			below.x = _xyz_array[b];
			below.y = _xyz_array[b + 1];
			below.z = _xyz_array[b + 2];
		
			next.x = _xyz_array[index + 3];
			next.y = _xyz_array[index + 4];
			next.z = _xyz_array[index + 5];
			
			if(j == maxJ - 1)
			{
				next.x = _xyz_array[3*(i * maxJ)];
				next.y = _xyz_array[3*(i * maxJ) + 1];
				next.z = _xyz_array[3*(i * maxJ) + 2];
			
			}
						
			norm = normal(point, next, below);
			if(!isnan(norm.x) && !isnan(norm.y) && !isnan(norm.z))
			{
				_normal_array[index] = (GLfloat)  norm.x;
				_normal_array[index + 1] = (GLfloat)  norm.y;
				_normal_array[index + 2] = (GLfloat) norm.z;
			}
		}
	}

}

void map_builder::reset_color()
{
	
	dataset * ds = data_set();
	if(!ds)
		return;
	
	float grid = (float)ds->grid_size();
	int maxI = abs((int)ds->max_latitude()) + abs((int)ds->min_latitude());
	int maxJ = (int)ds->max_longitude() + (int)ceil(grid);
	
	for(int i = 0; i <= maxI; i++)
	{
		for(int j = 0; j <= maxJ; j++)
		{
			int index = i * maxJ + j;
			
			
			if(isnan(ds->get_value(index)))
			{
				_color_array[4*index] = (GLfloat)1.0;
				_color_array[4*index + 1] = (GLfloat) 1.0;
				_color_array[4*index + 2] = (GLfloat) 1.0;
				_color_array[4*index + 3] = (GLfloat) 1.0f;

			}
			else
			{
				color c1 = _cbar->get_color(ds->get_value(index));
				_color_array[4*index] = (GLfloat) c1.r;
				_color_array[4*index + 1] = (GLfloat) c1.g;
				_color_array[4*index + 2] = (GLfloat) c1.b;
				_color_array[4*index + 3] = (GLfloat) 1.0f;
			}
			
			
		}		
		
	}
	
}

xyz_position* map_builder::normalize(xyz_position *p)
{
	if(!p)
		return NULL;
		
	double length;
	
	
	
	length = sqrt(p->x * p->x + p->y * p->y + p->z * p->z);
	if (length != 0) 
	{
		p->x /= length;
		p->y /= length;
		p->z /= length;
	} 
	else 
	{
		p->x = 0;
		p->y = 0;
		p->z = 0;
	}
	
	return p;
}

xyz_position map_builder::normal(xyz_position p, xyz_position p1, xyz_position p2)
{
	xyz_position n,pa,pb;
	
	pa.x = p1.x - p.x;
	pa.y = p1.y - p.y;
	pa.z = p1.z - p.z;
	pb.x = p2.x - p.x;
	pb.y = p2.y - p.y;
	pb.z = p2.z - p.z;
		
	n.x = pa.y * pb.z - pa.z * pb.y;
	n.y = pa.z * pb.x - pa.x * pb.z;
	n.z = pa.x * pb.y - pa.y * pb.x;
	normalize(&n);
	
	return(n);
}

/**
 * Calculates xyz values for a given longitude and latitude.
 * 
 * lat range from 0 to PI. lon ranges from -PI to PI.
 */
xyz_position map_builder::evaluate(double lat, double lon, int type, int index)
{
	xyz_position p = {0,0,1};
	
	switch (type) 
	{
		case kSphere:
			p.x = cos(lon)*sin(lat);
			p.y = sin(lon)*sin(lat);
			p.z = cos(lat);
			break;
		case kPlane:
			p.x = lon + PI_OVER_TWO;
			p.y = lat - PI;
			p.z =  _radius;
			break;	
		default:
			p.x = 0.0;
			p.y = 0.0;
			p.z = 0.0;
			break;
 	}
	
	return(p);
}

/**
 * Used by other methods to get the array of data values to draw.
 */
dataset *  map_builder::data_set()
{
	dataset *ds = NULL;
	
	if(!_animate || _data->size() <= 1 || !_anim)
	{
		ds = _data->get_current();	
	}
	else
	{	
		ds = _anim->get_frame();	
	}
	
	return ds;	
}

/**
 * For now the lighting is set constant. This could be modified to allow
 * some flexibily in the way the image looks.
 */
void map_builder::set_lighting(unsigned int mode, int w, int h)
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	
	if(w > h)
		glOrtho(-1.5,  1.5,-1.5*(GLfloat)h/(GLfloat)w, 1.5*(GLfloat)h/(GLfloat)w, -25.0, 25.0);
	else
		glOrtho(-1.5,  1.5,-1.5*(GLfloat)w/(GLfloat)h, 1.5*(GLfloat)w/(GLfloat)h, -25.0, 25.0);


	glMatrixMode (GL_MODELVIEW); //So the lighting adjust when you rotate the figure.
	glLoadIdentity();

	GLfloat mat_specular[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat mat_shininess[] = {10.0};
	GLfloat position[4] = {0.0,150.0,150.0,0.0};
	GLfloat ambient[4]  = {0.2,0.2,0.2,1.0};
	GLfloat diffuse[4]  = {1.0,1.0,1.0,1.0};
	GLfloat specular[4] = {0.2,0.2,0.2,1.0};
	
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);
	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	glLightfv(GL_LIGHT0,GL_POSITION, position);
	glLightfv(GL_LIGHT0,GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);
	
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
}

/**
 * Draws x,y,z axes and antialiases ligns.
 */
void map_builder::draw_axes()
{

	glEnable (GL_SMOOTH); //For antialiasing lines.
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_LINES);
	glColor3f(1.0, 0,0);
	glVertex3f(-_radius - 1.0, 0.0, 0.0);
	glVertex3f(_radius + 1.0, 0.0, 0.0);
	glColor3f(0.0, 1.0,0);
	glVertex3f(0.0,-_radius - 1.0,  0.0);
	glVertex3f( 0.0,_radius + 1.0, 0.0);
	glColor3f(0.0, 0.0,1.0);
	glVertex3f(0.0, 0.0, -_radius - 1.0);
	glVertex3f( 0.0,0.0, _radius + 1.0);	
	glEnd();
	
	//Make labels
	glColor3f(0.0, 0.0,1.0);
	print_string(0.0,0.0,_radius + 0.1,MAP_BUILDER_Z_NORTH);
	glColor3f(1.0, 0,0);
	print_string(-_radius - 0.1,0.0,0.0, MAP_BUILDER_X_0);
	glColor3f(0.0, 1.0,0);
	print_string(0.0, _radius + 0.1,0.0,MAP_BUILDER_Y_90_EAST); 
	
	glDisable (GL_DEPTH_TEST);
	glDisable (GL_SMOOTH);
	glDisable (GL_BLEND);

}



void map_builder::draw_map(int w, int h)
{
	
	glPushMatrix();
	
	glEnable(GL_DEPTH_TEST);
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	
	float width = 1.8f;
	
	if(w > h)
		glOrtho(-width,  width,-width*(GLfloat)h/(GLfloat)w, width*(GLfloat)h/(GLfloat)w, -25.0, 25.0);
	else
		glOrtho(-width*(GLfloat)w/(GLfloat)h, width*(GLfloat)w/(GLfloat)h, -width,  width, -25.0, 25.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	glRotated(-90.0, 1.0, 0.0, 0.0);		
	glRotated(_XYrot, 1.0, 0.0, 0.0);
	glRotated(_Zrot, 0.0, 0.0, 1.0);
	
	if(_light)
	{
		glEnable(GL_LIGHTING);
	}

	if(_coastlines)
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	}

	draw_map();
	
	if(_coastlines)
	{
		glDisable(GL_TEXTURE_2D);
	}
	if(_light)
	{
		glDisable(GL_LIGHTING);
	}
	
	if(_axes)
	{
		draw_axes();
	}
	
		
	glPopMatrix();
	
	
	if(_epoch)
	{
		
	if(!_animate || _data->size() <= 1)
	{
		if(_data->get_current() && _es)
		{
			_es->draw_scale(w, h, _data->get_current()->epoch_internal());	
		}
	}
	else
	{
		if(_es)
		{
			_es->draw_scale(w, h, _anim->percent_complete());
		}
	}
	
	}
	
}