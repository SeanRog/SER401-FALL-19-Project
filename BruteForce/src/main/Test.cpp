/*
 * Test.cpp
 *
 *  Created on: Oct 27, 2019
 *      Author: Myles Colina
 *
 *     Description:
 *
 *     Class to hold all our test cases.
 *     To create a new test case, add a new function
 *     (also add function name to the header file)
 *     write the test code into that function, and
 *     call it in main.
 *
 */
#include "Test.h"
#include "json/json.h"
#include "StudentJson.h"
#include "ProjectJson.h"
#include "ClassSectionJson.h"
#include "Student.h"
#include "Project.h"
#include "ClassSection.h"

#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <array>
#include <string>

using namespace std;

Test::Test() {
	// TODO Auto-generated constructor stub
}

Test::~Test() {
	// TODO Auto-generated destructor stub
}

// Task #107
// Author: Cristi DeLeo
void Test::PrintProjectPool(Project projectPool[], int numProjects, int numSkills) {

	Project project;

	cout << endl << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "BEGIN: Test::PrintProjectPool Task#107" << endl << endl;

	cout << "Number of Projects: " << to_string(numProjects) << endl << endl;

	for (int i = 0; i < numProjects; i++) {

		project = *(projectPool + i);

		cout << "Project ID: ";
		cout << project.ProjectID << endl;

		cout << "Type:  " ;
		cout << project.Type << endl;

		cout << "Class ID:  " ;
				cout << project.ClassID << endl;

		cout << "Priority: ";
		cout << project.Priority << endl;
		cout << "Skills: ";
		for (unsigned int j = 0; j < numSkills; j++) {
			cout << to_string(project.Skills[j]);
			cout << " ";
		}
		cout << endl << endl;
	}

	cout << "END: Test::PrintProjectPool Task#107" << endl;
	cout << "----------------------------------------------------------";
	cout << endl << endl;
}

// Task #107
// Author: Cristi DeLeo
void Test::PrintStudentPool(Student studentPool[], int numStudents, int numSkills) {

	Student student;

	int numTimes = 4;
	int numAffinities = 0;

	cout << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "BEGIN: Test::PrintStudentPool Task#107" << endl << endl;

	cout << "Number of Students: " << to_string(numStudents) << endl << endl;

	for (int i = 0; i < numStudents; i++) {

		student = *(studentPool + i);

		numAffinities = student.StudentAffinity.size();

		cout << "Student ID: ";
		cout << student.StudentID << endl;

		cout << "Class ID: ";
		cout << student.ClassID << endl;

		cout << "Skills: ";
		for (unsigned int j = 0; j < numSkills; j++) {
			cout << to_string(student.Skills[j]);
			cout << " ";
		}

		cout << endl << endl;
		cout << "Begin Affinities: " << endl;
		for (int i = 0; i < numAffinities; i++){
			cout << "Peer ID: "
					+ to_string(student.StudentAffinity[i].first)
					+ "  Affinity: "
					+ to_string(student.StudentAffinity[i].second)<<endl;
		}

		cout << "Available Times: ";
		for(int j = 0; j < numTimes; j++) {
			cout << student.Availability[j];
		}
		cout << endl << endl;
	}

	cout << "END: Test::PrintStudentPool Task#107" << endl;
	cout << "----------------------------------------------------------";
	cout << endl << endl;
}

void Test::PrintProjectStudentSkills(int projectStudentSkills[], int numProjects, int numStudents) {

	cout << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "BEGIN: Test::PrintProjectStudentSkills" << endl << endl;

	for (int i = 0; i < numProjects; i++) {
		for (int j = 0; j < numStudents; j++) {
			cout << "[" << i << "][" << j << "] ";
			cout << *(projectStudentSkills + (i * numStudents) + j);
		}
		cout << endl;
	}

	cout << endl;
	cout << "END: Test::PrintProjectStudentSkills Task#107" << endl;
	cout << "----------------------------------------------------------";
	cout << endl << endl;
}

// AUTHOR: CRISTI DELEO
// DATE: 11/07/2019
void Test::PrintPercentMatrix(int percentMatrix[], int numProjects, int numClassSections) {

	cout << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "BEGIN: Test::PrintPercentMatrix" << endl << endl;

	for (int i = 0; i < numProjects; i++) {
		for (int j = 0; j < numClassSections; j++) {
			cout << "[" << i << "][" << j << "] ";
			cout << *(percentMatrix + (i * numClassSections) + j);
		}
		cout << endl;
	}

	cout << endl;
	cout << "END: Test::PrintPercentMatrix" << endl;
	cout << "----------------------------------------------------------";
	cout << endl << endl;
}

// Function to test structs.
// Task#97
void Test::StructTest() {

		//Task#97 Testing the student project and class section structs.
		cout<<endl;
		cout << "----------------------------------------------------------" << endl;
		cout << "BEGIN: Test::StructTest Student|Project|ClassSection Task#97" << endl;

		const int count = 12;//the highest number of students in the affinity list.

	    //Student Struct test
		//creating student object

		//skills
		 int s[7] = {1,0,2,0,3,2,2};
		 //StudentAffinity
			     vector< pair <int, bool> > aff;
			     for (int i = 0; i < count; i++){
			    	 pair <int, bool> x = {12310+i,true};
			    	 aff.push_back(x);
			    	 if(i>=5){
			    		 pair <int, bool> x= {12310+i,false};
			    		 aff.push_back(x);}
			    	 }
	    //Availability
	    int times[4] = { 0,1,2,3};

		//call student constructor
		 Student s1(123456, 1, s,  aff,  times);

	     //print Student results
		 cout <<"Student Info " << endl;
		 cout <<"-------------------------" << endl;
		 cout << "Student ID: " + to_string(s1.StudentID) << endl;
		 cout << "Skills: ";
		 for (int i = 0; i < 7; i++){
			 cout << to_string(s1.Skills[i]) + " ";
		 }
		 cout << endl;
		 for (int i = 0; i < count; i++){
		 cout << "Peer ID: " + to_string(s1.StudentAffinity[i].first) + "  Affinity: " + to_string(s1.StudentAffinity[i].second)<<endl;
		 	 }
	     cout << endl;
	     cout << "Available times to meet: ";
	     for (int i = 0; i < 4; i++){
	     	 cout <<  to_string(s1.Availability[i]) + " ";
	     	 	 }
	      cout << "\n \n  " << endl;


	     //Project Struct test
	      //creating Project object

	         int pskills[7] = {1,0,0,0,1,2,2};
	     	 Project p1( 35,'O', 1, pskills);

	     	//print Project results
	     		 cout <<"Project Info " << endl;
	     		 cout <<"-------------------------" << endl;
	     		 cout << "Project ID: " + to_string(p1.ProjectID) << endl;
	     		 cout << "Type:  " ;
	     	     cout.put(p1.Type);
	     		 cout << endl;
	     	     cout << "Priority:  " +  to_string(p1.Priority);
	     		 cout << "Skills: ";
	     		 for (int i = 0; i < 7; i++){
	     			 cout << to_string(p1.Skills[i]) + " ";
	     		 }
	     		 cout << "\n \n  " << endl;

	 //Class Section struct test
	     	const int NumOfStudents = 15;
	     	const int NumOfProjects = 3;

	     	 //ClassSection<NumOfStudents> c1(1, 'O');
	     	ClassSection c1(1,'O');
	     	//for (int i = 0; i < NumOfStudents; i++){
	     	 //c1.Enrollment[i]=i;}

	     	//for (int i = 0; i < NumOfProjects; i++){
	     	 //c1.ProjectPool.push_back(i);}

	     	//print Project results
	     		 cout <<"Class Section Info " << endl;
	     		 cout <<"-------------------------" << endl;
	     		 cout << "Class ID: " + to_string(c1.ClassID) << endl;
	     	     cout << "Type:  " ;
	     	     cout.put(c1.Type);
	     	    		 cout << endl;
	     		 //cout << "Number of Students in this section: " + to_string(NumOfStudents) << endl;
	     		 //cout << "Students: ";
	     		 //for (int i = 0; i < NumOfStudents; i++){
	     		//	 	 cout << to_string(c1.Enrollment[i]) + ", ";}
	     		cout << endl;
	     		//cout << "Number of Projects in pool: " + to_string(NumOfProjects) << endl;
	     		//cout << "Projects: ";
	     		//for (int i = 0; i < NumOfProjects; i++){
	     		//	     cout << to_string(c1.ProjectPool[i]) + ", ";}

	     	   cout << endl << endl;
	     	   cout << "END: Test::StructTest Student|Project|ClassSection Task#97" << endl;
	     	   cout << "----------------------------------------------------------";
		// end testing for Task#97
}
