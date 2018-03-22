#ifndef GVUTILS_H_INCLUDED
#define GVUTILS_H_INCLUDED

#include <FL/gl.h>
#include <FL/glut.h>
#include <string.h>
#include <time.h>

void print_string(int x, int y, char *str);
void print_string(float x, float y, char *str);
void print_string(float x, float y, const char *str);
void print_string(double x, double y, char *str);
void print_string(float x, float y, float z,  char *str);
void check_GL_errors (char *prefix);

bool leap_year(int year);
double ymdhms_to_jd(int year, int month, int day, int hour, int minute, float sec);
double yd_to_jd(int year, int day, int hour = 0, int minute = 0, int second = 0 );
double jd_to_mjd(double jd);
time_t yd_to_time_t(int year, int day, int hour = 0, int minute = 0, int second = 0);



const char *get_apple_resource_path();
void release_apple_resource();


#endif