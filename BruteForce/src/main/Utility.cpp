/*
 * Utility.cpp
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
 *      Authors: Fall 2019 Team 35 (Matthew, Cristi, Myles, Elizabeth, Sean)
 *
 * List of function:
 *  (see header file Utility.h)
 *
 */

#include "Utility.h"
#include "json/json.h"
#include "ProjectJson.h"
#include "StudentJson.h"
#include "ClassSectionJson.h"
#include "Project.h"
#include "Student.h"
#include "ClassSection.h"
#include "FakeStudentNames.h"

#include <iostream>
#include <utility>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

Utility::Utility() {
	// TODO Auto-generated constructor stub
}

Utility::~Utility() {
	// TODO Auto-generated destructor stub
}

/***********************************************
 * initProjectPool
 *
 * Description:
 * Initializes the project pool
 *
 * Arguments:
 * filename - name of data file
 * projectPool[] - pointer to the project pool
 * numProjects - integer value of the number of projects to be initialized
 *
 * returns -
 * void method.
 */
void Utility::initProjectPool(string filename, Project projectPool[],
		int numProjects) {
	ProjectJson PJson;
	for (int i = 0; i < numProjects; i++) {
		*(projectPool + i) = PJson.getProjectJsonObject(filename, i);
	}
}

/***********************************************
 * initStudentPool
 *
 * Description:
 * Initializes the student pool
 *
 * Arguments:
 * filename - name of data file
 * studentPool[] - pointer to the student pool
 * numStudents - integer value of the number of students to be initialized
 *
 * returns -
 * void method.
 */
void Utility::initStudentPool(string filename, Student studentPool[],
		int numStudents) {
	StudentJson SJson;
	for (int i = 0; i < numStudents; i++) {
		*(studentPool + i) = SJson.getStudentJsonObject(filename, i);
	}
}

/***********************************************
 * initClassSectionPool
 *
 * Description:
 * Initializes the classSection pool
 *
 * Arguments:
 * filename - name of data file
 * classSectionPool[] - pointer to the classSection pool
 * studentPool[] - pointer to the studentPool
 * numClassSections - integer value of the number of classSections.
 * numStudents - integer value of the number of students to be initialized
 *
 * returns -
 * void method.
 */
void Utility::initClassSectionPool(string filename,
		ClassSection classSectionPool[], Student studentPool[],
		int numClassSections, int numStudents) {
	ClassSectionJson CSJson;
	Student student;
	ClassSection classSection;

	for (int i = 0; i < numClassSections; i++) {
		classSection = CSJson.getClassSectionJsonObject(filename, i);
		int count = 0;
		for (int j = 0; j < numStudents; j++) {
			student = *(studentPool + j);
			if (student.ClassID == classSection.ClassID) {
				count++;
			}
		}
		classSection.Enrollment = count;
		*(classSectionPool + i) = classSection;
	}
}
/***********************************************
 * initProjectStudentSkills
 *
 * Description:
 * completes a dot product matrix of project skills x student skills
 * in order to created weighted values representing a student's skill strength
 * compared to a projects recommended skills.
 *
 * Arguments:
 * projectPool[] - pointer to the projectPool
 * studentPool[] - pointer to the studentPool
 * projectStudentSkills[] - pointer to the array storing weighted values
 * numProjects - integer value of the number of projects.
 * numStudents - integer value of the number of students
 * numSkills - integer value of the number of skills evaluated
 *
 * returns -
 * void method.
 */
void Utility::initProjectStudentSkills(Project projectPool[],
		Student studentPool[], int projectStudentSkills[], int numProjects,
		int numStudents, int numSkills) {

	int score = 0;

	for (int i = 0; i < numProjects; i++) {
		Project project;
		project = *(projectPool + i);
		for (int j = 0; j < numStudents; j++) {
			Student student;
			student = *(studentPool + j);
			score = 0;
			for (int k = 0; k < numSkills; k++) {
				score += project.Skills[k] * student.Skills[k];
			}

			*(projectStudentSkills + (i * numStudents) + j) = score;
		}
	}
}

/***********************************************
 * getSizeOfJson
 *
 * Description:
 * returns the size of a Json data file
 *
 * Arguments-
 * filename - name of Json data file
 * key - value to be targeted and counted
 *
 * returns -
 * obj[key].size()
 */
int Utility::getSizeOfJson(string filename, string key) {
	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	return obj[key].size();
}

/*************************************************
 * getProjectXskill
 *
 * Description:
 * returns a project's skill value to be used in matrix multiplication
 *
 * Arguments:
 * projectPool[] - pointer to the project pool
 * i - row value of project
 * j - column value of skill
 *
 * Returns:
 * project.Skills[j] - current iteration project's skill value.
 */
int Utility::getProjectXskill(Project projectPool[], int i, int j) {
	Project project;
	project = *(projectPool + i);
	return project.Skills[j];
}

/*/*************************************************
 * getSkillXstudent
 *
 * Description:
 * returns a student's skill value to be used in matrix multiplication
 *
 * Arguments:
 * studentPool[] - pointer to the project pool
 * i - row value of Student
 * j - column value of skill
 *
 * Returns:
 * student.Skills[j] - current iteration student's skill value.
 */
int Utility::getSkillXstudent(Student studentPool[], int i, int j) {
	Student student;
	student = *(studentPool + i);
	return student.Skills[j];
}

/*/*************************************************
 * calcProjectXStudentMatrix
 *
 * Description:
 * Deprecated method used to calculate and return vector of ProjectxStudent weighted skills.
 * use initProjectStudentSkills instead for better runtime.
 */
vector<vector<int>> Utility::calcProjectXStudentMatrix(vector<Student> students,
		vector<Project> projects) {
	int numStudents = students.size();
	int numProjects = projects.size();
	int numSkills = (sizeof(students.at(0).Skills)
			/ sizeof(*students.at(0).Skills));
	vector<vector<int>> projectXstudentMatrix;
	// create projectXskill matrix
	int projectXskill[numProjects][numSkills] = { 0 };
	for (int i = 0; i < numProjects; i++) {
		for (int j = 0; j < numSkills; j++) {
			projectXskill[i][j] = projects.at(i).Skills[j];
		}
	}
	// create skillXstudent matrix transposing skills and students
	int skillXstudent[numSkills][numStudents] = { 0 };
	for (int i = 0; i < numSkills; i++) {
		for (int j = 0; j < numStudents; j++) {
			skillXstudent[i][j] = students.at(j).Skills[i];
		}
	}
	//cout << "\t";
	for (int i = 0; i < numStudents; i++) {
		//cout << "st" << students.at(i).StudentID << "\t";
	}
	cout << endl;
	int projectXstudent[numProjects][numStudents];
	for (int rows = 0; rows < numProjects; rows++) {
		// print project name to projectxstudent matrix
		//string p = to_string(rows);
		//cout << "p" + p + "\t";
		// do the multiplication
		for (int cols = 0; cols < numStudents; cols++) {
			projectXstudent[rows][cols] = { 0 };
			for (int inner = 0; inner < numSkills; inner++) {
				projectXstudent[rows][cols] = projectXstudent[rows][cols]
						+ projectXskill[rows][inner]
								* skillXstudent[inner][cols];

			}
			//cout << projectXstudent[rows][cols] << "\t\t";
		}
		//cout << "\n";
	}
	for (int i = 0; i < numProjects; i++) {
		vector<int> currProject;
		for (int j = 0; j < numStudents; j++) {
			int studentScore = projectXstudent[i][j];
			currProject.push_back(studentScore);
		}
		projectXstudentMatrix.push_back(currProject);
	}
	return projectXstudentMatrix;
} // end calcProjectXStudentMatrix

/*************************************************
 * projectTypePartition
 * AUTHOR: CRISTI DELEO
 *
 * Description:
 *  Partitions the project pool by project type
 *  (ONLINE = O | GROUND = G | HYBRID = H)
 *
 * Arguments:
 * Project projectPool[],
 * int numProjects,
 *	char t0, char t1, char t2
 *
 * Returns:
 *    nothing
 */
void Utility::projectTypePartition(Project projectPool[], int numProjects,
		char t0, char t1, char t2) {

	int start = 0;
	int end = numProjects - 1;
	int t0Index = 0;

	for (int i = 0; i <= end;) {
		if (projectPool[i].Type == t0) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Type != t0) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}

	t0Index = 0;

	for (int i = 0; i <= end;) {
		if (projectPool[i].Type == t0) {
			t0Index++;
			i++;
		} else {
			i++;
		};
	}

	start = t0Index;
	end = numProjects - 1;

	for (int i = t0Index; i <= end;) {
		if (projectPool[i].Type == t1) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Type != t1) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}
}

/*************************************************
 * projectPriorityPartition
 * AUTHOR: CRISTI DELEO
 *
 * Description:
 *  Partitions the project pool by project priority
 *  (PRIMARY = 2 | SECONDARY = 1 | TERTIARY = 0)
 *
 * Arguments:
 * Project projectPool[],
 * int numProjects,
 *	int t0, int t1, int t2
 *
 * Returns:
 *    nothing
 */
void Utility::projectPriorityPartition(Project projectPool[], int numProjects,
		int t0, int t1, int t2) {

	int start = 0;
	int end = numProjects - 1;
	int t0Index = 0;
	int endG = 0;
	int endO = 0;
	int endH = 0;

	for (int i = 0; i < numProjects; i++) {
		if (projectPool[i].Type == 'O') {
			endO++;
		}
	}

	endG = endO;

	for (int i = 0; i < numProjects; i++) {
		if (projectPool[i].Type == 'G') {
			endG++;
		}
	}

	endH = endG;

	for (int i = 0; i < numProjects; i++) {
		if (projectPool[i].Type == 'H') {
			endH++;
		}
	}

// SORT ONLINE PROJECTS
	start = 0;
	t0Index = start;
	end = endO - 1;

	for (int i = 0; i <= end;) {
		if (projectPool[i].Priority == t0) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Priority != t0) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}

	t0Index = 0;

	for (int i = 0; i <= end;) {
		if (projectPool[i].Priority == t0) {
			t0Index++;
			i++;
		} else {
			i++;
		};
	}

	start = t0Index;
	end = endO - 1;

	for (int i = t0Index; i <= end;) {
		if (projectPool[i].Priority == t1) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Priority != t1) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}

// SORT GROUND PROJECTS
	start = endO;
	t0Index = start;
	end = endG - 1;

	for (int i = 0; i <= end;) {
		if (projectPool[i].Priority == t0) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Priority != t0) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}

	t0Index = endO;

	for (int i = 0; i <= end;) {
		if (projectPool[i].Priority == t0) {
			t0Index++;
			i++;
		} else {
			i++;
		};
	}

	start = t0Index;
	end = endG;

	for (int i = t0Index; i <= end;) {
		if (projectPool[i].Priority == t1) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Priority != t1) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}

// SORT HYBRID PROJECTS
	start = endG;
	t0Index = start;
	end = endH - 1;

	for (int i = 0; i <= end;) {
		if (projectPool[i].Priority == t0) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Priority != t0) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}

	t0Index = endG;

	for (int i = 0; i <= end;) {
		if (projectPool[i].Priority == t0) {
			t0Index++;
			i++;
		} else {
			i++;
		};
	}

	start = t0Index;
	end = endH - 1;

	for (int i = t0Index; i <= end;) {
		if (projectPool[i].Priority == t1) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Priority != t1) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}
}

void Utility::PriorityPartition(Project projectPool[], int numProjects, int t0,
		int t1, int t2) {

	int start = 0;
	int end = numProjects - 1;
	int t0Index = 0;

// SORT PROJECTS
	start = 0;
	t0Index = start;

	for (int i = 0; i <= end;) {
		if (projectPool[i].Priority == t0) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Priority != t0) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}

	t0Index = 0;
	end = numProjects - 1;

	for (int i = 0; i <= end;) {
		if (projectPool[i].Priority == t0) {
			t0Index++;
			i++;
		} else {
			i++;
		};
	}

	start = t0Index;
	end = numProjects - 1;

	for (int i = t0Index; i <= end;) {
		if (projectPool[i].Priority == t1) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Priority != t1) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}

}

/*************************************************
 * classSectionTypePartition
 *
 * Description:
 *  Partitions the class section by type.
 *  (ONLINE = O | GROUND = G )
 *
 * Arguments:
 * Project projectPool[],
 * int numProjects,
 *	char t0, char t1
 *
 * Returns:
 *    nothing
 */
void Utility::classSectionTypePartition(ClassSection classSectionPool[],
		int numClassSections, char t0, char t1) {

	int start = 0;
	int end = numClassSections - 1;

	for (int i = 0; i <= end;) {
		if (classSectionPool[i].Type == t0) {
			swap(classSectionPool[i++], classSectionPool[start++]);
		} else if (classSectionPool[i].Type != t0) {
			swap(classSectionPool[i], classSectionPool[end--]);
		} else {
			i++;
		};
	}
}

/*************************************************
 * printIntMatrix
 *
 * Description:
 *  Prints an int matrix
 *
 * Arguments:
 * vector<vector<int>> a
 *
 * Returns:
 *    nothing
 */
void Utility::printIntMatrix(vector<vector<int>> a) {
	cout << endl;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.at(i).size(); j++) {
			cout << a.at(i).at(j) << "\t";
		}
		cout << endl;
	}
}

/*************************************************
 * ProjectToSectionPercentages
 *
 * Description:
 *   Function returns a 2d array [number of projects] [ number of class sections]
 *   containing the percentages, 0-100, of how the students in a class section compare to that project
 *
 * Arguments:
 * vector<vector<Student>> studentList,
 * vector<Project> projectList,
 * int numProjects,
 * int NumOfClassSections
 *
 * Returns:
 *    int 2d array
 */
int** Utility::ProjectToSectionPercentages(vector<vector<Student>> studentList,
		vector<Project> projectList, int numProjects, int NumOfClassSections) {

	//create a 2d array containing the sum of all the students skills, for each skill.
	int SectionSkills[NumOfClassSections][7] = { 0 };
	int numStudentsByClass[NumOfClassSections];

	Student student;
	Project project;

	for (int i = 0; i < NumOfClassSections; i++) {
		//number of students in class sections
		int numStudents = studentList[i].size();
		numStudentsByClass[i] = numStudents;

		for (int j = 0; j < numStudents; j++) {
			student = studentList[i][j];
			for (int k = 0; k < 7; k++) {
				SectionSkills[i][k] += student.Skills[k];
			}
		}
	}

	//Print out to make sure Section Skills is correct.
	/*cout <<endl;
	 cout<<"Class Section Skills Matrix"<<endl;
	 for (int i = 0; i < NumOfClassSections; ++i)
	 {
	 for (int j = 0; j < 7; j++)
	 {
	 cout << SectionSkills[i][j] << ' ';
	 }
	 cout <<endl;
	 }*/

	//create skillXproject matrix
	int skillXproject[numProjects][7] = { 0 };

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < numProjects; j++) {
			skillXproject[i][j] = projectList[j].Skills[i];
		}
	}

	//Print out to make sure skillXproject is correct
	/*cout <<endl;
	 cout<<"Project Skills Matrix"<<endl;
	 for (int i = 0; i < 7; ++i) {
	 for (int j = 0; j < numProjects; j++) {
	 cout << skillXproject[i][j] << ' ';
	 }
	 cout <<endl;
	 }*/

	// Calculate Project x Section skills Matrix
	int projectXsection[numProjects][NumOfClassSections];

	for (int rows = 0; rows < numProjects; rows++) {
		// do the multiplication
		for (int cols = 0; cols < NumOfClassSections; cols++) {
			projectXsection[rows][cols] = { 0 };
			for (int inner = 0; inner < 7; inner++) {
				projectXsection[rows][cols] = projectXsection[rows][cols]
						+ SectionSkills[cols][inner]
								* skillXproject[inner][rows];
			}
		}
	}

	//Print out to make sure projectXsection is correct
	/* cout <<endl;
	 cout<<"projectXsection Matrix"<<endl;
	 for (int i = 0; i < numProjects; ++i) {
	 for (int j = 0; j < NumOfClassSections; j++) {
	 cout << projectXsection[i][j] << ' ';
	 }
	 cout <<endl;
	 }*/

	//create a 2d array for the projects, containing the maximum
	//skill score sum a student could have on that project.
	int ProjectSkills[numProjects][1] = { 0 };

	for (int i = 0; i < numProjects; i++) {
		int sum = 0;
		for (int j = 0; j < 7; j++) {
			sum = sum + projectList[i].Skills[j];
		}
		ProjectSkills[i][0] = sum * 4;
	}

	//Print out to make sure ProjectSkills is correct
	/*	  cout <<endl;
	 cout<<"ProjectSkills Matrix"<<endl;
	 for (int i = 0; i < numProjects; ++i) {
	 cout << ProjectSkills[i][0] << ' ';
	 cout <<endl;
	 }*/

	//gets the percentages and stores them in a new 2d matrix.
	int **percentMatrix = 0;
	percentMatrix = new int*[numProjects];

	for (int i = 0; i < numProjects; i++) {
		percentMatrix[i] = new int[NumOfClassSections];
		for (int j = 0; j < NumOfClassSections; j++) {
			float percent = 0;
			float x = 0;
			x = (ProjectSkills[i][0] * numStudentsByClass[j]);
			percent = projectXsection[i][j] / x;
			percent = percent * 100;
			percent = (int) percent;

			//store percentage in matrix as int, so if 88.8, it will be 88.
			percentMatrix[i][j] = percent;
		}
	}
	return percentMatrix;
}    //end ProjectToSectionPercentages

// ARRAY VERSION
/*************************************************
 * arrayProjectToSectionPercentages
 *
 * Description:
 *   ARRAY VERSION. Function calculates the percentages, 0-100, of how the students
 *    in a class section compare to that project
 *
 * Arguments:
 * Project projectPool[],
 * Student studentPool[],
 * ClassSection classSectionPool[],
 * int percentMatrix[], int numProjects, int numStudents,
 * int numClassSections, int numSkills
 *
 * Returns:
 *    nothing
 */
void Utility::arrayProjectToSectionPercentages(Project projectPool[],
		Student studentPool[], ClassSection classSectionPool[],
		int percentMatrix[], int numProjects, int numStudents,
		int numClassSections, int numSkills) {

	//create a 2d array containing the sum of all the students skills, for each skill.
	int SectionSkills[numClassSections * numSkills] = { 0 };
	int numStudentsByClass[numClassSections] = { 0 };

	Student student;
	Project project;
	ClassSection classSection;

	for (int i = 0; i < numClassSections; i++) {
		classSection = *(classSectionPool + i);
		numStudentsByClass[i] = classSection.Enrollment;
		for (int j = 0; j < numStudentsByClass[i]; j++) {
			student = *(studentPool + j);
			for (int k = 0; k < numSkills; k++) {
				SectionSkills[(i * numSkills) + k] += student.Skills[k];
			}
		}
	}

	//create skillXproject matrix
	int skillXproject[numProjects * numSkills];

	for (int i = 0; i < numSkills; i++) {
		for (int j = 0; j < numProjects; j++) {
			project = *(projectPool + j);
			skillXproject[(i * numProjects) + j] = project.Skills[i];
		}
	}

	// Calculate Project x Section skills Matrix
	int projectXsection[numProjects * numClassSections] = { 0 };

	for (int i = 0; i < numProjects; i++) {
		for (int j = 0; j < numClassSections; j++) {
			projectXsection[(i * numClassSections) + j] = { 0 };
			for (int k = 0; k < numSkills; k++) {
				projectXsection[(i * numClassSections) + j] += SectionSkills[(j
						* numSkills) + k]
						* skillXproject[(k * numProjects) + i];
			}
		}
	}

	//create a 2d array for the projects, containing the maximum
	//skill score sum a student could have on that project.
	int ProjectSkills[numProjects] = { 0 };

	for (int i = 0; i < numProjects; i++) {
		int sum = 0;
		project = *(projectPool + i);
		for (int j = 0; j < numSkills; j++) {
			sum += project.Skills[j];
		}
		ProjectSkills[i] = sum * 4;
	}

	//gets the percentages and stores them in a new 2d matrix.
	//int percentMatrix[numProjects][numClassSections] = {0};

	for (int i = 0; i < numProjects; i++) {
		for (int j = 0; j < numClassSections; j++) {
			float percent = 0;
			float x = 0;
			x = (ProjectSkills[i] * numStudentsByClass[j]);
			percent = projectXsection[(i * numClassSections) + j] / x;
			percent = percent * 100;
			percent = (int) percent;

			//store percentage in matrix as int, so if 88.8, it will be 88.
			percentMatrix[(i * numClassSections) + j] = percent;
		}
	}
	//return  percentMatrix;
}    //end ProjectToSectionPercentages

/*************************************************
 * projectToSectionAssignment
 *
 * Description:
 *   This function assigns the projects to class sections based on the
 *   Project's type and priority, the class section percentage scores, and
 *   the minimum number of projects each class section can have.
 *   This function assigns the minimum number of projects to each class section,
 *   based on the number of students in that class section.
 *   The extra projects are discarded (assigned to non-existent class section, 99999).
 *
 * Arguments:
 * Project projectPool[],
 * Student studentPool[],
 * ClassSection classSectionPool[],
 * int numProjects, int numStudents, int numClassSections,
 * int numSkills, int studentsInSections[]
 *
 * Returns:
 *    nothing
 */
void Utility::projectToSectionAssignment(Project projectPool[],
		Student studentPool[], ClassSection classSectionPool[], int numProjects,
		int numStudents, int numClassSections, int numSkills,
		int studentsInSections[]) {

	//create a 2d array containing the sum of all the students skills, for each skill.
	int SectionSkills[numClassSections * numSkills] = { 0 };

	Student student;
	Project project;
	ClassSection classSection;

	for (int i = 0; i < numClassSections; i++) {

		classSection = *(classSectionPool + i);

		for (int j = 0; j < numStudents; j++) {
			student = *(studentPool + j);
			if (student.ClassID == classSection.ClassID) {
				for (int k = 0; k < numSkills; k++) {
					SectionSkills[(i * numSkills) + k] += student.Skills[k];
				}
			}
		}
	}

	//create skillXproject matrix
	int skillXproject[numProjects * numSkills];

	for (int i = 0; i < numProjects; i++) {
		for (int j = 0; j < numSkills; j++) {
			project = *(projectPool + i);
			skillXproject[(i * numSkills) + j] = project.Skills[j];
		}
	}

	// Calculate Project x Section skills Matrix
	int projectXsection[numProjects * numClassSections] = { 0 };

	for (int i = 0; i < numProjects; i++) {

		project = *(projectPool + i);

		for (int j = 0; j < numClassSections; j++) {

			classSection = *(classSectionPool + j);
			projectXsection[(i * numClassSections) + j] = { 0 };

			if (project.Type == classSection.Type || project.Type == 'H') {
				for (int k = 0; k < numSkills; k++) {
					projectXsection[(i * numClassSections) + j] +=
							(SectionSkills[(j * numSkills) + k]
									* skillXproject[(i * numSkills) + k]);
				}
			}
		}
	}

	//vector to store the minimum number of projects that should be assigned to each class section.
	vector<int> MinProjectsPerClassSection;
	for (int i = 0; i < numClassSections; i++) {
		int minNumProjects = calc_projects(studentsInSections[i], 5, 4);
		MinProjectsPerClassSection.push_back(minNumProjects);

		cout << "Class section: " << i << " Number of students:"
				<< studentsInSections[i] << " MinNumofProjects Required: "
				<< minNumProjects << endl;
	}

	//increment vector to store the number of projects that have been assigned to a class section.
	vector<int> ProjectsToClassCount;
	for (int i = 0; i < numClassSections; i++) {
		ProjectsToClassCount.push_back(0);
	}

	//--Assignment of class sections begins here.-----

	int highestScore;
	int currentScore;
	int highestClassSection;
	int randInt;
	char online = 'O';
	char ground = 'G';
	//vector to store all class sections
	vector<ClassSection> ClassSections;
	//vector to store all online class sections
	vector<ClassSection> OnlineClassSections;
	//vector to store all ground class sections
	vector<ClassSection> GroundClassSections;

	for (int i = 0; i < numClassSections; i++) {
		classSection = *(classSectionPool + i);
		ClassSections.push_back(*(classSectionPool + i));

		if (classSection.Type == 'O') {
			OnlineClassSections.push_back(*(classSectionPool + i));

		} else if (classSection.Type == 'G') {
			GroundClassSections.push_back(*(classSectionPool + i));

		}

	}


	cout<<"All projects to be assigned"<<endl;

	for (int i = 0; i < numProjects; i++) {


		project = *(projectPool + i);
		highestScore = 0;
		highestClassSection = 0;

		cout<<project.ProjectID<<endl;

//Assign the Online projects
		if (projectPool[i].Type == 'O') {

			//refill vector if empty
			if (OnlineClassSections.empty()) {
				for (int k = 0; k < numClassSections; k++) {
					classSection = *(classSectionPool + k);
					if (classSection.Type == 'O') {
						OnlineClassSections.push_back(*(classSectionPool + k));

					}
				}
			}

			for (int j = 0; j < OnlineClassSections.size(); j++) {

				classSection = OnlineClassSections[j];
				currentScore = projectXsection[(i * numClassSections)
						+ OnlineClassSections[j].ClassID];

				//make sure that this class section has not reached the minNumOfProjects added.
				if (ProjectsToClassCount[OnlineClassSections[j].ClassID]
						< MinProjectsPerClassSection[OnlineClassSections[j].ClassID]) {
					if (currentScore > highestScore) {
						highestScore = currentScore;
						highestClassSection = OnlineClassSections[j].ClassID;
					} else if (currentScore == highestScore
							&& currentScore != 0) {
						randInt = rand() % 2;
						if (randInt == 1) {
							highestClassSection =
									OnlineClassSections[j].ClassID;
						}
					}
				}
			}

			// Checks to make sure the highest score is greater than 0
			// If highest score = 0, then project and class section
			// types did not match
			if (highestScore > 0 || OnlineClassSections.size() == 1) {
				for (int j = 0; j < OnlineClassSections.size(); j++) {

					if (OnlineClassSections[j].ClassID == highestClassSection
							|| OnlineClassSections.size() == 1) {
						if (ProjectsToClassCount[OnlineClassSections[j].ClassID]
								< MinProjectsPerClassSection[OnlineClassSections[j].ClassID]) {
							classSection = OnlineClassSections[j];
							projectPool[i].ClassID = classSection.ClassID;
							//projectPool[i].OfficialClassID = classSection.OfficialClassID;
							OnlineClassSections.erase(
									OnlineClassSections.begin() + j);
							//increment the number of projects added to this class section
							ProjectsToClassCount[classSection.ClassID]++;
						}
					}
				}

			}

//Assign the Ground Projects
		} else if (projectPool[i].Type == 'G') {

			//refill vector if empty
			if (GroundClassSections.empty()) {
				for (int k = 0; k < numClassSections; k++) {
					classSection = *(classSectionPool + k);
					if (classSection.Type == 'G') {
						GroundClassSections.push_back(*(classSectionPool + k));

					}
				}
			}

			for (int j = 0; j < GroundClassSections.size(); j++) {

				classSection = GroundClassSections[j];
				currentScore = projectXsection[(i * numClassSections)
						+ GroundClassSections[j].ClassID];

				//make sure that this class section has not reached the minNumOfProjects added.
				if (ProjectsToClassCount[GroundClassSections[j].ClassID]
						< MinProjectsPerClassSection[GroundClassSections[j].ClassID]) {
					if (currentScore > highestScore) {
						highestScore = currentScore;
						highestClassSection = GroundClassSections[j].ClassID;
					} else if (currentScore == highestScore
							&& currentScore != 0) {
						randInt = rand() % 2;
						if (randInt == 1) {
							highestClassSection =
									GroundClassSections[j].ClassID;
						}
					}
				}
			}

			// Checks to make sure the highest score is greater than 0
			// If highest score = 0, then project and class section
			// types did not match
			if (highestScore > 0 || GroundClassSections.size() == 1) {
				for (int j = 0; j < GroundClassSections.size(); j++) {

					if (GroundClassSections[j].ClassID == highestClassSection
							|| GroundClassSections.size() == 1) {
						if (ProjectsToClassCount[GroundClassSections[j].ClassID]
								< MinProjectsPerClassSection[GroundClassSections[j].ClassID]) {
							classSection = GroundClassSections[j];
							projectPool[i].ClassID = classSection.ClassID;
							//projectPool[i].OfficialClassID = classSection.OfficialClassID;
							GroundClassSections.erase(
									GroundClassSections.begin() + j);
							//increment the number of projects added to this class section
							ProjectsToClassCount[classSection.ClassID]++;
						}
					}
				}

			}

//Assign the Hybrid Projects
		} else {

			//refill vector if empty
			if (ClassSections.empty()) {
				for (int k = 0; k < numClassSections; k++) {
					ClassSections.push_back(*(classSectionPool + k));
				}
			}

			for (int j = 0; j < ClassSections.size(); j++) {

				classSection = ClassSections[j];
				currentScore = projectXsection[(i * numClassSections)
						+ ClassSections[j].ClassID];

				//make sure that this class section has not reached the minNumOfProjects added.
				if (ProjectsToClassCount[ClassSections[j].ClassID]
						< MinProjectsPerClassSection[ClassSections[j].ClassID]) {
					if (currentScore > highestScore) {
						highestScore = currentScore;
						highestClassSection = ClassSections[j].ClassID;
					} else if (currentScore == highestScore
							&& currentScore != 0) {
						randInt = rand() % 2;
						if (randInt == 1) {
							highestClassSection = ClassSections[j].ClassID;
						}
					}
				}
			}

			// Checks to make sure the highest score is greater than 0
			// If highest score = 0, then project and class section
			// types did not match
			if (highestScore > 0) {
				for (int j = 0; j < ClassSections.size(); j++) {

					if (ClassSections[j].ClassID == highestClassSection) {
						if (ProjectsToClassCount[ClassSections[j].ClassID]
								< MinProjectsPerClassSection[ClassSections[j].ClassID]) {
							classSection = ClassSections[j];
							projectPool[i].ClassID = classSection.ClassID;
							//projectPool[i].ClassID = classSection.OfficialClassID;
							//increment the number of projects added to this class section
							ProjectsToClassCount[classSection.ClassID]++;
							ClassSections.erase(ClassSections.begin() + j);

						}
					}
				}

			} else {

				ClassSections.clear();
				for (int k = 0; k < numClassSections; k++) {

					ClassSections.push_back(*(classSectionPool + k));
				}

				for (int j = 0; j < ClassSections.size(); j++) {
					if (ProjectsToClassCount[ClassSections[j].ClassID]
							< MinProjectsPerClassSection[ClassSections[j].ClassID]) {

						projectPool[i].ClassID = ClassSections[j].ClassID;
						ProjectsToClassCount[ClassSections[j].ClassID]++;
						break;

					} else {
						//No more room in any class Section for this project, so
						//assign it a value of 99999.
						projectPool[i].ClassID = 99999;
					}

				}
			}

		}

	}		  // end i num projects loop


	//Final check to make sure that all class sections have the minimum number of porjects needed.
	for (int j = 0; j < ClassSections.size(); j++) {
						if (ProjectsToClassCount[ClassSections[j].ClassID]
								< MinProjectsPerClassSection[ClassSections[j].ClassID]) {

							for (int k = 0; k < numProjects; k++) {
									//Project projectX = *(projectPool + k);

									if( projectPool[k].ClassID==100){
										//if (ProjectsToClassCount[ClassSections[j].ClassID]
										//		< MinProjectsPerClassSection[ClassSections[j].ClassID]) {
									//assign this project to the class section that needs it.
										projectPool[k].ClassID = ClassSections[j].ClassID;
										ProjectsToClassCount[ClassSections[j].ClassID]++;
										cout<<"Assigned a project to class section. Class section# "<<ClassSections[j].ClassID
												<<" Project# "<<projectPool[k].ProjectID<<endl;
									}
							}

						}}



	for (int k = 0; k < numClassSections; k++) {
		cout << "Class section #" << k << " Number of Projects assigned: "
				<< ProjectsToClassCount[k] << endl;

	}

}		  //end ProjectToSectionPercentages

/*************************************************
 * makeProjectJSON
 *
 * Description:
 *   This function creates a new Json file with random data for
 *   a specified number of projects.
 *
 * Arguments:
 * int numProj, - number of projects to create in the Json file
 * int numSkill
 *
 * Returns:
 *    nothing
 */
void Utility::makeProjectJSON(int numProj, int numSkill) {

	// Variables
	ofstream file;
	int numProjects = numProj;
	int numSkills = numSkill;

	// opening file in out(write) mode
	// ios::out Open for output operations.
	file.open("newProjects.json", ios::out);

	//Start of JSON file
	file << "{ \n\"projects\":[\n";

	//Loops through projectID to print
	for (int projectID = 1; projectID < (numProjects + 1); projectID++) {

		/*Prints out schema: {"ProjectID": (projectID#),the projectID
		 * number is set to have width of 3 if the number (e.g. 1)
		 * is less than 3, it will fill with 0's. (e.g. 001)     */
		file << "{\"ProjectID\": " << projectID << ",\n";

		/*Prints out schema: {"NDA": bool, */
		/*Prints out schema: {"IPR": bool, */
		//25 percent of projects will require students sign an IPR and NDA agreement.
		int percent = (int) numProjects * (0.25);
		if (projectID < (percent + 1)) {
			file << "\"NDA\": true,\n";
			file << "\"IPR\": true,\n";
		} else {
			file << "\"NDA\": false,\n";
			file << "\"IPR\": false,\n";
		}

		/*Prints out schema: {"NDA": bool, */
		/*Prints out schema: {"IPR": bool, */
		//5 percent of projects will require students use shared hardware.
		percent = (int) numProjects * (0.05);
		if (projectID < (percent + 1)) {
			file << "\"sharedHardware\": true,\n";
		} else {
			file << "\"sharedHardware\": false,\n";
		}

		/*Prints out schema: "Priority": (Priority), priority can be
		 * 0,1, or 2. This file randomizes it between the three options.  */
		file << " \"Priority\": " << rand() % (2 + 1) << ",\n";

		/*Prints out schema: "Skills": [(skills)], generates Skills from
		 * numSkills. Randomizes values between 0-4 for each skill.      */
		file << " \"Skills\": [";
		for (int i = 0; i < (numSkills); i++) {
			if (i < (numSkills - 1)) {
				file << rand() % (2 + 1) << ",";
			} else {
				file << rand() % (2 + 1) << "],\n";
			}
		}

		/*Prints out schema: "Type": O/G/H, right now 80% is hybrid
		 * 10% online and 10% ground projects    */

		//file << " \"Type\": ";
		//      file << "\"H\" },\n\n";
		file << " \"Type\": ";
		percent = (int) numProjects * (0.10);
		if (projectID < (percent + 1)) {
			file << "\"O\" }, \n\n";
		} else if (projectID > percent
				&& projectID < ((percent + percent + 1))) {
			file << "\"G\" }, \n\n";
		} else if (projectID == numProjects) {
			file << "\"H\" }\n\n";
		} else {
			file << "\"H\" },\n\n";
		}
	}
	file << "]\n}";

	file.close();

}

/*************************************************
 * makeProjectCSV
 *
 * Description:
 *   This function creates a new CSV file with random data for
 *   a specified number of projects.
 *
 * Arguments:
 * int numProj, - number of projects to create in the CSV file
 * int numSkill
 *
 * Returns:
 *    nothing
 */
void Utility::makeProjectCSV(int numProj, int numSkill) {
	string skills[14] =
		{ "ArtificialIntelligence", "WebApplicationProgramming",
				"IOSMobileApplicationProgramming",
				"AndroidMobileApplicationProgramming",
				"Sensing/Control/Embedded", "DesktopApplicationProgramming",
				"DatabaseProgramming", "NetworkSecurity", "C", "C++", "C#",
				"Java", "JavaScript", "Python" };
	// Variables
	ofstream file;
	int numProjects = numProj;
	int numSkills = numSkill;

	// opening file in out(write) mode
	// ios::out Open for output operations.
	file.open("newProjects.csv", ios::out);

	//Start of CSV file
	file << "Company,Submitter Name,Submitter Title,Submitter Email,Submitter Contact Phone #,Technical Contact Name,Technical Contact Title,Technical Contact E-mail,Technical Contact Phone Number,Project Motivation,Project Description,Project Deliverables,Technology Areas,PreferredLanguageSkills,RequiresNDA,RequiresIPR,RequiresSharedHardware,Type,Section,Priority\n";

	//Loops through projectID to print
	for (int projectID = 1; projectID <(numProjects+1) ; projectID++) {

		/*Prints out schema: {"ProjectID": (projectID#),the projectID
		 * number is set to have width of 3 if the number (e.g. 1)
		 * is less than 3, it will fill with 0's. (e.g. 001)     */
		//file << "{\"ProjectID\": " << projectID << ",\n";
		file << "Company" << projectID << ",";
		file << "Submitter Name" << projectID << ",";
		file << "Submitter Title" << projectID << ",";
		file << "Submitter Email" << projectID << ",";
		file << "Submitter Contact Phone #" << projectID << ",";
		file << "Technical Contact Name" << projectID << ",";
		file << "Technical Contact Title" << projectID << ",";
		file << "Technical Contact E-mail" << projectID << ",";
		file << "Technical Contact Phone Number" << projectID << ",";
		file << "Project Motivation" << projectID << ",";
		file << "Project Description" << projectID << ",";
		file << "Project Deliverables" << projectID << ",";
		/*file << "Technology Areas" << projectID << ",";
		file << "Preferred Language Skills" << projectID << ",";
		file << "Requires NDA" << projectID << ",";
		file << "Requires IPR" << projectID << ",";
		file << "Requires Shared Hardware" << projectID << ",";
		file << "Type" << projectID << ",";
		file << "Section" << projectID << ",";
		file << "Priority" << projectID;*/

		/*Prints out schema: "Skills": [(skills)], generates Skills from
		 * numSkills. Randomizes values between 0-4 for each skill.      */
		try {
			if(numSkills != 14) {
				cout << "WARNING: numSkills does not equal the number of skills specified in the project schema" << endl;
			}
			file << "\"[";
			for (int i = 0; i < (8); i++) {
				if (i < (8 - 1)) {
					if((rand() % (2 + 1)) == 0) {
						file << skills[i]<< ",";
					}
				} else {
					if((rand() % (2 + 1)) == 0) {
						file << skills[i]<< ",";
					}
					file << "]\",";
				}
			}
			file << "\"[";
			for (int i = 8; i < (14); i++) {
				if (i < (14 - 1)) {
					if((rand() % (2 + 1)) == 0) {
						file << skills[i] << ",";
					}
				} else {
					if((rand() % (2 + 1)) == 0) {
						file << skills[i]<< ",";
					}
					file << "]\",";
				}
			}
		} catch(range_error& e) {
					cout << "Index out of range" << endl;
		}
		/*Prints out schema: {"NDA": bool, */
		/*Prints out schema: {"IPR": bool, */
		//25 percent of projects will require students sign an IPR and NDA agreement.
		int percent = (int) numProjects * (0.25);
		if (projectID < (percent + 1)) {
			file << "1,";
			file << "1,";
		} else {
			file << "0,";
			file << "0,";
		}

		//5 percent of projects will require students use shared hardware.
		percent = (int) numProjects * (0.05);
		if (projectID < (percent + 1)) {
			file << "1,";
		} else {
			file << "0,";
		}

		/*Prints out schema: "Type": O/G/H, right now 80% is hybrid
		 * 10% online and 10% ground projects    */
		percent = (int) numProjects * (0.10);
		if (projectID < (percent + 1)) {
			file << "O,";
		} else if (projectID > percent
				&& projectID < ((percent + percent + 1))) {
			file << "G,";
		} else if (projectID == numProjects) {
			file << "H,";
		} else {
			file << "H,";
		}

		//Prints out schema: "Section": 0, 1, 2, or 3
		file << (projectID % 4) << ",";

		/*Prints out schema: "Priority": (Priority), priority can be
				 * 0,1, or 2. This file randomizes it between the three options.  */
		file << rand() % (2 + 1) << "\n";

	}

	file.close();

}//end makeProjectsCSV

/*************************************************
 * generateTestStudents
 *
 * Description:
 *   This function creates a Json file of test students
 *   for a given class section. It makes a new Json file
 *    with random data for a specified number of students.
 *
 * Arguments:
 * int numStud, - number of students to create in the Json file
 * int numSkill
 *
 * Returns:
 *    nothing
 */
void Utility::generateTestStudents(int numStud, int numSkill, vector<vector<Student>> studentsFromCanvas, ClassSection course) {

	// Variables
	ofstream file;
	int numStudent = numStud - studentsFromCanvas.size();
	int numSkills = numSkill;
	//int student_25 = (int) (numStudent * 0.25);
	//int student_50 = (int) (numStudent * 0.50);
	//int student_75 = (int) (numStudent * 0.75);

	// opening file in write mode
	file.open("newStudents.json", ios::out);

	//Start of JSON file
	file << "{ \n\"students\":[\n";

	//Loops through studentIDs to print
	for (int studentID = 1; studentID <= numStudent; studentID++) {

		string asuID = "ASU" + to_string(studentID);
		/*Prints out schema: {"StudentID": (studentID#), */
		file << "{\"ASUriteID\": \"" << asuID << "\",\n";

		/*Prints out schema: {"StudentID": (studentID#), */
		file << "\"StudentID\": " << studentID << ",\n";

		/*Prints out schema: {"StudentID": (studentID#), */
		file << "\"name\": \"" << names[studentID] << "\",\n";

		/*Prints out schema: {"ClassID": (studentID#), */
		file << " \"ClassID\": " << course.ClassID << ",\n";


		/*Prints out schema: {"NDA": bool, */
		/*Prints out schema: {"IPR": bool, */
		//5 percent of students will not want to sign the agreements.
		int percent = (int) numStudent * (0.05);
		if (studentID < (percent + 1)) {
			file << "\"NDA\": false,\n";
			file << "\"IPR\": false,\n";
		} else {
			file << "\"NDA\": true,\n";
			file << "\"IPR\": true,\n";
		}

		/*Prints out schema: "Skills": [(skills)],  ramdomly generates skills
		 * with values 0-4, total skills given as a parameter         */
		file << " \"Skills\": [";
		for (int i = 0; i < numSkills; i++) {
			if (i < (numSkills - 1)) {
				file << rand() % (4 + 1) << ",";
			} else {
				file << rand() % (4 + 1) << "],\n";
			}
		}

		/*Prints out schema: "StudentAffinity": null OR [(studentID), T/F]
		 * negative affinity: every 1/3 of students gets a randomized negative
		 *                  affinity for another Student
		 * positive affinity: every 1/4 of students gets a randomized positive
		 *                  affinity for another Student
		 *
		 * It can fall where 1 student has a positive & negative affinity (1/12)
		 * Else it will print "null"
		 */
		file << " \"StudentAffinity\": ";
		if (studentID % 3 == 0 || studentID % 4 == 0) {

			//Negative affinity matches
			int rand_1 = rand() % (numStud);
			while (rand_1 == studentID) {
				rand_1 = rand() % (numStud);
			}

			//Positive affinity matches
			int rand_2 = rand() % (numStud);
			while (rand_2 == studentID || rand_2 == rand_1) {
				rand_2 = rand() % (numStud);
			}

			//printing out affinity
			file << "[";
			if (studentID % 3 == 0) {
				if (studentID < numStud) {
					file << "\"ASU" << rand_1 << "\", false";

			}
			}
			if (studentID % 4 == 0) {
				if (studentID % 3 != 0) {
					if (studentID < numStud) {
						file << "\"ASU" << rand_2 << "\", true";
				}
				}
			}
				if (studentID % 3 == 0) {
					if (studentID < numStud) {
						file << ", " << "\"ASU" << rand_2 << "\", true";
					}

					}

			file << "],\n";
		} else {
			file << "null,\n";
		}

		/*Prints out schema: "Availability": [(Availability)] }
		 * ramdomly generates 4 times with values 0-5
		 */
		file << " \"Availability\": [";
		for (int i = 0; i < 4; i++) {
			if (i < 3) {
				file << rand() % (5 + 1) << ",";
			} else {
				file << rand() % (5 + 1);
			}
		}


		if (studentID < numStudent || studentsFromCanvas.size()> 0) {
			file << "] },\n\n";
		} else if (studentID == numStudent) {
			file << "] }\n\n";
		}
	}

	for(int i = 0; i < studentsFromCanvas.size(); i++) {
		for(int j = 0; j < studentsFromCanvas.at(i).size(); j++) {
			string asuID = studentsFromCanvas.at(i).at(j).ASUriteID;

			asuID = "ASU";
			asuID += to_string(numStud);
			/*Prints out schema: {"StudentID": (studentID#), */
			file << "{\"ASUriteID\": \"" << asuID << "\",\n";

			string studentID = to_string(studentsFromCanvas.at(i).at(j).StID);
			studentID = to_string(numStud);
			/*Prints out schema: {"StudentID": (studentID#), */
			file << "\"StudentID\": " << studentID << ",\n";

			/*Prints out schema: {"name": studentName, */
			file << "\"name\": \"" << studentsFromCanvas.at(i).at(j).name << "\",\n";

			/*Prints out schema: "ClassID": (classID),*/
			//file << " \"ClassID\": " << studentsFromCanvas.at(i).at(j).ClassID << ",\n";
			file << " \"ClassID\": " << course.ClassID << ",\n";

			/*Prints out schema: {"NDA": bool, */
			/*Prints out schema: {"IPR": bool, */
			if(studentsFromCanvas.at(i).at(j).NDA) {
				file << "\"NDA\": " << "true" << ",\n";
			} else {
				file << "\"NDA\": " << "false" << ",\n";
			}
			if(studentsFromCanvas.at(i).at(j).IPR) {
				file << "\"IPR\": " << "true" << ",\n";
			} else {
				file << "\"IPR\": " << "false" << ",\n";
			}
			/*file << "\"NDA\": " << to_string(studentsFromCanvas.at(i).at(j).NDA) << ",\n";
			file << "\"IPR\": " << to_string(studentsFromCanvas.at(i).at(j).IPR) << ",\n";*/

			/*Prints out schema: "Skills": [(skills)],*/
			file << " \"Skills\": [";
			for (int k = 0; k < numSkills; k++) {
				if (k < (numSkills - 1)) {
					file << studentsFromCanvas.at(i).at(j).Skills[k] << ",";
				} else {
					file << studentsFromCanvas.at(i).at(j).Skills[k] << "],\n";
				}
			}

			/*Prints out schema: "StudentAffinity": null OR [(studentID), T/F]*/
			file << " \"StudentAffinity\": ";
			if(studentsFromCanvas.at(i).at(j).StudentAffinity.size() == 0) {
				file << "null,\n";
			} else {
				file << "[";
				for (int k = 0; k < studentsFromCanvas.at(i).at(j).StudentAffinity.size(); k++) {
					file << "\"" << studentsFromCanvas.at(i).at(j).StudentAffinity.at(k).first << "\", ";
					if(studentsFromCanvas.at(i).at(j).StudentAffinity.at(k).second) {
						if(k == studentsFromCanvas.at(i).at(j).StudentAffinity.size() - 1) {
							file /*<< studentsFromCanvas.at(i).at(j).StudentAffinity[k].first*/ << "true";
						} else {
							file /*<< studentsFromCanvas.at(i).at(j).StudentAffinity[k].first*/ << "true, ";
						}
					} else {
						if(k == studentsFromCanvas.at(i).at(j).StudentAffinity.size() - 1) {
							file /*<< studentsFromCanvas.at(i).at(j).StudentAffinity[k].first*/ << "false";
						} else {
							file /*<< studentsFromCanvas.at(i).at(j).StudentAffinity[k].first*/ << "false, ";
						}
					}

				}
				file << "],\n";
			}




			/*Prints out schema: "Availability": [(Availability)] }*/
			file << " \"Availability\": [";
			for (int k = 0; k < 4; k++) {
				if (k < 3) {
					file << studentsFromCanvas.at(i).at(j).Availability[k] << ",";
				} else {
					file << studentsFromCanvas.at(i).at(j).Availability[k];
				}
			}
			if (j < studentsFromCanvas.at(i).size()) {
				file << "] }\n\n";
			} else if (j == studentsFromCanvas.at(i).size()) {
				file << "] }\n\n";
			}
		}
	}

	file << "]\n}";

	file.close();

}

/*************************************************
 * makeStudentJSON
 *
 * Description:
 *   This function creates a new Json file with random data for
 *   a specified number of students.
 *
 * Arguments:
 * int numStud, - number of students to create in the Json file
 * int numSkill
 *
 * Returns:
 *    nothing
 */
void Utility::makeStudentJSON(int numStud, int numSkill, vector<vector<Student>> studentsFromCanvas) {

	// Variables
	ofstream file;
	int numStudent = numStud - studentsFromCanvas.size();
	int numSkills = numSkill;
	int student_25 = (int) (numStudent * 0.25);
	int student_50 = (int) (numStudent * 0.50);
	int student_75 = (int) (numStudent * 0.75);

	// opening file in write mode
	file.open("newStudents.json", ios::out);

	//Start of JSON file
	file << "{ \n\"students\":[\n";

	//Loops through studentIDs to print
	for (int studentID = 1; studentID <= numStudent; studentID++) {

		string asuID = "ASU" + to_string(studentID);
		/*Prints out schema: {"StudentID": (studentID#), */
		file << "{\"ASUriteID\": \"" << asuID << "\",\n";

		/*Prints out schema: {"StudentID": (studentID#), */
		file << "\"StudentID\": " << studentID << ",\n";

		/*Prints out schema: {"StudentID": (studentID#), */
		file << "\"name\": \"" << names[studentID] << "\",\n";

		/*Prints out schema: "ClassID": (classID), classID is divided
		 * equally into 4 sections   */
		if (studentID <= student_25) {
			file << " \"ClassID\": 0,\n";
		}
		if (studentID > student_25 && studentID <= student_50) {
			file << " \"ClassID\": 1,\n";
		}
		if (studentID > student_50 && studentID <= student_75) {
			file << " \"ClassID\": 2,\n";
		}
		if (studentID > student_75 && studentID <= numStudent) {
			file << " \"ClassID\": 3,\n";
		}

		/*Prints out schema: {"NDA": bool, */
		/*Prints out schema: {"IPR": bool, */
		//5 percent of students will not want to sign the agreements.
		int percent = (int) numStudent * (0.05);
		if (studentID < (percent + 1)) {
			file << "\"NDA\": false,\n";
			file << "\"IPR\": false,\n";
		} else {
			file << "\"NDA\": true,\n";
			file << "\"IPR\": true,\n";
		}

		/*Prints out schema: "Skills": [(skills)],  ramdomly generates skills
		 * with values 0-4, total skills given as a parameter         */
		file << " \"Skills\": [";
		for (int i = 0; i < numSkills; i++) {
			if (i < (numSkills - 1)) {
				file << rand() % (4 + 1) << ",";
			} else {
				file << rand() % (4 + 1) << "],\n";
			}
		}

		/*Prints out schema: "StudentAffinity": null OR [(studentID), T/F]
		 * negative affinity: every 1/3 of students gets a randomized negative
		 *                  affinity for another Student
		 * positive affinity: every 1/4 of students gets a randomized positive
		 *                  affinity for another Student
		 *
		 * It can fall where 1 student has a positive & negative affinity (1/12)
		 * Else it will print "null"
		 */
		file << " \"StudentAffinity\": ";
		if (studentID % 3 == 0 || studentID % 4 == 0) {

			//Negative affinity matches
			int rand_1_25 = rand() % (student_25 + 1);
			while (rand_1_25 == studentID) {
				rand_1_25 = rand() % (student_25 + 1);
			}

			int rand_1_50 = rand() % (student_50 - student_25 + 1) + student_25;
			while (rand_1_50 == studentID) {
				rand_1_50 = rand() % (student_50 - student_25 + 1) + student_25;
			}

			int rand_1_75 = rand() % (student_75 - student_50 + 1) + student_50;
			while (rand_1_75 == studentID) {
				rand_1_75 = rand() % (student_75 - student_50 + 1) + student_50;
			}

			int rand_1_100 = rand() % (numStudent - student_75 + 1)
					+ student_75;
			while (rand_1_100 == studentID) {
				rand_1_100 = rand() % (numStudent - student_75 + 1)
						+ student_75;
			}

			//Positive affinity matches
			int rand_2_25 = rand() % (student_25 + 1);
			while (rand_2_25 == studentID || rand_2_25 == rand_1_25) {
				rand_2_25 = rand() % (student_25 + 1);
			}

			int rand_2_50 = rand() % (student_50 - student_25 + 1) + student_25;
			while (rand_2_50 == studentID || rand_2_50 == rand_1_50) {
				rand_2_50 = rand() % (student_50 - student_25 + 1) + student_25;
			}

			int rand_2_75 = rand() % (student_75 - student_50 + 1) + student_50;
			while (rand_2_75 == studentID || rand_2_75 == rand_1_75) {
				rand_2_75 = rand() % (student_75 - student_50 + 1) + student_50;
			}

			int rand_2_100 = rand() % (numStudent - student_75 + 1)
					+ student_75;
			while (rand_2_100 == studentID || rand_2_100 == rand_1_100) {
				rand_2_100 = rand() % (numStudent - student_75 + 1)
						+ student_75;
			}

			//printing out affinity
			file << "[";
			if (studentID % 3 == 0) {
				if (studentID < student_25) {
					file << "\"ASU" << rand_1_25 << "\", false";
				}
				if (studentID >= student_25 && studentID < student_50) {
					file << "\"ASU" << rand_1_50 << "\", false";
				}
				if (studentID >= student_50 && studentID < student_75) {
					file << "\"ASU" << rand_1_75 << "\", false";
				}
				if (studentID >= student_75 && studentID <= numStudent) {
					file << "\"ASU" << rand_1_100 << "\", false";
				}
			}
			if (studentID % 4 == 0) {
				if (studentID % 3 != 0) {
					if (studentID < student_25) {
						file << "\"ASU" << rand_2_25 << "\", true";
					}
					if (studentID >= student_25 && studentID < student_50) {
						file << "\"ASU" << rand_2_50 << "\", true";
					}
					if (studentID >= student_50 && studentID < student_75) {
						file << "\"ASU" << rand_2_75 << "\", true";
					}
					if (studentID >= student_75 && studentID <= numStudent) {
						file << "\"ASU" << rand_2_100 << "\", true";
					}
				}
				if (studentID % 3 == 0) {
					if (studentID < student_25) {
						file << ", " << "\"ASU" << rand_2_25 << "\", true";
					}
					if (studentID >= student_25 && studentID < student_50) {
						file << ", " << "\"ASU" << rand_2_50 << "\", true";
					}
					if (studentID >= student_50 && studentID < student_75) {
						file << ", " << "\"ASU" << rand_2_75 << "\", true";
					}
					if (studentID >= student_75 && studentID <= numStudent) {
						file << ", " << "\"ASU" << rand_2_100 << "\", true";
					}
				}
			}
			file << "],\n";
		} else {
			file << "null,\n";
		}

		/*Prints out schema: "Availability": [(Availability)] }
		 * ramdomly generates 4 times with values 0-5
		 */
		file << " \"Availability\": [";
		for (int i = 0; i < 4; i++) {
			if (i < 3) {
				file << rand() % (5 + 1) << ",";
			} else {
				file << rand() % (5 + 1);
			}
		}


		if (studentID < numStudent || studentsFromCanvas.size()> 0) {
			file << "] },\n\n";
		} else if (studentID == numStudent) {
			file << "] }\n\n";
		}
	}
	for(int i = 0; i < studentsFromCanvas.size(); i++) {
		for(int j = 0; j < studentsFromCanvas.at(i).size(); j++) {
			string asuID = studentsFromCanvas.at(i).at(j).ASUriteID;

			asuID = "ASU";
			asuID += to_string(numStud);
			/*Prints out schema: {"StudentID": (studentID#), */
			file << "{\"ASUriteID\": \"" << asuID << "\",\n";

			string studentID = to_string(studentsFromCanvas.at(i).at(j).StID);
			studentID = to_string(numStud);
			/*Prints out schema: {"StudentID": (studentID#), */
			file << "\"StudentID\": " << studentID << ",\n";

			/*Prints out schema: {"name": studentName, */
			file << "\"name\": \"" << studentsFromCanvas.at(i).at(j).name << "\",\n";

			/*Prints out schema: "ClassID": (classID),*/
			//file << " \"ClassID\": " << studentsFromCanvas.at(i).at(j).ClassID << ",\n";
			file << " \"ClassID\": " << to_string(0) << ",\n";

			/*Prints out schema: {"NDA": bool, */
			/*Prints out schema: {"IPR": bool, */
			if(studentsFromCanvas.at(i).at(j).NDA) {
				file << "\"NDA\": " << "true" << ",\n";
			} else {
				file << "\"NDA\": " << "false" << ",\n";
			}
			if(studentsFromCanvas.at(i).at(j).IPR) {
				file << "\"IPR\": " << "true" << ",\n";
			} else {
				file << "\"IPR\": " << "false" << ",\n";
			}
			/*file << "\"NDA\": " << to_string(studentsFromCanvas.at(i).at(j).NDA) << ",\n";
			file << "\"IPR\": " << to_string(studentsFromCanvas.at(i).at(j).IPR) << ",\n";*/

			/*Prints out schema: "Skills": [(skills)],*/
			file << " \"Skills\": [";
			for (int k = 0; k < numSkills; k++) {
				if (k < (numSkills - 1)) {
					file << studentsFromCanvas.at(i).at(j).Skills[k] << ",";
				} else {
					file << studentsFromCanvas.at(i).at(j).Skills[k] << "],\n";
				}
			}

			/*Prints out schema: "StudentAffinity": null OR [(studentID), T/F]*/
			file << " \"StudentAffinity\": ";
			if(studentsFromCanvas.at(i).at(j).StudentAffinity.size() == 0) {
				file << "null,\n";
			} else {
				file << "[";
				for (int k = 0; k < studentsFromCanvas.at(i).at(j).StudentAffinity.size(); k++) {
					file << "\"" << studentsFromCanvas.at(i).at(j).StudentAffinity.at(k).first << "\", ";
					if(studentsFromCanvas.at(i).at(j).StudentAffinity.at(k).second) {
						if(k == studentsFromCanvas.at(i).at(j).StudentAffinity.size() - 1) {
							file /*<< studentsFromCanvas.at(i).at(j).StudentAffinity[k].first*/ << "true";
						} else {
							file /*<< studentsFromCanvas.at(i).at(j).StudentAffinity[k].first*/ << "true, ";
						}
					} else {
						if(k == studentsFromCanvas.at(i).at(j).StudentAffinity.size() - 1) {
							file /*<< studentsFromCanvas.at(i).at(j).StudentAffinity[k].first*/ << "false";
						} else {
							file /*<< studentsFromCanvas.at(i).at(j).StudentAffinity[k].first*/ << "false, ";
						}
					}

				}
				file << "],\n";
			}




			/*Prints out schema: "Availability": [(Availability)] }*/
			file << " \"Availability\": [";
			for (int k = 0; k < 4; k++) {
				if (k < 3) {
					file << studentsFromCanvas.at(i).at(j).Availability[k] << ",";
				} else {
					file << studentsFromCanvas.at(i).at(j).Availability[k];
				}
			}
			if (j < studentsFromCanvas.at(i).size()) {
				file << "] },\n\n";
			} else if (j == studentsFromCanvas.at(i).size()) {
				file << "] }\n\n";
			}
		}
	}

	file << "]\n}";

	file.close();

}


/*************************************************
 * makeStudentCSV
 *
 * Description:
 *   This function creates a new CSV file with random data for
 *   a specified number of students.
 *
 * Arguments:
 * int numStud, - number of students to create in the CSV file
 * int numSkill
 *
 * Returns:
 *    nothing
 */
void Utility::makeStudentCSV(int numStud, int numSkill) {

	// Variables
	ofstream file;
	int numStudent = numStud;
	int numSkills = numSkill;
	int student_25 = (int) (numStudent * 0.25);
	int student_50 = (int) (numStudent * 0.50);
	int student_75 = (int) (numStudent * 0.75);

	// opening file in write mode
	//file.open("newStudents.json", ios::out);
	file.open("newStudents.CSV", ios::out);

	//Start of CSV file
	//file << "{ \n\"students\":[\n";
	file << "ASUriteID,StudentID,name,ClassID,NDA,IPR,Skills,StudentAffinity,Availability\n";
	//Loops through studentIDs to print
	for (int studentID = 1; studentID <= numStudent; studentID++) {

		string asuID = "ASU" + to_string(studentID);
		/*Prints out schema: {"StudentID": (studentID#), */
		//file << "{\"ASUriteID\": \"" << asuID << "\",\n";
		file << asuID << ",";

		/*Prints out schema: {"StudentID": (studentID#), */
		//file << "\"StudentID\": " << studentID << ",\n";
		file << studentID << ",";

		/*Prints out schema: {"StudentID": (studentID#), */
		//file << "\"name\": \"" << names[studentID] << "\",\n";
		file << names[studentID] << ",";

		/*Prints out schema: "ClassID": (classID), classID is divided
		 * equally into 4 sections   */
		/*if (studentID <= student_25) {
			file << " \"ClassID\": 0,\n";
		}
		if (studentID > student_25 && studentID <= student_50) {
			file << " \"ClassID\": 1,\n";
		}
		if (studentID > student_50 && studentID <= student_75) {
			file << " \"ClassID\": 2,\n";
		}
		if (studentID > student_75 && studentID <= numStudent) {
			file << " \"ClassID\": 3,\n";
		}*/
		if (studentID <= student_25) {
			file << "0,";
			}
		if (studentID > student_25 && studentID <= student_50) {
			file << "1,";
		}
		if (studentID > student_50 && studentID <= student_75) {
			file << "2,";
		}
		if (studentID > student_75 && studentID <= numStudent) {
			file << "3,";
		}

		/*Prints out schema: {"NDA": bool, */
		/*Prints out schema: {"IPR": bool, */
		//5 percent of students will not want to sign the agreements.
		int percent = (int) numStudent * (0.05);
		/*if (studentID < (percent + 1)) {
			file << "\"NDA\": false,\n";
			file << "\"IPR\": false,\n";
		} else {
			file << "\"NDA\": true,\n";
			file << "\"IPR\": true,\n";
		}*/

		if (studentID < (percent + 1)) {
			file << "0,";
			file << "0,";
		} else {
			file << "1,";
			file << "1,";
		}

		/*Prints out schema: "Skills": [(skills)],  ramdomly generates skills
		 * with values 0-4, total skills given as a parameter         */
		//file << " \"Skills\": [";
		file << "\"[";
		for (int i = 0; i < numSkills; i++) {
			if (i < (numSkills - 1)) {
				file << rand() % (4 + 1) << ",";
			} else {
				//file << rand() % (4 + 1) << "],\n";
				file << rand() % (4 + 1) << "]\",";
			}
		}

		/*Prints out schema: "StudentAffinity": null OR [(studentID), T/F]
		 * negative affinity: every 1/3 of students gets a randomized negative
		 *                  affinity for another Student
		 * positive affinity: every 1/4 of students gets a randomized positive
		 *                  affinity for another Student
		 *
		 * It can fall where 1 student has a positive & negative affinity (1/12)
		 * Else it will print "null"
		 */
		//file << " \"StudentAffinity\": ";
		if (studentID % 3 == 0 || studentID % 4 == 0) {

			//Negative affinity matches
			int rand_1_25 = rand() % (student_25 + 1);
			while (rand_1_25 == studentID) {
				rand_1_25 = rand() % (student_25 + 1);
			}

			int rand_1_50 = rand() % (student_50 - student_25 + 1) + student_25;
			while (rand_1_50 == studentID) {
				rand_1_50 = rand() % (student_50 - student_25 + 1) + student_25;
			}

			int rand_1_75 = rand() % (student_75 - student_50 + 1) + student_50;
			while (rand_1_75 == studentID) {
				rand_1_75 = rand() % (student_75 - student_50 + 1) + student_50;
			}

			int rand_1_100 = rand() % (numStudent - student_75 + 1)
					+ student_75;
			while (rand_1_100 == studentID) {
				rand_1_100 = rand() % (numStudent - student_75 + 1)
						+ student_75;
			}

			//Positive affinity matches
			int rand_2_25 = rand() % (student_25 + 1);
			while (rand_2_25 == studentID || rand_2_25 == rand_1_25) {
				rand_2_25 = rand() % (student_25 + 1);
			}

			int rand_2_50 = rand() % (student_50 - student_25 + 1) + student_25;
			while (rand_2_50 == studentID || rand_2_50 == rand_1_50) {
				rand_2_50 = rand() % (student_50 - student_25 + 1) + student_25;
			}

			int rand_2_75 = rand() % (student_75 - student_50 + 1) + student_50;
			while (rand_2_75 == studentID || rand_2_75 == rand_1_75) {
				rand_2_75 = rand() % (student_75 - student_50 + 1) + student_50;
			}

			int rand_2_100 = rand() % (numStudent - student_75 + 1)
					+ student_75;
			while (rand_2_100 == studentID || rand_2_100 == rand_1_100) {
				rand_2_100 = rand() % (numStudent - student_75 + 1)
						+ student_75;
			}

			//printing out affinity
			file << "\"[";
			if (studentID % 3 == 0) {
				if (studentID < student_25) {
					//file << "\"ASU" << rand_1_25 << "\", false";
					file << "ASU" << rand_1_25 << " 0,";
				}
				if (studentID >= student_25 && studentID < student_50) {
					//file << "\"ASU" << rand_1_50 << "\", false";
					file << "ASU" << rand_1_50 << " 0,";
				}
				if (studentID >= student_50 && studentID < student_75) {
					//file << "\"ASU" << rand_1_75 << "\", false";
					file << "ASU" << rand_1_75 << " 0,";
				}
				if (studentID >= student_75 && studentID <= numStudent) {
					//file << "\"ASU" << rand_1_100 << "\", false";
					file << "ASU" << rand_1_100 << " 0,";
				}
			}
			if (studentID % 4 == 0) {
				if (studentID % 3 != 0) {
					if (studentID < student_25) {
						//file << "\"ASU" << rand_2_25 << "\", true";
						file << "ASU" << rand_2_25 << " 1,";
					}
					if (studentID >= student_25 && studentID < student_50) {
						//file << "\"ASU" << rand_2_50 << "\", true";
						file << "ASU" << rand_2_50 << " 1,";
					}
					if (studentID >= student_50 && studentID < student_75) {
						//file << "\"ASU" << rand_2_75 << "\", true";
						file << "ASU" << rand_2_75 << " 1,";
					}
					if (studentID >= student_75 && studentID <= numStudent) {
						//file << "\"ASU" << rand_2_100 << "\", true";
						file << "ASU" << rand_2_100 << " 1,";
					}
				}
				if (studentID % 3 == 0) {
					if (studentID < student_25) {
						//file << ", " << "\"ASU" << rand_2_25 << "\", true";
						file << "ASU" << rand_2_25 << " 1,";
					}
					if (studentID >= student_25 && studentID < student_50) {
						//file << ", " << "\"ASU" << rand_2_50 << "\", true";
						file << "ASU" << rand_2_50 << " 1,";
					}
					if (studentID >= student_50 && studentID < student_75) {
						//file << ", " << "\"ASU" << rand_2_75 << "\", true";
						file << "ASU" << rand_2_75 << " 1,";
					}
					if (studentID >= student_75 && studentID <= numStudent) {
						//file << ", " << "\"ASU" << rand_2_100 << "\", true";
						file << "ASU" << rand_2_100 << " 1,";
					}
				}
			}
			file << "]\",";
		} else {
			file << "null,";
		}

		/*Prints out schema: "Availability": [(Availability)] }
		 * ramdomly generates 4 times with values 0-5
		 */
		/*file << " \"Availability\": [";
		for (int i = 0; i < 4; i++) {
			if (i < 3) {
				file << rand() % (5 + 1) << ",";
			} else {
				file << rand() % (5 + 1);
			}
		}
		if (studentID < numStudent) {
			file << "] },\n\n";
		} else if (studentID == numStudent) {
			file << "] }\n\n";
		}
	}
	file << "]\n}";*/
	file << "\"[";
		for (int i = 0; i < 4; i++) {
			if (i < 3) {
				file << rand() % (5 + 1) << ",";
			} else {
				file << rand() % (5 + 1);
			}
		}
		if (studentID < numStudent) {
			file << "]\"\n";
		} else if (studentID == numStudent) {
			file << "]\"";
		}
	}
	//file << "]\n";

	file.close();

}


/*************************************************
 * makeStudentJSON
 *
 * Description:
 *   This function creates a new Json file with random data for
 *   a specified number of students.
 *
 * Arguments:
 * int numStud, - number of students to create in the Json file
 * int numSkill
 *
 * Returns:
 *    nothing
 */
void Utility::makeCanvasStudentRosterJSON(int numStud, int numSkill, vector<vector<Student>> studentsFromCanvas,
		vector <ClassSection> allClassSections) {

	// Variables
	ofstream file;
	int numStudent = numStud - studentsFromCanvas.size();
	int numSkills = numSkill;
	int student_25 = (int) (numStudent * 0.25);
	int student_50 = (int) (numStudent * 0.50);
	int student_75 = (int) (numStudent * 0.75);

	// opening file in write mode
	file.open("newStudents.json", ios::out);

	//Start of JSON file
	file << "{ \n\"students\":[\n";


	for(int i = 0; i < studentsFromCanvas.size(); i++) {
		for(int j = 0; j < studentsFromCanvas.at(i).size(); j++) {

			string asuID = studentsFromCanvas.at(i).at(j).ASUriteID;
			/*Prints out schema: {"StudentID": (studentID#), */
			file << "{\"ASUriteID\": \"" << asuID << "\",\n";

			string studentID = to_string(studentsFromCanvas.at(i).at(j).StID);
			/*Prints out schema: {"StudentID": (studentID#), */
			file << "\"StudentID\": " << studentID << ",\n";

			/*Prints out schema: {"name": studentName, */
			file << "\"name\": \"" << studentsFromCanvas.at(i).at(j).name << "\",\n";

			/*Prints out schema: "ClassID": (classID),*/
			for(int k = 0 ;k < allClassSections.size() ; k++){

				if(studentsFromCanvas.at(i).at(j).ClassID == allClassSections[k].OfficialClassID){

					file << " \"ClassID\": " << allClassSections[k].ClassID << ",\n";
				}
			}

			//file << " \"ClassID\": " << to_string(0) << ",\n";

			/*Prints out schema: {"NDA": bool, */
			/*Prints out schema: {"IPR": bool, */
			if(studentsFromCanvas.at(i).at(j).NDA) {
				file << "\"NDA\": " << "true" << ",\n";
			} else {
				file << "\"NDA\": " << "false" << ",\n";
			}
			if(studentsFromCanvas.at(i).at(j).IPR) {
				file << "\"IPR\": " << "true" << ",\n";
			} else {
				file << "\"IPR\": " << "false" << ",\n";
			}
			/*file << "\"NDA\": " << to_string(studentsFromCanvas.at(i).at(j).NDA) << ",\n";
			file << "\"IPR\": " << to_string(studentsFromCanvas.at(i).at(j).IPR) << ",\n";*/

			/*Prints out schema: "Skills": [(skills)],*/
			file << " \"Skills\": [";
			for (int k = 0; k < numSkills; k++) {
				if (k < (numSkills - 1)) {
					file << studentsFromCanvas.at(i).at(j).Skills[k] << ",";
				} else {
					file << studentsFromCanvas.at(i).at(j).Skills[k] << "],\n";
				}
			}

			/*Prints out schema: "StudentAffinity": null OR [(studentID), T/F]*/
			file << " \"StudentAffinity\": ";
			if(studentsFromCanvas.at(i).at(j).StudentAffinity.size() == 0) {
				file << "null,\n";
			} else {
				file << "[";
				for (int k = 0; k < studentsFromCanvas.at(i).at(j).StudentAffinity.size(); k++) {
					file << "\"" << studentsFromCanvas.at(i).at(j).StudentAffinity.at(k).first << "\", ";
					if(studentsFromCanvas.at(i).at(j).StudentAffinity.at(k).second) {
						if(k == studentsFromCanvas.at(i).at(j).StudentAffinity.size() - 1) {
							file /*<< studentsFromCanvas.at(i).at(j).StudentAffinity[k].first*/ << "true";
						} else {
							file /*<< studentsFromCanvas.at(i).at(j).StudentAffinity[k].first*/ << "true, ";
						}
					} else {
						if(k == studentsFromCanvas.at(i).at(j).StudentAffinity.size() - 1) {
							file /*<< studentsFromCanvas.at(i).at(j).StudentAffinity[k].first*/ << "false";
						} else {
							file /*<< studentsFromCanvas.at(i).at(j).StudentAffinity[k].first*/ << "false, ";
						}
					}

				}
				file << "],\n";
			}




			/*Prints out schema: "Availability": [(Availability)] }*/
			file << " \"Availability\": [";
			for (int k = 0; k < 4; k++) {
				if (k < 3) {
					file << studentsFromCanvas.at(i).at(j).Availability[k] << ",";
				} else {
					file << studentsFromCanvas.at(i).at(j).Availability[k];
				}
			}
			if (j < studentsFromCanvas.at(i).size()-1) {
				file << "] },\n\n";
			} else if (j == studentsFromCanvas.at(i).size()-1) {
				file << "] }\n\n";
			}
		}
	}

	file << "]\n}";

	file.close();

}

/*************************************************
 * makeClassSectionJSON
 *
 * Description:
 *   This function creates a new Json file that contains all
 *   the selected class sections that the user wants to make
 *   team assignments for.
 *
 * Arguments:
 * vector<ClassSection> allClassSections
 *
 * Returns:
 *    nothing
 */
void Utility::makeClassSectionJSON(vector<ClassSection> allClassSections) {

	// Variables
	ofstream file;
	int numClassSections = allClassSections.size();

	// opening file in write mode
	file.open("ClassSections.json", ios::out);

	//Start of JSON file
	file << "{ \n\"courses\":[\n";

	//Loops through all Class sections to print the Json file
	for (int ClassID = 0; ClassID < numClassSections; ClassID++) {

		/*Prints out schema: {"id": (Officail class ID#), */
		file << "{\"id\": " << allClassSections[ClassID].OfficialClassID << ",\n";

		/*Prints out schema: {"name": (ex SER 401 Capstone), */
		file << "\"name\": \"" << allClassSections[ClassID].Course_Name << "\",\n";

		/*Prints out schema: {"course_code": (Couse_Code), */
		file << "\"course_code\": \"" << allClassSections[ClassID].Course_Code << "\",\n";

		/*Prints out schema: {"course_code": (Couse_Code), */
		if( allClassSections[ClassID].Type == 'O'){
		file << "\"course_format\": \"online\",\n";}
		else if( allClassSections[ClassID].Type == 'G'){
		file << "\"course_format\": \"on_campus\",\n";}



		/*Prints out schema: {"ClassID": (The class ID (integer from 0-on), */
		file << "\"ClassID\": " << ClassID << "\n";


		if (ClassID < numClassSections-1) {
			file << " },\n\n";
		} else if (ClassID == numClassSections-1) {
			file << " }\n\n";
		}
	}

	file << "]\n}";

	file.close();

}

// calc_projects Function
// Task #7 - Cristi DeLeo
// Calculates the number of projects required for any given
// number of students with a specified minimum team size.

/*************************************************
 * calc_projects
 *
 * Description:
 *   This function finds the minimum number of projects needed for a given
 *   number of students. Takes into consideration the team size, and the minimum team size.
 *
 * Arguments:
 * int numStudents,
 * int teamSize,
 * int minTeamSize
 *
 * Returns:
 *    nothing
 */
int Utility::calc_projects(int numStudents, int teamSize, int minTeamSize) {
	int numProjects;
	int numStudentsModTeamSize;
	int currentProjectCount;
	int numStudentsNeeded;

	numStudentsModTeamSize = numStudents % teamSize;

	if (numStudentsModTeamSize == 0) {
		numProjects = numStudents / teamSize;
	} else if (numStudentsModTeamSize >= minTeamSize) {
		numProjects = ((numStudents - numStudentsModTeamSize) / teamSize) + 1;
	} else if (numStudentsModTeamSize < minTeamSize) {
		// Calculation to determine number of projects needed when
		// more than one team will be set at the minimum team size.
		currentProjectCount = numStudents / teamSize;
		numStudentsNeeded = minTeamSize - numStudentsModTeamSize;

		// Determines whether there are enough students to evenly
		// distribute projects based on the minimum team size
		if (numStudentsNeeded > currentProjectCount) {
			if (teamSize > minTeamSize) {
				teamSize--;
			} else if (teamSize == minTeamSize) {
				teamSize--;
				minTeamSize--;
			} else {
				// Error catch
			}
			calc_projects(numStudents, teamSize, minTeamSize);
		} else if (numStudentsNeeded <= currentProjectCount) {
			numProjects = ((numStudents - numStudentsModTeamSize) / teamSize)
					+ 1;
		}
	}

	return numProjects;
}

/*********************************************************
 * NumOfTeamsOf4
 *
 * Author: Myles Colina
 *
 * Description:
 * 	This function returns the number of teams that will have 4 members.
 * 	It calculates this based on the number of students, and desired team size,
 *
 *Arguments:
 *	int numStudents, int teamSize
 *
 *Returns:
 *  integer value depicting the number of teams that will have 4 students.
 *  This value will be 0, 1, 2, 3, or 4.
 */
int Utility::NumOfTeamsOf4(int numStudents, int teamSize) {

	int numStudentsMod = numStudents % teamSize;

	if (numStudentsMod == 4) {
		return 1;

	} else if (numStudentsMod == 3) {
		return 2;

	} else if (numStudentsMod == 2) {
		return 3;

	} else if (numStudentsMod == 1) {
		return 4;

	} else if (numStudentsMod == 0) {
		return 0;
	}

}

/*********************************************************
 * toCSVsse
 *
 * Author: Sean Rogers
 *
 * Description:
 * 	Takes in a file, then outputs the comma separated values from that file.
 * 	This assumes the elements in arrays are separated by spaces
 *
 *Arguments:
 *	string filename
 *
 *Returns:
 *  vector<vector<string>> containing the comma separated values.
 */
vector<vector<string>> Utility::toCSVsse(string filename) {
	ifstream file(filename);

	vector<vector<string>> dataList;

	string line = "";

	while (getline(file, line)) {
		vector<string> vec;
		string element = "";
		for (int i = 0; i < line.length(); i++) {

			if (line.at(i) == ',') {
				vec.push_back(element);
				element = "";
			} else {
				element.push_back(line.at(i));
			}
		}
		dataList.push_back(vec);
	}
	file.close();
	return dataList;
}

/*********************************************************
 * toCSVsse
 *
 * Author: Sean Rogers
 *
 * Description:
 * 	Just like the previous method, takes in a file, then outputs the comma separated values from that file.
 * 	This assumes the elements in arrays are separated by commas
 *
 *Arguments:
 *	string filename
 *
 *Returns:
 *  vector<vector<string>> containing the comma separated values.
 */
vector<vector<string>> Utility::toCSVcse(string filename) {
	ifstream file(filename);

	vector<vector<string>> dataList;

	string line = "";

	int bracketCount = 0;
	while (getline(file, line)) {
		vector<string> vec;
		string element = "";
		for (int i = 0; i < line.length(); i++) {
			if (line.at(i) == '[') {
				bracketCount++;
			}
			if (line.at(i) == ']') {
				bracketCount--;
			}
			if (line.at(i) == ',' && bracketCount == 0) {
				vec.push_back(element);
				element = "";
			} else {
				element.push_back(line.at(i));
			}
		}
		dataList.push_back(vec);
	}
	file.close();
	return dataList;
}

/*********************************************************
 * csvToProjectsVector
 *
 * Author: Sean Rogers
 *
 * Description:
 * 	Just like the previous method, takes in a CSV file, puts the projects in the CSV file into
 * 	project objects, then places each project object into a vector, then returns that vector.
 *
 *Arguments:
 *	string filename
 *
 *Returns:
 *  vector<Project> containing the project objects obtained from the projects in the CSV file.
 */
vector<Project> Utility::csvToProjectsVector(string filename,
		Project projectPool[], int numProjects, int numSkills) {
	string skills1[numSkills] =
			{ "ArtificialIntelligence", "WebApplicationProgramming",
					"IOSMobileApplicationProgramming",
					"AndroidMobileApplicationProgramming",
					"Sensing/Control/Embedded", "DesktopApplicationProgramming",
					"DatabaseProgramming", "NetworkSecurity", "C", "C++", "C#",
					"Java", "JavaScript", "Python" };

	string currentSkill = "";

	vector<Project> projects;

	vector<vector<string>> dataList;

	ifstream file(filename);

	string line = "";
	int bracketCount = 0;
	while (getline(file, line)) {
		vector<string> vec;
		string element = "";
		for (int i = 0; i < line.length(); i++) {
			if (line.at(i) == '[') {
				bracketCount++;
			}
			if (line.at(i) == ']') {
				bracketCount--;
			}
			if (line.at(i) == ',' && bracketCount == 0) {
				vec.push_back(element);
				element = "";
			} else {
				if (line.at(i) != '[' && line.at(i) != ']') {
					element.push_back(line.at(i));
				}
			}

			if (i + 1 == line.length()) {
				vec.push_back(element);
			}
		}
		dataList.push_back(vec);
	}
	file.close();
	if (numProjects > dataList.size()) {
		cout << "numProjects can't be bigger than " << dataList.size() << endl;
		throw numProjects;
	}
	//put csv data into a project object, add that project object to vector<Project> projects,
	//repeat for all project data in CSV, return projects
	for (int i = 1; i < numProjects; i++) {
		Project p = Project();
		for (int j = 0; j < numSkills; j++) {
			p.Skills[j] = 0;
		}

		p.ProjectID = i;
		p.NDA = atoi((dataList.at(i).at(dataList.at(i).size() - 6)).c_str());
		p.IPR = atoi((dataList.at(i).at(dataList.at(i).size() - 5)).c_str());
		p.sharedHardware = atoi(
				(dataList.at(i).at(dataList.at(i).size() - 4)).c_str());
		p.Type = (dataList.at(i).at(dataList.at(i).size() - 3)).at(0);

		//a value of 100 lets us know this class section has not been assigned
		p.ClassID = 100;
		//p.ClassID = atoi(
		//		(dataList.at(i).at(dataList.at(i).size() - 2)).c_str());
		p.Priority = atoi(
				(dataList.at(i).at(dataList.at(i).size() - 1)).c_str());

		cout<<p.ProjectID<<endl;
		currentSkill = "";
		for (int j = 0; j < dataList.at(i).at(12).size(); j++) {

			if (dataList.at(i).at(12).at(j) == ',') {

				cout<<currentSkill<<endl;
				for (int k = 0; k < 8; k++) {
					if (currentSkill.compare(skills1[k]) == 0) {
						p.Skills[k] = 1;
					}}
				currentSkill = "";
			} else {
				if(dataList.at(i).at(12).at(j) != '\"'){
				currentSkill.push_back(dataList.at(i).at(12).at(j));

				}

			}
		}

		currentSkill = "";
		for (int j = 0; j < dataList.at(i).at(13).size(); j++) {

			if (dataList.at(i).at(13).at(j) == ',') {
				cout<<currentSkill<<endl;
				for (int k = 8; k < 14; k++) {
					if (currentSkill.compare(skills1[k]) == 0) {
						p.Skills[k] = 1;
					}}
				currentSkill = "";
			} else {
				if(dataList.at(i).at(13).at(j) != '\"'){
				currentSkill.push_back(dataList.at(i).at(13).at(j));}

			}

		}




	/*		if (dataList.at(i).at(12).at(j) == ',') {
				currentSkill = "";
			} else {
				currentSkill.push_back(dataList.at(i).at(12).at(j));
				cout<<currentSkill<<endl;
				for (int k = 0; k < 8; k++) {
					//if (currentSkill.compare(skills1[k]) == 0) {
					//	p.Skills[k] = 1;
					//}
					if (currentSkill.find(skills1[k]) != string::npos) {
						p.Skills[k] = 1;
					}
				}
			}
		}

		currentSkill = "";
		for (int j = 0; j < dataList.at(i).at(13).size(); j++) {

			if (dataList.at(i).at(13).at(j) == ',') {
				currentSkill = "";
			} else {
				currentSkill.push_back(dataList.at(i).at(13).at(j));
				cout<<currentSkill<<endl;
				for (int k = 8; k < 14; k++) {
					if (currentSkill.find(skills1[k]) != string::npos) {
						p.Skills[k] = 1;
					}
				}
			}
		}*/



		projects.push_back(p);
		//cout<<p.ProjectID<<"  priority:"<<p.Priority<<endl;


		projectPool[i-1] = p;

		//last project


		if(i == numProjects-1){
			i=numProjects;
			Project p1 = Project();
			for (int j = 0; j < numSkills; j++) {
				p1.Skills[j] = 0;
			}

					p1.ProjectID = numProjects;

					p1.NDA = atoi((dataList.at(i).at(dataList.at(i).size() - 6)).c_str());
					p1.IPR = atoi((dataList.at(i).at(dataList.at(i).size() - 5)).c_str());
					p1.sharedHardware = atoi(
							(dataList.at(i).at(dataList.at(i).size() - 4)).c_str());
					p1.Type = (dataList.at(i).at(dataList.at(i).size() - 3)).at(0);

					//a value of 100 lets us know this class section has not been assigned
					p1.ClassID = 100;
					//p.ClassID = atoi(
					//		(dataList.at(i).at(dataList.at(i).size() - 2)).c_str());
					p1.Priority = atoi(
							(dataList.at(i).at(dataList.at(i).size() - 1)).c_str());

					cout<<p1.ProjectID<<endl;
					currentSkill = "";
					for (int j = 0; j < dataList.at(i).at(12).size(); j++) {

						if (dataList.at(i).at(12).at(j) == ',') {

							cout<<currentSkill<<endl;
							for (int k = 0; k < 8; k++) {
								if (currentSkill.compare(skills1[k]) == 0) {
									p1.Skills[k] = 1;
								}}
							currentSkill = "";
						} else {
							if(dataList.at(i).at(12).at(j) != '\"'){
							currentSkill.push_back(dataList.at(i).at(12).at(j));

							}

						}
					}


					currentSkill = "";
					for (int j = 0; j < dataList.at(i).at(13).size(); j++) {

						if (dataList.at(i).at(13).at(j) == ',') {
							cout<<currentSkill<<endl;
							for (int k = 8; k < 14; k++) {
								if (currentSkill.compare(skills1[k]) == 0) {
									p1.Skills[k] = 1;
								}}
							currentSkill = "";
						} else {
							if(dataList.at(i).at(13).at(j) != '\"'){
							currentSkill.push_back(dataList.at(i).at(13).at(j));}

						}

					}



			projectPool[numProjects-1] = p1;
			i = numProjects-1;

		}
	}
	for (int i = 0; i < numProjects; i++) {

		cout<<"Project#: "<<projectPool[i].ProjectID<<"  priority:"<<projectPool[i].Priority<<endl;
		for (int d = 0; d < numSkills; d++) {
					cout<<projectPool[i].Skills[d]<<" ";
				}
		cout<<endl;
	}

	return projects;
}

/*********************************************************
 * getQuizID
 *
 * Author: Myles Colina
 *
 * Description:
 * 	Reads in all the quizzes from a Json file, and searches for the quiz ID of the
 * 	quiz that matches the string name entered.
 *
 *Arguments:
 *	string quizName, string filename
 *
 *Returns:
 *  int value of the quiz ID
 */
int Utility::getQuizID(string quizName, string filename) {

	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	int quiz_ID;

	const int numberOfQuizzes = obj["quizzes"].size();

	ClassSection classSection[numberOfQuizzes];

	for (int i = 0; i < numberOfQuizzes; i++) {

		if (quizName.compare(
				obj["quizzes"].get((int) i, "")["title"].asString()) == 0) {

			quiz_ID = obj["quizzes"].get((int) i, "")["id"].asInt();
		}

	}

	return quiz_ID;

}

/*********************************************************
 * getAssignmentID
 *
 * Author: Myles Colina
 *
 * Description:
 * 	Reads in all the assignments from a Json file, and searches for the assignment ID of the
 * 	assignment whose quiz_id that matches the parameter quiz_id .
 *
 *Arguments:
 *	string
 *
 *Returns:
 *  int value of the assignment ID
 */
int Utility::getAssignmentID(int quiz_ID, string filename) {

	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	int assignment_ID;

	const int numberOfQuizzes = obj["assignments"].size();

	ClassSection classSection[numberOfQuizzes];

	for (int i = 0; i < numberOfQuizzes; i++) {

		//make sure that the quiz ids match
		if (quiz_ID == obj["assignments"].get((int) i, "")["quiz_id"].asInt()) {

			assignment_ID = obj["assignments"].get((int) i, "")["id"].asInt();
		}

	}

	return assignment_ID;

}
/*********************************************************
 * getCategoryID
 *
 * Author: Myles Colina
 *
 * Description:
 * 	Reads in all the group categories from a Json file, and searches for the category ID of the
 * 	group category whose course_id that matches the parameter course_id .
 *
 *Arguments:
 *	string
 *
 *Returns:
 *  int value of the assignment ID
 */
int Utility::getCategoryID(int courseID, string filename) {

	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	int group_category_ID;

	const int numberOfCategories = obj["categories"].size();


	for (int i = 0; i < numberOfCategories; i++) {

		//make sure that the course ids match
				if (courseID == obj["categories"].get((int) i, "")["course_id"].asInt()) {
		group_category_ID = obj["categories"].get((int) i, "")["id"].asInt();

				}
	}

	return group_category_ID;
}

/*********************************************************
 * getGroupID
 *
 * Author: Myles Colina
 *
 * Description:
 * 	Reads in the group data from a Json file, and searches for the Group ID of the
 * 	group whose course_id that matches the parameter course_id .
 *
 *Arguments:
 *	string
 *
 *Returns:
 *  int value of the assignment ID
 */
int Utility::getGroupID(int course_ID ,string filename) {

	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	int group_ID;

	const int numberOfCategories = obj["groups"].size();


	for (int i = 0; i < numberOfCategories; i++) {

		//make sure that the course ids match
				if (course_ID == obj["groups"].get((int) i, "")["course_id"].asInt()) {
					group_ID = obj["groups"].get((int) i, "")["id"].asInt();

				}
	}

	return group_ID;
}


vector<Student> Utility::getStudentsFromJson(string filename) {
	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	const int numberOfStudents = obj["students"].size();

	vector<Student> students;
	Student student;
	string desiredRole = "StudentEnrollment";

	for (int i = 0; i < numberOfStudents; i++) {
		if (desiredRole.compare(obj["students"].get((int) i, "")["role"].asString()) == 0) {
			student.StudentID = obj["students"].get((int)i, "")["user_id"].asInt();
			student.ASUriteID = obj["students"].get((int)i, "")["user"]["login_id"].asString();
			student.ClassID = obj["students"].get((int)i, "")["course_id"].asInt();
			students.push_back(student);
		}
	}

	return students;

}


/*********************************************************
 * getSurveyAnswers
 *
 * Author: Myles Colina
 *
 * Description:
 * 	Reads in all the Survey quiz answers from a Json file, and matches the answers to
 * 	to the student whose ID matches.
 *
 *
 *Arguments:
 *	vector <Student> students, int quiz_ID, string filename
 *
 *Returns:
 *  a vector of students who have all their skills and other data.
 */
vector<Student> Utility::getSurveyAnswers(vector<Student> students,
		int assignment_ID, string filename) {

	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	const int numberSubmissions = obj["submissions"].size();

	int numSkills = 14;

	//loop over all submissions
	for (int i = 0; i < numberSubmissions; i++) {

		//loop over all students to find the student who matches the user_id
		for (int j = 0; j < students.size(); j++) {

			if (students[j].StudentID
					== obj["submissions"].get((int) i, "")["user_id"].asInt()) {

				//make sure that the ids match
				if (assignment_ID
						== obj["submissions"].get((int) i, "")["assignment_id"].asInt()) {

					//assign quiz answer data to the student
					auto submissionHistoryArray = obj["submissions"].get(
							(int) i, "")["submission_history"];


					auto data = submissionHistoryArray[0];

					auto submissionData = data["submission_data"];
					auto currentQuestion = submissionData[0];


					//#1-#2 get the students first and last name, space separated.
					students[j].name = currentQuestion["text"].asString();
					students[j].name += " ";
					currentQuestion = submissionData[1];	//next Question #2
					students[j].name += currentQuestion["text"].asString();

					//#3 get the list of asuriteIDS the student does NOT want to work with.
					currentQuestion = submissionData[2];	//next Question #3
					string negativeAffinity =
							currentQuestion["text"].asString();

					//remove the <p><span> from the front and back of the string
					negativeAffinity.erase(0, 9);
					negativeAffinity.erase(negativeAffinity.length() - 11, 12);

					pair<string, bool> x;
					std::istringstream is1(negativeAffinity);
					for (string negativeAffinity; is1 >> negativeAffinity;) {

						x.first = negativeAffinity;
						x.second = false;
						students[j].StudentAffinity.push_back(x);
					}

					//#4 get the list of asuriteIDS the student does want to work with.
					currentQuestion = submissionData[3];	//next Question #4
					string positiveAffinity =
							currentQuestion["text"].asString();

					//remove the <p><span> from the front and back of the string
					positiveAffinity.erase(0, 9);
					positiveAffinity.erase(positiveAffinity.length() - 11, 12);

					std::istringstream is2(positiveAffinity);
					for (string positiveAffinty; is2 >> positiveAffinity;) {

						x.first = positiveAffinity;
						x.second = true;
						students[j].StudentAffinity.push_back(x);
					}

					//#5 get all the skill information from the quiz
					currentQuestion = submissionData[4];	//next Question #5
					for (int k = 0; k < numSkills; k++) {
						string current_skill = "answer_for_skill";
						current_skill += to_string(k + 1);

						students[j].Skills[k] = stoi(
								currentQuestion[current_skill].asString());

					}

					//#6 get all the time availability data
					currentQuestion = submissionData[5];	//next Question #6
					for (int k = 0; k < 4; k++) {
						string current_time = "answer_for_Time";
						current_time += to_string(k + 1);

						students[j].Availability[k] = stoi(
								currentQuestion[current_time].asString());
					}

					//#7 get the NDA and the IPR agreement data
					currentQuestion = submissionData[6];	//next Question #7
					int NDA = stoi(
							currentQuestion["answer_for_NDA"].asString());
					int IPR = stoi(
							currentQuestion["answer_for_IPR"].asString());

					if (NDA == 1) {
						students[j].NDA = true;
					} else if (NDA == 0) {
						students[j].NDA = false;
					}

					if (IPR == 1) {
						students[j].IPR = true;
					} else if (IPR == 0) {
						students[j].IPR = false;
					}

				}
			}
		}
	}

	return students;

}
