#ifndef LMS_SUITE_VERSION_H
#define LMS_SUITE_VERSION_H

namespace lms_suite{
	
	//Date Version Types
	static const char DATE[] = "23";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.07";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 54;
	static const long REVISION  = 250;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 466;
	#define RC_FILEVERSION 1,0,51,246
	#define RC_FILEVERSION_STRING "1, 0, 51, 246\0"
	static const char FULLVERSION_STRING [] = "1.0.51.246";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 55;
	

}
#endif //LMS_SUITE_VERSION_H
