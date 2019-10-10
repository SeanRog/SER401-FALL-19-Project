/*
 * Project.cpp
 *
 *  Created on: Sep 30, 2019
 *      Author: sean
 */

#include "Project.h"
#include <iostream>
#include <string>
using namespace std;

/*
 * Set priority and skillsRequired to project.
 */
Project::Project(char priorityInitializer, vector<string> skillsRequired, char onlineOnCampus) {
	if(priorityInitializer < 0) {
		priority = 0;
	} else if(priorityInitializer > 2) {
		priority = 2;
	} else {
		priority = priorityInitializer;
	}
	projectSkills = skillsRequired;
	this->onlineOnCampus = onlineOnCampus;
}

Project::~Project() {
	// TODO Auto-generated destructor stub
}

/*
 * add studentID to vector<int> students
 *
 */
void Project::addStudent(int studentID) {
	students.push_back(studentID);
}

/*
 * remove studentID from vector<int> students
 *
 */
void Project::removeStudent(int studentID) {
	for(unsigned i = 0; i < students.size(); i++) {
		if(students.at(i) == studentID) {
			students.erase(students.begin() + i);
			break;
		}
	}

}


