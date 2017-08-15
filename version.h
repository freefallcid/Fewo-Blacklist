/* 
 * Ferienwohnung Blacklist Version Information
 * File:   version.h
 *
 * Author: Dominic Reich <dominic@mm.st>
 * Created on 20. Februar 2016, 16:15
 * Last modified: Samstag, 20.02.2016 20:13
 *
 * This file is licensed under the terms of the MIT license
 */

#ifndef VERSION_H
#define	VERSION_H

namespace Version{
	
	//Software Status
	static const char STATUS[] =  "Beta";
	static const char STATUS_SHORT[] =  "b";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 2;
	static const long BUILD  = 1;
	//static const long REVISION  = 0;
	
	//Miscellaneous Version Types
	//static const long BUILDS_COUNT  = 0;
	static const char FULLVERSION_STRING [] = "0.2.1";

}

#endif	/* VERSION_H */
