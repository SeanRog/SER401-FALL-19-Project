/*
 * Project.h
 *
 *  Created on: Sep 30, 2019
 *      Author: sean
 */

#ifndef PROJECT_H_
#define PROJECT_H_
#include <string>
#include <vector>

class Project {
public:
	//attributes
	std::vector<int> students;//students associated with the project
	std::vector<std::string> projectSkills; //skills required by the project
	int priority;//2 is top priority, 1 is medium priority, 0 is low priority
	int onlineOnCampus;//0 is online only, 1 is on-campus only, 2 is either online or on-campus

	//methods
	Project(char priorityInitializer, std::vector<std::string> skillsRequired, char onlineOnCampus);
	virtual ~Project();
	void addStudent(int studentID);
	void removeStudent(int studentID);
};

#endif /* PROJECT_H_ */
