/*
 * Utility.h
 *
 * Description:
 * The Utility class is a series of external functions that can be called
 * to perform repeated calculations in the system. These include methods
 * such as initializing student and project pools, determining the size of
 * an incoming data file, and performing matrix multiplication to extract
 * weighted values.
 *
 *
 *  Created on: Oct. 29, 2019
 *      Author: Matt Cilibraise
 *      		Cristi Deleo
 *      		Fall 2019 Team 35
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include "Student.h"
#include "Project.h"
#include "ClassSection.h"

#include <string>
#include <vector>
#include <array>

using namespace std;

class Utility {
    public:
		Utility();

		void initProjectPool(string filename, Project projectPool[], int numProjects);
		void initStudentPool(string filename, Student studentPool[], int numStudents);
		void initClassSectionPool(string filename, ClassSection classSectionPool[],
                Student studentPool[], int numClassSections, int numStudents);
		void initProjectStudentSkills(Project projectPool[], Student studentPool[],
				int projectStudentSkills[], int numProjects, int numStudents, int numSkills);
		int getSizeOfJson(string filename, string key);
		int getProjectXskill(Project projectPool[], int i, int j);
		int getSkillXstudent(Student studentPool[], int i, int j);
		vector<vector<int>> calcProjectXStudentMatrix(vector<Student> students, vector<Project> projects);
		void projectTypePartition(Project projectPool[], int numProjects,
				char t0, char t1, char t2);
		void projectPriorityPartition(Project projectPool[], int numProjects,
				int t0, int t1, int t2);
		void PriorityPartition(Project projectPool[], int numProjects,
				int t0, int t1, int t2);
		void classSectionTypePartition(ClassSection classSectionPool[], int numClassSections,
				char t0, char t1);
		void printIntMatrix(vector<vector<int>> a);
		int** ProjectToSectionPercentages(vector<vector<Student>> studentList,
				vector<Project> projectList, int numProjects, int NumOfClassSections);
		void arrayProjectToSectionPercentages(Project projectPool[],
		        Student studentPool[], ClassSection classSectionPool[], int percentMatrix[],
				int numProjects, int numStudents, int numClassSections,	int numSkills);
		void projectToSectionAssignment(Project projectPool[],
		        Student studentPool[], ClassSection classSectionPool[],
				int numProjects, int numStudents, int numClassSections, int numSkills, int studentsInSections[]);
		void makeProjectJSON(int numProj, int numSkill);
		void makeStudentJSON(int numStud, int numSkill);
		int calc_projects(int numStudents, int teamSize, int minTeamSize);
		int NumOfTeamsOf4(int numStudents, int teamSize);
		vector<vector<string>> toCSVsse (string filename);
		vector<vector<string>> toCSVcse (string filename);
		~Utility();
};

#endif /* SRC_MAIN_UTILITY_H_ */
