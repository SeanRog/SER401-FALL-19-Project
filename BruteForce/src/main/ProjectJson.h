/****************
* ProjectJson.h
*
*Author(s) Myles, Cristi, Sean
*
*Description:
*A class to store all the functions for Project Json data.
*Includes reading in Project Json Files.
*
*
* ProjectJson() - Constructor
* ~ProjectJson()- Destructor
* ProjectWriter - to be implemented in a later sprint
*
* getProjectJsonObject(string filename, int i) - Reads a json file given by string filename then reads a project object from the json file.
* int i selects the project object to be read. The project object from the json file is
* then stored into a c++ Project object with all the properties defined by the json project object.
*
* ProjectReaderVector(string filename)  - Reads a json file given by string filename, gets the number of projects in the json file,
* gets the information of each project, stores each project in a c++ Project instance,
* then pushes that into vector<Project> allProjects.
*
*
*/

#ifndef PROJECTJSON_H_
#define PROJECTJSON_H_

#include "Project.h"

#include <array>
#include <vector>
#include <string>

using namespace std;

class ProjectJson {
	public:
		int numProjects;
		vector<Project> allProjects;
		ProjectJson();
		~ProjectJson();
		Project getProjectJsonObject(string filename, int i);
		void ProjectWriter(string filename);
		void ProjectReaderVector(string filename);
};

#endif /* BRUTEFORCE_SRC_MAIN_PROJECTJSON_H_ */
