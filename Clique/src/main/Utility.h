/*
 * Utility.h
 *
 * Description:
 * 		The Utility class is a series of external functions that can be
 * 		called to perform repeated calculations in the system. These
 * 		include methods such as initializing student and project pools,
 * 		determining the size of an incoming data file, and performing
 * 		matrix multiplication to extract weighted values.
 *
 *
 *  Copyright (C) 2020 ASU
 *	Matthew Cilibraise, Myles Colina, Cristi DeLeo, Elizabeth Marquise, Sean Rogers,
 *	initial idea contributed by Douglas Sandy, All rights reserved
 *
 *
 * List of Functions:
 * void initProjectPool(string filename, Project projectPool[],int numProjects)
 * 		- Initializes the project pool
 *
 * void initstudentPool(string filename, Student studentPool[],int numStudents)
 * 		- Initializes the Student pool
 *
 * void initClassSectionPool(string filename, ClassSection classSectionPool[],
 *  Student studentPool[],int numClassSections, int numStudents)
 * 		- Initializes the Class Section pool
 *
 * void initProjectStudentSkills(Project projectPool[], Student studentPool[],
 *  int projectStudentSkills[], int numProjects, int numStudents, int numSkills)
 *  	- completes a dot product matrix of project skills x student skills
 *  	in order to created weighted values representing a student's skill
 *  	strength compared to a projects recommended skills.
 *
 * int getSizeOfJson(string filename, string key)
 * 		- returns the size of a Json data file
 *
 * int getProjectXskill(Project projectPool[], int i, int j)
 * 		- returns a project's skill value
 *
 * int getSkillXstudent(Student studentPool[], int i, int j)
 * 		- returns a student's skill value
 *
 * vector<vector<int>> calcProjectXStudentMatrix(vector<Student> students,
 *	vector<Project> projects)
 *		- Deprecated method used to calculate and return vector of
 *		ProjectxStudent weighted skills.use initProjectStudentSkills
 *		instead for better runtime.
 *
 * void projectTypePartition(Project projectPool[], int numProjects,
 *  char t0, char t1, char t2)
 *		- Partitions the project pool by project type
 *
 * void projectPriorityPartition(Project projectPool[], int numProjects,
 *  int t0, int t1, int t2)
 *  	- Partitions the project pool by project priority
 *
  * void tPriorityPartition(Project projectPool[], int numProjects,
 *  int t0, int t1, int t2)
 *  	- Partitions the project pool by project priority
 *
 * void classSectionTypePartition(ClassSection classSectionPool[],
 *  int numClassSections, char t0, char t1)
 *		- Partitions the class section by type.
 *
 * void printIntMatrix(vector<vector<int>> a)
 * 		- prints an int matrix
 *
 * int ** ProjectToSectionPercentages(vector<vector<Student>> studentList,
 *  vector<Project> projectList, int numProjects, int NumOfClassSections)
 * 		- Function returns a 2d array  [number of projects][ number of class
 * 		sections] containing the percentages, 0-100, of how the students
 * 	 	in a class section compare to that project
 *
 * void arrayProjectToSectionPercentages(Project projectPool[],
 *  Student studentPool[], ClassSection classSectionPool[],
 *  int percentMatrix[], int numProjects, int numStudents,
 *  int numClassSections, int numSkills)
 * 		- ARRAY VERSION. Function calculates the  percentages, 0-100,
 * 		of how the students in a class section compare to that project
 *
 * void projectToSectionAssignment(Project projectPool[],
 *  Student studentPool[], ClassSection classSectionPool[], int numProjects,
 *	int numStudents, int numClassSections, int numSkills, int studentsInSections[])
 *   	- This function assigns the projects to class sections based on the
 *   	Project's type and priority, the class section percentage scores, and
 *   	the minimum number of projects each class section can have.
 *
 * void makeProjectJSON(int numProj, int numSkill)
 * 		- creates a new Json file  with random data
 *
 * void makeProjectCSV(int numProj, int numSkill)
 * 		- creates a new CSV file with random data
 *
 * void generateTestStudents(int numStud, int numSkill,
 *  vector<vector<Student>> studentsFromCanvas, ClassSection course)
 * 		- creates a Json file of test students for a given class
 * 		section with given number of students
 *
 * void makeStudentJSON(int numStud, int numSkill,
	vector<vector<Student>> studentsFromCanvas)
 *		- creates a new Json file with random
 * 		data for a specified number of students.
 *
 * void makeStudentCSV(int numStud, int numSkill)
 *		- creates a new CSV file with random
 * 		data for a specified number of students.
 *
 * void makeCanvasStudentRosterJSON(int numStud, int numSkill,
 *  vector<vector<Student>> studentsFromCanvas,
 *  vector<ClassSection> allClassSections)
 *		- creates a new Json file with random
 * 		data for a specified number of students.
 *
 * void makeClassSectionJSON(vector<ClassSection> allClassSections)
 * 		- creates a new Json file that contains all the selected class
 * 		sections that the user wants to make team assignments for.
 *
 * int calc_projects(int numStudents, int teamSize, int minTeamSize)
 *		- finds the minimum number of projects needed
 *
 * int NumOfTeamsOf4(int numStudents, int teamSize)
 * 		- returns the number of teams that will have 4 members.
 *
 * vector<vector<string>> toCSVsse(string filename)
 * 		- Takes in a file, then outputs the CSV from that file.
 *
 * vector<vector<string>> toCSVcse(string filename)
 *		- takes in a file, then outputs the CSV from that file.
 *
 * vector <Project> csvToProjectsVector(string filename,
 *	Project projectPool[], int numProjects, int numSkills)
 *		-  takes in a CSV file, puts the projects into project objects,
 *		then places each project object into a vector 7 returns
 *
 * int getQuizID(string quizName, string filename)
 *		- Reads in all the quizzes from a Json file, and searches
 *		for the quiz ID of the that matches the string name
 *
 * int getAssignmentID(int quiz_ID, string filename)
 *		- Reads in all the assignments from a Json file, and searches
 *		for the assignment ID of the assignment whose quiz_id that
 *		matches the parameter quiz_id .
 *
  * int getCategoryID(int courseID, string filename)
 * 		- Reads in all the group categories from a Json file,
 * 		and searches for the category ID of the group category
 * 		whose course_id that matches the parameter course_id .
 *
 * int getGroupID(int course_ID, string filename)
 * 		- Reads in the group data from a Json file, and searches
 * 		for the Group ID of the group whose course_id that
 *		matches the parameter course_id .
 *
 * vector<Student> Utility::getStudentsFromJson(string filename)
 * 		- Reads in the students from a JSON file and returns them
 * 		in a vector
 *
 * vector<Student> Utility::getSurveyAnswers(vector<Student> students,
 *	int assignment_ID, string filename)
 * 		-  Reads in all the Survey quiz answers from a Json file,
 * 		and matches the answers to the student whose ID matches.
 */
#ifndef UTILITY_H_
#define UTILITY_H_


/********* BEGINNING OF INCLUSIONS **********/


/* Class Inclusions */
#include "Student.h"
#include "Project.h"
#include "ClassSection.h"


/* Library inclusions */
#include <string>
#include <vector>
#include <array>


using namespace std;


 /********* BEGINNING OF Program Code **********/


class Utility {
public:

	// methods in class
	Utility();
	void initProjectPool(string filename, Project projectPool[],
			int numProjects);
	void initStudentPool(string filename, Student studentPool[],
			int numStudents);
	void initClassSectionPool(string filename, ClassSection classSectionPool[],
			Student studentPool[], int numClassSections, int numStudents);
	void initProjectStudentSkills(Project projectPool[], Student studentPool[],
			int projectStudentSkills[], int numProjects, int numStudents,
			int numSkills);
	int getSizeOfJson(string filename, string key);
	int getProjectXskill(Project projectPool[], int i, int j);
	int getSkillXstudent(Student studentPool[], int i, int j);
	vector<vector<int>> calcProjectXStudentMatrix(vector<Student> students,
			vector<Project> projects);
	void projectTypePartition(Project projectPool[], int numProjects, char t0,
			char t1, char t2);
	void projectPriorityPartition(Project projectPool[], int numProjects,
			int t0, int t1, int t2);
	void PriorityPartition(Project projectPool[], int numProjects, int t0,
			int t1, int t2);
	void classSectionTypePartition(ClassSection classSectionPool[],
			int numClassSections, char t0, char t1);
	void printIntMatrix(vector<vector<int>> a);
	int** ProjectToSectionPercentages(vector<vector<Student>> studentList,
			vector<Project> projectList, int numProjects,
			int NumOfClassSections);
	void arrayProjectToSectionPercentages(Project projectPool[],
			Student studentPool[], ClassSection classSectionPool[],
			int percentMatrix[], int numProjects, int numStudents,
			int numClassSections, int numSkills);
	void projectToSectionAssignment(Project projectPool[],
			Student studentPool[], ClassSection classSectionPool[],
			int numProjects, int numStudents, int numClassSections,
			int numSkills, int studentsInSections[]);
	void makeProjectJSON(int numProj, int numSkill);
	void makeProjectCSV(int numProj, int numSkill);
	void generateTestStudents(int numStud, int numSkill,
				vector<vector<Student>> studentsFromCanvas, ClassSection course);
	void makeStudentJSON(int numStud, int numSkill, vector<vector<Student>> studentsFromCanvas);
	void makeStudentCSV(int numStud, int numSkill);
	void makeCanvasStudentRosterJSON(int numStud, int numSkill, vector<vector<Student>> studentsFromCanvas,
			vector <ClassSection> allClassSections);
	void makeClassSectionJSON(vector<ClassSection> allClassSections);
	int calc_projects(int numStudents, int teamSize, int minTeamSize);
	int NumOfTeamsOf4(int numStudents, int teamSize);
	vector<vector<string>> toCSVsse(string filename);
	vector<vector<string>> toCSVcse(string filename);
	vector<Project> csvToProjectsVector(string filename, Project projectPool[], int numProjects, int numSkills);
	int getQuizID(string quizName, string filename);
	int getAssignmentID(int quiz_ID, string filename);
	int getCategoryID(int courseID, string filename);
	int getGroupID(int course_ID ,string filename);
	vector <Student> getSurveyAnswers(vector <Student> students, int assignment_ID, string filename);
	vector<Student> getStudentsFromJson(string filename);
	~Utility();

};

#endif /* SRC_MAIN_UTILITY_H_ */
