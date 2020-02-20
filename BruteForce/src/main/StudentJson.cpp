/****************
* StudentJson.cpp
*
*Author(s)  Myles, Crsti, Sean
*
*Description:
*A class to store all the functions for Student Json data.
*Includes reading in Student Json Files.
*
*
* StudentJson() - Constructor
* ~StudentJson()- Destructor
* StudentWriter - to be implemented in a later sprint
*
* getStudentJsonObject(string filename, int i) - Reads a json file given by string filename then reads a Student object from the json file.
* int i selects the Student object to be read. The Student object from the json file is
* then stored into a c++ Student object with all the properties defined by the json Student object.
*
* StudentReaderVector(string filename)  - Reads a json file given by string filename, gets the number of Students in the json file,
* gets the information of each Student, stores each Student in a c++ Student instance,
* then pushes that into vector<Student> allStudents.
*
*/

#include "StudentJson.h"
#include "Student.h"
#include "json/json.h"

#include <fstream>
#include <string>
#include <vector>

using namespace std;

StudentJson::StudentJson() {
	// TODO Auto-generated constructor stub
}

StudentJson::~StudentJson() {
	// TODO Auto-generated destructor stub
}

void StudentJson::StudentWriter(string filename){
	//to be implemented in a later sprint.
}

/*********************************************************
 * getStudentJsonObject
 *
 *Authors: Cristi
 *
 *Description:
 * Reads a json file given by string filename then reads a Student object from the json file.
 * int i selects the Student object to be read. The Student object from the json file is
 * then stored into a c++ Student object with all the properties defined by the json Student object.
 *
 *Arguments:
 *	string filename, int i
 *
 *Returns:
 *	Student object
 *
 *	NOTES:
 *
 *
 */
Student StudentJson::getStudentJsonObject(string filename, int i){

	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	Student student;

	int numSkills = obj["students"].get((int)i, "")["Skills"].size();
	int numTimes = obj["students"].get((int)i, "")["Availability"].size();
	int numAffinities = obj["students"].get((int)i, "")["StudentAffinity"].size();

	student.ASUriteID = obj["students"].get((int)i, "")["ASUriteID"].asString();
	student.StudentID = obj["students"].get((int)i, "")["StudentID"].asInt();
	student.ClassID = obj["students"].get((int)i, "")["ClassID"].asInt();

	for(int j = 0; j < numAffinities; j =j+2) {
		pair <int, bool> x = {obj["students"].get((int)i, "")["StudentAffinity"][j].asInt(), obj["students"].get((int)i, "")["StudentAffinity"][j+1].asBool()};
		student.StudentAffinity.push_back(x);
	}

	for(int j = 0; j < numTimes; j++) {
		student.Availability[j] = (char)obj["students"].get((int)i, "")["Availability"][j].asInt();
	}

	for (int j = 0; j < numSkills; j++) {
		student.Skills[j] = (obj["students"].get((int)i, "")["Skills"][j].asInt());
	}

	return student;
}

/*********************************************************
 * StudentReaderVector
 *
 *Authors: Myles, Sean
 *
 *Description:
 * Reads a json file given by string filename, gets the number of Students in the json file,
 * gets the information of each Student, stores each Student in a c++ Student instance,
 * then pushes that into vector<Student> allStudents.
 *
 *Arguments:
 *	string filename
 *
 *Returns:
 *	void
 *
 *	NOTES:
 *
 *
 */
void StudentJson::StudentReader(string filename){

	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	//vector<Student> allStudents;
	int StudentID;
    int ClassID;
	int skills[7];
	vector< pair <int, bool> > affinity;
	int times[4];

	int numberOfSkills = 0;
	int numberOfTimes = 0;
	int numberOfAff = 0;

    const Json::Value& numberOfStudents = obj["students"];

    //for loop that iterates of the number of students in the Json file
    //and stores them as Student objects vector <Student> allStudents.
	for(int i = 0; i < numberOfStudents.size(); i++) {

		affinity.clear();
        //reading in Student ID
		StudentID = obj["students"].get((int)i, "")["StudentID"].asInt();

		//reading in Class Id
		ClassID = obj["students"].get((int)i, "")["ClassID"].asInt();

		//reading in Student Skills
		numberOfSkills = obj["students"].get((int)i, "")["Skills"].size();
		for(int j = 0; j < numberOfSkills; j++) {
			skills[j] = (obj["students"].get((int)i, "")["Skills"][j].asInt());
		}

		//reading in Student Affinity
		numberOfAff = obj["students"].get((int)i, "")["StudentAffinity"].size();
	    for(int j = 0; j < numberOfAff; j =j+2) {
	    	pair <int, bool> x = {obj["students"].get((int)i, "")["StudentAffinity"][j].asInt(), obj["students"].get((int)i, "")["StudentAffinity"][j+1].asBool()};
	    	affinity.push_back(x);
		}

		//reading in Availability
		numberOfTimes = obj["students"].get((int)i, "")["Availability"].size();
		for(int j = 0; j < numberOfTimes; j++) {
			times[j] = (char)obj["students"].get((int)i, "")["Availability"][j].asInt();
		}

		//Creating the student, and adding the student to the student list
		Student s(StudentID, ClassID, skills, affinity, times);
		allStudents.push_back(s);
	}
}



