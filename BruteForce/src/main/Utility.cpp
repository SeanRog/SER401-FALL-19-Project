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

#include <iostream>
#include <utility>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>
#include <stdio.h>

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
void Utility::initProjectPool(string filename, Project projectPool[], int numProjects) {
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
void Utility::initStudentPool(string filename, Student studentPool[], int numStudents) {
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
void Utility::initClassSectionPool(string filename, ClassSection classSectionPool[],
        Student studentPool[], int numClassSections, int numStudents) {
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
void Utility::initProjectStudentSkills(Project projectPool[], Student studentPool[],
		int projectStudentSkills[], int numProjects, int numStudents, int numSkills) {

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
int Utility::getProjectXskill(Project projectPool[], int i, int j){
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
int Utility::getSkillXstudent(Student studentPool[], int i, int j){
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
vector<vector<int>> Utility::calcProjectXStudentMatrix(vector<Student> students, vector<Project> projects){
	int numStudents = students.size();
	int numProjects = projects.size();
	int numSkills = (sizeof(students.at(0).Skills)/sizeof(*students.at(0).Skills));
	vector<vector<int>> projectXstudentMatrix;
	// create projectXskill matrix
	int projectXskill[numProjects][numSkills] = {0};
	for (int i = 0; i < numProjects; i++){
		for (int j = 0; j < numSkills; j++){
			projectXskill[i][j] = projects.at(i).Skills[j];
		}
	}
	// create skillXstudent matrix transposing skills and students
	int skillXstudent[numSkills][numStudents] = {0};
	for (int i = 0; i < numSkills; i++){
		for (int j = 0; j < numStudents; j++){
			skillXstudent[i][j] = students.at(j).Skills[i];
		}
	}
	//cout << "\t";
	for (int i = 0; i < numStudents ; i++ ){
		//cout << "st" << students.at(i).StudentID << "\t";
	}
	cout<< endl;
	int projectXstudent[numProjects][numStudents];
	for (int rows = 0; rows < numProjects; rows++){
		// print project name to projectxstudent matrix
		//string p = to_string(rows);
		//cout << "p" + p + "\t";
		// do the multiplication
		for (int cols = 0; cols < numStudents; cols++){
			projectXstudent[rows][cols] = {0};
			for (int inner = 0; inner < numSkills; inner++){
				projectXstudent[rows][cols] = projectXstudent[rows][cols] +  projectXskill[rows][inner] * skillXstudent[inner][cols];

			}
			//cout << projectXstudent[rows][cols] << "\t\t";
		}
		//cout << "\n";
	}
	for (int i = 0; i < numProjects; i++){
		vector<int> currProject;
		for (int j= 0; j < numStudents; j++){
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

	for (int i = 0; i <=end; ) {
		if (projectPool[i].Type == t0) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Type != t0) {
			swap(projectPool[i], projectPool[end--]);
	    } else {
	    	i++;
	    };
	}

	t0Index = 0;

	for (int i = 0; i <=end; ) {
		if (projectPool[i].Type == t0) {
			t0Index++;
			i++;
		} else {
			i++;
		};
	}

	start = t0Index;
	end = numProjects - 1;

	for (int i = t0Index; i <=end; ) {
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

	for (int i = 0; i <=end; ) {
		if (projectPool[i].Priority == t0) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Priority != t0) {
			swap(projectPool[i], projectPool[end--]);
	    } else {
	    	i++;
	    };
	}

	t0Index = 0;

	for (int i = 0; i <=end; ) {
		if (projectPool[i].Priority == t0) {
			t0Index++;
			i++;
		} else {
			i++;
		};
	}

	start = t0Index;
	end = endO - 1;

	for (int i = t0Index; i <=end; ) {
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

	for (int i = 0; i <=end; ) {
		if (projectPool[i].Priority == t0) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Priority != t0) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}

	t0Index = endO;

	for (int i = 0; i <=end; ) {
		if (projectPool[i].Priority == t0) {
			t0Index++;
			i++;
		} else {
			i++;
		};
	}

	start = t0Index;
	end = endG;

	for (int i = t0Index; i <=end; ) {
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

	for (int i = 0; i <=end; ) {
		if (projectPool[i].Priority == t0) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Priority != t0) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}

	t0Index = endG;

	for (int i = 0; i <=end; ) {
		if (projectPool[i].Priority == t0) {
			t0Index++;
			i++;
		} else {
			i++;
		};
	}

	start = t0Index;
	end = endH - 1;

	for (int i = t0Index; i <=end; ) {
		if (projectPool[i].Priority == t1) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Priority != t1) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}
}

void Utility::PriorityPartition(Project projectPool[], int numProjects,
		int t0, int t1, int t2) {

	int start = 0;
	int end = numProjects - 1;
	int t0Index = 0;

// SORT PROJECTS
	start = 0;
	t0Index = start;

	for (int i = 0; i <=end; ) {
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

	for (int i = 0; i <=end; ) {
		if (projectPool[i].Priority == t0) {
			t0Index++;
			i++;
		} else {
			i++;
		};
	}

	start = t0Index;
	end = numProjects - 1;

	for (int i = t0Index; i <=end; ) {
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

	for (int i = 0; i <=end; ) {
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
void Utility::printIntMatrix(vector<vector<int>> a){
	cout << endl;
	for (int i = 0; i < a.size() ; i++){
		for (int j = 0 ; j < a.at(i).size() ; j++){
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
	int SectionSkills[NumOfClassSections][7] = {0};
	int numStudentsByClass[NumOfClassSections];

    Student student;
    Project project;

    for(int i = 0; i < NumOfClassSections; i++) {
        //number of students in class sections
        int numStudents = studentList[i].size();
        numStudentsByClass[i] = numStudents;

        for(int j = 0; j < numStudents; j++) {
            student = studentList[i][j];
            for(int k = 0; k < 7; k++) {
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
	int skillXproject[numProjects][7] = {0};

	for (int i = 0; i < 7; i++){
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
	  		projectXsection[rows][cols] = {0};
	  		for (int inner = 0; inner < 7; inner++) {
	  			projectXsection[rows][cols] = projectXsection[rows][cols]
                        +  SectionSkills[cols][inner] * skillXproject[inner][rows];
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
    int ProjectSkills[numProjects][1] = {0};

    for (int i = 0; i < numProjects; i++) {
        int sum = 0;
        for (int j = 0; j < 7; j++) {
            sum  = sum + projectList[i].Skills[j];
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
    int** percentMatrix = 0;
    percentMatrix = new int *[numProjects];

    for (int i = 0; i < numProjects; i++) {
        percentMatrix[i] = new int [NumOfClassSections];
        for (int j = 0; j < NumOfClassSections; j++) {
            float percent= 0;
            float x = 0;
            x = (ProjectSkills[i][0] * numStudentsByClass[j]);
            percent = projectXsection[i][j]/ x;
            percent = percent * 100;
            percent = (int)percent;

            //store percentage in matrix as int, so if 88.8, it will be 88.
            percentMatrix[i][j] = percent;
        }
    }
    return  percentMatrix;
}//end ProjectToSectionPercentages


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
		int percentMatrix[], int numProjects, int numStudents, int numClassSections,
		int numSkills) {

	//create a 2d array containing the sum of all the students skills, for each skill.
	int SectionSkills[numClassSections * numSkills] = {0};
	int numStudentsByClass[numClassSections] = {0};

    Student student;
    Project project;
    ClassSection classSection;

    for(int i = 0; i < numClassSections; i++) {
    	classSection = *(classSectionPool + i);
        numStudentsByClass[i] = classSection.Enrollment;
        for(int j = 0; j < numStudentsByClass[i]; j++) {
            student = *(studentPool + j);
            for(int k = 0; k < numSkills; k++) {
				SectionSkills[(i * numSkills) + k] += student.Skills[k];
            }
        }
    }

    //create skillXproject matrix
	int skillXproject[numProjects * numSkills];

	for (int i = 0; i < numSkills; i++){
		for (int j = 0; j < numProjects; j++) {
			project = *(projectPool + j);
            skillXproject[(i * numProjects) + j] = project.Skills[i];
        }
    }

    // Calculate Project x Section skills Matrix
	int projectXsection[numProjects * numClassSections] = {0};

	for (int i = 0; i < numProjects; i++) {
	  	for (int j = 0; j < numClassSections; j++) {
	  		projectXsection[(i * numClassSections) + j] = {0};
	  		for (int k = 0; k < numSkills; k++) {
	  			projectXsection[(i * numClassSections) + j] +=
                        SectionSkills[(j * numSkills) + k] * skillXproject[(k * numProjects) + i];
            }
        }
    }

    //create a 2d array for the projects, containing the maximum
    //skill score sum a student could have on that project.
    int ProjectSkills[numProjects] = {0};

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
            float percent= 0;
            float x = 0;
            x = (ProjectSkills[i] * numStudentsByClass[j]);
            percent = projectXsection[(i * numClassSections) + j] / x;
            percent = percent * 100;
            percent = (int)percent;

            //store percentage in matrix as int, so if 88.8, it will be 88.
            percentMatrix[(i * numClassSections) + j] = percent;
        }
    }
    //return  percentMatrix;
}//end ProjectToSectionPercentages


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
        Student studentPool[], ClassSection classSectionPool[],
		int numProjects, int numStudents, int numClassSections,
		int numSkills, int studentsInSections[]) {

	//create a 2d array containing the sum of all the students skills, for each skill.
	int SectionSkills[numClassSections * numSkills] = {0};

    Student student;
    Project project;
    ClassSection classSection;

    for(int i = 0; i < numClassSections; i++) {

    	classSection = *(classSectionPool + i);

        for(int j = 0; j < numStudents; j++) {
            student = *(studentPool + j);
            if (student.ClassID == classSection.ClassID) {
            	for(int k = 0; k < numSkills; k++) {
            		SectionSkills[(i * numSkills) + k] += student.Skills[k];
            	}
            }
        }
    }

    //create skillXproject matrix
	int skillXproject[numProjects * numSkills];

	for (int i = 0; i < numProjects; i++){
		for (int j = 0; j < numSkills; j++) {
			project = *(projectPool + i);
            skillXproject[(i * numSkills) + j] = project.Skills[j];
        }
    }

    // Calculate Project x Section skills Matrix
	int projectXsection[numProjects * numClassSections] = {0};

	for (int i = 0; i < numProjects; i++) {

		project = *(projectPool + i);

	  	for (int j = 0; j < numClassSections; j++) {

	  		classSection = *(classSectionPool + j);
	  		projectXsection[(i * numClassSections) + j] = {0};

	  		if (project.Type == classSection.Type || project.Type == 'H') {
	  			for (int k = 0; k < numSkills; k++) {
	  				projectXsection[(i * numClassSections) + j] +=
                        (SectionSkills[(j * numSkills) + k] * skillXproject[(i * numSkills) + k]);
	  			}
	  		}
        }
    }

	//vector to store the minimum number of projects that should be assigned to each class section.
	vector <int> MinProjectsPerClassSection;
		for (int i = 0; i < numClassSections; i++) {
			int minNumProjects = calc_projects(studentsInSections[i], 5, 4);
			MinProjectsPerClassSection.push_back(minNumProjects);

			cout<<"Class section: "<< i << " Number of students:"<<studentsInSections[i] <<" MinNumofProjects Required: "<< minNumProjects<<endl;
			}

	//increment vector to store the number of projects that have been assigned to a class section.
	vector <int> ProjectsToClassCount;
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
	 vector <ClassSection> ClassSections;
	//vector to store all online class sections
     vector <ClassSection> OnlineClassSections;
    //vector to store all ground class sections
     vector <ClassSection> GroundClassSections;

	for (int i = 0; i < numClassSections; i++) {
		classSection = *(classSectionPool + i);
		ClassSections.push_back(*(classSectionPool + i));

		if(classSection.Type == 'O'){
		OnlineClassSections.push_back(*(classSectionPool + i));

		}else if(classSection.Type == 'G'){
		GroundClassSections.push_back(*(classSectionPool + i));

		}

	}


	for (int i = 0; i < numProjects; i++) {

		project = *(projectPool + i);
		highestScore = 0;
		highestClassSection = 0;



//Assign the Online projects
		if(projectPool[i].Type == 'O'){


			//refill vector if empty
									if(OnlineClassSections.empty()){
									for (int k = 0; k < numClassSections; k++) {
										classSection = *(classSectionPool + k);
										if(classSection.Type == 'G'){
											OnlineClassSections.push_back(*(classSectionPool + k));

									}}}



									for (int j = 0; j < OnlineClassSections.size(); j++) {

										classSection = OnlineClassSections[j];
										currentScore = projectXsection[(i * numClassSections) + OnlineClassSections[j].ClassID];

									 //make sure that this class section has not reached the minNumOfProjects added.
							         if(ProjectsToClassCount[OnlineClassSections[j].ClassID] < MinProjectsPerClassSection[OnlineClassSections[j].ClassID]){
										if (currentScore > highestScore) {
											highestScore = currentScore;
											highestClassSection = OnlineClassSections[j].ClassID;
										} else if (currentScore == highestScore &&
												currentScore != 0) {
											randInt = rand()%2;
											if (randInt == 1) {
												highestClassSection = OnlineClassSections[j].ClassID;
											}
										}
									}
									}

									// Checks to make sure the highest score is greater than 0
									// If highest score = 0, then project and class section
									// types did not match
									if (highestScore > 0 || OnlineClassSections.size()==1) {
										for (int j = 0; j < OnlineClassSections.size(); j++) {

										if(OnlineClassSections[j].ClassID==highestClassSection || OnlineClassSections.size()==1){
											if(ProjectsToClassCount[OnlineClassSections[j].ClassID] < MinProjectsPerClassSection[OnlineClassSections[j].ClassID]){
										classSection = OnlineClassSections[j];
										projectPool[i].ClassID = classSection.ClassID;
										OnlineClassSections.erase(OnlineClassSections.begin() + j);
										//increment the number of projects added to this class section
										ProjectsToClassCount[classSection.ClassID]++;
											}
										}
									}

								  }


//Assign the Ground Projects
		}else if(projectPool[i].Type ==  'G'){


			//refill vector if empty
						if(GroundClassSections.empty()){
						for (int k = 0; k < numClassSections; k++) {
							classSection = *(classSectionPool + k);
							if(classSection.Type == 'G'){
									GroundClassSections.push_back(*(classSectionPool + k));

						}}}



						for (int j = 0; j < GroundClassSections.size(); j++) {

							classSection = GroundClassSections[j];
							currentScore = projectXsection[(i * numClassSections) + GroundClassSections[j].ClassID];

						 //make sure that this class section has not reached the minNumOfProjects added.
				         if(ProjectsToClassCount[GroundClassSections[j].ClassID] < MinProjectsPerClassSection[GroundClassSections[j].ClassID]){
							if (currentScore > highestScore) {
								highestScore = currentScore;
								highestClassSection = GroundClassSections[j].ClassID;
							} else if (currentScore == highestScore &&
									currentScore != 0) {
								randInt = rand()%2;
								if (randInt == 1) {
									highestClassSection = GroundClassSections[j].ClassID;
								}
							}
						}
						}

						// Checks to make sure the highest score is greater than 0
						// If highest score = 0, then project and class section
						// types did not match
						if (highestScore > 0 || GroundClassSections.size()==1) {
							for (int j = 0; j < GroundClassSections.size(); j++) {

							if(GroundClassSections[j].ClassID==highestClassSection || GroundClassSections.size()==1){
								if(ProjectsToClassCount[GroundClassSections[j].ClassID] < MinProjectsPerClassSection[GroundClassSections[j].ClassID]){
							classSection = GroundClassSections[j];
							projectPool[i].ClassID = classSection.ClassID;
							GroundClassSections.erase(GroundClassSections.begin() + j);
							//increment the number of projects added to this class section
							ProjectsToClassCount[classSection.ClassID]++;
								}
							}
						}

					  }

//Assign the Hybrid Projects
		}else{

		//refill vector if empty
		if(ClassSections.empty()){
		for (int k = 0; k < numClassSections; k++) {
			ClassSections.push_back(*(classSectionPool + k));
		}}



		for (int j = 0; j < ClassSections.size(); j++) {

			classSection = ClassSections[j];
			currentScore = projectXsection[(i * numClassSections) + ClassSections[j].ClassID];

		 //make sure that this class section has not reached the minNumOfProjects added.
         if(ProjectsToClassCount[ClassSections[j].ClassID] < MinProjectsPerClassSection[ClassSections[j].ClassID]){
			if (currentScore > highestScore) {
				highestScore = currentScore;
				highestClassSection = ClassSections[j].ClassID;
			} else if (currentScore == highestScore &&
					currentScore != 0) {
				randInt = rand()%2;
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

			if(ClassSections[j].ClassID==highestClassSection){
				if(ProjectsToClassCount[ClassSections[j].ClassID] < MinProjectsPerClassSection[ClassSections[j].ClassID]){
			classSection = ClassSections[j];
			projectPool[i].ClassID = classSection.ClassID;
			//increment the number of projects added to this class section
			ProjectsToClassCount[classSection.ClassID]++;
			ClassSections.erase(ClassSections.begin() + j);

				}
			}
		}

	  }else{

		  ClassSections.clear();
		  for (int k = 0; k < numClassSections; k++) {

		  			ClassSections.push_back(*(classSectionPool + k));
		  		}


		  for(int j = 0; j < ClassSections.size(); j++) {
		  if(ProjectsToClassCount[ClassSections[j].ClassID] < MinProjectsPerClassSection[ClassSections[j].ClassID]){

			  projectPool[i].ClassID = ClassSections[j].ClassID;
			  ProjectsToClassCount[ClassSections[j].ClassID]++;
			  break;

		  }else{
		  //No more room in any class Section for this project, so
		  //assign it a value of 99999.
		  projectPool[i].ClassID = 99999;}

	  }}

		}

	}// end i num projects loop


	for (int k = 0; k < numClassSections; k++) {
		cout<<"Class section #"<<k<<" Number of Projects assigned: "<<ProjectsToClassCount[k]<<endl;

	}


}//end ProjectToSectionPercentages


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
	   file.open("newProjects.json",ios::out);


	    //Start of JSON file
	    file << "{ \n\"projects\":[\n";

	    //Loops through projectID to print
	    for(int projectID = 1; projectID < (numProjects+1); projectID++) {

	        /*Prints out schema: {"ProjectID": (projectID#),the projectID
	         * number is set to have width of 3 if the number (e.g. 1)
	         * is less than 3, it will fill with 0's. (e.g. 001)     */
	        file << "{\"ProjectID\": " << projectID << ",\n";


	        /*Prints out schema: "Priority": (Priority), priority can be
	         * 0,1, or 2. This file randomizes it between the three options.  */
	        file << " \"Priority\": " << rand() % (2 +1) << ",\n";


	        /*Prints out schema: "Skills": [(skills)], generates Skills from
	         * numSkills. Randomizes values between 0-4 for each skill.      */
	        file << " \"Skills\": [";
	        for(int i = 0; i < (numSkills); i++){
	            if(i < (numSkills-1)) {
	                file << rand() % (2 +1) << ",";}
	            else {
	                file << rand() % (2 +1)<< "],\n";    }    }


	        /*Prints out schema: "Type": O/G/H, right now 80% is hybrid
	         * 10% online and 10% ground projects    */

	        //file << " \"Type\": ";
	    	//      file << "\"H\" },\n\n";


	        file << " \"Type\": ";
	        int percent = (int) numProjects * (0.10);
	        if(projectID < (percent+1)) {
	            file << "\"O\" }, \n\n"; }
	        else if ( projectID > percent && projectID < ((percent+percent+1))) {
	            file << "\"G\" }, \n\n"; }
	        else if ( projectID == numProjects) {
	            file << "\"H\" }\n\n"; }
	        else {
	            file << "\"H\" },\n\n"; }
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
void Utility::makeStudentJSON(int numStud, int numSkill) {

	  // Variables
	  ofstream file;
	  int numStudent = numStud;
	  int numSkills = numSkill;
      int student_25 =(int) (numStudent * 0.25);
      int student_50 =(int) (numStudent * 0.50);
      int student_75 =(int) (numStudent * 0.75);

	   // opening file in write mode
	   file.open("newStudents.json",ios::out);

	   //Start of JSON file
	   file << "{ \n\"students\":[\n";

      //Loops through studentIDs to print
      for(int studentID = 1; studentID <= numStudent; studentID++) {

       string asuID = "ASU"+to_string(studentID);
       /*Prints out schema: {"StudentID": (studentID#), */
       file << "{\"ASUriteID\": \"" << asuID << "\",\n";

       /*Prints out schema: {"StudentID": (studentID#), */
       file << "\"StudentID\": " << studentID << ",\n";

        /*Prints out schema: "ClassID": (classID), classID is divided
         * equally into 4 sections   */
        if(studentID <= student_25) {
           file << " \"ClassID\": 0,\n";   }
        if(studentID > student_25 && studentID <= student_50) {
            file << " \"ClassID\": 1,\n";   }
        if(studentID > student_50 && studentID <= student_75) {
            file << " \"ClassID\": 2,\n";   }
        if(studentID > student_75 && studentID <= numStudent) {
            file << " \"ClassID\": 3,\n";   }


        /*Prints out schema: "Skills": [(skills)],  ramdomly generates skills
         * with values 0-4, total skills given as a parameter         */
        file << " \"Skills\": [";
        for(int i = 0; i < numSkills; i++){
            if(i < (numSkills-1)) {
                file << rand() % (4 +1) << ","; }
            else {
                file << rand() % (4 +1) << "],\n";  }
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
        if ( studentID %3 ==0 || studentID %4 ==0) {

            //Negative affinity matches
            int rand_1_25 = rand() % (student_25 + 1);
            while(rand_1_25 ==  studentID) {
                rand_1_25 = rand() % (student_25 + 1); }

            int rand_1_50 = rand() % (student_50-student_25 + 1) + student_25;
            while(rand_1_50 ==  studentID) {
                rand_1_50 = rand() % (student_50-student_25 + 1) + student_25; }

            int rand_1_75 = rand() % (student_75-student_50 + 1) +student_50;
            while(rand_1_75 ==  studentID) {
                rand_1_75 = rand() % (student_75-student_50 + 1) +student_50; }

            int rand_1_100 = rand() % (numStudent-student_75 + 1) + student_75;
            while(rand_1_100 ==  studentID) {
                rand_1_100 = rand() % (numStudent-student_75 + 1) + student_75; }

            //Positive affinity matches
            int rand_2_25 = rand() % (student_25 + 1);
            while(rand_2_25 ==  studentID || rand_2_25 == rand_1_25) {
                rand_2_25 = rand() % (student_25 + 1); }

            int rand_2_50 = rand() % (student_50-student_25 + 1) + student_25;
            while(rand_2_50 ==  studentID || rand_2_50 == rand_1_50) {
                rand_2_50 = rand() % (student_50-student_25 + 1) + student_25; }

            int rand_2_75 = rand() % (student_75-student_50 + 1) +student_50;
            while(rand_2_75 ==  studentID || rand_2_75 == rand_1_75) {
                rand_2_75 = rand() % (student_75-student_50 + 1) +student_50; }

            int rand_2_100 = rand() % (numStudent-student_75 + 1) + student_75;
            while(rand_2_100 ==  studentID || rand_2_100 == rand_1_100) {
                rand_2_100 = rand() % (numStudent-student_75 + 1) + student_75; }

            //printing out affinity
            file << "[";
            if(studentID %3 == 0) {
                if(studentID < student_25) {
                    file << rand_1_25 << ", false";}
                if(studentID >= student_25 && studentID < student_50) {
                    file << rand_1_50 << ", false"; }
                if(studentID >= student_50 && studentID < student_75) {
                    file << rand_1_75 << ", false"; }
                if(studentID >= student_75 && studentID <= numStudent) {
                    file << rand_1_100 << ", false"; }
            }
            if ( studentID %4 == 0) {
                if(studentID %3 != 0) {
                    if(studentID < student_25) {
                        file << rand_2_25 << ", true";}
                    if(studentID >= student_25 && studentID < student_50) {
                        file << rand_2_50 << ", true"; }
                    if(studentID >= student_50 && studentID < student_75) {
                        file << rand_2_75 << ", true"; }
                    if(studentID >= student_75 && studentID <= numStudent) {
                        file << rand_2_100 << ", true"; }
                }
                if(studentID %3 == 0) {
                    if(studentID < student_25) {
                        file << ", " << rand_2_25 << ", true";}
                    if(studentID >= student_25 && studentID < student_50) {
                        file << ", " << rand_2_50 << ", true"; }
                    if(studentID >= student_50 && studentID < student_75) {
                        file << ", " << rand_2_75 << ", true"; }
                    if(studentID >= student_75 && studentID <= numStudent) {
                        file << ", " << rand_2_100 << ", true"; }
                }
            }
            file << "],\n";
        }
        else {
            file << "null,\n"; }


        /*Prints out schema: "Availability": [(Availability)] }
         * ramdomly generates 4 times with values 0-5
         */
        file << " \"Availability\": [";
        for(int i = 0; i < 4; i++){
            if(i < 3) {
                file << rand() % (5 +1) << ","; }
            else {
                file << rand() % (5 +1); }
        }
        if(studentID < numStudent ) {
        	file << "] },\n\n";    }
        else if( studentID == numStudent) {
          	file << "] }\n\n";    }
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
int Utility::calc_projects(int numStudents, int teamSize, int minTeamSize){
    int numProjects;
    int numStudentsModTeamSize;
    int currentProjectCount;
    int numStudentsNeeded;

    numStudentsModTeamSize = numStudents % teamSize;

    if(numStudentsModTeamSize == 0) {
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
        if(numStudentsNeeded > currentProjectCount){
            if(teamSize > minTeamSize){
                teamSize--;
            } else if(teamSize == minTeamSize){
                teamSize--;
                minTeamSize--;
            } else{
                // Error catch
            }
            calc_projects(numStudents, teamSize, minTeamSize);
        } else if(numStudentsNeeded <= currentProjectCount){
            numProjects = ((numStudents - numStudentsModTeamSize) / teamSize) + 1;
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
int Utility::NumOfTeamsOf4(int numStudents, int teamSize){

	 int numStudentsMod = numStudents % teamSize;

	 if(numStudentsMod == 4){
		 return 1;

	 }else if(numStudentsMod == 3){
		 return 2;

	 }else if(numStudentsMod == 2){
		 return 3;

	 }else if(numStudentsMod == 1){
		 return 4;

	 }else if(numStudentsMod == 0){
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
vector<vector<string>> Utility::toCSVsse (string filename) {
	ifstream file(filename);

		vector<vector<string>> dataList;

		string line = "";

		while(getline(file,line)) {
			vector<string> vec;
			string element = "";
			for(int i = 0; i < line.length(); i++) {

				if(line.at(i) == ',') {
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
vector<vector<string>> Utility::toCSVcse (string filename) {
	ifstream file(filename);

	vector<vector<string>> dataList;

		string line = "";

		int bracketCount = 0;
		while(getline(file,line)) {
			vector<string> vec;
			string element = "";
			for(int i = 0; i < line.length(); i++) {
				if(line.at(i) == '[') {
					bracketCount++;
				}
				if(line.at(i) == ']') {
					bracketCount--;
				}
				if(line.at(i) == ',' && bracketCount == 0) {
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



