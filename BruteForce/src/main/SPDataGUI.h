/*
 * SPDataGUI.h
 *
 *  Created on: Feb 25, 2020
 *      Author: myles
 */

#ifndef SRC_MAIN_SPDATAGUI_H_
#define SRC_MAIN_SPDATAGUI_H_

#include "SteamPunkGUI1.h"
#include "GUIStyles.h"
#include "main.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Check_Browser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Native_File_Chooser.H>

using namespace std;


class SPDataGUI {

	//'static' callback functions which call the real callbacks
	static void static_BrowserSelection(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->BrowserSelection(w);
	}

	static void static_FindCoursesClick(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->FindCoursesClick(w);
	}

	static void static_GobackClick(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->GobackClick(w);
	}

	static void static_ConfirmClick(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->ConfirmClick(w);
	}

	static void static_GenerateTeamsClick(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->GenerateTeamsClick(w);
	}

	static void static_CancelClick1(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->CancelClick1(w);
	}

	static void static_CancelClick2(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->CancelClick2(w);
	}

	static void static_YesClick(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->YesClick(w);
	}
	static void static_chooseProjectFile_cb(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->chooseProjectFile_cb(w);
	}

	//callback functions
	void BrowserSelection(Fl_Widget *w);
	void FindCoursesClick(Fl_Widget *w);
	void GobackClick(Fl_Widget *w);
	void ConfirmClick(Fl_Widget *w);
	void YesClick(Fl_Widget *w);
	void CancelClick1(Fl_Widget *w);
	void CancelClick2(Fl_Widget *w);
	void GenerateTeamsClick(Fl_Widget *w);
	void chooseProjectFile_cb(Fl_Widget *w);

public:

	Fl_Window *masterWindow;
	Fl_Window *prevWindow;
	Fl_Box *steamBox1;
	Fl_Box *steamBox2;

	//Class Section Selector Components
	Fl_Box *boxHeader;
	Fl_Box *boxHeader2;
	Fl_Check_Browser *classBrowser;
	Fl_Button *findCourses;
	Fl_Button *Confirm;
	Fl_Button *goBack;
	Fl_Input *inputYear;
	Fl_Input_Choice *inputSemester;
	Fl_Box *classSectionInstructionsBox;

	//Go Back window Components
	Fl_Window *backWindow;
	Fl_Button *yesButton;
	Fl_Button *cancelButton1;

	//Go Back window Components
	Fl_Window *confirmWindow;
	Fl_Button *GenerateTeamsButton;
	Fl_Button *cancelButton2;

	//Choose Project File Components
	Fl_Box *projectFileInstructionsBox;
	Fl_Button *projectFileChooserButton;
	Fl_Input *fileInput_Project;

	//Enter Student Survey Quiz Components
	Fl_Box *quizFileInstructionsBox;
	Fl_Input *fileInput_StudentQuizName;

	// Confirm or Go Back
	Fl_Box *goBackorConfirmInstructionsBox;

	SPDataGUI(Fl_Window *win);
	virtual ~SPDataGUI();

	//string array of courses for use in testing.
	string courses[17] = { "2020Fall-X-SER401-90586", "2019Fall-X-SER401-80888",
			"2020Fall-X-SER401-84566", "2019Fall-X-SER401-91286",
			"2020Fall-X-SER401-70346", "2018Fall-X-SER401-65686",
			"2018Fall-X-SER401-52586", "2020Spring-X-SER401-43586",
			"2020Spring-X-SER401-65686", "2018Spring-X-SER401-93286",
			"2020Spring-X-SER401-45586", "2019Fall-X-SER486-21686",
			"2019Fall-X-SER455-10286", "2019Fall-X-SER423-45336",
			"2018Summer-X-SER530-14186", "2019Summer-X-SER219-10986",
			"2020Summer-X-SER323-55536", };

};


#endif /* SRC_MAIN_SPDATAGUI_H_ */
