/*
 * SteamPunkGUI1.h
 *
 *  Created on: Feb 19, 2020
 *      Author: myles
 */

#ifndef SRC_MAIN_STEAMPUNKGUI1_H_
#define SRC_MAIN_STEAMPUNKGUI1_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include "Student.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/names.h>

using namespace std;

class SteamPunkGUI1 {

	//generate teams 'static' callback function
	//this function calls the real TeamsButtonClick callback function.
	static void static_TeamsButtonClick(Fl_Widget *w, void *data) {
		((SteamPunkGUI1*) data)->TeamsButtonClick(w);

	}

	static void static_ProgressTeamsButtonClick(Fl_Widget *w, void *data) {
		((SteamPunkGUI1*) data)->ProgressTeamsButtonClick(w);

	}
	static void static_DoneButtonClick(Fl_Widget *w, void *data) {
		((SteamPunkGUI1*) data)->DoneButtonClick(w);

	}

	static void static_StartButtonClick(Fl_Widget *w, void *data) {
		((SteamPunkGUI1*) data)->StartButtonClick(w);

	}

	// callback functions
	void ProgressTeamsButtonClick(Fl_Widget *w);
	void DoneButtonClick(Fl_Widget *w);
	void StartButtonClick(Fl_Widget *w);
	int handle(int);
	void TeamsButtonClick(Fl_Widget *w);

public:
	static int num_projects;
	static int num_students;
	string SPGprojfile;
	vector<Student> studentsFromCanvas;
	bool nextWindowFlag;
	bool Authenticated;

	//progress bar window
	int barCount;
	//Fl_Box *backBox;
	Fl_Window *progressWindow;
	Fl_Progress *progressBar;
	Fl_Box *progressBox;
	Fl_Button *TeamsButton;
	Fl_Button *doneButton;
	Fl_Box *imageBox;
	Fl_Text_Display *terminalTextDisplay;
	Fl_Text_Buffer *terminalBuffer;

	//main window
	Fl_Window *windowMain;
	//ClassSelectorGUI *nextWindow;
	Fl_Window *nextWindow;
	Fl_Box *boxHeader;
	Fl_Button *buttonStart;
	Fl_Button *buttonOpenProject;
	Fl_Button *generateTeams;
	Fl_Int_Input *inputprojects;
	Fl_Int_Input *inputstudents;
	Fl_Box *gearBox1;
	Fl_Box *gearBox2;
	Fl_Box *gearBox3;
	Fl_Box *gearBox4;

	void MainWindow2();
	SteamPunkGUI1();
	~SteamPunkGUI1();
	void callTeams(Fl_Widget *w);

};

#endif /* SRC_MAIN_STEAMPUNKGUI1_H_ */
