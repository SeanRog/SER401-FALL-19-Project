/*
 * Utility.cpp
 *
 *  Created on: Oct. 29, 2019
 *      Author: mcilibra
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

#include "json/json.h"
#include "Student.h"
#include "Utility.h"

namespace std {

Utility::Utility() {
	// TODO Auto-generated constructor stub

}

Utility::~Utility() {
	// TODO Auto-generated destructor stub
}

int Utility::getNumProjects(string filename) {
	//read file named profile.json, then parse it as json,
	//then store that parse into obj
	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);
	//int numberOfProjects = obj["projects"].size();

	return obj["projects"].size();
}

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
	cout << "\t";
	for (int i = 0; i < numStudents ; i++ ){
		cout << "st" << students.at(i).StudentID << "\t";
	}
	cout<< endl;
	int projectXstudent[numProjects][numStudents];
	for (int rows = 0; rows < numProjects; rows++){
		// print project name to projectxstudent matrix
		string p = to_string(rows);
		cout << "p" + p + "\t";
		// do the multiplication
		for (int cols = 0; cols < numStudents; cols++){
			projectXstudent[rows][cols] = {0};
			for (int inner = 0; inner < numSkills; inner++){
				projectXstudent[rows][cols] = projectXstudent[rows][cols] +  projectXskill[rows][inner] * skillXstudent[inner][cols];

			}
			cout << projectXstudent[rows][cols] << "\t\t";
		}
		cout << "\n";
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


} /* namespace std */
