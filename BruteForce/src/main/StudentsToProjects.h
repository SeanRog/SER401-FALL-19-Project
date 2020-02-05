/*
 * StudentsToProjects.h
 *
 *  Created on: Oct 30, 2019
 *      Created by: Sean, Myles, Cristi, Matthew
 *
 *Description:
 *		This header file stores function declarations for StudentsToProjects.cpp.
 */

#ifndef STUDENTSTOPROJECTS_H_
#define STUDENTSTOPROJECTS_H_

#include<vector>

#include "Student.h"
#include "Team.h"
#include "Project.h"
#include "ClassSection.h"
#include <FL/Fl_Progress.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

using namespace std;

//current value of the progress Bar
extern int progressBarValue;

class StudentsToProjects {
	public:

		StudentsToProjects(); //constructor
		~StudentsToProjects(); //destructor

		// Function to assign the students to projects.
		string StudentsToProjectsAssignment(Student studentPool[],
				Project projectPool[],const int numStudents,const int numProjects, const int numSkills,
				const int teamSize,const int numTopTeams,Fl_Progress* progressBar, int progressIncrement);

		void updateProgressBar(int value, Fl_Progress* pW);//function to update the progress bar.

		bool NegativeAffinityCheck(Student team[5]); //checks a student team to see if their is any negative affinity.
		int getDuplicatesOfStudents(Team currentSet[], int size); //finds the number of duplicate students in a set of teams.

		//Team scoring functions
		int AvailabilityTeamScore(Student team[5]); //compares the availability of students on a team, returns a score 0-20
		int SkillCompareTeamScore(int studentSkills[5]); //compares the skills of students on a team, returns a score 0-40
		//compares the student's skills to the project, returns a score 0-40
	    int ProjectCompareTeamScore( int studentSkills[5], int maxProjectScore);
		int StudentToStudentSkill( int skillsum1, int skillsum2);   //helper function for SkillCompareTeamScore
		int StudentToStudentAvailibility(Student s1, Student s2);   //helper function for AvailabilityTeamScore

		//memory evaluation functions
		int parseLine(char* line);
		int getValuePhy();
		int getValueVirt();

		//function to convert an int to a constant
		constexpr int toConstInt(int constInt);
};

#endif /* BRUTEFORCE_SRC_MAIN_STUDENTSTOPROJECTS_H_ */
