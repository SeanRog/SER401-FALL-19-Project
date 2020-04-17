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

	/*********************************************************
	 * 	StudentsToProjectsAssignment
	 *
	 *	Authors: Matthew Cilibraise, Myles Colina, Cristi DeLeo, Elizabeth Marquise, Sean Rogers
	 *	Description:
	 *		This function assigns the students taken in, to the projects taken in.
	 *  	It finds all the possible team combinations for all the students, for each project.
	 *  	It stores the top number of teams (user specified) for all the combinations for each project.
	 *  	Then, based on those top teams it finds the combination of combinations of the horizontal mapping
	 *  	of teams to the projects. It stores the highest scoring teams to projects set, that has no duplicate
	 *  	students. If this can not be found, it stores the highest scoring teams to projects set, with the least
	 *  	amount of duplicate students. It then swaps out the duplicate students, with the highest scoring replacement
	 *  	student for that project, making sure that there is no negative affinity on the team.
	 *
	 *	Arguments:
	 *		Student studentPool[],
	 *		Project projectPool[],
	 *		const int numStudents,
	 *		const int numProjects,
	 *		const int numSkills,
	 *		const int teamSize,
	 *		const int numTopTeams,
	 *		Fl_Progress *progressBar,
	 *		int progressIncrement,
	 *		Fl_Text_Buffer *terminal,
	 *		int officialClassID)
	 *
	 *	Returns: void
	 *
	 *	NOTES:
	 *		For the combination of combinations of the horizontal mapping of student teams to projects,
	 *		research code was found here:https://www.geeksforgeeks.org/combinations-from-n-arrays-picking-one-element-from-each-array/
	 *		This was used as a reference when completing this portion of the function.
	 */
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

	/*********************************************************
	 *	parseLine(char *line)
	 * 	Author: Sean Rogers
	 * 	Description: Used to measure system memory usage
	 *	Arguments: char* line
	 *	Returns: integer value.
	 */
	int parseLine(char *line);

	/*********************************************************
	 * 	getValuePhy()
	 * 	Author: Sean Rogers
	 * 	Description: Gets the physical memory usage of the program
	 *	Arguments: nothing
	 *	Returns: integer value.
	 */
	int getValuePhy();

	/*********************************************************
	 * 	getValueVirt()
	 * 	Author: Sean Rogers
	 * 	Description: Gets the virtual memory usage of the program
	 *	Arguments: nothing
	 *	Returns: integer value.
	 */
	int getValueVirt();

	/*********************************************************
	 * 	updateProgressBar(int num, Fl_Progress *pb)
	 * 	Author: Sean Rogers
	 * 	Description: Updates the progress bar in the GUI window.
	 *	Arguments: int num, Fl_Progress* pb
	 *	Returns:integer value.
	 */
	void updateProgressBar(int value, Fl_Progress *pW);

	constexpr int toConstInt(int constInt);
};

#endif /* BRUTEFORCE_SRC_MAIN_STUDENTSTOPROJECTS_H_ */
