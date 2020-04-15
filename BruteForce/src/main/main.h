/*
 * main.h
 *
 * Description:
 *	 This class is the main driver for the skills based assignment of
 *   capstone project teams. The main method of this class starts the
 *   GUI application. Once the user completes all the GUI entries,
 *   main_run is called which is the main driver for the team assignment
 *   process.
 *
 *
 * @author(s) Elizabeth Marquise, Myles Colina, Sean Rogers, Cristi Deleo, Matthew Cilibraise
 * Copyright (C) 2020, ASU Capstone Project
 * All Rights Reserved
 *
 *
 * List of Functions:
 *  int parseLine(char *line)
 *  	- read char by char for a line given for memory
 *
 *  int getValuePhy()
 *		- a function to monitor system memory usage
 *
 *	int getValueVirt()
 *		- a function to monitor system memory usage
 *
 *	constexpr int toConstInt(int constInt)
 *		- a function to convert an int to a constant
 *
 *	void threadFunction(Student studentPool[], Project projectPool[], const int numStudents,
 *	const int numProjects, const int numSkills, const int teamSize, const int numTopTeams,
 *	string results[], int classSection int parseLine(char* line)
 *		- a function to monitor system memory usage
 *
 *	void Steampunk_Option(Fl_Widget *w)
 *		- Callback function for the Steampunk option button. Opens the Steampunk version
 *
 *  void ASU_Option(Fl_Widget *w)
 * 		- Callback function for the ASU option button. Opens the ASU colors version
 *
 *  int main(void)
 *  	-Initial function to start application. Opens the GUI window.
 *
 *	int main_run
 *		-The main driver for the skills based assignment of Capstone project teams.
 *
 *
 */
#ifndef SRC_MAIN_MAIN_H_
#define SRC_MAIN_MAIN_H_




/********* BEGINNING OF INCLUSIONS **********/


/* Class Inclusions */
#include "Student.h"
#include "Project.h"
#include "ClassSection.h"

/* FLTK Inclusions */
#include <FL/Fl_Progress.H>
#include <FL/Fl_Text_Buffer.H>


/* Library Inclusions */
#include <vector>
#include <mutex>
#include <libsoup/soup.h>


using namespace std;
extern mutex mtx;


/********* BEGINNING OF PROGRAM CODE **********/


class main {

public:

	// Variables
	string csvProjectFileName;
	static int numClasses;


	// Public functions
	int main_run(int projects_input, int students_input, string filepath, Fl_Progress *pb,
			Fl_Text_Buffer *terminal, vector<vector<Student>> allStudents,
			vector <ClassSection> allClassSections, vector<SoupCookie> cookies);


	//REMOVE AFTER TESTING!!!
	int main_run2(int projects_input, int students_input, string filepath,
			Fl_Progress *pb, Fl_Text_Buffer *tb, vector<Student> studentsFromCanvas);


};

#endif /* SRC_MAIN_MAIN_H_ */
