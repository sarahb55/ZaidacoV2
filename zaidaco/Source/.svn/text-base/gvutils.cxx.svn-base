#include "gvutils.h"

void print_string(int x, int y, char *str)
{
	print_string((float) x, (float) y, str);

}

void print_string(int x, int y, const char *str)
{
	print_string((float) x, (float) y, str);

}
void print_string(float x, float y, char *str)
{
	glRasterPos2f(x, y);
	if(!*str)
		return;
	int len = strlen(str);
	for(int i = 0; i < len; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str[i] );
	}

}



void print_string(float x, float y, float z,  char *str)
{
	glRasterPos3f(x, y, z);
	if(!*str)
		return;
	int len = strlen(str);
	for(int i = 0; i < len; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str[i] );
	}

}

void print_string(float x, float y, const char *str)
{
	glRasterPos2f(x, y);
	if(!*str)
		return;
	int len = strlen(str);
	for(int i = 0; i < len; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str[i] );
	}

}


void print_string(double x, double y, char *str)
{
	print_string((float) x, (float) y, str);
}

void print_string(double x, double y, const char *str)
{
	print_string((float) x, (float) y, str);
}

//-----------------------------------------------------------------------------------
//  Check for GL errors -- Copied from HW2 skeleton CSCIE234
//-----------------------------------------------------------------------------------
void check_GL_errors (char *prefix)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        char *errName = "Unknown";
        switch (err) {
            case GL_INVALID_ENUM: errName = "invalid enum";  break;
            case GL_INVALID_VALUE: errName = "invalid value";  break;
            case GL_INVALID_OPERATION: errName = "invalid operation";  break;
            case GL_STACK_OVERFLOW: errName = "stack overflow";  break;
            case GL_STACK_UNDERFLOW: errName = "stack underflow";  break;
            case GL_OUT_OF_MEMORY: errName = "out of memory";  break;
            default: break;
        }
        printf("GL Error (%s): %s\n", prefix, errName);
    }
}

bool leap_year(int year)
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

/*
Code modified from example provided by JL Davis
*/
double yd_to_jd(int year, int day_of_year, int hour, int minute, int second )
{

	/* Make sure year is within range */
	if (year < 1600 || day_of_year < 0) return (0);
	
	int years_from_1600, leap_days, leap_year;
	int days_from_1600;
	
	years_from_1600 = year - 1600;	
	
	double frac_day, mjd, jd;
	
	/*	Now compute number of leap days up to the start of the year
		we are in (i.e., if the year we are in is a leap year do not
		add the leap day yet) */
	leap_days = 0;
	leap_days += (int) ((years_from_1600 - 1) / 4);
	leap_days -= (int) ((years_from_1600 + 99) / 100);
	leap_days += (int) ((years_from_1600 + 399) / 400);
	leap_days += 1;
	leap_days -= (years_from_1600 == 0);

	
	/* Now compute number of days since 1600 */
	days_from_1600 = years_from_1600 * 365 + leap_days  + day_of_year;
	
	/* Compute the mjd and add in the fraction of a day part. The MJD of 1600 Jan 0 is -94554 */
	frac_day  = (double) second / 86400.0  + (double) minute / 1440.0 + (double) hour / 24.0;
	mjd = -94554.0 + (double) days_from_1600 + frac_day;
	
	/* Julian date */
	jd = 2400000.5 + mjd;
	
	/* Return full Julian date */
	return (jd);

}

double jd_to_mjd(double jd)
{

	return jd - 2400000.5;
}
/**



**/
time_t yd_to_time_t(int year, int day_of_year, int hour, int minute, int second )
{
	if(day_of_year < 0 || hour < 0 || minute < 0 || second < 0)
	{
		printf("%d year and %d day hour %d minute %d second %d Returning 0 from yd_to_time_t\n", year,day_of_year, hour, minute, second);
		return 0;
	}
		 
	int years_from_1970 = year - 1970;
	int days_from_1970, leap_days;
	time_t seconds_from_1970;
	
	
	leap_days = 0;
	leap_days += (int) ((years_from_1970 - 2) / 4);
	
	if(leap_year(year))
	{
		leap_days -= 1;
	}
	

	/* Now compute number of days since 1970 */
	days_from_1970 = years_from_1970 * 365 + leap_days  + day_of_year;
	seconds_from_1970 = days_from_1970*24*60*60 + hour*60*60 + minute*60 + second;
	//printf("%d\n", seconds_from_1970);
	return seconds_from_1970;
}

CFURLRef resourcesAbsURL = NULL;
CFURLRef myResourcesURL;
CFStringRef myResourcesPath;

const char *get_apple_resource_path()
{
		
		const char *directory;
		
		CFBundleRef myAppBundle = ::CFBundleGetMainBundle();
		resourcesAbsURL = NULL;
		if (myAppBundle) 
		{
			CFURLRef myResourcesURL = ::CFBundleCopyResourcesDirectoryURL(myAppBundle);
			if (myResourcesURL) 
			{
				
				resourcesAbsURL = ::CFURLCopyAbsoluteURL(myResourcesURL);
				
				myResourcesPath = ::CFURLCopyFileSystemPath(resourcesAbsURL, kCFURLPOSIXPathStyle);
				if (myResourcesPath)
				{
					
					directory  = ::CFStringGetCStringPtr(myResourcesPath, kCFStringEncodingMacRoman);
					
									
				}
				else
				{
					directory = NULL;
				}
								
				
			}
		}


	return directory;
}

void release_apple_resource()
{
				if (myResourcesURL)
				{
					::CFRelease(myResourcesURL);
				}
				if (myResourcesPath)
				{
					::CFRelease(myResourcesPath);
				}
				if(resourcesAbsURL)
				{
					::CFRelease(resourcesAbsURL);
				}


}



