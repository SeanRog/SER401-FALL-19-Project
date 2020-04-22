/****************
 * 	StudentJson.h
 *
 *	Description: Header file for StudentJson.cpp.

 * 	StudentJson() - Constructor
 * 	~StudentJson()- Destructor
 * 	StudentWriter - to be implemented in a later sprint
 *
 * 	getStudentJsonObject(string filename, int i) - Reads a json file given by string filename then reads a Student object from the json file.
 * 		int i selects the Student object to be read. The Student object from the json file is
 * 		then stored into a c++ Student object with all the properties defined by the json Student object.
 *
 * 	StudentReaderVector(string filename)  - Reads a json file given by string filename, gets the number of Students in the json file,
 * 		gets the information of each Student, stores each Student in a c++ Student instance,
 * 		then pushes that into vector<Student> allStudents.
 *
 *  Copyright (C) 2020 ASU
 *	Matthew Cilibraise, Myles Colina, Cristi DeLeo, Elizabeth Marquise, Sean Rogers,
 *	initial idea contributed by Douglas Sandy, All rights reserved
 *
 */

#ifndef STUDENTJSON_H_
#define STUDENTJSON_H_

#include <vector>
#include <string>

#include "Student.h"

namespace std {

class StudentJson {
public:
	vector<Student> allStudents;
	StudentJson();
	~StudentJson();
	void StudentReader(string filename);
	void StudentWriter(string filename);
	Student getStudentJsonObject(string filename, int i);
};
}
#endif /* BRUTEFORCE_SRC_MAIN_STUDENTJSON_H_ */
