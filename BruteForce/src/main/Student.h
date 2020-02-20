/*
 * Student.h
 *
 * Description:
 * Student to project allocation requires a model of a student in such a manner
 * that allows for the system to allocate students based on target characteristics
 * and partitioning student populations into managed clusters. Unique identifiers
 * are captured, such as the StudentID, and relational attributes are defined, such
 * as the class # ClassID, that helps keep track of what projects are available
 * to each instance of a student. Each instance of a student represents
 * a real student seeking to matched up with the best project possible allowed.
 *
 * Created on: Oct 27, 2019
 * Author: Myles Colina & Fall 2019 SER401 Team35
 *
 *
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <array>

using namespace std;

struct Student {
	string ASUriteID; //unique String ID for each ASU student.
	int StudentID; //Unique integer identifying the student uniquely in the whole student population.
	int StID; //Common integer to keep track of student in data structures. ID depicting from [0 - NumOfStudents] in that class section.
	int ClassID; //Unique integer depicting the Class/Section the student is assigned to.
	int PoolID;//for use in determining index number in StudetsToProjects.
	bool Assigned;  //for use to see if the student is assigned to a project yet.
	int ProjectID; //Value given once the student is assigned to a project.


	/* Skills - Students are given a survey in which they indicate their familiarity or
	 * 			strengths among [seven] predefined skills. Skills will hold an integer array
	 * 			that stores integer values. Each value represents the strength or value of each
	 * 			of the predefined skills. Each value is rated on a five point scale:
	 * 			0 = none | 1 = some | 2 = average | 3 = proficient | 4 = expert
	 */
	int Skills[7];
	double skillAverage; //Average skill of the student, used from skills above

	 /* vector<pair<int,bool>> StudentAffinity	- Students, additionally, are allowed in indicate other students that they
	 * 											would prefer to work with and not work with. This is defined as the
	 * 											the student's affinity toward other students. Affinity is instrumental
	 * 											for creating teams of students to allocate to class projects.
	 * 											Each student is given a dynamic array that will store pair values of
	 * 											an integer and a boolean value. The integer represents another student's
	 * 											StudentID and the boolean value evaluates true (1) if the current
	 * 											Student wants to work with the other student and false (0) if the
	 * 											current Student wants to avoid working with the other student.
	 * 											[0]PeerID | 0 = negative affinity | 1 = positive affinity
	 */
	 vector< pair <int, bool> > StudentAffinity;

	 /* Availability -	Students indicate their preferred meeting times on the student survey.
	 * 					A students preferred meeting times are stored in an integer array
	 * 					containing [Four] availability slots represented by the number of elements
	 * 					allowed in the array. The time slots are defined as the following:
	 * 					[0] Primary Weekday | [1] Secondary Weekday | [2] Primary Weekend | [3] Secondary Weekend
	 *
	 * 					Each time slot will hold an integer value from 0 to 5. These values
	 * 					represent the time of day the student prefers to meet.
	 * 					The times of day are defined as:
	 *
	 * 					|0 = Night-time:   12:00AM - 4:00AM |1 = Early Morning: 4:00AM - 8:00AM |
	 *					|2 = Morning:      8:00AM - 12:00PM |3 = Afternoon:    12:00PM - 4:00PM |
	 *					|4 = Early Evening: 4:00PM - 8:00PM |5 = Evening:      8:00PM - 12:00AM |
	 */
	int Availability[4];
	/*
	 * Default Student Constructor
	 *
	 * Creates default student object
	 */
	Student(){}
	/*
	 * Defined Student Constructor
	 *
	 * Creates defined student object with specific attributes
	 *
	 * Arguments:
	 * int stID - Unique integer identifying the student uniquely in the whole student population.
	 * int cID - Unique integer depicting the Class/Section the student is assigned to.
	 * int s[] - Student's Skill array
	 * vector<pair<int,bool>> aff - Student's affinity vector
	 * int times[] - student's availablity or preferred meeting times array
	 */
	Student(int stID, int cID, int s[], vector< pair <int, bool> > aff,
            int times[]){

		StudentID = stID;
        ClassID = cID;

        for (int i = 0; i < 7; i++){
        	Skills[i] = s[i];
        }

        for (int i = 0; i < aff.size(); i++){
        	pair <int, bool> x = {aff[i].first, aff[i].second};
        	StudentAffinity.push_back(x);
        }

        for (int i = 0; i < 4; i++){
        	Availability[i] = times[i];
        }
	}

	bool operator==(const Student &studentToCompare) const {
		if(this->StudentID == StudentID) {
			return true;
		} else {
			return false;
		}
	}


};

#endif /* BRUTEFORCE_SRC_MAIN_STUDENT_H_ */

