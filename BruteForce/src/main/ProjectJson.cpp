/****************
* ProjectJson.cpp
*
*Author(s) Myles, Crsti, Sean
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
*/

#include "ProjectJson.h"
#include "Project.h"
#include "json/json.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <array>

using namespace std;

ProjectJson::ProjectJson() {
	// TODO Auto-generated constructor stub
}

ProjectJson::~ProjectJson() {
	// TODO Auto-generated destructor stub
}

void ProjectJson::ProjectWriter(string filename){
	//to be implemented in a later sprint.
}

/*********************************************************
 * getProjectJsonObject
 *
 *Authors: Cristi
 *
 *Description:
 * Reads a json file given by string filename then reads a project object from the json file.
 * int i selects the project object to be read. The project object from the json file is
 * then stored into a c++ Project object with all the properties defined by the json project object.
 *
 *Arguments:
 *	string filename, int i
 *
 *Returns:
 *	Project object
 *
 *	NOTES:
 *
 *
 */
Project ProjectJson::getProjectJsonObject(string filename, int i){

	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	Project project;

	project.ProjectID = (char)obj["projects"].get((int)i, "")["ProjectID"].asInt();

	string temp;
	temp = obj["projects"].get((int)i, "")["Type"].asString();
	project.Type = temp[0];

	project.Priority = (char)obj["projects"].get((int)i, "")["Priority"].asInt();

	int numSkills = obj["projects"].get((int)i, "")["Skills"].size();

	for (int j = 0; j < numSkills; j++) {
		project.Skills[j] = (obj["projects"].get((int)i, "")["Skills"][j].asInt());
	}

	return project;
}

/*********************************************************
 * ProjectReaderVector
 *
 *Authors: Myles, Sean
 *
 *Description:
 * Reads a json file given by string filename, gets the number of projects in the json file,
 * gets the information of each project, stores each project in a c++ Project instance,
 * then pushes that into vector<Project> allProjects.
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
void ProjectJson::ProjectReaderVector(string filename){
	//read file named profile.json, then parse it as json, then store that parse into obj
	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	//get the size of the "projects" array in the json file, then store that into numberOfProjects
	const int numberOfProjects = obj["projects"].size();

	int numberOfSkills = 0;
	int skills[7];
	int ProjectID;
	int Priority = 0;
	char Type;

	// for each project in the json file, store the information into a Project object,
	//then push that object to vector<Project> allProjects
	for(int i = 0; i < numberOfProjects; i++) {

		// read in the ProjectID
		ProjectID = (char)obj["projects"].get((int)i, "")["ProjectID"].asInt();

		// read in the priority
		Priority = (char)obj["projects"].get((int)i, "")["Priority"].asInt();

		//read in the skills
		numberOfSkills = obj["projects"].get((int)i, "")["Skills"].size();
					for(int j = 0; j < numberOfSkills; j++) {
						skills[j] = (obj["projects"].get((int)i, "")["Skills"][j].asInt());
					}

		// read in the type
		string temp;
		temp = obj["projects"].get((int)i, "")["Type"].asString();
		Type = temp[0];

		//create the project object
		Project p( ProjectID, Type, Priority, skills);
		allProjects.push_back(p);
	}
}

