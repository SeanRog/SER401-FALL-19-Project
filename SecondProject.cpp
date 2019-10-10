//============================================================================
// Name        : SecondProject.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include "Project.h"
#include <fstream>
#include <jsoncpp/json/json.h>

using namespace std;

int main() {
	//read file named profile.json, then parse it as json, then store that parse into obj
	ifstream ifs("profile.json");
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	//get the size of the "projects" array in the json file, then store that into numberOfProjects
	const int numberOfProjects = obj["projects"].size();
	vector<Project> projects;
	vector<string> skills;

	int numberOfSkills = 0;

	int priority = 0;
	int onlineOnCampus = 0;

	// for each project in the json file, store the information into a Project object, then push that object to vector<Project> projects
	for(int i = 0; i < numberOfProjects; i++) {
		skills.clear();
		numberOfSkills = obj["projects"].get((int)i, "")["skills"].size();
		for(int j = 0; j < numberOfSkills; j++) {
			skills.push_back(obj["projects"].get((int)i, "")["skills"][j].asString());
		}

		priority = (char)obj["projects"].get((int)i, "")["priority"].asInt();
		onlineOnCampus = (char)obj["projects"].get((int)i, "")["online/oncampus"].asInt();
		Project p(priority, skills, onlineOnCampus);
		projects.push_back(p);
	}

	// for each Project object, print its information to ensure success
	for(unsigned int i = 0; i < projects.size(); i++) {
		cout << "Project ";
		cout << i+1 << endl;
		cout << "Skills: ";
		for (unsigned int j = 0; j < projects.at(i).projectSkills.size(); j++) {
			cout << projects.at(i).projectSkills.at(j);
			cout << " ";
		}
		cout << endl;
		cout << "Priority: ";
		cout << projects.at(i).priority << endl;
		cout << projects.at(i).onlineOnCampus << endl;
		cout << endl;
	}

	return 1;

}
