/*
 * main.h
 *
 *  Created on: Jan 28, 2020
 *      Author: myles
 */

#ifndef SRC_MAIN_MAIN_H_
#define SRC_MAIN_MAIN_H_
#include <FL/Fl_Progress.H>
#include <FL/Fl_Text_Buffer.H>

using namespace std;

class main {

public:
	string csvProjectFileName;
	int main_run(int projects_input, int students_input, string filepath, Fl_Progress *pb, Fl_Text_Buffer *terminal);

};

#endif /* SRC_MAIN_MAIN_H_ */
