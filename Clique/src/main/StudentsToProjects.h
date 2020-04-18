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

	/*********************************************************
	 * 	NegativeAffinityCheck
	 *	Author: Matthew Cilibraise
	 * 	Description:
	 * 		function checks to see if any students have negative affinity toward one another.
	 * 		If negative affinity between team members IS NOT found, function will return a boolean value of false,
	 * 		If negative affinity between team member IS found, function will return a boolean value of true.
	 * 	Arguments: Student team[5] (the team of students to check)
	 * 	Returns: boolean value depicting whether the team has negative affinity or not.
	 *  	True - If negative affinity between team members IS found
	 *  	False- If negative affinity between team members IS NOT found 	 */
	bool NegativeAffinityCheck(Student team[5]); //checks a student team to see if their is any negative affinity.

	/*********************************************************
	 * 	PositiveAffinityCheck
	 * 	Author: Matthew Cilibraise, Myles Colina
	 * 	Description:
	 * 		function checks to see how many students (if any) have positive affinity toward one another.
	 * 		This function returns the number of positive matches, for use as a tie-breaker when finding
	 * 		team combinations.
	 * 	Arguments: Student team[5] (the team of students to check)
	 * 	Returns: int value depicting how many positive affinity matches there are. 	*/
	int PositiveAffinityCheck(Student team[5]); //checks a student team and counts the number if positive affinity matches.

	/*********************************************************
	 * 	getDuplicatesOfStudents
	 * 	Author: Matthew Cilibraise
	 * 	Description:
	 *  	This function returns the number of duplicate students in a set of teams.
	 *   	Stores the IDs of unique students and compares the student IDs of the
	 *   	teams to that.
	 * 	Arguments:
	 *	 	Team currentSet[] - (array containing all the teams in the set)
	 *	 	int size  - (the number of teams to check in the array)
	 * 	Returns: integer value depicting the number of duplicate students. 	*/
	int getDuplicatesOfStudents(Team currentSet[], int size); //finds the number of duplicate students in a set of teams.

	/*********************************************************
	 * 	replaceDuplicatesOfStudent
	 *	Author: Matthew Cilibraise, Myles Colina
	 * 	Description: This function returns the studetn ID of a single duplicate student
	 * 	Arguments:
	 *		Team currentSet[] - (array containing all the teams in the set)
	 *	 	int size  - (the number of teams to check in the array)
	 * 	Returns: integer value depicting student ID number of a duplicate student. 	*/
	Student replaceDuplicateStudent(Team currentSet[], int size);

	/*********************************************************
	 * 	AvailabilityTeamScore
	 *	Author: Myles Colina
	 *	Description:
	 *		This function returns a score of 0-20 determining
	 * 		the quality of the team by comparing the Availability of students
	 * 		on a team to each other.
	 *
	 *	Arguments: Student team[]
	 * 	Returns: integer value from 0 to 20. 	*/
	int AvailabilityTeamScore(Student team[5]); //compares the availability of students on a team, returns a score 0-20

	/*********************************************************
	 * 	AvailabilityTeamScore4
	 * 	Author: Myles Colina
	 * 	Description: (For teams of 4)
	 * 		This function returns a score of 0-20 determining
	 * 		the quality of the team by comparing the Availability of students
	 * 		on a team to each other.
	 * 	Arguments: Student team[]
	 * 	Returns: integer value from 0 to 20. 	*/
	int AvailabilityTeamScore4(Student team4[5]); //For teams of 4. compares the availability and returns a score 0-20

	/*********************************************************
	 * 	NDA_IPRCheck(
	 *	Description:
	 * 		function checks to see if any students on this team do not want to sign an NDA or IPR agreement.
	 * 		returns false if there the project requires an NDA or an IPR, and a student on the team does not
	 * 		agree to sign one of them.
	 * 	Arguments:
	 *		Student team[5] (the team of students to check)
	 *		Project project
	 * 	Returns: boolean value 	*/
	bool NDA_IPRCheck(Student team[5], Project project); //checks the students against the project's NDA/IPR

	/*********************************************************
	 * 	SkillCompareTeamScore
	 *	Author: Myles Colina
	 * 	Description:
	 * 		This function returns a score of 0-40 determining
	 * 		the quality of the team by comparing the student's skills to each other
	 * 	Arguments: Student team[]
	 * 	Returns: integer value from 0 to 40. 	*/
	int SkillCompareTeamScore(int studentSkills[5]); //compares the skills of students on a team, returns a score 0-40

	/*********************************************************
	 * 	SkillCompareTeamScore4
	 * 	Author: Myles Colina
	 * 	Description: (For teams of 4)
	 * 		This function returns a score of 0-40 determining
	 * 		the quality of the team by comparing the student's skills to each other
	 * 	Arguments: Student team[], int NUM_SKILLS
	 * 	Returns: integer value from 0 to 40. 	*/
	int SkillCompareTeamScore4(int studentSkills4[5], int NUM_SKILLS); //For teams of 4. compares the skills to the project, returns a score 0-40

	/*********************************************************
	 * 	ProjectCompareTeamScore
	 * 	Author: Myles Colina
	 * 	Description:
	 * 		This function returns a score of 0-40 determining
	 * 		the quality of the team by comparing the max skills a team could have
	 *  	on a certain project, to the team's overall skills.
	 * 	Arguments:
	 *		int studentSkills[5] -(each element is sum of each students skills for that project)
	 *		int maxProjectScore - (integer that stores the maximum skill sum a team could possibly have
	 *			for this project.)
	 * 	Returns: integer value from 0 to 40. 	*/
	int ProjectCompareTeamScore(int studentSkills[5], int maxProjectScore);

	/*********************************************************
	 *	StudentToStudentSkill
	 * 	Author: Myles Colina
	 * 	Description:
	 * 		helper function for SkillCompareTeamScore
	 * 	 	returns a student to student comparison score of 0 - 4.
	 * 	Arguments: Student s1, Student s2
	 * 	Returns: integer value from 0 to 4. 	*/
	int StudentToStudentSkill(int skillsum1, int skillsum2); //helper function for SkillCompareTeamScore

	/*********************************************************
	 * 	StudentToStudentAvailibility
	 * 	Author: Myles Colina
	 * 	Description:
	 * 		helper function for AvailabilityTeamScore, compares 2 students
	 * 		returns an Availability comparison score of 0 - 4.
	 * 	Arguments: Student s1, Student s2
	 * 	Returns: integer value from 0 to 4. 	*/
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
