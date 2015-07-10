#ifndef LMS_SUITE_VERSION_H
#define LMS_SUITE_VERSION_H

namespace lms_suite{
	
	//Date Version Types
	static const char DATE[] = "01";
	static const char MONTH[] = "06";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.06";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 49;
	static const long REVISION  = 246;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 462;
	#define RC_FILEVERSION 1,0,49,246
	#define RC_FILEVERSION_STRING "1, 0, 49, 246\0"
	static const char FULLVERSION_STRING [] = "1.0.49.246";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 49;
	

}
#endif //LMS_SUITE_VERSION_H
