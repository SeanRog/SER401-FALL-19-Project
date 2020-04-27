/****************
 * 	ClassSectionJson.h
 *
 *	Description: (what the class does) - A class to store all the functions for student Json data.
 *      Includes reading in Student Json Files.
 *
 * 	ClassSectionWriter(string filename) - to be implemented in a later sprint.
 *
 * 	getClassSectionJsonObject(string filename, int i) - Reads in a json file pertaining to class sections.
 * 		Retrieves the class section in the json file at index int i.
 * 		Stores that information into a ClassSection instance.
 * 		Returns that instance.
 *
 *  Copyright (C) 2020 ASU
 *	Matthew Cilibraise, Myles Colina, Cristi DeLeo, Elizabeth Marquise, Sean Rogers,
 *	initial idea contributed by Douglas Sandy, All rights reserved
 */

#ifndef CLASSSECTIONJSON_H_
#define CLASSSECTIONJSON_H_

#include "ClassSection.h"
#include <string>

using namespace std;

class ClassSectionJson {
public:
	ClassSectionJson();
	void ClassSectionWriter(string filename);
	ClassSection getClassSectionJsonObject(string filename, int i);
	const int getNumClasses(string filename);
	void getAllClassSectionJsonObjects(string filename, ClassSection courses[]);
	~ClassSectionJson();
};

#endif /* BRUTEFORCE_SRC_MAIN_CLASSSECTIONJSON_H_ */
