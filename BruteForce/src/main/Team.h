/*
 * Team.h
 *
 * Description:
 * Student to project allocation requires a model of a Student team
 * to facilitate decision mechanisms such as student affinity toward
 * each other and preferred meeting times. Additionally teams are
 * formed based on partitioned sections of students based on skill
 * set strength. Relational attributes include ProjectID, the
 * project that the team is assigned too, and an aggregate team
 * score based on skills. The student team is represented by
 * an array of Student objects. Each team created is a possible
 * combination and may or may not represent a real world student
 * team.
 *
 *  Created on: Nov 11, 2019
 *      Author: Myles Colina & Fall 2019 SER401 Team35
 *
 */

#ifndef TEAM_H_
#define TEAM_H_

#include <iostream>
#include <utility>
#include <string>
#include <array>
#include "Student.h"


using namespace std;

//template<int teamsize>
struct Team {

	Student team[5]; 	// Array of Student objects to store and manipulate.
	int TeamScore; 		// TeamScore is an aggregate value of each Student's weighed skill scores.
	int projectID;		// represents the project that the student team is possibly assigned to.
	Team(){}

};

#endif /* TEAM_H_ */
