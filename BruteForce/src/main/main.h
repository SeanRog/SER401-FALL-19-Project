/*
 * main.h
 *
 * Description: Header class for main.cpp. Used for allowing main_run to be executed
 * 				from other classes, such as the GUI classes.
 *
 *  Copyright (C) 2020 ASU
 *	Matthew Cilibraise, Myles Colina, Cristi DeLeo, Elizabeth Marquise, Sean Rogers,
 *	initial idea contributed by Douglas Sandy, All rights reserved
 */

#ifndef SRC_MAIN_MAIN_H_
#define SRC_MAIN_MAIN_H_

#include "Student.h"

#include <FL/Fl_Progress.H>
#include <FL/Fl_Text_Buffer.H>
#include <vector>
#include <mutex>
#include <libsoup/soup.h>
#include "Student.h"
#include "Project.h"
#include "ClassSection.h"

using namespace std;

extern mutex mtx;

class main {

public:
	string csvProjectFileName;
	static int numClasses;

	int main_run(int projects_input, int students_input, string filepath, Fl_Progress *pb,
			Fl_Text_Buffer *terminal, vector<vector<Student>> allStudents,
			vector <ClassSection> allClassSections, vector<SoupCookie> cookies);

};

#endif /* SRC_MAIN_MAIN_H_ */
