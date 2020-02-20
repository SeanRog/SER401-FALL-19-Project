/*
 * Project.h
 *
 * Description:
 * Student to project allocation requires a model of a project in such a manner
 * that allows the system to match up projects to students allocated into a team
 * and partition project populations based on target characteristics. Unique
 * identifiers are captured, such as the ProjectID, and relational attributes are
 * defined, such as the ClassID and Type, that will help keep track of what
 * projects are available to each instance of a student. Each instance of a
 * project represents a project sponsored in real life; prioritized for
 * student allocation.
 *
 * Created on: Oct 27, 2019
 *      Author: Myles Colina & Fall 2019 SER401 Team35
 *
 */

#ifndef PROJECT_H_
#define PROJECT_H_

#include <array>

struct Project {
	int ProjectID; 	// Unique integer identifying the project uniquely in the whole project population.
	int ClassID; 	// Unique integer depicting the Class/Section the project is contained in.
	int PoolID;    	// Common integer to keep track of project in data structures. Used in determining index number in StudetsToProjects.

	/* char Type - 	Projects can be dedicated to local students of the university, online students, or a combination.
	 * 				Type is defined as: O = online | G = ground | H = hybrid
	 */
	char Type;

	/* int Priority -	Projects are given a measure of priority for student team allocation by the faculty.
	 * 					Some projects absolutely must be assigned to fulfill contractual obligations to various non-academic sponsors,
	 * 					while some projects are deemed to be "nice to offer" to students
	 * 					Type is defined as: 0 = does not have to be assigned | 1 = preferred to be assigned | 2 = must be assigned
	 */
	int Priority;

	/* Skills - Information is gathered from project Sponsors which will include skill sets
	 * 			that may be needed by Students to successfully work on a Project. Project skills
	 * 			are matched up by the system to Student skills to dynamically create a weighted
	 * 			value of each students ability to work on the project. Unlike the Student's
	 * 			Skill values, which represent the strength of a Student's ability with the skill,
	 * 			Project skills represent whether the skill is required, nice to have, or not required
	 * 			for the Project. Skills will hold an integer array that stores integer values.
	 * 			Each value represents the need for a Student's Skill.
	 * 			Project Skills are defined as:
	 * 			0 = not required | 1 = nice to have skill | 2 = required skill
	 */
	int Skills[7];

	Project(){}
	//Constructor
	Project(int pID, char t, int priority, int pskills[]){
		ProjectID = pID;
		Type = t;
		Priority = priority;
		for (int i = 0; i < 7; i++){
		      Skills[i] = pskills[i];
		}
	}
};

#endif
