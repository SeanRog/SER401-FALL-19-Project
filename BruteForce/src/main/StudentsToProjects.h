/*
 *	StudentsToProjects.h
 *
 * 	Description:
 *	This header file stores function declarations for StudentsToProjects.cpp.
 *
 *	Copyright (C) 2020 ASU
 *	Matthew Cilibraise, Myles Colina, Cristi DeLeo, Elizabeth Marquise, Sean Rogers,
 *	initial idea contributed by Douglas Sandy, All rights reserved
 */

#ifndef STUDENTSTOPROJECTS_H_
#define STUDENTSTOPROJECTS_H_

#include <vector>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Box.H>
#include "Student.h"
#include "Team.h"
#include "Project.h"
#include "ClassSection.h"

using namespace std;

// variable for progress Bar
extern int progressBarValue;


class StudentsToProjects {
public:
	StudentsToProjects();
	~StudentsToProjects();

	string StudentsToProjectsAssignment(
			Student studentPool[],
			Project projectPool[],
			const int numStudents,
			const int numProjects,
			const int numSkills,
			const int teamSize,
			const int numTopTeams,
			Fl_Progress *progressBar,
			int progressIncrement,
			Fl_Text_Buffer *terminal,
			int officialClassID);

	bool NegativeAffinityCheck(Student team[5]); //checks a student team to see if their is any negative affinity.
	int PositiveAffinityCheck(Student team[5]); //checks a student team and counts the number if positive affinity matches.
	int getDuplicatesOfStudents(Team currentSet[], int size); //finds the number of duplicate students in a set of teams.
	Student replaceDuplicateStudent(Team currentSet[], int size);
	int AvailabilityTeamScore(Student team[5]); //compares the availability of students on a team, returns a score 0-20
	int AvailabilityTeamScore4(Student team4[5]); //For teams of 4. compares the availability and returns a score 0-20
	bool NDA_IPRCheck(Student team[5], Project project); //checks the students against the project's NDA/IPR
	int SkillCompareTeamScore(int studentSkills[5]); //compares the skills of students on a team, returns a score 0-40
	int SkillCompareTeamScore4(int studentSkills4[5], int NUM_SKILLS); //For teams of 4. compares the skills to the project, returns a score 0-40
	int ProjectCompareTeamScore(int studentSkills[5], int maxProjectScore);
	int StudentToStudentSkill(int skillsum1, int skillsum2); //helper function for SkillCompareTeamScore
	int StudentToStudentAvailibility(Student s1, Student s2); //helper function for AvailabilityTeamScore
	int parseLine(char *line);
	int getValuePhy();
	int getValueVirt();
	constexpr int toConstInt(int constInt);
	void updateProgressBar(int value, Fl_Progress *pW); //function to update the progress bar.
};

#endif /* BRUTEFORCE_SRC_MAIN_STUDENTSTOPROJECTS_H_ */
